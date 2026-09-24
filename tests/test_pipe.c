/** Docstring: Host test for headers/pipe.h (make test-pipe).
 *
 * Drives the pure ring core with stack buffers. Verifies init bounds,
 * write/read roundtrip, wraparound, partial write on a full ring,
 * EMPTY vs EOF discrimination, writer-close idempotence and the stat
 * snapshot, so a mutant that drops a bound or confuses EMPTY with EOF
 * dies on the host with no QEMU boot.
 */

#include <stdio.h>

#include "pipe.h"

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

int main(void) {
    unsigned char buf[16];
    unsigned char out[16];
    pipe_ring_t r;
    pipe_cfg_t st;
    int i;

    CHECK(pipe_ring_init(0, buf, sizeof(buf)) == PIPE_ERR_BOUND, "init null ring");
    CHECK(pipe_ring_init(&r, 0, sizeof(buf)) == PIPE_ERR_BOUND, "init null buf");
    CHECK(pipe_ring_init(&r, buf, 0u) == PIPE_ERR_BOUND, "init zero cap");
    CHECK(pipe_ring_init(&r, buf, PIPE_CAP_MAX + 1u) == PIPE_ERR_BOUND, "init oversize cap");
    CHECK(pipe_ring_init(&r, buf, sizeof(buf)) == 0, "init ok");
    CHECK(pipe_ring_avail(&r) == 0u, "avail empty");
    CHECK(pipe_ring_space(&r) == 16u, "space full");
    CHECK(pipe_ring_avail(0) == 0u, "avail null");
    CHECK(pipe_ring_space(0) == 0u, "space null");

    CHECK(pipe_ring_read(&r, out, sizeof(out)) == PIPE_EMPTY, "empty writer-open");
    for (i = 0; i < 16; i++)
        buf[i] = 0;
    CHECK(pipe_ring_write(&r, (unsigned char *)"abcd", 4u) == 4u, "write 4");
    CHECK(pipe_ring_avail(&r) == 4u, "avail 4");
    CHECK(pipe_ring_read(&r, out, 2u) == 2, "read 2");
    CHECK(out[0] == 'a' && out[1] == 'b', "read order");
    CHECK(pipe_ring_write(&r, (unsigned char *)"efghijklmnopqrst", 14u) == 14u, "write wrap");
    CHECK(pipe_ring_avail(&r) == 16u, "avail full");
    CHECK(pipe_ring_write(&r, (unsigned char *)"z", 1u) == 0u, "write full partial 0");
    {
        int total = 0, n;
        while ((n = pipe_ring_read(&r, out, sizeof(out))) > 0)
            total += n;
        CHECK(total == 16, "drain all");
        CHECK(n == PIPE_EMPTY, "drained writer-open is EMPTY");
    }

    CHECK(pipe_ring_close_writer(&r) == 0, "close writer");
    CHECK(pipe_ring_close_writer(&r) == 0, "close writer idempotent");
    CHECK(pipe_ring_close_writer(0) == PIPE_ERR_BOUND, "close null");
    CHECK(pipe_ring_read(&r, out, sizeof(out)) == 0, "drained writer-closed is EOF");
    CHECK(pipe_ring_write(&r, (unsigned char *)"q", 1u) == 0u, "write after close 0");
    CHECK(pipe_ring_read(&r, 0, 1u) == PIPE_ERR_BOUND, "read null dst");
    CHECK(pipe_ring_read(0, out, 1u) == PIPE_ERR_BOUND, "read null ring");
    CHECK(pipe_ring_write(&r, 0, 1u) == 0u, "write null src");

    CHECK(pipe_ring_init(&r, buf, sizeof(buf)) == 0, "reinit ok");
    CHECK(pipe_ring_write(&r, (unsigned char *)"xy", 2u) == 2u, "write 2");
    CHECK(pipe_ring_stat(&r, &st) == 0, "stat ok");
    CHECK(st.cap == 16u && st.count == 2u && st.wopen == 1, "stat values");
    CHECK(pipe_ring_stat(&r, 0) == PIPE_ERR_BOUND, "stat null out");
    CHECK(pipe_ring_stat(0, &st) == PIPE_ERR_BOUND, "stat null ring");

    {
        unsigned char cyc[16];
        pipe_ring_t rc;
        unsigned char w[3], tmp[3];
        CHECK(pipe_ring_init(&rc, cyc, sizeof(cyc)) == 0, "cyc init");
        for (i = 0; i < 200; i++) {
            w[0] = (unsigned char)i;
            w[1] = (unsigned char)(i + 1);
            w[2] = (unsigned char)(i + 2);
            if (pipe_ring_write(&rc, w, 3u) != 3u) {
                CHECK(0, "cyc write");
                break;
            }
            if (pipe_ring_read(&rc, tmp, 3u) != 3) {
                CHECK(0, "cyc read");
                break;
            }
            if (tmp[0] != w[0] || tmp[1] != w[1] || tmp[2] != w[2]) {
                CHECK(0, "cyc data");
                break;
            }
        }
        CHECK(pipe_ring_avail(&rc) == 0u, "cyc drained");
        CHECK(pipe_ring_space(&rc) == 16u, "cyc space back");
    }

    if (failures == 0)
        printf("pipe: ok\n");
    return failures != 0;
}
