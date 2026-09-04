# Subsystem: lua

## progs/lua/lua_main.c
- Layer: utility
- Language: c
- Symbols:
  - `luaL_require_global` (function, line 21) `static void luaL_require_global(lua_State *L, const char *name,
                                l...`
  - `set_arg_table` (function, line 27) `static void set_arg_table(lua_State *L, int argc, char **argv, int first)`
  - `docode` (function, line 40) `static int docode(lua_State *L, const char *code)`
  - `dofile` (function, line 50) `static int dofile(lua_State *L, const char *name)`
  - `repl` (function, line 60) `static int repl(lua_State *L)`
  - `main` (function, line 104) `int main(int argc, char **argv)`

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
  - `luaopen_minios` (function, line 191) `int luaopen_minios(lua_State *L)`
  - `SYS_TIME_MS` (macro, line 52)
  - `SYS_PALETTE` (macro, line 53)
  - `SYS_PCSPK_INIT` (macro, line 54)
  - `SYS_PCSPK_TONE` (macro, line 55)
  - `SYS_RTC` (macro, line 56)
  - `SYS_FB_INFO` (macro, line 57)
  - `SYS_PCSPK_VOL` (macro, line 58)
  - `SYS_SPAWN` (macro, line 59)
- Imported by: `progs/micropython/variants/minios/lib/hello.py`, `progs/src/shell.py`, `progs/src/test.py`
