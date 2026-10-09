# progs/doomgeneric: d_englsh

*Community 1 | 99 files | cohesion 0.66*

## Definition

This community groups 99 file(s) rooted at `progs/doomgeneric` with dominant language h (cohesion 0.66). Central symbols: `AMSTR_FOLLOWOFF`, `AMSTR_FOLLOWON`, `AMSTR_GRIDOFF`, `AMSTR_GRIDON`, `AMSTR_MARKEDSPOT`, `AMSTR_MARKSCLEARED`, `AM_Drawer`, `AM_LevelInit`. Core file: `progs/doomgeneric/d_englsh.h` (286 symbols). Documented purpose: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the .

## Files

### `progs/doomgeneric` (98 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/doomgeneric/am_map.c` | c | utility | 87 | yes |
| `progs/doomgeneric/am_map.h` | h | utility | 8 | yes |
| `progs/doomgeneric/config.h` | h | infrastructure | 16 | yes |
| `progs/doomgeneric/d_englsh.h` | h | utility | 286 | yes |
| `progs/doomgeneric/d_event.c` | c | infrastructure | 3 | yes |
| `progs/doomgeneric/d_event.h` | h | infrastructure | 4 | yes |
| `progs/doomgeneric/d_iwad.c` | c | utility | 27 | yes |
| `progs/doomgeneric/d_iwad.h` | h | utility | 14 | yes |
| `progs/doomgeneric/d_main.c` | c | utility | 29 | yes |
| `progs/doomgeneric/d_main.h` | h | utility | 8 | yes |
| `progs/doomgeneric/d_net.c` | c | utility | 8 | yes |
| `progs/doomgeneric/d_textur.h` | h | utility | 2 | yes |
| `progs/doomgeneric/deh_main.h` | h | utility | 12 | yes |
| `progs/doomgeneric/deh_str.h` | h | utility | 11 | yes |
| `progs/doomgeneric/doomfeatures.h` | h | utility | 2 | yes |
| `progs/doomgeneric/doomgeneric.c` | c | utility | 1 | no |
| `progs/doomgeneric/doomgeneric.h` | h | utility | 10 | no |
| `progs/doomgeneric/doomgeneric_sdl.c` | c | utility | 10 | yes |
| `progs/doomgeneric/doomgeneric_soso.c` | c | utility | 13 | yes |

### `progs/pokemon/minios_stubs` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/pokemon/minios_stubs/SDL.h` | h | testing | 10 | yes |

*... and 79 more files in this community.*


## Key Symbols

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
- `WALLCOLORS` (macro, `progs/doomgeneric/am_map.c:69`) `#define WALLCOLORS`
- `WALLRANGE` (macro, `progs/doomgeneric/am_map.c:70`) `#define WALLRANGE`
- `TSWALLCOLORS` (macro, `progs/doomgeneric/am_map.c:71`) `#define TSWALLCOLORS`
- `TSWALLRANGE` (macro, `progs/doomgeneric/am_map.c:72`) `#define TSWALLRANGE`
- `FDWALLCOLORS` (macro, `progs/doomgeneric/am_map.c:73`) `#define FDWALLCOLORS`
- `FDWALLRANGE` (macro, `progs/doomgeneric/am_map.c:74`) `#define FDWALLRANGE`
- `CDWALLCOLORS` (macro, `progs/doomgeneric/am_map.c:75`) `#define CDWALLCOLORS`
- `CDWALLRANGE` (macro, `progs/doomgeneric/am_map.c:76`) `#define CDWALLRANGE`
- `THINGCOLORS` (macro, `progs/doomgeneric/am_map.c:77`) `#define THINGCOLORS`
- `THINGRANGE` (macro, `progs/doomgeneric/am_map.c:78`) `#define THINGRANGE`
- `SECRETWALLCOLORS` (macro, `progs/doomgeneric/am_map.c:79`) `#define SECRETWALLCOLORS`
- `SECRETWALLRANGE` (macro, `progs/doomgeneric/am_map.c:80`) `#define SECRETWALLRANGE`
- `GRIDCOLORS` (macro, `progs/doomgeneric/am_map.c:81`) `#define GRIDCOLORS`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 379
- Cross-boundary resolved imports (EXTRACTED): 191

## Connections

- [EXTRACTED] depends_on community 1 <-> 2 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/am_map.c imports progs/doomgeneric/doomdef.h.
- [EXTRACTED] depends_on community 1 <-> 3 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/d_iwad.c imports kernel/string.c.
- [EXTRACTED] depends_on community 7 <-> 1 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/d_loop.c imports progs/doomgeneric/doomfeatures.h.
- [EXTRACTED] depends_on community 4 <-> 1 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/doomgeneric_xlib.c imports progs/doomgeneric/doomkeys.h.
- [INFERRED] shares_context community 1 <-> 5 (strength 0.5): Inferred shared context (language h and layer utility) with no import path between community 1 (progs/doomgeneric: d_englsh) and community 5 (headers: vga_fb).
- [INFERRED] shares_context community 1 <-> 6 (strength 0.5): Inferred shared context (layer utility) with no import path between community 1 (progs/doomgeneric: d_englsh) and community 6 (headers: net).
- [INFERRED] shares_context community 1 <-> 9 (strength 0.5): Inferred shared context (layer utility) with no import path between community 1 (progs/doomgeneric: d_englsh) and community 9 (orphans).

## Risks

- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/d_iwad.c:217` `GetRegistryString` `result`: Result of allocator stored in `result` is never checked against NULL.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/d_iwad.c:346` `CheckSteamGUSPatches` `patch_path`: Result of allocator stored in `patch_path` is never checked against NULL.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/d_iwad.c:425` `CheckDirectoryHasIWAD` `filename`: Result of allocator stored in `filename` is never checked against NULL.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/d_iwad.c:764` `D_FindAllIWADs` `result`: Result of allocator stored in `result` is never checked against NULL.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/doomgeneric.c:8` `dg_Create` `DG_ScreenBuffer`: Result of allocator stored in `DG_ScreenBuffer` is never checked against NULL.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/doomgeneric_soso.c:144` `DG_Init` `FrameBuffer`: Result of allocator stored in `FrameBuffer` is never checked against NULL.
- [dataflow DEAD_STORE] `progs/doomgeneric/g_game.c:1082` `G_PlayerReborn` `killcount`: `killcount` assigned at line 1082 but never read afterwards.
- [dataflow DEAD_STORE] `progs/doomgeneric/g_game.c:1083` `G_PlayerReborn` `itemcount`: `itemcount` assigned at line 1083 but never read afterwards.

## Open Questions

- Why do 6 file(s) lack file-level docs (e.g. `progs/doomgeneric/doomgeneric.c`)? What purpose do they serve?
- What would break if the most connected file in progs/doomgeneric: d_englsh changed?
- Should progs/doomgeneric: d_englsh be split, given cohesion 0.66?

## Sources

- `progs/doomgeneric/am_map.c`
- `progs/doomgeneric/am_map.h`
- `progs/doomgeneric/config.h`
- `progs/doomgeneric/d_englsh.h`
- `progs/doomgeneric/d_event.c`
- `progs/doomgeneric/d_event.h`
- `progs/doomgeneric/d_iwad.c`
- `progs/doomgeneric/d_iwad.h`
- `progs/doomgeneric/d_main.c`
- `progs/doomgeneric/d_main.h`
- `progs/doomgeneric/d_net.c`
- `progs/doomgeneric/d_textur.h`
- `progs/doomgeneric/deh_main.h`
- `progs/doomgeneric/deh_str.h`
- `progs/doomgeneric/doomfeatures.h`
- `progs/doomgeneric/doomgeneric.c`
- `progs/doomgeneric/doomgeneric.h`
- `progs/doomgeneric/doomgeneric_sdl.c`
- `progs/doomgeneric/doomgeneric_soso.c`
- `progs/doomgeneric/doomgeneric_sosox.c`
- *... and 79 more*
