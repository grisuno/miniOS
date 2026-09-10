#ifndef SCHED_H
#define SCHED_H

#include <stdint.h>
#include "spinlock.h"

/* ---- Process states ---- */
#define PROC_FREE       0
#define PROC_READY      1
#define PROC_RUNNING    2
#define PROC_BLOCKED    3
#define PROC_ZOMBIE     4
/* Transient: the owner CPU is between "decided to switch away" and
 * "context fully saved".  Never claimable: a steal here would resume a
 * stale context.  schedule() turns it into READY only after the save. */
#define PROC_SWITCHING  5

/* ---- Limits ---- */
#define MAX_PROCS       64
#define PROC_KSTACK_SZ  (16UL * 1024)

/* ---- SMP limits ---- */
#define MAX_CPUS        8
#define BOOT_CPU        0

/* ---- Per-process saved registers (offsets must match ctx_sw.S) ---- */
typedef struct {
    uint64_t rax, rbx, rcx, rdx;
    uint64_t rsi, rdi, rbp;
    uint64_t r8, r9, r10, r11;
    uint64_t r12, r13, r14, r15;
    uint64_t rip, rsp, rflags;
    uint64_t cr3;
} ctx_regs_t;

/* ---- Process Control Block ---- */
typedef struct {
    ctx_regs_t  ctx;
    int         pid;
    int         state;
    int         parent_pid;
    int         exit_code;
    uint64_t    kstack;         /* top of kernel stack for this proc */
    uint64_t    brk;
    uint64_t    brk_limit;
    uint64_t    mmap_cur;
    int         clone_flags;
    int         wq_next;        /* next pid in a wait queue, WQ_NONE if none */
    int         exited;         /* do_exit ran: kstack/pt already freed */
    int         nice;           /* -20 (high prio) .. +19 (low prio), default 0 */
    unsigned long vruntime;     /* fair-share virtual runtime for sched_next */
    unsigned int seccomp_deny;  /* bit (n-200) denies MiniOS syscall n 200..231 */
    unsigned long rl_as_max;
    unsigned long rl_cpu_max;
    unsigned long rl_nofile_max;
    unsigned long cpu_ticks;
    int open_files;
    int cpu_kill_pending;
    char        name[32];
    /* Per-thread FPU/SSE image (Phase 0.1, ADR-0014): 512-byte fxsave
     * area, heap-allocated at proc_create so the 64-entry procs[] array
     * grows by 8 bytes/slot, not 512 (a 32 KB .bss growth would overflow
     * USER_LOAD_BASE, which sits ~1 KB past _kernel_end). The pointed-to
     * buffer is 16-byte aligned (dlmalloc MALLOC_ALIGNMENT), as fxsave
     * faults otherwise. 0 means no image yet: the switch asm skips
     * save/restore, so idle contexts and half-built procs never fault. */
    void       *fpu_save;
} proc_t;
/* Single source of truth for the PCB footprint (review fix for the
 * 0a92118 imulq drift): the syscall_entry trampoline in kernel.c cannot
 * use C, so it multiplies pid by PROC_T_SIZE and adds PROC_KSTACK_OFF.
 * Both immediates derive from these macros via STR(); the _Static_asserts
 * in kernel/sched.c prove macro == struct. Adding a field changes the
 * macros' values automatically on rebuild -- no asm hunt. procs[] itself
 * is a static 64-entry .bss array (~19 KB at 304 B/entry), far below the
 * USER_LOAD_BASE budget enforced by `make check-size`. */
#define PROC_T_SIZE 312
#define PROC_KSTACK_OFF 168
/* Offset of fpu_save inside proc_t: the ctx_sw.S save/restore paths
 * address it as imm(proc) without C, so it is named here beside
 * PROC_T_SIZE (same imulq-drift lesson: the _Static_asserts in
 * kernel/sched.c prove offset and size against the struct). */
#define PROC_FPU_OFF 304
/* fxsave/fxrstor image footprint; MXCSR lives at byte 24 of it. */
#define FPU_SAVE_SZ 512
#define FPU_MXCSR_OFF 24
#define FPU_MXCSR_DEFAULT 0x1F80
/* Seccomp-basic: bit for MiniOS syscall n in proc_t.seccomp_deny. Only the
 * 200..231 window is filterable (the framebuffer/audio/spawn/TLS surface);
 * Linux-ABI numbers are never filtered so a filter cannot break exit. */
#define SECCOMP_MIN 200
#define SECCOMP_MAX 231
#define SECCOMP_BIT(n) (1u << ((unsigned)(n) - SECCOMP_MIN))
/* Seccomp modes for SYS_SECCOMP (238): deny one syscall, allow one back,
 * or deny the whole filterable window except an explicit keep mask. */
#define SECCOMP_OP_DENY_ONE  1
#define SECCOMP_OP_ALLOW_ONE 2
#define SECCOMP_OP_DENY_ALL  3
/* Rlimit/cgroups-lite (SYS_RLIMIT, 240): per-process resource caps, all
 * 0 = unlimited (the default). Inherited across proc_create/clone/spawn.
 *   RLIM_AS    total user bytes (brk growth + mmap) beyond the load base
 *   RLIM_CPU   timer ticks of CPU time, then SIGKILL-equivalent (137)
 *   RLIM_NOFILE open-file count attributed to the pid (best-effort: the
 *     fd table is global/shared, so close() attributes to the closer) */
#define RLIM_OP_SET   1
#define RLIM_OP_GET   2
#define RLIM_AS       1
#define RLIM_CPU      2
#define RLIM_NOFILE   3
#define RLIM_EXIT_CPU 137

/* clone() flags */
#define CLONE_VM    0x00000100  /* share address space (same CR3) */
#define CLONE_FILES 0x00000400  /* share fd table */

/* ---- Per-CPU state ----
 *
 * One instance per logical processor.  The BSP (boot processor) is always
 * cpus[0]; APs (application processors) receive their index from the AP
 * counter during smp_ap_entry.  The first qword of each cpu_t is a
 * self-pointer so that this_cpu() can dereference it via gs:0 without
 * knowing the CPU index at compile time.
 *
 * Fields:
 *   cpu_id:           index into cpus[], 0 for BSP
 *   cur_pid:           PID of the running process on this CPU
 *   syscall_kstack:   kernel stack top exchanged on syscall entry
 *   kstack_top:       per-CPU interrupt stack top
 *   last_sched_tick:  sys_ticks value of last context switch (Phase 2)
 *   lapic_id:         APIC ID from hardware
 *   is_bsp:           1 for the boot processor, 0 for APs
 *   idle:             1 when CPU is in idle loop (Phase 2: idle thread)
 *   irq_depth:        interrupt nesting count for irqsave (Phase 3)
 *   idle_proc:        pointer to idle process (Phase 2)
 *   run_queue:        opaque pointer to per-CPU run queue (Phase 2)
 */
typedef struct cpu {
    struct cpu     *self;          /* gs:0 = self-pointer for this_cpu() */
    int             cpu_id;
    int             cur_pid;
    uint64_t        syscall_kstack;
    uint64_t        kstack_top;
    uint64_t        last_sched_tick;
    int             lapic_id;
    int             is_bsp;
    volatile int    idle;
    int             irq_depth;
    struct proc    *idle_proc;
    void           *run_queue;
    /* Syscall-entry scratch, one set per CPU (gs:72..gs:112).  The entry
     * trampoline has no free register and no stack before the swap, so
     * it parks n/rip/pid here; per-CPU (not global) so two CPUs never
     * share a slot, and always under cli so one CPU never interleaves
     * with itself.  See the syscall_entry comment in kernel.c. */
    uint64_t        sc_n;           /* gs:72 */
    uint64_t        sc_rip;         /* gs:80 */
    uint64_t        sc_pid;         /* gs:88 */
    uint64_t        sc_ret;         /* gs:96 */
    uint64_t        sc_pcb;         /* gs:104 */
    uint64_t        sc_tmp;         /* gs:112 */
} cpu_t;

extern cpu_t cpus[MAX_CPUS];
extern int   cpu_count;

/* this_cpu() returns the cpu_t of the executing processor.
 * The GS base is set to &cpus[cpu_id] during sched_init (BSP) and
 * smp_ap_entry (APs).  The first qword of cpu_t is a self-pointer
 * so that gs:0 yields the cpu_t address directly. */
static inline cpu_t *this_cpu(void) {
    unsigned long val;
    __asm__ volatile("mov %%gs:0, %0" : "=r"(val));
    return (cpu_t *)val;
}

/* current_pid is a macro that resolves to the current CPU's PID.
 * This allows existing code to read/write current_pid without changes
 * while automatically becoming per-CPU when SMP is enabled.
 * Host unit tests (SYNC_HOST_CURRENT_PID) map it to a test global. */
#ifndef SYNC_HOST_CURRENT_PID
#define current_pid (this_cpu()->cur_pid)
#endif

/* ---- Limits ---- */
#define DESKTOP_TICK_INTERVAL 4

/* ---- Shared scheduler data (protected by sched_lock) ----
 *
 * Invariant: these structures are accessed by the BSP (boot processor)
 * and will be accessed by APs (application processors) when SMP
 * scheduling is enabled.  All modifications must hold sched_lock.
 *
 * Per-CPU data (no lock needed):
 *   - cpu_t cpus[]: each CPU reads only its own entry via this_cpu()
 *   - GS base: set to &cpus[cpu_id] for kernel execution
 *
 * Shared data (protected by sched_lock):
 *   - procs[]: the process table
 *   - proc_count: the high-water mark of PIDs
 *   - scheduler state in schedule(), do_exit(), do_waitpid()
 */
extern proc_t  procs[MAX_PROCS];
extern int     proc_count;
extern volatile uint64_t sys_ticks;
extern volatile int user_program_active;
extern spinlock_t sched_lock;
extern volatile int sched_ready;

/* ---- SMP thread execution (roadmap Phase 2.2, first increment) ----
 *
 * APs (application processors) run CLONE_VM threads: same CR3 as their
 * parent, so no brk/mmap view switch and no TLB shootdown is needed.
 * Non-CLONE_VM processes stay on the BSP, which owns the shared
 * g_brk/user_mmap_cur globals (guarded by mm_lock against concurrent
 * brk/mmap syscalls from AP threads).
 *
 * Per-CPU idle contexts: an AP with no READY thread parks in
 * ap_idle_proc[cpu] (pid -1, never in procs[], never picked by scans)
 * instead of borrowing procs[0], which the BSP owns.  current_pid == -1
 * on a CPU means that CPU is idle.
 *
 * smp_dispatches[cpu] counts threads first dispatched on that CPU; the
 * `smp` shell builtin reports it, so parallel execution is observable
 * over the serial console without a framebuffer. */
extern proc_t ap_idle_proc[MAX_CPUS];
extern volatile unsigned long smp_dispatches[MAX_CPUS];
extern volatile unsigned long smp_idle_polls[MAX_CPUS];
/* Timer ticks that arrived with a GS base outside cpus[] (fail-safe
 * EOI, no scheduling action).  Zero in a healthy boot. */
extern volatile unsigned smp_dbg_bad_gs;

/* Per-CPU TSS selectors: slot 5 + 2*cpu in the runtime GDT (each TSS
 * descriptor occupies two 8-byte slots).  CPU 0 keeps selector 0x28,
 * exactly as before. */
#define TSS_SEL(cpu) ((uint16_t)((5 + 2 * (cpu)) * 8))

/* Exported IDTR for APs to load during SMP bring-up. */
typedef struct __attribute__((packed)) { uint16_t limit; uint64_t base; } idtr_t;
extern idtr_t bsp_idtr;

/* ---- Functions ---- */
void     sched_init(void);
void     kstack_report(void);
void     tss_init_ap(int cpu);
void     smp_ap_idle_loop(void);
int      proc_create(const char *name, int parent_pid);
proc_t  *proc_get(int pid);
void     schedule(void);
int      sched_set_nice(int pid, int nice);
int      seccomp_deny_one(int pid, int n);
int      seccomp_allow_one(int pid, int n);
int      seccomp_denied(int pid, int n);
int      rlimit_cpu_exceeded(int pid);
void     rlimit_cpu_tick(int pid);
void     switch_to(proc_t *prev, proc_t *next);
void     switch_to_notrap(proc_t *prev, proc_t *next);
void     switch_save_only(proc_t *prev);
void     resume_iretq(void);
void     yield(void);
void     do_exit(int code);
long     do_clone(long flags, long newsp);
long     do_thread_spawn(unsigned long fn, unsigned long stack,
                         unsigned long arg);
int      do_waitpid(int pid);
int      do_kill(int pid);
void     timer_tick(void);

/* ---- Per-process page tables ---- */
uint64_t pt_clone_user(uint64_t parent_cr3);
void     pt_free_user(uint64_t cr3);

/* ---- Multitask spawn (isolated ET_EXEC, preemptive on BSP) ----
 * Builds a non-CLONE_VM process with a fresh user window, loads the
 * ELF image into it and leaves it READY for the next tick. The
 * caller (shell mrun) reaps it with do_waitpid. Returns pid or -1.
 * Programs using mmap/VMA or expecting a shared fd table beyond
 * O_RDONLY stdin-style use are best-effort in this revision. */
int      proc_spawn_elf(const char *name, void *data, unsigned size,
                       int argc, char **argv);

#endif
