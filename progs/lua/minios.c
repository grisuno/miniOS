/*
 * minios.c -- Lua bindings for MiniOS kernel services.
 *
 * Every function here runs in ring 3 and reaches the kernel through the
 * Linux syscall ABI (the syscall instruction), exactly like the `minios`
 * module MicroPython ships.  The module is registered globally at Lua startup
 * (see lua_main.c), so `minios.run(...)` etc. work directly, like
 * `import minios` in MicroPython.
 *
 * Exposed functions:
 *   minios.time_ms()        -> ms since boot
 *   minios.rtc()            -> hour, minute, second
 *   minios.fb_info()        -> width, height, pitch
 *   minios.vol([v])         -> get/set PC-speaker volume (0..100)
 *   minios.pal(buf)         -> load a 768-byte VGA DAC palette
 *   minios.pcspeaker(f,m)   -> play PC-speaker tone for ms milliseconds
 *   minios.run(path[,args][,redirect]) -> run a program via SYS_SPAWN (215)
 */

#include "lua.h"
#include "lauxlib.h"
#include <stdint.h>

/* ── raw syscall helpers (x86-64 Linux ABI) ─────────────────────────── */
static long msys(long n, long a1, long a2, long a3) {
    long ret;
    __asm__ volatile(
        "syscall"
        : "=a"(ret)
        : "a"(n), "D"(a1), "S"(a2), "d"(a3)
        : "rcx", "r11", "memory"
    );
    return ret;
}

/* 5-argument syscall (SYS_SPAWN needs path, redirect, argc, argv). */
static long msys5(long n, long a1, long a2, long a3, long a4, long a5) {
    long ret;
    register long r10 __asm__("r10") = a4;
    register long r8  __asm__("r8")  = a5;
    __asm__ volatile(
        "syscall"
        : "=a"(ret)
        : "a"(n), "D"(a1), "S"(a2), "d"(a3), "r"(r10), "r"(r8)
        : "rcx", "r11", "memory"
    );
    return ret;
}

/* ── MiniOS syscall numbers (must match kernel.c) ──────────────────── */
#define SYS_TIME_MS     204
#define SYS_PALETTE     206
#define SYS_PCSPK_INIT  209
#define SYS_PCSPK_TONE  210
#define SYS_RTC         212
#define SYS_FB_INFO     213
#define SYS_PCSPK_VOL   214
#define SYS_SPAWN       215

/* ── minios.time_ms() ──────────────────────────────────────────────── */
static int minios_time_ms(lua_State *L) {
    lua_pushinteger(L, (lua_Integer)msys(SYS_TIME_MS, 0, 0, 0));
    return 1;
}

/* ── minios.rtc() -> hour, minute, second ──────────────────────────── */
static int minios_rtc(lua_State *L) {
    int h, m, s;
    if (msys(SYS_RTC, (long)&h, (long)&m, (long)&s) < 0) {
        lua_pushnil(L);
        lua_pushstring(L, "rtc read failed");
        return 2;
    }
    lua_pushinteger(L, h);
    lua_pushinteger(L, m);
    lua_pushinteger(L, s);
    return 3;
}

/* ── minios.fb_info() -> width, height, pitch ──────────────────────── */
static int minios_fb_info(lua_State *L) {
    int w, h, p;
    if (msys(SYS_FB_INFO, (long)&w, (long)&h, (long)&p) < 0) {
        lua_pushnil(L);
        lua_pushstring(L, "fb_info failed");
        return 2;
    }
    lua_pushinteger(L, w);
    lua_pushinteger(L, h);
    lua_pushinteger(L, p);
    return 3;
}

/* ── minios.vol([v]) -> current volume ─────────────────────────────── */
static int minios_vol(lua_State *L) {
    if (lua_gettop(L) >= 1 && !lua_isnil(L, 1)) {
        int v = (int)luaL_checkinteger(L, 1);
        if (v < 0 || v > 100)
            return luaL_error(L, "volume must be 0..100");
        lua_pushinteger(L, (lua_Integer)msys(SYS_PCSPK_VOL, v, 0, 0));
    } else {
        lua_pushinteger(L, (lua_Integer)msys(SYS_PCSPK_VOL, -1, 0, 0));
    }
    return 1;
}

/* ── minios.pal(buf) -- load a 768-byte VGA DAC palette ────────────── */
static int minios_pal(lua_State *L) {
    size_t len;
    const char *buf = luaL_checklstring(L, 1, &len);
    if (len < 768)
        return luaL_error(L, "palette must be 768 bytes");
    msys(SYS_PALETTE, (long)buf, 0, 0);
    return 0;
}

/* ── minios.pcspeaker(freq, ms) ────────────────────────────────────── */
static int minios_pcspeaker(lua_State *L) {
    int freq = (int)luaL_checkinteger(L, 1);
    int ms   = (int)luaL_optinteger(L, 2, 200);
    msys(SYS_PCSPK_INIT, 0, 0, 0);
    msys(SYS_PCSPK_TONE, freq, 0, 0);
    uint32_t start = (uint32_t)msys(SYS_TIME_MS, 0, 0, 0);
    while ((uint32_t)msys(SYS_TIME_MS, 0, 0, 0) - start < (uint32_t)ms) {
        /* spin */
    }
    msys(SYS_PCSPK_TONE, 0, 0, 0);
    return 0;
}

/* ── minios.run(path[, args][, redirect]) -> exit code ───────────────
 * Runs a program through SYS_SPAWN (215), preserving the caller (Lua) so it
 * can chain toolchain commands.  args is an optional Lua table of strings;
 * redirect is an optional output file path that captures the console output. */
static int minios_run(lua_State *L) {
    const char *path = luaL_checkstring(L, 1);
    const char *argv[66];
    size_t n = 0;
    argv[0] = path;

    if (lua_gettop(L) >= 2 && lua_istable(L, 2)) {
        lua_pushnil(L);
        while (lua_next(L, 2) != 0) {
            /* key is at -2, value at -1 */
            lua_pushvalue(L, -1);
            const char *s = lua_tostring(L, -1);
            if (s == NULL) {
                lua_pop(L, 2);
                return luaL_error(L, "args must be strings");
            }
            if (n + 1 >= 65) {
                lua_pop(L, 2);
                return luaL_error(L, "too many args");
            }
            argv[n + 1] = s;
            n++;
            lua_pop(L, 2);
        }
    } else if (lua_gettop(L) >= 2 && !lua_isnil(L, 2)) {
        return luaL_error(L, "args must be a table");
    }
    argv[n + 1] = NULL;

    const char *redir = NULL;
    if (lua_gettop(L) >= 3 && !lua_isnil(L, 3))
        redir = luaL_checkstring(L, 3);

    long ret = msys5(SYS_SPAWN, (long)path, (long)redir,
                     (long)n + 1, (long)argv, 0);
    if (ret < 0) {
        lua_pushnil(L);
        lua_pushstring(L, "spawn failed");
        return 2;
    }
    lua_pushinteger(L, (lua_Integer)ret);
    return 1;
}

/* ── module table ──────────────────────────────────────────────────── */
static const luaL_Reg minios_funcs[] = {
    {"time_ms",    minios_time_ms},
    {"rtc",        minios_rtc},
    {"fb_info",    minios_fb_info},
    {"vol",        minios_vol},
    {"pal",        minios_pal},
    {"pcspeaker",  minios_pcspeaker},
    {"run",        minios_run},
    {NULL, NULL}
};

int luaopen_minios(lua_State *L) {
    lua_newtable(L);
    luaL_setfuncs(L, minios_funcs, 0);
    return 1;
}
