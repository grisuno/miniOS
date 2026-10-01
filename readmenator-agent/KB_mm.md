# Subsystem: mm

## kernel/mm/cow.c
- Layer: utility
- Doc: Docstring: kernel/mm/cow.c -- Copy-on-write fork support.
- Language: c
- Symbols:
  - `cow_entry_t` (struct, line 45)
  - `cow_find` (function, line 53) `static int cow_find(unsigned long phys)`
  - `cow_page_shared` (function, line 65) `int cow_page_shared(unsigned long phys)`
  - `cow_track` (function, line 75) `static int cow_track(unsigned long phys)`
  - `cow_walk` (function, line 97) `static void cow_walk(unsigned long cr3, cow_walk_fn fn)`
  - `cow_fork_one` (function, line 131) `static void cow_fork_one(unsigned long pcr3, unsigned long va,
        volatile unsigned long *ppte)`
  - `published` (function, line 161) `* with nothing published (the half-built window is freed). The caller
 * flushes the parent TLB a...`
  - `cow_resolve` (function, line 191) `int cow_resolve(unsigned long cr3, unsigned long va)`
  - `cow_release_window` (function, line 254) `void cow_release_window(unsigned long cr3)`
  - `cow_shared` (function, line 292) `int cow_shared(void)`
  - `alternative` (function, line 20) `* window is one instruction wide and the alternative (no CoW) is * documented, so the trade stands. */ #include "kernel.h" #include "bootdefs.h" #include "vga_fb.h" #include "sched.h" #define COW_MAX `
  - `private` (function, line 93) `* for every present page in a private (non-graphics) slot. Shared * graphics slots are never CoW: the compositor owns them. */ typedef void (*cow_walk_fn)(unsigned long cr3, unsigned long va, volatile`
  - `COW_MAX` (macro, line 28) `#define COW_MAX`
  - `PT_USER_RO` (macro, line 33) `#define PT_USER_RO`
  - `PT_USER_RW_ENTRY` (macro, line 34) `#define PT_USER_RW_ENTRY`
  - `PT_PTE_RW` (macro, line 35) `#define PT_PTE_RW`
- Depends on: `headers/arch/x86/boot/bootdefs.h`, `headers/kernel.h`, `headers/sched.h`, `headers/vga_fb.h`

## kernel/mm/paging.c
- Layer: utility
- Doc: paging.c - Page table management for the user window and per-process KPTI.
- Language: c
- Symbols:
  - `mm_page_aligned_alloc` (function, line 31) `static unsigned char *mm_page_aligned_alloc(unsigned size,
                                      ...`
  - `mm_setup_protections` (function, line 40) `void mm_setup_protections(void)`
  - `mm_user_pte_update` (function, line 160) `void mm_user_pte_update(unsigned long vaddr, int exec, unsigned long cr3)`
  - `mm_user_set_exec` (function, line 181) `void mm_user_set_exec(unsigned long start, unsigned long end, unsigned long cr3)`
  - `pt_page_alloc` (function, line 193) `void *pt_page_alloc(void)`
  - `pt_page_free` (function, line 203) `void pt_page_free(void *ptr)`
  - `pt_clone_user` (function, line 209) `uint64_t pt_clone_user(uint64_t parent_cr3)`
  - `mt_shared_slot` (function, line 338) `static int mt_shared_slot(unsigned long pd_idx)`
  - `pt_clone_user_empty` (function, line 357) `unsigned long pt_clone_user_empty(void)`
  - `mm_user_ensure_page` (function, line 414) `int mm_user_ensure_page(unsigned long cr3, unsigned long va)`
  - `honest` (function, line 444) `* and invlpg keeps the local TLB honest (cross-CPU shootdown rides
 * the documented T5 follow-up...`
  - `mm_file_page_phys` (function, line 495) `unsigned long mm_file_page_phys(unsigned long cr3, unsigned long va)`
  - `mm_file_pte` (function, line 514) `static volatile unsigned long *mm_file_pte(unsigned long cr3,
        unsigned long va)`
  - `mm_file_range_release` (function, line 649) `void mm_file_range_release(unsigned long cr3, unsigned long base,
        unsigned long len, int ...`
  - `mm_file_break` (function, line 697) `int mm_file_break(unsigned long cr3, unsigned long va)`
  - `mm_copy_user_page` (function, line 776) `int mm_copy_user_page(unsigned long dst_cr3, unsigned long src_cr3, unsigned long va)`
  - `pt_free_user` (function, line 853) `void pt_free_user(uint64_t cr3)`
  - `tables` (function, line 644) `* tables (munmap/mremap in caller context, under their mm_lock);`
  - `explicitly` (function, line 645) `* teardown passes the dying window explicitly (zombie-exclusive, no * lock needed). unmap == 0 drops refs only (teardown, whose tables * die next);`
  - `_kernel_end` (variable, line 48) `extern char _kernel_end[];`
  - `mm_lock` (variable, line 485) `extern spinlock_t mm_lock;`
  - `PT_ALLOC_HDR` (macro, line 191) `#define PT_ALLOC_HDR`
- Depends on: `headers/arch/x86/boot/bootdefs.h`, `headers/arch/x86/msr.h`, `headers/kernel.h`, `headers/ldso.h`, `headers/minifs.h`, `headers/pcache.h`, `headers/vga_fb.h`

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
