# Subsystem: lua

## progs/lua/lua_main.c
- Layer: utility
- Language: c
- Symbols:
  - `luaL_require_global` (function, line 22) `static void luaL_require_global(lua_State *L, const char *name,
                                l...`
  - `set_arg_table` (function, line 28) `static void set_arg_table(lua_State *L, int argc, char **argv, int first)`
  - `docode` (function, line 41) `static int docode(lua_State *L, const char *code)`
  - `dofile` (function, line 51) `static int dofile(lua_State *L, const char *name)`
  - `repl` (function, line 61) `static int repl(lua_State *L)`
  - `main` (function, line 105) `int main(int argc, char **argv)`
  - `module` (function, line 5) `* C module (minios.c) can be registered globally before any script runs: * `minios.run(...)`, `minios.time_ms()`, etc. are available as a plain global * table, exactly like `import minios` in MicroPyt`
- Depends on: `kernel/string.c`

## progs/lua/minios.c
- Layer: utility
- Language: c
- Symbols:
  - `msys5` (function, line 37) `static long msys5(long n, long a1, long a2, long a3, long a4, long a5)`
  - `minios_time_ms` (function, line 62) `static int minios_time_ms(lua_State *L)`
  - `minios_rtc` (function, line 68) `static int minios_rtc(lua_State *L)`
  - `minios_fb_info` (function, line 82) `static int minios_fb_info(lua_State *L)`
  - `minios_vol` (function, line 96) `static int minios_vol(lua_State *L)`
  - `minios_pal` (function, line 109) `static int minios_pal(lua_State *L)`
  - `minios_pcspeaker` (function, line 119) `static int minios_pcspeaker(lua_State *L)`
  - `minios_run` (function, line 136) `static int minios_run(lua_State *L)`
  - `luaopen_minios` (function, line 192) `int luaopen_minios(lua_State *L)`
  - `SYS_TIME_MS` (macro, line 52) `#define SYS_TIME_MS`
  - `SYS_PALETTE` (macro, line 53) `#define SYS_PALETTE`
  - `SYS_PCSPK_INIT` (macro, line 54) `#define SYS_PCSPK_INIT`
  - `SYS_PCSPK_TONE` (macro, line 55) `#define SYS_PCSPK_TONE`
  - `SYS_RTC` (macro, line 56) `#define SYS_RTC`
  - `SYS_FB_INFO` (macro, line 57) `#define SYS_FB_INFO`
  - `SYS_PCSPK_VOL` (macro, line 58) `#define SYS_PCSPK_VOL`
  - `SYS_SPAWN` (macro, line 59) `#define SYS_SPAWN`
- Depends on: `progs/minios_abi.h`
- Imported by: `progs/micropython/variants/minios/lib/hello.py`, `progs/src/shell.py`, `progs/src/test.py`
