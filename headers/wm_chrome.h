/** Docstring: Window chrome pixel math for the MiniOS desktop.
 *
 * Single-file header-only contract owning the integer arithmetic behind
 * the visual polish of the true-color desktop: alpha blending, soft drop
 * shadows, anti-aliased rounded corners and vertical gradients. Every
 * function is pure over its arguments, so it stays host-testable; the
 * kernel keeps owning the framebuffer and only feeds pixels through it.
 * Packed pixels are 0x00RRGGBB. All functions fail closed on degenerate
 * input and never overflow for 8-bit channels.
 */
#ifndef WM_CHROME_H
#define WM_CHROME_H

/** Docstring: Fully opaque alpha. */
#define WM_CHROME_ALPHA_OPAQUE 255

/** Docstring: Centralized chrome configuration, no magic numbers. */
typedef struct {
    int shadow_radius;
    int shadow_dx;
    int shadow_dy;
    int shadow_alpha;
    int corner_radius;
    int title_lift;
    int title_sink;
    int glass_alpha;
    int glow_alpha;
    int term_alpha;
} wm_chrome_config_t;

/** Docstring: Default chrome: 8 px soft shadow offset 2/4 px at 110/255,
 * 4 px corners (an 8 px title strip cannot carry more), title gradient
 * lifting 22 and sinking 18 levels, glass panels at 150/255, hover glow at
 * 70/255, terminal background 205/255 opaque. */
#define WM_CHROME_CONFIG_DEFAULT { 8, 2, 4, 110, 4, 22, 18, 150, 70, 205 }

/** Docstring: Largest corner radius the caller's scratch buffers carry. */
#define WM_CHROME_RADIUS_MAX 8

/** Docstring: Integer square root, floor, for non-negative arguments. */
static inline unsigned long wm_chrome_isqrt(unsigned long v)
{
    unsigned long r = 0;
    unsigned long bit = 1UL << (sizeof(unsigned long) * 8 - 2);
    while (bit > v) {
        bit >>= 2;
    }
    while (bit != 0) {
        if (v >= r + bit) {
            v -= r + bit;
            r = (r >> 1) + bit;
        } else {
            r >>= 1;
        }
        bit >>= 2;
    }
    return r;
}

/** Docstring: Clamp a channel to 0..255. */
static inline int wm_chrome_clamp(int v)
{
    return v < 0 ? 0 : (v > 255 ? 255 : v);
}

/** Docstring: Blend one channel: src over dst at alpha/255, rounded. */
static inline int wm_chrome_blend_channel(int dst, int src, int alpha)
{
    int a = wm_chrome_clamp(alpha);
    dst = wm_chrome_clamp(dst);
    src = wm_chrome_clamp(src);
    return (src * a + dst * (255 - a) + 127) / 255;
}

/** Docstring: Blend a packed src pixel over a packed dst pixel. */
static inline unsigned long wm_chrome_blend(unsigned long dst, unsigned long src, int alpha)
{
    int r = wm_chrome_blend_channel((int)((dst >> 16) & 0xFF), (int)((src >> 16) & 0xFF), alpha);
    int g = wm_chrome_blend_channel((int)((dst >> 8) & 0xFF), (int)((src >> 8) & 0xFF), alpha);
    int b = wm_chrome_blend_channel((int)(dst & 0xFF), (int)(src & 0xFF), alpha);
    return ((unsigned long)r << 16) | ((unsigned long)g << 8) | (unsigned long)b;
}

/** Docstring: Add a signed delta to every channel of a packed pixel. */
static inline unsigned long wm_chrome_shift(unsigned long px, int delta)
{
    int r = wm_chrome_clamp((int)((px >> 16) & 0xFF) + delta);
    int g = wm_chrome_clamp((int)((px >> 8) & 0xFF) + delta);
    int b = wm_chrome_clamp((int)(px & 0xFF) + delta);
    return ((unsigned long)r << 16) | ((unsigned long)g << 8) | (unsigned long)b;
}

/** Docstring: Vertical gradient row: lighter by lift at row 0, darker by
 * sink at the last row of span rows, linear in between. */
static inline unsigned long wm_chrome_gradient(unsigned long base, int row, int span,
                                               const wm_chrome_config_t *cfg)
{
    int delta;
    if (cfg == 0 || span <= 1 || row < 0 || row >= span) {
        return base;
    }
    delta = cfg->title_lift - ((cfg->title_lift + cfg->title_sink) * row) / (span - 1);
    return wm_chrome_shift(base, delta);
}

/** Docstring: Shadow alpha for pixel (px,py) of a window at (rx,ry,rw,rh).
 * The shadow is the window rect shifted by (dx,dy); inside it the alpha
 * is the maximum, outside it falls off quadratically over radius pixels
 * of euclidean distance. Zero for degenerate input or beyond the radius. */
static inline int wm_chrome_shadow_alpha(const wm_chrome_config_t *cfg, int px, int py,
                                         int rx, int ry, int rw, int rh)
{
    long ox, oy, d2;
    unsigned long d;
    long r;
    long num;
    if (cfg == 0 || rw <= 0 || rh <= 0 || cfg->shadow_radius <= 0 || cfg->shadow_alpha <= 0) {
        return 0;
    }
    rx += cfg->shadow_dx;
    ry += cfg->shadow_dy;
    ox = px < rx ? (long)rx - px : (px >= rx + rw ? (long)px - (rx + rw - 1) : 0);
    oy = py < ry ? (long)ry - py : (py >= ry + rh ? (long)py - (ry + rh - 1) : 0);
    d2 = ox * ox + oy * oy;
    r = cfg->shadow_radius;
    if (d2 == 0) {
        return wm_chrome_clamp(cfg->shadow_alpha);
    }
    d = wm_chrome_isqrt((unsigned long)d2);
    if ((long)d >= r) {
        return 0;
    }
    num = r - (long)d;
    return (int)(((long)wm_chrome_clamp(cfg->shadow_alpha) * num * num) / (r * r));
}

/** Docstring: Coverage 0..255 of pixel (x,y) inside a rounded corner of
 * the given radius. (0,0) is the outermost pixel of the corner and
 * (radius-1,radius-1) the innermost; pixels outside the radius box are
 * fully covered. The edge is anti-aliased across one pixel. */
static inline int wm_chrome_corner_coverage(int radius, int x, int y)
{
    long dx, dy, d16, edge16;
    long cov;
    if (radius <= 0 || x < 0 || y < 0) {
        return WM_CHROME_ALPHA_OPAQUE;
    }
    if (x >= radius || y >= radius) {
        return WM_CHROME_ALPHA_OPAQUE;
    }
    dx = 2L * radius - (2L * x + 1);
    dy = 2L * radius - (2L * y + 1);
    d16 = (long)wm_chrome_isqrt((unsigned long)((dx * dx + dy * dy) << 8));
    edge16 = 32L * radius;
    cov = ((edge16 + 16L - d16) * 255L) / 32L;
    return (int)(cov < 0 ? 0 : (cov > 255 ? 255 : cov));
}

/** Docstring: Coverage 0..255 of pixel (x,y) of a disc of the given radius
 * inscribed in a 2*radius square, anti-aliased across one pixel. Zero
 * outside the square or for a non-positive radius. */
static inline int wm_chrome_disc_coverage(int radius, int x, int y)
{
    int side;
    if (radius <= 0 || x < 0 || y < 0 || x >= 2 * radius || y >= 2 * radius) {
        return 0;
    }
    side = 2 * radius - 1;
    return wm_chrome_corner_coverage(radius, x < radius ? x : side - x, y < radius ? y : side - y);
}

#endif
