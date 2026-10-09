# progs/doomgeneric: p_spec

*Community 2 | 69 files | cohesion 0.56*

## Definition

This community groups 69 file(s) rooted at `progs/doomgeneric` with dominant language c (cohesion 0.56). Central symbols: `ANG1`, `ANG180`, `ANG1_X`, `ANG270`, `ANG45`, `ANG5`, `ANG60`, `ANG90`. Core file: `progs/doomgeneric/p_spec.h` (94 symbols). Documented purpose: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the .

## Files

### `progs/doomgeneric` (68 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/doomgeneric/d_items.c` | c | utility | 0 | yes |
| `progs/doomgeneric/d_items.h` | h | utility | 3 | yes |
| `progs/doomgeneric/d_loop.h` | h | utility | 10 | yes |
| `progs/doomgeneric/d_mode.c` | c | utility | 6 | yes |
| `progs/doomgeneric/d_mode.h` | h | utility | 3 | yes |
| `progs/doomgeneric/d_player.h` | h | utility | 5 | yes |
| `progs/doomgeneric/d_think.h` | h | utility | 4 | yes |
| `progs/doomgeneric/deh_misc.h` | h | utility | 49 | yes |
| `progs/doomgeneric/doomdata.h` | h | utility | 11 | yes |
| `progs/doomgeneric/doomdef.c` | c | utility | 0 | yes |
| `progs/doomgeneric/doomdef.h` | h | utility | 9 | yes |
| `progs/doomgeneric/doomstat.c` | c | utility | 0 | yes |
| `progs/doomgeneric/doomstat.h` | h | utility | 68 | yes |
| `progs/doomgeneric/hu_lib.c` | c | utility | 22 | yes |
| `progs/doomgeneric/hu_lib.h` | h | utility | 24 | yes |
| `progs/doomgeneric/info.c` | c | utility | 74 | yes |
| `progs/doomgeneric/info.h` | h | utility | 6 | yes |
| `progs/doomgeneric/m_bbox.c` | c | utility | 2 | yes |
| `progs/doomgeneric/m_bbox.h` | h | utility | 3 | yes |

### `progs/quake2generic` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/quake2generic/q2generic_minios.c` | c | utility | 34 | yes |

*... and 49 more files in this community.*


## Key Symbols

- `__D_ITEMS__` (macro, `progs/doomgeneric/d_items.h:21`) `#define __D_ITEMS__`
- `weaponinfo_t` (struct, `progs/doomgeneric/d_items.h:28`) - Weapon info: sprite frames, ammunition use.
- `weaponinfo` (variable, `progs/doomgeneric/d_items.h:39`) `extern weaponinfo_t weaponinfo[NUMWEAPONS];`
- `__D_LOOP__` (macro, `progs/doomgeneric/d_loop.h:20`) `#define __D_LOOP__`
- `loop_interface_t` (struct, `progs/doomgeneric/d_loop.h:31`)
- `D_RegisterLoopCallbacks` (function, `progs/doomgeneric/d_loop.h:52`) `void D_RegisterLoopCallbacks(loop_interface_t *i);` - Register callback functions for the main loop code to use.
- `NetUpdate` (function, `progs/doomgeneric/d_loop.h:55`) `void NetUpdate (void);` - Create any new ticcmds and broadcast to other players.
- `D_QuitNetGame` (function, `progs/doomgeneric/d_loop.h:59`) `void D_QuitNetGame (void);` - Broadcasts special packets to other players to notify of game exit
- `TryRunTics` (function, `progs/doomgeneric/d_loop.h:62`) `void TryRunTics (void);` - ? how many ticks to run?
- `D_StartGameLoop` (function, `progs/doomgeneric/d_loop.h:65`) `void D_StartGameLoop(void);` - Called at start of game loop to initialize timers
- `D_StartNetGame` (function, `progs/doomgeneric/d_loop.h:74`) `void D_StartNetGame(net_gamesettings_t *settings, netgame_startup_callback_t cal`
- `singletics` (variable, `progs/doomgeneric/d_loop.h:77`) `extern boolean singletics;`
- `ticdup` (variable, `progs/doomgeneric/d_loop.h:78`) `extern int gametic, ticdup;`
- `D_ValidGameMode` (function, `progs/doomgeneric/d_mode.c:50`) `boolean D_ValidGameMode(GameMission_t mission, GameMode_t mode)`
- `D_ValidEpisodeMap` (function, `progs/doomgeneric/d_mode.c:65`) `boolean D_ValidEpisodeMap(GameMission_t mission, GameMode_t mode,`
- `D_GetNumEpisodes` (function, `progs/doomgeneric/d_mode.c:103`) `int D_GetNumEpisodes(GameMission_t mission, GameMode_t mode)`
- `D_ValidGameVersion` (function, `progs/doomgeneric/d_mode.c:135`) `boolean D_ValidGameVersion(GameMission_t mission, GameVersion_t version)`
- `D_IsEpisodeMap` (function, `progs/doomgeneric/d_mode.c:161`) `boolean D_IsEpisodeMap(GameMission_t mission)`
- `D_GameMissionString` (function, `progs/doomgeneric/d_mode.c:182`) `char *D_GameMissionString(GameMission_t mission)`
- `__D_MODE__` (macro, `progs/doomgeneric/d_mode.h:21`) `#define __D_MODE__`
- `D_GetNumEpisodes` (function, `progs/doomgeneric/d_mode.h:93`) `int D_GetNumEpisodes(GameMission_t mission, GameMode_t mode);`
- `D_GameMissionString` (function, `progs/doomgeneric/d_mode.h:95`) `char *D_GameMissionString(GameMission_t mission);`
- `__D_PLAYER__` (macro, `progs/doomgeneric/d_player.h:21`) `#define __D_PLAYER__`
- `player_s` (struct, `progs/doomgeneric/d_player.h:78`) - Extended player object info: player_t
- `mo` (type_alias, `progs/doomgeneric/d_player.h:78`) `typedef struct player_s { mobj_t* mo;` - Extended player object info: player_t
- `wbplayerstruct_t` (struct, `progs/doomgeneric/d_player.h:168`) - INTERMISSION Structure passed e.g. to WI_Start(wb)
- `wbstartstruct_t` (struct, `progs/doomgeneric/d_player.h:182`)
- `__D_THINK__` (macro, `progs/doomgeneric/d_think.h:23`) `#define __D_THINK__`
- `think_t` (type_alias, `progs/doomgeneric/d_think.h:54`) `typedef actionf_t think_t;` - Historically, "think_t" is yet another function pointer to a routine to handle an actor.
- `thinker_s` (struct, `progs/doomgeneric/d_think.h:58`) - Doubly linked list of actors.

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 200
- Cross-boundary resolved imports (EXTRACTED): 158

## Connections

- [EXTRACTED] depends_on community 1 <-> 2 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/am_map.c imports progs/doomgeneric/doomdef.h.
- [EXTRACTED] depends_on community 7 <-> 2 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/d_loop.c imports progs/doomgeneric/d_loop.h.
- [EXTRACTED] depends_on community 2 <-> 3 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/doomdef.h imports kernel/string.c.
- [INFERRED] shares_context community 2 <-> 4 (strength 0.5): Inferred shared context (layer utility) with no import path between community 2 (progs/doomgeneric: p_spec) and community 4 (tools: lxabi).
- [INFERRED] shares_context community 2 <-> 5 (strength 0.5): Inferred shared context (layer utility) with no import path between community 2 (progs/doomgeneric: p_spec) and community 5 (headers: vga_fb).

## Risks

- [cycle] `progs/doomgeneric/r_data.h` -> `progs/doomgeneric/r_state.h` -> `progs/doomgeneric/r_data.h`

## Open Questions

- Why do 1 file(s) lack file-level docs (e.g. `progs/doomgeneric/statdump.c`)? What purpose do they serve?
- Can the cycle `progs/doomgeneric/r_data.h` -> `progs/doomgeneric/r_state.h` be broken with an interface?
- What would break if the most connected file in progs/doomgeneric: p_spec changed?
- Should progs/doomgeneric: p_spec be split, given cohesion 0.56?

## Sources

- `progs/doomgeneric/d_items.c`
- `progs/doomgeneric/d_items.h`
- `progs/doomgeneric/d_loop.h`
- `progs/doomgeneric/d_mode.c`
- `progs/doomgeneric/d_mode.h`
- `progs/doomgeneric/d_player.h`
- `progs/doomgeneric/d_think.h`
- `progs/doomgeneric/deh_misc.h`
- `progs/doomgeneric/doomdata.h`
- `progs/doomgeneric/doomdef.c`
- `progs/doomgeneric/doomdef.h`
- `progs/doomgeneric/doomstat.c`
- `progs/doomgeneric/doomstat.h`
- `progs/doomgeneric/hu_lib.c`
- `progs/doomgeneric/hu_lib.h`
- `progs/doomgeneric/info.c`
- `progs/doomgeneric/info.h`
- `progs/doomgeneric/m_bbox.c`
- `progs/doomgeneric/m_bbox.h`
- `progs/doomgeneric/m_fixed.h`
- *... and 49 more*
