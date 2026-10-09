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

/* Share table: open addressing over the frame number, sized for every
 * user page the heap can back (HEAP_SIZE / 4 KB frames at most 3/4 full).
 * The old 512-entry table made fork of any real process copy everything
 * past the first 512 pages eagerly: forking a 100 MB browser duplicated it
 * before the child could exec, and the kernel heap ran dry. */
#define COW_BITS      16
#define COW_CAP       (1UL << COW_BITS)
#define COW_MASK      (COW_CAP - 1UL)
#define COW_LOAD_MAX  (COW_CAP / 4UL * 3UL)
#define COW_TOMB_MAX  (COW_CAP / 4UL)
#define COW_EMPTY     0UL
#define COW_TOMB      1UL
#define COW_HASH_MUL  0x9E3779B97F4A7C15UL
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

static cow_entry_t *cow_tab;
static unsigned long cow_live;
static unsigned long cow_tombs;
static int cow_drops;

static unsigned long cow_slot(unsigned long phys) {
    return ((phys >> 12) * COW_HASH_MUL) >> (64 - COW_BITS);
}

/* Index of phys's live entry, or -1. Caller holds cow_lock. */
static int cow_find(unsigned long phys) {
    unsigned long i, n;
    if (!cow_tab || phys <= COW_TOMB) return -1;
    for (i = cow_slot(phys), n = 0; n < COW_CAP; i = (i + 1) & COW_MASK, n++) {
        if (cow_tab[i].phys == COW_EMPTY) return -1;
        if (cow_tab[i].phys == phys && cow_tab[i].ref > 0) return (int)i;
    }
    return -1;
}

/* Retire entry idx: a tombstone keeps later probe chains intact; an empty
 * table drops every tombstone at once. Caller holds cow_lock. */
static void cow_remove(int idx) {
    cow_tab[idx].ref = 0;
    cow_tab[idx].phys = COW_TOMB;
    cow_live--;
    cow_tombs++;
    if (cow_live == 0) {
        kmemset(cow_tab, 0, COW_CAP * sizeof(cow_entry_t));
        cow_tombs = 0;
    }
}

/* Create the table on first use, outside cow_lock (allocation). Fork
 * without a table copies pages eagerly, as before. */
static void cow_table_ensure(void) {
    cow_entry_t *t;
    if (cow_tab) return;
    t = (cow_entry_t *)kmalloc(COW_CAP * sizeof(cow_entry_t));
    if (!t) return;
    kmemset(t, 0, COW_CAP * sizeof(cow_entry_t));
    if (__sync_val_compare_and_swap(&cow_tab, (cow_entry_t *)0, t) != 0) kfree(t);
}

/* Reinsert the live entries in place when tombstones lengthen the probe
 * chains: lift each live entry out and insert it again. Caller holds
 * cow_lock. */
static void cow_rehash(void) {
    unsigned long i;
    for (i = 0; i < COW_CAP; i++)
        if (cow_tab[i].phys == COW_TOMB) cow_tab[i].phys = COW_EMPTY;
    cow_tombs = 0;
    for (i = 0; i < COW_CAP; i++) {
        unsigned long phys = cow_tab[i].phys, j;
        int ref = cow_tab[i].ref;
        if (phys == COW_EMPTY) continue;
        cow_tab[i].phys = COW_EMPTY;
        cow_tab[i].ref = 0;
        for (j = cow_slot(phys); cow_tab[j].phys != COW_EMPTY; j = (j + 1) & COW_MASK) {}
        cow_tab[j].phys = phys;
        cow_tab[j].ref = ref;
    }
}

/** Docstring: True when phys is still shared copy-on-write. mprotect
 * consults this before setting a writable bit: upgrading a shared
 * page in place would let one window write another's bytes without
 * ever faulting into cow_resolve. Pure scan, no allocation, safe
 * under the caller's mm_lock (cow_lock is a leaf here). */
int cow_page_shared(unsigned long phys) {
    irqflags_t cow_irq;
    int shared;
    spin_lock_irqsave(&cow_lock, &cow_irq);
    shared = cow_find(phys) >= 0;
    spin_unlock_irqrestore(&cow_lock, cow_irq);
    return shared;
}

/** Docstring: Share one phys page: bump its refcount, or install it.
 * Returns 0 shared, -1 when the table is full (caller eager-copies). */
/* Drop one mapping's share of phys. Returns 1 while other mappings still
 * share the frame (the caller only clears its PTE), 0 when the caller was
 * the last holder or the frame was never shared (the caller frees it). */
int cow_drop_ref(unsigned long phys) {
    irqflags_t cow_irq;
    int idx, shared = 0;
    spin_lock_irqsave(&cow_lock, &cow_irq);
    idx = cow_find(phys);
    if (idx >= 0) {
        if (cow_tab[idx].ref > 1) {
            cow_tab[idx].ref--;
            shared = 1;
        } else {
            cow_remove(idx);
        }
    }
    spin_unlock_irqrestore(&cow_lock, cow_irq);
    return shared;
}

/* Copy the parent's demand-paging reservations (non-present PTEs carrying
 * PTE_DEMAND) into the child: a reserved, never-touched page is part of
 * the address space fork duplicates, and the child faults it in fresh. */
static void cow_copy_demand(unsigned long pcr3, unsigned long ccr3) {
    volatile unsigned long *ppd, *cpd;
    volatile unsigned long *pml4;
    unsigned long lo = USER_LOAD_BASE >> PT_PD_INDEX_SHIFT;
    unsigned long hi = (USER_LOAD_END - 1) >> PT_PD_INDEX_SHIFT;
    unsigned long i, k;
    pml4 = (volatile unsigned long *)(pcr3 & PT_ADDR_MASK);
    if (!(pml4[0] & PT_FLAGS_PRESENT_RW)) return;
    ppd = (volatile unsigned long *)(((volatile unsigned long *)(pml4[0] & PT_ADDR_MASK))[0] & PT_ADDR_MASK);
    pml4 = (volatile unsigned long *)(ccr3 & PT_ADDR_MASK);
    if (!(pml4[0] & PT_FLAGS_PRESENT_RW)) return;
    cpd = (volatile unsigned long *)(((volatile unsigned long *)(pml4[0] & PT_ADDR_MASK))[0] & PT_ADDR_MASK);
    if (!ppd || !cpd) return;
    for (i = lo; i <= hi; i++) {
        volatile unsigned long *ppt, *cpt;
        if (!(ppd[i] & PT_FLAGS_PRESENT_RW) || (ppd[i] & PT_FLAGS_PS)) continue;
        if (!(cpd[i] & PT_FLAGS_PRESENT_RW) || (cpd[i] & PT_FLAGS_PS)) continue;
        ppt = (volatile unsigned long *)(ppd[i] & PT_ADDR_MASK);
        cpt = (volatile unsigned long *)(cpd[i] & PT_ADDR_MASK);
        for (k = 0; k < PT_PD_ENTRIES; k++)
            if (!(ppt[k] & 0x001) && (ppt[k] & PTE_DEMAND))
                cpt[k] = ppt[k];
    }
}

static int cow_track(unsigned long phys) {
    unsigned long i, n;
    int idx = cow_find(phys);
    if (idx >= 0) {
        cow_tab[idx].ref++;
        return 0;
    }
    if (!cow_tab || cow_live >= COW_LOAD_MAX) {
        cow_drops++;
        return -1;
    }
    if (cow_tombs > COW_TOMB_MAX) cow_rehash();
    for (i = cow_slot(phys), n = 0; n < COW_CAP; i = (i + 1) & COW_MASK, n++) {
        if (cow_tab[i].phys == COW_EMPTY || cow_tab[i].phys == COW_TOMB) {
            if (cow_tab[i].phys == COW_TOMB) cow_tombs--;
            cow_tab[i].phys = phys;
            cow_tab[i].ref = 2;
            cow_live++;
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
    irqflags_t cow_irq;
    unsigned long child;
    unsigned long saved;
    if (!parent_cr3) return 0;
    cow_table_ensure();
    child = pt_clone_user_empty();
    if (!child) return 0;
    cow_fork_parent = parent_cr3;
    cow_fork_child = child;
    cow_fork_failed = 0;
    __asm__ volatile("mov %%cr3, %0" : "=r"(saved));
    /* The walk switches CR3, so interrupts stay off across it; the
     * caller's interrupt state comes back afterwards (do_fork runs this
     * with interrupts already off and must not have them re-enabled). */
    spin_lock_irqsave(&cow_lock, &cow_irq);
    cow_walk(parent_cr3, cow_fork_one);
    if (!cow_fork_failed) cow_copy_demand(parent_cr3, child);
    __asm__ volatile("mov %0, %%cr3" :: "r"(saved) : "memory");
    spin_unlock_irqrestore(&cow_lock, cow_irq);
    if (cow_fork_failed) {
        cow_release_window(child);
        pt_free_user(child);
        return 0;
    }
    return child;
}

/** Docstring: 1 when va is mapped present and user-accessible in the
 * window of cr3. Lets the kernel test a user word it is about to write on
 * its own initiative (CLONE_CHILD_SETTID/CLEARTID), where a pointer that is
 * inside the user window but unmapped would otherwise fault in ring 0 with
 * nothing to recover it. A copy-on-write page counts as present: the write
 * privatizes through cow_resolve. */
int user_page_present(unsigned long cr3, unsigned long va) {
    volatile unsigned long *pml4;
    volatile unsigned long *pdpt;
    volatile unsigned long *pd;
    volatile unsigned long *pt;
    unsigned long pde, pte;
    if (!cr3) return 0;
    if (va < USER_LOAD_BASE || va >= USER_LOAD_END) return 0;
    pml4 = (volatile unsigned long *)(cr3 & PT_ADDR_MASK);
    if (!(pml4[0] & PT_FLAGS_PRESENT_RW)) return 0;
    pdpt = (volatile unsigned long *)(pml4[0] & PT_ADDR_MASK);
    if (!(pdpt[0] & PT_FLAGS_PRESENT_RW) || (pdpt[0] & PT_FLAGS_PS)) return 0;
    pd = (volatile unsigned long *)(pdpt[0] & PT_ADDR_MASK);
    pde = pd[va >> PT_PD_INDEX_SHIFT];
    if (!(pde & PT_FLAGS_PRESENT_RW)) return 0;
    if (pde & PT_FLAGS_PS) return (pde & PT_FLAGS_USER) ? 1 : 0;
    pt = (volatile unsigned long *)(pde & PT_ADDR_MASK);
    pte = pt[(va >> 12) & 0x1FF];
    return ((pte & 0x001) && (pte & PT_FLAGS_USER)) ? 1 : 0;
}

/* cow_lock is taken with the caller's interrupt state saved and restored,
 * never the plain spin_lock/spin_unlock pair: spin_unlock always runs sti,
 * which re-enabled interrupts in the middle of a resolve the #PF handler
 * deliberately runs with interrupts off. A tick then preempted ring-0 code
 * mid-copy and the resolve resumed with a clobbered index (a kernel #PF in
 * cow_resolve once kernel writes started faulting into it under CR0.WP). */

/** Docstring: Resolve a write fault on a CoW page: last sharer gets a
 * permission upgrade, otherwise the faulting window gets a private
 * copy. invlpg keeps the TLB honest. Returns 0 resolved (resume),
 * -1 not a CoW page (existing fault handling runs). */
int cow_resolve(unsigned long cr3, unsigned long va) {
    irqflags_t cow_irq;
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
    spin_lock_irqsave(&cow_lock, &cow_irq);
    idx = cow_find(phys);
    if (idx < 0) { spin_unlock_irqrestore(&cow_lock, cow_irq); return -1; }
    if (cow_tab[idx].ref <= 1) {
        cow_remove(idx);
        pt[(va >> 12) & 0x1FF] = phys | PT_USER_RW_ENTRY | nx;
        __asm__ volatile("invlpg (%0)" :: "r"(va) : "memory");
        spin_unlock_irqrestore(&cow_lock, cow_irq);
        return 0;
    }
    spin_unlock_irqrestore(&cow_lock, cow_irq);
    pg = pt_page_alloc();
    if (!pg) return -1;
    kmemcpy(pg, (void *)phys, 0x1000);
    spin_lock_irqsave(&cow_lock, &cow_irq);
    idx = cow_find(phys);
    if (idx < 0) {
        /* Lost the race with a releaser: keep the private copy
         * (bytes are right), just no ref to drop. */
        pt[(va >> 12) & 0x1FF] = ((unsigned long)pg) | PT_USER_RW_ENTRY | nx;
        __asm__ volatile("invlpg (%0)" :: "r"(va) : "memory");
        spin_unlock_irqrestore(&cow_lock, cow_irq);
        return 0;
    }
    pt[(va >> 12) & 0x1FF] = ((unsigned long)pg) | PT_USER_RW_ENTRY | nx;
    cow_tab[idx].ref--;
    __asm__ volatile("invlpg (%0)" :: "r"(va) : "memory");
    spin_unlock_irqrestore(&cow_lock, cow_irq);
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
    irqflags_t cow_irq;
    if (!cr3 || !pml4) return;
    if (!(pml4[0] & PT_FLAGS_PRESENT_RW)) return;
    pdpt = (volatile unsigned long *)(pml4[0] & PT_ADDR_MASK);
    if (!(pdpt[0] & PT_FLAGS_PRESENT_RW) || (pdpt[0] & PT_FLAGS_PS)) return;
    pd = (volatile unsigned long *)(pdpt[0] & PT_ADDR_MASK);
    /* The share counts change under cow_lock like every other cow_tab
     * update: a sibling thread on another CPU may be resolving a fault on
     * one of these frames right now. */
    spin_lock_irqsave(&cow_lock, &cow_irq);
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
                cow_remove(idx);
            }
        }
    }
    spin_unlock_irqrestore(&cow_lock, cow_irq);
}

/** Docstring: Live shared-page refs, for the `mem` pressure readout. */
int cow_shared(void) {
    int n = 0;
    unsigned long i;
    if (!cow_tab) return 0;
    for (i = 0; i < COW_CAP; i++)
        if (cow_tab[i].phys > COW_TOMB && cow_tab[i].ref > 1) n += cow_tab[i].ref;
    return n;
}
