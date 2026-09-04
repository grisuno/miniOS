# Subsystem: minios

## progs/micropython/variants/minios/manifest.py
- Layer: utility
- Doc: manifest.py -- frozen modules for the MiniOS MicroPython variant. Scripts listed here are compiled to .mpy by mpy-cross 
- Language: py

## progs/micropython/variants/minios/minios_module.c
- Layer: utility
- Language: c
- Symbols:
  - `msys5` (function, line 26) `static long msys5(long n, long a1, long a2, long a3, long a4, long a5)`
  - `minios_time_ms` (function, line 51) `static mp_obj_t minios_time_ms(void)`
  - `minios_rtc` (function, line 58) `static mp_obj_t minios_rtc(void)`
  - `minios_fb_info` (function, line 75) `static mp_obj_t minios_fb_info(void)`
  - `minios_pal` (function, line 110) `static mp_obj_t minios_pal(mp_obj_t buf_in)`
  - `minios_pcspeaker` (function, line 126) `static mp_obj_t minios_pcspeaker(mp_obj_t freq_in, mp_obj_t ms_in)`
  - `minios_run` (function, line 148) `static mp_obj_t minios_run(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)`
  - `SYS_TIME_MS` (macro, line 41)
  - `SYS_PALETTE` (macro, line 42)
  - `SYS_PCSPK_INIT` (macro, line 43)
  - `SYS_PCSPK_TONE` (macro, line 44)
  - `SYS_RTC` (macro, line 45)
  - `SYS_FB_INFO` (macro, line 46)
  - `SYS_PCSPK_VOL` (macro, line 47)
  - `SYS_SPAWN` (macro, line 48)

## progs/micropython/variants/minios/mpconfigvariant.h
- Layer: infrastructure
- Language: h
- Symbols:
  - `MICROPY_CONFIG_ROM_LEVEL` (macro, line 11)
  - `MICROPY_FLOAT_IMPL` (macro, line 14)
  - `MICROPY_LONGINT_IMPL` (macro, line 15)
  - `MICROPY_ERROR_REPORTING` (macro, line 18)
  - `MICROPY_WARNINGS` (macro, line 19)
  - `MICROPY_DEBUG_PRINTERS` (macro, line 20)
  - `MICROPY_USE_READLINE` (macro, line 23)
  - `MICROPY_KBD_EXCEPTION` (macro, line 30)
  - `MICROPY_ASYNC_KBD_INTR` (macro, line 31)
  - `MICROPY_HELPER_REPL` (macro, line 34)
  - `MICROPY_PY_SYS_PS1` (macro, line 35)
  - `MICROPY_PY_SYS_PS2` (macro, line 36)
  - `MICROPY_PY_SYS_ATEXIT` (macro, line 37)
  - `MICROPY_PY_SYS_EXC_INFO` (macro, line 38)
  - `MICROPY_PY_SYS_STDFILES` (macro, line 39)
  - `MICROPY_PY_OS` (macro, line 42)
  - `MICROPY_PY_OS_INCLUDEFILE` (macro, line 43)
  - `MICROPY_PY_OS_ERRNO` (macro, line 44)
  - `MICROPY_PY_OS_GETENV_PUTENV_UNSETENV` (macro, line 45)
  - `MICROPY_PY_OS_SYSTEM` (macro, line 46)
  - `MICROPY_PY_OS_URANDOM` (macro, line 47)
  - `MICROPY_PY_TIME` (macro, line 50)
  - `MICROPY_PY_SOCKET` (macro, line 53)
  - `MICROPY_PY_SSL` (macro, line 54)
  - `MICROPY_PY_FFI` (macro, line 55)
  - `MICROPY_PY_THREAD` (macro, line 56)
  - `MICROPY_PY_MACHINE` (macro, line 57)
  - `MICROPY_PY_WEBSOCKET` (macro, line 58)
  - `MICROPY_PERSISTENT_CODE_LOAD` (macro, line 61)
  - `MICROPY_REPL_EMACS_WORDS_MOVE` (macro, line 64)
  - `MICROPY_REPL_EMACS_EXTRA_WORDS_MOVE` (macro, line 65)
  - `MICROPY_USE_READLINE_HISTORY` (macro, line 66)
  - `MICROPY_OPT_COMPUTED_GOTO` (macro, line 71)
  - `MICROPY_ENABLE_EMERGENCY_EXCEPTION_BUF` (macro, line 74)
  - `MICROPY_EMERGENCY_EXCEPTION_BUF_SIZE` (macro, line 75)
  - `MICROPY_PY_GC_COLLECT_RETVAL` (macro, line 78)
  - `MICROPY_VFS_ROM` (macro, line 81)
  - `MICROPY_VFS_ROM_IOCTL` (macro, line 82)
