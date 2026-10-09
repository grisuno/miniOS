# Subsystem: doomgeneric (page 11 of 12)
Previous: [KB_doomgeneric_p10.md](KB_doomgeneric_p10.md)

## progs/doomgeneric/st_stuff.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `ST_refreshBackground` (function, line 416) `void ST_refreshBackground(void)`
  - `ST_Responder` (function, line 439) `boolean
ST_Responder (event_t* ev)`
  - `ST_calcPainOffset` (function, line 665) `int ST_calcPainOffset(void)`
  - `ST_updateFaceWidget` (function, line 688) `void ST_updateFaceWidget(void)`
  - `ST_updateWidgets` (function, line 860) `void ST_updateWidgets(void)`
  - `ST_Ticker` (function, line 924) `void ST_Ticker (void)`
  - `ST_doPaletteStuff` (function, line 936) `void ST_doPaletteStuff(void)`
  - `ST_drawWidgets` (function, line 1001) `void ST_drawWidgets(boolean refresh)`
  - `ST_doRefresh` (function, line 1036) `void ST_doRefresh(void)`
  - `ST_diffDraw` (function, line 1049) `void ST_diffDraw(void)`
  - `ST_Drawer` (function, line 1055) `void ST_Drawer (boolean fullscreen, boolean refresh)`
  - `ST_loadUnloadGraphics` (function, line 1076) `static void ST_loadUnloadGraphics(load_callback_t callback)`
  - `ST_loadCallback` (function, line 1162) `static void ST_loadCallback(char *lumpname, patch_t **variable)`
  - `ST_loadGraphics` (function, line 1167) `void ST_loadGraphics(void)`
  - `ST_loadData` (function, line 1172) `void ST_loadData(void)`
  - `ST_unloadCallback` (function, line 1178) `static void ST_unloadCallback(char *lumpname, patch_t **variable)`
  - `ST_unloadGraphics` (function, line 1184) `void ST_unloadGraphics(void)`
  - `ST_unloadData` (function, line 1189) `void ST_unloadData(void)`
  - `ST_initData` (function, line 1194) `void ST_initData(void)`
  - `ST_createWidgets` (function, line 1227) `void ST_createWidgets(void)`
  - `ST_Start` (function, line 1389) `void ST_Start (void)`
  - `ST_Stop` (function, line 1401) `void ST_Stop (void)`
  - `ST_Init` (function, line 1411) `void ST_Init (void)`
  - `STARTREDPALS` (macro, line 68) `#define STARTREDPALS`
  - `STARTBONUSPALS` (macro, line 69) `#define STARTBONUSPALS`
  - `NUMREDPALS` (macro, line 70) `#define NUMREDPALS`
  - `NUMBONUSPALS` (macro, line 71) `#define NUMBONUSPALS`
  - `RADIATIONPAL` (macro, line 73) `#define RADIATIONPAL`
  - `ST_FACEPROBABILITY` (macro, line 77) `#define ST_FACEPROBABILITY`
  - `ST_TOGGLECHAT` (macro, line 80) `#define ST_TOGGLECHAT`
  - `ST_X` (macro, line 83) `#define ST_X`
  - `ST_X2` (macro, line 84) `#define ST_X2`
  - `ST_FX` (macro, line 86) `#define ST_FX`
  - `ST_FY` (macro, line 87) `#define ST_FY`
  - `ST_TALLNUMWIDTH` (macro, line 91) `#define ST_TALLNUMWIDTH`
  - `ST_NUMPAINFACES` (macro, line 94) `#define ST_NUMPAINFACES`
  - `ST_NUMSTRAIGHTFACES` (macro, line 95) `#define ST_NUMSTRAIGHTFACES`
  - `ST_NUMTURNFACES` (macro, line 96) `#define ST_NUMTURNFACES`
  - `ST_NUMSPECIALFACES` (macro, line 97) `#define ST_NUMSPECIALFACES`
  - `ST_FACESTRIDE` (macro, line 99) `#define ST_FACESTRIDE`
  - `ST_NUMEXTRAFACES` (macro, line 102) `#define ST_NUMEXTRAFACES`
  - `ST_NUMFACES` (macro, line 104) `#define ST_NUMFACES`
  - `ST_TURNOFFSET` (macro, line 107) `#define ST_TURNOFFSET`
  - `ST_OUCHOFFSET` (macro, line 108) `#define ST_OUCHOFFSET`
  - `ST_EVILGRINOFFSET` (macro, line 109) `#define ST_EVILGRINOFFSET`
  - `ST_RAMPAGEOFFSET` (macro, line 110) `#define ST_RAMPAGEOFFSET`
  - `ST_GODFACE` (macro, line 111) `#define ST_GODFACE`
  - `ST_DEADFACE` (macro, line 112) `#define ST_DEADFACE`
  - `ST_FACESX` (macro, line 114) `#define ST_FACESX`
  - `ST_FACESY` (macro, line 115) `#define ST_FACESY`
  - `ST_EVILGRINCOUNT` (macro, line 117) `#define ST_EVILGRINCOUNT`
  - `ST_STRAIGHTFACECOUNT` (macro, line 118) `#define ST_STRAIGHTFACECOUNT`
  - `ST_TURNCOUNT` (macro, line 119) `#define ST_TURNCOUNT`
  - `ST_OUCHCOUNT` (macro, line 120) `#define ST_OUCHCOUNT`
  - `ST_RAMPAGEDELAY` (macro, line 121) `#define ST_RAMPAGEDELAY`
  - `ST_MUCHPAIN` (macro, line 123) `#define ST_MUCHPAIN`
  - `ST_AMMOWIDTH` (macro, line 135) `#define ST_AMMOWIDTH`
  - `ST_AMMOX` (macro, line 136) `#define ST_AMMOX`
  - `ST_AMMOY` (macro, line 137) `#define ST_AMMOY`
  - `ST_HEALTHWIDTH` (macro, line 140) `#define ST_HEALTHWIDTH`
  - `ST_HEALTHX` (macro, line 141) `#define ST_HEALTHX`
  - `ST_HEALTHY` (macro, line 142) `#define ST_HEALTHY`
  - `ST_ARMSX` (macro, line 145) `#define ST_ARMSX`
  - `ST_ARMSY` (macro, line 146) `#define ST_ARMSY`
  - `ST_ARMSBGX` (macro, line 147) `#define ST_ARMSBGX`
  - `ST_ARMSBGY` (macro, line 148) `#define ST_ARMSBGY`
  - `ST_ARMSXSPACE` (macro, line 149) `#define ST_ARMSXSPACE`
  - `ST_ARMSYSPACE` (macro, line 150) `#define ST_ARMSYSPACE`
  - `ST_FRAGSX` (macro, line 153) `#define ST_FRAGSX`
  - `ST_FRAGSY` (macro, line 154) `#define ST_FRAGSY`
  - `ST_FRAGSWIDTH` (macro, line 155) `#define ST_FRAGSWIDTH`
  - `ST_ARMORWIDTH` (macro, line 158) `#define ST_ARMORWIDTH`
  - `ST_ARMORX` (macro, line 159) `#define ST_ARMORX`
  - `ST_ARMORY` (macro, line 160) `#define ST_ARMORY`
  - `ST_KEY0WIDTH` (macro, line 163) `#define ST_KEY0WIDTH`
  - `ST_KEY0HEIGHT` (macro, line 164) `#define ST_KEY0HEIGHT`
  - `ST_KEY0X` (macro, line 165) `#define ST_KEY0X`
  - `ST_KEY0Y` (macro, line 166) `#define ST_KEY0Y`
  - `ST_KEY1WIDTH` (macro, line 167) `#define ST_KEY1WIDTH`
  - `ST_KEY1X` (macro, line 168) `#define ST_KEY1X`
  - `ST_KEY1Y` (macro, line 169) `#define ST_KEY1Y`
  - `ST_KEY2WIDTH` (macro, line 170) `#define ST_KEY2WIDTH`
  - `ST_KEY2X` (macro, line 171) `#define ST_KEY2X`
  - `ST_KEY2Y` (macro, line 172) `#define ST_KEY2Y`
  - `ST_AMMO0WIDTH` (macro, line 175) `#define ST_AMMO0WIDTH`
  - `ST_AMMO0HEIGHT` (macro, line 176) `#define ST_AMMO0HEIGHT`
  - `ST_AMMO0X` (macro, line 177) `#define ST_AMMO0X`
  - `ST_AMMO0Y` (macro, line 178) `#define ST_AMMO0Y`
  - `ST_AMMO1WIDTH` (macro, line 179) `#define ST_AMMO1WIDTH`
  - `ST_AMMO1X` (macro, line 180) `#define ST_AMMO1X`
  - `ST_AMMO1Y` (macro, line 181) `#define ST_AMMO1Y`
  - `ST_AMMO2WIDTH` (macro, line 182) `#define ST_AMMO2WIDTH`
  - `ST_AMMO2X` (macro, line 183) `#define ST_AMMO2X`
  - `ST_AMMO2Y` (macro, line 184) `#define ST_AMMO2Y`
  - `ST_AMMO3WIDTH` (macro, line 185) `#define ST_AMMO3WIDTH`
  - `ST_AMMO3X` (macro, line 186) `#define ST_AMMO3X`
  - `ST_AMMO3Y` (macro, line 187) `#define ST_AMMO3Y`
  - `ST_MAXAMMO0WIDTH` (macro, line 191) `#define ST_MAXAMMO0WIDTH`
  - `ST_MAXAMMO0HEIGHT` (macro, line 192) `#define ST_MAXAMMO0HEIGHT`
  - `ST_MAXAMMO0X` (macro, line 193) `#define ST_MAXAMMO0X`
  - `ST_MAXAMMO0Y` (macro, line 194) `#define ST_MAXAMMO0Y`
  - `ST_MAXAMMO1WIDTH` (macro, line 195) `#define ST_MAXAMMO1WIDTH`
  - `ST_MAXAMMO1X` (macro, line 196) `#define ST_MAXAMMO1X`
  - `ST_MAXAMMO1Y` (macro, line 197) `#define ST_MAXAMMO1Y`
  - `ST_MAXAMMO2WIDTH` (macro, line 198) `#define ST_MAXAMMO2WIDTH`
  - `ST_MAXAMMO2X` (macro, line 199) `#define ST_MAXAMMO2X`
  - `ST_MAXAMMO2Y` (macro, line 200) `#define ST_MAXAMMO2Y`
  - `ST_MAXAMMO3WIDTH` (macro, line 201) `#define ST_MAXAMMO3WIDTH`
  - `ST_MAXAMMO3X` (macro, line 202) `#define ST_MAXAMMO3X`
  - `ST_MAXAMMO3Y` (macro, line 203) `#define ST_MAXAMMO3Y`
  - `ST_WEAPON0X` (macro, line 206) `#define ST_WEAPON0X`
  - `ST_WEAPON0Y` (macro, line 207) `#define ST_WEAPON0Y`
  - `ST_WEAPON1X` (macro, line 210) `#define ST_WEAPON1X`
  - `ST_WEAPON1Y` (macro, line 211) `#define ST_WEAPON1Y`
  - `ST_WEAPON2X` (macro, line 214) `#define ST_WEAPON2X`
  - `ST_WEAPON2Y` (macro, line 215) `#define ST_WEAPON2Y`
  - `ST_WEAPON3X` (macro, line 218) `#define ST_WEAPON3X`
  - `ST_WEAPON3Y` (macro, line 219) `#define ST_WEAPON3Y`
  - `ST_WEAPON4X` (macro, line 222) `#define ST_WEAPON4X`
  - `ST_WEAPON4Y` (macro, line 223) `#define ST_WEAPON4Y`
  - `ST_WEAPON5X` (macro, line 226) `#define ST_WEAPON5X`
  - `ST_WEAPON5Y` (macro, line 227) `#define ST_WEAPON5Y`
  - `ST_WPNSX` (macro, line 230) `#define ST_WPNSX`
  - `ST_WPNSY` (macro, line 231) `#define ST_WPNSY`
  - `ST_DETHX` (macro, line 234) `#define ST_DETHX`
  - `ST_DETHY` (macro, line 235) `#define ST_DETHY`
  - `ST_MSGTEXTX` (macro, line 241) `#define ST_MSGTEXTX`
  - `ST_MSGTEXTY` (macro, line 242) `#define ST_MSGTEXTY`
  - `ST_MSGWIDTH` (macro, line 244) `#define ST_MSGWIDTH`
  - `ST_MSGHEIGHT` (macro, line 246) `#define ST_MSGHEIGHT`
  - `ST_OUTTEXTX` (macro, line 248) `#define ST_OUTTEXTX`
  - `ST_OUTTEXTY` (macro, line 249) `#define ST_OUTTEXTY`
  - `ST_OUTWIDTH` (macro, line 252) `#define ST_OUTWIDTH`
  - `ST_OUTHEIGHT` (macro, line 254) `#define ST_OUTHEIGHT`
  - `ST_MAPTITLEX` (macro, line 256) `#define ST_MAPTITLEX`
  - `ST_MAPTITLEY` (macro, line 259) `#define ST_MAPTITLEY`
  - `ST_MAPHEIGHT` (macro, line 260) `#define ST_MAPHEIGHT`
- Depends on: `progs/doomgeneric/am_map.h`, `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/deh_misc.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/dstrings.h`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_cheat.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/p_inter.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/st_lib.h`, `progs/doomgeneric/st_stuff.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/st_stuff.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `ST_Ticker` (function, line 43) `void ST_Ticker (void);`
  - `ST_Drawer` (function, line 46) `void ST_Drawer (boolean fullscreen, boolean refresh);`
  - `ST_Start` (function, line 49) `void ST_Start (void);`
  - `ST_Init` (function, line 52) `void ST_Init (void);`
  - `st_backing_screen` (variable, line 76) `extern byte *st_backing_screen;`
  - `cheat_mus` (variable, line 77) `extern cheatseq_t cheat_mus;`
  - `cheat_god` (variable, line 78) `extern cheatseq_t cheat_god;`
  - `cheat_ammo` (variable, line 79) `extern cheatseq_t cheat_ammo;`
  - `cheat_ammonokey` (variable, line 80) `extern cheatseq_t cheat_ammonokey;`
  - `cheat_noclip` (variable, line 81) `extern cheatseq_t cheat_noclip;`
  - `cheat_commercial_noclip` (variable, line 82) `extern cheatseq_t cheat_commercial_noclip;`
  - `cheat_powerup` (variable, line 83) `extern cheatseq_t cheat_powerup[7];`
  - `cheat_choppers` (variable, line 84) `extern cheatseq_t cheat_choppers;`
  - `cheat_clev` (variable, line 85) `extern cheatseq_t cheat_clev;`
  - `cheat_mypos` (variable, line 86) `extern cheatseq_t cheat_mypos;`
  - `__STSTUFF_H__` (macro, line 22) `#define __STSTUFF_H__`
  - `ST_HEIGHT` (macro, line 30) `#define ST_HEIGHT`
  - `ST_WIDTH` (macro, line 31) `#define ST_WIDTH`
  - `ST_Y` (macro, line 32) `#define ST_Y`
- Depends on: `progs/doomgeneric/d_event.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/m_cheat.h`
- Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/p_mobj.c`, `progs/doomgeneric/st_lib.c`, `progs/doomgeneric/st_stuff.c`

## progs/doomgeneric/statdump.c
- Layer: utility
- Language: c
- Symbols:
  - `DiscoverGamemode` (function, line 71) `static void DiscoverGamemode(wbstartstruct_t *stats, int num_stats)`
  - `GetNumPlayers` (function, line 130) `static int GetNumPlayers(wbstartstruct_t *stats)`
  - `PrintBanner` (function, line 150) `static void PrintBanner(FILE *stream)`
  - `PrintPercentage` (function, line 155) `static void PrintPercentage(FILE *stream, int amount, int total)`
  - `PrintPlayerStats` (function, line 180) `static void PrintPlayerStats(FILE *stream, wbstartstruct_t *stats,
        int player_num)`
  - `PrintFragsTable` (function, line 213) `static void PrintFragsTable(FILE *stream, wbstartstruct_t *stats)`
  - `PrintLevelName` (function, line 272) `static void PrintLevelName(FILE *stream, int episode, int level)`
  - `PrintStats` (function, line 301) `static void PrintStats(FILE *stream, wbstartstruct_t *stats)`
  - `StatCopy` (function, line 333) `void StatCopy(wbstartstruct_t *stats)`
  - `StatDump` (function, line 343) `void StatDump(void)`
  - `MAX_CAPTURES` (macro, line 56) `#define MAX_CAPTURES`
- Depends on: `kernel/string.c`, `progs/doomgeneric/d_mode.h`, `progs/doomgeneric/d_player.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/statdump.h`

## progs/doomgeneric/statdump.h
- Layer: utility
- Language: h
- Symbols:
  - `StatCopy` (function, line 20) `void StatCopy(wbstartstruct_t *stats);`
  - `StatDump` (function, line 21) `void StatDump(void);`
  - `DOOM_STATDUMP_H` (macro, line 18) `#define DOOM_STATDUMP_H`
- Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/statdump.c`

## progs/doomgeneric/tables.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `SlopeDiv` (function, line 41) `int SlopeDiv(unsigned int num, unsigned int den)`
- Depends on: `progs/doomgeneric/tables.h`

## progs/doomgeneric/tables.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `angle_t` (type_alias, line 80) `typedef unsigned angle_t;`
  - `SlopeDiv` (function, line 92) `int SlopeDiv(unsigned int num, unsigned int den);`
  - `finesine` (variable, line 49) `extern const fixed_t finesine[5*FINEANGLES/4];`
  - `finecosine` (variable, line 52) `extern const fixed_t *finecosine;`
  - `finetangent` (variable, line 56) `extern const fixed_t finetangent[FINEANGLES/2];`
  - `tantoangle` (variable, line 87) `extern const angle_t tantoangle[SLOPERANGE+1];`
  - `__TABLES__` (macro, line 35) `#define __TABLES__`
  - `FINEANGLES` (macro, line 41) `#define FINEANGLES`
  - `FINEMASK` (macro, line 42) `#define FINEMASK`
  - `ANGLETOFINESHIFT` (macro, line 46) `#define ANGLETOFINESHIFT`
  - `ANG45` (macro, line 63) `#define ANG45`
  - `ANG90` (macro, line 64) `#define ANG90`
  - `ANG180` (macro, line 65) `#define ANG180`
  - `ANG270` (macro, line 66) `#define ANG270`
  - `ANG_MAX` (macro, line 67) `#define ANG_MAX`
  - `ANG1` (macro, line 69) `#define ANG1`
  - `ANG60` (macro, line 70) `#define ANG60`
  - `ANG1_X` (macro, line 75) `#define ANG1_X`
  - `SLOPERANGE` (macro, line 77) `#define SLOPERANGE`
  - `SLOPEBITS` (macro, line 78) `#define SLOPEBITS`
  - `DBITS` (macro, line 79) `#define DBITS`
- Depends on: `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/m_fixed.h`
- Imported by: `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_video.c`, `progs/doomgeneric/p_mobj.h`, `progs/doomgeneric/p_pspr.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/tables.c`

## progs/doomgeneric/v_patch.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `column_t` (type_alias, line 47) `typedef post_t column_t;`
  - `V_PATCH_H` (macro, line 21) `#define V_PATCH_H`
- Imported by: `progs/doomgeneric/r_defs.h`, `progs/doomgeneric/v_video.h`

## progs/doomgeneric/v_video.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `V_MarkRect` (function, line 69) `void V_MarkRect(int x, int y, int width, int height)`
  - `V_CopyRect` (function, line 85) `void V_CopyRect(int srcx, int srcy, byte *source,
                int width, int height,
        ...`
  - `V_SetPatchClipCallback` (function, line 129) `void V_SetPatchClipCallback(vpatchclipfunc_t func)`
  - `V_DrawPatch` (function, line 139) `void V_DrawPatch(int x, int y, patch_t *patch)`
  - `V_DrawPatchFlipped` (function, line 203) `void V_DrawPatchFlipped(int x, int y, patch_t *patch)`
  - `V_DrawPatchDirect` (function, line 268) `void V_DrawPatchDirect(int x, int y, patch_t *patch)`
  - `V_DrawTLPatch` (function, line 279) `void V_DrawTLPatch(int x, int y, patch_t * patch)`
  - `V_DrawXlaPatch` (function, line 329) `void V_DrawXlaPatch(int x, int y, patch_t * patch)`
  - `V_DrawAltTLPatch` (function, line 378) `void V_DrawAltTLPatch(int x, int y, patch_t * patch)`
  - `V_DrawShadowedPatch` (function, line 428) `void V_DrawShadowedPatch(int x, int y, patch_t *patch)`
  - `V_LoadTintTable` (function, line 482) `void V_LoadTintTable(void)`
  - `V_LoadXlaTable` (function, line 493) `void V_LoadXlaTable(void)`
  - `V_DrawBlock` (function, line 503) `void V_DrawBlock(int x, int y, int width, int height, byte *src)`
  - `V_DrawFilledBox` (function, line 529) `void V_DrawFilledBox(int x, int y, int w, int h, int c)`
  - `V_DrawHorizLine` (function, line 549) `void V_DrawHorizLine(int x, int y, int w, int c)`
  - `V_DrawVertLine` (function, line 562) `void V_DrawVertLine(int x, int y, int h, int c)`
  - `V_DrawBox` (function, line 576) `void V_DrawBox(int x, int y, int w, int h, int c)`
  - `V_DrawRawScreen` (function, line 589) `void V_DrawRawScreen(byte *raw)`
  - `V_Init` (function, line 597) `void V_Init (void)`
  - `V_UseBuffer` (function, line 606) `void V_UseBuffer(byte *buffer)`
  - `V_RestoreBuffer` (function, line 613) `void V_RestoreBuffer(void)`
  - `WritePCXfile` (function, line 653) `void WritePCXfile(char *filename, byte *data,
                  int width, int height,
          ...`
  - `error_fn` (function, line 711) `static void error_fn(png_structp p, png_const_charp s)`
  - `warning_fn` (function, line 716) `static void warning_fn(png_structp p, png_const_charp s)`
  - `WritePNGfile` (function, line 721) `void WritePNGfile(char *filename, byte *data,
                  int width, int height,
          ...`
  - `V_ScreenShot` (function, line 791) `void V_ScreenShot(char *format)`
  - `V_DrawMouseSpeedBox` (function, line 846) `void V_DrawMouseSpeedBox(int speed)`
  - `png_screenshots` (variable, line 800) `extern int png_screenshots;`
  - `usemouse` (variable, line 848) `extern int usemouse;`
  - `RANGECHECK` (macro, line 46) `#define RANGECHECK`
  - `MOUSE_SPEED_BOX_WIDTH` (macro, line 843) `#define MOUSE_SPEED_BOX_WIDTH`
  - `MOUSE_SPEED_BOX_HEIGHT` (macro, line 844) `#define MOUSE_SPEED_BOX_HEIGHT`
- Depends on: `kernel/string.c`, `progs/doomgeneric/config.h`, `progs/doomgeneric/deh_str.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_bbox.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/v_video.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `V_SetPatchClipCallback` (function, line 45) `void V_SetPatchClipCallback(vpatchclipfunc_t func);`
  - `V_Init` (function, line 49) `void V_Init (void);`
  - `V_CopyRect` (function, line 53) `void V_CopyRect(int srcx, int srcy, byte *source, int width, int height, int destx, int desty);`
  - `V_DrawPatch` (function, line 57) `void V_DrawPatch(int x, int y, patch_t *patch);`
  - `V_DrawPatchFlipped` (function, line 58) `void V_DrawPatchFlipped(int x, int y, patch_t *patch);`
  - `V_DrawTLPatch` (function, line 59) `void V_DrawTLPatch(int x, int y, patch_t *patch);`
  - `V_DrawAltTLPatch` (function, line 60) `void V_DrawAltTLPatch(int x, int y, patch_t * patch);`
  - `V_DrawShadowedPatch` (function, line 61) `void V_DrawShadowedPatch(int x, int y, patch_t *patch);`
  - `V_DrawXlaPatch` (function, line 62) `void V_DrawXlaPatch(int x, int y, patch_t * patch);`
  - `V_DrawPatchDirect` (function, line 63) `void V_DrawPatchDirect(int x, int y, patch_t *patch);`
  - `V_DrawBlock` (function, line 67) `void V_DrawBlock(int x, int y, int width, int height, byte *src);`
  - `V_MarkRect` (function, line 69) `void V_MarkRect(int x, int y, int width, int height);`
  - `V_DrawFilledBox` (function, line 71) `void V_DrawFilledBox(int x, int y, int w, int h, int c);`
  - `V_DrawHorizLine` (function, line 72) `void V_DrawHorizLine(int x, int y, int w, int c);`
  - `V_DrawVertLine` (function, line 73) `void V_DrawVertLine(int x, int y, int h, int c);`
  - `V_DrawBox` (function, line 74) `void V_DrawBox(int x, int y, int w, int h, int c);`
  - `V_DrawRawScreen` (function, line 78) `void V_DrawRawScreen(byte *raw);`
  - `V_UseBuffer` (function, line 82) `void V_UseBuffer(byte *buffer);`
  - `V_RestoreBuffer` (function, line 86) `void V_RestoreBuffer(void);`
  - `V_ScreenShot` (function, line 92) `void V_ScreenShot(char *format);`
  - `V_LoadTintTable` (function, line 97) `void V_LoadTintTable(void);`
  - `V_LoadXlaTable` (function, line 103) `void V_LoadXlaTable(void);`
  - `V_DrawMouseSpeedBox` (function, line 105) `void V_DrawMouseSpeedBox(int speed);`
  - `dirtybox` (variable, line 37) `extern int dirtybox[4];`
  - `tinttable` (variable, line 39) `extern byte *tinttable;`
  - `__V_VIDEO__` (macro, line 23) `#define __V_VIDEO__`
  - `CENTERY` (macro, line 34) `#define CENTERY`
- Depends on: `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/v_patch.h`
- Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/f_finale.c`, `progs/doomgeneric/f_wipe.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/hu_lib.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_video.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/m_misc.c`, `progs/doomgeneric/r_draw.c`, `progs/doomgeneric/st_lib.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/v_video.c`, `progs/doomgeneric/wi_stuff.c`

## progs/doomgeneric/w_checksum.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `GetFileNumber` (function, line 31) `static int GetFileNumber(wad_file_t *handle)`
  - `ChecksumAddLump` (function, line 57) `static void ChecksumAddLump(sha1_context_t *sha1_context, lumpinfo_t *lump)`
  - `W_Checksum` (function, line 68) `void W_Checksum(sha1_digest_t digest)`
- Depends on: `kernel/string.c`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/sha1.h`, `progs/doomgeneric/w_checksum.h`, `progs/doomgeneric/w_wad.h`

## progs/doomgeneric/w_checksum.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `W_Checksum` (function, line 24) `extern void W_Checksum(sha1_digest_t digest);`
  - `W_CHECKSUM_H` (macro, line 20) `#define W_CHECKSUM_H`
- Depends on: `progs/doomgeneric/doomtype.h`
- Imported by: `progs/doomgeneric/d_net.c`, `progs/doomgeneric/w_checksum.c`

## progs/doomgeneric/w_file.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `W_OpenFile` (function, line 53) `wad_file_t *W_OpenFile(char *path)`
  - `W_CloseFile` (function, line 85) `void W_CloseFile(wad_file_t *wad)`
  - `W_Read` (function, line 90) `size_t W_Read(wad_file_t *wad, unsigned int offset,
              void *buffer, size_t buffer_len)`
  - `stdc_wad_file` (variable, line 28) `extern wad_file_class_t stdc_wad_file;`
  - `win32_wad_file` (variable, line 32) `extern wad_file_class_t win32_wad_file;`
  - `posix_wad_file` (variable, line 37) `extern wad_file_class_t posix_wad_file;`
- Depends on: `progs/doomgeneric/config.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/w_file.h`

## progs/doomgeneric/w_file.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `_wad_file_s` (struct, line 46)
  - `wad_file_class_t` (struct, line 28)
  - `wad_file_t` (type_alias, line 25) `typedef struct _wad_file_s wad_file_t;`
  - `W_OpenFile` (function, line 65) `wad_file_t *W_OpenFile(char *path);`
  - `W_CloseFile` (function, line 69) `void W_CloseFile(wad_file_t *wad);`
  - `W_Read` (function, line 75) `size_t W_Read(wad_file_t *wad, unsigned int offset, void *buffer, size_t buffer_len);`
  - `__W_FILE__` (macro, line 21) `#define __W_FILE__`
- Depends on: `progs/doomgeneric/doomtype.h`
- Imported by: `progs/doomgeneric/w_file.c`, `progs/doomgeneric/w_file_stdc.c`, `progs/doomgeneric/w_wad.h`

## progs/doomgeneric/w_file_stdc.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `stdc_wad_file_t` (struct, line 25)
  - `W_StdC_OpenFile` (function, line 33) `static wad_file_t *W_StdC_OpenFile(char *path)`
  - `W_StdC_CloseFile` (function, line 56) `static void W_StdC_CloseFile(wad_file_t *wad)`
  - `W_StdC_Read` (function, line 69) `size_t W_StdC_Read(wad_file_t *wad, unsigned int offset,
                   void *buffer, size_t ...`
  - `stdc_wad_file` (variable, line 31) `extern wad_file_class_t stdc_wad_file;`
- Depends on: `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/w_file.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/w_main.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `W_ParseCommandLine` (function, line 30) `boolean W_ParseCommandLine(void)`
- Depends on: `progs/doomgeneric/d_iwad.h`, `progs/doomgeneric/doomfeatures.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/w_main.h`, `progs/doomgeneric/w_merge.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/w_main.h
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it...
- Layer: utility
- Language: h
- Symbols:
  - `W_MAIN_H` (macro, line 19) `#define W_MAIN_H`
- Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/w_main.c`

## progs/doomgeneric/w_merge.h
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it...
- Layer: utility
- Language: h
- Symbols:
  - `W_MergeFile` (function, line 29) `void W_MergeFile(char *filename);`
  - `W_NWTMergeFile` (function, line 33) `void W_NWTMergeFile(char *filename, int flags);`
  - `W_NWTDashMerge` (function, line 37) `void W_NWTDashMerge(char *filename);`
  - `W_PrintDirectory` (function, line 41) `void W_PrintDirectory(void);`
  - `W_MERGE_H` (macro, line 22) `#define W_MERGE_H`
  - `W_NWT_MERGE_SPRITES` (macro, line 24) `#define W_NWT_MERGE_SPRITES`
  - `W_NWT_MERGE_FLATS` (macro, line 25) `#define W_NWT_MERGE_FLATS`
- Imported by: `progs/doomgeneric/w_main.c`

## progs/doomgeneric/w_wad.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `W_LumpNameHash` (function, line 72) `unsigned int W_LumpNameHash(const char *s)`
  - `ExtendLumpInfo` (function, line 89) `static void ExtendLumpInfo(int newnumlumps)`
  - `W_AddFile` (function, line 141) `wad_file_t *W_AddFile (char *filename)`
  - `W_NumLumps` (function, line 246) `int W_NumLumps (void)`
  - `W_CheckNumForName` (function, line 258) `int W_CheckNumForName (char* name)`
  - `W_GetNumForName` (function, line 308) `int W_GetNumForName (char* name)`
  - `W_LumpLength` (function, line 327) `int W_LumpLength (unsigned int lump)`
  - `W_ReadLump` (function, line 344) `void W_ReadLump(unsigned int lump, void *dest)`
  - `W_CacheLumpNum` (function, line 384) `void *W_CacheLumpNum(int lumpnum, int tag)`
  - `W_CacheLumpName` (function, line 431) `void *W_CacheLumpName(char *name, int tag)`
  - `W_ReleaseLumpNum` (function, line 446) `void W_ReleaseLumpNum(int lumpnum)`
  - `W_ReleaseLumpName` (function, line 467) `void W_ReleaseLumpName(char *name)`
  - `W_Profile` (function, line 480) `void W_Profile (void)`
  - `W_GenerateHashTable` (function, line 541) `void W_GenerateHashTable(void)`
  - `W_CheckCorrectIWAD` (function, line 588) `void W_CheckCorrectIWAD(GameMission_t mission)`
  - `I_EndRead` (function, line 39) `void I_EndRead (void);`
- Depends on: `kernel/string.c`, `progs/doomgeneric/config.h`, `progs/doomgeneric/d_iwad.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/w_wad.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `lumpinfo_s` (struct, line 41)
  - `lumpinfo_t` (type_alias, line 38) `typedef struct lumpinfo_s lumpinfo_t;`
  - `W_AddFile` (function, line 58) `wad_file_t *W_AddFile (char *filename);`
  - `W_CheckNumForName` (function, line 60) `int W_CheckNumForName (char* name);`
  - `W_GetNumForName` (function, line 61) `int W_GetNumForName (char* name);`
  - `W_LumpLength` (function, line 63) `int W_LumpLength (unsigned int lump);`
  - `W_ReadLump` (function, line 64) `void W_ReadLump (unsigned int lump, void *dest);`
  - `W_CacheLumpNum` (function, line 66) `void* W_CacheLumpNum (int lump, int tag);`
  - `W_CacheLumpName` (function, line 67) `void* W_CacheLumpName (char* name, int tag);`
  - `W_GenerateHashTable` (function, line 69) `void W_GenerateHashTable(void);`
  - `W_LumpNameHash` (function, line 71) `extern unsigned int W_LumpNameHash(const char *s);`
  - `W_ReleaseLumpNum` (function, line 73) `void W_ReleaseLumpNum(int lump);`
  - `W_ReleaseLumpName` (function, line 74) `void W_ReleaseLumpName(char *name);`
  - `W_CheckCorrectIWAD` (function, line 76) `void W_CheckCorrectIWAD(GameMission_t mission);`
  - `lumpinfo` (variable, line 55) `extern lumpinfo_t *lumpinfo;`
  - `numlumps` (variable, line 56) `extern unsigned int numlumps;`
  - `__W_WAD__` (macro, line 21) `#define __W_WAD__`
- Depends on: `progs/doomgeneric/d_mode.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/w_file.h`
- Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_iwad.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/f_finale.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/gusconf.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_minios_sound.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/m_misc.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/r_data.c`, `progs/doomgeneric/r_draw.c`, `progs/doomgeneric/r_plane.c`, `progs/doomgeneric/r_things.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/st_lib.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/v_video.c`, `progs/doomgeneric/w_checksum.c`, `progs/doomgeneric/w_main.c`, `progs/doomgeneric/w_wad.c`, `progs/doomgeneric/wi_stuff.c`


Next: [KB_doomgeneric_p12.md](KB_doomgeneric_p12.md)
