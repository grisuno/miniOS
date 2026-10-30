/** Docstring: DOOM-melt desktop effect contract for MiniOS.
 *
 * Single-file header-only contract owning the melt transition logic the
 * desktop plays when windows appear or disappear and on first boot. The
 * algorithm mirrors progs/doomgeneric/f_wipe.c wipe_initMelt/wipe_doMelt:
 * per-column fronts start with staggered negative delays, then scroll the
 * new frame down over the old one column by column. Pure integer logic
 * over caller-owned arrays, so it stays host-testable; the kernel keeps
 * owning the framebuffer, heap and pacing and only consumes the fronts.
 * All functions fail closed on degenerate input.
 */
#ifndef VGA_FX_H
#define VGA_FX_H

/** Docstring: Centralized effect configuration, no magic numbers. */
typedef struct {
    int step_px;
    int frame_ms;
    int max_delay;
    unsigned long seed;
} vga_fx_config_t;

/** Docstring: Default melt pacing: 8 px per frame, 8 ms per frame. */
#define VGA_FX_CONFIG_DEFAULT { 8, 8, 16, 0x1F2E3D4CUL }

/** Docstring: Widest transition the column array can describe. */
#define VGA_FX_COLS_MAX 1024

/** Docstring: One xorshift32 step, the melt's deterministic PRNG. */
static inline unsigned long vga_fx_rand(unsigned long *s)
{
    unsigned long x;
    if (s == 0) {
        return 1;
    }
    x = *s;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    *s = x;
    return x ? x : 1;
}

/** Docstring: Seed consecutive column fronts with staggered delays.
 * Mirrors f_wipe.c: first column waits a random 0..15 frames, each next
 * column drifts by -1..+1, clamped at zero, -16 repaired to -15. */
static inline int vga_fx_init_cols(const vga_fx_config_t *cfg, int *cols, int w)
{
    int i;
    int r;
    unsigned long s;
    if (cfg == 0 || cols == 0 || w <= 0 || w > VGA_FX_COLS_MAX) {
        return -1;
    }
    s = cfg->seed ? cfg->seed : 1;
    cols[0] = -((int)(vga_fx_rand(&s) % (unsigned long)cfg->max_delay));
    for (i = 1; i < w; i++) {
        r = ((int)(vga_fx_rand(&s) % 3UL)) - 1;
        cols[i] = cols[i - 1] + r;
        if (cols[i] > 0) {
            cols[i] = 0;
        } else if (cols[i] == -cfg->max_delay) {
            cols[i] = -cfg->max_delay + 1;
        }
    }
    return 0;
}

/** Docstring: Advance every column front one melt frame.
 * Returns 1 when every front reached the rect bottom, 0 otherwise. */
static inline int vga_fx_advance(const vga_fx_config_t *cfg, int *cols, int w, int h)
{
    int i;
    int done = 1;
    int step;
    if (cfg == 0 || cols == 0 || w <= 0 || h <= 0) {
        return 1;
    }
    step = (cfg->step_px > 0) ? cfg->step_px : 8;
    for (i = 0; i < w; i++) {
        if (cols[i] < 0) {
            cols[i]++;
            done = 0;
        } else if (cols[i] < h) {
            int dy = (cols[i] < 16) ? cols[i] + 1 : step;
            cols[i] += dy;
            if (cols[i] > h) {
                cols[i] = h;
            }
            done = 0;
        }
    }
    return done;
}

/** Docstring: Rows [0, front) of one column already show the new frame. */
static inline int vga_fx_front(int col_y, int h)
{
    if (col_y < 0) {
        return 0;
    }
    if (col_y > h) {
        return h;
    }
    return col_y;
}

/** Docstring: Clamp a transition rect inside the framebuffer. */
static inline int vga_fx_clamp_rect(int *x, int *y, int *w, int *h, int fb_w, int fb_h)
{
    if (x == 0 || y == 0 || w == 0 || h == 0) {
        return -1;
    }
    if (*x < 0) {
        *w += *x;
        *x = 0;
    }
    if (*y < 0) {
        *h += *y;
        *y = 0;
    }
    if (*x + *w > fb_w) {
        *w = fb_w - *x;
    }
    if (*y + *h > fb_h) {
        *h = fb_h - *y;
    }
    if (*w <= 0 || *h <= 0 || *w > VGA_FX_COLS_MAX) {
        return -1;
    }
    return 0;
}

/** Docstring: Fixed-point scale of every effect progress value: 0 is the
 * first frame, VGA_FX_PROG_ONE the last. */
#define VGA_FX_PROG_ONE 1024

/** Docstring: Pacing of the burn and genie drivers, one paint per this many
 * milliseconds at most. */
#define VGA_FX_FRAME_MS 12

/** Docstring: Burn flame colour stops are spaced this far apart in heat. */
#define VGA_FX_HEAT_STEP 64

/** Docstring: Highest flame heat. */
#define VGA_FX_HEAT_MAX 255

/** Docstring: Fire (window close) and genie (minimize/restore) tuning, no
 * magic numbers. Burn: duration, how far the front climbs, the noise
 * jitter added to each pixel's ignition time, the flame thickness, the
 * glow reach ahead of the front, the ember heat of that glow, and the
 * noise cell sizes (coarse blobs and fine grain). Genie: duration, how long
 * the top rows wait for the bottom ones (the lag that bends the shape) and
 * the width the window narrows to at the taskbar button. */
typedef struct {
    int burn_ms;
    int burn_rise;
    int burn_jitter;
    int burn_band;
    int burn_glow;
    int burn_ember;
    int burn_cell_coarse;
    int burn_cell_fine;
    int genie_ms;
    int genie_lag;
    int genie_min_w;
    unsigned long seed;
} vga_fx_motion_t;

/** Docstring: Default feel: a 700 ms fire climbing 560 units with 220 of
 * noise and 244 of flame (they add up to VGA_FX_PROG_ONE), a 420 ms genie
 * whose top rows trail by 600 units and narrow to 28 px. */
#define VGA_FX_MOTION_DEFAULT { 700, 560, 220, 244, 90, 110, 14, 5, 420, 600, 28, 0x5EED1E55UL }

/** Docstring: Integer smoothstep of q in [0, PROG_ONE]: slow start, slow
 * end, the ease every genie row follows. */
static inline int vga_fx_smooth(int q)
{
    long v;
    if (q <= 0) {
        return 0;
    }
    if (q >= VGA_FX_PROG_ONE) {
        return VGA_FX_PROG_ONE;
    }
    v = (long)q * (long)q * (3L * VGA_FX_PROG_ONE - 2L * (long)q);
    return (int)(v / ((long)VGA_FX_PROG_ONE * (long)VGA_FX_PROG_ONE));
}

/** Docstring: Deterministic 32-bit hash of a lattice point and a seed. */
static inline unsigned long vga_fx_hash2(int x, int y, unsigned long seed)
{
    unsigned long h = (seed ^ ((unsigned long)x * 0x9E3779B1UL) ^ ((unsigned long)y * 0x85EBCA77UL)) & 0xFFFFFFFFUL;
    h ^= h >> 15;
    h = (h * 0x2C1B3C6DUL) & 0xFFFFFFFFUL;
    h ^= h >> 12;
    h = (h * 0x297A2D39UL) & 0xFFFFFFFFUL;
    h ^= h >> 15;
    return h & 0xFFFFFFFFUL;
}

/** Docstring: Bilinear value noise in [0, 255] over cells of `cell` pixels
 * (x and y non-negative). Fails closed to 0 on a degenerate cell. */
static inline int vga_fx_noise(int x, int y, int cell, unsigned long seed)
{
    int cx, cy, fx, fy;
    int a, b, c, d, top, bot, v;
    if (cell <= 0 || x < 0 || y < 0) {
        return 0;
    }
    cx = x / cell;
    cy = y / cell;
    fx = ((x % cell) * 256) / cell;
    fy = ((y % cell) * 256) / cell;
    a = (int)(vga_fx_hash2(cx, cy, seed) & 255UL);
    b = (int)(vga_fx_hash2(cx + 1, cy, seed) & 255UL);
    c = (int)(vga_fx_hash2(cx, cy + 1, seed) & 255UL);
    d = (int)(vga_fx_hash2(cx + 1, cy + 1, seed) & 255UL);
    top = a + ((b - a) * fx) / 256;
    bot = c + ((d - c) * fx) / 256;
    v = top + ((bot - top) * fy) / 256;
    if (v < 0) {
        return 0;
    }
    return v > 255 ? 255 : v;
}

/** Docstring: Total progress the burn runs over: the climb, the noise
 * spread and the flame thickness. */
static inline int vga_fx_burn_span(const vga_fx_motion_t *cfg)
{
    if (cfg == 0) {
        return VGA_FX_PROG_ONE;
    }
    return cfg->burn_rise + cfg->burn_jitter + cfg->burn_band;
}

/** Docstring: Ignition time of window pixel (lx, ly) of a w x h window:
 * the bottom ignites first and the front climbs, bent by coarse noise into
 * blobs and by fine noise into ragged tongues. Fails closed to 0. */
static inline int vga_fx_burn_threshold(const vga_fx_motion_t *cfg, int lx, int ly, int w, int h)
{
    int rise, coarse, fine, n;
    if (cfg == 0 || w <= 0 || h <= 0 || lx < 0 || ly < 0 || lx >= w || ly >= h) {
        return 0;
    }
    rise = ((h - 1 - ly) * cfg->burn_rise) / h;
    coarse = vga_fx_noise(lx, ly, cfg->burn_cell_coarse, cfg->seed);
    fine = vga_fx_noise(lx, ly, cfg->burn_cell_fine, cfg->seed ^ 0xA5A5A5A5UL);
    n = (coarse * 3 + fine) / 4;
    return rise + (n * cfg->burn_jitter) / 255;
}

/** Docstring: What one pixel shows at progress `prog` given its ignition
 * time: *heat is the flame overlay strength (0 none, up to HEAT_MAX) and
 * the return value picks the pixel underneath, 0 the old frame, 1 the new
 * one. Ahead of the front an ember glow tints the old pixel; the flame
 * ramps up to its peak a quarter of the way through the band, where the
 * base switches to the new frame under full cover, then cools to nothing. */
static inline int vga_fx_burn_pixel(const vga_fx_motion_t *cfg, int thr, int prog, int *heat)
{
    int d, peak;
    if (cfg == 0 || heat == 0) {
        return 1;
    }
    d = prog - thr;
    peak = cfg->burn_band / 4;
    *heat = 0;
    if (d < -cfg->burn_glow) {
        return 0;
    }
    if (d < 0) {
        *heat = ((d + cfg->burn_glow) * cfg->burn_ember) / cfg->burn_glow;
        return 0;
    }
    if (d < peak) {
        *heat = cfg->burn_ember + ((VGA_FX_HEAT_MAX - cfg->burn_ember) * d) / (peak > 0 ? peak : 1);
        return 0;
    }
    if (d < cfg->burn_band) {
        *heat = (VGA_FX_HEAT_MAX * (cfg->burn_band - d)) / (cfg->burn_band - peak);
        return 1;
    }
    return 1;
}

/** Docstring: Flame colour (0x00RRGGBB) of a heat: dark red embers up
 * through red, orange and yellow to a white-hot core. */
static inline unsigned int vga_fx_fire_color(int heat)
{
    static const unsigned char stops[5][3] = {
        { 60, 0, 0 }, { 200, 30, 0 }, { 255, 120, 0 }, { 255, 210, 40 }, { 255, 255, 210 }
    };
    int seg, t, i;
    unsigned int out = 0;
    if (heat < 0) {
        heat = 0;
    }
    if (heat > VGA_FX_HEAT_MAX) {
        heat = VGA_FX_HEAT_MAX;
    }
    seg = heat / VGA_FX_HEAT_STEP;
    if (seg > 3) {
        seg = 3;
    }
    t = ((heat - seg * VGA_FX_HEAT_STEP) * 256) / VGA_FX_HEAT_STEP;
    if (t > 256) {
        t = 256;
    }
    for (i = 0; i < 3; i++) {
        int a = stops[seg][i];
        int b = stops[seg + 1][i];
        out = (out << 8) | (unsigned int)(a + ((b - a) * t) / 256);
    }
    return out;
}

/** Docstring: Blend two 0x00RRGGBB pixels: alpha 0 keeps a, 255 gives b. */
static inline unsigned int vga_fx_mix(unsigned int a, unsigned int b, int alpha)
{
    unsigned int out = 0;
    int sh;
    if (alpha <= 0) {
        return a & 0x00FFFFFFu;
    }
    if (alpha >= 255) {
        return b & 0x00FFFFFFu;
    }
    for (sh = 16; sh >= 0; sh -= 8) {
        int ca = (int)((a >> sh) & 255u);
        int cb = (int)((b >> sh) & 255u);
        out = (out << 8) | (unsigned int)(ca + ((cb - ca) * alpha) / 255);
    }
    return out;
}

/** Docstring: Final pixel of a burn: the base frame pixel under the flame
 * overlay, whose opacity grows with the square of the heat so the glow is
 * a faint tint and the front is opaque. */
static inline unsigned int vga_fx_burn_compose(unsigned int base, int heat)
{
    int alpha;
    if (heat <= 0) {
        return base & 0x00FFFFFFu;
    }
    alpha = (heat * heat) / VGA_FX_HEAT_MAX;
    return vga_fx_mix(base, vga_fx_fire_color(heat), alpha);
}

/** Docstring: Where source row r of a wx,wy,ww x wh window sits at progress
 * `prog` while it is sucked into the point (tx, ty): its screen row, left
 * edge and width. The bottom row leaves first and each higher row waits
 * longer (the lag), every row follows the same smoothstep toward the
 * target and narrows to genie_min_w, so the window bends into a funnel.
 * ty is held at or below the window's last row, which keeps the row order
 * monotonic and so the funnel gap-free. Fails closed to the unmoved row. */
static inline int vga_fx_genie_row(const vga_fx_motion_t *cfg, int wx, int wy, int ww, int wh,
                                   int tx, int ty, int r, int prog,
                                   int *dy, int *left, int *width)
{
    long s, delay, q, e, yr, minw, wd, cx0, cx;
    if (cfg == 0 || dy == 0 || left == 0 || width == 0 || ww <= 0 || wh <= 0 || r < 0 || r >= wh) {
        return -1;
    }
    if (ty < wy + wh - 1) {
        ty = wy + wh - 1;
    }
    if (prog < 0) {
        prog = 0;
    }
    if (prog > VGA_FX_PROG_ONE) {
        prog = VGA_FX_PROG_ONE;
    }
    s = ((long)prog * (VGA_FX_PROG_ONE + (long)cfg->genie_lag)) / VGA_FX_PROG_ONE;
    delay = ((long)cfg->genie_lag * (long)(wh - 1 - r)) / wh;
    q = s - delay;
    e = vga_fx_smooth((int)(q < 0 ? 0 : (q > VGA_FX_PROG_ONE ? VGA_FX_PROG_ONE : q)));
    yr = (long)wy + r;
    *dy = (int)(yr + ((long)ty - yr) * e / VGA_FX_PROG_ONE);
    minw = cfg->genie_min_w < ww ? cfg->genie_min_w : ww;
    if (minw < 1) {
        minw = 1;
    }
    wd = ww + (minw - ww) * e / VGA_FX_PROG_ONE;
    cx0 = (long)wx + ww / 2;
    cx = cx0 + ((long)tx - cx0) * e / VGA_FX_PROG_ONE;
    *width = (int)wd;
    *left = (int)(cx - wd / 2);
    return 0;
}

#endif
