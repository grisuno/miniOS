/** tlb.h - cross-CPU TLB shootdown (docs/spec/smp-sched.md, "TLB shootdown").
 *
 * A PTE cleared or downgraded on one CPU stays cached in another CPU's TLB
 * while that CPU keeps running the same address space (CLONE_VM threads on
 * an AP). Callers clear the PTEs, flush locally, call tlb_shootdown with the
 * address space, and only then release the frames. Safe with any lock held
 * and with interrupts off: the request travels as an NMI.
 */
#ifndef TLB_H
#define TLB_H

/** Pages a release path clears before one shootdown releases them. */
#define TLB_RELEASE_BATCH 32

/* Flush every other CPU currently running address space cr3 and wait for
 * each to acknowledge. Returns at once on one CPU or when no other CPU
 * runs cr3. */
void tlb_shootdown(unsigned long cr3);

/* Shootdowns broadcast and acknowledgement waits that ran out of budget
 * (reported by the smp builtin). */
unsigned long tlb_shootdown_count(void);
unsigned long tlb_shootdown_timeouts(void);

/* The vector-2 gate (arch/x86/tlb_nmi.S) and its acknowledgement counter. */
void tlb_nmi_entry(void);
extern volatile unsigned int tlb_shoot_acks;

#endif
