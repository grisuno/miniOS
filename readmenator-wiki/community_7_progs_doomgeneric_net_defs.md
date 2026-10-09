# progs/doomgeneric: net_defs

*Community 7 | 13 files | cohesion 0.42*

## Definition

This community groups 13 file(s) rooted at `progs/doomgeneric` with dominant language h (cohesion 0.42). Central symbols: `BACKUPTICS`, `BlockUntilStart`, `BuildNewTic`, `D_Disconnected`, `D_InitNetGame`, `D_QuitNetGame`, `D_ReceiveTic`, `D_RegisterLoopCallbacks`. Core file: `progs/doomgeneric/net_defs.h` (28 symbols). Documented purpose: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the .

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/doomgeneric/d_loop.c` | c | utility | 18 | yes |
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
- `__D_TICCMD__` (macro, `progs/doomgeneric/d_ticcmd.h:22`) `#define __D_TICCMD__`
- `ticcmd_t` (struct, `progs/doomgeneric/d_ticcmd.h:32`)
- `NET_CLIENT_H` (macro, `progs/doomgeneric/net_client.h:18`) `#define NET_CLIENT_H`
- `NET_CL_Disconnect` (function, `progs/doomgeneric/net_client.h:26`) `void NET_CL_Disconnect(void);`
- `NET_CL_Run` (function, `progs/doomgeneric/net_client.h:27`) `void NET_CL_Run(void);`
- `NET_CL_Init` (function, `progs/doomgeneric/net_client.h:28`) `void NET_CL_Init(void);`
- `NET_CL_LaunchGame` (function, `progs/doomgeneric/net_client.h:29`) `void NET_CL_LaunchGame(void);`
- `NET_CL_StartGame` (function, `progs/doomgeneric/net_client.h:30`) `void NET_CL_StartGame(net_gamesettings_t *settings);`
- `NET_CL_SendTiccmd` (function, `progs/doomgeneric/net_client.h:31`) `void NET_CL_SendTiccmd(ticcmd_t *ticcmd, int maketic);`
- `NET_Init` (function, `progs/doomgeneric/net_client.h:33`) `void NET_Init(void);`
- `NET_BindVariables` (function, `progs/doomgeneric/net_client.h:35`) `void NET_BindVariables(void);`
- `net_client_connected` (variable, `progs/doomgeneric/net_client.h:37`) `extern boolean net_client_connected;`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 19
- Cross-boundary resolved imports (EXTRACTED): 26

## Connections

- [EXTRACTED] depends_on community 7 <-> 3 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/d_loop.c imports kernel/string.c.
- [EXTRACTED] depends_on community 7 <-> 1 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/d_loop.c imports progs/doomgeneric/doomfeatures.h.
- [EXTRACTED] depends_on community 7 <-> 2 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/d_loop.c imports progs/doomgeneric/d_loop.h.
- [INFERRED] shares_context community 0 <-> 7 (strength 0.5): Inferred shared context (layer utility) with no import path between community 0 (headers: kernel) and community 7 (progs/doomgeneric: net_defs).

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- What would break if the most connected file in progs/doomgeneric: net_defs changed?
- Should progs/doomgeneric: net_defs be split, given cohesion 0.42?

## Sources

- `progs/doomgeneric/d_loop.c`
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
