# progs/doomgeneric

*Community 8 | 175 files | cohesion 0.95*

## Definition

This community groups 175 file(s) rooted at `progs/doomgeneric` with dominant language h (cohesion 0.95). Central symbols: `AMSTR_FOLLOWOFF`, `AMSTR_FOLLOWON`, `AMSTR_GRIDOFF`, `AMSTR_GRIDON`, `AMSTR_MARKEDSPOT`, `AMSTR_MARKSCLEARED`, `AM_Drawer`, `AM_LevelInit`. Core file: `progs/doomgeneric/d_englsh.h` (286 symbols). Documented purpose: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the .

## Files

### `progs/doomgeneric` (174 files)

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
| `progs/doomgeneric/d_loop.h` | h | utility | 10 | yes |
| `progs/doomgeneric/d_main.c` | c | utility | 29 | yes |
| `progs/doomgeneric/d_main.h` | h | utility | 8 | yes |
| `progs/doomgeneric/d_mode.c` | c | utility | 6 | yes |
| `progs/doomgeneric/d_mode.h` | h | utility | 3 | yes |
| `progs/doomgeneric/d_net.c` | c | utility | 8 | yes |
| `progs/doomgeneric/d_player.h` | h | utility | 5 | yes |
| `progs/doomgeneric/d_textur.h` | h | utility | 2 | yes |

### `progs/pokemon/minios_stubs` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/pokemon/minios_stubs/SDL.h` | h | testing | 10 | yes |

*... and 155 more files in this community.*


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

- Internal resolved imports (EXTRACTED): 754
- Cross-boundary resolved imports (EXTRACTED): 38

## Connections

- [EXTRACTED] depends_on community 8 <-> 3 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/d_iwad.c imports kernel/string.c.

## Risks

- [cycle] `progs/doomgeneric/r_data.h` -> `progs/doomgeneric/r_state.h` -> `progs/doomgeneric/r_data.h`
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/d_iwad.c:217` `GetRegistryString` `result`: Result of allocator stored in `result` is never checked against NULL.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/d_iwad.c:346` `CheckSteamGUSPatches` `patch_path`: Result of allocator stored in `patch_path` is never checked against NULL.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/d_iwad.c:425` `CheckDirectoryHasIWAD` `filename`: Result of allocator stored in `filename` is never checked against NULL.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/d_iwad.c:764` `D_FindAllIWADs` `result`: Result of allocator stored in `result` is never checked against NULL.
- [dataflow DEAD_STORE] `progs/doomgeneric/g_game.c:1082` `G_PlayerReborn` `killcount`: `killcount` assigned at line 1082 but never read afterwards.
- [dataflow DEAD_STORE] `progs/doomgeneric/g_game.c:1083` `G_PlayerReborn` `itemcount`: `itemcount` assigned at line 1083 but never read afterwards.
- [dataflow DEAD_STORE] `progs/doomgeneric/g_game.c:1084` `G_PlayerReborn` `secretcount`: `secretcount` assigned at line 1084 but never read afterwards.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/i_system.c:77` `I_AtExit` `entry`: Result of allocator stored in `entry` is never checked against NULL.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/i_system.c:286` `EscapeShellString` `result`: Result of allocator stored in `result` is never checked against NULL.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/i_system.c:338` `ZenityErrorBox` `errorboxpath`: Result of allocator stored in `errorboxpath` is never checked against NULL.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/m_argv.c:109` `LoadResponseFile` `file`: Result of allocator stored in `file` is never checked against NULL.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/m_argv.c:129` `LoadResponseFile` `newargv`: Result of allocator stored in `newargv` is never checked against NULL.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/m_config.c:2045` `GetDefaultConfigDir` `result`: Result of allocator stored in `result` is never checked against NULL.

## Open Questions

- Why do 4 file(s) lack file-level docs (e.g. `progs/doomgeneric/dummy.c`)? What purpose do they serve?
- Can the cycle `progs/doomgeneric/r_data.h` -> `progs/doomgeneric/r_state.h` be broken with an interface?
- What would break if the most connected file in progs/doomgeneric changed?
- Should progs/doomgeneric be split, given cohesion 0.95?

## Sources

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
- `progs/doomgeneric/d_think.h`
- *... and 155 more*
