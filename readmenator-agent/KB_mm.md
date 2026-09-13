# Subsystem: mm

## kernel/mm/paging.c
- Layer: utility
- Doc: paging.c - Page table management for the user window and per-process KPTI.
- Language: c
- Symbols:
  - `mm_page_aligned_alloc` (function, line 29) `static unsigned char *mm_page_aligned_alloc(unsigned size,
                                      ...`
  - `mm_setup_protections` (function, line 38) `void mm_setup_protections(void)`
  - `mm_user_pte_update` (function, line 135) `void mm_user_pte_update(unsigned long vaddr, int exec, unsigned long cr3)`
  - `mm_user_set_exec` (function, line 156) `void mm_user_set_exec(unsigned long start, unsigned long end, unsigned long cr3)`
  - `pt_page_alloc` (function, line 168) `void *pt_page_alloc(void)`
  - `pt_page_free` (function, line 178) `void pt_page_free(void *ptr)`
  - `pt_clone_user` (function, line 184) `uint64_t pt_clone_user(uint64_t parent_cr3)`
  - `mt_shared_slot` (function, line 298) `static int mt_shared_slot(unsigned long pd_idx)`
  - `pt_clone_user_empty` (function, line 315) `unsigned long pt_clone_user_empty(void)`
  - `mm_user_ensure_page` (function, line 372) `int mm_user_ensure_page(unsigned long cr3, unsigned long va)`
  - `mm_copy_user_page` (function, line 400) `int mm_copy_user_page(unsigned long dst_cr3, unsigned long src_cr3, unsigned long va)`
  - `pt_free_user` (function, line 471) `void pt_free_user(uint64_t cr3)`
  - `kprintf` (function, line 49) `kprintf("mm: kernel image reaches 0x%lx, must stay below 0x%lx\n", (unsigned long)_kernel_end, USER_LOAD_BASE);`
  - `wrmsr` (function, line 57) `wrmsr(MSR_EFER, rdmsr(MSR_EFER) | EFER_NXE);`
  - `kmemset` (function, line 175) `kmemset((void *)aligned, 0, 0x1000);`
  - `kfree` (function, line 182) `kfree(raw);`
  - `volatile` (function, line 425) `__asm__ volatile("mov %%cr3, %0" : "=r"(saved_cr3));`
  - `kmemcpy` (function, line 427) `kmemcpy((void *)dst_phys, (void *)src_phys, 0x1000);`
  - `pt_free_data_pages` (function, line 474) `pt_free_data_pages(cr3);`
  - `_kernel_end` (variable, line 46) `extern char _kernel_end[];`
  - `PT_ALLOC_HDR` (macro, line 166) `#define PT_ALLOC_HDR`
- Depends on: `arch/x86/boot/bootdefs.h`, `arch/x86/msr.h`, `kernel.h`, `vga_fb.h`

## kernel/mm/swap.c
- Layer: utility
- Doc: swap.c - Swap-out/swap-in for the user window (LZ4-compressed disk swap).
- Language: c
- Symbols:
  - `swap_lba` (function, line 23) `static unsigned long swap_lba(void)`
  - `swap_out` (function, line 29) `int swap_out(unsigned long window_sz)`
  - `swap_in` (function, line 78) `int swap_in(void)`
  - `kmemcpy` (function, line 42) `kmemcpy(swap_buf_raw, (void *)(USER_LOAD_BASE + off), raw_sz);`
  - `kmemset` (function, line 72) `kmemset(hdr + 3, 0, IDE_SECTOR_SIZE - 12);`
  - `SWAP_CHUNK_RAW` (macro, line 14) `#define SWAP_CHUNK_RAW`
  - `SWAP_CHUNK_SECTORS` (macro, line 16) `#define SWAP_CHUNK_SECTORS`
  - `SWAP_HDR_SECTORS` (macro, line 17) `#define SWAP_HDR_SECTORS`
  - `SWAP_MAX_SECTORS` (macro, line 18) `#define SWAP_MAX_SECTORS`
  - `SWAP_MAGIC` (macro, line 19) `#define SWAP_MAGIC`
- Depends on: `ide.h`, `kernel.h`, `lz4_kernel.h`
