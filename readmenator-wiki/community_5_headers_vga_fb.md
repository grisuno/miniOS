# headers: vga_fb

*Community 5 | 18 files | cohesion 0.70*

## Definition

This community groups 18 file(s) rooted at `headers` with dominant language h (cohesion 0.70). Central symbols: `CHECK`, `CURSOR_H`, `CURSOR_TIP_X`, `CURSOR_TIP_Y`, `CURSOR_W`, `DESKTOP_ICONS_H`, `DESKTOP_SHORTCUTS_H`, `DOCK_BOUNCE_H`. Core file: `kernel/vga_fb.c` (200 symbols). Documented purpose: embedded icon pixel data for desktop shortcuts..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/desktop_icons.h` | h | utility | 3 | yes |
| `headers/desktop_shortcuts.h` | h | utility | 27 | yes |
| `headers/kernel/vga_cursor.h` | h | utility | 9 | yes |
| `headers/vga_fx.h` | h | utility | 9 | yes |
| `headers/wm_focus.h` | h | utility | 5 | yes |
| `headers/wm_geom.h` | h | utility | 11 | yes |
| `headers/wm_gfxview.h` | h | utility | 15 | yes |
| `headers/wm_layout.h` | h | presentation | 16 | yes |
| `headers/wm_notify.h` | h | utility | 9 | yes |
| `headers/wm_render.h` | h | presentation | 5 | yes |
| `headers/wm_tiling.h` | h | utility | 3 | yes |
| `headers/wm_window.h` | h | utility | 10 | yes |
| `kernel/vga_cursor.c` | c | utility | 13 | yes |
| `kernel/vga_fb.c` | c | utility | 200 | no |
| `kernel/vga_fx.c` | c | utility | 9 | yes |
| `tests/test_fx.c` | c | testing | 2 | yes |
| `tests/test_notify.c` | c | testing | 3 | no |
| `tests/test_wm.c` | c | testing | 2 | yes |

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
- `DOCK_CRYSTAL_STEP` (macro, `headers/desktop_shortcuts.h:41`) `#define DOCK_CRYSTAL_STEP`
- `DOCK_MAG_W` (macro, `headers/desktop_shortcuts.h:48`) `#define DOCK_MAG_W`
- `DOCK_MAG_H` (macro, `headers/desktop_shortcuts.h:49`) `#define DOCK_MAG_H`
- `DOCK_NEAR_W` (macro, `headers/desktop_shortcuts.h:50`) `#define DOCK_NEAR_W`
- `DOCK_NEAR_H` (macro, `headers/desktop_shortcuts.h:51`) `#define DOCK_NEAR_H`
- `DOCK_BOUNCE_H` (macro, `headers/desktop_shortcuts.h:57`) `#define DOCK_BOUNCE_H`
- `DOCK_BOUNCE_TICKS` (macro, `headers/desktop_shortcuts.h:58`) `#define DOCK_BOUNCE_TICKS`
- `ICON_PAL_BASE` (macro, `headers/desktop_shortcuts.h:65`) `#define ICON_PAL_BASE`
- `ICON_PAL_SIZE` (macro, `headers/desktop_shortcuts.h:66`) `#define ICON_PAL_SIZE`
- `desktop_shortcut` (struct, `headers/desktop_shortcuts.h:72`) - A decoded+cached desktop shortcut. Pixels are raw RGBA bytes (ICON_W*ICON_H*4): the PNG's own colors
- `desktop_shortcuts_load` (function, `headers/desktop_shortcuts.h:82`) `void desktop_shortcuts_load(void);` - Load shortcuts from etc/shortcuts, decode icons, compute layout. * Called once from vga_fb_draw_desk
- `desktop_shortcuts_draw` (function, `headers/desktop_shortcuts.h:85`) `void desktop_shortcuts_draw(void);` - Load shortcuts from etc/shortcuts, decode icons, compute layout. * Called once from vga_fb_draw_desk
- `desktop_shortcuts_hit_test` (function, `headers/desktop_shortcuts.h:89`) `const char *desktop_shortcuts_hit_test(int mx, int my);` - Handle a left-click at (mx, my).  Returns the command string if the * click hit an icon, or NULL oth

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 26
- Cross-boundary resolved imports (EXTRACTED): 11

## Connections

- [EXTRACTED] depends_on community 0 <-> 5 (strength 0.9): Extracted import edge crosses communities: headers/vga_fb.h imports headers/wm_notify.h.
- [INFERRED] shares_context community 1 <-> 5 (strength 0.5): Inferred shared context (language h and layer utility) with no import path between community 1 (progs/doomgeneric: d_englsh) and community 5 (headers: vga_fb).
- [INFERRED] shares_context community 2 <-> 5 (strength 0.5): Inferred shared context (layer utility) with no import path between community 2 (progs/doomgeneric: p_spec) and community 5 (headers: vga_fb).

## Risks

- [layer strict] `tests/test_wm.c` (testing) -> `headers/wm_render.h` (presentation)
- [layer strict] `tests/test_wm.c` (testing) -> `headers/wm_layout.h` (presentation)
- [dataflow DEAD_STORE] `kernel/vga_fb.c:2452` `taskbar_render` `lx`: `lx` assigned at line 2452 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:2822` `line` `rows_before`: `rows_before` assigned at line 2822 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:3515` `wallpaper_ensure` `d`: `d` assigned at line 3515 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:3640` `icon_decode` `dst`: `dst` assigned at line 3640 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:3659` `icon_embedded_rgba` `dst`: `dst` assigned at line 3659 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:4218` `vga_fb_mouse_tick` `gcfg`: `gcfg` assigned at line 4218 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:4219` `vga_fb_mouse_tick` `ecfg`: `ecfg` assigned at line 4219 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:4221` `vga_fb_mouse_tick` `win_w`: `win_w` assigned at line 4221 but never read afterwards.

## Open Questions

- Why do 2 file(s) lack file-level docs (e.g. `kernel/vga_fb.c`)? What purpose do they serve?
- What would break if the most connected file in headers: vga_fb changed?
- Should headers: vga_fb be split, given cohesion 0.70?

## Sources

- `headers/desktop_icons.h`
- `headers/desktop_shortcuts.h`
- `headers/kernel/vga_cursor.h`
- `headers/vga_fx.h`
- `headers/wm_focus.h`
- `headers/wm_geom.h`
- `headers/wm_gfxview.h`
- `headers/wm_layout.h`
- `headers/wm_notify.h`
- `headers/wm_render.h`
- `headers/wm_tiling.h`
- `headers/wm_window.h`
- `kernel/vga_cursor.c`
- `kernel/vga_fb.c`
- `kernel/vga_fx.c`
- `tests/test_fx.c`
- `tests/test_notify.c`
- `tests/test_wm.c`
