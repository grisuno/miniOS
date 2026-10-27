#include "kernel.h"

/* string.c -- Kernel string and memory functions.
 *
 * Pure functions with no dependencies beyond their own prototypes in
 * kernel.h.  These replace the libc equivalents for the freestanding
 * kernel and are also registered as kernel symbols for ET_REL programs.
 *
 * Contract:
 *   All functions handle NUL-terminated strings or fixed-size buffers.
 *   kmemmove handles overlapping regions correctly (copy forward when
 *   dst < src, backward when dst > src).
 *   kstrncpy does NOT NUL-pad; the caller must ensure the destination
 *   is already zeroed if NUL-termination is required.
 */

unsigned long kstrlen(const char *s) {
    const char *p = s;
    while (*p) p++;
    return (unsigned long)(p - s);
}

char *kstrcpy(char *dst, const char *src) {
    char *d = dst;
    while ((*d++ = *src++));
    return dst;
}

char *kstrncpy(char *dst, const char *src, unsigned long n) {
    char *d = dst;
    while (n-- && (*d++ = *src++));
    return dst;
}

char *kstrncat(char *dst, const char *src, unsigned long n) {
    char *d = dst;
    while (*d) d++;
    while (n-- && *src) *d++ = *src++;
    *d = 0;
    return dst;
}

int kstrcmp(const char *a, const char *b) {
    while (*a && *a == *b) { a++; b++; }
    return (unsigned char)*a - (unsigned char)*b;
}

int kstrncmp(const char *a, const char *b, unsigned long n) {
    while (n-- && *a && *a == *b) { a++; b++; }
    return n == (unsigned long)-1 ? 0 : (unsigned char)*a - (unsigned char)*b;
}

char *kstrchr(const char *s, int c) {
    while (*s) { if (*s == (char)c) return (char *)s; s++; }
    return 0;
}

char *kstrstr(const char *hay, const char *ndl) {
    unsigned long nl = kstrlen(ndl);
    if (nl == 0) return (char *)hay;
    while (*hay) {
        if (kstrncmp(hay, ndl, nl) == 0) return (char *)hay;
        hay++;
    }
    return 0;
}

#define NO_LOOP_IDIOM __attribute__((optimize("no-tree-loop-distribute-patterns")))

/** Docstring: Byte copy. Immune to loop-idiom recognition, which would turn
 * the loop back into a call to memcpy and recurse through the wrappers
 * below. */
NO_LOOP_IDIOM void *kmemcpy(void *dst, const void *src, unsigned long n) {
    char *d = dst;
    const char *s = src;
    while (n--) *d++ = *s++;
    return dst;
}

NO_LOOP_IDIOM void *kmemset(void *dst, int c, unsigned long n) {
    char *d = dst;
    while (n--) *d++ = (char)c;
    return dst;
}

int kmemcmp(const void *a, const void *b, unsigned long n) {
    const unsigned char *pa = a, *pb = b;
    while (n--) { if (*pa != *pb) return *pa - *pb; pa++; pb++; }
    return 0;
}

NO_LOOP_IDIOM void *kmemmove(void *dst, const void *src, unsigned long n) {
    char *d = dst;
    const char *s = src;
    if (d < s) { while (n--) *d++ = *s++; }
    else       { d += n; s += n; while (n--) *--d = *--s; }
    return dst;
}

/** Docstring: ISO C entry points the compiler itself emits calls to for
 * struct copies and large initializers, even under -ffreestanding. Thin
 * wrappers over the kernel primitives so the link never depends on the
 * optimizer inlining them. */
void *memcpy(void *dst, const void *src, unsigned long n) {
    return kmemcpy(dst, src, n);
}

void *memmove(void *dst, const void *src, unsigned long n) {
    return kmemmove(dst, src, n);
}

void *memset(void *dst, int c, unsigned long n) {
    return kmemset(dst, c, n);
}

int memcmp(const void *a, const void *b, unsigned long n) {
    return kmemcmp(a, b, n);
}

long katol(const char *s) {
    long v = 0, sign = 1;
    while (*s == ' ') s++;
    if (*s == '-') { sign = -1; s++; }
    else if (*s == '+') s++;
    while (*s >= '0' && *s <= '9') { v = v * 10 + (*s - '0'); s++; }
    return v * sign;
}
