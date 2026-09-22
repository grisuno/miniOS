# progs/src

*Community 8 | 60 files | cohesion 0.66*

## Definition

This community groups 60 file(s) rooted at `progs/src` with dominant language c (cohesion 0.66). Central symbols: `AllocTracker`, `BACKBUF`, `BEZIER_PAD`, `BK_H`, `BK_W`, `BTN_GAP`, `BTN_W`, `BUF`. Core file: `progs/minicraft/minicraft.c` (237 symbols). Documented purpose: Kernel string and memory functions..

## Files

### `progs/src` (10 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/src/audio.c` | c | infrastructure | 17 | no |

### `progs/doomgeneric` (9 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/doomgeneric/doomgeneric.c` | c | utility | 1 | no |

### `progs/nuklear` (8 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/nuklear/cvm_emit.c` | c | utility | 56 | yes |

### `tests` (7 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_file_assoc.c` | c | testing | 10 | yes |

### `progs/wl` (5 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/wl/wl_client.h` | h | infrastructure | 5 | yes |

### `progs` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/minios_abi.h` | h | utility | 138 | yes |

### `progs/file` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/file/file.c` | c | utility | 63 | yes |

### `progs/lua` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/lua/lua_main.c` | c | utility | 7 | no |

### `progs/quake2generic` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/quake2generic/q2generic_minios.c` | c | utility | 32 | yes |

### `kernel` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/string.c` | c | utility | 13 | yes |

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

### `progs/micropython/variants/minios/lib` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/micropython/variants/minios/lib/hello.py` | py | utility | 0 | yes |

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

### `progs/tls_u` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/tls_u/tls_u_port.c` | c | utility | 15 | yes |

### `progs/topogpt3` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/topogpt3/topogpt3.c` | c | utility | 128 | no |

*... and 40 more files in this community.*


## Key Symbols

- `kstrlen` (function, `kernel/string.c:17`) `unsigned long kstrlen(const char *s)`
- `kstrcpy` (function, `kernel/string.c:23`) `char *kstrcpy(char *dst, const char *src)`
- `kstrncpy` (function, `kernel/string.c:29`) `char *kstrncpy(char *dst, const char *src, unsigned long n)`
- `kstrncat` (function, `kernel/string.c:35`) `char *kstrncat(char *dst, const char *src, unsigned long n)`
- `kstrcmp` (function, `kernel/string.c:43`) `int kstrcmp(const char *a, const char *b)`
- `kstrncmp` (function, `kernel/string.c:48`) `int kstrncmp(const char *a, const char *b, unsigned long n)`
- `kstrchr` (function, `kernel/string.c:53`) `char *kstrchr(const char *s, int c)`
- `kstrstr` (function, `kernel/string.c:58`) `char *kstrstr(const char *hay, const char *ndl)`
- `kmemcpy` (function, `kernel/string.c:68`) `void *kmemcpy(void *dst, const void *src, unsigned long n)`
- `kmemset` (function, `kernel/string.c:75`) `void *kmemset(void *dst, int c, unsigned long n)`
- `kmemcmp` (function, `kernel/string.c:81`) `int kmemcmp(const void *a, const void *b, unsigned long n)`
- `kmemmove` (function, `kernel/string.c:87`) `void *kmemmove(void *dst, const void *src, unsigned long n)`
- `katol` (function, `kernel/string.c:95`) `long katol(const char *s)`
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

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 110
- Cross-boundary resolved imports (EXTRACTED): 57

## Connections

- [EXTRACTED] depends_on community 0 <-> 8 (strength 0.9): Extracted import edge crosses communities: headers/kernel.h imports progs/minios_abi.h.
- [EXTRACTED] depends_on community 7 <-> 8 (strength 0.9): Extracted import edge crosses communities: headers/tls_port.h imports kernel/string.c.
- [EXTRACTED] depends_on community 10 <-> 8 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/d_iwad.c imports kernel/string.c.
- [EXTRACTED] depends_on community 8 <-> 9 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/doomgeneric_xlib.c imports kernel/time.c.
- [EXTRACTED] depends_on community 8 <-> 2 (strength 0.9): Extracted import edge crosses communities: progs/file/file.c imports progs/minios_png.h.
- [EXTRACTED] depends_on community 1 <-> 8 (strength 0.9): Extracted import edge crosses communities: tests/test_driver.c imports kernel/string.c.

## Risks

- [taint high] `mcp/mcp_dbg_driver.py` -> `progs/minios_abi.h` via `subprocess` (3 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `progs/minios_abi.h` via `subprocess` (3 hops)
- [taint high] `mcp/minios_addons.py` -> `progs/minios_abi.h` via `subprocess` (3 hops)
- [layer strict] `tests/test_freedomui.c` (testing) -> `progs/freedomui/freedomui_minios.c` (presentation)
- [dataflow DEAD_STORE] `progs/doomedit/doomedit.c:1556` `dmap_build_wad` `side`: `side` assigned at line 1556 but never read afterwards.
- [dataflow DEAD_STORE] `progs/doomedit/doomedit.c:1633` `dmap_build_wad` `dir`: `dir` assigned at line 1633 but never read afterwards.
- [dataflow DEAD_STORE] `progs/doomedit/doomedit.c:2145` `dmap_selftest` `mrgb`: `mrgb` assigned at line 2145 but never read afterwards.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/doomgeneric.c:8` `dg_Create` `DG_ScreenBuffer`: Result of allocator stored in `DG_ScreenBuffer` is never checked against NULL.
- [dataflow UNINIT_USE] `progs/doomgeneric/doomgeneric_minios.c:212` `DG_Init` `myargc`: `myargc` may be read before initialization (declared line 210).
- [dataflow UNINIT_USE] `progs/doomgeneric/doomgeneric_minios.c:212` `DG_Init` `myargv`: `myargv` may be read before initialization (declared line 211).
- [dataflow DEAD_STORE] `progs/doomgeneric/doomgeneric_minios.c:225` `DG_DrawFrame` `dst`: `dst` assigned at line 225 but never read afterwards.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/doomgeneric_soso.c:144` `DG_Init` `FrameBuffer`: Result of allocator stored in `FrameBuffer` is never checked against NULL.

## Open Questions

- Why do 11 file(s) lack file-level docs (e.g. `progs/doomgeneric/doomgeneric.c`)? What purpose do they serve?
- What would break if the most connected file in progs/src changed?
- Should progs/src be split, given cohesion 0.66?

## Sources

- `kernel/string.c`
- `progs/doomedit/doomedit.c`
- `progs/doomgeneric/doomgeneric.c`
- `progs/doomgeneric/doomgeneric.h`
- `progs/doomgeneric/doomgeneric_minios.c`
- `progs/doomgeneric/doomgeneric_soso.c`
- `progs/doomgeneric/doomgeneric_sosox.c`
- `progs/doomgeneric/doomgeneric_win.c`
- `progs/doomgeneric/doomgeneric_xlib.c`
- `progs/doomgeneric/memio.c`
- `progs/doomgeneric/memio.h`
- `progs/file/file.c`
- `progs/file/file_assoc.h`
- `progs/freedomui/freedomui_minios.c`
- `progs/lisp/lisp.c`
- `progs/lua/lua_main.c`
- `progs/lua/minios.c`
- `progs/micropython/variants/minios/lib/hello.py`
- `progs/micropython/variants/minios/minios_module.c`
- `progs/minicraft/minicraft.c`
- *... and 40 more*
