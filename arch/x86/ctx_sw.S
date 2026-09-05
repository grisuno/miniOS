/*
 * ctx_sw.S  --  x86-64 context switch
 *
 *   void switch_to(proc_t *prev, proc_t *next);
 *
 * Saves all registers into prev->ctx, loads them from next->ctx.
 * First-time processes have ctx.rip = user_trampoline and ctx.rsp
 * pointing at an iretq frame built by proc_create().
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
switch_to:
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

        /* 6. rflags (use rcx as scratch, already restored above) */
        movq   136(%rax), %rcx
        pushq  %rcx
        popfq

        /* 7. rip: push target address and ret into it */
        movq   120(%rax), %rax
        pushq  %rax
        ret


/*
 * user_trampoline -- first entry point for a new process.
 * proc_create() sets ctx.rip = user_trampoline and builds an iretq
 * frame on the kernel stack.  switch_to jumps here via ret.
 */
        .globl  user_trampoline
user_trampoline:
        popq    %rax        /* rip */
        popq    %rcx        /* cs */
        popq    %rdx        /* rflags */
        popq    %rsi        /* rsp */
        popq    %rdi        /* ss */
        pushq   %rdi        /* ss   */
        pushq   %rsi        /* rsp  */
        pushq   %rdx        /* rflags */
        pushq   %rcx        /* cs   */
        pushq   %rax        /* rip  */
        iretq
