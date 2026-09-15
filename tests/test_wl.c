/** Host test for progs/wl/wl_mini.h (make test-wl).
 *
 * Pins wire roundtrip plus fail-closed bounds: liar size, truncated
 * opcode, wild object id, overlong string, pool overflow, surface dup,
 * focus order and hit testing top-most first.
 */

#include <stdio.h>
#include <string.h>

#include "progs/wl/wl_mini.h"

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

int main(void) {
    unsigned char buf[WL_MAX_MSG];
    wl_hdr_t h;
    wl_hdr_t d;
    unsigned int v;
    char out[WL_MAX_STR];
    wl_comp_t c;
    wl_client_t cl;
    unsigned int id;
    int n;
    int i;

    CHECK(wl_hdr_encode(buf, sizeof buf, WL_ID_DISPLAY,
        WL_OP_DISPLAY_GET_REGISTRY, 12, &h) == WL_ERR_OK,
        "hdr encode ok");
    CHECK(wl_hdr_decode(buf, 12, &d) == WL_ERR_OK, "hdr decode ok");
    CHECK(d.id == WL_ID_DISPLAY && d.opcode == WL_OP_DISPLAY_GET_REGISTRY
        && d.size == 12, "hdr roundtrip");

    CHECK(wl_hdr_encode(buf, sizeof buf, 0, 1, 12, 0) == WL_ERR_ID,
        "zero id rejected");
    CHECK(wl_hdr_encode(buf, sizeof buf, 1, 1, 4, 0) == WL_ERR_SIZE,
        "liar small size rejected");
    CHECK(wl_hdr_encode(buf, 4, 1, 1, 12, 0) == WL_ERR_BOUND,
        "short cap rejected");
    CHECK(wl_hdr_decode(buf, 4, &d) == WL_ERR_TRUNC, "truncated hdr");
    buf[0] = 7; buf[1] = 0; buf[2] = 0; buf[3] = 0;
    buf[4] = 1; buf[5] = 0; buf[6] = 12; buf[7] = 0;
    CHECK(wl_hdr_decode(buf, 12, &d) == WL_ERR_OK, "id 7 decodes");
    buf[0] = 0; buf[1] = 0; buf[2] = 0; buf[3] = 0;
    CHECK(wl_hdr_decode(buf, 12, &d) == WL_ERR_ID, "wild id rejected");

    CHECK(wl_u32_encode(buf, sizeof buf, 8, 0x12345678u) == WL_ERR_OK,
        "u32 encode");
    CHECK(wl_u32_decode(buf, 12, 8, &v) == WL_ERR_OK && v == 0x12345678u,
        "u32 roundtrip");
    CHECK(wl_u32_decode(buf, 10, 8, &v) == WL_ERR_BOUND, "u32 overrun");

    n = wl_str_encode(buf, sizeof buf, 8, "wl_shm");
    CHECK(n > 0, "str encode");
    CHECK(wl_str_decode(buf, 8 + n, 8, out, sizeof out) == n,
        "str roundtrip");
    CHECK(strcmp(out, "wl_shm") == 0, "str value");
    CHECK(wl_str_encode(buf, 10, 8, "wl_shm") == WL_ERR_BOUND,
        "str overrun fail-closed");
    CHECK(wl_str_decode(buf, 8 + 4, 8, out, sizeof out) == WL_ERR_TRUNC,
        "str trunc fail-closed");

    CHECK(wl_surface_id_valid(WL_ID_SURFACE_BASE) != 0, "surface base ok");
    CHECK(wl_surface_id_valid(WL_ID_SURFACE_BASE + WL_MAX_SURFACES) == 0,
        "surface past-end rejected");
    CHECK(wl_pool_fit(800, 360) == WL_ERR_OK, "max pool fits");
    CHECK(wl_pool_fit(801, 360) == WL_ERR_BOUND, "wide pool rejected");
    CHECK(wl_pool_fit(0, 10) == WL_ERR_BOUND, "zero pool rejected");

    wl_comp_init(&c);
    CHECK(c.count == 0 && c.focus == -1, "comp empty");
    CHECK(wl_comp_add(&c, WL_ID_SURFACE_BASE, 320, 200) == WL_ERR_OK,
        "add s0");
    CHECK(wl_comp_add(&c, WL_ID_SURFACE_BASE, 100, 100) == WL_ERR_ID,
        "dup id rejected");
    CHECK(wl_comp_add(&c, 7, 100, 100) == WL_ERR_ID, "wild id rejected");
    for (i = 1; i < WL_MAX_SURFACES; i++) {
        CHECK(wl_comp_add(&c, WL_ID_SURFACE_BASE + (unsigned int)i,
            64, 64) == WL_ERR_OK, "fill pool");
    }
    CHECK(wl_comp_add(&c, WL_ID_SURFACE_BASE + 7, 64, 64) == WL_ERR_BOUND
        || c.count == WL_MAX_SURFACES, "ninth surface refused");
    CHECK(wl_comp_focus(&c, WL_ID_SURFACE_BASE) == WL_ERR_OK, "focus s0");
    CHECK(c.focus == 0, "focus lands");
    CHECK(wl_comp_hit(&c, 10, 10) == (int)WL_ID_SURFACE_BASE, "hit top");
    CHECK(wl_comp_remove(&c, WL_ID_SURFACE_BASE) == WL_ERR_OK, "remove s0");
    CHECK(wl_comp_remove(&c, WL_ID_SURFACE_BASE) == WL_ERR_ID,
        "double remove rejected");

    wl_client_init(&cl);
    for (i = 0; i < WL_MAX_SURFACES; i++) {
        CHECK(wl_client_surface(&cl, &id) == WL_ERR_OK, "client surface");
    }
    CHECK(wl_client_surface(&cl, &id) == WL_ERR_BOUND, "client drained");
    wl_client_init(&cl);
    for (i = 0; i < WL_MAX_POOLS; i++) {
        CHECK(wl_client_pool(&cl, &id) == WL_ERR_OK, "client pool");
    }
    CHECK(wl_client_pool(&cl, &id) == WL_ERR_BOUND, "pool drained");

    {
        unsigned char fb[16 * 10];
        wl_comp_t r;
        unsigned int a = 0;
        unsigned int b = 0;
        wl_client_t rc;
        wl_comp_init(&r);
        wl_client_init(&rc);
        CHECK(wl_client_surface(&rc, &a) == WL_ERR_OK, "render surf a");
        CHECK(wl_client_surface(&rc, &b) == WL_ERR_OK, "render surf b");
        CHECK(wl_comp_add(&r, a, 8, 6) == WL_ERR_OK, "render add a");
        CHECK(wl_comp_add(&r, b, 8, 6) == WL_ERR_OK, "render add b");
        r.items[0].x = 0; r.items[0].y = 0;
        r.items[1].x = 4; r.items[1].y = 0;
        CHECK(wl_comp_set_color(&r, a, 4) == WL_ERR_OK, "color a");
        CHECK(wl_comp_set_color(&r, b, 6) == WL_ERR_OK, "color b");
        CHECK(wl_comp_set_color(&r, b, 300) == WL_ERR_BOUND,
            "wild color refused");
        CHECK(wl_comp_set_color(&r, 7, 4) == WL_ERR_ID,
            "color unknown id refused");
        CHECK(wlcomp_render(&r, fb, 16, 10) == WL_ERR_OK, "render ok");
        CHECK(fb[9 * 16 + 15] == WLCOMP_BG, "bg pixel");
        CHECK(fb[2 * 16 + 2] == 4, "surface a interior");
        CHECK(fb[0] == WLCOMP_BORDER, "border pixel");
        CHECK(fb[2 * 16 + 6] == 6, "top-most wins overlap");
        CHECK(wlcomp_render(&r, fb, 0, 10) == WL_ERR_BOUND,
            "zero width refused");
        CHECK(wlcomp_render(&r, fb, 801, 10) == WL_ERR_BOUND,
            "oversize refused");
        CHECK(wlcomp_render(0, fb, 16, 10) == WL_ERR_BOUND,
            "null comp refused");
    }

    if (failures == 0)
        printf("wl: ok (%d surfaces, msg %d)\n", WL_MAX_SURFACES, WL_MAX_MSG);
    return failures != 0;
}
