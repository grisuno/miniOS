# Subsystem: src (page 2 of 2)
Previous: [KB_src.md](KB_src.md)

## progs/src/lxhello.c
- Doc: lmain: static void lx_write_int(long v) { char buf[24]; int i = (int)sizeof(buf); int neg = 0...
- Layer: utility
- Language: c
- Symbols:
  - `lx_syscall3` (function, line 11) `static long lx_syscall3(long n, long a1, long a2, long a3)`
  - `lx_strlen` (function, line 23) `static unsigned long lx_strlen(const char *s)`
  - `lx_write` (function, line 29) `static void lx_write(const char *s)`
  - `lx_write_int` (function, line 33) `static void lx_write_int(long v)`
  - `lmain` (function, line 46) `int lmain(long argc, char **argv)`
  - `SYS_write` (macro, line 20) `#define SYS_write`
  - `SYS_exit` (macro, line 21) `#define SYS_exit`

## progs/src/lz4.c
- Doc: command path LZ4 (de)compression tools: lz4 and unlz4.
- Layer: utility
- Language: c
- Symbols:
  - `lz4_has` (function, line 39) `static int lz4_has(const char *s, const char *needle)`
  - `lz4_read_all` (function, line 53) `static char *lz4_read_all(const char *name, int *len)`
  - `lz4_write_all` (function, line 70) `static int lz4_write_all(const char *name, char *data, int len)`
  - `lz4_compress_file` (function, line 80) `static int lz4_compress_file(const char *src, const char *dst)`
  - `lz4_decompress_file` (function, line 117) `static int lz4_decompress_file(const char *src, const char *dst)`
  - `main` (function, line 164) `int main(int argc, char **argv)`
  - `kernel` (function, line 6) `* * The codec lives in the kernel (lz4_kernel.c, the same one MiniFS uses), so * these tools are thin front-ends...`
  - `free` (function, line 15) `void free();`
  - `printf` (function, line 16) `int printf();`
  - `strcmp` (function, line 17) `int strcmp();`
  - `strlen` (function, line 18) `int strlen();`
  - `fopen` (function, line 19) `void *fopen();`
  - `fclose` (function, line 20) `int fclose();`
  - `fread` (function, line 21) `int fread();`
  - `fwrite` (function, line 22) `int fwrite();`
  - `fseek` (function, line 23) `int fseek();`
  - `ftell` (function, line 24) `int ftell();`
  - `rewind` (function, line 25) `void rewind();`
  - `lz4_compress` (function, line 27) `int lz4_compress(char *src, int srclen, char *dst, int dstcap);`
  - `lz4_decompress` (function, line 28) `int lz4_decompress(char *src, int srclen, char *dst, int dstcap);`
  - `LZ4_HDR_SIZE` (macro, line 30) `#define LZ4_HDR_SIZE`
  - `LZ4_BOUND_DEN` (macro, line 31) `#define LZ4_BOUND_DEN`
  - `LZ4_BOUND_SLACK` (macro, line 32) `#define LZ4_BOUND_SLACK`
  - `LZ4_MAX_BLOCK` (macro, line 33) `#define LZ4_MAX_BLOCK`
  - `LZ4_SEEK_END` (macro, line 35) `#define LZ4_SEEK_END`
  - `LZ4_EXIT_FAIL` (macro, line 37) `#define LZ4_EXIT_FAIL`

## progs/src/lzss.c
- Doc: command path LZSS (de)compression tools: lzss and unlzss.
- Layer: utility
- Language: c
- Symbols:
  - `lz_in_getc` (function, line 64) `static int lz_in_getc(void)`
  - `lz_out_put` (function, line 69) `static void lz_out_put(int c)`
  - `lz_putbit1` (function, line 74) `static void lz_putbit1(void)`
  - `lz_putbit0` (function, line 84) `static void lz_putbit0(void)`
  - `lz_flush_bits` (function, line 93) `static void lz_flush_bits(void)`
  - `lz_out_literal` (function, line 97) `static void lz_out_literal(int c)`
  - `lz_out_pair` (function, line 105) `static void lz_out_pair(int x, int y)`
  - `lz_encode` (function, line 118) `static int lz_encode(void)`
  - `lz_getbit` (function, line 173) `static int lz_getbit(int n)`
  - `lz_decode` (function, line 189) `static int lz_decode(void)`
  - `lz_hdr_put` (function, line 218) `static void lz_hdr_put(char *h, int size)`
  - `lz_hdr_get` (function, line 229) `static int lz_hdr_get(char *h)`
  - `lz_has` (function, line 237) `static int lz_has(const char *s, const char *needle)`
  - `lz_read_all` (function, line 251) `static char *lz_read_all(const char *name, int *len)`
  - `lz_write_all` (function, line 268) `static int lz_write_all(const char *name, char *data, int len)`
  - `lz_compress` (function, line 278) `static int lz_compress(const char *src, const char *dst)`
  - `lz_decompress` (function, line 325) `static int lz_decompress(const char *src, const char *dst)`
  - `main` (function, line 397) `int main(int argc, char **argv)`
  - `malloc` (function, line 13) `void *malloc();`
  - `free` (function, line 14) `void free();`
  - `printf` (function, line 15) `int printf();`
  - `strcmp` (function, line 16) `int strcmp();`
  - `strlen` (function, line 17) `int strlen();`
  - `fopen` (function, line 18) `void *fopen();`
  - `fclose` (function, line 19) `int fclose();`
  - `fread` (function, line 20) `int fread();`
  - `fwrite` (function, line 21) `int fwrite();`
  - `fseek` (function, line 22) `int fseek();`
  - `ftell` (function, line 23) `int ftell();`
  - `rewind` (function, line 24) `void rewind();`
  - `LZSS_EI` (macro, line 26) `#define LZSS_EI`
  - `LZSS_EJ` (macro, line 27) `#define LZSS_EJ`
  - `LZSS_P` (macro, line 28) `#define LZSS_P`
  - `LZSS_N` (macro, line 29) `#define LZSS_N`
  - `LZSS_F` (macro, line 30) `#define LZSS_F`
  - `LZSS_WIN` (macro, line 31) `#define LZSS_WIN`
  - `LZSS_MAGIC0` (macro, line 33) `#define LZSS_MAGIC0`
  - `LZSS_MAGIC1` (macro, line 34) `#define LZSS_MAGIC1`
  - `LZSS_MAGIC2` (macro, line 35) `#define LZSS_MAGIC2`
  - `LZSS_MAGIC3` (macro, line 36) `#define LZSS_MAGIC3`
  - `LZSS_HDR_SIZE` (macro, line 37) `#define LZSS_HDR_SIZE`
  - `LZSS_ENC_SLACK` (macro, line 39) `#define LZSS_ENC_SLACK`
  - `LZSS_EXPAND_NUM` (macro, line 40) `#define LZSS_EXPAND_NUM`
  - `LZSS_EXPAND_DEN` (macro, line 41) `#define LZSS_EXPAND_DEN`
  - `LZSS_SEEK_END` (macro, line 43) `#define LZSS_SEEK_END`
  - `LZSS_ERR_NONE` (macro, line 45) `#define LZSS_ERR_NONE`
  - `LZSS_ERR_OVERFLOW` (macro, line 46) `#define LZSS_ERR_OVERFLOW`
  - `LZSS_EXIT_FAIL` (macro, line 48) `#define LZSS_EXIT_FAIL`

## progs/src/mmreuse.c
- Doc: mmap/munmap reclaim stress test.
- Layer: utility
- Language: c
- Symbols:
  - `mmap_anon` (function, line 7) `static long mmap_anon(long len)`
  - `munmap` (function, line 21) `static long munmap(long addr, long len)`
  - `exit_now` (function, line 31) `static void exit_now(long code)`
  - `_start` (function, line 35) `void _start(void)`
  - `ENOMEM` (function, line 3) `* downward mmap cursor drains until a map fails with ENOMEM (-12);`

## progs/src/mprot.c
- Doc: mprotect probe.
- Layer: utility
- Language: c
- Symbols:
  - `mmap_anon` (function, line 11) `static long mmap_anon(long len)`
  - `mprotect_sys` (function, line 25) `static long mprotect_sys(long addr, long len, long prot)`
  - `write_str` (function, line 36) `static long write_str(const char *s, long n)`
  - `exit_now` (function, line 44) `static void exit_now(long code)`
  - `_start` (function, line 48) `void _start(void)`

## progs/src/mthreads.h
- Doc: Minimal pthread-like threads for MiniOS ELFs (roadmap
- Layer: utility
- Language: h
- Symbols:
  - `mmutex_t` (struct, line 38)
  - `mthread_slot_t` (struct, line 42)
  - `mthread_t` (type_alias, line 35) `typedef int mthread_t;`
  - `m_syscall6` (function, line 50) `static inline long m_syscall6(long n, long a, long b, long c)`
  - `myield` (function, line 59) `static inline void myield(void)`
  - `mfutex_wait` (function, line 63) `static inline long mfutex_wait(volatile int *addr, int val)`
  - `mfutex_wake` (function, line 67) `static inline long mfutex_wake(volatile int *addr, int n)`
  - `mmutex_init` (function, line 71) `static inline void mmutex_init(mmutex_t *m)`
  - `mmutex_lock` (function, line 75) `static inline void mmutex_lock(mmutex_t *m)`
  - `mmutex_unlock` (function, line 90) `static inline void mmutex_unlock(mmutex_t *m)`
  - `mthread_entry` (function, line 98) `static void mthread_entry(void *p)`
  - `mthread_create` (function, line 117) `static int mthread_create(mthread_t *t, void *(*fn)(void *), void *arg)`
  - `mthread_join` (function, line 140) `static int mthread_join(mthread_t t, void **retval)`
  - `MTHREADS_H` (macro, line 24) `#define MTHREADS_H`
  - `MTHREAD_STACK_SZ` (macro, line 28) `#define MTHREAD_STACK_SZ`
  - `MTHREAD_MAX` (macro, line 29) `#define MTHREAD_MAX`
  - `MMUTEX_FREE` (macro, line 31) `#define MMUTEX_FREE`
  - `MMUTEX_HELD` (macro, line 32) `#define MMUTEX_HELD`
  - `MMUTEX_CONTENDED` (macro, line 33) `#define MMUTEX_CONTENDED`
  - `MMUTEX_SPINS` (macro, line 34) `#define MMUTEX_SPINS`
- Depends on: `progs/minios_abi.h`
- Imported by: `progs/src/fptest.c`, `progs/src/scfuzz.c`, `progs/src/thdemo.c`

## progs/src/mtop.c
- Doc: ASCII real-time system monitor for MiniOS.
- Layer: utility
- Language: c
- Symbols:
  - `sc3` (function, line 63) `static long sc3(long n, long a1, long a2, long a3)`
  - `mtop_time` (function, line 72) `static long mtop_time(void)`
  - `mtop_rtc` (function, line 76) `static long mtop_rtc(int *h, int *m, int *s)`
  - `mtop_key` (function, line 80) `static long mtop_key(void)`
  - `mtop_minfo` (function, line 84) `static long mtop_minfo(long sel, long *o1, long *o2)`
  - `emit` (function, line 90) `static void emit(char *s)`
  - `mtop_quit_key` (function, line 94) `static int mtop_quit_key(long k)`
  - `mtop_clear_ansi` (function, line 103) `static void mtop_clear_ansi(void)`
  - `mtop_clear` (function, line 113) `static void mtop_clear(void)`
  - `mtop_atoi` (function, line 117) `static int mtop_atoi(char *s)`
  - `mtop_putu` (function, line 136) `static void mtop_putu(long v)`
  - `mtop_put2` (function, line 158) `static void mtop_put2(int v)`
  - `mtop_put_kb` (function, line 163) `static void mtop_put_kb(long kb)`
  - `mtop_bar` (function, line 179) `static void mtop_bar(long v, long max, int w)`
  - `mtop_hist_max` (function, line 194) `static long mtop_hist_max(long *h, int n)`
  - `mtop_hist_push` (function, line 204) `static void mtop_hist_push(long *h, long v)`
  - `mtop_spark` (function, line 214) `static void mtop_spark(long *h, int n)`
  - `mtop_mem` (function, line 242) `static long mtop_mem(long *used, long *freeb, long *total)`
  - `mtop_cpu` (function, line 253) `static long mtop_cpu(long *count, long *busy)`
  - `mtop_disk_open` (function, line 289) `static void mtop_disk_open(void)`
  - `mtop_disk_read` (function, line 313) `static long mtop_disk_read(long *bytes)`
  - `mtop_net_probe` (function, line 337) `static long mtop_net_probe(long *dns_ms, long *sock_ok)`
  - `mtop_frame` (function, line 355) `static void mtop_frame(int n)`
  - `main` (function, line 531) `int main(int argc, char **argv)`
  - `syscall` (function, line 12) `* * All system figures come from the MINFO syscall (251): heap used / * free, ramdisk used / cap, MiniFS free /...`
  - `putchar` (function, line 35) `int putchar();`
  - `strlen` (function, line 36) `int strlen();`
  - `strcmp` (function, line 37) `int strcmp();`
  - `fopen` (function, line 38) `void *fopen();`
  - `fclose` (function, line 39) `int fclose();`
  - `fread` (function, line 40) `int fread();`
  - `rewind` (function, line 41) `void rewind();`
  - `socket` (function, line 42) `int socket();`
  - `close` (function, line 43) `int close();`
  - `net_dns_resolve` (function, line 44) `int net_dns_resolve();`
  - `MTOP_HIST` (macro, line 46) `#define MTOP_HIST`
  - `MTOP_DISK_BUF` (macro, line 47) `#define MTOP_DISK_BUF`
  - `MTOP_DISK_MAX` (macro, line 48) `#define MTOP_DISK_MAX`
  - `MTOP_MINFO` (macro, line 49) `#define MTOP_MINFO`

## progs/src/mvrn.c
- Doc: mvrn -- rename(82) syscall probe.
- Layer: utility
- Language: c
- Symbols:
  - `mvrn_sc3` (function, line 9) `static long mvrn_sc3(long n, long a1, long a2, long a3)`
  - `mvrn_write` (function, line 16) `static void mvrn_write(const char *s, unsigned long len)`
  - `mvrn_exit` (function, line 20) `static void mvrn_exit(long code)`
  - `mvrn_fail` (function, line 24) `static void mvrn_fail(int step)`
  - `lmain` (function, line 32) `int lmain(void)`

## progs/src/nx.c
- Doc: NX probe.
- Layer: utility
- Language: c
- Symbols:
  - `write_str` (function, line 11) `static long write_str(const char *s, long n)`
  - `exit_now` (function, line 19) `static void exit_now(long code)`
  - `_start` (function, line 23) `void _start(void)`

## progs/src/opl3.c
- Doc: opl3_set_instrument: } static long sys_open(long on) { long r; __asm__...
- Layer: utility
- Language: c
- Symbols:
  - `note_t` (struct, line 102)
  - `sys_time` (function, line 36) `static long sys_time(void)`
  - `sys_open` (function, line 39) `static long sys_open(long on)`
  - `sys_submit` (function, line 42) `static long sys_submit(const void *buf, long len)`
  - `busy_ms` (function, line 46) `static void busy_ms(long ms)`
  - `opl3_set_instrument` (function, line 52) `static void opl3_set_instrument(opl3_chip *chip)`
  - `opl3_note` (function, line 69) `static void opl3_note(opl3_chip *chip, unsigned block, unsigned fnum, int on)`
  - `render` (function, line 77) `static void render(opl3_chip *chip, long ms, long *fail)`
  - `main` (function, line 107) `int main(void)`
  - `SYS_TIME` (macro, line 21) `#define SYS_TIME`
  - `SYS_SB16_OPEN` (macro, line 22) `#define SYS_SB16_OPEN`
  - `SYS_SB16_SUBMIT` (macro, line 23) `#define SYS_SB16_SUBMIT`
  - `SYS_WRITE` (macro, line 24) `#define SYS_WRITE`
  - `SAMPLE_RATE` (macro, line 28) `#define SAMPLE_RATE`
  - `STEREO_FRAMES` (macro, line 29) `#define STEREO_FRAMES`
  - `MONO_BYTES` (macro, line 30) `#define MONO_BYTES`
  - `BUF_MS` (macro, line 32) `#define BUF_MS`
  - `F_NUM_FACTOR` (macro, line 34) `#define F_NUM_FACTOR`
- Depends on: `kernel/string.c`, `progs/minios_abi.h`
- Imported by: `progs/piano/piano.c`

## progs/src/pcmap.c
- Doc: pcmap probe: file-backed MAP_PRIVATE mmap shares text.
- Layer: utility
- Language: c
- Symbols:
  - `sc_open` (function, line 12) `static long sc_open(const char *p)`
  - `sc_mmap` (function, line 21) `static long sc_mmap(long len, long prot, long flags, long fd, long off)`
  - `sc_write` (function, line 34) `static long sc_write(long fd, const char *s, long n)`
  - `sc_exit` (function, line 42) `static void sc_exit(long code)`
  - `sc_fnv` (function, line 46) `static unsigned long sc_fnv(const char *p, long n)`
  - `sc_hex8` (function, line 56) `static void sc_hex8(unsigned long v, char *out)`
  - `sc_munmap` (function, line 65) `static long sc_munmap(long addr, long len)`
  - `_start` (function, line 75) `void _start(void)`

## progs/src/pollready.c
- Doc: lmain: int v = 0; int digits = 0; while (*s >= '0' && *s <= '9') { v = v * 10 + (*s - '0'); s++...
- Layer: utility
- Language: c
- Symbols:
  - `p_write` (function, line 26) `static long p_write(long fd, const char *s, long n)`
  - `p_strlen` (function, line 30) `static unsigned long p_strlen(const char *s)`
  - `p_puts` (function, line 36) `static void p_puts(long fd, const char *s)`
  - `p_atoi` (function, line 40) `static int p_atoi(const char *s)`
  - `p_parse_ip` (function, line 46) `static int p_parse_ip(const char *s, unsigned char out[4])`
  - `lmain` (function, line 63) `int lmain(long argc, char **argv)`

## progs/src/sbtone.c
- Doc: — headless SB16 diagnostic (ring-3, no GUI).
- Layer: utility
- Language: c
- Symbols:
  - `buffers` (function, line 14) `*
 * Exit code is the number of submitted buffers (0 on failure to open).
 */

#include <stdio.h>...`
  - `main` (function, line 36) `int main(void)`
  - `SYS_SB16_OPEN` (macro, line 21) `#define SYS_SB16_OPEN`
  - `SYS_SB16_SUBMIT` (macro, line 22) `#define SYS_SB16_SUBMIT`
  - `SYS_TIME` (macro, line 23) `#define SYS_TIME`
  - `RATE` (macro, line 25) `#define RATE`
  - `BUF` (macro, line 26) `#define BUF`
  - `WINDOW_MS` (macro, line 27) `#define WINDOW_MS`
- Depends on: `progs/minios_abi.h`

## progs/src/scfuzz.c
- Doc: scfuzz: deterministic syscall fuzzer (syzkaller spirit, BDD scale).
- Layer: utility
- Language: c
- Symbols:
  - `guest` (function, line 7) `* the guest (the BDD timeout then talks). All fuzz maps stay inside
 * one private 4 MB arena (pa...`
  - `sc_mprotect` (function, line 38) `static long sc_mprotect(long addr, long len, long prot)`
  - `sc_munmap` (function, line 49) `static long sc_munmap(long addr, long len)`
  - `sc_write` (function, line 53) `static long sc_write(long fd, const char *s, long n)`
  - `sc_exit` (function, line 61) `static void sc_exit(long code)`
  - `sc_rng` (function, line 67) `static unsigned long sc_rng(unsigned long *s)`
  - `sc_fold` (function, line 76) `static unsigned long sc_fold(unsigned long h, unsigned long v)`
  - `sc_hex8` (function, line 88) `static void sc_hex8(unsigned long v, char *out)`
  - `sc_worker` (function, line 97) `static unsigned long sc_worker(int me, unsigned long seed)`
  - `sc_thread1` (function, line 154) `static void *sc_thread1(void *arg)`
  - `_start` (function, line 160) `void _start(void)`
  - `SC_OPS` (macro, line 15) `#define SC_OPS`
  - `SC_ARENA` (macro, line 16) `#define SC_ARENA`
  - `SC_PAGE` (macro, line 17) `#define SC_PAGE`
  - `SC_PAGES` (macro, line 18) `#define SC_PAGES`
  - `SC_T0_BASE` (macro, line 19) `#define SC_T0_BASE`
  - `SC_T0_N` (macro, line 20) `#define SC_T0_N`
  - `SC_T1_BASE` (macro, line 21) `#define SC_T1_BASE`
  - `SC_T1_N` (macro, line 22) `#define SC_T1_N`
- Depends on: `progs/src/mthreads.h`

## progs/src/shell.py
- Doc: pybash: a Python shell layer on top of MiniOS's C shell.
- Layer: utility
- Language: py
- Symbols:
  - `run_capture` (function, line 20) `def run_capture(cmd, args)`
  - `expand` (function, line 30) `def expand(line, env)`
  - `main` (function, line 36) `def main()`
- Depends on: `progs/lua/minios.c`

## progs/src/spin.c
- Layer: utility
- Language: c
- Symbols:
  - `lx_syscall3` (function, line 11) `static long lx_syscall3(long n, long a1, long a2, long a3)`
  - `lx_strlen` (function, line 20) `static unsigned long lx_strlen(const char *s)`
  - `lx_write` (function, line 26) `static void lx_write(const char *s)`
  - `lx_write_int` (function, line 30) `static void lx_write_int(long v)`
  - `lx_atoi` (function, line 42) `static long lx_atoi(const char *s)`
  - `spin_u32` (function, line 66) `static void spin_u32(unsigned char *d, unsigned long v)`
  - `spin_hdr` (function, line 73) `static void spin_hdr(unsigned char *d, unsigned long id, unsigned long op,
        unsigned long ...`
  - `spin_box_ok` (function, line 82) `static int spin_box_ok(const char *box)`
  - `spin_hex8` (function, line 95) `static void spin_hex8(unsigned int v, char *dst)`
  - `spin_write_all` (function, line 104) `static long spin_write_all(long fd, const unsigned char *buf, long len)`
  - `spin_emit` (function, line 114) `static int spin_emit(const char *box, unsigned int seq,
        const unsigned char *msg, long mlen)`
  - `spin_raw_file` (function, line 145) `static int spin_raw_file(const char *box)`
  - `spin_pixels` (function, line 169) `static void spin_pixels(long off)`
  - `spin_wl` (function, line 181) `static int spin_wl(const char *box, const char *narg)`
  - `lmain` (function, line 225) `int lmain(long argc, char **argv)`
  - `SPIN_WLW` (macro, line 56) `#define SPIN_WLW`
  - `SPIN_WLH` (macro, line 57) `#define SPIN_WLH`
  - `SPIN_WLA` (macro, line 58) `#define SPIN_WLA`
  - `SPIN_WLB` (macro, line 59) `#define SPIN_WLB`

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
- Doc: in-OS test suite for MiniOS, driven by MicroPython.
- Layer: testing
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
- Doc: comprehensive non-interactive test suite for MiniOS.
- Layer: testing
- Language: sh

## progs/src/thdemo.c
- Doc: Producer-consumer over mthreads (roadmap Phase 1, M1).
- Layer: utility
- Language: c
- Symbols:
  - `producer` (function, line 36) `static void *producer(void *p)`
  - `consumer` (function, line 57) `static void *consumer(void *p)`
  - `main` (function, line 82) `int main(void)`
  - `threads` (function, line 3) `* * Ten threads (1 main + 5 producers + 4 consumers) share one address * space through thread_spawn (MiniOS syscall...`
  - `NPROD` (macro, line 21) `#define NPROD`
  - `NCONS` (macro, line 22) `#define NCONS`
  - `PER_PROD` (macro, line 23) `#define PER_PROD`
  - `BUFSZ` (macro, line 24) `#define BUFSZ`
  - `EXPECTED_N` (macro, line 26) `#define EXPECTED_N`
  - `EXPECTED_SUM` (macro, line 27) `#define EXPECTED_SUM`
- Depends on: `progs/minios_abi.h`, `progs/src/mthreads.h`

## progs/src/w1.c
- Layer: utility
- Language: c
- Symbols:
  - `main` (function, line 3) `int main(void)`
  - `write` (function, line 1) `int write(int fd, char *buf, int n);`

