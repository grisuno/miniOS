# `headers/vga_fb.h`

> Source: [headers/vga_fb.h:1](../../headers/vga_fb.h#L1) | language `h` | coverage 25.4% | [API index](../index.md)

## Contents

- **Structs:** [`mouse_state_t`](#mouse_state_t)
- **Functions:** [`fb_bytes_per_pixel`](#fb_bytes_per_pixel), [`vga_fb_read_rgb`](#vga_fb_read_rgb), [`vga_fb_set_gfx_palette`](#vga_fb_set_gfx_palette), [`vga_fb_boot_config`](#vga_fb_boot_config), [`SYS_DOOM_FRAME`](#sys_doom_frame), [`SYS_NK_FRAME`](#sys_nk_frame), [`vga_fb_blit_nk_window`](#vga_fb_blit_nk_window), [`vga_fb_blit_nk_rgb_window`](#vga_fb_blit_nk_rgb_window), [`below`](#below), [`vga_fb_init`](#vga_fb_init), [`vga_fb_term_ring_init`](#vga_fb_term_ring_init), [`vga_fb_term_feed`](#vga_fb_term_feed), [`vga_fb_history_page`](#vga_fb_history_page), [`vga_fb_clear`](#vga_fb_clear), [`vga_fb_pixel`](#vga_fb_pixel), [`vga_fb_rect`](#vga_fb_rect), [`vga_fb_pixel_rgb`](#vga_fb_pixel_rgb), [`vga_fb_rect_rgb`](#vga_fb_rect_rgb), [`vga_fb_char`](#vga_fb_char), [`vga_fb_str`](#vga_fb_str), [`vga_fb_putc_term`](#vga_fb_putc_term), [`vga_fb_puts_term`](#vga_fb_puts_term), [`term_clear`](#term_clear), [`vga_fb_text_cursor`](#vga_fb_text_cursor), [`vga_fb_hide_text_cursor`](#vga_fb_hide_text_cursor), [`fb_read_packed`](#fb_read_packed), [`fb_write_packed`](#fb_write_packed), [`vga_fb_draw_desktop`](#vga_fb_draw_desktop), [`vga_fb_toggle_fullscreen`](#vga_fb_toggle_fullscreen), [`vga_fb_move_terminal`](#vga_fb_move_terminal), [`vga_fb_snap_window`](#vga_fb_snap_window), [`vga_fb_resize`](#vga_fb_resize), [`vga_fb_reset_default`](#vga_fb_reset_default), [`vga_fb_toggle_minimize`](#vga_fb_toggle_minimize), [`vga_fb_is_minimized`](#vga_fb_is_minimized), [`vga_fb_is_fullscreen`](#vga_fb_is_fullscreen), [`vga_fb_gfx_set_fullscreen`](#vga_fb_gfx_set_fullscreen), [`vga_fb_gfx_set_hidden`](#vga_fb_gfx_set_hidden), [`vga_fb_gfx_view_name`](#vga_fb_gfx_view_name), [`vga_fb_gfx_origin`](#vga_fb_gfx_origin), [`vga_fb_gfx_map_mouse`](#vga_fb_gfx_map_mouse), [`fb_write_row_packed`](#fb_write_row_packed), [`fb_read_row_packed`](#fb_read_row_packed), [`vga_fb_close_active`](#vga_fb_close_active), [`vga_fb_focus_next`](#vga_fb_focus_next), [`vga_fb_focus_id`](#vga_fb_focus_id), [`vga_fb_focus_get`](#vga_fb_focus_get), [`vga_fb_focus_event`](#vga_fb_focus_event), [`vga_fb_focus_report`](#vga_fb_focus_report), [`vga_fb_theme_name`](#vga_fb_theme_name), [`vga_fb_ps2_owner`](#vga_fb_ps2_owner), [`vga_fb_nterms_get`](#vga_fb_nterms_get), [`vga_fb_term_split`](#vga_fb_term_split), [`vga_fb_term_close_focused`](#vga_fb_term_close_focused), [`vga_fb_tile_all`](#vga_fb_tile_all), [`vga_fb_layout_set`](#vga_fb_layout_set), [`vga_fb_layout_cycle`](#vga_fb_layout_cycle), [`vga_fb_layout_get`](#vga_fb_layout_get), [`vga_fb_layout_name`](#vga_fb_layout_name), [`vga_fb_list_windows`](#vga_fb_list_windows), [`wm_close_pending`](#wm_close_pending), [`wm_clear_close`](#wm_clear_close), [`wm_gfx_mode_active`](#wm_gfx_mode_active), [`vga_fb_mouse_tick`](#vga_fb_mouse_tick), [`vga_fb_wait_tick`](#vga_fb_wait_tick), [`vga_fb_mouse_init`](#vga_fb_mouse_init), [`dock_bounce_counts`](#dock_bounce_counts), [`dock_click_count`](#dock_click_count), [`dock_pending_active`](#dock_pending_active), [`pixels`](#pixels), [`vga_fx_enabled`](#vga_fx_enabled), [`vga_fx_snap_rect`](#vga_fx_snap_rect), [`vga_fx_restore_rect`](#vga_fx_restore_rect), [`vga_fx_free`](#vga_fx_free), [`vga_fx_melt_rect`](#vga_fx_melt_rect), [`vga_fx_melt_from_black`](#vga_fx_melt_from_black), [`vga_fx_burn_rect`](#vga_fx_burn_rect), [`vga_fx_genie_rect`](#vga_fx_genie_rect), [`vga_fb_set_gfx_mode`](#vga_fb_set_gfx_mode)
- **Macros:** [`FB_ADDR`](#fb_addr), [`DOOM_W`](#doom_w), [`DOOM_BACKBUF_ADDR`](#doom_backbuf_addr), [`GFX_TITLE_DEFAULT`](#gfx_title_default), [`NK_W`](#nk_w), [`NK_BACKBUF_ADDR`](#nk_backbuf_addr), [`NK_RGB_ADDR`](#nk_rgb_addr), [`NK_RGB_BYTES`](#nk_rgb_bytes), [`COL_BLACK`](#col_black), [`COL_BG`](#col_bg), [`COL_TASKBAR`](#col_taskbar), [`COL_TASKBAR_TXT`](#col_taskbar_txt), [`COL_TITLEBAR`](#col_titlebar), [`COL_TITLE_TXT`](#col_title_txt), [`COL_TERMINAL`](#col_terminal), [`COL_TERM_TXT`](#col_term_txt), [`COL_TERM_CUR`](#col_term_cur), [`COL_BORDER`](#col_border), [`COL_WHITE`](#col_white), [`COL_SHADOW`](#col_shadow), [`COL_HIGHLIGHT`](#col_highlight), [`COL_SCROLLBAR`](#col_scrollbar), [`COL_SCROLL_THUMB`](#col_scroll_thumb), [`WALLPAPER_PATH`](#wallpaper_path), [`WALL_PAL_BASE`](#wall_pal_base), [`WALL_PAL_SIZE`](#wall_pal_size), [`FONT_W`](#font_w), [`TERM_MAX_COLS`](#term_max_cols), [`TERM_MAX_ROWS`](#term_max_rows), [`TASKBAR_PAD`](#taskbar_pad), [`TASKBAR_CLOCK_CH`](#taskbar_clock_ch), [`TASKBAR_VOL_CH`](#taskbar_vol_ch), [`TASKBAR_VOL_STEP`](#taskbar_vol_step), [`TASKBAR_ICON_W`](#taskbar_icon_w), [`TASKBAR_BTN_W`](#taskbar_btn_w), [`TASKBAR_KBD_CH`](#taskbar_kbd_ch), [`TASKBAR_KBD_W`](#taskbar_kbd_w), [`TASKBAR_THEME_CH`](#taskbar_theme_ch), [`TASKBAR_THEME_W`](#taskbar_theme_w), [`TILING_LEFT`](#tiling_left), [`TILING_RIGHT`](#tiling_right), [`TILING_TOP`](#tiling_top), [`TILING_BOTTOM`](#tiling_bottom), [`TILING_TOP_LEFT`](#tiling_top_left), [`TILING_TOP_RIGHT`](#tiling_top_right), [`TILING_BOTTOM_LEFT`](#tiling_bottom_left), [`TILING_BOTTOM_RIGHT`](#tiling_bottom_right), [`SCROLLBAR_W`](#scrollbar_w), [`SCROLLBAR_PAD`](#scrollbar_pad), [`WM_BTN_W`](#wm_btn_w), [`WM_BTN_PAD`](#wm_btn_pad), [`WM_BTN_MIN`](#wm_btn_min), [`WM_BTN_MAX`](#wm_btn_max), [`WM_BTN_CLOSE`](#wm_btn_close), [`SB_MAX_LINES`](#sb_max_lines), [`SB_LINE_MAX`](#sb_line_max), [`WM_FOCUS_GFX`](#wm_focus_gfx)
- **Variables:** [`fb_width`](#fb_width), [`fb_height`](#fb_height), [`fb_pitch`](#fb_pitch), [`fb_bpp`](#fb_bpp), [`fb_phys_base`](#fb_phys_base), [`gfx_win_title`](#gfx_win_title), [`gfx_frames_composited`](#gfx_frames_composited), [`nk_win_y`](#nk_win_y), [`term_rows`](#term_rows), [`mouse_state`](#mouse_state), [`fx_melts_completed`](#fx_melts_completed), [`fx_burns_completed`](#fx_burns_completed), [`fx_genies_completed`](#fx_genies_completed), [`vga_fb_active`](#vga_fb_active)

## Structs

<a id="mouse_state_t"></a>

### `mouse_state_t`

`struct` | [headers/vga_fb.h:159](../../headers/vga_fb.h#L159)

```c
typedef struct
```

---- Mouse state (updated by IRQ12 handler in sched.c) ----

---

## Functions

<a id="fb_bytes_per_pixel"></a>

### `fb_bytes_per_pixel`

`function` | [headers/vga_fb.h:30](../../headers/vga_fb.h#L30)

```c
int fb_bytes_per_pixel(void);
```

Bytes per framebuffer pixel derived from fb_bpp (1 for 8-bit, 3 for 24, 4 for 32).

**Returns:** `int`

---

<a id="vga_fb_read_rgb"></a>

### `vga_fb_read_rgb`

`function` | [headers/vga_fb.h:34](../../headers/vga_fb.h#L34)

```c
unsigned long vga_fb_read_rgb(int x, int y);
```

Read one desktop pixel as packed 0x00RRGGBB (palette-resolved in 8-bit mode, native in true color).

Backstop for `gfx pixel`/`gfx shot`, which must report colors instead of DAC indices once the DAC is gone.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `y` | `int` |  |  |

**Returns:** `unsigned long`

---

<a id="vga_fb_set_gfx_palette"></a>

### `vga_fb_set_gfx_palette`

`function` | [headers/vga_fb.h:38](../../headers/vga_fb.h#L38)

```c
void vga_fb_set_gfx_palette(const unsigned char *pal);
```

Store the graphics program's 768-byte palette (SYS_PALETTE).

In 8-bit mode it is also programmed into the DAC; in true color it is only kept so the DOOM/Nuklear blits can expand their indexed back-buffers to RGB.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `pal` | `unsigned char *` |  |  |

---

<a id="vga_fb_boot_config"></a>

### `vga_fb_boot_config`

`function` | [headers/vga_fb.h:40](../../headers/vga_fb.h#L40)

```c
void vga_fb_boot_config(void);
```

*Called by:* [`__attribute__`](kernel.c.md#__attribute__)

---

<a id="sys_doom_frame"></a>

### `SYS_DOOM_FRAME`

`function` | [headers/vga_fb.h:44](../../headers/vga_fb.h#L44)

```c
* and calls SYS_DOOM_FRAME (211) to have the kernel composite it onto the * desktop at its native resolution, so the shell window stays visible. */ #define DOOM_W MINIOS_DOOM_W #define DOOM_H MINIOS_D
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `211` |  |  |  |

**Returns:** `* and calls`

---

<a id="sys_nk_frame"></a>

### `SYS_NK_FRAME`

`function` | [headers/vga_fb.h:63](../../headers/vga_fb.h#L63)

```c
* SYS_NK_FRAME (220);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `220` |  |  |  |

**Returns:** `*`

---

<a id="vga_fb_blit_nk_window"></a>

### `vga_fb_blit_nk_window`

`function` | [headers/vga_fb.h:75](../../headers/vga_fb.h#L75)

```c
void vga_fb_blit_nk_window(void);
```

RGB companion buffer (3 bytes per pixel, R,G,B order, NK_W x NK_H).

Mapped by mm_setup_protections like the indexed buffers; presented with * GFX_PRESENT + MINIOS_GFX_BUF_NK_RGB through vga_fb_blit_nk_rgb_window. define NK_RGB_ADDR   MINIOS_NK_RGB_ADDR define NK_RGB_BYTES  MINIOS_NK_RGB_BYTES

*Called by:* [`DOOM_FRAME`](kernel.syscalls.c.md#doom_frame)

---

<a id="vga_fb_blit_nk_rgb_window"></a>

### `vga_fb_blit_nk_rgb_window`

`function` | [headers/vga_fb.h:76](../../headers/vga_fb.h#L76)

```c
void vga_fb_blit_nk_rgb_window(void);
```

*Called by:* [`DOOM_FRAME`](kernel.syscalls.c.md#doom_frame)

---

<a id="below"></a>

### `below`

`function` | [headers/vga_fb.h:99](../../headers/vga_fb.h#L99)

```c
* file below (800x600 RGB PNG on the ramdisk, produced by * tools/gen_desktop_pngs.py) is decoded once per boot via stbi_load_file, * stretched to the framebuffer and mapped to a fixed 6x6x6 websafe c
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ramdisk` | `800x600 RGB PNG on the` |  |  |
| `py` | `produced by * tools/gen_desktop_pngs.` |  |  |

**Returns:** `* file`

---

<a id="vga_fb_init"></a>

### `vga_fb_init`

`function` | [headers/vga_fb.h:177](../../headers/vga_fb.h#L177)

```c
void vga_fb_init(void);
```

---- Public API ----

*Called by:* [`__attribute__`](kernel.c.md#__attribute__)

---

<a id="vga_fb_term_ring_init"></a>

### `vga_fb_term_ring_init`

`function` | [headers/vga_fb.h:182](../../headers/vga_fb.h#L182)

```c
void vga_fb_term_ring_init(void);
```

Feed one completed console line into the terminal history (the text-mode console has no other history) and page that history by one screen (dir -1 up, +1 down).

The page keys drive the paging when the framebuffer terminal is up.

*Called by:* [`__attribute__`](kernel.c.md#__attribute__)

---

<a id="vga_fb_term_feed"></a>

### `vga_fb_term_feed`

`function` | [headers/vga_fb.h:183](../../headers/vga_fb.h#L183)

```c
void vga_fb_term_feed(const char *line, int len);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `line` | `char *` |  |  |
| `len` | `int` |  |  |

---

<a id="vga_fb_history_page"></a>

### `vga_fb_history_page`

`function` | [headers/vga_fb.h:184](../../headers/vga_fb.h#L184)

```c
void vga_fb_history_page(int dir);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `dir` | `int` |  |  |

*Called by:* [`console_history_page`](kernel.console_in.c.md#console_history_page)

---

<a id="vga_fb_clear"></a>

### `vga_fb_clear`

`function` | [headers/vga_fb.h:185](../../headers/vga_fb.h#L185)

```c
void vga_fb_clear(void);
```

---

<a id="vga_fb_pixel"></a>

### `vga_fb_pixel`

`function` | [headers/vga_fb.h:186](../../headers/vga_fb.h#L186)

```c
void vga_fb_pixel(int x, int y, uint8_t color);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `y` | `int` |  |  |
| `color` | `uint8_t` |  |  |

---

<a id="vga_fb_rect"></a>

### `vga_fb_rect`

`function` | [headers/vga_fb.h:187](../../headers/vga_fb.h#L187)

```c
void vga_fb_rect(int x, int y, int w, int h, uint8_t color);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `y` | `int` |  |  |
| `w` | `int` |  |  |
| `h` | `int` |  |  |
| `color` | `uint8_t` |  |  |

---

<a id="vga_fb_pixel_rgb"></a>

### `vga_fb_pixel_rgb`

`function` | [headers/vga_fb.h:189](../../headers/vga_fb.h#L189)

```c
void vga_fb_pixel_rgb(int x, int y, uint8_t r, uint8_t g, uint8_t b);
```

Direct RGB primitives: full depth in 32/24-bit, quantized in 8-bit.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `y` | `int` |  |  |
| `r` | `uint8_t` |  |  |
| `g` | `uint8_t` |  |  |
| `b` | `uint8_t` |  |  |

---

<a id="vga_fb_rect_rgb"></a>

### `vga_fb_rect_rgb`

`function` | [headers/vga_fb.h:190](../../headers/vga_fb.h#L190)

```c
void vga_fb_rect_rgb(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `y` | `int` |  |  |
| `w` | `int` |  |  |
| `h` | `int` |  |  |
| `r` | `uint8_t` |  |  |
| `g` | `uint8_t` |  |  |
| `b` | `uint8_t` |  |  |

---

<a id="vga_fb_char"></a>

### `vga_fb_char`

`function` | [headers/vga_fb.h:191](../../headers/vga_fb.h#L191)

```c
void vga_fb_char(int col, int row, char c, uint8_t fg, uint8_t bg);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `col` | `int` |  |  |
| `row` | `int` |  |  |
| `c` | `char` |  |  |
| `fg` | `uint8_t` |  |  |
| `bg` | `uint8_t` |  |  |

---

<a id="vga_fb_str"></a>

### `vga_fb_str`

`function` | [headers/vga_fb.h:192](../../headers/vga_fb.h#L192)

```c
void vga_fb_str(int col, int row, const char *s, uint8_t fg, uint8_t bg);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `col` | `int` |  |  |
| `row` | `int` |  |  |
| `s` | `char *` |  |  |
| `fg` | `uint8_t` |  |  |
| `bg` | `uint8_t` |  |  |

---

<a id="vga_fb_putc_term"></a>

### `vga_fb_putc_term`

`function` | [headers/vga_fb.h:193](../../headers/vga_fb.h#L193)

```c
void vga_fb_putc_term(char c);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `c` | `char` |  |  |

*Called by:* [`vga_putc`](kernel.console.c.md#vga_putc), [`line`](kernel.vga_fb.c.md#line), [`vga_fb_puts_term`](kernel.vga_fb.c.md#vga_fb_puts_term)

---

<a id="vga_fb_puts_term"></a>

### `vga_fb_puts_term`

`function` | [headers/vga_fb.h:194](../../headers/vga_fb.h#L194)

```c
void vga_fb_puts_term(const char *s);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `s` | `char *` |  |  |

---

<a id="term_clear"></a>

### `term_clear`

`function` | [headers/vga_fb.h:195](../../headers/vga_fb.h#L195)

```c
void term_clear(void);
```

*Called by:* [`shell_exec_builtin`](kernel.shell.c.md#shell_exec_builtin), [`view`](kernel.syscalls.c.md#view), [`buffer`](kernel.vga_fb.c.md#buffer)

---

<a id="vga_fb_text_cursor"></a>

### `vga_fb_text_cursor`

`function` | [headers/vga_fb.h:196](../../headers/vga_fb.h#L196)

```c
void vga_fb_text_cursor(int col);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `col` | `int` |  |  |

*Called by:* [`shell_focus_restore`](kernel.shell.c.md#shell_focus_restore)

---

<a id="vga_fb_hide_text_cursor"></a>

### `vga_fb_hide_text_cursor`

`function` | [headers/vga_fb.h:197](../../headers/vga_fb.h#L197)

```c
void vga_fb_hide_text_cursor(void);
```

---

<a id="fb_read_packed"></a>

### `fb_read_packed`

`function` | [headers/vga_fb.h:200](../../headers/vga_fb.h#L200)

```c
unsigned long fb_read_packed(int x, int y);
```

Packed-pixel primitives (0x00RRGGBB): the cursor layer draws through these so it never touches raw framebuffer memory itself.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `y` | `int` |  |  |

**Returns:** `unsigned long`

---

<a id="fb_write_packed"></a>

### `fb_write_packed`

`function` | [headers/vga_fb.h:201](../../headers/vga_fb.h#L201)

```c
void fb_write_packed(int x, int y, unsigned long rgb);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `y` | `int` |  |  |
| `rgb` | `unsigned long` |  |  |

*Called by:* [`once`](kernel.vga_fx.c.md#once)

---

<a id="vga_fb_draw_desktop"></a>

### `vga_fb_draw_desktop`

`function` | [headers/vga_fb.h:202](../../headers/vga_fb.h#L202)

```c
void vga_fb_draw_desktop(void);
```

*Called by:* [`ETREL_CHILD_STACK_SZ`](kernel.exec.c.md#etrel_child_stack_sz), [`k_run_rel`](kernel.exec.c.md#k_run_rel)

---

<a id="vga_fb_toggle_fullscreen"></a>

### `vga_fb_toggle_fullscreen`

`function` | [headers/vga_fb.h:203](../../headers/vga_fb.h#L203)

```c
void vga_fb_toggle_fullscreen(void);
```

*Called by:* [`key`](drivers.kbd.c.md#key)

---

<a id="vga_fb_move_terminal"></a>

### `vga_fb_move_terminal`

`function` | [headers/vga_fb.h:204](../../headers/vga_fb.h#L204)

```c
void vga_fb_move_terminal(int dx, int dy);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `dx` | `int` |  |  |
| `dy` | `int` |  |  |

*Called by:* [`key`](drivers.kbd.c.md#key)

---

<a id="vga_fb_snap_window"></a>

### `vga_fb_snap_window`

`function` | [headers/vga_fb.h:205](../../headers/vga_fb.h#L205)

```c
void vga_fb_snap_window(int zone);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `zone` | `int` |  |  |

---

<a id="vga_fb_resize"></a>

### `vga_fb_resize`

`function` | [headers/vga_fb.h:206](../../headers/vga_fb.h#L206)

```c
void vga_fb_resize(int dcols, int drows);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `dcols` | `int` |  |  |
| `drows` | `int` |  |  |

---

<a id="vga_fb_reset_default"></a>

### `vga_fb_reset_default`

`function` | [headers/vga_fb.h:207](../../headers/vga_fb.h#L207)

```c
void vga_fb_reset_default(void);
```

---

<a id="vga_fb_toggle_minimize"></a>

### `vga_fb_toggle_minimize`

`function` | [headers/vga_fb.h:208](../../headers/vga_fb.h#L208)

```c
void vga_fb_toggle_minimize(void);
```

---

<a id="vga_fb_is_minimized"></a>

### `vga_fb_is_minimized`

`function` | [headers/vga_fb.h:209](../../headers/vga_fb.h#L209)

```c
int vga_fb_is_minimized(void);
```

**Returns:** `int`

---

<a id="vga_fb_is_fullscreen"></a>

### `vga_fb_is_fullscreen`

`function` | [headers/vga_fb.h:210](../../headers/vga_fb.h#L210)

```c
int vga_fb_is_fullscreen(void);
```

**Returns:** `int`

---

<a id="vga_fb_gfx_set_fullscreen"></a>

### `vga_fb_gfx_set_fullscreen`

`function` | [headers/vga_fb.h:218](../../headers/vga_fb.h#L218)

```c
int vga_fb_gfx_set_fullscreen(int on);
```

Graphics window view (headers/wm_gfxview.h owns the math).

Fullscreen scales the app to the whole display with the aspect kept and takes the keyboard; hidden minimizes it to its taskbar button while it keeps running. Both glide between frames and return -1 without a program. The origin is the content top-left an app subtracts from SYS_MOUSE coordinates, and map_mouse converts a desktop pointer into the app's back-buffer space when its view is scaled (1:1 views pass through).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `on` | `int` |  |  |

**Returns:** `int`

*Called by:* [`from`](kernel.vga_fb.c.md#from), [`taskbar`](kernel.vga_fb.c.md#taskbar), [`vga_fb_toggle_fullscreen`](kernel.vga_fb.c.md#vga_fb_toggle_fullscreen)

---

<a id="vga_fb_gfx_set_hidden"></a>

### `vga_fb_gfx_set_hidden`

`function` | [headers/vga_fb.h:219](../../headers/vga_fb.h#L219)

```c
int vga_fb_gfx_set_hidden(int hide);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `hide` | `int` |  |  |

**Returns:** `int`

---

<a id="vga_fb_gfx_view_name"></a>

### `vga_fb_gfx_view_name`

`function` `const` | [headers/vga_fb.h:220](../../headers/vga_fb.h#L220)

```c
const char *vga_fb_gfx_view_name(void);
```

**Returns:** `char *`

---

<a id="vga_fb_gfx_origin"></a>

### `vga_fb_gfx_origin`

`function` | [headers/vga_fb.h:221](../../headers/vga_fb.h#L221)

```c
void vga_fb_gfx_origin(int *x, int *y);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int *` |  |  |
| `y` | `int *` |  |  |

*Called by:* [`DOOM_FRAME`](kernel.syscalls.c.md#doom_frame)

---

<a id="vga_fb_gfx_map_mouse"></a>

### `vga_fb_gfx_map_mouse`

`function` | [headers/vga_fb.h:222](../../headers/vga_fb.h#L222)

```c
void vga_fb_gfx_map_mouse(int *x, int *y);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int *` |  |  |
| `y` | `int *` |  |  |

---

<a id="fb_write_row_packed"></a>

### `fb_write_row_packed`

`function` | [headers/vga_fb.h:224](../../headers/vga_fb.h#L224)

```c
void fb_write_row_packed(int x, int y, const unsigned int *src, int n);
```

Row fast paths of the packed-pixel primitives (clipped once per row).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `y` | `int` |  |  |
| `src` | `unsigned int *` |  |  |
| `n` | `int` |  |  |

*Called by:* [`vga_fx_restore_rect`](kernel.vga_fx.c.md#vga_fx_restore_rect)

---

<a id="fb_read_row_packed"></a>

### `fb_read_row_packed`

`function` | [headers/vga_fb.h:225](../../headers/vga_fb.h#L225)

```c
void fb_read_row_packed(int x, int y, unsigned int *dst, int n);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `y` | `int` |  |  |
| `dst` | `unsigned int *` |  |  |
| `n` | `int` |  |  |

*Called by:* [`vga_fx_snap_rect`](kernel.vga_fx.c.md#vga_fx_snap_rect)

---

<a id="vga_fb_close_active"></a>

### `vga_fb_close_active`

`function` | [headers/vga_fb.h:226](../../headers/vga_fb.h#L226)

```c
int vga_fb_close_active(void);
```

**Returns:** `int`

---

<a id="vga_fb_focus_next"></a>

### `vga_fb_focus_next`

`function` | [headers/vga_fb.h:230](../../headers/vga_fb.h#L230)

```c
void vga_fb_focus_next(void);
```

Multi-window manager: Alt-Tab focus cycle, Super-Tab tiling, second * terminal.

Focus ids 0/1 = terminals, 2 = graphics window. define WM_FOCUS_GFX 2

---

<a id="vga_fb_focus_id"></a>

### `vga_fb_focus_id`

`function` | [headers/vga_fb.h:231](../../headers/vga_fb.h#L231)

```c
int vga_fb_focus_id(int id);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `id` | `int` |  |  |

**Returns:** `int`

---

<a id="vga_fb_focus_get"></a>

### `vga_fb_focus_get`

`function` | [headers/vga_fb.h:232](../../headers/vga_fb.h#L232)

```c
int vga_fb_focus_get(void);
```

**Returns:** `int`

---

<a id="vga_fb_focus_event"></a>

### `vga_fb_focus_event`

`function` `const` | [headers/vga_fb.h:235](../../headers/vga_fb.h#L235)

```c
const wm_notify_event_t *vga_fb_focus_event(void);
```

Focus event bus (wm_notify.h): last move for serial-observable state, plus programmatic reporting for focus moves owned by other units.

**Returns:** `wm_notify_event_t *`

---

<a id="vga_fb_focus_report"></a>

### `vga_fb_focus_report`

`function` | [headers/vga_fb.h:236](../../headers/vga_fb.h#L236)

```c
void vga_fb_focus_report(int before, int source);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `before` | `int` |  |  |
| `source` | `int` |  |  |

---

<a id="vga_fb_theme_name"></a>

### `vga_fb_theme_name`

`function` | [headers/vga_fb.h:237](../../headers/vga_fb.h#L237)

```c
int vga_fb_theme_name(char *dst, int cap);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `dst` | `char *` |  |  |
| `cap` | `int` |  |  |

**Returns:** `int`

---

<a id="vga_fb_ps2_owner"></a>

### `vga_fb_ps2_owner`

`function` | [headers/vga_fb.h:243](../../headers/vga_fb.h#L243)

```c
int vga_fb_ps2_owner(int pid);
```

PS/2 ownership for pid: 1 when pid may consume the keyboard port.

One keyboard feeds every window, so the focused window owns it: a background gfx job reads only while the gfx window is focused, the shell only while a terminal is. A legacy foreground program owns everything (its shell is blocked, so there is nobody to steal from). Serial stays shell-only.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `pid` | `int` |  |  |

**Returns:** `int`

*Called by:* [`kbd_read`](drivers.kbd.c.md#kbd_read)

---

<a id="vga_fb_nterms_get"></a>

### `vga_fb_nterms_get`

`function` | [headers/vga_fb.h:244](../../headers/vga_fb.h#L244)

```c
int vga_fb_nterms_get(void);
```

**Returns:** `int`

---

<a id="vga_fb_term_split"></a>

### `vga_fb_term_split`

`function` | [headers/vga_fb.h:245](../../headers/vga_fb.h#L245)

```c
int vga_fb_term_split(void);
```

**Returns:** `int`

*Called by:* [`content`](kernel.vga_fb.c.md#content)

---

<a id="vga_fb_term_close_focused"></a>

### `vga_fb_term_close_focused`

`function` | [headers/vga_fb.h:246](../../headers/vga_fb.h#L246)

```c
int vga_fb_term_close_focused(void);
```

**Returns:** `int`

---

<a id="vga_fb_tile_all"></a>

### `vga_fb_tile_all`

`function` | [headers/vga_fb.h:247](../../headers/vga_fb.h#L247)

```c
void vga_fb_tile_all(void);
```

*Called by:* [`alone`](kernel.vga_fb.c.md#alone), [`content`](kernel.vga_fb.c.md#content), [`vga_fb_layout_cycle`](kernel.vga_fb.c.md#vga_fb_layout_cycle)

---

<a id="vga_fb_layout_set"></a>

### `vga_fb_layout_set`

`function` | [headers/vga_fb.h:248](../../headers/vga_fb.h#L248)

```c
int vga_fb_layout_set(int mode);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `mode` | `int` |  |  |

**Returns:** `int`

---

<a id="vga_fb_layout_cycle"></a>

### `vga_fb_layout_cycle`

`function` | [headers/vga_fb.h:249](../../headers/vga_fb.h#L249)

```c
void vga_fb_layout_cycle(void);
```

---

<a id="vga_fb_layout_get"></a>

### `vga_fb_layout_get`

`function` | [headers/vga_fb.h:250](../../headers/vga_fb.h#L250)

```c
int vga_fb_layout_get(void);
```

**Returns:** `int`

---

<a id="vga_fb_layout_name"></a>

### `vga_fb_layout_name`

`function` `const` | [headers/vga_fb.h:251](../../headers/vga_fb.h#L251)

```c
const char *vga_fb_layout_name(void);
```

**Returns:** `char *`

---

<a id="vga_fb_list_windows"></a>

### `vga_fb_list_windows`

`function` | [headers/vga_fb.h:252](../../headers/vga_fb.h#L252)

```c
void vga_fb_list_windows(void);
```

---

<a id="wm_close_pending"></a>

### `wm_close_pending`

`function` | [headers/vga_fb.h:253](../../headers/vga_fb.h#L253)

```c
int wm_close_pending(void);
```

**Returns:** `int`

---

<a id="wm_clear_close"></a>

### `wm_clear_close`

`function` | [headers/vga_fb.h:254](../../headers/vga_fb.h#L254)

```c
void wm_clear_close(void);
```

---

<a id="wm_gfx_mode_active"></a>

### `wm_gfx_mode_active`

`function` | [headers/vga_fb.h:255](../../headers/vga_fb.h#L255)

```c
int wm_gfx_mode_active(void);
```

**Returns:** `int`

---

<a id="vga_fb_mouse_tick"></a>

### `vga_fb_mouse_tick`

`function` | [headers/vga_fb.h:256](../../headers/vga_fb.h#L256)

```c
void vga_fb_mouse_tick(void);
```

---

<a id="vga_fb_wait_tick"></a>

### `vga_fb_wait_tick`

`function` | [headers/vga_fb.h:260](../../headers/vga_fb.h#L260)

```c
void vga_fb_wait_tick(void);
```

Desktop tick for a kernel wait loop (foreground process wait, mrun): runs vga_fb_mouse_tick at DESKTOP_TICK_INTERVAL unless the exec frame's timer ISR already owns it.

*Called by:* [`code`](kernel.shell.c.md#code)

---

<a id="vga_fb_mouse_init"></a>

### `vga_fb_mouse_init`

`function` | [headers/vga_fb.h:261](../../headers/vga_fb.h#L261)

```c
void vga_fb_mouse_init(void);
```

---

<a id="dock_bounce_counts"></a>

### `dock_bounce_counts`

`function` | [headers/vga_fb.h:264](../../headers/vga_fb.h#L264)

```c
void dock_bounce_counts(unsigned long *kicks, unsigned long *paints);
```

Dock click bounce (Mac style): arm count and strip repaints while live, for the serial-observable proof (`wm state` reports both).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `kicks` | `unsigned long *` |  |  |
| `paints` | `unsigned long *` |  |  |

---

<a id="dock_click_count"></a>

### `dock_click_count`

`function` | [headers/vga_fb.h:265](../../headers/vga_fb.h#L265)

```c
void dock_click_count(unsigned long *edges);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `edges` | `unsigned long *` |  |  |

---

<a id="dock_pending_active"></a>

### `dock_pending_active`

`function` | [headers/vga_fb.h:266](../../headers/vga_fb.h#L266)

```c
int dock_pending_active(void);
```

**Returns:** `int`

---

<a id="pixels"></a>

### `pixels`

`function` | [headers/vga_fb.h:270](../../headers/vga_fb.h#L270)

```c
* are heap buffers of packed pixels (fb_read_packed order), 0 on OOM or a * degenerate rect. A disabled effect or a failed snapshot leaves the new * frame in place, so every entry fails closed to a pl
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `order` | `fb_read_packed` |  |  |

**Returns:** `* are heap buffers of packed`

*Called by:* [`ICON_PAL_SIZE`](headers.desktop_shortcuts.h.md#icon_pal_size)

---

<a id="vga_fx_enabled"></a>

### `vga_fx_enabled`

`function` | [headers/vga_fb.h:274](../../headers/vga_fb.h#L274)

```c
int vga_fx_enabled(void);
```

**Returns:** `int`

*Called by:* [`first`](kernel.vga_fb.c.md#first), [`vga_fb_draw_desktop`](kernel.vga_fb.c.md#vga_fb_draw_desktop), [`vga_fb_init`](kernel.vga_fb.c.md#vga_fb_init)

---

<a id="vga_fx_snap_rect"></a>

### `vga_fx_snap_rect`

`function` | [headers/vga_fb.h:275](../../headers/vga_fb.h#L275)

```c
unsigned int *vga_fx_snap_rect(int x, int y, int w, int h);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `y` | `int` |  |  |
| `w` | `int` |  |  |
| `h` | `int` |  |  |

**Returns:** `unsigned int *`

*Called by:* [`first`](kernel.vga_fb.c.md#first), [`vga_fb_draw_desktop`](kernel.vga_fb.c.md#vga_fb_draw_desktop), [`vga_fb_init`](kernel.vga_fb.c.md#vga_fb_init)

---

<a id="vga_fx_restore_rect"></a>

### `vga_fx_restore_rect`

`function` | [headers/vga_fb.h:276](../../headers/vga_fb.h#L276)

```c
void vga_fx_restore_rect(int x, int y, int w, int h, const unsigned int *buf);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `y` | `int` |  |  |
| `w` | `int` |  |  |
| `h` | `int` |  |  |
| `buf` | `unsigned int *` |  |  |

*Called by:* [`vga_fb_draw_desktop`](kernel.vga_fb.c.md#vga_fb_draw_desktop)

---

<a id="vga_fx_free"></a>

### `vga_fx_free`

`function` | [headers/vga_fb.h:277](../../headers/vga_fb.h#L277)

```c
void vga_fx_free(unsigned int *buf);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `buf` | `unsigned int *` |  |  |

*Called by:* [`vga_fb_draw_desktop`](kernel.vga_fb.c.md#vga_fb_draw_desktop), [`vga_fb_init`](kernel.vga_fb.c.md#vga_fb_init)

---

<a id="vga_fx_melt_rect"></a>

### `vga_fx_melt_rect`

`function` | [headers/vga_fb.h:278](../../headers/vga_fb.h#L278)

```c
void vga_fx_melt_rect(int x, int y, int w, int h, const unsigned int *oldb, const unsigned int *newb);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `y` | `int` |  |  |
| `w` | `int` |  |  |
| `h` | `int` |  |  |
| `oldb` | `unsigned int *` |  |  |
| `newb` | `unsigned int *` |  |  |

*Called by:* [`vga_fb_draw_desktop`](kernel.vga_fb.c.md#vga_fb_draw_desktop)

---

<a id="vga_fx_melt_from_black"></a>

### `vga_fx_melt_from_black`

`function` | [headers/vga_fb.h:280](../../headers/vga_fb.h#L280)

```c
void vga_fx_melt_from_black(int x, int y, int w, int h, const unsigned int *newb);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `y` | `int` |  |  |
| `w` | `int` |  |  |
| `h` | `int` |  |  |
| `newb` | `unsigned int *` |  |  |

*Called by:* [`vga_fb_init`](kernel.vga_fb.c.md#vga_fb_init)

---

<a id="vga_fx_burn_rect"></a>

### `vga_fx_burn_rect`

`function` | [headers/vga_fb.h:281](../../headers/vga_fb.h#L281)

```c
void vga_fx_burn_rect(int x, int y, int w, int h, const unsigned int *oldb, const unsigned int *newb, int stride);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `y` | `int` |  |  |
| `w` | `int` |  |  |
| `h` | `int` |  |  |
| `oldb` | `unsigned int *` |  |  |
| `newb` | `unsigned int *` |  |  |
| `stride` | `int` |  |  |

*Called by:* [`vga_fb_draw_desktop`](kernel.vga_fb.c.md#vga_fb_draw_desktop)

---

<a id="vga_fx_genie_rect"></a>

### `vga_fx_genie_rect`

`function` | [headers/vga_fb.h:283](../../headers/vga_fb.h#L283)

```c
void vga_fx_genie_rect(int wx, int wy, int ww, int wh, int tx, int ty, const unsigned int *bgb, const unsigned int *winb, int reverse);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `wx` | `int` |  |  |
| `wy` | `int` |  |  |
| `ww` | `int` |  |  |
| `wh` | `int` |  |  |
| `tx` | `int` |  |  |
| `ty` | `int` |  |  |
| `bgb` | `unsigned int *` |  |  |
| `winb` | `unsigned int *` |  |  |
| `reverse` | `int` |  |  |

---

<a id="vga_fb_set_gfx_mode"></a>

### `vga_fb_set_gfx_mode`

`function` | [headers/vga_fb.h:297](../../headers/vga_fb.h#L297)

```c
void vga_fb_set_gfx_mode(int on);
```

Graphics-mode pointer.

SYS_VGA_MODE toggles vga_fb_set_gfx_mode; while a ring-3 graphics program owns the display the kernel idle loop (and with it vga_fb_mouse_tick) never runs, so the frame-composite functions restore the previous frame's pointer before the blit and redraw it after, keeping the desktop pointer visible over the whole display without leaving trails.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `on` | `int` |  |  |

*Called by:* [`ETREL_CHILD_STACK_SZ`](kernel.exec.c.md#etrel_child_stack_sz), [`k_run_rel`](kernel.exec.c.md#k_run_rel)

---

## Macros

<a id="fb_addr"></a>

### `FB_ADDR`

`macro` | [headers/vga_fb.h:22](../../headers/vga_fb.h#L22)

```c
#define FB_ADDR
```

Framebuffer geometry.

The boot loader probes VESA BIOS Extensions for a high-resolution linear framebuffer (32-bit true color first, then the 8-bit-palette modes) and records width, height, pitch, physical base and bits per pixel in the fixed VBE_INFO_ADDR struct; vga_fb_boot_config loads them into the globals below before the kernel maps the framebuffer. Without VBE the values are the Mode 13h defaults (320x200x8, phys 0xA0000). In a true-color mode the kernel's palette-index drawing is expanded to RGB on write, so desktop, icons and wallpaper are no longer quantized to the 256-entry VGA DAC; in 8-bit mode the DAC path is used unchanged. FB_ADDR is the fixed virtual address in the user window that both the kernel desktop and graphics programs write through. It sits in the reserved tail above DOOM_BACKBUF_ADDR (which is also the brk cap), so a program's heap can never grow over the framebuffer. All three pinned addresses derive from progs/minios_abi.h (single source of truth for the kernel-ABI layout).

---

<a id="doom_w"></a>

### `DOOM_W`

`macro` | [headers/vga_fb.h:46](../../headers/vga_fb.h#L46)

```c
#define DOOM_W
```

Graphics-window compositing.

A ring-3 program (DOOM) renders into a kernel-backed back-buffer mapped into the user window at DOOM_BACKBUF_ADDR and calls SYS_DOOM_FRAME (211) to have the kernel composite it onto the desktop at its native resolution, so the shell window stays visible.

---

<a id="doom_backbuf_addr"></a>

### `DOOM_BACKBUF_ADDR`

`macro` | [headers/vga_fb.h:48](../../headers/vga_fb.h#L48)

```c
#define DOOM_BACKBUF_ADDR
```

---

<a id="gfx_title_default"></a>

### `GFX_TITLE_DEFAULT`

`macro` | [headers/vga_fb.h:52](../../headers/vga_fb.h#L52)

```c
#define GFX_TITLE_DEFAULT
```

Docstring: Default graphics window title before SYS_GFX_SET_TITLE.

---

<a id="nk_w"></a>

### `NK_W`

`macro` | [headers/vga_fb.h:67](../../headers/vga_fb.h#L67)

```c
#define NK_W
```

Nuklear UI back-buffer.

A ring-3 program (the node editor) renders a UI into a kernel-heap back-buffer mapped into the user window and calls SYS_NK_FRAME (220); the kernel composites it as a titled window on the desktop exactly like the DOOM window, so the shell stays visible. It sits in the reserved tail with the framebuffer, above DOOM_BACKBUF_ADDR (the brk cap), so neither a growing heap nor the mmap zone can ever reach it.

---

<a id="nk_backbuf_addr"></a>

### `NK_BACKBUF_ADDR`

`macro` | [headers/vga_fb.h:69](../../headers/vga_fb.h#L69)

```c
#define NK_BACKBUF_ADDR
```

---

<a id="nk_rgb_addr"></a>

### `NK_RGB_ADDR`

`macro` | [headers/vga_fb.h:73](../../headers/vga_fb.h#L73)

```c
#define NK_RGB_ADDR
```

RGB companion buffer (3 bytes per pixel, R,G,B order, NK_W x NK_H).

Mapped by mm_setup_protections like the indexed buffers; presented with GFX_PRESENT + MINIOS_GFX_BUF_NK_RGB through vga_fb_blit_nk_rgb_window.

---

<a id="nk_rgb_bytes"></a>

### `NK_RGB_BYTES`

`macro` | [headers/vga_fb.h:74](../../headers/vga_fb.h#L74)

```c
#define NK_RGB_BYTES
```

---

<a id="col_black"></a>

### `COL_BLACK`

`macro` | [headers/vga_fb.h:82](../../headers/vga_fb.h#L82)

```c
#define COL_BLACK
```

Palette indices

---

<a id="col_bg"></a>

### `COL_BG`

`macro` | [headers/vga_fb.h:83](../../headers/vga_fb.h#L83)

```c
#define COL_BG
```

---

<a id="col_taskbar"></a>

### `COL_TASKBAR`

`macro` | [headers/vga_fb.h:84](../../headers/vga_fb.h#L84)

```c
#define COL_TASKBAR
```

---

<a id="col_taskbar_txt"></a>

### `COL_TASKBAR_TXT`

`macro` | [headers/vga_fb.h:85](../../headers/vga_fb.h#L85)

```c
#define COL_TASKBAR_TXT
```

---

<a id="col_titlebar"></a>

### `COL_TITLEBAR`

`macro` | [headers/vga_fb.h:86](../../headers/vga_fb.h#L86)

```c
#define COL_TITLEBAR
```

---

<a id="col_title_txt"></a>

### `COL_TITLE_TXT`

`macro` | [headers/vga_fb.h:87](../../headers/vga_fb.h#L87)

```c
#define COL_TITLE_TXT
```

---

<a id="col_terminal"></a>

### `COL_TERMINAL`

`macro` | [headers/vga_fb.h:88](../../headers/vga_fb.h#L88)

```c
#define COL_TERMINAL
```

---

<a id="col_term_txt"></a>

### `COL_TERM_TXT`

`macro` | [headers/vga_fb.h:89](../../headers/vga_fb.h#L89)

```c
#define COL_TERM_TXT
```

---

<a id="col_term_cur"></a>

### `COL_TERM_CUR`

`macro` | [headers/vga_fb.h:90](../../headers/vga_fb.h#L90)

```c
#define COL_TERM_CUR
```

---

<a id="col_border"></a>

### `COL_BORDER`

`macro` | [headers/vga_fb.h:91](../../headers/vga_fb.h#L91)

```c
#define COL_BORDER
```

---

<a id="col_white"></a>

### `COL_WHITE`

`macro` | [headers/vga_fb.h:92](../../headers/vga_fb.h#L92)

```c
#define COL_WHITE
```

---

<a id="col_shadow"></a>

### `COL_SHADOW`

`macro` | [headers/vga_fb.h:93](../../headers/vga_fb.h#L93)

```c
#define COL_SHADOW
```

---

<a id="col_highlight"></a>

### `COL_HIGHLIGHT`

`macro` | [headers/vga_fb.h:94](../../headers/vga_fb.h#L94)

```c
#define COL_HIGHLIGHT
```

---

<a id="col_scrollbar"></a>

### `COL_SCROLLBAR`

`macro` | [headers/vga_fb.h:95](../../headers/vga_fb.h#L95)

```c
#define COL_SCROLLBAR
```

---

<a id="col_scroll_thumb"></a>

### `COL_SCROLL_THUMB`

`macro` | [headers/vga_fb.h:96](../../headers/vga_fb.h#L96)

```c
#define COL_SCROLL_THUMB
```

---

<a id="wallpaper_path"></a>

### `WALLPAPER_PATH`

`macro` | [headers/vga_fb.h:103](../../headers/vga_fb.h#L103)

```c
#define WALLPAPER_PATH
```

Wallpaper: a photographic background on the 8-bit desktop.

The image file below (800x600 RGB PNG on the ramdisk, produced by tools/gen_desktop_pngs.py) is decoded once per boot via stbi_load_file, stretched to the framebuffer and mapped to a fixed 6x6x6 websafe cube at DAC 16-231, clear of the desktop (0-14) and icon (240-255) ranges.

---

<a id="wall_pal_base"></a>

### `WALL_PAL_BASE`

`macro` | [headers/vga_fb.h:104](../../headers/vga_fb.h#L104)

```c
#define WALL_PAL_BASE
```

---

<a id="wall_pal_size"></a>

### `WALL_PAL_SIZE`

`macro` | [headers/vga_fb.h:105](../../headers/vga_fb.h#L105)

```c
#define WALL_PAL_SIZE
```

---

<a id="font_w"></a>

### `FONT_W`

`macro` | [headers/vga_fb.h:107](../../headers/vga_fb.h#L107)

```c
#define FONT_W
```

---

<a id="term_max_cols"></a>

### `TERM_MAX_COLS`

`macro` | [headers/vga_fb.h:113](../../headers/vga_fb.h#L113)

```c
#define TERM_MAX_COLS
```

Upper bound on the terminal's size, used to size the live-screen buffer and the scrollback ring.

The framebuffer dimensions are clamped to these before any buffer is indexed, so a very large display never overruns them.

---

<a id="term_max_rows"></a>

### `TERM_MAX_ROWS`

`macro` | [headers/vga_fb.h:114](../../headers/vga_fb.h#L114)

```c
#define TERM_MAX_ROWS
```

---

<a id="taskbar_pad"></a>

### `TASKBAR_PAD`

`macro` | [headers/vga_fb.h:118](../../headers/vga_fb.h#L118)

```c
#define TASKBAR_PAD
```

---

<a id="taskbar_clock_ch"></a>

### `TASKBAR_CLOCK_CH`

`macro` | [headers/vga_fb.h:119](../../headers/vga_fb.h#L119)

```c
#define TASKBAR_CLOCK_CH
```

---

<a id="taskbar_vol_ch"></a>

### `TASKBAR_VOL_CH`

`macro` | [headers/vga_fb.h:120](../../headers/vga_fb.h#L120)

```c
#define TASKBAR_VOL_CH
```

"HH:MM:SS"

---

<a id="taskbar_vol_step"></a>

### `TASKBAR_VOL_STEP`

`macro` | [headers/vga_fb.h:121](../../headers/vga_fb.h#L121)

```c
#define TASKBAR_VOL_STEP
```

"NN%"

---

<a id="taskbar_icon_w"></a>

### `TASKBAR_ICON_W`

`macro` | [headers/vga_fb.h:122](../../headers/vga_fb.h#L122)

```c
#define TASKBAR_ICON_W
```

---

<a id="taskbar_btn_w"></a>

### `TASKBAR_BTN_W`

`macro` | [headers/vga_fb.h:123](../../headers/vga_fb.h#L123)

```c
#define TASKBAR_BTN_W
```

---

<a id="taskbar_kbd_ch"></a>

### `TASKBAR_KBD_CH`

`macro` | [headers/vga_fb.h:125](../../headers/vga_fb.h#L125)

```c
#define TASKBAR_KBD_CH
```

Keyboard-layout widget: two-letter "EN"/"ES" label, click toggles.

---

<a id="taskbar_kbd_w"></a>

### `TASKBAR_KBD_W`

`macro` | [headers/vga_fb.h:126](../../headers/vga_fb.h#L126)

```c
#define TASKBAR_KBD_W
```

"EN" / "ES"

---

<a id="taskbar_theme_ch"></a>

### `TASKBAR_THEME_CH`

`macro` | [headers/vga_fb.h:128](../../headers/vga_fb.h#L128)

```c
#define TASKBAR_THEME_CH
```

Theme widget: active theme name (clamped to 6 chars), click cycles.

---

<a id="taskbar_theme_w"></a>

### `TASKBAR_THEME_W`

`macro` | [headers/vga_fb.h:129](../../headers/vga_fb.h#L129)

```c
#define TASKBAR_THEME_W
```

---

<a id="tiling_left"></a>

### `TILING_LEFT`

`macro` | [headers/vga_fb.h:132](../../headers/vga_fb.h#L132)

```c
#define TILING_LEFT
```

Tiling snap zones (Alt is the WM modifier).

---

<a id="tiling_right"></a>

### `TILING_RIGHT`

`macro` | [headers/vga_fb.h:133](../../headers/vga_fb.h#L133)

```c
#define TILING_RIGHT
```

---

<a id="tiling_top"></a>

### `TILING_TOP`

`macro` | [headers/vga_fb.h:134](../../headers/vga_fb.h#L134)

```c
#define TILING_TOP
```

---

<a id="tiling_bottom"></a>

### `TILING_BOTTOM`

`macro` | [headers/vga_fb.h:135](../../headers/vga_fb.h#L135)

```c
#define TILING_BOTTOM
```

---

<a id="tiling_top_left"></a>

### `TILING_TOP_LEFT`

`macro` | [headers/vga_fb.h:136](../../headers/vga_fb.h#L136)

```c
#define TILING_TOP_LEFT
```

---

<a id="tiling_top_right"></a>

### `TILING_TOP_RIGHT`

`macro` | [headers/vga_fb.h:137](../../headers/vga_fb.h#L137)

```c
#define TILING_TOP_RIGHT
```

---

<a id="tiling_bottom_left"></a>

### `TILING_BOTTOM_LEFT`

`macro` | [headers/vga_fb.h:138](../../headers/vga_fb.h#L138)

```c
#define TILING_BOTTOM_LEFT
```

---

<a id="tiling_bottom_right"></a>

### `TILING_BOTTOM_RIGHT`

`macro` | [headers/vga_fb.h:139](../../headers/vga_fb.h#L139)

```c
#define TILING_BOTTOM_RIGHT
```

---

<a id="scrollbar_w"></a>

### `SCROLLBAR_W`

`macro` | [headers/vga_fb.h:142](../../headers/vga_fb.h#L142)

```c
#define SCROLLBAR_W
```

Scrollbar geometry

---

<a id="scrollbar_pad"></a>

### `SCROLLBAR_PAD`

`macro` | [headers/vga_fb.h:143](../../headers/vga_fb.h#L143)

```c
#define SCROLLBAR_PAD
```

---

<a id="wm_btn_w"></a>

### `WM_BTN_W`

`macro` | [headers/vga_fb.h:148](../../headers/vga_fb.h#L148)

```c
#define WM_BTN_W
```

Title-bar window controls (minimize, maximize, close).

Drawn as a strip of three FONT_W-wide glyph buttons at the right end of any titled window (terminal, DOOM, Nuklear); the mouse tick hit-tests them before drag.

---

<a id="wm_btn_pad"></a>

### `WM_BTN_PAD`

`macro` | [headers/vga_fb.h:150](../../headers/vga_fb.h#L150)

```c
#define WM_BTN_PAD
```

---

<a id="wm_btn_min"></a>

### `WM_BTN_MIN`

`macro` | [headers/vga_fb.h:151](../../headers/vga_fb.h#L151)

```c
#define WM_BTN_MIN
```

---

<a id="wm_btn_max"></a>

### `WM_BTN_MAX`

`macro` | [headers/vga_fb.h:152](../../headers/vga_fb.h#L152)

```c
#define WM_BTN_MAX
```

---

<a id="wm_btn_close"></a>

### `WM_BTN_CLOSE`

`macro` | [headers/vga_fb.h:153](../../headers/vga_fb.h#L153)

```c
#define WM_BTN_CLOSE
```

---

<a id="sb_max_lines"></a>

### `SB_MAX_LINES`

`macro` | [headers/vga_fb.h:173](../../headers/vga_fb.h#L173)

```c
#define SB_MAX_LINES
```

A scrollback line can be up to the widest terminal (TERM_MAX_COLS), and a long logical line that wrapped across several screen rows is stored whole, so the ring must not truncate it or a re-rendered line would be cut short.

---

<a id="sb_line_max"></a>

### `SB_LINE_MAX`

`macro` | [headers/vga_fb.h:174](../../headers/vga_fb.h#L174)

```c
#define SB_LINE_MAX
```

---

<a id="wm_focus_gfx"></a>

### `WM_FOCUS_GFX`

`macro` | [headers/vga_fb.h:229](../../headers/vga_fb.h#L229)

```c
#define WM_FOCUS_GFX
```

Multi-window manager: Alt-Tab focus cycle, Super-Tab tiling, second terminal.

Focus ids 0/1 = terminals, 2 = graphics window.

---

## Variables

<a id="fb_width"></a>

### `fb_width`

`variable` `extern` | [headers/vga_fb.h:23](../../headers/vga_fb.h#L23)

```c
extern int fb_width;
```

high-resolution linear framebuffer (32-bit true color first, then the 8-bit-palette modes) and records width, height, pitch, physical base and bits per pixel in the fixed VBE_INFO_ADDR struct; vga_fb_boot_config loads them into the globals below before the kernel maps the framebuffer.

Without VBE the values are the Mode 13h defaults (320x200x8, phys 0xA0000). In a true-color mode the kernel's palette-index drawing is expanded to RGB on write, so desktop, icons and wallpaper are no longer quantized to the 256-entry VGA DAC; in 8-bit mode the DAC path is used unchanged. FB_ADDR is the fixed virtual address in the user window that both the kernel desktop and graphics programs write through. It sits in the reserved tail above DOOM_BACKBUF_ADDR (which is also the brk cap), so a program's heap can never grow over the framebuffer. All three pinned addresses derive from * progs/minios_abi.h (single source of truth for the kernel-ABI layout). define FB_ADDR    ((volatile uint8_t *)MINIOS_FB_ADDR)

---

<a id="fb_height"></a>

### `fb_height`

`variable` `extern` | [headers/vga_fb.h:24](../../headers/vga_fb.h#L24)

```c
extern int fb_height;
```

---

<a id="fb_pitch"></a>

### `fb_pitch`

`variable` `extern` | [headers/vga_fb.h:25](../../headers/vga_fb.h#L25)

```c
extern int fb_pitch;
```

---

<a id="fb_bpp"></a>

### `fb_bpp`

`variable` `extern` | [headers/vga_fb.h:26](../../headers/vga_fb.h#L26)

```c
extern int fb_bpp;
```

---

<a id="fb_phys_base"></a>

### `fb_phys_base`

`variable` `extern` | [headers/vga_fb.h:27](../../headers/vga_fb.h#L27)

```c
extern unsigned long fb_phys_base;
```

---

<a id="gfx_win_title"></a>

### `gfx_win_title`

`variable` `const` `extern` | [headers/vga_fb.h:50](../../headers/vga_fb.h#L50)

```c
extern const char *gfx_win_title;
```

---

<a id="gfx_frames_composited"></a>

### `gfx_frames_composited`

`variable` `extern` | [headers/vga_fb.h:59](../../headers/vga_fb.h#L59)

```c
extern unsigned long gfx_frames_composited;
```

Number of frames a ring-3 graphics program (DOOM, Quake 2, Nuklear) has composited through SYS_DOOM_FRAME / SYS_NK_FRAME since boot.

The shell's `gfx frames` builtin reports it over the serial console, so the BDD suite can prove a game actually rendered frames -- not merely launched -- by running a demo and checking the counter climbed.

---

<a id="nk_win_y"></a>

### `nk_win_y`

`variable` `extern` | [headers/vga_fb.h:79](../../headers/vga_fb.h#L79)

```c
extern int nk_win_x, nk_win_y;
```

Window origin of the last Nuklear composite, so SYS_NK_FRAME can report where the UI landed for mouse-coordinate translation.

---

<a id="term_rows"></a>

### `term_rows`

`variable` `extern` | [headers/vga_fb.h:156](../../headers/vga_fb.h#L156)

```c
extern int term_x, term_y, term_cols, term_rows;
```

Terminal geometry (set by vga_fb layout engine)

---

<a id="mouse_state"></a>

### `mouse_state`

`variable` `extern` | [headers/vga_fb.h:167](../../headers/vga_fb.h#L167)

```c
extern mouse_state_t mouse_state;
```

---

<a id="fx_melts_completed"></a>

### `fx_melts_completed`

`variable` `extern` | [headers/vga_fb.h:288](../../headers/vga_fb.h#L288)

```c
extern unsigned long fx_melts_completed;
```

Melt transitions completed since boot (boot melt counts, so a fresh shell already reports 1 with the effect on).

Serial-observable proof the melts ran, in the same spirit as `gfx frames`.

---

<a id="fx_burns_completed"></a>

### `fx_burns_completed`

`variable` `extern` | [headers/vga_fb.h:289](../../headers/vga_fb.h#L289)

```c
extern unsigned long fx_burns_completed;
```

---

<a id="fx_genies_completed"></a>

### `fx_genies_completed`

`variable` `extern` | [headers/vga_fb.h:290](../../headers/vga_fb.h#L290)

```c
extern unsigned long fx_genies_completed;
```

---

<a id="vga_fb_active"></a>

### `vga_fb_active`

`variable` `extern` | [headers/vga_fb.h:299](../../headers/vga_fb.h#L299)

```c
extern int vga_fb_active;
```

---
