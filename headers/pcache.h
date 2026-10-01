/** Docstring: pcache.h -- page cache for MiniFS, slice 1 (store only).
 *
 * A fixed pool of 4 KB pages keyed by (inode, page index) with
 * refcounts and dirty bits, the backing store the file-backed mmap
 * of T5 slice 2 will populate from and the writeback of slice 3
 * will flush. Slice 1 owns the store, the lookup/reserve/evict
 * discipline and the invalidate hooks (truncate/unlink drop the
 * inode's pages; dirty pages drop too until slice 3 teaches
 * writeback, and no in-tree writer marks dirty yet so nothing is
 * lost). Reads and writes still flow through the existing block
 * paths untouched: the cache is live scaffolding (pool allocated
 * at boot, hooks active) with zero behavior change until slice 2
 * wires the fault path to it.
 */

#ifndef PCACHE_H
#define PCACHE_H

/** Docstring: Pool size in pages (256 x 4 KB = 1 MB of heap). */
#define PCACHE_PAGES 256

/** Docstring: Cache page size, always the MiniFS block size. */
#define PCACHE_PAGE 4096

/** Docstring: Allocate the page pool; disabled (all calls fail
 * closed) when the heap cannot spare it, exactly like the block
 * cache. Prints one boot marker either way. */
void pcache_init(void);

/** Docstring: Find a cached page without reserving. Returns the slot
 * or -1. Never allocates, never evicts. */
int pcache_lookup(int ino, unsigned index);

/** Docstring: Get a page, pinned with one ref. Hit returns the live
 * slot; miss reserves an empty or evicted slot (ref 1, clean,
 * *is_new 1, data uninitialized: the caller fills it before any
 * reader sees it) or -1 when every slot is pinned or the pool is
 * disabled, in which case the caller falls back to direct block
 * I/O, fail-open correct. Racy fills must use publish below, never
 * a reserved-then-filled get: a concurrent faulter would map the
 * half-written page. */
int pcache_get(int ino, unsigned index, int *is_new);

/** Docstring: Publish a privately filled page into the cache
 * atomically. Copies data into a reserved slot and marks it valid
 * under one lock hold, or refs the slot a racing publisher won
 * first; either way the returned slot is complete before any other
 * holder can see it. Returns the slot (ref 1 for this mapping) or
 * -1 when no slot is free, in which case the caller maps its
 * private page and takes no ref. */
int pcache_publish(int ino, unsigned index, const unsigned char *data);

/** Docstring: Drop one ref taken by get. A zero ref is a no-op,
 * never negative. */
void pcache_put(int slot);

/** Docstring: Take one more ref on a cached page without allocating.
 * Fork uses this for every file-backed page the child inherits, so
 * the child teardown drops exactly what the copy added. Returns the
 * slot or -1 when the page is not cached. */
int pcache_ref(int ino, unsigned index);

/** Docstring: Drop the ref a mapping holds on one cached page. The
 * munmap and teardown walks derive (ino, index) from the VMA node
 * and call this per page; unknown pages are a silent no-op so a
 * partially populated mapping unmaps cleanly. Prefer put_if below
 * wherever the PTE is at hand: blind drops can steal another
 * mapping's ref after a private fallback. */
void pcache_unmap(int ino, unsigned index);

/** Docstring: Drop one ref only when the cached page is the exact
 * phys the caller maps. Munmap, mremap and teardown prove ownership
 * through the PTE before releasing, so a private fallback page (or
 * a recycled slot) never donates a ref it never took. Returns 1 on
 * a phys match (owned, ref dropped unless already zero), 0
 * otherwise. */
int pcache_put_if(int ino, unsigned index, unsigned long phys);

/** Docstring: Take one more ref only when the cached page is the
 * exact phys the caller shares. Fork proves sharing through the
 * parent PTE before inheriting, so a stale VMA tag never pins a
 * recycled slot. Returns the slot or -1. */
int pcache_ref_if(int ino, unsigned index, unsigned long phys);

/** Docstring: True when phys is a cache pool page. The teardown
 * sweeper skips those instead of freeing pool memory as if it were
 * a private data page. */
int pcache_owns_phys(unsigned long phys);

/** Docstring: Page data for a slot from get/lookup, 0 on a bad
 * slot. The pointer stays valid until put drops the last ref and
 * the slot is recycled. */
unsigned char *pcache_data(int slot);

/** Docstring: Mark a pinned page dirty. Slice 3 flushes it;
 * slice 1 only records. Recycled slots bump a generation counter
 * (slice 3 exposes it so holders can validate across put). */
void pcache_mark_dirty(int slot);

/** Docstring: Drop every page of an inode (truncate/unlink).
 * Dirty pages drop with them until slice 3 teaches writeback. */
void pcache_invalidate_ino(int ino);

/** Docstring: Snapshot for the mem builtin and BDD: live pages,
 * cumulative hits/misses/evictions, dirty count. */
void pcache_stats(unsigned long *pages_out, unsigned long *hits_out,
    unsigned long *miss_out, unsigned long *evicted_out,
    unsigned long *dirty_out);

#endif
