/** Docstring: fs/pcache.c -- page cache store for MiniFS (T5 slice 1).
 *
 * Fixed pool, FIFO eviction skipping pinned slots, refcounts,
 * dirty bits, per-inode invalidation. Pure bookkeeping: no
 * filesystem knowledge (callers pass inode numbers, never paths),
 * no disk I/O (callers fill reserved pages and flush dirty ones),
 * no blocking (every function is a bounded scan under one irqsave
 * leaf lock, so #PF and syscall context can both call in). The
 * data pages are heap-owned since the .bss diet: a null pool
 * disables every call fail-closed, exactly like the block cache.
 * Slice 2 wires the mmap fault path to get/put; slice 3 wires
 * writeback and pressure eviction around mark_dirty. */

#include "kernel.h"
#include "pcache.h"

typedef struct {
    int ino;
    unsigned index;
    int ref;
    int dirty;
    int valid;
    unsigned long seq;
    unsigned long gen;
} pcache_slot_t;

static pcache_slot_t pc_slots[PCACHE_PAGES];
/** Docstring: Page bodies, heap-owned since the .bss diet. The pool
 * must be page-aligned (slots double as guest-physical mappings),
 * so init over-allocates and aligns up, keeping the raw pointer
 * (never freed: the pool lives for the machine's life, like the
 * virtio queue areas). Null disables the cache; every entry point
 * checks it first. */
static unsigned char *pc_data;
static unsigned char *pc_raw;
static unsigned long pc_seq;
static unsigned long pc_hits;
static unsigned long pc_miss;
static unsigned long pc_evicted;
static spinlock_t pc_lock = SPINLOCK_INIT;

void pcache_init(void) {
    pc_raw = (unsigned char *)kmalloc(
        (unsigned long)PCACHE_PAGES * PCACHE_PAGE + 0xFFFUL);
    if (!pc_raw) {
        kprintf("pcache: disabled (out of memory)\n");
        return;
    }
    pc_data = (unsigned char *)(((unsigned long)pc_raw + 0xFFFUL) &
        ~0xFFFUL);
    kprintf("pcache: %u pages ready\n", (unsigned)PCACHE_PAGES);
}

int pcache_lookup(int ino, unsigned index) {
    irqflags_t flags;
    int i;
    int slot = -1;
    if (!pc_data || ino < 0) return -1;
    spin_lock_irqsave(&pc_lock, &flags);
    for (i = 0; i < PCACHE_PAGES; i++) {
        if (pc_slots[i].valid && pc_slots[i].ino == ino &&
                pc_slots[i].index == index) {
            slot = i;
            break;
        }
    }
    spin_unlock_irqrestore(&pc_lock, flags);
    return slot;
}

int pcache_get(int ino, unsigned index, int *is_new) {
    irqflags_t flags;
    int i;
    int slot = -1;
    unsigned long oldest = 0;
    int victim = -1;
    if (!pc_data || ino < 0) return -1;
    if (is_new) *is_new = 0;
    spin_lock_irqsave(&pc_lock, &flags);
    for (i = 0; i < PCACHE_PAGES; i++) {
        if (pc_slots[i].valid && pc_slots[i].ino == ino &&
                pc_slots[i].index == index) {
            pc_slots[i].ref++;
            pc_hits++;
            slot = i;
            spin_unlock_irqrestore(&pc_lock, flags);
            return slot;
        }
    }
    pc_miss++;
    for (i = 0; i < PCACHE_PAGES; i++) {
        if (!pc_slots[i].valid) {
            victim = i;
            break;
        }
        if (pc_slots[i].ref == 0 &&
                (victim < 0 || pc_slots[i].seq < oldest)) {
            victim = i;
            oldest = pc_slots[i].seq;
        }
    }
    if (victim < 0) {
        spin_unlock_irqrestore(&pc_lock, flags);
        return -1;
    }
    if (pc_slots[victim].valid) pc_evicted++;
    pc_slots[victim].valid = 1;
    pc_slots[victim].ino = ino;
    pc_slots[victim].index = index;
    pc_slots[victim].ref = 1;
    pc_slots[victim].dirty = 0;
    pc_seq++;
    pc_slots[victim].seq = pc_seq;
    pc_slots[victim].gen++;
    slot = victim;
    spin_unlock_irqrestore(&pc_lock, flags);
    if (is_new) *is_new = 1;
    return slot;
}

/** Docstring: Publish a privately filled page into the cache
 * atomically. Copies data into a reserved slot and marks it valid
 * under one lock hold, or refs the slot a racing publisher won
 * first; either way the returned slot is complete before any other
 * holder can see it. Returns the slot (ref 1 for this mapping) or
 * -1 when no slot is free, in which case the caller maps its
 * private page and takes no ref. */
int pcache_publish(int ino, unsigned index, const unsigned char *data) {
    irqflags_t flags;
    int i;
    int slot = -1;
    unsigned long oldest = 0;
    int victim = -1;
    if (!pc_data || ino < 0 || !data) return -1;
    spin_lock_irqsave(&pc_lock, &flags);
    for (i = 0; i < PCACHE_PAGES; i++) {
        if (pc_slots[i].valid && pc_slots[i].ino == ino &&
                pc_slots[i].index == index) {
            pc_slots[i].ref++;
            pc_hits++;
            slot = i;
            spin_unlock_irqrestore(&pc_lock, flags);
            return slot;
        }
    }
    pc_miss++;
    for (i = 0; i < PCACHE_PAGES; i++) {
        if (!pc_slots[i].valid) {
            victim = i;
            break;
        }
        if (pc_slots[i].ref == 0 &&
                (victim < 0 || pc_slots[i].seq < oldest)) {
            victim = i;
            oldest = pc_slots[i].seq;
        }
    }
    if (victim < 0) {
        spin_unlock_irqrestore(&pc_lock, flags);
        return -1;
    }
    if (pc_slots[victim].valid) pc_evicted++;
    for (i = 0; i < PCACHE_PAGE; i++)
        pc_data[(unsigned long)victim * PCACHE_PAGE + (unsigned long)i] =
            data[i];
    pc_slots[victim].valid = 1;
    pc_slots[victim].ino = ino;
    pc_slots[victim].index = index;
    pc_slots[victim].ref = 1;
    pc_slots[victim].dirty = 0;
    pc_seq++;
    pc_slots[victim].seq = pc_seq;
    pc_slots[victim].gen++;
    slot = victim;
    spin_unlock_irqrestore(&pc_lock, flags);
    return slot;
}

void pcache_put(int slot) {
    irqflags_t flags;
    if (!pc_data || slot < 0 || slot >= PCACHE_PAGES) return;
    spin_lock_irqsave(&pc_lock, &flags);
    if (pc_slots[slot].valid && pc_slots[slot].ref > 0)
        pc_slots[slot].ref--;
    spin_unlock_irqrestore(&pc_lock, flags);
}

/** Docstring: Take one more ref on a cached page without allocating.
 * Fork uses this for every file-backed page the child inherits, so
 * the child teardown drops exactly what the copy added. Returns the
 * slot or -1 when the page is not cached. */
int pcache_ref(int ino, unsigned index) {
    irqflags_t flags;
    int i;
    int slot = -1;
    if (!pc_data || ino < 0) return -1;
    spin_lock_irqsave(&pc_lock, &flags);
    for (i = 0; i < PCACHE_PAGES; i++) {
        if (pc_slots[i].valid && pc_slots[i].ino == ino &&
                pc_slots[i].index == index) {
            pc_slots[i].ref++;
            slot = i;
            break;
        }
    }
    spin_unlock_irqrestore(&pc_lock, flags);
    return slot;
}

/** Docstring: Drop the ref a mapping holds on one cached page. The
 * munmap and teardown walks derive (ino, index) from the VMA node
 * and call this per page; unknown pages are a silent no-op so a
 * partially populated mapping unmaps cleanly. Prefer put_if below
 * wherever the PTE is at hand: blind drops can steal another
 * mapping's ref after a private fallback. */
void pcache_unmap(int ino, unsigned index) {
    int slot = pcache_lookup(ino, index);
    if (slot >= 0) pcache_put(slot);
}

/** Docstring: Slot base address for phys comparisons. */
static unsigned long pcache_slot_phys(int slot) {
    return (unsigned long)pc_data + (unsigned long)slot * PCACHE_PAGE;
}

/** Docstring: Drop one ref only when the cached page is the exact
 * phys the caller maps. Munmap, mremap and teardown prove ownership
 * through the PTE before releasing, so a private fallback page (or
 * a recycled slot) never donates a ref it never took. Returns 1 on
 * a phys match (owned, ref dropped unless already zero), 0
 * otherwise. */
int pcache_put_if(int ino, unsigned index, unsigned long phys) {
    irqflags_t flags;
    int i;
    int owned = 0;
    if (!pc_data || ino < 0) return 0;
    spin_lock_irqsave(&pc_lock, &flags);
    for (i = 0; i < PCACHE_PAGES; i++) {
        if (pc_slots[i].valid && pc_slots[i].ino == ino &&
                pc_slots[i].index == index) {
            if (pcache_slot_phys(i) != phys) break;
            if (pc_slots[i].ref > 0) pc_slots[i].ref--;
            owned = 1;
            break;
        }
    }
    spin_unlock_irqrestore(&pc_lock, flags);
    return owned;
}

/** Docstring: Take one more ref only when the cached page is the
 * exact phys the caller shares. Fork proves sharing through the
 * parent PTE before inheriting, so a stale VMA tag never pins a
 * recycled slot. Returns the slot or -1. */
int pcache_ref_if(int ino, unsigned index, unsigned long phys) {
    irqflags_t flags;
    int i;
    int slot = -1;
    if (!pc_data || ino < 0) return -1;
    spin_lock_irqsave(&pc_lock, &flags);
    for (i = 0; i < PCACHE_PAGES; i++) {
        if (pc_slots[i].valid && pc_slots[i].ino == ino &&
                pc_slots[i].index == index) {
            if (pcache_slot_phys(i) != phys) break;
            pc_slots[i].ref++;
            slot = i;
            break;
        }
    }
    spin_unlock_irqrestore(&pc_lock, flags);
    return slot;
}

/** Docstring: True when phys is a cache pool page. The teardown
 * sweeper skips those instead of freeing pool memory as if it were
 * a private data page. */
int pcache_owns_phys(unsigned long phys) {
    unsigned long base;
    if (!pc_data) return 0;
    base = (unsigned long)pc_data;
    return phys >= base &&
        phys < base + (unsigned long)PCACHE_PAGES * PCACHE_PAGE;
}

unsigned char *pcache_data(int slot) {
    if (!pc_data || slot < 0 || slot >= PCACHE_PAGES) return 0;
    if (!pc_slots[slot].valid) return 0;
    return pc_data + (unsigned long)slot * PCACHE_PAGE;
}

void pcache_mark_dirty(int slot) {
    irqflags_t flags;
    if (!pc_data || slot < 0 || slot >= PCACHE_PAGES) return;
    spin_lock_irqsave(&pc_lock, &flags);
    if (pc_slots[slot].valid) pc_slots[slot].dirty = 1;
    spin_unlock_irqrestore(&pc_lock, flags);
}

void pcache_invalidate_ino(int ino) {
    irqflags_t flags;
    int i;
    if (!pc_data || ino < 0) return;
    spin_lock_irqsave(&pc_lock, &flags);
    for (i = 0; i < PCACHE_PAGES; i++) {
        if (pc_slots[i].valid && pc_slots[i].ino == ino) {
            pc_slots[i].valid = 0;
            pc_slots[i].ref = 0;
            pc_slots[i].dirty = 0;
        }
    }
    spin_unlock_irqrestore(&pc_lock, flags);
}

void pcache_stats(unsigned long *pages_out, unsigned long *hits_out,
        unsigned long *miss_out, unsigned long *evicted_out,
        unsigned long *dirty_out) {
    irqflags_t flags;
    unsigned long n = 0;
    unsigned long d = 0;
    int i;
    spin_lock_irqsave(&pc_lock, &flags);
    for (i = 0; i < PCACHE_PAGES; i++) {
        if (!pc_slots[i].valid) continue;
        n++;
        if (pc_slots[i].dirty) d++;
    }
    if (pages_out) *pages_out = n;
    if (hits_out) *hits_out = pc_hits;
    if (miss_out) *miss_out = pc_miss;
    if (evicted_out) *evicted_out = pc_evicted;
    if (dirty_out) *dirty_out = d;
    spin_unlock_irqrestore(&pc_lock, flags);
}
