/** Docstring: Tiling layout contract for the MiniOS desktop.
 *
 * Single-file header-only contract owning terminal cell layout. Given the
 * usable grid and which windows exist, it computes one cell per terminal
 * in character units so no caller hardcodes half splits or stack math.
 * Graphics placement stays in the kernel; this contract only reserves
 * its half by narrowing the terminals. All functions fail closed.
 */
#ifndef WM_TILING_H
#define WM_TILING_H

/** Docstring: Terminal cell in character units. */
typedef struct {
    int x;
    int y;
    int cols;
    int rows;
    int fullscreen;
} wm_tile_cell_t;

/** Docstring: Compute terminal cells for the current window set. */
static inline int wm_tile_layout(const int *present, int nterms, int gfx_active, int max_cols, int max_rows, wm_tile_cell_t *out, int cap)
{
    int hw;
    int ow;
    int top;
    int bot;
    int single;
    if (present == 0 || out == 0 || nterms <= 0 || cap <= 0) {
        return 0;
    }
    if (max_cols <= 0 || max_rows <= 0) {
        return 0;
    }
    single = (nterms < 2 || !present[1]) ? 1 : 0;
    hw = max_cols / 2;
    ow = max_cols - hw;
    top = max_rows / 2;
    bot = max_rows - top;
    if (single && gfx_active) {
        if (cap < 1) {
            return 0;
        }
        out[0].x = 0;
        out[0].y = 0;
        out[0].cols = hw;
        out[0].rows = max_rows;
        out[0].fullscreen = 0;
        return 1;
    }
    if (single) {
        if (cap < 1) {
            return 0;
        }
        out[0].x = 0;
        out[0].y = 0;
        out[0].cols = max_cols;
        out[0].rows = max_rows;
        out[0].fullscreen = 1;
        return 1;
    }
    if (gfx_active) {
        if (cap < 2) {
            return 0;
        }
        out[0].x = 0;
        out[0].y = 0;
        out[0].cols = hw;
        out[0].rows = top;
        out[0].fullscreen = 0;
        out[1].x = 0;
        out[1].y = top;
        out[1].cols = hw;
        out[1].rows = bot;
        out[1].fullscreen = 0;
        return 2;
    }
    if (cap < 2) {
        return 0;
    }
    out[0].x = 0;
    out[0].y = 0;
    out[0].cols = hw;
    out[0].rows = max_rows;
    out[0].fullscreen = 0;
    out[1].x = hw;
    out[1].y = 0;
    out[1].cols = ow;
    out[1].rows = max_rows;
    out[1].fullscreen = 0;
    return 2;
}

#endif
