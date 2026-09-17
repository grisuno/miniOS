# Subsystem: doomgeneric

## progs/doomgeneric/am_map.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `fpoint_t` (struct, line 111)
  - `fline_t` (struct, line 116)
  - `mpoint_t` (struct, line 121)
  - `mline_t` (struct, line 126)
  - `islope_t` (struct, line 131)
  - `AM_getIslope` (function, line 275) `void
AM_getIslope
( mline_t*	ml,
  islope_t*	is )`
  - `AM_activateNewScale` (function, line 293) `void AM_activateNewScale(void)`
  - `AM_saveScaleAndLoc` (function, line 308) `void AM_saveScaleAndLoc(void)`
  - `AM_restoreScaleAndLoc` (function, line 319) `void AM_restoreScaleAndLoc(void)`
  - `AM_addMark` (function, line 343) `void AM_addMark(void)`
  - `AM_findMinMaxBoundaries` (function, line 355) `void AM_findMinMaxBoundaries(void)`
  - `AM_changeWindowLoc` (function, line 395) `void AM_changeWindowLoc(void)`
  - `AM_initVariables` (function, line 424) `void AM_initVariables(void)`
  - `AM_loadPics` (function, line 480) `void AM_loadPics(void)`
  - `AM_unloadPics` (function, line 493) `void AM_unloadPics(void)`
  - `AM_clearMarks` (function, line 505) `void AM_clearMarks(void)`
  - `AM_LevelInit` (function, line 518) `void AM_LevelInit(void)`
  - `AM_Stop` (function, line 541) `void AM_Stop (void)`
  - `AM_Start` (function, line 554) `void AM_Start (void)`
  - `AM_minOutWindowScale` (function, line 573) `void AM_minOutWindowScale(void)`
  - `AM_maxOutWindowScale` (function, line 583) `void AM_maxOutWindowScale(void)`
  - `AM_Responder` (function, line 595) `boolean
AM_Responder
( event_t*	ev )`
  - `AM_changeWindowScale` (function, line 742) `void AM_changeWindowScale(void)`
  - `AM_doFollowPlayer` (function, line 761) `void AM_doFollowPlayer(void)`
  - `AM_updateLightLev` (function, line 785) `void AM_updateLightLev(void)`
  - `AM_Ticker` (function, line 806) `void AM_Ticker (void)`
  - `AM_clearFB` (function, line 834) `void AM_clearFB(int color)`
  - `AM_clipMline` (function, line 848) `boolean
AM_clipMline
( mline_t*	ml,
  fline_t*	fl )`
  - `AM_drawFline` (function, line 984) `void
AM_drawFline
( fline_t*	fl,
  int		color )`
  - `AM_drawMline` (function, line 1062) `void
AM_drawMline
( mline_t*	ml,
  int		color )`
  - `AM_drawGrid` (function, line 1077) `void AM_drawGrid(int color)`
  - `AM_drawWalls` (function, line 1123) `void AM_drawWalls(void)`
  - `AM_rotate` (function, line 1179) `void
AM_rotate
( fixed_t*	x,
  fixed_t*	y,
  angle_t	a )`
  - `AM_drawLineCharacter` (function, line 1198) `void
AM_drawLineCharacter
( mline_t*	lineguy,
  int		lineguylines,
  fixed_t	scale,
  angle_t	ang...`
  - `AM_drawPlayers` (function, line 1246) `void AM_drawPlayers(void)`
  - `AM_drawThings` (function, line 1291) `void
AM_drawThings
( int	colors,
  int 	colorrange)`
  - `AM_drawMarks` (function, line 1311) `void AM_drawMarks(void)`
  - `AM_drawCrosshair` (function, line 1332) `void AM_drawCrosshair(int color)`
  - `AM_Drawer` (function, line 1338) `void AM_Drawer (void)`
  - `REDS` (macro, line 50) `#define REDS`
  - `REDRANGE` (macro, line 51) `#define REDRANGE`
  - `BLUES` (macro, line 52) `#define BLUES`
  - `BLUERANGE` (macro, line 53) `#define BLUERANGE`
  - `GREENS` (macro, line 54) `#define GREENS`
  - `GREENRANGE` (macro, line 55) `#define GREENRANGE`
  - `GRAYS` (macro, line 56) `#define GRAYS`
  - `GRAYSRANGE` (macro, line 57) `#define GRAYSRANGE`
  - `BROWNS` (macro, line 58) `#define BROWNS`
  - `BROWNRANGE` (macro, line 59) `#define BROWNRANGE`
  - `YELLOWS` (macro, line 60) `#define YELLOWS`
  - `YELLOWRANGE` (macro, line 61) `#define YELLOWRANGE`
  - `BLACK` (macro, line 62) `#define BLACK`
  - `WHITE` (macro, line 63) `#define WHITE`
  - `BACKGROUND` (macro, line 66) `#define BACKGROUND`
  - `YOURCOLORS` (macro, line 67) `#define YOURCOLORS`
  - `YOURRANGE` (macro, line 68) `#define YOURRANGE`
  - `WALLCOLORS` (macro, line 69) `#define WALLCOLORS`
  - `WALLRANGE` (macro, line 70) `#define WALLRANGE`
  - `TSWALLCOLORS` (macro, line 71) `#define TSWALLCOLORS`
  - `TSWALLRANGE` (macro, line 72) `#define TSWALLRANGE`
  - `FDWALLCOLORS` (macro, line 73) `#define FDWALLCOLORS`
  - `FDWALLRANGE` (macro, line 74) `#define FDWALLRANGE`
  - `CDWALLCOLORS` (macro, line 75) `#define CDWALLCOLORS`
  - `CDWALLRANGE` (macro, line 76) `#define CDWALLRANGE`
  - `THINGCOLORS` (macro, line 77) `#define THINGCOLORS`
  - `THINGRANGE` (macro, line 78) `#define THINGRANGE`
  - `SECRETWALLCOLORS` (macro, line 79) `#define SECRETWALLCOLORS`
  - `SECRETWALLRANGE` (macro, line 80) `#define SECRETWALLRANGE`
  - `GRIDCOLORS` (macro, line 81) `#define GRIDCOLORS`
  - `GRIDRANGE` (macro, line 82) `#define GRIDRANGE`
  - `XHAIRCOLORS` (macro, line 83) `#define XHAIRCOLORS`
  - `AM_NUMMARKPOINTS` (macro, line 87) `#define AM_NUMMARKPOINTS`
  - `INITSCALEMTOF` (macro, line 90) `#define INITSCALEMTOF`
  - `F_PANINC` (macro, line 93) `#define F_PANINC`
  - `M_ZOOMIN` (macro, line 96) `#define M_ZOOMIN`
  - `M_ZOOMOUT` (macro, line 99) `#define M_ZOOMOUT`
  - `FTOM` (macro, line 102) `#define FTOM(x)`
  - `MTOF` (macro, line 103) `#define MTOF(x)`
  - `CXMTOF` (macro, line 105) `#define CXMTOF(x)`
  - `CYMTOF` (macro, line 106) `#define CYMTOF(y)`
  - `LINE_NEVERSEE` (macro, line 109) `#define LINE_NEVERSEE`
  - `R` (macro, line 143) `#define R`
  - `R` (macro, line 155) `#define R`
  - `R` (macro, line 176) `#define R`
  - `R` (macro, line 184) `#define R`
  - `DOOUTCODE` (macro, line 869) `#define DOOUTCODE(oc, mx, my)`
  - `PUTDOT` (macro, line 1010) `#define PUTDOT(xx,yy,cc)`
- Depends on: `progs/doomgeneric/am_map.h`, `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/dstrings.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_cheat.h`, `progs/doomgeneric/m_controls.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/st_stuff.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/am_map.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `AM_Ticker` (function, line 35) `void AM_Ticker (void);`
  - `AM_Drawer` (function, line 39) `void AM_Drawer (void);`
  - `AM_Stop` (function, line 43) `void AM_Stop (void);`
  - `cheat_amap` (variable, line 46) `extern cheatseq_t cheat_amap;`
  - `__AMMAP_H__` (macro, line 20) `#define __AMMAP_H__`
  - `AM_MSGHEADER` (macro, line 26) `#define AM_MSGHEADER`
  - `AM_MSGENTERED` (macro, line 27) `#define AM_MSGENTERED`
  - `AM_MSGEXITED` (macro, line 28) `#define AM_MSGEXITED`
- Depends on: `progs/doomgeneric/d_event.h`, `progs/doomgeneric/m_cheat.h`
- Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/p_inter.c`, `progs/doomgeneric/st_stuff.c`

## progs/doomgeneric/config.h
- Layer: infrastructure
- Doc: config.hin.  Generated from configure.ac by autoheader.
- Language: h
- Symbols:
  - `HAVE_INTTYPES_H` (macro, line 10) `#define HAVE_INTTYPES_H`
  - `HAVE_STDINT_H` (macro, line 46) `#define HAVE_STDINT_H`
  - `HAVE_STDLIB_H` (macro, line 49) `#define HAVE_STDLIB_H`
  - `HAVE_STRINGS_H` (macro, line 52) `#define HAVE_STRINGS_H`
  - `HAVE_STRING_H` (macro, line 55) `#define HAVE_STRING_H`
  - `HAVE_SYS_TYPES_H` (macro, line 61) `#define HAVE_SYS_TYPES_H`
  - `PACKAGE` (macro, line 67) `#define PACKAGE`
  - `PACKAGE_NAME` (macro, line 73) `#define PACKAGE_NAME`
  - `PACKAGE_STRING` (macro, line 76) `#define PACKAGE_STRING`
  - `PACKAGE_TARNAME` (macro, line 79) `#define PACKAGE_TARNAME`
  - `PACKAGE_URL` (macro, line 82) `#define PACKAGE_URL`
  - `PACKAGE_VERSION` (macro, line 85) `#define PACKAGE_VERSION`
  - `PROGRAM_PREFIX` (macro, line 88) `#define PROGRAM_PREFIX`
  - `STDC_HEADERS` (macro, line 91) `#define STDC_HEADERS`
  - `VERSION` (macro, line 94) `#define VERSION`
  - `FILES_DIR` (macro, line 100) `#define FILES_DIR`
- Imported by: `progs/doomgeneric/d_iwad.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/i_endoom.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_sound.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/i_video.c`, `progs/doomgeneric/m_config.c`, `progs/doomgeneric/v_video.c`, `progs/doomgeneric/w_file.c`, `progs/doomgeneric/w_wad.c`

## progs/doomgeneric/d_englsh.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__D_ENGLSH__` (macro, line 21) `#define __D_ENGLSH__`
  - `D_DEVSTR` (macro, line 30) `#define D_DEVSTR`
  - `D_CDROM` (macro, line 31) `#define D_CDROM`
  - `PRESSKEY` (macro, line 36) `#define PRESSKEY`
  - `PRESSYN` (macro, line 37) `#define PRESSYN`
  - `QUITMSG` (macro, line 38) `#define QUITMSG`
  - `LOADNET` (macro, line 39) `#define LOADNET`
  - `QLOADNET` (macro, line 40) `#define QLOADNET`
  - `QSAVESPOT` (macro, line 41) `#define QSAVESPOT`
  - `SAVEDEAD` (macro, line 42) `#define SAVEDEAD`
  - `QSPROMPT` (macro, line 43) `#define QSPROMPT`
  - `QLPROMPT` (macro, line 44) `#define QLPROMPT`
  - `NEWGAME` (macro, line 46) `#define NEWGAME`
  - `NIGHTMARE` (macro, line 50) `#define NIGHTMARE`
  - `SWSTRING` (macro, line 54) `#define SWSTRING`
  - `MSGOFF` (macro, line 58) `#define MSGOFF`
  - `MSGON` (macro, line 59) `#define MSGON`
  - `NETEND` (macro, line 60) `#define NETEND`
  - `ENDGAME` (macro, line 61) `#define ENDGAME`
  - `DOSY` (macro, line 63) `#define DOSY`
  - `DETAILHI` (macro, line 65) `#define DETAILHI`
  - `DETAILLO` (macro, line 66) `#define DETAILLO`
  - `GAMMALVL0` (macro, line 67) `#define GAMMALVL0`
  - `GAMMALVL1` (macro, line 68) `#define GAMMALVL1`
  - `GAMMALVL2` (macro, line 69) `#define GAMMALVL2`
  - `GAMMALVL3` (macro, line 70) `#define GAMMALVL3`
  - `GAMMALVL4` (macro, line 71) `#define GAMMALVL4`
  - `EMPTYSTRING` (macro, line 72) `#define EMPTYSTRING`
  - `GOTARMOR` (macro, line 77) `#define GOTARMOR`
  - `GOTMEGA` (macro, line 78) `#define GOTMEGA`
  - `GOTHTHBONUS` (macro, line 79) `#define GOTHTHBONUS`
  - `GOTARMBONUS` (macro, line 80) `#define GOTARMBONUS`
  - `GOTSTIM` (macro, line 81) `#define GOTSTIM`
  - `GOTMEDINEED` (macro, line 82) `#define GOTMEDINEED`
  - `GOTMEDIKIT` (macro, line 83) `#define GOTMEDIKIT`
  - `GOTSUPER` (macro, line 84) `#define GOTSUPER`
  - `GOTBLUECARD` (macro, line 86) `#define GOTBLUECARD`
  - `GOTYELWCARD` (macro, line 87) `#define GOTYELWCARD`
  - `GOTREDCARD` (macro, line 88) `#define GOTREDCARD`
  - `GOTBLUESKUL` (macro, line 89) `#define GOTBLUESKUL`
  - `GOTYELWSKUL` (macro, line 90) `#define GOTYELWSKUL`
  - `GOTREDSKULL` (macro, line 91) `#define GOTREDSKULL`
  - `GOTINVUL` (macro, line 93) `#define GOTINVUL`
  - `GOTBERSERK` (macro, line 94) `#define GOTBERSERK`
  - `GOTINVIS` (macro, line 95) `#define GOTINVIS`
  - `GOTSUIT` (macro, line 96) `#define GOTSUIT`
  - `GOTMAP` (macro, line 97) `#define GOTMAP`
  - `GOTVISOR` (macro, line 98) `#define GOTVISOR`
  - `GOTMSPHERE` (macro, line 99) `#define GOTMSPHERE`
  - `GOTCLIP` (macro, line 101) `#define GOTCLIP`
  - `GOTCLIPBOX` (macro, line 102) `#define GOTCLIPBOX`
  - `GOTROCKET` (macro, line 103) `#define GOTROCKET`
  - `GOTROCKBOX` (macro, line 104) `#define GOTROCKBOX`
  - `GOTCELL` (macro, line 105) `#define GOTCELL`
  - `GOTCELLBOX` (macro, line 106) `#define GOTCELLBOX`
  - `GOTSHELLS` (macro, line 107) `#define GOTSHELLS`
  - `GOTSHELLBOX` (macro, line 108) `#define GOTSHELLBOX`
  - `GOTBACKPACK` (macro, line 109) `#define GOTBACKPACK`
  - `GOTBFG9000` (macro, line 111) `#define GOTBFG9000`
  - `GOTCHAINGUN` (macro, line 112) `#define GOTCHAINGUN`
  - `GOTCHAINSAW` (macro, line 113) `#define GOTCHAINSAW`
  - `GOTLAUNCHER` (macro, line 114) `#define GOTLAUNCHER`
  - `GOTPLASMA` (macro, line 115) `#define GOTPLASMA`
  - `GOTSHOTGUN` (macro, line 116) `#define GOTSHOTGUN`
  - `GOTSHOTGUN2` (macro, line 117) `#define GOTSHOTGUN2`
  - `PD_BLUEO` (macro, line 122) `#define PD_BLUEO`
  - `PD_REDO` (macro, line 123) `#define PD_REDO`
  - `PD_YELLOWO` (macro, line 124) `#define PD_YELLOWO`
  - `PD_BLUEK` (macro, line 125) `#define PD_BLUEK`
  - `PD_REDK` (macro, line 126) `#define PD_REDK`
  - `PD_YELLOWK` (macro, line 127) `#define PD_YELLOWK`
  - `GGSAVED` (macro, line 132) `#define GGSAVED`
  - `HUSTR_MSGU` (macro, line 137) `#define HUSTR_MSGU`
  - `HUSTR_E1M1` (macro, line 139) `#define HUSTR_E1M1`
  - `HUSTR_E1M2` (macro, line 140) `#define HUSTR_E1M2`
  - `HUSTR_E1M3` (macro, line 141) `#define HUSTR_E1M3`
  - `HUSTR_E1M4` (macro, line 142) `#define HUSTR_E1M4`
  - `HUSTR_E1M5` (macro, line 143) `#define HUSTR_E1M5`
  - `HUSTR_E1M6` (macro, line 144) `#define HUSTR_E1M6`
  - `HUSTR_E1M7` (macro, line 145) `#define HUSTR_E1M7`
  - `HUSTR_E1M8` (macro, line 146) `#define HUSTR_E1M8`
  - `HUSTR_E1M9` (macro, line 147) `#define HUSTR_E1M9`
  - `HUSTR_E2M1` (macro, line 149) `#define HUSTR_E2M1`
  - `HUSTR_E2M2` (macro, line 150) `#define HUSTR_E2M2`
  - `HUSTR_E2M3` (macro, line 151) `#define HUSTR_E2M3`
  - `HUSTR_E2M4` (macro, line 152) `#define HUSTR_E2M4`
  - `HUSTR_E2M5` (macro, line 153) `#define HUSTR_E2M5`
  - `HUSTR_E2M6` (macro, line 154) `#define HUSTR_E2M6`
  - `HUSTR_E2M7` (macro, line 155) `#define HUSTR_E2M7`
  - `HUSTR_E2M8` (macro, line 156) `#define HUSTR_E2M8`
  - `HUSTR_E2M9` (macro, line 157) `#define HUSTR_E2M9`
  - `HUSTR_E3M1` (macro, line 159) `#define HUSTR_E3M1`
  - `HUSTR_E3M2` (macro, line 160) `#define HUSTR_E3M2`
  - `HUSTR_E3M3` (macro, line 161) `#define HUSTR_E3M3`
  - `HUSTR_E3M4` (macro, line 162) `#define HUSTR_E3M4`
  - `HUSTR_E3M5` (macro, line 163) `#define HUSTR_E3M5`
  - `HUSTR_E3M6` (macro, line 164) `#define HUSTR_E3M6`
  - `HUSTR_E3M7` (macro, line 165) `#define HUSTR_E3M7`
  - `HUSTR_E3M8` (macro, line 166) `#define HUSTR_E3M8`
  - `HUSTR_E3M9` (macro, line 167) `#define HUSTR_E3M9`
  - `HUSTR_E4M1` (macro, line 169) `#define HUSTR_E4M1`
  - `HUSTR_E4M2` (macro, line 170) `#define HUSTR_E4M2`
  - `HUSTR_E4M3` (macro, line 171) `#define HUSTR_E4M3`
  - `HUSTR_E4M4` (macro, line 172) `#define HUSTR_E4M4`
  - `HUSTR_E4M5` (macro, line 173) `#define HUSTR_E4M5`
  - `HUSTR_E4M6` (macro, line 174) `#define HUSTR_E4M6`
  - `HUSTR_E4M7` (macro, line 175) `#define HUSTR_E4M7`
  - `HUSTR_E4M8` (macro, line 176) `#define HUSTR_E4M8`
  - `HUSTR_E4M9` (macro, line 177) `#define HUSTR_E4M9`
  - `HUSTR_1` (macro, line 179) `#define HUSTR_1`
  - `HUSTR_2` (macro, line 180) `#define HUSTR_2`
  - `HUSTR_3` (macro, line 181) `#define HUSTR_3`
  - `HUSTR_4` (macro, line 182) `#define HUSTR_4`
  - `HUSTR_5` (macro, line 183) `#define HUSTR_5`
  - `HUSTR_6` (macro, line 184) `#define HUSTR_6`
  - `HUSTR_7` (macro, line 185) `#define HUSTR_7`
  - `HUSTR_8` (macro, line 186) `#define HUSTR_8`
  - `HUSTR_9` (macro, line 187) `#define HUSTR_9`
  - `HUSTR_10` (macro, line 188) `#define HUSTR_10`
  - `HUSTR_11` (macro, line 189) `#define HUSTR_11`
  - `HUSTR_12` (macro, line 191) `#define HUSTR_12`
  - `HUSTR_13` (macro, line 192) `#define HUSTR_13`
  - `HUSTR_14` (macro, line 193) `#define HUSTR_14`
  - `HUSTR_15` (macro, line 194) `#define HUSTR_15`
  - `HUSTR_16` (macro, line 195) `#define HUSTR_16`
  - `HUSTR_17` (macro, line 196) `#define HUSTR_17`
  - `HUSTR_18` (macro, line 197) `#define HUSTR_18`
  - `HUSTR_19` (macro, line 198) `#define HUSTR_19`
  - `HUSTR_20` (macro, line 199) `#define HUSTR_20`
  - `HUSTR_21` (macro, line 201) `#define HUSTR_21`
  - `HUSTR_22` (macro, line 202) `#define HUSTR_22`
  - `HUSTR_23` (macro, line 203) `#define HUSTR_23`
  - `HUSTR_24` (macro, line 204) `#define HUSTR_24`
  - `HUSTR_25` (macro, line 205) `#define HUSTR_25`
  - `HUSTR_26` (macro, line 206) `#define HUSTR_26`
  - `HUSTR_27` (macro, line 207) `#define HUSTR_27`
  - `HUSTR_28` (macro, line 208) `#define HUSTR_28`
  - `HUSTR_29` (macro, line 209) `#define HUSTR_29`
  - `HUSTR_30` (macro, line 210) `#define HUSTR_30`
  - `HUSTR_31` (macro, line 212) `#define HUSTR_31`
  - `HUSTR_32` (macro, line 213) `#define HUSTR_32`
  - `PHUSTR_1` (macro, line 215) `#define PHUSTR_1`
  - `PHUSTR_2` (macro, line 216) `#define PHUSTR_2`
  - `PHUSTR_3` (macro, line 217) `#define PHUSTR_3`
  - `PHUSTR_4` (macro, line 218) `#define PHUSTR_4`
  - `PHUSTR_5` (macro, line 219) `#define PHUSTR_5`
  - `PHUSTR_6` (macro, line 220) `#define PHUSTR_6`
  - `PHUSTR_7` (macro, line 221) `#define PHUSTR_7`
  - `PHUSTR_8` (macro, line 222) `#define PHUSTR_8`
  - `PHUSTR_9` (macro, line 223) `#define PHUSTR_9`
  - `PHUSTR_10` (macro, line 224) `#define PHUSTR_10`
  - `PHUSTR_11` (macro, line 225) `#define PHUSTR_11`
  - `PHUSTR_12` (macro, line 227) `#define PHUSTR_12`
  - `PHUSTR_13` (macro, line 228) `#define PHUSTR_13`
  - `PHUSTR_14` (macro, line 229) `#define PHUSTR_14`
  - `PHUSTR_15` (macro, line 230) `#define PHUSTR_15`
  - `PHUSTR_16` (macro, line 231) `#define PHUSTR_16`
  - `PHUSTR_17` (macro, line 232) `#define PHUSTR_17`
  - `PHUSTR_18` (macro, line 233) `#define PHUSTR_18`
  - `PHUSTR_19` (macro, line 234) `#define PHUSTR_19`
  - `PHUSTR_20` (macro, line 235) `#define PHUSTR_20`
  - `PHUSTR_21` (macro, line 237) `#define PHUSTR_21`
  - `PHUSTR_22` (macro, line 238) `#define PHUSTR_22`
  - `PHUSTR_23` (macro, line 239) `#define PHUSTR_23`
  - `PHUSTR_24` (macro, line 240) `#define PHUSTR_24`
  - `PHUSTR_25` (macro, line 241) `#define PHUSTR_25`
  - `PHUSTR_26` (macro, line 242) `#define PHUSTR_26`
  - `PHUSTR_27` (macro, line 243) `#define PHUSTR_27`
  - `PHUSTR_28` (macro, line 244) `#define PHUSTR_28`
  - `PHUSTR_29` (macro, line 245) `#define PHUSTR_29`
  - `PHUSTR_30` (macro, line 246) `#define PHUSTR_30`
  - `PHUSTR_31` (macro, line 248) `#define PHUSTR_31`
  - `PHUSTR_32` (macro, line 249) `#define PHUSTR_32`
  - `THUSTR_1` (macro, line 251) `#define THUSTR_1`
  - `THUSTR_2` (macro, line 252) `#define THUSTR_2`
  - `THUSTR_3` (macro, line 253) `#define THUSTR_3`
  - `THUSTR_4` (macro, line 254) `#define THUSTR_4`
  - `THUSTR_5` (macro, line 255) `#define THUSTR_5`
  - `THUSTR_6` (macro, line 256) `#define THUSTR_6`
  - `THUSTR_7` (macro, line 257) `#define THUSTR_7`
  - `THUSTR_8` (macro, line 258) `#define THUSTR_8`
  - `THUSTR_9` (macro, line 259) `#define THUSTR_9`
  - `THUSTR_10` (macro, line 260) `#define THUSTR_10`
  - `THUSTR_11` (macro, line 261) `#define THUSTR_11`
  - `THUSTR_12` (macro, line 263) `#define THUSTR_12`
  - `THUSTR_13` (macro, line 264) `#define THUSTR_13`
  - `THUSTR_14` (macro, line 265) `#define THUSTR_14`
  - `THUSTR_15` (macro, line 266) `#define THUSTR_15`
  - `THUSTR_16` (macro, line 267) `#define THUSTR_16`
  - `THUSTR_17` (macro, line 268) `#define THUSTR_17`
  - `THUSTR_18` (macro, line 269) `#define THUSTR_18`
  - `THUSTR_19` (macro, line 270) `#define THUSTR_19`
  - `THUSTR_20` (macro, line 271) `#define THUSTR_20`
  - `THUSTR_21` (macro, line 273) `#define THUSTR_21`
  - `THUSTR_22` (macro, line 274) `#define THUSTR_22`
  - `THUSTR_23` (macro, line 275) `#define THUSTR_23`
  - `THUSTR_24` (macro, line 276) `#define THUSTR_24`
  - `THUSTR_25` (macro, line 277) `#define THUSTR_25`
  - `THUSTR_26` (macro, line 278) `#define THUSTR_26`
  - `THUSTR_27` (macro, line 279) `#define THUSTR_27`
  - `THUSTR_28` (macro, line 280) `#define THUSTR_28`
  - `THUSTR_29` (macro, line 281) `#define THUSTR_29`
  - `THUSTR_30` (macro, line 282) `#define THUSTR_30`
  - `THUSTR_31` (macro, line 284) `#define THUSTR_31`
  - `THUSTR_32` (macro, line 285) `#define THUSTR_32`
  - `HUSTR_CHATMACRO1` (macro, line 287) `#define HUSTR_CHATMACRO1`
  - `HUSTR_CHATMACRO2` (macro, line 288) `#define HUSTR_CHATMACRO2`
  - `HUSTR_CHATMACRO3` (macro, line 289) `#define HUSTR_CHATMACRO3`
  - `HUSTR_CHATMACRO4` (macro, line 290) `#define HUSTR_CHATMACRO4`
  - `HUSTR_CHATMACRO5` (macro, line 291) `#define HUSTR_CHATMACRO5`
  - `HUSTR_CHATMACRO6` (macro, line 292) `#define HUSTR_CHATMACRO6`
  - `HUSTR_CHATMACRO7` (macro, line 293) `#define HUSTR_CHATMACRO7`
  - `HUSTR_CHATMACRO8` (macro, line 294) `#define HUSTR_CHATMACRO8`
  - `HUSTR_CHATMACRO9` (macro, line 295) `#define HUSTR_CHATMACRO9`
  - `HUSTR_CHATMACRO0` (macro, line 296) `#define HUSTR_CHATMACRO0`
  - `HUSTR_TALKTOSELF1` (macro, line 298) `#define HUSTR_TALKTOSELF1`
  - `HUSTR_TALKTOSELF2` (macro, line 299) `#define HUSTR_TALKTOSELF2`
  - `HUSTR_TALKTOSELF3` (macro, line 300) `#define HUSTR_TALKTOSELF3`
  - `HUSTR_TALKTOSELF4` (macro, line 301) `#define HUSTR_TALKTOSELF4`
  - `HUSTR_TALKTOSELF5` (macro, line 302) `#define HUSTR_TALKTOSELF5`
  - `HUSTR_MESSAGESENT` (macro, line 304) `#define HUSTR_MESSAGESENT`
  - `HUSTR_PLRGREEN` (macro, line 309) `#define HUSTR_PLRGREEN`
  - `HUSTR_PLRINDIGO` (macro, line 310) `#define HUSTR_PLRINDIGO`
  - `HUSTR_PLRBROWN` (macro, line 311) `#define HUSTR_PLRBROWN`
  - `HUSTR_PLRRED` (macro, line 312) `#define HUSTR_PLRRED`
  - `HUSTR_KEYGREEN` (macro, line 314) `#define HUSTR_KEYGREEN`
  - `HUSTR_KEYINDIGO` (macro, line 315) `#define HUSTR_KEYINDIGO`
  - `HUSTR_KEYBROWN` (macro, line 316) `#define HUSTR_KEYBROWN`
  - `HUSTR_KEYRED` (macro, line 317) `#define HUSTR_KEYRED`
  - `AMSTR_FOLLOWON` (macro, line 323) `#define AMSTR_FOLLOWON`
  - `AMSTR_FOLLOWOFF` (macro, line 324) `#define AMSTR_FOLLOWOFF`
  - `AMSTR_GRIDON` (macro, line 326) `#define AMSTR_GRIDON`
  - `AMSTR_GRIDOFF` (macro, line 327) `#define AMSTR_GRIDOFF`
  - `AMSTR_MARKEDSPOT` (macro, line 329) `#define AMSTR_MARKEDSPOT`
  - `AMSTR_MARKSCLEARED` (macro, line 330) `#define AMSTR_MARKSCLEARED`
  - `STSTR_MUS` (macro, line 336) `#define STSTR_MUS`
  - `STSTR_NOMUS` (macro, line 337) `#define STSTR_NOMUS`
  - `STSTR_DQDON` (macro, line 338) `#define STSTR_DQDON`
  - `STSTR_DQDOFF` (macro, line 339) `#define STSTR_DQDOFF`
  - `STSTR_KFAADDED` (macro, line 341) `#define STSTR_KFAADDED`
  - `STSTR_FAADDED` (macro, line 342) `#define STSTR_FAADDED`
  - `STSTR_NCON` (macro, line 344) `#define STSTR_NCON`
  - `STSTR_NCOFF` (macro, line 345) `#define STSTR_NCOFF`
  - `STSTR_BEHOLD` (macro, line 347) `#define STSTR_BEHOLD`
  - `STSTR_BEHOLDX` (macro, line 348) `#define STSTR_BEHOLDX`
  - `STSTR_CHOPPERS` (macro, line 350) `#define STSTR_CHOPPERS`
  - `STSTR_CLEV` (macro, line 351) `#define STSTR_CLEV`
  - `E1TEXT` (macro, line 356) `#define E1TEXT`
  - `E2TEXT` (macro, line 374) `#define E2TEXT`
  - `E3TEXT` (macro, line 394) `#define E3TEXT`
  - `E4TEXT` (macro, line 414) `#define E4TEXT`
  - `C1TEXT` (macro, line 435) `#define C1TEXT`
  - `C2TEXT` (macro, line 451) `#define C2TEXT`
  - `C3TEXT` (macro, line 473) `#define C3TEXT`
  - `C4TEXT` (macro, line 487) `#define C4TEXT`
  - `C5TEXT` (macro, line 508) `#define C5TEXT`
  - `C6TEXT` (macro, line 518) `#define C6TEXT`
  - `P1TEXT` (macro, line 526) `#define P1TEXT`
  - `P2TEXT` (macro, line 543) `#define P2TEXT`
  - `P3TEXT` (macro, line 554) `#define P3TEXT`
  - `P4TEXT` (macro, line 568) `#define P4TEXT`
  - `P5TEXT` (macro, line 584) `#define P5TEXT`
  - `P6TEXT` (macro, line 592) `#define P6TEXT`
  - `T1TEXT` (macro, line 598) `#define T1TEXT`
  - `T2TEXT` (macro, line 613) `#define T2TEXT`
  - `T3TEXT` (macro, line 625) `#define T3TEXT`
  - `T4TEXT` (macro, line 635) `#define T4TEXT`
  - `T5TEXT` (macro, line 649) `#define T5TEXT`
  - `T6TEXT` (macro, line 657) `#define T6TEXT`
  - `CC_ZOMBIE` (macro, line 674) `#define CC_ZOMBIE`
  - `CC_SHOTGUN` (macro, line 675) `#define CC_SHOTGUN`
  - `CC_HEAVY` (macro, line 676) `#define CC_HEAVY`
  - `CC_IMP` (macro, line 677) `#define CC_IMP`
  - `CC_DEMON` (macro, line 678) `#define CC_DEMON`
  - `CC_LOST` (macro, line 679) `#define CC_LOST`
  - `CC_CACO` (macro, line 680) `#define CC_CACO`
  - `CC_HELL` (macro, line 681) `#define CC_HELL`
  - `CC_BARON` (macro, line 682) `#define CC_BARON`
  - `CC_ARACH` (macro, line 683) `#define CC_ARACH`
  - `CC_PAIN` (macro, line 684) `#define CC_PAIN`
  - `CC_REVEN` (macro, line 685) `#define CC_REVEN`
  - `CC_MANCU` (macro, line 686) `#define CC_MANCU`
  - `CC_ARCH` (macro, line 687) `#define CC_ARCH`
  - `CC_SPIDER` (macro, line 688) `#define CC_SPIDER`
  - `CC_CYBER` (macro, line 689) `#define CC_CYBER`
  - `CC_HERO` (macro, line 690) `#define CC_HERO`
- Imported by: `progs/doomgeneric/dstrings.h`

## progs/doomgeneric/d_event.c
- Layer: infrastructure
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `D_PostEvent` (function, line 35) `void D_PostEvent (event_t* ev)`
  - `D_PopEvent` (function, line 43) `event_t *D_PopEvent(void)`
  - `MAXEVENTS` (macro, line 25) `#define MAXEVENTS`
- Depends on: `progs/doomgeneric/d_event.h`

## progs/doomgeneric/d_event.h
- Layer: infrastructure
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `event_t` (struct, line 42)
  - `D_PostEvent` (function, line 129) `void D_PostEvent (event_t *ev);`
  - `D_PopEvent` (function, line 133) `event_t *D_PopEvent(void);`
  - `__D_EVENT__` (macro, line 21) `#define __D_EVENT__`
- Depends on: `progs/doomgeneric/doomtype.h`
- Imported by: `progs/doomgeneric/am_map.h`, `progs/doomgeneric/d_event.c`, `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/f_finale.h`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/hu_stuff.h`, `progs/doomgeneric/i_joystick.c`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/i_video.c`, `progs/doomgeneric/m_menu.h`, `progs/doomgeneric/p_pspr.c`, `progs/doomgeneric/p_user.c`, `progs/doomgeneric/st_stuff.h`

## progs/doomgeneric/d_items.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Depends on: `progs/doomgeneric/d_items.h`, `progs/doomgeneric/info.h`

## progs/doomgeneric/d_items.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `weaponinfo_t` (struct, line 28)
  - `weaponinfo` (variable, line 39) `extern weaponinfo_t weaponinfo[NUMWEAPONS];`
  - `__D_ITEMS__` (macro, line 21) `#define __D_ITEMS__`
- Depends on: `progs/doomgeneric/doomdef.h`
- Imported by: `progs/doomgeneric/d_items.c`, `progs/doomgeneric/d_player.h`

## progs/doomgeneric/d_iwad.c
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
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
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
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
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `D_GetNumEpisodes` (function, line 93) `int D_GetNumEpisodes(GameMission_t mission, GameMode_t mode);`
  - `D_GameMissionString` (function, line 95) `char *D_GameMissionString(GameMission_t mission);`
  - `__D_MODE__` (macro, line 21) `#define __D_MODE__`
- Depends on: `progs/doomgeneric/doomtype.h`
- Imported by: `progs/doomgeneric/d_iwad.h`, `progs/doomgeneric/d_mode.c`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/statdump.c`, `progs/doomgeneric/w_wad.h`

## progs/doomgeneric/d_net.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `pic_t` (struct, line 33)
  - `__D_TEXTUR__` (macro, line 22) `#define __D_TEXTUR__`
- Depends on: `progs/doomgeneric/doomtype.h`

## progs/doomgeneric/d_think.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `thinker_s` (struct, line 58)
  - `think_t` (type_alias, line 54) `typedef actionf_t think_t;`
  - `prev` (type_alias, line 58) `typedef struct thinker_s { struct thinker_s* prev;`
  - `__D_THINK__` (macro, line 23) `#define __D_THINK__`
- Imported by: `progs/doomgeneric/info.h`, `progs/doomgeneric/p_mobj.h`, `progs/doomgeneric/r_defs.h`

## progs/doomgeneric/d_ticcmd.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software Copyright(C) 2005-2014 Simon Howard  This
- Language: h
- Symbols:
  - `ticcmd_t` (struct, line 32)
  - `__D_TICCMD__` (macro, line 22) `#define __D_TICCMD__`
- Depends on: `progs/doomgeneric/doomtype.h`
- Imported by: `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/d_player.h`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/net_client.h`, `progs/doomgeneric/net_defs.h`

## progs/doomgeneric/deh_main.h
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
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
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
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
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
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
- Layer: data_access
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Depends on: `progs/doomgeneric/doomdef.h`

## progs/doomgeneric/doomdef.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
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
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
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
- Layer: utility
- Doc: doomgeneric_minios.c - MiniOS platform layer for doomgeneric.
- Language: c
- Symbols:
  - `color` (struct, line 79)
  - `mini_parse_autoframes` (function, line 23) `static void mini_parse_autoframes(int argc, char **argv)`
  - `sys_time_ms` (function, line 37) `static long sys_time_ms(void)`
  - `sys_kbd` (function, line 42) `static long sys_kbd(void)`
  - `sys_palette` (function, line 47) `static long sys_palette(const unsigned char *pal)`
  - `sys_kbd_raw` (function, line 52) `static long sys_kbd_raw(int on)`
  - `sys_vga_mode` (function, line 57) `static long sys_vga_mode(int on)`
  - `sys_doom_frame` (function, line 62) `static long sys_doom_frame(void)`
  - `load_vga_palette` (function, line 86) `static void load_vga_palette(void)`
  - `scancode_to_doom` (function, line 99) `static unsigned char scancode_to_doom(unsigned char raw)`
  - `kbd_enqueue` (function, line 158) `static void kbd_enqueue(unsigned char doom_key, int pressed)`
  - `kbd_poll` (function, line 165) `static void kbd_poll(void)`
  - `DG_Init` (function, line 208) `void DG_Init(void)`
  - `DG_DrawFrame` (function, line 216) `void DG_DrawFrame(void)`
  - `DG_SleepMs` (function, line 246) `void DG_SleepMs(uint32_t ms)`
  - `DG_GetTicksMs` (function, line 252) `uint32_t DG_GetTicksMs(void)`
  - `DG_GetKey` (function, line 256) `int DG_GetKey(int *pressed, unsigned char *key)`
  - `DG_SetWindowTitle` (function, line 267) `void DG_SetWindowTitle(const char *title)`
  - `MINIOS_DOOM_BACKBUF_ADDR` (function, line 4) `* MINIOS_DOOM_BACKBUF_ADDR (minios_abi.h);`
  - `colors` (variable, line 80) `extern struct color colors[256];`
  - `I_VideoBuffer` (variable, line 206) `extern unsigned char *I_VideoBuffer;`
  - `myargc` (variable, line 209) `extern int myargc;`
  - `myargv` (variable, line 210) `extern char **myargv;`
  - `FB_ADDR` (macro, line 72) `#define FB_ADDR`
  - `FB_WIDTH` (macro, line 73) `#define FB_WIDTH`
  - `FB_HEIGHT` (macro, line 74) `#define FB_HEIGHT`
  - `KBD_QUEUE_SIZE` (macro, line 154) `#define KBD_QUEUE_SIZE`
- Depends on: `kernel/string.c`, `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomkeys.h`, `progs/minios_abi.h`

## progs/doomgeneric/doomgeneric_sdl.c
- Layer: utility
- Doc: doomgeneric for soso os
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
- Layer: utility
- Doc: doomgeneric for soso os
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

## progs/doomgeneric/doomgeneric_sosox.c
- Layer: utility
- Doc: doomgeneric for soso os (nano-x version) TODO: get keys from X, not using direct keyboard access!
- Language: c
- Symbols:
  - `convert_to_doom_key` (function, line 39) `static unsigned char convert_to_doom_key(unsigned char scancode)`
  - `add_key_to_queue` (function, line 88) `static void add_key_to_queue(int pressed, unsigned char key_code)`
  - `disable_raw_mode` (function, line 102) `void disable_raw_mode()`
  - `enable_raw_mode` (function, line 107) `void enable_raw_mode()`
  - `DG_Init` (function, line 117) `void DG_Init()`
  - `handle_key_input` (function, line 159) `static void handle_key_input()`
  - `DG_DrawFrame` (function, line 187) `void DG_DrawFrame()`
  - `DG_SleepMs` (function, line 225) `void DG_SleepMs(uint32_t ms)`
  - `DG_GetTicksMs` (function, line 230) `uint32_t DG_GetTicksMs()`
  - `DG_GetKey` (function, line 235) `int DG_GetKey(int* pressed, unsigned char* doomKey)`
  - `DG_SetWindowTitle` (function, line 256) `void DG_SetWindowTitle(const char * title)`
  - `KEYQUEUE_SIZE` (macro, line 24) `#define KEYQUEUE_SIZE`
- Depends on: `kernel/string.c`, `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/m_argv.h`

## progs/doomgeneric/doomgeneric_win.c
- Layer: utility
- Language: c
- Symbols:
  - `convertToDoomKey` (function, line 20) `static unsigned char convertToDoomKey(unsigned char key)`
  - `addKeyToQueue` (function, line 59) `static void addKeyToQueue(int pressed, unsigned char keyCode)`
  - `wndProc` (function, line 70) `static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)`
  - `DG_Init` (function, line 95) `void DG_Init()`
  - `DG_DrawFrame` (function, line 146) `void DG_DrawFrame()`
  - `DG_SleepMs` (function, line 162) `void DG_SleepMs(uint32_t ms)`
  - `DG_GetTicksMs` (function, line 167) `uint32_t DG_GetTicksMs()`
  - `DG_GetKey` (function, line 172) `int DG_GetKey(int* pressed, unsigned char* doomKey)`
  - `DG_SetWindowTitle` (function, line 193) `void DG_SetWindowTitle(const char * title)`
  - `KEYQUEUE_SIZE` (macro, line 14) `#define KEYQUEUE_SIZE`
- Depends on: `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomkeys.h`

## progs/doomgeneric/doomgeneric_xlib.c
- Layer: utility
- Language: c
- Symbols:
  - `convertToDoomKey` (function, line 27) `static unsigned char convertToDoomKey(unsigned int key)`
  - `addKeyToQueue` (function, line 68) `static void addKeyToQueue(int pressed, unsigned int keyCode)`
  - `DG_Init` (function, line 79) `void DG_Init()`
  - `DG_DrawFrame` (function, line 127) `void DG_DrawFrame()`
  - `DG_SleepMs` (function, line 172) `void DG_SleepMs(uint32_t ms)`
  - `DG_GetTicksMs` (function, line 177) `uint32_t DG_GetTicksMs()`
  - `DG_GetKey` (function, line 187) `int DG_GetKey(int* pressed, unsigned char* doomKey)`
  - `DG_SetWindowTitle` (function, line 208) `void DG_SetWindowTitle(const char * title)`
  - `KEYQUEUE_SIZE` (macro, line 21) `#define KEYQUEUE_SIZE`
- Depends on: `kernel/string.c`, `kernel/time.c`, `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomkeys.h`

## progs/doomgeneric/doomkeys.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__DOOMKEYS__` (macro, line 20) `#define __DOOMKEYS__`
  - `KEY_RIGHTARROW` (macro, line 27) `#define KEY_RIGHTARROW`
  - `KEY_LEFTARROW` (macro, line 28) `#define KEY_LEFTARROW`
  - `KEY_UPARROW` (macro, line 29) `#define KEY_UPARROW`
  - `KEY_DOWNARROW` (macro, line 30) `#define KEY_DOWNARROW`
  - `KEY_STRAFE_L` (macro, line 31) `#define KEY_STRAFE_L`
  - `KEY_STRAFE_R` (macro, line 32) `#define KEY_STRAFE_R`
  - `KEY_USE` (macro, line 33) `#define KEY_USE`
  - `KEY_FIRE` (macro, line 34) `#define KEY_FIRE`
  - `KEY_ESCAPE` (macro, line 35) `#define KEY_ESCAPE`
  - `KEY_ENTER` (macro, line 36) `#define KEY_ENTER`
  - `KEY_TAB` (macro, line 37) `#define KEY_TAB`
  - `KEY_F1` (macro, line 38) `#define KEY_F1`
  - `KEY_F2` (macro, line 39) `#define KEY_F2`
  - `KEY_F3` (macro, line 40) `#define KEY_F3`
  - `KEY_F4` (macro, line 41) `#define KEY_F4`
  - `KEY_F5` (macro, line 42) `#define KEY_F5`
  - `KEY_F6` (macro, line 43) `#define KEY_F6`
  - `KEY_F7` (macro, line 44) `#define KEY_F7`
  - `KEY_F8` (macro, line 45) `#define KEY_F8`
  - `KEY_F9` (macro, line 46) `#define KEY_F9`
  - `KEY_F10` (macro, line 47) `#define KEY_F10`
  - `KEY_F11` (macro, line 48) `#define KEY_F11`
  - `KEY_F12` (macro, line 49) `#define KEY_F12`
  - `KEY_BACKSPACE` (macro, line 51) `#define KEY_BACKSPACE`
  - `KEY_PAUSE` (macro, line 52) `#define KEY_PAUSE`
  - `KEY_EQUALS` (macro, line 54) `#define KEY_EQUALS`
  - `KEY_MINUS` (macro, line 55) `#define KEY_MINUS`
  - `KEY_RSHIFT` (macro, line 57) `#define KEY_RSHIFT`
  - `KEY_RCTRL` (macro, line 58) `#define KEY_RCTRL`
  - `KEY_RALT` (macro, line 59) `#define KEY_RALT`
  - `KEY_LALT` (macro, line 61) `#define KEY_LALT`
  - `KEY_CAPSLOCK` (macro, line 65) `#define KEY_CAPSLOCK`
  - `KEY_NUMLOCK` (macro, line 66) `#define KEY_NUMLOCK`
  - `KEY_SCRLCK` (macro, line 67) `#define KEY_SCRLCK`
  - `KEY_PRTSCR` (macro, line 68) `#define KEY_PRTSCR`
  - `KEY_HOME` (macro, line 70) `#define KEY_HOME`
  - `KEY_END` (macro, line 71) `#define KEY_END`
  - `KEY_PGUP` (macro, line 72) `#define KEY_PGUP`
  - `KEY_PGDN` (macro, line 73) `#define KEY_PGDN`
  - `KEY_INS` (macro, line 74) `#define KEY_INS`
  - `KEY_DEL` (macro, line 75) `#define KEY_DEL`
  - `KEYP_0` (macro, line 77) `#define KEYP_0`
  - `KEYP_1` (macro, line 78) `#define KEYP_1`
  - `KEYP_2` (macro, line 79) `#define KEYP_2`
  - `KEYP_3` (macro, line 80) `#define KEYP_3`
  - `KEYP_4` (macro, line 81) `#define KEYP_4`
  - `KEYP_5` (macro, line 82) `#define KEYP_5`
  - `KEYP_6` (macro, line 83) `#define KEYP_6`
  - `KEYP_7` (macro, line 84) `#define KEYP_7`
  - `KEYP_8` (macro, line 85) `#define KEYP_8`
  - `KEYP_9` (macro, line 86) `#define KEYP_9`
  - `KEYP_DIVIDE` (macro, line 88) `#define KEYP_DIVIDE`
  - `KEYP_PLUS` (macro, line 89) `#define KEYP_PLUS`
  - `KEYP_MINUS` (macro, line 90) `#define KEYP_MINUS`
  - `KEYP_MULTIPLY` (macro, line 91) `#define KEYP_MULTIPLY`
  - `KEYP_PERIOD` (macro, line 92) `#define KEYP_PERIOD`
  - `KEYP_EQUALS` (macro, line 93) `#define KEYP_EQUALS`
  - `KEYP_ENTER` (macro, line 94) `#define KEYP_ENTER`
- Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_iwad.c`, `progs/doomgeneric/doomgeneric_minios.c`, `progs/doomgeneric/doomgeneric_sdl.c`, `progs/doomgeneric/doomgeneric_soso.c`, `progs/doomgeneric/doomgeneric_sosox.c`, `progs/doomgeneric/doomgeneric_win.c`, `progs/doomgeneric/doomgeneric_xlib.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/hu_lib.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_video.c`, `progs/doomgeneric/m_config.c`, `progs/doomgeneric/m_controls.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/st_stuff.c`

## progs/doomgeneric/doomstat.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Depends on: `progs/doomgeneric/doomstat.h`

## progs/doomgeneric/doomstat.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `nomonsters` (variable, line 46) `extern boolean nomonsters;`
  - `respawnparm` (variable, line 47) `extern boolean respawnparm;`
  - `fastparm` (variable, line 48) `extern boolean fastparm;`
  - `devparm` (variable, line 50) `extern boolean devparm;`
  - `gamemode` (variable, line 56) `extern GameMode_t gamemode;`
  - `gamemission` (variable, line 57) `extern GameMission_t gamemission;`
  - `gameversion` (variable, line 58) `extern GameVersion_t gameversion;`
  - `gamedescription` (variable, line 59) `extern char *gamedescription;`
  - `bfgedition` (variable, line 62) `extern boolean bfgedition;`
  - `modifiedgame` (variable, line 74) `extern boolean modifiedgame;`
  - `startskill` (variable, line 82) `extern skill_t startskill;`
  - `startepisode` (variable, line 83) `extern int startepisode;`
  - `startmap` (variable, line 84) `extern int startmap;`
  - `startloadgame` (variable, line 89) `extern int startloadgame;`
  - `autostart` (variable, line 91) `extern boolean autostart;`
  - `gameskill` (variable, line 94) `extern skill_t gameskill;`
  - `gameepisode` (variable, line 95) `extern int gameepisode;`
  - `gamemap` (variable, line 96) `extern int gamemap;`
  - `timelimit` (variable, line 99) `extern int timelimit;`
  - `respawnmonsters` (variable, line 102) `extern boolean respawnmonsters;`
  - `netgame` (variable, line 105) `extern boolean netgame;`
  - `deathmatch` (variable, line 108) `extern int deathmatch;`
  - `sfxVolume` (variable, line 120) `extern int sfxVolume;`
  - `musicVolume` (variable, line 121) `extern int musicVolume;`
  - `snd_MusicDevice` (variable, line 127) `extern int snd_MusicDevice;`
  - `snd_SfxDevice` (variable, line 128) `extern int snd_SfxDevice;`
  - `snd_DesiredMusicDevice` (variable, line 130) `extern int snd_DesiredMusicDevice;`
  - `snd_DesiredSfxDevice` (variable, line 131) `extern int snd_DesiredSfxDevice;`
  - `statusbaractive` (variable, line 141) `extern boolean statusbaractive;`
  - `automapactive` (variable, line 143) `extern boolean automapactive;`
  - `menuactive` (variable, line 144) `extern boolean menuactive;`
  - `paused` (variable, line 145) `extern boolean paused;`
  - `viewactive` (variable, line 148) `extern boolean viewactive;`
  - `nodrawers` (variable, line 150) `extern boolean nodrawers;`
  - `testcontrols` (variable, line 153) `extern boolean testcontrols;`
  - `testcontrols_mousespeed` (variable, line 154) `extern int testcontrols_mousespeed;`
  - `viewangleoffset` (variable, line 161) `extern int viewangleoffset;`
  - `consoleplayer` (variable, line 164) `extern int consoleplayer;`
  - `displayplayer` (variable, line 165) `extern int displayplayer;`
  - `totalkills` (variable, line 172) `extern int totalkills;`
  - `totalitems` (variable, line 173) `extern int totalitems;`
  - `totalsecret` (variable, line 174) `extern int totalsecret;`
  - `levelstarttic` (variable, line 177) `extern int levelstarttic;`
  - `leveltime` (variable, line 178) `extern int leveltime;`
  - `usergame` (variable, line 186) `extern boolean usergame;`
  - `demoplayback` (variable, line 189) `extern boolean demoplayback;`
  - `demorecording` (variable, line 190) `extern boolean demorecording;`
  - `lowres_turn` (variable, line 195) `extern boolean lowres_turn;`
  - `singledemo` (variable, line 198) `extern boolean singledemo;`
  - `gamestate` (variable, line 204) `extern gamestate_t gamestate;`
  - `players` (variable, line 220) `extern player_t players[MAXPLAYERS];`
  - `playeringame` (variable, line 223) `extern boolean playeringame[MAXPLAYERS];`
  - `deathmatchstarts` (variable, line 228) `extern mapthing_t deathmatchstarts[MAX_DM_STARTS];`
  - `deathmatch_p` (variable, line 229) `extern mapthing_t* deathmatch_p;`
  - `playerstarts` (variable, line 232) `extern mapthing_t playerstarts[MAXPLAYERS];`
  - `wminfo` (variable, line 236) `extern wbstartstruct_t wminfo;`
  - `savegamedir` (variable, line 249) `extern char * savegamedir;`
  - `basedefault` (variable, line 250) `extern char basedefault[1024];`
  - `precache` (variable, line 253) `extern boolean precache;`
  - `wipegamestate` (variable, line 258) `extern gamestate_t wipegamestate;`
  - `mouseSensitivity` (variable, line 260) `extern int mouseSensitivity;`
  - `bodyqueslot` (variable, line 262) `extern int bodyqueslot;`
  - `skyflatnum` (variable, line 269) `extern int skyflatnum;`
  - `rndindex` (variable, line 276) `extern int rndindex;`
  - `netcmds` (variable, line 278) `extern ticcmd_t *netcmds;`
  - `__D_STATE__` (macro, line 26) `#define __D_STATE__`
  - `logical_gamemission` (macro, line 69) `#define logical_gamemission`
  - `MAX_DM_STARTS` (macro, line 227) `#define MAX_DM_STARTS`
- Depends on: `progs/doomgeneric/d_loop.h`, `progs/doomgeneric/d_mode.h`, `progs/doomgeneric/d_player.h`, `progs/doomgeneric/doomdata.h`, `progs/doomgeneric/net_defs.h`
- Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/doomstat.c`, `progs/doomgeneric/f_finale.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/p_ceilng.c`, `progs/doomgeneric/p_doors.c`, `progs/doomgeneric/p_enemy.c`, `progs/doomgeneric/p_floor.c`, `progs/doomgeneric/p_inter.c`, `progs/doomgeneric/p_map.c`, `progs/doomgeneric/p_maputl.c`, `progs/doomgeneric/p_mobj.c`, `progs/doomgeneric/p_plats.c`, `progs/doomgeneric/p_pspr.c`, `progs/doomgeneric/p_saveg.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/p_switch.c`, `progs/doomgeneric/p_telept.c`, `progs/doomgeneric/p_tick.c`, `progs/doomgeneric/p_user.c`, `progs/doomgeneric/r_bsp.c`, `progs/doomgeneric/r_data.c`, `progs/doomgeneric/r_draw.c`, `progs/doomgeneric/r_plane.c`, `progs/doomgeneric/r_segs.c`, `progs/doomgeneric/r_things.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/wi_stuff.c`

## progs/doomgeneric/doomtype.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `boolean` (type_alias, line 68) `typedef bool boolean;`
  - `byte` (type_alias, line 81) `typedef uint8_t byte;`
  - `__DOOMTYPE__` (macro, line 22) `#define __DOOMTYPE__`
  - `strcasecmp` (macro, line 30) `#define strcasecmp`
  - `strncasecmp` (macro, line 31) `#define strncasecmp`
  - `PACKEDATTR` (macro, line 50) `#define PACKEDATTR`
  - `PACKEDATTR` (macro, line 52) `#define PACKEDATTR`
  - `DIR_SEPARATOR` (macro, line 88) `#define DIR_SEPARATOR`
  - `DIR_SEPARATOR_S` (macro, line 89) `#define DIR_SEPARATOR_S`
  - `PATH_SEPARATOR` (macro, line 90) `#define PATH_SEPARATOR`
  - `DIR_SEPARATOR` (macro, line 94) `#define DIR_SEPARATOR`
  - `DIR_SEPARATOR_S` (macro, line 95) `#define DIR_SEPARATOR_S`
  - `PATH_SEPARATOR` (macro, line 96) `#define PATH_SEPARATOR`
  - `arrlen` (macro, line 100) `#define arrlen(array)`
- Imported by: `progs/doomgeneric/d_event.h`, `progs/doomgeneric/d_mode.c`, `progs/doomgeneric/d_mode.h`, `progs/doomgeneric/d_textur.h`, `progs/doomgeneric/d_ticcmd.h`, `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdata.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/dummy.c`, `progs/doomgeneric/f_finale.h`, `progs/doomgeneric/f_wipe.c`, `progs/doomgeneric/gusconf.h`, `progs/doomgeneric/i_cdmus.c`, `progs/doomgeneric/i_endoom.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_joystick.c`, `progs/doomgeneric/i_minios_sound.c`, `progs/doomgeneric/i_scale.c`, `progs/doomgeneric/i_scale.h`, `progs/doomgeneric/i_sound.c`, `progs/doomgeneric/i_sound.h`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/i_timer.c`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.c`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_cheat.c`, `progs/doomgeneric/m_config.c`, `progs/doomgeneric/m_config.h`, `progs/doomgeneric/m_controls.c`, `progs/doomgeneric/m_fixed.c`, `progs/doomgeneric/m_misc.c`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/net_client.h`, `progs/doomgeneric/net_defs.h`, `progs/doomgeneric/net_gui.h`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/sha1.h`, `progs/doomgeneric/sounds.c`, `progs/doomgeneric/st_stuff.h`, `progs/doomgeneric/tables.h`, `progs/doomgeneric/v_video.c`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_checksum.h`, `progs/doomgeneric/w_file.c`, `progs/doomgeneric/w_file.h`, `progs/doomgeneric/w_wad.c`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.c`

## progs/doomgeneric/dstrings.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Depends on: `progs/doomgeneric/dstrings.h`

## progs/doomgeneric/dstrings.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `doom1_endmsg` (variable, line 37) `extern char *doom1_endmsg[];`
  - `doom2_endmsg` (variable, line 38) `extern char *doom2_endmsg[];`
  - `__DSTRINGS__` (macro, line 22) `#define __DSTRINGS__`
  - `SAVEGAMENAME` (macro, line 30) `#define SAVEGAMENAME`
  - `NUM_QUITMESSAGES` (macro, line 35) `#define NUM_QUITMESSAGES`
- Depends on: `progs/doomgeneric/d_englsh.h`
- Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/dstrings.c`, `progs/doomgeneric/f_finale.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/p_doors.c`, `progs/doomgeneric/p_inter.c`, `progs/doomgeneric/p_saveg.c`, `progs/doomgeneric/st_stuff.c`

## progs/doomgeneric/dummy.c
- Layer: utility
- Language: c
- Symbols:
  - `I_InitTimidityConfig` (function, line 43) `void I_InitTimidityConfig(void)`
- Depends on: `progs/doomgeneric/doomtype.h`

## progs/doomgeneric/f_finale.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `textscreen_t` (struct, line 60)
  - `castinfo_t` (struct, line 300)
  - `F_StartFinale` (function, line 108) `void F_StartFinale (void)`
  - `F_Responder` (function, line 160) `boolean F_Responder (event_t *event)`
  - `F_Ticker` (function, line 172) `void F_Ticker (void)`
  - `F_TextWrite` (function, line 227) `void F_TextWrite (void)`
  - `F_StartCast` (function, line 340) `void F_StartCast (void)`
  - `F_CastTicker` (function, line 358) `void F_CastTicker (void)`
  - `F_CastResponder` (function, line 465) `boolean F_CastResponder (event_t* ev)`
  - `F_CastPrint` (function, line 486) `void F_CastPrint (char* text)`
  - `F_CastDrawer` (function, line 541) `void F_CastDrawer (void)`
  - `F_DrawPatchCol` (function, line 572) `void
F_DrawPatchCol
( int		x,
  patch_t*	patch,
  int		col )`
  - `F_BunnyScroll` (function, line 606) `void F_BunnyScroll (void)`
  - `F_ArtScreenDrawer` (function, line 661) `static void F_ArtScreenDrawer(void)`
  - `F_Drawer` (function, line 702) `void F_Drawer (void)`
  - `hu_font` (variable, line 224) `extern patch_t *hu_font[HU_FONTSIZE];`
  - `TEXTSPEED` (macro, line 57) `#define	TEXTSPEED`
  - `TEXTWAIT` (macro, line 58) `#define	TEXTWAIT`
- Depends on: `progs/doomgeneric/d_main.h`, `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/dstrings.h`, `progs/doomgeneric/hu_stuff.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/f_finale.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `F_Ticker` (function, line 34) `void F_Ticker (void);`
  - `F_Drawer` (function, line 37) `void F_Drawer (void);`
  - `F_StartFinale` (function, line 40) `void F_StartFinale (void);`
  - `__F_FINALE__` (macro, line 21) `#define __F_FINALE__`
- Depends on: `progs/doomgeneric/d_event.h`, `progs/doomgeneric/doomtype.h`
- Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/g_game.c`

## progs/doomgeneric/f_wipe.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `wipe_shittyColMajorXform` (function, line 43) `void
wipe_shittyColMajorXform
( short*	array,
  int		width,
  int		height )`
  - `wipe_initColorXForm` (function, line 65) `int
wipe_initColorXForm
( int	width,
  int	height,
  int	ticks )`
  - `wipe_doColorXForm` (function, line 75) `int
wipe_doColorXForm
( int	width,
  int	height,
  int	ticks )`
  - `wipe_exitColorXForm` (function, line 121) `int
wipe_exitColorXForm
( int	width,
  int	height,
  int	ticks )`
  - `wipe_initMelt` (function, line 133) `int
wipe_initMelt
( int	width,
  int	height,
  int	ticks )`
  - `wipe_doMelt` (function, line 164) `int
wipe_doMelt
( int	width,
  int	height,
  int	ticks )`
  - `wipe_exitMelt` (function, line 219) `int
wipe_exitMelt
( int	width,
  int	height,
  int	ticks )`
  - `wipe_StartScreen` (function, line 231) `int
wipe_StartScreen
( int	x,
  int	y,
  int	width,
  int	height )`
  - `wipe_EndScreen` (function, line 243) `int
wipe_EndScreen
( int	x,
  int	y,
  int	width,
  int	height )`
  - `wipe_ScreenWipe` (function, line 256) `int
wipe_ScreenWipe
( int	wipeno,
  int	x,
  int	y,
  int	width,
  int	height,
  int	ticks )`
- Depends on: `kernel/string.c`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/f_wipe.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/f_wipe.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `wipe_StartScreen` (function, line 39) `int wipe_StartScreen ( int x, int y, int width, int height );`
  - `wipe_EndScreen` (function, line 47) `int wipe_EndScreen ( int x, int y, int width, int height );`
  - `wipe_ScreenWipe` (function, line 55) `int wipe_ScreenWipe ( int wipeno, int x, int y, int width, int height, int ticks );`
  - `__F_WIPE_H__` (macro, line 21) `#define __F_WIPE_H__`
- Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/f_wipe.c`

## progs/doomgeneric/g_game.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `G_CmdChecksum` (function, line 233) `int G_CmdChecksum (ticcmd_t* cmd)`
  - `WeaponSelectable` (function, line 244) `static boolean WeaponSelectable(weapontype_t weapon)`
  - `G_NextWeapon` (function, line 281) `static int G_NextWeapon(int direction)`
  - `G_BuildTiccmd` (function, line 322) `void G_BuildTiccmd (ticcmd_t* cmd, int maketic)`
  - `G_DoLoadLevel` (function, line 603) `void G_DoLoadLevel (void)`
  - `SetJoyButtons` (function, line 675) `static void SetJoyButtons(unsigned int buttons_mask)`
  - `SetMouseButtons` (function, line 703) `static void SetMouseButtons(unsigned int buttons_mask)`
  - `G_Responder` (function, line 733) `boolean G_Responder (event_t* ev)`
  - `G_Ticker` (function, line 854) `void G_Ticker (void)`
  - `G_InitPlayer` (function, line 1039) `void G_InitPlayer (int player)`
  - `G_PlayerFinishLevel` (function, line 1051) `void G_PlayerFinishLevel (int player)`
  - `G_PlayerReborn` (function, line 1072) `void G_PlayerReborn (int player)`
  - `G_CheckSpot` (function, line 1116) `boolean
G_CheckSpot
( int		playernum,
  mapthing_t*	mthing )`
  - `G_DeathMatchSpawnPlayer` (function, line 1223) `void G_DeathMatchSpawnPlayer (int playernum)`
  - `G_DoReborn` (function, line 1250) `void G_DoReborn (int playernum)`
  - `G_ScreenShot` (function, line 1296) `void G_ScreenShot (void)`
  - `G_ExitLevel` (function, line 1328) `void G_ExitLevel (void)`
  - `G_SecretExitLevel` (function, line 1335) `void G_SecretExitLevel (void)`
  - `G_DoCompleted` (function, line 1346) `void G_DoCompleted (void)`
  - `G_WorldDone` (function, line 1494) `void G_WorldDone (void)`
  - `G_DoWorldDone` (function, line 1519) `void G_DoWorldDone (void)`
  - `G_LoadGame` (function, line 1539) `void G_LoadGame (char* name)`
  - `G_DoLoadGame` (function, line 1548) `void G_DoLoadGame (void)`
  - `G_SaveGame` (function, line 1601) `void
G_SaveGame
( int	slot,
  char*	description )`
  - `G_DoSaveGame` (function, line 1610) `void G_DoSaveGame (void)`
  - `G_DeferedInitNew` (function, line 1698) `void
G_DeferedInitNew
( skill_t	skill,
  int		episode,
  int		map)`
  - `G_DoNewGame` (function, line 1710) `void G_DoNewGame (void)`
  - `G_InitNew` (function, line 1727) `void
G_InitNew
( skill_t	skill,
  int		episode,
  int		map )`
  - `G_ReadDemoTiccmd` (function, line 1898) `void G_ReadDemoTiccmd (ticcmd_t* cmd)`
  - `IncreaseDemoBuffer` (function, line 1926) `static void IncreaseDemoBuffer(void)`
  - `G_WriteDemoTiccmd` (function, line 1956) `void G_WriteDemoTiccmd (ticcmd_t* cmd)`
  - `G_RecordDemo` (function, line 2010) `void G_RecordDemo (char *name)`
  - `G_VanillaVersionCode` (function, line 2040) `int G_VanillaVersionCode(void)`
  - `G_BeginRecording` (function, line 2058) `void G_BeginRecording (void)`
  - `G_DeferedPlayDemo` (function, line 2107) `void G_DeferedPlayDemo (char* name)`
  - `DemoVersionDescription` (function, line 2115) `static char *DemoVersionDescription(int version)`
  - `G_DoPlayDemo` (function, line 2152) `void G_DoPlayDemo (void)`
  - `G_TimeDemo` (function, line 2215) `void G_TimeDemo (char* name)`
  - `G_CheckDemoStatus` (function, line 2243) `boolean G_CheckDemoStatus (void)`
  - `G_DoVictory` (function, line 88) `void G_DoVictory (void);`
  - `P_SpawnPlayer` (function, line 1113) `void P_SpawnPlayer (mapthing_t* mthing);`
  - `R_ExecuteSetViewSize` (function, line 1535) `void R_ExecuteSetViewSize (void);`
  - `player_names` (variable, line 939) `extern char *player_names[4];`
  - `pagename` (variable, line 1326) `extern char* pagename;`
  - `setsizeneeded` (variable, line 1534) `extern boolean setsizeneeded;`
  - `SAVEGAMESIZE` (macro, line 76) `#define SAVEGAMESIZE`
  - `MAXPLMOVE` (macro, line 152) `#define MAXPLMOVE`
  - `TURBOTHRESHOLD` (macro, line 154) `#define TURBOTHRESHOLD`
  - `SLOWTURNTICS` (macro, line 193) `#define SLOWTURNTICS`
  - `NUMKEYS` (macro, line 195) `#define NUMKEYS`
  - `MAX_JOY_BUTTONS` (macro, line 196) `#define MAX_JOY_BUTTONS`
  - `BODYQUESIZE` (macro, line 225) `#define	BODYQUESIZE`
  - `VERSIONSIZE` (macro, line 1545) `#define VERSIONSIZE`
  - `DEMOMARKER` (macro, line 1895) `#define DEMOMARKER`
- Depends on: `kernel/string.c`, `progs/doomgeneric/am_map.h`, `progs/doomgeneric/d_main.h`, `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/deh_misc.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/dstrings.h`, `progs/doomgeneric/f_finale.h`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/hu_stuff.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/i_timer.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_controls.h`, `progs/doomgeneric/m_menu.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/p_saveg.h`, `progs/doomgeneric/p_setup.h`, `progs/doomgeneric/p_tick.h`, `progs/doomgeneric/r_data.h`, `progs/doomgeneric/r_sky.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/st_stuff.h`, `progs/doomgeneric/statdump.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/wi_stuff.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/g_game.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `G_DeathMatchSpawnPlayer` (function, line 31) `void G_DeathMatchSpawnPlayer (int playernum);`
  - `G_InitNew` (function, line 33) `void G_InitNew (skill_t skill, int episode, int map);`
  - `G_DeferedInitNew` (function, line 38) `void G_DeferedInitNew (skill_t skill, int episode, int map);`
  - `G_DeferedPlayDemo` (function, line 40) `void G_DeferedPlayDemo (char* demo);`
  - `G_LoadGame` (function, line 44) `void G_LoadGame (char* name);`
  - `G_DoLoadGame` (function, line 46) `void G_DoLoadGame (void);`
  - `G_SaveGame` (function, line 49) `void G_SaveGame (int slot, char* description);`
  - `G_RecordDemo` (function, line 52) `void G_RecordDemo (char* name);`
  - `G_BeginRecording` (function, line 54) `void G_BeginRecording (void);`
  - `G_PlayDemo` (function, line 56) `void G_PlayDemo (char* name);`
  - `G_TimeDemo` (function, line 57) `void G_TimeDemo (char* name);`
  - `G_ExitLevel` (function, line 60) `void G_ExitLevel (void);`
  - `G_SecretExitLevel` (function, line 61) `void G_SecretExitLevel (void);`
  - `G_WorldDone` (function, line 63) `void G_WorldDone (void);`
  - `G_BuildTiccmd` (function, line 67) `void G_BuildTiccmd (ticcmd_t *cmd, int maketic);`
  - `G_Ticker` (function, line 69) `void G_Ticker (void);`
  - `G_ScreenShot` (function, line 72) `void G_ScreenShot (void);`
  - `G_DrawMouseSpeedBox` (function, line 74) `void G_DrawMouseSpeedBox(void);`
  - `G_VanillaVersionCode` (function, line 75) `int G_VanillaVersionCode(void);`
  - `vanilla_savegame_limit` (variable, line 77) `extern int vanilla_savegame_limit;`
  - `vanilla_demo_limit` (variable, line 78) `extern int vanilla_demo_limit;`
  - `__G_GAME__` (macro, line 21) `#define __G_GAME__`
- Depends on: `progs/doomgeneric/d_event.h`, `progs/doomgeneric/d_ticcmd.h`, `progs/doomgeneric/doomdef.h`
- Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/p_enemy.c`, `progs/doomgeneric/p_saveg.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/p_switch.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/wi_stuff.c`

## progs/doomgeneric/gusconf.c
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: c
- Symbols:
  - `gus_config_t` (struct, line 34)
  - `MappingIndex` (function, line 43) `static unsigned int MappingIndex(void)`
  - `SplitLine` (function, line 61) `static int SplitLine(char *line, char **fields, unsigned int max_fields)`
  - `ParseLine` (function, line 108) `static void ParseLine(gus_config_t *config, char *line)`
  - `ParseDMXConfig` (function, line 129) `static void ParseDMXConfig(char *dmxconf, gus_config_t *config)`
  - `FreeDMXConfig` (function, line 165) `static void FreeDMXConfig(gus_config_t *config)`
  - `ReadDMXConfig` (function, line 175) `static char *ReadDMXConfig(void)`
  - `WriteTimidityConfig` (function, line 197) `static boolean WriteTimidityConfig(char *path, gus_config_t *config)`
  - `GUS_WriteConfig` (function, line 244) `boolean GUS_WriteConfig(char *path)`
  - `MAX_INSTRUMENTS` (macro, line 32) `#define MAX_INSTRUMENTS`
- Depends on: `kernel/string.c`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/gusconf.h
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `gus_patch_path` (variable, line 23) `extern char *gus_patch_path;`
  - `gus_ram_kb` (variable, line 24) `extern unsigned int gus_ram_kb;`
  - `__GUSCONF_H__` (macro, line 19) `#define __GUSCONF_H__`
- Depends on: `progs/doomgeneric/doomtype.h`
- Imported by: `progs/doomgeneric/i_sound.c`

## progs/doomgeneric/hu_lib.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `HUlib_init` (function, line 36) `void HUlib_init(void)`
  - `HUlib_clearTextLine` (function, line 40) `void HUlib_clearTextLine(hu_textline_t* t)`
  - `HUlib_initTextLine` (function, line 48) `void
HUlib_initTextLine
( hu_textline_t*	t,
  int			x,
  int			y,
  patch_t**		f,
  int			sc )`
  - `HUlib_addCharToTextLine` (function, line 63) `boolean
HUlib_addCharToTextLine
( hu_textline_t*	t,
  char			ch )`
  - `HUlib_delCharFromTextLine` (function, line 80) `boolean HUlib_delCharFromTextLine(hu_textline_t* t)`
  - `HUlib_drawTextLine` (function, line 94) `void
HUlib_drawTextLine
( hu_textline_t*	l,
  boolean		drawcursor )`
  - `HUlib_eraseTextLine` (function, line 137) `void HUlib_eraseTextLine(hu_textline_t* l)`
  - `HUlib_initSText` (function, line 169) `void
HUlib_initSText
( hu_stext_t*	s,
  int		x,
  int		y,
  int		h,
  patch_t**	font,
  int		star...`
  - `HUlib_addLineToSText` (function, line 192) `void HUlib_addLineToSText(hu_stext_t* s)`
  - `HUlib_addMessageToSText` (function, line 209) `void
HUlib_addMessageToSText
( hu_stext_t*	s,
  char*		prefix,
  char*		msg )`
  - `HUlib_drawSText` (function, line 223) `void HUlib_drawSText(hu_stext_t* s)`
  - `HUlib_eraseSText` (function, line 246) `void HUlib_eraseSText(hu_stext_t* s)`
  - `HUlib_initIText` (function, line 262) `void
HUlib_initIText
( hu_itext_t*	it,
  int		x,
  int		y,
  patch_t**	font,
  int		startchar,
  ...`
  - `HUlib_delCharFromIText` (function, line 278) `void HUlib_delCharFromIText(hu_itext_t* it)`
  - `HUlib_eraseLineFromIText` (function, line 284) `void HUlib_eraseLineFromIText(hu_itext_t* it)`
  - `HUlib_resetIText` (function, line 291) `void HUlib_resetIText(hu_itext_t* it)`
  - `HUlib_addPrefixToIText` (function, line 298) `void
HUlib_addPrefixToIText
( hu_itext_t*	it,
  char*		str )`
  - `HUlib_keyInIText` (function, line 310) `boolean
HUlib_keyInIText
( hu_itext_t*	it,
  unsigned char ch )`
  - `HUlib_drawIText` (function, line 329) `void HUlib_drawIText(hu_itext_t* it)`
  - `HUlib_eraseIText` (function, line 340) `void HUlib_eraseIText(hu_itext_t* it)`
  - `automapactive` (variable, line 34) `extern boolean automapactive;`
  - `noterased` (macro, line 32) `#define noterased`
- Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/hu_lib.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/r_draw.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/v_video.h`

## progs/doomgeneric/hu_lib.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `hu_textline_t` (struct, line 36)
  - `hu_stext_t` (struct, line 56)
  - `hu_itext_t` (struct, line 72)
  - `HUlib_init` (function, line 91) `void HUlib_init(void);`
  - `HUlib_clearTextLine` (function, line 98) `void HUlib_clearTextLine(hu_textline_t *t);`
  - `HUlib_initTextLine` (function, line 100) `void HUlib_initTextLine(hu_textline_t *t, int x, int y, patch_t **f, int sc);`
  - `HUlib_drawTextLine` (function, line 109) `void HUlib_drawTextLine(hu_textline_t *l, boolean drawcursor);`
  - `HUlib_eraseTextLine` (function, line 112) `void HUlib_eraseTextLine(hu_textline_t *l);`
  - `HUlib_initSText` (function, line 121) `void HUlib_initSText ( hu_stext_t* s, int x, int y, int h, patch_t** font, int startchar, boolean* on );`
  - `HUlib_addLineToSText` (function, line 131) `void HUlib_addLineToSText(hu_stext_t* s);`
  - `HUlib_addMessageToSText` (function, line 135) `void HUlib_addMessageToSText ( hu_stext_t* s, char* prefix, char* msg );`
  - `HUlib_drawSText` (function, line 141) `void HUlib_drawSText(hu_stext_t* s);`
  - `HUlib_eraseSText` (function, line 144) `void HUlib_eraseSText(hu_stext_t* s);`
  - `HUlib_initIText` (function, line 148) `void HUlib_initIText ( hu_itext_t* it, int x, int y, patch_t** font, int startchar, boolean* on );`
  - `HUlib_delCharFromIText` (function, line 157) `void HUlib_delCharFromIText(hu_itext_t* it);`
  - `HUlib_eraseLineFromIText` (function, line 160) `void HUlib_eraseLineFromIText(hu_itext_t* it);`
  - `HUlib_resetIText` (function, line 163) `void HUlib_resetIText(hu_itext_t* it);`
  - `HUlib_addPrefixToIText` (function, line 167) `void HUlib_addPrefixToIText ( hu_itext_t* it, char* str );`
  - `HUlib_drawIText` (function, line 177) `void HUlib_drawIText(hu_itext_t* it);`
  - `HUlib_eraseIText` (function, line 180) `void HUlib_eraseIText(hu_itext_t* it);`
  - `__HULIB__` (macro, line 19) `#define __HULIB__`
  - `HU_CHARERASE` (macro, line 25) `#define HU_CHARERASE`
  - `HU_MAXLINES` (macro, line 27) `#define HU_MAXLINES`
  - `HU_MAXLINELENGTH` (macro, line 28) `#define HU_MAXLINELENGTH`
- Depends on: `progs/doomgeneric/r_defs.h`
- Imported by: `progs/doomgeneric/hu_lib.c`, `progs/doomgeneric/hu_stuff.c`

## progs/doomgeneric/hu_stuff.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `HU_Init` (function, line 286) `void HU_Init(void)`
  - `HU_Stop` (function, line 303) `void HU_Stop(void)`
  - `HU_Start` (function, line 308) `void HU_Start(void)`
  - `HU_Drawer` (function, line 383) `void HU_Drawer(void)`
  - `HU_Erase` (function, line 393) `void HU_Erase(void)`
  - `HU_Ticker` (function, line 402) `void HU_Ticker(void)`
  - `HU_queueChatChar` (function, line 482) `void HU_queueChatChar(char c)`
  - `HU_dequeueChatChar` (function, line 495) `char HU_dequeueChatChar(void)`
  - `HU_Responder` (function, line 512) `boolean HU_Responder(event_t *ev)`
  - `showMessages` (variable, line 103) `extern int showMessages;`
  - `HU_TITLE` (macro, line 47) `#define HU_TITLE`
  - `HU_TITLE2` (macro, line 48) `#define HU_TITLE2`
  - `HU_TITLEP` (macro, line 49) `#define HU_TITLEP`
  - `HU_TITLET` (macro, line 50) `#define HU_TITLET`
  - `HU_TITLE_CHEX` (macro, line 51) `#define HU_TITLE_CHEX`
  - `HU_TITLEHEIGHT` (macro, line 52) `#define HU_TITLEHEIGHT`
  - `HU_TITLEX` (macro, line 53) `#define HU_TITLEX`
  - `HU_TITLEY` (macro, line 54) `#define HU_TITLEY`
  - `HU_INPUTTOGGLE` (macro, line 56) `#define HU_INPUTTOGGLE`
  - `HU_INPUTX` (macro, line 57) `#define HU_INPUTX`
  - `HU_INPUTY` (macro, line 58) `#define HU_INPUTY`
  - `HU_INPUTWIDTH` (macro, line 59) `#define HU_INPUTWIDTH`
  - `HU_INPUTHEIGHT` (macro, line 60) `#define HU_INPUTHEIGHT`
  - `QUEUESIZE` (macro, line 475) `#define QUEUESIZE`
- Depends on: `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/dstrings.h`, `progs/doomgeneric/hu_lib.h`, `progs/doomgeneric/hu_stuff.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_controls.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/hu_stuff.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `HU_Init` (function, line 46) `void HU_Init(void);`
  - `HU_Start` (function, line 47) `void HU_Start(void);`
  - `HU_Ticker` (function, line 51) `void HU_Ticker(void);`
  - `HU_Drawer` (function, line 52) `void HU_Drawer(void);`
  - `HU_dequeueChatChar` (function, line 53) `char HU_dequeueChatChar(void);`
  - `HU_Erase` (function, line 54) `void HU_Erase(void);`
  - `chat_macros` (variable, line 56) `extern char *chat_macros[10];`
  - `__HU_STUFF_H__` (macro, line 19) `#define __HU_STUFF_H__`
  - `HU_FONTSTART` (macro, line 27) `#define HU_FONTSTART`
  - `HU_FONTEND` (macro, line 28) `#define HU_FONTEND`
  - `HU_FONTSIZE` (macro, line 31) `#define HU_FONTSIZE`
  - `HU_BROADCAST` (macro, line 33) `#define HU_BROADCAST`
  - `HU_MSGX` (macro, line 35) `#define HU_MSGX`
  - `HU_MSGY` (macro, line 36) `#define HU_MSGY`
  - `HU_MSGWIDTH` (macro, line 37) `#define HU_MSGWIDTH`
  - `HU_MSGHEIGHT` (macro, line 38) `#define HU_MSGHEIGHT`
  - `HU_MSGTIMEOUT` (macro, line 40) `#define HU_MSGTIMEOUT`
- Depends on: `progs/doomgeneric/d_event.h`
- Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/f_finale.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/p_mobj.c`

## progs/doomgeneric/i_cdmus.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software  This program is free software; you can r
- Language: c
- Symbols:
  - `I_CDMusInit` (function, line 38) `int I_CDMusInit(void)`
  - `I_CDMusPrintStartup` (function, line 92) `void I_CDMusPrintStartup(void)`
  - `I_CDMusPlay` (function, line 107) `int I_CDMusPlay(int track)`
  - `I_CDMusStop` (function, line 130) `int I_CDMusStop(void)`
  - `I_CDMusResume` (function, line 145) `int I_CDMusResume(void)`
  - `I_CDMusSetVolume` (function, line 160) `int I_CDMusSetVolume(int volume)`
  - `I_CDMusFirstTrack` (function, line 169) `int I_CDMusFirstTrack(void)`
  - `I_CDMusLastTrack` (function, line 202) `int I_CDMusLastTrack(void)`
  - `I_CDMusTrackLength` (function, line 219) `int I_CDMusTrackLength(int track_num)`
- Depends on: `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_cdmus.h`, `progs/pokemon/minios_stubs/SDL.h`

## progs/doomgeneric/i_cdmus.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software  This program is free software; you can r
- Language: h
- Symbols:
  - `I_CDMusInit` (function, line 31) `int I_CDMusInit(void);`
  - `I_CDMusPrintStartup` (function, line 32) `void I_CDMusPrintStartup(void);`
  - `I_CDMusPlay` (function, line 33) `int I_CDMusPlay(int track);`
  - `I_CDMusStop` (function, line 34) `int I_CDMusStop(void);`
  - `I_CDMusResume` (function, line 35) `int I_CDMusResume(void);`
  - `I_CDMusSetVolume` (function, line 36) `int I_CDMusSetVolume(int volume);`
  - `I_CDMusFirstTrack` (function, line 37) `int I_CDMusFirstTrack(void);`
  - `I_CDMusLastTrack` (function, line 38) `int I_CDMusLastTrack(void);`
  - `I_CDMusTrackLength` (function, line 39) `int I_CDMusTrackLength(int track);`
  - `cd_Error` (variable, line 29) `extern int cd_Error;`
  - `__ICDMUS__` (macro, line 19) `#define __ICDMUS__`
  - `CDERR_NOTINSTALLED` (macro, line 21) `#define CDERR_NOTINSTALLED`
  - `CDERR_NOAUDIOSUPPORT` (macro, line 22) `#define CDERR_NOAUDIOSUPPORT`
  - `CDERR_NOAUDIOTRACKS` (macro, line 23) `#define CDERR_NOAUDIOTRACKS`
  - `CDERR_BADDRIVE` (macro, line 24) `#define CDERR_BADDRIVE`
  - `CDERR_BADTRACK` (macro, line 25) `#define CDERR_BADTRACK`
  - `CDERR_IOCTLBUFFMEM` (macro, line 26) `#define CDERR_IOCTLBUFFMEM`
  - `CDERR_DEVREQBASE` (macro, line 27) `#define CDERR_DEVREQBASE`
- Imported by: `progs/doomgeneric/i_cdmus.c`

## progs/doomgeneric/i_endoom.c
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: c
- Symbols:
  - `I_Endoom` (function, line 36) `void I_Endoom(byte *endoom_data)`
  - `ENDOOM_W` (macro, line 29) `#define ENDOOM_W`
  - `ENDOOM_H` (macro, line 30) `#define ENDOOM_H`
- Depends on: `kernel/string.c`, `progs/doomgeneric/config.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_video.h`

## progs/doomgeneric/i_endoom.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `I_Endoom` (function, line 26) `void I_Endoom(byte *data);`
  - `__I_ENDOOM__` (macro, line 21) `#define __I_ENDOOM__`
- Imported by: `progs/doomgeneric/d_main.c`

## progs/doomgeneric/i_input.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `TranslateKey` (function, line 225) `static unsigned char TranslateKey(unsigned char key)`
  - `GetTypedChar` (function, line 242) `static unsigned char GetTypedChar(unsigned char key)`
  - `UpdateShiftStatus` (function, line 263) `static void UpdateShiftStatus(int pressed, unsigned char key)`
  - `I_GetEvent` (function, line 279) `void I_GetEvent(void)`
  - `I_InitInput` (function, line 338) `void I_InitInput(void)`
- Depends on: `kernel/string.c`, `progs/doomgeneric/config.h`, `progs/doomgeneric/deh_str.h`, `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_joystick.h`, `progs/doomgeneric/i_scale.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/i_timer.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_config.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/tables.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/i_joystick.c
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: c
- Symbols:
  - `I_ShutdownJoystick` (function, line 77) `void I_ShutdownJoystick(void)`
  - `IsValidAxis` (function, line 90) `static boolean IsValidAxis(int axis)`
  - `I_InitJoystick` (function, line 115) `void I_InitJoystick(void)`
  - `IsAxisButton` (function, line 171) `static boolean IsAxisButton(int physbutton)`
  - `ReadButtonState` (function, line 203) `static int ReadButtonState(int vbutton)`
  - `GetButtonsState` (function, line 228) `static int GetButtonsState(void)`
  - `GetAxisState` (function, line 248) `static int GetAxisState(int axis, int invert)`
  - `I_UpdateJoystick` (function, line 321) `void I_UpdateJoystick(void)`
  - `I_BindJoystickVariables` (function, line 339) `void I_BindJoystickVariables(void)`
  - `DEAD_ZONE` (macro, line 38) `#define DEAD_ZONE`
- Depends on: `kernel/string.c`, `progs/doomgeneric/d_event.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_joystick.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_config.h`, `progs/doomgeneric/m_misc.h`, `progs/pokemon/minios_stubs/SDL.h`

## progs/doomgeneric/i_joystick.h
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `I_InitJoystick` (function, line 63) `void I_InitJoystick(void);`
  - `I_ShutdownJoystick` (function, line 64) `void I_ShutdownJoystick(void);`
  - `I_UpdateJoystick` (function, line 65) `void I_UpdateJoystick(void);`
  - `I_BindJoystickVariables` (function, line 67) `void I_BindJoystickVariables(void);`
  - `__I_JOYSTICK__` (macro, line 20) `#define __I_JOYSTICK__`
  - `NUM_VIRTUAL_BUTTONS` (macro, line 25) `#define NUM_VIRTUAL_BUTTONS`
  - `BUTTON_AXIS` (macro, line 33) `#define BUTTON_AXIS`
  - `IS_BUTTON_AXIS` (macro, line 36) `#define IS_BUTTON_AXIS(axis)`
  - `BUTTON_AXIS_NEG` (macro, line 39) `#define BUTTON_AXIS_NEG(axis)`
  - `BUTTON_AXIS_POS` (macro, line 40) `#define BUTTON_AXIS_POS(axis)`
  - `CREATE_BUTTON_AXIS` (macro, line 43) `#define CREATE_BUTTON_AXIS(neg, pos)`
  - `HAT_AXIS` (macro, line 48) `#define HAT_AXIS`
  - `IS_HAT_AXIS` (macro, line 50) `#define IS_HAT_AXIS(axis)`
  - `HAT_AXIS_HAT` (macro, line 53) `#define HAT_AXIS_HAT(axis)`
  - `HAT_AXIS_DIRECTION` (macro, line 55) `#define HAT_AXIS_DIRECTION(axis)`
  - `CREATE_HAT_AXIS` (macro, line 57) `#define CREATE_HAT_AXIS(hat, direction)`
  - `HAT_AXIS_HORIZONTAL` (macro, line 60) `#define HAT_AXIS_HORIZONTAL`
  - `HAT_AXIS_VERTICAL` (macro, line 61) `#define HAT_AXIS_VERTICAL`
- Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_joystick.c`, `progs/doomgeneric/i_system.c`

## progs/doomgeneric/i_main.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `main` (function, line 40) `int main(int argc, char **argv)`
  - `D_DoomMain` (function, line 33) `void D_DoomMain (void);`
  - `M_FindResponseFile` (function, line 35) `void M_FindResponseFile(void);`
  - `dg_Create` (function, line 37) `void dg_Create();`
- Depends on: `progs/doomgeneric/m_argv.h`

## progs/doomgeneric/i_minios_sound.c
- Layer: utility
- Language: c
- Symbols:
  - `pcspk_channel_t` (struct, line 17)
  - `mus_player_t` (struct, line 84)
  - `sys_tone` (function, line 32) `static long sys_tone(unsigned f)`
  - `sys_time` (function, line 35) `static long sys_time(void)`
  - `mus_read_varlen` (function, line 101) `static int mus_read_varlen(mus_player_t *m, unsigned long *out)`
  - `mus_next_block` (function, line 115) `static int mus_next_block(mus_player_t *m, unsigned long *out)`
  - `mus_note_cmp` (function, line 154) `static int mus_note_cmp(const void *a, const void *b)`
  - `mus_build_chord` (function, line 162) `static void mus_build_chord(mus_player_t *m)`
  - `mus_hold_tone` (function, line 185) `static void mus_hold_tone(unsigned freq, unsigned long ms)`
  - `mus_play_chord` (function, line 196) `static void mus_play_chord(mus_player_t *m)`
  - `mus_advance` (function, line 210) `static void mus_advance(mus_player_t *m, unsigned long ms)`
  - `MUS_Init` (function, line 231) `static boolean MUS_Init(void)`
  - `MUS_Shutdown` (function, line 236) `static void MUS_Shutdown(void)`
  - `MUS_SetMusicVolume` (function, line 241) `static void MUS_SetMusicVolume(int volume)`
  - `MUS_Pause` (function, line 243) `static void MUS_Pause(void)`
  - `MUS_Resume` (function, line 244) `static void MUS_Resume(void)`
  - `MUS_RegisterSong` (function, line 246) `static void *MUS_RegisterSong(void *data, int len)`
  - `MUS_UnRegisterSong` (function, line 261) `static void MUS_UnRegisterSong(void *handle)`
  - `MUS_PlaySong` (function, line 267) `static void MUS_PlaySong(void *handle, boolean looping)`
  - `MUS_StopSong` (function, line 280) `static void MUS_StopSong(void)`
  - `MUS_MusicIsPlaying` (function, line 285) `static boolean MUS_MusicIsPlaying(void)`
  - `MUS_Poll` (function, line 289) `static void MUS_Poll(void)`
  - `PCSPK_Init` (function, line 318) `static boolean PCSPK_Init(boolean use_sfx_prefix)`
  - `PCSPK_Shutdown` (function, line 325) `static void PCSPK_Shutdown(void)`
  - `PCSPK_GetSfxLumpNum` (function, line 330) `static int PCSPK_GetSfxLumpNum(sfxinfo_t *sfx)`
  - `free_channel` (function, line 341) `static void free_channel(int i)`
  - `PCSPK_Update` (function, line 350) `static void PCSPK_Update(void)`
  - `PCSPK_UpdateSoundParams` (function, line 382) `static void PCSPK_UpdateSoundParams(int ch, int v, int s)`
  - `PCSPK_StartSound` (function, line 386) `static int PCSPK_StartSound(sfxinfo_t *sfx, int channel, int vol, int sep)`
  - `PCSPK_StopSound` (function, line 436) `static void PCSPK_StopSound(int channel)`
  - `PCSPK_SoundIsPlaying` (function, line 442) `static boolean PCSPK_SoundIsPlaying(int channel)`
  - `PCSPK_CacheSounds` (function, line 448) `static void PCSPK_CacheSounds(sfxinfo_t *s, int n)`
  - `PCSPK_CHANNELS` (macro, line 12) `#define PCSPK_CHANNELS`
  - `PCSPK_TICK_MS` (macro, line 13) `#define PCSPK_TICK_MS`
  - `MUS_TICKS_PER_SEC` (macro, line 58) `#define MUS_TICKS_PER_SEC`
  - `MUS_PERCUSSION_CHAN` (macro, line 59) `#define MUS_PERCUSSION_CHAN`
  - `MUS_ARP_SLOT_MS` (macro, line 60) `#define MUS_ARP_SLOT_MS`
  - `MUS_BASS_HOLD_MS` (macro, line 61) `#define MUS_BASS_HOLD_MS`
  - `MUS_BASS_LINE_MIDI` (macro, line 62) `#define MUS_BASS_LINE_MIDI`
  - `MUS_ARP_MAX` (macro, line 63) `#define MUS_ARP_MAX`
- Depends on: `kernel/string.c`, `progs/doomgeneric/doomfeatures.h`, `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_sound.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`, `progs/minios_abi.h`

## progs/doomgeneric/i_scale.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `I_InitScale` (function, line 61) `void I_InitScale(byte *_src_buffer, byte *_dest_buffer, int _dest_pitch)`
  - `I_Scale1x` (function, line 75) `static boolean I_Scale1x(int x1, int y1, int x2, int y2)`
  - `I_Scale2x` (function, line 105) `static boolean I_Scale2x(int x1, int y1, int x2, int y2)`
  - `I_Scale3x` (function, line 146) `static boolean I_Scale3x(int x1, int y1, int x2, int y2)`
  - `I_Scale4x` (function, line 191) `static boolean I_Scale4x(int x1, int y1, int x2, int y2)`
  - `I_Scale5x` (function, line 240) `static boolean I_Scale5x(int x1, int y1, int x2, int y2)`
  - `FindNearestColor` (function, line 295) `static int FindNearestColor(byte *palette, int r, int g, int b)`
  - `GenerateStretchTable` (function, line 332) `static byte *GenerateStretchTable(byte *palette, int pct)`
  - `I_InitStretchTables` (function, line 361) `static void I_InitStretchTables(byte *palette)`
  - `I_InitSquashTable` (function, line 387) `static void I_InitSquashTable(byte *palette)`
  - `I_ResetScaleTables` (function, line 404) `void I_ResetScaleTables(byte *palette)`
  - `WriteBlendedLine1x` (function, line 434) `static inline void WriteBlendedLine1x(byte *dest, byte *src1, byte *src2, 
                      ...`
  - `I_Stretch1x` (function, line 450) `static boolean I_Stretch1x(int x1, int y1, int x2, int y2)`
  - `WriteLine2x` (function, line 507) `static inline void WriteLine2x(byte *dest, byte *src)`
  - `WriteBlendedLine2x` (function, line 520) `static inline void WriteBlendedLine2x(byte *dest, byte *src1, byte *src2, 
                      ...`
  - `I_Stretch2x` (function, line 539) `static boolean I_Stretch2x(int x1, int y1, int x2, int y2)`
  - `WriteLine3x` (function, line 620) `static inline void WriteLine3x(byte *dest, byte *src)`
  - `WriteBlendedLine3x` (function, line 634) `static inline void WriteBlendedLine3x(byte *dest, byte *src1, byte *src2, 
                      ...`
  - `I_Stretch3x` (function, line 654) `static boolean I_Stretch3x(int x1, int y1, int x2, int y2)`
  - `WriteLine4x` (function, line 759) `static inline void WriteLine4x(byte *dest, byte *src)`
  - `WriteBlendedLine4x` (function, line 774) `static inline void WriteBlendedLine4x(byte *dest, byte *src1, byte *src2, 
                      ...`
  - `I_Stretch4x` (function, line 795) `static boolean I_Stretch4x(int x1, int y1, int x2, int y2)`
  - `WriteLine5x` (function, line 924) `static inline void WriteLine5x(byte *dest, byte *src)`
  - `I_Stretch5x` (function, line 942) `static boolean I_Stretch5x(int x1, int y1, int x2, int y2)`
  - `WriteSquashedLine1x` (function, line 1030) `static inline void WriteSquashedLine1x(byte *dest, byte *src)`
  - `I_Squash1x` (function, line 1061) `static boolean I_Squash1x(int x1, int y1, int x2, int y2)`
  - `WriteSquashedLine2x` (function, line 1102) `static inline void WriteSquashedLine2x(byte *dest, byte *src)`
  - `I_Squash2x` (function, line 1160) `static boolean I_Squash2x(int x1, int y1, int x2, int y2)`
  - `WriteSquashedLine3x` (function, line 1197) `static inline void WriteSquashedLine3x(byte *dest, byte *src)`
  - `I_Squash3x` (function, line 1243) `static boolean I_Squash3x(int x1, int y1, int x2, int y2)`
  - `WriteSquashedLine4x` (function, line 1279) `static inline void WriteSquashedLine4x(byte *dest, byte *src)`
  - `I_Squash4x` (function, line 1354) `static boolean I_Squash4x(int x1, int y1, int x2, int y2)`
  - `WriteSquashedLine5x` (function, line 1390) `static inline void WriteSquashedLine5x(byte *dest, byte *src)`
  - `I_Squash5x` (function, line 1419) `static boolean I_Squash5x(int x1, int y1, int x2, int y2)`
  - `inline` (macro, line 32) `#define inline`
  - `DRAW_PIXEL2` (macro, line 1099) `#define DRAW_PIXEL2`
  - `DRAW_PIXEL3` (macro, line 1194) `#define DRAW_PIXEL3`
  - `DRAW_PIXEL4` (macro, line 1276) `#define DRAW_PIXEL4`
  - `DRAW_PIXEL5` (macro, line 1387) `#define DRAW_PIXEL5`
- Depends on: `kernel/string.c`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/i_scale.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `I_InitScale` (function, line 25) `void I_InitScale(byte *_src_buffer, byte *_dest_buffer, int _dest_pitch);`
  - `I_ResetScaleTables` (function, line 26) `void I_ResetScaleTables(byte *palette);`
  - `mode_scale_1x` (variable, line 30) `extern screen_mode_t mode_scale_1x;`
  - `mode_scale_2x` (variable, line 31) `extern screen_mode_t mode_scale_2x;`
  - `mode_scale_3x` (variable, line 32) `extern screen_mode_t mode_scale_3x;`
  - `mode_scale_4x` (variable, line 33) `extern screen_mode_t mode_scale_4x;`
  - `mode_scale_5x` (variable, line 34) `extern screen_mode_t mode_scale_5x;`
  - `mode_stretch_1x` (variable, line 38) `extern screen_mode_t mode_stretch_1x;`
  - `mode_stretch_2x` (variable, line 39) `extern screen_mode_t mode_stretch_2x;`
  - `mode_stretch_3x` (variable, line 40) `extern screen_mode_t mode_stretch_3x;`
  - `mode_stretch_4x` (variable, line 41) `extern screen_mode_t mode_stretch_4x;`
  - `mode_stretch_5x` (variable, line 42) `extern screen_mode_t mode_stretch_5x;`
  - `mode_squash_1x` (variable, line 46) `extern screen_mode_t mode_squash_1x;`
  - `mode_squash_2x` (variable, line 47) `extern screen_mode_t mode_squash_2x;`
  - `mode_squash_3x` (variable, line 48) `extern screen_mode_t mode_squash_3x;`
  - `mode_squash_4x` (variable, line 49) `extern screen_mode_t mode_squash_4x;`
  - `mode_squash_5x` (variable, line 50) `extern screen_mode_t mode_squash_5x;`
  - `__I_SCALE__` (macro, line 21) `#define __I_SCALE__`
- Depends on: `progs/doomgeneric/doomtype.h`
- Imported by: `progs/doomgeneric/i_input.c`

## progs/doomgeneric/i_sound.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `SndDeviceInList` (function, line 116) `static boolean SndDeviceInList(snddevice_t device, snddevice_t *list,
                           ...`
  - `InitSfxModule` (function, line 135) `static void InitSfxModule(boolean use_sfx_prefix)`
  - `InitMusicModule` (function, line 163) `static void InitMusicModule(void)`
  - `I_InitSound` (function, line 195) `void I_InitSound(boolean use_sfx_prefix)`
  - `I_ShutdownSound` (function, line 250) `void I_ShutdownSound(void)`
  - `I_GetSfxLumpNum` (function, line 263) `int I_GetSfxLumpNum(sfxinfo_t *sfxinfo)`
  - `I_UpdateSound` (function, line 275) `void I_UpdateSound(void)`
  - `CheckVolumeSeparation` (function, line 288) `static void CheckVolumeSeparation(int *vol, int *sep)`
  - `I_UpdateSoundParams` (function, line 309) `void I_UpdateSoundParams(int channel, int vol, int sep)`
  - `I_StartSound` (function, line 318) `int I_StartSound(sfxinfo_t *sfxinfo, int channel, int vol, int sep)`
  - `I_StopSound` (function, line 331) `void I_StopSound(int channel)`
  - `I_SoundIsPlaying` (function, line 339) `boolean I_SoundIsPlaying(int channel)`
  - `I_PrecacheSounds` (function, line 351) `void I_PrecacheSounds(sfxinfo_t *sounds, int num_sounds)`
  - `I_InitMusic` (function, line 359) `void I_InitMusic(void)`
  - `I_ShutdownMusic` (function, line 363) `void I_ShutdownMusic(void)`
  - `I_SetMusicVolume` (function, line 368) `void I_SetMusicVolume(int volume)`
  - `I_PauseSong` (function, line 376) `void I_PauseSong(void)`
  - `I_ResumeSong` (function, line 384) `void I_ResumeSong(void)`
  - `I_RegisterSong` (function, line 392) `void *I_RegisterSong(void *data, int len)`
  - `I_UnRegisterSong` (function, line 404) `void I_UnRegisterSong(void *handle)`
  - `I_PlaySong` (function, line 412) `void I_PlaySong(void *handle, boolean looping)`
  - `I_StopSong` (function, line 420) `void I_StopSong(void)`
  - `I_MusicIsPlaying` (function, line 428) `boolean I_MusicIsPlaying(void)`
  - `I_BindSoundVariables` (function, line 440) `void I_BindSoundVariables(void)`
  - `I_InitTimidityConfig` (function, line 65) `extern void I_InitTimidityConfig(void);`
  - `sound_sdl_module` (variable, line 66) `extern sound_module_t sound_sdl_module;`
  - `sound_pcsound_module` (variable, line 67) `extern sound_module_t sound_pcsound_module;`
  - `music_sdl_module` (variable, line 68) `extern music_module_t music_sdl_module;`
  - `music_opl_module` (variable, line 69) `extern music_module_t music_opl_module;`
  - `music_pcspeaker_module` (variable, line 70) `extern music_module_t music_pcspeaker_module;`
  - `opl_io_port` (variable, line 74) `extern int opl_io_port;`
  - `timidity_cfg_path` (variable, line 78) `extern char *timidity_cfg_path;`
  - `use_libsamplerate` (variable, line 443) `extern int use_libsamplerate;`
  - `libsamplerate_scale` (variable, line 444) `extern float libsamplerate_scale;`
- Depends on: `progs/doomgeneric/config.h`, `progs/doomgeneric/doomfeatures.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/gusconf.h`, `progs/doomgeneric/i_sound.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_config.h`

## progs/doomgeneric/i_sound.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `sfxinfo_struct` (struct, line 31)
  - `musicinfo_t` (struct, line 72)
  - `sound_module_t` (struct, line 105)
  - `music_module_t` (struct, line 164)
  - `sfxinfo_t` (type_alias, line 29) `typedef struct sfxinfo_struct sfxinfo_t;`
  - `I_InitSound` (function, line 152) `void I_InitSound(boolean use_sfx_prefix);`
  - `I_ShutdownSound` (function, line 153) `void I_ShutdownSound(void);`
  - `I_GetSfxLumpNum` (function, line 154) `int I_GetSfxLumpNum(sfxinfo_t *sfxinfo);`
  - `I_UpdateSound` (function, line 155) `void I_UpdateSound(void);`
  - `I_UpdateSoundParams` (function, line 156) `void I_UpdateSoundParams(int channel, int vol, int sep);`
  - `I_StartSound` (function, line 157) `int I_StartSound(sfxinfo_t *sfxinfo, int channel, int vol, int sep);`
  - `I_StopSound` (function, line 158) `void I_StopSound(int channel);`
  - `I_PrecacheSounds` (function, line 160) `void I_PrecacheSounds(sfxinfo_t *sounds, int num_sounds);`
  - `I_InitMusic` (function, line 217) `void I_InitMusic(void);`
  - `I_ShutdownMusic` (function, line 218) `void I_ShutdownMusic(void);`
  - `I_SetMusicVolume` (function, line 219) `void I_SetMusicVolume(int volume);`
  - `I_PauseSong` (function, line 220) `void I_PauseSong(void);`
  - `I_ResumeSong` (function, line 221) `void I_ResumeSong(void);`
  - `I_RegisterSong` (function, line 222) `void *I_RegisterSong(void *data, int len);`
  - `I_UnRegisterSong` (function, line 223) `void I_UnRegisterSong(void *handle);`
  - `I_PlaySong` (function, line 224) `void I_PlaySong(void *handle, boolean looping);`
  - `I_StopSong` (function, line 225) `void I_StopSong(void);`
  - `I_BindSoundVariables` (function, line 235) `void I_BindSoundVariables(void);`
  - `snd_sfxdevice` (variable, line 228) `extern int snd_sfxdevice;`
  - `snd_musicdevice` (variable, line 229) `extern int snd_musicdevice;`
  - `snd_samplerate` (variable, line 230) `extern int snd_samplerate;`
  - `snd_cachesize` (variable, line 231) `extern int snd_cachesize;`
  - `snd_maxslicetime_ms` (variable, line 232) `extern int snd_maxslicetime_ms;`
  - `snd_musiccmd` (variable, line 233) `extern char *snd_musiccmd;`
  - `__I_SOUND__` (macro, line 21) `#define __I_SOUND__`
- Depends on: `progs/doomgeneric/doomtype.h`
- Imported by: `progs/doomgeneric/i_minios_sound.c`, `progs/doomgeneric/i_sound.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/sounds.h`

## progs/doomgeneric/i_swap.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
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
- Layer: utility
- Doc: Emacs style mode select   -*- C++ -*- -----------------------------------------------------------------------------  $Id
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `M_ClearBox` (function, line 38) `void M_ClearBox (fixed_t* box);`
  - `M_AddToBox` (function, line 41) `void M_AddToBox ( fixed_t* box, fixed_t x, fixed_t y );`
  - `__M_BBOX__` (macro, line 21) `#define __M_BBOX__`
- Depends on: `progs/doomgeneric/m_fixed.h`
- Imported by: `progs/doomgeneric/m_bbox.c`, `progs/doomgeneric/p_map.c`, `progs/doomgeneric/p_maputl.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/r_bsp.c`, `progs/doomgeneric/r_main.c`, `progs/doomgeneric/v_video.c`

## progs/doomgeneric/m_cheat.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
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
- Layer: infrastructure
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software Copyright(C) 2005-2014 Simon Howard  This
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
- Layer: infrastructure
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software Copyright(C) 2005-2014 Simon Howard  This
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

## progs/doomgeneric/m_controls.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software Copyright(C) 2005-2014 Simon Howard  This
- Language: h
- Symbols:
  - `M_BindBaseControls` (function, line 156) `void M_BindBaseControls(void);`
  - `M_BindHereticControls` (function, line 157) `void M_BindHereticControls(void);`
  - `M_BindHexenControls` (function, line 158) `void M_BindHexenControls(void);`
  - `M_BindStrifeControls` (function, line 159) `void M_BindStrifeControls(void);`
  - `M_BindWeaponControls` (function, line 160) `void M_BindWeaponControls(void);`
  - `M_BindMapControls` (function, line 161) `void M_BindMapControls(void);`
  - `M_BindMenuControls` (function, line 162) `void M_BindMenuControls(void);`
  - `M_BindChatControls` (function, line 163) `void M_BindChatControls(unsigned int num_players);`
  - `M_ApplyPlatformDefaults` (function, line 165) `void M_ApplyPlatformDefaults(void);`
  - `key_right` (variable, line 20) `extern int key_right;`
  - `key_left` (variable, line 21) `extern int key_left;`
  - `key_up` (variable, line 23) `extern int key_up;`
  - `key_down` (variable, line 24) `extern int key_down;`
  - `key_strafeleft` (variable, line 25) `extern int key_strafeleft;`
  - `key_straferight` (variable, line 26) `extern int key_straferight;`
  - `key_fire` (variable, line 27) `extern int key_fire;`
  - `key_use` (variable, line 28) `extern int key_use;`
  - `key_strafe` (variable, line 29) `extern int key_strafe;`
  - `key_speed` (variable, line 30) `extern int key_speed;`
  - `key_jump` (variable, line 32) `extern int key_jump;`
  - `key_flyup` (variable, line 34) `extern int key_flyup;`
  - `key_flydown` (variable, line 35) `extern int key_flydown;`
  - `key_flycenter` (variable, line 36) `extern int key_flycenter;`
  - `key_lookup` (variable, line 37) `extern int key_lookup;`
  - `key_lookdown` (variable, line 38) `extern int key_lookdown;`
  - `key_lookcenter` (variable, line 39) `extern int key_lookcenter;`
  - `key_invleft` (variable, line 40) `extern int key_invleft;`
  - `key_invright` (variable, line 41) `extern int key_invright;`
  - `key_useartifact` (variable, line 42) `extern int key_useartifact;`
  - `key_usehealth` (variable, line 45) `extern int key_usehealth;`
  - `key_invquery` (variable, line 46) `extern int key_invquery;`
  - `key_mission` (variable, line 47) `extern int key_mission;`
  - `key_invpop` (variable, line 48) `extern int key_invpop;`
  - `key_invkey` (variable, line 49) `extern int key_invkey;`
  - `key_invhome` (variable, line 50) `extern int key_invhome;`
  - `key_invend` (variable, line 51) `extern int key_invend;`
  - `key_invuse` (variable, line 52) `extern int key_invuse;`
  - `key_invdrop` (variable, line 53) `extern int key_invdrop;`
  - `key_message_refresh` (variable, line 55) `extern int key_message_refresh;`
  - `key_pause` (variable, line 56) `extern int key_pause;`
  - `key_multi_msg` (variable, line 58) `extern int key_multi_msg;`
  - `key_multi_msgplayer` (variable, line 59) `extern int key_multi_msgplayer[8];`
  - `key_weapon1` (variable, line 61) `extern int key_weapon1;`
  - `key_weapon2` (variable, line 62) `extern int key_weapon2;`
  - `key_weapon3` (variable, line 63) `extern int key_weapon3;`
  - `key_weapon4` (variable, line 64) `extern int key_weapon4;`
  - `key_weapon5` (variable, line 65) `extern int key_weapon5;`
  - `key_weapon6` (variable, line 66) `extern int key_weapon6;`
  - `key_weapon7` (variable, line 67) `extern int key_weapon7;`
  - `key_weapon8` (variable, line 68) `extern int key_weapon8;`
  - `key_arti_all` (variable, line 70) `extern int key_arti_all;`
  - `key_arti_health` (variable, line 71) `extern int key_arti_health;`
  - `key_arti_poisonbag` (variable, line 72) `extern int key_arti_poisonbag;`
  - `key_arti_blastradius` (variable, line 73) `extern int key_arti_blastradius;`
  - `key_arti_teleport` (variable, line 74) `extern int key_arti_teleport;`
  - `key_arti_teleportother` (variable, line 75) `extern int key_arti_teleportother;`
  - `key_arti_egg` (variable, line 76) `extern int key_arti_egg;`
  - `key_arti_invulnerability` (variable, line 77) `extern int key_arti_invulnerability;`
  - `key_demo_quit` (variable, line 79) `extern int key_demo_quit;`
  - `key_spy` (variable, line 80) `extern int key_spy;`
  - `key_prevweapon` (variable, line 81) `extern int key_prevweapon;`
  - `key_nextweapon` (variable, line 82) `extern int key_nextweapon;`
  - `key_map_north` (variable, line 84) `extern int key_map_north;`
  - `key_map_south` (variable, line 85) `extern int key_map_south;`
  - `key_map_east` (variable, line 86) `extern int key_map_east;`
  - `key_map_west` (variable, line 87) `extern int key_map_west;`
  - `key_map_zoomin` (variable, line 88) `extern int key_map_zoomin;`
  - `key_map_zoomout` (variable, line 89) `extern int key_map_zoomout;`
  - `key_map_toggle` (variable, line 90) `extern int key_map_toggle;`
  - `key_map_maxzoom` (variable, line 91) `extern int key_map_maxzoom;`
  - `key_map_follow` (variable, line 92) `extern int key_map_follow;`
  - `key_map_grid` (variable, line 93) `extern int key_map_grid;`
  - `key_map_mark` (variable, line 94) `extern int key_map_mark;`
  - `key_map_clearmark` (variable, line 95) `extern int key_map_clearmark;`
  - `key_menu_activate` (variable, line 99) `extern int key_menu_activate;`
  - `key_menu_up` (variable, line 100) `extern int key_menu_up;`
  - `key_menu_down` (variable, line 101) `extern int key_menu_down;`
  - `key_menu_left` (variable, line 102) `extern int key_menu_left;`
  - `key_menu_right` (variable, line 103) `extern int key_menu_right;`
  - `key_menu_back` (variable, line 104) `extern int key_menu_back;`
  - `key_menu_forward` (variable, line 105) `extern int key_menu_forward;`
  - `key_menu_confirm` (variable, line 106) `extern int key_menu_confirm;`
  - `key_menu_abort` (variable, line 107) `extern int key_menu_abort;`
  - `key_menu_help` (variable, line 109) `extern int key_menu_help;`
  - `key_menu_save` (variable, line 110) `extern int key_menu_save;`
  - `key_menu_load` (variable, line 111) `extern int key_menu_load;`
  - `key_menu_volume` (variable, line 112) `extern int key_menu_volume;`
  - `key_menu_detail` (variable, line 113) `extern int key_menu_detail;`
  - `key_menu_qsave` (variable, line 114) `extern int key_menu_qsave;`
  - `key_menu_endgame` (variable, line 115) `extern int key_menu_endgame;`
  - `key_menu_messages` (variable, line 116) `extern int key_menu_messages;`
  - `key_menu_qload` (variable, line 117) `extern int key_menu_qload;`
  - `key_menu_quit` (variable, line 118) `extern int key_menu_quit;`
  - `key_menu_gamma` (variable, line 119) `extern int key_menu_gamma;`
  - `key_menu_incscreen` (variable, line 121) `extern int key_menu_incscreen;`
  - `key_menu_decscreen` (variable, line 122) `extern int key_menu_decscreen;`
  - `key_menu_screenshot` (variable, line 123) `extern int key_menu_screenshot;`
  - `mousebfire` (variable, line 125) `extern int mousebfire;`
  - `mousebstrafe` (variable, line 126) `extern int mousebstrafe;`
  - `mousebforward` (variable, line 127) `extern int mousebforward;`
  - `mousebjump` (variable, line 129) `extern int mousebjump;`
  - `mousebstrafeleft` (variable, line 131) `extern int mousebstrafeleft;`
  - `mousebstraferight` (variable, line 132) `extern int mousebstraferight;`
  - `mousebbackward` (variable, line 133) `extern int mousebbackward;`
  - `mousebuse` (variable, line 134) `extern int mousebuse;`
  - `mousebprevweapon` (variable, line 136) `extern int mousebprevweapon;`
  - `mousebnextweapon` (variable, line 137) `extern int mousebnextweapon;`
  - `joybfire` (variable, line 139) `extern int joybfire;`
  - `joybstrafe` (variable, line 140) `extern int joybstrafe;`
  - `joybuse` (variable, line 141) `extern int joybuse;`
  - `joybspeed` (variable, line 142) `extern int joybspeed;`
  - `joybjump` (variable, line 144) `extern int joybjump;`
  - `joybstrafeleft` (variable, line 146) `extern int joybstrafeleft;`
  - `joybstraferight` (variable, line 147) `extern int joybstraferight;`
  - `joybprevweapon` (variable, line 149) `extern int joybprevweapon;`
  - `joybnextweapon` (variable, line 150) `extern int joybnextweapon;`
  - `joybmenu` (variable, line 152) `extern int joybmenu;`
  - `dclick_use` (variable, line 154) `extern int dclick_use;`
  - `__M_CONTROLS_H__` (macro, line 18) `#define __M_CONTROLS_H__`
- Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/m_menu.c`

## progs/doomgeneric/m_fixed.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `FixedMul` (function, line 34) `fixed_t
FixedMul
( fixed_t	a,
  fixed_t	b )`
  - `FixedDiv` (function, line 47) `fixed_t FixedDiv(fixed_t a, fixed_t b)`
- Depends on: `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_fixed.h`

## progs/doomgeneric/m_fixed.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `fixed_t` (type_alias, line 31) `typedef int fixed_t;`
  - `FixedMul` (function, line 34) `fixed_t FixedMul (fixed_t a, fixed_t b);`
  - `FixedDiv` (function, line 35) `fixed_t FixedDiv (fixed_t a, fixed_t b);`
  - `__M_FIXED__` (macro, line 21) `#define __M_FIXED__`
  - `FRACBITS` (macro, line 29) `#define FRACBITS`
  - `FRACUNIT` (macro, line 30) `#define FRACUNIT`
- Imported by: `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/info.c`, `progs/doomgeneric/m_bbox.h`, `progs/doomgeneric/m_fixed.c`, `progs/doomgeneric/p_mobj.h`, `progs/doomgeneric/p_pspr.h`, `progs/doomgeneric/r_defs.h`, `progs/doomgeneric/r_sky.c`, `progs/doomgeneric/tables.h`

## progs/doomgeneric/m_menu.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `menu_s` (struct, line 151)
  - `menuitem_t` (struct, line 133)
  - `numitems` (type_alias, line 148) `typedef struct menu_s { short numitems;`
  - `M_ReadSaveStrings` (function, line 503) `void M_ReadSaveStrings(void)`
  - `M_DrawLoad` (function, line 530) `void M_DrawLoad(void)`
  - `M_DrawSaveLoadBorder` (function, line 549) `void M_DrawSaveLoadBorder(int x,int y)`
  - `M_LoadSelect` (function, line 572) `void M_LoadSelect(int choice)`
  - `M_LoadGame` (function, line 585) `void M_LoadGame (int choice)`
  - `M_DrawSave` (function, line 601) `void M_DrawSave(void)`
  - `M_DoSave` (function, line 622) `void M_DoSave(int slot)`
  - `M_SaveSelect` (function, line 635) `void M_SaveSelect(int choice)`
  - `M_SaveGame` (function, line 650) `void M_SaveGame (int choice)`
  - `M_QuickSaveResponse` (function, line 672) `void M_QuickSaveResponse(int key)`
  - `M_QuickSave` (function, line 681) `void M_QuickSave(void)`
  - `M_QuickLoadResponse` (function, line 709) `void M_QuickLoadResponse(int key)`
  - `M_QuickLoad` (function, line 719) `void M_QuickLoad(void)`
  - `M_DrawReadThis1` (function, line 743) `void M_DrawReadThis1(void)`
  - `M_DrawReadThis2` (function, line 820) `void M_DrawReadThis2(void)`
  - `M_DrawSound` (function, line 834) `void M_DrawSound(void)`
  - `M_Sound` (function, line 845) `void M_Sound(int choice)`
  - `M_SfxVol` (function, line 850) `void M_SfxVol(int choice)`
  - `M_MusicVol` (function, line 867) `void M_MusicVol(int choice)`
  - `M_DrawMainMenu` (function, line 890) `void M_DrawMainMenu(void)`
  - `M_DrawNewGame` (function, line 902) `void M_DrawNewGame(void)`
  - `M_NewGame` (function, line 908) `void M_NewGame(int choice)`
  - `M_DrawEpisode` (function, line 930) `void M_DrawEpisode(void)`
  - `M_VerifyNightmare` (function, line 935) `void M_VerifyNightmare(int key)`
  - `M_ChooseSkill` (function, line 944) `void M_ChooseSkill(int choice)`
  - `M_Episode` (function, line 956) `void M_Episode(int choice)`
  - `M_DrawOptions` (function, line 987) `void M_DrawOptions(void)`
  - `M_Options` (function, line 1007) `void M_Options(int choice)`
  - `M_ChangeMessages` (function, line 1017) `void M_ChangeMessages(int choice)`
  - `M_EndGameResponse` (function, line 1035) `void M_EndGameResponse(int key)`
  - `M_EndGame` (function, line 1045) `void M_EndGame(int choice)`
  - `M_ReadThis` (function, line 1069) `void M_ReadThis(int choice)`
  - `M_ReadThis2` (function, line 1075) `void M_ReadThis2(int choice)`
  - `M_FinishReadThis` (function, line 1093) `void M_FinishReadThis(int choice)`
  - `M_QuitResponse` (function, line 1131) `void M_QuitResponse(int key)`
  - `M_SelectEndMessage` (function, line 1147) `static char *M_SelectEndMessage(void)`
  - `M_QuitDOOM` (function, line 1168) `void M_QuitDOOM(int choice)`
  - `M_ChangeSensitivity` (function, line 1179) `void M_ChangeSensitivity(int choice)`
  - `M_ChangeDetail` (function, line 1197) `void M_ChangeDetail(int choice)`
  - `M_SizeDisplay` (function, line 1213) `void M_SizeDisplay(int choice)`
  - `M_DrawThermo` (function, line 1244) `void
M_DrawThermo
( int	x,
  int	y,
  int	thermWidth,
  int	thermDot )`
  - `M_DrawEmptyCell` (function, line 1270) `void
M_DrawEmptyCell
( menu_t*	menu,
  int		item )`
  - `M_DrawSelCell` (function, line 1279) `void
M_DrawSelCell
( menu_t*	menu,
  int		item )`
  - `M_StartMessage` (function, line 1289) `void
M_StartMessage
( char*		string,
  void*		routine,
  boolean	input )`
  - `M_StopMessage` (function, line 1304) `void M_StopMessage(void)`
  - `M_StringWidth` (function, line 1315) `int M_StringWidth(char* string)`
  - `M_StringHeight` (function, line 1338) `int M_StringHeight(char* string)`
  - `M_WriteText` (function, line 1357) `void
M_WriteText
( int		x,
  int		y,
  char*		string)`
  - `IsNullKey` (function, line 1403) `static boolean IsNullKey(int key)`
  - `M_Responder` (function, line 1416) `boolean M_Responder (event_t* ev)`
  - `M_StartControlPanel` (function, line 1899) `void M_StartControlPanel (void)`
  - `M_DrawOPLDev` (function, line 1913) `static void M_DrawOPLDev(void)`
  - `M_Drawer` (function, line 1951) `void M_Drawer (void)`
  - `M_ClearMenus` (function, line 2041) `void M_ClearMenus (void)`
  - `M_SetupNextMenu` (function, line 2054) `void M_SetupNextMenu(menu_t *menudef)`
  - `M_Ticker` (function, line 2064) `void M_Ticker (void)`
  - `M_Init` (function, line 2077) `void M_Init (void)`
  - `M_StartGame` (function, line 193) `void M_StartGame(int choice);`
  - `I_OPL_DevMessages` (function, line 1915) `extern void I_OPL_DevMessages(char *, size_t);`
  - `hu_font` (variable, line 62) `extern patch_t* hu_font[HU_FONTSIZE];`
  - `message_dontfuckwithme` (variable, line 63) `extern boolean message_dontfuckwithme;`
  - `chat_on` (variable, line 65) `extern boolean chat_on;`
  - `sendpause` (variable, line 123) `extern boolean sendpause;`
  - `SKULLXOFF` (macro, line 120) `#define SKULLXOFF`
  - `LINEHEIGHT` (macro, line 121) `#define LINEHEIGHT`
- Depends on: `progs/doomgeneric/d_main.h`, `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/dstrings.h`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/hu_stuff.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/i_timer.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_controls.h`, `progs/doomgeneric/m_menu.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/p_saveg.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/m_menu.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `M_Ticker` (function, line 40) `void M_Ticker (void);`
  - `M_Drawer` (function, line 44) `void M_Drawer (void);`
  - `M_Init` (function, line 48) `void M_Init (void);`
  - `M_StartControlPanel` (function, line 52) `void M_StartControlPanel (void);`
  - `detailLevel` (variable, line 56) `extern int detailLevel;`
  - `screenblocks` (variable, line 57) `extern int screenblocks;`
  - `__M_MENU__` (macro, line 21) `#define __M_MENU__`
- Depends on: `progs/doomgeneric/d_event.h`
- Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/r_main.c`

## progs/doomgeneric/m_misc.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software Copyright(C) 2005-2014 Simon Howard  This
- Language: c
- Symbols:
  - `M_MakeDirectory` (function, line 55) `void M_MakeDirectory(char *path)`
  - `M_FileExists` (function, line 66) `boolean M_FileExists(char *filename)`
  - `M_FileLength` (function, line 89) `long M_FileLength(FILE *handle)`
  - `M_WriteFile` (function, line 111) `boolean M_WriteFile(char *name, void *source, int length)`
  - `M_ReadFile` (function, line 135) `int M_ReadFile(char *name, byte **buffer)`
  - `M_TempFile` (function, line 166) `char *M_TempFile(char *s)`
  - `M_StrToInt` (function, line 189) `boolean M_StrToInt(const char *str, int *result)`
  - `M_ExtractFileBase` (function, line 197) `void M_ExtractFileBase(char *path, char *dest)`
  - `M_ForceUppercase` (function, line 242) `void M_ForceUppercase(char *text)`
  - `M_StrCaseStr` (function, line 258) `char *M_StrCaseStr(char *haystack, char *needle)`
  - `M_StringDuplicate` (function, line 291) `char *M_StringDuplicate(const char *orig)`
  - `M_StringReplace` (function, line 310) `char *M_StringReplace(const char *haystack, const char *needle,
                      const char ...`
  - `M_StringCopy` (function, line 372) `boolean M_StringCopy(char *dest, const char *src, size_t dest_size)`
  - `M_StringConcat` (function, line 393) `boolean M_StringConcat(char *dest, const char *src, size_t dest_size)`
  - `M_StringStartsWith` (function, line 408) `boolean M_StringStartsWith(const char *s, const char *prefix)`
  - `M_StringEndsWith` (function, line 416) `boolean M_StringEndsWith(const char *s, const char *suffix)`
  - `M_StringJoin` (function, line 425) `char *M_StringJoin(const char *s, ...)`
  - `M_vsnprintf` (function, line 481) `int M_vsnprintf(char *buf, size_t buf_len, const char *s, va_list args)`
  - `M_snprintf` (function, line 507) `int M_snprintf(char *buf, size_t buf_len, const char *s, ...)`
  - `M_OEMToUTF8` (function, line 519) `char *M_OEMToUTF8(const char *oem)`
  - `WIN32_LEAN_AND_MEAN` (macro, line 28) `#define WIN32_LEAN_AND_MEAN`
  - `vsnprintf` (macro, line 476) `#define vsnprintf`
- Depends on: `kernel/string.c`, `progs/doomgeneric/deh_str.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/m_misc.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `M_ReadFile` (function, line 29) `int M_ReadFile(char *name, byte **buffer);`
  - `M_MakeDirectory` (function, line 30) `void M_MakeDirectory(char *dir);`
  - `M_TempFile` (function, line 31) `char *M_TempFile(char *s);`
  - `M_FileLength` (function, line 33) `long M_FileLength(FILE *handle);`
  - `M_ExtractFileBase` (function, line 35) `void M_ExtractFileBase(char *path, char *dest);`
  - `M_ForceUppercase` (function, line 36) `void M_ForceUppercase(char *text);`
  - `M_StrCaseStr` (function, line 37) `char *M_StrCaseStr(char *haystack, char *needle);`
  - `M_StringDuplicate` (function, line 38) `char *M_StringDuplicate(const char *orig);`
  - `M_StringReplace` (function, line 41) `char *M_StringReplace(const char *haystack, const char *needle, const char *replacement);`
  - `M_StringJoin` (function, line 43) `char *M_StringJoin(const char *s, ...);`
  - `M_vsnprintf` (function, line 46) `int M_vsnprintf(char *buf, size_t buf_len, const char *s, va_list args);`
  - `M_snprintf` (function, line 47) `int M_snprintf(char *buf, size_t buf_len, const char *s, ...);`
  - `M_OEMToUTF8` (function, line 48) `char *M_OEMToUTF8(const char *ansi);`
  - `__M_MISC__` (macro, line 21) `#define __M_MISC__`
- Depends on: `progs/doomgeneric/doomtype.h`
- Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_iwad.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_joystick.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/m_argv.c`, `progs/doomgeneric/m_config.c`, `progs/doomgeneric/m_controls.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/m_misc.c`, `progs/doomgeneric/p_map.c`, `progs/doomgeneric/p_saveg.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/r_data.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/v_video.c`, `progs/doomgeneric/w_checksum.c`, `progs/doomgeneric/w_file_stdc.c`, `progs/doomgeneric/w_wad.c`, `progs/doomgeneric/wi_stuff.c`

## progs/doomgeneric/m_random.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `P_Random` (function, line 50) `int P_Random (void)`
  - `M_Random` (function, line 56) `int M_Random (void)`
  - `M_ClearRandom` (function, line 62) `void M_ClearRandom (void)`

## progs/doomgeneric/m_random.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `M_Random` (function, line 30) `int M_Random (void);`
  - `P_Random` (function, line 33) `int P_Random (void);`
  - `M_ClearRandom` (function, line 36) `void M_ClearRandom (void);`
  - `__M_RANDOM__` (macro, line 21) `#define __M_RANDOM__`
- Depends on: `progs/doomgeneric/doomtype.h`
- Imported by: `progs/doomgeneric/f_wipe.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/p_enemy.c`, `progs/doomgeneric/p_inter.c`, `progs/doomgeneric/p_lights.c`, `progs/doomgeneric/p_map.c`, `progs/doomgeneric/p_mobj.c`, `progs/doomgeneric/p_plats.c`, `progs/doomgeneric/p_pspr.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/wi_stuff.c`

## progs/doomgeneric/memio.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `_MEMFILE` (struct, line 32)
  - `mem_fopen_read` (function, line 42) `MEMFILE *mem_fopen_read(void *buf, size_t buflen)`
  - `mem_fread` (function, line 58) `size_t mem_fread(void *buf, size_t size, size_t nmemb, MEMFILE *stream)`
  - `mem_fopen_write` (function, line 90) `MEMFILE *mem_fopen_write(void)`
  - `mem_fwrite` (function, line 107) `size_t mem_fwrite(const void *ptr, size_t size, size_t nmemb, MEMFILE *stream)`
  - `mem_get_buf` (function, line 143) `void mem_get_buf(MEMFILE *stream, void **buf, size_t *buflen)`
  - `mem_fclose` (function, line 149) `void mem_fclose(MEMFILE *stream)`
  - `mem_ftell` (function, line 159) `long mem_ftell(MEMFILE *stream)`
  - `mem_fseek` (function, line 164) `int mem_fseek(MEMFILE *stream, signed long position, mem_rel_t whence)`
- Depends on: `kernel/string.c`, `progs/doomgeneric/memio.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/memio.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `MEMFILE` (type_alias, line 18) `typedef struct _MEMFILE MEMFILE;`
  - `mem_fopen_read` (function, line 28) `MEMFILE *mem_fopen_read(void *buf, size_t buflen);`
  - `mem_fread` (function, line 29) `size_t mem_fread(void *buf, size_t size, size_t nmemb, MEMFILE *stream);`
  - `mem_fopen_write` (function, line 30) `MEMFILE *mem_fopen_write(void);`
  - `mem_fwrite` (function, line 31) `size_t mem_fwrite(const void *ptr, size_t size, size_t nmemb, MEMFILE *stream);`
  - `mem_get_buf` (function, line 32) `void mem_get_buf(MEMFILE *stream, void **buf, size_t *buflen);`
  - `mem_fclose` (function, line 33) `void mem_fclose(MEMFILE *stream);`
  - `mem_ftell` (function, line 34) `long mem_ftell(MEMFILE *stream);`
  - `mem_fseek` (function, line 35) `int mem_fseek(MEMFILE *stream, signed long offset, mem_rel_t whence);`
  - `MEMIO_H` (macro, line 17) `#define MEMIO_H`
- Imported by: `progs/doomgeneric/memio.c`

## progs/doomgeneric/net_client.h
- Layer: infrastructure
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `NET_CL_Disconnect` (function, line 26) `void NET_CL_Disconnect(void);`
  - `NET_CL_Run` (function, line 27) `void NET_CL_Run(void);`
  - `NET_CL_Init` (function, line 28) `void NET_CL_Init(void);`
  - `NET_CL_LaunchGame` (function, line 29) `void NET_CL_LaunchGame(void);`
  - `NET_CL_StartGame` (function, line 30) `void NET_CL_StartGame(net_gamesettings_t *settings);`
  - `NET_CL_SendTiccmd` (function, line 31) `void NET_CL_SendTiccmd(ticcmd_t *ticcmd, int maketic);`
  - `NET_Init` (function, line 33) `void NET_Init(void);`
  - `NET_BindVariables` (function, line 35) `void NET_BindVariables(void);`
  - `net_client_connected` (variable, line 37) `extern boolean net_client_connected;`
  - `net_client_received_wait_data` (variable, line 38) `extern boolean net_client_received_wait_data;`
  - `net_client_wait_data` (variable, line 39) `extern net_waitdata_t net_client_wait_data;`
  - `net_waiting_for_launch` (variable, line 40) `extern boolean net_waiting_for_launch;`
  - `net_player_name` (variable, line 41) `extern char *net_player_name;`
  - `net_server_wad_sha1sum` (variable, line 43) `extern sha1_digest_t net_server_wad_sha1sum;`
  - `net_server_deh_sha1sum` (variable, line 44) `extern sha1_digest_t net_server_deh_sha1sum;`
  - `net_server_is_freedoom` (variable, line 45) `extern unsigned int net_server_is_freedoom;`
  - `net_local_wad_sha1sum` (variable, line 46) `extern sha1_digest_t net_local_wad_sha1sum;`
  - `net_local_deh_sha1sum` (variable, line 47) `extern sha1_digest_t net_local_deh_sha1sum;`
  - `net_local_is_freedoom` (variable, line 48) `extern unsigned int net_local_is_freedoom;`
  - `drone` (variable, line 50) `extern boolean drone;`
  - `NET_CLIENT_H` (macro, line 18) `#define NET_CLIENT_H`
- Depends on: `progs/doomgeneric/d_ticcmd.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/net_defs.h`, `progs/doomgeneric/sha1.h`
- Imported by: `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/d_main.c`

## progs/doomgeneric/net_dedicated.h
- Layer: infrastructure
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `NET_DedicatedServer` (function, line 21) `void NET_DedicatedServer(void);`
  - `NET_DEDICATED_H` (macro, line 19) `#define NET_DEDICATED_H`
- Imported by: `progs/doomgeneric/d_main.c`

## progs/doomgeneric/net_defs.h
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `_net_packet_s` (struct, line 52)
  - `_net_module_s` (struct, line 60)
  - `_net_addr_s` (struct, line 95)
  - `net_connect_data_t` (struct, line 147)
  - `net_gamesettings_t` (struct, line 163)
  - `net_ticdiff_t` (struct, line 202)
  - `net_full_ticcmd_t` (struct, line 210)
  - `net_querydata_t` (struct, line 220)
  - `net_waitdata_t` (struct, line 233)
  - `net_module_t` (type_alias, line 46) `typedef struct _net_module_s net_module_t;`
  - `net_packet_t` (type_alias, line 48) `typedef struct _net_packet_s net_packet_t;`
  - `net_addr_t` (type_alias, line 49) `typedef struct _net_addr_s net_addr_t;`
  - `net_context_t` (type_alias, line 50) `typedef struct _net_context_s net_context_t;`
  - `NET_DEFS_H` (macro, line 19) `#define NET_DEFS_H`
  - `MAXNETNODES` (macro, line 31) `#define MAXNETNODES`
  - `NET_MAXPLAYERS` (macro, line 37) `#define NET_MAXPLAYERS`
  - `MAXPLAYERNAME` (macro, line 41) `#define MAXPLAYERNAME`
  - `BACKUPTICS` (macro, line 45) `#define BACKUPTICS`
  - `NET_MAGIC_NUMBER` (macro, line 103) `#define NET_MAGIC_NUMBER`
  - `NET_RELIABLE_PACKET` (macro, line 107) `#define NET_RELIABLE_PACKET`
  - `NET_TICDIFF_FORWARD` (macro, line 193) `#define NET_TICDIFF_FORWARD`
  - `NET_TICDIFF_SIDE` (macro, line 194) `#define NET_TICDIFF_SIDE`
  - `NET_TICDIFF_TURN` (macro, line 195) `#define NET_TICDIFF_TURN`
  - `NET_TICDIFF_BUTTONS` (macro, line 196) `#define NET_TICDIFF_BUTTONS`
  - `NET_TICDIFF_CONSISTANCY` (macro, line 197) `#define NET_TICDIFF_CONSISTANCY`
  - `NET_TICDIFF_CHATCHAR` (macro, line 198) `#define NET_TICDIFF_CHATCHAR`
  - `NET_TICDIFF_RAVEN` (macro, line 199) `#define NET_TICDIFF_RAVEN`
  - `NET_TICDIFF_STRIFE` (macro, line 200) `#define NET_TICDIFF_STRIFE`
- Depends on: `progs/doomgeneric/d_ticcmd.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/sha1.h`
- Imported by: `progs/doomgeneric/d_loop.h`, `progs/doomgeneric/d_player.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/net_client.h`, `progs/doomgeneric/net_io.h`, `progs/doomgeneric/net_loop.h`, `progs/doomgeneric/net_packet.h`, `progs/doomgeneric/net_query.h`, `progs/doomgeneric/net_sdl.h`

## progs/doomgeneric/net_gui.h
- Layer: presentation
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `NET_WaitForLaunch` (function, line 26) `extern void NET_WaitForLaunch(void);`
  - `NET_GUI_H` (macro, line 22) `#define NET_GUI_H`
- Depends on: `progs/doomgeneric/doomtype.h`
- Imported by: `progs/doomgeneric/d_loop.c`

## progs/doomgeneric/net_io.h
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `NET_NewContext` (function, line 25) `net_context_t *NET_NewContext(void);`
  - `NET_AddModule` (function, line 26) `void NET_AddModule(net_context_t *context, net_module_t *module);`
  - `NET_SendPacket` (function, line 27) `void NET_SendPacket(net_addr_t *addr, net_packet_t *packet);`
  - `NET_SendBroadcast` (function, line 28) `void NET_SendBroadcast(net_context_t *context, net_packet_t *packet);`
  - `NET_AddrToString` (function, line 31) `char *NET_AddrToString(net_addr_t *addr);`
  - `NET_FreeAddress` (function, line 32) `void NET_FreeAddress(net_addr_t *addr);`
  - `NET_ResolveAddress` (function, line 33) `net_addr_t *NET_ResolveAddress(net_context_t *context, char *address);`
  - `net_broadcast_addr` (variable, line 23) `extern net_addr_t net_broadcast_addr;`
  - `NET_IO_H` (macro, line 19) `#define NET_IO_H`
- Depends on: `progs/doomgeneric/net_defs.h`
- Imported by: `progs/doomgeneric/d_loop.c`

## progs/doomgeneric/net_loop.h
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `net_loop_client_module` (variable, line 23) `extern net_module_t net_loop_client_module;`
  - `net_loop_server_module` (variable, line 24) `extern net_module_t net_loop_server_module;`
  - `NET_LOOP_H` (macro, line 19) `#define NET_LOOP_H`
- Depends on: `progs/doomgeneric/net_defs.h`
- Imported by: `progs/doomgeneric/d_loop.c`

## progs/doomgeneric/net_packet.h
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `NET_NewPacket` (function, line 23) `net_packet_t *NET_NewPacket(int initial_size);`
  - `NET_PacketDup` (function, line 24) `net_packet_t *NET_PacketDup(net_packet_t *packet);`
  - `NET_FreePacket` (function, line 25) `void NET_FreePacket(net_packet_t *packet);`
  - `NET_ReadString` (function, line 35) `char *NET_ReadString(net_packet_t *packet);`
  - `NET_WriteInt8` (function, line 37) `void NET_WriteInt8(net_packet_t *packet, unsigned int i);`
  - `NET_WriteInt16` (function, line 38) `void NET_WriteInt16(net_packet_t *packet, unsigned int i);`
  - `NET_WriteInt32` (function, line 39) `void NET_WriteInt32(net_packet_t *packet, unsigned int i);`
  - `NET_WriteString` (function, line 41) `void NET_WriteString(net_packet_t *packet, char *string);`
  - `NET_PACKET_H` (macro, line 19) `#define NET_PACKET_H`
- Depends on: `progs/doomgeneric/net_defs.h`

## progs/doomgeneric/net_query.h
- Layer: data_access
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `NET_StartLANQuery` (function, line 28) `extern int NET_StartLANQuery(void);`
  - `NET_StartMasterQuery` (function, line 29) `extern int NET_StartMasterQuery(void);`
  - `NET_LANQuery` (function, line 31) `extern void NET_LANQuery(void);`
  - `NET_MasterQuery` (function, line 32) `extern void NET_MasterQuery(void);`
  - `NET_QueryAddress` (function, line 33) `extern void NET_QueryAddress(char *addr);`
  - `NET_FindLANServer` (function, line 34) `extern net_addr_t *NET_FindLANServer(void);`
  - `NET_Query_Poll` (function, line 36) `extern int NET_Query_Poll(net_query_callback_t callback, void *user_data);`
  - `NET_Query_ResolveMaster` (function, line 38) `extern net_addr_t *NET_Query_ResolveMaster(net_context_t *context);`
  - `NET_Query_AddToMaster` (function, line 39) `extern void NET_Query_AddToMaster(net_addr_t *master_addr);`
  - `NET_Query_CheckAddedToMaster` (function, line 40) `extern boolean NET_Query_CheckAddedToMaster(boolean *result);`
  - `NET_Query_MasterResponse` (function, line 41) `extern void NET_Query_MasterResponse(net_packet_t *packet);`
  - `NET_QUERY_H` (macro, line 19) `#define NET_QUERY_H`
- Depends on: `progs/doomgeneric/net_defs.h`
- Imported by: `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/d_main.c`

## progs/doomgeneric/net_sdl.h
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `net_sdl_module` (variable, line 23) `extern net_module_t net_sdl_module;`
  - `NET_SDL_H` (macro, line 19) `#define NET_SDL_H`
- Depends on: `progs/doomgeneric/net_defs.h`
- Imported by: `progs/doomgeneric/d_loop.c`

## progs/doomgeneric/net_server.h
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `NET_SV_Init` (function, line 22) `void NET_SV_Init(void);`
  - `NET_SV_Run` (function, line 26) `void NET_SV_Run(void);`
  - `NET_SV_Shutdown` (function, line 31) `void NET_SV_Shutdown(void);`
  - `NET_SV_AddModule` (function, line 35) `void NET_SV_AddModule(net_module_t *module);`
  - `NET_SV_RegisterWithMaster` (function, line 39) `void NET_SV_RegisterWithMaster(void);`
  - `NET_SERVER_H` (macro, line 18) `#define NET_SERVER_H`
- Imported by: `progs/doomgeneric/d_loop.c`

## progs/doomgeneric/p_ceilng.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `T_MoveCeiling` (function, line 45) `void T_MoveCeiling (ceiling_t* ceiling)`
  - `EV_DoCeiling` (function, line 161) `int
EV_DoCeiling
( line_t*	line,
  ceiling_e	type )`
  - `P_AddActiveCeiling` (function, line 240) `void P_AddActiveCeiling(ceiling_t* c)`
  - `P_RemoveActiveCeiling` (function, line 259) `void P_RemoveActiveCeiling(ceiling_t* c)`
  - `P_ActivateInStasisCeiling` (function, line 280) `void P_ActivateInStasisCeiling(line_t* line)`
  - `EV_CeilingCrushStop` (function, line 303) `int	EV_CeilingCrushStop(line_t	*line)`
- Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/p_doors.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `T_VerticalDoor` (function, line 57) `void T_VerticalDoor (vldoor_t* door)`
  - `EV_DoLockedDoor` (function, line 195) `int
EV_DoLockedDoor
( line_t*	line,
  vldoor_e	type,
  mobj_t*	thing )`
  - `EV_DoDoor` (function, line 252) `int
EV_DoDoor
( line_t*	line,
  vldoor_e	type )`
  - `EV_VerticalDoor` (function, line 337) `void
EV_VerticalDoor
( line_t*	line,
  mobj_t*	thing )`
  - `P_SpawnDoorCloseIn30` (function, line 519) `void P_SpawnDoorCloseIn30 (sector_t* sec)`
  - `P_SpawnDoorRaiseIn5Mins` (function, line 542) `void
P_SpawnDoorRaiseIn5Mins
( sector_t*	sec,
  int		secnum )`
  - `P_InitSlidingDoorFrames` (function, line 580) `void P_InitSlidingDoorFrames(void)`
  - `P_FindSlidingDoorType` (function, line 624) `int P_FindSlidingDoorType(line_t*	line)`
  - `T_SlidingDoor` (function, line 639) `void T_SlidingDoor (slidedoor_t*	door)`
  - `EV_SlidingDoor` (function, line 727) `void
EV_SlidingDoor
( line_t*	line,
  mobj_t*	thing )`
- Depends on: `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/dstrings.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/p_enemy.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `P_RecursiveSound` (function, line 99) `void
P_RecursiveSound
( sector_t*	sec,
  int		soundblocks )`
  - `P_NoiseAlert` (function, line 152) `void
P_NoiseAlert
( mobj_t*	target,
  mobj_t*	emmiter )`
  - `P_CheckMeleeRange` (function, line 167) `boolean P_CheckMeleeRange (mobj_t*	actor)`
  - `P_CheckMissileRange` (function, line 190) `boolean P_CheckMissileRange (mobj_t* actor)`
  - `P_Move` (function, line 260) `boolean P_Move (mobj_t*	actor)`
  - `P_TryWalk` (function, line 337) `boolean P_TryWalk (mobj_t* actor)`
  - `P_NewChaseDir` (function, line 351) `void P_NewChaseDir (mobj_t*	actor)`
  - `P_LookForPlayers` (function, line 487) `boolean
P_LookForPlayers
( mobj_t*	actor,
  boolean	allaround )`
  - `A_KeenDie` (function, line 551) `void A_KeenDie (mobj_t* mo)`
  - `A_Look` (function, line 589) `void A_Look (mobj_t* actor)`
  - `A_Chase` (function, line 657) `void A_Chase (mobj_t*	actor)`
  - `A_FaceTarget` (function, line 767) `void A_FaceTarget (mobj_t* actor)`
  - `A_PosAttack` (function, line 787) `void A_PosAttack (mobj_t* actor)`
  - `A_SPosAttack` (function, line 806) `void A_SPosAttack (mobj_t* actor)`
  - `A_CPosAttack` (function, line 830) `void A_CPosAttack (mobj_t* actor)`
  - `A_CPosRefire` (function, line 850) `void A_CPosRefire (mobj_t* actor)`
  - `A_SpidRefire` (function, line 867) `void A_SpidRefire (mobj_t* actor)`
  - `A_BspiAttack` (function, line 883) `void A_BspiAttack (mobj_t *actor)`
  - `A_TroopAttack` (function, line 898) `void A_TroopAttack (mobj_t* actor)`
  - `A_SargAttack` (function, line 920) `void A_SargAttack (mobj_t* actor)`
  - `A_HeadAttack` (function, line 935) `void A_HeadAttack (mobj_t* actor)`
  - `A_CyberAttack` (function, line 954) `void A_CyberAttack (mobj_t* actor)`
  - `A_BruisAttack` (function, line 964) `void A_BruisAttack (mobj_t* actor)`
  - `A_SkelMissile` (function, line 987) `void A_SkelMissile (mobj_t* actor)`
  - `A_Tracer` (function, line 1006) `void A_Tracer (mobj_t* actor)`
  - `A_SkelWhoosh` (function, line 1078) `void A_SkelWhoosh (mobj_t*	actor)`
  - `A_SkelFist` (function, line 1086) `void A_SkelFist (mobj_t*	actor)`
  - `PIT_VileCheck` (function, line 1114) `boolean PIT_VileCheck (mobj_t*	thing)`
  - `A_VileChase` (function, line 1152) `void A_VileChase (mobj_t* actor)`
  - `A_VileStart` (function, line 1218) `void A_VileStart (mobj_t* actor)`
  - `A_StartFire` (function, line 1230) `void A_StartFire (mobj_t* actor)`
  - `A_FireCrackle` (function, line 1236) `void A_FireCrackle (mobj_t* actor)`
  - `A_Fire` (function, line 1242) `void A_Fire (mobj_t* actor)`
  - `A_VileTarget` (function, line 1273) `void A_VileTarget (mobj_t*	actor)`
  - `A_VileAttack` (function, line 1298) `void A_VileAttack (mobj_t* actor)`
  - `A_FatRaise` (function, line 1339) `void A_FatRaise (mobj_t *actor)`
  - `A_FatAttack1` (function, line 1346) `void A_FatAttack1 (mobj_t* actor)`
  - `A_FatAttack2` (function, line 1366) `void A_FatAttack2 (mobj_t* actor)`
  - `A_FatAttack3` (function, line 1385) `void A_FatAttack3 (mobj_t*	actor)`
  - `A_SkullAttack` (function, line 1415) `void A_SkullAttack (mobj_t* actor)`
  - `A_PainShootSkull` (function, line 1446) `void
A_PainShootSkull
( mobj_t*	actor,
  angle_t	angle )`
  - `A_PainAttack` (function, line 1508) `void A_PainAttack (mobj_t* actor)`
  - `A_PainDie` (function, line 1518) `void A_PainDie (mobj_t* actor)`
  - `A_Scream` (function, line 1531) `void A_Scream (mobj_t* actor)`
  - `A_XScream` (function, line 1568) `void A_XScream (mobj_t* actor)`
  - `A_Pain` (function, line 1573) `void A_Pain (mobj_t* actor)`
  - `A_Fall` (function, line 1581) `void A_Fall (mobj_t *actor)`
  - `A_Explode` (function, line 1594) `void A_Explode (mobj_t* thingy)`
  - `CheckBossEnd` (function, line 1605) `static boolean CheckBossEnd(mobjtype_t motype)`
  - `A_BossDeath` (function, line 1656) `void A_BossDeath (mobj_t* mo)`
  - `A_Hoof` (function, line 1757) `void A_Hoof (mobj_t* mo)`
  - `A_Metal` (function, line 1763) `void A_Metal (mobj_t* mo)`
  - `A_BabyMetal` (function, line 1769) `void A_BabyMetal (mobj_t* mo)`
  - `A_OpenShotgun2` (function, line 1776) `void
A_OpenShotgun2
( player_t*	player,
  pspdef_t*	psp )`
  - `A_LoadShotgun2` (function, line 1784) `void
A_LoadShotgun2
( player_t*	player,
  pspdef_t*	psp )`
  - `A_CloseShotgun2` (function, line 1797) `void
A_CloseShotgun2
( player_t*	player,
  pspdef_t*	psp )`
  - `A_BrainAwake` (function, line 1811) `void A_BrainAwake (mobj_t* mo)`
  - `A_BrainPain` (function, line 1841) `void A_BrainPain (mobj_t*	mo)`
  - `A_BrainScream` (function, line 1847) `void A_BrainScream (mobj_t*	mo)`
  - `A_BrainExplode` (function, line 1873) `void A_BrainExplode (mobj_t* mo)`
  - `A_BrainDie` (function, line 1894) `void A_BrainDie (mobj_t*	mo)`
  - `A_BrainSpit` (function, line 1899) `void A_BrainSpit (mobj_t*	mo)`
  - `A_SpawnSound` (function, line 1928) `void A_SpawnSound (mobj_t* mo)`
  - `A_SpawnFly` (function, line 1934) `void A_SpawnFly (mobj_t* mo)`
  - `A_PlayerScream` (function, line 1992) `void A_PlayerScream (mobj_t* mo)`
  - `A_ReFire` (function, line 1792) `void A_ReFire ( player_t* player, pspdef_t* psp );`
  - `FATSPREAD` (macro, line 1337) `#define	FATSPREAD`
  - `SKULLSPEED` (macro, line 1413) `#define	SKULLSPEED`
- Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`

## progs/doomgeneric/p_floor.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `T_MovePlane` (function, line 42) `result_e
T_MovePlane
( sector_t*	sector,
  fixed_t	speed,
  fixed_t	dest,
  boolean	crush,
  int	...`
  - `T_MoveFloor` (function, line 202) `void T_MoveFloor(floormove_t* floor)`
  - `EV_DoFloor` (function, line 251) `int
EV_DoFloor
( line_t*	line,
  floor_e	floortype )`
  - `EV_BuildStairs` (function, line 444) `int
EV_BuildStairs
( line_t*	line,
  stair_e	type )`
- Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/p_inter.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `P_GiveAmmo` (function, line 66) `boolean
P_GiveAmmo
( player_t*	player,
  ammotype_t	ammo,
  int		num )`
  - `P_GiveWeapon` (function, line 160) `boolean
P_GiveWeapon
( player_t*	player,
  weapontype_t	weapon,
  boolean	dropped )`
  - `P_GiveBody` (function, line 223) `boolean
P_GiveBody
( player_t*	player,
  int		num )`
  - `P_GiveArmor` (function, line 246) `boolean
P_GiveArmor
( player_t*	player,
  int		armortype )`
  - `P_GiveCard` (function, line 268) `void
P_GiveCard
( player_t*	player,
  card_t	card )`
  - `P_GivePower` (function, line 284) `boolean
P_GivePower
( player_t*	player,
  int /*powertype_t*/	power )`
  - `P_TouchSpecialThing` (function, line 333) `void
P_TouchSpecialThing
( mobj_t*	special,
  mobj_t*	toucher )`
  - `P_KillMobj` (function, line 666) `void
P_KillMobj
( mobj_t*	source,
  mobj_t*	target )`
  - `P_DamageMobj` (function, line 779) `void
P_DamageMobj
( mobj_t*	target,
  mobj_t*	inflictor,
  mobj_t*	source,
  int 		damage )`
  - `BONUSADD` (macro, line 43) `#define BONUSADD`
- Depends on: `progs/doomgeneric/am_map.h`, `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/deh_misc.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/dstrings.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/p_inter.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`

## progs/doomgeneric/p_inter.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__P_INTER__` (macro, line 21) `#define __P_INTER__`
- Imported by: `progs/doomgeneric/p_inter.c`, `progs/doomgeneric/st_stuff.c`

## progs/doomgeneric/p_lights.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `T_FireFlicker` (function, line 39) `void T_FireFlicker (fireflicker_t* flick)`
  - `P_SpawnFireFlicker` (function, line 61) `void P_SpawnFireFlicker (sector_t*	sector)`
  - `T_LightFlash` (function, line 91) `void T_LightFlash (lightflash_t* flash)`
  - `P_SpawnLightFlash` (function, line 117) `void P_SpawnLightFlash (sector_t*	sector)`
  - `T_StrobeFlash` (function, line 148) `void T_StrobeFlash (strobe_t*		flash)`
  - `P_SpawnStrobeFlash` (function, line 174) `void
P_SpawnStrobeFlash
( sector_t*	sector,
  int		fastOrSlow,
  int		inSync )`
  - `EV_StartLightStrobing` (function, line 208) `void EV_StartLightStrobing(line_t*	line)`
  - `EV_TurnTagLightsOff` (function, line 229) `void EV_TurnTagLightsOff(line_t* line)`
  - `EV_LightTurnOn` (function, line 264) `void
EV_LightTurnOn
( line_t*	line,
  int		bright )`
  - `T_Glow` (function, line 307) `void T_Glow(glow_t*	g)`
  - `P_SpawnGlowingLight` (function, line 334) `void P_SpawnGlowingLight(sector_t*	sector)`
- Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/p_local.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `divline_t` (struct, line 133)
  - `d` (struct, line 142)
  - `P_InitThinkers` (function, line 70) `void P_InitThinkers (void);`
  - `P_AddThinker` (function, line 71) `void P_AddThinker (thinker_t* thinker);`
  - `P_RemoveThinker` (function, line 72) `void P_RemoveThinker (thinker_t* thinker);`
  - `P_SetupPsprites` (function, line 78) `void P_SetupPsprites (player_t* curplayer);`
  - `P_MovePsprites` (function, line 79) `void P_MovePsprites (player_t* curplayer);`
  - `P_DropWeapon` (function, line 80) `void P_DropWeapon (player_t* player);`
  - `P_PlayerThink` (function, line 86) `void P_PlayerThink (player_t* player);`
  - `P_RespawnSpecials` (function, line 104) `void P_RespawnSpecials (void);`
  - `P_SpawnMobj` (function, line 107) `mobj_t* P_SpawnMobj ( fixed_t x, fixed_t y, fixed_t z, mobjtype_t type );`
  - `P_RemoveMobj` (function, line 113) `void P_RemoveMobj (mobj_t* th);`
  - `P_SubstNullMobj` (function, line 114) `mobj_t* P_SubstNullMobj (mobj_t* th);`
  - `P_MobjThinker` (function, line 116) `void P_MobjThinker (mobj_t* mobj);`
  - `P_SpawnPuff` (function, line 118) `void P_SpawnPuff (fixed_t x, fixed_t y, fixed_t z);`
  - `P_SpawnBlood` (function, line 119) `void P_SpawnBlood (fixed_t x, fixed_t y, fixed_t z, int damage);`
  - `P_SpawnMissile` (function, line 120) `mobj_t* P_SpawnMissile (mobj_t* source, mobj_t* dest, mobjtype_t type);`
  - `P_SpawnPlayerMissile` (function, line 121) `void P_SpawnPlayerMissile (mobj_t* source, mobjtype_t type);`
  - `P_NoiseAlert` (function, line 127) `void P_NoiseAlert (mobj_t* target, mobj_t* emmiter);`
  - `P_AproxDistance` (function, line 162) `fixed_t P_AproxDistance (fixed_t dx, fixed_t dy);`
  - `P_PointOnLineSide` (function, line 163) `int P_PointOnLineSide (fixed_t x, fixed_t y, line_t* line);`
  - `P_PointOnDivlineSide` (function, line 164) `int P_PointOnDivlineSide (fixed_t x, fixed_t y, divline_t* line);`
  - `P_MakeDivline` (function, line 165) `void P_MakeDivline (line_t* li, divline_t* dl);`
  - `P_InterceptVector` (function, line 166) `fixed_t P_InterceptVector (divline_t* v2, divline_t* v1);`
  - `P_BoxOnLineSide` (function, line 167) `int P_BoxOnLineSide (fixed_t* tmbox, line_t* ld);`
  - `P_LineOpening` (function, line 174) `void P_LineOpening (line_t* linedef);`
  - `P_UnsetThingPosition` (function, line 194) `void P_UnsetThingPosition (mobj_t* thing);`
  - `P_SetThingPosition` (function, line 195) `void P_SetThingPosition (mobj_t* thing);`
  - `P_SlideMove` (function, line 228) `void P_SlideMove (mobj_t* mo);`
  - `P_UseLines` (function, line 230) `void P_UseLines (player_t* player);`
  - `P_AimLineAttack` (function, line 237) `fixed_t P_AimLineAttack ( mobj_t* t1, angle_t angle, fixed_t distance );`
  - `P_LineAttack` (function, line 243) `void P_LineAttack ( mobj_t* t1, angle_t angle, fixed_t distance, fixed_t slope, int damage );`
  - `P_RadiusAttack` (function, line 251) `void P_RadiusAttack ( mobj_t* spot, mobj_t* source, int damage );`
  - `P_TouchSpecialThing` (function, line 279) `void P_TouchSpecialThing ( mobj_t* special, mobj_t* toucher );`
  - `P_DamageMobj` (function, line 284) `void P_DamageMobj ( mobj_t* target, mobj_t* inflictor, mobj_t* source, int damage );`
  - `thinkercap` (variable, line 67) `extern thinker_t thinkercap;`
  - `itemrespawnque` (variable, line 98) `extern mapthing_t itemrespawnque[ITEMQUESIZE];`
  - `itemrespawntime` (variable, line 99) `extern int itemrespawntime[ITEMQUESIZE];`
  - `iquehead` (variable, line 100) `extern int iquehead;`
  - `iquetail` (variable, line 101) `extern int iquetail;`
  - `intercepts` (variable, line 157) `extern intercept_t intercepts[MAXINTERCEPTS];`
  - `intercept_p` (variable, line 158) `extern intercept_t* intercept_p;`
  - `opentop` (variable, line 169) `extern fixed_t opentop;`
  - `openbottom` (variable, line 170) `extern fixed_t openbottom;`
  - `openrange` (variable, line 171) `extern fixed_t openrange;`
  - `lowfloor` (variable, line 172) `extern fixed_t lowfloor;`
  - `trace` (variable, line 183) `extern divline_t trace;`
  - `floatok` (variable, line 204) `extern boolean floatok;`
  - `tmfloorz` (variable, line 205) `extern fixed_t tmfloorz;`
  - `tmceilingz` (variable, line 206) `extern fixed_t tmceilingz;`
  - `ceilingline` (variable, line 209) `extern line_t* ceilingline;`
  - `spechit` (variable, line 222) `extern line_t* spechit[MAXSPECIALCROSS];`
  - `numspechit` (variable, line 223) `extern int numspechit;`
  - `linetarget` (variable, line 234) `extern mobj_t* linetarget;`
  - `rejectmatrix` (variable, line 261) `extern byte* rejectmatrix;`
  - `blockmaplump` (variable, line 262) `extern short* blockmaplump;`
  - `blockmap` (variable, line 263) `extern short* blockmap;`
  - `bmapwidth` (variable, line 264) `extern int bmapwidth;`
  - `bmapheight` (variable, line 265) `extern int bmapheight;`
  - `bmaporgx` (variable, line 266) `extern fixed_t bmaporgx;`
  - `bmaporgy` (variable, line 267) `extern fixed_t bmaporgy;`
  - `blocklinks` (variable, line 268) `extern mobj_t** blocklinks;`
  - `maxammo` (variable, line 275) `extern int maxammo[NUMAMMO];`
  - `clipammo` (variable, line 276) `extern int clipammo[NUMAMMO];`
  - `__P_LOCAL__` (macro, line 21) `#define __P_LOCAL__`
  - `FLOATSPEED` (macro, line 27) `#define FLOATSPEED`
  - `MAXHEALTH` (macro, line 30) `#define MAXHEALTH`
  - `VIEWHEIGHT` (macro, line 31) `#define VIEWHEIGHT`
  - `MAPBLOCKUNITS` (macro, line 35) `#define MAPBLOCKUNITS`
  - `MAPBLOCKSIZE` (macro, line 36) `#define MAPBLOCKSIZE`
  - `MAPBLOCKSHIFT` (macro, line 37) `#define MAPBLOCKSHIFT`
  - `MAPBMASK` (macro, line 38) `#define MAPBMASK`
  - `MAPBTOFRAC` (macro, line 39) `#define MAPBTOFRAC`
  - `PLAYERRADIUS` (macro, line 43) `#define PLAYERRADIUS`
  - `MAXRADIUS` (macro, line 48) `#define MAXRADIUS`
  - `GRAVITY` (macro, line 50) `#define GRAVITY`
  - `MAXMOVE` (macro, line 51) `#define MAXMOVE`
  - `USERANGE` (macro, line 53) `#define USERANGE`
  - `MELEERANGE` (macro, line 54) `#define MELEERANGE`
  - `MISSILERANGE` (macro, line 55) `#define MISSILERANGE`
  - `BASETHRESHOLD` (macro, line 58) `#define	BASETHRESHOLD`
  - `ONFLOORZ` (macro, line 92) `#define ONFLOORZ`
  - `ONCEILINGZ` (macro, line 93) `#define ONCEILINGZ`
  - `ITEMQUESIZE` (macro, line 96) `#define ITEMQUESIZE`
  - `MAXINTERCEPTS_ORIGINAL` (macro, line 154) `#define MAXINTERCEPTS_ORIGINAL`
  - `MAXINTERCEPTS` (macro, line 155) `#define MAXINTERCEPTS`
  - `PT_ADDLINES` (macro, line 179) `#define PT_ADDLINES`
  - `PT_ADDTHINGS` (macro, line 180) `#define PT_ADDTHINGS`
  - `PT_EARLYOUT` (macro, line 181) `#define PT_EARLYOUT`
  - `MAXSPECIALCROSS` (macro, line 219) `#define MAXSPECIALCROSS`
  - `MAXSPECIALCROSS_ORIGINAL` (macro, line 220) `#define MAXSPECIALCROSS_ORIGINAL`
- Depends on: `progs/doomgeneric/p_spec.h`, `progs/doomgeneric/r_local.h`
- Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/p_ceilng.c`, `progs/doomgeneric/p_doors.c`, `progs/doomgeneric/p_enemy.c`, `progs/doomgeneric/p_floor.c`, `progs/doomgeneric/p_inter.c`, `progs/doomgeneric/p_lights.c`, `progs/doomgeneric/p_map.c`, `progs/doomgeneric/p_maputl.c`, `progs/doomgeneric/p_mobj.c`, `progs/doomgeneric/p_plats.c`, `progs/doomgeneric/p_pspr.c`, `progs/doomgeneric/p_saveg.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/p_sight.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/p_switch.c`, `progs/doomgeneric/p_telept.c`, `progs/doomgeneric/p_tick.c`, `progs/doomgeneric/p_user.c`, `progs/doomgeneric/r_data.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/st_stuff.c`

## progs/doomgeneric/p_map.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard, Andrey Budko  This program is free softwar
- Language: c
- Symbols:
  - `PIT_StompThing` (function, line 97) `boolean PIT_StompThing (mobj_t* thing)`
  - `P_TeleportMove` (function, line 131) `boolean
P_TeleportMove
( mobj_t*	thing,
  fixed_t	x,
  fixed_t	y )`
  - `PIT_CheckLine` (function, line 206) `boolean PIT_CheckLine (line_t* ld)`
  - `PIT_CheckThing` (function, line 275) `boolean PIT_CheckThing (mobj_t* thing)`
  - `P_CheckPosition` (function, line 402) `boolean
P_CheckPosition
( mobj_t*	thing,
  fixed_t	x,
  fixed_t	y )`
  - `P_TryMove` (function, line 478) `boolean
P_TryMove
( mobj_t*	thing,
  fixed_t	x,
  fixed_t	y )`
  - `P_ThingHeightClip` (function, line 557) `boolean P_ThingHeightClip (mobj_t* thing)`
  - `P_HitSlideLine` (function, line 611) `void P_HitSlideLine (line_t* ld)`
  - `PTR_SlideTraverse` (function, line 663) `boolean PTR_SlideTraverse (intercept_t* in)`
  - `P_SlideMove` (function, line 722) `void P_SlideMove (mobj_t* mo)`
  - `PTR_AimTraverse` (function, line 843) `boolean
PTR_AimTraverse (intercept_t* in)`
  - `PTR_ShootTraverse` (function, line 928) `boolean PTR_ShootTraverse (intercept_t* in)`
  - `P_AimLineAttack` (function, line 1068) `fixed_t
P_AimLineAttack
( mobj_t*	t1,
  angle_t	angle,
  fixed_t	distance )`
  - `P_LineAttack` (function, line 1110) `void
P_LineAttack
( mobj_t*	t1,
  angle_t	angle,
  fixed_t	distance,
  fixed_t	slope,
  int		dama...`
  - `PTR_UseTraverse` (function, line 1142) `boolean	PTR_UseTraverse (intercept_t* in)`
  - `P_UseLines` (function, line 1177) `void P_UseLines (player_t*	player)`
  - `PIT_RadiusAttack` (function, line 1211) `boolean PIT_RadiusAttack (mobj_t* thing)`
  - `P_RadiusAttack` (function, line 1253) `void
P_RadiusAttack
( mobj_t*	spot,
  mobj_t*	source,
  int		damage )`
  - `PIT_ChangeSector` (function, line 1304) `boolean PIT_ChangeSector (mobj_t*	thing)`
  - `P_ChangeSector` (function, line 1368) `boolean
P_ChangeSector
( sector_t*	sector,
  boolean	crunch )`
  - `SpechitOverrun` (function, line 1391) `static void SpechitOverrun(line_t *ld)`
  - `topslope` (variable, line 834) `extern fixed_t topslope;`
  - `bottomslope` (variable, line 835) `extern fixed_t bottomslope;`
  - `DEFAULT_SPECHIT_MAGIC` (macro, line 50) `#define DEFAULT_SPECHIT_MAGIC`
- Depends on: `progs/doomgeneric/deh_misc.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_bbox.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`

## progs/doomgeneric/p_maputl.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard Copyright(C) 2005, 2006 Andrey Budko  This 
- Language: c
- Symbols:
  - `intercepts_overrun_t` (struct, line 738)
  - `P_AproxDistance` (function, line 44) `fixed_t
P_AproxDistance
( fixed_t	dx,
  fixed_t	dy )`
  - `P_PointOnLineSide` (function, line 61) `int
P_PointOnLineSide
( fixed_t	x,
  fixed_t	y,
  line_t*	line )`
  - `P_BoxOnLineSide` (function, line 105) `int
P_BoxOnLineSide
( fixed_t*	tmbox,
  line_t*	ld )`
  - `P_PointOnDivlineSide` (function, line 156) `int
P_PointOnDivlineSide
( fixed_t	x,
  fixed_t	y,
  divline_t*	line )`
  - `P_MakeDivline` (function, line 206) `void
P_MakeDivline
( line_t*	li,
  divline_t*	dl )`
  - `P_InterceptVector` (function, line 226) `fixed_t
P_InterceptVector
( divline_t*	v2,
  divline_t*	v1 )`
  - `P_LineOpening` (function, line 295) `void P_LineOpening (line_t* linedef)`
  - `P_UnsetThingPosition` (function, line 342) `void P_UnsetThingPosition (mobj_t* thing)`
  - `P_SetThingPosition` (function, line 391) `void
P_SetThingPosition (mobj_t* thing)`
  - `P_BlockLinesIterator` (function, line 467) `boolean
P_BlockLinesIterator
( int			x,
  int			y,
  boolean(*func)(line_t*) )`
  - `P_BlockThingsIterator` (function, line 508) `boolean
P_BlockThingsIterator
( int			x,
  int			y,
  boolean(*func)(mobj_t*) )`
  - `PIT_AddLineIntercepts` (function, line 559) `boolean
PIT_AddLineIntercepts (line_t* ld)`
  - `PIT_AddThingIntercepts` (function, line 614) `boolean PIT_AddThingIntercepts (mobj_t* thing)`
  - `P_TraverseIntercepts` (function, line 682) `boolean
P_TraverseIntercepts
( traverser_t	func,
  fixed_t	maxfrac )`
  - `InterceptsMemoryOverrun` (function, line 782) `static void InterceptsMemoryOverrun(int location, int value)`
  - `InterceptsOverrun` (function, line 827) `static void InterceptsOverrun(int num_intercepts, intercept_t *intercept)`
  - `P_PathTraverse` (function, line 861) `boolean
P_PathTraverse
( fixed_t		x1,
  fixed_t		y1,
  fixed_t		x2,
  fixed_t		y2,
  int			flags,...`
  - `bulletslope` (variable, line 731) `extern fixed_t bulletslope;`
- Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/m_bbox.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_state.h`

## progs/doomgeneric/p_mobj.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `P_SetMobjState` (function, line 48) `boolean
P_SetMobjState
( mobj_t*	mobj,
  statenum_t	state )`
  - `P_ExplodeMissile` (function, line 84) `void P_ExplodeMissile (mobj_t* mo)`
  - `P_XYMovement` (function, line 108) `void P_XYMovement (mobj_t* mo)`
  - `P_ZMovement` (function, line 240) `void P_ZMovement (mobj_t* mo)`
  - `P_NightmareRespawn` (function, line 383) `void
P_NightmareRespawn (mobj_t* mobj)`
  - `P_MobjThinker` (function, line 441) `void P_MobjThinker (mobj_t* mobj)`
  - `P_SpawnMobj` (function, line 506) `mobj_t*
P_SpawnMobj
( fixed_t	x,
  fixed_t	y,
  fixed_t	z,
  mobjtype_t	type )`
  - `P_RemoveMobj` (function, line 572) `void P_RemoveMobj (mobj_t* mobj)`
  - `P_RespawnSpecials` (function, line 604) `void P_RespawnSpecials (void)`
  - `P_SpawnPlayer` (function, line 668) `void P_SpawnPlayer (mapthing_t* mthing)`
  - `P_SpawnMapThing` (function, line 739) `void P_SpawnMapThing (mapthing_t* mthing)`
  - `P_SpawnPuff` (function, line 851) `void
P_SpawnPuff
( fixed_t	x,
  fixed_t	y,
  fixed_t	z )`
  - `P_SpawnBlood` (function, line 878) `void
P_SpawnBlood
( fixed_t	x,
  fixed_t	y,
  fixed_t	z,
  int		damage )`
  - `P_CheckMissileSpawn` (function, line 907) `void P_CheckMissileSpawn (mobj_t* th)`
  - `P_SubstNullMobj` (function, line 929) `mobj_t *P_SubstNullMobj(mobj_t *mobj)`
  - `P_SpawnMissile` (function, line 950) `mobj_t*
P_SpawnMissile
( mobj_t*	source,
  mobj_t*	dest,
  mobjtype_t	type )`
  - `P_SpawnPlayerMissile` (function, line 996) `void
P_SpawnPlayerMissile
( mobj_t*	source,
  mobjtype_t	type )`
  - `G_PlayerReborn` (function, line 37) `void G_PlayerReborn (int player);`
  - `attackrange` (variable, line 848) `extern fixed_t attackrange;`
  - `STOPSPEED` (macro, line 105) `#define STOPSPEED`
  - `FRICTION` (macro, line 106) `#define FRICTION`
- Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/hu_stuff.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/st_stuff.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/p_mobj.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `mobj_s` (struct, line 201)
  - `thinker` (type_alias, line 201) `typedef struct mobj_s { // List: thinker links. thinker_t thinker;`
  - `__P_MOBJ__` (macro, line 21) `#define __P_MOBJ__`
- Depends on: `progs/doomgeneric/d_think.h`, `progs/doomgeneric/doomdata.h`, `progs/doomgeneric/info.h`, `progs/doomgeneric/m_fixed.h`, `progs/doomgeneric/tables.h`
- Imported by: `progs/doomgeneric/d_player.h`, `progs/doomgeneric/info.c`, `progs/doomgeneric/r_defs.h`, `progs/doomgeneric/s_sound.h`

## progs/doomgeneric/p_plats.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `T_PlatRaise` (function, line 45) `void T_PlatRaise(plat_t* plat)`
  - `EV_DoPlat` (function, line 129) `int
EV_DoPlat
( line_t*	line,
  plattype_e	type,
  int		amount )`
  - `P_ActivateInStasis` (function, line 248) `void P_ActivateInStasis(int tag)`
  - `EV_StopPlat` (function, line 263) `void EV_StopPlat(line_t* line)`
  - `P_AddActivePlat` (function, line 278) `void P_AddActivePlat(plat_t* plat)`
  - `P_RemoveActivePlat` (function, line 291) `void P_RemoveActivePlat(plat_t* plat)`
- Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/p_pspr.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `P_SetPsprite` (function, line 50) `void
P_SetPsprite
( player_t*	player,
  int		position,
  statenum_t	stnum )`
  - `P_CalcSwing` (function, line 103) `void P_CalcSwing (player_t*	player)`
  - `P_BringUpWeapon` (function, line 129) `void P_BringUpWeapon (player_t* player)`
  - `P_CheckAmmo` (function, line 152) `boolean P_CheckAmmo (player_t* player)`
  - `P_FireWeapon` (function, line 237) `void P_FireWeapon (player_t* player)`
  - `P_DropWeapon` (function, line 256) `void P_DropWeapon (player_t* player)`
  - `A_WeaponReady` (function, line 273) `void
A_WeaponReady
( player_t*	player,
  pspdef_t*	psp )`
  - `A_ReFire` (function, line 334) `void A_ReFire
( player_t*	player,
  pspdef_t*	psp )`
  - `A_CheckReload` (function, line 357) `void
A_CheckReload
( player_t*	player,
  pspdef_t*	psp )`
  - `A_Lower` (function, line 376) `void
A_Lower
( player_t*	player,
  pspdef_t*	psp )`
  - `A_Raise` (function, line 414) `void
A_Raise
( player_t*	player,
  pspdef_t*	psp )`
  - `A_GunFlash` (function, line 440) `void
A_GunFlash
( player_t*	player,
  pspdef_t*	psp )`
  - `A_Punch` (function, line 459) `void
A_Punch
( player_t*	player,
  pspdef_t*	psp )`
  - `A_Saw` (function, line 493) `void
A_Saw
( player_t*	player,
  pspdef_t*	psp )`
  - `DecreaseAmmo` (function, line 542) `static void DecreaseAmmo(player_t *player, int ammonum, int amount)`
  - `A_FireMissile` (function, line 559) `void
A_FireMissile
( player_t*	player,
  pspdef_t*	psp )`
  - `A_FireBFG` (function, line 572) `void
A_FireBFG
( player_t*	player,
  pspdef_t*	psp )`
  - `A_FirePlasma` (function, line 587) `void
A_FirePlasma
( player_t*	player,
  pspdef_t*	psp )`
  - `P_BulletSlope` (function, line 610) `void P_BulletSlope (mobj_t*	mo)`
  - `P_GunShot` (function, line 635) `void
P_GunShot
( mobj_t*	mo,
  boolean	accurate )`
  - `A_FirePistol` (function, line 656) `void
A_FirePistol
( player_t*	player,
  pspdef_t*	psp )`
  - `A_FireShotgun` (function, line 678) `void
A_FireShotgun
( player_t*	player,
  pspdef_t*	psp )`
  - `A_FireShotgun2` (function, line 705) `void
A_FireShotgun2
( player_t*	player,
  pspdef_t*	psp )`
  - `A_FireCGun` (function, line 742) `void
A_FireCGun
( player_t*	player,
  pspdef_t*	psp )`
  - `A_Light0` (function, line 770) `void A_Light0 (player_t *player, pspdef_t *psp)`
  - `A_Light1` (function, line 775) `void A_Light1 (player_t *player, pspdef_t *psp)`
  - `A_Light2` (function, line 780) `void A_Light2 (player_t *player, pspdef_t *psp)`
  - `A_BFGSpray` (function, line 790) `void A_BFGSpray (mobj_t* mo)`
  - `A_BFGsound` (function, line 827) `void
A_BFGsound
( player_t*	player,
  pspdef_t*	psp )`
  - `P_SetupPsprites` (function, line 840) `void P_SetupPsprites (player_t* player)`
  - `P_MovePsprites` (function, line 860) `void P_MovePsprites (player_t* player)`
  - `LOWERSPEED` (macro, line 38) `#define LOWERSPEED`
  - `RAISESPEED` (macro, line 39) `#define RAISESPEED`
  - `WEAPONBOTTOM` (macro, line 41) `#define WEAPONBOTTOM`
  - `WEAPONTOP` (macro, line 42) `#define WEAPONTOP`
- Depends on: `progs/doomgeneric/d_event.h`, `progs/doomgeneric/deh_misc.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/p_pspr.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`

## progs/doomgeneric/p_pspr.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `pspdef_t` (struct, line 62)
  - `__P_PSPR__` (macro, line 21) `#define __P_PSPR__`
  - `FF_FULLBRIGHT` (macro, line 44) `#define FF_FULLBRIGHT`
  - `FF_FRAMEMASK` (macro, line 45) `#define FF_FRAMEMASK`
- Depends on: `progs/doomgeneric/info.h`, `progs/doomgeneric/m_fixed.h`, `progs/doomgeneric/tables.h`
- Imported by: `progs/doomgeneric/d_player.h`, `progs/doomgeneric/p_pspr.c`

## progs/doomgeneric/p_saveg.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `P_TempSaveGameFile` (function, line 47) `char *P_TempSaveGameFile(void)`
  - `P_SaveGameFile` (function, line 61) `char *P_SaveGameFile(int slot)`
  - `saveg_read8` (function, line 81) `static byte saveg_read8(void)`
  - `saveg_write8` (function, line 99) `static void saveg_write8(byte value)`
  - `saveg_read16` (function, line 112) `static short saveg_read16(void)`
  - `saveg_write16` (function, line 122) `static void saveg_write16(short value)`
  - `saveg_read32` (function, line 128) `static int saveg_read32(void)`
  - `saveg_write32` (function, line 140) `static void saveg_write32(int value)`
  - `saveg_read_pad` (function, line 150) `static void saveg_read_pad(void)`
  - `saveg_write_pad` (function, line 166) `static void saveg_write_pad(void)`
  - `saveg_readp` (function, line 185) `static void *saveg_readp(void)`
  - `saveg_writep` (function, line 190) `static void saveg_writep(void *p)`
  - `saveg_read_mapthing_t` (function, line 208) `static void saveg_read_mapthing_t(mapthing_t *str)`
  - `saveg_write_mapthing_t` (function, line 226) `static void saveg_write_mapthing_t(mapthing_t *str)`
  - `saveg_read_actionf_t` (function, line 248) `static void saveg_read_actionf_t(actionf_t *str)`
  - `saveg_write_actionf_t` (function, line 254) `static void saveg_write_actionf_t(actionf_t *str)`
  - `saveg_read_thinker_t` (function, line 273) `static void saveg_read_thinker_t(thinker_t *str)`
  - `saveg_write_thinker_t` (function, line 285) `static void saveg_write_thinker_t(thinker_t *str)`
  - `saveg_read_mobj_t` (function, line 301) `static void saveg_read_mobj_t(mobj_t *str)`
  - `saveg_write_mobj_t` (function, line 421) `static void saveg_write_mobj_t(mobj_t *str)`
  - `saveg_read_ticcmd_t` (function, line 541) `static void saveg_read_ticcmd_t(ticcmd_t *str)`
  - `saveg_write_ticcmd_t` (function, line 563) `static void saveg_write_ticcmd_t(ticcmd_t *str)`
  - `saveg_read_pspdef_t` (function, line 589) `static void saveg_read_pspdef_t(pspdef_t *str)`
  - `saveg_write_pspdef_t` (function, line 615) `static void saveg_write_pspdef_t(pspdef_t *str)`
  - `saveg_read_player_t` (function, line 641) `static void saveg_read_player_t(player_t *str)`
  - `saveg_write_player_t` (function, line 772) `static void saveg_write_player_t(player_t *str)`
  - `saveg_read_ceiling_t` (function, line 908) `static void saveg_read_ceiling_t(ceiling_t *str)`
  - `saveg_write_ceiling_t` (function, line 944) `static void saveg_write_ceiling_t(ceiling_t *str)`
  - `saveg_read_vldoor_t` (function, line 981) `static void saveg_read_vldoor_t(vldoor_t *str)`
  - `saveg_write_vldoor_t` (function, line 1011) `static void saveg_write_vldoor_t(vldoor_t *str)`
  - `saveg_read_floormove_t` (function, line 1042) `static void saveg_read_floormove_t(floormove_t *str)`
  - `saveg_write_floormove_t` (function, line 1075) `static void saveg_write_floormove_t(floormove_t *str)`
  - `saveg_read_plat_t` (function, line 1109) `static void saveg_read_plat_t(plat_t *str)`
  - `saveg_write_plat_t` (function, line 1151) `static void saveg_write_plat_t(plat_t *str)`
  - `saveg_read_lightflash_t` (function, line 1194) `static void saveg_read_lightflash_t(lightflash_t *str)`
  - `saveg_write_lightflash_t` (function, line 1221) `static void saveg_write_lightflash_t(lightflash_t *str)`
  - `saveg_read_strobe_t` (function, line 1249) `static void saveg_read_strobe_t(strobe_t *str)`
  - `saveg_write_strobe_t` (function, line 1276) `static void saveg_write_strobe_t(strobe_t *str)`
  - `saveg_read_glow_t` (function, line 1304) `static void saveg_read_glow_t(glow_t *str)`
  - `saveg_write_glow_t` (function, line 1325) `static void saveg_write_glow_t(glow_t *str)`
  - `P_WriteSaveGameHeader` (function, line 1347) `void P_WriteSaveGameHeader(char *description)`
  - `P_ReadSaveGameHeader` (function, line 1379) `boolean P_ReadSaveGameHeader(void)`
  - `P_ReadSaveGameEOF` (function, line 1419) `boolean P_ReadSaveGameEOF(void)`
  - `P_WriteSaveGameEOF` (function, line 1432) `void P_WriteSaveGameEOF(void)`
  - `P_ArchivePlayers` (function, line 1440) `void P_ArchivePlayers (void)`
  - `P_UnArchivePlayers` (function, line 1460) `void P_UnArchivePlayers (void)`
  - `P_ArchiveWorld` (function, line 1484) `void P_ArchiveWorld (void)`
  - `P_UnArchiveWorld` (function, line 1532) `void P_UnArchiveWorld (void)`
  - `P_ArchiveThinkers` (function, line 1592) `void P_ArchiveThinkers (void)`
  - `P_UnArchiveThinkers` (function, line 1620) `void P_UnArchiveThinkers (void)`
  - `P_ArchiveSpecials` (function, line 1704) `void P_ArchiveSpecials (void)`
  - `P_UnArchiveSpecials` (function, line 1793) `void P_UnArchiveSpecials (void)`
  - `SAVEGAME_EOF` (macro, line 36) `#define SAVEGAME_EOF`
  - `VERSIONSIZE` (macro, line 37) `#define VERSIONSIZE`
  - `saveg_read_enum` (macro, line 197) `#define saveg_read_enum`
  - `saveg_write_enum` (macro, line 198) `#define saveg_write_enum`
  - `saveg_read_think_t` (macro, line 266) `#define saveg_read_think_t`
  - `saveg_write_think_t` (macro, line 267) `#define saveg_write_think_t`
- Depends on: `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/dstrings.h`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/p_saveg.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/p_saveg.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `P_TempSaveGameFile` (function, line 31) `char *P_TempSaveGameFile(void);`
  - `P_SaveGameFile` (function, line 35) `char *P_SaveGameFile(int slot);`
  - `P_WriteSaveGameHeader` (function, line 40) `void P_WriteSaveGameHeader(char *description);`
  - `P_WriteSaveGameEOF` (function, line 45) `void P_WriteSaveGameEOF(void);`
  - `P_ArchivePlayers` (function, line 49) `void P_ArchivePlayers (void);`
  - `P_UnArchivePlayers` (function, line 50) `void P_UnArchivePlayers (void);`
  - `P_ArchiveWorld` (function, line 51) `void P_ArchiveWorld (void);`
  - `P_UnArchiveWorld` (function, line 52) `void P_UnArchiveWorld (void);`
  - `P_ArchiveThinkers` (function, line 53) `void P_ArchiveThinkers (void);`
  - `P_UnArchiveThinkers` (function, line 54) `void P_UnArchiveThinkers (void);`
  - `P_ArchiveSpecials` (function, line 55) `void P_ArchiveSpecials (void);`
  - `P_UnArchiveSpecials` (function, line 56) `void P_UnArchiveSpecials (void);`
  - `save_stream` (variable, line 58) `extern FILE *save_stream;`
  - `savegame_error` (variable, line 59) `extern boolean savegame_error;`
  - `__P_SAVEG__` (macro, line 21) `#define __P_SAVEG__`
  - `SAVESTRINGSIZE` (macro, line 27) `#define SAVESTRINGSIZE`
- Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/p_saveg.c`

## progs/doomgeneric/p_setup.c
- Layer: infrastructure
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `P_LoadVertexes` (function, line 118) `void P_LoadVertexes (int lump)`
  - `GetSectorAtNullAddress` (function, line 153) `sector_t* GetSectorAtNullAddress(void)`
  - `P_LoadSegs` (function, line 172) `void P_LoadSegs (int lump)`
  - `P_LoadSubsectors` (function, line 236) `void P_LoadSubsectors (int lump)`
  - `P_LoadSectors` (function, line 265) `void P_LoadSectors (int lump)`
  - `P_LoadNodes` (function, line 298) `void P_LoadNodes (int lump)`
  - `P_LoadThings` (function, line 335) `void P_LoadThings (int lump)`
  - `P_LoadLineDefs` (function, line 392) `void P_LoadLineDefs (int lump)`
  - `P_LoadSideDefs` (function, line 473) `void P_LoadSideDefs (int lump)`
  - `P_LoadBlockMap` (function, line 504) `void P_LoadBlockMap (int lump)`
  - `P_GroupLines` (function, line 545) `void P_GroupLines (void)`
  - `PadRejectArray` (function, line 661) `static void PadRejectArray(byte *array, unsigned int len)`
  - `P_LoadReject` (function, line 712) `static void P_LoadReject(int lumpnum)`
  - `P_SetupLevel` (function, line 744) `void
P_SetupLevel
( int		episode,
  int		map,
  int		playermask,
  skill_t	skill)`
  - `P_Init` (function, line 847) `void P_Init (void)`
  - `P_SpawnMapThing` (function, line 44) `void P_SpawnMapThing (mapthing_t* mthing);`
  - `MAX_DEATHMATCH_STARTS` (macro, line 105) `#define MAX_DEATHMATCH_STARTS`
- Depends on: `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_bbox.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/p_setup.h
- Layer: infrastructure
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `P_SetupLevel` (function, line 28) `void P_SetupLevel ( int episode, int map, int playermask, skill_t skill);`
  - `P_Init` (function, line 35) `void P_Init (void);`
  - `__P_SETUP__` (macro, line 21) `#define __P_SETUP__`
- Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/g_game.c`

## progs/doomgeneric/p_sight.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `P_DivlineSide` (function, line 48) `int
P_DivlineSide
( fixed_t	x,
  fixed_t	y,
  divline_t*	node )`
  - `P_InterceptVector2` (function, line 102) `fixed_t
P_InterceptVector2
( divline_t*	v2,
  divline_t*	v1 )`
  - `P_CrossSubsector` (function, line 128) `boolean P_CrossSubsector (int num)`
  - `P_CrossBSPNode` (function, line 258) `boolean P_CrossBSPNode (int bspnum)`
  - `P_CheckSight` (function, line 301) `boolean
P_CheckSight
( mobj_t*	t1,
  mobj_t*	t2 )`
- Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_state.h`

## progs/doomgeneric/p_spec.c
- Layer: testing
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `anim_t` (struct, line 55)
  - `animdef_t` (struct, line 68)
  - `P_InitPicAnims` (function, line 143) `void P_InitPicAnims (void)`
  - `getSide` (function, line 203) `side_t*
getSide
( int		currentSector,
  int		line,
  int		side )`
  - `getSector` (function, line 219) `sector_t*
getSector
( int		currentSector,
  int		line,
  int		side )`
  - `twoSided` (function, line 234) `int
twoSided
( int	sector,
  int	line )`
  - `getNextSector` (function, line 250) `sector_t*
getNextSector
( line_t*	line,
  sector_t*	sec )`
  - `P_FindLowestFloorSurrounding` (function, line 269) `fixed_t	P_FindLowestFloorSurrounding(sector_t* sec)`
  - `P_FindHighestFloorSurrounding` (function, line 296) `fixed_t	P_FindHighestFloorSurrounding(sector_t *sec)`
  - `P_FindNextHighestFloor` (function, line 330) `fixed_t
P_FindNextHighestFloor
( sector_t* sec,
  int       currentheight )`
  - `P_FindLowestCeilingSurrounding` (function, line 392) `fixed_t
P_FindLowestCeilingSurrounding(sector_t* sec)`
  - `P_FindHighestCeilingSurrounding` (function, line 417) `fixed_t	P_FindHighestCeilingSurrounding(sector_t* sec)`
  - `P_FindSectorFromLineTag` (function, line 444) `int
P_FindSectorFromLineTag
( line_t*	line,
  int		start )`
  - `P_FindMinSurroundingLight` (function, line 464) `int
P_FindMinSurroundingLight
( sector_t*	sector,
  int		max )`
  - `P_CrossSpecialLine` (function, line 502) `void
P_CrossSpecialLine
( int		linenum,
  int		side,
  mobj_t*	thing )`
  - `P_ShootSpecialLine` (function, line 969) `void
P_ShootSpecialLine
( mobj_t*	thing,
  line_t*	line )`
  - `P_PlayerInSpecialSector` (function, line 1019) `void P_PlayerInSpecialSector (player_t* player)`
  - `P_UpdateSpecials` (function, line 1093) `void P_UpdateSpecials (void)`
  - `DonutOverrun` (function, line 1178) `static void DonutOverrun(fixed_t *s3_floorheight, short *s3_floorpic,
                         li...`
  - `EV_DoDonut` (function, line 1257) `int EV_DoDonut(line_t*	line)`
  - `P_SpawnSpecials` (function, line 1374) `void P_SpawnSpecials (void)`
  - `anims` (variable, line 80) `extern anim_t anims[MAXANIMS];`
  - `lastanim` (variable, line 81) `extern anim_t* lastanim;`
  - `numlinespecials` (variable, line 138) `extern short numlinespecials;`
  - `linespeciallist` (variable, line 139) `extern line_t* linespeciallist[MAXLINEANIMS];`
  - `numflats` (variable, line 1185) `extern int numflats;`
  - `MAXANIMS` (macro, line 78) `#define MAXANIMS`
  - `MAXLINEANIMS` (macro, line 136) `#define MAXLINEANIMS`
  - `MAX_ADJOINING_SECTORS` (macro, line 327) `#define MAX_ADJOINING_SECTORS`
  - `DONUT_FLOORHEIGHT_DEFAULT` (macro, line 1175) `#define DONUT_FLOORHEIGHT_DEFAULT`
  - `DONUT_FLOORPIC_DEFAULT` (macro, line 1176) `#define DONUT_FLOORPIC_DEFAULT`
- Depends on: `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/p_spec.h
- Layer: testing
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `fireflicker_t` (struct, line 121)
  - `lightflash_t` (struct, line 133)
  - `strobe_t` (struct, line 147)
  - `glow_t` (struct, line 162)
  - `switchlist_t` (struct, line 206)
  - `button_t` (struct, line 224)
  - `plat_t` (struct, line 282)
  - `vldoor_t` (struct, line 340)
  - `slidedoor_t` (struct, line 415)
  - `slidename_t` (struct, line 431)
  - `slideframe_t` (struct, line 446)
  - `ceiling_t` (struct, line 490)
  - `floormove_t` (struct, line 581)
  - `P_InitPicAnims` (function, line 39) `void P_InitPicAnims (void);`
  - `P_SpawnSpecials` (function, line 42) `void P_SpawnSpecials (void);`
  - `P_UpdateSpecials` (function, line 45) `void P_UpdateSpecials (void);`
  - `P_ShootSpecialLine` (function, line 55) `void P_ShootSpecialLine ( mobj_t* thing, line_t* line );`
  - `P_CrossSpecialLine` (function, line 60) `void P_CrossSpecialLine ( int linenum, int side, mobj_t* thing );`
  - `P_PlayerInSpecialSector` (function, line 65) `void P_PlayerInSpecialSector (player_t* player);`
  - `twoSided` (function, line 68) `int twoSided ( int sector, int line );`
  - `getSector` (function, line 73) `sector_t* getSector ( int currentSector, int line, int side );`
  - `getSide` (function, line 79) `side_t* getSide ( int currentSector, int line, int side );`
  - `P_FindLowestFloorSurrounding` (function, line 84) `fixed_t P_FindLowestFloorSurrounding(sector_t* sec);`
  - `P_FindHighestFloorSurrounding` (function, line 85) `fixed_t P_FindHighestFloorSurrounding(sector_t* sec);`
  - `P_FindNextHighestFloor` (function, line 88) `fixed_t P_FindNextHighestFloor ( sector_t* sec, int currentheight );`
  - `P_FindLowestCeilingSurrounding` (function, line 92) `fixed_t P_FindLowestCeilingSurrounding(sector_t* sec);`
  - `P_FindHighestCeilingSurrounding` (function, line 93) `fixed_t P_FindHighestCeilingSurrounding(sector_t* sec);`
  - `P_FindSectorFromLineTag` (function, line 96) `int P_FindSectorFromLineTag ( line_t* line, int start );`
  - `P_FindMinSurroundingLight` (function, line 101) `int P_FindMinSurroundingLight ( sector_t* sector, int max );`
  - `getNextSector` (function, line 106) `sector_t* getNextSector ( line_t* line, sector_t* sec );`
  - `EV_DoDonut` (function, line 114) `int EV_DoDonut(line_t* line);`
  - `P_SpawnFireFlicker` (function, line 178) `void P_SpawnFireFlicker (sector_t* sector);`
  - `T_LightFlash` (function, line 179) `void T_LightFlash (lightflash_t* flash);`
  - `P_SpawnLightFlash` (function, line 180) `void P_SpawnLightFlash (sector_t* sector);`
  - `T_StrobeFlash` (function, line 181) `void T_StrobeFlash (strobe_t* flash);`
  - `P_SpawnStrobeFlash` (function, line 184) `void P_SpawnStrobeFlash ( sector_t* sector, int fastOrSlow, int inSync );`
  - `EV_StartLightStrobing` (function, line 189) `void EV_StartLightStrobing(line_t* line);`
  - `EV_TurnTagLightsOff` (function, line 190) `void EV_TurnTagLightsOff(line_t* line);`
  - `EV_LightTurnOn` (function, line 193) `void EV_LightTurnOn ( line_t* line, int bright );`
  - `T_Glow` (function, line 197) `void T_Glow(glow_t* g);`
  - `P_SpawnGlowingLight` (function, line 198) `void P_SpawnGlowingLight(sector_t* sector);`
  - `P_ChangeSwitchTexture` (function, line 249) `void P_ChangeSwitchTexture ( line_t* line, int useAgain );`
  - `P_InitSwitchList` (function, line 253) `void P_InitSwitchList(void);`
  - `T_PlatRaise` (function, line 308) `void T_PlatRaise(plat_t* plat);`
  - `EV_DoPlat` (function, line 311) `int EV_DoPlat ( line_t* line, plattype_e type, int amount );`
  - `P_AddActivePlat` (function, line 316) `void P_AddActivePlat(plat_t* plat);`
  - `P_RemoveActivePlat` (function, line 317) `void P_RemoveActivePlat(plat_t* plat);`
  - `EV_StopPlat` (function, line 318) `void EV_StopPlat(line_t* line);`
  - `P_ActivateInStasis` (function, line 319) `void P_ActivateInStasis(int tag);`
  - `EV_VerticalDoor` (function, line 365) `void EV_VerticalDoor ( line_t* line, mobj_t* thing );`
  - `EV_DoDoor` (function, line 370) `int EV_DoDoor ( line_t* line, vldoor_e type );`
  - `EV_DoLockedDoor` (function, line 375) `int EV_DoLockedDoor ( line_t* line, vldoor_e type, mobj_t* thing );`
  - `T_VerticalDoor` (function, line 380) `void T_VerticalDoor (vldoor_t* door);`
  - `P_SpawnDoorCloseIn30` (function, line 381) `void P_SpawnDoorCloseIn30 (sector_t* sec);`
  - `P_SpawnDoorRaiseIn5Mins` (function, line 384) `void P_SpawnDoorRaiseIn5Mins ( sector_t* sec, int secnum );`
  - `P_InitSlidingDoorFrames` (function, line 464) `void P_InitSlidingDoorFrames(void);`
  - `EV_SlidingDoor` (function, line 467) `void EV_SlidingDoor ( line_t* line, mobj_t* thing );`
  - `EV_DoCeiling` (function, line 520) `int EV_DoCeiling ( line_t* line, ceiling_e type );`
  - `T_MoveCeiling` (function, line 524) `void T_MoveCeiling (ceiling_t* ceiling);`
  - `P_AddActiveCeiling` (function, line 525) `void P_AddActiveCeiling(ceiling_t* c);`
  - `P_RemoveActiveCeiling` (function, line 526) `void P_RemoveActiveCeiling(ceiling_t* c);`
  - `EV_CeilingCrushStop` (function, line 527) `int EV_CeilingCrushStop(line_t* line);`
  - `P_ActivateInStasisCeiling` (function, line 528) `void P_ActivateInStasisCeiling(line_t* line);`
  - `EV_BuildStairs` (function, line 617) `int EV_BuildStairs ( line_t* line, stair_e type );`
  - `EV_DoFloor` (function, line 622) `int EV_DoFloor ( line_t* line, floor_e floortype );`
  - `T_MoveFloor` (function, line 626) `void T_MoveFloor( floormove_t* floor);`
  - `EV_Teleport` (function, line 632) `int EV_Teleport ( line_t* line, int side, mobj_t* thing );`
  - `levelTimer` (variable, line 30) `extern boolean levelTimer;`
  - `levelTimeCount` (variable, line 31) `extern int levelTimeCount;`
  - `buttonlist` (variable, line 246) `extern button_t buttonlist[MAXBUTTONS];`
  - `activeplats` (variable, line 306) `extern plat_t* activeplats[MAXPLATS];`
  - `activeceilings` (variable, line 517) `extern ceiling_t* activeceilings[MAXCEILINGS];`
  - `__P_SPEC__` (macro, line 24) `#define __P_SPEC__`
  - `MO_TELEPORTMAN` (macro, line 35) `#define MO_TELEPORTMAN`
  - `GLOWSPEED` (macro, line 173) `#define GLOWSPEED`
  - `STROBEBRIGHT` (macro, line 174) `#define STROBEBRIGHT`
  - `FASTDARK` (macro, line 175) `#define FASTDARK`
  - `SLOWDARK` (macro, line 176) `#define SLOWDARK`
  - `MAXSWITCHES` (macro, line 238) `#define MAXSWITCHES`
  - `MAXBUTTONS` (macro, line 241) `#define MAXBUTTONS`
  - `BUTTONTIME` (macro, line 244) `#define BUTTONTIME`
  - `PLATWAIT` (macro, line 301) `#define PLATWAIT`
  - `PLATSPEED` (macro, line 302) `#define PLATSPEED`
  - `MAXPLATS` (macro, line 303) `#define MAXPLATS`
  - `VDOORSPEED` (macro, line 361) `#define VDOORSPEED`
  - `VDOORWAIT` (macro, line 362) `#define VDOORWAIT`
  - `SNUMFRAMES` (macro, line 456) `#define SNUMFRAMES`
  - `SDOORWAIT` (macro, line 458) `#define SDOORWAIT`
  - `SWAITTICS` (macro, line 459) `#define SWAITTICS`
  - `MAXSLIDEDOORS` (macro, line 462) `#define MAXSLIDEDOORS`
  - `CEILSPEED` (macro, line 513) `#define CEILSPEED`
  - `CEILWAIT` (macro, line 514) `#define CEILWAIT`
  - `MAXCEILINGS` (macro, line 515) `#define MAXCEILINGS`
  - `FLOORSPEED` (macro, line 597) `#define FLOORSPEED`
- Imported by: `progs/doomgeneric/p_local.h`

## progs/doomgeneric/p_switch.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `P_InitSwitchList` (function, line 101) `void P_InitSwitchList(void)`
  - `P_StartButton` (function, line 149) `void
P_StartButton
( line_t*	line,
  bwhere_e	w,
  int		texture,
  int		time )`
  - `P_ChangeSwitchTexture` (function, line 195) `void
P_ChangeSwitchTexture
( line_t*	line,
  int 		useAgain )`
  - `P_UseSpecialLine` (function, line 270) `boolean
P_UseSpecialLine
( mobj_t*	thing,
  line_t*	line,
  int		side )`
- Depends on: `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`

## progs/doomgeneric/p_telept.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `EV_Teleport` (function, line 42) `int
EV_Teleport
( line_t*	line,
  int		side,
  mobj_t*	thing )`
- Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`

## progs/doomgeneric/p_tick.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `P_InitThinkers` (function, line 46) `void P_InitThinkers (void)`
  - `P_AddThinker` (function, line 58) `void P_AddThinker (thinker_t* thinker)`
  - `P_RemoveThinker` (function, line 73) `void P_RemoveThinker (thinker_t* thinker)`
  - `P_AllocateThinker` (function, line 85) `void P_AllocateThinker (thinker_t*	thinker)`
  - `P_RunThinkers` (function, line 94) `void P_RunThinkers (void)`
  - `P_Ticker` (function, line 123) `void P_Ticker (void)`
- Depends on: `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/p_tick.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `P_Ticker` (function, line 29) `void P_Ticker (void);`
  - `__P_TICK__` (macro, line 21) `#define __P_TICK__`
- Imported by: `progs/doomgeneric/g_game.c`

## progs/doomgeneric/p_user.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `P_Thrust` (function, line 52) `void
P_Thrust
( player_t*	player,
  angle_t	angle,
  fixed_t	move )`
  - `P_CalcHeight` (function, line 70) `void P_CalcHeight (player_t* player)`
  - `P_MovePlayer` (function, line 141) `void P_MovePlayer (player_t* player)`
  - `P_DeathThink` (function, line 175) `void P_DeathThink (player_t* player)`
  - `P_PlayerThink` (function, line 229) `void P_PlayerThink (player_t* player)`
  - `INVERSECOLORMAP` (macro, line 34) `#define INVERSECOLORMAP`
  - `MAXBOB` (macro, line 42) `#define MAXBOB`
  - `ANG5` (macro, line 173) `#define ANG5`
- Depends on: `progs/doomgeneric/d_event.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/p_local.h`

## progs/doomgeneric/r_bsp.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `cliprange_t` (struct, line 73)
  - `R_ClearDrawSegs` (function, line 61) `void R_ClearDrawSegs (void)`
  - `R_ClipSolidWallSegment` (function, line 97) `void
R_ClipSolidWallSegment
( int			first,
  int			last )`
  - `R_ClipPassWallSegment` (function, line 190) `void
R_ClipPassWallSegment
( int	first,
  int	last )`
  - `R_ClearClipSegs` (function, line 238) `void R_ClearClipSegs (void)`
  - `R_AddLine` (function, line 252) `void R_AddLine (seg_t*	line)`
  - `R_CheckBBox` (function, line 374) `boolean R_CheckBBox (fixed_t*	bspcoord)`
  - `R_Subsector` (function, line 490) `void R_Subsector (int num)`
  - `R_RenderBSPNode` (function, line 545) `void R_RenderBSPNode (int bspnum)`
  - `R_StoreWallRange` (function, line 51) `void R_StoreWallRange ( int start, int stop );`
  - `MAXSEGS` (macro, line 81) `#define MAXSEGS`
- Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_bbox.h`, `progs/doomgeneric/r_main.h`, `progs/doomgeneric/r_plane.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/r_things.h`

## progs/doomgeneric/r_bsp.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `R_ClearClipSegs` (function, line 54) `void R_ClearClipSegs (void);`
  - `R_ClearDrawSegs` (function, line 55) `void R_ClearDrawSegs (void);`
  - `R_RenderBSPNode` (function, line 58) `void R_RenderBSPNode (int bspnum);`
  - `curline` (variable, line 25) `extern seg_t* curline;`
  - `sidedef` (variable, line 26) `extern side_t* sidedef;`
  - `linedef` (variable, line 27) `extern line_t* linedef;`
  - `frontsector` (variable, line 28) `extern sector_t* frontsector;`
  - `backsector` (variable, line 29) `extern sector_t* backsector;`
  - `rw_x` (variable, line 31) `extern int rw_x;`
  - `rw_stopx` (variable, line 32) `extern int rw_stopx;`
  - `segtextured` (variable, line 34) `extern boolean segtextured;`
  - `markfloor` (variable, line 37) `extern boolean markfloor;`
  - `markceiling` (variable, line 38) `extern boolean markceiling;`
  - `skymap` (variable, line 40) `extern boolean skymap;`
  - `drawsegs` (variable, line 42) `extern drawseg_t drawsegs[MAXDRAWSEGS];`
  - `ds_p` (variable, line 43) `extern drawseg_t* ds_p;`
  - `hscalelight` (variable, line 45) `extern lighttable_t** hscalelight;`
  - `vscalelight` (variable, line 46) `extern lighttable_t** vscalelight;`
  - `dscalelight` (variable, line 47) `extern lighttable_t** dscalelight;`
  - `__R_BSP__` (macro, line 21) `#define __R_BSP__`
- Imported by: `progs/doomgeneric/r_local.h`

## progs/doomgeneric/r_data.c
- Layer: data_access
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `texture_s` (struct, line 106)
  - `texpatch_t` (struct, line 89)
  - `texture_t` (type_alias, line 103) `typedef struct texture_s texture_t;`
  - `R_DrawColumnInCache` (function, line 186) `void
R_DrawColumnInCache
( column_t*	patch,
  byte*		cache,
  int		originy,
  int		cacheheight )`
  - `R_GenerateComposite` (function, line 226) `void R_GenerateComposite (int texnum)`
  - `R_GenerateLookup` (function, line 294) `void R_GenerateLookup (int texnum)`
  - `R_GetColumn` (function, line 383) `byte*
R_GetColumn
( int		tex,
  int		col )`
  - `GenerateTextureHashTable` (function, line 404) `static void GenerateTextureHashTable(void)`
  - `R_InitTextures` (function, line 451) `void R_InitTextures (void)`
  - `R_InitFlats` (function, line 633) `void R_InitFlats (void)`
  - `R_InitSpriteLumps` (function, line 655) `void R_InitSpriteLumps (void)`
  - `R_InitColormaps` (function, line 685) `void R_InitColormaps (void)`
  - `R_InitData` (function, line 703) `void R_InitData (void)`
  - `R_FlatNumForName` (function, line 720) `int R_FlatNumForName (char* name)`
  - `R_CheckTextureNumForName` (function, line 744) `int	R_CheckTextureNumForName (char *name)`
  - `R_TextureNumForName` (function, line 775) `int	R_TextureNumForName (char* name)`
  - `R_PrecacheLevel` (function, line 800) `void R_PrecacheLevel (void)`
- Depends on: `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_data.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/r_sky.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/r_data.h
- Layer: data_access
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `R_GetColumn` (function, line 30) `byte* R_GetColumn ( int tex, int col );`
  - `R_InitData` (function, line 36) `void R_InitData (void);`
  - `R_PrecacheLevel` (function, line 37) `void R_PrecacheLevel (void);`
  - `R_FlatNumForName` (function, line 43) `int R_FlatNumForName (char* name);`
  - `R_TextureNumForName` (function, line 48) `int R_TextureNumForName (char *name);`
  - `R_CheckTextureNumForName` (function, line 49) `int R_CheckTextureNumForName (char *name);`
  - `__R_DATA__` (macro, line 22) `#define __R_DATA__`
- Depends on: `progs/doomgeneric/r_defs.h`, `progs/doomgeneric/r_state.h`
- Imported by: `progs/doomgeneric/g_game.c`, `progs/doomgeneric/r_data.c`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/r_main.h`, `progs/doomgeneric/r_plane.h`, `progs/doomgeneric/r_sky.c`, `progs/doomgeneric/r_state.h`

## progs/doomgeneric/r_defs.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `line_s` (struct, line 76)
  - `line_s` (struct, line 175)
  - `subsector_s` (struct, line 223)
  - `drawseg_s` (struct, line 306)
  - `vissprite_s` (struct, line 338)
  - `vertex_t` (struct, line 67)
  - `degenmobj_t` (struct, line 84)
  - `sector_t` (struct, line 97)
  - `side_t` (struct, line 140)
  - `seg_t` (struct, line 236)
  - `node_t` (struct, line 261)
  - `spriteframe_t` (struct, line 390)
  - `spritedef_t` (struct, line 411)
  - `visplane_t` (struct, line 423)
  - `v1` (type_alias, line 172) `typedef struct line_s { // Vertices, from v1 to v2. vertex_t* v1;`
  - `sector` (type_alias, line 223) `typedef struct subsector_s { sector_t* sector;`
  - `lighttable_t` (type_alias, line 298) `typedef byte lighttable_t;`
  - `curline` (type_alias, line 306) `typedef struct drawseg_s { seg_t* curline;`
  - `prev` (type_alias, line 338) `typedef struct vissprite_s { // Doubly linked list. struct vissprite_s* prev;`
  - `__R_DEFS__` (macro, line 21) `#define __R_DEFS__`
  - `SIL_NONE` (macro, line 46) `#define SIL_NONE`
  - `SIL_BOTTOM` (macro, line 47) `#define SIL_BOTTOM`
  - `SIL_TOP` (macro, line 48) `#define SIL_TOP`
  - `SIL_BOTH` (macro, line 49) `#define SIL_BOTH`
  - `MAXDRAWSEGS` (macro, line 51) `#define MAXDRAWSEGS`
- Depends on: `progs/doomgeneric/d_think.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_fixed.h`, `progs/doomgeneric/p_mobj.h`, `progs/doomgeneric/v_patch.h`
- Imported by: `progs/doomgeneric/hu_lib.h`, `progs/doomgeneric/r_data.h`, `progs/doomgeneric/st_lib.h`

## progs/doomgeneric/r_draw.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `R_DrawColumn` (function, line 102) `void R_DrawColumn (void)`
  - `R_DrawColumn` (function, line 152) `void R_DrawColumn (void)`
  - `R_DrawColumnLow` (function, line 208) `void R_DrawColumnLow (void)`
  - `R_DrawFuzzColumn` (function, line 283) `void R_DrawFuzzColumn (void)`
  - `R_DrawFuzzColumnLow` (function, line 342) `void R_DrawFuzzColumnLow (void)`
  - `R_DrawTranslatedColumn` (function, line 424) `void R_DrawTranslatedColumn (void)`
  - `R_DrawTranslatedColumnLow` (function, line 468) `void R_DrawTranslatedColumnLow (void)`
  - `R_InitTranslationTables` (function, line 530) `void R_InitTranslationTables (void)`
  - `R_DrawSpan` (function, line 590) `void R_DrawSpan (void)`
  - `R_DrawSpan` (function, line 646) `void R_DrawSpan (void)`
  - `R_DrawSpanLow` (function, line 719) `void R_DrawSpanLow (void)`
  - `R_InitBuffer` (function, line 777) `void
R_InitBuffer
( int		width,
  int		height )`
  - `R_FillBackScreen` (function, line 812) `void R_FillBackScreen (void)`
  - `R_VideoErase` (function, line 919) `void
R_VideoErase
( unsigned	ofs,
  int		count )`
  - `R_DrawViewBorder` (function, line 941) `void R_DrawViewBorder (void)`
  - `MAXWIDTH` (macro, line 41) `#define MAXWIDTH`
  - `MAXHEIGHT` (macro, line 42) `#define MAXHEIGHT`
  - `SBARHEIGHT` (macro, line 45) `#define SBARHEIGHT`
  - `FUZZTABLE` (macro, line 257) `#define FUZZTABLE`
  - `FUZZOFF` (macro, line 258) `#define FUZZOFF`
- Depends on: `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/r_draw.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `R_DrawColumn` (function, line 40) `void R_DrawColumn (void);`
  - `R_DrawColumnLow` (function, line 41) `void R_DrawColumnLow (void);`
  - `R_DrawFuzzColumn` (function, line 44) `void R_DrawFuzzColumn (void);`
  - `R_DrawFuzzColumnLow` (function, line 45) `void R_DrawFuzzColumnLow (void);`
  - `R_DrawTranslatedColumn` (function, line 50) `void R_DrawTranslatedColumn (void);`
  - `R_DrawTranslatedColumnLow` (function, line 51) `void R_DrawTranslatedColumnLow (void);`
  - `R_VideoErase` (function, line 54) `void R_VideoErase ( unsigned ofs, int count );`
  - `R_DrawSpan` (function, line 78) `void R_DrawSpan (void);`
  - `R_DrawSpanLow` (function, line 81) `void R_DrawSpanLow (void);`
  - `R_InitBuffer` (function, line 85) `void R_InitBuffer ( int width, int height );`
  - `R_InitTranslationTables` (function, line 92) `void R_InitTranslationTables (void);`
  - `R_FillBackScreen` (function, line 97) `void R_FillBackScreen (void);`
  - `R_DrawViewBorder` (function, line 100) `void R_DrawViewBorder (void);`
  - `dc_colormap` (variable, line 26) `extern lighttable_t* dc_colormap;`
  - `dc_x` (variable, line 27) `extern int dc_x;`
  - `dc_yl` (variable, line 28) `extern int dc_yl;`
  - `dc_yh` (variable, line 29) `extern int dc_yh;`
  - `dc_iscale` (variable, line 30) `extern fixed_t dc_iscale;`
  - `dc_texturemid` (variable, line 31) `extern fixed_t dc_texturemid;`
  - `dc_source` (variable, line 34) `extern byte* dc_source;`
  - `ds_y` (variable, line 58) `extern int ds_y;`
  - `ds_x1` (variable, line 59) `extern int ds_x1;`
  - `ds_x2` (variable, line 60) `extern int ds_x2;`
  - `ds_colormap` (variable, line 62) `extern lighttable_t* ds_colormap;`
  - `ds_xfrac` (variable, line 64) `extern fixed_t ds_xfrac;`
  - `ds_yfrac` (variable, line 65) `extern fixed_t ds_yfrac;`
  - `ds_xstep` (variable, line 66) `extern fixed_t ds_xstep;`
  - `ds_ystep` (variable, line 67) `extern fixed_t ds_ystep;`
  - `ds_source` (variable, line 70) `extern byte* ds_source;`
  - `translationtables` (variable, line 72) `extern byte* translationtables;`
  - `dc_translation` (variable, line 73) `extern byte* dc_translation;`
  - `__R_DRAW__` (macro, line 21) `#define __R_DRAW__`
- Imported by: `progs/doomgeneric/hu_lib.c`, `progs/doomgeneric/r_local.h`

## progs/doomgeneric/r_local.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__R_LOCAL__` (macro, line 21) `#define __R_LOCAL__`
- Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/r_bsp.h`, `progs/doomgeneric/r_data.h`, `progs/doomgeneric/r_draw.h`, `progs/doomgeneric/r_main.h`, `progs/doomgeneric/r_plane.h`, `progs/doomgeneric/r_segs.h`, `progs/doomgeneric/r_things.h`, `progs/doomgeneric/tables.h`
- Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/hu_lib.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/r_data.c`, `progs/doomgeneric/r_draw.c`, `progs/doomgeneric/r_main.c`, `progs/doomgeneric/r_plane.c`, `progs/doomgeneric/r_segs.c`, `progs/doomgeneric/r_things.c`, `progs/doomgeneric/st_lib.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/wi_stuff.c`, `progs/quake2generic/q2generic_minios.c`

## progs/doomgeneric/r_main.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `R_AddPointToBox` (function, line 123) `void
R_AddPointToBox
( int		x,
  int		y,
  fixed_t*	box )`
  - `R_PointOnSide` (function, line 146) `int
R_PointOnSide
( fixed_t	x,
  fixed_t	y,
  node_t*	node )`
  - `R_PointOnSegSide` (function, line 199) `int
R_PointOnSegSide
( fixed_t	x,
  fixed_t	y,
  seg_t*	line )`
  - `R_PointToAngle` (function, line 276) `angle_t
R_PointToAngle
( fixed_t	x,
  fixed_t	y )`
  - `R_PointToAngle2` (function, line 362) `angle_t
R_PointToAngle2
( fixed_t	x1,
  fixed_t	y1,
  fixed_t	x2,
  fixed_t	y2 )`
  - `R_PointToDist` (function, line 376) `fixed_t
R_PointToDist
( fixed_t	x,
  fixed_t	y )`
  - `R_InitPointToAngle` (function, line 422) `void R_InitPointToAngle (void)`
  - `R_ScaleFromGlobalAngle` (function, line 449) `fixed_t R_ScaleFromGlobalAngle (angle_t visangle)`
  - `R_InitTables` (function, line 505) `void R_InitTables (void)`
  - `R_InitTextureMapping` (function, line 540) `void R_InitTextureMapping (void)`
  - `R_InitLightTables` (function, line 610) `void R_InitLightTables (void)`
  - `R_SetViewSize` (function, line 654) `void
R_SetViewSize
( int		blocks,
  int		detail )`
  - `R_ExecuteSetViewSize` (function, line 667) `void R_ExecuteSetViewSize (void)`
  - `R_Init` (function, line 767) `void R_Init (void)`
  - `R_PointInSubsector` (function, line 794) `subsector_t*
R_PointInSubsector
( fixed_t	x,
  fixed_t	y )`
  - `R_SetupFrame` (function, line 823) `void R_SetupFrame (player_t* player)`
  - `R_RenderPlayerView` (function, line 863) `void R_RenderPlayerView (player_t* player)`
  - `walllights` (variable, line 54) `extern lighttable_t** walllights;`
  - `FIELDOFVIEW` (macro, line 43) `#define FIELDOFVIEW`
  - `DISTMAP` (macro, line 608) `#define DISTMAP`
- Depends on: `progs/doomgeneric/d_loop.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/m_bbox.h`, `progs/doomgeneric/m_menu.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/r_sky.h`

## progs/doomgeneric/r_main.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `void` (function, line 92) `extern void (*colfunc) (void);`
  - `R_PointOnSide` (function, line 103) `int R_PointOnSide ( fixed_t x, fixed_t y, node_t* node );`
  - `R_PointOnSegSide` (function, line 109) `int R_PointOnSegSide ( fixed_t x, fixed_t y, seg_t* line );`
  - `R_PointToAngle` (function, line 115) `angle_t R_PointToAngle ( fixed_t x, fixed_t y );`
  - `R_PointToAngle2` (function, line 120) `angle_t R_PointToAngle2 ( fixed_t x1, fixed_t y1, fixed_t x2, fixed_t y2 );`
  - `R_PointToDist` (function, line 127) `fixed_t R_PointToDist ( fixed_t x, fixed_t y );`
  - `R_ScaleFromGlobalAngle` (function, line 132) `fixed_t R_ScaleFromGlobalAngle (angle_t visangle);`
  - `R_PointInSubsector` (function, line 135) `subsector_t* R_PointInSubsector ( fixed_t x, fixed_t y );`
  - `R_AddPointToBox` (function, line 140) `void R_AddPointToBox ( int x, int y, fixed_t* box );`
  - `R_RenderPlayerView` (function, line 152) `void R_RenderPlayerView (player_t *player);`
  - `R_Init` (function, line 155) `void R_Init (void);`
  - `R_SetViewSize` (function, line 158) `void R_SetViewSize (int blocks, int detail);`
  - `viewcos` (variable, line 32) `extern fixed_t viewcos;`
  - `viewsin` (variable, line 33) `extern fixed_t viewsin;`
  - `viewwindowx` (variable, line 35) `extern int viewwindowx;`
  - `viewwindowy` (variable, line 36) `extern int viewwindowy;`
  - `centerx` (variable, line 40) `extern int centerx;`
  - `centery` (variable, line 41) `extern int centery;`
  - `centerxfrac` (variable, line 43) `extern fixed_t centerxfrac;`
  - `centeryfrac` (variable, line 44) `extern fixed_t centeryfrac;`
  - `projection` (variable, line 45) `extern fixed_t projection;`
  - `validcount` (variable, line 47) `extern int validcount;`
  - `linecount` (variable, line 49) `extern int linecount;`
  - `loopcount` (variable, line 50) `extern int loopcount;`
  - `scalelightfixed` (variable, line 70) `extern lighttable_t* scalelightfixed[MAXLIGHTSCALE];`
  - `extralight` (variable, line 73) `extern int extralight;`
  - `fixedcolormap` (variable, line 74) `extern lighttable_t* fixedcolormap;`
  - `detailshift` (variable, line 85) `extern int detailshift;`
  - `__R_MAIN__` (macro, line 21) `#define __R_MAIN__`
  - `LIGHTLEVELS` (macro, line 61) `#define LIGHTLEVELS`
  - `LIGHTSEGSHIFT` (macro, line 62) `#define LIGHTSEGSHIFT`
  - `MAXLIGHTSCALE` (macro, line 64) `#define MAXLIGHTSCALE`
  - `LIGHTSCALESHIFT` (macro, line 65) `#define LIGHTSCALESHIFT`
  - `MAXLIGHTZ` (macro, line 66) `#define MAXLIGHTZ`
  - `LIGHTZSHIFT` (macro, line 67) `#define LIGHTZSHIFT`
  - `NUMCOLORMAPS` (macro, line 79) `#define NUMCOLORMAPS`
- Depends on: `progs/doomgeneric/d_player.h`, `progs/doomgeneric/r_data.h`
- Imported by: `progs/doomgeneric/r_bsp.c`, `progs/doomgeneric/r_local.h`

## progs/doomgeneric/r_plane.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `R_InitPlanes` (function, line 94) `void R_InitPlanes (void)`
  - `R_MapPlane` (function, line 114) `void
R_MapPlane
( int		y,
  int		x1,
  int		x2 )`
  - `R_ClearPlanes` (function, line 178) `void R_ClearPlanes (void)`
  - `R_FindPlane` (function, line 211) `visplane_t*
R_FindPlane
( fixed_t	height,
  int		picnum,
  int		lightlevel )`
  - `R_CheckPlane` (function, line 259) `visplane_t*
R_CheckPlane
( visplane_t*	pl,
  int		start,
  int		stop )`
  - `R_MakeSpans` (function, line 324) `void
R_MakeSpans
( int		x,
  int		t1,
  int		b1,
  int		t2,
  int		b2 )`
  - `R_DrawPlanes` (function, line 360) `void R_DrawPlanes (void)`
  - `MAXVISPLANES` (macro, line 45) `#define MAXVISPLANES`
  - `MAXOPENINGS` (macro, line 52) `#define MAXOPENINGS`
- Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/r_sky.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/r_plane.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `R_InitPlanes` (function, line 43) `void R_InitPlanes (void);`
  - `R_ClearPlanes` (function, line 44) `void R_ClearPlanes (void);`
  - `R_MapPlane` (function, line 47) `void R_MapPlane ( int y, int x1, int x2 );`
  - `R_MakeSpans` (function, line 53) `void R_MakeSpans ( int x, int t1, int b1, int t2, int b2 );`
  - `R_DrawPlanes` (function, line 60) `void R_DrawPlanes (void);`
  - `R_FindPlane` (function, line 63) `visplane_t* R_FindPlane ( fixed_t height, int picnum, int lightlevel );`
  - `R_CheckPlane` (function, line 69) `visplane_t* R_CheckPlane ( visplane_t* pl, int start, int stop );`
  - `lastopening` (variable, line 29) `extern short* lastopening;`
  - `floorfunc` (variable, line 34) `extern planefunction_t floorfunc;`
  - `ceilingfunc_t` (variable, line 35) `extern planefunction_t ceilingfunc_t;`
  - `floorclip` (variable, line 37) `extern short floorclip[SCREENWIDTH];`
  - `ceilingclip` (variable, line 38) `extern short ceilingclip[SCREENWIDTH];`
  - `yslope` (variable, line 40) `extern fixed_t yslope[SCREENHEIGHT];`
  - `distscale` (variable, line 41) `extern fixed_t distscale[SCREENWIDTH];`
  - `__R_PLANE__` (macro, line 21) `#define __R_PLANE__`
- Depends on: `progs/doomgeneric/r_data.h`
- Imported by: `progs/doomgeneric/r_bsp.c`, `progs/doomgeneric/r_local.h`

## progs/doomgeneric/r_segs.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `R_RenderMaskedSegRange` (function, line 96) `void
R_RenderMaskedSegRange
( drawseg_t*	ds,
  int		x1,
  int		x2 )`
  - `R_RenderSegLoop` (function, line 199) `void R_RenderSegLoop (void)`
  - `R_StoreWallRange` (function, line 372) `void
R_StoreWallRange
( int	start,
  int	stop )`
  - `HEIGHTBITS` (macro, line 196) `#define HEIGHTBITS`
  - `HEIGHTUNIT` (macro, line 197) `#define HEIGHTUNIT`
- Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/r_sky.h`

## progs/doomgeneric/r_segs.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `R_RenderMaskedSegRange` (function, line 27) `void R_RenderMaskedSegRange ( drawseg_t* ds, int x1, int x2 );`
  - `__R_SEGS__` (macro, line 21) `#define __R_SEGS__`
- Imported by: `progs/doomgeneric/r_local.h`

## progs/doomgeneric/r_sky.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `R_InitSkyMap` (function, line 47) `void R_InitSkyMap (void)`
- Depends on: `progs/doomgeneric/m_fixed.h`, `progs/doomgeneric/r_data.h`, `progs/doomgeneric/r_sky.h`

## progs/doomgeneric/r_sky.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `R_InitSkyMap` (function, line 35) `void R_InitSkyMap (void);`
  - `skytexture` (variable, line 31) `extern int skytexture;`
  - `skytexturemid` (variable, line 32) `extern int skytexturemid;`
  - `__R_SKY__` (macro, line 21) `#define __R_SKY__`
  - `SKYFLATNAME` (macro, line 26) `#define			SKYFLATNAME`
  - `ANGLETOSKYSHIFT` (macro, line 29) `#define ANGLETOSKYSHIFT`
- Imported by: `progs/doomgeneric/g_game.c`, `progs/doomgeneric/r_data.c`, `progs/doomgeneric/r_main.c`, `progs/doomgeneric/r_plane.c`, `progs/doomgeneric/r_segs.c`, `progs/doomgeneric/r_sky.c`

## progs/doomgeneric/r_state.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `textureheight` (variable, line 38) `extern fixed_t* textureheight;`
  - `spritewidth` (variable, line 41) `extern fixed_t* spritewidth;`
  - `spriteoffset` (variable, line 43) `extern fixed_t* spriteoffset;`
  - `spritetopoffset` (variable, line 44) `extern fixed_t* spritetopoffset;`
  - `colormaps` (variable, line 46) `extern lighttable_t* colormaps;`
  - `viewwidth` (variable, line 48) `extern int viewwidth;`
  - `scaledviewwidth` (variable, line 49) `extern int scaledviewwidth;`
  - `viewheight` (variable, line 50) `extern int viewheight;`
  - `firstflat` (variable, line 52) `extern int firstflat;`
  - `flattranslation` (variable, line 55) `extern int* flattranslation;`
  - `texturetranslation` (variable, line 56) `extern int* texturetranslation;`
  - `firstspritelump` (variable, line 60) `extern int firstspritelump;`
  - `lastspritelump` (variable, line 61) `extern int lastspritelump;`
  - `numspritelumps` (variable, line 62) `extern int numspritelumps;`
  - `numsprites` (variable, line 69) `extern int numsprites;`
  - `sprites` (variable, line 70) `extern spritedef_t* sprites;`
  - `numvertexes` (variable, line 72) `extern int numvertexes;`
  - `vertexes` (variable, line 73) `extern vertex_t* vertexes;`
  - `numsegs` (variable, line 75) `extern int numsegs;`
  - `segs` (variable, line 76) `extern seg_t* segs;`
  - `numsectors` (variable, line 78) `extern int numsectors;`
  - `sectors` (variable, line 79) `extern sector_t* sectors;`
  - `numsubsectors` (variable, line 81) `extern int numsubsectors;`
  - `subsectors` (variable, line 82) `extern subsector_t* subsectors;`
  - `numnodes` (variable, line 84) `extern int numnodes;`
  - `nodes` (variable, line 85) `extern node_t* nodes;`
  - `numlines` (variable, line 87) `extern int numlines;`
  - `lines` (variable, line 88) `extern line_t* lines;`
  - `numsides` (variable, line 90) `extern int numsides;`
  - `sides` (variable, line 91) `extern side_t* sides;`
  - `viewx` (variable, line 97) `extern fixed_t viewx;`
  - `viewy` (variable, line 98) `extern fixed_t viewy;`
  - `viewz` (variable, line 99) `extern fixed_t viewz;`
  - `viewangle` (variable, line 101) `extern angle_t viewangle;`
  - `viewplayer` (variable, line 102) `extern player_t* viewplayer;`
  - `clipangle` (variable, line 106) `extern angle_t clipangle;`
  - `viewangletox` (variable, line 108) `extern int viewangletox[FINEANGLES/2];`
  - `xtoviewangle` (variable, line 109) `extern angle_t xtoviewangle[SCREENWIDTH+1];`
  - `rw_distance` (variable, line 112) `extern fixed_t rw_distance;`
  - `rw_normalangle` (variable, line 113) `extern angle_t rw_normalangle;`
  - `rw_angle1` (variable, line 118) `extern int rw_angle1;`
  - `sscount` (variable, line 121) `extern int sscount;`
  - `floorplane` (variable, line 123) `extern visplane_t* floorplane;`
  - `ceilingplane` (variable, line 124) `extern visplane_t* ceilingplane;`
  - `__R_STATE__` (macro, line 21) `#define __R_STATE__`
- Depends on: `progs/doomgeneric/d_player.h`, `progs/doomgeneric/r_data.h`
- Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/f_finale.c`, `progs/doomgeneric/p_ceilng.c`, `progs/doomgeneric/p_doors.c`, `progs/doomgeneric/p_enemy.c`, `progs/doomgeneric/p_floor.c`, `progs/doomgeneric/p_lights.c`, `progs/doomgeneric/p_map.c`, `progs/doomgeneric/p_maputl.c`, `progs/doomgeneric/p_plats.c`, `progs/doomgeneric/p_saveg.c`, `progs/doomgeneric/p_sight.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/p_switch.c`, `progs/doomgeneric/p_telept.c`, `progs/doomgeneric/r_bsp.c`, `progs/doomgeneric/r_data.h`

## progs/doomgeneric/r_things.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `maskdraw_t` (struct, line 48)
  - `R_InstallSpriteLump` (function, line 100) `void
R_InstallSpriteLump
( int		lump,
  unsigned	frame,
  unsigned	rotation,
  boolean	flipped )`
  - `R_InitSpriteDefs` (function, line 171) `void R_InitSpriteDefs (char** namelist)`
  - `R_InitSprites` (function, line 291) `void R_InitSprites (char** namelist)`
  - `R_ClearSprites` (function, line 309) `void R_ClearSprites (void)`
  - `R_NewVisSprite` (function, line 320) `vissprite_t* R_NewVisSprite (void)`
  - `R_DrawMaskedColumn` (function, line 343) `void R_DrawMaskedColumn (column_t* column)`
  - `R_DrawVisSprite` (function, line 389) `void
R_DrawVisSprite
( vissprite_t*		vis,
  int			x1,
  int			x2 )`
  - `R_ProjectSprite` (function, line 444) `void R_ProjectSprite (mobj_t* thing)`
  - `R_AddSprites` (function, line 605) `void R_AddSprites (sector_t* sec)`
  - `R_DrawPSprite` (function, line 638) `void R_DrawPSprite (pspdef_t* psp)`
  - `R_DrawPlayerSprites` (function, line 738) `void R_DrawPlayerSprites (void)`
  - `R_SortVisSprites` (function, line 779) `void R_SortVisSprites (void)`
  - `R_DrawSprite` (function, line 837) `void R_DrawSprite (vissprite_t* spr)`
  - `R_DrawMasked` (function, line 951) `void R_DrawMasked (void)`
  - `MINZ` (macro, line 40) `#define MINZ`
  - `BASEYCENTER` (macro, line 41) `#define BASEYCENTER`
- Depends on: `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/r_things.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `R_DrawMaskedColumn` (function, line 46) `void R_DrawMaskedColumn (column_t* column);`
  - `R_SortVisSprites` (function, line 49) `void R_SortVisSprites (void);`
  - `R_AddSprites` (function, line 51) `void R_AddSprites (sector_t* sec);`
  - `R_AddPSprites` (function, line 52) `void R_AddPSprites (void);`
  - `R_DrawSprites` (function, line 53) `void R_DrawSprites (void);`
  - `R_InitSprites` (function, line 54) `void R_InitSprites (char** namelist);`
  - `R_ClearSprites` (function, line 55) `void R_ClearSprites (void);`
  - `R_DrawMasked` (function, line 56) `void R_DrawMasked (void);`
  - `R_ClipVisSprite` (function, line 59) `void R_ClipVisSprite ( vissprite_t* vis, int xl, int xh );`
  - `vissprites` (variable, line 27) `extern vissprite_t vissprites[MAXVISSPRITES];`
  - `vissprite_p` (variable, line 28) `extern vissprite_t* vissprite_p;`
  - `vsprsortedhead` (variable, line 29) `extern vissprite_t vsprsortedhead;`
  - `negonearray` (variable, line 33) `extern short negonearray[SCREENWIDTH];`
  - `screenheightarray` (variable, line 34) `extern short screenheightarray[SCREENWIDTH];`
  - `mfloorclip` (variable, line 37) `extern short* mfloorclip;`
  - `mceilingclip` (variable, line 38) `extern short* mceilingclip;`
  - `spryscale` (variable, line 39) `extern fixed_t spryscale;`
  - `sprtopscreen` (variable, line 40) `extern fixed_t sprtopscreen;`
  - `pspritescale` (variable, line 42) `extern fixed_t pspritescale;`
  - `pspriteiscale` (variable, line 43) `extern fixed_t pspriteiscale;`
  - `__R_THINGS__` (macro, line 21) `#define __R_THINGS__`
  - `MAXVISSPRITES` (macro, line 25) `#define MAXVISSPRITES`
- Imported by: `progs/doomgeneric/r_bsp.c`, `progs/doomgeneric/r_local.h`

## progs/doomgeneric/s_sound.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `channel_t` (struct, line 66)
  - `S_Init` (function, line 114) `void S_Init(int sfxVolume, int musicVolume)`
  - `S_Shutdown` (function, line 146) `void S_Shutdown(void)`
  - `S_StopChannel` (function, line 152) `static void S_StopChannel(int cnum)`
  - `S_Start` (function, line 191) `void S_Start(void)`
  - `S_StopSound` (function, line 243) `void S_StopSound(mobj_t *origin)`
  - `S_GetChannel` (function, line 262) `static int S_GetChannel(mobj_t *origin, sfxinfo_t *sfxinfo)`
  - `S_AdjustSoundParams` (function, line 323) `static int S_AdjustSoundParams(mobj_t *listener, mobj_t *source,
                               i...`
  - `S_StartSound` (function, line 391) `void S_StartSound(void *origin_p, int sfx_id)`
  - `S_PauseSound` (function, line 482) `void S_PauseSound(void)`
  - `S_ResumeSound` (function, line 491) `void S_ResumeSound(void)`
  - `S_UpdateSounds` (function, line 504) `void S_UpdateSounds(mobj_t *listener)`
  - `S_SetMusicVolume` (function, line 571) `void S_SetMusicVolume(int volume)`
  - `S_SetSfxVolume` (function, line 582) `void S_SetSfxVolume(int volume)`
  - `S_StartMusic` (function, line 596) `void S_StartMusic(int m_id)`
  - `S_ChangeMusic` (function, line 601) `void S_ChangeMusic(int musicnum, int looping)`
  - `S_MusicPlaying` (function, line 649) `boolean S_MusicPlaying(void)`
  - `S_StopMusic` (function, line 654) `void S_StopMusic(void)`
  - `S_CLIPPING_DIST` (macro, line 44) `#define S_CLIPPING_DIST`
  - `S_CLOSE_DIST` (macro, line 52) `#define S_CLOSE_DIST`
  - `S_ATTENUATOR` (macro, line 56) `#define S_ATTENUATOR`
  - `S_STEREO_SWING` (macro, line 60) `#define S_STEREO_SWING`
  - `NORM_PITCH` (macro, line 62) `#define NORM_PITCH`
  - `NORM_PRIORITY` (macro, line 63) `#define NORM_PRIORITY`
  - `NORM_SEP` (macro, line 64) `#define NORM_SEP`
- Depends on: `progs/doomgeneric/deh_str.h`, `progs/doomgeneric/doomfeatures.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_sound.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/s_sound.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `S_Init` (function, line 32) `void S_Init(int sfxVolume, int musicVolume);`
  - `S_Shutdown` (function, line 37) `void S_Shutdown(void);`
  - `S_Start` (function, line 47) `void S_Start(void);`
  - `S_StartSound` (function, line 54) `void S_StartSound(void *origin, int sound_id);`
  - `S_StopSound` (function, line 57) `void S_StopSound(mobj_t *origin);`
  - `S_StartMusic` (function, line 61) `void S_StartMusic(int music_id);`
  - `S_ChangeMusic` (function, line 65) `void S_ChangeMusic(int music_id, int looping);`
  - `S_StopMusic` (function, line 71) `void S_StopMusic(void);`
  - `S_PauseSound` (function, line 74) `void S_PauseSound(void);`
  - `S_ResumeSound` (function, line 75) `void S_ResumeSound(void);`
  - `S_UpdateSounds` (function, line 81) `void S_UpdateSounds(mobj_t *listener);`
  - `S_SetMusicVolume` (function, line 83) `void S_SetMusicVolume(int volume);`
  - `S_SetSfxVolume` (function, line 84) `void S_SetSfxVolume(int volume);`
  - `snd_channels` (variable, line 86) `extern int snd_channels;`
  - `__S_SOUND__` (macro, line 21) `#define __S_SOUND__`
- Depends on: `progs/doomgeneric/p_mobj.h`, `progs/doomgeneric/sounds.h`
- Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/f_finale.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/p_ceilng.c`, `progs/doomgeneric/p_doors.c`, `progs/doomgeneric/p_enemy.c`, `progs/doomgeneric/p_floor.c`, `progs/doomgeneric/p_inter.c`, `progs/doomgeneric/p_map.c`, `progs/doomgeneric/p_mobj.c`, `progs/doomgeneric/p_plats.c`, `progs/doomgeneric/p_pspr.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/p_switch.c`, `progs/doomgeneric/p_telept.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/wi_stuff.c`

## progs/doomgeneric/sha1.c
- Layer: utility
- Doc: sha1.c - SHA1 hash function
- Language: c
- Symbols:
  - `SHA1_Init` (function, line 40) `void SHA1_Init(sha1_context_t *hd)`
  - `Transform` (function, line 55) `static void Transform(sha1_context_t *hd, byte *data)`
  - `SHA1_Update` (function, line 198) `void SHA1_Update(sha1_context_t *hd, byte *inbuf, size_t inlen)`
  - `SHA1_Final` (function, line 238) `void SHA1_Final(sha1_digest_t digest, sha1_context_t *hd)`
  - `SHA1_UpdateInt32` (function, line 303) `void SHA1_UpdateInt32(sha1_context_t *context, unsigned int val)`
  - `SHA1_UpdateString` (function, line 315) `void SHA1_UpdateString(sha1_context_t *context, char *str)`
  - `K1` (macro, line 84) `#define K1`
  - `K2` (macro, line 85) `#define K2`
  - `K3` (macro, line 86) `#define K3`
  - `K4` (macro, line 87) `#define K4`
  - `F1` (macro, line 88) `#define F1(x,y,z)`
  - `F2` (macro, line 89) `#define F2(x,y,z)`
  - `F3` (macro, line 90) `#define F3(x,y,z)`
  - `F4` (macro, line 91) `#define F4(x,y,z)`
  - `rol` (macro, line 93) `#define rol(x,n)`
  - `M` (macro, line 95) `#define M(i)`
  - `R` (macro, line 99) `#define R(a,b,c,d,e,f,k,m)`
  - `X` (macro, line 288) `#define X(a)`
  - `X` (macro, line 290) `#define X(a)`
- Depends on: `kernel/string.c`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/sha1.h`

## progs/doomgeneric/sha1.h
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `sha1_context_s` (struct, line 26)
  - `sha1_context_t` (type_alias, line 22) `typedef struct sha1_context_s sha1_context_t;`
  - `sha1_digest_t` (type_alias, line 24) `typedef byte sha1_digest_t[20];`
  - `SHA1_Init` (function, line 33) `void SHA1_Init(sha1_context_t *context);`
  - `SHA1_Update` (function, line 34) `void SHA1_Update(sha1_context_t *context, byte *buf, size_t len);`
  - `SHA1_Final` (function, line 35) `void SHA1_Final(sha1_digest_t digest, sha1_context_t *context);`
  - `SHA1_UpdateInt32` (function, line 36) `void SHA1_UpdateInt32(sha1_context_t *context, unsigned int val);`
  - `SHA1_UpdateString` (function, line 37) `void SHA1_UpdateString(sha1_context_t *context, char *str);`
  - `__SHA1_H__` (macro, line 19) `#define __SHA1_H__`
- Depends on: `progs/doomgeneric/doomtype.h`
- Imported by: `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/net_client.h`, `progs/doomgeneric/net_defs.h`, `progs/doomgeneric/sha1.c`, `progs/doomgeneric/w_checksum.c`

## progs/doomgeneric/sounds.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `MUSIC` (macro, line 31) `#define MUSIC(name)`
  - `SOUND` (macro, line 111) `#define SOUND(name, priority)`
  - `SOUND_LINK` (macro, line 113) `#define SOUND_LINK(name, priority, link_id, pitch, volume)`
- Depends on: `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/sounds.h`

## progs/doomgeneric/sounds.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `S_sfx` (variable, line 26) `extern sfxinfo_t S_sfx[];`
  - `S_music` (variable, line 29) `extern musicinfo_t S_music[];`
  - `__SOUNDS__` (macro, line 21) `#define __SOUNDS__`
- Depends on: `progs/doomgeneric/i_sound.h`
- Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/f_finale.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/info.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/p_ceilng.c`, `progs/doomgeneric/p_doors.c`, `progs/doomgeneric/p_enemy.c`, `progs/doomgeneric/p_floor.c`, `progs/doomgeneric/p_inter.c`, `progs/doomgeneric/p_map.c`, `progs/doomgeneric/p_mobj.c`, `progs/doomgeneric/p_plats.c`, `progs/doomgeneric/p_pspr.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/p_switch.c`, `progs/doomgeneric/p_telept.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/wi_stuff.c`

## progs/doomgeneric/st_lib.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `STlib_init` (function, line 51) `void STlib_init(void)`
  - `STlib_initNum` (function, line 59) `void
STlib_initNum
( st_number_t*		n,
  int			x,
  int			y,
  patch_t**		pl,
  int*			num,
  bool...`
  - `STlib_drawNum` (function, line 84) `void
STlib_drawNum
( st_number_t*	n,
  boolean	refresh )`
  - `STlib_updateNum` (function, line 146) `void
STlib_updateNum
( st_number_t*		n,
  boolean		refresh )`
  - `STlib_initPercent` (function, line 156) `void
STlib_initPercent
( st_percent_t*		p,
  int			x,
  int			y,
  patch_t**		pl,
  int*			num,
 ...`
  - `STlib_updatePercent` (function, line 173) `void
STlib_updatePercent
( st_percent_t*		per,
  int			refresh )`
  - `STlib_initMultIcon` (function, line 186) `void
STlib_initMultIcon
( st_multicon_t*	i,
  int			x,
  int			y,
  patch_t**		il,
  int*			inum,...`
  - `STlib_updateMultIcon` (function, line 205) `void
STlib_updateMultIcon
( st_multicon_t*	mi,
  boolean		refresh )`
  - `STlib_initBinIcon` (function, line 236) `void
STlib_initBinIcon
( st_binicon_t*		b,
  int			x,
  int			y,
  patch_t*		i,
  boolean*		val,
...`
  - `STlib_updateBinIcon` (function, line 255) `void
STlib_updateBinIcon
( st_binicon_t*		bi,
  boolean		refresh )`
  - `automapactive` (variable, line 40) `extern boolean automapactive;`
- Depends on: `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/st_lib.h`, `progs/doomgeneric/st_stuff.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/st_lib.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `st_number_t` (struct, line 32)
  - `st_percent_t` (struct, line 64)
  - `st_multicon_t` (struct, line 77)
  - `st_binicon_t` (struct, line 106)
  - `STlib_init` (function, line 138) `void STlib_init(void);`
  - `STlib_initNum` (function, line 144) `void STlib_initNum ( st_number_t* n, int x, int y, patch_t** pl, int* num, boolean* on, int width );`
  - `STlib_updateNum` (function, line 154) `void STlib_updateNum ( st_number_t* n, boolean refresh );`
  - `STlib_initPercent` (function, line 161) `void STlib_initPercent ( st_percent_t* p, int x, int y, patch_t** pl, int* num, boolean* on, patch_t* percent );`
  - `STlib_updatePercent` (function, line 172) `void STlib_updatePercent ( st_percent_t* per, int refresh );`
  - `STlib_initMultIcon` (function, line 179) `void STlib_initMultIcon ( st_multicon_t* mi, int x, int y, patch_t** il, int* inum, boolean* on );`
  - `STlib_updateMultIcon` (function, line 189) `void STlib_updateMultIcon ( st_multicon_t* mi, boolean refresh );`
  - `STlib_initBinIcon` (function, line 196) `void STlib_initBinIcon ( st_binicon_t* b, int x, int y, patch_t* i, boolean* val, boolean* on );`
  - `STlib_updateBinIcon` (function, line 205) `void STlib_updateBinIcon ( st_binicon_t* bi, boolean refresh );`
  - `__STLIB__` (macro, line 20) `#define __STLIB__`
- Depends on: `progs/doomgeneric/r_defs.h`
- Imported by: `progs/doomgeneric/st_lib.c`, `progs/doomgeneric/st_stuff.c`

## progs/doomgeneric/st_stuff.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `SlopeDiv` (function, line 41) `int SlopeDiv(unsigned int num, unsigned int den)`
- Depends on: `progs/doomgeneric/tables.h`

## progs/doomgeneric/tables.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software Copyright(C) 2005-2014 Simon Howard  This
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `column_t` (type_alias, line 47) `typedef post_t column_t;`
  - `V_PATCH_H` (macro, line 21) `#define V_PATCH_H`
- Imported by: `progs/doomgeneric/r_defs.h`, `progs/doomgeneric/v_video.h`

## progs/doomgeneric/v_video.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software Copyright(C) 2005-2014 Simon Howard  This
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `GetFileNumber` (function, line 31) `static int GetFileNumber(wad_file_t *handle)`
  - `ChecksumAddLump` (function, line 57) `static void ChecksumAddLump(sha1_context_t *sha1_context, lumpinfo_t *lump)`
  - `W_Checksum` (function, line 68) `void W_Checksum(sha1_digest_t digest)`
- Depends on: `kernel/string.c`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/sha1.h`, `progs/doomgeneric/w_checksum.h`, `progs/doomgeneric/w_wad.h`

## progs/doomgeneric/w_checksum.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `W_Checksum` (function, line 24) `extern void W_Checksum(sha1_digest_t digest);`
  - `W_CHECKSUM_H` (macro, line 20) `#define W_CHECKSUM_H`
- Depends on: `progs/doomgeneric/doomtype.h`
- Imported by: `progs/doomgeneric/d_net.c`, `progs/doomgeneric/w_checksum.c`

## progs/doomgeneric/w_file.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `W_ParseCommandLine` (function, line 30) `boolean W_ParseCommandLine(void)`
- Depends on: `progs/doomgeneric/d_iwad.h`, `progs/doomgeneric/doomfeatures.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/w_main.h`, `progs/doomgeneric/w_merge.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/w_main.h
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `W_MAIN_H` (macro, line 19) `#define W_MAIN_H`
- Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/w_main.c`

## progs/doomgeneric/w_merge.h
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
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
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
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

## progs/doomgeneric/wi_stuff.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `point_t` (struct, line 117)
  - `anim_t` (struct, line 129)
  - `WI_slamBackground` (function, line 402) `void WI_slamBackground(void)`
  - `WI_Responder` (function, line 409) `boolean WI_Responder(event_t* ev)`
  - `WI_drawLF` (function, line 416) `void WI_drawLF(void)`
  - `WI_drawEL` (function, line 452) `void WI_drawEL(void)`
  - `WI_drawOnLnode` (function, line 471) `void
WI_drawOnLnode
( int		n,
  patch_t*	c[] )`
  - `WI_initAnimatedBack` (function, line 519) `void WI_initAnimatedBack(void)`
  - `WI_updateAnimatedBack` (function, line 548) `void WI_updateAnimatedBack(void)`
  - `WI_drawAnimatedBack` (function, line 599) `void WI_drawAnimatedBack(void)`
  - `WI_drawNum` (function, line 628) `int
WI_drawNum
( int		x,
  int		y,
  int		n,
  int		digits )`
  - `WI_drawPercent` (function, line 685) `void
WI_drawPercent
( int		x,
  int		y,
  int		p )`
  - `WI_drawTime` (function, line 704) `void
WI_drawTime
( int		x,
  int		y,
  int		t )`
  - `WI_End` (function, line 740) `void WI_End(void)`
  - `WI_initNoState` (function, line 746) `void WI_initNoState(void)`
  - `WI_updateNoState` (function, line 753) `void WI_updateNoState(void)`
  - `WI_initShowNextLoc` (function, line 772) `void WI_initShowNextLoc(void)`
  - `WI_updateShowNextLoc` (function, line 781) `void WI_updateShowNextLoc(void)`
  - `WI_drawShowNextLoc` (function, line 791) `void WI_drawShowNextLoc(void)`
  - `WI_drawNoState` (function, line 832) `void WI_drawNoState(void)`
  - `WI_fragSum` (function, line 838) `int WI_fragSum(int playernum)`
  - `WI_initDeathmatchStats` (function, line 869) `void WI_initDeathmatchStats(void)`
  - `WI_updateDeathmatchStats` (function, line 898) `void WI_updateDeathmatchStats(void)`
  - `WI_drawDeathmatchStats` (function, line 1001) `void WI_drawDeathmatchStats(void)`
  - `WI_initNetgameStats` (function, line 1089) `void WI_initNetgameStats(void)`
  - `WI_updateNetgameStats` (function, line 1117) `void WI_updateNetgameStats(void)`
  - `WI_drawNetgameStats` (function, line 1272) `void WI_drawNetgameStats(void)`
  - `WI_initStats` (function, line 1329) `void WI_initStats(void)`
  - `WI_updateStats` (function, line 1341) `void WI_updateStats(void)`
  - `WI_drawStats` (function, line 1447) `void WI_drawStats(void)`
  - `WI_checkForAccelerate` (function, line 1481) `void WI_checkForAccelerate(void)`
  - `WI_Ticker` (function, line 1514) `void WI_Ticker(void)`
  - `WI_loadUnloadData` (function, line 1554) `static void WI_loadUnloadData(load_callback_t callback)`
  - `WI_loadCallback` (function, line 1704) `static void WI_loadCallback(char *name, patch_t **variable)`
  - `WI_loadData` (function, line 1709) `void WI_loadData(void)`
  - `WI_unloadCallback` (function, line 1735) `static void WI_unloadCallback(char *name, patch_t **variable)`
  - `WI_unloadData` (function, line 1741) `void WI_unloadData(void)`
  - `WI_Drawer` (function, line 1752) `void WI_Drawer (void)`
  - `WI_initVariables` (function, line 1776) `void WI_initVariables(wbstartstruct_t* wbstartstruct)`
  - `WI_Start` (function, line 1818) `void WI_Start(wbstartstruct_t* wbstartstruct)`
  - `NUMEPISODES` (macro, line 61) `#define NUMEPISODES`
  - `NUMMAPS` (macro, line 62) `#define NUMMAPS`
  - `WI_TITLEY` (macro, line 75) `#define WI_TITLEY`
  - `WI_SPACINGY` (macro, line 76) `#define WI_SPACINGY`
  - `SP_STATSX` (macro, line 79) `#define SP_STATSX`
  - `SP_STATSY` (macro, line 80) `#define SP_STATSY`
  - `SP_TIMEX` (macro, line 82) `#define SP_TIMEX`
  - `SP_TIMEY` (macro, line 83) `#define SP_TIMEY`
  - `NG_STATSY` (macro, line 87) `#define NG_STATSY`
  - `NG_STATSX` (macro, line 88) `#define NG_STATSX`
  - `NG_SPACINGX` (macro, line 90) `#define NG_SPACINGX`
  - `DM_MATRIXX` (macro, line 94) `#define DM_MATRIXX`
  - `DM_MATRIXY` (macro, line 95) `#define DM_MATRIXY`
  - `DM_SPACINGX` (macro, line 97) `#define DM_SPACINGX`
  - `DM_TOTALSX` (macro, line 99) `#define DM_TOTALSX`
  - `DM_KILLERSX` (macro, line 101) `#define DM_KILLERSX`
  - `DM_KILLERSY` (macro, line 102) `#define DM_KILLERSY`
  - `DM_VICTIMSX` (macro, line 103) `#define DM_VICTIMSX`
  - `DM_VICTIMSY` (macro, line 104) `#define DM_VICTIMSY`
  - `ANIM` (macro, line 222) `#define ANIM(type, period, nanims, x, y, nexttic)`
  - `SP_KILLS` (macro, line 288) `#define SP_KILLS`
  - `SP_ITEMS` (macro, line 289) `#define SP_ITEMS`
  - `SP_SECRET` (macro, line 290) `#define SP_SECRET`
  - `SP_FRAGS` (macro, line 291) `#define SP_FRAGS`
  - `SP_TIME` (macro, line 292) `#define SP_TIME`
  - `SP_PAR` (macro, line 293) `#define SP_PAR`
  - `SP_PAUSE` (macro, line 295) `#define SP_PAUSE`
  - `SHOWNEXTLOCDELAY` (macro, line 298) `#define SHOWNEXTLOCDELAY`
- Depends on: `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/wi_stuff.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/wi_stuff.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `WI_Ticker` (function, line 36) `void WI_Ticker (void);`
  - `WI_Drawer` (function, line 40) `void WI_Drawer (void);`
  - `WI_Start` (function, line 43) `void WI_Start(wbstartstruct_t* wbstartstruct);`
  - `WI_End` (function, line 46) `void WI_End(void);`
  - `__WI_STUFF__` (macro, line 20) `#define __WI_STUFF__`
- Depends on: `progs/doomgeneric/doomdef.h`
- Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/wi_stuff.c`

## progs/doomgeneric/z_zone.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `memblock_s` (struct, line 39)
  - `memzone_t` (struct, line 50)
  - `size` (type_alias, line 38) `typedef struct memblock_s { int size;`
  - `Z_ClearZone` (function, line 71) `void Z_ClearZone (memzone_t* zone)`
  - `Z_Init` (function, line 97) `void Z_Init (void)`
  - `Z_Free` (function, line 126) `void Z_Free (void* ptr)`
  - `Z_Malloc` (function, line 185) `void*
Z_Malloc
( int		size,
  int		tag,
  void*		user )`
  - `Z_FreeTags` (function, line 298) `void
Z_FreeTags
( int		lowtag,
  int		hightag )`
  - `Z_DumpHeap` (function, line 328) `void
Z_DumpHeap
( int		lowtag,
  int		hightag )`
  - `Z_FileDumpHeap` (function, line 367) `void Z_FileDumpHeap (FILE* f)`
  - `Z_CheckHeap` (function, line 400) `void Z_CheckHeap (void)`
  - `Z_ChangeTag2` (function, line 429) `void Z_ChangeTag2(void *ptr, int tag, char *file, int line)`
  - `Z_ChangeUser` (function, line 446) `void Z_ChangeUser(void *ptr, void **user)`
  - `Z_FreeMemory` (function, line 466) `int Z_FreeMemory (void)`
  - `Z_ZoneSize` (function, line 484) `unsigned int Z_ZoneSize(void)`
  - `MEM_ALIGN` (macro, line 36) `#define MEM_ALIGN`
  - `ZONEID` (macro, line 37) `#define ZONEID`
  - `MINFRAGMENT` (macro, line 181) `#define MINFRAGMENT`
- Depends on: `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/z_zone.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `Z_Init` (function, line 53) `void Z_Init (void);`
  - `Z_Malloc` (function, line 54) `void* Z_Malloc (int size, int tag, void *ptr);`
  - `Z_Free` (function, line 55) `void Z_Free (void *ptr);`
  - `Z_FreeTags` (function, line 56) `void Z_FreeTags (int lowtag, int hightag);`
  - `Z_DumpHeap` (function, line 57) `void Z_DumpHeap (int lowtag, int hightag);`
  - `Z_FileDumpHeap` (function, line 58) `void Z_FileDumpHeap (FILE *f);`
  - `Z_CheckHeap` (function, line 59) `void Z_CheckHeap (void);`
  - `Z_ChangeTag2` (function, line 60) `void Z_ChangeTag2 (void *ptr, int tag, char *file, int line);`
  - `Z_ChangeUser` (function, line 61) `void Z_ChangeUser(void *ptr, void **user);`
  - `Z_FreeMemory` (function, line 62) `int Z_FreeMemory (void);`
  - `Z_ZoneSize` (function, line 63) `unsigned int Z_ZoneSize(void);`
  - `__Z_ZONE__` (macro, line 25) `#define __Z_ZONE__`
  - `Z_ChangeTag` (macro, line 69) `#define Z_ChangeTag(p,t)`
- Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_iwad.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/f_finale.c`, `progs/doomgeneric/f_wipe.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/gusconf.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_minios_sound.c`, `progs/doomgeneric/i_scale.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/i_video.c`, `progs/doomgeneric/m_config.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/m_misc.c`, `progs/doomgeneric/memio.c`, `progs/doomgeneric/p_ceilng.c`, `progs/doomgeneric/p_doors.c`, `progs/doomgeneric/p_floor.c`, `progs/doomgeneric/p_lights.c`, `progs/doomgeneric/p_mobj.c`, `progs/doomgeneric/p_plats.c`, `progs/doomgeneric/p_saveg.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/p_tick.c`, `progs/doomgeneric/r_data.c`, `progs/doomgeneric/r_draw.c`, `progs/doomgeneric/r_plane.c`, `progs/doomgeneric/r_things.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/st_lib.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/v_video.c`, `progs/doomgeneric/w_file_stdc.c`, `progs/doomgeneric/w_main.c`, `progs/doomgeneric/w_wad.c`, `progs/doomgeneric/wi_stuff.c`, `progs/doomgeneric/z_zone.c`
