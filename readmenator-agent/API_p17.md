# API (page 17 of 19)
Previous: [API_p16.md](API_p16.md)

## progs/src/ftest.c
- `fprintf` (function) `progs/src/ftest.c:4` `extern int fprintf(void *stream, const char *fmt, ...);` -- Exercises the kernel libc surface used by loaded .o programs: fprintf to stdout/stderr, snprintf into a buffer...
- `snprintf` (function) `progs/src/ftest.c:5` `extern int snprintf(char *buf, unsigned long size, const char *fmt, ...);`
- `printf` (function) `progs/src/ftest.c:6` `extern int printf(const char *fmt, ...);`
- `exit` (function) `progs/src/ftest.c:7` `extern void exit(int code);`
- `fopen` (function) `progs/src/ftest.c:11` `extern void *fopen(const char *path, const char *mode);`
- `main` (function) `progs/src/ftest.c:13` `int main(int argc, char **argv)`

## progs/src/hello.c
- `printf` (function) `progs/src/hello.c:2` `extern int printf(const char *fmt, ...);` -- /* MiniOS test program — compiled as relocatable .o, loaded by kernel ELF loader
- `main` (function) `progs/src/hello.c:4` `int main(int argc, char **argv)`

## progs/src/http.c
- `kernel` (function) `progs/src/http.c:3` `* Hostnames are resolved by the kernel (net_dns_resolve syscall). */ int socket(int domain, int type, int proto);`
- `connect` (function) `progs/src/http.c:6` `int connect(int fd, void *addr, int addrlen);`
- `sendto` (function) `progs/src/http.c:7` `int sendto(int fd, char *buf, int len, int flags, void *to, int tolen);`
- `recvfrom` (function) `progs/src/http.c:8` `int recvfrom(int fd, char *buf, int len, int flags, void *from, int *fromlen);`
- `shutdown` (function) `progs/src/http.c:9` `int shutdown(int fd, int how);`
- `close` (function) `progs/src/http.c:10` `int close(int fd);`
- `net_dns_resolve` (function) `progs/src/http.c:11` `int net_dns_resolve(const char *host);`
- `puts` (function) `progs/src/http.c:12` `int puts(char *s);`
- `printf` (function) `progs/src/http.c:13` `int printf(char *fmt, ...);`
- `strlen` (function) `progs/src/http.c:14` `int strlen(char *s);`
- `putchar` (function) `progs/src/http.c:15` `int putchar(int c);`
- `atoi` (function) `progs/src/http.c:18` `int atoi(char *s)` -- int socket(int domain, int type, int proto); int connect(int fd, void *addr, int addrlen); int sendto(int fd, char...
- `main` (function) `progs/src/http.c:29` `int main(int argc, char **argv)`

## progs/src/json.c
- `js_str` (function) `progs/src/json.c:5` `* members keep their key in js_str (the member value node) and their value * in the node itself, and object members...`
- `free` (function) `progs/src/json.c:14` `void free();`
- `printf` (function) `progs/src/json.c:15` `int printf();`
- `putchar` (function) `progs/src/json.c:16` `int putchar();`
- `puts` (function) `progs/src/json.c:17` `int puts();`
- `strlen` (function) `progs/src/json.c:18` `int strlen();`
- `strcmp` (function) `progs/src/json.c:19` `int strcmp();`
- `fopen` (function) `progs/src/json.c:20` `void *fopen();`
- `fclose` (function) `progs/src/json.c:21` `int fclose();`
- `fread` (function) `progs/src/json.c:22` `int fread();`
- `fseek` (function) `progs/src/json.c:23` `int fseek();`
- `ftell` (function) `progs/src/json.c:24` `int ftell();`
- `rewind` (function) `progs/src/json.c:25` `void rewind();`
- `js_read_all` (function) `progs/src/json.c:58` `static char *js_read_all(const char *name, int *len)`
- `js_new` (function) `progs/src/json.c:76` `static int js_new(void)`
- `js_skip_ws` (function) `progs/src/json.c:81` `static void js_skip_ws(void)`
- `js_peek` (function) `progs/src/json.c:89` `static int js_peek(void)`
- `js_parse_string` (function) `progs/src/json.c:97` `static int js_parse_string(void)`
- `js_parse_number` (function) `progs/src/json.c:133` `static int js_parse_number(void)`
- `js_key_match` (function) `progs/src/json.c:143` `static int js_key_match(int child, const char *key)`
- `js_parse_object` (function) `progs/src/json.c:147` `static int js_parse_object(void)`
- `js_parse_array` (function) `progs/src/json.c:182` `static int js_parse_array(void)`
- `js_parse_value` (function) `progs/src/json.c:211` `static int js_parse_value(void)`
- `js_indent` (function) `progs/src/json.c:281` `static void js_indent(int n)`
- `js_print_str` (function) `progs/src/json.c:286` `static void js_print_str(const char *s)`
- `js_print_value` (function) `progs/src/json.c:303` `static void js_print_value(int node, int depth)`
- `js_find_member` (function) `progs/src/json.c:347` `static int js_find_member(int obj, const char *key)`
- `js_array_at` (function) `progs/src/json.c:357` `static int js_array_at(int arr, int idx)`
- `js_query` (function) `progs/src/json.c:369` `static int js_query(int root, const char *path)`
- `main` (function) `progs/src/json.c:401` `int main(int argc, char **argv)`

## progs/src/kmem.c
- `syscall3` (function) `progs/src/kmem.c:7` `static long syscall3(long n, long a1, long a2, long a3)` -- Kernel-pointer rejection probe.
- `exit_now` (function) `progs/src/kmem.c:14` `static void exit_now(long code)`

## progs/src/ldhello.c
- `main` (function) `progs/src/ldhello.c:1` `int main(void)`

## progs/src/lxhello.c
- `lx_syscall3` (function) `progs/src/lxhello.c:11` `static long lx_syscall3(long n, long a1, long a2, long a3)`
- `lx_strlen` (function) `progs/src/lxhello.c:23` `static unsigned long lx_strlen(const char *s)`
- `lx_write` (function) `progs/src/lxhello.c:29` `static void lx_write(const char *s)`
- `lx_write_int` (function) `progs/src/lxhello.c:33` `static void lx_write_int(long v)`
- `lmain` (function) `progs/src/lxhello.c:46` `int lmain(long argc, char **argv)` -- static void lx_write_int(long v) { char buf[24]; int i = (int)sizeof(buf); int neg = 0; buf[--i] = 0; if (v < 0) {...

## progs/src/lz4.c
- `kernel` (function) `progs/src/lz4.c:6` `* * The codec lives in the kernel (lz4_kernel.c, the same one MiniFS uses), so * these tools are thin front-ends...`
- `free` (function) `progs/src/lz4.c:15` `void free();`
- `printf` (function) `progs/src/lz4.c:16` `int printf();`
- `strcmp` (function) `progs/src/lz4.c:17` `int strcmp();`
- `strlen` (function) `progs/src/lz4.c:18` `int strlen();`
- `fopen` (function) `progs/src/lz4.c:19` `void *fopen();`
- `fclose` (function) `progs/src/lz4.c:20` `int fclose();`
- `fread` (function) `progs/src/lz4.c:21` `int fread();`
- `fwrite` (function) `progs/src/lz4.c:22` `int fwrite();`
- `fseek` (function) `progs/src/lz4.c:23` `int fseek();`
- `ftell` (function) `progs/src/lz4.c:24` `int ftell();`
- `rewind` (function) `progs/src/lz4.c:25` `void rewind();`
- `lz4_compress` (function) `progs/src/lz4.c:27` `int lz4_compress(char *src, int srclen, char *dst, int dstcap);`
- `lz4_decompress` (function) `progs/src/lz4.c:28` `int lz4_decompress(char *src, int srclen, char *dst, int dstcap);`
- `lz4_has` (function) `progs/src/lz4.c:39` `static int lz4_has(const char *s, const char *needle)`
- `lz4_read_all` (function) `progs/src/lz4.c:53` `static char *lz4_read_all(const char *name, int *len)`
- `lz4_write_all` (function) `progs/src/lz4.c:70` `static int lz4_write_all(const char *name, char *data, int len)`
- `lz4_compress_file` (function) `progs/src/lz4.c:80` `static int lz4_compress_file(const char *src, const char *dst)`
- `lz4_decompress_file` (function) `progs/src/lz4.c:117` `static int lz4_decompress_file(const char *src, const char *dst)`
- `main` (function) `progs/src/lz4.c:164` `int main(int argc, char **argv)`

## progs/src/lzss.c
- `malloc` (function) `progs/src/lzss.c:13` `void *malloc();`
- `free` (function) `progs/src/lzss.c:14` `void free();`
- `printf` (function) `progs/src/lzss.c:15` `int printf();`
- `strcmp` (function) `progs/src/lzss.c:16` `int strcmp();`
- `strlen` (function) `progs/src/lzss.c:17` `int strlen();`
- `fopen` (function) `progs/src/lzss.c:18` `void *fopen();`
- `fclose` (function) `progs/src/lzss.c:19` `int fclose();`
- `fread` (function) `progs/src/lzss.c:20` `int fread();`
- `fwrite` (function) `progs/src/lzss.c:21` `int fwrite();`
- `fseek` (function) `progs/src/lzss.c:22` `int fseek();`
- `ftell` (function) `progs/src/lzss.c:23` `int ftell();`
- `rewind` (function) `progs/src/lzss.c:24` `void rewind();`
- `lz_in_getc` (function) `progs/src/lzss.c:64` `static int lz_in_getc(void)`
- `lz_out_put` (function) `progs/src/lzss.c:69` `static void lz_out_put(int c)`
- `lz_putbit1` (function) `progs/src/lzss.c:74` `static void lz_putbit1(void)`
- `lz_putbit0` (function) `progs/src/lzss.c:84` `static void lz_putbit0(void)`
- `lz_flush_bits` (function) `progs/src/lzss.c:93` `static void lz_flush_bits(void)`
- `lz_out_literal` (function) `progs/src/lzss.c:97` `static void lz_out_literal(int c)`
- `lz_out_pair` (function) `progs/src/lzss.c:105` `static void lz_out_pair(int x, int y)`
- `lz_encode` (function) `progs/src/lzss.c:118` `static int lz_encode(void)`
- `lz_getbit` (function) `progs/src/lzss.c:173` `static int lz_getbit(int n)`
- `lz_decode` (function) `progs/src/lzss.c:189` `static int lz_decode(void)`
- `lz_hdr_put` (function) `progs/src/lzss.c:218` `static void lz_hdr_put(char *h, int size)`
- `lz_hdr_get` (function) `progs/src/lzss.c:229` `static int lz_hdr_get(char *h)`
- `lz_has` (function) `progs/src/lzss.c:237` `static int lz_has(const char *s, const char *needle)`
- `lz_read_all` (function) `progs/src/lzss.c:251` `static char *lz_read_all(const char *name, int *len)`
- `lz_write_all` (function) `progs/src/lzss.c:268` `static int lz_write_all(const char *name, char *data, int len)`
- `lz_compress` (function) `progs/src/lzss.c:278` `static int lz_compress(const char *src, const char *dst)`
- `lz_decompress` (function) `progs/src/lzss.c:325` `static int lz_decompress(const char *src, const char *dst)`
- `main` (function) `progs/src/lzss.c:397` `int main(int argc, char **argv)`

## progs/src/mmreuse.c
- `ENOMEM` (function) `progs/src/mmreuse.c:3` `* downward mmap cursor drains until a map fails with ENOMEM (-12);`
- `mmap_anon` (function) `progs/src/mmreuse.c:7` `static long mmap_anon(long len)` -- mmap/munmap reclaim stress test.
- `munmap` (function) `progs/src/mmreuse.c:21` `static long munmap(long addr, long len)`
- `exit_now` (function) `progs/src/mmreuse.c:31` `static void exit_now(long code)`

## progs/src/mprot.c
- `mmap_anon` (function) `progs/src/mprot.c:11` `static long mmap_anon(long len)`
- `mprotect_sys` (function) `progs/src/mprot.c:25` `static long mprotect_sys(long addr, long len, long prot)`
- `write_str` (function) `progs/src/mprot.c:36` `static long write_str(const char *s, long n)`
- `exit_now` (function) `progs/src/mprot.c:44` `static void exit_now(long code)`

## progs/src/mthreads.h
Depends on: `progs/minios_abi.h`
Imported by: `progs/src/fptest.c`, `progs/src/scfuzz.c`, `progs/src/thdemo.c`
- `m_syscall6` (function) `progs/src/mthreads.h:50` `static inline long m_syscall6(long n, long a, long b, long c)`
- `myield` (function) `progs/src/mthreads.h:59` `static inline void myield(void)`
- `mfutex_wait` (function) `progs/src/mthreads.h:63` `static inline long mfutex_wait(volatile int *addr, int val)`
- `mfutex_wake` (function) `progs/src/mthreads.h:67` `static inline long mfutex_wake(volatile int *addr, int n)`
- `mmutex_init` (function) `progs/src/mthreads.h:71` `static inline void mmutex_init(mmutex_t *m)`
- `mmutex_lock` (function) `progs/src/mthreads.h:75` `static inline void mmutex_lock(mmutex_t *m)`
- `mmutex_unlock` (function) `progs/src/mthreads.h:90` `static inline void mmutex_unlock(mmutex_t *m)`
- `mthread_entry` (function) `progs/src/mthreads.h:98` `static void mthread_entry(void *p)` -- Thread entry trampoline: runs fn(arg), stores the return, exits 0. * The exit code is always 0; join reads retval...
- `mthread_create` (function) `progs/src/mthreads.h:117` `static int mthread_create(mthread_t *t, void *(*fn)(void *), void *arg)`
- `mthread_join` (function) `progs/src/mthreads.h:140` `static int mthread_join(mthread_t t, void **retval)`

## progs/src/mtop.c
- `syscall` (function) `progs/src/mtop.c:12` `* * All system figures come from the MINFO syscall (251): heap used / * free, ramdisk used / cap, MiniFS free /...`
- `putchar` (function) `progs/src/mtop.c:35` `int putchar();`
- `strlen` (function) `progs/src/mtop.c:36` `int strlen();`
- `strcmp` (function) `progs/src/mtop.c:37` `int strcmp();`
- `fopen` (function) `progs/src/mtop.c:38` `void *fopen();`
- `fclose` (function) `progs/src/mtop.c:39` `int fclose();`
- `fread` (function) `progs/src/mtop.c:40` `int fread();`
- `rewind` (function) `progs/src/mtop.c:41` `void rewind();`
- `socket` (function) `progs/src/mtop.c:42` `int socket();`
- `close` (function) `progs/src/mtop.c:43` `int close();`
- `net_dns_resolve` (function) `progs/src/mtop.c:44` `int net_dns_resolve();`
- `sc3` (function) `progs/src/mtop.c:63` `static long sc3(long n, long a1, long a2, long a3)`
- `mtop_time` (function) `progs/src/mtop.c:72` `static long mtop_time(void)`
- `mtop_rtc` (function) `progs/src/mtop.c:76` `static long mtop_rtc(int *h, int *m, int *s)`
- `mtop_key` (function) `progs/src/mtop.c:80` `static long mtop_key(void)`
- `mtop_minfo` (function) `progs/src/mtop.c:84` `static long mtop_minfo(long sel, long *o1, long *o2)`
- `emit` (function) `progs/src/mtop.c:90` `static void emit(char *s)`
- `mtop_quit_key` (function) `progs/src/mtop.c:94` `static int mtop_quit_key(long k)`
- `mtop_clear_ansi` (function) `progs/src/mtop.c:103` `static void mtop_clear_ansi(void)`
- `mtop_clear` (function) `progs/src/mtop.c:113` `static void mtop_clear(void)`
- `mtop_atoi` (function) `progs/src/mtop.c:117` `static int mtop_atoi(char *s)`
- `mtop_putu` (function) `progs/src/mtop.c:136` `static void mtop_putu(long v)`
- `mtop_put2` (function) `progs/src/mtop.c:158` `static void mtop_put2(int v)`
- `mtop_put_kb` (function) `progs/src/mtop.c:163` `static void mtop_put_kb(long kb)`
- `mtop_bar` (function) `progs/src/mtop.c:179` `static void mtop_bar(long v, long max, int w)`
- `mtop_hist_max` (function) `progs/src/mtop.c:194` `static long mtop_hist_max(long *h, int n)`
- `mtop_hist_push` (function) `progs/src/mtop.c:204` `static void mtop_hist_push(long *h, long v)`
- `mtop_spark` (function) `progs/src/mtop.c:214` `static void mtop_spark(long *h, int n)`
- `mtop_mem` (function) `progs/src/mtop.c:242` `static long mtop_mem(long *used, long *freeb, long *total)`
- `mtop_cpu` (function) `progs/src/mtop.c:253` `static long mtop_cpu(long *count, long *busy)`
- `mtop_disk_open` (function) `progs/src/mtop.c:289` `static void mtop_disk_open(void)`
- `mtop_disk_read` (function) `progs/src/mtop.c:313` `static long mtop_disk_read(long *bytes)`
- `mtop_net_probe` (function) `progs/src/mtop.c:337` `static long mtop_net_probe(long *dns_ms, long *sock_ok)`
- `mtop_frame` (function) `progs/src/mtop.c:355` `static void mtop_frame(int n)`
- `main` (function) `progs/src/mtop.c:531` `int main(int argc, char **argv)`

## progs/src/mvrn.c
- `mvrn_sc3` (function) `progs/src/mvrn.c:9` `static long mvrn_sc3(long n, long a1, long a2, long a3)` -- mvrn -- rename(82) syscall probe.
- `mvrn_write` (function) `progs/src/mvrn.c:16` `static void mvrn_write(const char *s, unsigned long len)`
- `mvrn_exit` (function) `progs/src/mvrn.c:20` `static void mvrn_exit(long code)`
- `mvrn_fail` (function) `progs/src/mvrn.c:24` `static void mvrn_fail(int step)`
- `lmain` (function) `progs/src/mvrn.c:32` `int lmain(void)`

## progs/src/nx.c
- `write_str` (function) `progs/src/nx.c:11` `static long write_str(const char *s, long n)`
- `exit_now` (function) `progs/src/nx.c:19` `static void exit_now(long code)`

## progs/src/opl3.c
Depends on: `kernel/string.c`, `progs/minios_abi.h`
Imported by: `progs/piano/piano.c`
- `sys_time` (function) `progs/src/opl3.c:36` `static long sys_time(void)`
- `sys_open` (function) `progs/src/opl3.c:39` `static long sys_open(long on)`
- `sys_submit` (function) `progs/src/opl3.c:42` `static long sys_submit(const void *buf, long len)`
- `busy_ms` (function) `progs/src/opl3.c:46` `static void busy_ms(long ms)`
- `opl3_set_instrument` (function) `progs/src/opl3.c:52` `static void opl3_set_instrument(opl3_chip *chip)` -- } static long sys_open(long on) { long r; __asm__ volatile("syscall":"=a"(r):"a"(SYS_SB16_OPEN),"D"(on):"rcx","r11","...
- `opl3_note` (function) `progs/src/opl3.c:69` `static void opl3_note(opl3_chip *chip, unsigned block, unsigned fnum, int on)`
- `render` (function) `progs/src/opl3.c:77` `static void render(opl3_chip *chip, long ms, long *fail)` -- Render `ms` of the current note and stream it to the SB16.
- `main` (function) `progs/src/opl3.c:107` `int main(void)`

## progs/src/pcmap.c
- `sc_open` (function) `progs/src/pcmap.c:12` `static long sc_open(const char *p)` -- pcmap probe: file-backed MAP_PRIVATE mmap shares text.
- `sc_mmap` (function) `progs/src/pcmap.c:21` `static long sc_mmap(long len, long prot, long flags, long fd, long off)`
- `sc_write` (function) `progs/src/pcmap.c:34` `static long sc_write(long fd, const char *s, long n)`
- `sc_exit` (function) `progs/src/pcmap.c:42` `static void sc_exit(long code)`
- `sc_fnv` (function) `progs/src/pcmap.c:46` `static unsigned long sc_fnv(const char *p, long n)`
- `sc_hex8` (function) `progs/src/pcmap.c:56` `static void sc_hex8(unsigned long v, char *out)`
- `sc_munmap` (function) `progs/src/pcmap.c:65` `static long sc_munmap(long addr, long len)`

## progs/src/pollready.c
- `p_write` (function) `progs/src/pollready.c:26` `static long p_write(long fd, const char *s, long n)`
- `p_strlen` (function) `progs/src/pollready.c:30` `static unsigned long p_strlen(const char *s)`
- `p_puts` (function) `progs/src/pollready.c:36` `static void p_puts(long fd, const char *s)`
- `p_atoi` (function) `progs/src/pollready.c:40` `static int p_atoi(const char *s)`
- `p_parse_ip` (function) `progs/src/pollready.c:46` `static int p_parse_ip(const char *s, unsigned char out[4])`
- `lmain` (function) `progs/src/pollready.c:63` `int lmain(long argc, char **argv)` -- int v = 0; int digits = 0; while (*s >= '0' && *s <= '9') { v = v * 10 + (*s - '0'); s++; digits++; } if (!digits ||...

## progs/src/sbtone.c
Depends on: `progs/minios_abi.h`
- `buffers` (function) `progs/src/sbtone.c:14` `*
 * Exit code is the number of submitted buffers (0 on failure to open).
 */

#include <stdio.h>...`
- `main` (function) `progs/src/sbtone.c:36` `int main(void)`

## progs/src/scfuzz.c
Depends on: `progs/src/mthreads.h`
- `guest` (function) `progs/src/scfuzz.c:7` `* the guest (the BDD timeout then talks). All fuzz maps stay inside
 * one private 4 MB arena (pa...`
- `sc_mprotect` (function) `progs/src/scfuzz.c:38` `static long sc_mprotect(long addr, long len, long prot)`
- `sc_munmap` (function) `progs/src/scfuzz.c:49` `static long sc_munmap(long addr, long len)`
- `sc_write` (function) `progs/src/scfuzz.c:53` `static long sc_write(long fd, const char *s, long n)`
- `sc_exit` (function) `progs/src/scfuzz.c:61` `static void sc_exit(long code)`
- `sc_rng` (function) `progs/src/scfuzz.c:67` `static unsigned long sc_rng(unsigned long *s)`
- `sc_fold` (function) `progs/src/scfuzz.c:76` `static unsigned long sc_fold(unsigned long h, unsigned long v)`
- `sc_hex8` (function) `progs/src/scfuzz.c:88` `static void sc_hex8(unsigned long v, char *out)`
- `sc_worker` (function) `progs/src/scfuzz.c:97` `static unsigned long sc_worker(int me, unsigned long seed)`
- `sc_thread1` (function) `progs/src/scfuzz.c:154` `static void *sc_thread1(void *arg)`

## progs/src/shell.py
Depends on: `progs/lua/minios.c`
- `run_capture` (function) `progs/src/shell.py:20` `def run_capture(cmd, args)`
- `expand` (function) `progs/src/shell.py:30` `def expand(line, env)`
- `main` (function) `progs/src/shell.py:36` `def main()`

## progs/src/spin.c
- `lx_syscall3` (function) `progs/src/spin.c:11` `static long lx_syscall3(long n, long a1, long a2, long a3)`
- `lx_strlen` (function) `progs/src/spin.c:20` `static unsigned long lx_strlen(const char *s)`
- `lx_write` (function) `progs/src/spin.c:26` `static void lx_write(const char *s)`
- `lx_write_int` (function) `progs/src/spin.c:30` `static void lx_write_int(long v)`
- `lx_atoi` (function) `progs/src/spin.c:42` `static long lx_atoi(const char *s)`
- `spin_u32` (function) `progs/src/spin.c:66` `static void spin_u32(unsigned char *d, unsigned long v)`
- `spin_hdr` (function) `progs/src/spin.c:73` `static void spin_hdr(unsigned char *d, unsigned long id, unsigned long op,
        unsigned long ...`
- `spin_box_ok` (function) `progs/src/spin.c:82` `static int spin_box_ok(const char *box)`
- `spin_hex8` (function) `progs/src/spin.c:95` `static void spin_hex8(unsigned int v, char *dst)`
- `spin_write_all` (function) `progs/src/spin.c:104` `static long spin_write_all(long fd, const unsigned char *buf, long len)`
- `spin_emit` (function) `progs/src/spin.c:114` `static int spin_emit(const char *box, unsigned int seq,
        const unsigned char *msg, long mlen)`
- `spin_raw_file` (function) `progs/src/spin.c:145` `static int spin_raw_file(const char *box)`
- `spin_pixels` (function) `progs/src/spin.c:169` `static void spin_pixels(long off)`
- `spin_wl` (function) `progs/src/spin.c:181` `static int spin_wl(const char *box, const char *narg)`
- `lmain` (function) `progs/src/spin.c:225` `int lmain(long argc, char **argv)`

## progs/src/thdemo.c
Depends on: `progs/minios_abi.h`, `progs/src/mthreads.h`
- `threads` (function) `progs/src/thdemo.c:3` `* * Ten threads (1 main + 5 producers + 4 consumers) share one address * space through thread_spawn (MiniOS syscall...`
- `producer` (function) `progs/src/thdemo.c:36` `static void *producer(void *p)`
- `consumer` (function) `progs/src/thdemo.c:57` `static void *consumer(void *p)`
- `main` (function) `progs/src/thdemo.c:82` `int main(void)`

## progs/src/w1.c
- `write` (function) `progs/src/w1.c:1` `int write(int fd, char *buf, int n);`
- `main` (function) `progs/src/w1.c:3` `int main(void)`

## progs/tls_u/tls_u_main.c
Depends on: `headers/tls.h`, `headers/tls_port.h`, `kernel/string.c`
- `syscall` (function) `progs/tls_u/tls_u_main.c:10` `* the MiniOS DNS syscall (200, sig 0: error-check only, sends nothing).
 * The kernel keeps servi...`
- `parse_port` (function) `progs/tls_u/tls_u_main.c:47` `static int parse_port(const char *s)` -- Strict port parser (clang-tidy cert-err34-c: atoi reports no errors, so "abc" and overflow both become 0 and fail...
- `main` (function) `progs/tls_u/tls_u_main.c:61` `int main(int argc, char **argv)`

## progs/tls_u/tls_u_port.c
Depends on: `kernel/string.c`, `kernel/time.c`
- `sockets` (function) `progs/tls_u/tls_u_port.c:5` `* sockets: on the host they are host sockets (used by the
 * openssl-s_server interop test), insi...`
- `tls_u_recv` (function) `progs/tls_u/tls_u_port.c:39` `int tls_u_recv(int fd, char *buf, int len)`
- `tls_u_recv_timeout` (function) `progs/tls_u/tls_u_port.c:44` `int tls_u_recv_timeout(int fd, char *buf, int len, unsigned long ms)`
- `tls_u_close` (function) `progs/tls_u/tls_u_port.c:55` `void tls_u_close(int fd)`
- `tls_free_fd` (function) `progs/tls_u/tls_u_port.c:66` `void tls_free_fd(int fd);` -- Session-aware close for multi-fetch processes (freedom follows redirects and linked stylesheets, reusing the lowest...
- `tls_close` (function) `progs/tls_u/tls_u_port.c:67` `void tls_close(int fd)` -- Session-aware close for multi-fetch processes (freedom follows redirects and linked stylesheets, reusing the lowest...
- `tls_now_days` (function) `progs/tls_u/tls_u_port.c:72` `long tls_now_days(void)`
- `tls_random` (function) `progs/tls_u/tls_u_port.c:78` `void tls_random(unsigned char *out, unsigned len)`
- `u_raw_syscall3` (function) `progs/tls_u/tls_u_port.c:99` `static long u_raw_syscall3(long n, long a1, long a2, long a3)`
- `parse_quad` (function) `progs/tls_u/tls_u_port.c:122` `static int parse_quad(const char *s, unsigned *ip_out)` -- Strict dotted-quad parser (clang-tidy cert-err34-c: sscanf %u has undefined overflow and accepts whitespace/sign, so...
- `tls_u_resolve` (function) `progs/tls_u/tls_u_port.c:147` `int tls_u_resolve(const char *host, unsigned *ip_out)`
- `answer` (function) `progs/tls_u/tls_u_port.c:163` `* answer (some resolvers go IPv6-only on the first query). */ memset(&hints, 0, sizeof(hints));`
- `net_dns_resolve` (function) `progs/tls_u/tls_u_port.c:183` `int net_dns_resolve(const char *host)` -- freedom's resolver name: kernel DNS value semantics (u32 host order, * -1 on failure).

## progs/topogpt3/topogpt3.c
Depends on: `kernel/string.c`
- `printf` (function) `progs/topogpt3/topogpt3.c:28` `extern int printf(const char *, ...);`
- `fprintf` (function) `progs/topogpt3/topogpt3.c:29` `extern int fprintf(FILE *, const char *, ...);`
- `sprintf` (function) `progs/topogpt3/topogpt3.c:30` `extern int sprintf(char *, const char *, ...);`
- `snprintf` (function) `progs/topogpt3/topogpt3.c:31` `extern int snprintf(char *, unsigned long, const char *, ...);`
- `puts` (function) `progs/topogpt3/topogpt3.c:32` `extern int puts(const char *);`
- `putchar` (function) `progs/topogpt3/topogpt3.c:33` `extern int putchar(int);`
- `fputc` (function) `progs/topogpt3/topogpt3.c:34` `extern int fputc(int, FILE *);`
- `fputs` (function) `progs/topogpt3/topogpt3.c:35` `extern int fputs(const char *, FILE *);`
- `fopen` (function) `progs/topogpt3/topogpt3.c:36` `extern FILE *fopen(const char *, const char *);`
- `fclose` (function) `progs/topogpt3/topogpt3.c:37` `extern int fclose(FILE *);`
- `fread` (function) `progs/topogpt3/topogpt3.c:38` `extern unsigned long fread(void *, unsigned long, unsigned long, FILE *);`
- `fwrite` (function) `progs/topogpt3/topogpt3.c:39` `extern unsigned long fwrite(const void *, unsigned long, unsigned long, FILE *);`
- `fseek` (function) `progs/topogpt3/topogpt3.c:40` `extern int fseek(FILE *, long, int);`
- `ftell` (function) `progs/topogpt3/topogpt3.c:41` `extern long ftell(FILE *);`
- `fflush` (function) `progs/topogpt3/topogpt3.c:42` `extern int fflush(FILE *);`
- `malloc` (function) `progs/topogpt3/topogpt3.c:47` `extern void *malloc(unsigned long);` -- define NULL ((void*)0) define SEEK_SET 0 define SEEK_CUR 1 define SEEK_END 2
- `free` (function) `progs/topogpt3/topogpt3.c:48` `extern void free(void *);`
- `memcpy` (function) `progs/topogpt3/topogpt3.c:49` `extern void *memcpy(void *, const void *, unsigned long);`
- `memset` (function) `progs/topogpt3/topogpt3.c:50` `extern void *memset(void *, int, unsigned long);`
- `strcmp` (function) `progs/topogpt3/topogpt3.c:51` `extern int strcmp(const char *, const char *);`
- `strncmp` (function) `progs/topogpt3/topogpt3.c:52` `extern int strncmp(const char *, const char *, unsigned long);`
- `strlen` (function) `progs/topogpt3/topogpt3.c:53` `extern unsigned long strlen(const char *);`
- `strstr` (function) `progs/topogpt3/topogpt3.c:54` `extern char *strstr(const char *, const char *);`
- `tg_exp` (function) `progs/topogpt3/topogpt3.c:114` `static float tg_exp(float x)`
- `tg_tanh` (function) `progs/topogpt3/topogpt3.c:128` `static float tg_tanh(float x)`
- `tg_sin` (function) `progs/topogpt3/topogpt3.c:135` `static float tg_sin(float x)`
- `tg_cos` (function) `progs/topogpt3/topogpt3.c:144` `static float tg_cos(float x)`
- `tg_fabs` (function) `progs/topogpt3/topogpt3.c:148` `static float tg_fabs(float x)`
- `tg_log` (function) `progs/topogpt3/topogpt3.c:152` `static float tg_log(float x)`
- `tg_fmax` (function) `progs/topogpt3/topogpt3.c:164` `static float tg_fmax(float a, float b)`
- `tg_fmin` (function) `progs/topogpt3/topogpt3.c:168` `static float tg_fmin(float a, float b)`
- `load_vocab` (function) `progs/topogpt3/topogpt3.c:255` `static void load_vocab(const char *path)`
- `build_torus_graph` (function) `progs/topogpt3/topogpt3.c:296` `static void build_torus_graph(void)`
- `precompute_rope` (function) `progs/topogpt3/topogpt3.c:327` `static void precompute_rope(void)`
- `matvec` (function) `progs/topogpt3/topogpt3.c:359` `static void matvec(const float *W, const float *x, float *y, int rows, int cols)`
- `matvec_bias` (function) `progs/topogpt3/topogpt3.c:370` `static void matvec_bias(const float *W, const float *b, const float *x, float *y,
               ...`
- `rmsnorm` (function) `progs/topogpt3/topogpt3.c:382` `static void rmsnorm(const float *x, const float *w, float *y, int d)`
- `softmax` (function) `progs/topogpt3/topogpt3.c:391` `static void softmax(float *x, int n)`
- `gelu` (function) `progs/topogpt3/topogpt3.c:400` `static void gelu(float *x, int n)`
- `silu` (function) `progs/topogpt3/topogpt3.c:410` `static void silu(float *x, int n)`
- `swiglu` (function) `progs/topogpt3/topogpt3.c:418` `static void swiglu(const float *gate_w, const float *up_w, const float *down_w,
                 ...`
- `quat_normalize` (function) `progs/topogpt3/topogpt3.c:435` `static void quat_normalize(float *q)`
- `quat_hamilton` (function) `progs/topogpt3/topogpt3.c:440` `static void quat_hamilton(const float *a, const float *b, float *c)`
- `quat_linear` (function) `progs/topogpt3/topogpt3.c:448` `static void quat_linear(const float *Ww, const float *Wx, const float *Wy, const float *Wz,
     ...` -- static void quat_normalize(float *q) { float n = tg_sqrt(q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3]); if (n >...
- `ifft_radix2` (function) `progs/topogpt3/topogpt3.c:505` `static void ifft_radix2(float *real, float *imag, int n)`
- `rfft` (function) `progs/topogpt3/topogpt3.c:513` `static void rfft(const float *x, float *Xr, float *Xi, int n)` -- cur_r = nr; } } } } static void ifft_radix2(float *real, float *imag, int n) { int i; for (i = 0; i < n; i++)...
- `irfft` (function) `progs/topogpt3/topogpt3.c:522` `static void irfft(const float *Xr, const float *Xi, float *x, int n)` -- fft_radix2(real, imag, n); for (i = 0; i < n; i++) { real[i] /= (float)n; imag[i] = -imag[i] / (float)n; } } /* Real...
- `filter1d` (function) `progs/topogpt3/topogpt3.c:537` `static void filter1d(const float *x, const float *kr, const float *ki,
                      floa...`
- `ifft2d` (function) `progs/topogpt3/topogpt3.c:580` `static void ifft2d(float *data_r, float *data_i, int h, int w)`
- `rfft2d_real` (function) `progs/topogpt3/topogpt3.c:602` `static void rfft2d_real(const float *data, float *out_r, float *out_i,
                         i...` -- ifft_radix2(row_re, row_im, w); for (c = 0; c < w; c++) { re[r*w+c] = row_re[c]; im[r*w+c] = row_im[c]; } } /* IFFT...
- `irfft2d` (function) `progs/topogpt3/topogpt3.c:629` `static void irfft2d(const float *in_r, const float *in_i, float *out,
                     int h,...` -- for (r = 0; r < h; r++) { col_re[r] = re[r*w+c]; col_im[r] = im[r*w+c]; } fft_radix2(col_re, col_im, h); for (r = 0...
- `cmul` (function) `progs/topogpt3/topogpt3.c:664` `static void cmul(float ar, float ai, float cr, float di, float *rr, float *ri)`
- `spectral_contract` (function) `progs/topogpt3/topogpt3.c:670` `static void spectral_contract(const float *Wr, const float *Wi,
                               co...`
- `quat_spectral_layer_2d` (function) `progs/topogpt3/topogpt3.c:695` `static void quat_spectral_layer_2d(
    const float *x, float *y,
    const float *kr_w, const fl...`
- `spectral_ae_encode` (function) `progs/topogpt3/topogpt3.c:785` `static void spectral_ae_encode(const float *x, float *z, const LayerWeights *lw)`
- `spectral_ae_decode` (function) `progs/topogpt3/topogpt3.c:793` `static void spectral_ae_decode(const float *z, float *x, const LayerWeights *lw)`
- `process_torus_grid` (function) `progs/topogpt3/topogpt3.c:800` `static void process_torus_grid(const float *grid, float *out, const LayerWeights *lw)`
- `torus_soft_assign` (function) `progs/topogpt3/topogpt3.c:821` `static void torus_soft_assign(const float *phi1, const float *phi2,
                             ...`
- `message_passing` (function) `progs/topogpt3/topogpt3.c:843` `static void message_passing(const float *node_feat, float *out,
                             cons...`
- `torus_brain_forward` (function) `progs/topogpt3/topogpt3.c:888` `static void torus_brain_forward(const float *x, float *out, float *recon_loss,
                  ...`
- `attention_forward` (function) `progs/topogpt3/topogpt3.c:978` `static void attention_forward(const float *x, float *out, int layer_idx, int pos, int total_kv_co...`
- `moe_forward` (function) `progs/topogpt3/topogpt3.c:1078` `static void moe_forward(const float *x, float *out, const LayerWeights *lw)`
- `forward` (function) `progs/topogpt3/topogpt3.c:1128` `static void forward(const int *token_ids, int seq_len, float *logits_out)`
- `tokenize_string` (function) `progs/topogpt3/topogpt3.c:1195` `static int tokenize_string(const char *text, int *tokens, int max_tokens)`
- `apply_temperature` (function) `progs/topogpt3/topogpt3.c:1210` `static void apply_temperature(float *logits, int n, float temp)`
- `apply_repetition_penalty` (function) `progs/topogpt3/topogpt3.c:1216` `static void apply_repetition_penalty(float *logits, int n, const int *tokens,
                   ...`
- `apply_top_k` (function) `progs/topogpt3/topogpt3.c:1229` `static void apply_top_k(float *logits, int n, int k)`
- `sample` (function) `progs/topogpt3/topogpt3.c:1248` `static int sample(const float *logits, int n)`
- `load_weights` (function) `progs/topogpt3/topogpt3.c:1282` `static int load_weights(const char *path)`
- `load_weights_fp16` (function) `progs/topogpt3/topogpt3.c:1452` `static int load_weights_fp16(const char *path)`
- `load_weights_auto` (function) `progs/topogpt3/topogpt3.c:1583` `static int load_weights_auto(const char *path)` -- printf("  Layer %d loaded\n", i); } READ_TENSOR16(W.final_norm, D_MODEL); #undef SKIP_TENSOR16 #undef READ_TENSOR16...
- `time_now_ms` (function) `progs/topogpt3/topogpt3.c:1600` `static double time_now_ms(void)`
- `decode_token` (function) `progs/topogpt3/topogpt3.c:1614` `static void decode_token(int tid)`
- `load_token_file` (function) `progs/topogpt3/topogpt3.c:1629` `static int load_token_file(const char *path, int *out_ids, int max_ids)` -- if (tid < 256) { /* Map GPT-2 byte-level encoding back to original byte int n = tid; if (n < 94) n += 33; else if (n...
- `decode_token_tiktoken` (function) `progs/topogpt3/topogpt3.c:1652` `static void decode_token_tiktoken(int tid)` -- if (fread(&n, 4, 1, f) != 1) { fclose(f); return 0; } if (n > (unsigned)max_ids) n = max_ids; int count = (int)n...
- `generate_tokens` (function) `progs/topogpt3/topogpt3.c:1661` `static void generate_tokens(int *prompt_tokens, int n_prompt, int max_new_tokens,
               ...`
- `generate` (function) `progs/topogpt3/topogpt3.c:1725` `static void generate(const char *prompt, int max_new_tokens, float temperature,
                 ...`
- `interactive_mode` (function) `progs/topogpt3/topogpt3.c:1736` `static void interactive_mode(void)`
- `print_help` (function) `progs/topogpt3/topogpt3.c:1850` `static void print_help(void)`
- `main` (function) `progs/topogpt3/topogpt3.c:1885` `int main(int argc, char **argv)`


Next: [API_p18.md](API_p18.md)
