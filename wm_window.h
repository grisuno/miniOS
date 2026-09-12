/** Docstring: Unified window contract for the MiniOS desktop.
 *
 * Single-file header-only contract replacing the terminal versus graphics
 * special cases in the window manager. Every window is one wm_window_t
 * with a kind tag; hit testing, title testing and focus rotation are pure
 * integer functions over that model so they stay host-testable without
 * kernel dependencies. Geometry delegates to wm_geom so no dimension is
 * hardcoded here. All functions fail closed on invalid windows.
 */
#ifndef WM_WINDOW_H
#define WM_WINDOW_H

#include "wm_geom.h"

/** Docstring: Window kinds sharing one focus space. */
typedef enum {
    WM_WIN_NONE = 0,
    WM_WIN_TERMINAL = 1,
    WM_WIN_GRAPHICS = 2
} wm_window_kind_t;

/** Docstring: Focus id for the graphics window in the shared focus space. */
#define WM_WINDOW_GFX_ID 2

/** Docstring: Maximum terminal windows sharing the focus space. */
#define WM_WINDOW_MAX_TERMS 2

/** Docstring: Unified window descriptor in framebuffer pixels. */
typedef struct {
    wm_window_kind_t kind;
    int id;
    int x;
    int y;
    int w;
    int h;
    int present;
    int minimized;
} wm_window_t;

/** Docstring: True when the window can receive input or pointer hits. */
static inline int wm_window_active(const wm_window_t *w)
{
    return w != 0 && w->kind != WM_WIN_NONE && w->present && !w->minimized && w->w > 0 && w->h > 0;
}

/** Docstring: Rectangle covering the whole window including decorations. */
static inline wm_rect_t wm_window_rect(const wm_window_t *w)
{
    wm_rect_t r;
    r.x = (w != 0) ? w->x : 0;
    r.y = (w != 0) ? w->y : 0;
    r.w = (w != 0 && w->w > 0) ? w->w : 0;
    r.h = (w != 0 && w->h > 0) ? w->h : 0;
    return r;
}

/** Docstring: True when point px,py hits the window body or decorations. */
static inline int wm_window_contains(const wm_window_t *w, int px, int py)
{
    wm_rect_t r = wm_window_rect(w);
    if (!wm_window_active(w)) {
        return 0;
    }
    return wm_rect_contains(&r, px, py);
}

/** Docstring: True when point px,py hits the window title bar. */
static inline int wm_window_title_hits(const wm_geom_config_t *cfg, const wm_window_t *w, int px, int py)
{
    if (!wm_window_active(w)) {
        return 0;
    }
    return wm_hit_title_bar(cfg, w->x, w->y, w->w, px, py);
}

/** Docstring: Next focus id across present terminals plus graphics when active. */
static inline int wm_focus_next_id(const int *present, int nterms, int gfx_active, int focus)
{
    int ids[4];
    int n = 0;
    int at = -1;
    int i;
    int k;
    if (present == 0 || nterms <= 0) {
        return focus;
    }
    for (i = 0; i < nterms; i++) {
        if (present[i]) {
            if (n < 4) {
                ids[n++] = i;
            }
        }
    }
    if (gfx_active) {
        if (n < 4) {
            ids[n++] = WM_WINDOW_GFX_ID;
        }
    }
    if (n < 2) {
        return focus;
    }
    for (k = 0; k < n; k++) {
        if (ids[k] == focus) {
            at = k;
        }
    }
    if (at < 0) {
        return ids[0];
    }
    return ids[(at + 1) % n];
}

/** Docstring: Paint order for terminals with focused window last. */
static inline int wm_paint_order(const int *present, int nterms, int focus, int *order, int cap)
{
    int n = 0;
    int i;
    if (present == 0 || order == 0 || nterms <= 0 || cap <= 0) {
        return 0;
    }
    for (i = 0; i < nterms && n < cap; i++) {
        if (present[i] && i != focus) {
            order[n++] = i;
        }
    }
    for (i = 0; i < nterms && n < cap; i++) {
        if (present[i] && i == focus) {
            order[n++] = i;
        }
    }
    return n;
}

#endif
