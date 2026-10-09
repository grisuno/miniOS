# API (page 16 of 19)
Previous: [API_p15.md](API_p15.md)

## progs/nuklear/nuklear_minios.c
Depends on: `kernel/string.c`, `progs/nk_palette.h`, `progs/nuklear/nuklear_minios.h`, `progs/wl/wl_client.h`, `progs/wl/wl_mbox.h`
- `list` (function) `progs/nuklear/nuklear_minios.c:4` `* abstract draw command list (nk__begin/nk__next);`
- `nk_sys_time_ms` (function) `progs/nuklear/nuklear_minios.c:33` `long nk_sys_time_ms(void)` -- #include <string.h> #include <stdio.h> #include <math.h> #include "nuklear_minios.h" /* glibc program name for the...
- `nk_sys_kbd` (function) `progs/nuklear/nuklear_minios.c:38` `long nk_sys_kbd(void)`
- `nk_sys_palette` (function) `progs/nuklear/nuklear_minios.c:43` `long nk_sys_palette(const unsigned char *pal)`
- `nk_sys_kbd_raw` (function) `progs/nuklear/nuklear_minios.c:48` `long nk_sys_kbd_raw(int on)`
- `nk_sys_getpid` (function) `progs/nuklear/nuklear_minios.c:53` `long nk_sys_getpid(void)`
- `nk_client_probe` (function) `progs/nuklear/nuklear_minios.c:72` `static int nk_client_probe(void)`
- `nk_sys_vga_mode` (function) `progs/nuklear/nuklear_minios.c:114` `long nk_sys_vga_mode(int on)`
- `nk_sys_fb_info` (function) `progs/nuklear/nuklear_minios.c:121` `long nk_sys_fb_info(int *w, int *h, int *pitch)`
- `nk_sys_fb_info_rgb` (function) `progs/nuklear/nuklear_minios.c:137` `static long nk_sys_fb_info_rgb(int *w, int *h, int *pitch, int *rgb)`
- `nk_rgb_available` (function) `progs/nuklear/nuklear_minios.c:147` `int nk_rgb_available(void)`
- `rgb256_prepare` (function) `progs/nuklear/nuklear_minios.c:162` `static void rgb256_prepare(void)`
- `nk_idx_to_rgb` (function) `progs/nuklear/nuklear_minios.c:170` `void nk_idx_to_rgb(int idx, unsigned char *r, unsigned char *g,
                   unsigned char *b)`
- `cur_set` (function) `progs/nuklear/nuklear_minios.c:186` `static void cur_set(struct nk_color c)`
- `cur_bg_set` (function) `progs/nuklear/nuklear_minios.c:190` `static void cur_bg_set(struct nk_color c)`
- `nk_sys_mouse` (function) `progs/nuklear/nuklear_minios.c:193` `long nk_sys_mouse(int *xybw)`
- `nk_sys_mouse_badptr` (function) `progs/nuklear/nuklear_minios.c:198` `long nk_sys_mouse_badptr(void)`
- `nk_client_hash` (function) `progs/nuklear/nuklear_minios.c:216` `static unsigned nk_client_hash(const unsigned char *p, unsigned n)`
- `nk_client_publish` (function) `progs/nuklear/nuklear_minios.c:227` `static int nk_client_publish(void)`
- `nk_sys_nk_frame` (function) `progs/nuklear/nuklear_minios.c:280` `long nk_sys_nk_frame(int *origin)`
- `nk_mirror_box` (function) `progs/nuklear/nuklear_minios.c:314` `static void nk_mirror_box(char *dst, int cap)`
- `nk_mirror_emit` (function) `progs/nuklear/nuklear_minios.c:335` `static int nk_mirror_emit(const char *box, unsigned seq,
        const unsigned char *msg, int mlen)`
- `nk_mirror_tick` (function) `progs/nuklear/nuklear_minios.c:352` `static void nk_mirror_tick(void)`
- `nk_sys_gfx_set_title` (function) `progs/nuklear/nuklear_minios.c:409` `long nk_sys_gfx_set_title(const char *t)`
- `nk_build_palette` (function) `progs/nuklear/nuklear_minios.c:418` `void nk_build_palette(unsigned char *pal768)` -- The desktop-exact hybrid palette lives once in progs/nk_palette.h; * this wrapper keeps the platform signature while...
- `pal_prepare` (function) `progs/nuklear/nuklear_minios.c:427` `static void pal_prepare(void)`
- `col_to_idx` (function) `progs/nuklear/nuklear_minios.c:438` `static int col_to_idx(struct nk_color c)`
- `set_clip` (function) `progs/nuklear/nuklear_minios.c:469` `static void set_clip(int x, int y, int w, int h)`
- `px` (function) `progs/nuklear/nuklear_minios.c:479` `static void px(int x, int y, int c)`
- `px_bg` (function) `progs/nuklear/nuklear_minios.c:492` `static void px_bg(int x, int y, int c)` -- static void px(int x, int y, int c) { volatile uint8_t *d; if (x < clip_x || x >= clip_x + clip_w) return; if (y <...
- `px_idx` (function) `progs/nuklear/nuklear_minios.c:506` `static void px_idx(int x, int y, int c)` -- Index-owned pixels (IMAGE commands): RGB resolves through the exact * rgb256 table, so both buffers agree without a...
- `fill_rect` (function) `progs/nuklear/nuklear_minios.c:522` `static void fill_rect(int x, int y, int w, int h, int c)`
- `draw_line` (function) `progs/nuklear/nuklear_minios.c:529` `static void draw_line(int x0, int y0, int x1, int y1, int th, int c)`
- `fill_circle` (function) `progs/nuklear/nuklear_minios.c:547` `static void fill_circle(int cx, int cy, int r, int c)`
- `stroke_circle` (function) `progs/nuklear/nuklear_minios.c:553` `static void stroke_circle(int cx, int cy, int r, int th, int c)`
- `fill_poly` (function) `progs/nuklear/nuklear_minios.c:571` `static void fill_poly(int *xs, int *ys, int n, int c)` -- draw_line(cx + x, cy - y, cx - x, cy - y, th, c); draw_line(cx - x, cy + y, cx - x, cy - y, th, c); draw_line(cx +...
- `stroke_poly` (function) `progs/nuklear/nuklear_minios.c:594` `static void stroke_poly(int *xs, int *ys, int n, int th, int c)`
- `draw_text` (function) `progs/nuklear/nuklear_minios.c:601` `static void draw_text(int x, int y, const char *s, int len, int fg, int bg)`
- `draw_arc` (function) `progs/nuklear/nuklear_minios.c:615` `static void draw_arc(int cx, int cy, int r, float a0, float a1,
                     int filled, ...`
- `nk_rasterize` (function) `progs/nuklear/nuklear_minios.c:636` `void nk_rasterize(struct nk_context *ctx)`
- `nk_foreach` (function) `progs/nuklear/nuklear_minios.c:641` `nk_foreach(cmd, ctx)`
- `nk_minios_font_width` (function) `progs/nuklear/nuklear_minios.c:813` `static float nk_minios_font_width(nk_handle handle, float height,
                               ...` -- im->px[iy * im->w + ix]); } } break; } case NK_COMMAND_CUSTOM: break; default: break; } } } /* ---- Font (8x8...
- `nk_minios_font` (function) `progs/nuklear/nuklear_minios.c:819` `struct nk_user_font nk_minios_font(void)`
- `feed_key` (function) `progs/nuklear/nuklear_minios.c:854` `static void feed_key(struct nk_context *ctx, enum nk_keys key, int down)`
- `nk_set_scancode_hook` (function) `progs/nuklear/nuklear_minios.c:861` `void nk_set_scancode_hook(nk_scancode_cb cb, void *ud)`
- `handle_scancode` (function) `progs/nuklear/nuklear_minios.c:866` `static void handle_scancode(struct nk_context *ctx, unsigned char sc)`
- `nk_client_poll` (function) `progs/nuklear/nuklear_minios.c:914` `static void nk_client_poll(struct nk_context *ctx)` -- Client input pump: feed the pending .ev batch when its seq advanced, else hold the last state.
- `nk_poll_input` (function) `progs/nuklear/nuklear_minios.c:961` `void nk_poll_input(struct nk_context *ctx)`
- `nk_set_window_origin` (function) `progs/nuklear/nuklear_minios.c:1000` `void nk_set_window_origin(int x, int y)`
- `nk_quit_requested` (function) `progs/nuklear/nuklear_minios.c:1008` `int nk_quit_requested(void)` -- WM quit gesture latch: ESC or Alt+F4 pressed since the last poll.

## progs/nuklear/nuklear_minios.h
Depends on: `progs/minios_abi.h`
Imported by: `progs/doomedit/doomedit.c`, `progs/file/file.c`, `progs/nuklear/font8x8.c`, `progs/nuklear/node_editor.c`, `progs/nuklear/nuklear_minios.c`, `progs/paint/paint.c`, `progs/piano/piano.c`, `progs/vedit/vedit.c`
- `nk_rgb_available` (function) `progs/nuklear/nuklear_minios.h:33` `int nk_rgb_available(void);` -- RGB companion buffer (R,G,B byte order, NK_W x NK_H).
- `nk_idx_to_rgb` (function) `progs/nuklear/nuklear_minios.h:37` `void nk_idx_to_rgb(int idx, unsigned char *r, unsigned char *g, unsigned char *b);` -- Resolve one hybrid palette index to its exact RGB triple (canvas and preview mirrors that own indexed pixels reuse...
- `nk_sys_time_ms` (function) `progs/nuklear/nuklear_minios.h:41` `long nk_sys_time_ms(void);` -- Resolve one hybrid palette index to its exact RGB triple (canvas and preview mirrors that own indexed pixels reuse...
- `nk_sys_kbd` (function) `progs/nuklear/nuklear_minios.h:42` `long nk_sys_kbd(void);`
- `nk_sys_palette` (function) `progs/nuklear/nuklear_minios.h:43` `long nk_sys_palette(const unsigned char *pal768);`
- `nk_sys_kbd_raw` (function) `progs/nuklear/nuklear_minios.h:44` `long nk_sys_kbd_raw(int on);`
- `nk_sys_vga_mode` (function) `progs/nuklear/nuklear_minios.h:45` `long nk_sys_vga_mode(int on);`
- `nk_sys_fb_info` (function) `progs/nuklear/nuklear_minios.h:46` `long nk_sys_fb_info(int *w, int *h, int *pitch);`
- `nk_sys_mouse` (function) `progs/nuklear/nuklear_minios.h:47` `long nk_sys_mouse(int *xybw);`
- `nk_sys_mouse_badptr` (function) `progs/nuklear/nuklear_minios.h:51` `long nk_sys_mouse_badptr(void);` -- Call SYS_MOUSE with a pointer that is NOT in the user window; the kernel must reject it with -EFAULT.
- `nk_sys_nk_frame` (function) `progs/nuklear/nuklear_minios.h:52` `long nk_sys_nk_frame(int *origin);`
- `nk_sys_gfx_set_title` (function) `progs/nuklear/nuklear_minios.h:53` `long nk_sys_gfx_set_title(const char *t);` -- Call SYS_MOUSE with a pointer that is NOT in the user window; the kernel must reject it with -EFAULT.
- `nk_build_palette` (function) `progs/nuklear/nuklear_minios.h:57` `void nk_build_palette(unsigned char *pal768);` -- Hybrid palette: indices 0-14 are the desktop colors (kept so the desktop * behind the window never recolors); 15-255...
- `nk_minios_font` (function) `progs/nuklear/nuklear_minios.h:63` `struct nk_user_font nk_minios_font(void);` -- Hybrid palette: indices 0-14 are the desktop colors (kept so the desktop * behind the window never recolors); 15-255...
- `nk_rasterize` (function) `progs/nuklear/nuklear_minios.h:66` `void nk_rasterize(struct nk_context *ctx);` -- Hybrid palette: indices 0-14 are the desktop colors (kept so the desktop * behind the window never recolors); 15-255...
- `SYS_NK_FRAME` (function) `progs/nuklear/nuklear_minios.h:85` `* SYS_NK_FRAME (nk_set_window_origin). */ void nk_set_window_origin(int x, int y);`
- `nk_poll_input` (function) `progs/nuklear/nuklear_minios.h:87` `void nk_poll_input(struct nk_context *ctx);`
- `nk_quit_requested` (function) `progs/nuklear/nuklear_minios.h:92` `int nk_quit_requested(void);` -- WM quit gesture: ESC or Alt+F4 since the last poll (1 once, then clears).
- `nk_set_scancode_hook` (function) `progs/nuklear/nuklear_minios.h:101` `void nk_set_scancode_hook(nk_scancode_cb cb, void *ud);`

## progs/nuklear/nuklear_theme.c
Depends on: `kernel/string.c`, `progs/nuklear/nuklear_theme.h`
- `nk_theme_name_ok` (function) `progs/nuklear/nuklear_theme.c:37` `static int nk_theme_name_ok(const char *name)`
- `nk_theme_active` (function) `progs/nuklear/nuklear_theme.c:49` `int nk_theme_active(char *dst, int cap)`
- `nk_theme_parse_line` (function) `progs/nuklear/nuklear_theme.c:73` `static int nk_theme_parse_line(const char *line,
                               unsigned char rgb...`
- `nk_theme_probe` (function) `progs/nuklear/nuklear_theme.c:105` `int nk_theme_probe(const char *name, unsigned char rgb[NK_THEME_KEY_COUNT][3])`
- `nk_theme_apply` (function) `progs/nuklear/nuklear_theme.c:141` `int nk_theme_apply(struct nk_context *ctx, const char *name)`

## progs/nuklear/nuklear_theme.h
Imported by: `progs/doomedit/doomedit.c`, `progs/file/file.c`, `progs/nuklear/node_editor.c`, `progs/nuklear/nuklear_theme.c`, `progs/paint/paint.c`, `progs/piano/piano.c`, `progs/vedit/vedit.c`, `tests/test_theme.c`
- `nk_theme_active` (function) `progs/nuklear/nuklear_theme.h:62` `int nk_theme_active(char *dst, int cap);` -- X(scrollbar_cursor, 24) \ X(scrollbar_cursor_hover, 25) \ X(scrollbar_cursor_active, 26) \ X(tab_header, 27) \...
- `nk_theme_probe` (function) `progs/nuklear/nuklear_theme.h:65` `int nk_theme_probe(const char *name, unsigned char rgb[NK_THEME_KEY_COUNT][3]);` -- X(tab_header, 27) \ X(knob, 28) \ X(knob_cursor, 29) \ X(knob_cursor_hover, 30) \ X(knob_cursor_active, 31) #define...
- `nk_theme_apply` (function) `progs/nuklear/nuklear_theme.h:68` `int nk_theme_apply(struct nk_context *ctx, const char *name);` -- X(knob_cursor_hover, 30) \ X(knob_cursor_active, 31) #define NK_THEME_KEY_COUNT 32 struct nk_context; /** Resolve...

## progs/paint/paint.c
Depends on: `kernel/string.c`, `progs/minios_abi.h`, `progs/nuklear/nuklear_minios.h`, `progs/nuklear/nuklear_theme.h`
- `paint_clamp` (function) `progs/paint/paint.c:92` `static int paint_clamp(int v, int lo, int hi)` -- static int paint_size = 0; static int paint_down = 0; static int paint_lastx; static int paint_lasty; static int...
- `paint_plot` (function) `progs/paint/paint.c:99` `static int paint_plot(unsigned char *buf, int w, int h, int x, int y,
                      unsig...` -- static float paint_recty; static char paint_path[PAINT_PATH_MAX] = PAINT_DEFAULT_PATH; static char...
- `paint_dab` (function) `progs/paint/paint.c:108` `static void paint_dab(unsigned char *buf, int w, int h, int x, int y,
                      unsig...` -- if (v > hi) return hi; return v; } /** Bound-checked pixel plot, fail closed outside the canvas. static int...
- `paint_line` (function) `progs/paint/paint.c:119` `static int paint_line(unsigned char *buf, int w, int h, int x0, int y0,
                      int...` -- } /** Filled square dab of side s centered on (x, y). static void paint_dab(unsigned char *buf, int w, int h, int x...
- `paint_rect_fill` (function) `progs/paint/paint.c:144` `static int paint_rect_fill(unsigned char *buf, int w, int h, int x0, int y0,
                    ...` -- paint_dab(buf, w, h, x0, y0, c, s); n++; } if (x0 == x1 && y0 == y1) break; { int e2 = 2 * err; if (e2 > -dy) { err...
- `paint_circle_fill` (function) `progs/paint/paint.c:161` `static int paint_circle_fill(unsigned char *buf, int w, int h, int cx,
                          ...` -- int xb = x0 < x1 ? x1 : x0; int ya = y0 < y1 ? y0 : y1; int yb = y0 < y1 ? y1 : y0; int x; int y; int n = 0; if...
- `paint_flood` (function) `progs/paint/paint.c:179` `static int paint_flood(unsigned char *buf, int w, int h, int x, int y,
                       uns...` -- Bounded flood fill with mark-on-push: every cell is marked once, so * the explicit stack never exceeds the canvas size.
- `paint_nearest` (function) `progs/paint/paint.c:223` `static int paint_nearest(const unsigned char *pal, unsigned r, unsigned g,
                      ...` -- } if (cy + 1 < h && buf[(cy + 1) * w + cx] == oc) { buf[(cy + 1) * w + cx] = nc; sx[top] = cx; sy[top] = cy + 1...
- `paint_pal` (function) `progs/paint/paint.c:240` `static const unsigned char *paint_pal(void)` -- unsigned long bd = 0xFFFFFFFFUL; unsigned k; if (!pal) return -1; for (k = 0; k < 256; k++) { long dr = (long)pal[k...
- `paint_path_ok` (function) `progs/paint/paint.c:251` `static int paint_path_ok(const char *p)` -- } /** Cached hybrid palette: built once, shared by picker, save and load. static const unsigned char...
- `paint_crc_init` (function) `progs/paint/paint.c:272` `static void paint_crc_init(void)`
- `paint_crc_update` (function) `progs/paint/paint.c:285` `static unsigned long paint_crc_update(unsigned long c,
                                      cons...`
- `paint_adler` (function) `progs/paint/paint.c:296` `static unsigned long paint_adler(const unsigned char *p, unsigned long n)` -- paint_crc_ready = 1; } static unsigned long paint_crc_update(unsigned long c, const unsigned char *p, unsigned long...
- `paint_put_u32` (function) `progs/paint/paint.c:308` `static int paint_put_u32(unsigned char *dst, unsigned long cap,
                         unsigned...` -- /** Adler-32 over one buffer (the zlib trailer of a single IDAT). static unsigned long paint_adler(const unsigned...
- `paint_put_bytes` (function) `progs/paint/paint.c:320` `static int paint_put_bytes(unsigned char *dst, unsigned long cap,
                           unsi...` -- /** Bound-checked big-endian u32 store for the PNG writer. static int paint_put_u32(unsigned char *dst, unsigned...
- `paint_png_encode` (function) `progs/paint/paint.c:333` `static long paint_png_encode(unsigned char *dst, unsigned long cap,
                             ...` -- Encode indexed pixels as 8-bit truecolor PNG (stored deflate blocks). * Returns the byte count or a negative code on...
- `paint_load_file` (function) `progs/paint/paint.c:461` `static int paint_load_file(const char *path)` -- Decode a PNG file into the canvas (top-left, clamped, nearest-mapped). * Reports through the status line, never a...
- `paint_save_file` (function) `progs/paint/paint.c:514` `static int paint_save_file(const char *path)` -- for (x = 0; x < cw; x++) { int v = paint_nearest(pal768, px[(y * w + x) * 3], px[(y * w + x) * 3 + 1], px[(y * w +...
- `paint_blit` (function) `progs/paint/paint.c:549` `static void paint_blit(int ox, int oy)` -- Blit the canvas into the NK back-buffer after rasterize (and its RGB * twin when the kernel maps it, so the canvas...
- `paint_ink` (function) `progs/paint/paint.c:570` `static unsigned char paint_ink(void)` -- int dx = ox + x; int dy = oy + y; unsigned char r, g, b; volatile uint8_t *d; if (dx < 0 || dx >= NK_W || dy < 0 ||...
- `paint_handle_input` (function) `progs/paint/paint.c:577` `static void paint_handle_input(struct nk_context *ctx)` -- nk_idx_to_rgb(paint_px[y * PAINT_W + x], &r, &g, &b); d = NK_RGB_BUF + ((dy * NK_W) + dx) * 3; d[0] = r; d[1] = g...
- `paint_ui_build` (function) `progs/paint/paint.c:636` `static void paint_ui_build(struct nk_context *ctx)` -- Build the file row, the exact-size canvas beside the tool panel, and the status row.
- `paint_pattern_present` (function) `progs/paint/paint.c:720` `static int paint_pattern_present(int fw, int fh, int fp, int *ox, int *oy)` -- Scan the whole framebuffer for the canvas marker run (first four swatches consecutive).
- `paint_selftest` (function) `progs/paint/paint.c:755` `static int paint_selftest(void)` -- break; } } if (hit) { ox = x; oy = y; return 1; } } } return 0; } /** Headless selftest for BDD: core vectors, PNG...
- `paint_gui_run` (function) `progs/paint/paint.c:942` `static void paint_gui_run(void)` -- printf("paint: composite did not land (canvas %d,%d origin %d,%d)\n", (int)paint_rectx, (int)paint_recty, origin[0]...
- `main` (function) `progs/paint/paint.c:992` `int main(int argc, char **argv)`

## progs/piano/piano.c
Depends on: `kernel/string.c`, `progs/minios_abi.h`, `progs/nuklear/nuklear_minios.h`, `progs/nuklear/nuklear_theme.h`, `progs/src/opl3.c`
- `sys_pcm_open` (function) `progs/piano/piano.c:93` `static long sys_pcm_open(long flags)`
- `sys_pcm_write` (function) `progs/piano/piano.c:98` `static long sys_pcm_write(const void *buf, long len)` -- Returns bytes taken (NONBLOCK short count on backpressure, never a * stall), or negative on a dead path.
- `sys_pcm_close` (function) `progs/piano/piano.c:101` `static void sys_pcm_close(void)`
- `sys_yield` (function) `progs/piano/piano.c:104` `static void sys_yield(void)`
- `sys_present_idx` (function) `progs/piano/piano.c:112` `static long sys_present_idx(int *origin)` -- Indexed present (buffer id 1): the 288 KB indexed copy instead of the 864 KB RGB twin.
- `o3_op` (function) `progs/piano/piano.c:127` `static int o3_op(int ch, int is_car)`
- `o3_opreg` (function) `progs/piano/piano.c:131` `static void o3_opreg(int ch, int is_car, int regbase, int val)`
- `o3_chreg` (function) `progs/piano/piano.c:135` `static void o3_chreg(int ch, int regbase, int val)`
- `o3_note` (function) `progs/piano/piano.c:173` `static void o3_note(int ch, int midi, int on)`
- `midi_to_key` (function) `progs/piano/piano.c:211` `static int midi_to_key(int midi)`
- `clamp_midi` (function) `progs/piano/piano.c:234` `static int clamp_midi(int m)`
- `pedal_set` (function) `progs/piano/piano.c:241` `static void pedal_set(int on)` -- pressed scancode owns its channel until release.
- `voice_alloc` (function) `progs/piano/piano.c:255` `static int voice_alloc(void)`
- `note_off_key` (function) `progs/piano/piano.c:268` `static void note_off_key(int key)`
- `note_on_key` (function) `progs/piano/piano.c:281` `static void note_on_key(int key, int midi, int vel)`
- `kbd_semitone` (function) `progs/piano/piano.c:298` `static int kbd_semitone(int code)` -- ── PC-keyboard MIDI map (Fruity Loops style) ───────────────────────── PS/2 set-1 scancodes (7-bit code, E0 clear)...
- `kbd_all_off` (function) `progs/piano/piano.c:333` `static void kbd_all_off(void)`
- `note_on_sc` (function) `progs/piano/piano.c:339` `static void note_on_sc(int code, int vel)`
- `note_off_sc` (function) `progs/piano/piano.c:353` `static void note_off_sc(int code)`
- `piano_scancode` (function) `progs/piano/piano.c:369` `static void piano_scancode(int code, int make, int e0, void *ud)` -- Raw scancode hook (registered with nk_set_scancode_hook): note on/off * plus comma/period octave shift.
- `fx_configure` (function) `progs/piano/piano.c:421` `static void fx_configure(int delay_ms, int tremolo_pct, int clip, int vol)` -- #define FX_DELAY_CAP (RATE)           /* 1 s of delay at 22050 Hz #define FX_DELAY_MAX_MS 800 #define FX_FEEDBACK...
- `fx_process` (function) `progs/piano/piano.c:440` `static float fx_process(float x)`
- `sb_flush` (function) `progs/piano/piano.c:469` `static void sb_flush(void)` -- Flush held bytes to the low-latency ring.
- `render_audio` (function) `progs/piano/piano.c:484` `static void render_audio(long ms)`
- `key_rect` (function) `progs/piano/piano.c:511` `static void key_rect(int key, int *x, int *y, int *w, int *h)`
- `hit_key` (function) `progs/piano/piano.c:518` `static int hit_key(int mx, int my)`
- `hit_velocity` (function) `progs/piano/piano.c:535` `static int hit_velocity(int key, int my)` -- Velocity 1..100 from the click's vertical position inside a key: the very * top is soft, the bottom is loud.
- `ctrl_hit` (function) `progs/piano/piano.c:563` `static int ctrl_hit(int id, int mx, int my)`
- `ctrl_active` (function) `progs/piano/piano.c:567` `static int ctrl_active(int id)`
- `ctrl_press` (function) `progs/piano/piano.c:577` `static void ctrl_press(int id)`
- `ui_run` (function) `progs/piano/piano.c:594` `static void ui_run(int bench_ms)` -- case 1: if (octave < 2) octave++; break; case 2: if (volume > 0) volume -= 5; break; case 3: if (volume < 100)...
- `rate` (function) `progs/piano/piano.c:818` `* wait below caps the frame rate (bench mode skips it so the
         * benchmark still measures ...`
- `run_selftest` (function) `progs/piano/piano.c:836` `static int run_selftest(void)` -- sys_yield(); } else { sys_yield(); } } nk_set_scancode_hook(0, 0); nk_free(&ctx); nk_sys_kbd_raw(0)...
- `run_pcm2_probe` (function) `progs/piano/piano.c:1015` `static int run_pcm2_probe(void)` -- Headless pcm2 plumbing probe (BDD hook): open NONBLOCK, stream one 2048-byte pattern, close, reopen (release...
- `main` (function) `progs/piano/piano.c:1042` `int main(int argc, char **argv)`

## progs/pokemon/platform_minios.c
Depends on: `headers/audio.h`, `kernel/string.c`, `progs/minios_abi.h`, `progs/minios_png.h`
- `audible` (function) `progs/pokemon/platform_minios.c:36` `* voice is audible (noise SFX, sweep zaps), the raw mix estimate plays.
 *
 * Debug: heartbeat to...`
- `sys_kbd` (function) `progs/pokemon/platform_minios.c:75` `static long sys_kbd(void)`
- `sys_nk_frame` (function) `progs/pokemon/platform_minios.c:81` `static long sys_nk_frame(int *origin)`
- `sys_mouse` (function) `progs/pokemon/platform_minios.c:87` `static long sys_mouse(int *xybw)`
- `sys_vga_mode` (function) `progs/pokemon/platform_minios.c:93` `static long sys_vga_mode(int on)`
- `sys_kbd_raw` (function) `progs/pokemon/platform_minios.c:99` `static long sys_kbd_raw(int on)`
- `sys_palette` (function) `progs/pokemon/platform_minios.c:105` `static long sys_palette(const unsigned char *pal)`
- `sys_gfx_title` (function) `progs/pokemon/platform_minios.c:111` `static long sys_gfx_title(const char *t)`
- `sys_tone` (function) `progs/pokemon/platform_minios.c:117` `static long sys_tone(unsigned f)`
- `sys_pcm2_open` (function) `progs/pokemon/platform_minios.c:123` `static long sys_pcm2_open(long flags)`
- `sys_pcm2_write` (function) `progs/pokemon/platform_minios.c:129` `static long sys_pcm2_write(const void *buf, long len)`
- `sys_pcm2_close` (function) `progs/pokemon/platform_minios.c:135` `static void sys_pcm2_close(void)`
- `gain` (function) `progs/pokemon/platform_minios.c:142` `* timing gain (overshoot is microseconds against millisecond waits).
 * Difference-based, so it s...`
- `gb_platform_set_debug` (function) `progs/pokemon/platform_minios.c:190` `void gb_platform_set_debug(bool enabled)`
- `audio` (function) `progs/pokemon/platform_minios.c:218` `* PC speaker audio (DOOM-style: sparse syscalls from poll points) * * Per rendered frame, live voice frequencies...`
- `minios_audio_sample` (function) `progs/pokemon/platform_minios.c:262` `static void minios_audio_sample(GBContext *ctx, int16_t left, int16_t right)`
- `gb_voice_in_range` (function) `progs/pokemon/platform_minios.c:306` `static bool gb_voice_in_range(unsigned f)`
- `sample_apu_voices` (function) `progs/pokemon/platform_minios.c:310` `static void sample_apu_voices(gb_voice_t *v)`
- `minios_audio_play` (function) `progs/pokemon/platform_minios.c:330` `static void minios_audio_play(const gb_voice_t *v, bool pcm_audible,
                            ...`
- `rebuild_joypad` (function) `progs/pokemon/platform_minios.c:402` `static void rebuild_joypad(void)`
- `poll_keyboard` (function) `progs/pokemon/platform_minios.c:416` `static void poll_keyboard(void)`
- `push_332_palette` (function) `progs/pokemon/platform_minios.c:455` `static void push_332_palette(void)` -- 3-3-2 RGB palette ramp, pushed ONCE at init (not per frame). * Pixel index = (R & 0xE0) | ((G & 0xE0) >> 3) | ((B &...
- `menu` (function) `progs/pokemon/platform_minios.c:571` `* FILE menu (no Nuklear on purpose) * * A 16 px menu bar lives in the top margin the 2x GB image never touches * (it...`
- `ui_fringe_dirty` (function) `progs/pokemon/platform_minios.c:620` `static bool ui_fringe_dirty(uint32_t now)`
- `ui_fringe_sync` (function) `progs/pokemon/platform_minios.c:626` `static void ui_fringe_sync(uint32_t now)`
- `menu_fill` (function) `progs/pokemon/platform_minios.c:632` `static void menu_fill(int x0, int y0, int w, int h, uint8_t idx)`
- `menu_text` (function) `progs/pokemon/platform_minios.c:645` `static void menu_text(int x, int y, const char *s, uint8_t fg)`
- `menu_osd` (function) `progs/pokemon/platform_minios.c:664` `static void menu_osd(const char *s)`
- `menu_draw` (function) `progs/pokemon/platform_minios.c:670` `static void menu_draw(void)`
- `menu_item_at` (function) `progs/pokemon/platform_minios.c:700` `static int menu_item_at(int lx, int ly)`
- `menu_do_save` (function) `progs/pokemon/platform_minios.c:707` `static void menu_do_save(void)`
- `menu_do_load` (function) `progs/pokemon/platform_minios.c:723` `static void menu_do_load(void)`
- `menu_activate` (function) `progs/pokemon/platform_minios.c:742` `static void menu_activate(int it)`
- `poll_menu` (function) `progs/pokemon/platform_minios.c:776` `static void poll_menu(void)` -- Esc toggles, Up/Down move, Enter activates; the mouse is a bonus. * PS/2 Set 1: Esc = 0x01, Up = 0x48, Down = 0x50...
- `pokemon_art_load_one` (function) `progs/pokemon/platform_minios.c:844` `static int pokemon_art_load_one(const char *path, unsigned char **rgb,
                          ...`
- `pokemon_art_load` (function) `progs/pokemon/platform_minios.c:869` `static void pokemon_art_load(void)`
- `pokemon_art_draw_one` (function) `progs/pokemon/platform_minios.c:887` `static void pokemon_art_draw_one(const unsigned char *rgb, int sw, int sh,
                      ...`
- `pokemon_art_draw` (function) `progs/pokemon/platform_minios.c:925` `static void pokemon_art_draw(void)`
- `px_to_idx` (function) `progs/pokemon/platform_minios.c:956` `static uint8_t px_to_idx(uint32_t pixel)`
- `upload_frame` (function) `progs/pokemon/platform_minios.c:975` `static void upload_frame(const uint32_t *framebuffer)`
- `gb_platform_init` (function) `progs/pokemon/platform_minios.c:1056` `bool gb_platform_init(int scale)`
- `minios_persist_path` (function) `progs/pokemon/platform_minios.c:1088` `static void minios_persist_path(char *out, size_t n, const GBContext *ctx,
                      ...`
- `minios_legacy_path` (function) `progs/pokemon/platform_minios.c:1097` `static void minios_legacy_path(char *out, size_t n, const GBContext *ctx,
                       ...` -- Legacy ramdisk path (pre-MiniFS fix wrote bin/<id>.* onto volatile ramdisk).
- `minios_load_helper` (function) `progs/pokemon/platform_minios.c:1103` `static bool minios_load_helper(const char *path, void *data, size_t size,
                       ...`
- `minios_save_helper` (function) `progs/pokemon/platform_minios.c:1121` `static bool minios_save_helper(const char *path, const void *data, size_t size)`
- `minios_load_battery_ram` (function) `progs/pokemon/platform_minios.c:1132` `static bool minios_load_battery_ram(GBContext *ctx, const char *rom_name,
                       ...`
- `minios_save_battery_ram` (function) `progs/pokemon/platform_minios.c:1147` `static bool minios_save_battery_ram(GBContext *ctx, const char *rom_name,
                       ...`
- `minios_load_rtc_data` (function) `progs/pokemon/platform_minios.c:1157` `static bool minios_load_rtc_data(GBContext *ctx, const char *rom_name,
                          ...`
- `minios_save_rtc_data` (function) `progs/pokemon/platform_minios.c:1170` `static bool minios_save_rtc_data(GBContext *ctx, const char *rom_name,
                          ...`
- `minios_fast_forward` (function) `progs/pokemon/platform_minios.c:1208` `static inline bool minios_fast_forward(void)`
- `minios_state_path` (function) `progs/pokemon/platform_minios.c:1212` `static void minios_state_path(char *out, size_t n, const GBContext *ctx)`
- `minios_legacy_state_path` (function) `progs/pokemon/platform_minios.c:1217` `static void minios_legacy_state_path(char *out, size_t n, const GBContext *ctx)`
- `minios_autosave` (function) `progs/pokemon/platform_minios.c:1222` `static void minios_autosave(uint32_t now)`
- `poll_hotkeys` (function) `progs/pokemon/platform_minios.c:1236` `static void poll_hotkeys(void)` -- PS/2 Set 1: F5 = 0x3F, F8 = 0x42, Ctrl = 0x1D, S = 0x1F, L = 0x26, SPACE = 0x39, Shift = 0x2A/0x36.
- `gb_platform_register_context` (function) `progs/pokemon/platform_minios.c:1288` `void gb_platform_register_context(GBContext *ctx)`
- `gb_platform_shutdown` (function) `progs/pokemon/platform_minios.c:1310` `void gb_platform_shutdown(void)`
- `gb_platform_poll_events` (function) `progs/pokemon/platform_minios.c:1321` `bool gb_platform_poll_events(GBContext *ctx)`
- `gb_platform_render_frame` (function) `progs/pokemon/platform_minios.c:1330` `void gb_platform_render_frame(const uint32_t *framebuffer)`
- `frames` (function) `progs/pokemon/platform_minios.c:1366` `* frames (menu bar not on screen yet) and any frame after the
         * LCD-off path zeroed the ...`
- `gb_platform_present_framebuffer` (function) `progs/pokemon/platform_minios.c:1399` `void gb_platform_present_framebuffer(const uint32_t *framebuffer)`
- `gb_platform_render_lcd_off_frame` (function) `progs/pokemon/platform_minios.c:1411` `void gb_platform_render_lcd_off_frame(void)`
- `gb_platform_vsync` (function) `progs/pokemon/platform_minios.c:1433` `void gb_platform_vsync(uint32_t frame_cycles)`
- `gb_platform_set_benchmark_mode` (function) `progs/pokemon/platform_minios.c:1450` `void gb_platform_set_benchmark_mode(bool enabled)`
- `gb_platform_set_input_script` (function) `progs/pokemon/platform_minios.c:1454` `bool gb_platform_set_input_script(const char *script)`
- `gb_platform_set_input_record_file` (function) `progs/pokemon/platform_minios.c:1460` `void gb_platform_set_input_record_file(const char *path)`
- `gb_platform_set_persistence_dir` (function) `progs/pokemon/platform_minios.c:1465` `bool gb_platform_set_persistence_dir(const char *path)`
- `gb_platform_set_dump_frames` (function) `progs/pokemon/platform_minios.c:1474` `void gb_platform_set_dump_frames(const char *frames)`
- `gb_platform_set_dump_present_frames` (function) `progs/pokemon/platform_minios.c:1496` `void gb_platform_set_dump_present_frames(const char *frames)`
- `gb_platform_set_screenshot_prefix` (function) `progs/pokemon/platform_minios.c:1517` `void gb_platform_set_screenshot_prefix(const char *prefix)`
- `gb_platform_get_timing_info` (function) `progs/pokemon/platform_minios.c:1523` `void gb_platform_get_timing_info(GBPlatformTimingInfo *out)`
- `gb_platform_get_joypad` (function) `progs/pokemon/platform_minios.c:1530` `uint8_t gb_platform_get_joypad(void)`
- `gb_platform_set_title` (function) `progs/pokemon/platform_minios.c:1534` `void gb_platform_set_title(const char *title)`
- `gb_platform_get_smooth_lcd_transitions` (function) `progs/pokemon/platform_minios.c:1540` `bool gb_platform_get_smooth_lcd_transitions(void)`
- `gb_platform_set_smooth_lcd_transitions` (function) `progs/pokemon/platform_minios.c:1544` `void gb_platform_set_smooth_lcd_transitions(bool enabled)`
- `gb_platform_set_launcher_return_enabled` (function) `progs/pokemon/platform_minios.c:1548` `void gb_platform_set_launcher_return_enabled(bool enabled)`
- `gb_platform_get_exit_action` (function) `progs/pokemon/platform_minios.c:1552` `GBPlatformExitAction gb_platform_get_exit_action(void)`
- `gb_platform_submit_port_frame` (function) `progs/pokemon/platform_minios.c:1556` `void gb_platform_submit_port_frame(void *user, const GBPortFrame *frame)`
- `gb_platform_test_audio_concurrency` (function) `progs/pokemon/platform_minios.c:1562` `bool gb_platform_test_audio_concurrency(uint32_t frames,
                                        ...` -- void gb_platform_set_launcher_return_enabled(bool enabled) { (void)enabled; } GBPlatformExitAction...
- `gb_platform_test_inject_persistence_fault` (function) `progs/pokemon/platform_minios.c:1571` `void gb_platform_test_inject_persistence_fault(
    GBPersistenceTestTarget target,
    GBPersist...`

## progs/quake2generic/q2generic_minios.c
Depends on: `kernel/string.c`, `progs/doomgeneric/r_local.h`, `progs/minios_abi.h`
- `MINIOS_DOOM_BACKBUF_ADDR` (function) `progs/quake2generic/q2generic_minios.c:4` `* MINIOS_DOOM_BACKBUF_ADDR (minios_abi.h);`
- `MINIOS_GFX_BUF_GAME` (function) `progs/quake2generic/q2generic_minios.c:5` `* MINIOS_SYS_GFX_PRESENT with MINIOS_GFX_BUF_GAME (211 stays as a kernel
 * compat alias) and the...`
- `sys_kbd` (function) `progs/quake2generic/q2generic_minios.c:30` `static long sys_kbd(void)`
- `sys_palette` (function) `progs/quake2generic/q2generic_minios.c:36` `static long sys_palette(const unsigned char *pal)`
- `sys_kbd_raw` (function) `progs/quake2generic/q2generic_minios.c:42` `static long sys_kbd_raw(int on)`
- `sys_vga_mode` (function) `progs/quake2generic/q2generic_minios.c:48` `static long sys_vga_mode(int on)`
- `sys_doom_frame` (function) `progs/quake2generic/q2generic_minios.c:54` `static long sys_doom_frame(void)`
- `sys_mouse` (function) `progs/quake2generic/q2generic_minios.c:60` `static long sys_mouse(int *buf)`
- `sys_set_title` (function) `progs/quake2generic/q2generic_minios.c:66` `static long sys_set_title(const char *t)`
- `sys_gfx_zoom` (function) `progs/quake2generic/q2generic_minios.c:72` `static long sys_gfx_zoom(long mode)`
- `q2g_parse_windowed` (function) `progs/quake2generic/q2generic_minios.c:86` `static void q2g_parse_windowed(int argc, char **argv)`
- `Sys_Quit` (function) `progs/quake2generic/q2generic_minios.c:99` `extern void Sys_Quit(void);` -- Sys_Quit lives in the engine's system driver (other/q_system.c); not pulled * in through quake2.h, so declare it...
- `Cbuf_AddText` (function) `progs/quake2generic/q2generic_minios.c:102` `extern void Cbuf_AddText(char *text);` -- Sys_Quit lives in the engine's system driver (other/q_system.c); not pulled * in through quake2.h, so declare it...
- `q2snd_probe` (function) `progs/quake2generic/q2generic_minios.c:106` `extern int q2snd_probe(void);` -- Sound backend probe (snddma_minios.c): headless proof the DMA layer * reaches the pcm2 path, run with...
- `q2g_parse_autoframes` (function) `progs/quake2generic/q2generic_minios.c:121` `static void q2g_parse_autoframes(int argc, char **argv)`
- `QG_GetMouseDiff` (function) `progs/quake2generic/q2generic_minios.c:154` `void QG_GetMouseDiff(int *dx, int *dy)`
- `QG_CaptureMouse` (function) `progs/quake2generic/q2generic_minios.c:168` `void QG_CaptureMouse(void)`
- `QG_ReleaseMouse` (function) `progs/quake2generic/q2generic_minios.c:172` `void QG_ReleaseMouse(void)`
- `QG_Mkdir` (function) `progs/quake2generic/q2generic_minios.c:175` `void QG_Mkdir(const char *path)`
- `scancode_to_q2key` (function) `progs/quake2generic/q2generic_minios.c:179` `static unsigned char scancode_to_q2key(unsigned char raw)`
- `extended_to_q2key` (function) `progs/quake2generic/q2generic_minios.c:262` `static unsigned char extended_to_q2key(unsigned char sc)`
- `kbd_poll` (function) `progs/quake2generic/q2generic_minios.c:280` `static void kbd_poll(void)`
- `SWimp_SetPalette` (function) `progs/quake2generic/q2generic_minios.c:310` `void SWimp_SetPalette(const unsigned char *palette)`
- `SWimp_SetMode` (function) `progs/quake2generic/q2generic_minios.c:320` `rserr_t SWimp_SetMode(int *pwidth, int *pheight, int mode, qboolean fullscreen)`
- `SWimp_Init` (function) `progs/quake2generic/q2generic_minios.c:337` `int SWimp_Init(void *hInstance, void *wndProc)`
- `SWimp_Shutdown` (function) `progs/quake2generic/q2generic_minios.c:346` `void SWimp_Shutdown(void)`
- `SWimp_BeginFrame` (function) `progs/quake2generic/q2generic_minios.c:349` `void SWimp_BeginFrame(float camera_separation)`
- `SWimp_EndFrame` (function) `progs/quake2generic/q2generic_minios.c:352` `void SWimp_EndFrame(void)`
- `SWimp_AppActivate` (function) `progs/quake2generic/q2generic_minios.c:381` `void SWimp_AppActivate(qboolean active)`
- `QG_Milliseconds` (function) `progs/quake2generic/q2generic_minios.c:385` `int QG_Milliseconds(void)`
- `main` (function) `progs/quake2generic/q2generic_minios.c:389` `int main(int argc, char **argv)`

## progs/quake2generic/snddma_minios.c
Depends on: `kernel/string.c`, `progs/minios_abi.h`
- `sys_pcm2_open` (function) `progs/quake2generic/snddma_minios.c:67` `static long sys_pcm2_open(long flags)`
- `sys_pcm2_write` (function) `progs/quake2generic/snddma_minios.c:75` `static long sys_pcm2_write(const void *buf, long len)`
- `sys_pcm2_close` (function) `progs/quake2generic/snddma_minios.c:83` `static void sys_pcm2_close(void)`
- `sys_time_ms` (function) `progs/quake2generic/snddma_minios.c:89` `static long sys_time_ms(void)`
- `q2_dma_push` (function) `progs/quake2generic/snddma_minios.c:104` `static int q2_dma_push(int end)` -- Push the freshly painted range [q2_dma_written, end) in ring order with NONBLOCK writes that take what the kernel...
- `SNDDMA_Init` (function) `progs/quake2generic/snddma_minios.c:138` `qboolean SNDDMA_Init(void)`
- `SNDDMA_GetDMAPos` (function) `progs/quake2generic/snddma_minios.c:182` `int SNDDMA_GetDMAPos(void)`
- `SNDDMA_Shutdown` (function) `progs/quake2generic/snddma_minios.c:190` `void SNDDMA_Shutdown(void)`
- `SNDDMA_BeginPainting` (function) `progs/quake2generic/snddma_minios.c:202` `void SNDDMA_BeginPainting(void)`
- `SNDDMA_Submit` (function) `progs/quake2generic/snddma_minios.c:205` `void SNDDMA_Submit(void)`
- `q2snd_probe` (function) `progs/quake2generic/snddma_minios.c:222` `int q2snd_probe(void)` -- Headless plumbing probe (BDD hook): open pcm2, stream one pattern, close, report.

## progs/src/aes.c
- `GF` (function) `progs/src/aes.c:8` `* generated procedurally from the GF(2^8) multiplicative inverse plus the * FIPS-197 affine transform, so the file...`
- `putchar` (function) `progs/src/aes.c:25` `int putchar();`
- `strcmp` (function) `progs/src/aes.c:26` `int strcmp();`
- `strlen` (function) `progs/src/aes.c:27` `int strlen();`
- `fopen` (function) `progs/src/aes.c:28` `void *fopen();`
- `fclose` (function) `progs/src/aes.c:29` `int fclose();`
- `fread` (function) `progs/src/aes.c:30` `int fread();`
- `fwrite` (function) `progs/src/aes.c:31` `int fwrite();`
- `fseek` (function) `progs/src/aes.c:32` `int fseek();`
- `ftell` (function) `progs/src/aes.c:33` `int ftell();`
- `rewind` (function) `progs/src/aes.c:34` `void rewind();`
- `malloc` (function) `progs/src/aes.c:35` `void *malloc();`
- `free` (function) `progs/src/aes.c:36` `void free();`
- `aes_read_all` (function) `progs/src/aes.c:69` `static char *aes_read_all(const char *name, int *len)`
- `aes_write_all` (function) `progs/src/aes.c:86` `static int aes_write_all(const char *name, char *data, int len)`
- `aes_has` (function) `progs/src/aes.c:96` `static int aes_has(const char *s, const char *needle)`
- `hex_val` (function) `progs/src/aes.c:110` `static int hex_val(int c)`
- `aes_parse_hex` (function) `progs/src/aes.c:117` `static int aes_parse_hex(const char *s, int want, int *out)`
- `aes_gf_mul` (function) `progs/src/aes.c:130` `static int aes_gf_mul(int a, int b)` -- static int aes_parse_hex(const char *s, int want, int *out) { int i, hi, lo; if ((int)strlen(s) != want) return 0...
- `aes_xtime` (function) `progs/src/aes.c:142` `static int aes_xtime(int x)`
- `aes_rotl8` (function) `progs/src/aes.c:148` `static int aes_rotl8(int x, int n)`
- `aes_init_tables` (function) `progs/src/aes.c:155` `static void aes_init_tables(void)` -- Build the S-box from first principles: multiplicative inverse in GF(2^8) composed with the FIPS-197 affine transform.
- `aes_key_expand` (function) `progs/src/aes.c:174` `static void aes_key_expand(const int *key)` -- Expand the 32-byte key into AES_RK_LEN round-key bytes (FIPS-197 for Nk=8, Nr=14: RotWord plus SubWord every Nk...
- `aes_add_round_key` (function) `progs/src/aes.c:209` `static void aes_add_round_key(int round)`
- `aes_sub_bytes` (function) `progs/src/aes.c:215` `static void aes_sub_bytes(void)`
- `aes_shift_rows` (function) `progs/src/aes.c:220` `static void aes_shift_rows(void)`
- `aes_mix_columns` (function) `progs/src/aes.c:228` `static void aes_mix_columns(void)`
- `aes_cipher` (function) `progs/src/aes.c:248` `static void aes_cipher(void)`
- `aes_iv_increment` (function) `progs/src/aes.c:263` `static void aes_iv_increment(void)` -- int r; aes_add_round_key(0); for (r = 1; r < AES_ROUNDS; r++) { aes_sub_bytes(); aes_shift_rows()...
- `aes_ctr_crypt` (function) `progs/src/aes.c:273` `static void aes_ctr_crypt(char *data, int len)` -- aes_add_round_key(AES_ROUNDS); } /* Big-endian increment of the whole counter block (SP 800-38A CTR). static void...
- `aes_hdr_put` (function) `progs/src/aes.c:288` `static void aes_hdr_put(char *h, int size)`
- `aes_hdr_get` (function) `progs/src/aes.c:299` `static int aes_hdr_get(char *h)`
- `aes_tool_name` (function) `progs/src/aes.c:307` `static const char *aes_tool_name(int decode)`
- `aes_run` (function) `progs/src/aes.c:312` `static int aes_run(int decode, const char *keyhex, const char *noncehex,
                   const...`
- `main` (function) `progs/src/aes.c:384` `int main(int argc, char **argv)`

## progs/src/aslr.c
- `as_sc` (function) `progs/src/aslr.c:10` `static long as_sc(long n, long a1, long a2, long a3)` -- aslr -- userspace ASLR probe (self-exec chain).  gen0 (no args) prints its stack pointer, brk and first-mmap...
- `as_mmap` (function) `progs/src/aslr.c:18` `static long as_mmap(void)`
- `as_write` (function) `progs/src/aslr.c:31` `static void as_write(const char *s, unsigned long len)`
- `as_exit` (function) `progs/src/aslr.c:35` `static void as_exit(long code)`
- `as_execve` (function) `progs/src/aslr.c:40` `static void as_execve(const char *path, const char **argv)`
- `as_putu` (function) `progs/src/aslr.c:47` `static void as_putu(unsigned long v)`
- `as_atou` (function) `progs/src/aslr.c:59` `static unsigned long as_atou(const char *s)`
- `as_rsp` (function) `progs/src/aslr.c:68` `static unsigned long as_rsp(void)`
- `as_fail` (function) `progs/src/aslr.c:74` `static void as_fail(int step)`
- `lmain` (function) `progs/src/aslr.c:82` `int lmain(long argc, char **argv)`

## progs/src/audio.c
Depends on: `progs/minios_abi.h`
- `syscall1` (function) `progs/src/audio.c:3` `static long syscall1(long n, long a1)`
- `syscall2` (function) `progs/src/audio.c:9` `static long syscall2(long n, long a1, long a2)`
- `syscall3` (function) `progs/src/audio.c:15` `static long syscall3(long n, long a1, long a2, long a3)`
- `syscall0` (function) `progs/src/audio.c:21` `static long syscall0(long n)`
- `audio_init` (function) `progs/src/audio.c:27` `int audio_init(void)`
- `audio_tone` (function) `progs/src/audio.c:31` `void audio_tone(unsigned freq)`
- `audio_pcm_open` (function) `progs/src/audio.c:35` `int audio_pcm_open(unsigned rate, unsigned channels, unsigned format)`
- `audio_pcm_submit` (function) `progs/src/audio.c:40` `int audio_pcm_submit(const void *buf, unsigned len)`
- `audio_pcm_pump` (function) `progs/src/audio.c:44` `void audio_pcm_pump(void)`
- `audio_pcm_close` (function) `progs/src/audio.c:48` `void audio_pcm_close(void)`
- `audio_set_volume` (function) `progs/src/audio.c:52` `void audio_set_volume(unsigned volume)`
- `audio_get_volume` (function) `progs/src/audio.c:56` `unsigned audio_get_volume(void)`
- `audio_sb16_present` (function) `progs/src/audio.c:60` `int audio_sb16_present(void)`
- `audio_stream_open` (function) `progs/src/audio.c:64` `int audio_stream_open(void)`
- `audio_stream_close` (function) `progs/src/audio.c:68` `void audio_stream_close(int id)`
- `audio_stream_submit` (function) `progs/src/audio.c:72` `int audio_stream_submit(int id, const void *buf, unsigned len)`
- `audio_stream_volume` (function) `progs/src/audio.c:76` `void audio_stream_volume(int id, unsigned char vol)`

## progs/src/burn.c
- `bn_sc` (function) `progs/src/burn.c:6` `static long bn_sc(long n, long a1, long a2, long a3)` -- burn -- SMP mixed-workload probe: brk plus mmap plus CPU burn with a deterministic checksum.
- `bn_mmap` (function) `progs/src/burn.c:14` `static long bn_mmap(unsigned long len)`
- `bn_write` (function) `progs/src/burn.c:27` `static void bn_write(const char *s, unsigned long len)`
- `bn_exit` (function) `progs/src/burn.c:31` `static void bn_exit(long code)`
- `bn_putu` (function) `progs/src/burn.c:36` `static void bn_putu(unsigned long v)`
- `bn_fail` (function) `progs/src/burn.c:48` `static void bn_fail(void)`
- `lmain` (function) `progs/src/burn.c:53` `int lmain(void)`

## progs/src/cp.c
- `printf` (function) `progs/src/cp.c:1` `int printf();`
- `fopen` (function) `progs/src/cp.c:2` `void *fopen();`
- `fclose` (function) `progs/src/cp.c:3` `int fclose();`
- `fread` (function) `progs/src/cp.c:4` `int fread();`
- `fwrite` (function) `progs/src/cp.c:5` `int fwrite();`
- `main` (function) `progs/src/cp.c:10` `int main(int argc, char **argv)`

## progs/src/cpl.c
- `read_cpl` (function) `progs/src/cpl.c:6` `static long read_cpl(void)` -- Ring-3 privilege probe.
- `exit_now` (function) `progs/src/cpl.c:12` `static void exit_now(long code)`

## progs/src/execho.c
- `program` (function) `progs/src/execho.c:5` `* * Proves the UNIX process composition the kernel lacked: a child * produced by fork replaces its image with execve...`
- `path` (function) `progs/src/execho.c:7` `* execs a ghost path (must fail -2, exits 42). The parent checks
 * both wait4 results with Linux...`
- `ex_write` (function) `progs/src/execho.c:20` `static void ex_write(const char *s, unsigned long len)`
- `ex_exit` (function) `progs/src/execho.c:24` `static void ex_exit(long code)`
- `ex_fail` (function) `progs/src/execho.c:29` `static void ex_fail(int step)`
- `lmain` (function) `progs/src/execho.c:37` `int lmain(void)`

## progs/src/execthr.c
- `et_sc` (function) `progs/src/execthr.c:11` `static long et_sc(long n, long a1, long a2, long a3)` -- execthr -- execve kills sibling threads (Linux semantics).
- `et_exit` (function) `progs/src/execthr.c:19` `static void et_exit(long code)`
- `et_thread` (function) `progs/src/execthr.c:27` `static void et_thread(void)`
- `lmain` (function) `progs/src/execthr.c:33` `int lmain(void)`

## progs/src/fib.c
- `fib` (function) `progs/src/fib.c:1` `int fib(int n)`
- `main` (function) `progs/src/fib.c:6` `int main(void)`

## progs/src/forktest.c
- `fx_syscall6` (function) `progs/src/forktest.c:17` `static long fx_syscall6(long n, long a1, long a2, long a3, long a4, long a5, long a6)`
- `fx_strlen` (function) `progs/src/forktest.c:41` `static unsigned long fx_strlen(const char *s)`
- `fx_write` (function) `progs/src/forktest.c:47` `static void fx_write(const char *s)`
- `fx_exit` (function) `progs/src/forktest.c:51` `static void fx_exit(long code)`
- `this` (function) `progs/src/forktest.c:115` `* this (and the child's closes must survive below). */ fx_syscall6(SYS_close, pfd[1], 0, 0, 0, 0, 0);`

## progs/src/fptest.c
Depends on: `progs/minios_abi.h`, `progs/src/mthreads.h`
- `gettid` (function) `progs/src/fptest.c:21` `* * The same run smokes gettid (Phase 0.4: the two workers must observe * distinct tids, never the constant 1) and...`
- `read_mxcsr` (function) `progs/src/fptest.c:42` `static unsigned int read_mxcsr(void)`
- `raw_gettid` (function) `progs/src/fptest.c:48` `static long raw_gettid(void)`
- `raw_getrandom` (function) `progs/src/fptest.c:52` `static long raw_getrandom(void *buf, unsigned long n)`
- `stack_align_canary` (function) `progs/src/fptest.c:78` `static void stack_align_canary(void)` -- Stack-alignment canary: an aligned SSE store to a stack slot faults with #GP unless the thread entry stack satisfies...
- `worker` (function) `progs/src/fptest.c:84` `static void *worker(void *p)`
- `main` (function) `progs/src/fptest.c:148` `int main(void)`


Next: [API_p17.md](API_p17.md)
