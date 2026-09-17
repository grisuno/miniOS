# headers

*Community 7 | 10 files | cohesion 0.63*

## Definition

This community groups 10 file(s) rooted at `headers` with dominant language h (cohesion 0.63). Central symbols: `CHECK`, `DESKTOP_ICONS_H`, `DESKTOP_SHORTCUTS_H`, `DOCK_GAP`, `DOCK_LABEL_GAP`, `DOCK_PAD_X`, `DOCK_PAD_Y`, `FB_OFFSET`. Core file: `kernel/vga_fb.c` (177 symbols). Documented purpose: Docstring: Render pipeline contract for the MiniOS desktop..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/desktop_icons.h` | h | utility | 3 | yes |
| `headers/desktop_shortcuts.h` | h | utility | 20 | yes |
| `headers/wm_focus.h` | h | utility | 6 | yes |
| `headers/wm_geom.h` | h | utility | 11 | yes |
| `headers/wm_layout.h` | h | presentation | 16 | yes |
| `headers/wm_render.h` | h | presentation | 5 | yes |
| `headers/wm_tiling.h` | h | utility | 3 | yes |
| `headers/wm_window.h` | h | utility | 12 | yes |
| `kernel/vga_fb.c` | c | utility | 177 | no |
| `tests/test_wm.c` | c | testing | 6 | yes |

## Key Symbols

- `DESKTOP_ICONS_H` (macro, `headers/desktop_icons.h:8`) `#define DESKTOP_ICONS_H`
- `ICON_EMBEDDED_W` (macro, `headers/desktop_icons.h:11`) `#define ICON_EMBEDDED_W`
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
- `WM_FOCUS_H` (macro, `headers/wm_focus.h:10`) `#define WM_FOCUS_H`
- `wm_focus_state_t` (struct, `headers/wm_focus.h:15`) - Docstring: Focus manager contract for the MiniOS desktop.  Single-file header-only contract owning f
- `wm_focus_selectable` (function, `headers/wm_focus.h:23`) `static inline int wm_focus_selectable(const wm_focus_state_t *st, int id)` - #ifndef WM_FOCUS_H #define WM_FOCUS_H #include "wm_window.h" /** Docstring: Focus state snapshot con
- `wm_focus_next` (function, `headers/wm_focus.h:38`) `static inline int wm_focus_next(const wm_focus_state_t *st)` - { if (st == 0) { return 0; } if (id == WM_WINDOW_GFX_ID) { return st->gfx_active ? 1 : 0; } if (id <
- `wm_focus_next_id` (function, `headers/wm_focus.h:51`) `return wm_focus_next_id(flat, st->nterms > 4 ? 4 : st->nterms, st->gfx_active, s`
- `wm_focus_set` (function, `headers/wm_focus.h:55`) `static inline int wm_focus_set(const wm_focus_state_t *st, int id)` - int i; if (st == 0) { return 0; } for (i = 0; i < 4; i++) { flat[i] = 0; } for (i = 0; i < st->nterm
- `WM_GEOM_H` (macro, `headers/wm_geom.h:11`) `#define WM_GEOM_H`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 17
- Cross-boundary resolved imports (EXTRACTED): 10

## Connections

- [EXTRACTED] depends_on community 3 <-> 7 (strength 0.9): Extracted import edge crosses communities: kernel/shell.c imports headers/wm_layout.h.
- [EXTRACTED] depends_on community 7 <-> 0 (strength 0.9): Extracted import edge crosses communities: kernel/vga_fb.c imports headers/arch/x86/boot/bootdefs.h.
- [EXTRACTED] depends_on community 7 <-> 2 (strength 0.9): Extracted import edge crosses communities: kernel/vga_fb.c imports headers/sched.h.

## Risks

- [layer strict] `tests/test_wm.c` (testing) -> `headers/wm_render.h` (presentation)
- [layer strict] `tests/test_wm.c` (testing) -> `headers/wm_layout.h` (presentation)

## Open Questions

- Why do 1 file(s) lack file-level docs (e.g. `kernel/vga_fb.c`)? What purpose do they serve?
- What would break if the most connected file in headers changed?
- Should headers be split, given cohesion 0.63?

## Sources

- `headers/desktop_icons.h`
- `headers/desktop_shortcuts.h`
- `headers/wm_focus.h`
- `headers/wm_geom.h`
- `headers/wm_layout.h`
- `headers/wm_render.h`
- `headers/wm_tiling.h`
- `headers/wm_window.h`
- `kernel/vga_fb.c`
- `tests/test_wm.c`
