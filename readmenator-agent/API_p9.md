# API (page 9 of 21)
Previous: [API_p8.md](API_p8.md)

## kernel/vga_fb.c
Depends on: `headers/arch/x86/boot/bootdefs.h`, `headers/avatar_data.h`, `headers/desktop_icons.h`, `headers/desktop_shortcuts.h`, `headers/drivers/kbd.h`, `headers/kernel/vga_cursor.h`, `headers/sched.h`, `headers/vga_fb.h`, `headers/vga_fx.h`, `headers/wm_chrome.h`, `headers/wm_events.h`, `headers/wm_focus.h`, `headers/wm_geom.h`, `headers/wm_gfxview.h`, `headers/wm_jelly.h`, `headers/wm_layout.h`, `headers/wm_notify.h`, `headers/wm_render.h`, `headers/wm_tiling.h`, `headers/wm_window.h`
- `wm_geom_cfg` (function) `kernel/vga_fb.c:54` `static wm_geom_config_t wm_geom_cfg(void)` -- _Static_assert(WM_FOCUS_GFX == WM_WINDOW_GFX_ID, "gfx focus id drifted from unified window contract"); static void...
- `wm_event_cfg` (function) `kernel/vga_fb.c:65` `static wm_event_config_t wm_event_cfg(void)` -- static int wm_ggy; /** Docstring: Geometry config derived once from the font layout. static wm_geom_config_t...
- `wm_drag_reset` (function) `kernel/vga_fb.c:74` `static void wm_drag_reset(void)` -- cfg.title_h = FONT_H; return cfg; } /** Docstring: Event config for the PS/2 mouse button mask. static...
- `vga_fb_boot_config` (function) `kernel/vga_fb.c:96` `void vga_fb_boot_config(void)`
- `fb_bytes_per_pixel` (function) `kernel/vga_fb.c:123` `int fb_bytes_per_pixel(void)`
- `compositions` (function) `kernel/vga_fb.c:139` `* compositions (an ISR tick composing inside a syscall composition) draw * into the same shadow and leave the...`
- `fb_copy_bytes` (function) `kernel/vga_fb.c:157` `static void fb_copy_bytes(volatile void *dst, const volatile void *src, unsigned long n)` -- Docstring: Bulk copy through the string engine: quadwords first (rep movsq, an eighth of the iterations, which is...
- `fb_fill_u32` (function) `kernel/vga_fb.c:175` `static void fb_fill_u32(volatile void *dst, unsigned int v, unsigned long n)` -- Docstring: Fill n 32-bit words with one value: pairs as quadwords * (rep stosq), then the odd word.
- `fb_frame_bytes` (function) `kernel/vga_fb.c:189` `static unsigned long fb_frame_bytes(void)` -- static void fb_fill_u32(volatile void *dst, unsigned int v, unsigned long n) { void *d = (void *)dst; unsigned long...
- `fb_shadow_ready` (function) `kernel/vga_fb.c:195` `static int fb_shadow_ready(void)` -- : "+D"(d), "+c"(q) : "a"(pat) : "memory"); if (n & 1UL) (volatile unsigned int *)d = v; } /** Docstring: Bytes one...
- `fb_present_shadow` (function) `kernel/vga_fb.c:219` `static void fb_present_shadow(void)` -- Docstring: Copy the whole shadow onto the visible framebuffer; an * armed wobble band is presented through its mesh...
- `fb_compose_begin` (function) `kernel/vga_fb.c:233` `static int fb_compose_begin(void)` -- Docstring: Enter a composition.
- `fb_compose_end` (function) `kernel/vga_fb.c:246` `static void fb_compose_end(int owner)` -- entry that must not present. static int fb_compose_begin(void) { if (fb_compose_depth++ > 0) { return 0; } if...
- `lg_get` (function) `kernel/vga_fb.c:319` `static const char *lg_get(int i)` -- Docstring: Completed-logical-lines ring, heap-owned since the .bss diet (256 x TERM_MAX_COLS).
- `lg_push` (function) `kernel/vga_fb.c:326` `static void lg_push(const char *line, int len)` -- Append a completed logical line to the ring.
- `lg_alloc` (function) `kernel/vga_fb.c:347` `static void lg_alloc(void)`
- `vga_fb_term_ring_init` (function) `kernel/vga_fb.c:363` `void vga_fb_term_ring_init(void)` -- Docstring: Create the terminal history ring.
- `vga_fb_term_feed` (function) `kernel/vga_fb.c:371` `void vga_fb_term_feed(const char *line, int len)` -- Docstring: Feed one completed console line into the terminal history.
- `line_nrows` (function) `kernel/vga_fb.c:378` `static int line_nrows(int len)` -- Docstring: Feed one completed console line into the terminal history.
- `act_nrows` (function) `kernel/vga_fb.c:385` `static int act_nrows(void)`
- `total_rows` (function) `kernel/vga_fb.c:388` `static int total_rows(void)` -- lg_push(line, len); } /* Display rows a logical line of `len` characters occupies at term_cols. static int...
- `disp_clamp` (function) `kernel/vga_fb.c:396` `static void disp_clamp(void)` -- return n; } static int act_nrows(void) { return line_nrows(act_len); } /* Total display rows of the whole history...
- `line_at` (function) `kernel/vga_fb.c:414` `static const char *line_at(int abs, int *off)` -- Locate the logical line contributing the display row `abs`, and set *off to the character offset where that display...
- `fx_plan_burn` (function) `kernel/vga_fb.c:494` `static void fx_plan_burn(int x, int y, int w, int h)`
- `fx_plan_genie` (function) `kernel/vga_fb.c:500` `static void fx_plan_genie(int x, int y, int w, int h, int tx, int ty, int reverse)`
- `first` (function) `kernel/vga_fb.c:512` `* screen ever showing it whole first (the old flash-then-melt). */
static unsigned int *fx_start_...`
- `flag` (function) `kernel/vga_fb.c:606` `* is the minimized flag (the program keeps running, nothing composites);`
- `letterbox` (function) `kernel/vga_fb.c:610` `* present to repaint chrome plus letterbox (after a desktop redraw or a * view change);`
- `gfx_view_cfg` (function) `kernel/vga_fb.c:645` `static wm_gfxview_config_t gfx_view_cfg(void)` -- Handshake between the present path and the desktop tick, the two painters of the graphics-mode pointer.
- `gfx_covers_screen` (function) `kernel/vga_fb.c:654` `static int gfx_covers_screen(void)` -- Docstring: 1 while a visible fullscreen graphics window owns every * pixel: the terminals, taskbar and dock must not...
- `gfx_keep_save` (function) `kernel/vga_fb.c:660` `static void gfx_keep_save(const volatile uint8_t *src, int kind, int sw, int sh)` -- Docstring: 1 while a visible fullscreen graphics window owns every * pixel: the terminals, taskbar and dock must not...
- `vga_fb_set_gfx_program` (function) `kernel/vga_fb.c:686` `void vga_fb_set_gfx_program(const char *name)`
- `shcmd_base` (function) `kernel/vga_fb.c:705` `static void shcmd_base(const char *cmd, char *out, unsigned long cap)` -- Basename of a shortcut command's program: first token after an optional `run`, then past the last '/'. "run...
- `ci_eq` (function) `kernel/vga_fb.c:722` `static int ci_eq(const char *a, const char *b)`
- `gfx_prog_icon` (function) `kernel/vga_fb.c:735` `static const uint8_t *gfx_prog_icon(void)` -- Icon of the running program via the shortcuts config: whoever composited * last, resolved through its launch command.
- `vga_fb_set_gfx_mode` (function) `kernel/vga_fb.c:748` `void vga_fb_set_gfx_mode(int on)`
- `gfx_view_for` (function) `kernel/vga_fb.c:806` `static int gfx_view_for(int sw, int sh, wm_gfxview_t *v)` -- Docstring: Compute the view for a sw x sh source under the current mode.
- `gfx_view_publish` (function) `kernel/vga_fb.c:818` `static void gfx_view_publish(const wm_gfxview_t *v)` -- mode.
- `gfx_float_frame` (function) `kernel/vga_fb.c:832` `static int gfx_float_frame(wm_gfxview_rect_t *out)` -- Docstring: Floating-mode frame of the current source, used by the * snap and drag math, which move the native...
- `vga_fb_gfx_origin` (function) `kernel/vga_fb.c:848` `void vga_fb_gfx_origin(int *x, int *y)` -- Docstring: Content origin of the graphics window (the point an app * subtracts from SYS_MOUSE coordinates), for the...
- `coordinates` (function) `kernel/vga_fb.c:862` `* windows keep the exact historical coordinates (including outside the * window);`
- `vga_fb_gfx_map_mouse` (function) `kernel/vga_fb.c:865` `void vga_fb_gfx_map_mouse(int *x, int *y)` -- Docstring: Map a desktop pointer into the graphics app's back-buffer space when its view is scaled.
- `vga_fb_gfx_cursor_erase` (function) `kernel/vga_fb.c:880` `static void vga_fb_gfx_cursor_erase(void)` -- Restore the last composite's pointer before the new frame covers it.
- `vga_fb_gfx_cursor_draw` (function) `kernel/vga_fb.c:890` `static void vga_fb_gfx_cursor_draw(void)` -- Clamp the mouse into the framebuffer (the idle loop that normally clamps never runs in graphics mode) and draw the...
- `gfx_transition` (function) `kernel/vga_fb.c:1057` `static void gfx_transition(const wm_gfxview_rect_t *from, int from_titled);`
- `wm_focus_cursor_sync` (function) `kernel/vga_fb.c:1082` `static void wm_focus_cursor_sync(const wm_notify_event_t *e)` -- char eline[WM_ELINE_SZ]; int epos, has_line; int prompted; } termwin_t; static termwin_t twins[WM_MAX_TERMS]; static...
- `wm_emit_focus_moved` (function) `kernel/vga_fb.c:1089` `static void wm_emit_focus_moved(int before, int source)` -- static int wm_term; static int wm_inited; /** Docstring: Single focus event bus owned by the desktop. static...
- `vga_fb_focus_event` (function) `kernel/vga_fb.c:1101` `const wm_notify_event_t *vga_fb_focus_event(void)` -- /** Docstring: Emit one focus event when the id actually moved. static void wm_emit_focus_moved(int before, int...
- `vga_fb_focus_report` (function) `kernel/vga_fb.c:1107` `void vga_fb_focus_report(int before, int source)` -- e.type = WM_NOTIFY_FOCUS; e.old_focus = before; e.new_focus = wm_focus; e.source = source; wm_notify_emit(&wm_bus...
- `tw_park` (function) `kernel/vga_fb.c:1116` `static void tw_park(int i)`
- `tw_unpark` (function) `kernel/vga_fb.c:1146` `static void tw_unpark(int i)`
- `wm_init_once` (function) `kernel/vga_fb.c:1181` `static void wm_init_once(void)`
- `tw_select` (function) `kernel/vga_fb.c:1206` `static void tw_select(int i)` -- twins[k].has_line = 0; twins[k].eline[0] = '\0'; twins[k].epos = 0; twins[k].prompted = 0; } twins[0].lg = lg; if...
- `vga_fb_focus_get` (function) `kernel/vga_fb.c:1218` `int vga_fb_focus_get(void)`
- `vga_fb_nterms_get` (function) `kernel/vga_fb.c:1219` `int vga_fb_nterms_get(void)`
- `wm_snapshot_state` (function) `kernel/vga_fb.c:1222` `static void wm_snapshot_state(wm_focus_state_t *st)` -- if (!twins[i].present) return; if (shell_readline_active()) shell_focus_park(); tw_park(wm_term); wm_focus = i...
- `vga_fb_focus_next` (function) `kernel/vga_fb.c:1235` `void vga_fb_focus_next(void)` -- /** Docstring: Single snapshot of every window for focus decisions. static void wm_snapshot_state(wm_focus_state_t...
- `app` (function) `kernel/vga_fb.c:1276` `* a gfx child spawned from another gfx app (file -> vedit) keeps the * terminal focused, so its keys and wheel keep...`
- `wm_gfx_focus_sync` (function) `kernel/vga_fb.c:1281` `static void wm_gfx_focus_sync(int on)` -- Docstring: Route WM focus with the graphics mode switch.
- `vga_fb_focus_id` (function) `kernel/vga_fb.c:1300` `int vga_fb_focus_id(int id)` -- tw_park(wm_term); wm_focus = WM_FOCUS_GFX; kbd_raw_flush(); wm_emit_focus_moved(before, WM_FOCUS_SRC_MODE); } } else...
- `vga_fb_boot_history_to_active` (function) `kernel/vga_fb.c:1335` `static void vga_fb_boot_history_to_active(void)` -- Docstring: Copy the boot-time history into the terminal that owns the screen after the desktop comes up.
- `content` (function) `kernel/vga_fb.c:1350` `* windows would share content (same prompt/output on both) and a park
 * would alias src == dst. ...`
- `vga_fb_layout_set` (function) `kernel/vga_fb.c:1440` `int vga_fb_layout_set(int mode)` -- twins[1].lg = 0; twins[1].present = 0; twins[1].has_line = 0; twins[1].eline[0] = '\0'; twins[1].epos = 0...
- `vga_fb_layout_cycle` (function) `kernel/vga_fb.c:1451` `void vga_fb_layout_cycle(void)` -- /** Docstring: Tile terminals through the tiling contract, graphics right. /** Docstring: Set active layout mode...
- `vga_fb_layout_get` (function) `kernel/vga_fb.c:1467` `int vga_fb_layout_get(void)` -- if (wm_layout_mode == WM_LAYOUT_TILE) { wm_layout_mode = WM_LAYOUT_BSP; } else if (wm_layout_mode == WM_LAYOUT_BSP)...
- `vga_fb_layout_name` (function) `kernel/vga_fb.c:1473` `const char *vga_fb_layout_name(void)` -- } else { wm_layout_mode = WM_LAYOUT_TILE; } wm_last_n = -1; vga_fb_tile_all(); } /** Docstring: Active layout mode...
- `alone` (function) `kernel/vga_fb.c:1485` `* window alone (an unfocused graphics window minimizes to the taskbar,
 * exactly like the hidden...`
- `vga_fb_list_windows` (function) `kernel/vga_fb.c:1612` `void vga_fb_list_windows(void)`
- `vga_fb_act_empty` (function) `kernel/vga_fb.c:1670` `int vga_fb_act_empty(void)` -- vn ? vn : "floating", gfx_view_valid ? gfx_view.content.x : gfx_win_x, gfx_view_valid ? gfx_view.content.y...
- `vga_fb_note_prompt` (function) `kernel/vga_fb.c:1674` `void vga_fb_note_prompt(void)` -- The shell loop calls note after printing a prompt (it is live in the * focused window) and clear once the line is...
- `vga_fb_clear_prompt` (function) `kernel/vga_fb.c:1679` `void vga_fb_clear_prompt(void)`
- `vga_fb_prompted` (function) `kernel/vga_fb.c:1684` `int vga_fb_prompted(void)`
- `vga_fb_prompt_live` (function) `kernel/vga_fb.c:1693` `int vga_fb_prompt_live(void)` -- 1 when the active line is empty or holds exactly a fresh prompt, so printing another one would stack duplicate...
- `vga_fb_park_line` (function) `kernel/vga_fb.c:1700` `void vga_fb_park_line(const char *b, int p)` -- 1 when the active line is empty or holds exactly a fresh prompt, so printing another one would stack duplicate...
- `vga_fb_unpark_line` (function) `kernel/vga_fb.c:1715` `int vga_fb_unpark_line(char *b, int *p)` -- A fresh prompt parks empty: record no line, so `wm list` does not * claim a half-typed command that never existed....
- `tw_hit` (function) `kernel/vga_fb.c:1730` `static int tw_hit(int i, int mx, int my)` -- termwin_t *t; int k; wm_init_once(); if (wm_focus < 0 || wm_focus >= WM_MAX_TERMS) return 0; t = &twins[wm_focus]...
- `vga_fb_set_gfx_palette` (function) `kernel/vga_fb.c:1836` `void vga_fb_set_gfx_palette(const unsigned char *pal)`
- `fb_pack_idx` (function) `kernel/vga_fb.c:1851` `static unsigned long fb_pack_idx(unsigned idx)` -- --- True-color pixel layer ---- VBE true-color framebuffers store pixels natively as B,G,R(,X) bytes, so the DAC is...
- `fb_write_packed` (function) `kernel/vga_fb.c:1867` `void fb_write_packed(int x, int y, unsigned long rgb)`
- `fb_read_packed` (function) `kernel/vga_fb.c:1887` `unsigned long fb_read_packed(int x, int y)`
- `vga_fb_read_rgb` (function) `kernel/vga_fb.c:1911` `unsigned long vga_fb_read_rgb(int x, int y)`
- `fb_write_row_packed` (function) `kernel/vga_fb.c:1916` `void fb_write_row_packed(int x, int y, const unsigned int *src, int n)` -- Docstring: Write n packed pixels (0x00RRGGBB, or raw indices in 8-bit mode) to row y from column x, clipped once.
- `fb_read_row_packed` (function) `kernel/vga_fb.c:1946` `void fb_read_row_packed(int x, int y, unsigned int *dst, int n)` -- Docstring: Read n packed pixels of row y from column x into dst, * clipped once; pixels outside the screen read as 0.
- `fb_fill_run` (function) `kernel/vga_fb.c:1968` `static void fb_fill_run(int x, int y, int n, unsigned long px)` -- int xx = x + i; if (xx < 0 || xx >= fb_width) continue; if (fb_bpp == 32) { dst[i] = *(volatile unsigned int *)(p +...
- `wall_level` (function) `kernel/vga_fb.c:1994` `static int wall_level(int v)` -- for (i = 0; i < n; i++) { q[0] = (uint8_t)(px & 0xFF); q[1] = (uint8_t)((px >> 8) & 0xFF); q[2] = (uint8_t)((px >>...
- `vga_fb_set_palette` (function) `kernel/vga_fb.c:2003` `static void vga_fb_set_palette(void)`
- `fb_glyph` (function) `kernel/vga_fb.c:2056` `static const uint8_t *fb_glyph(unsigned char c)` -- Resolve one byte to its 8-row glyph: ASCII through font8x8, Spanish Latin-1 through the table above, anything else...
- `vga_fb_pixel` (function) `kernel/vga_fb.c:2077` `void vga_fb_pixel(int x, int y, uint8_t color)` -- case 0xAC: return glyph_notsign; case 0xB4: return glyph_acute; case 0xB7: return glyph_middot; case 0xBA: return...
- `vga_fb_clear` (function) `kernel/vga_fb.c:2087` `void vga_fb_clear(void)` -- } } /* ---- Drawing primitives ---- void vga_fb_pixel(int x, int y, uint8_t color) { if (fb_bpp == 8) { if (x >= 0...
- `vga_fb_rect` (function) `kernel/vga_fb.c:2097` `void vga_fb_rect(int x, int y, int w, int h, uint8_t color)` -- Docstring: Solid rectangle: the color resolves once, every row is one * clipped run fill instead of a per-pixel...
- `vga_fb_pixel_rgb` (function) `kernel/vga_fb.c:2112` `void vga_fb_pixel_rgb(int x, int y, uint8_t r, uint8_t g, uint8_t b)` -- Direct RGB pixel: full color depth in true-color modes, best-effort quantization in 8-bit mode.
- `vga_fb_rect_rgb` (function) `kernel/vga_fb.c:2121` `void vga_fb_rect_rgb(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b)`
- `vga_fb_char` (function) `kernel/vga_fb.c:2128` `void vga_fb_char(int col, int row, char c, uint8_t fg, uint8_t bg)`
- `vga_fb_str` (function) `kernel/vga_fb.c:2154` `void vga_fb_str(int col, int row, const char *s, uint8_t fg, uint8_t bg)`
- `text_px` (function) `kernel/vga_fb.c:2169` `static void text_px(int px, int py, const char *s, uint8_t fg, uint8_t bg)` -- Blit a text string at an absolute pixel position.
- `wm_draw_buttons` (function) `kernel/vga_fb.c:2198` `static void wm_draw_buttons(int px, int py, int win_w, uint8_t fg, uint8_t bg)` -- --- Window controls ---- Three glyph buttons at the right end of a window's title bar: minimize (_), maximize...
- `chrome_color` (function) `kernel/vga_fb.c:2243` `static unsigned long chrome_color(unsigned idx)` -- Docstring: Profile card geometry: padding, avatar ring width, margin * from the screen corner and the name column...
- `chrome_title_strip` (function) `kernel/vga_fb.c:2283` `static int chrome_title_strip(int x, int y, int w, int focused)` -- Docstring: Gradient title strip for a window of width w.
- `chrome_win_rect` (function) `kernel/vga_fb.c:2310` `static int chrome_win_rect(int id, int *x, int *y, int *w, int *h)` -- Docstring: Last composed rect of terminal window id; 0 when the window * was never composed or id is out of range.
- `chrome_corner_origin` (function) `kernel/vga_fb.c:2322` `static void chrome_corner_origin(const chrome_win_t *c, int k, int *ox, int *oy)` -- Docstring: Last composed rect of terminal window id; 0 when the window * was never composed or id is out of range....
- `chrome_wins_reset` (function) `kernel/vga_fb.c:2330` `static void chrome_wins_reset(void)` -- w = chrome_wins[id].w; h = chrome_wins[id].h; return 1; } /** Docstring: Outer pixel of corner k of a window rect....
- `chrome_win_capture` (function) `kernel/vga_fb.c:2341` `static void chrome_win_capture(int idx, int x, int y, int w, int h)` -- Docstring: Save the pixels under the corners of window slot idx before * it paints.
- `chrome_win_cut` (function) `kernel/vga_fb.c:2371` `static void chrome_win_cut(const chrome_win_t *c, int k)` -- Docstring: Cut corner k of a slot with the anti-aliased arc, blending the painted window pixel over the saved...
- `chrome_win_live` (function) `kernel/vga_fb.c:2392` `static chrome_win_t *chrome_win_live(void)` -- Docstring: Slot whose window origin and width match the live terminal, * or null when the window was not captured by...
- `chrome_win_recut_bottom` (function) `kernel/vga_fb.c:2407` `static void chrome_win_recut_bottom(int corner)` -- Docstring: Re-cut a bottom corner after its pixels were repainted by an incremental update: the last-row first cell...
- `chrome_tint_capture` (function) `kernel/vga_fb.c:2421` `static void chrome_tint_capture(int idx, int x, int y, int w, int h)` -- Docstring: Build the tinted backdrop of window slot idx over its content rect, from what the composition has painted...
- `chrome_tint_live` (function) `kernel/vga_fb.c:2453` `static const chrome_tint_t *chrome_tint_live(void)` -- Docstring: Tinted backdrop whose rect is exactly the live terminal's * content rect, or null when the last...
- `chrome_term_fill` (function) `kernel/vga_fb.c:2467` `static int chrome_term_fill(void)` -- Docstring: Paint the live terminal's content rect from its tinted * backdrop.
- `chrome_panel_coverage` (function) `kernel/vga_fb.c:2483` `static int chrome_panel_coverage(int xx, int yy, int x, int y, int w, int h)` -- Docstring: Coverage of pixel (xx,yy) of a w by h panel at (x,y) with all * four corners rounded by the chrome radius.
- `chrome_glass` (function) `kernel/vga_fb.c:2496` `static void chrome_glass(int x, int y, int w, int h)` -- Docstring: Translucent rounded glass panel over whatever is already painted: the dock tint blends over the backdrop...
- `chrome_disc` (function) `kernel/vga_fb.c:2528` `static void chrome_disc(int cx2, int cy2, int r2, unsigned long color, int alpha)` -- Docstring: Anti-aliased filled disc of radius r (in 1/2 pixel units * of the pixel centre) blended over the target...
- `chrome_traffic_lights` (function) `kernel/vga_fb.c:2550` `static int chrome_traffic_lights(int bx, int by)` -- Docstring: macOS-style window buttons in the existing three 8x8 hit cells: minimize amber, maximize green, close red.
- `chrome_glow` (function) `kernel/vga_fb.c:2566` `static void chrome_glow(int x, int y, int w, int h)` -- static const unsigned long lights[3] = { 0xFFBD2EUL, 0x27C93FUL, 0xFF5F56UL }; int i; if (fb_bpp == 8) return 0; for...
- `chrome_profile_card` (function) `kernel/vga_fb.c:2586` `static void chrome_profile_card(void)` -- Docstring: Profile card in the top-right corner: glass panel with a soft shadow, the circular avatar with a bright...
- `wm_buttons_hit` (function) `kernel/vga_fb.c:2616` `static int wm_buttons_hit(int mx, int my, int win_x, int win_y, int win_w)` -- for (j = 0; j < AVATAR_SIZE; j++) for (i = 0; i < AVATAR_SIZE; i++) { int cov = wm_chrome_disc_coverage(AVATAR_SIZE...
- `wm_close_pending` (function) `kernel/vga_fb.c:2631` `int wm_close_pending(void)` -- Close request bridge: the syscall dispatcher polls this so a graphics * program's next syscall exits it on the...
- `wm_clear_close` (function) `kernel/vga_fb.c:2632` `void wm_clear_close(void)`
- `wm_gfx_mode_active` (function) `kernel/vga_fb.c:2633` `int wm_gfx_mode_active(void)`
- `vga_fb_ps2_owner` (function) `kernel/vga_fb.c:2636` `int vga_fb_ps2_owner(int pid)` -- Close request bridge: the syscall dispatcher polls this so a graphics * program's next syscall exits it on the...
- `taskbar` (function) `kernel/vga_fb.c:2656` `* minimize hides the app to the taskbar (it never closes it), maximize
 * toggles true fullscreen...`
- `directly` (function) `kernel/vga_fb.c:2704` `* RGB sources pack directly (quantized to the wallpaper cube in 8-bit). */
static void gfx_scale_...`
- `gfx_letterbox` (function) `kernel/vga_fb.c:2809` `static void gfx_letterbox(const wm_gfxview_t *v)` -- Docstring: Clear the frame area the content does not cover (the * letterbox bars of a tiled or fullscreen view) to...
- `gfx_title` (function) `kernel/vga_fb.c:2828` `static void gfx_title(const wm_gfxview_t *v)` -- int ah = v->frame.h - v->title_h; const wm_gfxview_rect_t *c = &v->content; if (aw <= 0 || ah <= 0) return; if (c->y...
- `gfx_compose` (function) `kernel/vga_fb.c:2842` `static void gfx_compose(const volatile uint8_t *src, int kind, int sw, int sh,
                  ...` -- Docstring: Compose one graphics frame at a view into the render target: * title, letterbox (when full is set) and...
- `gfx_present` (function) `kernel/vga_fb.c:2910` `static void gfx_present(const volatile uint8_t *bb, int kind, int sw, int sh)` -- Docstring: Present under the pointer handshake: wait out a desktop tick that is moving the sprite, composite, then...
- `gfx_cursor_follow_idle` (function) `kernel/vga_fb.c:2926` `static void gfx_cursor_follow_idle(void)` -- Docstring: Move the graphics-mode pointer from the desktop tick while the app is idle.
- `vga_fb_blit_gfx_window` (function) `kernel/vga_fb.c:2939` `void vga_fb_blit_gfx_window(void)`
- `vga_fb_blit_nk_window` (function) `kernel/vga_fb.c:2948` `void vga_fb_blit_nk_window(void)`
- `vga_fb_blit_nk_rgb_window` (function) `kernel/vga_fb.c:2954` `void vga_fb_blit_nk_rgb_window(void)` -- Composite the Nuklear RGB back-buffer (NK_RGB_ADDR, NK_W x NK_H x 3 bytes) * through the same present path as the...
- `term_recalc` (function) `kernel/vga_fb.c:2963` `static void term_recalc(void)`
- `draw_title_win` (function) `kernel/vga_fb.c:2989` `static void draw_title_win(int idx, int focused)` -- Preserve the current window position, clamping it into range so a * drag or Ctrl+arrow move is not undone by the...
- `taskbar_layout` (function) `kernel/vga_fb.c:3022` `static void taskbar_layout(void)`
- `draw_speaker_icon` (function) `kernel/vga_fb.c:3053` `static void draw_speaker_icon(int x, int y, uint8_t color)` -- Running-app button right after it: mini icon + title while a graphics program owns the display.
- `taskbar_render` (function) `kernel/vga_fb.c:3062` `static void taskbar_render(void)`
- `title` (function) `kernel/vga_fb.c:3072` `* 8px row plus its title (bright when focused). The hint line * starts after it instead of underneath. */ const...`
- `taskbar_tick` (function) `kernel/vga_fb.c:3141` `static void taskbar_tick(void)` -- Redraw the clock only when the wall-clock second changes.
- `vga_fb_theme_name` (function) `kernel/vga_fb.c:3157` `int vga_fb_theme_name(char *dst, int cap)` -- Docstring: Active Nuklear theme name for the taskbar widget.
- `taskbar_theme_cycle` (function) `kernel/vga_fb.c:3178` `static void taskbar_theme_cycle(void)` -- Cycle the active theme to the next etc/themes/ entry (ramdisk).
- `taskbar_handle_click` (function) `kernel/vga_fb.c:3218` `static void taskbar_handle_click(int mx, int my)` -- Click handling for the keyboard widget, the speaker icon and -/+ buttons, plus the restore button that reappears...
- `draw_scrollbar` (function) `kernel/vga_fb.c:3278` `static void draw_scrollbar(void)` -- return; } if (mx >= tb_minus_x && mx < tb_minus_x + TASKBAR_BTN_W) { v = pcspk_get_volume(); pcspk_set_volume(v >...
- `render_blank_row` (function) `kernel/vga_fb.c:3314` `static void render_blank_row(int vrow)` -- Blank one viewport row: every cell is repainted with the terminal background. vga_fb_str with an empty string would...
- `render_row` (function) `kernel/vga_fb.c:3324` `static void render_row(int vrow, int abs)` -- Render one display row at viewport row `vrow` for the absolute display row `abs`.
- `term_render` (function) `kernel/vga_fb.c:3359` `static void term_render(void)`
- `buffer` (function) `kernel/vga_fb.c:3375` `* owns the buffer (indices reset, render reads an empty ring). */
void term_clear(void)`
- `term_render_active` (function) `kernel/vga_fb.c:3392` `static void term_render_active(void)` -- Repaint only the bottom region that a live edit touches: from the active line's first visible display row to the...
- `line` (function) `kernel/vga_fb.c:3435` `* display stale bytes left over from a longer previous line (e.g. the prompt
 * would show the ta...`
- `escapes` (function) `kernel/vga_fb.c:3444` `* swallowing them here keeps the escapes (which the serial side needs)
     * from printing as li...`
- `vga_fb_puts_term` (function) `kernel/vga_fb.c:3501` `void vga_fb_puts_term(const char *s)`
- `vga_fb_text_cursor` (function) `kernel/vga_fb.c:3507` `void vga_fb_text_cursor(int col)` -- Show the text cursor at character column `col` of the active line, or hide * it with a negative column.
- `vga_fb_hide_text_cursor` (function) `kernel/vga_fb.c:3515` `void vga_fb_hide_text_cursor(void)` -- Show the text cursor at character column `col` of the active line, or hide * it with a negative column.
- `jelly_cancel` (function) `kernel/vga_fb.c:3568` `static void jelly_cancel(void)` -- enum { JELLY_NONE = 0, JELLY_TERM = 1, JELLY_GFX = 2 }; static wm_jelly_config_t jelly_cfg =...
- `jelly_begin` (function) `kernel/vga_fb.c:3577` `static void jelly_begin(int kind, int gx, int gy)` -- Docstring: Start wobbling the dragged window (kind, grab point inside * the window).
- `jelly_rect` (function) `kernel/vga_fb.c:3589` `static int jelly_rect(int *x, int *y, int *w, int *h)` -- Docstring: Start wobbling the dragged window (kind, grab point inside * the window).
- `jelly_kick` (function) `kernel/vga_fb.c:3612` `static void jelly_kick(int mx, int my)` -- return 1; } if (jelly_kind == JELLY_GFX && vga_fb_gfx_mode && !gfx_hidden && gfx_view_valid && gfx_view_mode !=...
- `jelly_live` (function) `kernel/vga_fb.c:3621` `static int jelly_live(void)` -- } return 0; } /** Docstring: The pointer moved the window by (mx, my): shove the mesh. static void jelly_kick(int...
- `jelly_arm` (function) `kernel/vga_fb.c:3629` `static void jelly_arm(void)` -- Docstring: Record the wobble band of a finished outermost composition so the present can warp it.
- `jelly_shadow_px` (function) `kernel/vga_fb.c:3655` `static unsigned int jelly_shadow_px(int x, int y)` -- jelly_bx1 = jelly_rx + jelly_rw + reach; jelly_by0 = jelly_ry - reach; jelly_by1 = jelly_ry + jelly_rh + reach; if...
- `jelly_put_row` (function) `kernel/vga_fb.c:3665` `static void jelly_put_row(int x, int y, const unsigned int *src, int n)` -- jelly_armed = 1; } /** Docstring: Packed pixel of the shadow at (x, y), 24 and 32-bit only. static unsigned int...
- `jelly_warp_band` (function) `kernel/vga_fb.c:3687` `static void jelly_warp_band(void)` -- Docstring: Write the wobble band to the framebuffer: every pixel takes the shadow pixel the mesh displaces onto it...
- `jelly_present` (function) `kernel/vga_fb.c:3720` `static void jelly_present(void)` -- Docstring: Present the shadow, warping the armed band.
- `jelly_try_present` (function) `kernel/vga_fb.c:3744` `static int jelly_try_present(void)` -- Docstring: Present through the mesh when a band is armed; 1 when the * frame was presented here.
- `jelly_advance` (function) `kernel/vga_fb.c:3755` `static void jelly_advance(void)` -- Docstring: Advance the spring at most once per desktop tick, in * JELLY_SUBSTEPS finer steps so the wobble stays...
- `jelly_tick` (function) `kernel/vga_fb.c:3768` `static void jelly_tick(int held)` -- Docstring: Desktop-tick driver.
- `vga_fb_draw_desktop` (function) `kernel/vga_fb.c:3791` `void vga_fb_draw_desktop(void)` -- Docstring: Repaint the desktop through the shared render plan.
- `gfx_view_in_rect` (function) `kernel/vga_fb.c:3903` `static void gfx_view_in_rect(const wm_gfxview_rect_t *r, int titled, wm_gfxview_t *v)` -- Docstring: View of the persistent source inside an arbitrary frame, * titled when the frame is tall enough to carry...
- `gfx_animate` (function) `kernel/vga_fb.c:3922` `static void gfx_animate(const wm_gfxview_rect_t *from, const wm_gfxview_rect_t *to,
             ...` -- Docstring: Glide the persistent source frame from one rect to * another over the desktop, then settle with a plain...
- `gfx_taskbar_rect` (function) `kernel/vga_fb.c:3972` `static void gfx_taskbar_rect(wm_gfxview_rect_t *r)` -- fb_tgt = fb_shadow; gfx_compose(gfx_keep, gfx_keep_kind, gfx_keep_sw, gfx_keep_sh, &v, 0); fb_tgt = 0...
- `gfx_drop_focus` (function) `kernel/vga_fb.c:4009` `static void gfx_drop_focus(int source)` -- Docstring: Hand keyboard focus to the graphics window without a * redraw (callers repaint once afterwards). static...
- `from` (function) `kernel/vga_fb.c:4020` `* leaving returns to the view it came from (floating or tiled). Returns
 * 0 on success, -1 witho...`
- `vga_fb_gfx_set_hidden` (function) `kernel/vga_fb.c:4054` `int vga_fb_gfx_set_hidden(int hide)` -- Docstring: Minimize (hide) or restore the graphics window.
- `vga_fb_gfx_view_name` (function) `kernel/vga_fb.c:4104` `const char *vga_fb_gfx_view_name(void)` -- gfx_hidden = 0; gfx_take_focus(WM_FOCUS_SRC_TASKBAR); wm_last_n = -1; if (fx_old) { gfx_frame_dirty = 1...
- `term_toggle_fullscreen` (function) `kernel/vga_fb.c:4116` `static void term_toggle_fullscreen(void)` -- /** Docstring: Graphics view state for `wm state`/`wm list`. const char *vga_fb_gfx_view_name(void) { const char *n...
- `vga_fb_toggle_fullscreen` (function) `kernel/vga_fb.c:4128` `void vga_fb_toggle_fullscreen(void)` -- Docstring: Toggle fullscreen on the focused window: the graphics * window scales to the whole display, a terminal...
- `term_toggle_minimize` (function) `kernel/vga_fb.c:4139` `static void term_toggle_minimize(void)` -- Minimize/restore the terminal window.
- `vga_fb_toggle_minimize` (function) `kernel/vga_fb.c:4161` `void vga_fb_toggle_minimize(void)` -- fx_plan_genie(term_px_x, term_px_y, term_px_w + SCROLLBAR_W, term_px_h + FONT_H, tx, ty, 0); fx_old =...
- `vga_fb_is_minimized` (function) `kernel/vga_fb.c:4169` `int vga_fb_is_minimized(void)`
- `vga_fb_is_fullscreen` (function) `kernel/vga_fb.c:4170` `int vga_fb_is_fullscreen(void)`
- `gfx_snap` (function) `kernel/vga_fb.c:4175` `static void gfx_snap(int zone)` -- Snap the focused graphics window into a screen region (halves place it against that edge, quadrants into that...
- `term_close_default` (function) `kernel/vga_fb.c:4208` `static void term_close_default(void)` -- Docstring: Terminal close button: restore the default geometry (the * shell cannot be closed).
- `vga_fb_close_active` (function) `kernel/vga_fb.c:4224` `int vga_fb_close_active(void)` -- Close the focused window.
- `vga_fb_move_terminal` (function) `kernel/vga_fb.c:4238` `void vga_fb_move_terminal(int dx, int dy)`
- `term_max_cols` (function) `kernel/vga_fb.c:4283` `static int term_max_cols(void)` -- --- Tiling window operations (Alt = WM modifier) ---- Snap places the window in a screen half or quadrant and sizes...
- `term_max_rows` (function) `kernel/vga_fb.c:4287` `static int term_max_rows(void)`
- `term_finish_layout` (function) `kernel/vga_fb.c:4292` `static void term_finish_layout(void)`
- `vga_fb_snap_window` (function) `kernel/vga_fb.c:4298` `void vga_fb_snap_window(int zone)`
- `vga_fb_resize` (function) `kernel/vga_fb.c:4326` `void vga_fb_resize(int dcols, int drows)`
- `vga_fb_reset_default` (function) `kernel/vga_fb.c:4346` `void vga_fb_reset_default(void)` -- int ncol = term_sz_cols + dcols; int nrow = term_sz_rows + drows; if (ncol < 1) ncol = 1; if (nrow < 1) nrow = 1; if...
- `wallpaper_ensure` (function) `kernel/vga_fb.c:4403` `static void wallpaper_ensure(void)`
- `wallpaper_usable` (function) `kernel/vga_fb.c:4455` `static int wallpaper_usable(void)` -- d[2] = px[0]; if (bpx == 4) d[3] = 0; } } } stbi_image_free(img); wall_native = cache; wall_cw = fb_width; wall_ch =...
- `wallpaper_draw` (function) `kernel/vga_fb.c:4460` `static void wallpaper_draw(void)`
- `wallpaper_packed` (function) `kernel/vga_fb.c:4476` `static int wallpaper_packed(int x, int y, unsigned int *out)` -- Docstring: Packed 0x00RRGGBB wallpaper pixel at (x, y); 0 when the * cache is unusable, the coordinate is off screen...
- `pipe_field` (function) `kernel/vga_fb.c:4498` `static const char *pipe_field(const char *line, int idx, char *buf, int buflen)` -- --- Desktop shortcut icons ---- Shortcuts are defined in etc/shortcuts on the ramdisk, one per line...
- `icon_nearest` (function) `kernel/vga_fb.c:4516` `static int icon_nearest(int r, int g, int b)` -- Nearest entry in the 16-colour icon palette (squared RGB distance, * integer-only: at most 3*255*255 per entry, far...
- `icon_embedded` (function) `kernel/vga_fb.c:4532` `static const uint8_t *icon_embedded(const char *name)` -- for (i = 0; i < ICON_PAL_SIZE; i++) { int dr = r - icon_pal[i][0]; int dg = g - icon_pal[i][1]; int db = b...
- `icon_decode` (function) `kernel/vga_fb.c:4552` `static const uint8_t *icon_decode(const char *path)` -- Decode a shortcut's PNG to raw 32x32 RGBA pixels.
- `icon_embedded_rgba` (function) `kernel/vga_fb.c:4586` `static const uint8_t *icon_embedded_rgba(const uint8_t *idx)` -- Expand an embedded index icon (desktop_icons.h, transparent 0) to RGBA through the icon palette, so fallback art...
- `dock_label_px` (function) `kernel/vga_fb.c:4614` `static int dock_label_px(const struct desktop_shortcut *sc)` -- Width of the longest shortcut label in pixels (cached after load).
- `shortcuts_layout` (function) `kernel/vga_fb.c:4623` `static void shortcuts_layout(void)` -- Dock layout: one centred row just above the taskbar.
- `shortcut_cell_left` (function) `kernel/vga_fb.c:4641` `static int shortcut_cell_left(int i)` -- dock_h = ICON_H + DOCK_LABEL_GAP + ICON_LABEL_H + 2 * DOCK_PAD_Y; x0 = (fb_width - dock_w) / 2; if (x0 < 0) x0 = 0...
- `desktop_shortcuts_load` (function) `kernel/vga_fb.c:4648` `void desktop_shortcuts_load(void)`
- `shortcut_draw_scaled` (function) `kernel/vga_fb.c:4704` `static void shortcut_draw_scaled(const struct desktop_shortcut *sc,
                             ...` -- Blit one shortcut icon scaled to dw x dh at (dx, dy), nearest neighbour from the cached 32x32 RGBA source.
- `dock_hover_index` (function) `kernel/vga_fb.c:4729` `static int dock_hover_index(int mx, int my)` -- Index of the shortcut column under (mx, my), or -1.
- `dock_bounce_counts` (function) `kernel/vga_fb.c:4756` `void dock_bounce_counts(unsigned long *kicks, unsigned long *paints)`
- `dock_click_count` (function) `kernel/vga_fb.c:4766` `void dock_click_count(unsigned long *edges)`
- `dock_bounce_elapsed` (function) `kernel/vga_fb.c:4772` `static unsigned long dock_bounce_elapsed(void)` -- Ticks elapsed since the bounce click, capped so the subtraction can * never wrap on a late read.
- `dock_bounce_live` (function) `kernel/vga_fb.c:4780` `static int dock_bounce_live(void)` -- Ticks elapsed since the bounce click, capped so the subtraction can * never wrap on a late read. static unsigned...
- `dock_pending_active` (function) `kernel/vga_fb.c:4830` `int dock_pending_active(void)`
- `dock_paint_icons` (function) `kernel/vga_fb.c:4838` `static void dock_paint_icons(int hover)` -- Paint every shortcut icon and label at the given hover sizes.
- `dock_paint_backing` (function) `kernel/vga_fb.c:4880` `static void dock_paint_backing(int x0, int y0, int dock_w, int dock_h, int with_shadow)` -- Docstring: Paint the dock backing: soft shadow first when requested (the hover repaint skips it, it lies outside the...
- `desktop_shortcuts_draw` (function) `kernel/vga_fb.c:4887` `void desktop_shortcuts_draw(void)`
- `wallpaper_rect` (function) `kernel/vga_fb.c:4907` `static void wallpaper_rect(int x0, int y0, int w, int h)` -- Paint one wallpaper rectangle from the cache (solid fill when the cache * is absent or stale): the strip-erase...
- `dock_paint_hover` (function) `kernel/vga_fb.c:4938` `static void dock_paint_hover(int hover)` -- Hover repaint without the fullscreen flash: erase only the dock strip (bar plus the overflow the magnified icons...
- `command` (function) `kernel/vga_fb.c:4962` `* its launch command (config-driven, covers apps that never set a window * title);`
- `gfx_task_icon` (function) `kernel/vga_fb.c:4967` `static const uint8_t *gfx_task_icon(void)` -- Icon for the taskbar running-app button.
- `desktop_shortcuts_hit_test` (function) `kernel/vga_fb.c:4988` `const char *desktop_shortcuts_hit_test(int mx, int my)`
- `mouse_focus_topmost` (function) `kernel/vga_fb.c:5002` `static int mouse_focus_topmost(int mx, int my)` -- const char *desktop_shortcuts_hit_test(int mx, int my) { shortcuts_layout(); for (int i = 0; i < shortcut_count...
- `mouse_apply_wheel` (function) `kernel/vga_fb.c:5028` `static void mouse_apply_wheel(int wheel, int step)` -- if (!twins[f].present) continue; if (tw_hit(f, mx, my)) { if (f == wm_focus) return 0; before = wm_focus...
- `pointer` (function) `kernel/vga_fb.c:5049` `* tiled window floats it at native size under the pointer (the grab point * keeps its relative position along the...`
- `mouse_drag_gfx` (function) `kernel/vga_fb.c:5052` `static void mouse_drag_gfx(const wm_geom_config_t *gcfg, int mx, int my)` -- Docstring: Title-bar drag of the graphics window.
- `mouse_drag_term` (function) `kernel/vga_fb.c:5109` `static void mouse_drag_term(const wm_geom_config_t *gcfg, int win_w, int mx, int my, int gfx_cursor)` -- Docstring: Title-bar drag of the focused terminal window.
- `mouse_scrollbar` (function) `kernel/vga_fb.c:5132` `static void mouse_scrollbar(const wm_geom_config_t *gcfg, int mx, int my)` -- wm_grab_cx = (mx - term_px_x) / FONT_W; } } else { wm_dragging = 0; } if (wm_dragging) { vga_fb_drag_terminal(mx...
- `vga_fb_wait_tick` (function) `kernel/vga_fb.c:5161` `void vga_fb_wait_tick(void)` -- Docstring: Drive the desktop from a kernel wait loop.
- `vga_fb_mouse_tick` (function) `kernel/vga_fb.c:5170` `void vga_fb_mouse_tick(void)` -- timer ISR drives it only for the pid-0 exec frame (user_program_active) and the shell's input loop is not running...
- `path` (function) `kernel/vga_fb.c:5181` `* present path (blit_gfx_buf) is the sole cursor painter. The tick * used to share the sprite state with it and...`
- `state` (function) `kernel/vga_fb.c:5295` `* ignores the button state (the arming press is consumed) and settles
     * once on expiry, so t...`
- `vga_fb_mouse_init` (function) `kernel/vga_fb.c:5373` `void vga_fb_mouse_init(void)`
- `vga_fb_history_page` (function) `kernel/vga_fb.c:5427` `void vga_fb_history_page(int dir)` -- Docstring: Page the terminal history by one screen (dir -1 up, +1 down).
- `vga_fb_init` (function) `kernel/vga_fb.c:5439` `void vga_fb_init(void)`

## kernel/vga_fx.c
Depends on: `headers/vga_fb.h`, `headers/vga_fx.h`
- `vga_fx_set_enabled` (function) `kernel/vga_fx.c:27` `void vga_fx_set_enabled(int on)`
- `vga_fx_enabled` (function) `kernel/vga_fx.c:32` `int vga_fx_enabled(void)`
- `fx_wait_until` (function) `kernel/vga_fx.c:40` `static void fx_wait_until(unsigned long deadline)` -- Deadline pacing over the PIT-calibrated TSC clock.
- `vga_fx_snap_rect` (function) `kernel/vga_fx.c:46` `unsigned int *vga_fx_snap_rect(int x, int y, int w, int h)`
- `vga_fx_restore_rect` (function) `kernel/vga_fx.c:68` `void vga_fx_restore_rect(int x, int y, int w, int h, const unsigned int *buf)`
- `vga_fx_free` (function) `kernel/vga_fx.c:82` `void vga_fx_free(unsigned int *buf)`
- `once` (function) `kernel/vga_fx.c:95` `* once (prev[] tracks the revealed frontier per column), then the final
 * restore guarantees the...`
- `vga_fx_melt_rect` (function) `kernel/vga_fx.c:155` `void vga_fx_melt_rect(int x, int y, int w, int h,
    const unsigned int *oldb, const unsigned in...` -- Drive one old->new melt.
- `vga_fx_melt_from_black` (function) `kernel/vga_fx.c:164` `void vga_fx_melt_from_black(int x, int y, int w, int h, const unsigned int *newb)` -- Boot melt: the framebuffer is already cleared to black on entry, so no * old snapshot is needed; the new frame...

## mcp/mcp_dbg_driver.py
Depends on: `kernel/time.c`
- `Client.__init__` (method) `mcp/mcp_dbg_driver.py:16` `def __init__(self)`
- `Client.request` (method) `mcp/mcp_dbg_driver.py:28` `def request(self, method, params)`
- `Client.tool` (method) `mcp/mcp_dbg_driver.py:46` `def tool(self, name, params)`
- `Client.close` (method) `mcp/mcp_dbg_driver.py:54` `def close(self)`
- `main` (function) `mcp/mcp_dbg_driver.py:64` `def main()`

## mcp/mcp_dogfood.py
Depends on: `kernel/time.c`
- `Client.__init__` (method) `mcp/mcp_dogfood.py:20` `def __init__(self, addons_dir)`
- `Client.request` (method) `mcp/mcp_dogfood.py:40` `def request(self, method, params)`
- `Client.tool` (method) `mcp/mcp_dogfood.py:58` `def tool(self, name, params)`
- `Client.close` (method) `mcp/mcp_dogfood.py:68` `def close(self)`
- `main` (function) `mcp/mcp_dogfood.py:78` `def main()`

## mcp/minios_addons.py
Depends on: `kernel/time.c`
Imported by: `mcp/minios_mcp.py`
- `parse_addon_yaml` (function) `mcp/minios_addons.py:73` `def parse_addon_yaml(text)` -- Parse the strict YAML subset.
- `fail` (function) `mcp/minios_addons.py:85` `def fail(lineno, why)`
- `validate_addon` (function) `mcp/minios_addons.py:205` `def validate_addon(addon, source)` -- Check bounds and character sets.
- `validate_addon_path` (function) `mcp/minios_addons.py:295` `def validate_addon_path(path)` -- dst paths live on the ramdisk: relative, no '..', bounded charset.
- `validate_shell_line` (function) `mcp/minios_addons.py:309` `def validate_shell_line(line)` -- Build/verify lines are single printable-ASCII shell commands.
- `load_addons_dir` (function) `mcp/minios_addons.py:323` `def load_addons_dir(addons_dir)` -- Load every addon yaml; each entry is a dict or an error string.
- `split_for_editor` (function) `mcp/minios_addons.py:347` `def split_for_editor(text)` -- Split a source into editor-sized chunks.
- `exit_code_of` (function) `mcp/minios_addons.py:372` `def exit_code_of(text)`
- `AddonState.__init__` (method) `mcp/minios_addons.py:380` `def __init__(self, path)`
- `AddonState.load` (method) `mcp/minios_addons.py:383` `def load(self)`
- `AddonState.save` (method) `mcp/minios_addons.py:393` `def save(self, addons)`
- `install_addon` (function) `mcp/minios_addons.py:401` `def install_addon(session, addon, cfg)` -- Install one validated addon into the booted MiniOS session.

## mcp/minios_mcp.py
Depends on: `kernel/time.c`, `mcp/minios_addons.py`
- `env_config` (function) `mcp/minios_mcp.py:71` `def env_config()` -- Resolve the configuration: defaults overridden by the environment.
- `clamp_timeout` (function) `mcp/minios_mcp.py:89` `def clamp_timeout(ms)` -- Clamp a requested wait to the bounded timeout range.
- `validate_path` (function) `mcp/minios_mcp.py:102` `def validate_path(name)` -- Reject file names the ramdisk or the shell would mishandle.
- `validate_content` (function) `mcp/minios_mcp.py:118` `def validate_content(text)` -- Reject lines the kernel readline cannot carry (printable ASCII).
- `RPCError.__init__` (method) `mcp/minios_mcp.py:140` `def __init__(self, code, message)`
- `LogBuffer.__init__` (method) `mcp/minios_mcp.py:149` `def __init__(self, cap)`
- `LogBuffer.append` (method) `mcp/minios_mcp.py:155` `def append(self, data)`
- `LogBuffer.bytes_from` (method) `mcp/minios_mcp.py:163` `def bytes_from(self, pos)`
- `LogBuffer.text_from` (method) `mcp/minios_mcp.py:168` `def text_from(self, pos, end)`
- `LogBuffer.find` (method) `mcp/minios_mcp.py:175` `def find(self, marker, start)`
- `LogBuffer.wait_for` (method) `mcp/minios_mcp.py:179` `def wait_for(self, marker, start, timeout_ms)` -- Block until marker appears at or after start; return position.
- `LogBuffer.wait_for_any` (method) `mcp/minios_mcp.py:192` `def wait_for_any(self, markers, start, timeout_ms)` -- Block until any of markers appears at or after start; return the earliest position found, or -1 when the timeout...
- `MiniOSSession.__init__` (method) `mcp/minios_mcp.py:219` `def __init__(self, cfg)`
- `MiniOSSession.booted` (method) `mcp/minios_mcp.py:230` `def booted(self)`
- `MiniOSSession.status` (method) `mcp/minios_mcp.py:233` `def status(self)`
- `MiniOSSession.boot` (method) `mcp/minios_mcp.py:284` `def boot(self, timeout_ms)`
- `MiniOSSession.send` (method) `mcp/minios_mcp.py:356` `def send(self, line, timeout_ms)`
- `MiniOSSession.expect` (method) `mcp/minios_mcp.py:367` `def expect(self, marker, timeout_ms)`
- `MiniOSSession.snapshot` (method) `mcp/minios_mcp.py:381` `def snapshot(self, max_bytes)`
- `MiniOSSession.run_test` (method) `mcp/minios_mcp.py:391` `def run_test(self, commands, expect, refute, timeout_ms)` -- Run a generic scenario: send a list of shell commands, then assert that each expected marker appears (and each...
- `MiniOSSession.cat` (method) `mcp/minios_mcp.py:447` `def cat(self, path)`
- `MiniOSSession.run_python` (method) `mcp/minios_mcp.py:453` `def run_python(self, script, args, timeout_ms)` -- Run a MicroPython script (or `-c` code) inside MiniOS and return its output, including the `exit code: N` line.
- `MiniOSSession.cat_body` (method) `mcp/minios_mcp.py:464` `def cat_body(self, path, missing_ok)` -- Read a ramdisk file and return exactly its bytes.
- `MiniOSSession.write` (method) `mcp/minios_mcp.py:500` `def write(self, path, content)`
- `MiniOSSession.poweroff` (method) `mcp/minios_mcp.py:537` `def poweroff(self, timeout_ms)`
- `MiniOSSession.terminate` (method) `mcp/minios_mcp.py:557` `def terminate(self)`
- `MiniOSSession.close` (method) `mcp/minios_mcp.py:576` `def close(self)`
- `subprocess_launch` (function) `mcp/minios_mcp.py:580` `def subprocess_launch(cfg, slave_fd)`
- `MCPServer.__init__` (method) `mcp/minios_mcp.py:734` `def __init__(self, cfg)`
- `MCPServer.run` (method) `mcp/minios_mcp.py:738` `def run(self)`
- `main` (function) `mcp/minios_mcp.py:888` `def main()`

## mcp/mutate_mcp.sh
- `run_one` (function) `mcp/mutate_mcp.sh:116` -- Each mutant runs the suite in its own directory with its own pid file and addon state, so the runs are independent...

## net/net.c
Depends on: `headers/drivers/virtio_net.h`, `headers/net.h`, `headers/net/rtl8139.h`, `headers/sched.h`, `headers/tls.h`
- `net_drv_send` (function) `net/net.c:38` `static int net_drv_send(const unsigned char *frame, unsigned len)`
- `net_drv_poll` (function) `net/net.c:43` `static void net_drv_poll(void)`
- `net_drv_present` (function) `net/net.c:48` `static int net_drv_present(void)`
- `net_put16` (function) `net/net.c:57` `static void net_put16(unsigned char *p, unsigned short v)`
- `net_put32` (function) `net/net.c:62` `static void net_put32(unsigned char *p, unsigned int v)`
- `net_get16` (function) `net/net.c:69` `static unsigned short net_get16(const unsigned char *p)`
- `net_get32` (function) `net/net.c:73` `static unsigned int net_get32(const unsigned char *p)`
- `net_checksum` (function) `net/net.c:78` `static unsigned short net_checksum(const void *data, unsigned len)`
- `net_arp_store` (function) `net/net.c:103` `static void net_arp_store(const unsigned char *ip, const unsigned char *mac)`
- `net_arp_lookup` (function) `net/net.c:118` `static int net_arp_lookup(const unsigned char *ip, unsigned char *mac_out)`
- `net_arp_request` (function) `net/net.c:129` `static void net_arp_request(const unsigned char *ip)`
- `net_arp_resolve` (function) `net/net.c:147` `static int net_arp_resolve(const unsigned char *ip, unsigned char *mac_out)` -- kmemcpy(frame + 6, net_mac, NET_ETH_ALEN); net_put16(frame + 12, NET_ETHERTYPE_ARP); net_put16(frame + 14, 1)...
- `net_ip_send` (function) `net/net.c:172` `static int net_ip_send(const unsigned char *dip, unsigned char proto,
                       cons...`
- `net_udp_send` (function) `net/net.c:208` `static int net_udp_send(const unsigned char *dip, unsigned short sport,
                        u...`
- `net_dns_parse` (function) `net/net.c:230` `static void net_dns_parse(const unsigned char *data, unsigned len)` -- net_put16(pkt + 6, 0);                    /* checksum optional for UDP kmemcpy(pkt + 8, data, len); return...
- `net_dns_resolve` (function) `net/net.c:268` `static int net_dns_resolve(const char *host, unsigned char ip_out[4])` -- rtype = net_get16(data + pos); rdlen = net_get16(data + pos + 8); pos += 10; if (pos + rdlen > len) return; if...
- `net_udp_send` (function) `net/net.c:329` `net_udp_send((const unsigned char[])`
- `net_icmp_rx` (function) `net/net.c:348` `static void net_icmp_rx(const unsigned char *ip, unsigned len)`
- `net_ping` (function) `net/net.c:377` `static int net_ping(const unsigned char ip[4])`
- `net_sock_alloc` (function) `net/net.c:469` `static struct net_tcp_sock *net_sock_alloc(void)`
- `net_sock_index` (function) `net/net.c:484` `static int net_sock_index(const struct net_tcp_sock *s)`
- `net_tcp_checksum` (function) `net/net.c:493` `static unsigned short net_tcp_checksum(const unsigned char *src, const unsigned char *dst,
      ...` -- } } return 0; } static int net_sock_index(const struct net_tcp_sock *s) { int i; if (!net_sockets) return -1; for (i...
- `net_udp_checksum_ok` (function) `net/net.c:509` `static int net_udp_checksum_ok(const unsigned char *src, const unsigned char *dst,
              ...` -- const unsigned char *seg, unsigned len) { unsigned char buf[NET_TX_MAX + 12]; unsigned total = 12 + len...
- `net_tcp_xmit` (function) `net/net.c:525` `static int net_tcp_xmit(struct net_tcp_sock *s, unsigned flags,
                        const uns...`
- `net_tcp_rx` (function) `net/net.c:559` `static void net_tcp_rx(const unsigned char *ip, unsigned len)`
- `net_tcp_passive_open` (function) `net/net.c:687` `static int net_tcp_passive_open(struct net_tcp_sock *ls,
        const unsigned char peer[4], uns...` -- Passive open: park a SYN_RCVD child on a LISTEN socket and answer SYN-ACK.
- `net_tcp_connect_into` (function) `net/net.c:711` `static int net_tcp_connect_into(struct net_tcp_sock *s, const unsigned char ip[4],
              ...` -- kmemcpy(c->dip, peer, 4); c->dport = pport; c->sport = lport; c->seq = net_tcp_seq; net_tcp_seq += 0x1000...
- `net_tcp_send` (function) `net/net.c:738` `static int net_tcp_send(struct net_tcp_sock *s, const char *buf, int len)` -- unsigned long retry = net_time_ms() + NET_RETRY_MS; while (net_time_ms() < retry && s->state == NET_TCP_SYN_SENT)...
- `net_tcp_recv` (function) `net/net.c:764` `static int net_tcp_recv(struct net_tcp_sock *s, char *buf, int len)` -- net_time_ms() < deadline) { unsigned long retry = net_time_ms() + NET_RETRY_MS; while (net_time_ms() < retry &&...
- `net_tcp_close` (function) `net/net.c:802` `static void net_tcp_close(struct net_tcp_sock *s)`
- `net_rx_handle_frame` (function) `net/net.c:822` `void net_rx_handle_frame(const unsigned char *frame, unsigned len)`
- `net_open` (function) `net/net.c:886` `int net_open(void)`
- `net_connect` (function) `net/net.c:892` `int net_connect(const char *host, unsigned short port)`
- `net_send` (function) `net/net.c:901` `int net_send(int fd, const char *buf, int len)`
- `net_recv` (function) `net/net.c:906` `int net_recv(int fd, char *buf, int len)`
- `net_recv_timeout` (function) `net/net.c:911` `int net_recv_timeout(int fd, char *buf, int len, unsigned long timeout_ms)`
- `net_close` (function) `net/net.c:916` `void net_close(int fd)`
- `net_listen` (function) `net/net.c:927` `int net_listen(unsigned short port)` -- Docstring: Allocate a socket bound to a local port and listening. * Returns the socket index, or -1 when the table...
- `net_accept_nb` (function) `net/net.c:942` `int net_accept_nb(int fd)` -- Docstring: Take a pending child off a LISTEN socket without waiting.
- `polling` (function) `net/net.c:959` `* without polling (the peer's ACK arrives through the driver poll). */
int net_accept(int fd, uns...`
- `net_sock_state` (function) `net/net.c:976` `int net_sock_state(int fd)` -- Docstring: Socket state for diagnostics (the `net` builtin and the * httpd selftest). -1 on a wild fd.
- `net_fd_udp` (function) `net/net.c:1096` `static int net_fd_udp(long fd)`
- `net_sys_is_socket` (function) `net/net.c:1102` `int net_sys_is_socket(long fd)`
- `net_udp_alloc` (function) `net/net.c:1106` `static struct net_udp_sock *net_udp_alloc(void)`
- `net_udp_ephemeral` (function) `net/net.c:1120` `static unsigned short net_udp_ephemeral(void)` -- static struct net_udp_sock *net_udp_alloc(void) { int i; if (!net_udp_sockets) return 0; for (i = 0; i <...
- `net_udp_deliver` (function) `net/net.c:1136` `static int net_udp_deliver(const unsigned char sip[4], unsigned short sport,
                    ...` -- Queue a received datagram on the user socket bound to dport (and, when connected, from that peer only).
- `net_put_sockaddr` (function) `net/net.c:1158` `static void net_put_sockaddr(unsigned char *sa, const unsigned char ip[4], unsigned short port)`
- `net_store_sockaddr` (function) `net/net.c:1168` `static long net_store_sockaddr(long addr, long lenp, const unsigned char ip[4],
                 ...` -- Store a sockaddr_in at a user address with a user socklen_t length * pointer, truncating like Linux and reporting...
- `net_load_sockaddr` (function) `net/net.c:1185` `static long net_load_sockaddr(long addr, long len, unsigned char ip[4], unsigned short *port)` -- int len; if (!addr || !lenp) return 0; if (!user_range_ok((unsigned long)lenp, sizeof(int))) return -LNX_EFAULT; len...
- `net_sys_socket` (function) `net/net.c:1222` `long net_sys_socket(long a1, long a2, long a3)`
- `net_sys_connect` (function) `net/net.c:1249` `long net_sys_connect(long fd, long sockaddr, long addrlen)`
- `net_sys_bind` (function) `net/net.c:1296` `long net_sys_bind(long fd, long sockaddr, long addrlen)`
- `net_sys_listen` (function) `net/net.c:1318` `long net_sys_listen(long fd, long backlog)`
- `net_sys_accept` (function) `net/net.c:1329` `long net_sys_accept(long fd, long sockaddr, long addrlen)`
- `net_send_bytes` (function) `net/net.c:1347` `static long net_send_bytes(long fd, const unsigned char *buf, long len,
                         ...` -- Send len validated bytes: a stream sends synchronously (stop-and-wait), * a datagram goes out as one UDP datagram to...
- `net_sys_sendto` (function) `net/net.c:1375` `long net_sys_sendto(long fd, long buf, long len, long flags, long to, long tolen)`
- `net_sys_recvfrom` (function) `net/net.c:1390` `long net_sys_recvfrom(long fd, long buf, long len, long flags, long from, long fromlen)`
- `net_gather_msg` (function) `net/net.c:1450` `static long net_gather_msg(long msg, unsigned char *kbuf, long cap)` -- long rc = net_store_sockaddr(from, fromlen, s->dip, s->dport); if (rc) return rc; } return (long)take; } if...
- `net_sys_sendmsg` (function) `net/net.c:1470` `long net_sys_sendmsg(long fd, long msg, long flags)`
- `net_sys_sendmmsg` (function) `net/net.c:1498` `long net_sys_sendmmsg(long fd, long vec, long vlen, long flags)` -- sendmmsg (307): glibc's resolver sends its A and AAAA queries together and treats ENOSYS as a failed lookup.
- `net_sys_shutdown` (function) `net/net.c:1514` `long net_sys_shutdown(long fd, long how)`
- `net_sys_close` (function) `net/net.c:1523` `long net_sys_close(long fd)`
- `net_sys_setsockopt` (function) `net/net.c:1534` `long net_sys_setsockopt(long fd, long level, long name, long val, long len)`
- `net_sys_getsockopt` (function) `net/net.c:1569` `long net_sys_getsockopt(long fd, long level, long name, long val, long lenp)`
- `net_sys_getsockname` (function) `net/net.c:1616` `long net_sys_getsockname(long fd, long addr, long lenp)`
- `net_sys_getpeername` (function) `net/net.c:1625` `long net_sys_getpeername(long fd, long addr, long lenp)`
- `net_sys_fcntl` (function) `net/net.c:1643` `long net_sys_fcntl(long fd, long cmd, long arg)` -- fcntl on a socket: O_NONBLOCK through F_GETFL/F_SETFL, FD_CLOEXEC recorded through F_GETFD/F_SETFD (sockets live in...
- `net_sys_ioctl` (function) `net/net.c:1674` `long net_sys_ioctl(long fd, long req, long arg)` -- ioctl on a socket: FIONREAD answers the bytes a read would return now (a stream's buffered bytes, the size of a...
- `net_socket_revents` (function) `net/net.c:1707` `static unsigned short net_socket_revents(long fd)` -- return 0; } } else { return -LNX_EBADF; } switch (req) { case LNX_FIONBIO: *nb = *(const int *)arg != 0; return 0...
- `net_sys_poll` (function) `net/net.c:1727` `long net_sys_poll(long fds, long nfds, long timeout_ms)`
- `net_sys_dns` (function) `net/net.c:1767` `long net_sys_dns(long host)` -- MiniOS syscall 200: resolve a hostname, returned as a network-order * 32-bit address (like inet_addr), or -1 on failure.
- `net_parse_ip` (function) `net/net.c:1778` `static int net_parse_ip(const char *text, unsigned char ip[4])`
- `net_cmd_status` (function) `net/net.c:1803` `void net_cmd_status(void)`
- `net_get_addrs` (function) `net/net.c:1825` `void net_get_addrs(unsigned char mac_out[NET_ETH_ALEN], unsigned char ip_out[4])` -- kprintf("virtio-net iobase 0x%x\n", vnet_iobase()); } else { rtl_counters(&tx_frames, &rx_frames); kprintf("rtl8139...
- `net_cmd_ping` (function) `net/net.c:1831` `void net_cmd_ping(const char *ip_text)`
- `net_cmd_dns` (function) `net/net.c:1842` `void net_cmd_dns(const char *host)`
- `net_register_symbols` (function) `net/net.c:1855` `void net_register_symbols(void)`
- `net_init` (function) `net/net.c:1863` `void net_init(void)`

## net/rtl8139.c
Depends on: `headers/drivers/pci.h`, `headers/net.h`, `headers/net/rtl8139.h`, `headers/sched.h`
- `outl_port` (function) `net/rtl8139.c:29` `static void outl_port(unsigned short port, unsigned int val)` -- Byte/word port I/O comes from kernel.h (outb/inb/outw/inw, same asm). * Only the dword pair stays local: the shared...
- `inl_port` (function) `net/rtl8139.c:33` `static unsigned int inl_port(unsigned short port)`
- `rtl_reg8` (function) `net/rtl8139.c:39` `static unsigned char rtl_reg8(unsigned short off)`
- `rtl_reg8_w` (function) `net/rtl8139.c:40` `static void rtl_reg8_w(unsigned short off, unsigned char v)`
- `rtl_reg16` (function) `net/rtl8139.c:41` `static unsigned short rtl_reg16(unsigned short off)`
- `rtl_reg16_w` (function) `net/rtl8139.c:42` `static void rtl_reg16_w(unsigned short off, unsigned short v)`
- `rtl_reg32` (function) `net/rtl8139.c:43` `static unsigned int rtl_reg32(unsigned short off)`
- `rtl_reg32_w` (function) `net/rtl8139.c:44` `static void rtl_reg32_w(unsigned short off, unsigned int v)`
- `rtl_find` (function) `net/rtl8139.c:58` `static unsigned short rtl_find(void)` -- PCI config space lives in drivers/pci.h now (shared with virtio-blk and future devices); only the dword port pair...
- `deleted` (function) `net/rtl8139.c:79` `* been deleted (a second base/per-ms pair beside ktime's is a second
 * clock, and drivers must n...`
- `rtl_present` (function) `net/rtl8139.c:107` `int rtl_present(void)`
- `rtl_reset` (function) `net/rtl8139.c:111` `static void rtl_reset(void)`
- `rtl_init` (function) `net/rtl8139.c:120` `void rtl_init(void)`
- `rtl_tx_wait` (function) `net/rtl8139.c:168` `static int rtl_tx_wait(unsigned slot, unsigned long deadline)`
- `rtl_send` (function) `net/rtl8139.c:177` `int rtl_send(const unsigned char *frame, unsigned len)`
- `rtl_get_mac` (function) `net/rtl8139.c:205` `void rtl_get_mac(unsigned char out[NET_ETH_ALEN])`
- `rtl_iobase` (function) `net/rtl8139.c:210` `unsigned short rtl_iobase(void)`
- `rtl_counters` (function) `net/rtl8139.c:214` `void rtl_counters(unsigned int *tx_frames, unsigned int *rx_frames)`
- `rtl_poll` (function) `net/rtl8139.c:238` `void rtl_poll(void)`

## net/tls.c
Depends on: `headers/tls.h`, `headers/tls_port.h`, `headers/tls_roots.h`
- `tls_fail` (function) `net/tls.c:25` `static void tls_fail(struct tls_session *s, const char *stage, const char *reason)`
- `tls_fd_of` (function) `net/tls.c:33` `static int tls_fd_of(const struct tls_session *s)`
- `tls_free_fd` (function) `net/tls.c:40` `void tls_free_fd(int fd)`
- `tls_aad` (function) `net/tls.c:52` `static void tls_aad(unsigned char aad[13], int type, unsigned long long seq,
                    ...` -- Build the TLS 1.2 AEAD additional data: seq(8) || type || 0303 || * TLSCompressed.length (the plaintext length, RFC...
- `number` (function) `net/tls.c:64` `* The nonce_explicit is the sequence number (RFC 5288 allows it and * OpenSSL uses it);`
- `tls_send_record` (function) `net/tls.c:66` `static int tls_send_record(struct tls_session *s, int type,
                           const unsi...` -- Send one record: header || nonce_explicit(8) || ciphertext || tag.
- `tls_send_raw_record` (function) `net/tls.c:95` `static int tls_send_raw_record(struct tls_session *s, int type,
                               co...` -- for (i = 0; i < 8; i++) buf[5 + i] = (unsigned char)(s->cli_seq >> (56 - i * 8)); TLS_MEMCPY(nonce, s->cli_salt, 4)...
- `tls_read_record` (function) `net/tls.c:114` `static int tls_read_record(struct tls_session *s, int fd, int deadline_ms)` -- Read one record: header into s->rec_hdr, payload into s->rec.
- `exchange` (function) `net/tls.c:173` `* key exchange (ClientHello, ClientKeyExchange) go out in plaintext
 * records, as TLS 1.2 requir...`
- `build_client_hello` (function) `net/tls.c:190` `static int build_client_hello(struct tls_session *s, unsigned char *out)` -- const unsigned char *body, int len) { if (len < 0 || len > 1024) return -1; s->pt[0] = (unsigned char)type; s->pt[1]...
- `client_finish_flight` (function) `net/tls.c:244` `static int client_finish_flight(struct tls_session *s)` -- out[pos++] = 0x00; out[pos++] = 0x06; out[pos++] = 0x04; out[pos++] = 0x01;   /* rsa_pkcs1_sha256 out[pos++] = 0x04...
- `parse_server_hello` (function) `net/tls.c:340` `static int parse_server_hello(struct tls_session *s,
                              const unsigned...`
- `parse_certificate` (function) `net/tls.c:370` `static int parse_certificate(struct tls_session *s,
                             const unsigned c...`
- `parse_server_key_exchange` (function) `net/tls.c:401` `static int parse_server_key_exchange(struct tls_session *s,
                                     ...`
- `tls_handshake` (function) `net/tls.c:466` `int tls_handshake(int fd, const char *host)`
- `tls_send` (function) `net/tls.c:687` `int tls_send(int fd, const char *buf, int len)`
- `tls_recv` (function) `net/tls.c:696` `int tls_recv(int fd, char *buf, int len)`
- `tls_sys_handshake` (function) `net/tls.c:772` `long tls_sys_handshake(long fd, long host)` -- if !defined(TLS_TEST) && !defined(TLS_RING3)
- `tls_sys_send` (function) `net/tls.c:777` `long tls_sys_send(long fd, long buf, long len)`
- `tls_sys_recv` (function) `net/tls.c:782` `long tls_sys_recv(long fd, long buf, long len)`
- `tls_rdtsc` (function) `net/tls.c:789` `static inline unsigned long long tls_rdtsc(void)`
- `tls_random` (function) `net/tls.c:795` `void tls_random(unsigned char *out, unsigned len)`
- `outb` (function) `net/tls.c:810` `static inline void outb(unsigned short port, unsigned char v)` -- unsigned long long seed = tls_rdtsc() ^ ((unsigned long long)net_time_ms() << 33); unsigned i; static unsigned long...
- `inb` (function) `net/tls.c:813` `static inline unsigned char inb(unsigned short port)`
- `cmos_read` (function) `net/tls.c:821` `static inline unsigned char cmos_read(unsigned char reg)` -- /* The port helpers in net.c are static; these live here for the RTC. #ifndef PORT_IO_DEFINED #define...
- `tls_now_days` (function) `net/tls.c:826` `long tls_now_days(void)`


Next: [API_p10.md](API_p10.md)
