/** Docstring: Dock magnification math for the MiniOS desktop.
 *
 * Single-file header-only contract owning the integer arithmetic behind
 * the fluid dock: the bell curve that sizes every icon from its distance
 * to the pointer, the timed level that eases the whole bell in and out,
 * and the filtered sampler that scales an RGBA icon without the blocky
 * steps of nearest neighbour. Every function is pure over its arguments
 * and host-testable; the kernel owns the icons and the framebuffer.
 *
 * Usage: build a wm_dock_config_t once, derive the level from the ticks
 * since the pointer entered or left the dock (wm_dock_level), size each
 * icon with wm_dock_mag_size and paint it through wm_dock_sample.
 * Failure modes: every function fails closed (base size, level kept,
 * transparent sample) on degenerate input and never overflows for the
 * documented bounds.
 */
#ifndef WM_DOCK_H
#define WM_DOCK_H

/** Docstring: Full magnification level; 0 is a flat dock. */
#define WM_DOCK_LEVEL_ONE 256

/** Docstring: Largest reach in pixels; keeps reach^4 times the size span
 * inside 63 bits. */
#define WM_DOCK_REACH_MAX 4096

/** Docstring: Largest icon size in pixels the curve may produce. */
#define WM_DOCK_SIZE_MAX 1024

/** Docstring: One source texel in the sampler's 8.8 fixed point. */
#define WM_DOCK_FRAC_ONE 256

/** Docstring: Fully opaque alpha. */
#define WM_DOCK_ALPHA_OPAQUE 255

/** Docstring: Centralized magnification configuration, no magic numbers:
 * resting size, size under the pointer, and the distance at which an
 * icon is back to its resting size. */
typedef struct {
    int base;
    int peak;
    int reach;
} wm_dock_config_t;

/** Docstring: Absolute value of an int without overflow on the minimum. */
static inline long wm_dock_abs(long v)
{
    return v < 0 ? -v : v;
}

/** Docstring: Clamp a level to 0..WM_DOCK_LEVEL_ONE. */
static inline int wm_dock_level_clamp(long level)
{
    return level < 0 ? 0 : (level > WM_DOCK_LEVEL_ONE ? WM_DOCK_LEVEL_ONE : (int)level);
}

/** Docstring: Magnification level after elapsed ticks of a ramp that
 * started at from: rising toward WM_DOCK_LEVEL_ONE or falling toward 0,
 * linear over duration ticks for the full span. A non-positive duration
 * jumps to the target. */
static inline int wm_dock_level(int from, int rising, unsigned long elapsed,
                                unsigned long duration)
{
    long step;
    from = wm_dock_level_clamp(from);
    if (duration == 0 || elapsed >= duration) {
        return rising ? WM_DOCK_LEVEL_ONE : 0;
    }
    step = (long)((elapsed * (unsigned long)WM_DOCK_LEVEL_ONE) / duration);
    return wm_dock_level_clamp(rising ? (long)from + step : (long)from - step);
}

/** Docstring: Size of an icon whose centre lies dist pixels from the
 * pointer, at the given level. The bell is (1 - t^2)^2 with t = dist /
 * reach: peak under the pointer, base at the reach and beyond, smooth at
 * both ends, symmetric in the sign of dist. The level scales the growth
 * linearly. Returns base on a degenerate configuration, 0 on a null one. */
static inline int wm_dock_mag_size(const wm_dock_config_t *cfg, long dist, int level)
{
    long d, r, u, span, grow;
    if (cfg == 0 || cfg->base <= 0) {
        return 0;
    }
    if (cfg->peak <= cfg->base || cfg->peak > WM_DOCK_SIZE_MAX || cfg->reach <= 0 ||
        cfg->reach > WM_DOCK_REACH_MAX) {
        return cfg->base;
    }
    d = wm_dock_abs(dist);
    r = cfg->reach;
    if (d >= r) {
        return cfg->base;
    }
    u = r * r - d * d;
    span = cfg->peak - cfg->base;
    grow = (span * u * u + (r * r * r * r) / 2) / (r * r * r * r);
    return cfg->base + (int)((grow * wm_dock_level_clamp(level) + WM_DOCK_LEVEL_ONE / 2) /
                             WM_DOCK_LEVEL_ONE);
}

/** Docstring: Source coordinate, in 8.8 fixed point, that destination
 * pixel o of a d-pixel span maps to in an s-texel span. Pixel centres
 * are aligned, so a 1:1 scale maps every pixel onto its own texel, and
 * the result is clamped to the first and last texel centre. */
static inline long wm_dock_src_coord(int o, int d, int s)
{
    long u, last;
    if (d <= 0 || s <= 0) {
        return 0;
    }
    u = ((2L * o + 1L) * s * WM_DOCK_FRAC_ONE) / (2L * d) - WM_DOCK_FRAC_ONE / 2;
    last = (long)(s - 1) * WM_DOCK_FRAC_ONE;
    return u < 0 ? 0 : (u > last ? last : u);
}

/** Docstring: Bilinear sample of destination pixel (ox,oy) of an sw by
 * sh RGBA source scaled to dw by dh. Colours are weighted by alpha, so a
 * transparent texel never darkens the edge of an opaque one. Returns the
 * packed 0x00RRGGBB colour and stores the coverage 0..255 in alpha; a
 * degenerate call returns 0 with alpha 0. */
static inline unsigned long wm_dock_sample(const unsigned char *rgba, int sw, int sh,
                                           int dw, int dh, int ox, int oy, int *alpha)
{
    long u, v, fx, fy;
    int x0, y0, x1, y1, k;
    const unsigned char *t[4];
    unsigned long w[4];
    unsigned long wa = 0, r = 0, g = 0, b = 0, a;
    if (alpha != 0) {
        *alpha = 0;
    }
    if (rgba == 0 || alpha == 0 || sw <= 0 || sh <= 0 || dw <= 0 || dh <= 0 ||
        ox < 0 || oy < 0 || ox >= dw || oy >= dh) {
        return 0;
    }
    u = wm_dock_src_coord(ox, dw, sw);
    v = wm_dock_src_coord(oy, dh, sh);
    x0 = (int)(u / WM_DOCK_FRAC_ONE);
    y0 = (int)(v / WM_DOCK_FRAC_ONE);
    fx = u % WM_DOCK_FRAC_ONE;
    fy = v % WM_DOCK_FRAC_ONE;
    x1 = x0 + 1 < sw ? x0 + 1 : x0;
    y1 = y0 + 1 < sh ? y0 + 1 : y0;
    t[0] = rgba + ((long)y0 * sw + x0) * 4;
    t[1] = rgba + ((long)y0 * sw + x1) * 4;
    t[2] = rgba + ((long)y1 * sw + x0) * 4;
    t[3] = rgba + ((long)y1 * sw + x1) * 4;
    w[0] = (unsigned long)((WM_DOCK_FRAC_ONE - fx) * (WM_DOCK_FRAC_ONE - fy));
    w[1] = (unsigned long)(fx * (WM_DOCK_FRAC_ONE - fy));
    w[2] = (unsigned long)((WM_DOCK_FRAC_ONE - fx) * fy);
    w[3] = (unsigned long)(fx * fy);
    for (k = 0; k < 4; k++) {
        unsigned long m = w[k] * t[k][3];
        wa += m;
        r += m * t[k][0];
        g += m * t[k][1];
        b += m * t[k][2];
    }
    if (wa == 0) {
        return 0;
    }
    a = (wa + (unsigned long)(WM_DOCK_FRAC_ONE * WM_DOCK_FRAC_ONE) / 2) /
        (unsigned long)(WM_DOCK_FRAC_ONE * WM_DOCK_FRAC_ONE);
    *alpha = (int)(a > WM_DOCK_ALPHA_OPAQUE ? WM_DOCK_ALPHA_OPAQUE : a);
    r = (r + wa / 2) / wa;
    g = (g + wa / 2) / wa;
    b = (b + wa / 2) / wa;
    return (r << 16) | (g << 8) | b;
}

#endif
