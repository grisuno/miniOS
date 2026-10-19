# API (page 7 of 21)
Previous: [API_p6.md](API_p6.md)

## kernel/printf.c
- `putc_buf` (function) `kernel/printf.c:7` `static void putc_buf(char c, void *ctx, int *written)`
- `putc_file` (function) `kernel/printf.c:13` `static void putc_file(char c, void *ctx, int *written)`
- `putc_str` (function) `kernel/printf.c:19` `static void putc_str(char c, void *ctx, int *written)`
- `emit_num` (function) `kernel/printf.c:26` `static void emit_num(void (*emit)(char, void *, int *), void *ctx, int *written,
                ...`
- `kformat` (function) `kernel/printf.c:44` `static void kformat(void (*emit)(char, void *, int *), void *ctx,
                    int *writte...`
- `kfprintf` (function) `kernel/printf.c:157` `int kfprintf(KFILE *f, const char *fmt, ...)`
- `ksprintf` (function) `kernel/printf.c:166` `int ksprintf(char *buf, const char *fmt, ...)`
- `putc_snbuf` (function) `kernel/printf.c:178` `static void putc_snbuf(char c, void *ctx, int *written)`
- `ksnprintf` (function) `kernel/printf.c:184` `int ksnprintf(char *buf, unsigned long size, const char *fmt, ...)`

## kernel/proc_sec.c
Depends on: `headers/proc_sec.h`, `headers/sanitize.h`, `headers/sched.h`, `headers/seccomp_bpf.h`, `headers/syscalls_proc.h`
- `pid_ok` (function) `kernel/proc_sec.c:74` `static int pid_ok(int pid)`
- `chain_put` (function) `kernel/proc_sec.c:78` `static void chain_put(sec_filter_t *f)`
- `proc_sec_inherit` (function) `kernel/proc_sec.c:87` `void proc_sec_inherit(int child, int parent)`
- `proc_sec_release` (function) `kernel/proc_sec.c:101` `void proc_sec_release(int pid)`
- `proc_sec_exec` (function) `kernel/proc_sec.c:115` `void proc_sec_exec(int pid)` -- execve keeps the filters and no_new_privs (Linux) and makes the fresh * image dumpable again.
- `proc_sec_set_exe` (function) `kernel/proc_sec.c:119` `void proc_sec_set_exe(int pid, const char *resolved)`
- `proc_sec_exe` (function) `kernel/proc_sec.c:125` `const char *proc_sec_exe(int pid)`
- `sec_kill` (function) `kernel/proc_sec.c:130` `static void sec_kill(long n, int whole_group)` -- if (pid_ok(pid)) sec_undumpable[pid] = 0; } void proc_sec_set_exe(int pid, const char *resolved) { if (!pid_ok(pid)...
- `proc_sec_filter` (function) `kernel/proc_sec.c:136` `int proc_sec_filter(long n, long a1, long a2, long a3, long a4, long a5, long a6, long *ret)`
- `sec_install` (function) `kernel/proc_sec.c:191` `static long sec_install(const sbpf_insn *prog, unsigned len, int strict)` -- Validate and push one program onto the caller's chain. strict skips the * no_new_privs requirement, as Linux strict...
- `sec_install_user` (function) `kernel/proc_sec.c:224` `static long sec_install_user(long ufprog)` -- return ERR_EINVAL; } kfree(scratch); node->ref = 1; node->len = len; node->depth = depth; node->prev = head...
- `proc_sec_prctl` (function) `kernel/proc_sec.c:235` `long proc_sec_prctl(long option, long a2, long a3, long a4, long a5)`
- `proc_sec_seccomp` (function) `kernel/proc_sec.c:290` `long proc_sec_seccomp(long op, long flags, long uargs)`

## kernel/rcu.c
Depends on: `headers/rcu.h`
- `rcu_me` (function) `kernel/rcu.c:13` `static cpu_t *rcu_me(void)`
- `rcu_me` (function) `kernel/rcu.c:17` `static cpu_t *rcu_me(void)` -- else
- `rcu_cpu_valid` (function) `kernel/rcu.c:40` `static int rcu_cpu_valid(int cpu)`
- `rcu_init` (function) `kernel/rcu.c:45` `void rcu_init(void)` -- unsigned long qs[MAX_CPUS]; unsigned long depth[MAX_CPUS]; rcu_slot_t pending[RCU_CB_MAX]; int pending_count...
- `rcu_read_lock` (function) `kernel/rcu.c:63` `void rcu_read_lock(void)` -- for (i = 0; i < MAX_CPUS; i++) { rcu_state.qs[i] = 0; rcu_state.depth[i] = 0; } for (i = 0; i < RCU_CB_MAX; i++) {...
- `rcu_read_unlock` (function) `kernel/rcu.c:75` `void rcu_read_unlock(void)` -- /** Docstring: Enter a read section on the current CPU.
- `rcu_deref` (function) `kernel/rcu.c:88` `void *rcu_deref(void *volatile *pp)` -- /** Docstring: Leave a read section.
- `rcu_publish` (function) `kernel/rcu.c:94` `void rcu_publish(void *volatile *pp, void *v)` -- return; spin_lock_irqsave(&rcu_state.lock, &flags); if (rcu_state.depth[cpu] > 0) rcu_state.depth[cpu]...
- `rcu_note_tick` (function) `kernel/rcu.c:126` `void rcu_note_tick(int cpu)` -- if (rcu_state.pending_count >= RCU_CB_MAX) { r = RCU_ERR_FULL; } else { rcu_slot_t *s =...
- `rcu_note_idle` (function) `kernel/rcu.c:137` `void rcu_note_idle(int cpu)` -- } /** Docstring: Record a quiescent state for cpu at the current epoch. void rcu_note_tick(int cpu) { irqflags_t...
- `rcu_poll` (function) `kernel/rcu.c:152` `void rcu_poll(void)` -- Docstring: Advance the epoch and run due callbacks.
- `expires` (function) `kernel/rcu.c:193` `* expires (ticks stalled, never a hang). No completion assert is
 * possible here by design: a re...`

## kernel/redirect.c
- `shell_report_exit` (function) `kernel/redirect.c:11` `void shell_report_exit(int code)`
- `shell_report` (function) `kernel/redirect.c:17` `void shell_report(const char *what, const char *detail)`
- `shell_take_redirect` (function) `kernel/redirect.c:25` `int shell_take_redirect(int *argc, char **argv, char **path, int *append_mode)`

## kernel/sched.c
Depends on: `headers/arch/x86/boot/bootdefs.h`, `headers/arch/x86/hal_io.h`, `headers/arch/x86/msr.h`, `headers/drivers/mouse.h`, `headers/drivers/xhci.h`, `headers/futex.h`, `headers/pcache.h`, `headers/pcm2.h`, `headers/percpu_rq.h`, `headers/proc_sec.h`, `headers/rcu.h`, `headers/sb16.h`, `headers/sched.h`, `headers/smp.h`, `headers/spawn.h`, `headers/sync.h`, `headers/tick.h`, `headers/tlb.h`, `headers/vga_fb.h`
- `sched_tick_audio` (function) `kernel/sched.c:26` `static void sched_tick_audio(void *ctx)` -- #include "rcu.h" #include "proc_sec.h" #include "bootdefs.h" #include "vga_fb.h" #include "sb16.h" #include "pcm2.h"...
- `sched_tick_desktop` (function) `kernel/sched.c:32` `static void sched_tick_desktop(void *ctx)` -- #include "tick.h" #include "arch/x86/hal_io.h" #include "arch/x86/msr.h" #include "drivers/mouse.h" #include...
- `sched_tick_usb` (function) `kernel/sched.c:43` `static void sched_tick_usb(void *ctx)` -- Docstring: USB tick adapter.
- `user_trampoline` (function) `kernel/sched.c:66` `extern void user_trampoline(void);`
- `fork_trampoline` (function) `kernel/sched.c:67` `extern void fork_trampoline(void);`
- `exec_enter` (function) `kernel/sched.c:72` `extern void exec_enter(unsigned long frame);`
- `read_cr3` (function) `kernel/sched.c:74` `static inline unsigned long read_cr3(void)`
- `PROC_KSTACK_OFF` (function) `kernel/sched.c:82` `* PROC_KSTACK_OFF (it cannot use C here). The asm derives both * immediates from headers/syscall_asm.h, so this...`
- `descriptor` (function) `kernel/sched.c:97` `* descriptor (two slots) per CPU past the 5 stage-2 entries. */ _Static_assert((5 + 2 * MAX_CPUS) * 8 ==...`
- `here` (function) `kernel/sched.c:128` `* smp_ap_idle_loop here (idle_proc ctx.rsp points at the top). */ static char ap_idle_stack[MAX_CPUS][4096]...`
- `kstack_paint` (function) `kernel/sched.c:171` `static void kstack_paint(uint64_t top, unsigned long size)`
- `kstack_usage` (function) `kernel/sched.c:180` `static int kstack_usage(uint64_t top, unsigned long size,
                        unsigned long *...` -- allocation rate only, never in the ISR path; the report is fail-closed * (a dead canary prints OVERFLOW, never a...
- `kstack_is_slot_end` (function) `kernel/sched.c:199` `static int kstack_is_slot_end(uint64_t v)` -- pid of a live process still standing on the stack slot ending at top (its kernel stack, or the stack its open...
- `kstack_of` (function) `kernel/sched.c:209` `static uint64_t kstack_of(int j)` -- The stack slot process j stands on: PCB.kstack between syscalls, the entry's saved top while a syscall is open (the...
- `kstack_owner` (function) `kernel/sched.c:216` `static int kstack_owner(uint64_t top)`
- `kstack_scan_serial` (function) `kernel/sched.c:231` `static void kstack_scan_serial(void)` -- Serial-only stack census for the exception dump: every pool slot in use, its owner and high-water mark, and "CANARY...
- `alloc_kstack` (function) `kernel/sched.c:262` `static uint64_t alloc_kstack(void)`
- `live` (function) `kernel/sched.c:286` `* every reap leaked its own stack and released a neighbour that could
 * still be live (two procs...`
- `MXCSR` (function) `kernel/sched.c:306` `* A fresh image is explicit zeros plus the default MXCSR (0x1F80, all
 * exceptions masked): fxsa...`
- `fpu_restore_from` (function) `kernel/sched.c:314` `static inline void fpu_restore_from(void *area)`
- `fpu_alloc_clean` (function) `kernel/sched.c:318` `static void *fpu_alloc_clean(void)`
- `fpu_free_proc` (function) `kernel/sched.c:336` `static void fpu_free_proc(proc_t *p)`
- `vma_ctx_alloc` (function) `kernel/sched.c:342` `vma_ctx_t *vma_ctx_alloc(void)` -- Per-process VMA contexts (vma.h contract; defined here so vma.c stays * host-testable).
- `vma_ctx_free` (function) `kernel/sched.c:352` `void vma_ctx_free(vma_ctx_t *c)`
- `copy` (function) `kernel/sched.c:362` `* copy (fail closed, fork refuses) instead of forging pointers. */
/* Name the link a fork could ...`
- `vma_ctx_copy` (function) `kernel/sched.c:371` `static vma_ctx_t *vma_ctx_copy(vma_ctx_t *src)`
- `vma_owned` (function) `kernel/sched.c:446` `static int vma_owned(proc_t *p)`
- `sched_lock` (function) `kernel/sched.c:452` `* hold sched_lock (+mm_lock at the swap sites);`
- `vma_save_proc` (function) `kernel/sched.c:454` `static void vma_save_proc(proc_t *p)` -- Rebind the global VMA view alongside the brk/mmap view.
- `vma_load_proc` (function) `kernel/sched.c:458` `static void vma_load_proc(proc_t *p)`
- `mm_owner` (function) `kernel/sched.c:472` `static proc_t *mm_owner(proc_t *p)` -- The process whose brk/mmap/VMA view an address space lives in: p itself unless p is a CLONE_VM thread, then the...
- `mm_view_enter` (function) `kernel/sched.c:494` `static void mm_view_enter(proc_t *nxt)` -- Make the globals describe nxt's address space before nxt runs, from any entry path (a switch, the timer, or the idle...
- `mm_view_claim_current` (function) `kernel/sched.c:513` `void mm_view_claim_current(void)` -- The running process installed a fresh view itself (execve, spawn * restore): it is the holder from now on.
- `kstack_report` (function) `kernel/sched.c:520` `void kstack_report(void)` -- Serial-observable stack health: per-proc high-water marks plus the legacy 32 KB syscall stack, ending in `kstack...
- `schedtop_report` (function) `kernel/sched.c:563` `void schedtop_report(void)` -- `schedtop` -- one screenful of scheduler state: uptime from the 100 Hz tick, per-CPU current pid, then one row per...
- `slot` (function) `kernel/sched.c:567` `* must not eat a quarter of a 16 KB slot (see the stack discipline * contract in CLAUDE.md). Fail-closed on OOM. */...`
- `sys_ticks` (function) `kernel/sched.c:627` `* sys_ticks (PIT 100 Hz on the BSP, broadcast as IPIs to APs);`
- `irqstat_report` (function) `kernel/sched.c:631` `void irqstat_report(void)` -- `irqstat` -- interrupt arrivals per source.
- `rtl_counters` (function) `kernel/sched.c:634` `extern void rtl_counters(unsigned int *tx_frames, unsigned int *rx_frames);`
- `rtl_present` (function) `kernel/sched.c:636` `extern int rtl_present(void);`
- `stub` (function) `kernel/sched.c:650` `* gdb stub (`make gdb`, then `target remote :1234` from the host). These
 * helpers are the seria...`
- `gdb_dump_report` (function) `kernel/sched.c:697` `void gdb_dump_report(unsigned long addr, unsigned long len)`
- `sched_idle_on_kernel_cr3` (function) `kernel/sched.c:723` `int sched_idle_on_kernel_cr3(int cpu)` -- 1 when cpu's idle context runs on the kernel tables (the `smp` builtin * reports it as idle_cr3=kernel|stale).
- `idt_set` (function) `kernel/sched.c:745` `static void idt_set(int vec, void (*h)(void))` -- Parked trap frames for preempted ring-3 contexts, one slot per pid.
- `idt_init` (function) `kernel/sched.c:756` `static void idt_init(void)`
- `pic_init` (function) `kernel/sched.c:772` `static void pic_init(void)` -- NMI is the TLB shootdown (kernel/mm/tlb.c): its own gate, its own * IST stack, never the trap-frame path....
- `IRQ4` (function) `kernel/sched.c:796` `* IRQ4 (COM1, UART IER stays 0 so it never fires) + * IRQ5 (Sound Blaster 16 DMA done). In the mask register a bit...`
- `pit_init` (function) `kernel/sched.c:807` `static void pit_init(void)` -- Master: unmask IRQ0 (timer) + IRQ1 (keyboard) + IRQ2 (cascade) + IRQ4 (COM1, UART IER stays 0 so it never fires) +...
- `pic_eoi` (function) `kernel/sched.c:814` `static void pic_eoi(int irq)`
- `tss_write_desc` (function) `kernel/sched.c:821` `static void tss_write_desc(int cpu)`
- `tss_init` (function) `kernel/sched.c:838` `static void tss_init(void)`
- `tss_init_ap` (function) `kernel/sched.c:870` `void tss_init_ap(int cpu)` -- Load this AP's task register.
- `context` (function) `kernel/sched.c:888` `* context (anything entered via k_exec_user) is inside a syscall
 * (entry swapped 0 in), and a c...`
- `point` (function) `kernel/sched.c:901` `* return address as the resume point ("continue the ISR"), which
 * required the stranded ISR fra...`
- `FSBASE` (function) `kernel/sched.c:913` `* for FSBASE (per-proc TLS): a thread preempted after arch_prctl * would otherwise resume with whatever base the...`
- `sched_next_locked` (function) `kernel/sched.c:930` `static int sched_next_locked(int start, int vm_only)` -- Fair-share scan with sched_lock HELD.
- `sched_set_nice` (function) `kernel/sched.c:948` `int sched_set_nice(int pid, int nice)` -- for (t = 0; t < MAX_PROCS; t++) { int cand = (start + 1 + t) % MAX_PROCS; unsigned long key; if (procs[cand].state...
- `seccomp_deny_one` (function) `kernel/sched.c:957` `int seccomp_deny_one(int pid, int n)` -- procs[best].state = PROC_RUNNING; procs[best].vruntime += SCHED_BASE_QUANTUM + (unsigned long)(procs[best].nice +...
- `seccomp_allow_one` (function) `kernel/sched.c:964` `int seccomp_allow_one(int pid, int n)`
- `seccomp_denied` (function) `kernel/sched.c:971` `int seccomp_denied(int pid, int n)`
- `smp_try_claim_hint` (function) `kernel/sched.c:980` `static int smp_try_claim_hint(int pid, int vm_only)` -- Claim one READY thread for this CPU's idle loop (the AP only claims CLONE_VM threads): marks it RUNNING under lock...
- `smp_claim_thread_v` (function) `kernel/sched.c:996` `static int smp_claim_thread_v(int vm_only)`
- `smp_ap_idle_loop` (function) `kernel/sched.c:1042` `void smp_ap_idle_loop(void)` -- AP idle loop: hlt until a CLONE_VM thread is ready, run it, repeat.
- `sched_ap_preempt` (function) `kernel/sched.c:1076` `static void sched_ap_preempt(trap_frame_t *frame)` -- AP timer preemption: time-slice the AP's current CLONE_VM thread with the next READY one.
- `smp_any_ap_idle` (function) `kernel/sched.c:1146` `static int smp_any_ap_idle(void)` -- True when some AP is idle.
- `rlimit_cpu_exceeded` (function) `kernel/sched.c:1182` `int rlimit_cpu_exceeded(int pid)`
- `isr_dispatch` (function) `kernel/sched.c:1203` `void isr_dispatch(int vector, trap_frame_t *frame)`
- `syscall` (function) `kernel/sched.c:1320` `* outgoing syscall (see sched_rearm_kgs). Without * this the next entry swapgs puts garbage under GS * and the pid...`
- `BSP` (function) `kernel/sched.c:1780` `* CPU believe it is the BSP (wrong per-CPU identity, two CPUs
         * running the shell contex...`
- `proc_get` (function) `kernel/sched.c:1821` `proc_t *proc_get(int pid)`
- `proc_create` (function) `kernel/sched.c:1827` `int proc_create(const char *name, int parent_pid)`
- `proc_spawn_elf_inner` (function) `kernel/sched.c:1945` `static int proc_spawn_elf_inner(const char *name, void *data, unsigned size,
                   i...` -- Spawn body: runs with the timer held off by the wrapper below, so page-table construction, heap allocation and the...
- `proc_spawn_elf` (function) `kernel/sched.c:2105` `int proc_spawn_elf(const char *name, void *data, unsigned size,
                   int argc, char...` -- Atomic spawn wrapper: the whole construction (page tables, image copy, stack, publish) runs with the timer held off...
- `schedule` (function) `kernel/sched.c:2147` `* that keeps schedule()'s own rbp runs the caller's frame accesses
 * (locals, leave/ret) on the ...`
- `schedule` (function) `kernel/sched.c:2154` `void schedule(void)`
- `PROC_SWITCHING` (function) `kernel/sched.c:2180` `* while the thread is still PROC_SWITCHING (never claimable), * then set the resume point and publish. A...`
- `yield` (function) `kernel/sched.c:2235` `void yield(void)`
- `returns` (function) `kernel/sched.c:2243` `* that returns (and the resumed thread returns with IF=1). */ __asm__ volatile("cli");`
- `do_exit` (function) `kernel/sched.c:2250` `void do_exit(int code)`
- `do_thread_spawn` (function) `kernel/sched.c:2314` `long do_thread_spawn(unsigned long fn, unsigned long stack,
                     unsigned long arg)` -- frame is ambiguous, this one starts cleanly at fn(arg) on the given stack:  child RIP = fn, child RSP = stack, child...
- `registers` (function) `kernel/sched.c:2345` `* registers (float args would need XMM inheritance, which the * arg-passing contract does not carry: fn takes one...`
- `itself` (function) `kernel/sched.c:2514` `* the shell itself (use mrun first), and a CLONE_VM thread forking
 * would duplicate shared stat...`
- `ctx_from_frame` (function) `kernel/sched.c:2537` `static void ctx_from_frame(ctx_regs_t *c, const syscall_frame_t *f)` -- Every register Linux preserves across a syscall, copied into a child's * PCB so it resumes after the syscall exactly...
- `fork_child_settid` (function) `kernel/sched.c:2555` `void fork_child_settid(void)` -- First code a fork or clone child runs (fork_trampoline, its own window live): store its tid at the...
- `do_fork` (function) `kernel/sched.c:2564` `long do_fork(void)`
- `fork_report` (function) `kernel/sched.c:2570` `static void fork_report(const char *what)` -- A fork that fails names the resource that ran out (failure paths * report): -ENOMEM alone cannot tell a heap leak...
- `do_fork_ex` (function) `kernel/sched.c:2577` `long do_fork_ex(uint64_t set_tid, uint64_t clear_tid)`
- `shares` (function) `kernel/sched.c:2595` `* thread on another CPU kept its writable translation and wrote straight * into frames the child now shares (the...`
- `MSR` (function) `kernel/sched.c:2633` `* in the MSR (the PCB field refreshes on switch-out) and its FPU * regs live in the CPU (the PCB image refreshes on...`
- `do_clone_thread` (function) `kernel/sched.c:2724` `static long do_clone_thread(unsigned long flags, unsigned long newsp,
                           ...` -- NPTL thread (clone with CLONE_VM|CLONE_SIGHAND|CLONE_THREAD): same window and fd view, resumes after the syscall on...
- `kill_group_threads_locked` (function) `kernel/sched.c:2838` `static void kill_group_threads_locked(int tgid, int except)` -- Zombify every live CLONE_THREAD member of a group except one pid.
- `do_group_exit` (function) `kernel/sched.c:2859` `void do_group_exit(int code)` -- Linux exit_group(2) and fatal-signal semantics, minus the caller's own exit (the caller follows with do_exit or...
- `aslr_mix` (function) `kernel/sched.c:2887` `static unsigned long aslr_mix(unsigned long salt)`
- `aslr_stack_bytes` (function) `kernel/sched.c:2896` `unsigned long aslr_stack_bytes(void)`
- `aslr_brk_pages` (function) `kernel/sched.c:2897` `unsigned long aslr_brk_pages(void)`
- `aslr_mmap_pages` (function) `kernel/sched.c:2898` `unsigned long aslr_mmap_pages(void)`
- `aslr_dyn_base` (function) `kernel/sched.c:2899` `unsigned long aslr_dyn_base(void)`
- `cli` (function) `kernel/sched.c:2908` `* cli (disk PIO must never run with the timer held off);`
- `adopt` (function) `kernel/sched.c:2922` `* adopt (armed by Linux O_CLOEXEC on open);`
- `do_execve` (function) `kernel/sched.c:2926` `long do_execve(char *kpath, int kargc, char **kargv)` -- Scope, fail-closed: the caller must be an isolated non-CLONE_VM ring-3 proc (pid 0 has no own window; a thread...
- `proc_running_anywhere` (function) `kernel/sched.c:3159` `static int proc_running_anywhere(int pid)` -- A zombie may still be finishing its exit tail (schedule()'s save and switch) on its own kernel stack on some CPU...
- `reap_autoreap_locked` (function) `kernel/sched.c:3168` `static void reap_autoreap_locked(int tgid)` -- Reclaim every auto-reaped (CLONE_THREAD) zombie, or only those of one * thread group when tgid >= 0.
- `alloc_pid_locked` (function) `kernel/sched.c:3180` `static int alloc_pid_locked(void)` -- First free pid slot after reclaiming finished threads, or -1.
- `group_threads_live_locked` (function) `kernel/sched.c:3192` `static int group_threads_live_locked(int tgid)` -- 1 while a thread of group tgid has not finished exiting: still alive, or a zombie some CPU is still running on.
- `waitpid_scan` (function) `kernel/sched.c:3203` `static int waitpid_scan(int pid, int *found)`
- `do_waitpid` (function) `kernel/sched.c:3224` `int do_waitpid(int pid)`
- `waitpid_has_child` (function) `kernel/sched.c:3241` `static int waitpid_has_child(int pid)` -- 1 when the caller has a waitable child matching pid (-1 = any): one that is not an auto-reaped thread, in any state...
- `do_waitpid_linux` (function) `kernel/sched.c:3255` `int do_waitpid_linux(int pid, int nohang, int *found)` -- Linux wait4 core (docs/spec/smp-sched.md): reap one matching child and report its pid through *found and its raw...
- `shell_reap_nb` (function) `kernel/sched.c:3272` `int shell_reap_nb(int *pid_out, int *code_out)` -- Reap one zombie child for `jobs`/auto-reap messages: returns 1 with * pid+code, or 0 when none is ready.
- `shell_reap_one` (function) `kernel/sched.c:3286` `int shell_reap_one(int pid, int *code_out)` -- Reap one specific zombie child (foreground wait).
- `shell_nchildren` (function) `kernel/sched.c:3298` `int shell_nchildren(void)` -- Reap one specific zombie child (foreground wait).
- `do_kill` (function) `kernel/sched.c:3324` `int do_kill(int pid)` -- True kill: the TARGET becomes a zombie for its parent to reap (its stack/tables free in do_waitpid, never here).
- `do_kill_code` (function) `kernel/sched.c:3330` `int do_kill_code(int pid, int code)` -- End pid with exit code (negative: killed by signal -code, as wait4 * reports it).
- `timer_tick` (function) `kernel/sched.c:3357` `void timer_tick(void)`
- `sched_init` (function) `kernel/sched.c:3362` `void sched_init(void)`
- `it` (function) `kernel/sched.c:3370` `* it (SPAWN/exec point proc 0 here transiently);`
- `park` (function) `kernel/sched.c:3422` `* an image its live FPU registers would be dropped by the preempt * park (the save path skips a null area). */...`
- `zeroed` (function) `kernel/sched.c:3433` `* still zeroed (kmemset happens inside idt_init) faults through a * null gate. Handlers for 32/33/44 are safe...`

## kernel/scrollback.c
- `vga_scroll` (function) `kernel/scrollback.c:4` `* Captured lazily from vga_scroll();`
- `sb_init` (function) `kernel/scrollback.c:17` `void sb_init(void)`
- `sb_capture_row0` (function) `kernel/scrollback.c:23` `void sb_capture_row0(void)`
- `sb_reset` (function) `kernel/scrollback.c:34` `void sb_reset(void)`
- `sb_get_count` (function) `kernel/scrollback.c:38` `int sb_get_count(void)`
- `sb_get_head` (function) `kernel/scrollback.c:39` `int sb_get_head(void)`
- `sb_get_char` (function) `kernel/scrollback.c:41` `char sb_get_char(int row, int col)`

## kernel/seccomp_bpf.c
Depends on: `headers/seccomp_bpf.h`
- `sbpf_opcode_ok` (function) `kernel/seccomp_bpf.c:17` `static int sbpf_opcode_ok(const sbpf_insn *in)` -- Freestanding: no libc, no kernel state; the same object links into the kernel and into the host test.  #include...
- `sbpf_check` (function) `kernel/seccomp_bpf.c:69` `int sbpf_check(const sbpf_insn *prog, unsigned len, unsigned short *scratch)`
- `sbpf_load_word` (function) `kernel/seccomp_bpf.c:114` `static unsigned int sbpf_load_word(const sbpf_data *d, unsigned off)` -- scratch[pc + 1u + in->k] &= (unsigned short)memvalid; } else { scratch[pc + 1u + in->jt] &= (unsigned...
- `sbpf_run` (function) `kernel/seccomp_bpf.c:120` `unsigned int sbpf_run(const sbpf_insn *prog, unsigned len, const sbpf_data *d)`
- `sbpf_action_rank` (function) `kernel/seccomp_bpf.c:194` `int sbpf_action_rank(unsigned int action)`

## kernel/serial.c
Depends on: `headers/sched.h`
- `serial_init` (function) `kernel/serial.c:20` `void serial_init(void)`
- `serial_tx_ready` (function) `kernel/serial.c:30` `static int serial_tx_ready(void)`
- `serial_rx_ready` (function) `kernel/serial.c:31` `static int serial_rx_ready(void)`
- `serial_putc` (function) `kernel/serial.c:33` `void serial_putc(char c)`
- `serial_e_count` (function) `kernel/serial.c:38` `unsigned long serial_e_count(void)`
- `serial_puts` (function) `kernel/serial.c:40` `void serial_puts(const char *s)`
- `serial_available` (function) `kernel/serial.c:42` `int serial_available(void)`
- `serial_getc` (function) `kernel/serial.c:44` `int serial_getc(void)`

## kernel/shell.c
Depends on: `headers/drivers/kbd.h`, `headers/drivers/nvme.h`, `headers/drivers/usbblk.h`, `headers/drivers/usbhid.h`, `headers/drivers/virtio_blk.h`, `headers/drivers/virtio_net.h`, `headers/drivers/xhci.h`, `headers/editor.h`, `headers/ext4.h`, `headers/fat32.h`, `headers/httpd.h`, `headers/kernel/console_in.h`, `headers/minifetch.h`, `headers/minifs.h`, `headers/net.h`, `headers/pcache.h`, `headers/pcm2.h`, `headers/pcspk.h`, `headers/percpu_rq.h`, `headers/proc_sec.h`, `headers/rtc.h`, `headers/sb16.h`, `headers/sched.h`, `headers/shell.h`, `headers/smp.h`, `headers/spawn.h`, `headers/tlb.h`, `headers/vga_fb.h`, `headers/wm_layout.h`, `headers/wm_notify.h`, `headers/zip.h`
- `shell_queue_launch` (function) `kernel/shell.c:87` `void shell_queue_launch(const char *cmd)` -- Queue a desktop-icon command to run after the current user program exits.
- `shell_readline_active` (function) `kernel/shell.c:115` `int shell_readline_active(void)`
- `shell_focus_park` (function) `kernel/shell.c:116` `void shell_focus_park(void)`
- `shell_focus_restore` (function) `kernel/shell.c:121` `void shell_focus_restore(void)`
- `shell_prompt` (function) `kernel/shell.c:148` `static void shell_prompt(void)`
- `shell_run_pipeline` (function) `kernel/shell.c:151` `static int shell_run_pipeline(char **argv, int argc, const char *redir_path, int redir_append, int redirected);`
- `shell_parse_vol` (function) `kernel/shell.c:158` `static int shell_parse_vol(const char *s, unsigned *out)` -- Strict decimal parse for the `vol` builtin: delegates the digit and overflow work to shell_parse_long and clamps the...
- `shell_readline_buf` (function) `kernel/shell.c:184` `void shell_readline_buf(char *buf, int size)` -- Read one line into buf (at most size-1 chars).
- `shell_name_base` (function) `kernel/shell.c:213` `static const char *shell_name_base(const char *path)` -- The component of a ramdisk path after the last '/', or the whole path when * there is no '/'.
- `shell_complete_tier` (function) `kernel/shell.c:238` `static int shell_complete_tier(const char *nm)` -- Runnable tier of a file name for first-word TAB completion: 0=.elf, 1=.cvm, 2=.o, 3=anything else.
- `shell_complete_replace` (function) `kernel/shell.c:250` `static void shell_complete_replace(char *buf, int size, int *pos,
                               ...`
- `shell_complete_minifs_arg` (function) `kernel/shell.c:271` `static void shell_complete_minifs_arg(const char *word, unsigned long wlen,
                     ...` -- Complete an argument word from MiniFS (the ramdisk loop at the call site covers the ramdisk half).
- `shell_readline` (function) `kernel/shell.c:338` `static void shell_readline(void)`
- `shell_hist_show` (function) `kernel/shell.c:346` `static void shell_hist_show(char *buf, int size, int *pos, const char *text)` -- Redraw the edit line: erase what is shown, then write `text` into buf and onto the console, leaving the text cursor...
- `shell_line_repaint` (function) `kernel/shell.c:368` `static void shell_line_repaint(char *buf, int size, int pos)` -- Repaint the edit line after a cursor move or mid-line edit: erase the whole visible line, rewrite buf, then back the...
- `shell_line_insert` (function) `kernel/shell.c:381` `static void shell_line_insert(char *buf, int size, int *pos, char c)` -- Insert character c into buf at `pos`, shifting the tail right.
- `shell_line_backspace` (function) `kernel/shell.c:390` `static void shell_line_backspace(char *buf, int size, int *pos)` -- Insert character c into buf at `pos`, shifting the tail right.
- `shell_line_delete` (function) `kernel/shell.c:398` `static void shell_line_delete(char *buf, int size, int *pos)` -- kmemmove(buf + *pos + 1, buf + *pos, (unsigned long)(len - *pos + 1)); buf[*pos] = c; (*pos)++; } /* Delete the...
- `shell_line_kill_front` (function) `kernel/shell.c:405` `static void shell_line_kill_front(char *buf, int size, int *pos)` -- int len = (int)kstrlen(buf); if (*pos <= 0) return; kmemmove(buf + *pos - 1, buf + *pos, (unsigned long)(len - *pos...
- `shell_line_kill_tail` (function) `kernel/shell.c:412` `static void shell_line_kill_tail(char *buf, int size, int *pos)` -- static void shell_line_delete(char *buf, int size, int *pos) { int len = (int)kstrlen(buf); if (*pos >= len) return...
- `shell_line_kill_word` (function) `kernel/shell.c:417` `static void shell_line_kill_word(char *buf, int size, int *pos)` -- /* Delete from the cursor to the start of the line (Ctrl+U). static void shell_line_kill_front(char *buf, int size...
- `shell_hist_newest_match` (function) `kernel/shell.c:429` `static int shell_hist_newest_match(const char *prefix, unsigned long plen)` -- Most recent history entry starting with `prefix` (of length plen) that is strictly longer than the prefix, or -1...
- `line` (function) `kernel/shell.c:446` `* to the live line (handled by the caller resetting shell_hist_idx). */
static void shell_hist_na...`
- `shell_readline_hist` (function) `kernel/shell.c:491` `static void shell_readline_hist(char *buf, int size)` -- Shell prompt readline: like shell_readline_buf plus command history.
- `root` (function) `kernel/shell.c:654` `* MiniFS root (where the big ELFs live under bare names), * and only the highest-priority non-empty tier is kept. An...`
- `shell_parse` (function) `kernel/shell.c:815` `int shell_parse(char *line, char **argv, int max_args)`
- `desktop_unflag` (function) `kernel/shell.c:837` `static void desktop_unflag(const char *name);`
- `shell_run_init` (function) `kernel/shell.c:844` `static void shell_run_init(void)` -- Startup commands from etc/init: one shell command per line, `#` comments and blank lines skipped.
- `shell_run` (function) `kernel/shell.c:883` `void shell_run(void)`
- `shell_load` (function) `kernel/shell.c:955` `static int shell_load(const char *fname, char *progname_out, void **entry_out)`
- `outw_port` (function) `kernel/shell.c:1018` `static inline void outw_port(unsigned short port, unsigned short val)`
- `shell_cmd_poweroff` (function) `kernel/shell.c:1024` `static void shell_cmd_poweroff(void)`
- `shell_run_dir_for` (function) `kernel/shell.c:1040` `static const ShellRunDir *shell_run_dir_for(const char *name)` -- The toolchain directory that owns `name`, chosen by suffix.
- `shell_file_is_real` (function) `kernel/shell.c:1058` `static int shell_file_is_real(const char *resolved)` -- Is `resolved` (already normalised against the cwd) a real ramdisk file?
- `shell_resolve_run` (function) `kernel/shell.c:1070` `static int shell_resolve_run(const char *name, char *out, unsigned cap)` -- Resolve `name` to a full ramdisk path suitable for running.
- `etrel_path_trusted` (function) `kernel/shell.c:1112` `static int etrel_path_trusted(const char *full)` -- ET_REL trust gate (boyscout fix for ring-0 .o without validation): relocatables execute as kernel extensions, so...
- `shell_run_elf_buf_path` (function) `kernel/shell.c:1152` `static int shell_run_elf_buf_path(const char *data, unsigned size, int argc,
                    ...` -- Run a raw ELF image (ET_REL, ET_EXEC or ET_DYN) already read into `data`. argv[0] is the program name the program sees.
- `shell_run_elf_file` (function) `kernel/shell.c:1185` `static int shell_run_elf_file(const char *full, int argc, char **argv)` -- Load the ramdisk file at `full` and run it as an ELF.
- `shell_run_elf_minifs` (function) `kernel/shell.c:1198` `static int shell_run_elf_minifs(const char *name, int argc, char **argv)` -- Load a Linux ELF from the MiniFS disk and run it (preserves the historical * `run` fallback when a name is not on...
- `shell_run_cvm` (function) `kernel/shell.c:1255` `static int shell_run_cvm(const char *full, int argc, char **argv)` -- Run a `.cvm` module at the resolved path `full`.
- `shell_run_file` (function) `kernel/shell.c:1291` `static int shell_run_file(const char *name, int argc, char **argv)` -- Run `name` as a ramdisk/MiniFS file: `.cvm` modules through the interpreter, ELF files by content through the...
- `window` (function) `kernel/shell.c:1328` `* window (proc_spawn_elf) and waits for all of them. The 100 Hz timer * preempts the BSP across the READY set, so...`
- `shell_read_elf_bytes` (function) `kernel/shell.c:1335` `static int shell_read_elf_bytes(const char *name, unsigned char **out,
                          ...` -- --- Multitask run (mrun): concurrent isolated ELFs ----  `mrun a.elf b.elf ...` loads each ET_EXEC/ET_DYN into its...
- `code` (function) `kernel/shell.c:1401` `* the last exit code (130 when interrupted). */
static int shell_wait_fg(int *pids, int n, int ki...`
- `shell_cmd_mrun` (function) `kernel/shell.c:1455` `static void shell_cmd_mrun(int argc, char **argv)`
- `shell_run_bg` (function) `kernel/shell.c:1503` `static void shell_run_bg(const char *name, int argc, char **argv)` -- `run <elf> &`: background a single isolated ELF (same spawn path as mrun).
- `this` (function) `kernel/shell.c:1533` `* boot into the tiled Wayland desktop: every NK app started after * this (paint, vedit, file, nuklear, doomedit...`
- `desktop_path` (function) `kernel/shell.c:1546` `static void desktop_path(const char *name, char *dst, unsigned cap)`
- `desktop_flag` (function) `kernel/shell.c:1555` `static void desktop_flag(const char *name)`
- `desktop_flag_on` (function) `kernel/shell.c:1565` `static int desktop_flag_on(const char *name)`
- `flows` (function) `kernel/shell.c:1579` `* and external flows (make wl) set it themselves. */
static void desktop_unflag(const char *name)`
- `desktop_srv_alive` (function) `kernel/shell.c:1587` `static int desktop_srv_alive(void)`
- `shell_cmd_desktop` (function) `kernel/shell.c:1603` `static void shell_cmd_desktop(int argc, char **argv)`
- `shell_run_any` (function) `kernel/shell.c:1667` `int shell_run_any(const char *name, int argc, char **argv)` -- Unified dispatcher used by `run` and by bare commands: a registered program wins, then the runnable-file resolver....
- `context` (function) `kernel/shell.c:1694` `* ISR context (which corrupts the running program's state) or * nesting a second foreground run inside the wait. */...`
- `gfx_parse_int` (function) `kernel/shell.c:1740` `static int gfx_parse_int(const char *s, int *out)` -- --- Graphics debugging (`gfx` builtin) ----  The serial console is the observability surface the BDD suite drives...
- `gfx_read_palette` (function) `kernel/shell.c:1760` `static void gfx_read_palette(unsigned char pal[768])` -- Read the current 256-entry VGA DAC palette (3x6-bit per entry, read at 8-bit precision by the kernel's normalisation).
- `shell_cmd_gfx` (function) `kernel/shell.c:1767` `static void shell_cmd_gfx(int argc, char **argv)`
- `shell_cmd_wm` (function) `kernel/shell.c:1919` `static void shell_cmd_wm(int argc, char **argv)` -- `wm <op>` — window-manager operations, exposed as a shell builtin so the tiling-WM behaviour is observable and...
- `tree` (function) `kernel/shell.c:2054` `* tree (mmap-heavy jobs stay best-effort), legacy blocking `run` ignores
 * Ctrl+C (it never poll...`
- `shell_cmd_jobs` (function) `kernel/shell.c:2067` `static void shell_cmd_jobs(void)`
- `shell_has_child` (function) `kernel/shell.c:2096` `static int shell_has_child(int pid)` -- Live-child check for one pid: a slot that is neither FREE nor reparented still belongs to this shell.
- `shell_cmd_wait` (function) `kernel/shell.c:2106` `static void shell_cmd_wait(int argc, char **argv)`
- `shell_cmd_kill` (function) `kernel/shell.c:2141` `static void shell_cmd_kill(int argc, char **argv)`
- `shell_cmd_mem` (function) `kernel/shell.c:2164` `static void shell_cmd_mem(void)` -- `mem` — memory and disk pressure in one screenful: kernel heap use (dlmalloc), ramdisk use versus its cap, MiniFS...
- `VMA` (function) `kernel/shell.c:2197` `* plus the live VMA (mmap) tree. The walk is bounded (64-deep explicit
 * stack, 128 regions prin...`
- `to` (function) `kernel/shell.c:2270` `* actually trap to (brk/mmap/munmap/mprotect) and says so up front. */
static void shell_cmd_trac...`
- `shell_parse_u64` (function) `kernel/shell.c:2339` `static int shell_parse_u64(const char *s, unsigned long *out)` -- Strict unsigned parse for debugger/inspector operands: `0x`-prefixed hex or plain decimal, no signs, no trailing...
- `shell_parse_long` (function) `kernel/shell.c:2355` `int shell_parse_long(const char *s, long *out)` -- Strict signed decimal twin of shell_parse_u64: optional sign, at least one digit, whole string consumed, overflow...
- `shell_parse_pid` (function) `kernel/shell.c:2376` `int shell_parse_pid(const char *s, int min_pid, int *out)` -- Bounded pid parse shared by wait/kill/vmmap: one range check instead of three open-coded copies. min_pid is 1 for...
- `shell_cmd_gdb` (function) `kernel/shell.c:2391` `static void shell_cmd_gdb(int argc, char **argv)` -- `gdb <op>` -- in-OS inspector half of the debugger story.
- `shell_cmd_hash` (function) `kernel/shell.c:2434` `static void shell_cmd_hash(int argc, char **argv)` -- `hash <file>` — XXH64 (64-bit, seed 0) of a ramdisk/MiniFS file, streamed in bounded chunks so a large MiniFS file...
- `shell_resolve_arg` (function) `kernel/shell.c:2453` `static int shell_resolve_arg(const char *cmd, const char *arg,
                             const...` -- Docstring: Resolve `arg` against the cwd into `out` (`RAMDISK_FNAME_LEN` bytes); on failure print `<cmd>: <arg>...
- `shell_httpd_one` (function) `kernel/shell.c:2559` `static void shell_httpd_one(int child, const char *root)` -- Serve one accepted connection: read one request, map GET path onto the VFS mounts under root, stream head + body, close.
- `shell_httpd_serve` (function) `kernel/shell.c:2644` `static void shell_httpd_serve(unsigned short port, const char *root,
        int max_conn)` -- Accept loop: one connection at a time, Ctrl+C quits.
- `shell_cross_ls` (function) `kernel/shell.c:2811` `static void shell_cross_ls(const char *drv, const char *imgarg,
                           const ...` -- List one directory from a cross-filesystem VFS driver (fat:, ext4:) to the console: same "drv:/img:path" addressing...
- `shell_cross_cat` (function) `kernel/shell.c:2852` `static void shell_cross_cat(const char *drv, const char *imgarg,
                            cons...` -- Stream one file from a cross-filesystem VFS driver (fat:, ext4:) to the console: "drv:/img:path" per open (the...
- `shell_exec_builtin` (function) `kernel/shell.c:2894` `void shell_exec_builtin(int argc, char **argv)`
- `terminal` (function) `kernel/shell.c:2969` `* sequence clears serial consoles and is swallowed without * garbage by the framebuffer terminal (vedit pattern). */...`
- `driver` (function) `kernel/shell.c:3312` `* stream through the fat: VFS driver ("img:fatpath" per open,
     * registered at boot beside me...`
- `frame` (function) `kernel/shell.c:3706` `* not live in this frame (stack discipline, CLAUDE.md). */ struct ps_row *snap = (struct ps_row...`
- `stdout` (function) `kernel/shell.c:4074` `* the pipe exactly like stdout (`2>` is an alias of `>`). * Per-stage `exit code:` lines report to the console...`
- `shell_is_pipe_tok` (function) `kernel/shell.c:4086` `static int shell_is_pipe_tok(const char *a)`
- `shell_run_stage` (function) `kernel/shell.c:4125` `static char *shell_run_stage(char **sargv, int sargc,
        const char *input, unsigned long in...` -- Run one pipeline stage with stdin/out doors installed. input may be 0 (first stage reads the live console).

## kernel/spawn.c
Depends on: `headers/arch/x86/msr.h`, `headers/arena.h`, `headers/minifs.h`, `headers/sched.h`, `headers/spawn.h`, `headers/vga_fb.h`, `headers/vma.h`
- `spawn_backup` (function) `kernel/spawn.c:11` `int spawn_backup(spawn_ctx_t *ctx)` -- #include "kernel.h" #include "sched.h" #include "vma.h" #include "spawn.h" #include "arena.h" #include "minifs.h"...
- `spawn_restore` (function) `kernel/spawn.c:38` `void spawn_restore(spawn_ctx_t *ctx)` -- if (!ctx->pool_copy) return 0; for (i = 0; i < vma_pool_n; i++) ctx->pool_copy[i] = vma_pool[i]; } ctx->live_root =...
- `spawn_free_argv` (function) `kernel/spawn.c:87` `void spawn_free_argv(char **kargv, int argc)` -- Docstring: Release a copy produced by spawn_copy_argv.
- `spawn_copy_argv` (function) `kernel/spawn.c:99` `char **spawn_copy_argv(int argc, const char **uargv)` -- Docstring: Copy user argv into kernel memory, zero terminated.
- `spawn_validate_argv` (function) `kernel/spawn.c:143` `int spawn_validate_argv(int argc, const char **uargv)` -- slen = (unsigned long)kstrlen(uargv[i]) + 1; dst = (char *)arena_alloc(&a, (size_t)slen, 1); if (!dst) {...
- `spawn_load_image` (function) `kernel/spawn.c:161` `unsigned char *spawn_load_image(const char *resolved, unsigned *size_out)` -- if (!user_range_ok((unsigned long)uargv, (unsigned long)(argc + 1) * sizeof(char *))) return 0; for (i = 0; i <...
- `spawn_run_rel` (function) `kernel/spawn.c:196` `static int spawn_run_rel(const char *resolved, const char *redirect,
                         uns...` -- MiniFSInode mi; if (minifs_stat(ino, &mi) >= 0 && mi.size > 0) { data_size = mi.size; data = (unsigned char...
- `spawn_run_exec` (function) `kernel/spawn.c:222` `static int spawn_run_exec(const char *resolved, const char *redirect,
                           ...` -- return EFAULT; } entry = elf_load((void *)data, data_size, &base); if (redirect && redirect[0]) did_redirect =...
- `spawn_execute` (function) `kernel/spawn.c:268` `int spawn_execute(const char *resolved, const char *redirect,
                  unsigned char *da...` -- do_kill(pid); do_waitpid(pid); rc = 130; break; } yield(); } } if (did_redirect && redirect_commit(redirect, 0) !=...

## kernel/string.c
Imported by: `headers/leakcheck.h`, `headers/tls_port.h`, `progs/doomedit/doomedit.c`, `progs/doomgeneric/d_iwad.c`, `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomgeneric_minios.c`, `progs/doomgeneric/doomgeneric_soso.c`, `progs/doomgeneric/doomgeneric_sosox.c`, `progs/doomgeneric/doomgeneric_xlib.c`, `progs/doomgeneric/f_wipe.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/gusconf.c`, `progs/doomgeneric/i_endoom.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_joystick.c`, `progs/doomgeneric/i_minios_sound.c`, `progs/doomgeneric/i_scale.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/m_argv.c`, `progs/doomgeneric/m_cheat.c`, `progs/doomgeneric/m_config.c`, `progs/doomgeneric/m_misc.c`, `progs/doomgeneric/memio.c`, `progs/doomgeneric/sha1.c`, `progs/doomgeneric/statdump.c`, `progs/doomgeneric/v_video.c`, `progs/doomgeneric/w_checksum.c`, `progs/doomgeneric/w_wad.c`, `progs/file/file.c`, `progs/file/file_assoc.h`, `progs/freedomui/freedomui_minios.c`, `progs/freedomui/media_unavailable.c`, `progs/freedomui/platform_minios.c`, `progs/freedomui/ps2_keymap.c`, `progs/lisp/lisp.c`, `progs/lua/lua_main.c`, `progs/minicraft/minicraft.c`, `progs/nuklear/cvm_emit.c`, `progs/nuklear/node_editor.c`, `progs/nuklear/nuklear_minios.c`, `progs/nuklear/nuklear_theme.c`, `progs/paint/paint.c`, `progs/piano/piano.c`, `progs/pokemon/platform_minios.c`, `progs/quake2generic/q2generic_minios.c`, `progs/quake2generic/snddma_minios.c`, `progs/src/apsse.c`, `progs/src/freedom.c`, `progs/src/freedom_wl.c`, `progs/src/lxabi.c`, `progs/src/lxnet.c`, `progs/src/lxsecc.c`, `progs/src/lxtls.c`, `progs/src/opl3.c`, `progs/src/pip.c`, `progs/tls_u/tls_u_main.c`, `progs/tls_u/tls_u_port.c`, `progs/topogpt3/topogpt3.c`, `progs/vedit/vedit.c`, `progs/wl/wl_pixbuf.h`, `progs/wl/wlcomp.c`, `tests/stubs/kernel.h`, `tests/test_arena.c`, `tests/test_driver.c`, `tests/test_ext4.c`, `tests/test_fat32.c`, `tests/test_fault.c`, `tests/test_file_assoc.c`, `tests/test_freedomui.c`, `tests/test_httpd.c`, `tests/test_ldso.c`, `tests/test_leakcheck.c`, `tests/test_minios_png.c`, `tests/test_paint.c`, `tests/test_pcache.c`, `tests/test_pcm.c`, `tests/test_ps2_keymap.c`, `tests/test_sanitize.c`, `tests/test_seccomp_bpf.c`, `tests/test_select_map.c`, `tests/test_sign.c`, `tests/test_theme.c`, `tests/test_usbhid.c`, `tests/test_vedit_build.c`, `tests/test_wl.c`, `tests/test_xhci.c`, `tls_test.c`
- `kstrlen` (function) `kernel/string.c:17` `unsigned long kstrlen(const char *s)`
- `kstrcpy` (function) `kernel/string.c:23` `char *kstrcpy(char *dst, const char *src)`
- `kstrncpy` (function) `kernel/string.c:29` `char *kstrncpy(char *dst, const char *src, unsigned long n)`
- `kstrncat` (function) `kernel/string.c:35` `char *kstrncat(char *dst, const char *src, unsigned long n)`
- `kstrcmp` (function) `kernel/string.c:43` `int kstrcmp(const char *a, const char *b)`
- `kstrncmp` (function) `kernel/string.c:48` `int kstrncmp(const char *a, const char *b, unsigned long n)`
- `kstrchr` (function) `kernel/string.c:53` `char *kstrchr(const char *s, int c)`
- `kstrstr` (function) `kernel/string.c:58` `char *kstrstr(const char *hay, const char *ndl)`
- `kmemcpy` (function) `kernel/string.c:68` `void *kmemcpy(void *dst, const void *src, unsigned long n)`
- `kmemset` (function) `kernel/string.c:75` `void *kmemset(void *dst, int c, unsigned long n)`
- `kmemcmp` (function) `kernel/string.c:81` `int kmemcmp(const void *a, const void *b, unsigned long n)`
- `kmemmove` (function) `kernel/string.c:87` `void *kmemmove(void *dst, const void *src, unsigned long n)`
- `katol` (function) `kernel/string.c:95` `long katol(const char *s)`

## kernel/symtab.c
- `k_register_symbol` (function) `kernel/symtab.c:10` `void k_register_symbol(const char *name, void *addr)`
- `ksym_resolve` (function) `kernel/symtab.c:18` `void *ksym_resolve(const char *name)`
- `kprog_slot` (function) `kernel/symtab.c:34` `KProg *kprog_slot(const char *name)`
- `kprog_lookup` (function) `kernel/symtab.c:42` `KProg *kprog_lookup(const char *name)`
- `k_register_program` (function) `kernel/symtab.c:49` `void k_register_program(const char *name, prog_entry_t entry)`
- `k_register_process` (function) `kernel/symtab.c:57` `void k_register_process(const char *name, void *proc_entry)`
- `k_spawn` (function) `kernel/symtab.c:65` `int k_spawn(const char *name, int argc, char **argv)`

## kernel/sync.c
Depends on: `headers/sync.h`
- `wq_init` (function) `kernel/sync.c:27` `void wq_init(wait_queue_t *q)`
- `sleep_on` (function) `kernel/sync.c:33` `void sleep_on(wait_queue_t *q)`
- `wake_up` (function) `kernel/sync.c:54` `int wake_up(wait_queue_t *q)`
- `wake_up_all` (function) `kernel/sync.c:70` `int wake_up_all(wait_queue_t *q)`
- `mutex_init` (function) `kernel/sync.c:76` `void mutex_init(mutex_t *m)`
- `pi_valid` (function) `kernel/sync.c:93` `static int pi_valid(int pid)`
- `pi_set_base` (function) `kernel/sync.c:99` `void pi_set_base(int pid, int prio)`
- `pi_get_eff` (function) `kernel/sync.c:108` `int pi_get_eff(int pid)`
- `pi_recompute` (function) `kernel/sync.c:113` `static void pi_recompute(int pid)`
- `pi_boost` (function) `kernel/sync.c:124` `static void pi_boost(int waiter, int owner)`
- `mutex_lock` (function) `kernel/sync.c:150` `void mutex_lock(mutex_t *m)`
- `mutex_trylock` (function) `kernel/sync.c:170` `int mutex_trylock(mutex_t *m)`
- `mutex_unlock` (function) `kernel/sync.c:186` `void mutex_unlock(mutex_t *m)`
- `sem_init` (function) `kernel/sync.c:207` `void sem_init(sem_t *s, int value)`
- `sem_wait` (function) `kernel/sync.c:213` `void sem_wait(sem_t *s)`
- `sem_post` (function) `kernel/sync.c:227` `void sem_post(sem_t *s)`
- `cond_init` (function) `kernel/sync.c:235` `void cond_init(cond_t *c)`
- `cond_wait` (function) `kernel/sync.c:239` `void cond_wait(cond_t *c, mutex_t *m)`
- `cond_signal` (function) `kernel/sync.c:245` `void cond_signal(cond_t *c)`
- `cond_broadcast` (function) `kernel/sync.c:249` `void cond_broadcast(cond_t *c)`
- `rwlock_init` (function) `kernel/sync.c:253` `void rwlock_init(rwlock_t *rw)`
- `rwlock_read_lock` (function) `kernel/sync.c:260` `void rwlock_read_lock(rwlock_t *rw)`
- `rwlock_read_unlock` (function) `kernel/sync.c:274` `void rwlock_read_unlock(rwlock_t *rw)`
- `rwlock_write_lock` (function) `kernel/sync.c:283` `void rwlock_write_lock(rwlock_t *rw)`
- `rwlock_write_unlock` (function) `kernel/sync.c:297` `void rwlock_write_unlock(rwlock_t *rw)`


Next: [API_p8.md](API_p8.md)
