/** Docstring: bump arena for MiniOS, kernel and ring-3 alike.
 *
 * A bump arena serves one kmalloc (kernel) or malloc (ring-3) with pointer
 * bumps instead of N allocator round trips, then releases the whole scope
 * with a single free. That is the exact shape of the per-keypress churn
 * behind the file -> vedit -> Ctrl+R / Ctrl+L heap drain: spawn argv
 * copies, redirect captures and insert scratch buffers are born together
 * and die together, so freeing them one by one fragments the dlmalloc
 * heap and turns any missed free into a cumulative leak that finally
 * starves MiniFS writes. An arena makes the scope atomic by construction:
 * one backing block, many borrows, one release.
 *
 * Backend agnostic on purpose: the caller owns the backing store (kmalloc
 * in the kernel, malloc in ring-3 or host tests) and hands it to
 * arena_init. No allocation happens inside this header, so it compiles
 * freestanding (-ffreestanding, no libc) as well as hosted. Only
 * <stddef.h> is needed.
 *
 * Typical kernel scope:
 *   unsigned char *back = kmalloc(total);
 *   arena_t a;
 *   arena_init(&a, back, total);
 *   kargv = arena_alloc(&a, nptr, sizeof(char *));
 *   ... bump each string ...
 *   kfree(back);
 *
 * Alignment defaults to 8 bytes when the caller passes 0. Every size sum
 * is overflow checked and fails closed with a null return, never a wrap.
 * Arenas are not thread safe; one arena per CPU or per syscall scope.
 */

#ifndef MINIOS_ARENA_H
#define MINIOS_ARENA_H

#include <stddef.h>

/** Docstring: default borrow alignment when the caller passes align 0. */
#define ARENA_DEFAULT_ALIGN 8u

/** Docstring: one bump scope over a caller-owned backing block. */
typedef struct minios_arena {
    unsigned char *base;
    unsigned char *cur;
    unsigned char *end;
} arena_t;

/** Docstring: bind an arena to a backing block, empty when block is null. */
static inline void arena_init(arena_t *a, void *block, size_t size) {
    if (!a) return;
    if (!block || size == 0) {
        a->base = 0;
        a->cur = 0;
        a->end = 0;
        return;
    }
    a->base = (unsigned char *)block;
    a->cur = (unsigned char *)block;
    a->end = (unsigned char *)block + size;
}

/** Docstring: round n up to align, 0 on overflow or non-power-of-two align. */
static inline size_t arena_align_up(size_t n, size_t align) {
    size_t mask;
    size_t up;
    if (align == 0) align = ARENA_DEFAULT_ALIGN;
    if (align & (align - 1)) return 0;
    mask = align - 1;
    if (n > (size_t)-1 - mask) return 0;
    up = (n + mask) & ~mask;
    return up;
}

/** Docstring: overflow checked bytes for count items of elem_size. */
static inline size_t arena_bytes_for(size_t count, size_t elem_size) {
    if (count == 0 || elem_size == 0) return 0;
    if (count > (size_t)-1 / elem_size) return 0;
    return count * elem_size;
}

/** Docstring: borrow size bytes at align, null when the scope is exhausted. */
static inline void *arena_alloc(arena_t *a, size_t size, size_t align) {
    size_t off;
    size_t up;
    if (!a || !a->base || size == 0) return 0;
    off = (size_t)(a->cur - a->base);
    up = arena_align_up(off, align);
    if (up == 0 && off != 0) return 0;
    if (up > (size_t)(a->end - a->base)) return 0;
    if (size > (size_t)(a->end - a->base) - up) return 0;
    a->cur = a->base + up + size;
    return a->base + up;
}

/** Docstring: bytes borrowed so far, 0 for a null or empty arena. */
static inline size_t arena_used(const arena_t *a) {
    if (!a || !a->base) return 0;
    return (size_t)(a->cur - a->base);
}

/** Docstring: bytes still borrowable, 0 for a null or empty arena. */
static inline size_t arena_free_bytes(const arena_t *a) {
    if (!a || !a->base) return 0;
    return (size_t)(a->end - a->cur);
}

/** Docstring: rewind the scope to empty without releasing the backing block. */
static inline void arena_reset(arena_t *a) {
    if (!a) return;
    a->cur = a->base;
}

/** Docstring: bookmark the cursor for a later partial rewind. */
static inline size_t arena_checkpoint(const arena_t *a) {
    if (!a || !a->base) return 0;
    return (size_t)(a->cur - a->base);
}

/** Docstring: rewind to a checkpoint, -1 when the mark is out of range. */
static inline int arena_rewind(arena_t *a, size_t checkpoint) {
    if (!a || !a->base) return -1;
    if (checkpoint > (size_t)(a->end - a->base)) return -1;
    if (checkpoint > (size_t)(a->cur - a->base)) return -1;
    a->cur = a->base + checkpoint;
    return 0;
}

/** Docstring: true when ptr lies inside the backing block. */
static inline int arena_contains(const arena_t *a, const void *ptr) {
    const unsigned char *p = (const unsigned char *)ptr;
    if (!a || !a->base || !p) return 0;
    return p >= a->base && p < a->end;
}

#endif
