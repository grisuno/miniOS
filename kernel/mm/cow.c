/** Docstring: kernel/mm/cow.c -- Copy-on-write fork support.
 *
 * Bounded Context (DDD): page sharing between a fork parent and child.
 * Owns the phys-to-refcount table, the fork-time window share
 * (same phys mapped read-only in both windows) and the fault-time
 * resolve (first write gets a private copy, or a permission upgrade
 * when the last sharer left). The #PF handler in kernel/sched.c owns
 * the trap decision; this file never sees a trap frame, only
 * (window, address) pairs. pt_free_user owns reclamation and calls
 * cow_release_window first, so a freed window never strands a ref.
 *
 * Degrade, never fail: a full table or an OOM page makes that one
 * page eager-copied (same bytes, no sharing), so fork succeeds with
 * less sharing instead of refusing. Counts shared pages out for the
 * `mem` builtin... (no counter yet: cow_shared() reports live refs).
 *
 * Fault-context discipline: cow_resolve allocates through
 * pt_page_alloc (dlmalloc-backed). A write fault landing inside a
 * dlmalloc critical section could self-deadlock on that lock; the
 * window is one instruction wide and the alternative (no CoW) is
 * documented, so the trade stands. */

#include "kernel.h"
#include "bootdefs.h"
#include "vga_fb.h"
#include "sched.h"

#define COW_MAX 512
/* RO share entries preserve the parent's NX bit (flags): forcing NX
 * would fault instruction fetch in the child on executable pages,
 * and the resolver only upgrades writes, so a forced-NX fetch fault
 * would loop forever. */
#define PT_USER_RO ((unsigned long)(0x001 | PT_FLAGS_USER))
#define PT_USER_RW_ENTRY ((unsigned long)(0x001 | PT_FLAGS_USER | PT_PTE_RW))
#define PT_PTE_RW ((unsigned long)0x002)

/* Table lock: fork's walk and fault-time resolves serialize here. Leaf
 * (never nested, never held across yields); resolve allocates under it
 * (dlmalloc owns its own lock, no cycle: nothing behind dlmalloc takes
 * cow_lock). Fork runs cli so a fault cannot re-enter it on the same
 * CPU; two threads faulting one page resolve atomically, so the second
 * sees ref 1 and upgrades instead of double-copying. */
static spinlock_t cow_lock = SPINLOCK_INIT;

typedef struct {
    unsigned long phys;
    int ref;
} cow_entry_t;

static cow_entry_t cow_tab[COW_MAX];
static int cow_drops;

static int cow_find(unsigned long phys) {
    int i;
    for (i = 0; i < COW_MAX; i++)
        if (cow_tab[i].ref > 0 && cow_tab[i].phys == phys) return i;
    return -1;
}

/** Docstring: Share one phys page: bump its refcount, or install it.
 * Returns 0 shared, -1 when the table is full (caller eager-copies). */
static int cow_track(unsigned long phys) {
    int i = cow_find(phys);
    if (i >= 0) {
        cow_tab[i].ref++;
        return 0;
    }
    for (i = 0; i < COW_MAX; i++) {
        if (cow_tab[i].ref <= 0) {
            cow_tab[i].phys = phys;
            cow_tab[i].ref = 2;
            return 0;
        }
    }
    cow_drops++;
    return -1;
}

/** Docstring: Walk one window's user data PTEs. Calls fn(cr3, va, pte)
 * for every present page in a private (non-graphics) slot. Shared
 * graphics slots are never CoW: the compositor owns them. */
typedef void (*cow_walk_fn)(unsigned long cr3, unsigned long va,
        volatile unsigned long *pte_slot);
static void cow_walk(unsigned long cr3, cow_walk_fn fn) {
    volatile unsigned long *pml4 = (volatile unsigned long *)(cr3 & PT_ADDR_MASK);
    volatile unsigned long *pdpt;
    volatile unsigned long *pd;
    unsigned long lo = USER_LOAD_BASE >> PT_PD_INDEX_SHIFT;
    unsigned long hi = (USER_LOAD_END - 1) >> PT_PD_INDEX_SHIFT;
    unsigned long i, k;
    unsigned long fb_first = (unsigned long)FB_ADDR >> PT_PD_INDEX_SHIFT;
    unsigned long fb_bytes = (unsigned long)fb_pitch * (unsigned long)fb_height;
    unsigned long fb_last = ((unsigned long)FB_ADDR + fb_bytes - 1) >> PT_PD_INDEX_SHIFT;
    if (!pml4 || !(pml4[0] & PT_FLAGS_PRESENT_RW)) return;
    pdpt = (volatile unsigned long *)(pml4[0] & PT_ADDR_MASK);
    if (!(pdpt[0] & PT_FLAGS_PRESENT_RW) || (pdpt[0] & PT_FLAGS_PS)) return;
    pd = (volatile unsigned long *)(pdpt[0] & PT_ADDR_MASK);
    for (i = lo; i <= hi; i++) {
        volatile unsigned long *pt;
        if (!(pd[i] & PT_FLAGS_PRESENT_RW) || (pd[i] & PT_FLAGS_PS)) continue;
        if (i >= fb_first && i <= fb_last) continue;
        if (i == ((unsigned long)DOOM_BACKBUF_ADDR >> PT_PD_INDEX_SHIFT)) continue;
        if (i == ((unsigned long)NK_BACKBUF_ADDR >> PT_PD_INDEX_SHIFT)) continue;
        if (i == ((unsigned long)NK_RGB_ADDR >> PT_PD_INDEX_SHIFT)) continue;
        pt = (volatile unsigned long *)(pd[i] & PT_ADDR_MASK);
        for (k = 0; k < PT_PD_ENTRIES; k++) {
            if (!(pt[k] & 0x001)) continue;
            if (!(pt[k] & PT_FLAGS_USER)) continue;
            fn(cr3, (i << PT_PD_INDEX_SHIFT) + (k << 12), &pt[k]);
        }
    }
}

static unsigned long cow_fork_parent;
static unsigned long cow_fork_child;
static int cow_fork_failed;

static void cow_fork_one(unsigned long pcr3, unsigned long va,
        volatile unsigned long *ppte) {
    unsigned long phys;
    unsigned long flags;
    volatile unsigned long *cpml4;
    volatile unsigned long *cpdpt;
    volatile unsigned long *cpd;
    volatile unsigned long *cpt;
    (void)pcr3;
    if (cow_fork_failed) return;
    phys = *ppte & PT_ADDR_MASK;
    if (!phys) return;
    flags = *ppte & (unsigned long)PT_FLAGS_NX;
    if (cow_track(phys) == 0) {
        *ppte = phys | PT_USER_RO | flags;
        cpml4 = (volatile unsigned long *)(cow_fork_child & PT_ADDR_MASK);
        cpdpt = (volatile unsigned long *)(cpml4[0] & PT_ADDR_MASK);
        cpd = (volatile unsigned long *)(cpdpt[0] & PT_ADDR_MASK);
        cpt = (volatile unsigned long *)((cpd[va >> PT_PD_INDEX_SHIFT]) & PT_ADDR_MASK);
        if (!cpt) { cow_fork_failed = 1; return; }
        cpt[(va >> 12) & 0x1FF] = phys | PT_USER_RO | flags;
        return;
    }
    if (mm_copy_user_page(cow_fork_child, cow_fork_parent, va) != 0)
        cow_fork_failed = 1;
}

/** Docstring: Build a CoW child window from a parent window. Present
 * data pages are shared read-only (both sides); a full table or OOM
 * degrades that page to an eager copy. Returns the child CR3, or 0
 * with nothing published (the half-built window is freed). The caller
 * flushes the parent TLB after (its PTEs changed under it). */
unsigned long cow_fork_window(unsigned long parent_cr3) {
    unsigned long child;
    unsigned long saved;
    if (!parent_cr3) return 0;
    child = pt_clone_user_empty();
    if (!child) return 0;
    cow_fork_parent = parent_cr3;
    cow_fork_child = child;
    cow_fork_failed = 0;
    __asm__ volatile("mov %%cr3, %0" : "=r"(saved));
    __asm__ volatile("cli");
    spin_lock(&cow_lock);
    cow_walk(parent_cr3, cow_fork_one);
    spin_unlock(&cow_lock);
    __asm__ volatile("mov %0, %%cr3" :: "r"(saved) : "memory");
    __asm__ volatile("sti");
    if (cow_fork_failed) {
        cow_release_window(child);
        pt_free_user(child);
        return 0;
    }
    return child;
}

/** Docstring: Resolve a write fault on a CoW page: last sharer gets a
 * permission upgrade, otherwise the faulting window gets a private
 * copy. invlpg keeps the TLB honest. Returns 0 resolved (resume),
 * -1 not a CoW page (existing fault handling runs). */
int cow_resolve(unsigned long cr3, unsigned long va) {
    volatile unsigned long *pml4;
    volatile unsigned long *pdpt;
    volatile unsigned long *pd;
    volatile unsigned long *pt;
    unsigned long pte;
    unsigned long phys;
    unsigned long nx;
    int idx;
    void *pg;
    if (!cr3) return -1;
    va &= ~0xFFFUL;
    if (va < USER_LOAD_BASE || va >= USER_LOAD_END) return -1;
    pml4 = (volatile unsigned long *)(cr3 & PT_ADDR_MASK);
    if (!(pml4[0] & PT_FLAGS_PRESENT_RW)) return -1;
    pdpt = (volatile unsigned long *)(pml4[0] & PT_ADDR_MASK);
    if (!(pdpt[0] & PT_FLAGS_PRESENT_RW) || (pdpt[0] & PT_FLAGS_PS)) return -1;
    pd = (volatile unsigned long *)(pdpt[0] & PT_ADDR_MASK);
    if (!(pd[va >> PT_PD_INDEX_SHIFT] & PT_FLAGS_PRESENT_RW)) return -1;
    if (pd[va >> PT_PD_INDEX_SHIFT] & PT_FLAGS_PS) return -1;
    pt = (volatile unsigned long *)((pd[va >> PT_PD_INDEX_SHIFT]) & PT_ADDR_MASK);
    pte = pt[(va >> 12) & 0x1FF];
    if (!(pte & 0x001) || !(pte & PT_FLAGS_USER)) return -1;
    if (pte & PT_PTE_RW) return -1;
    phys = pte & PT_ADDR_MASK;
    if (!phys) return -1;
    nx = pte & (unsigned long)PT_FLAGS_NX;
    spin_lock(&cow_lock);
    idx = cow_find(phys);
    if (idx < 0) { spin_unlock(&cow_lock); return -1; }
    if (cow_tab[idx].ref <= 1) {
        cow_tab[idx].ref = 0;
        cow_tab[idx].phys = 0;
        pt[(va >> 12) & 0x1FF] = phys | PT_USER_RW_ENTRY | nx;
        __asm__ volatile("invlpg (%0)" :: "r"(va) : "memory");
        spin_unlock(&cow_lock);
        return 0;
    }
    spin_unlock(&cow_lock);
    pg = pt_page_alloc();
    if (!pg) return -1;
    kmemcpy(pg, (void *)phys, 0x1000);
    spin_lock(&cow_lock);
    idx = cow_find(phys);
    if (idx < 0) {
        /* Lost the race with a releaser: keep the private copy
         * (bytes are right), just no ref to drop. */
        pt[(va >> 12) & 0x1FF] = ((unsigned long)pg) | PT_USER_RW_ENTRY | nx;
        __asm__ volatile("invlpg (%0)" :: "r"(va) : "memory");
        spin_unlock(&cow_lock);
        return 0;
    }
    pt[(va >> 12) & 0x1FF] = ((unsigned long)pg) | PT_USER_RW_ENTRY | nx;
    cow_tab[idx].ref--;
    __asm__ volatile("invlpg (%0)" :: "r"(va) : "memory");
    spin_unlock(&cow_lock);
    return 0;
}

/** Docstring: Drop one window's CoW shares before its pages are freed:
 * multi-shared pages are unmapped here (phys survives for the other
 * window), last-shared pages are forgotten so pt_free_user frees them
 * normally. Runs at the head of pt_free_user. */
void cow_release_window(unsigned long cr3) {
    volatile unsigned long *pml4 = (volatile unsigned long *)(cr3 & PT_ADDR_MASK);
    volatile unsigned long *pdpt;
    volatile unsigned long *pd;
    unsigned long lo = USER_LOAD_BASE >> PT_PD_INDEX_SHIFT;
    unsigned long hi = (USER_LOAD_END - 1) >> PT_PD_INDEX_SHIFT;
    unsigned long i, k;
    if (!cr3 || !pml4) return;
    if (!(pml4[0] & PT_FLAGS_PRESENT_RW)) return;
    pdpt = (volatile unsigned long *)(pml4[0] & PT_ADDR_MASK);
    if (!(pdpt[0] & PT_FLAGS_PRESENT_RW) || (pdpt[0] & PT_FLAGS_PS)) return;
    pd = (volatile unsigned long *)(pdpt[0] & PT_ADDR_MASK);
    for (i = lo; i <= hi; i++) {
        volatile unsigned long *pt;
        if (!(pd[i] & PT_FLAGS_PRESENT_RW) || (pd[i] & PT_FLAGS_PS)) continue;
        pt = (volatile unsigned long *)(pd[i] & PT_ADDR_MASK);
        for (k = 0; k < PT_PD_ENTRIES; k++) {
            unsigned long pte = pt[k];
            unsigned long phys;
            int idx;
            if (!(pte & 0x001) || !(pte & PT_FLAGS_USER)) continue;
            if (pte & PT_PTE_RW) continue;
            phys = pte & PT_ADDR_MASK;
            if (!phys) continue;
            idx = cow_find(phys);
            if (idx < 0) continue;
            if (cow_tab[idx].ref > 1) {
                cow_tab[idx].ref--;
                pt[k] = 0;
            } else {
                cow_tab[idx].ref = 0;
                cow_tab[idx].phys = 0;
            }
        }
    }
}

/** Docstring: Live shared-page refs, for the `mem` pressure readout. */
int cow_shared(void) {
    int n = 0, i;
    for (i = 0; i < COW_MAX; i++)
        if (cow_tab[i].ref > 1) n += cow_tab[i].ref;
    return n;
}
