/** wlcomp - Wayland-mini ring-3 compositor (ADR-0024, ADR-0026).
 *
 * Owns up to WL_MAX_SURFACES client surfaces, orders them by focus
 * (z-order), and presents through the existing kernel compositor
 * (GFX_PRESENT BUF_NK) so no kernel change is needed. Mailbox files
 * under /shm/wl carry one wire message each from live client
 * processes; raw pixels travel beside them as .raw files sized by
 * the last attach. The server drains, composites and presents, and
 * the desktop answers with click focus, drag move and ESC quit.
 *
 * Guest: wlcomp --selftest runs the pure state machine (no display
 * touch, safe anywhere) and prints wlcomp: frame ok (800x360).
 * Guest: wlcomp builds a two-surface demo, uploads the shared hybrid
 * palette, software-composites it into the NK back-buffer, titles
 * the window and presents it, so the desktop visibly gains tiled
 * clients beside the terminal. The gfx frames counter proves it.
 * Guest: wlcomp --server runs the interactive desktop, wlcomp --once
 * drains once for scripts, wlcomp --client attaches one surface from
 * a second process, wlcomp --clean unlinks the directory.
 *
 * Host test: tests/test_wl.c covers wl_mini.h plus wl_mbox.h (wire,
 * state, render, mailbox); this file only wires the compositor state
 * to syscalls and stays thin.
 */

/** Docstring above the code it describes, no inline comments. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "minios_abi.h"
#include "nk_palette.h"
#include "wl_mini.h"
#include "wl/wl_mbox.h"
#include "wl/wl_client.h"

#define WLCOMP_W 800
#define WLCOMP_H 360

/** Centralized compositor configuration, no magic numbers at call sites. */
typedef struct {
    int frame_w;
    int frame_h;
    int max_surfaces;
    unsigned char stripe_a;
    unsigned char stripe_b;
    unsigned char check_a;
    unsigned char check_b;
} wlcomp_cfg_t;

#define WLCOMP_CFG_DEFAULT { 800, 360, 8, 4, 12, 6, 13 }

static long wlcomp_sys_title(const char *t) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret)
        : "a"(MINIOS_SYS_GFX_SET_TITLE), "D"(t)
        : "rcx", "r11", "memory");
    return ret;
}

static long wlcomp_sys_present(long buf) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret)
        : "a"(MINIOS_SYS_GFX_PRESENT), "D"(buf), "S"(0L)
        : "rcx", "r11", "memory");
    return ret;
}

static long wlcomp_sys_present_origin(long buf, int *origin) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret)
        : "a"(MINIOS_SYS_GFX_PRESENT), "D"(buf), "S"(origin)
        : "rcx", "r11", "memory");
    return ret;
}

static long wlcomp_sys_palette(unsigned char *pal) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret)
        : "a"(MINIOS_SYS_PALETTE), "D"(pal)
        : "rcx", "r11", "memory");
    return ret;
}

static long wlcomp_sys_mouse(int *m) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret)
        : "a"(MINIOS_SYS_MOUSE), "D"(m)
        : "rcx", "r11", "memory");
    return ret;
}

static long wlcomp_sys_kbd(void) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret)
        : "a"(MINIOS_SYS_KBD), "D"(0L)
        : "rcx", "r11", "memory");
    return ret;
}

static long wlcomp_sys_kbd_raw(long on) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret)
        : "a"(MINIOS_SYS_KBD_RAW), "D"(on)
        : "rcx", "r11", "memory");
    return ret;
}

static long wlcomp_sys_vga_mode(long on) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret)
        : "a"(MINIOS_SYS_VGA_MODE), "D"(on)
        : "rcx", "r11", "memory");
    return ret;
}

static long wlcomp_sys_yield(void) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret)
        : "a"(MINIOS_SYS_SCHED_YIELD), "D"(0L)
        : "rcx", "r11", "memory");
    return ret;
}

static long wlcomp_sys_dir_list(const char *path, char *buf, long cap) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret)
        : "a"(MINIOS_SYS_DIR_LIST), "D"(path), "S"(buf), "d"(cap)
        : "rcx", "r11", "memory");
    return ret;
}

/** Upload the shared hybrid palette so indexed pixels expand through
 * desktop-exact colors on every VBE mode instead of the gray ramp. */
static int wlcomp_palette(void) {
    unsigned char pal[NK_PAL_BYTES];
    if (nk_palette_build(pal, NK_PAL_BYTES) != NK_PAL_ERR_OK)
        return 1;
    if (wlcomp_sys_palette(pal) != 0)
        return 1;
    return 0;
}

/** Paint a deterministic test pattern so the demo proves real pixels
 * travelled the blit path instead of solid fills. */
static void wlcomp_pattern(unsigned char *dst, int w, int h,
        unsigned char a, unsigned char b, int checker) {
    int y;
    int x;
    if (!dst || w <= 0 || h <= 0)
        return;
    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            int pick;
            if (checker)
                pick = ((x / 8) + (y / 8)) & 1;
            else
                pick = (x / 16) & 1;
            dst[y * w + x] = pick ? b : a;
        }
    }
}

/** Terminal-look tile: dark rows with green text bars and a prompt
 * block, so the fourth tile reads as a shell at a glance. Inks are
 * the desktop terminal bg (6) and text (7), never magic numbers. */
static void wlcomp_term_pattern(unsigned char *dst, int w, int h) {
    int y;
    int x;
    if (!dst || w <= 0 || h <= 0)
        return;
    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            unsigned char ink = 6;
            int row = y % 16;
            if (row < 8 && x >= 16 && (x % 16) < 12)
                ink = 7;
            if (y >= h - 16 && x < 24)
                ink = 7;
            dst[y * w + x] = ink;
        }
    }
}

static int wlcomp_demo(wl_comp_t *c) {
    wl_client_t cl;
    unsigned int s0 = 0;
    unsigned int s1 = 0;
    wl_client_init(&cl);
    if (wl_client_surface(&cl, &s0) != WL_ERR_OK)
        return 1;
    if (wl_client_surface(&cl, &s1) != WL_ERR_OK)
        return 1;
    if (wl_comp_add(c, s0, 320, 200) != WL_ERR_OK)
        return 1;
    if (wl_comp_add(c, s1, 320, 200) != WL_ERR_OK)
        return 1;
    if (wl_comp_set_color(c, s0, 4) != WL_ERR_OK)
        return 1;
    if (wl_comp_set_color(c, s1, 6) != WL_ERR_OK)
        return 1;
    if (wl_comp_layout_tile(c, WLCOMP_W, WLCOMP_H) != 2)
        return 1;
    if (wl_comp_focus(c, s0) != WL_ERR_OK)
        return 1;
    return 0;
}

/** Composite the tiled demo with real client pixels into the frame. */
static int wlcomp_demo_blit(wl_comp_t *c, unsigned char *fb) {
    wlcomp_cfg_t cfg = WLCOMP_CFG_DEFAULT;
    const unsigned char *px[WL_MAX_SURFACES];
    int pw[WL_MAX_SURFACES];
    int ph[WL_MAX_SURFACES];
    unsigned char *p0 = 0;
    unsigned char *p1 = 0;
    int w0;
    int h0;
    int w1;
    int h1;
    int i;
    int rc;
    for (i = 0; i < WL_MAX_SURFACES; i++) {
        px[i] = 0;
        pw[i] = 0;
        ph[i] = 0;
    }
    w0 = c->items[c->order[0]].w;
    h0 = c->items[c->order[0]].h;
    w1 = c->items[c->order[1]].w;
    h1 = c->items[c->order[1]].h;
    if (w0 <= 0 || h0 <= 0 || w1 <= 0 || h1 <= 0)
        return 1;
    p0 = malloc((unsigned long)w0 * (unsigned long)h0);
    p1 = malloc((unsigned long)w1 * (unsigned long)h1);
    if (!p0 || !p1) {
        free(p0);
        free(p1);
        return 1;
    }
    wlcomp_pattern(p0, w0, h0, cfg.stripe_a, cfg.stripe_b, 0);
    wlcomp_pattern(p1, w1, h1, cfg.check_a, cfg.check_b, 1);
    px[c->order[0]] = p0;
    pw[c->order[0]] = w0;
    ph[c->order[0]] = h0;
    px[c->order[1]] = p1;
    pw[c->order[1]] = w1;
    ph[c->order[1]] = h1;
    rc = wlcomp_blit(c, fb, WLCOMP_W, WLCOMP_H, px, pw, ph);
    free(p0);
    free(p1);
    return rc != WL_ERR_OK;
}

/** Append one header-only request to a session buffer. */
static int wlcomp_emit(unsigned char *s, int cap, int o, unsigned int id,
        unsigned int op, unsigned int size) {
    wl_hdr_t h;
    if (!s || o < 0 || cap - o < (int)size)
        return -1;
    if (wl_hdr_encode(s + o, cap - o, id, op, size, &h) != WL_ERR_OK)
        return -1;
    return o + (int)size;
}

/** Drive a full client session through stream plus dispatch. The byte
 * feed splits mid-header so reassembly is proven, not assumed. */
static int wlcomp_session(wl_comp_t *c, wl_client_t *cl) {
    unsigned char s[256];
    wl_stream_t st;
    wl_hdr_t m;
    int o = 0;
    int sz = 0;
    int n = 0;
    o = wlcomp_emit(s, 256, o, WL_ID_DISPLAY,
        WL_OP_DISPLAY_GET_REGISTRY, 8);
    if (o < 0)
        return 1;
    o = wlcomp_emit(s, 256, o, WL_ID_REGISTRY, WL_OP_REGISTRY_BIND, 12);
    if (o < 0)
        return 1;
    if (wl_u32_encode(s, 256, o - 4, WL_ID_COMPOSITOR) != WL_ERR_OK)
        return 1;
    o = wlcomp_emit(s, 256, o, WL_ID_COMPOSITOR,
        WL_OP_COMPOSITOR_CREATE_SURFACE, 8);
    if (o < 0)
        return 1;
    o = wlcomp_emit(s, 256, o, WL_ID_SHM, WL_OP_SHM_CREATE_POOL, 8);
    if (o < 0)
        return 1;
    o = wlcomp_emit(s, 256, o, WL_ID_SURFACE_BASE, WL_OP_SURFACE_ATTACH,
        20);
    if (o < 0)
        return 1;
    if (wl_attach_encode(s + o - 12, 12, WL_ID_POOL_BASE, 8, 6)
        != WL_ATTACH_SZ)
        return 1;
    o = wlcomp_emit(s, 256, o, WL_ID_SURFACE_BASE, WL_OP_SURFACE_COMMIT,
        8);
    if (o < 0)
        return 1;
    o = wlcomp_emit(s, 256, o, WL_ID_COMPOSITOR,
        WL_OP_COMPOSITOR_CREATE_SURFACE, 8);
    if (o < 0)
        return 1;
    o = wlcomp_emit(s, 256, o, WL_ID_SURFACE_BASE + 1,
        WL_OP_SURFACE_ATTACH, 20);
    if (o < 0)
        return 1;
    if (wl_attach_encode(s + o - 12, 12, WL_ID_POOL_BASE, 8, 6)
        != WL_ATTACH_SZ)
        return 1;
    o = wlcomp_emit(s, 256, o, WL_ID_SURFACE_BASE + 1,
        WL_OP_SURFACE_COMMIT, 8);
    if (o < 0)
        return 1;
    wl_stream_init(&st);
    if (wl_stream_feed(&st, s, 5) != WL_ERR_OK)
        return 1;
    if (wl_stream_next(&st, &sz) != WL_ERR_MORE)
        return 1;
    if (wl_stream_feed(&st, s + 5, o - 5) != WL_ERR_OK)
        return 1;
    while (wl_stream_next(&st, &sz) == WL_ERR_OK) {
        if (wl_hdr_decode(st.buf, sz, &m) != WL_ERR_OK)
            return 1;
        if (wl_dispatch(c, cl, m.id, m.opcode, st.buf + 8, sz - 8)
            != WL_ERR_OK)
            return 1;
        if (wl_stream_consume(&st, sz) != WL_ERR_OK)
            return 1;
        n++;
        if (n > 16)
            return 1;
    }
    if (n != 9 || c->count != 2)
        return 1;
    return 0;
}

static int wlcomp_selftest(void) {
    wl_comp_t c;
    wl_client_t cl;
    unsigned char fb[16 * 10];
    unsigned char src[8 * 10];
    const unsigned char *px[WL_MAX_SURFACES];
    int pw[WL_MAX_SURFACES];
    int ph[WL_MAX_SURFACES];
    unsigned int other = 0;
    int hit;
    int i;

    wl_comp_init(&c);
    wl_client_init(&cl);
    if (wlcomp_session(&c, &cl) != 0)
        return 1;
    other = WL_ID_SURFACE_BASE + 1;
    if (wl_comp_layout_tile(&c, 16, 10) != 2)
        return 1;
    if (wl_comp_focus(&c, WL_ID_SURFACE_BASE) != WL_ERR_OK)
        return 1;
    hit = wl_comp_hit(&c, 2, 2);
    if (hit != (int)WL_ID_SURFACE_BASE)
        return 1;
    for (i = 0; i < WL_MAX_SURFACES; i++) {
        px[i] = 0;
        pw[i] = 0;
        ph[i] = 0;
    }
    for (i = 0; i < 8 * 10; i++)
        src[i] = 7;
    px[0] = src;
    pw[0] = 8;
    ph[0] = 10;
    if (wlcomp_blit(&c, fb, 16, 10, px, pw, ph) != WL_ERR_OK)
        return 1;
    if (fb[0] == WLCOMP_BG)
        return 1;
    if (wl_comp_remove(&c, other) != WL_ERR_OK)
        return 1;
    if (c.count != 1)
        return 1;
    printf("wlcomp: frame ok (%dx%d)\n", WLCOMP_W, WLCOMP_H);
    return 0;
}

/** Live server state: compositor plus mailbox slots plus one
 * cached pixel buffer per surface, indexed by items slot. The cache
 * is a static pool, never malloc in the frame loop: wlserv_fit loads
 * the box raw file into a static scratch, resamples into a second
 * scratch, then copies into the slot buffer. */
static unsigned char wlserv_pool[WL_MAX_SURFACES][WL_POOL_MAX];
static unsigned char wlserv_raw[WL_POOL_MAX];
static unsigned char wlserv_dst[WL_POOL_MAX];

typedef struct {
    wl_comp_t comp;
    wl_mbox_box_t boxes[WL_MAX_SURFACES];
    int pw[WL_MAX_SURFACES];
    int ph[WL_MAX_SURFACES];
    int rw[WL_MAX_SURFACES];
    int rh[WL_MAX_SURFACES];
    int origin[2];
    int last_count;
} wlserv_t;

static void wlserv_init(wlserv_t *s) {
    int i;
    wl_comp_init(&s->comp);
    wl_mbox_init(s->boxes);
    for (i = 0; i < WL_MAX_SURFACES; i++) {
        s->pw[i] = 0;
        s->ph[i] = 0;
        s->rw[i] = 0;
        s->rh[i] = 0;
    }
    s->origin[0] = 0;
    s->origin[1] = 0;
    s->last_count = 0;
}

/** Items index owning a surface id, or -1 for a stranger. */
static int wlserv_slot(const wl_comp_t *c, unsigned int id) {
    int i;
    if (!c)
        return -1;
    for (i = 0; i < WL_MAX_SURFACES; i++) {
        if (c->items[i].id == id)
            return i;
    }
    return -1;
}

/** Paint every mapped slot a distinct desktop-exact ink so clients
 * without pixels still read as separate windows. */
static void wlserv_recolor(wl_comp_t *c) {
    static const unsigned char inks[WL_MAX_SURFACES] = {
        4, 6, 12, 13, 9, 10, 7, 2
    };
    int i;
    if (!c)
        return;
    for (i = 0; i < WL_MAX_SURFACES; i++) {
        if (c->items[i].id != 0)
            c->items[i].color = (int)inks[i % WL_MAX_SURFACES];
    }
}

/** Composite the cached pixels and present with palette uploaded,
 * capturing the content origin for pointer translation. Chrome
 * (title bar plus close box plus active focus) paints here so every
 * frame carries real window decorations. */
static int wlserv_present(wlserv_t *s) {
    unsigned char *fb = (unsigned char *)MINIOS_NK_BACKBUF_ADDR;
    const unsigned char *px[WL_MAX_SURFACES];
    int i;
    if (!s)
        return 1;
    if (wlcomp_palette() != 0)
        return 1;
    for (i = 0; i < WL_MAX_SURFACES; i++)
        px[i] = s->pw[i] > 0 && s->ph[i] > 0 ? wlserv_pool[i] : 0;
    if (wlcomp_blit_chrome(&s->comp, fb, WLCOMP_W, WLCOMP_H, px, s->pw,
            s->ph) != WL_ERR_OK)
        return 1;
    wlcomp_sys_title("wlcomp");
    if (wlcomp_sys_present_origin((long)MINIOS_GFX_BUF_NK,
            s->origin) != 0)
        return 1;
    return 0;
}

/** Drop one slot cache so its surface falls back to solid ink. */
static void wlserv_drop(wlserv_t *s, int idx) {
    if (!s || idx < 0 || idx >= WL_MAX_SURFACES)
        return;
    s->pw[idx] = 0;
    s->ph[idx] = 0;
}

/** Fit every mapped surface to its laid-out size: reload the box raw
 * file at attach dims, then resample into the live cell. Static
 * scratch only, never malloc: any short file or size lie drops that
 * cache, never a neighbour, so one hostile client cannot blank the
 * desktop. */
static void wlserv_fit(wlserv_t *s) {
    int b = 0;
    for (b = 0; b < WL_MAX_SURFACES; b++) {
        char path[WL_MBOX_NAME_MAX];
        FILE *f = 0;
        long n = 0;
        long want = 0;
        long cells = 0;
        int idx = -1;
        int w = 0;
        int h = 0;
        int k = 0;
        if (!s || !s->boxes[b].used)
            continue;
        idx = wlserv_slot(&s->comp,
            WL_ID_SURFACE_BASE + (unsigned int)b);
        if (idx < 0 || !s->comp.items[idx].mapped
            || s->comp.items[idx].minimized) {
            continue;
        }
        w = s->comp.items[idx].w;
        h = s->comp.items[idx].h;
        if (s->rw[idx] <= 0 || s->rh[idx] <= 0) {
            wlserv_drop(s, idx);
            continue;
        }
        want = (long)s->rw[idx] * (long)s->rh[idx];
        cells = (long)w * (long)h;
        if (want <= 0 || want > (long)WL_POOL_MAX || cells <= 0
            || cells > (long)WL_POOL_MAX) {
            wlserv_drop(s, idx);
            continue;
        }
        if (wl_mbox_raw_name(path, sizeof path,
                s->boxes[b].box) <= 0) {
            wlserv_drop(s, idx);
            continue;
        }
        f = fopen(path, "rb");
        if (!f) {
            wlserv_drop(s, idx);
            continue;
        }
        if (fseek(f, 0, SEEK_END) != 0) {
            fclose(f);
            wlserv_drop(s, idx);
            continue;
        }
        n = ftell(f);
        if (n != want || fseek(f, 0, SEEK_SET) != 0) {
            fclose(f);
            wlserv_drop(s, idx);
            continue;
        }
        if (fread(wlserv_raw, 1, (unsigned long)n, f)
            != (unsigned long)n) {
            fclose(f);
            wlserv_drop(s, idx);
            continue;
        }
        fclose(f);
        if (wl_scale_nearest(wlserv_dst, w, h, wlserv_raw, s->rw[idx],
                s->rh[idx]) != WL_ERR_OK) {
            wlserv_drop(s, idx);
            continue;
        }
        for (k = 0; k < cells; k++)
            wlserv_pool[idx][k] = wlserv_dst[k];
        s->pw[idx] = w;
        s->ph[idx] = h;
    }
}

/** Unlink stray .msg files no client owns: names that fail the exact
 * mailbox parse can never dispatch, so they are dead weight from a
 * crashed client. The mirror flag carries no suffix and is kept. */
static void wlserv_gc_strays(void) {
    char names[4096];
    long count = 0;
    char *p = 0;
    long k = 0;
    count = wlcomp_sys_dir_list(WL_MBOX_DIR, names, sizeof names);
    if (count <= 0)
        return;
    p = names;
    for (k = 0; k < count; k++) {
        int nl = 0;
        int dot = -1;
        int i = 0;
        char box[WL_MBOX_BOX_MAX];
        unsigned int seq = 0;
        char path[WL_MBOX_NAME_MAX];
        int di = 0;
        while (p[nl] != '\0')
            nl++;
        for (i = 0; i < nl; i++) {
            if (p[i] == '.')
                dot = i;
        }
        if (dot < 0) {
            p += nl + 1;
            continue;
        }
        if (strcmp(p + dot, WL_MBOX_SUFFIX) != 0) {
            p += nl + 1;
            continue;
        }
        di = 0;
        i = 0;
        while (WL_MBOX_DIR[i] != '\0')
            path[di++] = WL_MBOX_DIR[i++];
        path[di++] = '/';
        i = 0;
        while (p[i] != '\0' && di < WL_MBOX_NAME_MAX - 1)
            path[di++] = p[i++];
        path[di] = '\0';
        if (p[i] != '\0'
            || wl_mbox_parse(path, box, sizeof box, &seq)
                == WL_ERR_OK) {
            p += nl + 1;
            continue;
        }
        unlink(path);
        p += nl + 1;
    }
}

/** Server-to-client input delivery (ADR-0026 live step). The server
 * owns PS/2 while it owns the display, so it forwards raw scancodes
 * plus mapped pointer state to the focused box through its .ev file.
 * Queues are static (never malloc): a full queue drops the oldest
 * byte, a slow client loses middle batches by seq design. */
static unsigned char wlserv_ev_pend[WL_MAX_SURFACES][WL_EV_SC_MAX];
static unsigned wlserv_ev_npend[WL_MAX_SURFACES];
static unsigned wlserv_ev_seq[WL_MAX_SURFACES];
static unsigned wlserv_ev_wheel = 0;

/** Focused box slot, or -1 when no mapped window holds input. */
static int wlserv_focus_box(const wlserv_t *s) {
    unsigned int id = 0;
    int b = -1;
    if (!s || s->comp.count <= 0)
        return -1;
    id = s->comp.items[s->comp.order[s->comp.count - 1]].id;
    if (!wl_surface_id_valid(id))
        return -1;
    b = (int)(id - WL_ID_SURFACE_BASE);
    if (b < 0 || b >= WL_MAX_SURFACES)
        return -1;
    if (!s->boxes[b].used)
        return -1;
    return b;
}

/** Queue one raw byte for the focused client. Bytes nobody owns are
 * dropped, never buffered: input without a window is noise. */
static void wlserv_key(wlserv_t *s, unsigned char byte) {
    int b = 0;
    unsigned n = 0;
    unsigned i = 0;
    if (!s)
        return;
    b = wlserv_focus_box(s);
    if (b < 0)
        return;
    n = wlserv_ev_npend[b];
    if (n >= WL_EV_SC_MAX) {
        for (i = 0; i + 1 < WL_EV_SC_MAX; i++)
            wlserv_ev_pend[b][i] = wlserv_ev_pend[b][i + 1];
        n = WL_EV_SC_MAX - 1;
    }
    wlserv_ev_pend[b][n] = byte;
    wlserv_ev_npend[b] = n + 1;
}

/** Drop a slot queue without serving it. */
static void wlserv_ev_clear(wlserv_t *s, int b) {
    (void)s;
    if (b < 0 || b >= WL_MAX_SURFACES)
        return;
    wlserv_ev_npend[b] = 0;
}

/** Push the current input state to the focused box. Frame coords map
 * into the client's raw buffer through wl_ev_map; outside is (-1,-1)
 * so the client never warps a click. The queue clears after write,
 * which is what keeps batches from replaying. */
static void wlserv_push_ev(wlserv_t *s, int fx, int fy, int buttons) {
    wl_ev_t e;
    unsigned char frame[WL_EV_SZ];
    char path[WL_MBOX_NAME_MAX];
    FILE *f = 0;
    int b = 0;
    int idx = -1;
    int cx = -1;
    int cy = -1;
    unsigned i = 0;
    if (!s)
        return;
    b = wlserv_focus_box(s);
    if (b < 0)
        return;
    idx = wlserv_slot(&s->comp, WL_ID_SURFACE_BASE + (unsigned int)b);
    if (idx < 0)
        return;
    wl_ev_map(fx, fy, s->comp.items[idx].x, s->comp.items[idx].y,
        s->comp.items[idx].w, s->comp.items[idx].h, s->rw[idx],
        s->rh[idx], &cx, &cy);
    e.seq = ++wlserv_ev_seq[b];
    e.mx = cx;
    e.my = cy;
    e.buttons = (unsigned int)(buttons & 7);
    e.wheel = wlserv_ev_wheel;
    e.nsc = wlserv_ev_npend[b] > WL_EV_SC_MAX ? WL_EV_SC_MAX
        : wlserv_ev_npend[b];
    for (i = 0; i < WL_EV_SC_MAX; i++)
        e.sc[i] = i < e.nsc ? wlserv_ev_pend[b][i] : 0;
    wlserv_ev_npend[b] = 0;
    if (wl_ev_encode(frame, sizeof frame, &e) != WL_EV_SZ)
        return;
    if (wl_mbox_ev_name(path, sizeof path, s->boxes[b].box) <= 0)
        return;
    f = fopen(path, "wb");
    if (!f)
        return;
    if (fwrite(frame, 1, sizeof frame, f) != sizeof frame) {
        fclose(f);
        return;
    }
    fclose(f);
}

/** Unlink every stale .ev file so no dead input replays after a
 * restart. Runs once at server start; live files are rewritten by
 * their owners from then on. */
static void wlserv_clean_ev(void) {
    char names[4096];
    long count = 0;
    char *p = 0;
    long k = 0;
    count = wlcomp_sys_dir_list(WL_MBOX_DIR, names, sizeof names);
    if (count <= 0)
        return;
    p = names;
    for (k = 0; k < count; k++) {
        int nl = 0;
        int dot = -1;
        int i = 0;
        char path[WL_MBOX_NAME_MAX];
        int di = 0;
        while (p[nl] != '\0')
            nl++;
        for (i = 0; i < nl; i++) {
            if (p[i] == '.')
                dot = i;
        }
        if (dot >= 0 && strcmp(p + dot, WL_MBOX_EV_SUFFIX) == 0) {
            di = 0;
            i = 0;
            while (WL_MBOX_DIR[i] != '\0')
                path[di++] = WL_MBOX_DIR[i++];
            path[di++] = '/';
            i = 0;
            while (p[i] != '\0' && di < WL_MBOX_NAME_MAX - 1)
                path[di++] = p[i++];
            path[di] = '\0';
            if (p[i] == '\0')
                unlink(path);
        }
        p += nl + 1;
    }
}

/** Close one surface by id: remove it, free its box slot for the next
 * client, drop its cache and unlink its raw pixels. Returns 1 when
 * something closed. A live client re-attaches on its next frame, so
 * closing a live window also wants the client's job killed from the
 * shell; the box name carries the client pid for exactly that. */
static int wlserv_close(wlserv_t *s, unsigned int id) {
    int b = 0;
    int idx = -1;
    char path[WL_MBOX_NAME_MAX];
    if (!s || !wl_surface_id_valid(id))
        return 0;
    b = (int)(id - WL_ID_SURFACE_BASE);
    if (b < 0 || b >= WL_MAX_SURFACES)
        return 0;
    idx = wlserv_slot(&s->comp, id);
    if (idx < 0)
        return 0;
    if (wl_comp_remove(&s->comp, id) != WL_ERR_OK)
        return 0;
    wlserv_drop(s, idx);
    s->rw[idx] = 0;
    s->rh[idx] = 0;
    wlserv_ev_clear(s, b);
    if (s->boxes[b].used) {
        if (wl_mbox_raw_name(path, sizeof path, s->boxes[b].box) > 0)
            unlink(path);
        if (wl_mbox_ev_name(path, sizeof path, s->boxes[b].box) > 0)
            unlink(path);
        s->boxes[b].used = 0;
        s->boxes[b].box[0] = '\0';
        s->boxes[b].seq_last = 0;
    }
    wlserv_recolor(&s->comp);
    return 1;
}

/** Drain at most WL_MBOX_POLL_MAX mailbox files: validate every frame
 * before dispatch, unlink what was consumed, and leave torn writes
 * for the next poll. Returns 1 when pixels changed. */
static int wlserv_drain(wlserv_t *s) {
    char names[4096];
    long count = 0;
    char *p = 0;
    long k = 0;
    int changed = 0;
    int routed = 0;
    if (!s)
        return 0;
    count = wlcomp_sys_dir_list(WL_MBOX_DIR, names, sizeof names);
    if (count <= 0)
        return 0;
    p = names;
    for (k = 0; k < count && routed < WL_MBOX_POLL_MAX; k++) {
        char box[WL_MBOX_BOX_MAX];
        char path[WL_MBOX_NAME_MAX];
        unsigned int seq = 0;
        int slot = -1;
        int w = -1;
        int h = -1;
        int di = 0;
        FILE *f = 0;
        long n = 0;
        unsigned char file[WL_MAX_MSG + WL_MBOX_FRAME_HEAD + 1];
        unsigned int fseq = 0;
        int off = 0;
        int mlen = 0;
        wl_hdr_t mh;
        int r = 0;
        int nl = 0;
        int pi = 0;
        int ei = 0;
        while (p[nl] != '\0')
            nl++;
        while (WL_MBOX_DIR[pi] != '\0'
            && pi < WL_MBOX_NAME_MAX - 1) {
            path[pi] = WL_MBOX_DIR[pi];
            pi++;
        }
        if (pi >= WL_MBOX_NAME_MAX - 1) {
            p += nl + 1;
            continue;
        }
        path[pi++] = '/';
        ei = 0;
        while (p[ei] != '\0' && pi < WL_MBOX_NAME_MAX - 1) {
            path[pi++] = p[ei++];
        }
        path[pi] = '\0';
        if (p[ei] != '\0'
            || wl_mbox_parse(path, box, sizeof box,
                &seq) != WL_ERR_OK) {
            p += nl + 1;
            continue;
        }
        slot = wl_mbox_assign(s->boxes, box);
        if (slot < 0) {
            p += nl + 1;
            continue;
        }
        if (wl_mbox_fresh(s->boxes, slot, seq) == 0) {
            di = wl_mbox_name(path, sizeof path, box, seq);
            if (di > 0)
                unlink(path);
            p += nl + 1;
            continue;
        }
        di = wl_mbox_name(path, sizeof path, box, seq);
        if (di <= 0) {
            p += nl + 1;
            continue;
        }
        f = fopen(path, "rb");
        if (!f) {
            p += nl + 1;
            continue;
        }
        if (fseek(f, 0, SEEK_END) != 0) {
            fclose(f);
            p += nl + 1;
            continue;
        }
        n = ftell(f);
        if (n < WL_MBOX_FRAME_HEAD || n > WL_MAX_MSG + WL_MBOX_FRAME_HEAD) {
            fclose(f);
            if (n >= 0 && n < WL_MBOX_FRAME_HEAD) {
                p += nl + 1;
                continue;
            }
            unlink(path);
            p += nl + 1;
            continue;
        }
        if (fseek(f, 0, SEEK_SET) != 0) {
            fclose(f);
            p += nl + 1;
            continue;
        }
        if (fread(file, 1, (unsigned long)n, f) != (unsigned long)n) {
            fclose(f);
            p += nl + 1;
            continue;
        }
        fclose(f);
        r = wl_mbox_frame_decode(file, (int)n, &fseq, &off, &mlen);
        if (r == WL_ERR_TRUNC) {
            p += nl + 1;
            continue;
        }
        if (r != WL_ERR_OK) {
            unlink(path);
            p += nl + 1;
            continue;
        }
        if (fseq != seq) {
            unlink(path);
            p += nl + 1;
            continue;
        }
        if (wl_hdr_decode(file + off, mlen, &mh) != WL_ERR_OK) {
            unlink(path);
            p += nl + 1;
            continue;
        }
        r = wl_mbox_route(&s->comp, s->boxes, box, mh.id, mh.opcode,
            file + off + WL_HDR_SZ, mlen - WL_HDR_SZ, &slot, &w, &h);
        if (r != WL_ERR_OK) {
            unlink(path);
            p += nl + 1;
            continue;
        }
        s->boxes[slot].seq_last = seq;
        s->boxes[slot].used = 1;
        unlink(path);
        routed++;
        if (w > 0 && h > 0) {
            int idx = wlserv_slot(&s->comp,
                WL_ID_SURFACE_BASE + (unsigned int)slot);
            if (idx >= 0) {
                wlserv_drop(s, idx);
                s->rw[idx] = w;
                s->rh[idx] = h;
            }
        }
        changed = 1;
        p += nl + 1;
    }
    if (changed)
        wlserv_recolor(&s->comp);
    return changed;
}

/** Client pattern table, one row per attachable demo client. */
typedef struct {
    const char *name;
    int w;
    int h;
    unsigned char a;
    unsigned char b;
    int checker;
    int term;
} wlclient_pat_t;

static const wlclient_pat_t *wlclient_find(const char *name) {
    static const wlclient_pat_t pats[] = {
        { "stripe", 400, 180, 4, 12, 0, 0 },
        { "checker", 320, 200, 6, 13, 1, 0 },
        { "field", 400, 180, 7, 3, 1, 0 },
        { "term", 400, 180, 6, 7, 0, 1 },
        { 0, 0, 0, 0, 0, 0, 0 }
    };
    int i = 0;
    int k = 0;
    if (!name)
        return 0;
    while (pats[i].name != 0) {
        k = 0;
        while (pats[i].name[k] != '\0' && name[k] != '\0'
            && pats[i].name[k] == name[k])
            k++;
        if (pats[i].name[k] == '\0' && name[k] == '\0')
            return &pats[i];
        i++;
    }
    return 0;
}

/** Attach one client surface from a second process through the
 * shared wl_client.h transport: pixels first so the server never
 * attaches a surface whose raw file is missing, then the six-message
 * session, each sequenced. One-shot malloc is fine here; the server
 * hot loop is the path that must never allocate. */
static int wlcomp_client(const char *box, const char *pat) {
    const wlclient_pat_t *cp = 0;
    unsigned char *raw = 0;
    unsigned char msg[WL_MAX_MSG];
    wl_hdr_t h;
    unsigned int seq = 1;
    cp = wlclient_find(pat);
    if (!cp || wl_mbox_box_ok(box) != WL_ERR_OK) {
        printf("usage: wlcomp --client <box> <stripe|checker|field|term>\n");
        return 2;
    }
    raw = malloc((unsigned long)cp->w * (unsigned long)cp->h);
    if (!raw) {
        printf("wlcomp: client out of memory\n");
        return 1;
    }
    if (cp->term)
        wlcomp_term_pattern(raw, cp->w, cp->h);
    else
        wlcomp_pattern(raw, cp->w, cp->h, cp->a, cp->b, cp->checker);
    if (wl_client_raw_file(box, raw, cp->w, cp->h) != WL_ERR_OK) {
        printf("wlcomp: client cannot write pixels\n");
        free(raw);
        return 1;
    }
    free(raw);
    if (wl_hdr_encode(msg, sizeof msg, WL_ID_DISPLAY,
            WL_OP_DISPLAY_GET_REGISTRY, 8, &h) != WL_ERR_OK)
        return 1;
    if (wl_client_emit_file(box, seq++, msg, 8) != WL_ERR_OK)
        return 1;
    if (wl_hdr_encode(msg, sizeof msg, WL_ID_REGISTRY, WL_OP_REGISTRY_BIND,
            12, &h) != WL_ERR_OK)
        return 1;
    if (wl_u32_encode(msg, sizeof msg, 8, WL_ID_COMPOSITOR) != WL_ERR_OK)
        return 1;
    if (wl_client_emit_file(box, seq++, msg, 12) != WL_ERR_OK)
        return 1;
    if (wl_hdr_encode(msg, sizeof msg, WL_ID_COMPOSITOR,
            WL_OP_COMPOSITOR_CREATE_SURFACE, 8, &h) != WL_ERR_OK)
        return 1;
    if (wl_client_emit_file(box, seq++, msg, 8) != WL_ERR_OK)
        return 1;
    if (wl_hdr_encode(msg, sizeof msg, WL_ID_SHM, WL_OP_SHM_CREATE_POOL,
            8, &h) != WL_ERR_OK)
        return 1;
    if (wl_client_emit_file(box, seq++, msg, 8) != WL_ERR_OK)
        return 1;
    if (wl_hdr_encode(msg, sizeof msg, WL_ID_SURFACE_BASE,
            WL_OP_SURFACE_ATTACH, 20, &h) != WL_ERR_OK)
        return 1;
    if (wl_attach_encode(msg + 8, (int)sizeof msg - 8, WL_ID_POOL_BASE,
            cp->w, cp->h) != WL_ATTACH_SZ)
        return 1;
    if (wl_client_emit_file(box, seq++, msg, 20) != WL_ERR_OK)
        return 1;
    if (wl_hdr_encode(msg, sizeof msg, WL_ID_SURFACE_BASE,
            WL_OP_SURFACE_COMMIT, 8, &h) != WL_ERR_OK)
        return 1;
    if (wl_client_emit_file(box, seq++, msg, 8) != WL_ERR_OK)
        return 1;
    printf("wlcomp: client %s attached (%dx%d)\n", box, cp->w, cp->h);
    return 0;
}

/** Unlink every mailbox file so a new session starts clean. */
static int wlcomp_clean(void) {
    char names[4096];
    long count = 0;
    char *p = 0;
    long k = 0;
    int n = 0;
    char path[WL_MBOX_NAME_MAX];
    count = wlcomp_sys_dir_list(WL_MBOX_DIR, names, sizeof names);
    if (count <= 0) {
        printf("wlcomp: cleaned 0 files\n");
        return 0;
    }
    p = names;
    for (k = 0; k < count; k++) {
        int nl = 0;
        int di = 0;
        int i = 0;
        while (p[nl] != '\0')
            nl++;
        di = 0;
        i = 0;
        while (WL_MBOX_DIR[i] != '\0')
            path[di++] = WL_MBOX_DIR[i++];
        path[di++] = '/';
        i = 0;
        while (p[i] != '\0' && di < WL_MBOX_NAME_MAX - 1)
            path[di++] = p[i++];
        path[di] = '\0';
        if (p[i] == '\0')
            if (unlink(path) == 0)
                n++;
        p += nl + 1;
    }
    printf("wlcomp: cleaned %d files\n", n);
    return 0;
}

/** Drain once and exit so scripts prove multiprocess composition
 * through the gfx frames counter without an interactive loop. */
static int wlcomp_once(void) {
    wlserv_t s;
    wlserv_init(&s);
    wlcomp_sys_vga_mode(1L);
    if (wlserv_drain(&s) == 0 && s.comp.count == 0) {
        wlcomp_sys_vga_mode(0L);
        printf("wlcomp: mapped 0 surfaces (%dx%d)\n", WLCOMP_W, WLCOMP_H);
        return 0;
    }
    if (wl_comp_layout_tile(&s.comp, WLCOMP_W, WLCOMP_H) <= 0) {
        wlcomp_sys_vga_mode(0L);
        return 1;
    }
    wlserv_recolor(&s.comp);
    wlserv_fit(&s);
    if (wlserv_present(&s) != 0) {
        wlcomp_sys_vga_mode(0L);
        return 1;
    }
    printf("wlcomp: mapped %d surfaces (%dx%d)\n", s.comp.count, WLCOMP_W,
        WLCOMP_H);
    wlcomp_sys_vga_mode(0L);
    return 0;
}

/** Interactive desktop: click focuses, title drag moves, rim drag
 * resizes, close box closes, Alt+T re-tiles, Alt+M minimizes,
 * Alt+U restores, Alt+Q quits with the desktop redrawn behind it.
 * Plain keys always reach the focused client through its .ev file;
 * only Alt-held combos act on the server, so typing never tiles.
 * A /shm/wl/quit flag file quits cleanly too (the `desktop stop`
 * path, which cannot send keystrokes to a background job). */
static int wlcomp_server(void) {
    wlserv_t s;
    long tick = 0;
    int dragging = -1;
    int dragmode = WL_HIT_NONE;
    int grabx = 0;
    int graby = 0;
    int grabw = 0;
    int grabh = 0;
    int alt_held = 0;
    int lastfx = -1000000;
    int lastfy = -1000000;
    int lastbtn = -1;
    int lastfocus = -2;
    int ev_force = 1;
    wlserv_init(&s);
    wlcomp_sys_vga_mode(1L);
    wlcomp_sys_kbd_raw(1L);
    wlserv_clean_ev();
    wlserv_drain(&s);
    if (s.comp.count > 0) {
        if (wl_comp_layout_tile(&s.comp, WLCOMP_W, WLCOMP_H) <= 0)
            return 1;
        wlserv_recolor(&s.comp);
        wlserv_fit(&s);
        s.last_count = s.comp.count;
    }
    if (wlserv_present(&s) != 0)
        return 1;
    for (;;) {
        int m[4];
        long sc = 0;
        int fx = -1000000;
        int fy = -1000000;
        int buttons = 0;
        int focusb = -1;
        tick++;
        if (tick % 64 == 0)
            wlserv_gc_strays();
        if (tick % 8 == 0) {
            FILE *qf = fopen(WL_MBOX_DIR "/quit", "rb");
            if (qf) {
                fclose(qf);
                unlink(WL_MBOX_DIR "/quit");
                goto done;
            }
            if (wlserv_drain(&s) != 0) {
                if (s.comp.count != s.last_count) {
                    if (wl_comp_layout_tile(&s.comp, WLCOMP_W,
                            WLCOMP_H) <= 0)
                        break;
                    s.last_count = s.comp.count;
                }
                wlserv_fit(&s);
                if (wlserv_present(&s) != 0)
                    break;
                ev_force = 1;
            }
        }
        if (wlcomp_sys_mouse(m) == 0) {
            fx = m[0] - s.origin[0];
            fy = m[1] - s.origin[1];
            buttons = m[2] & 7;
            wlserv_ev_wheel += (unsigned)m[3];
            {
                int left = (buttons & 1) != 0;
            if (left && dragging < 0) {
                int hit = wl_comp_hit(&s.comp, fx, fy);
                if (hit >= 0) {
                    int idx = wlserv_slot(&s.comp, (unsigned int)hit);
                    int zone = WL_HIT_NONE;
                    if (idx >= 0)
                        zone = wl_surface_hit_zone(&s.comp.items[idx],
                            fx, fy);
                    if (zone == WL_HIT_CLOSE) {
                        if (wlserv_close(&s, (unsigned int)hit)) {
                            s.last_count = s.comp.count;
                            if (s.comp.count > 0) {
                                if (wl_comp_layout_tile(&s.comp,
                                        WLCOMP_W, WLCOMP_H) <= 0)
                                    break;
                                s.last_count = s.comp.count;
                                wlserv_fit(&s);
                            }
                            if (wlserv_present(&s) != 0)
                                break;
                        }
                    } else if (idx >= 0 && zone != WL_HIT_NONE) {
                        wl_comp_focus(&s.comp, (unsigned int)hit);
                        dragging = idx;
                        dragmode = zone;
                        grabx = fx - s.comp.items[idx].x;
                        graby = fy - s.comp.items[idx].y;
                        grabw = s.comp.items[idx].w;
                        grabh = s.comp.items[idx].h;
                        ev_force = 1;
                        if (wlserv_present(&s) != 0)
                            break;
                    }
                }
            } else if (left && dragging >= 0) {
                unsigned int id = s.comp.items[dragging].id;
                int x0 = s.comp.items[dragging].x;
                int y0 = s.comp.items[dragging].y;
                if (id != 0 && dragmode == WL_HIT_RESIZE) {
                    int w = fx - x0 + 1;
                    int h = fy - y0 + 1;
                    if (w < WL_CLOSE_W + 8)
                        w = WL_CLOSE_W + 8;
                    if (h < WL_TITLE_H + 8)
                        h = WL_TITLE_H + 8;
                    if (wl_comp_set_rect(&s.comp, id, x0, y0, w,
                            h) == WL_ERR_OK) {
                        wlserv_fit(&s);
                        if (wlserv_present(&s) != 0)
                            break;
                    }
                } else if (id != 0) {
                    int w = grabw;
                    int h = grabh;
                    if (wl_comp_set_rect(&s.comp, id, fx - grabx,
                            fy - graby, w, h) == WL_ERR_OK) {
                        if (wlserv_present(&s) != 0)
                            break;
                    }
                }
            } else if (!left) {
                dragging = -1;
                dragmode = WL_HIT_NONE;
            }
            }
        }
        sc = wlcomp_sys_kbd();
        while (sc >= 0) {
            if (sc == 0xE0L) {
                long sc2 = wlcomp_sys_kbd();
                if (sc2 < 0)
                    break;
                if ((sc2 & 0x7FL) == 0x38L)
                    alt_held = !(sc2 & 0x80L);
                wlserv_key(&s, (unsigned char)sc);
                wlserv_key(&s, (unsigned char)sc2);
                ev_force = 1;
                sc = wlcomp_sys_kbd();
            } else {
                unsigned char byte = (unsigned char)sc;
                int make = !(sc & 0x80L);
                long code = sc & 0x7FL;
                int i = 0;
                if (code == 0x38L)
                    alt_held = make;
                if (make && alt_held && (code == 0x14L || code == 0x32L
                        || code == 0x16L || code == 0x10L)) {
                    if (code == 0x10L)
                        goto done;
                    if (code == 0x14L) {
                        if (wl_comp_layout_tile(&s.comp, WLCOMP_W,
                                WLCOMP_H) <= 0)
                            goto done;
                        wlserv_fit(&s);
                        if (wlserv_present(&s) != 0)
                            goto done;
                        ev_force = 1;
                    }
                    if (code == 0x32L && s.comp.focus >= 0) {
                        unsigned int id =
                            s.comp.items[s.comp.focus].id;
                        if (id != 0
                            && wl_comp_set_minimized(&s.comp, id,
                                1) == WL_ERR_OK) {
                            if (wlserv_present(&s) != 0)
                                goto done;
                            ev_force = 1;
                        }
                    }
                    if (code == 0x16L) {
                        for (i = 0; i < WL_MAX_SURFACES; i++) {
                            if (s.comp.items[i].id != 0)
                                s.comp.items[i].minimized = 0;
                        }
                        wl_comp_refresh_active(&s.comp);
                        wlserv_fit(&s);
                        if (wlserv_present(&s) != 0)
                            goto done;
                        ev_force = 1;
                    }
                } else {
                    wlserv_key(&s, byte);
                    ev_force = 1;
                }
                sc = wlcomp_sys_kbd();
            }
        }
        focusb = wlserv_focus_box(&s);
        if (fx != -1000000 && (ev_force || fx != lastfx || fy != lastfy
                || buttons != lastbtn || focusb != lastfocus)) {
            wlserv_push_ev(&s, fx, fy, buttons);
            lastfx = fx;
            lastfy = fy;
            lastbtn = buttons;
            lastfocus = focusb;
            ev_force = 0;
        }
        wlcomp_sys_yield();
    }
done:
    wlcomp_sys_kbd_raw(0L);
    wlcomp_sys_vga_mode(0L);
    printf("wlcomp: server done (%d surfaces)\n", s.comp.count);
    return 0;
}

int main(int argc, char **argv) {
    if (argc == 2 && strcmp(argv[1], "--selftest") == 0)
        return wlcomp_selftest();
    if (argc == 2 && strcmp(argv[1], "--server") == 0)
        return wlcomp_server();
    if (argc == 2 && strcmp(argv[1], "--once") == 0)
        return wlcomp_once();
    if (argc == 2 && strcmp(argv[1], "--clean") == 0)
        return wlcomp_clean();
    if (argc == 4 && strcmp(argv[1], "--client") == 0)
        return wlcomp_client(argv[2], argv[3]);
    if (argc != 1) {
        printf("usage: wlcomp [--selftest|--server|--once|--clean]\n");
        printf("       wlcomp --client <box> <stripe|checker|field|term>\n");
        return 2;
    }
    {
        wl_comp_t c;
        unsigned char *fb = (unsigned char *)MINIOS_NK_BACKBUF_ADDR;
        wl_comp_init(&c);
        if (wlcomp_demo(&c) != 0) {
            printf("wlcomp: demo setup failed\n");
            return 1;
        }
        if (wlcomp_demo_blit(&c, fb) != 0) {
            printf("wlcomp: render failed\n");
            return 1;
        }
        if (wlcomp_palette() != 0) {
            printf("wlcomp: palette failed\n");
            return 1;
        }
        wlcomp_sys_title("wlcomp");
        wlcomp_sys_present((long)MINIOS_GFX_BUF_NK);
        printf("wlcomp: presented 2 surfaces (%dx%d)\n", WLCOMP_W, WLCOMP_H);
        return 0;
    }
}
