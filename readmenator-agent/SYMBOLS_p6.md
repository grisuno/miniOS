# Symbols (page 6 of 26)
Previous: [SYMBOLS_p5.md](SYMBOLS_p5.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `pcm2_irq` | function | `headers/pcm2.h:81` | `void pcm2_irq(void);` |
| `pcm2_open` | function | `headers/pcm2.h:78` | `int pcm2_open(unsigned flags, int owner);` |
| `pcm2_poll` | function | `headers/pcm2.h:82` | `void pcm2_poll(void);` |
| `pcm2_write` | function | `headers/pcm2.h:79` | `int pcm2_write(const unsigned char *user, unsigned len, int owner);` |
| `PCM_RING_H` | macro | `headers/pcm_ring.h:2` | `#define PCM_RING_H` |
| `pcm_ring_free` | function | `headers/pcm_ring.h:51` | `static inline unsigned pcm_ring_free(const pcm_ring_t *r)` |
| `pcm_ring_init` | function | `headers/pcm_ring.h:36` | `static inline void pcm_ring_init(pcm_ring_t *r, unsigned char *buf,                              ...` |
| `pcm_ring_read` | function | `headers/pcm_ring.h:76` | `static inline unsigned pcm_ring_read(pcm_ring_t *r, unsigned char *dst,                          ...` |
| `pcm_ring_t` | struct | `headers/pcm_ring.h:26` | `` |
| `pcm_ring_used` | function | `headers/pcm_ring.h:47` | `static inline unsigned pcm_ring_used(const pcm_ring_t *r)` |
| `pcm_ring_write` | function | `headers/pcm_ring.h:55` | `static inline unsigned pcm_ring_write(pcm_ring_t *r, const unsigned char *src,                   ...` |
| `PCSPK_H` | macro | `headers/pcspk.h:2` | `#define PCSPK_H` |
| `PCSPK_VOL_DEFAULT` | macro | `headers/pcspk.h:6` | `#define PCSPK_VOL_DEFAULT` |
| `PCSPK_VOL_MAX` | macro | `headers/pcspk.h:5` | `#define PCSPK_VOL_MAX` |
| `PCSPK_VOL_MIN` | macro | `headers/pcspk.h:4` | `#define PCSPK_VOL_MIN` |
| `pcspk_get_volume` | function | `headers/pcspk.h:12` | `unsigned pcspk_get_volume(void);` |
| `pcspk_init` | function | `headers/pcspk.h:8` | `void pcspk_init(void);` |
| `pcspk_off` | function | `headers/pcspk.h:10` | `void pcspk_off(void);` |
| `pcspk_set_volume` | function | `headers/pcspk.h:11` | `void pcspk_set_volume(unsigned volume);` |
| `pcspk_tone` | function | `headers/pcspk.h:9` | `void pcspk_tone(unsigned freq);` |
| `PERCPU_RQ_H` | macro | `headers/percpu_rq.h:2` | `#define PERCPU_RQ_H` |
| `RQ_DEPTH` | macro | `headers/percpu_rq.h:45` | `#define RQ_DEPTH` |
| `RQ_RESCAN_PERIOD` | macro | `headers/percpu_rq.h:46` | `#define RQ_RESCAN_PERIOD` |
| `RQ_VALIDATE_ATTEMPTS` | macro | `headers/percpu_rq.h:47` | `#define RQ_VALIDATE_ATTEMPTS` |
| `WQ_NONE_HINT` | macro | `headers/percpu_rq.h:48` | `#define WQ_NONE_HINT` |
| `percpu_rq_t` | struct | `headers/percpu_rq.h:50` | `` |
| `rq_empty` | function | `headers/percpu_rq.h:65` | `int rq_empty(int cpu);` |
| `rq_enqueue` | function | `headers/percpu_rq.h:62` | `void rq_enqueue(int cpu, int pid);` |
| `rq_init` | function | `headers/percpu_rq.h:61` | `void rq_init(void);` |
| `rq_note_poll` | function | `headers/percpu_rq.h:67` | `void rq_note_poll(int cpu);` |
| `rq_pop_local` | function | `headers/percpu_rq.h:63` | `int rq_pop_local(int cpu);` |
| `rq_should_rescan` | function | `headers/percpu_rq.h:66` | `int rq_should_rescan(int cpu);` |
| `rq_stats` | function | `headers/percpu_rq.h:68` | `void rq_stats(int cpu, unsigned long *hits, unsigned long *steals, unsigned long *drops);` |
| `rq_steal_once` | function | `headers/percpu_rq.h:64` | `int rq_steal_once(int self_cpu, int *from_cpu);` |
| `PIPE_CAP_DEFAULT` | macro | `headers/pipe.h:21` | `#define PIPE_CAP_DEFAULT` |
| `PIPE_CAP_MAX` | macro | `headers/pipe.h:22` | `#define PIPE_CAP_MAX` |
| `PIPE_CFG_DEFAULT` | macro | `headers/pipe.h:43` | `#define PIPE_CFG_DEFAULT` |
| `PIPE_EMPTY` | macro | `headers/pipe.h:25` | `#define PIPE_EMPTY` |
| `PIPE_ERR_BOUND` | macro | `headers/pipe.h:24` | `#define PIPE_ERR_BOUND` |
| `PIPE_H` | macro | `headers/pipe.h:19` | `#define PIPE_H` |
| `ends` | function | `headers/pipe.h:4` | `* * Single source of truth for the pipe byte ring shared by the kernel * pipe ends (fs/kfile.c), the pipe/dup/dup2...` |
| `pipe_cfg_t` | struct | `headers/pipe.h:37` | `` |
| `pipe_ring_avail` | function | `headers/pipe.h:64` | `static inline unsigned pipe_ring_avail(const pipe_ring_t *r)` |
| `pipe_ring_close_reader` | function | `headers/pipe.h:128` | `static inline int pipe_ring_close_reader(pipe_ring_t *r)` |
| `pipe_ring_close_writer` | function | `headers/pipe.h:118` | `static inline int pipe_ring_close_writer(pipe_ring_t *r)` |
| `pipe_ring_init` | function | `headers/pipe.h:47` | `static inline int pipe_ring_init(pipe_ring_t *r, unsigned char *buf,         unsigned cap)` |
| `pipe_ring_ropen` | function | `headers/pipe.h:135` | `static inline int pipe_ring_ropen(const pipe_ring_t *r)` |
| `pipe_ring_space` | function | `headers/pipe.h:71` | `static inline unsigned pipe_ring_space(const pipe_ring_t *r)` |
| `pipe_ring_stat` | function | `headers/pipe.h:140` | `static inline int pipe_ring_stat(const pipe_ring_t *r, pipe_cfg_t *out)` |
| `pipe_ring_t` | struct | `headers/pipe.h:27` | `` |
| `pipe_ring_write` | function | `headers/pipe.h:79` | `static inline unsigned pipe_ring_write(pipe_ring_t *r,         const unsigned char *src, unsigned...` |
| `PROC_SEC_H` | macro | `headers/proc_sec.h:13` | `#define PROC_SEC_H` |
| `SECCOMP_FILTERS_MAX` | macro | `headers/proc_sec.h:16` | `#define SECCOMP_FILTERS_MAX` |
| `SECCOMP_KILL_EXIT` | macro | `headers/proc_sec.h:20` | `#define SECCOMP_KILL_EXIT` |
| `it` | function | `headers/proc_sec.h:31` | `* the syscall must answer in *ret when a filter decided it (ERRNO, TRACE, * USER_NOTIF);` |
| `proc_sec_exe` | function | `headers/proc_sec.h:28` | `const char *proc_sec_exe(int pid);` |
| `proc_sec_exec` | function | `headers/proc_sec.h:25` | `void proc_sec_exec(int pid);` |
| `proc_sec_filter` | function | `headers/proc_sec.h:34` | `int proc_sec_filter(long n, long a1, long a2, long a3, long a4, long a5, long a6, long *ret);` |
| `proc_sec_inherit` | function | `headers/proc_sec.h:23` | `void proc_sec_inherit(int child, int parent);` |
| `proc_sec_prctl` | function | `headers/proc_sec.h:36` | `long proc_sec_prctl(long option, long a2, long a3, long a4, long a5);` |
| `proc_sec_release` | function | `headers/proc_sec.h:24` | `void proc_sec_release(int pid);` |
| `proc_sec_seccomp` | function | `headers/proc_sec.h:37` | `long proc_sec_seccomp(long op, long flags, long uargs);` |
| `proc_sec_set_exe` | function | `headers/proc_sec.h:26` | `void proc_sec_set_exe(int pid, const char *resolved);` |
| `QGA_BAUD_DIVISOR` | macro | `headers/qga.h:25` | `#define QGA_BAUD_DIVISOR` |
| `QGA_COM2_BASE` | macro | `headers/qga.h:5` | `#define QGA_COM2_BASE` |
| `QGA_COM2_IRQ` | macro | `headers/qga.h:6` | `#define QGA_COM2_IRQ` |
| `QGA_FILE_MAX` | macro | `headers/qga.h:46` | `#define QGA_FILE_MAX` |
| `QGA_FILE_READ_MAX` | macro | `headers/qga.h:34` | `#define QGA_FILE_READ_MAX` |
| `QGA_H` | macro | `headers/qga.h:2` | `#define QGA_H` |
| `QGA_KEY_MAX` | macro | `headers/qga.h:38` | `#define QGA_KEY_MAX` |
| `QGA_LINE_MAX` | macro | `headers/qga.h:30` | `#define QGA_LINE_MAX` |
| `QGA_MAX_DEPTH` | macro | `headers/qga.h:42` | `#define QGA_MAX_DEPTH` |
| `QGA_MAX_PAIRS` | macro | `headers/qga.h:37` | `#define QGA_MAX_PAIRS` |
| `QGA_RESP_MAX` | macro | `headers/qga.h:31` | `#define QGA_RESP_MAX` |
| `QGA_STR_MAX` | macro | `headers/qga.h:39` | `#define QGA_STR_MAX` |
| `QGA_UART_DLL` | macro | `headers/qga.h:11` | `#define QGA_UART_DLL` |
| `QGA_UART_DLM` | macro | `headers/qga.h:12` | `#define QGA_UART_DLM` |
| `QGA_UART_FCR` | macro | `headers/qga.h:14` | `#define QGA_UART_FCR` |
| `QGA_UART_FCR_CFG` | macro | `headers/qga.h:22` | `#define QGA_UART_FCR_CFG` |
| `QGA_UART_IER` | macro | `headers/qga.h:13` | `#define QGA_UART_IER` |
| `QGA_UART_LCR` | macro | `headers/qga.h:15` | `#define QGA_UART_LCR` |
| `QGA_UART_LCR_8N1` | macro | `headers/qga.h:21` | `#define QGA_UART_LCR_8N1` |
| `QGA_UART_LCR_DLAB` | macro | `headers/qga.h:20` | `#define QGA_UART_LCR_DLAB` |
| `QGA_UART_LSR` | macro | `headers/qga.h:16` | `#define QGA_UART_LSR` |
| `QGA_UART_LSR_RX_RDY` | macro | `headers/qga.h:19` | `#define QGA_UART_LSR_RX_RDY` |
| `QGA_UART_LSR_TX_RDY` | macro | `headers/qga.h:18` | `#define QGA_UART_LSR_TX_RDY` |
| `QGA_UART_MCR` | macro | `headers/qga.h:17` | `#define QGA_UART_MCR` |
| `QGA_UART_MCR_CFG` | macro | `headers/qga.h:23` | `#define QGA_UART_MCR_CFG` |
| `QGA_UART_RBR` | macro | `headers/qga.h:10` | `#define QGA_UART_RBR` |
| `QGA_UART_THR` | macro | `headers/qga.h:9` | `#define QGA_UART_THR` |
| `qga_init` | function | `headers/qga.h:48` | `void qga_init(void);` |
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
| `EXECVE_MAX_ARG` | macro | `headers/sched.h:422` | `#define EXECVE_MAX_ARG` |
| `EXECVE_MAX_ARGS` | macro | `headers/sched.h:421` | `#define EXECVE_MAX_ARGS` |
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
| `USER_FAULT_SIGNAL` | macro | `headers/sched.h:417` | `#define USER_FAULT_SIGNAL` |
| `WAITPID_NOCHILD` | macro | `headers/sched.h:447` | `#define WAITPID_NOCHILD` |
| `WAITPID_NONE` | macro | `headers/sched.h:445` | `#define WAITPID_NONE` |
| `__attribute__` | function | `headers/sched.h:372` | `typedef struct __attribute__((packed))` |
| `ap_idle_proc` | variable | `headers/sched.h:356` | `extern proc_t ap_idle_proc[MAX_CPUS];` |
| `aslr_brk_pages` | function | `headers/sched.h:429` | `unsigned long aslr_brk_pages(void);` |
| `aslr_dyn_base` | function | `headers/sched.h:431` | `unsigned long aslr_dyn_base(void);` |
| `aslr_mmap_pages` | function | `headers/sched.h:430` | `unsigned long aslr_mmap_pages(void);` |
| `aslr_stack_bytes` | function | `headers/sched.h:428` | `unsigned long aslr_stack_bytes(void);` |
| `bsp_idtr` | variable | `headers/sched.h:373` | `extern idtr_t bsp_idtr;` |
| `bytes` | function | `headers/sched.h:173` | `* RLIM_AS total user bytes (brk growth + mmap) beyond the load base * RLIM_CPU timer ticks of CPU time, then...` |
| `caller` | function | `headers/sched.h:459` | `* caller (shell mrun) reaps it with do_waitpid. Returns pid or -1. * Programs using mmap/VMA or expecting a shared...` |
| `cpu` | struct | `headers/sched.h:268` | `` |
| `cpu_count` | variable | `headers/sched.h:295` | `extern int cpu_count;` |
| `cpu_idle_ticks` | variable | `headers/sched.h:361` | `extern volatile unsigned long cpu_idle_ticks[MAX_CPUS];` |
| `cpus` | variable | `headers/sched.h:294` | `extern cpu_t cpus[MAX_CPUS];` |
| `ctx_regs_t` | struct | `headers/sched.h:33` | `` |
| `current_pid` | macro | `headers/sched.h:312` | `#define current_pid` |
| `do_clone` | function | `headers/sched.h:408` | `long do_clone(long flags, long newsp);` |
| `do_execve` | function | `headers/sched.h:437` | `long do_execve(char *kpath, int kargc, char **kargv);` |
| `do_exit` | function | `headers/sched.h:407` | `void do_exit(int code);` |
| `do_fork` | function | `headers/sched.h:409` | `long do_fork(void);` |
| `do_fork_ex` | function | `headers/sched.h:410` | `long do_fork_ex(uint64_t set_tid, uint64_t clear_tid);` |
| `do_group_exit` | function | `headers/sched.h:413` | `void do_group_exit(int code);` |
| `do_kill` | function | `headers/sched.h:449` | `int do_kill(int pid);` |
| `do_kill_code` | function | `headers/sched.h:415` | `int do_kill_code(int pid, int code);` |
| `do_linux_clone` | function | `headers/sched.h:411` | `long do_linux_clone(unsigned long flags, unsigned long newsp, unsigned long ptid, unsigned long ctid, unsigned long...` |
| `do_thread_spawn` | function | `headers/sched.h:438` | `long do_thread_spawn(unsigned long fn, unsigned long stack, unsigned long arg);` |
| `do_waitpid` | function | `headers/sched.h:440` | `int do_waitpid(int pid);` |
| `do_waitpid_linux` | function | `headers/sched.h:448` | `int do_waitpid_linux(int pid, int nohang, int *found);` |
| `do_waitpid_nb` | function | `headers/sched.h:441` | `int do_waitpid_nb(int pid);` |
| `entry` | function | `headers/sched.h:135` | `* private view with one KFILE ref per live entry (0 on OOM), release * drops the view at reap, cloexec closes marked...` |
| `failure` | function | `headers/sched.h:436` | `* failure (negative errno);` |
| `first` | function | `headers/sched.h:232` | `* address first (SYSCALL_FRAME_WORDS in syscall_asm.h). It ends exactly at * the saved top (sc_top_save[pid]);` |
| `fork_child_settid` | function | `headers/sched.h:418` | `void fork_child_settid(void);` |
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
| `mm_view_claim_current` | function | `headers/sched.h:414` | `void mm_view_claim_current(void);` |
| `proc_count` | variable | `headers/sched.h:334` | `extern int proc_count;` |
| `proc_create` | function | `headers/sched.h:387` | `int proc_create(const char *name, int parent_pid);` |
| `proc_get` | function | `headers/sched.h:388` | `proc_t *proc_get(int pid);` |
| `proc_t` | struct | `headers/sched.h:50` | `` |
| `procs` | variable | `headers/sched.h:333` | `extern proc_t procs[MAX_PROCS];` |
| `pt_clone_user` | function | `headers/sched.h:453` | `uint64_t pt_clone_user(uint64_t parent_cr3);` |
| `pt_free_user` | function | `headers/sched.h:454` | `void pt_free_user(uint64_t cr3);` |
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
| `shell_nchildren` | function | `headers/sched.h:444` | `int shell_nchildren(void);` |
| `shell_reap_nb` | function | `headers/sched.h:442` | `int shell_reap_nb(int *pid_out, int *code_out);` |
| `shell_reap_one` | function | `headers/sched.h:443` | `int shell_reap_one(int pid, int *code_out);` |
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
| `timer_tick` | function | `headers/sched.h:450` | `void timer_tick(void);` |
| `tss_init_ap` | function | `headers/sched.h:385` | `void tss_init_ap(int cpu);` |
| `user_program_active` | variable | `headers/sched.h:336` | `extern volatile int user_program_active;` |
| `yield` | function | `headers/sched.h:406` | `void yield(void);` |
| `SBPF_A` | macro | `headers/seccomp_bpf.h:84` | `#define SBPF_A` |
| `SBPF_ABS` | macro | `headers/seccomp_bpf.h:63` | `#define SBPF_ABS` |
| `SBPF_ADD` | macro | `headers/seccomp_bpf.h:66` | `#define SBPF_ADD` |
| `SBPF_ALU` | macro | `headers/seccomp_bpf.h:57` | `#define SBPF_ALU` |
| `SBPF_AND` | macro | `headers/seccomp_bpf.h:71` | `#define SBPF_AND` |
| `SBPF_AUDIT_ARCH_X86_64` | macro | `headers/seccomp_bpf.h:49` | `#define SBPF_AUDIT_ARCH_X86_64` |
| `SBPF_CLASS` | macro | `headers/seccomp_bpf.h:52` | `#define SBPF_CLASS(c)` |
| `SBPF_DATA_SIZE` | macro | `headers/seccomp_bpf.h:31` | `#define SBPF_DATA_SIZE` |
| `SBPF_DIV` | macro | `headers/seccomp_bpf.h:69` | `#define SBPF_DIV` |
| `SBPF_ERR_INVALID` | macro | `headers/seccomp_bpf.h:35` | `#define SBPF_ERR_INVALID` |
| `SBPF_IMM` | macro | `headers/seccomp_bpf.h:62` | `#define SBPF_IMM` |
| `SBPF_JA` | macro | `headers/seccomp_bpf.h:77` | `#define SBPF_JA` |
| `SBPF_JEQ` | macro | `headers/seccomp_bpf.h:78` | `#define SBPF_JEQ` |
| `SBPF_JGE` | macro | `headers/seccomp_bpf.h:80` | `#define SBPF_JGE` |
| `SBPF_JGT` | macro | `headers/seccomp_bpf.h:79` | `#define SBPF_JGT` |
| `SBPF_JMP` | macro | `headers/seccomp_bpf.h:58` | `#define SBPF_JMP` |
| `SBPF_JSET` | macro | `headers/seccomp_bpf.h:81` | `#define SBPF_JSET` |
| `SBPF_K` | macro | `headers/seccomp_bpf.h:82` | `#define SBPF_K` |
| `SBPF_LD` | macro | `headers/seccomp_bpf.h:53` | `#define SBPF_LD` |
| `SBPF_LDX` | macro | `headers/seccomp_bpf.h:54` | `#define SBPF_LDX` |
| `SBPF_LEN` | macro | `headers/seccomp_bpf.h:65` | `#define SBPF_LEN` |
| `SBPF_LSH` | macro | `headers/seccomp_bpf.h:72` | `#define SBPF_LSH` |
| `SBPF_MAX_INSNS` | macro | `headers/seccomp_bpf.h:30` | `#define SBPF_MAX_INSNS` |
| `SBPF_MEM` | macro | `headers/seccomp_bpf.h:64` | `#define SBPF_MEM` |
| `SBPF_MEMWORDS` | macro | `headers/seccomp_bpf.h:32` | `#define SBPF_MEMWORDS` |
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

Next: [SYMBOLS_p7.md](SYMBOLS_p7.md)
