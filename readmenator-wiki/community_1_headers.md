# headers

*Community 1 | 32 files | cohesion 0.57*

## Definition

This community groups 32 file(s) rooted at `headers` with dominant language h (cohesion 0.57). Central symbols: `CHECK`, `CMD_BUF_SZ`, `COL_BG`, `COL_BLACK`, `COL_BORDER`, `COL_HIGHLIGHT`, `COL_SCROLLBAR`, `COL_SCROLL_THUMB`. Core file: `kernel/vga_fb.c` (161 symbols). Documented purpose: embedded icon pixel data for desktop shortcuts..

## Files

### `headers` (16 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/desktop_icons.h` | h | utility | 3 | yes |
| `headers/desktop_shortcuts.h` | h | utility | 25 | yes |
| `headers/editor.h` | h | infrastructure | 2 | yes |
| `headers/minifetch.h` | h | utility | 2 | yes |
| `headers/shell.h` | h | utility | 7 | yes |
| `headers/vga_fb.h` | h | utility | 138 | yes |

### `kernel` (7 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/console_in.c` | c | utility | 26 | yes |
| `kernel/editor.c` | c | infrastructure | 22 | yes |
| `kernel/loader.c` | c | utility | 38 | yes |
| `kernel/shell.c` | c | utility | 80 | yes |
| `kernel/vga_cursor.c` | c | utility | 13 | yes |

### `tests` (4 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_fx.c` | c | testing | 2 | yes |
| `tests/test_modifiers.c` | c | testing | 2 | no |
| `tests/test_notify.c` | c | testing | 3 | no |
| `tests/test_wm.c` | c | testing | 2 | yes |

### `headers/drivers` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/drivers/kbd.h` | h | infrastructure | 23 | yes |
| `headers/drivers/modifiers.h` | h | infrastructure | 11 | yes |

### `headers/kernel` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/kernel/console_in.h` | h | utility | 8 | yes |
| `headers/kernel/vga_cursor.h` | h | utility | 9 | yes |

### `drivers` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `drivers/kbd.c` | c | infrastructure | 34 | yes |

*... and 12 more files in this community.*


## Key Symbols

- `kbd_get_layout` (function, `drivers/kbd.c:100`) `int kbd_get_layout(void)`
- `kbd_set_layout` (function, `drivers/kbd.c:101`) `void kbd_set_layout(int layout)`
- `kbd_toggle_layout` (function, `drivers/kbd.c:105`) `void kbd_toggle_layout(void)`
- `kbd_shift` (macro, `drivers/kbd.c:115`) `#define kbd_shift`
- `kbd_ctrl` (macro, `drivers/kbd.c:116`) `#define kbd_ctrl`
- `kbd_alt` (macro, `drivers/kbd.c:117`) `#define kbd_alt`
- `kbd_super` (macro, `drivers/kbd.c:118`) `#define kbd_super`
- `kbd_altgr` (macro, `drivers/kbd.c:119`) `#define kbd_altgr`
- `KBD_QUEUE_LEN` (macro, `drivers/kbd.c:121`) `#define KBD_QUEUE_LEN`
- `KBD_SCAN_DEL` (macro, `drivers/kbd.c:122`) `#define KBD_SCAN_DEL`
- `kbd_drop_counts` (function, `drivers/kbd.c:132`) `void kbd_drop_counts(unsigned long *cooked, unsigned long *raw)` - #define kbd_super (kbd_mods.super) #define kbd_altgr (kbd_mods.altgr) #define KBD_QUEUE_LEN 8 #defin
- `KBD_RAW_LEN` (macro, `drivers/kbd.c:141`) `#define KBD_RAW_LEN`
- `kbd_q_push` (function, `drivers/kbd.c:146`) `void kbd_q_push(unsigned char c)`
- `kbd_raw_push_internal` (function, `drivers/kbd.c:156`) `static void kbd_raw_push_internal(unsigned char c)`
- `kbd_q_empty` (function, `drivers/kbd.c:166`) `int kbd_q_empty(void)`
- `kbd_q_pop` (function, `drivers/kbd.c:168`) `int kbd_q_pop(void)`
- `kbd_available` (function, `drivers/kbd.c:175`) `int kbd_available(void)`
- `kbd_raw_mode_get` (function, `drivers/kbd.c:181`) `int kbd_raw_mode_get(void)`
- `kbd_raw_mode_set` (function, `drivers/kbd.c:182`) `void kbd_raw_mode_set(int on)`
- `kbd_raw_empty` (function, `drivers/kbd.c:183`) `int kbd_raw_empty(void)`
- `kbd_raw_pop` (function, `drivers/kbd.c:184`) `int kbd_raw_pop(void)`
- `kbd_raw_push_byte` (function, `drivers/kbd.c:190`) `void kbd_raw_push_byte(unsigned char c)`
- `kbd_e0_get` (function, `drivers/kbd.c:191`) `int kbd_e0_get(void)`
- `kbd_e0_set` (function, `drivers/kbd.c:192`) `void kbd_e0_set(int v)`
- `kbd_flush_all` (function, `drivers/kbd.c:193`) `void kbd_flush_all(void)`
- `kbd_raw_flush` (function, `drivers/kbd.c:200`) `void kbd_raw_flush(void)` - Drop queued raw scancodes (shell-typed while a terminal owned PS/2) so a * newly focused game never
- `paths` (function, `drivers/kbd.c:210`) `* keeps the modifier state in sync on both paths (the old raw branch never * tra`
- `too` (function, `drivers/kbd.c:215`) `* too (DOOM strafes with Alt+arrows);`
- `raw_track_mods` (function, `drivers/kbd.c:221`) `static int raw_track_mods(int code, int brk, int e0)`
- `wm_combo_dispatch` (function, `drivers/kbd.c:226`) `static int wm_combo_dispatch(int action, int zone)` - wm_raw_combo performs the WM action and reports 1 when the byte must be swallowed. Deliberately narr

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 53
- Cross-boundary resolved imports (EXTRACTED): 40

## Connections

- [EXTRACTED] depends_on community 1 <-> 0 (strength 0.9): Extracted import edge crosses communities: drivers/kbd.c imports headers/kernel.h.
- [EXTRACTED] depends_on community 1 <-> 3 (strength 0.9): Extracted import edge crosses communities: headers/vga_fb.h imports progs/minios_abi.h.
- [EXTRACTED] depends_on community 1 <-> 5 (strength 0.9): Extracted import edge crosses communities: kernel/shell.c imports headers/net.h.
- [INFERRED] shares_context community 1 <-> 2 (strength 0.5): Inferred shared context (layer utility) with no import path between community 1 (headers) and community 2 (headers).
- [INFERRED] shares_context community 1 <-> 4 (strength 0.5): Inferred shared context (layer utility) with no import path between community 1 (headers) and community 4 (headers).
- [INFERRED] shares_context community 1 <-> 7 (strength 0.5): Inferred shared context (layer utility) with no import path between community 1 (headers) and community 7 (tools).

## Risks

- [layer strict] `tests/test_wm.c` (testing) -> `headers/wm_render.h` (presentation)
- [layer strict] `tests/test_wm.c` (testing) -> `headers/wm_layout.h` (presentation)
- [dataflow DEAD_STORE] `kernel/loader.c:458` `load_exec_elf` `base`: `base` assigned at line 458 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/loader.c:463` `load_exec_elf` `max_end`: `max_end` assigned at line 463 but never read afterwards.
- [dataflow UNINIT_USE] `kernel/shell.c:1533` `context` `buf`: `buf` may be read before initialization (declared line 1525).
- [dataflow DEAD_STORE] `kernel/vga_fb.c:2092` `taskbar_render` `lx`: `lx` assigned at line 2092 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:2429` `line` `rows_before`: `rows_before` assigned at line 2429 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:2865` `wallpaper_ensure` `dst`: `dst` assigned at line 2865 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:2991` `icon_decode` `dst`: `dst` assigned at line 2991 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:3010` `icon_embedded_rgba` `dst`: `dst` assigned at line 3010 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:3469` `vga_fb_mouse_tick` `gcfg`: `gcfg` assigned at line 3469 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:3470` `vga_fb_mouse_tick` `ecfg`: `ecfg` assigned at line 3470 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:3472` `vga_fb_mouse_tick` `win_w`: `win_w` assigned at line 3472 but never read afterwards.

## Open Questions

- Why do 3 file(s) lack file-level docs (e.g. `kernel/vga_fb.c`)? What purpose do they serve?
- What would break if the most connected file in headers changed?
- Should headers be split, given cohesion 0.57?

## Sources

- `drivers/kbd.c`
- `headers/desktop_icons.h`
- `headers/desktop_shortcuts.h`
- `headers/drivers/kbd.h`
- `headers/drivers/modifiers.h`
- `headers/editor.h`
- `headers/kernel/console_in.h`
- `headers/kernel/vga_cursor.h`
- `headers/minifetch.h`
- `headers/shell.h`
- `headers/vga_fb.h`
- `headers/vga_fx.h`
- `headers/wm_events.h`
- `headers/wm_focus.h`
- `headers/wm_geom.h`
- `headers/wm_layout.h`
- `headers/wm_notify.h`
- `headers/wm_render.h`
- `headers/wm_tiling.h`
- `headers/wm_window.h`
- *... and 12 more*
