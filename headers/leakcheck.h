/** Docstring: allocation tracker for MiniOS, STB leakcheck lineage.
 *
 * Every malloc/free/realloc spelled after this header (with
 * MINIOS_LK_ENABLE) records its file and line in a doubly linked table,
 * so lk_dumpmem prints each block that was never released. That is the
 * instrument the file -> vedit -> Ctrl+R / Ctrl+L drain needed: the
 * tracker was floating around as a paste but never wired in, and the
 * cumulative per-keypress growth went unnoticed until MiniFS writes
 * started failing. Include this header last in the translation unit so
 * the override macros also cover allocator calls inside implementation
 * headers such as stb_image.
 *
 * Two backends, selected before the include:
 *   hosted (default): raw malloc/free/realloc, report on stdout.
 *   kernel (MINIOS_LK_KERNEL): raw kmalloc/kfree plus kprintf.
 * The kernel backend is explicit instrumentation for a scope, never a
 * global override: wrapping kmalloc itself would drown the report in
 * permanent caches such as the redirect buffer.
 *
 * One translation unit per binary defines MINIOS_LEAKCHECK_IMPL.
 * Unknown pointers passed to lk_free are released through the raw
 * backend instead of faulting, so tracked code can free blocks that a
 * non-instrumented unit allocated. Not thread safe; ring-3 and host
 * tests only, or kernel code with the owner lock held.
 */

#ifndef MINIOS_LEAKCHECK_H
#define MINIOS_LEAKCHECK_H

#include <stddef.h>

/** Docstring: hosted includes come first so later override macros never
 * rewrite the libc declarations themselves; include this header last
 * in the translation unit as a second fence. */
#ifndef MINIOS_LK_KERNEL
#include <stdlib.h>
#include <stdio.h>
#endif

#ifndef MINIOS_LK_PIPE
#ifdef MINIOS_LK_KERNEL
#define MINIOS_LK_PIPE 0
#else
#define MINIOS_LK_PIPE stdout
#endif
#endif

/** Docstring: one live allocation record, intrusive list node. */
typedef struct lk_block lk_block_t;
struct lk_block {
    const char *file;
    int line;
    size_t size;
    lk_block_t *next;
    lk_block_t *prev;
};

/** Docstring: tracked malloc, records caller file and line. */
extern void *lk_malloc(size_t size, const char *file, int line);

/** Docstring: tracked free, passes unknown blocks to the raw backend. */
extern void lk_free(void *ptr);

/** Docstring: tracked realloc, preserves bytes across a tracked move. */
extern void *lk_realloc(void *ptr, size_t size, const char *file, int line);

/** Docstring: report every block still live, newest first. */
extern void lk_dumpmem(void);

/** Docstring: count of blocks still live. */
extern unsigned long lk_live_count(void);

/** Docstring: payload bytes still live. */
extern unsigned long lk_live_bytes(void);

#ifdef MINIOS_LEAKCHECK_IMPL

#ifdef MINIOS_LK_KERNEL
extern void *kmalloc(unsigned long size);
extern void kfree(void *ptr);
extern int kprintf(const char *fmt, ...);
#define MINIOS_LK_RAW_ALLOC(sz) kmalloc((unsigned long)(sz))
#define MINIOS_LK_RAW_FREE(p) kfree(p)
#else
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MINIOS_LK_RAW_ALLOC(sz) malloc(sz)
#define MINIOS_LK_RAW_FREE(p) free(p)
#endif

/** Docstring: head of the live-block list, newest allocation first. */
static lk_block_t *lk_head;

/** Docstring: tracked malloc, records caller file and line. */
void *lk_malloc(size_t size, const char *file, int line) {
    lk_block_t *b = (lk_block_t *)MINIOS_LK_RAW_ALLOC(size + sizeof(*b));
    if (b == 0) return 0;
    b->file = file;
    b->line = line;
    b->size = size;
    b->next = lk_head;
    b->prev = 0;
    if (lk_head) lk_head->prev = b;
    lk_head = b;
    return b + 1;
}

/** Docstring: unlink one record from the live-block list. */
static void lk_unlink(lk_block_t *b) {
    if (b->prev == 0) {
        lk_head = b->next;
    } else {
        b->prev->next = b->next;
    }
    if (b->next) b->next->prev = b->prev;
}

/** Docstring: find the record owning ptr by scanning for its payload base. */
static lk_block_t *lk_find(void *ptr) {
    lk_block_t *b = lk_head;
    while (b) {
        if ((void *)(b + 1) == ptr) return b;
        b = b->next;
    }
    return 0;
}

/** Docstring: tracked free, passes unknown blocks to the raw backend. */
void lk_free(void *ptr) {
    lk_block_t *b;
    if (ptr == 0) return;
    b = lk_find(ptr);
    if (b == 0) {
        MINIOS_LK_RAW_FREE(ptr);
        return;
    }
    lk_unlink(b);
    MINIOS_LK_RAW_FREE(b);
}

/** Docstring: tracked realloc, preserves bytes across a tracked move. */
void *lk_realloc(void *ptr, size_t size, const char *file, int line) {
    lk_block_t *b;
    void *q;
    unsigned char *d;
    unsigned char *s;
    size_t k;
    size_t keep;
    if (ptr == 0) return lk_malloc(size, file, line);
    if (size == 0) {
        lk_free(ptr);
        return 0;
    }
    b = lk_find(ptr);
    if (b == 0) {
        q = MINIOS_LK_RAW_ALLOC(size + sizeof(*b));
        if (q == 0) return 0;
        b = (lk_block_t *)q;
        b->file = file;
        b->line = line;
        b->size = size;
        b->next = lk_head;
        b->prev = 0;
        if (lk_head) lk_head->prev = b;
        lk_head = b;
        return b + 1;
    }
    if (size <= b->size) {
        b->file = file;
        b->line = line;
        return ptr;
    }
    q = lk_malloc(size, file, line);
    if (q) {
        d = (unsigned char *)q;
        s = (unsigned char *)ptr;
        keep = b->size;
        for (k = 0; k < keep; k++) d[k] = s[k];
        lk_free(ptr);
    }
    return q;
}

/** Docstring: print one live record on the configured pipe. */
static void lk_print(const char *reason, const lk_block_t *b) {
#ifdef MINIOS_LK_KERNEL
    kprintf("%s: %s (%d): %lu bytes\n", reason, b->file, b->line,
        (unsigned long)b->size);
#else
    fprintf(MINIOS_LK_PIPE, "%s: %s (%d): %lu bytes at %p\n", reason,
        b->file, b->line, (unsigned long)b->size, (const void *)(b + 1));
#endif
}

/** Docstring: report every block still live, newest first. */
void lk_dumpmem(void) {
    lk_block_t *b = lk_head;
    while (b) {
        lk_print("LEAKED", b);
        b = b->next;
    }
}

/** Docstring: count of blocks still live. */
unsigned long lk_live_count(void) {
    unsigned long n = 0;
    lk_block_t *b = lk_head;
    while (b) {
        n++;
        b = b->next;
    }
    return n;
}

/** Docstring: payload bytes still live. */
unsigned long lk_live_bytes(void) {
    unsigned long n = 0;
    lk_block_t *b = lk_head;
    while (b) {
        n += (unsigned long)b->size;
        b = b->next;
    }
    return n;
}

#endif

#ifdef MINIOS_LK_ENABLE
#ifdef malloc
#undef malloc
#undef free
#undef realloc
#endif
#define malloc(sz) lk_malloc((sz), __FILE__, __LINE__)
#define free(p) lk_free(p)
#define realloc(p, sz) lk_realloc((p), (sz), __FILE__, __LINE__)
#endif

#endif
