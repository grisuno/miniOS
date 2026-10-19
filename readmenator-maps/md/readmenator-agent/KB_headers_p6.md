# Subsystem: headers (page 6 of 6)
Previous: [KB_headers_p5.md](KB_headers_p5.md)

## headers/wm_geom.h
- Doc: Docstring: Window geometry contract for the MiniOS desktop.
- Layer: utility
- Language: h
- Symbols:
  - `wm_geom_config_t` (struct, line 14)
  - `wm_rect_t` (struct, line 25)
  - `wm_rect_valid` (function, line 33) `static inline int wm_rect_valid(const wm_rect_t *r)`
  - `wm_rect_contains` (function, line 39) `static inline int wm_rect_contains(const wm_rect_t *r, int px, int py)`
  - `wm_title_bar_rect` (function, line 48) `static inline wm_rect_t wm_title_bar_rect(const wm_geom_config_t *cfg, int px, int py, int w)`
  - `wm_content_rect` (function, line 59) `static inline wm_rect_t wm_content_rect(const wm_geom_config_t *cfg, int px, int py, int w, int h)`
  - `wm_scrollbar_rect` (function, line 71) `static inline wm_rect_t wm_scrollbar_rect(const wm_geom_config_t *cfg, int px, int py, int conten...`
  - `wm_hit_title_bar` (function, line 84) `static inline int wm_hit_title_bar(const wm_geom_config_t *cfg, int wx, int wy, int w, int px, in...`
  - `wm_clamp_point` (function, line 91) `static inline void wm_clamp_point(int *px, int *py, int fb_w, int fb_h)`
  - `WM_GEOM_H` (macro, line 11) `#define WM_GEOM_H`
  - `WM_GEOM_CONFIG_DEFAULT` (macro, line 22) `#define WM_GEOM_CONFIG_DEFAULT`
- Imported by: `headers/wm_window.h`, `kernel/vga_fb.c`, `tests/test_wm.c`

## headers/wm_gfxview.h
- Doc: Docstring: Graphics-window view contract for the MiniOS desktop.
- Layer: utility
- Language: h
- Symbols:
  - `wm_gfxview_config_t` (struct, line 31)
  - `wm_gfxview_rect_t` (struct, line 47)
  - `wm_gfxview_t` (struct, line 56)
  - `wm_gfxview_mode_name` (function, line 64) `static inline const char *wm_gfxview_mode_name(int mode)`
  - `wm_gfxview_dims_ok` (function, line 79) `static inline int wm_gfxview_dims_ok(int w, int h)`
  - `Downscale` (function, line 88) `* Downscale (fit below 1x) always takes the exact fit. Returns 1 on
 * success, 0 on degenerate i...`
  - `wm_gfxview_clamp` (function, line 134) `static inline void wm_gfxview_clamp(wm_gfxview_rect_t *r, int fb_w, int fb_h)`
  - `wm_gfxview_place_content` (function, line 160) `static inline int wm_gfxview_place_content(const wm_gfxview_config_t *cfg, int sw, int sh,
      ...`
  - `wm_gfxview_map_point` (function, line 255) `static inline int wm_gfxview_map_point(const wm_gfxview_t *v, int sw, int sh,
                   ...`
  - `wm_gfxview_ease` (function, line 291) `static inline long wm_gfxview_ease(int t, int n, long den)`
  - `wm_gfxview_lerp_rect` (function, line 313) `static inline int wm_gfxview_lerp_rect(const wm_gfxview_rect_t *a, const wm_gfxview_rect_t *b,
  ...`
  - `wm_gfxview_rect_same` (function, line 336) `static inline int wm_gfxview_rect_same(const wm_gfxview_rect_t *a, const wm_gfxview_rect_t *b)`
  - `WM_GFXVIEW_H` (macro, line 21) `#define WM_GFXVIEW_H`
  - `WM_GFXVIEW_CONFIG_DEFAULT` (macro, line 41) `#define WM_GFXVIEW_CONFIG_DEFAULT`
  - `WM_GFXVIEW_DIM_MAX` (macro, line 44) `#define WM_GFXVIEW_DIM_MAX`
- Imported by: `kernel/vga_fb.c`, `tests/test_wm.c`

## headers/wm_layout.h
- Doc: Docstring: Unified layout contract for the MiniOS desktop.
- Layer: presentation
- Language: h
- Symbols:
  - `wm_layout_window_t` (struct, line 27)
  - `wm_layout_config_t` (struct, line 36)
  - `wm_layout_cell_t` (struct, line 48)
  - `wm_layout_mode_name` (function, line 57) `static inline const char *wm_layout_mode_name(int mode)`
  - `wm_layout_mode_valid` (function, line 76) `static inline int wm_layout_mode_valid(int mode)`
  - `wm_layout_clamp_cell` (function, line 82) `static inline int wm_layout_clamp_cell(wm_layout_cell_t *cell, int max_cols, int max_rows)`
  - `wm_layout_fullscreen_cell` (function, line 118) `static inline int wm_layout_fullscreen_cell(int max_cols, int max_rows, wm_layout_cell_t *out)`
  - `wm_layout_compute_tile` (function, line 135) `static inline int wm_layout_compute_tile(const wm_layout_window_t *wins, int nwin, int max_cols, ...`
  - `wm_layout_compute_bsp` (function, line 182) `static inline int wm_layout_compute_bsp(const wm_layout_window_t *wins, int nwin, int max_cols, i...`
  - `wm_layout_compute_cascade` (function, line 250) `static inline int wm_layout_compute_cascade(const wm_layout_config_t *cfg, const wm_layout_window...`
  - `wm_layout_compute_fibonacci` (function, line 285) `static inline int wm_layout_compute_fibonacci(const wm_layout_config_t *cfg, const wm_layout_wind...`
  - `wm_layout_compute` (function, line 361) `static inline int wm_layout_compute(const wm_layout_config_t *cfg, const wm_layout_window_t *wins...`
  - `wm_layout_same` (function, line 443) `static inline int wm_layout_same(const wm_layout_cell_t *a, const wm_layout_cell_t *b, int n)`
  - `WM_LAYOUT_H` (macro, line 12) `#define WM_LAYOUT_H`
  - `WM_LAYOUT_MODE_COUNT` (macro, line 24) `#define WM_LAYOUT_MODE_COUNT`
  - `WM_LAYOUT_CONFIG_DEFAULT` (macro, line 45) `#define WM_LAYOUT_CONFIG_DEFAULT`
- Imported by: `kernel/shell.c`, `kernel/vga_fb.c`, `tests/test_wm.c`

## headers/wm_notify.h
- Doc: Docstring: Focus event bus for the MiniOS desktop.
- Layer: utility
- Language: h
- Symbols:
  - `wm_notify_event_t` (struct, line 30)
  - `wm_notify_bus_t` (struct, line 43)
  - `wm_notify_reset` (function, line 51) `static inline void wm_notify_reset(wm_notify_bus_t *bus)`
  - `wm_notify_subscribe` (function, line 66) `static inline int wm_notify_subscribe(wm_notify_bus_t *bus,
                                     ...`
  - `wm_notify_emit` (function, line 76) `static inline void wm_notify_emit(wm_notify_bus_t *bus,
                                  const w...`
  - `wm_notify_last` (function, line 90) `static inline const wm_notify_event_t *wm_notify_last(
    const wm_notify_bus_t *bus)`
  - `wm_notify_src_name` (function, line 98) `static inline const char *wm_notify_src_name(int source)`
  - `WM_NOTIFY_H` (macro, line 2) `#define WM_NOTIFY_H`
  - `WM_NOTIFY_MAX_HANDLERS` (macro, line 41) `#define WM_NOTIFY_MAX_HANDLERS`
- Imported by: `headers/vga_fb.h`, `kernel/shell.c`, `kernel/vga_fb.c`, `tests/test_notify.c`

## headers/wm_render.h
- Doc: Docstring: Render pipeline contract for the MiniOS desktop.
- Layer: presentation
- Language: h
- Symbols:
  - `wm_render_item_t` (struct, line 25)
  - `wm_render_config_t` (struct, line 31)
  - `wm_build_render_plan` (function, line 39) `static inline int wm_build_render_plan(const wm_render_config_t *cfg, const int *present, int nte...`
  - `WM_RENDER_H` (macro, line 11) `#define WM_RENDER_H`
  - `WM_RENDER_CONFIG_DEFAULT` (macro, line 36) `#define WM_RENDER_CONFIG_DEFAULT`
- Depends on: `headers/wm_window.h`
- Imported by: `kernel/vga_fb.c`, `tests/test_wm.c`

## headers/wm_tiling.h
- Doc: Docstring: Tiling layout contract for the MiniOS desktop.
- Layer: utility
- Language: h
- Symbols:
  - `wm_tile_cell_t` (struct, line 13)
  - `wm_tile_layout` (function, line 22) `static inline int wm_tile_layout(const int *present, int nterms, int gfx_active, int max_cols, in...`
  - `WM_TILING_H` (macro, line 10) `#define WM_TILING_H`
- Imported by: `kernel/vga_fb.c`, `tests/test_wm.c`

## headers/wm_window.h
- Doc: Docstring: Unified window contract for the MiniOS desktop.
- Layer: utility
- Language: h
- Symbols:
  - `wm_window_t` (struct, line 29)
  - `wm_window_active` (function, line 41) `static inline int wm_window_active(const wm_window_t *w)`
  - `wm_window_rect` (function, line 47) `static inline wm_rect_t wm_window_rect(const wm_window_t *w)`
  - `wm_window_contains` (function, line 58) `static inline int wm_window_contains(const wm_window_t *w, int px, int py)`
  - `wm_window_title_hits` (function, line 68) `static inline int wm_window_title_hits(const wm_geom_config_t *cfg, const wm_window_t *w, int px,...`
  - `wm_focus_next_id` (function, line 77) `static inline int wm_focus_next_id(const int *present, int nterms, int gfx_active, int focus)`
  - `wm_paint_order` (function, line 114) `static inline int wm_paint_order(const int *present, int nterms, int focus, int *order, int cap)`
  - `WM_WINDOW_H` (macro, line 11) `#define WM_WINDOW_H`
  - `WM_WINDOW_GFX_ID` (macro, line 23) `#define WM_WINDOW_GFX_ID`
  - `WM_WINDOW_MAX_TERMS` (macro, line 26) `#define WM_WINDOW_MAX_TERMS`
- Depends on: `headers/wm_geom.h`
- Imported by: `headers/wm_focus.h`, `headers/wm_render.h`, `kernel/vga_fb.c`, `tests/test_wm.c`

## headers/zip.h
- Doc: — MiniOS integration API for the miniz zip library.
- Layer: utility
- Language: h
- Symbols:
  - `miniz` (function, line 6) `* * The shell builtins over miniz (see zip.c) are declared here so kernel.c's * shell dispatcher can route the...`
  - `shell_cmd_zip` (function, line 15) `void shell_cmd_zip(int argc, char **argv);`
  - `ZIP_H` (macro, line 2) `#define ZIP_H`
- Imported by: `kernel/shell.c`, `kernel/syscalls.c`

