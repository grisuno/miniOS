# Symbols (page 10 of 26)
Previous: [SYMBOLS_p9.md](SYMBOLS_p9.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `vga_fb_gfx_map_mouse` | function | `kernel/vga_fb.c:726` | `void vga_fb_gfx_map_mouse(int *x, int *y)` |
| `vga_fb_gfx_origin` | function | `kernel/vga_fb.c:709` | `void vga_fb_gfx_origin(int *x, int *y)` |
| `vga_fb_gfx_set_hidden` | function | `kernel/vga_fb.c:3168` | `int vga_fb_gfx_set_hidden(int hide)` |
| `vga_fb_gfx_view_name` | function | `kernel/vga_fb.c:3196` | `const char *vga_fb_gfx_view_name(void)` |
| `vga_fb_hide_text_cursor` | function | `kernel/vga_fb.c:2898` | `void vga_fb_hide_text_cursor(void)` |
| `vga_fb_init` | function | `kernel/vga_fb.c:4445` | `void vga_fb_init(void)` |
| `vga_fb_is_fullscreen` | function | `kernel/vga_fb.c:3250` | `int vga_fb_is_fullscreen(void)` |
| `vga_fb_is_minimized` | function | `kernel/vga_fb.c:3249` | `int vga_fb_is_minimized(void)` |
| `vga_fb_layout_cycle` | function | `kernel/vga_fb.c:1285` | `void vga_fb_layout_cycle(void)` |
| `vga_fb_layout_get` | function | `kernel/vga_fb.c:1301` | `int vga_fb_layout_get(void)` |
| `vga_fb_layout_name` | function | `kernel/vga_fb.c:1307` | `const char *vga_fb_layout_name(void)` |
| `vga_fb_layout_set` | function | `kernel/vga_fb.c:1274` | `int vga_fb_layout_set(int mode)` |
| `vga_fb_list_windows` | function | `kernel/vga_fb.c:1446` | `void vga_fb_list_windows(void)` |
| `vga_fb_mouse_init` | function | `kernel/vga_fb.c:4417` | `void vga_fb_mouse_init(void)` |
| `vga_fb_mouse_tick` | function | `kernel/vga_fb.c:4216` | `void vga_fb_mouse_tick(void)` |
| `vga_fb_move_terminal` | function | `kernel/vga_fb.c:3318` | `void vga_fb_move_terminal(int dx, int dy)` |
| `vga_fb_note_prompt` | function | `kernel/vga_fb.c:1508` | `void vga_fb_note_prompt(void)` |
| `vga_fb_nterms_get` | function | `kernel/vga_fb.c:1079` | `int vga_fb_nterms_get(void)` |
| `vga_fb_park_line` | function | `kernel/vga_fb.c:1534` | `void vga_fb_park_line(const char *b, int p)` |
| `vga_fb_pixel` | function | `kernel/vga_fb.c:1911` | `void vga_fb_pixel(int x, int y, uint8_t color)` |
| `vga_fb_pixel_rgb` | function | `kernel/vga_fb.c:1946` | `void vga_fb_pixel_rgb(int x, int y, uint8_t r, uint8_t g, uint8_t b)` |
| `vga_fb_prompt_live` | function | `kernel/vga_fb.c:1527` | `int vga_fb_prompt_live(void)` |
| `vga_fb_prompted` | function | `kernel/vga_fb.c:1518` | `int vga_fb_prompted(void)` |
| `vga_fb_ps2_owner` | function | `kernel/vga_fb.c:2059` | `int vga_fb_ps2_owner(int pid)` |
| `vga_fb_puts_term` | function | `kernel/vga_fb.c:2884` | `void vga_fb_puts_term(const char *s)` |
| `vga_fb_read_rgb` | function | `kernel/vga_fb.c:1745` | `unsigned long vga_fb_read_rgb(int x, int y)` |
| `vga_fb_rect` | function | `kernel/vga_fb.c:1931` | `void vga_fb_rect(int x, int y, int w, int h, uint8_t color)` |
| `vga_fb_rect_rgb` | function | `kernel/vga_fb.c:1955` | `void vga_fb_rect_rgb(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b)` |
| `vga_fb_reset_default` | function | `kernel/vga_fb.c:3426` | `void vga_fb_reset_default(void)` |
| `vga_fb_resize` | function | `kernel/vga_fb.c:3406` | `void vga_fb_resize(int dcols, int drows)` |
| `vga_fb_set_gfx_mode` | function | `kernel/vga_fb.c:621` | `void vga_fb_set_gfx_mode(int on)` |
| `vga_fb_set_gfx_palette` | function | `kernel/vga_fb.c:1670` | `void vga_fb_set_gfx_palette(const unsigned char *pal)` |
| `vga_fb_set_gfx_program` | function | `kernel/vga_fb.c:559` | `void vga_fb_set_gfx_program(const char *name)` |
| `vga_fb_set_palette` | function | `kernel/vga_fb.c:1837` | `static void vga_fb_set_palette(void)` |
| `vga_fb_snap_window` | function | `kernel/vga_fb.c:3378` | `void vga_fb_snap_window(int zone)` |
| `vga_fb_str` | function | `kernel/vga_fb.c:1976` | `void vga_fb_str(int col, int row, const char *s, uint8_t fg, uint8_t bg)` |
| `vga_fb_text_cursor` | function | `kernel/vga_fb.c:2890` | `void vga_fb_text_cursor(int col)` |
| `vga_fb_theme_name` | function | `kernel/vga_fb.c:2542` | `int vga_fb_theme_name(char *dst, int cap)` |
| `vga_fb_toggle_fullscreen` | function | `kernel/vga_fb.c:3220` | `void vga_fb_toggle_fullscreen(void)` |
| `vga_fb_toggle_minimize` | function | `kernel/vga_fb.c:3241` | `void vga_fb_toggle_minimize(void)` |
| `vga_fb_unpark_line` | function | `kernel/vga_fb.c:1549` | `int vga_fb_unpark_line(char *b, int *p)` |
| `wall_level` | function | `kernel/vga_fb.c:1828` | `static int wall_level(int v)` |
| `wallpaper_draw` | function | `kernel/vga_fb.c:3537` | `static void wallpaper_draw(void)` |
| `wallpaper_ensure` | function | `kernel/vga_fb.c:3480` | `static void wallpaper_ensure(void)` |
| `wallpaper_rect` | function | `kernel/vga_fb.c:3966` | `static void wallpaper_rect(int x0, int y0, int w, int h)` |
| `wallpaper_usable` | function | `kernel/vga_fb.c:3532` | `static int wallpaper_usable(void)` |
| `wm_buttons_hit` | function | `kernel/vga_fb.c:2039` | `static int wm_buttons_hit(int mx, int my, int win_x, int win_y, int win_w)` |
| `wm_clear_close` | function | `kernel/vga_fb.c:2055` | `void wm_clear_close(void)` |
| `wm_close_pending` | function | `kernel/vga_fb.c:2054` | `int wm_close_pending(void)` |
| `wm_drag_reset` | function | `kernel/vga_fb.c:69` | `static void wm_drag_reset(void)` |
| `wm_draw_buttons` | function | `kernel/vga_fb.c:2013` | `static void wm_draw_buttons(int px, int py, int win_w, uint8_t fg, uint8_t bg)` |
| `wm_emit_focus_moved` | function | `kernel/vga_fb.c:949` | `static void wm_emit_focus_moved(int before, int source)` |
| `wm_event_cfg` | function | `kernel/vga_fb.c:60` | `static wm_event_config_t wm_event_cfg(void)` |
| `wm_focus_cursor_sync` | function | `kernel/vga_fb.c:942` | `static void wm_focus_cursor_sync(const wm_notify_event_t *e)` |
| `wm_geom_cfg` | function | `kernel/vga_fb.c:49` | `static wm_geom_config_t wm_geom_cfg(void)` |
| `wm_gfx_focus_sync` | function | `kernel/vga_fb.c:1141` | `static void wm_gfx_focus_sync(int on)` |
| `wm_gfx_mode_active` | function | `kernel/vga_fb.c:2056` | `int wm_gfx_mode_active(void)` |
| `wm_init_once` | function | `kernel/vga_fb.c:1041` | `static void wm_init_once(void)` |
| `wm_snapshot_state` | function | `kernel/vga_fb.c:1082` | `static void wm_snapshot_state(wm_focus_state_t *st)` |
| `fx_wait_until` | function | `kernel/vga_fx.c:35` | `static void fx_wait_until(unsigned long deadline)` |
| `once` | function | `kernel/vga_fx.c:90` | `* once (prev[] tracks the revealed frontier per column), then the final  * restore guarantees the...` |
| `vga_fx_enabled` | function | `kernel/vga_fx.c:27` | `int vga_fx_enabled(void)` |
| `vga_fx_free` | function | `kernel/vga_fx.c:77` | `void vga_fx_free(unsigned int *buf)` |
| `vga_fx_melt_from_black` | function | `kernel/vga_fx.c:159` | `void vga_fx_melt_from_black(int x, int y, int w, int h, const unsigned int *newb)` |
| `vga_fx_melt_rect` | function | `kernel/vga_fx.c:150` | `void vga_fx_melt_rect(int x, int y, int w, int h,     const unsigned int *oldb, const unsigned in...` |
| `vga_fx_restore_rect` | function | `kernel/vga_fx.c:63` | `void vga_fx_restore_rect(int x, int y, int w, int h, const unsigned int *buf)` |
| `vga_fx_set_enabled` | function | `kernel/vga_fx.c:22` | `void vga_fx_set_enabled(int on)` |
| `vga_fx_snap_rect` | function | `kernel/vga_fx.c:41` | `unsigned int *vga_fx_snap_rect(int x, int y, int w, int h)` |
| `Client` | class | `mcp/mcp_dbg_driver.py:15` | `class Client` |
| `__init__` | method | `mcp/mcp_dbg_driver.py:16` | `def __init__(self)` |
| `close` | method | `mcp/mcp_dbg_driver.py:54` | `def close(self)` |
| `main` | method | `mcp/mcp_dbg_driver.py:64` | `def main()` |
| `request` | method | `mcp/mcp_dbg_driver.py:28` | `def request(self, method, params)` |
| `tool` | method | `mcp/mcp_dbg_driver.py:46` | `def tool(self, name, params)` |
| `Client` | class | `mcp/mcp_dogfood.py:19` | `class Client` |
| `__init__` | method | `mcp/mcp_dogfood.py:20` | `def __init__(self, addons_dir)` |
| `close` | method | `mcp/mcp_dogfood.py:68` | `def close(self)` |
| `main` | method | `mcp/mcp_dogfood.py:78` | `def main()` |
| `request` | method | `mcp/mcp_dogfood.py:40` | `def request(self, method, params)` |
| `tool` | method | `mcp/mcp_dogfood.py:58` | `def tool(self, name, params)` |
| `AddonError` | class | `mcp/minios_addons.py:56` | `class AddonError(Exception)` |
| `AddonState` | class | `mcp/minios_addons.py:377` | `class AddonState` |
| `__init__` | method | `mcp/minios_addons.py:380` | `def __init__(self, path)` |
| `_clean` | method | `mcp/minios_addons.py:62` | `def _clean(s)` |
| `_unquote` | method | `mcp/minios_addons.py:66` | `def _unquote(v)` |
| `exit_code_of` | method | `mcp/minios_addons.py:372` | `def exit_code_of(text)` |
| `fail` | method | `mcp/minios_addons.py:85` | `def fail(lineno, why)` |
| `install_addon` | method | `mcp/minios_addons.py:401` | `def install_addon(session, addon, cfg)` |
| `load` | method | `mcp/minios_addons.py:383` | `def load(self)` |
| `load_addons_dir` | method | `mcp/minios_addons.py:323` | `def load_addons_dir(addons_dir)` |
| `parse_addon_yaml` | method | `mcp/minios_addons.py:73` | `def parse_addon_yaml(text)` |
| `save` | method | `mcp/minios_addons.py:393` | `def save(self, addons)` |
| `split_for_editor` | method | `mcp/minios_addons.py:347` | `def split_for_editor(text)` |
| `validate_addon` | method | `mcp/minios_addons.py:205` | `def validate_addon(addon, source)` |
| `validate_addon_path` | method | `mcp/minios_addons.py:295` | `def validate_addon_path(path)` |
| `validate_shell_line` | method | `mcp/minios_addons.py:309` | `def validate_shell_line(line)` |
| `LogBuffer` | class | `mcp/minios_mcp.py:143` | `class LogBuffer` |
| `MCPServer` | class | `mcp/minios_mcp.py:711` | `class MCPServer` |
| `MiniOSSession` | class | `mcp/minios_mcp.py:199` | `class MiniOSSession` |
| `RPCError` | class | `mcp/minios_mcp.py:134` | `class RPCError(Exception)` |
| `ToolError` | class | `mcp/minios_mcp.py:128` | `class ToolError(Exception)` |
| `__init__` | method | `mcp/minios_mcp.py:137` | `def __init__(self, code, message)` |
| `__init__` | method | `mcp/minios_mcp.py:146` | `def __init__(self, cap)` |
| `__init__` | method | `mcp/minios_mcp.py:202` | `def __init__(self, cfg)` |
| `__init__` | method | `mcp/minios_mcp.py:714` | `def __init__(self, cfg)` |
| `_addon_install` | method | `mcp/minios_mcp.py:843` | `def _addon_install(self, args)` |
| `_addons_list` | method | `mcp/minios_mcp.py:822` | `def _addons_list(self)` |
| `_call` | method | `mcp/minios_mcp.py:759` | `def _call(self, params)` |
| `_cleanup_parts` | method | `mcp/minios_mcp.py:473` | `def _cleanup_parts(self, parts)` |
| `_close_pty` | method | `mcp/minios_mcp.py:312` | `def _close_pty(self)` |
| `_dispatch` | method | `mcp/minios_mcp.py:776` | `def _dispatch(self, name, args)` |
| `_drop_pidfile` | method | `mcp/minios_mcp.py:261` | `def _drop_pidfile(self)` |
| `_find_locked` | method | `mcp/minios_mcp.py:189` | `def _find_locked(self, marker, start)` |
| `_handle` | method | `mcp/minios_mcp.py:726` | `def _handle(self, line)` |
| `_initialize` | method | `mcp/minios_mcp.py:752` | `def _initialize(self, params)` |
| `_read_loop` | method | `mcp/minios_mcp.py:302` | `def _read_loop(self)` |
| `_reap_stale` | method | `mcp/minios_mcp.py:225` | `def _reap_stale(self)` |
| `_reply` | method | `mcp/minios_mcp.py:864` | `def _reply(self, msg)` |
| `_write_editor_line` | method | `mcp/minios_mcp.py:331` | `def _write_editor_line(self, line)` |
| `_write_line` | method | `mcp/minios_mcp.py:322` | `def _write_line(self, line)` |
| `append` | method | `mcp/minios_mcp.py:152` | `def append(self, data)` |
| `boot` | method | `mcp/minios_mcp.py:267` | `def boot(self, timeout_ms)` |
| `booted` | method | `mcp/minios_mcp.py:213` | `def booted(self)` |
| `bytes_from` | method | `mcp/minios_mcp.py:160` | `def bytes_from(self, pos)` |
| `cat` | method | `mcp/minios_mcp.py:430` | `def cat(self, path)` |
| `cat_body` | method | `mcp/minios_mcp.py:447` | `def cat_body(self, path, missing_ok)` |
| `clamp_timeout` | function | `mcp/minios_mcp.py:86` | `def clamp_timeout(ms)` |
| `close` | method | `mcp/minios_mcp.py:556` | `def close(self)` |
| `env_config` | function | `mcp/minios_mcp.py:68` | `def env_config()` |
| `expect` | method | `mcp/minios_mcp.py:350` | `def expect(self, marker, timeout_ms)` |
| `find` | method | `mcp/minios_mcp.py:172` | `def find(self, marker, start)` |
| `main` | method | `mcp/minios_mcp.py:868` | `def main()` |
| `poweroff` | method | `mcp/minios_mcp.py:517` | `def poweroff(self, timeout_ms)` |
| `run` | method | `mcp/minios_mcp.py:718` | `def run(self)` |
| `run_python` | method | `mcp/minios_mcp.py:436` | `def run_python(self, script, args, timeout_ms)` |
| `run_test` | method | `mcp/minios_mcp.py:374` | `def run_test(self, commands, expect, refute, timeout_ms)` |
| `send` | method | `mcp/minios_mcp.py:339` | `def send(self, line, timeout_ms)` |
| `snapshot` | method | `mcp/minios_mcp.py:364` | `def snapshot(self, max_bytes)` |
| `status` | method | `mcp/minios_mcp.py:216` | `def status(self)` |
| `subprocess_launch` | method | `mcp/minios_mcp.py:560` | `def subprocess_launch(cfg, slave_fd)` |
| `terminate` | method | `mcp/minios_mcp.py:537` | `def terminate(self)` |
| `text_from` | method | `mcp/minios_mcp.py:165` | `def text_from(self, pos, end)` |
| `validate_content` | function | `mcp/minios_mcp.py:115` | `def validate_content(text)` |
| `validate_path` | function | `mcp/minios_mcp.py:99` | `def validate_path(name)` |
| `wait_for` | method | `mcp/minios_mcp.py:176` | `def wait_for(self, marker, start, timeout_ms)` |
| `write` | method | `mcp/minios_mcp.py:480` | `def write(self, path, content)` |
| `run_one` | function | `mcp/mutate_mcp.sh:115` | `` |
| `FakeOS` | class | `mcp/test_minios_mcp.py:619` | `class FakeOS` |
| `MCPServer` | class | `mcp/test_minios_mcp.py:58` | `class MCPServer` |
| `TestAddonBDD` | class | `mcp/test_minios_mcp.py:820` | `class TestAddonBDD(_ConsoleBDDBase)` |
| `TestAddonHelpers` | class | `mcp/test_minios_mcp.py:579` | `class TestAddonHelpers(TestCase)` |
| `TestAddonInstall` | class | `mcp/test_minios_mcp.py:685` | `class TestAddonInstall(TestCase)` |
| `TestAddonYaml` | class | `mcp/test_minios_mcp.py:457` | `class TestAddonYaml(TestCase)` |
| `TestLogBuffer` | class | `mcp/test_minios_mcp.py:254` | `class TestLogBuffer(TestCase)` |
| `TestMiniOSBDD` | class | `mcp/test_minios_mcp.py:322` | `class TestMiniOSBDD(_ConsoleBDDBase)` |
| `TestProtocol` | class | `mcp/test_minios_mcp.py:141` | `class TestProtocol(TestCase)` |
| `TestValidation` | class | `mcp/test_minios_mcp.py:205` | `class TestValidation(TestCase)` |
| `_ConsoleBDDBase` | class | `mcp/test_minios_mcp.py:286` | `class _ConsoleBDDBase(TestCase)` |
| `__init__` | method | `mcp/test_minios_mcp.py:61` | `def __init__(self, env_extra)` |
| `__init__` | method | `mcp/test_minios_mcp.py:622` | `def __init__(self, exit_codes)` |
| `_cleanup_parts` | method | `mcp/test_minios_mcp.py:679` | `def _cleanup_parts(self, parts)` |
| `_read_response` | method | `mcp/test_minios_mcp.py:96` | `def _read_response(self)` |
| `_roundtrip` | method | `mcp/test_minios_mcp.py:102` | `def _roundtrip(self, msg)` |
| `_toolerror` | class | `mcp/test_minios_mcp.py:674` | `class _toolerror(Exception)` |
| `boot` | method | `mcp/test_minios_mcp.py:632` | `def boot(self, timeout_ms)` |
| `booted` | method | `mcp/test_minios_mcp.py:629` | `def booted(self)` |
| `broken_cat` | method | `mcp/test_minios_mcp.py:763` | `def broken_cat(path, missing_ok)` |
| `cat_body` | method | `mcp/test_minios_mcp.py:667` | `def cat_body(self, path, missing_ok)` |
| `close` | method | `mcp/test_minios_mcp.py:120` | `def close(self)` |
| `guard_server` | method | `mcp/test_minios_mcp.py:295` | `def guard_server(cls)` |
| `guarded` | method | `mcp/test_minios_mcp.py:298` | `def guarded(name, params)` |
| `have_qemu` | function | `mcp/test_minios_mcp.py:52` | `def have_qemu()` |
| `initialize` | method | `mcp/test_minios_mcp.py:80` | `def initialize(self)` |
| `load_module` | function | `mcp/test_minios_mcp.py:29` | `def load_module()` |
| `make_addon` | method | `mcp/test_minios_mcp.py:724` | `def make_addon(self)` |
| `raw` | method | `mcp/test_minios_mcp.py:91` | `def raw(self, line)` |
| `request` | method | `mcp/test_minios_mcp.py:84` | `def request(self, method, params)` |
| `send` | method | `mcp/test_minios_mcp.py:643` | `def send(self, line, timeout_ms)` |
| `setUp` | method | `mcp/test_minios_mcp.py:316` | `def setUp(self)` |
| `setUpClass` | method | `mcp/test_minios_mcp.py:143` | `def setUpClass(cls)` |
| `setUpClass` | method | `mcp/test_minios_mcp.py:207` | `def setUpClass(cls)` |
| `setUpClass` | method | `mcp/test_minios_mcp.py:256` | `def setUpClass(cls)` |
| `setUpClass` | method | `mcp/test_minios_mcp.py:324` | `def setUpClass(cls)` |
| `setUpClass` | method | `mcp/test_minios_mcp.py:459` | `def setUpClass(cls)` |
| `setUpClass` | method | `mcp/test_minios_mcp.py:581` | `def setUpClass(cls)` |
| `setUpClass` | method | `mcp/test_minios_mcp.py:687` | `def setUpClass(cls)` |
| `setUpClass` | method | `mcp/test_minios_mcp.py:824` | `def setUpClass(cls)` |
| `tearDownClass` | method | `mcp/test_minios_mcp.py:149` | `def tearDownClass(cls)` |
| `tearDownClass` | method | `mcp/test_minios_mcp.py:331` | `def tearDownClass(cls)` |
| `tearDownClass` | method | `mcp/test_minios_mcp.py:719` | `def tearDownClass(cls)` |
| `tearDownClass` | method | `mcp/test_minios_mcp.py:861` | `def tearDownClass(cls)` |
| `test_addons_list` | method | `mcp/test_minios_mcp.py:869` | `def test_addons_list(self)` |
| `test_bad_indent_rejected` | method | `mcp/test_minios_mcp.py:487` | `def test_bad_indent_rejected(self)` |
| `test_bad_kind_rejected` | method | `mcp/test_minios_mcp.py:541` | `def test_bad_kind_rejected(self)` |
| `test_bounds` | method | `mcp/test_minios_mcp.py:261` | `def test_bounds(self)` |
| `test_content_accepts_ascii` | method | `mcp/test_minios_mcp.py:223` | `def test_content_accepts_ascii(self)` |
| `test_content_rejects_non_printable` | method | `mcp/test_minios_mcp.py:226` | `def test_content_rejects_non_printable(self)` |
| `test_cursor_prevents_stale_match` | method | `mcp/test_minios_mcp.py:275` | `def test_cursor_prevents_stale_match(self)` |
| `test_exit_code_of` | method | `mcp/test_minios_mcp.py:606` | `def test_exit_code_of(self)` |
| `test_find_and_total` | method | `mcp/test_minios_mcp.py:268` | `def test_find_and_total(self)` |
| `test_host_kind_accepts_empty_files` | method | `mcp/test_minios_mcp.py:518` | `def test_host_kind_accepts_empty_files(self)` |
| `test_host_kind_requires_artifact` | method | `mcp/test_minios_mcp.py:549` | `def test_host_kind_requires_artifact(self)` |
| `test_initialize` | method | `mcp/test_minios_mcp.py:152` | `def test_initialize(self)` |
| `test_install_build_failure_aborts` | method | `mcp/test_minios_mcp.py:811` | `def test_install_build_failure_aborts(self)` |
| `test_install_fixture` | method | `mcp/test_minios_mcp.py:875` | `def test_install_fixture(self)` |
| `test_install_mismatch_aborts_and_cleans` | method | `mcp/test_minios_mcp.py:759` | `def test_install_mismatch_aborts_and_cleans(self)` |
| `test_install_multi_chunk_reassembly` | method | `mcp/test_minios_mcp.py:773` | `def test_install_multi_chunk_reassembly(self)` |
| `test_install_refuses_host_before_touching_session` | method | `mcp/test_minios_mcp.py:563` | `def test_install_refuses_host_before_touching_session(self)` |
| `test_install_success` | method | `mcp/test_minios_mcp.py:746` | `def test_install_success(self)` |
| `test_install_unknown_addon_fails` | method | `mcp/test_minios_mcp.py:884` | `def test_install_unknown_addon_fails(self)` |
| `test_install_verify_failure_aborts` | method | `mcp/test_minios_mcp.py:804` | `def test_install_verify_failure_aborts(self)` |
| `test_malformed_json` | method | `mcp/test_minios_mcp.py:174` | `def test_malformed_json(self)` |
| `test_parse_valid` | method | `mcp/test_minios_mcp.py:469` | `def test_parse_valid(self)` |
| `test_path_accepts_plain_names` | method | `mcp/test_minios_mcp.py:212` | `def test_path_accepts_plain_names(self)` |
| `test_path_rejects_long` | method | `mcp/test_minios_mcp.py:220` | `def test_path_rejects_long(self)` |
| `test_path_rejects_unsafe` | method | `mcp/test_minios_mcp.py:216` | `def test_path_rejects_unsafe(self)` |
| `test_ping` | method | `mcp/test_minios_mcp.py:166` | `def test_ping(self)` |
| `test_reference_kind_carries_nothing` | method | `mcp/test_minios_mcp.py:533` | `def test_reference_kind_carries_nothing(self)` |
| `test_send_empty_line_rejected` | method | `mcp/test_minios_mcp.py:189` | `def test_send_empty_line_rejected(self)` |
| `test_send_not_booted` | method | `mcp/test_minios_mcp.py:183` | `def test_send_not_booted(self)` |
| `test_split_for_editor_chunks` | method | `mcp/test_minios_mcp.py:591` | `def test_split_for_editor_chunks(self)` |
| `test_split_rejects_long_line` | method | `mcp/test_minios_mcp.py:598` | `def test_split_rejects_long_line(self)` |
| `test_split_rejects_non_ascii` | method | `mcp/test_minios_mcp.py:602` | `def test_split_rejects_non_ascii(self)` |
| `test_state_roundtrip` | method | `mcp/test_minios_mcp.py:611` | `def test_state_roundtrip(self)` |
| `test_t01_boot` | method | `mcp/test_minios_mcp.py:335` | `def test_t01_boot(self)` |
| `test_t02_expect` | method | `mcp/test_minios_mcp.py:345` | `def test_t02_expect(self)` |
| `test_t03_write_and_cat` | method | `mcp/test_minios_mcp.py:352` | `def test_t03_write_and_cat(self)` |
| `test_t04_toolchain_elf` | method | `mcp/test_minios_mcp.py:362` | `def test_t04_toolchain_elf(self)` |
| `test_t05_toolchain_cvm` | method | `mcp/test_minios_mcp.py:373` | `def test_t05_toolchain_cvm(self)` |
| `test_t06_selfhosted_compiler` | method | `mcp/test_minios_mcp.py:383` | `def test_t06_selfhosted_compiler(self)` |
| `test_t07_bin_command_path` | method | `mcp/test_minios_mcp.py:389` | `def test_t07_bin_command_path(self)` |
| `test_t08_python_script` | method | `mcp/test_minios_mcp.py:397` | `def test_t08_python_script(self)` |
| `test_t09_py_eval` | method | `mcp/test_minios_mcp.py:404` | `def test_t09_py_eval(self)` |
| `test_t10_minios_test` | method | `mcp/test_minios_mcp.py:409` | `def test_t10_minios_test(self)` |
| `test_t11_poweroff_and_reboot` | method | `mcp/test_minios_mcp.py:430` | `def test_t11_poweroff_and_reboot(self)` |
| `test_test_not_booted` | method | `mcp/test_minios_mcp.py:195` | `def test_test_not_booted(self)` |
| `test_timeout_clamped` | method | `mcp/test_minios_mcp.py:230` | `def test_timeout_clamped(self)` |
| `test_tools_list` | method | `mcp/test_minios_mcp.py:158` | `def test_tools_list(self)` |
| `test_unknown_key_rejected` | method | `mcp/test_minios_mcp.py:483` | `def test_unknown_key_rejected(self)` |
| `test_unknown_method` | method | `mcp/test_minios_mcp.py:170` | `def test_unknown_method(self)` |
| `test_unknown_tool` | method | `mcp/test_minios_mcp.py:178` | `def test_unknown_tool(self)` |
| `test_validate_accepts_valid` | method | `mcp/test_minios_mcp.py:479` | `def test_validate_accepts_valid(self)` |
| `test_validate_rejects_bad_dst` | method | `mcp/test_minios_mcp.py:491` | `def test_validate_rejects_bad_dst(self)` |
| `test_validate_rejects_control_chars` | method | `mcp/test_minios_mcp.py:508` | `def test_validate_rejects_control_chars(self)` |
| `test_validate_rejects_empty_files` | method | `mcp/test_minios_mcp.py:513` | `def test_validate_rejects_empty_files(self)` |
| `test_validate_rejects_long_build_line` | method | `mcp/test_minios_mcp.py:500` | `def test_validate_rejects_long_build_line(self)` |
| `test_validate_rejects_missing_name` | method | `mcp/test_minios_mcp.py:496` | `def test_validate_rejects_missing_name(self)` |
| `test_write_rejects_line_too_long` | method | `mcp/test_minios_mcp.py:234` | `def test_write_rejects_line_too_long(self)` |
| `test_write_rejects_too_many_lines` | method | `mcp/test_minios_mcp.py:243` | `def test_write_rejects_too_many_lines(self)` |
| `tool` | method | `mcp/test_minios_mcp.py:110` | `def tool(self, name, params)` |
| `write` | method | `mcp/test_minios_mcp.py:636` | `def write(self, path, content)` |
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
| `LNX_EOPNOTSUPP` | macro | `net/net.c:1080` | `#define LNX_EOPNOTSUPP` |
| `LNX_EPIPE` | macro | `net/net.c:1075` | `#define LNX_EPIPE` |
| `LNX_EPROTONOSUPPORT` | macro | `net/net.c:1079` | `#define LNX_EPROTONOSUPPORT` |
| `LNX_ETIMEDOUT` | macro | `net/net.c:1084` | `#define LNX_ETIMEDOUT` |
| `LNX_FD_CLOEXEC` | macro | `net/net.c:1061` | `#define LNX_FD_CLOEXEC` |
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
| `net_cmd_dns` | function | `net/net.c:1799` | `void net_cmd_dns(const char *host)` |
| `net_cmd_ping` | function | `net/net.c:1788` | `void net_cmd_ping(const char *ip_text)` |
| `net_cmd_status` | function | `net/net.c:1760` | `void net_cmd_status(void)` |
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
| `net_get_addrs` | function | `net/net.c:1782` | `void net_get_addrs(unsigned char mac_out[NET_ETH_ALEN], unsigned char ip_out[4])` |
| `net_icmp_rx` | function | `net/net.c:348` | `static void net_icmp_rx(const unsigned char *ip, unsigned len)` |
| `net_init` | function | `net/net.c:1820` | `void net_init(void)` |
| `net_ip_send` | function | `net/net.c:172` | `static int net_ip_send(const unsigned char *dip, unsigned char proto,                        cons...` |
| `net_listen` | function | `net/net.c:927` | `int net_listen(unsigned short port)` |
| `net_load_sockaddr` | function | `net/net.c:1185` | `static long net_load_sockaddr(long addr, long len, unsigned char ip[4], unsigned short *port)` |
| `net_open` | function | `net/net.c:886` | `int net_open(void)` |
| `net_parse_ip` | function | `net/net.c:1735` | `static int net_parse_ip(const char *text, unsigned char ip[4])` |
| `net_ping` | function | `net/net.c:377` | `static int net_ping(const unsigned char ip[4])` |
| `net_put16` | function | `net/net.c:57` | `static void net_put16(unsigned char *p, unsigned short v)` |
| `net_put32` | function | `net/net.c:62` | `static void net_put32(unsigned char *p, unsigned int v)` |
| `net_put_sockaddr` | function | `net/net.c:1158` | `static void net_put_sockaddr(unsigned char *sa, const unsigned char ip[4], unsigned short port)` |
| `net_recv` | function | `net/net.c:906` | `int net_recv(int fd, char *buf, int len)` |
| `net_recv_timeout` | function | `net/net.c:911` | `int net_recv_timeout(int fd, char *buf, int len, unsigned long timeout_ms)` |
| `net_register_symbols` | function | `net/net.c:1812` | `void net_register_symbols(void)` |
| `net_rx_handle_frame` | function | `net/net.c:822` | `void net_rx_handle_frame(const unsigned char *frame, unsigned len)` |
| `net_send` | function | `net/net.c:901` | `int net_send(int fd, const char *buf, int len)` |
| `net_send_bytes` | function | `net/net.c:1347` | `static long net_send_bytes(long fd, const unsigned char *buf, long len,                          ...` |
| `net_sock_alloc` | function | `net/net.c:469` | `static struct net_tcp_sock *net_sock_alloc(void)` |
| `net_sock_index` | function | `net/net.c:484` | `static int net_sock_index(const struct net_tcp_sock *s)` |
| `net_sock_state` | function | `net/net.c:976` | `int net_sock_state(int fd)` |
| `net_socket_revents` | function | `net/net.c:1664` | `static unsigned short net_socket_revents(long fd)` |
| `net_store_sockaddr` | function | `net/net.c:1168` | `static long net_store_sockaddr(long addr, long lenp, const unsigned char ip[4],                  ...` |
| `net_sys_accept` | function | `net/net.c:1329` | `long net_sys_accept(long fd, long sockaddr, long addrlen)` |
| `net_sys_bind` | function | `net/net.c:1296` | `long net_sys_bind(long fd, long sockaddr, long addrlen)` |
| `net_sys_close` | function | `net/net.c:1523` | `long net_sys_close(long fd)` |
| `net_sys_connect` | function | `net/net.c:1249` | `long net_sys_connect(long fd, long sockaddr, long addrlen)` |
| `net_sys_dns` | function | `net/net.c:1724` | `long net_sys_dns(long host)` |
| `net_sys_fcntl` | function | `net/net.c:1643` | `long net_sys_fcntl(long fd, long cmd, long arg)` |
| `net_sys_getpeername` | function | `net/net.c:1625` | `long net_sys_getpeername(long fd, long addr, long lenp)` |
| `net_sys_getsockname` | function | `net/net.c:1616` | `long net_sys_getsockname(long fd, long addr, long lenp)` |
| `net_sys_getsockopt` | function | `net/net.c:1569` | `long net_sys_getsockopt(long fd, long level, long name, long val, long lenp)` |
| `net_sys_is_socket` | function | `net/net.c:1102` | `int net_sys_is_socket(long fd)` |
| `net_sys_listen` | function | `net/net.c:1318` | `long net_sys_listen(long fd, long backlog)` |
| `net_sys_poll` | function | `net/net.c:1684` | `long net_sys_poll(long fds, long nfds, long timeout_ms)` |
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
| `RTL_REG_9346CR` | macro | `net/rtl8139.c:52` | `#define RTL_REG_9346CR` |
| `RTL_REG_CAPR` | macro | `net/rtl8139.c:50` | `#define RTL_REG_CAPR` |
| `RTL_REG_CBR` | macro | `net/rtl8139.c:51` | `#define RTL_REG_CBR` |
| `RTL_REG_CONFIG1` | macro | `net/rtl8139.c:53` | `#define RTL_REG_CONFIG1` |
| `RTL_REG_CR` | macro | `net/rtl8139.c:46` | `#define RTL_REG_CR` |
| `RTL_REG_RBSTART` | macro | `net/rtl8139.c:49` | `#define RTL_REG_RBSTART` |
| `RTL_REG_TSAD0` | macro | `net/rtl8139.c:48` | `#define RTL_REG_TSAD0` |
| `RTL_REG_TSD0` | macro | `net/rtl8139.c:47` | `#define RTL_REG_TSD0` |
| `RTL_TX_YIELD_EVERY` | macro | `net/rtl8139.c:147` | `#define RTL_TX_YIELD_EVERY` |
| `deleted` | function | `net/rtl8139.c:79` | `* been deleted (a second base/per-ms pair beside ktime's is a second  * clock, and drivers must n...` |
| `inl_port` | function | `net/rtl8139.c:33` | `static unsigned int inl_port(unsigned short port)` |
| `outl_port` | function | `net/rtl8139.c:29` | `static void outl_port(unsigned short port, unsigned int val)` |
| `rtl_counters` | function | `net/rtl8139.c:191` | `void rtl_counters(unsigned int *tx_frames, unsigned int *rx_frames)` |
| `rtl_find` | function | `net/rtl8139.c:58` | `static unsigned short rtl_find(void)` |
| `rtl_get_mac` | function | `net/rtl8139.c:182` | `void rtl_get_mac(unsigned char out[NET_ETH_ALEN])` |
| `rtl_init` | function | `net/rtl8139.c:112` | `void rtl_init(void)` |
| `rtl_iobase` | function | `net/rtl8139.c:187` | `unsigned short rtl_iobase(void)` |
| `rtl_poll` | function | `net/rtl8139.c:215` | `void rtl_poll(void)` |
| `rtl_present` | function | `net/rtl8139.c:99` | `int rtl_present(void)` |
| `rtl_reg16` | function | `net/rtl8139.c:41` | `static unsigned short rtl_reg16(unsigned short off)` |
| `rtl_reg16_w` | function | `net/rtl8139.c:42` | `static void rtl_reg16_w(unsigned short off, unsigned short v)` |
| `rtl_reg32` | function | `net/rtl8139.c:43` | `static unsigned int rtl_reg32(unsigned short off)` |
| `rtl_reg32_w` | function | `net/rtl8139.c:44` | `static void rtl_reg32_w(unsigned short off, unsigned int v)` |
| `rtl_reg8` | function | `net/rtl8139.c:39` | `static unsigned char rtl_reg8(unsigned short off)` |
| `rtl_reg8_w` | function | `net/rtl8139.c:40` | `static void rtl_reg8_w(unsigned short off, unsigned char v)` |
| `rtl_reset` | function | `net/rtl8139.c:103` | `static void rtl_reset(void)` |
| `rtl_send` | function | `net/rtl8139.c:158` | `int rtl_send(const unsigned char *frame, unsigned len)` |
| `rtl_tx_wait` | function | `net/rtl8139.c:149` | `static int rtl_tx_wait(unsigned slot, unsigned long deadline)` |
| `PORT_IO_DEFINED` | macro | `net/tls.c:809` | `#define PORT_IO_DEFINED` |
| `build_client_hello` | function | `net/tls.c:190` | `static int build_client_hello(struct tls_session *s, unsigned char *out)` |
| `client_finish_flight` | function | `net/tls.c:244` | `static int client_finish_flight(struct tls_session *s)` |
| `cmos_read` | function | `net/tls.c:821` | `static inline unsigned char cmos_read(unsigned char reg)` |
| `exchange` | function | `net/tls.c:173` | `* key exchange (ClientHello, ClientKeyExchange) go out in plaintext  * records, as TLS 1.2 requir...` |
| `inb` | function | `net/tls.c:813` | `static inline unsigned char inb(unsigned short port)` |
| `number` | function | `net/tls.c:64` | `* The nonce_explicit is the sequence number (RFC 5288 allows it and * OpenSSL uses it);` |
| `outb` | function | `net/tls.c:810` | `static inline void outb(unsigned short port, unsigned char v)` |
| `parse_certificate` | function | `net/tls.c:370` | `static int parse_certificate(struct tls_session *s,                              const unsigned c...` |
| `parse_server_hello` | function | `net/tls.c:340` | `static int parse_server_hello(struct tls_session *s,                               const unsigned...` |
| `parse_server_key_exchange` | function | `net/tls.c:401` | `static int parse_server_key_exchange(struct tls_session *s,                                      ...` |
| `tls_aad` | function | `net/tls.c:52` | `static void tls_aad(unsigned char aad[13], int type, unsigned long long seq,                     ...` |
| `tls_fail` | function | `net/tls.c:25` | `static void tls_fail(struct tls_session *s, const char *stage, const char *reason)` |
| `tls_fd_of` | function | `net/tls.c:33` | `static int tls_fd_of(const struct tls_session *s)` |
| `tls_free_fd` | function | `net/tls.c:40` | `void tls_free_fd(int fd)` |
| `tls_handshake` | function | `net/tls.c:466` | `int tls_handshake(int fd, const char *host)` |
| `tls_now_days` | function | `net/tls.c:826` | `long tls_now_days(void)` |
| `tls_random` | function | `net/tls.c:795` | `void tls_random(unsigned char *out, unsigned len)` |
| `tls_rdtsc` | function | `net/tls.c:789` | `static inline unsigned long long tls_rdtsc(void)` |
| `tls_read_record` | function | `net/tls.c:114` | `static int tls_read_record(struct tls_session *s, int fd, int deadline_ms)` |
| `tls_recv` | function | `net/tls.c:696` | `int tls_recv(int fd, char *buf, int len)` |
| `tls_send` | function | `net/tls.c:687` | `int tls_send(int fd, const char *buf, int len)` |
| `tls_send_raw_record` | function | `net/tls.c:95` | `static int tls_send_raw_record(struct tls_session *s, int type,                                co...` |
| `tls_send_record` | function | `net/tls.c:66` | `static int tls_send_record(struct tls_session *s, int type,                            const unsi...` |
| `tls_sys_handshake` | function | `net/tls.c:772` | `long tls_sys_handshake(long fd, long host)` |
| `tls_sys_recv` | function | `net/tls.c:782` | `long tls_sys_recv(long fd, long buf, long len)` |
| `tls_sys_send` | function | `net/tls.c:777` | `long tls_sys_send(long fd, long buf, long len)` |
| `TLS_BN_WORDS` | macro | `net/tls_crypto.c:535` | `#define TLS_BN_WORDS` |
| `aes128_encrypt_block` | function | `net/tls_crypto.c:263` | `void aes128_encrypt_block(const unsigned char key[16],                           const unsigned c...` |
| `aes128_gcm_open` | function | `net/tls_crypto.c:487` | `int aes128_gcm_open(const unsigned char key[16],                     const unsigned char salt[4],...` |
| `aes128_gcm_open_core` | function | `net/tls_crypto.c:516` | `int aes128_gcm_open_core(const unsigned char key[16],                          const unsigned cha...` |
| `aes128_gcm_seal` | function | `net/tls_crypto.c:475` | `int aes128_gcm_seal(const unsigned char key[16],                     const unsigned char salt[4],...` |
| `aes128_gcm_seal_core` | function | `net/tls_crypto.c:505` | `int aes128_gcm_seal_core(const unsigned char key[16],                          const unsigned cha...` |
| `aes_key_expand` | function | `net/tls_crypto.c:235` | `static void aes_key_expand(const unsigned char key[16], unsigned rk[44])` |
| `aes_mixcol` | function | `net/tls_crypto.c:253` | `static void aes_mixcol(unsigned a0, unsigned a1, unsigned a2, unsigned a3,                       ...` |
| `aes_xtime` | function | `net/tls_crypto.c:230` | `static unsigned aes_xtime(unsigned x)` |
| `bn_add` | function | `net/tls_crypto.c:559` | `static unsigned bn_add(const unsigned *a, const unsigned *b, unsigned *r, int nw)` |
| `bn_cmp` | function | `net/tls_crypto.c:549` | `static int bn_cmp(const unsigned *a, const unsigned *b, int nw)` |
| `bn_dbl_mod` | function | `net/tls_crypto.c:584` | `static void bn_dbl_mod(const unsigned *a, const unsigned *n, const unsigned *v,                  ...` |
| `bn_from_be` | function | `net/tls_crypto.c:663` | `static void bn_from_be(const unsigned char *bytes, unsigned len,                        unsigned ...` |
| `bn_is_zero` | function | `net/tls_crypto.c:542` | `static int bn_is_zero(const unsigned *a, int nw)` |
| `bn_mont_mul` | function | `net/tls_crypto.c:596` | `static void bn_mont_mul(const unsigned *a, const unsigned *b, const unsigned *n,                 ...` |
| `bn_mont_n0inv` | function | `net/tls_crypto.c:635` | `static unsigned bn_mont_n0inv(unsigned n0)` |
| `bn_mont_r2` | function | `net/tls_crypto.c:643` | `static void bn_mont_r2(const unsigned *n, const unsigned *v, int nw,                        unsig...` |
| `bn_sub` | function | `net/tls_crypto.c:571` | `static unsigned bn_sub(const unsigned *a, const unsigned *b, unsigned *r, int nw)` |
| `bn_to_be` | function | `net/tls_crypto.c:671` | `static void bn_to_be(const unsigned *a, unsigned char *out, unsigned len)` |
| `bn_zero` | function | `net/tls_crypto.c:537` | `static void bn_zero(unsigned *a, int nw)` |
| `der_parse_sig` | function | `net/tls_crypto.c:1129` | `static int der_parse_sig(const unsigned char *sig, unsigned sig_len,                          con...` |
| `ec_boot` | function | `net/tls_crypto.c:1080` | `static void ec_boot(void)` |
| `ec_curve` | struct | `net/tls_crypto.c:838` | `` |
| `ec_curve_by_id` | function | `net/tls_crypto.c:1076` | `static struct ec_curve *ec_curve_by_id(int curve)` |
| `ec_init` | function | `net/tls_crypto.c:848` | `static void ec_init(struct ec_curve *c, const unsigned char *p,                     const unsigne...` |
| `ecdsa_verify` | function | `net/tls_crypto.c:1163` | `int ecdsa_verify(int curve, const unsigned char pub_x[], const unsigned char pub_y[],            ...` |
| `gcm_ctr` | function | `net/tls_crypto.c:467` | `static void gcm_ctr(const unsigned char key[16], const unsigned char salt[4],                    ...` |
| `gcm_ctr_core` | function | `net/tls_crypto.c:427` | `static void gcm_ctr_core(const unsigned char key[16],                          const unsigned cha...` |
| `gcm_tag` | function | `net/tls_crypto.c:457` | `static void gcm_tag(const unsigned char key[16], const unsigned char salt[4],                    ...` |
| `gcm_tag_core` | function | `net/tls_crypto.c:384` | `static void gcm_tag_core(const unsigned char key[16],                          const unsigned cha...` |
| `gf128` | struct | `net/tls_crypto.c:316` | `` |
| `gf_mul` | function | `net/tls_crypto.c:334` | `static gf128 gf_mul(gf128 z, gf128 h)` |
| `gf_put` | function | `net/tls_crypto.c:351` | `static gf128 gf_put(const unsigned char *p)` |
| `gf_shift_right` | function | `net/tls_crypto.c:321` | `static gf128 gf_shift_right(gf128 v)` |
| `ghash_blocks` | function | `net/tls_crypto.c:361` | `static gf128 ghash_blocks(gf128 z, gf128 h, const unsigned char *data, unsigned len)` |
| `hmac_sha256` | function | `net/tls_crypto.c:135` | `void hmac_sha256(const unsigned char *key, unsigned klen,                  const unsigned char *d...` |

Next: [SYMBOLS_p11.md](SYMBOLS_p11.md)
