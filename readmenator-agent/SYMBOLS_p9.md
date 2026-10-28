# Symbols (page 9 of 27)
Previous: [SYMBOLS_p8.md](SYMBOLS_p8.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `rcu_me` | function | `kernel/rcu.c:13` | `static cpu_t *rcu_me(void)` |
| `rcu_me` | function | `kernel/rcu.c:17` | `static cpu_t *rcu_me(void)` |
| `rcu_note_idle` | function | `kernel/rcu.c:137` | `void rcu_note_idle(int cpu)` |
| `rcu_note_tick` | function | `kernel/rcu.c:126` | `void rcu_note_tick(int cpu)` |
| `rcu_poll` | function | `kernel/rcu.c:152` | `void rcu_poll(void)` |
| `rcu_publish` | function | `kernel/rcu.c:94` | `void rcu_publish(void *volatile *pp, void *v)` |
| `rcu_read_lock` | function | `kernel/rcu.c:63` | `void rcu_read_lock(void)` |
| `rcu_read_unlock` | function | `kernel/rcu.c:75` | `void rcu_read_unlock(void)` |
| `rcu_slot_t` | struct | `kernel/rcu.c:22` | `` |
| `rcu_state_t` | struct | `kernel/rcu.c:28` | `` |
| `shell_report` | function | `kernel/redirect.c:17` | `void shell_report(const char *what, const char *detail)` |
| `shell_report_exit` | function | `kernel/redirect.c:11` | `void shell_report_exit(int code)` |
| `shell_take_redirect` | function | `kernel/redirect.c:25` | `int shell_take_redirect(int *argc, char **argv, char **path, int *append_mode)` |
| `BSP` | function | `kernel/sched.c:1780` | `* CPU believe it is the BSP (wrong per-CPU identity, two CPUs          * running the shell contex...` |
| `FSBASE` | function | `kernel/sched.c:913` | `* for FSBASE (per-proc TLS): a thread preempted after arch_prctl * would otherwise resume with whatever base the...` |
| `IRQ4` | function | `kernel/sched.c:796` | `* IRQ4 (COM1, UART IER stays 0 so it never fires) + * IRQ5 (Sound Blaster 16 DMA done). In the mask register a bit...` |
| `KSTACK_CANARY` | macro | `kernel/sched.c:169` | `#define KSTACK_CANARY` |
| `KSTACK_PAINT` | macro | `kernel/sched.c:168` | `#define KSTACK_PAINT` |
| `KSTACK_SZ` | macro | `kernel/sched.c:155` | `#define KSTACK_SZ` |
| `MSR` | function | `kernel/sched.c:2633` | `* in the MSR (the PCB field refreshes on switch-out) and its FPU * regs live in the CPU (the PCB image refreshes on...` |
| `MXCSR` | function | `kernel/sched.c:306` | `* A fresh image is explicit zeros plus the default MXCSR (0x1F80, all  * exceptions masked): fxsa...` |
| `MY_SYS_KSTK_TOP` | macro | `kernel/sched.c:53` | `#define MY_SYS_KSTK_TOP` |
| `MY_USER_LOAD_BASE` | macro | `kernel/sched.c:55` | `#define MY_USER_LOAD_BASE` |
| `MY_USER_STACK_TOP` | macro | `kernel/sched.c:54` | `#define MY_USER_STACK_TOP` |
| `NMI_IST_SLOT` | macro | `kernel/sched.c:125` | `#define NMI_IST_SLOT` |
| `NMI_IST_STACK_SZ` | macro | `kernel/sched.c:123` | `#define NMI_IST_STACK_SZ` |
| `NMI_VECTOR` | macro | `kernel/sched.c:124` | `#define NMI_VECTOR` |
| `PROC_KSTACK_OFF` | function | `kernel/sched.c:82` | `* PROC_KSTACK_OFF (it cannot use C here). The asm derives both * immediates from headers/syscall_asm.h, so this...` |
| `PROC_SWITCHING` | function | `kernel/sched.c:2180` | `* while the thread is still PROC_SWITCHING (never claimable), * then set the resume point and publish. A...` |
| `__attribute__` | function | `kernel/sched.c:109` | `typedef struct __attribute__((packed))` |
| `__attribute__` | function | `kernel/sched.c:143` | `typedef struct __attribute__((packed))` |
| `adopt` | function | `kernel/sched.c:2922` | `* adopt (armed by Linux O_CLOEXEC on open);` |
| `alloc_kstack` | function | `kernel/sched.c:262` | `static uint64_t alloc_kstack(void)` |
| `alloc_pid_locked` | function | `kernel/sched.c:3180` | `static int alloc_pid_locked(void)` |
| `aslr_brk_pages` | function | `kernel/sched.c:2897` | `unsigned long aslr_brk_pages(void)` |
| `aslr_dyn_base` | function | `kernel/sched.c:2899` | `unsigned long aslr_dyn_base(void)` |
| `aslr_mix` | function | `kernel/sched.c:2887` | `static unsigned long aslr_mix(unsigned long salt)` |
| `aslr_mmap_pages` | function | `kernel/sched.c:2898` | `unsigned long aslr_mmap_pages(void)` |
| `aslr_stack_bytes` | function | `kernel/sched.c:2896` | `unsigned long aslr_stack_bytes(void)` |
| `cli` | function | `kernel/sched.c:2908` | `* cli (disk PIO must never run with the timer held off);` |
| `context` | function | `kernel/sched.c:888` | `* context (anything entered via k_exec_user) is inside a syscall  * (entry swapped 0 in), and a c...` |
| `copy` | function | `kernel/sched.c:362` | `* copy (fail closed, fork refuses) instead of forging pointers. */ /* Name the link a fork could ...` |
| `ctx_from_frame` | function | `kernel/sched.c:2537` | `static void ctx_from_frame(ctx_regs_t *c, const syscall_frame_t *f)` |
| `descriptor` | function | `kernel/sched.c:97` | `* descriptor (two slots) per CPU past the 5 stage-2 entries. */ _Static_assert((5 + 2 * MAX_CPUS) * 8 ==...` |
| `do_clone_thread` | function | `kernel/sched.c:2724` | `static long do_clone_thread(unsigned long flags, unsigned long newsp,                            ...` |
| `do_execve` | function | `kernel/sched.c:2926` | `long do_execve(char *kpath, int kargc, char **kargv)` |
| `do_exit` | function | `kernel/sched.c:2250` | `void do_exit(int code)` |
| `do_fork` | function | `kernel/sched.c:2564` | `long do_fork(void)` |
| `do_fork_ex` | function | `kernel/sched.c:2577` | `long do_fork_ex(uint64_t set_tid, uint64_t clear_tid)` |
| `do_group_exit` | function | `kernel/sched.c:2859` | `void do_group_exit(int code)` |
| `do_kill` | function | `kernel/sched.c:3324` | `int do_kill(int pid)` |
| `do_kill_code` | function | `kernel/sched.c:3330` | `int do_kill_code(int pid, int code)` |
| `do_thread_spawn` | function | `kernel/sched.c:2314` | `long do_thread_spawn(unsigned long fn, unsigned long stack,                      unsigned long arg)` |
| `do_waitpid` | function | `kernel/sched.c:3224` | `int do_waitpid(int pid)` |
| `do_waitpid_linux` | function | `kernel/sched.c:3255` | `int do_waitpid_linux(int pid, int nohang, int *found)` |
| `exec_enter` | function | `kernel/sched.c:72` | `extern void exec_enter(unsigned long frame);` |
| `fork_child_settid` | function | `kernel/sched.c:2555` | `void fork_child_settid(void)` |
| `fork_report` | function | `kernel/sched.c:2570` | `static void fork_report(const char *what)` |
| `fork_trampoline` | function | `kernel/sched.c:67` | `extern void fork_trampoline(void);` |
| `fpu_alloc_clean` | function | `kernel/sched.c:318` | `static void *fpu_alloc_clean(void)` |
| `fpu_free_proc` | function | `kernel/sched.c:336` | `static void fpu_free_proc(proc_t *p)` |
| `fpu_restore_from` | function | `kernel/sched.c:314` | `static inline void fpu_restore_from(void *area)` |
| `gdb_dump_report` | function | `kernel/sched.c:697` | `void gdb_dump_report(unsigned long addr, unsigned long len)` |
| `group_threads_live_locked` | function | `kernel/sched.c:3192` | `static int group_threads_live_locked(int tgid)` |
| `here` | function | `kernel/sched.c:128` | `* smp_ap_idle_loop here (idle_proc ctx.rsp points at the top). */ static char ap_idle_stack[MAX_CPUS][4096]...` |
| `idt_init` | function | `kernel/sched.c:756` | `static void idt_init(void)` |
| `idt_set` | function | `kernel/sched.c:745` | `static void idt_set(int vec, void (*h)(void))` |
| `irqstat_report` | function | `kernel/sched.c:631` | `void irqstat_report(void)` |
| `isr_dispatch` | function | `kernel/sched.c:1203` | `void isr_dispatch(int vector, trap_frame_t *frame)` |
| `isr_stub_table` | variable | `kernel/sched.c:152` | `extern void *isr_stub_table[];` |
| `it` | function | `kernel/sched.c:3370` | `* it (SPAWN/exec point proc 0 here transiently);` |
| `itself` | function | `kernel/sched.c:2514` | `* the shell itself (use mrun first), and a CLONE_VM thread forking  * would duplicate shared stat...` |
| `kill_group_threads_locked` | function | `kernel/sched.c:2838` | `static void kill_group_threads_locked(int tgid, int except)` |
| `kstack_is_slot_end` | function | `kernel/sched.c:199` | `static int kstack_is_slot_end(uint64_t v)` |
| `kstack_of` | function | `kernel/sched.c:209` | `static uint64_t kstack_of(int j)` |
| `kstack_owner` | function | `kernel/sched.c:216` | `static int kstack_owner(uint64_t top)` |
| `kstack_paint` | function | `kernel/sched.c:171` | `static void kstack_paint(uint64_t top, unsigned long size)` |
| `kstack_report` | function | `kernel/sched.c:520` | `void kstack_report(void)` |
| `kstack_scan_serial` | function | `kernel/sched.c:231` | `static void kstack_scan_serial(void)` |
| `kstack_usage` | function | `kernel/sched.c:180` | `static int kstack_usage(uint64_t top, unsigned long size,                         unsigned long *...` |
| `live` | function | `kernel/sched.c:286` | `* every reap leaked its own stack and released a neighbour that could  * still be live (two procs...` |
| `mm_lock` | variable | `kernel/sched.c:882` | `extern spinlock_t mm_lock;` |
| `mm_owner` | function | `kernel/sched.c:472` | `static proc_t *mm_owner(proc_t *p)` |
| `mm_view_claim_current` | function | `kernel/sched.c:513` | `void mm_view_claim_current(void)` |
| `mm_view_enter` | function | `kernel/sched.c:494` | `static void mm_view_enter(proc_t *nxt)` |
| `net_rx_dropped` | variable | `kernel/sched.c:635` | `extern unsigned int net_rx_dropped;` |
| `off_lo` | type_alias | `kernel/sched.c:143` | `typedef struct __attribute__((packed)) { uint16_t off_lo;` |
| `park` | function | `kernel/sched.c:3422` | `* an image its live FPU registers would be dropped by the preempt * park (the save path skips a null area). */...` |
| `pic_eoi` | function | `kernel/sched.c:814` | `static void pic_eoi(int irq)` |
| `pic_init` | function | `kernel/sched.c:772` | `static void pic_init(void)` |
| `pit_init` | function | `kernel/sched.c:807` | `static void pit_init(void)` |
| `point` | function | `kernel/sched.c:901` | `* return address as the resume point ("continue the ISR"), which  * required the stranded ISR fra...` |
| `proc_create` | function | `kernel/sched.c:1827` | `int proc_create(const char *name, int parent_pid)` |
| `proc_get` | function | `kernel/sched.c:1821` | `proc_t *proc_get(int pid)` |
| `proc_running_anywhere` | function | `kernel/sched.c:3159` | `static int proc_running_anywhere(int pid)` |
| `proc_spawn_elf` | function | `kernel/sched.c:2105` | `int proc_spawn_elf(const char *name, void *data, unsigned size,                    int argc, char...` |
| `proc_spawn_elf_inner` | function | `kernel/sched.c:1945` | `static int proc_spawn_elf_inner(const char *name, void *data, unsigned size,                    i...` |
| `read_cr3` | function | `kernel/sched.c:74` | `static inline unsigned long read_cr3(void)` |
| `reap_autoreap_locked` | function | `kernel/sched.c:3168` | `static void reap_autoreap_locked(int tgid)` |
| `registers` | function | `kernel/sched.c:2345` | `* registers (float args would need XMM inheritance, which the * arg-passing contract does not carry: fn takes one...` |
| `res0` | type_alias | `kernel/sched.c:109` | `typedef struct __attribute__((packed)) { uint32_t res0;` |
| `returns` | function | `kernel/sched.c:2243` | `* that returns (and the resumed thread returns with IF=1). */ __asm__ volatile("cli");` |
| `rlimit_cpu_exceeded` | function | `kernel/sched.c:1182` | `int rlimit_cpu_exceeded(int pid)` |
| `rtl_counters` | function | `kernel/sched.c:634` | `extern void rtl_counters(unsigned int *tx_frames, unsigned int *rx_frames);` |
| `rtl_present` | function | `kernel/sched.c:636` | `extern int rtl_present(void);` |
| `sc_top_save` | variable | `kernel/sched.c:69` | `extern unsigned long sc_top_save[];` |
| `sched_ap_preempt` | function | `kernel/sched.c:1076` | `static void sched_ap_preempt(trap_frame_t *frame)` |
| `sched_idle_on_kernel_cr3` | function | `kernel/sched.c:723` | `int sched_idle_on_kernel_cr3(int cpu)` |
| `sched_init` | function | `kernel/sched.c:3362` | `void sched_init(void)` |
| `sched_lock` | function | `kernel/sched.c:452` | `* hold sched_lock (+mm_lock at the swap sites);` |
| `sched_next_locked` | function | `kernel/sched.c:930` | `static int sched_next_locked(int start, int vm_only)` |
| `sched_set_nice` | function | `kernel/sched.c:948` | `int sched_set_nice(int pid, int nice)` |
| `sched_tick_audio` | function | `kernel/sched.c:26` | `static void sched_tick_audio(void *ctx)` |
| `sched_tick_desktop` | function | `kernel/sched.c:32` | `static void sched_tick_desktop(void *ctx)` |
| `sched_tick_usb` | function | `kernel/sched.c:43` | `static void sched_tick_usb(void *ctx)` |
| `schedtop_report` | function | `kernel/sched.c:563` | `void schedtop_report(void)` |
| `schedule` | function | `kernel/sched.c:2147` | `* that keeps schedule()'s own rbp runs the caller's frame accesses  * (locals, leave/ret) on the ...` |
| `schedule` | function | `kernel/sched.c:2154` | `void schedule(void)` |
| `seccomp_allow_one` | function | `kernel/sched.c:964` | `int seccomp_allow_one(int pid, int n)` |
| `seccomp_denied` | function | `kernel/sched.c:971` | `int seccomp_denied(int pid, int n)` |
| `seccomp_deny_one` | function | `kernel/sched.c:957` | `int seccomp_deny_one(int pid, int n)` |
| `shares` | function | `kernel/sched.c:2595` | `* thread on another CPU kept its writable translation and wrote straight * into frames the child now shares (the...` |
| `shell_nchildren` | function | `kernel/sched.c:3298` | `int shell_nchildren(void)` |
| `shell_reap_nb` | function | `kernel/sched.c:3272` | `int shell_reap_nb(int *pid_out, int *code_out)` |
| `shell_reap_one` | function | `kernel/sched.c:3286` | `int shell_reap_one(int pid, int *code_out)` |
| `slot` | function | `kernel/sched.c:567` | `* must not eat a quarter of a 16 KB slot (see the stack discipline * contract in CLAUDE.md). Fail-closed on OOM. */...` |
| `smp_any_ap_idle` | function | `kernel/sched.c:1146` | `static int smp_any_ap_idle(void)` |
| `smp_ap_idle_loop` | function | `kernel/sched.c:1042` | `void smp_ap_idle_loop(void)` |
| `smp_claim_thread_v` | function | `kernel/sched.c:996` | `static int smp_claim_thread_v(int vm_only)` |
| `smp_try_claim_hint` | function | `kernel/sched.c:980` | `static int smp_try_claim_hint(int pid, int vm_only)` |
| `stop_row` | struct | `kernel/sched.c:564` | `` |
| `stub` | function | `kernel/sched.c:650` | `* gdb stub (`make gdb`, then `target remote :1234` from the host). These  * helpers are the seria...` |
| `sys_ticks` | function | `kernel/sched.c:627` | `* sys_ticks (PIT 100 Hz on the BSP, broadcast as IPIs to APs);` |
| `syscall` | function | `kernel/sched.c:1320` | `* outgoing syscall (see sched_rearm_kgs). Without * this the next entry swapgs puts garbage under GS * and the pid...` |
| `timer_tick` | function | `kernel/sched.c:3357` | `void timer_tick(void)` |
| `trap_frame_t` | struct | `kernel/sched.c:729` | `` |
| `tss_init` | function | `kernel/sched.c:838` | `static void tss_init(void)` |
| `tss_init_ap` | function | `kernel/sched.c:870` | `void tss_init_ap(int cpu)` |
| `tss_write_desc` | function | `kernel/sched.c:821` | `static void tss_write_desc(int cpu)` |
| `user_trampoline` | function | `kernel/sched.c:66` | `extern void user_trampoline(void);` |
| `vma_ctx_alloc` | function | `kernel/sched.c:342` | `vma_ctx_t *vma_ctx_alloc(void)` |
| `vma_ctx_copy` | function | `kernel/sched.c:371` | `static vma_ctx_t *vma_ctx_copy(vma_ctx_t *src)` |
| `vma_ctx_free` | function | `kernel/sched.c:352` | `void vma_ctx_free(vma_ctx_t *c)` |
| `vma_load_proc` | function | `kernel/sched.c:458` | `static void vma_load_proc(proc_t *p)` |
| `vma_owned` | function | `kernel/sched.c:446` | `static int vma_owned(proc_t *p)` |
| `vma_save_proc` | function | `kernel/sched.c:454` | `static void vma_save_proc(proc_t *p)` |
| `waitpid_has_child` | function | `kernel/sched.c:3241` | `static int waitpid_has_child(int pid)` |
| `waitpid_scan` | function | `kernel/sched.c:3203` | `static int waitpid_scan(int pid, int *found)` |
| `yield` | function | `kernel/sched.c:2235` | `void yield(void)` |
| `zeroed` | function | `kernel/sched.c:3433` | `* still zeroed (kmemset happens inside idt_init) faults through a * null gate. Handlers for 32/33/44 are safe...` |
| `SCROLLBACK_ROWS` | macro | `kernel/scrollback.c:12` | `#define SCROLLBACK_ROWS` |
| `sb_capture_row0` | function | `kernel/scrollback.c:23` | `void sb_capture_row0(void)` |
| `sb_get_char` | function | `kernel/scrollback.c:41` | `char sb_get_char(int row, int col)` |
| `sb_get_count` | function | `kernel/scrollback.c:38` | `int sb_get_count(void)` |
| `sb_get_head` | function | `kernel/scrollback.c:39` | `int sb_get_head(void)` |
| `sb_init` | function | `kernel/scrollback.c:17` | `void sb_init(void)` |
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
| `HTTPD_IO_CHUNK` | macro | `kernel/shell.c:2564` | `#define HTTPD_IO_CHUNK` |
| `HTTPD_REQ_CAP` | macro | `kernel/shell.c:2563` | `#define HTTPD_REQ_CAP` |
| `PIPE_HOP_MAX` | macro | `kernel/shell.c:4103` | `#define PIPE_HOP_MAX` |
| `QEMU_PM_PORT` | macro | `kernel/shell.c:1033` | `#define QEMU_PM_PORT` |
| `SHELL_BUILTIN_COUNT` | macro | `kernel/shell.c:232` | `#define SHELL_BUILTIN_COUNT` |
| `SHELL_CVM_INTERP` | macro | `kernel/shell.c:53` | `#define SHELL_CVM_INTERP` |
| `SHELL_HIST_MAX` | macro | `kernel/shell.c:98` | `#define SHELL_HIST_MAX` |
| `SHELL_LS_CAP` | macro | `kernel/shell.c:2821` | `#define SHELL_LS_CAP` |
| `SHELL_RUN_DIRS` | macro | `kernel/shell.c:72` | `#define SHELL_RUN_DIRS` |
| `ShellRunDir` | struct | `kernel/shell.c:61` | `` |
| `VMA` | function | `kernel/shell.c:2208` | `* plus the live VMA (mmap) tree. The walk is bounded (64-deep explicit  * stack, 128 regions prin...` |
| `XXH_STATIC_LINKING_ONLY` | macro | `kernel/shell.c:25` | `#define XXH_STATIC_LINKING_ONLY` |
| `code` | function | `kernel/shell.c:1412` | `* the last exit code (130 when interrupted). */ static int shell_wait_fg(int *pids, int n, int ki...` |
| `context` | function | `kernel/shell.c:1705` | `* ISR context (which corrupts the running program's state) or * nesting a second foreground run inside the wait. */...` |
| `desktop_flag` | function | `kernel/shell.c:1566` | `static void desktop_flag(const char *name)` |
| `desktop_flag_on` | function | `kernel/shell.c:1576` | `static int desktop_flag_on(const char *name)` |
| `desktop_path` | function | `kernel/shell.c:1557` | `static void desktop_path(const char *name, char *dst, unsigned cap)` |
| `desktop_srv_alive` | function | `kernel/shell.c:1598` | `static int desktop_srv_alive(void)` |
| `desktop_unflag` | function | `kernel/shell.c:848` | `static void desktop_unflag(const char *name);` |
| `driver` | function | `kernel/shell.c:3331` | `* stream through the fat: VFS driver ("img:fatpath" per open,      * registered at boot beside me...` |
| `etrel_path_trusted` | function | `kernel/shell.c:1123` | `static int etrel_path_trusted(const char *full)` |
| `flows` | function | `kernel/shell.c:1590` | `* and external flows (make wl) set it themselves. */ static void desktop_unflag(const char *name)` |
| `frame` | function | `kernel/shell.c:3725` | `* not live in this frame (stack discipline, CLAUDE.md). */ struct ps_row *snap = (struct ps_row...` |
| `gfx_parse_int` | function | `kernel/shell.c:1751` | `static int gfx_parse_int(const char *s, int *out)` |
| `gfx_read_palette` | function | `kernel/shell.c:1771` | `static void gfx_read_palette(unsigned char pal[768])` |
| `job_row` | struct | `kernel/shell.c:2079` | `` |
| `line` | function | `kernel/shell.c:446` | `* to the live line (handled by the caller resetting shell_hist_idx). */ static void shell_hist_na...` |
| `outw_port` | function | `kernel/shell.c:1029` | `static inline void outw_port(unsigned short port, unsigned short val)` |
| `ps_row` | struct | `kernel/shell.c:3723` | `` |
| `root` | function | `kernel/shell.c:665` | `* MiniFS root (where the big ELFs live under bare names), * and only the highest-priority non-empty tier is kept. An...` |
| `shell_cmd_desktop` | function | `kernel/shell.c:1614` | `static void shell_cmd_desktop(int argc, char **argv)` |
| `shell_cmd_gdb` | function | `kernel/shell.c:2402` | `static void shell_cmd_gdb(int argc, char **argv)` |
| `shell_cmd_gfx` | function | `kernel/shell.c:1778` | `static void shell_cmd_gfx(int argc, char **argv)` |
| `shell_cmd_hash` | function | `kernel/shell.c:2445` | `static void shell_cmd_hash(int argc, char **argv)` |
| `shell_cmd_jobs` | function | `kernel/shell.c:2078` | `static void shell_cmd_jobs(void)` |
| `shell_cmd_kill` | function | `kernel/shell.c:2152` | `static void shell_cmd_kill(int argc, char **argv)` |
| `shell_cmd_mem` | function | `kernel/shell.c:2175` | `static void shell_cmd_mem(void)` |
| `shell_cmd_mrun` | function | `kernel/shell.c:1466` | `static void shell_cmd_mrun(int argc, char **argv)` |
| `shell_cmd_poweroff` | function | `kernel/shell.c:1035` | `static void shell_cmd_poweroff(void)` |
| `shell_cmd_wait` | function | `kernel/shell.c:2117` | `static void shell_cmd_wait(int argc, char **argv)` |
| `shell_cmd_wm` | function | `kernel/shell.c:1930` | `static void shell_cmd_wm(int argc, char **argv)` |
| `shell_complete_minifs_arg` | function | `kernel/shell.c:271` | `static void shell_complete_minifs_arg(const char *word, unsigned long wlen,                      ...` |
| `shell_complete_replace` | function | `kernel/shell.c:250` | `static void shell_complete_replace(char *buf, int size, int *pos,                                ...` |
| `shell_complete_tier` | function | `kernel/shell.c:238` | `static int shell_complete_tier(const char *nm)` |
| `shell_cross_cat` | function | `kernel/shell.c:2863` | `static void shell_cross_cat(const char *drv, const char *imgarg,                             cons...` |
| `shell_cross_ls` | function | `kernel/shell.c:2822` | `static void shell_cross_ls(const char *drv, const char *imgarg,                            const ...` |
| `shell_exec_builtin` | function | `kernel/shell.c:2905` | `void shell_exec_builtin(int argc, char **argv)` |
| `shell_file_is_real` | function | `kernel/shell.c:1069` | `static int shell_file_is_real(const char *resolved)` |
| `shell_focus_park` | function | `kernel/shell.c:116` | `void shell_focus_park(void)` |
| `shell_focus_restore` | function | `kernel/shell.c:121` | `void shell_focus_restore(void)` |
| `shell_has_child` | function | `kernel/shell.c:2107` | `static int shell_has_child(int pid)` |
| `shell_hist_newest_match` | function | `kernel/shell.c:429` | `static int shell_hist_newest_match(const char *prefix, unsigned long plen)` |
| `shell_hist_show` | function | `kernel/shell.c:346` | `static void shell_hist_show(char *buf, int size, int *pos, const char *text)` |
| `shell_httpd_one` | function | `kernel/shell.c:2570` | `static void shell_httpd_one(int child, const char *root)` |
| `shell_httpd_serve` | function | `kernel/shell.c:2655` | `static void shell_httpd_serve(unsigned short port, const char *root,         int max_conn)` |
| `shell_is_pipe_tok` | function | `kernel/shell.c:4105` | `static int shell_is_pipe_tok(const char *a)` |
| `shell_line_backspace` | function | `kernel/shell.c:390` | `static void shell_line_backspace(char *buf, int size, int *pos)` |
| `shell_line_delete` | function | `kernel/shell.c:398` | `static void shell_line_delete(char *buf, int size, int *pos)` |
| `shell_line_insert` | function | `kernel/shell.c:381` | `static void shell_line_insert(char *buf, int size, int *pos, char c)` |
| `shell_line_kill_front` | function | `kernel/shell.c:405` | `static void shell_line_kill_front(char *buf, int size, int *pos)` |
| `shell_line_kill_tail` | function | `kernel/shell.c:412` | `static void shell_line_kill_tail(char *buf, int size, int *pos)` |
| `shell_line_kill_word` | function | `kernel/shell.c:417` | `static void shell_line_kill_word(char *buf, int size, int *pos)` |
| `shell_line_repaint` | function | `kernel/shell.c:368` | `static void shell_line_repaint(char *buf, int size, int pos)` |
| `shell_load` | function | `kernel/shell.c:966` | `static int shell_load(const char *fname, char *progname_out, void **entry_out)` |
| `shell_name_base` | function | `kernel/shell.c:213` | `static const char *shell_name_base(const char *path)` |
| `shell_parse` | function | `kernel/shell.c:826` | `int shell_parse(char *line, char **argv, int max_args)` |
| `shell_parse_long` | function | `kernel/shell.c:2366` | `int shell_parse_long(const char *s, long *out)` |
| `shell_parse_pid` | function | `kernel/shell.c:2387` | `int shell_parse_pid(const char *s, int min_pid, int *out)` |
| `shell_parse_u64` | function | `kernel/shell.c:2350` | `static int shell_parse_u64(const char *s, unsigned long *out)` |
| `shell_parse_vol` | function | `kernel/shell.c:158` | `static int shell_parse_vol(const char *s, unsigned *out)` |
| `shell_prompt` | function | `kernel/shell.c:148` | `static void shell_prompt(void)` |
| `shell_queue_launch` | function | `kernel/shell.c:87` | `void shell_queue_launch(const char *cmd)` |
| `shell_read_elf_bytes` | function | `kernel/shell.c:1346` | `static int shell_read_elf_bytes(const char *name, unsigned char **out,                           ...` |
| `shell_readline` | function | `kernel/shell.c:338` | `static void shell_readline(void)` |
| `shell_readline_active` | function | `kernel/shell.c:115` | `int shell_readline_active(void)` |
| `shell_readline_buf` | function | `kernel/shell.c:184` | `void shell_readline_buf(char *buf, int size)` |
| `shell_readline_hist` | function | `kernel/shell.c:491` | `static void shell_readline_hist(char *buf, int size)` |
| `shell_resolve_arg` | function | `kernel/shell.c:2464` | `static int shell_resolve_arg(const char *cmd, const char *arg,                              const...` |
| `shell_resolve_run` | function | `kernel/shell.c:1081` | `static int shell_resolve_run(const char *name, char *out, unsigned cap)` |
| `shell_run` | function | `kernel/shell.c:894` | `void shell_run(void)` |
| `shell_run_any` | function | `kernel/shell.c:1678` | `int shell_run_any(const char *name, int argc, char **argv)` |
| `shell_run_bg` | function | `kernel/shell.c:1514` | `static void shell_run_bg(const char *name, int argc, char **argv)` |
| `shell_run_cvm` | function | `kernel/shell.c:1266` | `static int shell_run_cvm(const char *full, int argc, char **argv)` |
| `shell_run_dir_for` | function | `kernel/shell.c:1051` | `static const ShellRunDir *shell_run_dir_for(const char *name)` |
| `shell_run_elf_buf_path` | function | `kernel/shell.c:1163` | `static int shell_run_elf_buf_path(const char *data, unsigned size, int argc,                     ...` |
| `shell_run_elf_file` | function | `kernel/shell.c:1196` | `static int shell_run_elf_file(const char *full, int argc, char **argv)` |
| `shell_run_elf_minifs` | function | `kernel/shell.c:1209` | `static int shell_run_elf_minifs(const char *name, int argc, char **argv)` |
| `shell_run_file` | function | `kernel/shell.c:1302` | `static int shell_run_file(const char *name, int argc, char **argv)` |
| `shell_run_init` | function | `kernel/shell.c:855` | `static void shell_run_init(void)` |
| `shell_run_pipeline` | function | `kernel/shell.c:151` | `static int shell_run_pipeline(char **argv, int argc, const char *redir_path, int redir_append, int redirected);` |
| `shell_run_stage` | function | `kernel/shell.c:4144` | `static char *shell_run_stage(char **sargv, int sargc,         const char *input, unsigned long in...` |
| `stdout` | function | `kernel/shell.c:4093` | `* the pipe exactly like stdout (`2>` is an alias of `>`). * Per-stage `exit code:` lines report to the console...` |
| `terminal` | function | `kernel/shell.c:2980` | `* sequence clears serial consoles and is swallowed without * garbage by the framebuffer terminal (vedit pattern). */...` |
| `text` | function | `kernel/shell.c:594` | `* swallowed the sequence as plain text ("5~" in the * line) and the history was unreachable from the * prompt. */...` |
| `this` | function | `kernel/shell.c:1544` | `* boot into the tiled Wayland desktop: every NK app started after * this (paint, vedit, file, nuklear, doomedit...` |
| `to` | function | `kernel/shell.c:2281` | `* actually trap to (brk/mmap/munmap/mprotect) and says so up front. */ static void shell_cmd_trac...` |
| `tree` | function | `kernel/shell.c:2065` | `* tree (mmap-heavy jobs stay best-effort), legacy blocking `run` ignores  * Ctrl+C (it never poll...` |
| `window` | function | `kernel/shell.c:1339` | `* window (proc_spawn_elf) and waits for all of them. The 100 Hz timer * preempts the BSP across the READY set, so...` |
| `spawn_backup` | function | `kernel/spawn.c:11` | `int spawn_backup(spawn_ctx_t *ctx)` |
| `spawn_copy_argv` | function | `kernel/spawn.c:99` | `char **spawn_copy_argv(int argc, const char **uargv)` |
| `spawn_execute` | function | `kernel/spawn.c:268` | `int spawn_execute(const char *resolved, const char *redirect,                   unsigned char *da...` |
| `spawn_free_argv` | function | `kernel/spawn.c:87` | `void spawn_free_argv(char **kargv, int argc)` |
| `spawn_load_image` | function | `kernel/spawn.c:161` | `unsigned char *spawn_load_image(const char *resolved, unsigned *size_out)` |
| `spawn_restore` | function | `kernel/spawn.c:38` | `void spawn_restore(spawn_ctx_t *ctx)` |
| `spawn_run_exec` | function | `kernel/spawn.c:222` | `static int spawn_run_exec(const char *resolved, const char *redirect,                            ...` |
| `spawn_run_rel` | function | `kernel/spawn.c:196` | `static int spawn_run_rel(const char *resolved, const char *redirect,                          uns...` |
| `spawn_validate_argv` | function | `kernel/spawn.c:143` | `int spawn_validate_argv(int argc, const char **uargv)` |
| `NO_LOOP_IDIOM` | macro | `kernel/string.c:68` | `#define NO_LOOP_IDIOM` |
| `katol` | function | `kernel/string.c:120` | `long katol(const char *s)` |
| `kmemcmp` | function | `kernel/string.c:86` | `int kmemcmp(const void *a, const void *b, unsigned long n)` |
| `kmemcpy` | function | `kernel/string.c:73` | `NO_LOOP_IDIOM void *kmemcpy(void *dst, const void *src, unsigned long n)` |
| `kmemmove` | function | `kernel/string.c:92` | `NO_LOOP_IDIOM void *kmemmove(void *dst, const void *src, unsigned long n)` |
| `kmemset` | function | `kernel/string.c:80` | `NO_LOOP_IDIOM void *kmemset(void *dst, int c, unsigned long n)` |
| `kstrchr` | function | `kernel/string.c:53` | `char *kstrchr(const char *s, int c)` |
| `kstrcmp` | function | `kernel/string.c:43` | `int kstrcmp(const char *a, const char *b)` |
| `kstrcpy` | function | `kernel/string.c:23` | `char *kstrcpy(char *dst, const char *src)` |
| `kstrlen` | function | `kernel/string.c:17` | `unsigned long kstrlen(const char *s)` |
| `kstrncat` | function | `kernel/string.c:35` | `char *kstrncat(char *dst, const char *src, unsigned long n)` |
| `kstrncmp` | function | `kernel/string.c:48` | `int kstrncmp(const char *a, const char *b, unsigned long n)` |
| `kstrncpy` | function | `kernel/string.c:29` | `char *kstrncpy(char *dst, const char *src, unsigned long n)` |
| `kstrstr` | function | `kernel/string.c:58` | `char *kstrstr(const char *hay, const char *ndl)` |
| `memcmp` | function | `kernel/string.c:116` | `int memcmp(const void *a, const void *b, unsigned long n)` |
| `memcpy` | function | `kernel/string.c:104` | `void *memcpy(void *dst, const void *src, unsigned long n)` |
| `memmove` | function | `kernel/string.c:108` | `void *memmove(void *dst, const void *src, unsigned long n)` |
| `memset` | function | `kernel/string.c:112` | `void *memset(void *dst, int c, unsigned long n)` |
| `k_register_process` | function | `kernel/symtab.c:57` | `void k_register_process(const char *name, void *proc_entry)` |
| `k_register_program` | function | `kernel/symtab.c:49` | `void k_register_program(const char *name, prog_entry_t entry)` |
| `k_register_symbol` | function | `kernel/symtab.c:10` | `void k_register_symbol(const char *name, void *addr)` |
| `k_spawn` | function | `kernel/symtab.c:65` | `int k_spawn(const char *name, int argc, char **argv)` |
| `kprog_lookup` | function | `kernel/symtab.c:42` | `KProg *kprog_lookup(const char *name)` |
| `kprog_slot` | function | `kernel/symtab.c:34` | `KProg *kprog_slot(const char *name)` |
| `ksym_resolve` | function | `kernel/symtab.c:18` | `void *ksym_resolve(const char *name)` |
| `cond_broadcast` | function | `kernel/sync.c:251` | `void cond_broadcast(cond_t *c)` |
| `cond_init` | function | `kernel/sync.c:237` | `void cond_init(cond_t *c)` |
| `cond_signal` | function | `kernel/sync.c:247` | `void cond_signal(cond_t *c)` |
| `cond_wait` | function | `kernel/sync.c:241` | `void cond_wait(cond_t *c, mutex_t *m)` |
| `mutex_init` | function | `kernel/sync.c:78` | `void mutex_init(mutex_t *m)` |
| `mutex_lock` | function | `kernel/sync.c:152` | `void mutex_lock(mutex_t *m)` |
| `mutex_trylock` | function | `kernel/sync.c:172` | `int mutex_trylock(mutex_t *m)` |
| `mutex_unlock` | function | `kernel/sync.c:188` | `void mutex_unlock(mutex_t *m)` |
| `pi_boost` | function | `kernel/sync.c:126` | `static void pi_boost(int waiter, int owner)` |
| `pi_get_eff` | function | `kernel/sync.c:110` | `int pi_get_eff(int pid)` |
| `pi_recompute` | function | `kernel/sync.c:115` | `static void pi_recompute(int pid)` |
| `pi_set_base` | function | `kernel/sync.c:101` | `void pi_set_base(int pid, int prio)` |
| `pi_valid` | function | `kernel/sync.c:95` | `static int pi_valid(int pid)` |
| `rwlock_init` | function | `kernel/sync.c:255` | `void rwlock_init(rwlock_t *rw)` |
| `rwlock_read_lock` | function | `kernel/sync.c:289` | `void rwlock_read_lock(rwlock_t *rw)` |
| `rwlock_read_trylock` | function | `kernel/sync.c:263` | `int rwlock_read_trylock(rwlock_t *rw)` |
| `rwlock_read_unlock` | function | `kernel/sync.c:296` | `void rwlock_read_unlock(rwlock_t *rw)` |
| `rwlock_write_lock` | function | `kernel/sync.c:306` | `void rwlock_write_lock(rwlock_t *rw)` |
| `rwlock_write_trylock` | function | `kernel/sync.c:277` | `int rwlock_write_trylock(rwlock_t *rw)` |
| `rwlock_write_unlock` | function | `kernel/sync.c:328` | `void rwlock_write_unlock(rwlock_t *rw)` |
| `sem_init` | function | `kernel/sync.c:209` | `void sem_init(sem_t *s, int value)` |
| `sem_post` | function | `kernel/sync.c:229` | `void sem_post(sem_t *s)` |
| `sem_wait` | function | `kernel/sync.c:215` | `void sem_wait(sem_t *s)` |
| `sleep_on` | function | `kernel/sync.c:35` | `void sleep_on(wait_queue_t *q)` |
| `t_cur_pid` | variable | `kernel/sync.c:26` | `extern int t_cur_pid;` |
| `wake_up` | function | `kernel/sync.c:56` | `int wake_up(wait_queue_t *q)` |
| `wake_up_all` | function | `kernel/sync.c:72` | `int wake_up_all(wait_queue_t *q)` |
| `wq_init` | function | `kernel/sync.c:29` | `void wq_init(wait_queue_t *q)` |
| `DOOM_FRAME` | function | `kernel/syscalls.c:829` | `* DOOM_FRAME (211) and NK_FRAME (220) stay as compat aliases. */ static long sys_minios_gfx_prese...` |
| `Discipline` | function | `kernel/syscalls.c:3637` | `* * Discipline (audit 2026-09, kept as comment, not a deprecation: both * primitives are legitimate): user_range_ok...` |
| `EAGAIN` | function | `kernel/syscalls.c:1287` | `* writer open is EAGAIN (-11, retry);` |
| `EOF` | function | `kernel/syscalls.c:1288` | `* is EOF (0). */ KFILE *o = kfd_get(0);` |
| `FD_STD_COUNT` | macro | `kernel/syscalls.c:1523` | `#define FD_STD_COUNT` |
| `FIONREAD` | function | `kernel/syscalls.c:2633` | `* descriptor answers FIONREAD (bytes readable now), FIONBIO (O_NONBLOCK),  * FIOCLEX/FIONCLEX (FD...` |
| `GETDENTS64_ALIGN` | macro | `kernel/syscalls.c:950` | `#define GETDENTS64_ALIGN` |
| `GETDENTS64_NAME_OFF` | macro | `kernel/syscalls.c:949` | `#define GETDENTS64_NAME_OFF` |
| `KFD_MAX` | macro | `kernel/syscalls.c:52` | `#define KFD_MAX` |
| `LINUX_AT_FDCWD` | macro | `kernel/syscalls.c:1468` | `#define LINUX_AT_FDCWD` |
| `LINUX_CLOCK_BOOTTIME` | macro | `kernel/syscalls.c:2814` | `#define LINUX_CLOCK_BOOTTIME` |
| `LINUX_CLOCK_MONOTONIC` | macro | `kernel/syscalls.c:2813` | `#define LINUX_CLOCK_MONOTONIC` |
| `LINUX_CLOCK_REALTIME` | macro | `kernel/syscalls.c:2812` | `#define LINUX_CLOCK_REALTIME` |
| `LINUX_CLOSE_RANGE_CLOEXEC` | macro | `kernel/syscalls.c:1518` | `#define LINUX_CLOSE_RANGE_CLOEXEC` |
| `LINUX_CLOSE_RANGE_UNSHARE` | macro | `kernel/syscalls.c:1517` | `#define LINUX_CLOSE_RANGE_UNSHARE` |
| `LINUX_CPUMASK_BYTES` | macro | `kernel/syscalls.c:2747` | `#define LINUX_CPUMASK_BYTES` |
| `LINUX_DT_DIR` | macro | `kernel/syscalls.c:947` | `#define LINUX_DT_DIR` |
| `LINUX_DT_REG` | macro | `kernel/syscalls.c:948` | `#define LINUX_DT_REG` |
| `LINUX_EFD_CLOEXEC` | macro | `kernel/syscalls.c:1521` | `#define LINUX_EFD_CLOEXEC` |
| `LINUX_EFD_NONBLOCK` | macro | `kernel/syscalls.c:1520` | `#define LINUX_EFD_NONBLOCK` |
| `LINUX_EFD_SEMAPHORE` | macro | `kernel/syscalls.c:1519` | `#define LINUX_EFD_SEMAPHORE` |
| `LINUX_ENOTTY` | macro | `kernel/syscalls.c:2610` | `#define LINUX_ENOTTY` |
| `LINUX_EVENTFD_WORD` | macro | `kernel/syscalls.c:1522` | `#define LINUX_EVENTFD_WORD` |
| `LINUX_FD_CLOEXEC` | macro | `kernel/syscalls.c:1510` | `#define LINUX_FD_CLOEXEC` |
| `LINUX_FIOCLEX` | macro | `kernel/syscalls.c:2608` | `#define LINUX_FIOCLEX` |
| `LINUX_FIONBIO` | macro | `kernel/syscalls.c:2606` | `#define LINUX_FIONBIO` |
| `LINUX_FIONCLEX` | macro | `kernel/syscalls.c:2607` | `#define LINUX_FIONCLEX` |
| `LINUX_FIONREAD` | macro | `kernel/syscalls.c:2605` | `#define LINUX_FIONREAD` |
| `LINUX_F_DUPFD` | macro | `kernel/syscalls.c:1511` | `#define LINUX_F_DUPFD` |
| `LINUX_F_DUPFD_CLOEXEC` | macro | `kernel/syscalls.c:1516` | `#define LINUX_F_DUPFD_CLOEXEC` |
| `LINUX_F_GETFD` | macro | `kernel/syscalls.c:1512` | `#define LINUX_F_GETFD` |
| `LINUX_F_GETFL` | macro | `kernel/syscalls.c:1514` | `#define LINUX_F_GETFL` |
| `LINUX_F_SETFD` | macro | `kernel/syscalls.c:1513` | `#define LINUX_F_SETFD` |
| `LINUX_F_SETFL` | macro | `kernel/syscalls.c:1515` | `#define LINUX_F_SETFL` |
| `LINUX_IOCTL_INT` | macro | `kernel/syscalls.c:2614` | `#define LINUX_IOCTL_INT` |
| `LINUX_MAP_ANONYMOUS` | macro | `kernel/syscalls.c:1968` | `#define LINUX_MAP_ANONYMOUS` |
| `LINUX_MAP_FIXED` | macro | `kernel/syscalls.c:1967` | `#define LINUX_MAP_FIXED` |
| `LINUX_MAP_PRIVATE` | macro | `kernel/syscalls.c:1966` | `#define LINUX_MAP_PRIVATE` |
| `LINUX_MAP_SHARED` | macro | `kernel/syscalls.c:1965` | `#define LINUX_MAP_SHARED` |
| `LINUX_MREMAP_FIXED` | macro | `kernel/syscalls.c:2277` | `#define LINUX_MREMAP_FIXED` |
| `LINUX_MREMAP_MAYMOVE` | macro | `kernel/syscalls.c:2276` | `#define LINUX_MREMAP_MAYMOVE` |
| `LINUX_NS_PER_S` | macro | `kernel/syscalls.c:2818` | `#define LINUX_NS_PER_S` |
| `LINUX_NS_PER_US` | macro | `kernel/syscalls.c:2816` | `#define LINUX_NS_PER_US` |
| `LINUX_O_APPEND` | macro | `kernel/syscalls.c:1506` | `#define LINUX_O_APPEND` |
| `LINUX_O_CLOEXEC` | macro | `kernel/syscalls.c:1509` | `#define LINUX_O_CLOEXEC` |
| `LINUX_O_DIRECT` | macro | `kernel/syscalls.c:1508` | `#define LINUX_O_DIRECT` |
| `LINUX_O_NONBLOCK` | macro | `kernel/syscalls.c:1507` | `#define LINUX_O_NONBLOCK` |
| `LINUX_O_RDONLY` | macro | `kernel/syscalls.c:1503` | `#define LINUX_O_RDONLY` |
| `LINUX_O_RDWR` | macro | `kernel/syscalls.c:1505` | `#define LINUX_O_RDWR` |
| `LINUX_O_WRONLY` | macro | `kernel/syscalls.c:1504` | `#define LINUX_O_WRONLY` |
| `LINUX_RLIMIT_AS` | macro | `kernel/syscalls.c:2741` | `#define LINUX_RLIMIT_AS` |
| `LINUX_RLIMIT_CPU` | macro | `kernel/syscalls.c:2738` | `#define LINUX_RLIMIT_CPU` |
| `LINUX_RLIMIT_NLIMITS` | macro | `kernel/syscalls.c:2742` | `#define LINUX_RLIMIT_NLIMITS` |
| `LINUX_RLIMIT_NOFILE` | macro | `kernel/syscalls.c:2740` | `#define LINUX_RLIMIT_NOFILE` |
| `LINUX_RLIMIT_PAIR` | macro | `kernel/syscalls.c:2744` | `#define LINUX_RLIMIT_PAIR` |
| `LINUX_RLIMIT_STACK` | macro | `kernel/syscalls.c:2739` | `#define LINUX_RLIMIT_STACK` |
| `LINUX_RLIMIT_TICKS_PER_S` | macro | `kernel/syscalls.c:2746` | `#define LINUX_RLIMIT_TICKS_PER_S` |
| `LINUX_RLIM_INFINITY` | macro | `kernel/syscalls.c:2743` | `#define LINUX_RLIM_INFINITY` |
| `LINUX_SLEEP_MAX_S` | macro | `kernel/syscalls.c:2819` | `#define LINUX_SLEEP_MAX_S` |
| `LINUX_SYSCALL_COUNT` | macro | `kernel/syscalls.c:3368` | `#define LINUX_SYSCALL_COUNT` |
| `LINUX_TCGETS` | macro | `kernel/syscalls.c:2603` | `#define LINUX_TCGETS` |
| `LINUX_TCGETS2` | macro | `kernel/syscalls.c:2609` | `#define LINUX_TCGETS2` |
| `LINUX_TERMIOS2_LEN` | macro | `kernel/syscalls.c:2613` | `#define LINUX_TERMIOS2_LEN` |
| `LINUX_TERMIOS_LEN` | macro | `kernel/syscalls.c:2612` | `#define LINUX_TERMIOS_LEN` |
| `LINUX_TIMER_ABSTIME` | macro | `kernel/syscalls.c:2815` | `#define LINUX_TIMER_ABSTIME` |
| `LINUX_TIOCGWINSZ` | macro | `kernel/syscalls.c:2604` | `#define LINUX_TIOCGWINSZ` |
| `LINUX_UID_GID_ROOT` | macro | `kernel/syscalls.c:3231` | `#define LINUX_UID_GID_ROOT` |
| `LINUX_US_PER_S` | macro | `kernel/syscalls.c:2817` | `#define LINUX_US_PER_S` |
| `LINUX_WINSIZE_LEN` | macro | `kernel/syscalls.c:2611` | `#define LINUX_WINSIZE_LEN` |
| `MINIOS_SYSCALL_BASE` | macro | `kernel/syscalls.c:243` | `#define MINIOS_SYSCALL_BASE` |
| `MINIOS_SYSCALL_COUNT` | macro | `kernel/syscalls.c:244` | `#define MINIOS_SYSCALL_COUNT` |
| `NULL` | function | `kernel/syscalls.c:166` | `* on NULL (already released or never owned). */ void kfd_view_release(proc_t *p)` |
| `PROC_SELF_EXE` | macro | `kernel/syscalls.c:3096` | `#define PROC_SELF_EXE` |
| `SC_EXTRA_COUNT` | macro | `kernel/syscalls.c:3471` | `#define SC_EXTRA_COUNT` |
| `SC_RECORD_LEN` | macro | `kernel/syscalls.c:3532` | `#define SC_RECORD_LEN` |
| `SELECT_NFDS_MAX` | macro | `kernel/syscalls.c:2935` | `#define SELECT_NFDS_MAX` |
| `SELECT_TIMEOUT_MS_MAX` | macro | `kernel/syscalls.c:2940` | `#define SELECT_TIMEOUT_MS_MAX` |
| `SELECT_TIMESPEC_BYTES` | macro | `kernel/syscalls.c:2937` | `#define SELECT_TIMESPEC_BYTES` |
| `SELECT_TIMEVAL_BYTES` | macro | `kernel/syscalls.c:2936` | `#define SELECT_TIMEVAL_BYTES` |
| `SYSCALL_TRACE` | macro | `kernel/syscalls.c:1231` | `#define SYSCALL_TRACE` |
| `SYS_NOISY_GETC_RAW` | macro | `kernel/syscalls.c:1254` | `#define SYS_NOISY_GETC_RAW` |
| `SYS_NOISY_KBD` | macro | `kernel/syscalls.c:1252` | `#define SYS_NOISY_KBD` |
| `SYS_NOISY_MOUSE` | macro | `kernel/syscalls.c:1253` | `#define SYS_NOISY_MOUSE` |
| `SYS_NOISY_TIME` | macro | `kernel/syscalls.c:1251` | `#define SYS_NOISY_TIME` |
| `TRACE_HINT_NONE` | macro | `kernel/syscalls.c:3493` | `#define TRACE_HINT_NONE` |
| `TRACE_HINT_PATH` | macro | `kernel/syscalls.c:3494` | `#define TRACE_HINT_PATH` |
| `answer` | function | `kernel/syscalls.c:3230` | `* made glibc answer (uid_t)-1, which CPython's startup reads. */ #define LINUX_UID_GID_ROOT 0  st...` |
| `batch_kdispatch` | function | `kernel/syscalls.c:814` | `static long batch_kdispatch(uint32_t opcode)` |
| `boot` | function | `kernel/syscalls.c:479` | `* boot (minfo_sleep_init from sched_init);` |
| `by` | function | `kernel/syscalls.c:225` | `* is indexed by (syscall_number - 200). New syscalls are added by: * 1. Adding a MINIOS_SYS_* constant to...` |
| `clock` | function | `kernel/syscalls.c:2859` | `* clock (the monotonic TSC clock times it, as Linux does: glibc sends * every nanosleep here as a relative...` |
| `clock_gettime` | function | `kernel/syscalls.c:2863` | `* clock_gettime(1) reads. */ static long sys_linux_clock_nanosleep(long a1, long a2, long a3, lon...` |
| `cwd` | function | `kernel/syscalls.c:1466` | `* ENAMETOOLONG instead of silently resolving against the cwd (the bug  * that broke shutil.rmtree...` |
| `do_open_kpath` | function | `kernel/syscalls.c:1426` | `static long do_open_kpath(const char *path, long flags)` |
| `do_open_path` | function | `kernel/syscalls.c:1452` | `static long do_open_path(const char *path, long flags)` |
| `fd_write` | function | `kernel/syscalls.c:1327` | `static long fd_write(long fd, const char *buf, long cnt)` |
| `first` | function | `kernel/syscalls.c:2200` | `* passes under mm_lock: validate every page first (present, user,  * private), then apply, so a h...` |
| `gfx_win_title` | variable | `kernel/syscalls.c:703` | `extern const char *gfx_win_title;` |
| `gfx_zoom_2x` | variable | `kernel/syscalls.c:422` | `extern int gfx_zoom_2x;` |
| `k_syscall_spawn` | function | `kernel/syscalls.c:3932` | `static int k_syscall_spawn(const char *path, const char *redirect,                              i...` |
| `kfd_claim` | function | `kernel/syscalls.c:1554` | `static long kfd_claim(KFILE *f)` |
| `kfd_claim_from` | function | `kernel/syscalls.c:1529` | `static long kfd_claim_from(KFILE *f, long minfd, int cloexec)` |
| `kfd_cloexec_get` | function | `kernel/syscalls.c:1612` | `static int kfd_cloexec_get(long fd)` |
| `kfd_cloexec_set` | function | `kernel/syscalls.c:1622` | `static void kfd_cloexec_set(long fd, int on)` |
| `kfd_get` | function | `kernel/syscalls.c:90` | `KFILE *kfd_get(int fd)` |
| `kfd_install` | function | `kernel/syscalls.c:1403` | `static long kfd_install(KFILE *f, int cloexec)` |
| `kfd_poll_revents` | function | `kernel/syscalls.c:1739` | `int kfd_poll_revents(int fd)` |
| `kfd_put` | function | `kernel/syscalls.c:103` | `void kfd_put(KFILE *f)` |
| `kfd_view_cloexec` | function | `kernel/syscalls.c:197` | `void kfd_view_cloexec(void)` |
| `kfd_view_count` | function | `kernel/syscalls.c:115` | `static int kfd_view_count(kfd_view_t *v)` |
| `kfd_view_current` | function | `kernel/syscalls.c:61` | `static kfd_view_t *kfd_view_current(void)` |
| `kfd_view_root` | function | `kernel/syscalls.c:71` | `kfd_view_t *kfd_view_root(void)` |
| `kfile_readable_bytes` | function | `kernel/syscalls.c:2617` | `static int kfile_readable_bytes(KFILE *f)` |
| `kfile_status_flags` | function | `kernel/syscalls.c:1633` | `static long kfile_status_flags(KFILE *f)` |
| `kfile_user_read` | function | `kernel/syscalls.c:1774` | `static long kfile_user_read(KFILE *f, char *buf, long cnt)` |
| `kfile_user_write` | function | `kernel/syscalls.c:1804` | `static long kfile_user_write(KFILE *f, const char *buf, long cnt)` |
| `kiovec` | struct | `kernel/syscalls.c:1229` | `` |
| `ksyscall` | function | `kernel/syscalls.c:3585` | `long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6)` |
| `ksyscall_dispatch` | function | `kernel/syscalls.c:3654` | `static long ksyscall_dispatch(long n, long a1, long a2, long a3, long a4, long a5, long a6)` |
| `linux_timespec_us` | function | `kernel/syscalls.c:2823` | `static long linux_timespec_us(long ts)` |
| `long` | function | `kernel/syscalls.c:2865` | `unsigned long (*now)(void);` |
| `minfo_sleep_init` | function | `kernel/syscalls.c:486` | `void minfo_sleep_init(int tick_ok)` |
| `minfo_tick_wake` | function | `kernel/syscalls.c:491` | `void minfo_tick_wake(void *ctx)` |
| `minios_syscall_entry_t` | struct | `kernel/syscalls.c:238` | `` |
| `mm_ensure_cur` | function | `kernel/syscalls.c:1923` | `static int mm_ensure_cur(unsigned long start, unsigned long end)` |
| `mmap_range_free` | function | `kernel/syscalls.c:1988` | `static int mmap_range_free(unsigned long base, unsigned long len)` |
| `mmap_tag_file` | function | `kernel/syscalls.c:1973` | `static int mmap_tag_file(unsigned long base, int ino, unsigned long off)` |
| `mprotect_pte` | function | `kernel/syscalls.c:2176` | `static volatile unsigned long *mprotect_pte(unsigned long cr3,         unsigned long va)` |
| `node` | function | `kernel/syscalls.c:2322` | `* mapping is one exact live VMA node (what mmap inserts);` |
| `proc_spawn_elf` | function | `kernel/syscalls.c:3923` | `* proc_spawn_elf (the same path mrun uses) and the caller blocks in * do_waitpid, so the parent address space is...` |
| `products` | function | `kernel/syscalls.c:3641` | `* products (writev cnt*sizeof, poll a2*8, spawn (argc+1)*sizeof) are  * pre-bounded against (END-...` |
| `readlink` | function | `kernel/syscalls.c:3801` | `* readlink (89). */ return readlink_path((const char *)a2, (char *)a3, a4);` |
| `readlink_path` | function | `kernel/syscalls.c:3101` | `static long readlink_path(const char *path, char *buf, long bufsz)` |
| `rmdir_kpath` | function | `kernel/syscalls.c:3299` | `static long rmdir_kpath(const char *path)` |
| `sb16_audio_device` | function | `kernel/syscalls.c:669` | `static device_t *sb16_audio_device(void)` |
| `sc_extra_name` | struct | `kernel/syscalls.c:3455` | `` |
| `sc_hex` | function | `kernel/syscalls.c:3557` | `static void sc_hex(unsigned long v)` |
| `sc_log` | struct | `kernel/syscalls.c:3534` | `` |
| `sc_record` | struct | `kernel/syscalls.c:3533` | `` |
| `sc_record` | function | `kernel/syscalls.c:3537` | `static void sc_record(long n, long a1, long a2, long a3, long ret)` |
| `sc_record_dump` | function | `kernel/syscalls.c:3567` | `void sc_record_dump(int pid)` |
| `select_timeout_ms` | function | `kernel/syscalls.c:2946` | `static int select_timeout_ms(const long *t, int pselect, long *out)` |
| `split` | function | `kernel/syscalls.c:2126` | `* hold a split (the mapping is restored untouched). */ static long sys_linux_munmap(long a1, long...` |
| `sys_linux_accept` | function | `kernel/syscalls.c:2717` | `static long sys_linux_accept(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_access` | function | `kernel/syscalls.c:2673` | `static long sys_linux_access(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_arch_prctl` | function | `kernel/syscalls.c:3194` | `static long sys_linux_arch_prctl(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_bind` | function | `kernel/syscalls.c:2706` | `static long sys_linux_bind(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_brk` | function | `kernel/syscalls.c:1932` | `static long sys_linux_brk(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_close` | function | `kernel/syscalls.c:1882` | `static long sys_linux_close(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_close_range` | function | `kernel/syscalls.c:1694` | `static long sys_linux_close_range(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_connect` | function | `kernel/syscalls.c:2700` | `static long sys_linux_connect(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_dup` | function | `kernel/syscalls.c:1833` | `static long sys_linux_dup(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_dup2` | function | `kernel/syscalls.c:1848` | `static long sys_linux_dup2(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_dup3` | function | `kernel/syscalls.c:1684` | `static long sys_linux_dup3(long a1, long a2, long a3, long a4, long a5, long a6)` |

Next: [SYMBOLS_p10.md](SYMBOLS_p10.md)
