# Subsystem: doomgeneric (page 5 of 12)
Previous: [KB_doomgeneric_p4.md](KB_doomgeneric_p4.md)

## progs/doomgeneric/i_swap.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `__I_SWAP__` (macro, line 21) `#define __I_SWAP__`
  - `SHORT` (macro, line 34) `#define SHORT(x)`
  - `LONG` (macro, line 35) `#define LONG(x)`
  - `SYS_LITTLE_ENDIAN` (macro, line 40) `#define SYS_LITTLE_ENDIAN`
  - `SYS_BIG_ENDIAN` (macro, line 42) `#define SYS_BIG_ENDIAN`
  - `SHORT` (macro, line 47) `#define SHORT(x)`
  - `LONG` (macro, line 48) `#define LONG(x)`
  - `SYS_LITTLE_ENDIAN` (macro, line 50) `#define SYS_LITTLE_ENDIAN`
- Imported by: `progs/doomgeneric/f_finale.c`, `progs/doomgeneric/hu_lib.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/m_misc.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/r_data.c`, `progs/doomgeneric/r_things.c`, `progs/doomgeneric/sha1.c`, `progs/doomgeneric/st_lib.c`, `progs/doomgeneric/v_video.c`, `progs/doomgeneric/w_wad.c`, `progs/doomgeneric/wi_stuff.c`

## progs/doomgeneric/i_system.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `atexit_listentry_s` (struct, line 64)
  - `atexit_listentry_t` (type_alias, line 60) `typedef struct atexit_listentry_s atexit_listentry_t;`
  - `I_AtExit` (function, line 73) `void I_AtExit(atexit_func_t func, boolean run_on_error)`
  - `I_Tactile` (function, line 87) `void I_Tactile(int on, int off, int total)`
  - `AutoAllocMemory` (function, line 95) `static byte *AutoAllocMemory(int *size, int default_ram, int min_ram)`
  - `I_ZoneBase` (function, line 133) `byte *I_ZoneBase (int *size)`
  - `I_PrintBanner` (function, line 166) `void I_PrintBanner(char *msg)`
  - `I_PrintDivider` (function, line 177) `void I_PrintDivider(void)`
  - `I_PrintStartupBanner` (function, line 189) `void I_PrintStartupBanner(char *gamedescription)`
  - `I_ConsoleStdout` (function, line 210) `boolean I_ConsoleStdout(void)`
  - `I_Quit` (function, line 246) `void I_Quit (void)`
  - `ZenityAvailable` (function, line 272) `static int ZenityAvailable(void)`
  - `EscapeShellString` (function, line 280) `static char *EscapeShellString(char *string)`
  - `ZenityErrorBox` (function, line 323) `static int ZenityErrorBox(char *message)`
  - `I_Error` (function, line 359) `void I_Error (char *error, ...)`
  - `I_GetMemoryValue` (function, line 502) `boolean I_GetMemoryValue(unsigned int offset, void *value, int size)`
  - `WIN32_LEAN_AND_MEAN` (macro, line 27) `#define WIN32_LEAN_AND_MEAN`
  - `DEFAULT_RAM` (macro, line 58) `#define DEFAULT_RAM`
  - `MIN_RAM` (macro, line 59) `#define MIN_RAM`
  - `ZENITY_BINARY` (macro, line 268) `#define ZENITY_BINARY`
  - `DOS_MEM_DUMP_SIZE` (macro, line 490) `#define DOS_MEM_DUMP_SIZE`
- Depends on: `kernel/string.c`, `progs/doomgeneric/config.h`, `progs/doomgeneric/deh_str.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_joystick.h`, `progs/doomgeneric/i_sound.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/i_timer.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_config.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`, `progs/pokemon/minios_stubs/SDL.h`

## progs/doomgeneric/i_system.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `I_Init` (function, line 30) `void I_Init (void);`
  - `I_ZoneBase` (function, line 35) `byte* I_ZoneBase (int *size);`
  - `I_BaseTiccmd` (function, line 48) `ticcmd_t* I_BaseTiccmd (void);`
  - `I_Quit` (function, line 53) `void I_Quit (void);`
  - `I_Error` (function, line 55) `void I_Error (char *error, ...);`
  - `I_Tactile` (function, line 57) `void I_Tactile (int on, int off, int total);`
  - `I_AtExit` (function, line 65) `void I_AtExit(atexit_func_t func, boolean run_if_error);`
  - `I_BindVariables` (function, line 69) `void I_BindVariables(void);`
  - `I_PrintStartupBanner` (function, line 73) `void I_PrintStartupBanner(char *gamedescription);`
  - `I_PrintBanner` (function, line 77) `void I_PrintBanner(char *text);`
  - `I_PrintDivider` (function, line 81) `void I_PrintDivider(void);`
  - `__I_SYSTEM__` (macro, line 21) `#define __I_SYSTEM__`
- Depends on: `progs/doomgeneric/d_event.h`, `progs/doomgeneric/d_ticcmd.h`
- Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_iwad.c`, `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/f_finale.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_joystick.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/m_argv.c`, `progs/doomgeneric/m_config.c`, `progs/doomgeneric/m_fixed.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/m_misc.c`, `progs/doomgeneric/p_enemy.c`, `progs/doomgeneric/p_inter.c`, `progs/doomgeneric/p_map.c`, `progs/doomgeneric/p_mobj.c`, `progs/doomgeneric/p_plats.c`, `progs/doomgeneric/p_saveg.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/p_sight.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/p_switch.c`, `progs/doomgeneric/r_bsp.c`, `progs/doomgeneric/r_data.c`, `progs/doomgeneric/r_draw.c`, `progs/doomgeneric/r_plane.c`, `progs/doomgeneric/r_segs.c`, `progs/doomgeneric/r_things.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/st_lib.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/v_video.c`, `progs/doomgeneric/w_wad.c`, `progs/doomgeneric/wi_stuff.c`, `progs/doomgeneric/z_zone.c`

## progs/doomgeneric/i_timer.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `I_GetTicks` (function, line 37) `int I_GetTicks(void)`
  - `I_GetTime` (function, line 42) `int  I_GetTime (void)`
  - `I_GetTimeMS` (function, line 61) `int I_GetTimeMS(void)`
  - `I_Sleep` (function, line 75) `void I_Sleep(int ms)`
  - `I_WaitVBL` (function, line 83) `void I_WaitVBL(int count)`
  - `I_InitTimer` (function, line 89) `void I_InitTimer(void)`
- Depends on: `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_timer.h`

## progs/doomgeneric/i_timer.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `I_GetTime` (function, line 27) `int I_GetTime (void);`
  - `I_GetTimeMS` (function, line 30) `int I_GetTimeMS (void);`
  - `I_Sleep` (function, line 33) `void I_Sleep(int ms);`
  - `I_InitTimer` (function, line 36) `void I_InitTimer(void);`
  - `I_WaitVBL` (function, line 39) `void I_WaitVBL(int count);`
  - `__I_TIMER__` (macro, line 21) `#define __I_TIMER__`
  - `TICRATE` (macro, line 23) `#define TICRATE`
- Imported by: `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/i_timer.c`, `progs/doomgeneric/m_menu.c`

## progs/doomgeneric/i_video.c
- Doc: Emacs style mode select   -*- C++ -*-
- Layer: utility
- Language: c
- Symbols:
  - `FB_BitField` (struct, line 54)
  - `FB_ScreenInfo` (struct, line 60)
  - `color` (struct, line 80)
  - `col_t` (struct, line 120)
  - `cmap_to_rgb565` (function, line 131) `void cmap_to_rgb565(uint16_t * out, uint8_t * in, int in_pixels)`
  - `cmap_to_fb` (function, line 152) `void cmap_to_fb(uint8_t * out, uint8_t * in, int in_pixels)`
  - `I_InitGraphics` (function, line 179) `void I_InitGraphics (void)`
  - `I_ShutdownGraphics` (function, line 232) `void I_ShutdownGraphics (void)`
  - `I_StartFrame` (function, line 237) `void I_StartFrame (void)`
  - `I_StartTic` (function, line 242) `void I_StartTic (void)`
  - `I_UpdateNoBlit` (function, line 247) `void I_UpdateNoBlit (void)`
  - `I_FinishUpdate` (function, line 255) `void I_FinishUpdate (void)`
  - `I_ReadScreen` (function, line 302) `void I_ReadScreen (byte* scr)`
  - `I_SetPalette` (function, line 315) `void I_SetPalette (byte* palette)`
  - `I_GetPaletteIndex` (function, line 333) `int I_GetPaletteIndex (int r, int g, int b)`
  - `I_BeginRead` (function, line 369) `void I_BeginRead (void)`
  - `I_EndRead` (function, line 373) `void I_EndRead (void)`
  - `I_SetWindowTitle` (function, line 377) `void I_SetWindowTitle (char *title)`
  - `I_GraphicsCheckCommandLine` (function, line 382) `void I_GraphicsCheckCommandLine (void)`
  - `I_SetGrabMouseCallback` (function, line 386) `void I_SetGrabMouseCallback (grabmouse_callback_t func)`
  - `I_EnableLoadingDisk` (function, line 390) `void I_EnableLoadingDisk(void)`
  - `I_BindVideoVariables` (function, line 394) `void I_BindVideoVariables (void)`
  - `I_DisplayFPSDots` (function, line 398) `void I_DisplayFPSDots (boolean dots_on)`
  - `I_CheckIsScreensaver` (function, line 402) `void I_CheckIsScreensaver (void)`
  - `I_GetEvent` (function, line 89) `void I_GetEvent(void);`
  - `I_InitInput` (function, line 228) `extern int I_InitInput(void);`
  - `minios_palette_dirty` (variable, line 52) `extern volatile int minios_palette_dirty;`
  - `GFX_RGB565` (macro, line 310) `#define GFX_RGB565(r, g, b)`
  - `GFX_RGB565_R` (macro, line 311) `#define GFX_RGB565_R(color)`
  - `GFX_RGB565_G` (macro, line 312) `#define GFX_RGB565_G(color)`
  - `GFX_RGB565_B` (macro, line 313) `#define GFX_RGB565_B(color)`
- Depends on: `progs/doomgeneric/config.h`, `progs/doomgeneric/d_event.h`, `progs/doomgeneric/d_main.h`, `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/tables.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/i_video.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `screen_mode_t` (struct, line 40)
  - `I_InitGraphics` (function, line 97) `void I_InitGraphics (void);`
  - `I_GraphicsCheckCommandLine` (function, line 99) `void I_GraphicsCheckCommandLine(void);`
  - `I_ShutdownGraphics` (function, line 101) `void I_ShutdownGraphics(void);`
  - `I_SetPalette` (function, line 104) `void I_SetPalette (byte* palette);`
  - `I_GetPaletteIndex` (function, line 105) `int I_GetPaletteIndex(int r, int g, int b);`
  - `I_UpdateNoBlit` (function, line 107) `void I_UpdateNoBlit (void);`
  - `I_FinishUpdate` (function, line 108) `void I_FinishUpdate (void);`
  - `I_ReadScreen` (function, line 110) `void I_ReadScreen (byte* scr);`
  - `I_BeginRead` (function, line 112) `void I_BeginRead (void);`
  - `I_SetWindowTitle` (function, line 114) `void I_SetWindowTitle(char *title);`
  - `I_CheckIsScreensaver` (function, line 116) `void I_CheckIsScreensaver(void);`
  - `I_SetGrabMouseCallback` (function, line 117) `void I_SetGrabMouseCallback(grabmouse_callback_t func);`
  - `I_DisplayFPSDots` (function, line 119) `void I_DisplayFPSDots(boolean dots_on);`
  - `I_BindVideoVariables` (function, line 120) `void I_BindVideoVariables(void);`
  - `I_InitWindowTitle` (function, line 122) `void I_InitWindowTitle(void);`
  - `I_InitWindowIcon` (function, line 123) `void I_InitWindowIcon(void);`
  - `I_StartFrame` (function, line 128) `void I_StartFrame (void);`
  - `I_StartTic` (function, line 133) `void I_StartTic (void);`
  - `I_EnableLoadingDisk` (function, line 137) `void I_EnableLoadingDisk(void);`
  - `video_driver` (variable, line 139) `extern char *video_driver;`
  - `screenvisible` (variable, line 140) `extern boolean screenvisible;`
  - `mouse_acceleration` (variable, line 142) `extern float mouse_acceleration;`
  - `mouse_threshold` (variable, line 143) `extern int mouse_threshold;`
  - `vanilla_keyboard_mapping` (variable, line 144) `extern int vanilla_keyboard_mapping;`
  - `screensaver_mode` (variable, line 145) `extern boolean screensaver_mode;`
  - `usegamma` (variable, line 146) `extern int usegamma;`
  - `I_VideoBuffer` (variable, line 147) `extern byte *I_VideoBuffer;`
  - `screen_width` (variable, line 149) `extern int screen_width;`
  - `screen_height` (variable, line 150) `extern int screen_height;`
  - `screen_bpp` (variable, line 151) `extern int screen_bpp;`
  - `fullscreen` (variable, line 152) `extern int fullscreen;`
  - `aspect_ratio_correct` (variable, line 153) `extern int aspect_ratio_correct;`
  - `show_diskicon` (variable, line 155) `extern int show_diskicon;`
  - `diskicon_readbytes` (variable, line 156) `extern int diskicon_readbytes;`
  - `__I_VIDEO__` (macro, line 21) `#define __I_VIDEO__`
  - `SCREENWIDTH` (macro, line 27) `#define SCREENWIDTH`
  - `SCREENHEIGHT` (macro, line 28) `#define SCREENHEIGHT`
  - `SCREENWIDTH_4_3` (macro, line 32) `#define SCREENWIDTH_4_3`
  - `SCREENHEIGHT_4_3` (macro, line 36) `#define SCREENHEIGHT_4_3`
  - `MAX_MOUSE_BUTTONS` (macro, line 38) `#define MAX_MOUSE_BUTTONS`
- Depends on: `progs/doomgeneric/doomtype.h`
- Imported by: `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/f_wipe.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/i_endoom.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_scale.c`, `progs/doomgeneric/i_sound.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/i_video.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/m_misc.c`, `progs/doomgeneric/r_defs.h`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/v_video.c`, `progs/doomgeneric/w_wad.c`

## progs/doomgeneric/icon.c
- Layer: utility
- Language: c

## progs/doomgeneric/info.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `A_Light0` (function, line 51) `void A_Light0();`
  - `A_WeaponReady` (function, line 52) `void A_WeaponReady();`
  - `A_Lower` (function, line 53) `void A_Lower();`
  - `A_Raise` (function, line 54) `void A_Raise();`
  - `A_Punch` (function, line 55) `void A_Punch();`
  - `A_ReFire` (function, line 56) `void A_ReFire();`
  - `A_FirePistol` (function, line 57) `void A_FirePistol();`
  - `A_Light1` (function, line 58) `void A_Light1();`
  - `A_FireShotgun` (function, line 59) `void A_FireShotgun();`
  - `A_Light2` (function, line 60) `void A_Light2();`
  - `A_FireShotgun2` (function, line 61) `void A_FireShotgun2();`
  - `A_CheckReload` (function, line 62) `void A_CheckReload();`
  - `A_OpenShotgun2` (function, line 63) `void A_OpenShotgun2();`
  - `A_LoadShotgun2` (function, line 64) `void A_LoadShotgun2();`
  - `A_CloseShotgun2` (function, line 65) `void A_CloseShotgun2();`
  - `A_FireCGun` (function, line 66) `void A_FireCGun();`
  - `A_GunFlash` (function, line 67) `void A_GunFlash();`
  - `A_FireMissile` (function, line 68) `void A_FireMissile();`
  - `A_Saw` (function, line 69) `void A_Saw();`
  - `A_FirePlasma` (function, line 70) `void A_FirePlasma();`
  - `A_BFGsound` (function, line 71) `void A_BFGsound();`
  - `A_FireBFG` (function, line 72) `void A_FireBFG();`
  - `A_BFGSpray` (function, line 73) `void A_BFGSpray();`
  - `A_Explode` (function, line 74) `void A_Explode();`
  - `A_Pain` (function, line 75) `void A_Pain();`
  - `A_PlayerScream` (function, line 76) `void A_PlayerScream();`
  - `A_Fall` (function, line 77) `void A_Fall();`
  - `A_XScream` (function, line 78) `void A_XScream();`
  - `A_Look` (function, line 79) `void A_Look();`
  - `A_Chase` (function, line 80) `void A_Chase();`
  - `A_FaceTarget` (function, line 81) `void A_FaceTarget();`
  - `A_PosAttack` (function, line 82) `void A_PosAttack();`
  - `A_Scream` (function, line 83) `void A_Scream();`
  - `A_SPosAttack` (function, line 84) `void A_SPosAttack();`
  - `A_VileChase` (function, line 85) `void A_VileChase();`
  - `A_VileStart` (function, line 86) `void A_VileStart();`
  - `A_VileTarget` (function, line 87) `void A_VileTarget();`
  - `A_VileAttack` (function, line 88) `void A_VileAttack();`
  - `A_StartFire` (function, line 89) `void A_StartFire();`
  - `A_Fire` (function, line 90) `void A_Fire();`
  - `A_FireCrackle` (function, line 91) `void A_FireCrackle();`
  - `A_Tracer` (function, line 92) `void A_Tracer();`
  - `A_SkelWhoosh` (function, line 93) `void A_SkelWhoosh();`
  - `A_SkelFist` (function, line 94) `void A_SkelFist();`
  - `A_SkelMissile` (function, line 95) `void A_SkelMissile();`
  - `A_FatRaise` (function, line 96) `void A_FatRaise();`
  - `A_FatAttack1` (function, line 97) `void A_FatAttack1();`
  - `A_FatAttack2` (function, line 98) `void A_FatAttack2();`
  - `A_FatAttack3` (function, line 99) `void A_FatAttack3();`
  - `A_BossDeath` (function, line 100) `void A_BossDeath();`
  - `A_CPosAttack` (function, line 101) `void A_CPosAttack();`
  - `A_CPosRefire` (function, line 102) `void A_CPosRefire();`
  - `A_TroopAttack` (function, line 103) `void A_TroopAttack();`
  - `A_SargAttack` (function, line 104) `void A_SargAttack();`
  - `A_HeadAttack` (function, line 105) `void A_HeadAttack();`
  - `A_BruisAttack` (function, line 106) `void A_BruisAttack();`
  - `A_SkullAttack` (function, line 107) `void A_SkullAttack();`
  - `A_Metal` (function, line 108) `void A_Metal();`
  - `A_SpidRefire` (function, line 109) `void A_SpidRefire();`
  - `A_BabyMetal` (function, line 110) `void A_BabyMetal();`
  - `A_BspiAttack` (function, line 111) `void A_BspiAttack();`
  - `A_Hoof` (function, line 112) `void A_Hoof();`
  - `A_CyberAttack` (function, line 113) `void A_CyberAttack();`
  - `A_PainAttack` (function, line 114) `void A_PainAttack();`
  - `A_PainDie` (function, line 115) `void A_PainDie();`
  - `A_KeenDie` (function, line 116) `void A_KeenDie();`
  - `A_BrainPain` (function, line 117) `void A_BrainPain();`
  - `A_BrainScream` (function, line 118) `void A_BrainScream();`
  - `A_BrainDie` (function, line 119) `void A_BrainDie();`
  - `A_BrainAwake` (function, line 120) `void A_BrainAwake();`
  - `A_BrainSpit` (function, line 121) `void A_BrainSpit();`
  - `A_SpawnSound` (function, line 122) `void A_SpawnSound();`
  - `A_SpawnFly` (function, line 123) `void A_SpawnFly();`
  - `A_BrainExplode` (function, line 124) `void A_BrainExplode();`
- Depends on: `progs/doomgeneric/info.h`, `progs/doomgeneric/m_fixed.h`, `progs/doomgeneric/p_mobj.h`, `progs/doomgeneric/sounds.h`

## progs/doomgeneric/info.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `state_t` (struct, line 1144)
  - `mobjinfo_t` (struct, line 1301)
  - `states` (variable, line 1156) `extern state_t states[NUMSTATES];`
  - `sprnames` (variable, line 1157) `extern char *sprnames[];`
  - `mobjinfo` (variable, line 1329) `extern mobjinfo_t mobjinfo[NUMMOBJTYPES];`
  - `__INFO__` (macro, line 22) `#define __INFO__`
- Depends on: `progs/doomgeneric/d_think.h`
- Imported by: `progs/doomgeneric/d_items.c`, `progs/doomgeneric/info.c`, `progs/doomgeneric/p_mobj.h`, `progs/doomgeneric/p_pspr.h`

## progs/doomgeneric/m_argv.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `M_CheckParmWithArgs` (function, line 43) `int M_CheckParmWithArgs(char *check, int num_args)`
  - `M_ParmExists` (function, line 63) `boolean M_ParmExists(char *check)`
  - `M_CheckParm` (function, line 68) `int M_CheckParm(char *check)`
  - `LoadResponseFile` (function, line 75) `static void LoadResponseFile(int argv_index)`
  - `M_FindResponseFile` (function, line 235) `void M_FindResponseFile(void)`
  - `M_GetExecutableName` (function, line 250) `char *M_GetExecutableName(void)`
  - `MAXARGVS` (macro, line 73) `#define MAXARGVS`
- Depends on: `kernel/string.c`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_misc.h`

## progs/doomgeneric/m_argv.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `M_CheckParm` (function, line 33) `int M_CheckParm (char* check);`
  - `M_CheckParmWithArgs` (function, line 37) `int M_CheckParmWithArgs(char *check, int num_args);`
  - `M_FindResponseFile` (function, line 39) `void M_FindResponseFile(void);`
  - `M_GetExecutableName` (function, line 47) `char *M_GetExecutableName(void);`
  - `myargc` (variable, line 28) `extern int myargc;`
  - `myargv` (variable, line 29) `extern char** myargv;`
  - `__M_ARGV__` (macro, line 21) `#define __M_ARGV__`
- Depends on: `progs/doomgeneric/doomtype.h`
- Imported by: `progs/doomgeneric/d_iwad.c`, `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/doomgeneric_sdl.c`, `progs/doomgeneric/doomgeneric_soso.c`, `progs/doomgeneric/doomgeneric_sosox.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_main.c`, `progs/doomgeneric/i_scale.c`, `progs/doomgeneric/i_sound.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/i_video.c`, `progs/doomgeneric/m_argv.c`, `progs/doomgeneric/m_config.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/p_map.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/statdump.c`, `progs/doomgeneric/w_file.c`, `progs/doomgeneric/w_main.c`

## progs/doomgeneric/m_bbox.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `M_ClearBox` (function, line 29) `void M_ClearBox (fixed_t *box)`
  - `M_AddToBox` (function, line 36) `void
M_AddToBox
( fixed_t*	box,
  fixed_t	x,
  fixed_t	y )`
- Depends on: `progs/doomgeneric/m_bbox.h`

## progs/doomgeneric/m_bbox.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `M_ClearBox` (function, line 38) `void M_ClearBox (fixed_t* box);`
  - `M_AddToBox` (function, line 41) `void M_AddToBox ( fixed_t* box, fixed_t x, fixed_t y );`
  - `__M_BBOX__` (macro, line 21) `#define __M_BBOX__`
- Depends on: `progs/doomgeneric/m_fixed.h`
- Imported by: `progs/doomgeneric/m_bbox.c`, `progs/doomgeneric/p_map.c`, `progs/doomgeneric/p_maputl.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/r_bsp.c`, `progs/doomgeneric/r_main.c`, `progs/doomgeneric/v_video.c`

## progs/doomgeneric/m_cheat.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `cht_CheckCheat` (function, line 35) `int
cht_CheckCheat
( cheatseq_t*	cht,
  char		key )`
  - `cht_GetParam` (function, line 82) `void
cht_GetParam
( cheatseq_t*	cht,
  char*		buffer )`
- Depends on: `kernel/string.c`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/m_cheat.h`

## progs/doomgeneric/m_cheat.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `cheatseq_t` (struct, line 35)
  - `cht_CheckCheat` (function, line 51) `int cht_CheckCheat ( cheatseq_t* cht, char key );`
  - `cht_GetParam` (function, line 57) `void cht_GetParam ( cheatseq_t* cht, char* buffer );`
  - `__M_CHEAT__` (macro, line 21) `#define __M_CHEAT__`
  - `CHEAT` (macro, line 29) `#define CHEAT(value, parameters)`
  - `MAX_CHEAT_LEN` (macro, line 32) `#define MAX_CHEAT_LEN`
  - `MAX_CHEAT_PARAMS` (macro, line 33) `#define MAX_CHEAT_PARAMS`
- Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/am_map.h`, `progs/doomgeneric/m_cheat.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/st_stuff.h`

## progs/doomgeneric/m_config.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: infrastructure
- Language: c
- Symbols:
  - `default_t` (struct, line 61)
  - `default_collection_t` (struct, line 88)
  - `SearchCollection` (function, line 1563) `static default_t *SearchCollection(default_collection_t *collection, char *name)`
  - `SaveDefaultCollection` (function, line 1609) `static void SaveDefaultCollection(default_collection_t *collection)`
  - `ParseIntParameter` (function, line 1716) `static int ParseIntParameter(char *strparm)`
  - `SetVariable` (function, line 1728) `static void SetVariable(default_t *def, char *value)`
  - `LoadDefaultCollection` (function, line 1771) `static void LoadDefaultCollection(default_collection_t *collection)`
  - `M_SetConfigFilenames` (function, line 1836) `void M_SetConfigFilenames(char *main_config, char *extra_config)`
  - `M_SaveDefaults` (function, line 1846) `void M_SaveDefaults (void)`
  - `M_SaveDefaultsAlternate` (function, line 1856) `void M_SaveDefaultsAlternate(char *main, char *extra)`
  - `M_LoadDefaults` (function, line 1881) `void M_LoadDefaults (void)`
  - `GetDefaultForName` (function, line 1937) `static default_t *GetDefaultForName(char *name)`
  - `M_BindVariable` (function, line 1964) `void M_BindVariable(char *name, void *location)`
  - `M_SetVariable` (function, line 1977) `boolean M_SetVariable(char *name, char *value)`
  - `M_GetIntVariable` (function, line 1995) `int M_GetIntVariable(char *name)`
  - `M_GetStrVariable` (function, line 2010) `const char *M_GetStrVariable(char *name)`
  - `M_GetFloatVariable` (function, line 2025) `float M_GetFloatVariable(char *name)`
  - `GetDefaultConfigDir` (function, line 2043) `static char *GetDefaultConfigDir(void)`
  - `M_SetConfigDir` (function, line 2059) `void M_SetConfigDir(char *dir)`
  - `M_GetSaveGameDir` (function, line 2087) `char *M_GetSaveGameDir(char *iwadname)`
  - `CONFIG_VARIABLE_GENERIC` (macro, line 95) `#define CONFIG_VARIABLE_GENERIC(name, type)`
  - `CONFIG_VARIABLE_KEY` (macro, line 98) `#define CONFIG_VARIABLE_KEY(name)`
  - `CONFIG_VARIABLE_INT` (macro, line 100) `#define CONFIG_VARIABLE_INT(name)`
  - `CONFIG_VARIABLE_INT_HEX` (macro, line 102) `#define CONFIG_VARIABLE_INT_HEX(name)`
  - `CONFIG_VARIABLE_FLOAT` (macro, line 104) `#define CONFIG_VARIABLE_FLOAT(name)`
  - `CONFIG_VARIABLE_STRING` (macro, line 106) `#define CONFIG_VARIABLE_STRING(name)`
- Depends on: `kernel/string.c`, `progs/doomgeneric/config.h`, `progs/doomgeneric/doomfeatures.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/m_config.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: infrastructure
- Language: h
- Symbols:
  - `M_LoadDefaults` (function, line 25) `void M_LoadDefaults(void);`
  - `M_SaveDefaults` (function, line 26) `void M_SaveDefaults(void);`
  - `M_SaveDefaultsAlternate` (function, line 27) `void M_SaveDefaultsAlternate(char *main, char *extra);`
  - `M_SetConfigDir` (function, line 28) `void M_SetConfigDir(char *dir);`
  - `M_BindVariable` (function, line 29) `void M_BindVariable(char *name, void *variable);`
  - `M_GetIntVariable` (function, line 31) `int M_GetIntVariable(char *name);`
  - `M_GetStrVariable` (function, line 32) `const char *M_GetStrVariable(char *name);`
  - `M_GetFloatVariable` (function, line 33) `float M_GetFloatVariable(char *name);`
  - `M_SetConfigFilenames` (function, line 34) `void M_SetConfigFilenames(char *main_config, char *extra_config);`
  - `M_GetSaveGameDir` (function, line 35) `char *M_GetSaveGameDir(char *iwadname);`
  - `configdir` (variable, line 37) `extern char *configdir;`
  - `__M_CONFIG__` (macro, line 21) `#define __M_CONFIG__`
- Depends on: `progs/doomgeneric/doomtype.h`
- Imported by: `progs/doomgeneric/d_iwad.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_joystick.c`, `progs/doomgeneric/i_sound.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/m_controls.c`

## progs/doomgeneric/m_controls.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `M_BindBaseControls` (function, line 204) `void M_BindBaseControls(void)`
  - `M_BindHereticControls` (function, line 241) `void M_BindHereticControls(void)`
  - `M_BindHexenControls` (function, line 256) `void M_BindHexenControls(void)`
  - `M_BindStrifeControls` (function, line 272) `void M_BindStrifeControls(void)`
  - `M_BindWeaponControls` (function, line 307) `void M_BindWeaponControls(void)`
  - `M_BindMapControls` (function, line 328) `void M_BindMapControls(void)`
  - `M_BindMenuControls` (function, line 344) `void M_BindMenuControls(void)`
  - `M_BindChatControls` (function, line 375) `void M_BindChatControls(unsigned int num_players)`
  - `M_ApplyPlatformDefaults` (function, line 394) `void M_ApplyPlatformDefaults(void)`
- Depends on: `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/m_config.h`, `progs/doomgeneric/m_misc.h`


Next: [KB_doomgeneric_p6.md](KB_doomgeneric_p6.md)
