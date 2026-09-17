# progs/doomgeneric

*Community 12 | 10 files | cohesion 0.39*

## Definition

This community groups 10 file(s) rooted at `progs/doomgeneric` with dominant language h (cohesion 0.39). Central symbols: `BACKUPTICS`, `BlockUntilStart`, `BuildNewTic`, `D_Disconnected`, `D_InitNetGame`, `D_QuitNetGame`, `D_ReceiveTic`, `D_RegisterLoopCallbacks`. Core file: `progs/doomgeneric/d_loop.c` (36 symbols). Documented purpose: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License a.

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/doomgeneric/d_loop.c` | c | utility | 36 | yes |
| `progs/doomgeneric/d_ticcmd.h` | h | utility | 2 | yes |
| `progs/doomgeneric/net_client.h` | h | infrastructure | 23 | yes |
| `progs/doomgeneric/net_defs.h` | h | utility | 30 | yes |
| `progs/doomgeneric/net_io.h` | h | utility | 10 | yes |
| `progs/doomgeneric/net_loop.h` | h | utility | 3 | yes |
| `progs/doomgeneric/net_packet.h` | h | utility | 15 | yes |
| `progs/doomgeneric/net_query.h` | h | data_access | 13 | yes |
| `progs/doomgeneric/net_sdl.h` | h | utility | 2 | yes |
| `progs/doomgeneric/net_server.h` | h | utility | 6 | yes |

## Key Symbols

- `ticcmd_set_t` (struct, `progs/doomgeneric/d_loop.c:45`)
- `GetAdjustedTime` (function, `progs/doomgeneric/d_loop.c:118`) `static int GetAdjustedTime(void)` - 35 fps clock adjusted by offsetms milliseconds
- `BuildNewTic` (function, `progs/doomgeneric/d_loop.c:135`) `static boolean BuildNewTic(void)`
- `I_StartTic` (function, `progs/doomgeneric/d_loop.c:142`) `I_StartTic ();`
- `memset` (function, `progs/doomgeneric/d_loop.c:177`) `memset(&cmd, 0, sizeof(ticcmd_t));` - printf ("mk:%i ",maketic);
- `NET_CL_SendTiccmd` (function, `progs/doomgeneric/d_loop.c:184`) `NET_CL_SendTiccmd(&cmd, maketic);`
- `NetUpdate` (function, `progs/doomgeneric/d_loop.c:202`) `void NetUpdate (void)`
- `NET_CL_Run` (function, `progs/doomgeneric/d_loop.c:218`) `NET_CL_Run();` - Run network subsystems
- `NET_SV_Run` (function, `progs/doomgeneric/d_loop.c:220`) `NET_SV_Run();`
- `D_Disconnected` (function, `progs/doomgeneric/d_loop.c:251`) `static void D_Disconnected(void)`
- `I_Error` (function, `progs/doomgeneric/d_loop.c:258`) `I_Error("Disconnected from server in drone mode.");`
- `printf` (function, `progs/doomgeneric/d_loop.c:262`) `printf("Disconnected from server.\n");` - disconnected from server
- `D_ReceiveTic` (function, `progs/doomgeneric/d_loop.c:270`) `void D_ReceiveTic(ticcmd_t *ticcmds, boolean *players_mask)` - Invoked by the network engine when a complete set of ticcmds is available.
- `D_StartGameLoop` (function, `progs/doomgeneric/d_loop.c:304`) `void D_StartGameLoop(void)` - Start game loop  Called after the screen is set but before the game starts running.
- `BlockUntilStart` (function, `progs/doomgeneric/d_loop.c:314`) `static void BlockUntilStart(net_gamesettings_t *settings,` - if ORIGCODE  Block until the game start message is received from the server.
- `I_Sleep` (function, `progs/doomgeneric/d_loop.c:333`) `I_Sleep(100);`
- `D_StartNetGame` (function, `progs/doomgeneric/d_loop.c:339`) `void D_StartNetGame(net_gamesettings_t *settings,                     netgame_st` - endif
- `NET_CL_StartGame` (function, `progs/doomgeneric/d_loop.c:406`) `NET_CL_StartGame(settings);` - Send our game settings and block until game start is received from the server.
- `NET_CL_GetSettings` (function, `progs/doomgeneric/d_loop.c:411`) `NET_CL_GetSettings(settings);` - Read the game settings that were received.
- `D_InitNetGame` (function, `progs/doomgeneric/d_loop.c:451`) `boolean D_InitNetGame(net_connect_data_t *connect_data)`
- `I_AtExit` (function, `progs/doomgeneric/d_loop.c:461`) `I_AtExit(D_QuitNetGame, true);` - Call D_QuitNetGame on exit:
- `NET_SV_Init` (function, `progs/doomgeneric/d_loop.c:477`) `NET_SV_Init();`
- `NET_SV_AddModule` (function, `progs/doomgeneric/d_loop.c:478`) `NET_SV_AddModule(&net_loop_server_module);`
- `NET_SV_RegisterWithMaster` (function, `progs/doomgeneric/d_loop.c:480`) `NET_SV_RegisterWithMaster();`
- `NET_WaitForLaunch` (function, `progs/doomgeneric/d_loop.c:544`) `NET_WaitForLaunch();` - Wait for launch message received from server.
- `D_QuitNetGame` (function, `progs/doomgeneric/d_loop.c:560`) `void D_QuitNetGame (void)` - D_QuitNetGame Called before quitting to leave a net game without hanging the other players
- `NET_SV_Shutdown` (function, `progs/doomgeneric/d_loop.c:563`) `NET_SV_Shutdown();` - ifdef FEATURE_MULTIPLAYER
- `NET_CL_Disconnect` (function, `progs/doomgeneric/d_loop.c:564`) `NET_CL_Disconnect();`
- `GetLowTic` (function, `progs/doomgeneric/d_loop.c:567`) `static int GetLowTic(void)`
- `OldNetSync` (function, `progs/doomgeneric/d_loop.c:590`) `static void OldNetSync(void)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 15
- Cross-boundary resolved imports (EXTRACTED): 23

## Connections

- [EXTRACTED] depends_on community 12 <-> 5 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/d_loop.c imports kernel/string.c.
- [EXTRACTED] depends_on community 12 <-> 11 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/d_loop.c imports progs/doomgeneric/d_event.h.

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- What would break if the most connected file in progs/doomgeneric changed?
- Should progs/doomgeneric be split, given cohesion 0.39?

## Sources

- `progs/doomgeneric/d_loop.c`
- `progs/doomgeneric/d_ticcmd.h`
- `progs/doomgeneric/net_client.h`
- `progs/doomgeneric/net_defs.h`
- `progs/doomgeneric/net_io.h`
- `progs/doomgeneric/net_loop.h`
- `progs/doomgeneric/net_packet.h`
- `progs/doomgeneric/net_query.h`
- `progs/doomgeneric/net_sdl.h`
- `progs/doomgeneric/net_server.h`
