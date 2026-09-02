#ifndef VMA_H
#define VMA_H

/* Virtual Memory Area (VMA) tree for mmap tracking.
 *
 * Replaces the flat mmap_used/mmap_free arrays with a red-black tree
 * for O(log n) lookup and insertion.  The current kernel uses flat
 * arrays (MMAP_MAX=4096); this header defines the tree structure for
 * future adoption when the single-address-space model gains per-process
 * page tables.
 *
 * Design:
 *   - One VMA node per mmap allocation (base + len + flags)
 *   - Sorted by base address in a red-black tree
 *   - Free regions tracked in a separate buddy or slab structure
 *   - munmap splits or removes nodes; coalescing on adjacent frees
 *   - All operations are page-aligned (4 KB granularity)
 */

#define VMA_GRANULE 0x1000

typedef enum {
    VMA_ANONYMOUS = 0,
    VMA_MAPPED    = 1,
    VMA_STACK     = 2,
    VMA_HEAP      = 3,
} vma_type_t;

typedef struct vma_node {
    unsigned long      base;
    unsigned long      len;
    vma_type_t         type;
    int                red;    /* red-black tree color: 1=red, 0=black */
    struct vma_node   *left;
    struct vma_node   *right;
    struct vma_node   *parent;
} vma_node_t;

typedef struct {
    vma_node_t *root;
    vma_node_t *nil;       /* sentinel node (black leaf) */
    int         count;
    int         capacity;
    vma_node_t *pool;      /* pre-allocated node array */
} vma_tree_t;

/* Initialize a VMA tree with a pre-allocated pool of `cap` nodes. */
void vma_init(vma_tree_t *t, vma_node_t *pool, int cap);

/* Insert a new region.  Returns the node or NULL if pool exhausted. */
vma_node_t *vma_insert(vma_tree_t *t, unsigned long base, unsigned long len,
                        vma_type_t type);

/* Find the node containing `addr`, or NULL. */
vma_node_t *vma_find(vma_tree_t *t, unsigned long addr);

/* Remove a node by base address.  Returns 0 on success, -1 if not found. */
int vma_remove(vma_tree_t *t, unsigned long base);

/* Find the first free gap of at least `len` bytes above `min_addr`.
   Returns the base address of the gap, or 0 if none found. */
unsigned long vma_find_free(vma_tree_t *t, unsigned long len, unsigned long min_addr);

/* Coalesce adjacent free regions (call after munmap). */
void vma_coalesce(vma_tree_t *t);

#endif /* VMA_H */
