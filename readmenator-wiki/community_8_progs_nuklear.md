# progs/nuklear

*Community 8 | 39 files | cohesion 0.66*

## Definition

This community groups 39 file(s) rooted at `progs/nuklear` with dominant language c (cohesion 0.66). Central symbols: `AllocTracker`, `BACKBUF`, `BEZIER_PAD`, `BK_H`, `BK_W`, `BTN_GAP`, `BTN_W`, `BUF`. Core file: `progs/vedit/vedit.c` (239 symbols). Documented purpose: tile map editor that builds playable Doom PWADs..

## Files

### `progs/nuklear` (8 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/nuklear/cvm_emit.c` | c | utility | 56 | yes |
| `progs/nuklear/cvm_emit.h` | h | utility | 6 | yes |

### `progs/src` (7 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/src/audio.c` | c | infrastructure | 17 | no |
| `progs/src/fptest.c` | c | testing | 9 | yes |

### `progs/wl` (5 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/wl/wl_client.h` | h | infrastructure | 5 | yes |
| `progs/wl/wl_mbox.h` | h | utility | 26 | yes |

### `tests` (5 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_file_assoc.c` | c | testing | 10 | yes |
| `tests/test_freedom_wl.c` | c | testing | 3 | yes |

### `progs` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/minios_abi.h` | h | utility | 142 | yes |

### `progs/file` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/file/file.c` | c | utility | 63 | yes |

### `progs/doomedit` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/doomedit/doomedit.c` | c | infrastructure | 108 | yes |

### `progs/freedomui` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/freedomui/freedomui_minios.c` | c | presentation | 42 | yes |

### `progs/lisp` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/lisp/lisp.c` | c | utility | 105 | no |

### `progs/micropython/variants/minios` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/micropython/variants/minios/minios_module.c` | c | utility | 21 | no |

### `progs/minicraft` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/minicraft/minicraft.c` | c | utility | 237 | yes |

### `progs/paint` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/paint/paint.c` | c | utility | 53 | yes |

### `progs/piano` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/piano/piano.c` | c | utility | 65 | yes |

### `progs/quake2generic` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/quake2generic/snddma_minios.c` | c | utility | 16 | yes |

### `progs/vedit` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/vedit/vedit.c` | c | infrastructure | 239 | yes |

### `tools` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tools/abi_stamp.c` | c | utility | 1 | yes |

*... and 19 more files in this community.*


## Key Symbols

- `DMAP_MAX_W` (macro, `progs/doomedit/doomedit.c:55`) `#define DMAP_MAX_W`
- `DMAP_MAX_H` (macro, `progs/doomedit/doomedit.c:56`) `#define DMAP_MAX_H`
- `DMAP_DEF_W` (macro, `progs/doomedit/doomedit.c:57`) `#define DMAP_DEF_W`
- `DMAP_DEF_H` (macro, `progs/doomedit/doomedit.c:58`) `#define DMAP_DEF_H`
- `DMAP_TILE` (macro, `progs/doomedit/doomedit.c:59`) `#define DMAP_TILE`
- `DMAP_CELL_PX` (macro, `progs/doomedit/doomedit.c:60`) `#define DMAP_CELL_PX`
- `DMAP_CANVAS_W` (macro, `progs/doomedit/doomedit.c:61`) `#define DMAP_CANVAS_W`
- `DMAP_PANEL_MIN_H` (macro, `progs/doomedit/doomedit.c:62`) `#define DMAP_PANEL_MIN_H`
- `DMAP_PREV_W` (macro, `progs/doomedit/doomedit.c:63`) `#define DMAP_PREV_W`
- `DMAP_PREV_H` (macro, `progs/doomedit/doomedit.c:64`) `#define DMAP_PREV_H`
- `DMAP_UI_MEMORY` (macro, `progs/doomedit/doomedit.c:65`) `#define DMAP_UI_MEMORY`
- `DMAP_WAD_MAX` (macro, `progs/doomedit/doomedit.c:66`) `#define DMAP_WAD_MAX`
- `DMAP_FNAME_MAX` (macro, `progs/doomedit/doomedit.c:67`) `#define DMAP_FNAME_MAX`
- `DMAP_STATUS_MAX` (macro, `progs/doomedit/doomedit.c:68`) `#define DMAP_STATUS_MAX`
- `DMAP_SLOTS` (macro, `progs/doomedit/doomedit.c:69`) `#define DMAP_SLOTS`
- `DMAP_LEVEL_COUNT` (macro, `progs/doomedit/doomedit.c:70`) `#define DMAP_LEVEL_COUNT`
- `DMAP_RANDOM_ATTEMPTS` (macro, `progs/doomedit/doomedit.c:71`) `#define DMAP_RANDOM_ATTEMPTS`
- `DMAP_MAX_SECTORS` (macro, `progs/doomedit/doomedit.c:72`) `#define DMAP_MAX_SECTORS`
- `DMAP_ROOM_MAX` (macro, `progs/doomedit/doomedit.c:73`) `#define DMAP_ROOM_MAX`
- `DMAP_ROOM_TRIES` (macro, `progs/doomedit/doomedit.c:74`) `#define DMAP_ROOM_TRIES`
- `DMAP_FRAME_MS` (macro, `progs/doomedit/doomedit.c:75`) `#define DMAP_FRAME_MS`
- `DMAP_TURN_STEP` (macro, `progs/doomedit/doomedit.c:76`) `#define DMAP_TURN_STEP`
- `DMAP_MOVE_STEP` (macro, `progs/doomedit/doomedit.c:77`) `#define DMAP_MOVE_STEP`
- `DMAP_FOV_PLANE` (macro, `progs/doomedit/doomedit.c:78`) `#define DMAP_FOV_PLANE`
- `DMAP_MAX_LINES` (macro, `progs/doomedit/doomedit.c:79`) `#define DMAP_MAX_LINES`
- `DMAP_MAX_VERTS` (macro, `progs/doomedit/doomedit.c:80`) `#define DMAP_MAX_VERTS`
- `DMAP_MAX_THINGS` (macro, `progs/doomedit/doomedit.c:81`) `#define DMAP_MAX_THINGS`
- `DMAP_PLAYER_TYPE` (macro, `progs/doomedit/doomedit.c:82`) `#define DMAP_PLAYER_TYPE`
- `DMAP_THING_OPT` (macro, `progs/doomedit/doomedit.c:83`) `#define DMAP_THING_OPT`
- `DMAP_EXIT_SPECIAL` (macro, `progs/doomedit/doomedit.c:84`) `#define DMAP_EXIT_SPECIAL`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 63
- Cross-boundary resolved imports (EXTRACTED): 32

## Connections

- [EXTRACTED] depends_on community 0 <-> 8 (strength 0.9): Extracted import edge crosses communities: headers/kernel.h imports progs/minios_abi.h.
- [EXTRACTED] depends_on community 8 <-> 6 (strength 0.9): Extracted import edge crosses communities: progs/doomedit/doomedit.c imports kernel/string.c.
- [EXTRACTED] depends_on community 8 <-> 2 (strength 0.9): Extracted import edge crosses communities: progs/file/file.c imports progs/minios_png.h.
- [EXTRACTED] depends_on community 9 <-> 8 (strength 0.9): Extracted import edge crosses communities: progs/lua/minios.c imports progs/minios_abi.h.

## Risks

- [taint high] `mcp/mcp_dbg_driver.py` -> `progs/minios_abi.h` via `subprocess` (3 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `progs/minios_abi.h` via `subprocess` (3 hops)
- [layer strict] `tests/test_freedomui.c` (testing) -> `progs/freedomui/freedomui_minios.c` (presentation)
- [dataflow DEAD_STORE] `progs/doomedit/doomedit.c:1556` `dmap_build_wad` `side`: `side` assigned at line 1556 but never read afterwards.
- [dataflow DEAD_STORE] `progs/doomedit/doomedit.c:1633` `dmap_build_wad` `dir`: `dir` assigned at line 1633 but never read afterwards.
- [dataflow DEAD_STORE] `progs/doomedit/doomedit.c:2145` `dmap_selftest` `mrgb`: `mrgb` assigned at line 2145 but never read afterwards.

## Open Questions

- Why do 4 file(s) lack file-level docs (e.g. `progs/lisp/lisp.c`)? What purpose do they serve?
- What would break if the most connected file in progs/nuklear changed?
- Should progs/nuklear be split, given cohesion 0.66?

## Sources

- `progs/doomedit/doomedit.c`
- `progs/file/file.c`
- `progs/file/file_assoc.h`
- `progs/freedomui/freedomui_minios.c`
- `progs/lisp/lisp.c`
- `progs/micropython/variants/minios/minios_module.c`
- `progs/minicraft/minicraft.c`
- `progs/minios_abi.h`
- `progs/nk_palette.h`
- `progs/nuklear/cvm_emit.c`
- `progs/nuklear/cvm_emit.h`
- `progs/nuklear/font8x8.c`
- `progs/nuklear/node_editor.c`
- `progs/nuklear/nuklear_minios.c`
- `progs/nuklear/nuklear_minios.h`
- `progs/nuklear/nuklear_theme.c`
- `progs/nuklear/nuklear_theme.h`
- `progs/paint/paint.c`
- `progs/piano/piano.c`
- `progs/quake2generic/snddma_minios.c`
- *... and 19 more*
