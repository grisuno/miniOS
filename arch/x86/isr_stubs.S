/*
 * isr_stubs.S  --  256 interrupt service routine stubs
 *
 * Each stub pushes a dummy error code (if the CPU does not push one)
 * and the vector number, then jumps to isr_common.
 *
 * isr_common saves all general-purpose registers into a trap_frame_t
 * on the stack, calls the C dispatcher isr_dispatch(vector, frame),
 * then restores registers and returns via iretq.
 *
 * Exceptions that push an error code on the CPU stack:
 *   8 (double fault), 10 (invalid TSS), 11 (segment NP),
 *   12 (stack-segment fault), 13 (GPF), 14 (page fault),
 *   17 (alignment check), 21 (machine check), 29 (virtualization),
 *   30 (security exception).
 *
 * All other vectors (including 32-47 hardware IRQs) get a dummy $0.
 */

        .altmacro

/* ------------------------------------------------------------------ */
/*  Single macro that emits the correct stub for any vector.           */
/*  The .if uses assembler-time evaluation -- no runtime overhead.     */
/* ------------------------------------------------------------------ */
        .macro ISR_STUB vec
        .globl isr_stub_\vec
isr_stub_\vec:
        .if     \vec == 8  || \vec == 10 || \vec == 11 || \
                \vec == 12 || \vec == 13 || \vec == 14 || \
                \vec == 17 || \vec == 21 || \vec == 29 || \vec == 30
        pushq   $\vec                           /* CPU already pushed error code */
        .else
        pushq   $0                              /* dummy error code */
        pushq   $\vec                           /* vector number */
        .endif
        jmp     isr_common
        .endm

/* ------------------------------------------------------------------ */
/*  Generate all 256 stubs -- one .rept, zero duplication.             */
/* ------------------------------------------------------------------ */
        .text
.set v, 0
.rept 256
        ISR_STUB %v
.set v, v+1
.endr

/* ------------------------------------------------------------------ */
/*  trap_frame_t layout (must match sched.c)                           */
/*                                                                     */
/*  Offset from RSP after `subq $TF_SIZE, %rsp`:                      */
/*    0x00 tf_rax       0x08 tf_rbx       0x10 tf_rcx                */
/*    0x18 tf_rdx       0x20 tf_rsi       0x28 tf_rdi                */
/*    0x30 tf_rbp       0x38 tf_r8        0x40 tf_r9                 */
/*    0x48 tf_r10       0x50 tf_r11       0x58 tf_r12                */
/*    0x60 tf_r13       0x68 tf_r14       0x70 tf_r15                */
/*    0x78 tf_rip       0x80 tf_cs        0x88 tf_rflags             */
/*    0x90 tf_rsp       0x98 tf_ss        0xA0 tf_vector             */
/*    0xA8 tf_errcode                                                */
/*                                                                     */
/*  Above TF_SIZE: vector(8) + errcode(8) + rip(8) + cs(8) +         */
/*                 rflags(8) + rsp(8) + ss(8)  = 56 bytes            */
/* ------------------------------------------------------------------ */
        .struct 0
tf_rax:     .quad 0
tf_rbx:     .quad 0
tf_rcx:     .quad 0
tf_rdx:     .quad 0
tf_rsi:     .quad 0
tf_rdi:     .quad 0
tf_rbp:     .quad 0
tf_r8:      .quad 0
tf_r9:      .quad 0
tf_r10:     .quad 0
tf_r11:     .quad 0
tf_r12:     .quad 0
tf_r13:     .quad 0
tf_r14:     .quad 0
tf_r15:     .quad 0
tf_rip:     .quad 0
tf_cs:      .quad 0
tf_rflags:  .quad 0
tf_rsp:     .quad 0
tf_ss:      .quad 0
tf_vector:  .quad 0
tf_errcode: .quad 0
TF_SIZE = .

/* ------------------------------------------------------------------ */
/*  isr_common -- save regs, call C, restore, iretq                   */
/* ------------------------------------------------------------------ */
        .text
        .globl isr_common
isr_common:
        /* Allocate space for the trap frame */
        subq    $TF_SIZE, %rsp

        /* Save all general-purpose registers */
        movq    %rax, tf_rax(%rsp)
        movq    %rbx, tf_rbx(%rsp)
        movq    %rcx, tf_rcx(%rsp)
        movq    %rdx, tf_rdx(%rsp)
        movq    %rsi, tf_rsi(%rsp)
        movq    %rdi, tf_rdi(%rsp)
        movq    %rbp, tf_rbp(%rsp)
        movq    %r8,  tf_r8(%rsp)
        movq    %r9,  tf_r9(%rsp)
        movq    %r10, tf_r10(%rsp)
        movq    %r11, tf_r11(%rsp)
        movq    %r12, tf_r12(%rsp)
        movq    %r13, tf_r13(%rsp)
        movq    %r14, tf_r14(%rsp)
        movq    %r15, tf_r15(%rsp)

        /* Copy the CPU interrupt frame + stub-pushed values into the
         * trap frame.  After subq $TF_SIZE the layout above RSP is:
         *   (%rsp) + TF_SIZE + 0  = vector   (pushed by stub)
         *   (%rsp) + TF_SIZE + 8  = errcode  (pushed by stub or CPU)
         *   (%rsp) + TF_SIZE + 16 = rip      (CPU frame)
         *   (%rsp) + TF_SIZE + 24 = cs
         *   (%rsp) + TF_SIZE + 32 = rflags
         *   (%rsp) + TF_SIZE + 40 = rsp
         *   (%rsp) + TF_SIZE + 48 = ss
         */
        movq    TF_SIZE + 0(%rsp), %rax
        movq    %rax, tf_vector(%rsp)
        movq    TF_SIZE + 8(%rsp), %rax
        movq    %rax, tf_errcode(%rsp)
        movq    TF_SIZE + 16(%rsp), %rax
        movq    %rax, tf_rip(%rsp)
        movq    TF_SIZE + 24(%rsp), %rax
        movq    %rax, tf_cs(%rsp)
        movq    TF_SIZE + 32(%rsp), %rax
        movq    %rax, tf_rflags(%rsp)
        movq    TF_SIZE + 40(%rsp), %rax
        movq    %rax, tf_rsp(%rsp)
        movq    TF_SIZE + 48(%rsp), %rax
        movq    %rax, tf_ss(%rsp)

        /* Call C dispatcher: isr_dispatch(vector, &frame) */
        movq    tf_vector(%rsp), %rdi          /* arg1 = vector */
        movq    %rsp, %rsi                     /* arg2 = &frame */
        call    isr_dispatch

        /* Restore all general-purpose registers from the trap frame */
        movq    tf_rax(%rsp), %rax
        movq    tf_rbx(%rsp), %rbx
        movq    tf_rcx(%rsp), %rcx
        movq    tf_rdx(%rsp), %rdx
        movq    tf_rsi(%rsp), %rsi
        movq    tf_rdi(%rsp), %rdi
        movq    tf_rbp(%rsp), %rbp
        movq    tf_r8(%rsp),  %r8
        movq    tf_r9(%rsp),  %r9
        movq    tf_r10(%rsp), %r10
        movq    tf_r11(%rsp), %r11
        movq    tf_r12(%rsp), %r12
        movq    tf_r13(%rsp), %r13
        movq    tf_r14(%rsp), %r14
        movq    tf_r15(%rsp), %r15

        /* Tear down the trap frame, skip vector + errcode (16 bytes),
         * then iretq with the CPU's interrupt frame. */
        addq    $TF_SIZE, %rsp
        addq    $16, %rsp
        iretq

/* ------------------------------------------------------------------ */
/*  Stub address table -- 256 quadwords, one per vector.               */
/*  Lets C code look up a stub by index without 256 extern decls.      */
/* ------------------------------------------------------------------ */
        .macro TABLE_ENTRY vec
        .quad   isr_stub_\vec
        .endm

        .data
        .globl  isr_stub_table
        .balign 8
isr_stub_table:
.set v, 0
.rept 256
        TABLE_ENTRY %v
.set v, v+1
.endr
