/** Docstring: Render pipeline contract for the MiniOS desktop.
 *
 * Single-file header-only contract owning frame composition order. The
 * pipeline is a fixed layer stack with terminals painted through the
 * window paint order and the graphics window always last so a blocked
 * app survives redraws. The builder is pure integer logic over present
 * flags so it stays host-testable; the kernel keeps owning the actual
 * pixel work and only consumes the plan. All functions fail closed.
 */
#ifndef WM_RENDER_H
#define WM_RENDER_H

#include "wm_window.h"

/** Docstring: Composition layers from back to front. */
typedef enum {
    WM_LAYER_WALLPAPER = 0,
    WM_LAYER_SHORTCUTS = 1,
    WM_LAYER_TASKBAR = 2,
    WM_LAYER_TERMINAL = 3,
    WM_LAYER_GRAPHICS = 4
} wm_layer_t;

/** Docstring: One composited item in back-to-front order. */
typedef struct {
    wm_layer_t layer;
    int id;
} wm_render_item_t;

/** Docstring: Centralized render pipeline configuration. */
typedef struct {
    int max_items;
} wm_render_config_t;

/** Docstring: Default pipeline bound for two terminals plus chrome. */
#define WM_RENDER_CONFIG_DEFAULT { 8 }

/** Docstring: Build the back-to-front composition plan for one frame. */
static inline int wm_build_render_plan(const wm_render_config_t *cfg, const int *present, int nterms, int focus, int gfx_active, wm_render_item_t *items, int cap)
{
    int n = 0;
    int torder[4];
    int nt = 0;
    int i;
    int bound = (cfg != 0 && cfg->max_items > 0) ? cfg->max_items : 8;
    if (present == 0 || items == 0 || nterms <= 0 || cap <= 0) {
        return 0;
    }
    if (cap > bound) {
        cap = bound;
    }
    items[n].layer = WM_LAYER_WALLPAPER;
    items[n].id = 0;
    n++;
    if (n >= cap) {
        return n;
    }
    items[n].layer = WM_LAYER_SHORTCUTS;
    items[n].id = 0;
    n++;
    if (n >= cap) {
        return n;
    }
    items[n].layer = WM_LAYER_TASKBAR;
    items[n].id = 0;
    n++;
    if (n >= cap) {
        return n;
    }
    nt = wm_paint_order(present, nterms, focus, torder, 4);
    for (i = 0; i < nt && n < cap; i++) {
        items[n].layer = WM_LAYER_TERMINAL;
        items[n].id = torder[i];
        n++;
    }
    if (gfx_active && n < cap) {
        items[n].layer = WM_LAYER_GRAPHICS;
        items[n].id = WM_WINDOW_GFX_ID;
        n++;
    }
    return n;
}

#endif
