# headers

*Community 7 | 5 files | cohesion 0.50*

## Definition

This community groups 5 file(s) rooted at `headers` with dominant language h (cohesion 0.50). Central symbols: `CHECK`, `WM_FOCUS_H`, `WM_GEOM_CONFIG_DEFAULT`, `WM_GEOM_H`, `WM_RENDER_CONFIG_DEFAULT`, `WM_RENDER_H`, `WM_WINDOW_GFX_ID`, `WM_WINDOW_H`. Core file: `headers/wm_geom.h` (11 symbols). Documented purpose: Docstring: Focus manager contract for the MiniOS desktop..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/wm_focus.h` | h | utility | 5 | yes |
| `headers/wm_geom.h` | h | utility | 11 | yes |
| `headers/wm_render.h` | h | presentation | 5 | yes |
| `headers/wm_window.h` | h | utility | 10 | yes |
| `tests/test_wm.c` | c | testing | 2 | yes |

## Key Symbols

- `WM_FOCUS_H` (macro, `headers/wm_focus.h:10`) `#define WM_FOCUS_H`
- `wm_focus_state_t` (struct, `headers/wm_focus.h:15`) - Docstring: Focus manager contract for the MiniOS desktop.  Single-file header-only contract owning f
- `wm_focus_selectable` (function, `headers/wm_focus.h:23`) `static inline int wm_focus_selectable(const wm_focus_state_t *st, int id)` - #ifndef WM_FOCUS_H #define WM_FOCUS_H #include "wm_window.h" /** Docstring: Focus state snapshot con
- `wm_focus_next` (function, `headers/wm_focus.h:38`) `static inline int wm_focus_next(const wm_focus_state_t *st)` - { if (st == 0) { return 0; } if (id == WM_WINDOW_GFX_ID) { return st->gfx_active ? 1 : 0; } if (id <
- `wm_focus_set` (function, `headers/wm_focus.h:55`) `static inline int wm_focus_set(const wm_focus_state_t *st, int id)` - int i; if (st == 0) { return 0; } for (i = 0; i < 4; i++) { flat[i] = 0; } for (i = 0; i < st->nterm
- `WM_GEOM_H` (macro, `headers/wm_geom.h:11`) `#define WM_GEOM_H`
- `wm_geom_config_t` (struct, `headers/wm_geom.h:14`) - Docstring: Window geometry contract for the MiniOS desktop.  Single-file header-only contract owning
- `WM_GEOM_CONFIG_DEFAULT` (macro, `headers/wm_geom.h:22`) `#define WM_GEOM_CONFIG_DEFAULT`
- `wm_rect_t` (struct, `headers/wm_geom.h:25`) - #define WM_GEOM_H /** Docstring: Centralized geometry configuration for one WM layout engine. typede
- `wm_rect_valid` (function, `headers/wm_geom.h:33`) `static inline int wm_rect_valid(const wm_rect_t *r)` - } wm_geom_config_t; /** Docstring: Default geometry matching the kernel 8x8 font layout. #define WM_
- `wm_rect_contains` (function, `headers/wm_geom.h:39`) `static inline int wm_rect_contains(const wm_rect_t *r, int px, int py)` - typedef struct { int x; int y; int w; int h; } wm_rect_t; /** Docstring: True when the rectangle can
- `wm_title_bar_rect` (function, `headers/wm_geom.h:48`) `static inline wm_rect_t wm_title_bar_rect(const wm_geom_config_t *cfg, int px, i` - { return r != 0 && r->w > 0 && r->h > 0; } /** Docstring: True when point px,py lies inside rectangl
- `wm_content_rect` (function, `headers/wm_geom.h:59`) `static inline wm_rect_t wm_content_rect(const wm_geom_config_t *cfg, int px, int` - } /** Docstring: Title bar strip for a window at px,py with total width w. static inline wm_rect_t w
- `wm_scrollbar_rect` (function, `headers/wm_geom.h:71`) `static inline wm_rect_t wm_scrollbar_rect(const wm_geom_config_t *cfg, int px, i` - /** Docstring: Text content area below the title bar. static inline wm_rect_t wm_content_rect(const
- `wm_hit_title_bar` (function, `headers/wm_geom.h:84`) `static inline int wm_hit_title_bar(const wm_geom_config_t *cfg, int wx, int wy,` - /** Docstring: Scrollbar strip at the right edge of the content area. static inline wm_rect_t wm_scr
- `wm_clamp_point` (function, `headers/wm_geom.h:91`) `static inline void wm_clamp_point(int *px, int *py, int fb_w, int fb_h)` - r.y = py + th; r.w = sw; r.h = content_h > 0 ? content_h : 0; return r; } /** Docstring: True when p
- `WM_RENDER_H` (macro, `headers/wm_render.h:11`) `#define WM_RENDER_H`
- `wm_render_item_t` (struct, `headers/wm_render.h:25`) - #define WM_RENDER_H #include "wm_window.h" /** Docstring: Composition layers from back to front. typ
- `wm_render_config_t` (struct, `headers/wm_render.h:31`) - WM_LAYER_WALLPAPER = 0, WM_LAYER_SHORTCUTS = 1, WM_LAYER_TASKBAR = 2, WM_LAYER_TERMINAL = 3, WM_LAYE
- `WM_RENDER_CONFIG_DEFAULT` (macro, `headers/wm_render.h:36`) `#define WM_RENDER_CONFIG_DEFAULT`
- `wm_build_render_plan` (function, `headers/wm_render.h:39`) `static inline int wm_build_render_plan(const wm_render_config_t *cfg, const int` - typedef struct { wm_layer_t layer; int id; } wm_render_item_t; /** Docstring: Centralized render pip
- `WM_WINDOW_H` (macro, `headers/wm_window.h:11`) `#define WM_WINDOW_H`
- `WM_WINDOW_GFX_ID` (macro, `headers/wm_window.h:23`) `#define WM_WINDOW_GFX_ID`
- `WM_WINDOW_MAX_TERMS` (macro, `headers/wm_window.h:26`) `#define WM_WINDOW_MAX_TERMS`
- `wm_window_t` (struct, `headers/wm_window.h:29`) - /** Docstring: Window kinds sharing one focus space. typedef enum { WM_WIN_NONE = 0, WM_WIN_TERMINAL
- `wm_window_active` (function, `headers/wm_window.h:41`) `static inline int wm_window_active(const wm_window_t *w)` - /** Docstring: Unified window descriptor in framebuffer pixels. typedef struct { wm_window_kind_t ki
- `wm_window_rect` (function, `headers/wm_window.h:47`) `static inline wm_rect_t wm_window_rect(const wm_window_t *w)` - int y; int w; int h; int present; int minimized; } wm_window_t; /** Docstring: True when the window
- `wm_window_contains` (function, `headers/wm_window.h:58`) `static inline int wm_window_contains(const wm_window_t *w, int px, int py)` - } /** Docstring: Rectangle covering the whole window including decorations. static inline wm_rect_t
- `wm_window_title_hits` (function, `headers/wm_window.h:68`) `static inline int wm_window_title_hits(const wm_geom_config_t *cfg, const wm_win` - return r; } /** Docstring: True when point px,py hits the window body or decorations. static inline
- `wm_focus_next_id` (function, `headers/wm_window.h:77`) `static inline int wm_focus_next_id(const int *present, int nterms, int gfx_activ` - } return wm_rect_contains(&r, px, py); } /** Docstring: True when point px,py hits the window title

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 7
- Cross-boundary resolved imports (EXTRACTED): 7

## Connections

- [EXTRACTED] depends_on community 5 <-> 7 (strength 0.9): Extracted import edge crosses communities: kernel/vga_fb.c imports headers/wm_geom.h.
- [INFERRED] shares_context community 0 <-> 7 (strength 0.5): Inferred shared context (layer utility) with no import path between community 0 (headers) and community 7 (headers).

## Risks

- [layer strict] `tests/test_wm.c` (testing) -> `headers/wm_render.h` (presentation)
- [layer strict] `tests/test_wm.c` (testing) -> `headers/wm_layout.h` (presentation)

## Open Questions

- What would break if the most connected file in headers changed?
- Should headers be split, given cohesion 0.50?

## Sources

- `headers/wm_focus.h`
- `headers/wm_geom.h`
- `headers/wm_render.h`
- `headers/wm_window.h`
- `tests/test_wm.c`
