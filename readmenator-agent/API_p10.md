# API (page 10 of 19)
Previous: [API_p9.md](API_p9.md)

## progs/doomgeneric/f_wipe.c
Depends on: `kernel/string.c`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/f_wipe.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/z_zone.h`
- `wipe_shittyColMajorXform` (function) `progs/doomgeneric/f_wipe.c:43` `void
wipe_shittyColMajorXform
( short*	array,
  int		width,
  int		height )`
- `wipe_initColorXForm` (function) `progs/doomgeneric/f_wipe.c:65` `int
wipe_initColorXForm
( int	width,
  int	height,
  int	ticks )`
- `wipe_doColorXForm` (function) `progs/doomgeneric/f_wipe.c:75` `int
wipe_doColorXForm
( int	width,
  int	height,
  int	ticks )`
- `wipe_exitColorXForm` (function) `progs/doomgeneric/f_wipe.c:121` `int
wipe_exitColorXForm
( int	width,
  int	height,
  int	ticks )`
- `wipe_initMelt` (function) `progs/doomgeneric/f_wipe.c:133` `int
wipe_initMelt
( int	width,
  int	height,
  int	ticks )`
- `wipe_doMelt` (function) `progs/doomgeneric/f_wipe.c:164` `int
wipe_doMelt
( int	width,
  int	height,
  int	ticks )`
- `wipe_exitMelt` (function) `progs/doomgeneric/f_wipe.c:219` `int
wipe_exitMelt
( int	width,
  int	height,
  int	ticks )`
- `wipe_StartScreen` (function) `progs/doomgeneric/f_wipe.c:231` `int
wipe_StartScreen
( int	x,
  int	y,
  int	width,
  int	height )`
- `wipe_EndScreen` (function) `progs/doomgeneric/f_wipe.c:243` `int
wipe_EndScreen
( int	x,
  int	y,
  int	width,
  int	height )`
- `wipe_ScreenWipe` (function) `progs/doomgeneric/f_wipe.c:256` `int
wipe_ScreenWipe
( int	wipeno,
  int	x,
  int	y,
  int	width,
  int	height,
  int	ticks )`

## progs/doomgeneric/f_wipe.h
Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/f_wipe.c`
- `wipe_StartScreen` (function) `progs/doomgeneric/f_wipe.h:39` `int wipe_StartScreen ( int x, int y, int width, int height );`
- `wipe_EndScreen` (function) `progs/doomgeneric/f_wipe.h:47` `int wipe_EndScreen ( int x, int y, int width, int height );`
- `wipe_ScreenWipe` (function) `progs/doomgeneric/f_wipe.h:55` `int wipe_ScreenWipe ( int wipeno, int x, int y, int width, int height, int ticks );`

## progs/doomgeneric/g_game.c
Depends on: `kernel/string.c`, `progs/doomgeneric/am_map.h`, `progs/doomgeneric/d_main.h`, `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/deh_misc.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/dstrings.h`, `progs/doomgeneric/f_finale.h`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/hu_stuff.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/i_timer.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_controls.h`, `progs/doomgeneric/m_menu.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/p_saveg.h`, `progs/doomgeneric/p_setup.h`, `progs/doomgeneric/p_tick.h`, `progs/doomgeneric/r_data.h`, `progs/doomgeneric/r_sky.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/st_stuff.h`, `progs/doomgeneric/statdump.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/wi_stuff.h`, `progs/doomgeneric/z_zone.h`
- `G_DoVictory` (function) `progs/doomgeneric/g_game.c:88` `void G_DoVictory (void);`
- `G_CmdChecksum` (function) `progs/doomgeneric/g_game.c:233` `int G_CmdChecksum (ticcmd_t* cmd)`
- `WeaponSelectable` (function) `progs/doomgeneric/g_game.c:244` `static boolean WeaponSelectable(weapontype_t weapon)`
- `G_NextWeapon` (function) `progs/doomgeneric/g_game.c:281` `static int G_NextWeapon(int direction)`
- `G_BuildTiccmd` (function) `progs/doomgeneric/g_game.c:322` `void G_BuildTiccmd (ticcmd_t* cmd, int maketic)` -- G_BuildTiccmd Builds a ticcmd from all of the available inputs or reads it from the demo buffer.
- `G_DoLoadLevel` (function) `progs/doomgeneric/g_game.c:603` `void G_DoLoadLevel (void)` -- G_DoLoadLevel
- `SetJoyButtons` (function) `progs/doomgeneric/g_game.c:675` `static void SetJoyButtons(unsigned int buttons_mask)`
- `SetMouseButtons` (function) `progs/doomgeneric/g_game.c:703` `static void SetMouseButtons(unsigned int buttons_mask)`
- `G_Responder` (function) `progs/doomgeneric/g_game.c:733` `boolean G_Responder (event_t* ev)` -- G_Responder Get info needed to make ticcmd_ts for the players.
- `G_Ticker` (function) `progs/doomgeneric/g_game.c:854` `void G_Ticker (void)` -- G_Ticker Make ticcmd_ts for the players.
- `G_InitPlayer` (function) `progs/doomgeneric/g_game.c:1039` `void G_InitPlayer (int player)` -- G_InitPlayer Called at the start.
- `G_PlayerFinishLevel` (function) `progs/doomgeneric/g_game.c:1051` `void G_PlayerFinishLevel (int player)` -- G_PlayerFinishLevel Can when a player completes a level.
- `G_PlayerReborn` (function) `progs/doomgeneric/g_game.c:1072` `void G_PlayerReborn (int player)` -- G_PlayerReborn Called after a player dies almost everything is cleared and initialized
- `P_SpawnPlayer` (function) `progs/doomgeneric/g_game.c:1113` `void P_SpawnPlayer (mapthing_t* mthing);` -- G_CheckSpot Returns false if the player cannot be respawned at the given mapthing_t spot because something is...
- `G_CheckSpot` (function) `progs/doomgeneric/g_game.c:1116` `boolean
G_CheckSpot
( int		playernum,
  mapthing_t*	mthing )`
- `G_DeathMatchSpawnPlayer` (function) `progs/doomgeneric/g_game.c:1223` `void G_DeathMatchSpawnPlayer (int playernum)` -- G_DeathMatchSpawnPlayer Spawns a player at one of the random death match spots called at level load and each death
- `G_DoReborn` (function) `progs/doomgeneric/g_game.c:1250` `void G_DoReborn (int playernum)` -- G_DoReborn
- `G_ScreenShot` (function) `progs/doomgeneric/g_game.c:1296` `void G_ScreenShot (void)`
- `G_ExitLevel` (function) `progs/doomgeneric/g_game.c:1328` `void G_ExitLevel (void)`
- `G_SecretExitLevel` (function) `progs/doomgeneric/g_game.c:1335` `void G_SecretExitLevel (void)` -- Here's for the german edition.
- `G_DoCompleted` (function) `progs/doomgeneric/g_game.c:1346` `void G_DoCompleted (void)`
- `G_WorldDone` (function) `progs/doomgeneric/g_game.c:1494` `void G_WorldDone (void)` -- G_WorldDone
- `G_DoWorldDone` (function) `progs/doomgeneric/g_game.c:1519` `void G_DoWorldDone (void)`
- `R_ExecuteSetViewSize` (function) `progs/doomgeneric/g_game.c:1535` `void R_ExecuteSetViewSize (void);`
- `G_LoadGame` (function) `progs/doomgeneric/g_game.c:1539` `void G_LoadGame (char* name)`
- `G_DoLoadGame` (function) `progs/doomgeneric/g_game.c:1548` `void G_DoLoadGame (void)`
- `G_SaveGame` (function) `progs/doomgeneric/g_game.c:1601` `void
G_SaveGame
( int	slot,
  char*	description )`
- `G_DoSaveGame` (function) `progs/doomgeneric/g_game.c:1610` `void G_DoSaveGame (void)`
- `G_DeferedInitNew` (function) `progs/doomgeneric/g_game.c:1698` `void
G_DeferedInitNew
( skill_t	skill,
  int		episode,
  int		map)`
- `G_DoNewGame` (function) `progs/doomgeneric/g_game.c:1710` `void G_DoNewGame (void)`
- `G_InitNew` (function) `progs/doomgeneric/g_game.c:1727` `void
G_InitNew
( skill_t	skill,
  int		episode,
  int		map )`
- `G_ReadDemoTiccmd` (function) `progs/doomgeneric/g_game.c:1898` `void G_ReadDemoTiccmd (ticcmd_t* cmd)`
- `IncreaseDemoBuffer` (function) `progs/doomgeneric/g_game.c:1926` `static void IncreaseDemoBuffer(void)`
- `G_WriteDemoTiccmd` (function) `progs/doomgeneric/g_game.c:1956` `void G_WriteDemoTiccmd (ticcmd_t* cmd)`
- `G_RecordDemo` (function) `progs/doomgeneric/g_game.c:2010` `void G_RecordDemo (char *name)` -- G_RecordDemo
- `G_VanillaVersionCode` (function) `progs/doomgeneric/g_game.c:2040` `int G_VanillaVersionCode(void)` -- Get the demo version code appropriate for the version set in gameversion.
- `G_BeginRecording` (function) `progs/doomgeneric/g_game.c:2058` `void G_BeginRecording (void)`
- `G_DeferedPlayDemo` (function) `progs/doomgeneric/g_game.c:2107` `void G_DeferedPlayDemo (char* name)`
- `DemoVersionDescription` (function) `progs/doomgeneric/g_game.c:2115` `static char *DemoVersionDescription(int version)`
- `G_DoPlayDemo` (function) `progs/doomgeneric/g_game.c:2152` `void G_DoPlayDemo (void)`
- `G_TimeDemo` (function) `progs/doomgeneric/g_game.c:2215` `void G_TimeDemo (char* name)` -- G_TimeDemo
- `G_CheckDemoStatus` (function) `progs/doomgeneric/g_game.c:2243` `boolean G_CheckDemoStatus (void)`

## progs/doomgeneric/g_game.h
Depends on: `progs/doomgeneric/d_event.h`, `progs/doomgeneric/d_ticcmd.h`, `progs/doomgeneric/doomdef.h`
Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/p_enemy.c`, `progs/doomgeneric/p_saveg.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/p_switch.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/wi_stuff.c`
- `G_DeathMatchSpawnPlayer` (function) `progs/doomgeneric/g_game.h:31` `void G_DeathMatchSpawnPlayer (int playernum);` -- GAME
- `G_InitNew` (function) `progs/doomgeneric/g_game.h:33` `void G_InitNew (skill_t skill, int episode, int map);`
- `G_DeferedInitNew` (function) `progs/doomgeneric/g_game.h:38` `void G_DeferedInitNew (skill_t skill, int episode, int map);` -- Can be called by the startup code or M_Responder.
- `G_DeferedPlayDemo` (function) `progs/doomgeneric/g_game.h:40` `void G_DeferedPlayDemo (char* demo);`
- `G_LoadGame` (function) `progs/doomgeneric/g_game.h:44` `void G_LoadGame (char* name);` -- Can be called by the startup code or M_Responder, calls P_SetupLevel or W_EnterWorld.
- `G_DoLoadGame` (function) `progs/doomgeneric/g_game.h:46` `void G_DoLoadGame (void);`
- `G_SaveGame` (function) `progs/doomgeneric/g_game.h:49` `void G_SaveGame (int slot, char* description);` -- Called by M_Responder.
- `G_RecordDemo` (function) `progs/doomgeneric/g_game.h:52` `void G_RecordDemo (char* name);` -- Only called by startup code.
- `G_BeginRecording` (function) `progs/doomgeneric/g_game.h:54` `void G_BeginRecording (void);`
- `G_PlayDemo` (function) `progs/doomgeneric/g_game.h:56` `void G_PlayDemo (char* name);`
- `G_TimeDemo` (function) `progs/doomgeneric/g_game.h:57` `void G_TimeDemo (char* name);`
- `G_ExitLevel` (function) `progs/doomgeneric/g_game.h:60` `void G_ExitLevel (void);`
- `G_SecretExitLevel` (function) `progs/doomgeneric/g_game.h:61` `void G_SecretExitLevel (void);`
- `G_WorldDone` (function) `progs/doomgeneric/g_game.h:63` `void G_WorldDone (void);`
- `G_BuildTiccmd` (function) `progs/doomgeneric/g_game.h:67` `void G_BuildTiccmd (ticcmd_t *cmd, int maketic);`
- `G_Ticker` (function) `progs/doomgeneric/g_game.h:69` `void G_Ticker (void);`
- `G_ScreenShot` (function) `progs/doomgeneric/g_game.h:72` `void G_ScreenShot (void);`
- `G_DrawMouseSpeedBox` (function) `progs/doomgeneric/g_game.h:74` `void G_DrawMouseSpeedBox(void);`
- `G_VanillaVersionCode` (function) `progs/doomgeneric/g_game.h:75` `int G_VanillaVersionCode(void);`

## progs/doomgeneric/gusconf.c
Depends on: `kernel/string.c`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`
- `MappingIndex` (function) `progs/doomgeneric/gusconf.c:43` `static unsigned int MappingIndex(void)`
- `SplitLine` (function) `progs/doomgeneric/gusconf.c:61` `static int SplitLine(char *line, char **fields, unsigned int max_fields)`
- `ParseLine` (function) `progs/doomgeneric/gusconf.c:108` `static void ParseLine(gus_config_t *config, char *line)`
- `ParseDMXConfig` (function) `progs/doomgeneric/gusconf.c:129` `static void ParseDMXConfig(char *dmxconf, gus_config_t *config)`
- `FreeDMXConfig` (function) `progs/doomgeneric/gusconf.c:165` `static void FreeDMXConfig(gus_config_t *config)`
- `ReadDMXConfig` (function) `progs/doomgeneric/gusconf.c:175` `static char *ReadDMXConfig(void)`
- `WriteTimidityConfig` (function) `progs/doomgeneric/gusconf.c:197` `static boolean WriteTimidityConfig(char *path, gus_config_t *config)`
- `GUS_WriteConfig` (function) `progs/doomgeneric/gusconf.c:244` `boolean GUS_WriteConfig(char *path)`

## progs/doomgeneric/hu_lib.c
Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/hu_lib.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/r_draw.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/v_video.h`
- `HUlib_init` (function) `progs/doomgeneric/hu_lib.c:36` `void HUlib_init(void)`
- `HUlib_clearTextLine` (function) `progs/doomgeneric/hu_lib.c:40` `void HUlib_clearTextLine(hu_textline_t* t)`
- `HUlib_initTextLine` (function) `progs/doomgeneric/hu_lib.c:48` `void
HUlib_initTextLine
( hu_textline_t*	t,
  int			x,
  int			y,
  patch_t**		f,
  int			sc )`
- `HUlib_addCharToTextLine` (function) `progs/doomgeneric/hu_lib.c:63` `boolean
HUlib_addCharToTextLine
( hu_textline_t*	t,
  char			ch )`
- `HUlib_delCharFromTextLine` (function) `progs/doomgeneric/hu_lib.c:80` `boolean HUlib_delCharFromTextLine(hu_textline_t* t)`
- `HUlib_drawTextLine` (function) `progs/doomgeneric/hu_lib.c:94` `void
HUlib_drawTextLine
( hu_textline_t*	l,
  boolean		drawcursor )`
- `HUlib_eraseTextLine` (function) `progs/doomgeneric/hu_lib.c:137` `void HUlib_eraseTextLine(hu_textline_t* l)` -- sorta called by HU_Erase and just better darn get things straight
- `HUlib_initSText` (function) `progs/doomgeneric/hu_lib.c:169` `void
HUlib_initSText
( hu_stext_t*	s,
  int		x,
  int		y,
  int		h,
  patch_t**	font,
  int		star...`
- `HUlib_addLineToSText` (function) `progs/doomgeneric/hu_lib.c:192` `void HUlib_addLineToSText(hu_stext_t* s)`
- `HUlib_addMessageToSText` (function) `progs/doomgeneric/hu_lib.c:209` `void
HUlib_addMessageToSText
( hu_stext_t*	s,
  char*		prefix,
  char*		msg )`
- `HUlib_drawSText` (function) `progs/doomgeneric/hu_lib.c:223` `void HUlib_drawSText(hu_stext_t* s)`
- `HUlib_eraseSText` (function) `progs/doomgeneric/hu_lib.c:246` `void HUlib_eraseSText(hu_stext_t* s)`
- `HUlib_initIText` (function) `progs/doomgeneric/hu_lib.c:262` `void
HUlib_initIText
( hu_itext_t*	it,
  int		x,
  int		y,
  patch_t**	font,
  int		startchar,
  ...`
- `HUlib_delCharFromIText` (function) `progs/doomgeneric/hu_lib.c:278` `void HUlib_delCharFromIText(hu_itext_t* it)` -- The following deletion routines adhere to the left margin restriction
- `HUlib_eraseLineFromIText` (function) `progs/doomgeneric/hu_lib.c:284` `void HUlib_eraseLineFromIText(hu_itext_t* it)`
- `HUlib_resetIText` (function) `progs/doomgeneric/hu_lib.c:291` `void HUlib_resetIText(hu_itext_t* it)` -- Resets left margin as well
- `HUlib_addPrefixToIText` (function) `progs/doomgeneric/hu_lib.c:298` `void
HUlib_addPrefixToIText
( hu_itext_t*	it,
  char*		str )`
- `HUlib_keyInIText` (function) `progs/doomgeneric/hu_lib.c:310` `boolean
HUlib_keyInIText
( hu_itext_t*	it,
  unsigned char ch )`
- `HUlib_drawIText` (function) `progs/doomgeneric/hu_lib.c:329` `void HUlib_drawIText(hu_itext_t* it)`
- `HUlib_eraseIText` (function) `progs/doomgeneric/hu_lib.c:340` `void HUlib_eraseIText(hu_itext_t* it)`

## progs/doomgeneric/hu_lib.h
Depends on: `progs/doomgeneric/r_defs.h`
Imported by: `progs/doomgeneric/hu_lib.c`, `progs/doomgeneric/hu_stuff.c`
- `HUlib_init` (function) `progs/doomgeneric/hu_lib.h:91` `void HUlib_init(void);` -- initializes heads-up widget library
- `HUlib_clearTextLine` (function) `progs/doomgeneric/hu_lib.h:98` `void HUlib_clearTextLine(hu_textline_t *t);` -- clear a line of text
- `HUlib_initTextLine` (function) `progs/doomgeneric/hu_lib.h:100` `void HUlib_initTextLine(hu_textline_t *t, int x, int y, patch_t **f, int sc);`
- `HUlib_drawTextLine` (function) `progs/doomgeneric/hu_lib.h:109` `void HUlib_drawTextLine(hu_textline_t *l, boolean drawcursor);` -- draws tline
- `HUlib_eraseTextLine` (function) `progs/doomgeneric/hu_lib.h:112` `void HUlib_eraseTextLine(hu_textline_t *l);` -- erases text line
- `HUlib_initSText` (function) `progs/doomgeneric/hu_lib.h:121` `void HUlib_initSText ( hu_stext_t* s, int x, int y, int h, patch_t** font, int startchar, boolean* on );`
- `HUlib_addLineToSText` (function) `progs/doomgeneric/hu_lib.h:131` `void HUlib_addLineToSText(hu_stext_t* s);` -- add a new line
- `HUlib_addMessageToSText` (function) `progs/doomgeneric/hu_lib.h:135` `void HUlib_addMessageToSText ( hu_stext_t* s, char* prefix, char* msg );`
- `HUlib_drawSText` (function) `progs/doomgeneric/hu_lib.h:141` `void HUlib_drawSText(hu_stext_t* s);` -- draws stext
- `HUlib_eraseSText` (function) `progs/doomgeneric/hu_lib.h:144` `void HUlib_eraseSText(hu_stext_t* s);` -- erases all stext lines
- `HUlib_initIText` (function) `progs/doomgeneric/hu_lib.h:148` `void HUlib_initIText ( hu_itext_t* it, int x, int y, patch_t** font, int startchar, boolean* on );`
- `HUlib_delCharFromIText` (function) `progs/doomgeneric/hu_lib.h:157` `void HUlib_delCharFromIText(hu_itext_t* it);` -- enforces left margin
- `HUlib_eraseLineFromIText` (function) `progs/doomgeneric/hu_lib.h:160` `void HUlib_eraseLineFromIText(hu_itext_t* it);` -- enforces left margin
- `HUlib_resetIText` (function) `progs/doomgeneric/hu_lib.h:163` `void HUlib_resetIText(hu_itext_t* it);` -- resets line and left margin
- `HUlib_addPrefixToIText` (function) `progs/doomgeneric/hu_lib.h:167` `void HUlib_addPrefixToIText ( hu_itext_t* it, char* str );`
- `HUlib_drawIText` (function) `progs/doomgeneric/hu_lib.h:177` `void HUlib_drawIText(hu_itext_t* it);`
- `HUlib_eraseIText` (function) `progs/doomgeneric/hu_lib.h:180` `void HUlib_eraseIText(hu_itext_t* it);` -- erases all itext lines

## progs/doomgeneric/hu_stuff.c
Depends on: `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/dstrings.h`, `progs/doomgeneric/hu_lib.h`, `progs/doomgeneric/hu_stuff.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_controls.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`
- `HU_Init` (function) `progs/doomgeneric/hu_stuff.c:286` `void HU_Init(void)`
- `HU_Stop` (function) `progs/doomgeneric/hu_stuff.c:303` `void HU_Stop(void)`
- `HU_Start` (function) `progs/doomgeneric/hu_stuff.c:308` `void HU_Start(void)`
- `HU_Drawer` (function) `progs/doomgeneric/hu_stuff.c:383` `void HU_Drawer(void)`
- `HU_Erase` (function) `progs/doomgeneric/hu_stuff.c:393` `void HU_Erase(void)`
- `HU_Ticker` (function) `progs/doomgeneric/hu_stuff.c:402` `void HU_Ticker(void)`
- `HU_queueChatChar` (function) `progs/doomgeneric/hu_stuff.c:482` `void HU_queueChatChar(char c)`
- `HU_dequeueChatChar` (function) `progs/doomgeneric/hu_stuff.c:495` `char HU_dequeueChatChar(void)`
- `HU_Responder` (function) `progs/doomgeneric/hu_stuff.c:512` `boolean HU_Responder(event_t *ev)`

## progs/doomgeneric/hu_stuff.h
Depends on: `progs/doomgeneric/d_event.h`
Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/f_finale.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/p_mobj.c`
- `HU_Init` (function) `progs/doomgeneric/hu_stuff.h:46` `void HU_Init(void);`
- `HU_Start` (function) `progs/doomgeneric/hu_stuff.h:47` `void HU_Start(void);`
- `HU_Ticker` (function) `progs/doomgeneric/hu_stuff.h:51` `void HU_Ticker(void);`
- `HU_Drawer` (function) `progs/doomgeneric/hu_stuff.h:52` `void HU_Drawer(void);`
- `HU_dequeueChatChar` (function) `progs/doomgeneric/hu_stuff.h:53` `char HU_dequeueChatChar(void);`
- `HU_Erase` (function) `progs/doomgeneric/hu_stuff.h:54` `void HU_Erase(void);`

## progs/doomgeneric/i_cdmus.c
Depends on: `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_cdmus.h`, `progs/pokemon/minios_stubs/SDL.h`
- `I_CDMusInit` (function) `progs/doomgeneric/i_cdmus.c:38` `int I_CDMusInit(void)`
- `I_CDMusPrintStartup` (function) `progs/doomgeneric/i_cdmus.c:92` `void I_CDMusPrintStartup(void)`
- `I_CDMusPlay` (function) `progs/doomgeneric/i_cdmus.c:107` `int I_CDMusPlay(int track)`
- `I_CDMusStop` (function) `progs/doomgeneric/i_cdmus.c:130` `int I_CDMusStop(void)`
- `I_CDMusResume` (function) `progs/doomgeneric/i_cdmus.c:145` `int I_CDMusResume(void)`
- `I_CDMusSetVolume` (function) `progs/doomgeneric/i_cdmus.c:160` `int I_CDMusSetVolume(int volume)`
- `I_CDMusFirstTrack` (function) `progs/doomgeneric/i_cdmus.c:169` `int I_CDMusFirstTrack(void)`
- `I_CDMusLastTrack` (function) `progs/doomgeneric/i_cdmus.c:202` `int I_CDMusLastTrack(void)`
- `I_CDMusTrackLength` (function) `progs/doomgeneric/i_cdmus.c:219` `int I_CDMusTrackLength(int track_num)`

## progs/doomgeneric/i_cdmus.h
Imported by: `progs/doomgeneric/i_cdmus.c`
- `I_CDMusInit` (function) `progs/doomgeneric/i_cdmus.h:31` `int I_CDMusInit(void);`
- `I_CDMusPrintStartup` (function) `progs/doomgeneric/i_cdmus.h:32` `void I_CDMusPrintStartup(void);`
- `I_CDMusPlay` (function) `progs/doomgeneric/i_cdmus.h:33` `int I_CDMusPlay(int track);`
- `I_CDMusStop` (function) `progs/doomgeneric/i_cdmus.h:34` `int I_CDMusStop(void);`
- `I_CDMusResume` (function) `progs/doomgeneric/i_cdmus.h:35` `int I_CDMusResume(void);`
- `I_CDMusSetVolume` (function) `progs/doomgeneric/i_cdmus.h:36` `int I_CDMusSetVolume(int volume);`
- `I_CDMusFirstTrack` (function) `progs/doomgeneric/i_cdmus.h:37` `int I_CDMusFirstTrack(void);`
- `I_CDMusLastTrack` (function) `progs/doomgeneric/i_cdmus.h:38` `int I_CDMusLastTrack(void);`
- `I_CDMusTrackLength` (function) `progs/doomgeneric/i_cdmus.h:39` `int I_CDMusTrackLength(int track);`

## progs/doomgeneric/i_endoom.c
Depends on: `kernel/string.c`, `progs/doomgeneric/config.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_video.h`
- `I_Endoom` (function) `progs/doomgeneric/i_endoom.c:36` `void I_Endoom(byte *endoom_data)`

## progs/doomgeneric/i_endoom.h
Imported by: `progs/doomgeneric/d_main.c`
- `I_Endoom` (function) `progs/doomgeneric/i_endoom.h:26` `void I_Endoom(byte *data);`

## progs/doomgeneric/i_input.c
Depends on: `kernel/string.c`, `progs/doomgeneric/config.h`, `progs/doomgeneric/deh_str.h`, `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_joystick.h`, `progs/doomgeneric/i_scale.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/i_timer.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_config.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/tables.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`
- `TranslateKey` (function) `progs/doomgeneric/i_input.c:225` `static unsigned char TranslateKey(unsigned char key)`
- `GetTypedChar` (function) `progs/doomgeneric/i_input.c:242` `static unsigned char GetTypedChar(unsigned char key)`
- `UpdateShiftStatus` (function) `progs/doomgeneric/i_input.c:263` `static void UpdateShiftStatus(int pressed, unsigned char key)`
- `I_GetEvent` (function) `progs/doomgeneric/i_input.c:279` `void I_GetEvent(void)`
- `I_InitInput` (function) `progs/doomgeneric/i_input.c:338` `void I_InitInput(void)`

## progs/doomgeneric/i_joystick.c
Depends on: `kernel/string.c`, `progs/doomgeneric/d_event.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_joystick.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_config.h`, `progs/doomgeneric/m_misc.h`, `progs/pokemon/minios_stubs/SDL.h`
- `I_ShutdownJoystick` (function) `progs/doomgeneric/i_joystick.c:77` `void I_ShutdownJoystick(void)`
- `IsValidAxis` (function) `progs/doomgeneric/i_joystick.c:90` `static boolean IsValidAxis(int axis)` -- ifdef ORIGCODE
- `I_InitJoystick` (function) `progs/doomgeneric/i_joystick.c:115` `void I_InitJoystick(void)`
- `IsAxisButton` (function) `progs/doomgeneric/i_joystick.c:171` `static boolean IsAxisButton(int physbutton)` -- ifdef ORIGCODE
- `ReadButtonState` (function) `progs/doomgeneric/i_joystick.c:203` `static int ReadButtonState(int vbutton)`
- `GetButtonsState` (function) `progs/doomgeneric/i_joystick.c:228` `static int GetButtonsState(void)`
- `GetAxisState` (function) `progs/doomgeneric/i_joystick.c:248` `static int GetAxisState(int axis, int invert)`
- `I_UpdateJoystick` (function) `progs/doomgeneric/i_joystick.c:321` `void I_UpdateJoystick(void)` -- endif
- `I_BindJoystickVariables` (function) `progs/doomgeneric/i_joystick.c:339` `void I_BindJoystickVariables(void)`

## progs/doomgeneric/i_joystick.h
Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_joystick.c`, `progs/doomgeneric/i_system.c`
- `I_InitJoystick` (function) `progs/doomgeneric/i_joystick.h:63` `void I_InitJoystick(void);`
- `I_ShutdownJoystick` (function) `progs/doomgeneric/i_joystick.h:64` `void I_ShutdownJoystick(void);`
- `I_UpdateJoystick` (function) `progs/doomgeneric/i_joystick.h:65` `void I_UpdateJoystick(void);`
- `I_BindJoystickVariables` (function) `progs/doomgeneric/i_joystick.h:67` `void I_BindJoystickVariables(void);`

## progs/doomgeneric/i_main.c
Depends on: `progs/doomgeneric/m_argv.h`
- `D_DoomMain` (function) `progs/doomgeneric/i_main.c:33` `void D_DoomMain (void);`
- `M_FindResponseFile` (function) `progs/doomgeneric/i_main.c:35` `void M_FindResponseFile(void);`
- `dg_Create` (function) `progs/doomgeneric/i_main.c:37` `void dg_Create();`
- `main` (function) `progs/doomgeneric/i_main.c:40` `int main(int argc, char **argv)`

## progs/doomgeneric/i_minios_sound.c
Depends on: `kernel/string.c`, `progs/doomgeneric/doomfeatures.h`, `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_sound.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`, `progs/minios_abi.h`
- `sys_tone_hw` (function) `progs/doomgeneric/i_minios_sound.c:32` `static long sys_tone_hw(unsigned f)`
- `sys_time` (function) `progs/doomgeneric/i_minios_sound.c:35` `static long sys_time(void)`
- `sys_pcm2_open` (function) `progs/doomgeneric/i_minios_sound.c:38` `static long sys_pcm2_open(long flags)`
- `sys_pcm2_write` (function) `progs/doomgeneric/i_minios_sound.c:41` `static long sys_pcm2_write(const void *buf, long len)`
- `sys_pcm2_close` (function) `progs/doomgeneric/i_minios_sound.c:44` `static void sys_pcm2_close(void)`
- `muted` (function) `progs/doomgeneric/i_minios_sound.c:51` `* pcm2 while sfx stay muted (effect tones ruined the melody);`
- `audio_ensure` (function) `progs/doomgeneric/i_minios_sound.c:68` `static void audio_ensure(void)`
- `audio_pump` (function) `progs/doomgeneric/i_minios_sound.c:77` `static void audio_pump(void)` -- SFX are muted on pcm2 (music only): effect tones ruined the melody, so audio_pump below only advances the shared...
- `audio_tone` (function) `progs/doomgeneric/i_minios_sound.c:85` `static void audio_tone(unsigned freq)`
- `audio_close` (function) `progs/doomgeneric/i_minios_sound.c:92` `static void audio_close(void)`
- `mus_read_varlen` (function) `progs/doomgeneric/i_minios_sound.c:169` `static int mus_read_varlen(mus_player_t *m, unsigned long *out)`
- `mus_next_block` (function) `progs/doomgeneric/i_minios_sound.c:183` `static int mus_next_block(mus_player_t *m, unsigned long *out)` -- Process one full block of events at the current tick and advance pos past * its delta.
- `mus_note_cmp` (function) `progs/doomgeneric/i_minios_sound.c:228` `static int mus_note_cmp(const void *a, const void *b)`
- `mus_build_chord` (function) `progs/doomgeneric/i_minios_sound.c:236` `static void mus_build_chord(mus_player_t *m)` -- Split the sounding notes into a bass pedal (the lowest note below the bass line) and the melody arpeggio (the...
- `mus_hold_tone` (function) `progs/doomgeneric/i_minios_sound.c:261` `static void mus_hold_tone(unsigned freq, unsigned long ms)` -- Hold a tone for the given number of milliseconds.
- `mus_play_chord` (function) `progs/doomgeneric/i_minios_sound.c:274` `static void mus_play_chord(mus_player_t *m)` -- Play one full cycle of the pseudo-polyphony: the bass pedal first, held long like the NES triangle voice, then the...
- `mus_advance` (function) `progs/doomgeneric/i_minios_sound.c:288` `static void mus_advance(mus_player_t *m, unsigned long ms)`
- `mus_render_pcm` (function) `progs/doomgeneric/i_minios_sound.c:320` `static void mus_render_pcm(mus_player_t *m, unsigned char *out, unsigned n)` -- Polyphonic pcm2 music: every sounding voice at once, as the score has it.
- `mus_render_push` (function) `progs/doomgeneric/i_minios_sound.c:359` `static void mus_render_push(mus_player_t *m, unsigned n)`
- `mus_advance_pcm` (function) `progs/doomgeneric/i_minios_sound.c:369` `static void mus_advance_pcm(mus_player_t *m)`
- `MUS_Init` (function) `progs/doomgeneric/i_minios_sound.c:410` `static boolean MUS_Init(void)`
- `MUS_Shutdown` (function) `progs/doomgeneric/i_minios_sound.c:415` `static void MUS_Shutdown(void)`
- `MUS_SetMusicVolume` (function) `progs/doomgeneric/i_minios_sound.c:422` `static void MUS_SetMusicVolume(int volume)`
- `MUS_Pause` (function) `progs/doomgeneric/i_minios_sound.c:424` `static void MUS_Pause(void)`
- `MUS_Resume` (function) `progs/doomgeneric/i_minios_sound.c:425` `static void MUS_Resume(void)`
- `MUS_RegisterSong` (function) `progs/doomgeneric/i_minios_sound.c:427` `static void *MUS_RegisterSong(void *data, int len)`
- `MUS_UnRegisterSong` (function) `progs/doomgeneric/i_minios_sound.c:442` `static void MUS_UnRegisterSong(void *handle)`
- `MUS_PlaySong` (function) `progs/doomgeneric/i_minios_sound.c:448` `static void MUS_PlaySong(void *handle, boolean looping)`
- `MUS_StopSong` (function) `progs/doomgeneric/i_minios_sound.c:469` `static void MUS_StopSong(void)`
- `MUS_MusicIsPlaying` (function) `progs/doomgeneric/i_minios_sound.c:474` `static boolean MUS_MusicIsPlaying(void)`
- `MUS_Poll` (function) `progs/doomgeneric/i_minios_sound.c:478` `static void MUS_Poll(void)`
- `PCSPK_Init` (function) `progs/doomgeneric/i_minios_sound.c:512` `static boolean PCSPK_Init(boolean use_sfx_prefix)`
- `PCSPK_Shutdown` (function) `progs/doomgeneric/i_minios_sound.c:519` `static void PCSPK_Shutdown(void)`
- `PCSPK_GetSfxLumpNum` (function) `progs/doomgeneric/i_minios_sound.c:529` `static int PCSPK_GetSfxLumpNum(sfxinfo_t *sfx)`
- `free_channel` (function) `progs/doomgeneric/i_minios_sound.c:540` `static void free_channel(int i)`
- `PCSPK_Update` (function) `progs/doomgeneric/i_minios_sound.c:549` `static void PCSPK_Update(void)`
- `PCSPK_UpdateSoundParams` (function) `progs/doomgeneric/i_minios_sound.c:587` `static void PCSPK_UpdateSoundParams(int ch, int v, int s)`
- `PCSPK_StartSound` (function) `progs/doomgeneric/i_minios_sound.c:591` `static int PCSPK_StartSound(sfxinfo_t *sfx, int channel, int vol, int sep)`
- `PCSPK_StopSound` (function) `progs/doomgeneric/i_minios_sound.c:641` `static void PCSPK_StopSound(int channel)`
- `PCSPK_SoundIsPlaying` (function) `progs/doomgeneric/i_minios_sound.c:647` `static boolean PCSPK_SoundIsPlaying(int channel)`
- `PCSPK_CacheSounds` (function) `progs/doomgeneric/i_minios_sound.c:653` `static void PCSPK_CacheSounds(sfxinfo_t *s, int n)`

## progs/doomgeneric/i_scale.c
Depends on: `kernel/string.c`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/z_zone.h`
- `I_InitScale` (function) `progs/doomgeneric/i_scale.c:61` `void I_InitScale(byte *_src_buffer, byte *_dest_buffer, int _dest_pitch)`
- `I_Scale1x` (function) `progs/doomgeneric/i_scale.c:75` `static boolean I_Scale1x(int x1, int y1, int x2, int y2)`
- `I_Scale2x` (function) `progs/doomgeneric/i_scale.c:105` `static boolean I_Scale2x(int x1, int y1, int x2, int y2)`
- `I_Scale3x` (function) `progs/doomgeneric/i_scale.c:146` `static boolean I_Scale3x(int x1, int y1, int x2, int y2)`
- `I_Scale4x` (function) `progs/doomgeneric/i_scale.c:191` `static boolean I_Scale4x(int x1, int y1, int x2, int y2)`
- `I_Scale5x` (function) `progs/doomgeneric/i_scale.c:240` `static boolean I_Scale5x(int x1, int y1, int x2, int y2)`
- `FindNearestColor` (function) `progs/doomgeneric/i_scale.c:295` `static int FindNearestColor(byte *palette, int r, int g, int b)`
- `GenerateStretchTable` (function) `progs/doomgeneric/i_scale.c:332` `static byte *GenerateStretchTable(byte *palette, int pct)`
- `I_InitStretchTables` (function) `progs/doomgeneric/i_scale.c:361` `static void I_InitStretchTables(byte *palette)`
- `I_InitSquashTable` (function) `progs/doomgeneric/i_scale.c:387` `static void I_InitSquashTable(byte *palette)`
- `I_ResetScaleTables` (function) `progs/doomgeneric/i_scale.c:404` `void I_ResetScaleTables(byte *palette)`
- `WriteBlendedLine1x` (function) `progs/doomgeneric/i_scale.c:434` `static inline void WriteBlendedLine1x(byte *dest, byte *src1, byte *src2, 
                      ...`
- `I_Stretch1x` (function) `progs/doomgeneric/i_scale.c:450` `static boolean I_Stretch1x(int x1, int y1, int x2, int y2)`
- `WriteLine2x` (function) `progs/doomgeneric/i_scale.c:507` `static inline void WriteLine2x(byte *dest, byte *src)`
- `WriteBlendedLine2x` (function) `progs/doomgeneric/i_scale.c:520` `static inline void WriteBlendedLine2x(byte *dest, byte *src1, byte *src2, 
                      ...`
- `I_Stretch2x` (function) `progs/doomgeneric/i_scale.c:539` `static boolean I_Stretch2x(int x1, int y1, int x2, int y2)`
- `WriteLine3x` (function) `progs/doomgeneric/i_scale.c:620` `static inline void WriteLine3x(byte *dest, byte *src)`
- `WriteBlendedLine3x` (function) `progs/doomgeneric/i_scale.c:634` `static inline void WriteBlendedLine3x(byte *dest, byte *src1, byte *src2, 
                      ...`
- `I_Stretch3x` (function) `progs/doomgeneric/i_scale.c:654` `static boolean I_Stretch3x(int x1, int y1, int x2, int y2)`
- `WriteLine4x` (function) `progs/doomgeneric/i_scale.c:759` `static inline void WriteLine4x(byte *dest, byte *src)`
- `WriteBlendedLine4x` (function) `progs/doomgeneric/i_scale.c:774` `static inline void WriteBlendedLine4x(byte *dest, byte *src1, byte *src2, 
                      ...`
- `I_Stretch4x` (function) `progs/doomgeneric/i_scale.c:795` `static boolean I_Stretch4x(int x1, int y1, int x2, int y2)`
- `WriteLine5x` (function) `progs/doomgeneric/i_scale.c:924` `static inline void WriteLine5x(byte *dest, byte *src)`
- `I_Stretch5x` (function) `progs/doomgeneric/i_scale.c:942` `static boolean I_Stretch5x(int x1, int y1, int x2, int y2)`
- `WriteSquashedLine1x` (function) `progs/doomgeneric/i_scale.c:1030` `static inline void WriteSquashedLine1x(byte *dest, byte *src)`
- `I_Squash1x` (function) `progs/doomgeneric/i_scale.c:1061` `static boolean I_Squash1x(int x1, int y1, int x2, int y2)`
- `WriteSquashedLine2x` (function) `progs/doomgeneric/i_scale.c:1102` `static inline void WriteSquashedLine2x(byte *dest, byte *src)`
- `I_Squash2x` (function) `progs/doomgeneric/i_scale.c:1160` `static boolean I_Squash2x(int x1, int y1, int x2, int y2)`
- `WriteSquashedLine3x` (function) `progs/doomgeneric/i_scale.c:1197` `static inline void WriteSquashedLine3x(byte *dest, byte *src)`
- `I_Squash3x` (function) `progs/doomgeneric/i_scale.c:1243` `static boolean I_Squash3x(int x1, int y1, int x2, int y2)`
- `WriteSquashedLine4x` (function) `progs/doomgeneric/i_scale.c:1279` `static inline void WriteSquashedLine4x(byte *dest, byte *src)`
- `I_Squash4x` (function) `progs/doomgeneric/i_scale.c:1354` `static boolean I_Squash4x(int x1, int y1, int x2, int y2)`
- `WriteSquashedLine5x` (function) `progs/doomgeneric/i_scale.c:1390` `static inline void WriteSquashedLine5x(byte *dest, byte *src)`
- `I_Squash5x` (function) `progs/doomgeneric/i_scale.c:1419` `static boolean I_Squash5x(int x1, int y1, int x2, int y2)`

## progs/doomgeneric/i_scale.h
Depends on: `progs/doomgeneric/doomtype.h`
Imported by: `progs/doomgeneric/i_input.c`
- `I_InitScale` (function) `progs/doomgeneric/i_scale.h:25` `void I_InitScale(byte *_src_buffer, byte *_dest_buffer, int _dest_pitch);`
- `I_ResetScaleTables` (function) `progs/doomgeneric/i_scale.h:26` `void I_ResetScaleTables(byte *palette);`

## progs/doomgeneric/i_sound.c
Depends on: `progs/doomgeneric/config.h`, `progs/doomgeneric/doomfeatures.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/gusconf.h`, `progs/doomgeneric/i_sound.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_config.h`
- `I_InitTimidityConfig` (function) `progs/doomgeneric/i_sound.c:65` `extern void I_InitTimidityConfig(void);`
- `SndDeviceInList` (function) `progs/doomgeneric/i_sound.c:116` `static boolean SndDeviceInList(snddevice_t device, snddevice_t *list,
                           ...`
- `InitSfxModule` (function) `progs/doomgeneric/i_sound.c:135` `static void InitSfxModule(boolean use_sfx_prefix)`
- `InitMusicModule` (function) `progs/doomgeneric/i_sound.c:163` `static void InitMusicModule(void)`
- `I_InitSound` (function) `progs/doomgeneric/i_sound.c:195` `void I_InitSound(boolean use_sfx_prefix)`
- `I_ShutdownSound` (function) `progs/doomgeneric/i_sound.c:250` `void I_ShutdownSound(void)`
- `I_GetSfxLumpNum` (function) `progs/doomgeneric/i_sound.c:263` `int I_GetSfxLumpNum(sfxinfo_t *sfxinfo)`
- `I_UpdateSound` (function) `progs/doomgeneric/i_sound.c:275` `void I_UpdateSound(void)`
- `CheckVolumeSeparation` (function) `progs/doomgeneric/i_sound.c:288` `static void CheckVolumeSeparation(int *vol, int *sep)`
- `I_UpdateSoundParams` (function) `progs/doomgeneric/i_sound.c:309` `void I_UpdateSoundParams(int channel, int vol, int sep)`
- `I_StartSound` (function) `progs/doomgeneric/i_sound.c:318` `int I_StartSound(sfxinfo_t *sfxinfo, int channel, int vol, int sep)`
- `I_StopSound` (function) `progs/doomgeneric/i_sound.c:331` `void I_StopSound(int channel)`
- `I_SoundIsPlaying` (function) `progs/doomgeneric/i_sound.c:339` `boolean I_SoundIsPlaying(int channel)`
- `I_PrecacheSounds` (function) `progs/doomgeneric/i_sound.c:351` `void I_PrecacheSounds(sfxinfo_t *sounds, int num_sounds)`
- `I_InitMusic` (function) `progs/doomgeneric/i_sound.c:359` `void I_InitMusic(void)`
- `I_ShutdownMusic` (function) `progs/doomgeneric/i_sound.c:363` `void I_ShutdownMusic(void)`
- `I_SetMusicVolume` (function) `progs/doomgeneric/i_sound.c:368` `void I_SetMusicVolume(int volume)`
- `I_PauseSong` (function) `progs/doomgeneric/i_sound.c:376` `void I_PauseSong(void)`
- `I_ResumeSong` (function) `progs/doomgeneric/i_sound.c:384` `void I_ResumeSong(void)`
- `I_RegisterSong` (function) `progs/doomgeneric/i_sound.c:392` `void *I_RegisterSong(void *data, int len)`
- `I_UnRegisterSong` (function) `progs/doomgeneric/i_sound.c:404` `void I_UnRegisterSong(void *handle)`
- `I_PlaySong` (function) `progs/doomgeneric/i_sound.c:412` `void I_PlaySong(void *handle, boolean looping)`
- `I_StopSong` (function) `progs/doomgeneric/i_sound.c:420` `void I_StopSong(void)`
- `I_MusicIsPlaying` (function) `progs/doomgeneric/i_sound.c:428` `boolean I_MusicIsPlaying(void)`
- `I_BindSoundVariables` (function) `progs/doomgeneric/i_sound.c:440` `void I_BindSoundVariables(void)`

## progs/doomgeneric/i_sound.h
Depends on: `progs/doomgeneric/doomtype.h`
Imported by: `progs/doomgeneric/i_minios_sound.c`, `progs/doomgeneric/i_sound.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/sounds.h`
- `I_InitSound` (function) `progs/doomgeneric/i_sound.h:152` `void I_InitSound(boolean use_sfx_prefix);`
- `I_ShutdownSound` (function) `progs/doomgeneric/i_sound.h:153` `void I_ShutdownSound(void);`
- `I_GetSfxLumpNum` (function) `progs/doomgeneric/i_sound.h:154` `int I_GetSfxLumpNum(sfxinfo_t *sfxinfo);`
- `I_UpdateSound` (function) `progs/doomgeneric/i_sound.h:155` `void I_UpdateSound(void);`
- `I_UpdateSoundParams` (function) `progs/doomgeneric/i_sound.h:156` `void I_UpdateSoundParams(int channel, int vol, int sep);`
- `I_StartSound` (function) `progs/doomgeneric/i_sound.h:157` `int I_StartSound(sfxinfo_t *sfxinfo, int channel, int vol, int sep);`
- `I_StopSound` (function) `progs/doomgeneric/i_sound.h:158` `void I_StopSound(int channel);`
- `I_PrecacheSounds` (function) `progs/doomgeneric/i_sound.h:160` `void I_PrecacheSounds(sfxinfo_t *sounds, int num_sounds);`
- `I_InitMusic` (function) `progs/doomgeneric/i_sound.h:217` `void I_InitMusic(void);`
- `I_ShutdownMusic` (function) `progs/doomgeneric/i_sound.h:218` `void I_ShutdownMusic(void);`
- `I_SetMusicVolume` (function) `progs/doomgeneric/i_sound.h:219` `void I_SetMusicVolume(int volume);`
- `I_PauseSong` (function) `progs/doomgeneric/i_sound.h:220` `void I_PauseSong(void);`
- `I_ResumeSong` (function) `progs/doomgeneric/i_sound.h:221` `void I_ResumeSong(void);`
- `I_RegisterSong` (function) `progs/doomgeneric/i_sound.h:222` `void *I_RegisterSong(void *data, int len);`
- `I_UnRegisterSong` (function) `progs/doomgeneric/i_sound.h:223` `void I_UnRegisterSong(void *handle);`
- `I_PlaySong` (function) `progs/doomgeneric/i_sound.h:224` `void I_PlaySong(void *handle, boolean looping);`
- `I_StopSong` (function) `progs/doomgeneric/i_sound.h:225` `void I_StopSong(void);`
- `I_BindSoundVariables` (function) `progs/doomgeneric/i_sound.h:235` `void I_BindSoundVariables(void);`

## progs/doomgeneric/i_system.c
Depends on: `kernel/string.c`, `progs/doomgeneric/config.h`, `progs/doomgeneric/deh_str.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_joystick.h`, `progs/doomgeneric/i_sound.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/i_timer.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_config.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`, `progs/pokemon/minios_stubs/SDL.h`
- `I_AtExit` (function) `progs/doomgeneric/i_system.c:73` `void I_AtExit(atexit_func_t func, boolean run_on_error)`
- `I_Tactile` (function) `progs/doomgeneric/i_system.c:87` `void I_Tactile(int on, int off, int total)`
- `AutoAllocMemory` (function) `progs/doomgeneric/i_system.c:95` `static byte *AutoAllocMemory(int *size, int default_ram, int min_ram)`
- `I_ZoneBase` (function) `progs/doomgeneric/i_system.c:133` `byte *I_ZoneBase (int *size)`
- `I_PrintBanner` (function) `progs/doomgeneric/i_system.c:166` `void I_PrintBanner(char *msg)`
- `I_PrintDivider` (function) `progs/doomgeneric/i_system.c:177` `void I_PrintDivider(void)`
- `I_PrintStartupBanner` (function) `progs/doomgeneric/i_system.c:189` `void I_PrintStartupBanner(char *gamedescription)`
- `I_ConsoleStdout` (function) `progs/doomgeneric/i_system.c:210` `boolean I_ConsoleStdout(void)`
- `I_Quit` (function) `progs/doomgeneric/i_system.c:246` `void I_Quit (void)`
- `ZenityAvailable` (function) `progs/doomgeneric/i_system.c:272` `static int ZenityAvailable(void)`
- `EscapeShellString` (function) `progs/doomgeneric/i_system.c:280` `static char *EscapeShellString(char *string)`
- `ZenityErrorBox` (function) `progs/doomgeneric/i_system.c:323` `static int ZenityErrorBox(char *message)`
- `I_Error` (function) `progs/doomgeneric/i_system.c:359` `void I_Error (char *error, ...)`
- `I_GetMemoryValue` (function) `progs/doomgeneric/i_system.c:502` `boolean I_GetMemoryValue(unsigned int offset, void *value, int size)`


Next: [API_p11.md](API_p11.md)
