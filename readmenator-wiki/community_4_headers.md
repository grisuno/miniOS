# headers

*Community 4 | 33 files | cohesion 0.63*

## Definition

This community groups 33 file(s) rooted at `headers` with dominant language h (cohesion 0.63). Central symbols: `CHECK`, `CONSOLE_IN_H`, `CURSOR_H`, `CURSOR_TIP_X`, `CURSOR_TIP_Y`, `CURSOR_W`, `Consumers`, `DESKTOP_ICONS_H`. Core file: `drivers/xhci.c` (209 symbols). Documented purpose: Docstring: PS/2 mouse device driver (drivers/mouse.c)..

## Files

### `headers` (11 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/desktop_icons.h` | h | utility | 3 | yes |
| `headers/desktop_shortcuts.h` | h | utility | 27 | yes |
| `headers/vga_fx.h` | h | utility | 9 | yes |
| `headers/wm_events.h` | h | infrastructure | 39 | yes |

### `tests` (6 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_fx.c` | c | testing | 2 | yes |
| `tests/test_hal_io.c` | c | testing | 3 | yes |
| `tests/test_modifiers.c` | c | testing | 2 | yes |
| `tests/test_usbhid.c` | c | testing | 5 | yes |

### `headers/drivers` (5 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/drivers/kbd.h` | h | infrastructure | 24 | yes |
| `headers/drivers/modifiers.h` | h | infrastructure | 11 | yes |
| `headers/drivers/mouse.h` | h | infrastructure | 4 | yes |

### `drivers` (4 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `drivers/kbd.c` | c | infrastructure | 35 | yes |
| `drivers/mouse.c` | c | infrastructure | 7 | yes |
| `drivers/usbhid.c` | c | infrastructure | 26 | yes |

### `kernel` (4 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/console_in.c` | c | utility | 31 | yes |
| `kernel/vga_cursor.c` | c | utility | 13 | yes |
| `kernel/vga_fb.c` | c | utility | 200 | no |

### `headers/kernel` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/kernel/console_in.h` | h | utility | 11 | yes |
| `headers/kernel/vga_cursor.h` | h | utility | 9 | yes |

### `headers/arch/x86` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/arch/x86/hal_io.h` | h | utility | 69 | yes |

*... and 13 more files in this community.*


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

- Internal resolved imports (EXTRACTED): 52
- Cross-boundary resolved imports (EXTRACTED): 31

## Connections

- [EXTRACTED] depends_on community 4 <-> 10 (strength 0.9): Extracted import edge crosses communities: drivers/kbd.c imports headers/sched.h.
- [EXTRACTED] depends_on community 4 <-> 0 (strength 0.9): Extracted import edge crosses communities: drivers/kbd.c imports headers/vga_fb.h.
- [EXTRACTED] depends_on community 2 <-> 4 (strength 0.9): Extracted import edge crosses communities: drivers/nvme.c imports headers/arch/x86/hal_io.h.
- [EXTRACTED] depends_on community 3 <-> 4 (strength 0.9): Extracted import edge crosses communities: drivers/usbblk.c imports headers/drivers/xhci.h.
- [EXTRACTED] depends_on community 9 <-> 4 (strength 0.9): Extracted import edge crosses communities: headers/shell.h imports headers/kernel/console_in.h.

## Risks

- [layer strict] `tests/test_wm.c` (testing) -> `headers/wm_render.h` (presentation)
- [layer strict] `tests/test_wm.c` (testing) -> `headers/wm_layout.h` (presentation)
- [layer strict] `tests/test_wm.c` (testing) -> `headers/wm_gfxview.h` (presentation)
- [dataflow DEAD_STORE] `kernel/vga_fb.c:2452` `taskbar_render` `lx`: `lx` assigned at line 2452 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:2822` `line` `rows_before`: `rows_before` assigned at line 2822 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:3515` `wallpaper_ensure` `d`: `d` assigned at line 3515 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:3640` `icon_decode` `dst`: `dst` assigned at line 3640 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:3659` `icon_embedded_rgba` `dst`: `dst` assigned at line 3659 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:4218` `vga_fb_mouse_tick` `gcfg`: `gcfg` assigned at line 4218 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:4219` `vga_fb_mouse_tick` `ecfg`: `ecfg` assigned at line 4219 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:4221` `vga_fb_mouse_tick` `win_w`: `win_w` assigned at line 4221 but never read afterwards.

## Open Questions

- Why do 1 file(s) lack file-level docs (e.g. `kernel/vga_fb.c`)? What purpose do they serve?
- What would break if the most connected file in headers changed?
- Should headers be split, given cohesion 0.63?

## Sources

- `drivers/kbd.c`
- `drivers/mouse.c`
- `drivers/usbhid.c`
- `drivers/xhci.c`
- `headers/arch/x86/hal_io.h`
- `headers/desktop_icons.h`
- `headers/desktop_shortcuts.h`
- `headers/drivers/kbd.h`
- `headers/drivers/modifiers.h`
- `headers/drivers/mouse.h`
- `headers/drivers/usbhid.h`
- `headers/drivers/xhci.h`
- `headers/kernel/console_in.h`
- `headers/kernel/vga_cursor.h`
- `headers/vga_fx.h`
- `headers/wm_events.h`
- `headers/wm_focus.h`
- `headers/wm_geom.h`
- `headers/wm_gfxview.h`
- `headers/wm_layout.h`
- *... and 13 more*
