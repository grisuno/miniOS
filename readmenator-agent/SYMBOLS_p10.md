# Symbols (page 10 of 26)
Previous: [SYMBOLS_p9.md](SYMBOLS_p9.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `syscall_trace_shown` | function | `kernel/syscalls.c:1113` | `unsigned long syscall_trace_shown(void)` |
| `syscall_trace_verbose_enabled` | function | `kernel/syscalls.c:1111` | `long syscall_trace_verbose_enabled(void)` |
| `syscall_trace_verbose_set` | function | `kernel/syscalls.c:1112` | `void syscall_trace_verbose_set(int on)` |
| `trace_hint_print` | function | `kernel/syscalls.c:3086` | `static void trace_hint_print(long n, int kind, const char *path,                              lon...` |
| `trace_is_noisy` | function | `kernel/syscalls.c:3018` | `static int trace_is_noisy(long n)` |
| `unchanged` | function | `kernel/syscalls.c:1128` | `* unchanged (same code, same order of checks). Numbers >= 200 that * overlap real Linux ABIs stay in the switch as...` |
| `untouched` | function | `kernel/syscalls.c:138` | `* child untouched (caller refuses fail-closed). */ int kfd_view_copy(proc_t *child, proc_t *parent)` |
| `user_range_ok` | function | `kernel/syscalls.c:3197` | `int user_range_ok(unsigned long p, unsigned long len)` |
| `view` | function | `kernel/syscalls.c:502` | `* view (same as the `clear` builtin). Anything else is -EINVAL. Each  * out-word is range-checked...` |
| `vma_free_cover` | function | `kernel/syscalls.c:2087` | `static vma_node_t *vma_free_cover(unsigned long base, unsigned long len)` |
| `vma_live_first_overlap` | function | `kernel/syscalls.c:1901` | `static vma_node_t *vma_live_first_overlap(unsigned long base, unsigned long end)` |
| `vma_live_overlap` | function | `kernel/syscalls.c:2106` | `static int vma_live_overlap(unsigned long base, unsigned long len)` |
| `vma_live_remainder` | function | `kernel/syscalls.c:1918` | `static int vma_live_remainder(unsigned long base, unsigned long len,         int file, int ino, u...` |
| `wall_us_now` | function | `kernel/syscalls.c:255` | `unsigned long wall_us_now(void)` |
| `LINUX_ECHILD` | macro | `kernel/syscalls_proc.c:197` | `#define LINUX_ECHILD` |
| `LINUX_EINVAL` | macro | `kernel/syscalls_proc.c:198` | `#define LINUX_EINVAL` |
| `LINUX_ESRCH` | macro | `kernel/syscalls_proc.c:199` | `#define LINUX_ESRCH` |
| `LINUX_SIGKILL` | macro | `kernel/syscalls_proc.c:194` | `#define LINUX_SIGKILL` |
| `LINUX_STATUS_CODE` | macro | `kernel/syscalls_proc.c:196` | `#define LINUX_STATUS_CODE` |
| `LINUX_STATUS_SHIFT` | macro | `kernel/syscalls_proc.c:195` | `#define LINUX_STATUS_SHIFT` |
| `LINUX_WNOHANG` | macro | `kernel/syscalls_proc.c:193` | `#define LINUX_WNOHANG` |
| `groups` | function | `kernel/syscalls_proc.c:213` | `* groups (pid 0 and < -1) are not modelled and wait for any child. */ long sys_linux_wait4(long a...` |
| `kill` | function | `kernel/syscalls_proc.c:192` | `* historic kill (SIGKILL), -N is signal N (a seccomp kill is -SIGSYS). */ #define LINUX_WNOHANG  ...` |
| `sig` | function | `kernel/syscalls_proc.c:245` | `* the target as killed by sig (wait4 reports WTERMSIG);` |
| `state` | function | `kernel/syscalls_proc.c:5` | `* touches only scheduler state (current_pid, procs[], do_* / * seccomp_* / yield) plus the kernel-wide user_range_ok...` |
| `sys_linux_clone` | function | `kernel/syscalls_proc.c:83` | `long sys_linux_clone(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_execve` | function | `kernel/syscalls_proc.c:99` | `long sys_linux_execve(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_exit` | function | `kernel/syscalls_proc.c:184` | `long sys_linux_exit(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_fork` | function | `kernel/syscalls_proc.c:89` | `long sys_linux_fork(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_getpid` | function | `kernel/syscalls_proc.c:75` | `long sys_linux_getpid(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_gettid` | function | `kernel/syscalls_proc.c:259` | `long sys_linux_gettid(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_kill` | function | `kernel/syscalls_proc.c:248` | `long sys_linux_kill(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_vfork` | function | `kernel/syscalls_proc.c:94` | `long sys_linux_vfork(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_yield` | function | `kernel/syscalls_proc.c:66` | `long sys_linux_yield(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_clone` | function | `kernel/syscalls_proc.c:18` | `long sys_minios_clone(long flags, long newsp, long a3, long a4, long a5, long a6)` |
| `sys_minios_nice` | function | `kernel/syscalls_proc.c:53` | `long sys_minios_nice(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_seccomp` | function | `kernel/syscalls_proc.c:37` | `long sys_minios_seccomp(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_thread_spawn` | function | `kernel/syscalls_proc.c:24` | `long sys_minios_thread_spawn(long a1, long a2, long a3, long a4, long a5, long a6)` |
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
| `FB_OFFSET` | macro | `kernel/vga_fb.c:1629` | `#define FB_OFFSET(x,y)` |
| `GFX_CURSOR_FOLLOW_TICKS` | macro | `kernel/vga_fb.c:521` | `#define GFX_CURSOR_FOLLOW_TICKS` |
| `GFX_CURSOR_IDLE_TICKS` | macro | `kernel/vga_fb.c:515` | `#define GFX_CURSOR_IDLE_TICKS` |
| `GFX_KEEP_BYTES` | macro | `kernel/vga_fb.c:489` | `#define GFX_KEEP_BYTES` |
| `GFX_PROG_LEN` | macro | `kernel/vga_fb.c:573` | `#define GFX_PROG_LEN` |
| `GFX_SRC_IDX` | macro | `kernel/vga_fb.c:487` | `#define GFX_SRC_IDX` |
| `GFX_SRC_RGB` | macro | `kernel/vga_fb.c:488` | `#define GFX_SRC_RGB` |
| `LG_LINE` | macro | `kernel/vga_fb.c:296` | `#define LG_LINE(a)` |
| `TB_GFX_TITLE_MAX` | macro | `kernel/vga_fb.c:2459` | `#define TB_GFX_TITLE_MAX` |
| `WIN_DEF_COLS` | macro | `kernel/vga_fb.c:899` | `#define WIN_DEF_COLS` |
| `WIN_DEF_ROWS` | macro | `kernel/vga_fb.c:900` | `#define WIN_DEF_ROWS` |
| `WIN_DEF_X` | macro | `kernel/vga_fb.c:901` | `#define WIN_DEF_X` |
| `WIN_DEF_Y` | macro | `kernel/vga_fb.c:902` | `#define WIN_DEF_Y` |
| `WM_ELINE_SZ` | macro | `kernel/vga_fb.c:931` | `#define WM_ELINE_SZ` |
| `WM_MAX_TERMS` | macro | `kernel/vga_fb.c:930` | `#define WM_MAX_TERMS` |
| `act_nrows` | function | `kernel/vga_fb.c:334` | `static int act_nrows(void)` |
| `alone` | function | `kernel/vga_fb.c:1341` | `* window alone (an unfocused graphics window minimizes to the taskbar,  * exactly like the hidden...` |
| `app` | function | `kernel/vga_fb.c:1158` | `* a gfx child spawned from another gfx app (file -> vedit) keeps the * terminal focused, so its keys and wheel keep...` |
| `buffer` | function | `kernel/vga_fb.c:2812` | `* owns the buffer (indices reset, render reads an empty ring). */ void term_clear(void)` |
| `ci_eq` | function | `kernel/vga_fb.c:612` | `static int ci_eq(const char *a, const char *b)` |
| `command` | function | `kernel/vga_fb.c:4082` | `* its launch command (config-driven, covers apps that never set a window * title);` |
| `compositions` | function | `kernel/vga_fb.c:133` | `* compositions (an ISR tick composing inside a syscall composition) draw * into the same shadow and leave the...` |
| `content` | function | `kernel/vga_fb.c:1215` | `* windows would share content (same prompt/output on both) and a park  * would alias src == dst. ...` |
| `coordinates` | function | `kernel/vga_fb.c:745` | `* windows keep the exact historical coordinates (including outside the * window);` |
| `desktop_shortcuts_draw` | function | `kernel/vga_fb.c:3993` | `void desktop_shortcuts_draw(void)` |
| `desktop_shortcuts_hit_test` | function | `kernel/vga_fb.c:4108` | `const char *desktop_shortcuts_hit_test(int mx, int my)` |
| `desktop_shortcuts_load` | function | `kernel/vga_fb.c:3767` | `void desktop_shortcuts_load(void)` |
| `directly` | function | `kernel/vga_fb.c:2149` | `* RGB sources pack directly (quantized to the wallpaper cube in 8-bit). */ static void gfx_scale_...` |
| `disp_clamp` | function | `kernel/vga_fb.c:345` | `static void disp_clamp(void)` |
| `dock_bounce_counts` | function | `kernel/vga_fb.c:3875` | `void dock_bounce_counts(unsigned long *kicks, unsigned long *paints)` |
| `dock_bounce_elapsed` | function | `kernel/vga_fb.c:3891` | `static unsigned long dock_bounce_elapsed(void)` |
| `dock_bounce_live` | function | `kernel/vga_fb.c:3899` | `static int dock_bounce_live(void)` |
| `dock_click_count` | function | `kernel/vga_fb.c:3885` | `void dock_click_count(unsigned long *edges)` |
| `dock_hover_index` | function | `kernel/vga_fb.c:3848` | `static int dock_hover_index(int mx, int my)` |
| `dock_label_px` | function | `kernel/vga_fb.c:3733` | `static int dock_label_px(const struct desktop_shortcut *sc)` |
| `dock_paint_hover` | function | `kernel/vga_fb.c:4051` | `static void dock_paint_hover(int hover)` |
| `dock_paint_icons` | function | `kernel/vga_fb.c:3957` | `static void dock_paint_icons(int hover)` |
| `dock_pending_active` | function | `kernel/vga_fb.c:3949` | `int dock_pending_active(void)` |
| `draw_scrollbar` | function | `kernel/vga_fb.c:2717` | `static void draw_scrollbar(void)` |
| `draw_speaker_icon` | function | `kernel/vga_fb.c:2492` | `static void draw_speaker_icon(int x, int y, uint8_t color)` |
| `draw_title_win` | function | `kernel/vga_fb.c:2430` | `static void draw_title_win(int idx, int focused)` |
| `escapes` | function | `kernel/vga_fb.c:2881` | `* swallowing them here keeps the escapes (which the serial side needs)      * from printing as li...` |
| `fb_bytes_per_pixel` | function | `kernel/vga_fb.c:117` | `int fb_bytes_per_pixel(void)` |
| `fb_compose_begin` | function | `kernel/vga_fb.c:221` | `static int fb_compose_begin(void)` |
| `fb_compose_end` | function | `kernel/vga_fb.c:234` | `static void fb_compose_end(int owner)` |
| `fb_copy_bytes` | function | `kernel/vga_fb.c:151` | `static void fb_copy_bytes(volatile void *dst, const volatile void *src, unsigned long n)` |
| `fb_fill_run` | function | `kernel/vga_fb.c:1824` | `static void fb_fill_run(int x, int y, int n, unsigned long px)` |
| `fb_fill_u32` | function | `kernel/vga_fb.c:169` | `static void fb_fill_u32(volatile void *dst, unsigned int v, unsigned long n)` |
| `fb_frame_bytes` | function | `kernel/vga_fb.c:183` | `static unsigned long fb_frame_bytes(void)` |
| `fb_glyph` | function | `kernel/vga_fb.c:1912` | `static const uint8_t *fb_glyph(unsigned char c)` |
| `fb_pack_idx` | function | `kernel/vga_fb.c:1707` | `static unsigned long fb_pack_idx(unsigned idx)` |
| `fb_present_shadow` | function | `kernel/vga_fb.c:210` | `static void fb_present_shadow(void)` |
| `fb_read_packed` | function | `kernel/vga_fb.c:1743` | `unsigned long fb_read_packed(int x, int y)` |
| `fb_read_row_packed` | function | `kernel/vga_fb.c:1802` | `void fb_read_row_packed(int x, int y, unsigned int *dst, int n)` |
| `fb_shadow_ready` | function | `kernel/vga_fb.c:189` | `static int fb_shadow_ready(void)` |
| `fb_write_packed` | function | `kernel/vga_fb.c:1723` | `void fb_write_packed(int x, int y, unsigned long rgb)` |
| `fb_write_row_packed` | function | `kernel/vga_fb.c:1772` | `void fb_write_row_packed(int x, int y, const unsigned int *src, int n)` |
| `first` | function | `kernel/vga_fb.c:419` | `* screen ever showing it whole first (the old flash-then-melt). */ static unsigned int *fx_start_...` |
| `flag` | function | `kernel/vga_fb.c:496` | `* is the minimized flag (the program keeps running, nothing composites);` |
| `from` | function | `kernel/vga_fb.c:3188` | `* leaving returns to the view it came from (floating or tiled). Returns  * 0 on success, -1 witho...` |
| `gfx_animate` | function | `kernel/vga_fb.c:3090` | `static void gfx_animate(const wm_gfxview_rect_t *from, const wm_gfxview_rect_t *to,              ...` |
| `gfx_compose` | function | `kernel/vga_fb.c:2285` | `static void gfx_compose(const volatile uint8_t *src, int kind, int sw, int sh,                   ...` |
| `gfx_covers_screen` | function | `kernel/vga_fb.c:544` | `static int gfx_covers_screen(void)` |
| `gfx_cursor_follow_idle` | function | `kernel/vga_fb.c:2367` | `static void gfx_cursor_follow_idle(void)` |
| `gfx_drop_focus` | function | `kernel/vga_fb.c:3177` | `static void gfx_drop_focus(int source)` |
| `gfx_float_frame` | function | `kernel/vga_fb.c:715` | `static int gfx_float_frame(wm_gfxview_rect_t *out)` |
| `gfx_keep_save` | function | `kernel/vga_fb.c:550` | `static void gfx_keep_save(const volatile uint8_t *src, int kind, int sw, int sh)` |
| `gfx_letterbox` | function | `kernel/vga_fb.c:2254` | `static void gfx_letterbox(const wm_gfxview_t *v)` |
| `gfx_present` | function | `kernel/vga_fb.c:2351` | `static void gfx_present(const volatile uint8_t *bb, int kind, int sw, int sh)` |
| `gfx_prog_icon` | function | `kernel/vga_fb.c:625` | `static const uint8_t *gfx_prog_icon(void)` |
| `gfx_snap` | function | `kernel/vga_fb.c:3309` | `static void gfx_snap(int zone)` |
| `gfx_task_icon` | function | `kernel/vga_fb.c:4087` | `static const uint8_t *gfx_task_icon(void)` |
| `gfx_taskbar_rect` | function | `kernel/vga_fb.c:3140` | `static void gfx_taskbar_rect(wm_gfxview_rect_t *r)` |
| `gfx_title` | function | `kernel/vga_fb.c:2273` | `static void gfx_title(const wm_gfxview_t *v)` |
| `gfx_transition` | function | `kernel/vga_fb.c:939` | `static void gfx_transition(const wm_gfxview_rect_t *from, int from_titled);` |
| `gfx_view_cfg` | function | `kernel/vga_fb.c:535` | `static wm_gfxview_config_t gfx_view_cfg(void)` |
| `gfx_view_for` | function | `kernel/vga_fb.c:689` | `static int gfx_view_for(int sw, int sh, wm_gfxview_t *v)` |
| `gfx_view_in_rect` | function | `kernel/vga_fb.c:3071` | `static void gfx_view_in_rect(const wm_gfxview_rect_t *r, int titled, wm_gfxview_t *v)` |
| `gfx_view_publish` | function | `kernel/vga_fb.c:701` | `static void gfx_view_publish(const wm_gfxview_t *v)` |
| `icon_decode` | function | `kernel/vga_fb.c:3671` | `static const uint8_t *icon_decode(const char *path)` |
| `icon_embedded` | function | `kernel/vga_fb.c:3651` | `static const uint8_t *icon_embedded(const char *name)` |
| `icon_embedded_rgba` | function | `kernel/vga_fb.c:3705` | `static const uint8_t *icon_embedded_rgba(const uint8_t *idx)` |
| `icon_nearest` | function | `kernel/vga_fb.c:3635` | `static int icon_nearest(int r, int g, int b)` |
| `letterbox` | function | `kernel/vga_fb.c:500` | `* present to repaint chrome plus letterbox (after a desktop redraw or a * view change);` |
| `lg_get` | function | `kernel/vga_fb.c:305` | `static const char *lg_get(int i)` |
| `lg_push` | function | `kernel/vga_fb.c:312` | `static void lg_push(const char *line, int len)` |
| `line` | function | `kernel/vga_fb.c:2872` | `* display stale bytes left over from a longer previous line (e.g. the prompt  * would show the ta...` |
| `line_at` | function | `kernel/vga_fb.c:363` | `static const char *line_at(int abs, int *off)` |
| `line_nrows` | function | `kernel/vga_fb.c:327` | `static int line_nrows(int len)` |
| `mouse_apply_wheel` | function | `kernel/vga_fb.c:4148` | `static void mouse_apply_wheel(int wheel, int step)` |
| `mouse_drag_gfx` | function | `kernel/vga_fb.c:4172` | `static void mouse_drag_gfx(const wm_geom_config_t *gcfg, int mx, int my)` |
| `mouse_drag_term` | function | `kernel/vga_fb.c:4224` | `static void mouse_drag_term(const wm_geom_config_t *gcfg, int win_w, int mx, int my, int gfx_cursor)` |
| `mouse_focus_topmost` | function | `kernel/vga_fb.c:4122` | `static int mouse_focus_topmost(int mx, int my)` |
| `mouse_scrollbar` | function | `kernel/vga_fb.c:4247` | `static void mouse_scrollbar(const wm_geom_config_t *gcfg, int mx, int my)` |
| `path` | function | `kernel/vga_fb.c:4296` | `* present path (blit_gfx_buf) is the sole cursor painter. The tick * used to share the sprite state with it and...` |
| `pipe_field` | function | `kernel/vga_fb.c:3617` | `static const char *pipe_field(const char *line, int idx, char *buf, int buflen)` |
| `pointer` | function | `kernel/vga_fb.c:4169` | `* tiled window floats it at native size under the pointer (the grab point * keeps its relative position along the...` |
| `render_blank_row` | function | `kernel/vga_fb.c:2752` | `static void render_blank_row(int vrow)` |
| `render_row` | function | `kernel/vga_fb.c:2762` | `static void render_row(int vrow, int abs)` |
| `shcmd_base` | function | `kernel/vga_fb.c:595` | `static void shcmd_base(const char *cmd, char *out, unsigned long cap)` |
| `shortcut_cell_left` | function | `kernel/vga_fb.c:3760` | `static int shortcut_cell_left(int i)` |
| `shortcut_draw_scaled` | function | `kernel/vga_fb.c:3823` | `static void shortcut_draw_scaled(const struct desktop_shortcut *sc,                              ...` |
| `shortcuts_layout` | function | `kernel/vga_fb.c:3742` | `static void shortcuts_layout(void)` |
| `state` | function | `kernel/vga_fb.c:4409` | `* ignores the button state (the arming press is consumed) and settles      * once on expiry, so t...` |
| `taskbar` | function | `kernel/vga_fb.c:2101` | `* minimize hides the app to the taskbar (it never closes it), maximize  * toggles true fullscreen...` |
| `taskbar_handle_click` | function | `kernel/vga_fb.c:2657` | `static void taskbar_handle_click(int mx, int my)` |
| `taskbar_layout` | function | `kernel/vga_fb.c:2461` | `static void taskbar_layout(void)` |
| `taskbar_render` | function | `kernel/vga_fb.c:2501` | `static void taskbar_render(void)` |
| `taskbar_theme_cycle` | function | `kernel/vga_fb.c:2617` | `static void taskbar_theme_cycle(void)` |
| `taskbar_tick` | function | `kernel/vga_fb.c:2580` | `static void taskbar_tick(void)` |
| `term_close_default` | function | `kernel/vga_fb.c:3342` | `static void term_close_default(void)` |
| `term_finish_layout` | function | `kernel/vga_fb.c:3426` | `static void term_finish_layout(void)` |
| `term_max_cols` | function | `kernel/vga_fb.c:3417` | `static int term_max_cols(void)` |
| `term_max_rows` | function | `kernel/vga_fb.c:3421` | `static int term_max_rows(void)` |
| `term_recalc` | function | `kernel/vga_fb.c:2404` | `static void term_recalc(void)` |
| `term_render` | function | `kernel/vga_fb.c:2797` | `static void term_render(void)` |
| `term_render_active` | function | `kernel/vga_fb.c:2829` | `static void term_render_active(void)` |
| `term_toggle_fullscreen` | function | `kernel/vga_fb.c:3262` | `static void term_toggle_fullscreen(void)` |
| `term_toggle_minimize` | function | `kernel/vga_fb.c:3285` | `static void term_toggle_minimize(void)` |
| `termwin_t` | struct | `kernel/vga_fb.c:941` | `` |
| `text_px` | function | `kernel/vga_fb.c:2009` | `static void text_px(int px, int py, const char *s, uint8_t fg, uint8_t bg)` |
| `title` | function | `kernel/vga_fb.c:2511` | `* 8px row plus its title (bright when focused). The hint line * starts after it instead of underneath. */ const...` |
| `total_rows` | function | `kernel/vga_fb.c:337` | `static int total_rows(void)` |
| `tw_hit` | function | `kernel/vga_fb.c:1586` | `static int tw_hit(int i, int mx, int my)` |
| `tw_park` | function | `kernel/vga_fb.c:998` | `static void tw_park(int i)` |
| `tw_select` | function | `kernel/vga_fb.c:1088` | `static void tw_select(int i)` |
| `tw_unpark` | function | `kernel/vga_fb.c:1028` | `static void tw_unpark(int i)` |
| `vga_fb_act_empty` | function | `kernel/vga_fb.c:1526` | `int vga_fb_act_empty(void)` |
| `vga_fb_blit_gfx_window` | function | `kernel/vga_fb.c:2380` | `void vga_fb_blit_gfx_window(void)` |
| `vga_fb_blit_nk_rgb_window` | function | `kernel/vga_fb.c:2395` | `void vga_fb_blit_nk_rgb_window(void)` |
| `vga_fb_blit_nk_window` | function | `kernel/vga_fb.c:2389` | `void vga_fb_blit_nk_window(void)` |
| `vga_fb_boot_config` | function | `kernel/vga_fb.c:90` | `void vga_fb_boot_config(void)` |
| `vga_fb_char` | function | `kernel/vga_fb.c:1984` | `void vga_fb_char(int col, int row, char c, uint8_t fg, uint8_t bg)` |
| `vga_fb_clear` | function | `kernel/vga_fb.c:1943` | `void vga_fb_clear(void)` |
| `vga_fb_clear_prompt` | function | `kernel/vga_fb.c:1535` | `void vga_fb_clear_prompt(void)` |
| `vga_fb_close_active` | function | `kernel/vga_fb.c:3358` | `int vga_fb_close_active(void)` |
| `vga_fb_draw_desktop` | function | `kernel/vga_fb.c:2976` | `void vga_fb_draw_desktop(void)` |
| `vga_fb_focus_event` | function | `kernel/vga_fb.c:983` | `const wm_notify_event_t *vga_fb_focus_event(void)` |
| `vga_fb_focus_get` | function | `kernel/vga_fb.c:1100` | `int vga_fb_focus_get(void)` |
| `vga_fb_focus_id` | function | `kernel/vga_fb.c:1182` | `int vga_fb_focus_id(int id)` |
| `vga_fb_focus_next` | function | `kernel/vga_fb.c:1117` | `void vga_fb_focus_next(void)` |
| `vga_fb_focus_report` | function | `kernel/vga_fb.c:989` | `void vga_fb_focus_report(int before, int source)` |
| `vga_fb_gfx_cursor_draw` | function | `kernel/vga_fb.c:773` | `static void vga_fb_gfx_cursor_draw(void)` |
| `vga_fb_gfx_cursor_erase` | function | `kernel/vga_fb.c:763` | `static void vga_fb_gfx_cursor_erase(void)` |
| `vga_fb_gfx_map_mouse` | function | `kernel/vga_fb.c:748` | `void vga_fb_gfx_map_mouse(int *x, int *y)` |
| `vga_fb_gfx_origin` | function | `kernel/vga_fb.c:731` | `void vga_fb_gfx_origin(int *x, int *y)` |
| `vga_fb_gfx_set_hidden` | function | `kernel/vga_fb.c:3222` | `int vga_fb_gfx_set_hidden(int hide)` |
| `vga_fb_gfx_view_name` | function | `kernel/vga_fb.c:3250` | `const char *vga_fb_gfx_view_name(void)` |
| `vga_fb_hide_text_cursor` | function | `kernel/vga_fb.c:2952` | `void vga_fb_hide_text_cursor(void)` |
| `vga_fb_init` | function | `kernel/vga_fb.c:4515` | `void vga_fb_init(void)` |
| `vga_fb_is_fullscreen` | function | `kernel/vga_fb.c:3304` | `int vga_fb_is_fullscreen(void)` |
| `vga_fb_is_minimized` | function | `kernel/vga_fb.c:3303` | `int vga_fb_is_minimized(void)` |
| `vga_fb_layout_cycle` | function | `kernel/vga_fb.c:1307` | `void vga_fb_layout_cycle(void)` |
| `vga_fb_layout_get` | function | `kernel/vga_fb.c:1323` | `int vga_fb_layout_get(void)` |
| `vga_fb_layout_name` | function | `kernel/vga_fb.c:1329` | `const char *vga_fb_layout_name(void)` |
| `vga_fb_layout_set` | function | `kernel/vga_fb.c:1296` | `int vga_fb_layout_set(int mode)` |
| `vga_fb_list_windows` | function | `kernel/vga_fb.c:1468` | `void vga_fb_list_windows(void)` |
| `vga_fb_mouse_init` | function | `kernel/vga_fb.c:4487` | `void vga_fb_mouse_init(void)` |
| `vga_fb_mouse_tick` | function | `kernel/vga_fb.c:4285` | `void vga_fb_mouse_tick(void)` |
| `vga_fb_move_terminal` | function | `kernel/vga_fb.c:3372` | `void vga_fb_move_terminal(int dx, int dy)` |
| `vga_fb_note_prompt` | function | `kernel/vga_fb.c:1530` | `void vga_fb_note_prompt(void)` |
| `vga_fb_nterms_get` | function | `kernel/vga_fb.c:1101` | `int vga_fb_nterms_get(void)` |
| `vga_fb_park_line` | function | `kernel/vga_fb.c:1556` | `void vga_fb_park_line(const char *b, int p)` |
| `vga_fb_pixel` | function | `kernel/vga_fb.c:1933` | `void vga_fb_pixel(int x, int y, uint8_t color)` |
| `vga_fb_pixel_rgb` | function | `kernel/vga_fb.c:1968` | `void vga_fb_pixel_rgb(int x, int y, uint8_t r, uint8_t g, uint8_t b)` |
| `vga_fb_prompt_live` | function | `kernel/vga_fb.c:1549` | `int vga_fb_prompt_live(void)` |
| `vga_fb_prompted` | function | `kernel/vga_fb.c:1540` | `int vga_fb_prompted(void)` |
| `vga_fb_ps2_owner` | function | `kernel/vga_fb.c:2081` | `int vga_fb_ps2_owner(int pid)` |
| `vga_fb_puts_term` | function | `kernel/vga_fb.c:2938` | `void vga_fb_puts_term(const char *s)` |
| `vga_fb_read_rgb` | function | `kernel/vga_fb.c:1767` | `unsigned long vga_fb_read_rgb(int x, int y)` |
| `vga_fb_rect` | function | `kernel/vga_fb.c:1953` | `void vga_fb_rect(int x, int y, int w, int h, uint8_t color)` |
| `vga_fb_rect_rgb` | function | `kernel/vga_fb.c:1977` | `void vga_fb_rect_rgb(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b)` |
| `vga_fb_reset_default` | function | `kernel/vga_fb.c:3480` | `void vga_fb_reset_default(void)` |
| `vga_fb_resize` | function | `kernel/vga_fb.c:3460` | `void vga_fb_resize(int dcols, int drows)` |
| `vga_fb_set_gfx_mode` | function | `kernel/vga_fb.c:638` | `void vga_fb_set_gfx_mode(int on)` |
| `vga_fb_set_gfx_palette` | function | `kernel/vga_fb.c:1692` | `void vga_fb_set_gfx_palette(const unsigned char *pal)` |
| `vga_fb_set_gfx_program` | function | `kernel/vga_fb.c:576` | `void vga_fb_set_gfx_program(const char *name)` |
| `vga_fb_set_palette` | function | `kernel/vga_fb.c:1859` | `static void vga_fb_set_palette(void)` |
| `vga_fb_snap_window` | function | `kernel/vga_fb.c:3432` | `void vga_fb_snap_window(int zone)` |
| `vga_fb_str` | function | `kernel/vga_fb.c:1998` | `void vga_fb_str(int col, int row, const char *s, uint8_t fg, uint8_t bg)` |
| `vga_fb_text_cursor` | function | `kernel/vga_fb.c:2944` | `void vga_fb_text_cursor(int col)` |
| `vga_fb_theme_name` | function | `kernel/vga_fb.c:2596` | `int vga_fb_theme_name(char *dst, int cap)` |
| `vga_fb_toggle_fullscreen` | function | `kernel/vga_fb.c:3274` | `void vga_fb_toggle_fullscreen(void)` |
| `vga_fb_toggle_minimize` | function | `kernel/vga_fb.c:3295` | `void vga_fb_toggle_minimize(void)` |
| `vga_fb_unpark_line` | function | `kernel/vga_fb.c:1571` | `int vga_fb_unpark_line(char *b, int *p)` |
| `vga_fb_wait_tick` | function | `kernel/vga_fb.c:4276` | `void vga_fb_wait_tick(void)` |
| `wall_level` | function | `kernel/vga_fb.c:1850` | `static int wall_level(int v)` |
| `wallpaper_draw` | function | `kernel/vga_fb.c:3591` | `static void wallpaper_draw(void)` |
| `wallpaper_ensure` | function | `kernel/vga_fb.c:3534` | `static void wallpaper_ensure(void)` |
| `wallpaper_rect` | function | `kernel/vga_fb.c:4020` | `static void wallpaper_rect(int x0, int y0, int w, int h)` |
| `wallpaper_usable` | function | `kernel/vga_fb.c:3586` | `static int wallpaper_usable(void)` |
| `wm_buttons_hit` | function | `kernel/vga_fb.c:2061` | `static int wm_buttons_hit(int mx, int my, int win_x, int win_y, int win_w)` |
| `wm_clear_close` | function | `kernel/vga_fb.c:2077` | `void wm_clear_close(void)` |
| `wm_close_pending` | function | `kernel/vga_fb.c:2076` | `int wm_close_pending(void)` |
| `wm_drag_reset` | function | `kernel/vga_fb.c:69` | `static void wm_drag_reset(void)` |
| `wm_draw_buttons` | function | `kernel/vga_fb.c:2035` | `static void wm_draw_buttons(int px, int py, int win_w, uint8_t fg, uint8_t bg)` |
| `wm_emit_focus_moved` | function | `kernel/vga_fb.c:971` | `static void wm_emit_focus_moved(int before, int source)` |
| `wm_event_cfg` | function | `kernel/vga_fb.c:60` | `static wm_event_config_t wm_event_cfg(void)` |
| `wm_focus_cursor_sync` | function | `kernel/vga_fb.c:964` | `static void wm_focus_cursor_sync(const wm_notify_event_t *e)` |
| `wm_geom_cfg` | function | `kernel/vga_fb.c:49` | `static wm_geom_config_t wm_geom_cfg(void)` |
| `wm_gfx_focus_sync` | function | `kernel/vga_fb.c:1163` | `static void wm_gfx_focus_sync(int on)` |
| `wm_gfx_mode_active` | function | `kernel/vga_fb.c:2078` | `int wm_gfx_mode_active(void)` |
| `wm_init_once` | function | `kernel/vga_fb.c:1063` | `static void wm_init_once(void)` |
| `wm_snapshot_state` | function | `kernel/vga_fb.c:1104` | `static void wm_snapshot_state(wm_focus_state_t *st)` |
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

Next: [SYMBOLS_p11.md](SYMBOLS_p11.md)
