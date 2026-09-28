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

/* Fault-injection hook for stress testing (boyscout gap #10): when
 * kmalloc_fail_after >= 0, the next allocations fail deterministically.
 * Host and BDD suites drive OOM paths through it; production leaves it at -1. */
long kmalloc_fail_after = -1;
void *kmalloc(unsigned long size) {
    if (size == 0) return 0;
    if (kmalloc_fail_after == 0) return 0;
    if (kmalloc_fail_after > 0) kmalloc_fail_after--;
    return dlmalloc_malloc(size);
}

void kfree(void *ptr) {
    unsigned long p;
    if (!ptr) return;
    /* Fail loud with attribution instead of a cryptic #GP inside
     * dlmalloc: a pointer outside the heap is never a valid free, and
     * the caller address identifies the culprit at the next crash
     * instead of leaving a poisoned-pointer mystery. */
    p = (unsigned long)ptr;
    if (p < (unsigned long)HEAP_BASE ||
        p >= (unsigned long)HEAP_BASE + (unsigned long)HEAP_SIZE) {
        unsigned long rsp_now;
        __asm__ volatile("mov %%rsp, %0" : "=r"(rsp_now));
        panic_screen(13, p,
                (unsigned long)__builtin_return_address(0),
                rsp_now,
                (unsigned long)__builtin_frame_address(0), 1);
        for (;;) __asm__ volatile("hlt");
    }
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

/** Docstring: Aligned allocation with a recoverable raw pointer.
 *
 * Reserves size bytes at the requested power-of-two alignment and stores
 * the original kmalloc pointer in the word below the aligned base, so
 * kfree_aligned releases exactly what the allocator returned. Fail-closed
 * on zero size, non-power-of-two alignment and size arithmetic overflow. */
void *kmalloc_aligned(unsigned long size, unsigned long align) {
    unsigned long total;
    unsigned long raw;
    unsigned long aligned;
    if (size == 0 || align == 0 || (align & (align - 1)) != 0) return 0;
    if (size > (unsigned long)-1 - align - sizeof(void *)) return 0;
    total = size + align + sizeof(void *);
    raw = (unsigned long)kmalloc(total);
    if (!raw) return 0;
    aligned = (raw + sizeof(void *) + align - 1) & ~(align - 1);
    *(unsigned long *)(aligned - sizeof(void *)) = raw;
    return (void *)aligned;
}

/** Docstring: Release a kmalloc_aligned block. A null pointer is a no-op;
 * a pointer outside the heap halts through kfree, never silently. */
void kfree_aligned(void *ptr) {
    unsigned long raw;
    if (!ptr) return;
    raw = *(unsigned long *)((unsigned long)ptr - sizeof(void *));
    kfree((void *)raw);
}
