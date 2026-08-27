/* stage2.S - MiniOS second-stage loader.
 *
 * Loaded at 0x9000 by the boot sector with DL holding the boot drive. Stage 2
 * enables the A20 gate, streams the kernel image off the disk and hands the
 * machine to the kernel in 64-bit long mode.
 *
 * The kernel is larger than the 640 KB of usable low memory, so it cannot be
 * read directly to its final address: BIOS disk services only reach real-mode
 * addresses. The image is therefore moved one 64 KB chunk at a time. Each
 * chunk is read into the staging buffer at 0x10000 with INT 13h extended
 * reads, then copied to its final home above 1 MB during a short excursion
 * into 32-bit protected mode. The loop keeps its state in memory rather than
 * registers so that no assumption is made about which registers the firmware
 * preserves across INT 13h.
 *
 * Once the whole image is in place the loader builds identity-mapped page
 * tables covering the first gigabyte with 2 MB pages, enables PAE and long
 * mode, installs the 64-bit GDT the kernel expects at 0x8000 and jumps to the
 * kernel entry point at 0x100000.
 *
 * KERNEL_SECTORS is supplied by the build from the size of the kernel image.
 * The trailing .org pads stage 2 to the sector count reserved for it on disk
 * and makes the assembler fail if the loader ever outgrows that reservation.
 */

#include "bootdefs.h"

#ifndef KERNEL_SECTORS
#error "KERNEL_SECTORS must be defined by the build"
#endif

#if KERNEL_SECTORS > 65535
#error "kernel image exceeds the 16-bit sector counter"
#endif

    .code16
    .global stage2_main

stage2_main:
    cli
    xorw %ax, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %ss
    movw $BOOT_STACK_TOP, %sp
    sti

    inb $A20_CONTROL_PORT, %al
    testb $A20_ENABLE_BIT, %al
    jnz a20_ready
    orb $A20_ENABLE_BIT, %al
    andb $A20_RESET_CLEAR_MASK, %al
    outb %al, $A20_CONTROL_PORT
a20_ready:

    sgdtl saved_gdtr
    movw $KERNEL_SECTORS, sectors_left
    movl $BOOT_KERNEL_LBA, next_lba
#ifdef KASLR
    call kaslr_pick
    movl %eax, dest_addr
    movl %eax, kaslr_dest
#else
    movl $BOOT_KERNEL_PHYS_ADDR, dest_addr
#endif
    movl dest_addr, %eax
    movl %eax, BOOT_KASLR_ADDR

load_chunk:
    movw sectors_left, %ax
    cmpw $BOOT_CHUNK_SECTORS, %ax
    jbe chunk_size_ready
    movw $BOOT_CHUNK_SECTORS, %ax
chunk_size_ready:
    movw %ax, chunk_sectors
    subw %ax, sectors_left

    movw %ax, %cx
    movw $BOOT_KERNEL_BUF_SEG, %bx

read_piece:
    movw $BOOT_BIOS_MAX_SECTORS, %ax
    cmpw %cx, %ax
    jbe piece_size_ready
    movw %cx, %ax
piece_size_ready:
    movw $BOOT_DAP_ADDR, %si
    movb $BOOT_DAP_SIZE, (%si)
    movb $0, 1(%si)
    movw %ax, BOOT_DAP_OFF_COUNT(%si)
    movw $0, BOOT_DAP_OFF_OFFSET(%si)
    movw %bx, BOOT_DAP_OFF_SEGMENT(%si)
    movl next_lba, %edx
    movl %edx, BOOT_DAP_OFF_LBA_LO(%si)
    movl $0, BOOT_DAP_OFF_LBA_HI(%si)
    pushw %ax
    movb $BIOS_DISK_READ_EXT, %ah
    movb BOOT_DRIVE_ADDR, %dl
    int $BIOS_DISK_INT
    jc read_failed
    popw %ax
    subw %ax, %cx
    movzwl %ax, %edx
    addl %edx, next_lba
    shlw $SECTOR_PARAGRAPH_SHIFT, %ax
    addw %ax, %bx
    testw %cx, %cx
    jnz read_piece

    cli
    lgdtl gdt32_ptr
    mov %cr0, %eax
    orl $CR0_PE, %eax
    mov %eax, %cr0
    ljmpl $GDT32_CODE32_SEL, $chunk_copy

    .code32
chunk_copy:
    movw $GDT32_DATA32_SEL, %ax
    movw %ax, %ds
    movw %ax, %es
    movl $BOOT_KERNEL_BUF_ADDR, %esi
    movl dest_addr, %edi
    movzwl chunk_sectors, %ecx
    shll $SECTOR_DWORD_SHIFT, %ecx
    rep movsl
    movl %edi, dest_addr
    ljmpl $GDT32_CODE16_SEL, $chunk_leave_pm

    .code16
chunk_leave_pm:
    movw $GDT32_DATA16_SEL, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %ss
    mov %cr0, %eax
    andl $CR0_PE_CLEAR_MASK, %eax
    mov %eax, %cr0
    ljmp $BOOT_SEG_NULL, $chunk_resume

chunk_resume:
    xorw %ax, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %ss
    movw $BOOT_STACK_TOP, %sp
    lgdtl saved_gdtr
    sti
    cmpw $0, sectors_left
    jne load_chunk

    call vbe_probe

    cli
    lgdtl gdt32_ptr
    mov %cr0, %eax
    orl $CR0_PE, %eax
    mov %eax, %cr0
    ljmpl $GDT32_CODE32_SEL, $enter_long_mode

    .code32
enter_long_mode:
    movw $GDT32_DATA32_SEL, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss
    movl $BOOT_PM_STACK_TOP, %esp

    movl $PT_PML4_ADDR, %edi
    xorl %eax, %eax
    movl $PT_ZERO_DWORDS, %ecx
    rep stosl

    movl $(PT_PDPT_ADDR | PT_FLAGS_PRESENT_RW), PT_PML4_ADDR
    movl $(PT_PD_ADDR | PT_FLAGS_PRESENT_RW), PT_PDPT_ADDR

#ifdef KASLR
    /* PD[0] and PD[1] become 4 KB page tables for the kernel image slide:
     * virtual 0x100000..0x400000 maps to the randomized physical base.
     * PT0 keeps [0, 1 MB) identity so the page tables, GDT, staging buffer
     * and stacks stay where the kernel expects them. */
    movl $(PT_USER0_ADDR | PT_FLAGS_PRESENT_RW), PT_PD_ADDR
    movl $(PT_USER1_ADDR | PT_FLAGS_PRESENT_RW), (PT_PD_ADDR + PT_PD_ENTRY_BYTES)

movl $PT_USER0_ADDR, %edi
    xorl %eax, %eax
    movl $256, %ecx
fill_pt0_low:
    orl $PT_FLAGS_PRESENT_RW, %eax
    movl %eax, (%edi)
    addl $PT_PD_ENTRY_BYTES, %edi
    addl $0x1000, %eax
    loop fill_pt0_low
    movl kaslr_dest, %eax
    movl $256, %ecx
fill_pt0_kernel:
    orl $PT_FLAGS_PRESENT_RW, %eax
    movl %eax, (%edi)
    addl $PT_PD_ENTRY_BYTES, %edi
    addl $0x1000, %eax
    loop fill_pt0_kernel

    /* PT1 continues the kernel image mapping at 4 KB granularity: virtual
     * [2 MB, 4 MB) maps to physical [base+1 MB, base+3 MB), covering the
     * tail of the kernel image, the embedded ramdisk and the whole kernel
     * .bss. The kernel therefore occupies ONE contiguous physical range
     * [base, base + KASLR_IMAGE_SPAN); a .bss that grows past 2 MB can no
     * longer spill onto the identity-mapped low-memory reserved zones
     * (user page tables, staging, stacks), which is what used to corrupt
     * the user page tables on every terminal line. */
    movl $PT_USER1_ADDR, %edi
    movl kaslr_dest, %eax
    addl $KASLR_IMG_OFF_1MB, %eax
    movl $256, %ecx
fill_pt1_kernel:
    orl $PT_FLAGS_PRESENT_RW, %eax
    movl %eax, (%edi)
    addl $PT_PD_ENTRY_BYTES, %edi
    addl $0x1000, %eax
    loop fill_pt1_kernel
    movl kaslr_dest, %eax
    addl $KASLR_IMG_OFF_2MB, %eax
    movl $256, %ecx
fill_pt1_bss:
    orl $PT_FLAGS_PRESENT_RW, %eax
    movl %eax, (%edi)
    addl $PT_PD_ENTRY_BYTES, %edi
    addl $0x1000, %eax
    loop fill_pt1_bss

    movl $PT_PD_ADDR, %edi
    addl $PT_FILL_START_INDEX * PT_PD_ENTRY_BYTES, %edi
    movl $(PT_FILL_START_ADDR | PT_FLAGS_PRESENT_RW_PS), %eax
    movl $PT_FILL_ENTRIES, %ecx
#else
    movl $PT_PD_ADDR, %edi
    movl $PT_FLAGS_PRESENT_RW_PS, %eax
    movl $PT_PD_ENTRIES, %ecx
#endif
fill_page_directory:
    movl %eax, (%edi)
    addl $PT_PD_ENTRY_BYTES, %edi
    addl $PT_PD_PAGE_BYTES, %eax
    loop fill_page_directory

    movl $PT_PML4_ADDR, %eax
    mov %eax, %cr3
    mov %cr4, %eax
    orl $CR4_PAE, %eax
    mov %eax, %cr4

    movl $MSR_EFER, %ecx
    rdmsr
    orl $EFER_LME, %eax
    wrmsr

    movl $gdt64_image, %esi
    movl $GDT64_ADDR, %edi
    movl $GDT64_BYTES, %ecx
    rep movsb
    lgdtl gdt64_ptr

    mov %cr0, %eax
    orl $CR0_PG, %eax
    mov %eax, %cr0
    ljmpl $GDT64_CODE_SEL, $BOOT_KERNEL_PHYS_ADDR

    .code16
read_failed:
    movw $msg_read, %si
    call puts

halt:
    cli
    hlt
    jmp halt

puts:
    pusha
    movw $BIOS_VIDEO_TTY_ATTR, %bx
    movb $BIOS_VIDEO_TTY_WRITE, %ah
puts_next:
    lodsb
    testb %al, %al
    jz puts_done
    int $BIOS_VIDEO_INT
    jmp puts_next
puts_done:
    popa
    ret

msg_read:
    .asciz "stage2: read error"

/* Probe VESA BIOS Extensions for a high-resolution 8-bit-palette linear
 * framebuffer and record it for the kernel in the fixed VBE_INFO_ADDR struct.
 * Tries 800x600x8, then 640x480x8, then falls back to VGA Mode 13h. Runs in
 * real mode (the kernel image is already fully loaded, so this scratch is
 * safe) and must complete before the transition to long mode kills the BIOS
 * video services. The 8-bit modes keep the 256-entry VGA DAC path the kernel
 * desktop and DOOM rely on. */
vbe_probe:
    movw $VBE_MODE_800x600x8, %bx
    call vbe_try_mode
    jnc vbe_ok
    movw $VBE_MODE_640x480x8, %bx
    call vbe_try_mode
    jnc vbe_ok
    /* Fallback: VGA Mode 13h (320x200x8, linear framebuffer at 0xA0000). */
    movw $BIOS_VIDEO_SET_MODE, %ax
    int $BIOS_VIDEO_INT
    movl $0x000A0000, %eax
    movl %eax, VBE_INFO_ADDR + VBE_INFO_FBBASE_OFF
    movw $320, VBE_INFO_ADDR + VBE_INFO_WIDTH_OFF
    movw $200, VBE_INFO_ADDR + VBE_INFO_HEIGHT_OFF
    movw $320, VBE_INFO_ADDR + VBE_INFO_PITCH_OFF
    movb $1, VBE_INFO_ADDR + VBE_INFO_VALID_OFF
    ret

/* Try one VBE mode held in %bx. On success the mode is set with the linear
 * framebuffer bit and carry is cleared; on any failure carry is set so the
 * caller can try the next candidate. */
vbe_try_mode:
    pushw %bx
    pushw %di
    pushw %es
    /* Get mode info: AX=4F01, CX=mode, ES:DI -> 0x7000. */
    movw $0, %ax
    movw %ax, %es
    movw $VBE_MODE_INFO_ADDR, %di
    movw $BIOS_VBE_GET_MODE_INFO, %ax
    movw %bx, %cx
    int $BIOS_VIDEO_INT
    cmpw $0x4F, %ax
    jne vbe_try_fail
    /* Attributes word at offset 0 must claim supported and linear FB. */
    movw $0, %ax
    movw %ax, %es
    movw $VBE_MODE_INFO_ADDR, %si
    movw (%si), %dx
    andw $VBE_ATTR_SUPPORTED, %dx
    jz vbe_try_fail
    movw (%si), %dx
    andw $VBE_ATTR_LFB, %dx
    jz vbe_try_fail
    /* Copy width, height, pitch and physical base into the info struct. */
    movw VBE_INFO_XRES_OFF(%si), %dx
    movw %dx, VBE_INFO_ADDR + VBE_INFO_WIDTH_OFF
    movw VBE_INFO_YRES_OFF(%si), %dx
    movw %dx, VBE_INFO_ADDR + VBE_INFO_HEIGHT_OFF
    movw VBE_INFO_BYTES_SCAN_OFF(%si), %dx
    movw %dx, VBE_INFO_ADDR + VBE_INFO_PITCH_OFF
    movl VBE_INFO_PHYSBASE_OFF(%si), %edx
    movl %edx, VBE_INFO_ADDR + VBE_INFO_FBBASE_OFF
    popw %es
    popw %di
    popw %bx
    /* Set the mode with the linear-framebuffer bit: AX=4F02, BX=mode|LFB. */
    orw $VBE_MODE_LFB, %bx
    movw $BIOS_VBE_SET_MODE, %ax
    int $BIOS_VIDEO_INT
    cmpw $0x4F, %ax
    jne vbe_set_fail
    movb $1, VBE_INFO_ADDR + VBE_INFO_VALID_OFF
    clc
    ret
vbe_set_fail:
    stc
    ret
vbe_try_fail:
    popw %es
    popw %di
    popw %bx
    stc
    ret
vbe_ok:
    ret

#ifdef KASLR
/* Pick the kernel's physical load base: a 2 MB-aligned address in the
 * 64-position window above the kernel heap, seeded from the TSC and the RTC
 * so consecutive boots land at different locations. Returns the base in
 * eax. The virtual base stays at the link-time 0x100000, which PT0/PT1 map
 * to the returned physical base. */
kaslr_pick:
    pushl %ecx
    rdtsc
    xorl %edx, %eax
    pushl %eax
    movb $(CMOS_NMI_DISABLE | CMOS_REG_SECONDS), %al
    outb %al, $CMOS_INDEX_PORT
    inb  $CMOS_DATA_PORT, %al
    movzbl %al, %ecx
    shll $24, %ecx
    popl %eax
    xorl %ecx, %eax
    pushl %eax
    movb $(CMOS_NMI_DISABLE | CMOS_REG_MINUTES), %al
    outb %al, $CMOS_INDEX_PORT
    inb  $CMOS_DATA_PORT, %al
    movzbl %al, %ecx
    shll $16, %ecx
    popl %eax
    xorl %ecx, %eax
    pushl %eax
    movb $(CMOS_NMI_DISABLE | CMOS_REG_HOURS), %al
    outb %al, $CMOS_INDEX_PORT
    inb  $CMOS_DATA_PORT, %al
    movzbl %al, %ecx
    shll $8, %ecx
    popl %eax
    xorl %ecx, %eax
    shrl $KASLR_ALIGN_SHIFT, %eax
    andl $KASLR_MAX_UNITS - 1, %eax
    shll $KASLR_ALIGN_SHIFT, %eax
    addl $KASLR_MIN_ADDR, %eax
    popl %ecx
    ret
#endif

    .p2align 3
gdt32_start:
    .quad GDT32_DESC_NULL
    .quad GDT32_DESC_CODE32
    .quad GDT32_DESC_DATA32
    .quad GDT32_DESC_CODE16
    .quad GDT32_DESC_DATA16
gdt32_end:
gdt32_ptr:
    .word gdt32_end - gdt32_start - 1
    .long gdt32_start

    .p2align 3
gdt64_image:
    .quad GDT64_DESC_NULL
    .quad GDT64_DESC_CODE
    .quad GDT64_DESC_DATA
    .quad GDT64_DESC_UDATA
    .quad GDT64_DESC_UCODE
gdt64_ptr:
    .word GDT64_BYTES - 1
    .long GDT64_ADDR

saved_gdtr:
    .word 0
    .long 0
sectors_left:
    .word 0
chunk_sectors:
    .word 0
next_lba:
    .long 0
dest_addr:
    .long 0
kaslr_dest:
    .long 0

    .org BOOT_STAGE2_SECTORS * SECTOR_BYTES
