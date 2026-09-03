#include "kernel.h"

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
