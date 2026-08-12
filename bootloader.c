__asm__(".code16gcc\n");

__asm__("jmpl $0x0000, $main\n");

__asm__(
    ".global gdt_start\n"
    "gdt_start:\n"
    "  .quad 0x0000000000000000\n"
    "  .quad 0x00CF9A000000FFFF\n"
    "  .quad 0x00CF92000000FFFF\n"
    "  .quad 0x00209A0000000000\n"
    "  .quad 0x0000920000000000\n"
    "gdt_end:\n"
    ".global gdt32_ptr\n"
    "gdt32_ptr:\n"
    "  .word gdt_end - gdt_start - 1\n"
    "  .long gdt_start\n"
    ".global gdt64_ptr\n"
    "gdt64_ptr:\n"
    "  .word gdt_end - gdt_start - 1\n"
    "  .long gdt_start\n"
);

/* Disk Address Packet for LBA extended read */
__asm__(
    "boot_drive:\n"
    "  .byte 0x00\n"
    "dap:\n"
    "  .byte 0x10\n"
    "  .byte 0x00\n"
    "  .word 512\n"
    "  .word 0x0000\n"
    "  .word 0x1000\n"
    "  .quad 1\n"
);

void main(void) {
    /* Save boot drive (BIOS passes it in DL) */
    __asm__ volatile("mov %%dl, boot_drive\n" : : : "dx");

    __asm__ volatile("cli");

    __asm__ volatile(
        "xor %%ax, %%ax\n"
        "mov %%ax, %%ds\n"
        "mov %%ax, %%es\n"
        "mov %%ax, %%fs\n"
        "mov %%ax, %%gs\n"
        "mov %%ax, %%ss\n"
        "mov $0x7C00, %%sp\n"
        ::: "ax"
    );

    /* Reset disk */
    __asm__ volatile("xor %%ah, %%ah\n"
                     "mov boot_drive, %%dl\n"
                     "int $0x13" ::: "ax", "dx");

    /* Load kernel: CHS read, 128 sectors from CHS 0,0,2 -> phys 0x10000 */
    __asm__ volatile(
        "mov $0x02, %%ah\n"
        "mov $128, %%al\n"
        "mov $0x00, %%ch\n"
        "mov $0x02, %%cl\n"
        "mov $0x00, %%dh\n"
        "mov boot_drive, %%dl\n"
        "mov $0x1000, %%bx\n"
        "mov %%bx, %%es\n"
        "xor %%bx, %%bx\n"
        "int $0x13\n"
        "jnc 1f\n"
        /* On error: output 'X' to serial and halt */
        "mov $0x58, %%al\n"
        "mov $0x3F8, %%dx\n"
        "outb %%al, %%dx\n"
        "2: hlt\n"
        "jmp 2b\n"
        "1:\n"
        ::: "ax", "bx", "cx", "dx"
    );

    /* Switch to 32-bit protected mode */
    __asm__ volatile(
        "lgdt gdt32_ptr\n"
        "mov %%cr0, %%eax\n"
        "or $1, %%al\n"
        "mov %%eax, %%cr0\n"
        "ljmp $0x08, $pmode_%=\n"
        ".code32\n"
        "pmode_%=:\n"
        "mov $0x10, %%ax\n"
        "mov %%ax, %%ds\n"
        "mov %%ax, %%es\n"
        "mov %%ax, %%fs\n"
        "mov %%ax, %%gs\n"
        "mov %%ax, %%ss\n"
        "mov $0x90000, %%esp\n"

        /* Clear page tables at 0x1000 */
        "mov $0x1000, %%edi\n"
        "xor %%eax, %%eax\n"
        "mov $4096, %%ecx\n"
        "rep stosl\n"

        /* Page tables: PML4[0]->0x2000, PDPT[0]->0x3000, PD[0]->2MB at 0 */
        "movl $0x2003, 0x1000\n"
        "movl $0x3003, 0x2000\n"
        "movl $0x0083, 0x3000\n"

        "mov $0x1000, %%eax\n"
        "mov %%eax, %%cr3\n"

        /* Enable PAE */
        "mov %%cr4, %%eax\n"
        "or $0x20, %%eax\n"
        "mov %%eax, %%cr4\n"

        /* Enable Long Mode */
        "mov $0xC0000080, %%ecx\n"
        "rdmsr\n"
        "or $0x100, %%eax\n"
        "wrmsr\n"

        /* Build minimal 64-bit GDT at 0x8000 (null + code64 + data64) */
        "xor %%eax, %%eax\n"
        "mov $0x8000, %%edi\n"
        "stosl\n"
        "stosl\n"
        "stosl\n"
        "movl $0x00209A00, %%eax\n"
        "stosl\n"
        "xor %%eax, %%eax\n"
        "stosl\n"
        "movl $0x00009200, %%eax\n"
        "stosl\n"

        /* GDT pointer at 0x7000: limit=23 (3*8-1), base=0x8000 */
        "movl $0x80000017, 0x7000\n"
        "movw $0x0000, 0x7004\n"

        /* Enable paging */
        "mov %%cr0, %%eax\n"
        "or $0x80000000, %%eax\n"
        "mov %%eax, %%cr0\n"
        "jmp 1f\n"
        "1:\n"

        /* Load 64-bit GDT */
        "lgdt 0x7000\n"

        /* Jump to 64-bit kernel */
        "ljmp $0x08, $0x10000\n"
        ::: "eax", "ecx", "edi", "memory"
    );

    while (1) __asm__ volatile("hlt");
}
