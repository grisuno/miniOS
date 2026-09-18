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

#endif
