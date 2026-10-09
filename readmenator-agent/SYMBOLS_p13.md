# Symbols (page 13 of 26)
Previous: [SYMBOLS_p12.md](SYMBOLS_p12.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `D_InitNetGame` | function | `progs/doomgeneric/d_loop.c:452` | `boolean D_InitNetGame(net_connect_data_t *connect_data)` |
| `D_QuitNetGame` | function | `progs/doomgeneric/d_loop.c:560` | `void D_QuitNetGame (void)` |
| `D_ReceiveTic` | function | `progs/doomgeneric/d_loop.c:271` | `void D_ReceiveTic(ticcmd_t *ticcmds, boolean *players_mask)` |
| `D_RegisterLoopCallbacks` | function | `progs/doomgeneric/d_loop.c:822` | `void D_RegisterLoopCallbacks(loop_interface_t *i)` |
| `D_StartGameLoop` | function | `progs/doomgeneric/d_loop.c:305` | `void D_StartGameLoop(void)` |
| `D_StartNetGame` | function | `progs/doomgeneric/d_loop.c:340` | `void D_StartNetGame(net_gamesettings_t *settings,                     netgame_startup_callback_t ...` |
| `GetAdjustedTime` | function | `progs/doomgeneric/d_loop.c:119` | `static int GetAdjustedTime(void)` |
| `GetLowTic` | function | `progs/doomgeneric/d_loop.c:568` | `static int GetLowTic(void)` |
| `NetUpdate` | function | `progs/doomgeneric/d_loop.c:203` | `void NetUpdate (void)` |
| `OldNetSync` | function | `progs/doomgeneric/d_loop.c:591` | `static void OldNetSync(void)` |
| `PlayersInGame` | function | `progs/doomgeneric/d_loop.c:642` | `static boolean PlayersInGame(void)` |
| `SinglePlayerClear` | function | `progs/doomgeneric/d_loop.c:689` | `static void SinglePlayerClear(ticcmd_set_t *set)` |
| `TicdupSquash` | function | `progs/doomgeneric/d_loop.c:672` | `static void TicdupSquash(ticcmd_set_t *set)` |
| `TryRunTics` | function | `progs/doomgeneric/d_loop.c:706` | `void TryRunTics (void)` |
| `ticcmd_set_t` | struct | `progs/doomgeneric/d_loop.c:45` | `` |
| `D_QuitNetGame` | function | `progs/doomgeneric/d_loop.h:59` | `void D_QuitNetGame (void);` |
| `D_RegisterLoopCallbacks` | function | `progs/doomgeneric/d_loop.h:52` | `void D_RegisterLoopCallbacks(loop_interface_t *i);` |
| `D_StartGameLoop` | function | `progs/doomgeneric/d_loop.h:65` | `void D_StartGameLoop(void);` |
| `D_StartNetGame` | function | `progs/doomgeneric/d_loop.h:74` | `void D_StartNetGame(net_gamesettings_t *settings, netgame_startup_callback_t callback);` |
| `NetUpdate` | function | `progs/doomgeneric/d_loop.h:55` | `void NetUpdate (void);` |
| `TryRunTics` | function | `progs/doomgeneric/d_loop.h:62` | `void TryRunTics (void);` |
| `__D_LOOP__` | macro | `progs/doomgeneric/d_loop.h:20` | `#define __D_LOOP__` |
| `loop_interface_t` | struct | `progs/doomgeneric/d_loop.h:31` | `` |
| `singletics` | variable | `progs/doomgeneric/d_loop.h:77` | `extern boolean singletics;` |
| `ticdup` | variable | `progs/doomgeneric/d_loop.h:78` | `extern int gametic, ticdup;` |
| `D_AddFile` | function | `progs/doomgeneric/d_main.c:883` | `static boolean D_AddFile(char *filename)` |
| `D_AdvanceDemo` | function | `progs/doomgeneric/d_main.c:511` | `void D_AdvanceDemo (void)` |
| `D_BindVariables` | function | `progs/doomgeneric/d_main.c:335` | `void D_BindVariables(void)` |
| `D_CheckNetGame` | function | `progs/doomgeneric/d_main.c:132` | `void D_CheckNetGame(void);` |
| `D_ConnectNetGame` | function | `progs/doomgeneric/d_main.c:131` | `void D_ConnectNetGame(void);` |
| `D_Display` | function | `progs/doomgeneric/d_main.c:169` | `void D_Display (void)` |
| `D_DoAdvanceDemo` | function | `progs/doomgeneric/d_main.c:521` | `void D_DoAdvanceDemo (void)` |
| `D_DoomLoop` | function | `progs/doomgeneric/d_main.c:408` | `void D_DoomLoop (void)` |
| `D_DoomMain` | function | `progs/doomgeneric/d_main.c:1178` | `void D_DoomMain (void)` |
| `D_Endoom` | function | `progs/doomgeneric/d_main.c:1082` | `static void D_Endoom(void)` |
| `D_GrabMouseCallback` | function | `progs/doomgeneric/d_main.c:388` | `boolean D_GrabMouseCallback(void)` |
| `D_IdentifyVersion` | function | `progs/doomgeneric/d_main.c:737` | `void D_IdentifyVersion(void)` |
| `D_PageDrawer` | function | `progs/doomgeneric/d_main.c:501` | `void D_PageDrawer (void)` |
| `D_PageTicker` | function | `progs/doomgeneric/d_main.c:490` | `void D_PageTicker (void)` |
| `D_ProcessEvents` | function | `progs/doomgeneric/d_main.c:139` | `void D_ProcessEvents (void)` |
| `D_SetGameDescription` | function | `progs/doomgeneric/d_main.c:820` | `void D_SetGameDescription(void)` |
| `D_StartTitle` | function | `progs/doomgeneric/d_main.c:609` | `void D_StartTitle (void)` |
| `GetGameName` | function | `progs/doomgeneric/d_main.c:658` | `static char *GetGameName(char *gamename)` |
| `InitGameVersion` | function | `progs/doomgeneric/d_main.c:963` | `static void InitGameVersion(void)` |
| `LoadIwadDeh` | function | `progs/doomgeneric/d_main.c:1105` | `static void LoadIwadDeh(void)` |
| `PrintDehackedBanners` | function | `progs/doomgeneric/d_main.c:918` | `void PrintDehackedBanners(void)` |
| `PrintGameVersion` | function | `progs/doomgeneric/d_main.c:1065` | `void PrintGameVersion(void)` |
| `R_ExecuteSetViewSize` | function | `progs/doomgeneric/d_main.c:167` | `void R_ExecuteSetViewSize (void);` |
| `SetMissionForPackName` | function | `progs/doomgeneric/d_main.c:701` | `static void SetMissionForPackName(char *pack_name)` |
| `forwardmove` | variable | `progs/doomgeneric/d_main.c:1351` | `extern int forwardmove[2];` |
| `inhelpscreens` | variable | `progs/doomgeneric/d_main.c:106` | `extern boolean inhelpscreens;` |
| `setsizeneeded` | variable | `progs/doomgeneric/d_main.c:165` | `extern boolean setsizeneeded;` |
| `showMessages` | variable | `progs/doomgeneric/d_main.c:166` | `extern int showMessages;` |
| `sidemove` | variable | `progs/doomgeneric/d_main.c:1352` | `extern int sidemove[2];` |
| `D_AdvanceDemo` | function | `progs/doomgeneric/d_main.h:38` | `void D_AdvanceDemo (void);` |
| `D_DoAdvanceDemo` | function | `progs/doomgeneric/d_main.h:39` | `void D_DoAdvanceDemo (void);` |
| `D_PageDrawer` | function | `progs/doomgeneric/d_main.h:37` | `void D_PageDrawer (void);` |
| `D_PageTicker` | function | `progs/doomgeneric/d_main.h:36` | `void D_PageTicker (void);` |
| `D_ProcessEvents` | function | `progs/doomgeneric/d_main.h:30` | `void D_ProcessEvents (void);` |
| `D_StartTitle` | function | `progs/doomgeneric/d_main.h:40` | `void D_StartTitle (void);` |
| `__D_MAIN__` | macro | `progs/doomgeneric/d_main.h:21` | `#define __D_MAIN__` |
| `gameaction` | variable | `progs/doomgeneric/d_main.h:46` | `extern gameaction_t gameaction;` |
| `D_GameMissionString` | function | `progs/doomgeneric/d_mode.c:182` | `char *D_GameMissionString(GameMission_t mission)` |
| `D_GetNumEpisodes` | function | `progs/doomgeneric/d_mode.c:103` | `int D_GetNumEpisodes(GameMission_t mission, GameMode_t mode)` |
| `D_IsEpisodeMap` | function | `progs/doomgeneric/d_mode.c:161` | `boolean D_IsEpisodeMap(GameMission_t mission)` |
| `D_ValidEpisodeMap` | function | `progs/doomgeneric/d_mode.c:65` | `boolean D_ValidEpisodeMap(GameMission_t mission, GameMode_t mode,                           int e...` |
| `D_ValidGameMode` | function | `progs/doomgeneric/d_mode.c:50` | `boolean D_ValidGameMode(GameMission_t mission, GameMode_t mode)` |
| `D_ValidGameVersion` | function | `progs/doomgeneric/d_mode.c:135` | `boolean D_ValidGameVersion(GameMission_t mission, GameVersion_t version)` |
| `D_GameMissionString` | function | `progs/doomgeneric/d_mode.h:95` | `char *D_GameMissionString(GameMission_t mission);` |
| `D_GetNumEpisodes` | function | `progs/doomgeneric/d_mode.h:93` | `int D_GetNumEpisodes(GameMission_t mission, GameMode_t mode);` |
| `__D_MODE__` | macro | `progs/doomgeneric/d_mode.h:21` | `#define __D_MODE__` |
| `D_CheckNetGame` | function | `progs/doomgeneric/d_net.c:240` | `void D_CheckNetGame (void)` |
| `D_ConnectNetGame` | function | `progs/doomgeneric/d_net.c:215` | `void D_ConnectNetGame(void)` |
| `InitConnectData` | function | `progs/doomgeneric/d_net.c:159` | `static void InitConnectData(net_connect_data_t *connect_data)` |
| `LoadGameSettings` | function | `progs/doomgeneric/d_net.c:108` | `static void LoadGameSettings(net_gamesettings_t *settings)` |
| `PlayerQuitGame` | function | `progs/doomgeneric/d_net.c:45` | `static void PlayerQuitGame(player_t *player)` |
| `RunTic` | function | `progs/doomgeneric/d_net.c:71` | `static void RunTic(ticcmd_t *cmds, boolean *ingame)` |
| `SaveGameSettings` | function | `progs/doomgeneric/d_net.c:139` | `static void SaveGameSettings(net_gamesettings_t *settings)` |
| `advancedemo` | variable | `progs/doomgeneric/d_net.c:73` | `extern boolean advancedemo;` |
| `__D_PLAYER__` | macro | `progs/doomgeneric/d_player.h:21` | `#define __D_PLAYER__` |
| `mo` | type_alias | `progs/doomgeneric/d_player.h:78` | `typedef struct player_s { mobj_t* mo;` |
| `player_s` | struct | `progs/doomgeneric/d_player.h:78` | `` |
| `wbplayerstruct_t` | struct | `progs/doomgeneric/d_player.h:168` | `` |
| `wbstartstruct_t` | struct | `progs/doomgeneric/d_player.h:182` | `` |
| `__D_TEXTUR__` | macro | `progs/doomgeneric/d_textur.h:22` | `#define __D_TEXTUR__` |
| `pic_t` | struct | `progs/doomgeneric/d_textur.h:33` | `` |
| `__D_THINK__` | macro | `progs/doomgeneric/d_think.h:23` | `#define __D_THINK__` |
| `prev` | type_alias | `progs/doomgeneric/d_think.h:58` | `typedef struct thinker_s { struct thinker_s* prev;` |
| `think_t` | type_alias | `progs/doomgeneric/d_think.h:54` | `typedef actionf_t think_t;` |
| `thinker_s` | struct | `progs/doomgeneric/d_think.h:58` | `` |
| `__D_TICCMD__` | macro | `progs/doomgeneric/d_ticcmd.h:22` | `#define __D_TICCMD__` |
| `ticcmd_t` | struct | `progs/doomgeneric/d_ticcmd.h:32` | `` |
| `DEH_Checksum` | function | `progs/doomgeneric/deh_main.h:40` | `void DEH_Checksum(sha1_digest_t digest);` |
| `DEH_LoadFile` | function | `progs/doomgeneric/deh_main.h:34` | `int DEH_LoadFile(char *filename);` |
| `DEH_LoadLump` | function | `progs/doomgeneric/deh_main.h:35` | `int DEH_LoadLump(int lumpnum, boolean allow_long, boolean allow_error);` |
| `DEH_LoadLumpByName` | function | `progs/doomgeneric/deh_main.h:36` | `int DEH_LoadLumpByName(char *name, boolean allow_long, boolean allow_error);` |
| `DEH_MAIN_H` | macro | `progs/doomgeneric/deh_main.h:19` | `#define DEH_MAIN_H` |
| `DEH_ParseCommandLine` | function | `progs/doomgeneric/deh_main.h:33` | `void DEH_ParseCommandLine(void);` |
| `DEH_VANILLA_NUMSFX` | macro | `progs/doomgeneric/deh_main.h:31` | `#define DEH_VANILLA_NUMSFX` |
| `DEH_VANILLA_NUMSTATES` | macro | `progs/doomgeneric/deh_main.h:30` | `#define DEH_VANILLA_NUMSTATES` |
| `deh_allow_extended_strings` | variable | `progs/doomgeneric/deh_main.h:42` | `extern boolean deh_allow_extended_strings;` |
| `deh_allow_long_cheats` | variable | `progs/doomgeneric/deh_main.h:44` | `extern boolean deh_allow_long_cheats;` |
| `deh_allow_long_strings` | variable | `progs/doomgeneric/deh_main.h:43` | `extern boolean deh_allow_long_strings;` |
| `deh_apply_cheats` | variable | `progs/doomgeneric/deh_main.h:45` | `extern boolean deh_apply_cheats;` |
| `DEH_DEFAULT_BFG_CELLS_PER_SHOT` | macro | `progs/doomgeneric/deh_misc.h:37` | `#define DEH_DEFAULT_BFG_CELLS_PER_SHOT` |
| `DEH_DEFAULT_BLUE_ARMOR_CLASS` | macro | `progs/doomgeneric/deh_misc.h:28` | `#define DEH_DEFAULT_BLUE_ARMOR_CLASS` |
| `DEH_DEFAULT_GOD_MODE_HEALTH` | macro | `progs/doomgeneric/deh_misc.h:32` | `#define DEH_DEFAULT_GOD_MODE_HEALTH` |
| `DEH_DEFAULT_GREEN_ARMOR_CLASS` | macro | `progs/doomgeneric/deh_misc.h:27` | `#define DEH_DEFAULT_GREEN_ARMOR_CLASS` |
| `DEH_DEFAULT_IDFA_ARMOR` | macro | `progs/doomgeneric/deh_misc.h:33` | `#define DEH_DEFAULT_IDFA_ARMOR` |
| `DEH_DEFAULT_IDFA_ARMOR_CLASS` | macro | `progs/doomgeneric/deh_misc.h:34` | `#define DEH_DEFAULT_IDFA_ARMOR_CLASS` |
| `DEH_DEFAULT_IDKFA_ARMOR` | macro | `progs/doomgeneric/deh_misc.h:35` | `#define DEH_DEFAULT_IDKFA_ARMOR` |
| `DEH_DEFAULT_IDKFA_ARMOR_CLASS` | macro | `progs/doomgeneric/deh_misc.h:36` | `#define DEH_DEFAULT_IDKFA_ARMOR_CLASS` |
| `DEH_DEFAULT_INITIAL_BULLETS` | macro | `progs/doomgeneric/deh_misc.h:24` | `#define DEH_DEFAULT_INITIAL_BULLETS` |
| `DEH_DEFAULT_INITIAL_HEALTH` | macro | `progs/doomgeneric/deh_misc.h:23` | `#define DEH_DEFAULT_INITIAL_HEALTH` |
| `DEH_DEFAULT_MAX_ARMOR` | macro | `progs/doomgeneric/deh_misc.h:26` | `#define DEH_DEFAULT_MAX_ARMOR` |
| `DEH_DEFAULT_MAX_HEALTH` | macro | `progs/doomgeneric/deh_misc.h:25` | `#define DEH_DEFAULT_MAX_HEALTH` |
| `DEH_DEFAULT_MAX_SOULSPHERE` | macro | `progs/doomgeneric/deh_misc.h:29` | `#define DEH_DEFAULT_MAX_SOULSPHERE` |
| `DEH_DEFAULT_MEGASPHERE_HEALTH` | macro | `progs/doomgeneric/deh_misc.h:31` | `#define DEH_DEFAULT_MEGASPHERE_HEALTH` |
| `DEH_DEFAULT_SOULSPHERE_HEALTH` | macro | `progs/doomgeneric/deh_misc.h:30` | `#define DEH_DEFAULT_SOULSPHERE_HEALTH` |
| `DEH_DEFAULT_SPECIES_INFIGHTING` | macro | `progs/doomgeneric/deh_misc.h:38` | `#define DEH_DEFAULT_SPECIES_INFIGHTING` |
| `DEH_MISC_H` | macro | `progs/doomgeneric/deh_misc.h:19` | `#define DEH_MISC_H` |
| `deh_bfg_cells_per_shot` | variable | `progs/doomgeneric/deh_misc.h:56` | `extern int deh_bfg_cells_per_shot;` |
| `deh_bfg_cells_per_shot` | macro | `progs/doomgeneric/deh_misc.h:77` | `#define deh_bfg_cells_per_shot` |
| `deh_blue_armor_class` | variable | `progs/doomgeneric/deh_misc.h:47` | `extern int deh_blue_armor_class;` |
| `deh_blue_armor_class` | macro | `progs/doomgeneric/deh_misc.h:68` | `#define deh_blue_armor_class` |
| `deh_god_mode_health` | variable | `progs/doomgeneric/deh_misc.h:51` | `extern int deh_god_mode_health;` |
| `deh_god_mode_health` | macro | `progs/doomgeneric/deh_misc.h:72` | `#define deh_god_mode_health` |
| `deh_green_armor_class` | variable | `progs/doomgeneric/deh_misc.h:46` | `extern int deh_green_armor_class;` |
| `deh_green_armor_class` | macro | `progs/doomgeneric/deh_misc.h:67` | `#define deh_green_armor_class` |
| `deh_idfa_armor` | variable | `progs/doomgeneric/deh_misc.h:52` | `extern int deh_idfa_armor;` |
| `deh_idfa_armor` | macro | `progs/doomgeneric/deh_misc.h:73` | `#define deh_idfa_armor` |
| `deh_idfa_armor_class` | variable | `progs/doomgeneric/deh_misc.h:53` | `extern int deh_idfa_armor_class;` |
| `deh_idfa_armor_class` | macro | `progs/doomgeneric/deh_misc.h:74` | `#define deh_idfa_armor_class` |
| `deh_idkfa_armor` | variable | `progs/doomgeneric/deh_misc.h:54` | `extern int deh_idkfa_armor;` |
| `deh_idkfa_armor` | macro | `progs/doomgeneric/deh_misc.h:75` | `#define deh_idkfa_armor` |
| `deh_idkfa_armor_class` | variable | `progs/doomgeneric/deh_misc.h:55` | `extern int deh_idkfa_armor_class;` |
| `deh_idkfa_armor_class` | macro | `progs/doomgeneric/deh_misc.h:76` | `#define deh_idkfa_armor_class` |
| `deh_initial_bullets` | variable | `progs/doomgeneric/deh_misc.h:43` | `extern int deh_initial_bullets;` |
| `deh_initial_bullets` | macro | `progs/doomgeneric/deh_misc.h:64` | `#define deh_initial_bullets` |
| `deh_initial_health` | variable | `progs/doomgeneric/deh_misc.h:42` | `extern int deh_initial_health;` |
| `deh_initial_health` | macro | `progs/doomgeneric/deh_misc.h:63` | `#define deh_initial_health` |
| `deh_max_armor` | variable | `progs/doomgeneric/deh_misc.h:45` | `extern int deh_max_armor;` |
| `deh_max_armor` | macro | `progs/doomgeneric/deh_misc.h:66` | `#define deh_max_armor` |
| `deh_max_health` | variable | `progs/doomgeneric/deh_misc.h:44` | `extern int deh_max_health;` |
| `deh_max_health` | macro | `progs/doomgeneric/deh_misc.h:65` | `#define deh_max_health` |
| `deh_max_soulsphere` | variable | `progs/doomgeneric/deh_misc.h:48` | `extern int deh_max_soulsphere;` |
| `deh_max_soulsphere` | macro | `progs/doomgeneric/deh_misc.h:69` | `#define deh_max_soulsphere` |
| `deh_megasphere_health` | variable | `progs/doomgeneric/deh_misc.h:50` | `extern int deh_megasphere_health;` |
| `deh_megasphere_health` | macro | `progs/doomgeneric/deh_misc.h:71` | `#define deh_megasphere_health` |
| `deh_soulsphere_health` | variable | `progs/doomgeneric/deh_misc.h:49` | `extern int deh_soulsphere_health;` |
| `deh_soulsphere_health` | macro | `progs/doomgeneric/deh_misc.h:70` | `#define deh_soulsphere_health` |
| `deh_species_infighting` | variable | `progs/doomgeneric/deh_misc.h:57` | `extern int deh_species_infighting;` |
| `deh_species_infighting` | macro | `progs/doomgeneric/deh_misc.h:78` | `#define deh_species_infighting` |
| `DEH_AddStringReplacement` | function | `progs/doomgeneric/deh_str.h:33` | `void DEH_AddStringReplacement(char *from_text, char *to_text);` |
| `DEH_AddStringReplacement` | macro | `progs/doomgeneric/deh_str.h:42` | `#define DEH_AddStringReplacement(x, y)` |
| `DEH_STR_H` | macro | `progs/doomgeneric/deh_str.h:19` | `#define DEH_STR_H` |
| `DEH_String` | function | `progs/doomgeneric/deh_str.h:29` | `char *DEH_String(char *s);` |
| `DEH_String` | macro | `progs/doomgeneric/deh_str.h:38` | `#define DEH_String(x)` |
| `DEH_fprintf` | function | `progs/doomgeneric/deh_str.h:31` | `void DEH_fprintf(FILE *fstream, char *fmt, ...);` |
| `DEH_fprintf` | macro | `progs/doomgeneric/deh_str.h:40` | `#define DEH_fprintf` |
| `DEH_printf` | function | `progs/doomgeneric/deh_str.h:30` | `void DEH_printf(char *fmt, ...);` |
| `DEH_printf` | macro | `progs/doomgeneric/deh_str.h:39` | `#define DEH_printf` |
| `DEH_snprintf` | function | `progs/doomgeneric/deh_str.h:32` | `void DEH_snprintf(char *buffer, size_t len, char *fmt, ...);` |
| `DEH_snprintf` | macro | `progs/doomgeneric/deh_str.h:41` | `#define DEH_snprintf` |
| `D_DoomMain` | function | `progs/doomgeneric/doom.h:28` | `void D_DoomMain (void);` |
| `SRC_CHOCDOOM_DOOM_H_` | macro | `progs/doomgeneric/doom.h:10` | `#define SRC_CHOCDOOM_DOOM_H_` |
| `ML_BLOCKING` | macro | `progs/doomgeneric/doomdata.h:98` | `#define ML_BLOCKING` |
| `ML_BLOCKMONSTERS` | macro | `progs/doomgeneric/doomdata.h:101` | `#define ML_BLOCKMONSTERS` |
| `ML_DONTDRAW` | macro | `progs/doomgeneric/doomdata.h:129` | `#define ML_DONTDRAW` |
| `ML_DONTPEGBOTTOM` | macro | `progs/doomgeneric/doomdata.h:120` | `#define ML_DONTPEGBOTTOM` |
| `ML_DONTPEGTOP` | macro | `progs/doomgeneric/doomdata.h:117` | `#define ML_DONTPEGTOP` |
| `ML_MAPPED` | macro | `progs/doomgeneric/doomdata.h:132` | `#define ML_MAPPED` |
| `ML_SECRET` | macro | `progs/doomgeneric/doomdata.h:123` | `#define ML_SECRET` |
| `ML_SOUNDBLOCK` | macro | `progs/doomgeneric/doomdata.h:126` | `#define ML_SOUNDBLOCK` |
| `ML_TWOSIDED` | macro | `progs/doomgeneric/doomdata.h:105` | `#define ML_TWOSIDED` |
| `NF_SUBSECTOR` | macro | `progs/doomgeneric/doomdata.h:175` | `#define	NF_SUBSECTOR` |
| `__DOOMDATA__` | macro | `progs/doomgeneric/doomdata.h:22` | `#define __DOOMDATA__` |
| `DOOM_191_VERSION` | macro | `progs/doomgeneric/doomdef.h:37` | `#define DOOM_191_VERSION` |
| `DOOM_VERSION` | macro | `progs/doomgeneric/doomdef.h:34` | `#define DOOM_VERSION` |
| `MAXPLAYERS` | macro | `progs/doomgeneric/doomdef.h:45` | `#define MAXPLAYERS` |
| `MTF_AMBUSH` | macro | `progs/doomgeneric/doomdef.h:82` | `#define	MTF_AMBUSH` |
| `MTF_EASY` | macro | `progs/doomgeneric/doomdef.h:77` | `#define	MTF_EASY` |
| `MTF_HARD` | macro | `progs/doomgeneric/doomdef.h:79` | `#define	MTF_HARD` |
| `MTF_NORMAL` | macro | `progs/doomgeneric/doomdef.h:78` | `#define	MTF_NORMAL` |
| `RANGECHECK` | macro | `progs/doomgeneric/doomdef.h:42` | `#define RANGECHECK` |
| `__DOOMDEF__` | macro | `progs/doomgeneric/doomdef.h:21` | `#define __DOOMDEF__` |
| `DOOM_FEATURES_H` | macro | `progs/doomgeneric/doomfeatures.h:20` | `#define DOOM_FEATURES_H` |
| `FEATURE_SOUND` | macro | `progs/doomgeneric/doomfeatures.h:36` | `#define FEATURE_SOUND` |
| `dg_Create` | function | `progs/doomgeneric/doomgeneric.c:6` | `void dg_Create()` |
| `DG_DrawFrame` | function | `progs/doomgeneric/doomgeneric.h:15` | `void DG_DrawFrame();` |
| `DG_GetKey` | function | `progs/doomgeneric/doomgeneric.h:18` | `int DG_GetKey(int* pressed, unsigned char* key);` |
| `DG_GetTicksMs` | function | `progs/doomgeneric/doomgeneric.h:17` | `uint32_t DG_GetTicksMs();` |
| `DG_Init` | function | `progs/doomgeneric/doomgeneric.h:14` | `void DG_Init();` |
| `DG_ScreenBuffer` | variable | `progs/doomgeneric/doomgeneric.h:11` | `extern uint32_t* DG_ScreenBuffer;` |
| `DG_SetWindowTitle` | function | `progs/doomgeneric/doomgeneric.h:19` | `void DG_SetWindowTitle(const char * title);` |
| `DG_SleepMs` | function | `progs/doomgeneric/doomgeneric.h:16` | `void DG_SleepMs(uint32_t ms);` |
| `DOOMGENERIC_RESX` | macro | `progs/doomgeneric/doomgeneric.h:7` | `#define DOOMGENERIC_RESX` |
| `DOOMGENERIC_RESY` | macro | `progs/doomgeneric/doomgeneric.h:8` | `#define DOOMGENERIC_RESY` |
| `DOOM_GENERIC` | macro | `progs/doomgeneric/doomgeneric.h:2` | `#define DOOM_GENERIC` |
| `DG_DrawFrame` | function | `progs/doomgeneric/doomgeneric_minios.c:243` | `void DG_DrawFrame(void)` |
| `DG_GetKey` | function | `progs/doomgeneric/doomgeneric_minios.c:284` | `int DG_GetKey(int *pressed, unsigned char *key)` |
| `DG_GetTicksMs` | function | `progs/doomgeneric/doomgeneric_minios.c:280` | `uint32_t DG_GetTicksMs(void)` |
| `DG_Init` | function | `progs/doomgeneric/doomgeneric_minios.c:232` | `void DG_Init(void)` |
| `DG_SetWindowTitle` | function | `progs/doomgeneric/doomgeneric_minios.c:295` | `void DG_SetWindowTitle(const char *title)` |
| `DG_SleepMs` | function | `progs/doomgeneric/doomgeneric_minios.c:274` | `void DG_SleepMs(uint32_t ms)` |
| `FB_ADDR` | macro | `progs/doomgeneric/doomgeneric_minios.c:96` | `#define FB_ADDR` |
| `FB_HEIGHT` | macro | `progs/doomgeneric/doomgeneric_minios.c:98` | `#define FB_HEIGHT` |
| `FB_WIDTH` | macro | `progs/doomgeneric/doomgeneric_minios.c:97` | `#define FB_WIDTH` |
| `I_VideoBuffer` | variable | `progs/doomgeneric/doomgeneric_minios.c:230` | `extern unsigned char *I_VideoBuffer;` |
| `KBD_QUEUE_SIZE` | macro | `progs/doomgeneric/doomgeneric_minios.c:178` | `#define KBD_QUEUE_SIZE` |
| `MINIOS_DOOM_BACKBUF_ADDR` | function | `progs/doomgeneric/doomgeneric_minios.c:4` | `* MINIOS_DOOM_BACKBUF_ADDR (minios_abi.h);` |
| `color` | struct | `progs/doomgeneric/doomgeneric_minios.c:103` | `` |
| `colors` | variable | `progs/doomgeneric/doomgeneric_minios.c:104` | `extern struct color colors[256];` |
| `kbd_enqueue` | function | `progs/doomgeneric/doomgeneric_minios.c:182` | `static void kbd_enqueue(unsigned char doom_key, int pressed)` |
| `kbd_poll` | function | `progs/doomgeneric/doomgeneric_minios.c:189` | `static void kbd_poll(void)` |
| `load_vga_palette` | function | `progs/doomgeneric/doomgeneric_minios.c:110` | `static void load_vga_palette(void)` |
| `mini_parse_autoframes` | function | `progs/doomgeneric/doomgeneric_minios.c:24` | `static void mini_parse_autoframes(int argc, char **argv)` |
| `mini_parse_windowed` | function | `progs/doomgeneric/doomgeneric_minios.c:43` | `static void mini_parse_windowed(int argc, char **argv)` |
| `myargc` | variable | `progs/doomgeneric/doomgeneric_minios.c:233` | `extern int myargc;` |
| `myargv` | variable | `progs/doomgeneric/doomgeneric_minios.c:234` | `extern char **myargv;` |
| `scancode_to_doom` | function | `progs/doomgeneric/doomgeneric_minios.c:123` | `static unsigned char scancode_to_doom(unsigned char raw)` |
| `sys_doom_frame` | function | `progs/doomgeneric/doomgeneric_minios.c:86` | `static long sys_doom_frame(void)` |
| `sys_gfx_zoom` | function | `progs/doomgeneric/doomgeneric_minios.c:81` | `static long sys_gfx_zoom(long mode)` |
| `sys_kbd` | function | `progs/doomgeneric/doomgeneric_minios.c:61` | `static long sys_kbd(void)` |
| `sys_kbd_raw` | function | `progs/doomgeneric/doomgeneric_minios.c:71` | `static long sys_kbd_raw(int on)` |
| `sys_palette` | function | `progs/doomgeneric/doomgeneric_minios.c:66` | `static long sys_palette(const unsigned char *pal)` |
| `sys_time_ms` | function | `progs/doomgeneric/doomgeneric_minios.c:56` | `static long sys_time_ms(void)` |
| `sys_vga_mode` | function | `progs/doomgeneric/doomgeneric_minios.c:76` | `static long sys_vga_mode(int on)` |
| `DG_DrawFrame` | function | `progs/doomgeneric/doomgeneric_sdl.c:112` | `void DG_DrawFrame()` |
| `DG_GetKey` | function | `progs/doomgeneric/doomgeneric_sdl.c:133` | `int DG_GetKey(int* pressed, unsigned char* doomKey)` |
| `DG_GetTicksMs` | function | `progs/doomgeneric/doomgeneric_sdl.c:128` | `uint32_t DG_GetTicksMs()` |
| `DG_Init` | function | `progs/doomgeneric/doomgeneric_sdl.c:93` | `void DG_Init()` |
| `DG_SetWindowTitle` | function | `progs/doomgeneric/doomgeneric_sdl.c:152` | `void DG_SetWindowTitle(const char * title)` |
| `DG_SleepMs` | function | `progs/doomgeneric/doomgeneric_sdl.c:123` | `void DG_SleepMs(uint32_t ms)` |
| `KEYQUEUE_SIZE` | macro | `progs/doomgeneric/doomgeneric_sdl.c:17` | `#define KEYQUEUE_SIZE` |
| `addKeyToQueue` | function | `progs/doomgeneric/doomgeneric_sdl.c:63` | `static void addKeyToQueue(int pressed, unsigned int keyCode)` |
| `convertToDoomKey` | function | `progs/doomgeneric/doomgeneric_sdl.c:23` | `static unsigned char convertToDoomKey(unsigned int key)` |
| `handleKeyInput` | function | `progs/doomgeneric/doomgeneric_sdl.c:72` | `static void handleKeyInput()` |
| `DG_DrawFrame` | function | `progs/doomgeneric/doomgeneric_soso.c:214` | `void DG_DrawFrame()` |
| `DG_GetKey` | function | `progs/doomgeneric/doomgeneric_soso.c:237` | `int DG_GetKey(int* pressed, unsigned char* doomKey)` |
| `DG_GetTicksMs` | function | `progs/doomgeneric/doomgeneric_soso.c:232` | `uint32_t DG_GetTicksMs()` |
| `DG_Init` | function | `progs/doomgeneric/doomgeneric_soso.c:124` | `void DG_Init()` |
| `DG_SetWindowTitle` | function | `progs/doomgeneric/doomgeneric_soso.c:258` | `void DG_SetWindowTitle(const char * title)` |
| `DG_SleepMs` | function | `progs/doomgeneric/doomgeneric_soso.c:227` | `void DG_SleepMs(uint32_t ms)` |
| `EnFrameBuferIoctl` | enum | `progs/doomgeneric/doomgeneric_soso.c:36` | `` |
| `KEYQUEUE_SIZE` | macro | `progs/doomgeneric/doomgeneric_soso.c:24` | `#define KEYQUEUE_SIZE` |
| `addKeyToQueue` | function | `progs/doomgeneric/doomgeneric_soso.c:92` | `static void addKeyToQueue(int pressed, unsigned char keyCode)` |
| `convertToDoomKey` | function | `progs/doomgeneric/doomgeneric_soso.c:43` | `static unsigned char convertToDoomKey(unsigned char scancode)` |
| `disableRawMode` | function | `progs/doomgeneric/doomgeneric_soso.c:108` | `void disableRawMode()` |
| `enableRawMode` | function | `progs/doomgeneric/doomgeneric_soso.c:114` | `void enableRawMode()` |
| `handleKeyInput` | function | `progs/doomgeneric/doomgeneric_soso.c:186` | `static void handleKeyInput()` |
| `DG_DrawFrame` | function | `progs/doomgeneric/doomgeneric_sosox.c:187` | `void DG_DrawFrame()` |
| `DG_GetKey` | function | `progs/doomgeneric/doomgeneric_sosox.c:235` | `int DG_GetKey(int* pressed, unsigned char* doomKey)` |
| `DG_GetTicksMs` | function | `progs/doomgeneric/doomgeneric_sosox.c:230` | `uint32_t DG_GetTicksMs()` |
| `DG_Init` | function | `progs/doomgeneric/doomgeneric_sosox.c:117` | `void DG_Init()` |
| `DG_SetWindowTitle` | function | `progs/doomgeneric/doomgeneric_sosox.c:256` | `void DG_SetWindowTitle(const char * title)` |
| `DG_SleepMs` | function | `progs/doomgeneric/doomgeneric_sosox.c:225` | `void DG_SleepMs(uint32_t ms)` |
| `KEYQUEUE_SIZE` | macro | `progs/doomgeneric/doomgeneric_sosox.c:24` | `#define KEYQUEUE_SIZE` |
| `add_key_to_queue` | function | `progs/doomgeneric/doomgeneric_sosox.c:88` | `static void add_key_to_queue(int pressed, unsigned char key_code)` |
| `convert_to_doom_key` | function | `progs/doomgeneric/doomgeneric_sosox.c:39` | `static unsigned char convert_to_doom_key(unsigned char scancode)` |
| `disable_raw_mode` | function | `progs/doomgeneric/doomgeneric_sosox.c:102` | `void disable_raw_mode()` |
| `enable_raw_mode` | function | `progs/doomgeneric/doomgeneric_sosox.c:107` | `void enable_raw_mode()` |
| `handle_key_input` | function | `progs/doomgeneric/doomgeneric_sosox.c:159` | `static void handle_key_input()` |
| `DG_DrawFrame` | function | `progs/doomgeneric/doomgeneric_win.c:146` | `void DG_DrawFrame()` |
| `DG_GetKey` | function | `progs/doomgeneric/doomgeneric_win.c:172` | `int DG_GetKey(int* pressed, unsigned char* doomKey)` |
| `DG_GetTicksMs` | function | `progs/doomgeneric/doomgeneric_win.c:167` | `uint32_t DG_GetTicksMs()` |
| `DG_Init` | function | `progs/doomgeneric/doomgeneric_win.c:95` | `void DG_Init()` |
| `DG_SetWindowTitle` | function | `progs/doomgeneric/doomgeneric_win.c:193` | `void DG_SetWindowTitle(const char * title)` |
| `DG_SleepMs` | function | `progs/doomgeneric/doomgeneric_win.c:162` | `void DG_SleepMs(uint32_t ms)` |
| `KEYQUEUE_SIZE` | macro | `progs/doomgeneric/doomgeneric_win.c:14` | `#define KEYQUEUE_SIZE` |
| `addKeyToQueue` | function | `progs/doomgeneric/doomgeneric_win.c:59` | `static void addKeyToQueue(int pressed, unsigned char keyCode)` |
| `convertToDoomKey` | function | `progs/doomgeneric/doomgeneric_win.c:20` | `static unsigned char convertToDoomKey(unsigned char key)` |
| `wndProc` | function | `progs/doomgeneric/doomgeneric_win.c:70` | `static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)` |
| `DG_DrawFrame` | function | `progs/doomgeneric/doomgeneric_xlib.c:127` | `void DG_DrawFrame()` |
| `DG_GetKey` | function | `progs/doomgeneric/doomgeneric_xlib.c:187` | `int DG_GetKey(int* pressed, unsigned char* doomKey)` |
| `DG_GetTicksMs` | function | `progs/doomgeneric/doomgeneric_xlib.c:177` | `uint32_t DG_GetTicksMs()` |
| `DG_Init` | function | `progs/doomgeneric/doomgeneric_xlib.c:79` | `void DG_Init()` |
| `DG_SetWindowTitle` | function | `progs/doomgeneric/doomgeneric_xlib.c:208` | `void DG_SetWindowTitle(const char * title)` |
| `DG_SleepMs` | function | `progs/doomgeneric/doomgeneric_xlib.c:172` | `void DG_SleepMs(uint32_t ms)` |
| `KEYQUEUE_SIZE` | macro | `progs/doomgeneric/doomgeneric_xlib.c:21` | `#define KEYQUEUE_SIZE` |
| `addKeyToQueue` | function | `progs/doomgeneric/doomgeneric_xlib.c:68` | `static void addKeyToQueue(int pressed, unsigned int keyCode)` |
| `convertToDoomKey` | function | `progs/doomgeneric/doomgeneric_xlib.c:27` | `static unsigned char convertToDoomKey(unsigned int key)` |
| `KEYP_0` | macro | `progs/doomgeneric/doomkeys.h:77` | `#define KEYP_0` |
| `KEYP_1` | macro | `progs/doomgeneric/doomkeys.h:78` | `#define KEYP_1` |
| `KEYP_2` | macro | `progs/doomgeneric/doomkeys.h:79` | `#define KEYP_2` |
| `KEYP_3` | macro | `progs/doomgeneric/doomkeys.h:80` | `#define KEYP_3` |
| `KEYP_4` | macro | `progs/doomgeneric/doomkeys.h:81` | `#define KEYP_4` |
| `KEYP_5` | macro | `progs/doomgeneric/doomkeys.h:82` | `#define KEYP_5` |
| `KEYP_6` | macro | `progs/doomgeneric/doomkeys.h:83` | `#define KEYP_6` |
| `KEYP_7` | macro | `progs/doomgeneric/doomkeys.h:84` | `#define KEYP_7` |
| `KEYP_8` | macro | `progs/doomgeneric/doomkeys.h:85` | `#define KEYP_8` |
| `KEYP_9` | macro | `progs/doomgeneric/doomkeys.h:86` | `#define KEYP_9` |
| `KEYP_DIVIDE` | macro | `progs/doomgeneric/doomkeys.h:88` | `#define KEYP_DIVIDE` |
| `KEYP_ENTER` | macro | `progs/doomgeneric/doomkeys.h:94` | `#define KEYP_ENTER` |
| `KEYP_EQUALS` | macro | `progs/doomgeneric/doomkeys.h:93` | `#define KEYP_EQUALS` |
| `KEYP_MINUS` | macro | `progs/doomgeneric/doomkeys.h:90` | `#define KEYP_MINUS` |
| `KEYP_MULTIPLY` | macro | `progs/doomgeneric/doomkeys.h:91` | `#define KEYP_MULTIPLY` |
| `KEYP_PERIOD` | macro | `progs/doomgeneric/doomkeys.h:92` | `#define KEYP_PERIOD` |
| `KEYP_PLUS` | macro | `progs/doomgeneric/doomkeys.h:89` | `#define KEYP_PLUS` |
| `KEY_BACKSPACE` | macro | `progs/doomgeneric/doomkeys.h:51` | `#define KEY_BACKSPACE` |
| `KEY_CAPSLOCK` | macro | `progs/doomgeneric/doomkeys.h:65` | `#define KEY_CAPSLOCK` |
| `KEY_DEL` | macro | `progs/doomgeneric/doomkeys.h:75` | `#define KEY_DEL` |
| `KEY_DOWNARROW` | macro | `progs/doomgeneric/doomkeys.h:30` | `#define KEY_DOWNARROW` |
| `KEY_END` | macro | `progs/doomgeneric/doomkeys.h:71` | `#define KEY_END` |
| `KEY_ENTER` | macro | `progs/doomgeneric/doomkeys.h:36` | `#define KEY_ENTER` |
| `KEY_EQUALS` | macro | `progs/doomgeneric/doomkeys.h:54` | `#define KEY_EQUALS` |
| `KEY_ESCAPE` | macro | `progs/doomgeneric/doomkeys.h:35` | `#define KEY_ESCAPE` |
| `KEY_F1` | macro | `progs/doomgeneric/doomkeys.h:38` | `#define KEY_F1` |
| `KEY_F10` | macro | `progs/doomgeneric/doomkeys.h:47` | `#define KEY_F10` |
| `KEY_F11` | macro | `progs/doomgeneric/doomkeys.h:48` | `#define KEY_F11` |
| `KEY_F12` | macro | `progs/doomgeneric/doomkeys.h:49` | `#define KEY_F12` |
| `KEY_F2` | macro | `progs/doomgeneric/doomkeys.h:39` | `#define KEY_F2` |
| `KEY_F3` | macro | `progs/doomgeneric/doomkeys.h:40` | `#define KEY_F3` |
| `KEY_F4` | macro | `progs/doomgeneric/doomkeys.h:41` | `#define KEY_F4` |
| `KEY_F5` | macro | `progs/doomgeneric/doomkeys.h:42` | `#define KEY_F5` |
| `KEY_F6` | macro | `progs/doomgeneric/doomkeys.h:43` | `#define KEY_F6` |
| `KEY_F7` | macro | `progs/doomgeneric/doomkeys.h:44` | `#define KEY_F7` |
| `KEY_F8` | macro | `progs/doomgeneric/doomkeys.h:45` | `#define KEY_F8` |
| `KEY_F9` | macro | `progs/doomgeneric/doomkeys.h:46` | `#define KEY_F9` |
| `KEY_FIRE` | macro | `progs/doomgeneric/doomkeys.h:34` | `#define KEY_FIRE` |
| `KEY_HOME` | macro | `progs/doomgeneric/doomkeys.h:70` | `#define KEY_HOME` |
| `KEY_INS` | macro | `progs/doomgeneric/doomkeys.h:74` | `#define KEY_INS` |
| `KEY_LALT` | macro | `progs/doomgeneric/doomkeys.h:61` | `#define KEY_LALT` |
| `KEY_LEFTARROW` | macro | `progs/doomgeneric/doomkeys.h:28` | `#define KEY_LEFTARROW` |
| `KEY_MINUS` | macro | `progs/doomgeneric/doomkeys.h:55` | `#define KEY_MINUS` |
| `KEY_NUMLOCK` | macro | `progs/doomgeneric/doomkeys.h:66` | `#define KEY_NUMLOCK` |
| `KEY_PAUSE` | macro | `progs/doomgeneric/doomkeys.h:52` | `#define KEY_PAUSE` |
| `KEY_PGDN` | macro | `progs/doomgeneric/doomkeys.h:73` | `#define KEY_PGDN` |
| `KEY_PGUP` | macro | `progs/doomgeneric/doomkeys.h:72` | `#define KEY_PGUP` |
| `KEY_PRTSCR` | macro | `progs/doomgeneric/doomkeys.h:68` | `#define KEY_PRTSCR` |
| `KEY_RALT` | macro | `progs/doomgeneric/doomkeys.h:59` | `#define KEY_RALT` |
| `KEY_RCTRL` | macro | `progs/doomgeneric/doomkeys.h:58` | `#define KEY_RCTRL` |
| `KEY_RIGHTARROW` | macro | `progs/doomgeneric/doomkeys.h:27` | `#define KEY_RIGHTARROW` |
| `KEY_RSHIFT` | macro | `progs/doomgeneric/doomkeys.h:57` | `#define KEY_RSHIFT` |
| `KEY_SCRLCK` | macro | `progs/doomgeneric/doomkeys.h:67` | `#define KEY_SCRLCK` |
| `KEY_STRAFE_L` | macro | `progs/doomgeneric/doomkeys.h:31` | `#define KEY_STRAFE_L` |
| `KEY_STRAFE_R` | macro | `progs/doomgeneric/doomkeys.h:32` | `#define KEY_STRAFE_R` |
| `KEY_TAB` | macro | `progs/doomgeneric/doomkeys.h:37` | `#define KEY_TAB` |
| `KEY_UPARROW` | macro | `progs/doomgeneric/doomkeys.h:29` | `#define KEY_UPARROW` |
| `KEY_USE` | macro | `progs/doomgeneric/doomkeys.h:33` | `#define KEY_USE` |
| `__DOOMKEYS__` | macro | `progs/doomgeneric/doomkeys.h:20` | `#define __DOOMKEYS__` |
| `MAX_DM_STARTS` | macro | `progs/doomgeneric/doomstat.h:227` | `#define MAX_DM_STARTS` |
| `__D_STATE__` | macro | `progs/doomgeneric/doomstat.h:26` | `#define __D_STATE__` |
| `automapactive` | variable | `progs/doomgeneric/doomstat.h:143` | `extern boolean automapactive;` |
| `autostart` | variable | `progs/doomgeneric/doomstat.h:91` | `extern boolean autostart;` |
| `basedefault` | variable | `progs/doomgeneric/doomstat.h:250` | `extern char basedefault[1024];` |
| `bfgedition` | variable | `progs/doomgeneric/doomstat.h:62` | `extern boolean bfgedition;` |
| `bodyqueslot` | variable | `progs/doomgeneric/doomstat.h:262` | `extern int bodyqueslot;` |
| `consoleplayer` | variable | `progs/doomgeneric/doomstat.h:164` | `extern int consoleplayer;` |
| `deathmatch` | variable | `progs/doomgeneric/doomstat.h:108` | `extern int deathmatch;` |
| `deathmatch_p` | variable | `progs/doomgeneric/doomstat.h:229` | `extern mapthing_t* deathmatch_p;` |
| `deathmatchstarts` | variable | `progs/doomgeneric/doomstat.h:228` | `extern mapthing_t deathmatchstarts[MAX_DM_STARTS];` |
| `demoplayback` | variable | `progs/doomgeneric/doomstat.h:189` | `extern boolean demoplayback;` |
| `demorecording` | variable | `progs/doomgeneric/doomstat.h:190` | `extern boolean demorecording;` |
| `devparm` | variable | `progs/doomgeneric/doomstat.h:50` | `extern boolean devparm;` |
| `displayplayer` | variable | `progs/doomgeneric/doomstat.h:165` | `extern int displayplayer;` |
| `fastparm` | variable | `progs/doomgeneric/doomstat.h:48` | `extern boolean fastparm;` |
| `gamedescription` | variable | `progs/doomgeneric/doomstat.h:59` | `extern char *gamedescription;` |
| `gameepisode` | variable | `progs/doomgeneric/doomstat.h:95` | `extern int gameepisode;` |
| `gamemap` | variable | `progs/doomgeneric/doomstat.h:96` | `extern int gamemap;` |
| `gamemission` | variable | `progs/doomgeneric/doomstat.h:57` | `extern GameMission_t gamemission;` |
| `gamemode` | variable | `progs/doomgeneric/doomstat.h:56` | `extern GameMode_t gamemode;` |
| `gameskill` | variable | `progs/doomgeneric/doomstat.h:94` | `extern skill_t gameskill;` |
| `gamestate` | variable | `progs/doomgeneric/doomstat.h:204` | `extern gamestate_t gamestate;` |
| `gameversion` | variable | `progs/doomgeneric/doomstat.h:58` | `extern GameVersion_t gameversion;` |
| `levelstarttic` | variable | `progs/doomgeneric/doomstat.h:177` | `extern int levelstarttic;` |
| `leveltime` | variable | `progs/doomgeneric/doomstat.h:178` | `extern int leveltime;` |
| `logical_gamemission` | macro | `progs/doomgeneric/doomstat.h:69` | `#define logical_gamemission` |
| `lowres_turn` | variable | `progs/doomgeneric/doomstat.h:195` | `extern boolean lowres_turn;` |
| `menuactive` | variable | `progs/doomgeneric/doomstat.h:144` | `extern boolean menuactive;` |
| `modifiedgame` | variable | `progs/doomgeneric/doomstat.h:74` | `extern boolean modifiedgame;` |
| `mouseSensitivity` | variable | `progs/doomgeneric/doomstat.h:260` | `extern int mouseSensitivity;` |
| `musicVolume` | variable | `progs/doomgeneric/doomstat.h:121` | `extern int musicVolume;` |
| `netcmds` | variable | `progs/doomgeneric/doomstat.h:278` | `extern ticcmd_t *netcmds;` |
| `netgame` | variable | `progs/doomgeneric/doomstat.h:105` | `extern boolean netgame;` |
| `nodrawers` | variable | `progs/doomgeneric/doomstat.h:150` | `extern boolean nodrawers;` |
| `nomonsters` | variable | `progs/doomgeneric/doomstat.h:46` | `extern boolean nomonsters;` |
| `paused` | variable | `progs/doomgeneric/doomstat.h:145` | `extern boolean paused;` |
| `playeringame` | variable | `progs/doomgeneric/doomstat.h:223` | `extern boolean playeringame[MAXPLAYERS];` |
| `players` | variable | `progs/doomgeneric/doomstat.h:220` | `extern player_t players[MAXPLAYERS];` |
| `playerstarts` | variable | `progs/doomgeneric/doomstat.h:232` | `extern mapthing_t playerstarts[MAXPLAYERS];` |
| `precache` | variable | `progs/doomgeneric/doomstat.h:253` | `extern boolean precache;` |
| `respawnmonsters` | variable | `progs/doomgeneric/doomstat.h:102` | `extern boolean respawnmonsters;` |
| `respawnparm` | variable | `progs/doomgeneric/doomstat.h:47` | `extern boolean respawnparm;` |
| `rndindex` | variable | `progs/doomgeneric/doomstat.h:276` | `extern int rndindex;` |
| `savegamedir` | variable | `progs/doomgeneric/doomstat.h:249` | `extern char * savegamedir;` |
| `sfxVolume` | variable | `progs/doomgeneric/doomstat.h:120` | `extern int sfxVolume;` |
| `singledemo` | variable | `progs/doomgeneric/doomstat.h:198` | `extern boolean singledemo;` |
| `skyflatnum` | variable | `progs/doomgeneric/doomstat.h:269` | `extern int skyflatnum;` |
| `snd_DesiredMusicDevice` | variable | `progs/doomgeneric/doomstat.h:130` | `extern int snd_DesiredMusicDevice;` |
| `snd_DesiredSfxDevice` | variable | `progs/doomgeneric/doomstat.h:131` | `extern int snd_DesiredSfxDevice;` |
| `snd_MusicDevice` | variable | `progs/doomgeneric/doomstat.h:127` | `extern int snd_MusicDevice;` |
| `snd_SfxDevice` | variable | `progs/doomgeneric/doomstat.h:128` | `extern int snd_SfxDevice;` |
| `startepisode` | variable | `progs/doomgeneric/doomstat.h:83` | `extern int startepisode;` |
| `startloadgame` | variable | `progs/doomgeneric/doomstat.h:89` | `extern int startloadgame;` |
| `startmap` | variable | `progs/doomgeneric/doomstat.h:84` | `extern int startmap;` |
| `startskill` | variable | `progs/doomgeneric/doomstat.h:82` | `extern skill_t startskill;` |
| `statusbaractive` | variable | `progs/doomgeneric/doomstat.h:141` | `extern boolean statusbaractive;` |
| `testcontrols` | variable | `progs/doomgeneric/doomstat.h:153` | `extern boolean testcontrols;` |
| `testcontrols_mousespeed` | variable | `progs/doomgeneric/doomstat.h:154` | `extern int testcontrols_mousespeed;` |
| `timelimit` | variable | `progs/doomgeneric/doomstat.h:99` | `extern int timelimit;` |
| `totalitems` | variable | `progs/doomgeneric/doomstat.h:173` | `extern int totalitems;` |
| `totalkills` | variable | `progs/doomgeneric/doomstat.h:172` | `extern int totalkills;` |
| `totalsecret` | variable | `progs/doomgeneric/doomstat.h:174` | `extern int totalsecret;` |
| `usergame` | variable | `progs/doomgeneric/doomstat.h:186` | `extern boolean usergame;` |
| `viewactive` | variable | `progs/doomgeneric/doomstat.h:148` | `extern boolean viewactive;` |
| `viewangleoffset` | variable | `progs/doomgeneric/doomstat.h:161` | `extern int viewangleoffset;` |
| `wipegamestate` | variable | `progs/doomgeneric/doomstat.h:258` | `extern gamestate_t wipegamestate;` |
| `wminfo` | variable | `progs/doomgeneric/doomstat.h:236` | `extern wbstartstruct_t wminfo;` |
| `DIR_SEPARATOR` | macro | `progs/doomgeneric/doomtype.h:88` | `#define DIR_SEPARATOR` |
| `DIR_SEPARATOR` | macro | `progs/doomgeneric/doomtype.h:94` | `#define DIR_SEPARATOR` |
| `DIR_SEPARATOR_S` | macro | `progs/doomgeneric/doomtype.h:89` | `#define DIR_SEPARATOR_S` |
| `DIR_SEPARATOR_S` | macro | `progs/doomgeneric/doomtype.h:95` | `#define DIR_SEPARATOR_S` |
| `PACKEDATTR` | macro | `progs/doomgeneric/doomtype.h:50` | `#define PACKEDATTR` |
| `PACKEDATTR` | macro | `progs/doomgeneric/doomtype.h:52` | `#define PACKEDATTR` |
| `PATH_SEPARATOR` | macro | `progs/doomgeneric/doomtype.h:90` | `#define PATH_SEPARATOR` |
| `PATH_SEPARATOR` | macro | `progs/doomgeneric/doomtype.h:96` | `#define PATH_SEPARATOR` |
| `__DOOMTYPE__` | macro | `progs/doomgeneric/doomtype.h:22` | `#define __DOOMTYPE__` |
| `arrlen` | macro | `progs/doomgeneric/doomtype.h:100` | `#define arrlen(array)` |
| `boolean` | type_alias | `progs/doomgeneric/doomtype.h:68` | `typedef bool boolean;` |
| `byte` | type_alias | `progs/doomgeneric/doomtype.h:81` | `typedef uint8_t byte;` |
| `strcasecmp` | macro | `progs/doomgeneric/doomtype.h:30` | `#define strcasecmp` |
| `strncasecmp` | macro | `progs/doomgeneric/doomtype.h:31` | `#define strncasecmp` |
| `NUM_QUITMESSAGES` | macro | `progs/doomgeneric/dstrings.h:35` | `#define NUM_QUITMESSAGES` |
| `SAVEGAMENAME` | macro | `progs/doomgeneric/dstrings.h:30` | `#define SAVEGAMENAME` |
| `__DSTRINGS__` | macro | `progs/doomgeneric/dstrings.h:22` | `#define __DSTRINGS__` |
| `doom1_endmsg` | variable | `progs/doomgeneric/dstrings.h:37` | `extern char *doom1_endmsg[];` |
| `doom2_endmsg` | variable | `progs/doomgeneric/dstrings.h:38` | `extern char *doom2_endmsg[];` |
| `I_InitTimidityConfig` | function | `progs/doomgeneric/dummy.c:43` | `void I_InitTimidityConfig(void)` |
| `F_ArtScreenDrawer` | function | `progs/doomgeneric/f_finale.c:661` | `static void F_ArtScreenDrawer(void)` |
| `F_BunnyScroll` | function | `progs/doomgeneric/f_finale.c:606` | `void F_BunnyScroll (void)` |
| `F_CastDrawer` | function | `progs/doomgeneric/f_finale.c:541` | `void F_CastDrawer (void)` |
| `F_CastPrint` | function | `progs/doomgeneric/f_finale.c:486` | `void F_CastPrint (char* text)` |
| `F_CastResponder` | function | `progs/doomgeneric/f_finale.c:465` | `boolean F_CastResponder (event_t* ev)` |
| `F_CastTicker` | function | `progs/doomgeneric/f_finale.c:358` | `void F_CastTicker (void)` |
| `F_DrawPatchCol` | function | `progs/doomgeneric/f_finale.c:572` | `void F_DrawPatchCol ( int		x,   patch_t*	patch,   int		col )` |
| `F_Drawer` | function | `progs/doomgeneric/f_finale.c:702` | `void F_Drawer (void)` |
| `F_Responder` | function | `progs/doomgeneric/f_finale.c:160` | `boolean F_Responder (event_t *event)` |
| `F_StartCast` | function | `progs/doomgeneric/f_finale.c:340` | `void F_StartCast (void)` |
| `F_StartFinale` | function | `progs/doomgeneric/f_finale.c:108` | `void F_StartFinale (void)` |
| `F_TextWrite` | function | `progs/doomgeneric/f_finale.c:227` | `void F_TextWrite (void)` |
| `F_Ticker` | function | `progs/doomgeneric/f_finale.c:172` | `void F_Ticker (void)` |
| `TEXTSPEED` | macro | `progs/doomgeneric/f_finale.c:57` | `#define	TEXTSPEED` |
| `TEXTWAIT` | macro | `progs/doomgeneric/f_finale.c:58` | `#define	TEXTWAIT` |
| `castinfo_t` | struct | `progs/doomgeneric/f_finale.c:300` | `` |
| `hu_font` | variable | `progs/doomgeneric/f_finale.c:224` | `extern patch_t *hu_font[HU_FONTSIZE];` |
| `textscreen_t` | struct | `progs/doomgeneric/f_finale.c:60` | `` |
| `F_Drawer` | function | `progs/doomgeneric/f_finale.h:37` | `void F_Drawer (void);` |
| `F_StartFinale` | function | `progs/doomgeneric/f_finale.h:40` | `void F_StartFinale (void);` |
| `F_Ticker` | function | `progs/doomgeneric/f_finale.h:34` | `void F_Ticker (void);` |
| `__F_FINALE__` | macro | `progs/doomgeneric/f_finale.h:21` | `#define __F_FINALE__` |
| `wipe_EndScreen` | function | `progs/doomgeneric/f_wipe.c:243` | `int wipe_EndScreen ( int	x,   int	y,   int	width,   int	height )` |
| `wipe_ScreenWipe` | function | `progs/doomgeneric/f_wipe.c:256` | `int wipe_ScreenWipe ( int	wipeno,   int	x,   int	y,   int	width,   int	height,   int	ticks )` |
| `wipe_StartScreen` | function | `progs/doomgeneric/f_wipe.c:231` | `int wipe_StartScreen ( int	x,   int	y,   int	width,   int	height )` |
| `wipe_doColorXForm` | function | `progs/doomgeneric/f_wipe.c:75` | `int wipe_doColorXForm ( int	width,   int	height,   int	ticks )` |
| `wipe_doMelt` | function | `progs/doomgeneric/f_wipe.c:164` | `int wipe_doMelt ( int	width,   int	height,   int	ticks )` |
| `wipe_exitColorXForm` | function | `progs/doomgeneric/f_wipe.c:121` | `int wipe_exitColorXForm ( int	width,   int	height,   int	ticks )` |
| `wipe_exitMelt` | function | `progs/doomgeneric/f_wipe.c:219` | `int wipe_exitMelt ( int	width,   int	height,   int	ticks )` |
| `wipe_initColorXForm` | function | `progs/doomgeneric/f_wipe.c:65` | `int wipe_initColorXForm ( int	width,   int	height,   int	ticks )` |
| `wipe_initMelt` | function | `progs/doomgeneric/f_wipe.c:133` | `int wipe_initMelt ( int	width,   int	height,   int	ticks )` |
| `wipe_shittyColMajorXform` | function | `progs/doomgeneric/f_wipe.c:43` | `void wipe_shittyColMajorXform ( short*	array,   int		width,   int		height )` |
| `__F_WIPE_H__` | macro | `progs/doomgeneric/f_wipe.h:21` | `#define __F_WIPE_H__` |
| `wipe_EndScreen` | function | `progs/doomgeneric/f_wipe.h:47` | `int wipe_EndScreen ( int x, int y, int width, int height );` |
| `wipe_ScreenWipe` | function | `progs/doomgeneric/f_wipe.h:55` | `int wipe_ScreenWipe ( int wipeno, int x, int y, int width, int height, int ticks );` |
| `wipe_StartScreen` | function | `progs/doomgeneric/f_wipe.h:39` | `int wipe_StartScreen ( int x, int y, int width, int height );` |
| `BODYQUESIZE` | macro | `progs/doomgeneric/g_game.c:225` | `#define	BODYQUESIZE` |
| `DEMOMARKER` | macro | `progs/doomgeneric/g_game.c:1895` | `#define DEMOMARKER` |
| `DemoVersionDescription` | function | `progs/doomgeneric/g_game.c:2115` | `static char *DemoVersionDescription(int version)` |
| `G_BeginRecording` | function | `progs/doomgeneric/g_game.c:2058` | `void G_BeginRecording (void)` |
| `G_BuildTiccmd` | function | `progs/doomgeneric/g_game.c:322` | `void G_BuildTiccmd (ticcmd_t* cmd, int maketic)` |
| `G_CheckDemoStatus` | function | `progs/doomgeneric/g_game.c:2243` | `boolean G_CheckDemoStatus (void)` |
| `G_CheckSpot` | function | `progs/doomgeneric/g_game.c:1116` | `boolean G_CheckSpot ( int		playernum,   mapthing_t*	mthing )` |
| `G_CmdChecksum` | function | `progs/doomgeneric/g_game.c:233` | `int G_CmdChecksum (ticcmd_t* cmd)` |
| `G_DeathMatchSpawnPlayer` | function | `progs/doomgeneric/g_game.c:1223` | `void G_DeathMatchSpawnPlayer (int playernum)` |
| `G_DeferedInitNew` | function | `progs/doomgeneric/g_game.c:1698` | `void G_DeferedInitNew ( skill_t	skill,   int		episode,   int		map)` |
| `G_DeferedPlayDemo` | function | `progs/doomgeneric/g_game.c:2107` | `void G_DeferedPlayDemo (char* name)` |
| `G_DoCompleted` | function | `progs/doomgeneric/g_game.c:1346` | `void G_DoCompleted (void)` |
| `G_DoLoadGame` | function | `progs/doomgeneric/g_game.c:1548` | `void G_DoLoadGame (void)` |
| `G_DoLoadLevel` | function | `progs/doomgeneric/g_game.c:603` | `void G_DoLoadLevel (void)` |
| `G_DoNewGame` | function | `progs/doomgeneric/g_game.c:1710` | `void G_DoNewGame (void)` |
| `G_DoPlayDemo` | function | `progs/doomgeneric/g_game.c:2152` | `void G_DoPlayDemo (void)` |
| `G_DoReborn` | function | `progs/doomgeneric/g_game.c:1250` | `void G_DoReborn (int playernum)` |
| `G_DoSaveGame` | function | `progs/doomgeneric/g_game.c:1610` | `void G_DoSaveGame (void)` |
| `G_DoVictory` | function | `progs/doomgeneric/g_game.c:88` | `void G_DoVictory (void);` |
| `G_DoWorldDone` | function | `progs/doomgeneric/g_game.c:1519` | `void G_DoWorldDone (void)` |
| `G_ExitLevel` | function | `progs/doomgeneric/g_game.c:1328` | `void G_ExitLevel (void)` |
| `G_InitNew` | function | `progs/doomgeneric/g_game.c:1727` | `void G_InitNew ( skill_t	skill,   int		episode,   int		map )` |
| `G_InitPlayer` | function | `progs/doomgeneric/g_game.c:1039` | `void G_InitPlayer (int player)` |
| `G_LoadGame` | function | `progs/doomgeneric/g_game.c:1539` | `void G_LoadGame (char* name)` |
| `G_NextWeapon` | function | `progs/doomgeneric/g_game.c:281` | `static int G_NextWeapon(int direction)` |
| `G_PlayerFinishLevel` | function | `progs/doomgeneric/g_game.c:1051` | `void G_PlayerFinishLevel (int player)` |
| `G_PlayerReborn` | function | `progs/doomgeneric/g_game.c:1072` | `void G_PlayerReborn (int player)` |
| `G_ReadDemoTiccmd` | function | `progs/doomgeneric/g_game.c:1898` | `void G_ReadDemoTiccmd (ticcmd_t* cmd)` |

Next: [SYMBOLS_p14.md](SYMBOLS_p14.md)
