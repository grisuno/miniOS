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

    {
        unsigned long fb_vaddr   = (unsigned long)FB_ADDR;
        unsigned long fb_pd_idx  = fb_vaddr >> PT_PD_INDEX_SHIFT;
        unsigned long fb_pt_off  = (fb_vaddr & 0x1FFFFF) >> 12;
        unsigned long *fb_pt     = (unsigned long *)PT_USER_TABLES_ADDR +
                                   (fb_pd_idx - lo) * 0x1000 /
                                   sizeof(unsigned long);
        unsigned long fb_bytes  = (unsigned long)fb_pitch * (unsigned long)fb_height;
        unsigned long fb_pages  = (fb_bytes + 0xFFF) >> 12;
        unsigned long k;
        if (fb_pages == 0) fb_pages = 1;
        if (fb_pages > PT_PD_ENTRIES - fb_pt_off)
            fb_pages = PT_PD_ENTRIES - fb_pt_off;
        for (k = 0; k < fb_pages; k++)
            fb_pt[fb_pt_off + k] = (fb_phys_base + k * 0x1000) | PT_USER_NX_ENTRY;
    }

    {
        unsigned long bb_vaddr = DOOM_BACKBUF_ADDR;
        unsigned long bb_pd_idx = bb_vaddr >> PT_PD_INDEX_SHIFT;
        unsigned long bb_pt_off = (bb_vaddr & 0x1FFFFF) >> 12;
        unsigned long *bb_pt = (unsigned long *)PT_USER_TABLES_ADDR +
                               (bb_pd_idx - lo) * 0x1000 /
                               sizeof(unsigned long);
        unsigned char *buf = (unsigned char *)kmalloc(DOOM_W * DOOM_H);
        unsigned long phys;
        unsigned long k;
        if (buf == 0) return;
        phys = (unsigned long)buf;
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
        unsigned char *buf = (unsigned char *)kmalloc(NK_W * NK_H);
        unsigned long phys;
        unsigned long k;
        if (buf == 0) return;
        phys = (unsigned long)buf;
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
        unsigned long fb_pd_idx = (unsigned long)FB_ADDR >> PT_PD_INDEX_SHIFT;
        unsigned long bb_pd_idx = (unsigned long)DOOM_BACKBUF_ADDR >> PT_PD_INDEX_SHIFT;
        unsigned long nk_pd_idx = (unsigned long)NK_BACKBUF_ADDR >> PT_PD_INDEX_SHIFT;
        unsigned long indices[] = { fb_pd_idx, bb_pd_idx, nk_pd_idx };
        unsigned long nidx = sizeof(indices) / sizeof(indices[0]);
        unsigned long j;
        for (j = 0; j < nidx; j++) {
            unsigned long idx = indices[j];
            volatile unsigned long *boot_pt =
                (volatile unsigned long *)(boot_pd[idx] & PT_ADDR_MASK);
            volatile unsigned long *our_pt =
                (volatile unsigned long *)pt_page_alloc();
            if (!our_pt || !boot_pt) continue;
            unsigned long k;
            for (k = 0; k < PT_PD_ENTRIES; k++)
                our_pt[k] = boot_pt[k];
            pd[idx] = ((unsigned long)our_pt) | (boot_pd[idx] & 0x7);
        }
    }

    return (uint64_t)(unsigned long)pml4;
}

void pt_free_user(uint64_t cr3) {
    if (cr3 == 0) return;
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
        unsigned long bb_idx = (unsigned long)DOOM_BACKBUF_ADDR >> PT_PD_INDEX_SHIFT;
        unsigned long nk_idx = (unsigned long)NK_BACKBUF_ADDR >> PT_PD_INDEX_SHIFT;
        unsigned long extra[] = { fb_idx, bb_idx, nk_idx };
        unsigned long ne = sizeof(extra) / sizeof(extra[0]);
        unsigned long j;
        for (j = 0; j < ne; j++) {
            unsigned long idx = extra[j];
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
