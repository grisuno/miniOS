# Symbols (page 20 of 27)
Previous: [SYMBOLS_p19.md](SYMBOLS_p19.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `make_num` | function | `progs/lisp/lisp.c:302` | `static Node *make_num(Runtime *rt, int64_t value)` |
| `make_prim` | function | `progs/lisp/lisp.c:329` | `static Node *make_prim(Runtime *rt, PrimFn function)` |
| `make_str` | function | `progs/lisp/lisp.c:311` | `static Node *make_str(Runtime *rt, const char *value)` |
| `make_sym` | function | `progs/lisp/lisp.c:320` | `static Node *make_sym(Runtime *rt, const char *value)` |
| `msys` | function | `progs/lisp/lisp.c:205` | `static long msys(long n, long a1, long a2, long a3)` |
| `msys5` | function | `progs/lisp/lisp.c:218` | `static long msys5(long n, long a1, long a2, long a3, long a4, long a5)` |
| `numbers` | function | `progs/lisp/lisp.c:9` | `* * Language surface: numbers (int64), strings, symbols, cons cells, closures * with lexical scope, and the special...` |
| `parse_eof` | function | `progs/lisp/lisp.c:573` | `static ParseResult parse_eof(void)` |
| `parse_error` | function | `progs/lisp/lisp.c:584` | `static ParseResult parse_error(const char *message)` |
| `parse_ok` | function | `progs/lisp/lisp.c:562` | `static ParseResult parse_ok(Node *value)` |
| `prim_add` | function | `progs/lisp/lisp.c:869` | `static Node *prim_add(Runtime *rt, Node *args)` |
| `prim_car` | function | `progs/lisp/lisp.c:963` | `static Node *prim_car(Runtime *rt, Node *args)` |
| `prim_cdr` | function | `progs/lisp/lisp.c:975` | `static Node *prim_cdr(Runtime *rt, Node *args)` |
| `prim_char_code` | function | `progs/lisp/lisp.c:1072` | `static Node *prim_char_code(Runtime *rt, Node *args)` |
| `prim_close_file` | function | `progs/lisp/lisp.c:1224` | `static Node *prim_close_file(Runtime *rt, Node *args)` |
| `prim_cons` | function | `progs/lisp/lisp.c:987` | `static Node *prim_cons(Runtime *rt, Node *args)` |
| `prim_div` | function | `progs/lisp/lisp.c:917` | `static Node *prim_div(Runtime *rt, Node *args)` |
| `prim_eq` | function | `progs/lisp/lisp.c:939` | `static Node *prim_eq(Runtime *rt, Node *args)` |
| `prim_error_message` | function | `progs/lisp/lisp.c:1285` | `static Node *prim_error_message(Runtime *rt, Node *args)` |
| `prim_exit` | function | `progs/lisp/lisp.c:1303` | `static Node *prim_exit(Runtime *rt, Node *args)` |
| `prim_fb_info` | function | `progs/lisp/lisp.c:1357` | `static Node *prim_fb_info(Runtime *rt, Node *args)` |
| `prim_lt` | function | `progs/lisp/lisp.c:951` | `static Node *prim_lt(Runtime *rt, Node *args)` |
| `prim_minios_run` | function | `progs/lisp/lisp.c:1465` | `static Node *prim_minios_run(Runtime *rt, Node *args)` |
| `prim_mul` | function | `progs/lisp/lisp.c:901` | `static Node *prim_mul(Runtime *rt, Node *args)` |
| `prim_null_p` | function | `progs/lisp/lisp.c:1249` | `static Node *prim_null_p(Runtime *rt, Node *args)` |
| `prim_number_p` | function | `progs/lisp/lisp.c:1261` | `static Node *prim_number_p(Runtime *rt, Node *args)` |
| `prim_pal` | function | `progs/lisp/lisp.c:1405` | `static Node *prim_pal(Runtime *rt, Node *args)` |
| `prim_pcspeaker` | function | `progs/lisp/lisp.c:1421` | `static Node *prim_pcspeaker(Runtime *rt, Node *args)` |
| `prim_print` | function | `progs/lisp/lisp.c:1094` | `static Node *prim_print(Runtime *rt, Node *args)` |
| `prim_println` | function | `progs/lisp/lisp.c:1108` | `static Node *prim_println(Runtime *rt, Node *args)` |
| `prim_read_char` | function | `progs/lisp/lisp.c:1183` | `static Node *prim_read_char(Runtime *rt, Node *args)` |
| `prim_rtc` | function | `progs/lisp/lisp.c:1340` | `static Node *prim_rtc(Runtime *rt, Node *args)` |
| `prim_string_at` | function | `progs/lisp/lisp.c:1050` | `static Node *prim_string_at(Runtime *rt, Node *args)` |
| `prim_string_concat` | function | `progs/lisp/lisp.c:999` | `static Node *prim_string_concat(Runtime *rt, Node *args)` |
| `prim_string_eq` | function | `progs/lisp/lisp.c:1026` | `static Node *prim_string_eq(Runtime *rt, Node *args)` |
| `prim_string_length` | function | `progs/lisp/lisp.c:1038` | `static Node *prim_string_length(Runtime *rt, Node *args)` |
| `prim_string_p` | function | `progs/lisp/lisp.c:1273` | `static Node *prim_string_p(Runtime *rt, Node *args)` |
| `prim_sub` | function | `progs/lisp/lisp.c:885` | `static Node *prim_sub(Runtime *rt, Node *args)` |
| `prim_time_ms` | function | `progs/lisp/lisp.c:1330` | `static Node *prim_time_ms(Runtime *rt, Node *args)` |
| `prim_vol` | function | `progs/lisp/lisp.c:1377` | `static Node *prim_vol(Runtime *rt, Node *args)` |
| `prim_write` | function | `progs/lisp/lisp.c:1200` | `static Node *prim_write(Runtime *rt, Node *args)` |
| `print_escaped_string` | function | `progs/lisp/lisp.c:1846` | `static void print_escaped_string(FILE *out, const char *value)` |
| `print_node` | function | `progs/lisp/lisp.c:1877` | `static void print_node(Runtime *rt, Node *node, bool readable)` |
| `print_usage` | function | `progs/lisp/lisp.c:2136` | `static void print_usage(Runtime *rt)` |
| `process_inline` | function | `progs/lisp/lisp.c:2129` | `static int process_inline(Runtime *rt, const char *code)` |
| `process_source` | function | `progs/lisp/lisp.c:2087` | `static int process_source(Runtime *rt, const char *source,     const char *source_name, bool echo)` |
| `read_all_file` | function | `progs/lisp/lisp.c:2029` | `static char *read_all_file(const char *filename, size_t max_bytes)` |
| `read_atom` | function | `progs/lisp/lisp.c:685` | `static ParseResult read_atom(Runtime *rt, Reader *reader)` |
| `read_expr` | function | `progs/lisp/lisp.c:721` | `static ParseResult read_expr(Runtime *rt, Reader *reader)` |
| `read_list` | function | `progs/lisp/lisp.c:596` | `static ParseResult read_list(Runtime *rt, Reader *reader)` |
| `read_string` | function | `progs/lisp/lisp.c:626` | `static ParseResult read_string(Runtime *rt, Reader *reader)` |
| `reader_at_end` | function | `progs/lisp/lisp.c:500` | `static bool reader_at_end(const Reader *reader)` |
| `reader_next` | function | `progs/lisp/lisp.c:482` | `static char reader_next(Reader *reader)` |
| `reader_peek` | function | `progs/lisp/lisp.c:475` | `static char reader_peek(const Reader *reader)` |
| `repl` | function | `progs/lisp/lisp.c:2143` | `static int repl(Runtime *rt)` |
| `runtime_init` | function | `progs/lisp/lisp.c:399` | `static void runtime_init(Runtime *rt)` |
| `sb_init` | function | `progs/lisp/lisp.c:523` | `static void sb_init(StringBuilder *builder)` |
| `sb_push` | function | `progs/lisp/lisp.c:536` | `static void sb_push(StringBuilder *builder, char value)` |
| `skip_space_and_comments` | function | `progs/lisp/lisp.c:507` | `static void skip_space_and_comments(Reader *reader)` |
| `token_delimiter` | function | `progs/lisp/lisp.c:677` | `static bool token_delimiter(char c)` |
| `valid_params` | function | `progs/lisp/lisp.c:1569` | `static bool valid_params(Runtime *rt, Node *params)` |
| `xalloc` | function | `progs/lisp/lisp.c:242` | `static void *xalloc(Runtime *rt, size_t size)` |
| `xstrdup` | function | `progs/lisp/lisp.c:266` | `static char *xstrdup(Runtime *rt, const char *source)` |
| `main` | function | `progs/lisp/tin.c:1` | `int main()` |
| `docode` | function | `progs/lua/lua_main.c:41` | `static int docode(lua_State *L, const char *code)` |
| `dofile` | function | `progs/lua/lua_main.c:51` | `static int dofile(lua_State *L, const char *name)` |
| `luaL_require_global` | function | `progs/lua/lua_main.c:22` | `static void luaL_require_global(lua_State *L, const char *name,                                 l...` |
| `main` | function | `progs/lua/lua_main.c:105` | `int main(int argc, char **argv)` |
| `module` | function | `progs/lua/lua_main.c:5` | `* C module (minios.c) can be registered globally before any script runs: * `minios.run(...)`, `minios.time_ms()`...` |
| `repl` | function | `progs/lua/lua_main.c:61` | `static int repl(lua_State *L)` |
| `set_arg_table` | function | `progs/lua/lua_main.c:28` | `static void set_arg_table(lua_State *L, int argc, char **argv, int first)` |
| `SYS_FB_INFO` | macro | `progs/lua/minios.c:57` | `#define SYS_FB_INFO` |
| `SYS_PALETTE` | macro | `progs/lua/minios.c:53` | `#define SYS_PALETTE` |
| `SYS_PCSPK_INIT` | macro | `progs/lua/minios.c:54` | `#define SYS_PCSPK_INIT` |
| `SYS_PCSPK_TONE` | macro | `progs/lua/minios.c:55` | `#define SYS_PCSPK_TONE` |
| `SYS_PCSPK_VOL` | macro | `progs/lua/minios.c:58` | `#define SYS_PCSPK_VOL` |
| `SYS_RTC` | macro | `progs/lua/minios.c:56` | `#define SYS_RTC` |
| `SYS_SPAWN` | macro | `progs/lua/minios.c:59` | `#define SYS_SPAWN` |
| `SYS_TIME_MS` | macro | `progs/lua/minios.c:52` | `#define SYS_TIME_MS` |
| `luaopen_minios` | function | `progs/lua/minios.c:192` | `int luaopen_minios(lua_State *L)` |
| `minios_fb_info` | function | `progs/lua/minios.c:82` | `static int minios_fb_info(lua_State *L)` |
| `minios_pal` | function | `progs/lua/minios.c:109` | `static int minios_pal(lua_State *L)` |
| `minios_pcspeaker` | function | `progs/lua/minios.c:119` | `static int minios_pcspeaker(lua_State *L)` |
| `minios_rtc` | function | `progs/lua/minios.c:68` | `static int minios_rtc(lua_State *L)` |
| `minios_run` | function | `progs/lua/minios.c:136` | `static int minios_run(lua_State *L)` |
| `minios_time_ms` | function | `progs/lua/minios.c:62` | `static int minios_time_ms(lua_State *L)` |
| `minios_vol` | function | `progs/lua/minios.c:96` | `static int minios_vol(lua_State *L)` |
| `msys5` | function | `progs/lua/minios.c:37` | `static long msys5(long n, long a1, long a2, long a3, long a4, long a5)` |
| `_is_module_stem` | function | `progs/micropython/variants/minios/lib/mip.py:136` | `def _is_module_stem(stem)` |
| `_split_authority_path` | function | `progs/micropython/variants/minios/lib/mip.py:67` | `def _split_authority_path(url, rest, default_port)` |
| `_status_code` | function | `progs/micropython/variants/minios/lib/mip.py:191` | `def _status_code(line)` |
| `_unlink_quiet` | function | `progs/micropython/variants/minios/lib/mip.py:268` | `def _unlink_quiet(path)` |
| `absolute_url` | function | `progs/micropython/variants/minios/lib/mip.py:202` | `def absolute_url(base, location)` |
| `ensure_dir` | function | `progs/micropython/variants/minios/lib/mip.py:276` | `def ensure_dir(path)` |
| `http_get` | function | `progs/micropython/variants/minios/lib/mip.py:222` | `def http_get(host, port, path)` |
| `https_get` | function | `progs/micropython/variants/minios/lib/mip.py:298` | `def https_get(host, port, path)` |
| `install` | function | `progs/micropython/variants/minios/lib/mip.py:336` | `def install(url, dest)` |
| `main` | function | `progs/micropython/variants/minios/lib/mip.py:394` | `def main(argv)` |
| `module_name` | function | `progs/micropython/variants/minios/lib/mip.py:114` | `def module_name(url)` |
| `parse_response` | function | `progs/micropython/variants/minios/lib/mip.py:150` | `def parse_response(data)` |
| `parse_url` | function | `progs/micropython/variants/minios/lib/mip.py:49` | `def parse_url(url)` |
| `split_https_url` | function | `progs/micropython/variants/minios/lib/mip.py:106` | `def split_https_url(url)` |
| `split_url` | function | `progs/micropython/variants/minios/lib/mip.py:98` | `def split_url(url)` |
| `MP_DEFINE_CONST_DICT` | function | `progs/micropython/variants/minios/minios_module.c:207` | `static MP_DEFINE_CONST_DICT(minios_module_globals, minios_module_globals_table);` |
| `MP_DEFINE_CONST_FUN_OBJ_0` | function | `progs/micropython/variants/minios/minios_module.c:55` | `static MP_DEFINE_CONST_FUN_OBJ_0(minios_time_ms_obj, minios_time_ms);` |
| `MP_DEFINE_CONST_FUN_OBJ_1` | function | `progs/micropython/variants/minios/minios_module.c:123` | `static MP_DEFINE_CONST_FUN_OBJ_1(minios_pal_obj, minios_pal);` |
| `MP_DEFINE_CONST_FUN_OBJ_2` | function | `progs/micropython/variants/minios/minios_module.c:140` | `static MP_DEFINE_CONST_FUN_OBJ_2(minios_pcspeaker_obj, minios_pcspeaker);` |
| `MP_DEFINE_CONST_FUN_OBJ_KW` | function | `progs/micropython/variants/minios/minios_module.c:193` | `static MP_DEFINE_CONST_FUN_OBJ_KW(minios_run_obj, 1, minios_run);` |
| `MP_DEFINE_CONST_FUN_OBJ_VAR` | function | `progs/micropython/variants/minios/minios_module.c:107` | `static MP_DEFINE_CONST_FUN_OBJ_VAR(minios_vol_obj, 0, minios_vol);` |
| `SYS_FB_INFO` | macro | `progs/micropython/variants/minios/minios_module.c:46` | `#define SYS_FB_INFO` |
| `SYS_PALETTE` | macro | `progs/micropython/variants/minios/minios_module.c:42` | `#define SYS_PALETTE` |
| `SYS_PCSPK_INIT` | macro | `progs/micropython/variants/minios/minios_module.c:43` | `#define SYS_PCSPK_INIT` |
| `SYS_PCSPK_TONE` | macro | `progs/micropython/variants/minios/minios_module.c:44` | `#define SYS_PCSPK_TONE` |
| `SYS_PCSPK_VOL` | macro | `progs/micropython/variants/minios/minios_module.c:47` | `#define SYS_PCSPK_VOL` |
| `SYS_RTC` | macro | `progs/micropython/variants/minios/minios_module.c:45` | `#define SYS_RTC` |
| `SYS_SPAWN` | macro | `progs/micropython/variants/minios/minios_module.c:48` | `#define SYS_SPAWN` |
| `SYS_TIME_MS` | macro | `progs/micropython/variants/minios/minios_module.c:41` | `#define SYS_TIME_MS` |
| `minios_fb_info` | function | `progs/micropython/variants/minios/minios_module.c:76` | `static mp_obj_t minios_fb_info(void)` |
| `minios_pal` | function | `progs/micropython/variants/minios/minios_module.c:111` | `static mp_obj_t minios_pal(mp_obj_t buf_in)` |
| `minios_pcspeaker` | function | `progs/micropython/variants/minios/minios_module.c:127` | `static mp_obj_t minios_pcspeaker(mp_obj_t freq_in, mp_obj_t ms_in)` |
| `minios_rtc` | function | `progs/micropython/variants/minios/minios_module.c:59` | `static mp_obj_t minios_rtc(void)` |
| `minios_run` | function | `progs/micropython/variants/minios/minios_module.c:149` | `static mp_obj_t minios_run(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)` |
| `minios_time_ms` | function | `progs/micropython/variants/minios/minios_module.c:52` | `static mp_obj_t minios_time_ms(void)` |
| `msys5` | function | `progs/micropython/variants/minios/minios_module.c:26` | `static long msys5(long n, long a1, long a2, long a3, long a4, long a5)` |
| `MICROPY_ASYNC_KBD_INTR` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:31` | `#define MICROPY_ASYNC_KBD_INTR` |
| `MICROPY_CONFIG_ROM_LEVEL` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:11` | `#define MICROPY_CONFIG_ROM_LEVEL` |
| `MICROPY_DEBUG_PRINTERS` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:20` | `#define MICROPY_DEBUG_PRINTERS` |
| `MICROPY_EMERGENCY_EXCEPTION_BUF_SIZE` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:103` | `#define MICROPY_EMERGENCY_EXCEPTION_BUF_SIZE` |
| `MICROPY_ENABLE_EMERGENCY_EXCEPTION_BUF` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:102` | `#define MICROPY_ENABLE_EMERGENCY_EXCEPTION_BUF` |
| `MICROPY_ERROR_REPORTING` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:18` | `#define MICROPY_ERROR_REPORTING` |
| `MICROPY_FLOAT_IMPL` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:14` | `#define MICROPY_FLOAT_IMPL` |
| `MICROPY_HELPER_REPL` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:34` | `#define MICROPY_HELPER_REPL` |
| `MICROPY_KBD_EXCEPTION` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:30` | `#define MICROPY_KBD_EXCEPTION` |
| `MICROPY_LONGINT_IMPL` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:15` | `#define MICROPY_LONGINT_IMPL` |
| `MICROPY_OPT_COMPUTED_GOTO` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:99` | `#define MICROPY_OPT_COMPUTED_GOTO` |
| `MICROPY_PERSISTENT_CODE_LOAD` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:89` | `#define MICROPY_PERSISTENT_CODE_LOAD` |
| `MICROPY_PY_ASYNCIO` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:65` | `#define MICROPY_PY_ASYNCIO` |
| `MICROPY_PY_ERRNO` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:73` | `#define MICROPY_PY_ERRNO` |
| `MICROPY_PY_FFI` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:83` | `#define MICROPY_PY_FFI` |
| `MICROPY_PY_GC_COLLECT_RETVAL` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:106` | `#define MICROPY_PY_GC_COLLECT_RETVAL` |
| `MICROPY_PY_MACHINE` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:85` | `#define MICROPY_PY_MACHINE` |
| `MICROPY_PY_OS` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:42` | `#define MICROPY_PY_OS` |
| `MICROPY_PY_OS_ERRNO` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:44` | `#define MICROPY_PY_OS_ERRNO` |
| `MICROPY_PY_OS_GETENV_PUTENV_UNSETENV` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:45` | `#define MICROPY_PY_OS_GETENV_PUTENV_UNSETENV` |
| `MICROPY_PY_OS_INCLUDEFILE` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:43` | `#define MICROPY_PY_OS_INCLUDEFILE` |
| `MICROPY_PY_OS_SYSTEM` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:46` | `#define MICROPY_PY_OS_SYSTEM` |
| `MICROPY_PY_OS_URANDOM` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:47` | `#define MICROPY_PY_OS_URANDOM` |
| `MICROPY_PY_SELECT` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:60` | `#define MICROPY_PY_SELECT` |
| `MICROPY_PY_SELECT_POSIX_OPTIMISATIONS` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:61` | `#define MICROPY_PY_SELECT_POSIX_OPTIMISATIONS` |
| `MICROPY_PY_SELECT_SELECT` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:62` | `#define MICROPY_PY_SELECT_SELECT` |
| `MICROPY_PY_SSL` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:82` | `#define MICROPY_PY_SSL` |
| `MICROPY_PY_SYS_ATEXIT` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:37` | `#define MICROPY_PY_SYS_ATEXIT` |
| `MICROPY_PY_SYS_EXC_INFO` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:38` | `#define MICROPY_PY_SYS_EXC_INFO` |
| `MICROPY_PY_SYS_PS1` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:35` | `#define MICROPY_PY_SYS_PS1` |
| `MICROPY_PY_SYS_PS2` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:36` | `#define MICROPY_PY_SYS_PS2` |
| `MICROPY_PY_SYS_STDFILES` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:39` | `#define MICROPY_PY_SYS_STDFILES` |
| `MICROPY_PY_THREAD` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:84` | `#define MICROPY_PY_THREAD` |
| `MICROPY_PY_TIME` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:76` | `#define MICROPY_PY_TIME` |
| `MICROPY_PY_TIME_CUSTOM_SLEEP` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:79` | `#define MICROPY_PY_TIME_CUSTOM_SLEEP` |
| `MICROPY_PY_TIME_INCLUDEFILE` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:77` | `#define MICROPY_PY_TIME_INCLUDEFILE` |
| `MICROPY_PY_TIME_TIME_TIME_NS` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:78` | `#define MICROPY_PY_TIME_TIME_TIME_NS` |
| `MICROPY_PY_WEBSOCKET` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:86` | `#define MICROPY_PY_WEBSOCKET` |
| `MICROPY_REPL_EMACS_EXTRA_WORDS_MOVE` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:93` | `#define MICROPY_REPL_EMACS_EXTRA_WORDS_MOVE` |
| `MICROPY_REPL_EMACS_WORDS_MOVE` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:92` | `#define MICROPY_REPL_EMACS_WORDS_MOVE` |
| `MICROPY_STREAMS_NON_BLOCK` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:70` | `#define MICROPY_STREAMS_NON_BLOCK` |
| `MICROPY_USE_READLINE` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:23` | `#define MICROPY_USE_READLINE` |
| `MICROPY_USE_READLINE_HISTORY` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:94` | `#define MICROPY_USE_READLINE_HISTORY` |
| `MICROPY_VFS_ROM` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:109` | `#define MICROPY_VFS_ROM` |
| `MICROPY_VFS_ROM_IOCTL` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:110` | `#define MICROPY_VFS_ROM_IOCTL` |
| `MICROPY_WARNINGS` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:19` | `#define MICROPY_WARNINGS` |
| `BACKBUF` | macro | `progs/minicraft/minicraft.c:45` | `#define BACKBUF` |
| `BACKBUF` | macro | `progs/minicraft/minicraft.c:47` | `#define BACKBUF` |
| `ChunkHeader` | struct | `progs/minicraft/minicraft.c:2907` | `` |
| `EXT_DOWN` | macro | `progs/minicraft/minicraft.c:151` | `#define EXT_DOWN` |
| `EXT_F11` | macro | `progs/minicraft/minicraft.c:154` | `#define EXT_F11` |
| `EXT_LEFT` | macro | `progs/minicraft/minicraft.c:152` | `#define EXT_LEFT` |
| `EXT_RIGHT` | macro | `progs/minicraft/minicraft.c:153` | `#define EXT_RIGHT` |
| `EXT_UP` | macro | `progs/minicraft/minicraft.c:150` | `#define EXT_UP` |
| `FB_H` | macro | `progs/minicraft/minicraft.c:42` | `#define FB_H` |
| `FB_W` | macro | `progs/minicraft/minicraft.c:41` | `#define FB_W` |
| `MC_AUTOSTEP` | macro | `progs/minicraft/minicraft.c:78` | `#define MC_AUTOSTEP` |
| `MC_BAYER_N` | macro | `progs/minicraft/minicraft.c:110` | `#define MC_BAYER_N` |
| `MC_BOOM_R` | macro | `progs/minicraft/minicraft.c:85` | `#define MC_BOOM_R` |
| `MC_BREAK_GRACE_MS` | macro | `progs/minicraft/minicraft.c:71` | `#define MC_BREAK_GRACE_MS` |
| `MC_BREAK_MS` | macro | `progs/minicraft/minicraft.c:70` | `#define MC_BREAK_MS` |
| `MC_CHUNK` | macro | `progs/minicraft/minicraft.c:35` | `#define MC_CHUNK` |
| `MC_CHUNKS` | macro | `progs/minicraft/minicraft.c:37` | `#define MC_CHUNKS` |
| `MC_CHUNK_MAGIC` | macro | `progs/minicraft/minicraft.c:55` | `#define MC_CHUNK_MAGIC` |
| `MC_CHUNK_VERSION` | macro | `progs/minicraft/minicraft.c:56` | `#define MC_CHUNK_VERSION` |
| `MC_COLS` | macro | `progs/minicraft/minicraft.c:39` | `#define MC_COLS` |
| `MC_CREEPS_DEF` | macro | `progs/minicraft/minicraft.c:82` | `#define MC_CREEPS_DEF` |
| `MC_CREEPS_MAX` | macro | `progs/minicraft/minicraft.c:81` | `#define MC_CREEPS_MAX` |
| `MC_CREEP_DEFUSE_D` | macro | `progs/minicraft/minicraft.c:91` | `#define MC_CREEP_DEFUSE_D` |
| `MC_CREEP_DZ_MAX` | macro | `progs/minicraft/minicraft.c:89` | `#define MC_CREEP_DZ_MAX` |
| `MC_CREEP_FUSE_D` | macro | `progs/minicraft/minicraft.c:90` | `#define MC_CREEP_FUSE_D` |
| `MC_CREEP_HP` | macro | `progs/minicraft/minicraft.c:83` | `#define MC_CREEP_HP` |
| `MC_CREEP_NIGHT_MS` | macro | `progs/minicraft/minicraft.c:99` | `#define MC_CREEP_NIGHT_MS` |
| `MC_CREEP_SENSE` | macro | `progs/minicraft/minicraft.c:88` | `#define MC_CREEP_SENSE` |
| `MC_CREEP_SEP_D` | macro | `progs/minicraft/minicraft.c:102` | `#define MC_CREEP_SEP_D` |
| `MC_CVOL` | macro | `progs/minicraft/minicraft.c:38` | `#define MC_CVOL` |
| `MC_DAY_MS` | macro | `progs/minicraft/minicraft.c:108` | `#define MC_DAY_MS` |
| `MC_DDA_STEPS` | macro | `progs/minicraft/minicraft.c:69` | `#define MC_DDA_STEPS` |
| `MC_EYE` | macro | `progs/minicraft/minicraft.c:59` | `#define MC_EYE` |
| `MC_FLY_SPEED` | macro | `progs/minicraft/minicraft.c:64` | `#define MC_FLY_SPEED` |
| `MC_FUSE_MS` | macro | `progs/minicraft/minicraft.c:84` | `#define MC_FUSE_MS` |
| `MC_GRAV` | macro | `progs/minicraft/minicraft.c:60` | `#define MC_GRAV` |
| `MC_H` | macro | `progs/minicraft/minicraft.c:34` | `#define MC_H` |
| `MC_HP_MAX` | macro | `progs/minicraft/minicraft.c:79` | `#define MC_HP_MAX` |
| `MC_HUNGER_MAX` | macro | `progs/minicraft/minicraft.c:104` | `#define MC_HUNGER_MAX` |
| `MC_HUNGER_MS` | macro | `progs/minicraft/minicraft.c:105` | `#define MC_HUNGER_MS` |
| `MC_H_BASE` | macro | `progs/minicraft/minicraft.c:111` | `#define MC_H_BASE` |
| `MC_H_WT_COARSE` | macro | `progs/minicraft/minicraft.c:114` | `#define MC_H_WT_COARSE` |
| `MC_H_WT_DET` | macro | `progs/minicraft/minicraft.c:112` | `#define MC_H_WT_DET` |
| `MC_H_WT_MID` | macro | `progs/minicraft/minicraft.c:113` | `#define MC_H_WT_MID` |
| `MC_INV_MAX` | macro | `progs/minicraft/minicraft.c:76` | `#define MC_INV_MAX` |
| `MC_JUMP` | macro | `progs/minicraft/minicraft.c:61` | `#define MC_JUMP` |
| `MC_KBD_SEQ_SPINS` | macro | `progs/minicraft/minicraft.c:145` | `#define MC_KBD_SEQ_SPINS` |
| `MC_LEGACY_WORLD` | macro | `progs/minicraft/minicraft.c:2916` | `#define MC_LEGACY_WORLD` |
| `MC_LOAD_R` | macro | `progs/minicraft/minicraft.c:36` | `#define MC_LOAD_R` |
| `MC_MAXFALL` | macro | `progs/minicraft/minicraft.c:62` | `#define MC_MAXFALL` |
| `MC_MOUSE` | macro | `progs/minicraft/minicraft.c:66` | `#define MC_MOUSE` |
| `MC_NIGHT_LIGHT` | macro | `progs/minicraft/minicraft.c:101` | `#define MC_NIGHT_LIGHT` |
| `MC_PIGS` | macro | `progs/minicraft/minicraft.c:80` | `#define MC_PIGS` |
| `MC_PIG_DAY_MS` | macro | `progs/minicraft/minicraft.c:100` | `#define MC_PIG_DAY_MS` |
| `MC_PIG_HP` | macro | `progs/minicraft/minicraft.c:106` | `#define MC_PIG_HP` |
| `MC_PIG_HURT_MS` | macro | `progs/minicraft/minicraft.c:107` | `#define MC_PIG_HURT_MS` |
| `MC_PITCH_MAX` | macro | `progs/minicraft/minicraft.c:77` | `#define MC_PITCH_MAX` |
| `MC_PLACE_MS` | macro | `progs/minicraft/minicraft.c:72` | `#define MC_PLACE_MS` |
| `MC_PORK_HEAL` | macro | `progs/minicraft/minicraft.c:103` | `#define MC_PORK_HEAL` |
| `MC_REACH` | macro | `progs/minicraft/minicraft.c:67` | `#define MC_REACH` |
| `MC_RESPAWN_MS` | macro | `progs/minicraft/minicraft.c:98` | `#define MC_RESPAWN_MS` |
| `MC_SAVE_CRC_SEED` | macro | `progs/minicraft/minicraft.c:54` | `#define MC_SAVE_CRC_SEED` |
| `MC_SAVE_MAGIC` | macro | `progs/minicraft/minicraft.c:52` | `#define MC_SAVE_MAGIC` |
| `MC_SAVE_SECS` | macro | `progs/minicraft/minicraft.c:109` | `#define MC_SAVE_SECS` |
| `MC_SAVE_VERSION` | macro | `progs/minicraft/minicraft.c:53` | `#define MC_SAVE_VERSION` |
| `MC_SEED_MAX` | macro | `progs/minicraft/minicraft.c:144` | `#define MC_SEED_MAX` |
| `MC_SPEED` | macro | `progs/minicraft/minicraft.c:63` | `#define MC_SPEED` |
| `MC_SPRINT` | macro | `progs/minicraft/minicraft.c:65` | `#define MC_SPRINT` |
| `MC_VIEW` | macro | `progs/minicraft/minicraft.c:68` | `#define MC_VIEW` |
| `MC_VORO_DESERT_CELL` | macro | `progs/minicraft/minicraft.c:858` | `#define MC_VORO_DESERT_CELL` |
| `MC_VORO_SNOW_CELL` | macro | `progs/minicraft/minicraft.c:859` | `#define MC_VORO_SNOW_CELL` |
| `MC_WATER_GRAV` | macro | `progs/minicraft/minicraft.c:73` | `#define MC_WATER_GRAV` |
| `MC_WATER_SINK` | macro | `progs/minicraft/minicraft.c:74` | `#define MC_WATER_SINK` |
| `MC_WATER_SWIM` | macro | `progs/minicraft/minicraft.c:75` | `#define MC_WATER_SWIM` |
| `MOB_CREEP` | macro | `progs/minicraft/minicraft.c:309` | `#define MOB_CREEP` |
| `MOB_PIG` | macro | `progs/minicraft/minicraft.c:308` | `#define MOB_PIG` |
| `Pig` | struct | `progs/minicraft/minicraft.c:295` | `` |
| `RayHit` | struct | `progs/minicraft/minicraft.c:1650` | `` |
| `Recipe` | struct | `progs/minicraft/minicraft.c:216` | `` |
| `SAVE_PATH` | macro | `progs/minicraft/minicraft.c:50` | `#define SAVE_PATH` |
| `SAVE_TMP_PATH` | macro | `progs/minicraft/minicraft.c:51` | `#define SAVE_TMP_PATH` |
| `SC_0` | macro | `progs/minicraft/minicraft.c:143` | `#define SC_0` |
| `SC_1` | macro | `progs/minicraft/minicraft.c:118` | `#define SC_1` |
| `SC_9` | macro | `progs/minicraft/minicraft.c:119` | `#define SC_9` |
| `SC_A` | macro | `progs/minicraft/minicraft.c:130` | `#define SC_A` |
| `SC_B` | macro | `progs/minicraft/minicraft.c:139` | `#define SC_B` |
| `SC_BACK` | macro | `progs/minicraft/minicraft.c:142` | `#define SC_BACK` |
| `SC_C` | macro | `progs/minicraft/minicraft.c:137` | `#define SC_C` |
| `SC_CTRL` | macro | `progs/minicraft/minicraft.c:149` | `#define SC_CTRL` |
| `SC_D` | macro | `progs/minicraft/minicraft.c:132` | `#define SC_D` |
| `SC_E` | macro | `progs/minicraft/minicraft.c:122` | `#define SC_E` |
| `SC_ENTER` | macro | `progs/minicraft/minicraft.c:141` | `#define SC_ENTER` |
| `SC_ESC` | macro | `progs/minicraft/minicraft.c:117` | `#define SC_ESC` |
| `SC_F` | macro | `progs/minicraft/minicraft.c:133` | `#define SC_F` |
| `SC_G` | macro | `progs/minicraft/minicraft.c:134` | `#define SC_G` |
| `SC_I` | macro | `progs/minicraft/minicraft.c:126` | `#define SC_I` |
| `SC_J` | macro | `progs/minicraft/minicraft.c:129` | `#define SC_J` |
| `SC_K` | macro | `progs/minicraft/minicraft.c:135` | `#define SC_K` |
| `SC_L` | macro | `progs/minicraft/minicraft.c:136` | `#define SC_L` |
| `SC_LSHIFT` | macro | `progs/minicraft/minicraft.c:147` | `#define SC_LSHIFT` |
| `SC_N` | macro | `progs/minicraft/minicraft.c:140` | `#define SC_N` |
| `SC_O` | macro | `progs/minicraft/minicraft.c:127` | `#define SC_O` |
| `SC_P` | macro | `progs/minicraft/minicraft.c:128` | `#define SC_P` |
| `SC_Q` | macro | `progs/minicraft/minicraft.c:120` | `#define SC_Q` |
| `SC_R` | macro | `progs/minicraft/minicraft.c:123` | `#define SC_R` |
| `SC_RSHIFT` | macro | `progs/minicraft/minicraft.c:148` | `#define SC_RSHIFT` |
| `SC_S` | macro | `progs/minicraft/minicraft.c:131` | `#define SC_S` |
| `SC_SPACE` | macro | `progs/minicraft/minicraft.c:146` | `#define SC_SPACE` |
| `SC_T` | macro | `progs/minicraft/minicraft.c:124` | `#define SC_T` |
| `SC_U` | macro | `progs/minicraft/minicraft.c:125` | `#define SC_U` |
| `SC_V` | macro | `progs/minicraft/minicraft.c:138` | `#define SC_V` |
| `SC_W` | macro | `progs/minicraft/minicraft.c:121` | `#define SC_W` |
| `SER_STASH_CAP` | macro | `progs/minicraft/minicraft.c:369` | `#define SER_STASH_CAP` |
| `SaveHeader` | struct | `progs/minicraft/minicraft.c:2892` | `` |
| `SaveHeaderV3` | struct | `progs/minicraft/minicraft.c:2878` | `` |
| `__attribute__` | function | `progs/minicraft/minicraft.c:473` | `static long __attribute__((unused)) s_tone(long f)` |
| `beep` | function | `progs/minicraft/minicraft.c:478` | `static void beep(long freq, long dur_ms)` |
| `best_tool_for` | function | `progs/minicraft/minicraft.c:231` | `static int best_tool_for(unsigned char b)` |
| `biome_desert` | function | `progs/minicraft/minicraft.c:893` | `static int biome_desert(int x, int y, unsigned int seed)` |
| `biome_fdiv` | function | `progs/minicraft/minicraft.c:846` | `static int biome_fdiv(int v, int c)` |
| `biome_snow` | function | `progs/minicraft/minicraft.c:897` | `static int biome_snow(int x, int y, unsigned int seed)` |
| `biome_voro` | function | `progs/minicraft/minicraft.c:869` | `static int biome_voro(int x, int y, unsigned int seed, int cell,     int ox, int oy, unsigned int...` |
| `block_intersects_player` | function | `progs/minicraft/minicraft.c:2404` | `static int block_intersects_player(int bx, int by, int bz)` |
| `break_beep_for` | function | `progs/minicraft/minicraft.c:275` | `static long break_beep_for(unsigned char b)` |
| `break_time_ms` | function | `progs/minicraft/minicraft.c:250` | `static long break_time_ms(unsigned char b, int tool)` |
| `build_palette` | function | `progs/minicraft/minicraft.c:503` | `static void build_palette(void)` |
| `cam_build` | function | `progs/minicraft/minicraft.c:1892` | `static void cam_build(void)` |
| `carve_blob` | function | `progs/minicraft/minicraft.c:3108` | `static void carve_blob(const unsigned char *blob)` |
| `cast_ray` | function | `progs/minicraft/minicraft.c:1659` | `static RayHit cast_ray(float ox, float oy, float oz, float dx, float dy, float dz, float maxd)` |
| `census` | function | `progs/minicraft/minicraft.c:3606` | `static int census(void)` |
| `chunk_build_meta` | function | `progs/minicraft/minicraft.c:658` | `static void chunk_build_meta(int slot)` |
| `chunk_ensure` | function | `progs/minicraft/minicraft.c:635` | `static int chunk_ensure(int cx, int cy)` |
| `chunk_evict_slot` | function | `progs/minicraft/minicraft.c:615` | `static int chunk_evict_slot(int cx, int cy)` |
| `chunk_find` | function | `progs/minicraft/minicraft.c:592` | `static int chunk_find(int cx, int cy)` |
| `chunk_lidx` | function | `progs/minicraft/minicraft.c:586` | `static int chunk_lidx(int lx, int ly, int z)` |
| `chunk_local` | function | `progs/minicraft/minicraft.c:581` | `static int chunk_local(int v)` |
| `chunk_of` | function | `progs/minicraft/minicraft.c:577` | `static int chunk_of(int v)` |
| `chunk_path` | function | `progs/minicraft/minicraft.c:2938` | `static void chunk_path(int cx, int cy, char *out, size_t n)` |
| `col_recompute` | function | `progs/minicraft/minicraft.c:703` | `static void col_recompute(int x, int y)` |
| `col_top_at` | function | `progs/minicraft/minicraft.c:728` | `static int col_top_at(int x, int y)` |
| `creep_has_los` | function | `progs/minicraft/minicraft.c:1337` | `static int creep_has_los(Pig *c)` |
| `creep_sense` | function | `progs/minicraft/minicraft.c:1325` | `static void creep_sense(Pig *c, float *pdx, float *pdy, float *pdz, float *pd3)` |
| `creep_separate` | function | `progs/minicraft/minicraft.c:1361` | `static void creep_separate(Pig *p, int id, float dt)` |
| `creeper_explode` | function | `progs/minicraft/minicraft.c:1257` | `static void creeper_explode(Pig *c, long now)` |
| `decorate_chunk` | function | `progs/minicraft/minicraft.c:1043` | `static void decorate_chunk(int slot)` |
| `decorate_column` | function | `progs/minicraft/minicraft.c:995` | `static void decorate_column(int x, int y, unsigned int seed)` |
| `dumpstats` | function | `progs/minicraft/minicraft.c:3670` | `static int dumpstats(void)` |
| `ensure_around` | function | `progs/minicraft/minicraft.c:1090` | `static void ensure_around(void)` |
| `ensure_around_px` | function | `progs/minicraft/minicraft.c:1056` | `static void ensure_around_px(float px, float py)` |
| `eye_z` | function | `progs/minicraft/minicraft.c:1750` | `static float eye_z(void)` |
| `face_color` | function | `progs/minicraft/minicraft.c:1520` | `static unsigned char face_color(unsigned char b, int face)` |
| `gen_terrain_chunk` | function | `progs/minicraft/minicraft.c:1034` | `static void gen_terrain_chunk(int slot)` |
| `get_b` | function | `progs/minicraft/minicraft.c:764` | `static unsigned char get_b(int x, int y, int z)` |
| `goal_text` | function | `progs/minicraft/minicraft.c:2608` | `static const char *goal_text(void)` |
| `ground_h_seed` | function | `progs/minicraft/minicraft.c:909` | `static int ground_h_seed(int x, int y, unsigned int seed)` |
| `hash2` | function | `progs/minicraft/minicraft.c:823` | `static unsigned int hash2(int x, int y)` |
| `hash2_seed` | function | `progs/minicraft/minicraft.c:830` | `static unsigned int hash2_seed(int x, int y, unsigned int seed)` |
| `hurt` | function | `progs/minicraft/minicraft.c:2424` | `static void hurt(int dmg, const char *why)` |
| `in_water_at` | function | `progs/minicraft/minicraft.c:814` | `static int in_water_at(float x, float y, float z)` |
| `in_world` | function | `progs/minicraft/minicraft.c:562` | `static int in_world(int x, int y, int z)` |
| `inv_add` | function | `progs/minicraft/minicraft.c:931` | `static int inv_add(int b, int n)` |
| `inv_remove` | function | `progs/minicraft/minicraft.c:945` | `static int inv_remove(int b, int n)` |
| `is_cave` | function | `progs/minicraft/minicraft.c:901` | `static int is_cave(int x, int y, int z, unsigned int seed)` |
| `is_solid` | function | `progs/minicraft/minicraft.c:811` | `static int is_solid(unsigned char b)` |
| `is_visible` | function | `progs/minicraft/minicraft.c:819` | `static int is_visible(unsigned char b)` |
| `kbd_drain` | function | `progs/minicraft/minicraft.c:428` | `static void kbd_drain(void)` |
| `light_recompute_col` | function | `progs/minicraft/minicraft.c:735` | `static void light_recompute_col(int x, int y)` |
| `load_apply_player` | function | `progs/minicraft/minicraft.c:3175` | `static void load_apply_player(const SaveHeader *hd)` |
| `load_chunk_file` | function | `progs/minicraft/minicraft.c:2974` | `static int load_chunk_file(int slot, int cx, int cy)` |
| `load_reset_runtime` | function | `progs/minicraft/minicraft.c:3075` | `static void load_reset_runtime(void)` |
| `load_world` | function | `progs/minicraft/minicraft.c:3271` | `static int load_world(void)` |
| `load_world_legacy` | function | `progs/minicraft/minicraft.c:3137` | `static int load_world_legacy(FILE *f)` |
| `load_world_v2` | function | `progs/minicraft/minicraft.c:3234` | `static int load_world_v2(FILE *f, SaveHeader *hd)` |
| `load_world_v3` | function | `progs/minicraft/minicraft.c:3194` | `static int load_world_v3(FILE *f, SaveHeader *hd)` |
| `main` | function | `progs/minicraft/minicraft.c:4095` | `int main(int argc, char **argv)` |
| `mc_block_name` | function | `progs/minicraft/minicraft.c:1857` | `static const char *mc_block_name(unsigned char b)` |
| `mc_crc32` | function | `progs/minicraft/minicraft.c:2919` | `static uint32_t mc_crc32(const void *data, size_t len, uint32_t crc)` |
| `mc_facing` | function | `progs/minicraft/minicraft.c:1877` | `static char mc_facing(void)` |
| `mc_glyph` | function | `progs/minicraft/minicraft.c:1817` | `static int mc_glyph(char ch)` |
| `mc_pixel` | function | `progs/minicraft/minicraft.c:1825` | `static void mc_pixel(int x, int y, unsigned char c)` |
| `mc_smoothstep` | function | `progs/minicraft/minicraft.c:839` | `static float mc_smoothstep(float t)` |
| `mc_text` | function | `progs/minicraft/minicraft.c:1831` | `static void mc_text(int x, int y, const char *s, unsigned char fg)` |
| `mc_text_bg` | function | `progs/minicraft/minicraft.c:1844` | `static void mc_text_bg(int x, int y, const char *s, unsigned char fg, unsigned char bg)` |
| `mc_toggle_zoom` | function | `progs/minicraft/minicraft.c:316` | `static void mc_toggle_zoom(void)` |
| `menu_ser_key` | function | `progs/minicraft/minicraft.c:391` | `static long menu_ser_key(long b)` |
| `mob_pixel` | function | `progs/minicraft/minicraft.c:1945` | `static unsigned char mob_pixel(Pig *m, int id, int px, int py, int x0, int x1, int y0, int y1)` |
| `mob_spawn_one` | function | `progs/minicraft/minicraft.c:1191` | `static void mob_spawn_one(Pig *m, int id, int hp, long now)` |
| `move_x` | function | `progs/minicraft/minicraft.c:2379` | `static void move_x(float nx)` |
| `move_y` | function | `progs/minicraft/minicraft.c:2384` | `static void move_y(float ny)` |
| `move_z_abs` | function | `progs/minicraft/minicraft.c:2389` | `static MoveResult move_z_abs(float nz)` |
| `new_world` | function | `progs/minicraft/minicraft.c:1095` | `static void new_world(unsigned int seed)` |
| `pal_set` | function | `progs/minicraft/minicraft.c:497` | `static void pal_set(int i, int r, int g, int b)` |
| `pause_menu` | function | `progs/minicraft/minicraft.c:3922` | `static int pause_menu(int *seed_io)` |
| `pig_collides` | function | `progs/minicraft/minicraft.c:1243` | `static int pig_collides(float x, float y, float z)` |
| `player_collides` | function | `progs/minicraft/minicraft.c:2355` | `static int player_collides(float x, float y, float z)` |
| `poll_kbd` | function | `progs/minicraft/minicraft.c:2162` | `static void poll_kbd(void)` |
| `render_frame` | function | `progs/minicraft/minicraft.c:2038` | `static void render_frame(void)` |
| `render_mob_array` | function | `progs/minicraft/minicraft.c:1979` | `static void render_mob_array(Pig *arr, int n, float fx, float fy, float fz,     float rx, float r...` |
| `render_pigs` | function | `progs/minicraft/minicraft.c:2030` | `static void render_pigs(float cyaw, float syaw, float cpit, float spit, float ez)` |
| `render_terrain` | function | `progs/minicraft/minicraft.c:1910` | `static void render_terrain(RayHit tgt, float cyaw, float syaw, float cpit,                       ...` |
| `s_getc_raw` | function | `progs/minicraft/minicraft.c:359` | `static long s_getc_raw(void)` |
| `s_kbd` | function | `progs/minicraft/minicraft.c:342` | `static long s_kbd(void)` |
| `s_kbd_raw` | function | `progs/minicraft/minicraft.c:347` | `static long s_kbd_raw(long on)` |
| `s_mouse` | function | `progs/minicraft/minicraft.c:453` | `static long s_mouse(int *m)` |
| `s_pal` | function | `progs/minicraft/minicraft.c:438` | `static long s_pal(const unsigned char *p)` |
| `s_pcspk_init` | function | `progs/minicraft/minicraft.c:468` | `static long s_pcspk_init(void)` |
| `s_present` | function | `progs/minicraft/minicraft.c:443` | `static long s_present(void)` |
| `s_time_ms` | function | `progs/minicraft/minicraft.c:337` | `static long s_time_ms(void)` |
| `s_title` | function | `progs/minicraft/minicraft.c:448` | `static long s_title(const char *t)` |
| `s_vga` | function | `progs/minicraft/minicraft.c:433` | `static long s_vga(long on)` |
| `s_yield` | function | `progs/minicraft/minicraft.c:463` | `static void s_yield(void)` |
| `s_zoom` | function | `progs/minicraft/minicraft.c:458` | `static long s_zoom(long on)` |
| `save_chunk_file` | function | `progs/minicraft/minicraft.c:2942` | `static int save_chunk_file(int slot)` |
| `save_compute_crc` | function | `progs/minicraft/minicraft.c:2932` | `static uint32_t save_compute_crc(const SaveHeader *hd)` |
| `save_validate_loaded` | function | `progs/minicraft/minicraft.c:3056` | `static int save_validate_loaded(void)` |
| `save_world` | function | `progs/minicraft/minicraft.c:330` | `static int save_world(void);` |
| `sc_hist_push` | function | `progs/minicraft/minicraft.c:2151` | `static void sc_hist_push(unsigned char b)` |
| `selftest` | function | `progs/minicraft/minicraft.c:3345` | `static int selftest(void)` |
| `ser_get` | function | `progs/minicraft/minicraft.c:373` | `static long ser_get(void)` |
| `ser_unget` | function | `progs/minicraft/minicraft.c:386` | `static void ser_unget(unsigned char b)` |
| `set_b` | function | `progs/minicraft/minicraft.c:774` | `static void set_b(int x, int y, int z, unsigned char b)` |
| `set_b_raw` | function | `progs/minicraft/minicraft.c:790` | `static void set_b_raw(int x, int y, int z, unsigned char b)` |
| `shade_block` | function | `progs/minicraft/minicraft.c:1602` | `static unsigned char shade_block(unsigned char b, int face, int bx, int by, int bz,              ...` |
| `sky_color` | function | `progs/minicraft/minicraft.c:1569` | `static unsigned char sky_color(float dz, float sun_dot, int x, int y, float tsec)` |
| `sky_light` | function | `progs/minicraft/minicraft.c:801` | `static float sky_light(int x, int y, int z)` |
| `tick_discover` | function | `progs/minicraft/minicraft.c:2630` | `static void tick_discover(long now)` |
| `tick_goals` | function | `progs/minicraft/minicraft.c:2619` | `static void tick_goals(void)` |
| `tick_hunger` | function | `progs/minicraft/minicraft.c:2596` | `static void tick_hunger(long now)` |
| `tick_interact` | function | `progs/minicraft/minicraft.c:2668` | `static void tick_interact(void)` |
| `tick_mob` | function | `progs/minicraft/minicraft.c:1386` | `static void tick_mob(Pig *p, int id, float dt, long now)` |
| `tick_pigs` | function | `progs/minicraft/minicraft.c:1512` | `static void tick_pigs(float dt, long now)` |
| `tick_player` | function | `progs/minicraft/minicraft.c:2449` | `static void tick_player(float dt)` |
| `tick_water` | function | `progs/minicraft/minicraft.c:2548` | `static void tick_water(long now)` |
| `title_menu` | function | `progs/minicraft/minicraft.c:3754` | `static int title_menu(int have_save, int *seed_io)` |
| `try_autostep` | function | `progs/minicraft/minicraft.c:2413` | `static void try_autostep(float tx, float ty)` |
| `voro_site` | function | `progs/minicraft/minicraft.c:861` | `static void voro_site(int cx, int cy, unsigned int seed, int cell,     int *sx, int *sy)` |
| `world_max_recompute` | function | `progs/minicraft/minicraft.c:606` | `static void world_max_recompute(void)` |
| `DOOM_BACKBUF_ADDR` | function | `progs/minios_abi.h:128` | `* * All three sit in the reserved tail above DOOM_BACKBUF_ADDR (the brk cap), * so a growing heap or mmap region can...` |
| `MINIOS_ABI_CHECKSUM` | macro | `progs/minios_abi.h:45` | `#define MINIOS_ABI_CHECKSUM` |
| `MINIOS_ABI_H` | macro | `progs/minios_abi.h:2` | `#define MINIOS_ABI_H` |
| `MINIOS_ABI_VERSION` | macro | `progs/minios_abi.h:41` | `#define MINIOS_ABI_VERSION` |
| `MINIOS_DEV_MMIO_VBASE` | macro | `progs/minios_abi.h:214` | `#define MINIOS_DEV_MMIO_VBASE` |
| `MINIOS_DOOM_BACKBUF_ADDR` | macro | `progs/minios_abi.h:135` | `#define MINIOS_DOOM_BACKBUF_ADDR` |
| `MINIOS_DOOM_H` | macro | `progs/minios_abi.h:137` | `#define MINIOS_DOOM_H` |
| `MINIOS_DOOM_W` | macro | `progs/minios_abi.h:136` | `#define MINIOS_DOOM_W` |
| `MINIOS_EABI_MISMATCH` | macro | `progs/minios_abi.h:440` | `#define MINIOS_EABI_MISMATCH` |
| `MINIOS_FB_ADDR` | macro | `progs/minios_abi.h:138` | `#define MINIOS_FB_ADDR` |
| `MINIOS_FB_HEIGHT_MAX` | macro | `progs/minios_abi.h:220` | `#define MINIOS_FB_HEIGHT_MAX` |
| `MINIOS_FB_WIDTH_MAX` | macro | `progs/minios_abi.h:219` | `#define MINIOS_FB_WIDTH_MAX` |
| `MINIOS_GFX_BUF_GAME` | macro | `progs/minios_abi.h:410` | `#define MINIOS_GFX_BUF_GAME` |
| `MINIOS_GFX_BUF_NK` | macro | `progs/minios_abi.h:411` | `#define MINIOS_GFX_BUF_NK` |
| `MINIOS_GFX_BUF_NK_RGB` | macro | `progs/minios_abi.h:412` | `#define MINIOS_GFX_BUF_NK_RGB` |
| `MINIOS_GFX_ZOOM_2X` | macro | `progs/minios_abi.h:423` | `#define MINIOS_GFX_ZOOM_2X` |
| `MINIOS_GFX_ZOOM_FULLSCREEN` | macro | `progs/minios_abi.h:424` | `#define MINIOS_GFX_ZOOM_FULLSCREEN` |
| `MINIOS_GFX_ZOOM_NATIVE` | macro | `progs/minios_abi.h:422` | `#define MINIOS_GFX_ZOOM_NATIVE` |
| `MINIOS_GFX_ZOOM_WINDOWED` | macro | `progs/minios_abi.h:425` | `#define MINIOS_GFX_ZOOM_WINDOWED` |
| `MINIOS_HEAP_BASE` | macro | `progs/minios_abi.h:172` | `#define MINIOS_HEAP_BASE` |
| `MINIOS_HEAP_SIZE` | macro | `progs/minios_abi.h:178` | `#define MINIOS_HEAP_SIZE` |
| `MINIOS_LDSO_BASE` | macro | `progs/minios_abi.h:156` | `#define MINIOS_LDSO_BASE` |
| `MINIOS_LDSO_END` | macro | `progs/minios_abi.h:158` | `#define MINIOS_LDSO_END` |
| `MINIOS_LDSO_SIZE` | macro | `progs/minios_abi.h:157` | `#define MINIOS_LDSO_SIZE` |
| `MINIOS_NK_BACKBUF_ADDR` | macro | `progs/minios_abi.h:139` | `#define MINIOS_NK_BACKBUF_ADDR` |
| `MINIOS_NK_H` | macro | `progs/minios_abi.h:141` | `#define MINIOS_NK_H` |
| `MINIOS_NK_RGB_ADDR` | macro | `progs/minios_abi.h:166` | `#define MINIOS_NK_RGB_ADDR` |
| `MINIOS_NK_RGB_BYTES` | macro | `progs/minios_abi.h:167` | `#define MINIOS_NK_RGB_BYTES` |
| `MINIOS_NK_W` | macro | `progs/minios_abi.h:140` | `#define MINIOS_NK_W` |
| `MINIOS_NOTE_NAME` | macro | `progs/minios_abi.h:453` | `#define MINIOS_NOTE_NAME` |
| `MINIOS_NOTE_PROCESS` | macro | `progs/minios_abi.h:454` | `#define MINIOS_NOTE_PROCESS` |
| `MINIOS_NOTE_SIGN` | macro | `progs/minios_abi.h:455` | `#define MINIOS_NOTE_SIGN` |
| `MINIOS_PCI_MMIO_SIZE` | macro | `progs/minios_abi.h:202` | `#define MINIOS_PCI_MMIO_SIZE` |
| `MINIOS_PCM2_FRAG` | macro | `progs/minios_abi.h:399` | `#define MINIOS_PCM2_FRAG` |
| `MINIOS_PCM2_NONBLOCK` | macro | `progs/minios_abi.h:394` | `#define MINIOS_PCM2_NONBLOCK` |
| `MINIOS_PCM2_RATE` | macro | `progs/minios_abi.h:398` | `#define MINIOS_PCM2_RATE` |
| `MINIOS_SYS_ACCESS` | macro | `progs/minios_abi.h:253` | `#define MINIOS_SYS_ACCESS` |
| `MINIOS_SYS_ARCH_PRCTL` | macro | `progs/minios_abi.h:280` | `#define MINIOS_SYS_ARCH_PRCTL` |
| `MINIOS_SYS_BRK` | macro | `progs/minios_abi.h:248` | `#define MINIOS_SYS_BRK` |
| `MINIOS_SYS_CLIP_GET` | macro | `progs/minios_abi.h:376` | `#define MINIOS_SYS_CLIP_GET` |
| `MINIOS_SYS_CLIP_SET` | macro | `progs/minios_abi.h:375` | `#define MINIOS_SYS_CLIP_SET` |
| `MINIOS_SYS_CLOCK_GETTIME` | macro | `progs/minios_abi.h:298` | `#define MINIOS_SYS_CLOCK_GETTIME` |
| `MINIOS_SYS_CLONE` | macro | `progs/minios_abi.h:401` | `#define MINIOS_SYS_CLONE` |
| `MINIOS_SYS_CLOSE` | macro | `progs/minios_abi.h:241` | `#define MINIOS_SYS_CLOSE` |
| `MINIOS_SYS_CONNECT` | macro | `progs/minios_abi.h:257` | `#define MINIOS_SYS_CONNECT` |
| `MINIOS_SYS_DIR_LIST` | macro | `progs/minios_abi.h:352` | `#define MINIOS_SYS_DIR_LIST` |
| `MINIOS_SYS_DNS` | macro | `progs/minios_abi.h:302` | `#define MINIOS_SYS_DNS` |
| `MINIOS_SYS_DOOM_FRAME` | macro | `progs/minios_abi.h:320` | `#define MINIOS_SYS_DOOM_FRAME` |
| `MINIOS_SYS_EXECVE` | macro | `progs/minios_abi.h:263` | `#define MINIOS_SYS_EXECVE` |
| `MINIOS_SYS_EXIT` | macro | `progs/minios_abi.h:264` | `#define MINIOS_SYS_EXIT` |
| `MINIOS_SYS_EXIT_GROUP` | macro | `progs/minios_abi.h:296` | `#define MINIOS_SYS_EXIT_GROUP` |
| `MINIOS_SYS_FB_INFO` | macro | `progs/minios_abi.h:322` | `#define MINIOS_SYS_FB_INFO` |
| `MINIOS_SYS_FDATASYNC` | macro | `progs/minios_abi.h:277` | `#define MINIOS_SYS_FDATASYNC` |
| `MINIOS_SYS_FLOCK` | macro | `progs/minios_abi.h:275` | `#define MINIOS_SYS_FLOCK` |
| `MINIOS_SYS_FORK` | macro | `progs/minios_abi.h:261` | `#define MINIOS_SYS_FORK` |
| `MINIOS_SYS_FRAMEBUFFER_COMMIT` | macro | `progs/minios_abi.h:413` | `#define MINIOS_SYS_FRAMEBUFFER_COMMIT` |
| `MINIOS_SYS_FSTAT` | macro | `progs/minios_abi.h:242` | `#define MINIOS_SYS_FSTAT` |
| `MINIOS_SYS_FSYNC` | macro | `progs/minios_abi.h:276` | `#define MINIOS_SYS_FSYNC` |
| `MINIOS_SYS_FUTEX_WAIT` | macro | `progs/minios_abi.h:344` | `#define MINIOS_SYS_FUTEX_WAIT` |
| `MINIOS_SYS_FUTEX_WAKE` | macro | `progs/minios_abi.h:345` | `#define MINIOS_SYS_FUTEX_WAKE` |
| `MINIOS_SYS_GETCWD` | macro | `progs/minios_abi.h:278` | `#define MINIOS_SYS_GETCWD` |
| `MINIOS_SYS_GETC_RAW` | macro | `progs/minios_abi.h:347` | `#define MINIOS_SYS_GETC_RAW` |
| `MINIOS_SYS_GETPID` | macro | `progs/minios_abi.h:255` | `#define MINIOS_SYS_GETPID` |
| `MINIOS_SYS_GETRANDOM` | macro | `progs/minios_abi.h:294` | `#define MINIOS_SYS_GETRANDOM` |
| `MINIOS_SYS_GETTID` | macro | `progs/minios_abi.h:271` | `#define MINIOS_SYS_GETTID` |
| `MINIOS_SYS_GETTIMEOFDAY` | macro | `progs/minios_abi.h:279` | `#define MINIOS_SYS_GETTIMEOFDAY` |
| `MINIOS_SYS_GFX_PRESENT` | macro | `progs/minios_abi.h:348` | `#define MINIOS_SYS_GFX_PRESENT` |
| `MINIOS_SYS_GFX_SET_TITLE` | macro | `progs/minios_abi.h:335` | `#define MINIOS_SYS_GFX_SET_TITLE` |
| `MINIOS_SYS_GFX_ZOOM` | macro | `progs/minios_abi.h:353` | `#define MINIOS_SYS_GFX_ZOOM` |
| `MINIOS_SYS_IOCTL` | macro | `progs/minios_abi.h:251` | `#define MINIOS_SYS_IOCTL` |
| `MINIOS_SYS_KBD` | macro | `progs/minios_abi.h:314` | `#define MINIOS_SYS_KBD` |
| `MINIOS_SYS_KBD_RAW` | macro | `progs/minios_abi.h:316` | `#define MINIOS_SYS_KBD_RAW` |
| `MINIOS_SYS_KILL` | macro | `progs/minios_abi.h:266` | `#define MINIOS_SYS_KILL` |
| `MINIOS_SYS_LSEEK` | macro | `progs/minios_abi.h:244` | `#define MINIOS_SYS_LSEEK` |
| `MINIOS_SYS_LZ4_COMPRESS` | macro | `progs/minios_abi.h:325` | `#define MINIOS_SYS_LZ4_COMPRESS` |
| `MINIOS_SYS_LZ4_DECOMPRESS` | macro | `progs/minios_abi.h:330` | `#define MINIOS_SYS_LZ4_DECOMPRESS` |
| `MINIOS_SYS_MINFO` | macro | `progs/minios_abi.h:393` | `#define MINIOS_SYS_MINFO` |
| `MINIOS_SYS_MMAP` | macro | `progs/minios_abi.h:245` | `#define MINIOS_SYS_MMAP` |
| `MINIOS_SYS_MOUSE` | macro | `progs/minios_abi.h:331` | `#define MINIOS_SYS_MOUSE` |
| `MINIOS_SYS_MPROTECT` | macro | `progs/minios_abi.h:246` | `#define MINIOS_SYS_MPROTECT` |
| `MINIOS_SYS_MUNMAP` | macro | `progs/minios_abi.h:247` | `#define MINIOS_SYS_MUNMAP` |
| `MINIOS_SYS_NEWFSTATAT` | macro | `progs/minios_abi.h:282` | `#define MINIOS_SYS_NEWFSTATAT` |
| `MINIOS_SYS_NICE` | macro | `progs/minios_abi.h:350` | `#define MINIOS_SYS_NICE` |
| `MINIOS_SYS_NK_FRAME` | macro | `progs/minios_abi.h:332` | `#define MINIOS_SYS_NK_FRAME` |
| `MINIOS_SYS_OPEN` | macro | `progs/minios_abi.h:240` | `#define MINIOS_SYS_OPEN` |
| `MINIOS_SYS_OPENAT` | macro | `progs/minios_abi.h:281` | `#define MINIOS_SYS_OPENAT` |

Next: [SYMBOLS_p21.md](SYMBOLS_p21.md)
