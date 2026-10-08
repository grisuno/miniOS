# API (page 11 of 19)
Previous: [API_p10.md](API_p10.md)

## progs/doomgeneric/i_system.h
Depends on: `progs/doomgeneric/d_event.h`, `progs/doomgeneric/d_ticcmd.h`
Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_iwad.c`, `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/f_finale.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_joystick.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/m_argv.c`, `progs/doomgeneric/m_config.c`, `progs/doomgeneric/m_fixed.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/m_misc.c`, `progs/doomgeneric/p_enemy.c`, `progs/doomgeneric/p_inter.c`, `progs/doomgeneric/p_map.c`, `progs/doomgeneric/p_mobj.c`, `progs/doomgeneric/p_plats.c`, `progs/doomgeneric/p_saveg.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/p_sight.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/p_switch.c`, `progs/doomgeneric/r_bsp.c`, `progs/doomgeneric/r_data.c`, `progs/doomgeneric/r_draw.c`, `progs/doomgeneric/r_plane.c`, `progs/doomgeneric/r_segs.c`, `progs/doomgeneric/r_things.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/st_lib.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/v_video.c`, `progs/doomgeneric/w_wad.c`, `progs/doomgeneric/wi_stuff.c`, `progs/doomgeneric/z_zone.c`
- `I_Init` (function) `progs/doomgeneric/i_system.h:30` `void I_Init (void);` -- Called by DoomMain.
- `I_ZoneBase` (function) `progs/doomgeneric/i_system.h:35` `byte* I_ZoneBase (int *size);` -- Called by startup code to get the ammount of memory to malloc for the zone management.
- `I_BaseTiccmd` (function) `progs/doomgeneric/i_system.h:48` `ticcmd_t* I_BaseTiccmd (void);` -- Either returns a null ticcmd, or calls a loadable driver to build it.
- `I_Quit` (function) `progs/doomgeneric/i_system.h:53` `void I_Quit (void);` -- Called by M_Responder when quit is selected.
- `I_Error` (function) `progs/doomgeneric/i_system.h:55` `void I_Error (char *error, ...);`
- `I_Tactile` (function) `progs/doomgeneric/i_system.h:57` `void I_Tactile (int on, int off, int total);`
- `I_AtExit` (function) `progs/doomgeneric/i_system.h:65` `void I_AtExit(atexit_func_t func, boolean run_if_error);`
- `I_BindVariables` (function) `progs/doomgeneric/i_system.h:69` `void I_BindVariables(void);`
- `I_PrintStartupBanner` (function) `progs/doomgeneric/i_system.h:73` `void I_PrintStartupBanner(char *gamedescription);`
- `I_PrintBanner` (function) `progs/doomgeneric/i_system.h:77` `void I_PrintBanner(char *text);`
- `I_PrintDivider` (function) `progs/doomgeneric/i_system.h:81` `void I_PrintDivider(void);`

## progs/doomgeneric/i_timer.c
Depends on: `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_timer.h`
- `I_GetTicks` (function) `progs/doomgeneric/i_timer.c:37` `int I_GetTicks(void)`
- `I_GetTime` (function) `progs/doomgeneric/i_timer.c:42` `int  I_GetTime (void)`
- `I_GetTimeMS` (function) `progs/doomgeneric/i_timer.c:61` `int I_GetTimeMS(void)`
- `I_Sleep` (function) `progs/doomgeneric/i_timer.c:75` `void I_Sleep(int ms)`
- `I_WaitVBL` (function) `progs/doomgeneric/i_timer.c:83` `void I_WaitVBL(int count)`
- `I_InitTimer` (function) `progs/doomgeneric/i_timer.c:89` `void I_InitTimer(void)`

## progs/doomgeneric/i_timer.h
Imported by: `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/i_timer.c`, `progs/doomgeneric/m_menu.c`
- `I_GetTime` (function) `progs/doomgeneric/i_timer.h:27` `int I_GetTime (void);` -- Called by D_DoomLoop, returns current time in tics.
- `I_GetTimeMS` (function) `progs/doomgeneric/i_timer.h:30` `int I_GetTimeMS (void);` -- returns current time in ms
- `I_Sleep` (function) `progs/doomgeneric/i_timer.h:33` `void I_Sleep(int ms);` -- Pause for a specified number of ms
- `I_InitTimer` (function) `progs/doomgeneric/i_timer.h:36` `void I_InitTimer(void);` -- Initialize timer
- `I_WaitVBL` (function) `progs/doomgeneric/i_timer.h:39` `void I_WaitVBL(int count);` -- Wait for vertical retrace or pause a bit.

## progs/doomgeneric/i_video.c
Depends on: `progs/doomgeneric/config.h`, `progs/doomgeneric/d_event.h`, `progs/doomgeneric/d_main.h`, `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/tables.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/z_zone.h`
- `I_GetEvent` (function) `progs/doomgeneric/i_video.c:89` `void I_GetEvent(void);`
- `cmap_to_rgb565` (function) `progs/doomgeneric/i_video.c:131` `void cmap_to_rgb565(uint16_t * out, uint8_t * in, int in_pixels)`
- `cmap_to_fb` (function) `progs/doomgeneric/i_video.c:152` `void cmap_to_fb(uint8_t * out, uint8_t * in, int in_pixels)`
- `I_InitGraphics` (function) `progs/doomgeneric/i_video.c:179` `void I_InitGraphics (void)`
- `I_InitInput` (function) `progs/doomgeneric/i_video.c:228` `extern int I_InitInput(void);`
- `I_ShutdownGraphics` (function) `progs/doomgeneric/i_video.c:232` `void I_ShutdownGraphics (void)`
- `I_StartFrame` (function) `progs/doomgeneric/i_video.c:237` `void I_StartFrame (void)`
- `I_StartTic` (function) `progs/doomgeneric/i_video.c:242` `void I_StartTic (void)`
- `I_UpdateNoBlit` (function) `progs/doomgeneric/i_video.c:247` `void I_UpdateNoBlit (void)`
- `I_FinishUpdate` (function) `progs/doomgeneric/i_video.c:255` `void I_FinishUpdate (void)`
- `I_ReadScreen` (function) `progs/doomgeneric/i_video.c:302` `void I_ReadScreen (byte* scr)` -- I_ReadScreen
- `I_SetPalette` (function) `progs/doomgeneric/i_video.c:315` `void I_SetPalette (byte* palette)`
- `I_GetPaletteIndex` (function) `progs/doomgeneric/i_video.c:333` `int I_GetPaletteIndex (int r, int g, int b)`
- `I_BeginRead` (function) `progs/doomgeneric/i_video.c:369` `void I_BeginRead (void)`
- `I_EndRead` (function) `progs/doomgeneric/i_video.c:373` `void I_EndRead (void)`
- `I_SetWindowTitle` (function) `progs/doomgeneric/i_video.c:377` `void I_SetWindowTitle (char *title)`
- `I_GraphicsCheckCommandLine` (function) `progs/doomgeneric/i_video.c:382` `void I_GraphicsCheckCommandLine (void)`
- `I_SetGrabMouseCallback` (function) `progs/doomgeneric/i_video.c:386` `void I_SetGrabMouseCallback (grabmouse_callback_t func)`
- `I_EnableLoadingDisk` (function) `progs/doomgeneric/i_video.c:390` `void I_EnableLoadingDisk(void)`
- `I_BindVideoVariables` (function) `progs/doomgeneric/i_video.c:394` `void I_BindVideoVariables (void)`
- `I_DisplayFPSDots` (function) `progs/doomgeneric/i_video.c:398` `void I_DisplayFPSDots (boolean dots_on)`
- `I_CheckIsScreensaver` (function) `progs/doomgeneric/i_video.c:402` `void I_CheckIsScreensaver (void)`

## progs/doomgeneric/i_video.h
Depends on: `progs/doomgeneric/doomtype.h`
Imported by: `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/f_wipe.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/i_endoom.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_scale.c`, `progs/doomgeneric/i_sound.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/i_video.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/m_misc.c`, `progs/doomgeneric/r_defs.h`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/v_video.c`, `progs/doomgeneric/w_wad.c`
- `I_InitGraphics` (function) `progs/doomgeneric/i_video.h:97` `void I_InitGraphics (void);` -- Called by D_DoomMain, determines the hardware configuration and sets up the video mode
- `I_GraphicsCheckCommandLine` (function) `progs/doomgeneric/i_video.h:99` `void I_GraphicsCheckCommandLine(void);`
- `I_ShutdownGraphics` (function) `progs/doomgeneric/i_video.h:101` `void I_ShutdownGraphics(void);`
- `I_SetPalette` (function) `progs/doomgeneric/i_video.h:104` `void I_SetPalette (byte* palette);` -- Takes full 8 bit values.
- `I_GetPaletteIndex` (function) `progs/doomgeneric/i_video.h:105` `int I_GetPaletteIndex(int r, int g, int b);`
- `I_UpdateNoBlit` (function) `progs/doomgeneric/i_video.h:107` `void I_UpdateNoBlit (void);`
- `I_FinishUpdate` (function) `progs/doomgeneric/i_video.h:108` `void I_FinishUpdate (void);`
- `I_ReadScreen` (function) `progs/doomgeneric/i_video.h:110` `void I_ReadScreen (byte* scr);`
- `I_BeginRead` (function) `progs/doomgeneric/i_video.h:112` `void I_BeginRead (void);`
- `I_SetWindowTitle` (function) `progs/doomgeneric/i_video.h:114` `void I_SetWindowTitle(char *title);`
- `I_CheckIsScreensaver` (function) `progs/doomgeneric/i_video.h:116` `void I_CheckIsScreensaver(void);`
- `I_SetGrabMouseCallback` (function) `progs/doomgeneric/i_video.h:117` `void I_SetGrabMouseCallback(grabmouse_callback_t func);`
- `I_DisplayFPSDots` (function) `progs/doomgeneric/i_video.h:119` `void I_DisplayFPSDots(boolean dots_on);`
- `I_BindVideoVariables` (function) `progs/doomgeneric/i_video.h:120` `void I_BindVideoVariables(void);`
- `I_InitWindowTitle` (function) `progs/doomgeneric/i_video.h:122` `void I_InitWindowTitle(void);`
- `I_InitWindowIcon` (function) `progs/doomgeneric/i_video.h:123` `void I_InitWindowIcon(void);`
- `I_StartFrame` (function) `progs/doomgeneric/i_video.h:128` `void I_StartFrame (void);`
- `I_StartTic` (function) `progs/doomgeneric/i_video.h:133` `void I_StartTic (void);`
- `I_EnableLoadingDisk` (function) `progs/doomgeneric/i_video.h:137` `void I_EnableLoadingDisk(void);`

## progs/doomgeneric/info.c
Depends on: `progs/doomgeneric/info.h`, `progs/doomgeneric/m_fixed.h`, `progs/doomgeneric/p_mobj.h`, `progs/doomgeneric/sounds.h`
- `A_Light0` (function) `progs/doomgeneric/info.c:51` `void A_Light0();` -- Doesn't work with g++, needs actionf_p1
- `A_WeaponReady` (function) `progs/doomgeneric/info.c:52` `void A_WeaponReady();`
- `A_Lower` (function) `progs/doomgeneric/info.c:53` `void A_Lower();`
- `A_Raise` (function) `progs/doomgeneric/info.c:54` `void A_Raise();`
- `A_Punch` (function) `progs/doomgeneric/info.c:55` `void A_Punch();`
- `A_ReFire` (function) `progs/doomgeneric/info.c:56` `void A_ReFire();`
- `A_FirePistol` (function) `progs/doomgeneric/info.c:57` `void A_FirePistol();`
- `A_Light1` (function) `progs/doomgeneric/info.c:58` `void A_Light1();`
- `A_FireShotgun` (function) `progs/doomgeneric/info.c:59` `void A_FireShotgun();`
- `A_Light2` (function) `progs/doomgeneric/info.c:60` `void A_Light2();`
- `A_FireShotgun2` (function) `progs/doomgeneric/info.c:61` `void A_FireShotgun2();`
- `A_CheckReload` (function) `progs/doomgeneric/info.c:62` `void A_CheckReload();`
- `A_OpenShotgun2` (function) `progs/doomgeneric/info.c:63` `void A_OpenShotgun2();`
- `A_LoadShotgun2` (function) `progs/doomgeneric/info.c:64` `void A_LoadShotgun2();`
- `A_CloseShotgun2` (function) `progs/doomgeneric/info.c:65` `void A_CloseShotgun2();`
- `A_FireCGun` (function) `progs/doomgeneric/info.c:66` `void A_FireCGun();`
- `A_GunFlash` (function) `progs/doomgeneric/info.c:67` `void A_GunFlash();`
- `A_FireMissile` (function) `progs/doomgeneric/info.c:68` `void A_FireMissile();`
- `A_Saw` (function) `progs/doomgeneric/info.c:69` `void A_Saw();`
- `A_FirePlasma` (function) `progs/doomgeneric/info.c:70` `void A_FirePlasma();`
- `A_BFGsound` (function) `progs/doomgeneric/info.c:71` `void A_BFGsound();`
- `A_FireBFG` (function) `progs/doomgeneric/info.c:72` `void A_FireBFG();`
- `A_BFGSpray` (function) `progs/doomgeneric/info.c:73` `void A_BFGSpray();`
- `A_Explode` (function) `progs/doomgeneric/info.c:74` `void A_Explode();`
- `A_Pain` (function) `progs/doomgeneric/info.c:75` `void A_Pain();`
- `A_PlayerScream` (function) `progs/doomgeneric/info.c:76` `void A_PlayerScream();`
- `A_Fall` (function) `progs/doomgeneric/info.c:77` `void A_Fall();`
- `A_XScream` (function) `progs/doomgeneric/info.c:78` `void A_XScream();`
- `A_Look` (function) `progs/doomgeneric/info.c:79` `void A_Look();`
- `A_Chase` (function) `progs/doomgeneric/info.c:80` `void A_Chase();`
- `A_FaceTarget` (function) `progs/doomgeneric/info.c:81` `void A_FaceTarget();`
- `A_PosAttack` (function) `progs/doomgeneric/info.c:82` `void A_PosAttack();`
- `A_Scream` (function) `progs/doomgeneric/info.c:83` `void A_Scream();`
- `A_SPosAttack` (function) `progs/doomgeneric/info.c:84` `void A_SPosAttack();`
- `A_VileChase` (function) `progs/doomgeneric/info.c:85` `void A_VileChase();`
- `A_VileStart` (function) `progs/doomgeneric/info.c:86` `void A_VileStart();`
- `A_VileTarget` (function) `progs/doomgeneric/info.c:87` `void A_VileTarget();`
- `A_VileAttack` (function) `progs/doomgeneric/info.c:88` `void A_VileAttack();`
- `A_StartFire` (function) `progs/doomgeneric/info.c:89` `void A_StartFire();`
- `A_Fire` (function) `progs/doomgeneric/info.c:90` `void A_Fire();`
- `A_FireCrackle` (function) `progs/doomgeneric/info.c:91` `void A_FireCrackle();`
- `A_Tracer` (function) `progs/doomgeneric/info.c:92` `void A_Tracer();`
- `A_SkelWhoosh` (function) `progs/doomgeneric/info.c:93` `void A_SkelWhoosh();`
- `A_SkelFist` (function) `progs/doomgeneric/info.c:94` `void A_SkelFist();`
- `A_SkelMissile` (function) `progs/doomgeneric/info.c:95` `void A_SkelMissile();`
- `A_FatRaise` (function) `progs/doomgeneric/info.c:96` `void A_FatRaise();`
- `A_FatAttack1` (function) `progs/doomgeneric/info.c:97` `void A_FatAttack1();`
- `A_FatAttack2` (function) `progs/doomgeneric/info.c:98` `void A_FatAttack2();`
- `A_FatAttack3` (function) `progs/doomgeneric/info.c:99` `void A_FatAttack3();`
- `A_BossDeath` (function) `progs/doomgeneric/info.c:100` `void A_BossDeath();`
- `A_CPosAttack` (function) `progs/doomgeneric/info.c:101` `void A_CPosAttack();`
- `A_CPosRefire` (function) `progs/doomgeneric/info.c:102` `void A_CPosRefire();`
- `A_TroopAttack` (function) `progs/doomgeneric/info.c:103` `void A_TroopAttack();`
- `A_SargAttack` (function) `progs/doomgeneric/info.c:104` `void A_SargAttack();`
- `A_HeadAttack` (function) `progs/doomgeneric/info.c:105` `void A_HeadAttack();`
- `A_BruisAttack` (function) `progs/doomgeneric/info.c:106` `void A_BruisAttack();`
- `A_SkullAttack` (function) `progs/doomgeneric/info.c:107` `void A_SkullAttack();`
- `A_Metal` (function) `progs/doomgeneric/info.c:108` `void A_Metal();`
- `A_SpidRefire` (function) `progs/doomgeneric/info.c:109` `void A_SpidRefire();`
- `A_BabyMetal` (function) `progs/doomgeneric/info.c:110` `void A_BabyMetal();`
- `A_BspiAttack` (function) `progs/doomgeneric/info.c:111` `void A_BspiAttack();`
- `A_Hoof` (function) `progs/doomgeneric/info.c:112` `void A_Hoof();`
- `A_CyberAttack` (function) `progs/doomgeneric/info.c:113` `void A_CyberAttack();`
- `A_PainAttack` (function) `progs/doomgeneric/info.c:114` `void A_PainAttack();`
- `A_PainDie` (function) `progs/doomgeneric/info.c:115` `void A_PainDie();`
- `A_KeenDie` (function) `progs/doomgeneric/info.c:116` `void A_KeenDie();`
- `A_BrainPain` (function) `progs/doomgeneric/info.c:117` `void A_BrainPain();`
- `A_BrainScream` (function) `progs/doomgeneric/info.c:118` `void A_BrainScream();`
- `A_BrainDie` (function) `progs/doomgeneric/info.c:119` `void A_BrainDie();`
- `A_BrainAwake` (function) `progs/doomgeneric/info.c:120` `void A_BrainAwake();`
- `A_BrainSpit` (function) `progs/doomgeneric/info.c:121` `void A_BrainSpit();`
- `A_SpawnSound` (function) `progs/doomgeneric/info.c:122` `void A_SpawnSound();`
- `A_SpawnFly` (function) `progs/doomgeneric/info.c:123` `void A_SpawnFly();`
- `A_BrainExplode` (function) `progs/doomgeneric/info.c:124` `void A_BrainExplode();`

## progs/doomgeneric/m_argv.c
Depends on: `kernel/string.c`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_misc.h`
- `M_CheckParmWithArgs` (function) `progs/doomgeneric/m_argv.c:43` `int M_CheckParmWithArgs(char *check, int num_args)`
- `M_ParmExists` (function) `progs/doomgeneric/m_argv.c:63` `boolean M_ParmExists(char *check)`
- `M_CheckParm` (function) `progs/doomgeneric/m_argv.c:68` `int M_CheckParm(char *check)`
- `LoadResponseFile` (function) `progs/doomgeneric/m_argv.c:75` `static void LoadResponseFile(int argv_index)`
- `M_FindResponseFile` (function) `progs/doomgeneric/m_argv.c:235` `void M_FindResponseFile(void)`
- `M_GetExecutableName` (function) `progs/doomgeneric/m_argv.c:250` `char *M_GetExecutableName(void)`

## progs/doomgeneric/m_argv.h
Depends on: `progs/doomgeneric/doomtype.h`
Imported by: `progs/doomgeneric/d_iwad.c`, `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/doomgeneric_sdl.c`, `progs/doomgeneric/doomgeneric_soso.c`, `progs/doomgeneric/doomgeneric_sosox.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_main.c`, `progs/doomgeneric/i_scale.c`, `progs/doomgeneric/i_sound.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/i_video.c`, `progs/doomgeneric/m_argv.c`, `progs/doomgeneric/m_config.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/p_map.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/statdump.c`, `progs/doomgeneric/w_file.c`, `progs/doomgeneric/w_main.c`
- `M_CheckParm` (function) `progs/doomgeneric/m_argv.h:33` `int M_CheckParm (char* check);` -- Returns the position of the given parameter in the arg list (0 if not found).
- `M_CheckParmWithArgs` (function) `progs/doomgeneric/m_argv.h:37` `int M_CheckParmWithArgs(char *check, int num_args);` -- Same as M_CheckParm, but checks that num_args arguments are available following the specified argument.
- `M_FindResponseFile` (function) `progs/doomgeneric/m_argv.h:39` `void M_FindResponseFile(void);`
- `M_GetExecutableName` (function) `progs/doomgeneric/m_argv.h:47` `char *M_GetExecutableName(void);`

## progs/doomgeneric/m_bbox.c
Depends on: `progs/doomgeneric/m_bbox.h`
- `M_ClearBox` (function) `progs/doomgeneric/m_bbox.c:29` `void M_ClearBox (fixed_t *box)`
- `M_AddToBox` (function) `progs/doomgeneric/m_bbox.c:36` `void
M_AddToBox
( fixed_t*	box,
  fixed_t	x,
  fixed_t	y )`

## progs/doomgeneric/m_bbox.h
Depends on: `progs/doomgeneric/m_fixed.h`
Imported by: `progs/doomgeneric/m_bbox.c`, `progs/doomgeneric/p_map.c`, `progs/doomgeneric/p_maputl.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/r_bsp.c`, `progs/doomgeneric/r_main.c`, `progs/doomgeneric/v_video.c`
- `M_ClearBox` (function) `progs/doomgeneric/m_bbox.h:38` `void M_ClearBox (fixed_t* box);` -- Bounding box functions.
- `M_AddToBox` (function) `progs/doomgeneric/m_bbox.h:41` `void M_AddToBox ( fixed_t* box, fixed_t x, fixed_t y );`

## progs/doomgeneric/m_cheat.c
Depends on: `kernel/string.c`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/m_cheat.h`
- `cht_CheckCheat` (function) `progs/doomgeneric/m_cheat.c:35` `int
cht_CheckCheat
( cheatseq_t*	cht,
  char		key )`
- `cht_GetParam` (function) `progs/doomgeneric/m_cheat.c:82` `void
cht_GetParam
( cheatseq_t*	cht,
  char*		buffer )`

## progs/doomgeneric/m_cheat.h
Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/am_map.h`, `progs/doomgeneric/m_cheat.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/st_stuff.h`
- `cht_CheckCheat` (function) `progs/doomgeneric/m_cheat.h:51` `int cht_CheckCheat ( cheatseq_t* cht, char key );`
- `cht_GetParam` (function) `progs/doomgeneric/m_cheat.h:57` `void cht_GetParam ( cheatseq_t* cht, char* buffer );`

## progs/doomgeneric/m_config.c
Depends on: `kernel/string.c`, `progs/doomgeneric/config.h`, `progs/doomgeneric/doomfeatures.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/z_zone.h`
- `SearchCollection` (function) `progs/doomgeneric/m_config.c:1563` `static default_t *SearchCollection(default_collection_t *collection, char *name)`
- `SaveDefaultCollection` (function) `progs/doomgeneric/m_config.c:1609` `static void SaveDefaultCollection(default_collection_t *collection)`
- `ParseIntParameter` (function) `progs/doomgeneric/m_config.c:1716` `static int ParseIntParameter(char *strparm)`
- `SetVariable` (function) `progs/doomgeneric/m_config.c:1728` `static void SetVariable(default_t *def, char *value)`
- `LoadDefaultCollection` (function) `progs/doomgeneric/m_config.c:1771` `static void LoadDefaultCollection(default_collection_t *collection)`
- `M_SetConfigFilenames` (function) `progs/doomgeneric/m_config.c:1836` `void M_SetConfigFilenames(char *main_config, char *extra_config)`
- `M_SaveDefaults` (function) `progs/doomgeneric/m_config.c:1846` `void M_SaveDefaults (void)`
- `M_SaveDefaultsAlternate` (function) `progs/doomgeneric/m_config.c:1856` `void M_SaveDefaultsAlternate(char *main, char *extra)`
- `M_LoadDefaults` (function) `progs/doomgeneric/m_config.c:1881` `void M_LoadDefaults (void)`
- `GetDefaultForName` (function) `progs/doomgeneric/m_config.c:1937` `static default_t *GetDefaultForName(char *name)`
- `M_BindVariable` (function) `progs/doomgeneric/m_config.c:1964` `void M_BindVariable(char *name, void *location)`
- `M_SetVariable` (function) `progs/doomgeneric/m_config.c:1977` `boolean M_SetVariable(char *name, char *value)`
- `M_GetIntVariable` (function) `progs/doomgeneric/m_config.c:1995` `int M_GetIntVariable(char *name)`
- `M_GetStrVariable` (function) `progs/doomgeneric/m_config.c:2010` `const char *M_GetStrVariable(char *name)`
- `M_GetFloatVariable` (function) `progs/doomgeneric/m_config.c:2025` `float M_GetFloatVariable(char *name)`
- `GetDefaultConfigDir` (function) `progs/doomgeneric/m_config.c:2043` `static char *GetDefaultConfigDir(void)`
- `M_SetConfigDir` (function) `progs/doomgeneric/m_config.c:2059` `void M_SetConfigDir(char *dir)`
- `M_GetSaveGameDir` (function) `progs/doomgeneric/m_config.c:2087` `char *M_GetSaveGameDir(char *iwadname)`

## progs/doomgeneric/m_config.h
Depends on: `progs/doomgeneric/doomtype.h`
Imported by: `progs/doomgeneric/d_iwad.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_joystick.c`, `progs/doomgeneric/i_sound.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/m_controls.c`
- `M_LoadDefaults` (function) `progs/doomgeneric/m_config.h:25` `void M_LoadDefaults(void);`
- `M_SaveDefaults` (function) `progs/doomgeneric/m_config.h:26` `void M_SaveDefaults(void);`
- `M_SaveDefaultsAlternate` (function) `progs/doomgeneric/m_config.h:27` `void M_SaveDefaultsAlternate(char *main, char *extra);`
- `M_SetConfigDir` (function) `progs/doomgeneric/m_config.h:28` `void M_SetConfigDir(char *dir);`
- `M_BindVariable` (function) `progs/doomgeneric/m_config.h:29` `void M_BindVariable(char *name, void *variable);`
- `M_GetIntVariable` (function) `progs/doomgeneric/m_config.h:31` `int M_GetIntVariable(char *name);`
- `M_GetStrVariable` (function) `progs/doomgeneric/m_config.h:32` `const char *M_GetStrVariable(char *name);`
- `M_GetFloatVariable` (function) `progs/doomgeneric/m_config.h:33` `float M_GetFloatVariable(char *name);`
- `M_SetConfigFilenames` (function) `progs/doomgeneric/m_config.h:34` `void M_SetConfigFilenames(char *main_config, char *extra_config);`
- `M_GetSaveGameDir` (function) `progs/doomgeneric/m_config.h:35` `char *M_GetSaveGameDir(char *iwadname);`

## progs/doomgeneric/m_controls.c
Depends on: `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/m_config.h`, `progs/doomgeneric/m_misc.h`
- `M_BindBaseControls` (function) `progs/doomgeneric/m_controls.c:204` `void M_BindBaseControls(void)`
- `M_BindHereticControls` (function) `progs/doomgeneric/m_controls.c:241` `void M_BindHereticControls(void)`
- `M_BindHexenControls` (function) `progs/doomgeneric/m_controls.c:256` `void M_BindHexenControls(void)`
- `M_BindStrifeControls` (function) `progs/doomgeneric/m_controls.c:272` `void M_BindStrifeControls(void)`
- `M_BindWeaponControls` (function) `progs/doomgeneric/m_controls.c:307` `void M_BindWeaponControls(void)`
- `M_BindMapControls` (function) `progs/doomgeneric/m_controls.c:328` `void M_BindMapControls(void)`
- `M_BindMenuControls` (function) `progs/doomgeneric/m_controls.c:344` `void M_BindMenuControls(void)`
- `M_BindChatControls` (function) `progs/doomgeneric/m_controls.c:375` `void M_BindChatControls(unsigned int num_players)`
- `M_ApplyPlatformDefaults` (function) `progs/doomgeneric/m_controls.c:394` `void M_ApplyPlatformDefaults(void)`

## progs/doomgeneric/m_controls.h
Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/m_menu.c`
- `M_BindBaseControls` (function) `progs/doomgeneric/m_controls.h:156` `void M_BindBaseControls(void);`
- `M_BindHereticControls` (function) `progs/doomgeneric/m_controls.h:157` `void M_BindHereticControls(void);`
- `M_BindHexenControls` (function) `progs/doomgeneric/m_controls.h:158` `void M_BindHexenControls(void);`
- `M_BindStrifeControls` (function) `progs/doomgeneric/m_controls.h:159` `void M_BindStrifeControls(void);`
- `M_BindWeaponControls` (function) `progs/doomgeneric/m_controls.h:160` `void M_BindWeaponControls(void);`
- `M_BindMapControls` (function) `progs/doomgeneric/m_controls.h:161` `void M_BindMapControls(void);`
- `M_BindMenuControls` (function) `progs/doomgeneric/m_controls.h:162` `void M_BindMenuControls(void);`
- `M_BindChatControls` (function) `progs/doomgeneric/m_controls.h:163` `void M_BindChatControls(unsigned int num_players);`
- `M_ApplyPlatformDefaults` (function) `progs/doomgeneric/m_controls.h:165` `void M_ApplyPlatformDefaults(void);`

## progs/doomgeneric/m_fixed.c
Depends on: `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_fixed.h`
- `FixedMul` (function) `progs/doomgeneric/m_fixed.c:34` `fixed_t
FixedMul
( fixed_t	a,
  fixed_t	b )`
- `FixedDiv` (function) `progs/doomgeneric/m_fixed.c:47` `fixed_t FixedDiv(fixed_t a, fixed_t b)`

## progs/doomgeneric/m_fixed.h
Imported by: `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/info.c`, `progs/doomgeneric/m_bbox.h`, `progs/doomgeneric/m_fixed.c`, `progs/doomgeneric/p_mobj.h`, `progs/doomgeneric/p_pspr.h`, `progs/doomgeneric/r_defs.h`, `progs/doomgeneric/r_sky.c`, `progs/doomgeneric/tables.h`
- `FixedMul` (function) `progs/doomgeneric/m_fixed.h:34` `fixed_t FixedMul (fixed_t a, fixed_t b);`
- `FixedDiv` (function) `progs/doomgeneric/m_fixed.h:35` `fixed_t FixedDiv (fixed_t a, fixed_t b);`

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


Next: [API_p12.md](API_p12.md)
