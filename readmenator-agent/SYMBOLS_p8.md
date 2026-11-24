# Symbols (page 8 of 28)
Previous: [SYMBOLS_p7.md](SYMBOLS_p7.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `VGA_FX_PROG_ONE` | macro | `headers/vga_fx.h:136` | `#define VGA_FX_PROG_ONE` |
| `longer` | function | `headers/vga_fx.h:353` | `* longer (the lag), every row follows the same smoothstep toward the  * target and narrows to gen...` |
| `vga_fx_advance` | function | `headers/vga_fx.h:71` | `static inline int vga_fx_advance(const vga_fx_config_t *cfg, int *cols, int w, int h)` |
| `vga_fx_burn_compose` | function | `headers/vga_fx.h:340` | `static inline unsigned int vga_fx_burn_compose(unsigned int base, int heat)` |
| `vga_fx_burn_pixel` | function | `headers/vga_fx.h:260` | `static inline int vga_fx_burn_pixel(const vga_fx_motion_t *cfg, int thr, int prog, int *heat)` |
| `vga_fx_burn_span` | function | `headers/vga_fx.h:230` | `static inline int vga_fx_burn_span(const vga_fx_motion_t *cfg)` |
| `vga_fx_burn_threshold` | function | `headers/vga_fx.h:241` | `static inline int vga_fx_burn_threshold(const vga_fx_motion_t *cfg, int lx, int ly, int w, int h)` |
| `vga_fx_clamp_rect` | function | `headers/vga_fx.h:109` | `static inline int vga_fx_clamp_rect(int *x, int *y, int *w, int *h, int fb_w, int fb_h)` |
| `vga_fx_config_t` | struct | `headers/vga_fx.h:16` | `` |
| `vga_fx_fire_color` | function | `headers/vga_fx.h:289` | `static inline unsigned int vga_fx_fire_color(int heat)` |
| `vga_fx_front` | function | `headers/vga_fx.h:97` | `static inline int vga_fx_front(int col_y, int h)` |
| `vga_fx_hash2` | function | `headers/vga_fx.h:191` | `static inline unsigned long vga_fx_hash2(int x, int y, unsigned long seed)` |
| `vga_fx_init_cols` | function | `headers/vga_fx.h:47` | `static inline int vga_fx_init_cols(const vga_fx_config_t *cfg, int *cols, int w)` |
| `vga_fx_mix` | function | `headers/vga_fx.h:319` | `static inline unsigned int vga_fx_mix(unsigned int a, unsigned int b, int alpha)` |
| `vga_fx_motion_t` | struct | `headers/vga_fx.h:155` | `` |
| `vga_fx_noise` | function | `headers/vga_fx.h:204` | `static inline int vga_fx_noise(int x, int y, int cell, unsigned long seed)` |
| `vga_fx_rand` | function | `headers/vga_fx.h:30` | `static inline unsigned long vga_fx_rand(unsigned long *s)` |
| `vga_fx_smooth` | function | `headers/vga_fx.h:177` | `static inline int vga_fx_smooth(int q)` |
| `VMA_H` | macro | `headers/vma.h:2` | `#define VMA_H` |
| `VMA_MAX` | macro | `headers/vma.h:31` | `#define VMA_MAX` |
| `VMA_NIL` | variable | `headers/vma.h:55` | `extern vma_node_t *VMA_NIL;` |
| `base` | type_alias | `headers/vma.h:20` | `typedef struct vma_node { unsigned long base;` |
| `vma_ctx_alloc` | function | `headers/vma.h:90` | `vma_ctx_t *vma_ctx_alloc(void);` |
| `vma_ctx_bind` | function | `headers/vma.h:70` | `void vma_ctx_bind(vma_ctx_t *c);` |
| `vma_ctx_free` | function | `headers/vma.h:91` | `void vma_ctx_free(vma_ctx_t *c);` |
| `vma_ctx_init` | function | `headers/vma.h:69` | `void vma_ctx_init(vma_ctx_t *c, vma_node_t *pool);` |
| `vma_ctx_save` | function | `headers/vma.h:71` | `void vma_ctx_save(vma_ctx_t *c);` |
| `vma_ctx_t` | struct | `headers/vma.h:44` | `` |
| `vma_free_root` | variable | `headers/vma.h:57` | `extern vma_node_t *vma_free_root;` |
| `vma_legacy` | variable | `headers/vma.h:62` | `extern vma_ctx_t vma_legacy;` |
| `vma_live_root` | variable | `headers/vma.h:56` | `extern vma_node_t *vma_live_root;` |
| `vma_node` | struct | `headers/vma.h:21` | `` |
| `vma_pool` | variable | `headers/vma.h:58` | `extern vma_node_t vma_pool[VMA_MAX];` |
| `vma_pool_n` | variable | `headers/vma.h:59` | `extern int vma_pool_n;` |
| `vma_pool_ptr` | variable | `headers/vma.h:61` | `extern vma_node_t *vma_pool_ptr;` |
| `vma_spare` | variable | `headers/vma.h:60` | `extern vma_node_t *vma_spare;` |
| `vma_tree_delete` | function | `headers/vma.h:68` | `int vma_tree_delete(vma_node_t **root, unsigned long base);` |
| `vma_tree_find` | function | `headers/vma.h:66` | `vma_node_t *vma_tree_find(vma_node_t *root, unsigned long base);` |
| `vma_tree_find_containing` | function | `headers/vma.h:67` | `vma_node_t *vma_tree_find_containing(vma_node_t *root, unsigned long va);` |
| `vma_tree_init` | function | `headers/vma.h:64` | `void vma_tree_init(void);` |
| `vma_tree_insert` | function | `headers/vma.h:65` | `vma_node_t *vma_tree_insert(vma_node_t **root, unsigned long base, unsigned long len);` |
| `vma_view_load` | function | `headers/vma.h:87` | `void vma_view_load(const vma_view_t *v);` |
| `vma_view_save` | function | `headers/vma.h:86` | `void vma_view_save(vma_view_t *v);` |
| `vma_view_t` | struct | `headers/vma.h:76` | `` |
| `WM_BLUR_CHANNEL_MASK` | macro | `headers/wm_blur.h:36` | `#define WM_BLUR_CHANNEL_MASK` |
| `WM_BLUR_CONFIG_DEFAULT` | macro | `headers/wm_blur.h:47` | `#define WM_BLUR_CONFIG_DEFAULT` |
| `WM_BLUR_H` | macro | `headers/wm_blur.h:21` | `#define WM_BLUR_H` |
| `WM_BLUR_PASSES_MAX` | macro | `headers/wm_blur.h:28` | `#define WM_BLUR_PASSES_MAX` |
| `WM_BLUR_RADIUS_MAX` | macro | `headers/wm_blur.h:25` | `#define WM_BLUR_RADIUS_MAX` |
| `WM_BLUR_RECIP_SHIFT` | macro | `headers/wm_blur.h:33` | `#define WM_BLUR_RECIP_SHIFT` |
| `wm_blur_config_t` | struct | `headers/wm_blur.h:39` | `` |
| `wm_blur_config_valid` | function | `headers/wm_blur.h:50` | `static inline int wm_blur_config_valid(const wm_blur_config_t *cfg)` |
| `wm_blur_edge` | function | `headers/wm_blur.h:84` | `static inline int wm_blur_edge(int i, int n)` |
| `wm_blur_line` | function | `headers/wm_blur.h:93` | `static inline void wm_blur_line(unsigned int *px, long stride, int n, int radius,                ...` |
| `wm_blur_line_len` | function | `headers/wm_blur.h:58` | `static inline unsigned long wm_blur_line_len(int w, int h)` |
| `wm_blur_recip` | function | `headers/wm_blur.h:68` | `static inline unsigned long wm_blur_recip(int win)` |
| `WM_CHROME_ALPHA_OPAQUE` | macro | `headers/wm_chrome.h:15` | `#define WM_CHROME_ALPHA_OPAQUE` |
| `WM_CHROME_CONFIG_DEFAULT` | macro | `headers/wm_chrome.h:35` | `#define WM_CHROME_CONFIG_DEFAULT` |
| `WM_CHROME_H` | macro | `headers/wm_chrome.h:12` | `#define WM_CHROME_H` |
| `WM_CHROME_RADIUS_MAX` | macro | `headers/wm_chrome.h:38` | `#define WM_CHROME_RADIUS_MAX` |
| `by` | function | `headers/wm_chrome.h:107` | `* The shadow is the window rect shifted by (dx,dy);` |
| `wm_chrome_blend` | function | `headers/wm_chrome.h:76` | `static inline unsigned long wm_chrome_blend(unsigned long dst, unsigned long src, int alpha)` |
| `wm_chrome_blend_channel` | function | `headers/wm_chrome.h:67` | `static inline int wm_chrome_blend_channel(int dst, int src, int alpha)` |
| `wm_chrome_clamp` | function | `headers/wm_chrome.h:61` | `static inline int wm_chrome_clamp(int v)` |
| `wm_chrome_config_t` | struct | `headers/wm_chrome.h:18` | `` |
| `wm_chrome_corner_coverage` | function | `headers/wm_chrome.h:141` | `static inline int wm_chrome_corner_coverage(int radius, int x, int y)` |
| `wm_chrome_disc_coverage` | function | `headers/wm_chrome.h:162` | `static inline int wm_chrome_disc_coverage(int radius, int x, int y)` |
| `wm_chrome_gradient` | function | `headers/wm_chrome.h:95` | `static inline unsigned long wm_chrome_gradient(unsigned long base, int row, int span,            ...` |
| `wm_chrome_isqrt` | function | `headers/wm_chrome.h:41` | `static inline unsigned long wm_chrome_isqrt(unsigned long v)` |
| `wm_chrome_shadow_alpha` | function | `headers/wm_chrome.h:110` | `static inline int wm_chrome_shadow_alpha(const wm_chrome_config_t *cfg, int px, int py,          ...` |
| `wm_chrome_shift` | function | `headers/wm_chrome.h:85` | `static inline unsigned long wm_chrome_shift(unsigned long px, int delta)` |
| `WM_DOCK_ALPHA_OPAQUE` | macro | `headers/wm_dock.h:34` | `#define WM_DOCK_ALPHA_OPAQUE` |
| `WM_DOCK_FRAC_ONE` | macro | `headers/wm_dock.h:31` | `#define WM_DOCK_FRAC_ONE` |
| `WM_DOCK_H` | macro | `headers/wm_dock.h:18` | `#define WM_DOCK_H` |
| `WM_DOCK_LEVEL_ONE` | macro | `headers/wm_dock.h:21` | `#define WM_DOCK_LEVEL_ONE` |
| `WM_DOCK_REACH_MAX` | macro | `headers/wm_dock.h:25` | `#define WM_DOCK_REACH_MAX` |
| `WM_DOCK_SIZE_MAX` | macro | `headers/wm_dock.h:28` | `#define WM_DOCK_SIZE_MAX` |
| `wm_dock_abs` | function | `headers/wm_dock.h:46` | `static inline long wm_dock_abs(long v)` |
| `wm_dock_config_t` | struct | `headers/wm_dock.h:39` | `` |
| `wm_dock_level` | function | `headers/wm_dock.h:61` | `static inline int wm_dock_level(int from, int rising, unsigned long elapsed,                     ...` |
| `wm_dock_level_clamp` | function | `headers/wm_dock.h:52` | `static inline int wm_dock_level_clamp(long level)` |
| `wm_dock_mag_size` | function | `headers/wm_dock.h:78` | `static inline int wm_dock_mag_size(const wm_dock_config_t *cfg, long dist, int level)` |
| `wm_dock_sample` | function | `headers/wm_dock.h:120` | `static inline unsigned long wm_dock_sample(const unsigned char *rgba, int sw, int sh,            ...` |
| `wm_dock_src_coord` | function | `headers/wm_dock.h:104` | `static inline long wm_dock_src_coord(int o, int d, int s)` |
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
| `WM_JELLY_CONFIG_DEFAULT` | macro | `headers/wm_jelly.h:48` | `#define WM_JELLY_CONFIG_DEFAULT` |
| `WM_JELLY_FP` | macro | `headers/wm_jelly.h:22` | `#define WM_JELLY_FP` |
| `WM_JELLY_GRID` | macro | `headers/wm_jelly.h:19` | `#define WM_JELLY_GRID` |
| `WM_JELLY_H` | macro | `headers/wm_jelly.h:16` | `#define WM_JELLY_H` |
| `WM_JELLY_WEIGHT_ONE` | macro | `headers/wm_jelly.h:25` | `#define WM_JELLY_WEIGHT_ONE` |
| `wm_jelly_abs` | function | `headers/wm_jelly.h:71` | `static inline int wm_jelly_abs(int v)` |
| `wm_jelly_at_rest` | function | `headers/wm_jelly.h:186` | `static inline int wm_jelly_at_rest(const wm_jelly_config_t *cfg, const wm_jelly_t *j)` |
| `wm_jelly_clamp` | function | `headers/wm_jelly.h:59` | `static inline int wm_jelly_clamp(int v, int lim)` |
| `wm_jelly_config_t` | struct | `headers/wm_jelly.h:33` | `` |
| `wm_jelly_neighbours` | function | `headers/wm_jelly.h:130` | `static inline int wm_jelly_neighbours(const int *d, int r, int c)` |
| `wm_jelly_reset` | function | `headers/wm_jelly.h:77` | `static inline void wm_jelly_reset(wm_jelly_t *j)` |
| `wm_jelly_sample` | function | `headers/wm_jelly.h:203` | `static inline void wm_jelly_sample(const wm_jelly_t *j, int x, int y, int w, int h,              ...` |
| `wm_jelly_step` | function | `headers/wm_jelly.h:155` | `static inline void wm_jelly_step(const wm_jelly_config_t *cfg, wm_jelly_t *j)` |
| `wm_jelly_t` | struct | `headers/wm_jelly.h:51` | `` |
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
| `BOOTLOG_MAX` | macro | `kernel.c:189` | `#define BOOTLOG_MAX` |
| `KSYM_MAX` | macro | `kernel.c:108` | `#define KSYM_MAX` |
| `__attribute__` | function | `kernel.c:208` | `__attribute__((section(".init.text"))) void kmain(void)` |
| `bootlog_mark` | function | `kernel.c:193` | `void bootlog_mark(const char *name)` |
| `bootlog_report` | function | `kernel.c:200` | `void bootlog_report(void)` |
| `kstack` | function | `kernel.c:147` | `* Reading gs:8 instead resolves every thread to the wrong kstack (0 on * the BSP, 1 on APs): harmless while a single...` |
| `ksyscall` | function | `kernel.c:131` | `extern long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6);` |
| `ms` | function | `kernel.c:186` | `* 0 ms (TSC ticks since power-on divided down, still monotonic);` |
| `ramdisk_end` | variable | `kernel.c:181` | `extern char ramdisk_end[];` |
| `ramdisk_start` | variable | `kernel.c:180` | `extern char ramdisk_start[];` |
| `size` | function | `kernel.c:258` | `* image size (see kernel.ld);` |
| `syscall_init` | function | `kernel.c:118` | `void syscall_init(void)` |
| `syscall_kstack` | variable | `kernel.c:116` | `extern unsigned long syscall_kstack;` |
| `table` | function | `kernel.c:105` | `* Symbol table (for resolving program references) * ================================================================...` |
| `tables` | function | `kernel.c:280` | `* tables (already built above) for its uncached register window and the      * heap for its rings...` |
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
| `VGA_LINE_MAX` | macro | `kernel/console.c:226` | `#define VGA_LINE_MAX` |
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
| `register_libc_symbols` | function | `kernel/console.c:287` | `void register_libc_symbols(void)` |
| `vga_clear` | function | `kernel/console.c:25` | `void vga_clear(void)` |
| `vga_cursor_enable` | function | `kernel/console.c:81` | `void vga_cursor_enable(int on)` |
| `vga_get_color` | function | `kernel/console.c:21` | `char vga_get_color(void)` |
| `vga_get_x` | function | `kernel/console.c:18` | `int vga_get_x(void)` |
| `vga_get_y` | function | `kernel/console.c:19` | `int vga_get_y(void)` |
| `vga_line_feed` | function | `kernel/console.c:231` | `static void vga_line_feed(void)` |
| `vga_newline` | function | `kernel/console.c:75` | `void vga_newline(void)` |
| `vga_offset` | function | `kernel/console.c:23` | `static inline unsigned vga_offset(int x, int y)` |
| `vga_putc` | function | `kernel/console.c:237` | `void vga_putc(char c)` |
| `vga_puts` | function | `kernel/console.c:283` | `void vga_puts(const char *s)` |
| `vga_raw_space` | function | `kernel/console.c:88` | `static void vga_raw_space(void)` |
| `vga_scroll` | function | `kernel/console.c:56` | `void vga_scroll(void)` |
| `vga_set_cursor` | function | `kernel/console.c:36` | `void vga_set_cursor(int x, int y)` |
| `vga_set_xy` | function | `kernel/console.c:20` | `void vga_set_xy(int x, int y)` |
| `ESC` | function | `kernel/console_in.c:157` | `* The bound keeps a bare ESC (never completed into a sequence) from  * hanging the reader. */ #de...` |
| `MAX_SEQ_POLL` | macro | `kernel/console_in.c:159` | `#define MAX_SEQ_POLL` |
| `PB_LEN` | macro | `kernel/console_in.c:18` | `#define PB_LEN` |
| `SB_EXIT` | macro | `kernel/console_in.c:320` | `#define SB_EXIT` |
| `SB_LEN` | macro | `kernel/console_in.c:295` | `#define SB_LEN` |
| `SB_PGDN` | macro | `kernel/console_in.c:319` | `#define SB_PGDN` |
| `SB_PGUP` | macro | `kernel/console_in.c:318` | `#define SB_PGUP` |
| `console_getc` | function | `kernel/console_in.c:217` | `int console_getc(void)` |
| `console_history_page` | function | `kernel/console_in.c:204` | `void console_history_page(int dir)` |
| `console_job_get` | function | `kernel/console_in.c:281` | `int console_job_get(void)` |
| `console_job_try` | function | `kernel/console_in.c:271` | `int console_job_try(void)` |
| `console_peek` | function | `kernel/console_in.c:247` | `int console_peek(void)` |
| `console_poll_usb` | function | `kernel/console_in.c:93` | `static void console_poll_usb(void)` |
| `console_ps2_live` | function | `kernel/console_in.c:106` | `static int console_ps2_live(void)` |
| `console_raw_get` | function | `kernel/console_in.c:264` | `int console_raw_get(void)` |
| `console_raw_try` | function | `kernel/console_in.c:260` | `int console_raw_try(void)` |
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
| `sb_next` | function | `kernel/console_in.c:325` | `static int sb_next(void)` |
| `scrollback_render` | function | `kernel/console_in.c:297` | `static void scrollback_render(int voff, int total, const unsigned char *saved)` |
| `scrollback_view` | function | `kernel/console_in.c:335` | `static void scrollback_view(int initial_dir)` |
| `cvm_main` | function | `kernel/cvm_host.c:497` | `int cvm_main(int argc, char **argv)` |
| `kformat` | function | `kernel/cvm_host.c:313` | `static void kformat(void *ctx, const char *fmt, uint64_t *argv, int argc)` |
| `kout_char` | function | `kernel/cvm_host.c:288` | `static void kout_char(void *ctx, char c)` |
| `kout_sink` | struct | `kernel/cvm_host.c:281` | `` |
| `kout_uint` | function | `kernel/cvm_host.c:300` | `static void kout_uint(void *ctx, unsigned long long v, int base, int upper)` |
| `n_atol` | function | `kernel/cvm_host.c:236` | `static int64_t n_atol(void *vm, int ac, uint64_t *av)` |
| `n_calloc` | function | `kernel/cvm_host.c:98` | `static int64_t n_calloc(void *vm, int ac, uint64_t *av)` |
| `n_exit` | function | `kernel/cvm_host.c:114` | `static int64_t n_exit(void *vm, int ac, uint64_t *av)` |
| `n_fclose` | function | `kernel/cvm_host.c:128` | `static int64_t n_fclose(void *vm, int ac, uint64_t *av)` |
| `n_fflush` | function | `kernel/cvm_host.c:191` | `static int64_t n_fflush(void *vm, int ac, uint64_t *av)` |
| `n_fgetc` | function | `kernel/cvm_host.c:179` | `static int64_t n_fgetc(void *vm, int ac, uint64_t *av)` |
| `n_fopen` | function | `kernel/cvm_host.c:121` | `static int64_t n_fopen(void *vm, int ac, uint64_t *av)` |
| `n_fprintf` | function | `kernel/cvm_host.c:390` | `static int64_t n_fprintf(void *vm, int ac, uint64_t *av)` |
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
| `n_printf` | function | `kernel/cvm_host.c:403` | `static int64_t n_printf(void *vm, int ac, uint64_t *av)` |
| `n_putchar` | function | `kernel/cvm_host.c:197` | `static int64_t n_putchar(void *vm, int ac, uint64_t *av)` |
| `n_puts` | function | `kernel/cvm_host.c:228` | `static int64_t n_puts(void *vm, int ac, uint64_t *av)` |
| `n_read` | function | `kernel/cvm_host.c:213` | `static int64_t n_read(void *vm, int ac, uint64_t *av)` |
| `n_realloc` | function | `kernel/cvm_host.c:106` | `static int64_t n_realloc(void *vm, int ac, uint64_t *av)` |
| `n_rewind` | function | `kernel/cvm_host.c:160` | `static int64_t n_rewind(void *vm, int ac, uint64_t *av)` |
| `n_sprintf` | function | `kernel/cvm_host.c:418` | `static int64_t n_sprintf(void *vm, int ac, uint64_t *av)` |
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
| `register_host_natives` | function | `kernel/cvm_host.c:452` | `static void register_host_natives(CvmState *vm)` |
| `ed25519_verify` | function | `kernel/ed25519.c:810` | `int ed25519_verify(const unsigned char sig[64], const unsigned char *msg,                    unsi...` |
| `ed_bytes_lt_q` | function | `kernel/ed25519.c:477` | `static unsigned ed_bytes_lt_q(const unsigned char b[32])` |
| `ed_curve_d` | function | `kernel/ed25519.c:706` | `static void ed_curve_d(ed_fe *d)` |
| `ed_fe` | struct | `kernel/ed25519.c:28` | `` |
| `ed_fe_add` | function | `kernel/ed25519.c:280` | `static void ed_fe_add(ed_fe *r, const ed_fe *a, const ed_fe *b)` |
| `ed_fe_cmov` | function | `kernel/ed25519.c:238` | `static void ed_fe_cmov(ed_fe *r, const ed_fe *b, unsigned flag)` |
| `ed_fe_copy` | function | `kernel/ed25519.c:214` | `static void ed_fe_copy(ed_fe *r, const ed_fe *a)` |
| `ed_fe_eq` | function | `kernel/ed25519.c:470` | `static unsigned ed_fe_eq(const ed_fe *a, const ed_fe *b)` |
| `ed_fe_fold` | function | `kernel/ed25519.c:344` | `static void ed_fe_fold(ed_fe *r, ed_u64 w[8])` |
| `ed_fe_frombytes` | function | `kernel/ed25519.c:449` | `static void ed_fe_frombytes(ed_fe *r, const unsigned char b[32])` |
| `ed_fe_ge` | function | `kernel/ed25519.c:247` | `static unsigned ed_fe_ge(const ed_fe *a, const ed_fe *b)` |
| `ed_fe_inv` | function | `kernel/ed25519.c:438` | `static void ed_fe_inv(ed_fe *r, const ed_fe *a)` |
| `ed_fe_mul` | function | `kernel/ed25519.c:387` | `static void ed_fe_mul(ed_fe *r, const ed_fe *a, const ed_fe *b)` |
| `ed_fe_one` | function | `kernel/ed25519.c:230` | `static void ed_fe_one(ed_fe *r)` |
| `ed_fe_pow` | function | `kernel/ed25519.c:421` | `static void ed_fe_pow(ed_fe *r, const ed_fe *a, const unsigned char *bits, unsigned nbits)` |
| `ed_fe_rawsub` | function | `kernel/ed25519.c:258` | `static void ed_fe_rawsub(ed_fe *r, const ed_fe *a, const ed_fe *b)` |
| `ed_fe_sq` | function | `kernel/ed25519.c:416` | `static void ed_fe_sq(ed_fe *r, const ed_fe *a)` |
| `ed_fe_sub` | function | `kernel/ed25519.c:302` | `static void ed_fe_sub(ed_fe *r, const ed_fe *a, const ed_fe *b)` |
| `ed_fe_tobytes` | function | `kernel/ed25519.c:461` | `static void ed_fe_tobytes(unsigned char b[32], const ed_fe *a)` |
| `ed_fe_zero` | function | `kernel/ed25519.c:222` | `static void ed_fe_zero(ed_fe *r)` |
| `ed_ge` | struct | `kernel/ed25519.c:32` | `` |
| `ed_ge_add` | function | `kernel/ed25519.c:612` | `static void ed_ge_add(ed_ge *r, const ed_ge *p, const ed_ge *q, const ed_fe *d2)` |
| `ed_ge_cmov` | function | `kernel/ed25519.c:604` | `static void ed_ge_cmov(ed_ge *r, const ed_ge *b, unsigned flag)` |
| `ed_ge_copy` | function | `kernel/ed25519.c:596` | `static void ed_ge_copy(ed_ge *r, const ed_ge *a)` |
| `ed_ge_double` | function | `kernel/ed25519.c:644` | `static void ed_ge_double(ed_ge *r, const ed_ge *p)` |
| `ed_ge_scalarmult` | function | `kernel/ed25519.c:686` | `static void ed_ge_scalarmult(ed_ge *r, const ed_ge *p, const unsigned char s[32],                ...` |
| `ed_mod_l` | function | `kernel/ed25519.c:557` | `static void ed_mod_l(ed_fe *r, const unsigned char h[64])` |
| `ed_rem_ge` | function | `kernel/ed25519.c:545` | `static unsigned ed_rem_ge(const ed_u64 a[5], const ed_u64 b[5])` |
| `ed_rem_sub` | function | `kernel/ed25519.c:517` | `static void ed_rem_sub(ed_u64 r[5], const ed_u64 a[5], const ed_u64 b[5])` |
| `ed_rotr` | function | `kernel/ed25519.c:84` | `static ed_u64 ed_rotr(ed_u64 x, unsigned n)` |
| `ed_scalar_lt_l` | function | `kernel/ed25519.c:495` | `static unsigned ed_scalar_lt_l(const unsigned char b[32])` |
| `ed_sha512_final` | function | `kernel/ed25519.c:188` | `void ed_sha512_final(ed_sha *c, unsigned char out[64])` |
| `ed_sha512_init` | function | `kernel/ed25519.c:147` | `void ed_sha512_init(ed_sha *c)` |
| `ed_sha512_update` | function | `kernel/ed25519.c:162` | `void ed_sha512_update(ed_sha *c, const unsigned char *data, unsigned long len)` |
| `ed_sha_block` | function | `kernel/ed25519.c:89` | `static void ed_sha_block(ed_sha *c, const unsigned char *p)` |
| `ed_u64` | type_alias | `kernel/ed25519.c:23` | `typedef unsigned long long ed_u64;` |
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
| `ETREL_CHILD_STACK_SZ` | macro | `kernel/exec.c:133` | `#define ETREL_CHILD_STACK_SZ` |
| `EXEC_KSTACK_SZ` | macro | `kernel/exec.c:124` | `#define EXEC_KSTACK_SZ` |
| `k_run_rel` | function | `kernel/exec.c:233` | `int k_run_rel(prog_entry_t entry, int argc, char **argv)` |
| `k_user_fault_return` | function | `kernel/exec.c:66` | `void k_user_fault_return(void)` |
| `kexit` | function | `kernel/exec.c:284` | `void kexit(int code)` |
| `setup_user_stack` | function | `kernel/exec.c:83` | `unsigned long *setup_user_stack(char *sbase, unsigned long ssize,                                ...` |
| `syscall_kstack` | variable | `kernel/exec.c:116` | `extern unsigned long syscall_kstack;` |
| `vga_gfx_ran_set` | function | `kernel/exec.c:63` | `void vga_gfx_ran_set(int on)` |
| `vga_mode_is_active` | function | `kernel/exec.c:62` | `int  vga_mode_is_active(void)` |
| `vga_mode_set` | function | `kernel/exec.c:61` | `void vga_mode_set(int on)` |
| `futex_bucket` | function | `kernel/futex.c:31` | `static futex_bucket_t *futex_bucket(unsigned long uaddr)` |
| `futex_forget` | function | `kernel/futex.c:76` | `void futex_forget(int pid)` |
| `futex_hash` | function | `kernel/futex.c:23` | `static unsigned long futex_hash(unsigned long uaddr)` |
| `futex_init` | function | `kernel/futex.c:36` | `void futex_init(void)` |
| `futex_linux_cmd` | function | `kernel/futex.c:128` | `int futex_linux_cmd(long op)` |
| `futex_table_t` | struct | `kernel/futex.c:16` | `` |
| `futex_timeout_remaining_us` | function | `kernel/futex.c:139` | `long futex_timeout_remaining_us(int cmd, long sec, long nsec, unsigned long now_us)` |
| `futex_unlink_locked` | function | `kernel/futex.c:50` | `static void futex_unlink_locked(futex_bucket_t *b, int pid)` |
| `futex_wake` | function | `kernel/futex.c:158` | `long futex_wake(unsigned long uaddr, int n)` |
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
| `ELF64_R_SYM` | macro | `kernel/loader.c:62` | `#define ELF64_R_SYM(i)` |
| `ELF64_R_TYPE` | macro | `kernel/loader.c:63` | `#define ELF64_R_TYPE(i)` |
| `ELF_MAX_SEGMENTS` | macro | `kernel/loader.c:101` | `#define ELF_MAX_SEGMENTS` |
| `ELF_NAME_MAX` | macro | `kernel/loader.c:102` | `#define ELF_NAME_MAX` |
| `ELF_NOTE_ALIGN` | macro | `kernel/loader.c:88` | `#define ELF_NOTE_ALIGN` |
| `ELF_NOTE_HDR` | macro | `kernel/loader.c:87` | `#define ELF_NOTE_HDR` |
| `EM_X86_64` | macro | `kernel/loader.c:81` | `#define EM_X86_64` |
| `ETREL_IMAGE_MAX` | macro | `kernel/loader.c:71` | `#define ETREL_IMAGE_MAX` |
| `Elf64_Phdr` | struct | `kernel/loader.c:51` | `` |
| `Elf64_Rela` | struct | `kernel/loader.c:45` | `` |
| `Elf64_Shdr` | struct | `kernel/loader.c:23` | `` |
| `Elf64_Sym` | struct | `kernel/loader.c:36` | `` |
| `LdsoLibEnt` | struct | `kernel/loader.c:388` | `` |
| `PF_X` | macro | `kernel/loader.c:100` | `#define PF_X` |
| `PT_LOAD` | macro | `kernel/loader.c:82` | `#define PT_LOAD` |
| `PT_NOTE` | macro | `kernel/loader.c:83` | `#define PT_NOTE` |
| `R_X86_64_32` | macro | `kernel/loader.c:96` | `#define R_X86_64_32` |
| `R_X86_64_32S` | macro | `kernel/loader.c:97` | `#define R_X86_64_32S` |
| `R_X86_64_64` | macro | `kernel/loader.c:90` | `#define R_X86_64_64` |
| `R_X86_64_GLOB_DAT` | macro | `kernel/loader.c:93` | `#define R_X86_64_GLOB_DAT` |
| `R_X86_64_IRELATIVE` | macro | `kernel/loader.c:98` | `#define R_X86_64_IRELATIVE` |
| `R_X86_64_JUMP_SLOT` | macro | `kernel/loader.c:94` | `#define R_X86_64_JUMP_SLOT` |
| `R_X86_64_PC32` | macro | `kernel/loader.c:91` | `#define R_X86_64_PC32` |
| `R_X86_64_PLT32` | macro | `kernel/loader.c:92` | `#define R_X86_64_PLT32` |
| `R_X86_64_RELATIVE` | macro | `kernel/loader.c:95` | `#define R_X86_64_RELATIVE` |
| `SHF_ALLOC` | macro | `kernel/loader.c:78` | `#define SHF_ALLOC` |
| `SHF_EXECINSTR` | macro | `kernel/loader.c:79` | `#define SHF_EXECINSTR` |
| `SHN_UNDEF` | macro | `kernel/loader.c:64` | `#define SHN_UNDEF` |
| `SHT_NOBITS` | macro | `kernel/loader.c:77` | `#define SHT_NOBITS` |
| `SHT_NOTE` | macro | `kernel/loader.c:1067` | `#define SHT_NOTE` |
| `SHT_PROGBITS` | macro | `kernel/loader.c:76` | `#define SHT_PROGBITS` |
| `SHT_RELA` | macro | `kernel/loader.c:75` | `#define SHT_RELA` |
| `SHT_STRTAB` | macro | `kernel/loader.c:74` | `#define SHT_STRTAB` |
| `SHT_SYMTAB` | macro | `kernel/loader.c:73` | `#define SHT_SYMTAB` |
| `SIGN_NOTE_NAME` | macro | `kernel/loader.c:1069` | `#define SIGN_NOTE_NAME` |
| `apply_exec_relocs` | function | `kernel/loader.c:984` | `static void apply_exec_relocs(void *data, unsigned size, unsigned long base,                     ...` |
| `base_out` | function | `kernel/loader.c:1395` | `* the link base via base_out (0 when the caller runs static images  * only: the dynamic binder ne...` |
| `consistent` | function | `kernel/loader.c:579` | `* consistent (the next exec forgets them, a dying window frees them),  * and only reports. */ sta...` |
| `elf_load` | function | `kernel/loader.c:136` | `void *elf_load(void *data, unsigned size, void **base_out)` |
| `elf_load_fail` | function | `kernel/loader.c:128` | `static void elf_load_fail(void *base, void **sec_addrs, const char *why)` |
| `elf_name_copy` | function | `kernel/loader.c:114` | `static void elf_name_copy(char *out, unsigned out_cap, const char *tab,                          ...` |
| `elf_note_pad` | function | `kernel/loader.c:1072` | `static unsigned long elf_note_pad(unsigned long n)` |
| `elf_sign_note_find` | function | `kernel/loader.c:1108` | `static int elf_sign_note_find(const unsigned char *img, unsigned size,                           ...` |
| `elf_sign_note_span` | function | `kernel/loader.c:1083` | `static int elf_sign_note_span(const unsigned char *img, unsigned long off,                       ...` |
| `elf_sign_section_find` | function | `kernel/loader.c:1132` | `static int elf_sign_section_find(const unsigned char *img, unsigned size,                        ...` |
| `elf_sign_u32` | function | `kernel/loader.c:1181` | `static void elf_sign_u32(ed_sha *c, unsigned v)` |

Next: [SYMBOLS_p9.md](SYMBOLS_p9.md)
