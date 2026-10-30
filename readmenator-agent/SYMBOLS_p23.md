# Symbols (page 23 of 27)
Previous: [SYMBOLS_p22.md](SYMBOLS_p22.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `errno` | variable | `progs/src/ftest.c:10` | `extern int errno;` |
| `exit` | function | `progs/src/ftest.c:7` | `extern void exit(int code);` |
| `fopen` | function | `progs/src/ftest.c:11` | `extern void *fopen(const char *path, const char *mode);` |
| `fprintf` | function | `progs/src/ftest.c:4` | `extern int fprintf(void *stream, const char *fmt, ...);` |
| `main` | function | `progs/src/ftest.c:13` | `int main(int argc, char **argv)` |
| `printf` | function | `progs/src/ftest.c:6` | `extern int printf(const char *fmt, ...);` |
| `snprintf` | function | `progs/src/ftest.c:5` | `extern int snprintf(char *buf, unsigned long size, const char *fmt, ...);` |
| `stderr` | variable | `progs/src/ftest.c:9` | `extern void *stderr;` |
| `stdout` | variable | `progs/src/ftest.c:8` | `extern void *stdout;` |
| `main` | function | `progs/src/hello.c:4` | `int main(int argc, char **argv)` |
| `printf` | function | `progs/src/hello.c:2` | `extern int printf(const char *fmt, ...);` |
| `atoi` | function | `progs/src/http.c:18` | `int atoi(char *s)` |
| `close` | function | `progs/src/http.c:10` | `int close(int fd);` |
| `connect` | function | `progs/src/http.c:6` | `int connect(int fd, void *addr, int addrlen);` |
| `kernel` | function | `progs/src/http.c:3` | `* Hostnames are resolved by the kernel (net_dns_resolve syscall). */ int socket(int domain, int type, int proto);` |
| `main` | function | `progs/src/http.c:29` | `int main(int argc, char **argv)` |
| `net_dns_resolve` | function | `progs/src/http.c:11` | `int net_dns_resolve(const char *host);` |
| `printf` | function | `progs/src/http.c:13` | `int printf(char *fmt, ...);` |
| `putchar` | function | `progs/src/http.c:15` | `int putchar(int c);` |
| `puts` | function | `progs/src/http.c:12` | `int puts(char *s);` |
| `recvfrom` | function | `progs/src/http.c:8` | `int recvfrom(int fd, char *buf, int len, int flags, void *from, int *fromlen);` |
| `sendto` | function | `progs/src/http.c:7` | `int sendto(int fd, char *buf, int len, int flags, void *to, int tolen);` |
| `shutdown` | function | `progs/src/http.c:9` | `int shutdown(int fd, int how);` |
| `strlen` | function | `progs/src/http.c:14` | `int strlen(char *s);` |
| `JS_ARR` | macro | `progs/src/json.c:35` | `#define JS_ARR` |
| `JS_BOOL` | macro | `progs/src/json.c:31` | `#define JS_BOOL` |
| `JS_EXIT_FAIL` | macro | `progs/src/json.c:39` | `#define JS_EXIT_FAIL` |
| `JS_EXIT_OK` | macro | `progs/src/json.c:38` | `#define JS_EXIT_OK` |
| `JS_MAX_NODES` | macro | `progs/src/json.c:27` | `#define JS_MAX_NODES` |
| `JS_NULL` | macro | `progs/src/json.c:30` | `#define JS_NULL` |
| `JS_NUM` | macro | `progs/src/json.c:32` | `#define JS_NUM` |
| `JS_OBJ` | macro | `progs/src/json.c:34` | `#define JS_OBJ` |
| `JS_POOL` | macro | `progs/src/json.c:28` | `#define JS_POOL` |
| `JS_SEEK_END` | macro | `progs/src/json.c:37` | `#define JS_SEEK_END` |
| `JS_STR` | macro | `progs/src/json.c:33` | `#define JS_STR` |
| `fclose` | function | `progs/src/json.c:21` | `int fclose();` |
| `fopen` | function | `progs/src/json.c:20` | `void *fopen();` |
| `fread` | function | `progs/src/json.c:22` | `int fread();` |
| `free` | function | `progs/src/json.c:14` | `void free();` |
| `fseek` | function | `progs/src/json.c:23` | `int fseek();` |
| `ftell` | function | `progs/src/json.c:24` | `int ftell();` |
| `js_array_at` | function | `progs/src/json.c:357` | `static int js_array_at(int arr, int idx)` |
| `js_find_member` | function | `progs/src/json.c:347` | `static int js_find_member(int obj, const char *key)` |
| `js_indent` | function | `progs/src/json.c:281` | `static void js_indent(int n)` |
| `js_key_match` | function | `progs/src/json.c:143` | `static int js_key_match(int child, const char *key)` |
| `js_new` | function | `progs/src/json.c:76` | `static int js_new(void)` |
| `js_parse_array` | function | `progs/src/json.c:182` | `static int js_parse_array(void)` |
| `js_parse_number` | function | `progs/src/json.c:133` | `static int js_parse_number(void)` |
| `js_parse_object` | function | `progs/src/json.c:147` | `static int js_parse_object(void)` |
| `js_parse_string` | function | `progs/src/json.c:97` | `static int js_parse_string(void)` |
| `js_parse_value` | function | `progs/src/json.c:211` | `static int js_parse_value(void)` |
| `js_peek` | function | `progs/src/json.c:89` | `static int js_peek(void)` |
| `js_print_str` | function | `progs/src/json.c:286` | `static void js_print_str(const char *s)` |
| `js_print_value` | function | `progs/src/json.c:303` | `static void js_print_value(int node, int depth)` |
| `js_query` | function | `progs/src/json.c:369` | `static int js_query(int root, const char *path)` |
| `js_read_all` | function | `progs/src/json.c:58` | `static char *js_read_all(const char *name, int *len)` |
| `js_skip_ws` | function | `progs/src/json.c:81` | `static void js_skip_ws(void)` |
| `js_str` | function | `progs/src/json.c:5` | `* members keep their key in js_str (the member value node) and their value * in the node itself, and object members...` |
| `main` | function | `progs/src/json.c:401` | `int main(int argc, char **argv)` |
| `printf` | function | `progs/src/json.c:15` | `int printf();` |
| `putchar` | function | `progs/src/json.c:16` | `int putchar();` |
| `puts` | function | `progs/src/json.c:17` | `int puts();` |
| `rewind` | function | `progs/src/json.c:25` | `void rewind();` |
| `strcmp` | function | `progs/src/json.c:19` | `int strcmp();` |
| `strlen` | function | `progs/src/json.c:18` | `int strlen();` |
| `_start` | function | `progs/src/kmem.c:18` | `void _start(void)` |
| `exit_now` | function | `progs/src/kmem.c:14` | `static void exit_now(long code)` |
| `syscall3` | function | `progs/src/kmem.c:7` | `static long syscall3(long n, long a1, long a2, long a3)` |
| `main` | function | `progs/src/ldhello.c:1` | `int main(void)` |
| `LXABI_A6_MAGIC` | macro | `progs/src/lxabi.c:55` | `#define LXABI_A6_MAGIC` |
| `LXABI_CHILD_BAD` | macro | `progs/src/lxabi.c:56` | `#define LXABI_CHILD_BAD` |
| `LXABI_CHILD_DELAY_MS` | macro | `progs/src/lxabi.c:41` | `#define LXABI_CHILD_DELAY_MS` |
| `LXABI_CLOCK_SKEW_S` | macro | `progs/src/lxabi.c:51` | `#define LXABI_CLOCK_SKEW_S` |
| `LXABI_CLONE_NR` | macro | `progs/src/lxabi.c:53` | `#define LXABI_CLONE_NR` |
| `LXABI_CLOSE_RANGE_NR` | macro | `progs/src/lxabi.c:59` | `#define LXABI_CLOSE_RANGE_NR` |
| `LXABI_COW_WORD` | macro | `progs/src/lxabi.c:61` | `#define LXABI_COW_WORD` |
| `LXABI_DETACHED` | macro | `progs/src/lxabi.c:44` | `#define LXABI_DETACHED` |
| `LXABI_EPOCH_2023` | macro | `progs/src/lxabi.c:50` | `#define LXABI_EPOCH_2023` |
| `LXABI_GROUP_EXIT_CODE` | macro | `progs/src/lxabi.c:46` | `#define LXABI_GROUP_EXIT_CODE` |
| `LXABI_MAX_SANE_CPUS` | macro | `progs/src/lxabi.c:48` | `#define LXABI_MAX_SANE_CPUS` |
| `LXABI_MKDIR_FILE` | macro | `progs/src/lxabi.c:58` | `#define LXABI_MKDIR_FILE` |
| `LXABI_MKDIR_PATH` | macro | `progs/src/lxabi.c:57` | `#define LXABI_MKDIR_PATH` |
| `LXABI_PAGE` | macro | `progs/src/lxabi.c:60` | `#define LXABI_PAGE` |
| `LXABI_REG_PROBE_WORDS` | macro | `progs/src/lxabi.c:52` | `#define LXABI_REG_PROBE_WORDS` |
| `LXABI_SIGCHLD` | macro | `progs/src/lxabi.c:54` | `#define LXABI_SIGCHLD` |
| `LXABI_SLEEP_MS` | macro | `progs/src/lxabi.c:47` | `#define LXABI_SLEEP_MS` |
| `LXABI_THREADS` | macro | `progs/src/lxabi.c:42` | `#define LXABI_THREADS` |
| `LXABI_THREAD_ITERS` | macro | `progs/src/lxabi.c:43` | `#define LXABI_THREAD_ITERS` |
| `LXABI_TIMEDWAIT_MS` | macro | `progs/src/lxabi.c:49` | `#define LXABI_TIMEDWAIT_MS` |
| `LXABI_WAIT_SPINS` | macro | `progs/src/lxabi.c:45` | `#define LXABI_WAIT_SPINS` |
| `_GNU_SOURCE` | macro | `progs/src/lxabi.c:17` | `#define _GNU_SOURCE` |
| `abort_from_worker_body` | function | `progs/src/lxabi.c:555` | `static void abort_from_worker_body(void)` |
| `busy_wait_ms` | function | `progs/src/lxabi.c:81` | `static void busy_wait_ms(long ms)` |
| `check_close_range` | function | `progs/src/lxabi.c:443` | `static void check_close_range(void)` |
| `check_condvar` | function | `progs/src/lxabi.c:285` | `static void check_condvar(void)` |
| `check_detached_reaped` | function | `progs/src/lxabi.c:251` | `static void check_detached_reaped(void)` |
| `check_eventfd` | function | `progs/src/lxabi.c:418` | `static void check_eventfd(void)` |
| `check_fork_cow_kernel_write` | function | `progs/src/lxabi.c:160` | `static void check_fork_cow_kernel_write(void)` |
| `check_fork_registers` | function | `progs/src/lxabi.c:138` | `static void check_fork_registers(void)` |
| `check_getdents64` | function | `progs/src/lxabi.c:722` | `static void check_getdents64(void)` |
| `check_limits` | function | `progs/src/lxabi.c:478` | `static void check_limits(void)` |
| `check_mkdir` | function | `progs/src/lxabi.c:464` | `static void check_mkdir(void)` |
| `check_pipe2_flags` | function | `progs/src/lxabi.c:307` | `static void check_pipe2_flags(void)` |
| `check_pipe_blocking` | function | `progs/src/lxabi.c:334` | `static void check_pipe_blocking(void)` |
| `check_pipe_epipe` | function | `progs/src/lxabi.c:356` | `static void check_pipe_epipe(void)` |
| `check_poll` | function | `progs/src/lxabi.c:394` | `static void check_poll(void)` |
| `check_rename_dir` | function | `progs/src/lxabi.c:649` | `static void check_rename_dir(void)` |
| `check_sleep` | function | `progs/src/lxabi.c:500` | `static void check_sleep(void)` |
| `check_threads` | function | `progs/src/lxabi.c:215` | `static void check_threads(void)` |
| `check_time` | function | `progs/src/lxabi.c:455` | `static void check_time(void)` |
| `check_uid_gid` | function | `progs/src/lxabi.c:642` | `static void check_uid_gid(void)` |
| `check_writev_pipe` | function | `progs/src/lxabi.c:382` | `static void check_writev_pipe(void)` |
| `child_status` | function | `progs/src/lxabi.c:535` | `static int child_status(void (*body)(void))` |
| `copy_dentry_name` | function | `progs/src/lxabi.c:715` | `static void copy_dentry_name(char *dst, size_t cap, const char *src)` |
| `detached_worker` | function | `progs/src/lxabi.c:245` | `static void *detached_worker(void *arg)` |
| `exit_group_from_worker_body` | function | `progs/src/lxabi.c:567` | `static void exit_group_from_worker_body(void)` |
| `fork_probe` | function | `progs/src/lxabi.c:95` | `static void fork_probe(uint64_t *out)` |
| `lxabi_exit_group_worker` | function | `progs/src/lxabi.c:561` | `static void *lxabi_exit_group_worker(void *arg)` |
| `lxabi_sleeper` | function | `progs/src/lxabi.c:527` | `static void *lxabi_sleeper(void *arg)` |
| `main` | function | `progs/src/lxabi.c:789` | `int main(void)` |
| `mono_us` | function | `progs/src/lxabi.c:491` | `static long mono_us(void)` |
| `now_ms` | function | `progs/src/lxabi.c:75` | `static long now_ms(void)` |
| `process` | function | `progs/src/lxabi.c:581` | `* process (never a kernel panic), and kill(pid, 0) or a harmless signal  * leaves the target aliv...` |
| `regs_match` | function | `progs/src/lxabi.c:132` | `static int regs_match(const uint64_t *r)` |
| `report` | function | `progs/src/lxabi.c:65` | `static void report(const char *name, int ok, const char *detail)` |
| `signaller` | function | `progs/src/lxabi.c:275` | `static void *signaller(void *arg)` |
| `thread_result` | struct | `progs/src/lxabi.c:195` | `` |
| `tls_seen` | type_alias | `progs/src/lxabi.c:194` | `typedef struct thread_result { long tls_seen;` |
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
| `_start` | function | `progs/src/scfuzz.c:167` | `void _start(void)` |
| `guest` | function | `progs/src/scfuzz.c:7` | `* the guest (the BDD timeout then talks). All fuzz maps stay inside  * one private 4 MB arena (pa...` |
| `sc_exit` | function | `progs/src/scfuzz.c:61` | `static void sc_exit(long code)` |
| `sc_fold` | function | `progs/src/scfuzz.c:76` | `static unsigned long sc_fold(unsigned long h, unsigned long v)` |
| `sc_hex8` | function | `progs/src/scfuzz.c:88` | `static void sc_hex8(unsigned long v, char *out)` |
| `sc_mprotect` | function | `progs/src/scfuzz.c:38` | `static long sc_mprotect(long addr, long len, long prot)` |
| `sc_munmap` | function | `progs/src/scfuzz.c:49` | `static long sc_munmap(long addr, long len)` |
| `sc_rng` | function | `progs/src/scfuzz.c:67` | `static unsigned long sc_rng(unsigned long *s)` |
| `sc_thread1` | function | `progs/src/scfuzz.c:161` | `static void *sc_thread1(void *arg)` |
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

Next: [SYMBOLS_p24.md](SYMBOLS_p24.md)
