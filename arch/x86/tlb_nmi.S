/*
 * tlb_nmi.S  --  cross-CPU TLB shootdown receiver (docs/spec/smp-sched.md,
 * "TLB shootdown").
 *
 * tlb_shootdown (kernel/mm/tlb.c) clears user PTEs, then broadcasts an NMI
 * to every other CPU and waits for each to acknowledge before the frames
 * behind those PTEs go back to the kernel heap. An NMI is the only
 * interrupt a CPU takes while it spins on a lock with IF clear, which is
 * exactly where the issuer's mm_lock would otherwise deadlock a fixed IPI.
 *
 * The vector-2 gate runs on a private IST stack (TSS.ist1), so an NMI that
 * lands in the syscall entry window, still on the user stack, never writes
 * below the user's stack pointer. The handler touches no GS, no lock and
 * no C code: it reloads CR3 with its own value (a full flush of non-global
 * entries, which is every user mapping) and increments the ack counter.
 * Nothing else in MiniOS raises an NMI (LINT1 stays masked), so every NMI
 * is a shootdown; a spurious one costs one flush.
 */
        .text
        .globl  tlb_nmi_entry
tlb_nmi_entry:
        pushq   %rax
        movq    %cr3, %rax
        movq    %rax, %cr3
        lock incl tlb_shoot_acks(%rip)
        popq    %rax
        iretq
