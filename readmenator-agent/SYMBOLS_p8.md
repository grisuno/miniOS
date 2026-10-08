# Symbols (page 8 of 24)
Previous: [SYMBOLS_p7.md](SYMBOLS_p7.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `kmalloc_aligned` | function | `kernel/mm.c:65` | `void *kmalloc_aligned(unsigned long size, unsigned long align)` |
| `krealloc` | function | `kernel/mm.c:53` | `void *krealloc(void *ptr, unsigned long size)` |
| `COW_MAX` | macro | `kernel/mm/cow.c:28` | `#define COW_MAX` |
| `PT_PTE_RW` | macro | `kernel/mm/cow.c:35` | `#define PT_PTE_RW` |
| `PT_USER_RO` | macro | `kernel/mm/cow.c:33` | `#define PT_USER_RO` |
| `PT_USER_RW_ENTRY` | macro | `kernel/mm/cow.c:34` | `#define PT_USER_RW_ENTRY` |
| `alternative` | function | `kernel/mm/cow.c:20` | `* window is one instruction wide and the alternative (no CoW) is * documented, so the trade stands. */ #include...` |
| `cow_entry_t` | struct | `kernel/mm/cow.c:45` | `` |
| `cow_find` | function | `kernel/mm/cow.c:53` | `static int cow_find(unsigned long phys)` |
| `cow_fork_one` | function | `kernel/mm/cow.c:131` | `static void cow_fork_one(unsigned long pcr3, unsigned long va,         volatile unsigned long *ppte)` |
| `cow_page_shared` | function | `kernel/mm/cow.c:65` | `int cow_page_shared(unsigned long phys)` |
| `cow_release_window` | function | `kernel/mm/cow.c:254` | `void cow_release_window(unsigned long cr3)` |
| `cow_resolve` | function | `kernel/mm/cow.c:191` | `int cow_resolve(unsigned long cr3, unsigned long va)` |
| `cow_shared` | function | `kernel/mm/cow.c:292` | `int cow_shared(void)` |
| `cow_track` | function | `kernel/mm/cow.c:75` | `static int cow_track(unsigned long phys)` |
| `cow_walk` | function | `kernel/mm/cow.c:97` | `static void cow_walk(unsigned long cr3, cow_walk_fn fn)` |
| `private` | function | `kernel/mm/cow.c:93` | `* for every present page in a private (non-graphics) slot. Shared * graphics slots are never CoW: the compositor...` |
| `published` | function | `kernel/mm/cow.c:161` | `* with nothing published (the half-built window is freed). The caller  * flushes the parent TLB a...` |
| `KMM_DEVICE_FLAGS` | macro | `kernel/mm/paging.c:199` | `#define KMM_DEVICE_FLAGS` |
| `KMM_DEVICE_MAX` | macro | `kernel/mm/paging.c:188` | `#define KMM_DEVICE_MAX` |
| `KMM_MAX_IDENTITY` | macro | `kernel/mm/paging.c:192` | `#define KMM_MAX_IDENTITY` |
| `PT_ALLOC_HDR` | macro | `kernel/mm/paging.c:354` | `#define PT_ALLOC_HDR` |
| `_kernel_end` | variable | `kernel/mm/paging.c:48` | `extern char _kernel_end[];` |
| `coherent` | function | `kernel/mm/paging.c:247` | `* for memory a device reads and writes by DMA: a controller that is not cache  * coherent (and an...` |
| `explicitly` | function | `kernel/mm/paging.c:808` | `* teardown passes the dying window explicitly (zombie-exclusive, no * lock needed). unmap == 0 drops refs only...` |
| `honest` | function | `kernel/mm/paging.c:607` | `* and invlpg keeps the local TLB honest (cross-CPU shootdown rides  * the documented T5 follow-up...` |
| `kmm_ensure_pt` | function | `kernel/mm/paging.c:223` | `static volatile unsigned long *kmm_ensure_pt(unsigned long phys)` |
| `kmm_map_device` | function | `kernel/mm/paging.c:284` | `unsigned long kmm_map_device(unsigned long phys, unsigned long len)` |
| `mm_copy_user_page` | function | `kernel/mm/paging.c:939` | `int mm_copy_user_page(unsigned long dst_cr3, unsigned long src_cr3, unsigned long va)` |
| `mm_file_break` | function | `kernel/mm/paging.c:860` | `int mm_file_break(unsigned long cr3, unsigned long va)` |
| `mm_file_page_phys` | function | `kernel/mm/paging.c:658` | `unsigned long mm_file_page_phys(unsigned long cr3, unsigned long va)` |
| `mm_file_pte` | function | `kernel/mm/paging.c:677` | `static volatile unsigned long *mm_file_pte(unsigned long cr3,         unsigned long va)` |
| `mm_file_range_release` | function | `kernel/mm/paging.c:812` | `void mm_file_range_release(unsigned long cr3, unsigned long base,         unsigned long len, int ...` |
| `mm_lock` | variable | `kernel/mm/paging.c:648` | `extern spinlock_t mm_lock;` |
| `mm_page_aligned_alloc` | function | `kernel/mm/paging.c:31` | `static unsigned char *mm_page_aligned_alloc(unsigned size,                                       ...` |
| `mm_setup_protections` | function | `kernel/mm/paging.c:40` | `void mm_setup_protections(void)` |
| `mm_user_ensure_page` | function | `kernel/mm/paging.c:577` | `int mm_user_ensure_page(unsigned long cr3, unsigned long va)` |
| `mm_user_pte_update` | function | `kernel/mm/paging.c:324` | `void mm_user_pte_update(unsigned long vaddr, int exec, unsigned long cr3)` |
| `mm_user_set_exec` | function | `kernel/mm/paging.c:344` | `void mm_user_set_exec(unsigned long start, unsigned long end, unsigned long cr3)` |
| `mt_shared_slot` | function | `kernel/mm/paging.c:501` | `static int mt_shared_slot(unsigned long pd_idx)` |
| `pt_clone_user` | function | `kernel/mm/paging.c:372` | `uint64_t pt_clone_user(uint64_t parent_cr3)` |
| `pt_clone_user_empty` | function | `kernel/mm/paging.c:520` | `unsigned long pt_clone_user_empty(void)` |
| `pt_free_user` | function | `kernel/mm/paging.c:1016` | `void pt_free_user(uint64_t cr3)` |
| `pt_page_alloc` | function | `kernel/mm/paging.c:356` | `void *pt_page_alloc(void)` |
| `pt_page_free` | function | `kernel/mm/paging.c:366` | `void pt_page_free(void *ptr)` |
| `tables` | function | `kernel/mm/paging.c:807` | `* tables (munmap/mremap in caller context, under their mm_lock);` |
| `SWAP_CHUNK_CMP` | macro | `kernel/mm/swap.c:18` | `#define SWAP_CHUNK_CMP` |
| `SWAP_CHUNK_RAW` | macro | `kernel/mm/swap.c:17` | `#define SWAP_CHUNK_RAW` |
| `SWAP_CHUNK_SECTORS` | macro | `kernel/mm/swap.c:19` | `#define SWAP_CHUNK_SECTORS` |
| `SWAP_HDR_SECTORS` | macro | `kernel/mm/swap.c:20` | `#define SWAP_HDR_SECTORS` |
| `SWAP_MAGIC` | macro | `kernel/mm/swap.c:22` | `#define SWAP_MAGIC` |
| `SWAP_MAX_SECTORS` | macro | `kernel/mm/swap.c:21` | `#define SWAP_MAX_SECTORS` |
| `swap_ensure` | function | `kernel/mm/swap.c:28` | `static int swap_ensure(void)` |
| `swap_in` | function | `kernel/mm/swap.c:97` | `int swap_in(void)` |
| `swap_lba` | function | `kernel/mm/swap.c:41` | `static unsigned long swap_lba(void)` |
| `swap_out` | function | `kernel/mm/swap.c:47` | `int swap_out(unsigned long window_sz)` |
| `unwired` | function | `kernel/mm/swap.c:7` | `* * Currently unwired (the isolated-window spawn path superseded the * swap-out design);` |
| `panic_fb_hex` | function | `kernel/panic.c:61` | `static void panic_fb_hex(unsigned long v, int digits)` |
| `panic_fb_puts` | function | `kernel/panic.c:30` | `static void panic_fb_puts(const char *s)` |
| `panic_hex` | function | `kernel/panic.c:23` | `static void panic_hex(unsigned long v, int digits)` |
| `panic_screen` | function | `kernel/panic.c:96` | `void panic_screen(unsigned long vector, unsigned long err,         unsigned long rip, unsigned lo...` |
| `rq_cpu_valid` | function | `kernel/percpu_rq.c:14` | `static int rq_cpu_valid(int cpu)` |
| `rq_empty` | function | `kernel/percpu_rq.c:115` | `int rq_empty(int cpu)` |
| `rq_enqueue` | function | `kernel/percpu_rq.c:41` | `void rq_enqueue(int cpu, int pid)` |
| `rq_init` | function | `kernel/percpu_rq.c:19` | `void rq_init(void)` |
| `rq_note_poll` | function | `kernel/percpu_rq.c:127` | `void rq_note_poll(int cpu)` |
| `rq_pop_local` | function | `kernel/percpu_rq.c:61` | `int rq_pop_local(int cpu)` |
| `rq_should_rescan` | function | `kernel/percpu_rq.c:137` | `int rq_should_rescan(int cpu)` |
| `rq_stats` | function | `kernel/percpu_rq.c:152` | `void rq_stats(int cpu, unsigned long *hits, unsigned long *steals,               unsigned long *d...` |
| `rq_steal_once` | function | `kernel/percpu_rq.c:89` | `int rq_steal_once(int self_cpu, int *from_cpu)` |
| `emit_num` | function | `kernel/printf.c:26` | `static void emit_num(void (*emit)(char, void *, int *), void *ctx, int *written,                 ...` |
| `kformat` | function | `kernel/printf.c:44` | `static void kformat(void (*emit)(char, void *, int *), void *ctx,                     int *writte...` |
| `kfprintf` | function | `kernel/printf.c:157` | `int kfprintf(KFILE *f, const char *fmt, ...)` |
| `ksnprintf` | function | `kernel/printf.c:184` | `int ksnprintf(char *buf, unsigned long size, const char *fmt, ...)` |
| `ksprintf` | function | `kernel/printf.c:166` | `int ksprintf(char *buf, const char *fmt, ...)` |
| `putc_buf` | function | `kernel/printf.c:7` | `static void putc_buf(char c, void *ctx, int *written)` |
| `putc_file` | function | `kernel/printf.c:13` | `static void putc_file(char c, void *ctx, int *written)` |
| `putc_snbuf` | function | `kernel/printf.c:178` | `static void putc_snbuf(char c, void *ctx, int *written)` |
| `putc_str` | function | `kernel/printf.c:19` | `static void putc_str(char c, void *ctx, int *written)` |
| `snctx` | struct | `kernel/printf.c:177` | `` |
| `expires` | function | `kernel/rcu.c:193` | `* expires (ticks stalled, never a hang). No completion assert is  * possible here by design: a re...` |
| `rcu_cpu_valid` | function | `kernel/rcu.c:40` | `static int rcu_cpu_valid(int cpu)` |
| `rcu_deref` | function | `kernel/rcu.c:88` | `void *rcu_deref(void *volatile *pp)` |
| `rcu_init` | function | `kernel/rcu.c:45` | `void rcu_init(void)` |
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
| `BSP` | function | `kernel/sched.c:1588` | `* CPU believe it is the BSP (wrong per-CPU identity, two CPUs          * running the shell contex...` |
| `FSBASE` | function | `kernel/sched.c:726` | `* for FSBASE (per-proc TLS): a thread preempted after arch_prctl * would otherwise resume with whatever base the...` |
| `IRQ4` | function | `kernel/sched.c:610` | `* IRQ4 (COM1, UART IER stays 0 so it never fires) + * IRQ5 (Sound Blaster 16 DMA done). In the mask register a bit...` |
| `KSTACK_CANARY` | macro | `kernel/sched.c:157` | `#define KSTACK_CANARY` |
| `KSTACK_PAINT` | macro | `kernel/sched.c:156` | `#define KSTACK_PAINT` |
| `KSTACK_SZ` | macro | `kernel/sched.c:143` | `#define KSTACK_SZ` |
| `MSR` | function | `kernel/sched.c:2329` | `* in the MSR (the PCB field refreshes on switch-out) and its FPU * regs live in the CPU (the PCB image refreshes on...` |
| `MXCSR` | function | `kernel/sched.c:206` | `* A fresh image is explicit zeros plus the default MXCSR (0x1F80, all  * exceptions masked): fxsa...` |
| `MY_SYS_KSTK_TOP` | macro | `kernel/sched.c:51` | `#define MY_SYS_KSTK_TOP` |
| `MY_USER_LOAD_BASE` | macro | `kernel/sched.c:53` | `#define MY_USER_LOAD_BASE` |
| `MY_USER_STACK_TOP` | macro | `kernel/sched.c:52` | `#define MY_USER_STACK_TOP` |
| `PROC_KSTACK_OFF` | function | `kernel/sched.c:76` | `* PROC_KSTACK_OFF (it cannot use C here). The asm derives both * immediates from headers/syscall_asm.h, so this...` |
| `PROC_SWITCHING` | function | `kernel/sched.c:1965` | `* while the thread is still PROC_SWITCHING (never claimable), * then set the resume point and publish. A...` |
| `__attribute__` | function | `kernel/sched.c:103` | `typedef struct __attribute__((packed))` |
| `__attribute__` | function | `kernel/sched.c:131` | `typedef struct __attribute__((packed))` |
| `adopt` | function | `kernel/sched.c:2445` | `* adopt (armed by Linux O_CLOEXEC on open);` |
| `alloc_kstack` | function | `kernel/sched.c:183` | `static uint64_t alloc_kstack(void)` |
| `aslr_brk_pages` | function | `kernel/sched.c:2420` | `unsigned long aslr_brk_pages(void)` |
| `aslr_dyn_base` | function | `kernel/sched.c:2422` | `unsigned long aslr_dyn_base(void)` |
| `aslr_mix` | function | `kernel/sched.c:2410` | `static unsigned long aslr_mix(unsigned long salt)` |
| `aslr_mmap_pages` | function | `kernel/sched.c:2421` | `unsigned long aslr_mmap_pages(void)` |
| `aslr_stack_bytes` | function | `kernel/sched.c:2419` | `unsigned long aslr_stack_bytes(void)` |
| `cli` | function | `kernel/sched.c:2431` | `* cli (disk PIO must never run with the timer held off);` |
| `context` | function | `kernel/sched.c:701` | `* context (anything entered via k_exec_user) is inside a syscall  * (entry swapped 0 in), and a c...` |
| `copy` | function | `kernel/sched.c:262` | `* copy (fail closed, fork refuses) instead of forging pointers. */ static vma_ctx_t *vma_ctx_copy...` |
| `descriptor` | function | `kernel/sched.c:91` | `* descriptor (two slots) per CPU past the 5 stage-2 entries. */ _Static_assert((5 + 2 * MAX_CPUS) * 8 ==...` |
| `do_execve` | function | `kernel/sched.c:2449` | `long do_execve(char *kpath, int kargc, char **kargv)` |
| `do_exit` | function | `kernel/sched.c:2036` | `void do_exit(int code)` |
| `do_kill` | function | `kernel/sched.c:2742` | `int do_kill(int pid)` |
| `do_thread_spawn` | function | `kernel/sched.c:2075` | `long do_thread_spawn(unsigned long fn, unsigned long stack,                      unsigned long arg)` |
| `do_waitpid` | function | `kernel/sched.c:2674` | `int do_waitpid(int pid)` |
| `exec_enter` | function | `kernel/sched.c:66` | `extern void exec_enter(unsigned long frame);` |
| `fork_trampoline` | function | `kernel/sched.c:65` | `extern void fork_trampoline(void);` |
| `fpu_alloc_clean` | function | `kernel/sched.c:218` | `static void *fpu_alloc_clean(void)` |
| `fpu_free_proc` | function | `kernel/sched.c:236` | `static void fpu_free_proc(proc_t *p)` |
| `fpu_restore_from` | function | `kernel/sched.c:214` | `static inline void fpu_restore_from(void *area)` |
| `free_kstack` | function | `kernel/sched.c:195` | `static void free_kstack(uint64_t top)` |
| `gdb_dump_report` | function | `kernel/sched.c:530` | `void gdb_dump_report(unsigned long addr, unsigned long len)` |
| `here` | function | `kernel/sched.c:116` | `* smp_ap_idle_loop here (idle_proc ctx.rsp points at the top). */ static char ap_idle_stack[MAX_CPUS][4096]...` |
| `idt_init` | function | `kernel/sched.c:574` | `static void idt_init(void)` |
| `idt_set` | function | `kernel/sched.c:563` | `static void idt_set(int vec, void (*h)(void))` |
| `irqstat_report` | function | `kernel/sched.c:464` | `void irqstat_report(void)` |
| `isr_dispatch` | function | `kernel/sched.c:1009` | `void isr_dispatch(int vector, trap_frame_t *frame)` |
| `isr_stub_table` | variable | `kernel/sched.c:140` | `extern void *isr_stub_table[];` |
| `it` | function | `kernel/sched.c:2780` | `* it (SPAWN/exec point proc 0 here transiently);` |
| `itself` | function | `kernel/sched.c:2273` | `* the shell itself (use mrun first), and a CLONE_VM thread forking  * would duplicate shared stat...` |
| `kstack_paint` | function | `kernel/sched.c:159` | `static void kstack_paint(uint64_t top, unsigned long size)` |
| `kstack_report` | function | `kernel/sched.c:353` | `void kstack_report(void)` |
| `kstack_usage` | function | `kernel/sched.c:168` | `static int kstack_usage(uint64_t top, unsigned long size,                         unsigned long *...` |
| `mm_lock` | variable | `kernel/sched.c:695` | `extern spinlock_t mm_lock;` |
| `net_rx_dropped` | variable | `kernel/sched.c:468` | `extern unsigned int net_rx_dropped;` |
| `off_lo` | type_alias | `kernel/sched.c:131` | `typedef struct __attribute__((packed)) { uint16_t off_lo;` |
| `park` | function | `kernel/sched.c:2831` | `* an image its live FPU registers would be dropped by the preempt * park (the save path skips a null area). */...` |
| `pic_eoi` | function | `kernel/sched.c:628` | `static void pic_eoi(int irq)` |
| `pic_init` | function | `kernel/sched.c:586` | `static void pic_init(void)` |
| `pit_init` | function | `kernel/sched.c:621` | `static void pit_init(void)` |
| `point` | function | `kernel/sched.c:714` | `* return address as the resume point ("continue the ISR"), which  * required the stranded ISR fra...` |
| `proc_create` | function | `kernel/sched.c:1619` | `int proc_create(const char *name, int parent_pid)` |
| `proc_get` | function | `kernel/sched.c:1613` | `proc_t *proc_get(int pid)` |
| `proc_spawn_elf` | function | `kernel/sched.c:1890` | `int proc_spawn_elf(const char *name, void *data, unsigned size,                    int argc, char...` |
| `proc_spawn_elf_inner` | function | `kernel/sched.c:1737` | `static int proc_spawn_elf_inner(const char *name, void *data, unsigned size,                    i...` |
| `read_cr3` | function | `kernel/sched.c:68` | `static inline unsigned long read_cr3(void)` |
| `registers` | function | `kernel/sched.c:2106` | `* registers (float args would need XMM inheritance, which the * arg-passing contract does not carry: fn takes one...` |
| `res0` | type_alias | `kernel/sched.c:103` | `typedef struct __attribute__((packed)) { uint32_t res0;` |
| `returns` | function | `kernel/sched.c:2029` | `* that returns (and the resumed thread returns with IF=1). */ __asm__ volatile("cli");` |
| `rlimit_cpu_exceeded` | function | `kernel/sched.c:988` | `int rlimit_cpu_exceeded(int pid)` |
| `rtl_counters` | function | `kernel/sched.c:467` | `extern void rtl_counters(unsigned int *tx_frames, unsigned int *rx_frames);` |
| `rtl_present` | function | `kernel/sched.c:469` | `extern int rtl_present(void);` |
| `sched_ap_preempt` | function | `kernel/sched.c:882` | `static void sched_ap_preempt(trap_frame_t *frame)` |
| `sched_init` | function | `kernel/sched.c:2772` | `void sched_init(void)` |
| `sched_lock` | function | `kernel/sched.c:340` | `* hold sched_lock (+mm_lock at the swap sites);` |
| `sched_next_locked` | function | `kernel/sched.c:743` | `static int sched_next_locked(int start, int vm_only)` |
| `sched_set_nice` | function | `kernel/sched.c:761` | `int sched_set_nice(int pid, int nice)` |
| `sched_tick_audio` | function | `kernel/sched.c:24` | `static void sched_tick_audio(void *ctx)` |
| `sched_tick_desktop` | function | `kernel/sched.c:30` | `static void sched_tick_desktop(void *ctx)` |
| `sched_tick_usb` | function | `kernel/sched.c:41` | `static void sched_tick_usb(void *ctx)` |
| `schedtop_report` | function | `kernel/sched.c:396` | `void schedtop_report(void)` |
| `schedule` | function | `kernel/sched.c:1932` | `* that keeps schedule()'s own rbp runs the caller's frame accesses  * (locals, leave/ret) on the ...` |
| `schedule` | function | `kernel/sched.c:1939` | `void schedule(void)` |
| `seccomp_allow_one` | function | `kernel/sched.c:777` | `int seccomp_allow_one(int pid, int n)` |
| `seccomp_denied` | function | `kernel/sched.c:784` | `int seccomp_denied(int pid, int n)` |
| `seccomp_deny_one` | function | `kernel/sched.c:770` | `int seccomp_deny_one(int pid, int n)` |
| `shell_nchildren` | function | `kernel/sched.c:2716` | `int shell_nchildren(void)` |
| `shell_reap_nb` | function | `kernel/sched.c:2690` | `int shell_reap_nb(int *pid_out, int *code_out)` |
| `shell_reap_one` | function | `kernel/sched.c:2704` | `int shell_reap_one(int pid, int *code_out)` |
| `slot` | function | `kernel/sched.c:400` | `* must not eat a quarter of a 16 KB slot (see the stack discipline * contract in CLAUDE.md). Fail-closed on OOM. */...` |
| `smp_any_ap_idle` | function | `kernel/sched.c:952` | `static int smp_any_ap_idle(void)` |
| `smp_ap_idle_loop` | function | `kernel/sched.c:848` | `void smp_ap_idle_loop(void)` |
| `smp_claim_thread_v` | function | `kernel/sched.c:809` | `static int smp_claim_thread_v(int vm_only)` |
| `smp_try_claim_hint` | function | `kernel/sched.c:793` | `static int smp_try_claim_hint(int pid, int vm_only)` |
| `stop_row` | struct | `kernel/sched.c:397` | `` |
| `stub` | function | `kernel/sched.c:483` | `* gdb stub (`make gdb`, then `target remote :1234` from the host). These  * helpers are the seria...` |
| `sys_ticks` | function | `kernel/sched.c:460` | `* sys_ticks (PIT 100 Hz on the BSP, broadcast as IPIs to APs);` |
| `syscall` | function | `kernel/sched.c:1133` | `* outgoing syscall (see sched_rearm_kgs). Without * this the next entry swapgs puts garbage under GS * and the pid...` |
| `timer_tick` | function | `kernel/sched.c:2767` | `void timer_tick(void)` |
| `trap_frame_t` | struct | `kernel/sched.c:547` | `` |
| `tss_init` | function | `kernel/sched.c:652` | `static void tss_init(void)` |
| `tss_init_ap` | function | `kernel/sched.c:683` | `void tss_init_ap(int cpu)` |
| `tss_write_desc` | function | `kernel/sched.c:635` | `static void tss_write_desc(int cpu)` |
| `user_trampoline` | function | `kernel/sched.c:64` | `extern void user_trampoline(void);` |
| `vma_ctx_alloc` | function | `kernel/sched.c:242` | `vma_ctx_t *vma_ctx_alloc(void)` |
| `vma_ctx_free` | function | `kernel/sched.c:252` | `void vma_ctx_free(vma_ctx_t *c)` |
| `vma_load_proc` | function | `kernel/sched.c:346` | `static void vma_load_proc(proc_t *p)` |
| `vma_owned` | function | `kernel/sched.c:334` | `static int vma_owned(proc_t *p)` |
| `vma_save_proc` | function | `kernel/sched.c:342` | `static void vma_save_proc(proc_t *p)` |
| `yield` | function | `kernel/sched.c:2021` | `void yield(void)` |
| `zeroed` | function | `kernel/sched.c:2841` | `* still zeroed (kmemset happens inside idt_init) faults through a * null gate. Handlers for 32/33/44 are safe...` |
| `SCROLLBACK_ROWS` | macro | `kernel/scrollback.c:12` | `#define SCROLLBACK_ROWS` |
| `sb_capture_row0` | function | `kernel/scrollback.c:23` | `void sb_capture_row0(void)` |
| `sb_get_char` | function | `kernel/scrollback.c:41` | `char sb_get_char(int row, int col)` |
| `sb_get_count` | function | `kernel/scrollback.c:38` | `int sb_get_count(void)` |
| `sb_get_head` | function | `kernel/scrollback.c:39` | `int sb_get_head(void)` |
| `sb_init` | function | `kernel/scrollback.c:17` | `void sb_init(void)` |
| `sb_reset` | function | `kernel/scrollback.c:34` | `void sb_reset(void)` |
| `vga_scroll` | function | `kernel/scrollback.c:4` | `* Captured lazily from vga_scroll();` |
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
| `PIPE_HOP_MAX` | macro | `kernel/shell.c:4018` | `#define PIPE_HOP_MAX` |
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
| `DOOM_FRAME` | function | `kernel/syscalls.c:791` | `* DOOM_FRAME (211) and NK_FRAME (220) stay as compat aliases. */ static long sys_minios_gfx_prese...` |
| `Discipline` | function | `kernel/syscalls.c:2408` | `* * Discipline (audit 2026-09, kept as comment, not a deprecation: both * primitives are legitimate): user_range_ok...` |
| `EAGAIN` | function | `kernel/syscalls.c:1109` | `* writer open is EAGAIN (-11, retry);` |
| `EOF` | function | `kernel/syscalls.c:1110` | `* is EOF (0). */ KFILE *o = kfd_get(0);` |
| `KFD_MAX` | macro | `kernel/syscalls.c:49` | `#define KFD_MAX` |
| `LINUX_MAP_ANONYMOUS` | macro | `kernel/syscalls.c:1446` | `#define LINUX_MAP_ANONYMOUS` |
| `LINUX_MAP_FIXED` | macro | `kernel/syscalls.c:1445` | `#define LINUX_MAP_FIXED` |
| `LINUX_MAP_PRIVATE` | macro | `kernel/syscalls.c:1444` | `#define LINUX_MAP_PRIVATE` |
| `LINUX_MAP_SHARED` | macro | `kernel/syscalls.c:1443` | `#define LINUX_MAP_SHARED` |
| `LINUX_MREMAP_FIXED` | macro | `kernel/syscalls.c:1672` | `#define LINUX_MREMAP_FIXED` |
| `LINUX_MREMAP_MAYMOVE` | macro | `kernel/syscalls.c:1671` | `#define LINUX_MREMAP_MAYMOVE` |
| `LINUX_SYSCALL_COUNT` | macro | `kernel/syscalls.c:2221` | `#define LINUX_SYSCALL_COUNT` |
| `MINIOS_SYSCALL_BASE` | macro | `kernel/syscalls.c:240` | `#define MINIOS_SYSCALL_BASE` |
| `MINIOS_SYSCALL_COUNT` | macro | `kernel/syscalls.c:241` | `#define MINIOS_SYSCALL_COUNT` |
| `NULL` | function | `kernel/syscalls.c:163` | `* on NULL (already released or never owned). */ void kfd_view_release(proc_t *p)` |
| `SC_EXTRA_COUNT` | macro | `kernel/syscalls.c:2302` | `#define SC_EXTRA_COUNT` |
| `SYSCALL_TRACE` | macro | `kernel/syscalls.c:1062` | `#define SYSCALL_TRACE` |
| `SYS_NOISY_GETC_RAW` | macro | `kernel/syscalls.c:1085` | `#define SYS_NOISY_GETC_RAW` |
| `SYS_NOISY_KBD` | macro | `kernel/syscalls.c:1083` | `#define SYS_NOISY_KBD` |
| `SYS_NOISY_MOUSE` | macro | `kernel/syscalls.c:1084` | `#define SYS_NOISY_MOUSE` |
| `SYS_NOISY_TIME` | macro | `kernel/syscalls.c:1082` | `#define SYS_NOISY_TIME` |
| `TRACE_HINT_NONE` | macro | `kernel/syscalls.c:2324` | `#define TRACE_HINT_NONE` |
| `TRACE_HINT_PATH` | macro | `kernel/syscalls.c:2325` | `#define TRACE_HINT_PATH` |
| `batch_kdispatch` | function | `kernel/syscalls.c:776` | `static long batch_kdispatch(uint32_t opcode)` |
| `boot` | function | `kernel/syscalls.c:441` | `* boot (minfo_sleep_init from sched_init);` |
| `by` | function | `kernel/syscalls.c:222` | `* is indexed by (syscall_number - 200). New syscalls are added by: * 1. Adding a MINIOS_SYS_* constant to...` |
| `do_open_path` | function | `kernel/syscalls.c:1207` | `static long do_open_path(const char *path, long flags)` |
| `first` | function | `kernel/syscalls.c:1604` | `* passes under mm_lock: validate every page first (present, user,  * private), then apply, so a h...` |
| `gfx_win_title` | variable | `kernel/syscalls.c:665` | `extern const char *gfx_win_title;` |
| `gfx_zoom_2x` | variable | `kernel/syscalls.c:384` | `extern int gfx_zoom_2x;` |
| `k_syscall_spawn` | function | `kernel/syscalls.c:2631` | `static int k_syscall_spawn(const char *path, const char *redirect,                              i...` |
| `kfd_claim` | function | `kernel/syscalls.c:1248` | `static long kfd_claim(KFILE *f)` |
| `kfd_get` | function | `kernel/syscalls.c:87` | `KFILE *kfd_get(int fd)` |
| `kfd_put` | function | `kernel/syscalls.c:100` | `void kfd_put(KFILE *f)` |
| `kfd_view_cloexec` | function | `kernel/syscalls.c:194` | `void kfd_view_cloexec(void)` |
| `kfd_view_count` | function | `kernel/syscalls.c:112` | `static int kfd_view_count(kfd_view_t *v)` |
| `kfd_view_current` | function | `kernel/syscalls.c:58` | `static kfd_view_t *kfd_view_current(void)` |
| `kfd_view_root` | function | `kernel/syscalls.c:68` | `kfd_view_t *kfd_view_root(void)` |
| `kiovec` | struct | `kernel/syscalls.c:1060` | `` |
| `ksyscall` | function | `kernel/syscalls.c:2357` | `long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6)` |
| `ksyscall_dispatch` | function | `kernel/syscalls.c:2425` | `static long ksyscall_dispatch(long n, long a1, long a2, long a3, long a4, long a5, long a6)` |
| `minfo_sleep_init` | function | `kernel/syscalls.c:448` | `void minfo_sleep_init(int tick_ok)` |
| `minfo_tick_wake` | function | `kernel/syscalls.c:453` | `void minfo_tick_wake(void *ctx)` |
| `minios_syscall_entry_t` | struct | `kernel/syscalls.c:235` | `` |
| `mm_ensure_cur` | function | `kernel/syscalls.c:1401` | `static int mm_ensure_cur(unsigned long start, unsigned long end)` |
| `mmap_tag_file` | function | `kernel/syscalls.c:1451` | `static int mmap_tag_file(unsigned long base, int ino, unsigned long off)` |
| `mprotect_pte` | function | `kernel/syscalls.c:1580` | `static volatile unsigned long *mprotect_pte(unsigned long cr3,         unsigned long va)` |
| `node` | function | `kernel/syscalls.c:1717` | `* mapping is one exact live VMA node (what mmap inserts);` |
| `proc_spawn_elf` | function | `kernel/syscalls.c:2622` | `* proc_spawn_elf (the same path mrun uses) and the caller blocks in * do_waitpid, so the parent address space is...` |
| `products` | function | `kernel/syscalls.c:2412` | `* products (writev cnt*sizeof, poll a2*8, spawn (argc+1)*sizeof) are  * pre-bounded against (END-...` |
| `sb16_audio_device` | function | `kernel/syscalls.c:631` | `static device_t *sb16_audio_device(void)` |
| `sc_extra_name` | struct | `kernel/syscalls.c:2287` | `` |
| `sys_linux_accept` | function | `kernel/syscalls.c:2041` | `static long sys_linux_accept(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_access` | function | `kernel/syscalls.c:1997` | `static long sys_linux_access(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_arch_prctl` | function | `kernel/syscalls.c:2188` | `static long sys_linux_arch_prctl(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_bind` | function | `kernel/syscalls.c:2030` | `static long sys_linux_bind(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_brk` | function | `kernel/syscalls.c:1410` | `static long sys_linux_brk(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_close` | function | `kernel/syscalls.c:1360` | `static long sys_linux_close(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_connect` | function | `kernel/syscalls.c:2024` | `static long sys_linux_connect(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_dup` | function | `kernel/syscalls.c:1312` | `static long sys_linux_dup(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_dup2` | function | `kernel/syscalls.c:1327` | `static long sys_linux_dup2(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_fdatasync` | function | `kernel/syscalls.c:2083` | `static long sys_linux_fdatasync(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_flock` | function | `kernel/syscalls.c:2069` | `static long sys_linux_flock(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_fstat` | function | `kernel/syscalls.c:2142` | `static long sys_linux_fstat(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_fsync` | function | `kernel/syscalls.c:2078` | `static long sys_linux_fsync(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_futex` | function | `kernel/syscalls.c:275` | `static long sys_linux_futex(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_getcwd` | function | `kernel/syscalls.c:2088` | `static long sys_linux_getcwd(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_gettimeofday` | function | `kernel/syscalls.c:2165` | `static long sys_linux_gettimeofday(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_ioctl` | function | `kernel/syscalls.c:1992` | `static long sys_linux_ioctl(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_listen` | function | `kernel/syscalls.c:2036` | `static long sys_linux_listen(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_lseek` | function | `kernel/syscalls.c:1383` | `static long sys_linux_lseek(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_mmap` | function | `kernel/syscalls.c:1460` | `static long sys_linux_mmap(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_mremap` | function | `kernel/syscalls.c:1722` | `static long sys_linux_mremap(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_munmap` | function | `kernel/syscalls.c:1548` | `static long sys_linux_munmap(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_open` | function | `kernel/syscalls.c:1240` | `static long sys_linux_open(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_pipe` | function | `kernel/syscalls.c:1287` | `static long sys_linux_pipe(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_poll` | function | `kernel/syscalls.c:2062` | `static long sys_linux_poll(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_readlink` | function | `kernel/syscalls.c:2119` | `static long sys_linux_readlink(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_recvfrom` | function | `kernel/syscalls.c:2052` | `static long sys_linux_recvfrom(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_rename` | function | `kernel/syscalls.c:2128` | `static long sys_linux_rename(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_sendto` | function | `kernel/syscalls.c:2047` | `static long sys_linux_sendto(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_shutdown` | function | `kernel/syscalls.c:2057` | `static long sys_linux_shutdown(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_sigaction` | function | `kernel/syscalls.c:1982` | `static long sys_linux_sigaction(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_sigprocmask` | function | `kernel/syscalls.c:1987` | `static long sys_linux_sigprocmask(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_socket` | function | `kernel/syscalls.c:2019` | `static long sys_linux_socket(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_uname` | function | `kernel/syscalls.c:2200` | `static long sys_linux_uname(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_unlink` | function | `kernel/syscalls.c:2100` | `static long sys_linux_unlink(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_write` | function | `kernel/syscalls.c:1145` | `static long sys_linux_write(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_writev` | function | `kernel/syscalls.c:1173` | `static long sys_linux_writev(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_clip_get` | function | `kernel/syscalls.c:732` | `static long sys_minios_clip_get(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_clip_set` | function | `kernel/syscalls.c:722` | `static long sys_minios_clip_set(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_dir_list` | function | `kernel/syscalls.c:900` | `static long sys_minios_dir_list(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_dns` | function | `kernel/syscalls.c:263` | `static long sys_minios_dns(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_doom_frame` | function | `kernel/syscalls.c:371` | `static long sys_minios_doom_frame(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_fb_info` | function | `kernel/syscalls.c:404` | `static long sys_minios_fb_info(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_futex_wait` | function | `kernel/syscalls.c:761` | `static long sys_minios_futex_wait(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_futex_wake` | function | `kernel/syscalls.c:767` | `static long sys_minios_futex_wake(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_getc_raw` | function | `kernel/syscalls.c:825` | `static long sys_minios_getc_raw(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_gfx_title` | function | `kernel/syscalls.c:660` | `static long sys_minios_gfx_title(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_gfx_zoom` | function | `kernel/syscalls.c:382` | `static long sys_minios_gfx_zoom(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_kbd` | function | `kernel/syscalls.c:308` | `static long sys_minios_kbd(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_kbd_raw` | function | `kernel/syscalls.c:340` | `static long sys_minios_kbd_raw(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_lz4_compress` | function | `kernel/syscalls.c:567` | `static long sys_minios_lz4_compress(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_lz4_decompress` | function | `kernel/syscalls.c:580` | `static long sys_minios_lz4_decompress(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_mouse` | function | `kernel/syscalls.c:594` | `static long sys_minios_mouse(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_nk_frame` | function | `kernel/syscalls.c:618` | `static long sys_minios_nk_frame(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_palette` | function | `kernel/syscalls.c:328` | `static long sys_minios_palette(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_pcm2_close` | function | `kernel/syscalls.c:712` | `static long sys_minios_pcm2_close(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_pcm2_open` | function | `kernel/syscalls.c:699` | `static long sys_minios_pcm2_open(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_pcm2_write` | function | `kernel/syscalls.c:704` | `static long sys_minios_pcm2_write(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_pcspk_init` | function | `kernel/syscalls.c:353` | `static long sys_minios_pcspk_init(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_pcspk_tone` | function | `kernel/syscalls.c:357` | `static long sys_minios_pcspk_tone(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_pcspk_vol` | function | `kernel/syscalls.c:424` | `static long sys_minios_pcspk_vol(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_rlimit` | function | `kernel/syscalls.c:859` | `static long sys_minios_rlimit(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_rtc` | function | `kernel/syscalls.c:391` | `static long sys_minios_rtc(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_sb16_open` | function | `kernel/syscalls.c:637` | `static long sys_minios_sb16_open(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_sb16_pump` | function | `kernel/syscalls.c:674` | `static long sys_minios_sb16_pump(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_sb16_stream_close` | function | `kernel/syscalls.c:682` | `static long sys_minios_sb16_stream_close(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_sb16_stream_open` | function | `kernel/syscalls.c:678` | `static long sys_minios_sb16_stream_open(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_sb16_stream_submit` | function | `kernel/syscalls.c:686` | `static long sys_minios_sb16_stream_submit(long a1, long a2, long a3, long a4, long a5, long a6)` |

Next: [SYMBOLS_p9.md](SYMBOLS_p9.md)
