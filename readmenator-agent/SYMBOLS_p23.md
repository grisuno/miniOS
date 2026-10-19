# Symbols (page 23 of 27)
Previous: [SYMBOLS_p22.md](SYMBOLS_p22.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `wild_jump_body` | function | `progs/src/lxabi.c:573` | `static void wild_jump_body(void)` |
| `worker` | function | `progs/src/lxabi.c:201` | `static void *worker(void *arg)` |
| `SYS_exit` | macro | `progs/src/lxhello.c:21` | `#define SYS_exit` |
| `SYS_write` | macro | `progs/src/lxhello.c:20` | `#define SYS_write` |
| `lmain` | function | `progs/src/lxhello.c:46` | `int lmain(long argc, char **argv)` |
| `lx_strlen` | function | `progs/src/lxhello.c:23` | `static unsigned long lx_strlen(const char *s)` |
| `lx_syscall3` | function | `progs/src/lxhello.c:11` | `static long lx_syscall3(long n, long a1, long a2, long a3)` |
| `lx_write` | function | `progs/src/lxhello.c:29` | `static void lx_write(const char *s)` |
| `lx_write_int` | function | `progs/src/lxhello.c:33` | `static void lx_write_int(long v)` |
| `LXNET_BUF` | macro | `progs/src/lxnet.c:41` | `#define LXNET_BUF` |
| `LXNET_IP_UNKNOWN` | macro | `progs/src/lxnet.c:45` | `#define LXNET_IP_UNKNOWN` |
| `LXNET_LOOPBACK` | macro | `progs/src/lxnet.c:44` | `#define LXNET_LOOPBACK` |
| `LXNET_TCP_MSG` | macro | `progs/src/lxnet.c:43` | `#define LXNET_TCP_MSG` |
| `LXNET_UDP_MSG` | macro | `progs/src/lxnet.c:42` | `#define LXNET_UDP_MSG` |
| `LXNET_WAIT_MS` | macro | `progs/src/lxnet.c:40` | `#define LXNET_WAIT_MS` |
| `_GNU_SOURCE` | macro | `progs/src/lxnet.c:24` | `#define _GNU_SOURCE` |
| `check_misc` | function | `progs/src/lxnet.c:217` | `static void check_misc(void)` |
| `check_refused` | function | `progs/src/lxnet.c:150` | `static void check_refused(const struct sockaddr_in *peer)` |
| `check_tcp` | function | `progs/src/lxnet.c:174` | `static void check_tcp(const struct sockaddr_in *peer)` |
| `check_udp` | function | `progs/src/lxnet.c:73` | `static void check_udp(const struct sockaddr_in *peer)` |
| `dial` | function | `progs/src/lxnet.c:236` | `static int dial(const char *host, const char *port)` |
| `main` | function | `progs/src/lxnet.c:280` | `int main(int argc, char **argv)` |
| `read_all` | function | `progs/src/lxnet.c:62` | `static int read_all(int fd, char *buf, size_t len)` |
| `report` | function | `progs/src/lxnet.c:49` | `static void report(const char *name, int ok, const char *detail)` |
| `wait_for` | function | `progs/src/lxnet.c:55` | `static int wait_for(int fd, short events)` |
| `LXPROC_BAD` | macro | `progs/src/lxproc.c:31` | `#define LXPROC_BAD` |
| `LXPROC_CHILD_CODE` | macro | `progs/src/lxproc.c:29` | `#define LXPROC_CHILD_CODE` |
| `LXPROC_EXE_MAX` | macro | `progs/src/lxproc.c:27` | `#define LXPROC_EXE_MAX` |
| `LXPROC_OK` | macro | `progs/src/lxproc.c:30` | `#define LXPROC_OK` |
| `_GNU_SOURCE` | macro | `progs/src/lxproc.c:17` | `#define _GNU_SOURCE` |
| `lxproc_note` | struct | `progs/src/lxproc.c:35` | `` |
| `main` | function | `progs/src/lxproc.c:91` | `int main(void)` |
| `report_exe` | function | `progs/src/lxproc.c:50` | `static int report_exe(void)` |
| `report_fork` | function | `progs/src/lxproc.c:64` | `static int report_fork(void)` |
| `LXSECC_BAD_CODE` | macro | `progs/src/lxsecc.c:31` | `#define LXSECC_BAD_CODE` |
| `LXSECC_ERRNO_A` | macro | `progs/src/lxsecc.c:35` | `#define LXSECC_ERRNO_A` |
| `LXSECC_ERRNO_B` | macro | `progs/src/lxsecc.c:36` | `#define LXSECC_ERRNO_B` |
| `LXSECC_EXEC_CODE` | macro | `progs/src/lxsecc.c:29` | `#define LXSECC_EXEC_CODE` |
| `LXSECC_EXEC_FLAG` | macro | `progs/src/lxsecc.c:28` | `#define LXSECC_EXEC_FLAG` |
| `LXSECC_EXE_MAX` | macro | `progs/src/lxsecc.c:32` | `#define LXSECC_EXE_MAX` |
| `LXSECC_NAME` | macro | `progs/src/lxsecc.c:33` | `#define LXSECC_NAME` |
| `LXSECC_NAME_MAX` | macro | `progs/src/lxsecc.c:34` | `#define LXSECC_NAME_MAX` |
| `LXSECC_OK_CODE` | macro | `progs/src/lxsecc.c:30` | `#define LXSECC_OK_CODE` |
| `LXSECC_PAGE` | macro | `progs/src/lxsecc.c:37` | `#define LXSECC_PAGE` |
| `LXSECC_STATUS_BYTE` | macro | `progs/src/lxsecc.c:40` | `#define LXSECC_STATUS_BYTE` |
| `LXSECC_STATUS_MASK` | macro | `progs/src/lxsecc.c:38` | `#define LXSECC_STATUS_MASK` |
| `LXSECC_STATUS_SHIFT` | macro | `progs/src/lxsecc.c:39` | `#define LXSECC_STATUS_SHIFT` |
| `_GNU_SOURCE` | macro | `progs/src/lxsecc.c:13` | `#define _GNU_SOURCE` |
| `check_prctl_flags` | function | `progs/src/lxsecc.c:177` | `static void check_prctl_flags(void)` |
| `check_proc_self_exe` | function | `progs/src/lxsecc.c:197` | `static void check_proc_self_exe(const char *argv0)` |
| `child_bad_program` | function | `progs/src/lxsecc.c:165` | `static void child_bad_program(void)` |
| `child_errno_action` | function | `progs/src/lxsecc.c:100` | `static void child_errno_action(void)` |
| `child_inherit` | function | `progs/src/lxsecc.c:133` | `static void child_inherit(void)` |
| `child_kill_action` | function | `progs/src/lxsecc.c:107` | `static void child_kill_action(void)` |
| `child_no_nnp` | function | `progs/src/lxsecc.c:157` | `static void child_no_nnp(void)` |
| `child_stacked` | function | `progs/src/lxsecc.c:142` | `static void child_stacked(void)` |
| `child_strict` | function | `progs/src/lxsecc.c:150` | `static void child_strict(void)` |
| `child_wx` | function | `progs/src/lxsecc.c:116` | `static void child_wx(void)` |
| `exit_code_of` | function | `progs/src/lxsecc.c:53` | `static int exit_code_of(int st)` |
| `grandchild_inherits` | function | `progs/src/lxsecc.c:127` | `static void grandchild_inherits(void)` |
| `install_filter` | function | `progs/src/lxsecc.c:72` | `static int install_filter(unsigned getpid_action)` |
| `main` | function | `progs/src/lxsecc.c:215` | `int main(int argc, char **argv)` |
| `report` | function | `progs/src/lxsecc.c:44` | `static void report(const char *name, int ok, const char *detail)` |
| `run_child` | function | `progs/src/lxsecc.c:58` | `static int run_child(void (*body)(void))` |
| `LXSEL_BAD_FD` | macro | `progs/src/lxsel.c:29` | `#define LXSEL_BAD_FD` |
| `LXSEL_NFDS_OUT_OF_RANGE` | macro | `progs/src/lxsel.c:28` | `#define LXSEL_NFDS_OUT_OF_RANGE` |
| `LXSEL_PSELECT_TIMEOUT_NS` | macro | `progs/src/lxsel.c:32` | `#define LXSEL_PSELECT_TIMEOUT_NS` |
| `LXSEL_TIMEOUT_MS_MIN` | macro | `progs/src/lxsel.c:31` | `#define LXSEL_TIMEOUT_MS_MIN` |
| `LXSEL_TIMEOUT_US` | macro | `progs/src/lxsel.c:30` | `#define LXSEL_TIMEOUT_US` |
| `_GNU_SOURCE` | macro | `progs/src/lxsel.c:17` | `#define _GNU_SOURCE` |
| `elapsed_ms` | function | `progs/src/lxsel.c:55` | `static long elapsed_ms(struct timespec *a, struct timespec *b)` |
| `main` | function | `progs/src/lxsel.c:60` | `int main(void)` |
| `raw_pselect6` | function | `progs/src/lxsel.c:50` | `static long raw_pselect6(long nfds, fd_set *r, fd_set *w, fd_set *e,                          str...` |
| `raw_select` | function | `progs/src/lxsel.c:45` | `static long raw_select(long nfds, fd_set *r, fd_set *w, fd_set *e,                        struct ...` |
| `report` | function | `progs/src/lxsel.c:36` | `static void report(const char *name, int ok)` |
| `LXTLS_CA_BUNDLE` | macro | `progs/src/lxtls.c:34` | `#define LXTLS_CA_BUNDLE` |
| `LXTLS_CONNECT_S` | macro | `progs/src/lxtls.c:32` | `#define LXTLS_CONNECT_S` |
| `LXTLS_MAX_REDIRECTS` | macro | `progs/src/lxtls.c:33` | `#define LXTLS_MAX_REDIRECTS` |
| `LXTLS_RAND_BYTES` | macro | `progs/src/lxtls.c:35` | `#define LXTLS_RAND_BYTES` |
| `LXTLS_TIMEOUT_S` | macro | `progs/src/lxtls.c:31` | `#define LXTLS_TIMEOUT_S` |
| `lxtls_debug` | function | `progs/src/lxtls.c:46` | `static int lxtls_debug(CURL *h, curl_infotype type, char *data, size_t size, void *user)` |
| `lxtls_rand` | function | `progs/src/lxtls.c:73` | `static int lxtls_rand(void)` |
| `lxtls_sink` | function | `progs/src/lxtls.c:39` | `static size_t lxtls_sink(char *data, size_t size, size_t nmemb, void *user)` |
| `lxtls_step` | function | `progs/src/lxtls.c:65` | `static int lxtls_step(const char *name, int ok)` |
| `main` | function | `progs/src/lxtls.c:87` | `int main(int argc, char **argv)` |
| `LZ4_BOUND_DEN` | macro | `progs/src/lz4.c:31` | `#define LZ4_BOUND_DEN` |
| `LZ4_BOUND_SLACK` | macro | `progs/src/lz4.c:32` | `#define LZ4_BOUND_SLACK` |
| `LZ4_EXIT_FAIL` | macro | `progs/src/lz4.c:37` | `#define LZ4_EXIT_FAIL` |
| `LZ4_HDR_SIZE` | macro | `progs/src/lz4.c:30` | `#define LZ4_HDR_SIZE` |
| `LZ4_MAX_BLOCK` | macro | `progs/src/lz4.c:33` | `#define LZ4_MAX_BLOCK` |
| `LZ4_SEEK_END` | macro | `progs/src/lz4.c:35` | `#define LZ4_SEEK_END` |
| `fclose` | function | `progs/src/lz4.c:20` | `int fclose();` |
| `fopen` | function | `progs/src/lz4.c:19` | `void *fopen();` |
| `fread` | function | `progs/src/lz4.c:21` | `int fread();` |
| `free` | function | `progs/src/lz4.c:15` | `void free();` |
| `fseek` | function | `progs/src/lz4.c:23` | `int fseek();` |
| `ftell` | function | `progs/src/lz4.c:24` | `int ftell();` |
| `fwrite` | function | `progs/src/lz4.c:22` | `int fwrite();` |
| `kernel` | function | `progs/src/lz4.c:6` | `* * The codec lives in the kernel (lz4_kernel.c, the same one MiniFS uses), so * these tools are thin front-ends...` |
| `lz4_compress` | function | `progs/src/lz4.c:27` | `int lz4_compress(char *src, int srclen, char *dst, int dstcap);` |
| `lz4_compress_file` | function | `progs/src/lz4.c:80` | `static int lz4_compress_file(const char *src, const char *dst)` |
| `lz4_decompress` | function | `progs/src/lz4.c:28` | `int lz4_decompress(char *src, int srclen, char *dst, int dstcap);` |
| `lz4_decompress_file` | function | `progs/src/lz4.c:117` | `static int lz4_decompress_file(const char *src, const char *dst)` |
| `lz4_has` | function | `progs/src/lz4.c:39` | `static int lz4_has(const char *s, const char *needle)` |
| `lz4_read_all` | function | `progs/src/lz4.c:53` | `static char *lz4_read_all(const char *name, int *len)` |
| `lz4_write_all` | function | `progs/src/lz4.c:70` | `static int lz4_write_all(const char *name, char *data, int len)` |
| `main` | function | `progs/src/lz4.c:164` | `int main(int argc, char **argv)` |
| `printf` | function | `progs/src/lz4.c:16` | `int printf();` |
| `rewind` | function | `progs/src/lz4.c:25` | `void rewind();` |
| `strcmp` | function | `progs/src/lz4.c:17` | `int strcmp();` |
| `strlen` | function | `progs/src/lz4.c:18` | `int strlen();` |
| `LZSS_EI` | macro | `progs/src/lzss.c:26` | `#define LZSS_EI` |
| `LZSS_EJ` | macro | `progs/src/lzss.c:27` | `#define LZSS_EJ` |
| `LZSS_ENC_SLACK` | macro | `progs/src/lzss.c:39` | `#define LZSS_ENC_SLACK` |
| `LZSS_ERR_NONE` | macro | `progs/src/lzss.c:45` | `#define LZSS_ERR_NONE` |
| `LZSS_ERR_OVERFLOW` | macro | `progs/src/lzss.c:46` | `#define LZSS_ERR_OVERFLOW` |
| `LZSS_EXIT_FAIL` | macro | `progs/src/lzss.c:48` | `#define LZSS_EXIT_FAIL` |
| `LZSS_EXPAND_DEN` | macro | `progs/src/lzss.c:41` | `#define LZSS_EXPAND_DEN` |
| `LZSS_EXPAND_NUM` | macro | `progs/src/lzss.c:40` | `#define LZSS_EXPAND_NUM` |
| `LZSS_F` | macro | `progs/src/lzss.c:30` | `#define LZSS_F` |
| `LZSS_HDR_SIZE` | macro | `progs/src/lzss.c:37` | `#define LZSS_HDR_SIZE` |
| `LZSS_MAGIC0` | macro | `progs/src/lzss.c:33` | `#define LZSS_MAGIC0` |
| `LZSS_MAGIC1` | macro | `progs/src/lzss.c:34` | `#define LZSS_MAGIC1` |
| `LZSS_MAGIC2` | macro | `progs/src/lzss.c:35` | `#define LZSS_MAGIC2` |
| `LZSS_MAGIC3` | macro | `progs/src/lzss.c:36` | `#define LZSS_MAGIC3` |
| `LZSS_N` | macro | `progs/src/lzss.c:29` | `#define LZSS_N` |
| `LZSS_P` | macro | `progs/src/lzss.c:28` | `#define LZSS_P` |
| `LZSS_SEEK_END` | macro | `progs/src/lzss.c:43` | `#define LZSS_SEEK_END` |
| `LZSS_WIN` | macro | `progs/src/lzss.c:31` | `#define LZSS_WIN` |
| `fclose` | function | `progs/src/lzss.c:19` | `int fclose();` |
| `fopen` | function | `progs/src/lzss.c:18` | `void *fopen();` |
| `fread` | function | `progs/src/lzss.c:20` | `int fread();` |
| `free` | function | `progs/src/lzss.c:14` | `void free();` |
| `fseek` | function | `progs/src/lzss.c:22` | `int fseek();` |
| `ftell` | function | `progs/src/lzss.c:23` | `int ftell();` |
| `fwrite` | function | `progs/src/lzss.c:21` | `int fwrite();` |
| `lz_compress` | function | `progs/src/lzss.c:278` | `static int lz_compress(const char *src, const char *dst)` |
| `lz_decode` | function | `progs/src/lzss.c:189` | `static int lz_decode(void)` |
| `lz_decompress` | function | `progs/src/lzss.c:325` | `static int lz_decompress(const char *src, const char *dst)` |
| `lz_encode` | function | `progs/src/lzss.c:118` | `static int lz_encode(void)` |
| `lz_flush_bits` | function | `progs/src/lzss.c:93` | `static void lz_flush_bits(void)` |
| `lz_getbit` | function | `progs/src/lzss.c:173` | `static int lz_getbit(int n)` |
| `lz_has` | function | `progs/src/lzss.c:237` | `static int lz_has(const char *s, const char *needle)` |
| `lz_hdr_get` | function | `progs/src/lzss.c:229` | `static int lz_hdr_get(char *h)` |
| `lz_hdr_put` | function | `progs/src/lzss.c:218` | `static void lz_hdr_put(char *h, int size)` |
| `lz_in_getc` | function | `progs/src/lzss.c:64` | `static int lz_in_getc(void)` |
| `lz_out_literal` | function | `progs/src/lzss.c:97` | `static void lz_out_literal(int c)` |
| `lz_out_pair` | function | `progs/src/lzss.c:105` | `static void lz_out_pair(int x, int y)` |
| `lz_out_put` | function | `progs/src/lzss.c:69` | `static void lz_out_put(int c)` |
| `lz_putbit0` | function | `progs/src/lzss.c:84` | `static void lz_putbit0(void)` |
| `lz_putbit1` | function | `progs/src/lzss.c:74` | `static void lz_putbit1(void)` |
| `lz_read_all` | function | `progs/src/lzss.c:251` | `static char *lz_read_all(const char *name, int *len)` |
| `lz_write_all` | function | `progs/src/lzss.c:268` | `static int lz_write_all(const char *name, char *data, int len)` |
| `main` | function | `progs/src/lzss.c:397` | `int main(int argc, char **argv)` |
| `malloc` | function | `progs/src/lzss.c:13` | `void *malloc();` |
| `printf` | function | `progs/src/lzss.c:15` | `int printf();` |
| `rewind` | function | `progs/src/lzss.c:24` | `void rewind();` |
| `strcmp` | function | `progs/src/lzss.c:16` | `int strcmp();` |
| `strlen` | function | `progs/src/lzss.c:17` | `int strlen();` |
| `ENOMEM` | function | `progs/src/mmreuse.c:3` | `* downward mmap cursor drains until a map fails with ENOMEM (-12);` |
| `_start` | function | `progs/src/mmreuse.c:35` | `void _start(void)` |
| `exit_now` | function | `progs/src/mmreuse.c:31` | `static void exit_now(long code)` |
| `mmap_anon` | function | `progs/src/mmreuse.c:7` | `static long mmap_anon(long len)` |
| `munmap` | function | `progs/src/mmreuse.c:21` | `static long munmap(long addr, long len)` |
| `_start` | function | `progs/src/mprot.c:48` | `void _start(void)` |
| `exit_now` | function | `progs/src/mprot.c:44` | `static void exit_now(long code)` |
| `mmap_anon` | function | `progs/src/mprot.c:11` | `static long mmap_anon(long len)` |
| `mprotect_sys` | function | `progs/src/mprot.c:25` | `static long mprotect_sys(long addr, long len, long prot)` |
| `write_str` | function | `progs/src/mprot.c:36` | `static long write_str(const char *s, long n)` |
| `MMUTEX_CONTENDED` | macro | `progs/src/mthreads.h:33` | `#define MMUTEX_CONTENDED` |
| `MMUTEX_FREE` | macro | `progs/src/mthreads.h:31` | `#define MMUTEX_FREE` |
| `MMUTEX_HELD` | macro | `progs/src/mthreads.h:32` | `#define MMUTEX_HELD` |
| `MMUTEX_SPINS` | macro | `progs/src/mthreads.h:34` | `#define MMUTEX_SPINS` |
| `MTHREADS_H` | macro | `progs/src/mthreads.h:24` | `#define MTHREADS_H` |
| `MTHREAD_MAX` | macro | `progs/src/mthreads.h:29` | `#define MTHREAD_MAX` |
| `MTHREAD_STACK_SZ` | macro | `progs/src/mthreads.h:28` | `#define MTHREAD_STACK_SZ` |
| `m_syscall6` | function | `progs/src/mthreads.h:50` | `static inline long m_syscall6(long n, long a, long b, long c)` |
| `mfutex_wait` | function | `progs/src/mthreads.h:63` | `static inline long mfutex_wait(volatile int *addr, int val)` |
| `mfutex_wake` | function | `progs/src/mthreads.h:67` | `static inline long mfutex_wake(volatile int *addr, int n)` |
| `mmutex_init` | function | `progs/src/mthreads.h:71` | `static inline void mmutex_init(mmutex_t *m)` |
| `mmutex_lock` | function | `progs/src/mthreads.h:75` | `static inline void mmutex_lock(mmutex_t *m)` |
| `mmutex_t` | struct | `progs/src/mthreads.h:38` | `` |
| `mmutex_unlock` | function | `progs/src/mthreads.h:90` | `static inline void mmutex_unlock(mmutex_t *m)` |
| `mthread_create` | function | `progs/src/mthreads.h:117` | `static int mthread_create(mthread_t *t, void *(*fn)(void *), void *arg)` |
| `mthread_entry` | function | `progs/src/mthreads.h:98` | `static void mthread_entry(void *p)` |
| `mthread_join` | function | `progs/src/mthreads.h:144` | `static int mthread_join(mthread_t t, void **retval)` |
| `mthread_slot_t` | struct | `progs/src/mthreads.h:42` | `` |
| `mthread_t` | type_alias | `progs/src/mthreads.h:35` | `typedef int mthread_t;` |
| `myield` | function | `progs/src/mthreads.h:59` | `static inline void myield(void)` |
| `MTOP_DISK_BUF` | macro | `progs/src/mtop.c:47` | `#define MTOP_DISK_BUF` |
| `MTOP_DISK_MAX` | macro | `progs/src/mtop.c:48` | `#define MTOP_DISK_MAX` |
| `MTOP_HIST` | macro | `progs/src/mtop.c:46` | `#define MTOP_HIST` |
| `MTOP_MINFO` | macro | `progs/src/mtop.c:49` | `#define MTOP_MINFO` |
| `close` | function | `progs/src/mtop.c:43` | `int close();` |
| `emit` | function | `progs/src/mtop.c:90` | `static void emit(char *s)` |
| `fclose` | function | `progs/src/mtop.c:39` | `int fclose();` |
| `fopen` | function | `progs/src/mtop.c:38` | `void *fopen();` |
| `fread` | function | `progs/src/mtop.c:40` | `int fread();` |
| `main` | function | `progs/src/mtop.c:531` | `int main(int argc, char **argv)` |
| `mtop_atoi` | function | `progs/src/mtop.c:117` | `static int mtop_atoi(char *s)` |
| `mtop_bar` | function | `progs/src/mtop.c:179` | `static void mtop_bar(long v, long max, int w)` |
| `mtop_clear` | function | `progs/src/mtop.c:113` | `static void mtop_clear(void)` |
| `mtop_clear_ansi` | function | `progs/src/mtop.c:103` | `static void mtop_clear_ansi(void)` |
| `mtop_cpu` | function | `progs/src/mtop.c:253` | `static long mtop_cpu(long *count, long *busy)` |
| `mtop_disk_open` | function | `progs/src/mtop.c:289` | `static void mtop_disk_open(void)` |
| `mtop_disk_read` | function | `progs/src/mtop.c:313` | `static long mtop_disk_read(long *bytes)` |
| `mtop_frame` | function | `progs/src/mtop.c:355` | `static void mtop_frame(int n)` |
| `mtop_hist_max` | function | `progs/src/mtop.c:194` | `static long mtop_hist_max(long *h, int n)` |
| `mtop_hist_push` | function | `progs/src/mtop.c:204` | `static void mtop_hist_push(long *h, long v)` |
| `mtop_key` | function | `progs/src/mtop.c:80` | `static long mtop_key(void)` |
| `mtop_mem` | function | `progs/src/mtop.c:242` | `static long mtop_mem(long *used, long *freeb, long *total)` |
| `mtop_minfo` | function | `progs/src/mtop.c:84` | `static long mtop_minfo(long sel, long *o1, long *o2)` |
| `mtop_net_probe` | function | `progs/src/mtop.c:337` | `static long mtop_net_probe(long *dns_ms, long *sock_ok)` |
| `mtop_put2` | function | `progs/src/mtop.c:158` | `static void mtop_put2(int v)` |
| `mtop_put_kb` | function | `progs/src/mtop.c:163` | `static void mtop_put_kb(long kb)` |
| `mtop_putu` | function | `progs/src/mtop.c:136` | `static void mtop_putu(long v)` |
| `mtop_quit_key` | function | `progs/src/mtop.c:94` | `static int mtop_quit_key(long k)` |
| `mtop_rtc` | function | `progs/src/mtop.c:76` | `static long mtop_rtc(int *h, int *m, int *s)` |
| `mtop_spark` | function | `progs/src/mtop.c:214` | `static void mtop_spark(long *h, int n)` |
| `mtop_time` | function | `progs/src/mtop.c:72` | `static long mtop_time(void)` |
| `net_dns_resolve` | function | `progs/src/mtop.c:44` | `int net_dns_resolve();` |
| `putchar` | function | `progs/src/mtop.c:35` | `int putchar();` |
| `rewind` | function | `progs/src/mtop.c:41` | `void rewind();` |
| `sc3` | function | `progs/src/mtop.c:63` | `static long sc3(long n, long a1, long a2, long a3)` |
| `socket` | function | `progs/src/mtop.c:42` | `int socket();` |
| `strcmp` | function | `progs/src/mtop.c:37` | `int strcmp();` |
| `strlen` | function | `progs/src/mtop.c:36` | `int strlen();` |
| `syscall` | function | `progs/src/mtop.c:12` | `* * All system figures come from the MINFO syscall (251): heap used / * free, ramdisk used / cap, MiniFS free /...` |
| `lmain` | function | `progs/src/mvrn.c:32` | `int lmain(void)` |
| `mvrn_exit` | function | `progs/src/mvrn.c:20` | `static void mvrn_exit(long code)` |
| `mvrn_fail` | function | `progs/src/mvrn.c:24` | `static void mvrn_fail(int step)` |
| `mvrn_sc3` | function | `progs/src/mvrn.c:9` | `static long mvrn_sc3(long n, long a1, long a2, long a3)` |
| `mvrn_write` | function | `progs/src/mvrn.c:16` | `static void mvrn_write(const char *s, unsigned long len)` |
| `_start` | function | `progs/src/nx.c:23` | `void _start(void)` |
| `exit_now` | function | `progs/src/nx.c:19` | `static void exit_now(long code)` |
| `write_str` | function | `progs/src/nx.c:11` | `static long write_str(const char *s, long n)` |
| `BUF_MS` | macro | `progs/src/opl3.c:32` | `#define BUF_MS` |
| `F_NUM_FACTOR` | macro | `progs/src/opl3.c:34` | `#define F_NUM_FACTOR` |
| `MONO_BYTES` | macro | `progs/src/opl3.c:30` | `#define MONO_BYTES` |
| `SAMPLE_RATE` | macro | `progs/src/opl3.c:28` | `#define SAMPLE_RATE` |
| `STEREO_FRAMES` | macro | `progs/src/opl3.c:29` | `#define STEREO_FRAMES` |
| `SYS_SB16_OPEN` | macro | `progs/src/opl3.c:22` | `#define SYS_SB16_OPEN` |
| `SYS_SB16_SUBMIT` | macro | `progs/src/opl3.c:23` | `#define SYS_SB16_SUBMIT` |
| `SYS_TIME` | macro | `progs/src/opl3.c:21` | `#define SYS_TIME` |
| `SYS_WRITE` | macro | `progs/src/opl3.c:24` | `#define SYS_WRITE` |
| `busy_ms` | function | `progs/src/opl3.c:46` | `static void busy_ms(long ms)` |
| `main` | function | `progs/src/opl3.c:107` | `int main(void)` |
| `note_t` | struct | `progs/src/opl3.c:102` | `` |
| `opl3_note` | function | `progs/src/opl3.c:69` | `static void opl3_note(opl3_chip *chip, unsigned block, unsigned fnum, int on)` |
| `opl3_set_instrument` | function | `progs/src/opl3.c:52` | `static void opl3_set_instrument(opl3_chip *chip)` |
| `render` | function | `progs/src/opl3.c:77` | `static void render(opl3_chip *chip, long ms, long *fail)` |
| `sys_open` | function | `progs/src/opl3.c:39` | `static long sys_open(long on)` |
| `sys_submit` | function | `progs/src/opl3.c:42` | `static long sys_submit(const void *buf, long len)` |
| `sys_time` | function | `progs/src/opl3.c:36` | `static long sys_time(void)` |
| `_start` | function | `progs/src/pcmap.c:75` | `void _start(void)` |
| `sc_exit` | function | `progs/src/pcmap.c:42` | `static void sc_exit(long code)` |
| `sc_fnv` | function | `progs/src/pcmap.c:46` | `static unsigned long sc_fnv(const char *p, long n)` |
| `sc_hex8` | function | `progs/src/pcmap.c:56` | `static void sc_hex8(unsigned long v, char *out)` |
| `sc_mmap` | function | `progs/src/pcmap.c:21` | `static long sc_mmap(long len, long prot, long flags, long fd, long off)` |
| `sc_munmap` | function | `progs/src/pcmap.c:65` | `static long sc_munmap(long addr, long len)` |
| `sc_open` | function | `progs/src/pcmap.c:12` | `static long sc_open(const char *p)` |
| `sc_write` | function | `progs/src/pcmap.c:34` | `static long sc_write(long fd, const char *s, long n)` |
| `PIP_EXEC_FAILED` | macro | `progs/src/pip.c:26` | `#define PIP_EXEC_FAILED` |
| `PIP_MODULE_FLAG` | macro | `progs/src/pip.c:21` | `#define PIP_MODULE_FLAG` |
| `PIP_MODULE_NAME` | macro | `progs/src/pip.c:22` | `#define PIP_MODULE_NAME` |
| `PIP_PREFIX_WORDS` | macro | `progs/src/pip.c:24` | `#define PIP_PREFIX_WORDS` |
| `PIP_PYTHON_PATH` | macro | `progs/src/pip.c:19` | `#define PIP_PYTHON_PATH` |
| `main` | function | `progs/src/pip.c:45` | `int main(int argc, char **argv)` |
| `pip_note` | struct | `progs/src/pip.c:30` | `` |
| `lmain` | function | `progs/src/pollready.c:63` | `int lmain(long argc, char **argv)` |
| `p_atoi` | function | `progs/src/pollready.c:40` | `static int p_atoi(const char *s)` |
| `p_parse_ip` | function | `progs/src/pollready.c:46` | `static int p_parse_ip(const char *s, unsigned char out[4])` |
| `p_puts` | function | `progs/src/pollready.c:36` | `static void p_puts(long fd, const char *s)` |
| `p_strlen` | function | `progs/src/pollready.c:30` | `static unsigned long p_strlen(const char *s)` |
| `p_write` | function | `progs/src/pollready.c:26` | `static long p_write(long fd, const char *s, long n)` |
| `BUF` | macro | `progs/src/sbtone.c:26` | `#define BUF` |
| `RATE` | macro | `progs/src/sbtone.c:25` | `#define RATE` |
| `SYS_SB16_OPEN` | macro | `progs/src/sbtone.c:21` | `#define SYS_SB16_OPEN` |
| `SYS_SB16_SUBMIT` | macro | `progs/src/sbtone.c:22` | `#define SYS_SB16_SUBMIT` |
| `SYS_TIME` | macro | `progs/src/sbtone.c:23` | `#define SYS_TIME` |
| `WINDOW_MS` | macro | `progs/src/sbtone.c:27` | `#define WINDOW_MS` |
| `buffers` | function | `progs/src/sbtone.c:14` | `*  * Exit code is the number of submitted buffers (0 on failure to open).  */  #include <stdio.h>...` |
| `main` | function | `progs/src/sbtone.c:36` | `int main(void)` |
| `SC_ARENA` | macro | `progs/src/scfuzz.c:16` | `#define SC_ARENA` |
| `SC_OPS` | macro | `progs/src/scfuzz.c:15` | `#define SC_OPS` |
| `SC_PAGE` | macro | `progs/src/scfuzz.c:17` | `#define SC_PAGE` |
| `SC_PAGES` | macro | `progs/src/scfuzz.c:18` | `#define SC_PAGES` |
| `SC_T0_BASE` | macro | `progs/src/scfuzz.c:19` | `#define SC_T0_BASE` |
| `SC_T0_N` | macro | `progs/src/scfuzz.c:20` | `#define SC_T0_N` |
| `SC_T1_BASE` | macro | `progs/src/scfuzz.c:21` | `#define SC_T1_BASE` |
| `SC_T1_N` | macro | `progs/src/scfuzz.c:22` | `#define SC_T1_N` |
| `_start` | function | `progs/src/scfuzz.c:160` | `void _start(void)` |
| `guest` | function | `progs/src/scfuzz.c:7` | `* the guest (the BDD timeout then talks). All fuzz maps stay inside  * one private 4 MB arena (pa...` |
| `sc_exit` | function | `progs/src/scfuzz.c:61` | `static void sc_exit(long code)` |
| `sc_fold` | function | `progs/src/scfuzz.c:76` | `static unsigned long sc_fold(unsigned long h, unsigned long v)` |
| `sc_hex8` | function | `progs/src/scfuzz.c:88` | `static void sc_hex8(unsigned long v, char *out)` |
| `sc_mprotect` | function | `progs/src/scfuzz.c:38` | `static long sc_mprotect(long addr, long len, long prot)` |
| `sc_munmap` | function | `progs/src/scfuzz.c:49` | `static long sc_munmap(long addr, long len)` |
| `sc_rng` | function | `progs/src/scfuzz.c:67` | `static unsigned long sc_rng(unsigned long *s)` |
| `sc_thread1` | function | `progs/src/scfuzz.c:154` | `static void *sc_thread1(void *arg)` |
| `sc_worker` | function | `progs/src/scfuzz.c:97` | `static unsigned long sc_worker(int me, unsigned long seed)` |
| `sc_write` | function | `progs/src/scfuzz.c:53` | `static long sc_write(long fd, const char *s, long n)` |
| `expand` | function | `progs/src/shell.py:30` | `def expand(line, env)` |
| `main` | function | `progs/src/shell.py:36` | `def main()` |
| `run_capture` | function | `progs/src/shell.py:20` | `def run_capture(cmd, args)` |
| `SIGN_DESC_BYTES` | macro | `progs/src/sign.c:52` | `#define SIGN_DESC_BYTES` |
| `SIGN_EHDR_SIZE` | macro | `progs/src/sign.c:48` | `#define SIGN_EHDR_SIZE` |
| `SIGN_EM_X86_64` | macro | `progs/src/sign.c:44` | `#define SIGN_EM_X86_64` |
| `SIGN_ET_DYN` | macro | `progs/src/sign.c:43` | `#define SIGN_ET_DYN` |
| `SIGN_ET_EXEC` | macro | `progs/src/sign.c:42` | `#define SIGN_ET_EXEC` |
| `SIGN_EXIT_FAIL` | macro | `progs/src/sign.c:40` | `#define SIGN_EXIT_FAIL` |
| `SIGN_KEY_ID` | macro | `progs/src/sign.c:39` | `#define SIGN_KEY_ID` |
| `SIGN_MAX_FILE` | macro | `progs/src/sign.c:56` | `#define SIGN_MAX_FILE` |
| `SIGN_NOTE_HDR` | macro | `progs/src/sign.c:51` | `#define SIGN_NOTE_HDR` |
| `SIGN_NOTE_TOTAL` | macro | `progs/src/sign.c:54` | `#define SIGN_NOTE_TOTAL` |
| `SIGN_NOTE_TYPE` | macro | `progs/src/sign.c:55` | `#define SIGN_NOTE_TYPE` |
| `SIGN_PHDR_SIZE` | macro | `progs/src/sign.c:49` | `#define SIGN_PHDR_SIZE` |
| `SIGN_PT_LOAD` | macro | `progs/src/sign.c:45` | `#define SIGN_PT_LOAD` |
| `SIGN_PT_NOTE` | macro | `progs/src/sign.c:46` | `#define SIGN_PT_NOTE` |
| `SIGN_SEEK_END` | macro | `progs/src/sign.c:57` | `#define SIGN_SEEK_END` |
| `SIGN_SHDR_SIZE` | macro | `progs/src/sign.c:50` | `#define SIGN_SHDR_SIZE` |
| `SIGN_SHT_NOTE` | macro | `progs/src/sign.c:47` | `#define SIGN_SHT_NOTE` |
| `SIGN_SIG_BYTES` | macro | `progs/src/sign.c:53` | `#define SIGN_SIG_BYTES` |
| `below` | function | `progs/src/sign.c:195` | `* every other op below (`\|`, `<<`) is low-32 exact. */ static void sign_rotr(unsigned int *lo, un...` |
| `bits` | function | `progs/src/sign.c:672` | `* values here always fit 32 bits (limbs below 2^16, carries and  * products below 2^32), so the s...` |
| `fclose` | function | `progs/src/sign.c:31` | `int fclose();` |
| `fe_add` | function | `progs/src/sign.c:617` | `static void fe_add(unsigned int *r, unsigned int *a, unsigned int *b)` |
| `fe_cmov` | function | `progs/src/sign.c:573` | `static void fe_cmov(unsigned int *r, unsigned int *b, unsigned int flag)` |
| `fe_copy` | function | `progs/src/sign.c:549` | `static void fe_copy(unsigned int *r, unsigned int *a)` |
| `fe_curved` | function | `progs/src/sign.c:812` | `static void fe_curved(unsigned int *d, unsigned int *d2)` |
| `fe_foldadd` | function | `progs/src/sign.c:690` | `static void fe_foldadd(unsigned int *row, int at, unsigned int x)` |
| `fe_frombytes` | function | `progs/src/sign.c:790` | `static void fe_frombytes(unsigned int *r, char *b)` |
| `fe_ge` | function | `progs/src/sign.c:586` | `static unsigned int fe_ge(unsigned int *a, unsigned int *b)` |
| `fe_inv` | function | `progs/src/sign.c:771` | `static void fe_inv(unsigned int *r, unsigned int *a)` |
| `fe_mul` | function | `progs/src/sign.c:696` | `static void fe_mul(unsigned int *r, unsigned int *a, unsigned int *b)` |
| `fe_off` | function | `progs/src/sign.c:845` | `static unsigned int *fe_off(unsigned int *p, int n)` |
| `fe_one` | function | `progs/src/sign.c:567` | `static void fe_one(unsigned int *r)` |
| `fe_rawsub` | function | `progs/src/sign.c:601` | `static void fe_rawsub(unsigned int *r, unsigned int *a, unsigned int *b)` |
| `fe_sq` | function | `progs/src/sign.c:766` | `static void fe_sq(unsigned int *r, unsigned int *a)` |
| `fe_sub` | function | `progs/src/sign.c:636` | `static void fe_sub(unsigned int *r, unsigned int *a, unsigned int *b)` |
| `fe_tobytes` | function | `progs/src/sign.c:800` | `static void fe_tobytes(char *b, unsigned int *a)` |
| `fe_zero` | function | `progs/src/sign.c:558` | `static void fe_zero(unsigned int *r)` |
| `fopen` | function | `progs/src/sign.c:30` | `void *fopen();` |
| `fread` | function | `progs/src/sign.c:32` | `int fread();` |
| `free` | function | `progs/src/sign.c:37` | `void free();` |
| `fseek` | function | `progs/src/sign.c:34` | `int fseek();` |
| `ftell` | function | `progs/src/sign.c:35` | `int ftell();` |
| `fwrite` | function | `progs/src/sign.c:33` | `int fwrite();` |
| `ge_add` | function | `progs/src/sign.c:860` | `static void ge_add(unsigned int *r, unsigned int *p, unsigned int *q, unsigned int *d2)` |
| `ge_cmov` | function | `progs/src/sign.c:850` | `static void ge_cmov(unsigned int *r, unsigned int *b, unsigned int flag)` |
| `ge_copy` | function | `progs/src/sign.c:829` | `static void ge_copy(unsigned int *r, unsigned int *a)` |
| `ge_double` | function | `progs/src/sign.c:892` | `static void ge_double(unsigned int *r, unsigned int *p)` |
| `ge_scalarmult` | function | `progs/src/sign.c:926` | `static void ge_scalarmult(unsigned int *r, unsigned int *p, char *s, unsigned int *d2)` |
| `main` | function | `progs/src/sign.c:1657` | `int main(int argc, char **argv)` |
| `malloc` | function | `progs/src/sign.c:36` | `void *malloc();` |
| `printf` | function | `progs/src/sign.c:28` | `int printf();` |
| `sc_mod_l` | function | `progs/src/sign.c:951` | `static void sc_mod_l(unsigned int *r, unsigned int *t16)` |
| `sc_mul_add` | function | `progs/src/sign.c:1013` | `static void sc_mul_add(unsigned int *r, unsigned int *a, unsigned int *b, unsigned int *c)` |
| `sign_add3` | function | `progs/src/sign.c:237` | `static unsigned int sign_add3(unsigned int *s, unsigned int a, unsigned int b, unsigned int c)` |
| `sign_append` | function | `progs/src/sign.c:1393` | `static int sign_append(char *name, char *img, int size, int shoff, int shnum, int shentsize,     ...` |
| `sign_be32` | function | `progs/src/sign.c:247` | `static unsigned int sign_be32(char *p, int off)` |
| `sign_block` | function | `progs/src/sign.c:253` | `static void sign_block(void)` |
| `sign_borrow2` | function | `progs/src/sign.c:230` | `static unsigned int sign_borrow2(unsigned int x, unsigned int y, unsigned int s)` |
| `sign_byte` | function | `progs/src/sign.c:111` | `static unsigned int sign_byte(char *p, int i)` |
| `sign_copy` | function | `progs/src/sign.c:119` | `static void sign_copy(char *dst, char *src, int n)` |
| `sign_digest` | function | `progs/src/sign.c:1112` | `static void sign_digest(char *sig, char *digest)` |
| `sign_digest_of` | function | `progs/src/sign.c:1307` | `static int sign_digest_of(char *img, int size, int entry, char *ph, int phnum, char *digest)` |
| `sign_feed32` | function | `progs/src/sign.c:490` | `static void sign_feed32(unsigned int v)` |
| `sign_file` | function | `progs/src/sign.c:1529` | `static int sign_file(char *name)` |
| `sign_hexval` | function | `progs/src/sign.c:89` | `static unsigned int sign_hexval(char c)` |
| `sign_key_init` | function | `progs/src/sign.c:500` | `static void sign_key_init(void)` |
| `sign_le16` | function | `progs/src/sign.c:136` | `static unsigned int sign_le16(char *p, int off)` |
| `sign_le32` | function | `progs/src/sign.c:141` | `static unsigned int sign_le32(char *p, int off)` |
| `sign_note_span` | function | `progs/src/sign.c:1273` | `static int sign_note_span(char *img, int off, int len, int *desc)` |
| `sign_offok` | function | `progs/src/sign.c:180` | `static int sign_offok(char *p, int off, int *lo)` |
| `sign_patch_notes` | function | `progs/src/sign.c:1356` | `static int sign_patch_notes(char *img, int size, char *ph, int phnum, char *desc)` |
| `sign_points_init` | function | `progs/src/sign.c:1081` | `static void sign_points_init(void)` |
| `sign_put32` | function | `progs/src/sign.c:147` | `static void sign_put32(char *p, int off, unsigned int v)` |
| `sign_read` | function | `progs/src/sign.c:1232` | `static char *sign_read(char *name, int *len)` |
| `sign_rev32` | function | `progs/src/sign.c:1070` | `static void sign_rev32(char *b)` |
| `sign_selftest` | function | `progs/src/sign.c:1637` | `static int sign_selftest(void)` |
| `sign_sha_final` | function | `progs/src/sign.c:442` | `static void sign_sha_final(char *out)` |
| `sign_sha_init` | function | `progs/src/sign.c:387` | `static void sign_sha_init(void)` |
| `sign_sha_update` | function | `progs/src/sign.c:410` | `static void sign_sha_update(char *data, int len)` |
| `sign_strlen` | function | `progs/src/sign.c:128` | `static int sign_strlen(char *s)` |
| `sign_unhex` | function | `progs/src/sign.c:100` | `static void sign_unhex(char *out, char *in, int n)` |
| `sign_write` | function | `progs/src/sign.c:1260` | `static int sign_write(char *name, char *data, int len)` |
| `strcmp` | function | `progs/src/sign.c:29` | `int strcmp();` |
| `SPIN_WLA` | macro | `progs/src/spin.c:58` | `#define SPIN_WLA` |
| `SPIN_WLB` | macro | `progs/src/spin.c:59` | `#define SPIN_WLB` |
| `SPIN_WLH` | macro | `progs/src/spin.c:57` | `#define SPIN_WLH` |
| `SPIN_WLW` | macro | `progs/src/spin.c:56` | `#define SPIN_WLW` |
| `lmain` | function | `progs/src/spin.c:225` | `int lmain(long argc, char **argv)` |
| `lx_atoi` | function | `progs/src/spin.c:42` | `static long lx_atoi(const char *s)` |
| `lx_strlen` | function | `progs/src/spin.c:20` | `static unsigned long lx_strlen(const char *s)` |
| `lx_syscall3` | function | `progs/src/spin.c:11` | `static long lx_syscall3(long n, long a1, long a2, long a3)` |
| `lx_write` | function | `progs/src/spin.c:26` | `static void lx_write(const char *s)` |
| `lx_write_int` | function | `progs/src/spin.c:30` | `static void lx_write_int(long v)` |
| `spin_box_ok` | function | `progs/src/spin.c:82` | `static int spin_box_ok(const char *box)` |
| `spin_emit` | function | `progs/src/spin.c:114` | `static int spin_emit(const char *box, unsigned int seq,         const unsigned char *msg, long mlen)` |
| `spin_hdr` | function | `progs/src/spin.c:73` | `static void spin_hdr(unsigned char *d, unsigned long id, unsigned long op,         unsigned long ...` |
| `spin_hex8` | function | `progs/src/spin.c:95` | `static void spin_hex8(unsigned int v, char *dst)` |
| `spin_pixels` | function | `progs/src/spin.c:169` | `static void spin_pixels(long off)` |
| `spin_raw_file` | function | `progs/src/spin.c:145` | `static int spin_raw_file(const char *box)` |
| `spin_u32` | function | `progs/src/spin.c:66` | `static void spin_u32(unsigned char *d, unsigned long v)` |
| `spin_wl` | function | `progs/src/spin.c:181` | `static int spin_wl(const char *box, const char *narg)` |
| `spin_write_all` | function | `progs/src/spin.c:104` | `static long spin_write_all(long fd, const unsigned char *buf, long len)` |
| `add` | function | `progs/src/test.c:1` | `int add(int a, int b)` |
| `main` | function | `progs/src/test.c:2` | `int main(void)` |
| `check` | function | `progs/src/test.lua:12` | `` |
| `read_file` | function | `progs/src/test.lua:30` | `` |
| `test_bin_aes` | function | `progs/src/test.lua:175` | `` |
| `test_bin_cp` | function | `progs/src/test.lua:135` | `` |
| `test_bin_freedom` | function | `progs/src/test.lua:205` | `` |
| `test_bin_json` | function | `progs/src/test.lua:194` | `` |
| `test_bin_lz4` | function | `progs/src/test.lua:141` | `` |
| `test_bin_lzss` | function | `progs/src/test.lua:158` | `` |
| `test_dlmalloc` | function | `progs/src/test.lua:80` | `` |
| `test_filesystem` | function | `progs/src/test.lua:53` | `` |
| `test_ftest` | function | `progs/src/test.lua:90` | `` |
| `test_hello` | function | `progs/src/test.lua:85` | `` |
| `test_ld` | function | `progs/src/test.lua:100` | `` |
| `test_minigcc` | function | `progs/src/test.lua:95` | `` |
| `test_module_bindings` | function | `progs/src/test.lua:40` | `` |
| `test_spawn_preserves_interpreter` | function | `progs/src/test.lua:122` | `` |
| `test_stb` | function | `progs/src/test.lua:75` | `` |
| `test_toolchain_roundtrip` | function | `progs/src/test.lua:112` | `` |
| `test_xxhash` | function | `progs/src/test.lua:70` | `` |
| `write_file` | function | `progs/src/test.lua:22` | `` |
| `check` | function | `progs/src/test.py:15` | `def check(name, cond, detail)` |
| `main` | function | `progs/src/test.py:261` | `def main()` |
| `safe_run` | function | `progs/src/test.py:25` | `def safe_run()` |
| `test_bin_aes` | function | `progs/src/test.py:209` | `def test_bin_aes()` |
| `test_bin_cp` | function | `progs/src/test.py:148` | `def test_bin_cp()` |
| `test_bin_freedom` | function | `progs/src/test.py:253` | `def test_bin_freedom()` |
| `test_bin_json` | function | `progs/src/test.py:239` | `def test_bin_json()` |
| `test_bin_lz4` | function | `progs/src/test.py:153` | `def test_bin_lz4()` |
| `test_bin_lzss` | function | `progs/src/test.py:181` | `def test_bin_lzss()` |
| `test_dlmalloc` | function | `progs/src/test.py:82` | `def test_dlmalloc()` |
| `test_filesystem` | function | `progs/src/test.py:56` | `def test_filesystem()` |
| `test_ftest` | function | `progs/src/test.py:92` | `def test_ftest()` |
| `test_hello` | function | `progs/src/test.py:87` | `def test_hello()` |
| `test_ld` | function | `progs/src/test.py:102` | `def test_ld()` |
| `test_minigcc` | function | `progs/src/test.py:97` | `def test_minigcc()` |
| `test_module_bindings` | function | `progs/src/test.py:38` | `def test_module_bindings()` |
| `test_spawn_preserves_interpreter` | function | `progs/src/test.py:134` | `def test_spawn_preserves_interpreter()` |
| `test_stb` | function | `progs/src/test.py:77` | `def test_stb()` |
| `test_toolchain_roundtrip` | function | `progs/src/test.py:119` | `def test_toolchain_roundtrip()` |
| `test_xxhash` | function | `progs/src/test.py:72` | `def test_xxhash()` |
| `_asyncio_double` | function | `progs/src/test_py.py:79` | `def _asyncio_double(n, ms)` |
| `_asyncio_main` | function | `progs/src/test_py.py:84` | `def _asyncio_main()` |
| `_asyncio_wire_check` | function | `progs/src/test_py.py:88` | `def _asyncio_wire_check(host, port)` |
| `_one` | function | `progs/src/test_py.py:89` | `def _one()` |
| `check` | function | `progs/src/test_py.py:12` | `def check(name, cond)` |
| `BUFSZ` | macro | `progs/src/thdemo.c:24` | `#define BUFSZ` |
| `EXPECTED_N` | macro | `progs/src/thdemo.c:26` | `#define EXPECTED_N` |
| `EXPECTED_SUM` | macro | `progs/src/thdemo.c:27` | `#define EXPECTED_SUM` |
| `NCONS` | macro | `progs/src/thdemo.c:22` | `#define NCONS` |
| `NPROD` | macro | `progs/src/thdemo.c:21` | `#define NPROD` |
| `PER_PROD` | macro | `progs/src/thdemo.c:23` | `#define PER_PROD` |
| `consumer` | function | `progs/src/thdemo.c:57` | `static void *consumer(void *p)` |
| `main` | function | `progs/src/thdemo.c:82` | `int main(void)` |
| `producer` | function | `progs/src/thdemo.c:36` | `static void *producer(void *p)` |
| `threads` | function | `progs/src/thdemo.c:3` | `* * Ten threads (1 main + 5 producers + 4 consumers) share one address * space through thread_spawn (MiniOS syscall...` |
| `main` | function | `progs/src/w1.c:3` | `int main(void)` |
| `write` | function | `progs/src/w1.c:1` | `int write(int fd, char *buf, int n);` |
| `_DEFAULT_SOURCE` | macro | `progs/tls_u/tls_u_main.c:15` | `#define _DEFAULT_SOURCE` |
| `_POSIX_C_SOURCE` | macro | `progs/tls_u/tls_u_main.c:14` | `#define _POSIX_C_SOURCE` |
| `main` | function | `progs/tls_u/tls_u_main.c:61` | `int main(int argc, char **argv)` |
| `parse_port` | function | `progs/tls_u/tls_u_main.c:47` | `static int parse_port(const char *s)` |
| `syscall` | function | `progs/tls_u/tls_u_main.c:10` | `* the MiniOS DNS syscall (200, sig 0: error-check only, sends nothing).  * The kernel keeps servi...` |
| `_DEFAULT_SOURCE` | macro | `progs/tls_u/tls_u_port.c:13` | `#define _DEFAULT_SOURCE` |
| `_POSIX_C_SOURCE` | macro | `progs/tls_u/tls_u_port.c:12` | `#define _POSIX_C_SOURCE` |
| `answer` | function | `progs/tls_u/tls_u_port.c:163` | `* answer (some resolvers go IPv6-only on the first query). */ memset(&hints, 0, sizeof(hints));` |
| `net_dns_resolve` | function | `progs/tls_u/tls_u_port.c:183` | `int net_dns_resolve(const char *host)` |
| `parse_quad` | function | `progs/tls_u/tls_u_port.c:122` | `static int parse_quad(const char *s, unsigned *ip_out)` |
| `sockets` | function | `progs/tls_u/tls_u_port.c:5` | `* sockets: on the host they are host sockets (used by the  * openssl-s_server interop test), insi...` |
| `tls_close` | function | `progs/tls_u/tls_u_port.c:67` | `void tls_close(int fd)` |
| `tls_free_fd` | function | `progs/tls_u/tls_u_port.c:66` | `void tls_free_fd(int fd);` |
| `tls_now_days` | function | `progs/tls_u/tls_u_port.c:72` | `long tls_now_days(void)` |
| `tls_random` | function | `progs/tls_u/tls_u_port.c:78` | `void tls_random(unsigned char *out, unsigned len)` |
| `tls_u_close` | function | `progs/tls_u/tls_u_port.c:55` | `void tls_u_close(int fd)` |
| `tls_u_recv` | function | `progs/tls_u/tls_u_port.c:39` | `int tls_u_recv(int fd, char *buf, int len)` |
| `tls_u_recv_timeout` | function | `progs/tls_u/tls_u_port.c:44` | `int tls_u_recv_timeout(int fd, char *buf, int len, unsigned long ms)` |
| `tls_u_resolve` | function | `progs/tls_u/tls_u_port.c:147` | `int tls_u_resolve(const char *host, unsigned *ip_out)` |
| `u_raw_syscall3` | function | `progs/tls_u/tls_u_port.c:99` | `static long u_raw_syscall3(long n, long a1, long a2, long a3)` |
| `D_HEAD` | macro | `progs/topogpt3/topogpt3.c:70` | `#define D_HEAD` |
| `D_LAT_Q` | macro | `progs/topogpt3/topogpt3.c:82` | `#define D_LAT_Q` |
| `D_MODEL` | macro | `progs/topogpt3/topogpt3.c:66` | `#define D_MODEL` |
| `D_QUAT` | macro | `progs/topogpt3/topogpt3.c:71` | `#define D_QUAT` |
| `EMBED_INNER` | macro | `progs/topogpt3/topogpt3.c:90` | `#define EMBED_INNER` |
| `EOS_TOKEN` | macro | `progs/topogpt3/topogpt3.c:89` | `#define EOS_TOKEN` |
| `EPS_RMS` | macro | `progs/topogpt3/topogpt3.c:92` | `#define EPS_RMS` |

Next: [SYMBOLS_p24.md](SYMBOLS_p24.md)
