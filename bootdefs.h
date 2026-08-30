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
 *   0x10000 - 0x1FFFF  user-window page tables (4 KB leaves, NX per page).
 *                      This zone deliberately sits BELOW the kernel image
 *                      base (0x100000) so no kernel code, data or .bss can
 *                      ever land on it. It reuses the tail of the boot
 *                      staging buffer, which is dead once the kernel runs.
 *   0x07000 - 0x070FF  VBE mode information block (stage 2 probe)
 *   0x07C00 - 0x07DFF  stage 1 (boot sector)
 *   0x07E00 - 0x07E14  disk address packet, boot drive and KASLR base scratch
 *   0x07E20 - 0x07E2B  VBE framebuffer info struct handed to the kernel
 *   0x08000 - 0x08017  long-mode GDT handed to the kernel
 *   0x09000 - 0x0AFFF  stage 2
 *   0x10000 - 0x8FFFF  kernel staging buffer (one chunk at a time; the
 *                      first 64 KB are reclaimed by the user page tables)
 *   0x90000            protected/long mode stack top; the kernel stack
 *                      grows DOWN from here.  The region ABOVE it is the
 *                      reserved SB16 DMA audio ring [0x90000, 0x94000):
 *                      it is identity mapped (low 1 MB) and below the ISA
 *                      DMA 16 MB limit, so the 8237 can reach it.  The
 *                      stack never grows up past 0x90000 to touch it.
 *   0x100000           kernel link-time virtual base (physical base is
 *                      randomized by KASLR into [0x0600000, 0x0E000000)
 *                      when enabled). The kernel image (code + .bss) maps
 *                      contiguously: KASLR builds put it at [base, base+3 MB),
 *                      plain builds at [0x100000, 0x400000).
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

/* VESA BIOS Extensions (VBE) linear-framebuffer video setup. Stage 2 probes a
 * high-resolution 8-bit-palette mode before entering long mode and records
 * the result for the kernel in a fixed low-memory struct (see VBE_INFO_ADDR).
 * If no VBE mode is available it falls back to VGA Mode 13h (320x200x8). The
 * 8-bit modes keep the 256-entry VGA DAC palette path used by the desktop and
 * DOOM unchanged. */
#define BIOS_VBE_GET_MODE_INFO    0x4F01
#define BIOS_VBE_SET_MODE         0x4F02
#define VBE_MODE_800x600x8        0x0103
#define VBE_MODE_640x480x8        0x0101
#define VBE_MODE_LFB              0x4000
#define VBE_MODE_INFO_ADDR        0x7000
#define VBE_MODE_ATTR_OFF         0x00
#define VBE_ATTR_SUPPORTED        0x01
#define VBE_ATTR_LFB              0x80
#define VBE_INFO_XRES_OFF         0x12
#define VBE_INFO_YRES_OFF         0x14
#define VBE_INFO_BYTES_SCAN_OFF   0x10
#define VBE_INFO_PHYSBASE_OFF     0x28

/* Framebuffer info handed to the kernel. Stage 2 writes this fixed low-memory
 * struct; the kernel reads it once at boot to map the linear framebuffer into
 * the user window. Layout:
 *   +0  dword  physical base of the linear framebuffer
 *   +4  word   bytes per scanline (pitch)
 *   +6  word   width in pixels
 *   +8  word   height in pixels
 *   +10 byte   valid (1 when stage 2 programmed a video mode) */
#define VBE_INFO_ADDR             0x7E20
#define VBE_INFO_FBBASE_OFF       0
#define VBE_INFO_PITCH_OFF        4
#define VBE_INFO_WIDTH_OFF        6
#define VBE_INFO_HEIGHT_OFF       8
#define VBE_INFO_VALID_OFF        10

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

/* SMP application-processor bootstrap stub: a flat binary copied to this low
 * address (below 1 MB so a real-mode SIPI can reach it) and executed by every
 * AP.  It reuses the page tables and 64-bit GDT stage 2 built for the BSP. */
#define AP_STUB_ADDR              0x6000
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
#define PT_FLAGS_PCD              0x010   /* page cache disable (uncacheable) */

/* The SB16 DMA audio ring [0x90000, 0x94000) is read by the 8237 DMA
 * controller directly from physical RAM, bypassing the CPU caches.  Those
 * pages must be marked uncacheable (PCD) or the freshly written PCM stays
 * stale in a write-back cache and the DMA plays garbage. */
#define SB16_DMA_PT_ENTRY         (0x90000 >> 12)   /* PT0 entry index */
#define SB16_DMA_PT_PAGES         4                 /* 0x90000..0x94000 */
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
 * could be overwritten by a later reservation.
 *
 * It must ALSO never share memory with the kernel image. The kernel .bss is
 * ~1.4 MB and grows, so a zone placed "between the kernel image and the
 * user window" (the historical 0x300000) sits right where the kernel's
 * own .bss lands once the image outgrows 2 MB. That collision silently
 * corrupted the page tables every time the shell wrote a terminal line
 * (the line buffer lived in the .bss tail), which is why user programs
 * crashed intermittently at "unmapped" addresses. The zone therefore
 * lives at 0x10000, BELOW the kernel link base (0x100000), inside the
 * boot staging buffer that is dead once the kernel is running: nothing in
 * the kernel image can ever reach it, in the plain build or under KASLR.
 * It is identity-mapped in every build (PT0 low half in KASLR, 2 MB PD
 * leaf in the plain build), so the PDEs can carry the same addresses the
 * kernel writes through. */
#define PT_USER_TABLES_ADDR       0x00010000
#define PT_USER_TABLES_BYTES      0x00038000

/* KASLR: the kernel image is loaded at a random 2 MB-aligned physical base
 * chosen from a 64-position window above the kernel heap, so the kernel's
 * physical location varies on every boot. The virtual base stays at the
 * link-time address (0x100000); the loader maps it to the chosen physical
 * base. The image (code + .bss) is mapped CONTIGUOUSLY over the whole
 * virtual span [0x100000, KASLR_IMAGE_SPAN): PT0 covers the first MB and
 * PT1 covers [0x200000, KASLR_IMAGE_SPAN) at 4 KB granularity, so a growing
 * .bss can never spill onto the identity-mapped low-memory reserved zones.
 * Keep KASLR_IMAGE_SPAN in sync with the kernel link layout: the image
 * must end below the user window at USER_LOAD_BASE (0x400000). */
#define KASLR_MIN_ADDR            0x08000000
#define KASLR_ALIGN_SHIFT         21
#define KASLR_MAX_UNITS           64
#define KASLR_IMG_OFF_1MB         0x00100000
#define KASLR_IMG_OFF_2MB         0x00200000
#define KASLR_IMAGE_SPAN          0x00300000

#define CMOS_INDEX_PORT           0x70
#define CMOS_DATA_PORT            0x71
#define CMOS_NMI_DISABLE          0x80
#define CMOS_REG_SECONDS          0x00
#define CMOS_REG_MINUTES          0x02
#define CMOS_REG_HOURS            0x04

#endif
