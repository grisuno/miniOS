# Subsystem: headers (page 6 of 6)
Previous: [KB_headers_p5.md](KB_headers_p5.md)

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

