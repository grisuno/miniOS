/* nuklear_minios.c — MiniOS platform layer for Nuklear.
 *
 * Software rasterizer for an 8-bit indexed back-buffer: Nuklear emits an
 * abstract draw command list (nk__begin/nk__next); this layer rasterizes
 * every command into the palette-indexed back-buffer at NK_BACKBUF_ADDR with
 * scissor clipping, then the app calls MINIOS_SYS_GFX_PRESENT with
 * MINIOS_GFX_BUF_NK (220 stays as a kernel compat alias) to composite
 * the buffer as a titled desktop window. Colors are mapped to the hybrid palette
 * (indices 0-14 = desktop colors, 15-255 = UI ramp) by nearest neighbour.
 *
 * Input: raw PS/2 scancodes (SYS_KBD in raw mode) are translated to Nuklear
 * keys and unicode characters; the mouse (SYS_MOUSE) feeds motion/buttons/
 * wheel. All MiniOS-specific syscalls go through the Linux syscall ABI, so
 * this compiles into a normal static ring-3 ELF.
 */

#define NK_IMPLEMENTATION
#include "nuklear.h"

#include <string.h>
#include <stdio.h>
#include <math.h>

#include "nuklear_minios.h"

/* glibc program name for the mailbox box (GNU extension). */
extern char *program_invocation_short_name;
#include "nk_palette.h"
#include "wl/wl_mbox.h"
#include "wl/wl_client.h"

/* ---- MiniOS syscalls (canonical table from minios_abi.h) ---- */
long nk_sys_time_ms(void) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_TIME), "D"(0) : "rcx","r11","memory");
    return ret;
}
long nk_sys_kbd(void) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_KBD), "D"(0) : "rcx","r11","memory");
    return ret;
}
long nk_sys_palette(const unsigned char *pal) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_PALETTE), "D"(pal) : "rcx","r11","memory");
    return ret;
}
long nk_sys_kbd_raw(int on) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_KBD_RAW), "D"((long)on) : "rcx","r11","memory");
    return ret;
}
long nk_sys_getpid(void) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(39L) : "rcx","r11","memory");
    return ret;
}

/* Wayland client mode (ADR-0026 live step): when /shm/wl/client
 * exists this process is a pure producer for the wlcomp server. It
 * never takes the display (no VGA mode, no direct present) and never
 * touches PS/2; pixels go to its pid-unique mailbox every 2nd frame
 * and input arrives from its .ev file. Probed once per process. */
static int nk_client_on = -1;
static char nk_client_box[WL_MBOX_BOX_MAX];
static unsigned nk_client_seq = 1;
static unsigned nk_client_frame = 0;
static unsigned nk_client_ev_seq = 0;
static unsigned nk_client_ev_wheel = 0;
static int nk_client_ev_btn = 0;

static int nk_client_probe(void) {
    FILE *f = 0;
    long pid = 0;
    const char *prog = 0;
    if (nk_client_on >= 0) return nk_client_on;
    nk_client_on = 0;
    nk_client_box[0] = '\0';
    f = fopen(WL_MBOX_DIR "/client", "rb");
    if (!f) return 0;
    fclose(f);
    nk_client_on = 1;
    prog = program_invocation_short_name;
    if (!prog) prog = "nkapp";
    pid = nk_sys_getpid();
    if (pid < 0) pid = 0;
    if (wl_client_box(prog, pid, nk_client_box,
            sizeof nk_client_box) != WL_ERR_OK) {
        nk_client_on = 0;
        return 0;
    }
    f = NULL;
    {
        char evp[WL_MBOX_NAME_MAX];
        unsigned char raw[WL_EV_SZ];
        wl_ev_t e;
        size_t n = 0;
        if (wl_mbox_ev_name(evp, sizeof evp, nk_client_box) > 0) {
            f = fopen(evp, "rb");
            if (f) {
                n = fread(raw, 1, sizeof raw, f);
                fclose(f);
                if (n == sizeof raw
                    && wl_ev_decode(raw, (int)n, &e) == WL_ERR_OK) {
                    nk_client_ev_seq = e.seq;
                    nk_client_ev_wheel = e.wheel;
                }
            }
        }
    }
    return 1;
}

long nk_sys_vga_mode(int on) {
    long ret;
    (void)on;
    if (nk_client_probe()) return 0;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_VGA_MODE), "D"((long)on) : "rcx","r11","memory");
    return ret;
}
long nk_sys_fb_info(int *w, int *h, int *pitch) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret)
                     : "a"(MINIOS_SYS_FB_INFO), "D"(w), "S"(h), "d"(pitch)
                     : "rcx","r11","memory");
    return ret;
}
long nk_sys_mouse(int *xybw) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_MOUSE), "D"(xybw) : "rcx","r11","memory");
    return ret;
}
long nk_sys_mouse_badptr(void) {
    /* A kernel address (0x100000) is far outside the user window; the kernel
     * user_range_ok check must reject it with -EFAULT. */
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_MOUSE), "D"(0x100000L)
                     : "rcx","r11","memory");
    return ret;
}
static void nk_mirror_tick(void);

/* Publish one client frame through the shared mailbox transport:
 * pixels first, then the six-message session, each sequenced.
 * Damage-tracked: a 32-bit FNV over the backbuffer skips the whole
 * publish when nothing changed (an idle window costs zero fs churn,
 * which is what keeps several live clients from saturating the
 * mailbox), with a heartbeat every 32nd frame for resync. */
static unsigned nk_client_last_hash = 0;

static unsigned nk_client_hash(const unsigned char *p, unsigned n) {
    unsigned h = 2166136261u;
    unsigned i = 0;
    if (!p) return 0;
    for (i = 0; i < n; i++) {
        h ^= p[i];
        h *= 16777619u;
    }
    return h;
}

static int nk_client_publish(void) {
    unsigned char msg[WL_MAX_MSG];
    wl_hdr_t h;
    unsigned char *raw = 0;
    raw = (unsigned char *)NK_BACKBUF;
    if (wl_client_raw_file(nk_client_box, raw, NK_W, NK_H)
        != WL_ERR_OK)
        return 1;
    if (wl_hdr_encode(msg, sizeof msg, WL_ID_DISPLAY,
            WL_OP_DISPLAY_GET_REGISTRY, 8, &h) != WL_ERR_OK)
        return 1;
    if (wl_client_emit_file(nk_client_box, nk_client_seq++, msg, 8)
        != WL_ERR_OK)
        return 1;
    if (wl_hdr_encode(msg, sizeof msg, WL_ID_REGISTRY,
            WL_OP_REGISTRY_BIND, 12, &h) != WL_ERR_OK)
        return 1;
    if (wl_u32_encode(msg, sizeof msg, 8, WL_ID_COMPOSITOR)
        != WL_ERR_OK)
        return 1;
    if (wl_client_emit_file(nk_client_box, nk_client_seq++, msg, 12)
        != WL_ERR_OK)
        return 1;
    if (wl_hdr_encode(msg, sizeof msg, WL_ID_COMPOSITOR,
            WL_OP_COMPOSITOR_CREATE_SURFACE, 8, &h) != WL_ERR_OK)
        return 1;
    if (wl_client_emit_file(nk_client_box, nk_client_seq++, msg, 8)
        != WL_ERR_OK)
        return 1;
    if (wl_hdr_encode(msg, sizeof msg, WL_ID_SHM,
            WL_OP_SHM_CREATE_POOL, 8, &h) != WL_ERR_OK)
        return 1;
    if (wl_client_emit_file(nk_client_box, nk_client_seq++, msg, 8)
        != WL_ERR_OK)
        return 1;
    if (wl_hdr_encode(msg, sizeof msg, WL_ID_SURFACE_BASE,
            WL_OP_SURFACE_ATTACH, 20, &h) != WL_ERR_OK)
        return 1;
    if (wl_attach_encode(msg + 8, (int)sizeof msg - 8,
            WL_ID_POOL_BASE, NK_W, NK_H) != WL_ATTACH_SZ)
        return 1;
    if (wl_client_emit_file(nk_client_box, nk_client_seq++, msg, 20)
        != WL_ERR_OK)
        return 1;
    if (wl_hdr_encode(msg, sizeof msg, WL_ID_SURFACE_BASE,
            WL_OP_SURFACE_COMMIT, 8, &h) != WL_ERR_OK)
        return 1;
    if (wl_client_emit_file(nk_client_box, nk_client_seq++, msg, 8)
        != WL_ERR_OK)
        return 1;
    return 0;
}

long nk_sys_nk_frame(int *origin) {
    long ret;
    if (nk_client_probe()) {
        unsigned h = 0;
        if (origin) { origin[0] = 0; origin[1] = 0; }
        nk_client_frame++;
        h = nk_client_hash((unsigned char *)NK_BACKBUF,
            (unsigned)NK_W * (unsigned)NK_H);
        if (h != nk_client_last_hash || (nk_client_frame & 31) == 0) {
            nk_client_last_hash = h;
            nk_client_publish();
        }
        return 0;
    }
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_GFX_PRESENT), "D"((long)MINIOS_GFX_BUF_NK), "S"(origin) : "rcx","r11","memory");
    if (ret == 0) nk_mirror_tick();
    return ret;
}

/* Best-effort mailbox mirror (ADR-0026): when /shm/wl/mirror exists,
 * every 8th present also publishes this window to the wlcomp server
 * (raw pixels plus a six-message session under the program's own box
 * name), so static selftests and scripted runs tile real app frames
 * with zero code changes in the apps. Mirror errors never fail the
 * present; the flag is probed once, so create it before app start. */
static int nk_mirror_on = -1;
static unsigned nk_mirror_tick_n = 0;

static void nk_mirror_box(char *dst, int cap) {
    const char *src = program_invocation_short_name;
    int i = 0;
    int o = 0;
    if (!dst || cap <= 0) return;
    if (!src) src = "nkapp";
    while (src[i] != '\0' && o + 1 < cap && o < 16) {
        char ch = src[i];
        if (ch >= 'A' && ch <= 'Z') ch = (char)(ch + ('a' - 'A'));
        if ((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9'))
            dst[o++] = ch;
        i++;
        if (i > 64) break;
    }
    if (o == 0 && cap > 6) {
        dst[0] = 'n'; dst[1] = 'k'; dst[2] = 'a';
        dst[3] = 'p'; dst[4] = 'p'; o = 5;
    }
    dst[o] = '\0';
}

static int nk_mirror_emit(const char *box, unsigned seq,
        const unsigned char *msg, int mlen) {
    char path[WL_MBOX_NAME_MAX];
    unsigned char frame[WL_MAX_MSG + WL_MBOX_FRAME_HEAD];
    FILE *f = 0;
    int n = 0;
    if (!box || !msg || mlen <= 0) return 1;
    n = wl_mbox_frame_encode(frame, sizeof frame, seq, msg, mlen);
    if (n <= 0) return 1;
    if (wl_mbox_name(path, sizeof path, box, seq) <= 0) return 1;
    f = fopen(path, "wb");
    if (!f) return 1;
    n = fwrite(frame, 1, (unsigned)n, f) == (unsigned)n ? 0 : 1;
    if (fclose(f) != 0) n = 1;
    return n;
}

static void nk_mirror_tick(void) {
    char box[WL_MBOX_BOX_MAX];
    char path[WL_MBOX_NAME_MAX];
    unsigned char msg[WL_MAX_MSG];
    wl_hdr_t h;
    FILE *f = 0;
    unsigned char *raw = 0;
    unsigned seq = 1;
    if (nk_mirror_on < 0) {
        f = fopen(WL_MBOX_DIR "/mirror", "rb");
        nk_mirror_on = (f != 0) ? 1 : 0;
        if (f) fclose(f);
    }
    if (!nk_mirror_on) return;
    if ((nk_mirror_tick_n++ % 8) != 0) return;
    nk_mirror_box(box, sizeof box);
    if (wl_mbox_box_ok(box) != WL_ERR_OK) return;
    raw = (unsigned char *)NK_BACKBUF;
    if (wl_mbox_raw_name(path, sizeof path, box) <= 0) return;
    f = fopen(path, "wb");
    if (!f) return;
    if (fwrite(raw, 1, (unsigned)NK_W * (unsigned)NK_H, f)
        != (unsigned)NK_W * (unsigned)NK_H) {
        fclose(f);
        return;
    }
    if (fclose(f) != 0) return;
    if (wl_hdr_encode(msg, sizeof msg, WL_ID_DISPLAY,
            WL_OP_DISPLAY_GET_REGISTRY, 8, &h) != WL_ERR_OK)
        return;
    if (nk_mirror_emit(box, seq++, msg, 8) != 0) return;
    if (wl_hdr_encode(msg, sizeof msg, WL_ID_REGISTRY, WL_OP_REGISTRY_BIND,
            12, &h) != WL_ERR_OK)
        return;
    if (wl_u32_encode(msg, sizeof msg, 8, WL_ID_COMPOSITOR) != WL_ERR_OK)
        return;
    if (nk_mirror_emit(box, seq++, msg, 12) != 0) return;
    if (wl_hdr_encode(msg, sizeof msg, WL_ID_COMPOSITOR,
            WL_OP_COMPOSITOR_CREATE_SURFACE, 8, &h) != WL_ERR_OK)
        return;
    if (nk_mirror_emit(box, seq++, msg, 8) != 0) return;
    if (wl_hdr_encode(msg, sizeof msg, WL_ID_SHM, WL_OP_SHM_CREATE_POOL,
            8, &h) != WL_ERR_OK)
        return;
    if (nk_mirror_emit(box, seq++, msg, 8) != 0) return;
    if (wl_hdr_encode(msg, sizeof msg, WL_ID_SURFACE_BASE,
            WL_OP_SURFACE_ATTACH, 20, &h) != WL_ERR_OK)
        return;
    if (wl_attach_encode(msg + 8, (int)sizeof msg - 8, WL_ID_POOL_BASE,
            NK_W, NK_H) != WL_ATTACH_SZ)
        return;
    if (nk_mirror_emit(box, seq++, msg, 20) != 0) return;
    if (wl_hdr_encode(msg, sizeof msg, WL_ID_SURFACE_BASE,
            WL_OP_SURFACE_COMMIT, 8, &h) != WL_ERR_OK)
        return;
    nk_mirror_emit(box, seq++, msg, 8);
}
long nk_sys_gfx_set_title(const char *t) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_GFX_SET_TITLE), "D"(t) : "rcx","r11","memory");
    return ret;
}

/* ---- Hybrid palette ---- */
/* The desktop-exact hybrid palette lives once in progs/nk_palette.h;
 * this wrapper keeps the platform signature while sharing the table. */
void nk_build_palette(unsigned char *pal768) {
    if (nk_palette_build(pal768, NK_PAL_BYTES) != NK_PAL_ERR_OK)
        return;
}

/* ---- Color mapping ---- */
static int pal_r[241], pal_g[241], pal_b[241];
static int pal_ready;

static void pal_prepare(void) {
    unsigned char pal768[768];
    nk_build_palette(pal768);
    for (int i = 0; i < 241; i++) {
        pal_r[i] = pal768[(i+15)*3+0];
        pal_g[i] = pal768[(i+15)*3+1];
        pal_b[i] = pal768[(i+15)*3+2];
    }
    pal_ready = 1;
}

static int col_to_idx(struct nk_color c) {
    if (!pal_ready) pal_prepare();
    int best = 0;
    int bestd = 1 << 30;
    for (int i = 0; i < 241; i++) {
        int dr = pal_r[i] - c.r;
        int dg = pal_g[i] - c.g;
        int db = pal_b[i] - c.b;
        int d = dr*dr + dg*dg + db*db;
        if (d < bestd) { bestd = d; best = i; }
    }
    return best + 15;
}

/* ---- Software rasterizer ---- */
static volatile uint8_t *fb = NK_BACKBUF;
static int clip_x, clip_y, clip_w, clip_h;

static void set_clip(int x, int y, int w, int h) {
    if (x < 0) { w += x; x = 0; }
    if (y < 0) { h += y; y = 0; }
    if (x + w > NK_W) w = NK_W - x;
    if (y + h > NK_H) h = NK_H - y;
    clip_x = x; clip_y = y; clip_w = w; clip_h = h;
    if (clip_w < 0) clip_w = 0;
    if (clip_h < 0) clip_h = 0;
}

static void px(int x, int y, int c) {
    if (x < clip_x || x >= clip_x + clip_w) return;
    if (y < clip_y || y >= clip_y + clip_h) return;
    if (x < 0 || x >= NK_W || y < 0 || y >= NK_H) return;
    fb[y * NK_W + x] = (uint8_t)c;
}

static void fill_rect(int x, int y, int w, int h, int c) {
    if (w <= 0 || h <= 0) return;
    for (int yy = y; yy < y + h; yy++)
        for (int xx = x; xx < x + w; xx++)
            px(xx, yy, c);
}

static void draw_line(int x0, int y0, int x1, int y1, int th, int c) {
    int dx = x1 > x0 ? x1 - x0 : x0 - x1;
    int dy = y1 > y0 ? y1 - y0 : y0 - y1;
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;
    int r = th / 2;
    for (;;) {
        for (int ox = -r; ox <= r; ox++)
            for (int oy = -r; oy <= r; oy++)
                px(x0 + ox, y0 + oy, c);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx)  { err += dx; y0 += sy; }
    }
}

static void fill_circle(int cx, int cy, int r, int c) {
    for (int y = -r; y <= r; y++)
        for (int x = -r; x <= r; x++)
            if (x*x + y*y <= r*r) px(cx + x, cy + y, c);
}

static void stroke_circle(int cx, int cy, int r, int th, int c) {
    int x = r, y = 0, err = 0;
    while (x >= y) {
        draw_line(cx - x, cy - y, cx - x, cy - y, th, c);
        draw_line(cx + x, cy - y, cx - x, cy - y, th, c);
        draw_line(cx - x, cy + y, cx - x, cy - y, th, c);
        draw_line(cx + x, cy + y, cx - x, cy - y, th, c);
        draw_line(cx - y, cy - x, cx - x, cy - y, th, c);
        draw_line(cx + y, cy - x, cx - x, cy - y, th, c);
        draw_line(cx - y, cy + x, cx - x, cy - y, th, c);
        draw_line(cx + y, cy + x, cx - x, cy - y, th, c);
        y++;
        if (err <= 0) { err += 2*y + 1; }
        if (err > 0)  { x--; err -= 2*x + 1; }
    }
}

/* Fill a convex polygon (x[], y[]). */
static void fill_poly(int *xs, int *ys, int n, int c) {
    if (n < 3) return;
    int miny = ys[0], maxy = ys[0];
    for (int i = 1; i < n; i++) {
        if (ys[i] < miny) miny = ys[i];
        if (ys[i] > maxy) maxy = ys[i];
    }
    for (int y = miny; y <= maxy; y++) {
        int hits[16], nh = 0;
        for (int i = 0; i < n && nh < 16; i++) {
            int j = (i + 1) % n;
            int yi = ys[i], yj = ys[j];
            if ((yi <= y && yj > y) || (yj <= y && yi > y)) {
                hits[nh++] = xs[i] + (int)((long)(y - yi) * (xs[j] - xs[i]) /
                                           (long)(yj - yi));
            }
        }
        for (int k = 0; k < nh; k += 2)
            for (int x = hits[k]; x <= hits[k+1] && x < clip_x + clip_w; x++)
                px(x, y, c);
    }
}

static void stroke_poly(int *xs, int *ys, int n, int th, int c) {
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        draw_line(xs[i], ys[i], xs[j], ys[j], th, c);
    }
}

static void draw_text(int x, int y, const char *s, int len, int fg, int bg) {
    for (int k = 0; k < len; k++) {
        unsigned char ch = (unsigned char)s[k];
        if (ch < 32 || ch > 127) ch = '?';
        const uint8_t *glyph = nk_font8x8[ch - 32];
        for (int j = 0; j < 8; j++) {
            uint8_t bits = glyph[j];
            for (int i = 0; i < 8; i++)
                if (bits & (0x80 >> i)) px(x + k*8 + i, y + j, fg);
                else if (bg >= 0) px(x + k*8 + i, y + j, bg);
        }
    }
}

static void draw_arc(int cx, int cy, int r, float a0, float a1,
                     int filled, int th, int c) {
    int ptsx[40], ptsy[40], n = 0;
    int segs = 32;
    for (int i = 0; i <= segs; i++) {
        float t = a0 + (a1 - a0) * (float)i / (float)segs;
        ptsx[n] = cx + (int)(r * cosf(t));
        ptsy[n] = cy + (int)(r * sinf(t));
        n++;
    }
    if (filled) {
        int allx[42], ally[42];
        allx[0] = cx; ally[0] = cy;
        for (int i = 0; i < n; i++) { allx[i+1] = ptsx[i]; ally[i+1] = ptsy[i]; }
        fill_poly(allx, ally, n + 1, c);
    } else {
        for (int i = 0; i < n - 1; i++)
            draw_line(ptsx[i], ptsy[i], ptsx[i+1], ptsy[i+1], th, c);
    }
}

void nk_rasterize(struct nk_context *ctx) {
    if (!ctx) return;
    const struct nk_command *cmd;
    set_clip(0, 0, NK_W, NK_H);
    nk_foreach(cmd, ctx) {
        switch (cmd->type) {
        case NK_COMMAND_NOP: break;
        case NK_COMMAND_SCISSOR: {
            const struct nk_command_scissor *c =
                (const struct nk_command_scissor *)cmd;
            set_clip(c->x, c->y, c->w, c->h);
            break;
        }
        case NK_COMMAND_LINE: {
            const struct nk_command_line *c = (const struct nk_command_line *)cmd;
            draw_line(c->begin.x, c->begin.y, c->end.x, c->end.y,
                      c->line_thickness, col_to_idx(c->color));
            break;
        }
        case NK_COMMAND_CURVE: {
            const struct nk_command_curve *c = (const struct nk_command_curve *)cmd;
            int ptsx[32], ptsy[32];
            for (int i = 0; i < 32; i++) {
                float t = (float)i / 31.0f;
                float mt = 1.0f - t;
                float x = mt*mt*mt*c->begin.x + 3*mt*mt*t*c->ctrl[0].x +
                          3*mt*t*t*c->ctrl[1].x + t*t*t*c->end.x;
                float y = mt*mt*mt*c->begin.y + 3*mt*mt*t*c->ctrl[0].y +
                          3*mt*t*t*c->ctrl[1].y + t*t*t*c->end.y;
                ptsx[i] = (int)x; ptsy[i] = (int)y;
            }
            for (int i = 0; i < 31; i++)
                draw_line(ptsx[i], ptsy[i], ptsx[i+1], ptsy[i+1],
                          c->line_thickness, col_to_idx(c->color));
            break;
        }
        case NK_COMMAND_RECT: {
            const struct nk_command_rect *c = (const struct nk_command_rect *)cmd;
            int cidx = col_to_idx(c->color);
            int th = c->line_thickness ? c->line_thickness : 1;
            fill_rect(c->x, c->y, c->w, th, cidx);
            fill_rect(c->x, c->y + c->h - th, c->w, th, cidx);
            fill_rect(c->x, c->y, th, c->h, cidx);
            fill_rect(c->x + c->w - th, c->y, th, c->h, cidx);
            break;
        }
        case NK_COMMAND_RECT_FILLED: {
            const struct nk_command_rect_filled *c =
                (const struct nk_command_rect_filled *)cmd;
            fill_rect(c->x, c->y, c->w, c->h, col_to_idx(c->color));
            break;
        }
        case NK_COMMAND_RECT_MULTI_COLOR: {
            const struct nk_command_rect_multi_color *c =
                (const struct nk_command_rect_multi_color *)cmd;
            struct nk_color avg;
            avg.r = (c->left.r + c->top.r + c->right.r + c->bottom.r) / 4;
            avg.g = (c->left.g + c->top.g + c->right.g + c->bottom.g) / 4;
            avg.b = (c->left.b + c->top.b + c->right.b + c->bottom.b) / 4;
            fill_rect(c->x, c->y, c->w, c->h, col_to_idx(avg));
            break;
        }
        case NK_COMMAND_CIRCLE: {
            const struct nk_command_circle *c = (const struct nk_command_circle *)cmd;
            int r = (c->w < c->h ? c->w : c->h) / 2;
            stroke_circle(c->x + c->w/2, c->y + c->h/2, r,
                          c->line_thickness, col_to_idx(c->color));
            break;
        }
        case NK_COMMAND_CIRCLE_FILLED: {
            const struct nk_command_circle_filled *c =
                (const struct nk_command_circle_filled *)cmd;
            int r = (c->w < c->h ? c->w : c->h) / 2;
            fill_circle(c->x + c->w/2, c->y + c->h/2, r, col_to_idx(c->color));
            break;
        }
        case NK_COMMAND_ARC: {
            const struct nk_command_arc *c = (const struct nk_command_arc *)cmd;
            draw_arc(c->cx, c->cy, c->r, c->a[0], c->a[1], 0,
                     c->line_thickness, col_to_idx(c->color));
            break;
        }
        case NK_COMMAND_ARC_FILLED: {
            const struct nk_command_arc_filled *c =
                (const struct nk_command_arc_filled *)cmd;
            draw_arc(c->cx, c->cy, c->r, c->a[0], c->a[1], 1,
                     0, col_to_idx(c->color));
            break;
        }
        case NK_COMMAND_TRIANGLE: {
            const struct nk_command_triangle *c =
                (const struct nk_command_triangle *)cmd;
            int xs[3] = {c->a.x, c->b.x, c->c.x};
            int ys[3] = {c->a.y, c->b.y, c->c.y};
            stroke_poly(xs, ys, 3, c->line_thickness, col_to_idx(c->color));
            break;
        }
        case NK_COMMAND_TRIANGLE_FILLED: {
            const struct nk_command_triangle_filled *c =
                (const struct nk_command_triangle_filled *)cmd;
            int xs[3] = {c->a.x, c->b.x, c->c.x};
            int ys[3] = {c->a.y, c->b.y, c->c.y};
            fill_poly(xs, ys, 3, col_to_idx(c->color));
            break;
        }
        case NK_COMMAND_POLYGON: {
            const struct nk_command_polygon *c = (const struct nk_command_polygon *)cmd;
            int xs[32], ys[32];
            int n = c->point_count < 32 ? c->point_count : 32;
            for (int i = 0; i < n; i++) { xs[i] = c->points[i].x; ys[i] = c->points[i].y; }
            stroke_poly(xs, ys, n, c->line_thickness, col_to_idx(c->color));
            break;
        }
        case NK_COMMAND_POLYGON_FILLED: {
            const struct nk_command_polygon_filled *c =
                (const struct nk_command_polygon_filled *)cmd;
            int xs[32], ys[32];
            int n = c->point_count < 32 ? c->point_count : 32;
            for (int i = 0; i < n; i++) { xs[i] = c->points[i].x; ys[i] = c->points[i].y; }
            fill_poly(xs, ys, n, col_to_idx(c->color));
            break;
        }
        case NK_COMMAND_POLYLINE: {
            const struct nk_command_polyline *c = (const struct nk_command_polyline *)cmd;
            int xs[32], ys[32];
            int n = c->point_count < 32 ? c->point_count : 32;
            for (int i = 0; i < n; i++) { xs[i] = c->points[i].x; ys[i] = c->points[i].y; }
            for (int i = 0; i < n - 1; i++)
                draw_line(xs[i], ys[i], xs[i+1], ys[i+1],
                          c->line_thickness, col_to_idx(c->color));
            break;
        }
        case NK_COMMAND_TEXT: {
            const struct nk_command_text *c = (const struct nk_command_text *)cmd;
            int fg = col_to_idx(c->foreground);
            int bg = -1;
            if (c->background.a > 0) bg = col_to_idx(c->background);
            draw_text(c->x, c->y, c->string, c->length, fg, bg);
            break;
        }
        case NK_COMMAND_IMAGE:
        case NK_COMMAND_CUSTOM:
            break;
        default:
            break;
        }
    }
}

/* ---- Font (8x8 monospace) ---- */
static float nk_minios_font_width(nk_handle handle, float height,
                                  const char *text, int len) {
    (void)handle; (void)height; (void)text;
    return (float)(len * 8);
}

struct nk_user_font nk_minios_font(void) {
    struct nk_user_font f;
    f.userdata = nk_handle_id(0);
    f.height = 8.0f;
    f.width = nk_minios_font_width;
    return f;
}

/* ---- Input ---- */
/* PS/2 set 1 scancode -> Nuklear key/char translation (raw mode). */

static int kbd_shift, kbd_ctrl, kbd_alt;
static int pending_e0;
static int nk_quit_req;
static int nk_win_origin_x, nk_win_origin_y;

static const char kbd_us[128] = {
    0,   27,  '1','2','3','4','5','6','7','8','9','0','-','=','\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0,   'a','s','d','f','g','h','j','k','l',';','\'','`',
    0,   '\\','z','x','c','v','b','n','m',',','.','/', 0,
    '*', 0,   ' ', 0,
    0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, '-',0,0,0,0,
    '+', 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
static const char kbd_us_shift[128] = {
    0,   27,  '!','@','#','$','%','^','&','*','(',')','_','+','\b',
    '\t','Q','W','E','R','T','Y','U','I','O','P','{','}','\n',
    0,   'A','S','D','F','G','H','J','K','L',':','"','~',
    0,   '|','Z','X','C','V','B','N','M','<','>','?', 0,
    '*', 0,   ' ', 0,
    0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, '-',0,0,0,0,
    '+', 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

static void feed_key(struct nk_context *ctx, enum nk_keys key, int down) {
    nk_input_key(ctx, key, down ? nk_true : nk_false);
}

static nk_scancode_cb sc_hook;
static void *sc_hook_ud;

void nk_set_scancode_hook(nk_scancode_cb cb, void *ud) {
    sc_hook = cb;
    sc_hook_ud = ud;
}

static void handle_scancode(struct nk_context *ctx, unsigned char sc) {
    if (sc == 0xE0) { pending_e0 = 1; return; }
    int make = !(sc & 0x80);
    unsigned char code = sc & 0x7F;
    int e0 = pending_e0 ? 1 : 0;
    if (sc_hook) sc_hook((int)code, make, e0, sc_hook_ud);

    if (pending_e0) {
        pending_e0 = 0;
        if (code == 0x1D) { feed_key(ctx, NK_KEY_CTRL, make); kbd_ctrl = make; return; }
        if (code == 0x38) { feed_key(ctx, NK_KEY_ALT, make); kbd_alt = make; return; }
        if (code == 0x48) { feed_key(ctx, NK_KEY_UP, make); return; }
        if (code == 0x50) { feed_key(ctx, NK_KEY_DOWN, make); return; }
        if (code == 0x4B) { feed_key(ctx, NK_KEY_LEFT, make); return; }
        if (code == 0x4D) { feed_key(ctx, NK_KEY_RIGHT, make); return; }
        if (code == 0x47) { feed_key(ctx, NK_KEY_TEXT_LINE_START, make); return; }
        if (code == 0x4F) { feed_key(ctx, NK_KEY_TEXT_LINE_END, make); return; }
        if (code == 0x49) { feed_key(ctx, NK_KEY_SCROLL_UP, make); return; }
        if (code == 0x51) { feed_key(ctx, NK_KEY_SCROLL_DOWN, make); return; }
        if (code == 0x53) { feed_key(ctx, NK_KEY_DEL, make); return; }
        return;
    }

    switch (code) {
    case 0x2A: case 0x36: feed_key(ctx, NK_KEY_SHIFT, make); kbd_shift = make; return;
    case 0x1D: feed_key(ctx, NK_KEY_CTRL, make); kbd_ctrl = make; return;
    case 0x38: feed_key(ctx, NK_KEY_ALT, make); kbd_alt = make; return;
    case 0x1C: feed_key(ctx, NK_KEY_ENTER, make); return;
    case 0x0E: feed_key(ctx, NK_KEY_BACKSPACE, make); return;
    case 0x0F: feed_key(ctx, NK_KEY_TAB, make); return;
    case 0x39: if (make) nk_input_unicode(ctx, ' '); return;
    case 0x01: if (make) nk_quit_req = 1; return;
    case 0x3E: if (make && kbd_alt) nk_quit_req = 1; return;
    default: break;
    }

    /* Printable ASCII translation on the make edge only. */
    if (make && code < 128) {
        char ch = kbd_shift ? kbd_us_shift[code] : kbd_us[code];
        if (ch >= 32 && ch <= 126) {
            nk_input_unicode(ctx, (nk_rune)ch);
        }
    }
}

/* Client input pump: feed the pending .ev batch when its seq
 * advanced, else hold the last state. Never touches PS/2; the
 * server owns the port while the desktop runs. */
static void nk_client_poll(struct nk_context *ctx) {
    char evp[WL_MBOX_NAME_MAX];
    unsigned char raw[WL_EV_SZ];
    wl_ev_t e;
    FILE *f = 0;
    size_t n = 0;
    unsigned i = 0;
    int dw = 0;
    if (!ctx) return;
    if (wl_mbox_ev_name(evp, sizeof evp, nk_client_box) <= 0) return;
    f = fopen(evp, "rb");
    if (!f) return;
    n = fread(raw, 1, sizeof raw, f);
    fclose(f);
    if (n != sizeof raw) return;
    if (wl_ev_decode(raw, (int)n, &e) != WL_ERR_OK) return;
    if (e.seq == nk_client_ev_seq) return;
    nk_client_ev_seq = e.seq;
    for (i = 0; i < e.nsc; i++)
        handle_scancode(ctx, e.sc[i]);
    if (e.mx >= 0 && e.my >= 0)
        nk_input_motion(ctx, e.mx, e.my);
    {
        int b = (int)(e.buttons & 7u);
        int now = e.mx >= 0 ? e.mx : 0;
        int noy = e.my >= 0 ? e.my : 0;
        if ((b & 1) != (nk_client_ev_btn & 1))
            nk_input_button(ctx, NK_BUTTON_LEFT, now, noy,
                    (b & 1) ? nk_true : nk_false);
        if ((b & 2) != (nk_client_ev_btn & 2))
            nk_input_button(ctx, NK_BUTTON_RIGHT, now, noy,
                    (b & 2) ? nk_true : nk_false);
        if ((b & 4) != (nk_client_ev_btn & 4))
            nk_input_button(ctx, NK_BUTTON_MIDDLE, now, noy,
                    (b & 4) ? nk_true : nk_false);
        nk_client_ev_btn = b;
    }
    dw = (int)(e.wheel - nk_client_ev_wheel);
    nk_client_ev_wheel = e.wheel;
    if (dw != 0) {
        struct nk_vec2 scroll;
        scroll.x = 0;
        scroll.y = (float)dw;
        nk_input_scroll(ctx, scroll);
    }
}

void nk_poll_input(struct nk_context *ctx) {
    int mouse[4];
    static int prev_buttons;

    if (nk_client_probe()) { nk_client_poll(ctx); return; }

    /* Keyboard. */
    for (;;) {
        long sc = nk_sys_kbd();
        if (sc < 0) break;
        handle_scancode(ctx, (unsigned char)sc);
    }

    /* Mouse: translate desktop coordinates into the UI window's local
     * coordinates (the window content origin is reported by GFX_PRESENT). */
    if (nk_sys_mouse(mouse) == 0) {
        int lx = mouse[0] - nk_win_origin_x;
        int ly = mouse[1] - nk_win_origin_y;
        nk_input_motion(ctx, lx, ly);
        int b = mouse[2];
        if ((b & 1) != (prev_buttons & 1))
            nk_input_button(ctx, NK_BUTTON_LEFT, lx, ly,
                            (b & 1) ? nk_true : nk_false);
        if ((b & 2) != (prev_buttons & 2))
            nk_input_button(ctx, NK_BUTTON_RIGHT, lx, ly,
                            (b & 2) ? nk_true : nk_false);
        if ((b & 4) != (prev_buttons & 4))
            nk_input_button(ctx, NK_BUTTON_MIDDLE, lx, ly,
                            (b & 4) ? nk_true : nk_false);
        prev_buttons = b;
        if (mouse[3]) {
            struct nk_vec2 scroll;
            scroll.x = 0;
            scroll.y = (float)mouse[3];
            nk_input_scroll(ctx, scroll);
        }
    }
}

void nk_set_window_origin(int x, int y) {
    nk_win_origin_x = x;
    nk_win_origin_y = y;
}

/** WM quit gesture latch: ESC or Alt+F4 pressed since the last poll.
 * Returns 1 once per gesture, then clears. Every NK app polls this per
 * frame so no window depends on the tiny title-bar X to close. */
int nk_quit_requested(void) {
    int r = nk_quit_req;
    nk_quit_req = 0;
    return r;
}