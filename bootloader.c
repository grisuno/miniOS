__asm__(".code16gcc\n");
__asm__("jmpl $0x0000, $main\n");

__asm__(
    ".global gdt_start\n"
    "gdt_start:\n"
    "  .quad 0\n"
    "  .quad 0x00CF9A000000FFFF\n"
    "  .quad 0x00CF92000000FFFF\n"
    "gdt_end:\n"
    ".global gdt32_ptr\n"
    "gdt32_ptr:\n"
    "  .word gdt_end - gdt_start - 1\n"
    "  .long gdt_start\n"
);
__asm__("boot_drive: .byte 0\n");

/* Number of 512-byte sectors of kernel to load from LBA 1 to phys 0x10000. */
#define KSECTORS 508

void main(void) {
    __asm__ volatile("mov %%dl, boot_drive\n" : : : "dx");
    __asm__ volatile("cli");
    __asm__ volatile("xor %%ax,%%ax;mov %%ax,%%ds;mov %%ax,%%es;mov %%ax,%%ss;mov $0x7C00,%%esp" ::: "ax");
    __asm__ volatile("xor %%ah,%%ah;mov boot_drive,%%dl;int $0x13" ::: "ax","dx");

    /*
     * Load the kernel one track at a time (1.44M floppy: 18 sectors/track,
     * 2 heads).  Each BIOS int 13h call is capped so it spans neither a track
     * boundary (SeaBIOS stops partway) nor a 64 KB physical boundary (the
     * floppy DMA controller cannot cross one).  CHS is advanced with counters
     * so no 32-bit division (which would pull in libgcc) is emitted.
     */
    {
        unsigned sector = 2, head = 0, cyl = 0;   /* LBA 1 = C0 H0 S2 */
        unsigned short seg = 0x1000;              /* -> physical 0x10000 */
        int remaining = KSECTORS;
        while (remaining > 0) {
            unsigned count = 19 - sector;                     /* rest of this track */
            unsigned tb    = (0x1000U - (seg & 0x0FFF)) >> 5; /* sectors to 64K edge */
            if (count > tb)             count = tb;
            if ((int)count > remaining) count = remaining;
            unsigned char al = (unsigned char)count, ch = (unsigned char)cyl;
            unsigned char cl = (unsigned char)sector, dh = (unsigned char)head;
            __asm__ volatile(
                "movw %[es], %%es\n\t"
                "xorw %%bx, %%bx\n\t"
                "movb $0x02, %%ah\n\t"
                "movb %[al], %%al\n\t"
                "movb %[ch], %%ch\n\t"
                "movb %[cl], %%cl\n\t"
                "movb %[dh], %%dh\n\t"
                "movb boot_drive, %%dl\n\t"
                "int $0x13\n\t"
                :
                : [es]"m"(seg), [al]"m"(al), [ch]"m"(ch), [cl]"m"(cl), [dh]"m"(dh)
                : "ax", "bx", "cx", "dx", "memory");

            seg       += (unsigned short)(count << 5);        /* count * 512 bytes */
            remaining -= (int)count;
            sector    += count;
            if (sector > 18) { sector = 1; if (++head > 1) { head = 0; cyl++; } }
        }
    }

    /* 16->32->64 transition */
    __asm__ volatile(
        "lgdt gdt32_ptr;mov %%cr0,%%eax;or $1,%%al;mov %%eax,%%cr0;ljmp $0x08,$pm_%=\n"
        ".code32\n"
        "pm_%=:\n"
        "mov $0x10,%%ax;mov %%ax,%%ds;mov %%ax,%%es;mov %%ax,%%ss;mov $0x90000,%%esp\n"
        "mov $0x1000,%%edi;xor %%eax,%%eax;mov $4096,%%ecx;rep stosl\n"
        "movl $0x2003,0x1000;movl $0x3003,0x2000\n"
        "mov $0x3000,%%edi;mov $0x83,%%eax;mov $512,%%ecx\n"
        "2:movl %%eax,(%%edi);movl $0,4(%%edi);add $8,%%edi;add $0x200000,%%eax;loop 2b\n"
        "mov $0x1000,%%eax;mov %%eax,%%cr3\n"
        "mov %%cr4,%%eax;or $0x20,%%eax;mov %%eax,%%cr4\n"
        "mov $0xC0000080,%%ecx;rdmsr;or $0x100,%%eax;wrmsr\n"
        "xor %%eax,%%eax;mov $0x8000,%%edi;stosl;stosl;stosl;movl $0x00209A00,%%eax;stosl\n"
        "xor %%eax,%%eax;stosl;movl $0x00009200,%%eax;stosl\n"
        "movl $0x80000017,0x7000;movw $0,0x7004\n"
        "mov %%cr0,%%eax;or $0x80000000,%%eax;mov %%eax,%%cr0;jmp 1f;1:;lgdt 0x7000;ljmp $0x08,$0x10000\n"
        ::: "eax","ecx","edi","memory");
    while(1)__asm__("hlt");
}
