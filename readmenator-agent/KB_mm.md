# Subsystem: mm

## kernel/mm/paging.c
- Layer: utility
- Doc: paging.c - Page table management for the user window and per-process KPTI.
- Language: c
- Symbols:
  - `mm_setup_protections` (function, line 18) `void mm_setup_protections(void)`
  - `mm_user_pte_update` (function, line 100) `void mm_user_pte_update(unsigned long vaddr, int exec, unsigned long cr3)`
  - `mm_user_set_exec` (function, line 121) `void mm_user_set_exec(unsigned long start, unsigned long end, unsigned long cr3)`
  - `pt_page_alloc` (function, line 133) `void *pt_page_alloc(void)`
  - `pt_page_free` (function, line 143) `void pt_page_free(void *ptr)`
  - `pt_clone_user` (function, line 149) `uint64_t pt_clone_user(uint64_t parent_cr3)`
  - `pt_free_user` (function, line 227) `void pt_free_user(uint64_t cr3)`
  - `PT_ALLOC_HDR` (macro, line 131)

## kernel/mm/swap.c
- Layer: utility
- Doc: swap.c - Swap-out/swap-in for the user window (LZ4-compressed disk swap).
- Language: c
- Symbols:
  - `swap_lba` (function, line 23) `static unsigned long swap_lba(void)`
  - `swap_out` (function, line 29) `int swap_out(unsigned long window_sz)`
  - `swap_in` (function, line 78) `int swap_in(void)`
  - `SWAP_CHUNK_RAW` (macro, line 14)
  - `SWAP_CHUNK_SECTORS` (macro, line 16)
  - `SWAP_HDR_SECTORS` (macro, line 17)
  - `SWAP_MAX_SECTORS` (macro, line 18)
  - `SWAP_MAGIC` (macro, line 19)
