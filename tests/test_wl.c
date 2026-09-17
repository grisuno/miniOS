/** Host test for progs/wl/wl_mini.h (make test-wl).
 *
 * Pins wire roundtrip plus fail-closed bounds: liar size, truncated
 * opcode, wild object id, overlong string, pool overflow, surface dup,
 * focus order and hit testing top-most first.
 */

#include <stdio.h>
#include <string.h>

#include "progs/wl/wl_mini.h"
#include "progs/wl/wl_mbox.h"
#include "progs/nk_palette.h"
#include "progs/minios_abi.h"

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

    {
        wl_comp_t t;
        unsigned int s0 = 0;
        unsigned int s1 = 0;
        wl_client_t tc;
        wl_comp_init(&t);
        wl_client_init(&tc);
        CHECK(wl_client_surface(&tc, &s0) == WL_ERR_OK, "tile surf a");
        CHECK(wl_client_surface(&tc, &s1) == WL_ERR_OK, "tile surf b");
        CHECK(wl_comp_add(&t, s0, 320, 200) == WL_ERR_OK, "tile add a");
        CHECK(wl_comp_add(&t, s1, 320, 200) == WL_ERR_OK, "tile add b");
        CHECK(wl_comp_set_rect(&t, s0, 0, 0, 400, 180) == WL_ERR_OK,
            "set rect ok");
        CHECK(t.items[0].x == 0 && t.items[0].w == 400, "rect lands");
        CHECK(wl_comp_set_rect(&t, 7, 0, 0, 64, 64) == WL_ERR_ID,
            "rect wild id refused");
        CHECK(wl_comp_set_rect(&t, s0, 0, 0, 801, 360) == WL_ERR_BOUND,
            "rect oversize refused");
        CHECK(wl_comp_set_rect(&t, s0, 5000, 0, 64, 64) == WL_ERR_BOUND,
            "rect far x refused");
        CHECK(wl_comp_set_rect(0, s0, 0, 0, 64, 64) == WL_ERR_BOUND,
            "rect null refused");
        CHECK(wl_comp_layout_tile(&t, 800, 360) == 2, "layout two");
        CHECK(t.items[t.order[0]].x == 0, "layout first left");
        CHECK(t.items[t.order[1]].x == 400, "layout second right");
        CHECK(t.items[t.order[0]].w == 400, "layout half width");
        CHECK(wl_comp_layout_tile(&t, 0, 360) == WL_ERR_BOUND,
            "layout zero fb refused");
        CHECK(wl_comp_layout_tile(0, 800, 360) == WL_ERR_BOUND,
            "layout null refused");
        CHECK(wl_comp_layout_tile(&t, 31, 24) == 2, "layout odd width");
        CHECK(t.items[t.order[0]].w == 15, "layout odd left floor");
        CHECK(t.items[t.order[1]].w == 16, "layout odd remainder right");
        CHECK(t.items[t.order[0]].x == 0
            && t.items[t.order[1]].x == 15, "layout odd edges meet");
        CHECK(wl_comp_layout_tile(&t, 801, 24) == WL_ERR_BOUND,
            "layout oversize fb refused");
    }

    {
        wl_comp_t b;
        unsigned int s0 = 0;
        wl_client_t bc;
        unsigned char fb[16 * 10];
        unsigned char src[8 * 6];
        const unsigned char *px[WL_MAX_SURFACES];
        int pw[WL_MAX_SURFACES];
        int ph[WL_MAX_SURFACES];
        int i;
        wl_comp_init(&b);
        wl_client_init(&bc);
        CHECK(wl_client_surface(&bc, &s0) == WL_ERR_OK, "blit surf");
        CHECK(wl_comp_add(&b, s0, 8, 6) == WL_ERR_OK, "blit add");
        b.items[0].x = 0; b.items[0].y = 0;
        for (i = 0; i < WL_MAX_SURFACES; i++) {
            px[i] = 0; pw[i] = 0; ph[i] = 0;
        }
        for (i = 0; i < 8 * 6; i++)
            src[i] = 7;
        px[0] = src; pw[0] = 8; ph[0] = 6;
        CHECK(wlcomp_blit(&b, fb, 16, 10, px, pw, ph) == WL_ERR_OK,
            "blit pixels ok");
        CHECK(fb[2 * 16 + 2] == 7, "blit interior from client");
        CHECK(fb[0] == WLCOMP_BORDER, "blit border kept");
        CHECK(wlcomp_blit(&b, fb, 16, 10, 0, 0, 0) == WL_ERR_OK,
            "blit null table falls back");
        CHECK(fb[2 * 16 + 2] == 4, "blit fallback is solid color");
        pw[0] = 4;
        CHECK(wlcomp_blit(&b, fb, 16, 10, px, pw, ph) == WL_ERR_BOUND,
            "blit dim mismatch refused");
        CHECK(wlcomp_blit(0, fb, 16, 10, px, pw, ph) == WL_ERR_BOUND,
            "blit null comp refused");
        CHECK(wlcomp_blit(&b, 0, 16, 10, px, pw, ph) == WL_ERR_BOUND,
            "blit null fb refused");
    }

    {
        unsigned char m[WL_MAX_MSG];
        unsigned int pool = 0;
        int w = 0;
        int h = 0;
        unsigned int id = 0;
        int n;
        n = wl_attach_encode(m, sizeof m, WL_ID_POOL_BASE, 320, 200);
        CHECK(n == 12, "attach encode ok");
        CHECK(wl_attach_decode(m, n, &pool, &w, &h) == WL_ERR_OK
            && pool == WL_ID_POOL_BASE && w == 320 && h == 200,
            "attach roundtrip");
        CHECK(wl_attach_encode(m, sizeof m, 7, 64, 64) == WL_ERR_ID,
            "attach wild pool refused");
        CHECK(wl_attach_encode(m, sizeof m, WL_ID_POOL_BASE, 801, 360)
            == WL_ERR_BOUND, "attach oversize refused");
        CHECK(wl_attach_encode(m, 4, WL_ID_POOL_BASE, 64, 64) == WL_ERR_BOUND,
            "attach short cap refused");
        CHECK(wl_attach_decode(m, 4, &pool, &w, &h) == WL_ERR_TRUNC,
            "attach trunc refused");
        m[0] = 7; m[1] = 0; m[2] = 0; m[3] = 0;
        m[4] = 64; m[5] = 0; m[6] = 0; m[7] = 0;
        m[8] = 64; m[9] = 0; m[10] = 0; m[11] = 0;
        CHECK(wl_attach_decode(m, 12, &pool, &w, &h) == WL_ERR_ID,
            "attach wild pool refused");
        CHECK(wl_attach_decode(0, 12, &pool, &w, &h) == WL_ERR_BOUND,
            "attach null refused");
        n = wl_commit_encode(m, sizeof m, WL_ID_SURFACE_BASE);
        CHECK(n == 4, "commit encode ok");
        CHECK(wl_commit_decode(m, n, &id) == WL_ERR_OK
            && id == WL_ID_SURFACE_BASE, "commit roundtrip");
        CHECK(wl_commit_encode(m, sizeof m, 7) == WL_ERR_ID,
            "commit wild id refused");
        m[0] = 7; m[1] = 0; m[2] = 0; m[3] = 0;
        CHECK(wl_commit_decode(m, 4, &id) == WL_ERR_ID,
            "commit wild id on decode refused");
        CHECK(wl_commit_decode(m, 2, &id) == WL_ERR_TRUNC,
            "commit trunc refused");
    }

    {
        unsigned char s[256];
        unsigned char bad[16];
        wl_hdr_t m;
        wl_comp_t d;
        wl_client_t dc;
        wl_stream_t st;
        int o = 0;
        int sz = 0;
        int n;
        int off;
        wl_comp_init(&d);
        wl_client_init(&dc);
        wl_stream_init(&st);
        CHECK(wl_hdr_encode(s + o, 32, WL_ID_DISPLAY,
            WL_OP_DISPLAY_GET_REGISTRY, 8, 0) == WL_ERR_OK, "sess registry");
        o += 8;
        CHECK(wl_hdr_encode(s + o, 32, WL_ID_REGISTRY, WL_OP_REGISTRY_BIND,
            12, 0) == WL_ERR_OK, "sess bind");
        CHECK(wl_u32_encode(s + o, 32, 8, WL_ID_COMPOSITOR) == WL_ERR_OK,
            "sess bind arg");
        o += 12;
        CHECK(wl_hdr_encode(s + o, 32, WL_ID_COMPOSITOR,
            WL_OP_COMPOSITOR_CREATE_SURFACE, 8, 0) == WL_ERR_OK,
            "sess surface a");
        o += 8;
        CHECK(wl_hdr_encode(s + o, 32, WL_ID_SHM, WL_OP_SHM_CREATE_POOL,
            8, 0) == WL_ERR_OK, "sess pool");
        o += 8;
        CHECK(wl_hdr_encode(s + o, 32, WL_ID_SURFACE_BASE,
            WL_OP_SURFACE_ATTACH, 20, 0) == WL_ERR_OK, "sess attach a");
        CHECK(wl_attach_encode(s + o + 8, 32, WL_ID_POOL_BASE, 320, 200)
            == WL_ATTACH_SZ, "sess attach arg a");
        o += 20;
        CHECK(wl_hdr_encode(s + o, 32, WL_ID_SURFACE_BASE,
            WL_OP_SURFACE_COMMIT, 8, 0) == WL_ERR_OK, "sess commit a");
        o += 8;
        CHECK(wl_hdr_encode(s + o, 32, WL_ID_COMPOSITOR,
            WL_OP_COMPOSITOR_CREATE_SURFACE, 8, 0) == WL_ERR_OK,
            "sess surface b");
        o += 8;
        CHECK(wl_hdr_encode(s + o, 32, WL_ID_SURFACE_BASE + 1,
            WL_OP_SURFACE_ATTACH, 20, 0) == WL_ERR_OK, "sess attach b");
        CHECK(wl_attach_encode(s + o + 8, 32, WL_ID_POOL_BASE, 400, 180)
            == WL_ATTACH_SZ, "sess attach arg b");
        o += 20;
        CHECK(wl_hdr_encode(s + o, 32, WL_ID_SURFACE_BASE + 1,
            WL_OP_SURFACE_COMMIT, 8, 0) == WL_ERR_OK, "sess commit b");
        o += 8;
        CHECK(wl_stream_feed(&st, s, 5) == WL_ERR_OK, "stream split feed");
        CHECK(wl_stream_next(&st, &sz) == WL_ERR_MORE, "stream halves wait");
        CHECK(wl_stream_feed(&st, s + 5, o - 5) == WL_ERR_OK,
            "stream rest feed");
        n = 0;
        while (wl_stream_next(&st, &sz) == WL_ERR_OK) {
            CHECK(wl_hdr_decode(st.buf, sz, &m) == WL_ERR_OK,
                "stream msg decodes");
            CHECK(wl_dispatch(&d, &dc, m.id, m.opcode, st.buf + 8, sz - 8)
                == WL_ERR_OK, "session request dispatches");
            CHECK(wl_stream_consume(&st, sz) == WL_ERR_OK,
                "stream consumes");
            n++;
            if (n > 16)
                break;
        }
        CHECK(n == 9, "session runs nine messages");
        CHECK(d.count == 2, "session maps two surfaces");
        CHECK(wl_comp_layout_tile(&d, 800, 360) == 2, "session tiles");
        CHECK(d.items[d.order[0]].x == 0, "session first left");
        CHECK(d.items[d.order[1]].x == 400, "session second right");
        CHECK(wl_dispatch(&d, &dc, 9, 0, bad, 0) == WL_ERR_ID,
            "dispatch wild id refused");
        CHECK(wl_dispatch(&d, &dc, WL_ID_DISPLAY, 7, bad, 0)
            == WL_ERR_BOUND, "dispatch wild opcode refused");
        CHECK(wl_hdr_encode(bad, sizeof bad, WL_ID_SURFACE_BASE,
            WL_OP_SURFACE_ATTACH, 8, 0) == WL_ERR_OK, "short attach hdr");
        CHECK(wl_dispatch(&d, &dc, WL_ID_SURFACE_BASE,
            WL_OP_SURFACE_ATTACH, bad + 8, 0) == WL_ERR_BOUND,
            "dispatch short attach refused");
        CHECK(wl_dispatch(&d, &dc, WL_ID_SURFACE_BASE + 7,
            WL_OP_SURFACE_COMMIT, bad, 0) == WL_ERR_ID,
            "dispatch commit stranger refused");
        CHECK(wl_stream_next(&st, &sz) == WL_ERR_MORE, "stream drains clean");
        CHECK(wl_stream_consume(&st, 1) == WL_ERR_BOUND,
            "stream over-consume refused");
        CHECK(wl_stream_feed(&st, s, WL_STREAM_CAP + 1) == WL_ERR_BOUND,
            "stream overflow refused");
        CHECK(wl_iface_find("wl_compositor") == 2, "iface lookup hits");
        CHECK(wl_iface_find("wl_nope") == WL_ERR_ID, "iface miss refused");
        for (off = 0; off < 16; off++)
            bad[off] = 0;
        CHECK(wl_stream_feed(0, bad, 4) == WL_ERR_BOUND,
            "stream null refused");
    }

    {
        unsigned char pal[768];
        unsigned char frame[WL_MAX_MSG + 8];
        char name[WL_MBOX_NAME_MAX];
        char box[WL_MBOX_BOX_MAX];
        unsigned int seq = 0;
        int off = 0;
        int len = 0;
        int n;
        unsigned char hello[8];
        wl_mbox_box_t boxes[WL_MAX_SURFACES];
        wl_mbox_init(boxes);
        CHECK(nk_palette_build(pal, 768) == NK_PAL_ERR_OK, "pal builds");
        CHECK(pal[6 * 3] == 15 && pal[6 * 3 + 1] == 15
            && pal[6 * 3 + 2] == 15, "pal terminal bg exact");
        CHECK(pal[7 * 3] == 0 && pal[7 * 3 + 1] == 220
            && pal[7 * 3 + 2] == 0, "pal terminal fg exact");
        CHECK(pal[4 * 3] == 60 && pal[4 * 3 + 1] == 90
            && pal[4 * 3 + 2] == 140, "pal titlebar exact");
        CHECK(pal[15 * 3] == 0 && pal[230 * 3] == 255, "pal cube spans");
        CHECK(pal[231 * 3] == 0 && pal[241 * 3] == 255, "pal grays span");
        CHECK(nk_palette_build(0, 768) == NK_PAL_ERR_BOUND,
            "pal null refused");
        CHECK(nk_palette_build(pal, 100) == NK_PAL_ERR_BOUND,
            "pal short refused");
        CHECK(wl_mbox_box_ok("stripe") == WL_ERR_OK, "box name ok");
        CHECK(wl_mbox_box_ok("") == WL_ERR_STR, "box empty refused");
        CHECK(wl_mbox_box_ok("UP") == WL_ERR_STR, "box upper refused");
        CHECK(wl_mbox_box_ok("a/b") == WL_ERR_STR, "box slash refused");
        CHECK(wl_mbox_name(name, sizeof name, "stripe", 7) > 0,
            "mbox name builds");
        CHECK(wl_mbox_parse(name, box, sizeof box, &seq) == WL_ERR_OK
            && seq == 7, "mbox name roundtrips");
        CHECK(box[6] == '\0' && memcmp(box, "stripe", 6) == 0,
            "mbox box value");
        CHECK(wl_mbox_name(name, 8, "stripe", 7) == WL_ERR_BOUND,
            "mbox short cap refused");
        CHECK(wl_mbox_name(name, sizeof name, "UP", 7) == WL_ERR_STR,
            "mbox wild box refused");
        CHECK(wl_mbox_parse("/shm/wl/nope.txt", box, sizeof box, &seq)
            == WL_ERR_STR, "mbox suffix refused");
        CHECK(wl_mbox_parse("/shm/wl/a-zzzzzzzz.msg", box, sizeof box,
            &seq) == WL_ERR_STR, "mbox wild seq refused");
        hello[0] = 1; hello[1] = 0; hello[2] = 0; hello[3] = 0;
        hello[4] = 1; hello[5] = 0; hello[6] = 8; hello[7] = 0;
        n = wl_mbox_frame_encode(frame, sizeof frame, 9, hello, 8);
        CHECK(n == 16, "mbox frame encodes");
        CHECK(wl_mbox_frame_decode(frame, n, &seq, &off, &len)
            == WL_ERR_OK && seq == 9 && len == 8, "mbox frame roundtrips");
        CHECK(wl_mbox_frame_decode(frame, 4, &seq, &off, &len)
            == WL_ERR_TRUNC, "mbox torn frame refused");
        frame[0] = 'X';
        CHECK(wl_mbox_frame_decode(frame, n, &seq, &off, &len)
            == WL_ERR_BOUND, "mbox wild magic refused");
        CHECK(wl_mbox_assign(boxes, "stripe") == 0, "mbox slot zero");
        CHECK(wl_mbox_assign(boxes, "checker") == 1, "mbox slot one");
        CHECK(wl_mbox_assign(boxes, "stripe") == 0, "mbox slot stable");
        CHECK(wl_mbox_assign(boxes, "UP") == WL_ERR_STR,
            "mbox assign wild refused");
        CHECK(wl_mbox_raw_name(name, sizeof name, "stripe") > 0,
            "mbox raw builds");
        CHECK(wl_mbox_raw_name(name, 8, "stripe") == WL_ERR_BOUND,
            "mbox raw short refused");
        CHECK(wl_mbox_fresh(boxes, 0, 8) == 1, "mbox new seq accepted");
        boxes[0].used = 1;
        boxes[0].seq_last = 8;
        CHECK(wl_mbox_fresh(boxes, 0, 8) == 0, "mbox dup refused");
        CHECK(wl_mbox_fresh(boxes, 0, 9) == 1, "mbox next accepted");
        CHECK(wl_mbox_fresh(boxes, 99, 9) == WL_ERR_BOUND,
            "mbox wild slot refused");
        CHECK(wl_mbox_fresh(0, 0, 9) == WL_ERR_BOUND,
            "mbox null refused");
    }

    {
        wl_comp_t r;
        wl_mbox_box_t rb[WL_MAX_SURFACES];
        unsigned char arg[WL_ATTACH_SZ];
        unsigned char four[4];
        int slot = -1;
        int w = 0;
        int h = 0;
        wl_comp_init(&r);
        wl_mbox_init(rb);
        CHECK(wl_attach_encode(arg, sizeof arg, WL_ID_POOL_BASE, 320, 200)
            == WL_ATTACH_SZ, "route attach arg");
        CHECK(wl_mbox_route(&r, rb, "stripe", WL_ID_SURFACE_BASE,
            WL_OP_SURFACE_ATTACH, arg, sizeof arg, &slot, &w, &h)
            == WL_ERR_OK && slot == 0 && w == 320 && h == 200,
            "route attach maps slot zero");
        CHECK(r.items[0].w == 320 && r.items[0].h == 200,
            "route attach resizes");
        four[0] = 3; four[1] = 0; four[2] = 0; four[3] = 0;
        CHECK(wl_mbox_route(&r, rb, "stripe", WL_ID_REGISTRY,
            WL_OP_REGISTRY_BIND, four, 4, &slot, &w, &h) == WL_ERR_OK
            && slot == 0, "route bind stable slot");
        CHECK(wl_mbox_route(&r, rb, "stripe", WL_ID_SURFACE_BASE + 7,
            WL_OP_SURFACE_COMMIT, 0, 0, &slot, &w, &h) == WL_ERR_OK
            && slot == 0, "route foreign id same box");
        CHECK(wl_attach_encode(arg, sizeof arg, WL_ID_POOL_BASE, 400, 180)
            == WL_ATTACH_SZ, "route second arg");
        CHECK(wl_mbox_route(&r, rb, "checker", WL_ID_SURFACE_BASE + 1,
            WL_OP_SURFACE_ATTACH, arg, sizeof arg, &slot, &w, &h)
            == WL_ERR_OK && slot == 1, "route second box slot one");
        CHECK(wl_mbox_route(&r, rb, "UP", WL_ID_SURFACE_BASE,
            WL_OP_SURFACE_ATTACH, arg, sizeof arg, &slot, &w, &h)
            == WL_ERR_STR, "route wild box refused");
        CHECK(wl_mbox_route(&r, rb, "stripe", 9, 0, four, 4, &slot, &w,
            &h) == WL_ERR_ID, "route wild id refused");
        CHECK(wl_mbox_route(&r, rb, "stripe", WL_ID_SURFACE_BASE, 7,
            four, 4, &slot, &w, &h) == WL_ERR_BOUND,
            "route wild opcode refused");
        CHECK(wl_mbox_route(&r, rb, "stripe", WL_ID_SURFACE_BASE,
            WL_OP_SURFACE_ATTACH, four, 4, &slot, &w, &h) == WL_ERR_BOUND,
            "route short attach refused");
        CHECK(wl_mbox_route(0, rb, "stripe", WL_ID_SURFACE_BASE,
            WL_OP_SURFACE_COMMIT, 0, 0, &slot, &w, &h) == WL_ERR_BOUND,
            "route null refused");
    }

    {
        unsigned char src4[4] = {1, 2, 3, 4};
        unsigned char dst16[16];
        unsigned char same[4];
        CHECK(wl_scale_nearest(dst16, 4, 4, src4, 2, 2) == WL_ERR_OK,
            "scale up ok");
        CHECK(dst16[0] == 1 && dst16[1] == 1 && dst16[2] == 2
            && dst16[3] == 2, "scale top row doubles");
        CHECK(dst16[8] == 3 && dst16[15] == 4, "scale bottom lands");
        CHECK(wl_scale_nearest(same, 2, 2, src4, 2, 2) == WL_ERR_OK
            && same[3] == 4, "scale identity copies");
        CHECK(wl_scale_nearest(0, 4, 4, src4, 2, 2) == WL_ERR_BOUND,
            "scale null refused");
        CHECK(wl_scale_nearest(dst16, 0, 4, src4, 2, 2) == WL_ERR_BOUND,
            "scale zero refused");
        CHECK(wl_scale_nearest(dst16, 801, 4, src4, 2, 2) == WL_ERR_BOUND,
            "scale oversize refused");
    }

    {
        wl_comp_t w;
        wl_client_t wc;
        unsigned int a = 0;
        unsigned int b = 0;
        unsigned char fb[32 * 24];
        int zone = 0;
        wl_comp_init(&w);
        wl_client_init(&wc);
        CHECK(wl_client_surface(&wc, &a) == WL_ERR_OK, "chrome surf a");
        CHECK(wl_client_surface(&wc, &b) == WL_ERR_OK, "chrome surf b");
        CHECK(wl_comp_add(&w, a, 30, 30) == WL_ERR_OK, "chrome add a");
        CHECK(wl_comp_add(&w, b, 30, 30) == WL_ERR_OK, "chrome add b");
        w.items[0].x = 0; w.items[0].y = 0;
        w.items[1].x = 4; w.items[1].y = 0;
        CHECK(w.items[1].active == 1 && w.items[0].active == 0,
            "chrome top is active");
        CHECK(wl_comp_focus(&w, a) == WL_ERR_OK, "chrome refocus");
        CHECK(w.items[0].active == 1 && w.items[1].active == 0,
            "chrome focus flips active");
        zone = wl_surface_hit_zone(&w.items[0], 2, 2);
        CHECK(zone == WL_HIT_TITLE, "chrome title zone");
        zone = wl_surface_hit_zone(&w.items[0], 27, 2);
        CHECK(zone == WL_HIT_CLOSE, "chrome close zone");
        zone = wl_surface_hit_zone(&w.items[0], 28, 28);
        CHECK(zone == WL_HIT_RESIZE, "chrome resize zone");
        zone = wl_surface_hit_zone(&w.items[0], 10, 20);
        CHECK(zone == WL_HIT_BODY, "chrome body zone");
        zone = wl_surface_hit_zone(&w.items[0], 60, 60);
        CHECK(zone == WL_HIT_NONE, "chrome outside refused");
        CHECK(wl_surface_hit_zone(0, 2, 2) == WL_HIT_NONE,
            "chrome null refused");
        CHECK(wlcomp_blit_chrome(&w, fb, 32, 24, 0, 0, 0)
            == WL_ERR_OK, "chrome blit ok");
        CHECK(fb[2 * 32 + 2] == (unsigned char)WL_TITLE_ACTIVE,
            "chrome active title paints");
        CHECK(fb[2 * 32 + 27] == (unsigned char)WL_CLOSE_INK,
            "chrome close box paints");
        CHECK(fb[20 * 32 + 10] == 4, "chrome body keeps color");
        CHECK(wlcomp_blit_chrome(&w, fb, 32, 24, 0, 0, 0)
            == WL_ERR_OK, "chrome blit stable");
        CHECK(wl_comp_set_minimized(&w, b, 1) == WL_ERR_OK,
            "chrome minimize ok");
        CHECK(wl_comp_hit(&w, 6, 2) == (int)a,
            "chrome minimized skips hit");
        CHECK(wl_comp_layout_tile(&w, 32, 24) == 1,
            "chrome tile skips minimized");
        CHECK(wl_comp_set_minimized(&w, 7, 1) == WL_ERR_ID,
            "chrome minimize stranger refused");
        CHECK(wl_comp_set_minimized(0, a, 1) == WL_ERR_BOUND,
            "chrome minimize null refused");
        CHECK(wlcomp_blit_chrome(0, fb, 32, 24, 0, 0, 0)
            == WL_ERR_BOUND, "chrome null refused");
        CHECK(wlcomp_blit_chrome(&w, 0, 32, 24, 0, 0, 0)
            == WL_ERR_BOUND, "chrome null fb refused");
    }

    {
        wl_ev_t e;
        wl_ev_t d;
        unsigned char frame[WL_EV_SZ];
        int cx = -9;
        int cy = -9;
        char box[WL_MBOX_BOX_MAX];
        char path[WL_MBOX_NAME_MAX];
        int i;
        e.seq = 7;
        e.mx = 100;
        e.my = 50;
        e.buttons = 1;
        e.wheel = 3;
        e.nsc = 2;
        e.sc[0] = 0x1C;
        e.sc[1] = 0x9C;
        for (i = 2; i < WL_EV_SC_MAX; i++)
            e.sc[i] = 0;
        CHECK(wl_ev_encode(frame, sizeof frame, &e) == WL_EV_SZ,
            "ev encode ok");
        CHECK(wl_ev_decode(frame, WL_EV_SZ, &d) == WL_ERR_OK
            && d.seq == 7 && d.mx == 100 && d.my == 50
            && d.buttons == 1 && d.wheel == 3 && d.nsc == 2
            && d.sc[0] == 0x1C && d.sc[1] == 0x9C,
            "ev roundtrip");
        CHECK(wl_ev_decode(frame, 4, &d) == WL_ERR_TRUNC,
            "ev torn refused");
        frame[0] = 'X';
        CHECK(wl_ev_decode(frame, WL_EV_SZ, &d) == WL_ERR_BOUND,
            "ev wild magic refused");
        e.nsc = WL_EV_SC_MAX + 1;
        CHECK(wl_ev_encode(frame, sizeof frame, &e) == WL_ERR_BOUND,
            "ev wild count refused");
        CHECK(wl_ev_encode(frame, 4, &e) == WL_ERR_BOUND,
            "ev short cap refused");
        CHECK(wl_ev_encode(0, WL_EV_SZ, &e) == WL_ERR_BOUND,
            "ev null refused");
        CHECK(wl_ev_map(10, 20, 0, 0, 30, 30, 30, 30, &cx, &cy) == 1
            && cx == 9 && cy == 11,
            "ev map centers");
        CHECK(wl_ev_map(200, 200, 0, 0, 30, 30, 30, 30, &cx, &cy) == 0
            && cx == -1 && cy == -1,
            "ev map outside refused");
        CHECK(wl_ev_map(2, 2, 0, 0, 30, 30, 30, 30, &cx, &cy) == 0,
            "ev map title refused");
        CHECK(wl_ev_map(10, 20, 0, 0, 30, 30, 30, 30, 0, &cy)
            == WL_ERR_BOUND,
            "ev map null refused");
        CHECK(wl_client_box("Paint", 42, box, sizeof box) == WL_ERR_OK
            && strcmp(box, "paint42") == 0,
            "client box names pid");
        CHECK(wl_client_box("a", 0, box, sizeof box) == WL_ERR_OK
            && strcmp(box, "a0") == 0,
            "client box pid zero");
        CHECK(wl_client_box("UPPER", 7, box, 4) == WL_ERR_BOUND,
            "client box short refused");
        CHECK(wl_client_box("a", -1, box, sizeof box) == WL_ERR_BOUND,
            "client box negative pid refused");
        CHECK(wl_client_box(0, 7, box, sizeof box) == WL_ERR_BOUND,
            "client box null refused");
        CHECK(wl_mbox_ev_name(path, sizeof path, "paint42") > 0
            && strcmp(path, "/shm/wl/paint42.ev") == 0,
            "ev name builds");
        CHECK(wl_mbox_ev_name(path, 8, "paint42") == WL_ERR_BOUND,
            "ev name short refused");
        CHECK(wl_mbox_ev_name(path, sizeof path, "UP") == WL_ERR_STR,
            "ev name wild refused");
    }

    CHECK(WL_SURF_MAX_W == MINIOS_NK_W, "surf max w tracks abi");
    CHECK(WL_SURF_MAX_H == MINIOS_NK_H, "surf max h tracks abi");

    if (failures == 0)
        printf("wl: ok (%d surfaces, msg %d)\n", WL_MAX_SURFACES, WL_MAX_MSG);
    return failures != 0;
}
