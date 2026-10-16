# API (page 6 of 21)
Previous: [API_p5.md](API_p5.md)

## headers/wm_layout.h
Imported by: `kernel/shell.c`, `kernel/vga_fb.c`, `tests/test_wm.c`
- `wm_layout_mode_name` (function) `headers/wm_layout.h:57` `static inline const char *wm_layout_mode_name(int mode)` -- /** Docstring: Default layout matching the legacy two terminal split. #define WM_LAYOUT_CONFIG_DEFAULT { 0, 4, 2...
- `wm_layout_mode_valid` (function) `headers/wm_layout.h:76` `static inline int wm_layout_mode_valid(int mode)` -- case WM_LAYOUT_BSP: return "bsp"; case WM_LAYOUT_CASCADE: return "cascade"; case WM_LAYOUT_FIBONACCI: return...
- `wm_layout_clamp_cell` (function) `headers/wm_layout.h:82` `static inline int wm_layout_clamp_cell(wm_layout_cell_t *cell, int max_cols, int max_rows)` -- case WM_LAYOUT_FULLSCREEN: return "fullscreen"; default: return 0; } } /** Docstring: True when mode is a selectable...
- `wm_layout_fullscreen_cell` (function) `headers/wm_layout.h:118` `static inline int wm_layout_fullscreen_cell(int max_cols, int max_rows, wm_layout_cell_t *out)` -- } if (cell->rows < 1) { cell->rows = 1; } if (cell->x + cell->cols > max_cols) { cell->cols = max_cols - cell->x; }...
- `wm_layout_compute_tile` (function) `headers/wm_layout.h:135` `static inline int wm_layout_compute_tile(const wm_layout_window_t *wins, int nwin, int max_cols, ...` -- return 0; } if (max_cols <= 0 || max_rows <= 0) { return 0; } out->x = 0; out->y = 0; out->cols = max_cols...
- `wm_layout_compute_bsp` (function) `headers/wm_layout.h:182` `static inline int wm_layout_compute_bsp(const wm_layout_window_t *wins, int nwin, int max_cols, i...` -- } base = max_rows / nwin; rem = max_rows - base * nwin; for (i = 0; i < nwin; i++) { out[i].x = 0; out[i].y = i *...
- `wm_layout_compute_cascade` (function) `headers/wm_layout.h:250` `static inline int wm_layout_compute_cascade(const wm_layout_config_t *cfg, const wm_layout_window...` -- } out[i].x = rx; out[i].y = ry; out[i].cols = rw; out[i].rows = half; out[i].fullscreen = 0; ry = ry + half; rh = rh...
- `wm_layout_compute_fibonacci` (function) `headers/wm_layout.h:285` `static inline int wm_layout_compute_fibonacci(const wm_layout_config_t *cfg, const wm_layout_wind...` -- out[i].cols = max_cols - ox; out[i].rows = max_rows - oy; out[i].fullscreen = 0; if (out[i].cols < 1) { out[i].cols...
- `wm_layout_compute` (function) `headers/wm_layout.h:361` `static inline int wm_layout_compute(const wm_layout_config_t *cfg, const wm_layout_window_t *wins...` -- } out[i].x = rx; out[i].y = ry; out[i].cols = rw; out[i].rows = cut; out[i].fullscreen = 0; ry = ry + cut; rh = rh...
- `wm_layout_same` (function) `headers/wm_layout.h:443` `static inline int wm_layout_same(const wm_layout_cell_t *a, const wm_layout_cell_t *b, int n)` -- } if (n != nc) { return 0; } for (i = 0; i < nc; i++) { if (!wm_layout_clamp_cell(&cells[i], max_cols, max_rows)) {...

## headers/wm_notify.h
Imported by: `headers/vga_fb.h`, `kernel/shell.c`, `kernel/vga_fb.c`, `tests/test_notify.c`
- `wm_notify_reset` (function) `headers/wm_notify.h:51` `static inline void wm_notify_reset(wm_notify_bus_t *bus)` -- /** Docstring: Focus listener, runs synchronously inside emit. typedef void (*wm_notify_handler_t)(const...
- `wm_notify_subscribe` (function) `headers/wm_notify.h:66` `static inline int wm_notify_subscribe(wm_notify_bus_t *bus,
                                     ...` -- { int i; if (bus == 0) return; for (i = 0; i < WM_NOTIFY_MAX_HANDLERS; i++) bus->handlers[i] = 0; bus->count = 0...
- `wm_notify_emit` (function) `headers/wm_notify.h:76` `static inline void wm_notify_emit(wm_notify_bus_t *bus,
                                  const w...` -- bus->has_event = 0; } /** Docstring: Register one listener, -1 when full or null. static inline int...
- `wm_notify_last` (function) `headers/wm_notify.h:90` `static inline const wm_notify_event_t *wm_notify_last(
    const wm_notify_bus_t *bus)` -- static inline void wm_notify_emit(wm_notify_bus_t *bus, const wm_notify_event_t *event) { int i; if (bus == 0 ||...
- `wm_notify_src_name` (function) `headers/wm_notify.h:98` `static inline const char *wm_notify_src_name(int source)` -- } bus->last = *event; bus->has_event = 1; } /** Docstring: Last emitted event, 0 when none was ever emitted. static...

## headers/wm_render.h
Depends on: `headers/wm_window.h`
Imported by: `kernel/vga_fb.c`, `tests/test_wm.c`
- `wm_build_render_plan` (function) `headers/wm_render.h:39` `static inline int wm_build_render_plan(const wm_render_config_t *cfg, const int *present, int nte...` -- typedef struct { wm_layer_t layer; int id; } wm_render_item_t; /** Docstring: Centralized render pipeline...

## headers/wm_tiling.h
Imported by: `kernel/vga_fb.c`, `tests/test_wm.c`
- `wm_tile_layout` (function) `headers/wm_tiling.h:22` `static inline int wm_tile_layout(const int *present, int nterms, int gfx_active, int max_cols, in...` -- #ifndef WM_TILING_H #define WM_TILING_H /** Docstring: Terminal cell in character units. typedef struct { int x; int...

## headers/wm_window.h
Depends on: `headers/wm_geom.h`
Imported by: `headers/wm_focus.h`, `headers/wm_render.h`, `kernel/vga_fb.c`, `tests/test_wm.c`
- `wm_window_active` (function) `headers/wm_window.h:41` `static inline int wm_window_active(const wm_window_t *w)` -- /** Docstring: Unified window descriptor in framebuffer pixels. typedef struct { wm_window_kind_t kind; int id; int...
- `wm_window_rect` (function) `headers/wm_window.h:47` `static inline wm_rect_t wm_window_rect(const wm_window_t *w)` -- int y; int w; int h; int present; int minimized; } wm_window_t; /** Docstring: True when the window can receive...
- `wm_window_contains` (function) `headers/wm_window.h:58` `static inline int wm_window_contains(const wm_window_t *w, int px, int py)` -- } /** Docstring: Rectangle covering the whole window including decorations. static inline wm_rect_t...
- `wm_window_title_hits` (function) `headers/wm_window.h:68` `static inline int wm_window_title_hits(const wm_geom_config_t *cfg, const wm_window_t *w, int px,...` -- return r; } /** Docstring: True when point px,py hits the window body or decorations. static inline int...
- `wm_focus_next_id` (function) `headers/wm_window.h:77` `static inline int wm_focus_next_id(const int *present, int nterms, int gfx_active, int focus)` -- } return wm_rect_contains(&r, px, py); } /** Docstring: True when point px,py hits the window title bar. static...
- `wm_paint_order` (function) `headers/wm_window.h:114` `static inline int wm_paint_order(const int *present, int nterms, int focus, int *order, int cap)` -- return focus; } for (k = 0; k < n; k++) { if (ids[k] == focus) { at = k; } } if (at < 0) { return ids[0]; } return...

## headers/zip.h
Imported by: `kernel/shell.c`, `kernel/syscalls.c`
- `miniz` (function) `headers/zip.h:6` `* * The shell builtins over miniz (see zip.c) are declared here so kernel.c's * shell dispatcher can route the...`
- `shell_cmd_zip` (function) `headers/zip.h:15` `void shell_cmd_zip(int argc, char **argv);`

## kernel.c
Depends on: `headers/abi.h`, `headers/arch/x86/boot/bootdefs.h`, `headers/arch/x86/cpu_setup.h`, `headers/arch/x86/msr.h`, `headers/block.h`, `headers/drivers/usbblk.h`, `headers/drivers/usbhid.h`, `headers/drivers/virtio_blk.h`, `headers/drivers/xhci.h`, `headers/ide.h`, `headers/minifs.h`, `headers/net.h`, `headers/pcache.h`, `headers/sb16.h`, `headers/sched.h`, `headers/smp.h`, `headers/syscall_asm.h`, `headers/vga_fb.h`
- `table` (function) `kernel.c:104` `* Symbol table (for resolving program references) * ================================================================...`
- `syscall_init` (function) `kernel.c:117` `void syscall_init(void)`
- `ksyscall` (function) `kernel.c:130` `extern long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6);`
- `kstack` (function) `kernel.c:146` `* Reading gs:8 instead resolves every thread to the wrong kstack (0 on * the BSP, 1 on APs): harmless while a single...`
- `ms` (function) `kernel.c:185` `* 0 ms (TSC ticks since power-on divided down, still monotonic);`
- `bootlog_mark` (function) `kernel.c:192` `void bootlog_mark(const char *name)`
- `bootlog_report` (function) `kernel.c:199` `void bootlog_report(void)`
- `size` (function) `kernel.c:253` `* image size (see kernel.ld);`
- `tables` (function) `kernel.c:275` `* tables (already built above) for its uncached register window and the
     * heap for its rings...`

## kernel/abi.c
Depends on: `headers/abi.h`
- `abi_parse_num` (function) `kernel/abi.c:20` `static int abi_parse_num(const char **pp, const char *end, unsigned long *out)` -- order, junk, overflow, missing newline) fails closed as BAD_FORMAT.
- `abi_verify` (function) `kernel/abi.c:38` `int abi_verify(const char *text, long version, unsigned long checksum)` -- return 0; while (p < end && *p >= '0' && *p <= '9') { unsigned digit = (unsigned)(*p - '0'); if (v >...
- `abi_check_manifest` (function) `kernel/abi.c:74` `int abi_check_manifest(void)` -- p += 2; if (!abi_parse_num(&p, end, &c)) return ABI_BAD_FORMAT; if (p + 1 != end || *p != '\n') return...

## kernel/batch.c
Depends on: `headers/batch.h`
- `batch_exec` (function) `kernel/batch.c:19` `long batch_exec(const batch_op_t *ops, long *results, int count,
                int *completed, ...` -- Docstring: Run ops in order, storing one result per index.

## kernel/clip.c
- `clip_set` (function) `kernel/clip.c:25` `int clip_set(const char *data, unsigned long len)` -- Docstring: Replace the clipboard with len bytes from data.
- `clip_clear` (function) `kernel/clip.c:48` `void clip_clear(void)` -- Docstring: Copy the clipboard into out (cap bytes).
- `clip_len_get` (function) `kernel/clip.c:55` `int clip_len_get(void)` -- Docstring: Current length, or -1 when empty.

## kernel/console.c
Depends on: `headers/sched.h`, `headers/vga_fb.h`
- `vga_get_x` (function) `kernel/console.c:18` `int vga_get_x(void)`
- `vga_get_y` (function) `kernel/console.c:19` `int vga_get_y(void)`
- `vga_set_xy` (function) `kernel/console.c:20` `void vga_set_xy(int x, int y)`
- `vga_get_color` (function) `kernel/console.c:21` `char vga_get_color(void)`
- `vga_offset` (function) `kernel/console.c:23` `static inline unsigned vga_offset(int x, int y)`
- `vga_clear` (function) `kernel/console.c:25` `void vga_clear(void)`
- `vga_set_cursor` (function) `kernel/console.c:36` `void vga_set_cursor(int x, int y)`
- `vga_scroll` (function) `kernel/console.c:56` `void vga_scroll(void)`
- `vga_newline` (function) `kernel/console.c:75` `void vga_newline(void)`
- `vga_cursor_enable` (function) `kernel/console.c:81` `void vga_cursor_enable(int on)`
- `vga_raw_space` (function) `kernel/console.c:88` `static void vga_raw_space(void)`
- `redir_grow` (function) `kernel/console.c:110` `static int redir_grow(void)`
- `redirect_active` (function) `kernel/console.c:120` `int redirect_active(void)`
- `redirect_putc` (function) `kernel/console.c:122` `static int redirect_putc(char c)`
- `redirect_suspend` (function) `kernel/console.c:129` `int redirect_suspend(void)`
- `redirect_resume` (function) `kernel/console.c:135` `void redirect_resume(int was)`
- `redirect_begin` (function) `kernel/console.c:139` `int redirect_begin(void)`
- `redirect_commit` (function) `kernel/console.c:147` `int redirect_commit(const char *path, int append_mode)`
- `redirect_pending` (function) `kernel/console.c:185` `unsigned long redirect_pending(void)` -- Docstring: Bytes waiting in the capture, 0 when idle or overflowed.
- `redirect_take_into` (function) `kernel/console.c:196` `unsigned long redirect_take_into(char *dst, unsigned long cap,
        unsigned long *len_out)` -- Docstring: Drain the capture into the caller's arena memory instead of a fresh heap block.
- `redirect_discard` (function) `kernel/console.c:216` `void redirect_discard(void)` -- Docstring: Drop the capture without any allocation.
- `vga_putc` (function) `kernel/console.c:223` `void vga_putc(char c)`
- `vga_puts` (function) `kernel/console.c:267` `void vga_puts(const char *s)`
- `register_libc_symbols` (function) `kernel/console.c:271` `void register_libc_symbols(void)`

## kernel/console_in.c
Depends on: `headers/drivers/kbd.h`, `headers/drivers/usbhid.h`, `headers/drivers/xhci.h`, `headers/kernel/console_in.h`, `headers/pipe.h`, `headers/vga_fb.h`
- `console_stdin_push` (function) `kernel/console_in.c:32` `int console_stdin_push(const char *data, unsigned long len)` -- Pipeline stdin override (see console_in.h): heap buffer served ahead of every live source while set.
- `console_stdin_clear` (function) `kernel/console_in.c:46` `void console_stdin_clear(void)` -- int console_stdin_push(const char *data, unsigned long len) { unsigned long i; if (!data || len == 0u || len >...
- `console_stdin_active` (function) `kernel/console_in.c:56` `int console_stdin_active(void)` -- Docstring: True while a pipeline stdin buffer is installed (drained * or not).
- `pb_empty` (function) `kernel/console_in.c:60` `static int pb_empty(void)`
- `pb_count` (function) `kernel/console_in.c:61` `static int pb_count(void)`
- `pb_push_back` (function) `kernel/console_in.c:62` `static void pb_push_back(unsigned char c)`
- `pb_push_front` (function) `kernel/console_in.c:67` `static void pb_push_front(unsigned char c)`
- `pb_pop` (function) `kernel/console_in.c:72` `static int pb_pop(void)`
- `pb_peek` (function) `kernel/console_in.c:78` `static int pb_peek(void)`
- `console_ungetc` (function) `kernel/console_in.c:85` `void console_ungetc(unsigned char c)` -- Docstring: Push one byte back into the console FIFO; the next * console_getc/console_peek serves it first.
- `console_poll_usb` (function) `kernel/console_in.c:93` `static void console_poll_usb(void)` -- Docstring: Service the polled USB input path: drain the controller's event ring, then take one report from each...
- `console_ps2_live` (function) `kernel/console_in.c:106` `static int console_ps2_live(void)` -- Docstring: True when the PS/2 data port should be read.
- `raw_blocking_getc` (function) `kernel/console_in.c:118` `static int raw_blocking_getc(void)` -- Docstring: Next raw byte (kbd queue, then serial, then USB, then PS/2) without touching the pushback FIFO; blocks...
- `raw_try_getc` (function) `kernel/console_in.c:139` `static int raw_try_getc(void)` -- } console_poll_usb(); if (!kbd_q_empty()) return kbd_q_pop(); if (console_ps2_live()) { int c = kbd_read(); if (c >=...
- `ESC` (function) `kernel/console_in.c:157` `* The bound keeps a bare ESC (never completed into a sequence) from
 * hanging the reader. */
#de...`
- `consume_page_after_esc` (function) `kernel/console_in.c:178` `static int consume_page_after_esc(void)` -- Docstring: Called after an ESC byte has been read.
- `console_getc` (function) `kernel/console_in.c:205` `int console_getc(void)` -- Docstring: Blocking read from either the PS/2 keyboard or COM1 serial line.
- `console_peek` (function) `kernel/console_in.c:233` `int console_peek(void)` -- Docstring: Next buffered byte without consuming it, or -1 when nothing is available right now.
- `console_raw_try` (function) `kernel/console_in.c:246` `int console_raw_try(void)` -- Docstring: Raw console multiplexer for the GETC_RAW syscall.
- `console_raw_get` (function) `kernel/console_in.c:250` `int console_raw_get(void)`
- `console_job_try` (function) `kernel/console_in.c:257` `int console_job_try(void)` -- Docstring: GETC_RAW source for ring-3 background jobs.
- `console_job_get` (function) `kernel/console_in.c:267` `int console_job_get(void)` -- Docstring: GETC_RAW source for ring-3 background jobs.
- `scrollback_render` (function) `kernel/console_in.c:283` `static void scrollback_render(int voff, int total, const unsigned char *saved)`
- `sb_next` (function) `kernel/console_in.c:311` `static int sb_next(void)` -- Docstring: Reads the next scrollback key event: PageUp/PageDown navigate; any other key (or a non-page escape...
- `scrollback_view` (function) `kernel/console_in.c:321` `static void scrollback_view(int initial_dir)`

## kernel/cvm_host.c
- `n_strcmp` (function) `kernel/cvm_host.c:22` `static int64_t n_strcmp(void *vm, int ac, uint64_t *av)`
- `n_strncmp` (function) `kernel/cvm_host.c:28` `static int64_t n_strncmp(void *vm, int ac, uint64_t *av)`
- `n_strcpy` (function) `kernel/cvm_host.c:35` `static int64_t n_strcpy(void *vm, int ac, uint64_t *av)`
- `n_strncpy` (function) `kernel/cvm_host.c:41` `static int64_t n_strncpy(void *vm, int ac, uint64_t *av)`
- `n_memcpy` (function) `kernel/cvm_host.c:48` `static int64_t n_memcpy(void *vm, int ac, uint64_t *av)`
- `n_memset` (function) `kernel/cvm_host.c:55` `static int64_t n_memset(void *vm, int ac, uint64_t *av)`
- `n_memmove` (function) `kernel/cvm_host.c:61` `static int64_t n_memmove(void *vm, int ac, uint64_t *av)`
- `n_memcmp` (function) `kernel/cvm_host.c:68` `static int64_t n_memcmp(void *vm, int ac, uint64_t *av)`
- `n_strchr` (function) `kernel/cvm_host.c:75` `static int64_t n_strchr(void *vm, int ac, uint64_t *av)`
- `n_strstr` (function) `kernel/cvm_host.c:81` `static int64_t n_strstr(void *vm, int ac, uint64_t *av)`
- `n_malloc` (function) `kernel/cvm_host.c:88` `static int64_t n_malloc(void *vm, int ac, uint64_t *av)`
- `n_free` (function) `kernel/cvm_host.c:93` `static int64_t n_free(void *vm, int ac, uint64_t *av)`
- `n_calloc` (function) `kernel/cvm_host.c:98` `static int64_t n_calloc(void *vm, int ac, uint64_t *av)`
- `n_realloc` (function) `kernel/cvm_host.c:106` `static int64_t n_realloc(void *vm, int ac, uint64_t *av)`
- `n_exit` (function) `kernel/cvm_host.c:114` `static int64_t n_exit(void *vm, int ac, uint64_t *av)`
- `n_fopen` (function) `kernel/cvm_host.c:121` `static int64_t n_fopen(void *vm, int ac, uint64_t *av)`
- `n_fclose` (function) `kernel/cvm_host.c:128` `static int64_t n_fclose(void *vm, int ac, uint64_t *av)`
- `n_fread` (function) `kernel/cvm_host.c:134` `static int64_t n_fread(void *vm, int ac, uint64_t *av)`
- `n_fwrite` (function) `kernel/cvm_host.c:141` `static int64_t n_fwrite(void *vm, int ac, uint64_t *av)`
- `n_fseek` (function) `kernel/cvm_host.c:148` `static int64_t n_fseek(void *vm, int ac, uint64_t *av)`
- `n_ftell` (function) `kernel/cvm_host.c:154` `static int64_t n_ftell(void *vm, int ac, uint64_t *av)`
- `n_rewind` (function) `kernel/cvm_host.c:160` `static int64_t n_rewind(void *vm, int ac, uint64_t *av)`
- `n_fputs` (function) `kernel/cvm_host.c:167` `static int64_t n_fputs(void *vm, int ac, uint64_t *av)`
- `n_fputc` (function) `kernel/cvm_host.c:173` `static int64_t n_fputc(void *vm, int ac, uint64_t *av)`
- `n_fgetc` (function) `kernel/cvm_host.c:179` `static int64_t n_fgetc(void *vm, int ac, uint64_t *av)`
- `n_ungetc` (function) `kernel/cvm_host.c:185` `static int64_t n_ungetc(void *vm, int ac, uint64_t *av)`
- `n_fflush` (function) `kernel/cvm_host.c:191` `static int64_t n_fflush(void *vm, int ac, uint64_t *av)`
- `n_putchar` (function) `kernel/cvm_host.c:197` `static int64_t n_putchar(void *vm, int ac, uint64_t *av)`
- `n_write` (function) `kernel/cvm_host.c:204` `static int64_t n_write(void *vm, int ac, uint64_t *av)`
- `n_read` (function) `kernel/cvm_host.c:213` `static int64_t n_read(void *vm, int ac, uint64_t *av)`
- `n_puts` (function) `kernel/cvm_host.c:228` `static int64_t n_puts(void *vm, int ac, uint64_t *av)`
- `n_atol` (function) `kernel/cvm_host.c:236` `static int64_t n_atol(void *vm, int ac, uint64_t *av)`
- `n_strtol` (function) `kernel/cvm_host.c:249` `static int64_t n_strtol(void *vm, int ac, uint64_t *av)`
- `n_stderr_addr` (function) `kernel/cvm_host.c:262` `static int64_t n_stderr_addr(void *vm, int ac, uint64_t *av)`
- `n_stdout_addr` (function) `kernel/cvm_host.c:267` `static int64_t n_stdout_addr(void *vm, int ac, uint64_t *av)`
- `n_stdin_addr` (function) `kernel/cvm_host.c:272` `static int64_t n_stdin_addr(void *vm, int ac, uint64_t *av)`
- `kout_char` (function) `kernel/cvm_host.c:277` `static void kout_char(void *ctx, char c)`
- `kout_uint` (function) `kernel/cvm_host.c:283` `static void kout_uint(void *ctx, unsigned long long v, int base, int upper)`
- `kformat` (function) `kernel/cvm_host.c:296` `static void kformat(void *ctx, const char *fmt, uint64_t *argv, int argc)`
- `n_fprintf` (function) `kernel/cvm_host.c:362` `static int64_t n_fprintf(void *vm, int ac, uint64_t *av)`
- `n_printf` (function) `kernel/cvm_host.c:369` `static int64_t n_printf(void *vm, int ac, uint64_t *av)`
- `n_sprintf` (function) `kernel/cvm_host.c:376` `static int64_t n_sprintf(void *vm, int ac, uint64_t *av)`
- `n_snprintf` (function) `kernel/cvm_host.c:384` `static int64_t n_snprintf(void *vm, int ac, uint64_t *av)`
- `register_host_natives` (function) `kernel/cvm_host.c:392` `static void register_host_natives(CvmState *vm)`
- `cvm_main` (function) `kernel/cvm_host.c:437` `int cvm_main(int argc, char **argv)`

## kernel/ed25519.c
Depends on: `headers/sign.h`
- `ed_rotr` (function) `kernel/ed25519.c:84` `static ed_u64 ed_rotr(ed_u64 x, unsigned n)`
- `ed_sha_block` (function) `kernel/ed25519.c:89` `static void ed_sha_block(ed_sha *c, const unsigned char *p)` -- /** Docstring: Compressed base point: 0x58 then thirty-one 0x66. static const unsigned char ed_braw[32] = { 0x58...
- `ed_sha512_init` (function) `kernel/ed25519.c:147` `void ed_sha512_init(ed_sha *c)` -- b = a; a = t1 + t2; } c->h[0] += a; c->h[1] += b; c->h[2] += cc; c->h[3] += d; c->h[4] += e; c->h[5] += f; c->h[6]...
- `ed_sha512_update` (function) `kernel/ed25519.c:162` `void ed_sha512_update(ed_sha *c, const unsigned char *data, unsigned long len)` -- c->h[0] = 0x6a09e667f3bcc908ULL; c->h[1] = 0xbb67ae8584caa73bULL; c->h[2] = 0x3c6ef372fe94f82bULL; c->h[3] =...
- `ed_sha512_final` (function) `kernel/ed25519.c:188` `void ed_sha512_final(ed_sha *c, unsigned char out[64])` -- if ((unsigned long)take > left) take = (unsigned)left; for (k = 0; k < take; k++) c->buf[c->used + k] = data[i + k]...
- `ed_fe_copy` (function) `kernel/ed25519.c:214` `static void ed_fe_copy(ed_fe *r, const ed_fe *a)` -- for (k = 0; k < 8u; k++) c->buf[112u + k] = (unsigned char)(c->hi >> (56u - 8u * k)); for (k = 0; k < 8u; k++)...
- `ed_fe_zero` (function) `kernel/ed25519.c:222` `static void ed_fe_zero(ed_fe *r)` -- for (s = 0; s < 8u; s++) out[b + s] = (unsigned char)(c->h[i] >> (56u - 8u * s)); } } /** Docstring: Copy one field...
- `ed_fe_one` (function) `kernel/ed25519.c:230` `static void ed_fe_one(ed_fe *r)` -- r->v[1] = a->v[1]; r->v[2] = a->v[2]; r->v[3] = a->v[3]; } /** Docstring: Zero one field element. static void...
- `ed_fe_cmov` (function) `kernel/ed25519.c:238` `static void ed_fe_cmov(ed_fe *r, const ed_fe *b, unsigned flag)` -- r->v[1] = 0; r->v[2] = 0; r->v[3] = 0; } /** Docstring: One as a field element. static void ed_fe_one(ed_fe *r) {...
- `ed_fe_ge` (function) `kernel/ed25519.c:247` `static unsigned ed_fe_ge(const ed_fe *a, const ed_fe *b)` -- r->v[2] = 0; r->v[3] = 0; } /** Docstring: Constant-time select between two field elements. static void...
- `ed_fe_rawsub` (function) `kernel/ed25519.c:258` `static void ed_fe_rawsub(ed_fe *r, const ed_fe *a, const ed_fe *b)` -- } /** Docstring: 1 when a is at least b as 256-bit integers, else 0. static unsigned ed_fe_ge(const ed_fe *a, const...
- `ed_fe_add` (function) `kernel/ed25519.c:280` `static void ed_fe_add(ed_fe *r, const ed_fe *a, const ed_fe *b)` -- ed_u64 d2 = a->v[2] - bw1; ed_u64 c3 = (d2 > a->v[2]) ?
- `ed_fe_sub` (function) `kernel/ed25519.c:302` `static void ed_fe_sub(ed_fe *r, const ed_fe *a, const ed_fe *b)` -- c = (__uint128_t)a->v[2] + b->v[2] + (ed_u64)(c >> 64); t.v[2] = (ed_u64)c; c = (__uint128_t)a->v[3] + b->v[3] +...
- `ed_fe_fold` (function) `kernel/ed25519.c:344` `static void ed_fe_fold(ed_fe *r, ed_u64 w[8])` -- q.v[2] = ed_qq[2]; q.v[3] = ed_qq[3]; c = (__uint128_t)t.v[0] + q.v[0]; t.v[0] = (ed_u64)c; c = (__uint128_t)t.v[1]...
- `ed_fe_mul` (function) `kernel/ed25519.c:387` `static void ed_fe_mul(ed_fe *r, const ed_fe *a, const ed_fe *b)` -- back.v[0] = w[4] * 38u; back.v[1] = 0; back.v[2] = 0; back.v[3] = 0; ed_fe_add(&t, &t, &back); if (ed_fe_ge(&t, &q))...
- `ed_fe_sq` (function) `kernel/ed25519.c:416` `static void ed_fe_sq(ed_fe *r, const ed_fe *a)` -- } carry = acc; k = i + 4u; while (carry && k < 8u) { __uint128_t s = (__uint128_t)t[k] + (ed_u64)carry; t[k] =...
- `ed_fe_pow` (function) `kernel/ed25519.c:421` `static void ed_fe_pow(ed_fe *r, const ed_fe *a, const unsigned char *bits, unsigned nbits)` -- t[k] = (ed_u64)s; carry = s >> 64; k++; } } ed_fe_fold(r, t); } /** Docstring: r holds a squared mod q. static void...
- `ed_fe_inv` (function) `kernel/ed25519.c:438` `static void ed_fe_inv(ed_fe *r, const ed_fe *a)` -- Docstring: r holds one over a mod q via Fermat, exponent q minus 2.  * q minus 2 keeps bits 0, 1, 3 and 5..254 set...
- `ed_fe_frombytes` (function) `kernel/ed25519.c:449` `static void ed_fe_frombytes(ed_fe *r, const unsigned char b[32])` -- Docstring: r holds one over a mod q via Fermat, exponent q minus 2.  * q minus 2 keeps bits 0, 1, 3 and 5..254 set...
- `ed_fe_tobytes` (function) `kernel/ed25519.c:461` `static void ed_fe_tobytes(unsigned char b[32], const ed_fe *a)` -- /** Docstring: Load 32 little-endian bytes into a field element. static void ed_fe_frombytes(ed_fe *r, const...
- `ed_fe_eq` (function) `kernel/ed25519.c:470` `static unsigned ed_fe_eq(const ed_fe *a, const ed_fe *b)` -- r->v[i] = w; } } /** Docstring: Store a field element as 32 little-endian bytes. static void ed_fe_tobytes(unsigned...
- `ed_bytes_lt_q` (function) `kernel/ed25519.c:477` `static unsigned ed_bytes_lt_q(const unsigned char b[32])` -- unsigned k; for (i = 0; i < 4u; i++) for (k = 0; k < 8u; k++) b[i * 8u + k] = (unsigned char)(a->v[i] >> (8u * k))...
- `ed_scalar_lt_l` (function) `kernel/ed25519.c:495` `static unsigned ed_scalar_lt_l(const unsigned char b[32])` -- i--; if (i == 31u) qb = 0x7f; else if (i == 0u) qb = 0xed; else qb = 0xff; if (b[i] != qb) return (b[i] < qb) ?
- `ed_rem_sub` (function) `kernel/ed25519.c:517` `static void ed_rem_sub(ed_u64 r[5], const ed_u64 a[5], const ed_u64 b[5])` -- lb = (unsigned char)(ed_ll[1] >> (8u * (i - 8u))); else if (i < 24u) lb = 0; else if (i < 31u) lb = 0; else lb =...
- `ed_rem_ge` (function) `kernel/ed25519.c:545` `static unsigned ed_rem_ge(const ed_u64 a[5], const ed_u64 b[5])` -- ed_u64 c5 = (d3 > a[3]) ?
- `ed_mod_l` (function) `kernel/ed25519.c:557` `static void ed_mod_l(ed_fe *r, const unsigned char h[64])` -- /** Docstring: 1 when the 320-bit a holds at least b, else 0. static unsigned ed_rem_ge(const ed_u64 a[5], const...
- `ed_ge_copy` (function) `kernel/ed25519.c:596` `static void ed_ge_copy(ed_ge *r, const ed_ge *a)` -- if (ed_rem_ge(rem, lv)) { ed_rem_sub(tmp, rem, lv); for (nk = 0; nk < 5u; nk++) rem[nk] = tmp[nk]; } } } r->v[0] =...
- `ed_ge_cmov` (function) `kernel/ed25519.c:604` `static void ed_ge_cmov(ed_ge *r, const ed_ge *b, unsigned flag)` -- r->v[1] = rem[1]; r->v[2] = rem[2]; r->v[3] = rem[3]; } /** Docstring: Copy one extended point. static void...
- `ed_ge_add` (function) `kernel/ed25519.c:612` `static void ed_ge_add(ed_ge *r, const ed_ge *p, const ed_ge *q, const ed_fe *d2)` -- ed_fe_copy(&r->y, &a->y); ed_fe_copy(&r->z, &a->z); ed_fe_copy(&r->t, &a->t); } /** Docstring: Constant-time point...
- `ed_ge_double` (function) `kernel/ed25519.c:644` `static void ed_ge_double(ed_ge *r, const ed_ge *p)` -- ed_fe_mul(&c, &t0, d2); ed_fe_add(&t0, &p->z, &p->z); ed_fe_mul(&d, &t0, &q->z); ed_fe_sub(&e, &b, &a)...
- `ed_ge_scalarmult` (function) `kernel/ed25519.c:686` `static void ed_ge_scalarmult(ed_ge *r, const ed_ge *p, const unsigned char s[32],
               ...` -- ed_fe nb; ed_fe_zero(&na); ed_fe_zero(&nb); ed_fe_sub(&na, &na, &a); ed_fe_sub(&nb, &nb, &b); ed_fe_add(&h, &na...
- `ed_curve_d` (function) `kernel/ed25519.c:706` `static void ed_curve_d(ed_fe *d)` -- ed_fe_one(&q.y); ed_fe_one(&q.z); ed_fe_zero(&q.t); for (i = 254; i >= 0; i--) { unsigned bit = (unsigned)((s[i >>...
- `ed25519_verify` (function) `kernel/ed25519.c:810` `int ed25519_verify(const unsigned char sig[64], const unsigned char *msg,
                   unsi...` -- Docstring: Verify an Ed25519 signature, 1 valid else 0 fail-closed.

## kernel/editor.c
Depends on: `headers/editor.h`, `headers/shell.h`
- `edit_alloc` (function) `kernel/editor.c:38` `static EditBuf *edit_alloc(const char *fname)`
- `edit_free` (function) `kernel/editor.c:55` `static void edit_free(EditBuf *e)`
- `edit_load` (function) `kernel/editor.c:61` `static int edit_load(EditBuf *e)`
- `edit_save` (function) `kernel/editor.c:99` `static int edit_save(EditBuf *e)`
- `edit_print` (function) `kernel/editor.c:113` `static void edit_print(EditBuf *e, int idx)`
- `edit_list` (function) `kernel/editor.c:123` `static void edit_list(EditBuf *e, int start, int end)` -- List a (possibly empty) range [start, end], both 1-based inclusive.
- `edit_set_line` (function) `kernel/editor.c:135` `static int edit_set_line(EditBuf *e, int idx, const char *text)`
- `edit_insert` (function) `kernel/editor.c:144` `static int edit_insert(EditBuf *e, int idx, const char *text)`
- `edit_delete` (function) `kernel/editor.c:154` `static int edit_delete(EditBuf *e, int idx)`
- `edit_line_cstr` (function) `kernel/editor.c:166` `static void edit_line_cstr(EditLine *l, char *out)` -- Copy a line into a NUL-terminated scratch buffer (lines are otherwise * stored length-prefixed without a terminator).
- `edit_search` (function) `kernel/editor.c:171` `static void edit_search(EditBuf *e, const char *needle)`
- `edit_status` (function) `kernel/editor.c:188` `static void edit_status(EditBuf *e)`
- `edit_usage` (function) `kernel/editor.c:196` `static void edit_usage(void)`
- `edit_refuse_save` (function) `kernel/editor.c:207` `static int edit_refuse_save(EditBuf *e)` -- A buffer that did not hold the whole file must never be written back: * saving it would drop the part that was never...
- `edit_arg_line` (function) `kernel/editor.c:213` `static int edit_arg_line(int argc, char **argv, EditBuf *e, int *out)`
- `edit_loop` (function) `kernel/editor.c:224` `static void edit_loop(EditBuf *e)`
- `shell_cmd_edit` (function) `kernel/editor.c:329` `void shell_cmd_edit(int argc, char **argv)`

## kernel/exec.c
Depends on: `headers/arch/x86/boot/bootdefs.h`, `headers/arch/x86/msr.h`, `headers/drivers/kbd.h`, `headers/proc_sec.h`, `headers/sched.h`, `headers/vga_fb.h`
- `vga_mode_set` (function) `kernel/exec.c:61` `void vga_mode_set(int on)`
- `vga_mode_is_active` (function) `kernel/exec.c:62` `int  vga_mode_is_active(void)`
- `vga_gfx_ran_set` (function) `kernel/exec.c:63` `void vga_gfx_ran_set(int on)`
- `k_user_fault_return` (function) `kernel/exec.c:66` `void k_user_fault_return(void)` -- VGA mode tracking: set/cleared by k_exec_user and k_run_rel when a * graphics program owns the display. static int...
- `setup_user_stack` (function) `kernel/exec.c:83` `unsigned long *setup_user_stack(char *sbase, unsigned long ssize,
                               ...`
- `k_run_rel` (function) `kernel/exec.c:233` `int k_run_rel(prog_entry_t entry, int argc, char **argv)`
- `kexit` (function) `kernel/exec.c:284` `void kexit(int code)`

## kernel/futex.c
Depends on: `headers/futex.h`, `headers/sync.h`
- `futex_hash` (function) `kernel/futex.c:23` `static unsigned long futex_hash(unsigned long uaddr)`
- `futex_bucket` (function) `kernel/futex.c:31` `static futex_bucket_t *futex_bucket(unsigned long uaddr)`
- `futex_init` (function) `kernel/futex.c:36` `void futex_init(void)` -- static unsigned long futex_hash(unsigned long uaddr) { unsigned long word = uaddr >> 2; word ^= word >> 16; word *=...
- `futex_unlink_locked` (function) `kernel/futex.c:50` `static void futex_unlink_locked(futex_bucket_t *b, int pid)` -- Unlink pid from bucket b's queue (bucket lock held).
- `futex_forget` (function) `kernel/futex.c:76` `void futex_forget(int pid)` -- Docstring: Drop pid from the futex queues (see futex.h).
- `futex_linux_cmd` (function) `kernel/futex.c:128` `int futex_linux_cmd(long op)` -- futex_table.awaited[cur->pid] = uaddr; if (b->head == WQ_NONE) { b->head = cur->pid; b->tail = cur->pid; } else {...
- `futex_timeout_remaining_us` (function) `kernel/futex.c:139` `long futex_timeout_remaining_us(int cmd, long sec, long nsec, unsigned long now_us)` -- } /** Docstring: Decode a Linux futex(2) op to WAIT/WAKE. int futex_linux_cmd(long op) { long cmd; if (op < 0)...
- `futex_wake` (function) `kernel/futex.c:158` `long futex_wake(unsigned long uaddr, int n)` -- Docstring: Wake up to n sleepers waiting on uaddr.

## kernel/klog.c
- `klog_set_level` (function) `kernel/klog.c:29` `void klog_set_level(log_level_t level)`
- `klog_set_subsys_level` (function) `kernel/klog.c:33` `void klog_set_subsys_level(log_subsystem_t subsys, log_level_t level)`
- `klog_disable` (function) `kernel/klog.c:38` `void klog_disable(void)`
- `klog_enable` (function) `kernel/klog.c:39` `void klog_enable(void)`
- `klog` (function) `kernel/klog.c:41` `void klog(log_level_t level, log_subsystem_t subsys,
          const char *fmt, ...)`
- `klog_hexdump` (function) `kernel/klog.c:119` `void klog_hexdump(log_level_t level, log_subsystem_t subsys,
                  const void *data, ...`

## kernel/ldso_parse.c
Depends on: `headers/ldso.h`
Imported by: `tests/test_ldso.c`
- `ldso_rd16` (function) `kernel/ldso_parse.c:18` `static unsigned ldso_rd16(const unsigned char *p)`
- `ldso_rd32` (function) `kernel/ldso_parse.c:22` `static unsigned long ldso_rd32(const unsigned char *p)`
- `ldso_rd64` (function) `kernel/ldso_parse.c:27` `static unsigned long long ldso_rd64(const unsigned char *p)`
- `ldso_slice` (function) `kernel/ldso_parse.c:32` `static int ldso_slice(const unsigned char *file, unsigned long long fsize,
        unsigned long ...`
- `ldso_valid_ehdr` (function) `kernel/ldso_parse.c:40` `static int ldso_valid_ehdr(const unsigned char *file,
        unsigned long long fsize)`
- `ldso_vaddr_to_offset` (function) `kernel/ldso_parse.c:54` `int ldso_vaddr_to_offset(const unsigned char *file,
        unsigned long long fsize, unsigned lo...`
- `ldso_segments` (function) `kernel/ldso_parse.c:86` `int ldso_segments(const unsigned char *file, unsigned long long fsize,
        LdsoSeg *segs, uns...`
- `ldso_find_dynamic` (function) `kernel/ldso_parse.c:120` `int ldso_find_dynamic(const unsigned char *file, unsigned long long fsize,
        unsigned long ...`
- `ldso_scan_dynamic` (function) `kernel/ldso_parse.c:150` `int ldso_scan_dynamic(const unsigned char *file, unsigned long long fsize,
        unsigned long ...`
- `ldso_sym_count` (function) `kernel/ldso_parse.c:213` `int ldso_sym_count(const unsigned char *file, unsigned long long fsize,
        unsigned long lon...`
- `ldso_copy_str` (function) `kernel/ldso_parse.c:227` `int ldso_copy_str(const unsigned char *file, unsigned long long fsize,
        unsigned long long...`
- `ldso_name_eq` (function) `kernel/ldso_parse.c:250` `static int ldso_name_eq(const unsigned char *tab, unsigned long long strsz,
        unsigned long...`
- `ldso_sym_lookup` (function) `kernel/ldso_parse.c:263` `int ldso_sym_lookup(const unsigned char *file, unsigned long long fsize,
        unsigned long lo...`
- `ldso_rela_count` (function) `kernel/ldso_parse.c:296` `int ldso_rela_count(const LdsoDynInfo *info, unsigned *nrela)`
- `ldso_read_rela` (function) `kernel/ldso_parse.c:309` `int ldso_read_rela(const unsigned char *file, unsigned long long fsize,
        unsigned long lon...`
- `ldso_basename` (function) `kernel/ldso_parse.c:331` `void ldso_basename(char *out, const char *src)`

## kernel/loader.c
Depends on: `headers/ldso.h`, `headers/minifs.h`, `headers/pcache.h`, `headers/sched.h`, `headers/sign.h`, `headers/vga_fb.h`
- `elf_name_copy` (function) `kernel/loader.c:114` `static void elf_name_copy(char *out, unsigned out_cap, const char *tab,
                         ...`
- `elf_load_fail` (function) `kernel/loader.c:128` `static void elf_load_fail(void *base, void **sec_addrs, const char *why)`
- `elf_load` (function) `kernel/loader.c:136` `void *elf_load(void *data, unsigned size, void **base_out)`
- `inodes` (function) `kernel/loader.c:381` `* Pseudo inodes (LDSO_INO_BASE + slot) keep registry pages apart from * MiniFS inodes in the shared cache. No unload...`
- `ldso_pseudo_stat` (function) `kernel/loader.c:402` `int ldso_pseudo_stat(int ino, unsigned long *size_out)`
- `ldso_pseudo_read` (function) `kernel/loader.c:416` `int ldso_pseudo_read(int ino, void *dst, unsigned long off, unsigned len)`
- `ldso_read_file` (function) `kernel/loader.c:441` `static int ldso_read_file(const char *name, unsigned char **out,
        unsigned *size_out)` -- Read a whole library file by DT_NEEDED name: exact path first, then the basename, ramdisk before MiniFS (the shell's...
- `ldso_ensure_slot` (function) `kernel/loader.c:483` `static int ldso_ensure_slot(const char *needed, int *slot_out)` -- Resolve a DT_NEEDED name to a registry slot, loading and reserving on first use.
- `consistent` (function) `kernel/loader.c:579` `* consistent (the next exec forgets them, a dying window frees them),
 * and only reports. */
sta...`
- `images` (function) `kernel/loader.c:790` `* Static images (no dynamic section, or none needed) return 0 at * once, so the legacy paths never observe a...`
- `ldso_bind_into` (function) `kernel/loader.c:794` `int ldso_bind_into(void *data, unsigned size, unsigned long base,
        unsigned long cr3, vma_...` -- Bind one executable image with DT_NEEDED libraries: map every library into the target window, then resolve each...
- `apply_exec_relocs` (function) `kernel/loader.c:984` `static void apply_exec_relocs(void *data, unsigned size, unsigned long base,
                    ...`
- `elf_note_pad` (function) `kernel/loader.c:1072` `static unsigned long elf_note_pad(unsigned long n)` -- case R_X86_64_GLOB_DAT: case R_X86_64_JUMP_SLOT: PP = S; break; } } } } #define SHT_NOTE    7 #define SIGN_NOTE_NAME...
- `elf_sign_note_span` (function) `kernel/loader.c:1083` `static int elf_sign_note_span(const unsigned char *img, unsigned long off,
                      ...` -- Docstring: Pull the signature descriptor out of one PT_NOTE span.
- `elf_sign_note_find` (function) `kernel/loader.c:1108` `static int elf_sign_note_find(const unsigned char *img, unsigned size,
                          ...` -- Docstring: Find a signature note across the PT_NOTE segments. * Reports 1 with the first descriptor found, else 0.
- `elf_sign_section_find` (function) `kernel/loader.c:1132` `static int elf_sign_section_find(const unsigned char *img, unsigned size,
                       ...` -- Docstring: Find a signature note in the SHT_NOTE section table.
- `elf_sign_u64` (function) `kernel/loader.c:1172` `static void elf_sign_u64(ed_sha *c, unsigned long v)` -- elf_note_pad(SIGN_DESC_BYTES)) continue; elf_name_copy(secname, sizeof(secname), shstrtab, shstr->sh_size...
- `elf_sign_u32` (function) `kernel/loader.c:1181` `static void elf_sign_u32(ed_sha *c, unsigned v)` -- } return 0; } /** Docstring: Feed one little-endian u64 into the image digest. static void elf_sign_u64(ed_sha *c...
- `load_exec_elf` (function) `kernel/loader.c:1262` `void *load_exec_elf(void *data, unsigned size)`
- `process` (function) `kernel/loader.c:1288` `* atomic section: a 100 Hz tick between two segments would switch * CR3 into another process (copies landing in its...`
- `base_out` (function) `kernel/loader.c:1395` `* the link base via base_out (0 when the caller runs static images
 * only: the dynamic binder ne...`
- `elf_wants_process` (function) `kernel/loader.c:1432` `int elf_wants_process(const void *data, unsigned size)` -- Does an ET_EXEC/ET_DYN image ask to run as a process (minios_abi.h, process note)?
- `load_exec_elf_into` (function) `kernel/loader.c:1456` `void *load_exec_elf_into(void *data, unsigned size, unsigned long cr3,
                         u...`
- `time` (function) `kernel/loader.c:1520` `* time (with the failing offset);`

## kernel/lz4_kernel.c
Depends on: `headers/lz4_kernel.h`
- `LZ4_read32` (function) `kernel/lz4_kernel.c:7` `static inline unsigned int LZ4_read32(const unsigned char *p)`
- `LZ4_read16` (function) `kernel/lz4_kernel.c:14` `static inline unsigned int LZ4_read16(const unsigned char *p)`
- `LZ4_write16` (function) `kernel/lz4_kernel.c:21` `static inline void LZ4_write16(unsigned char *dst, unsigned short v)`
- `LZ4_hash` (function) `kernel/lz4_kernel.c:26` `static unsigned int LZ4_hash(const unsigned char *p)`
- `LZ4_compressBound` (function) `kernel/lz4_kernel.c:33` `int LZ4_compressBound(int inputSize)`
- `LZ4_compress_default` (function) `kernel/lz4_kernel.c:40` `int LZ4_compress_default(const char *src, char *dst, int srcSize, int dstCapacity)`
- `slots` (function) `kernel/lz4_kernel.c:43` `* runs from file writes on 16 KB proc slots (stack discipline, * CLAUDE.md). OOM returns 0 and the caller stores...`
- `LZ4_decompress_safe` (function) `kernel/lz4_kernel.c:176` `int LZ4_decompress_safe(const char *src, char *dst, int compressedSize, int dstCapacity)`

## kernel/minifetch.c
Depends on: `headers/minifetch.h`, `headers/minifs.h`, `headers/net.h`, `headers/rtc.h`, `headers/sched.h`, `headers/vga_fb.h`
- `minifetch_row` (function) `kernel/minifetch.c:57` `static void minifetch_row(const unsigned char *img, int w, int h, int row,
                      ...` -- "       DOOM  ready.           ", "                              ", "                              ", "...
- `minifetch_logo` (function) `kernel/minifetch.c:81` `static void minifetch_logo(char rows[16][33])` -- const unsigned char *p1 = img + ((y1 * w) + sx) * 4; unsigned lum; if (p0[3] < 128 && p1[3] < 128) { out[x] = ' '...
- `minifetch_specs` (function) `kernel/minifetch.c:101` `static int minifetch_specs(char lines[20][96])` -- stbi_image_free(img); for (r = 0; r < mf_cfg.logo_rows; r++) { for (i = 0; i < mf_cfg.logo_cols; i++) rows[r][i] =...
- `shell_cmd_minifetch` (function) `kernel/minifetch.c:156` `void shell_cmd_minifetch(void)` -- ksprintf(lines[n++], "Display: %dx%dx%d", fb_width, fb_height, fb_bpp); ksprintf(lines[n++], "Net...
- `frame` (function) `kernel/minifetch.c:159` `* frame (stack discipline, CLAUDE.md). Fail-closed on OOM. */ char (*specs)[96] = (char (*)[96])kmalloc(20 * 96);`

## kernel/mm.c
Depends on: `headers/arch/x86/boot/bootdefs.h`, `headers/sched.h`
- `kheap_ram_top` (function) `kernel/mm.c:19` `static unsigned long kheap_ram_top(void)` -- RAM top from the CMOS extended-memory count (the identity map covers the first gigabyte; nothing else reports the...
- `kallocator_init` (function) `kernel/mm.c:32` `void kallocator_init(void)` -- Build the heap over [HEAP_BASE, HEAP_BASE + kheap_size): the layout maximum, never past the installed RAM (a smaller...
- `kmalloc_report_failure` (function) `kernel/mm.c:53` `static void kmalloc_report_failure(unsigned long size)`
- `kmalloc` (function) `kernel/mm.c:66` `void *kmalloc(unsigned long size)`
- `kmalloc_page` (function) `kernel/mm.c:81` `void *kmalloc_page(void)` -- One page-aligned heap page (the page-table and user-page allocator's backing). memalign keeps the cost at one page...
- `kfree` (function) `kernel/mm.c:90` `void kfree(void *ptr)`
- `kcalloc` (function) `kernel/mm.c:111` `void *kcalloc(unsigned long nmemb, unsigned long size)`
- `krealloc` (function) `kernel/mm.c:115` `void *krealloc(void *ptr, unsigned long size)`
- `kmalloc_aligned` (function) `kernel/mm.c:127` `void *kmalloc_aligned(unsigned long size, unsigned long align)` -- Docstring: Aligned allocation with a recoverable raw pointer.
- `kfree_aligned` (function) `kernel/mm.c:143` `void kfree_aligned(void *ptr)` -- Docstring: Release a kmalloc_aligned block.

## kernel/mm/cow.c
Depends on: `headers/arch/x86/boot/bootdefs.h`, `headers/sched.h`, `headers/tlb.h`, `headers/vga_fb.h`
- `alternative` (function) `kernel/mm/cow.c:20` `* window is one instruction wide and the alternative (no CoW) is * documented, so the trade stands. */ #include...`
- `cow_slot` (function) `kernel/mm/cow.c:68` `static unsigned long cow_slot(unsigned long phys)`
- `cow_find` (function) `kernel/mm/cow.c:73` `static int cow_find(unsigned long phys)` -- unsigned long phys; int ref; } cow_entry_t; static cow_entry_t *cow_tab; static unsigned long cow_live; static...
- `cow_remove` (function) `kernel/mm/cow.c:85` `static void cow_remove(int idx)` -- Retire entry idx: a tombstone keeps later probe chains intact; an empty * table drops every tombstone at once.
- `cow_table_ensure` (function) `kernel/mm/cow.c:98` `static void cow_table_ensure(void)` -- Create the table on first use, outside cow_lock (allocation).
- `cow_rehash` (function) `kernel/mm/cow.c:110` `static void cow_rehash(void)` -- Reinsert the live entries in place when tombstones lengthen the probe chains: lift each live entry out and insert it...
- `cow_page_shared` (function) `kernel/mm/cow.c:132` `int cow_page_shared(unsigned long phys)` -- Docstring: True when phys is still shared copy-on-write. mprotect consults this before setting a writable bit...
- `cow_copy_demand` (function) `kernel/mm/cow.c:166` `static void cow_copy_demand(unsigned long pcr3, unsigned long ccr3)` -- Copy the parent's demand-paging reservations (non-present PTEs carrying PTE_DEMAND) into the child: a reserved...
- `cow_track` (function) `kernel/mm/cow.c:191` `static int cow_track(unsigned long phys)`
- `private` (function) `kernel/mm/cow.c:217` `* for every present page in a private (non-graphics) slot. Shared * graphics slots are never CoW: the compositor...`
- `cow_walk` (function) `kernel/mm/cow.c:221` `static void cow_walk(unsigned long cr3, cow_walk_fn fn)`
- `cow_fork_one` (function) `kernel/mm/cow.c:255` `static void cow_fork_one(unsigned long pcr3, unsigned long va,
        volatile unsigned long *ppte)`
- `CPU` (function) `kernel/mm/cow.c:287` `* address space down on every other CPU (tlb_shootdown in do_fork_ex). */
unsigned long cow_fork_...`
- `cow_resolve` (function) `kernel/mm/cow.c:356` `int cow_resolve(unsigned long cr3, unsigned long va)` -- Docstring: Resolve a write fault on a CoW page: last sharer gets a permission upgrade, otherwise the faulting window...
- `cow_release_window` (function) `kernel/mm/cow.c:421` `void cow_release_window(unsigned long cr3)` -- Docstring: Drop one window's CoW shares before its pages are freed: multi-shared pages are unmapped here (phys...
- `cow_shared` (function) `kernel/mm/cow.c:464` `int cow_shared(void)` -- idx = cow_find(phys); if (idx < 0) continue; if (cow_tab[idx].ref > 1) { cow_tab[idx].ref--; pt[k] = 0; } else {...

## kernel/mm/paging.c
Depends on: `headers/arch/x86/boot/bootdefs.h`, `headers/arch/x86/msr.h`, `headers/ldso.h`, `headers/minifs.h`, `headers/pcache.h`, `headers/tlb.h`, `headers/vga_fb.h`
- `mm_page_aligned_alloc` (function) `kernel/mm/paging.c:32` `static unsigned char *mm_page_aligned_alloc(unsigned size,
                                      ...` -- Page-align a kmalloc'd region.
- `mm_setup_protections` (function) `kernel/mm/paging.c:41` `void mm_setup_protections(void)`
- `kmm_ensure_pt` (function) `kernel/mm/paging.c:235` `static volatile unsigned long *kmm_ensure_pt(unsigned long phys)` -- Docstring: Return the 4 KB page table backing a 2 MB identity slot, splitting the boot leaf if needed.
- `coherent` (function) `kernel/mm/paging.c:259` `* for memory a device reads and writes by DMA: a controller that is not cache
 * coherent (and an...`
- `kmm_map_device` (function) `kernel/mm/paging.c:296` `unsigned long kmm_map_device(unsigned long phys, unsigned long len)`
- `mm_user_pte_update` (function) `kernel/mm/paging.c:336` `void mm_user_pte_update(unsigned long vaddr, int exec, unsigned long cr3)`
- `mm_user_set_exec` (function) `kernel/mm/paging.c:356` `void mm_user_set_exec(unsigned long start, unsigned long end, unsigned long cr3)`
- `pt_owned_index` (function) `kernel/mm/paging.c:374` `static int pt_owned_index(unsigned long phys, unsigned long *byte, unsigned *bit)`
- `pt_page_owned` (function) `kernel/mm/paging.c:385` `int pt_page_owned(unsigned long phys)` -- #define PT_OWNED_BYTES (HEAP_SIZE / 0x1000UL / 8UL) static unsigned char *pt_owned; static int...
- `pt_page_alloc` (function) `kernel/mm/paging.c:392` `void *pt_page_alloc(void)`
- `pt_page_free` (function) `kernel/mm/paging.c:411` `void pt_page_free(void *ptr)`
- `pt_clone_user` (function) `kernel/mm/paging.c:420` `uint64_t pt_clone_user(uint64_t parent_cr3)`
- `mt_shared_slot` (function) `kernel/mm/paging.c:549` `static int mt_shared_slot(unsigned long pd_idx)` -- The legacy path identity-maps the user window (VA == PA), so every CR3 built by pt_clone_user aliases the same...
- `pt_clone_user_empty` (function) `kernel/mm/paging.c:568` `unsigned long pt_clone_user_empty(void)` -- Fresh user window: kernel mappings copied, every user PT zeroed, graphics slots re-shared from the boot tables.
- `mm_user_ensure_page` (function) `kernel/mm/paging.c:625` `int mm_user_ensure_page(unsigned long cr3, unsigned long va)` -- Ensure one 4 KB user page at va inside cr3 exists (heap-owned). * Returns 0 on success, -1 on OOM or when va leaves...
- `honest` (function) `kernel/mm/paging.c:655` `* and invlpg keeps the local TLB honest (cross-CPU shootdown rides
 * the documented T5 follow-up...`
- `mm_demand_pte` (function) `kernel/mm/paging.c:704` `unsigned long mm_demand_pte(unsigned long prot)` -- Docstring: PTE walker shared by the fault, fork and teardown * paths (forward declaration; documented at the...
- `mm_anon_frame` (function) `kernel/mm/paging.c:715` `static int mm_anon_frame(unsigned long phys)` -- Heap-owned anonymous frame: the only kind an unmap may free (the shared pid-0 window and graphics slots map fixed...
- `mm_anon_fault` (function) `kernel/mm/paging.c:779` `int mm_anon_fault(unsigned long cr3, unsigned long va, int write)` -- Resolve a fault on a reservation: map a zeroed page with the reserved protection.
- `mm_file_page_phys` (function) `kernel/mm/paging.c:861` `unsigned long mm_file_page_phys(unsigned long cr3, unsigned long va)` -- Docstring: Read the mapped phys for va in cr3, 0 when the PTE is absent or non-present.
- `mm_file_pte` (function) `kernel/mm/paging.c:880` `static volatile unsigned long *mm_file_pte(unsigned long cr3,
        unsigned long va)` -- Docstring: Locate the PTE for va in cr3 without allocating.
- `tables` (function) `kernel/mm/paging.c:1010` `* tables (munmap/mremap in caller context, under their mm_lock);`
- `explicitly` (function) `kernel/mm/paging.c:1011` `* teardown passes the dying window explicitly (zombie-exclusive, no * lock needed). unmap == 0 drops refs only...`
- `PTE` (function) `kernel/mm/paging.c:1015` `* PTE (a cache page stays cached, but no stale writer may reach it).
 * Never allocates. */
void ...`
- `mm_file_break` (function) `kernel/mm/paging.c:1070` `int mm_file_break(unsigned long cr3, unsigned long va)` -- Docstring: Break a write fault on a cache-shared file page into a private copy (fail-closed).
- `mm_copy_user_page` (function) `kernel/mm/paging.c:1149` `int mm_copy_user_page(unsigned long dst_cr3, unsigned long src_cr3, unsigned long va)` -- Copy one present user page from src_cr3 to the same VA in dst_cr3, allocating the destination page.
- `pt_free_user` (function) `kernel/mm/paging.c:1227` `void pt_free_user(uint64_t cr3)`

## kernel/mm/swap.c
Depends on: `headers/ide.h`, `headers/lz4_kernel.h`
- `unwired` (function) `kernel/mm/swap.c:7` `* * Currently unwired (the isolated-window spawn path superseded the * swap-out design);`
- `swap_ensure` (function) `kernel/mm/swap.c:28` `static int swap_ensure(void)` -- #include "ide.h" #include "lz4_kernel.h" #define SWAP_CHUNK_RAW     65536 #define SWAP_CHUNK_CMP     (SWAP_CHUNK_RAW...
- `swap_lba` (function) `kernel/mm/swap.c:41` `static unsigned long swap_lba(void)`
- `swap_out` (function) `kernel/mm/swap.c:47` `int swap_out(unsigned long window_sz)`
- `swap_in` (function) `kernel/mm/swap.c:97` `int swap_in(void)`

## kernel/mm/tlb.c
Depends on: `headers/sched.h`, `headers/smp.h`, `headers/spinlock.h`, `headers/tlb.h`
- `tlb_others_on` (function) `kernel/mm/tlb.c:36` `static int tlb_others_on(unsigned long cr3)` -- 1 when another online CPU is running address space cr3 right now.
- `tlb_shootdown` (function) `kernel/mm/tlb.c:49` `void tlb_shootdown(unsigned long cr3)`
- `tlb_shootdown_count` (function) `kernel/mm/tlb.c:71` `unsigned long tlb_shootdown_count(void)`
- `tlb_shootdown_timeouts` (function) `kernel/mm/tlb.c:75` `unsigned long tlb_shootdown_timeouts(void)`

## kernel/panic.c
Depends on: `headers/panic.h`, `headers/sched.h`, `headers/vga_fb.h`
- `panic_hex` (function) `kernel/panic.c:23` `static void panic_hex(unsigned long v, int digits)`
- `panic_fb_puts` (function) `kernel/panic.c:30` `static void panic_fb_puts(const char *s)`
- `panic_fb_hex` (function) `kernel/panic.c:61` `static void panic_fb_hex(unsigned long v, int digits)`
- `panic_screen` (function) `kernel/panic.c:96` `void panic_screen(unsigned long vector, unsigned long err,
        unsigned long rip, unsigned lo...` -- Docstring: Paint the panic screen for an unrecoverable fault and halt when asked. vector/err/rip/rsp come from the...

## kernel/percpu_rq.c
Depends on: `headers/percpu_rq.h`
- `rq_cpu_valid` (function) `kernel/percpu_rq.c:14` `static int rq_cpu_valid(int cpu)`
- `rq_init` (function) `kernel/percpu_rq.c:19` `void rq_init(void)` -- topology and on spinlock.h for the ring locks, which keeps it host-testable (tests/test_percpu_rq.c, make...
- `rq_enqueue` (function) `kernel/percpu_rq.c:41` `void rq_enqueue(int cpu, int pid)` -- Docstring: Record pid as READY work for cpu.
- `rq_pop_local` (function) `kernel/percpu_rq.c:61` `int rq_pop_local(int cpu)` -- return; spin_lock_irqsave(&rqueues[cpu].lock, &flags); if (rqueues[cpu].count >= RQ_DEPTH) { rqueues[cpu].drops++...
- `rq_steal_once` (function) `kernel/percpu_rq.c:89` `int rq_steal_once(int self_cpu, int *from_cpu)` -- Docstring: Non-blocking steal of one hint from another CPU's ring.
- `rq_empty` (function) `kernel/percpu_rq.c:115` `int rq_empty(int cpu)` -- pid = rqueues[c].ring[rqueues[c].head]; rqueues[c].ring[rqueues[c].head] = WQ_NONE_HINT; rqueues[c].head =...
- `rq_note_poll` (function) `kernel/percpu_rq.c:127` `void rq_note_poll(int cpu)` -- /** Docstring: True when cpu holds no hint.
- `rq_should_rescan` (function) `kernel/percpu_rq.c:137` `int rq_should_rescan(int cpu)` -- return empty; } /** Docstring: Count an unsuccessful claim poll for the rescan schedule. void rq_note_poll(int cpu)...
- `rq_stats` (function) `kernel/percpu_rq.c:152` `void rq_stats(int cpu, unsigned long *hits, unsigned long *steals,
              unsigned long *d...` -- irqflags_t flags; int due = 0; if (!rq_cpu_valid(cpu)) return 1; spin_lock_irqsave(&rqueues[cpu].lock, &flags); if...

## kernel/printf.c
- `putc_buf` (function) `kernel/printf.c:7` `static void putc_buf(char c, void *ctx, int *written)`
- `putc_file` (function) `kernel/printf.c:13` `static void putc_file(char c, void *ctx, int *written)`
- `putc_str` (function) `kernel/printf.c:19` `static void putc_str(char c, void *ctx, int *written)`
- `emit_num` (function) `kernel/printf.c:26` `static void emit_num(void (*emit)(char, void *, int *), void *ctx, int *written,
                ...`
- `kformat` (function) `kernel/printf.c:44` `static void kformat(void (*emit)(char, void *, int *), void *ctx,
                    int *writte...`
- `kfprintf` (function) `kernel/printf.c:157` `int kfprintf(KFILE *f, const char *fmt, ...)`
- `ksprintf` (function) `kernel/printf.c:166` `int ksprintf(char *buf, const char *fmt, ...)`
- `putc_snbuf` (function) `kernel/printf.c:178` `static void putc_snbuf(char c, void *ctx, int *written)`
- `ksnprintf` (function) `kernel/printf.c:184` `int ksnprintf(char *buf, unsigned long size, const char *fmt, ...)`


Next: [API_p7.md](API_p7.md)
