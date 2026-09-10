/* kernel.c -- Mediator: boot orchestration and the syscall trampoline.
 *
 * Bounded-Context map (DDD): this file owns NO subsystem state. Execution
 * output lives in kernel/console.c, scheduling in kernel/sched.c, memory in
 * kernel/mm.c + vma.c, files in fs/, drivers in drivers/, network in net/.
 * kmain below only injects init order into those subsystems; the syscall
 * trampoline stays here because it is position-sensitive asm bound to the
 * proc_t layout asserted by sched.c. New logic belongs in a subsystem file,
 * never here. */
#include "kernel.h"
#include "net.h"
#include "bootdefs.h"
#include "minifs.h"
#include "ide.h"
#include "block.h"
#include "sched.h"
#include "vga_fb.h"
#include "sb16.h"
#include "smp.h"
#include "arch/x86/msr.h"

/* Text console, output capture and libc names: kernel/console.c. */
/* Scrollback ring: kernel/scrollback.c. */

/* Execution console, output capture and libc names: kernel/console.c. */


/* ================================================================
 *  Keyboard driver — see drivers/kbd.c
 * ================================================================ */


/* ================================================================
 *  Memory allocator — dlmalloc backend over the fixed kernel heap.
 *  kmalloc/free/calloc/realloc delegate to a private mspace rooted at
 *  [HEAP_BASE, HEAP_BASE+HEAP_SIZE) (see third_party/dlmalloc). The
 *  mspace is built with HAVE_MORECORE=0 and HAVE_MMAP=0, so it can
 *  never grow beyond the heap; an exhausted heap returns 0 exactly
 *  like the first-fit allocator it replaced.
 * ================================================================ */

/* ---- Physical memory map (identity-mapped 0..1GB by the bootloader) ----
 * The user-window and kernel-heap layout lives in progs/minios_abi.h (single
 * source of truth) and is surfaced through kernel.h, so a layout change is a
 * one-line edit in one file instead of a cross-file address hunt.
 *   0x00000000 .. 0x00100000   BIOS / kernel image / page tables / stack
 *   0x00400000 .. 0x0C000000   user program region (ELF load addr + brk)
 *   0x0C000000 .. 0x18000000   192 MB kernel heap (HEAP_BASE/HEAP_SIZE)
 */

/* Asm-safe (no UL suffix) mirror of the user window for the syscall-entry
 * return discriminator; the trampoline is a raw string literal, so the C
 * preprocessor cannot paste the UL-suffixed macros into it. The values must
 * track minios_abi.h; the _Static_asserts below prove they do. */
#define USER_WIN_LO     0x00400000
#define USER_WIN_HI     0x0C000000
#define STR_(x) #x
#define STR(x)  STR_(x)

/* The kernel's layout constants are derived from minios_abi.h, and the
 * asm-safe mirrors above are checked against them at compile time, so a
 * layout edit in the ABI header can never silently leave the syscall return
 * discriminator, the page-table zone sizing or a ring-3 program out of step. */
_Static_assert(USER_WIN_LO == MINIOS_USER_LOAD_BASE, "USER_WIN_LO drift");
_Static_assert(USER_WIN_HI == MINIOS_USER_LOAD_END, "USER_WIN_HI drift");
_Static_assert(USER_LOAD_BASE == MINIOS_USER_LOAD_BASE, "USER_LOAD_BASE drift");
_Static_assert(USER_LOAD_END == MINIOS_USER_LOAD_END, "USER_LOAD_END drift");
_Static_assert(USER_STACK_TOP == MINIOS_USER_STACK_TOP, "USER_STACK_TOP drift");
_Static_assert(USER_BRK_END == MINIOS_USER_BRK_END, "USER_BRK_END drift");
_Static_assert(HEAP_BASE == MINIOS_HEAP_BASE, "HEAP_BASE drift");
_Static_assert(HEAP_SIZE == MINIOS_HEAP_SIZE, "HEAP_SIZE drift");

/* SYSCALL/SYSRET setup and page table code moved to:
 *   arch/x86/msr.h          - wrmsr/rdmsr
 *   kernel/mm/paging.c      - page table management
 *   kernel/mm/swap.c        - swap-out/swap-in
 */



/* Code moved to kernel/mm/paging.c */



/* ================================================================
 *  Ramdisk file system
 * ================================================================ */





/* ================================================================
 *  Symbol table (for resolving program references)
 * ================================================================ */

#define KSYM_MAX 256




/* ---- SYSCALL/SYSRET setup ---------------------------------- */

extern void syscall_entry(void);
extern unsigned long syscall_kstack;

void syscall_init(void) {
    /* SYSCALL loads CS=0x08, SS=0x10 from STAR[47:32]. SYSRET derives its
     * selectors from STAR[63:48]: CS = n + 16 = 0x20 (user code), SS =
     * n + 8 = 0x18 (user data), the Linux layout. */
    wrmsr(MSR_STAR,  ((unsigned long)GDT64_DATA_SEL << 48) | ((unsigned long)GDT64_CODE_SEL << 32));
    wrmsr(MSR_LSTAR, (unsigned long)syscall_entry);
    wrmsr(MSR_SFMASK, 0x600); /* clear DF and IF on entry */
    wrmsr(MSR_EFER, rdmsr(MSR_EFER) | 1); /* SCE: enable SYSCALL */
}


/* ---- Syscall dispatcher moved to kernel/syscalls.c -------------------- */

extern long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6);


/* ksyscall_dispatch, kfd_table, user_range_ok, user_str_ok, k_syscall_spawn
 * moved to kernel/syscalls.c */


/* ---- syscall trampoline: marshal Linux ABI regs into the C ABI ----------
 * Every syscall swaps onto the calling proc's own kernel stack
 * (procs[pid].kstack, located as procs + pid * 304 + 168; the C side
 * asserts both numbers), so concurrent thread syscalls never share one:
 * sharing a single entry stack corrupts both frames when a timer tick
 * interleaves two syscalls.  Ring-0 ET_REL syscalls use the same
 * per-proc stack of whoever runs them (never the legacy shared
 * `syscall_kstack`, which could not survive two threads entering
 * ring-0 syscalls on one CPU).
 *
 * The entry has no free register and no stack before the swap, so n and
 * the user rip park in per-CPU scratch (cpu_t sc_n/sc_rip at gs:72/80,
 * asserted below): per-CPU, never global, so two CPUs cannot share a
 * slot, and always under cli, so one CPU cannot interleave with itself.
 * The kstack top likewise cannot live in a global (a thread preempted
 * mid-syscall would have its top overwritten by the next thread's
 * entry): it is saved per-pid in sc_top_save[], written at entry and
 * read at exit by the owning thread only.  The pushed frame layout is
 * identical on both paths (r11/rip/n/a1..a6/pid/pcb), and the kernel
 * never runs on a user stack and never touches the user red zone.  The
 * return discriminates on the restored rsp: a syscall that came from
 * ring 3 ran on the user stack in the user window and returns with
 * sysretq (ring 3); a ring-0 ET_REL syscall ran on a kernel stack and
 * returns with `jmp *%rcx`, the old contract, because sysretq always
 * lands on ring 3. */

/* cpu_t layout contract for the syscall_entry asm below: it reads
 * cur_pid at gs:12 (gs:0 is the self pointer for this_cpu(), gs:8 is
 * cpu_id).  Reading gs:8 instead resolves every thread to the wrong
 * kstack (0 on the BSP, 1 on APs): harmless while a single process
 * runs, fatal as soon as two threads syscall concurrently. */
_Static_assert(__builtin_offsetof(cpu_t, cur_pid) == 12, "cpu cur_pid off");
_Static_assert(__builtin_offsetof(cpu_t, cpu_id) == 8, "cpu cpu_id off");
_Static_assert(__builtin_offsetof(cpu_t, sc_n) == 72, "cpu sc_n off");
_Static_assert(__builtin_offsetof(cpu_t, sc_rip) == 80, "cpu sc_rip off");
_Static_assert(__builtin_offsetof(cpu_t, sc_pid) == 88, "cpu sc_pid off");
_Static_assert(__builtin_offsetof(cpu_t, sc_ret) == 96, "cpu sc_ret off");
_Static_assert(__builtin_offsetof(cpu_t, sc_tmp) == 112, "cpu sc_tmp off");

/* Per-pid kstack-top save area, written by the owning thread at entry
 * and read back by it at exit (see above).  Indexed by pid like the
 * kstack math; a pid only ever runs on one CPU at a time, so no lock.
 * "used" because the only references live in the asm string below. */
static unsigned long sc_top_save[MAX_PROCS] __attribute__((used));

__asm__(
    ".text\n"
    ".global syscall_kstack\n"
    ".data\n"
    ".align 8\n"
    "syscall_kstack:\n"
    "  .quad 0\n"
    ".align 8\n"
    "kstack_base:\n"
    "  .quad procs+168\n"
    ".align 8\n"
    "sc_top_save_addr:\n"
    "  .quad sc_top_save\n"
    ".text\n"
    ".global syscall_entry\n"
    "syscall_entry:\n"
    /* A timer tick observing kernel CS with a user GS base reads garbage
     * per-CPU state and dies in this_cpu().  That pairing exists from the
     * syscall insn (kernel CS, user GS) until the entry swapgs, and again
     * from the exit swapgs to sysretq, so both windows run with interrupts
     * off on the ring-3 path.  Ring-3 IF is provably 1 (CPL3 cannot clear
     * it).  sysretq restores the user IF, so the exit needs no sti;
     * the entry re-enables before ksyscall so blocking calls still work.
     * The whole exit runs under cli too (see below), so per-CPU scratch
     * is never observed mid-update. */
    "  cli\n"
    "  cmpq $" STR(USER_WIN_LO) ", %rsp\n"
    "  jb 10f\n"
    "  cmpq $" STR(USER_WIN_HI) ", %rsp\n"
    "  jae 10f\n"
    /* --- ring 3: per-proc kernel stack --- */
    "  swapgs\n"                     /* switch to kernel GS (per-CPU) */
    "  movq %rax, %gs:72\n"         /* sc_n = n (per-CPU scratch) */
    "  movq %rcx, %gs:80\n"         /* sc_rip = user rip */
    "  movl %gs:12, %eax\n"         /* cur_pid (gs:8 is cpu_id) */
    "  movq %rax, %gs:88\n"         /* sc_pid = pid */
    "  imulq $" STR(PROC_T_SIZE) ", %rax\n"  /* == sizeof(proc_t), see sched.h */
    "  addq kstack_base(%rip), %rax\n"  /* rax = &PCB.kstack */
    "  jmp 13f\n"
    /* --- ring 0: per-proc kernel stack; swapgs puts the per-CPU base
     * under GS (ET_REL programs run with a base-0 GS descriptor) --- */
    "10:\n"
    "  swapgs\n"
    "  movq %rax, %gs:72\n"
    "  movq %rcx, %gs:80\n"
    "  movl %gs:12, %eax\n"
    "  movq %rax, %gs:88\n"
    "  imulq $" STR(PROC_T_SIZE) ", %rax\n"
    "  addq kstack_base(%rip), %rax\n"
    /* --- shared swap + top save (IF=0, rax = &PCB.kstack) --- */
    "13:\n"
    "  xchgq %rsp, (%rax)\n"        /* rsp = top; rsp saved in the PCB */
    "  pushq %rax\n"                /* &PCB.kstack */
    "  movq %gs:88, %rcx\n"         /* pid (rip safe in scratch) */
    "  pushq %rcx\n"                /* pid */
    "  pushq %rsi\n"                /* park a2 (kstack, IF=0) */
    "  pushq %rdx\n"                /* park a3 */
    "  leaq 32(%rsp), %rdx\n"       /* top (4 parks above) */
    "  movq sc_top_save_addr(%rip), %rsi\n"
    "  movq %rdx, (%rsi,%rcx,8)\n"  /* per-pid top */
    "  popq %rdx\n"                 /* a3 */
    "  popq %rsi\n"                 /* a2 */
    "  popq %rcx\n"                 /* pid */
    "  popq %rax\n"                 /* &PCB.kstack (rsp = top again) */
    "12:\n"
    "  pushq %rax\n"                /* 80(%rsp) &PCB.kstack */
    "  pushq %rcx\n"                /* 72(%rsp) pid */
    "  pushq %r9\n"              /* 64(%rsp) a6 */
    "  pushq %r8\n"              /* 56       a5 */
    "  pushq %r10\n"             /* 48       a4 */
    "  pushq %rdx\n"             /* 40       a3 */
    "  pushq %rsi\n"             /* 32       a2 */
    "  pushq %rdi\n"             /* 24       a1 */
    "  pushq %gs:72\n"           /* 16       n / return value slot */
    "  pushq %gs:80\n"           /*  8       user rip */
    "  pushq %r11\n"             /*  0       user rflags */
    "  sti\n"                       /* bodies stay preemptible */
    "11:\n"
    "  movq 16(%rsp), %rdi\n"    /* C arg1 = n  */
    "  movq 24(%rsp), %rsi\n"    /* C arg2 = a1 */
    "  movq 32(%rsp), %rdx\n"    /* C arg3 = a2 */
    "  movq 40(%rsp), %rcx\n"    /* C arg4 = a3 */
    "  movq 48(%rsp), %r8\n"     /* C arg5 = a4 */
    "  movq 56(%rsp), %r9\n"     /* C arg6 = a5 */
    "  movq 64(%rsp), %rax\n"
    "  pushq %rax\n"             /* C arg7 = a6 (stack) */
    "  call ksyscall\n"
    "  addq $8, %rsp\n"
    "  cli\n"                       /* exit runs atomic: scratch is per-CPU */
    "  movq %rax, %gs:96\n"      /* sc_ret = return value */
    "  movl %gs:12, %eax\n"
    "  movq %rax, %gs:88\n"      /* sc_pid = pid */
    "  imulq $304, %rax\n"
    "  addq kstack_base(%rip), %rax\n"  /* rax = &PCB.kstack */
    "  cmpq $" STR(USER_WIN_LO) ", (%rax)\n"  /* origin = saved user rsp */
    "  jb 20f\n"
    "  cmpq $" STR(USER_WIN_HI) ", (%rax)\n"
    "  jae 20f\n"
    /* --- ring-3 exit: restore the user rsp saved in the PCB, and put
     * the kstack top back so the next entry finds a stack, not a stale
     * user rsp (running a syscall on a user stack drifts every return
     * until a ret lands on data). --- */
    "  popq %r11\n"
    "  popq %rcx\n"              /* user rip: park next */
    "  movq %rcx, %gs:80\n"
    "  popq %rax\n"              /* stale n */
    "  popq %rdi\n"
    "  popq %rsi\n"
    "  popq %rdx\n"
    "  popq %r10\n"
    "  popq %r8\n"
    "  popq %r9\n"
    "  popq %rcx\n"              /* pid */
    "  popq %rax\n"              /* &PCB.kstack */
    "  pushq %rdx\n"             /* park a3 (kstack, IF=0) */
    "  pushq %rsi\n"             /* park a2 */
    "  movq (%rax), %rdx\n"      /* user rsp */
    "  movq %rdx, %gs:112\n"     /* park user rsp (sc_tmp) */
    "  movq sc_top_save_addr(%rip), %rsi\n"
    "  movq (%rsi,%rcx,8), %rdx\n"  /* top (pid still in rcx) */
    "  movq %rdx, (%rax)\n"      /* PCB.kstack = top: invariant restored */
    "  popq %rsi\n"              /* a2 */
    "  popq %rdx\n"              /* a3 */
    "  movq %gs:112, %rsp\n"     /* rsp = user rsp; no kstack use past here */
    "  movq %gs:96, %rax\n"      /* restore return value */
    "  movq %gs:80, %rcx\n"      /* restore user rip */
    "  swapgs\n"                     /* restore user GS */
    "  jmp 21f\n"
    /* --- ring-0 exit: same pops, no swapgs --- */
    "20:\n"
    "  popq %r11\n"
    "  popq %rcx\n"
    "  movq %rcx, %gs:80\n"
    "  popq %rax\n"
    "  popq %rdi\n"
    "  popq %rsi\n"
    "  popq %rdx\n"
    "  popq %r10\n"
    "  popq %r8\n"
    "  popq %r9\n"
    "  popq %rcx\n"
    "  popq %rax\n"
    "  pushq %rdx\n"
    "  pushq %rsi\n"             /* park a2 (rsi is scratch below) */
    "  movq (%rax), %rdx\n"
    "  movq %rdx, %gs:112\n"
    "  movq sc_top_save_addr(%rip), %rsi\n"
    "  movq (%rsi,%rcx,8), %rdx\n"
    "  movq %rdx, (%rax)\n"
    "  popq %rsi\n"              /* a2 */
    "  popq %rdx\n"
    "  movq %gs:112, %rsp\n"
    "  movq %gs:96, %rax\n"
    "  movq %gs:80, %rcx\n"
    "  swapgs\n"                 /* undo the entry swapgs (ring-0 path) */
    "  sti\n"                    /* ring-0 callers ran with IF=1 (old contract) */
    "21:\n"
    "  cmpq $" STR(USER_WIN_LO) ", %rsp\n"
    "  jb 1f\n"
    "  cmpq $" STR(USER_WIN_HI) ", %rsp\n"
    "  jae 1f\n"
    "  sysretq\n"
    "1:\n"
    "  jmp *%rcx\n"
);


/* k_exec_user, k_run_rel, kexit moved to kernel/exec.c */


/* The entire shell (console line reader, history, completion, built-in
 * editor, builtin commands, shell_run) moved to kernel/shell.c. */


/* Libc symbol registration: kernel/console.c. */


/* ================================================================
 *  Kernel entry point
 * ================================================================ */

extern char ramdisk_start[];
extern char ramdisk_end[];
extern char ramdisk_size[];

__attribute__((section(".init.text")))
void kmain(void) {
    __asm__ volatile(
        "mov $0x10, %%ax\n"
        "mov %%ax, %%ds\n"
        "mov %%ax, %%es\n"
        "mov %%ax, %%fs\n"
        "mov %%ax, %%gs\n"
        "mov %%ax, %%ss\n"
        "mov $0x90000, %%rsp\n"
        ::: "ax"
    );

    /* Enable SSE so loaded programs (and Linux binaries) may use XMM/SSE2.
     * CR0: clear EM (bit 2), set MP (bit 1); CR4: set OSFXSR|OSXMMEXCPT. */
    __asm__ volatile(
        "mov %%cr0, %%rax\n"
        "and $0xFFFFFFFFFFFFFFFB, %%rax\n"
        "or  $0x2, %%rax\n"
        "mov %%rax, %%cr0\n"
        "mov %%cr4, %%rax\n"
        "or  $0x600, %%rax\n"
        "mov %%rax, %%cr4\n"
        ::: "rax"
    );

    serial_init();
    vga_clear();
    /* Mask every PIC line immediately: until sched_init's pic_init
     * remaps the 8259s and installs the IDT, the power-on vector base
     * (0x70 for the slave) delivers hardware IRQs (e.g. IDE IRQ14
     * during the pre-IDT disk probe) into the real-mode IVT, whose
     * garbage gates triple-fault the machine. */
    outb(0x21, 0xFF);
    outb(0xA1, 0xFF);
    vga_puts("MiniOS Kernel v0.3\n====================\n");

    kallocator_init();
    ramdisk_init();
    register_libc_symbols();
    syscall_init();
    vga_fb_boot_config();
    mm_setup_protections();
    kprintf("fb: %dx%d pitch %d bpp %d base 0x%lx\n",
            fb_width, fb_height, fb_pitch, fb_bpp, fb_phys_base);
    kprintf("kernel: physical base 0x%x, user pages 4 KB with NX\n",
            *(unsigned *)BOOT_KASLR_ADDR);
    kprintf("isolation: user window %x..%x ring 3, syscall ABI on %x\n",
            USER_LOAD_BASE, USER_LOAD_END, SYS_KSTK_TOP);
    net_init();

    /* ramdisk_size is an absolute linker symbol whose address IS the
     * image size (see kernel.ld); no pointer subtraction involved. */
    if ((unsigned long)ramdisk_size > 0) {
        ramdisk_setup_from(ramdisk_start, (unsigned)(unsigned long)ramdisk_size);
    }

    block_init();
    minifs_init();
    if (ide_present()) {
        if (minifs_mount() < 0) {
            kprintf("minifs: no filesystem found on disk\n");
        }
    }

    /* Register VFS drivers.  Ramdisk is always available; MiniFS is
     * registered only when the IDE disk was found and mounted. */
    vfs_register_builtins();

    kprintf("Heap: %d MB  Symbols: %d  (Linux ELF: syscall ABI ready)\n",
            (int)(HEAP_SIZE >> 20), ksym_count);

    /* Initialize the scheduler: IDT, TSS, PIC, PIT timer.
     * This enables interrupts and the 100 Hz timer tick. */
    sched_init();
    kprintf("Scheduler: IDT 256 entries, TSS loaded, PIT 100 Hz, preemptive\n");

    vga_fb_init();

    /* Probe the Sound Blaster 16 for real audio; fall back to the PC speaker
     * when none is present. */
    if (sb16_init())
        kprintf("sb16: DSP probed, 8-bit %d Hz DMA channel 1\n", 22050);
    else
        kprintf("sb16: not present, PC speaker stays the audio sink\n");

    /* Wake the application processors; fail-safe, APs idle, system unchanged. */
    smp_init();

    shell_run();
}
