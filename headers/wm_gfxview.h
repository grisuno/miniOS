/** Docstring: Graphics-window view contract for the MiniOS desktop.
 *
 * Single-file header-only contract owning where and how large a ring-3
 * graphics back-buffer (DOOM 320x200, Nuklear/Pokemon 800x360, the
 * Wayland-mini compositor) lands on the framebuffer. Three view modes
 * share one compute entry point:
 *   floating   native size (or the app-requested 2x zoom), centered plus
 *              the WM drag/snap offset, clamped on screen, titled;
 *   tiled      the cell the tiling layout assigned, titled, content
 *              aspect-fit and centered inside it (scaled up or down);
 *   fullscreen the whole framebuffer, no chrome, content aspect-fit and
 *              letterboxed.
 * The content rect is what the scaler fills; the frame rect is what the
 * WM hit-tests and what the letterbox clears. The inverse point map is
 * what lets a scaled app keep reading mouse coordinates in its own
 * back-buffer space. The easing helpers drive the animated transitions
 * between two frame rects. Pure integer logic, no kernel dependencies,
 * every entry fails closed on degenerate input so it stays host-testable.
 */
#ifndef WM_GFXVIEW_H
#define WM_GFXVIEW_H

/** Docstring: View modes of the graphics window. */
typedef enum {
    WM_GFXVIEW_FLOAT = 0,
    WM_GFXVIEW_TILED = 1,
    WM_GFXVIEW_FULL = 2
} wm_gfxview_mode_t;

/** Docstring: Centralized view configuration, no magic numbers. */
typedef struct {
    int title_h;
    int snap_num;
    int snap_den;
    int anim_frames;
    int anim_frame_ms;
} wm_gfxview_config_t;

/** Docstring: Default view: 8 px title, integer scale kept when it
 * covers at least 7/8 of the fit, 10 animation frames at 16 ms. */
#define WM_GFXVIEW_CONFIG_DEFAULT { 8, 7, 8, 10, 16 }

/** Docstring: Largest source or destination edge the math accepts. */
#define WM_GFXVIEW_DIM_MAX 8192

/** Docstring: One axis-aligned rectangle in framebuffer pixels. */
typedef struct {
    int x;
    int y;
    int w;
    int h;
} wm_gfxview_rect_t;

/** Docstring: One computed view: frame (chrome plus content area),
 * title strip height (0 in fullscreen) and the scaled content rect. */
typedef struct {
    int mode;
    wm_gfxview_rect_t frame;
    int title_h;
    wm_gfxview_rect_t content;
} wm_gfxview_t;

/** Docstring: Human name for one view mode, else zero. */
static inline const char *wm_gfxview_mode_name(int mode)
{
    switch (mode) {
    case WM_GFXVIEW_FLOAT:
        return "floating";
    case WM_GFXVIEW_TILED:
        return "tiled";
    case WM_GFXVIEW_FULL:
        return "fullscreen";
    default:
        return 0;
    }
}

/** Docstring: True when every edge lies in the accepted range. */
static inline int wm_gfxview_dims_ok(int w, int h)
{
    return w > 0 && h > 0 && w <= WM_GFXVIEW_DIM_MAX && h <= WM_GFXVIEW_DIM_MAX;
}

/** Docstring: Aspect-preserving fit of sw x sh inside aw x ah.
 * The largest integer scale wins when it covers at least snap_num/snap_den
 * of the exact fit on the limiting axis, so pixel art stays crisp without
 * wasting most of the screen; otherwise the exact fractional fit is used.
 * Downscale (fit below 1x) always takes the exact fit. Returns 1 on
 * success, 0 on degenerate input with both outputs untouched. */
static inline int wm_gfxview_fit(const wm_gfxview_config_t *cfg, int sw, int sh,
                                 int aw, int ah, int *dw, int *dh)
{
    long fw;
    long fh;
    long k;
    long num;
    long den;
    if (dw == 0 || dh == 0 || !wm_gfxview_dims_ok(sw, sh) || !wm_gfxview_dims_ok(aw, ah)) {
        return 0;
    }
    if ((long)aw * (long)sh <= (long)ah * (long)sw) {
        fw = aw;
        fh = ((long)aw * (long)sh) / (long)sw;
    } else {
        fh = ah;
        fw = ((long)ah * (long)sw) / (long)sh;
    }
    if (fw < 1) {
        fw = 1;
    }
    if (fh < 1) {
        fh = 1;
    }
    k = (long)aw / (long)sw;
    if ((long)ah / (long)sh < k) {
        k = (long)ah / (long)sh;
    }
    num = (cfg != 0 && cfg->snap_num > 0) ? cfg->snap_num : 7;
    den = (cfg != 0 && cfg->snap_den > 0) ? cfg->snap_den : 8;
    if (num > den) {
        num = den;
    }
    if (k >= 1 && k * (long)sw * den >= fw * num && k * (long)sh * den >= fh * num) {
        fw = k * (long)sw;
        fh = k * (long)sh;
    }
    *dw = (int)fw;
    *dh = (int)fh;
    return 1;
}

/** Docstring: Clamp a rect inside the framebuffer by moving, then by
 * shrinking when it is larger than the screen. */
static inline void wm_gfxview_clamp(wm_gfxview_rect_t *r, int fb_w, int fb_h)
{
    if (r == 0) {
        return;
    }
    if (r->w > fb_w) {
        r->w = fb_w;
    }
    if (r->h > fb_h) {
        r->h = fb_h;
    }
    if (r->x + r->w > fb_w) {
        r->x = fb_w - r->w;
    }
    if (r->y + r->h > fb_h) {
        r->y = fb_h - r->h;
    }
    if (r->x < 0) {
        r->x = 0;
    }
    if (r->y < 0) {
        r->y = 0;
    }
}

/** Docstring: Center an aspect-fit content rect inside an area. */
static inline int wm_gfxview_place_content(const wm_gfxview_config_t *cfg, int sw, int sh,
                                           const wm_gfxview_rect_t *area, wm_gfxview_rect_t *out)
{
    int dw = 0;
    int dh = 0;
    if (area == 0 || out == 0) {
        return 0;
    }
    if (!wm_gfxview_fit(cfg, sw, sh, area->w, area->h, &dw, &dh)) {
        return 0;
    }
    out->w = dw;
    out->h = dh;
    out->x = area->x + (area->w - dw) / 2;
    out->y = area->y + (area->h - dh) / 2;
    return 1;
}

/** Docstring: Compute the view for one source buffer.
 * zoom scales the floating window by an integer factor (1 = native).
 * cell is the tiled frame rect (only read in tiled mode). off_x/off_y are
 * the floating WM offsets from the centered position. Returns 1 on
 * success, 0 on degenerate input or an unknown mode. */
static inline int wm_gfxview_compute(const wm_gfxview_config_t *cfg, int mode, int sw, int sh,
                                     int zoom, int fb_w, int fb_h, const wm_gfxview_rect_t *cell,
                                     int off_x, int off_y, wm_gfxview_t *out)
{
    int th;
    wm_gfxview_rect_t area;
    if (out == 0 || !wm_gfxview_dims_ok(sw, sh) || !wm_gfxview_dims_ok(fb_w, fb_h)) {
        return 0;
    }
    th = (cfg != 0 && cfg->title_h > 0) ? cfg->title_h : 8;
    if (mode == WM_GFXVIEW_FULL) {
        out->mode = mode;
        out->frame.x = 0;
        out->frame.y = 0;
        out->frame.w = fb_w;
        out->frame.h = fb_h;
        out->title_h = 0;
        return wm_gfxview_place_content(cfg, sw, sh, &out->frame, &out->content);
    }
    if (mode == WM_GFXVIEW_TILED) {
        if (cell == 0 || cell->w <= 0 || cell->h <= th) {
            return 0;
        }
        out->mode = mode;
        out->frame = *cell;
        wm_gfxview_clamp(&out->frame, fb_w, fb_h);
        if (out->frame.h <= th) {
            return 0;
        }
        out->title_h = th;
        area.x = out->frame.x;
        area.y = out->frame.y + th;
        area.w = out->frame.w;
        area.h = out->frame.h - th;
        return wm_gfxview_place_content(cfg, sw, sh, &area, &out->content);
    }
    if (mode == WM_GFXVIEW_FLOAT) {
        int k = (zoom > 1) ? zoom : 1;
        int dw = sw * k;
        int dh = sh * k;
        if (dw > fb_w || dh + th > fb_h) {
            area.x = 0;
            area.y = 0;
            area.w = fb_w;
            area.h = fb_h - th;
            if (area.h <= 0 || !wm_gfxview_fit(cfg, sw, sh, area.w, area.h, &dw, &dh)) {
                return 0;
            }
        }
        out->mode = mode;
        out->title_h = th;
        out->frame.w = dw;
        out->frame.h = dh + th;
        out->frame.x = (fb_w - out->frame.w) / 2 + off_x;
        out->frame.y = (fb_h - out->frame.h) / 2 + off_y;
        wm_gfxview_clamp(&out->frame, fb_w, fb_h);
        out->content.x = out->frame.x;
        out->content.y = out->frame.y + th;
        out->content.w = dw;
        out->content.h = dh;
        return 1;
    }
    return 0;
}

/** Docstring: Map a framebuffer point into back-buffer space.
 * Inside the content rect the point scales exactly into [0, sw) x [0, sh);
 * outside it clamps to the nearest edge so a drag that leaves the window
 * keeps tracking. The result is reported as content origin plus local
 * offset, which is the coordinate space apps already subtract their
 * reported origin from. Returns 1 when the point was inside, 0 when it
 * was clamped, -1 on degenerate input. */
static inline int wm_gfxview_map_point(const wm_gfxview_t *v, int sw, int sh,
                                       int mx, int my, int *vx, int *vy)
{
    long lx;
    long ly;
    int inside;
    if (v == 0 || vx == 0 || vy == 0 || !wm_gfxview_dims_ok(sw, sh)) {
        return -1;
    }
    if (v->content.w <= 0 || v->content.h <= 0) {
        return -1;
    }
    inside = mx >= v->content.x && my >= v->content.y &&
             mx < v->content.x + v->content.w && my < v->content.y + v->content.h;
    lx = ((long)(mx - v->content.x) * (long)sw) / (long)v->content.w;
    ly = ((long)(my - v->content.y) * (long)sh) / (long)v->content.h;
    if (lx < 0) {
        lx = 0;
    }
    if (ly < 0) {
        ly = 0;
    }
    if (lx >= sw) {
        lx = sw - 1;
    }
    if (ly >= sh) {
        ly = sh - 1;
    }
    *vx = v->content.x + (int)lx;
    *vy = v->content.y + (int)ly;
    return inside ? 1 : 0;
}

/** Docstring: Ease-out cubic progress in [0, den] for step t of n.
 * 1 - (1 - t/n)^3 in integer arithmetic: fast start, soft landing,
 * monotonic, exactly 0 at t = 0 and exactly den at t = n. */
static inline long wm_gfxview_ease(int t, int n, long den)
{
    long r;
    long inv;
    if (n <= 0 || den <= 0 || t >= n) {
        return den > 0 ? den : 0;
    }
    if (t <= 0) {
        return 0;
    }
    inv = (long)(n - t);
    r = den - (den * inv * inv * inv) / ((long)n * (long)n * (long)n);
    if (r < 0) {
        r = 0;
    }
    if (r > den) {
        r = den;
    }
    return r;
}

/** Docstring: Interpolate one rect between a and b at eased step t of n. */
static inline int wm_gfxview_lerp_rect(const wm_gfxview_rect_t *a, const wm_gfxview_rect_t *b,
                                       int t, int n, wm_gfxview_rect_t *out)
{
    const long den = 4096;
    long p;
    if (a == 0 || b == 0 || out == 0) {
        return 0;
    }
    p = wm_gfxview_ease(t, n, den);
    out->x = a->x + (int)(((long)(b->x - a->x) * p) / den);
    out->y = a->y + (int)(((long)(b->y - a->y) * p) / den);
    out->w = a->w + (int)(((long)(b->w - a->w) * p) / den);
    out->h = a->h + (int)(((long)(b->h - a->h) * p) / den);
    if (out->w < 1) {
        out->w = 1;
    }
    if (out->h < 1) {
        out->h = 1;
    }
    return 1;
}

/** Docstring: True when two rects are identical. */
static inline int wm_gfxview_rect_same(const wm_gfxview_rect_t *a, const wm_gfxview_rect_t *b)
{
    if (a == 0 || b == 0) {
        return 0;
    }
    return a->x == b->x && a->y == b->y && a->w == b->w && a->h == b->h;
}

#endif
