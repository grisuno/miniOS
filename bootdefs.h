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
 *   0x00000 - 0x005FF  real-mode IVT and BIOS data area
 *   0x01000 - 0x05FFF  long-mode page tables (PML4, PDPT, PD, KASLR PT0/PT1)
 *   0x030000 - 0x031000  user-window page tables (4 KB leaves, NX per page)
 *   0x07C00 - 0x07DFF  stage 1 (boot sector)
 *   0x07E00 - 0x07E14  disk address packet, boot drive and KASLR base scratch
 *   0x08000 - 0x08017  long-mode GDT handed to the kernel
 *   0x09000 - 0x0AFFF  stage 2
 *   0x10000 - 0x8FFFF  kernel staging buffer (one chunk at a time)
 *   0x90000            protected/long mode stack top
 *   0x100000           kernel link-time virtual base (physical base is
 *                      randomized by KASLR into [0x0600000, 0x0E000000)
 *                      when enabled)
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
#define BOOT_KASLR_ADDR           0x7E14

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
#define BIOS_VIDEO_SET_MODE       0x0013

#define A20_CONTROL_PORT          0x92
#define A20_ENABLE_BIT            0x02
#define A20_RESET_CLEAR_MASK      0xFE

#define CR0_PE                    0x00000001
#define CR0_PE_CLEAR_MASK         0xFFFFFFFE
#define CR0_PG                    0x80000000
#define CR4_PAE                   0x00000020

#define MSR_EFER                  0xC0000080
#define EFER_LME                  0x00000100
#define EFER_NXE                  0x00000800

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
#define PT_USER0_ADDR             0x4000
#define PT_USER1_ADDR             0x5000
#define PT_ZERO_DWORDS            4096
#define PT_FLAGS_PRESENT_RW       0x003
#define PT_FLAGS_PRESENT_RW_PS    0x083
#define PT_FLAGS_PS               0x080
#define PT_FLAGS_USER             0x004
#define PT_PD_ENTRIES             512
#define PT_PD_ENTRY_BYTES         8
#define PT_PD_PAGE_BYTES          0x200000
#define PT_PD_INDEX_SHIFT         21
#define PT_FILL_START_INDEX       2
#define PT_FILL_START_ADDR        0x400000
#define PT_FILL_ENTRIES           (PT_PD_ENTRIES - PT_FILL_START_INDEX)

/* Dedicated zone for the kernel-installed 4 KB user-window page tables.
 * It must never share memory with the heap: the ramdisk data area is
 * heap-backed and its size is discovered at boot, so page tables there
 * could be overwritten by a later reservation. This zone sits between the
 * kernel image and the user window and is identity-mapped (2 MB PD leaf in
 * the plain build, PT1 in the KASLR build) so the PDEs can carry the same
 * addresses the kernel writes through. */
#define PT_USER_TABLES_ADDR       0x00300000
#define PT_USER_TABLES_BYTES      0x00010000

/* KASLR: the kernel image is loaded at a random 2 MB-aligned physical base
 * chosen from a 64-position window above the kernel heap, so the kernel's
 * physical location varies on every boot. The virtual base stays at the
 * link-time address (0x100000); the loader maps it to the chosen physical
 * base. */
#define KASLR_MIN_ADDR            0x06000000
#define KASLR_ALIGN_SHIFT         21
#define KASLR_MAX_UNITS           64

#define CMOS_INDEX_PORT           0x70
#define CMOS_DATA_PORT            0x71
#define CMOS_NMI_DISABLE          0x80
#define CMOS_REG_SECONDS          0x00
#define CMOS_REG_MINUTES          0x02
#define CMOS_REG_HOURS            0x04

#endif
