#ifndef VMA_H
#define VMA_H

/*
 * Virtual Memory Area (VMA) red-black tree for mmap/munmap tracking.
 *
 * Replaces the former flat mmap_used/mmap_free arrays with an O(log n)
 * tree.  A single fixed node pool backs the tree for the life of one
 * ring-3 program; both the live and free trees draw from it.  The pool is
 * reset by vma_tree_init on every exec, so a fresh program starts empty.
 *
 * The current kernel runs a single address space, so the tree is a set of
 * process-wide globals (vma_live_root, vma_free_root, VMA_NIL, vma_pool)
 * rather than a per-process instance.  The SPAWN syscall saves and
 * restores those globals across a child ET_EXEC/DYN execution.
 *
 * All operations are integer-only and free of kernel dependencies, which
 * lets the tree be exercised host-side by tests/test_vma.c.
 */

typedef struct vma_node {
    unsigned long    base;
    unsigned long    len;
    int              red;                 /* 1 = red, 0 = black */
    struct vma_node *left, *right, *parent;
} vma_node_t;

#define VMA_MAX 4096

extern vma_node_t *VMA_NIL;
extern vma_node_t *vma_live_root;
extern vma_node_t *vma_free_root;
extern vma_node_t  vma_pool[VMA_MAX];
extern int         vma_pool_n;

void        vma_tree_init(void);
vma_node_t *vma_tree_insert(vma_node_t **root, unsigned long base, unsigned long len);
vma_node_t *vma_tree_find(vma_node_t *root, unsigned long base);
int         vma_tree_delete(vma_node_t **root, unsigned long base);

#endif /* VMA_H */