/** Docstring: Window geometry contract for the MiniOS desktop.
 *
 * Single-file header-only contract owning every rectangle computation the
 * window manager performs. All dimensions arrive through wm_geom_config_t
 * so no caller hardcodes font metrics, title height or scrollbar width.
 * Every predicate fails closed on degenerate rectangles and every
 * constructor clamps negative extents to zero instead of producing
 * inverted ranges that a hit test could misread.
 */
#ifndef WM_GEOM_H
#define WM_GEOM_H

/** Docstring: Centralized geometry configuration for one WM layout engine. */
typedef struct {
    int font_w;
    int font_h;
    int scrollbar_w;
    int title_h;
} wm_geom_config_t;

/** Docstring: Default geometry matching the kernel 8x8 font layout. */
#define WM_GEOM_CONFIG_DEFAULT { 8, 8, 8, 8 }

/** Docstring: Axis-aligned rectangle in framebuffer pixels. */
typedef struct {
    int x;
    int y;
    int w;
    int h;
} wm_rect_t;

/** Docstring: True when the rectangle can contain any point. */
static inline int wm_rect_valid(const wm_rect_t *r)
{
    return r != 0 && r->w > 0 && r->h > 0;
}

/** Docstring: True when point px,py lies inside rectangle r. */
static inline int wm_rect_contains(const wm_rect_t *r, int px, int py)
{
    if (!wm_rect_valid(r)) {
        return 0;
    }
    return px >= r->x && px < r->x + r->w && py >= r->y && py < r->y + r->h;
}

/** Docstring: Title bar strip for a window at px,py with total width w. */
static inline wm_rect_t wm_title_bar_rect(const wm_geom_config_t *cfg, int px, int py, int w)
{
    wm_rect_t r;
    r.x = px;
    r.y = py;
    r.w = w > 0 ? w : 0;
    r.h = (cfg != 0 && cfg->title_h > 0) ? cfg->title_h : 0;
    return r;
}

/** Docstring: Text content area below the title bar. */
static inline wm_rect_t wm_content_rect(const wm_geom_config_t *cfg, int px, int py, int w, int h)
{
    wm_rect_t r;
    int th = (cfg != 0 && cfg->title_h > 0) ? cfg->title_h : 0;
    r.x = px;
    r.y = py + th;
    r.w = w > 0 ? w : 0;
    r.h = h - th > 0 ? h - th : 0;
    return r;
}

/** Docstring: Scrollbar strip at the right edge of the content area. */
static inline wm_rect_t wm_scrollbar_rect(const wm_geom_config_t *cfg, int px, int py, int content_w, int content_h)
{
    wm_rect_t r;
    int th = (cfg != 0 && cfg->title_h > 0) ? cfg->title_h : 0;
    int sw = (cfg != 0 && cfg->scrollbar_w > 0) ? cfg->scrollbar_w : 0;
    r.x = px + content_w;
    r.y = py + th;
    r.w = sw;
    r.h = content_h > 0 ? content_h : 0;
    return r;
}

/** Docstring: True when point px,py hits the title bar of a window at wx,wy with total width w. */
static inline int wm_hit_title_bar(const wm_geom_config_t *cfg, int wx, int wy, int w, int px, int py)
{
    wm_rect_t r = wm_title_bar_rect(cfg, wx, wy, w);
    return wm_rect_contains(&r, px, py);
}

/** Docstring: Clamp a point into the framebuffer bounds. */
static inline void wm_clamp_point(int *px, int *py, int fb_w, int fb_h)
{
    if (px == 0 || py == 0) {
        return;
    }
    if (fb_w <= 0 || fb_h <= 0) {
        return;
    }
    if (*px < 0) {
        *px = 0;
    }
    if (*px >= fb_w) {
        *px = fb_w - 1;
    }
    if (*py < 0) {
        *py = 0;
    }
    if (*py >= fb_h) {
        *py = fb_h - 1;
    }
}

#endif
