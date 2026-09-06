/* ap_entry.S - SMP application-processor bootstrap stub.
 *
 * Copied to AP_STUB_ADDR (0x6000, below 1 MB so a real-mode SIPI can reach it)
 * and executed by every AP after the BSP sends it INIT + SIPI.  It reuses the
 * page tables (PT_PML4_ADDR) and the 64-bit GDT (GDT64_ADDR) that stage 2
 * already built for the BSP, so each AP only has to enable PAE/long mode and
 * jump to a C entry point.  The 64-bit entry then calls smp_ap_entry(), whose
 * absolute address the BSP patches into the 8-byte slot at ap_entry_patch
 * before it wakes the APs.
 *
 * This is a flat binary, so nothing here can reference a kernel symbol at
 * assembly time; every external address is patched at runtime. */

#include "bootdefs.h"

#define AP_GDT32_SEL_CODE  0x08
#define AP_GDT32_SEL_DATA  0x10

    .code16
    .globl ap_stub_start
ap_stub_start:
    cli
    /* Progress marker 0x41 -> scratch 0x70000 (dead staging buffer). */
    movw $0x7000, %ax
    movw %ax, %es
    movb $0x41, %es:0
    xorw %ax, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %ss
    movw $(AP_STUB_ADDR + 0x800), %sp
    lgdtl ap_gdt32_ptr
    movl %cr0, %eax
    orl  $CR0_PE, %eax
    movl %eax, %cr0
    ljmpl $AP_GDT32_SEL_CODE, $ap_pm

    .code32
ap_pm:
    movw $AP_GDT32_SEL_DATA, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %ss
    movl $0x78000, %esp
    /* PAE + long mode, reusing the BSP's page tables. */
    movl %cr4, %eax
    orl  $CR4_PAE, %eax
    movl %eax, %cr4
    movl $PT_PML4_ADDR, %eax
    movl %eax, %cr3
    movl $MSR_EFER, %ecx
    rdmsr
    orl  $EFER_LME, %eax
    wrmsr
    lgdtl ap_gdt64_ptr
    movl %cr0, %eax
    orl  $CR0_PG, %eax
    movl %eax, %cr0
    ljmpl $AP_GDT32_SEL_CODE, $ap_lm

    .code64
ap_lm:
    /* Progress marker 0x42 at 0x70001. */
    movq $0x70001, %rbx
    movb $0x42, (%rbx)
    /* Temp stack in identity-mapped low memory, below the LAPIC PD.
     * This is only needed until smp_ap_entry switches to its own context.
     * Must be above 0x70000 (LAPIC PD) and below 0x80000 (syscall stack). */
    movq $0x78000, %rsp
    xorw %ax, %ax
    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %ss
    /* Load smp_ap_entry()'s address from the BSP-patched slot and go. */
    mov ap_patch_slot(%rip), %rax
    jmp *%rax

    .globl ap_patch_slot
ap_patch_slot:
    .quad 0

    .p2align 2
ap_gdt32:
    .quad 0x0000000000000000
    .quad 0x00CF9A000000FFFF     /* code32 base 0 limit 4G */
    .quad 0x00CF92000000FFFF     /* data32 base 0 limit 4G */
ap_gdt32_ptr:
    .word ap_gdt32_end - ap_gdt32 - 1
    .long ap_gdt32
ap_gdt32_end:

ap_gdt64_ptr:
    .word GDT64_SMP_BYTES - 1
    .quad GDT64_ADDR

    .globl ap_stub_end
ap_stub_end:
