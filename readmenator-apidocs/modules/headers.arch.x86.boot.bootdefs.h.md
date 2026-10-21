# `headers/arch/x86/boot/bootdefs.h`

> Source: [headers/arch/x86/boot/bootdefs.h:1](../../headers/arch/x86/boot/bootdefs.h#L1) | language `h` | coverage 15.3% | [API index](../index.md)

bootdefs.h - centralized configuration for the MiniOS two-stage boot path.

## Contents

- **Functions:** [`address`](#address)
- **Macros:** [`SECTOR_BYTES`](#sector_bytes), [`SECTOR_PARAGRAPH_SHIFT`](#sector_paragraph_shift), [`SECTOR_DWORD_SHIFT`](#sector_dword_shift), [`BOOT_SIGNATURE`](#boot_signature), [`BOOT_SIGNATURE_BYTES`](#boot_signature_bytes), [`BOOT_SEG_NULL`](#boot_seg_null), [`BOOT_STACK_TOP`](#boot_stack_top), [`BOOT_DAP_ADDR`](#boot_dap_addr), [`BOOT_DAP_SIZE`](#boot_dap_size), [`BOOT_DAP_OFF_COUNT`](#boot_dap_off_count), [`BOOT_DAP_OFF_OFFSET`](#boot_dap_off_offset), [`BOOT_DAP_OFF_SEGMENT`](#boot_dap_off_segment), [`BOOT_DAP_OFF_LBA_LO`](#boot_dap_off_lba_lo), [`BOOT_DAP_OFF_LBA_HI`](#boot_dap_off_lba_hi), [`BOOT_DRIVE_ADDR`](#boot_drive_addr), [`BOOT_KASLR_ADDR`](#boot_kaslr_addr), [`BOOT_STAGE2_LBA`](#boot_stage2_lba), [`BOOT_STAGE2_SECTORS`](#boot_stage2_sectors), [`BOOT_STAGE2_ADDR`](#boot_stage2_addr), [`BOOT_STAGE2_SEG`](#boot_stage2_seg), [`BOOT_KERNEL_LBA`](#boot_kernel_lba), [`BOOT_KERNEL_BUF_ADDR`](#boot_kernel_buf_addr), [`BOOT_KERNEL_BUF_SEG`](#boot_kernel_buf_seg), [`BOOT_KERNEL_PHYS_ADDR`](#boot_kernel_phys_addr), [`BOOT_CHUNK_SECTORS`](#boot_chunk_sectors), [`BOOT_BIOS_MAX_SECTORS`](#boot_bios_max_sectors), [`BOOT_PM_STACK_TOP`](#boot_pm_stack_top), [`BOOT_SB16_DMA_ADDR`](#boot_sb16_dma_addr), [`BOOT_SB16_DMA_BYTES`](#boot_sb16_dma_bytes), [`BOOT_PCM2_DMA_ADDR`](#boot_pcm2_dma_addr), [`BOOT_PCM2_DMA_BYTES`](#boot_pcm2_dma_bytes), [`BIOS_DISK_INT`](#bios_disk_int), [`BIOS_DISK_EXT_CHECK`](#bios_disk_ext_check), [`BIOS_DISK_EXT_REQ_MAGIC`](#bios_disk_ext_req_magic), [`BIOS_DISK_EXT_ACK_MAGIC`](#bios_disk_ext_ack_magic), [`BIOS_DISK_EXT_PACKET_BIT`](#bios_disk_ext_packet_bit), [`BIOS_DISK_READ_EXT`](#bios_disk_read_ext), [`BIOS_VIDEO_INT`](#bios_video_int), [`BIOS_VIDEO_TTY_WRITE`](#bios_video_tty_write), [`BIOS_VIDEO_TTY_ATTR`](#bios_video_tty_attr), [`BIOS_VIDEO_SET_MODE`](#bios_video_set_mode), [`BIOS_VBE_GET_MODE_INFO`](#bios_vbe_get_mode_info), [`BIOS_VBE_SET_MODE`](#bios_vbe_set_mode), [`VBE_MODE_1024x768x32`](#vbe_mode_1024x768x32), [`VBE_MODE_800x600x32`](#vbe_mode_800x600x32), [`VBE_MODE_640x480x32`](#vbe_mode_640x480x32), [`VBE_MODE_1024x768x8`](#vbe_mode_1024x768x8), [`VBE_MODE_800x600x8`](#vbe_mode_800x600x8), [`VBE_MODE_640x480x8`](#vbe_mode_640x480x8), [`VBE_MODE_LFB`](#vbe_mode_lfb), [`VBE_MODE_INFO_ADDR`](#vbe_mode_info_addr), [`VBE_MODE_ATTR_OFF`](#vbe_mode_attr_off), [`VBE_ATTR_SUPPORTED`](#vbe_attr_supported), [`VBE_ATTR_LFB`](#vbe_attr_lfb), [`VBE_INFO_XRES_OFF`](#vbe_info_xres_off), [`VBE_INFO_YRES_OFF`](#vbe_info_yres_off), [`VBE_INFO_BYTES_SCAN_OFF`](#vbe_info_bytes_scan_off), [`VBE_INFO_PHYSBASE_OFF`](#vbe_info_physbase_off), [`VBE_INFO_BPP_SRC_OFF`](#vbe_info_bpp_src_off), [`VBE_BPP_8`](#vbe_bpp_8), [`VBE_BPP_24`](#vbe_bpp_24), [`VBE_BPP_32`](#vbe_bpp_32), [`VBE_INFO_ADDR`](#vbe_info_addr), [`VBE_INFO_FBBASE_OFF`](#vbe_info_fbbase_off), [`VBE_INFO_PITCH_OFF`](#vbe_info_pitch_off), [`VBE_INFO_WIDTH_OFF`](#vbe_info_width_off), [`VBE_INFO_HEIGHT_OFF`](#vbe_info_height_off), [`VBE_INFO_VALID_OFF`](#vbe_info_valid_off), [`VBE_INFO_BPP_OFF`](#vbe_info_bpp_off), [`A20_CONTROL_PORT`](#a20_control_port), [`A20_ENABLE_BIT`](#a20_enable_bit), [`A20_RESET_CLEAR_MASK`](#a20_reset_clear_mask), [`CR0_PE`](#cr0_pe), [`CR0_PE_CLEAR_MASK`](#cr0_pe_clear_mask), [`CR0_PG`](#cr0_pg), [`CR0_WP`](#cr0_wp), [`CR4_PAE`](#cr4_pae), [`CR0_MP`](#cr0_mp), [`CR0_EM`](#cr0_em), [`CR0_NW`](#cr0_nw), [`CR0_CD`](#cr0_cd), [`CR4_OSFXSR`](#cr4_osfxsr), [`CR4_OSXMMEXCPT`](#cr4_osxmmexcpt), [`MSR_EFER`](#msr_efer), [`EFER_LME`](#efer_lme), [`EFER_NXE`](#efer_nxe), [`GDT32_CODE32_SEL`](#gdt32_code32_sel), [`GDT32_DATA32_SEL`](#gdt32_data32_sel), [`GDT32_CODE16_SEL`](#gdt32_code16_sel), [`GDT32_DATA16_SEL`](#gdt32_data16_sel), [`GDT32_DESC_NULL`](#gdt32_desc_null), [`GDT32_DESC_CODE32`](#gdt32_desc_code32), [`GDT32_DESC_DATA32`](#gdt32_desc_data32), [`GDT32_DESC_CODE16`](#gdt32_desc_code16), [`GDT32_DESC_DATA16`](#gdt32_desc_data16), [`GDT64_ADDR`](#gdt64_addr), [`GDT64_BYTES`](#gdt64_bytes), [`GDT64_SMP_BYTES`](#gdt64_smp_bytes), [`AP_STUB_ADDR`](#ap_stub_addr), [`GDT64_CODE_SEL`](#gdt64_code_sel), [`GDT64_DATA_SEL`](#gdt64_data_sel), [`GDT64_USER_DATA_SEL`](#gdt64_user_data_sel), [`GDT64_USER_CODE_SEL`](#gdt64_user_code_sel), [`GDT64_DESC_NULL`](#gdt64_desc_null), [`GDT64_DESC_CODE`](#gdt64_desc_code), [`GDT64_DESC_DATA`](#gdt64_desc_data), [`GDT64_DESC_UDATA`](#gdt64_desc_udata), [`GDT64_DESC_UCODE`](#gdt64_desc_ucode), [`PT_PML4_ADDR`](#pt_pml4_addr), [`PT_PDPT_ADDR`](#pt_pdpt_addr), [`PT_PD_ADDR`](#pt_pd_addr), [`PT_USER0_ADDR`](#pt_user0_addr), [`PT_USER1_ADDR`](#pt_user1_addr), [`PT_ZERO_DWORDS`](#pt_zero_dwords), [`PT_FLAGS_PRESENT_RW`](#pt_flags_present_rw), [`PT_FLAGS_PRESENT_RW_PS`](#pt_flags_present_rw_ps), [`PT_FLAGS_PS`](#pt_flags_ps), [`PT_FLAGS_USER`](#pt_flags_user), [`PT_FLAGS_PCD`](#pt_flags_pcd), [`PT_FLAGS_PWT`](#pt_flags_pwt), [`PT_FLAGS_NX`](#pt_flags_nx), [`PT_ADDR_MASK`](#pt_addr_mask), [`PT_USER_ENTRY`](#pt_user_entry), [`PT_USER_NX_ENTRY`](#pt_user_nx_entry), [`PT_ENTRY_PRESENT`](#pt_entry_present), [`PT_ENTRY_USER`](#pt_entry_user), [`SB16_DMA_PT_ENTRY`](#sb16_dma_pt_entry), [`SB16_DMA_PT_PAGES`](#sb16_dma_pt_pages), [`PT_FLAGS_UNCACHED`](#pt_flags_uncached), [`KMM_DEVICE_PDPT_SLOT`](#kmm_device_pdpt_slot), [`PT_PD_ENTRIES`](#pt_pd_entries), [`PT_PD_ENTRY_BYTES`](#pt_pd_entry_bytes), [`PT_PD_PAGE_BYTES`](#pt_pd_page_bytes), [`PT_PD_INDEX_SHIFT`](#pt_pd_index_shift), [`PT_FILL_START_INDEX`](#pt_fill_start_index), [`PT_FILL_START_ADDR`](#pt_fill_start_addr), [`PT_FILL_ENTRIES`](#pt_fill_entries), [`PT_USER_TABLES_ADDR`](#pt_user_tables_addr), [`PT_USER_TABLES_BYTES`](#pt_user_tables_bytes), [`KASLR_MIN_ADDR`](#kaslr_min_addr), [`KASLR_ALIGN_SHIFT`](#kaslr_align_shift), [`KASLR_MAX_UNITS`](#kaslr_max_units), [`KASLR_IMG_OFF_1MB`](#kaslr_img_off_1mb), [`KASLR_IMG_OFF_2MB`](#kaslr_img_off_2mb), [`KASLR_IMAGE_SPAN`](#kaslr_image_span), [`CMOS_INDEX_PORT`](#cmos_index_port), [`CMOS_DATA_PORT`](#cmos_data_port), [`CMOS_NMI_DISABLE`](#cmos_nmi_disable), [`CMOS_REG_EXTMEM_LO`](#cmos_reg_extmem_lo), [`CMOS_REG_EXTMEM_HI`](#cmos_reg_extmem_hi), [`CMOS_EXTMEM_BASE`](#cmos_extmem_base), [`CMOS_EXTMEM_UNIT`](#cmos_extmem_unit), [`CMOS_REG_SECONDS`](#cmos_reg_seconds), [`CMOS_REG_MINUTES`](#cmos_reg_minutes), [`CMOS_REG_HOURS`](#cmos_reg_hours)

## Functions

<a id="address"></a>

### `address`

`function` | [headers/arch/x86/boot/bootdefs.h:196](../../headers/arch/x86/boot/bootdefs.h#L196)

```c
* address (below 1 MB so a real-mode SIPI can reach it) and executed by every * AP. It reuses the page tables and 64-bit GDT stage 2 built for the BSP. */ #define AP_STUB_ADDR 0x6000 #define GDT64_COD
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `it` | `below 1 MB so a real-mode SIPI can reach` |  |  |

**Returns:** `*`

*Called by:* [`CVM_NODE_STR_MAX`](progs.nuklear.cvm_emit.h.md#cvm_node_str_max)

---

## Macros

<a id="sector_bytes"></a>

### `SECTOR_BYTES`

`macro` | [headers/arch/x86/boot/bootdefs.h:54](../../headers/arch/x86/boot/bootdefs.h#L54)

```c
#define SECTOR_BYTES
```

---

<a id="sector_paragraph_shift"></a>

### `SECTOR_PARAGRAPH_SHIFT`

`macro` | [headers/arch/x86/boot/bootdefs.h:55](../../headers/arch/x86/boot/bootdefs.h#L55)

```c
#define SECTOR_PARAGRAPH_SHIFT
```

---

<a id="sector_dword_shift"></a>

### `SECTOR_DWORD_SHIFT`

`macro` | [headers/arch/x86/boot/bootdefs.h:56](../../headers/arch/x86/boot/bootdefs.h#L56)

```c
#define SECTOR_DWORD_SHIFT
```

---

<a id="boot_signature"></a>

### `BOOT_SIGNATURE`

`macro` | [headers/arch/x86/boot/bootdefs.h:58](../../headers/arch/x86/boot/bootdefs.h#L58)

```c
#define BOOT_SIGNATURE
```

---

<a id="boot_signature_bytes"></a>

### `BOOT_SIGNATURE_BYTES`

`macro` | [headers/arch/x86/boot/bootdefs.h:59](../../headers/arch/x86/boot/bootdefs.h#L59)

```c
#define BOOT_SIGNATURE_BYTES
```

---

<a id="boot_seg_null"></a>

### `BOOT_SEG_NULL`

`macro` | [headers/arch/x86/boot/bootdefs.h:61](../../headers/arch/x86/boot/bootdefs.h#L61)

```c
#define BOOT_SEG_NULL
```

---

<a id="boot_stack_top"></a>

### `BOOT_STACK_TOP`

`macro` | [headers/arch/x86/boot/bootdefs.h:62](../../headers/arch/x86/boot/bootdefs.h#L62)

```c
#define BOOT_STACK_TOP
```

---

<a id="boot_dap_addr"></a>

### `BOOT_DAP_ADDR`

`macro` | [headers/arch/x86/boot/bootdefs.h:64](../../headers/arch/x86/boot/bootdefs.h#L64)

```c
#define BOOT_DAP_ADDR
```

---

<a id="boot_dap_size"></a>

### `BOOT_DAP_SIZE`

`macro` | [headers/arch/x86/boot/bootdefs.h:65](../../headers/arch/x86/boot/bootdefs.h#L65)

```c
#define BOOT_DAP_SIZE
```

---

<a id="boot_dap_off_count"></a>

### `BOOT_DAP_OFF_COUNT`

`macro` | [headers/arch/x86/boot/bootdefs.h:66](../../headers/arch/x86/boot/bootdefs.h#L66)

```c
#define BOOT_DAP_OFF_COUNT
```

*Called by:* [`normalize`](arch.x86.boot.stage1.S.md#normalize), [`piece_size_ready`](arch.x86.boot.stage2.S.md#piece_size_ready)

---

<a id="boot_dap_off_offset"></a>

### `BOOT_DAP_OFF_OFFSET`

`macro` | [headers/arch/x86/boot/bootdefs.h:67](../../headers/arch/x86/boot/bootdefs.h#L67)

```c
#define BOOT_DAP_OFF_OFFSET
```

*Called by:* [`normalize`](arch.x86.boot.stage1.S.md#normalize), [`piece_size_ready`](arch.x86.boot.stage2.S.md#piece_size_ready)

---

<a id="boot_dap_off_segment"></a>

### `BOOT_DAP_OFF_SEGMENT`

`macro` | [headers/arch/x86/boot/bootdefs.h:68](../../headers/arch/x86/boot/bootdefs.h#L68)

```c
#define BOOT_DAP_OFF_SEGMENT
```

*Called by:* [`normalize`](arch.x86.boot.stage1.S.md#normalize), [`piece_size_ready`](arch.x86.boot.stage2.S.md#piece_size_ready)

---

<a id="boot_dap_off_lba_lo"></a>

### `BOOT_DAP_OFF_LBA_LO`

`macro` | [headers/arch/x86/boot/bootdefs.h:69](../../headers/arch/x86/boot/bootdefs.h#L69)

```c
#define BOOT_DAP_OFF_LBA_LO
```

*Called by:* [`normalize`](arch.x86.boot.stage1.S.md#normalize), [`piece_size_ready`](arch.x86.boot.stage2.S.md#piece_size_ready)

---

<a id="boot_dap_off_lba_hi"></a>

### `BOOT_DAP_OFF_LBA_HI`

`macro` | [headers/arch/x86/boot/bootdefs.h:70](../../headers/arch/x86/boot/bootdefs.h#L70)

```c
#define BOOT_DAP_OFF_LBA_HI
```

*Called by:* [`normalize`](arch.x86.boot.stage1.S.md#normalize), [`piece_size_ready`](arch.x86.boot.stage2.S.md#piece_size_ready)

---

<a id="boot_drive_addr"></a>

### `BOOT_DRIVE_ADDR`

`macro` | [headers/arch/x86/boot/bootdefs.h:71](../../headers/arch/x86/boot/bootdefs.h#L71)

```c
#define BOOT_DRIVE_ADDR
```

---

<a id="boot_kaslr_addr"></a>

### `BOOT_KASLR_ADDR`

`macro` | [headers/arch/x86/boot/bootdefs.h:72](../../headers/arch/x86/boot/bootdefs.h#L72)

```c
#define BOOT_KASLR_ADDR
```

---

<a id="boot_stage2_lba"></a>

### `BOOT_STAGE2_LBA`

`macro` | [headers/arch/x86/boot/bootdefs.h:74](../../headers/arch/x86/boot/bootdefs.h#L74)

```c
#define BOOT_STAGE2_LBA
```

---

<a id="boot_stage2_sectors"></a>

### `BOOT_STAGE2_SECTORS`

`macro` | [headers/arch/x86/boot/bootdefs.h:75](../../headers/arch/x86/boot/bootdefs.h#L75)

```c
#define BOOT_STAGE2_SECTORS
```

---

<a id="boot_stage2_addr"></a>

### `BOOT_STAGE2_ADDR`

`macro` | [headers/arch/x86/boot/bootdefs.h:76](../../headers/arch/x86/boot/bootdefs.h#L76)

```c
#define BOOT_STAGE2_ADDR
```

---

<a id="boot_stage2_seg"></a>

### `BOOT_STAGE2_SEG`

`macro` | [headers/arch/x86/boot/bootdefs.h:77](../../headers/arch/x86/boot/bootdefs.h#L77)

```c
#define BOOT_STAGE2_SEG
```

---

<a id="boot_kernel_lba"></a>

### `BOOT_KERNEL_LBA`

`macro` | [headers/arch/x86/boot/bootdefs.h:79](../../headers/arch/x86/boot/bootdefs.h#L79)

```c
#define BOOT_KERNEL_LBA
```

---

<a id="boot_kernel_buf_addr"></a>

### `BOOT_KERNEL_BUF_ADDR`

`macro` | [headers/arch/x86/boot/bootdefs.h:80](../../headers/arch/x86/boot/bootdefs.h#L80)

```c
#define BOOT_KERNEL_BUF_ADDR
```

---

<a id="boot_kernel_buf_seg"></a>

### `BOOT_KERNEL_BUF_SEG`

`macro` | [headers/arch/x86/boot/bootdefs.h:81](../../headers/arch/x86/boot/bootdefs.h#L81)

```c
#define BOOT_KERNEL_BUF_SEG
```

---

<a id="boot_kernel_phys_addr"></a>

### `BOOT_KERNEL_PHYS_ADDR`

`macro` | [headers/arch/x86/boot/bootdefs.h:82](../../headers/arch/x86/boot/bootdefs.h#L82)

```c
#define BOOT_KERNEL_PHYS_ADDR
```

---

<a id="boot_chunk_sectors"></a>

### `BOOT_CHUNK_SECTORS`

`macro` | [headers/arch/x86/boot/bootdefs.h:84](../../headers/arch/x86/boot/bootdefs.h#L84)

```c
#define BOOT_CHUNK_SECTORS
```

---

<a id="boot_bios_max_sectors"></a>

### `BOOT_BIOS_MAX_SECTORS`

`macro` | [headers/arch/x86/boot/bootdefs.h:85](../../headers/arch/x86/boot/bootdefs.h#L85)

```c
#define BOOT_BIOS_MAX_SECTORS
```

---

<a id="boot_pm_stack_top"></a>

### `BOOT_PM_STACK_TOP`

`macro` | [headers/arch/x86/boot/bootdefs.h:87](../../headers/arch/x86/boot/bootdefs.h#L87)

```c
#define BOOT_PM_STACK_TOP
```

---

<a id="boot_sb16_dma_addr"></a>

### `BOOT_SB16_DMA_ADDR`

`macro` | [headers/arch/x86/boot/bootdefs.h:89](../../headers/arch/x86/boot/bootdefs.h#L89)

```c
#define BOOT_SB16_DMA_ADDR
```

---

<a id="boot_sb16_dma_bytes"></a>

### `BOOT_SB16_DMA_BYTES`

`macro` | [headers/arch/x86/boot/bootdefs.h:90](../../headers/arch/x86/boot/bootdefs.h#L90)

```c
#define BOOT_SB16_DMA_BYTES
```

---

<a id="boot_pcm2_dma_addr"></a>

### `BOOT_PCM2_DMA_ADDR`

`macro` | [headers/arch/x86/boot/bootdefs.h:91](../../headers/arch/x86/boot/bootdefs.h#L91)

```c
#define BOOT_PCM2_DMA_ADDR
```

---

<a id="boot_pcm2_dma_bytes"></a>

### `BOOT_PCM2_DMA_BYTES`

`macro` | [headers/arch/x86/boot/bootdefs.h:92](../../headers/arch/x86/boot/bootdefs.h#L92)

```c
#define BOOT_PCM2_DMA_BYTES
```

---

<a id="bios_disk_int"></a>

### `BIOS_DISK_INT`

`macro` | [headers/arch/x86/boot/bootdefs.h:94](../../headers/arch/x86/boot/bootdefs.h#L94)

```c
#define BIOS_DISK_INT
```

---

<a id="bios_disk_ext_check"></a>

### `BIOS_DISK_EXT_CHECK`

`macro` | [headers/arch/x86/boot/bootdefs.h:95](../../headers/arch/x86/boot/bootdefs.h#L95)

```c
#define BIOS_DISK_EXT_CHECK
```

---

<a id="bios_disk_ext_req_magic"></a>

### `BIOS_DISK_EXT_REQ_MAGIC`

`macro` | [headers/arch/x86/boot/bootdefs.h:96](../../headers/arch/x86/boot/bootdefs.h#L96)

```c
#define BIOS_DISK_EXT_REQ_MAGIC
```

---

<a id="bios_disk_ext_ack_magic"></a>

### `BIOS_DISK_EXT_ACK_MAGIC`

`macro` | [headers/arch/x86/boot/bootdefs.h:97](../../headers/arch/x86/boot/bootdefs.h#L97)

```c
#define BIOS_DISK_EXT_ACK_MAGIC
```

---

<a id="bios_disk_ext_packet_bit"></a>

### `BIOS_DISK_EXT_PACKET_BIT`

`macro` | [headers/arch/x86/boot/bootdefs.h:98](../../headers/arch/x86/boot/bootdefs.h#L98)

```c
#define BIOS_DISK_EXT_PACKET_BIT
```

---

<a id="bios_disk_read_ext"></a>

### `BIOS_DISK_READ_EXT`

`macro` | [headers/arch/x86/boot/bootdefs.h:99](../../headers/arch/x86/boot/bootdefs.h#L99)

```c
#define BIOS_DISK_READ_EXT
```

---

<a id="bios_video_int"></a>

### `BIOS_VIDEO_INT`

`macro` | [headers/arch/x86/boot/bootdefs.h:101](../../headers/arch/x86/boot/bootdefs.h#L101)

```c
#define BIOS_VIDEO_INT
```

---

<a id="bios_video_tty_write"></a>

### `BIOS_VIDEO_TTY_WRITE`

`macro` | [headers/arch/x86/boot/bootdefs.h:102](../../headers/arch/x86/boot/bootdefs.h#L102)

```c
#define BIOS_VIDEO_TTY_WRITE
```

---

<a id="bios_video_tty_attr"></a>

### `BIOS_VIDEO_TTY_ATTR`

`macro` | [headers/arch/x86/boot/bootdefs.h:103](../../headers/arch/x86/boot/bootdefs.h#L103)

```c
#define BIOS_VIDEO_TTY_ATTR
```

---

<a id="bios_video_set_mode"></a>

### `BIOS_VIDEO_SET_MODE`

`macro` | [headers/arch/x86/boot/bootdefs.h:104](../../headers/arch/x86/boot/bootdefs.h#L104)

```c
#define BIOS_VIDEO_SET_MODE
```

---

<a id="bios_vbe_get_mode_info"></a>

### `BIOS_VBE_GET_MODE_INFO`

`macro` | [headers/arch/x86/boot/bootdefs.h:116](../../headers/arch/x86/boot/bootdefs.h#L116)

```c
#define BIOS_VBE_GET_MODE_INFO
```

VESA BIOS Extensions (VBE) linear-framebuffer video setup.

Stage 2 probes a ladder of modes, true color first at each resolution, and records the result for the kernel in a fixed low-memory struct (see VBE_INFO_ADDR): 1024x768x32, 1024x768x8, 800x600x32, 800x600x8, 640x480x32, 640x480x8. If no VBE mode is available it falls back to VGA Mode 13h (320x200x8). In a true-color mode the kernel expands its palette-index drawing to RGB and the desktop/icon pixels are no longer quantized; the 8-bit modes keep the 256-entry VGA DAC palette path unchanged. The kernel maps the framebuffer slot by slot, so a multi-MB framebuffer spanning two 2 MB PD slots is fully mapped.

---

<a id="bios_vbe_set_mode"></a>

### `BIOS_VBE_SET_MODE`

`macro` | [headers/arch/x86/boot/bootdefs.h:117](../../headers/arch/x86/boot/bootdefs.h#L117)

```c
#define BIOS_VBE_SET_MODE
```

---

<a id="vbe_mode_1024x768x32"></a>

### `VBE_MODE_1024x768x32`

`macro` | [headers/arch/x86/boot/bootdefs.h:118](../../headers/arch/x86/boot/bootdefs.h#L118)

```c
#define VBE_MODE_1024x768x32
```

---

<a id="vbe_mode_800x600x32"></a>

### `VBE_MODE_800x600x32`

`macro` | [headers/arch/x86/boot/bootdefs.h:119](../../headers/arch/x86/boot/bootdefs.h#L119)

```c
#define VBE_MODE_800x600x32
```

---

<a id="vbe_mode_640x480x32"></a>

### `VBE_MODE_640x480x32`

`macro` | [headers/arch/x86/boot/bootdefs.h:120](../../headers/arch/x86/boot/bootdefs.h#L120)

```c
#define VBE_MODE_640x480x32
```

---

<a id="vbe_mode_1024x768x8"></a>

### `VBE_MODE_1024x768x8`

`macro` | [headers/arch/x86/boot/bootdefs.h:121](../../headers/arch/x86/boot/bootdefs.h#L121)

```c
#define VBE_MODE_1024x768x8
```

---

<a id="vbe_mode_800x600x8"></a>

### `VBE_MODE_800x600x8`

`macro` | [headers/arch/x86/boot/bootdefs.h:122](../../headers/arch/x86/boot/bootdefs.h#L122)

```c
#define VBE_MODE_800x600x8
```

---

<a id="vbe_mode_640x480x8"></a>

### `VBE_MODE_640x480x8`

`macro` | [headers/arch/x86/boot/bootdefs.h:123](../../headers/arch/x86/boot/bootdefs.h#L123)

```c
#define VBE_MODE_640x480x8
```

---

<a id="vbe_mode_lfb"></a>

### `VBE_MODE_LFB`

`macro` | [headers/arch/x86/boot/bootdefs.h:124](../../headers/arch/x86/boot/bootdefs.h#L124)

```c
#define VBE_MODE_LFB
```

---

<a id="vbe_mode_info_addr"></a>

### `VBE_MODE_INFO_ADDR`

`macro` | [headers/arch/x86/boot/bootdefs.h:125](../../headers/arch/x86/boot/bootdefs.h#L125)

```c
#define VBE_MODE_INFO_ADDR
```

---

<a id="vbe_mode_attr_off"></a>

### `VBE_MODE_ATTR_OFF`

`macro` | [headers/arch/x86/boot/bootdefs.h:126](../../headers/arch/x86/boot/bootdefs.h#L126)

```c
#define VBE_MODE_ATTR_OFF
```

---

<a id="vbe_attr_supported"></a>

### `VBE_ATTR_SUPPORTED`

`macro` | [headers/arch/x86/boot/bootdefs.h:127](../../headers/arch/x86/boot/bootdefs.h#L127)

```c
#define VBE_ATTR_SUPPORTED
```

---

<a id="vbe_attr_lfb"></a>

### `VBE_ATTR_LFB`

`macro` | [headers/arch/x86/boot/bootdefs.h:128](../../headers/arch/x86/boot/bootdefs.h#L128)

```c
#define VBE_ATTR_LFB
```

---

<a id="vbe_info_xres_off"></a>

### `VBE_INFO_XRES_OFF`

`macro` | [headers/arch/x86/boot/bootdefs.h:129](../../headers/arch/x86/boot/bootdefs.h#L129)

```c
#define VBE_INFO_XRES_OFF
```

*Called by:* [`vbe_try_bpp_ok`](arch.x86.boot.stage2.S.md#vbe_try_bpp_ok)

---

<a id="vbe_info_yres_off"></a>

### `VBE_INFO_YRES_OFF`

`macro` | [headers/arch/x86/boot/bootdefs.h:130](../../headers/arch/x86/boot/bootdefs.h#L130)

```c
#define VBE_INFO_YRES_OFF
```

*Called by:* [`vbe_try_bpp_ok`](arch.x86.boot.stage2.S.md#vbe_try_bpp_ok)

---

<a id="vbe_info_bytes_scan_off"></a>

### `VBE_INFO_BYTES_SCAN_OFF`

`macro` | [headers/arch/x86/boot/bootdefs.h:131](../../headers/arch/x86/boot/bootdefs.h#L131)

```c
#define VBE_INFO_BYTES_SCAN_OFF
```

*Called by:* [`vbe_try_bpp_ok`](arch.x86.boot.stage2.S.md#vbe_try_bpp_ok)

---

<a id="vbe_info_physbase_off"></a>

### `VBE_INFO_PHYSBASE_OFF`

`macro` | [headers/arch/x86/boot/bootdefs.h:132](../../headers/arch/x86/boot/bootdefs.h#L132)

```c
#define VBE_INFO_PHYSBASE_OFF
```

*Called by:* [`vbe_try_bpp_ok`](arch.x86.boot.stage2.S.md#vbe_try_bpp_ok)

---

<a id="vbe_info_bpp_src_off"></a>

### `VBE_INFO_BPP_SRC_OFF`

`macro` | [headers/arch/x86/boot/bootdefs.h:133](../../headers/arch/x86/boot/bootdefs.h#L133)

```c
#define VBE_INFO_BPP_SRC_OFF
```

*Called by:* [`vbe_try_bpp_ok`](arch.x86.boot.stage2.S.md#vbe_try_bpp_ok), [`vbe_try_mode`](arch.x86.boot.stage2.S.md#vbe_try_mode)

---

<a id="vbe_bpp_8"></a>

### `VBE_BPP_8`

`macro` | [headers/arch/x86/boot/bootdefs.h:134](../../headers/arch/x86/boot/bootdefs.h#L134)

```c
#define VBE_BPP_8
```

---

<a id="vbe_bpp_24"></a>

### `VBE_BPP_24`

`macro` | [headers/arch/x86/boot/bootdefs.h:135](../../headers/arch/x86/boot/bootdefs.h#L135)

```c
#define VBE_BPP_24
```

---

<a id="vbe_bpp_32"></a>

### `VBE_BPP_32`

`macro` | [headers/arch/x86/boot/bootdefs.h:136](../../headers/arch/x86/boot/bootdefs.h#L136)

```c
#define VBE_BPP_32
```

---

<a id="vbe_info_addr"></a>

### `VBE_INFO_ADDR`

`macro` | [headers/arch/x86/boot/bootdefs.h:148](../../headers/arch/x86/boot/bootdefs.h#L148)

```c
#define VBE_INFO_ADDR
```

Framebuffer info handed to the kernel.

Stage 2 writes this fixed low-memory struct; the kernel reads it once at boot to map the linear framebuffer into the user window. Layout: +0  dword  physical base of the linear framebuffer +4  word   bytes per scanline (pitch) +6  word   width in pixels +8  word   height in pixels +10 byte   valid (1 when stage 2 programmed a video mode) +11 byte   bits per pixel (8, 24 or 32; 8 when stage 2 fell back to VGA Mode 13h, whose mode info carries no bpp field)

---

<a id="vbe_info_fbbase_off"></a>

### `VBE_INFO_FBBASE_OFF`

`macro` | [headers/arch/x86/boot/bootdefs.h:149](../../headers/arch/x86/boot/bootdefs.h#L149)

```c
#define VBE_INFO_FBBASE_OFF
```

---

<a id="vbe_info_pitch_off"></a>

### `VBE_INFO_PITCH_OFF`

`macro` | [headers/arch/x86/boot/bootdefs.h:150](../../headers/arch/x86/boot/bootdefs.h#L150)

```c
#define VBE_INFO_PITCH_OFF
```

---

<a id="vbe_info_width_off"></a>

### `VBE_INFO_WIDTH_OFF`

`macro` | [headers/arch/x86/boot/bootdefs.h:151](../../headers/arch/x86/boot/bootdefs.h#L151)

```c
#define VBE_INFO_WIDTH_OFF
```

---

<a id="vbe_info_height_off"></a>

### `VBE_INFO_HEIGHT_OFF`

`macro` | [headers/arch/x86/boot/bootdefs.h:152](../../headers/arch/x86/boot/bootdefs.h#L152)

```c
#define VBE_INFO_HEIGHT_OFF
```

---

<a id="vbe_info_valid_off"></a>

### `VBE_INFO_VALID_OFF`

`macro` | [headers/arch/x86/boot/bootdefs.h:153](../../headers/arch/x86/boot/bootdefs.h#L153)

```c
#define VBE_INFO_VALID_OFF
```

---

<a id="vbe_info_bpp_off"></a>

### `VBE_INFO_BPP_OFF`

`macro` | [headers/arch/x86/boot/bootdefs.h:154](../../headers/arch/x86/boot/bootdefs.h#L154)

```c
#define VBE_INFO_BPP_OFF
```

---

<a id="a20_control_port"></a>

### `A20_CONTROL_PORT`

`macro` | [headers/arch/x86/boot/bootdefs.h:156](../../headers/arch/x86/boot/bootdefs.h#L156)

```c
#define A20_CONTROL_PORT
```

---

<a id="a20_enable_bit"></a>

### `A20_ENABLE_BIT`

`macro` | [headers/arch/x86/boot/bootdefs.h:157](../../headers/arch/x86/boot/bootdefs.h#L157)

```c
#define A20_ENABLE_BIT
```

---

<a id="a20_reset_clear_mask"></a>

### `A20_RESET_CLEAR_MASK`

`macro` | [headers/arch/x86/boot/bootdefs.h:158](../../headers/arch/x86/boot/bootdefs.h#L158)

```c
#define A20_RESET_CLEAR_MASK
```

---

<a id="cr0_pe"></a>

### `CR0_PE`

`macro` | [headers/arch/x86/boot/bootdefs.h:160](../../headers/arch/x86/boot/bootdefs.h#L160)

```c
#define CR0_PE
```

---

<a id="cr0_pe_clear_mask"></a>

### `CR0_PE_CLEAR_MASK`

`macro` | [headers/arch/x86/boot/bootdefs.h:161](../../headers/arch/x86/boot/bootdefs.h#L161)

```c
#define CR0_PE_CLEAR_MASK
```

---

<a id="cr0_pg"></a>

### `CR0_PG`

`macro` | [headers/arch/x86/boot/bootdefs.h:162](../../headers/arch/x86/boot/bootdefs.h#L162)

```c
#define CR0_PG
```

---

<a id="cr0_wp"></a>

### `CR0_WP`

`macro` | [headers/arch/x86/boot/bootdefs.h:163](../../headers/arch/x86/boot/bootdefs.h#L163)

```c
#define CR0_WP
```

---

<a id="cr4_pae"></a>

### `CR4_PAE`

`macro` | [headers/arch/x86/boot/bootdefs.h:164](../../headers/arch/x86/boot/bootdefs.h#L164)

```c
#define CR4_PAE
```

ring 0 honours read-only user pages (COW)

---

<a id="cr0_mp"></a>

### `CR0_MP`

`macro` | [headers/arch/x86/boot/bootdefs.h:165](../../headers/arch/x86/boot/bootdefs.h#L165)

```c
#define CR0_MP
```

---

<a id="cr0_em"></a>

### `CR0_EM`

`macro` | [headers/arch/x86/boot/bootdefs.h:166](../../headers/arch/x86/boot/bootdefs.h#L166)

```c
#define CR0_EM
```

WAIT/FWAIT honour TS (SSE contract)

---

<a id="cr0_nw"></a>

### `CR0_NW`

`macro` | [headers/arch/x86/boot/bootdefs.h:167](../../headers/arch/x86/boot/bootdefs.h#L167)

```c
#define CR0_NW
```

x87/SSE emulation: must be clear for SSE

---

<a id="cr0_cd"></a>

### `CR0_CD`

`macro` | [headers/arch/x86/boot/bootdefs.h:168](../../headers/arch/x86/boot/bootdefs.h#L168)

```c
#define CR0_CD
```

not write-through (power-on value on an AP)

---

<a id="cr4_osfxsr"></a>

### `CR4_OSFXSR`

`macro` | [headers/arch/x86/boot/bootdefs.h:169](../../headers/arch/x86/boot/bootdefs.h#L169)

```c
#define CR4_OSFXSR
```

cache disable (power-on value on an AP)

---

<a id="cr4_osxmmexcpt"></a>

### `CR4_OSXMMEXCPT`

`macro` | [headers/arch/x86/boot/bootdefs.h:170](../../headers/arch/x86/boot/bootdefs.h#L170)

```c
#define CR4_OSXMMEXCPT
```

FXSAVE/FXRSTOR and SSE instructions enabled

---

<a id="msr_efer"></a>

### `MSR_EFER`

`macro` | [headers/arch/x86/boot/bootdefs.h:172](../../headers/arch/x86/boot/bootdefs.h#L172)

```c
#define MSR_EFER
```

---

<a id="efer_lme"></a>

### `EFER_LME`

`macro` | [headers/arch/x86/boot/bootdefs.h:173](../../headers/arch/x86/boot/bootdefs.h#L173)

```c
#define EFER_LME
```

---

<a id="efer_nxe"></a>

### `EFER_NXE`

`macro` | [headers/arch/x86/boot/bootdefs.h:174](../../headers/arch/x86/boot/bootdefs.h#L174)

```c
#define EFER_NXE
```

---

<a id="gdt32_code32_sel"></a>

### `GDT32_CODE32_SEL`

`macro` | [headers/arch/x86/boot/bootdefs.h:176](../../headers/arch/x86/boot/bootdefs.h#L176)

```c
#define GDT32_CODE32_SEL
```

---

<a id="gdt32_data32_sel"></a>

### `GDT32_DATA32_SEL`

`macro` | [headers/arch/x86/boot/bootdefs.h:177](../../headers/arch/x86/boot/bootdefs.h#L177)

```c
#define GDT32_DATA32_SEL
```

---

<a id="gdt32_code16_sel"></a>

### `GDT32_CODE16_SEL`

`macro` | [headers/arch/x86/boot/bootdefs.h:178](../../headers/arch/x86/boot/bootdefs.h#L178)

```c
#define GDT32_CODE16_SEL
```

---

<a id="gdt32_data16_sel"></a>

### `GDT32_DATA16_SEL`

`macro` | [headers/arch/x86/boot/bootdefs.h:179](../../headers/arch/x86/boot/bootdefs.h#L179)

```c
#define GDT32_DATA16_SEL
```

---

<a id="gdt32_desc_null"></a>

### `GDT32_DESC_NULL`

`macro` | [headers/arch/x86/boot/bootdefs.h:181](../../headers/arch/x86/boot/bootdefs.h#L181)

```c
#define GDT32_DESC_NULL
```

---

<a id="gdt32_desc_code32"></a>

### `GDT32_DESC_CODE32`

`macro` | [headers/arch/x86/boot/bootdefs.h:182](../../headers/arch/x86/boot/bootdefs.h#L182)

```c
#define GDT32_DESC_CODE32
```

---

<a id="gdt32_desc_data32"></a>

### `GDT32_DESC_DATA32`

`macro` | [headers/arch/x86/boot/bootdefs.h:183](../../headers/arch/x86/boot/bootdefs.h#L183)

```c
#define GDT32_DESC_DATA32
```

---

<a id="gdt32_desc_code16"></a>

### `GDT32_DESC_CODE16`

`macro` | [headers/arch/x86/boot/bootdefs.h:184](../../headers/arch/x86/boot/bootdefs.h#L184)

```c
#define GDT32_DESC_CODE16
```

---

<a id="gdt32_desc_data16"></a>

### `GDT32_DESC_DATA16`

`macro` | [headers/arch/x86/boot/bootdefs.h:185](../../headers/arch/x86/boot/bootdefs.h#L185)

```c
#define GDT32_DESC_DATA16
```

---

<a id="gdt64_addr"></a>

### `GDT64_ADDR`

`macro` | [headers/arch/x86/boot/bootdefs.h:187](../../headers/arch/x86/boot/bootdefs.h#L187)

```c
#define GDT64_ADDR
```

---

<a id="gdt64_bytes"></a>

### `GDT64_BYTES`

`macro` | [headers/arch/x86/boot/bootdefs.h:188](../../headers/arch/x86/boot/bootdefs.h#L188)

```c
#define GDT64_BYTES
```

---

<a id="gdt64_smp_bytes"></a>

### `GDT64_SMP_BYTES`

`macro` | [headers/arch/x86/boot/bootdefs.h:193](../../headers/arch/x86/boot/bootdefs.h#L193)

```c
#define GDT64_SMP_BYTES
```

Runtime-expanded GDT: the 5 stage-2 entries plus one 16-byte TSS descriptor (two slots) per CPU for MAX_CPUS 8.  tss_init() writes them; the AP stub loads this limit so every TR selector is inside the table.  sched.c asserts this equals (5 + 2*MAX_CPUS)*8.

---

<a id="ap_stub_addr"></a>

### `AP_STUB_ADDR`

`macro` | [headers/arch/x86/boot/bootdefs.h:198](../../headers/arch/x86/boot/bootdefs.h#L198)

```c
#define AP_STUB_ADDR
```

SMP application-processor bootstrap stub: a flat binary copied to this low address (below 1 MB so a real-mode SIPI can reach it) and executed by every AP.

It reuses the page tables and 64-bit GDT stage 2 built for the BSP.

---

<a id="gdt64_code_sel"></a>

### `GDT64_CODE_SEL`

`macro` | [headers/arch/x86/boot/bootdefs.h:199](../../headers/arch/x86/boot/bootdefs.h#L199)

```c
#define GDT64_CODE_SEL
```

---

<a id="gdt64_data_sel"></a>

### `GDT64_DATA_SEL`

`macro` | [headers/arch/x86/boot/bootdefs.h:200](../../headers/arch/x86/boot/bootdefs.h#L200)

```c
#define GDT64_DATA_SEL
```

---

<a id="gdt64_user_data_sel"></a>

### `GDT64_USER_DATA_SEL`

`macro` | [headers/arch/x86/boot/bootdefs.h:201](../../headers/arch/x86/boot/bootdefs.h#L201)

```c
#define GDT64_USER_DATA_SEL
```

---

<a id="gdt64_user_code_sel"></a>

### `GDT64_USER_CODE_SEL`

`macro` | [headers/arch/x86/boot/bootdefs.h:202](../../headers/arch/x86/boot/bootdefs.h#L202)

```c
#define GDT64_USER_CODE_SEL
```

---

<a id="gdt64_desc_null"></a>

### `GDT64_DESC_NULL`

`macro` | [headers/arch/x86/boot/bootdefs.h:203](../../headers/arch/x86/boot/bootdefs.h#L203)

```c
#define GDT64_DESC_NULL
```

---

<a id="gdt64_desc_code"></a>

### `GDT64_DESC_CODE`

`macro` | [headers/arch/x86/boot/bootdefs.h:204](../../headers/arch/x86/boot/bootdefs.h#L204)

```c
#define GDT64_DESC_CODE
```

---

<a id="gdt64_desc_data"></a>

### `GDT64_DESC_DATA`

`macro` | [headers/arch/x86/boot/bootdefs.h:205](../../headers/arch/x86/boot/bootdefs.h#L205)

```c
#define GDT64_DESC_DATA
```

---

<a id="gdt64_desc_udata"></a>

### `GDT64_DESC_UDATA`

`macro` | [headers/arch/x86/boot/bootdefs.h:206](../../headers/arch/x86/boot/bootdefs.h#L206)

```c
#define GDT64_DESC_UDATA
```

---

<a id="gdt64_desc_ucode"></a>

### `GDT64_DESC_UCODE`

`macro` | [headers/arch/x86/boot/bootdefs.h:207](../../headers/arch/x86/boot/bootdefs.h#L207)

```c
#define GDT64_DESC_UCODE
```

---

<a id="pt_pml4_addr"></a>

### `PT_PML4_ADDR`

`macro` | [headers/arch/x86/boot/bootdefs.h:209](../../headers/arch/x86/boot/bootdefs.h#L209)

```c
#define PT_PML4_ADDR
```

---

<a id="pt_pdpt_addr"></a>

### `PT_PDPT_ADDR`

`macro` | [headers/arch/x86/boot/bootdefs.h:210](../../headers/arch/x86/boot/bootdefs.h#L210)

```c
#define PT_PDPT_ADDR
```

---

<a id="pt_pd_addr"></a>

### `PT_PD_ADDR`

`macro` | [headers/arch/x86/boot/bootdefs.h:211](../../headers/arch/x86/boot/bootdefs.h#L211)

```c
#define PT_PD_ADDR
```

---

<a id="pt_user0_addr"></a>

### `PT_USER0_ADDR`

`macro` | [headers/arch/x86/boot/bootdefs.h:212](../../headers/arch/x86/boot/bootdefs.h#L212)

```c
#define PT_USER0_ADDR
```

---

<a id="pt_user1_addr"></a>

### `PT_USER1_ADDR`

`macro` | [headers/arch/x86/boot/bootdefs.h:213](../../headers/arch/x86/boot/bootdefs.h#L213)

```c
#define PT_USER1_ADDR
```

---

<a id="pt_zero_dwords"></a>

### `PT_ZERO_DWORDS`

`macro` | [headers/arch/x86/boot/bootdefs.h:214](../../headers/arch/x86/boot/bootdefs.h#L214)

```c
#define PT_ZERO_DWORDS
```

---

<a id="pt_flags_present_rw"></a>

### `PT_FLAGS_PRESENT_RW`

`macro` | [headers/arch/x86/boot/bootdefs.h:215](../../headers/arch/x86/boot/bootdefs.h#L215)

```c
#define PT_FLAGS_PRESENT_RW
```

---

<a id="pt_flags_present_rw_ps"></a>

### `PT_FLAGS_PRESENT_RW_PS`

`macro` | [headers/arch/x86/boot/bootdefs.h:216](../../headers/arch/x86/boot/bootdefs.h#L216)

```c
#define PT_FLAGS_PRESENT_RW_PS
```

---

<a id="pt_flags_ps"></a>

### `PT_FLAGS_PS`

`macro` | [headers/arch/x86/boot/bootdefs.h:217](../../headers/arch/x86/boot/bootdefs.h#L217)

```c
#define PT_FLAGS_PS
```

---

<a id="pt_flags_user"></a>

### `PT_FLAGS_USER`

`macro` | [headers/arch/x86/boot/bootdefs.h:218](../../headers/arch/x86/boot/bootdefs.h#L218)

```c
#define PT_FLAGS_USER
```

---

<a id="pt_flags_pcd"></a>

### `PT_FLAGS_PCD`

`macro` | [headers/arch/x86/boot/bootdefs.h:219](../../headers/arch/x86/boot/bootdefs.h#L219)

```c
#define PT_FLAGS_PCD
```

---

<a id="pt_flags_pwt"></a>

### `PT_FLAGS_PWT`

`macro` | [headers/arch/x86/boot/bootdefs.h:220](../../headers/arch/x86/boot/bootdefs.h#L220)

```c
#define PT_FLAGS_PWT
```

page cache disable (uncacheable)

---

<a id="pt_flags_nx"></a>

### `PT_FLAGS_NX`

`macro` | [headers/arch/x86/boot/bootdefs.h:221](../../headers/arch/x86/boot/bootdefs.h#L221)

```c
#define PT_FLAGS_NX
```

page write-through

---

<a id="pt_addr_mask"></a>

### `PT_ADDR_MASK`

`macro` | [headers/arch/x86/boot/bootdefs.h:222](../../headers/arch/x86/boot/bootdefs.h#L222)

```c
#define PT_ADDR_MASK
```

no-execute

---

<a id="pt_user_entry"></a>

### `PT_USER_ENTRY`

`macro` | [headers/arch/x86/boot/bootdefs.h:223](../../headers/arch/x86/boot/bootdefs.h#L223)

```c
#define PT_USER_ENTRY
```

physical addr mask

---

<a id="pt_user_nx_entry"></a>

### `PT_USER_NX_ENTRY`

`macro` | [headers/arch/x86/boot/bootdefs.h:224](../../headers/arch/x86/boot/bootdefs.h#L224)

```c
#define PT_USER_NX_ENTRY
```

present | rw | user

---

<a id="pt_entry_present"></a>

### `PT_ENTRY_PRESENT`

`macro` | [headers/arch/x86/boot/bootdefs.h:225](../../headers/arch/x86/boot/bootdefs.h#L225)

```c
#define PT_ENTRY_PRESENT
```

---

<a id="pt_entry_user"></a>

### `PT_ENTRY_USER`

`macro` | [headers/arch/x86/boot/bootdefs.h:226](../../headers/arch/x86/boot/bootdefs.h#L226)

```c
#define PT_ENTRY_USER
```

present | rw

---

<a id="sb16_dma_pt_entry"></a>

### `SB16_DMA_PT_ENTRY`

`macro` | [headers/arch/x86/boot/bootdefs.h:232](../../headers/arch/x86/boot/bootdefs.h#L232)

```c
#define SB16_DMA_PT_ENTRY
```

The SB16 DMA audio ring [0x90000, 0x94000) is read by the 8237 DMA controller directly from physical RAM, bypassing the CPU caches.

Those pages must be marked uncacheable (PCD) or the freshly written PCM stays stale in a write-back cache and the DMA plays garbage.

---

<a id="sb16_dma_pt_pages"></a>

### `SB16_DMA_PT_PAGES`

`macro` | [headers/arch/x86/boot/bootdefs.h:233](../../headers/arch/x86/boot/bootdefs.h#L233)

```c
#define SB16_DMA_PT_PAGES
```

PT0 entry index

---

<a id="pt_flags_uncached"></a>

### `PT_FLAGS_UNCACHED`

`macro` | [headers/arch/x86/boot/bootdefs.h:238](../../headers/arch/x86/boot/bootdefs.h#L238)

```c
#define PT_FLAGS_UNCACHED
```

Both bits are required for a device mapping: PCD alone leaves the page write-back, so a device writing a status register leaves a stale copy in cache and a poll loop never observes the update.

---

<a id="kmm_device_pdpt_slot"></a>

### `KMM_DEVICE_PDPT_SLOT`

`macro` | [headers/arch/x86/boot/bootdefs.h:244](../../headers/arch/x86/boot/bootdefs.h#L244)

```c
#define KMM_DEVICE_PDPT_SLOT
```

PDPT slot 4 is the kernel's device-MMIO window (see progs/minios_abi.h MINIOS_DEV_MMIO_VBASE).

Slot 0 is the boot identity map, slot 1 the user window, slot 3 the local APIC, and nothing else claims slot 4: it starts at 4 GB of virtual address, above every heap and every ring-3 window.

---

<a id="pt_pd_entries"></a>

### `PT_PD_ENTRIES`

`macro` | [headers/arch/x86/boot/bootdefs.h:245](../../headers/arch/x86/boot/bootdefs.h#L245)

```c
#define PT_PD_ENTRIES
```

---

<a id="pt_pd_entry_bytes"></a>

### `PT_PD_ENTRY_BYTES`

`macro` | [headers/arch/x86/boot/bootdefs.h:246](../../headers/arch/x86/boot/bootdefs.h#L246)

```c
#define PT_PD_ENTRY_BYTES
```

---

<a id="pt_pd_page_bytes"></a>

### `PT_PD_PAGE_BYTES`

`macro` | [headers/arch/x86/boot/bootdefs.h:247](../../headers/arch/x86/boot/bootdefs.h#L247)

```c
#define PT_PD_PAGE_BYTES
```

---

<a id="pt_pd_index_shift"></a>

### `PT_PD_INDEX_SHIFT`

`macro` | [headers/arch/x86/boot/bootdefs.h:248](../../headers/arch/x86/boot/bootdefs.h#L248)

```c
#define PT_PD_INDEX_SHIFT
```

---

<a id="pt_fill_start_index"></a>

### `PT_FILL_START_INDEX`

`macro` | [headers/arch/x86/boot/bootdefs.h:249](../../headers/arch/x86/boot/bootdefs.h#L249)

```c
#define PT_FILL_START_INDEX
```

---

<a id="pt_fill_start_addr"></a>

### `PT_FILL_START_ADDR`

`macro` | [headers/arch/x86/boot/bootdefs.h:250](../../headers/arch/x86/boot/bootdefs.h#L250)

```c
#define PT_FILL_START_ADDR
```

---

<a id="pt_fill_entries"></a>

### `PT_FILL_ENTRIES`

`macro` | [headers/arch/x86/boot/bootdefs.h:251](../../headers/arch/x86/boot/bootdefs.h#L251)

```c
#define PT_FILL_ENTRIES
```

---

<a id="pt_user_tables_addr"></a>

### `PT_USER_TABLES_ADDR`

`macro` | [headers/arch/x86/boot/bootdefs.h:271](../../headers/arch/x86/boot/bootdefs.h#L271)

```c
#define PT_USER_TABLES_ADDR
```

Dedicated zone for the kernel-installed 4 KB user-window page tables.

It must never share memory with the heap: the ramdisk data area is heap-backed and its size is discovered at boot, so page tables there could be overwritten by a later reservation.

It must ALSO never share memory with the kernel image. The kernel .bss is
~1.4 MB and grows, so a zone placed "between the kernel image and the
user window" (the historical 0x300000) sits right where the kernel's
own .bss lands once the image outgrows 2 MB. That collision silently
corrupted the page tables every time the shell wrote a terminal line
(the line buffer lived in the .bss tail), which is why user programs
crashed intermittently at "unmapped" addresses. The zone therefore
lives at 0x10000, BELOW the kernel link base (0x100000), inside the
boot staging buffer that is dead once the kernel is running: nothing in
the kernel image can ever reach it, in the plain build or under KASLR.
It is identity-mapped in every build (PT0 low half in KASLR, 2 MB PD
leaf in the plain build), so the PDEs can carry the same addresses the
kernel writes through.

---

<a id="pt_user_tables_bytes"></a>

### `PT_USER_TABLES_BYTES`

`macro` | [headers/arch/x86/boot/bootdefs.h:272](../../headers/arch/x86/boot/bootdefs.h#L272)

```c
#define PT_USER_TABLES_BYTES
```

---

<a id="kaslr_min_addr"></a>

### `KASLR_MIN_ADDR`

`macro` | [headers/arch/x86/boot/bootdefs.h:284](../../headers/arch/x86/boot/bootdefs.h#L284)

```c
#define KASLR_MIN_ADDR
```

KASLR: the kernel image is loaded at a random 2 MB-aligned physical base chosen from a 64-position window above the kernel heap, so the kernel's physical location varies on every boot.

The virtual base stays at the link-time address (0x100000); the loader maps it to the chosen physical base. The image (code + .bss) is mapped CONTIGUOUSLY over the whole virtual span [0x100000, KASLR_IMAGE_SPAN): PT0 covers the first MB and PT1 covers [0x200000, KASLR_IMAGE_SPAN) at 4 KB granularity, so a growing .bss can never spill onto the identity-mapped low-memory reserved zones. Keep KASLR_IMAGE_SPAN in sync with the kernel link layout: the image must end below the user window at USER_LOAD_BASE (0x400000).

---

<a id="kaslr_align_shift"></a>

### `KASLR_ALIGN_SHIFT`

`macro` | [headers/arch/x86/boot/bootdefs.h:285](../../headers/arch/x86/boot/bootdefs.h#L285)

```c
#define KASLR_ALIGN_SHIFT
```

---

<a id="kaslr_max_units"></a>

### `KASLR_MAX_UNITS`

`macro` | [headers/arch/x86/boot/bootdefs.h:286](../../headers/arch/x86/boot/bootdefs.h#L286)

```c
#define KASLR_MAX_UNITS
```

---

<a id="kaslr_img_off_1mb"></a>

### `KASLR_IMG_OFF_1MB`

`macro` | [headers/arch/x86/boot/bootdefs.h:287](../../headers/arch/x86/boot/bootdefs.h#L287)

```c
#define KASLR_IMG_OFF_1MB
```

---

<a id="kaslr_img_off_2mb"></a>

### `KASLR_IMG_OFF_2MB`

`macro` | [headers/arch/x86/boot/bootdefs.h:288](../../headers/arch/x86/boot/bootdefs.h#L288)

```c
#define KASLR_IMG_OFF_2MB
```

---

<a id="kaslr_image_span"></a>

### `KASLR_IMAGE_SPAN`

`macro` | [headers/arch/x86/boot/bootdefs.h:289](../../headers/arch/x86/boot/bootdefs.h#L289)

```c
#define KASLR_IMAGE_SPAN
```

---

<a id="cmos_index_port"></a>

### `CMOS_INDEX_PORT`

`macro` | [headers/arch/x86/boot/bootdefs.h:291](../../headers/arch/x86/boot/bootdefs.h#L291)

```c
#define CMOS_INDEX_PORT
```

---

<a id="cmos_data_port"></a>

### `CMOS_DATA_PORT`

`macro` | [headers/arch/x86/boot/bootdefs.h:292](../../headers/arch/x86/boot/bootdefs.h#L292)

```c
#define CMOS_DATA_PORT
```

---

<a id="cmos_nmi_disable"></a>

### `CMOS_NMI_DISABLE`

`macro` | [headers/arch/x86/boot/bootdefs.h:293](../../headers/arch/x86/boot/bootdefs.h#L293)

```c
#define CMOS_NMI_DISABLE
```

---

<a id="cmos_reg_extmem_lo"></a>

### `CMOS_REG_EXTMEM_LO`

`macro` | [headers/arch/x86/boot/bootdefs.h:295](../../headers/arch/x86/boot/bootdefs.h#L295)

```c
#define CMOS_REG_EXTMEM_LO
```

RAM above 16 MB in 64 KB units (PC BIOS / QEMU convention).

---

<a id="cmos_reg_extmem_hi"></a>

### `CMOS_REG_EXTMEM_HI`

`macro` | [headers/arch/x86/boot/bootdefs.h:296](../../headers/arch/x86/boot/bootdefs.h#L296)

```c
#define CMOS_REG_EXTMEM_HI
```

---

<a id="cmos_extmem_base"></a>

### `CMOS_EXTMEM_BASE`

`macro` | [headers/arch/x86/boot/bootdefs.h:297](../../headers/arch/x86/boot/bootdefs.h#L297)

```c
#define CMOS_EXTMEM_BASE
```

---

<a id="cmos_extmem_unit"></a>

### `CMOS_EXTMEM_UNIT`

`macro` | [headers/arch/x86/boot/bootdefs.h:298](../../headers/arch/x86/boot/bootdefs.h#L298)

```c
#define CMOS_EXTMEM_UNIT
```

---

<a id="cmos_reg_seconds"></a>

### `CMOS_REG_SECONDS`

`macro` | [headers/arch/x86/boot/bootdefs.h:299](../../headers/arch/x86/boot/bootdefs.h#L299)

```c
#define CMOS_REG_SECONDS
```

---

<a id="cmos_reg_minutes"></a>

### `CMOS_REG_MINUTES`

`macro` | [headers/arch/x86/boot/bootdefs.h:300](../../headers/arch/x86/boot/bootdefs.h#L300)

```c
#define CMOS_REG_MINUTES
```

---

<a id="cmos_reg_hours"></a>

### `CMOS_REG_HOURS`

`macro` | [headers/arch/x86/boot/bootdefs.h:301](../../headers/arch/x86/boot/bootdefs.h#L301)

```c
#define CMOS_REG_HOURS
```

---
