/** Docstring: Wobbly-window spring mesh contract for the MiniOS desktop.
 *
 * Single-file header-only contract owning the jelly physics the desktop
 * plays while a window is dragged and after it is dropped. A small grid of
 * nodes carries a displacement and a velocity in 24.8 fixed point; moving
 * the window kicks every node against the motion in proportion to its
 * distance from the grab point (the grab stays pinned, the far corners lag),
 * and a damped spring with neighbour coupling pulls the mesh home with a
 * visible overshoot. Sampling interpolates the grid bilinearly so the
 * renderer can ask for the displacement of any window pixel. Pure integer
 * logic over caller-owned state, so it stays host-testable; the kernel only
 * owns the window texture, the warp blit and the pacing. Every function
 * fails closed on null or degenerate input.
 */
#ifndef WM_JELLY_H
#define WM_JELLY_H

/** Docstring: Nodes per side of the mesh. */
#define WM_JELLY_GRID 4

/** Docstring: Fractional bits of a node displacement or velocity. */
#define WM_JELLY_FP 8

/** Docstring: Weight scale: 256 means the node lags the full motion. */
#define WM_JELLY_WEIGHT_ONE 256

/** Docstring: Centralized jelly tuning, no magic numbers. Stiffness,
 * coupling, damping and impulse are per-frame fractions of 256 (impulse is
 * the share of a window move handed to the nodes as velocity, which is what
 * keeps them swinging after the pointer stops); max_px clamps any
 * displacement; rest_disp and rest_vel (fixed point) bound the settle
 * verdict; max_frames caps a settle loop. */
typedef struct {
    int grid;
    int stiffness;
    int coupling;
    int damping;
    int impulse;
    int max_px;
    int rest_disp;
    int rest_vel;
    int max_frames;
} wm_jelly_config_t;

/** Docstring: Default feel: period near 18 frames, damping ratio near 0.25,
 * a move also launches the nodes at 43% of its speed, 64 px of reach, settled once under half a pixel and an eighth of a pixel
 * per frame. */
#define WM_JELLY_CONFIG_DEFAULT { WM_JELLY_GRID, 22, 38, 22, 170, 72, 128, 32, 220 }

/** Docstring: Mesh state: displacement and velocity per node, row-major. */
typedef struct {
    int dx[WM_JELLY_GRID * WM_JELLY_GRID];
    int dy[WM_JELLY_GRID * WM_JELLY_GRID];
    int vx[WM_JELLY_GRID * WM_JELLY_GRID];
    int vy[WM_JELLY_GRID * WM_JELLY_GRID];
} wm_jelly_t;

/** Docstring: Clamp v to plus or minus lim. */
static inline int wm_jelly_clamp(int v, int lim)
{
    if (v > lim) {
        return lim;
    }
    if (v < -lim) {
        return -lim;
    }
    return v;
}

/** Docstring: Absolute value. */
static inline int wm_jelly_abs(int v)
{
    return v < 0 ? -v : v;
}

/** Docstring: Zero the mesh: every node home, no velocity. */
static inline void wm_jelly_reset(wm_jelly_t *j)
{
    int i;
    if (j == 0) {
        return;
    }
    for (i = 0; i < WM_JELLY_GRID * WM_JELLY_GRID; i++) {
        j->dx[i] = 0;
        j->dy[i] = 0;
        j->vx[i] = 0;
        j->vy[i] = 0;
    }
}

/** Docstring: Lag weight of a node: its normalized distance from the grab
 * point (average of the two axes), 0 at the grab and 256 at the far corner. */
static inline int wm_jelly_weight(int px, int py, int gx, int gy, int w, int h)
{
    int ax = (wm_jelly_abs(px - gx) * WM_JELLY_WEIGHT_ONE) / w;
    int ay = (wm_jelly_abs(py - gy) * WM_JELLY_WEIGHT_ONE) / h;
    int d = (ax + ay) / 2;
    return d > WM_JELLY_WEIGHT_ONE ? WM_JELLY_WEIGHT_ONE : d;
}

/** Docstring: The window moved by (mx, my) pixels with the pointer holding
 * the window point (gx, gy) of a w x h window: shove every node against the
 * motion by its lag weight, then clamp to the configured reach. */
static inline void wm_jelly_kick(wm_jelly_t *j, const wm_jelly_config_t *cfg,
                                 int mx, int my, int gx, int gy, int w, int h)
{
    int r, c;
    int lim;
    if (j == 0 || cfg == 0 || w <= 0 || h <= 0 || cfg->grid != WM_JELLY_GRID) {
        return;
    }
    lim = cfg->max_px << WM_JELLY_FP;
    mx = wm_jelly_clamp(mx, cfg->max_px);
    my = wm_jelly_clamp(my, cfg->max_px);
    for (r = 0; r < WM_JELLY_GRID; r++) {
        for (c = 0; c < WM_JELLY_GRID; c++) {
            int i = r * WM_JELLY_GRID + c;
            int px = (c * (w - 1)) / (WM_JELLY_GRID - 1);
            int py = (r * (h - 1)) / (WM_JELLY_GRID - 1);
            int wt = wm_jelly_weight(px, py, gx, gy, w, h);
            j->dx[i] = wm_jelly_clamp(j->dx[i] - ((mx * wt) << WM_JELLY_FP) / WM_JELLY_WEIGHT_ONE, lim);
            j->dy[i] = wm_jelly_clamp(j->dy[i] - ((my * wt) << WM_JELLY_FP) / WM_JELLY_WEIGHT_ONE, lim);
            j->vx[i] -= ((((mx * wt) << WM_JELLY_FP) / WM_JELLY_WEIGHT_ONE) * cfg->impulse) / WM_JELLY_WEIGHT_ONE;
            j->vy[i] -= ((((my * wt) << WM_JELLY_FP) / WM_JELLY_WEIGHT_ONE) * cfg->impulse) / WM_JELLY_WEIGHT_ONE;
        }
    }
}

/** Docstring: Average of the in-grid neighbours of node (r, c) in one axis. */
static inline int wm_jelly_neighbours(const int *d, int r, int c)
{
    int sum = 0;
    int n = 0;
    if (r > 0) {
        sum += d[(r - 1) * WM_JELLY_GRID + c];
        n++;
    }
    if (r < WM_JELLY_GRID - 1) {
        sum += d[(r + 1) * WM_JELLY_GRID + c];
        n++;
    }
    if (c > 0) {
        sum += d[r * WM_JELLY_GRID + c - 1];
        n++;
    }
    if (c < WM_JELLY_GRID - 1) {
        sum += d[r * WM_JELLY_GRID + c + 1];
        n++;
    }
    return n ? sum / n : 0;
}

/** Docstring: Advance the mesh one frame: spring toward home, coupling
 * toward the neighbour average, velocity damping, semi-implicit Euler. */
static inline void wm_jelly_step(const wm_jelly_config_t *cfg, wm_jelly_t *j)
{
    int ax[WM_JELLY_GRID * WM_JELLY_GRID];
    int ay[WM_JELLY_GRID * WM_JELLY_GRID];
    int r, c, i;
    int lim;
    if (cfg == 0 || j == 0 || cfg->grid != WM_JELLY_GRID) {
        return;
    }
    lim = cfg->max_px << WM_JELLY_FP;
    for (r = 0; r < WM_JELLY_GRID; r++) {
        for (c = 0; c < WM_JELLY_GRID; c++) {
            i = r * WM_JELLY_GRID + c;
            ax[i] = (-cfg->stiffness * j->dx[i]
                     + cfg->coupling * (wm_jelly_neighbours(j->dx, r, c) - j->dx[i])
                     - cfg->damping * j->vx[i]) / WM_JELLY_WEIGHT_ONE;
            ay[i] = (-cfg->stiffness * j->dy[i]
                     + cfg->coupling * (wm_jelly_neighbours(j->dy, r, c) - j->dy[i])
                     - cfg->damping * j->vy[i]) / WM_JELLY_WEIGHT_ONE;
        }
    }
    for (i = 0; i < WM_JELLY_GRID * WM_JELLY_GRID; i++) {
        j->vx[i] += ax[i];
        j->vy[i] += ay[i];
        j->dx[i] = wm_jelly_clamp(j->dx[i] + j->vx[i], lim);
        j->dy[i] = wm_jelly_clamp(j->dy[i] + j->vy[i], lim);
    }
}

/** Docstring: 1 when every node is within the rest thresholds in both
 * displacement and velocity; null input reads as rest. */
static inline int wm_jelly_at_rest(const wm_jelly_config_t *cfg, const wm_jelly_t *j)
{
    int i;
    if (cfg == 0 || j == 0) {
        return 1;
    }
    for (i = 0; i < WM_JELLY_GRID * WM_JELLY_GRID; i++) {
        if (wm_jelly_abs(j->dx[i]) > cfg->rest_disp || wm_jelly_abs(j->dy[i]) > cfg->rest_disp ||
            wm_jelly_abs(j->vx[i]) > cfg->rest_vel || wm_jelly_abs(j->vy[i]) > cfg->rest_vel) {
            return 0;
        }
    }
    return 1;
}

/** Docstring: Displacement in whole pixels at window point (x, y) of a
 * w x h window, bilinear over the grid. Points outside clamp to the edge. */
static inline void wm_jelly_sample(const wm_jelly_t *j, int x, int y, int w, int h,
                                   int *ox, int *oy)
{
    int u, v, c, r, fu, fv, i;
    long ax, ay;
    if (ox) {
        *ox = 0;
    }
    if (oy) {
        *oy = 0;
    }
    if (j == 0 || ox == 0 || oy == 0 || w <= 1 || h <= 1) {
        return;
    }
    x = x < 0 ? 0 : (x > w - 1 ? w - 1 : x);
    y = y < 0 ? 0 : (y > h - 1 ? h - 1 : y);
    u = (x * (WM_JELLY_GRID - 1) * WM_JELLY_WEIGHT_ONE) / (w - 1);
    v = (y * (WM_JELLY_GRID - 1) * WM_JELLY_WEIGHT_ONE) / (h - 1);
    c = u / WM_JELLY_WEIGHT_ONE;
    r = v / WM_JELLY_WEIGHT_ONE;
    if (c > WM_JELLY_GRID - 2) {
        c = WM_JELLY_GRID - 2;
    }
    if (r > WM_JELLY_GRID - 2) {
        r = WM_JELLY_GRID - 2;
    }
    fu = u - c * WM_JELLY_WEIGHT_ONE;
    fv = v - r * WM_JELLY_WEIGHT_ONE;
    i = r * WM_JELLY_GRID + c;
    ax = ((long)j->dx[i] * (WM_JELLY_WEIGHT_ONE - fu) + (long)j->dx[i + 1] * fu) * (WM_JELLY_WEIGHT_ONE - fv)
       + ((long)j->dx[i + WM_JELLY_GRID] * (WM_JELLY_WEIGHT_ONE - fu) + (long)j->dx[i + WM_JELLY_GRID + 1] * fu) * fv;
    ay = ((long)j->dy[i] * (WM_JELLY_WEIGHT_ONE - fu) + (long)j->dy[i + 1] * fu) * (WM_JELLY_WEIGHT_ONE - fv)
       + ((long)j->dy[i + WM_JELLY_GRID] * (WM_JELLY_WEIGHT_ONE - fu) + (long)j->dy[i + WM_JELLY_GRID + 1] * fu) * fv;
    *ox = (int)((ax + (1L << (WM_JELLY_FP + 15))) >> (WM_JELLY_FP + 16));
    *oy = (int)((ay + (1L << (WM_JELLY_FP + 15))) >> (WM_JELLY_FP + 16));
}

#endif
