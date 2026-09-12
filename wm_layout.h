/** Docstring: Unified layout contract for the MiniOS desktop.
 *
 * Single-file header-only contract owning every window placement decision.
 * Given a window list, a layout mode and the usable grid, it computes one
 * cell per window in character units so no caller hardcodes splits, stacks
 * or spiral math. Graphics placement stays in the kernel; this contract
 * only reserves grid space so terminals and graphics share one policy.
 * All functions are pure integer logic with no kernel dependencies and
 * fail closed on degenerate input.
 */
#ifndef WM_LAYOUT_H
#define WM_LAYOUT_H

/** Docstring: Layout modes sharing one compute entry point. */
typedef enum {
    WM_LAYOUT_TILE = 0,
    WM_LAYOUT_BSP = 1,
    WM_LAYOUT_CASCADE = 2,
    WM_LAYOUT_FIBONACCI = 3,
    WM_LAYOUT_FULLSCREEN = 4
} wm_layout_mode_t;

/** Docstring: Total layout modes in the mode table. */
#define WM_LAYOUT_MODE_COUNT 5

/** Docstring: One input window for layout computation. */
typedef struct {
    int kind;
    int id;
    int present;
    int min_cols;
    int min_rows;
} wm_layout_window_t;

/** Docstring: Centralized layout configuration for one engine. */
typedef struct {
    int gap;
    int cascade_dx;
    int cascade_dy;
    int fib_num;
    int fib_den;
} wm_layout_config_t;

/** Docstring: Default layout matching the legacy two terminal split. */
#define WM_LAYOUT_CONFIG_DEFAULT { 0, 4, 2, 618, 1000 }

/** Docstring: One computed cell in character units. */
typedef struct {
    int x;
    int y;
    int cols;
    int rows;
    int fullscreen;
} wm_layout_cell_t;

/** Docstring: Human name for one layout mode, else zero. */
static inline const char *wm_layout_mode_name(int mode)
{
    switch (mode) {
    case WM_LAYOUT_TILE:
        return "tile";
    case WM_LAYOUT_BSP:
        return "bsp";
    case WM_LAYOUT_CASCADE:
        return "cascade";
    case WM_LAYOUT_FIBONACCI:
        return "fibonacci";
    case WM_LAYOUT_FULLSCREEN:
        return "fullscreen";
    default:
        return 0;
    }
}

/** Docstring: True when mode is a selectable layout mode. */
static inline int wm_layout_mode_valid(int mode)
{
    return mode >= WM_LAYOUT_TILE && mode <= WM_LAYOUT_FULLSCREEN;
}

/** Docstring: Clamp cell extents into the grid, fail closed on nulls. */
static inline int wm_layout_clamp_cell(wm_layout_cell_t *cell, int max_cols, int max_rows)
{
    if (cell == 0) {
        return 0;
    }
    if (max_cols <= 0 || max_rows <= 0) {
        return 0;
    }
    if (cell->x < 0) {
        cell->x = 0;
    }
    if (cell->y < 0) {
        cell->y = 0;
    }
    if (cell->x >= max_cols) {
        cell->x = max_cols - 1;
    }
    if (cell->y >= max_rows) {
        cell->y = max_rows - 1;
    }
    if (cell->cols < 1) {
        cell->cols = 1;
    }
    if (cell->rows < 1) {
        cell->rows = 1;
    }
    if (cell->x + cell->cols > max_cols) {
        cell->cols = max_cols - cell->x;
    }
    if (cell->y + cell->rows > max_rows) {
        cell->rows = max_rows - cell->y;
    }
    return cell->cols > 0 && cell->rows > 0;
}

/** Docstring: Full grid cell for the focused window. */
static inline int wm_layout_fullscreen_cell(int max_cols, int max_rows, wm_layout_cell_t *out)
{
    if (out == 0) {
        return 0;
    }
    if (max_cols <= 0 || max_rows <= 0) {
        return 0;
    }
    out->x = 0;
    out->y = 0;
    out->cols = max_cols;
    out->rows = max_rows;
    out->fullscreen = 1;
    return 1;
}

/** Docstring: Tile split across the long axis, legacy dual split exactly. */
static inline int wm_layout_compute_tile(const wm_layout_window_t *wins, int nwin, int max_cols, int max_rows, wm_layout_cell_t *out, int cap)
{
    int i;
    int base;
    int rem;
    if (wins == 0 || out == 0 || nwin <= 0 || cap <= 0) {
        return 0;
    }
    if (max_cols <= 0 || max_rows <= 0) {
        return 0;
    }
    if (cap < nwin) {
        return 0;
    }
    if (nwin == 1) {
        out[0].x = 0;
        out[0].y = 0;
        out[0].cols = max_cols;
        out[0].rows = max_rows;
        out[0].fullscreen = 1;
        return 1;
    }
    if (max_cols >= max_rows) {
        base = max_cols / nwin;
        rem = max_cols - base * nwin;
        for (i = 0; i < nwin; i++) {
            out[i].x = i * base;
            out[i].y = 0;
            out[i].cols = base + ((i == nwin - 1) ? rem : 0);
            out[i].rows = max_rows;
            out[i].fullscreen = 0;
        }
        return nwin;
    }
    base = max_rows / nwin;
    rem = max_rows - base * nwin;
    for (i = 0; i < nwin; i++) {
        out[i].x = 0;
        out[i].y = i * base;
        out[i].cols = max_cols;
        out[i].rows = base + ((i == nwin - 1) ? rem : 0);
        out[i].fullscreen = 0;
    }
    return nwin;
}

/** Docstring: Recursive binary splits alternating axes, bspwm feel. */
static inline int wm_layout_compute_bsp(const wm_layout_window_t *wins, int nwin, int max_cols, int max_rows, wm_layout_cell_t *out, int cap)
{
    int rx;
    int ry;
    int rw;
    int rh;
    int i;
    int half;
    if (wins == 0 || out == 0 || nwin <= 0 || cap <= 0) {
        return 0;
    }
    if (max_cols <= 0 || max_rows <= 0) {
        return 0;
    }
    if (cap < nwin) {
        return 0;
    }
    rx = 0;
    ry = 0;
    rw = max_cols;
    rh = max_rows;
    for (i = 0; i < nwin; i++) {
        int last = (i == nwin - 1);
        int vertical = ((rw >= rh) ? 1 : 0);
        if (last) {
            out[i].x = rx;
            out[i].y = ry;
            out[i].cols = rw;
            out[i].rows = rh;
            out[i].fullscreen = (nwin == 1) ? 1 : 0;
            break;
        }
        if (vertical) {
            half = rw / 2;
            if (half < 1) {
                half = 1;
            }
            if (half >= rw) {
                half = rw - 1;
            }
            out[i].x = rx;
            out[i].y = ry;
            out[i].cols = half;
            out[i].rows = rh;
            out[i].fullscreen = 0;
            rx = rx + half;
            rw = rw - half;
        } else {
            half = rh / 2;
            if (half < 1) {
                half = 1;
            }
            if (half >= rh) {
                half = rh - 1;
            }
            out[i].x = rx;
            out[i].y = ry;
            out[i].cols = rw;
            out[i].rows = half;
            out[i].fullscreen = 0;
            ry = ry + half;
            rh = rh - half;
        }
    }
    return nwin;
}

/** Docstring: Cascaded offsets so every title stays visible. */
static inline int wm_layout_compute_cascade(const wm_layout_config_t *cfg, const wm_layout_window_t *wins, int nwin, int max_cols, int max_rows, wm_layout_cell_t *out, int cap)
{
    int dx;
    int dy;
    int i;
    if (cfg == 0 || wins == 0 || out == 0 || nwin <= 0 || cap <= 0) {
        return 0;
    }
    if (max_cols <= 0 || max_rows <= 0) {
        return 0;
    }
    if (cap < nwin) {
        return 0;
    }
    dx = (cfg->cascade_dx > 0) ? cfg->cascade_dx : 4;
    dy = (cfg->cascade_dy > 0) ? cfg->cascade_dy : 2;
    for (i = 0; i < nwin; i++) {
        int ox = (i * dx) % (max_cols / 2 + 1);
        int oy = (i * dy) % (max_rows / 2 + 1);
        out[i].x = ox;
        out[i].y = oy;
        out[i].cols = max_cols - ox;
        out[i].rows = max_rows - oy;
        out[i].fullscreen = 0;
        if (out[i].cols < 1) {
            out[i].cols = 1;
        }
        if (out[i].rows < 1) {
            out[i].rows = 1;
        }
    }
    return nwin;
}

/** Docstring: Fibonacci spiral carving integer ratio strips. */
static inline int wm_layout_compute_fibonacci(const wm_layout_config_t *cfg, const wm_layout_window_t *wins, int nwin, int max_cols, int max_rows, wm_layout_cell_t *out, int cap)
{
    int rx;
    int ry;
    int rw;
    int rh;
    int num;
    int den;
    int i;
    if (cfg == 0 || wins == 0 || out == 0 || nwin <= 0 || cap <= 0) {
        return 0;
    }
    if (max_cols <= 0 || max_rows <= 0) {
        return 0;
    }
    if (cap < nwin) {
        return 0;
    }
    num = (cfg->fib_num > 0) ? cfg->fib_num : 618;
    den = (cfg->fib_den > 0) ? cfg->fib_den : 1000;
    if (num <= 0 || num >= den) {
        num = 618;
        den = 1000;
    }
    rx = 0;
    ry = 0;
    rw = max_cols;
    rh = max_rows;
    for (i = 0; i < nwin; i++) {
        int last = (i == nwin - 1);
        int vertical = ((i % 2) == 0) ? ((rw >= rh) ? 1 : 0) : ((rh > rw) ? 1 : 0);
        int cut;
        if (last) {
            out[i].x = rx;
            out[i].y = ry;
            out[i].cols = rw;
            out[i].rows = rh;
            out[i].fullscreen = (nwin == 1) ? 1 : 0;
            break;
        }
        if (vertical) {
            cut = (rw * num) / den;
            if (cut < 1) {
                cut = 1;
            }
            if (cut >= rw) {
                cut = rw - 1;
            }
            out[i].x = rx;
            out[i].y = ry;
            out[i].cols = cut;
            out[i].rows = rh;
            out[i].fullscreen = 0;
            rx = rx + cut;
            rw = rw - cut;
        } else {
            cut = (rh * num) / den;
            if (cut < 1) {
                cut = 1;
            }
            if (cut >= rh) {
                cut = rh - 1;
            }
            out[i].x = rx;
            out[i].y = ry;
            out[i].cols = rw;
            out[i].rows = cut;
            out[i].fullscreen = 0;
            ry = ry + cut;
            rh = rh - cut;
        }
    }
    return nwin;
}

/** Docstring: Compute one cell per present window in input order. */
static inline int wm_layout_compute(const wm_layout_config_t *cfg, const wm_layout_window_t *wins, int nwin, int mode, int focus, int max_cols, int max_rows, wm_layout_cell_t *out, int cap)
{
    int i;
    int n;
    wm_layout_window_t compact[8];
    wm_layout_cell_t cells[8];
    int nc = 0;
    int at = -1;
    if (wins == 0 || out == 0 || nwin <= 0 || cap <= 0) {
        return 0;
    }
    if (max_cols <= 0 || max_rows <= 0) {
        return 0;
    }
    if (!wm_layout_mode_valid(mode)) {
        return 0;
    }
    for (i = 0; i < nwin && nc < 8; i++) {
        if (wins[i].present) {
            compact[nc] = wins[i];
            if (wins[i].id == focus) {
                at = nc;
            }
            nc++;
        }
    }
    if (nc <= 0) {
        return 0;
    }
    if (cap < nc) {
        return 0;
    }
    if (mode == WM_LAYOUT_FULLSCREEN) {
        if (at < 0) {
            at = 0;
        }
        for (i = 0; i < nc; i++) {
            if (i == at) {
                cells[i].x = 0;
                cells[i].y = 0;
                cells[i].cols = max_cols;
                cells[i].rows = max_rows;
                cells[i].fullscreen = 1;
            } else {
                cells[i].x = 0;
                cells[i].y = 0;
                cells[i].cols = 0;
                cells[i].rows = 0;
                cells[i].fullscreen = 0;
            }
        }
        for (i = 0; i < nc; i++) {
            out[i] = cells[i];
        }
        return nc;
    }
    if (mode == WM_LAYOUT_BSP) {
        n = wm_layout_compute_bsp(compact, nc, max_cols, max_rows, cells, 8);
    } else if (mode == WM_LAYOUT_CASCADE) {
        wm_layout_config_t dcfg = WM_LAYOUT_CONFIG_DEFAULT;
        const wm_layout_config_t *use = (cfg != 0) ? cfg : &dcfg;
        n = wm_layout_compute_cascade(use, compact, nc, max_cols, max_rows, cells, 8);
    } else if (mode == WM_LAYOUT_FIBONACCI) {
        wm_layout_config_t dcfg = WM_LAYOUT_CONFIG_DEFAULT;
        const wm_layout_config_t *use = (cfg != 0) ? cfg : &dcfg;
        n = wm_layout_compute_fibonacci(use, compact, nc, max_cols, max_rows, cells, 8);
    } else {
        n = wm_layout_compute_tile(compact, nc, max_cols, max_rows, cells, 8);
    }
    if (n != nc) {
        return 0;
    }
    for (i = 0; i < nc; i++) {
        if (!wm_layout_clamp_cell(&cells[i], max_cols, max_rows)) {
            return 0;
        }
        out[i] = cells[i];
    }
    return nc;
}

/** Docstring: True when two plans cover identical cells in order. */
static inline int wm_layout_same(const wm_layout_cell_t *a, const wm_layout_cell_t *b, int n)
{
    int i;
    if (n <= 0) {
        return 1;
    }
    if (a == 0 || b == 0) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        if (a[i].x != b[i].x) {
            return 0;
        }
        if (a[i].y != b[i].y) {
            return 0;
        }
        if (a[i].cols != b[i].cols) {
            return 0;
        }
        if (a[i].rows != b[i].rows) {
            return 0;
        }
        if (a[i].fullscreen != b[i].fullscreen) {
            return 0;
        }
    }
    return 1;
}

#endif
