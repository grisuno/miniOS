/* paging.c - Page table management for the user window and per-process KPTI.
 *
 * Extracted from kernel.c. Provides:
 *   mm_setup_protections  - boot-time user-window NX + framebuffer/backbuffer mapping
 *   mm_user_pte_update    - set/clear NX on a single 4 KB page
 *   mm_user_set_exec      - mark ELF segment pages as executable
 *   pt_page_alloc/free    - page-aligned allocator for page-table pages
 *   pt_clone_user         - build per-process PML4 (KPTI)
 *   pt_free_user          - release per-process page-table pages
 */

#include "kernel.h"
#include "bootdefs.h"
#include "vga_fb.h"
#include "arch/x86/msr.h"

/* ---- Page table helpers (from kernel.c, now shared via bootdefs.h) ---- */

/* Page-align a kmalloc'd region. The framebuffer/back-buffer PTEs are
 * built once per 4 KB page from the buffer's base address, and x86 masks
 * the low 12 bits of a PTE into flags, so a 16-byte-aligned `kmalloc`
 * pointer would make the first mapped page start at `buf & ~0xFFF` —
 * i.e. up to 4095 bytes BEFORE the buffer. A guest writing its frame to
 * the mapped VA then overwrote the heap chunk in front of the buffer
 * (a live KFILE), which is the corrupt-handle black screen. Over-
 * allocate one page and round the base up so VA offset 0 is buffer
 * offset 0. The raw pointer is deliberately untracked: both callers
 * allocate once at boot and never free. */
static unsigned char *mm_page_aligned_alloc(unsigned size,
                                            unsigned long *phys_out) {
    unsigned char *raw = (unsigned char *)kmalloc((unsigned long)size + 0x1000);
    unsigned char *buf;
    if (!raw) return 0;
    buf = (unsigned char *)(((unsigned long)raw + 0xFFF) & ~0xFFFUL);
    *phys_out = (unsigned long)buf;
    return buf;
}

void mm_setup_protections(void) {
    volatile unsigned long *pml4 = (volatile unsigned long *)PT_PML4_ADDR;
    volatile unsigned long *pdpt = (volatile unsigned long *)PT_PDPT_ADDR;
    volatile unsigned long *pd = (volatile unsigned long *)PT_PD_ADDR;
    unsigned long lo = USER_LOAD_BASE >> PT_PD_INDEX_SHIFT;
    unsigned long hi = (USER_LOAD_END - 1) >> PT_PD_INDEX_SHIFT;
    unsigned long i;

    extern char _kernel_end[];
    if ((unsigned long)_kernel_end > USER_LOAD_BASE) {
        kprintf("mm: kernel image reaches 0x%lx, must stay below 0x%lx\n",
                (unsigned long)_kernel_end, USER_LOAD_BASE);
        return;
    }
    if (hi - lo + 1 > PT_USER_TABLES_BYTES / 0x1000) {
        kprintf("mm: user window needs more page table space\n");
        return;
    }
    wrmsr(MSR_EFER, rdmsr(MSR_EFER) | EFER_NXE);
    pml4[0] |= (unsigned long)PT_FLAGS_USER;
    pdpt[0] |= (unsigned long)PT_FLAGS_USER;
    for (i = lo; i <= hi; i++) {
        unsigned long *pt = (unsigned long *)PT_USER_TABLES_ADDR +
                            (i - lo) * 0x1000 / sizeof(unsigned long);
        unsigned long phys = i << PT_PD_INDEX_SHIFT;
        unsigned long k;
        for (k = 0; k < PT_PD_ENTRIES; k++)
            pt[k] = (phys + k * 0x1000) | PT_USER_NX_ENTRY;
        pd[i] = ((unsigned long)pt) | PT_USER_ENTRY;
    }
    __asm__ volatile("mov %%cr3, %%rax; mov %%rax, %%cr3" ::: "rax", "memory");

    /* The framebuffer can span two 2 MB PD slots (1024x768x32 needs 3 MB),
     * so pages are mapped slot by slot instead of being capped at the end
     * of the first slot's page table; a cap would leave the bottom of a
     * tall screen unmapped. Every slot stays inside the user window (the
     * framebuffer lives in its reserved tail), whose tables are allocated
     * above. */
    {
        unsigned long fb_vaddr   = (unsigned long)FB_ADDR;
        unsigned long fb_bytes  = (unsigned long)fb_pitch * (unsigned long)fb_height;
        unsigned long fb_pages  = (fb_bytes + 0xFFF) >> 12;
        unsigned long p;
        if (fb_pages == 0) fb_pages = 1;
        for (p = 0; p < fb_pages; p++) {
            unsigned long va     = fb_vaddr + p * 0x1000;
            unsigned long pd_idx = va >> PT_PD_INDEX_SHIFT;
            unsigned long pt_off = (va & 0x1FFFFF) >> 12;
            unsigned long *pt;
            if (pd_idx < lo || pd_idx > hi) break;
            pt = (unsigned long *)PT_USER_TABLES_ADDR +
                 (pd_idx - lo) * 0x1000 / sizeof(unsigned long);
            pt[pt_off] = (fb_phys_base + p * 0x1000) | PT_USER_NX_ENTRY;
        }
    }

    {
        unsigned long bb_vaddr = DOOM_BACKBUF_ADDR;
        unsigned long bb_pd_idx = bb_vaddr >> PT_PD_INDEX_SHIFT;
        unsigned long bb_pt_off = (bb_vaddr & 0x1FFFFF) >> 12;
        unsigned long *bb_pt = (unsigned long *)PT_USER_TABLES_ADDR +
                               (bb_pd_idx - lo) * 0x1000 /
                               sizeof(unsigned long);
        unsigned char *buf;
        unsigned long phys;
        unsigned long k;
        buf = mm_page_aligned_alloc(DOOM_W * DOOM_H, &phys);
        if (buf == 0) return;
        if (phys & 0xFFFUL) {
            kprintf("mm: DOOM back-buffer not page aligned\n");
            return;
        }
        for (k = 0; k < (DOOM_W * DOOM_H + 0xFFF) >> 12; k++)
            bb_pt[bb_pt_off + k] = (phys + k * 0x1000) | PT_USER_NX_ENTRY;
    }

    {
        unsigned long bb_vaddr = NK_BACKBUF_ADDR;
        unsigned long bb_pd_idx = bb_vaddr >> PT_PD_INDEX_SHIFT;
        unsigned long bb_pt_off = (bb_vaddr & 0x1FFFFF) >> 12;
        unsigned long *bb_pt = (unsigned long *)PT_USER_TABLES_ADDR +
                               (bb_pd_idx - lo) * 0x1000 /
                               sizeof(unsigned long);
        unsigned char *buf;
        unsigned long phys;
        unsigned long k;
        buf = mm_page_aligned_alloc(NK_W * NK_H, &phys);
        if (buf == 0) return;
        if (phys & 0xFFFUL) {
            kprintf("mm: NK back-buffer not page aligned\n");
            return;
        }
        for (k = 0; k < (NK_W * NK_H + 0xFFF) >> 12; k++)
            bb_pt[bb_pt_off + k] = (phys + k * 0x1000) | PT_USER_NX_ENTRY;
    }
}

void mm_user_pte_update(unsigned long vaddr, int exec, unsigned long cr3) {
    unsigned long pd_phys;
    if (cr3 == 0) {
        pd_phys = PT_PD_ADDR;
    } else {
        volatile unsigned long *pml4 = (volatile unsigned long *)(cr3 & PT_ADDR_MASK);
        volatile unsigned long *pdpt = (volatile unsigned long *)(pml4[0] & PT_ADDR_MASK);
        pd_phys = pdpt[0] & PT_ADDR_MASK;
    }
    volatile unsigned long *pd = (volatile unsigned long *)pd_phys;
    unsigned long pd_idx = vaddr >> PT_PD_INDEX_SHIFT;
    unsigned long pde = pd[pd_idx];
    if (!(pde & PT_FLAGS_PRESENT_RW)) return;
    if (pde & PT_FLAGS_PS) return;
    volatile unsigned long *pt =
        (volatile unsigned long *)(pde & PT_ADDR_MASK);
    unsigned long pte_idx = (vaddr >> 12) & 0x1FF;
    if (exec) pt[pte_idx] &= ~(unsigned long)PT_FLAGS_NX;
    else      pt[pte_idx] |=  (unsigned long)PT_FLAGS_NX;
}

void mm_user_set_exec(unsigned long start, unsigned long end, unsigned long cr3) {
    unsigned long p;
    start &= ~0xFFFUL;
    end = ALIGN_UP(end, 0x1000);
    for (p = start; p < end; p += 0x1000) mm_user_pte_update(p, 1, cr3);
    __asm__ volatile("mov %%cr3, %%rax; mov %%rax, %%cr3" ::: "rax", "memory");
}

/* ---- Per-process page tables (KPTI) ---- */

#define PT_ALLOC_HDR  sizeof(void *)

void *pt_page_alloc(void) {
    void *raw = kmalloc(0x1000 + PT_ALLOC_HDR + 0xFFF);
    if (!raw) return 0;
    unsigned long addr = (unsigned long)raw + PT_ALLOC_HDR;
    unsigned long aligned = (addr + 0xFFF) & ~0xFFFUL;
    *((void **)(aligned - PT_ALLOC_HDR)) = raw;
    kmemset((void *)aligned, 0, 0x1000);
    return (void *)aligned;
}

void pt_page_free(void *ptr) {
    if (!ptr) return;
    void *raw = *((void **)((unsigned long)ptr - PT_ALLOC_HDR));
    kfree(raw);
}

uint64_t pt_clone_user(uint64_t parent_cr3) {
    (void)parent_cr3;
    volatile unsigned long *boot_pml4 = (volatile unsigned long *)PT_PML4_ADDR;
    volatile unsigned long *boot_pd   = (volatile unsigned long *)PT_PD_ADDR;

    volatile unsigned long *pml4 = (volatile unsigned long *)pt_page_alloc();
    if (!pml4) return 0;

    unsigned long i;
    for (i = 0; i < PT_PD_ENTRIES; i++)
        pml4[i] = boot_pml4[i];

    volatile unsigned long *pdpt = (volatile unsigned long *)pt_page_alloc();
    if (!pdpt) { pt_page_free((void *)pml4); return 0; }
    volatile unsigned long *boot_pdpt = (volatile unsigned long *)(boot_pml4[0] & PT_ADDR_MASK);
    for (i = 0; i < PT_PD_ENTRIES; i++)
        pdpt[i] = boot_pdpt[i];
    pml4[0] = (unsigned long)pdpt | (boot_pml4[0] & 0x7);

    volatile unsigned long *pd = (volatile unsigned long *)pt_page_alloc();
    if (!pd) { pt_page_free((void *)pdpt); pt_page_free((void *)pml4); return 0; }
    pdpt[0] = (unsigned long)pd | (boot_pdpt[0] & 0x7);
    pd[0] = boot_pd[0];
    pd[1] = boot_pd[1];
    {
        unsigned long hi_pd = (USER_LOAD_END - 1) >> PT_PD_INDEX_SHIFT;
        for (i = hi_pd + 1; i < PT_PD_ENTRIES; i++)
            pd[i] = boot_pd[i];
    }

    unsigned long lo = USER_LOAD_BASE >> PT_PD_INDEX_SHIFT;
    unsigned long hi = (USER_LOAD_END - 1) >> PT_PD_INDEX_SHIFT;
    volatile unsigned long *boot_user_pt_base =
        (volatile unsigned long *)PT_USER_TABLES_ADDR;
    for (i = lo; i <= hi; i++) {
        volatile unsigned long *pt = (volatile unsigned long *)pt_page_alloc();
        if (!pt) {
            unsigned long j;
            for (j = lo; j < i; j++) {
                unsigned long pte_addr = pd[j] & PT_ADDR_MASK;
                if (pte_addr) pt_page_free((void *)pte_addr);
            }
            pt_page_free((void *)pd);
            pt_page_free((void *)pdpt);
            pt_page_free((void *)pml4);
            return 0;
        }
        volatile unsigned long *boot_pt = boot_user_pt_base + (i - lo) * PT_PD_ENTRIES;
        unsigned long k;
        for (k = 0; k < PT_PD_ENTRIES; k++)
            pt[k] = boot_pt[k];
        pd[i] = ((unsigned long)pt) | PT_USER_ENTRY;
    }

    {
        /* The framebuffer can span two PD slots (see mm_setup_protections),
         * so every slot it touches is copied, not just its first page. */
        unsigned long fb_bytes =
            (unsigned long)fb_pitch * (unsigned long)fb_height;
        unsigned long fb_last =
            ((unsigned long)FB_ADDR + fb_bytes - 1) >> PT_PD_INDEX_SHIFT;
        unsigned long fb_pd_idx = (unsigned long)FB_ADDR >> PT_PD_INDEX_SHIFT;
        unsigned long bb_pd_idx = (unsigned long)DOOM_BACKBUF_ADDR >> PT_PD_INDEX_SHIFT;
        unsigned long nk_pd_idx = (unsigned long)NK_BACKBUF_ADDR >> PT_PD_INDEX_SHIFT;
        unsigned long idx;
        for (idx = fb_pd_idx; idx <= fb_last; idx++) {
            volatile unsigned long *boot_pt =
                (volatile unsigned long *)(boot_pd[idx] & PT_ADDR_MASK);
            volatile unsigned long *our_pt =
                (volatile unsigned long *)pt_page_alloc();
            unsigned long k;
            if (!our_pt || !boot_pt) continue;
            for (k = 0; k < PT_PD_ENTRIES; k++)
                our_pt[k] = boot_pt[k];
            pd[idx] = ((unsigned long)our_pt) | (boot_pd[idx] & 0x7);
        }
        {
            unsigned long indices[] = { bb_pd_idx, nk_pd_idx };
            unsigned long nidx = sizeof(indices) / sizeof(indices[0]);
            unsigned long j;
            for (j = 0; j < nidx; j++) {
                unsigned long bidx = indices[j];
                volatile unsigned long *boot_pt =
                    (volatile unsigned long *)(boot_pd[bidx] & PT_ADDR_MASK);
                volatile unsigned long *our_pt =
                    (volatile unsigned long *)pt_page_alloc();
                unsigned long k;
                if (!our_pt || !boot_pt) continue;
                for (k = 0; k < PT_PD_ENTRIES; k++)
                    our_pt[k] = boot_pt[k];
                pd[bidx] = ((unsigned long)our_pt) | (boot_pd[bidx] & 0x7);
            }
        }
    }

    return (uint64_t)(unsigned long)pml4;
}

/* ---- Multitask foundations (isolated user pages) ----
 *
 * The legacy path identity-maps the user window (VA == PA), so every
 * CR3 built by pt_clone_user aliases the same physical pages. That is
 * why only one ET_EXEC can run at a time today. The helpers below
 * build an EMPTY user window instead: fresh page tables with no user
 * data pages mapped, except the kernel-owned graphics slots (FB,
 * DOOM/NK back-buffers) which stay shared on purpose. Data pages come
 * from the kernel heap via pt_page_alloc, so each process owns its
 * bytes and switch_to's CR3 swap already isolates them. Pages are
 * freed by the extended pt_free_user below, which releases heap-owned
 * data pages in private slots and never touches identity pages or
 * the shared graphics slots. */

/* 1 when this PD slot holds kernel-shared graphics mappings. */
static int mt_shared_slot(unsigned long pd_idx) {
    unsigned long fb_bytes =
        (unsigned long)fb_pitch * (unsigned long)fb_height;
    unsigned long fb_first = (unsigned long)FB_ADDR >> PT_PD_INDEX_SHIFT;
    unsigned long fb_last =
        ((unsigned long)FB_ADDR + fb_bytes - 1) >> PT_PD_INDEX_SHIFT;
    unsigned long bb = (unsigned long)DOOM_BACKBUF_ADDR >> PT_PD_INDEX_SHIFT;
    unsigned long nk = (unsigned long)NK_BACKBUF_ADDR >> PT_PD_INDEX_SHIFT;
    if (pd_idx >= fb_first && pd_idx <= fb_last) return 1;
    if (pd_idx == bb) return 1;
    if (pd_idx == nk) return 1;
    return 0;
}

/* Fresh user window: kernel mappings copied, every user PT zeroed,
 * graphics slots re-shared from the boot tables. Returns PML4 phys
 * (usable as CR3), or 0 on OOM. No user data page is mapped. */
unsigned long pt_clone_user_empty(void) {
    volatile unsigned long *boot_pml4 = (volatile unsigned long *)PT_PML4_ADDR;
    volatile unsigned long *boot_pd   = (volatile unsigned long *)PT_PD_ADDR;
    volatile unsigned long *pml4 = (volatile unsigned long *)pt_page_alloc();
    unsigned long i;
    if (!pml4) return 0;
    for (i = 0; i < PT_PD_ENTRIES; i++)
        pml4[i] = boot_pml4[i];
    volatile unsigned long *pdpt = (volatile unsigned long *)pt_page_alloc();
    if (!pdpt) { pt_page_free((void *)pml4); return 0; }
    volatile unsigned long *boot_pdpt = (volatile unsigned long *)(boot_pml4[0] & PT_ADDR_MASK);
    for (i = 0; i < PT_PD_ENTRIES; i++)
        pdpt[i] = boot_pdpt[i];
    pml4[0] = (unsigned long)pdpt | (boot_pml4[0] & 0x7);
    volatile unsigned long *pd = (volatile unsigned long *)pt_page_alloc();
    if (!pd) { pt_page_free((void *)pdpt); pt_page_free((void *)pml4); return 0; }
    pdpt[0] = (unsigned long)pd | (boot_pdpt[0] & 0x7);
    pd[0] = boot_pd[0];
    pd[1] = boot_pd[1];
    {
        unsigned long hi_pd = (USER_LOAD_END - 1) >> PT_PD_INDEX_SHIFT;
        for (i = hi_pd + 1; i < PT_PD_ENTRIES; i++)
            pd[i] = boot_pd[i];
    }
    unsigned long lo = USER_LOAD_BASE >> PT_PD_INDEX_SHIFT;
    unsigned long hi = (USER_LOAD_END - 1) >> PT_PD_INDEX_SHIFT;
    for (i = lo; i <= hi; i++) {
        volatile unsigned long *pt = (volatile unsigned long *)pt_page_alloc();
        unsigned long j;
        if (!pt) {
            unsigned long k;
            for (k = lo; k < i; k++) {
                unsigned long a = pd[k] & PT_ADDR_MASK;
                if (a && !mt_shared_slot(k)) pt_page_free((void *)a);
            }
            pt_page_free((void *)pd);
            pt_page_free((void *)pdpt);
            pt_page_free((void *)pml4);
            return 0;
        }
        if (mt_shared_slot(i)) {
            volatile unsigned long *boot_pt =
                (volatile unsigned long *)(boot_pd[i] & PT_ADDR_MASK);
            if (boot_pt)
                for (j = 0; j < PT_PD_ENTRIES; j++) pt[j] = boot_pt[j];
            else
                for (j = 0; j < PT_PD_ENTRIES; j++) pt[j] = 0;
        } else {
            for (j = 0; j < PT_PD_ENTRIES; j++) pt[j] = 0;
        }
        pd[i] = ((unsigned long)pt) | PT_USER_ENTRY;
    }
    return (uint64_t)(unsigned long)pml4;
}

/* Ensure one 4 KB user page at va inside cr3 exists (heap-owned).
 * Returns 0 on success, -1 on OOM or when va leaves the user window. */
int mm_user_ensure_page(unsigned long cr3, unsigned long va) {
    volatile unsigned long *pml4;
    volatile unsigned long *pdpt;
    volatile unsigned long *pd;
    volatile unsigned long *pt;
    unsigned long pd_idx;
    unsigned long pte_idx;
    void *pg;
    if (cr3 == 0) return -1;
    if (va < USER_LOAD_BASE || va >= USER_LOAD_END) return -1;
    if (mt_shared_slot(va >> PT_PD_INDEX_SHIFT)) return -1;
    pml4 = (volatile unsigned long *)(cr3 & PT_ADDR_MASK);
    pdpt = (volatile unsigned long *)(pml4[0] & PT_ADDR_MASK);
    pd = (volatile unsigned long *)(pdpt[0] & PT_ADDR_MASK);
    pd_idx = va >> PT_PD_INDEX_SHIFT;
    if (!(pd[pd_idx] & PT_FLAGS_PRESENT_RW)) return -1;
    if (pd[pd_idx] & PT_FLAGS_PS) return -1;
    pt = (volatile unsigned long *)(pd[pd_idx] & PT_ADDR_MASK);
    pte_idx = (va >> 12) & 0x1FF;
    if (pt[pte_idx] & PT_FLAGS_PRESENT_RW) return 0;
    pg = pt_page_alloc();
    if (!pg) return -1;
    pt[pte_idx] = ((unsigned long)pg) | PT_USER_NX_ENTRY;
    return 0;
}

/* Copy one present user page from src_cr3 to the same VA in dst_cr3,
 * allocating the destination page. Used by fork-style clones. */
int mm_copy_user_page(unsigned long dst_cr3, unsigned long src_cr3, unsigned long va) {
    volatile unsigned long *spml4;
    volatile unsigned long *spdpt;
    volatile unsigned long *spd;
    volatile unsigned long *spt;
    unsigned long src_phys;
    unsigned long dst_phys;
    volatile unsigned long *dpml4;
    volatile unsigned long *dpdpt;
    volatile unsigned long *dpd;
    volatile unsigned long *dpt;
    unsigned long saved_cr3;
    if (mm_user_ensure_page(dst_cr3, va)) return -1;
    spml4 = (volatile unsigned long *)(src_cr3 & PT_ADDR_MASK);
    spdpt = (volatile unsigned long *)(spml4[0] & PT_ADDR_MASK);
    spd = (volatile unsigned long *)(spdpt[0] & PT_ADDR_MASK);
    spt = (volatile unsigned long *)((spd[va >> PT_PD_INDEX_SHIFT]) & PT_ADDR_MASK);
    src_phys = spt[(va >> 12) & 0x1FF] & PT_ADDR_MASK;
    if (!src_phys) return -1;
    dpml4 = (volatile unsigned long *)(dst_cr3 & PT_ADDR_MASK);
    dpdpt = (volatile unsigned long *)(dpml4[0] & PT_ADDR_MASK);
    dpd = (volatile unsigned long *)(dpdpt[0] & PT_ADDR_MASK);
    dpt = (volatile unsigned long *)((dpd[va >> PT_PD_INDEX_SHIFT]) & PT_ADDR_MASK);
    dst_phys = dpt[(va >> 12) & 0x1FF] & PT_ADDR_MASK;
    if (!dst_phys) return -1;
    __asm__ volatile("mov %%cr3, %0" : "=r"(saved_cr3));
    __asm__ volatile("cli");
    kmemcpy((void *)dst_phys, (void *)src_phys, 0x1000);
    __asm__ volatile("mov %0, %%cr3" :: "r"(saved_cr3) : "memory");
    __asm__ volatile("sti");
    return 0;
}

/* Release heap-owned user data pages of an isolated CR3. Identity
 * pages (phys below HEAP_BASE) and shared graphics slots are left
 * alone, so legacy shared CR3s free nothing here. */
static void pt_free_data_pages(uint64_t cr3) {
    volatile unsigned long *pml4 = (volatile unsigned long *)(cr3 & PT_ADDR_MASK);
    volatile unsigned long *pdpt;
    volatile unsigned long *pd;
    unsigned long lo = USER_LOAD_BASE >> PT_PD_INDEX_SHIFT;
    unsigned long hi = (USER_LOAD_END - 1) >> PT_PD_INDEX_SHIFT;
    unsigned long i;
    if (!pml4) return;
    if (!(pml4[0] & PT_FLAGS_PRESENT_RW)) return;
    pdpt = (volatile unsigned long *)(pml4[0] & PT_ADDR_MASK);
    if (!(pdpt[0] & PT_FLAGS_PRESENT_RW)) return;
    if (pdpt[0] & PT_FLAGS_PS) return;
    pd = (volatile unsigned long *)(pdpt[0] & PT_ADDR_MASK);
    for (i = lo; i <= hi; i++) {
        volatile unsigned long *pt;
        unsigned long k;
        if (mt_shared_slot(i)) continue;
        if (!(pd[i] & PT_FLAGS_PRESENT_RW)) continue;
        if (pd[i] & PT_FLAGS_PS) continue;
        pt = (volatile unsigned long *)(pd[i] & PT_ADDR_MASK);
        if (!pt) continue;
        for (k = 0; k < PT_PD_ENTRIES; k++) {
            unsigned long pte = pt[k];
            unsigned long phys;
            void *raw;
            if (!(pte & PT_FLAGS_PRESENT_RW)) continue;
            phys = pte & PT_ADDR_MASK;
            if (phys < HEAP_BASE || phys >= HEAP_BASE + HEAP_SIZE) continue;
            raw = *((void **)(phys - PT_ALLOC_HDR));
            if ((unsigned long)raw < HEAP_BASE ||
                (unsigned long)raw >= HEAP_BASE + HEAP_SIZE) continue;
            kfree(raw);
        }
    }
}

void pt_free_user(uint64_t cr3) {
    if (cr3 == 0) return;
    pt_free_data_pages(cr3);
    volatile unsigned long *pml4 = (volatile unsigned long *)(cr3 & PT_ADDR_MASK);
    volatile unsigned long *pdpt = (volatile unsigned long *)(pml4[0] & PT_ADDR_MASK);
    if (!pdpt) return;
    volatile unsigned long *pd = (volatile unsigned long *)(pdpt[0] & PT_ADDR_MASK);

    unsigned long lo = USER_LOAD_BASE >> PT_PD_INDEX_SHIFT;
    unsigned long hi = (USER_LOAD_END - 1) >> PT_PD_INDEX_SHIFT;
    unsigned long i;
    if (pd) {
        for (i = lo; i <= hi; i++) {
            if ((pd[i] & PT_FLAGS_PRESENT_RW) && !(pd[i] & PT_FLAGS_PS)) {
                unsigned long pt_addr = pd[i] & PT_ADDR_MASK;
                if (pt_addr) pt_page_free((void *)pt_addr);
            }
        }
        unsigned long fb_idx = (unsigned long)FB_ADDR >> PT_PD_INDEX_SHIFT;
        unsigned long fb_bytes =
            (unsigned long)fb_pitch * (unsigned long)fb_height;
        unsigned long fb_last =
            ((unsigned long)FB_ADDR + fb_bytes - 1) >> PT_PD_INDEX_SHIFT;
        unsigned long bb_idx = (unsigned long)DOOM_BACKBUF_ADDR >> PT_PD_INDEX_SHIFT;
        unsigned long nk_idx = (unsigned long)NK_BACKBUF_ADDR >> PT_PD_INDEX_SHIFT;
        unsigned long extra[] = { bb_idx, nk_idx };
        unsigned long ne = sizeof(extra) / sizeof(extra[0]);
        unsigned long j;
        unsigned long idx;
        for (idx = fb_idx; idx <= fb_last; idx++) {
            if (idx >= lo && idx <= hi) continue;
            if ((pd[idx] & PT_FLAGS_PRESENT_RW) && !(pd[idx] & PT_FLAGS_PS)) {
                unsigned long pt_addr = pd[idx] & PT_ADDR_MASK;
                if (pt_addr) pt_page_free((void *)pt_addr);
            }
        }
        for (j = 0; j < ne; j++) {
            idx = extra[j];
            if (idx >= lo && idx <= hi) continue;
            if ((pd[idx] & PT_FLAGS_PRESENT_RW) && !(pd[idx] & PT_FLAGS_PS)) {
                unsigned long pt_addr = pd[idx] & PT_ADDR_MASK;
                if (pt_addr) pt_page_free((void *)pt_addr);
            }
        }
        pt_page_free((void *)pd);
    }
    if (pdpt) pt_page_free((void *)pdpt);
    pt_page_free((void *)pml4);
}
