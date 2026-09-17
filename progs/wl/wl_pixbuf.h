/** Docstring: heap pixel store for the Wayland-mini server.
 *
 * Ring-3 only contract replacing the former static server pool
 * wlserv_pool[WL_MAX_SURFACES][WL_POOL_MAX] plus two fixed scratch
 * buffers. Each slot allocates exactly w*h bytes on attach or resize
 * instead of a full 288000 byte reservation, so small clients pay
 * small and the server binary no longer carries megabytes of static
 * pixels. A global byte budget bounds total allocation so hostile
 * geometry can never drive unbounded growth. Steady state allocates
 * nothing: reallocation happens only when a slot geometry changes.
 * Every failure preserves the old pixels and reports -1, so one bad
 * client degrades to solid ink exactly as before.
 * Include wl_mini.h before this header for the protocol bounds.
 */

#ifndef MINIOS_WL_PIXBUF_H
#define MINIOS_WL_PIXBUF_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifndef WL_MAX_SURFACES
#error "include wl_mini.h before wl_pixbuf.h"
#endif

#ifndef WPIX_MAX_SLOTS
#define WPIX_MAX_SLOTS WL_MAX_SURFACES
#endif

#ifndef WPIX_MAX_W
#define WPIX_MAX_W WL_SURF_MAX_W
#endif

#ifndef WPIX_MAX_H
#define WPIX_MAX_H WL_SURF_MAX_H
#endif

#ifndef WPIX_SLOT_MAX
#define WPIX_SLOT_MAX WL_POOL_MAX
#endif

#ifndef WPIX_BUDGET_MAX
#define WPIX_BUDGET_MAX (WL_MAX_SURFACES * WL_POOL_MAX)
#endif

/** Docstring: one slot cache, empty when p is null or w*h is zero. */
struct wpix_slot {
    unsigned char *p;
    int w;
    int h;
};

/** Docstring: slot caches plus one reusable raw/decode scratch pair. */
struct wpix_store {
    struct wpix_slot slots[WPIX_MAX_SLOTS];
    unsigned char *tmp_raw;
    unsigned char *tmp_dst;
    size_t tmp_cap;
};

/** Docstring: zero init every slot and scratch pointer. */
static int wpix_init(struct wpix_store *s) {
    size_t k = 0;
    if (s == NULL) return -1;
    for (k = 0; k < (size_t)WPIX_MAX_SLOTS; k++) {
        s->slots[k].p = NULL;
        s->slots[k].w = 0;
        s->slots[k].h = 0;
    }
    s->tmp_raw = NULL;
    s->tmp_dst = NULL;
    s->tmp_cap = 0;
    return 0;
}

/** Docstring: release every slot and scratch buffer, back to zero init. */
static void wpix_free(struct wpix_store *s) {
    size_t k = 0;
    if (s == NULL) return;
    for (k = 0; k < (size_t)WPIX_MAX_SLOTS; k++) {
        free(s->slots[k].p);
        s->slots[k].p = NULL;
        s->slots[k].w = 0;
        s->slots[k].h = 0;
    }
    free(s->tmp_raw);
    free(s->tmp_dst);
    s->tmp_raw = NULL;
    s->tmp_dst = NULL;
    s->tmp_cap = 0;
}

/** Docstring: live pixel bytes held across all slots. */
static size_t wpix_used(const struct wpix_store *s) {
    size_t k = 0;
    size_t n = 0;
    if (s == NULL) return 0;
    for (k = 0; k < (size_t)WPIX_MAX_SLOTS; k++) {
        if (s->slots[k].p != NULL && s->slots[k].w > 0 && s->slots[k].h > 0)
            n += (size_t)s->slots[k].w * (size_t)s->slots[k].h;
    }
    return n;
}

/** Docstring: readable pixels for slot idx, null when empty or wild. */
static unsigned char *wpix_ptr(struct wpix_store *s, int idx) {
    if (s == NULL || idx < 0 || idx >= WPIX_MAX_SLOTS) return NULL;
    if (s->slots[idx].p == NULL || s->slots[idx].w <= 0 || s->slots[idx].h <= 0)
        return NULL;
    return s->slots[idx].p;
}

/** Docstring: raw scratch for mailbox file reads, null below capacity. */
static unsigned char *wpix_raw(struct wpix_store *s) {
    if (s == NULL) return NULL;
    return s->tmp_raw;
}

/** Docstring: decode scratch for resampled cells, null below capacity. */
static unsigned char *wpix_dst(struct wpix_store *s) {
    if (s == NULL) return NULL;
    return s->tmp_dst;
}

/** Docstring: drop slot pixels and release its memory to the budget. */
static void wpix_drop(struct wpix_store *s, int idx) {
    if (s == NULL || idx < 0 || idx >= WPIX_MAX_SLOTS) return;
    free(s->slots[idx].p);
    s->slots[idx].p = NULL;
    s->slots[idx].w = 0;
    s->slots[idx].h = 0;
}

/** Docstring: grow both scratch buffers to need bytes, old kept on failure. */
static int wpix_tmp(struct wpix_store *s, size_t need) {
    unsigned char *nr = NULL;
    unsigned char *nd = NULL;
    if (s == NULL) return -1;
    if (need == 0 || need > (size_t)WPIX_SLOT_MAX) return -1;
    if (s->tmp_cap >= need) return 0;
    nr = (unsigned char *)realloc(s->tmp_raw, need);
    if (nr == NULL) return -1;
    s->tmp_raw = nr;
    nd = (unsigned char *)realloc(s->tmp_dst, need);
    if (nd == NULL) return -1;
    s->tmp_dst = nd;
    s->tmp_cap = need;
    return 0;
}

/** Docstring: size slot idx for w*h cells inside bounds and budget. */
static int wpix_ensure(struct wpix_store *s, int idx, int w, int h) {
    size_t cells = 0;
    size_t old = 0;
    unsigned char *np = NULL;
    if (s == NULL || idx < 0 || idx >= WPIX_MAX_SLOTS) return -1;
    if (w <= 0 || h <= 0 || w > WPIX_MAX_W || h > WPIX_MAX_H) return -1;
    cells = (size_t)w * (size_t)h;
    if (cells == 0 || cells > (size_t)WPIX_SLOT_MAX) return -1;
    if (s->slots[idx].p != NULL && s->slots[idx].w == w && s->slots[idx].h == h)
        return 0;
    if (s->slots[idx].p != NULL && s->slots[idx].w > 0 && s->slots[idx].h > 0)
        old = (size_t)s->slots[idx].w * (size_t)s->slots[idx].h;
    if (wpix_used(s) - old + cells > (size_t)WPIX_BUDGET_MAX) return -1;
    np = (unsigned char *)realloc(s->slots[idx].p, cells);
    if (np == NULL) return -1;
    s->slots[idx].p = np;
    s->slots[idx].w = w;
    s->slots[idx].h = h;
    return 0;
}

/** Docstring: copy cells into a matching slot, fail closed on mismatch. */
static int wpix_commit(struct wpix_store *s, int idx, const unsigned char *src, int w, int h) {
    size_t cells = 0;
    if (s == NULL || src == NULL) return -1;
    if (idx < 0 || idx >= WPIX_MAX_SLOTS) return -1;
    if (w <= 0 || h <= 0) return -1;
    if (s->slots[idx].p == NULL || s->slots[idx].w != w || s->slots[idx].h != h)
        return -1;
    cells = (size_t)w * (size_t)h;
    if (cells > (size_t)WPIX_SLOT_MAX) return -1;
    memcpy(s->slots[idx].p, src, cells);
    return 0;
}

#endif
