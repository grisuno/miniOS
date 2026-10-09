# Subsystem: kernel (page 2 of 4)
Previous: [KB_kernel.md](KB_kernel.md)

## kernel/redirect.c
- Layer: utility
- Language: c
- Symbols:
  - `shell_report_exit` (function, line 11) `void shell_report_exit(int code)`
  - `shell_report` (function, line 17) `void shell_report(const char *what, const char *detail)`
  - `shell_take_redirect` (function, line 25) `int shell_take_redirect(int *argc, char **argv, char **path, int *append_mode)`

## kernel/sched.c
- Doc: trap_frame_t: if (len == 0 || len > 256) { kprintf("gdb: dump length 1..256 (got %lu)\n", len)...
- Layer: utility
- Language: c
- Symbols:
  - `stop_row` (struct, line 415)
  - `trap_frame_t` (struct, line 565)
  - `res0` (type_alias, line 108) `typedef struct __attribute__((packed)) { uint32_t res0;`
  - `off_lo` (type_alias, line 136) `typedef struct __attribute__((packed)) { uint16_t off_lo;`
  - `sched_tick_audio` (function, line 25) `static void sched_tick_audio(void *ctx)`
  - `sched_tick_desktop` (function, line 31) `static void sched_tick_desktop(void *ctx)`
  - `sched_tick_usb` (function, line 42) `static void sched_tick_usb(void *ctx)`
  - `read_cr3` (function, line 73) `static inline unsigned long read_cr3(void)`
  - `__attribute__` (function, line 108) `typedef struct __attribute__((packed))`
  - `__attribute__` (function, line 136) `typedef struct __attribute__((packed))`
  - `kstack_paint` (function, line 164) `static void kstack_paint(uint64_t top, unsigned long size)`
  - `kstack_usage` (function, line 173) `static int kstack_usage(uint64_t top, unsigned long size,
                        unsigned long *...`
  - `alloc_kstack` (function, line 188) `static uint64_t alloc_kstack(void)`
  - `live` (function, line 204) `* every reap leaked its own stack and released a neighbour that could
 * still be live (two procs...`
  - `MXCSR` (function, line 224) `* A fresh image is explicit zeros plus the default MXCSR (0x1F80, all
 * exceptions masked): fxsa...`
  - `fpu_restore_from` (function, line 232) `static inline void fpu_restore_from(void *area)`
  - `fpu_alloc_clean` (function, line 236) `static void *fpu_alloc_clean(void)`
  - `fpu_free_proc` (function, line 254) `static void fpu_free_proc(proc_t *p)`
  - `vma_ctx_alloc` (function, line 260) `vma_ctx_t *vma_ctx_alloc(void)`
  - `vma_ctx_free` (function, line 270) `void vma_ctx_free(vma_ctx_t *c)`
  - `copy` (function, line 280) `* copy (fail closed, fork refuses) instead of forging pointers. */
static vma_ctx_t *vma_ctx_copy...`
  - `vma_owned` (function, line 352) `static int vma_owned(proc_t *p)`
  - `vma_save_proc` (function, line 360) `static void vma_save_proc(proc_t *p)`
  - `vma_load_proc` (function, line 364) `static void vma_load_proc(proc_t *p)`
  - `kstack_report` (function, line 371) `void kstack_report(void)`
  - `schedtop_report` (function, line 414) `void schedtop_report(void)`
  - `irqstat_report` (function, line 482) `void irqstat_report(void)`
  - `stub` (function, line 501) `* gdb stub (`make gdb`, then `target remote :1234` from the host). These
 * helpers are the seria...`
  - `gdb_dump_report` (function, line 548) `void gdb_dump_report(unsigned long addr, unsigned long len)`
  - `idt_set` (function, line 581) `static void idt_set(int vec, void (*h)(void))`
  - `idt_init` (function, line 592) `static void idt_init(void)`
  - `pic_init` (function, line 604) `static void pic_init(void)`
  - `pit_init` (function, line 639) `static void pit_init(void)`
  - `pic_eoi` (function, line 646) `static void pic_eoi(int irq)`
  - `tss_write_desc` (function, line 653) `static void tss_write_desc(int cpu)`
  - `tss_init` (function, line 670) `static void tss_init(void)`
  - `tss_init_ap` (function, line 701) `void tss_init_ap(int cpu)`
  - `context` (function, line 719) `* context (anything entered via k_exec_user) is inside a syscall
 * (entry swapped 0 in), and a c...`
  - `point` (function, line 732) `* return address as the resume point ("continue the ISR"), which
 * required the stranded ISR fra...`
  - `sched_next_locked` (function, line 761) `static int sched_next_locked(int start, int vm_only)`
  - `sched_set_nice` (function, line 779) `int sched_set_nice(int pid, int nice)`
  - `seccomp_deny_one` (function, line 788) `int seccomp_deny_one(int pid, int n)`
  - `seccomp_allow_one` (function, line 795) `int seccomp_allow_one(int pid, int n)`
  - `seccomp_denied` (function, line 802) `int seccomp_denied(int pid, int n)`
  - `smp_try_claim_hint` (function, line 811) `static int smp_try_claim_hint(int pid, int vm_only)`
  - `smp_claim_thread_v` (function, line 827) `static int smp_claim_thread_v(int vm_only)`
  - `smp_ap_idle_loop` (function, line 866) `void smp_ap_idle_loop(void)`
  - `sched_ap_preempt` (function, line 900) `static void sched_ap_preempt(trap_frame_t *frame)`
  - `smp_any_ap_idle` (function, line 970) `static int smp_any_ap_idle(void)`
  - `rlimit_cpu_exceeded` (function, line 1006) `int rlimit_cpu_exceeded(int pid)`
  - `isr_dispatch` (function, line 1027) `void isr_dispatch(int vector, trap_frame_t *frame)`
  - `BSP` (function, line 1606) `* CPU believe it is the BSP (wrong per-CPU identity, two CPUs
         * running the shell contex...`
  - `proc_get` (function, line 1631) `proc_t *proc_get(int pid)`
  - `proc_create` (function, line 1637) `int proc_create(const char *name, int parent_pid)`
  - `proc_spawn_elf_inner` (function, line 1755) `static int proc_spawn_elf_inner(const char *name, void *data, unsigned size,
                   i...`
  - `proc_spawn_elf` (function, line 1915) `int proc_spawn_elf(const char *name, void *data, unsigned size,
                   int argc, char...`
  - `schedule` (function, line 1957) `* that keeps schedule()'s own rbp runs the caller's frame accesses
 * (locals, leave/ret) on the ...`
  - `schedule` (function, line 1964) `void schedule(void)`
  - `yield` (function, line 2046) `void yield(void)`
  - `do_exit` (function, line 2061) `void do_exit(int code)`
  - `do_thread_spawn` (function, line 2115) `long do_thread_spawn(unsigned long fn, unsigned long stack,
                     unsigned long arg)`
  - `itself` (function, line 2315) `* the shell itself (use mrun first), and a CLONE_VM thread forking
 * would duplicate shared stat...`
  - `ctx_from_frame` (function, line 2337) `static void ctx_from_frame(ctx_regs_t *c, const syscall_frame_t *f)`
  - `fork_child_settid` (function, line 2355) `void fork_child_settid(void)`
  - `do_fork` (function, line 2364) `long do_fork(void)`
  - `do_fork_ex` (function, line 2368) `long do_fork_ex(uint64_t set_tid, uint64_t clear_tid)`
  - `do_clone_thread` (function, line 2504) `static long do_clone_thread(unsigned long flags, unsigned long newsp,
                           ...`
  - `kill_group_threads_locked` (function, line 2618) `static void kill_group_threads_locked(int tgid, int except)`
  - `do_exit_group_threads` (function, line 2632) `void do_exit_group_threads(void)`
  - `aslr_mix` (function, line 2648) `static unsigned long aslr_mix(unsigned long salt)`
  - `aslr_stack_bytes` (function, line 2657) `unsigned long aslr_stack_bytes(void)`
  - `aslr_brk_pages` (function, line 2658) `unsigned long aslr_brk_pages(void)`
  - `aslr_mmap_pages` (function, line 2659) `unsigned long aslr_mmap_pages(void)`
  - `aslr_dyn_base` (function, line 2660) `unsigned long aslr_dyn_base(void)`
  - `do_execve` (function, line 2687) `long do_execve(char *kpath, int kargc, char **kargv)`
  - `proc_running_anywhere` (function, line 2917) `static int proc_running_anywhere(int pid)`
  - `reap_autoreap_locked` (function, line 2926) `static void reap_autoreap_locked(int tgid)`
  - `alloc_pid_locked` (function, line 2938) `static int alloc_pid_locked(void)`
  - `waitpid_scan` (function, line 2946) `static int waitpid_scan(int pid, int *found)`
  - `do_waitpid` (function, line 2965) `int do_waitpid(int pid)`
  - `waitpid_has_child` (function, line 2982) `static int waitpid_has_child(int pid)`
  - `do_waitpid_linux` (function, line 2996) `int do_waitpid_linux(int pid, int nohang, int *found)`
  - `shell_reap_nb` (function, line 3013) `int shell_reap_nb(int *pid_out, int *code_out)`
  - `shell_reap_one` (function, line 3027) `int shell_reap_one(int pid, int *code_out)`
  - `shell_nchildren` (function, line 3039) `int shell_nchildren(void)`
  - `do_kill` (function, line 3065) `int do_kill(int pid)`
  - `timer_tick` (function, line 3091) `void timer_tick(void)`
  - `sched_init` (function, line 3096) `void sched_init(void)`
  - `user_trampoline` (function, line 65) `extern void user_trampoline(void);`
  - `fork_trampoline` (function, line 66) `extern void fork_trampoline(void);`
  - `exec_enter` (function, line 71) `extern void exec_enter(unsigned long frame);`
  - `PROC_KSTACK_OFF` (function, line 81) `* PROC_KSTACK_OFF (it cannot use C here). The asm derives both * immediates from headers/syscall_asm.h, so this...`
  - `descriptor` (function, line 96) `* descriptor (two slots) per CPU past the 5 stage-2 entries. */ _Static_assert((5 + 2 * MAX_CPUS) * 8 ==...`
  - `here` (function, line 121) `* smp_ap_idle_loop here (idle_proc ctx.rsp points at the top). */ static char ap_idle_stack[MAX_CPUS][4096]...`
  - `sched_lock` (function, line 358) `* hold sched_lock (+mm_lock at the swap sites);`
  - `slot` (function, line 418) `* must not eat a quarter of a 16 KB slot (see the stack discipline * contract in CLAUDE.md). Fail-closed on OOM. */...`
  - `sys_ticks` (function, line 478) `* sys_ticks (PIT 100 Hz on the BSP, broadcast as IPIs to APs);`
  - `rtl_counters` (function, line 485) `extern void rtl_counters(unsigned int *tx_frames, unsigned int *rx_frames);`
  - `rtl_present` (function, line 487) `extern int rtl_present(void);`
  - `IRQ4` (function, line 628) `* IRQ4 (COM1, UART IER stays 0 so it never fires) + * IRQ5 (Sound Blaster 16 DMA done). In the mask register a bit...`
  - `FSBASE` (function, line 744) `* for FSBASE (per-proc TLS): a thread preempted after arch_prctl * would otherwise resume with whatever base the...`
  - `syscall` (function, line 1151) `* outgoing syscall (see sched_rearm_kgs). Without * this the next entry swapgs puts garbage under GS * and the pid...`
  - `PROC_SWITCHING` (function, line 1990) `* while the thread is still PROC_SWITCHING (never claimable), * then set the resume point and publish. A...`
  - `returns` (function, line 2054) `* that returns (and the resumed thread returns with IF=1). */ __asm__ volatile("cli");`
  - `registers` (function, line 2146) `* registers (float args would need XMM inheritance, which the * arg-passing contract does not carry: fn takes one...`
  - `MSR` (function, line 2418) `* in the MSR (the PCB field refreshes on switch-out) and its FPU * regs live in the CPU (the PCB image refreshes on...`
  - `cli` (function, line 2669) `* cli (disk PIO must never run with the timer held off);`
  - `adopt` (function, line 2683) `* adopt (armed by Linux O_CLOEXEC on open);`
  - `it` (function, line 3104) `* it (SPAWN/exec point proc 0 here transiently);`
  - `park` (function, line 3155) `* an image its live FPU registers would be dropped by the preempt * park (the save path skips a null area). */...`
  - `zeroed` (function, line 3165) `* still zeroed (kmemset happens inside idt_init) faults through a * null gate. Handlers for 32/33/44 are safe...`
  - `sc_top_save` (variable, line 68) `extern unsigned long sc_top_save[];`
  - `isr_stub_table` (variable, line 145) `extern void *isr_stub_table[];`
  - `net_rx_dropped` (variable, line 486) `extern unsigned int net_rx_dropped;`
  - `mm_lock` (variable, line 713) `extern spinlock_t mm_lock;`
  - `MY_SYS_KSTK_TOP` (macro, line 52) `#define MY_SYS_KSTK_TOP`
  - `MY_USER_STACK_TOP` (macro, line 53) `#define MY_USER_STACK_TOP`
  - `MY_USER_LOAD_BASE` (macro, line 54) `#define MY_USER_LOAD_BASE`
  - `KSTACK_SZ` (macro, line 148) `#define KSTACK_SZ`
  - `KSTACK_PAINT` (macro, line 161) `#define KSTACK_PAINT`
  - `KSTACK_CANARY` (macro, line 162) `#define KSTACK_CANARY`
- Depends on: `headers/arch/x86/boot/bootdefs.h`, `headers/arch/x86/hal_io.h`, `headers/arch/x86/msr.h`, `headers/drivers/mouse.h`, `headers/drivers/xhci.h`, `headers/futex.h`, `headers/pcache.h`, `headers/pcm2.h`, `headers/percpu_rq.h`, `headers/proc_sec.h`, `headers/rcu.h`, `headers/sb16.h`, `headers/sched.h`, `headers/smp.h`, `headers/spawn.h`, `headers/sync.h`, `headers/tick.h`, `headers/vga_fb.h`

## kernel/scrollback.c
- Doc: Console scrollback ring buffer.
- Layer: utility
- Language: c
- Symbols:
  - `sb_init` (function, line 17) `void sb_init(void)`
  - `sb_capture_row0` (function, line 23) `void sb_capture_row0(void)`
  - `sb_reset` (function, line 34) `void sb_reset(void)`
  - `sb_get_count` (function, line 38) `int sb_get_count(void)`
  - `sb_get_head` (function, line 39) `int sb_get_head(void)`
  - `sb_get_char` (function, line 41) `char sb_get_char(int row, int col)`
  - `vga_scroll` (function, line 4) `* Captured lazily from vga_scroll();`
  - `SCROLLBACK_ROWS` (macro, line 12) `#define SCROLLBACK_ROWS`

## kernel/seccomp_bpf.c
- Doc: Docstring: seccomp_bpf.c -- classic BPF checker and interpreter for Linux
- Layer: utility
- Language: c
- Symbols:
  - `sbpf_opcode_ok` (function, line 17) `static int sbpf_opcode_ok(const sbpf_insn *in)`
  - `sbpf_check` (function, line 69) `int sbpf_check(const sbpf_insn *prog, unsigned len, unsigned short *scratch)`
  - `sbpf_load_word` (function, line 114) `static unsigned int sbpf_load_word(const sbpf_data *d, unsigned off)`
  - `sbpf_run` (function, line 120) `unsigned int sbpf_run(const sbpf_insn *prog, unsigned len, const sbpf_data *d)`
  - `sbpf_action_rank` (function, line 194) `int sbpf_action_rank(unsigned int action)`
  - `SBPF_OP_MASK` (macro, line 8) `#define SBPF_OP_MASK`
  - `SBPF_SRC_MASK` (macro, line 9) `#define SBPF_SRC_MASK`
  - `SBPF_SIZE_MASK` (macro, line 10) `#define SBPF_SIZE_MASK`
  - `SBPF_MODE_MASK` (macro, line 11) `#define SBPF_MODE_MASK`
  - `SBPF_RVAL_MASK` (macro, line 12) `#define SBPF_RVAL_MASK`
  - `SBPF_MISC_MASK` (macro, line 13) `#define SBPF_MISC_MASK`
  - `SBPF_MEM_ALL` (macro, line 14) `#define SBPF_MEM_ALL`
- Depends on: `headers/seccomp_bpf.h`

## kernel/serial.c
- Doc: COM1 16550 UART driver.
- Layer: utility
- Language: c
- Symbols:
  - `serial_init` (function, line 20) `void serial_init(void)`
  - `serial_tx_ready` (function, line 30) `static int serial_tx_ready(void)`
  - `serial_rx_ready` (function, line 31) `static int serial_rx_ready(void)`
  - `serial_putc` (function, line 33) `void serial_putc(char c)`
  - `serial_e_count` (function, line 38) `unsigned long serial_e_count(void)`
  - `serial_puts` (function, line 40) `void serial_puts(const char *s)`
  - `serial_available` (function, line 42) `int serial_available(void)`
  - `serial_getc` (function, line 44) `int serial_getc(void)`
  - `COM1` (macro, line 18) `#define COM1`
- Depends on: `headers/sched.h`

## kernel/shell.c
- Doc: ShellRunDir: Runnable-file lookup: a bare name is mapped to a toolchain directory by its suffix...
- Layer: utility
- Language: c
- Symbols:
  - `job_row` (struct, line 2020)
  - `ps_row` (struct, line 3656)
  - `ShellRunDir` (struct, line 58)
  - `shell_queue_launch` (function, line 84) `void shell_queue_launch(const char *cmd)`
  - `shell_readline_active` (function, line 112) `int shell_readline_active(void)`
  - `shell_focus_park` (function, line 113) `void shell_focus_park(void)`
  - `shell_focus_restore` (function, line 118) `void shell_focus_restore(void)`
  - `shell_prompt` (function, line 145) `static void shell_prompt(void)`
  - `shell_parse_vol` (function, line 155) `static int shell_parse_vol(const char *s, unsigned *out)`
  - `shell_readline_buf` (function, line 181) `void shell_readline_buf(char *buf, int size)`
  - `shell_name_base` (function, line 210) `static const char *shell_name_base(const char *path)`
  - `shell_complete_tier` (function, line 235) `static int shell_complete_tier(const char *nm)`
  - `shell_complete_replace` (function, line 247) `static void shell_complete_replace(char *buf, int size, int *pos,
                               ...`
  - `shell_complete_minifs_arg` (function, line 268) `static void shell_complete_minifs_arg(const char *word, unsigned long wlen,
                     ...`
  - `shell_readline` (function, line 335) `static void shell_readline(void)`
  - `shell_hist_show` (function, line 343) `static void shell_hist_show(char *buf, int size, int *pos, const char *text)`
  - `shell_line_repaint` (function, line 365) `static void shell_line_repaint(char *buf, int size, int pos)`
  - `shell_line_insert` (function, line 378) `static void shell_line_insert(char *buf, int size, int *pos, char c)`
  - `shell_line_backspace` (function, line 387) `static void shell_line_backspace(char *buf, int size, int *pos)`
  - `shell_line_delete` (function, line 395) `static void shell_line_delete(char *buf, int size, int *pos)`
  - `shell_line_kill_front` (function, line 402) `static void shell_line_kill_front(char *buf, int size, int *pos)`
  - `shell_line_kill_tail` (function, line 409) `static void shell_line_kill_tail(char *buf, int size, int *pos)`
  - `shell_line_kill_word` (function, line 414) `static void shell_line_kill_word(char *buf, int size, int *pos)`
  - `shell_hist_newest_match` (function, line 426) `static int shell_hist_newest_match(const char *prefix, unsigned long plen)`
  - `line` (function, line 443) `* to the live line (handled by the caller resetting shell_hist_idx). */
static void shell_hist_na...`
  - `shell_readline_hist` (function, line 488) `static void shell_readline_hist(char *buf, int size)`
  - `shell_parse` (function, line 808) `int shell_parse(char *line, char **argv, int max_args)`
  - `shell_run_init` (function, line 837) `static void shell_run_init(void)`
  - `shell_run` (function, line 876) `void shell_run(void)`
  - `shell_load` (function, line 946) `static int shell_load(const char *fname, char *progname_out, void **entry_out)`
  - `outw_port` (function, line 1009) `static inline void outw_port(unsigned short port, unsigned short val)`
  - `shell_cmd_poweroff` (function, line 1015) `static void shell_cmd_poweroff(void)`
  - `shell_run_dir_for` (function, line 1031) `static const ShellRunDir *shell_run_dir_for(const char *name)`
  - `shell_file_is_real` (function, line 1049) `static int shell_file_is_real(const char *resolved)`
  - `shell_resolve_run` (function, line 1061) `static int shell_resolve_run(const char *name, char *out, unsigned cap)`
  - `etrel_path_trusted` (function, line 1103) `static int etrel_path_trusted(const char *full)`
  - `shell_run_elf_buf_path` (function, line 1117) `static int shell_run_elf_buf_path(const char *data, unsigned size, int argc,
                    ...`
  - `shell_run_elf_file` (function, line 1147) `static int shell_run_elf_file(const char *full, int argc, char **argv)`
  - `shell_run_elf_minifs` (function, line 1160) `static int shell_run_elf_minifs(const char *name, int argc, char **argv)`
  - `shell_run_cvm` (function, line 1210) `static int shell_run_cvm(const char *full, int argc, char **argv)`
  - `shell_run_file` (function, line 1246) `static int shell_run_file(const char *name, int argc, char **argv)`
  - `shell_read_elf_bytes` (function, line 1290) `static int shell_read_elf_bytes(const char *name, unsigned char **out,
                          ...`
  - `code` (function, line 1356) `* the last exit code (130 when interrupted). */
static int shell_wait_fg(int *pids, int n, int ki...`
  - `shell_cmd_mrun` (function, line 1409) `static void shell_cmd_mrun(int argc, char **argv)`
  - `shell_run_bg` (function, line 1457) `static void shell_run_bg(const char *name, int argc, char **argv)`
  - `desktop_path` (function, line 1500) `static void desktop_path(const char *name, char *dst, unsigned cap)`
  - `desktop_flag` (function, line 1509) `static void desktop_flag(const char *name)`
  - `desktop_flag_on` (function, line 1519) `static int desktop_flag_on(const char *name)`
  - `flows` (function, line 1533) `* and external flows (make wl) set it themselves. */
static void desktop_unflag(const char *name)`
  - `desktop_srv_alive` (function, line 1541) `static int desktop_srv_alive(void)`
  - `shell_cmd_desktop` (function, line 1557) `static void shell_cmd_desktop(int argc, char **argv)`
  - `shell_run_any` (function, line 1621) `int shell_run_any(const char *name, int argc, char **argv)`
  - `gfx_parse_int` (function, line 1692) `static int gfx_parse_int(const char *s, int *out)`
  - `gfx_read_palette` (function, line 1712) `static void gfx_read_palette(unsigned char pal[768])`
  - `shell_cmd_gfx` (function, line 1719) `static void shell_cmd_gfx(int argc, char **argv)`
  - `shell_cmd_wm` (function, line 1871) `static void shell_cmd_wm(int argc, char **argv)`
  - `tree` (function, line 2006) `* tree (mmap-heavy jobs stay best-effort), legacy blocking `run` ignores
 * Ctrl+C (it never poll...`
  - `shell_cmd_jobs` (function, line 2019) `static void shell_cmd_jobs(void)`
  - `shell_has_child` (function, line 2048) `static int shell_has_child(int pid)`
  - `shell_cmd_wait` (function, line 2058) `static void shell_cmd_wait(int argc, char **argv)`
  - `shell_cmd_kill` (function, line 2093) `static void shell_cmd_kill(int argc, char **argv)`
  - `shell_cmd_mem` (function, line 2116) `static void shell_cmd_mem(void)`
  - `VMA` (function, line 2149) `* plus the live VMA (mmap) tree. The walk is bounded (64-deep explicit
 * stack, 128 regions prin...`
  - `to` (function, line 2222) `* actually trap to (brk/mmap/munmap/mprotect) and says so up front. */
static void shell_cmd_trac...`
  - `shell_parse_u64` (function, line 2291) `static int shell_parse_u64(const char *s, unsigned long *out)`
  - `shell_parse_long` (function, line 2307) `int shell_parse_long(const char *s, long *out)`
  - `shell_parse_pid` (function, line 2328) `int shell_parse_pid(const char *s, int min_pid, int *out)`
  - `shell_cmd_gdb` (function, line 2343) `static void shell_cmd_gdb(int argc, char **argv)`
  - `shell_cmd_hash` (function, line 2386) `static void shell_cmd_hash(int argc, char **argv)`
  - `shell_resolve_arg` (function, line 2405) `static int shell_resolve_arg(const char *cmd, const char *arg,
                             const...`
  - `shell_httpd_one` (function, line 2511) `static void shell_httpd_one(int child, const char *root)`
  - `shell_httpd_serve` (function, line 2596) `static void shell_httpd_serve(unsigned short port, const char *root,
        int max_conn)`
  - `shell_cross_ls` (function, line 2763) `static void shell_cross_ls(const char *drv, const char *imgarg,
                           const ...`
  - `shell_cross_cat` (function, line 2804) `static void shell_cross_cat(const char *drv, const char *imgarg,
                            cons...`
  - `shell_exec_builtin` (function, line 2846) `void shell_exec_builtin(int argc, char **argv)`
  - `driver` (function, line 3264) `* stream through the fat: VFS driver ("img:fatpath" per open,
     * registered at boot beside me...`
  - `shell_is_pipe_tok` (function, line 4020) `static int shell_is_pipe_tok(const char *a)`
  - `shell_run_stage` (function, line 4059) `static char *shell_run_stage(char **sargv, int sargc,
        const char *input, unsigned long in...`
  - `shell_run_pipeline` (function, line 148) `static int shell_run_pipeline(char **argv, int argc, const char *redir_path, int redir_append, int redirected);`
  - `root` (function, line 648) `* MiniFS root (where the big ELFs live under bare names), * and only the highest-priority non-empty tier is kept. An...`
  - `desktop_unflag` (function, line 830) `static void desktop_unflag(const char *name);`
  - `window` (function, line 1283) `* window (proc_spawn_elf) and waits for all of them. The 100 Hz timer * preempts the BSP across the READY set, so...`
  - `this` (function, line 1487) `* boot into the tiled Wayland desktop: every NK app started after * this (paint, vedit, file, nuklear, doomedit...`
  - `context` (function, line 1647) `* from ISR context (which corrupts the running program's state). */ shell_queue_launch(cmd);`
  - `terminal` (function, line 2921) `* sequence clears serial consoles and is swallowed without * garbage by the framebuffer terminal (vedit pattern). */...`
  - `frame` (function, line 3658) `* not live in this frame (stack discipline, CLAUDE.md). */ struct ps_row *snap = (struct ps_row...`
  - `stdout` (function, line 4008) `* the pipe exactly like stdout (`2>` is an alias of `>`). * Per-stage `exit code:` lines report to the console...`
  - `XXH_STATIC_LINKING_ONLY` (macro, line 25) `#define XXH_STATIC_LINKING_ONLY`
  - `SHELL_CVM_INTERP` (macro, line 50) `#define SHELL_CVM_INTERP`
  - `SHELL_RUN_DIRS` (macro, line 69) `#define SHELL_RUN_DIRS`
  - `SHELL_HIST_MAX` (macro, line 95) `#define SHELL_HIST_MAX`
  - `SHELL_BUILTIN_COUNT` (macro, line 229) `#define SHELL_BUILTIN_COUNT`
  - `QEMU_PM_PORT` (macro, line 1013) `#define QEMU_PM_PORT`
  - `HTTPD_REQ_CAP` (macro, line 2504) `#define HTTPD_REQ_CAP`
  - `HTTPD_IO_CHUNK` (macro, line 2505) `#define HTTPD_IO_CHUNK`
  - `SHELL_LS_CAP` (macro, line 2762) `#define SHELL_LS_CAP`
  - `PIPE_HOP_MAX` (macro, line 4018) `#define PIPE_HOP_MAX`
- Depends on: `headers/drivers/kbd.h`, `headers/drivers/nvme.h`, `headers/drivers/usbblk.h`, `headers/drivers/usbhid.h`, `headers/drivers/virtio_blk.h`, `headers/drivers/virtio_net.h`, `headers/drivers/xhci.h`, `headers/editor.h`, `headers/ext4.h`, `headers/fat32.h`, `headers/httpd.h`, `headers/kernel/console_in.h`, `headers/minifetch.h`, `headers/minifs.h`, `headers/net.h`, `headers/pcache.h`, `headers/pcm2.h`, `headers/pcspk.h`, `headers/percpu_rq.h`, `headers/rtc.h`, `headers/sb16.h`, `headers/sched.h`, `headers/shell.h`, `headers/smp.h`, `headers/vga_fb.h`, `headers/wm_layout.h`, `headers/wm_notify.h`, `headers/zip.h`

## kernel/spawn.c
- Doc: Docstring: Save the caller shared-window view into ctx.
- Layer: utility
- Language: c
- Symbols:
  - `spawn_backup` (function, line 11) `int spawn_backup(spawn_ctx_t *ctx)`
  - `spawn_restore` (function, line 37) `void spawn_restore(spawn_ctx_t *ctx)`
  - `spawn_free_argv` (function, line 84) `void spawn_free_argv(char **kargv, int argc)`
  - `spawn_copy_argv` (function, line 96) `char **spawn_copy_argv(int argc, const char **uargv)`
  - `spawn_validate_argv` (function, line 140) `int spawn_validate_argv(int argc, const char **uargv)`
  - `spawn_load_image` (function, line 158) `unsigned char *spawn_load_image(const char *resolved, unsigned *size_out)`
  - `spawn_run_rel` (function, line 193) `static int spawn_run_rel(const char *resolved, const char *redirect,
                         uns...`
  - `spawn_run_exec` (function, line 219) `static int spawn_run_exec(const char *resolved, const char *redirect,
                           ...`
  - `spawn_execute` (function, line 264) `int spawn_execute(const char *resolved, const char *redirect,
                  unsigned char *da...`
- Depends on: `headers/arch/x86/msr.h`, `headers/arena.h`, `headers/minifs.h`, `headers/sched.h`, `headers/spawn.h`, `headers/vga_fb.h`, `headers/vma.h`

## kernel/string.c
- Doc: Kernel string and memory functions.
- Layer: utility
- Language: c
- Symbols:
  - `kstrlen` (function, line 17) `unsigned long kstrlen(const char *s)`
  - `kstrcpy` (function, line 23) `char *kstrcpy(char *dst, const char *src)`
  - `kstrncpy` (function, line 29) `char *kstrncpy(char *dst, const char *src, unsigned long n)`
  - `kstrncat` (function, line 35) `char *kstrncat(char *dst, const char *src, unsigned long n)`
  - `kstrcmp` (function, line 43) `int kstrcmp(const char *a, const char *b)`
  - `kstrncmp` (function, line 48) `int kstrncmp(const char *a, const char *b, unsigned long n)`
  - `kstrchr` (function, line 53) `char *kstrchr(const char *s, int c)`
  - `kstrstr` (function, line 58) `char *kstrstr(const char *hay, const char *ndl)`
  - `kmemcpy` (function, line 68) `void *kmemcpy(void *dst, const void *src, unsigned long n)`
  - `kmemset` (function, line 75) `void *kmemset(void *dst, int c, unsigned long n)`
  - `kmemcmp` (function, line 81) `int kmemcmp(const void *a, const void *b, unsigned long n)`
  - `kmemmove` (function, line 87) `void *kmemmove(void *dst, const void *src, unsigned long n)`
  - `katol` (function, line 95) `long katol(const char *s)`
- Imported by: `headers/leakcheck.h`, `headers/tls_port.h`, `progs/doomedit/doomedit.c`, `progs/doomgeneric/d_iwad.c`, `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomgeneric_minios.c`, `progs/doomgeneric/doomgeneric_soso.c`, `progs/doomgeneric/doomgeneric_sosox.c`, `progs/doomgeneric/doomgeneric_xlib.c`, `progs/doomgeneric/f_wipe.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/gusconf.c`, `progs/doomgeneric/i_endoom.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_joystick.c`, `progs/doomgeneric/i_minios_sound.c`, `progs/doomgeneric/i_scale.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/m_argv.c`, `progs/doomgeneric/m_cheat.c`, `progs/doomgeneric/m_config.c`, `progs/doomgeneric/m_misc.c`, `progs/doomgeneric/memio.c`, `progs/doomgeneric/sha1.c`, `progs/doomgeneric/statdump.c`, `progs/doomgeneric/v_video.c`, `progs/doomgeneric/w_checksum.c`, `progs/doomgeneric/w_wad.c`, `progs/file/file.c`, `progs/file/file_assoc.h`, `progs/freedomui/freedomui_minios.c`, `progs/freedomui/media_unavailable.c`, `progs/freedomui/platform_minios.c`, `progs/freedomui/ps2_keymap.c`, `progs/lisp/lisp.c`, `progs/lua/lua_main.c`, `progs/minicraft/minicraft.c`, `progs/nuklear/cvm_emit.c`, `progs/nuklear/node_editor.c`, `progs/nuklear/nuklear_minios.c`, `progs/nuklear/nuklear_theme.c`, `progs/paint/paint.c`, `progs/piano/piano.c`, `progs/pokemon/platform_minios.c`, `progs/quake2generic/q2generic_minios.c`, `progs/quake2generic/snddma_minios.c`, `progs/src/freedom.c`, `progs/src/freedom_wl.c`, `progs/src/lxabi.c`, `progs/src/lxnet.c`, `progs/src/lxsecc.c`, `progs/src/opl3.c`, `progs/tls_u/tls_u_main.c`, `progs/tls_u/tls_u_port.c`, `progs/topogpt3/topogpt3.c`, `progs/vedit/vedit.c`, `progs/wl/wl_pixbuf.h`, `progs/wl/wlcomp.c`, `tests/stubs/kernel.h`, `tests/test_arena.c`, `tests/test_driver.c`, `tests/test_ext4.c`, `tests/test_fat32.c`, `tests/test_fault.c`, `tests/test_file_assoc.c`, `tests/test_freedomui.c`, `tests/test_httpd.c`, `tests/test_ldso.c`, `tests/test_leakcheck.c`, `tests/test_minios_png.c`, `tests/test_paint.c`, `tests/test_pcache.c`, `tests/test_pcm.c`, `tests/test_ps2_keymap.c`, `tests/test_sanitize.c`, `tests/test_seccomp_bpf.c`, `tests/test_theme.c`, `tests/test_usbhid.c`, `tests/test_vedit_build.c`, `tests/test_wl.c`, `tests/test_xhci.c`, `tls_test.c`

## kernel/symtab.c
- Layer: utility
- Language: c
- Symbols:
  - `k_register_symbol` (function, line 10) `void k_register_symbol(const char *name, void *addr)`
  - `ksym_resolve` (function, line 18) `void *ksym_resolve(const char *name)`
  - `kprog_slot` (function, line 34) `KProg *kprog_slot(const char *name)`
  - `kprog_lookup` (function, line 42) `KProg *kprog_lookup(const char *name)`
  - `k_register_program` (function, line 49) `void k_register_program(const char *name, prog_entry_t entry)`
  - `k_register_process` (function, line 57) `void k_register_process(const char *name, void *proc_entry)`
  - `k_spawn` (function, line 65) `int k_spawn(const char *name, int argc, char **argv)`

## kernel/sync.c
- Doc: Blocking synchronization primitives (roadmap Phase 3.1).
- Layer: utility
- Language: c
- Symbols:
  - `wq_init` (function, line 27) `void wq_init(wait_queue_t *q)`
  - `sleep_on` (function, line 33) `void sleep_on(wait_queue_t *q)`
  - `wake_up` (function, line 54) `int wake_up(wait_queue_t *q)`
  - `wake_up_all` (function, line 70) `int wake_up_all(wait_queue_t *q)`
  - `mutex_init` (function, line 76) `void mutex_init(mutex_t *m)`
  - `pi_valid` (function, line 93) `static int pi_valid(int pid)`
  - `pi_set_base` (function, line 99) `void pi_set_base(int pid, int prio)`
  - `pi_get_eff` (function, line 108) `int pi_get_eff(int pid)`
  - `pi_recompute` (function, line 113) `static void pi_recompute(int pid)`
  - `pi_boost` (function, line 124) `static void pi_boost(int waiter, int owner)`
  - `mutex_lock` (function, line 150) `void mutex_lock(mutex_t *m)`
  - `mutex_trylock` (function, line 170) `int mutex_trylock(mutex_t *m)`
  - `mutex_unlock` (function, line 186) `void mutex_unlock(mutex_t *m)`
  - `sem_init` (function, line 207) `void sem_init(sem_t *s, int value)`
  - `sem_wait` (function, line 213) `void sem_wait(sem_t *s)`
  - `sem_post` (function, line 227) `void sem_post(sem_t *s)`
  - `cond_init` (function, line 235) `void cond_init(cond_t *c)`
  - `cond_wait` (function, line 239) `void cond_wait(cond_t *c, mutex_t *m)`
  - `cond_signal` (function, line 245) `void cond_signal(cond_t *c)`
  - `cond_broadcast` (function, line 249) `void cond_broadcast(cond_t *c)`
  - `rwlock_init` (function, line 253) `void rwlock_init(rwlock_t *rw)`
  - `rwlock_read_lock` (function, line 260) `void rwlock_read_lock(rwlock_t *rw)`
  - `rwlock_read_unlock` (function, line 274) `void rwlock_read_unlock(rwlock_t *rw)`
  - `rwlock_write_lock` (function, line 283) `void rwlock_write_lock(rwlock_t *rw)`
  - `rwlock_write_unlock` (function, line 297) `void rwlock_write_unlock(rwlock_t *rw)`
  - `t_cur_pid` (variable, line 24) `extern int t_cur_pid;`
- Depends on: `headers/sync.h`


Next: [KB_kernel_p3.md](KB_kernel_p3.md)
