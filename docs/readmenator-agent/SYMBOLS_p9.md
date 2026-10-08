# Symbols (page 9 of 24)
Previous: [SYMBOLS_p8.md](SYMBOLS_p8.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `sys_minios_sb16_stream_vol` | function | `kernel/syscalls.c:748` | `static long sys_minios_sb16_stream_vol(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_sb16_submit` | function | `kernel/syscalls.c:649` | `static long sys_minios_sb16_submit(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_spawn` | function | `kernel/syscalls.c:556` | `static long sys_minios_spawn(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_submit_batch` | function | `kernel/syscalls.c:836` | `static long sys_minios_submit_batch(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_time` | function | `kernel/syscalls.c:304` | `static long sys_minios_time(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_tls_retired` | function | `kernel/syscalls.c:268` | `static long sys_minios_tls_retired(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_vga_mode` | function | `kernel/syscalls.c:346` | `static long sys_minios_vga_mode(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `syscall_name` | function | `kernel/syscalls.c:2303` | `const char *syscall_name(long n)` |
| `syscall_trace_enabled` | function | `kernel/syscalls.c:1072` | `long syscall_trace_enabled(void)` |
| `syscall_trace_set` | function | `kernel/syscalls.c:1073` | `void syscall_trace_set(int on)` |
| `syscall_trace_shown` | function | `kernel/syscalls.c:1076` | `unsigned long syscall_trace_shown(void)` |
| `syscall_trace_verbose_enabled` | function | `kernel/syscalls.c:1074` | `long syscall_trace_verbose_enabled(void)` |
| `syscall_trace_verbose_set` | function | `kernel/syscalls.c:1075` | `void syscall_trace_verbose_set(int on)` |
| `trace_hint_print` | function | `kernel/syscalls.c:2344` | `static void trace_hint_print(long n, int kind, const char *path,                              lon...` |
| `trace_is_noisy` | function | `kernel/syscalls.c:2275` | `static int trace_is_noisy(long n)` |
| `untouched` | function | `kernel/syscalls.c:136` | `* child untouched (caller refuses fail-closed). */ int kfd_view_copy(proc_t *child, proc_t *parent)` |
| `user_range_ok` | function | `kernel/syscalls.c:2395` | `int user_range_ok(unsigned long p, unsigned long len)` |
| `view` | function | `kernel/syscalls.c:465` | `* view (same as the `clear` builtin). Anything else is -EINVAL. Each  * out-word is range-checked...` |
| `vma_free_cover` | function | `kernel/syscalls.c:1676` | `static vma_node_t *vma_free_cover(unsigned long base, unsigned long len)` |
| `vma_live_overlap` | function | `kernel/syscalls.c:1695` | `static int vma_live_overlap(unsigned long base, unsigned long len)` |
| `wall_us_now` | function | `kernel/syscalls.c:253` | `unsigned long wall_us_now(void)` |
| `code` | function | `kernel/syscalls_proc.c:169` | `* exit code (no WEXITSTATUS encoding: MiniOS reports codes directly). */ long sys_linux_wait4(lon...` |
| `state` | function | `kernel/syscalls_proc.c:5` | `* touches only scheduler state (current_pid, procs[], do_* / * seccomp_* / yield) plus the kernel-wide user_range_ok...` |
| `sys_linux_execve` | function | `kernel/syscalls_proc.c:85` | `long sys_linux_execve(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_exit` | function | `kernel/syscalls_proc.c:161` | `long sys_linux_exit(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_fork` | function | `kernel/syscalls_proc.c:75` | `long sys_linux_fork(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_getpid` | function | `kernel/syscalls_proc.c:70` | `long sys_linux_getpid(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_gettid` | function | `kernel/syscalls_proc.c:193` | `long sys_linux_gettid(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_kill` | function | `kernel/syscalls_proc.c:188` | `long sys_linux_kill(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_vfork` | function | `kernel/syscalls_proc.c:80` | `long sys_linux_vfork(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_yield` | function | `kernel/syscalls_proc.c:65` | `long sys_linux_yield(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_clone` | function | `kernel/syscalls_proc.c:16` | `long sys_minios_clone(long flags, long newsp, long a3, long a4, long a5, long a6)` |
| `sys_minios_nice` | function | `kernel/syscalls_proc.c:52` | `long sys_minios_nice(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_seccomp` | function | `kernel/syscalls_proc.c:35` | `long sys_minios_seccomp(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_thread_spawn` | function | `kernel/syscalls_proc.c:22` | `long sys_minios_thread_spawn(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `tick_audio_count` | function | `kernel/tick.c:133` | `int tick_audio_count(void)` |
| `tick_desktop_count` | function | `kernel/tick.c:144` | `int tick_desktop_count(void)` |
| `tick_desktop_due` | function | `kernel/tick.c:160` | `int tick_desktop_due(unsigned long long ticks, unsigned interval)` |
| `tick_register_audio` | function | `kernel/tick.c:58` | `int tick_register_audio(tick_fn_t fn, void *ctx)` |
| `tick_register_desktop` | function | `kernel/tick.c:76` | `int tick_register_desktop(tick_fn_t fn, void *ctx)` |
| `tick_register_usb` | function | `kernel/tick.c:89` | `int tick_register_usb(tick_fn_t fn, void *ctx)` |
| `tick_reset` | function | `kernel/tick.c:34` | `void tick_reset(void)` |
| `tick_run_audio` | function | `kernel/tick.c:113` | `void tick_run_audio(void)` |
| `tick_run_desktop` | function | `kernel/tick.c:123` | `void tick_run_desktop(void)` |
| `tick_run_usb` | function | `kernel/tick.c:103` | `void tick_run_usb(void)` |
| `tick_slot_t` | struct | `kernel/tick.c:15` | `` |
| `ktime_init` | function | `kernel/time.c:19` | `static void ktime_init(void)` |
| `ktime_ms` | function | `kernel/time.c:33` | `unsigned long ktime_ms(void)` |
| `ktime_rdtsc` | function | `kernel/time.c:13` | `static unsigned long ktime_rdtsc(void)` |
| `ktime_us` | function | `kernel/time.c:41` | `unsigned long ktime_us(void)` |
| `CURSOR_TIP_X` | macro | `kernel/vga_cursor.c:28` | `#define CURSOR_TIP_X` |
| `CURSOR_TIP_Y` | macro | `kernel/vga_cursor.c:29` | `#define CURSOR_TIP_Y` |
| `cursor_draw` | function | `kernel/vga_cursor.c:68` | `static void cursor_draw(int mx, int my)` |
| `cursor_erase` | function | `kernel/vga_cursor.c:133` | `void cursor_erase(void)` |
| `cursor_has_set_neighbour` | function | `kernel/vga_cursor.c:57` | `static int cursor_has_set_neighbour(int i, int j)` |
| `cursor_invalidate` | function | `kernel/vga_cursor.c:141` | `void cursor_invalidate(void)` |
| `cursor_is_set` | function | `kernel/vga_cursor.c:50` | `static int cursor_is_set(int i, int j)` |
| `cursor_move` | function | `kernel/vga_cursor.c:116` | `void cursor_move(int mx, int my)` |
| `cursor_note_repaint` | function | `kernel/vga_cursor.c:147` | `void cursor_note_repaint(int x0, int y0, int w, int h)` |
| `cursor_over` | function | `kernel/vga_cursor.c:96` | `int cursor_over(int x0, int y0, int w, int h)` |
| `cursor_place` | function | `kernel/vga_cursor.c:106` | `void cursor_place(int mx, int my)` |
| `cursor_restore` | function | `kernel/vga_cursor.c:81` | `static void cursor_restore(int mx, int my)` |
| `cursor_save_bg` | function | `kernel/vga_cursor.c:40` | `static void cursor_save_bg(int mx, int my)` |
| `FBT` | macro | `kernel/vga_fb.c:145` | `#define FBT` |
| `FB_OFFSET` | macro | `kernel/vga_fb.c:1607` | `#define FB_OFFSET(x,y)` |
| `GFX_CURSOR_IDLE_TICKS` | macro | `kernel/vga_fb.c:515` | `#define GFX_CURSOR_IDLE_TICKS` |
| `GFX_KEEP_BYTES` | macro | `kernel/vga_fb.c:489` | `#define GFX_KEEP_BYTES` |
| `GFX_PROG_LEN` | macro | `kernel/vga_fb.c:556` | `#define GFX_PROG_LEN` |
| `GFX_SRC_IDX` | macro | `kernel/vga_fb.c:487` | `#define GFX_SRC_IDX` |
| `GFX_SRC_RGB` | macro | `kernel/vga_fb.c:488` | `#define GFX_SRC_RGB` |
| `LG_LINE` | macro | `kernel/vga_fb.c:296` | `#define LG_LINE(a)` |
| `TB_GFX_TITLE_MAX` | macro | `kernel/vga_fb.c:2405` | `#define TB_GFX_TITLE_MAX` |
| `WIN_DEF_COLS` | macro | `kernel/vga_fb.c:877` | `#define WIN_DEF_COLS` |
| `WIN_DEF_ROWS` | macro | `kernel/vga_fb.c:878` | `#define WIN_DEF_ROWS` |
| `WIN_DEF_X` | macro | `kernel/vga_fb.c:879` | `#define WIN_DEF_X` |
| `WIN_DEF_Y` | macro | `kernel/vga_fb.c:880` | `#define WIN_DEF_Y` |
| `WM_ELINE_SZ` | macro | `kernel/vga_fb.c:909` | `#define WM_ELINE_SZ` |
| `WM_MAX_TERMS` | macro | `kernel/vga_fb.c:908` | `#define WM_MAX_TERMS` |
| `act_nrows` | function | `kernel/vga_fb.c:334` | `static int act_nrows(void)` |
| `alone` | function | `kernel/vga_fb.c:1319` | `* window alone (an unfocused graphics window minimizes to the taskbar,  * exactly like the hidden...` |
| `app` | function | `kernel/vga_fb.c:1136` | `* a gfx child spawned from another gfx app (file -> vedit) keeps the * terminal focused, so its keys and wheel keep...` |
| `buffer` | function | `kernel/vga_fb.c:2758` | `* owns the buffer (indices reset, render reads an empty ring). */ void term_clear(void)` |
| `ci_eq` | function | `kernel/vga_fb.c:595` | `static int ci_eq(const char *a, const char *b)` |
| `command` | function | `kernel/vga_fb.c:4028` | `* its launch command (config-driven, covers apps that never set a window * title);` |
| `compositions` | function | `kernel/vga_fb.c:133` | `* compositions (an ISR tick composing inside a syscall composition) draw * into the same shadow and leave the...` |
| `content` | function | `kernel/vga_fb.c:1193` | `* windows would share content (same prompt/output on both) and a park  * would alias src == dst. ...` |
| `coordinates` | function | `kernel/vga_fb.c:723` | `* windows keep the exact historical coordinates (including outside the * window);` |
| `desktop_shortcuts_draw` | function | `kernel/vga_fb.c:3939` | `void desktop_shortcuts_draw(void)` |
| `desktop_shortcuts_hit_test` | function | `kernel/vga_fb.c:4054` | `const char *desktop_shortcuts_hit_test(int mx, int my)` |
| `desktop_shortcuts_load` | function | `kernel/vga_fb.c:3713` | `void desktop_shortcuts_load(void)` |
| `directly` | function | `kernel/vga_fb.c:2127` | `* RGB sources pack directly (quantized to the wallpaper cube in 8-bit). */ static void gfx_scale_...` |
| `disp_clamp` | function | `kernel/vga_fb.c:345` | `static void disp_clamp(void)` |
| `dock_bounce_counts` | function | `kernel/vga_fb.c:3821` | `void dock_bounce_counts(unsigned long *kicks, unsigned long *paints)` |
| `dock_bounce_elapsed` | function | `kernel/vga_fb.c:3837` | `static unsigned long dock_bounce_elapsed(void)` |
| `dock_bounce_live` | function | `kernel/vga_fb.c:3845` | `static int dock_bounce_live(void)` |
| `dock_click_count` | function | `kernel/vga_fb.c:3831` | `void dock_click_count(unsigned long *edges)` |
| `dock_hover_index` | function | `kernel/vga_fb.c:3794` | `static int dock_hover_index(int mx, int my)` |
| `dock_label_px` | function | `kernel/vga_fb.c:3679` | `static int dock_label_px(const struct desktop_shortcut *sc)` |
| `dock_paint_hover` | function | `kernel/vga_fb.c:3997` | `static void dock_paint_hover(int hover)` |
| `dock_paint_icons` | function | `kernel/vga_fb.c:3903` | `static void dock_paint_icons(int hover)` |
| `dock_pending_active` | function | `kernel/vga_fb.c:3895` | `int dock_pending_active(void)` |
| `draw_scrollbar` | function | `kernel/vga_fb.c:2663` | `static void draw_scrollbar(void)` |
| `draw_speaker_icon` | function | `kernel/vga_fb.c:2438` | `static void draw_speaker_icon(int x, int y, uint8_t color)` |
| `draw_title_win` | function | `kernel/vga_fb.c:2376` | `static void draw_title_win(int idx, int focused)` |
| `escapes` | function | `kernel/vga_fb.c:2827` | `* swallowing them here keeps the escapes (which the serial side needs)      * from printing as li...` |
| `fb_bytes_per_pixel` | function | `kernel/vga_fb.c:117` | `int fb_bytes_per_pixel(void)` |
| `fb_compose_begin` | function | `kernel/vga_fb.c:221` | `static int fb_compose_begin(void)` |
| `fb_compose_end` | function | `kernel/vga_fb.c:234` | `static void fb_compose_end(int owner)` |
| `fb_copy_bytes` | function | `kernel/vga_fb.c:151` | `static void fb_copy_bytes(volatile void *dst, const volatile void *src, unsigned long n)` |
| `fb_fill_run` | function | `kernel/vga_fb.c:1802` | `static void fb_fill_run(int x, int y, int n, unsigned long px)` |
| `fb_fill_u32` | function | `kernel/vga_fb.c:169` | `static void fb_fill_u32(volatile void *dst, unsigned int v, unsigned long n)` |
| `fb_frame_bytes` | function | `kernel/vga_fb.c:183` | `static unsigned long fb_frame_bytes(void)` |
| `fb_glyph` | function | `kernel/vga_fb.c:1890` | `static const uint8_t *fb_glyph(unsigned char c)` |
| `fb_pack_idx` | function | `kernel/vga_fb.c:1685` | `static unsigned long fb_pack_idx(unsigned idx)` |
| `fb_present_shadow` | function | `kernel/vga_fb.c:210` | `static void fb_present_shadow(void)` |
| `fb_read_packed` | function | `kernel/vga_fb.c:1721` | `unsigned long fb_read_packed(int x, int y)` |
| `fb_read_row_packed` | function | `kernel/vga_fb.c:1780` | `void fb_read_row_packed(int x, int y, unsigned int *dst, int n)` |
| `fb_shadow_ready` | function | `kernel/vga_fb.c:189` | `static int fb_shadow_ready(void)` |
| `fb_write_packed` | function | `kernel/vga_fb.c:1701` | `void fb_write_packed(int x, int y, unsigned long rgb)` |
| `fb_write_row_packed` | function | `kernel/vga_fb.c:1750` | `void fb_write_row_packed(int x, int y, const unsigned int *src, int n)` |
| `first` | function | `kernel/vga_fb.c:419` | `* screen ever showing it whole first (the old flash-then-melt). */ static unsigned int *fx_start_...` |
| `flag` | function | `kernel/vga_fb.c:496` | `* is the minimized flag (the program keeps running, nothing composites);` |
| `from` | function | `kernel/vga_fb.c:3134` | `* leaving returns to the view it came from (floating or tiled). Returns  * 0 on success, -1 witho...` |
| `gfx_animate` | function | `kernel/vga_fb.c:3036` | `static void gfx_animate(const wm_gfxview_rect_t *from, const wm_gfxview_rect_t *to,              ...` |
| `gfx_compose` | function | `kernel/vga_fb.c:2263` | `static void gfx_compose(const volatile uint8_t *src, int kind, int sw, int sh,                   ...` |
| `gfx_covers_screen` | function | `kernel/vga_fb.c:527` | `static int gfx_covers_screen(void)` |
| `gfx_drop_focus` | function | `kernel/vga_fb.c:3123` | `static void gfx_drop_focus(int source)` |
| `gfx_float_frame` | function | `kernel/vga_fb.c:693` | `static int gfx_float_frame(wm_gfxview_rect_t *out)` |
| `gfx_keep_save` | function | `kernel/vga_fb.c:533` | `static void gfx_keep_save(const volatile uint8_t *src, int kind, int sw, int sh)` |
| `gfx_letterbox` | function | `kernel/vga_fb.c:2232` | `static void gfx_letterbox(const wm_gfxview_t *v)` |
| `gfx_prog_icon` | function | `kernel/vga_fb.c:608` | `static const uint8_t *gfx_prog_icon(void)` |
| `gfx_snap` | function | `kernel/vga_fb.c:3255` | `static void gfx_snap(int zone)` |
| `gfx_task_icon` | function | `kernel/vga_fb.c:4033` | `static const uint8_t *gfx_task_icon(void)` |
| `gfx_taskbar_rect` | function | `kernel/vga_fb.c:3086` | `static void gfx_taskbar_rect(wm_gfxview_rect_t *r)` |
| `gfx_title` | function | `kernel/vga_fb.c:2251` | `static void gfx_title(const wm_gfxview_t *v)` |
| `gfx_transition` | function | `kernel/vga_fb.c:917` | `static void gfx_transition(const wm_gfxview_rect_t *from, int from_titled);` |
| `gfx_view_for` | function | `kernel/vga_fb.c:667` | `static int gfx_view_for(int sw, int sh, wm_gfxview_t *v)` |
| `gfx_view_in_rect` | function | `kernel/vga_fb.c:3017` | `static void gfx_view_in_rect(const wm_gfxview_rect_t *r, int titled, wm_gfxview_t *v)` |
| `gfx_view_publish` | function | `kernel/vga_fb.c:679` | `static void gfx_view_publish(const wm_gfxview_t *v)` |
| `icon_decode` | function | `kernel/vga_fb.c:3617` | `static const uint8_t *icon_decode(const char *path)` |
| `icon_embedded` | function | `kernel/vga_fb.c:3597` | `static const uint8_t *icon_embedded(const char *name)` |
| `icon_embedded_rgba` | function | `kernel/vga_fb.c:3651` | `static const uint8_t *icon_embedded_rgba(const uint8_t *idx)` |
| `icon_nearest` | function | `kernel/vga_fb.c:3581` | `static int icon_nearest(int r, int g, int b)` |
| `letterbox` | function | `kernel/vga_fb.c:500` | `* present to repaint chrome plus letterbox (after a desktop redraw or a * view change);` |
| `lg_get` | function | `kernel/vga_fb.c:305` | `static const char *lg_get(int i)` |
| `lg_push` | function | `kernel/vga_fb.c:312` | `static void lg_push(const char *line, int len)` |
| `line` | function | `kernel/vga_fb.c:2818` | `* display stale bytes left over from a longer previous line (e.g. the prompt  * would show the ta...` |
| `line_at` | function | `kernel/vga_fb.c:363` | `static const char *line_at(int abs, int *off)` |
| `line_nrows` | function | `kernel/vga_fb.c:327` | `static int line_nrows(int len)` |
| `mouse_apply_wheel` | function | `kernel/vga_fb.c:4094` | `static void mouse_apply_wheel(int wheel, int step)` |
| `mouse_drag_gfx` | function | `kernel/vga_fb.c:4118` | `static void mouse_drag_gfx(const wm_geom_config_t *gcfg, int mx, int my)` |
| `mouse_drag_term` | function | `kernel/vga_fb.c:4170` | `static void mouse_drag_term(const wm_geom_config_t *gcfg, int win_w, int mx, int my, int gfx_cursor)` |
| `mouse_focus_topmost` | function | `kernel/vga_fb.c:4068` | `static int mouse_focus_topmost(int mx, int my)` |
| `mouse_scrollbar` | function | `kernel/vga_fb.c:4193` | `static void mouse_scrollbar(const wm_geom_config_t *gcfg, int mx, int my)` |
| `path` | function | `kernel/vga_fb.c:4227` | `* present path (blit_gfx_buf) is the sole cursor painter. The tick * used to share the sprite state with it and...` |
| `pipe_field` | function | `kernel/vga_fb.c:3563` | `static const char *pipe_field(const char *line, int idx, char *buf, int buflen)` |
| `pointer` | function | `kernel/vga_fb.c:4115` | `* tiled window floats it at native size under the pointer (the grab point * keeps its relative position along the...` |
| `render_blank_row` | function | `kernel/vga_fb.c:2698` | `static void render_blank_row(int vrow)` |
| `render_row` | function | `kernel/vga_fb.c:2708` | `static void render_row(int vrow, int abs)` |
| `shcmd_base` | function | `kernel/vga_fb.c:578` | `static void shcmd_base(const char *cmd, char *out, unsigned long cap)` |
| `shortcut_cell_left` | function | `kernel/vga_fb.c:3706` | `static int shortcut_cell_left(int i)` |
| `shortcut_draw_scaled` | function | `kernel/vga_fb.c:3769` | `static void shortcut_draw_scaled(const struct desktop_shortcut *sc,                              ...` |
| `shortcuts_layout` | function | `kernel/vga_fb.c:3688` | `static void shortcuts_layout(void)` |
| `state` | function | `kernel/vga_fb.c:4339` | `* ignores the button state (the arming press is consumed) and settles      * once on expiry, so t...` |
| `taskbar` | function | `kernel/vga_fb.c:2079` | `* minimize hides the app to the taskbar (it never closes it), maximize  * toggles true fullscreen...` |
| `taskbar_handle_click` | function | `kernel/vga_fb.c:2603` | `static void taskbar_handle_click(int mx, int my)` |
| `taskbar_layout` | function | `kernel/vga_fb.c:2407` | `static void taskbar_layout(void)` |
| `taskbar_render` | function | `kernel/vga_fb.c:2447` | `static void taskbar_render(void)` |
| `taskbar_theme_cycle` | function | `kernel/vga_fb.c:2563` | `static void taskbar_theme_cycle(void)` |
| `taskbar_tick` | function | `kernel/vga_fb.c:2526` | `static void taskbar_tick(void)` |
| `term_close_default` | function | `kernel/vga_fb.c:3288` | `static void term_close_default(void)` |
| `term_finish_layout` | function | `kernel/vga_fb.c:3372` | `static void term_finish_layout(void)` |
| `term_max_cols` | function | `kernel/vga_fb.c:3363` | `static int term_max_cols(void)` |
| `term_max_rows` | function | `kernel/vga_fb.c:3367` | `static int term_max_rows(void)` |
| `term_recalc` | function | `kernel/vga_fb.c:2350` | `static void term_recalc(void)` |
| `term_render` | function | `kernel/vga_fb.c:2743` | `static void term_render(void)` |
| `term_render_active` | function | `kernel/vga_fb.c:2775` | `static void term_render_active(void)` |
| `term_toggle_fullscreen` | function | `kernel/vga_fb.c:3208` | `static void term_toggle_fullscreen(void)` |
| `term_toggle_minimize` | function | `kernel/vga_fb.c:3231` | `static void term_toggle_minimize(void)` |
| `termwin_t` | struct | `kernel/vga_fb.c:919` | `` |
| `text_px` | function | `kernel/vga_fb.c:1987` | `static void text_px(int px, int py, const char *s, uint8_t fg, uint8_t bg)` |
| `title` | function | `kernel/vga_fb.c:2457` | `* 8px row plus its title (bright when focused). The hint line * starts after it instead of underneath. */ const...` |
| `total_rows` | function | `kernel/vga_fb.c:337` | `static int total_rows(void)` |
| `tw_hit` | function | `kernel/vga_fb.c:1564` | `static int tw_hit(int i, int mx, int my)` |
| `tw_park` | function | `kernel/vga_fb.c:976` | `static void tw_park(int i)` |
| `tw_select` | function | `kernel/vga_fb.c:1066` | `static void tw_select(int i)` |
| `tw_unpark` | function | `kernel/vga_fb.c:1006` | `static void tw_unpark(int i)` |
| `vga_fb_act_empty` | function | `kernel/vga_fb.c:1504` | `int vga_fb_act_empty(void)` |
| `vga_fb_blit_gfx_window` | function | `kernel/vga_fb.c:2326` | `void vga_fb_blit_gfx_window(void)` |
| `vga_fb_blit_nk_rgb_window` | function | `kernel/vga_fb.c:2341` | `void vga_fb_blit_nk_rgb_window(void)` |
| `vga_fb_blit_nk_window` | function | `kernel/vga_fb.c:2335` | `void vga_fb_blit_nk_window(void)` |
| `vga_fb_boot_config` | function | `kernel/vga_fb.c:90` | `void vga_fb_boot_config(void)` |
| `vga_fb_char` | function | `kernel/vga_fb.c:1962` | `void vga_fb_char(int col, int row, char c, uint8_t fg, uint8_t bg)` |
| `vga_fb_clear` | function | `kernel/vga_fb.c:1921` | `void vga_fb_clear(void)` |
| `vga_fb_clear_prompt` | function | `kernel/vga_fb.c:1513` | `void vga_fb_clear_prompt(void)` |
| `vga_fb_close_active` | function | `kernel/vga_fb.c:3304` | `int vga_fb_close_active(void)` |
| `vga_fb_draw_desktop` | function | `kernel/vga_fb.c:2922` | `void vga_fb_draw_desktop(void)` |
| `vga_fb_focus_event` | function | `kernel/vga_fb.c:961` | `const wm_notify_event_t *vga_fb_focus_event(void)` |
| `vga_fb_focus_get` | function | `kernel/vga_fb.c:1078` | `int vga_fb_focus_get(void)` |
| `vga_fb_focus_id` | function | `kernel/vga_fb.c:1160` | `int vga_fb_focus_id(int id)` |
| `vga_fb_focus_next` | function | `kernel/vga_fb.c:1095` | `void vga_fb_focus_next(void)` |
| `vga_fb_focus_report` | function | `kernel/vga_fb.c:967` | `void vga_fb_focus_report(int before, int source)` |
| `vga_fb_gfx_cursor_draw` | function | `kernel/vga_fb.c:751` | `static void vga_fb_gfx_cursor_draw(void)` |
| `vga_fb_gfx_cursor_erase` | function | `kernel/vga_fb.c:741` | `static void vga_fb_gfx_cursor_erase(void)` |
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
| `NET_TCP_CLOSED` | macro | `net/net.c:399` | `#define NET_TCP_CLOSED` |
| `NET_TCP_DEAD` | macro | `net/net.c:403` | `#define NET_TCP_DEAD` |
| `NET_TCP_ESTABLISHED` | macro | `net/net.c:401` | `#define NET_TCP_ESTABLISHED` |
| `NET_TCP_FIN_SENT` | macro | `net/net.c:402` | `#define NET_TCP_FIN_SENT` |
| `NET_TCP_LISTEN` | macro | `net/net.c:404` | `#define NET_TCP_LISTEN` |
| `NET_TCP_SYN_RCVD` | macro | `net/net.c:405` | `#define NET_TCP_SYN_RCVD` |
| `NET_TCP_SYN_SENT` | macro | `net/net.c:400` | `#define NET_TCP_SYN_SENT` |
| `net_accept_nb` | function | `net/net.c:906` | `int net_accept_nb(int fd)` |
| `net_arp_entry` | struct | `net/net.c:94` | `` |
| `net_arp_lookup` | function | `net/net.c:117` | `static int net_arp_lookup(const unsigned char *ip, unsigned char *mac_out)` |
| `net_arp_request` | function | `net/net.c:128` | `static void net_arp_request(const unsigned char *ip)` |
| `net_arp_resolve` | function | `net/net.c:146` | `static int net_arp_resolve(const unsigned char *ip, unsigned char *mac_out)` |
| `net_arp_store` | function | `net/net.c:102` | `static void net_arp_store(const unsigned char *ip, const unsigned char *mac)` |
| `net_checksum` | function | `net/net.c:77` | `static unsigned short net_checksum(const void *data, unsigned len)` |
| `net_close` | function | `net/net.c:880` | `void net_close(int fd)` |
| `net_cmd_dns` | function | `net/net.c:1204` | `void net_cmd_dns(const char *host)` |
| `net_cmd_ping` | function | `net/net.c:1193` | `void net_cmd_ping(const char *ip_text)` |
| `net_cmd_status` | function | `net/net.c:1165` | `void net_cmd_status(void)` |
| `net_connect` | function | `net/net.c:856` | `int net_connect(const char *host, unsigned short port)` |
| `net_dns_parse` | function | `net/net.c:229` | `static void net_dns_parse(const unsigned char *data, unsigned len)` |
| `net_dns_resolve` | function | `net/net.c:267` | `static int net_dns_resolve(const char *host, unsigned char ip_out[4])` |
| `net_dns_state` | struct | `net/net.c:220` | `` |
| `net_drv_poll` | function | `net/net.c:42` | `static void net_drv_poll(void)` |
| `net_drv_present` | function | `net/net.c:47` | `static int net_drv_present(void)` |
| `net_drv_send` | function | `net/net.c:37` | `static int net_drv_send(const unsigned char *frame, unsigned len)` |
| `net_get16` | function | `net/net.c:68` | `static unsigned short net_get16(const unsigned char *p)` |
| `net_get32` | function | `net/net.c:72` | `static unsigned int net_get32(const unsigned char *p)` |
| `net_get_addrs` | function | `net/net.c:1187` | `void net_get_addrs(unsigned char mac_out[NET_ETH_ALEN], unsigned char ip_out[4])` |
| `net_icmp_rx` | function | `net/net.c:347` | `static void net_icmp_rx(const unsigned char *ip, unsigned len)` |
| `net_init` | function | `net/net.c:1225` | `void net_init(void)` |
| `net_ip_send` | function | `net/net.c:171` | `static int net_ip_send(const unsigned char *dip, unsigned char proto,                        cons...` |
| `net_listen` | function | `net/net.c:891` | `int net_listen(unsigned short port)` |
| `net_open` | function | `net/net.c:850` | `int net_open(void)` |
| `net_parse_ip` | function | `net/net.c:1140` | `static int net_parse_ip(const char *text, unsigned char ip[4])` |
| `net_ping` | function | `net/net.c:376` | `static int net_ping(const unsigned char ip[4])` |
| `net_put16` | function | `net/net.c:56` | `static void net_put16(unsigned char *p, unsigned short v)` |
| `net_put32` | function | `net/net.c:61` | `static void net_put32(unsigned char *p, unsigned int v)` |
| `net_recv` | function | `net/net.c:870` | `int net_recv(int fd, char *buf, int len)` |

Next: [SYMBOLS_p10.md](SYMBOLS_p10.md)
