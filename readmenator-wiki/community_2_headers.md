# headers

*Community 2 | 11 files | cohesion 0.63*

## Definition

This community groups 11 file(s) rooted at `headers` with dominant language h (cohesion 0.63). Central symbols: `CHECK`, `DESKTOP_ICONS_H`, `DESKTOP_SHORTCUTS_H`, `DOCK_BOUNCE_H`, `DOCK_BOUNCE_TICKS`, `DOCK_CRYSTAL_STEP`, `DOCK_GAP`, `DOCK_LABEL_GAP`. Core file: `kernel/vga_fb.c` (167 symbols). Documented purpose: embedded icon pixel data for desktop shortcuts..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/desktop_icons.h` | h | utility | 3 | yes |
| `headers/desktop_shortcuts.h` | h | utility | 27 | yes |
| `headers/wm_events.h` | h | infrastructure | 39 | yes |
| `headers/wm_focus.h` | h | utility | 5 | yes |
| `headers/wm_geom.h` | h | utility | 11 | yes |
| `headers/wm_layout.h` | h | presentation | 16 | yes |
| `headers/wm_render.h` | h | presentation | 5 | yes |
| `headers/wm_tiling.h` | h | utility | 3 | yes |
| `headers/wm_window.h` | h | utility | 10 | yes |
| `kernel/vga_fb.c` | c | utility | 167 | no |
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

- Internal resolved imports (EXTRACTED): 19
- Cross-boundary resolved imports (EXTRACTED): 11

## Connections

- [EXTRACTED] depends_on community 0 <-> 2 (strength 0.9): Extracted import edge crosses communities: drivers/kbd.c imports headers/wm_events.h.
- [EXTRACTED] depends_on community 2 <-> 3 (strength 0.9): Extracted import edge crosses communities: headers/wm_events.h imports headers/drivers/modifiers.h.
- [INFERRED] shares_context community 1 <-> 2 (strength 0.5): Inferred shared context (layer utility) with no import path between community 1 (progs/doomgeneric) and community 2 (headers).
- [INFERRED] shares_context community 2 <-> 4 (strength 0.5): Inferred shared context (layer utility) with no import path between community 2 (headers) and community 4 (headers).
- [INFERRED] shares_context community 2 <-> 5 (strength 0.5): Inferred shared context (layer utility) with no import path between community 2 (headers) and community 5 (tools).
- [INFERRED] shares_context community 2 <-> 6 (strength 0.5): Inferred shared context (language h and layer utility) with no import path between community 2 (headers) and community 6 (progs/doomgeneric).
- [INFERRED] shares_context community 2 <-> 7 (strength 0.5): Inferred shared context (layer utility) with no import path between community 2 (headers) and community 7 (progs/src).

## Risks

- [layer strict] `tests/test_wm.c` (testing) -> `headers/wm_render.h` (presentation)
- [layer strict] `tests/test_wm.c` (testing) -> `headers/wm_layout.h` (presentation)
- [dataflow DEAD_STORE] `kernel/vga_fb.c:2112` `taskbar_render` `lx`: `lx` assigned at line 2112 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:2449` `line` `rows_before`: `rows_before` assigned at line 2449 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:2885` `wallpaper_ensure` `dst`: `dst` assigned at line 2885 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:3011` `icon_decode` `dst`: `dst` assigned at line 3011 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:3030` `icon_embedded_rgba` `dst`: `dst` assigned at line 3030 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:3584` `vga_fb_mouse_tick` `gcfg`: `gcfg` assigned at line 3584 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:3585` `vga_fb_mouse_tick` `ecfg`: `ecfg` assigned at line 3585 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/vga_fb.c:3587` `vga_fb_mouse_tick` `win_w`: `win_w` assigned at line 3587 but never read afterwards.

## Open Questions

- Why do 1 file(s) lack file-level docs (e.g. `kernel/vga_fb.c`)? What purpose do they serve?
- What would break if the most connected file in headers changed?
- Should headers be split, given cohesion 0.63?

## Sources

- `headers/desktop_icons.h`
- `headers/desktop_shortcuts.h`
- `headers/wm_events.h`
- `headers/wm_focus.h`
- `headers/wm_geom.h`
- `headers/wm_layout.h`
- `headers/wm_render.h`
- `headers/wm_tiling.h`
- `headers/wm_window.h`
- `kernel/vga_fb.c`
- `tests/test_wm.c`
