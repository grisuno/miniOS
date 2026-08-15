/* stage1.S - MiniOS boot sector.
 *
 * The BIOS loads this sector at 0x7C00 and enters in 16-bit real mode with
 * DL holding the boot drive. Stage 1 has one job: bring stage 2 in from the
 * disk and transfer control to it. All kernel loading, A20 handling and mode
 * switching live in stage 2, which has no 512-byte size ceiling.
 *
 * Reads use INT 13h extended (LBA) addressing, so the image must be attached
 * as a hard disk. Extension support is verified before the first read and a
 * diagnostic is printed if the firmware cannot serve the request.
 *
 * The trailing .org directive both pads the image to a full sector and makes
 * the assembler fail if the code ever outgrows the boot sector.
 */

#include "bootdefs.h"

    .code16
    .global main

main:
    cli
    ljmp $BOOT_SEG_NULL, $normalize

normalize:
    xorw %ax, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %ss
    movw $BOOT_STACK_TOP, %sp
    sti
    movb %dl, BOOT_DRIVE_ADDR

    movb $BIOS_DISK_EXT_CHECK, %ah
    movw $BIOS_DISK_EXT_REQ_MAGIC, %bx
    int $BIOS_DISK_INT
    jc no_extensions
    cmpw $BIOS_DISK_EXT_ACK_MAGIC, %bx
    jne no_extensions
    testb $BIOS_DISK_EXT_PACKET_BIT, %cl
    jz no_extensions

    movw $BOOT_DAP_ADDR, %si
    movb $BOOT_DAP_SIZE, (%si)
    movb $0, 1(%si)
    movw $BOOT_STAGE2_SECTORS, BOOT_DAP_OFF_COUNT(%si)
    movw $0, BOOT_DAP_OFF_OFFSET(%si)
    movw $BOOT_STAGE2_SEG, BOOT_DAP_OFF_SEGMENT(%si)
    movl $BOOT_STAGE2_LBA, BOOT_DAP_OFF_LBA_LO(%si)
    movl $0, BOOT_DAP_OFF_LBA_HI(%si)
    movb $BIOS_DISK_READ_EXT, %ah
    movb BOOT_DRIVE_ADDR, %dl
    int $BIOS_DISK_INT
    jc read_failed

    movb BOOT_DRIVE_ADDR, %dl
    ljmp $BOOT_SEG_NULL, $BOOT_STAGE2_ADDR

no_extensions:
    movw $msg_no_lba, %si
    jmp fail

read_failed:
    movw $msg_read, %si

fail:
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

msg_no_lba:
    .asciz "stage1: no LBA support"
msg_read:
    .asciz "stage1: read error"

    .org SECTOR_BYTES - BOOT_SIGNATURE_BYTES
    .word BOOT_SIGNATURE
