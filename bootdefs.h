/* bootdefs.h - centralized configuration for the MiniOS two-stage boot path.
 *
 * Shared by stage1.S (the 512-byte boot sector) and stage2.S (the loader).
 * Every address, BIOS service number, descriptor value and control-register
 * bit used by the boot path is named here so that neither stage carries a
 * magic number. The file is preprocessor-only so it can be included from
 * assembly translation units.
 *
 * Physical memory map established by the boot path:
 *
 *   0x00000 - 0x004FF  real-mode IVT and BIOS data area
 *   0x01000 - 0x04FFF  long-mode page tables (PML4, PDPT, PD)
 *   0x07C00 - 0x07DFF  stage 1 (boot sector)
 *   0x07E00 - 0x07E10  disk address packet and boot drive scratch
 *   0x08000 - 0x08017  long-mode GDT handed to the kernel
 *   0x09000 - 0x0AFFF  stage 2
 *   0x10000 - 0x8FFFF  kernel staging buffer (one chunk at a time)
 *   0x90000            protected/long mode stack top
 *   0x100000           kernel image
 *
 * Disk layout (LBA, 512-byte sectors):
 *
 *   0                  stage 1
 *   1 .. 8             stage 2
 *   9 ..               kernel image
 */

#ifndef BOOTDEFS_H
#define BOOTDEFS_H

#define SECTOR_BYTES              512
#define SECTOR_PARAGRAPH_SHIFT    5
#define SECTOR_DWORD_SHIFT        7

#define BOOT_SIGNATURE            0xAA55
#define BOOT_SIGNATURE_BYTES      2

#define BOOT_SEG_NULL             0x0000
#define BOOT_STACK_TOP            0x7C00

#define BOOT_DAP_ADDR             0x7E00
#define BOOT_DAP_SIZE             0x10
#define BOOT_DAP_OFF_COUNT        2
#define BOOT_DAP_OFF_OFFSET       4
#define BOOT_DAP_OFF_SEGMENT      6
#define BOOT_DAP_OFF_LBA_LO       8
#define BOOT_DAP_OFF_LBA_HI       12
#define BOOT_DRIVE_ADDR           0x7E10

#define BOOT_STAGE2_LBA           1
#define BOOT_STAGE2_SECTORS       8
#define BOOT_STAGE2_ADDR          0x9000
#define BOOT_STAGE2_SEG           0x0900

#define BOOT_KERNEL_LBA           (BOOT_STAGE2_LBA + BOOT_STAGE2_SECTORS)
#define BOOT_KERNEL_BUF_ADDR      0x10000
#define BOOT_KERNEL_BUF_SEG       0x1000
#define BOOT_KERNEL_PHYS_ADDR     0x100000

#define BOOT_CHUNK_SECTORS        128
#define BOOT_BIOS_MAX_SECTORS     64

#define BOOT_PM_STACK_TOP         0x90000

#define BIOS_DISK_INT             0x13
#define BIOS_DISK_EXT_CHECK       0x41
#define BIOS_DISK_EXT_REQ_MAGIC   0x55AA
#define BIOS_DISK_EXT_ACK_MAGIC   0xAA55
#define BIOS_DISK_EXT_PACKET_BIT  0x01
#define BIOS_DISK_READ_EXT        0x42

#define BIOS_VIDEO_INT            0x10
#define BIOS_VIDEO_TTY_WRITE      0x0E
#define BIOS_VIDEO_TTY_ATTR       0x0007

#define A20_CONTROL_PORT          0x92
#define A20_ENABLE_BIT            0x02
#define A20_RESET_CLEAR_MASK      0xFE

#define CR0_PE                    0x00000001
#define CR0_PE_CLEAR_MASK         0xFFFFFFFE
#define CR0_PG                    0x80000000
#define CR4_PAE                   0x00000020

#define MSR_EFER                  0xC0000080
#define EFER_LME                  0x00000100

#define GDT32_CODE32_SEL          0x08
#define GDT32_DATA32_SEL          0x10
#define GDT32_CODE16_SEL          0x18
#define GDT32_DATA16_SEL          0x20

#define GDT32_DESC_NULL           0x0000000000000000
#define GDT32_DESC_CODE32         0x00CF9A000000FFFF
#define GDT32_DESC_DATA32         0x00CF92000000FFFF
#define GDT32_DESC_CODE16         0x00009A000000FFFF
#define GDT32_DESC_DATA16         0x000092000000FFFF

#define GDT64_ADDR                0x8000
#define GDT64_BYTES               40
#define GDT64_CODE_SEL            0x08
#define GDT64_DATA_SEL            0x10
#define GDT64_USER_DATA_SEL       0x18
#define GDT64_USER_CODE_SEL       0x20
#define GDT64_DESC_NULL           0x0000000000000000
#define GDT64_DESC_CODE           0x00209A0000000000
#define GDT64_DESC_DATA           0x0000920000000000
#define GDT64_DESC_UDATA          0x0000F20000000000
#define GDT64_DESC_UCODE          0x0020FA0000000000

#define PT_PML4_ADDR              0x1000
#define PT_PDPT_ADDR              0x2000
#define PT_PD_ADDR                0x3000
#define PT_ZERO_DWORDS            4096
#define PT_FLAGS_PRESENT_RW       0x003
#define PT_FLAGS_PRESENT_RW_PS    0x083
#define PT_FLAGS_USER             0x004
#define PT_PD_ENTRIES             512
#define PT_PD_ENTRY_BYTES         8
#define PT_PD_PAGE_BYTES          0x200000
#define PT_PD_INDEX_SHIFT         21

#endif
