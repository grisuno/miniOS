/*
 * ctx_sw.S  --  x86-64 context switch
 *
 *   void switch_to(proc_t *prev, proc_t *next);
 *   void switch_to_notrap(proc_t *prev, proc_t *next);
 *
 * switch_to saves all registers into prev->ctx, loads them from next->ctx.
 * switch_to_notrap skips the save and only restores: the ISR uses it after
 * parking a preempted ring-3 trap frame where next resumes from (see
 * resume_iretq below), because saving the ISR's own kernel registers over
 * that parked state would destroy it.  Both entries share the restore
 * sequence.  First-time processes have ctx.rip = user_trampoline and
 * ctx.rsp pointing at an iretq frame built by proc_create().
 *
 * RFLAGS: saved into ctx as metadata but NEVER restored by the switch.
 * Restoring them (popfq) before the final ret opens a two-instruction
 * window in which an IPI interrupts a half-switched context.  Every
 * resume path sets its own IF instead: resume_iretq and user_trampoline
 * iretq with the parked/spawned rflags, and kernel continuations re-enable
 * interrupts explicitly (schedule sti's after switch_to returns).
 *
 * Restore order (rdi/rsi swap):
 *   1. rax = &next (freed after saving prev's regs)
 *   2. rdi loaded from next's PCB via rax
 *   3. rsi loaded from next's PCB via rax
 *   4. rdi/rsi swapped via xchg to restore correct values
 *   5. all other regs loaded from PCB via rax
 *   6. rsp switched, rflags restored
 *   7. rip pushed and ret'd into
 */
        .text
        .globl  switch_to
        .globl  switch_to_notrap
        .globl  switch_save_only
switch_save_only:
        /* Save-only entry: rdi = prev, (%rsp) = return address.  Captures
         * the live continuation into prev->ctx and RETs to the caller.
         * schedule() uses it under sched_lock so a thread is published
         * READY only with a complete context.  r11d = 0 selects the
         * return; switch_to sets r11d = 1 and falls into the same save
         * before restoring next. */
        xorl    %r11d, %r11d
        jmp     2f
switch_to:
        movl    $1, %r11d
2:
        /* ==== SAVE current process (rdi = &prev) ==== */
        movq    %rax,  0(%rdi)
        movq    %rbx,  8(%rdi)
        movq    %rcx, 16(%rdi)
        movq    %rdx, 24(%rdi)
        movq    %rsi, 32(%rdi)
        movq    %rdi, 40(%rdi)
        movq    %rbp, 48(%rdi)
        movq    %r8,  56(%rdi)
        movq    %r9,  64(%rdi)
        movq    %r10, 72(%rdi)
        movq    %r11, 80(%rdi)
        movq    %r12, 88(%rdi)
        movq    %r13, 96(%rdi)
        movq    %r14,104(%rdi)
        movq    %r15,112(%rdi)
        movq    (%rsp), %rax
        movq    %rax, 120(%rdi)     /* rip */
        leaq    8(%rsp), %rax
        movq    %rax, 128(%rdi)     /* rsp */
        pushfq
        popq    %rax
        movq    %rax, 136(%rdi)     /* rflags */
        movq    %cr3, %rax
        movq    %rax, 144(%rdi)     /* cr3 */
        testl   %r11d, %r11d
        jz      3f
        jmp     switch_to_notrap
3:      ret
switch_to_notrap:
        /* ==== RESTORE next process (rsi = &next) ==== */

        /* 1. Switch page tables */
        movq    144(%rsi), %rax
        movq    %rax, %cr3

        /* 2. rax = &next (rsi is free to use as scratch now) */
        movq    %rsi, %rax

        /* 3. rdi/rsi cross-restore: load both, then swap */
        movq    32(%rax), %rdi      /* rdi = next->ctx.rsi (temp) */
        movq    40(%rax), %rsi      /* rsi = next->ctx.rdi */
        xchgq   %rdi, %rsi         /* rdi = next->ctx.rdi, rsi = next->ctx.rsi */

        /* 4. All other registers from PCB via rax */
        movq     8(%rax), %rbx
        movq    16(%rax), %rcx
        movq    24(%rax), %rdx
        movq    48(%rax), %rbp
        movq    56(%rax), %r8
        movq    64(%rax), %r9
        movq    72(%rax), %r10
        movq    80(%rax), %r11
        movq    88(%rax), %r12
        movq    96(%rax), %r13
        movq   104(%rax), %r14
        movq   112(%rax), %r15

        /* 5. rsp (switch to next's kernel stack) */
        movq   128(%rax), %rsp

        /* 6. rflags: NOT restored here.  Loading the incoming rflags
         * (IF=1 for a live thread) before the final ret leaves a
         * two-instruction window in which an IPI interrupts a
         * half-switched context — fatal under SMP.  Every resume path
         * sets its own IF instead: resume_iretq and user_trampoline
         * iretq with the parked/spawned rflags, and the AP idle loop
         * sti's explicitly after each switch_to return.  ctx.rflags is
         * saved (metadata, host tests) but never loaded by the switch. */

        /* 7. rip: push target address and ret into it */
        movq   120(%rax), %rax
        pushq  %rax
        ret


/*
 * user_trampoline -- first entry point for a new process.
 * proc_create() sets ctx.rip = user_trampoline and builds an iretq
 * frame on the kernel stack.  switch_to jumps here via ret.
 *
 * The frame at ctx.rsp is already a valid iretq image
 * ([rip, cs, rflags, rsp, ss]), so enter it directly: popping and
 * re-pushing the frame (as an older revision did) clobbers the
 * restored registers, which thread entry needs (the start routine
 * arrives with its argument in rdi, like a normal call).
 */
        .globl  user_trampoline
user_trampoline:
        iretq

/*
 * resume_iretq -- resume a process preempted from ring 3.
 * isr_dispatch copies the preempted trap frame to the process's own
 * kernel stack, points ctx.rsp at the copy and ctx.rip here; switch_to
 * rets here in ring 0, and this stub pops the saved registers and
 * iretqs back to ring 3 with the exact preempted state.  Resuming such
 * a context with a plain ret would keep executing user code at CPL 0.
 * GPR order must match trap_frame_t in kernel/sched.c.
 */
        .globl  resume_iretq
resume_iretq:
        popq    %rax
        popq    %rbx
        popq    %rcx
        popq    %rdx
        popq    %rsi
        popq    %rdi
        popq    %rbp
        popq    %r8
        popq    %r9
        popq    %r10
        popq    %r11
        popq    %r12
        popq    %r13
        popq    %r14
        popq    %r15
        iretq
