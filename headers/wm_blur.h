/** Docstring: Frosted-glass box blur for the MiniOS desktop.
 *
 * Single-file header-only contract owning the integer arithmetic behind
 * the blurred backdrop of translucent panels (dock, profile card,
 * terminal windows). The blur is a separable box filter run a small
 * number of times, which converges on a gaussian; every line is filtered
 * with a running sum, so the cost per pixel does not depend on the
 * radius. Edges replicate the border pixel, so a uniform image is
 * returned unchanged and no darkening creeps in from outside the rect.
 *
 * Every function is pure over its arguments and host-testable; the
 * kernel owns the buffers and only feeds pixels through it. Packed
 * pixels are 0x00RRGGBB. All functions fail closed on degenerate input.
 *
 * Usage: read a rect into a w*h buffer, call wm_blur_rect with a scratch
 * line of wm_blur_line_len(w, h) entries, write the buffer back.
 * Failure modes: wm_blur_rect returns 0 and leaves the buffer untouched
 * when the geometry or the configuration is out of range.
 */
#ifndef WM_BLUR_H
#define WM_BLUR_H

/** Docstring: Largest box radius; bounds the running sum and the
 * reciprocal table so the fixed-point average stays exact. */
#define WM_BLUR_RADIUS_MAX 32

/** Docstring: Largest number of box passes. */
#define WM_BLUR_PASSES_MAX 4

/** Docstring: Fixed-point shift of the window reciprocal. With a window
 * of at most 2*WM_BLUR_RADIUS_MAX+1 pixels of 8-bit channels the
 * multiply-shift equals the integer division exactly. */
#define WM_BLUR_RECIP_SHIFT 24

/** Docstring: Channel mask of a packed pixel. */
#define WM_BLUR_CHANNEL_MASK 0xFFu

/** Docstring: Centralized blur configuration, no magic numbers. */
typedef struct {
    int radius;
    int passes;
} wm_blur_config_t;

/** Docstring: Default frost: two passes of a 9-pixel box (radius 4), a
 * triangle kernel 17 pixels wide that hides text and edges behind a
 * panel while keeping the colour of what lies under it. */
#define WM_BLUR_CONFIG_DEFAULT { 4, 2 }

/** Docstring: 1 when the configuration is inside the supported range. */
static inline int wm_blur_config_valid(const wm_blur_config_t *cfg)
{
    return cfg != 0 && cfg->radius >= 1 && cfg->radius <= WM_BLUR_RADIUS_MAX &&
           cfg->passes >= 1 && cfg->passes <= WM_BLUR_PASSES_MAX;
}

/** Docstring: Scratch entries wm_blur_rect needs for a w by h rect: one
 * full line in either direction. Zero for a degenerate rect. */
static inline unsigned long wm_blur_line_len(int w, int h)
{
    if (w <= 0 || h <= 0) {
        return 0;
    }
    return (unsigned long)(w > h ? w : h);
}

/** Docstring: Reciprocal of a window of win pixels, rounded up, in
 * WM_BLUR_RECIP_SHIFT fixed point. Zero for a non-positive window. */
static inline unsigned long wm_blur_recip(int win)
{
    if (win <= 0) {
        return 0;
    }
    return ((1UL << WM_BLUR_RECIP_SHIFT) + (unsigned long)win - 1UL) / (unsigned long)win;
}

/** Docstring: Rounded average of a channel sum over win pixels through
 * the reciprocal: equals (sum + win / 2) / win for every reachable sum. */
static inline unsigned int wm_blur_avg(unsigned long sum, int win, unsigned long recip)
{
    return (unsigned int)(((sum + (unsigned long)(win / 2)) * recip) >> WM_BLUR_RECIP_SHIFT);
}

/** Docstring: Clamp a line index to 0..n-1 (edge replication). */
static inline int wm_blur_edge(int i, int n)
{
    return i < 0 ? 0 : (i >= n ? n - 1 : i);
}

/** Docstring: Box-blur one line of n pixels spaced stride entries apart,
 * in place. line is a scratch of at least n entries that receives the
 * untouched source. A radius outside 1..WM_BLUR_RADIUS_MAX, a null
 * pointer or an empty line leave the pixels untouched. */
static inline void wm_blur_line(unsigned int *px, long stride, int n, int radius,
                                unsigned int *line)
{
    unsigned long sr = 0, sg = 0, sb = 0;
    unsigned long recip;
    int win, i, k;
    if (px == 0 || line == 0 || n <= 0 || radius < 1 || radius > WM_BLUR_RADIUS_MAX) {
        return;
    }
    win = 2 * radius + 1;
    recip = wm_blur_recip(win);
    for (i = 0; i < n; i++) {
        line[i] = px[(long)i * stride];
    }
    for (k = -radius; k <= radius; k++) {
        unsigned int p = line[wm_blur_edge(k, n)];
        sr += (p >> 16) & WM_BLUR_CHANNEL_MASK;
        sg += (p >> 8) & WM_BLUR_CHANNEL_MASK;
        sb += p & WM_BLUR_CHANNEL_MASK;
    }
    for (i = 0; i < n; i++) {
        unsigned int out = line[wm_blur_edge(i - radius, n)];
        unsigned int in = line[wm_blur_edge(i + radius + 1, n)];
        px[(long)i * stride] = (wm_blur_avg(sr, win, recip) << 16) |
                               (wm_blur_avg(sg, win, recip) << 8) |
                               wm_blur_avg(sb, win, recip);
        sr = sr + ((in >> 16) & WM_BLUR_CHANNEL_MASK) - ((out >> 16) & WM_BLUR_CHANNEL_MASK);
        sg = sg + ((in >> 8) & WM_BLUR_CHANNEL_MASK) - ((out >> 8) & WM_BLUR_CHANNEL_MASK);
        sb = sb + (in & WM_BLUR_CHANNEL_MASK) - (out & WM_BLUR_CHANNEL_MASK);
    }
}

/** Docstring: Blur a w by h rect of packed pixels in place: every pass
 * filters all rows, then all columns. line is a scratch of at least
 * wm_blur_line_len(w, h) entries. Returns 1 when the rect was blurred,
 * 0 (pixels untouched) on a null pointer, a degenerate rect or an
 * invalid configuration. */
static inline int wm_blur_rect(unsigned int *px, int w, int h, const wm_blur_config_t *cfg,
                               unsigned int *line)
{
    int p, x, y;
    if (px == 0 || line == 0 || w <= 0 || h <= 0 || !wm_blur_config_valid(cfg)) {
        return 0;
    }
    for (p = 0; p < cfg->passes; p++) {
        for (y = 0; y < h; y++) {
            wm_blur_line(px + (unsigned long)y * (unsigned long)w, 1L, w, cfg->radius, line);
        }
        for (x = 0; x < w; x++) {
            wm_blur_line(px + x, (long)w, h, cfg->radius, line);
        }
    }
    return 1;
}

#endif
