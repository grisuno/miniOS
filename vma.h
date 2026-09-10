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

/* Per-process VMA context (multitask foundation): every non-CLONE_VM
 * process owns its live/free trees plus a private node pool, so two
 * concurrent jobs never corrupt each other's mmap bookkeeping the way
 * the old single global tree did (the DOOM-in-isolation #GP came from
 * exactly that: a fresh window over a stale shared tree). CLONE_VM
 * threads share their parent's context pointer. The kernel-global
 * VMA_NIL/roots/pool below are a *view* onto the running process's
 * context, rebound by vma_ctx_bind on every brk/mmap-view switch; the
 * legacy single-window path keeps using the static vma_legacy context,
 * so its behavior is byte-for-byte unchanged. Pools live on the kernel
 * heap (a static per-proc pool would blow the USER_LOAD_BASE budget). */
typedef struct {
    vma_node_t  nil;
    vma_node_t *pool;
    int         pool_n;
    vma_node_t *live;
    vma_node_t *free;
    vma_node_t *mru;
    unsigned long mru_base;
} vma_ctx_t;

extern vma_node_t *VMA_NIL;
extern vma_node_t *vma_live_root;
extern vma_node_t *vma_free_root;
extern vma_node_t  vma_pool[VMA_MAX];
extern int         vma_pool_n;
extern vma_node_t *vma_pool_ptr;
extern vma_ctx_t   vma_legacy;

void        vma_tree_init(void);
vma_node_t *vma_tree_insert(vma_node_t **root, unsigned long base, unsigned long len);
vma_node_t *vma_tree_find(vma_node_t *root, unsigned long base);
int         vma_tree_delete(vma_node_t **root, unsigned long base);
void        vma_ctx_init(vma_ctx_t *c, vma_node_t *pool);
void        vma_ctx_bind(vma_ctx_t *c);
void        vma_ctx_save(vma_ctx_t *c);
/* Heap-backed contexts live in sched.c (vma.c stays host-testable):
 * alloc returns a fresh context with a private pool, or 0 on OOM. */
vma_ctx_t  *vma_ctx_alloc(void);
void        vma_ctx_free(vma_ctx_t *c);

#endif /* VMA_H */