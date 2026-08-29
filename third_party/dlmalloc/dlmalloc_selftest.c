/* dlmalloc_selftest.c - ring-0 ET_REL self-test for the kernel allocator.
 *
 * The kernel's kmalloc/free/calloc/realloc are backed by a private dlmalloc
 * mspace over the fixed heap (third_party/dlmalloc). The libc names are
 * registered against the kernel table, so this object exercises the real
 * allocator through those symbols: a burst of allocations, a realloc that
 * grows and one that shrinks, a calloc that must be zeroed, a free that
 * must not corrupt a live neighbour, and a large allocation near the heap
 * ceiling to prove bounded growth still returns a pointer (or 0 cleanly).
 * Fails closed on any mismatch.
 *
 * Build: gcc -c -ffreestanding -m64 -mno-red-zone -fno-pic -o objects/dlmalloc.o dlmalloc_selftest.c
 * (host gcc, not miniGCC - the symbols resolve against the kernel table at load.)
 * Ship on the ramdisk as objects/dlmalloc.o.
 * Usage: run objects/dlmalloc.o
 */
#include <stdint.h>

extern void *malloc(unsigned long size);
extern void *calloc(unsigned long nmemb, unsigned long size);
extern void *realloc(void *ptr, unsigned long size);
extern void  free(void *ptr);
extern int printf(const char *fmt, ...);

static int fails;

static void check(int cond, const char *what) {
    if (!cond) { printf("dlmalloc: %s FAIL\n", what); fails = 1; }
}

int main(void) {
    int i;
    char *a[64];
    char *p, *q, *z;

    for (i = 0; i < 64; i++) {
        a[i] = (char *)malloc((unsigned long)(i * 7 + 1));
        check(a[i] != 0, "burst malloc");
        if (a[i]) a[i][0] = (char)i;
    }

    p = (char *)malloc(16);
    check(p != 0, "malloc");
    if (p) { p[0] = 'x'; p[15] = 'y'; }

    q = (char *)realloc(p, 4096);   /* grow */
    check(q != 0, "realloc grow");
    if (q) { check(q[0] == 'x' && q[15] == 'y', "realloc copy"); }
    q = (char *)realloc(q, 8);      /* shrink */
    check(q != 0, "realloc shrink");

    z = (char *)calloc(4, 8);
    check(z != 0, "calloc");
    if (z) check(z[0] == 0 && z[15] == 0 && z[31] == 0, "calloc zeroed");

    free(q);
    free(z);

    for (i = 0; i < 64; i++) {
        check(a[i][0] == (char)i, "burst integrity");
        free(a[i]);
    }

    /* Large allocation near the ceiling: must return a pointer or 0, never
     * corrupt memory or hang. */
    p = (char *)malloc(8UL * 1024 * 1024);
    free(p);

    if (fails) { printf("dlmalloc: selftest FAIL\n"); return 1; }
    printf("dlmalloc: ok (alloc/realloc/calloc/free)\n");
    return 0;
}
