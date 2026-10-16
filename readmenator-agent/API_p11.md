# API (page 11 of 21)
Previous: [API_p10.md](API_p10.md)

## progs/doomgeneric/doomgeneric_minios.c
Depends on: `kernel/string.c`, `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/s_sound.h`, `progs/minios_abi.h`
- `MINIOS_DOOM_BACKBUF_ADDR` (function) `progs/doomgeneric/doomgeneric_minios.c:4` `* MINIOS_DOOM_BACKBUF_ADDR (minios_abi.h);`
- `mini_parse_autoframes` (function) `progs/doomgeneric/doomgeneric_minios.c:24` `static void mini_parse_autoframes(int argc, char **argv)`
- `mini_parse_windowed` (function) `progs/doomgeneric/doomgeneric_minios.c:43` `static void mini_parse_windowed(int argc, char **argv)`
- `sys_time_ms` (function) `progs/doomgeneric/doomgeneric_minios.c:56` `static long sys_time_ms(void)`
- `sys_kbd` (function) `progs/doomgeneric/doomgeneric_minios.c:61` `static long sys_kbd(void)`
- `sys_palette` (function) `progs/doomgeneric/doomgeneric_minios.c:66` `static long sys_palette(const unsigned char *pal)`
- `sys_kbd_raw` (function) `progs/doomgeneric/doomgeneric_minios.c:71` `static long sys_kbd_raw(int on)`
- `sys_vga_mode` (function) `progs/doomgeneric/doomgeneric_minios.c:76` `static long sys_vga_mode(int on)`
- `sys_gfx_zoom` (function) `progs/doomgeneric/doomgeneric_minios.c:81` `static long sys_gfx_zoom(long mode)`
- `sys_doom_frame` (function) `progs/doomgeneric/doomgeneric_minios.c:86` `static long sys_doom_frame(void)`
- `load_vga_palette` (function) `progs/doomgeneric/doomgeneric_minios.c:110` `static void load_vga_palette(void)`
- `scancode_to_doom` (function) `progs/doomgeneric/doomgeneric_minios.c:123` `static unsigned char scancode_to_doom(unsigned char raw)`
- `kbd_enqueue` (function) `progs/doomgeneric/doomgeneric_minios.c:182` `static void kbd_enqueue(unsigned char doom_key, int pressed)`
- `kbd_poll` (function) `progs/doomgeneric/doomgeneric_minios.c:189` `static void kbd_poll(void)`
- `DG_Init` (function) `progs/doomgeneric/doomgeneric_minios.c:232` `void DG_Init(void)`
- `DG_DrawFrame` (function) `progs/doomgeneric/doomgeneric_minios.c:243` `void DG_DrawFrame(void)`
- `DG_SleepMs` (function) `progs/doomgeneric/doomgeneric_minios.c:274` `void DG_SleepMs(uint32_t ms)`
- `DG_GetTicksMs` (function) `progs/doomgeneric/doomgeneric_minios.c:280` `uint32_t DG_GetTicksMs(void)`
- `DG_GetKey` (function) `progs/doomgeneric/doomgeneric_minios.c:284` `int DG_GetKey(int *pressed, unsigned char *key)`
- `DG_SetWindowTitle` (function) `progs/doomgeneric/doomgeneric_minios.c:295` `void DG_SetWindowTitle(const char *title)`

## progs/doomgeneric/doomgeneric_sdl.c
Depends on: `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/m_argv.h`, `progs/pokemon/minios_stubs/SDL.h`
- `convertToDoomKey` (function) `progs/doomgeneric/doomgeneric_sdl.c:23` `static unsigned char convertToDoomKey(unsigned int key)`
- `addKeyToQueue` (function) `progs/doomgeneric/doomgeneric_sdl.c:63` `static void addKeyToQueue(int pressed, unsigned int keyCode)`
- `handleKeyInput` (function) `progs/doomgeneric/doomgeneric_sdl.c:72` `static void handleKeyInput()`
- `DG_Init` (function) `progs/doomgeneric/doomgeneric_sdl.c:93` `void DG_Init()`
- `DG_DrawFrame` (function) `progs/doomgeneric/doomgeneric_sdl.c:112` `void DG_DrawFrame()`
- `DG_SleepMs` (function) `progs/doomgeneric/doomgeneric_sdl.c:123` `void DG_SleepMs(uint32_t ms)`
- `DG_GetTicksMs` (function) `progs/doomgeneric/doomgeneric_sdl.c:128` `uint32_t DG_GetTicksMs()`
- `DG_GetKey` (function) `progs/doomgeneric/doomgeneric_sdl.c:133` `int DG_GetKey(int* pressed, unsigned char* doomKey)`
- `DG_SetWindowTitle` (function) `progs/doomgeneric/doomgeneric_sdl.c:152` `void DG_SetWindowTitle(const char * title)`

## progs/doomgeneric/doomgeneric_soso.c
Depends on: `kernel/string.c`, `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/m_argv.h`
- `convertToDoomKey` (function) `progs/doomgeneric/doomgeneric_soso.c:43` `static unsigned char convertToDoomKey(unsigned char scancode)`
- `addKeyToQueue` (function) `progs/doomgeneric/doomgeneric_soso.c:92` `static void addKeyToQueue(int pressed, unsigned char keyCode)`
- `disableRawMode` (function) `progs/doomgeneric/doomgeneric_soso.c:108` `void disableRawMode()`
- `enableRawMode` (function) `progs/doomgeneric/doomgeneric_soso.c:114` `void enableRawMode()`
- `DG_Init` (function) `progs/doomgeneric/doomgeneric_soso.c:124` `void DG_Init()`
- `handleKeyInput` (function) `progs/doomgeneric/doomgeneric_soso.c:186` `static void handleKeyInput()`
- `DG_DrawFrame` (function) `progs/doomgeneric/doomgeneric_soso.c:214` `void DG_DrawFrame()`
- `DG_SleepMs` (function) `progs/doomgeneric/doomgeneric_soso.c:227` `void DG_SleepMs(uint32_t ms)`
- `DG_GetTicksMs` (function) `progs/doomgeneric/doomgeneric_soso.c:232` `uint32_t DG_GetTicksMs()`
- `DG_GetKey` (function) `progs/doomgeneric/doomgeneric_soso.c:237` `int DG_GetKey(int* pressed, unsigned char* doomKey)`
- `DG_SetWindowTitle` (function) `progs/doomgeneric/doomgeneric_soso.c:258` `void DG_SetWindowTitle(const char * title)`

## progs/doomgeneric/doomgeneric_sosox.c
Depends on: `kernel/string.c`, `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/m_argv.h`
- `convert_to_doom_key` (function) `progs/doomgeneric/doomgeneric_sosox.c:39` `static unsigned char convert_to_doom_key(unsigned char scancode)`
- `add_key_to_queue` (function) `progs/doomgeneric/doomgeneric_sosox.c:88` `static void add_key_to_queue(int pressed, unsigned char key_code)`
- `disable_raw_mode` (function) `progs/doomgeneric/doomgeneric_sosox.c:102` `void disable_raw_mode()`
- `enable_raw_mode` (function) `progs/doomgeneric/doomgeneric_sosox.c:107` `void enable_raw_mode()`
- `DG_Init` (function) `progs/doomgeneric/doomgeneric_sosox.c:117` `void DG_Init()`
- `handle_key_input` (function) `progs/doomgeneric/doomgeneric_sosox.c:159` `static void handle_key_input()`
- `DG_DrawFrame` (function) `progs/doomgeneric/doomgeneric_sosox.c:187` `void DG_DrawFrame()`
- `DG_SleepMs` (function) `progs/doomgeneric/doomgeneric_sosox.c:225` `void DG_SleepMs(uint32_t ms)`
- `DG_GetTicksMs` (function) `progs/doomgeneric/doomgeneric_sosox.c:230` `uint32_t DG_GetTicksMs()`
- `DG_GetKey` (function) `progs/doomgeneric/doomgeneric_sosox.c:235` `int DG_GetKey(int* pressed, unsigned char* doomKey)`
- `DG_SetWindowTitle` (function) `progs/doomgeneric/doomgeneric_sosox.c:256` `void DG_SetWindowTitle(const char * title)`

## progs/doomgeneric/doomgeneric_win.c
Depends on: `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomkeys.h`
- `convertToDoomKey` (function) `progs/doomgeneric/doomgeneric_win.c:20` `static unsigned char convertToDoomKey(unsigned char key)`
- `addKeyToQueue` (function) `progs/doomgeneric/doomgeneric_win.c:59` `static void addKeyToQueue(int pressed, unsigned char keyCode)`
- `wndProc` (function) `progs/doomgeneric/doomgeneric_win.c:70` `static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)`
- `DG_Init` (function) `progs/doomgeneric/doomgeneric_win.c:95` `void DG_Init()`
- `DG_DrawFrame` (function) `progs/doomgeneric/doomgeneric_win.c:146` `void DG_DrawFrame()`
- `DG_SleepMs` (function) `progs/doomgeneric/doomgeneric_win.c:162` `void DG_SleepMs(uint32_t ms)`
- `DG_GetTicksMs` (function) `progs/doomgeneric/doomgeneric_win.c:167` `uint32_t DG_GetTicksMs()`
- `DG_GetKey` (function) `progs/doomgeneric/doomgeneric_win.c:172` `int DG_GetKey(int* pressed, unsigned char* doomKey)`
- `DG_SetWindowTitle` (function) `progs/doomgeneric/doomgeneric_win.c:193` `void DG_SetWindowTitle(const char * title)`

## progs/doomgeneric/doomgeneric_xlib.c
Depends on: `kernel/string.c`, `kernel/time.c`, `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomkeys.h`
- `convertToDoomKey` (function) `progs/doomgeneric/doomgeneric_xlib.c:27` `static unsigned char convertToDoomKey(unsigned int key)`
- `addKeyToQueue` (function) `progs/doomgeneric/doomgeneric_xlib.c:68` `static void addKeyToQueue(int pressed, unsigned int keyCode)`
- `DG_Init` (function) `progs/doomgeneric/doomgeneric_xlib.c:79` `void DG_Init()`
- `DG_DrawFrame` (function) `progs/doomgeneric/doomgeneric_xlib.c:127` `void DG_DrawFrame()`
- `DG_SleepMs` (function) `progs/doomgeneric/doomgeneric_xlib.c:172` `void DG_SleepMs(uint32_t ms)`
- `DG_GetTicksMs` (function) `progs/doomgeneric/doomgeneric_xlib.c:177` `uint32_t DG_GetTicksMs()`
- `DG_GetKey` (function) `progs/doomgeneric/doomgeneric_xlib.c:187` `int DG_GetKey(int* pressed, unsigned char* doomKey)`
- `DG_SetWindowTitle` (function) `progs/doomgeneric/doomgeneric_xlib.c:208` `void DG_SetWindowTitle(const char * title)`

## progs/doomgeneric/dummy.c
Depends on: `progs/doomgeneric/doomtype.h`
- `I_InitTimidityConfig` (function) `progs/doomgeneric/dummy.c:43` `void I_InitTimidityConfig(void)`

## progs/doomgeneric/f_finale.c
Depends on: `progs/doomgeneric/d_main.h`, `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/dstrings.h`, `progs/doomgeneric/hu_stuff.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`
- `F_StartFinale` (function) `progs/doomgeneric/f_finale.c:108` `void F_StartFinale (void)` -- F_StartFinale
- `F_Responder` (function) `progs/doomgeneric/f_finale.c:160` `boolean F_Responder (event_t *event)`
- `F_Ticker` (function) `progs/doomgeneric/f_finale.c:172` `void F_Ticker (void)` -- F_Ticker
- `F_TextWrite` (function) `progs/doomgeneric/f_finale.c:227` `void F_TextWrite (void)`
- `F_StartCast` (function) `progs/doomgeneric/f_finale.c:340` `void F_StartCast (void)` -- F_StartCast
- `F_CastTicker` (function) `progs/doomgeneric/f_finale.c:358` `void F_CastTicker (void)` -- F_CastTicker
- `F_CastResponder` (function) `progs/doomgeneric/f_finale.c:465` `boolean F_CastResponder (event_t* ev)`
- `F_CastPrint` (function) `progs/doomgeneric/f_finale.c:486` `void F_CastPrint (char* text)`
- `F_CastDrawer` (function) `progs/doomgeneric/f_finale.c:541` `void F_CastDrawer (void)`
- `F_DrawPatchCol` (function) `progs/doomgeneric/f_finale.c:572` `void
F_DrawPatchCol
( int		x,
  patch_t*	patch,
  int		col )`
- `F_BunnyScroll` (function) `progs/doomgeneric/f_finale.c:606` `void F_BunnyScroll (void)` -- F_BunnyScroll
- `F_ArtScreenDrawer` (function) `progs/doomgeneric/f_finale.c:661` `static void F_ArtScreenDrawer(void)`
- `F_Drawer` (function) `progs/doomgeneric/f_finale.c:702` `void F_Drawer (void)` -- F_Drawer

## progs/doomgeneric/f_finale.h
Depends on: `progs/doomgeneric/d_event.h`, `progs/doomgeneric/doomtype.h`
Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/g_game.c`
- `F_Ticker` (function) `progs/doomgeneric/f_finale.h:34` `void F_Ticker (void);` -- Called by main loop.
- `F_Drawer` (function) `progs/doomgeneric/f_finale.h:37` `void F_Drawer (void);` -- Called by main loop.
- `F_StartFinale` (function) `progs/doomgeneric/f_finale.h:40` `void F_StartFinale (void);`

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


Next: [API_p12.md](API_p12.md)
