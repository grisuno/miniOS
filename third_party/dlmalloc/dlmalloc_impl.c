/* dlmalloc_impl.c — kernel-side implementation of the dlmalloc allocator.
 *
 * Compiles Doug Lea's malloc (2.8.6) into the kernel image as a private
 * mspace rooted at the fixed kernel heap, so kmalloc/kfree/realloc/calloc
 * get a battle-tested, fragmentation-aware allocator. The mspace API is used
 * (MSPACES + ONLY_MSPACES) so no global malloc/free symbols are emitted that
 * could shadow the kernel's own libc stubs, and create_mspace_with_base roots
 * the space directly over the existing [HEAP_BASE, HEAP_BASE+HEAP_SIZE)
 * region. HAVE_MORECORE and HAVE_MMAP are both disabled, so the space can
 * never grow beyond the fixed heap: an exhausted heap returns 0 exactly like
 * the first-fit allocator it replaces, never a wild expansion.
 *
 * malloc.c is a pristine upstream copy (MIT-0); none of it is edited, every
 * knob is applied through the macros below.
 */
#include "kernel.h"
#include <stddef.h>

#define MSPACES 1
#define ONLY_MSPACES 1
#define HAVE_MORECORE 0
#define HAVE_MMAP 0
#define MALLOC_ALIGNMENT ((size_t)16U)
#define LACKS_STDLIB_H
#define LACKS_STRING_H
#define LACKS_UNISTD_H
#define LACKS_SYS_PARAM_H
#define LACKS_SYS_MMAN_H
#define LACKS_ERRNO_H
#define LACKS_SCHED_H
#define LACKS_FCNTL_H
#define LACKS_STRINGS_H
#define LACKS_TIME_H

/* No malloc_stats(): it pulls in stdio (fprintf/stderr) the kernel does not
 * carry. The seed used for the internal magic comes from a fixed nonzero
 * constant instead of time(0) (the kernel has no RTC dependency here; the
 * value only needs to be nonzero for the integrity footers). */
#define NO_MALLOC_STATS 1
#define time(x) 0
#define DEFAULT_GRANULARITY ((size_t)4096U)

/* Fail closed: an exhausted heap returns 0 (the caller gets a NULL and
 * reports), never a set errno the kernel has no concept of. */
#define MALLOC_FAILURE_ACTION
/* Internal-corruption path: hang the machine rather than silently proceed. */
#define ABORT for(;;)
#define memcpy(a, b, n)  kmemcpy(a, b, n)
#define memmove(a, b, n) kmemmove(a, b, n)
#define memset(a, c, n)  kmemset(a, c, n)

#include "malloc.c"

/* Kernel adapter: keep the mspace handle in one place. kallocator_init calls
 * dlmalloc_init to build the space over the kernel heap; every kmalloc/kfree
 * call below is a thin mspace_* pass-through. */
static mspace kheap_mspace = 0;

void dlmalloc_init(void) {
    kheap_mspace = create_mspace_with_base((void *)HEAP_BASE, HEAP_SIZE, 0);
}

void *dlmalloc_malloc(unsigned long size) {
    if (!kheap_mspace) return 0;
    return mspace_malloc(kheap_mspace, (size_t)size);
}

void dlmalloc_free(void *ptr) {
    if (kheap_mspace) mspace_free(kheap_mspace, ptr);
}

void *dlmalloc_calloc(unsigned long nmemb, unsigned long size) {
    if (!kheap_mspace) return 0;
    return mspace_calloc(kheap_mspace, (size_t)nmemb, (size_t)size);
}

void *dlmalloc_realloc(void *ptr, unsigned long size) {
    if (!kheap_mspace) return 0;
    return mspace_realloc(kheap_mspace, ptr, (size_t)size);
}
