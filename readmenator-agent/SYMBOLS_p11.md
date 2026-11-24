# Symbols (page 11 of 28)
Previous: [SYMBOLS_p10.md](SYMBOLS_p10.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `lg_push` | function | `kernel/vga_fb.c:328` | `static void lg_push(const char *line, int len)` |
| `line` | function | `kernel/vga_fb.c:3533` | `* display stale bytes left over from a longer previous line (e.g. the prompt  * would show the ta...` |
| `line_at` | function | `kernel/vga_fb.c:416` | `static const char *line_at(int abs, int *off)` |
| `line_nrows` | function | `kernel/vga_fb.c:380` | `static int line_nrows(int len)` |
| `mouse_apply_wheel` | function | `kernel/vga_fb.c:5251` | `static void mouse_apply_wheel(int wheel, int step)` |
| `mouse_drag_gfx` | function | `kernel/vga_fb.c:5275` | `static void mouse_drag_gfx(const wm_geom_config_t *gcfg, int mx, int my)` |
| `mouse_drag_term` | function | `kernel/vga_fb.c:5332` | `static void mouse_drag_term(const wm_geom_config_t *gcfg, int win_w, int mx, int my, int gfx_cursor)` |
| `mouse_focus_topmost` | function | `kernel/vga_fb.c:5225` | `static int mouse_focus_topmost(int mx, int my)` |
| `mouse_scrollbar` | function | `kernel/vga_fb.c:5355` | `static void mouse_scrollbar(const wm_geom_config_t *gcfg, int mx, int my)` |
| `path` | function | `kernel/vga_fb.c:5404` | `* present path (blit_gfx_buf) is the sole cursor painter. The tick * used to share the sprite state with it and...` |
| `pipe_field` | function | `kernel/vga_fb.c:4597` | `static const char *pipe_field(const char *line, int idx, char *buf, int buflen)` |
| `pointer` | function | `kernel/vga_fb.c:5272` | `* tiled window floats it at native size under the pointer (the grab point * keeps its relative position along the...` |
| `render_blank_row` | function | `kernel/vga_fb.c:3412` | `static void render_blank_row(int vrow)` |
| `render_row` | function | `kernel/vga_fb.c:3422` | `static void render_row(int vrow, int abs)` |
| `shcmd_base` | function | `kernel/vga_fb.c:707` | `static void shcmd_base(const char *cmd, char *out, unsigned long cap)` |
| `shortcut_cell_left` | function | `kernel/vga_fb.c:4740` | `static int shortcut_cell_left(int i)` |
| `shortcut_draw_scaled` | function | `kernel/vga_fb.c:4803` | `static void shortcut_draw_scaled(const struct desktop_shortcut *sc,                              ...` |
| `shortcuts_layout` | function | `kernel/vga_fb.c:4722` | `static void shortcuts_layout(void)` |
| `state` | function | `kernel/vga_fb.c:5518` | `* ignores the button state (the arming press is consumed) and settles      * once on expiry, so t...` |
| `strip_compose_begin` | function | `kernel/vga_fb.c:5120` | `static int strip_compose_begin(void)` |
| `strip_compose_end` | function | `kernel/vga_fb.c:5131` | `static void strip_compose_end(int owner, int x, int y, int w, int h)` |
| `taskbar` | function | `kernel/vga_fb.c:2754` | `* minimize hides the app to the taskbar (it never closes it), maximize  * toggles true fullscreen...` |
| `taskbar_handle_click` | function | `kernel/vga_fb.c:3316` | `static void taskbar_handle_click(int mx, int my)` |
| `taskbar_layout` | function | `kernel/vga_fb.c:3120` | `static void taskbar_layout(void)` |
| `taskbar_render` | function | `kernel/vga_fb.c:3160` | `static void taskbar_render(void)` |
| `taskbar_theme_cycle` | function | `kernel/vga_fb.c:3276` | `static void taskbar_theme_cycle(void)` |
| `taskbar_tick` | function | `kernel/vga_fb.c:3239` | `static void taskbar_tick(void)` |
| `term_close_default` | function | `kernel/vga_fb.c:4307` | `static void term_close_default(void)` |
| `term_finish_layout` | function | `kernel/vga_fb.c:4391` | `static void term_finish_layout(void)` |
| `term_max_cols` | function | `kernel/vga_fb.c:4382` | `static int term_max_cols(void)` |
| `term_max_rows` | function | `kernel/vga_fb.c:4386` | `static int term_max_rows(void)` |
| `term_recalc` | function | `kernel/vga_fb.c:3061` | `static void term_recalc(void)` |
| `term_render` | function | `kernel/vga_fb.c:3457` | `static void term_render(void)` |
| `term_render_active` | function | `kernel/vga_fb.c:3490` | `static void term_render_active(void)` |
| `term_toggle_fullscreen` | function | `kernel/vga_fb.c:4215` | `static void term_toggle_fullscreen(void)` |
| `term_toggle_minimize` | function | `kernel/vga_fb.c:4238` | `static void term_toggle_minimize(void)` |
| `termwin_t` | struct | `kernel/vga_fb.c:1061` | `` |
| `text_px` | function | `kernel/vga_fb.c:2171` | `static void text_px(int px, int py, const char *s, uint8_t fg, uint8_t bg)` |
| `title` | function | `kernel/vga_fb.c:3170` | `* 8px row plus its title (bright when focused). The hint line * starts after it instead of underneath. */ const...` |
| `total_rows` | function | `kernel/vga_fb.c:390` | `static int total_rows(void)` |
| `tw_hit` | function | `kernel/vga_fb.c:1732` | `static int tw_hit(int i, int mx, int my)` |
| `tw_park` | function | `kernel/vga_fb.c:1118` | `static void tw_park(int i)` |
| `tw_select` | function | `kernel/vga_fb.c:1208` | `static void tw_select(int i)` |
| `tw_unpark` | function | `kernel/vga_fb.c:1148` | `static void tw_unpark(int i)` |
| `vga_fb_act_empty` | function | `kernel/vga_fb.c:1672` | `int vga_fb_act_empty(void)` |
| `vga_fb_blit_gfx_window` | function | `kernel/vga_fb.c:3037` | `void vga_fb_blit_gfx_window(void)` |
| `vga_fb_blit_nk_rgb_window` | function | `kernel/vga_fb.c:3052` | `void vga_fb_blit_nk_rgb_window(void)` |
| `vga_fb_blit_nk_window` | function | `kernel/vga_fb.c:3046` | `void vga_fb_blit_nk_window(void)` |
| `vga_fb_boot_config` | function | `kernel/vga_fb.c:98` | `void vga_fb_boot_config(void)` |
| `vga_fb_boot_history_to_active` | function | `kernel/vga_fb.c:1337` | `static void vga_fb_boot_history_to_active(void)` |
| `vga_fb_char` | function | `kernel/vga_fb.c:2130` | `void vga_fb_char(int col, int row, char c, uint8_t fg, uint8_t bg)` |
| `vga_fb_clear` | function | `kernel/vga_fb.c:2089` | `void vga_fb_clear(void)` |
| `vga_fb_clear_prompt` | function | `kernel/vga_fb.c:1681` | `void vga_fb_clear_prompt(void)` |
| `vga_fb_close_active` | function | `kernel/vga_fb.c:4323` | `int vga_fb_close_active(void)` |
| `vga_fb_draw_desktop` | function | `kernel/vga_fb.c:3889` | `void vga_fb_draw_desktop(void)` |
| `vga_fb_focus_event` | function | `kernel/vga_fb.c:1103` | `const wm_notify_event_t *vga_fb_focus_event(void)` |
| `vga_fb_focus_get` | function | `kernel/vga_fb.c:1220` | `int vga_fb_focus_get(void)` |
| `vga_fb_focus_id` | function | `kernel/vga_fb.c:1302` | `int vga_fb_focus_id(int id)` |
| `vga_fb_focus_next` | function | `kernel/vga_fb.c:1237` | `void vga_fb_focus_next(void)` |
| `vga_fb_focus_report` | function | `kernel/vga_fb.c:1109` | `void vga_fb_focus_report(int before, int source)` |
| `vga_fb_gfx_cursor_draw` | function | `kernel/vga_fb.c:892` | `static void vga_fb_gfx_cursor_draw(void)` |
| `vga_fb_gfx_cursor_erase` | function | `kernel/vga_fb.c:882` | `static void vga_fb_gfx_cursor_erase(void)` |
| `vga_fb_gfx_map_mouse` | function | `kernel/vga_fb.c:867` | `void vga_fb_gfx_map_mouse(int *x, int *y)` |
| `vga_fb_gfx_origin` | function | `kernel/vga_fb.c:850` | `void vga_fb_gfx_origin(int *x, int *y)` |
| `vga_fb_gfx_set_hidden` | function | `kernel/vga_fb.c:4153` | `int vga_fb_gfx_set_hidden(int hide)` |
| `vga_fb_gfx_view_name` | function | `kernel/vga_fb.c:4203` | `const char *vga_fb_gfx_view_name(void)` |
| `vga_fb_hide_text_cursor` | function | `kernel/vga_fb.c:3613` | `void vga_fb_hide_text_cursor(void)` |
| `vga_fb_history_page` | function | `kernel/vga_fb.c:5658` | `void vga_fb_history_page(int dir)` |
| `vga_fb_init` | function | `kernel/vga_fb.c:5670` | `void vga_fb_init(void)` |
| `vga_fb_is_fullscreen` | function | `kernel/vga_fb.c:4269` | `int vga_fb_is_fullscreen(void)` |
| `vga_fb_is_minimized` | function | `kernel/vga_fb.c:4268` | `int vga_fb_is_minimized(void)` |
| `vga_fb_layout_cycle` | function | `kernel/vga_fb.c:1453` | `void vga_fb_layout_cycle(void)` |
| `vga_fb_layout_get` | function | `kernel/vga_fb.c:1469` | `int vga_fb_layout_get(void)` |
| `vga_fb_layout_name` | function | `kernel/vga_fb.c:1475` | `const char *vga_fb_layout_name(void)` |
| `vga_fb_layout_set` | function | `kernel/vga_fb.c:1442` | `int vga_fb_layout_set(int mode)` |
| `vga_fb_list_windows` | function | `kernel/vga_fb.c:1614` | `void vga_fb_list_windows(void)` |
| `vga_fb_mouse_init` | function | `kernel/vga_fb.c:5599` | `void vga_fb_mouse_init(void)` |
| `vga_fb_mouse_tick` | function | `kernel/vga_fb.c:5393` | `void vga_fb_mouse_tick(void)` |
| `vga_fb_move_terminal` | function | `kernel/vga_fb.c:4337` | `void vga_fb_move_terminal(int dx, int dy)` |
| `vga_fb_note_prompt` | function | `kernel/vga_fb.c:1676` | `void vga_fb_note_prompt(void)` |
| `vga_fb_nterms_get` | function | `kernel/vga_fb.c:1221` | `int vga_fb_nterms_get(void)` |
| `vga_fb_park_line` | function | `kernel/vga_fb.c:1702` | `void vga_fb_park_line(const char *b, int p)` |
| `vga_fb_pixel` | function | `kernel/vga_fb.c:2079` | `void vga_fb_pixel(int x, int y, uint8_t color)` |
| `vga_fb_pixel_rgb` | function | `kernel/vga_fb.c:2114` | `void vga_fb_pixel_rgb(int x, int y, uint8_t r, uint8_t g, uint8_t b)` |
| `vga_fb_prompt_live` | function | `kernel/vga_fb.c:1695` | `int vga_fb_prompt_live(void)` |
| `vga_fb_prompted` | function | `kernel/vga_fb.c:1686` | `int vga_fb_prompted(void)` |
| `vga_fb_ps2_owner` | function | `kernel/vga_fb.c:2734` | `int vga_fb_ps2_owner(int pid)` |
| `vga_fb_puts_term` | function | `kernel/vga_fb.c:3599` | `void vga_fb_puts_term(const char *s)` |
| `vga_fb_read_rgb` | function | `kernel/vga_fb.c:1913` | `unsigned long vga_fb_read_rgb(int x, int y)` |
| `vga_fb_rect` | function | `kernel/vga_fb.c:2099` | `void vga_fb_rect(int x, int y, int w, int h, uint8_t color)` |
| `vga_fb_rect_rgb` | function | `kernel/vga_fb.c:2123` | `void vga_fb_rect_rgb(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b)` |
| `vga_fb_reset_default` | function | `kernel/vga_fb.c:4445` | `void vga_fb_reset_default(void)` |
| `vga_fb_resize` | function | `kernel/vga_fb.c:4425` | `void vga_fb_resize(int dcols, int drows)` |
| `vga_fb_set_gfx_mode` | function | `kernel/vga_fb.c:750` | `void vga_fb_set_gfx_mode(int on)` |
| `vga_fb_set_gfx_palette` | function | `kernel/vga_fb.c:1838` | `void vga_fb_set_gfx_palette(const unsigned char *pal)` |
| `vga_fb_set_gfx_program` | function | `kernel/vga_fb.c:688` | `void vga_fb_set_gfx_program(const char *name)` |
| `vga_fb_set_palette` | function | `kernel/vga_fb.c:2005` | `static void vga_fb_set_palette(void)` |
| `vga_fb_snap_window` | function | `kernel/vga_fb.c:4397` | `void vga_fb_snap_window(int zone)` |
| `vga_fb_str` | function | `kernel/vga_fb.c:2156` | `void vga_fb_str(int col, int row, const char *s, uint8_t fg, uint8_t bg)` |
| `vga_fb_term_feed` | function | `kernel/vga_fb.c:373` | `void vga_fb_term_feed(const char *line, int len)` |
| `vga_fb_term_ring_init` | function | `kernel/vga_fb.c:365` | `void vga_fb_term_ring_init(void)` |
| `vga_fb_text_cursor` | function | `kernel/vga_fb.c:3605` | `void vga_fb_text_cursor(int col)` |
| `vga_fb_theme_name` | function | `kernel/vga_fb.c:3255` | `int vga_fb_theme_name(char *dst, int cap)` |
| `vga_fb_toggle_fullscreen` | function | `kernel/vga_fb.c:4227` | `void vga_fb_toggle_fullscreen(void)` |
| `vga_fb_toggle_minimize` | function | `kernel/vga_fb.c:4260` | `void vga_fb_toggle_minimize(void)` |
| `vga_fb_unpark_line` | function | `kernel/vga_fb.c:1717` | `int vga_fb_unpark_line(char *b, int *p)` |
| `vga_fb_wait_tick` | function | `kernel/vga_fb.c:5384` | `void vga_fb_wait_tick(void)` |
| `wall_level` | function | `kernel/vga_fb.c:1996` | `static int wall_level(int v)` |
| `wallpaper_draw` | function | `kernel/vga_fb.c:4559` | `static void wallpaper_draw(void)` |
| `wallpaper_ensure` | function | `kernel/vga_fb.c:4502` | `static void wallpaper_ensure(void)` |
| `wallpaper_packed` | function | `kernel/vga_fb.c:4575` | `static int wallpaper_packed(int x, int y, unsigned int *out)` |
| `wallpaper_rect` | function | `kernel/vga_fb.c:5093` | `static void wallpaper_rect(int x0, int y0, int w, int h)` |
| `wallpaper_usable` | function | `kernel/vga_fb.c:4554` | `static int wallpaper_usable(void)` |
| `wm_buttons_hit` | function | `kernel/vga_fb.c:2714` | `static int wm_buttons_hit(int mx, int my, int win_x, int win_y, int win_w)` |
| `wm_clear_close` | function | `kernel/vga_fb.c:2730` | `void wm_clear_close(void)` |
| `wm_close_pending` | function | `kernel/vga_fb.c:2729` | `int wm_close_pending(void)` |
| `wm_drag_reset` | function | `kernel/vga_fb.c:76` | `static void wm_drag_reset(void)` |
| `wm_draw_buttons` | function | `kernel/vga_fb.c:2200` | `static void wm_draw_buttons(int px, int py, int win_w, uint8_t fg, uint8_t bg)` |
| `wm_emit_focus_moved` | function | `kernel/vga_fb.c:1091` | `static void wm_emit_focus_moved(int before, int source)` |
| `wm_event_cfg` | function | `kernel/vga_fb.c:67` | `static wm_event_config_t wm_event_cfg(void)` |
| `wm_focus_cursor_sync` | function | `kernel/vga_fb.c:1084` | `static void wm_focus_cursor_sync(const wm_notify_event_t *e)` |
| `wm_geom_cfg` | function | `kernel/vga_fb.c:56` | `static wm_geom_config_t wm_geom_cfg(void)` |
| `wm_gfx_focus_sync` | function | `kernel/vga_fb.c:1283` | `static void wm_gfx_focus_sync(int on)` |
| `wm_gfx_mode_active` | function | `kernel/vga_fb.c:2731` | `int wm_gfx_mode_active(void)` |
| `wm_init_once` | function | `kernel/vga_fb.c:1183` | `static void wm_init_once(void)` |
| `wm_snapshot_state` | function | `kernel/vga_fb.c:1224` | `static void wm_snapshot_state(wm_focus_state_t *st)` |
| `fx_wait_until` | function | `kernel/vga_fx.c:40` | `static void fx_wait_until(unsigned long deadline)` |
| `once` | function | `kernel/vga_fx.c:95` | `* once (prev[] tracks the revealed frontier per column), then the final  * restore guarantees the...` |
| `vga_fx_enabled` | function | `kernel/vga_fx.c:32` | `int vga_fx_enabled(void)` |
| `vga_fx_free` | function | `kernel/vga_fx.c:82` | `void vga_fx_free(unsigned int *buf)` |
| `vga_fx_melt_from_black` | function | `kernel/vga_fx.c:164` | `void vga_fx_melt_from_black(int x, int y, int w, int h, const unsigned int *newb)` |
| `vga_fx_melt_rect` | function | `kernel/vga_fx.c:155` | `void vga_fx_melt_rect(int x, int y, int w, int h,     const unsigned int *oldb, const unsigned in...` |
| `vga_fx_restore_rect` | function | `kernel/vga_fx.c:68` | `void vga_fx_restore_rect(int x, int y, int w, int h, const unsigned int *buf)` |
| `vga_fx_set_enabled` | function | `kernel/vga_fx.c:27` | `void vga_fx_set_enabled(int on)` |
| `vga_fx_snap_rect` | function | `kernel/vga_fx.c:46` | `unsigned int *vga_fx_snap_rect(int x, int y, int w, int h)` |
| `Client` | class | `mcp/mcp_dbg_driver.py:15` | `class Client` |
| `__init__` | method | `mcp/mcp_dbg_driver.py:16` | `def __init__(self)` |
| `close` | method | `mcp/mcp_dbg_driver.py:54` | `def close(self)` |
| `main` | function | `mcp/mcp_dbg_driver.py:64` | `def main()` |
| `request` | method | `mcp/mcp_dbg_driver.py:28` | `def request(self, method, params)` |
| `tool` | method | `mcp/mcp_dbg_driver.py:46` | `def tool(self, name, params)` |
| `Client` | class | `mcp/mcp_dogfood.py:19` | `class Client` |
| `__init__` | method | `mcp/mcp_dogfood.py:20` | `def __init__(self, addons_dir)` |
| `close` | method | `mcp/mcp_dogfood.py:68` | `def close(self)` |
| `main` | function | `mcp/mcp_dogfood.py:78` | `def main()` |
| `request` | method | `mcp/mcp_dogfood.py:40` | `def request(self, method, params)` |
| `tool` | method | `mcp/mcp_dogfood.py:58` | `def tool(self, name, params)` |
| `AddonError` | class | `mcp/minios_addons.py:56` | `class AddonError(Exception)` |
| `AddonState` | class | `mcp/minios_addons.py:377` | `class AddonState` |
| `__init__` | method | `mcp/minios_addons.py:380` | `def __init__(self, path)` |
| `_clean` | function | `mcp/minios_addons.py:62` | `def _clean(s)` |
| `_unquote` | function | `mcp/minios_addons.py:66` | `def _unquote(v)` |
| `exit_code_of` | function | `mcp/minios_addons.py:372` | `def exit_code_of(text)` |
| `fail` | function | `mcp/minios_addons.py:85` | `def fail(lineno, why)` |
| `install_addon` | function | `mcp/minios_addons.py:401` | `def install_addon(session, addon, cfg)` |
| `load` | method | `mcp/minios_addons.py:383` | `def load(self)` |
| `load_addons_dir` | function | `mcp/minios_addons.py:323` | `def load_addons_dir(addons_dir)` |
| `parse_addon_yaml` | function | `mcp/minios_addons.py:73` | `def parse_addon_yaml(text)` |
| `save` | method | `mcp/minios_addons.py:393` | `def save(self, addons)` |
| `split_for_editor` | function | `mcp/minios_addons.py:347` | `def split_for_editor(text)` |
| `validate_addon` | function | `mcp/minios_addons.py:205` | `def validate_addon(addon, source)` |
| `validate_addon_path` | function | `mcp/minios_addons.py:295` | `def validate_addon_path(path)` |
| `validate_shell_line` | function | `mcp/minios_addons.py:309` | `def validate_shell_line(line)` |
| `LogBuffer` | class | `mcp/minios_mcp.py:146` | `class LogBuffer` |
| `MCPServer` | class | `mcp/minios_mcp.py:731` | `class MCPServer` |
| `MiniOSSession` | class | `mcp/minios_mcp.py:216` | `class MiniOSSession` |
| `RPCError` | class | `mcp/minios_mcp.py:137` | `class RPCError(Exception)` |
| `ToolError` | class | `mcp/minios_mcp.py:131` | `class ToolError(Exception)` |
| `__init__` | method | `mcp/minios_mcp.py:140` | `def __init__(self, code, message)` |
| `__init__` | method | `mcp/minios_mcp.py:149` | `def __init__(self, cap)` |
| `__init__` | method | `mcp/minios_mcp.py:219` | `def __init__(self, cfg)` |
| `__init__` | method | `mcp/minios_mcp.py:734` | `def __init__(self, cfg)` |
| `_addon_install` | method | `mcp/minios_mcp.py:863` | `def _addon_install(self, args)` |
| `_addons_list` | method | `mcp/minios_mcp.py:842` | `def _addons_list(self)` |
| `_call` | method | `mcp/minios_mcp.py:779` | `def _call(self, params)` |
| `_cleanup_parts` | method | `mcp/minios_mcp.py:493` | `def _cleanup_parts(self, parts)` |
| `_close_pty` | method | `mcp/minios_mcp.py:329` | `def _close_pty(self)` |
| `_dispatch` | method | `mcp/minios_mcp.py:796` | `def _dispatch(self, name, args)` |
| `_drop_pidfile` | method | `mcp/minios_mcp.py:278` | `def _drop_pidfile(self)` |
| `_find_locked` | method | `mcp/minios_mcp.py:206` | `def _find_locked(self, marker, start)` |
| `_handle` | method | `mcp/minios_mcp.py:746` | `def _handle(self, line)` |
| `_initialize` | method | `mcp/minios_mcp.py:772` | `def _initialize(self, params)` |
| `_read_loop` | method | `mcp/minios_mcp.py:319` | `def _read_loop(self)` |
| `_reap_stale` | method | `mcp/minios_mcp.py:242` | `def _reap_stale(self)` |
| `_reply` | method | `mcp/minios_mcp.py:884` | `def _reply(self, msg)` |
| `_write_editor_line` | method | `mcp/minios_mcp.py:348` | `def _write_editor_line(self, line)` |
| `_write_line` | method | `mcp/minios_mcp.py:339` | `def _write_line(self, line)` |
| `append` | method | `mcp/minios_mcp.py:155` | `def append(self, data)` |
| `boot` | method | `mcp/minios_mcp.py:284` | `def boot(self, timeout_ms)` |
| `booted` | method | `mcp/minios_mcp.py:230` | `def booted(self)` |
| `bytes_from` | method | `mcp/minios_mcp.py:163` | `def bytes_from(self, pos)` |
| `cat` | method | `mcp/minios_mcp.py:447` | `def cat(self, path)` |
| `cat_body` | method | `mcp/minios_mcp.py:464` | `def cat_body(self, path, missing_ok)` |
| `clamp_timeout` | function | `mcp/minios_mcp.py:89` | `def clamp_timeout(ms)` |
| `close` | method | `mcp/minios_mcp.py:576` | `def close(self)` |
| `env_config` | function | `mcp/minios_mcp.py:71` | `def env_config()` |
| `expect` | method | `mcp/minios_mcp.py:367` | `def expect(self, marker, timeout_ms)` |
| `find` | method | `mcp/minios_mcp.py:175` | `def find(self, marker, start)` |
| `main` | function | `mcp/minios_mcp.py:888` | `def main()` |
| `poweroff` | method | `mcp/minios_mcp.py:537` | `def poweroff(self, timeout_ms)` |
| `run` | method | `mcp/minios_mcp.py:738` | `def run(self)` |
| `run_python` | method | `mcp/minios_mcp.py:453` | `def run_python(self, script, args, timeout_ms)` |
| `run_test` | method | `mcp/minios_mcp.py:391` | `def run_test(self, commands, expect, refute, timeout_ms)` |
| `send` | method | `mcp/minios_mcp.py:356` | `def send(self, line, timeout_ms)` |
| `snapshot` | method | `mcp/minios_mcp.py:381` | `def snapshot(self, max_bytes)` |
| `status` | method | `mcp/minios_mcp.py:233` | `def status(self)` |
| `subprocess_launch` | function | `mcp/minios_mcp.py:580` | `def subprocess_launch(cfg, slave_fd)` |
| `terminate` | method | `mcp/minios_mcp.py:557` | `def terminate(self)` |
| `text_from` | method | `mcp/minios_mcp.py:168` | `def text_from(self, pos, end)` |
| `validate_content` | function | `mcp/minios_mcp.py:118` | `def validate_content(text)` |
| `validate_path` | function | `mcp/minios_mcp.py:102` | `def validate_path(name)` |
| `wait_for` | method | `mcp/minios_mcp.py:179` | `def wait_for(self, marker, start, timeout_ms)` |
| `wait_for_any` | method | `mcp/minios_mcp.py:192` | `def wait_for_any(self, markers, start, timeout_ms)` |
| `write` | method | `mcp/minios_mcp.py:500` | `def write(self, path, content)` |
| `run_one` | function | `mcp/mutate_mcp.sh:116` | `` |
| `FakeOS` | class | `mcp/test_minios_mcp.py:642` | `class FakeOS` |
| `MCPServer` | class | `mcp/test_minios_mcp.py:58` | `class MCPServer` |
| `TestAddonBDD` | class | `mcp/test_minios_mcp.py:844` | `class TestAddonBDD(_ConsoleBDDBase)` |
| `TestAddonHelpers` | class | `mcp/test_minios_mcp.py:602` | `class TestAddonHelpers(TestCase)` |
| `TestAddonInstall` | class | `mcp/test_minios_mcp.py:708` | `class TestAddonInstall(TestCase)` |
| `TestAddonYaml` | class | `mcp/test_minios_mcp.py:480` | `class TestAddonYaml(TestCase)` |
| `TestLogBuffer` | class | `mcp/test_minios_mcp.py:254` | `class TestLogBuffer(TestCase)` |
| `TestMiniOSBDD` | class | `mcp/test_minios_mcp.py:342` | `class TestMiniOSBDD(_ConsoleBDDBase)` |
| `TestProtocol` | class | `mcp/test_minios_mcp.py:141` | `class TestProtocol(TestCase)` |
| `TestValidation` | class | `mcp/test_minios_mcp.py:205` | `class TestValidation(TestCase)` |
| `_ConsoleBDDBase` | class | `mcp/test_minios_mcp.py:306` | `class _ConsoleBDDBase(TestCase)` |
| `__init__` | method | `mcp/test_minios_mcp.py:61` | `def __init__(self, env_extra)` |
| `__init__` | method | `mcp/test_minios_mcp.py:645` | `def __init__(self, exit_codes)` |
| `_cleanup_parts` | method | `mcp/test_minios_mcp.py:702` | `def _cleanup_parts(self, parts)` |
| `_read_response` | method | `mcp/test_minios_mcp.py:96` | `def _read_response(self)` |
| `_roundtrip` | method | `mcp/test_minios_mcp.py:102` | `def _roundtrip(self, msg)` |
| `_toolerror` | class | `mcp/test_minios_mcp.py:697` | `class _toolerror(Exception)` |
| `boot` | method | `mcp/test_minios_mcp.py:655` | `def boot(self, timeout_ms)` |
| `booted` | method | `mcp/test_minios_mcp.py:652` | `def booted(self)` |
| `broken_cat` | function | `mcp/test_minios_mcp.py:786` | `def broken_cat(path, missing_ok)` |
| `cat_body` | method | `mcp/test_minios_mcp.py:690` | `def cat_body(self, path, missing_ok)` |
| `close` | method | `mcp/test_minios_mcp.py:120` | `def close(self)` |
| `guard_server` | method | `mcp/test_minios_mcp.py:315` | `def guard_server(cls)` |
| `guarded` | function | `mcp/test_minios_mcp.py:318` | `def guarded(name, params)` |
| `have_qemu` | function | `mcp/test_minios_mcp.py:52` | `def have_qemu()` |
| `initialize` | method | `mcp/test_minios_mcp.py:80` | `def initialize(self)` |
| `load_module` | function | `mcp/test_minios_mcp.py:29` | `def load_module()` |
| `make_addon` | method | `mcp/test_minios_mcp.py:747` | `def make_addon(self)` |
| `raw` | method | `mcp/test_minios_mcp.py:91` | `def raw(self, line)` |
| `request` | method | `mcp/test_minios_mcp.py:84` | `def request(self, method, params)` |
| `send` | method | `mcp/test_minios_mcp.py:666` | `def send(self, line, timeout_ms)` |
| `setUp` | method | `mcp/test_minios_mcp.py:336` | `def setUp(self)` |
| `setUpClass` | method | `mcp/test_minios_mcp.py:143` | `def setUpClass(cls)` |
| `setUpClass` | method | `mcp/test_minios_mcp.py:207` | `def setUpClass(cls)` |
| `setUpClass` | method | `mcp/test_minios_mcp.py:256` | `def setUpClass(cls)` |
| `setUpClass` | method | `mcp/test_minios_mcp.py:344` | `def setUpClass(cls)` |
| `setUpClass` | method | `mcp/test_minios_mcp.py:482` | `def setUpClass(cls)` |
| `setUpClass` | method | `mcp/test_minios_mcp.py:604` | `def setUpClass(cls)` |
| `setUpClass` | method | `mcp/test_minios_mcp.py:710` | `def setUpClass(cls)` |
| `setUpClass` | method | `mcp/test_minios_mcp.py:848` | `def setUpClass(cls)` |
| `tearDownClass` | method | `mcp/test_minios_mcp.py:149` | `def tearDownClass(cls)` |
| `tearDownClass` | method | `mcp/test_minios_mcp.py:351` | `def tearDownClass(cls)` |
| `tearDownClass` | method | `mcp/test_minios_mcp.py:742` | `def tearDownClass(cls)` |
| `tearDownClass` | method | `mcp/test_minios_mcp.py:886` | `def tearDownClass(cls)` |
| `test_addons_list` | method | `mcp/test_minios_mcp.py:894` | `def test_addons_list(self)` |
| `test_bad_indent_rejected` | method | `mcp/test_minios_mcp.py:510` | `def test_bad_indent_rejected(self)` |
| `test_bad_kind_rejected` | method | `mcp/test_minios_mcp.py:564` | `def test_bad_kind_rejected(self)` |
| `test_bounds` | method | `mcp/test_minios_mcp.py:261` | `def test_bounds(self)` |
| `test_cat_body_drops_console_framing` | method | `mcp/test_minios_mcp.py:292` | `def test_cat_body_drops_console_framing(self)` |
| `test_content_accepts_ascii` | method | `mcp/test_minios_mcp.py:223` | `def test_content_accepts_ascii(self)` |
| `test_content_rejects_non_printable` | method | `mcp/test_minios_mcp.py:226` | `def test_content_rejects_non_printable(self)` |
| `test_cursor_prevents_stale_match` | method | `mcp/test_minios_mcp.py:275` | `def test_cursor_prevents_stale_match(self)` |
| `test_editor_prompt_forms_cover_kernel_markers` | method | `mcp/test_minios_mcp.py:298` | `def test_editor_prompt_forms_cover_kernel_markers(self)` |
| `test_exit_code_of` | method | `mcp/test_minios_mcp.py:629` | `def test_exit_code_of(self)` |
| `test_find_and_total` | method | `mcp/test_minios_mcp.py:268` | `def test_find_and_total(self)` |
| `test_host_kind_accepts_empty_files` | method | `mcp/test_minios_mcp.py:541` | `def test_host_kind_accepts_empty_files(self)` |
| `test_host_kind_requires_artifact` | method | `mcp/test_minios_mcp.py:572` | `def test_host_kind_requires_artifact(self)` |
| `test_initialize` | method | `mcp/test_minios_mcp.py:152` | `def test_initialize(self)` |
| `test_install_build_failure_aborts` | method | `mcp/test_minios_mcp.py:835` | `def test_install_build_failure_aborts(self)` |
| `test_install_fixture` | method | `mcp/test_minios_mcp.py:900` | `def test_install_fixture(self)` |
| `test_install_mismatch_aborts_and_cleans` | method | `mcp/test_minios_mcp.py:782` | `def test_install_mismatch_aborts_and_cleans(self)` |
| `test_install_multi_chunk_reassembly` | method | `mcp/test_minios_mcp.py:796` | `def test_install_multi_chunk_reassembly(self)` |
| `test_install_refuses_host_before_touching_session` | method | `mcp/test_minios_mcp.py:586` | `def test_install_refuses_host_before_touching_session(self)` |
| `test_install_success` | method | `mcp/test_minios_mcp.py:769` | `def test_install_success(self)` |
| `test_install_unknown_addon_fails` | method | `mcp/test_minios_mcp.py:909` | `def test_install_unknown_addon_fails(self)` |
| `test_install_verify_failure_aborts` | method | `mcp/test_minios_mcp.py:828` | `def test_install_verify_failure_aborts(self)` |
| `test_malformed_json` | method | `mcp/test_minios_mcp.py:174` | `def test_malformed_json(self)` |
| `test_parse_valid` | method | `mcp/test_minios_mcp.py:492` | `def test_parse_valid(self)` |
| `test_path_accepts_plain_names` | method | `mcp/test_minios_mcp.py:212` | `def test_path_accepts_plain_names(self)` |
| `test_path_rejects_long` | method | `mcp/test_minios_mcp.py:220` | `def test_path_rejects_long(self)` |
| `test_path_rejects_unsafe` | method | `mcp/test_minios_mcp.py:216` | `def test_path_rejects_unsafe(self)` |
| `test_ping` | method | `mcp/test_minios_mcp.py:166` | `def test_ping(self)` |
| `test_reference_kind_carries_nothing` | method | `mcp/test_minios_mcp.py:556` | `def test_reference_kind_carries_nothing(self)` |
| `test_send_empty_line_rejected` | method | `mcp/test_minios_mcp.py:189` | `def test_send_empty_line_rejected(self)` |
| `test_send_not_booted` | method | `mcp/test_minios_mcp.py:183` | `def test_send_not_booted(self)` |
| `test_split_for_editor_chunks` | method | `mcp/test_minios_mcp.py:614` | `def test_split_for_editor_chunks(self)` |
| `test_split_rejects_long_line` | method | `mcp/test_minios_mcp.py:621` | `def test_split_rejects_long_line(self)` |
| `test_split_rejects_non_ascii` | method | `mcp/test_minios_mcp.py:625` | `def test_split_rejects_non_ascii(self)` |
| `test_state_roundtrip` | method | `mcp/test_minios_mcp.py:634` | `def test_state_roundtrip(self)` |
| `test_t01_boot` | method | `mcp/test_minios_mcp.py:355` | `def test_t01_boot(self)` |
| `test_t02_expect` | method | `mcp/test_minios_mcp.py:365` | `def test_t02_expect(self)` |
| `test_t03_write_and_cat` | method | `mcp/test_minios_mcp.py:372` | `def test_t03_write_and_cat(self)` |
| `test_t04_toolchain_elf` | method | `mcp/test_minios_mcp.py:382` | `def test_t04_toolchain_elf(self)` |
| `test_t05_toolchain_cvm` | method | `mcp/test_minios_mcp.py:394` | `def test_t05_toolchain_cvm(self)` |
| `test_t06_selfhosted_compiler` | method | `mcp/test_minios_mcp.py:404` | `def test_t06_selfhosted_compiler(self)` |
| `test_t07_bin_command_path` | method | `mcp/test_minios_mcp.py:411` | `def test_t07_bin_command_path(self)` |
| `test_t08_python_script` | method | `mcp/test_minios_mcp.py:419` | `def test_t08_python_script(self)` |
| `test_t09_py_eval` | method | `mcp/test_minios_mcp.py:426` | `def test_t09_py_eval(self)` |
| `test_t10_minios_test` | method | `mcp/test_minios_mcp.py:431` | `def test_t10_minios_test(self)` |
| `test_t11_poweroff_and_reboot` | method | `mcp/test_minios_mcp.py:452` | `def test_t11_poweroff_and_reboot(self)` |
| `test_test_not_booted` | method | `mcp/test_minios_mcp.py:195` | `def test_test_not_booted(self)` |
| `test_timeout_clamped` | method | `mcp/test_minios_mcp.py:230` | `def test_timeout_clamped(self)` |
| `test_tools_list` | method | `mcp/test_minios_mcp.py:158` | `def test_tools_list(self)` |
| `test_unknown_key_rejected` | method | `mcp/test_minios_mcp.py:506` | `def test_unknown_key_rejected(self)` |
| `test_unknown_method` | method | `mcp/test_minios_mcp.py:170` | `def test_unknown_method(self)` |
| `test_unknown_tool` | method | `mcp/test_minios_mcp.py:178` | `def test_unknown_tool(self)` |
| `test_validate_accepts_valid` | method | `mcp/test_minios_mcp.py:502` | `def test_validate_accepts_valid(self)` |
| `test_validate_rejects_bad_dst` | method | `mcp/test_minios_mcp.py:514` | `def test_validate_rejects_bad_dst(self)` |
| `test_validate_rejects_control_chars` | method | `mcp/test_minios_mcp.py:531` | `def test_validate_rejects_control_chars(self)` |
| `test_validate_rejects_empty_files` | method | `mcp/test_minios_mcp.py:536` | `def test_validate_rejects_empty_files(self)` |
| `test_validate_rejects_long_build_line` | method | `mcp/test_minios_mcp.py:523` | `def test_validate_rejects_long_build_line(self)` |
| `test_validate_rejects_missing_name` | method | `mcp/test_minios_mcp.py:519` | `def test_validate_rejects_missing_name(self)` |
| `test_wait_for_any_earliest` | method | `mcp/test_minios_mcp.py:284` | `def test_wait_for_any_earliest(self)` |
| `test_write_rejects_line_too_long` | method | `mcp/test_minios_mcp.py:234` | `def test_write_rejects_line_too_long(self)` |
| `test_write_rejects_too_many_lines` | method | `mcp/test_minios_mcp.py:243` | `def test_write_rejects_too_many_lines(self)` |
| `tool` | method | `mcp/test_minios_mcp.py:110` | `def tool(self, name, params)` |
| `write` | method | `mcp/test_minios_mcp.py:659` | `def write(self, path, content)` |
| `LNX_AF_INET` | macro | `net/net.c:1028` | `#define LNX_AF_INET` |
| `LNX_EAFNOSUPPORT` | macro | `net/net.c:1081` | `#define LNX_EAFNOSUPPORT` |
| `LNX_EAGAIN` | macro | `net/net.c:1072` | `#define LNX_EAGAIN` |
| `LNX_EALREADY` | macro | `net/net.c:1086` | `#define LNX_EALREADY` |
| `LNX_EBADF` | macro | `net/net.c:1071` | `#define LNX_EBADF` |
| `LNX_ECONNREFUSED` | macro | `net/net.c:1085` | `#define LNX_ECONNREFUSED` |
| `LNX_EDESTADDRREQ` | macro | `net/net.c:1076` | `#define LNX_EDESTADDRREQ` |
| `LNX_EFAULT` | macro | `net/net.c:1073` | `#define LNX_EFAULT` |
| `LNX_EINPROGRESS` | macro | `net/net.c:1087` | `#define LNX_EINPROGRESS` |
| `LNX_EINVAL` | macro | `net/net.c:1074` | `#define LNX_EINVAL` |
| `LNX_EISCONN` | macro | `net/net.c:1082` | `#define LNX_EISCONN` |
| `LNX_EMSGSIZE` | macro | `net/net.c:1077` | `#define LNX_EMSGSIZE` |
| `LNX_ENOPROTOOPT` | macro | `net/net.c:1078` | `#define LNX_ENOPROTOOPT` |
| `LNX_ENOTCONN` | macro | `net/net.c:1083` | `#define LNX_ENOTCONN` |
| `LNX_ENOTTY` | macro | `net/net.c:1667` | `#define LNX_ENOTTY` |
| `LNX_EOPNOTSUPP` | macro | `net/net.c:1080` | `#define LNX_EOPNOTSUPP` |
| `LNX_EPIPE` | macro | `net/net.c:1075` | `#define LNX_EPIPE` |
| `LNX_EPROTONOSUPPORT` | macro | `net/net.c:1079` | `#define LNX_EPROTONOSUPPORT` |
| `LNX_ETIMEDOUT` | macro | `net/net.c:1084` | `#define LNX_ETIMEDOUT` |
| `LNX_FD_CLOEXEC` | macro | `net/net.c:1061` | `#define LNX_FD_CLOEXEC` |
| `LNX_FIOCLEX` | macro | `net/net.c:1666` | `#define LNX_FIOCLEX` |
| `LNX_FIONBIO` | macro | `net/net.c:1664` | `#define LNX_FIONBIO` |
| `LNX_FIONCLEX` | macro | `net/net.c:1665` | `#define LNX_FIONCLEX` |
| `LNX_FIONREAD` | macro | `net/net.c:1663` | `#define LNX_FIONREAD` |
| `LNX_F_GETFD` | macro | `net/net.c:1062` | `#define LNX_F_GETFD` |
| `LNX_F_GETFL` | macro | `net/net.c:1064` | `#define LNX_F_GETFL` |
| `LNX_F_SETFD` | macro | `net/net.c:1063` | `#define LNX_F_SETFD` |
| `LNX_F_SETFL` | macro | `net/net.c:1065` | `#define LNX_F_SETFL` |
| `LNX_IPPROTO_IP` | macro | `net/net.c:1049` | `#define LNX_IPPROTO_IP` |
| `LNX_IPPROTO_TCP` | macro | `net/net.c:1034` | `#define LNX_IPPROTO_TCP` |
| `LNX_IPPROTO_UDP` | macro | `net/net.c:1035` | `#define LNX_IPPROTO_UDP` |
| `LNX_IP_MTU_DISCOVER` | macro | `net/net.c:1052` | `#define LNX_IP_MTU_DISCOVER` |
| `LNX_IP_RECVERR` | macro | `net/net.c:1053` | `#define LNX_IP_RECVERR` |
| `LNX_IP_TOS` | macro | `net/net.c:1050` | `#define LNX_IP_TOS` |
| `LNX_IP_TTL` | macro | `net/net.c:1051` | `#define LNX_IP_TTL` |
| `LNX_MSG_DONTWAIT` | macro | `net/net.c:1037` | `#define LNX_MSG_DONTWAIT` |
| `LNX_MSG_NOSIGNAL` | macro | `net/net.c:1038` | `#define LNX_MSG_NOSIGNAL` |
| `LNX_MSG_PEEK` | macro | `net/net.c:1036` | `#define LNX_MSG_PEEK` |
| `LNX_O_NONBLOCK` | macro | `net/net.c:1060` | `#define LNX_O_NONBLOCK` |
| `LNX_O_RDWR` | macro | `net/net.c:1059` | `#define LNX_O_RDWR` |
| `LNX_POLLERR` | macro | `net/net.c:1068` | `#define LNX_POLLERR` |
| `LNX_POLLHUP` | macro | `net/net.c:1069` | `#define LNX_POLLHUP` |
| `LNX_POLLIN` | macro | `net/net.c:1066` | `#define LNX_POLLIN` |
| `LNX_POLLNVAL` | macro | `net/net.c:1070` | `#define LNX_POLLNVAL` |
| `LNX_POLLOUT` | macro | `net/net.c:1067` | `#define LNX_POLLOUT` |
| `LNX_SOCK_CLOEXEC` | macro | `net/net.c:1033` | `#define LNX_SOCK_CLOEXEC` |
| `LNX_SOCK_DGRAM` | macro | `net/net.c:1030` | `#define LNX_SOCK_DGRAM` |
| `LNX_SOCK_NONBLOCK` | macro | `net/net.c:1032` | `#define LNX_SOCK_NONBLOCK` |
| `LNX_SOCK_STREAM` | macro | `net/net.c:1029` | `#define LNX_SOCK_STREAM` |
| `LNX_SOCK_TYPE_MASK` | macro | `net/net.c:1031` | `#define LNX_SOCK_TYPE_MASK` |
| `LNX_SOL_SOCKET` | macro | `net/net.c:1039` | `#define LNX_SOL_SOCKET` |
| `LNX_SO_ERROR` | macro | `net/net.c:1042` | `#define LNX_SO_ERROR` |
| `LNX_SO_KEEPALIVE` | macro | `net/net.c:1045` | `#define LNX_SO_KEEPALIVE` |
| `LNX_SO_LINGER` | macro | `net/net.c:1046` | `#define LNX_SO_LINGER` |
| `LNX_SO_RCVBUF` | macro | `net/net.c:1044` | `#define LNX_SO_RCVBUF` |
| `LNX_SO_RCVTIMEO` | macro | `net/net.c:1047` | `#define LNX_SO_RCVTIMEO` |
| `LNX_SO_REUSEADDR` | macro | `net/net.c:1040` | `#define LNX_SO_REUSEADDR` |
| `LNX_SO_SNDBUF` | macro | `net/net.c:1043` | `#define LNX_SO_SNDBUF` |
| `LNX_SO_SNDTIMEO` | macro | `net/net.c:1048` | `#define LNX_SO_SNDTIMEO` |
| `LNX_SO_TYPE` | macro | `net/net.c:1041` | `#define LNX_SO_TYPE` |
| `LNX_TCP_KEEPCNT` | macro | `net/net.c:1058` | `#define LNX_TCP_KEEPCNT` |
| `LNX_TCP_KEEPIDLE` | macro | `net/net.c:1056` | `#define LNX_TCP_KEEPIDLE` |
| `LNX_TCP_KEEPINTVL` | macro | `net/net.c:1057` | `#define LNX_TCP_KEEPINTVL` |
| `LNX_TCP_NODELAY` | macro | `net/net.c:1055` | `#define LNX_TCP_NODELAY` |
| `NET_IP_DEFAULT_TTL` | macro | `net/net.c:1054` | `#define NET_IP_DEFAULT_TTL` |
| `NET_RECV_FLAGS_OK` | macro | `net/net.c:1089` | `#define NET_RECV_FLAGS_OK` |
| `NET_SEND_FLAGS_OK` | macro | `net/net.c:1088` | `#define NET_SEND_FLAGS_OK` |
| `NET_TCP_CLOSED` | macro | `net/net.c:400` | `#define NET_TCP_CLOSED` |
| `NET_TCP_DEAD` | macro | `net/net.c:404` | `#define NET_TCP_DEAD` |
| `NET_TCP_ESTABLISHED` | macro | `net/net.c:402` | `#define NET_TCP_ESTABLISHED` |
| `NET_TCP_FIN_SENT` | macro | `net/net.c:403` | `#define NET_TCP_FIN_SENT` |
| `NET_TCP_LISTEN` | macro | `net/net.c:405` | `#define NET_TCP_LISTEN` |
| `NET_TCP_SYN_RCVD` | macro | `net/net.c:406` | `#define NET_TCP_SYN_RCVD` |
| `NET_TCP_SYN_SENT` | macro | `net/net.c:401` | `#define NET_TCP_SYN_SENT` |
| `net_accept_nb` | function | `net/net.c:942` | `int net_accept_nb(int fd)` |
| `net_arp_entry` | struct | `net/net.c:95` | `` |
| `net_arp_lookup` | function | `net/net.c:118` | `static int net_arp_lookup(const unsigned char *ip, unsigned char *mac_out)` |
| `net_arp_request` | function | `net/net.c:129` | `static void net_arp_request(const unsigned char *ip)` |
| `net_arp_resolve` | function | `net/net.c:147` | `static int net_arp_resolve(const unsigned char *ip, unsigned char *mac_out)` |
| `net_arp_store` | function | `net/net.c:103` | `static void net_arp_store(const unsigned char *ip, const unsigned char *mac)` |
| `net_checksum` | function | `net/net.c:78` | `static unsigned short net_checksum(const void *data, unsigned len)` |
| `net_close` | function | `net/net.c:916` | `void net_close(int fd)` |
| `net_cmd_dns` | function | `net/net.c:1842` | `void net_cmd_dns(const char *host)` |
| `net_cmd_ping` | function | `net/net.c:1831` | `void net_cmd_ping(const char *ip_text)` |
| `net_cmd_status` | function | `net/net.c:1803` | `void net_cmd_status(void)` |
| `net_connect` | function | `net/net.c:892` | `int net_connect(const char *host, unsigned short port)` |
| `net_dns_parse` | function | `net/net.c:230` | `static void net_dns_parse(const unsigned char *data, unsigned len)` |
| `net_dns_resolve` | function | `net/net.c:268` | `static int net_dns_resolve(const char *host, unsigned char ip_out[4])` |
| `net_dns_state` | struct | `net/net.c:221` | `` |
| `net_drv_poll` | function | `net/net.c:43` | `static void net_drv_poll(void)` |
| `net_drv_present` | function | `net/net.c:48` | `static int net_drv_present(void)` |
| `net_drv_send` | function | `net/net.c:38` | `static int net_drv_send(const unsigned char *frame, unsigned len)` |
| `net_fd_udp` | function | `net/net.c:1096` | `static int net_fd_udp(long fd)` |
| `net_gather_msg` | function | `net/net.c:1450` | `static long net_gather_msg(long msg, unsigned char *kbuf, long cap)` |
| `net_get16` | function | `net/net.c:69` | `static unsigned short net_get16(const unsigned char *p)` |
| `net_get32` | function | `net/net.c:73` | `static unsigned int net_get32(const unsigned char *p)` |
| `net_get_addrs` | function | `net/net.c:1825` | `void net_get_addrs(unsigned char mac_out[NET_ETH_ALEN], unsigned char ip_out[4])` |
| `net_icmp_rx` | function | `net/net.c:348` | `static void net_icmp_rx(const unsigned char *ip, unsigned len)` |
| `net_init` | function | `net/net.c:1863` | `void net_init(void)` |
| `net_ip_send` | function | `net/net.c:172` | `static int net_ip_send(const unsigned char *dip, unsigned char proto,                        cons...` |
| `net_listen` | function | `net/net.c:927` | `int net_listen(unsigned short port)` |
| `net_load_sockaddr` | function | `net/net.c:1185` | `static long net_load_sockaddr(long addr, long len, unsigned char ip[4], unsigned short *port)` |
| `net_open` | function | `net/net.c:886` | `int net_open(void)` |
| `net_parse_ip` | function | `net/net.c:1778` | `static int net_parse_ip(const char *text, unsigned char ip[4])` |
| `net_ping` | function | `net/net.c:377` | `static int net_ping(const unsigned char ip[4])` |
| `net_put16` | function | `net/net.c:57` | `static void net_put16(unsigned char *p, unsigned short v)` |
| `net_put32` | function | `net/net.c:62` | `static void net_put32(unsigned char *p, unsigned int v)` |
| `net_put_sockaddr` | function | `net/net.c:1158` | `static void net_put_sockaddr(unsigned char *sa, const unsigned char ip[4], unsigned short port)` |
| `net_recv` | function | `net/net.c:906` | `int net_recv(int fd, char *buf, int len)` |
| `net_recv_timeout` | function | `net/net.c:911` | `int net_recv_timeout(int fd, char *buf, int len, unsigned long timeout_ms)` |
| `net_register_symbols` | function | `net/net.c:1855` | `void net_register_symbols(void)` |
| `net_rx_handle_frame` | function | `net/net.c:822` | `void net_rx_handle_frame(const unsigned char *frame, unsigned len)` |
| `net_send` | function | `net/net.c:901` | `int net_send(int fd, const char *buf, int len)` |
| `net_send_bytes` | function | `net/net.c:1347` | `static long net_send_bytes(long fd, const unsigned char *buf, long len,                          ...` |
| `net_sock_alloc` | function | `net/net.c:469` | `static struct net_tcp_sock *net_sock_alloc(void)` |
| `net_sock_index` | function | `net/net.c:484` | `static int net_sock_index(const struct net_tcp_sock *s)` |
| `net_sock_state` | function | `net/net.c:976` | `int net_sock_state(int fd)` |
| `net_socket_revents` | function | `net/net.c:1707` | `static unsigned short net_socket_revents(long fd)` |
| `net_store_sockaddr` | function | `net/net.c:1168` | `static long net_store_sockaddr(long addr, long lenp, const unsigned char ip[4],                  ...` |
| `net_sys_accept` | function | `net/net.c:1329` | `long net_sys_accept(long fd, long sockaddr, long addrlen)` |
| `net_sys_bind` | function | `net/net.c:1296` | `long net_sys_bind(long fd, long sockaddr, long addrlen)` |
| `net_sys_close` | function | `net/net.c:1523` | `long net_sys_close(long fd)` |
| `net_sys_connect` | function | `net/net.c:1249` | `long net_sys_connect(long fd, long sockaddr, long addrlen)` |
| `net_sys_dns` | function | `net/net.c:1767` | `long net_sys_dns(long host)` |
| `net_sys_fcntl` | function | `net/net.c:1643` | `long net_sys_fcntl(long fd, long cmd, long arg)` |
| `net_sys_getpeername` | function | `net/net.c:1625` | `long net_sys_getpeername(long fd, long addr, long lenp)` |
| `net_sys_getsockname` | function | `net/net.c:1616` | `long net_sys_getsockname(long fd, long addr, long lenp)` |
| `net_sys_getsockopt` | function | `net/net.c:1569` | `long net_sys_getsockopt(long fd, long level, long name, long val, long lenp)` |
| `net_sys_ioctl` | function | `net/net.c:1674` | `long net_sys_ioctl(long fd, long req, long arg)` |
| `net_sys_is_socket` | function | `net/net.c:1102` | `int net_sys_is_socket(long fd)` |
| `net_sys_listen` | function | `net/net.c:1318` | `long net_sys_listen(long fd, long backlog)` |
| `net_sys_poll` | function | `net/net.c:1727` | `long net_sys_poll(long fds, long nfds, long timeout_ms)` |
| `net_sys_recvfrom` | function | `net/net.c:1390` | `long net_sys_recvfrom(long fd, long buf, long len, long flags, long from, long fromlen)` |
| `net_sys_sendmmsg` | function | `net/net.c:1498` | `long net_sys_sendmmsg(long fd, long vec, long vlen, long flags)` |
| `net_sys_sendmsg` | function | `net/net.c:1470` | `long net_sys_sendmsg(long fd, long msg, long flags)` |
| `net_sys_sendto` | function | `net/net.c:1375` | `long net_sys_sendto(long fd, long buf, long len, long flags, long to, long tolen)` |
| `net_sys_setsockopt` | function | `net/net.c:1534` | `long net_sys_setsockopt(long fd, long level, long name, long val, long len)` |
| `net_sys_shutdown` | function | `net/net.c:1514` | `long net_sys_shutdown(long fd, long how)` |
| `net_sys_socket` | function | `net/net.c:1222` | `long net_sys_socket(long a1, long a2, long a3)` |
| `net_tcp_checksum` | function | `net/net.c:493` | `static unsigned short net_tcp_checksum(const unsigned char *src, const unsigned char *dst,       ...` |
| `net_tcp_close` | function | `net/net.c:802` | `static void net_tcp_close(struct net_tcp_sock *s)` |
| `net_tcp_connect_into` | function | `net/net.c:711` | `static int net_tcp_connect_into(struct net_tcp_sock *s, const unsigned char ip[4],               ...` |
| `net_tcp_passive_open` | function | `net/net.c:687` | `static int net_tcp_passive_open(struct net_tcp_sock *ls,         const unsigned char peer[4], uns...` |
| `net_tcp_recv` | function | `net/net.c:764` | `static int net_tcp_recv(struct net_tcp_sock *s, char *buf, int len)` |
| `net_tcp_rx` | function | `net/net.c:559` | `static void net_tcp_rx(const unsigned char *ip, unsigned len)` |
| `net_tcp_send` | function | `net/net.c:738` | `static int net_tcp_send(struct net_tcp_sock *s, const char *buf, int len)` |
| `net_tcp_sock` | struct | `net/net.c:408` | `` |
| `net_tcp_xmit` | function | `net/net.c:525` | `static int net_tcp_xmit(struct net_tcp_sock *s, unsigned flags,                         const uns...` |
| `net_udp_alloc` | function | `net/net.c:1106` | `static struct net_udp_sock *net_udp_alloc(void)` |
| `net_udp_checksum_ok` | function | `net/net.c:509` | `static int net_udp_checksum_ok(const unsigned char *src, const unsigned char *dst,               ...` |
| `net_udp_deliver` | function | `net/net.c:1136` | `static int net_udp_deliver(const unsigned char sip[4], unsigned short sport,                     ...` |
| `net_udp_dgram` | struct | `net/net.c:437` | `` |
| `net_udp_ephemeral` | function | `net/net.c:1120` | `static unsigned short net_udp_ephemeral(void)` |
| `net_udp_send` | function | `net/net.c:208` | `static int net_udp_send(const unsigned char *dip, unsigned short sport,                         u...` |
| `net_udp_send` | function | `net/net.c:329` | `net_udp_send((const unsigned char[])` |
| `net_udp_sock` | struct | `net/net.c:445` | `` |
| `polling` | function | `net/net.c:959` | `* without polling (the peer's ACK arrives through the driver poll). */ int net_accept(int fd, uns...` |
| `RTL_MIN_FRAME` | macro | `net/rtl8139.c:99` | `#define RTL_MIN_FRAME` |
| `RTL_REG_9346CR` | macro | `net/rtl8139.c:52` | `#define RTL_REG_9346CR` |
| `RTL_REG_CAPR` | macro | `net/rtl8139.c:50` | `#define RTL_REG_CAPR` |
| `RTL_REG_CBR` | macro | `net/rtl8139.c:51` | `#define RTL_REG_CBR` |
| `RTL_REG_CONFIG1` | macro | `net/rtl8139.c:53` | `#define RTL_REG_CONFIG1` |
| `RTL_REG_CR` | macro | `net/rtl8139.c:46` | `#define RTL_REG_CR` |
| `RTL_REG_RBSTART` | macro | `net/rtl8139.c:49` | `#define RTL_REG_RBSTART` |
| `RTL_REG_TSAD0` | macro | `net/rtl8139.c:48` | `#define RTL_REG_TSAD0` |
| `RTL_REG_TSD0` | macro | `net/rtl8139.c:47` | `#define RTL_REG_TSD0` |
| `RTL_TX_YIELD_EVERY` | macro | `net/rtl8139.c:166` | `#define RTL_TX_YIELD_EVERY` |
| `deleted` | function | `net/rtl8139.c:79` | `* been deleted (a second base/per-ms pair beside ktime's is a second  * clock, and drivers must n...` |
| `inl_port` | function | `net/rtl8139.c:33` | `static unsigned int inl_port(unsigned short port)` |
| `outl_port` | function | `net/rtl8139.c:29` | `static void outl_port(unsigned short port, unsigned int val)` |
| `rtl_counters` | function | `net/rtl8139.c:214` | `void rtl_counters(unsigned int *tx_frames, unsigned int *rx_frames)` |

Next: [SYMBOLS_p12.md](SYMBOLS_p12.md)
