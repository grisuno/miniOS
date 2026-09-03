/* exec.c - Process execution: setjmp/longjmp, k_exec_user, k_run_rel, kexit.
 *
 * Extracted from kernel.c. Contains the ring-3 entry/exit infrastructure:
 * ksetjmp/klongjmp (asm), setup_user_stack, k_exec_user (enter ring 3),
 * k_run_rel (run ET_REL as function), kexit (libc exit trampoline),
 * and k_user_fault_return (ISR fault handler escape hatch).
 */

#include "kernel.h"
#include "bootdefs.h"
#include "arch/x86/msr.h"
#include "vga_fb.h"
#include "sched.h"
#include "drivers/kbd.h"

/* kjmpbuf is declared in kernel.h.  ksetjmp/klongjmp are asm trampolines
 * for unwinding back to the shell on exit() or fault. */
__asm__(
    ".text\n"
    ".global ksetjmp\n"
    "ksetjmp:\n"
    "  movq %rbx,  0(%rdi)\n"
    "  movq %rbp,  8(%rdi)\n"
    "  movq %r12, 16(%rdi)\n"
    "  movq %r13, 24(%rdi)\n"
    "  movq %r14, 32(%rdi)\n"
    "  movq %r15, 40(%rdi)\n"
    "  leaq 8(%rsp), %rax\n"
    "  movq %rax, 48(%rdi)\n"
    "  movq (%rsp), %rax\n"
    "  movq %rax, 56(%rdi)\n"
    "  xorl %eax, %eax\n"
    "  ret\n"
    ".global klongjmp\n"
    "klongjmp:\n"
    "  movq  0(%rdi), %rbx\n"
    "  movq  8(%rdi), %rbp\n"
    "  movq 16(%rdi), %r12\n"
    "  movq 24(%rdi), %r13\n"
    "  movq 32(%rdi), %r14\n"
    "  movq 40(%rdi), %r15\n"
    "  movq 48(%rdi), %rsp\n"
    "  movl %esi, %eax\n"
    "  testl %eax, %eax\n"
    "  jnz 1f\n"
    "  incl %eax\n"
    "1:\n"
    "  jmp *56(%rdi)\n"
);

/* Shared execution state. */
kjmpbuf exec_return;
int     exec_exit_code;

/* VGA mode tracking: set/cleared by k_exec_user and k_run_rel when a
 * graphics program owns the display. */
static int vga_mode13h;
static int graphics_program_ran;

void vga_mode_set(int on)       { vga_mode13h = on; }
int  vga_mode_is_active(void)   { return vga_mode13h; }
void vga_gfx_ran_set(int on)    { graphics_program_ran = on; }

/* Called from the ISR exception handler when a ring-3 user program faults. */
void k_user_fault_return(void) {
    exec_exit_code = EFAULT;
    __asm__ volatile(
        "mov %[kdata], %%ax\n"
        "mov %%ax, %%ds\n"
        "mov %%ax, %%es\n"
        "mov %%ax, %%fs\n"
        "mov %%ax, %%gs\n"
        :: [kdata] "i"(GDT64_DATA_SEL)
        : "ax", "memory");
    wrmsr(MSR_FSBASE, 0);
    wrmsr(MSR_GSBASE, 0);
    klongjmp(&exec_return, 1);
}

/* ---- Build the SysV initial stack and jump to the ELF entry ------------- */

unsigned long *setup_user_stack(char *sbase, unsigned long ssize,
                                int argc, char **argv) {
    char *p = sbase + ssize;
    char *argp[64];
    int i;
    if (argc > 64) argc = 64;
    for (i = 0; i < argc; i++) {
        unsigned long l = kstrlen(argv[i]) + 1;
        if (l > (unsigned long)(p - sbase)) return 0;
        p -= l;
        kmemcpy(p, argv[i], l);
        argp[i] = p;
    }
    p -= 16;
    char *randp = p;
    for (i = 0; i < 16; i++) randp[i] = (char)(0x37 + i);
    p = (char *)((unsigned long)p & ~15UL);

    int nwords = 1 + argc + 1 + 1 + 6;
    unsigned long sp = ((unsigned long)p - (unsigned long)nwords * 8) & ~15UL;
    unsigned long *w = (unsigned long *)sp;
    int idx = 0;
    w[idx++] = (unsigned long)argc;
    for (i = 0; i < argc; i++) w[idx++] = (unsigned long)argp[i];
    w[idx++] = 0;
    w[idx++] = 0;
    w[idx++] = 6;  w[idx++] = 4096;
    w[idx++] = 25; w[idx++] = (unsigned long)randp;
    w[idx++] = 0;  w[idx++] = 0;
    return w;
}

/* Enter a ring-3 program via iretq. */
extern unsigned long syscall_kstack;

int k_exec_user(void *entry, int argc, char **argv) {
    char *stk = (char *)USER_STACK_BASE;
    unsigned long *sp = setup_user_stack(stk, USER_STACK_SIZE, argc, argv);
    unsigned long frame[5];
    if (!sp) return -1;
    exec_exit_code = 0;
    unsigned long saved_kstack = syscall_kstack;

    unsigned long parent_cr3;
    __asm__ volatile("mov %%cr3, %0" : "=r"(parent_cr3));
    uint64_t new_cr3 = pt_clone_user(0);
    if (new_cr3) {
        __asm__ volatile("mov %0, %%cr3; mov %%cr3, %%rax" :: "r"(new_cr3) : "rax", "memory");
    }

    unsigned long child_stack_sz = SYS_KSTK_TOP - SYS_KSTK_BASE;
    void *child_stack = kmalloc(child_stack_sz);
    if (child_stack)
        syscall_kstack = (unsigned long)child_stack + child_stack_sz;
    else
        syscall_kstack = SYS_KSTK_TOP;
    wrmsr(MSR_FSBASE, 0);
    wrmsr(MSR_GSBASE, 0);

    frame[0] = (unsigned long)entry;
    frame[1] = (unsigned long)(GDT64_USER_CODE_SEL | 3);
    frame[2] = 0x202;
    frame[3] = (unsigned long)sp;
    frame[4] = (unsigned long)(GDT64_USER_DATA_SEL | 3);

    kjmpbuf saved_exec = exec_return;
    user_program_active = 1;
    if (ksetjmp(&exec_return) == 0) {
        __asm__ volatile(
            "mov %[udata], %%ax\n"
            "mov %%ax, %%ds\n"
            "mov %%ax, %%es\n"
            "mov %%ax, %%fs\n"
            "mov %%ax, %%gs\n"
            "mov %[frame], %%rsp\n"
            "xorl %%ebp, %%ebp\n"
            "xorl %%edi, %%edi\n"
            "xorl %%esi, %%esi\n"
            "xorl %%edx, %%edx\n"
            "iretq\n"
            :: [frame] "r"(frame), [udata] "i"(GDT64_USER_DATA_SEL | 3)
            : "rax", "memory");
        __builtin_unreachable();
    }
    user_program_active = 0;

    if (new_cr3) {
        pt_free_user(new_cr3);
        __asm__ volatile("mov %0, %%cr3" :: "r"(parent_cr3) : "memory");
    }
    (void)parent_cr3;

    __asm__ volatile(
        "mov %[kdata], %%ax\n"
        "mov %%ax, %%ds\n"
        "mov %%ax, %%es\n"
        "mov %%ax, %%fs\n"
        "mov %%ax, %%gs\n"
        "mov %%ax, %%ss\n"
        :: [kdata] "i"(GDT64_DATA_SEL)
        : "ax", "memory");
    wrmsr(MSR_FSBASE, 0);
    wrmsr(MSR_GSBASE, 0);
    exec_return = saved_exec;
    syscall_kstack = saved_kstack;
    if (child_stack) kfree(child_stack);
    if (vga_mode13h || graphics_program_ran) {
        vga_mode13h = 0;
        graphics_program_ran = 0;
        vga_fb_set_gfx_mode(0);
        vga_fb_draw_desktop();
    }
    kbd_reset_for_shell();
    return exec_exit_code;
}

int k_run_rel(prog_entry_t entry, int argc, char **argv) {
    exec_exit_code = 0;
    unsigned long saved_kstack = syscall_kstack;
    syscall_kstack = SYS_KSTK_TOP;

    unsigned long cr0, cr4;
    __asm__ volatile("mov %%cr0, %0" : "=r"(cr0));
    __asm__ volatile("mov %0, %%cr0" :: "r"(cr0 & ~0x8UL) : "memory");
    __asm__ volatile("mov %%cr4, %0" : "=r"(cr4));
    __asm__ volatile("mov %0, %%cr4" :: "r"(cr4 | 0x600UL) : "memory");

    kjmpbuf saved_exec = exec_return;

    if (ksetjmp(&exec_return) == 0) {
        int rc = entry(argc, argv);
        exec_return = saved_exec;
        syscall_kstack = saved_kstack;
        return rc;
    }

    exec_return = saved_exec;
    syscall_kstack = saved_kstack;
    if (vga_mode13h || graphics_program_ran) {
        vga_mode13h = 0;
        graphics_program_ran = 0;
        vga_fb_set_gfx_mode(0);
        vga_fb_draw_desktop();
    }
    kbd_reset_for_shell();
    return exec_exit_code;
}

void kexit(int code) {
    exec_exit_code = code;
    klongjmp(&exec_return, 1);
}
