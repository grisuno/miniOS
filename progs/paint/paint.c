/** Docstring: MiniOS paint program (Nuklear ring-3 app, MiniFS: paint/paint.elf).
 *
 * A canvas paint program over the shared Nuklear platform layer
 * (progs/nuklear/nuklear_minios.c): toolbar (brush, line, rect, circle,
 * fill, eraser), a 16-swatch picker drawn from exact hybrid-palette
 * entries, brush sizes 1/2/4, and PNG save/load. The canvas is a
 * palette-index buffer blitted into the NK back-buffer after rasterize
 * (the file-browser preview pattern); its widget bounds from nk_widget
 * are the single source for both the blit offset and mouse hit-testing,
 * so no screen coordinate is hardcoded. PNG output uses a self-contained
 * stored-deflate writer (no third-party encoder dependency); PNG input
 * decodes through stb_image and nearest-maps onto the hybrid palette.
 * Every bound, tool, path, label and limit lives in the config block
 * below; no address or number is hardcoded outside it.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "minios_abi.h"
#include "nuklear.h"
#include "nuklear_minios.h"
#include "nuklear_theme.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#define STBI_NO_STDIO
#include "stb_image.h"

/** Central configuration: every bound, tool, path, label and limit. */
#define PAINT_W 320
#define PAINT_H 200
#define PAINT_N (PAINT_W * PAINT_H)
#define PAINT_PATH_MAX 128
#define PAINT_FILE_MAX (1024 * 1024)
#define PAINT_STATUS_MAX 128
#define PAINT_UI_MEMORY (4 * 1024 * 1024)
#define PAINT_PNG_MAX (PAINT_H * (1 + PAINT_W * 3) + 512)
#define PAINT_PNG_MAX_DIM 512
#define PAINT_TITLE "Paint"
#define PAINT_DEFAULT_PATH "/drawing.png"
#define PAINT_PANEL_TITLE "tools"
#define PAINT_FILE_BTN_W 64
#define PAINT_FRAME_MS 16
#define PAINT_FRAME_ATTEMPTS 3
#define PAINT_NCOLORS 16
#define PAINT_NSIZES 3
#define PAINT_NTOOLS 6

/** Tool ids in toolbar order. */
#define PAINT_TOOL_BRUSH 0
#define PAINT_TOOL_LINE 1
#define PAINT_TOOL_RECT 2
#define PAINT_TOOL_CIRCLE 3
#define PAINT_TOOL_FILL 4
#define PAINT_TOOL_ERASER 5

/** Brush diameters for the size selector. */
static const int paint_sizes[PAINT_NSIZES] = {1, 2, 4};

/** Swatch palette: exact hybrid-palette indices (black, 14 saturated
 * accents, white), so a saved PNG reloads pixel-identical. */
static const unsigned char paint_colors[PAINT_NCOLORS] = {
    231, 242, 243, 244, 245, 246, 247, 248,
    249, 250, 251, 252, 253, 254, 255, 241
};

static const char *paint_tool_names[PAINT_NTOOLS] = {
    "brush", "line", "rect", "circle", "fill", "eraser"
};

static unsigned char paint_px[PAINT_N];
static unsigned char paint_backup[PAINT_N];
static unsigned char paint_png[PAINT_PNG_MAX];
static int paint_tool = PAINT_TOOL_BRUSH;
static int paint_swatch = 2;
static int paint_size = 0;
static int paint_down = 0;
static int paint_lastx;
static int paint_lasty;
static int paint_anchorx;
static int paint_anchory;
static float paint_rectx;
static float paint_recty;
static char paint_path[PAINT_PATH_MAX] = PAINT_DEFAULT_PATH;
static char paint_status[PAINT_STATUS_MAX];
static int paint_quit;
static int paint_autoload;

/** Clamp v into [lo, hi]. */
static int paint_clamp(int v, int lo, int hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

/** Bound-checked pixel plot, fail closed outside the canvas. */
static int paint_plot(unsigned char *buf, int w, int h, int x, int y,
                      unsigned char c) {
    if (!buf || w <= 0 || h <= 0) return -1;
    if (x < 0 || y < 0 || x >= w || y >= h) return -1;
    buf[y * w + x] = c;
    return 0;
}

/** Filled square dab of side s centered on (x, y). */
static void paint_dab(unsigned char *buf, int w, int h, int x, int y,
                      unsigned char c, int s) {
    int half = s / 2;
    int dx;
    int dy;
    for (dy = -half; dy < s - half; dy++)
        for (dx = -half; dx < s - half; dx++)
            paint_plot(buf, w, h, x + dx, y + dy, c);
}

/** Bresenham line with brush dabs, returns plotted points (not dabs). */
static int paint_line(unsigned char *buf, int w, int h, int x0, int y0,
                      int x1, int y1, unsigned char c, int s) {
    int dx = x1 >= x0 ? x1 - x0 : x0 - x1;
    int dy = y1 >= y0 ? y1 - y0 : y0 - y1;
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;
    int n = 0;
    if (!buf || w <= 0 || h <= 0) return -1;
    for (;;) {
        if (x0 >= 0 && y0 >= 0 && x0 < w && y0 < h) {
            paint_dab(buf, w, h, x0, y0, c, s);
            n++;
        }
        if (x0 == x1 && y0 == y1) break;
        {
            int e2 = 2 * err;
            if (e2 > -dy) { err -= dy; x0 += sx; }
            if (e2 < dx) { err += dx; y0 += sy; }
        }
    }
    return n;
}

/** Filled rectangle, corners normalized, returns painted pixels. */
static int paint_rect_fill(unsigned char *buf, int w, int h, int x0, int y0,
                           int x1, int y1, unsigned char c) {
    int xa = x0 < x1 ? x0 : x1;
    int xb = x0 < x1 ? x1 : x0;
    int ya = y0 < y1 ? y0 : y1;
    int yb = y0 < y1 ? y1 : y0;
    int x;
    int y;
    int n = 0;
    if (!buf || w <= 0 || h <= 0) return -1;
    for (y = ya; y <= yb; y++)
        for (x = xa; x <= xb; x++)
            if (paint_plot(buf, w, h, x, y, c) == 0) n++;
    return n;
}

/** Filled midpoint circle of radius r, returns painted pixels. */
static int paint_circle_fill(unsigned char *buf, int w, int h, int cx,
                             int cy, int r, unsigned char c) {
    int x;
    int y;
    int n = 0;
    if (!buf || w <= 0 || h <= 0 || r < 0) return -1;
    for (y = cy - r; y <= cy + r; y++)
        for (x = cx - r; x <= cx + r; x++) {
            int dx = x - cx;
            int dy = y - cy;
            if (dx * dx + dy * dy <= r * r)
                if (paint_plot(buf, w, h, x, y, c) == 0) n++;
        }
    return n;
}

/** Bounded flood fill with mark-on-push: every cell is marked once, so
 * the explicit stack never exceeds the canvas size. */
static int paint_flood(unsigned char *buf, int w, int h, int x, int y,
                       unsigned char nc) {
    static int sx[PAINT_N];
    static int sy[PAINT_N];
    unsigned char oc;
    int top = 0;
    int n;
    if (!buf || w <= 0 || h <= 0) return -1;
    if (x < 0 || y < 0 || x >= w || y >= h) return -1;
    oc = buf[y * w + x];
    if (oc == nc) return 0;
    buf[y * w + x] = nc;
    sx[top] = x;
    sy[top] = y;
    top++;
    n = 1;
    while (top > 0) {
        int cx;
        int cy;
        top--;
        cx = sx[top];
        cy = sy[top];
        if (top + 4 > PAINT_N) return -1;
        if (cx + 1 < w && buf[cy * w + cx + 1] == oc) {
            buf[cy * w + cx + 1] = nc;
            sx[top] = cx + 1; sy[top] = cy; top++; n++;
        }
        if (cx - 1 >= 0 && buf[cy * w + cx - 1] == oc) {
            buf[cy * w + cx - 1] = nc;
            sx[top] = cx - 1; sy[top] = cy; top++; n++;
        }
        if (cy + 1 < h && buf[(cy + 1) * w + cx] == oc) {
            buf[(cy + 1) * w + cx] = nc;
            sx[top] = cx; sy[top] = cy + 1; top++; n++;
        }
        if (cy - 1 >= 0 && buf[(cy - 1) * w + cx] == oc) {
            buf[(cy - 1) * w + cx] = nc;
            sx[top] = cx; sy[top] = cy - 1; top++; n++;
        }
    }
    return n;
}

/** Nearest hybrid-palette index by squared RGB distance. */
static int paint_nearest(const unsigned char *pal, unsigned r, unsigned g,
                         unsigned b) {
    unsigned best = 0;
    unsigned long bd = 0xFFFFFFFFUL;
    unsigned k;
    if (!pal) return -1;
    for (k = 0; k < 256; k++) {
        long dr = (long)pal[k * 3] - (long)r;
        long dg = (long)pal[k * 3 + 1] - (long)g;
        long db = (long)pal[k * 3 + 2] - (long)b;
        unsigned long d = (unsigned long)(dr * dr + dg * dg + db * db);
        if (d < bd) { bd = d; best = k; }
    }
    return (int)best;
}

/** Cached hybrid palette: built once, shared by picker, save and load. */
static const unsigned char *paint_pal(void) {
    static unsigned char pal768[768];
    static int ready = 0;
    if (!ready) {
        nk_build_palette(pal768);
        ready = 1;
    }
    return pal768;
}

/** Save-path gate: printable ASCII, bounded, .png suffix, no traversal. */
static int paint_path_ok(const char *p) {
    unsigned n = 0;
    unsigned k;
    if (!p || !p[0]) return -1;
    while (p[n]) {
        if (p[n] < 32 || p[n] > 126) return -1;
        n++;
        if (n >= PAINT_PATH_MAX) return -1;
    }
    if (n <= 4) return -1;
    if (strcmp(p + n - 4, ".png") != 0) return -1;
    if (p[n - 5] == '/') return -1;
    for (k = 0; k + 1 < n; k++)
        if (p[k] == '.' && p[k + 1] == '.') return -1;
    return 0;
}

/** CRC-32 (ISO HDLC) with a procedurally generated table, incremental. */
static unsigned long paint_crc_tab[256];
static int paint_crc_ready = 0;

static void paint_crc_init(void) {
    unsigned k;
    int b;
    if (paint_crc_ready) return;
    for (k = 0; k < 256; k++) {
        unsigned long c = k;
        for (b = 0; b < 8; b++)
            c = (c & 1) ? (0xEDB88320UL ^ (c >> 1)) : (c >> 1);
        paint_crc_tab[k] = c;
    }
    paint_crc_ready = 1;
}

static unsigned long paint_crc_update(unsigned long c,
                                      const unsigned char *p,
                                      unsigned long n) {
    unsigned long k;
    paint_crc_init();
    for (k = 0; k < n; k++)
        c = paint_crc_tab[(c ^ p[k]) & 0xFF] ^ (c >> 8);
    return c;
}

/** Adler-32 over one buffer (the zlib trailer of a single IDAT). */
static unsigned long paint_adler(const unsigned char *p, unsigned long n) {
    unsigned long a = 1;
    unsigned long b = 0;
    unsigned long k;
    for (k = 0; k < n; k++) {
        a = (a + p[k]) % 65521;
        b = (b + a) % 65521;
    }
    return (b << 16) | a;
}

/** Bound-checked big-endian u32 store for the PNG writer. */
static int paint_put_u32(unsigned char *dst, unsigned long cap,
                         unsigned long *pos, unsigned long v) {
    if (!dst || !pos || *pos + 4 > cap) return -1;
    dst[*pos] = (unsigned char)((v >> 24) & 0xFF);
    dst[*pos + 1] = (unsigned char)((v >> 16) & 0xFF);
    dst[*pos + 2] = (unsigned char)((v >> 8) & 0xFF);
    dst[*pos + 3] = (unsigned char)(v & 0xFF);
    *pos += 4;
    return 0;
}

/** Bound-checked raw copy for the PNG writer. */
static int paint_put_bytes(unsigned char *dst, unsigned long cap,
                           unsigned long *pos, const unsigned char *src,
                           unsigned long n) {
    unsigned long k;
    if (!dst || !pos || *pos + n > cap || *pos + n < *pos) return -1;
    for (k = 0; k < n; k++)
        dst[*pos + k] = src[k];
    *pos += n;
    return 0;
}

/** Encode indexed pixels as 8-bit truecolor PNG (stored deflate blocks).
 * Returns the byte count or a negative code on any bound violation. */
static long paint_png_encode(unsigned char *dst, unsigned long cap,
                             const unsigned char *idx,
                             const unsigned char *pal, int w, int h) {
    static const unsigned char sig[8] = {137, 80, 78, 71, 13, 10, 26, 10};
    unsigned long pos = 0;
    unsigned long idat_len_pos;
    unsigned long idat_data_pos;
    unsigned long raw_len;
    unsigned long nblocks;
    unsigned long b;
    unsigned long crc;
    unsigned long adler_a = 1;
    unsigned long adler_b = 0;
    if (!dst || !idx || !pal) return -1;
    if (w <= 0 || h <= 0 || w > PAINT_PNG_MAX_DIM || h > PAINT_PNG_MAX_DIM)
        return -1;
    if (paint_put_bytes(dst, cap, &pos, sig, sizeof(sig)) < 0) return -1;
    if (paint_put_u32(dst, cap, &pos, 13) < 0) return -1;
    {
        unsigned char ihdr[17];
        ihdr[0] = 'I'; ihdr[1] = 'H'; ihdr[2] = 'D'; ihdr[3] = 'R';
        ihdr[4] = (unsigned char)((w >> 24) & 0xFF);
        ihdr[5] = (unsigned char)((w >> 16) & 0xFF);
        ihdr[6] = (unsigned char)((w >> 8) & 0xFF);
        ihdr[7] = (unsigned char)(w & 0xFF);
        ihdr[8] = (unsigned char)((h >> 24) & 0xFF);
        ihdr[9] = (unsigned char)((h >> 16) & 0xFF);
        ihdr[10] = (unsigned char)((h >> 8) & 0xFF);
        ihdr[11] = (unsigned char)(h & 0xFF);
        ihdr[12] = 8;
        ihdr[13] = 2;
        ihdr[14] = 0;
        ihdr[15] = 0;
        ihdr[16] = 0;
        if (paint_put_bytes(dst, cap, &pos, ihdr, 4) < 0) return -1;
        if (paint_put_bytes(dst, cap, &pos, ihdr + 4, 13) < 0) return -1;
        crc = paint_crc_update(0xFFFFFFFFUL, ihdr, sizeof(ihdr));
        if (paint_put_u32(dst, cap, &pos, crc ^ 0xFFFFFFFFUL) < 0) return -1;
    }
    idat_len_pos = pos;
    if (paint_put_u32(dst, cap, &pos, 0) < 0) return -1;
    {
        static const unsigned char idat[4] = {'I', 'D', 'A', 'T'};
        if (paint_put_bytes(dst, cap, &pos, idat, sizeof(idat)) < 0)
            return -1;
    }
    idat_data_pos = pos;
    {
        static const unsigned char zhdr[2] = {0x78, 0x01};
        if (paint_put_bytes(dst, cap, &pos, zhdr, sizeof(zhdr)) < 0)
            return -1;
        crc = paint_crc_update(0xFFFFFFFFUL, (unsigned char *)"IDAT", 4);
        crc = paint_crc_update(crc, zhdr, sizeof(zhdr));
    }
    raw_len = (unsigned long)h * (unsigned long)(1 + 3 * w);
    nblocks = (raw_len + 65534) / 65535;
    for (b = 0; b < nblocks; b++) {
        unsigned long off = b * 65535;
        unsigned long blen = raw_len - off;
        unsigned long k;
        unsigned char hdr[5];
        if (blen > 65535) blen = 65535;
        hdr[0] = (b + 1 == nblocks) ? 1 : 0;
        hdr[1] = (unsigned char)(blen & 0xFF);
        hdr[2] = (unsigned char)((blen >> 8) & 0xFF);
        hdr[3] = (unsigned char)(~blen & 0xFF);
        hdr[4] = (unsigned char)((~blen >> 8) & 0xFF);
        if (paint_put_bytes(dst, cap, &pos, hdr, sizeof(hdr)) < 0)
            return -1;
        crc = paint_crc_update(crc, hdr, sizeof(hdr));
        for (k = 0; k < blen; k++) {
            unsigned long o = off + k;
            unsigned long stride = (unsigned long)(1 + 3 * w);
            unsigned long row = o / stride;
            unsigned long col = o % stride;
            unsigned char v;
            if (col == 0) {
                v = 0;
            } else {
                unsigned long px = row * (unsigned long)w + (col - 1) / 3;
                unsigned ch = (col - 1) % 3;
                v = pal[idx[px] * 3 + ch];
            }
            if (pos + 1 > cap || pos + 1 < pos) return -1;
            dst[pos++] = v;
            crc = paint_crc_update(crc, &v, 1);
            adler_a = (adler_a + v) % 65521;
            adler_b = (adler_b + adler_a) % 65521;
        }
    }
    {
        unsigned long adler = (adler_b << 16) | adler_a;
        unsigned char tail[4];
        tail[0] = (unsigned char)((adler >> 24) & 0xFF);
        tail[1] = (unsigned char)((adler >> 16) & 0xFF);
        tail[2] = (unsigned char)((adler >> 8) & 0xFF);
        tail[3] = (unsigned char)(adler & 0xFF);
        if (paint_put_bytes(dst, cap, &pos, tail, sizeof(tail)) < 0)
            return -1;
        crc = paint_crc_update(crc, tail, sizeof(tail));
    }
    {
        unsigned long idat_len = pos - idat_data_pos;
        unsigned long kept = pos;
        unsigned long back = idat_len_pos;
        unsigned long v = idat_len;
        if (idat_data_pos > cap || back + 4 > cap) return -1;
        dst[back] = (unsigned char)((v >> 24) & 0xFF);
        dst[back + 1] = (unsigned char)((v >> 16) & 0xFF);
        dst[back + 2] = (unsigned char)((v >> 8) & 0xFF);
        dst[back + 3] = (unsigned char)(v & 0xFF);
        pos = kept;
        if (paint_put_u32(dst, cap, &pos, crc ^ 0xFFFFFFFFUL) < 0) return -1;
    }
    if (paint_put_u32(dst, cap, &pos, 0) < 0) return -1;
    {
        static const unsigned char iend[4] = {'I', 'E', 'N', 'D'};
        unsigned long c2;
        if (paint_put_bytes(dst, cap, &pos, iend, sizeof(iend)) < 0)
            return -1;
        c2 = paint_crc_update(0xFFFFFFFFUL, iend, sizeof(iend));
        if (paint_put_u32(dst, cap, &pos, c2 ^ 0xFFFFFFFFUL) < 0) return -1;
    }
    return (long)pos;
}

/** Decode a PNG file into the canvas (top-left, clamped, nearest-mapped).
 * Reports through the status line, never a partial silent canvas. */
static int paint_load_file(const char *path) {
    static unsigned char filebuf[PAINT_FILE_MAX];
    const unsigned char *pal768 = paint_pal();
    FILE *f;
    long n;
    int w;
    int h;
    int comp;
    unsigned char *px;
    int x;
    int y;
    if (paint_path_ok(path) < 0) {
        snprintf(paint_status, sizeof(paint_status), "bad path %s", path);
        return -1;
    }
    f = fopen(path, "rb");
    if (!f) {
        snprintf(paint_status, sizeof(paint_status), "cannot read %s",
                 path);
        return -1;
    }
    n = (long)fread(filebuf, 1, sizeof(filebuf), f);
    fclose(f);
    if (n <= 0 || n >= (long)sizeof(filebuf)) {
        snprintf(paint_status, sizeof(paint_status), "cannot read %s",
                 path);
        return -1;
    }
    px = stbi_load_from_memory(filebuf, (int)n, &w, &h, &comp, 3);
    if (!px || w <= 0 || h <= 0) {
        snprintf(paint_status, sizeof(paint_status), "%s: not a png",
                 path);
        return -1;
    }
    {
        int cw = w < PAINT_W ? w : PAINT_W;
        int ch = h < PAINT_H ? h : PAINT_H;
        memset(paint_px, paint_colors[PAINT_NCOLORS - 1], sizeof(paint_px));
        for (y = 0; y < ch; y++)
            for (x = 0; x < cw; x++) {
                int v = paint_nearest(pal768, px[(y * w + x) * 3],
                                      px[(y * w + x) * 3 + 1],
                                      px[(y * w + x) * 3 + 2]);
                paint_px[y * PAINT_W + x] = (unsigned char)v;
            }
        snprintf(paint_status, sizeof(paint_status), "loaded %s (%dx%d)",
                 path, w, h);
    }
    stbi_image_free(px);
    return 0;
}

/** Encode the canvas and write it to path, fail closed on any shortfall. */
static int paint_save_file(const char *path) {
    const unsigned char *pal768 = paint_pal();
    FILE *f;
    size_t n;
    long png_n;
    if (paint_path_ok(path) < 0) {
        snprintf(paint_status, sizeof(paint_status), "bad path %s", path);
        return -1;
    }
    png_n = paint_png_encode(paint_png, sizeof(paint_png), paint_px,
                             pal768, PAINT_W, PAINT_H);
    if (png_n <= 0) {
        snprintf(paint_status, sizeof(paint_status), "encode failed");
        return -1;
    }
    f = fopen(path, "wb");
    if (!f) {
        snprintf(paint_status, sizeof(paint_status), "cannot write %s",
                 path);
        return -1;
    }
    n = fwrite(paint_png, 1, (size_t)png_n, f);
    fclose(f);
    if (n != (size_t)png_n) {
        snprintf(paint_status, sizeof(paint_status), "short write %s",
                 path);
        return -1;
    }
    snprintf(paint_status, sizeof(paint_status), "saved %s (%ld bytes)",
             path, png_n);
    return 0;
}

/** Blit the canvas into the NK back-buffer after rasterize. */
static void paint_blit(int ox, int oy) {
    volatile uint8_t *fb = NK_BACKBUF;
    int x;
    int y;
    for (y = 0; y < PAINT_H; y++)
        for (x = 0; x < PAINT_W; x++) {
            int dx = ox + x;
            int dy = oy + y;
            if (dx < 0 || dx >= NK_W || dy < 0 || dy >= NK_H) continue;
            fb[dy * NK_W + dx] = paint_px[y * PAINT_W + x];
        }
}

/** Current drawing color index (eraser paints the canvas background). */
static unsigned char paint_ink(void) {
    if (paint_tool == PAINT_TOOL_ERASER)
        return paint_colors[PAINT_NCOLORS - 1];
    return paint_colors[paint_swatch % PAINT_NCOLORS];
}

/** Drive the active stroke from the Nuklear input state. */
static void paint_handle_input(struct nk_context *ctx) {
    struct nk_input *in = &ctx->input;
    int down = nk_input_is_mouse_down(in, NK_BUTTON_LEFT) ? 1 : 0;
    int mx = (int)in->mouse.pos.x - (int)paint_rectx;
    int my = (int)in->mouse.pos.y - (int)paint_recty;
    int inside = mx >= 0 && my >= 0 && mx < PAINT_W && my < PAINT_H;
    int size = paint_sizes[paint_size % PAINT_NSIZES];
    unsigned char ink = paint_ink();
    if (down && !paint_down && inside) {
        paint_down = 1;
        paint_anchorx = mx;
        paint_anchory = my;
        paint_lastx = mx;
        paint_lasty = my;
        memcpy(paint_backup, paint_px, sizeof(paint_px));
        if (paint_tool == PAINT_TOOL_BRUSH ||
            paint_tool == PAINT_TOOL_ERASER)
            paint_dab(paint_px, PAINT_W, PAINT_H, mx, my, ink, size);
        else if (paint_tool == PAINT_TOOL_FILL)
            paint_flood(paint_px, PAINT_W, PAINT_H, mx, my, ink);
    } else if (down && paint_down) {
        if (!inside) {
            mx = paint_clamp(mx, 0, PAINT_W - 1);
            my = paint_clamp(my, 0, PAINT_H - 1);
        }
        if (paint_tool == PAINT_TOOL_BRUSH ||
            paint_tool == PAINT_TOOL_ERASER) {
            paint_line(paint_px, PAINT_W, PAINT_H, paint_lastx, paint_lasty,
                       mx, my, ink, size);
            paint_lastx = mx;
            paint_lasty = my;
        } else if (paint_tool == PAINT_TOOL_LINE) {
            memcpy(paint_px, paint_backup, sizeof(paint_px));
            paint_line(paint_px, PAINT_W, PAINT_H, paint_anchorx,
                       paint_anchory, mx, my, ink, size);
        } else if (paint_tool == PAINT_TOOL_RECT) {
            memcpy(paint_px, paint_backup, sizeof(paint_px));
            paint_rect_fill(paint_px, PAINT_W, PAINT_H, paint_anchorx,
                            paint_anchory, mx, my, ink);
        } else if (paint_tool == PAINT_TOOL_CIRCLE) {
            int dx = mx - paint_anchorx;
            int dy = my - paint_anchory;
            int r = dx * dx + dy * dy;
            int k;
            memcpy(paint_px, paint_backup, sizeof(paint_px));
            k = 0;
            while ((k + 1) * (k + 1) <= r) k++;
            paint_circle_fill(paint_px, PAINT_W, PAINT_H, paint_anchorx,
                              paint_anchory, k, ink);
        }
    } else if (!down && paint_down) {
        paint_down = 0;
    }
}

/** Build the file row, the exact-size canvas beside the tool panel,
 * and the status row. The canvas cell is PAINT_W wide so every white
 * pixel shown is paintable; tools, colors and buttons live in the side
 * panel instead of above an oversized slot. */
static void paint_ui_build(struct nk_context *ctx) {
    int k;
    if (nk_begin(ctx, PAINT_TITLE, nk_rect(0, 0, (float)NK_W, (float)NK_H),
                 NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR)) {
        nk_layout_row_template_begin(ctx, 24);
        nk_layout_row_template_push_dynamic(ctx);
        nk_layout_row_template_push_static(ctx, PAINT_FILE_BTN_W);
        nk_layout_row_template_push_static(ctx, PAINT_FILE_BTN_W);
        nk_layout_row_template_end(ctx);
        nk_edit_string_zero_terminated(ctx, NK_EDIT_SIMPLE, paint_path,
                                       sizeof(paint_path) - 1,
                                       nk_filter_ascii);
        if (nk_button_label(ctx, "save"))
            paint_save_file(paint_path);
        if (nk_button_label(ctx, "load"))
            paint_load_file(paint_path);
        nk_layout_row_template_begin(ctx, PAINT_H);
        nk_layout_row_template_push_static(ctx, PAINT_W);
        nk_layout_row_template_push_dynamic(ctx);
        nk_layout_row_template_end(ctx);
        {
            struct nk_rect r;
            nk_widget(&r, ctx);
            paint_rectx = r.x;
            paint_recty = r.y;
            {
                struct nk_command_buffer *cv = nk_window_get_canvas(ctx);
                nk_fill_rect(cv, r, 0, nk_rgb(255, 255, 255));
            }
        }
        if (nk_group_begin(ctx, PAINT_PANEL_TITLE,
                           NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR)) {
            nk_layout_row_dynamic(ctx, 24, PAINT_NTOOLS);
            for (k = 0; k < PAINT_NTOOLS; k++) {
                if (nk_button_label(ctx, paint_tool_names[k]))
                    paint_tool = k;
            }
            nk_layout_row_dynamic(ctx, 22, PAINT_NCOLORS);
            for (k = 0; k < PAINT_NCOLORS; k++) {
                const unsigned char *pal768 = paint_pal();
                struct nk_color sw;
                sw = nk_rgb(pal768[paint_colors[k] * 3],
                            pal768[paint_colors[k] * 3 + 1],
                            pal768[paint_colors[k] * 3 + 2]);
                if (nk_button_color(ctx, sw))
                    paint_swatch = k;
            }
            nk_layout_row_dynamic(ctx, 24, 5);
            if (nk_button_label(ctx, "thin"))
                paint_size = 0;
            if (nk_button_label(ctx, "med"))
                paint_size = 1;
            if (nk_button_label(ctx, "thick"))
                paint_size = 2;
            if (nk_button_label(ctx, "clear")) {
                memset(paint_px, paint_colors[PAINT_NCOLORS - 1],
                       sizeof(paint_px));
                snprintf(paint_status, sizeof(paint_status), "cleared");
            }
            if (nk_button_label(ctx, "quit"))
                paint_quit = 1;
        }
        nk_group_end(ctx);
        nk_layout_row_dynamic(ctx, 18, 1);
        {
            char line[PAINT_STATUS_MAX];
            snprintf(line, sizeof(line), "%s sw%d %s | %s",
                     paint_tool_names[paint_tool],
                     paint_swatch,
                     paint_sizes[paint_size % PAINT_NSIZES] == 1 ? "thin" :
                     paint_sizes[paint_size % PAINT_NSIZES] == 2 ? "med" :
                     "thick",
                     paint_status[0] ? paint_status : "draw on the canvas");
            nk_label(ctx, line, NK_TEXT_LEFT);
        }
    }
    nk_end(ctx);
}

/** Scan the whole framebuffer for the canvas marker run (first four
 * swatches consecutive). Position-independent: it holds whatever video
 * mode the boot picked and wherever the compositor centered the window.
 * No console output inside: serial prints take milliseconds and open
 * windows for the 25 Hz desktop tick between present and scan. */
static int paint_pattern_present(int fw, int fh, int fp, int *ox, int *oy) {
    const unsigned char *pal768 = paint_pal();
    volatile uint8_t *fb = (volatile uint8_t *)MINIOS_FB_ADDR;
    int bpx = (fw > 0 && fp % fw == 0) ? fp / fw : 1;
    int y;
    if (!ox || !oy || fw <= 0 || fh <= 0 || fp <= 0) return 0;
    for (y = 0; y < fh; y++) {
        int x;
        for (x = 0; x + 3 < fw; x++) {
            volatile uint8_t *pxp = fb + y * fp + x * bpx;
            int k;
            int hit = 1;
            for (k = 0; k < 4; k++) {
                unsigned pi = (unsigned)paint_colors[1 + k] * 3;
                volatile uint8_t *q = pxp + k * bpx;
                if (bpx == 1) {
                    if (q[0] != paint_colors[1 + k]) { hit = 0; break; }
                } else if (q[0] != pal768[pi + 2] ||
                           q[1] != pal768[pi + 1] ||
                           q[2] != pal768[pi + 0]) {
                    hit = 0;
                    break;
                }
            }
            if (hit) {
                *ox = x;
                *oy = y;
                return 1;
            }
        }
    }
    return 0;
}

/** Headless selftest for BDD: core vectors, PNG roundtrip, one frame. */
static int paint_selftest(void) {
    const unsigned char *pal768 = paint_pal();
    unsigned char tiny[4] = {242, 243, 244, 245};
    unsigned char small_png[256];
    long png_n;
    int fw;
    int fh;
    int fp;
    struct nk_user_font font = nk_minios_font();
    struct nk_context ctx;
    static unsigned char ui_mem[PAINT_UI_MEMORY];
    int origin[2] = {0, 0};
    int mouse[4] = {0, 0, 0, 0};
    int ox = 0;
    int oy = 0;
    int landed = 0;
    memset(paint_px, 0, sizeof(paint_px));
    if (paint_plot(paint_px, PAINT_W, PAINT_H, 0, 0, 7) != 0 ||
        paint_px[0] != 7) {
        printf("paint: selftest plot failed\n");
        return 1;
    }
    if (paint_plot(paint_px, PAINT_W, PAINT_H, -1, 0, 1) == 0) {
        printf("paint: selftest plot bounds failed\n");
        return 1;
    }
    memset(paint_px, 0, sizeof(paint_px));
    if (paint_line(paint_px, PAINT_W, PAINT_H, 0, 0, 9, 0, 5, 1) != 10 ||
        paint_px[0] != 5 || paint_px[9] != 5) {
        printf("paint: selftest line failed\n");
        return 1;
    }
    memset(paint_px, 1, sizeof(paint_px));
    {
        int k;
        for (k = 0; k < PAINT_W; k++) {
            paint_px[k] = 0;
            paint_px[(PAINT_H - 1) * PAINT_W + k] = 0;
        }
        for (k = 0; k < PAINT_H; k++) {
            paint_px[k * PAINT_W] = 0;
            paint_px[k * PAINT_W + PAINT_W - 1] = 0;
        }
    }
    if (paint_flood(paint_px, PAINT_W, PAINT_H, PAINT_W / 2, PAINT_H / 2,
                    4) != (PAINT_W - 2) * (PAINT_H - 2) ||
        paint_px[0] != 0) {
        printf("paint: selftest flood failed\n");
        return 1;
    }
    if (paint_path_ok("/drawing.png") != 0 ||
        paint_path_ok("/../escape.png") == 0 ||
        paint_path_ok("/art/a.txt") == 0) {
        printf("paint: selftest path failed\n");
        return 1;
    }
    {
        int v = paint_nearest(pal768, 255, 0, 0);
        if (v < 0 || pal768[v * 3] != 255 || pal768[v * 3 + 1] != 0 ||
            pal768[v * 3 + 2] != 0) {
            printf("paint: selftest nearest failed\n");
            return 1;
        }
    }
    png_n = paint_png_encode(small_png, sizeof(small_png), tiny, pal768,
                             2, 2);
    if (png_n <= 0 || small_png[0] != 137 || small_png[1] != 80) {
        printf("paint: selftest png encode failed\n");
        return 1;
    }
    {
        int w = 0;
        int h = 0;
        int comp = 0;
        unsigned char *px = stbi_load_from_memory(small_png, (int)png_n,
                                                  &w, &h, &comp, 3);
        if (!px || w != 2 || h != 2) {
            printf("paint: selftest png decode failed\n");
            return 1;
        }
        {
            int v0 = paint_nearest(pal768, px[0], px[1], px[2]);
            int v3 = paint_nearest(pal768, px[9], px[10], px[11]);
            if (v0 < 0 || v3 < 0 ||
                pal768[v0 * 3] != pal768[242 * 3] ||
                pal768[v0 * 3 + 1] != pal768[242 * 3 + 1] ||
                pal768[v0 * 3 + 2] != pal768[242 * 3 + 2] ||
                pal768[v3 * 3] != pal768[245 * 3] ||
                pal768[v3 * 3 + 1] != pal768[245 * 3 + 1] ||
                pal768[v3 * 3 + 2] != pal768[245 * 3 + 2]) {
                printf("paint: selftest png roundtrip failed\n");
                stbi_image_free(px);
                return 1;
            }
        }
        stbi_image_free(px);
    }
    printf("paint: png ok (%ld bytes 2x2)\n", png_n);
    memset(paint_px, paint_colors[PAINT_NCOLORS - 1], sizeof(paint_px));
    paint_px[0] = paint_colors[1];
    paint_px[PAINT_W - 1] = paint_colors[2];
    paint_px[(PAINT_H - 1) * PAINT_W] = paint_colors[3];
    paint_px[PAINT_N - 1] = paint_colors[4];
    if (paint_save_file("/paint_selftest.png") != 0) {
        printf("paint: selftest save failed\n");
        return 1;
    }
    memset(paint_px, paint_colors[PAINT_NCOLORS - 1], sizeof(paint_px));
    if (paint_load_file("/paint_selftest.png") != 0) {
        printf("paint: selftest load failed\n");
        return 1;
    }
    {
        static const int corners[4] = {
            0, PAINT_W - 1, (PAINT_H - 1) * PAINT_W, PAINT_N - 1
        };
        int k;
        int hit = 1;
        for (k = 0; k < 4 && hit; k++) {
            unsigned char got = paint_px[corners[k]];
            unsigned char want = paint_colors[1 + k];
            if (pal768[got * 3] != pal768[want * 3] ||
                pal768[got * 3 + 1] != pal768[want * 3 + 1] ||
                pal768[got * 3 + 2] != pal768[want * 3 + 2])
                hit = 0;
        }
        if (!hit) {
            printf("paint: selftest file roundtrip failed\n");
            return 1;
        }
    }
    printf("paint: file ok (/paint_selftest.png)\n");
    nk_sys_vga_mode(1);
    nk_sys_kbd_raw(1);
    nk_sys_palette(pal768);
    nk_sys_fb_info(&fw, &fh, &fp);
    if (!nk_init_fixed(&ctx, ui_mem, sizeof(ui_mem), &font)) {
        printf("paint: init failed\n");
        return 1;
    }
    nk_input_begin(&ctx);
    nk_input_end(&ctx);
    memset(paint_px, paint_colors[PAINT_NCOLORS - 1], sizeof(paint_px));
    paint_px[0] = paint_colors[1];
    paint_px[1] = paint_colors[2];
    paint_px[2] = paint_colors[3];
    paint_px[3] = paint_colors[4];
    paint_ui_build(&ctx);
    nk_rasterize(&ctx);
    paint_blit((int)paint_rectx, (int)paint_recty);
    {
        int attempt;
        landed = 0;
        for (attempt = 0; attempt < PAINT_FRAME_ATTEMPTS && !landed;
             attempt++) {
            if (nk_sys_nk_frame(origin) != 0) {
                printf("paint: frame syscall failed\n");
                return 1;
            }
            landed = paint_pattern_present(fw, fh, fp, &ox, &oy);
        }
    }
    if (nk_sys_mouse(mouse) != 0) {
        printf("paint: mouse syscall failed\n");
        return 1;
    }
    if (nk_sys_mouse_badptr() >= 0) {
        printf("paint: mouse accepted a kernel pointer\n");
        return 1;
    }
    if (landed)
        printf("paint: pattern at (%d,%d)\n", ox, oy);
    if (!landed) {
        printf("paint: composite did not land (canvas %d,%d origin %d,%d)\n",
               (int)paint_rectx, (int)paint_recty, origin[0], origin[1]);
        return 1;
    }
    nk_free(&ctx);
    nk_sys_kbd_raw(0);
    nk_sys_vga_mode(0);
    printf("paint: frame ok (%dx%d)\n", NK_W, NK_H);
    return 0;
}

static unsigned char paint_ui_memory[PAINT_UI_MEMORY];

/** Interactive GUI loop: toolbar, canvas strokes, blit, present. */
static void paint_gui_run(void) {
    struct nk_user_font font = nk_minios_font();
    struct nk_context ctx;
    const unsigned char *pal768 = paint_pal();
    int origin[2] = {0, 0};
    nk_sys_vga_mode(1);
    nk_sys_kbd_raw(1);
    nk_sys_palette(pal768);
    nk_sys_gfx_set_title(PAINT_TITLE);
    if (!nk_init_fixed(&ctx, paint_ui_memory, sizeof(paint_ui_memory),
                       &font)) {
        printf("paint: init failed\n");
        nk_sys_kbd_raw(0);
        nk_sys_vga_mode(0);
        return;
    }
    nk_theme_apply(&ctx, 0);
    memset(paint_px, paint_colors[PAINT_NCOLORS - 1], sizeof(paint_px));
    if (paint_autoload) {
        paint_autoload = 0;
        paint_load_file(paint_path);
    }
    paint_quit = 0;
    paint_down = 0;
    if (paint_path[0] == 0)
        strcpy(paint_path, PAINT_DEFAULT_PATH);
    while (!paint_quit) {
        nk_input_begin(&ctx);
        nk_poll_input(&ctx);
        nk_input_end(&ctx);
        if (nk_quit_requested()) paint_quit = 1;
        paint_ui_build(&ctx);
        paint_handle_input(&ctx);
        nk_rasterize(&ctx);
        paint_blit((int)paint_rectx, (int)paint_recty);
        if (nk_sys_nk_frame(origin) == 0)
            nk_set_window_origin(origin[0], origin[1]);
        nk_clear(&ctx);
        {
            unsigned t0 = (unsigned)nk_sys_time_ms();
            while ((unsigned)nk_sys_time_ms() - t0 < PAINT_FRAME_MS) {
                __asm__ volatile("pause");
            }
        }
    }
    nk_free(&ctx);
    nk_sys_kbd_raw(0);
    nk_sys_vga_mode(0);
}

int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], "--selftest") == 0)
        return paint_selftest();
    if (argc > 1 && strcmp(argv[1], "--help") == 0) {
        printf("paint: Nuklear canvas paint (PNG save/load)\n");
        printf("  (no args)        GUI paint\n");
        printf("  paint <file>     GUI paint preloading a png\n");
        printf("  --selftest       core vectors, png roundtrip, one frame\n");
        return 0;
    }
    if (argc > 1 && argv[1][0] != '-') {
        if (strlen(argv[1]) + 1 < sizeof(paint_path)) {
            strcpy(paint_path, argv[1]);
            paint_autoload = 1;
        }
    }
    paint_gui_run();
    return 0;
}
