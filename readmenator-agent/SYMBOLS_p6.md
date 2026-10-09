# Symbols (page 6 of 25)
Previous: [SYMBOLS_p5.md](SYMBOLS_p5.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `qga_poll` | function | `headers/qga.h:49` | `void qga_poll(void);` |
| `RANDMIX_H` | macro | `headers/randmix.h:2` | `#define RANDMIX_H` |
| `source` | function | `headers/randmix.h:11` | `* source (all-zero seed) still walks, because the increment is inside  * the mixer, not in the ca...` |
| `RCU_CB_MAX` | macro | `headers/rcu.h:42` | `#define RCU_CB_MAX` |
| `RCU_ERR_FULL` | macro | `headers/rcu.h:46` | `#define RCU_ERR_FULL` |
| `RCU_ERR_TIMEOUT` | macro | `headers/rcu.h:47` | `#define RCU_ERR_TIMEOUT` |
| `RCU_H` | macro | `headers/rcu.h:2` | `#define RCU_H` |
| `RCU_OK` | macro | `headers/rcu.h:45` | `#define RCU_OK` |
| `RCU_SYNC_SPINS` | macro | `headers/rcu.h:43` | `#define RCU_SYNC_SPINS` |
| `rcu_call` | function | `headers/rcu.h:56` | `long rcu_call(rcu_cb_t fn, void *arg);` |
| `rcu_deref` | function | `headers/rcu.h:54` | `void *rcu_deref(void *volatile *pp);` |
| `rcu_init` | function | `headers/rcu.h:51` | `void rcu_init(void);` |
| `rcu_note_idle` | function | `headers/rcu.h:58` | `void rcu_note_idle(int cpu);` |
| `rcu_note_tick` | function | `headers/rcu.h:57` | `void rcu_note_tick(int cpu);` |
| `rcu_poll` | function | `headers/rcu.h:59` | `void rcu_poll(void);` |
| `rcu_publish` | function | `headers/rcu.h:55` | `void rcu_publish(void *volatile *pp, void *v);` |
| `rcu_read_lock` | function | `headers/rcu.h:52` | `void rcu_read_lock(void);` |
| `rcu_read_unlock` | function | `headers/rcu.h:53` | `void rcu_read_unlock(void);` |
| `rcu_synchronize` | function | `headers/rcu.h:60` | `long rcu_synchronize(void);` |
| `retirement` | function | `headers/rcu.h:30` | `* retirement (the writer keeps ownership) instead of dropping the free. * Callbacks run in tick context with...` |
| `RTC_H` | macro | `headers/rtc.h:2` | `#define RTC_H` |
| `rtc_days_from_civil` | function | `headers/rtc.h:18` | `static inline long rtc_days_from_civil(long y, long m, long d)` |
| `rtc_read_date` | function | `headers/rtc.h:11` | `int rtc_read_date(int *year, int *mon, int *day);` |
| `rtc_read_tod` | function | `headers/rtc.h:4` | `int rtc_read_tod(int *hour, int *min, int *sec);` |
| `rtc_wall_seconds` | function | `headers/rtc.h:33` | `int rtc_wall_seconds(unsigned long *out);` |
| `suite` | function | `headers/rtc.h:15` | `* host suite (tests/test_rtc.c);` |
| `SANITIZE_COPY_IN` | macro | `headers/sanitize.h:49` | `#define SANITIZE_COPY_IN(kbuf, uptr, count, elemsz)` |
| `SANITIZE_H` | macro | `headers/sanitize.h:2` | `#define SANITIZE_H` |
| `SANITIZE_LEN_NEG` | macro | `headers/sanitize.h:32` | `#define SANITIZE_LEN_NEG(var)` |
| `SANITIZE_RANGE` | macro | `headers/sanitize.h:37` | `#define SANITIZE_RANGE(ptr, len)` |
| `SANITIZE_STR` | macro | `headers/sanitize.h:43` | `#define SANITIZE_STR(ptr, maxlen)` |
| `SB16_ARM_PERIOD_MS` | macro | `headers/sb16.h:36` | `#define SB16_ARM_PERIOD_MS` |
| `SB16_H` | macro | `headers/sb16.h:2` | `#define SB16_H` |
| `SB16_PCM_BUF` | macro | `headers/sb16.h:32` | `#define SB16_PCM_BUF` |
| `SB16_PCM_RATE` | macro | `headers/sb16.h:33` | `#define SB16_PCM_RATE` |
| `SB16_RING_CAP` | macro | `headers/sb16.h:35` | `#define SB16_RING_CAP` |
| `SB16_SLOTS` | macro | `headers/sb16.h:34` | `#define SB16_SLOTS` |
| `SB16_STREAMS` | macro | `headers/sb16.h:42` | `#define SB16_STREAMS` |
| `SB16_STREAM_BUF` | macro | `headers/sb16.h:43` | `#define SB16_STREAM_BUF` |
| `sb16_counters` | function | `headers/sb16.h:93` | `void sb16_counters(sb16_counters_t *out);` |
| `sb16_counters_t` | struct | `headers/sb16.h:55` | `` |
| `sb16_init` | function | `headers/sb16.h:65` | `int sb16_init(void);` |
| `sb16_irq` | function | `headers/sb16.h:68` | `void sb16_irq(void);` |
| `sb16_legacy_busy` | function | `headers/sb16.h:91` | `int sb16_legacy_busy(void);` |
| `sb16_mode_active` | function | `headers/sb16.h:86` | `int sb16_mode_active(void);` |
| `sb16_pcm_close` | function | `headers/sb16.h:75` | `void sb16_pcm_close(void);` |
| `sb16_pcm_open` | function | `headers/sb16.h:73` | `void sb16_pcm_open(void);` |
| `sb16_pcm_submit` | function | `headers/sb16.h:74` | `int sb16_pcm_submit(const unsigned char *pcm, unsigned len);` |
| `sb16_poll` | function | `headers/sb16.h:69` | `void sb16_poll(void);` |
| `sb16_present` | function | `headers/sb16.h:66` | `int sb16_present(void);` |
| `sb16_pump` | function | `headers/sb16.h:76` | `void sb16_pump(void);` |
| `sb16_ring_free` | function | `headers/sb16.h:85` | `unsigned sb16_ring_free(void);` |
| `sb16_stream_close` | function | `headers/sb16.h:80` | `void sb16_stream_close(int id);` |
| `sb16_stream_count` | function | `headers/sb16.h:83` | `int sb16_stream_count(void);` |
| `sb16_stream_open` | function | `headers/sb16.h:79` | `int sb16_stream_open(void);` |
| `sb16_stream_submit` | function | `headers/sb16.h:81` | `int sb16_stream_submit(int id, const unsigned char *pcm, unsigned len);` |
| `sb16_stream_t` | struct | `headers/sb16.h:46` | `` |
| `sb16_stream_volume` | function | `headers/sb16.h:82` | `void sb16_stream_volume(int id, unsigned char vol);` |
| `sb16_tone` | function | `headers/sb16.h:67` | `void sb16_tone(unsigned freq);` |
| `BOOT_CPU` | macro | `headers/sched.h:30` | `#define BOOT_CPU` |
| `CLONE_FILES` | macro | `headers/sched.h:198` | `#define CLONE_FILES` |
| `CLONE_VM` | macro | `headers/sched.h:197` | `#define CLONE_VM` |
| `CTX_RBP_OFF` | macro | `headers/sched.h:44` | `#define CTX_RBP_OFF` |
| `CTX_RFLAGS_OFF` | macro | `headers/sched.h:47` | `#define CTX_RFLAGS_OFF` |
| `CTX_RIP_OFF` | macro | `headers/sched.h:45` | `#define CTX_RIP_OFF` |
| `CTX_RSP_OFF` | macro | `headers/sched.h:46` | `#define CTX_RSP_OFF` |
| `DESKTOP_TICK_INTERVAL` | macro | `headers/sched.h:316` | `#define DESKTOP_TICK_INTERVAL` |
| `EXECVE_MAX_ARG` | macro | `headers/sched.h:413` | `#define EXECVE_MAX_ARG` |
| `EXECVE_MAX_ARGS` | macro | `headers/sched.h:412` | `#define EXECVE_MAX_ARGS` |
| `FPU_MXCSR_DEFAULT` | macro | `headers/sched.h:159` | `#define FPU_MXCSR_DEFAULT` |
| `FPU_MXCSR_OFF` | macro | `headers/sched.h:158` | `#define FPU_MXCSR_OFF` |
| `FPU_SAVE_SZ` | macro | `headers/sched.h:157` | `#define FPU_SAVE_SZ` |
| `LINUX_CLONE_CHILD_CLEARTID` | macro | `headers/sched.h:214` | `#define LINUX_CLONE_CHILD_CLEARTID` |
| `LINUX_CLONE_CHILD_SETTID` | macro | `headers/sched.h:217` | `#define LINUX_CLONE_CHILD_SETTID` |
| `LINUX_CLONE_DETACHED` | macro | `headers/sched.h:215` | `#define LINUX_CLONE_DETACHED` |
| `LINUX_CLONE_FILES` | macro | `headers/sched.h:203` | `#define LINUX_CLONE_FILES` |
| `LINUX_CLONE_FORK_OK` | macro | `headers/sched.h:228` | `#define LINUX_CLONE_FORK_OK` |
| `LINUX_CLONE_FS` | macro | `headers/sched.h:202` | `#define LINUX_CLONE_FS` |
| `LINUX_CLONE_IO` | macro | `headers/sched.h:219` | `#define LINUX_CLONE_IO` |
| `LINUX_CLONE_NEWNS` | macro | `headers/sched.h:210` | `#define LINUX_CLONE_NEWNS` |
| `LINUX_CLONE_NEWNS_MASK` | macro | `headers/sched.h:218` | `#define LINUX_CLONE_NEWNS_MASK` |
| `LINUX_CLONE_PARENT` | macro | `headers/sched.h:208` | `#define LINUX_CLONE_PARENT` |
| `LINUX_CLONE_PARENT_SETTID` | macro | `headers/sched.h:213` | `#define LINUX_CLONE_PARENT_SETTID` |
| `LINUX_CLONE_PIDFD` | macro | `headers/sched.h:205` | `#define LINUX_CLONE_PIDFD` |
| `LINUX_CLONE_PTRACE` | macro | `headers/sched.h:206` | `#define LINUX_CLONE_PTRACE` |
| `LINUX_CLONE_SETTLS` | macro | `headers/sched.h:212` | `#define LINUX_CLONE_SETTLS` |
| `LINUX_CLONE_SIGHAND` | macro | `headers/sched.h:204` | `#define LINUX_CLONE_SIGHAND` |
| `LINUX_CLONE_SIGNAL_MASK` | macro | `headers/sched.h:200` | `#define LINUX_CLONE_SIGNAL_MASK` |
| `LINUX_CLONE_SYSVSEM` | macro | `headers/sched.h:211` | `#define LINUX_CLONE_SYSVSEM` |
| `LINUX_CLONE_THREAD` | macro | `headers/sched.h:209` | `#define LINUX_CLONE_THREAD` |
| `LINUX_CLONE_THREAD_OK` | macro | `headers/sched.h:223` | `#define LINUX_CLONE_THREAD_OK` |
| `LINUX_CLONE_UNTRACED` | macro | `headers/sched.h:216` | `#define LINUX_CLONE_UNTRACED` |
| `LINUX_CLONE_VFORK` | macro | `headers/sched.h:207` | `#define LINUX_CLONE_VFORK` |
| `LINUX_CLONE_VM` | macro | `headers/sched.h:201` | `#define LINUX_CLONE_VM` |
| `LINUX_SIGCHLD` | macro | `headers/sched.h:220` | `#define LINUX_SIGCHLD` |
| `MAX_CPUS` | macro | `headers/sched.h:29` | `#define MAX_CPUS` |
| `MAX_PROCS` | macro | `headers/sched.h:25` | `#define MAX_PROCS` |
| `NICE_DEFAULT` | macro | `headers/sched.h:186` | `#define NICE_DEFAULT` |
| `NICE_MAX` | macro | `headers/sched.h:185` | `#define NICE_MAX` |
| `NICE_MIN` | macro | `headers/sched.h:184` | `#define NICE_MIN` |
| `PROC_BLOCKED` | macro | `headers/sched.h:17` | `#define PROC_BLOCKED` |
| `PROC_FPU_OFF` | macro | `headers/sched.h:147` | `#define PROC_FPU_OFF` |
| `PROC_FREE` | macro | `headers/sched.h:14` | `#define PROC_FREE` |
| `PROC_FSBASE_OFF` | macro | `headers/sched.h:155` | `#define PROC_FSBASE_OFF` |
| `PROC_KSTACK_OFF` | macro | `headers/sched.h:142` | `#define PROC_KSTACK_OFF` |
| `PROC_KSTACK_SZ` | macro | `headers/sched.h:26` | `#define PROC_KSTACK_SZ` |
| `PROC_PID_OFF` | macro | `headers/sched.h:154` | `#define PROC_PID_OFF` |
| `PROC_READY` | macro | `headers/sched.h:15` | `#define PROC_READY` |
| `PROC_RUNNING` | macro | `headers/sched.h:16` | `#define PROC_RUNNING` |
| `PROC_SWITCHING` | macro | `headers/sched.h:22` | `#define PROC_SWITCHING` |
| `PROC_T_SIZE` | macro | `headers/sched.h:132` | `#define PROC_T_SIZE` |
| `PROC_ZOMBIE` | macro | `headers/sched.h:18` | `#define PROC_ZOMBIE` |
| `RLIM_AS` | macro | `headers/sched.h:179` | `#define RLIM_AS` |
| `RLIM_CPU` | macro | `headers/sched.h:180` | `#define RLIM_CPU` |
| `RLIM_EXIT_CPU` | macro | `headers/sched.h:182` | `#define RLIM_EXIT_CPU` |
| `RLIM_NOFILE` | macro | `headers/sched.h:181` | `#define RLIM_NOFILE` |
| `RLIM_OP_GET` | macro | `headers/sched.h:178` | `#define RLIM_OP_GET` |
| `RLIM_OP_SET` | macro | `headers/sched.h:177` | `#define RLIM_OP_SET` |
| `SCHED_BASE_QUANTUM` | macro | `headers/sched.h:191` | `#define SCHED_BASE_QUANTUM` |
| `SCHED_H` | macro | `headers/sched.h:2` | `#define SCHED_H` |
| `SCHED_NICE_MULT_CHARGE` | macro | `headers/sched.h:193` | `#define SCHED_NICE_MULT_CHARGE` |
| `SCHED_NICE_MULT_KEY` | macro | `headers/sched.h:192` | `#define SCHED_NICE_MULT_KEY` |
| `SCHED_NICE_OFFSET` | macro | `headers/sched.h:194` | `#define SCHED_NICE_OFFSET` |
| `SECCOMP_BIT` | macro | `headers/sched.h:165` | `#define SECCOMP_BIT(n)` |
| `SECCOMP_MAX` | macro | `headers/sched.h:164` | `#define SECCOMP_MAX` |
| `SECCOMP_MIN` | macro | `headers/sched.h:163` | `#define SECCOMP_MIN` |
| `SECCOMP_OP_ALLOW_ONE` | macro | `headers/sched.h:169` | `#define SECCOMP_OP_ALLOW_ONE` |
| `SECCOMP_OP_DENY_ALL` | macro | `headers/sched.h:170` | `#define SECCOMP_OP_DENY_ALL` |
| `SECCOMP_OP_DENY_ONE` | macro | `headers/sched.h:168` | `#define SECCOMP_OP_DENY_ONE` |
| `TSS_SEL` | macro | `headers/sched.h:369` | `#define TSS_SEL(cpu)` |
| `WAITPID_NONE` | macro | `headers/sched.h:436` | `#define WAITPID_NONE` |
| `__attribute__` | function | `headers/sched.h:372` | `typedef struct __attribute__((packed))` |
| `ap_idle_proc` | variable | `headers/sched.h:356` | `extern proc_t ap_idle_proc[MAX_CPUS];` |
| `aslr_brk_pages` | function | `headers/sched.h:420` | `unsigned long aslr_brk_pages(void);` |
| `aslr_dyn_base` | function | `headers/sched.h:422` | `unsigned long aslr_dyn_base(void);` |
| `aslr_mmap_pages` | function | `headers/sched.h:421` | `unsigned long aslr_mmap_pages(void);` |
| `aslr_stack_bytes` | function | `headers/sched.h:419` | `unsigned long aslr_stack_bytes(void);` |
| `bsp_idtr` | variable | `headers/sched.h:373` | `extern idtr_t bsp_idtr;` |
| `bytes` | function | `headers/sched.h:173` | `* RLIM_AS total user bytes (brk growth + mmap) beyond the load base * RLIM_CPU timer ticks of CPU time, then...` |
| `caller` | function | `headers/sched.h:447` | `* caller (shell mrun) reaps it with do_waitpid. Returns pid or -1. * Programs using mmap/VMA or expecting a shared...` |
| `cpu` | struct | `headers/sched.h:268` | `` |
| `cpu_count` | variable | `headers/sched.h:295` | `extern int cpu_count;` |
| `cpu_idle_ticks` | variable | `headers/sched.h:361` | `extern volatile unsigned long cpu_idle_ticks[MAX_CPUS];` |
| `cpus` | variable | `headers/sched.h:294` | `extern cpu_t cpus[MAX_CPUS];` |
| `ctx_regs_t` | struct | `headers/sched.h:33` | `` |
| `current_pid` | macro | `headers/sched.h:312` | `#define current_pid` |
| `do_clone` | function | `headers/sched.h:408` | `long do_clone(long flags, long newsp);` |
| `do_execve` | function | `headers/sched.h:428` | `long do_execve(char *kpath, int kargc, char **kargv);` |
| `do_exit` | function | `headers/sched.h:407` | `void do_exit(int code);` |
| `do_fork` | function | `headers/sched.h:409` | `long do_fork(void);` |
| `do_kill` | function | `headers/sched.h:437` | `int do_kill(int pid);` |
| `do_thread_spawn` | function | `headers/sched.h:429` | `long do_thread_spawn(unsigned long fn, unsigned long stack, unsigned long arg);` |
| `do_waitpid` | function | `headers/sched.h:431` | `int do_waitpid(int pid);` |
| `do_waitpid_nb` | function | `headers/sched.h:432` | `int do_waitpid_nb(int pid);` |
| `entry` | function | `headers/sched.h:135` | `* private view with one KFILE ref per live entry (0 on OOM), release * drops the view at reap, cloexec closes marked...` |
| `failure` | function | `headers/sched.h:427` | `* failure (negative errno);` |
| `first` | function | `headers/sched.h:232` | `* address first (SYSCALL_FRAME_WORDS in syscall_asm.h). It ends exactly at * the saved top (sc_top_save[pid]);` |
| `gdb_dump_report` | function | `headers/sched.h:381` | `void gdb_dump_report(unsigned long addr, unsigned long len);` |
| `gdb_regs_report` | function | `headers/sched.h:380` | `void gdb_regs_report(int pid);` |
| `group` | function | `headers/sched.h:108` | `* process is its own group (tgid == pid);` |
| `irqstat_report` | function | `headers/sched.h:379` | `void irqstat_report(void);` |
| `isr_cnt_kbd` | variable | `headers/sched.h:382` | `extern volatile unsigned long isr_cnt_kbd;` |
| `isr_cnt_mouse` | variable | `headers/sched.h:383` | `extern volatile unsigned long isr_cnt_mouse;` |
| `isr_cnt_sb16` | variable | `headers/sched.h:384` | `extern volatile unsigned long isr_cnt_sb16;` |
| `kfd_view_cloexec` | function | `headers/sched.h:140` | `void kfd_view_cloexec(void);` |
| `kfd_view_copy` | function | `headers/sched.h:138` | `int kfd_view_copy(proc_t *child, proc_t *parent);` |
| `kfd_view_release` | function | `headers/sched.h:139` | `void kfd_view_release(proc_t *p);` |
| `kfd_view_root` | function | `headers/sched.h:141` | `kfd_view_t *kfd_view_root(void);` |
| `kfd_view_t` | type_alias | `headers/sched.h:11` | `typedef struct kfd_view kfd_view_t;` |
| `kstack_report` | function | `headers/sched.h:377` | `void kstack_report(void);` |
| `limit` | type_alias | `headers/sched.h:372` | `typedef struct __attribute__((packed)) { uint16_t limit;` |
| `proc_count` | variable | `headers/sched.h:334` | `extern int proc_count;` |
| `proc_create` | function | `headers/sched.h:387` | `int proc_create(const char *name, int parent_pid);` |
| `proc_get` | function | `headers/sched.h:388` | `proc_t *proc_get(int pid);` |
| `proc_t` | struct | `headers/sched.h:50` | `` |
| `procs` | variable | `headers/sched.h:333` | `extern proc_t procs[MAX_PROCS];` |
| `pt_clone_user` | function | `headers/sched.h:441` | `uint64_t pt_clone_user(uint64_t parent_cr3);` |
| `pt_free_user` | function | `headers/sched.h:442` | `void pt_free_user(uint64_t cr3);` |
| `resume_iretq` | function | `headers/sched.h:405` | `void resume_iretq(void);` |
| `rlimit_cpu_exceeded` | function | `headers/sched.h:394` | `int rlimit_cpu_exceeded(int pid);` |
| `rlimit_cpu_tick` | function | `headers/sched.h:395` | `void rlimit_cpu_tick(int pid);` |
| `sched_init` | function | `headers/sched.h:376` | `void sched_init(void);` |
| `sched_lock` | variable | `headers/sched.h:337` | `extern spinlock_t sched_lock;` |
| `sched_ready` | variable | `headers/sched.h:338` | `extern volatile int sched_ready;` |
| `sched_set_nice` | function | `headers/sched.h:390` | `int sched_set_nice(int pid, int nice);` |
| `schedtop_report` | function | `headers/sched.h:378` | `void schedtop_report(void);` |
| `schedule` | function | `headers/sched.h:389` | `void schedule(void);` |
| `seccomp_allow_one` | function | `headers/sched.h:392` | `int seccomp_allow_one(int pid, int n);` |
| `seccomp_denied` | function | `headers/sched.h:393` | `int seccomp_denied(int pid, int n);` |
| `seccomp_deny_one` | function | `headers/sched.h:391` | `int seccomp_deny_one(int pid, int n);` |
| `shell_nchildren` | function | `headers/sched.h:435` | `int shell_nchildren(void);` |
| `shell_reap_nb` | function | `headers/sched.h:433` | `int shell_reap_nb(int *pid_out, int *code_out);` |
| `shell_reap_one` | function | `headers/sched.h:434` | `int shell_reap_one(int pid, int *code_out);` |
| `smp_ap_idle_loop` | function | `headers/sched.h:386` | `void smp_ap_idle_loop(void);` |
| `smp_dbg_bad_gs` | variable | `headers/sched.h:364` | `extern volatile unsigned smp_dbg_bad_gs;` |
| `smp_dispatches` | variable | `headers/sched.h:357` | `extern volatile unsigned long smp_dispatches[MAX_CPUS];` |
| `smp_idle_polls` | variable | `headers/sched.h:358` | `extern volatile unsigned long smp_idle_polls[MAX_CPUS];` |
| `switch_save_only` | function | `headers/sched.h:398` | `void switch_save_only(proc_t *prev);` |
| `switch_to` | function | `headers/sched.h:396` | `void switch_to(proc_t *prev, proc_t *next);` |
| `switch_to_notrap` | function | `headers/sched.h:397` | `void switch_to_notrap(proc_t *prev, proc_t *next);` |
| `sys_ticks` | variable | `headers/sched.h:335` | `extern volatile uint64_t sys_ticks;` |
| `syscall_frame_current` | function | `headers/sched.h:245` | `const syscall_frame_t *syscall_frame_current(void);` |
| `syscall_frame_t` | struct | `headers/sched.h:235` | `` |
| `timer_tick` | function | `headers/sched.h:438` | `void timer_tick(void);` |
| `tss_init_ap` | function | `headers/sched.h:385` | `void tss_init_ap(int cpu);` |
| `user_program_active` | variable | `headers/sched.h:336` | `extern volatile int user_program_active;` |
| `yield` | function | `headers/sched.h:406` | `void yield(void);` |
| `CMD_BUF_SZ` | macro | `headers/shell.h:13` | `#define CMD_BUF_SZ` |
| `MAX_ARGS` | macro | `headers/shell.h:14` | `#define MAX_ARGS` |
| `SHELL_H` | macro | `headers/shell.h:2` | `#define SHELL_H` |
| `shell_cmd_sh` | function | `headers/shell.h:39` | `int shell_cmd_sh(int argc, char **argv);` |
| `shell_parse` | function | `headers/shell.h:21` | `int shell_parse(char *line, char **argv, int max_args);` |
| `shell_parse_long` | function | `headers/shell.h:29` | `int shell_parse_long(const char *s, long *out);` |
| `shell_parse_pid` | function | `headers/shell.h:34` | `int shell_parse_pid(const char *s, int min_pid, int *out);` |
| `shell_readline_buf` | function | `headers/shell.h:18` | `void shell_readline_buf(char *buf, int size);` |
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
| `SPAWN_H` | macro | `headers/spawn.h:2` | `#define SPAWN_H` |
| `spawn_backup` | function | `headers/spawn.h:27` | `int spawn_backup(spawn_ctx_t *ctx);` |
| `spawn_copy_argv` | function | `headers/spawn.h:38` | `char **spawn_copy_argv(int argc, const char **uargv);` |
| `spawn_ctx_t` | struct | `headers/spawn.h:9` | `` |
| `spawn_execute` | function | `headers/spawn.h:47` | `int spawn_execute(const char *resolved, const char *redirect, unsigned char *data, unsigned data_size, int argc...` |
| `spawn_free_argv` | function | `headers/spawn.h:41` | `void spawn_free_argv(char **kargv, int argc);` |
| `spawn_load_image` | function | `headers/spawn.h:44` | `unsigned char *spawn_load_image(const char *resolved, unsigned *size_out);` |
| `spawn_restore` | function | `headers/spawn.h:30` | `void spawn_restore(spawn_ctx_t *ctx);` |
| `spawn_validate_argv` | function | `headers/spawn.h:33` | `int spawn_validate_argv(int argc, const char **uargv);` |
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
| `RWLOCK_INIT` | macro | `headers/sync.h:116` | `#define RWLOCK_INIT` |
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
| `pi_get_eff` | function | `headers/sync.h:78` | `int pi_get_eff(int pid);` |
| `pi_set_base` | function | `headers/sync.h:77` | `void pi_set_base(int pid, int prio);` |
| `rwlock_init` | function | `headers/sync.h:118` | `void rwlock_init(rwlock_t *rw);` |
| `rwlock_read_lock` | function | `headers/sync.h:119` | `void rwlock_read_lock(rwlock_t *rw);` |
| `rwlock_read_unlock` | function | `headers/sync.h:120` | `void rwlock_read_unlock(rwlock_t *rw);` |
| `rwlock_t` | struct | `headers/sync.h:109` | `` |
| `rwlock_write_lock` | function | `headers/sync.h:121` | `void rwlock_write_lock(rwlock_t *rw);` |
| `rwlock_write_unlock` | function | `headers/sync.h:122` | `void rwlock_write_unlock(rwlock_t *rw);` |
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
| `SYSCALLS_PROC_H` | macro | `headers/syscalls_proc.h:2` | `#define SYSCALLS_PROC_H` |
| `dispatcher` | function | `headers/syscalls_proc.h:5` | `* dispatcher (kernel/syscalls.c). These handlers touch only scheduler * state (current_pid, procs[], do_* /...` |
| `do_proc_exit` | function | `headers/syscalls_proc.h:26` | `long do_proc_exit(long code);` |
| `sys_linux_execve` | function | `headers/syscalls_proc.h:20` | `long sys_linux_execve(long a1, long a2, long a3, long a4, long a5, long a6);` |
| `sys_linux_exit` | function | `headers/syscalls_proc.h:21` | `long sys_linux_exit(long a1, long a2, long a3, long a4, long a5, long a6);` |
| `sys_linux_fork` | function | `headers/syscalls_proc.h:18` | `long sys_linux_fork(long a1, long a2, long a3, long a4, long a5, long a6);` |
| `sys_linux_getpid` | function | `headers/syscalls_proc.h:16` | `long sys_linux_getpid(long a1, long a2, long a3, long a4, long a5, long a6);` |
| `sys_linux_gettid` | function | `headers/syscalls_proc.h:17` | `long sys_linux_gettid(long a1, long a2, long a3, long a4, long a5, long a6);` |
| `sys_linux_kill` | function | `headers/syscalls_proc.h:23` | `long sys_linux_kill(long a1, long a2, long a3, long a4, long a5, long a6);` |
| `sys_linux_vfork` | function | `headers/syscalls_proc.h:19` | `long sys_linux_vfork(long a1, long a2, long a3, long a4, long a5, long a6);` |
| `sys_linux_wait4` | function | `headers/syscalls_proc.h:22` | `long sys_linux_wait4(long a1, long a2, long a3, long a4, long a5, long a6);` |
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

Next: [SYMBOLS_p7.md](SYMBOLS_p7.md)
