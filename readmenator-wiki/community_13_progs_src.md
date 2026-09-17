# progs/src

*Community 13 | 4 files | cohesion 0.75*

## Definition

This community groups 4 file(s) rooted at `progs/src` with dominant language py (cohesion 0.75). Central symbols: `SYS_FB_INFO`, `SYS_PALETTE`, `SYS_PCSPK_INIT`, `SYS_PCSPK_TONE`, `SYS_PCSPK_VOL`, `SYS_RTC`, `SYS_SPAWN`, `SYS_TIME_MS`. Core file: `progs/lua/minios.c` (27 symbols). Documented purpose: hello.py -- frozen demo: runs at import time as a smoke test..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/lua/minios.c` | c | utility | 27 | no |
| `progs/micropython/variants/minios/lib/hello.py` | py | utility | 0 | yes |
| `progs/src/shell.py` | py | utility | 3 | yes |
| `progs/src/test.py` | py | testing | 20 | yes |

## Key Symbols

- `volatile` (function, `progs/lua/minios.c:27`) `__asm__ volatile( "syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2), "d"(a3) : "r`
- `msys5` (function, `progs/lua/minios.c:37`) `static long msys5(long n, long a1, long a2, long a3, long a4, long a5)` - /* ── raw syscall helpers (x86-64 Linux ABI) ─────────────────────────── static long msys(long n, lo
- `SYS_TIME_MS` (macro, `progs/lua/minios.c:52`) `#define SYS_TIME_MS`
- `SYS_PALETTE` (macro, `progs/lua/minios.c:53`) `#define SYS_PALETTE`
- `SYS_PCSPK_INIT` (macro, `progs/lua/minios.c:54`) `#define SYS_PCSPK_INIT`
- `SYS_PCSPK_TONE` (macro, `progs/lua/minios.c:55`) `#define SYS_PCSPK_TONE`
- `SYS_RTC` (macro, `progs/lua/minios.c:56`) `#define SYS_RTC`
- `SYS_FB_INFO` (macro, `progs/lua/minios.c:57`) `#define SYS_FB_INFO`
- `SYS_PCSPK_VOL` (macro, `progs/lua/minios.c:58`) `#define SYS_PCSPK_VOL`
- `SYS_SPAWN` (macro, `progs/lua/minios.c:59`) `#define SYS_SPAWN`
- `minios_time_ms` (function, `progs/lua/minios.c:62`) `static int minios_time_ms(lua_State *L)` - } /* ── MiniOS syscall numbers (canonical table from minios_abi.h) ─────── #include "minios_abi.h" #
- `lua_pushinteger` (function, `progs/lua/minios.c:63`) `lua_pushinteger(L, (lua_Integer)msys(SYS_TIME_MS, 0, 0, 0));`
- `minios_rtc` (function, `progs/lua/minios.c:68`) `static int minios_rtc(lua_State *L)` - #define SYS_PCSPK_INIT  MINIOS_SYS_PCSPK_INIT #define SYS_PCSPK_TONE  MINIOS_SYS_PCSPK_TONE #define
- `lua_pushnil` (function, `progs/lua/minios.c:71`) `lua_pushnil(L);`
- `lua_pushstring` (function, `progs/lua/minios.c:72`) `lua_pushstring(L, "rtc read failed");`
- `minios_fb_info` (function, `progs/lua/minios.c:82`) `static int minios_fb_info(lua_State *L)` - static int minios_rtc(lua_State *L) { int h, m, s; if (msys(SYS_RTC, (long)&h, (long)&m, (long)&s) <
- `minios_vol` (function, `progs/lua/minios.c:96`) `static int minios_vol(lua_State *L)` - static int minios_fb_info(lua_State *L) { int w, h, p; if (msys(SYS_FB_INFO, (long)&w, (long)&h, (lo
- `minios_pal` (function, `progs/lua/minios.c:109`) `static int minios_pal(lua_State *L)` - /* ── minios.vol([v]) -> current volume ─────────────────────────────── static int minios_vol(lua_St
- `msys` (function, `progs/lua/minios.c:114`) `msys(SYS_PALETTE, (long)buf, 0, 0);`
- `minios_pcspeaker` (function, `progs/lua/minios.c:119`) `static int minios_pcspeaker(lua_State *L)` - return 1; } /* ── minios.pal(buf) -- load a 768-byte VGA DAC palette ────────────── static int minio
- `minios_run` (function, `progs/lua/minios.c:136`) `static int minios_run(lua_State *L)` - ── minios.run(path[, args][, redirect]) -> exit code ─────────────── Runs a program through SYS_SPAW
- `lua_pushvalue` (function, `progs/lua/minios.c:146`) `lua_pushvalue(L, -1);` - ── minios.run(path[, args][, redirect]) -> exit code ─────────────── Runs a program through SYS_SPAW
- `lua_pop` (function, `progs/lua/minios.c:149`) `lua_pop(L, 2);`
- `luaL_error` (function, `progs/lua/minios.c:150`) `return luaL_error(L, "args must be strings");`
- `luaopen_minios` (function, `progs/lua/minios.c:191`) `int luaopen_minios(lua_State *L)`
- `lua_newtable` (function, `progs/lua/minios.c:193`) `lua_newtable(L);`
- `luaL_setfuncs` (function, `progs/lua/minios.c:194`) `luaL_setfuncs(L, minios_funcs, 0);`
- `run_capture` (function, `progs/src/shell.py:20`) `def run_capture(cmd, args)`
- `expand` (function, `progs/src/shell.py:30`) `def expand(line, env)`
- `main` (function, `progs/src/shell.py:36`) `def main()`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 3
- Cross-boundary resolved imports (EXTRACTED): 1

## Connections

- [EXTRACTED] depends_on community 13 <-> 5 (strength 0.9): Extracted import edge crosses communities: progs/lua/minios.c imports progs/minios_abi.h.

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 1 file(s) lack file-level docs (e.g. `progs/lua/minios.c`)? What purpose do they serve?
- What would break if the most connected file in progs/src changed?
- Should progs/src be split, given cohesion 0.75?

## Sources

- `progs/lua/minios.c`
- `progs/micropython/variants/minios/lib/hello.py`
- `progs/src/shell.py`
- `progs/src/test.py`
