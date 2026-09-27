/*
 * syscall_entry.S -- SYSCALL trampoline: marshal Linux ABI regs into C ABI.
 *
 * Moved out of kernel.c inline asm so the entry path assembles with
 * standard GNU directives (.cfi unwind info, .type/.size symbols) and
 * reads as assembly instead of a 180-line string literal. Behavior is
 * byte-identical to the old inline block; every immediate derives from
 * headers/syscall_asm.h (whose values kernel.c asserts against the C
 * macros), so growing proc_t can never strand a stale stride here.
 *
 * Every syscall swaps onto the calling proc's own kernel stack
 * (procs[pid].kstack, located as procs + pid * SYSCALL_PROC_T_SIZE +
 * SYSCALL_PROC_KSTACK_OFF), so concurrent thread syscalls never share
 * one: sharing a single entry stack corrupts both frames when a timer
 * tick interleaves two syscalls. Ring-0 ET_REL syscalls use the same
 * per-proc stack of whoever runs them (never the legacy shared
 * `syscall_kstack`, which could not survive two threads entering
 * ring-0 syscalls on one CPU).
 *
 * The entry has no free register and no stack before the swap, so n and
 * the user rip park in per-CPU scratch (cpu_t sc_n/sc_rip at
 * gs:SYSCALL_CPU_SC_N_OFF/gs:SYSCALL_CPU_SC_RIP_OFF): per-CPU, never
 * global, so two CPUs cannot share a slot, and always under cli, so one
 * CPU cannot interleave with itself. The kstack top likewise cannot live
 * in a global (a thread preempted mid-syscall would have its top
 * overwritten by the next thread's entry): it is saved per-pid in
 * sc_top_save[], written at entry and read at exit by the owning thread
 * only. Pid is range-checked at entry (jae 98f, fail closed with -EFAULT
 * touching no memory), so a corrupt cur_pid can neither index
 * sc_top_save OOB nor xchg onto a wild kstack address. The pushed frame
 * layout is identical on both paths (r11/rip/n/a1..a6/pid/pcb), and the
 * kernel never runs on a user stack and never touches the user red zone.
 * The return discriminates on the caller RIP, never on the saved rsp:
 * rsp is attacker-controlled (a ring-3 caller sets any rsp before
 * syscall without faulting, since syscall touches no stack), while rip
 * is constrained to executable mappings (a ring-3 caller can only trap
 * from the user window; heap/kernel fetch faults at CPL3). A syscall
 * trapped from the user window returns with sysretq (ring 3); a ring-0
 * ET_REL syscall trapped from heap/kernel code returns with `jmp *%rcx`,
 * the old contract, because sysretq always lands on ring 3. Checking
 * rsp instead lets a ring-3 attacker set rsp=0, force the jmp path and
 * retain CPL0 with a controlled rip.
 */
#include "syscall_asm.h"

        .data
        .align 8
        .globl syscall_kstack
syscall_kstack:
        .quad 0
        .align 8
kstack_base:
        .quad procs+SYSCALL_PROC_KSTACK_OFF
        .align 8
sc_top_save_addr:
        .quad sc_top_save
        /* Per-pid kstack-top save area, written by the owning thread at
         * entry and read back by it at exit. Indexed by pid like the
         * kstack math; a pid only ever runs on one CPU at a time. */
        .comm sc_top_save, 8*SYSCALL_MAX_PROCS, 8

        .text
        .globl syscall_entry
        .type syscall_entry, @function
syscall_entry:
        .cfi_startproc
        /* A timer tick observing kernel CS with a user GS base reads
         * garbage per-CPU state and dies in this_cpu(). That pairing
         * exists from the syscall insn (kernel CS, user GS) until the
         * entry swapgs, and again from the exit swapgs to sysretq, so
         * both windows run with interrupts off on the ring-3 path.
         * Ring-3 IF is provably 1 (CPL3 cannot clear it). sysretq
         * restores the user IF, so the exit needs no sti; the entry
         * re-enables before ksyscall so blocking calls still work. The
         * whole exit runs under cli too (see below), so per-CPU scratch
         * is never observed mid-update. */
        cli
        cmpq $SYSCALL_USER_WIN_LO, %rsp
        jb 10f
        cmpq $SYSCALL_USER_WIN_HI, %rsp
        jae 10f
        /* --- ring 3: per-proc kernel stack --- */
        swapgs                          /* switch to kernel GS (per-CPU) */
        movq %rax, %gs:SYSCALL_CPU_SC_N_OFF     /* sc_n = n (per-CPU scratch) */
        movq %rcx, %gs:SYSCALL_CPU_SC_RIP_OFF   /* sc_rip = user rip */
        movl %gs:SYSCALL_CPU_CUR_PID_OFF, %eax  /* cur_pid (gs:8 is cpu_id) */
        movq %rax, %gs:SYSCALL_CPU_SC_PID_OFF   /* sc_pid = pid */
        imulq $SYSCALL_PROC_T_SIZE, %rax
        addq kstack_base(%rip), %rax    /* rax = &PCB.kstack */
        jmp 13f
        /* --- ring 0: per-proc kernel stack; swapgs puts the per-CPU base
         * under GS (ET_REL programs run with a base-0 GS descriptor) --- */
10:
        swapgs
        movq %rax, %gs:SYSCALL_CPU_SC_N_OFF
        movq %rcx, %gs:SYSCALL_CPU_SC_RIP_OFF
        movl %gs:SYSCALL_CPU_CUR_PID_OFF, %eax
        movq %rax, %gs:SYSCALL_CPU_SC_PID_OFF
        imulq $SYSCALL_PROC_T_SIZE, %rax
        addq kstack_base(%rip), %rax
        /* --- shared swap + top save (IF=0, rax = &PCB.kstack) --- */
13:
        movl %gs:SYSCALL_CPU_SC_PID_OFF, %ecx    /* pid; rip stays parked in gs:80 */
        cmpl $SYSCALL_MAX_PROCS, %ecx
        jae 98f                         /* pid OOB (incl. -1 idle): fail closed below */
        movq %gs:SYSCALL_CPU_SC_RIP_OFF, %rcx    /* restore caller rip */
        xchgq %rsp, (%rax)              /* rsp = top; rsp saved in the PCB */
        pushq %rax                      /* &PCB.kstack */
        movq %gs:SYSCALL_CPU_SC_PID_OFF, %rcx    /* pid (rip safe in scratch) */
        pushq %rcx                      /* pid */
        pushq %rsi                      /* park a2 (kstack, IF=0) */
        pushq %rdx                      /* park a3 */
        leaq 32(%rsp), %rdx             /* top (4 parks above) */
        movq sc_top_save_addr(%rip), %rsi
        movq %rdx, (%rsi,%rcx,8)        /* per-pid top */
        popq %rdx                       /* a3 */
        popq %rsi                       /* a2 */
        popq %rcx                       /* pid */
        popq %rax                       /* &PCB.kstack (rsp = top again) */
12:
        pushq %rax                      /* 80(%rsp) &PCB.kstack */
        pushq %rcx                      /* 72(%rsp) pid */
        pushq %r9                       /* 64(%rsp) a6 */
        pushq %r8                       /* 56       a5 */
        pushq %r10                      /* 48       a4 */
        pushq %rdx                      /* 40       a3 */
        pushq %rsi                      /* 32       a2 */
        pushq %rdi                      /* 24       a1 */
        pushq %gs:SYSCALL_CPU_SC_N_OFF  /* 16       n / return value slot */
        pushq %gs:SYSCALL_CPU_SC_RIP_OFF /*  8      user rip */
        pushq %r11                      /*  0       user rflags */
        sti                             /* bodies stay preemptible */
11:
        movq 16(%rsp), %rdi             /* C arg1 = n  */
        movq 24(%rsp), %rsi             /* C arg2 = a1 */
        movq 32(%rsp), %rdx             /* C arg3 = a2 */
        movq 40(%rsp), %rcx             /* C arg4 = a3 */
        movq 48(%rsp), %r8              /* C arg5 = a4 */
        movq 56(%rsp), %r9              /* C arg6 = a5 */
        movq 64(%rsp), %rax
        pushq %rax                      /* C arg7 = a6 (stack) */
        call ksyscall
        addq $8, %rsp
        cli                             /* exit runs atomic: scratch is per-CPU */
        movq %rax, %gs:SYSCALL_CPU_SC_RET_OFF    /* sc_ret = return value */
        movl %gs:SYSCALL_CPU_CUR_PID_OFF, %eax
        movq %rax, %gs:SYSCALL_CPU_SC_PID_OFF    /* sc_pid = pid */
        imulq $SYSCALL_PROC_T_SIZE, %rax
        addq kstack_base(%rip), %rax    /* rax = &PCB.kstack */
        cmpq $SYSCALL_USER_WIN_LO, 8(%rsp)   /* caller rip in frame; rsp is spoofable */
        jb 20f
        cmpq $SYSCALL_USER_WIN_HI, 8(%rsp)
        jae 20f
        /* --- ring-3 exit: restore the user rsp saved in the PCB, and put
         * the kstack top back so the next entry finds a stack, not a stale
         * user rsp (running a syscall on a user stack drifts every return
         * until a ret lands on data). --- */
        popq %r11
        popq %rcx                       /* user rip: park next */
        movq %rcx, %gs:SYSCALL_CPU_SC_RIP_OFF
        popq %rax                       /* stale n */
        popq %rdi
        popq %rsi
        popq %rdx
        popq %r10
        popq %r8
        popq %r9
        popq %rcx                       /* pid */
        popq %rax                       /* &PCB.kstack */
        pushq %rdx                      /* park a3 (kstack, IF=0) */
        pushq %rsi                      /* park a2 */
        movq (%rax), %rdx               /* user rsp */
        movq %rdx, %gs:SYSCALL_CPU_SC_TMP_OFF    /* park user rsp (sc_tmp) */
        movq sc_top_save_addr(%rip), %rsi
        movq (%rsi,%rcx,8), %rdx        /* top (pid still in rcx) */
        movq %rdx, (%rax)               /* PCB.kstack = top: invariant restored */
        popq %rsi                       /* a2 */
        popq %rdx                       /* a3 */
        movq %gs:SYSCALL_CPU_SC_TMP_OFF, %rsp    /* rsp = user rsp; no kstack use past here */
        movq %gs:SYSCALL_CPU_SC_RET_OFF, %rax    /* restore return value */
        movq %gs:SYSCALL_CPU_SC_RIP_OFF, %rcx    /* restore user rip */
        swapgs                          /* restore user GS */
        jmp 21f
        /* --- ring-0 exit: same pops, no swapgs --- */
20:
        popq %r11
        popq %rcx
        movq %rcx, %gs:SYSCALL_CPU_SC_RIP_OFF
        popq %rax
        popq %rdi
        popq %rsi
        popq %rdx
        popq %r10
        popq %r8
        popq %r9
        popq %rcx
        popq %rax
        pushq %rdx
        pushq %rsi                      /* park a2 (rsi is scratch below) */
        movq (%rax), %rdx
        movq %rdx, %gs:SYSCALL_CPU_SC_TMP_OFF
        movq sc_top_save_addr(%rip), %rsi
        movq (%rsi,%rcx,8), %rdx
        movq %rdx, (%rax)
        popq %rsi                       /* a2 */
        popq %rdx
        movq %gs:SYSCALL_CPU_SC_TMP_OFF, %rsp
        movq %gs:SYSCALL_CPU_SC_RET_OFF, %rax
        movq %gs:SYSCALL_CPU_SC_RIP_OFF, %rcx
        swapgs                          /* undo the entry swapgs (ring-0 path) */
        sti                             /* ring-0 callers ran with IF=1 (old contract) */
21:
        cmpq $SYSCALL_USER_WIN_LO, %rcx  /* rcx = caller rip; rsp is spoofable */
        jb 1f
        cmpq $SYSCALL_USER_WIN_HI, %rcx
        jae 1f
        sysretq
1:
        jmp *%rcx
        /* --- pid-OOB fail closed: entry validated pid before any mem use,
         * so sc_top_save and the kstack xchg are never indexed wild. No
         * stack or scratch touched yet: r11/rsp still caller-owned, rip
         * reloaded from scratch, -EFAULT in rax, return by rip like 21f. */
98:
        movq %gs:SYSCALL_CPU_SC_RIP_OFF, %rcx    /* caller rip */
        movq $-14, %rax                 /* -EFAULT */
        cmpq $SYSCALL_USER_WIN_LO, %rcx
        jb 97f
        cmpq $SYSCALL_USER_WIN_HI, %rcx
        jae 97f
        swapgs                          /* restore user GS */
        sysretq
97:
        swapgs                          /* undo the entry swapgs (ring-0 path) */
        sti                             /* ring-0 callers ran with IF=1 */
        jmp *%rcx
        .cfi_endproc
        .size syscall_entry, .-syscall_entry
