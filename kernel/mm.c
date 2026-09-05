#include "kernel.h"
#include "sched.h"

/* ================================================================
 *  Memory allocator
 *
 *  Thin wrappers over dlmalloc 2.8.6 (third_party/dlmalloc), a
 *  private mspace rooted at the fixed kernel heap.  The space is
 *  built with HAVE_MORECORE=0 and HAVE_MMAP=0, so it can never
 *  grow past HEAP_SIZE; an exhausted heap returns 0.
 * ================================================================ */

void kallocator_init(void) {
    dlmalloc_init();
}

void *kmalloc(unsigned long size) {
    if (size == 0) return 0;
    return dlmalloc_malloc(size);
}

void kfree(void *ptr) {
    if (!ptr) return;
    dlmalloc_free(ptr);
}

void *kcalloc(unsigned long nmemb, unsigned long size) {
    return dlmalloc_calloc(nmemb, size);
}

void *krealloc(void *ptr, unsigned long size) {
    if (!ptr) return kmalloc(size);
    if (size == 0) { kfree(ptr); return 0; }
    return dlmalloc_realloc(ptr, size);
}

/* Per-CPU memory allocation.
 *
 * Allocates cpu_count * size bytes, aligned to `align`, zeroed.
 * Each CPU accesses its own region at offset cpu_id * size.
 * Returns NULL on failure.  The caller must not free individual
 * CPU regions; the whole block is freed as one allocation.
 *
 * This is a building block for Phase 2 (per-CPU run queues)
 * and Phase 3 (per-CPU wait queue caches).  Not wired into
 * any subsystem yet; the API is established for future use. */
void *kmalloc_percpu(unsigned long size, unsigned long align) {
    if (size == 0 || cpu_count == 0) return 0;
    unsigned long total = size * (unsigned long)cpu_count;
    if (align > sizeof(void *)) {
        total += align;
    }
    void *base = kmalloc(total);
    if (!base) return 0;
    kmemset(base, 0, total);
    if (align > sizeof(void *)) {
        unsigned long addr = (unsigned long)base;
        unsigned long aligned = (addr + align - 1) & ~(align - 1);
        return (void *)aligned;
    }
    return base;
}
