# Symbols (page 9 of 26)
Previous: [SYMBOLS_p8.md](SYMBOLS_p8.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `sb_reset` | function | `kernel/scrollback.c:34` | `void sb_reset(void)` |
| `vga_scroll` | function | `kernel/scrollback.c:4` | `* Captured lazily from vga_scroll();` |
| `SBPF_MEM_ALL` | macro | `kernel/seccomp_bpf.c:14` | `#define SBPF_MEM_ALL` |
| `SBPF_MISC_MASK` | macro | `kernel/seccomp_bpf.c:13` | `#define SBPF_MISC_MASK` |
| `SBPF_MODE_MASK` | macro | `kernel/seccomp_bpf.c:11` | `#define SBPF_MODE_MASK` |
| `SBPF_OP_MASK` | macro | `kernel/seccomp_bpf.c:8` | `#define SBPF_OP_MASK` |
| `SBPF_RVAL_MASK` | macro | `kernel/seccomp_bpf.c:12` | `#define SBPF_RVAL_MASK` |
| `SBPF_SIZE_MASK` | macro | `kernel/seccomp_bpf.c:10` | `#define SBPF_SIZE_MASK` |
| `SBPF_SRC_MASK` | macro | `kernel/seccomp_bpf.c:9` | `#define SBPF_SRC_MASK` |
| `sbpf_action_rank` | function | `kernel/seccomp_bpf.c:194` | `int sbpf_action_rank(unsigned int action)` |
| `sbpf_check` | function | `kernel/seccomp_bpf.c:69` | `int sbpf_check(const sbpf_insn *prog, unsigned len, unsigned short *scratch)` |
| `sbpf_load_word` | function | `kernel/seccomp_bpf.c:114` | `static unsigned int sbpf_load_word(const sbpf_data *d, unsigned off)` |
| `sbpf_opcode_ok` | function | `kernel/seccomp_bpf.c:17` | `static int sbpf_opcode_ok(const sbpf_insn *in)` |
| `sbpf_run` | function | `kernel/seccomp_bpf.c:120` | `unsigned int sbpf_run(const sbpf_insn *prog, unsigned len, const sbpf_data *d)` |
| `COM1` | macro | `kernel/serial.c:18` | `#define COM1` |
| `serial_available` | function | `kernel/serial.c:42` | `int serial_available(void)` |
| `serial_e_count` | function | `kernel/serial.c:38` | `unsigned long serial_e_count(void)` |
| `serial_getc` | function | `kernel/serial.c:44` | `int serial_getc(void)` |
| `serial_init` | function | `kernel/serial.c:20` | `void serial_init(void)` |
| `serial_putc` | function | `kernel/serial.c:33` | `void serial_putc(char c)` |
| `serial_puts` | function | `kernel/serial.c:40` | `void serial_puts(const char *s)` |
| `serial_rx_ready` | function | `kernel/serial.c:31` | `static int serial_rx_ready(void)` |
| `serial_tx_ready` | function | `kernel/serial.c:30` | `static int serial_tx_ready(void)` |
| `HTTPD_IO_CHUNK` | macro | `kernel/shell.c:2505` | `#define HTTPD_IO_CHUNK` |
| `HTTPD_REQ_CAP` | macro | `kernel/shell.c:2504` | `#define HTTPD_REQ_CAP` |
| `PIPE_HOP_MAX` | macro | `kernel/shell.c:4033` | `#define PIPE_HOP_MAX` |
| `QEMU_PM_PORT` | macro | `kernel/shell.c:1013` | `#define QEMU_PM_PORT` |
| `SHELL_BUILTIN_COUNT` | macro | `kernel/shell.c:229` | `#define SHELL_BUILTIN_COUNT` |
| `SHELL_CVM_INTERP` | macro | `kernel/shell.c:50` | `#define SHELL_CVM_INTERP` |
| `SHELL_HIST_MAX` | macro | `kernel/shell.c:95` | `#define SHELL_HIST_MAX` |
| `SHELL_LS_CAP` | macro | `kernel/shell.c:2762` | `#define SHELL_LS_CAP` |
| `SHELL_RUN_DIRS` | macro | `kernel/shell.c:69` | `#define SHELL_RUN_DIRS` |
| `ShellRunDir` | struct | `kernel/shell.c:58` | `` |
| `VMA` | function | `kernel/shell.c:2149` | `* plus the live VMA (mmap) tree. The walk is bounded (64-deep explicit  * stack, 128 regions prin...` |
| `XXH_STATIC_LINKING_ONLY` | macro | `kernel/shell.c:25` | `#define XXH_STATIC_LINKING_ONLY` |
| `code` | function | `kernel/shell.c:1356` | `* the last exit code (130 when interrupted). */ static int shell_wait_fg(int *pids, int n, int ki...` |
| `context` | function | `kernel/shell.c:1647` | `* from ISR context (which corrupts the running program's state). */ shell_queue_launch(cmd);` |
| `desktop_flag` | function | `kernel/shell.c:1509` | `static void desktop_flag(const char *name)` |
| `desktop_flag_on` | function | `kernel/shell.c:1519` | `static int desktop_flag_on(const char *name)` |
| `desktop_path` | function | `kernel/shell.c:1500` | `static void desktop_path(const char *name, char *dst, unsigned cap)` |
| `desktop_srv_alive` | function | `kernel/shell.c:1541` | `static int desktop_srv_alive(void)` |
| `desktop_unflag` | function | `kernel/shell.c:830` | `static void desktop_unflag(const char *name);` |
| `driver` | function | `kernel/shell.c:3264` | `* stream through the fat: VFS driver ("img:fatpath" per open,      * registered at boot beside me...` |
| `etrel_path_trusted` | function | `kernel/shell.c:1103` | `static int etrel_path_trusted(const char *full)` |
| `flows` | function | `kernel/shell.c:1533` | `* and external flows (make wl) set it themselves. */ static void desktop_unflag(const char *name)` |
| `frame` | function | `kernel/shell.c:3658` | `* not live in this frame (stack discipline, CLAUDE.md). */ struct ps_row *snap = (struct ps_row...` |
| `gfx_parse_int` | function | `kernel/shell.c:1692` | `static int gfx_parse_int(const char *s, int *out)` |
| `gfx_read_palette` | function | `kernel/shell.c:1712` | `static void gfx_read_palette(unsigned char pal[768])` |
| `job_row` | struct | `kernel/shell.c:2020` | `` |
| `line` | function | `kernel/shell.c:443` | `* to the live line (handled by the caller resetting shell_hist_idx). */ static void shell_hist_na...` |
| `outw_port` | function | `kernel/shell.c:1009` | `static inline void outw_port(unsigned short port, unsigned short val)` |
| `ps_row` | struct | `kernel/shell.c:3656` | `` |
| `root` | function | `kernel/shell.c:648` | `* MiniFS root (where the big ELFs live under bare names), * and only the highest-priority non-empty tier is kept. An...` |
| `shell_cmd_desktop` | function | `kernel/shell.c:1557` | `static void shell_cmd_desktop(int argc, char **argv)` |
| `shell_cmd_gdb` | function | `kernel/shell.c:2343` | `static void shell_cmd_gdb(int argc, char **argv)` |
| `shell_cmd_gfx` | function | `kernel/shell.c:1719` | `static void shell_cmd_gfx(int argc, char **argv)` |
| `shell_cmd_hash` | function | `kernel/shell.c:2386` | `static void shell_cmd_hash(int argc, char **argv)` |
| `shell_cmd_jobs` | function | `kernel/shell.c:2019` | `static void shell_cmd_jobs(void)` |
| `shell_cmd_kill` | function | `kernel/shell.c:2093` | `static void shell_cmd_kill(int argc, char **argv)` |
| `shell_cmd_mem` | function | `kernel/shell.c:2116` | `static void shell_cmd_mem(void)` |
| `shell_cmd_mrun` | function | `kernel/shell.c:1409` | `static void shell_cmd_mrun(int argc, char **argv)` |
| `shell_cmd_poweroff` | function | `kernel/shell.c:1015` | `static void shell_cmd_poweroff(void)` |
| `shell_cmd_wait` | function | `kernel/shell.c:2058` | `static void shell_cmd_wait(int argc, char **argv)` |
| `shell_cmd_wm` | function | `kernel/shell.c:1871` | `static void shell_cmd_wm(int argc, char **argv)` |
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
| `shell_is_pipe_tok` | function | `kernel/shell.c:4035` | `static int shell_is_pipe_tok(const char *a)` |
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
| `shell_run_stage` | function | `kernel/shell.c:4074` | `static char *shell_run_stage(char **sargv, int sargc,         const char *input, unsigned long in...` |
| `stdout` | function | `kernel/shell.c:4023` | `* the pipe exactly like stdout (`2>` is an alias of `>`). * Per-stage `exit code:` lines report to the console...` |
| `terminal` | function | `kernel/shell.c:2921` | `* sequence clears serial consoles and is swallowed without * garbage by the framebuffer terminal (vedit pattern). */...` |
| `this` | function | `kernel/shell.c:1487` | `* boot into the tiled Wayland desktop: every NK app started after * this (paint, vedit, file, nuklear, doomedit...` |
| `to` | function | `kernel/shell.c:2222` | `* actually trap to (brk/mmap/munmap/mprotect) and says so up front. */ static void shell_cmd_trac...` |
| `tree` | function | `kernel/shell.c:2006` | `* tree (mmap-heavy jobs stay best-effort), legacy blocking `run` ignores  * Ctrl+C (it never poll...` |
| `window` | function | `kernel/shell.c:1283` | `* window (proc_spawn_elf) and waits for all of them. The 100 Hz timer * preempts the BSP across the READY set, so...` |
| `spawn_backup` | function | `kernel/spawn.c:11` | `int spawn_backup(spawn_ctx_t *ctx)` |
| `spawn_copy_argv` | function | `kernel/spawn.c:99` | `char **spawn_copy_argv(int argc, const char **uargv)` |
| `spawn_execute` | function | `kernel/spawn.c:267` | `int spawn_execute(const char *resolved, const char *redirect,                   unsigned char *da...` |
| `spawn_free_argv` | function | `kernel/spawn.c:87` | `void spawn_free_argv(char **kargv, int argc)` |
| `spawn_load_image` | function | `kernel/spawn.c:161` | `unsigned char *spawn_load_image(const char *resolved, unsigned *size_out)` |
| `spawn_restore` | function | `kernel/spawn.c:38` | `void spawn_restore(spawn_ctx_t *ctx)` |
| `spawn_run_exec` | function | `kernel/spawn.c:222` | `static int spawn_run_exec(const char *resolved, const char *redirect,                            ...` |
| `spawn_run_rel` | function | `kernel/spawn.c:196` | `static int spawn_run_rel(const char *resolved, const char *redirect,                          uns...` |
| `spawn_validate_argv` | function | `kernel/spawn.c:143` | `int spawn_validate_argv(int argc, const char **uargv)` |
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
| `Discipline` | function | `kernel/syscalls.c:3208` | `* * Discipline (audit 2026-09, kept as comment, not a deprecation: both * primitives are legitimate): user_range_ok...` |
| `EAGAIN` | function | `kernel/syscalls.c:1154` | `* writer open is EAGAIN (-11, retry);` |
| `EOF` | function | `kernel/syscalls.c:1155` | `* is EOF (0). */ KFILE *o = kfd_get(0);` |
| `FD_STD_COUNT` | macro | `kernel/syscalls.c:1328` | `#define FD_STD_COUNT` |
| `FIONREAD` | function | `kernel/syscalls.c:2437` | `* descriptor answers FIONREAD (bytes readable now), FIONBIO (O_NONBLOCK),  * FIOCLEX/FIONCLEX (FD...` |
| `KFD_MAX` | macro | `kernel/syscalls.c:50` | `#define KFD_MAX` |
| `LINUX_CLOCK_BOOTTIME` | macro | `kernel/syscalls.c:2618` | `#define LINUX_CLOCK_BOOTTIME` |
| `LINUX_CLOCK_MONOTONIC` | macro | `kernel/syscalls.c:2617` | `#define LINUX_CLOCK_MONOTONIC` |
| `LINUX_CLOCK_REALTIME` | macro | `kernel/syscalls.c:2616` | `#define LINUX_CLOCK_REALTIME` |
| `LINUX_CLOSE_RANGE_CLOEXEC` | macro | `kernel/syscalls.c:1323` | `#define LINUX_CLOSE_RANGE_CLOEXEC` |
| `LINUX_CLOSE_RANGE_UNSHARE` | macro | `kernel/syscalls.c:1322` | `#define LINUX_CLOSE_RANGE_UNSHARE` |
| `LINUX_CPUMASK_BYTES` | macro | `kernel/syscalls.c:2551` | `#define LINUX_CPUMASK_BYTES` |
| `LINUX_EFD_CLOEXEC` | macro | `kernel/syscalls.c:1326` | `#define LINUX_EFD_CLOEXEC` |
| `LINUX_EFD_NONBLOCK` | macro | `kernel/syscalls.c:1325` | `#define LINUX_EFD_NONBLOCK` |
| `LINUX_EFD_SEMAPHORE` | macro | `kernel/syscalls.c:1324` | `#define LINUX_EFD_SEMAPHORE` |
| `LINUX_ENOTTY` | macro | `kernel/syscalls.c:2414` | `#define LINUX_ENOTTY` |
| `LINUX_EVENTFD_WORD` | macro | `kernel/syscalls.c:1327` | `#define LINUX_EVENTFD_WORD` |
| `LINUX_FD_CLOEXEC` | macro | `kernel/syscalls.c:1315` | `#define LINUX_FD_CLOEXEC` |
| `LINUX_FIOCLEX` | macro | `kernel/syscalls.c:2412` | `#define LINUX_FIOCLEX` |
| `LINUX_FIONBIO` | macro | `kernel/syscalls.c:2410` | `#define LINUX_FIONBIO` |
| `LINUX_FIONCLEX` | macro | `kernel/syscalls.c:2411` | `#define LINUX_FIONCLEX` |
| `LINUX_FIONREAD` | macro | `kernel/syscalls.c:2409` | `#define LINUX_FIONREAD` |
| `LINUX_F_DUPFD` | macro | `kernel/syscalls.c:1316` | `#define LINUX_F_DUPFD` |
| `LINUX_F_DUPFD_CLOEXEC` | macro | `kernel/syscalls.c:1321` | `#define LINUX_F_DUPFD_CLOEXEC` |
| `LINUX_F_GETFD` | macro | `kernel/syscalls.c:1317` | `#define LINUX_F_GETFD` |
| `LINUX_F_GETFL` | macro | `kernel/syscalls.c:1319` | `#define LINUX_F_GETFL` |
| `LINUX_F_SETFD` | macro | `kernel/syscalls.c:1318` | `#define LINUX_F_SETFD` |
| `LINUX_F_SETFL` | macro | `kernel/syscalls.c:1320` | `#define LINUX_F_SETFL` |
| `LINUX_IOCTL_INT` | macro | `kernel/syscalls.c:2418` | `#define LINUX_IOCTL_INT` |
| `LINUX_MAP_ANONYMOUS` | macro | `kernel/syscalls.c:1773` | `#define LINUX_MAP_ANONYMOUS` |
| `LINUX_MAP_FIXED` | macro | `kernel/syscalls.c:1772` | `#define LINUX_MAP_FIXED` |
| `LINUX_MAP_PRIVATE` | macro | `kernel/syscalls.c:1771` | `#define LINUX_MAP_PRIVATE` |
| `LINUX_MAP_SHARED` | macro | `kernel/syscalls.c:1770` | `#define LINUX_MAP_SHARED` |
| `LINUX_MREMAP_FIXED` | macro | `kernel/syscalls.c:2081` | `#define LINUX_MREMAP_FIXED` |
| `LINUX_MREMAP_MAYMOVE` | macro | `kernel/syscalls.c:2080` | `#define LINUX_MREMAP_MAYMOVE` |
| `LINUX_NS_PER_S` | macro | `kernel/syscalls.c:2622` | `#define LINUX_NS_PER_S` |
| `LINUX_NS_PER_US` | macro | `kernel/syscalls.c:2620` | `#define LINUX_NS_PER_US` |
| `LINUX_O_APPEND` | macro | `kernel/syscalls.c:1311` | `#define LINUX_O_APPEND` |
| `LINUX_O_CLOEXEC` | macro | `kernel/syscalls.c:1314` | `#define LINUX_O_CLOEXEC` |
| `LINUX_O_DIRECT` | macro | `kernel/syscalls.c:1313` | `#define LINUX_O_DIRECT` |
| `LINUX_O_NONBLOCK` | macro | `kernel/syscalls.c:1312` | `#define LINUX_O_NONBLOCK` |
| `LINUX_O_RDONLY` | macro | `kernel/syscalls.c:1308` | `#define LINUX_O_RDONLY` |
| `LINUX_O_RDWR` | macro | `kernel/syscalls.c:1310` | `#define LINUX_O_RDWR` |
| `LINUX_O_WRONLY` | macro | `kernel/syscalls.c:1309` | `#define LINUX_O_WRONLY` |
| `LINUX_RLIMIT_AS` | macro | `kernel/syscalls.c:2545` | `#define LINUX_RLIMIT_AS` |
| `LINUX_RLIMIT_CPU` | macro | `kernel/syscalls.c:2542` | `#define LINUX_RLIMIT_CPU` |
| `LINUX_RLIMIT_NLIMITS` | macro | `kernel/syscalls.c:2546` | `#define LINUX_RLIMIT_NLIMITS` |
| `LINUX_RLIMIT_NOFILE` | macro | `kernel/syscalls.c:2544` | `#define LINUX_RLIMIT_NOFILE` |
| `LINUX_RLIMIT_PAIR` | macro | `kernel/syscalls.c:2548` | `#define LINUX_RLIMIT_PAIR` |
| `LINUX_RLIMIT_STACK` | macro | `kernel/syscalls.c:2543` | `#define LINUX_RLIMIT_STACK` |
| `LINUX_RLIMIT_TICKS_PER_S` | macro | `kernel/syscalls.c:2550` | `#define LINUX_RLIMIT_TICKS_PER_S` |
| `LINUX_RLIM_INFINITY` | macro | `kernel/syscalls.c:2547` | `#define LINUX_RLIM_INFINITY` |
| `LINUX_SLEEP_MAX_S` | macro | `kernel/syscalls.c:2623` | `#define LINUX_SLEEP_MAX_S` |
| `LINUX_SYSCALL_COUNT` | macro | `kernel/syscalls.c:2950` | `#define LINUX_SYSCALL_COUNT` |
| `LINUX_TCGETS` | macro | `kernel/syscalls.c:2407` | `#define LINUX_TCGETS` |
| `LINUX_TCGETS2` | macro | `kernel/syscalls.c:2413` | `#define LINUX_TCGETS2` |
| `LINUX_TERMIOS2_LEN` | macro | `kernel/syscalls.c:2417` | `#define LINUX_TERMIOS2_LEN` |
| `LINUX_TERMIOS_LEN` | macro | `kernel/syscalls.c:2416` | `#define LINUX_TERMIOS_LEN` |
| `LINUX_TIMER_ABSTIME` | macro | `kernel/syscalls.c:2619` | `#define LINUX_TIMER_ABSTIME` |
| `LINUX_TIOCGWINSZ` | macro | `kernel/syscalls.c:2408` | `#define LINUX_TIOCGWINSZ` |
| `LINUX_US_PER_S` | macro | `kernel/syscalls.c:2621` | `#define LINUX_US_PER_S` |
| `LINUX_WINSIZE_LEN` | macro | `kernel/syscalls.c:2415` | `#define LINUX_WINSIZE_LEN` |
| `MINIOS_SYSCALL_BASE` | macro | `kernel/syscalls.c:241` | `#define MINIOS_SYSCALL_BASE` |
| `MINIOS_SYSCALL_COUNT` | macro | `kernel/syscalls.c:242` | `#define MINIOS_SYSCALL_COUNT` |
| `NULL` | function | `kernel/syscalls.c:164` | `* on NULL (already released or never owned). */ void kfd_view_release(proc_t *p)` |
| `PROC_SELF_EXE` | macro | `kernel/syscalls.c:2781` | `#define PROC_SELF_EXE` |
| `SC_EXTRA_COUNT` | macro | `kernel/syscalls.c:3042` | `#define SC_EXTRA_COUNT` |
| `SC_RECORD_LEN` | macro | `kernel/syscalls.c:3103` | `#define SC_RECORD_LEN` |
| `SYSCALL_TRACE` | macro | `kernel/syscalls.c:1098` | `#define SYSCALL_TRACE` |
| `SYS_NOISY_GETC_RAW` | macro | `kernel/syscalls.c:1121` | `#define SYS_NOISY_GETC_RAW` |
| `SYS_NOISY_KBD` | macro | `kernel/syscalls.c:1119` | `#define SYS_NOISY_KBD` |
| `SYS_NOISY_MOUSE` | macro | `kernel/syscalls.c:1120` | `#define SYS_NOISY_MOUSE` |
| `SYS_NOISY_TIME` | macro | `kernel/syscalls.c:1118` | `#define SYS_NOISY_TIME` |
| `TRACE_HINT_NONE` | macro | `kernel/syscalls.c:3064` | `#define TRACE_HINT_NONE` |
| `TRACE_HINT_PATH` | macro | `kernel/syscalls.c:3065` | `#define TRACE_HINT_PATH` |
| `batch_kdispatch` | function | `kernel/syscalls.c:812` | `static long batch_kdispatch(uint32_t opcode)` |
| `boot` | function | `kernel/syscalls.c:477` | `* boot (minfo_sleep_init from sched_init);` |
| `by` | function | `kernel/syscalls.c:223` | `* is indexed by (syscall_number - 200). New syscalls are added by: * 1. Adding a MINIOS_SYS_* constant to...` |
| `clock` | function | `kernel/syscalls.c:2663` | `* clock (the monotonic TSC clock times it, as Linux does: glibc sends * every nanosleep here as a relative...` |
| `clock_gettime` | function | `kernel/syscalls.c:2667` | `* clock_gettime(1) reads. */ static long sys_linux_clock_nanosleep(long a1, long a2, long a3, lon...` |
| `do_open_path` | function | `kernel/syscalls.c:1268` | `static long do_open_path(const char *path, long flags)` |
| `fd_write` | function | `kernel/syscalls.c:1194` | `static long fd_write(long fd, const char *buf, long cnt)` |
| `first` | function | `kernel/syscalls.c:2005` | `* passes under mm_lock: validate every page first (present, user,  * private), then apply, so a h...` |
| `gfx_win_title` | variable | `kernel/syscalls.c:701` | `extern const char *gfx_win_title;` |
| `gfx_zoom_2x` | variable | `kernel/syscalls.c:420` | `extern int gfx_zoom_2x;` |
| `k_syscall_spawn` | function | `kernel/syscalls.c:3480` | `static int k_syscall_spawn(const char *path, const char *redirect,                              i...` |
| `kfd_claim` | function | `kernel/syscalls.c:1359` | `static long kfd_claim(KFILE *f)` |
| `kfd_claim_from` | function | `kernel/syscalls.c:1334` | `static long kfd_claim_from(KFILE *f, long minfd, int cloexec)` |
| `kfd_cloexec_get` | function | `kernel/syscalls.c:1417` | `static int kfd_cloexec_get(long fd)` |
| `kfd_cloexec_set` | function | `kernel/syscalls.c:1427` | `static void kfd_cloexec_set(long fd, int on)` |
| `kfd_get` | function | `kernel/syscalls.c:88` | `KFILE *kfd_get(int fd)` |
| `kfd_poll_revents` | function | `kernel/syscalls.c:1544` | `int kfd_poll_revents(int fd)` |
| `kfd_put` | function | `kernel/syscalls.c:101` | `void kfd_put(KFILE *f)` |
| `kfd_view_cloexec` | function | `kernel/syscalls.c:195` | `void kfd_view_cloexec(void)` |
| `kfd_view_count` | function | `kernel/syscalls.c:113` | `static int kfd_view_count(kfd_view_t *v)` |
| `kfd_view_current` | function | `kernel/syscalls.c:59` | `static kfd_view_t *kfd_view_current(void)` |
| `kfd_view_root` | function | `kernel/syscalls.c:69` | `kfd_view_t *kfd_view_root(void)` |
| `kfile_readable_bytes` | function | `kernel/syscalls.c:2421` | `static int kfile_readable_bytes(KFILE *f)` |
| `kfile_status_flags` | function | `kernel/syscalls.c:1438` | `static long kfile_status_flags(KFILE *f)` |
| `kfile_user_read` | function | `kernel/syscalls.c:1579` | `static long kfile_user_read(KFILE *f, char *buf, long cnt)` |
| `kfile_user_write` | function | `kernel/syscalls.c:1609` | `static long kfile_user_write(KFILE *f, const char *buf, long cnt)` |
| `kiovec` | struct | `kernel/syscalls.c:1096` | `` |
| `ksyscall` | function | `kernel/syscalls.c:3156` | `long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6)` |
| `ksyscall_dispatch` | function | `kernel/syscalls.c:3225` | `static long ksyscall_dispatch(long n, long a1, long a2, long a3, long a4, long a5, long a6)` |
| `linux_timespec_us` | function | `kernel/syscalls.c:2627` | `static long linux_timespec_us(long ts)` |
| `long` | function | `kernel/syscalls.c:2669` | `unsigned long (*now)(void);` |
| `minfo_sleep_init` | function | `kernel/syscalls.c:484` | `void minfo_sleep_init(int tick_ok)` |
| `minfo_tick_wake` | function | `kernel/syscalls.c:489` | `void minfo_tick_wake(void *ctx)` |
| `minios_syscall_entry_t` | struct | `kernel/syscalls.c:236` | `` |
| `mm_ensure_cur` | function | `kernel/syscalls.c:1728` | `static int mm_ensure_cur(unsigned long start, unsigned long end)` |
| `mmap_range_free` | function | `kernel/syscalls.c:1793` | `static int mmap_range_free(unsigned long base, unsigned long len)` |
| `mmap_tag_file` | function | `kernel/syscalls.c:1778` | `static int mmap_tag_file(unsigned long base, int ino, unsigned long off)` |
| `mprotect_pte` | function | `kernel/syscalls.c:1981` | `static volatile unsigned long *mprotect_pte(unsigned long cr3,         unsigned long va)` |
| `node` | function | `kernel/syscalls.c:2126` | `* mapping is one exact live VMA node (what mmap inserts);` |
| `proc_spawn_elf` | function | `kernel/syscalls.c:3471` | `* proc_spawn_elf (the same path mrun uses) and the caller blocks in * do_waitpid, so the parent address space is...` |
| `products` | function | `kernel/syscalls.c:3212` | `* products (writev cnt*sizeof, poll a2*8, spawn (argc+1)*sizeof) are  * pre-bounded against (END-...` |
| `readlink` | function | `kernel/syscalls.c:3362` | `* readlink (89). */ return readlink_path((const char *)a2, (char *)a3, a4);` |
| `readlink_path` | function | `kernel/syscalls.c:2786` | `static long readlink_path(const char *path, char *buf, long bufsz)` |
| `sb16_audio_device` | function | `kernel/syscalls.c:667` | `static device_t *sb16_audio_device(void)` |
| `sc_extra_name` | struct | `kernel/syscalls.c:3028` | `` |
| `sc_hex` | function | `kernel/syscalls.c:3128` | `static void sc_hex(unsigned long v)` |
| `sc_log` | struct | `kernel/syscalls.c:3105` | `` |
| `sc_record` | struct | `kernel/syscalls.c:3104` | `` |
| `sc_record` | function | `kernel/syscalls.c:3108` | `static void sc_record(long n, long a1, long a2, long a3, long ret)` |
| `sc_record_dump` | function | `kernel/syscalls.c:3138` | `void sc_record_dump(int pid)` |
| `split` | function | `kernel/syscalls.c:1931` | `* hold a split (the mapping is restored untouched). */ static long sys_linux_munmap(long a1, long...` |
| `sys_linux_accept` | function | `kernel/syscalls.c:2521` | `static long sys_linux_accept(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_access` | function | `kernel/syscalls.c:2477` | `static long sys_linux_access(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_arch_prctl` | function | `kernel/syscalls.c:2877` | `static long sys_linux_arch_prctl(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_bind` | function | `kernel/syscalls.c:2510` | `static long sys_linux_bind(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_brk` | function | `kernel/syscalls.c:1737` | `static long sys_linux_brk(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_close` | function | `kernel/syscalls.c:1687` | `static long sys_linux_close(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_close_range` | function | `kernel/syscalls.c:1499` | `static long sys_linux_close_range(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_connect` | function | `kernel/syscalls.c:2504` | `static long sys_linux_connect(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_dup` | function | `kernel/syscalls.c:1638` | `static long sys_linux_dup(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_dup2` | function | `kernel/syscalls.c:1653` | `static long sys_linux_dup2(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_dup3` | function | `kernel/syscalls.c:1489` | `static long sys_linux_dup3(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_eventfd` | function | `kernel/syscalls.c:1536` | `static long sys_linux_eventfd(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_eventfd2` | function | `kernel/syscalls.c:1523` | `static long sys_linux_eventfd2(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_fdatasync` | function | `kernel/syscalls.c:2745` | `static long sys_linux_fdatasync(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_flock` | function | `kernel/syscalls.c:2731` | `static long sys_linux_flock(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_fstat` | function | `kernel/syscalls.c:2831` | `static long sys_linux_fstat(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_fsync` | function | `kernel/syscalls.c:2740` | `static long sys_linux_fsync(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_futex` | function | `kernel/syscalls.c:291` | `static long sys_linux_futex(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_getcwd` | function | `kernel/syscalls.c:2750` | `static long sys_linux_getcwd(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_getpeername` | function | `kernel/syscalls.c:2704` | `static long sys_linux_getpeername(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_getsockname` | function | `kernel/syscalls.c:2698` | `static long sys_linux_getsockname(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_getsockopt` | function | `kernel/syscalls.c:2691` | `static long sys_linux_getsockopt(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_gettimeofday` | function | `kernel/syscalls.c:2854` | `static long sys_linux_gettimeofday(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_listen` | function | `kernel/syscalls.c:2516` | `static long sys_linux_listen(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_lseek` | function | `kernel/syscalls.c:1710` | `static long sys_linux_lseek(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_madvise` | function | `kernel/syscalls.c:2912` | `static long sys_linux_madvise(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_mkdir` | function | `kernel/syscalls.c:2920` | `static long sys_linux_mkdir(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_mmap` | function | `kernel/syscalls.c:1802` | `static long sys_linux_mmap(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_mremap` | function | `kernel/syscalls.c:2131` | `static long sys_linux_mremap(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_nanosleep` | function | `kernel/syscalls.c:2652` | `static long sys_linux_nanosleep(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_open` | function | `kernel/syscalls.c:1301` | `static long sys_linux_open(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_pause` | function | `kernel/syscalls.c:2644` | `static long sys_linux_pause(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_pipe` | function | `kernel/syscalls.c:1411` | `static long sys_linux_pipe(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_pipe2` | function | `kernel/syscalls.c:1383` | `static long sys_linux_pipe2(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_poll` | function | `kernel/syscalls.c:2724` | `static long sys_linux_poll(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_prctl` | function | `kernel/syscalls.c:2808` | `static long sys_linux_prctl(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_prlimit64` | function | `kernel/syscalls.c:2572` | `static long sys_linux_prlimit64(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_read` | function | `kernel/syscalls.c:1138` | `static long sys_linux_read(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_readlink` | function | `kernel/syscalls.c:2802` | `static long sys_linux_readlink(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_recvfrom` | function | `kernel/syscalls.c:2532` | `static long sys_linux_recvfrom(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_rename` | function | `kernel/syscalls.c:2817` | `static long sys_linux_rename(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_sched_getaffinity` | function | `kernel/syscalls.c:2605` | `static long sys_linux_sched_getaffinity(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_sendmmsg` | function | `kernel/syscalls.c:2716` | `static long sys_linux_sendmmsg(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_sendmsg` | function | `kernel/syscalls.c:2710` | `static long sys_linux_sendmsg(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_sendto` | function | `kernel/syscalls.c:2527` | `static long sys_linux_sendto(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_setsockopt` | function | `kernel/syscalls.c:2684` | `static long sys_linux_setsockopt(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_shutdown` | function | `kernel/syscalls.c:2537` | `static long sys_linux_shutdown(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_sigaction` | function | `kernel/syscalls.c:2397` | `static long sys_linux_sigaction(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_sigprocmask` | function | `kernel/syscalls.c:2402` | `static long sys_linux_sigprocmask(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_socket` | function | `kernel/syscalls.c:2499` | `static long sys_linux_socket(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_time` | function | `kernel/syscalls.c:282` | `static long sys_linux_time(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_uname` | function | `kernel/syscalls.c:2889` | `static long sys_linux_uname(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_unlink` | function | `kernel/syscalls.c:2762` | `static long sys_linux_unlink(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_write` | function | `kernel/syscalls.c:1218` | `static long sys_linux_write(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_writev` | function | `kernel/syscalls.c:1225` | `static long sys_linux_writev(long a1, long a2, long a3, long a4, long a5, long a6)` |
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
| `syscall_name` | function | `kernel/syscalls.c:3043` | `const char *syscall_name(long n)` |
| `syscall_trace_enabled` | function | `kernel/syscalls.c:1108` | `long syscall_trace_enabled(void)` |
| `syscall_trace_set` | function | `kernel/syscalls.c:1109` | `void syscall_trace_set(int on)` |
| `syscall_trace_shown` | function | `kernel/syscalls.c:1112` | `unsigned long syscall_trace_shown(void)` |
| `syscall_trace_verbose_enabled` | function | `kernel/syscalls.c:1110` | `long syscall_trace_verbose_enabled(void)` |
| `syscall_trace_verbose_set` | function | `kernel/syscalls.c:1111` | `void syscall_trace_verbose_set(int on)` |
| `trace_hint_print` | function | `kernel/syscalls.c:3084` | `static void trace_hint_print(long n, int kind, const char *path,                              lon...` |
| `trace_is_noisy` | function | `kernel/syscalls.c:3016` | `static int trace_is_noisy(long n)` |
| `unchanged` | function | `kernel/syscalls.c:1127` | `* unchanged (same code, same order of checks). Numbers >= 200 that * overlap real Linux ABIs stay in the switch as...` |
| `untouched` | function | `kernel/syscalls.c:137` | `* child untouched (caller refuses fail-closed). */ int kfd_view_copy(proc_t *child, proc_t *parent)` |
| `user_range_ok` | function | `kernel/syscalls.c:3195` | `int user_range_ok(unsigned long p, unsigned long len)` |
| `view` | function | `kernel/syscalls.c:501` | `* view (same as the `clear` builtin). Anything else is -EINVAL. Each  * out-word is range-checked...` |
| `vma_free_cover` | function | `kernel/syscalls.c:2085` | `static vma_node_t *vma_free_cover(unsigned long base, unsigned long len)` |
| `vma_live_first_overlap` | function | `kernel/syscalls.c:1900` | `static vma_node_t *vma_live_first_overlap(unsigned long base, unsigned long end)` |
| `vma_live_overlap` | function | `kernel/syscalls.c:2104` | `static int vma_live_overlap(unsigned long base, unsigned long len)` |
| `vma_live_remainder` | function | `kernel/syscalls.c:1917` | `static int vma_live_remainder(unsigned long base, unsigned long len,         int file, int ino, u...` |
| `wall_us_now` | function | `kernel/syscalls.c:254` | `unsigned long wall_us_now(void)` |
| `LINUX_ECHILD` | macro | `kernel/syscalls_proc.c:197` | `#define LINUX_ECHILD` |
| `LINUX_EINVAL` | macro | `kernel/syscalls_proc.c:198` | `#define LINUX_EINVAL` |
| `LINUX_ESRCH` | macro | `kernel/syscalls_proc.c:199` | `#define LINUX_ESRCH` |
| `LINUX_SIGKILL` | macro | `kernel/syscalls_proc.c:194` | `#define LINUX_SIGKILL` |
| `LINUX_STATUS_CODE` | macro | `kernel/syscalls_proc.c:196` | `#define LINUX_STATUS_CODE` |
| `LINUX_STATUS_SHIFT` | macro | `kernel/syscalls_proc.c:195` | `#define LINUX_STATUS_SHIFT` |
| `LINUX_WNOHANG` | macro | `kernel/syscalls_proc.c:193` | `#define LINUX_WNOHANG` |
| `groups` | function | `kernel/syscalls_proc.c:213` | `* groups (pid 0 and < -1) are not modelled and wait for any child. */ long sys_linux_wait4(long a...` |
| `kill` | function | `kernel/syscalls_proc.c:192` | `* historic kill (SIGKILL), -N is signal N (a seccomp kill is -SIGSYS). */ #define LINUX_WNOHANG  ...` |
| `sig` | function | `kernel/syscalls_proc.c:245` | `* the target as killed by sig (wait4 reports WTERMSIG);` |
| `state` | function | `kernel/syscalls_proc.c:5` | `* touches only scheduler state (current_pid, procs[], do_* / * seccomp_* / yield) plus the kernel-wide user_range_ok...` |
| `sys_linux_clone` | function | `kernel/syscalls_proc.c:83` | `long sys_linux_clone(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_execve` | function | `kernel/syscalls_proc.c:99` | `long sys_linux_execve(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_exit` | function | `kernel/syscalls_proc.c:184` | `long sys_linux_exit(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_fork` | function | `kernel/syscalls_proc.c:89` | `long sys_linux_fork(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_getpid` | function | `kernel/syscalls_proc.c:75` | `long sys_linux_getpid(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_gettid` | function | `kernel/syscalls_proc.c:259` | `long sys_linux_gettid(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_kill` | function | `kernel/syscalls_proc.c:248` | `long sys_linux_kill(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_vfork` | function | `kernel/syscalls_proc.c:94` | `long sys_linux_vfork(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_yield` | function | `kernel/syscalls_proc.c:66` | `long sys_linux_yield(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_clone` | function | `kernel/syscalls_proc.c:18` | `long sys_minios_clone(long flags, long newsp, long a3, long a4, long a5, long a6)` |
| `sys_minios_nice` | function | `kernel/syscalls_proc.c:53` | `long sys_minios_nice(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_seccomp` | function | `kernel/syscalls_proc.c:37` | `long sys_minios_seccomp(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_thread_spawn` | function | `kernel/syscalls_proc.c:24` | `long sys_minios_thread_spawn(long a1, long a2, long a3, long a4, long a5, long a6)` |
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

Next: [SYMBOLS_p10.md](SYMBOLS_p10.md)
