# progs/doomgeneric: net_defs

*Community 5 | 19 files | cohesion 0.40*

## Definition

This community groups 19 file(s) rooted at `progs/doomgeneric` with dominant language h (cohesion 0.40). Central symbols: `BACKUPTICS`, `BlockUntilStart`, `BuildNewTic`, `DOOM_STATDUMP_H`, `D_Disconnected`, `D_GameMissionString`, `D_GetNumEpisodes`, `D_InitNetGame`. Core file: `progs/doomgeneric/net_defs.h` (28 symbols). Documented purpose: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the .

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/doomgeneric/d_loop.c` | c | utility | 18 | yes |
| `progs/doomgeneric/d_loop.h` | h | utility | 10 | yes |
| `progs/doomgeneric/d_mode.c` | c | utility | 6 | yes |
| `progs/doomgeneric/d_mode.h` | h | utility | 3 | yes |
| `progs/doomgeneric/d_player.h` | h | utility | 5 | yes |
| `progs/doomgeneric/d_ticcmd.h` | h | utility | 2 | yes |
| `progs/doomgeneric/net_client.h` | h | infrastructure | 21 | yes |
| `progs/doomgeneric/net_defs.h` | h | utility | 28 | yes |
| `progs/doomgeneric/net_gui.h` | h | utility | 2 | yes |
| `progs/doomgeneric/net_io.h` | h | utility | 9 | yes |
| `progs/doomgeneric/net_loop.h` | h | utility | 3 | yes |
| `progs/doomgeneric/net_packet.h` | h | utility | 9 | yes |
| `progs/doomgeneric/net_query.h` | h | data_access | 12 | yes |
| `progs/doomgeneric/net_sdl.h` | h | utility | 2 | yes |
| `progs/doomgeneric/net_server.h` | h | utility | 6 | yes |
| `progs/doomgeneric/sha1.c` | c | utility | 19 | yes |
| `progs/doomgeneric/sha1.h` | h | utility | 9 | yes |
| `progs/doomgeneric/statdump.c` | c | utility | 11 | no |
| `progs/doomgeneric/statdump.h` | h | utility | 3 | no |

## Key Symbols

- `ticcmd_set_t` (struct, `progs/doomgeneric/d_loop.c:45`)
- `GetAdjustedTime` (function, `progs/doomgeneric/d_loop.c:119`) `static int GetAdjustedTime(void)`
- `BuildNewTic` (function, `progs/doomgeneric/d_loop.c:136`) `static boolean BuildNewTic(void)`
- `NetUpdate` (function, `progs/doomgeneric/d_loop.c:203`) `void NetUpdate (void)`
- `D_Disconnected` (function, `progs/doomgeneric/d_loop.c:252`) `static void D_Disconnected(void)`
- `D_ReceiveTic` (function, `progs/doomgeneric/d_loop.c:271`) `void D_ReceiveTic(ticcmd_t *ticcmds, boolean *players_mask)`
- `D_StartGameLoop` (function, `progs/doomgeneric/d_loop.c:305`) `void D_StartGameLoop(void)`
- `BlockUntilStart` (function, `progs/doomgeneric/d_loop.c:315`) `static void BlockUntilStart(net_gamesettings_t *settings,`
- `D_StartNetGame` (function, `progs/doomgeneric/d_loop.c:340`) `void D_StartNetGame(net_gamesettings_t *settings,                     netgame_st`
- `D_InitNetGame` (function, `progs/doomgeneric/d_loop.c:452`) `boolean D_InitNetGame(net_connect_data_t *connect_data)`
- `D_QuitNetGame` (function, `progs/doomgeneric/d_loop.c:560`) `void D_QuitNetGame (void)` - D_QuitNetGame Called before quitting to leave a net game without hanging the other players
- `GetLowTic` (function, `progs/doomgeneric/d_loop.c:568`) `static int GetLowTic(void)`
- `OldNetSync` (function, `progs/doomgeneric/d_loop.c:591`) `static void OldNetSync(void)`
- `PlayersInGame` (function, `progs/doomgeneric/d_loop.c:642`) `static boolean PlayersInGame(void)`
- `TicdupSquash` (function, `progs/doomgeneric/d_loop.c:672`) `static void TicdupSquash(ticcmd_set_t *set)`
- `SinglePlayerClear` (function, `progs/doomgeneric/d_loop.c:689`) `static void SinglePlayerClear(ticcmd_set_t *set)`
- `TryRunTics` (function, `progs/doomgeneric/d_loop.c:706`) `void TryRunTics (void)`
- `D_RegisterLoopCallbacks` (function, `progs/doomgeneric/d_loop.c:822`) `void D_RegisterLoopCallbacks(loop_interface_t *i)`
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

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 27
- Cross-boundary resolved imports (EXTRACTED): 41

## Connections

- [EXTRACTED] depends_on community 1 <-> 5 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/d_iwad.h imports progs/doomgeneric/d_mode.h.
- [EXTRACTED] depends_on community 5 <-> 2 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/d_loop.c imports kernel/string.c.
- [EXTRACTED] depends_on community 5 <-> 3 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/d_loop.c imports progs/doomgeneric/m_fixed.h.

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 2 file(s) lack file-level docs (e.g. `progs/doomgeneric/statdump.c`)? What purpose do they serve?
- What would break if the most connected file in progs/doomgeneric: net_defs changed?
- Should progs/doomgeneric: net_defs be split, given cohesion 0.40?

## Sources

- `progs/doomgeneric/d_loop.c`
- `progs/doomgeneric/d_loop.h`
- `progs/doomgeneric/d_mode.c`
- `progs/doomgeneric/d_mode.h`
- `progs/doomgeneric/d_player.h`
- `progs/doomgeneric/d_ticcmd.h`
- `progs/doomgeneric/net_client.h`
- `progs/doomgeneric/net_defs.h`
- `progs/doomgeneric/net_gui.h`
- `progs/doomgeneric/net_io.h`
- `progs/doomgeneric/net_loop.h`
- `progs/doomgeneric/net_packet.h`
- `progs/doomgeneric/net_query.h`
- `progs/doomgeneric/net_sdl.h`
- `progs/doomgeneric/net_server.h`
- `progs/doomgeneric/sha1.c`
- `progs/doomgeneric/sha1.h`
- `progs/doomgeneric/statdump.c`
- `progs/doomgeneric/statdump.h`
