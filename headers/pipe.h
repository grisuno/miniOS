/** Docstring: pipe.h -- Kernel pipe ring contract (header-only).
 *
 * Single source of truth for the pipe byte ring shared by the kernel
 * pipe ends (fs/kfile.c), the pipe/dup/dup2 syscalls (kernel/syscalls.c)
 * and the shell pipeline runner (kernel/shell.c). Header-only like
 * wm_geom.h and wl_mini.h: the core is pure integer arithmetic over a
 * caller-owned buffer, so tests/test_pipe.c (make test-pipe) drives it
 * on the host with no kernel stubs.
 *
 * Semantics:
 * Two ends share one ring. The write end appends, the read end drains.
 * A read on an empty ring whose writer is still open reports PIPE_EMPTY
 * (the caller yields and retries, EAGAIN-style); a read on an empty
 * ring whose writer closed reports 0 (EOF). A write that does not fit
 * reports the bytes actually stored (partial, never overrun). Every
 * bound fails closed with PIPE_ERR_*, never truncates. */

#ifndef PIPE_H
#define PIPE_H

#define PIPE_CAP_DEFAULT 4096u
#define PIPE_CAP_MAX     65536u

#define PIPE_ERR_BOUND (-1)
#define PIPE_EMPTY     (-2)

typedef struct {
    unsigned char *buf;
    unsigned cap;
    unsigned head;
    unsigned tail;
    unsigned count;
    int wopen;
} pipe_ring_t;

typedef struct {
    unsigned cap;
    unsigned count;
    int wopen;
} pipe_cfg_t;

#define PIPE_CFG_DEFAULT { PIPE_CAP_DEFAULT, 0u, 1 }

/** Docstring: Bind a caller-owned buffer to a ring. Fails closed on a
 * null buffer or a zero/oversize capacity. */
static inline int pipe_ring_init(pipe_ring_t *r, unsigned char *buf,
        unsigned cap) {
    if (!r || !buf)
        return PIPE_ERR_BOUND;
    if (cap == 0u || cap > PIPE_CAP_MAX)
        return PIPE_ERR_BOUND;
    r->buf = buf;
    r->cap = cap;
    r->head = 0u;
    r->tail = 0u;
    r->count = 0u;
    r->wopen = 1;
    return 0;
}

/** Docstring: Bytes available to read. Zero on a null ring. */
static inline unsigned pipe_ring_avail(const pipe_ring_t *r) {
    if (!r || !r->buf)
        return 0u;
    return r->count;
}

/** Docstring: Free space available to write. Zero on a null ring. */
static inline unsigned pipe_ring_space(const pipe_ring_t *r) {
    if (!r || !r->buf)
        return 0u;
    return r->cap - r->count;
}

/** Docstring: Append up to len bytes, return bytes stored. Partial on a
 * full ring, never overrun. Zero on null input or a closed writer. */
static inline unsigned pipe_ring_write(pipe_ring_t *r,
        const unsigned char *src, unsigned len) {
    unsigned i;
    if (!r || !r->buf || !src)
        return 0u;
    if (!r->wopen)
        return 0u;
    for (i = 0u; i < len && r->count < r->cap; i++) {
        r->buf[r->tail] = src[i];
        r->tail++;
        if (r->tail >= r->cap)
            r->tail = 0u;
        r->count++;
    }
    return i;
}

/** Docstring: Drain up to len bytes, return bytes read. PIPE_EMPTY when
 * empty with the writer open (retry later), 0 when empty with the
 * writer closed (EOF). Never reads past the stored bytes. */
static inline int pipe_ring_read(pipe_ring_t *r, unsigned char *dst,
        unsigned len) {
    unsigned i;
    if (!r || !r->buf || !dst)
        return PIPE_ERR_BOUND;
    if (r->count == 0u)
        return r->wopen ? PIPE_EMPTY : 0;
    for (i = 0u; i < len && r->count > 0u; i++) {
        dst[i] = r->buf[r->head];
        r->head++;
        if (r->head >= r->cap)
            r->head = 0u;
        r->count--;
    }
    return (int)i;
}

/** Docstring: Mark the writer closed. Later reads drain then report EOF.
 * Idempotent; null ring is a no-op returning PIPE_ERR_BOUND. */
static inline int pipe_ring_close_writer(pipe_ring_t *r) {
    if (!r)
        return PIPE_ERR_BOUND;
    r->wopen = 0;
    return 0;
}

/** Docstring: Snapshot ring geometry into a caller struct. Fail-closed
 * on null input. */
static inline int pipe_ring_stat(const pipe_ring_t *r, pipe_cfg_t *out) {
    if (!r || !out)
        return PIPE_ERR_BOUND;
    out->cap = r->cap;
    out->count = r->count;
    out->wopen = r->wopen;
    return 0;
}

#endif
