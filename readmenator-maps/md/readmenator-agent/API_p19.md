# API (page 19 of 21)
Previous: [API_p18.md](API_p18.md)

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

## progs/src/lxabi.c
Depends on: `headers/sched.h`, `kernel/string.c`, `kernel/time.c`
- `report` (function) `progs/src/lxabi.c:65` `static void report(const char *name, int ok, const char *detail)`
- `now_ms` (function) `progs/src/lxabi.c:75` `static long now_ms(void)`
- `busy_wait_ms` (function) `progs/src/lxabi.c:81` `static void busy_wait_ms(long ms)`
- `fork_probe` (function) `progs/src/lxabi.c:95` `static void fork_probe(uint64_t *out)` -- Raw clone(SIGCHLD) with known values in every callee-saved register and in * the argument registers; both sides...
- `regs_match` (function) `progs/src/lxabi.c:132` `static int regs_match(const uint64_t *r)`
- `check_fork_registers` (function) `progs/src/lxabi.c:138` `static void check_fork_registers(void)`
- `check_fork_cow_kernel_write` (function) `progs/src/lxabi.c:160` `static void check_fork_cow_kernel_write(void)`
- `worker` (function) `progs/src/lxabi.c:201` `static void *worker(void *arg)`
- `check_threads` (function) `progs/src/lxabi.c:215` `static void check_threads(void)`
- `detached_worker` (function) `progs/src/lxabi.c:245` `static void *detached_worker(void *arg)`
- `check_detached_reaped` (function) `progs/src/lxabi.c:251` `static void check_detached_reaped(void)`
- `signaller` (function) `progs/src/lxabi.c:275` `static void *signaller(void *arg)`
- `check_condvar` (function) `progs/src/lxabi.c:285` `static void check_condvar(void)`
- `check_pipe2_flags` (function) `progs/src/lxabi.c:307` `static void check_pipe2_flags(void)`
- `check_pipe_blocking` (function) `progs/src/lxabi.c:334` `static void check_pipe_blocking(void)`
- `check_pipe_epipe` (function) `progs/src/lxabi.c:356` `static void check_pipe_epipe(void)`
- `check_writev_pipe` (function) `progs/src/lxabi.c:382` `static void check_writev_pipe(void)`
- `check_poll` (function) `progs/src/lxabi.c:394` `static void check_poll(void)`
- `check_eventfd` (function) `progs/src/lxabi.c:418` `static void check_eventfd(void)`
- `check_close_range` (function) `progs/src/lxabi.c:443` `static void check_close_range(void)`
- `check_time` (function) `progs/src/lxabi.c:455` `static void check_time(void)`
- `check_mkdir` (function) `progs/src/lxabi.c:464` `static void check_mkdir(void)`
- `check_limits` (function) `progs/src/lxabi.c:478` `static void check_limits(void)` -- The answers glibc sizes memory from: a finite stack limit (thread stacks default to it) and a CPU count that matches...
- `mono_us` (function) `progs/src/lxabi.c:491` `static long mono_us(void)`
- `check_sleep` (function) `progs/src/lxabi.c:500` `static void check_sleep(void)` -- Sleeps really wait: nanosleep for a relative interval, clock_nanosleep until an absolute monotonic deadline, and a...
- `lxabi_sleeper` (function) `progs/src/lxabi.c:527` `static void *lxabi_sleeper(void *arg)` -- rc = clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &abs_t, NULL); waited = mono_us() - t0...
- `child_status` (function) `progs/src/lxabi.c:535` `static int child_status(void (*body)(void))` -- Fork a child that runs body, wait for it with a bounded spin and return * its wait status, or -1 when it never ended...
- `abort_from_worker_body` (function) `progs/src/lxabi.c:555` `static void abort_from_worker_body(void)`
- `lxabi_exit_group_worker` (function) `progs/src/lxabi.c:561` `static void *lxabi_exit_group_worker(void *arg)`
- `exit_group_from_worker_body` (function) `progs/src/lxabi.c:567` `static void exit_group_from_worker_body(void)`
- `wild_jump_body` (function) `progs/src/lxabi.c:573` `static void wild_jump_body(void)`
- `process` (function) `progs/src/lxabi.c:581` `* process (never a kernel panic), and kill(pid, 0) or a harmless signal
 * leaves the target aliv...`
- `check_uid_gid` (function) `progs/src/lxabi.c:642` `static void check_uid_gid(void)` -- Every process runs as root (uid/gid 0); glibc and CPython's startup * read these, and -ENOSYS made them answer...
- `check_rename_dir` (function) `progs/src/lxabi.c:649` `static void check_rename_dir(void)` -- Directory rename within one parent: Linux allows it, and pip's * uninstall stashes a whole dist-info/pycache...
- `copy_dentry_name` (function) `progs/src/lxabi.c:715` `static void copy_dentry_name(char *dst, size_t cap, const char *src)` -- getdents64 (217): a directory fd enumerates MiniFS entries with the right d_type and resumes across calls; a regular...
- `check_getdents64` (function) `progs/src/lxabi.c:722` `static void check_getdents64(void)`
- `main` (function) `progs/src/lxabi.c:789` `int main(void)`

## progs/src/lxhello.c
- `lx_syscall3` (function) `progs/src/lxhello.c:11` `static long lx_syscall3(long n, long a1, long a2, long a3)`
- `lx_strlen` (function) `progs/src/lxhello.c:23` `static unsigned long lx_strlen(const char *s)`
- `lx_write` (function) `progs/src/lxhello.c:29` `static void lx_write(const char *s)`
- `lx_write_int` (function) `progs/src/lxhello.c:33` `static void lx_write_int(long v)`
- `lmain` (function) `progs/src/lxhello.c:46` `int lmain(long argc, char **argv)` -- static void lx_write_int(long v) { char buf[24]; int i = (int)sizeof(buf); int neg = 0; buf[--i] = 0; if (v < 0) {...

## progs/src/lxnet.c
Depends on: `kernel/string.c`
- `report` (function) `progs/src/lxnet.c:49` `static void report(const char *name, int ok, const char *detail)`
- `wait_for` (function) `progs/src/lxnet.c:55` `static int wait_for(int fd, short events)`
- `read_all` (function) `progs/src/lxnet.c:62` `static int read_all(int fd, char *buf, size_t len)` -- static void report(const char *name, int ok, const char *detail) { if (ok) printf("lxnet: %s ok\n", name); else {...
- `check_udp` (function) `progs/src/lxnet.c:73` `static void check_udp(const struct sockaddr_in *peer)`
- `check_refused` (function) `progs/src/lxnet.c:150` `static void check_refused(const struct sockaddr_in *peer)` -- A non-blocking connect to a port nobody listens on fails through poll * (POLLERR) with SO_ERROR = ECONNREFUSED...
- `check_tcp` (function) `progs/src/lxnet.c:174` `static void check_tcp(const struct sockaddr_in *peer)`
- `check_misc` (function) `progs/src/lxnet.c:217` `static void check_misc(void)`
- `dial` (function) `progs/src/lxnet.c:236` `static int dial(const char *host, const char *port)` -- if (fd >= 0) close(fd); struct addrinfo hints, *res = NULL; memset(&hints, 0, sizeof hints); hints.ai_family =...
- `main` (function) `progs/src/lxnet.c:280` `int main(int argc, char **argv)`

## progs/src/lxproc.c
Depends on: `progs/minios_abi.h`
- `report_exe` (function) `progs/src/lxproc.c:50` `static int report_exe(void)` -- uint32_t namesz; uint32_t descsz; uint32_t type; char     name[sizeof MINIOS_NOTE_NAME]; uint32_t desc; }...
- `report_fork` (function) `progs/src/lxproc.c:64` `static int report_fork(void)` -- Fork a child that exits with LXPROC_CHILD_CODE and reap it; 0 when the * outcome is one of the two the contract allows.
- `main` (function) `progs/src/lxproc.c:91` `int main(void)`

## progs/src/lxsecc.c
Depends on: `kernel/string.c`
- `report` (function) `progs/src/lxsecc.c:44` `static void report(const char *name, int ok, const char *detail)`
- `exit_code_of` (function) `progs/src/lxsecc.c:53` `static int exit_code_of(int st)` -- Exit code of a reaped child under both encodings: Linux's status word (code << 8, signal in the low bits) and...
- `run_child` (function) `progs/src/lxsecc.c:58` `static int run_child(void (*body)(void))`
- `install_filter` (function) `progs/src/lxsecc.c:72` `static int install_filter(unsigned getpid_action)` -- Filter: arch guard, getpid -> ERRNO(err_getpid), write/exit/exit_group/ * rt_sigreturn/mprotect(no PROT_EXEC)/fork...
- `child_errno_action` (function) `progs/src/lxsecc.c:100` `static void child_errno_action(void)`
- `child_kill_action` (function) `progs/src/lxsecc.c:107` `static void child_kill_action(void)`
- `child_wx` (function) `progs/src/lxsecc.c:116` `static void child_wx(void)` -- The page is the child's own anonymous mapping, made before the filter (which forbids mmap): a copy-on-write page...
- `grandchild_inherits` (function) `progs/src/lxsecc.c:127` `static void grandchild_inherits(void)`
- `child_inherit` (function) `progs/src/lxsecc.c:133` `static void child_inherit(void)`
- `child_stacked` (function) `progs/src/lxsecc.c:142` `static void child_stacked(void)`
- `child_strict` (function) `progs/src/lxsecc.c:150` `static void child_strict(void)`
- `child_no_nnp` (function) `progs/src/lxsecc.c:157` `static void child_no_nnp(void)`
- `child_bad_program` (function) `progs/src/lxsecc.c:165` `static void child_bad_program(void)`
- `check_prctl_flags` (function) `progs/src/lxsecc.c:177` `static void check_prctl_flags(void)`
- `check_proc_self_exe` (function) `progs/src/lxsecc.c:197` `static void check_proc_self_exe(const char *argv0)`
- `main` (function) `progs/src/lxsecc.c:215` `int main(int argc, char **argv)`

## progs/src/lxsel.c
Depends on: `kernel/time.c`
- `report` (function) `progs/src/lxsel.c:36` `static void report(const char *name, int ok)`
- `raw_select` (function) `progs/src/lxsel.c:45` `static long raw_select(long nfds, fd_set *r, fd_set *w, fd_set *e,
                       struct ...`
- `raw_pselect6` (function) `progs/src/lxsel.c:50` `static long raw_pselect6(long nfds, fd_set *r, fd_set *w, fd_set *e,
                         str...`
- `elapsed_ms` (function) `progs/src/lxsel.c:55` `static long elapsed_ms(struct timespec *a, struct timespec *b)`
- `main` (function) `progs/src/lxsel.c:60` `int main(void)`

## progs/src/lxtls.c
Depends on: `kernel/string.c`
- `lxtls_sink` (function) `progs/src/lxtls.c:39` `static size_t lxtls_sink(char *data, size_t size, size_t nmemb, void *user)` -- Count the body without storing it: the probe proves transport, not * content.
- `lxtls_debug` (function) `progs/src/lxtls.c:46` `static int lxtls_debug(CURL *h, curl_infotype type, char *data, size_t size, void *user)` -- Count the body without storing it: the probe proves transport, not * content. static size_t lxtls_sink(char *data...
- `lxtls_step` (function) `progs/src/lxtls.c:65` `static int lxtls_step(const char *name, int ok)` -- return 0; for (i = 0; i <= size; i++) { if (i == size || data[i] == '\n') { size_t len = i - start; if (len > 0 &&...
- `lxtls_rand` (function) `progs/src/lxtls.c:73` `static int lxtls_rand(void)` -- } fflush(stdout); return 0; } /* Report one RAND step and, on failure, OpenSSL's error queue. static int...
- `main` (function) `progs/src/lxtls.c:87` `int main(int argc, char **argv)`

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
- `mthread_join` (function) `progs/src/mthreads.h:144` `static int mthread_join(mthread_t t, void **retval)` -- Join: wait4 (Linux semantics) answers the reaped pid and stores the status word; the thread always exits 0, so a...

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

## progs/src/pip.c
Depends on: `kernel/string.c`, `progs/minios_abi.h`
- `main` (function) `progs/src/pip.c:45` `int main(int argc, char **argv)` -- uint32_t namesz; uint32_t descsz; uint32_t type; char     name[sizeof MINIOS_NOTE_NAME]; uint32_t desc; }...

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
- `sc_thread1` (function) `progs/src/scfuzz.c:161` `static void *sc_thread1(void *arg)`

## progs/src/shell.py
Depends on: `progs/lua/minios.c`
- `run_capture` (function) `progs/src/shell.py:20` `def run_capture(cmd, args)`
- `expand` (function) `progs/src/shell.py:30` `def expand(line, env)`
- `main` (function) `progs/src/shell.py:36` `def main()`

## progs/src/sign.c
- `printf` (function) `progs/src/sign.c:28` `int printf();`
- `strcmp` (function) `progs/src/sign.c:29` `int strcmp();`
- `fopen` (function) `progs/src/sign.c:30` `void *fopen();`
- `fclose` (function) `progs/src/sign.c:31` `int fclose();`
- `fread` (function) `progs/src/sign.c:32` `int fread();`
- `fwrite` (function) `progs/src/sign.c:33` `int fwrite();`
- `fseek` (function) `progs/src/sign.c:34` `int fseek();`
- `ftell` (function) `progs/src/sign.c:35` `int ftell();`
- `malloc` (function) `progs/src/sign.c:36` `void *malloc();`
- `free` (function) `progs/src/sign.c:37` `void free();`
- `sign_hexval` (function) `progs/src/sign.c:89` `static unsigned int sign_hexval(char c)` -- static unsigned int sign_k[160]; static unsigned int sign_h[16]; static unsigned int sign_w[160]; static char...
- `sign_unhex` (function) `progs/src/sign.c:100` `static void sign_unhex(char *out, char *in, int n)` -- static unsigned int sign_ga[32]; /** Docstring: Hex digit value, 0 outside hex. static unsigned int sign_hexval(char...
- `sign_byte` (function) `progs/src/sign.c:111` `static unsigned int sign_byte(char *p, int i)` -- } /** Docstring: Decode 2*n hex chars into n bytes. static void sign_unhex(char *out, char *in, int n) { int i = 0...
- `sign_copy` (function) `progs/src/sign.c:119` `static void sign_copy(char *dst, char *src, int n)` -- out[i] = (char)((hi << 4) | lo); i++; } } /** Docstring: Unsigned byte at index, the aes.c masking idiom. static...
- `sign_strlen` (function) `progs/src/sign.c:128` `static int sign_strlen(char *s)` -- v = v + 256; return (unsigned int)v; } /** Docstring: Copy n bytes. static void sign_copy(char *dst, char *src, int...
- `sign_le16` (function) `progs/src/sign.c:136` `static unsigned int sign_le16(char *p, int off)` -- dst[i] = src[i]; i++; } } /** Docstring: String length. static int sign_strlen(char *s) { int n = 0; while (s[n] !=...
- `sign_le32` (function) `progs/src/sign.c:141` `static unsigned int sign_le32(char *p, int off)` -- /** Docstring: String length. static int sign_strlen(char *s) { int n = 0; while (s[n] != 0) n = n + 1; return n; }...
- `sign_put32` (function) `progs/src/sign.c:147` `static void sign_put32(char *p, int off, unsigned int v)` -- } /** Docstring: Little-endian u16 at offset. static unsigned int sign_le16(char *p, int off) { return sign_byte(p...
- `sign_offok` (function) `progs/src/sign.c:180` `static int sign_offok(char *p, int off, int *lo)` -- if (hi < 10) out[2 * i] = (char)(48 + hi); else out[2 * i] = (char)(87 + hi); if (lo < 10) out[2 * i + 1] =...
- `below` (function) `progs/src/sign.c:195` `* every other op below (`|`, `<<`) is low-32 exact. */
static void sign_rotr(unsigned int *lo, un...`
- `sign_borrow2` (function) `progs/src/sign.c:230` `static unsigned int sign_borrow2(unsigned int x, unsigned int y, unsigned int s)` -- Docstring: Borrow out of x minus y into s, without comparisons. * Same miniGCC rationale as sign_carry2: sanitize...
- `sign_add3` (function) `progs/src/sign.c:237` `static unsigned int sign_add3(unsigned int *s, unsigned int a, unsigned int b, unsigned int c)` -- Docstring: Borrow out of x minus y into s, without comparisons. * Same miniGCC rationale as sign_carry2: sanitize...
- `sign_be32` (function) `progs/src/sign.c:247` `static unsigned int sign_be32(char *p, int off)` -- return (t >> 31) & 1; } /** Docstring: Add three words with carry, returning the new carry. static unsigned int...
- `sign_block` (function) `progs/src/sign.c:253` `static void sign_block(void)` -- unsigned int cy = sign_carry2(a, b, t); unsigned int u = t + c; cy = cy + sign_carry2(t, c, u); s = u; return cy; }...
- `sign_sha_init` (function) `progs/src/sign.c:387` `static void sign_sha_init(void)` -- i = 0; while (i < 16) { unsigned int n = sign_h[i] + st[i]; unsigned int cy = 0; cy = sign_carry2(sign_h[i], st[i]...
- `sign_sha_update` (function) `progs/src/sign.c:410` `static void sign_sha_update(char *data, int len)` -- sign_h[8] = 0xade682d1; sign_h[9] = 0x510e527f; sign_h[10] = 0x2b3e6c1f; sign_h[11] = 0x9b05688c; sign_h[12] =...
- `sign_sha_final` (function) `progs/src/sign.c:442` `static void sign_sha_final(char *out)` -- Docstring: Finish the digest into 64 bytes.
- `sign_feed32` (function) `progs/src/sign.c:490` `static void sign_feed32(unsigned int v)` -- while (s < 8) { int ww = 0; if (s < 4) ww = (int)((sign_h[2 * i + 1] >> (24 - 8 * s)) & 255); else ww =...
- `sign_key_init` (function) `progs/src/sign.c:500` `static void sign_key_init(void)` -- } } /** Docstring: Feed a u32 into the digest little-endian. static void sign_feed32(unsigned int v) { char b[4]...
- `fe_copy` (function) `progs/src/sign.c:549` `static void fe_copy(unsigned int *r, unsigned int *a)` -- sign_q4[5] = 4294967295; sign_q4[6] = 4294967295; sign_q4[7] = 2147483647; sign_l8[0] = 1559614445; sign_l8[1] =...
- `fe_zero` (function) `progs/src/sign.c:558` `static void fe_zero(unsigned int *r)` -- sign_l8[6] = 0; sign_l8[7] = 268435456; } /** Docstring: Copy eight limbs. static void fe_copy(unsigned int *r...
- `fe_one` (function) `progs/src/sign.c:567` `static void fe_one(unsigned int *r)` -- i = i + 1; } } /** Docstring: Zero eight limbs. static void fe_zero(unsigned int *r) { int i = 0; while (i < 8) {...
- `fe_cmov` (function) `progs/src/sign.c:573` `static void fe_cmov(unsigned int *r, unsigned int *b, unsigned int flag)` -- int i = 0; while (i < 8) { r[i] = 0; i = i + 1; } } /** Docstring: One as eight limbs. static void fe_one(unsigned...
- `fe_ge` (function) `progs/src/sign.c:586` `static unsigned int fe_ge(unsigned int *a, unsigned int *b)` -- Docstring: 1 when a holds at least b, else 0.
- `fe_rawsub` (function) `progs/src/sign.c:601` `static void fe_rawsub(unsigned int *r, unsigned int *a, unsigned int *b)` -- unsigned int borrow = 0; int i = 0; while (i < 8) { unsigned int t1 = a[i] - borrow; unsigned int c0 =...
- `fe_add` (function) `progs/src/sign.c:617` `static void fe_add(unsigned int *r, unsigned int *a, unsigned int *b)` -- int i = 0; while (i < 8) { unsigned int ai = a[i]; unsigned int t1 = ai - borrow; unsigned int c0 = sign_borrow2(ai...
- `fe_sub` (function) `progs/src/sign.c:636` `static void fe_sub(unsigned int *r, unsigned int *a, unsigned int *b)` -- unsigned int s1 = a[i] + b[i]; unsigned int c0 = sign_carry2(a[i], b[i], s1); unsigned int s2 = s1 + carry; unsigned...
- `bits` (function) `progs/src/sign.c:672` `* values here always fit 32 bits (limbs below 2^16, carries and
 * products below 2^32), so the s...`
- `fe_foldadd` (function) `progs/src/sign.c:690` `static void fe_foldadd(unsigned int *row, int at, unsigned int x)` -- unsigned int carry = 0; carry = (v << 32) >> 32; while (i < 32 && carry != 0) { unsigned int rv = 0; unsigned int s...
- `fe_mul` (function) `progs/src/sign.c:696` `static void fe_mul(unsigned int *r, unsigned int *a, unsigned int *b)` -- s = rv + carry; row[i] = s & 65535; carry = s >> 16; i = i + 1; } } /** Docstring: Fold 38 times a sub-2^16 limb...
- `fe_sq` (function) `progs/src/sign.c:766` `static void fe_sq(unsigned int *r, unsigned int *a)` -- fe_zero(back); back[0] = acc[16] * 38; fe_add(t, t, back); k = 0; while (k < 3) { if (fe_ge(t, sign_q4) == 1)...
- `fe_inv` (function) `progs/src/sign.c:771` `static void fe_inv(unsigned int *r, unsigned int *a)` -- if (fe_ge(t, sign_q4) == 1) fe_rawsub(t, t, sign_q4); k = k + 1; } fe_copy(r, t); } } /** Docstring: Square mod q....
- `fe_frombytes` (function) `progs/src/sign.c:790` `static void fe_frombytes(unsigned int *r, char *b)` -- while (i < 255) { unsigned int bit = 1; if (i == 252 || i == 250) bit = 0; fe_sq(tmp, acc); fe_copy(acc, tmp)...
- `fe_tobytes` (function) `progs/src/sign.c:800` `static void fe_tobytes(char *b, unsigned int *a)` -- fe_copy(r, acc); } /** Docstring: Load 32 bytes into eight limbs. static void fe_frombytes(unsigned int *r, char *b)...
- `fe_curved` (function) `progs/src/sign.c:812` `static void fe_curved(unsigned int *d, unsigned int *d2)` -- /** Docstring: Store eight limbs as 32 bytes. static void fe_tobytes(char *b, unsigned int *a) { int i = 0; while (i...
- `ge_copy` (function) `progs/src/sign.c:829` `static void ge_copy(unsigned int *r, unsigned int *a)` -- unsigned int inv[8]; unsigned int zero[8]; fe_zero(num); fe_zero(den); num[0] = 121665; den[0] = 121666; fe_inv(inv...
- `fe_off` (function) `progs/src/sign.c:845` `static unsigned int *fe_off(unsigned int *p, int n)` -- Docstring: Address of limb n from a limb base.  miniGCC scales `a[i]` by 8 (its `unsigned int` slot) but adds raw...
- `ge_cmov` (function) `progs/src/sign.c:850` `static void ge_cmov(unsigned int *r, unsigned int *b, unsigned int flag)` -- Docstring: Address of limb n from a limb base.  miniGCC scales `a[i]` by 8 (its `unsigned int` slot) but adds raw...
- `ge_add` (function) `progs/src/sign.c:860` `static void ge_add(unsigned int *r, unsigned int *p, unsigned int *q, unsigned int *d2)` -- return p + n * 8; } /** Docstring: Masked point select, no secret branches. static void ge_cmov(unsigned int *r...
- `ge_double` (function) `progs/src/sign.c:892` `static void ge_double(unsigned int *r, unsigned int *p)` -- fe_mul(c, t0, d2); fe_add(t0, fe_off(p, 16), fe_off(p, 16)); fe_mul(d, t0, fe_off(q, 16)); fe_sub(e, b, a)...
- `ge_scalarmult` (function) `progs/src/sign.c:926` `static void ge_scalarmult(unsigned int *r, unsigned int *p, char *s, unsigned int *d2)` -- fe_zero(na); fe_sub(na, na, a); fe_add(g, na, b); fe_sub(f, g, c); fe_zero(nb); fe_sub(nb, nb, b); fe_add(h, na...
- `sc_mod_l` (function) `progs/src/sign.c:951` `static void sc_mod_l(unsigned int *r, unsigned int *t16)` -- while (i >= 0) { unsigned int bit = 0; if (((sign_byte(s, i >> 3) >> (i & 7)) & 1) == 1) bit = 1; ge_double(dbl...
- `sc_mul_add` (function) `progs/src/sign.c:1013` `static void sc_mul_add(unsigned int *r, unsigned int *a, unsigned int *b, unsigned int *c)` -- rem[8] = rem[8] - borrow; } s = s + 1; } b = b + 1; } k = 0; while (k < 8) { r[k] = rem[k]; k = k + 1; } } /**...
- `sign_rev32` (function) `progs/src/sign.c:1070` `static void sign_rev32(char *b)` -- carry = c0 | c1; i = i + 1; } while (i < 16) { unsigned int s = t16[i] + carry; carry = sign_carry2(t16[i], carry...
- `sign_points_init` (function) `progs/src/sign.c:1081` `static void sign_points_init(void)` -- } /** Docstring: Reverse 32 bytes in place, big-endian hex to limbs. static void sign_rev32(char *b) { int i = 0...
- `sign_digest` (function) `progs/src/sign.c:1112` `static void sign_digest(char *sig, char *digest)` -- fe_copy(fe_off(sign_gb, 8), t); fe_one(fe_off(sign_gb, 16)); fe_mul(t, sign_gb, fe_off(sign_gb, 8))...
- `sign_read` (function) `progs/src/sign.c:1232` `static char *sign_read(char *name, int *len)` -- while (i < 16) { t16[i] = sign_byte(hrambytes, 4 * i) | (sign_byte(hrambytes, 4 * i + 1) << 8) |...
- `sign_write` (function) `progs/src/sign.c:1260` `static int sign_write(char *name, char *data, int len)` -- len = 1; buf = malloc(*len); if (buf == 0) { fclose(f); return 0; } got = fread(buf, 1, *len, f); fclose(f); if (got...
- `sign_note_span` (function) `progs/src/sign.c:1273` `static int sign_note_span(char *img, int off, int len, int *desc)` -- /** Docstring: Write a whole file, 0 on success. static int sign_write(char *name, char *data, int len) { void *f =...
- `sign_digest_of` (function) `progs/src/sign.c:1307` `static int sign_digest_of(char *img, int size, int entry, char *ph, int phnum, char *digest)` -- Docstring: Build the canonical digest over entry plus PT_LOADs.
- `sign_patch_notes` (function) `progs/src/sign.c:1356` `static int sign_patch_notes(char *img, int size, char *ph, int phnum, char *desc)` -- sign_feed32(0); start = poff; if (start < SIGN_EHDR_SIZE) start = SIGN_EHDR_SIZE; end = poff + pfilesz; if (start <...
- `sign_append` (function) `progs/src/sign.c:1393` `static int sign_append(char *name, char *img, int size, int shoff, int shnum, int shentsize,
    ...` -- rc = sign_note_span(img, poff, pfilesz, &slot); if (rc == 1 && img[slot] == SIGN_KEY_ID) { while (k <...
- `sign_file` (function) `progs/src/sign.c:1529` `static int sign_file(char *name)` -- int sn = shnum + 1; out[60] = (char)(sn & 255); out[61] = (char)((sn >> 8) & 255); } } if (sign_write(name, out...
- `sign_selftest` (function) `progs/src/sign.c:1637` `static int sign_selftest(void)` -- Docstring: In-OS differential selftest, pinned by BDD.
- `main` (function) `progs/src/sign.c:1657` `int main(int argc, char **argv)`

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


Next: [API_p20.md](API_p20.md)
