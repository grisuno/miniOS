# Subsystem: doomgeneric (page 2 of 12)
Previous: [KB_doomgeneric.md](KB_doomgeneric.md)

## progs/doomgeneric/d_iwad.c
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it...
- Layer: utility
- Language: c
- Symbols:
  - `registry_value_t` (struct, line 83)
  - `AddIWADDir` (function, line 64) `static void AddIWADDir(char *dir)`
  - `GetRegistryString` (function, line 192) `static char *GetRegistryString(registry_value_t *reg_val)`
  - `CheckUninstallStrings` (function, line 236) `static void CheckUninstallStrings(void)`
  - `CheckCollectorsEdition` (function, line 270) `static void CheckCollectorsEdition(void)`
  - `CheckSteamEdition` (function, line 297) `static void CheckSteamEdition(void)`
  - `CheckSteamGUSPatches` (function, line 324) `static void CheckSteamGUSPatches(void)`
  - `CheckDOSDefaults` (function, line 364) `static void CheckDOSDefaults(void)`
  - `DirIsFile` (function, line 391) `static boolean DirIsFile(char *path, char *filename)`
  - `CheckDirectoryHasIWAD` (function, line 408) `static char *CheckDirectoryHasIWAD(char *dir, char *iwadname)`
  - `SearchDirectoryForIWAD` (function, line 449) `static char *SearchDirectoryForIWAD(char *dir, int mask, GameMission_t *mission)`
  - `IdentifyIWADByName` (function, line 477) `static GameMission_t IdentifyIWADByName(char *name, int mask)`
  - `AddDoomWadPath` (function, line 518) `static void AddDoomWadPath(void)`
  - `BuildIWADDirList` (function, line 569) `static void BuildIWADDirList(void)`
  - `D_FindWADByName` (function, line 630) `char *D_FindWADByName(char *name)`
  - `D_TryFindWADByName` (function, line 681) `char *D_TryFindWADByName(char *filename)`
  - `D_FindIWAD` (function, line 704) `char *D_FindIWAD(int mask, GameMission_t *mission)`
  - `D_FindAllIWADs` (function, line 757) `const iwad_t **D_FindAllIWADs(int mask)`
  - `D_SaveGameIWADName` (function, line 796) `char *D_SaveGameIWADName(GameMission_t gamemission)`
  - `D_SuggestIWADName` (function, line 820) `char *D_SuggestIWADName(GameMission_t mission, GameMode_t mode)`
  - `D_SuggestGameName` (function, line 835) `char *D_SuggestGameName(GameMission_t mission, GameMode_t mode)`
  - `MAX_IWAD_DIRS` (macro, line 58) `#define MAX_IWAD_DIRS`
  - `WIN32_LEAN_AND_MEAN` (macro, line 80) `#define WIN32_LEAN_AND_MEAN`
  - `UNINSTALLER_STRING` (macro, line 90) `#define UNINSTALLER_STRING`
  - `SOFTWARE_KEY` (macro, line 102) `#define SOFTWARE_KEY`
  - `SOFTWARE_KEY` (macro, line 104) `#define SOFTWARE_KEY`
  - `STEAM_BFG_GUS_PATCHES` (macro, line 189) `#define STEAM_BFG_GUS_PATCHES`
- Depends on: `kernel/string.c`, `progs/doomgeneric/config.h`, `progs/doomgeneric/d_iwad.h`, `progs/doomgeneric/deh_str.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_config.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/d_iwad.h
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it...
- Layer: utility
- Language: h
- Symbols:
  - `iwad_t` (struct, line 34)
  - `D_FindWADByName` (function, line 42) `char *D_FindWADByName(char *filename);`
  - `D_TryFindWADByName` (function, line 43) `char *D_TryFindWADByName(char *filename);`
  - `D_FindIWAD` (function, line 44) `char *D_FindIWAD(int mask, GameMission_t *mission);`
  - `D_FindAllIWADs` (function, line 45) `const iwad_t **D_FindAllIWADs(int mask);`
  - `D_SaveGameIWADName` (function, line 46) `char *D_SaveGameIWADName(GameMission_t gamemission);`
  - `D_SuggestIWADName` (function, line 47) `char *D_SuggestIWADName(GameMission_t mission, GameMode_t mode);`
  - `D_SuggestGameName` (function, line 48) `char *D_SuggestGameName(GameMission_t mission, GameMode_t mode);`
  - `D_CheckCorrectIWAD` (function, line 49) `void D_CheckCorrectIWAD(GameMission_t mission);`
  - `__D_IWAD__` (macro, line 20) `#define __D_IWAD__`
  - `IWAD_MASK_DOOM` (macro, line 24) `#define IWAD_MASK_DOOM`
  - `IWAD_MASK_HERETIC` (macro, line 30) `#define IWAD_MASK_HERETIC`
  - `IWAD_MASK_HEXEN` (macro, line 31) `#define IWAD_MASK_HEXEN`
  - `IWAD_MASK_STRIFE` (macro, line 32) `#define IWAD_MASK_STRIFE`
- Depends on: `progs/doomgeneric/d_mode.h`
- Imported by: `progs/doomgeneric/d_iwad.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/w_main.c`, `progs/doomgeneric/w_wad.c`

## progs/doomgeneric/d_loop.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `ticcmd_set_t` (struct, line 45)
  - `GetAdjustedTime` (function, line 119) `static int GetAdjustedTime(void)`
  - `BuildNewTic` (function, line 136) `static boolean BuildNewTic(void)`
  - `NetUpdate` (function, line 203) `void NetUpdate (void)`
  - `D_Disconnected` (function, line 252) `static void D_Disconnected(void)`
  - `D_ReceiveTic` (function, line 271) `void D_ReceiveTic(ticcmd_t *ticcmds, boolean *players_mask)`
  - `D_StartGameLoop` (function, line 305) `void D_StartGameLoop(void)`
  - `BlockUntilStart` (function, line 315) `static void BlockUntilStart(net_gamesettings_t *settings,
                            netgame_sta...`
  - `D_StartNetGame` (function, line 340) `void D_StartNetGame(net_gamesettings_t *settings,
                    netgame_startup_callback_t ...`
  - `D_InitNetGame` (function, line 452) `boolean D_InitNetGame(net_connect_data_t *connect_data)`
  - `D_QuitNetGame` (function, line 560) `void D_QuitNetGame (void)`
  - `GetLowTic` (function, line 568) `static int GetLowTic(void)`
  - `OldNetSync` (function, line 591) `static void OldNetSync(void)`
  - `PlayersInGame` (function, line 642) `static boolean PlayersInGame(void)`
  - `TicdupSquash` (function, line 672) `static void TicdupSquash(ticcmd_set_t *set)`
  - `SinglePlayerClear` (function, line 689) `static void SinglePlayerClear(ticcmd_set_t *set)`
  - `TryRunTics` (function, line 706) `void TryRunTics (void)`
  - `D_RegisterLoopCallbacks` (function, line 822) `void D_RegisterLoopCallbacks(loop_interface_t *i)`
- Depends on: `kernel/string.c`, `progs/doomgeneric/d_event.h`, `progs/doomgeneric/d_loop.h`, `progs/doomgeneric/d_ticcmd.h`, `progs/doomgeneric/doomfeatures.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/i_timer.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_fixed.h`, `progs/doomgeneric/net_client.h`, `progs/doomgeneric/net_gui.h`, `progs/doomgeneric/net_io.h`, `progs/doomgeneric/net_loop.h`, `progs/doomgeneric/net_query.h`, `progs/doomgeneric/net_sdl.h`, `progs/doomgeneric/net_server.h`

## progs/doomgeneric/d_loop.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `loop_interface_t` (struct, line 31)
  - `D_RegisterLoopCallbacks` (function, line 52) `void D_RegisterLoopCallbacks(loop_interface_t *i);`
  - `NetUpdate` (function, line 55) `void NetUpdate (void);`
  - `D_QuitNetGame` (function, line 59) `void D_QuitNetGame (void);`
  - `TryRunTics` (function, line 62) `void TryRunTics (void);`
  - `D_StartGameLoop` (function, line 65) `void D_StartGameLoop(void);`
  - `D_StartNetGame` (function, line 74) `void D_StartNetGame(net_gamesettings_t *settings, netgame_startup_callback_t callback);`
  - `singletics` (variable, line 77) `extern boolean singletics;`
  - `ticdup` (variable, line 78) `extern int gametic, ticdup;`
  - `__D_LOOP__` (macro, line 20) `#define __D_LOOP__`
- Depends on: `progs/doomgeneric/net_defs.h`
- Imported by: `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/r_main.c`

## progs/doomgeneric/d_main.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `D_ProcessEvents` (function, line 139) `void D_ProcessEvents (void)`
  - `D_Display` (function, line 169) `void D_Display (void)`
  - `D_BindVariables` (function, line 335) `void D_BindVariables(void)`
  - `D_GrabMouseCallback` (function, line 388) `boolean D_GrabMouseCallback(void)`
  - `D_DoomLoop` (function, line 408) `void D_DoomLoop (void)`
  - `D_PageTicker` (function, line 490) `void D_PageTicker (void)`
  - `D_PageDrawer` (function, line 501) `void D_PageDrawer (void)`
  - `D_AdvanceDemo` (function, line 511) `void D_AdvanceDemo (void)`
  - `D_DoAdvanceDemo` (function, line 521) `void D_DoAdvanceDemo (void)`
  - `D_StartTitle` (function, line 609) `void D_StartTitle (void)`
  - `GetGameName` (function, line 658) `static char *GetGameName(char *gamename)`
  - `SetMissionForPackName` (function, line 701) `static void SetMissionForPackName(char *pack_name)`
  - `D_IdentifyVersion` (function, line 737) `void D_IdentifyVersion(void)`
  - `D_SetGameDescription` (function, line 820) `void D_SetGameDescription(void)`
  - `D_AddFile` (function, line 883) `static boolean D_AddFile(char *filename)`
  - `PrintDehackedBanners` (function, line 918) `void PrintDehackedBanners(void)`
  - `InitGameVersion` (function, line 963) `static void InitGameVersion(void)`
  - `PrintGameVersion` (function, line 1065) `void PrintGameVersion(void)`
  - `D_Endoom` (function, line 1082) `static void D_Endoom(void)`
  - `LoadIwadDeh` (function, line 1105) `static void LoadIwadDeh(void)`
  - `D_DoomMain` (function, line 1178) `void D_DoomMain (void)`
  - `D_ConnectNetGame` (function, line 131) `void D_ConnectNetGame(void);`
  - `D_CheckNetGame` (function, line 132) `void D_CheckNetGame(void);`
  - `R_ExecuteSetViewSize` (function, line 167) `void R_ExecuteSetViewSize (void);`
  - `inhelpscreens` (variable, line 106) `extern boolean inhelpscreens;`
  - `setsizeneeded` (variable, line 165) `extern boolean setsizeneeded;`
  - `showMessages` (variable, line 166) `extern int showMessages;`
  - `forwardmove` (variable, line 1351) `extern int forwardmove[2];`
  - `sidemove` (variable, line 1352) `extern int sidemove[2];`
- Depends on: `kernel/string.c`, `progs/doomgeneric/am_map.h`, `progs/doomgeneric/config.h`, `progs/doomgeneric/d_iwad.h`, `progs/doomgeneric/d_main.h`, `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomfeatures.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/dstrings.h`, `progs/doomgeneric/f_finale.h`, `progs/doomgeneric/f_wipe.h`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/hu_stuff.h`, `progs/doomgeneric/i_endoom.h`, `progs/doomgeneric/i_joystick.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/i_timer.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_config.h`, `progs/doomgeneric/m_controls.h`, `progs/doomgeneric/m_menu.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/net_client.h`, `progs/doomgeneric/net_dedicated.h`, `progs/doomgeneric/net_query.h`, `progs/doomgeneric/p_saveg.h`, `progs/doomgeneric/p_setup.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/st_stuff.h`, `progs/doomgeneric/statdump.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_main.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/wi_stuff.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/d_main.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `D_ProcessEvents` (function, line 30) `void D_ProcessEvents (void);`
  - `D_PageTicker` (function, line 36) `void D_PageTicker (void);`
  - `D_PageDrawer` (function, line 37) `void D_PageDrawer (void);`
  - `D_AdvanceDemo` (function, line 38) `void D_AdvanceDemo (void);`
  - `D_DoAdvanceDemo` (function, line 39) `void D_DoAdvanceDemo (void);`
  - `D_StartTitle` (function, line 40) `void D_StartTitle (void);`
  - `gameaction` (variable, line 46) `extern gameaction_t gameaction;`
  - `__D_MAIN__` (macro, line 21) `#define __D_MAIN__`
- Depends on: `progs/doomgeneric/doomdef.h`
- Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/f_finale.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/i_video.c`, `progs/doomgeneric/m_menu.c`

## progs/doomgeneric/d_mode.c
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it...
- Layer: utility
- Language: c
- Symbols:
  - `D_ValidGameMode` (function, line 50) `boolean D_ValidGameMode(GameMission_t mission, GameMode_t mode)`
  - `D_ValidEpisodeMap` (function, line 65) `boolean D_ValidEpisodeMap(GameMission_t mission, GameMode_t mode,
                          int e...`
  - `D_GetNumEpisodes` (function, line 103) `int D_GetNumEpisodes(GameMission_t mission, GameMode_t mode)`
  - `D_ValidGameVersion` (function, line 135) `boolean D_ValidGameVersion(GameMission_t mission, GameVersion_t version)`
  - `D_IsEpisodeMap` (function, line 161) `boolean D_IsEpisodeMap(GameMission_t mission)`
  - `D_GameMissionString` (function, line 182) `char *D_GameMissionString(GameMission_t mission)`
- Depends on: `progs/doomgeneric/d_mode.h`, `progs/doomgeneric/doomtype.h`

## progs/doomgeneric/d_mode.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `D_GetNumEpisodes` (function, line 93) `int D_GetNumEpisodes(GameMission_t mission, GameMode_t mode);`
  - `D_GameMissionString` (function, line 95) `char *D_GameMissionString(GameMission_t mission);`
  - `__D_MODE__` (macro, line 21) `#define __D_MODE__`
- Depends on: `progs/doomgeneric/doomtype.h`
- Imported by: `progs/doomgeneric/d_iwad.h`, `progs/doomgeneric/d_mode.c`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/statdump.c`, `progs/doomgeneric/w_wad.h`

## progs/doomgeneric/d_net.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `PlayerQuitGame` (function, line 45) `static void PlayerQuitGame(player_t *player)`
  - `RunTic` (function, line 71) `static void RunTic(ticcmd_t *cmds, boolean *ingame)`
  - `LoadGameSettings` (function, line 108) `static void LoadGameSettings(net_gamesettings_t *settings)`
  - `SaveGameSettings` (function, line 139) `static void SaveGameSettings(net_gamesettings_t *settings)`
  - `InitConnectData` (function, line 159) `static void InitConnectData(net_connect_data_t *connect_data)`
  - `D_ConnectNetGame` (function, line 215) `void D_ConnectNetGame(void)`
  - `D_CheckNetGame` (function, line 240) `void D_CheckNetGame (void)`
  - `advancedemo` (variable, line 73) `extern boolean advancedemo;`
- Depends on: `progs/doomgeneric/d_loop.h`, `progs/doomgeneric/d_main.h`, `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomfeatures.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/i_timer.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_menu.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/w_checksum.h`, `progs/doomgeneric/w_wad.h`

## progs/doomgeneric/d_player.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `player_s` (struct, line 78)
  - `wbplayerstruct_t` (struct, line 168)
  - `wbstartstruct_t` (struct, line 182)
  - `mo` (type_alias, line 78) `typedef struct player_s { mobj_t* mo;`
  - `__D_PLAYER__` (macro, line 21) `#define __D_PLAYER__`
- Depends on: `progs/doomgeneric/d_items.h`, `progs/doomgeneric/d_ticcmd.h`, `progs/doomgeneric/net_defs.h`, `progs/doomgeneric/p_mobj.h`, `progs/doomgeneric/p_pspr.h`
- Imported by: `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/r_main.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/statdump.c`

## progs/doomgeneric/d_textur.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `pic_t` (struct, line 33)
  - `__D_TEXTUR__` (macro, line 22) `#define __D_TEXTUR__`
- Depends on: `progs/doomgeneric/doomtype.h`

## progs/doomgeneric/d_think.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `thinker_s` (struct, line 58)
  - `think_t` (type_alias, line 54) `typedef actionf_t think_t;`
  - `prev` (type_alias, line 58) `typedef struct thinker_s { struct thinker_s* prev;`
  - `__D_THINK__` (macro, line 23) `#define __D_THINK__`
- Imported by: `progs/doomgeneric/info.h`, `progs/doomgeneric/p_mobj.h`, `progs/doomgeneric/r_defs.h`

## progs/doomgeneric/d_ticcmd.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `ticcmd_t` (struct, line 32)
  - `__D_TICCMD__` (macro, line 22) `#define __D_TICCMD__`
- Depends on: `progs/doomgeneric/doomtype.h`
- Imported by: `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/d_player.h`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/net_client.h`, `progs/doomgeneric/net_defs.h`

## progs/doomgeneric/deh_main.h
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it...
- Layer: utility
- Language: h
- Symbols:
  - `DEH_ParseCommandLine` (function, line 33) `void DEH_ParseCommandLine(void);`
  - `DEH_LoadFile` (function, line 34) `int DEH_LoadFile(char *filename);`
  - `DEH_LoadLump` (function, line 35) `int DEH_LoadLump(int lumpnum, boolean allow_long, boolean allow_error);`
  - `DEH_LoadLumpByName` (function, line 36) `int DEH_LoadLumpByName(char *name, boolean allow_long, boolean allow_error);`
  - `DEH_Checksum` (function, line 40) `void DEH_Checksum(sha1_digest_t digest);`
  - `deh_allow_extended_strings` (variable, line 42) `extern boolean deh_allow_extended_strings;`
  - `deh_allow_long_strings` (variable, line 43) `extern boolean deh_allow_long_strings;`
  - `deh_allow_long_cheats` (variable, line 44) `extern boolean deh_allow_long_cheats;`
  - `deh_apply_cheats` (variable, line 45) `extern boolean deh_apply_cheats;`
  - `DEH_MAIN_H` (macro, line 19) `#define DEH_MAIN_H`
  - `DEH_VANILLA_NUMSTATES` (macro, line 30) `#define DEH_VANILLA_NUMSTATES`
  - `DEH_VANILLA_NUMSFX` (macro, line 31) `#define DEH_VANILLA_NUMSFX`
- Depends on: `progs/doomgeneric/deh_str.h`, `progs/doomgeneric/doomfeatures.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/sha1.h`
- Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/f_finale.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/p_doors.c`, `progs/doomgeneric/p_inter.c`, `progs/doomgeneric/p_saveg.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/p_switch.c`, `progs/doomgeneric/r_data.c`, `progs/doomgeneric/r_draw.c`, `progs/doomgeneric/r_things.c`, `progs/doomgeneric/st_lib.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/wi_stuff.c`

## progs/doomgeneric/deh_misc.h
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it...
- Layer: utility
- Language: h
- Symbols:
  - `deh_initial_health` (variable, line 42) `extern int deh_initial_health;`
  - `deh_initial_bullets` (variable, line 43) `extern int deh_initial_bullets;`
  - `deh_max_health` (variable, line 44) `extern int deh_max_health;`
  - `deh_max_armor` (variable, line 45) `extern int deh_max_armor;`
  - `deh_green_armor_class` (variable, line 46) `extern int deh_green_armor_class;`
  - `deh_blue_armor_class` (variable, line 47) `extern int deh_blue_armor_class;`
  - `deh_max_soulsphere` (variable, line 48) `extern int deh_max_soulsphere;`
  - `deh_soulsphere_health` (variable, line 49) `extern int deh_soulsphere_health;`
  - `deh_megasphere_health` (variable, line 50) `extern int deh_megasphere_health;`
  - `deh_god_mode_health` (variable, line 51) `extern int deh_god_mode_health;`
  - `deh_idfa_armor` (variable, line 52) `extern int deh_idfa_armor;`
  - `deh_idfa_armor_class` (variable, line 53) `extern int deh_idfa_armor_class;`
  - `deh_idkfa_armor` (variable, line 54) `extern int deh_idkfa_armor;`
  - `deh_idkfa_armor_class` (variable, line 55) `extern int deh_idkfa_armor_class;`
  - `deh_bfg_cells_per_shot` (variable, line 56) `extern int deh_bfg_cells_per_shot;`
  - `deh_species_infighting` (variable, line 57) `extern int deh_species_infighting;`
  - `DEH_MISC_H` (macro, line 19) `#define DEH_MISC_H`
  - `DEH_DEFAULT_INITIAL_HEALTH` (macro, line 23) `#define DEH_DEFAULT_INITIAL_HEALTH`
  - `DEH_DEFAULT_INITIAL_BULLETS` (macro, line 24) `#define DEH_DEFAULT_INITIAL_BULLETS`
  - `DEH_DEFAULT_MAX_HEALTH` (macro, line 25) `#define DEH_DEFAULT_MAX_HEALTH`
  - `DEH_DEFAULT_MAX_ARMOR` (macro, line 26) `#define DEH_DEFAULT_MAX_ARMOR`
  - `DEH_DEFAULT_GREEN_ARMOR_CLASS` (macro, line 27) `#define DEH_DEFAULT_GREEN_ARMOR_CLASS`
  - `DEH_DEFAULT_BLUE_ARMOR_CLASS` (macro, line 28) `#define DEH_DEFAULT_BLUE_ARMOR_CLASS`
  - `DEH_DEFAULT_MAX_SOULSPHERE` (macro, line 29) `#define DEH_DEFAULT_MAX_SOULSPHERE`
  - `DEH_DEFAULT_SOULSPHERE_HEALTH` (macro, line 30) `#define DEH_DEFAULT_SOULSPHERE_HEALTH`
  - `DEH_DEFAULT_MEGASPHERE_HEALTH` (macro, line 31) `#define DEH_DEFAULT_MEGASPHERE_HEALTH`
  - `DEH_DEFAULT_GOD_MODE_HEALTH` (macro, line 32) `#define DEH_DEFAULT_GOD_MODE_HEALTH`
  - `DEH_DEFAULT_IDFA_ARMOR` (macro, line 33) `#define DEH_DEFAULT_IDFA_ARMOR`
  - `DEH_DEFAULT_IDFA_ARMOR_CLASS` (macro, line 34) `#define DEH_DEFAULT_IDFA_ARMOR_CLASS`
  - `DEH_DEFAULT_IDKFA_ARMOR` (macro, line 35) `#define DEH_DEFAULT_IDKFA_ARMOR`
  - `DEH_DEFAULT_IDKFA_ARMOR_CLASS` (macro, line 36) `#define DEH_DEFAULT_IDKFA_ARMOR_CLASS`
  - `DEH_DEFAULT_BFG_CELLS_PER_SHOT` (macro, line 37) `#define DEH_DEFAULT_BFG_CELLS_PER_SHOT`
  - `DEH_DEFAULT_SPECIES_INFIGHTING` (macro, line 38) `#define DEH_DEFAULT_SPECIES_INFIGHTING`
  - `deh_initial_health` (macro, line 63) `#define deh_initial_health`
  - `deh_initial_bullets` (macro, line 64) `#define deh_initial_bullets`
  - `deh_max_health` (macro, line 65) `#define deh_max_health`
  - `deh_max_armor` (macro, line 66) `#define deh_max_armor`
  - `deh_green_armor_class` (macro, line 67) `#define deh_green_armor_class`
  - `deh_blue_armor_class` (macro, line 68) `#define deh_blue_armor_class`
  - `deh_max_soulsphere` (macro, line 69) `#define deh_max_soulsphere`
  - `deh_soulsphere_health` (macro, line 70) `#define deh_soulsphere_health`
  - `deh_megasphere_health` (macro, line 71) `#define deh_megasphere_health`
  - `deh_god_mode_health` (macro, line 72) `#define deh_god_mode_health`
  - `deh_idfa_armor` (macro, line 73) `#define deh_idfa_armor`
  - `deh_idfa_armor_class` (macro, line 74) `#define deh_idfa_armor_class`
  - `deh_idkfa_armor` (macro, line 75) `#define deh_idkfa_armor`
  - `deh_idkfa_armor_class` (macro, line 76) `#define deh_idkfa_armor_class`
  - `deh_bfg_cells_per_shot` (macro, line 77) `#define deh_bfg_cells_per_shot`
  - `deh_species_infighting` (macro, line 78) `#define deh_species_infighting`
- Depends on: `progs/doomgeneric/doomfeatures.h`
- Imported by: `progs/doomgeneric/g_game.c`, `progs/doomgeneric/p_inter.c`, `progs/doomgeneric/p_map.c`, `progs/doomgeneric/p_pspr.c`, `progs/doomgeneric/st_stuff.c`

## progs/doomgeneric/deh_str.h
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it...
- Layer: utility
- Language: h
- Symbols:
  - `DEH_String` (function, line 29) `char *DEH_String(char *s);`
  - `DEH_printf` (function, line 30) `void DEH_printf(char *fmt, ...);`
  - `DEH_fprintf` (function, line 31) `void DEH_fprintf(FILE *fstream, char *fmt, ...);`
  - `DEH_snprintf` (function, line 32) `void DEH_snprintf(char *buffer, size_t len, char *fmt, ...);`
  - `DEH_AddStringReplacement` (function, line 33) `void DEH_AddStringReplacement(char *from_text, char *to_text);`
  - `DEH_STR_H` (macro, line 19) `#define DEH_STR_H`
  - `DEH_String` (macro, line 38) `#define DEH_String(x)`
  - `DEH_printf` (macro, line 39) `#define DEH_printf`
  - `DEH_fprintf` (macro, line 40) `#define DEH_fprintf`
  - `DEH_snprintf` (macro, line 41) `#define DEH_snprintf`
  - `DEH_AddStringReplacement` (macro, line 42) `#define DEH_AddStringReplacement(x, y)`
- Depends on: `progs/doomgeneric/doomfeatures.h`
- Imported by: `progs/doomgeneric/d_iwad.c`, `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/m_misc.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/v_video.c`

## progs/doomgeneric/doom.h
- Layer: utility
- Language: h
- Symbols:
  - `D_DoomMain` (function, line 28) `void D_DoomMain (void);`
  - `SRC_CHOCDOOM_DOOM_H_` (macro, line 10) `#define SRC_CHOCDOOM_DOOM_H_`

## progs/doomgeneric/doomdata.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `__DOOMDATA__` (macro, line 22) `#define __DOOMDATA__`
  - `ML_BLOCKING` (macro, line 98) `#define ML_BLOCKING`
  - `ML_BLOCKMONSTERS` (macro, line 101) `#define ML_BLOCKMONSTERS`
  - `ML_TWOSIDED` (macro, line 105) `#define ML_TWOSIDED`
  - `ML_DONTPEGTOP` (macro, line 117) `#define ML_DONTPEGTOP`
  - `ML_DONTPEGBOTTOM` (macro, line 120) `#define ML_DONTPEGBOTTOM`
  - `ML_SECRET` (macro, line 123) `#define ML_SECRET`
  - `ML_SOUNDBLOCK` (macro, line 126) `#define ML_SOUNDBLOCK`
  - `ML_DONTDRAW` (macro, line 129) `#define ML_DONTDRAW`
  - `ML_MAPPED` (macro, line 132) `#define ML_MAPPED`
  - `NF_SUBSECTOR` (macro, line 175) `#define	NF_SUBSECTOR`
- Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomtype.h`
- Imported by: `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/p_mobj.h`

## progs/doomgeneric/doomdef.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Depends on: `progs/doomgeneric/doomdef.h`

## progs/doomgeneric/doomdef.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `__DOOMDEF__` (macro, line 21) `#define __DOOMDEF__`
  - `DOOM_VERSION` (macro, line 34) `#define DOOM_VERSION`
  - `DOOM_191_VERSION` (macro, line 37) `#define DOOM_191_VERSION`
  - `RANGECHECK` (macro, line 42) `#define RANGECHECK`
  - `MAXPLAYERS` (macro, line 45) `#define MAXPLAYERS`
  - `MTF_EASY` (macro, line 77) `#define	MTF_EASY`
  - `MTF_NORMAL` (macro, line 78) `#define	MTF_NORMAL`
  - `MTF_HARD` (macro, line 79) `#define	MTF_HARD`
  - `MTF_AMBUSH` (macro, line 82) `#define	MTF_AMBUSH`
- Depends on: `kernel/string.c`, `progs/doomgeneric/d_mode.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_timer.h`
- Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_items.h`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_main.h`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/doomdata.h`, `progs/doomgeneric/doomdef.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/hu_lib.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/p_ceilng.c`, `progs/doomgeneric/p_doors.c`, `progs/doomgeneric/p_enemy.c`, `progs/doomgeneric/p_floor.c`, `progs/doomgeneric/p_inter.c`, `progs/doomgeneric/p_lights.c`, `progs/doomgeneric/p_map.c`, `progs/doomgeneric/p_maputl.c`, `progs/doomgeneric/p_mobj.c`, `progs/doomgeneric/p_plats.c`, `progs/doomgeneric/p_pspr.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/p_sight.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/p_switch.c`, `progs/doomgeneric/p_telept.c`, `progs/doomgeneric/p_user.c`, `progs/doomgeneric/r_bsp.c`, `progs/doomgeneric/r_data.c`, `progs/doomgeneric/r_defs.h`, `progs/doomgeneric/r_draw.c`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/r_main.c`, `progs/doomgeneric/r_plane.c`, `progs/doomgeneric/r_segs.c`, `progs/doomgeneric/r_things.c`, `progs/doomgeneric/st_lib.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/wi_stuff.h`

## progs/doomgeneric/doomfeatures.h
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it...
- Layer: utility
- Language: h
- Symbols:
  - `DOOM_FEATURES_H` (macro, line 20) `#define DOOM_FEATURES_H`
  - `FEATURE_SOUND` (macro, line 36) `#define FEATURE_SOUND`
- Imported by: `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/deh_misc.h`, `progs/doomgeneric/deh_str.h`, `progs/doomgeneric/i_minios_sound.c`, `progs/doomgeneric/i_sound.c`, `progs/doomgeneric/m_config.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/w_main.c`

## progs/doomgeneric/doomgeneric.c
- Layer: utility
- Language: c
- Symbols:
  - `dg_Create` (function, line 6) `void dg_Create()`
- Depends on: `progs/doomgeneric/doomgeneric.h`

## progs/doomgeneric/doomgeneric.h
- Layer: utility
- Language: h
- Symbols:
  - `DG_Init` (function, line 14) `void DG_Init();`
  - `DG_DrawFrame` (function, line 15) `void DG_DrawFrame();`
  - `DG_SleepMs` (function, line 16) `void DG_SleepMs(uint32_t ms);`
  - `DG_GetTicksMs` (function, line 17) `uint32_t DG_GetTicksMs();`
  - `DG_GetKey` (function, line 18) `int DG_GetKey(int* pressed, unsigned char* key);`
  - `DG_SetWindowTitle` (function, line 19) `void DG_SetWindowTitle(const char * title);`
  - `DG_ScreenBuffer` (variable, line 11) `extern uint32_t* DG_ScreenBuffer;`
  - `DOOM_GENERIC` (macro, line 2) `#define DOOM_GENERIC`
  - `DOOMGENERIC_RESX` (macro, line 7) `#define DOOMGENERIC_RESX`
  - `DOOMGENERIC_RESY` (macro, line 8) `#define DOOMGENERIC_RESY`
- Imported by: `progs/doomgeneric/doomgeneric.c`, `progs/doomgeneric/doomgeneric_minios.c`, `progs/doomgeneric/doomgeneric_sdl.c`, `progs/doomgeneric/doomgeneric_soso.c`, `progs/doomgeneric/doomgeneric_sosox.c`, `progs/doomgeneric/doomgeneric_win.c`, `progs/doomgeneric/doomgeneric_xlib.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_minios_sound.c`, `progs/doomgeneric/i_timer.c`, `progs/doomgeneric/i_video.c`

## progs/doomgeneric/doomgeneric_minios.c
- Doc: MiniOS platform layer for doomgeneric.
- Layer: utility
- Language: c
- Symbols:
  - `color` (struct, line 103)
  - `mini_parse_autoframes` (function, line 24) `static void mini_parse_autoframes(int argc, char **argv)`
  - `mini_parse_windowed` (function, line 43) `static void mini_parse_windowed(int argc, char **argv)`
  - `sys_time_ms` (function, line 56) `static long sys_time_ms(void)`
  - `sys_kbd` (function, line 61) `static long sys_kbd(void)`
  - `sys_palette` (function, line 66) `static long sys_palette(const unsigned char *pal)`
  - `sys_kbd_raw` (function, line 71) `static long sys_kbd_raw(int on)`
  - `sys_vga_mode` (function, line 76) `static long sys_vga_mode(int on)`
  - `sys_gfx_zoom` (function, line 81) `static long sys_gfx_zoom(long mode)`
  - `sys_doom_frame` (function, line 86) `static long sys_doom_frame(void)`
  - `load_vga_palette` (function, line 110) `static void load_vga_palette(void)`
  - `scancode_to_doom` (function, line 123) `static unsigned char scancode_to_doom(unsigned char raw)`
  - `kbd_enqueue` (function, line 182) `static void kbd_enqueue(unsigned char doom_key, int pressed)`
  - `kbd_poll` (function, line 189) `static void kbd_poll(void)`
  - `DG_Init` (function, line 232) `void DG_Init(void)`
  - `DG_DrawFrame` (function, line 243) `void DG_DrawFrame(void)`
  - `DG_SleepMs` (function, line 274) `void DG_SleepMs(uint32_t ms)`
  - `DG_GetTicksMs` (function, line 280) `uint32_t DG_GetTicksMs(void)`
  - `DG_GetKey` (function, line 284) `int DG_GetKey(int *pressed, unsigned char *key)`
  - `DG_SetWindowTitle` (function, line 295) `void DG_SetWindowTitle(const char *title)`
  - `MINIOS_DOOM_BACKBUF_ADDR` (function, line 4) `* MINIOS_DOOM_BACKBUF_ADDR (minios_abi.h);`
  - `colors` (variable, line 104) `extern struct color colors[256];`
  - `I_VideoBuffer` (variable, line 230) `extern unsigned char *I_VideoBuffer;`
  - `myargc` (variable, line 233) `extern int myargc;`
  - `myargv` (variable, line 234) `extern char **myargv;`
  - `FB_ADDR` (macro, line 96) `#define FB_ADDR`
  - `FB_WIDTH` (macro, line 97) `#define FB_WIDTH`
  - `FB_HEIGHT` (macro, line 98) `#define FB_HEIGHT`
  - `KBD_QUEUE_SIZE` (macro, line 178) `#define KBD_QUEUE_SIZE`
- Depends on: `kernel/string.c`, `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/s_sound.h`, `progs/minios_abi.h`

## progs/doomgeneric/doomgeneric_sdl.c
- Doc: doomgeneric for soso os
- Layer: utility
- Language: c
- Symbols:
  - `convertToDoomKey` (function, line 23) `static unsigned char convertToDoomKey(unsigned int key)`
  - `addKeyToQueue` (function, line 63) `static void addKeyToQueue(int pressed, unsigned int keyCode)`
  - `handleKeyInput` (function, line 72) `static void handleKeyInput()`
  - `DG_Init` (function, line 93) `void DG_Init()`
  - `DG_DrawFrame` (function, line 112) `void DG_DrawFrame()`
  - `DG_SleepMs` (function, line 123) `void DG_SleepMs(uint32_t ms)`
  - `DG_GetTicksMs` (function, line 128) `uint32_t DG_GetTicksMs()`
  - `DG_GetKey` (function, line 133) `int DG_GetKey(int* pressed, unsigned char* doomKey)`
  - `DG_SetWindowTitle` (function, line 152) `void DG_SetWindowTitle(const char * title)`
  - `KEYQUEUE_SIZE` (macro, line 17) `#define KEYQUEUE_SIZE`
- Depends on: `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/m_argv.h`, `progs/pokemon/minios_stubs/SDL.h`

## progs/doomgeneric/doomgeneric_soso.c
- Doc: doomgeneric for soso os
- Layer: utility
- Language: c
- Symbols:
  - `EnFrameBuferIoctl` (enum, line 36)
  - `convertToDoomKey` (function, line 43) `static unsigned char convertToDoomKey(unsigned char scancode)`
  - `addKeyToQueue` (function, line 92) `static void addKeyToQueue(int pressed, unsigned char keyCode)`
  - `disableRawMode` (function, line 108) `void disableRawMode()`
  - `enableRawMode` (function, line 114) `void enableRawMode()`
  - `DG_Init` (function, line 124) `void DG_Init()`
  - `handleKeyInput` (function, line 186) `static void handleKeyInput()`
  - `DG_DrawFrame` (function, line 214) `void DG_DrawFrame()`
  - `DG_SleepMs` (function, line 227) `void DG_SleepMs(uint32_t ms)`
  - `DG_GetTicksMs` (function, line 232) `uint32_t DG_GetTicksMs()`
  - `DG_GetKey` (function, line 237) `int DG_GetKey(int* pressed, unsigned char* doomKey)`
  - `DG_SetWindowTitle` (function, line 258) `void DG_SetWindowTitle(const char * title)`
  - `KEYQUEUE_SIZE` (macro, line 24) `#define KEYQUEUE_SIZE`
- Depends on: `kernel/string.c`, `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/m_argv.h`


Next: [KB_doomgeneric_p3.md](KB_doomgeneric_p3.md)
