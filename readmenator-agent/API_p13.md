# API (page 13 of 21)
Previous: [API_p12.md](API_p12.md)

## progs/doomgeneric/m_menu.c
Depends on: `progs/doomgeneric/d_main.h`, `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/dstrings.h`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/hu_stuff.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/i_timer.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_controls.h`, `progs/doomgeneric/m_menu.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/p_saveg.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`
- `M_StartGame` (function) `progs/doomgeneric/m_menu.c:193` `void M_StartGame(int choice);`
- `M_ReadSaveStrings` (function) `progs/doomgeneric/m_menu.c:503` `void M_ReadSaveStrings(void)` -- M_ReadSaveStrings read the strings from the savegame files
- `M_DrawLoad` (function) `progs/doomgeneric/m_menu.c:530` `void M_DrawLoad(void)` -- M_LoadGame & Cie.
- `M_DrawSaveLoadBorder` (function) `progs/doomgeneric/m_menu.c:549` `void M_DrawSaveLoadBorder(int x,int y)` -- Draw border for the savegame description
- `M_LoadSelect` (function) `progs/doomgeneric/m_menu.c:572` `void M_LoadSelect(int choice)` -- User wants to load this game
- `M_LoadGame` (function) `progs/doomgeneric/m_menu.c:585` `void M_LoadGame (int choice)` -- Selected from DOOM menu
- `M_DrawSave` (function) `progs/doomgeneric/m_menu.c:601` `void M_DrawSave(void)` -- M_SaveGame & Cie.
- `M_DoSave` (function) `progs/doomgeneric/m_menu.c:622` `void M_DoSave(int slot)` -- M_Responder calls this when user is finished
- `M_SaveSelect` (function) `progs/doomgeneric/m_menu.c:635` `void M_SaveSelect(int choice)` -- User wants to save.
- `M_SaveGame` (function) `progs/doomgeneric/m_menu.c:650` `void M_SaveGame (int choice)` -- Selected from DOOM menu
- `M_QuickSaveResponse` (function) `progs/doomgeneric/m_menu.c:672` `void M_QuickSaveResponse(int key)`
- `M_QuickSave` (function) `progs/doomgeneric/m_menu.c:681` `void M_QuickSave(void)`
- `M_QuickLoadResponse` (function) `progs/doomgeneric/m_menu.c:709` `void M_QuickLoadResponse(int key)` -- M_QuickLoad
- `M_QuickLoad` (function) `progs/doomgeneric/m_menu.c:719` `void M_QuickLoad(void)`
- `M_DrawReadThis1` (function) `progs/doomgeneric/m_menu.c:743` `void M_DrawReadThis1(void)` -- Read This Menus Had a "quick hack to fix romero bug"
- `M_DrawReadThis2` (function) `progs/doomgeneric/m_menu.c:820` `void M_DrawReadThis2(void)` -- Read This Menus - optional second page.
- `M_DrawSound` (function) `progs/doomgeneric/m_menu.c:834` `void M_DrawSound(void)` -- Change Sfx & Music volumes
- `M_Sound` (function) `progs/doomgeneric/m_menu.c:845` `void M_Sound(int choice)`
- `M_SfxVol` (function) `progs/doomgeneric/m_menu.c:850` `void M_SfxVol(int choice)`
- `M_MusicVol` (function) `progs/doomgeneric/m_menu.c:867` `void M_MusicVol(int choice)`
- `M_DrawMainMenu` (function) `progs/doomgeneric/m_menu.c:890` `void M_DrawMainMenu(void)` -- M_DrawMainMenu
- `M_DrawNewGame` (function) `progs/doomgeneric/m_menu.c:902` `void M_DrawNewGame(void)` -- M_NewGame
- `M_NewGame` (function) `progs/doomgeneric/m_menu.c:908` `void M_NewGame(int choice)`
- `M_DrawEpisode` (function) `progs/doomgeneric/m_menu.c:930` `void M_DrawEpisode(void)`
- `M_VerifyNightmare` (function) `progs/doomgeneric/m_menu.c:935` `void M_VerifyNightmare(int key)`
- `M_ChooseSkill` (function) `progs/doomgeneric/m_menu.c:944` `void M_ChooseSkill(int choice)`
- `M_Episode` (function) `progs/doomgeneric/m_menu.c:956` `void M_Episode(int choice)`
- `M_DrawOptions` (function) `progs/doomgeneric/m_menu.c:987` `void M_DrawOptions(void)`
- `M_Options` (function) `progs/doomgeneric/m_menu.c:1007` `void M_Options(int choice)`
- `M_ChangeMessages` (function) `progs/doomgeneric/m_menu.c:1017` `void M_ChangeMessages(int choice)` -- Toggle messages on/off
- `M_EndGameResponse` (function) `progs/doomgeneric/m_menu.c:1035` `void M_EndGameResponse(int key)` -- M_EndGame
- `M_EndGame` (function) `progs/doomgeneric/m_menu.c:1045` `void M_EndGame(int choice)`
- `M_ReadThis` (function) `progs/doomgeneric/m_menu.c:1069` `void M_ReadThis(int choice)` -- M_ReadThis
- `M_ReadThis2` (function) `progs/doomgeneric/m_menu.c:1075` `void M_ReadThis2(int choice)`
- `M_FinishReadThis` (function) `progs/doomgeneric/m_menu.c:1093` `void M_FinishReadThis(int choice)`
- `M_QuitResponse` (function) `progs/doomgeneric/m_menu.c:1131` `void M_QuitResponse(int key)`
- `M_SelectEndMessage` (function) `progs/doomgeneric/m_menu.c:1147` `static char *M_SelectEndMessage(void)`
- `M_QuitDOOM` (function) `progs/doomgeneric/m_menu.c:1168` `void M_QuitDOOM(int choice)`
- `M_ChangeSensitivity` (function) `progs/doomgeneric/m_menu.c:1179` `void M_ChangeSensitivity(int choice)`
- `M_ChangeDetail` (function) `progs/doomgeneric/m_menu.c:1197` `void M_ChangeDetail(int choice)`
- `M_SizeDisplay` (function) `progs/doomgeneric/m_menu.c:1213` `void M_SizeDisplay(int choice)`
- `M_DrawThermo` (function) `progs/doomgeneric/m_menu.c:1244` `void
M_DrawThermo
( int	x,
  int	y,
  int	thermWidth,
  int	thermDot )`
- `M_DrawEmptyCell` (function) `progs/doomgeneric/m_menu.c:1270` `void
M_DrawEmptyCell
( menu_t*	menu,
  int		item )`
- `M_DrawSelCell` (function) `progs/doomgeneric/m_menu.c:1279` `void
M_DrawSelCell
( menu_t*	menu,
  int		item )`
- `M_StartMessage` (function) `progs/doomgeneric/m_menu.c:1289` `void
M_StartMessage
( char*		string,
  void*		routine,
  boolean	input )`
- `M_StopMessage` (function) `progs/doomgeneric/m_menu.c:1304` `void M_StopMessage(void)`
- `M_StringWidth` (function) `progs/doomgeneric/m_menu.c:1315` `int M_StringWidth(char* string)` -- Find string width from hu_font chars
- `M_StringHeight` (function) `progs/doomgeneric/m_menu.c:1338` `int M_StringHeight(char* string)` -- Find string height from hu_font chars
- `M_WriteText` (function) `progs/doomgeneric/m_menu.c:1357` `void
M_WriteText
( int		x,
  int		y,
  char*		string)`
- `IsNullKey` (function) `progs/doomgeneric/m_menu.c:1403` `static boolean IsNullKey(int key)`
- `M_Responder` (function) `progs/doomgeneric/m_menu.c:1416` `boolean M_Responder (event_t* ev)` -- M_Responder
- `M_StartControlPanel` (function) `progs/doomgeneric/m_menu.c:1899` `void M_StartControlPanel (void)` -- M_StartControlPanel
- `M_DrawOPLDev` (function) `progs/doomgeneric/m_menu.c:1913` `static void M_DrawOPLDev(void)`
- `I_OPL_DevMessages` (function) `progs/doomgeneric/m_menu.c:1915` `extern void I_OPL_DevMessages(char *, size_t);`
- `M_Drawer` (function) `progs/doomgeneric/m_menu.c:1951` `void M_Drawer (void)` -- M_Drawer Called after the view has been rendered, but before it has been blitted.
- `M_ClearMenus` (function) `progs/doomgeneric/m_menu.c:2041` `void M_ClearMenus (void)` -- M_ClearMenus
- `M_SetupNextMenu` (function) `progs/doomgeneric/m_menu.c:2054` `void M_SetupNextMenu(menu_t *menudef)` -- M_SetupNextMenu
- `M_Ticker` (function) `progs/doomgeneric/m_menu.c:2064` `void M_Ticker (void)` -- M_Ticker
- `M_Init` (function) `progs/doomgeneric/m_menu.c:2077` `void M_Init (void)` -- M_Init

## progs/doomgeneric/m_menu.h
Depends on: `progs/doomgeneric/d_event.h`
Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/r_main.c`
- `M_Ticker` (function) `progs/doomgeneric/m_menu.h:40` `void M_Ticker (void);` -- Called by main loop, only used for menu (skull cursor) animation.
- `M_Drawer` (function) `progs/doomgeneric/m_menu.h:44` `void M_Drawer (void);` -- Called by main loop, draws the menus directly into the screen buffer.
- `M_Init` (function) `progs/doomgeneric/m_menu.h:48` `void M_Init (void);` -- Called by D_DoomMain, loads the config file.
- `M_StartControlPanel` (function) `progs/doomgeneric/m_menu.h:52` `void M_StartControlPanel (void);` -- Called by intro code to force menu up upon a keypress, does nothing if menu is already up.

## progs/doomgeneric/m_misc.c
Depends on: `kernel/string.c`, `progs/doomgeneric/deh_str.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`
- `M_MakeDirectory` (function) `progs/doomgeneric/m_misc.c:55` `void M_MakeDirectory(char *path)`
- `M_FileExists` (function) `progs/doomgeneric/m_misc.c:66` `boolean M_FileExists(char *filename)`
- `M_FileLength` (function) `progs/doomgeneric/m_misc.c:89` `long M_FileLength(FILE *handle)`
- `M_WriteFile` (function) `progs/doomgeneric/m_misc.c:111` `boolean M_WriteFile(char *name, void *source, int length)`
- `M_ReadFile` (function) `progs/doomgeneric/m_misc.c:135` `int M_ReadFile(char *name, byte **buffer)`
- `M_TempFile` (function) `progs/doomgeneric/m_misc.c:166` `char *M_TempFile(char *s)`
- `M_StrToInt` (function) `progs/doomgeneric/m_misc.c:189` `boolean M_StrToInt(const char *str, int *result)`
- `M_ExtractFileBase` (function) `progs/doomgeneric/m_misc.c:197` `void M_ExtractFileBase(char *path, char *dest)`
- `M_ForceUppercase` (function) `progs/doomgeneric/m_misc.c:242` `void M_ForceUppercase(char *text)`
- `M_StrCaseStr` (function) `progs/doomgeneric/m_misc.c:258` `char *M_StrCaseStr(char *haystack, char *needle)`
- `M_StringDuplicate` (function) `progs/doomgeneric/m_misc.c:291` `char *M_StringDuplicate(const char *orig)`
- `M_StringReplace` (function) `progs/doomgeneric/m_misc.c:310` `char *M_StringReplace(const char *haystack, const char *needle,
                      const char ...`
- `M_StringCopy` (function) `progs/doomgeneric/m_misc.c:372` `boolean M_StringCopy(char *dest, const char *src, size_t dest_size)`
- `M_StringConcat` (function) `progs/doomgeneric/m_misc.c:393` `boolean M_StringConcat(char *dest, const char *src, size_t dest_size)`
- `M_StringStartsWith` (function) `progs/doomgeneric/m_misc.c:408` `boolean M_StringStartsWith(const char *s, const char *prefix)`
- `M_StringEndsWith` (function) `progs/doomgeneric/m_misc.c:416` `boolean M_StringEndsWith(const char *s, const char *suffix)`
- `M_StringJoin` (function) `progs/doomgeneric/m_misc.c:425` `char *M_StringJoin(const char *s, ...)`
- `M_vsnprintf` (function) `progs/doomgeneric/m_misc.c:481` `int M_vsnprintf(char *buf, size_t buf_len, const char *s, va_list args)` -- Safe, portable vsnprintf().
- `M_snprintf` (function) `progs/doomgeneric/m_misc.c:507` `int M_snprintf(char *buf, size_t buf_len, const char *s, ...)` -- Safe, portable snprintf().
- `M_OEMToUTF8` (function) `progs/doomgeneric/m_misc.c:519` `char *M_OEMToUTF8(const char *oem)`

## progs/doomgeneric/m_misc.h
Depends on: `progs/doomgeneric/doomtype.h`
Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_iwad.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_joystick.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/m_argv.c`, `progs/doomgeneric/m_config.c`, `progs/doomgeneric/m_controls.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/m_misc.c`, `progs/doomgeneric/p_map.c`, `progs/doomgeneric/p_saveg.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/r_data.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/v_video.c`, `progs/doomgeneric/w_checksum.c`, `progs/doomgeneric/w_file_stdc.c`, `progs/doomgeneric/w_wad.c`, `progs/doomgeneric/wi_stuff.c`
- `M_ReadFile` (function) `progs/doomgeneric/m_misc.h:29` `int M_ReadFile(char *name, byte **buffer);`
- `M_MakeDirectory` (function) `progs/doomgeneric/m_misc.h:30` `void M_MakeDirectory(char *dir);`
- `M_TempFile` (function) `progs/doomgeneric/m_misc.h:31` `char *M_TempFile(char *s);`
- `M_FileLength` (function) `progs/doomgeneric/m_misc.h:33` `long M_FileLength(FILE *handle);`
- `M_ExtractFileBase` (function) `progs/doomgeneric/m_misc.h:35` `void M_ExtractFileBase(char *path, char *dest);`
- `M_ForceUppercase` (function) `progs/doomgeneric/m_misc.h:36` `void M_ForceUppercase(char *text);`
- `M_StrCaseStr` (function) `progs/doomgeneric/m_misc.h:37` `char *M_StrCaseStr(char *haystack, char *needle);`
- `M_StringDuplicate` (function) `progs/doomgeneric/m_misc.h:38` `char *M_StringDuplicate(const char *orig);`
- `M_StringReplace` (function) `progs/doomgeneric/m_misc.h:41` `char *M_StringReplace(const char *haystack, const char *needle, const char *replacement);`
- `M_StringJoin` (function) `progs/doomgeneric/m_misc.h:43` `char *M_StringJoin(const char *s, ...);`
- `M_vsnprintf` (function) `progs/doomgeneric/m_misc.h:46` `int M_vsnprintf(char *buf, size_t buf_len, const char *s, va_list args);`
- `M_snprintf` (function) `progs/doomgeneric/m_misc.h:47` `int M_snprintf(char *buf, size_t buf_len, const char *s, ...);`
- `M_OEMToUTF8` (function) `progs/doomgeneric/m_misc.h:48` `char *M_OEMToUTF8(const char *ansi);`

## progs/doomgeneric/m_random.c
- `P_Random` (function) `progs/doomgeneric/m_random.c:50` `int P_Random (void)` -- Which one is deterministic?
- `M_Random` (function) `progs/doomgeneric/m_random.c:56` `int M_Random (void)`
- `M_ClearRandom` (function) `progs/doomgeneric/m_random.c:62` `void M_ClearRandom (void)`

## progs/doomgeneric/m_random.h
Depends on: `progs/doomgeneric/doomtype.h`
Imported by: `progs/doomgeneric/f_wipe.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/p_enemy.c`, `progs/doomgeneric/p_inter.c`, `progs/doomgeneric/p_lights.c`, `progs/doomgeneric/p_map.c`, `progs/doomgeneric/p_mobj.c`, `progs/doomgeneric/p_plats.c`, `progs/doomgeneric/p_pspr.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/wi_stuff.c`
- `M_Random` (function) `progs/doomgeneric/m_random.h:30` `int M_Random (void);` -- Returns a number from 0 to 255, from a lookup table.
- `P_Random` (function) `progs/doomgeneric/m_random.h:33` `int P_Random (void);` -- As M_Random, but used only by the play simulation.
- `M_ClearRandom` (function) `progs/doomgeneric/m_random.h:36` `void M_ClearRandom (void);` -- Fix randoms for demos.

## progs/doomgeneric/memio.c
Depends on: `kernel/string.c`, `progs/doomgeneric/memio.h`, `progs/doomgeneric/z_zone.h`
- `mem_fopen_read` (function) `progs/doomgeneric/memio.c:42` `MEMFILE *mem_fopen_read(void *buf, size_t buflen)`
- `mem_fread` (function) `progs/doomgeneric/memio.c:58` `size_t mem_fread(void *buf, size_t size, size_t nmemb, MEMFILE *stream)`
- `mem_fopen_write` (function) `progs/doomgeneric/memio.c:90` `MEMFILE *mem_fopen_write(void)`
- `mem_fwrite` (function) `progs/doomgeneric/memio.c:107` `size_t mem_fwrite(const void *ptr, size_t size, size_t nmemb, MEMFILE *stream)`
- `mem_get_buf` (function) `progs/doomgeneric/memio.c:143` `void mem_get_buf(MEMFILE *stream, void **buf, size_t *buflen)`
- `mem_fclose` (function) `progs/doomgeneric/memio.c:149` `void mem_fclose(MEMFILE *stream)`
- `mem_ftell` (function) `progs/doomgeneric/memio.c:159` `long mem_ftell(MEMFILE *stream)`
- `mem_fseek` (function) `progs/doomgeneric/memio.c:164` `int mem_fseek(MEMFILE *stream, signed long position, mem_rel_t whence)`

## progs/doomgeneric/memio.h
Imported by: `progs/doomgeneric/memio.c`
- `mem_fopen_read` (function) `progs/doomgeneric/memio.h:28` `MEMFILE *mem_fopen_read(void *buf, size_t buflen);`
- `mem_fread` (function) `progs/doomgeneric/memio.h:29` `size_t mem_fread(void *buf, size_t size, size_t nmemb, MEMFILE *stream);`
- `mem_fopen_write` (function) `progs/doomgeneric/memio.h:30` `MEMFILE *mem_fopen_write(void);`
- `mem_fwrite` (function) `progs/doomgeneric/memio.h:31` `size_t mem_fwrite(const void *ptr, size_t size, size_t nmemb, MEMFILE *stream);`
- `mem_get_buf` (function) `progs/doomgeneric/memio.h:32` `void mem_get_buf(MEMFILE *stream, void **buf, size_t *buflen);`
- `mem_fclose` (function) `progs/doomgeneric/memio.h:33` `void mem_fclose(MEMFILE *stream);`
- `mem_ftell` (function) `progs/doomgeneric/memio.h:34` `long mem_ftell(MEMFILE *stream);`
- `mem_fseek` (function) `progs/doomgeneric/memio.h:35` `int mem_fseek(MEMFILE *stream, signed long offset, mem_rel_t whence);`

## progs/doomgeneric/net_client.h
Depends on: `progs/doomgeneric/d_ticcmd.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/net_defs.h`, `progs/doomgeneric/sha1.h`
Imported by: `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/d_main.c`
- `NET_CL_Disconnect` (function) `progs/doomgeneric/net_client.h:26` `void NET_CL_Disconnect(void);`
- `NET_CL_Run` (function) `progs/doomgeneric/net_client.h:27` `void NET_CL_Run(void);`
- `NET_CL_Init` (function) `progs/doomgeneric/net_client.h:28` `void NET_CL_Init(void);`
- `NET_CL_LaunchGame` (function) `progs/doomgeneric/net_client.h:29` `void NET_CL_LaunchGame(void);`
- `NET_CL_StartGame` (function) `progs/doomgeneric/net_client.h:30` `void NET_CL_StartGame(net_gamesettings_t *settings);`
- `NET_CL_SendTiccmd` (function) `progs/doomgeneric/net_client.h:31` `void NET_CL_SendTiccmd(ticcmd_t *ticcmd, int maketic);`
- `NET_Init` (function) `progs/doomgeneric/net_client.h:33` `void NET_Init(void);`
- `NET_BindVariables` (function) `progs/doomgeneric/net_client.h:35` `void NET_BindVariables(void);`

## progs/doomgeneric/net_dedicated.h
Imported by: `progs/doomgeneric/d_main.c`
- `NET_DedicatedServer` (function) `progs/doomgeneric/net_dedicated.h:21` `void NET_DedicatedServer(void);`

## progs/doomgeneric/net_gui.h
Depends on: `progs/doomgeneric/doomtype.h`
Imported by: `progs/doomgeneric/d_loop.c`
- `NET_WaitForLaunch` (function) `progs/doomgeneric/net_gui.h:26` `extern void NET_WaitForLaunch(void);`

## progs/doomgeneric/net_io.h
Depends on: `progs/doomgeneric/net_defs.h`
Imported by: `progs/doomgeneric/d_loop.c`
- `NET_NewContext` (function) `progs/doomgeneric/net_io.h:25` `net_context_t *NET_NewContext(void);`
- `NET_AddModule` (function) `progs/doomgeneric/net_io.h:26` `void NET_AddModule(net_context_t *context, net_module_t *module);`
- `NET_SendPacket` (function) `progs/doomgeneric/net_io.h:27` `void NET_SendPacket(net_addr_t *addr, net_packet_t *packet);`
- `NET_SendBroadcast` (function) `progs/doomgeneric/net_io.h:28` `void NET_SendBroadcast(net_context_t *context, net_packet_t *packet);`
- `NET_AddrToString` (function) `progs/doomgeneric/net_io.h:31` `char *NET_AddrToString(net_addr_t *addr);`
- `NET_FreeAddress` (function) `progs/doomgeneric/net_io.h:32` `void NET_FreeAddress(net_addr_t *addr);`
- `NET_ResolveAddress` (function) `progs/doomgeneric/net_io.h:33` `net_addr_t *NET_ResolveAddress(net_context_t *context, char *address);`

## progs/doomgeneric/net_packet.h
Depends on: `progs/doomgeneric/net_defs.h`
- `NET_NewPacket` (function) `progs/doomgeneric/net_packet.h:23` `net_packet_t *NET_NewPacket(int initial_size);`
- `NET_PacketDup` (function) `progs/doomgeneric/net_packet.h:24` `net_packet_t *NET_PacketDup(net_packet_t *packet);`
- `NET_FreePacket` (function) `progs/doomgeneric/net_packet.h:25` `void NET_FreePacket(net_packet_t *packet);`
- `NET_ReadString` (function) `progs/doomgeneric/net_packet.h:35` `char *NET_ReadString(net_packet_t *packet);`
- `NET_WriteInt8` (function) `progs/doomgeneric/net_packet.h:37` `void NET_WriteInt8(net_packet_t *packet, unsigned int i);`
- `NET_WriteInt16` (function) `progs/doomgeneric/net_packet.h:38` `void NET_WriteInt16(net_packet_t *packet, unsigned int i);`
- `NET_WriteInt32` (function) `progs/doomgeneric/net_packet.h:39` `void NET_WriteInt32(net_packet_t *packet, unsigned int i);`
- `NET_WriteString` (function) `progs/doomgeneric/net_packet.h:41` `void NET_WriteString(net_packet_t *packet, char *string);`

## progs/doomgeneric/net_query.h
Depends on: `progs/doomgeneric/net_defs.h`
Imported by: `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/d_main.c`
- `NET_StartLANQuery` (function) `progs/doomgeneric/net_query.h:28` `extern int NET_StartLANQuery(void);`
- `NET_StartMasterQuery` (function) `progs/doomgeneric/net_query.h:29` `extern int NET_StartMasterQuery(void);`
- `NET_LANQuery` (function) `progs/doomgeneric/net_query.h:31` `extern void NET_LANQuery(void);`
- `NET_MasterQuery` (function) `progs/doomgeneric/net_query.h:32` `extern void NET_MasterQuery(void);`
- `NET_QueryAddress` (function) `progs/doomgeneric/net_query.h:33` `extern void NET_QueryAddress(char *addr);`
- `NET_FindLANServer` (function) `progs/doomgeneric/net_query.h:34` `extern net_addr_t *NET_FindLANServer(void);`
- `NET_Query_Poll` (function) `progs/doomgeneric/net_query.h:36` `extern int NET_Query_Poll(net_query_callback_t callback, void *user_data);`
- `NET_Query_ResolveMaster` (function) `progs/doomgeneric/net_query.h:38` `extern net_addr_t *NET_Query_ResolveMaster(net_context_t *context);`
- `NET_Query_AddToMaster` (function) `progs/doomgeneric/net_query.h:39` `extern void NET_Query_AddToMaster(net_addr_t *master_addr);`
- `NET_Query_CheckAddedToMaster` (function) `progs/doomgeneric/net_query.h:40` `extern boolean NET_Query_CheckAddedToMaster(boolean *result);`
- `NET_Query_MasterResponse` (function) `progs/doomgeneric/net_query.h:41` `extern void NET_Query_MasterResponse(net_packet_t *packet);`

## progs/doomgeneric/net_server.h
Imported by: `progs/doomgeneric/d_loop.c`
- `NET_SV_Init` (function) `progs/doomgeneric/net_server.h:22` `void NET_SV_Init(void);`
- `NET_SV_Run` (function) `progs/doomgeneric/net_server.h:26` `void NET_SV_Run(void);`
- `NET_SV_Shutdown` (function) `progs/doomgeneric/net_server.h:31` `void NET_SV_Shutdown(void);`
- `NET_SV_AddModule` (function) `progs/doomgeneric/net_server.h:35` `void NET_SV_AddModule(net_module_t *module);`
- `NET_SV_RegisterWithMaster` (function) `progs/doomgeneric/net_server.h:39` `void NET_SV_RegisterWithMaster(void);`

## progs/doomgeneric/p_ceilng.c
Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/z_zone.h`
- `T_MoveCeiling` (function) `progs/doomgeneric/p_ceilng.c:45` `void T_MoveCeiling (ceiling_t* ceiling)`
- `EV_DoCeiling` (function) `progs/doomgeneric/p_ceilng.c:161` `int
EV_DoCeiling
( line_t*	line,
  ceiling_e	type )`
- `P_AddActiveCeiling` (function) `progs/doomgeneric/p_ceilng.c:240` `void P_AddActiveCeiling(ceiling_t* c)` -- Add an active ceiling
- `P_RemoveActiveCeiling` (function) `progs/doomgeneric/p_ceilng.c:259` `void P_RemoveActiveCeiling(ceiling_t* c)` -- Remove a ceiling's thinker
- `P_ActivateInStasisCeiling` (function) `progs/doomgeneric/p_ceilng.c:280` `void P_ActivateInStasisCeiling(line_t* line)` -- Restart a ceiling that's in-stasis
- `EV_CeilingCrushStop` (function) `progs/doomgeneric/p_ceilng.c:303` `int	EV_CeilingCrushStop(line_t	*line)` -- EV_CeilingCrushStop Stop a ceiling from crushing!

## progs/doomgeneric/p_doors.c
Depends on: `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/dstrings.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/z_zone.h`
- `T_VerticalDoor` (function) `progs/doomgeneric/p_doors.c:57` `void T_VerticalDoor (vldoor_t* door)` -- T_VerticalDoor
- `EV_DoLockedDoor` (function) `progs/doomgeneric/p_doors.c:195` `int
EV_DoLockedDoor
( line_t*	line,
  vldoor_e	type,
  mobj_t*	thing )`
- `EV_DoDoor` (function) `progs/doomgeneric/p_doors.c:252` `int
EV_DoDoor
( line_t*	line,
  vldoor_e	type )`
- `EV_VerticalDoor` (function) `progs/doomgeneric/p_doors.c:337` `void
EV_VerticalDoor
( line_t*	line,
  mobj_t*	thing )`
- `P_SpawnDoorCloseIn30` (function) `progs/doomgeneric/p_doors.c:519` `void P_SpawnDoorCloseIn30 (sector_t* sec)` -- Spawn a door that closes after 30 seconds
- `P_SpawnDoorRaiseIn5Mins` (function) `progs/doomgeneric/p_doors.c:542` `void
P_SpawnDoorRaiseIn5Mins
( sector_t*	sec,
  int		secnum )`
- `P_InitSlidingDoorFrames` (function) `progs/doomgeneric/p_doors.c:580` `void P_InitSlidingDoorFrames(void)`
- `P_FindSlidingDoorType` (function) `progs/doomgeneric/p_doors.c:624` `int P_FindSlidingDoorType(line_t*	line)` -- Return index into "slideFrames" array for which door type to use
- `T_SlidingDoor` (function) `progs/doomgeneric/p_doors.c:639` `void T_SlidingDoor (slidedoor_t*	door)`
- `EV_SlidingDoor` (function) `progs/doomgeneric/p_doors.c:727` `void
EV_SlidingDoor
( line_t*	line,
  mobj_t*	thing )`

## progs/doomgeneric/p_enemy.c
Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`
- `P_RecursiveSound` (function) `progs/doomgeneric/p_enemy.c:99` `void
P_RecursiveSound
( sector_t*	sec,
  int		soundblocks )`
- `P_NoiseAlert` (function) `progs/doomgeneric/p_enemy.c:152` `void
P_NoiseAlert
( mobj_t*	target,
  mobj_t*	emmiter )`
- `P_CheckMeleeRange` (function) `progs/doomgeneric/p_enemy.c:167` `boolean P_CheckMeleeRange (mobj_t*	actor)` -- P_CheckMeleeRange
- `P_CheckMissileRange` (function) `progs/doomgeneric/p_enemy.c:190` `boolean P_CheckMissileRange (mobj_t* actor)` -- P_CheckMissileRange
- `P_Move` (function) `progs/doomgeneric/p_enemy.c:260` `boolean P_Move (mobj_t*	actor)`
- `P_TryWalk` (function) `progs/doomgeneric/p_enemy.c:337` `boolean P_TryWalk (mobj_t* actor)` -- TryWalk Attempts to move actor on in its current (ob->moveangle) direction.
- `P_NewChaseDir` (function) `progs/doomgeneric/p_enemy.c:351` `void P_NewChaseDir (mobj_t*	actor)`
- `P_LookForPlayers` (function) `progs/doomgeneric/p_enemy.c:487` `boolean
P_LookForPlayers
( mobj_t*	actor,
  boolean	allaround )`
- `A_KeenDie` (function) `progs/doomgeneric/p_enemy.c:551` `void A_KeenDie (mobj_t* mo)` -- A_KeenDie DOOM II special, map 32.
- `A_Look` (function) `progs/doomgeneric/p_enemy.c:589` `void A_Look (mobj_t* actor)` -- A_Look Stay in state until a player is sighted.
- `A_Chase` (function) `progs/doomgeneric/p_enemy.c:657` `void A_Chase (mobj_t*	actor)` -- A_Chase Actor has a melee attack, so it tries to close as fast as possible
- `A_FaceTarget` (function) `progs/doomgeneric/p_enemy.c:767` `void A_FaceTarget (mobj_t* actor)` -- A_FaceTarget
- `A_PosAttack` (function) `progs/doomgeneric/p_enemy.c:787` `void A_PosAttack (mobj_t* actor)` -- A_PosAttack
- `A_SPosAttack` (function) `progs/doomgeneric/p_enemy.c:806` `void A_SPosAttack (mobj_t* actor)`
- `A_CPosAttack` (function) `progs/doomgeneric/p_enemy.c:830` `void A_CPosAttack (mobj_t* actor)`
- `A_CPosRefire` (function) `progs/doomgeneric/p_enemy.c:850` `void A_CPosRefire (mobj_t* actor)`
- `A_SpidRefire` (function) `progs/doomgeneric/p_enemy.c:867` `void A_SpidRefire (mobj_t* actor)`
- `A_BspiAttack` (function) `progs/doomgeneric/p_enemy.c:883` `void A_BspiAttack (mobj_t *actor)`
- `A_TroopAttack` (function) `progs/doomgeneric/p_enemy.c:898` `void A_TroopAttack (mobj_t* actor)` -- A_TroopAttack
- `A_SargAttack` (function) `progs/doomgeneric/p_enemy.c:920` `void A_SargAttack (mobj_t* actor)`
- `A_HeadAttack` (function) `progs/doomgeneric/p_enemy.c:935` `void A_HeadAttack (mobj_t* actor)`
- `A_CyberAttack` (function) `progs/doomgeneric/p_enemy.c:954` `void A_CyberAttack (mobj_t* actor)`
- `A_BruisAttack` (function) `progs/doomgeneric/p_enemy.c:964` `void A_BruisAttack (mobj_t* actor)`
- `A_SkelMissile` (function) `progs/doomgeneric/p_enemy.c:987` `void A_SkelMissile (mobj_t* actor)` -- A_SkelMissile
- `A_Tracer` (function) `progs/doomgeneric/p_enemy.c:1006` `void A_Tracer (mobj_t* actor)`
- `A_SkelWhoosh` (function) `progs/doomgeneric/p_enemy.c:1078` `void A_SkelWhoosh (mobj_t*	actor)`
- `A_SkelFist` (function) `progs/doomgeneric/p_enemy.c:1086` `void A_SkelFist (mobj_t*	actor)`
- `PIT_VileCheck` (function) `progs/doomgeneric/p_enemy.c:1114` `boolean PIT_VileCheck (mobj_t*	thing)`
- `A_VileChase` (function) `progs/doomgeneric/p_enemy.c:1152` `void A_VileChase (mobj_t* actor)` -- A_VileChase Check for ressurecting a body
- `A_VileStart` (function) `progs/doomgeneric/p_enemy.c:1218` `void A_VileStart (mobj_t* actor)` -- A_VileStart
- `A_StartFire` (function) `progs/doomgeneric/p_enemy.c:1230` `void A_StartFire (mobj_t* actor)`
- `A_FireCrackle` (function) `progs/doomgeneric/p_enemy.c:1236` `void A_FireCrackle (mobj_t* actor)`
- `A_Fire` (function) `progs/doomgeneric/p_enemy.c:1242` `void A_Fire (mobj_t* actor)`
- `A_VileTarget` (function) `progs/doomgeneric/p_enemy.c:1273` `void A_VileTarget (mobj_t*	actor)` -- A_VileTarget Spawn the hellfire
- `A_VileAttack` (function) `progs/doomgeneric/p_enemy.c:1298` `void A_VileAttack (mobj_t* actor)` -- A_VileAttack
- `A_FatRaise` (function) `progs/doomgeneric/p_enemy.c:1339` `void A_FatRaise (mobj_t *actor)`
- `A_FatAttack1` (function) `progs/doomgeneric/p_enemy.c:1346` `void A_FatAttack1 (mobj_t* actor)`
- `A_FatAttack2` (function) `progs/doomgeneric/p_enemy.c:1366` `void A_FatAttack2 (mobj_t* actor)`
- `A_FatAttack3` (function) `progs/doomgeneric/p_enemy.c:1385` `void A_FatAttack3 (mobj_t*	actor)`
- `A_SkullAttack` (function) `progs/doomgeneric/p_enemy.c:1415` `void A_SkullAttack (mobj_t* actor)`
- `A_PainShootSkull` (function) `progs/doomgeneric/p_enemy.c:1446` `void
A_PainShootSkull
( mobj_t*	actor,
  angle_t	angle )`
- `A_PainAttack` (function) `progs/doomgeneric/p_enemy.c:1508` `void A_PainAttack (mobj_t* actor)` -- A_PainAttack Spawn a lost soul and launch it at the target
- `A_PainDie` (function) `progs/doomgeneric/p_enemy.c:1518` `void A_PainDie (mobj_t* actor)`
- `A_Scream` (function) `progs/doomgeneric/p_enemy.c:1531` `void A_Scream (mobj_t* actor)`
- `A_XScream` (function) `progs/doomgeneric/p_enemy.c:1568` `void A_XScream (mobj_t* actor)`
- `A_Pain` (function) `progs/doomgeneric/p_enemy.c:1573` `void A_Pain (mobj_t* actor)`
- `A_Fall` (function) `progs/doomgeneric/p_enemy.c:1581` `void A_Fall (mobj_t *actor)`
- `A_Explode` (function) `progs/doomgeneric/p_enemy.c:1594` `void A_Explode (mobj_t* thingy)` -- A_Explode
- `CheckBossEnd` (function) `progs/doomgeneric/p_enemy.c:1605` `static boolean CheckBossEnd(mobjtype_t motype)`
- `A_BossDeath` (function) `progs/doomgeneric/p_enemy.c:1656` `void A_BossDeath (mobj_t* mo)` -- A_BossDeath Possibly trigger special effects if on first boss level
- `A_Hoof` (function) `progs/doomgeneric/p_enemy.c:1757` `void A_Hoof (mobj_t* mo)`
- `A_Metal` (function) `progs/doomgeneric/p_enemy.c:1763` `void A_Metal (mobj_t* mo)`
- `A_BabyMetal` (function) `progs/doomgeneric/p_enemy.c:1769` `void A_BabyMetal (mobj_t* mo)`
- `A_OpenShotgun2` (function) `progs/doomgeneric/p_enemy.c:1776` `void
A_OpenShotgun2
( player_t*	player,
  pspdef_t*	psp )`
- `A_LoadShotgun2` (function) `progs/doomgeneric/p_enemy.c:1784` `void
A_LoadShotgun2
( player_t*	player,
  pspdef_t*	psp )`
- `A_ReFire` (function) `progs/doomgeneric/p_enemy.c:1792` `void A_ReFire ( player_t* player, pspdef_t* psp );`
- `A_CloseShotgun2` (function) `progs/doomgeneric/p_enemy.c:1797` `void
A_CloseShotgun2
( player_t*	player,
  pspdef_t*	psp )`
- `A_BrainAwake` (function) `progs/doomgeneric/p_enemy.c:1811` `void A_BrainAwake (mobj_t* mo)`
- `A_BrainPain` (function) `progs/doomgeneric/p_enemy.c:1841` `void A_BrainPain (mobj_t*	mo)`
- `A_BrainScream` (function) `progs/doomgeneric/p_enemy.c:1847` `void A_BrainScream (mobj_t*	mo)`
- `A_BrainExplode` (function) `progs/doomgeneric/p_enemy.c:1873` `void A_BrainExplode (mobj_t* mo)`
- `A_BrainDie` (function) `progs/doomgeneric/p_enemy.c:1894` `void A_BrainDie (mobj_t*	mo)`
- `A_BrainSpit` (function) `progs/doomgeneric/p_enemy.c:1899` `void A_BrainSpit (mobj_t*	mo)`
- `A_SpawnSound` (function) `progs/doomgeneric/p_enemy.c:1928` `void A_SpawnSound (mobj_t* mo)` -- travelling cube sound
- `A_SpawnFly` (function) `progs/doomgeneric/p_enemy.c:1934` `void A_SpawnFly (mobj_t* mo)`
- `A_PlayerScream` (function) `progs/doomgeneric/p_enemy.c:1992` `void A_PlayerScream (mobj_t* mo)`

## progs/doomgeneric/p_floor.c
Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/z_zone.h`
- `T_MovePlane` (function) `progs/doomgeneric/p_floor.c:42` `result_e
T_MovePlane
( sector_t*	sector,
  fixed_t	speed,
  fixed_t	dest,
  boolean	crush,
  int	...`
- `T_MoveFloor` (function) `progs/doomgeneric/p_floor.c:202` `void T_MoveFloor(floormove_t* floor)` -- MOVE A FLOOR TO IT'S DESTINATION (UP OR DOWN)
- `EV_DoFloor` (function) `progs/doomgeneric/p_floor.c:251` `int
EV_DoFloor
( line_t*	line,
  floor_e	floortype )`
- `EV_BuildStairs` (function) `progs/doomgeneric/p_floor.c:444` `int
EV_BuildStairs
( line_t*	line,
  stair_e	type )`

## progs/doomgeneric/p_inter.c
Depends on: `progs/doomgeneric/am_map.h`, `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/deh_misc.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/dstrings.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/p_inter.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`
- `P_GiveAmmo` (function) `progs/doomgeneric/p_inter.c:66` `boolean
P_GiveAmmo
( player_t*	player,
  ammotype_t	ammo,
  int		num )`
- `P_GiveWeapon` (function) `progs/doomgeneric/p_inter.c:160` `boolean
P_GiveWeapon
( player_t*	player,
  weapontype_t	weapon,
  boolean	dropped )`
- `P_GiveBody` (function) `progs/doomgeneric/p_inter.c:223` `boolean
P_GiveBody
( player_t*	player,
  int		num )`
- `P_GiveArmor` (function) `progs/doomgeneric/p_inter.c:246` `boolean
P_GiveArmor
( player_t*	player,
  int		armortype )`
- `P_GiveCard` (function) `progs/doomgeneric/p_inter.c:268` `void
P_GiveCard
( player_t*	player,
  card_t	card )`
- `P_GivePower` (function) `progs/doomgeneric/p_inter.c:284` `boolean
P_GivePower
( player_t*	player,
  int /*powertype_t*/	power )`
- `P_TouchSpecialThing` (function) `progs/doomgeneric/p_inter.c:333` `void
P_TouchSpecialThing
( mobj_t*	special,
  mobj_t*	toucher )`
- `P_KillMobj` (function) `progs/doomgeneric/p_inter.c:666` `void
P_KillMobj
( mobj_t*	source,
  mobj_t*	target )`
- `P_DamageMobj` (function) `progs/doomgeneric/p_inter.c:779` `void
P_DamageMobj
( mobj_t*	target,
  mobj_t*	inflictor,
  mobj_t*	source,
  int 		damage )`

## progs/doomgeneric/p_lights.c
Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/z_zone.h`
- `T_FireFlicker` (function) `progs/doomgeneric/p_lights.c:39` `void T_FireFlicker (fireflicker_t* flick)` -- T_FireFlicker
- `P_SpawnFireFlicker` (function) `progs/doomgeneric/p_lights.c:61` `void P_SpawnFireFlicker (sector_t*	sector)` -- P_SpawnFireFlicker
- `T_LightFlash` (function) `progs/doomgeneric/p_lights.c:91` `void T_LightFlash (lightflash_t* flash)` -- T_LightFlash Do flashing lights.
- `P_SpawnLightFlash` (function) `progs/doomgeneric/p_lights.c:117` `void P_SpawnLightFlash (sector_t*	sector)` -- P_SpawnLightFlash After the map has been loaded, scan each sector for specials that spawn thinkers
- `T_StrobeFlash` (function) `progs/doomgeneric/p_lights.c:148` `void T_StrobeFlash (strobe_t*		flash)` -- T_StrobeFlash
- `P_SpawnStrobeFlash` (function) `progs/doomgeneric/p_lights.c:174` `void
P_SpawnStrobeFlash
( sector_t*	sector,
  int		fastOrSlow,
  int		inSync )`
- `EV_StartLightStrobing` (function) `progs/doomgeneric/p_lights.c:208` `void EV_StartLightStrobing(line_t*	line)` -- Start strobing lights (usually from a trigger)
- `EV_TurnTagLightsOff` (function) `progs/doomgeneric/p_lights.c:229` `void EV_TurnTagLightsOff(line_t* line)` -- TURN LINE'S TAG LIGHTS OFF
- `EV_LightTurnOn` (function) `progs/doomgeneric/p_lights.c:264` `void
EV_LightTurnOn
( line_t*	line,
  int		bright )`
- `T_Glow` (function) `progs/doomgeneric/p_lights.c:307` `void T_Glow(glow_t*	g)`
- `P_SpawnGlowingLight` (function) `progs/doomgeneric/p_lights.c:334` `void P_SpawnGlowingLight(sector_t*	sector)`

## progs/doomgeneric/p_local.h
Depends on: `progs/doomgeneric/p_spec.h`, `progs/doomgeneric/r_local.h`
Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/p_ceilng.c`, `progs/doomgeneric/p_doors.c`, `progs/doomgeneric/p_enemy.c`, `progs/doomgeneric/p_floor.c`, `progs/doomgeneric/p_inter.c`, `progs/doomgeneric/p_lights.c`, `progs/doomgeneric/p_map.c`, `progs/doomgeneric/p_maputl.c`, `progs/doomgeneric/p_mobj.c`, `progs/doomgeneric/p_plats.c`, `progs/doomgeneric/p_pspr.c`, `progs/doomgeneric/p_saveg.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/p_sight.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/p_switch.c`, `progs/doomgeneric/p_telept.c`, `progs/doomgeneric/p_tick.c`, `progs/doomgeneric/p_user.c`, `progs/doomgeneric/r_data.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/st_stuff.c`
- `P_InitThinkers` (function) `progs/doomgeneric/p_local.h:70` `void P_InitThinkers (void);`
- `P_AddThinker` (function) `progs/doomgeneric/p_local.h:71` `void P_AddThinker (thinker_t* thinker);`
- `P_RemoveThinker` (function) `progs/doomgeneric/p_local.h:72` `void P_RemoveThinker (thinker_t* thinker);`
- `P_SetupPsprites` (function) `progs/doomgeneric/p_local.h:78` `void P_SetupPsprites (player_t* curplayer);` -- P_PSPR
- `P_MovePsprites` (function) `progs/doomgeneric/p_local.h:79` `void P_MovePsprites (player_t* curplayer);`
- `P_DropWeapon` (function) `progs/doomgeneric/p_local.h:80` `void P_DropWeapon (player_t* player);`
- `P_PlayerThink` (function) `progs/doomgeneric/p_local.h:86` `void P_PlayerThink (player_t* player);` -- P_USER
- `P_RespawnSpecials` (function) `progs/doomgeneric/p_local.h:104` `void P_RespawnSpecials (void);`
- `P_SpawnMobj` (function) `progs/doomgeneric/p_local.h:107` `mobj_t* P_SpawnMobj ( fixed_t x, fixed_t y, fixed_t z, mobjtype_t type );`
- `P_RemoveMobj` (function) `progs/doomgeneric/p_local.h:113` `void P_RemoveMobj (mobj_t* th);`
- `P_SubstNullMobj` (function) `progs/doomgeneric/p_local.h:114` `mobj_t* P_SubstNullMobj (mobj_t* th);`
- `P_MobjThinker` (function) `progs/doomgeneric/p_local.h:116` `void P_MobjThinker (mobj_t* mobj);`
- `P_SpawnPuff` (function) `progs/doomgeneric/p_local.h:118` `void P_SpawnPuff (fixed_t x, fixed_t y, fixed_t z);`
- `P_SpawnBlood` (function) `progs/doomgeneric/p_local.h:119` `void P_SpawnBlood (fixed_t x, fixed_t y, fixed_t z, int damage);`
- `P_SpawnMissile` (function) `progs/doomgeneric/p_local.h:120` `mobj_t* P_SpawnMissile (mobj_t* source, mobj_t* dest, mobjtype_t type);`
- `P_SpawnPlayerMissile` (function) `progs/doomgeneric/p_local.h:121` `void P_SpawnPlayerMissile (mobj_t* source, mobjtype_t type);`
- `P_NoiseAlert` (function) `progs/doomgeneric/p_local.h:127` `void P_NoiseAlert (mobj_t* target, mobj_t* emmiter);` -- P_ENEMY
- `P_AproxDistance` (function) `progs/doomgeneric/p_local.h:162` `fixed_t P_AproxDistance (fixed_t dx, fixed_t dy);`
- `P_PointOnLineSide` (function) `progs/doomgeneric/p_local.h:163` `int P_PointOnLineSide (fixed_t x, fixed_t y, line_t* line);`
- `P_PointOnDivlineSide` (function) `progs/doomgeneric/p_local.h:164` `int P_PointOnDivlineSide (fixed_t x, fixed_t y, divline_t* line);`
- `P_MakeDivline` (function) `progs/doomgeneric/p_local.h:165` `void P_MakeDivline (line_t* li, divline_t* dl);`
- `P_InterceptVector` (function) `progs/doomgeneric/p_local.h:166` `fixed_t P_InterceptVector (divline_t* v2, divline_t* v1);`
- `P_BoxOnLineSide` (function) `progs/doomgeneric/p_local.h:167` `int P_BoxOnLineSide (fixed_t* tmbox, line_t* ld);`
- `P_LineOpening` (function) `progs/doomgeneric/p_local.h:174` `void P_LineOpening (line_t* linedef);`
- `P_UnsetThingPosition` (function) `progs/doomgeneric/p_local.h:194` `void P_UnsetThingPosition (mobj_t* thing);`
- `P_SetThingPosition` (function) `progs/doomgeneric/p_local.h:195` `void P_SetThingPosition (mobj_t* thing);`
- `P_SlideMove` (function) `progs/doomgeneric/p_local.h:228` `void P_SlideMove (mobj_t* mo);`
- `P_UseLines` (function) `progs/doomgeneric/p_local.h:230` `void P_UseLines (player_t* player);`
- `P_AimLineAttack` (function) `progs/doomgeneric/p_local.h:237` `fixed_t P_AimLineAttack ( mobj_t* t1, angle_t angle, fixed_t distance );`
- `P_LineAttack` (function) `progs/doomgeneric/p_local.h:243` `void P_LineAttack ( mobj_t* t1, angle_t angle, fixed_t distance, fixed_t slope, int damage );`
- `P_RadiusAttack` (function) `progs/doomgeneric/p_local.h:251` `void P_RadiusAttack ( mobj_t* spot, mobj_t* source, int damage );`
- `P_TouchSpecialThing` (function) `progs/doomgeneric/p_local.h:279` `void P_TouchSpecialThing ( mobj_t* special, mobj_t* toucher );`
- `P_DamageMobj` (function) `progs/doomgeneric/p_local.h:284` `void P_DamageMobj ( mobj_t* target, mobj_t* inflictor, mobj_t* source, int damage );`


Next: [API_p14.md](API_p14.md)
