# Symbols (page 7 of 28)
Previous: [SYMBOLS_p6.md](SYMBOLS_p6.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `SBPF_MISC` | macro | `headers/seccomp_bpf.h:60` | `#define SBPF_MISC` |
| `SBPF_MOD` | macro | `headers/seccomp_bpf.h:75` | `#define SBPF_MOD` |
| `SBPF_MUL` | macro | `headers/seccomp_bpf.h:68` | `#define SBPF_MUL` |
| `SBPF_NEG` | macro | `headers/seccomp_bpf.h:74` | `#define SBPF_NEG` |
| `SBPF_OR` | macro | `headers/seccomp_bpf.h:70` | `#define SBPF_OR` |
| `SBPF_RET` | macro | `headers/seccomp_bpf.h:59` | `#define SBPF_RET` |
| `SBPF_RET_ACTION_FULL` | macro | `headers/seccomp_bpf.h:46` | `#define SBPF_RET_ACTION_FULL` |
| `SBPF_RET_ALLOW` | macro | `headers/seccomp_bpf.h:45` | `#define SBPF_RET_ALLOW` |
| `SBPF_RET_DATA` | macro | `headers/seccomp_bpf.h:47` | `#define SBPF_RET_DATA` |
| `SBPF_RET_ERRNO` | macro | `headers/seccomp_bpf.h:41` | `#define SBPF_RET_ERRNO` |
| `SBPF_RET_KILL_PROCESS` | macro | `headers/seccomp_bpf.h:38` | `#define SBPF_RET_KILL_PROCESS` |
| `SBPF_RET_KILL_THREAD` | macro | `headers/seccomp_bpf.h:39` | `#define SBPF_RET_KILL_THREAD` |
| `SBPF_RET_LOG` | macro | `headers/seccomp_bpf.h:44` | `#define SBPF_RET_LOG` |
| `SBPF_RET_TRACE` | macro | `headers/seccomp_bpf.h:43` | `#define SBPF_RET_TRACE` |
| `SBPF_RET_TRAP` | macro | `headers/seccomp_bpf.h:40` | `#define SBPF_RET_TRAP` |
| `SBPF_RET_USER_NOTIF` | macro | `headers/seccomp_bpf.h:42` | `#define SBPF_RET_USER_NOTIF` |
| `SBPF_RSH` | macro | `headers/seccomp_bpf.h:73` | `#define SBPF_RSH` |
| `SBPF_SHIFT_MAX` | macro | `headers/seccomp_bpf.h:34` | `#define SBPF_SHIFT_MAX` |
| `SBPF_ST` | macro | `headers/seccomp_bpf.h:55` | `#define SBPF_ST` |
| `SBPF_STX` | macro | `headers/seccomp_bpf.h:56` | `#define SBPF_STX` |
| `SBPF_SUB` | macro | `headers/seccomp_bpf.h:67` | `#define SBPF_SUB` |
| `SBPF_TAX` | macro | `headers/seccomp_bpf.h:85` | `#define SBPF_TAX` |
| `SBPF_TXA` | macro | `headers/seccomp_bpf.h:86` | `#define SBPF_TXA` |
| `SBPF_W` | macro | `headers/seccomp_bpf.h:61` | `#define SBPF_W` |
| `SBPF_WORD` | macro | `headers/seccomp_bpf.h:33` | `#define SBPF_WORD` |
| `SBPF_X` | macro | `headers/seccomp_bpf.h:83` | `#define SBPF_X` |
| `SBPF_XOR` | macro | `headers/seccomp_bpf.h:76` | `#define SBPF_XOR` |
| `SECCOMP_BPF_H` | macro | `headers/seccomp_bpf.h:12` | `#define SECCOMP_BPF_H` |
| `sbpf_action_rank` | function | `headers/seccomp_bpf.h:104` | `int sbpf_action_rank(unsigned int action);` |
| `sbpf_check` | function | `headers/seccomp_bpf.h:95` | `int sbpf_check(const sbpf_insn *prog, unsigned len, unsigned short *scratch);` |
| `sbpf_data` | struct | `headers/seccomp_bpf.h:23` | `` |
| `sbpf_insn` | struct | `headers/seccomp_bpf.h:15` | `` |
| `sbpf_run` | function | `headers/seccomp_bpf.h:100` | `unsigned int sbpf_run(const sbpf_insn *prog, unsigned len, const sbpf_data *d);` |
| `SELECT_FD_SETSIZE` | macro | `headers/select_map.h:20` | `#define SELECT_FD_SETSIZE` |
| `SELECT_FD_SET_BYTES` | macro | `headers/select_map.h:21` | `#define SELECT_FD_SET_BYTES` |
| `SELECT_MAP_H` | macro | `headers/select_map.h:2` | `#define SELECT_MAP_H` |
| `SELECT_POLLERR` | macro | `headers/select_map.h:27` | `#define SELECT_POLLERR` |
| `SELECT_POLLHUP` | macro | `headers/select_map.h:28` | `#define SELECT_POLLHUP` |
| `SELECT_POLLIN` | macro | `headers/select_map.h:24` | `#define SELECT_POLLIN` |
| `SELECT_POLLNVAL` | macro | `headers/select_map.h:29` | `#define SELECT_POLLNVAL` |
| `SELECT_POLLOUT` | macro | `headers/select_map.h:26` | `#define SELECT_POLLOUT` |
| `SELECT_POLLPRI` | macro | `headers/select_map.h:25` | `#define SELECT_POLLPRI` |
| `select_fd_isset` | function | `headers/select_map.h:37` | `static inline int select_fd_isset(const unsigned char *set, int fd)` |
| `select_fd_put` | function | `headers/select_map.h:41` | `static inline void select_fd_put(unsigned char *set, int fd)` |
| `select_poll_badfd` | function | `headers/select_map.h:131` | `static inline int select_poll_badfd(const select_pollfd_t *pfd,                                  ...` |
| `select_poll_build` | function | `headers/select_map.h:66` | `static inline unsigned select_poll_build(select_pollfd_t *pfd,                                   ...` |
| `select_poll_count` | function | `headers/select_map.h:46` | `static inline unsigned select_poll_count(const unsigned char *r,                                 ...` |
| `select_poll_result` | function | `headers/select_map.h:95` | `static inline unsigned select_poll_result(unsigned char *rout,                                   ...` |
| `select_pollfd_t` | struct | `headers/select_map.h:31` | `` |
| `CMD_BUF_SZ` | macro | `headers/shell.h:13` | `#define CMD_BUF_SZ` |
| `MAX_ARGS` | macro | `headers/shell.h:14` | `#define MAX_ARGS` |
| `SHELL_H` | macro | `headers/shell.h:2` | `#define SHELL_H` |
| `shell_cmd_sh` | function | `headers/shell.h:39` | `int shell_cmd_sh(int argc, char **argv);` |
| `shell_parse` | function | `headers/shell.h:21` | `int shell_parse(char *line, char **argv, int max_args);` |
| `shell_parse_long` | function | `headers/shell.h:29` | `int shell_parse_long(const char *s, long *out);` |
| `shell_parse_pid` | function | `headers/shell.h:34` | `int shell_parse_pid(const char *s, int min_pid, int *out);` |
| `shell_readline_buf` | function | `headers/shell.h:18` | `void shell_readline_buf(char *buf, int size);` |
| `SIGN_DESC_BYTES` | macro | `headers/sign.h:24` | `#define SIGN_DESC_BYTES` |
| `SIGN_H` | macro | `headers/sign.h:17` | `#define SIGN_H` |
| `SIGN_KEYS` | macro | `headers/sign.h:21` | `#define SIGN_KEYS` |
| `SIGN_KEY_DEV` | macro | `headers/sign.h:19` | `#define SIGN_KEY_DEV` |
| `SIGN_KEY_PROD` | macro | `headers/sign.h:20` | `#define SIGN_KEY_PROD` |
| `SIGN_NOTE_TYPE` | macro | `headers/sign.h:25` | `#define SIGN_NOTE_TYPE` |
| `SIGN_PUB_BYTES` | macro | `headers/sign.h:22` | `#define SIGN_PUB_BYTES` |
| `SIGN_SIG_BYTES` | macro | `headers/sign.h:23` | `#define SIGN_SIG_BYTES` |
| `ed25519_verify` | function | `headers/sign.h:75` | `int ed25519_verify(const unsigned char sig[64], const unsigned char *msg, unsigned long msglen, const unsigned char...` |
| `ed_sha` | struct | `headers/sign.h:61` | `` |
| `ed_sha512_final` | function | `headers/sign.h:71` | `void ed_sha512_final(ed_sha *c, unsigned char out[64]);` |
| `ed_sha512_init` | function | `headers/sign.h:69` | `void ed_sha512_init(ed_sha *c);` |
| `ed_sha512_update` | function | `headers/sign.h:70` | `void ed_sha512_update(ed_sha *c, const unsigned char *data, unsigned long len);` |
| `sign_pubkey` | function | `headers/sign.h:47` | `static inline const unsigned char *sign_pubkey(unsigned id)` |
| `SMP_H` | macro | `headers/smp.h:2` | `#define SMP_H` |
| `lapic_cal_10ms` | variable | `headers/smp.h:38` | `extern unsigned lapic_cal_10ms;` |
| `lapic_cal_valid` | variable | `headers/smp.h:39` | `extern int lapic_cal_valid;` |
| `smp_ap_entry` | function | `headers/smp.h:42` | `void smp_ap_entry(void);` |
| `smp_dbg_ipis` | variable | `headers/smp.h:32` | `extern volatile unsigned smp_dbg_ipis;` |
| `smp_dbg_lvt` | variable | `headers/smp.h:31` | `extern volatile unsigned smp_dbg_lvt;` |
| `smp_dbg_sent` | variable | `headers/smp.h:33` | `extern volatile unsigned smp_dbg_sent;` |
| `smp_dbg_svr` | variable | `headers/smp.h:30` | `extern volatile unsigned smp_dbg_svr;` |
| `smp_init` | function | `headers/smp.h:41` | `void smp_init(void);` |
| `smp_ipi_broadcast` | function | `headers/smp.h:43` | `void smp_ipi_broadcast(int vector);` |
| `smp_lock` | variable | `headers/smp.h:25` | `extern spinlock_t smp_lock;` |
| `smp_nmi_broadcast` | function | `headers/smp.h:44` | `void smp_nmi_broadcast(void);` |
| `SPAWN_H` | macro | `headers/spawn.h:2` | `#define SPAWN_H` |
| `spawn_backup` | function | `headers/spawn.h:28` | `int spawn_backup(spawn_ctx_t *ctx);` |
| `spawn_copy_argv` | function | `headers/spawn.h:39` | `char **spawn_copy_argv(int argc, const char **uargv);` |
| `spawn_ctx_t` | struct | `headers/spawn.h:9` | `` |
| `spawn_execute` | function | `headers/spawn.h:48` | `int spawn_execute(const char *resolved, const char *redirect, unsigned char *data, unsigned data_size, int argc...` |
| `spawn_free_argv` | function | `headers/spawn.h:42` | `void spawn_free_argv(char **kargv, int argc);` |
| `spawn_load_image` | function | `headers/spawn.h:45` | `unsigned char *spawn_load_image(const char *resolved, unsigned *size_out);` |
| `spawn_restore` | function | `headers/spawn.h:31` | `void spawn_restore(spawn_ctx_t *ctx);` |
| `spawn_validate_argv` | function | `headers/spawn.h:34` | `int spawn_validate_argv(int argc, const char **uargv);` |
| `SPINLOCK_H` | macro | `headers/spinlock.h:2` | `#define SPINLOCK_H` |
| `SPINLOCK_INIT` | macro | `headers/spinlock.h:44` | `#define SPINLOCK_INIT` |
| `irqflags_t` | type_alias | `headers/spinlock.h:41` | `typedef unsigned long irqflags_t;` |
| `spin_init` | function | `headers/spinlock.h:46` | `static inline void spin_init(spinlock_t *lock)` |
| `spin_lock` | function | `headers/spinlock.h:58` | `static inline void spin_lock(spinlock_t *lock)` |
| `spin_lock` | function | `headers/spinlock.h:107` | `static inline void spin_lock(spinlock_t *lock)` |
| `spin_lock_irqsave` | function | `headers/spinlock.h:68` | `static inline void spin_lock_irqsave(spinlock_t *lock, irqflags_t *flags)` |
| `spin_restore_irq` | function | `headers/spinlock.h:57` | `static inline void spin_restore_irq(irqflags_t flags)` |
| `spin_restore_irq` | function | `headers/spinlock.h:99` | `static inline void spin_restore_irq(irqflags_t flags)` |
| `spin_save_irq` | function | `headers/spinlock.h:56` | `static inline irqflags_t spin_save_irq(void)` |
| `spin_save_irq` | function | `headers/spinlock.h:92` | `static inline irqflags_t spin_save_irq(void)` |
| `spin_trylock` | function | `headers/spinlock.h:84` | `static inline int spin_trylock(spinlock_t *lock)` |
| `spin_unlock` | function | `headers/spinlock.h:64` | `static inline void spin_unlock(spinlock_t *lock)` |
| `spin_unlock` | function | `headers/spinlock.h:118` | `static inline void spin_unlock(spinlock_t *lock)` |
| `spin_unlock_irqrestore` | function | `headers/spinlock.h:75` | `static inline void spin_unlock_irqrestore(spinlock_t *lock, irqflags_t flags)` |
| `spin_unlock_irqrestore` | function | `headers/spinlock.h:150` | `static inline void spin_unlock_irqrestore(spinlock_t *lock, irqflags_t flags)` |
| `spin_unlock_keep_irq` | function | `headers/spinlock.h:80` | `static inline void spin_unlock_keep_irq(spinlock_t *lock)` |
| `spin_unlock_keep_irq` | function | `headers/spinlock.h:130` | `static inline void spin_unlock_keep_irq(spinlock_t *lock)` |
| `spinlock_t` | struct | `headers/spinlock.h:38` | `` |
| `COND_INIT` | macro | `headers/sync.h:101` | `#define COND_INIT` |
| `MUTEX_INIT` | macro | `headers/sync.h:70` | `#define MUTEX_INIT` |
| `RWLOCK_INIT` | macro | `headers/sync.h:122` | `#define RWLOCK_INIT` |
| `SEM_INIT` | macro | `headers/sync.h:87` | `#define SEM_INIT(n)` |
| `SYNC_H` | macro | `headers/sync.h:2` | `#define SYNC_H` |
| `WAIT_QUEUE_INIT` | macro | `headers/sync.h:48` | `#define WAIT_QUEUE_INIT` |
| `WQ_NONE` | macro | `headers/sync.h:39` | `#define WQ_NONE` |
| `cond_broadcast` | function | `headers/sync.h:106` | `void cond_broadcast(cond_t *c);` |
| `cond_init` | function | `headers/sync.h:103` | `void cond_init(cond_t *c);` |
| `cond_signal` | function | `headers/sync.h:105` | `void cond_signal(cond_t *c);` |
| `cond_t` | struct | `headers/sync.h:97` | `` |
| `cond_wait` | function | `headers/sync.h:104` | `void cond_wait(cond_t *c, mutex_t *m);` |
| `inheritance` | function | `headers/sync.h:56` | `* Priority inheritance (thesis correction 3): a low-priority holder that * blocks a high-priority waiter is boosted...` |
| `mutex_init` | function | `headers/sync.h:72` | `void mutex_init(mutex_t *m);` |
| `mutex_lock` | function | `headers/sync.h:73` | `void mutex_lock(mutex_t *m);` |
| `mutex_note_waiter` | function | `headers/sync.h:76` | `void mutex_note_waiter(mutex_t *m, int waiter);` |
| `mutex_t` | struct | `headers/sync.h:63` | `` |
| `mutex_trylock` | function | `headers/sync.h:75` | `int mutex_trylock(mutex_t *m);` |
| `mutex_unlock` | function | `headers/sync.h:74` | `void mutex_unlock(mutex_t *m);` |
| `now` | function | `headers/sync.h:130` | `* available right now (a reader never takes it while a writer waits). */ int rwlock_read_trylock(rwlock_t *rw);` |
| `pi_get_eff` | function | `headers/sync.h:78` | `int pi_get_eff(int pid);` |
| `pi_set_base` | function | `headers/sync.h:77` | `void pi_set_base(int pid, int prio);` |
| `rwlock_init` | function | `headers/sync.h:124` | `void rwlock_init(rwlock_t *rw);` |
| `rwlock_read_lock` | function | `headers/sync.h:125` | `void rwlock_read_lock(rwlock_t *rw);` |
| `rwlock_read_unlock` | function | `headers/sync.h:126` | `void rwlock_read_unlock(rwlock_t *rw);` |
| `rwlock_t` | struct | `headers/sync.h:114` | `` |
| `rwlock_write_lock` | function | `headers/sync.h:127` | `void rwlock_write_lock(rwlock_t *rw);` |
| `rwlock_write_trylock` | function | `headers/sync.h:132` | `int rwlock_write_trylock(rwlock_t *rw);` |
| `rwlock_write_unlock` | function | `headers/sync.h:128` | `void rwlock_write_unlock(rwlock_t *rw);` |
| `sem_init` | function | `headers/sync.h:89` | `void sem_init(sem_t *s, int value);` |
| `sem_post` | function | `headers/sync.h:91` | `void sem_post(sem_t *s);` |
| `sem_t` | struct | `headers/sync.h:81` | `` |
| `sem_wait` | function | `headers/sync.h:90` | `void sem_wait(sem_t *s);` |
| `sleep_on` | function | `headers/sync.h:51` | `void sleep_on(wait_queue_t *q);` |
| `wait_queue_t` | struct | `headers/sync.h:42` | `` |
| `wake_up` | function | `headers/sync.h:52` | `int wake_up(wait_queue_t *q);` |
| `wake_up_all` | function | `headers/sync.h:53` | `int wake_up_all(wait_queue_t *q);` |
| `wq_init` | function | `headers/sync.h:50` | `void wq_init(wait_queue_t *q);` |
| `SYSCALL_ASM_H` | macro | `headers/syscall_asm.h:2` | `#define SYSCALL_ASM_H` |
| `SYSCALL_CPU_CUR_PID_OFF` | macro | `headers/syscall_asm.h:20` | `#define SYSCALL_CPU_CUR_PID_OFF` |
| `SYSCALL_CPU_SC_N_OFF` | macro | `headers/syscall_asm.h:21` | `#define SYSCALL_CPU_SC_N_OFF` |
| `SYSCALL_CPU_SC_PID_OFF` | macro | `headers/syscall_asm.h:23` | `#define SYSCALL_CPU_SC_PID_OFF` |
| `SYSCALL_CPU_SC_RET_OFF` | macro | `headers/syscall_asm.h:24` | `#define SYSCALL_CPU_SC_RET_OFF` |
| `SYSCALL_CPU_SC_RIP_OFF` | macro | `headers/syscall_asm.h:22` | `#define SYSCALL_CPU_SC_RIP_OFF` |
| `SYSCALL_CPU_SC_TMP_OFF` | macro | `headers/syscall_asm.h:25` | `#define SYSCALL_CPU_SC_TMP_OFF` |
| `SYSCALL_FRAME_WORDS` | macro | `headers/syscall_asm.h:29` | `#define SYSCALL_FRAME_WORDS` |
| `SYSCALL_MAX_PROCS` | macro | `headers/syscall_asm.h:19` | `#define SYSCALL_MAX_PROCS` |
| `SYSCALL_PROC_KSTACK_OFF` | macro | `headers/syscall_asm.h:18` | `#define SYSCALL_PROC_KSTACK_OFF` |
| `SYSCALL_PROC_T_SIZE` | macro | `headers/syscall_asm.h:17` | `#define SYSCALL_PROC_T_SIZE` |
| `SYSCALL_USER_WIN_HI` | macro | `headers/syscall_asm.h:16` | `#define SYSCALL_USER_WIN_HI` |
| `SYSCALL_USER_WIN_LO` | macro | `headers/syscall_asm.h:15` | `#define SYSCALL_USER_WIN_LO` |
| `LINUX_EXIT_STATUS_MASK` | macro | `headers/syscalls_proc.h:30` | `#define LINUX_EXIT_STATUS_MASK` |
| `LINUX_SIGNAL_EXIT_BASE` | macro | `headers/syscalls_proc.h:29` | `#define LINUX_SIGNAL_EXIT_BASE` |
| `LINUX_SIGNAL_MAX` | macro | `headers/syscalls_proc.h:28` | `#define LINUX_SIGNAL_MAX` |
| `SYSCALLS_PROC_H` | macro | `headers/syscalls_proc.h:2` | `#define SYSCALLS_PROC_H` |
| `dispatcher` | function | `headers/syscalls_proc.h:5` | `* dispatcher (kernel/syscalls.c). These handlers touch only scheduler * state (current_pid, procs[], do_* /...` |
| `do_proc_exit` | function | `headers/syscalls_proc.h:34` | `long do_proc_exit(long code);` |
| `linux_signal_fatal` | function | `headers/syscalls_proc.h:31` | `int linux_signal_fatal(long sig);` |
| `sys_linux_clone` | function | `headers/syscalls_proc.h:19` | `long sys_linux_clone(long a1, long a2, long a3, long a4, long a5, long a6);` |
| `sys_linux_execve` | function | `headers/syscalls_proc.h:21` | `long sys_linux_execve(long a1, long a2, long a3, long a4, long a5, long a6);` |
| `sys_linux_exit` | function | `headers/syscalls_proc.h:22` | `long sys_linux_exit(long a1, long a2, long a3, long a4, long a5, long a6);` |
| `sys_linux_fork` | function | `headers/syscalls_proc.h:18` | `long sys_linux_fork(long a1, long a2, long a3, long a4, long a5, long a6);` |
| `sys_linux_getpid` | function | `headers/syscalls_proc.h:16` | `long sys_linux_getpid(long a1, long a2, long a3, long a4, long a5, long a6);` |
| `sys_linux_gettid` | function | `headers/syscalls_proc.h:17` | `long sys_linux_gettid(long a1, long a2, long a3, long a4, long a5, long a6);` |
| `sys_linux_kill` | function | `headers/syscalls_proc.h:24` | `long sys_linux_kill(long a1, long a2, long a3, long a4, long a5, long a6);` |
| `sys_linux_vfork` | function | `headers/syscalls_proc.h:20` | `long sys_linux_vfork(long a1, long a2, long a3, long a4, long a5, long a6);` |
| `sys_linux_wait4` | function | `headers/syscalls_proc.h:23` | `long sys_linux_wait4(long a1, long a2, long a3, long a4, long a5, long a6);` |
| `sys_linux_yield` | function | `headers/syscalls_proc.h:15` | `long sys_linux_yield(long a1, long a2, long a3, long a4, long a5, long a6);` |
| `sys_minios_clone` | function | `headers/syscalls_proc.h:13` | `long sys_minios_clone(long flags, long newsp, long a3, long a4, long a5, long a6);` |
| `sys_minios_nice` | function | `headers/syscalls_proc.h:12` | `long sys_minios_nice(long a1, long a2, long a3, long a4, long a5, long a6);` |
| `sys_minios_thread_spawn` | function | `headers/syscalls_proc.h:14` | `long sys_minios_thread_spawn(long a1, long a2, long a3, long a4, long a5, long a6);` |
| `TICK_CONFIG_DEFAULT` | macro | `headers/tick.h:37` | `#define TICK_CONFIG_DEFAULT` |
| `TICK_H` | macro | `headers/tick.h:19` | `#define TICK_H` |
| `TICK_MAX_AUDIO_LISTENERS` | macro | `headers/tick.h:29` | `#define TICK_MAX_AUDIO_LISTENERS` |
| `TICK_MAX_DESKTOP_LISTENERS` | macro | `headers/tick.h:31` | `#define TICK_MAX_DESKTOP_LISTENERS` |
| `TICK_MAX_USB_LISTENERS` | macro | `headers/tick.h:34` | `#define TICK_MAX_USB_LISTENERS` |
| `tick_audio_count` | function | `headers/tick.h:81` | `int tick_audio_count(void);` |
| `tick_config_t` | struct | `headers/tick.h:22` | `` |
| `tick_desktop_count` | function | `headers/tick.h:84` | `int tick_desktop_count(void);` |
| `tick_desktop_due` | function | `headers/tick.h:92` | `int tick_desktop_due(unsigned long long ticks, unsigned interval);` |
| `tick_register_audio` | function | `headers/tick.h:54` | `int tick_register_audio(tick_fn_t fn, void *ctx);` |
| `tick_register_desktop` | function | `headers/tick.h:61` | `int tick_register_desktop(tick_fn_t fn, void *ctx);` |
| `tick_register_usb` | function | `headers/tick.h:69` | `int tick_register_usb(tick_fn_t fn, void *ctx);` |
| `tick_reset` | function | `headers/tick.h:47` | `void tick_reset(void);` |
| `tick_run_audio` | function | `headers/tick.h:75` | `void tick_run_audio(void);` |
| `tick_run_desktop` | function | `headers/tick.h:78` | `void tick_run_desktop(void);` |
| `tick_run_usb` | function | `headers/tick.h:72` | `void tick_run_usb(void);` |
| `TLB_H` | macro | `headers/tlb.h:10` | `#define TLB_H` |
| `TLB_RELEASE_BATCH` | macro | `headers/tlb.h:13` | `#define TLB_RELEASE_BATCH` |
| `space` | function | `headers/tlb.h:4` | `* while that CPU keeps running the same address space (CLONE_VM threads on * an AP). Callers clear the PTEs, flush...` |
| `tlb_nmi_entry` | function | `headers/tlb.h:26` | `void tlb_nmi_entry(void);` |
| `tlb_shoot_acks` | variable | `headers/tlb.h:27` | `extern volatile unsigned int tlb_shoot_acks;` |
| `tlb_shootdown_count` | function | `headers/tlb.h:22` | `unsigned long tlb_shootdown_count(void);` |
| `tlb_shootdown_timeouts` | function | `headers/tlb.h:23` | `unsigned long tlb_shootdown_timeouts(void);` |
| `TLS_ALERT_LEVEL_FATAL` | macro | `headers/tls.h:47` | `#define TLS_ALERT_LEVEL_FATAL` |
| `TLS_ALERT_LEVEL_WARNING` | macro | `headers/tls.h:46` | `#define TLS_ALERT_LEVEL_WARNING` |
| `TLS_BN_384_WORDS` | macro | `headers/tls.h:63` | `#define TLS_BN_384_WORDS` |
| `TLS_BN_4096_WORDS` | macro | `headers/tls.h:62` | `#define TLS_BN_4096_WORDS` |
| `TLS_CERT_MAX` | macro | `headers/tls.h:58` | `#define TLS_CERT_MAX` |
| `TLS_CHAIN_MAX` | macro | `headers/tls.h:57` | `#define TLS_CHAIN_MAX` |
| `TLS_CSUITE_ECDHE_ECDSA_AES128GCM` | macro | `headers/tls.h:29` | `#define TLS_CSUITE_ECDHE_ECDSA_AES128GCM` |
| `TLS_CSUITE_ECDHE_RSA_AES128GCM` | macro | `headers/tls.h:28` | `#define TLS_CSUITE_ECDHE_RSA_AES128GCM` |
| `TLS_CT_ALERT` | macro | `headers/tls.h:8` | `#define TLS_CT_ALERT` |
| `TLS_CT_APPDATA` | macro | `headers/tls.h:10` | `#define TLS_CT_APPDATA` |
| `TLS_CT_CCS` | macro | `headers/tls.h:7` | `#define TLS_CT_CCS` |
| `TLS_CT_HANDSHAKE` | macro | `headers/tls.h:9` | `#define TLS_CT_HANDSHAKE` |
| `TLS_EXT_EC_POINT_FORMATS` | macro | `headers/tls.h:42` | `#define TLS_EXT_EC_POINT_FORMATS` |
| `TLS_EXT_SERVER_NAME` | macro | `headers/tls.h:40` | `#define TLS_EXT_SERVER_NAME` |
| `TLS_EXT_SIGNATURE_ALGS` | macro | `headers/tls.h:43` | `#define TLS_EXT_SIGNATURE_ALGS` |
| `TLS_EXT_SUPPORTED_GROUPS` | macro | `headers/tls.h:41` | `#define TLS_EXT_SUPPORTED_GROUPS` |
| `TLS_GROUP_SECP256R1` | macro | `headers/tls.h:37` | `#define TLS_GROUP_SECP256R1` |
| `TLS_H` | macro | `headers/tls.h:2` | `#define TLS_H` |
| `TLS_HOST_MAX` | macro | `headers/tls.h:54` | `#define TLS_HOST_MAX` |
| `TLS_HS_CERTIFICATE` | macro | `headers/tls.h:21` | `#define TLS_HS_CERTIFICATE` |
| `TLS_HS_CLIENT_HELLO` | macro | `headers/tls.h:19` | `#define TLS_HS_CLIENT_HELLO` |
| `TLS_HS_CLIENT_KEY_EXCHANGE` | macro | `headers/tls.h:24` | `#define TLS_HS_CLIENT_KEY_EXCHANGE` |
| `TLS_HS_FINISHED` | macro | `headers/tls.h:25` | `#define TLS_HS_FINISHED` |
| `TLS_HS_SERVER_HELLO` | macro | `headers/tls.h:20` | `#define TLS_HS_SERVER_HELLO` |
| `TLS_HS_SERVER_HELLO_DONE` | macro | `headers/tls.h:23` | `#define TLS_HS_SERVER_HELLO_DONE` |
| `TLS_HS_SERVER_KEY_EXCHANGE` | macro | `headers/tls.h:22` | `#define TLS_HS_SERVER_KEY_EXCHANGE` |
| `TLS_HS_TIMEOUT_MS` | macro | `headers/tls.h:50` | `#define TLS_HS_TIMEOUT_MS` |
| `TLS_MSG_MAX` | macro | `headers/tls.h:13` | `#define TLS_MSG_MAX` |
| `TLS_PLAIN_MAX` | macro | `headers/tls.h:14` | `#define TLS_PLAIN_MAX` |
| `TLS_READ_TIMEOUT_MS` | macro | `headers/tls.h:51` | `#define TLS_READ_TIMEOUT_MS` |
| `TLS_REC_HEADER` | macro | `headers/tls.h:11` | `#define TLS_REC_HEADER` |
| `TLS_REC_MAX` | macro | `headers/tls.h:12` | `#define TLS_REC_MAX` |
| `TLS_ROOT_COUNT` | macro | `headers/tls.h:68` | `#define TLS_ROOT_COUNT` |
| `TLS_SIG_ECDSA_P256_SHA256` | macro | `headers/tls.h:33` | `#define TLS_SIG_ECDSA_P256_SHA256` |
| `TLS_SIG_ECDSA_P384_SHA384` | macro | `headers/tls.h:34` | `#define TLS_SIG_ECDSA_P384_SHA384` |
| `TLS_SIG_RSA_PKCS1_SHA256` | macro | `headers/tls.h:32` | `#define TLS_SIG_RSA_PKCS1_SHA256` |
| `TLS_VERSION_TLS10` | macro | `headers/tls.h:16` | `#define TLS_VERSION_TLS10` |
| `TLS_VERSION_TLS12` | macro | `headers/tls.h:15` | `#define TLS_VERSION_TLS12` |
| `aes128_encrypt_block` | function | `headers/tls.h:184` | `void aes128_encrypt_block(const unsigned char key[16], const unsigned char in[16], unsigned char out[16]);` |
| `aes128_gcm_open` | function | `headers/tls.h:197` | `int aes128_gcm_open(const unsigned char key[16], const unsigned char salt[4], unsigned long long seq, const unsigned...` |
| `aes128_gcm_open_core` | function | `headers/tls.h:213` | `int aes128_gcm_open_core(const unsigned char key[16], const unsigned char nonce[12], const unsigned char *aad...` |
| `aes128_gcm_seal` | function | `headers/tls.h:189` | `int aes128_gcm_seal(const unsigned char key[16], const unsigned char salt[4], unsigned long long seq, const unsigned...` |
| `aes128_gcm_seal_core` | function | `headers/tls.h:208` | `int aes128_gcm_seal_core(const unsigned char key[16], const unsigned char nonce[12], const unsigned char *aad...` |
| `ecdsa_verify` | function | `headers/tls.h:243` | `int ecdsa_verify(int curve, const unsigned char pub_x[], const unsigned char pub_y[], const unsigned char digest[]...` |
| `hmac_sha256` | function | `headers/tls.h:174` | `void hmac_sha256(const unsigned char *key, unsigned klen, const unsigned char *data, unsigned dlen, unsigned char...` |
| `now` | function | `headers/tls.h:267` | `* window against now (days since epoch). Returns 0 on success. */ int tls_x509_verify_chain(const unsigned char...` |
| `p256_ecdh` | function | `headers/tls.h:231` | `int p256_ecdh(const unsigned char priv[32], const unsigned char peer_x[32], const unsigned char peer_y[32], unsigned...` |
| `p256_point_valid` | function | `headers/tls.h:236` | `int p256_point_valid(const unsigned char x[32], const unsigned char y[32]);` |
| `p256_pub` | function | `headers/tls.h:237` | `int p256_pub(const unsigned char priv[32], unsigned char x[32], unsigned char y[32]);` |
| `p256_scalar_mult` | function | `headers/tls.h:222` | `int p256_scalar_mult(const unsigned char scalar[32], const unsigned char qx[32], const unsigned char qy[32]...` |
| `p256_scalar_valid` | function | `headers/tls.h:239` | `int p256_scalar_valid(const unsigned char scalar[32]);` |
| `p384_scalar_mult` | function | `headers/tls.h:225` | `int p384_scalar_mult(const unsigned char scalar[48], const unsigned char qx[48], const unsigned char qy[48]...` |
| `rsa_pkcs1_verify_sha256` | function | `headers/tls.h:249` | `int rsa_pkcs1_verify_sha256(const unsigned char *n, unsigned n_len, const unsigned char *e, unsigned e_len, const...` |
| `rsa_pkcs1_verify_sha384` | function | `headers/tls.h:253` | `int rsa_pkcs1_verify_sha384(const unsigned char *n, unsigned n_len, const unsigned char *e, unsigned e_len, const...` |
| `sha256` | function | `headers/tls.h:171` | `void sha256(const unsigned char *data, unsigned len, unsigned char out[32]);` |
| `sha256_ctx` | struct | `headers/tls.h:79` | `` |
| `sha256_final` | function | `headers/tls.h:170` | `void sha256_final(struct sha256_ctx *c, unsigned char out[32]);` |
| `sha256_init` | function | `headers/tls.h:168` | `void sha256_init(struct sha256_ctx *c);` |
| `sha256_update` | function | `headers/tls.h:169` | `void sha256_update(struct sha256_ctx *c, const unsigned char *data, unsigned len);` |
| `sha384` | function | `headers/tls.h:172` | `void sha384(const unsigned char *data, unsigned len, unsigned char out[48]);` |
| `tls_free_fd` | function | `headers/tls.h:293` | `static inline void tls_free_fd(int fd)` |
| `tls_handshake` | function | `headers/tls.h:277` | `int tls_handshake(int fd, const char *host);` |
| `tls_prf` | function | `headers/tls.h:179` | `void tls_prf(const unsigned char *secret, unsigned secret_len, const char *label, const unsigned char *seed...` |
| `tls_pubkey` | struct | `headers/tls.h:85` | `` |
| `tls_recv` | function | `headers/tls.h:284` | `int tls_recv(int fd, char *buf, int len);` |
| `tls_root` | struct | `headers/tls.h:70` | `` |
| `tls_roots` | variable | `headers/tls.h:75` | `extern const struct tls_root tls_roots[TLS_ROOT_COUNT];` |
| `tls_send` | function | `headers/tls.h:280` | `int tls_send(int fd, const char *buf, int len);` |
| `tls_session` | struct | `headers/tls.h:95` | `` |
| `tls_sys_handshake` | function | `headers/tls.h:297` | `long tls_sys_handshake(long fd, long host);` |
| `tls_sys_recv` | function | `headers/tls.h:299` | `long tls_sys_recv(long fd, long buf, long len);` |
| `tls_sys_send` | function | `headers/tls.h:298` | `long tls_sys_send(long fd, long buf, long len);` |
| `tls_x509_parse_pubkey` | function | `headers/tls.h:261` | `int tls_x509_parse_pubkey(const unsigned char *der, unsigned len, struct tls_pubkey *pk);` |
| `TLS_CLOSE` | macro | `headers/tls_port.h:38` | `#define TLS_CLOSE` |
| `TLS_CLOSE` | macro | `headers/tls_port.h:89` | `#define TLS_CLOSE` |
| `TLS_CLOSE` | macro | `headers/tls_port.h:114` | `#define TLS_CLOSE` |
| `TLS_FD_MAX` | macro | `headers/tls_port.h:18` | `#define TLS_FD_MAX` |
| `TLS_FD_MAX` | macro | `headers/tls_port.h:71` | `#define TLS_FD_MAX` |
| `TLS_FD_MAX` | macro | `headers/tls_port.h:115` | `#define TLS_FD_MAX` |
| `TLS_FREE` | macro | `headers/tls_port.h:22` | `#define TLS_FREE(p)` |
| `TLS_FREE` | macro | `headers/tls_port.h:75` | `#define TLS_FREE(p)` |
| `TLS_FREE` | macro | `headers/tls_port.h:105` | `#define TLS_FREE(p)` |
| `TLS_MALLOC` | macro | `headers/tls_port.h:21` | `#define TLS_MALLOC(n)` |
| `TLS_MALLOC` | macro | `headers/tls_port.h:74` | `#define TLS_MALLOC(n)` |
| `TLS_MALLOC` | macro | `headers/tls_port.h:104` | `#define TLS_MALLOC(n)` |
| `TLS_MEMCMP` | macro | `headers/tls_port.h:25` | `#define TLS_MEMCMP` |
| `TLS_MEMCMP` | macro | `headers/tls_port.h:78` | `#define TLS_MEMCMP` |
| `TLS_MEMCMP` | macro | `headers/tls_port.h:108` | `#define TLS_MEMCMP` |
| `TLS_MEMCPY` | macro | `headers/tls_port.h:23` | `#define TLS_MEMCPY` |
| `TLS_MEMCPY` | macro | `headers/tls_port.h:76` | `#define TLS_MEMCPY` |
| `TLS_MEMCPY` | macro | `headers/tls_port.h:106` | `#define TLS_MEMCPY` |
| `TLS_MEMSET` | macro | `headers/tls_port.h:24` | `#define TLS_MEMSET` |
| `TLS_MEMSET` | macro | `headers/tls_port.h:77` | `#define TLS_MEMSET` |
| `TLS_MEMSET` | macro | `headers/tls_port.h:107` | `#define TLS_MEMSET` |
| `TLS_PORT_H` | macro | `headers/tls_port.h:2` | `#define TLS_PORT_H` |
| `TLS_PRINTF` | macro | `headers/tls_port.h:20` | `#define TLS_PRINTF` |
| `TLS_PRINTF` | macro | `headers/tls_port.h:73` | `#define TLS_PRINTF` |
| `TLS_PRINTF` | macro | `headers/tls_port.h:103` | `#define TLS_PRINTF` |
| `TLS_RECV` | macro | `headers/tls_port.h:36` | `#define TLS_RECV` |
| `TLS_RECV` | macro | `headers/tls_port.h:87` | `#define TLS_RECV` |
| `TLS_RECV` | macro | `headers/tls_port.h:112` | `#define TLS_RECV` |
| `TLS_RECV_TIMEOUT` | macro | `headers/tls_port.h:37` | `#define TLS_RECV_TIMEOUT` |
| `TLS_RECV_TIMEOUT` | macro | `headers/tls_port.h:88` | `#define TLS_RECV_TIMEOUT` |
| `TLS_RECV_TIMEOUT` | macro | `headers/tls_port.h:113` | `#define TLS_RECV_TIMEOUT` |
| `TLS_SEND` | macro | `headers/tls_port.h:35` | `#define TLS_SEND` |
| `TLS_SEND` | macro | `headers/tls_port.h:86` | `#define TLS_SEND` |
| `TLS_SEND` | macro | `headers/tls_port.h:111` | `#define TLS_SEND` |
| `TLS_STRLEN` | macro | `headers/tls_port.h:26` | `#define TLS_STRLEN` |
| `TLS_STRLEN` | macro | `headers/tls_port.h:79` | `#define TLS_STRLEN` |
| `TLS_STRLEN` | macro | `headers/tls_port.h:109` | `#define TLS_STRLEN` |
| `gettimeofday` | function | `headers/tls_port.h:64` | `* gettimeofday(96) and entropy from /dev/urandom with a time/pid * fallback. Session slots are indexed by raw OS fd...` |
| `sockets` | function | `headers/tls_port.h:62` | `* sockets (glibc maps socket/connect/send/recv/poll onto the MiniOS * Linux ABI numbers the kernel implements);` |
| `syscall` | function | `headers/tls_port.h:95` | `* the MiniOS DNS syscall (200, invoked sig-0-safe). 0 on success. */ int tls_u_resolve(const char *host, unsigned...` |
| `these` | function | `headers/tls_port.h:29` | `* of these (tls_test.c). */ extern int tls_test_send(int fd, const char *buf, int len);` |
| `tls_now_days` | function | `headers/tls_port.h:40` | `static inline long tls_now_days(void)` |
| `tls_random` | function | `headers/tls_port.h:44` | `static inline void tls_random(unsigned char *out, unsigned len)` |
| `tls_test_close` | function | `headers/tls_port.h:33` | `extern void tls_test_close(int fd);` |
| `tls_test_recv` | function | `headers/tls_port.h:31` | `extern int tls_test_recv(int fd, char *buf, int len);` |
| `tls_test_recv_timeout` | function | `headers/tls_port.h:32` | `extern int tls_test_recv_timeout(int fd, char *buf, int len, unsigned long ms);` |
| `tls_u_close` | function | `headers/tls_port.h:84` | `void tls_u_close(int fd);` |
| `tls_u_recv` | function | `headers/tls_port.h:82` | `int tls_u_recv(int fd, char *buf, int len);` |
| `tls_u_recv_timeout` | function | `headers/tls_port.h:83` | `int tls_u_recv_timeout(int fd, char *buf, int len, unsigned long ms);` |
| `COL_BG` | macro | `headers/vga_fb.h:83` | `#define COL_BG` |
| `COL_BLACK` | macro | `headers/vga_fb.h:82` | `#define COL_BLACK` |
| `COL_BORDER` | macro | `headers/vga_fb.h:91` | `#define COL_BORDER` |
| `COL_HIGHLIGHT` | macro | `headers/vga_fb.h:94` | `#define COL_HIGHLIGHT` |
| `COL_SCROLLBAR` | macro | `headers/vga_fb.h:95` | `#define COL_SCROLLBAR` |
| `COL_SCROLL_THUMB` | macro | `headers/vga_fb.h:96` | `#define COL_SCROLL_THUMB` |
| `COL_SHADOW` | macro | `headers/vga_fb.h:93` | `#define COL_SHADOW` |
| `COL_TASKBAR` | macro | `headers/vga_fb.h:84` | `#define COL_TASKBAR` |
| `COL_TASKBAR_TXT` | macro | `headers/vga_fb.h:85` | `#define COL_TASKBAR_TXT` |
| `COL_TERMINAL` | macro | `headers/vga_fb.h:88` | `#define COL_TERMINAL` |
| `COL_TERM_CUR` | macro | `headers/vga_fb.h:90` | `#define COL_TERM_CUR` |
| `COL_TERM_TXT` | macro | `headers/vga_fb.h:89` | `#define COL_TERM_TXT` |
| `COL_TITLEBAR` | macro | `headers/vga_fb.h:86` | `#define COL_TITLEBAR` |
| `COL_TITLE_TXT` | macro | `headers/vga_fb.h:87` | `#define COL_TITLE_TXT` |
| `COL_WHITE` | macro | `headers/vga_fb.h:92` | `#define COL_WHITE` |
| `DOOM_BACKBUF_ADDR` | macro | `headers/vga_fb.h:48` | `#define DOOM_BACKBUF_ADDR` |
| `DOOM_H` | macro | `headers/vga_fb.h:47` | `#define DOOM_H` |
| `DOOM_W` | macro | `headers/vga_fb.h:46` | `#define DOOM_W` |
| `FB_ADDR` | macro | `headers/vga_fb.h:22` | `#define FB_ADDR` |
| `FONT_H` | macro | `headers/vga_fb.h:108` | `#define FONT_H` |
| `FONT_W` | macro | `headers/vga_fb.h:107` | `#define FONT_W` |
| `GFX_TITLE_DEFAULT` | macro | `headers/vga_fb.h:52` | `#define GFX_TITLE_DEFAULT` |
| `NK_BACKBUF_ADDR` | macro | `headers/vga_fb.h:69` | `#define NK_BACKBUF_ADDR` |
| `NK_H` | macro | `headers/vga_fb.h:68` | `#define NK_H` |
| `NK_RGB_ADDR` | macro | `headers/vga_fb.h:73` | `#define NK_RGB_ADDR` |
| `NK_RGB_BYTES` | macro | `headers/vga_fb.h:74` | `#define NK_RGB_BYTES` |
| `NK_W` | macro | `headers/vga_fb.h:67` | `#define NK_W` |
| `SB_LINE_MAX` | macro | `headers/vga_fb.h:174` | `#define SB_LINE_MAX` |
| `SB_MAX_LINES` | macro | `headers/vga_fb.h:173` | `#define SB_MAX_LINES` |
| `SCROLLBAR_PAD` | macro | `headers/vga_fb.h:143` | `#define SCROLLBAR_PAD` |
| `SCROLLBAR_W` | macro | `headers/vga_fb.h:142` | `#define SCROLLBAR_W` |
| `SYS_DOOM_FRAME` | function | `headers/vga_fb.h:44` | `* and calls SYS_DOOM_FRAME (211) to have the kernel composite it onto the * desktop at its native resolution, so the...` |
| `SYS_NK_FRAME` | function | `headers/vga_fb.h:63` | `* SYS_NK_FRAME (220);` |
| `TASKBAR_BTN_W` | macro | `headers/vga_fb.h:123` | `#define TASKBAR_BTN_W` |
| `TASKBAR_CLOCK_CH` | macro | `headers/vga_fb.h:119` | `#define TASKBAR_CLOCK_CH` |
| `TASKBAR_H` | macro | `headers/vga_fb.h:117` | `#define TASKBAR_H` |
| `TASKBAR_ICON_W` | macro | `headers/vga_fb.h:122` | `#define TASKBAR_ICON_W` |
| `TASKBAR_KBD_CH` | macro | `headers/vga_fb.h:125` | `#define TASKBAR_KBD_CH` |
| `TASKBAR_KBD_W` | macro | `headers/vga_fb.h:126` | `#define TASKBAR_KBD_W` |
| `TASKBAR_PAD` | macro | `headers/vga_fb.h:118` | `#define TASKBAR_PAD` |
| `TASKBAR_THEME_CH` | macro | `headers/vga_fb.h:128` | `#define TASKBAR_THEME_CH` |
| `TASKBAR_THEME_W` | macro | `headers/vga_fb.h:129` | `#define TASKBAR_THEME_W` |
| `TASKBAR_VOL_CH` | macro | `headers/vga_fb.h:120` | `#define TASKBAR_VOL_CH` |
| `TASKBAR_VOL_STEP` | macro | `headers/vga_fb.h:121` | `#define TASKBAR_VOL_STEP` |
| `TERM_MAX_COLS` | macro | `headers/vga_fb.h:113` | `#define TERM_MAX_COLS` |
| `TERM_MAX_ROWS` | macro | `headers/vga_fb.h:114` | `#define TERM_MAX_ROWS` |
| `TILING_BOTTOM` | macro | `headers/vga_fb.h:135` | `#define TILING_BOTTOM` |
| `TILING_BOTTOM_LEFT` | macro | `headers/vga_fb.h:138` | `#define TILING_BOTTOM_LEFT` |
| `TILING_BOTTOM_RIGHT` | macro | `headers/vga_fb.h:139` | `#define TILING_BOTTOM_RIGHT` |
| `TILING_LEFT` | macro | `headers/vga_fb.h:132` | `#define TILING_LEFT` |
| `TILING_RIGHT` | macro | `headers/vga_fb.h:133` | `#define TILING_RIGHT` |
| `TILING_TOP` | macro | `headers/vga_fb.h:134` | `#define TILING_TOP` |
| `TILING_TOP_LEFT` | macro | `headers/vga_fb.h:136` | `#define TILING_TOP_LEFT` |
| `TILING_TOP_RIGHT` | macro | `headers/vga_fb.h:137` | `#define TILING_TOP_RIGHT` |
| `VGA_FB_H` | macro | `headers/vga_fb.h:2` | `#define VGA_FB_H` |
| `WALLPAPER_PATH` | macro | `headers/vga_fb.h:103` | `#define WALLPAPER_PATH` |
| `WALL_PAL_BASE` | macro | `headers/vga_fb.h:104` | `#define WALL_PAL_BASE` |
| `WALL_PAL_SIZE` | macro | `headers/vga_fb.h:105` | `#define WALL_PAL_SIZE` |
| `WM_BTN_CLOSE` | macro | `headers/vga_fb.h:153` | `#define WM_BTN_CLOSE` |
| `WM_BTN_H` | macro | `headers/vga_fb.h:149` | `#define WM_BTN_H` |
| `WM_BTN_MAX` | macro | `headers/vga_fb.h:152` | `#define WM_BTN_MAX` |
| `WM_BTN_MIN` | macro | `headers/vga_fb.h:151` | `#define WM_BTN_MIN` |
| `WM_BTN_PAD` | macro | `headers/vga_fb.h:150` | `#define WM_BTN_PAD` |
| `WM_BTN_W` | macro | `headers/vga_fb.h:148` | `#define WM_BTN_W` |
| `WM_FOCUS_GFX` | macro | `headers/vga_fb.h:229` | `#define WM_FOCUS_GFX` |
| `below` | function | `headers/vga_fb.h:99` | `* file below (800x600 RGB PNG on the ramdisk, produced by * tools/gen_desktop_pngs.py) is decoded once per boot via...` |
| `chrome_blur_counts` | function | `headers/vga_fb.h:272` | `void chrome_blur_counts(int *active, unsigned long *panels);` |
| `dock_bounce_counts` | function | `headers/vga_fb.h:264` | `void dock_bounce_counts(unsigned long *kicks, unsigned long *paints);` |
| `dock_click_count` | function | `headers/vga_fb.h:265` | `void dock_click_count(unsigned long *edges);` |
| `dock_mag_counts` | function | `headers/vga_fb.h:269` | `void dock_mag_counts(int *level, unsigned long *paints);` |
| `dock_pending_active` | function | `headers/vga_fb.h:266` | `int dock_pending_active(void);` |
| `fb_bpp` | variable | `headers/vga_fb.h:26` | `extern int fb_bpp;` |
| `fb_bytes_per_pixel` | function | `headers/vga_fb.h:30` | `int fb_bytes_per_pixel(void);` |
| `fb_height` | variable | `headers/vga_fb.h:24` | `extern int fb_height;` |
| `fb_phys_base` | variable | `headers/vga_fb.h:27` | `extern unsigned long fb_phys_base;` |
| `fb_pitch` | variable | `headers/vga_fb.h:25` | `extern int fb_pitch;` |
| `fb_read_packed` | function | `headers/vga_fb.h:200` | `unsigned long fb_read_packed(int x, int y);` |
| `fb_read_row_packed` | function | `headers/vga_fb.h:225` | `void fb_read_row_packed(int x, int y, unsigned int *dst, int n);` |
| `fb_width` | variable | `headers/vga_fb.h:23` | `extern int fb_width;` |
| `fb_write_packed` | function | `headers/vga_fb.h:201` | `void fb_write_packed(int x, int y, unsigned long rgb);` |
| `fb_write_row_packed` | function | `headers/vga_fb.h:224` | `void fb_write_row_packed(int x, int y, const unsigned int *src, int n);` |
| `fx_burns_completed` | variable | `headers/vga_fb.h:295` | `extern unsigned long fx_burns_completed;` |
| `fx_genies_completed` | variable | `headers/vga_fb.h:296` | `extern unsigned long fx_genies_completed;` |
| `fx_melts_completed` | variable | `headers/vga_fb.h:294` | `extern unsigned long fx_melts_completed;` |
| `gfx_frames_composited` | variable | `headers/vga_fb.h:59` | `extern unsigned long gfx_frames_composited;` |
| `gfx_win_title` | variable | `headers/vga_fb.h:50` | `extern const char *gfx_win_title;` |
| `mouse_state` | variable | `headers/vga_fb.h:167` | `extern mouse_state_t mouse_state;` |
| `mouse_state_t` | struct | `headers/vga_fb.h:159` | `` |
| `nk_win_y` | variable | `headers/vga_fb.h:79` | `extern int nk_win_x, nk_win_y;` |
| `pixels` | function | `headers/vga_fb.h:276` | `* are heap buffers of packed pixels (fb_read_packed order), 0 on OOM or a * degenerate rect. A disabled effect or a...` |
| `term_clear` | function | `headers/vga_fb.h:195` | `void term_clear(void);` |
| `term_rows` | variable | `headers/vga_fb.h:156` | `extern int term_x, term_y, term_cols, term_rows;` |
| `vga_fb_active` | variable | `headers/vga_fb.h:305` | `extern int vga_fb_active;` |
| `vga_fb_blit_nk_rgb_window` | function | `headers/vga_fb.h:76` | `void vga_fb_blit_nk_rgb_window(void);` |
| `vga_fb_blit_nk_window` | function | `headers/vga_fb.h:75` | `void vga_fb_blit_nk_window(void);` |
| `vga_fb_boot_config` | function | `headers/vga_fb.h:40` | `void vga_fb_boot_config(void);` |
| `vga_fb_char` | function | `headers/vga_fb.h:191` | `void vga_fb_char(int col, int row, char c, uint8_t fg, uint8_t bg);` |
| `vga_fb_clear` | function | `headers/vga_fb.h:185` | `void vga_fb_clear(void);` |
| `vga_fb_close_active` | function | `headers/vga_fb.h:226` | `int vga_fb_close_active(void);` |
| `vga_fb_draw_desktop` | function | `headers/vga_fb.h:202` | `void vga_fb_draw_desktop(void);` |
| `vga_fb_focus_event` | function | `headers/vga_fb.h:235` | `const wm_notify_event_t *vga_fb_focus_event(void);` |
| `vga_fb_focus_get` | function | `headers/vga_fb.h:232` | `int vga_fb_focus_get(void);` |
| `vga_fb_focus_id` | function | `headers/vga_fb.h:231` | `int vga_fb_focus_id(int id);` |
| `vga_fb_focus_next` | function | `headers/vga_fb.h:230` | `void vga_fb_focus_next(void);` |
| `vga_fb_focus_report` | function | `headers/vga_fb.h:236` | `void vga_fb_focus_report(int before, int source);` |
| `vga_fb_gfx_map_mouse` | function | `headers/vga_fb.h:222` | `void vga_fb_gfx_map_mouse(int *x, int *y);` |
| `vga_fb_gfx_origin` | function | `headers/vga_fb.h:221` | `void vga_fb_gfx_origin(int *x, int *y);` |
| `vga_fb_gfx_set_fullscreen` | function | `headers/vga_fb.h:218` | `int vga_fb_gfx_set_fullscreen(int on);` |
| `vga_fb_gfx_set_hidden` | function | `headers/vga_fb.h:219` | `int vga_fb_gfx_set_hidden(int hide);` |
| `vga_fb_gfx_view_name` | function | `headers/vga_fb.h:220` | `const char *vga_fb_gfx_view_name(void);` |
| `vga_fb_hide_text_cursor` | function | `headers/vga_fb.h:197` | `void vga_fb_hide_text_cursor(void);` |
| `vga_fb_history_page` | function | `headers/vga_fb.h:184` | `void vga_fb_history_page(int dir);` |
| `vga_fb_init` | function | `headers/vga_fb.h:177` | `void vga_fb_init(void);` |
| `vga_fb_is_fullscreen` | function | `headers/vga_fb.h:210` | `int vga_fb_is_fullscreen(void);` |
| `vga_fb_is_minimized` | function | `headers/vga_fb.h:209` | `int vga_fb_is_minimized(void);` |
| `vga_fb_layout_cycle` | function | `headers/vga_fb.h:249` | `void vga_fb_layout_cycle(void);` |
| `vga_fb_layout_get` | function | `headers/vga_fb.h:250` | `int vga_fb_layout_get(void);` |
| `vga_fb_layout_name` | function | `headers/vga_fb.h:251` | `const char *vga_fb_layout_name(void);` |
| `vga_fb_layout_set` | function | `headers/vga_fb.h:248` | `int vga_fb_layout_set(int mode);` |
| `vga_fb_list_windows` | function | `headers/vga_fb.h:252` | `void vga_fb_list_windows(void);` |
| `vga_fb_mouse_init` | function | `headers/vga_fb.h:261` | `void vga_fb_mouse_init(void);` |
| `vga_fb_mouse_tick` | function | `headers/vga_fb.h:256` | `void vga_fb_mouse_tick(void);` |
| `vga_fb_move_terminal` | function | `headers/vga_fb.h:204` | `void vga_fb_move_terminal(int dx, int dy);` |
| `vga_fb_nterms_get` | function | `headers/vga_fb.h:244` | `int vga_fb_nterms_get(void);` |
| `vga_fb_pixel` | function | `headers/vga_fb.h:186` | `void vga_fb_pixel(int x, int y, uint8_t color);` |
| `vga_fb_pixel_rgb` | function | `headers/vga_fb.h:189` | `void vga_fb_pixel_rgb(int x, int y, uint8_t r, uint8_t g, uint8_t b);` |
| `vga_fb_ps2_owner` | function | `headers/vga_fb.h:243` | `int vga_fb_ps2_owner(int pid);` |
| `vga_fb_putc_term` | function | `headers/vga_fb.h:193` | `void vga_fb_putc_term(char c);` |
| `vga_fb_puts_term` | function | `headers/vga_fb.h:194` | `void vga_fb_puts_term(const char *s);` |
| `vga_fb_read_rgb` | function | `headers/vga_fb.h:34` | `unsigned long vga_fb_read_rgb(int x, int y);` |
| `vga_fb_rect` | function | `headers/vga_fb.h:187` | `void vga_fb_rect(int x, int y, int w, int h, uint8_t color);` |
| `vga_fb_rect_rgb` | function | `headers/vga_fb.h:190` | `void vga_fb_rect_rgb(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b);` |
| `vga_fb_reset_default` | function | `headers/vga_fb.h:207` | `void vga_fb_reset_default(void);` |
| `vga_fb_resize` | function | `headers/vga_fb.h:206` | `void vga_fb_resize(int dcols, int drows);` |
| `vga_fb_set_gfx_mode` | function | `headers/vga_fb.h:303` | `void vga_fb_set_gfx_mode(int on);` |
| `vga_fb_set_gfx_palette` | function | `headers/vga_fb.h:38` | `void vga_fb_set_gfx_palette(const unsigned char *pal);` |
| `vga_fb_snap_window` | function | `headers/vga_fb.h:205` | `void vga_fb_snap_window(int zone);` |
| `vga_fb_str` | function | `headers/vga_fb.h:192` | `void vga_fb_str(int col, int row, const char *s, uint8_t fg, uint8_t bg);` |
| `vga_fb_term_close_focused` | function | `headers/vga_fb.h:246` | `int vga_fb_term_close_focused(void);` |
| `vga_fb_term_feed` | function | `headers/vga_fb.h:183` | `void vga_fb_term_feed(const char *line, int len);` |
| `vga_fb_term_ring_init` | function | `headers/vga_fb.h:182` | `void vga_fb_term_ring_init(void);` |
| `vga_fb_term_split` | function | `headers/vga_fb.h:245` | `int vga_fb_term_split(void);` |
| `vga_fb_text_cursor` | function | `headers/vga_fb.h:196` | `void vga_fb_text_cursor(int col);` |
| `vga_fb_theme_name` | function | `headers/vga_fb.h:237` | `int vga_fb_theme_name(char *dst, int cap);` |
| `vga_fb_tile_all` | function | `headers/vga_fb.h:247` | `void vga_fb_tile_all(void);` |
| `vga_fb_toggle_fullscreen` | function | `headers/vga_fb.h:203` | `void vga_fb_toggle_fullscreen(void);` |
| `vga_fb_toggle_minimize` | function | `headers/vga_fb.h:208` | `void vga_fb_toggle_minimize(void);` |
| `vga_fb_wait_tick` | function | `headers/vga_fb.h:260` | `void vga_fb_wait_tick(void);` |
| `vga_fx_burn_rect` | function | `headers/vga_fb.h:287` | `void vga_fx_burn_rect(int x, int y, int w, int h, const unsigned int *oldb, const unsigned int *newb, int stride);` |
| `vga_fx_enabled` | function | `headers/vga_fb.h:280` | `int vga_fx_enabled(void);` |
| `vga_fx_free` | function | `headers/vga_fb.h:283` | `void vga_fx_free(unsigned int *buf);` |
| `vga_fx_genie_rect` | function | `headers/vga_fb.h:289` | `void vga_fx_genie_rect(int wx, int wy, int ww, int wh, int tx, int ty, const unsigned int *bgb, const unsigned int...` |
| `vga_fx_melt_from_black` | function | `headers/vga_fb.h:286` | `void vga_fx_melt_from_black(int x, int y, int w, int h, const unsigned int *newb);` |
| `vga_fx_melt_rect` | function | `headers/vga_fb.h:284` | `void vga_fx_melt_rect(int x, int y, int w, int h, const unsigned int *oldb, const unsigned int *newb);` |
| `vga_fx_restore_rect` | function | `headers/vga_fb.h:282` | `void vga_fx_restore_rect(int x, int y, int w, int h, const unsigned int *buf);` |
| `vga_fx_snap_rect` | function | `headers/vga_fb.h:281` | `unsigned int *vga_fx_snap_rect(int x, int y, int w, int h);` |
| `wm_clear_close` | function | `headers/vga_fb.h:254` | `void wm_clear_close(void);` |
| `wm_close_pending` | function | `headers/vga_fb.h:253` | `int wm_close_pending(void);` |
| `wm_gfx_mode_active` | function | `headers/vga_fb.h:255` | `int wm_gfx_mode_active(void);` |
| `VGA_FX_COLS_MAX` | macro | `headers/vga_fx.h:27` | `#define VGA_FX_COLS_MAX` |
| `VGA_FX_CONFIG_DEFAULT` | macro | `headers/vga_fx.h:24` | `#define VGA_FX_CONFIG_DEFAULT` |
| `VGA_FX_FRAME_MS` | macro | `headers/vga_fx.h:140` | `#define VGA_FX_FRAME_MS` |
| `VGA_FX_H` | macro | `headers/vga_fx.h:13` | `#define VGA_FX_H` |
| `VGA_FX_HEAT_MAX` | macro | `headers/vga_fx.h:146` | `#define VGA_FX_HEAT_MAX` |
| `VGA_FX_HEAT_STEP` | macro | `headers/vga_fx.h:143` | `#define VGA_FX_HEAT_STEP` |
| `VGA_FX_MOTION_DEFAULT` | macro | `headers/vga_fx.h:173` | `#define VGA_FX_MOTION_DEFAULT` |

Next: [SYMBOLS_p8.md](SYMBOLS_p8.md)
