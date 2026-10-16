# Subsystem: mm

## kernel/mm/cow.c
- Doc: Docstring: kernel/mm/cow.c -- Copy-on-write fork support.
- Layer: utility
- Language: c
- Symbols:
  - `cow_entry_t` (struct, line 58)
  - `cow_slot` (function, line 68) `static unsigned long cow_slot(unsigned long phys)`
  - `cow_find` (function, line 73) `static int cow_find(unsigned long phys)`
  - `cow_remove` (function, line 85) `static void cow_remove(int idx)`
  - `cow_table_ensure` (function, line 98) `static void cow_table_ensure(void)`
  - `cow_rehash` (function, line 110) `static void cow_rehash(void)`
  - `cow_page_shared` (function, line 132) `int cow_page_shared(unsigned long phys)`
  - `cow_copy_demand` (function, line 166) `static void cow_copy_demand(unsigned long pcr3, unsigned long ccr3)`
  - `cow_track` (function, line 191) `static int cow_track(unsigned long phys)`
  - `cow_walk` (function, line 221) `static void cow_walk(unsigned long cr3, cow_walk_fn fn)`
  - `cow_fork_one` (function, line 255) `static void cow_fork_one(unsigned long pcr3, unsigned long va,
        volatile unsigned long *ppte)`
  - `CPU` (function, line 287) `* address space down on every other CPU (tlb_shootdown in do_fork_ex). */
unsigned long cow_fork_...`
  - `cow_resolve` (function, line 356) `int cow_resolve(unsigned long cr3, unsigned long va)`
  - `cow_release_window` (function, line 421) `void cow_release_window(unsigned long cr3)`
  - `cow_shared` (function, line 464) `int cow_shared(void)`
  - `alternative` (function, line 20) `* window is one instruction wide and the alternative (no CoW) is * documented, so the trade stands. */ #include...`
  - `private` (function, line 217) `* for every present page in a private (non-graphics) slot. Shared * graphics slots are never CoW: the compositor...`
  - `COW_BITS` (macro, line 34) `#define COW_BITS`
  - `COW_CAP` (macro, line 35) `#define COW_CAP`
  - `COW_MASK` (macro, line 36) `#define COW_MASK`
  - `COW_LOAD_MAX` (macro, line 37) `#define COW_LOAD_MAX`
  - `COW_TOMB_MAX` (macro, line 38) `#define COW_TOMB_MAX`
  - `COW_EMPTY` (macro, line 39) `#define COW_EMPTY`
  - `COW_TOMB` (macro, line 40) `#define COW_TOMB`
  - `COW_HASH_MUL` (macro, line 41) `#define COW_HASH_MUL`
  - `PT_USER_RO` (macro, line 46) `#define PT_USER_RO`
  - `PT_USER_RW_ENTRY` (macro, line 47) `#define PT_USER_RW_ENTRY`
  - `PT_PTE_RW` (macro, line 48) `#define PT_PTE_RW`
- Depends on: `headers/arch/x86/boot/bootdefs.h`, `headers/sched.h`, `headers/tlb.h`, `headers/vga_fb.h`

## kernel/mm/paging.c
- Doc: Page table management for the user window and per-process KPTI.
- Layer: utility
- Language: c
- Symbols:
  - `mm_page_aligned_alloc` (function, line 32) `static unsigned char *mm_page_aligned_alloc(unsigned size,
                                      ...`
  - `mm_setup_protections` (function, line 41) `void mm_setup_protections(void)`
  - `kmm_ensure_pt` (function, line 235) `static volatile unsigned long *kmm_ensure_pt(unsigned long phys)`
  - `coherent` (function, line 259) `* for memory a device reads and writes by DMA: a controller that is not cache
 * coherent (and an...`
  - `kmm_map_device` (function, line 296) `unsigned long kmm_map_device(unsigned long phys, unsigned long len)`
  - `mm_user_pte_update` (function, line 336) `void mm_user_pte_update(unsigned long vaddr, int exec, unsigned long cr3)`
  - `mm_user_set_exec` (function, line 356) `void mm_user_set_exec(unsigned long start, unsigned long end, unsigned long cr3)`
  - `pt_owned_index` (function, line 374) `static int pt_owned_index(unsigned long phys, unsigned long *byte, unsigned *bit)`
  - `pt_page_owned` (function, line 385) `int pt_page_owned(unsigned long phys)`
  - `pt_page_alloc` (function, line 392) `void *pt_page_alloc(void)`
  - `pt_page_free` (function, line 411) `void pt_page_free(void *ptr)`
  - `pt_clone_user` (function, line 420) `uint64_t pt_clone_user(uint64_t parent_cr3)`
  - `mt_shared_slot` (function, line 549) `static int mt_shared_slot(unsigned long pd_idx)`
  - `pt_clone_user_empty` (function, line 568) `unsigned long pt_clone_user_empty(void)`
  - `mm_user_ensure_page` (function, line 625) `int mm_user_ensure_page(unsigned long cr3, unsigned long va)`
  - `honest` (function, line 655) `* and invlpg keeps the local TLB honest (cross-CPU shootdown rides
 * the documented T5 follow-up...`
  - `mm_demand_pte` (function, line 704) `unsigned long mm_demand_pte(unsigned long prot)`
  - `mm_anon_frame` (function, line 715) `static int mm_anon_frame(unsigned long phys)`
  - `mm_anon_fault` (function, line 779) `int mm_anon_fault(unsigned long cr3, unsigned long va, int write)`
  - `mm_file_page_phys` (function, line 861) `unsigned long mm_file_page_phys(unsigned long cr3, unsigned long va)`
  - `mm_file_pte` (function, line 880) `static volatile unsigned long *mm_file_pte(unsigned long cr3,
        unsigned long va)`
  - `PTE` (function, line 1015) `* PTE (a cache page stays cached, but no stale writer may reach it).
 * Never allocates. */
void ...`
  - `mm_file_break` (function, line 1070) `int mm_file_break(unsigned long cr3, unsigned long va)`
  - `mm_copy_user_page` (function, line 1149) `int mm_copy_user_page(unsigned long dst_cr3, unsigned long src_cr3, unsigned long va)`
  - `pt_free_user` (function, line 1227) `void pt_free_user(uint64_t cr3)`
  - `tables` (function, line 1010) `* tables (munmap/mremap in caller context, under their mm_lock);`
  - `explicitly` (function, line 1011) `* teardown passes the dying window explicitly (zombie-exclusive, no * lock needed). unmap == 0 drops refs only...`
  - `_kernel_end` (variable, line 49) `extern char _kernel_end[];`
  - `mm_lock` (variable, line 696) `extern spinlock_t mm_lock;`
  - `KMM_DEVICE_MAX` (macro, line 200) `#define KMM_DEVICE_MAX`
  - `KMM_MAX_IDENTITY` (macro, line 204) `#define KMM_MAX_IDENTITY`
  - `KMM_DEVICE_FLAGS` (macro, line 211) `#define KMM_DEVICE_FLAGS`
  - `PT_OWNED_BYTES` (macro, line 371) `#define PT_OWNED_BYTES`
- Depends on: `headers/arch/x86/boot/bootdefs.h`, `headers/arch/x86/msr.h`, `headers/ldso.h`, `headers/minifs.h`, `headers/pcache.h`, `headers/tlb.h`, `headers/vga_fb.h`

## kernel/mm/swap.c
- Doc: Swap-out/swap-in for the user window (LZ4-compressed disk swap).
- Layer: utility
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
- Depends on: `headers/ide.h`, `headers/lz4_kernel.h`

## kernel/mm/tlb.c
- Doc: cross-CPU TLB shootdown (docs/spec/smp-sched.md, "TLB shootdown").
- Layer: utility
- Language: c
- Symbols:
  - `tlb_others_on` (function, line 36) `static int tlb_others_on(unsigned long cr3)`
  - `tlb_shootdown` (function, line 49) `void tlb_shootdown(unsigned long cr3)`
  - `tlb_shootdown_count` (function, line 71) `unsigned long tlb_shootdown_count(void)`
  - `tlb_shootdown_timeouts` (function, line 75) `unsigned long tlb_shootdown_timeouts(void)`
  - `TLB_SHOOT_SPIN_MAX` (macro, line 24) `#define TLB_SHOOT_SPIN_MAX`
- Depends on: `headers/sched.h`, `headers/smp.h`, `headers/spinlock.h`, `headers/tlb.h`
