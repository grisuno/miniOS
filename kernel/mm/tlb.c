/** tlb.c - cross-CPU TLB shootdown (docs/spec/smp-sched.md, "TLB shootdown").
 *
 * munmap, mremap and file-range release free heap frames the moment their
 * PTEs are cleared. A CLONE_VM sibling running on another CPU still holds
 * the old translation in its TLB and kept reading and writing a frame the
 * heap had already handed to someone else: user data and kernel structures
 * were corrupted at random once glibc threads ran on the AP. Release paths
 * now clear a batch of PTEs, call tlb_shootdown, then free the batch.
 *
 * The request is an NMI (smp_nmi_broadcast): the issuer usually holds
 * mm_lock with interrupts off, and a CPU waiting for that lock spins with
 * IF clear, so a fixed IPI would never be taken and the wait would deadlock.
 * The receiver (arch/x86/tlb_nmi.S) reloads CR3 and acknowledges.
 */
#include "kernel.h"
#include "sched.h"
#include "smp.h"
#include "spinlock.h"
#include "tlb.h"

/** pause iterations the issuer waits for every acknowledgement before it
 * reports a lost one (an NMI is never masked, so this is a hardware or
 * emulator fault, not a scheduling delay). */
#define TLB_SHOOT_SPIN_MAX 10000000UL

volatile unsigned int tlb_shoot_acks;

static spinlock_t tlb_lock = SPINLOCK_INIT;
static volatile unsigned long tlb_shoots;
static volatile unsigned long tlb_timeouts;

/* 1 when another online CPU is running address space cr3 right now. The
 * read races with switches harmlessly: the PTEs are already cleared, so a
 * CPU that loads cr3 after this check starts with a flushed TLB, and one
 * leaving it is about to reload CR3 anyway. */
static int tlb_others_on(unsigned long cr3) {
    int me = this_cpu()->cpu_id;
    int c;
    for (c = 0; c < cpu_count && c < MAX_CPUS; c++) {
        int pid;
        if (c == me) continue;
        pid = cpus[c].cur_pid;
        if (pid < 0 || pid >= MAX_PROCS) continue;
        if (procs[pid].ctx.cr3 == cr3) return 1;
    }
    return 0;
}

void tlb_shootdown(unsigned long cr3) {
    irqflags_t flags;
    unsigned long spins = 0;
    unsigned int want;
    if (cpu_count < 2) return;
    if (!tlb_others_on(cr3)) return;
    spin_lock_irqsave(&tlb_lock, &flags);
    want = (unsigned int)(cpu_count - 1);
    __atomic_store_n(&tlb_shoot_acks, 0u, __ATOMIC_SEQ_CST);
    smp_nmi_broadcast();
    while (__atomic_load_n(&tlb_shoot_acks, __ATOMIC_SEQ_CST) < want) {
        if (++spins >= TLB_SHOOT_SPIN_MAX) {
            tlb_timeouts++;
            serial_puts("tlb: shootdown acknowledgement lost\n");
            break;
        }
        __asm__ volatile("pause" ::: "memory");
    }
    tlb_shoots++;
    spin_unlock_irqrestore(&tlb_lock, flags);
}

unsigned long tlb_shootdown_count(void) {
    return tlb_shoots;
}

unsigned long tlb_shootdown_timeouts(void) {
    return tlb_timeouts;
}
