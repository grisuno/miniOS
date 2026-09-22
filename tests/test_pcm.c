/* Host-side unit test for the PCM ring buffer (headers/pcm_ring.h).
 *
 * The ring is integer-only and free of kernel dependencies, so it is
 * exercised directly here against the host libc. The test pins the
 * observable contract (write/read, wrap, overrun drops, underrun pad,
 * zero-cap fail-closed) plus a deterministic interleaved model run, so
 * a mutant that breaks the index arithmetic or the loss counters dies
 * even when the plain roundtrip still looks correct.
 *
 * Run through `make test-pcm`.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pcm_ring.h"

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

static void t_roundtrip(void) {
    unsigned char mem[16];
    unsigned char out[16];
    unsigned char in[16];
    unsigned i;
    pcm_ring_t r;
    for (i = 0; i < 16; i++) in[i] = (unsigned char)(i + 1);
    pcm_ring_init(&r, mem, 16);
    CHECK(pcm_ring_write(&r, in, 16) == 16, "full write accepted");
    CHECK(pcm_ring_used(&r) == 16, "used counts full");
    CHECK(pcm_ring_free(&r) == 0, "free counts empty");
    CHECK(pcm_ring_read(&r, out, 16) == 16, "full read taken");
    CHECK(memcmp(in, out, 16) == 0, "bytes survive roundtrip");
    CHECK(pcm_ring_used(&r) == 0, "drained to zero");
}

static void t_wrap(void) {
    unsigned char mem[8];
    unsigned char out[8];
    unsigned char a[6] = {1, 2, 3, 4, 5, 6};
    unsigned char b[6] = {7, 8, 9, 10, 11, 12};
    pcm_ring_t r;
    pcm_ring_init(&r, mem, 8);
    CHECK(pcm_ring_write(&r, a, 6) == 6, "wrap: first write");
    CHECK(pcm_ring_read(&r, out, 4) == 4, "wrap: first read");
    CHECK(memcmp(out, a, 4) == 0, "wrap: order kept");
    CHECK(pcm_ring_write(&r, b, 6) == 6, "wrap: second write fits");
    CHECK(pcm_ring_read(&r, out, 8) == 8, "wrap: drain crosses origin");
    CHECK(out[0] == 5 && out[1] == 6, "wrap: tail of first kept");
    CHECK(out[2] == 7 && out[7] == 12, "wrap: second kept in order");
    CHECK(pcm_ring_used(&r) == 0, "wrap: empty after drain");
}

static void t_overrun(void) {
    unsigned char mem[4];
    unsigned char out[4];
    unsigned char in[6] = {1, 2, 3, 4, 5, 6};
    pcm_ring_t r;
    pcm_ring_init(&r, mem, 4);
    CHECK(pcm_ring_write(&r, in, 6) == 4, "overrun: fits what fits");
    CHECK(r.drops == 2, "overrun: refused tail counted");
    CHECK(pcm_ring_read(&r, out, 4) == 4, "overrun: kept head read");
    CHECK(out[0] == 1 && out[3] == 4, "overrun: unread data intact");
    CHECK(pcm_ring_write(&r, in, 6) == 4, "overrun: reusable after drain");
    CHECK(r.drops == 4, "overrun: drops accumulate");
}

static void t_underrun(void) {
    unsigned char mem[8];
    unsigned char out[6];
    unsigned char in[2] = {0x10, 0x20};
    unsigned i;
    pcm_ring_t r;
    pcm_ring_init(&r, mem, 8);
    CHECK(pcm_ring_write(&r, in, 2) == 2, "underrun: short write");
    CHECK(pcm_ring_read(&r, out, 6) == 2, "underrun: short taken");
    CHECK(out[0] == 0x10 && out[1] == 0x20, "underrun: bytes kept");
    for (i = 2; i < 6; i++)
        CHECK(out[i] == 0x80, "underrun: silence pad is 0x80");
    CHECK(r.underruns == 1, "underrun: counted once");
    CHECK(pcm_ring_used(&r) == 0, "underrun: drained");
}

static void t_zero_cap(void) {
    unsigned char out[4] = {9, 9, 9, 9};
    unsigned char in[4] = {1, 2, 3, 4};
    pcm_ring_t r;
    pcm_ring_init(&r, out, 0);
    CHECK(pcm_ring_write(&r, in, 4) == 0, "zero cap: write refuses");
    CHECK(r.drops == 4, "zero cap: loss counted");
    CHECK(pcm_ring_read(&r, out, 4) == 0, "zero cap: read refuses");
    CHECK(r.underruns == 1, "zero cap: underrun counted");
    CHECK(out[0] == 9, "zero cap: buffer untouched");
}

static unsigned lcg_state = 0x12345678u;
static unsigned lcg_next(void) {
    lcg_state = lcg_state * 1664525u + 1013904223u;
    return (lcg_state >> 16) & 0x7FFFu;
}

static void t_model(void) {
    unsigned char mem[32];
    unsigned char shadow[64];
    unsigned char tmp[40];
    unsigned char src[40];
    unsigned shadow_len = 0;
    unsigned step;
    pcm_ring_t r;
    unsigned i;
    pcm_ring_init(&r, mem, 32);
    for (i = 0; i < 40; i++) src[i] = (unsigned char)(i + 1);
    for (step = 0; step < 300; step++) {
        unsigned w = lcg_next() % 12;
        unsigned rd = lcg_next() % 12;
        unsigned free_before = 32 - r.count;
        unsigned want_acc = (w < free_before) ? w : free_before;
        unsigned want_taken;
        unsigned acc = pcm_ring_write(&r, src, w);
        unsigned taken;
        CHECK(acc == want_acc, "model: accepted matches free space");
        memcpy(shadow + shadow_len, src, acc);
        shadow_len += acc;
        want_taken = (rd < shadow_len) ? rd : shadow_len;
        taken = pcm_ring_read(&r, tmp, rd);
        CHECK(taken == want_taken, "model: taken matches available");
        if (taken > 0) {
            CHECK(memcmp(tmp, shadow, taken) == 0,
                  "model: fifo order against shadow");
            memmove(shadow, shadow + taken, shadow_len - taken);
            shadow_len -= taken;
        }
        CHECK(r.count == shadow_len, "model: count tracks shadow");
    }
}

int main(void) {
    t_roundtrip();
    t_wrap();
    t_overrun();
    t_underrun();
    t_zero_cap();
    t_model();
    if (failures == 0) {
        printf("pcm: ok\n");
        return 0;
    }
    printf("pcm: %d failures\n", failures);
    return 1;
}
