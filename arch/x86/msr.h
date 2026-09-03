#ifndef ARCH_X86_MSR_H
#define ARCH_X86_MSR_H

/* Model-Specific Register access for x86-64.
 * Shared by kernel.c (syscall_init, arch_prctl, k_exec_user),
 * paging.c (mm_setup_protections), and syscalls.c (arch_prctl handler). */

static inline void wrmsr(unsigned msr, unsigned long val) {
    unsigned lo = (unsigned)val, hi = (unsigned)(val >> 32);
    __asm__ volatile("wrmsr" :: "c"(msr), "a"(lo), "d"(hi));
}

static inline unsigned long rdmsr(unsigned msr) {
    unsigned lo, hi;
    __asm__ volatile("rdmsr" : "=a"(lo), "=d"(hi) : "c"(msr));
    return ((unsigned long)hi << 32) | lo;
}

#define MSR_STAR   0xC0000081
#define MSR_LSTAR  0xC0000082
#define MSR_SFMASK 0xC0000084
#define MSR_FSBASE 0xC0000100
#define MSR_GSBASE 0xC0000101

#endif
