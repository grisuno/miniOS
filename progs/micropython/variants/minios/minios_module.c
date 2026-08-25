/*
 * minios_module.c -- MicroPython bindings for MiniOS kernel services.
 *
 * Every function here runs in ring 3 and reaches the kernel through the
 * Linux syscall ABI (syscall instruction).  The module is auto-compiled
 * by the unix port wildcard rule on VARIANT_DIR .c files.
 */

#include "py/runtime.h"
#include <stdint.h>

/* ── raw syscall helper (x86-64 Linux ABI) ─────────────────────────── */

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

/* 5-argument syscall (SYS_SPAWN needs path, redirect, argc, argv, status). */
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

/* ── minios.time_ms() -> int ───────────────────────────────────────── */

static mp_obj_t minios_time_ms(void) {
    return mp_obj_new_int_from_uint((uint32_t)msys(SYS_TIME_MS, 0, 0, 0));
}
static MP_DEFINE_CONST_FUN_OBJ_0(minios_time_ms_obj, minios_time_ms);

/* ── minios.rtc() -> (hour, minute, second) ────────────────────────── */

static mp_obj_t minios_rtc(void) {
    int h, m, s;
    long ret = msys(SYS_RTC, (long)&h, (long)&m, (long)&s);
    if (ret < 0) {
        mp_raise_OSError(-ret);
    }
    mp_obj_t tuple[3] = {
        mp_obj_new_int(h),
        mp_obj_new_int(m),
        mp_obj_new_int(s),
    };
    return mp_obj_new_tuple(3, tuple);
}
static MP_DEFINE_CONST_FUN_OBJ_0(minios_rtc_obj, minios_rtc);

/* ── minios.fb_info() -> (width, height, pitch) ────────────────────── */

static mp_obj_t minios_fb_info(void) {
    int w, h, p;
    long ret = msys(SYS_FB_INFO, (long)&w, (long)&h, (long)&p);
    if (ret < 0) {
        mp_raise_OSError(-ret);
    }
    mp_obj_t tuple[3] = {
        mp_obj_new_int(w),
        mp_obj_new_int(h),
        mp_obj_new_int(p),
    };
    return mp_obj_new_tuple(3, tuple);
}
static MP_DEFINE_CONST_FUN_OBJ_0(minios_fb_info_obj, minios_fb_info);

/* ── minios.vol([value]) -> int ──────────────────────────────────────
 *    vol()       returns current volume (0..100)
 *    vol(n)      sets volume, returns new value
 */

static mp_obj_t minios_vol(size_t n_args, const mp_obj_t *args) {
    if (n_args == 0) {
        /* get volume: pass -1 to signal "read" */
        return mp_obj_new_int((int)msys(SYS_PCSPK_VOL, -1, 0, 0));
    }
    int v = mp_obj_get_int(args[0]);
    if (v < 0 || v > 100) {
        mp_raise_ValueError(MP_ERROR_TEXT("volume must be 0..100"));
    }
    return mp_obj_new_int((int)msys(SYS_PCSPK_VOL, v, 0, 0));
}
static MP_DEFINE_CONST_FUN_OBJ_VAR(minios_vol_obj, 0, minios_vol);

/* ── minios.pal(buf) -- load a 768-byte VGA DAC palette ────────────── */

static mp_obj_t minios_pal(mp_obj_t buf_in) {
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(buf_in, &bufinfo, MP_BUFFER_READ);
    if (bufinfo.len < 768) {
        mp_raise_ValueError(MP_ERROR_TEXT("palette must be 768 bytes"));
    }
    long ret = msys(SYS_PALETTE, (long)bufinfo.buf, 0, 0);
    if (ret < 0) {
        mp_raise_OSError(-ret);
    }
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(minios_pal_obj, minios_pal);

/* ── minios.pcspeaker(freq, ms) -- play a tone for ms milliseconds ── */

static mp_obj_t minios_pcspeaker(mp_obj_t freq_in, mp_obj_t ms_in) {
    int freq = mp_obj_get_int(freq_in);
    int ms = mp_obj_get_int(ms_in);
    msys(SYS_PCSPK_INIT, 0, 0, 0);
    msys(SYS_PCSPK_TONE, freq, 0, 0);
    /* busy-wait for the duration (no sleep syscall available) */
    uint32_t start = (uint32_t)msys(SYS_TIME_MS, 0, 0, 0);
    while ((uint32_t)msys(SYS_TIME_MS, 0, 0, 0) - start < (uint32_t)ms) {
        /* spin */
    }
    msys(SYS_PCSPK_TONE, 0, 0, 0);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(minios_pcspeaker_obj, minios_pcspeaker);

/* ── minios.run(path, args=None, redirect=None) -> exit code ─────────
 *    Runs a program through the kernel SYS_SPAWN (215) boundary, which
 *    preserves the caller (MicroPython) so it can chain toolchain commands.
 *    `args` is an optional list/tuple of argument strings; `redirect` is an
 *    optional output file path that captures the program's console output.
 *    Returns the child's exit code, or raises OSError on a kernel fault. */

static mp_obj_t minios_run(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_path, MP_ARG_REQUIRED | MP_ARG_OBJ, {.u_rom_obj = MP_ROM_NONE} },
        { MP_QSTR_args, MP_ARG_OBJ, {.u_rom_obj = MP_ROM_NONE} },
        { MP_QSTR_redirect, MP_ARG_OBJ, {.u_rom_obj = MP_ROM_NONE} },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    const char *path = mp_obj_str_get_str(args[0].u_obj);
    mp_obj_t args_in = args[1].u_obj;
    mp_obj_t redirect_in = args[2].u_obj;

    const char *argv[66];
    size_t n = 0;
    if (args_in != mp_const_none) {
        mp_obj_t *items;
        if (!mp_obj_is_type(args_in, &mp_type_tuple) &&
            !mp_obj_is_type(args_in, &mp_type_list)) {
            mp_raise_TypeError(MP_ERROR_TEXT("args must be a list or tuple"));
        }
        mp_obj_get_array(args_in, &n, &items);
        if (n > 64) {
            mp_raise_ValueError(MP_ERROR_TEXT("too many args"));
        }
        for (size_t i = 0; i < n; i++) {
            argv[i + 1] = mp_obj_str_get_str(items[i]);
        }
    }
    argv[0] = path;
    argv[n + 1] = NULL;

    const char *redir = NULL;
    if (redirect_in != mp_const_none) {
        redir = mp_obj_str_get_str(redirect_in);
    }

    long ret = msys5(SYS_SPAWN, (long)path, (long)redir,
                     (long)n + 1, (long)argv, 0);
    if (ret < 0) {
        mp_raise_OSError(-ret);
    }
    return mp_obj_new_int_from_uint((uint32_t)ret);
}
static MP_DEFINE_CONST_FUN_OBJ_KW(minios_run_obj, 1, minios_run);

/* ── module globals table ──────────────────────────────────────────── */

static const mp_rom_map_elem_t minios_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__),  MP_ROM_QSTR(MP_QSTR_minios) },
    { MP_ROM_QSTR(MP_QSTR_time_ms),  MP_ROM_PTR(&minios_time_ms_obj) },
    { MP_ROM_QSTR(MP_QSTR_rtc),      MP_ROM_PTR(&minios_rtc_obj) },
    { MP_ROM_QSTR(MP_QSTR_fb_info),  MP_ROM_PTR(&minios_fb_info_obj) },
    { MP_ROM_QSTR(MP_QSTR_vol),      MP_ROM_PTR(&minios_vol_obj) },
    { MP_ROM_QSTR(MP_QSTR_pal),      MP_ROM_PTR(&minios_pal_obj) },
    { MP_ROM_QSTR(MP_QSTR_pcspeaker), MP_ROM_PTR(&minios_pcspeaker_obj) },
    { MP_ROM_QSTR(MP_QSTR_run),       MP_ROM_PTR(&minios_run_obj) },
};
static MP_DEFINE_CONST_DICT(minios_module_globals, minios_module_globals_table);

const mp_obj_module_t minios_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&minios_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_minios, minios_module);
