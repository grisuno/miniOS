# Symbols (page 7 of 24)
Previous: [SYMBOLS_p6.md](SYMBOLS_p6.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `dock_bounce_counts` | function | `headers/vga_fb.h:253` | `void dock_bounce_counts(unsigned long *kicks, unsigned long *paints);` |
| `dock_click_count` | function | `headers/vga_fb.h:254` | `void dock_click_count(unsigned long *edges);` |
| `dock_pending_active` | function | `headers/vga_fb.h:255` | `int dock_pending_active(void);` |
| `fb_bpp` | variable | `headers/vga_fb.h:26` | `extern int fb_bpp;` |
| `fb_bytes_per_pixel` | function | `headers/vga_fb.h:30` | `int fb_bytes_per_pixel(void);` |
| `fb_height` | variable | `headers/vga_fb.h:24` | `extern int fb_height;` |
| `fb_phys_base` | variable | `headers/vga_fb.h:27` | `extern unsigned long fb_phys_base;` |
| `fb_pitch` | variable | `headers/vga_fb.h:25` | `extern int fb_pitch;` |
| `fb_read_packed` | function | `headers/vga_fb.h:193` | `unsigned long fb_read_packed(int x, int y);` |
| `fb_read_row_packed` | function | `headers/vga_fb.h:218` | `void fb_read_row_packed(int x, int y, unsigned int *dst, int n);` |
| `fb_width` | variable | `headers/vga_fb.h:23` | `extern int fb_width;` |
| `fb_write_packed` | function | `headers/vga_fb.h:194` | `void fb_write_packed(int x, int y, unsigned long rgb);` |
| `fb_write_row_packed` | function | `headers/vga_fb.h:217` | `void fb_write_row_packed(int x, int y, const unsigned int *src, int n);` |
| `fx_melts_completed` | variable | `headers/vga_fb.h:273` | `extern unsigned long fx_melts_completed;` |
| `gfx_frames_composited` | variable | `headers/vga_fb.h:59` | `extern unsigned long gfx_frames_composited;` |
| `gfx_win_title` | variable | `headers/vga_fb.h:50` | `extern const char *gfx_win_title;` |
| `mouse_state` | variable | `headers/vga_fb.h:167` | `extern mouse_state_t mouse_state;` |
| `mouse_state_t` | struct | `headers/vga_fb.h:159` | `` |
| `nk_win_y` | variable | `headers/vga_fb.h:79` | `extern int nk_win_x, nk_win_y;` |
| `pixels` | function | `headers/vga_fb.h:259` | `* are heap buffers of packed pixels (fb_read_packed order), 0 on OOM or a * degenerate rect. A disabled effect or a...` |
| `term_clear` | function | `headers/vga_fb.h:188` | `void term_clear(void);` |
| `term_rows` | variable | `headers/vga_fb.h:156` | `extern int term_x, term_y, term_cols, term_rows;` |
| `vga_fb_active` | variable | `headers/vga_fb.h:282` | `extern int vga_fb_active;` |
| `vga_fb_blit_nk_rgb_window` | function | `headers/vga_fb.h:76` | `void vga_fb_blit_nk_rgb_window(void);` |
| `vga_fb_blit_nk_window` | function | `headers/vga_fb.h:75` | `void vga_fb_blit_nk_window(void);` |
| `vga_fb_boot_config` | function | `headers/vga_fb.h:40` | `void vga_fb_boot_config(void);` |
| `vga_fb_char` | function | `headers/vga_fb.h:184` | `void vga_fb_char(int col, int row, char c, uint8_t fg, uint8_t bg);` |
| `vga_fb_clear` | function | `headers/vga_fb.h:178` | `void vga_fb_clear(void);` |
| `vga_fb_close_active` | function | `headers/vga_fb.h:219` | `int vga_fb_close_active(void);` |
| `vga_fb_draw_desktop` | function | `headers/vga_fb.h:195` | `void vga_fb_draw_desktop(void);` |
| `vga_fb_focus_event` | function | `headers/vga_fb.h:228` | `const wm_notify_event_t *vga_fb_focus_event(void);` |
| `vga_fb_focus_get` | function | `headers/vga_fb.h:225` | `int vga_fb_focus_get(void);` |
| `vga_fb_focus_id` | function | `headers/vga_fb.h:224` | `int vga_fb_focus_id(int id);` |
| `vga_fb_focus_next` | function | `headers/vga_fb.h:223` | `void vga_fb_focus_next(void);` |
| `vga_fb_focus_report` | function | `headers/vga_fb.h:229` | `void vga_fb_focus_report(int before, int source);` |
| `vga_fb_gfx_map_mouse` | function | `headers/vga_fb.h:215` | `void vga_fb_gfx_map_mouse(int *x, int *y);` |
| `vga_fb_gfx_origin` | function | `headers/vga_fb.h:214` | `void vga_fb_gfx_origin(int *x, int *y);` |
| `vga_fb_gfx_set_fullscreen` | function | `headers/vga_fb.h:211` | `int vga_fb_gfx_set_fullscreen(int on);` |
| `vga_fb_gfx_set_hidden` | function | `headers/vga_fb.h:212` | `int vga_fb_gfx_set_hidden(int hide);` |
| `vga_fb_gfx_view_name` | function | `headers/vga_fb.h:213` | `const char *vga_fb_gfx_view_name(void);` |
| `vga_fb_hide_text_cursor` | function | `headers/vga_fb.h:190` | `void vga_fb_hide_text_cursor(void);` |
| `vga_fb_init` | function | `headers/vga_fb.h:177` | `void vga_fb_init(void);` |
| `vga_fb_is_fullscreen` | function | `headers/vga_fb.h:203` | `int vga_fb_is_fullscreen(void);` |
| `vga_fb_is_minimized` | function | `headers/vga_fb.h:202` | `int vga_fb_is_minimized(void);` |
| `vga_fb_layout_cycle` | function | `headers/vga_fb.h:242` | `void vga_fb_layout_cycle(void);` |
| `vga_fb_layout_get` | function | `headers/vga_fb.h:243` | `int vga_fb_layout_get(void);` |
| `vga_fb_layout_name` | function | `headers/vga_fb.h:244` | `const char *vga_fb_layout_name(void);` |
| `vga_fb_layout_set` | function | `headers/vga_fb.h:241` | `int vga_fb_layout_set(int mode);` |
| `vga_fb_list_windows` | function | `headers/vga_fb.h:245` | `void vga_fb_list_windows(void);` |
| `vga_fb_mouse_init` | function | `headers/vga_fb.h:250` | `void vga_fb_mouse_init(void);` |
| `vga_fb_mouse_tick` | function | `headers/vga_fb.h:249` | `void vga_fb_mouse_tick(void);` |
| `vga_fb_move_terminal` | function | `headers/vga_fb.h:197` | `void vga_fb_move_terminal(int dx, int dy);` |
| `vga_fb_nterms_get` | function | `headers/vga_fb.h:237` | `int vga_fb_nterms_get(void);` |
| `vga_fb_pixel` | function | `headers/vga_fb.h:179` | `void vga_fb_pixel(int x, int y, uint8_t color);` |
| `vga_fb_pixel_rgb` | function | `headers/vga_fb.h:182` | `void vga_fb_pixel_rgb(int x, int y, uint8_t r, uint8_t g, uint8_t b);` |
| `vga_fb_ps2_owner` | function | `headers/vga_fb.h:236` | `int vga_fb_ps2_owner(int pid);` |
| `vga_fb_putc_term` | function | `headers/vga_fb.h:186` | `void vga_fb_putc_term(char c);` |
| `vga_fb_puts_term` | function | `headers/vga_fb.h:187` | `void vga_fb_puts_term(const char *s);` |
| `vga_fb_read_rgb` | function | `headers/vga_fb.h:34` | `unsigned long vga_fb_read_rgb(int x, int y);` |
| `vga_fb_rect` | function | `headers/vga_fb.h:180` | `void vga_fb_rect(int x, int y, int w, int h, uint8_t color);` |
| `vga_fb_rect_rgb` | function | `headers/vga_fb.h:183` | `void vga_fb_rect_rgb(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b);` |
| `vga_fb_reset_default` | function | `headers/vga_fb.h:200` | `void vga_fb_reset_default(void);` |
| `vga_fb_resize` | function | `headers/vga_fb.h:199` | `void vga_fb_resize(int dcols, int drows);` |
| `vga_fb_set_gfx_mode` | function | `headers/vga_fb.h:280` | `void vga_fb_set_gfx_mode(int on);` |
| `vga_fb_set_gfx_palette` | function | `headers/vga_fb.h:38` | `void vga_fb_set_gfx_palette(const unsigned char *pal);` |
| `vga_fb_snap_window` | function | `headers/vga_fb.h:198` | `void vga_fb_snap_window(int zone);` |
| `vga_fb_str` | function | `headers/vga_fb.h:185` | `void vga_fb_str(int col, int row, const char *s, uint8_t fg, uint8_t bg);` |
| `vga_fb_term_close_focused` | function | `headers/vga_fb.h:239` | `int vga_fb_term_close_focused(void);` |
| `vga_fb_term_split` | function | `headers/vga_fb.h:238` | `int vga_fb_term_split(void);` |
| `vga_fb_text_cursor` | function | `headers/vga_fb.h:189` | `void vga_fb_text_cursor(int col);` |
| `vga_fb_theme_name` | function | `headers/vga_fb.h:230` | `int vga_fb_theme_name(char *dst, int cap);` |
| `vga_fb_tile_all` | function | `headers/vga_fb.h:240` | `void vga_fb_tile_all(void);` |
| `vga_fb_toggle_fullscreen` | function | `headers/vga_fb.h:196` | `void vga_fb_toggle_fullscreen(void);` |
| `vga_fb_toggle_minimize` | function | `headers/vga_fb.h:201` | `void vga_fb_toggle_minimize(void);` |
| `vga_fx_enabled` | function | `headers/vga_fb.h:263` | `int vga_fx_enabled(void);` |
| `vga_fx_free` | function | `headers/vga_fb.h:266` | `void vga_fx_free(unsigned int *buf);` |
| `vga_fx_melt_from_black` | function | `headers/vga_fb.h:269` | `void vga_fx_melt_from_black(int x, int y, int w, int h, const unsigned int *newb);` |
| `vga_fx_melt_rect` | function | `headers/vga_fb.h:267` | `void vga_fx_melt_rect(int x, int y, int w, int h, const unsigned int *oldb, const unsigned int *newb);` |
| `vga_fx_restore_rect` | function | `headers/vga_fb.h:265` | `void vga_fx_restore_rect(int x, int y, int w, int h, const unsigned int *buf);` |
| `vga_fx_snap_rect` | function | `headers/vga_fb.h:264` | `unsigned int *vga_fx_snap_rect(int x, int y, int w, int h);` |
| `wm_clear_close` | function | `headers/vga_fb.h:247` | `void wm_clear_close(void);` |
| `wm_close_pending` | function | `headers/vga_fb.h:246` | `int wm_close_pending(void);` |
| `wm_gfx_mode_active` | function | `headers/vga_fb.h:248` | `int wm_gfx_mode_active(void);` |
| `VGA_FX_COLS_MAX` | macro | `headers/vga_fx.h:27` | `#define VGA_FX_COLS_MAX` |
| `VGA_FX_CONFIG_DEFAULT` | macro | `headers/vga_fx.h:24` | `#define VGA_FX_CONFIG_DEFAULT` |
| `VGA_FX_H` | macro | `headers/vga_fx.h:13` | `#define VGA_FX_H` |
| `vga_fx_advance` | function | `headers/vga_fx.h:71` | `static inline int vga_fx_advance(const vga_fx_config_t *cfg, int *cols, int w, int h)` |
| `vga_fx_clamp_rect` | function | `headers/vga_fx.h:109` | `static inline int vga_fx_clamp_rect(int *x, int *y, int *w, int *h, int fb_w, int fb_h)` |
| `vga_fx_config_t` | struct | `headers/vga_fx.h:16` | `` |
| `vga_fx_front` | function | `headers/vga_fx.h:97` | `static inline int vga_fx_front(int col_y, int h)` |
| `vga_fx_init_cols` | function | `headers/vga_fx.h:47` | `static inline int vga_fx_init_cols(const vga_fx_config_t *cfg, int *cols, int w)` |
| `vga_fx_rand` | function | `headers/vga_fx.h:30` | `static inline unsigned long vga_fx_rand(unsigned long *s)` |
| `VMA_H` | macro | `headers/vma.h:2` | `#define VMA_H` |
| `VMA_MAX` | macro | `headers/vma.h:31` | `#define VMA_MAX` |
| `VMA_NIL` | variable | `headers/vma.h:54` | `extern vma_node_t *VMA_NIL;` |
| `base` | type_alias | `headers/vma.h:20` | `typedef struct vma_node { unsigned long base;` |
| `vma_ctx_alloc` | function | `headers/vma.h:87` | `vma_ctx_t *vma_ctx_alloc(void);` |
| `vma_ctx_bind` | function | `headers/vma.h:68` | `void vma_ctx_bind(vma_ctx_t *c);` |
| `vma_ctx_free` | function | `headers/vma.h:88` | `void vma_ctx_free(vma_ctx_t *c);` |
| `vma_ctx_init` | function | `headers/vma.h:67` | `void vma_ctx_init(vma_ctx_t *c, vma_node_t *pool);` |
| `vma_ctx_save` | function | `headers/vma.h:69` | `void vma_ctx_save(vma_ctx_t *c);` |
| `vma_ctx_t` | struct | `headers/vma.h:44` | `` |
| `vma_free_root` | variable | `headers/vma.h:56` | `extern vma_node_t *vma_free_root;` |
| `vma_legacy` | variable | `headers/vma.h:60` | `extern vma_ctx_t vma_legacy;` |
| `vma_live_root` | variable | `headers/vma.h:55` | `extern vma_node_t *vma_live_root;` |
| `vma_node` | struct | `headers/vma.h:21` | `` |
| `vma_pool` | variable | `headers/vma.h:57` | `extern vma_node_t vma_pool[VMA_MAX];` |
| `vma_pool_n` | variable | `headers/vma.h:58` | `extern int vma_pool_n;` |
| `vma_pool_ptr` | variable | `headers/vma.h:59` | `extern vma_node_t *vma_pool_ptr;` |
| `vma_tree_delete` | function | `headers/vma.h:66` | `int vma_tree_delete(vma_node_t **root, unsigned long base);` |
| `vma_tree_find` | function | `headers/vma.h:64` | `vma_node_t *vma_tree_find(vma_node_t *root, unsigned long base);` |
| `vma_tree_find_containing` | function | `headers/vma.h:65` | `vma_node_t *vma_tree_find_containing(vma_node_t *root, unsigned long va);` |
| `vma_tree_init` | function | `headers/vma.h:62` | `void vma_tree_init(void);` |
| `vma_tree_insert` | function | `headers/vma.h:63` | `vma_node_t *vma_tree_insert(vma_node_t **root, unsigned long base, unsigned long len);` |
| `vma_view_load` | function | `headers/vma.h:84` | `void vma_view_load(const vma_view_t *v);` |
| `vma_view_save` | function | `headers/vma.h:83` | `void vma_view_save(vma_view_t *v);` |
| `vma_view_t` | struct | `headers/vma.h:74` | `` |
| `WM_COMBOS_N` | macro | `headers/wm_events.h:198` | `#define WM_COMBOS_N` |
| `WM_EVENTS_H` | macro | `headers/wm_events.h:11` | `#define WM_EVENTS_H` |
| `WM_EVENT_CONFIG_DEFAULT` | macro | `headers/wm_events.h:49` | `#define WM_EVENT_CONFIG_DEFAULT` |
| `WM_PATH_COOKED` | macro | `headers/wm_events.h:138` | `#define WM_PATH_COOKED` |
| `WM_PATH_RAW` | macro | `headers/wm_events.h:139` | `#define WM_PATH_RAW` |
| `WM_SC_DOWN` | macro | `headers/wm_events.h:121` | `#define WM_SC_DOWN` |
| `WM_SC_END` | macro | `headers/wm_events.h:125` | `#define WM_SC_END` |
| `WM_SC_ENTER` | macro | `headers/wm_events.h:111` | `#define WM_SC_ENTER` |
| `WM_SC_EQUAL` | macro | `headers/wm_events.h:113` | `#define WM_SC_EQUAL` |
| `WM_SC_HOME` | macro | `headers/wm_events.h:124` | `#define WM_SC_HOME` |
| `WM_SC_LBRACKET` | macro | `headers/wm_events.h:116` | `#define WM_SC_LBRACKET` |
| `WM_SC_LEFT` | macro | `headers/wm_events.h:122` | `#define WM_SC_LEFT` |
| `WM_SC_M` | macro | `headers/wm_events.h:118` | `#define WM_SC_M` |
| `WM_SC_MINUS` | macro | `headers/wm_events.h:112` | `#define WM_SC_MINUS` |
| `WM_SC_Q` | macro | `headers/wm_events.h:115` | `#define WM_SC_Q` |
| `WM_SC_RBRACKET` | macro | `headers/wm_events.h:117` | `#define WM_SC_RBRACKET` |
| `WM_SC_RIGHT` | macro | `headers/wm_events.h:123` | `#define WM_SC_RIGHT` |
| `WM_SC_TAB` | macro | `headers/wm_events.h:110` | `#define WM_SC_TAB` |
| `WM_SC_UP` | macro | `headers/wm_events.h:120` | `#define WM_SC_UP` |
| `WM_SC_X` | macro | `headers/wm_events.h:119` | `#define WM_SC_X` |
| `WM_SC_ZERO` | macro | `headers/wm_events.h:114` | `#define WM_SC_ZERO` |
| `WM_SNAP_BOTTOM` | macro | `headers/wm_events.h:131` | `#define WM_SNAP_BOTTOM` |
| `WM_SNAP_BOTTOM_LEFT` | macro | `headers/wm_events.h:134` | `#define WM_SNAP_BOTTOM_LEFT` |
| `WM_SNAP_BOTTOM_RIGHT` | macro | `headers/wm_events.h:135` | `#define WM_SNAP_BOTTOM_RIGHT` |
| `WM_SNAP_LEFT` | macro | `headers/wm_events.h:128` | `#define WM_SNAP_LEFT` |
| `WM_SNAP_RIGHT` | macro | `headers/wm_events.h:129` | `#define WM_SNAP_RIGHT` |
| `WM_SNAP_TOP` | macro | `headers/wm_events.h:130` | `#define WM_SNAP_TOP` |
| `WM_SNAP_TOP_LEFT` | macro | `headers/wm_events.h:132` | `#define WM_SNAP_TOP_LEFT` |
| `WM_SNAP_TOP_RIGHT` | macro | `headers/wm_events.h:133` | `#define WM_SNAP_TOP_RIGHT` |
| `wm_combo_lookup` | function | `headers/wm_events.h:201` | `static inline int wm_combo_lookup(int alt, int altgr, int sup, int e0, int sc, int path, int *zon...` |
| `wm_combo_lookup_mods` | function | `headers/wm_events.h:238` | `static inline int wm_combo_lookup_mods(const modifier_state_t *st, int e0, int sc, int path, int ...` |
| `wm_combo_t` | struct | `headers/wm_events.h:158` | `` |
| `wm_event_config_t` | struct | `headers/wm_events.h:43` | `` |
| `wm_event_suppresses_drag` | function | `headers/wm_events.h:104` | `static inline int wm_event_suppresses_drag(const wm_event_t *evt)` |
| `wm_event_t` | struct | `headers/wm_events.h:34` | `` |
| `wm_is_click_edge` | function | `headers/wm_events.h:52` | `static inline int wm_is_click_edge(const wm_event_config_t *cfg, int prev_buttons, int curr_buttons)` |
| `wm_is_release_edge` | function | `headers/wm_events.h:59` | `static inline int wm_is_release_edge(const wm_event_config_t *cfg, int prev_buttons, int curr_but...` |
| `wm_mouse_t` | struct | `headers/wm_events.h:25` | `` |
| `wm_translate_event` | function | `headers/wm_events.h:66` | `static inline wm_event_t wm_translate_event(const wm_event_config_t *cfg, const wm_mouse_t *prev,...` |
| `WM_FOCUS_H` | macro | `headers/wm_focus.h:10` | `#define WM_FOCUS_H` |
| `wm_focus_next` | function | `headers/wm_focus.h:38` | `static inline int wm_focus_next(const wm_focus_state_t *st)` |
| `wm_focus_selectable` | function | `headers/wm_focus.h:23` | `static inline int wm_focus_selectable(const wm_focus_state_t *st, int id)` |
| `wm_focus_set` | function | `headers/wm_focus.h:55` | `static inline int wm_focus_set(const wm_focus_state_t *st, int id)` |
| `wm_focus_state_t` | struct | `headers/wm_focus.h:15` | `` |
| `WM_GEOM_CONFIG_DEFAULT` | macro | `headers/wm_geom.h:22` | `#define WM_GEOM_CONFIG_DEFAULT` |
| `WM_GEOM_H` | macro | `headers/wm_geom.h:11` | `#define WM_GEOM_H` |
| `wm_clamp_point` | function | `headers/wm_geom.h:91` | `static inline void wm_clamp_point(int *px, int *py, int fb_w, int fb_h)` |
| `wm_content_rect` | function | `headers/wm_geom.h:59` | `static inline wm_rect_t wm_content_rect(const wm_geom_config_t *cfg, int px, int py, int w, int h)` |
| `wm_geom_config_t` | struct | `headers/wm_geom.h:14` | `` |
| `wm_hit_title_bar` | function | `headers/wm_geom.h:84` | `static inline int wm_hit_title_bar(const wm_geom_config_t *cfg, int wx, int wy, int w, int px, in...` |
| `wm_rect_contains` | function | `headers/wm_geom.h:39` | `static inline int wm_rect_contains(const wm_rect_t *r, int px, int py)` |
| `wm_rect_t` | struct | `headers/wm_geom.h:25` | `` |
| `wm_rect_valid` | function | `headers/wm_geom.h:33` | `static inline int wm_rect_valid(const wm_rect_t *r)` |
| `wm_scrollbar_rect` | function | `headers/wm_geom.h:71` | `static inline wm_rect_t wm_scrollbar_rect(const wm_geom_config_t *cfg, int px, int py, int conten...` |
| `wm_title_bar_rect` | function | `headers/wm_geom.h:48` | `static inline wm_rect_t wm_title_bar_rect(const wm_geom_config_t *cfg, int px, int py, int w)` |
| `Downscale` | function | `headers/wm_gfxview.h:88` | `* Downscale (fit below 1x) always takes the exact fit. Returns 1 on  * success, 0 on degenerate i...` |
| `WM_GFXVIEW_CONFIG_DEFAULT` | macro | `headers/wm_gfxview.h:41` | `#define WM_GFXVIEW_CONFIG_DEFAULT` |
| `WM_GFXVIEW_DIM_MAX` | macro | `headers/wm_gfxview.h:44` | `#define WM_GFXVIEW_DIM_MAX` |
| `WM_GFXVIEW_H` | macro | `headers/wm_gfxview.h:21` | `#define WM_GFXVIEW_H` |
| `wm_gfxview_clamp` | function | `headers/wm_gfxview.h:134` | `static inline void wm_gfxview_clamp(wm_gfxview_rect_t *r, int fb_w, int fb_h)` |
| `wm_gfxview_config_t` | struct | `headers/wm_gfxview.h:31` | `` |
| `wm_gfxview_dims_ok` | function | `headers/wm_gfxview.h:79` | `static inline int wm_gfxview_dims_ok(int w, int h)` |
| `wm_gfxview_ease` | function | `headers/wm_gfxview.h:291` | `static inline long wm_gfxview_ease(int t, int n, long den)` |
| `wm_gfxview_lerp_rect` | function | `headers/wm_gfxview.h:313` | `static inline int wm_gfxview_lerp_rect(const wm_gfxview_rect_t *a, const wm_gfxview_rect_t *b,   ...` |
| `wm_gfxview_map_point` | function | `headers/wm_gfxview.h:255` | `static inline int wm_gfxview_map_point(const wm_gfxview_t *v, int sw, int sh,                    ...` |
| `wm_gfxview_mode_name` | function | `headers/wm_gfxview.h:64` | `static inline const char *wm_gfxview_mode_name(int mode)` |
| `wm_gfxview_place_content` | function | `headers/wm_gfxview.h:160` | `static inline int wm_gfxview_place_content(const wm_gfxview_config_t *cfg, int sw, int sh,       ...` |
| `wm_gfxview_rect_same` | function | `headers/wm_gfxview.h:336` | `static inline int wm_gfxview_rect_same(const wm_gfxview_rect_t *a, const wm_gfxview_rect_t *b)` |
| `wm_gfxview_rect_t` | struct | `headers/wm_gfxview.h:47` | `` |
| `wm_gfxview_t` | struct | `headers/wm_gfxview.h:56` | `` |
| `WM_LAYOUT_CONFIG_DEFAULT` | macro | `headers/wm_layout.h:45` | `#define WM_LAYOUT_CONFIG_DEFAULT` |
| `WM_LAYOUT_H` | macro | `headers/wm_layout.h:12` | `#define WM_LAYOUT_H` |
| `WM_LAYOUT_MODE_COUNT` | macro | `headers/wm_layout.h:24` | `#define WM_LAYOUT_MODE_COUNT` |
| `wm_layout_cell_t` | struct | `headers/wm_layout.h:48` | `` |
| `wm_layout_clamp_cell` | function | `headers/wm_layout.h:82` | `static inline int wm_layout_clamp_cell(wm_layout_cell_t *cell, int max_cols, int max_rows)` |
| `wm_layout_compute` | function | `headers/wm_layout.h:361` | `static inline int wm_layout_compute(const wm_layout_config_t *cfg, const wm_layout_window_t *wins...` |
| `wm_layout_compute_bsp` | function | `headers/wm_layout.h:182` | `static inline int wm_layout_compute_bsp(const wm_layout_window_t *wins, int nwin, int max_cols, i...` |
| `wm_layout_compute_cascade` | function | `headers/wm_layout.h:250` | `static inline int wm_layout_compute_cascade(const wm_layout_config_t *cfg, const wm_layout_window...` |
| `wm_layout_compute_fibonacci` | function | `headers/wm_layout.h:285` | `static inline int wm_layout_compute_fibonacci(const wm_layout_config_t *cfg, const wm_layout_wind...` |
| `wm_layout_compute_tile` | function | `headers/wm_layout.h:135` | `static inline int wm_layout_compute_tile(const wm_layout_window_t *wins, int nwin, int max_cols, ...` |
| `wm_layout_config_t` | struct | `headers/wm_layout.h:36` | `` |
| `wm_layout_fullscreen_cell` | function | `headers/wm_layout.h:118` | `static inline int wm_layout_fullscreen_cell(int max_cols, int max_rows, wm_layout_cell_t *out)` |
| `wm_layout_mode_name` | function | `headers/wm_layout.h:57` | `static inline const char *wm_layout_mode_name(int mode)` |
| `wm_layout_mode_valid` | function | `headers/wm_layout.h:76` | `static inline int wm_layout_mode_valid(int mode)` |
| `wm_layout_same` | function | `headers/wm_layout.h:443` | `static inline int wm_layout_same(const wm_layout_cell_t *a, const wm_layout_cell_t *b, int n)` |
| `wm_layout_window_t` | struct | `headers/wm_layout.h:27` | `` |
| `WM_NOTIFY_H` | macro | `headers/wm_notify.h:2` | `#define WM_NOTIFY_H` |
| `WM_NOTIFY_MAX_HANDLERS` | macro | `headers/wm_notify.h:41` | `#define WM_NOTIFY_MAX_HANDLERS` |
| `wm_notify_bus_t` | struct | `headers/wm_notify.h:43` | `` |
| `wm_notify_emit` | function | `headers/wm_notify.h:76` | `static inline void wm_notify_emit(wm_notify_bus_t *bus,                                   const w...` |
| `wm_notify_event_t` | struct | `headers/wm_notify.h:30` | `` |
| `wm_notify_last` | function | `headers/wm_notify.h:90` | `static inline const wm_notify_event_t *wm_notify_last(     const wm_notify_bus_t *bus)` |
| `wm_notify_reset` | function | `headers/wm_notify.h:51` | `static inline void wm_notify_reset(wm_notify_bus_t *bus)` |
| `wm_notify_src_name` | function | `headers/wm_notify.h:98` | `static inline const char *wm_notify_src_name(int source)` |
| `wm_notify_subscribe` | function | `headers/wm_notify.h:66` | `static inline int wm_notify_subscribe(wm_notify_bus_t *bus,                                      ...` |
| `WM_RENDER_CONFIG_DEFAULT` | macro | `headers/wm_render.h:36` | `#define WM_RENDER_CONFIG_DEFAULT` |
| `WM_RENDER_H` | macro | `headers/wm_render.h:11` | `#define WM_RENDER_H` |
| `wm_build_render_plan` | function | `headers/wm_render.h:39` | `static inline int wm_build_render_plan(const wm_render_config_t *cfg, const int *present, int nte...` |
| `wm_render_config_t` | struct | `headers/wm_render.h:31` | `` |
| `wm_render_item_t` | struct | `headers/wm_render.h:25` | `` |
| `WM_TILING_H` | macro | `headers/wm_tiling.h:10` | `#define WM_TILING_H` |
| `wm_tile_cell_t` | struct | `headers/wm_tiling.h:13` | `` |
| `wm_tile_layout` | function | `headers/wm_tiling.h:22` | `static inline int wm_tile_layout(const int *present, int nterms, int gfx_active, int max_cols, in...` |
| `WM_WINDOW_GFX_ID` | macro | `headers/wm_window.h:23` | `#define WM_WINDOW_GFX_ID` |
| `WM_WINDOW_H` | macro | `headers/wm_window.h:11` | `#define WM_WINDOW_H` |
| `WM_WINDOW_MAX_TERMS` | macro | `headers/wm_window.h:26` | `#define WM_WINDOW_MAX_TERMS` |
| `wm_focus_next_id` | function | `headers/wm_window.h:77` | `static inline int wm_focus_next_id(const int *present, int nterms, int gfx_active, int focus)` |
| `wm_paint_order` | function | `headers/wm_window.h:114` | `static inline int wm_paint_order(const int *present, int nterms, int focus, int *order, int cap)` |
| `wm_window_active` | function | `headers/wm_window.h:41` | `static inline int wm_window_active(const wm_window_t *w)` |
| `wm_window_contains` | function | `headers/wm_window.h:58` | `static inline int wm_window_contains(const wm_window_t *w, int px, int py)` |
| `wm_window_rect` | function | `headers/wm_window.h:47` | `static inline wm_rect_t wm_window_rect(const wm_window_t *w)` |
| `wm_window_t` | struct | `headers/wm_window.h:29` | `` |
| `wm_window_title_hits` | function | `headers/wm_window.h:68` | `static inline int wm_window_title_hits(const wm_geom_config_t *cfg, const wm_window_t *w, int px,...` |
| `ZIP_H` | macro | `headers/zip.h:2` | `#define ZIP_H` |
| `miniz` | function | `headers/zip.h:6` | `* * The shell builtins over miniz (see zip.c) are declared here so kernel.c's * shell dispatcher can route the...` |
| `shell_cmd_zip` | function | `headers/zip.h:15` | `void shell_cmd_zip(int argc, char **argv);` |
| `BOOTLOG_MAX` | macro | `kernel.c:185` | `#define BOOTLOG_MAX` |
| `EM` | function | `kernel.c:218` | `* CR0: clear EM (bit 2), set MP (bit 1);` |
| `KSYM_MAX` | macro | `kernel.c:104` | `#define KSYM_MAX` |
| `__attribute__` | function | `kernel.c:204` | `__attribute__((section(".init.text"))) void kmain(void)` |
| `bootlog_mark` | function | `kernel.c:189` | `void bootlog_mark(const char *name)` |
| `bootlog_report` | function | `kernel.c:196` | `void bootlog_report(void)` |
| `kstack` | function | `kernel.c:143` | `* Reading gs:8 instead resolves every thread to the wrong kstack (0 on * the BSP, 1 on APs): harmless while a single...` |
| `ksyscall` | function | `kernel.c:127` | `extern long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6);` |
| `ms` | function | `kernel.c:182` | `* 0 ms (TSC ticks since power-on divided down, still monotonic);` |
| `ramdisk_end` | variable | `kernel.c:177` | `extern char ramdisk_end[];` |
| `ramdisk_start` | variable | `kernel.c:176` | `extern char ramdisk_start[];` |
| `size` | function | `kernel.c:259` | `* image size (see kernel.ld);` |
| `syscall_init` | function | `kernel.c:114` | `void syscall_init(void)` |
| `syscall_kstack` | variable | `kernel.c:112` | `extern unsigned long syscall_kstack;` |
| `table` | function | `kernel.c:101` | `* Symbol table (for resolving program references) * ================================================================...` |
| `tables` | function | `kernel.c:281` | `* tables (already built above) for its uncached register window and the      * heap for its rings...` |
| `abi_check_manifest` | function | `kernel/abi.c:74` | `int abi_check_manifest(void)` |
| `abi_parse_num` | function | `kernel/abi.c:20` | `static int abi_parse_num(const char **pp, const char *end, unsigned long *out)` |
| `abi_verify` | function | `kernel/abi.c:38` | `int abi_verify(const char *text, long version, unsigned long checksum)` |
| `batch_exec` | function | `kernel/batch.c:19` | `long batch_exec(const batch_op_t *ops, long *results, int count,                 int *completed, ...` |
| `CLIP_MAX` | macro | `kernel/clip.c:17` | `#define CLIP_MAX` |
| `clip_clear` | function | `kernel/clip.c:48` | `void clip_clear(void)` |
| `clip_len_get` | function | `kernel/clip.c:55` | `int clip_len_get(void)` |
| `clip_set` | function | `kernel/clip.c:25` | `int clip_set(const char *data, unsigned long len)` |
| `REDIR_INITIAL_CAP` | macro | `kernel/console.c:96` | `#define REDIR_INITIAL_CAP` |
| `REDIR_MAX_BYTES` | macro | `kernel/console.c:97` | `#define REDIR_MAX_BYTES` |
| `XXH_STATIC_LINKING_ONLY` | macro | `kernel/console.c:4` | `#define XXH_STATIC_LINKING_ONLY` |
| `redir_grow` | function | `kernel/console.c:110` | `static int redir_grow(void)` |
| `redirect_active` | function | `kernel/console.c:120` | `int redirect_active(void)` |
| `redirect_begin` | function | `kernel/console.c:139` | `int redirect_begin(void)` |
| `redirect_commit` | function | `kernel/console.c:147` | `int redirect_commit(const char *path, int append_mode)` |
| `redirect_discard` | function | `kernel/console.c:216` | `void redirect_discard(void)` |
| `redirect_pending` | function | `kernel/console.c:185` | `unsigned long redirect_pending(void)` |
| `redirect_putc` | function | `kernel/console.c:122` | `static int redirect_putc(char c)` |
| `redirect_resume` | function | `kernel/console.c:135` | `void redirect_resume(int was)` |
| `redirect_suspend` | function | `kernel/console.c:129` | `int redirect_suspend(void)` |
| `redirect_take_into` | function | `kernel/console.c:196` | `unsigned long redirect_take_into(char *dst, unsigned long cap,         unsigned long *len_out)` |
| `register_libc_symbols` | function | `kernel/console.c:271` | `void register_libc_symbols(void)` |
| `vga_clear` | function | `kernel/console.c:25` | `void vga_clear(void)` |
| `vga_cursor_enable` | function | `kernel/console.c:81` | `void vga_cursor_enable(int on)` |
| `vga_get_color` | function | `kernel/console.c:21` | `char vga_get_color(void)` |
| `vga_get_x` | function | `kernel/console.c:18` | `int vga_get_x(void)` |
| `vga_get_y` | function | `kernel/console.c:19` | `int vga_get_y(void)` |
| `vga_newline` | function | `kernel/console.c:75` | `void vga_newline(void)` |
| `vga_offset` | function | `kernel/console.c:23` | `static inline unsigned vga_offset(int x, int y)` |
| `vga_putc` | function | `kernel/console.c:223` | `void vga_putc(char c)` |
| `vga_puts` | function | `kernel/console.c:267` | `void vga_puts(const char *s)` |
| `vga_raw_space` | function | `kernel/console.c:88` | `static void vga_raw_space(void)` |
| `vga_scroll` | function | `kernel/console.c:56` | `void vga_scroll(void)` |
| `vga_set_cursor` | function | `kernel/console.c:36` | `void vga_set_cursor(int x, int y)` |
| `vga_set_xy` | function | `kernel/console.c:20` | `void vga_set_xy(int x, int y)` |
| `ESC` | function | `kernel/console_in.c:157` | `* The bound keeps a bare ESC (never completed into a sequence) from  * hanging the reader. */ #de...` |
| `MAX_SEQ_POLL` | macro | `kernel/console_in.c:159` | `#define MAX_SEQ_POLL` |
| `PB_LEN` | macro | `kernel/console_in.c:18` | `#define PB_LEN` |
| `SB_EXIT` | macro | `kernel/console_in.c:306` | `#define SB_EXIT` |
| `SB_LEN` | macro | `kernel/console_in.c:281` | `#define SB_LEN` |
| `SB_PGDN` | macro | `kernel/console_in.c:305` | `#define SB_PGDN` |
| `SB_PGUP` | macro | `kernel/console_in.c:304` | `#define SB_PGUP` |
| `console_getc` | function | `kernel/console_in.c:205` | `int console_getc(void)` |
| `console_job_get` | function | `kernel/console_in.c:267` | `int console_job_get(void)` |
| `console_job_try` | function | `kernel/console_in.c:257` | `int console_job_try(void)` |
| `console_peek` | function | `kernel/console_in.c:233` | `int console_peek(void)` |
| `console_poll_usb` | function | `kernel/console_in.c:93` | `static void console_poll_usb(void)` |
| `console_ps2_live` | function | `kernel/console_in.c:106` | `static int console_ps2_live(void)` |
| `console_raw_get` | function | `kernel/console_in.c:250` | `int console_raw_get(void)` |
| `console_raw_try` | function | `kernel/console_in.c:246` | `int console_raw_try(void)` |
| `console_stdin_active` | function | `kernel/console_in.c:56` | `int console_stdin_active(void)` |
| `console_stdin_clear` | function | `kernel/console_in.c:46` | `void console_stdin_clear(void)` |
| `console_stdin_push` | function | `kernel/console_in.c:32` | `int console_stdin_push(const char *data, unsigned long len)` |
| `console_ungetc` | function | `kernel/console_in.c:85` | `void console_ungetc(unsigned char c)` |
| `consume_page_after_esc` | function | `kernel/console_in.c:178` | `static int consume_page_after_esc(void)` |
| `pb_count` | function | `kernel/console_in.c:61` | `static int pb_count(void)` |
| `pb_empty` | function | `kernel/console_in.c:60` | `static int pb_empty(void)` |
| `pb_peek` | function | `kernel/console_in.c:78` | `static int pb_peek(void)` |
| `pb_pop` | function | `kernel/console_in.c:72` | `static int pb_pop(void)` |
| `pb_push_back` | function | `kernel/console_in.c:62` | `static void pb_push_back(unsigned char c)` |
| `pb_push_front` | function | `kernel/console_in.c:67` | `static void pb_push_front(unsigned char c)` |
| `raw_blocking_getc` | function | `kernel/console_in.c:118` | `static int raw_blocking_getc(void)` |
| `raw_try_getc` | function | `kernel/console_in.c:139` | `static int raw_try_getc(void)` |
| `sb_next` | function | `kernel/console_in.c:311` | `static int sb_next(void)` |
| `scrollback_render` | function | `kernel/console_in.c:283` | `static void scrollback_render(int voff, int total, const unsigned char *saved)` |
| `scrollback_view` | function | `kernel/console_in.c:321` | `static void scrollback_view(int initial_dir)` |
| `cvm_main` | function | `kernel/cvm_host.c:437` | `int cvm_main(int argc, char **argv)` |
| `kformat` | function | `kernel/cvm_host.c:296` | `static void kformat(void *ctx, const char *fmt, uint64_t *argv, int argc)` |
| `kout_char` | function | `kernel/cvm_host.c:277` | `static void kout_char(void *ctx, char c)` |
| `kout_uint` | function | `kernel/cvm_host.c:283` | `static void kout_uint(void *ctx, unsigned long long v, int base, int upper)` |
| `n_atol` | function | `kernel/cvm_host.c:236` | `static int64_t n_atol(void *vm, int ac, uint64_t *av)` |
| `n_calloc` | function | `kernel/cvm_host.c:98` | `static int64_t n_calloc(void *vm, int ac, uint64_t *av)` |
| `n_exit` | function | `kernel/cvm_host.c:114` | `static int64_t n_exit(void *vm, int ac, uint64_t *av)` |
| `n_fclose` | function | `kernel/cvm_host.c:128` | `static int64_t n_fclose(void *vm, int ac, uint64_t *av)` |
| `n_fflush` | function | `kernel/cvm_host.c:191` | `static int64_t n_fflush(void *vm, int ac, uint64_t *av)` |
| `n_fgetc` | function | `kernel/cvm_host.c:179` | `static int64_t n_fgetc(void *vm, int ac, uint64_t *av)` |
| `n_fopen` | function | `kernel/cvm_host.c:121` | `static int64_t n_fopen(void *vm, int ac, uint64_t *av)` |
| `n_fprintf` | function | `kernel/cvm_host.c:362` | `static int64_t n_fprintf(void *vm, int ac, uint64_t *av)` |
| `n_fputc` | function | `kernel/cvm_host.c:173` | `static int64_t n_fputc(void *vm, int ac, uint64_t *av)` |
| `n_fputs` | function | `kernel/cvm_host.c:167` | `static int64_t n_fputs(void *vm, int ac, uint64_t *av)` |
| `n_fread` | function | `kernel/cvm_host.c:134` | `static int64_t n_fread(void *vm, int ac, uint64_t *av)` |
| `n_free` | function | `kernel/cvm_host.c:93` | `static int64_t n_free(void *vm, int ac, uint64_t *av)` |
| `n_fseek` | function | `kernel/cvm_host.c:148` | `static int64_t n_fseek(void *vm, int ac, uint64_t *av)` |
| `n_ftell` | function | `kernel/cvm_host.c:154` | `static int64_t n_ftell(void *vm, int ac, uint64_t *av)` |
| `n_fwrite` | function | `kernel/cvm_host.c:141` | `static int64_t n_fwrite(void *vm, int ac, uint64_t *av)` |
| `n_malloc` | function | `kernel/cvm_host.c:88` | `static int64_t n_malloc(void *vm, int ac, uint64_t *av)` |
| `n_memcmp` | function | `kernel/cvm_host.c:68` | `static int64_t n_memcmp(void *vm, int ac, uint64_t *av)` |
| `n_memcpy` | function | `kernel/cvm_host.c:48` | `static int64_t n_memcpy(void *vm, int ac, uint64_t *av)` |
| `n_memmove` | function | `kernel/cvm_host.c:61` | `static int64_t n_memmove(void *vm, int ac, uint64_t *av)` |
| `n_memset` | function | `kernel/cvm_host.c:55` | `static int64_t n_memset(void *vm, int ac, uint64_t *av)` |
| `n_printf` | function | `kernel/cvm_host.c:369` | `static int64_t n_printf(void *vm, int ac, uint64_t *av)` |
| `n_putchar` | function | `kernel/cvm_host.c:197` | `static int64_t n_putchar(void *vm, int ac, uint64_t *av)` |
| `n_puts` | function | `kernel/cvm_host.c:228` | `static int64_t n_puts(void *vm, int ac, uint64_t *av)` |
| `n_read` | function | `kernel/cvm_host.c:213` | `static int64_t n_read(void *vm, int ac, uint64_t *av)` |
| `n_realloc` | function | `kernel/cvm_host.c:106` | `static int64_t n_realloc(void *vm, int ac, uint64_t *av)` |
| `n_rewind` | function | `kernel/cvm_host.c:160` | `static int64_t n_rewind(void *vm, int ac, uint64_t *av)` |
| `n_snprintf` | function | `kernel/cvm_host.c:384` | `static int64_t n_snprintf(void *vm, int ac, uint64_t *av)` |
| `n_sprintf` | function | `kernel/cvm_host.c:376` | `static int64_t n_sprintf(void *vm, int ac, uint64_t *av)` |
| `n_stderr_addr` | function | `kernel/cvm_host.c:262` | `static int64_t n_stderr_addr(void *vm, int ac, uint64_t *av)` |
| `n_stdin_addr` | function | `kernel/cvm_host.c:272` | `static int64_t n_stdin_addr(void *vm, int ac, uint64_t *av)` |
| `n_stdout_addr` | function | `kernel/cvm_host.c:267` | `static int64_t n_stdout_addr(void *vm, int ac, uint64_t *av)` |
| `n_strchr` | function | `kernel/cvm_host.c:75` | `static int64_t n_strchr(void *vm, int ac, uint64_t *av)` |
| `n_strcmp` | function | `kernel/cvm_host.c:22` | `static int64_t n_strcmp(void *vm, int ac, uint64_t *av)` |
| `n_strcpy` | function | `kernel/cvm_host.c:35` | `static int64_t n_strcpy(void *vm, int ac, uint64_t *av)` |
| `n_strncmp` | function | `kernel/cvm_host.c:28` | `static int64_t n_strncmp(void *vm, int ac, uint64_t *av)` |
| `n_strncpy` | function | `kernel/cvm_host.c:41` | `static int64_t n_strncpy(void *vm, int ac, uint64_t *av)` |
| `n_strstr` | function | `kernel/cvm_host.c:81` | `static int64_t n_strstr(void *vm, int ac, uint64_t *av)` |
| `n_strtol` | function | `kernel/cvm_host.c:249` | `static int64_t n_strtol(void *vm, int ac, uint64_t *av)` |
| `n_ungetc` | function | `kernel/cvm_host.c:185` | `static int64_t n_ungetc(void *vm, int ac, uint64_t *av)` |
| `n_write` | function | `kernel/cvm_host.c:204` | `static int64_t n_write(void *vm, int ac, uint64_t *av)` |
| `register_host_natives` | function | `kernel/cvm_host.c:392` | `static void register_host_natives(CvmState *vm)` |
| `EDIT_FILE_MAX` | macro | `kernel/editor.c:22` | `#define EDIT_FILE_MAX` |
| `EDIT_LINE_MAX` | macro | `kernel/editor.c:21` | `#define EDIT_LINE_MAX` |
| `EDIT_MAX_LINES` | macro | `kernel/editor.c:20` | `#define EDIT_MAX_LINES` |
| `EditBuf` | struct | `kernel/editor.c:29` | `` |
| `EditLine` | struct | `kernel/editor.c:24` | `` |
| `edit_alloc` | function | `kernel/editor.c:38` | `static EditBuf *edit_alloc(const char *fname)` |
| `edit_arg_line` | function | `kernel/editor.c:213` | `static int edit_arg_line(int argc, char **argv, EditBuf *e, int *out)` |
| `edit_delete` | function | `kernel/editor.c:154` | `static int edit_delete(EditBuf *e, int idx)` |
| `edit_free` | function | `kernel/editor.c:55` | `static void edit_free(EditBuf *e)` |
| `edit_insert` | function | `kernel/editor.c:144` | `static int edit_insert(EditBuf *e, int idx, const char *text)` |
| `edit_line_cstr` | function | `kernel/editor.c:166` | `static void edit_line_cstr(EditLine *l, char *out)` |
| `edit_list` | function | `kernel/editor.c:123` | `static void edit_list(EditBuf *e, int start, int end)` |
| `edit_load` | function | `kernel/editor.c:61` | `static int edit_load(EditBuf *e)` |
| `edit_loop` | function | `kernel/editor.c:224` | `static void edit_loop(EditBuf *e)` |
| `edit_print` | function | `kernel/editor.c:113` | `static void edit_print(EditBuf *e, int idx)` |
| `edit_refuse_save` | function | `kernel/editor.c:207` | `static int edit_refuse_save(EditBuf *e)` |
| `edit_save` | function | `kernel/editor.c:99` | `static int edit_save(EditBuf *e)` |
| `edit_search` | function | `kernel/editor.c:171` | `static void edit_search(EditBuf *e, const char *needle)` |
| `edit_set_line` | function | `kernel/editor.c:135` | `static int edit_set_line(EditBuf *e, int idx, const char *text)` |
| `edit_status` | function | `kernel/editor.c:188` | `static void edit_status(EditBuf *e)` |
| `edit_usage` | function | `kernel/editor.c:196` | `static void edit_usage(void)` |
| `shell_cmd_edit` | function | `kernel/editor.c:329` | `void shell_cmd_edit(int argc, char **argv)` |
| `ETREL_CHILD_STACK_SZ` | macro | `kernel/exec.c:132` | `#define ETREL_CHILD_STACK_SZ` |
| `EXEC_KSTACK_SZ` | macro | `kernel/exec.c:123` | `#define EXEC_KSTACK_SZ` |
| `k_run_rel` | function | `kernel/exec.c:229` | `int k_run_rel(prog_entry_t entry, int argc, char **argv)` |
| `k_user_fault_return` | function | `kernel/exec.c:65` | `void k_user_fault_return(void)` |
| `kexit` | function | `kernel/exec.c:280` | `void kexit(int code)` |
| `setup_user_stack` | function | `kernel/exec.c:82` | `unsigned long *setup_user_stack(char *sbase, unsigned long ssize,                                ...` |
| `syscall_kstack` | variable | `kernel/exec.c:115` | `extern unsigned long syscall_kstack;` |
| `vga_gfx_ran_set` | function | `kernel/exec.c:62` | `void vga_gfx_ran_set(int on)` |
| `vga_mode_is_active` | function | `kernel/exec.c:61` | `int  vga_mode_is_active(void)` |
| `vga_mode_set` | function | `kernel/exec.c:60` | `void vga_mode_set(int on)` |
| `futex_bucket` | function | `kernel/futex.c:31` | `static futex_bucket_t *futex_bucket(unsigned long uaddr)` |
| `futex_hash` | function | `kernel/futex.c:23` | `static unsigned long futex_hash(unsigned long uaddr)` |
| `futex_init` | function | `kernel/futex.c:36` | `void futex_init(void)` |
| `futex_linux_cmd` | function | `kernel/futex.c:84` | `int futex_linux_cmd(long op)` |
| `futex_table_t` | struct | `kernel/futex.c:16` | `` |
| `futex_wake` | function | `kernel/futex.c:97` | `long futex_wake(unsigned long uaddr, int n)` |
| `t_cur_pid` | variable | `kernel/futex.c:13` | `extern int t_cur_pid;` |
| `klog` | function | `kernel/klog.c:41` | `void klog(log_level_t level, log_subsystem_t subsys,           const char *fmt, ...)` |
| `klog_disable` | function | `kernel/klog.c:38` | `void klog_disable(void)` |
| `klog_enable` | function | `kernel/klog.c:39` | `void klog_enable(void)` |
| `klog_hexdump` | function | `kernel/klog.c:119` | `void klog_hexdump(log_level_t level, log_subsystem_t subsys,                   const void *data, ...` |
| `klog_set_level` | function | `kernel/klog.c:29` | `void klog_set_level(log_level_t level)` |
| `klog_set_subsys_level` | function | `kernel/klog.c:33` | `void klog_set_subsys_level(log_subsystem_t subsys, log_level_t level)` |
| `LDSO_DYN_ENT` | macro | `kernel/ldso_parse.c:15` | `#define LDSO_DYN_ENT` |
| `LDSO_EHSIZE` | macro | `kernel/ldso_parse.c:13` | `#define LDSO_EHSIZE` |
| `LDSO_HASH_HDR` | macro | `kernel/ldso_parse.c:16` | `#define LDSO_HASH_HDR` |
| `LDSO_PHENTSZ` | macro | `kernel/ldso_parse.c:14` | `#define LDSO_PHENTSZ` |
| `ldso_basename` | function | `kernel/ldso_parse.c:331` | `void ldso_basename(char *out, const char *src)` |
| `ldso_copy_str` | function | `kernel/ldso_parse.c:227` | `int ldso_copy_str(const unsigned char *file, unsigned long long fsize,         unsigned long long...` |
| `ldso_find_dynamic` | function | `kernel/ldso_parse.c:120` | `int ldso_find_dynamic(const unsigned char *file, unsigned long long fsize,         unsigned long ...` |
| `ldso_name_eq` | function | `kernel/ldso_parse.c:250` | `static int ldso_name_eq(const unsigned char *tab, unsigned long long strsz,         unsigned long...` |
| `ldso_rd16` | function | `kernel/ldso_parse.c:18` | `static unsigned ldso_rd16(const unsigned char *p)` |
| `ldso_rd32` | function | `kernel/ldso_parse.c:22` | `static unsigned long ldso_rd32(const unsigned char *p)` |
| `ldso_rd64` | function | `kernel/ldso_parse.c:27` | `static unsigned long long ldso_rd64(const unsigned char *p)` |
| `ldso_read_rela` | function | `kernel/ldso_parse.c:309` | `int ldso_read_rela(const unsigned char *file, unsigned long long fsize,         unsigned long lon...` |
| `ldso_rela_count` | function | `kernel/ldso_parse.c:296` | `int ldso_rela_count(const LdsoDynInfo *info, unsigned *nrela)` |
| `ldso_scan_dynamic` | function | `kernel/ldso_parse.c:150` | `int ldso_scan_dynamic(const unsigned char *file, unsigned long long fsize,         unsigned long ...` |
| `ldso_segments` | function | `kernel/ldso_parse.c:86` | `int ldso_segments(const unsigned char *file, unsigned long long fsize,         LdsoSeg *segs, uns...` |
| `ldso_slice` | function | `kernel/ldso_parse.c:32` | `static int ldso_slice(const unsigned char *file, unsigned long long fsize,         unsigned long ...` |
| `ldso_sym_count` | function | `kernel/ldso_parse.c:213` | `int ldso_sym_count(const unsigned char *file, unsigned long long fsize,         unsigned long lon...` |
| `ldso_sym_lookup` | function | `kernel/ldso_parse.c:263` | `int ldso_sym_lookup(const unsigned char *file, unsigned long long fsize,         unsigned long lo...` |
| `ldso_vaddr_to_offset` | function | `kernel/ldso_parse.c:54` | `int ldso_vaddr_to_offset(const unsigned char *file,         unsigned long long fsize, unsigned lo...` |
| `ldso_valid_ehdr` | function | `kernel/ldso_parse.c:40` | `static int ldso_valid_ehdr(const unsigned char *file,         unsigned long long fsize)` |
| `ELF64_R_SYM` | macro | `kernel/loader.c:61` | `#define ELF64_R_SYM(i)` |
| `ELF64_R_TYPE` | macro | `kernel/loader.c:62` | `#define ELF64_R_TYPE(i)` |
| `ELF_MAX_SEGMENTS` | macro | `kernel/loader.c:94` | `#define ELF_MAX_SEGMENTS` |
| `ELF_NAME_MAX` | macro | `kernel/loader.c:95` | `#define ELF_NAME_MAX` |
| `EM_X86_64` | macro | `kernel/loader.c:80` | `#define EM_X86_64` |
| `ETREL_IMAGE_MAX` | macro | `kernel/loader.c:70` | `#define ETREL_IMAGE_MAX` |
| `Elf64_Phdr` | struct | `kernel/loader.c:50` | `` |
| `Elf64_Rela` | struct | `kernel/loader.c:44` | `` |
| `Elf64_Shdr` | struct | `kernel/loader.c:22` | `` |
| `Elf64_Sym` | struct | `kernel/loader.c:35` | `` |
| `LdsoLibEnt` | struct | `kernel/loader.c:381` | `` |
| `PF_X` | macro | `kernel/loader.c:93` | `#define PF_X` |
| `PT_LOAD` | macro | `kernel/loader.c:81` | `#define PT_LOAD` |
| `R_X86_64_32` | macro | `kernel/loader.c:89` | `#define R_X86_64_32` |
| `R_X86_64_32S` | macro | `kernel/loader.c:90` | `#define R_X86_64_32S` |
| `R_X86_64_64` | macro | `kernel/loader.c:83` | `#define R_X86_64_64` |
| `R_X86_64_GLOB_DAT` | macro | `kernel/loader.c:86` | `#define R_X86_64_GLOB_DAT` |
| `R_X86_64_IRELATIVE` | macro | `kernel/loader.c:91` | `#define R_X86_64_IRELATIVE` |
| `R_X86_64_JUMP_SLOT` | macro | `kernel/loader.c:87` | `#define R_X86_64_JUMP_SLOT` |
| `R_X86_64_PC32` | macro | `kernel/loader.c:84` | `#define R_X86_64_PC32` |
| `R_X86_64_PLT32` | macro | `kernel/loader.c:85` | `#define R_X86_64_PLT32` |
| `R_X86_64_RELATIVE` | macro | `kernel/loader.c:88` | `#define R_X86_64_RELATIVE` |
| `SHF_ALLOC` | macro | `kernel/loader.c:77` | `#define SHF_ALLOC` |
| `SHF_EXECINSTR` | macro | `kernel/loader.c:78` | `#define SHF_EXECINSTR` |
| `SHN_UNDEF` | macro | `kernel/loader.c:63` | `#define SHN_UNDEF` |
| `SHT_NOBITS` | macro | `kernel/loader.c:76` | `#define SHT_NOBITS` |
| `SHT_PROGBITS` | macro | `kernel/loader.c:75` | `#define SHT_PROGBITS` |
| `SHT_RELA` | macro | `kernel/loader.c:74` | `#define SHT_RELA` |
| `SHT_STRTAB` | macro | `kernel/loader.c:73` | `#define SHT_STRTAB` |
| `SHT_SYMTAB` | macro | `kernel/loader.c:72` | `#define SHT_SYMTAB` |
| `apply_exec_relocs` | function | `kernel/loader.c:977` | `static void apply_exec_relocs(void *data, unsigned size, unsigned long base,                     ...` |
| `base_out` | function | `kernel/loader.c:1191` | `* the link base via base_out (0 when the caller runs static images  * only: the dynamic binder ne...` |
| `consistent` | function | `kernel/loader.c:572` | `* consistent (the next exec forgets them, a dying window frees them),  * and only reports. */ sta...` |
| `elf_load` | function | `kernel/loader.c:129` | `void *elf_load(void *data, unsigned size, void **base_out)` |
| `elf_load_fail` | function | `kernel/loader.c:121` | `static void elf_load_fail(void *base, void **sec_addrs, const char *why)` |
| `elf_name_copy` | function | `kernel/loader.c:107` | `static void elf_name_copy(char *out, unsigned out_cap, const char *tab,                          ...` |
| `exec_range` | struct | `kernel/loader.c:97` | `` |
| `images` | function | `kernel/loader.c:783` | `* Static images (no dynamic section, or none needed) return 0 at * once, so the legacy paths never observe a...` |
| `inodes` | function | `kernel/loader.c:374` | `* Pseudo inodes (LDSO_INO_BASE + slot) keep registry pages apart from * MiniFS inodes in the shared cache. No unload...` |
| `ldso_bind_into` | function | `kernel/loader.c:787` | `int ldso_bind_into(void *data, unsigned size, unsigned long base,         unsigned long cr3, vma_...` |
| `ldso_ensure_slot` | function | `kernel/loader.c:476` | `static int ldso_ensure_slot(const char *needed, int *slot_out)` |
| `ldso_pseudo_read` | function | `kernel/loader.c:409` | `int ldso_pseudo_read(int ino, void *dst, unsigned long off, unsigned len)` |
| `ldso_pseudo_stat` | function | `kernel/loader.c:395` | `int ldso_pseudo_stat(int ino, unsigned long *size_out)` |
| `ldso_read_file` | function | `kernel/loader.c:434` | `static int ldso_read_file(const char *name, unsigned char **out,         unsigned *size_out)` |
| `load_exec_elf` | function | `kernel/loader.c:1060` | `void *load_exec_elf(void *data, unsigned size)` |
| `process` | function | `kernel/loader.c:1084` | `* atomic section: a 100 Hz tick between two segments would switch * CR3 into another process (copies landing in its...` |
| `time` | function | `kernel/loader.c:1262` | `* time (with the failing offset);` |
| `HASH_BITS` | macro | `kernel/lz4_kernel.c:4` | `#define HASH_BITS` |
| `HASH_SIZE` | macro | `kernel/lz4_kernel.c:5` | `#define HASH_SIZE` |
| `LZ4_compressBound` | function | `kernel/lz4_kernel.c:33` | `int LZ4_compressBound(int inputSize)` |
| `LZ4_compress_default` | function | `kernel/lz4_kernel.c:40` | `int LZ4_compress_default(const char *src, char *dst, int srcSize, int dstCapacity)` |
| `LZ4_decompress_safe` | function | `kernel/lz4_kernel.c:176` | `int LZ4_decompress_safe(const char *src, char *dst, int compressedSize, int dstCapacity)` |
| `LZ4_hash` | function | `kernel/lz4_kernel.c:26` | `static unsigned int LZ4_hash(const unsigned char *p)` |
| `LZ4_read16` | function | `kernel/lz4_kernel.c:14` | `static inline unsigned int LZ4_read16(const unsigned char *p)` |
| `LZ4_read32` | function | `kernel/lz4_kernel.c:7` | `static inline unsigned int LZ4_read32(const unsigned char *p)` |
| `LZ4_write16` | function | `kernel/lz4_kernel.c:21` | `static inline void LZ4_write16(unsigned char *dst, unsigned short v)` |
| `slots` | function | `kernel/lz4_kernel.c:43` | `* runs from file writes on 16 KB proc slots (stack discipline, * CLAUDE.md). OOM returns 0 and the caller stores...` |
| `frame` | function | `kernel/minifetch.c:159` | `* frame (stack discipline, CLAUDE.md). Fail-closed on OOM. */ char (*specs)[96] = (char (*)[96])kmalloc(20 * 96);` |
| `minifetch_cfg` | struct | `kernel/minifetch.c:21` | `` |
| `minifetch_logo` | function | `kernel/minifetch.c:81` | `static void minifetch_logo(char rows[16][33])` |
| `minifetch_row` | function | `kernel/minifetch.c:57` | `static void minifetch_row(const unsigned char *img, int w, int h, int row,                       ...` |
| `minifetch_specs` | function | `kernel/minifetch.c:101` | `static int minifetch_specs(char lines[20][96])` |
| `shell_cmd_minifetch` | function | `kernel/minifetch.c:156` | `void shell_cmd_minifetch(void)` |
| `kallocator_init` | function | `kernel/mm.c:13` | `void kallocator_init(void)` |
| `kcalloc` | function | `kernel/mm.c:49` | `void *kcalloc(unsigned long nmemb, unsigned long size)` |
| `kfree` | function | `kernel/mm.c:28` | `void kfree(void *ptr)` |
| `kfree_aligned` | function | `kernel/mm.c:81` | `void kfree_aligned(void *ptr)` |
| `kmalloc` | function | `kernel/mm.c:21` | `void *kmalloc(unsigned long size)` |

Next: [SYMBOLS_p8.md](SYMBOLS_p8.md)
