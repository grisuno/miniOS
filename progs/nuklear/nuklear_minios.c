/* nuklear_minios.c — MiniOS platform layer for Nuklear.
 *
 * Software rasterizer for an 8-bit indexed back-buffer: Nuklear emits an
 * abstract draw command list (nk__begin/nk__next); this layer rasterizes
 * every command into the palette-indexed back-buffer at NK_BACKBUF_ADDR with
 * scissor clipping, then the app calls SYS_NK_FRAME to composite the buffer
 * as a titled desktop window. Colors are mapped to the hybrid palette
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

/* ---- MiniOS syscalls (Linux ABI numbers are MiniOS custom) ---- */
long nk_sys_time_ms(void) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(204), "D"(0) : "rcx","r11","memory");
    return ret;
}
long nk_sys_kbd(void) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(205), "D"(0) : "rcx","r11","memory");
    return ret;
}
long nk_sys_palette(const unsigned char *pal) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(206), "D"(pal) : "rcx","r11","memory");
    return ret;
}
long nk_sys_kbd_raw(int on) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(207), "D"((long)on) : "rcx","r11","memory");
    return ret;
}
long nk_sys_vga_mode(int on) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(208), "D"((long)on) : "rcx","r11","memory");
    return ret;
}
long nk_sys_fb_info(int *w, int *h, int *pitch) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret)
                     : "a"(213), "D"(w), "S"(h), "d"(pitch)
                     : "rcx","r11","memory");
    return ret;
}
long nk_sys_mouse(int *xybw) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(219), "D"(xybw) : "rcx","r11","memory");
    return ret;
}
long nk_sys_mouse_badptr(void) {
    /* A kernel address (0x100000) is far outside the user window; the kernel
     * user_range_ok check must reject it with -EFAULT. */
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(219), "D"(0x100000L)
                     : "rcx","r11","memory");
    return ret;
}
long nk_sys_nk_frame(int *origin) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(220), "D"(origin) : "rcx","r11","memory");
    return ret;
}

/* ---- Hybrid palette ---- */
/* Indices 0-14 must exactly match vga_fb.c's desktop palette so the desktop
 * behind the window is never recolored while the app runs. */
static const unsigned char desktop_pal[15][3] = {
    {  0,  0,  0},   /*  0 black          */
    { 15, 15, 50},   /*  1 bg dark navy   */
    {100,100,110},   /*  2 taskbar        */
    {255,255,255},   /*  3 taskbar text   */
    { 60, 90,140},   /*  4 title bar      */
    {255,255,255},   /*  5 title text     */
    { 15, 15, 15},   /*  6 terminal bg    */
    {  0,220,  0},   /*  7 terminal text  */
    {  0,160,  0},   /*  8 cursor         */
    {180,180,190},   /*  9 border         */
    {255,255,255},   /* 10 white          */
    { 30, 30, 40},   /* 11 shadow         */
    {100,140,220},   /* 12 highlight      */
    { 60, 60, 70},   /* 13 scrollbar bg   */
    {140,140,155},   /* 14 scrollbar thumb */
};

/* UI ramp: a 6x6x6 RGB cube (indices 15..230) plus grays and saturated
 * accents (231..255), giving the nearest-neighbour mapper good coverage. */
void nk_build_palette(unsigned char *pal768) {
    int i;
    for (i = 0; i < 15; i++) {
        pal768[i*3+0] = desktop_pal[i][0];
        pal768[i*3+1] = desktop_pal[i][1];
        pal768[i*3+2] = desktop_pal[i][2];
    }
    int idx = 15;
    int r, g, b;
    for (r = 0; r < 6; r++)
        for (g = 0; g < 6; g++)
            for (b = 0; b < 6; b++) {
                pal768[idx*3+0] = (unsigned char)(r * 51);
                pal768[idx*3+1] = (unsigned char)(g * 51);
                pal768[idx*3+2] = (unsigned char)(b * 51);
                idx++;
            }
    static const int grays[11] = {0,25,51,76,102,127,153,178,204,229,255};
    for (i = 0; i < 11; i++) {
        pal768[idx*3+0] = (unsigned char)grays[i];
        pal768[idx*3+1] = (unsigned char)grays[i];
        pal768[idx*3+2] = (unsigned char)grays[i];
        idx++;
    }
    static const unsigned char accents[14][3] = {
        {255,  0,  0}, {  0,255,  0}, {  0,  0,255}, {255,255,  0},
        {  0,255,255}, {255,  0,255}, {255,128,  0}, {128,  0,255},
        {255,  0,128}, {  0,128,255}, {128,255,  0}, {255,128,128},
        {128,255,128}, {128,128,255},
    };
    for (i = 0; i < 14; i++) {
        pal768[idx*3+0] = accents[i][0];
        pal768[idx*3+1] = accents[i][1];
        pal768[idx*3+2] = accents[i][2];
        idx++;
    }
    /* The ramp must fill exactly 15..255. */
    (void)idx;
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

/* ---- 8x8 bitmap font (public-domain font8x8, ASCII 32..127) ---- */
const uint8_t nk_font8x8[96][8] = {
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    {0x18,0x18,0x18,0x18,0x18,0x00,0x18,0x00},
    {0x6C,0x6C,0x00,0x00,0x00,0x00,0x00,0x00},
    {0x6C,0x6C,0xFE,0x6C,0xFE,0x6C,0x6C,0x00},
    {0x18,0x3E,0x60,0x3C,0x06,0x7C,0x18,0x00},
    {0xC2,0xC6,0x0C,0x18,0x30,0x66,0xC6,0x00},
    {0x38,0x6C,0x38,0x76,0xDC,0xCC,0x76,0x00},
    {0x18,0x18,0x30,0x00,0x00,0x00,0x00,0x00},
    {0x0C,0x18,0x30,0x30,0x30,0x18,0x0C,0x00},
    {0x30,0x18,0x0C,0x0C,0x0C,0x18,0x30,0x00},
    {0x00,0x66,0x3C,0xFF,0x3C,0x66,0x00,0x00},
    {0x00,0x18,0x18,0x7E,0x18,0x18,0x00,0x00},
    {0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x30},
    {0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00},
    {0x02,0x06,0x0C,0x18,0x30,0x60,0x40,0x00},
    {0x7C,0xC6,0xCE,0xDE,0xF6,0xE6,0x7C,0x00},
    {0x18,0x38,0x78,0x18,0x18,0x18,0x7E,0x00},
    {0x7C,0xC6,0x06,0x1C,0x30,0x66,0xFE,0x00},
    {0x7C,0xC6,0x06,0x3C,0x06,0xC6,0x7C,0x00},
    {0x1C,0x3C,0x6C,0xCC,0xFE,0x0C,0x1E,0x00},
    {0xFE,0xC0,0xFC,0x06,0x06,0xC6,0x7C,0x00},
    {0x38,0x60,0xC0,0xFC,0xC6,0xC6,0x7C,0x00},
    {0xFE,0xC6,0x0C,0x18,0x30,0x30,0x30,0x00},
    {0x7C,0xC6,0xC6,0x7C,0xC6,0xC6,0x7C,0x00},
    {0x7C,0xC6,0xC6,0x7E,0x06,0x0C,0x78,0x00},
    {0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x00},
    {0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x30},
    {0x0C,0x18,0x30,0x60,0x30,0x18,0x0C,0x00},
    {0x00,0x00,0x7E,0x00,0x7E,0x00,0x00,0x00},
    {0x60,0x30,0x18,0x0C,0x18,0x30,0x60,0x00},
    {0x7C,0xC6,0x0C,0x18,0x18,0x00,0x18,0x00},
    {0x7C,0xC6,0xDE,0xDE,0xDE,0xC0,0x78,0x00},
    {0x38,0x6C,0xC6,0xC6,0xFE,0xC6,0xC6,0x00},
    {0xFC,0x66,0x66,0x7C,0x66,0x66,0xFC,0x00},
    {0x3C,0x66,0xC0,0xC0,0xC0,0x66,0x3C,0x00},
    {0xF8,0x6C,0x66,0x66,0x66,0x6C,0xF8,0x00},
    {0xFE,0x62,0x68,0x78,0x68,0x62,0xFE,0x00},
    {0xFE,0x62,0x68,0x78,0x68,0x60,0xF0,0x00},
    {0x3C,0x66,0xC0,0xC0,0xC6,0x66,0x3E,0x00},
    {0xC6,0xC6,0xC6,0xFE,0xC6,0xC6,0xC6,0x00},
    {0x3C,0x18,0x18,0x18,0x18,0x18,0x3C,0x00},
    {0x1E,0x0C,0x0C,0x0C,0xCC,0xCC,0x78,0x00},
    {0xE6,0x66,0x6C,0x78,0x6C,0x66,0xE6,0x00},
    {0xF0,0x60,0x60,0x60,0x62,0x66,0xFE,0x00},
    {0xC6,0xEE,0xFE,0xFE,0xD6,0xC6,0xC6,0x00},
    {0xC6,0xE6,0xF6,0xDE,0xCE,0xC6,0xC6,0x00},
    {0x7C,0xC6,0xC6,0xC6,0xC6,0xC6,0x7C,0x00},
    {0xFC,0x66,0x66,0x7C,0x60,0x60,0xF0,0x00},
    {0x7C,0xC6,0xC6,0xC6,0xD6,0xDE,0x7C,0x06},
    {0xFC,0x66,0x66,0x7C,0x6C,0x66,0xE6,0x00},
    {0x7C,0xC6,0xE0,0x7C,0x0E,0xC6,0x7C,0x00},
    {0x7E,0x7E,0x5A,0x18,0x18,0x18,0x3C,0x00},
    {0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x7C,0x00},
    {0xC6,0xC6,0xC6,0xC6,0x6C,0x38,0x10,0x00},
    {0xC6,0xC6,0xC6,0xD6,0xFE,0xEE,0xC6,0x00},
    {0xC6,0xC6,0x6C,0x38,0x6C,0xC6,0xC6,0x00},
    {0x66,0x66,0x66,0x3C,0x18,0x18,0x3C,0x00},
    {0xFE,0xC6,0x8C,0x18,0x32,0x66,0xFE,0x00},
    {0x3C,0x30,0x30,0x30,0x30,0x30,0x3C,0x00},
    {0xC0,0x60,0x30,0x18,0x0C,0x06,0x02,0x00},
    {0x3C,0x0C,0x0C,0x0C,0x0C,0x0C,0x3C,0x00},
    {0x10,0x38,0x6C,0xC6,0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF},
    {0x30,0x18,0x0C,0x00,0x00,0x00,0x00,0x00},
    {0x00,0x00,0x78,0x0C,0x7C,0xCC,0x76,0x00},
    {0xE0,0x60,0x7C,0x66,0x66,0x66,0xDC,0x00},
    {0x00,0x00,0x7C,0xC6,0xC0,0xC6,0x7C,0x00},
    {0x1C,0x0C,0x7C,0xCC,0xCC,0xCC,0x76,0x00},
    {0x00,0x00,0x7C,0xC6,0xFE,0xC0,0x7C,0x00},
    {0x1C,0x36,0x30,0x7C,0x30,0x30,0x78,0x00},
    {0x00,0x00,0x76,0xCC,0xCC,0x7C,0x0C,0x78},
    {0xE0,0x60,0x6C,0x76,0x66,0x66,0xE6,0x00},
    {0x18,0x00,0x38,0x18,0x18,0x18,0x3C,0x00},
    {0x06,0x00,0x06,0x06,0x06,0x66,0x66,0x3C},
    {0xE0,0x60,0x66,0x6C,0x78,0x6C,0xE6,0x00},
    {0x38,0x18,0x18,0x18,0x18,0x18,0x3C,0x00},
    {0x00,0x00,0xEC,0xFE,0xD6,0xD6,0xD6,0x00},
    {0x00,0x00,0xDC,0x66,0x66,0x66,0x66,0x00},
    {0x00,0x00,0x7C,0xC6,0xC6,0xC6,0x7C,0x00},
    {0x00,0x00,0xDC,0x66,0x66,0x7C,0x60,0xF0},
    {0x00,0x00,0x76,0xCC,0xCC,0x7C,0x0C,0x1E},
    {0x00,0x00,0xDC,0x76,0x60,0x60,0xF0,0x00},
    {0x00,0x00,0x7E,0xC0,0x7C,0x06,0xFC,0x00},
    {0x30,0x30,0x7C,0x30,0x30,0x36,0x1C,0x00},
    {0x00,0x00,0xCC,0xCC,0xCC,0xCC,0x76,0x00},
    {0x00,0x00,0xC6,0xC6,0xC6,0x6C,0x38,0x00},
    {0x00,0x00,0xC6,0xD6,0xD6,0xFE,0x6C,0x00},
    {0x00,0x00,0xC6,0x6C,0x38,0x6C,0xC6,0x00},
    {0x00,0x00,0xC6,0xC6,0xCE,0x76,0x06,0xFC},
    {0x00,0x00,0xFC,0x98,0x30,0x64,0xFC,0x00},
    {0x0E,0x18,0x18,0x70,0x18,0x18,0x0E,0x00},
    {0x18,0x18,0x18,0x00,0x18,0x18,0x18,0x00},
    {0x70,0x18,0x18,0x0E,0x18,0x18,0x70,0x00},
    {0x76,0xDC,0x00,0x00,0x00,0x00,0x00,0x00},
    {0x00,0x10,0x38,0x6C,0xC6,0xC6,0xFE,0x00}
};

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

static void handle_scancode(struct nk_context *ctx, unsigned char sc) {
    if (sc == 0xE0) { pending_e0 = 1; return; }
    int make = !(sc & 0x80);
    unsigned char code = sc & 0x7F;

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

void nk_poll_input(struct nk_context *ctx) {
    int mouse[4];
    static int prev_buttons;

    /* Keyboard. */
    for (;;) {
        long sc = nk_sys_kbd();
        if (sc < 0) break;
        handle_scancode(ctx, (unsigned char)sc);
    }

    /* Mouse: translate desktop coordinates into the UI window's local
     * coordinates (the window content origin is reported by SYS_NK_FRAME). */
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