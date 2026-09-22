#ifndef PCM_RING_H
#define PCM_RING_H

/* pcm_ring.h -- single-producer/single-consumer byte ring for PCM audio.
 *
 * BSD-style software buffer (cf. audio(4)): the writer (syscall context)
 * appends samples, the reader (the SB16 block-completion IRQ/poll path)
 * drains one DMA block at a time. Integer-only, no kernel dependencies,
 * no allocation: the caller owns the storage, so the same code runs in
 * the kernel (heap buffer) and on the host (malloc'd buffer, `make test-pcm`).
 *
 * Contract:
 * - `cap` is fixed at init; `count <= cap` always holds. A zero cap
 *   degrades every op to a no-op that counts the loss, never a divide
 *   by zero or an out-of-bounds access.
 * - write accepts what fits and counts the refused tail in `drops`
 *   (overrun is a counter, never a overwrite of unread data).
 * - read takes what is available, pads the shortfall with 0x80
 *   (unsigned 8-bit PCM silence) and counts one `underrun` per short
 *   read (underrun is a counter, never a stall: the DMA engine must
 *   never wait).
 * - wrap arithmetic never indexes outside [0, cap): head/tail advance
 *   modulo cap one byte at a time on the copy path.
 */

typedef struct {
    unsigned char *buf;
    unsigned cap;
    unsigned head;
    unsigned tail;
    unsigned count;
    unsigned long drops;
    unsigned long underruns;
} pcm_ring_t;

static inline void pcm_ring_init(pcm_ring_t *r, unsigned char *buf,
                                 unsigned cap) {
    r->buf = buf;
    r->cap = cap;
    r->head = 0;
    r->tail = 0;
    r->count = 0;
    r->drops = 0;
    r->underruns = 0;
}

static inline unsigned pcm_ring_used(const pcm_ring_t *r) {
    return r->count;
}

static inline unsigned pcm_ring_free(const pcm_ring_t *r) {
    return (r->cap >= r->count) ? (r->cap - r->count) : 0;
}

static inline unsigned pcm_ring_write(pcm_ring_t *r, const unsigned char *src,
                                      unsigned len) {
    unsigned i, space;
    if (!r || !src || r->cap == 0 || !r->buf) {
        if (r) r->drops += len;
        return 0;
    }
    space = (r->cap >= r->count) ? (r->cap - r->count) : 0;
    if (len > space) {
        r->drops += (unsigned long)(len - space);
        len = space;
    }
    for (i = 0; i < len; i++) {
        r->buf[r->head] = src[i];
        r->head++;
        if (r->head >= r->cap) r->head = 0;
    }
    r->count += len;
    return len;
}

static inline unsigned pcm_ring_read(pcm_ring_t *r, unsigned char *dst,
                                     unsigned len) {
    unsigned i, taken;
    if (!r || !dst || r->cap == 0 || !r->buf) {
        if (r) r->underruns++;
        return 0;
    }
    taken = (r->count < len) ? r->count : len;
    for (i = 0; i < taken; i++) {
        dst[i] = r->buf[r->tail];
        r->tail++;
        if (r->tail >= r->cap) r->tail = 0;
    }
    if (taken < len) {
        unsigned j;
        for (j = taken; j < len; j++) dst[j] = 0x80;
        r->underruns++;
    }
    r->count -= taken;
    return taken;
}

#endif
