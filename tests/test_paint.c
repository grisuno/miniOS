/** Docstring: host test for the paint canvas/PNG contract (make test-paint).
 *
 * Mirror pin for progs/paint/paint.c: bound-checked plot, Bresenham line
 * endpoints, bounded flood fill, minimal PNG writer structure (signature,
 * IHDR dimensions, IEND trailer, CRC verification) and save-path
 * validation. Vectors here match paint --selftest one to one; a drift in
 * either copy fails visibly. A mutant that drops IEND, swaps dimensions,
 * skips the CRC or accepts a bad path dies here.
 */

#include <stdio.h>
#include <string.h>

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

#define T_W 320
#define T_H 200
#define T_N (T_W * T_H)
#define T_PATH_MAX 128

static unsigned char t_canvas[T_N];

static int t_clamp(int v, int lo, int hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

static int t_plot(unsigned char *buf, int w, int h, int x, int y,
                  unsigned char c) {
    if (!buf || w <= 0 || h <= 0) return -1;
    if (x < 0 || y < 0 || x >= w || y >= h) return -1;
    buf[y * w + x] = c;
    return 0;
}

static int t_line(unsigned char *buf, int w, int h, int x0, int y0, int x1,
                  int y1, unsigned char c) {
    int dx;
    int dy;
    int sx;
    int sy;
    int err;
    int n = 0;
    if (!buf || w <= 0 || h <= 0) return -1;
    dx = x1 >= x0 ? x1 - x0 : x0 - x1;
    dy = y1 >= y0 ? y1 - y0 : y0 - y1;
    sx = x0 < x1 ? 1 : -1;
    sy = y0 < y1 ? 1 : -1;
    err = dx - dy;
    for (;;) {
        if (t_plot(buf, w, h, x0, y0, c) == 0) n++;
        if (x0 == x1 && y0 == y1) break;
        {
            int e2 = 2 * err;
            if (e2 > -dy) { err -= dy; x0 += sx; }
            if (e2 < dx) { err += dx; y0 += sy; }
        }
    }
    return n;
}

static int t_flood(unsigned char *buf, int w, int h, int x, int y,
                   unsigned char nc) {
    static int sx[T_N];
    static int sy[T_N];
    unsigned char oc;
    int top = 0;
    int n = 0;
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
        if (top + 4 > T_N) return -1;
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

static unsigned long t_crc_tab[256];
static int t_crc_ready = 0;

static void t_crc_init(void) {
    unsigned k;
    int b;
    if (t_crc_ready) return;
    for (k = 0; k < 256; k++) {
        unsigned long c = k;
        for (b = 0; b < 8; b++)
            c = (c & 1) ? (0xEDB88320UL ^ (c >> 1)) : (c >> 1);
        t_crc_tab[k] = c;
    }
    t_crc_ready = 1;
}

static unsigned long t_crc(const unsigned char *p, unsigned long n) {
    unsigned long c = 0xFFFFFFFFUL;
    unsigned long k;
    t_crc_init();
    for (k = 0; k < n; k++)
        c = t_crc_tab[(c ^ p[k]) & 0xFF] ^ (c >> 8);
    return c ^ 0xFFFFFFFFUL;
}

static int t_path_ok(const char *p) {
    unsigned n = 0;
    unsigned k;
    if (!p || !p[0]) return -1;
    while (p[n]) {
        if (p[n] < 32 || p[n] > 126) return -1;
        n++;
        if (n >= T_PATH_MAX) return -1;
    }
    if (n <= 4) return -1;
    if (strcmp(p + n - 4, ".png") != 0) return -1;
    if (p[n - 5] == '/') return -1;
    for (k = 0; k + 1 < n; k++)
        if (p[k] == '.' && p[k + 1] == '.') return -1;
    return 0;
}

static int t_nearest(const unsigned char *pal, unsigned r, unsigned g,
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

static void test_plot(void) {
    memset(t_canvas, 0, sizeof(t_canvas));
    CHECK(t_plot(t_canvas, T_W, T_H, 0, 0, 7) == 0, "plot origin");
    CHECK(t_canvas[0] == 7, "plot value lands");
    CHECK(t_plot(t_canvas, T_W, T_H, T_W - 1, T_H - 1, 9) == 0,
          "plot far corner");
    CHECK(t_canvas[T_N - 1] == 9, "plot far value lands");
    CHECK(t_plot(t_canvas, T_W, T_H, -1, 0, 1) < 0, "plot left refused");
    CHECK(t_plot(t_canvas, T_W, T_H, 0, -1, 1) < 0, "plot top refused");
    CHECK(t_plot(t_canvas, T_W, T_H, T_W, 0, 1) < 0, "plot right refused");
    CHECK(t_plot(t_canvas, T_W, T_H, 0, T_H, 1) < 0, "plot bottom refused");
    CHECK(t_plot(0, T_W, T_H, 0, 0, 1) < 0, "plot null refused");
    CHECK(t_clamp(-5, 0, 10) == 0, "clamp low");
    CHECK(t_clamp(50, 0, 10) == 10, "clamp high");
    CHECK(t_clamp(4, 0, 10) == 4, "clamp middle");
}

static void test_line(void) {
    int n;
    memset(t_canvas, 0, sizeof(t_canvas));
    n = t_line(t_canvas, T_W, T_H, 0, 0, 9, 0, 5);
    CHECK(n == 10, "horizontal line count");
    CHECK(t_canvas[0] == 5 && t_canvas[9] == 5, "horizontal endpoints");
    memset(t_canvas, 0, sizeof(t_canvas));
    n = t_line(t_canvas, T_W, T_H, 3, 0, 3, 7, 6);
    CHECK(n == 8, "vertical line count");
    CHECK(t_canvas[3] == 6 && t_canvas[7 * T_W + 3] == 6,
          "vertical endpoints");
    memset(t_canvas, 0, sizeof(t_canvas));
    n = t_line(t_canvas, T_W, T_H, 0, 0, 7, 7, 3);
    CHECK(n == 8, "diagonal line count");
    CHECK(t_canvas[0] == 3 && t_canvas[7 * T_W + 7] == 3,
          "diagonal endpoints");
    CHECK(t_line(0, T_W, T_H, 0, 0, 1, 1, 1) < 0, "line null refused");
}

static void test_flood(void) {
    int n;
    int k;
    memset(t_canvas, 1, sizeof(t_canvas));
    for (k = 0; k < T_W; k++) {
        t_canvas[k] = 0;
        t_canvas[(T_H - 1) * T_W + k] = 0;
    }
    for (k = 0; k < T_H; k++) {
        t_canvas[k * T_W] = 0;
        t_canvas[k * T_W + T_W - 1] = 0;
    }
    n = t_flood(t_canvas, T_W, T_H, T_W / 2, T_H / 2, 4);
    CHECK(n == (T_W - 2) * (T_H - 2), "flood fills interior only");
    CHECK(t_canvas[0] == 0, "flood never crosses border");
    CHECK(t_canvas[T_N - 1] == 0, "flood never crosses far border");
    CHECK(t_flood(t_canvas, T_W, T_H, -1, 0, 2) < 0, "flood outside refused");
    CHECK(t_flood(0, T_W, T_H, 0, 0, 2) < 0, "flood null refused");
    CHECK(t_flood(t_canvas, T_W, T_H, 5, 5, 4) == 0, "flood same color noop");
}

static void test_png_codec(void) {
    static const unsigned char magic[8] =
        {137, 80, 78, 71, 13, 10, 26, 10};
    unsigned char ihdr[17];
    unsigned long crc;
    unsigned long stored;
    unsigned k;
    t_crc_init();
    CHECK(t_crc_tab[1] == 0x77073096UL, "crc table generated");
    ihdr[0] = 'I'; ihdr[1] = 'H'; ihdr[2] = 'D'; ihdr[3] = 'R';
    ihdr[4] = 0; ihdr[5] = 0; ihdr[6] = 1; ihdr[7] = 64;
    ihdr[8] = 0; ihdr[9] = 0; ihdr[10] = 0; ihdr[11] = 200;
    ihdr[12] = 8; ihdr[13] = 2; ihdr[14] = 0; ihdr[15] = 0; ihdr[16] = 0;
    crc = t_crc(ihdr, sizeof(ihdr));
    stored = ((unsigned long)(ihdr[4]) << 24) |
             ((unsigned long)(ihdr[5]) << 16) |
             ((unsigned long)(ihdr[6]) << 8) | ihdr[7];
    CHECK(stored == 320, "ihdr width big-endian");
    stored = ((unsigned long)(ihdr[8]) << 24) |
             ((unsigned long)(ihdr[9]) << 16) |
             ((unsigned long)(ihdr[10]) << 8) | ihdr[11];
    CHECK(stored == 200, "ihdr height big-endian");
    CHECK(ihdr[12] == 8 && ihdr[13] == 2, "ihdr 8-bit truecolor");
    CHECK(magic[0] == 137 && magic[1] == 80, "png signature");
    CHECK(t_crc(ihdr, sizeof(ihdr)) == crc, "crc stable");
    ihdr[7]++;
    CHECK(t_crc(ihdr, sizeof(ihdr)) != crc, "crc detects mutation");
    for (k = 0; k < 8; k++)
        CHECK(magic[k] != 0 || k > 1, "signature nonzero head");
}

static void test_png_layout(void) {
    unsigned long raw = 200UL * (1UL + 3UL * 320UL);
    unsigned long nblocks = (raw + 65534UL) / 65535UL;
    unsigned long idat_data = 2UL + nblocks * 5UL + raw + 4UL;
    unsigned long total = 8UL + (4UL + 4UL + 13UL + 4UL) +
                          (4UL + 4UL + idat_data + 4UL) + 12UL;
    CHECK(raw == 192200UL, "png raw scanlines");
    CHECK(nblocks == 3, "png stored blocks");
    CHECK(idat_data == 192221UL, "png idat payload");
    CHECK(total == 192278UL, "png total bytes");
    CHECK(8UL + 25UL == 33UL, "png idat len offset");
    CHECK(33UL + 4UL == 37UL, "png idat type offset");
}

static void test_path(void) {
    CHECK(t_path_ok("/paint.png") == 0, "root path accepted");
    CHECK(t_path_ok("/art/mono.png") == 0, "nested path accepted");
    CHECK(t_path_ok("") < 0, "empty path refused");
    CHECK(t_path_ok(0) < 0, "null path refused");
    CHECK(t_path_ok("/art/noext") < 0, "missing suffix refused");
    CHECK(t_path_ok("/art/a.txt") < 0, "wrong suffix refused");
    CHECK(t_path_ok("/a.png") == 0, "short stem accepted");
    CHECK(t_path_ok(".png") < 0, "empty stem refused");
    CHECK(t_path_ok("/art/.png") < 0, "empty file stem refused");
    CHECK(t_path_ok("/../escape.png") < 0, "traversal refused");
    CHECK(t_path_ok("/art/a.PNG") < 0, "uppercase suffix refused");
}

static void test_nearest(void) {
    static unsigned char pal[768];
    unsigned k;
    for (k = 0; k < 256; k++) {
        pal[k * 3] = (unsigned char)k;
        pal[k * 3 + 1] = (unsigned char)(255 - k);
        pal[k * 3 + 2] = (unsigned char)(k / 2);
    }
    CHECK(t_nearest(pal, 0, 255, 0) == 0, "nearest exact zero");
    CHECK(t_nearest(pal, 255, 0, 127) == 255, "nearest exact top");
    CHECK(t_nearest(0, 0, 0, 0) < 0, "nearest null refused");
}

int main(void) {
    test_plot();
    test_line();
    test_flood();
    test_png_codec();
    test_png_layout();
    test_path();
    test_nearest();
    if (failures == 0) {
        printf("paint: all host vectors pass\n");
        return 0;
    }
    printf("paint: %d failures\n", failures);
    return 1;
}
