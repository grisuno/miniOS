# Subsystem: src

## progs/src/aes.c
- Layer: utility
- Doc: aes.c - command path AES-256-CTR encryption tools: aes and unaes.
- Language: c
- Symbols:
  - `aes_read_all` (function, line 68) `static char *aes_read_all(const char *name, int *len)`
  - `aes_write_all` (function, line 85) `static int aes_write_all(const char *name, char *data, int len)`
  - `aes_has` (function, line 95) `static int aes_has(const char *s, const char *needle)`
  - `hex_val` (function, line 109) `static int hex_val(int c)`
  - `aes_parse_hex` (function, line 116) `static int aes_parse_hex(const char *s, int want, int *out)`
  - `aes_gf_mul` (function, line 130) `static int aes_gf_mul(int a, int b)`
  - `aes_xtime` (function, line 141) `static int aes_xtime(int x)`
  - `aes_rotl8` (function, line 147) `static int aes_rotl8(int x, int n)`
  - `aes_init_tables` (function, line 155) `static void aes_init_tables(void)`
  - `aes_key_expand` (function, line 174) `static void aes_key_expand(const int *key)`
  - `aes_add_round_key` (function, line 208) `static void aes_add_round_key(int round)`
  - `aes_sub_bytes` (function, line 214) `static void aes_sub_bytes(void)`
  - `aes_shift_rows` (function, line 219) `static void aes_shift_rows(void)`
  - `aes_mix_columns` (function, line 227) `static void aes_mix_columns(void)`
  - `aes_cipher` (function, line 247) `static void aes_cipher(void)`
  - `aes_iv_increment` (function, line 263) `static void aes_iv_increment(void)`
  - `aes_ctr_crypt` (function, line 273) `static void aes_ctr_crypt(char *data, int len)`
  - `aes_hdr_put` (function, line 287) `static void aes_hdr_put(char *h, int size)`
  - `aes_hdr_get` (function, line 298) `static int aes_hdr_get(char *h)`
  - `aes_tool_name` (function, line 306) `static const char *aes_tool_name(int decode)`
  - `aes_run` (function, line 311) `static int aes_run(int decode, const char *keyhex, const char *noncehex,
                   const...`
  - `main` (function, line 383) `int main(int argc, char **argv)`
  - `AES_MAGIC0` (macro, line 37)
  - `AES_MAGIC1` (macro, line 39)
  - `AES_MAGIC2` (macro, line 40)
  - `AES_MAGIC3` (macro, line 41)
  - `AES_HDR_SIZE` (macro, line 42)
  - `AES_BLOCK` (macro, line 43)
  - `AES_KEY_BYTES` (macro, line 45)
  - `AES_NONCE_BYTES` (macro, line 46)
  - `AES_ROUNDS` (macro, line 47)
  - `AES_RK_LEN` (macro, line 48)
  - `AES_SBOX_SIZE` (macro, line 49)
  - `AES_RCON_SIZE` (macro, line 50)
  - `AES_POLY` (macro, line 51)
  - `AES_AFFINE_C` (macro, line 53)
  - `AES_RCON_PAD` (macro, line 54)
  - `HEX_KEY_LEN` (macro, line 55)
  - `HEX_NONCE_LEN` (macro, line 57)
  - `AES_SEEK_END` (macro, line 58)
  - `AES_EXIT_FAIL` (macro, line 60)

## progs/src/audio.c
- Layer: infrastructure
- Doc: include "minios_abi.h"
- Language: c
- Symbols:
  - `syscall1` (function, line 2) `static long syscall1(long n, long a1)`
  - `syscall2` (function, line 8) `static long syscall2(long n, long a1, long a2)`
  - `syscall3` (function, line 14) `static long syscall3(long n, long a1, long a2, long a3)`
  - `syscall0` (function, line 20) `static long syscall0(long n)`
  - `audio_init` (function, line 26) `int audio_init(void)`
  - `audio_tone` (function, line 30) `void audio_tone(unsigned freq)`
  - `audio_pcm_open` (function, line 34) `int audio_pcm_open(unsigned rate, unsigned channels, unsigned format)`
  - `audio_pcm_submit` (function, line 39) `int audio_pcm_submit(const void *buf, unsigned len)`
  - `audio_pcm_pump` (function, line 43) `void audio_pcm_pump(void)`
  - `audio_pcm_close` (function, line 47) `void audio_pcm_close(void)`
  - `audio_set_volume` (function, line 51) `void audio_set_volume(unsigned volume)`
  - `audio_get_volume` (function, line 55) `unsigned audio_get_volume(void)`
  - `audio_sb16_present` (function, line 59) `int audio_sb16_present(void)`
  - `audio_stream_open` (function, line 63) `int audio_stream_open(void)`
  - `audio_stream_close` (function, line 67) `void audio_stream_close(int id)`
  - `audio_stream_submit` (function, line 71) `int audio_stream_submit(int id, const void *buf, unsigned len)`
  - `audio_stream_volume` (function, line 75) `void audio_stream_volume(int id, unsigned char vol)`

## progs/src/cp.c
- Layer: utility
- Language: c
- Symbols:
  - `main` (function, line 9) `int main(int argc, char **argv)`
  - `CP_BUF_SIZE` (macro, line 6)
  - `CP_EXIT_FAIL` (macro, line 8)

## progs/src/cpl.c
- Layer: utility
- Doc: Ring-3 privilege probe. Reads the CS selector at runtime and exits with
- Language: c
- Symbols:
  - `read_cpl` (function, line 6) `static long read_cpl(void)`
  - `exit_now` (function, line 11) `static void exit_now(long code)`
  - `_start` (function, line 15) `void _start(void)`

## progs/src/fib.c
- Layer: utility
- Language: c
- Symbols:
  - `fib` (function, line 1) `int fib(int n)`
  - `main` (function, line 5) `int main(void)`

## progs/src/freedom.c
- Layer: utility
- Doc: freedom - a headless text browser for MiniOS.
- Language: c
- Symbols:
  - `atoi` (function, line 127) `static int atoi(char *s)`
  - `append` (function, line 140) `static int append(char *dst, int pos, char *src, int cap)`
  - `ci_lower` (function, line 148) `static int ci_lower(int c)`
  - `ci_starts` (function, line 155) `static int ci_starts(char *s, char *pre)`
  - `ci_eq` (function, line 166) `static int ci_eq(char *a, char *b)`
  - `ci_index` (function, line 176) `static int ci_index(char *s, char *needle)`
  - `looks_like_url` (function, line 185) `static int looks_like_url(char *s)`
  - `has_scheme` (function, line 199) `static int has_scheme(char *s)`
  - `make_search` (function, line 215) `static void make_search(char *out, char *query, int cap)`
  - `split_url` (function, line 239) `static int split_url(char *url)`
  - `resolve_redirect` (function, line 286) `static int resolve_redirect(void)`
  - `put_ws` (function, line 338) `static void put_ws(void)`
  - `put_utf` (function, line 350) `static void put_utf(int c)`
  - `put_text` (function, line 400) `static void put_text(int c)`
  - `css_append` (function, line 455) `static void css_append(char *s, int n)`
  - `css_line` (function, line 461) `static void css_line(char *s)`
  - `dom_append` (function, line 466) `static void dom_append(char *s, int n)`
  - `dom_space` (function, line 472) `static void dom_space(void)`
  - `dom_nl` (function, line 476) `static void dom_nl(void)`
  - `record_attr` (function, line 482) `static void record_attr(void)`
  - `is_void_tag` (function, line 507) `static int is_void_tag(void)`
  - `classify_tag` (function, line 519) `static void classify_tag(void)`
  - `body_byte` (function, line 604) `static void body_byte(int c)`
  - `head_line` (function, line 769) `static void head_line(char *line)`
  - `parse_head` (function, line 794) `static void parse_head(void)`
  - `recv_body` (function, line 816) `static int recv_body(int fd, char *buf, int len)`
  - `send_all` (function, line 822) `static int send_all(int fd, char *buf, int len)`
  - `fetch` (function, line 833) `static int fetch(char *host, char *path, int port)`
  - `fetch_css` (function, line 993) `static void fetch_css(char *host, char *path)`
  - `print_css_dump` (function, line 1071) `static void print_css_dump(void)`
  - `print_dom_dump` (function, line 1080) `static void print_dom_dump(void)`
  - `main` (function, line 1086) `int main(int argc, char **argv)`
  - `FREEDOM_HOPS_MAX` (macro, line 49)
  - `FREEDOM_HDR_MAX` (macro, line 51)
  - `FREEDOM_BUF` (macro, line 52)
  - `FREEDOM_CHUNK_MAX` (macro, line 53)
  - `FREEDOM_CSS_MAX` (macro, line 54)
  - `FREEDOM_CSS_BUF` (macro, line 55)
  - `FREEDOM_DOM_BUF` (macro, line 56)
  - `FREEDOM_ATTR_MAX` (macro, line 57)
  - `FREEDOM_LINE_MAX` (macro, line 58)

## progs/src/ftest.c
- Layer: testing
- Doc: Exercises the kernel libc surface used by loaded .o programs: fprintf to stdout/stderr, snprintf into a buffer, and exit
- Language: c
- Symbols:
  - `main` (function, line 9) `int main(int argc, char **argv)`

## progs/src/hello.c
- Layer: utility
- Doc: MiniOS test program — compiled as relocatable .o, loaded by kernel ELF loader
- Language: c
- Symbols:
  - `main` (function, line 3) `int main(int argc, char **argv)`

## progs/src/hello.py
- Layer: utility
- Language: py

## progs/src/http.c
- Layer: presentation
- Doc: Minimal HTTP/1.0 GET through the Linux socket syscalls.
- Language: c
- Symbols:
  - `atoi` (function, line 18) `int atoi(char *s)`
  - `main` (function, line 28) `int main(int argc, char **argv)`

## progs/src/json.c
- Layer: utility
- Doc: json.c - command path JSON tool: validate, pretty-print and query.
- Language: c
- Symbols:
  - `js_read_all` (function, line 57) `static char *js_read_all(const char *name, int *len)`
  - `js_new` (function, line 75) `static int js_new(void)`
  - `js_skip_ws` (function, line 80) `static void js_skip_ws(void)`
  - `js_peek` (function, line 88) `static int js_peek(void)`
  - `js_parse_string` (function, line 96) `static int js_parse_string(void)`
  - `js_parse_number` (function, line 132) `static int js_parse_number(void)`
  - `js_key_match` (function, line 142) `static int js_key_match(int child, const char *key)`
  - `js_parse_object` (function, line 146) `static int js_parse_object(void)`
  - `js_parse_array` (function, line 181) `static int js_parse_array(void)`
  - `js_parse_value` (function, line 210) `static int js_parse_value(void)`
  - `js_indent` (function, line 280) `static void js_indent(int n)`
  - `js_print_str` (function, line 285) `static void js_print_str(const char *s)`
  - `js_print_value` (function, line 302) `static void js_print_value(int node, int depth)`
  - `js_find_member` (function, line 346) `static int js_find_member(int obj, const char *key)`
  - `js_array_at` (function, line 356) `static int js_array_at(int arr, int idx)`
  - `js_query` (function, line 368) `static int js_query(int root, const char *path)`
  - `main` (function, line 400) `int main(int argc, char **argv)`
  - `JS_MAX_NODES` (macro, line 26)
  - `JS_POOL` (macro, line 28)
  - `JS_NULL` (macro, line 29)
  - `JS_BOOL` (macro, line 31)
  - `JS_NUM` (macro, line 32)
  - `JS_STR` (macro, line 33)
  - `JS_OBJ` (macro, line 34)
  - `JS_ARR` (macro, line 35)
  - `JS_SEEK_END` (macro, line 36)
  - `JS_EXIT_OK` (macro, line 38)
  - `JS_EXIT_FAIL` (macro, line 39)

## progs/src/kmem.c
- Layer: utility
- Doc: Kernel-pointer rejection probe. Passes a kernel-heap address (0x2000000,
- Language: c
- Symbols:
  - `syscall3` (function, line 6) `static long syscall3(long n, long a1, long a2, long a3)`
  - `exit_now` (function, line 12) `static void exit_now(long code)`
  - `_start` (function, line 16) `void _start(void)`

## progs/src/ldhello.c
- Layer: utility
- Language: c
- Symbols:
  - `main` (function, line 1) `int main(void)`

## progs/src/lxhello.c
- Layer: utility
- Language: c
- Symbols:
  - `lx_syscall3` (function, line 10) `static long lx_syscall3(long n, long a1, long a2, long a3)`
  - `lx_strlen` (function, line 22) `static unsigned long lx_strlen(const char *s)`
  - `lx_write` (function, line 28) `static void lx_write(const char *s)`
  - `lx_write_int` (function, line 32) `static void lx_write_int(long v)`
  - `lmain` (function, line 46) `int lmain(long argc, char **argv)`
  - `SYS_write` (macro, line 19)
  - `SYS_exit` (macro, line 21)

## progs/src/lz4.c
- Layer: utility
- Doc: lz4.c - command path LZ4 (de)compression tools: lz4 and unlz4.
- Language: c
- Symbols:
  - `lz4_has` (function, line 38) `static int lz4_has(const char *s, const char *needle)`
  - `lz4_read_all` (function, line 52) `static char *lz4_read_all(const char *name, int *len)`
  - `lz4_write_all` (function, line 69) `static int lz4_write_all(const char *name, char *data, int len)`
  - `lz4_compress_file` (function, line 79) `static int lz4_compress_file(const char *src, const char *dst)`
  - `lz4_decompress_file` (function, line 116) `static int lz4_decompress_file(const char *src, const char *dst)`
  - `main` (function, line 163) `int main(int argc, char **argv)`
  - `LZ4_HDR_SIZE` (macro, line 29)
  - `LZ4_BOUND_DEN` (macro, line 31)
  - `LZ4_BOUND_SLACK` (macro, line 32)
  - `LZ4_MAX_BLOCK` (macro, line 33)
  - `LZ4_SEEK_END` (macro, line 34)
  - `LZ4_EXIT_FAIL` (macro, line 36)

## progs/src/lzss.c
- Layer: utility
- Doc: lzss.c - command path LZSS (de)compression tools: lzss and unlzss.
- Language: c
- Symbols:
  - `lz_in_getc` (function, line 63) `static int lz_in_getc(void)`
  - `lz_out_put` (function, line 68) `static void lz_out_put(int c)`
  - `lz_putbit1` (function, line 73) `static void lz_putbit1(void)`
  - `lz_putbit0` (function, line 83) `static void lz_putbit0(void)`
  - `lz_flush_bits` (function, line 92) `static void lz_flush_bits(void)`
  - `lz_out_literal` (function, line 96) `static void lz_out_literal(int c)`
  - `lz_out_pair` (function, line 104) `static void lz_out_pair(int x, int y)`
  - `lz_encode` (function, line 115) `static int lz_encode(void)`
  - `lz_getbit` (function, line 160) `static int lz_getbit(int n)`
  - `lz_decode` (function, line 176) `static int lz_decode(void)`
  - `lz_hdr_put` (function, line 205) `static void lz_hdr_put(char *h, int size)`
  - `lz_hdr_get` (function, line 216) `static int lz_hdr_get(char *h)`
  - `lz_has` (function, line 224) `static int lz_has(const char *s, const char *needle)`
  - `lz_read_all` (function, line 238) `static char *lz_read_all(const char *name, int *len)`
  - `lz_write_all` (function, line 255) `static int lz_write_all(const char *name, char *data, int len)`
  - `lz_compress` (function, line 265) `static int lz_compress(const char *src, const char *dst)`
  - `lz_decompress` (function, line 312) `static int lz_decompress(const char *src, const char *dst)`
  - `main` (function, line 384) `int main(int argc, char **argv)`
  - `LZSS_EI` (macro, line 25)
  - `LZSS_EJ` (macro, line 27)
  - `LZSS_P` (macro, line 28)
  - `LZSS_N` (macro, line 29)
  - `LZSS_F` (macro, line 30)
  - `LZSS_WIN` (macro, line 31)
  - `LZSS_MAGIC0` (macro, line 32)
  - `LZSS_MAGIC1` (macro, line 34)
  - `LZSS_MAGIC2` (macro, line 35)
  - `LZSS_MAGIC3` (macro, line 36)
  - `LZSS_HDR_SIZE` (macro, line 37)
  - `LZSS_ENC_SLACK` (macro, line 38)
  - `LZSS_EXPAND_NUM` (macro, line 40)
  - `LZSS_EXPAND_DEN` (macro, line 41)
  - `LZSS_SEEK_END` (macro, line 42)
  - `LZSS_ERR_NONE` (macro, line 44)
  - `LZSS_ERR_OVERFLOW` (macro, line 46)
  - `LZSS_EXIT_FAIL` (macro, line 47)

## progs/src/mmreuse.c
- Layer: utility
- Doc: mmap/munmap reclaim stress test.  Repeatedly maps and unmaps a large
- Language: c
- Symbols:
  - `mmap_anon` (function, line 7) `static long mmap_anon(long len)`
  - `munmap` (function, line 20) `static long munmap(long addr, long len)`
  - `exit_now` (function, line 30) `static void exit_now(long code)`
  - `_start` (function, line 34) `void _start(void)`

## progs/src/nx.c
- Layer: utility
- Doc: NX probe. Under the isolation contract every user page starts
- Language: c
- Symbols:
  - `write_str` (function, line 10) `static long write_str(const char *s, long n)`
  - `exit_now` (function, line 18) `static void exit_now(long code)`
  - `_start` (function, line 22) `void _start(void)`

## progs/src/opl3.c
- Layer: utility
- Language: c
- Symbols:
  - `sys_time` (function, line 35) `static long sys_time(void)`
  - `sys_open` (function, line 39) `static long sys_open(long on)`
  - `sys_submit` (function, line 42) `static long sys_submit(const void *buf, long len)`
  - `busy_ms` (function, line 45) `static void busy_ms(long ms)`
  - `opl3_set_instrument` (function, line 52) `static void opl3_set_instrument(opl3_chip *chip)`
  - `opl3_note` (function, line 68) `static void opl3_note(opl3_chip *chip, unsigned block, unsigned fnum, int on)`
  - `render` (function, line 77) `static void render(opl3_chip *chip, long ms, long *fail)`
  - `main` (function, line 106) `int main(void)`
  - `SYS_TIME` (macro, line 20)
  - `SYS_SB16_OPEN` (macro, line 22)
  - `SYS_SB16_SUBMIT` (macro, line 23)
  - `SYS_WRITE` (macro, line 24)
  - `SAMPLE_RATE` (macro, line 27)
  - `STEREO_FRAMES` (macro, line 29)
  - `MONO_BYTES` (macro, line 30)
  - `BUF_MS` (macro, line 31)
  - `F_NUM_FACTOR` (macro, line 33)

## progs/src/sbtone.c
- Layer: utility
- Doc: sbtone.c — headless SB16 diagnostic (ring-3, no GUI).
- Language: c
- Symbols:
  - `buffers` (function, line 13) `*
 * Exit code is the number of submitted buffers (0 on failure to open).
 */

#include <stdio.h>...`
  - `main` (function, line 35) `int main(void)`
  - `SYS_SB16_OPEN` (macro, line 20)
  - `SYS_SB16_SUBMIT` (macro, line 22)
  - `SYS_TIME` (macro, line 23)
  - `RATE` (macro, line 24)
  - `BUF` (macro, line 26)
  - `WINDOW_MS` (macro, line 27)

## progs/src/shell.py
- Layer: utility
- Doc: shell.py -- pybash: a Python shell layer on top of MiniOS's C shell.  The C shell is untouched. This is an additional ca
- Language: py
- Symbols:
  - `run_capture` (function, line 20) `def run_capture(cmd, args)`
  - `expand` (function, line 30) `def expand(line, env)`
  - `main` (function, line 36) `def main()`
- Depends on: `progs/lua/minios.c`

## progs/src/test.c
- Layer: testing
- Language: c
- Symbols:
  - `add` (function, line 1) `int add(int a, int b)`
  - `main` (function, line 2) `int main(void)`

## progs/src/test.lua
- Layer: testing
- Language: lua
- Symbols:
  - `check` (function, line 12)
  - `write_file` (function, line 22)
  - `read_file` (function, line 30)
  - `test_module_bindings` (function, line 40)
  - `test_filesystem` (function, line 53)
  - `test_xxhash` (function, line 70)
  - `test_stb` (function, line 75)
  - `test_dlmalloc` (function, line 80)
  - `test_hello` (function, line 85)
  - `test_ftest` (function, line 90)
  - `test_minigcc` (function, line 95)
  - `test_ld` (function, line 100)
  - `test_toolchain_roundtrip` (function, line 112)
  - `test_spawn_preserves_interpreter` (function, line 122)
  - `test_bin_cp` (function, line 135)
  - `test_bin_lz4` (function, line 141)
  - `test_bin_lzss` (function, line 158)
  - `test_bin_aes` (function, line 175)
  - `test_bin_json` (function, line 194)
  - `test_bin_freedom` (function, line 205)

## progs/src/test.py
- Layer: testing
- Doc: test.py -- in-OS test suite for MiniOS, driven by MicroPython.  Tests every available binary sorted by size (smallest fi
- Language: py
- Symbols:
  - `check` (function, line 15) `def check(name, cond, detail)`
  - `safe_run` (function, line 25) `def safe_run()`
  - `test_module_bindings` (function, line 38) `def test_module_bindings()`
  - `test_filesystem` (function, line 56) `def test_filesystem()`
  - `test_xxhash` (function, line 72) `def test_xxhash()`
  - `test_stb` (function, line 77) `def test_stb()`
  - `test_dlmalloc` (function, line 82) `def test_dlmalloc()`
  - `test_hello` (function, line 87) `def test_hello()`
  - `test_ftest` (function, line 92) `def test_ftest()`
  - `test_minigcc` (function, line 97) `def test_minigcc()`
  - `test_ld` (function, line 102) `def test_ld()`
  - `test_toolchain_roundtrip` (function, line 119) `def test_toolchain_roundtrip()`
  - `test_spawn_preserves_interpreter` (function, line 134) `def test_spawn_preserves_interpreter()`
  - `test_bin_cp` (function, line 148) `def test_bin_cp()`
  - `test_bin_lz4` (function, line 153) `def test_bin_lz4()`
  - `test_bin_lzss` (function, line 181) `def test_bin_lzss()`
  - `test_bin_aes` (function, line 209) `def test_bin_aes()`
  - `test_bin_json` (function, line 239) `def test_bin_json()`
  - `test_bin_freedom` (function, line 253) `def test_bin_freedom()`
  - `main` (function, line 261) `def main()`
- Depends on: `progs/lua/minios.c`

## progs/src/test_all.sh
- Layer: testing
- Doc: test_all.sh -- comprehensive non-interactive test suite for MiniOS.  Run with:  sh src/test_all.sh  Every test prints a 
- Language: sh

## progs/src/w1.c
- Layer: utility
- Language: c
- Symbols:
  - `main` (function, line 2) `int main(void)`
