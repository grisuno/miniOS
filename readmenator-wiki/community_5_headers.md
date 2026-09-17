# headers

*Community 5 | 10 files | cohesion 0.33*

## Definition

This community groups 10 file(s) rooted at `headers` with dominant language h (cohesion 0.33). Central symbols: `CHECK`, `DESKTOP_ICONS_H`, `DESKTOP_SHORTCUTS_H`, `DOCK_GAP`, `DOCK_LABEL_GAP`, `DOCK_PAD_X`, `DOCK_PAD_Y`, `FB_OFFSET`. Core file: `kernel/vga_fb.c` (150 symbols). Documented purpose: embedded icon pixel data for desktop shortcuts..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/desktop_icons.h` | h | utility | 3 | yes |
| `headers/desktop_shortcuts.h` | h | utility | 20 | yes |
| `headers/drivers/modifiers.h` | h | infrastructure | 11 | yes |
| `headers/wm_events.h` | h | infrastructure | 39 | yes |
| `headers/wm_layout.h` | h | presentation | 16 | yes |
| `headers/wm_notify.h` | h | utility | 9 | yes |
| `headers/wm_tiling.h` | h | utility | 3 | yes |
| `kernel/vga_fb.c` | c | utility | 150 | no |
| `tests/test_modifiers.c` | c | testing | 2 | no |
| `tests/test_notify.c` | c | testing | 3 | no |

## Key Symbols

- `DESKTOP_ICONS_H` (macro, `headers/desktop_icons.h:8`) `#define DESKTOP_ICONS_H`
- `ICON_EMBEDDED_W` (macro, `headers/desktop_icons.h:12`) `#define ICON_EMBEDDED_W`
- `ICON_EMBEDDED_H` (macro, `headers/desktop_icons.h:13`) `#define ICON_EMBEDDED_H`
- `DESKTOP_SHORTCUTS_H` (macro, `headers/desktop_shortcuts.h:13`) `#define DESKTOP_SHORTCUTS_H`
- `MAX_SHORTCUTS` (macro, `headers/desktop_shortcuts.h:18`) `#define MAX_SHORTCUTS`
- `SHORTCUT_NAME_LEN` (macro, `headers/desktop_shortcuts.h:19`) `#define SHORTCUT_NAME_LEN`
- `SHORTCUT_CMD_LEN` (macro, `headers/desktop_shortcuts.h:20`) `#define SHORTCUT_CMD_LEN`
- `SHORTCUT_PATH_LEN` (macro, `headers/desktop_shortcuts.h:21`) `#define SHORTCUT_PATH_LEN`
- `ICON_W` (macro, `headers/desktop_shortcuts.h:24`) `#define ICON_W`
- `ICON_H` (macro, `headers/desktop_shortcuts.h:25`) `#define ICON_H`
- `ICON_PAD_X` (macro, `headers/desktop_shortcuts.h:26`) `#define ICON_PAD_X`
- `ICON_PAD_Y` (macro, `headers/desktop_shortcuts.h:27`) `#define ICON_PAD_Y`
- `ICON_LABEL_H` (macro, `headers/desktop_shortcuts.h:28`) `#define ICON_LABEL_H`
- `DOCK_PAD_X` (macro, `headers/desktop_shortcuts.h:33`) `#define DOCK_PAD_X`
- `DOCK_PAD_Y` (macro, `headers/desktop_shortcuts.h:34`) `#define DOCK_PAD_Y`
- `DOCK_GAP` (macro, `headers/desktop_shortcuts.h:35`) `#define DOCK_GAP`
- `DOCK_LABEL_GAP` (macro, `headers/desktop_shortcuts.h:36`) `#define DOCK_LABEL_GAP`
- `ICON_PAL_BASE` (macro, `headers/desktop_shortcuts.h:43`) `#define ICON_PAL_BASE`
- `ICON_PAL_SIZE` (macro, `headers/desktop_shortcuts.h:44`) `#define ICON_PAL_SIZE`
- `desktop_shortcut` (struct, `headers/desktop_shortcuts.h:50`) - A decoded+cached desktop shortcut. Pixels are raw RGBA bytes (ICON_W*ICON_H*4): the PNG's own colors
- `desktop_shortcuts_load` (function, `headers/desktop_shortcuts.h:60`) `void desktop_shortcuts_load(void);` - Load shortcuts from etc/shortcuts, decode icons, compute layout. * Called once from vga_fb_draw_desk
- `desktop_shortcuts_draw` (function, `headers/desktop_shortcuts.h:63`) `void desktop_shortcuts_draw(void);` - Load shortcuts from etc/shortcuts, decode icons, compute layout. * Called once from vga_fb_draw_desk
- `desktop_shortcuts_hit_test` (function, `headers/desktop_shortcuts.h:67`) `const char *desktop_shortcuts_hit_test(int mx, int my);` - Handle a left-click at (mx, my).  Returns the command string if the * click hit an icon, or NULL oth
- `MODIFIERS_H` (macro, `headers/drivers/modifiers.h:2`) `#define MODIFIERS_H`
- `modifier_state_t` (struct, `headers/drivers/modifiers.h:5`) - #ifndef MODIFIERS_H #define MODIFIERS_H /** Docstring: Unified modifier tracking for cooked and raw
- `modifier_keys_t` (struct, `headers/drivers/modifiers.h:14`) - #ifndef MODIFIERS_H #define MODIFIERS_H /** Docstring: Unified modifier tracking for cooked and raw
- `MOD_SHIFT` (macro, `headers/drivers/modifiers.h:24`) `#define MOD_SHIFT`
- `MOD_CTRL` (macro, `headers/drivers/modifiers.h:25`) `#define MOD_CTRL`
- `MOD_ALT` (macro, `headers/drivers/modifiers.h:26`) `#define MOD_ALT`
- `MOD_ALTGR` (macro, `headers/drivers/modifiers.h:27`) `#define MOD_ALTGR`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 9
- Cross-boundary resolved imports (EXTRACTED): 18

## Connections

- [EXTRACTED] depends_on community 0 <-> 5 (strength 0.9): Extracted import edge crosses communities: drivers/kbd.c imports headers/drivers/modifiers.h.
- [EXTRACTED] depends_on community 5 <-> 7 (strength 0.9): Extracted import edge crosses communities: kernel/vga_fb.c imports headers/wm_geom.h.
- [INFERRED] shares_context community 1 <-> 5 (strength 0.5): Inferred shared context (layer utility) with no import path between community 1 (headers) and community 5 (headers).

## Risks

- [layer strict] `tests/test_wm.c` (testing) -> `headers/wm_layout.h` (presentation)
- [dataflow DEAD_STORE] `kernel/vga_fb.c:1884` `taskbar_render` `lx`: `lx` assigned at line 1884 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:2221` `line` `rows_before`: `rows_before` assigned at line 2221 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:2717` `icon_decode` `dst`: `dst` assigned at line 2717 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:2736` `icon_embedded_rgba` `dst`: `dst` assigned at line 2736 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:3072` `vga_fb_mouse_tick` `gcfg`: `gcfg` assigned at line 3072 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:3073` `vga_fb_mouse_tick` `ecfg`: `ecfg` assigned at line 3073 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:3075` `vga_fb_mouse_tick` `win_w`: `win_w` assigned at line 3075 but never read afterwards.

## Open Questions

- Why do 3 file(s) lack file-level docs (e.g. `kernel/vga_fb.c`)? What purpose do they serve?
- What would break if the most connected file in headers changed?
- Should headers be split, given cohesion 0.33?

## Sources

- `headers/desktop_icons.h`
- `headers/desktop_shortcuts.h`
- `headers/drivers/modifiers.h`
- `headers/wm_events.h`
- `headers/wm_layout.h`
- `headers/wm_notify.h`
- `headers/wm_tiling.h`
- `kernel/vga_fb.c`
- `tests/test_modifiers.c`
- `tests/test_notify.c`
