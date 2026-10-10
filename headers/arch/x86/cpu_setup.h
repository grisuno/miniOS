/** cpu_setup.h - per-CPU control-register setup shared by the BSP (kmain)
 * and every AP (smp_ap_entry).
 *
 * CR0 and CR4 are per-CPU: a bit the BSP sets never reaches an AP, which
 * leaves INIT with caching disabled (CR0.CD|NW) and SSE off (CR4.OSFXSR
 * clear). Each CPU that may run ring-3 code calls both helpers before it
 * schedules anything. Bit names live in bootdefs.h.
 */
#ifndef ARCH_X86_CPU_SETUP_H
#define ARCH_X86_CPU_SETUP_H

#include "bootdefs.h"

/** Enable x87/SSE for ring 3: CR0.EM clear, CR0.MP set, CR4.OSFXSR and
 * CR4.OSXMMEXCPT set, so XMM instructions and FXSAVE/FXRSTOR execute and
 * unmasked SIMD exceptions raise #XM instead of #UD. */
static inline void cpu_enable_sse(void) {
    unsigned long cr0, cr4;
    __asm__ volatile("mov %%cr0, %0" : "=r"(cr0));
    cr0 &= ~(unsigned long)CR0_EM;
    cr0 |= (unsigned long)CR0_MP;
    __asm__ volatile("mov %0, %%cr0" :: "r"(cr0) : "memory");
    __asm__ volatile("mov %%cr4, %0" : "=r"(cr4));
    cr4 |= (unsigned long)(CR4_OSFXSR | CR4_OSXMMEXCPT);
    __asm__ volatile("mov %0, %%cr4" :: "r"(cr4) : "memory");
}

/** Turn caching on (CR0.CD and CR0.NW clear), then write back and
 * invalidate so no line filled under the reset policy survives. */
static inline void cpu_enable_caches(void) {
    unsigned long cr0;
    __asm__ volatile("mov %%cr0, %0" : "=r"(cr0));
    if (!(cr0 & (unsigned long)(CR0_CD | CR0_NW))) return;
    cr0 &= ~(unsigned long)(CR0_CD | CR0_NW);
    __asm__ volatile("mov %0, %%cr0" :: "r"(cr0) : "memory");
    __asm__ volatile("wbinvd" ::: "memory");
}

#endif
