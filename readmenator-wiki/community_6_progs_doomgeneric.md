# progs/doomgeneric

*Community 6 | 192 files | cohesion 0.95*

## Definition

This community groups 192 file(s) rooted at `progs/doomgeneric` with dominant language c (cohesion 0.95). Central symbols: `AMSTR_FOLLOWOFF`, `AMSTR_FOLLOWON`, `AMSTR_GRIDOFF`, `AMSTR_GRIDON`, `AMSTR_MARKEDSPOT`, `AMSTR_MARKSCLEARED`, `AM_Drawer`, `AM_LevelInit`. Core file: `progs/doomgeneric/d_englsh.h` (286 symbols). Documented purpose: Kernel string and memory functions..

## Files

### `progs/doomgeneric` (183 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/doomgeneric/am_map.c` | c | utility | 87 | yes |
| `progs/doomgeneric/am_map.h` | h | utility | 8 | yes |
| `progs/doomgeneric/config.h` | h | infrastructure | 16 | yes |
| `progs/doomgeneric/d_englsh.h` | h | utility | 286 | yes |
| `progs/doomgeneric/d_event.c` | c | infrastructure | 3 | yes |
| `progs/doomgeneric/d_event.h` | h | infrastructure | 4 | yes |
| `progs/doomgeneric/d_items.c` | c | utility | 0 | yes |
| `progs/doomgeneric/d_items.h` | h | utility | 3 | yes |
| `progs/doomgeneric/d_iwad.c` | c | utility | 27 | yes |
| `progs/doomgeneric/d_iwad.h` | h | utility | 14 | yes |
| `progs/doomgeneric/d_loop.c` | c | utility | 18 | yes |

### `tests` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_paint.c` | c | testing | 21 | yes |
| `tests/test_vedit_build.c` | c | testing | 16 | yes |

### `kernel` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/string.c` | c | utility | 13 | yes |

### `progs/lua` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/lua/lua_main.c` | c | utility | 7 | no |

### `progs/pokemon/minios_stubs` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/pokemon/minios_stubs/SDL.h` | h | testing | 10 | yes |

### `progs/quake2generic` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/quake2generic/q2generic_minios.c` | c | utility | 32 | yes |

### `progs/src` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/src/freedom.c` | c | utility | 61 | yes |

### `progs/tls_u` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/tls_u/tls_u_port.c` | c | utility | 15 | yes |

### `progs/topogpt3` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/topogpt3/topogpt3.c` | c | utility | 128 | no |

*... and 172 more files in this community.*


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
- `REDS` (macro, `progs/doomgeneric/am_map.c:50`) `#define REDS`
- `REDRANGE` (macro, `progs/doomgeneric/am_map.c:51`) `#define REDRANGE`
- `BLUES` (macro, `progs/doomgeneric/am_map.c:52`) `#define BLUES`
- `BLUERANGE` (macro, `progs/doomgeneric/am_map.c:53`) `#define BLUERANGE`
- `GREENS` (macro, `progs/doomgeneric/am_map.c:54`) `#define GREENS`
- `GREENRANGE` (macro, `progs/doomgeneric/am_map.c:55`) `#define GREENRANGE`
- `GRAYS` (macro, `progs/doomgeneric/am_map.c:56`) `#define GRAYS`
- `GRAYSRANGE` (macro, `progs/doomgeneric/am_map.c:57`) `#define GRAYSRANGE`
- `BROWNS` (macro, `progs/doomgeneric/am_map.c:58`) `#define BROWNS`
- `BROWNRANGE` (macro, `progs/doomgeneric/am_map.c:59`) `#define BROWNRANGE`
- `YELLOWS` (macro, `progs/doomgeneric/am_map.c:60`) `#define YELLOWS`
- `YELLOWRANGE` (macro, `progs/doomgeneric/am_map.c:61`) `#define YELLOWRANGE`
- `BLACK` (macro, `progs/doomgeneric/am_map.c:62`) `#define BLACK`
- `WHITE` (macro, `progs/doomgeneric/am_map.c:63`) `#define WHITE`
- `BACKGROUND` (macro, `progs/doomgeneric/am_map.c:66`) `#define BACKGROUND`
- `YOURCOLORS` (macro, `progs/doomgeneric/am_map.c:67`) `#define YOURCOLORS`
- `YOURRANGE` (macro, `progs/doomgeneric/am_map.c:68`) `#define YOURRANGE`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 810
- Cross-boundary resolved imports (EXTRACTED): 41

## Connections

- [EXTRACTED] depends_on community 5 <-> 6 (strength 0.9): Extracted import edge crosses communities: headers/tls_port.h imports kernel/string.c.
- [EXTRACTED] depends_on community 6 <-> 0 (strength 0.9): Extracted import edge crosses communities: kernel/string.c imports headers/kernel.h.
- [EXTRACTED] depends_on community 8 <-> 6 (strength 0.9): Extracted import edge crosses communities: progs/doomedit/doomedit.c imports kernel/string.c.
- [EXTRACTED] depends_on community 6 <-> 7 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/doomgeneric_xlib.c imports kernel/time.c.
- [EXTRACTED] depends_on community 2 <-> 6 (strength 0.9): Extracted import edge crosses communities: progs/pokemon/platform_minios.c imports kernel/string.c.
- [INFERRED] shares_context community 1 <-> 6 (strength 0.5): Inferred shared context (language h) with no import path between community 1 (headers/drivers) and community 6 (progs/doomgeneric).

## Risks

- [cycle] `progs/doomgeneric/r_data.h` -> `progs/doomgeneric/r_state.h` -> `progs/doomgeneric/r_data.h`
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/d_iwad.c:217` `GetRegistryString` `result`: Result of allocator stored in `result` is never checked against NULL.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/d_iwad.c:346` `CheckSteamGUSPatches` `patch_path`: Result of allocator stored in `patch_path` is never checked against NULL.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/d_iwad.c:425` `CheckDirectoryHasIWAD` `filename`: Result of allocator stored in `filename` is never checked against NULL.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/d_iwad.c:764` `D_FindAllIWADs` `result`: Result of allocator stored in `result` is never checked against NULL.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/doomgeneric.c:8` `dg_Create` `DG_ScreenBuffer`: Result of allocator stored in `DG_ScreenBuffer` is never checked against NULL.
- [dataflow UNINIT_USE] `progs/doomgeneric/doomgeneric_minios.c:212` `DG_Init` `myargc`: `myargc` may be read before initialization (declared line 210).
- [dataflow UNINIT_USE] `progs/doomgeneric/doomgeneric_minios.c:212` `DG_Init` `myargv`: `myargv` may be read before initialization (declared line 211).
- [dataflow DEAD_STORE] `progs/doomgeneric/doomgeneric_minios.c:225` `DG_DrawFrame` `dst`: `dst` assigned at line 225 but never read afterwards.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/doomgeneric_soso.c:144` `DG_Init` `FrameBuffer`: Result of allocator stored in `FrameBuffer` is never checked against NULL.
- [dataflow DEAD_STORE] `progs/doomgeneric/g_game.c:1082` `G_PlayerReborn` `killcount`: `killcount` assigned at line 1082 but never read afterwards.
- [dataflow DEAD_STORE] `progs/doomgeneric/g_game.c:1083` `G_PlayerReborn` `itemcount`: `itemcount` assigned at line 1083 but never read afterwards.
- [dataflow DEAD_STORE] `progs/doomgeneric/g_game.c:1084` `G_PlayerReborn` `secretcount`: `secretcount` assigned at line 1084 but never read afterwards.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/i_system.c:77` `I_AtExit` `entry`: Result of allocator stored in `entry` is never checked against NULL.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/i_system.c:286` `EscapeShellString` `result`: Result of allocator stored in `result` is never checked against NULL.

## Open Questions

- Why do 10 file(s) lack file-level docs (e.g. `progs/doomgeneric/doomgeneric.c`)? What purpose do they serve?
- Can the cycle `progs/doomgeneric/r_data.h` -> `progs/doomgeneric/r_state.h` be broken with an interface?
- What would break if the most connected file in progs/doomgeneric changed?
- Should progs/doomgeneric be split, given cohesion 0.95?

## Sources

- `kernel/string.c`
- `progs/doomgeneric/am_map.c`
- `progs/doomgeneric/am_map.h`
- `progs/doomgeneric/config.h`
- `progs/doomgeneric/d_englsh.h`
- `progs/doomgeneric/d_event.c`
- `progs/doomgeneric/d_event.h`
- `progs/doomgeneric/d_items.c`
- `progs/doomgeneric/d_items.h`
- `progs/doomgeneric/d_iwad.c`
- `progs/doomgeneric/d_iwad.h`
- `progs/doomgeneric/d_loop.c`
- `progs/doomgeneric/d_loop.h`
- `progs/doomgeneric/d_main.c`
- `progs/doomgeneric/d_main.h`
- `progs/doomgeneric/d_mode.c`
- `progs/doomgeneric/d_mode.h`
- `progs/doomgeneric/d_net.c`
- `progs/doomgeneric/d_player.h`
- `progs/doomgeneric/d_textur.h`
- *... and 172 more*
