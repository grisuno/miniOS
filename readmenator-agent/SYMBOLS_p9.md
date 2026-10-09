# Symbols (page 9 of 26)
Previous: [SYMBOLS_p8.md](SYMBOLS_p8.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `shell_complete_minifs_arg` | function | `kernel/shell.c:268` | `static void shell_complete_minifs_arg(const char *word, unsigned long wlen,                      ...` |
| `shell_complete_replace` | function | `kernel/shell.c:247` | `static void shell_complete_replace(char *buf, int size, int *pos,                                ...` |
| `shell_complete_tier` | function | `kernel/shell.c:235` | `static int shell_complete_tier(const char *nm)` |
| `shell_cross_cat` | function | `kernel/shell.c:2804` | `static void shell_cross_cat(const char *drv, const char *imgarg,                             cons...` |
| `shell_cross_ls` | function | `kernel/shell.c:2763` | `static void shell_cross_ls(const char *drv, const char *imgarg,                            const ...` |
| `shell_exec_builtin` | function | `kernel/shell.c:2846` | `void shell_exec_builtin(int argc, char **argv)` |
| `shell_file_is_real` | function | `kernel/shell.c:1049` | `static int shell_file_is_real(const char *resolved)` |
| `shell_focus_park` | function | `kernel/shell.c:113` | `void shell_focus_park(void)` |
| `shell_focus_restore` | function | `kernel/shell.c:118` | `void shell_focus_restore(void)` |
| `shell_has_child` | function | `kernel/shell.c:2048` | `static int shell_has_child(int pid)` |
| `shell_hist_newest_match` | function | `kernel/shell.c:426` | `static int shell_hist_newest_match(const char *prefix, unsigned long plen)` |
| `shell_hist_show` | function | `kernel/shell.c:343` | `static void shell_hist_show(char *buf, int size, int *pos, const char *text)` |
| `shell_httpd_one` | function | `kernel/shell.c:2511` | `static void shell_httpd_one(int child, const char *root)` |
| `shell_httpd_serve` | function | `kernel/shell.c:2596` | `static void shell_httpd_serve(unsigned short port, const char *root,         int max_conn)` |
| `shell_is_pipe_tok` | function | `kernel/shell.c:4020` | `static int shell_is_pipe_tok(const char *a)` |
| `shell_line_backspace` | function | `kernel/shell.c:387` | `static void shell_line_backspace(char *buf, int size, int *pos)` |
| `shell_line_delete` | function | `kernel/shell.c:395` | `static void shell_line_delete(char *buf, int size, int *pos)` |
| `shell_line_insert` | function | `kernel/shell.c:378` | `static void shell_line_insert(char *buf, int size, int *pos, char c)` |
| `shell_line_kill_front` | function | `kernel/shell.c:402` | `static void shell_line_kill_front(char *buf, int size, int *pos)` |
| `shell_line_kill_tail` | function | `kernel/shell.c:409` | `static void shell_line_kill_tail(char *buf, int size, int *pos)` |
| `shell_line_kill_word` | function | `kernel/shell.c:414` | `static void shell_line_kill_word(char *buf, int size, int *pos)` |
| `shell_line_repaint` | function | `kernel/shell.c:365` | `static void shell_line_repaint(char *buf, int size, int pos)` |
| `shell_load` | function | `kernel/shell.c:946` | `static int shell_load(const char *fname, char *progname_out, void **entry_out)` |
| `shell_name_base` | function | `kernel/shell.c:210` | `static const char *shell_name_base(const char *path)` |
| `shell_parse` | function | `kernel/shell.c:808` | `int shell_parse(char *line, char **argv, int max_args)` |
| `shell_parse_long` | function | `kernel/shell.c:2307` | `int shell_parse_long(const char *s, long *out)` |
| `shell_parse_pid` | function | `kernel/shell.c:2328` | `int shell_parse_pid(const char *s, int min_pid, int *out)` |
| `shell_parse_u64` | function | `kernel/shell.c:2291` | `static int shell_parse_u64(const char *s, unsigned long *out)` |
| `shell_parse_vol` | function | `kernel/shell.c:155` | `static int shell_parse_vol(const char *s, unsigned *out)` |
| `shell_prompt` | function | `kernel/shell.c:145` | `static void shell_prompt(void)` |
| `shell_queue_launch` | function | `kernel/shell.c:84` | `void shell_queue_launch(const char *cmd)` |
| `shell_read_elf_bytes` | function | `kernel/shell.c:1290` | `static int shell_read_elf_bytes(const char *name, unsigned char **out,                           ...` |
| `shell_readline` | function | `kernel/shell.c:335` | `static void shell_readline(void)` |
| `shell_readline_active` | function | `kernel/shell.c:112` | `int shell_readline_active(void)` |
| `shell_readline_buf` | function | `kernel/shell.c:181` | `void shell_readline_buf(char *buf, int size)` |
| `shell_readline_hist` | function | `kernel/shell.c:488` | `static void shell_readline_hist(char *buf, int size)` |
| `shell_resolve_arg` | function | `kernel/shell.c:2405` | `static int shell_resolve_arg(const char *cmd, const char *arg,                              const...` |
| `shell_resolve_run` | function | `kernel/shell.c:1061` | `static int shell_resolve_run(const char *name, char *out, unsigned cap)` |
| `shell_run` | function | `kernel/shell.c:876` | `void shell_run(void)` |
| `shell_run_any` | function | `kernel/shell.c:1621` | `int shell_run_any(const char *name, int argc, char **argv)` |
| `shell_run_bg` | function | `kernel/shell.c:1457` | `static void shell_run_bg(const char *name, int argc, char **argv)` |
| `shell_run_cvm` | function | `kernel/shell.c:1210` | `static int shell_run_cvm(const char *full, int argc, char **argv)` |
| `shell_run_dir_for` | function | `kernel/shell.c:1031` | `static const ShellRunDir *shell_run_dir_for(const char *name)` |
| `shell_run_elf_buf_path` | function | `kernel/shell.c:1117` | `static int shell_run_elf_buf_path(const char *data, unsigned size, int argc,                     ...` |
| `shell_run_elf_file` | function | `kernel/shell.c:1147` | `static int shell_run_elf_file(const char *full, int argc, char **argv)` |
| `shell_run_elf_minifs` | function | `kernel/shell.c:1160` | `static int shell_run_elf_minifs(const char *name, int argc, char **argv)` |
| `shell_run_file` | function | `kernel/shell.c:1246` | `static int shell_run_file(const char *name, int argc, char **argv)` |
| `shell_run_init` | function | `kernel/shell.c:837` | `static void shell_run_init(void)` |
| `shell_run_pipeline` | function | `kernel/shell.c:148` | `static int shell_run_pipeline(char **argv, int argc, const char *redir_path, int redir_append, int redirected);` |
| `shell_run_stage` | function | `kernel/shell.c:4059` | `static char *shell_run_stage(char **sargv, int sargc,         const char *input, unsigned long in...` |
| `stdout` | function | `kernel/shell.c:4008` | `* the pipe exactly like stdout (`2>` is an alias of `>`). * Per-stage `exit code:` lines report to the console...` |
| `terminal` | function | `kernel/shell.c:2921` | `* sequence clears serial consoles and is swallowed without * garbage by the framebuffer terminal (vedit pattern). */...` |
| `this` | function | `kernel/shell.c:1487` | `* boot into the tiled Wayland desktop: every NK app started after * this (paint, vedit, file, nuklear, doomedit...` |
| `to` | function | `kernel/shell.c:2222` | `* actually trap to (brk/mmap/munmap/mprotect) and says so up front. */ static void shell_cmd_trac...` |
| `tree` | function | `kernel/shell.c:2006` | `* tree (mmap-heavy jobs stay best-effort), legacy blocking `run` ignores  * Ctrl+C (it never poll...` |
| `window` | function | `kernel/shell.c:1283` | `* window (proc_spawn_elf) and waits for all of them. The 100 Hz timer * preempts the BSP across the READY set, so...` |
| `spawn_backup` | function | `kernel/spawn.c:11` | `int spawn_backup(spawn_ctx_t *ctx)` |
| `spawn_copy_argv` | function | `kernel/spawn.c:96` | `char **spawn_copy_argv(int argc, const char **uargv)` |
| `spawn_execute` | function | `kernel/spawn.c:264` | `int spawn_execute(const char *resolved, const char *redirect,                   unsigned char *da...` |
| `spawn_free_argv` | function | `kernel/spawn.c:84` | `void spawn_free_argv(char **kargv, int argc)` |
| `spawn_load_image` | function | `kernel/spawn.c:158` | `unsigned char *spawn_load_image(const char *resolved, unsigned *size_out)` |
| `spawn_restore` | function | `kernel/spawn.c:37` | `void spawn_restore(spawn_ctx_t *ctx)` |
| `spawn_run_exec` | function | `kernel/spawn.c:219` | `static int spawn_run_exec(const char *resolved, const char *redirect,                            ...` |
| `spawn_run_rel` | function | `kernel/spawn.c:193` | `static int spawn_run_rel(const char *resolved, const char *redirect,                          uns...` |
| `spawn_validate_argv` | function | `kernel/spawn.c:140` | `int spawn_validate_argv(int argc, const char **uargv)` |
| `katol` | function | `kernel/string.c:95` | `long katol(const char *s)` |
| `kmemcmp` | function | `kernel/string.c:81` | `int kmemcmp(const void *a, const void *b, unsigned long n)` |
| `kmemcpy` | function | `kernel/string.c:68` | `void *kmemcpy(void *dst, const void *src, unsigned long n)` |
| `kmemmove` | function | `kernel/string.c:87` | `void *kmemmove(void *dst, const void *src, unsigned long n)` |
| `kmemset` | function | `kernel/string.c:75` | `void *kmemset(void *dst, int c, unsigned long n)` |
| `kstrchr` | function | `kernel/string.c:53` | `char *kstrchr(const char *s, int c)` |
| `kstrcmp` | function | `kernel/string.c:43` | `int kstrcmp(const char *a, const char *b)` |
| `kstrcpy` | function | `kernel/string.c:23` | `char *kstrcpy(char *dst, const char *src)` |
| `kstrlen` | function | `kernel/string.c:17` | `unsigned long kstrlen(const char *s)` |
| `kstrncat` | function | `kernel/string.c:35` | `char *kstrncat(char *dst, const char *src, unsigned long n)` |
| `kstrncmp` | function | `kernel/string.c:48` | `int kstrncmp(const char *a, const char *b, unsigned long n)` |
| `kstrncpy` | function | `kernel/string.c:29` | `char *kstrncpy(char *dst, const char *src, unsigned long n)` |
| `kstrstr` | function | `kernel/string.c:58` | `char *kstrstr(const char *hay, const char *ndl)` |
| `k_register_process` | function | `kernel/symtab.c:57` | `void k_register_process(const char *name, void *proc_entry)` |
| `k_register_program` | function | `kernel/symtab.c:49` | `void k_register_program(const char *name, prog_entry_t entry)` |
| `k_register_symbol` | function | `kernel/symtab.c:10` | `void k_register_symbol(const char *name, void *addr)` |
| `k_spawn` | function | `kernel/symtab.c:65` | `int k_spawn(const char *name, int argc, char **argv)` |
| `kprog_lookup` | function | `kernel/symtab.c:42` | `KProg *kprog_lookup(const char *name)` |
| `kprog_slot` | function | `kernel/symtab.c:34` | `KProg *kprog_slot(const char *name)` |
| `ksym_resolve` | function | `kernel/symtab.c:18` | `void *ksym_resolve(const char *name)` |
| `cond_broadcast` | function | `kernel/sync.c:249` | `void cond_broadcast(cond_t *c)` |
| `cond_init` | function | `kernel/sync.c:235` | `void cond_init(cond_t *c)` |
| `cond_signal` | function | `kernel/sync.c:245` | `void cond_signal(cond_t *c)` |
| `cond_wait` | function | `kernel/sync.c:239` | `void cond_wait(cond_t *c, mutex_t *m)` |
| `mutex_init` | function | `kernel/sync.c:76` | `void mutex_init(mutex_t *m)` |
| `mutex_lock` | function | `kernel/sync.c:150` | `void mutex_lock(mutex_t *m)` |
| `mutex_trylock` | function | `kernel/sync.c:170` | `int mutex_trylock(mutex_t *m)` |
| `mutex_unlock` | function | `kernel/sync.c:186` | `void mutex_unlock(mutex_t *m)` |
| `pi_boost` | function | `kernel/sync.c:124` | `static void pi_boost(int waiter, int owner)` |
| `pi_get_eff` | function | `kernel/sync.c:108` | `int pi_get_eff(int pid)` |
| `pi_recompute` | function | `kernel/sync.c:113` | `static void pi_recompute(int pid)` |
| `pi_set_base` | function | `kernel/sync.c:99` | `void pi_set_base(int pid, int prio)` |
| `pi_valid` | function | `kernel/sync.c:93` | `static int pi_valid(int pid)` |
| `rwlock_init` | function | `kernel/sync.c:253` | `void rwlock_init(rwlock_t *rw)` |
| `rwlock_read_lock` | function | `kernel/sync.c:260` | `void rwlock_read_lock(rwlock_t *rw)` |
| `rwlock_read_unlock` | function | `kernel/sync.c:274` | `void rwlock_read_unlock(rwlock_t *rw)` |
| `rwlock_write_lock` | function | `kernel/sync.c:283` | `void rwlock_write_lock(rwlock_t *rw)` |
| `rwlock_write_unlock` | function | `kernel/sync.c:297` | `void rwlock_write_unlock(rwlock_t *rw)` |
| `sem_init` | function | `kernel/sync.c:207` | `void sem_init(sem_t *s, int value)` |
| `sem_post` | function | `kernel/sync.c:227` | `void sem_post(sem_t *s)` |
| `sem_wait` | function | `kernel/sync.c:213` | `void sem_wait(sem_t *s)` |
| `sleep_on` | function | `kernel/sync.c:33` | `void sleep_on(wait_queue_t *q)` |
| `t_cur_pid` | variable | `kernel/sync.c:24` | `extern int t_cur_pid;` |
| `wake_up` | function | `kernel/sync.c:54` | `int wake_up(wait_queue_t *q)` |
| `wake_up_all` | function | `kernel/sync.c:70` | `int wake_up_all(wait_queue_t *q)` |
| `wq_init` | function | `kernel/sync.c:27` | `void wq_init(wait_queue_t *q)` |
| `DOOM_FRAME` | function | `kernel/syscalls.c:827` | `* DOOM_FRAME (211) and NK_FRAME (220) stay as compat aliases. */ static long sys_minios_gfx_prese...` |
| `Discipline` | function | `kernel/syscalls.c:2849` | `* * Discipline (audit 2026-09, kept as comment, not a deprecation: both * primitives are legitimate): user_range_ok...` |
| `EAGAIN` | function | `kernel/syscalls.c:1151` | `* writer open is EAGAIN (-11, retry);` |
| `EOF` | function | `kernel/syscalls.c:1152` | `* is EOF (0). */ KFILE *o = kfd_get(0);` |
| `FD_STD_COUNT` | macro | `kernel/syscalls.c:1325` | `#define FD_STD_COUNT` |
| `KFD_MAX` | macro | `kernel/syscalls.c:50` | `#define KFD_MAX` |
| `LINUX_CLOSE_RANGE_CLOEXEC` | macro | `kernel/syscalls.c:1320` | `#define LINUX_CLOSE_RANGE_CLOEXEC` |
| `LINUX_CLOSE_RANGE_UNSHARE` | macro | `kernel/syscalls.c:1319` | `#define LINUX_CLOSE_RANGE_UNSHARE` |
| `LINUX_EFD_CLOEXEC` | macro | `kernel/syscalls.c:1323` | `#define LINUX_EFD_CLOEXEC` |
| `LINUX_EFD_NONBLOCK` | macro | `kernel/syscalls.c:1322` | `#define LINUX_EFD_NONBLOCK` |
| `LINUX_EFD_SEMAPHORE` | macro | `kernel/syscalls.c:1321` | `#define LINUX_EFD_SEMAPHORE` |
| `LINUX_EVENTFD_WORD` | macro | `kernel/syscalls.c:1324` | `#define LINUX_EVENTFD_WORD` |
| `LINUX_FD_CLOEXEC` | macro | `kernel/syscalls.c:1312` | `#define LINUX_FD_CLOEXEC` |
| `LINUX_F_DUPFD` | macro | `kernel/syscalls.c:1313` | `#define LINUX_F_DUPFD` |
| `LINUX_F_DUPFD_CLOEXEC` | macro | `kernel/syscalls.c:1318` | `#define LINUX_F_DUPFD_CLOEXEC` |
| `LINUX_F_GETFD` | macro | `kernel/syscalls.c:1314` | `#define LINUX_F_GETFD` |
| `LINUX_F_GETFL` | macro | `kernel/syscalls.c:1316` | `#define LINUX_F_GETFL` |
| `LINUX_F_SETFD` | macro | `kernel/syscalls.c:1315` | `#define LINUX_F_SETFD` |
| `LINUX_F_SETFL` | macro | `kernel/syscalls.c:1317` | `#define LINUX_F_SETFL` |
| `LINUX_MAP_ANONYMOUS` | macro | `kernel/syscalls.c:1770` | `#define LINUX_MAP_ANONYMOUS` |
| `LINUX_MAP_FIXED` | macro | `kernel/syscalls.c:1769` | `#define LINUX_MAP_FIXED` |
| `LINUX_MAP_PRIVATE` | macro | `kernel/syscalls.c:1768` | `#define LINUX_MAP_PRIVATE` |
| `LINUX_MAP_SHARED` | macro | `kernel/syscalls.c:1767` | `#define LINUX_MAP_SHARED` |
| `LINUX_MREMAP_FIXED` | macro | `kernel/syscalls.c:1996` | `#define LINUX_MREMAP_FIXED` |
| `LINUX_MREMAP_MAYMOVE` | macro | `kernel/syscalls.c:1995` | `#define LINUX_MREMAP_MAYMOVE` |
| `LINUX_O_APPEND` | macro | `kernel/syscalls.c:1308` | `#define LINUX_O_APPEND` |
| `LINUX_O_CLOEXEC` | macro | `kernel/syscalls.c:1311` | `#define LINUX_O_CLOEXEC` |
| `LINUX_O_DIRECT` | macro | `kernel/syscalls.c:1310` | `#define LINUX_O_DIRECT` |
| `LINUX_O_NONBLOCK` | macro | `kernel/syscalls.c:1309` | `#define LINUX_O_NONBLOCK` |
| `LINUX_O_RDONLY` | macro | `kernel/syscalls.c:1305` | `#define LINUX_O_RDONLY` |
| `LINUX_O_RDWR` | macro | `kernel/syscalls.c:1307` | `#define LINUX_O_RDWR` |
| `LINUX_O_WRONLY` | macro | `kernel/syscalls.c:1306` | `#define LINUX_O_WRONLY` |
| `LINUX_SYSCALL_COUNT` | macro | `kernel/syscalls.c:2652` | `#define LINUX_SYSCALL_COUNT` |
| `MINIOS_SYSCALL_BASE` | macro | `kernel/syscalls.c:241` | `#define MINIOS_SYSCALL_BASE` |
| `MINIOS_SYSCALL_COUNT` | macro | `kernel/syscalls.c:242` | `#define MINIOS_SYSCALL_COUNT` |
| `NULL` | function | `kernel/syscalls.c:164` | `* on NULL (already released or never owned). */ void kfd_view_release(proc_t *p)` |
| `PROC_SELF_EXE` | macro | `kernel/syscalls.c:2483` | `#define PROC_SELF_EXE` |
| `SC_EXTRA_COUNT` | macro | `kernel/syscalls.c:2743` | `#define SC_EXTRA_COUNT` |
| `SYSCALL_TRACE` | macro | `kernel/syscalls.c:1098` | `#define SYSCALL_TRACE` |
| `SYS_NOISY_GETC_RAW` | macro | `kernel/syscalls.c:1121` | `#define SYS_NOISY_GETC_RAW` |
| `SYS_NOISY_KBD` | macro | `kernel/syscalls.c:1119` | `#define SYS_NOISY_KBD` |
| `SYS_NOISY_MOUSE` | macro | `kernel/syscalls.c:1120` | `#define SYS_NOISY_MOUSE` |
| `SYS_NOISY_TIME` | macro | `kernel/syscalls.c:1118` | `#define SYS_NOISY_TIME` |
| `TRACE_HINT_NONE` | macro | `kernel/syscalls.c:2765` | `#define TRACE_HINT_NONE` |
| `TRACE_HINT_PATH` | macro | `kernel/syscalls.c:2766` | `#define TRACE_HINT_PATH` |
| `batch_kdispatch` | function | `kernel/syscalls.c:812` | `static long batch_kdispatch(uint32_t opcode)` |
| `boot` | function | `kernel/syscalls.c:477` | `* boot (minfo_sleep_init from sched_init);` |
| `by` | function | `kernel/syscalls.c:223` | `* is indexed by (syscall_number - 200). New syscalls are added by: * 1. Adding a MINIOS_SYS_* constant to...` |
| `do_open_path` | function | `kernel/syscalls.c:1265` | `static long do_open_path(const char *path, long flags)` |
| `fd_write` | function | `kernel/syscalls.c:1191` | `static long fd_write(long fd, const char *buf, long cnt)` |
| `first` | function | `kernel/syscalls.c:1928` | `* passes under mm_lock: validate every page first (present, user,  * private), then apply, so a h...` |
| `gfx_win_title` | variable | `kernel/syscalls.c:701` | `extern const char *gfx_win_title;` |
| `gfx_zoom_2x` | variable | `kernel/syscalls.c:420` | `extern int gfx_zoom_2x;` |
| `k_syscall_spawn` | function | `kernel/syscalls.c:3112` | `static int k_syscall_spawn(const char *path, const char *redirect,                              i...` |
| `kfd_claim` | function | `kernel/syscalls.c:1356` | `static long kfd_claim(KFILE *f)` |
| `kfd_claim_from` | function | `kernel/syscalls.c:1331` | `static long kfd_claim_from(KFILE *f, long minfd, int cloexec)` |
| `kfd_cloexec_get` | function | `kernel/syscalls.c:1414` | `static int kfd_cloexec_get(long fd)` |
| `kfd_cloexec_set` | function | `kernel/syscalls.c:1424` | `static void kfd_cloexec_set(long fd, int on)` |
| `kfd_get` | function | `kernel/syscalls.c:88` | `KFILE *kfd_get(int fd)` |
| `kfd_poll_revents` | function | `kernel/syscalls.c:1541` | `int kfd_poll_revents(int fd)` |
| `kfd_put` | function | `kernel/syscalls.c:101` | `void kfd_put(KFILE *f)` |
| `kfd_view_cloexec` | function | `kernel/syscalls.c:195` | `void kfd_view_cloexec(void)` |
| `kfd_view_count` | function | `kernel/syscalls.c:113` | `static int kfd_view_count(kfd_view_t *v)` |
| `kfd_view_current` | function | `kernel/syscalls.c:59` | `static kfd_view_t *kfd_view_current(void)` |
| `kfd_view_root` | function | `kernel/syscalls.c:69` | `kfd_view_t *kfd_view_root(void)` |
| `kfile_status_flags` | function | `kernel/syscalls.c:1435` | `static long kfile_status_flags(KFILE *f)` |
| `kfile_user_read` | function | `kernel/syscalls.c:1576` | `static long kfile_user_read(KFILE *f, char *buf, long cnt)` |
| `kfile_user_write` | function | `kernel/syscalls.c:1606` | `static long kfile_user_write(KFILE *f, const char *buf, long cnt)` |
| `kiovec` | struct | `kernel/syscalls.c:1096` | `` |
| `ksyscall` | function | `kernel/syscalls.c:2798` | `long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6)` |
| `ksyscall_dispatch` | function | `kernel/syscalls.c:2866` | `static long ksyscall_dispatch(long n, long a1, long a2, long a3, long a4, long a5, long a6)` |
| `minfo_sleep_init` | function | `kernel/syscalls.c:484` | `void minfo_sleep_init(int tick_ok)` |
| `minfo_tick_wake` | function | `kernel/syscalls.c:489` | `void minfo_tick_wake(void *ctx)` |
| `minios_syscall_entry_t` | struct | `kernel/syscalls.c:236` | `` |
| `mm_ensure_cur` | function | `kernel/syscalls.c:1725` | `static int mm_ensure_cur(unsigned long start, unsigned long end)` |
| `mmap_tag_file` | function | `kernel/syscalls.c:1775` | `static int mmap_tag_file(unsigned long base, int ino, unsigned long off)` |
| `mprotect_pte` | function | `kernel/syscalls.c:1904` | `static volatile unsigned long *mprotect_pte(unsigned long cr3,         unsigned long va)` |
| `node` | function | `kernel/syscalls.c:2041` | `* mapping is one exact live VMA node (what mmap inserts);` |
| `proc_spawn_elf` | function | `kernel/syscalls.c:3103` | `* proc_spawn_elf (the same path mrun uses) and the caller blocks in * do_waitpid, so the parent address space is...` |
| `products` | function | `kernel/syscalls.c:2853` | `* products (writev cnt*sizeof, poll a2*8, spawn (argc+1)*sizeof) are  * pre-bounded against (END-...` |
| `readlink` | function | `kernel/syscalls.c:2994` | `* readlink (89). */ return readlink_path((const char *)a2, (char *)a3, a4);` |
| `readlink_path` | function | `kernel/syscalls.c:2488` | `static long readlink_path(const char *path, char *buf, long bufsz)` |
| `sb16_audio_device` | function | `kernel/syscalls.c:667` | `static device_t *sb16_audio_device(void)` |
| `sc_extra_name` | struct | `kernel/syscalls.c:2728` | `` |
| `sys_linux_accept` | function | `kernel/syscalls.c:2365` | `static long sys_linux_accept(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_access` | function | `kernel/syscalls.c:2321` | `static long sys_linux_access(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_arch_prctl` | function | `kernel/syscalls.c:2579` | `static long sys_linux_arch_prctl(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_bind` | function | `kernel/syscalls.c:2354` | `static long sys_linux_bind(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_brk` | function | `kernel/syscalls.c:1734` | `static long sys_linux_brk(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_close` | function | `kernel/syscalls.c:1684` | `static long sys_linux_close(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_close_range` | function | `kernel/syscalls.c:1496` | `static long sys_linux_close_range(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_connect` | function | `kernel/syscalls.c:2348` | `static long sys_linux_connect(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_dup` | function | `kernel/syscalls.c:1635` | `static long sys_linux_dup(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_dup2` | function | `kernel/syscalls.c:1650` | `static long sys_linux_dup2(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_dup3` | function | `kernel/syscalls.c:1486` | `static long sys_linux_dup3(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_eventfd` | function | `kernel/syscalls.c:1533` | `static long sys_linux_eventfd(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_eventfd2` | function | `kernel/syscalls.c:1520` | `static long sys_linux_eventfd2(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_fdatasync` | function | `kernel/syscalls.c:2447` | `static long sys_linux_fdatasync(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_flock` | function | `kernel/syscalls.c:2433` | `static long sys_linux_flock(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_fstat` | function | `kernel/syscalls.c:2533` | `static long sys_linux_fstat(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_fsync` | function | `kernel/syscalls.c:2442` | `static long sys_linux_fsync(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_futex` | function | `kernel/syscalls.c:291` | `static long sys_linux_futex(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_getcwd` | function | `kernel/syscalls.c:2452` | `static long sys_linux_getcwd(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_getpeername` | function | `kernel/syscalls.c:2406` | `static long sys_linux_getpeername(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_getsockname` | function | `kernel/syscalls.c:2400` | `static long sys_linux_getsockname(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_getsockopt` | function | `kernel/syscalls.c:2393` | `static long sys_linux_getsockopt(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_gettimeofday` | function | `kernel/syscalls.c:2556` | `static long sys_linux_gettimeofday(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_ioctl` | function | `kernel/syscalls.c:2316` | `static long sys_linux_ioctl(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_listen` | function | `kernel/syscalls.c:2360` | `static long sys_linux_listen(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_lseek` | function | `kernel/syscalls.c:1707` | `static long sys_linux_lseek(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_madvise` | function | `kernel/syscalls.c:2614` | `static long sys_linux_madvise(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_mkdir` | function | `kernel/syscalls.c:2622` | `static long sys_linux_mkdir(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_mmap` | function | `kernel/syscalls.c:1784` | `static long sys_linux_mmap(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_mremap` | function | `kernel/syscalls.c:2046` | `static long sys_linux_mremap(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_munmap` | function | `kernel/syscalls.c:1872` | `static long sys_linux_munmap(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_open` | function | `kernel/syscalls.c:1298` | `static long sys_linux_open(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_pipe` | function | `kernel/syscalls.c:1408` | `static long sys_linux_pipe(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_pipe2` | function | `kernel/syscalls.c:1380` | `static long sys_linux_pipe2(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_poll` | function | `kernel/syscalls.c:2426` | `static long sys_linux_poll(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_prctl` | function | `kernel/syscalls.c:2510` | `static long sys_linux_prctl(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_read` | function | `kernel/syscalls.c:1138` | `static long sys_linux_read(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_readlink` | function | `kernel/syscalls.c:2504` | `static long sys_linux_readlink(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_recvfrom` | function | `kernel/syscalls.c:2376` | `static long sys_linux_recvfrom(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_rename` | function | `kernel/syscalls.c:2519` | `static long sys_linux_rename(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_sendmmsg` | function | `kernel/syscalls.c:2418` | `static long sys_linux_sendmmsg(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_sendmsg` | function | `kernel/syscalls.c:2412` | `static long sys_linux_sendmsg(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_sendto` | function | `kernel/syscalls.c:2371` | `static long sys_linux_sendto(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_setsockopt` | function | `kernel/syscalls.c:2386` | `static long sys_linux_setsockopt(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_shutdown` | function | `kernel/syscalls.c:2381` | `static long sys_linux_shutdown(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_sigaction` | function | `kernel/syscalls.c:2306` | `static long sys_linux_sigaction(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_sigprocmask` | function | `kernel/syscalls.c:2311` | `static long sys_linux_sigprocmask(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_socket` | function | `kernel/syscalls.c:2343` | `static long sys_linux_socket(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_time` | function | `kernel/syscalls.c:282` | `static long sys_linux_time(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_uname` | function | `kernel/syscalls.c:2591` | `static long sys_linux_uname(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_unlink` | function | `kernel/syscalls.c:2464` | `static long sys_linux_unlink(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_write` | function | `kernel/syscalls.c:1215` | `static long sys_linux_write(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_writev` | function | `kernel/syscalls.c:1222` | `static long sys_linux_writev(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_clip_get` | function | `kernel/syscalls.c:768` | `static long sys_minios_clip_get(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_clip_set` | function | `kernel/syscalls.c:758` | `static long sys_minios_clip_set(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_dir_list` | function | `kernel/syscalls.c:936` | `static long sys_minios_dir_list(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_dns` | function | `kernel/syscalls.c:264` | `static long sys_minios_dns(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_doom_frame` | function | `kernel/syscalls.c:407` | `static long sys_minios_doom_frame(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_fb_info` | function | `kernel/syscalls.c:440` | `static long sys_minios_fb_info(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_futex_wait` | function | `kernel/syscalls.c:797` | `static long sys_minios_futex_wait(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_futex_wake` | function | `kernel/syscalls.c:803` | `static long sys_minios_futex_wake(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_getc_raw` | function | `kernel/syscalls.c:861` | `static long sys_minios_getc_raw(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_gfx_title` | function | `kernel/syscalls.c:696` | `static long sys_minios_gfx_title(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_gfx_zoom` | function | `kernel/syscalls.c:418` | `static long sys_minios_gfx_zoom(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_kbd` | function | `kernel/syscalls.c:344` | `static long sys_minios_kbd(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_kbd_raw` | function | `kernel/syscalls.c:376` | `static long sys_minios_kbd_raw(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_lz4_compress` | function | `kernel/syscalls.c:603` | `static long sys_minios_lz4_compress(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_lz4_decompress` | function | `kernel/syscalls.c:616` | `static long sys_minios_lz4_decompress(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_mouse` | function | `kernel/syscalls.c:630` | `static long sys_minios_mouse(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_nk_frame` | function | `kernel/syscalls.c:654` | `static long sys_minios_nk_frame(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_palette` | function | `kernel/syscalls.c:364` | `static long sys_minios_palette(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_pcm2_close` | function | `kernel/syscalls.c:748` | `static long sys_minios_pcm2_close(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_pcm2_open` | function | `kernel/syscalls.c:735` | `static long sys_minios_pcm2_open(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_pcm2_write` | function | `kernel/syscalls.c:740` | `static long sys_minios_pcm2_write(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_pcspk_init` | function | `kernel/syscalls.c:389` | `static long sys_minios_pcspk_init(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_pcspk_tone` | function | `kernel/syscalls.c:393` | `static long sys_minios_pcspk_tone(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_pcspk_vol` | function | `kernel/syscalls.c:460` | `static long sys_minios_pcspk_vol(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_rlimit` | function | `kernel/syscalls.c:895` | `static long sys_minios_rlimit(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_rtc` | function | `kernel/syscalls.c:427` | `static long sys_minios_rtc(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_sb16_open` | function | `kernel/syscalls.c:673` | `static long sys_minios_sb16_open(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_sb16_pump` | function | `kernel/syscalls.c:710` | `static long sys_minios_sb16_pump(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_sb16_stream_close` | function | `kernel/syscalls.c:718` | `static long sys_minios_sb16_stream_close(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_sb16_stream_open` | function | `kernel/syscalls.c:714` | `static long sys_minios_sb16_stream_open(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_sb16_stream_submit` | function | `kernel/syscalls.c:722` | `static long sys_minios_sb16_stream_submit(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_sb16_stream_vol` | function | `kernel/syscalls.c:784` | `static long sys_minios_sb16_stream_vol(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_sb16_submit` | function | `kernel/syscalls.c:685` | `static long sys_minios_sb16_submit(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_spawn` | function | `kernel/syscalls.c:592` | `static long sys_minios_spawn(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_submit_batch` | function | `kernel/syscalls.c:872` | `static long sys_minios_submit_batch(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_time` | function | `kernel/syscalls.c:340` | `static long sys_minios_time(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_tls_retired` | function | `kernel/syscalls.c:269` | `static long sys_minios_tls_retired(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_vga_mode` | function | `kernel/syscalls.c:382` | `static long sys_minios_vga_mode(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `syscall_name` | function | `kernel/syscalls.c:2744` | `const char *syscall_name(long n)` |
| `syscall_trace_enabled` | function | `kernel/syscalls.c:1108` | `long syscall_trace_enabled(void)` |
| `syscall_trace_set` | function | `kernel/syscalls.c:1109` | `void syscall_trace_set(int on)` |
| `syscall_trace_shown` | function | `kernel/syscalls.c:1112` | `unsigned long syscall_trace_shown(void)` |
| `syscall_trace_verbose_enabled` | function | `kernel/syscalls.c:1110` | `long syscall_trace_verbose_enabled(void)` |
| `syscall_trace_verbose_set` | function | `kernel/syscalls.c:1111` | `void syscall_trace_verbose_set(int on)` |
| `trace_hint_print` | function | `kernel/syscalls.c:2785` | `static void trace_hint_print(long n, int kind, const char *path,                              lon...` |
| `trace_is_noisy` | function | `kernel/syscalls.c:2716` | `static int trace_is_noisy(long n)` |
| `unchanged` | function | `kernel/syscalls.c:1127` | `* unchanged (same code, same order of checks). Numbers >= 200 that * overlap real Linux ABIs stay in the switch as...` |
| `untouched` | function | `kernel/syscalls.c:137` | `* child untouched (caller refuses fail-closed). */ int kfd_view_copy(proc_t *child, proc_t *parent)` |
| `user_range_ok` | function | `kernel/syscalls.c:2836` | `int user_range_ok(unsigned long p, unsigned long len)` |
| `view` | function | `kernel/syscalls.c:501` | `* view (same as the `clear` builtin). Anything else is -EINVAL. Each  * out-word is range-checked...` |
| `vma_free_cover` | function | `kernel/syscalls.c:2000` | `static vma_node_t *vma_free_cover(unsigned long base, unsigned long len)` |
| `vma_live_overlap` | function | `kernel/syscalls.c:2019` | `static int vma_live_overlap(unsigned long base, unsigned long len)` |
| `wall_us_now` | function | `kernel/syscalls.c:254` | `unsigned long wall_us_now(void)` |
| `LINUX_ECHILD` | macro | `kernel/syscalls_proc.c:198` | `#define LINUX_ECHILD` |
| `LINUX_EINVAL` | macro | `kernel/syscalls_proc.c:199` | `#define LINUX_EINVAL` |
| `LINUX_SIGKILL` | macro | `kernel/syscalls_proc.c:194` | `#define LINUX_SIGKILL` |
| `LINUX_SIG_MAX` | macro | `kernel/syscalls_proc.c:195` | `#define LINUX_SIG_MAX` |
| `LINUX_STATUS_CODE` | macro | `kernel/syscalls_proc.c:197` | `#define LINUX_STATUS_CODE` |
| `LINUX_STATUS_SHIFT` | macro | `kernel/syscalls_proc.c:196` | `#define LINUX_STATUS_SHIFT` |
| `LINUX_WNOHANG` | macro | `kernel/syscalls_proc.c:193` | `#define LINUX_WNOHANG` |
| `groups` | function | `kernel/syscalls_proc.c:213` | `* groups (pid 0 and < -1) are not modelled and wait for any child. */ long sys_linux_wait4(long a...` |
| `kill` | function | `kernel/syscalls_proc.c:192` | `* historic kill (SIGKILL), -N is signal N (a seccomp kill is -SIGSYS). */ #define LINUX_WNOHANG  ...` |
| `state` | function | `kernel/syscalls_proc.c:5` | `* touches only scheduler state (current_pid, procs[], do_* / * seccomp_* / yield) plus the kernel-wide user_range_ok...` |
| `sys_linux_clone` | function | `kernel/syscalls_proc.c:83` | `long sys_linux_clone(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_execve` | function | `kernel/syscalls_proc.c:99` | `long sys_linux_execve(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_exit` | function | `kernel/syscalls_proc.c:184` | `long sys_linux_exit(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_fork` | function | `kernel/syscalls_proc.c:89` | `long sys_linux_fork(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_getpid` | function | `kernel/syscalls_proc.c:75` | `long sys_linux_getpid(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_gettid` | function | `kernel/syscalls_proc.c:236` | `long sys_linux_gettid(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_kill` | function | `kernel/syscalls_proc.c:231` | `long sys_linux_kill(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_vfork` | function | `kernel/syscalls_proc.c:94` | `long sys_linux_vfork(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_yield` | function | `kernel/syscalls_proc.c:66` | `long sys_linux_yield(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_clone` | function | `kernel/syscalls_proc.c:17` | `long sys_minios_clone(long flags, long newsp, long a3, long a4, long a5, long a6)` |
| `sys_minios_nice` | function | `kernel/syscalls_proc.c:53` | `long sys_minios_nice(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_seccomp` | function | `kernel/syscalls_proc.c:36` | `long sys_minios_seccomp(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_thread_spawn` | function | `kernel/syscalls_proc.c:23` | `long sys_minios_thread_spawn(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `tick_audio_count` | function | `kernel/tick.c:133` | `int tick_audio_count(void)` |
| `tick_desktop_count` | function | `kernel/tick.c:144` | `int tick_desktop_count(void)` |
| `tick_desktop_due` | function | `kernel/tick.c:160` | `int tick_desktop_due(unsigned long long ticks, unsigned interval)` |
| `tick_register_audio` | function | `kernel/tick.c:58` | `int tick_register_audio(tick_fn_t fn, void *ctx)` |
| `tick_register_desktop` | function | `kernel/tick.c:76` | `int tick_register_desktop(tick_fn_t fn, void *ctx)` |
| `tick_register_usb` | function | `kernel/tick.c:89` | `int tick_register_usb(tick_fn_t fn, void *ctx)` |
| `tick_reset` | function | `kernel/tick.c:34` | `void tick_reset(void)` |
| `tick_run_audio` | function | `kernel/tick.c:113` | `void tick_run_audio(void)` |
| `tick_run_desktop` | function | `kernel/tick.c:123` | `void tick_run_desktop(void)` |
| `tick_run_usb` | function | `kernel/tick.c:103` | `void tick_run_usb(void)` |
| `tick_slot_t` | struct | `kernel/tick.c:15` | `` |
| `ktime_init` | function | `kernel/time.c:19` | `static void ktime_init(void)` |
| `ktime_ms` | function | `kernel/time.c:33` | `unsigned long ktime_ms(void)` |
| `ktime_rdtsc` | function | `kernel/time.c:13` | `static unsigned long ktime_rdtsc(void)` |
| `ktime_us` | function | `kernel/time.c:41` | `unsigned long ktime_us(void)` |
| `CURSOR_TIP_X` | macro | `kernel/vga_cursor.c:28` | `#define CURSOR_TIP_X` |
| `CURSOR_TIP_Y` | macro | `kernel/vga_cursor.c:29` | `#define CURSOR_TIP_Y` |
| `cursor_draw` | function | `kernel/vga_cursor.c:68` | `static void cursor_draw(int mx, int my)` |
| `cursor_erase` | function | `kernel/vga_cursor.c:133` | `void cursor_erase(void)` |
| `cursor_has_set_neighbour` | function | `kernel/vga_cursor.c:57` | `static int cursor_has_set_neighbour(int i, int j)` |
| `cursor_invalidate` | function | `kernel/vga_cursor.c:141` | `void cursor_invalidate(void)` |
| `cursor_is_set` | function | `kernel/vga_cursor.c:50` | `static int cursor_is_set(int i, int j)` |
| `cursor_move` | function | `kernel/vga_cursor.c:116` | `void cursor_move(int mx, int my)` |
| `cursor_note_repaint` | function | `kernel/vga_cursor.c:147` | `void cursor_note_repaint(int x0, int y0, int w, int h)` |
| `cursor_over` | function | `kernel/vga_cursor.c:96` | `int cursor_over(int x0, int y0, int w, int h)` |
| `cursor_place` | function | `kernel/vga_cursor.c:106` | `void cursor_place(int mx, int my)` |
| `cursor_restore` | function | `kernel/vga_cursor.c:81` | `static void cursor_restore(int mx, int my)` |
| `cursor_save_bg` | function | `kernel/vga_cursor.c:40` | `static void cursor_save_bg(int mx, int my)` |
| `FBT` | macro | `kernel/vga_fb.c:145` | `#define FBT` |
| `FB_OFFSET` | macro | `kernel/vga_fb.c:1607` | `#define FB_OFFSET(x,y)` |
| `GFX_CURSOR_IDLE_TICKS` | macro | `kernel/vga_fb.c:515` | `#define GFX_CURSOR_IDLE_TICKS` |
| `GFX_KEEP_BYTES` | macro | `kernel/vga_fb.c:489` | `#define GFX_KEEP_BYTES` |
| `GFX_PROG_LEN` | macro | `kernel/vga_fb.c:556` | `#define GFX_PROG_LEN` |
| `GFX_SRC_IDX` | macro | `kernel/vga_fb.c:487` | `#define GFX_SRC_IDX` |
| `GFX_SRC_RGB` | macro | `kernel/vga_fb.c:488` | `#define GFX_SRC_RGB` |
| `LG_LINE` | macro | `kernel/vga_fb.c:296` | `#define LG_LINE(a)` |
| `TB_GFX_TITLE_MAX` | macro | `kernel/vga_fb.c:2405` | `#define TB_GFX_TITLE_MAX` |
| `WIN_DEF_COLS` | macro | `kernel/vga_fb.c:877` | `#define WIN_DEF_COLS` |
| `WIN_DEF_ROWS` | macro | `kernel/vga_fb.c:878` | `#define WIN_DEF_ROWS` |
| `WIN_DEF_X` | macro | `kernel/vga_fb.c:879` | `#define WIN_DEF_X` |
| `WIN_DEF_Y` | macro | `kernel/vga_fb.c:880` | `#define WIN_DEF_Y` |
| `WM_ELINE_SZ` | macro | `kernel/vga_fb.c:909` | `#define WM_ELINE_SZ` |
| `WM_MAX_TERMS` | macro | `kernel/vga_fb.c:908` | `#define WM_MAX_TERMS` |
| `act_nrows` | function | `kernel/vga_fb.c:334` | `static int act_nrows(void)` |
| `alone` | function | `kernel/vga_fb.c:1319` | `* window alone (an unfocused graphics window minimizes to the taskbar,  * exactly like the hidden...` |
| `app` | function | `kernel/vga_fb.c:1136` | `* a gfx child spawned from another gfx app (file -> vedit) keeps the * terminal focused, so its keys and wheel keep...` |
| `buffer` | function | `kernel/vga_fb.c:2758` | `* owns the buffer (indices reset, render reads an empty ring). */ void term_clear(void)` |
| `ci_eq` | function | `kernel/vga_fb.c:595` | `static int ci_eq(const char *a, const char *b)` |
| `command` | function | `kernel/vga_fb.c:4028` | `* its launch command (config-driven, covers apps that never set a window * title);` |
| `compositions` | function | `kernel/vga_fb.c:133` | `* compositions (an ISR tick composing inside a syscall composition) draw * into the same shadow and leave the...` |
| `content` | function | `kernel/vga_fb.c:1193` | `* windows would share content (same prompt/output on both) and a park  * would alias src == dst. ...` |
| `coordinates` | function | `kernel/vga_fb.c:723` | `* windows keep the exact historical coordinates (including outside the * window);` |
| `desktop_shortcuts_draw` | function | `kernel/vga_fb.c:3939` | `void desktop_shortcuts_draw(void)` |
| `desktop_shortcuts_hit_test` | function | `kernel/vga_fb.c:4054` | `const char *desktop_shortcuts_hit_test(int mx, int my)` |
| `desktop_shortcuts_load` | function | `kernel/vga_fb.c:3713` | `void desktop_shortcuts_load(void)` |
| `directly` | function | `kernel/vga_fb.c:2127` | `* RGB sources pack directly (quantized to the wallpaper cube in 8-bit). */ static void gfx_scale_...` |
| `disp_clamp` | function | `kernel/vga_fb.c:345` | `static void disp_clamp(void)` |
| `dock_bounce_counts` | function | `kernel/vga_fb.c:3821` | `void dock_bounce_counts(unsigned long *kicks, unsigned long *paints)` |
| `dock_bounce_elapsed` | function | `kernel/vga_fb.c:3837` | `static unsigned long dock_bounce_elapsed(void)` |
| `dock_bounce_live` | function | `kernel/vga_fb.c:3845` | `static int dock_bounce_live(void)` |
| `dock_click_count` | function | `kernel/vga_fb.c:3831` | `void dock_click_count(unsigned long *edges)` |
| `dock_hover_index` | function | `kernel/vga_fb.c:3794` | `static int dock_hover_index(int mx, int my)` |
| `dock_label_px` | function | `kernel/vga_fb.c:3679` | `static int dock_label_px(const struct desktop_shortcut *sc)` |
| `dock_paint_hover` | function | `kernel/vga_fb.c:3997` | `static void dock_paint_hover(int hover)` |
| `dock_paint_icons` | function | `kernel/vga_fb.c:3903` | `static void dock_paint_icons(int hover)` |
| `dock_pending_active` | function | `kernel/vga_fb.c:3895` | `int dock_pending_active(void)` |
| `draw_scrollbar` | function | `kernel/vga_fb.c:2663` | `static void draw_scrollbar(void)` |
| `draw_speaker_icon` | function | `kernel/vga_fb.c:2438` | `static void draw_speaker_icon(int x, int y, uint8_t color)` |
| `draw_title_win` | function | `kernel/vga_fb.c:2376` | `static void draw_title_win(int idx, int focused)` |
| `escapes` | function | `kernel/vga_fb.c:2827` | `* swallowing them here keeps the escapes (which the serial side needs)      * from printing as li...` |
| `fb_bytes_per_pixel` | function | `kernel/vga_fb.c:117` | `int fb_bytes_per_pixel(void)` |
| `fb_compose_begin` | function | `kernel/vga_fb.c:221` | `static int fb_compose_begin(void)` |
| `fb_compose_end` | function | `kernel/vga_fb.c:234` | `static void fb_compose_end(int owner)` |
| `fb_copy_bytes` | function | `kernel/vga_fb.c:151` | `static void fb_copy_bytes(volatile void *dst, const volatile void *src, unsigned long n)` |
| `fb_fill_run` | function | `kernel/vga_fb.c:1802` | `static void fb_fill_run(int x, int y, int n, unsigned long px)` |
| `fb_fill_u32` | function | `kernel/vga_fb.c:169` | `static void fb_fill_u32(volatile void *dst, unsigned int v, unsigned long n)` |
| `fb_frame_bytes` | function | `kernel/vga_fb.c:183` | `static unsigned long fb_frame_bytes(void)` |
| `fb_glyph` | function | `kernel/vga_fb.c:1890` | `static const uint8_t *fb_glyph(unsigned char c)` |
| `fb_pack_idx` | function | `kernel/vga_fb.c:1685` | `static unsigned long fb_pack_idx(unsigned idx)` |
| `fb_present_shadow` | function | `kernel/vga_fb.c:210` | `static void fb_present_shadow(void)` |
| `fb_read_packed` | function | `kernel/vga_fb.c:1721` | `unsigned long fb_read_packed(int x, int y)` |
| `fb_read_row_packed` | function | `kernel/vga_fb.c:1780` | `void fb_read_row_packed(int x, int y, unsigned int *dst, int n)` |
| `fb_shadow_ready` | function | `kernel/vga_fb.c:189` | `static int fb_shadow_ready(void)` |
| `fb_write_packed` | function | `kernel/vga_fb.c:1701` | `void fb_write_packed(int x, int y, unsigned long rgb)` |
| `fb_write_row_packed` | function | `kernel/vga_fb.c:1750` | `void fb_write_row_packed(int x, int y, const unsigned int *src, int n)` |
| `first` | function | `kernel/vga_fb.c:419` | `* screen ever showing it whole first (the old flash-then-melt). */ static unsigned int *fx_start_...` |
| `flag` | function | `kernel/vga_fb.c:496` | `* is the minimized flag (the program keeps running, nothing composites);` |
| `from` | function | `kernel/vga_fb.c:3134` | `* leaving returns to the view it came from (floating or tiled). Returns  * 0 on success, -1 witho...` |
| `gfx_animate` | function | `kernel/vga_fb.c:3036` | `static void gfx_animate(const wm_gfxview_rect_t *from, const wm_gfxview_rect_t *to,              ...` |
| `gfx_compose` | function | `kernel/vga_fb.c:2263` | `static void gfx_compose(const volatile uint8_t *src, int kind, int sw, int sh,                   ...` |
| `gfx_covers_screen` | function | `kernel/vga_fb.c:527` | `static int gfx_covers_screen(void)` |
| `gfx_drop_focus` | function | `kernel/vga_fb.c:3123` | `static void gfx_drop_focus(int source)` |
| `gfx_float_frame` | function | `kernel/vga_fb.c:693` | `static int gfx_float_frame(wm_gfxview_rect_t *out)` |
| `gfx_keep_save` | function | `kernel/vga_fb.c:533` | `static void gfx_keep_save(const volatile uint8_t *src, int kind, int sw, int sh)` |
| `gfx_letterbox` | function | `kernel/vga_fb.c:2232` | `static void gfx_letterbox(const wm_gfxview_t *v)` |
| `gfx_prog_icon` | function | `kernel/vga_fb.c:608` | `static const uint8_t *gfx_prog_icon(void)` |
| `gfx_snap` | function | `kernel/vga_fb.c:3255` | `static void gfx_snap(int zone)` |
| `gfx_task_icon` | function | `kernel/vga_fb.c:4033` | `static const uint8_t *gfx_task_icon(void)` |
| `gfx_taskbar_rect` | function | `kernel/vga_fb.c:3086` | `static void gfx_taskbar_rect(wm_gfxview_rect_t *r)` |
| `gfx_title` | function | `kernel/vga_fb.c:2251` | `static void gfx_title(const wm_gfxview_t *v)` |
| `gfx_transition` | function | `kernel/vga_fb.c:917` | `static void gfx_transition(const wm_gfxview_rect_t *from, int from_titled);` |
| `gfx_view_for` | function | `kernel/vga_fb.c:667` | `static int gfx_view_for(int sw, int sh, wm_gfxview_t *v)` |
| `gfx_view_in_rect` | function | `kernel/vga_fb.c:3017` | `static void gfx_view_in_rect(const wm_gfxview_rect_t *r, int titled, wm_gfxview_t *v)` |
| `gfx_view_publish` | function | `kernel/vga_fb.c:679` | `static void gfx_view_publish(const wm_gfxview_t *v)` |
| `icon_decode` | function | `kernel/vga_fb.c:3617` | `static const uint8_t *icon_decode(const char *path)` |
| `icon_embedded` | function | `kernel/vga_fb.c:3597` | `static const uint8_t *icon_embedded(const char *name)` |
| `icon_embedded_rgba` | function | `kernel/vga_fb.c:3651` | `static const uint8_t *icon_embedded_rgba(const uint8_t *idx)` |
| `icon_nearest` | function | `kernel/vga_fb.c:3581` | `static int icon_nearest(int r, int g, int b)` |
| `letterbox` | function | `kernel/vga_fb.c:500` | `* present to repaint chrome plus letterbox (after a desktop redraw or a * view change);` |
| `lg_get` | function | `kernel/vga_fb.c:305` | `static const char *lg_get(int i)` |
| `lg_push` | function | `kernel/vga_fb.c:312` | `static void lg_push(const char *line, int len)` |
| `line` | function | `kernel/vga_fb.c:2818` | `* display stale bytes left over from a longer previous line (e.g. the prompt  * would show the ta...` |
| `line_at` | function | `kernel/vga_fb.c:363` | `static const char *line_at(int abs, int *off)` |
| `line_nrows` | function | `kernel/vga_fb.c:327` | `static int line_nrows(int len)` |
| `mouse_apply_wheel` | function | `kernel/vga_fb.c:4094` | `static void mouse_apply_wheel(int wheel, int step)` |
| `mouse_drag_gfx` | function | `kernel/vga_fb.c:4118` | `static void mouse_drag_gfx(const wm_geom_config_t *gcfg, int mx, int my)` |
| `mouse_drag_term` | function | `kernel/vga_fb.c:4170` | `static void mouse_drag_term(const wm_geom_config_t *gcfg, int win_w, int mx, int my, int gfx_cursor)` |
| `mouse_focus_topmost` | function | `kernel/vga_fb.c:4068` | `static int mouse_focus_topmost(int mx, int my)` |
| `mouse_scrollbar` | function | `kernel/vga_fb.c:4193` | `static void mouse_scrollbar(const wm_geom_config_t *gcfg, int mx, int my)` |
| `path` | function | `kernel/vga_fb.c:4227` | `* present path (blit_gfx_buf) is the sole cursor painter. The tick * used to share the sprite state with it and...` |
| `pipe_field` | function | `kernel/vga_fb.c:3563` | `static const char *pipe_field(const char *line, int idx, char *buf, int buflen)` |
| `pointer` | function | `kernel/vga_fb.c:4115` | `* tiled window floats it at native size under the pointer (the grab point * keeps its relative position along the...` |
| `render_blank_row` | function | `kernel/vga_fb.c:2698` | `static void render_blank_row(int vrow)` |
| `render_row` | function | `kernel/vga_fb.c:2708` | `static void render_row(int vrow, int abs)` |
| `shcmd_base` | function | `kernel/vga_fb.c:578` | `static void shcmd_base(const char *cmd, char *out, unsigned long cap)` |
| `shortcut_cell_left` | function | `kernel/vga_fb.c:3706` | `static int shortcut_cell_left(int i)` |
| `shortcut_draw_scaled` | function | `kernel/vga_fb.c:3769` | `static void shortcut_draw_scaled(const struct desktop_shortcut *sc,                              ...` |
| `shortcuts_layout` | function | `kernel/vga_fb.c:3688` | `static void shortcuts_layout(void)` |
| `state` | function | `kernel/vga_fb.c:4339` | `* ignores the button state (the arming press is consumed) and settles      * once on expiry, so t...` |
| `taskbar` | function | `kernel/vga_fb.c:2079` | `* minimize hides the app to the taskbar (it never closes it), maximize  * toggles true fullscreen...` |
| `taskbar_handle_click` | function | `kernel/vga_fb.c:2603` | `static void taskbar_handle_click(int mx, int my)` |
| `taskbar_layout` | function | `kernel/vga_fb.c:2407` | `static void taskbar_layout(void)` |
| `taskbar_render` | function | `kernel/vga_fb.c:2447` | `static void taskbar_render(void)` |
| `taskbar_theme_cycle` | function | `kernel/vga_fb.c:2563` | `static void taskbar_theme_cycle(void)` |
| `taskbar_tick` | function | `kernel/vga_fb.c:2526` | `static void taskbar_tick(void)` |
| `term_close_default` | function | `kernel/vga_fb.c:3288` | `static void term_close_default(void)` |
| `term_finish_layout` | function | `kernel/vga_fb.c:3372` | `static void term_finish_layout(void)` |
| `term_max_cols` | function | `kernel/vga_fb.c:3363` | `static int term_max_cols(void)` |
| `term_max_rows` | function | `kernel/vga_fb.c:3367` | `static int term_max_rows(void)` |
| `term_recalc` | function | `kernel/vga_fb.c:2350` | `static void term_recalc(void)` |
| `term_render` | function | `kernel/vga_fb.c:2743` | `static void term_render(void)` |
| `term_render_active` | function | `kernel/vga_fb.c:2775` | `static void term_render_active(void)` |
| `term_toggle_fullscreen` | function | `kernel/vga_fb.c:3208` | `static void term_toggle_fullscreen(void)` |
| `term_toggle_minimize` | function | `kernel/vga_fb.c:3231` | `static void term_toggle_minimize(void)` |
| `termwin_t` | struct | `kernel/vga_fb.c:919` | `` |
| `text_px` | function | `kernel/vga_fb.c:1987` | `static void text_px(int px, int py, const char *s, uint8_t fg, uint8_t bg)` |
| `title` | function | `kernel/vga_fb.c:2457` | `* 8px row plus its title (bright when focused). The hint line * starts after it instead of underneath. */ const...` |
| `total_rows` | function | `kernel/vga_fb.c:337` | `static int total_rows(void)` |
| `tw_hit` | function | `kernel/vga_fb.c:1564` | `static int tw_hit(int i, int mx, int my)` |
| `tw_park` | function | `kernel/vga_fb.c:976` | `static void tw_park(int i)` |
| `tw_select` | function | `kernel/vga_fb.c:1066` | `static void tw_select(int i)` |
| `tw_unpark` | function | `kernel/vga_fb.c:1006` | `static void tw_unpark(int i)` |
| `vga_fb_act_empty` | function | `kernel/vga_fb.c:1504` | `int vga_fb_act_empty(void)` |
| `vga_fb_blit_gfx_window` | function | `kernel/vga_fb.c:2326` | `void vga_fb_blit_gfx_window(void)` |
| `vga_fb_blit_nk_rgb_window` | function | `kernel/vga_fb.c:2341` | `void vga_fb_blit_nk_rgb_window(void)` |
| `vga_fb_blit_nk_window` | function | `kernel/vga_fb.c:2335` | `void vga_fb_blit_nk_window(void)` |
| `vga_fb_boot_config` | function | `kernel/vga_fb.c:90` | `void vga_fb_boot_config(void)` |
| `vga_fb_char` | function | `kernel/vga_fb.c:1962` | `void vga_fb_char(int col, int row, char c, uint8_t fg, uint8_t bg)` |
| `vga_fb_clear` | function | `kernel/vga_fb.c:1921` | `void vga_fb_clear(void)` |
| `vga_fb_clear_prompt` | function | `kernel/vga_fb.c:1513` | `void vga_fb_clear_prompt(void)` |
| `vga_fb_close_active` | function | `kernel/vga_fb.c:3304` | `int vga_fb_close_active(void)` |
| `vga_fb_draw_desktop` | function | `kernel/vga_fb.c:2922` | `void vga_fb_draw_desktop(void)` |
| `vga_fb_focus_event` | function | `kernel/vga_fb.c:961` | `const wm_notify_event_t *vga_fb_focus_event(void)` |
| `vga_fb_focus_get` | function | `kernel/vga_fb.c:1078` | `int vga_fb_focus_get(void)` |
| `vga_fb_focus_id` | function | `kernel/vga_fb.c:1160` | `int vga_fb_focus_id(int id)` |
| `vga_fb_focus_next` | function | `kernel/vga_fb.c:1095` | `void vga_fb_focus_next(void)` |
| `vga_fb_focus_report` | function | `kernel/vga_fb.c:967` | `void vga_fb_focus_report(int before, int source)` |
| `vga_fb_gfx_cursor_draw` | function | `kernel/vga_fb.c:751` | `static void vga_fb_gfx_cursor_draw(void)` |
| `vga_fb_gfx_cursor_erase` | function | `kernel/vga_fb.c:741` | `static void vga_fb_gfx_cursor_erase(void)` |

Next: [SYMBOLS_p10.md](SYMBOLS_p10.md)
