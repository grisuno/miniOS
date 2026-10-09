#include "kernel.h"
#include "sched.h"
#include "bootdefs.h"

/* ================================================================
 *  Memory allocator
 *
 *  Thin wrappers over dlmalloc 2.8.6 (third_party/dlmalloc), a
 *  private mspace rooted at the fixed kernel heap.  The space is
 *  built with HAVE_MORECORE=0 and HAVE_MMAP=0, so it can never
 *  grow past HEAP_SIZE; an exhausted heap returns 0.
 * ================================================================ */

unsigned long kheap_size;

/* RAM top from the CMOS extended-memory count (the identity map covers
 * the first gigabyte; nothing else reports the installed size). 0 when
 * the firmware left the count empty. */
static unsigned long kheap_ram_top(void) {
    unsigned long units;
    outb(CMOS_INDEX_PORT, CMOS_REG_EXTMEM_LO);
    units = inb(CMOS_DATA_PORT);
    outb(CMOS_INDEX_PORT, CMOS_REG_EXTMEM_HI);
    units |= (unsigned long)inb(CMOS_DATA_PORT) << 8;
    if (units == 0) return 0;
    return CMOS_EXTMEM_BASE + units * CMOS_EXTMEM_UNIT;
}

/* Build the heap over [HEAP_BASE, HEAP_BASE + kheap_size): the layout
 * maximum, never past the installed RAM (a smaller machine must not be
 * handed memory that does not exist). */
void kallocator_init(void) {
    unsigned long top = kheap_ram_top();
    kheap_size = HEAP_SIZE;
    if (top > HEAP_BASE && top - HEAP_BASE < kheap_size)
        kheap_size = (top - HEAP_BASE) & ~(KMALLOC_PAGE - 1UL);
    dlmalloc_init(kheap_size);
}

/* Fault-injection hook for stress testing (boyscout gap #10): when
 * kmalloc_fail_after >= 0, the next allocations fail deterministically.
 * Host and BDD suites drive OOM paths through it; production leaves it at -1. */
long kmalloc_fail_after = -1;

/* Heap exhaustion is reported on the serial line where it happens (the
 * failure paths report rule): a caller turning NULL into -ENOMEM, a fork
 * refusal or a killed process otherwise hides that the 192 MB heap ran
 * out. Serial only (safe from fault context); every KMALLOC_REPORT_EVERY
 * failures after the first to keep a storm readable. */
#define KMALLOC_REPORT_EVERY 64UL
static unsigned long kmalloc_failures;

static void kmalloc_report_failure(unsigned long size) {
    static const char digits[] = "0123456789";
    char num[24];
    int n = 0;
    unsigned long v = size;
    kmalloc_failures++;
    if (kmalloc_failures != 1 && kmalloc_failures % KMALLOC_REPORT_EVERY != 0) return;
    do { num[n++] = digits[v % 10]; v /= 10; } while (v && n < 23);
    serial_puts("kheap: allocation of ");
    while (n > 0) { char c[2]; c[0] = num[--n]; c[1] = 0; serial_puts(c); }
    serial_puts(" bytes failed (kernel heap exhausted)\n");
}

void *kmalloc(unsigned long size) {
    void *p;
    if (size == 0) return 0;
    if (kmalloc_fail_after == 0) return 0;
    if (kmalloc_fail_after > 0) kmalloc_fail_after--;
    p = dlmalloc_malloc(size);
    if (!p) kmalloc_report_failure(size);
    return p;
}

/* One page-aligned heap page (the page-table and user-page allocator's
 * backing). memalign keeps the cost at one page plus a chunk header,
 * where over-allocating to align cost two pages per page and halved the
 * user memory the heap could back. Same fault injection and reporting as
 * kmalloc. */
void *kmalloc_page(void) {
    void *p;
    if (kmalloc_fail_after == 0) return 0;
    if (kmalloc_fail_after > 0) kmalloc_fail_after--;
    p = dlmalloc_memalign(KMALLOC_PAGE, KMALLOC_PAGE);
    if (!p) kmalloc_report_failure(KMALLOC_PAGE);
    return p;
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
