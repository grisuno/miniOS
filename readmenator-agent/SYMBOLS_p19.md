# Symbols (page 19 of 26)
Previous: [SYMBOLS_p18.md](SYMBOLS_p18.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `file_assoc_lookup` | function | `progs/file/file.c:318` | `static const char *file_assoc_lookup(const char *ext)` |
| `file_ext_of` | function | `progs/file/file.c:122` | `static void file_ext_of(const char *fname, char *dst, unsigned cap)` |
| `file_gui_run` | function | `progs/file/file.c:779` | `static void file_gui_run(void)` |
| `file_icon_decode` | function | `progs/file/file.c:165` | `static int file_icon_decode(const char *path, unsigned char *px,                             unsi...` |
| `file_icon_kind` | function | `progs/file/file.c:146` | `static int file_icon_kind(const char *fname, int isdir)` |
| `file_icon_sz` | function | `progs/file/file.c:158` | `static int file_icon_sz(void)` |
| `file_icons_load` | function | `progs/file/file.c:213` | `static int file_icons_load(void)` |
| `file_join` | function | `progs/file/file.c:245` | `static int file_join(const char *dir, const char *name, char *dst, unsigned cap)` |
| `file_open_text` | function | `progs/file/file.c:430` | `static void file_open_text(const char *path)` |
| `file_parent` | function | `progs/file/file.c:259` | `static void file_parent(char *path)` |
| `file_preview_blit` | function | `progs/file/file.c:385` | `static void file_preview_blit(int ox, int oy)` |
| `file_preview_load` | function | `progs/file/file.c:351` | `static int file_preview_load(const char *path)` |
| `file_refresh` | function | `progs/file/file.c:336` | `static void file_refresh(void)` |
| `file_run_shell` | function | `progs/file/file.c:441` | `static void file_run_shell(const char *path)` |
| `file_selftest` | function | `progs/file/file.c:613` | `static int file_selftest(void)` |
| `file_spawn_visible` | function | `progs/file/file.c:407` | `static long file_spawn_visible(const char *tool, int argc, const char **argv,                    ...` |
| `file_sys_dir_list` | function | `progs/file/file.c:101` | `static long file_sys_dir_list(const char *path, char *buf, long cap)` |
| `file_sys_spawn` | function | `progs/file/file.c:111` | `static long file_sys_spawn(const char *path, int argc, const char **argv)` |
| `file_toggle_icons` | function | `progs/file/file.c:238` | `static int file_toggle_icons(void)` |
| `file_ui_build` | function | `progs/file/file.c:511` | `static void file_ui_build(struct nk_context *ctx)` |
| `main` | function | `progs/file/file.c:838` | `int main(int argc, char **argv)` |
| `FASSOC_EXT_MAX` | macro | `progs/file/file_assoc.h:22` | `#define FASSOC_EXT_MAX` |
| `FASSOC_GROW_DEN` | macro | `progs/file/file_assoc.h:42` | `#define FASSOC_GROW_DEN` |
| `FASSOC_GROW_NUM` | macro | `progs/file/file_assoc.h:38` | `#define FASSOC_GROW_NUM` |
| `FASSOC_HARD_MAX` | macro | `progs/file/file_assoc.h:34` | `#define FASSOC_HARD_MAX` |
| `FASSOC_INIT_CAP` | macro | `progs/file/file_assoc.h:30` | `#define FASSOC_INIT_CAP` |
| `FASSOC_PROG_MAX` | macro | `progs/file/file_assoc.h:26` | `#define FASSOC_PROG_MAX` |
| `MINIOS_FILE_ASSOC_H` | macro | `progs/file/file_assoc.h:15` | `#define MINIOS_FILE_ASSOC_H` |
| `fassoc_clear` | function | `progs/file/file_assoc.h:89` | `static void fassoc_clear(struct fassoc_table *t)` |
| `fassoc_count` | function | `progs/file/file_assoc.h:150` | `static size_t fassoc_count(const struct fassoc_table *t)` |
| `fassoc_entry` | struct | `progs/file/file_assoc.h:46` | `` |
| `fassoc_ext_ok` | function | `progs/file/file_assoc.h:59` | `static int fassoc_ext_ok(const char *ext)` |
| `fassoc_free` | function | `progs/file/file_assoc.h:95` | `static void fassoc_free(struct fassoc_table *t)` |
| `fassoc_lookup` | function | `progs/file/file_assoc.h:140` | `static const char *fassoc_lookup(const struct fassoc_table *t, const char *ext)` |
| `fassoc_prog_ok` | function | `progs/file/file_assoc.h:73` | `static int fassoc_prog_ok(const char *prog)` |
| `fassoc_push` | function | `progs/file/file_assoc.h:125` | `static int fassoc_push(struct fassoc_table *t, const char *ext, const char *prog)` |
| `fassoc_reserve` | function | `progs/file/file_assoc.h:104` | `static int fassoc_reserve(struct fassoc_table *t, size_t want)` |
| `fassoc_table` | struct | `progs/file/file_assoc.h:52` | `` |
| `FUI_BODY_CAP` | macro | `progs/freedomui/freedomui_minios.c:53` | `#define FUI_BODY_CAP` |
| `FUI_COLS` | macro | `progs/freedomui/freedomui_minios.c:51` | `#define FUI_COLS` |
| `FUI_FONT_H` | macro | `progs/freedomui/freedomui_minios.c:62` | `#define FUI_FONT_H` |
| `FUI_FONT_W` | macro | `progs/freedomui/freedomui_minios.c:61` | `#define FUI_FONT_W` |
| `FUI_HDR_MAX` | macro | `progs/freedomui/freedomui_minios.c:54` | `#define FUI_HDR_MAX` |
| `FUI_HOPS_MAX` | macro | `progs/freedomui/freedomui_minios.c:60` | `#define FUI_HOPS_MAX` |
| `FUI_HOST_MAX` | macro | `progs/freedomui/freedomui_minios.c:57` | `#define FUI_HOST_MAX` |
| `FUI_NET_BUF` | macro | `progs/freedomui/freedomui_minios.c:55` | `#define FUI_NET_BUF` |
| `FUI_PATH_MAX` | macro | `progs/freedomui/freedomui_minios.c:58` | `#define FUI_PATH_MAX` |
| `FUI_REQ_MAX` | macro | `progs/freedomui/freedomui_minios.c:56` | `#define FUI_REQ_MAX` |
| `FUI_TEXT_ROWS` | macro | `progs/freedomui/freedomui_minios.c:52` | `#define FUI_TEXT_ROWS` |
| `FUI_TITLE_MAX` | macro | `progs/freedomui/freedomui_minios.c:63` | `#define FUI_TITLE_MAX` |
| `FUI_URL_MAX` | macro | `progs/freedomui/freedomui_minios.c:59` | `#define FUI_URL_MAX` |
| `FreedomUiConfig` | struct | `progs/freedomui/freedomui_minios.c:69` | `` |
| `freedomui_build_palette` | function | `progs/freedomui/freedomui_minios.c:130` | `static long freedomui_build_palette(unsigned char *pal, long cap)` |
| `freedomui_default` | function | `progs/freedomui/freedomui_minios.c:97` | `static FreedomUiConfig freedomui_default(void)` |
| `freedomui_engine_text` | function | `progs/freedomui/freedomui_minios.c:145` | `static long freedomui_engine_text(char *body, long n, char **title, char **text)` |
| `freedomui_host_entry` | function | `progs/freedomui/freedomui_minios.c:1067` | `int freedomui_host_entry(FreedomUiConfig *c)` |
| `freedomui_host_probe` | function | `progs/freedomui/freedomui_minios.c:984` | `static long freedomui_host_probe(FreedomUiConfig *c)` |
| `freedomui_selftest` | function | `progs/freedomui/freedomui_minios.c:896` | `static long freedomui_selftest(void)` |
| `freedomui_sys_kbd` | function | `progs/freedomui/freedomui_minios.c:221` | `static long freedomui_sys_kbd(void)` |
| `freedomui_sys_kbd_raw` | function | `progs/freedomui/freedomui_minios.c:235` | `static long freedomui_sys_kbd_raw(long on)` |
| `freedomui_sys_mouse` | function | `progs/freedomui/freedomui_minios.c:214` | `static long freedomui_sys_mouse(long *m)` |
| `freedomui_sys_palette` | function | `progs/freedomui/freedomui_minios.c:207` | `static long freedomui_sys_palette(unsigned char *pal)` |
| `freedomui_sys_present` | function | `progs/freedomui/freedomui_minios.c:193` | `static long freedomui_sys_present(long buf, long origin)` |
| `freedomui_sys_title` | function | `progs/freedomui/freedomui_minios.c:200` | `static long freedomui_sys_title(char *t)` |
| `freedomui_sys_vga_mode` | function | `progs/freedomui/freedomui_minios.c:228` | `static long freedomui_sys_vga_mode(long on)` |
| `freedomui_sys_yield` | function | `progs/freedomui/freedomui_minios.c:242` | `static long freedomui_sys_yield(void)` |
| `fui_append` | function | `progs/freedomui/freedomui_minios.c:249` | `static long fui_append(char *dst, long pos, char *src, long cap)` |
| `fui_browse` | function | `progs/freedomui/freedomui_minios.c:817` | `static long fui_browse(FreedomUiConfig *c)` |
| `fui_fetch_raw` | function | `progs/freedomui/freedomui_minios.c:470` | `static long fui_fetch_raw(FreedomUiConfig *c, char *host, char *path, long port, long secure)` |
| `fui_parse_headers` | function | `progs/freedomui/freedomui_minios.c:352` | `static long fui_parse_headers(FreedomUiConfig *c, char *hdr, long *status, long *clen, long *hasc...` |
| `fui_render` | function | `progs/freedomui/freedomui_minios.c:698` | `static long fui_render(FreedomUiConfig *c, size_t off)` |
| `fui_split_url` | function | `progs/freedomui/freedomui_minios.c:283` | `static long fui_split_url(FreedomUiConfig *c, char *url, char *host, char *path, long *port, long...` |
| `fui_strlen` | function | `progs/freedomui/freedomui_minios.c:267` | `static long fui_strlen(char *s, long cap)` |
| `main` | function | `progs/freedomui/freedomui_minios.c:1072` | `int main(int argc, char **argv)` |
| `net_dns_resolve` | function | `progs/freedomui/freedomui_minios.c:44` | `int net_dns_resolve(const char *host);` |
| `present_buf` | type_alias | `progs/freedomui/freedomui_minios.c:69` | `typedef struct FreedomUiConfig { long present_buf;` |
| `tls_close` | function | `progs/freedomui/freedomui_minios.c:48` | `void tls_close(int fd);` |
| `tls_handshake` | function | `progs/freedomui/freedomui_minios.c:45` | `int tls_handshake(int fd, char *host);` |
| `tls_recv` | function | `progs/freedomui/freedomui_minios.c:47` | `int tls_recv(int fd, char *buf, int len);` |
| `tls_send` | function | `progs/freedomui/freedomui_minios.c:46` | `int tls_send(int fd, char *buf, int len);` |
| `media_decoder_run` | function | `progs/freedomui/media_unavailable.c:41` | `void media_decoder_run(int out_fd, int cmd_fd)` |
| `write_all` | function | `progs/freedomui/media_unavailable.c:20` | `static void write_all(int fd, const void *buf, size_t len)` |
| `FREEDOM_GUI_BUTTONS` | macro | `progs/freedomui/platform_minios.c:44` | `#define FREEDOM_GUI_BUTTONS` |
| `FREEDOM_GUI_CLIP_MAX` | macro | `progs/freedomui/platform_minios.c:33` | `#define FREEDOM_GUI_CLIP_MAX` |
| `FREEDOM_GUI_KBD_DRAIN_MAX` | macro | `progs/freedomui/platform_minios.c:29` | `#define FREEDOM_GUI_KBD_DRAIN_MAX` |
| `FREEDOM_GUI_KEY_F4` | macro | `progs/freedomui/platform_minios.c:46` | `#define FREEDOM_GUI_KEY_F4` |
| `FREEDOM_GUI_MALLOC_ARENAS` | macro | `progs/freedomui/platform_minios.c:35` | `#define FREEDOM_GUI_MALLOC_ARENAS` |
| `FREEDOM_GUI_MOUSE_BUTTONS` | macro | `progs/freedomui/platform_minios.c:41` | `#define FREEDOM_GUI_MOUSE_BUTTONS` |
| `FREEDOM_GUI_MOUSE_WHEEL` | macro | `progs/freedomui/platform_minios.c:42` | `#define FREEDOM_GUI_MOUSE_WHEEL` |
| `FREEDOM_GUI_MOUSE_WORDS` | macro | `progs/freedomui/platform_minios.c:38` | `#define FREEDOM_GUI_MOUSE_WORDS` |
| `FREEDOM_GUI_MOUSE_X` | macro | `progs/freedomui/platform_minios.c:39` | `#define FREEDOM_GUI_MOUSE_X` |
| `FREEDOM_GUI_MOUSE_Y` | macro | `progs/freedomui/platform_minios.c:40` | `#define FREEDOM_GUI_MOUSE_Y` |
| `FREEDOM_GUI_RGB_BPP` | macro | `progs/freedomui/platform_minios.c:48` | `#define FREEDOM_GUI_RGB_BPP` |
| `FREEDOM_GUI_RGB_PRESENT` | macro | `progs/freedomui/platform_minios.c:50` | `#define FREEDOM_GUI_RGB_PRESENT` |
| `FREEDOM_GUI_TICK_MS` | macro | `progs/freedomui/platform_minios.c:27` | `#define FREEDOM_GUI_TICK_MS` |
| `FREEDOM_GUI_TITLE_MAX` | macro | `progs/freedomui/platform_minios.c:31` | `#define FREEDOM_GUI_TITLE_MAX` |
| `_GNU_SOURCE` | macro | `progs/freedomui/platform_minios.c:11` | `#define _GNU_SOURCE` |
| `deliver_pending` | function | `progs/freedomui/platform_minios.c:157` | `static int deliver_pending(pf_display *d)` |
| `key_event` | function | `progs/freedomui/platform_minios.c:167` | `static void key_event(pf_display *d, const ps2_key *k, int kind)` |
| `now_ms` | function | `progs/freedomui/platform_minios.c:94` | `static long now_ms(void)` |
| `pf_clipboard_available` | function | `progs/freedomui/platform_minios.c:276` | `int pf_clipboard_available(const pf_display *d)` |
| `pf_clipboard_get_text` | function | `progs/freedomui/platform_minios.c:287` | `pf_status pf_clipboard_get_text(pf_display *d, char **out, size_t *out_len)` |
| `pf_clipboard_set_text` | function | `progs/freedomui/platform_minios.c:280` | `pf_status pf_clipboard_set_text(pf_display *d, const char *text)` |
| `pf_display` | struct | `progs/freedomui/platform_minios.c:68` | `` |
| `pf_display_close` | function | `progs/freedomui/platform_minios.c:137` | `void pf_display_close(pf_display *d)` |
| `pf_display_flush` | function | `progs/freedomui/platform_minios.c:146` | `void pf_display_flush(pf_display *d)` |
| `pf_display_open` | function | `progs/freedomui/platform_minios.c:121` | `pf_status pf_display_open(pf_display **out)` |
| `pf_display_set_cursor` | function | `progs/freedomui/platform_minios.c:150` | `void pf_display_set_cursor(pf_display *d, pf_cursor c)` |
| `pf_display_wait` | function | `progs/freedomui/platform_minios.c:251` | `int pf_display_wait(pf_display *d, struct pollfd *extra, int n, int timeout_ms)` |
| `pf_window` | struct | `progs/freedomui/platform_minios.c:56` | `` |
| `pf_window_begin_move` | function | `progs/freedomui/platform_minios.c:418` | `void pf_window_begin_move(pf_window *w)` |
| `pf_window_begin_resize` | function | `progs/freedomui/platform_minios.c:422` | `void pf_window_begin_resize(pf_window *w, pf_edge edge)` |
| `pf_window_close` | function | `progs/freedomui/platform_minios.c:325` | `void pf_window_close(pf_window *w)` |
| `pf_window_minimize` | function | `progs/freedomui/platform_minios.c:414` | `void pf_window_minimize(pf_window *w)` |
| `pf_window_open` | function | `progs/freedomui/platform_minios.c:303` | `pf_status pf_window_open(pf_display *d, const pf_window_opts *o,                          const p...` |
| `pf_window_present` | function | `progs/freedomui/platform_minios.c:357` | `void pf_window_present(pf_window *w)` |
| `pf_window_set_fullscreen` | function | `progs/freedomui/platform_minios.c:410` | `void pf_window_set_fullscreen(pf_window *w, int on)` |
| `pf_window_set_maximized` | function | `progs/freedomui/platform_minios.c:406` | `void pf_window_set_maximized(pf_window *w, int on)` |
| `pf_window_set_title` | function | `progs/freedomui/platform_minios.c:391` | `void pf_window_set_title(pf_window *w, const char *title)` |
| `pf_window_surface` | function | `progs/freedomui/platform_minios.c:342` | `cairo_surface_t *pf_window_surface(pf_window *w, int width, int height)` |
| `pump_keyboard` | function | `progs/freedomui/platform_minios.c:194` | `static int pump_keyboard(pf_display *d)` |
| `pump_mouse` | function | `progs/freedomui/platform_minios.c:208` | `static int pump_mouse(pf_display *d)` |
| `set_title` | function | `progs/freedomui/platform_minios.c:98` | `static void set_title(const char *title)` |
| `set_zoom_state` | function | `progs/freedomui/platform_minios.c:397` | `static void set_zoom_state(pf_window *w, unsigned bit, int on)` |
| `sys_fb_info_rgb` | function | `progs/freedomui/platform_minios.c:83` | `static long sys_fb_info_rgb(int *rgb)` |
| `ASCII_BS` | macro | `progs/freedomui/ps2_keymap.c:84` | `#define ASCII_BS` |
| `ASCII_CR` | macro | `progs/freedomui/ps2_keymap.c:86` | `#define ASCII_CR` |
| `ASCII_DEL` | macro | `progs/freedomui/ps2_keymap.c:88` | `#define ASCII_DEL` |
| `ASCII_ESC` | macro | `progs/freedomui/ps2_keymap.c:87` | `#define ASCII_ESC` |
| `ASCII_TAB` | macro | `progs/freedomui/ps2_keymap.c:85` | `#define ASCII_TAB` |
| `KS_F1` | macro | `progs/freedomui/ps2_keymap.c:61` | `#define KS_F1` |
| `KS_F11` | macro | `progs/freedomui/ps2_keymap.c:62` | `#define KS_F11` |
| `KS_INSERT` | macro | `progs/freedomui/ps2_keymap.c:63` | `#define KS_INSERT` |
| `KS_KP_BEGIN` | macro | `progs/freedomui/ps2_keymap.c:78` | `#define KS_KP_BEGIN` |
| `KS_KP_DECIMAL` | macro | `progs/freedomui/ps2_keymap.c:81` | `#define KS_KP_DECIMAL` |
| `KS_KP_DIVIDE` | macro | `progs/freedomui/ps2_keymap.c:82` | `#define KS_KP_DIVIDE` |
| `KS_KP_DOWN` | macro | `progs/freedomui/ps2_keymap.c:74` | `#define KS_KP_DOWN` |
| `KS_KP_END` | macro | `progs/freedomui/ps2_keymap.c:77` | `#define KS_KP_END` |
| `KS_KP_HOME` | macro | `progs/freedomui/ps2_keymap.c:70` | `#define KS_KP_HOME` |
| `KS_KP_INSERT` | macro | `progs/freedomui/ps2_keymap.c:79` | `#define KS_KP_INSERT` |
| `KS_KP_LEFT` | macro | `progs/freedomui/ps2_keymap.c:71` | `#define KS_KP_LEFT` |
| `KS_KP_MULTIPLY` | macro | `progs/freedomui/ps2_keymap.c:80` | `#define KS_KP_MULTIPLY` |
| `KS_KP_NEXT` | macro | `progs/freedomui/ps2_keymap.c:76` | `#define KS_KP_NEXT` |
| `KS_KP_PRIOR` | macro | `progs/freedomui/ps2_keymap.c:75` | `#define KS_KP_PRIOR` |
| `KS_KP_RIGHT` | macro | `progs/freedomui/ps2_keymap.c:73` | `#define KS_KP_RIGHT` |
| `KS_KP_UP` | macro | `progs/freedomui/ps2_keymap.c:72` | `#define KS_KP_UP` |
| `KS_MENU` | macro | `progs/freedomui/ps2_keymap.c:65` | `#define KS_MENU` |
| `KS_NUM_LOCK` | macro | `progs/freedomui/ps2_keymap.c:67` | `#define KS_NUM_LOCK` |
| `KS_PRINT` | macro | `progs/freedomui/ps2_keymap.c:64` | `#define KS_PRINT` |
| `KS_SCROLL_LOCK` | macro | `progs/freedomui/ps2_keymap.c:66` | `#define KS_SCROLL_LOCK` |
| `KS_SUPER_L` | macro | `progs/freedomui/ps2_keymap.c:68` | `#define KS_SUPER_L` |
| `KS_SUPER_R` | macro | `progs/freedomui/ps2_keymap.c:69` | `#define KS_SUPER_R` |
| `PS2_BREAK_BIT` | macro | `progs/freedomui/ps2_keymap.c:16` | `#define PS2_BREAK_BIT` |
| `PS2_CODE_MASK` | macro | `progs/freedomui/ps2_keymap.c:17` | `#define PS2_CODE_MASK` |
| `PS2_HELD_LALT` | macro | `progs/freedomui/ps2_keymap.c:24` | `#define PS2_HELD_LALT` |
| `PS2_HELD_LCTRL` | macro | `progs/freedomui/ps2_keymap.c:22` | `#define PS2_HELD_LCTRL` |
| `PS2_HELD_LSHIFT` | macro | `progs/freedomui/ps2_keymap.c:20` | `#define PS2_HELD_LSHIFT` |
| `PS2_HELD_RALT` | macro | `progs/freedomui/ps2_keymap.c:25` | `#define PS2_HELD_RALT` |
| `PS2_HELD_RCTRL` | macro | `progs/freedomui/ps2_keymap.c:23` | `#define PS2_HELD_RCTRL` |
| `PS2_HELD_RSHIFT` | macro | `progs/freedomui/ps2_keymap.c:21` | `#define PS2_HELD_RSHIFT` |
| `PS2_PAUSE_TAIL` | macro | `progs/freedomui/ps2_keymap.c:15` | `#define PS2_PAUSE_TAIL` |
| `PS2_PREFIX_EXTENDED` | macro | `progs/freedomui/ps2_keymap.c:13` | `#define PS2_PREFIX_EXTENDED` |
| `PS2_PREFIX_PAUSE` | macro | `progs/freedomui/ps2_keymap.c:14` | `#define PS2_PREFIX_PAUSE` |
| `PS2_TABLE_SIZE` | macro | `progs/freedomui/ps2_keymap.c:18` | `#define PS2_TABLE_SIZE` |
| `SC_ALT` | macro | `progs/freedomui/ps2_keymap.c:35` | `#define SC_ALT` |
| `SC_BACKSPACE` | macro | `progs/freedomui/ps2_keymap.c:28` | `#define SC_BACKSPACE` |
| `SC_CAPS` | macro | `progs/freedomui/ps2_keymap.c:36` | `#define SC_CAPS` |
| `SC_CTRL` | macro | `progs/freedomui/ps2_keymap.c:31` | `#define SC_CTRL` |
| `SC_E0_DELETE` | macro | `progs/freedomui/ps2_keymap.c:56` | `#define SC_E0_DELETE` |
| `SC_E0_DOWN` | macro | `progs/freedomui/ps2_keymap.c:53` | `#define SC_E0_DOWN` |
| `SC_E0_END` | macro | `progs/freedomui/ps2_keymap.c:52` | `#define SC_E0_END` |
| `SC_E0_HOME` | macro | `progs/freedomui/ps2_keymap.c:47` | `#define SC_E0_HOME` |
| `SC_E0_INSERT` | macro | `progs/freedomui/ps2_keymap.c:55` | `#define SC_E0_INSERT` |
| `SC_E0_KP_DIV` | macro | `progs/freedomui/ps2_keymap.c:45` | `#define SC_E0_KP_DIV` |
| `SC_E0_LEFT` | macro | `progs/freedomui/ps2_keymap.c:50` | `#define SC_E0_LEFT` |
| `SC_E0_MENU` | macro | `progs/freedomui/ps2_keymap.c:59` | `#define SC_E0_MENU` |
| `SC_E0_NEXT` | macro | `progs/freedomui/ps2_keymap.c:54` | `#define SC_E0_NEXT` |
| `SC_E0_PRINT` | macro | `progs/freedomui/ps2_keymap.c:46` | `#define SC_E0_PRINT` |
| `SC_E0_PRIOR` | macro | `progs/freedomui/ps2_keymap.c:49` | `#define SC_E0_PRIOR` |
| `SC_E0_RIGHT` | macro | `progs/freedomui/ps2_keymap.c:51` | `#define SC_E0_RIGHT` |
| `SC_E0_SUPERL` | macro | `progs/freedomui/ps2_keymap.c:57` | `#define SC_E0_SUPERL` |
| `SC_E0_SUPERR` | macro | `progs/freedomui/ps2_keymap.c:58` | `#define SC_E0_SUPERR` |
| `SC_E0_UP` | macro | `progs/freedomui/ps2_keymap.c:48` | `#define SC_E0_UP` |
| `SC_ESCAPE` | macro | `progs/freedomui/ps2_keymap.c:27` | `#define SC_ESCAPE` |
| `SC_F1` | macro | `progs/freedomui/ps2_keymap.c:37` | `#define SC_F1` |
| `SC_F10` | macro | `progs/freedomui/ps2_keymap.c:38` | `#define SC_F10` |
| `SC_F11` | macro | `progs/freedomui/ps2_keymap.c:43` | `#define SC_F11` |
| `SC_F12` | macro | `progs/freedomui/ps2_keymap.c:44` | `#define SC_F12` |
| `SC_KP_FIRST` | macro | `progs/freedomui/ps2_keymap.c:41` | `#define SC_KP_FIRST` |
| `SC_KP_LAST` | macro | `progs/freedomui/ps2_keymap.c:42` | `#define SC_KP_LAST` |
| `SC_KP_MUL` | macro | `progs/freedomui/ps2_keymap.c:34` | `#define SC_KP_MUL` |
| `SC_LSHIFT` | macro | `progs/freedomui/ps2_keymap.c:32` | `#define SC_LSHIFT` |
| `SC_NUMLOCK` | macro | `progs/freedomui/ps2_keymap.c:39` | `#define SC_NUMLOCK` |
| `SC_RETURN` | macro | `progs/freedomui/ps2_keymap.c:30` | `#define SC_RETURN` |
| `SC_RSHIFT` | macro | `progs/freedomui/ps2_keymap.c:33` | `#define SC_RSHIFT` |
| `SC_SCROLL` | macro | `progs/freedomui/ps2_keymap.c:40` | `#define SC_SCROLL` |
| `SC_TAB` | macro | `progs/freedomui/ps2_keymap.c:29` | `#define SC_TAB` |
| `extended_key` | function | `progs/freedomui/ps2_keymap.c:195` | `static uint32_t extended_key(unsigned code, ps2_key *k)` |
| `held_mods` | function | `progs/freedomui/ps2_keymap.c:150` | `static unsigned held_mods(const ps2_state *s)` |
| `is_letter` | function | `progs/freedomui/ps2_keymap.c:164` | `static int is_letter(char c)` |
| `modifier_key` | function | `progs/freedomui/ps2_keymap.c:169` | `static uint32_t modifier_key(ps2_state *s, unsigned code, int extended, int make)` |
| `num_sym` | type_alias | `progs/freedomui/ps2_keymap.c:122` | `typedef struct ps2_keypad { uint32_t num_sym;` |
| `plain_key` | function | `progs/freedomui/ps2_keymap.c:218` | `static uint32_t plain_key(const ps2_state *s, unsigned code, ps2_key *k)` |
| `ps2_feed` | function | `progs/freedomui/ps2_keymap.c:253` | `int ps2_feed(ps2_state *s, uint8_t byte, ps2_key *out)` |
| `ps2_init` | function | `progs/freedomui/ps2_keymap.c:144` | `void ps2_init(ps2_state *s)` |
| `ps2_keypad` | struct | `progs/freedomui/ps2_keymap.c:122` | `` |
| `set_text` | function | `progs/freedomui/ps2_keymap.c:158` | `static void set_text(ps2_key *k, char c)` |
| `MINIOS_PS2_KEYMAP_H` | macro | `progs/freedomui/ps2_keymap.h:10` | `#define MINIOS_PS2_KEYMAP_H` |
| `PS2_CODE_EXTENDED` | macro | `progs/freedomui/ps2_keymap.h:21` | `#define PS2_CODE_EXTENDED` |
| `PS2_CODE_LIMIT` | macro | `progs/freedomui/ps2_keymap.h:24` | `#define PS2_CODE_LIMIT` |
| `PS2_EV_NONE` | macro | `progs/freedomui/ps2_keymap.h:16` | `#define PS2_EV_NONE` |
| `PS2_EV_PRESS` | macro | `progs/freedomui/ps2_keymap.h:17` | `#define PS2_EV_PRESS` |
| `PS2_EV_RELEASE` | macro | `progs/freedomui/ps2_keymap.h:18` | `#define PS2_EV_RELEASE` |
| `PS2_TEXT_MAX` | macro | `progs/freedomui/ps2_keymap.h:26` | `#define PS2_TEXT_MAX` |
| `arguments` | function | `progs/freedomui/ps2_keymap.h:51` | `* arguments (out is then left untouched). */ int ps2_feed(ps2_state *s, uint8_t byte, ps2_key *out);` |
| `held` | type_alias | `progs/freedomui/ps2_keymap.h:29` | `typedef struct ps2_state { unsigned held;` |
| `ps2_init` | function | `progs/freedomui/ps2_keymap.h:47` | `void ps2_init(ps2_state *s);` |
| `ps2_key` | struct | `progs/freedomui/ps2_keymap.h:38` | `` |
| `ps2_state` | struct | `progs/freedomui/ps2_keymap.h:29` | `` |
| `sym` | type_alias | `progs/freedomui/ps2_keymap.h:38` | `typedef struct ps2_key { uint32_t sym;` |
| `AllocTracker` | type_alias | `progs/lisp/lisp.c:70` | `typedef struct AllocTracker AllocTracker;` |
| `AllocTracker` | struct | `progs/lisp/lisp.c:157` | `` |
| `Binding` | type_alias | `progs/lisp/lisp.c:69` | `typedef struct Binding Binding;` |
| `Binding` | struct | `progs/lisp/lisp.c:140` | `` |
| `Env` | type_alias | `progs/lisp/lisp.c:68` | `typedef struct Env Env;` |
| `Env` | struct | `progs/lisp/lisp.c:149` | `` |
| `LispConfig` | enum | `progs/lisp/lisp.c:41` | `` |
| `Node` | type_alias | `progs/lisp/lisp.c:67` | `typedef struct Node Node;` |
| `Node` | struct | `progs/lisp/lisp.c:113` | `` |
| `ParseResult` | struct | `progs/lisp/lisp.c:104` | `` |
| `PrimEntry` | struct | `progs/lisp/lisp.c:1960` | `` |
| `Reader` | struct | `progs/lisp/lisp.c:181` | `` |
| `Runtime` | type_alias | `progs/lisp/lisp.c:65` | `typedef struct Runtime Runtime;` |
| `Runtime` | struct | `progs/lisp/lisp.c:165` | `` |
| `StringBuilder` | struct | `progs/lisp/lisp.c:192` | `` |
| `arg_at` | function | `progs/lisp/lisp.c:775` | `static Node *arg_at(Runtime *rt, Node *args, size_t index)` |
| `arg_matches` | function | `progs/lisp/lisp.c:815` | `static bool arg_matches(const Node *value, ArgKind kind)` |
| `arity` | function | `progs/lisp/lisp.c:1300` | `* * Variable arity (0 or 1);` |
| `arity0` | function | `progs/lisp/lisp.c:861` | `static bool arity0(Runtime *rt, Node *args)` |
| `bind_argv` | function | `progs/lisp/lisp.c:2017` | `static void bind_argv(Runtime *rt, Env *env, int argc, char **argv, int first)` |
| `bind_primitive` | function | `progs/lisp/lisp.c:1948` | `static void bind_primitive(Runtime *rt, Env *env, const char *name,     PrimFn function)` |
| `check_args` | function | `progs/lisp/lisp.c:841` | `static bool check_args(Runtime *rt, Node *args, const ArgKind *kinds,     size_t n, Node **out)` |
| `cleanup` | function | `progs/lisp/lisp.c:377` | `static void cleanup(Runtime *rt)` |
| `cons` | function | `progs/lisp/lisp.c:338` | `static Node *cons(Runtime *rt, Node *car, Node *cdr)` |
| `env_bind` | function | `progs/lisp/lisp.c:421` | `static void env_bind(Runtime *rt, Env *env, Node *symbol, Node *value)` |
| `env_lookup` | function | `progs/lisp/lisp.c:454` | `static Node *env_lookup(Env *env, Node *symbol)` |
| `env_new` | function | `progs/lisp/lisp.c:411` | `static Env *env_new(Runtime *rt, Env *parent)` |
| `env_set` | function | `progs/lisp/lisp.c:432` | `static bool env_set(Env *env, Node *symbol, Node *value)` |
| `eval` | function | `progs/lisp/lisp.c:1583` | `static Node *eval(Runtime *rt, Node *expression, Env *env)` |
| `eval_list` | function | `progs/lisp/lisp.c:1527` | `static Node *eval_list(Runtime *rt, Node *list, Env *env)` |
| `eval_sequence` | function | `progs/lisp/lisp.c:1551` | `static Node *eval_sequence(Runtime *rt, Node *body, Env *env)` |
| `fatal` | function | `progs/lisp/lisp.c:233` | `static void fatal(Runtime *rt, const char *message)` |
| `file_mode_allowed` | function | `progs/lisp/lisp.c:1123` | `static bool file_mode_allowed(const char *mode)` |
| `has_arity` | function | `progs/lisp/lisp.c:767` | `static bool has_arity(Runtime *rt, Node *args, size_t expected)` |
| `init_env` | function | `progs/lisp/lisp.c:2004` | `static Env *init_env(Runtime *rt)` |
| `is_nil` | function | `progs/lisp/lisp.c:348` | `static bool is_nil(Runtime *rt, const Node *node)` |
| `lisp_version` | function | `progs/lisp/lisp.c:62` | `static const char *lisp_version(void)` |
| `list_count` | function | `progs/lisp/lisp.c:750` | `static size_t list_count(Runtime *rt, Node *list, bool *proper)` |
| `main` | function | `progs/lisp/lisp.c:2190` | `int main(int argc, char **argv)` |
| `make_error` | function | `progs/lisp/lisp.c:293` | `static Node *make_error(Runtime *rt, const char *message)` |
| `make_file` | function | `progs/lisp/lisp.c:355` | `static Node *make_file(Runtime *rt, FILE *handle)` |
| `make_node` | function | `progs/lisp/lisp.c:284` | `static Node *make_node(Runtime *rt, NodeType type)` |
| `make_num` | function | `progs/lisp/lisp.c:302` | `static Node *make_num(Runtime *rt, int64_t value)` |
| `make_prim` | function | `progs/lisp/lisp.c:329` | `static Node *make_prim(Runtime *rt, PrimFn function)` |
| `make_str` | function | `progs/lisp/lisp.c:311` | `static Node *make_str(Runtime *rt, const char *value)` |
| `make_sym` | function | `progs/lisp/lisp.c:320` | `static Node *make_sym(Runtime *rt, const char *value)` |
| `msys` | function | `progs/lisp/lisp.c:205` | `static long msys(long n, long a1, long a2, long a3)` |
| `msys5` | function | `progs/lisp/lisp.c:218` | `static long msys5(long n, long a1, long a2, long a3, long a4, long a5)` |
| `numbers` | function | `progs/lisp/lisp.c:9` | `* * Language surface: numbers (int64), strings, symbols, cons cells, closures * with lexical scope, and the special...` |
| `parse_eof` | function | `progs/lisp/lisp.c:573` | `static ParseResult parse_eof(void)` |
| `parse_error` | function | `progs/lisp/lisp.c:584` | `static ParseResult parse_error(const char *message)` |
| `parse_ok` | function | `progs/lisp/lisp.c:562` | `static ParseResult parse_ok(Node *value)` |
| `prim_add` | function | `progs/lisp/lisp.c:869` | `static Node *prim_add(Runtime *rt, Node *args)` |
| `prim_car` | function | `progs/lisp/lisp.c:963` | `static Node *prim_car(Runtime *rt, Node *args)` |
| `prim_cdr` | function | `progs/lisp/lisp.c:975` | `static Node *prim_cdr(Runtime *rt, Node *args)` |
| `prim_char_code` | function | `progs/lisp/lisp.c:1072` | `static Node *prim_char_code(Runtime *rt, Node *args)` |
| `prim_close_file` | function | `progs/lisp/lisp.c:1224` | `static Node *prim_close_file(Runtime *rt, Node *args)` |
| `prim_cons` | function | `progs/lisp/lisp.c:987` | `static Node *prim_cons(Runtime *rt, Node *args)` |
| `prim_div` | function | `progs/lisp/lisp.c:917` | `static Node *prim_div(Runtime *rt, Node *args)` |
| `prim_eq` | function | `progs/lisp/lisp.c:939` | `static Node *prim_eq(Runtime *rt, Node *args)` |
| `prim_error_message` | function | `progs/lisp/lisp.c:1285` | `static Node *prim_error_message(Runtime *rt, Node *args)` |
| `prim_exit` | function | `progs/lisp/lisp.c:1303` | `static Node *prim_exit(Runtime *rt, Node *args)` |
| `prim_fb_info` | function | `progs/lisp/lisp.c:1357` | `static Node *prim_fb_info(Runtime *rt, Node *args)` |
| `prim_lt` | function | `progs/lisp/lisp.c:951` | `static Node *prim_lt(Runtime *rt, Node *args)` |
| `prim_minios_run` | function | `progs/lisp/lisp.c:1465` | `static Node *prim_minios_run(Runtime *rt, Node *args)` |
| `prim_mul` | function | `progs/lisp/lisp.c:901` | `static Node *prim_mul(Runtime *rt, Node *args)` |
| `prim_null_p` | function | `progs/lisp/lisp.c:1249` | `static Node *prim_null_p(Runtime *rt, Node *args)` |
| `prim_number_p` | function | `progs/lisp/lisp.c:1261` | `static Node *prim_number_p(Runtime *rt, Node *args)` |
| `prim_pal` | function | `progs/lisp/lisp.c:1405` | `static Node *prim_pal(Runtime *rt, Node *args)` |
| `prim_pcspeaker` | function | `progs/lisp/lisp.c:1421` | `static Node *prim_pcspeaker(Runtime *rt, Node *args)` |
| `prim_print` | function | `progs/lisp/lisp.c:1094` | `static Node *prim_print(Runtime *rt, Node *args)` |
| `prim_println` | function | `progs/lisp/lisp.c:1108` | `static Node *prim_println(Runtime *rt, Node *args)` |
| `prim_read_char` | function | `progs/lisp/lisp.c:1183` | `static Node *prim_read_char(Runtime *rt, Node *args)` |
| `prim_rtc` | function | `progs/lisp/lisp.c:1340` | `static Node *prim_rtc(Runtime *rt, Node *args)` |
| `prim_string_at` | function | `progs/lisp/lisp.c:1050` | `static Node *prim_string_at(Runtime *rt, Node *args)` |
| `prim_string_concat` | function | `progs/lisp/lisp.c:999` | `static Node *prim_string_concat(Runtime *rt, Node *args)` |
| `prim_string_eq` | function | `progs/lisp/lisp.c:1026` | `static Node *prim_string_eq(Runtime *rt, Node *args)` |
| `prim_string_length` | function | `progs/lisp/lisp.c:1038` | `static Node *prim_string_length(Runtime *rt, Node *args)` |
| `prim_string_p` | function | `progs/lisp/lisp.c:1273` | `static Node *prim_string_p(Runtime *rt, Node *args)` |
| `prim_sub` | function | `progs/lisp/lisp.c:885` | `static Node *prim_sub(Runtime *rt, Node *args)` |
| `prim_time_ms` | function | `progs/lisp/lisp.c:1330` | `static Node *prim_time_ms(Runtime *rt, Node *args)` |
| `prim_vol` | function | `progs/lisp/lisp.c:1377` | `static Node *prim_vol(Runtime *rt, Node *args)` |
| `prim_write` | function | `progs/lisp/lisp.c:1200` | `static Node *prim_write(Runtime *rt, Node *args)` |
| `print_escaped_string` | function | `progs/lisp/lisp.c:1846` | `static void print_escaped_string(FILE *out, const char *value)` |
| `print_node` | function | `progs/lisp/lisp.c:1877` | `static void print_node(Runtime *rt, Node *node, bool readable)` |
| `print_usage` | function | `progs/lisp/lisp.c:2136` | `static void print_usage(Runtime *rt)` |
| `process_inline` | function | `progs/lisp/lisp.c:2129` | `static int process_inline(Runtime *rt, const char *code)` |
| `process_source` | function | `progs/lisp/lisp.c:2087` | `static int process_source(Runtime *rt, const char *source,     const char *source_name, bool echo)` |
| `read_all_file` | function | `progs/lisp/lisp.c:2029` | `static char *read_all_file(const char *filename, size_t max_bytes)` |
| `read_atom` | function | `progs/lisp/lisp.c:685` | `static ParseResult read_atom(Runtime *rt, Reader *reader)` |
| `read_expr` | function | `progs/lisp/lisp.c:721` | `static ParseResult read_expr(Runtime *rt, Reader *reader)` |
| `read_list` | function | `progs/lisp/lisp.c:596` | `static ParseResult read_list(Runtime *rt, Reader *reader)` |
| `read_string` | function | `progs/lisp/lisp.c:626` | `static ParseResult read_string(Runtime *rt, Reader *reader)` |
| `reader_at_end` | function | `progs/lisp/lisp.c:500` | `static bool reader_at_end(const Reader *reader)` |
| `reader_next` | function | `progs/lisp/lisp.c:482` | `static char reader_next(Reader *reader)` |
| `reader_peek` | function | `progs/lisp/lisp.c:475` | `static char reader_peek(const Reader *reader)` |
| `repl` | function | `progs/lisp/lisp.c:2143` | `static int repl(Runtime *rt)` |
| `runtime_init` | function | `progs/lisp/lisp.c:399` | `static void runtime_init(Runtime *rt)` |
| `sb_init` | function | `progs/lisp/lisp.c:523` | `static void sb_init(StringBuilder *builder)` |
| `sb_push` | function | `progs/lisp/lisp.c:536` | `static void sb_push(StringBuilder *builder, char value)` |
| `skip_space_and_comments` | function | `progs/lisp/lisp.c:507` | `static void skip_space_and_comments(Reader *reader)` |
| `token_delimiter` | function | `progs/lisp/lisp.c:677` | `static bool token_delimiter(char c)` |
| `valid_params` | function | `progs/lisp/lisp.c:1569` | `static bool valid_params(Runtime *rt, Node *params)` |
| `xalloc` | function | `progs/lisp/lisp.c:242` | `static void *xalloc(Runtime *rt, size_t size)` |
| `xstrdup` | function | `progs/lisp/lisp.c:266` | `static char *xstrdup(Runtime *rt, const char *source)` |
| `main` | function | `progs/lisp/tin.c:1` | `int main()` |
| `docode` | function | `progs/lua/lua_main.c:41` | `static int docode(lua_State *L, const char *code)` |
| `dofile` | function | `progs/lua/lua_main.c:51` | `static int dofile(lua_State *L, const char *name)` |
| `luaL_require_global` | function | `progs/lua/lua_main.c:22` | `static void luaL_require_global(lua_State *L, const char *name,                                 l...` |
| `main` | function | `progs/lua/lua_main.c:105` | `int main(int argc, char **argv)` |
| `module` | function | `progs/lua/lua_main.c:5` | `* C module (minios.c) can be registered globally before any script runs: * `minios.run(...)`, `minios.time_ms()`...` |
| `repl` | function | `progs/lua/lua_main.c:61` | `static int repl(lua_State *L)` |
| `set_arg_table` | function | `progs/lua/lua_main.c:28` | `static void set_arg_table(lua_State *L, int argc, char **argv, int first)` |
| `SYS_FB_INFO` | macro | `progs/lua/minios.c:57` | `#define SYS_FB_INFO` |
| `SYS_PALETTE` | macro | `progs/lua/minios.c:53` | `#define SYS_PALETTE` |
| `SYS_PCSPK_INIT` | macro | `progs/lua/minios.c:54` | `#define SYS_PCSPK_INIT` |
| `SYS_PCSPK_TONE` | macro | `progs/lua/minios.c:55` | `#define SYS_PCSPK_TONE` |
| `SYS_PCSPK_VOL` | macro | `progs/lua/minios.c:58` | `#define SYS_PCSPK_VOL` |
| `SYS_RTC` | macro | `progs/lua/minios.c:56` | `#define SYS_RTC` |
| `SYS_SPAWN` | macro | `progs/lua/minios.c:59` | `#define SYS_SPAWN` |
| `SYS_TIME_MS` | macro | `progs/lua/minios.c:52` | `#define SYS_TIME_MS` |
| `luaopen_minios` | function | `progs/lua/minios.c:192` | `int luaopen_minios(lua_State *L)` |
| `minios_fb_info` | function | `progs/lua/minios.c:82` | `static int minios_fb_info(lua_State *L)` |
| `minios_pal` | function | `progs/lua/minios.c:109` | `static int minios_pal(lua_State *L)` |
| `minios_pcspeaker` | function | `progs/lua/minios.c:119` | `static int minios_pcspeaker(lua_State *L)` |
| `minios_rtc` | function | `progs/lua/minios.c:68` | `static int minios_rtc(lua_State *L)` |
| `minios_run` | function | `progs/lua/minios.c:136` | `static int minios_run(lua_State *L)` |
| `minios_time_ms` | function | `progs/lua/minios.c:62` | `static int minios_time_ms(lua_State *L)` |
| `minios_vol` | function | `progs/lua/minios.c:96` | `static int minios_vol(lua_State *L)` |
| `msys5` | function | `progs/lua/minios.c:37` | `static long msys5(long n, long a1, long a2, long a3, long a4, long a5)` |
| `MP_DEFINE_CONST_DICT` | function | `progs/micropython/variants/minios/minios_module.c:207` | `static MP_DEFINE_CONST_DICT(minios_module_globals, minios_module_globals_table);` |
| `MP_DEFINE_CONST_FUN_OBJ_0` | function | `progs/micropython/variants/minios/minios_module.c:55` | `static MP_DEFINE_CONST_FUN_OBJ_0(minios_time_ms_obj, minios_time_ms);` |
| `MP_DEFINE_CONST_FUN_OBJ_1` | function | `progs/micropython/variants/minios/minios_module.c:123` | `static MP_DEFINE_CONST_FUN_OBJ_1(minios_pal_obj, minios_pal);` |
| `MP_DEFINE_CONST_FUN_OBJ_2` | function | `progs/micropython/variants/minios/minios_module.c:140` | `static MP_DEFINE_CONST_FUN_OBJ_2(minios_pcspeaker_obj, minios_pcspeaker);` |
| `MP_DEFINE_CONST_FUN_OBJ_KW` | function | `progs/micropython/variants/minios/minios_module.c:193` | `static MP_DEFINE_CONST_FUN_OBJ_KW(minios_run_obj, 1, minios_run);` |
| `MP_DEFINE_CONST_FUN_OBJ_VAR` | function | `progs/micropython/variants/minios/minios_module.c:107` | `static MP_DEFINE_CONST_FUN_OBJ_VAR(minios_vol_obj, 0, minios_vol);` |
| `SYS_FB_INFO` | macro | `progs/micropython/variants/minios/minios_module.c:46` | `#define SYS_FB_INFO` |
| `SYS_PALETTE` | macro | `progs/micropython/variants/minios/minios_module.c:42` | `#define SYS_PALETTE` |
| `SYS_PCSPK_INIT` | macro | `progs/micropython/variants/minios/minios_module.c:43` | `#define SYS_PCSPK_INIT` |
| `SYS_PCSPK_TONE` | macro | `progs/micropython/variants/minios/minios_module.c:44` | `#define SYS_PCSPK_TONE` |
| `SYS_PCSPK_VOL` | macro | `progs/micropython/variants/minios/minios_module.c:47` | `#define SYS_PCSPK_VOL` |
| `SYS_RTC` | macro | `progs/micropython/variants/minios/minios_module.c:45` | `#define SYS_RTC` |
| `SYS_SPAWN` | macro | `progs/micropython/variants/minios/minios_module.c:48` | `#define SYS_SPAWN` |
| `SYS_TIME_MS` | macro | `progs/micropython/variants/minios/minios_module.c:41` | `#define SYS_TIME_MS` |
| `minios_fb_info` | function | `progs/micropython/variants/minios/minios_module.c:76` | `static mp_obj_t minios_fb_info(void)` |
| `minios_pal` | function | `progs/micropython/variants/minios/minios_module.c:111` | `static mp_obj_t minios_pal(mp_obj_t buf_in)` |
| `minios_pcspeaker` | function | `progs/micropython/variants/minios/minios_module.c:127` | `static mp_obj_t minios_pcspeaker(mp_obj_t freq_in, mp_obj_t ms_in)` |
| `minios_rtc` | function | `progs/micropython/variants/minios/minios_module.c:59` | `static mp_obj_t minios_rtc(void)` |
| `minios_run` | function | `progs/micropython/variants/minios/minios_module.c:149` | `static mp_obj_t minios_run(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)` |
| `minios_time_ms` | function | `progs/micropython/variants/minios/minios_module.c:52` | `static mp_obj_t minios_time_ms(void)` |
| `msys5` | function | `progs/micropython/variants/minios/minios_module.c:26` | `static long msys5(long n, long a1, long a2, long a3, long a4, long a5)` |
| `MICROPY_ASYNC_KBD_INTR` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:31` | `#define MICROPY_ASYNC_KBD_INTR` |
| `MICROPY_CONFIG_ROM_LEVEL` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:11` | `#define MICROPY_CONFIG_ROM_LEVEL` |
| `MICROPY_DEBUG_PRINTERS` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:20` | `#define MICROPY_DEBUG_PRINTERS` |
| `MICROPY_EMERGENCY_EXCEPTION_BUF_SIZE` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:75` | `#define MICROPY_EMERGENCY_EXCEPTION_BUF_SIZE` |
| `MICROPY_ENABLE_EMERGENCY_EXCEPTION_BUF` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:74` | `#define MICROPY_ENABLE_EMERGENCY_EXCEPTION_BUF` |
| `MICROPY_ERROR_REPORTING` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:18` | `#define MICROPY_ERROR_REPORTING` |
| `MICROPY_FLOAT_IMPL` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:14` | `#define MICROPY_FLOAT_IMPL` |
| `MICROPY_HELPER_REPL` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:34` | `#define MICROPY_HELPER_REPL` |
| `MICROPY_KBD_EXCEPTION` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:30` | `#define MICROPY_KBD_EXCEPTION` |
| `MICROPY_LONGINT_IMPL` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:15` | `#define MICROPY_LONGINT_IMPL` |
| `MICROPY_OPT_COMPUTED_GOTO` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:71` | `#define MICROPY_OPT_COMPUTED_GOTO` |
| `MICROPY_PERSISTENT_CODE_LOAD` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:61` | `#define MICROPY_PERSISTENT_CODE_LOAD` |
| `MICROPY_PY_FFI` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:55` | `#define MICROPY_PY_FFI` |
| `MICROPY_PY_GC_COLLECT_RETVAL` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:78` | `#define MICROPY_PY_GC_COLLECT_RETVAL` |
| `MICROPY_PY_MACHINE` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:57` | `#define MICROPY_PY_MACHINE` |
| `MICROPY_PY_OS` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:42` | `#define MICROPY_PY_OS` |
| `MICROPY_PY_OS_ERRNO` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:44` | `#define MICROPY_PY_OS_ERRNO` |
| `MICROPY_PY_OS_GETENV_PUTENV_UNSETENV` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:45` | `#define MICROPY_PY_OS_GETENV_PUTENV_UNSETENV` |
| `MICROPY_PY_OS_INCLUDEFILE` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:43` | `#define MICROPY_PY_OS_INCLUDEFILE` |
| `MICROPY_PY_OS_SYSTEM` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:46` | `#define MICROPY_PY_OS_SYSTEM` |
| `MICROPY_PY_OS_URANDOM` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:47` | `#define MICROPY_PY_OS_URANDOM` |
| `MICROPY_PY_SOCKET` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:53` | `#define MICROPY_PY_SOCKET` |
| `MICROPY_PY_SSL` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:54` | `#define MICROPY_PY_SSL` |
| `MICROPY_PY_SYS_ATEXIT` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:37` | `#define MICROPY_PY_SYS_ATEXIT` |
| `MICROPY_PY_SYS_EXC_INFO` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:38` | `#define MICROPY_PY_SYS_EXC_INFO` |
| `MICROPY_PY_SYS_PS1` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:35` | `#define MICROPY_PY_SYS_PS1` |
| `MICROPY_PY_SYS_PS2` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:36` | `#define MICROPY_PY_SYS_PS2` |
| `MICROPY_PY_SYS_STDFILES` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:39` | `#define MICROPY_PY_SYS_STDFILES` |
| `MICROPY_PY_THREAD` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:56` | `#define MICROPY_PY_THREAD` |
| `MICROPY_PY_TIME` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:50` | `#define MICROPY_PY_TIME` |
| `MICROPY_PY_WEBSOCKET` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:58` | `#define MICROPY_PY_WEBSOCKET` |
| `MICROPY_REPL_EMACS_EXTRA_WORDS_MOVE` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:65` | `#define MICROPY_REPL_EMACS_EXTRA_WORDS_MOVE` |
| `MICROPY_REPL_EMACS_WORDS_MOVE` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:64` | `#define MICROPY_REPL_EMACS_WORDS_MOVE` |
| `MICROPY_USE_READLINE` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:23` | `#define MICROPY_USE_READLINE` |
| `MICROPY_USE_READLINE_HISTORY` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:66` | `#define MICROPY_USE_READLINE_HISTORY` |
| `MICROPY_VFS_ROM` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:81` | `#define MICROPY_VFS_ROM` |
| `MICROPY_VFS_ROM_IOCTL` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:82` | `#define MICROPY_VFS_ROM_IOCTL` |
| `MICROPY_WARNINGS` | macro | `progs/micropython/variants/minios/mpconfigvariant.h:19` | `#define MICROPY_WARNINGS` |
| `BACKBUF` | macro | `progs/minicraft/minicraft.c:45` | `#define BACKBUF` |
| `BACKBUF` | macro | `progs/minicraft/minicraft.c:47` | `#define BACKBUF` |
| `ChunkHeader` | struct | `progs/minicraft/minicraft.c:2907` | `` |
| `EXT_DOWN` | macro | `progs/minicraft/minicraft.c:151` | `#define EXT_DOWN` |
| `EXT_F11` | macro | `progs/minicraft/minicraft.c:154` | `#define EXT_F11` |
| `EXT_LEFT` | macro | `progs/minicraft/minicraft.c:152` | `#define EXT_LEFT` |
| `EXT_RIGHT` | macro | `progs/minicraft/minicraft.c:153` | `#define EXT_RIGHT` |
| `EXT_UP` | macro | `progs/minicraft/minicraft.c:150` | `#define EXT_UP` |
| `FB_H` | macro | `progs/minicraft/minicraft.c:42` | `#define FB_H` |
| `FB_W` | macro | `progs/minicraft/minicraft.c:41` | `#define FB_W` |
| `MC_AUTOSTEP` | macro | `progs/minicraft/minicraft.c:78` | `#define MC_AUTOSTEP` |
| `MC_BAYER_N` | macro | `progs/minicraft/minicraft.c:110` | `#define MC_BAYER_N` |
| `MC_BOOM_R` | macro | `progs/minicraft/minicraft.c:85` | `#define MC_BOOM_R` |
| `MC_BREAK_GRACE_MS` | macro | `progs/minicraft/minicraft.c:71` | `#define MC_BREAK_GRACE_MS` |
| `MC_BREAK_MS` | macro | `progs/minicraft/minicraft.c:70` | `#define MC_BREAK_MS` |
| `MC_CHUNK` | macro | `progs/minicraft/minicraft.c:35` | `#define MC_CHUNK` |
| `MC_CHUNKS` | macro | `progs/minicraft/minicraft.c:37` | `#define MC_CHUNKS` |
| `MC_CHUNK_MAGIC` | macro | `progs/minicraft/minicraft.c:55` | `#define MC_CHUNK_MAGIC` |
| `MC_CHUNK_VERSION` | macro | `progs/minicraft/minicraft.c:56` | `#define MC_CHUNK_VERSION` |
| `MC_COLS` | macro | `progs/minicraft/minicraft.c:39` | `#define MC_COLS` |
| `MC_CREEPS_DEF` | macro | `progs/minicraft/minicraft.c:82` | `#define MC_CREEPS_DEF` |
| `MC_CREEPS_MAX` | macro | `progs/minicraft/minicraft.c:81` | `#define MC_CREEPS_MAX` |
| `MC_CREEP_DEFUSE_D` | macro | `progs/minicraft/minicraft.c:91` | `#define MC_CREEP_DEFUSE_D` |
| `MC_CREEP_DZ_MAX` | macro | `progs/minicraft/minicraft.c:89` | `#define MC_CREEP_DZ_MAX` |
| `MC_CREEP_FUSE_D` | macro | `progs/minicraft/minicraft.c:90` | `#define MC_CREEP_FUSE_D` |
| `MC_CREEP_HP` | macro | `progs/minicraft/minicraft.c:83` | `#define MC_CREEP_HP` |
| `MC_CREEP_NIGHT_MS` | macro | `progs/minicraft/minicraft.c:99` | `#define MC_CREEP_NIGHT_MS` |
| `MC_CREEP_SENSE` | macro | `progs/minicraft/minicraft.c:88` | `#define MC_CREEP_SENSE` |
| `MC_CREEP_SEP_D` | macro | `progs/minicraft/minicraft.c:102` | `#define MC_CREEP_SEP_D` |
| `MC_CVOL` | macro | `progs/minicraft/minicraft.c:38` | `#define MC_CVOL` |
| `MC_DAY_MS` | macro | `progs/minicraft/minicraft.c:108` | `#define MC_DAY_MS` |
| `MC_DDA_STEPS` | macro | `progs/minicraft/minicraft.c:69` | `#define MC_DDA_STEPS` |
| `MC_EYE` | macro | `progs/minicraft/minicraft.c:59` | `#define MC_EYE` |
| `MC_FLY_SPEED` | macro | `progs/minicraft/minicraft.c:64` | `#define MC_FLY_SPEED` |
| `MC_FUSE_MS` | macro | `progs/minicraft/minicraft.c:84` | `#define MC_FUSE_MS` |
| `MC_GRAV` | macro | `progs/minicraft/minicraft.c:60` | `#define MC_GRAV` |
| `MC_H` | macro | `progs/minicraft/minicraft.c:34` | `#define MC_H` |
| `MC_HP_MAX` | macro | `progs/minicraft/minicraft.c:79` | `#define MC_HP_MAX` |
| `MC_HUNGER_MAX` | macro | `progs/minicraft/minicraft.c:104` | `#define MC_HUNGER_MAX` |
| `MC_HUNGER_MS` | macro | `progs/minicraft/minicraft.c:105` | `#define MC_HUNGER_MS` |
| `MC_H_BASE` | macro | `progs/minicraft/minicraft.c:111` | `#define MC_H_BASE` |
| `MC_H_WT_COARSE` | macro | `progs/minicraft/minicraft.c:114` | `#define MC_H_WT_COARSE` |
| `MC_H_WT_DET` | macro | `progs/minicraft/minicraft.c:112` | `#define MC_H_WT_DET` |
| `MC_H_WT_MID` | macro | `progs/minicraft/minicraft.c:113` | `#define MC_H_WT_MID` |
| `MC_INV_MAX` | macro | `progs/minicraft/minicraft.c:76` | `#define MC_INV_MAX` |
| `MC_JUMP` | macro | `progs/minicraft/minicraft.c:61` | `#define MC_JUMP` |
| `MC_KBD_SEQ_SPINS` | macro | `progs/minicraft/minicraft.c:145` | `#define MC_KBD_SEQ_SPINS` |
| `MC_LEGACY_WORLD` | macro | `progs/minicraft/minicraft.c:2916` | `#define MC_LEGACY_WORLD` |
| `MC_LOAD_R` | macro | `progs/minicraft/minicraft.c:36` | `#define MC_LOAD_R` |
| `MC_MAXFALL` | macro | `progs/minicraft/minicraft.c:62` | `#define MC_MAXFALL` |
| `MC_MOUSE` | macro | `progs/minicraft/minicraft.c:66` | `#define MC_MOUSE` |
| `MC_NIGHT_LIGHT` | macro | `progs/minicraft/minicraft.c:101` | `#define MC_NIGHT_LIGHT` |
| `MC_PIGS` | macro | `progs/minicraft/minicraft.c:80` | `#define MC_PIGS` |
| `MC_PIG_DAY_MS` | macro | `progs/minicraft/minicraft.c:100` | `#define MC_PIG_DAY_MS` |
| `MC_PIG_HP` | macro | `progs/minicraft/minicraft.c:106` | `#define MC_PIG_HP` |
| `MC_PIG_HURT_MS` | macro | `progs/minicraft/minicraft.c:107` | `#define MC_PIG_HURT_MS` |
| `MC_PITCH_MAX` | macro | `progs/minicraft/minicraft.c:77` | `#define MC_PITCH_MAX` |
| `MC_PLACE_MS` | macro | `progs/minicraft/minicraft.c:72` | `#define MC_PLACE_MS` |
| `MC_PORK_HEAL` | macro | `progs/minicraft/minicraft.c:103` | `#define MC_PORK_HEAL` |
| `MC_REACH` | macro | `progs/minicraft/minicraft.c:67` | `#define MC_REACH` |
| `MC_RESPAWN_MS` | macro | `progs/minicraft/minicraft.c:98` | `#define MC_RESPAWN_MS` |
| `MC_SAVE_CRC_SEED` | macro | `progs/minicraft/minicraft.c:54` | `#define MC_SAVE_CRC_SEED` |
| `MC_SAVE_MAGIC` | macro | `progs/minicraft/minicraft.c:52` | `#define MC_SAVE_MAGIC` |
| `MC_SAVE_SECS` | macro | `progs/minicraft/minicraft.c:109` | `#define MC_SAVE_SECS` |
| `MC_SAVE_VERSION` | macro | `progs/minicraft/minicraft.c:53` | `#define MC_SAVE_VERSION` |
| `MC_SEED_MAX` | macro | `progs/minicraft/minicraft.c:144` | `#define MC_SEED_MAX` |
| `MC_SPEED` | macro | `progs/minicraft/minicraft.c:63` | `#define MC_SPEED` |
| `MC_SPRINT` | macro | `progs/minicraft/minicraft.c:65` | `#define MC_SPRINT` |
| `MC_VIEW` | macro | `progs/minicraft/minicraft.c:68` | `#define MC_VIEW` |
| `MC_VORO_DESERT_CELL` | macro | `progs/minicraft/minicraft.c:858` | `#define MC_VORO_DESERT_CELL` |
| `MC_VORO_SNOW_CELL` | macro | `progs/minicraft/minicraft.c:859` | `#define MC_VORO_SNOW_CELL` |
| `MC_WATER_GRAV` | macro | `progs/minicraft/minicraft.c:73` | `#define MC_WATER_GRAV` |
| `MC_WATER_SINK` | macro | `progs/minicraft/minicraft.c:74` | `#define MC_WATER_SINK` |
| `MC_WATER_SWIM` | macro | `progs/minicraft/minicraft.c:75` | `#define MC_WATER_SWIM` |
| `MOB_CREEP` | macro | `progs/minicraft/minicraft.c:309` | `#define MOB_CREEP` |
| `MOB_PIG` | macro | `progs/minicraft/minicraft.c:308` | `#define MOB_PIG` |
| `Pig` | struct | `progs/minicraft/minicraft.c:295` | `` |
| `RayHit` | struct | `progs/minicraft/minicraft.c:1650` | `` |
| `Recipe` | struct | `progs/minicraft/minicraft.c:216` | `` |
| `SAVE_PATH` | macro | `progs/minicraft/minicraft.c:50` | `#define SAVE_PATH` |
| `SAVE_TMP_PATH` | macro | `progs/minicraft/minicraft.c:51` | `#define SAVE_TMP_PATH` |
| `SC_0` | macro | `progs/minicraft/minicraft.c:143` | `#define SC_0` |
| `SC_1` | macro | `progs/minicraft/minicraft.c:118` | `#define SC_1` |
| `SC_9` | macro | `progs/minicraft/minicraft.c:119` | `#define SC_9` |

Next: [SYMBOLS_p20.md](SYMBOLS_p20.md)
