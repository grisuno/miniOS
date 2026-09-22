# Subsystem: mm

## kernel/mm/paging.c
- Layer: utility
- Doc: paging.c - Page table management for the user window and per-process KPTI.
- Language: c
- Symbols:
  - `mm_page_aligned_alloc` (function, line 29) `static unsigned char *mm_page_aligned_alloc(unsigned size,
                                      ...`
  - `mm_setup_protections` (function, line 39) `void mm_setup_protections(void)`
  - `mm_user_pte_update` (function, line 159) `void mm_user_pte_update(unsigned long vaddr, int exec, unsigned long cr3)`
  - `mm_user_set_exec` (function, line 180) `void mm_user_set_exec(unsigned long start, unsigned long end, unsigned long cr3)`
  - `pt_page_alloc` (function, line 192) `void *pt_page_alloc(void)`
  - `pt_page_free` (function, line 202) `void pt_page_free(void *ptr)`
  - `pt_clone_user` (function, line 208) `uint64_t pt_clone_user(uint64_t parent_cr3)`
  - `mt_shared_slot` (function, line 322) `static int mt_shared_slot(unsigned long pd_idx)`
  - `pt_clone_user_empty` (function, line 341) `unsigned long pt_clone_user_empty(void)`
  - `mm_user_ensure_page` (function, line 398) `int mm_user_ensure_page(unsigned long cr3, unsigned long va)`
  - `mm_copy_user_page` (function, line 426) `int mm_copy_user_page(unsigned long dst_cr3, unsigned long src_cr3, unsigned long va)`
  - `pt_free_user` (function, line 498) `void pt_free_user(uint64_t cr3)`
  - `_kernel_end` (variable, line 47) `extern char _kernel_end[];`
  - `PT_ALLOC_HDR` (macro, line 190) `#define PT_ALLOC_HDR`
- Depends on: `headers/arch/x86/boot/bootdefs.h`, `headers/arch/x86/msr.h`, `headers/kernel.h`, `headers/vga_fb.h`

## kernel/mm/swap.c
- Layer: utility
- Doc: swap.c - Swap-out/swap-in for the user window (LZ4-compressed disk swap).
- Language: c
- Symbols:
  - `swap_ensure` (function, line 28) `static int swap_ensure(void)`
  - `swap_lba` (function, line 41) `static unsigned long swap_lba(void)`
  - `swap_out` (function, line 47) `int swap_out(unsigned long window_sz)`
  - `swap_in` (function, line 97) `int swap_in(void)`
  - `unwired` (function, line 7) `* * Currently unwired (the isolated-window spawn path superseded the * swap-out design);`
  - `SWAP_CHUNK_RAW` (macro, line 17) `#define SWAP_CHUNK_RAW`
  - `SWAP_CHUNK_CMP` (macro, line 18) `#define SWAP_CHUNK_CMP`
  - `SWAP_CHUNK_SECTORS` (macro, line 19) `#define SWAP_CHUNK_SECTORS`
  - `SWAP_HDR_SECTORS` (macro, line 20) `#define SWAP_HDR_SECTORS`
  - `SWAP_MAX_SECTORS` (macro, line 21) `#define SWAP_MAX_SECTORS`
  - `SWAP_MAGIC` (macro, line 22) `#define SWAP_MAGIC`
- Depends on: `headers/ide.h`, `headers/kernel.h`, `headers/lz4_kernel.h`
