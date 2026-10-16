# API (page 5 of 21)
Previous: [API_p4.md](API_p4.md)

## headers/pcspk.h
Imported by: `drivers/pcspk.c`, `kernel/shell.c`, `kernel/syscalls.c`
- `pcspk_init` (function) `headers/pcspk.h:8` `void pcspk_init(void);`
- `pcspk_tone` (function) `headers/pcspk.h:9` `void pcspk_tone(unsigned freq);`
- `pcspk_off` (function) `headers/pcspk.h:10` `void pcspk_off(void);`
- `pcspk_set_volume` (function) `headers/pcspk.h:11` `void pcspk_set_volume(unsigned volume);`
- `pcspk_get_volume` (function) `headers/pcspk.h:12` `unsigned pcspk_get_volume(void);`

## headers/percpu_rq.h
Depends on: `headers/sched.h`, `headers/spinlock.h`
Imported by: `kernel/percpu_rq.c`, `kernel/sched.c`, `kernel/shell.c`, `kernel/syscalls.c`, `tests/test_percpu_rq.c`
- `rq_init` (function) `headers/percpu_rq.h:61` `void rq_init(void);`
- `rq_enqueue` (function) `headers/percpu_rq.h:62` `void rq_enqueue(int cpu, int pid);`
- `rq_pop_local` (function) `headers/percpu_rq.h:63` `int rq_pop_local(int cpu);`
- `rq_steal_once` (function) `headers/percpu_rq.h:64` `int rq_steal_once(int self_cpu, int *from_cpu);`
- `rq_empty` (function) `headers/percpu_rq.h:65` `int rq_empty(int cpu);`
- `rq_should_rescan` (function) `headers/percpu_rq.h:66` `int rq_should_rescan(int cpu);`
- `rq_note_poll` (function) `headers/percpu_rq.h:67` `void rq_note_poll(int cpu);`
- `rq_stats` (function) `headers/percpu_rq.h:68` `void rq_stats(int cpu, unsigned long *hits, unsigned long *steals, unsigned long *drops);`

## headers/pipe.h
Imported by: `headers/kernel.h`, `kernel/console_in.c`, `tests/test_pipe.c`
- `ends` (function) `headers/pipe.h:4` `* * Single source of truth for the pipe byte ring shared by the kernel * pipe ends (fs/kfile.c), the pipe/dup/dup2...`
- `pipe_ring_init` (function) `headers/pipe.h:47` `static inline int pipe_ring_init(pipe_ring_t *r, unsigned char *buf,
        unsigned cap)` -- Docstring: Bind a caller-owned buffer to a ring.
- `pipe_ring_avail` (function) `headers/pipe.h:64` `static inline unsigned pipe_ring_avail(const pipe_ring_t *r)` -- return PIPE_ERR_BOUND; if (cap == 0u || cap > PIPE_CAP_MAX) return PIPE_ERR_BOUND; r->buf = buf; r->cap = cap...
- `pipe_ring_space` (function) `headers/pipe.h:71` `static inline unsigned pipe_ring_space(const pipe_ring_t *r)` -- r->count = 0u; r->wopen = 1; r->ropen = 1; return 0; } /** Docstring: Bytes available to read.
- `pipe_ring_write` (function) `headers/pipe.h:79` `static inline unsigned pipe_ring_write(pipe_ring_t *r,
        const unsigned char *src, unsigned...` -- Docstring: Append up to len bytes, return bytes stored.
- `pipe_ring_close_writer` (function) `headers/pipe.h:118` `static inline int pipe_ring_close_writer(pipe_ring_t *r)` -- Docstring: Mark the writer closed.
- `pipe_ring_close_reader` (function) `headers/pipe.h:128` `static inline int pipe_ring_close_reader(pipe_ring_t *r)` -- Docstring: Mark the reader closed.
- `pipe_ring_ropen` (function) `headers/pipe.h:135` `static inline int pipe_ring_ropen(const pipe_ring_t *r)` -- Docstring: Mark the reader closed.
- `pipe_ring_stat` (function) `headers/pipe.h:140` `static inline int pipe_ring_stat(const pipe_ring_t *r, pipe_cfg_t *out)` -- Docstring: Snapshot ring geometry into a caller struct.

## headers/proc_sec.h
Imported by: `kernel/exec.c`, `kernel/proc_sec.c`, `kernel/sched.c`, `kernel/shell.c`, `kernel/syscalls.c`, `kernel/syscalls_proc.c`
- `proc_sec_inherit` (function) `headers/proc_sec.h:23` `void proc_sec_inherit(int child, int parent);` -- Exit code of a process or thread a filter kills: a death by SIGSYS (31), recorded negative like every MiniOS signal...
- `proc_sec_release` (function) `headers/proc_sec.h:24` `void proc_sec_release(int pid);`
- `proc_sec_exec` (function) `headers/proc_sec.h:25` `void proc_sec_exec(int pid);`
- `proc_sec_set_exe` (function) `headers/proc_sec.h:26` `void proc_sec_set_exe(int pid, const char *resolved);`
- `proc_sec_exe` (function) `headers/proc_sec.h:28` `const char *proc_sec_exe(int pid);` -- Exit code of a process or thread a filter kills: a death by SIGSYS (31), recorded negative like every MiniOS signal...
- `it` (function) `headers/proc_sec.h:31` `* the syscall must answer in *ret when a filter decided it (ERRNO, TRACE, * USER_NOTIF);`
- `proc_sec_filter` (function) `headers/proc_sec.h:34` `int proc_sec_filter(long n, long a1, long a2, long a3, long a4, long a5, long a6, long *ret);` -- Run the caller's filters for syscall n.
- `proc_sec_prctl` (function) `headers/proc_sec.h:36` `long proc_sec_prctl(long option, long a2, long a3, long a4, long a5);`
- `proc_sec_seccomp` (function) `headers/proc_sec.h:37` `long proc_sec_seccomp(long op, long flags, long uargs);`

## headers/qga.h
Imported by: `qga.c`
- `qga_init` (function) `headers/qga.h:48` `void qga_init(void);`
- `qga_poll` (function) `headers/qga.h:49` `void qga_poll(void);`

## headers/randmix.h
Imported by: `kernel/syscalls.c`, `tests/test_randmix.c`
- `source` (function) `headers/randmix.h:11` `* source (all-zero seed) still walks, because the increment is inside
 * the mixer, not in the ca...`

## headers/rcu.h
Depends on: `headers/sched.h`, `headers/spinlock.h`
Imported by: `kernel/rcu.c`, `kernel/sched.c`, `kernel/syscalls.c`, `tests/test_rcu.c`
- `retirement` (function) `headers/rcu.h:30` `* retirement (the writer keeps ownership) instead of dropping the free. * Callbacks run in tick context with...`
- `rcu_init` (function) `headers/rcu.h:51` `void rcu_init(void);`
- `rcu_read_lock` (function) `headers/rcu.h:52` `void rcu_read_lock(void);`
- `rcu_read_unlock` (function) `headers/rcu.h:53` `void rcu_read_unlock(void);`
- `rcu_deref` (function) `headers/rcu.h:54` `void *rcu_deref(void *volatile *pp);`
- `rcu_publish` (function) `headers/rcu.h:55` `void rcu_publish(void *volatile *pp, void *v);`
- `rcu_call` (function) `headers/rcu.h:56` `long rcu_call(rcu_cb_t fn, void *arg);`
- `rcu_note_tick` (function) `headers/rcu.h:57` `void rcu_note_tick(int cpu);`
- `rcu_note_idle` (function) `headers/rcu.h:58` `void rcu_note_idle(int cpu);`
- `rcu_poll` (function) `headers/rcu.h:59` `void rcu_poll(void);`
- `rcu_synchronize` (function) `headers/rcu.h:60` `long rcu_synchronize(void);`

## headers/rtc.h
Imported by: `drivers/rtc.c`, `kernel/minifetch.c`, `kernel/shell.c`, `kernel/syscalls.c`, `qga.c`, `tests/test_rtc.c`
- `rtc_read_tod` (function) `headers/rtc.h:4` `int rtc_read_tod(int *hour, int *min, int *sec);`
- `rtc_read_date` (function) `headers/rtc.h:11` `int rtc_read_date(int *year, int *mon, int *day);` -- Calendar date from the CMOS RTC (registers 0x07-0x09).
- `suite` (function) `headers/rtc.h:15` `* host suite (tests/test_rtc.c);`
- `rtc_days_from_civil` (function) `headers/rtc.h:18` `static inline long rtc_days_from_civil(long y, long m, long d)` -- Days since 1970-01-01 for a civil date (Howard Hinnant's algorithm, pure integer arithmetic, no tables).
- `rtc_wall_seconds` (function) `headers/rtc.h:33` `int rtc_wall_seconds(unsigned long *out);` -- Wall-clock seconds since the Unix epoch from one RTC snapshot.

## headers/sb16.h
Imported by: `drivers/pcm2.c`, `drivers/sb16.c`, `kernel.c`, `kernel/sched.c`, `kernel/shell.c`, `kernel/syscalls.c`
- `sb16_init` (function) `headers/sb16.h:65` `int sb16_init(void);`
- `sb16_present` (function) `headers/sb16.h:66` `int sb16_present(void);`
- `sb16_tone` (function) `headers/sb16.h:67` `void sb16_tone(unsigned freq);`
- `sb16_irq` (function) `headers/sb16.h:68` `void sb16_irq(void);`
- `sb16_poll` (function) `headers/sb16.h:69` `void sb16_poll(void);`
- `sb16_pcm_open` (function) `headers/sb16.h:73` `void sb16_pcm_open(void);` -- Legacy single-stream API (maps to mixer stream 0: pcm_open allocates it, * pcm_submit forwards into it, pcm_close...
- `sb16_pcm_submit` (function) `headers/sb16.h:74` `int sb16_pcm_submit(const unsigned char *pcm, unsigned len);`
- `sb16_pcm_close` (function) `headers/sb16.h:75` `void sb16_pcm_close(void);`
- `sb16_pump` (function) `headers/sb16.h:76` `void sb16_pump(void);`
- `sb16_stream_open` (function) `headers/sb16.h:79` `int sb16_stream_open(void);` -- Legacy single-stream API (maps to mixer stream 0: pcm_open allocates it, * pcm_submit forwards into it, pcm_close...
- `sb16_stream_close` (function) `headers/sb16.h:80` `void sb16_stream_close(int id);`
- `sb16_stream_submit` (function) `headers/sb16.h:81` `int sb16_stream_submit(int id, const unsigned char *pcm, unsigned len);`
- `sb16_stream_volume` (function) `headers/sb16.h:82` `void sb16_stream_volume(int id, unsigned char vol);`
- `sb16_stream_count` (function) `headers/sb16.h:83` `int sb16_stream_count(void);`
- `sb16_ring_free` (function) `headers/sb16.h:85` `unsigned sb16_ring_free(void);`
- `sb16_mode_active` (function) `headers/sb16.h:86` `int sb16_mode_active(void);`
- `sb16_legacy_busy` (function) `headers/sb16.h:91` `int sb16_legacy_busy(void);` -- True while the legacy engine audibly owns the DSP (PCM stream open or a tone sounding). pcm2_open consults it for...
- `sb16_counters` (function) `headers/sb16.h:93` `void sb16_counters(sb16_counters_t *out);`

## headers/sched.h
Depends on: `headers/spinlock.h`, `headers/vma.h`
Imported by: `drivers/kbd.c`, `drivers/pcm2.c`, `headers/futex.h`, `headers/percpu_rq.h`, `headers/rcu.h`, `headers/spawn.h`, `headers/sync.h`, `kernel.c`, `kernel/console.c`, `kernel/exec.c`, `kernel/loader.c`, `kernel/minifetch.c`, `kernel/mm.c`, `kernel/mm/cow.c`, `kernel/mm/tlb.c`, `kernel/panic.c`, `kernel/proc_sec.c`, `kernel/sched.c`, `kernel/serial.c`, `kernel/shell.c`, `kernel/spawn.c`, `kernel/syscalls.c`, `kernel/syscalls_proc.c`, `kernel/vga_fb.c`, `net/net.c`, `net/rtl8139.c`, `progs/src/lxabi.c`, `smp.c`
- `group` (function) `headers/sched.h:108` `* process is its own group (tgid == pid);`
- `entry` (function) `headers/sched.h:135` `* private view with one KFILE ref per live entry (0 on OOM), release * drops the view at reap, cloexec closes marked...`
- `kfd_view_copy` (function) `headers/sched.h:138` `int kfd_view_copy(proc_t *child, proc_t *parent);`
- `kfd_view_release` (function) `headers/sched.h:139` `void kfd_view_release(proc_t *p);`
- `kfd_view_cloexec` (function) `headers/sched.h:140` `void kfd_view_cloexec(void);`
- `kfd_view_root` (function) `headers/sched.h:141` `kfd_view_t *kfd_view_root(void);`
- `bytes` (function) `headers/sched.h:173` `* RLIM_AS total user bytes (brk growth + mmap) beyond the load base * RLIM_CPU timer ticks of CPU time, then...`
- `first` (function) `headers/sched.h:232` `* address first (SYSCALL_FRAME_WORDS in syscall_asm.h). It ends exactly at * the saved top (sc_top_save[pid]);`
- `syscall_frame_current` (function) `headers/sched.h:245` `const syscall_frame_t *syscall_frame_current(void);` -- The frame syscall_entry.S builds on the per-proc kernel stack, lowest address first (SYSCALL_FRAME_WORDS in...
- `sched_idle_on_kernel_cr3` (function) `headers/sched.h:359` `int sched_idle_on_kernel_cr3(int cpu);` -- 1 when cpu's idle context is parked on the kernel page tables, never on * a process's (whose tables are freed when...
- `sched_init` (function) `headers/sched.h:379` `void sched_init(void);` -- Per-CPU TSS selectors: slot 5 + 2*cpu in the runtime GDT (each TSS descriptor occupies two 8-byte slots).
- `kstack_report` (function) `headers/sched.h:380` `void kstack_report(void);`
- `schedtop_report` (function) `headers/sched.h:381` `void schedtop_report(void);`
- `irqstat_report` (function) `headers/sched.h:382` `void irqstat_report(void);`
- `gdb_regs_report` (function) `headers/sched.h:383` `void gdb_regs_report(int pid);`
- `gdb_dump_report` (function) `headers/sched.h:384` `void gdb_dump_report(unsigned long addr, unsigned long len);`
- `tss_init_ap` (function) `headers/sched.h:388` `void tss_init_ap(int cpu);`
- `smp_ap_idle_loop` (function) `headers/sched.h:389` `void smp_ap_idle_loop(void);`
- `proc_create` (function) `headers/sched.h:390` `int proc_create(const char *name, int parent_pid);`
- `proc_get` (function) `headers/sched.h:391` `proc_t *proc_get(int pid);`
- `schedule` (function) `headers/sched.h:392` `void schedule(void);`
- `sched_set_nice` (function) `headers/sched.h:393` `int sched_set_nice(int pid, int nice);`
- `seccomp_deny_one` (function) `headers/sched.h:394` `int seccomp_deny_one(int pid, int n);`
- `seccomp_allow_one` (function) `headers/sched.h:395` `int seccomp_allow_one(int pid, int n);`
- `seccomp_denied` (function) `headers/sched.h:396` `int seccomp_denied(int pid, int n);`
- `rlimit_cpu_exceeded` (function) `headers/sched.h:397` `int rlimit_cpu_exceeded(int pid);`
- `rlimit_cpu_tick` (function) `headers/sched.h:398` `void rlimit_cpu_tick(int pid);`
- `switch_to` (function) `headers/sched.h:399` `void switch_to(proc_t *prev, proc_t *next);`
- `switch_to_notrap` (function) `headers/sched.h:400` `void switch_to_notrap(proc_t *prev, proc_t *next);`
- `switch_save_only` (function) `headers/sched.h:401` `void switch_save_only(proc_t *prev);`
- `resume_iretq` (function) `headers/sched.h:408` `void resume_iretq(void);`
- `yield` (function) `headers/sched.h:409` `void yield(void);`
- `do_exit` (function) `headers/sched.h:410` `void do_exit(int code);`
- `do_clone` (function) `headers/sched.h:411` `long do_clone(long flags, long newsp);`
- `do_fork` (function) `headers/sched.h:412` `long do_fork(void);`
- `do_fork_ex` (function) `headers/sched.h:413` `long do_fork_ex(uint64_t set_tid, uint64_t clear_tid);`
- `do_linux_clone` (function) `headers/sched.h:414` `long do_linux_clone(unsigned long flags, unsigned long newsp, unsigned long ptid, unsigned long ctid, unsigned long...`
- `do_group_exit` (function) `headers/sched.h:416` `void do_group_exit(int code);`
- `mm_view_claim_current` (function) `headers/sched.h:417` `void mm_view_claim_current(void);`
- `do_kill_code` (function) `headers/sched.h:418` `int do_kill_code(int pid, int code);`
- `fork_child_settid` (function) `headers/sched.h:421` `void fork_child_settid(void);` -- void     sched_park_capture(proc_t *cur); void     resume_iretq(void); void     yield(void); void     do_exit(int...
- `aslr_stack_bytes` (function) `headers/sched.h:431` `unsigned long aslr_stack_bytes(void);` -- ASLR jitter, fresh per exec (TSC + ticks + per-exec counter, never zero for stack/brk so consecutive execs differ...
- `aslr_brk_pages` (function) `headers/sched.h:432` `unsigned long aslr_brk_pages(void);`
- `aslr_mmap_pages` (function) `headers/sched.h:433` `unsigned long aslr_mmap_pages(void);`
- `aslr_dyn_base` (function) `headers/sched.h:434` `unsigned long aslr_dyn_base(void);`
- `failure` (function) `headers/sched.h:439` `* failure (negative errno);`
- `do_execve` (function) `headers/sched.h:440` `long do_execve(char *kpath, int kargc, char **kargv);` -- do_execve() - replace the caller's image with a fresh ET_EXEC/ET_DYN program (kernel/sched.c).
- `do_thread_spawn` (function) `headers/sched.h:441` `long do_thread_spawn(unsigned long fn, unsigned long stack, unsigned long arg);`
- `do_waitpid` (function) `headers/sched.h:443` `int do_waitpid(int pid);`
- `do_waitpid_nb` (function) `headers/sched.h:444` `int do_waitpid_nb(int pid);`
- `shell_reap_nb` (function) `headers/sched.h:445` `int shell_reap_nb(int *pid_out, int *code_out);`
- `shell_reap_one` (function) `headers/sched.h:446` `int shell_reap_one(int pid, int *code_out);`
- `shell_nchildren` (function) `headers/sched.h:447` `int shell_nchildren(void);`
- `do_waitpid_linux` (function) `headers/sched.h:451` `int do_waitpid_linux(int pid, int nohang, int *found);` -- kstack slot family, fd table and limits; everything else (window, VMA, brk view, stack, FPU, FSBASE, name) is rebuilt.
- `do_kill` (function) `headers/sched.h:452` `int do_kill(int pid);`
- `timer_tick` (function) `headers/sched.h:453` `void timer_tick(void);`
- `pt_clone_user` (function) `headers/sched.h:456` `uint64_t pt_clone_user(uint64_t parent_cr3);` -- unsigned long arg); int      do_waitpid(int pid); int      do_waitpid_nb(int pid); int      shell_reap_nb(int...
- `pt_free_user` (function) `headers/sched.h:457` `void pt_free_user(uint64_t cr3);`
- `caller` (function) `headers/sched.h:462` `* caller (shell mrun) reaps it with do_waitpid. Returns pid or -1. * Programs using mmap/VMA or expecting a shared...`

## headers/seccomp_bpf.h
Imported by: `kernel/proc_sec.c`, `kernel/seccomp_bpf.c`, `tests/test_seccomp_bpf.c`
- `sbpf_check` (function) `headers/seccomp_bpf.h:95` `int sbpf_check(const sbpf_insn *prog, unsigned len, unsigned short *scratch);` -- Validate a program before it ever runs: 1..SBPF_MAX_INSNS instructions, only the opcodes Linux accepts for seccomp...
- `sbpf_run` (function) `headers/seccomp_bpf.h:100` `unsigned int sbpf_run(const sbpf_insn *prog, unsigned len, const sbpf_data *d);` -- Run a program sbpf_check accepted over one syscall's data; returns the 32-bit action.
- `sbpf_action_rank` (function) `headers/seccomp_bpf.h:104` `int sbpf_action_rank(unsigned int action);` -- Restrictiveness rank of an action (0 = most restrictive): the order * stacked filters are combined in.

## headers/shell.h
Depends on: `headers/kernel.h`, `headers/kernel/console_in.h`
Imported by: `kernel/editor.c`, `kernel/shell.c`, `kernel/syscalls.c`
- `shell_readline_buf` (function) `headers/shell.h:18` `void shell_readline_buf(char *buf, int size);` -- Read one line into buf with arrow-key editing; used by the built-in * editor to edit file text.
- `shell_parse` (function) `headers/shell.h:21` `int shell_parse(char *line, char **argv, int max_args);` -- Read one line into buf with arrow-key editing; used by the built-in * editor to edit file text. void...
- `shell_parse_long` (function) `headers/shell.h:29` `int shell_parse_long(const char *s, long *out);` -- Strict signed decimal parse for numeric shell/editor operands: an optional sign followed by at least one digit...
- `shell_parse_pid` (function) `headers/shell.h:34` `int shell_parse_pid(const char *s, int min_pid, int *out);` -- Bounded pid parse: strict shell_parse_long plus min_pid <= pid < MAX_PROCS.
- `shell_cmd_sh` (function) `headers/shell.h:39` `int shell_cmd_sh(int argc, char **argv);` -- Execute a shell script: read `path` line by line, skip blanks and `#` comments, parse each line and dispatch it...

## headers/sign.h
Imported by: `kernel/ed25519.c`, `kernel/loader.c`, `tests/test_sign.c`
- `sign_pubkey` (function) `headers/sign.h:47` `static inline const unsigned char *sign_pubkey(unsigned id)` -- Docstring: Look up the trusted public key for a key id. * Answers 0 for unknown ids and for the unprovisioned slot.
- `ed_sha512_init` (function) `headers/sign.h:69` `void ed_sha512_init(ed_sha *c);`
- `ed_sha512_update` (function) `headers/sign.h:70` `void ed_sha512_update(ed_sha *c, const unsigned char *data, unsigned long len);`
- `ed_sha512_final` (function) `headers/sign.h:71` `void ed_sha512_final(ed_sha *c, unsigned char out[64]);`
- `ed25519_verify` (function) `headers/sign.h:75` `int ed25519_verify(const unsigned char sig[64], const unsigned char *msg, unsigned long msglen, const unsigned char...` -- Docstring: Verify an Ed25519 signature, 1 valid else 0. * See kernel/ed25519.c for the full contract.

## headers/smp.h
Depends on: `headers/spinlock.h`
Imported by: `kernel.c`, `kernel/mm/tlb.c`, `kernel/sched.c`, `kernel/shell.c`, `smp.c`
- `smp_init` (function) `headers/smp.h:41` `void smp_init(void);`
- `smp_ap_entry` (function) `headers/smp.h:42` `void smp_ap_entry(void);`
- `smp_ipi_broadcast` (function) `headers/smp.h:43` `void smp_ipi_broadcast(int vector);` -- PIT-anchored LAPIC calibration (ticks per 10 ms at divide-by-16).
- `smp_nmi_broadcast` (function) `headers/smp.h:44` `void smp_nmi_broadcast(void);` -- PIT-anchored LAPIC calibration (ticks per 10 ms at divide-by-16).

## headers/spawn.h
Depends on: `headers/kernel.h`, `headers/sched.h`, `headers/vma.h`
Imported by: `kernel/sched.c`, `kernel/shell.c`, `kernel/spawn.c`, `kernel/syscalls.c`
- `spawn_backup` (function) `headers/spawn.h:28` `int spawn_backup(spawn_ctx_t *ctx);` -- Docstring: Save the caller shared-window view into ctx.
- `spawn_restore` (function) `headers/spawn.h:31` `void spawn_restore(spawn_ctx_t *ctx);` -- Docstring: Save the caller shared-window view into ctx.
- `spawn_validate_argv` (function) `headers/spawn.h:34` `int spawn_validate_argv(int argc, const char **uargv);` -- Docstring: Save the caller shared-window view into ctx.
- `spawn_copy_argv` (function) `headers/spawn.h:39` `char **spawn_copy_argv(int argc, const char **uargv);` -- Docstring: Copy user argv into kernel memory, zero terminated.
- `spawn_free_argv` (function) `headers/spawn.h:42` `void spawn_free_argv(char **kargv, int argc);` -- Docstring: Copy user argv into kernel memory, zero terminated.
- `spawn_load_image` (function) `headers/spawn.h:45` `unsigned char *spawn_load_image(const char *resolved, unsigned *size_out);` -- Docstring: Copy user argv into kernel memory, zero terminated.
- `spawn_execute` (function) `headers/spawn.h:48` `int spawn_execute(const char *resolved, const char *redirect, unsigned char *data, unsigned data_size, int argc...` -- Docstring: Copy user argv into kernel memory, zero terminated.

## headers/spinlock.h
Imported by: `drivers/pcm2.c`, `headers/futex.h`, `headers/kernel.h`, `headers/percpu_rq.h`, `headers/rcu.h`, `headers/sched.h`, `headers/smp.h`, `headers/sync.h`, `kernel/mm/tlb.c`
- `spin_init` (function) `headers/spinlock.h:46` `static inline void spin_init(spinlock_t *lock)`
- `spin_save_irq` (function) `headers/spinlock.h:56` `static inline irqflags_t spin_save_irq(void)` -- Host unit-test variants (tests/test_sync.c, `make test-sync`): cli/sti and pushf/popf are privileged and fault in...
- `spin_restore_irq` (function) `headers/spinlock.h:57` `static inline void spin_restore_irq(irqflags_t flags)`
- `spin_lock` (function) `headers/spinlock.h:58` `static inline void spin_lock(spinlock_t *lock)`
- `spin_unlock` (function) `headers/spinlock.h:64` `static inline void spin_unlock(spinlock_t *lock)`
- `spin_lock_irqsave` (function) `headers/spinlock.h:68` `static inline void spin_lock_irqsave(spinlock_t *lock, irqflags_t *flags)`
- `spin_unlock_irqrestore` (function) `headers/spinlock.h:75` `static inline void spin_unlock_irqrestore(spinlock_t *lock, irqflags_t flags)`
- `spin_unlock_keep_irq` (function) `headers/spinlock.h:80` `static inline void spin_unlock_keep_irq(spinlock_t *lock)`
- `spin_trylock` (function) `headers/spinlock.h:84` `static inline int spin_trylock(spinlock_t *lock)`
- `spin_save_irq` (function) `headers/spinlock.h:92` `static inline irqflags_t spin_save_irq(void)` -- __sync_lock_release(&lock->locked); } static inline void spin_unlock_keep_irq(spinlock_t *lock) {...
- `spin_restore_irq` (function) `headers/spinlock.h:99` `static inline void spin_restore_irq(irqflags_t flags)` -- int was = __sync_lock_test_and_set(&lock->locked, 1); if (!was) __sync_synchronize(); return !was; } #else /* Read...
- `spin_lock` (function) `headers/spinlock.h:107` `static inline void spin_lock(spinlock_t *lock)` -- Acquire the lock and disable interrupts.
- `spin_unlock` (function) `headers/spinlock.h:118` `static inline void spin_unlock(spinlock_t *lock)` -- Release the lock and re-enable interrupts.
- `spin_unlock_keep_irq` (function) `headers/spinlock.h:130` `static inline void spin_unlock_keep_irq(spinlock_t *lock)` -- Release the lock WITHOUT touching interrupts (IF stays as-is).
- `spin_unlock_irqrestore` (function) `headers/spinlock.h:150` `static inline void spin_unlock_irqrestore(spinlock_t *lock, irqflags_t flags)` -- Release the lock and restore the saved interrupt state.

## headers/sync.h
Depends on: `headers/sched.h`, `headers/spinlock.h`
Imported by: `drivers/sb16.c`, `headers/futex.h`, `kernel/futex.c`, `kernel/sched.c`, `kernel/sync.c`, `kernel/syscalls.c`, `tests/test_sync.c`
- `wq_init` (function) `headers/sync.h:50` `void wq_init(wait_queue_t *q);`
- `sleep_on` (function) `headers/sync.h:51` `void sleep_on(wait_queue_t *q);`
- `wake_up` (function) `headers/sync.h:52` `int wake_up(wait_queue_t *q);`
- `wake_up_all` (function) `headers/sync.h:53` `int wake_up_all(wait_queue_t *q);`
- `inheritance` (function) `headers/sync.h:56` `* Priority inheritance (thesis correction 3): a low-priority holder that * blocks a high-priority waiter is boosted...`
- `mutex_init` (function) `headers/sync.h:72` `void mutex_init(mutex_t *m);`
- `mutex_lock` (function) `headers/sync.h:73` `void mutex_lock(mutex_t *m);`
- `mutex_unlock` (function) `headers/sync.h:74` `void mutex_unlock(mutex_t *m);`
- `mutex_trylock` (function) `headers/sync.h:75` `int mutex_trylock(mutex_t *m);`
- `mutex_note_waiter` (function) `headers/sync.h:76` `void mutex_note_waiter(mutex_t *m, int waiter);`
- `pi_set_base` (function) `headers/sync.h:77` `void pi_set_base(int pid, int prio);`
- `pi_get_eff` (function) `headers/sync.h:78` `int pi_get_eff(int pid);`
- `sem_init` (function) `headers/sync.h:89` `void sem_init(sem_t *s, int value);`
- `sem_wait` (function) `headers/sync.h:90` `void sem_wait(sem_t *s);`
- `sem_post` (function) `headers/sync.h:91` `void sem_post(sem_t *s);`
- `cond_init` (function) `headers/sync.h:103` `void cond_init(cond_t *c);`
- `cond_wait` (function) `headers/sync.h:104` `void cond_wait(cond_t *c, mutex_t *m);`
- `cond_signal` (function) `headers/sync.h:105` `void cond_signal(cond_t *c);`
- `cond_broadcast` (function) `headers/sync.h:106` `void cond_broadcast(cond_t *c);`
- `rwlock_init` (function) `headers/sync.h:118` `void rwlock_init(rwlock_t *rw);`
- `rwlock_read_lock` (function) `headers/sync.h:119` `void rwlock_read_lock(rwlock_t *rw);`
- `rwlock_read_unlock` (function) `headers/sync.h:120` `void rwlock_read_unlock(rwlock_t *rw);`
- `rwlock_write_lock` (function) `headers/sync.h:121` `void rwlock_write_lock(rwlock_t *rw);`
- `rwlock_write_unlock` (function) `headers/sync.h:122` `void rwlock_write_unlock(rwlock_t *rw);`

## headers/syscalls_proc.h
Imported by: `kernel/proc_sec.c`, `kernel/syscalls.c`, `kernel/syscalls_proc.c`
- `dispatcher` (function) `headers/syscalls_proc.h:5` `* dispatcher (kernel/syscalls.c). These handlers touch only scheduler * state (current_pid, procs[], do_* /...`
- `sys_minios_nice` (function) `headers/syscalls_proc.h:12` `long sys_minios_nice(long a1, long a2, long a3, long a4, long a5, long a6);`
- `sys_minios_clone` (function) `headers/syscalls_proc.h:13` `long sys_minios_clone(long flags, long newsp, long a3, long a4, long a5, long a6);`
- `sys_minios_thread_spawn` (function) `headers/syscalls_proc.h:14` `long sys_minios_thread_spawn(long a1, long a2, long a3, long a4, long a5, long a6);`
- `sys_linux_yield` (function) `headers/syscalls_proc.h:15` `long sys_linux_yield(long a1, long a2, long a3, long a4, long a5, long a6);`
- `sys_linux_getpid` (function) `headers/syscalls_proc.h:16` `long sys_linux_getpid(long a1, long a2, long a3, long a4, long a5, long a6);`
- `sys_linux_gettid` (function) `headers/syscalls_proc.h:17` `long sys_linux_gettid(long a1, long a2, long a3, long a4, long a5, long a6);`
- `sys_linux_fork` (function) `headers/syscalls_proc.h:18` `long sys_linux_fork(long a1, long a2, long a3, long a4, long a5, long a6);`
- `sys_linux_clone` (function) `headers/syscalls_proc.h:19` `long sys_linux_clone(long a1, long a2, long a3, long a4, long a5, long a6);`
- `sys_linux_vfork` (function) `headers/syscalls_proc.h:20` `long sys_linux_vfork(long a1, long a2, long a3, long a4, long a5, long a6);`
- `sys_linux_execve` (function) `headers/syscalls_proc.h:21` `long sys_linux_execve(long a1, long a2, long a3, long a4, long a5, long a6);`
- `sys_linux_exit` (function) `headers/syscalls_proc.h:22` `long sys_linux_exit(long a1, long a2, long a3, long a4, long a5, long a6);`
- `sys_linux_wait4` (function) `headers/syscalls_proc.h:23` `long sys_linux_wait4(long a1, long a2, long a3, long a4, long a5, long a6);`
- `sys_linux_kill` (function) `headers/syscalls_proc.h:24` `long sys_linux_kill(long a1, long a2, long a3, long a4, long a5, long a6);`
- `linux_signal_fatal` (function) `headers/syscalls_proc.h:31` `int linux_signal_fatal(long sig);` -- Linux signal numbers 1..LINUX_SIGNAL_MAX; a fatal one ends its target. * The foreground shell reports a signal death...
- `do_proc_exit` (function) `headers/syscalls_proc.h:34` `long do_proc_exit(long code);` -- Linux signal numbers 1..LINUX_SIGNAL_MAX; a fatal one ends its target. * The foreground shell reports a signal death...

## headers/tick.h
Imported by: `kernel/sched.c`, `kernel/tick.c`, `tests/test_tick.c`
- `tick_reset` (function) `headers/tick.h:47` `void tick_reset(void);` -- needs; the bound exists so the tables stay fixed-size. #define TICK_MAX_USB_LISTENERS 2 /** Docstring: Default bus...
- `tick_register_audio` (function) `headers/tick.h:54` `int tick_register_audio(tick_fn_t fn, void *ctx);` -- Docstring: Register an unconditional BSP audio effect.
- `tick_register_desktop` (function) `headers/tick.h:61` `int tick_register_desktop(tick_fn_t fn, void *ctx);` -- Docstring: Register a gated desktop effect.
- `tick_register_usb` (function) `headers/tick.h:69` `int tick_register_usb(tick_fn_t fn, void *ctx);` -- Docstring: Register a polled USB controller effect.
- `tick_run_usb` (function) `headers/tick.h:72` `void tick_run_usb(void);` -- Docstring: Register a polled USB controller effect.
- `tick_run_audio` (function) `headers/tick.h:75` `void tick_run_audio(void);` -- Docstring: Register a polled USB controller effect.
- `tick_run_desktop` (function) `headers/tick.h:78` `void tick_run_desktop(void);` -- The xHCI event ring is polled by decision rather than interrupt-driven, so this listener is the polling trigger.
- `tick_audio_count` (function) `headers/tick.h:81` `int tick_audio_count(void);` -- handler is null or the USB table is full.
- `tick_desktop_count` (function) `headers/tick.h:84` `int tick_desktop_count(void);` -- /** Docstring: Run USB listeners in registration order. void tick_run_usb(void); /** Docstring: Run audio listeners...
- `tick_desktop_due` (function) `headers/tick.h:92` `int tick_desktop_due(unsigned long long ticks, unsigned interval);` -- Docstring: Pure desktop gating predicate.

## headers/tlb.h
Imported by: `kernel/mm/cow.c`, `kernel/mm/paging.c`, `kernel/mm/tlb.c`, `kernel/sched.c`, `kernel/shell.c`, `kernel/syscalls.c`
- `space` (function) `headers/tlb.h:4` `* while that CPU keeps running the same address space (CLONE_VM threads on * an AP). Callers clear the PTEs, flush...`
- `tlb_shootdown_count` (function) `headers/tlb.h:22` `unsigned long tlb_shootdown_count(void);` -- Shootdowns broadcast and acknowledgement waits that ran out of budget * (reported by the smp builtin).
- `tlb_shootdown_timeouts` (function) `headers/tlb.h:23` `unsigned long tlb_shootdown_timeouts(void);`
- `tlb_nmi_entry` (function) `headers/tlb.h:26` `void tlb_nmi_entry(void);` -- Shootdowns broadcast and acknowledgement waits that ran out of budget * (reported by the smp builtin). unsigned long...

## headers/tls.h
Imported by: `net/net.c`, `net/tls.c`, `net/tls_crypto.c`, `net/tls_x509.c`, `progs/tls_u/tls_u_main.c`, `tls_test.c`
- `sha256_init` (function) `headers/tls.h:168` `void sha256_init(struct sha256_ctx *c);`
- `sha256_update` (function) `headers/tls.h:169` `void sha256_update(struct sha256_ctx *c, const unsigned char *data, unsigned len);`
- `sha256_final` (function) `headers/tls.h:170` `void sha256_final(struct sha256_ctx *c, unsigned char out[32]);`
- `sha256` (function) `headers/tls.h:171` `void sha256(const unsigned char *data, unsigned len, unsigned char out[32]);`
- `sha384` (function) `headers/tls.h:172` `void sha384(const unsigned char *data, unsigned len, unsigned char out[48]);`
- `hmac_sha256` (function) `headers/tls.h:174` `void hmac_sha256(const unsigned char *key, unsigned klen, const unsigned char *data, unsigned dlen, unsigned char...`
- `tls_prf` (function) `headers/tls.h:179` `void tls_prf(const unsigned char *secret, unsigned secret_len, const char *label, const unsigned char *seed...`
- `aes128_encrypt_block` (function) `headers/tls.h:184` `void aes128_encrypt_block(const unsigned char key[16], const unsigned char in[16], unsigned char out[16]);` -- void sha256_final(struct sha256_ctx *c, unsigned char out[32]); void sha256(const unsigned char *data, unsigned len...
- `aes128_gcm_seal` (function) `headers/tls.h:189` `int aes128_gcm_seal(const unsigned char key[16], const unsigned char salt[4], unsigned long long seq, const unsigned...` -- GCM.
- `aes128_gcm_open` (function) `headers/tls.h:197` `int aes128_gcm_open(const unsigned char key[16], const unsigned char salt[4], unsigned long long seq, const unsigned...` -- GCM.
- `aes128_gcm_seal_core` (function) `headers/tls.h:208` `int aes128_gcm_seal_core(const unsigned char key[16], const unsigned char nonce[12], const unsigned char *aad...` -- Core GCM with an arbitrary 12-byte nonce (the TLS API above is the 4-byte salt + 8-byte sequence special case).
- `aes128_gcm_open_core` (function) `headers/tls.h:213` `int aes128_gcm_open_core(const unsigned char key[16], const unsigned char nonce[12], const unsigned char *aad...`
- `p256_scalar_mult` (function) `headers/tls.h:222` `int p256_scalar_mult(const unsigned char scalar[32], const unsigned char qx[32], const unsigned char qy[32]...` -- secp256r1 / secp384r1: shared Jacobian point arithmetic over NIST * primes. curve: 0 = P-256, 1 = P-384.
- `p384_scalar_mult` (function) `headers/tls.h:225` `int p384_scalar_mult(const unsigned char scalar[48], const unsigned char qx[48], const unsigned char qy[48]...`
- `p256_ecdh` (function) `headers/tls.h:231` `int p256_ecdh(const unsigned char priv[32], const unsigned char peer_x[32], const unsigned char peer_y[32], unsigned...` -- ECDH shared secret: Z = priv * peer_pub (P-256).
- `p256_point_valid` (function) `headers/tls.h:236` `int p256_point_valid(const unsigned char x[32], const unsigned char y[32]);` -- ECDH shared secret: Z = priv * peer_pub (P-256).
- `p256_pub` (function) `headers/tls.h:237` `int p256_pub(const unsigned char priv[32], unsigned char x[32], unsigned char y[32]);`
- `p256_scalar_valid` (function) `headers/tls.h:239` `int p256_scalar_valid(const unsigned char scalar[32]);`
- `ecdsa_verify` (function) `headers/tls.h:243` `int ecdsa_verify(int curve, const unsigned char pub_x[], const unsigned char pub_y[], const unsigned char digest[]...` -- ECDSA verify over a SHA-256 or SHA-384 digest. curve: 0 = P-256, * 1 = P-384.
- `rsa_pkcs1_verify_sha256` (function) `headers/tls.h:249` `int rsa_pkcs1_verify_sha256(const unsigned char *n, unsigned n_len, const unsigned char *e, unsigned e_len, const...` -- RSA PKCS#1 v1.5 signature verify with SHA-256. modulus up to 4096 bits. * digest is the SHA-256 of the signed data.
- `rsa_pkcs1_verify_sha384` (function) `headers/tls.h:253` `int rsa_pkcs1_verify_sha384(const unsigned char *n, unsigned n_len, const unsigned char *e, unsigned e_len, const...`
- `tls_x509_parse_pubkey` (function) `headers/tls.h:261` `int tls_x509_parse_pubkey(const unsigned char *der, unsigned len, struct tls_pubkey *pk);` -- RSA PKCS#1 v1.5 signature verify with SHA-256. modulus up to 4096 bits. * digest is the SHA-256 of the signed data.
- `now` (function) `headers/tls.h:267` `* window against now (days since epoch). Returns 0 on success. */ int tls_x509_verify_chain(const unsigned char...`
- `tls_handshake` (function) `headers/tls.h:277` `int tls_handshake(int fd, const char *host);` -- Blocking TLS 1.2 handshake over an open TCP socket (net fd index). host is the SNI + certificate hostname.
- `tls_send` (function) `headers/tls.h:280` `int tls_send(int fd, const char *buf, int len);` -- Blocking TLS 1.2 handshake over an open TCP socket (net fd index). host is the SNI + certificate hostname.
- `tls_recv` (function) `headers/tls.h:284` `int tls_recv(int fd, char *buf, int len);` -- Receive decrypted application bytes.
- `tls_free_fd` (function) `headers/tls.h:293` `static inline void tls_free_fd(int fd)` -- Kernel built without the TLS engine (net/tls*.c unlinked): no session can ever exist, so the net.c close path needs...
- `tls_sys_handshake` (function) `headers/tls.h:297` `long tls_sys_handshake(long fd, long host);` -- Kernel built without the TLS engine (net/tls*.c unlinked): no session can ever exist, so the net.c close path needs...
- `tls_sys_send` (function) `headers/tls.h:298` `long tls_sys_send(long fd, long buf, long len);`
- `tls_sys_recv` (function) `headers/tls.h:299` `long tls_sys_recv(long fd, long buf, long len);`

## headers/tls_port.h
Depends on: `headers/kernel.h`, `headers/net.h`, `kernel/string.c`, `kernel/time.c`
Imported by: `net/tls.c`, `net/tls_crypto.c`, `net/tls_x509.c`, `progs/tls_u/tls_u_main.c`, `tls_test.c`
- `these` (function) `headers/tls_port.h:29` `* of these (tls_test.c). */ extern int tls_test_send(int fd, const char *buf, int len);`
- `tls_test_recv` (function) `headers/tls_port.h:31` `extern int tls_test_recv(int fd, char *buf, int len);`
- `tls_test_recv_timeout` (function) `headers/tls_port.h:32` `extern int tls_test_recv_timeout(int fd, char *buf, int len, unsigned long ms);`
- `tls_test_close` (function) `headers/tls_port.h:33` `extern void tls_test_close(int fd);`
- `tls_now_days` (function) `headers/tls_port.h:40` `static inline long tls_now_days(void)`
- `tls_random` (function) `headers/tls_port.h:44` `static inline void tls_random(unsigned char *out, unsigned len)`
- `sockets` (function) `headers/tls_port.h:62` `* sockets (glibc maps socket/connect/send/recv/poll onto the MiniOS * Linux ABI numbers the kernel implements);`
- `gettimeofday` (function) `headers/tls_port.h:64` `* gettimeofday(96) and entropy from /dev/urandom with a time/pid * fallback. Session slots are indexed by raw OS fd...`
- `tls_u_recv` (function) `headers/tls_port.h:82` `int tls_u_recv(int fd, char *buf, int len);`
- `tls_u_recv_timeout` (function) `headers/tls_port.h:83` `int tls_u_recv_timeout(int fd, char *buf, int len, unsigned long ms);`
- `tls_u_close` (function) `headers/tls_port.h:84` `void tls_u_close(int fd);`
- `syscall` (function) `headers/tls_port.h:95` `* the MiniOS DNS syscall (200, invoked sig-0-safe). 0 on success. */ int tls_u_resolve(const char *host, unsigned...`

## headers/vga_fb.h
Depends on: `headers/wm_notify.h`, `progs/minios_abi.h`
Imported by: `drivers/kbd.c`, `drivers/usbhid.c`, `kernel.c`, `kernel/console.c`, `kernel/console_in.c`, `kernel/exec.c`, `kernel/loader.c`, `kernel/minifetch.c`, `kernel/mm/cow.c`, `kernel/mm/paging.c`, `kernel/panic.c`, `kernel/sched.c`, `kernel/shell.c`, `kernel/spawn.c`, `kernel/syscalls.c`, `kernel/vga_cursor.c`, `kernel/vga_fb.c`, `kernel/vga_fx.c`, `progs/src/freedom_wl.c`
- `fb_bytes_per_pixel` (function) `headers/vga_fb.h:30` `int fb_bytes_per_pixel(void);` -- Bytes per framebuffer pixel derived from fb_bpp (1 for 8-bit, 3 for 24, * 4 for 32).
- `vga_fb_read_rgb` (function) `headers/vga_fb.h:34` `unsigned long vga_fb_read_rgb(int x, int y);` -- Read one desktop pixel as packed 0x00RRGGBB (palette-resolved in 8-bit mode, native in true color).
- `vga_fb_set_gfx_palette` (function) `headers/vga_fb.h:38` `void vga_fb_set_gfx_palette(const unsigned char *pal);` -- Store the graphics program's 768-byte palette (SYS_PALETTE).
- `vga_fb_boot_config` (function) `headers/vga_fb.h:40` `void vga_fb_boot_config(void);`
- `SYS_DOOM_FRAME` (function) `headers/vga_fb.h:44` `* and calls SYS_DOOM_FRAME (211) to have the kernel composite it onto the * desktop at its native resolution, so the...`
- `SYS_NK_FRAME` (function) `headers/vga_fb.h:63` `* SYS_NK_FRAME (220);`
- `vga_fb_blit_nk_window` (function) `headers/vga_fb.h:75` `void vga_fb_blit_nk_window(void);` -- RGB companion buffer (3 bytes per pixel, R,G,B order, NK_W x NK_H).
- `vga_fb_blit_nk_rgb_window` (function) `headers/vga_fb.h:76` `void vga_fb_blit_nk_rgb_window(void);`
- `below` (function) `headers/vga_fb.h:99` `* file below (800x600 RGB PNG on the ramdisk, produced by * tools/gen_desktop_pngs.py) is decoded once per boot via...`
- `vga_fb_init` (function) `headers/vga_fb.h:177` `void vga_fb_init(void);` -- A scrollback line can be up to the widest terminal (TERM_MAX_COLS), and a long logical line that wrapped across...
- `vga_fb_clear` (function) `headers/vga_fb.h:178` `void vga_fb_clear(void);`
- `vga_fb_pixel` (function) `headers/vga_fb.h:179` `void vga_fb_pixel(int x, int y, uint8_t color);`
- `vga_fb_rect` (function) `headers/vga_fb.h:180` `void vga_fb_rect(int x, int y, int w, int h, uint8_t color);`
- `vga_fb_pixel_rgb` (function) `headers/vga_fb.h:182` `void vga_fb_pixel_rgb(int x, int y, uint8_t r, uint8_t g, uint8_t b);` -- A scrollback line can be up to the widest terminal (TERM_MAX_COLS), and a long logical line that wrapped across...
- `vga_fb_rect_rgb` (function) `headers/vga_fb.h:183` `void vga_fb_rect_rgb(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b);`
- `vga_fb_char` (function) `headers/vga_fb.h:184` `void vga_fb_char(int col, int row, char c, uint8_t fg, uint8_t bg);`
- `vga_fb_str` (function) `headers/vga_fb.h:185` `void vga_fb_str(int col, int row, const char *s, uint8_t fg, uint8_t bg);`
- `vga_fb_putc_term` (function) `headers/vga_fb.h:186` `void vga_fb_putc_term(char c);`
- `vga_fb_puts_term` (function) `headers/vga_fb.h:187` `void vga_fb_puts_term(const char *s);`
- `term_clear` (function) `headers/vga_fb.h:188` `void term_clear(void);`
- `vga_fb_text_cursor` (function) `headers/vga_fb.h:189` `void vga_fb_text_cursor(int col);`
- `vga_fb_hide_text_cursor` (function) `headers/vga_fb.h:190` `void vga_fb_hide_text_cursor(void);`
- `fb_read_packed` (function) `headers/vga_fb.h:193` `unsigned long fb_read_packed(int x, int y);` -- Packed-pixel primitives (0x00RRGGBB): the cursor layer draws through * these so it never touches raw framebuffer...
- `fb_write_packed` (function) `headers/vga_fb.h:194` `void fb_write_packed(int x, int y, unsigned long rgb);`
- `vga_fb_draw_desktop` (function) `headers/vga_fb.h:195` `void vga_fb_draw_desktop(void);`
- `vga_fb_toggle_fullscreen` (function) `headers/vga_fb.h:196` `void vga_fb_toggle_fullscreen(void);`
- `vga_fb_move_terminal` (function) `headers/vga_fb.h:197` `void vga_fb_move_terminal(int dx, int dy);`
- `vga_fb_snap_window` (function) `headers/vga_fb.h:198` `void vga_fb_snap_window(int zone);`
- `vga_fb_resize` (function) `headers/vga_fb.h:199` `void vga_fb_resize(int dcols, int drows);`
- `vga_fb_reset_default` (function) `headers/vga_fb.h:200` `void vga_fb_reset_default(void);`
- `vga_fb_toggle_minimize` (function) `headers/vga_fb.h:201` `void vga_fb_toggle_minimize(void);`
- `vga_fb_is_minimized` (function) `headers/vga_fb.h:202` `int vga_fb_is_minimized(void);`
- `vga_fb_is_fullscreen` (function) `headers/vga_fb.h:203` `int vga_fb_is_fullscreen(void);`
- `vga_fb_gfx_set_fullscreen` (function) `headers/vga_fb.h:211` `int vga_fb_gfx_set_fullscreen(int on);` -- Graphics window view (headers/wm_gfxview.h owns the math).
- `vga_fb_gfx_set_hidden` (function) `headers/vga_fb.h:212` `int vga_fb_gfx_set_hidden(int hide);`
- `vga_fb_gfx_view_name` (function) `headers/vga_fb.h:213` `const char *vga_fb_gfx_view_name(void);`
- `vga_fb_gfx_origin` (function) `headers/vga_fb.h:214` `void vga_fb_gfx_origin(int *x, int *y);`
- `vga_fb_gfx_map_mouse` (function) `headers/vga_fb.h:215` `void vga_fb_gfx_map_mouse(int *x, int *y);`
- `fb_write_row_packed` (function) `headers/vga_fb.h:217` `void fb_write_row_packed(int x, int y, const unsigned int *src, int n);` -- Graphics window view (headers/wm_gfxview.h owns the math).
- `fb_read_row_packed` (function) `headers/vga_fb.h:218` `void fb_read_row_packed(int x, int y, unsigned int *dst, int n);`
- `vga_fb_close_active` (function) `headers/vga_fb.h:219` `int vga_fb_close_active(void);`
- `vga_fb_focus_next` (function) `headers/vga_fb.h:223` `void vga_fb_focus_next(void);` -- Multi-window manager: Alt-Tab focus cycle, Super-Tab tiling, second * terminal.
- `vga_fb_focus_id` (function) `headers/vga_fb.h:224` `int vga_fb_focus_id(int id);`
- `vga_fb_focus_get` (function) `headers/vga_fb.h:225` `int vga_fb_focus_get(void);`
- `vga_fb_focus_event` (function) `headers/vga_fb.h:228` `const wm_notify_event_t *vga_fb_focus_event(void);` -- Focus event bus (wm_notify.h): last move for serial-observable state, * plus programmatic reporting for focus moves...
- `vga_fb_focus_report` (function) `headers/vga_fb.h:229` `void vga_fb_focus_report(int before, int source);`
- `vga_fb_theme_name` (function) `headers/vga_fb.h:230` `int vga_fb_theme_name(char *dst, int cap);`
- `vga_fb_ps2_owner` (function) `headers/vga_fb.h:236` `int vga_fb_ps2_owner(int pid);` -- PS/2 ownership for pid: 1 when pid may consume the keyboard port.
- `vga_fb_nterms_get` (function) `headers/vga_fb.h:237` `int vga_fb_nterms_get(void);`
- `vga_fb_term_split` (function) `headers/vga_fb.h:238` `int vga_fb_term_split(void);`
- `vga_fb_term_close_focused` (function) `headers/vga_fb.h:239` `int vga_fb_term_close_focused(void);`
- `vga_fb_tile_all` (function) `headers/vga_fb.h:240` `void vga_fb_tile_all(void);`
- `vga_fb_layout_set` (function) `headers/vga_fb.h:241` `int vga_fb_layout_set(int mode);`
- `vga_fb_layout_cycle` (function) `headers/vga_fb.h:242` `void vga_fb_layout_cycle(void);`
- `vga_fb_layout_get` (function) `headers/vga_fb.h:243` `int vga_fb_layout_get(void);`
- `vga_fb_layout_name` (function) `headers/vga_fb.h:244` `const char *vga_fb_layout_name(void);`
- `vga_fb_list_windows` (function) `headers/vga_fb.h:245` `void vga_fb_list_windows(void);`
- `wm_close_pending` (function) `headers/vga_fb.h:246` `int wm_close_pending(void);`
- `wm_clear_close` (function) `headers/vga_fb.h:247` `void wm_clear_close(void);`
- `wm_gfx_mode_active` (function) `headers/vga_fb.h:248` `int wm_gfx_mode_active(void);`
- `vga_fb_mouse_tick` (function) `headers/vga_fb.h:249` `void vga_fb_mouse_tick(void);`
- `vga_fb_wait_tick` (function) `headers/vga_fb.h:253` `void vga_fb_wait_tick(void);` -- Desktop tick for a kernel wait loop (foreground process wait, mrun): runs vga_fb_mouse_tick at DESKTOP_TICK_INTERVAL...
- `vga_fb_mouse_init` (function) `headers/vga_fb.h:254` `void vga_fb_mouse_init(void);`
- `dock_bounce_counts` (function) `headers/vga_fb.h:257` `void dock_bounce_counts(unsigned long *kicks, unsigned long *paints);` -- Dock click bounce (Mac style): arm count and strip repaints while live, * for the serial-observable proof (`wm...
- `dock_click_count` (function) `headers/vga_fb.h:258` `void dock_click_count(unsigned long *edges);`
- `dock_pending_active` (function) `headers/vga_fb.h:259` `int dock_pending_active(void);`
- `pixels` (function) `headers/vga_fb.h:263` `* are heap buffers of packed pixels (fb_read_packed order), 0 on OOM or a * degenerate rect. A disabled effect or a...`
- `vga_fx_enabled` (function) `headers/vga_fb.h:267` `int vga_fx_enabled(void);`
- `vga_fx_snap_rect` (function) `headers/vga_fb.h:268` `unsigned int *vga_fx_snap_rect(int x, int y, int w, int h);`
- `vga_fx_restore_rect` (function) `headers/vga_fb.h:269` `void vga_fx_restore_rect(int x, int y, int w, int h, const unsigned int *buf);`
- `vga_fx_free` (function) `headers/vga_fb.h:270` `void vga_fx_free(unsigned int *buf);`
- `vga_fx_melt_rect` (function) `headers/vga_fb.h:271` `void vga_fx_melt_rect(int x, int y, int w, int h, const unsigned int *oldb, const unsigned int *newb);`
- `vga_fx_melt_from_black` (function) `headers/vga_fb.h:273` `void vga_fx_melt_from_black(int x, int y, int w, int h, const unsigned int *newb);`
- `vga_fb_set_gfx_mode` (function) `headers/vga_fb.h:284` `void vga_fb_set_gfx_mode(int on);` -- Graphics-mode pointer.

## headers/vga_fx.h
Imported by: `kernel/vga_fb.c`, `kernel/vga_fx.c`, `tests/test_fx.c`
- `vga_fx_rand` (function) `headers/vga_fx.h:30` `static inline unsigned long vga_fx_rand(unsigned long *s)` -- typedef struct { int step_px; int frame_ms; int max_delay; unsigned long seed; } vga_fx_config_t; /** Docstring...
- `vga_fx_init_cols` (function) `headers/vga_fx.h:47` `static inline int vga_fx_init_cols(const vga_fx_config_t *cfg, int *cols, int w)` -- Docstring: Seed consecutive column fronts with staggered delays.
- `vga_fx_advance` (function) `headers/vga_fx.h:71` `static inline int vga_fx_advance(const vga_fx_config_t *cfg, int *cols, int w, int h)` -- Docstring: Advance every column front one melt frame. * Returns 1 when every front reached the rect bottom, 0 otherwise.
- `vga_fx_front` (function) `headers/vga_fx.h:97` `static inline int vga_fx_front(int col_y, int h)` -- done = 0; } else if (cols[i] < h) { int dy = (cols[i] < 16) ? cols[i] + 1 : step; cols[i] += dy; if (cols[i] > h) {...
- `vga_fx_clamp_rect` (function) `headers/vga_fx.h:109` `static inline int vga_fx_clamp_rect(int *x, int *y, int *w, int *h, int fb_w, int fb_h)` -- /** Docstring: Rows [0, front) of one column already show the new frame. static inline int vga_fx_front(int col_y...

## headers/vma.h
Imported by: `headers/kernel.h`, `headers/sched.h`, `headers/spawn.h`, `kernel/spawn.c`, `tests/test_fault.c`, `tests/test_vma.c`, `tests/test_vma_bench.c`, `vma.c`
- `vma_tree_init` (function) `headers/vma.h:64` `void vma_tree_init(void);`
- `vma_tree_insert` (function) `headers/vma.h:65` `vma_node_t *vma_tree_insert(vma_node_t **root, unsigned long base, unsigned long len);`
- `vma_tree_find` (function) `headers/vma.h:66` `vma_node_t *vma_tree_find(vma_node_t *root, unsigned long base);`
- `vma_tree_find_containing` (function) `headers/vma.h:67` `vma_node_t *vma_tree_find_containing(vma_node_t *root, unsigned long va);`
- `vma_tree_delete` (function) `headers/vma.h:68` `int vma_tree_delete(vma_node_t **root, unsigned long base);`
- `vma_ctx_init` (function) `headers/vma.h:69` `void vma_ctx_init(vma_ctx_t *c, vma_node_t *pool);`
- `vma_ctx_bind` (function) `headers/vma.h:70` `void vma_ctx_bind(vma_ctx_t *c);`
- `vma_ctx_save` (function) `headers/vma.h:71` `void vma_ctx_save(vma_ctx_t *c);`
- `vma_view_save` (function) `headers/vma.h:86` `void vma_view_save(vma_view_t *v);`
- `vma_view_load` (function) `headers/vma.h:87` `void vma_view_load(const vma_view_t *v);`
- `vma_ctx_alloc` (function) `headers/vma.h:90` `vma_ctx_t *vma_ctx_alloc(void);` -- Heap-backed contexts live in sched.c (vma.c stays host-testable): * alloc returns a fresh context with a private...
- `vma_ctx_free` (function) `headers/vma.h:91` `void vma_ctx_free(vma_ctx_t *c);`

## headers/wm_events.h
Depends on: `headers/drivers/modifiers.h`
Imported by: `drivers/kbd.c`, `kernel/vga_fb.c`, `tests/test_wm.c`
- `wm_is_click_edge` (function) `headers/wm_events.h:52` `static inline int wm_is_click_edge(const wm_event_config_t *cfg, int prev_buttons, int curr_buttons)` -- int button; int wheel; } wm_event_t; /** Docstring: Centralized event translator configuration. typedef struct { int...
- `wm_is_release_edge` (function) `headers/wm_events.h:59` `static inline int wm_is_release_edge(const wm_event_config_t *cfg, int prev_buttons, int curr_but...` -- int wheel_step; } wm_event_config_t; /** Docstring: Default event configuration matching the PS/2 mouse path....
- `wm_translate_event` (function) `headers/wm_events.h:66` `static inline wm_event_t wm_translate_event(const wm_event_config_t *cfg, const wm_mouse_t *prev,...` -- static inline int wm_is_click_edge(const wm_event_config_t *cfg, int prev_buttons, int curr_buttons) { int mask =...
- `wm_event_suppresses_drag` (function) `headers/wm_events.h:104` `static inline int wm_event_suppresses_drag(const wm_event_t *evt)` -- return evt; } if (curr->wheel != 0) { evt.type = WM_EVT_SCROLL; return evt; } if (curr->x != prev->x || curr->y !=...
- `wm_combo_lookup` (function) `headers/wm_events.h:201` `static inline int wm_combo_lookup(int alt, int altgr, int sup, int e0, int sc, int path, int *zon...` -- {1, 0, 1, WM_SC_HOME, WM_PATH_COOKED, WM_COMBO_SNAP, WM_SNAP_TOP_LEFT}, {1, 0, 1, WM_SC_END, WM_PATH_COOKED...
- `wm_combo_lookup_mods` (function) `headers/wm_events.h:238` `static inline int wm_combo_lookup_mods(const modifier_state_t *st, int e0, int sc, int path, int ...` -- continue; } if (!(WM_COMBOS[i].paths & path)) { continue; } if (zone_out != 0) { zone_out = WM_COMBOS[i].zone; }...

## headers/wm_focus.h
Depends on: `headers/wm_window.h`
Imported by: `kernel/vga_fb.c`, `tests/test_wm.c`
- `wm_focus_selectable` (function) `headers/wm_focus.h:23` `static inline int wm_focus_selectable(const wm_focus_state_t *st, int id)` -- #ifndef WM_FOCUS_H #define WM_FOCUS_H #include "wm_window.h" /** Docstring: Focus state snapshot consumed by every...
- `wm_focus_next` (function) `headers/wm_focus.h:38` `static inline int wm_focus_next(const wm_focus_state_t *st)` -- { if (st == 0) { return 0; } if (id == WM_WINDOW_GFX_ID) { return st->gfx_active ?
- `wm_focus_set` (function) `headers/wm_focus.h:55` `static inline int wm_focus_set(const wm_focus_state_t *st, int id)` -- int i; if (st == 0) { return 0; } for (i = 0; i < 4; i++) { flat[i] = 0; } for (i = 0; i < st->nterms && i < 4; i++)...

## headers/wm_geom.h
Imported by: `headers/wm_window.h`, `kernel/vga_fb.c`, `tests/test_wm.c`
- `wm_rect_valid` (function) `headers/wm_geom.h:33` `static inline int wm_rect_valid(const wm_rect_t *r)` -- } wm_geom_config_t; /** Docstring: Default geometry matching the kernel 8x8 font layout. #define...
- `wm_rect_contains` (function) `headers/wm_geom.h:39` `static inline int wm_rect_contains(const wm_rect_t *r, int px, int py)` -- typedef struct { int x; int y; int w; int h; } wm_rect_t; /** Docstring: True when the rectangle can contain any...
- `wm_title_bar_rect` (function) `headers/wm_geom.h:48` `static inline wm_rect_t wm_title_bar_rect(const wm_geom_config_t *cfg, int px, int py, int w)` -- { return r != 0 && r->w > 0 && r->h > 0; } /** Docstring: True when point px,py lies inside rectangle r. static...
- `wm_content_rect` (function) `headers/wm_geom.h:59` `static inline wm_rect_t wm_content_rect(const wm_geom_config_t *cfg, int px, int py, int w, int h)` -- } /** Docstring: Title bar strip for a window at px,py with total width w. static inline wm_rect_t...
- `wm_scrollbar_rect` (function) `headers/wm_geom.h:71` `static inline wm_rect_t wm_scrollbar_rect(const wm_geom_config_t *cfg, int px, int py, int conten...` -- /** Docstring: Text content area below the title bar. static inline wm_rect_t wm_content_rect(const wm_geom_config_t...
- `wm_hit_title_bar` (function) `headers/wm_geom.h:84` `static inline int wm_hit_title_bar(const wm_geom_config_t *cfg, int wx, int wy, int w, int px, in...` -- /** Docstring: Scrollbar strip at the right edge of the content area. static inline wm_rect_t...
- `wm_clamp_point` (function) `headers/wm_geom.h:91` `static inline void wm_clamp_point(int *px, int *py, int fb_w, int fb_h)` -- r.y = py + th; r.w = sw; r.h = content_h > 0 ? content_h : 0; return r; } /** Docstring: True when point px,py hits...

## headers/wm_gfxview.h
Imported by: `kernel/vga_fb.c`, `tests/test_wm.c`
- `wm_gfxview_mode_name` (function) `headers/wm_gfxview.h:64` `static inline const char *wm_gfxview_mode_name(int mode)` -- Docstring: One computed view: frame (chrome plus content area), * title strip height (0 in fullscreen) and the...
- `wm_gfxview_dims_ok` (function) `headers/wm_gfxview.h:79` `static inline int wm_gfxview_dims_ok(int w, int h)` -- { switch (mode) { case WM_GFXVIEW_FLOAT: return "floating"; case WM_GFXVIEW_TILED: return "tiled"; case...
- `Downscale` (function) `headers/wm_gfxview.h:88` `* Downscale (fit below 1x) always takes the exact fit. Returns 1 on
 * success, 0 on degenerate i...`
- `wm_gfxview_clamp` (function) `headers/wm_gfxview.h:134` `static inline void wm_gfxview_clamp(wm_gfxview_rect_t *r, int fb_w, int fb_h)` -- Docstring: Clamp a rect inside the framebuffer by moving, then by * shrinking when it is larger than the screen.
- `wm_gfxview_place_content` (function) `headers/wm_gfxview.h:160` `static inline int wm_gfxview_place_content(const wm_gfxview_config_t *cfg, int sw, int sh,
      ...` -- r->x = fb_w - r->w; } if (r->y + r->h > fb_h) { r->y = fb_h - r->h; } if (r->x < 0) { r->x = 0; } if (r->y < 0) {...
- `wm_gfxview_map_point` (function) `headers/wm_gfxview.h:255` `static inline int wm_gfxview_map_point(const wm_gfxview_t *v, int sw, int sh,
                   ...` -- Docstring: Map a framebuffer point into back-buffer space.
- `wm_gfxview_ease` (function) `headers/wm_gfxview.h:291` `static inline long wm_gfxview_ease(int t, int n, long den)` -- Docstring: Ease-out cubic progress in [0, den] for step t of n.
- `wm_gfxview_lerp_rect` (function) `headers/wm_gfxview.h:313` `static inline int wm_gfxview_lerp_rect(const wm_gfxview_rect_t *a, const wm_gfxview_rect_t *b,
  ...` -- return 0; } inv = (long)(n - t); r = den - (den * inv * inv * inv) / ((long)n * (long)n * (long)n); if (r < 0) { r =...
- `wm_gfxview_rect_same` (function) `headers/wm_gfxview.h:336` `static inline int wm_gfxview_rect_same(const wm_gfxview_rect_t *a, const wm_gfxview_rect_t *b)` -- out->x = a->x + (int)(((long)(b->x - a->x) * p) / den); out->y = a->y + (int)(((long)(b->y - a->y) * p) / den)...


Next: [API_p6.md](API_p6.md)
