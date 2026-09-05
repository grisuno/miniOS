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
    char        name[32];
} proc_t;

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
 * while automatically becoming per-CPU when SMP is enabled. */
#define current_pid (this_cpu()->cur_pid)

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

/* Exported IDTR for APs to load during SMP bring-up. */
typedef struct __attribute__((packed)) { uint16_t limit; uint64_t base; } idtr_t;
extern idtr_t bsp_idtr;

/* ---- Functions ---- */
void     sched_init(void);
int      proc_create(const char *name, int parent_pid);
proc_t  *proc_get(int pid);
void     schedule(void);
void     switch_to(proc_t *prev, proc_t *next);
void     yield(void);
void     do_exit(int code);
long     do_clone(long flags, long newsp);
int      do_waitpid(int pid);
int      do_kill(int pid);
void     timer_tick(void);

/* ---- Per-process page tables ---- */
uint64_t pt_clone_user(uint64_t parent_cr3);
void     pt_free_user(uint64_t cr3);

#endif
