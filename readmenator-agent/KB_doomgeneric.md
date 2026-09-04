# Subsystem: doomgeneric

## progs/doomgeneric/am_map.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `AM_getIslope` (function, line 273) `void
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
  - `AM_unloadPics` (function, line 492) `void AM_unloadPics(void)`
  - `AM_clearMarks` (function, line 504) `void AM_clearMarks(void)`
  - `AM_LevelInit` (function, line 518) `void AM_LevelInit(void)`
  - `AM_Stop` (function, line 541) `void AM_Stop (void)`
  - `AM_Start` (function, line 554) `void AM_Start (void)`
  - `AM_minOutWindowScale` (function, line 573) `void AM_minOutWindowScale(void)`
  - `AM_maxOutWindowScale` (function, line 583) `void AM_maxOutWindowScale(void)`
  - `AM_Responder` (function, line 594) `boolean
AM_Responder
( event_t*	ev )`
  - `AM_changeWindowScale` (function, line 742) `void AM_changeWindowScale(void)`
  - `AM_doFollowPlayer` (function, line 761) `void AM_doFollowPlayer(void)`
  - `AM_updateLightLev` (function, line 785) `void AM_updateLightLev(void)`
  - `AM_Ticker` (function, line 806) `void AM_Ticker (void)`
  - `AM_clearFB` (function, line 834) `void AM_clearFB(int color)`
  - `AM_clipMline` (function, line 847) `boolean
AM_clipMline
( mline_t*	ml,
  fline_t*	fl )`
  - `AM_drawFline` (function, line 983) `void
AM_drawFline
( fline_t*	fl,
  int		color )`
  - `AM_drawMline` (function, line 1061) `void
AM_drawMline
( mline_t*	ml,
  int		color )`
  - `AM_drawGrid` (function, line 1077) `void AM_drawGrid(int color)`
  - `AM_drawWalls` (function, line 1123) `void AM_drawWalls(void)`
  - `AM_rotate` (function, line 1178) `void
AM_rotate
( fixed_t*	x,
  fixed_t*	y,
  angle_t	a )`
  - `AM_drawLineCharacter` (function, line 1196) `void
AM_drawLineCharacter
( mline_t*	lineguy,
  int		lineguylines,
  fixed_t	scale,
  angle_t	ang...`
  - `AM_drawPlayers` (function, line 1245) `void AM_drawPlayers(void)`
  - `AM_drawThings` (function, line 1289) `void
AM_drawThings
( int	colors,
  int 	colorrange)`
  - `AM_drawMarks` (function, line 1310) `void AM_drawMarks(void)`
  - `AM_drawCrosshair` (function, line 1331) `void AM_drawCrosshair(int color)`
  - `AM_Drawer` (function, line 1337) `void AM_Drawer (void)`
  - `REDS` (macro, line 50)
  - `REDRANGE` (macro, line 51)
  - `BLUES` (macro, line 52)
  - `BLUERANGE` (macro, line 53)
  - `GREENS` (macro, line 54)
  - `GREENRANGE` (macro, line 55)
  - `GRAYS` (macro, line 56)
  - `GRAYSRANGE` (macro, line 57)
  - `BROWNS` (macro, line 58)
  - `BROWNRANGE` (macro, line 59)
  - `YELLOWS` (macro, line 60)
  - `YELLOWRANGE` (macro, line 61)
  - `BLACK` (macro, line 62)
  - `WHITE` (macro, line 63)
  - `BACKGROUND` (macro, line 66)
  - `YOURCOLORS` (macro, line 67)
  - `YOURRANGE` (macro, line 68)
  - `WALLCOLORS` (macro, line 69)
  - `WALLRANGE` (macro, line 70)
  - `TSWALLCOLORS` (macro, line 71)
  - `TSWALLRANGE` (macro, line 72)
  - `FDWALLCOLORS` (macro, line 73)
  - `FDWALLRANGE` (macro, line 74)
  - `CDWALLCOLORS` (macro, line 75)
  - `CDWALLRANGE` (macro, line 76)
  - `THINGCOLORS` (macro, line 77)
  - `THINGRANGE` (macro, line 78)
  - `SECRETWALLCOLORS` (macro, line 79)
  - `SECRETWALLRANGE` (macro, line 80)
  - `GRIDCOLORS` (macro, line 81)
  - `GRIDRANGE` (macro, line 82)
  - `XHAIRCOLORS` (macro, line 83)
  - `AM_NUMMARKPOINTS` (macro, line 86)
  - `INITSCALEMTOF` (macro, line 90)
  - `F_PANINC` (macro, line 93)
  - `M_ZOOMIN` (macro, line 96)
  - `M_ZOOMOUT` (macro, line 99)
  - `FTOM` (macro, line 102)
  - `MTOF` (macro, line 103)
  - `CXMTOF` (macro, line 105)
  - `CYMTOF` (macro, line 106)
  - `LINE_NEVERSEE` (macro, line 109)
  - `R` (macro, line 143)
  - `R` (macro, line 154)
  - `R` (macro, line 175)
  - `R` (macro, line 183)
  - `DOOUTCODE` (macro, line 867)
  - `PUTDOT` (macro, line 1009)

## progs/doomgeneric/am_map.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__AMMAP_H__` (macro, line 20)
  - `AM_MSGHEADER` (macro, line 26)
  - `AM_MSGENTERED` (macro, line 27)
  - `AM_MSGEXITED` (macro, line 28)

## progs/doomgeneric/config.h
- Layer: infrastructure
- Doc: config.hin.  Generated from configure.ac by autoheader.
- Language: h
- Symbols:
  - `HAVE_INTTYPES_H` (macro, line 10)
  - `HAVE_STDINT_H` (macro, line 46)
  - `HAVE_STDLIB_H` (macro, line 49)
  - `HAVE_STRINGS_H` (macro, line 52)
  - `HAVE_STRING_H` (macro, line 55)
  - `HAVE_SYS_TYPES_H` (macro, line 61)
  - `PACKAGE` (macro, line 67)
  - `PACKAGE_NAME` (macro, line 73)
  - `PACKAGE_STRING` (macro, line 76)
  - `PACKAGE_TARNAME` (macro, line 79)
  - `PACKAGE_URL` (macro, line 82)
  - `PACKAGE_VERSION` (macro, line 85)
  - `PROGRAM_PREFIX` (macro, line 88)
  - `STDC_HEADERS` (macro, line 91)
  - `VERSION` (macro, line 94)
  - `FILES_DIR` (macro, line 100)

## progs/doomgeneric/d_englsh.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__D_ENGLSH__` (macro, line 21)
  - `D_DEVSTR` (macro, line 30)
  - `D_CDROM` (macro, line 31)
  - `PRESSKEY` (macro, line 36)
  - `PRESSYN` (macro, line 37)
  - `QUITMSG` (macro, line 38)
  - `LOADNET` (macro, line 39)
  - `QLOADNET` (macro, line 40)
  - `QSAVESPOT` (macro, line 41)
  - `SAVEDEAD` (macro, line 42)
  - `QSPROMPT` (macro, line 43)
  - `QLPROMPT` (macro, line 44)
  - `NEWGAME` (macro, line 45)
  - `NIGHTMARE` (macro, line 49)
  - `SWSTRING` (macro, line 53)
  - `MSGOFF` (macro, line 57)
  - `MSGON` (macro, line 59)
  - `NETEND` (macro, line 60)
  - `ENDGAME` (macro, line 61)
  - `DOSY` (macro, line 62)
  - `DETAILHI` (macro, line 64)
  - `DETAILLO` (macro, line 66)
  - `GAMMALVL0` (macro, line 67)
  - `GAMMALVL1` (macro, line 68)
  - `GAMMALVL2` (macro, line 69)
  - `GAMMALVL3` (macro, line 70)
  - `GAMMALVL4` (macro, line 71)
  - `EMPTYSTRING` (macro, line 72)
  - `GOTARMOR` (macro, line 77)
  - `GOTMEGA` (macro, line 78)
  - `GOTHTHBONUS` (macro, line 79)
  - `GOTARMBONUS` (macro, line 80)
  - `GOTSTIM` (macro, line 81)
  - `GOTMEDINEED` (macro, line 82)
  - `GOTMEDIKIT` (macro, line 83)
  - `GOTSUPER` (macro, line 84)
  - `GOTBLUECARD` (macro, line 85)
  - `GOTYELWCARD` (macro, line 87)
  - `GOTREDCARD` (macro, line 88)
  - `GOTBLUESKUL` (macro, line 89)
  - `GOTYELWSKUL` (macro, line 90)
  - `GOTREDSKULL` (macro, line 91)
  - `GOTINVUL` (macro, line 92)
  - `GOTBERSERK` (macro, line 94)
  - `GOTINVIS` (macro, line 95)
  - `GOTSUIT` (macro, line 96)
  - `GOTMAP` (macro, line 97)
  - `GOTVISOR` (macro, line 98)
  - `GOTMSPHERE` (macro, line 99)
  - `GOTCLIP` (macro, line 100)
  - `GOTCLIPBOX` (macro, line 102)
  - `GOTROCKET` (macro, line 103)
  - `GOTROCKBOX` (macro, line 104)
  - `GOTCELL` (macro, line 105)
  - `GOTCELLBOX` (macro, line 106)
  - `GOTSHELLS` (macro, line 107)
  - `GOTSHELLBOX` (macro, line 108)
  - `GOTBACKPACK` (macro, line 109)
  - `GOTBFG9000` (macro, line 110)
  - `GOTCHAINGUN` (macro, line 112)
  - `GOTCHAINSAW` (macro, line 113)
  - `GOTLAUNCHER` (macro, line 114)
  - `GOTPLASMA` (macro, line 115)
  - `GOTSHOTGUN` (macro, line 116)
  - `GOTSHOTGUN2` (macro, line 117)
  - `PD_BLUEO` (macro, line 122)
  - `PD_REDO` (macro, line 123)
  - `PD_YELLOWO` (macro, line 124)
  - `PD_BLUEK` (macro, line 125)
  - `PD_REDK` (macro, line 126)
  - `PD_YELLOWK` (macro, line 127)
  - `GGSAVED` (macro, line 132)
  - `HUSTR_MSGU` (macro, line 137)
  - `HUSTR_E1M1` (macro, line 138)
  - `HUSTR_E1M2` (macro, line 140)
  - `HUSTR_E1M3` (macro, line 141)
  - `HUSTR_E1M4` (macro, line 142)
  - `HUSTR_E1M5` (macro, line 143)
  - `HUSTR_E1M6` (macro, line 144)
  - `HUSTR_E1M7` (macro, line 145)
  - `HUSTR_E1M8` (macro, line 146)
  - `HUSTR_E1M9` (macro, line 147)
  - `HUSTR_E2M1` (macro, line 148)
  - `HUSTR_E2M2` (macro, line 150)
  - `HUSTR_E2M3` (macro, line 151)
  - `HUSTR_E2M4` (macro, line 152)
  - `HUSTR_E2M5` (macro, line 153)
  - `HUSTR_E2M6` (macro, line 154)
  - `HUSTR_E2M7` (macro, line 155)
  - `HUSTR_E2M8` (macro, line 156)
  - `HUSTR_E2M9` (macro, line 157)
  - `HUSTR_E3M1` (macro, line 158)
  - `HUSTR_E3M2` (macro, line 160)
  - `HUSTR_E3M3` (macro, line 161)
  - `HUSTR_E3M4` (macro, line 162)
  - `HUSTR_E3M5` (macro, line 163)
  - `HUSTR_E3M6` (macro, line 164)
  - `HUSTR_E3M7` (macro, line 165)
  - `HUSTR_E3M8` (macro, line 166)
  - `HUSTR_E3M9` (macro, line 167)
  - `HUSTR_E4M1` (macro, line 168)
  - `HUSTR_E4M2` (macro, line 170)
  - `HUSTR_E4M3` (macro, line 171)
  - `HUSTR_E4M4` (macro, line 172)
  - `HUSTR_E4M5` (macro, line 173)
  - `HUSTR_E4M6` (macro, line 174)
  - `HUSTR_E4M7` (macro, line 175)
  - `HUSTR_E4M8` (macro, line 176)
  - `HUSTR_E4M9` (macro, line 177)
  - `HUSTR_1` (macro, line 178)
  - `HUSTR_2` (macro, line 180)
  - `HUSTR_3` (macro, line 181)
  - `HUSTR_4` (macro, line 182)
  - `HUSTR_5` (macro, line 183)
  - `HUSTR_6` (macro, line 184)
  - `HUSTR_7` (macro, line 185)
  - `HUSTR_8` (macro, line 186)
  - `HUSTR_9` (macro, line 187)
  - `HUSTR_10` (macro, line 188)
  - `HUSTR_11` (macro, line 189)
  - `HUSTR_12` (macro, line 190)
  - `HUSTR_13` (macro, line 192)
  - `HUSTR_14` (macro, line 193)
  - `HUSTR_15` (macro, line 194)
  - `HUSTR_16` (macro, line 195)
  - `HUSTR_17` (macro, line 196)
  - `HUSTR_18` (macro, line 197)
  - `HUSTR_19` (macro, line 198)
  - `HUSTR_20` (macro, line 199)
  - `HUSTR_21` (macro, line 200)
  - `HUSTR_22` (macro, line 202)
  - `HUSTR_23` (macro, line 203)
  - `HUSTR_24` (macro, line 204)
  - `HUSTR_25` (macro, line 205)
  - `HUSTR_26` (macro, line 206)
  - `HUSTR_27` (macro, line 207)
  - `HUSTR_28` (macro, line 208)
  - `HUSTR_29` (macro, line 209)
  - `HUSTR_30` (macro, line 210)
  - `HUSTR_31` (macro, line 211)
  - `HUSTR_32` (macro, line 213)
  - `PHUSTR_1` (macro, line 214)
  - `PHUSTR_2` (macro, line 216)
  - `PHUSTR_3` (macro, line 217)
  - `PHUSTR_4` (macro, line 218)
  - `PHUSTR_5` (macro, line 219)
  - `PHUSTR_6` (macro, line 220)
  - `PHUSTR_7` (macro, line 221)
  - `PHUSTR_8` (macro, line 222)
  - `PHUSTR_9` (macro, line 223)
  - `PHUSTR_10` (macro, line 224)
  - `PHUSTR_11` (macro, line 225)
  - `PHUSTR_12` (macro, line 226)
  - `PHUSTR_13` (macro, line 228)
  - `PHUSTR_14` (macro, line 229)
  - `PHUSTR_15` (macro, line 230)
  - `PHUSTR_16` (macro, line 231)
  - `PHUSTR_17` (macro, line 232)
  - `PHUSTR_18` (macro, line 233)
  - `PHUSTR_19` (macro, line 234)
  - `PHUSTR_20` (macro, line 235)
  - `PHUSTR_21` (macro, line 236)
  - `PHUSTR_22` (macro, line 238)
  - `PHUSTR_23` (macro, line 239)
  - `PHUSTR_24` (macro, line 240)
  - `PHUSTR_25` (macro, line 241)
  - `PHUSTR_26` (macro, line 242)
  - `PHUSTR_27` (macro, line 243)
  - `PHUSTR_28` (macro, line 244)
  - `PHUSTR_29` (macro, line 245)
  - `PHUSTR_30` (macro, line 246)
  - `PHUSTR_31` (macro, line 247)
  - `PHUSTR_32` (macro, line 249)
  - `THUSTR_1` (macro, line 250)
  - `THUSTR_2` (macro, line 252)
  - `THUSTR_3` (macro, line 253)
  - `THUSTR_4` (macro, line 254)
  - `THUSTR_5` (macro, line 255)
  - `THUSTR_6` (macro, line 256)
  - `THUSTR_7` (macro, line 257)
  - `THUSTR_8` (macro, line 258)
  - `THUSTR_9` (macro, line 259)
  - `THUSTR_10` (macro, line 260)
  - `THUSTR_11` (macro, line 261)
  - `THUSTR_12` (macro, line 262)
  - `THUSTR_13` (macro, line 264)
  - `THUSTR_14` (macro, line 265)
  - `THUSTR_15` (macro, line 266)
  - `THUSTR_16` (macro, line 267)
  - `THUSTR_17` (macro, line 268)
  - `THUSTR_18` (macro, line 269)
  - `THUSTR_19` (macro, line 270)
  - `THUSTR_20` (macro, line 271)
  - `THUSTR_21` (macro, line 272)
  - `THUSTR_22` (macro, line 274)
  - `THUSTR_23` (macro, line 275)
  - `THUSTR_24` (macro, line 276)
  - `THUSTR_25` (macro, line 277)
  - `THUSTR_26` (macro, line 278)
  - `THUSTR_27` (macro, line 279)
  - `THUSTR_28` (macro, line 280)
  - `THUSTR_29` (macro, line 281)
  - `THUSTR_30` (macro, line 282)
  - `THUSTR_31` (macro, line 283)
  - `THUSTR_32` (macro, line 285)
  - `HUSTR_CHATMACRO1` (macro, line 286)
  - `HUSTR_CHATMACRO2` (macro, line 288)
  - `HUSTR_CHATMACRO3` (macro, line 289)
  - `HUSTR_CHATMACRO4` (macro, line 290)
  - `HUSTR_CHATMACRO5` (macro, line 291)
  - `HUSTR_CHATMACRO6` (macro, line 292)
  - `HUSTR_CHATMACRO7` (macro, line 293)
  - `HUSTR_CHATMACRO8` (macro, line 294)
  - `HUSTR_CHATMACRO9` (macro, line 295)
  - `HUSTR_CHATMACRO0` (macro, line 296)
  - `HUSTR_TALKTOSELF1` (macro, line 297)
  - `HUSTR_TALKTOSELF2` (macro, line 299)
  - `HUSTR_TALKTOSELF3` (macro, line 300)
  - `HUSTR_TALKTOSELF4` (macro, line 301)
  - `HUSTR_TALKTOSELF5` (macro, line 302)
  - `HUSTR_MESSAGESENT` (macro, line 303)
  - `HUSTR_PLRGREEN` (macro, line 308)
  - `HUSTR_PLRINDIGO` (macro, line 310)
  - `HUSTR_PLRBROWN` (macro, line 311)
  - `HUSTR_PLRRED` (macro, line 312)
  - `HUSTR_KEYGREEN` (macro, line 313)
  - `HUSTR_KEYINDIGO` (macro, line 315)
  - `HUSTR_KEYBROWN` (macro, line 316)
  - `HUSTR_KEYRED` (macro, line 317)
  - `AMSTR_FOLLOWON` (macro, line 322)
  - `AMSTR_FOLLOWOFF` (macro, line 324)
  - `AMSTR_GRIDON` (macro, line 325)
  - `AMSTR_GRIDOFF` (macro, line 327)
  - `AMSTR_MARKEDSPOT` (macro, line 328)
  - `AMSTR_MARKSCLEARED` (macro, line 330)
  - `STSTR_MUS` (macro, line 335)
  - `STSTR_NOMUS` (macro, line 337)
  - `STSTR_DQDON` (macro, line 338)
  - `STSTR_DQDOFF` (macro, line 339)
  - `STSTR_KFAADDED` (macro, line 340)
  - `STSTR_FAADDED` (macro, line 342)
  - `STSTR_NCON` (macro, line 343)
  - `STSTR_NCOFF` (macro, line 345)
  - `STSTR_BEHOLD` (macro, line 346)
  - `STSTR_BEHOLDX` (macro, line 348)
  - `STSTR_CHOPPERS` (macro, line 349)
  - `STSTR_CLEV` (macro, line 351)
  - `E1TEXT` (macro, line 356)
  - `E2TEXT` (macro, line 372)
  - `E3TEXT` (macro, line 392)
  - `E4TEXT` (macro, line 412)
  - `C1TEXT` (macro, line 434)
  - `C2TEXT` (macro, line 450)
  - `C3TEXT` (macro, line 472)
  - `C4TEXT` (macro, line 486)
  - `C5TEXT` (macro, line 507)
  - `C6TEXT` (macro, line 517)
  - `P1TEXT` (macro, line 525)
  - `P2TEXT` (macro, line 542)
  - `P3TEXT` (macro, line 553)
  - `P4TEXT` (macro, line 567)
  - `P5TEXT` (macro, line 583)
  - `P6TEXT` (macro, line 591)
  - `T1TEXT` (macro, line 596)
  - `T2TEXT` (macro, line 611)
  - `T3TEXT` (macro, line 623)
  - `T4TEXT` (macro, line 634)
  - `T5TEXT` (macro, line 647)
  - `T6TEXT` (macro, line 655)
  - `CC_ZOMBIE` (macro, line 674)
  - `CC_SHOTGUN` (macro, line 675)
  - `CC_HEAVY` (macro, line 676)
  - `CC_IMP` (macro, line 677)
  - `CC_DEMON` (macro, line 678)
  - `CC_LOST` (macro, line 679)
  - `CC_CACO` (macro, line 680)
  - `CC_HELL` (macro, line 681)
  - `CC_BARON` (macro, line 682)
  - `CC_ARACH` (macro, line 683)
  - `CC_PAIN` (macro, line 684)
  - `CC_REVEN` (macro, line 685)
  - `CC_MANCU` (macro, line 686)
  - `CC_ARCH` (macro, line 687)
  - `CC_SPIDER` (macro, line 688)
  - `CC_CYBER` (macro, line 689)
  - `CC_HERO` (macro, line 690)

## progs/doomgeneric/d_event.c
- Layer: infrastructure
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `D_PostEvent` (function, line 35) `void D_PostEvent (event_t* ev)`
  - `D_PopEvent` (function, line 42) `event_t *D_PopEvent(void)`
  - `MAXEVENTS` (macro, line 24)

## progs/doomgeneric/d_event.h
- Layer: infrastructure
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__D_EVENT__` (macro, line 21)

## progs/doomgeneric/d_items.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c

## progs/doomgeneric/d_items.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__D_ITEMS__` (macro, line 21)

## progs/doomgeneric/d_iwad.c
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: c
- Symbols:
  - `AddIWADDir` (function, line 63) `static void AddIWADDir(char *dir)`
  - `GetRegistryString` (function, line 191) `static char *GetRegistryString(registry_value_t *reg_val)`
  - `CheckUninstallStrings` (function, line 235) `static void CheckUninstallStrings(void)`
  - `CheckCollectorsEdition` (function, line 269) `static void CheckCollectorsEdition(void)`
  - `CheckSteamEdition` (function, line 296) `static void CheckSteamEdition(void)`
  - `CheckSteamGUSPatches` (function, line 323) `static void CheckSteamGUSPatches(void)`
  - `CheckDOSDefaults` (function, line 363) `static void CheckDOSDefaults(void)`
  - `DirIsFile` (function, line 390) `static boolean DirIsFile(char *path, char *filename)`
  - `CheckDirectoryHasIWAD` (function, line 407) `static char *CheckDirectoryHasIWAD(char *dir, char *iwadname)`
  - `SearchDirectoryForIWAD` (function, line 448) `static char *SearchDirectoryForIWAD(char *dir, int mask, GameMission_t *mission)`
  - `IdentifyIWADByName` (function, line 476) `static GameMission_t IdentifyIWADByName(char *name, int mask)`
  - `AddDoomWadPath` (function, line 517) `static void AddDoomWadPath(void)`
  - `BuildIWADDirList` (function, line 568) `static void BuildIWADDirList(void)`
  - `D_FindWADByName` (function, line 629) `char *D_FindWADByName(char *name)`
  - `D_TryFindWADByName` (function, line 680) `char *D_TryFindWADByName(char *filename)`
  - `D_FindIWAD` (function, line 703) `char *D_FindIWAD(int mask, GameMission_t *mission)`
  - `D_FindAllIWADs` (function, line 756) `const iwad_t **D_FindAllIWADs(int mask)`
  - `D_SaveGameIWADName` (function, line 795) `char *D_SaveGameIWADName(GameMission_t gamemission)`
  - `D_SuggestIWADName` (function, line 819) `char *D_SuggestIWADName(GameMission_t mission, GameMode_t mode)`
  - `D_SuggestGameName` (function, line 834) `char *D_SuggestGameName(GameMission_t mission, GameMode_t mode)`
  - `MAX_IWAD_DIRS` (macro, line 57)
  - `WIN32_LEAN_AND_MEAN` (macro, line 79)
  - `UNINSTALLER_STRING` (macro, line 89)
  - `SOFTWARE_KEY` (macro, line 102)
  - `SOFTWARE_KEY` (macro, line 104)
  - `STEAM_BFG_GUS_PATCHES` (macro, line 188)

## progs/doomgeneric/d_iwad.h
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `__D_IWAD__` (macro, line 20)
  - `IWAD_MASK_DOOM` (macro, line 23)
  - `IWAD_MASK_HERETIC` (macro, line 30)
  - `IWAD_MASK_HEXEN` (macro, line 31)
  - `IWAD_MASK_STRIFE` (macro, line 32)

## progs/doomgeneric/d_loop.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `GetAdjustedTime` (function, line 118) `static int GetAdjustedTime(void)`
  - `BuildNewTic` (function, line 135) `static boolean BuildNewTic(void)`
  - `NetUpdate` (function, line 202) `void NetUpdate (void)`
  - `D_Disconnected` (function, line 251) `static void D_Disconnected(void)`
  - `D_ReceiveTic` (function, line 270) `void D_ReceiveTic(ticcmd_t *ticcmds, boolean *players_mask)`
  - `D_StartGameLoop` (function, line 304) `void D_StartGameLoop(void)`
  - `BlockUntilStart` (function, line 314) `static void BlockUntilStart(net_gamesettings_t *settings,
                            netgame_sta...`
  - `D_StartNetGame` (function, line 339) `void D_StartNetGame(net_gamesettings_t *settings,
                    netgame_startup_callback_t ...`
  - `D_InitNetGame` (function, line 451) `boolean D_InitNetGame(net_connect_data_t *connect_data)`
  - `D_QuitNetGame` (function, line 560) `void D_QuitNetGame (void)`
  - `GetLowTic` (function, line 567) `static int GetLowTic(void)`
  - `OldNetSync` (function, line 590) `static void OldNetSync(void)`
  - `PlayersInGame` (function, line 641) `static boolean PlayersInGame(void)`
  - `TicdupSquash` (function, line 671) `static void TicdupSquash(ticcmd_set_t *set)`
  - `SinglePlayerClear` (function, line 688) `static void SinglePlayerClear(ticcmd_set_t *set)`
  - `TryRunTics` (function, line 705) `void TryRunTics (void)`
  - `D_RegisterLoopCallbacks` (function, line 821) `void D_RegisterLoopCallbacks(loop_interface_t *i)`

## progs/doomgeneric/d_loop.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__D_LOOP__` (macro, line 20)

## progs/doomgeneric/d_main.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `D_ProcessEvents` (function, line 139) `void D_ProcessEvents (void)`
  - `D_Display` (function, line 168) `void D_Display (void)`
  - `D_BindVariables` (function, line 334) `void D_BindVariables(void)`
  - `D_GrabMouseCallback` (function, line 387) `boolean D_GrabMouseCallback(void)`
  - `D_DoomLoop` (function, line 408) `void D_DoomLoop (void)`
  - `D_PageTicker` (function, line 490) `void D_PageTicker (void)`
  - `D_PageDrawer` (function, line 501) `void D_PageDrawer (void)`
  - `D_AdvanceDemo` (function, line 511) `void D_AdvanceDemo (void)`
  - `D_DoAdvanceDemo` (function, line 521) `void D_DoAdvanceDemo (void)`
  - `D_StartTitle` (function, line 609) `void D_StartTitle (void)`
  - `GetGameName` (function, line 657) `static char *GetGameName(char *gamename)`
  - `SetMissionForPackName` (function, line 700) `static void SetMissionForPackName(char *pack_name)`
  - `D_IdentifyVersion` (function, line 736) `void D_IdentifyVersion(void)`
  - `D_SetGameDescription` (function, line 819) `void D_SetGameDescription(void)`
  - `D_AddFile` (function, line 882) `static boolean D_AddFile(char *filename)`
  - `PrintDehackedBanners` (function, line 917) `void PrintDehackedBanners(void)`
  - `InitGameVersion` (function, line 962) `static void InitGameVersion(void)`
  - `PrintGameVersion` (function, line 1064) `void PrintGameVersion(void)`
  - `D_Endoom` (function, line 1081) `static void D_Endoom(void)`
  - `LoadIwadDeh` (function, line 1105) `static void LoadIwadDeh(void)`
  - `D_DoomMain` (function, line 1178) `void D_DoomMain (void)`

## progs/doomgeneric/d_main.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__D_MAIN__` (macro, line 21)

## progs/doomgeneric/d_mode.c
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: c
- Symbols:
  - `D_ValidGameMode` (function, line 49) `boolean D_ValidGameMode(GameMission_t mission, GameMode_t mode)`
  - `D_ValidEpisodeMap` (function, line 64) `boolean D_ValidEpisodeMap(GameMission_t mission, GameMode_t mode,
                          int e...`
  - `D_GetNumEpisodes` (function, line 102) `int D_GetNumEpisodes(GameMission_t mission, GameMode_t mode)`
  - `D_ValidGameVersion` (function, line 134) `boolean D_ValidGameVersion(GameMission_t mission, GameVersion_t version)`
  - `D_IsEpisodeMap` (function, line 160) `boolean D_IsEpisodeMap(GameMission_t mission)`
  - `D_GameMissionString` (function, line 181) `char *D_GameMissionString(GameMission_t mission)`

## progs/doomgeneric/d_mode.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__D_MODE__` (macro, line 21)

## progs/doomgeneric/d_net.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `PlayerQuitGame` (function, line 44) `static void PlayerQuitGame(player_t *player)`
  - `RunTic` (function, line 70) `static void RunTic(ticcmd_t *cmds, boolean *ingame)`
  - `LoadGameSettings` (function, line 107) `static void LoadGameSettings(net_gamesettings_t *settings)`
  - `SaveGameSettings` (function, line 138) `static void SaveGameSettings(net_gamesettings_t *settings)`
  - `InitConnectData` (function, line 158) `static void InitConnectData(net_connect_data_t *connect_data)`
  - `D_ConnectNetGame` (function, line 214) `void D_ConnectNetGame(void)`
  - `D_CheckNetGame` (function, line 240) `void D_CheckNetGame (void)`

## progs/doomgeneric/d_player.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `player_s` (struct, line 78)
  - `__D_PLAYER__` (macro, line 21)

## progs/doomgeneric/d_textur.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__D_TEXTUR__` (macro, line 22)

## progs/doomgeneric/d_think.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `thinker_s` (struct, line 58)
  - `__D_THINK__` (macro, line 23)

## progs/doomgeneric/d_ticcmd.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software Copyright(C) 2005-2014 Simon Howard  This
- Language: h
- Symbols:
  - `__D_TICCMD__` (macro, line 22)

## progs/doomgeneric/deh_main.h
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `DEH_MAIN_H` (macro, line 19)
  - `DEH_VANILLA_NUMSTATES` (macro, line 29)
  - `DEH_VANILLA_NUMSFX` (macro, line 31)

## progs/doomgeneric/deh_misc.h
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `DEH_MISC_H` (macro, line 19)
  - `DEH_DEFAULT_INITIAL_HEALTH` (macro, line 22)
  - `DEH_DEFAULT_INITIAL_BULLETS` (macro, line 24)
  - `DEH_DEFAULT_MAX_HEALTH` (macro, line 25)
  - `DEH_DEFAULT_MAX_ARMOR` (macro, line 26)
  - `DEH_DEFAULT_GREEN_ARMOR_CLASS` (macro, line 27)
  - `DEH_DEFAULT_BLUE_ARMOR_CLASS` (macro, line 28)
  - `DEH_DEFAULT_MAX_SOULSPHERE` (macro, line 29)
  - `DEH_DEFAULT_SOULSPHERE_HEALTH` (macro, line 30)
  - `DEH_DEFAULT_MEGASPHERE_HEALTH` (macro, line 31)
  - `DEH_DEFAULT_GOD_MODE_HEALTH` (macro, line 32)
  - `DEH_DEFAULT_IDFA_ARMOR` (macro, line 33)
  - `DEH_DEFAULT_IDFA_ARMOR_CLASS` (macro, line 34)
  - `DEH_DEFAULT_IDKFA_ARMOR` (macro, line 35)
  - `DEH_DEFAULT_IDKFA_ARMOR_CLASS` (macro, line 36)
  - `DEH_DEFAULT_BFG_CELLS_PER_SHOT` (macro, line 37)
  - `DEH_DEFAULT_SPECIES_INFIGHTING` (macro, line 38)
  - `deh_initial_health` (macro, line 62)
  - `deh_initial_bullets` (macro, line 64)
  - `deh_max_health` (macro, line 65)
  - `deh_max_armor` (macro, line 66)
  - `deh_green_armor_class` (macro, line 67)
  - `deh_blue_armor_class` (macro, line 68)
  - `deh_max_soulsphere` (macro, line 69)
  - `deh_soulsphere_health` (macro, line 70)
  - `deh_megasphere_health` (macro, line 71)
  - `deh_god_mode_health` (macro, line 72)
  - `deh_idfa_armor` (macro, line 73)
  - `deh_idfa_armor_class` (macro, line 74)
  - `deh_idkfa_armor` (macro, line 75)
  - `deh_idkfa_armor_class` (macro, line 76)
  - `deh_bfg_cells_per_shot` (macro, line 77)
  - `deh_species_infighting` (macro, line 78)

## progs/doomgeneric/deh_str.h
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `DEH_STR_H` (macro, line 19)
  - `DEH_String` (macro, line 37)
  - `DEH_printf` (macro, line 39)
  - `DEH_fprintf` (macro, line 40)
  - `DEH_snprintf` (macro, line 41)
  - `DEH_AddStringReplacement` (macro, line 42)

## progs/doomgeneric/doom.h
- Layer: utility
- Language: h
- Symbols:
  - `SRC_CHOCDOOM_DOOM_H_` (macro, line 10)

## progs/doomgeneric/doomdata.h
- Layer: data_access
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__DOOMDATA__` (macro, line 22)
  - `ML_BLOCKING` (macro, line 98)
  - `ML_BLOCKMONSTERS` (macro, line 101)
  - `ML_TWOSIDED` (macro, line 105)
  - `ML_DONTPEGTOP` (macro, line 117)
  - `ML_DONTPEGBOTTOM` (macro, line 120)
  - `ML_SECRET` (macro, line 123)
  - `ML_SOUNDBLOCK` (macro, line 126)
  - `ML_DONTDRAW` (macro, line 129)
  - `ML_MAPPED` (macro, line 132)
  - `NF_SUBSECTOR` (macro, line 175)

## progs/doomgeneric/doomdef.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c

## progs/doomgeneric/doomdef.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__DOOMDEF__` (macro, line 21)
  - `DOOM_VERSION` (macro, line 34)
  - `DOOM_191_VERSION` (macro, line 37)
  - `RANGECHECK` (macro, line 42)
  - `MAXPLAYERS` (macro, line 45)
  - `MTF_EASY` (macro, line 77)
  - `MTF_NORMAL` (macro, line 78)
  - `MTF_HARD` (macro, line 79)
  - `MTF_AMBUSH` (macro, line 82)

## progs/doomgeneric/doomfeatures.h
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `DOOM_FEATURES_H` (macro, line 20)
  - `FEATURE_SOUND` (macro, line 35)

## progs/doomgeneric/doomgeneric.c
- Layer: utility
- Doc: include "doomgeneric.h"
- Language: c
- Symbols:
  - `dg_Create` (function, line 4) `void dg_Create()`

## progs/doomgeneric/doomgeneric.h
- Layer: utility
- Doc: ifndef DOOM_GENERIC define DOOM_GENERIC  include <stdlib.h> include <stdint.h>  define DOOMGENERIC_RESX 320 define DOOMG
- Language: h
- Symbols:
  - `DOOM_GENERIC` (macro, line 2)
  - `DOOMGENERIC_RESX` (macro, line 6)
  - `DOOMGENERIC_RESY` (macro, line 8)

## progs/doomgeneric/doomgeneric_minios.c
- Layer: utility
- Doc: doomgeneric_minios.c - MiniOS platform layer for doomgeneric.
- Language: c
- Symbols:
  - `color` (struct, line 78)
  - `mini_parse_autoframes` (function, line 22) `static void mini_parse_autoframes(int argc, char **argv)`
  - `sys_time_ms` (function, line 35) `static long sys_time_ms(void)`
  - `sys_kbd` (function, line 41) `static long sys_kbd(void)`
  - `sys_palette` (function, line 46) `static long sys_palette(const unsigned char *pal)`
  - `sys_kbd_raw` (function, line 51) `static long sys_kbd_raw(int on)`
  - `sys_vga_mode` (function, line 56) `static long sys_vga_mode(int on)`
  - `sys_doom_frame` (function, line 61) `static long sys_doom_frame(void)`
  - `load_vga_palette` (function, line 84) `static void load_vga_palette(void)`
  - `scancode_to_doom` (function, line 97) `static unsigned char scancode_to_doom(unsigned char raw)`
  - `kbd_enqueue` (function, line 156) `static void kbd_enqueue(unsigned char doom_key, int pressed)`
  - `kbd_poll` (function, line 163) `static void kbd_poll(void)`
  - `DG_Init` (function, line 206) `void DG_Init(void)`
  - `DG_DrawFrame` (function, line 214) `void DG_DrawFrame(void)`
  - `DG_SleepMs` (function, line 244) `void DG_SleepMs(uint32_t ms)`
  - `DG_GetTicksMs` (function, line 250) `uint32_t DG_GetTicksMs(void)`
  - `DG_GetKey` (function, line 254) `int DG_GetKey(int *pressed, unsigned char *key)`
  - `DG_SetWindowTitle` (function, line 265) `void DG_SetWindowTitle(const char *title)`
  - `FB_ADDR` (macro, line 71)
  - `FB_WIDTH` (macro, line 72)
  - `FB_HEIGHT` (macro, line 73)
  - `KBD_QUEUE_SIZE` (macro, line 152)

## progs/doomgeneric/doomgeneric_sdl.c
- Layer: utility
- Doc: doomgeneric for soso os  include "doomkeys.h" include "m_argv.h" include "doomgeneric.h"  include <stdio.h> include <uni
- Language: c
- Symbols:
  - `convertToDoomKey` (function, line 22) `static unsigned char convertToDoomKey(unsigned int key)`
  - `addKeyToQueue` (function, line 62) `static void addKeyToQueue(int pressed, unsigned int keyCode)`
  - `handleKeyInput` (function, line 72) `static void handleKeyInput()`
  - `DG_Init` (function, line 91) `void DG_Init()`
  - `DG_DrawFrame` (function, line 111) `void DG_DrawFrame()`
  - `DG_SleepMs` (function, line 122) `void DG_SleepMs(uint32_t ms)`
  - `DG_GetTicksMs` (function, line 127) `uint32_t DG_GetTicksMs()`
  - `DG_GetKey` (function, line 132) `int DG_GetKey(int* pressed, unsigned char* doomKey)`
  - `DG_SetWindowTitle` (function, line 151) `void DG_SetWindowTitle(const char * title)`
  - `KEYQUEUE_SIZE` (macro, line 16)

## progs/doomgeneric/doomgeneric_soso.c
- Layer: utility
- Doc: doomgeneric for soso os  include "doomkeys.h" include "m_argv.h" include "doomgeneric.h"  include <stdio.h> include <fcn
- Language: c
- Symbols:
  - `convertToDoomKey` (function, line 42) `static unsigned char convertToDoomKey(unsigned char scancode)`
  - `addKeyToQueue` (function, line 91) `static void addKeyToQueue(int pressed, unsigned char keyCode)`
  - `disableRawMode` (function, line 107) `void disableRawMode()`
  - `enableRawMode` (function, line 113) `void enableRawMode()`
  - `DG_Init` (function, line 123) `void DG_Init()`
  - `handleKeyInput` (function, line 185) `static void handleKeyInput()`
  - `DG_DrawFrame` (function, line 213) `void DG_DrawFrame()`
  - `DG_SleepMs` (function, line 226) `void DG_SleepMs(uint32_t ms)`
  - `DG_GetTicksMs` (function, line 231) `uint32_t DG_GetTicksMs()`
  - `DG_GetKey` (function, line 236) `int DG_GetKey(int* pressed, unsigned char* doomKey)`
  - `DG_SetWindowTitle` (function, line 257) `void DG_SetWindowTitle(const char * title)`
  - `KEYQUEUE_SIZE` (macro, line 23)

## progs/doomgeneric/doomgeneric_sosox.c
- Layer: utility
- Doc: doomgeneric for soso os (nano-x version) TODO: get keys from X, not using direct keyboard access!  include "doomkeys.h" 
- Language: c
- Symbols:
  - `convert_to_doom_key` (function, line 37) `static unsigned char convert_to_doom_key(unsigned char scancode)`
  - `add_key_to_queue` (function, line 87) `static void add_key_to_queue(int pressed, unsigned char key_code)`
  - `disable_raw_mode` (function, line 101) `void disable_raw_mode()`
  - `enable_raw_mode` (function, line 106) `void enable_raw_mode()`
  - `DG_Init` (function, line 116) `void DG_Init()`
  - `handle_key_input` (function, line 158) `static void handle_key_input()`
  - `DG_DrawFrame` (function, line 186) `void DG_DrawFrame()`
  - `DG_SleepMs` (function, line 224) `void DG_SleepMs(uint32_t ms)`
  - `DG_GetTicksMs` (function, line 229) `uint32_t DG_GetTicksMs()`
  - `DG_GetKey` (function, line 234) `int DG_GetKey(int* pressed, unsigned char* doomKey)`
  - `DG_SetWindowTitle` (function, line 255) `void DG_SetWindowTitle(const char * title)`
  - `KEYQUEUE_SIZE` (macro, line 23)

## progs/doomgeneric/doomgeneric_win.c
- Layer: utility
- Doc: include "doomkeys.h"  include "doomgeneric.h"  include <stdio.h>  include <Windows.h>
- Language: c
- Symbols:
  - `convertToDoomKey` (function, line 19) `static unsigned char convertToDoomKey(unsigned char key)`
  - `addKeyToQueue` (function, line 58) `static void addKeyToQueue(int pressed, unsigned char keyCode)`
  - `wndProc` (function, line 69) `static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)`
  - `DG_Init` (function, line 94) `void DG_Init()`
  - `DG_DrawFrame` (function, line 145) `void DG_DrawFrame()`
  - `DG_SleepMs` (function, line 161) `void DG_SleepMs(uint32_t ms)`
  - `DG_GetTicksMs` (function, line 166) `uint32_t DG_GetTicksMs()`
  - `DG_GetKey` (function, line 171) `int DG_GetKey(int* pressed, unsigned char* doomKey)`
  - `DG_SetWindowTitle` (function, line 192) `void DG_SetWindowTitle(const char * title)`
  - `KEYQUEUE_SIZE` (macro, line 12)

## progs/doomgeneric/doomgeneric_xlib.c
- Layer: utility
- Doc: include "doomkeys.h"  include "doomgeneric.h"  include <ctype.h> include <stdio.h> include <string.h> include <unistd.h>
- Language: c
- Symbols:
  - `convertToDoomKey` (function, line 26) `static unsigned char convertToDoomKey(unsigned int key)`
  - `addKeyToQueue` (function, line 67) `static void addKeyToQueue(int pressed, unsigned int keyCode)`
  - `DG_Init` (function, line 78) `void DG_Init()`
  - `DG_DrawFrame` (function, line 125) `void DG_DrawFrame()`
  - `DG_SleepMs` (function, line 171) `void DG_SleepMs(uint32_t ms)`
  - `DG_GetTicksMs` (function, line 176) `uint32_t DG_GetTicksMs()`
  - `DG_GetKey` (function, line 186) `int DG_GetKey(int* pressed, unsigned char* doomKey)`
  - `DG_SetWindowTitle` (function, line 207) `void DG_SetWindowTitle(const char * title)`
  - `KEYQUEUE_SIZE` (macro, line 20)

## progs/doomgeneric/doomkeys.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__DOOMKEYS__` (macro, line 20)
  - `KEY_RIGHTARROW` (macro, line 27)
  - `KEY_LEFTARROW` (macro, line 28)
  - `KEY_UPARROW` (macro, line 29)
  - `KEY_DOWNARROW` (macro, line 30)
  - `KEY_STRAFE_L` (macro, line 31)
  - `KEY_STRAFE_R` (macro, line 32)
  - `KEY_USE` (macro, line 33)
  - `KEY_FIRE` (macro, line 34)
  - `KEY_ESCAPE` (macro, line 35)
  - `KEY_ENTER` (macro, line 36)
  - `KEY_TAB` (macro, line 37)
  - `KEY_F1` (macro, line 38)
  - `KEY_F2` (macro, line 39)
  - `KEY_F3` (macro, line 40)
  - `KEY_F4` (macro, line 41)
  - `KEY_F5` (macro, line 42)
  - `KEY_F6` (macro, line 43)
  - `KEY_F7` (macro, line 44)
  - `KEY_F8` (macro, line 45)
  - `KEY_F9` (macro, line 46)
  - `KEY_F10` (macro, line 47)
  - `KEY_F11` (macro, line 48)
  - `KEY_F12` (macro, line 49)
  - `KEY_BACKSPACE` (macro, line 50)
  - `KEY_PAUSE` (macro, line 52)
  - `KEY_EQUALS` (macro, line 53)
  - `KEY_MINUS` (macro, line 55)
  - `KEY_RSHIFT` (macro, line 56)
  - `KEY_RCTRL` (macro, line 58)
  - `KEY_RALT` (macro, line 59)
  - `KEY_LALT` (macro, line 60)
  - `KEY_CAPSLOCK` (macro, line 64)
  - `KEY_NUMLOCK` (macro, line 66)
  - `KEY_SCRLCK` (macro, line 67)
  - `KEY_PRTSCR` (macro, line 68)
  - `KEY_HOME` (macro, line 69)
  - `KEY_END` (macro, line 71)
  - `KEY_PGUP` (macro, line 72)
  - `KEY_PGDN` (macro, line 73)
  - `KEY_INS` (macro, line 74)
  - `KEY_DEL` (macro, line 75)
  - `KEYP_0` (macro, line 76)
  - `KEYP_1` (macro, line 78)
  - `KEYP_2` (macro, line 79)
  - `KEYP_3` (macro, line 80)
  - `KEYP_4` (macro, line 81)
  - `KEYP_5` (macro, line 82)
  - `KEYP_6` (macro, line 83)
  - `KEYP_7` (macro, line 84)
  - `KEYP_8` (macro, line 85)
  - `KEYP_9` (macro, line 86)
  - `KEYP_DIVIDE` (macro, line 87)
  - `KEYP_PLUS` (macro, line 89)
  - `KEYP_MINUS` (macro, line 90)
  - `KEYP_MULTIPLY` (macro, line 91)
  - `KEYP_PERIOD` (macro, line 92)
  - `KEYP_EQUALS` (macro, line 93)
  - `KEYP_ENTER` (macro, line 94)

## progs/doomgeneric/doomstat.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c

## progs/doomgeneric/doomstat.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__D_STATE__` (macro, line 26)
  - `logical_gamemission` (macro, line 68)
  - `MAX_DM_STARTS` (macro, line 227)

## progs/doomgeneric/doomtype.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__DOOMTYPE__` (macro, line 22)
  - `strcasecmp` (macro, line 29)
  - `strncasecmp` (macro, line 31)
  - `PACKEDATTR` (macro, line 50)
  - `PACKEDATTR` (macro, line 52)
  - `DIR_SEPARATOR` (macro, line 87)
  - `DIR_SEPARATOR_S` (macro, line 89)
  - `PATH_SEPARATOR` (macro, line 90)
  - `DIR_SEPARATOR` (macro, line 93)
  - `DIR_SEPARATOR_S` (macro, line 95)
  - `PATH_SEPARATOR` (macro, line 96)
  - `arrlen` (macro, line 99)

## progs/doomgeneric/dstrings.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c

## progs/doomgeneric/dstrings.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__DSTRINGS__` (macro, line 22)
  - `SAVEGAMENAME` (macro, line 30)
  - `NUM_QUITMESSAGES` (macro, line 35)

## progs/doomgeneric/dummy.c
- Layer: utility
- Language: c
- Symbols:
  - `I_InitTimidityConfig` (function, line 42) `void I_InitTimidityConfig(void)`

## progs/doomgeneric/f_finale.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `F_StartFinale` (function, line 108) `void F_StartFinale (void)`
  - `F_Responder` (function, line 157) `boolean F_Responder (event_t *event)`
  - `F_Ticker` (function, line 172) `void F_Ticker (void)`
  - `F_TextWrite` (function, line 225) `void F_TextWrite (void)`
  - `F_StartCast` (function, line 340) `void F_StartCast (void)`
  - `F_CastTicker` (function, line 358) `void F_CastTicker (void)`
  - `F_CastResponder` (function, line 464) `boolean F_CastResponder (event_t* ev)`
  - `F_CastPrint` (function, line 484) `void F_CastPrint (char* text)`
  - `F_CastDrawer` (function, line 540) `void F_CastDrawer (void)`
  - `F_DrawPatchCol` (function, line 571) `void
F_DrawPatchCol
( int		x,
  patch_t*	patch,
  int		col )`
  - `F_BunnyScroll` (function, line 606) `void F_BunnyScroll (void)`
  - `F_ArtScreenDrawer` (function, line 660) `static void F_ArtScreenDrawer(void)`
  - `F_Drawer` (function, line 702) `void F_Drawer (void)`
  - `TEXTSPEED` (macro, line 56)
  - `TEXTWAIT` (macro, line 58)

## progs/doomgeneric/f_finale.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__F_FINALE__` (macro, line 21)

## progs/doomgeneric/f_wipe.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `wipe_shittyColMajorXform` (function, line 40) `void
wipe_shittyColMajorXform
( short*	array,
  int		width,
  int		height )`
  - `wipe_initColorXForm` (function, line 63) `int
wipe_initColorXForm
( int	width,
  int	height,
  int	ticks )`
  - `wipe_doColorXForm` (function, line 73) `int
wipe_doColorXForm
( int	width,
  int	height,
  int	ticks )`
  - `wipe_exitColorXForm` (function, line 119) `int
wipe_exitColorXForm
( int	width,
  int	height,
  int	ticks )`
  - `wipe_initMelt` (function, line 131) `int
wipe_initMelt
( int	width,
  int	height,
  int	ticks )`
  - `wipe_doMelt` (function, line 162) `int
wipe_doMelt
( int	width,
  int	height,
  int	ticks )`
  - `wipe_exitMelt` (function, line 217) `int
wipe_exitMelt
( int	width,
  int	height,
  int	ticks )`
  - `wipe_StartScreen` (function, line 229) `int
wipe_StartScreen
( int	x,
  int	y,
  int	width,
  int	height )`
  - `wipe_EndScreen` (function, line 241) `int
wipe_EndScreen
( int	x,
  int	y,
  int	width,
  int	height )`
  - `wipe_ScreenWipe` (function, line 254) `int
wipe_ScreenWipe
( int	wipeno,
  int	x,
  int	y,
  int	width,
  int	height,
  int	ticks )`

## progs/doomgeneric/f_wipe.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__F_WIPE_H__` (macro, line 21)

## progs/doomgeneric/g_game.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `G_CmdChecksum` (function, line 232) `int G_CmdChecksum (ticcmd_t* cmd)`
  - `WeaponSelectable` (function, line 243) `static boolean WeaponSelectable(weapontype_t weapon)`
  - `G_NextWeapon` (function, line 280) `static int G_NextWeapon(int direction)`
  - `G_BuildTiccmd` (function, line 322) `void G_BuildTiccmd (ticcmd_t* cmd, int maketic)`
  - `G_DoLoadLevel` (function, line 603) `void G_DoLoadLevel (void)`
  - `SetJoyButtons` (function, line 674) `static void SetJoyButtons(unsigned int buttons_mask)`
  - `SetMouseButtons` (function, line 702) `static void SetMouseButtons(unsigned int buttons_mask)`
  - `G_Responder` (function, line 733) `boolean G_Responder (event_t* ev)`
  - `G_Ticker` (function, line 854) `void G_Ticker (void)`
  - `G_InitPlayer` (function, line 1039) `void G_InitPlayer (int player)`
  - `G_PlayerFinishLevel` (function, line 1051) `void G_PlayerFinishLevel (int player)`
  - `G_PlayerReborn` (function, line 1072) `void G_PlayerReborn (int player)`
  - `G_CheckSpot` (function, line 1114) `boolean
G_CheckSpot
( int		playernum,
  mapthing_t*	mthing )`
  - `G_DeathMatchSpawnPlayer` (function, line 1223) `void G_DeathMatchSpawnPlayer (int playernum)`
  - `G_DoReborn` (function, line 1250) `void G_DoReborn (int playernum)`
  - `G_ScreenShot` (function, line 1294) `void G_ScreenShot (void)`
  - `G_ExitLevel` (function, line 1327) `void G_ExitLevel (void)`
  - `G_SecretExitLevel` (function, line 1335) `void G_SecretExitLevel (void)`
  - `G_DoCompleted` (function, line 1345) `void G_DoCompleted (void)`
  - `G_WorldDone` (function, line 1494) `void G_WorldDone (void)`
  - `G_DoWorldDone` (function, line 1518) `void G_DoWorldDone (void)`
  - `G_LoadGame` (function, line 1538) `void G_LoadGame (char* name)`
  - `G_DoLoadGame` (function, line 1546) `void G_DoLoadGame (void)`
  - `G_SaveGame` (function, line 1600) `void
G_SaveGame
( int	slot,
  char*	description )`
  - `G_DoSaveGame` (function, line 1609) `void G_DoSaveGame (void)`
  - `G_DeferedInitNew` (function, line 1696) `void
G_DeferedInitNew
( skill_t	skill,
  int		episode,
  int		map)`
  - `G_DoNewGame` (function, line 1708) `void G_DoNewGame (void)`
  - `G_InitNew` (function, line 1724) `void
G_InitNew
( skill_t	skill,
  int		episode,
  int		map )`
  - `G_ReadDemoTiccmd` (function, line 1896) `void G_ReadDemoTiccmd (ticcmd_t* cmd)`
  - `IncreaseDemoBuffer` (function, line 1925) `static void IncreaseDemoBuffer(void)`
  - `G_WriteDemoTiccmd` (function, line 1955) `void G_WriteDemoTiccmd (ticcmd_t* cmd)`
  - `G_RecordDemo` (function, line 2010) `void G_RecordDemo (char *name)`
  - `G_VanillaVersionCode` (function, line 2040) `int G_VanillaVersionCode(void)`
  - `G_BeginRecording` (function, line 2057) `void G_BeginRecording (void)`
  - `G_DeferedPlayDemo` (function, line 2106) `void G_DeferedPlayDemo (char* name)`
  - `DemoVersionDescription` (function, line 2114) `static char *DemoVersionDescription(int version)`
  - `G_DoPlayDemo` (function, line 2151) `void G_DoPlayDemo (void)`
  - `G_TimeDemo` (function, line 2215) `void G_TimeDemo (char* name)`
  - `G_CheckDemoStatus` (function, line 2242) `boolean G_CheckDemoStatus (void)`
  - `SAVEGAMESIZE` (macro, line 74)
  - `MAXPLMOVE` (macro, line 151)
  - `TURBOTHRESHOLD` (macro, line 153)
  - `SLOWTURNTICS` (macro, line 192)
  - `NUMKEYS` (macro, line 194)
  - `MAX_JOY_BUTTONS` (macro, line 196)
  - `BODYQUESIZE` (macro, line 224)
  - `VERSIONSIZE` (macro, line 1544)
  - `DEMOMARKER` (macro, line 1895)

## progs/doomgeneric/g_game.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__G_GAME__` (macro, line 21)

## progs/doomgeneric/gusconf.c
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: c
- Symbols:
  - `MappingIndex` (function, line 42) `static unsigned int MappingIndex(void)`
  - `SplitLine` (function, line 60) `static int SplitLine(char *line, char **fields, unsigned int max_fields)`
  - `ParseLine` (function, line 107) `static void ParseLine(gus_config_t *config, char *line)`
  - `ParseDMXConfig` (function, line 128) `static void ParseDMXConfig(char *dmxconf, gus_config_t *config)`
  - `FreeDMXConfig` (function, line 164) `static void FreeDMXConfig(gus_config_t *config)`
  - `ReadDMXConfig` (function, line 174) `static char *ReadDMXConfig(void)`
  - `WriteTimidityConfig` (function, line 196) `static boolean WriteTimidityConfig(char *path, gus_config_t *config)`
  - `GUS_WriteConfig` (function, line 243) `boolean GUS_WriteConfig(char *path)`
  - `MAX_INSTRUMENTS` (macro, line 31)

## progs/doomgeneric/gusconf.h
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `__GUSCONF_H__` (macro, line 19)

## progs/doomgeneric/hu_lib.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `HUlib_init` (function, line 35) `void HUlib_init(void)`
  - `HUlib_clearTextLine` (function, line 39) `void HUlib_clearTextLine(hu_textline_t* t)`
  - `HUlib_initTextLine` (function, line 46) `void
HUlib_initTextLine
( hu_textline_t*	t,
  int			x,
  int			y,
  patch_t**		f,
  int			sc )`
  - `HUlib_addCharToTextLine` (function, line 61) `boolean
HUlib_addCharToTextLine
( hu_textline_t*	t,
  char			ch )`
  - `HUlib_delCharFromTextLine` (function, line 79) `boolean HUlib_delCharFromTextLine(hu_textline_t* t)`
  - `HUlib_drawTextLine` (function, line 92) `void
HUlib_drawTextLine
( hu_textline_t*	l,
  boolean		drawcursor )`
  - `HUlib_eraseTextLine` (function, line 137) `void HUlib_eraseTextLine(hu_textline_t* l)`
  - `HUlib_initSText` (function, line 167) `void
HUlib_initSText
( hu_stext_t*	s,
  int		x,
  int		y,
  int		h,
  patch_t**	font,
  int		star...`
  - `HUlib_addLineToSText` (function, line 191) `void HUlib_addLineToSText(hu_stext_t* s)`
  - `HUlib_addMessageToSText` (function, line 207) `void
HUlib_addMessageToSText
( hu_stext_t*	s,
  char*		prefix,
  char*		msg )`
  - `HUlib_drawSText` (function, line 222) `void HUlib_drawSText(hu_stext_t* s)`
  - `HUlib_eraseSText` (function, line 245) `void HUlib_eraseSText(hu_stext_t* s)`
  - `HUlib_initIText` (function, line 260) `void
HUlib_initIText
( hu_itext_t*	it,
  int		x,
  int		y,
  patch_t**	font,
  int		startchar,
  ...`
  - `HUlib_delCharFromIText` (function, line 278) `void HUlib_delCharFromIText(hu_itext_t* it)`
  - `HUlib_eraseLineFromIText` (function, line 283) `void HUlib_eraseLineFromIText(hu_itext_t* it)`
  - `HUlib_resetIText` (function, line 291) `void HUlib_resetIText(hu_itext_t* it)`
  - `HUlib_addPrefixToIText` (function, line 296) `void
HUlib_addPrefixToIText
( hu_itext_t*	it,
  char*		str )`
  - `HUlib_keyInIText` (function, line 309) `boolean
HUlib_keyInIText
( hu_itext_t*	it,
  unsigned char ch )`
  - `HUlib_drawIText` (function, line 328) `void HUlib_drawIText(hu_itext_t* it)`
  - `HUlib_eraseIText` (function, line 339) `void HUlib_eraseIText(hu_itext_t* it)`
  - `noterased` (macro, line 32)

## progs/doomgeneric/hu_lib.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__HULIB__` (macro, line 19)
  - `HU_CHARERASE` (macro, line 25)
  - `HU_MAXLINES` (macro, line 26)
  - `HU_MAXLINELENGTH` (macro, line 28)

## progs/doomgeneric/hu_stuff.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `HU_Init` (function, line 285) `void HU_Init(void)`
  - `HU_Stop` (function, line 302) `void HU_Stop(void)`
  - `HU_Start` (function, line 307) `void HU_Start(void)`
  - `HU_Drawer` (function, line 382) `void HU_Drawer(void)`
  - `HU_Erase` (function, line 392) `void HU_Erase(void)`
  - `HU_Ticker` (function, line 401) `void HU_Ticker(void)`
  - `HU_queueChatChar` (function, line 480) `void HU_queueChatChar(char c)`
  - `HU_dequeueChatChar` (function, line 494) `char HU_dequeueChatChar(void)`
  - `HU_Responder` (function, line 511) `boolean HU_Responder(event_t *ev)`
  - `HU_TITLE` (macro, line 47)
  - `HU_TITLE2` (macro, line 48)
  - `HU_TITLEP` (macro, line 49)
  - `HU_TITLET` (macro, line 50)
  - `HU_TITLE_CHEX` (macro, line 51)
  - `HU_TITLEHEIGHT` (macro, line 52)
  - `HU_TITLEX` (macro, line 53)
  - `HU_TITLEY` (macro, line 54)
  - `HU_INPUTTOGGLE` (macro, line 55)
  - `HU_INPUTX` (macro, line 57)
  - `HU_INPUTY` (macro, line 58)
  - `HU_INPUTWIDTH` (macro, line 59)
  - `HU_INPUTHEIGHT` (macro, line 60)
  - `QUEUESIZE` (macro, line 474)

## progs/doomgeneric/hu_stuff.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__HU_STUFF_H__` (macro, line 19)
  - `HU_FONTSTART` (macro, line 27)
  - `HU_FONTEND` (macro, line 28)
  - `HU_FONTSIZE` (macro, line 31)
  - `HU_BROADCAST` (macro, line 32)
  - `HU_MSGX` (macro, line 34)
  - `HU_MSGY` (macro, line 36)
  - `HU_MSGWIDTH` (macro, line 37)
  - `HU_MSGHEIGHT` (macro, line 38)
  - `HU_MSGTIMEOUT` (macro, line 39)

## progs/doomgeneric/i_cdmus.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software  This program is free software; you can r
- Language: c
- Symbols:
  - `I_CDMusInit` (function, line 37) `int I_CDMusInit(void)`
  - `I_CDMusPrintStartup` (function, line 91) `void I_CDMusPrintStartup(void)`
  - `I_CDMusPlay` (function, line 106) `int I_CDMusPlay(int track)`
  - `I_CDMusStop` (function, line 129) `int I_CDMusStop(void)`
  - `I_CDMusResume` (function, line 144) `int I_CDMusResume(void)`
  - `I_CDMusSetVolume` (function, line 159) `int I_CDMusSetVolume(int volume)`
  - `I_CDMusFirstTrack` (function, line 168) `int I_CDMusFirstTrack(void)`
  - `I_CDMusLastTrack` (function, line 201) `int I_CDMusLastTrack(void)`
  - `I_CDMusTrackLength` (function, line 218) `int I_CDMusTrackLength(int track_num)`

## progs/doomgeneric/i_cdmus.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software  This program is free software; you can r
- Language: h
- Symbols:
  - `__ICDMUS__` (macro, line 19)
  - `CDERR_NOTINSTALLED` (macro, line 20)
  - `CDERR_NOAUDIOSUPPORT` (macro, line 22)
  - `CDERR_NOAUDIOTRACKS` (macro, line 23)
  - `CDERR_BADDRIVE` (macro, line 24)
  - `CDERR_BADTRACK` (macro, line 25)
  - `CDERR_IOCTLBUFFMEM` (macro, line 26)
  - `CDERR_DEVREQBASE` (macro, line 27)

## progs/doomgeneric/i_endoom.c
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: c
- Symbols:
  - `I_Endoom` (function, line 35) `void I_Endoom(byte *endoom_data)`
  - `ENDOOM_W` (macro, line 28)
  - `ENDOOM_H` (macro, line 30)

## progs/doomgeneric/i_endoom.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__I_ENDOOM__` (macro, line 21)

## progs/doomgeneric/i_input.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `TranslateKey` (function, line 223) `static unsigned char TranslateKey(unsigned char key)`
  - `GetTypedChar` (function, line 241) `static unsigned char GetTypedChar(unsigned char key)`
  - `UpdateShiftStatus` (function, line 262) `static void UpdateShiftStatus(int pressed, unsigned char key)`
  - `I_GetEvent` (function, line 277) `void I_GetEvent(void)`
  - `I_InitInput` (function, line 337) `void I_InitInput(void)`

## progs/doomgeneric/i_joystick.c
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: c
- Symbols:
  - `I_ShutdownJoystick` (function, line 76) `void I_ShutdownJoystick(void)`
  - `IsValidAxis` (function, line 90) `static boolean IsValidAxis(int axis)`
  - `I_InitJoystick` (function, line 114) `void I_InitJoystick(void)`
  - `IsAxisButton` (function, line 171) `static boolean IsAxisButton(int physbutton)`
  - `ReadButtonState` (function, line 202) `static int ReadButtonState(int vbutton)`
  - `GetButtonsState` (function, line 227) `static int GetButtonsState(void)`
  - `GetAxisState` (function, line 247) `static int GetAxisState(int axis, int invert)`
  - `I_UpdateJoystick` (function, line 321) `void I_UpdateJoystick(void)`
  - `I_BindJoystickVariables` (function, line 338) `void I_BindJoystickVariables(void)`
  - `DEAD_ZONE` (macro, line 37)

## progs/doomgeneric/i_joystick.h
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `__I_JOYSTICK__` (macro, line 20)
  - `NUM_VIRTUAL_BUTTONS` (macro, line 25)
  - `BUTTON_AXIS` (macro, line 33)
  - `IS_BUTTON_AXIS` (macro, line 36)
  - `BUTTON_AXIS_NEG` (macro, line 39)
  - `BUTTON_AXIS_POS` (macro, line 40)
  - `CREATE_BUTTON_AXIS` (macro, line 43)
  - `HAT_AXIS` (macro, line 48)
  - `IS_HAT_AXIS` (macro, line 49)
  - `HAT_AXIS_HAT` (macro, line 53)
  - `HAT_AXIS_DIRECTION` (macro, line 55)
  - `CREATE_HAT_AXIS` (macro, line 56)
  - `HAT_AXIS_HORIZONTAL` (macro, line 59)
  - `HAT_AXIS_VERTICAL` (macro, line 61)

## progs/doomgeneric/i_main.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `main` (function, line 38) `int main(int argc, char **argv)`

## progs/doomgeneric/i_minios_sound.c
- Layer: utility
- Doc: include <stdio.h> include <stdlib.h> include <string.h> include "doomtype.h" include "doomfeatures.h" include "i_sound.h
- Language: c
- Symbols:
  - `sys_tone` (function, line 31) `static long sys_tone(unsigned f)`
  - `sys_time` (function, line 35) `static long sys_time(void)`
  - `mus_read_varlen` (function, line 100) `static int mus_read_varlen(mus_player_t *m, unsigned long *out)`
  - `mus_next_block` (function, line 115) `static int mus_next_block(mus_player_t *m, unsigned long *out)`
  - `mus_note_cmp` (function, line 153) `static int mus_note_cmp(const void *a, const void *b)`
  - `mus_build_chord` (function, line 162) `static void mus_build_chord(mus_player_t *m)`
  - `mus_hold_tone` (function, line 185) `static void mus_hold_tone(unsigned freq, unsigned long ms)`
  - `mus_play_chord` (function, line 196) `static void mus_play_chord(mus_player_t *m)`
  - `mus_advance` (function, line 209) `static void mus_advance(mus_player_t *m, unsigned long ms)`
  - `MUS_Init` (function, line 230) `static boolean MUS_Init(void)`
  - `MUS_Shutdown` (function, line 235) `static void MUS_Shutdown(void)`
  - `MUS_SetMusicVolume` (function, line 240) `static void MUS_SetMusicVolume(int volume)`
  - `MUS_Pause` (function, line 242) `static void MUS_Pause(void)`
  - `MUS_Resume` (function, line 244) `static void MUS_Resume(void)`
  - `MUS_RegisterSong` (function, line 245) `static void *MUS_RegisterSong(void *data, int len)`
  - `MUS_UnRegisterSong` (function, line 260) `static void MUS_UnRegisterSong(void *handle)`
  - `MUS_PlaySong` (function, line 266) `static void MUS_PlaySong(void *handle, boolean looping)`
  - `MUS_StopSong` (function, line 279) `static void MUS_StopSong(void)`
  - `MUS_MusicIsPlaying` (function, line 284) `static boolean MUS_MusicIsPlaying(void)`
  - `MUS_Poll` (function, line 288) `static void MUS_Poll(void)`
  - `PCSPK_Init` (function, line 317) `static boolean PCSPK_Init(boolean use_sfx_prefix)`
  - `PCSPK_Shutdown` (function, line 324) `static void PCSPK_Shutdown(void)`
  - `PCSPK_GetSfxLumpNum` (function, line 329) `static int PCSPK_GetSfxLumpNum(sfxinfo_t *sfx)`
  - `free_channel` (function, line 340) `static void free_channel(int i)`
  - `PCSPK_Update` (function, line 349) `static void PCSPK_Update(void)`
  - `PCSPK_UpdateSoundParams` (function, line 381) `static void PCSPK_UpdateSoundParams(int ch, int v, int s)`
  - `PCSPK_StartSound` (function, line 385) `static int PCSPK_StartSound(sfxinfo_t *sfx, int channel, int vol, int sep)`
  - `PCSPK_StopSound` (function, line 435) `static void PCSPK_StopSound(int channel)`
  - `PCSPK_SoundIsPlaying` (function, line 441) `static boolean PCSPK_SoundIsPlaying(int channel)`
  - `PCSPK_CacheSounds` (function, line 447) `static void PCSPK_CacheSounds(sfxinfo_t *s, int n)`
  - `PCSPK_CHANNELS` (macro, line 11)
  - `PCSPK_TICK_MS` (macro, line 13)
  - `MUS_TICKS_PER_SEC` (macro, line 57)
  - `MUS_PERCUSSION_CHAN` (macro, line 59)
  - `MUS_ARP_SLOT_MS` (macro, line 60)
  - `MUS_BASS_HOLD_MS` (macro, line 61)
  - `MUS_BASS_LINE_MIDI` (macro, line 62)
  - `MUS_ARP_MAX` (macro, line 63)

## progs/doomgeneric/i_scale.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `I_InitScale` (function, line 60) `void I_InitScale(byte *_src_buffer, byte *_dest_buffer, int _dest_pitch)`
  - `I_Scale1x` (function, line 74) `static boolean I_Scale1x(int x1, int y1, int x2, int y2)`
  - `I_Scale2x` (function, line 104) `static boolean I_Scale2x(int x1, int y1, int x2, int y2)`
  - `I_Scale3x` (function, line 145) `static boolean I_Scale3x(int x1, int y1, int x2, int y2)`
  - `I_Scale4x` (function, line 190) `static boolean I_Scale4x(int x1, int y1, int x2, int y2)`
  - `I_Scale5x` (function, line 239) `static boolean I_Scale5x(int x1, int y1, int x2, int y2)`
  - `FindNearestColor` (function, line 294) `static int FindNearestColor(byte *palette, int r, int g, int b)`
  - `GenerateStretchTable` (function, line 331) `static byte *GenerateStretchTable(byte *palette, int pct)`
  - `I_InitStretchTables` (function, line 360) `static void I_InitStretchTables(byte *palette)`
  - `I_InitSquashTable` (function, line 386) `static void I_InitSquashTable(byte *palette)`
  - `I_ResetScaleTables` (function, line 403) `void I_ResetScaleTables(byte *palette)`
  - `WriteBlendedLine1x` (function, line 433) `static inline void WriteBlendedLine1x(byte *dest, byte *src1, byte *src2, 
                      ...`
  - `I_Stretch1x` (function, line 449) `static boolean I_Stretch1x(int x1, int y1, int x2, int y2)`
  - `WriteLine2x` (function, line 506) `static inline void WriteLine2x(byte *dest, byte *src)`
  - `WriteBlendedLine2x` (function, line 519) `static inline void WriteBlendedLine2x(byte *dest, byte *src1, byte *src2, 
                      ...`
  - `I_Stretch2x` (function, line 538) `static boolean I_Stretch2x(int x1, int y1, int x2, int y2)`
  - `WriteLine3x` (function, line 619) `static inline void WriteLine3x(byte *dest, byte *src)`
  - `WriteBlendedLine3x` (function, line 633) `static inline void WriteBlendedLine3x(byte *dest, byte *src1, byte *src2, 
                      ...`
  - `I_Stretch3x` (function, line 653) `static boolean I_Stretch3x(int x1, int y1, int x2, int y2)`
  - `WriteLine4x` (function, line 758) `static inline void WriteLine4x(byte *dest, byte *src)`
  - `WriteBlendedLine4x` (function, line 773) `static inline void WriteBlendedLine4x(byte *dest, byte *src1, byte *src2, 
                      ...`
  - `I_Stretch4x` (function, line 794) `static boolean I_Stretch4x(int x1, int y1, int x2, int y2)`
  - `WriteLine5x` (function, line 923) `static inline void WriteLine5x(byte *dest, byte *src)`
  - `I_Stretch5x` (function, line 941) `static boolean I_Stretch5x(int x1, int y1, int x2, int y2)`
  - `WriteSquashedLine1x` (function, line 1029) `static inline void WriteSquashedLine1x(byte *dest, byte *src)`
  - `I_Squash1x` (function, line 1060) `static boolean I_Squash1x(int x1, int y1, int x2, int y2)`
  - `WriteSquashedLine2x` (function, line 1101) `static inline void WriteSquashedLine2x(byte *dest, byte *src)`
  - `I_Squash2x` (function, line 1159) `static boolean I_Squash2x(int x1, int y1, int x2, int y2)`
  - `WriteSquashedLine3x` (function, line 1196) `static inline void WriteSquashedLine3x(byte *dest, byte *src)`
  - `I_Squash3x` (function, line 1242) `static boolean I_Squash3x(int x1, int y1, int x2, int y2)`
  - `WriteSquashedLine4x` (function, line 1278) `static inline void WriteSquashedLine4x(byte *dest, byte *src)`
  - `I_Squash4x` (function, line 1353) `static boolean I_Squash4x(int x1, int y1, int x2, int y2)`
  - `WriteSquashedLine5x` (function, line 1389) `static inline void WriteSquashedLine5x(byte *dest, byte *src)`
  - `I_Squash5x` (function, line 1418) `static boolean I_Squash5x(int x1, int y1, int x2, int y2)`
  - `inline` (macro, line 32)
  - `DRAW_PIXEL2` (macro, line 1098)
  - `DRAW_PIXEL3` (macro, line 1192)
  - `DRAW_PIXEL4` (macro, line 1275)
  - `DRAW_PIXEL5` (macro, line 1386)

## progs/doomgeneric/i_scale.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__I_SCALE__` (macro, line 21)

## progs/doomgeneric/i_sound.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `SndDeviceInList` (function, line 115) `static boolean SndDeviceInList(snddevice_t device, snddevice_t *list,
                           ...`
  - `InitSfxModule` (function, line 134) `static void InitSfxModule(boolean use_sfx_prefix)`
  - `InitMusicModule` (function, line 162) `static void InitMusicModule(void)`
  - `I_InitSound` (function, line 194) `void I_InitSound(boolean use_sfx_prefix)`
  - `I_ShutdownSound` (function, line 249) `void I_ShutdownSound(void)`
  - `I_GetSfxLumpNum` (function, line 262) `int I_GetSfxLumpNum(sfxinfo_t *sfxinfo)`
  - `I_UpdateSound` (function, line 274) `void I_UpdateSound(void)`
  - `CheckVolumeSeparation` (function, line 287) `static void CheckVolumeSeparation(int *vol, int *sep)`
  - `I_UpdateSoundParams` (function, line 308) `void I_UpdateSoundParams(int channel, int vol, int sep)`
  - `I_StartSound` (function, line 317) `int I_StartSound(sfxinfo_t *sfxinfo, int channel, int vol, int sep)`
  - `I_StopSound` (function, line 330) `void I_StopSound(int channel)`
  - `I_SoundIsPlaying` (function, line 338) `boolean I_SoundIsPlaying(int channel)`
  - `I_PrecacheSounds` (function, line 350) `void I_PrecacheSounds(sfxinfo_t *sounds, int num_sounds)`
  - `I_InitMusic` (function, line 358) `void I_InitMusic(void)`
  - `I_ShutdownMusic` (function, line 362) `void I_ShutdownMusic(void)`
  - `I_SetMusicVolume` (function, line 367) `void I_SetMusicVolume(int volume)`
  - `I_PauseSong` (function, line 375) `void I_PauseSong(void)`
  - `I_ResumeSong` (function, line 383) `void I_ResumeSong(void)`
  - `I_RegisterSong` (function, line 391) `void *I_RegisterSong(void *data, int len)`
  - `I_UnRegisterSong` (function, line 403) `void I_UnRegisterSong(void *handle)`
  - `I_PlaySong` (function, line 411) `void I_PlaySong(void *handle, boolean looping)`
  - `I_StopSong` (function, line 419) `void I_StopSong(void)`
  - `I_MusicIsPlaying` (function, line 427) `boolean I_MusicIsPlaying(void)`
  - `I_BindSoundVariables` (function, line 439) `void I_BindSoundVariables(void)`

## progs/doomgeneric/i_sound.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `sfxinfo_struct` (struct, line 31)
  - `__I_SOUND__` (macro, line 21)

## progs/doomgeneric/i_swap.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__I_SWAP__` (macro, line 21)
  - `SHORT` (macro, line 33)
  - `LONG` (macro, line 35)
  - `SYS_LITTLE_ENDIAN` (macro, line 40)
  - `SYS_BIG_ENDIAN` (macro, line 42)
  - `SHORT` (macro, line 46)
  - `LONG` (macro, line 48)
  - `SYS_LITTLE_ENDIAN` (macro, line 49)

## progs/doomgeneric/i_system.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `atexit_listentry_s` (struct, line 64)
  - `I_AtExit` (function, line 72) `void I_AtExit(atexit_func_t func, boolean run_on_error)`
  - `I_Tactile` (function, line 86) `void I_Tactile(int on, int off, int total)`
  - `AutoAllocMemory` (function, line 94) `static byte *AutoAllocMemory(int *size, int default_ram, int min_ram)`
  - `I_ZoneBase` (function, line 132) `byte *I_ZoneBase (int *size)`
  - `I_PrintBanner` (function, line 165) `void I_PrintBanner(char *msg)`
  - `I_PrintDivider` (function, line 176) `void I_PrintDivider(void)`
  - `I_PrintStartupBanner` (function, line 188) `void I_PrintStartupBanner(char *gamedescription)`
  - `I_ConsoleStdout` (function, line 209) `boolean I_ConsoleStdout(void)`
  - `I_Quit` (function, line 245) `void I_Quit (void)`
  - `ZenityAvailable` (function, line 271) `static int ZenityAvailable(void)`
  - `EscapeShellString` (function, line 279) `static char *EscapeShellString(char *string)`
  - `ZenityErrorBox` (function, line 322) `static int ZenityErrorBox(char *message)`
  - `I_Error` (function, line 358) `void I_Error (char *error, ...)`
  - `I_GetMemoryValue` (function, line 501) `boolean I_GetMemoryValue(unsigned int offset, void *value, int size)`
  - `WIN32_LEAN_AND_MEAN` (macro, line 27)
  - `DEFAULT_RAM` (macro, line 57)
  - `MIN_RAM` (macro, line 59)
  - `ZENITY_BINARY` (macro, line 268)
  - `DOS_MEM_DUMP_SIZE` (macro, line 489)

## progs/doomgeneric/i_system.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__I_SYSTEM__` (macro, line 21)

## progs/doomgeneric/i_timer.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `I_GetTicks` (function, line 35) `int I_GetTicks(void)`
  - `I_GetTime` (function, line 41) `int  I_GetTime (void)`
  - `I_GetTimeMS` (function, line 60) `int I_GetTimeMS(void)`
  - `I_Sleep` (function, line 74) `void I_Sleep(int ms)`
  - `I_WaitVBL` (function, line 82) `void I_WaitVBL(int count)`
  - `I_InitTimer` (function, line 87) `void I_InitTimer(void)`

## progs/doomgeneric/i_timer.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__I_TIMER__` (macro, line 21)
  - `TICRATE` (macro, line 22)

## progs/doomgeneric/i_video.c
- Layer: utility
- Doc: Emacs style mode select   -*- C++ -*- -----------------------------------------------------------------------------  $Id
- Language: c
- Symbols:
  - `FB_BitField` (struct, line 54)
  - `FB_ScreenInfo` (struct, line 60)
  - `color` (struct, line 80)
  - `cmap_to_rgb565` (function, line 130) `void cmap_to_rgb565(uint16_t * out, uint8_t * in, int in_pixels)`
  - `cmap_to_fb` (function, line 151) `void cmap_to_fb(uint8_t * out, uint8_t * in, int in_pixels)`
  - `I_InitGraphics` (function, line 178) `void I_InitGraphics (void)`
  - `I_ShutdownGraphics` (function, line 231) `void I_ShutdownGraphics (void)`
  - `I_StartFrame` (function, line 236) `void I_StartFrame (void)`
  - `I_StartTic` (function, line 241) `void I_StartTic (void)`
  - `I_UpdateNoBlit` (function, line 246) `void I_UpdateNoBlit (void)`
  - `I_FinishUpdate` (function, line 254) `void I_FinishUpdate (void)`
  - `I_ReadScreen` (function, line 302) `void I_ReadScreen (byte* scr)`
  - `I_SetPalette` (function, line 314) `void I_SetPalette (byte* palette)`
  - `I_GetPaletteIndex` (function, line 332) `int I_GetPaletteIndex (int r, int g, int b)`
  - `I_BeginRead` (function, line 368) `void I_BeginRead (void)`
  - `I_EndRead` (function, line 372) `void I_EndRead (void)`
  - `I_SetWindowTitle` (function, line 376) `void I_SetWindowTitle (char *title)`
  - `I_GraphicsCheckCommandLine` (function, line 381) `void I_GraphicsCheckCommandLine (void)`
  - `I_SetGrabMouseCallback` (function, line 385) `void I_SetGrabMouseCallback (grabmouse_callback_t func)`
  - `I_EnableLoadingDisk` (function, line 389) `void I_EnableLoadingDisk(void)`
  - `I_BindVideoVariables` (function, line 393) `void I_BindVideoVariables (void)`
  - `I_DisplayFPSDots` (function, line 397) `void I_DisplayFPSDots (boolean dots_on)`
  - `I_CheckIsScreensaver` (function, line 401) `void I_CheckIsScreensaver (void)`
  - `GFX_RGB565` (macro, line 310)
  - `GFX_RGB565_R` (macro, line 311)
  - `GFX_RGB565_G` (macro, line 312)
  - `GFX_RGB565_B` (macro, line 313)

## progs/doomgeneric/i_video.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__I_VIDEO__` (macro, line 21)
  - `SCREENWIDTH` (macro, line 26)
  - `SCREENHEIGHT` (macro, line 28)
  - `SCREENWIDTH_4_3` (macro, line 31)
  - `SCREENHEIGHT_4_3` (macro, line 35)
  - `MAX_MOUSE_BUTTONS` (macro, line 37)

## progs/doomgeneric/icon.c
- Layer: utility
- Language: c

## progs/doomgeneric/info.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c

## progs/doomgeneric/info.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__INFO__` (macro, line 22)

## progs/doomgeneric/m_argv.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `M_CheckParmWithArgs` (function, line 42) `int M_CheckParmWithArgs(char *check, int num_args)`
  - `M_ParmExists` (function, line 62) `boolean M_ParmExists(char *check)`
  - `M_CheckParm` (function, line 67) `int M_CheckParm(char *check)`
  - `LoadResponseFile` (function, line 74) `static void LoadResponseFile(int argv_index)`
  - `M_FindResponseFile` (function, line 234) `void M_FindResponseFile(void)`
  - `M_GetExecutableName` (function, line 249) `char *M_GetExecutableName(void)`
  - `MAXARGVS` (macro, line 72)

## progs/doomgeneric/m_argv.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__M_ARGV__` (macro, line 21)

## progs/doomgeneric/m_bbox.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `M_ClearBox` (function, line 25) `void M_ClearBox (fixed_t *box)`
  - `M_AddToBox` (function, line 34) `void
M_AddToBox
( fixed_t*	box,
  fixed_t	x,
  fixed_t	y )`

## progs/doomgeneric/m_bbox.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__M_BBOX__` (macro, line 21)

## progs/doomgeneric/m_cheat.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `cht_CheckCheat` (function, line 34) `int
cht_CheckCheat
( cheatseq_t*	cht,
  char		key )`
  - `cht_GetParam` (function, line 80) `void
cht_GetParam
( cheatseq_t*	cht,
  char*		buffer )`

## progs/doomgeneric/m_cheat.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__M_CHEAT__` (macro, line 21)
  - `CHEAT` (macro, line 28)
  - `MAX_CHEAT_LEN` (macro, line 31)
  - `MAX_CHEAT_PARAMS` (macro, line 33)

## progs/doomgeneric/m_config.c
- Layer: infrastructure
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software Copyright(C) 2005-2014 Simon Howard  This
- Language: c
- Symbols:
  - `SearchCollection` (function, line 1562) `static default_t *SearchCollection(default_collection_t *collection, char *name)`
  - `SaveDefaultCollection` (function, line 1607) `static void SaveDefaultCollection(default_collection_t *collection)`
  - `ParseIntParameter` (function, line 1715) `static int ParseIntParameter(char *strparm)`
  - `SetVariable` (function, line 1727) `static void SetVariable(default_t *def, char *value)`
  - `LoadDefaultCollection` (function, line 1770) `static void LoadDefaultCollection(default_collection_t *collection)`
  - `M_SetConfigFilenames` (function, line 1835) `void M_SetConfigFilenames(char *main_config, char *extra_config)`
  - `M_SaveDefaults` (function, line 1845) `void M_SaveDefaults (void)`
  - `M_SaveDefaultsAlternate` (function, line 1855) `void M_SaveDefaultsAlternate(char *main, char *extra)`
  - `M_LoadDefaults` (function, line 1880) `void M_LoadDefaults (void)`
  - `GetDefaultForName` (function, line 1936) `static default_t *GetDefaultForName(char *name)`
  - `M_BindVariable` (function, line 1963) `void M_BindVariable(char *name, void *location)`
  - `M_SetVariable` (function, line 1976) `boolean M_SetVariable(char *name, char *value)`
  - `M_GetIntVariable` (function, line 1994) `int M_GetIntVariable(char *name)`
  - `M_GetStrVariable` (function, line 2009) `const char *M_GetStrVariable(char *name)`
  - `M_GetFloatVariable` (function, line 2024) `float M_GetFloatVariable(char *name)`
  - `GetDefaultConfigDir` (function, line 2042) `static char *GetDefaultConfigDir(void)`
  - `M_SetConfigDir` (function, line 2058) `void M_SetConfigDir(char *dir)`
  - `M_GetSaveGameDir` (function, line 2086) `char *M_GetSaveGameDir(char *iwadname)`
  - `CONFIG_VARIABLE_GENERIC` (macro, line 94)
  - `CONFIG_VARIABLE_KEY` (macro, line 97)
  - `CONFIG_VARIABLE_INT` (macro, line 100)
  - `CONFIG_VARIABLE_INT_HEX` (macro, line 102)
  - `CONFIG_VARIABLE_FLOAT` (macro, line 104)
  - `CONFIG_VARIABLE_STRING` (macro, line 106)

## progs/doomgeneric/m_config.h
- Layer: infrastructure
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__M_CONFIG__` (macro, line 21)

## progs/doomgeneric/m_controls.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software Copyright(C) 2005-2014 Simon Howard  This
- Language: c
- Symbols:
  - `M_BindBaseControls` (function, line 203) `void M_BindBaseControls(void)`
  - `M_BindHereticControls` (function, line 240) `void M_BindHereticControls(void)`
  - `M_BindHexenControls` (function, line 255) `void M_BindHexenControls(void)`
  - `M_BindStrifeControls` (function, line 271) `void M_BindStrifeControls(void)`
  - `M_BindWeaponControls` (function, line 306) `void M_BindWeaponControls(void)`
  - `M_BindMapControls` (function, line 327) `void M_BindMapControls(void)`
  - `M_BindMenuControls` (function, line 343) `void M_BindMenuControls(void)`
  - `M_BindChatControls` (function, line 374) `void M_BindChatControls(unsigned int num_players)`
  - `M_ApplyPlatformDefaults` (function, line 393) `void M_ApplyPlatformDefaults(void)`

## progs/doomgeneric/m_controls.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software Copyright(C) 2005-2014 Simon Howard  This
- Language: h
- Symbols:
  - `__M_CONTROLS_H__` (macro, line 18)

## progs/doomgeneric/m_fixed.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `FixedMul` (function, line 32) `fixed_t
FixedMul
( fixed_t	a,
  fixed_t	b )`
  - `FixedDiv` (function, line 46) `fixed_t FixedDiv(fixed_t a, fixed_t b)`

## progs/doomgeneric/m_fixed.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__M_FIXED__` (macro, line 21)
  - `FRACBITS` (macro, line 29)
  - `FRACUNIT` (macro, line 30)

## progs/doomgeneric/m_menu.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `menu_s` (struct, line 151)
  - `M_ReadSaveStrings` (function, line 503) `void M_ReadSaveStrings(void)`
  - `M_DrawLoad` (function, line 530) `void M_DrawLoad(void)`
  - `M_DrawSaveLoadBorder` (function, line 549) `void M_DrawSaveLoadBorder(int x,int y)`
  - `M_LoadSelect` (function, line 572) `void M_LoadSelect(int choice)`
  - `M_LoadGame` (function, line 585) `void M_LoadGame (int choice)`
  - `M_DrawSave` (function, line 601) `void M_DrawSave(void)`
  - `M_DoSave` (function, line 622) `void M_DoSave(int slot)`
  - `M_SaveSelect` (function, line 635) `void M_SaveSelect(int choice)`
  - `M_SaveGame` (function, line 650) `void M_SaveGame (int choice)`
  - `M_QuickSaveResponse` (function, line 671) `void M_QuickSaveResponse(int key)`
  - `M_QuickSave` (function, line 680) `void M_QuickSave(void)`
  - `M_QuickLoadResponse` (function, line 709) `void M_QuickLoadResponse(int key)`
  - `M_QuickLoad` (function, line 717) `void M_QuickLoad(void)`
  - `M_DrawReadThis1` (function, line 743) `void M_DrawReadThis1(void)`
  - `M_DrawReadThis2` (function, line 820) `void M_DrawReadThis2(void)`
  - `M_DrawSound` (function, line 834) `void M_DrawSound(void)`
  - `M_Sound` (function, line 844) `void M_Sound(int choice)`
  - `M_SfxVol` (function, line 849) `void M_SfxVol(int choice)`
  - `M_MusicVol` (function, line 866) `void M_MusicVol(int choice)`
  - `M_DrawMainMenu` (function, line 890) `void M_DrawMainMenu(void)`
  - `M_DrawNewGame` (function, line 902) `void M_DrawNewGame(void)`
  - `M_NewGame` (function, line 907) `void M_NewGame(int choice)`
  - `M_DrawEpisode` (function, line 929) `void M_DrawEpisode(void)`
  - `M_VerifyNightmare` (function, line 934) `void M_VerifyNightmare(int key)`
  - `M_ChooseSkill` (function, line 943) `void M_ChooseSkill(int choice)`
  - `M_Episode` (function, line 955) `void M_Episode(int choice)`
  - `M_DrawOptions` (function, line 986) `void M_DrawOptions(void)`
  - `M_Options` (function, line 1006) `void M_Options(int choice)`
  - `M_ChangeMessages` (function, line 1017) `void M_ChangeMessages(int choice)`
  - `M_EndGameResponse` (function, line 1035) `void M_EndGameResponse(int key)`
  - `M_EndGame` (function, line 1044) `void M_EndGame(int choice)`
  - `M_ReadThis` (function, line 1069) `void M_ReadThis(int choice)`
  - `M_ReadThis2` (function, line 1074) `void M_ReadThis2(int choice)`
  - `M_FinishReadThis` (function, line 1092) `void M_FinishReadThis(int choice)`
  - `M_QuitResponse` (function, line 1128) `void M_QuitResponse(int key)`
  - `M_SelectEndMessage` (function, line 1145) `static char *M_SelectEndMessage(void)`
  - `M_QuitDOOM` (function, line 1166) `void M_QuitDOOM(int choice)`
  - `M_ChangeSensitivity` (function, line 1175) `void M_ChangeSensitivity(int choice)`
  - `M_ChangeDetail` (function, line 1193) `void M_ChangeDetail(int choice)`
  - `M_SizeDisplay` (function, line 1209) `void M_SizeDisplay(int choice)`
  - `M_DrawThermo` (function, line 1243) `void
M_DrawThermo
( int	x,
  int	y,
  int	thermWidth,
  int	thermDot )`
  - `M_DrawEmptyCell` (function, line 1266) `void
M_DrawEmptyCell
( menu_t*	menu,
  int		item )`
  - `M_DrawSelCell` (function, line 1277) `void
M_DrawSelCell
( menu_t*	menu,
  int		item )`
  - `M_StartMessage` (function, line 1286) `void
M_StartMessage
( char*		string,
  void*		routine,
  boolean	input )`
  - `M_StopMessage` (function, line 1302) `void M_StopMessage(void)`
  - `M_StringWidth` (function, line 1315) `int M_StringWidth(char* string)`
  - `M_StringHeight` (function, line 1338) `int M_StringHeight(char* string)`
  - `M_WriteText` (function, line 1356) `void
M_WriteText
( int		x,
  int		y,
  char*		string)`
  - `IsNullKey` (function, line 1402) `static boolean IsNullKey(int key)`
  - `M_Responder` (function, line 1416) `boolean M_Responder (event_t* ev)`
  - `M_StartControlPanel` (function, line 1899) `void M_StartControlPanel (void)`
  - `M_DrawOPLDev` (function, line 1913) `static void M_DrawOPLDev(void)`
  - `M_Drawer` (function, line 1951) `void M_Drawer (void)`
  - `M_ClearMenus` (function, line 2041) `void M_ClearMenus (void)`
  - `M_SetupNextMenu` (function, line 2054) `void M_SetupNextMenu(menu_t *menudef)`
  - `M_Ticker` (function, line 2064) `void M_Ticker (void)`
  - `M_Init` (function, line 2077) `void M_Init (void)`
  - `SKULLXOFF` (macro, line 119)
  - `LINEHEIGHT` (macro, line 121)

## progs/doomgeneric/m_menu.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__M_MENU__` (macro, line 21)

## progs/doomgeneric/m_misc.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software Copyright(C) 2005-2014 Simon Howard  This
- Language: c
- Symbols:
  - `M_MakeDirectory` (function, line 54) `void M_MakeDirectory(char *path)`
  - `M_FileExists` (function, line 65) `boolean M_FileExists(char *filename)`
  - `M_FileLength` (function, line 88) `long M_FileLength(FILE *handle)`
  - `M_WriteFile` (function, line 110) `boolean M_WriteFile(char *name, void *source, int length)`
  - `M_ReadFile` (function, line 134) `int M_ReadFile(char *name, byte **buffer)`
  - `M_TempFile` (function, line 165) `char *M_TempFile(char *s)`
  - `M_StrToInt` (function, line 188) `boolean M_StrToInt(const char *str, int *result)`
  - `M_ExtractFileBase` (function, line 196) `void M_ExtractFileBase(char *path, char *dest)`
  - `M_ForceUppercase` (function, line 241) `void M_ForceUppercase(char *text)`
  - `M_StrCaseStr` (function, line 257) `char *M_StrCaseStr(char *haystack, char *needle)`
  - `M_StringDuplicate` (function, line 290) `char *M_StringDuplicate(const char *orig)`
  - `M_StringReplace` (function, line 309) `char *M_StringReplace(const char *haystack, const char *needle,
                      const char ...`
  - `M_StringCopy` (function, line 371) `boolean M_StringCopy(char *dest, const char *src, size_t dest_size)`
  - `M_StringConcat` (function, line 392) `boolean M_StringConcat(char *dest, const char *src, size_t dest_size)`
  - `M_StringStartsWith` (function, line 407) `boolean M_StringStartsWith(const char *s, const char *prefix)`
  - `M_StringEndsWith` (function, line 415) `boolean M_StringEndsWith(const char *s, const char *suffix)`
  - `M_StringJoin` (function, line 424) `char *M_StringJoin(const char *s, ...)`
  - `M_vsnprintf` (function, line 481) `int M_vsnprintf(char *buf, size_t buf_len, const char *s, va_list args)`
  - `M_snprintf` (function, line 507) `int M_snprintf(char *buf, size_t buf_len, const char *s, ...)`
  - `M_OEMToUTF8` (function, line 518) `char *M_OEMToUTF8(const char *oem)`
  - `WIN32_LEAN_AND_MEAN` (macro, line 28)
  - `vsnprintf` (macro, line 476)

## progs/doomgeneric/m_misc.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__M_MISC__` (macro, line 21)

## progs/doomgeneric/m_random.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `P_Random` (function, line 50) `int P_Random (void)`
  - `M_Random` (function, line 55) `int M_Random (void)`
  - `M_ClearRandom` (function, line 61) `void M_ClearRandom (void)`

## progs/doomgeneric/m_random.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__M_RANDOM__` (macro, line 21)

## progs/doomgeneric/memio.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `_MEMFILE` (struct, line 32)
  - `mem_fopen_read` (function, line 41) `MEMFILE *mem_fopen_read(void *buf, size_t buflen)`
  - `mem_fread` (function, line 57) `size_t mem_fread(void *buf, size_t size, size_t nmemb, MEMFILE *stream)`
  - `mem_fopen_write` (function, line 89) `MEMFILE *mem_fopen_write(void)`
  - `mem_fwrite` (function, line 106) `size_t mem_fwrite(const void *ptr, size_t size, size_t nmemb, MEMFILE *stream)`
  - `mem_get_buf` (function, line 142) `void mem_get_buf(MEMFILE *stream, void **buf, size_t *buflen)`
  - `mem_fclose` (function, line 148) `void mem_fclose(MEMFILE *stream)`
  - `mem_ftell` (function, line 158) `long mem_ftell(MEMFILE *stream)`
  - `mem_fseek` (function, line 163) `int mem_fseek(MEMFILE *stream, signed long position, mem_rel_t whence)`

## progs/doomgeneric/memio.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `MEMIO_H` (macro, line 17)

## progs/doomgeneric/net_client.h
- Layer: infrastructure
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `NET_CLIENT_H` (macro, line 18)

## progs/doomgeneric/net_dedicated.h
- Layer: infrastructure
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `NET_DEDICATED_H` (macro, line 19)

## progs/doomgeneric/net_defs.h
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `_net_packet_s` (struct, line 52)
  - `_net_module_s` (struct, line 60)
  - `_net_addr_s` (struct, line 95)
  - `NET_DEFS_H` (macro, line 19)
  - `MAXNETNODES` (macro, line 30)
  - `NET_MAXPLAYERS` (macro, line 36)
  - `MAXPLAYERNAME` (macro, line 40)
  - `BACKUPTICS` (macro, line 44)
  - `NET_MAGIC_NUMBER` (macro, line 102)
  - `NET_RELIABLE_PACKET` (macro, line 106)
  - `NET_TICDIFF_FORWARD` (macro, line 192)
  - `NET_TICDIFF_SIDE` (macro, line 194)
  - `NET_TICDIFF_TURN` (macro, line 195)
  - `NET_TICDIFF_BUTTONS` (macro, line 196)
  - `NET_TICDIFF_CONSISTANCY` (macro, line 197)
  - `NET_TICDIFF_CHATCHAR` (macro, line 198)
  - `NET_TICDIFF_RAVEN` (macro, line 199)
  - `NET_TICDIFF_STRIFE` (macro, line 200)

## progs/doomgeneric/net_gui.h
- Layer: presentation
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `NET_GUI_H` (macro, line 22)

## progs/doomgeneric/net_io.h
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `NET_IO_H` (macro, line 19)

## progs/doomgeneric/net_loop.h
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `NET_LOOP_H` (macro, line 19)

## progs/doomgeneric/net_packet.h
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `NET_PACKET_H` (macro, line 19)

## progs/doomgeneric/net_query.h
- Layer: data_access
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `NET_QUERY_H` (macro, line 19)

## progs/doomgeneric/net_sdl.h
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `NET_SDL_H` (macro, line 19)

## progs/doomgeneric/net_server.h
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `NET_SERVER_H` (macro, line 18)

## progs/doomgeneric/p_ceilng.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `T_MoveCeiling` (function, line 44) `void T_MoveCeiling (ceiling_t* ceiling)`
  - `EV_DoCeiling` (function, line 160) `int
EV_DoCeiling
( line_t*	line,
  ceiling_e	type )`
  - `P_AddActiveCeiling` (function, line 240) `void P_AddActiveCeiling(ceiling_t* c)`
  - `P_RemoveActiveCeiling` (function, line 259) `void P_RemoveActiveCeiling(ceiling_t* c)`
  - `P_ActivateInStasisCeiling` (function, line 280) `void P_ActivateInStasisCeiling(line_t* line)`
  - `EV_CeilingCrushStop` (function, line 303) `int	EV_CeilingCrushStop(line_t	*line)`

## progs/doomgeneric/p_doors.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `T_VerticalDoor` (function, line 57) `void T_VerticalDoor (vldoor_t* door)`
  - `EV_DoLockedDoor` (function, line 193) `int
EV_DoLockedDoor
( line_t*	line,
  vldoor_e	type,
  mobj_t*	thing )`
  - `EV_DoDoor` (function, line 249) `int
EV_DoDoor
( line_t*	line,
  vldoor_e	type )`
  - `EV_VerticalDoor` (function, line 336) `void
EV_VerticalDoor
( line_t*	line,
  mobj_t*	thing )`
  - `P_SpawnDoorCloseIn30` (function, line 519) `void P_SpawnDoorCloseIn30 (sector_t* sec)`
  - `P_SpawnDoorRaiseIn5Mins` (function, line 541) `void
P_SpawnDoorRaiseIn5Mins
( sector_t*	sec,
  int		secnum )`
  - `P_InitSlidingDoorFrames` (function, line 579) `void P_InitSlidingDoorFrames(void)`
  - `P_FindSlidingDoorType` (function, line 624) `int P_FindSlidingDoorType(line_t*	line)`
  - `T_SlidingDoor` (function, line 638) `void T_SlidingDoor (slidedoor_t*	door)`
  - `EV_SlidingDoor` (function, line 723) `void
EV_SlidingDoor
( line_t*	line,
  mobj_t*	thing )`

## progs/doomgeneric/p_enemy.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `P_RecursiveSound` (function, line 97) `void
P_RecursiveSound
( sector_t*	sec,
  int		soundblocks )`
  - `P_NoiseAlert` (function, line 151) `void
P_NoiseAlert
( mobj_t*	target,
  mobj_t*	emmiter )`
  - `P_CheckMeleeRange` (function, line 167) `boolean P_CheckMeleeRange (mobj_t*	actor)`
  - `P_CheckMissileRange` (function, line 190) `boolean P_CheckMissileRange (mobj_t* actor)`
  - `P_Move` (function, line 259) `boolean P_Move (mobj_t*	actor)`
  - `P_TryWalk` (function, line 337) `boolean P_TryWalk (mobj_t* actor)`
  - `P_NewChaseDir` (function, line 347) `void P_NewChaseDir (mobj_t*	actor)`
  - `P_LookForPlayers` (function, line 486) `boolean
P_LookForPlayers
( mobj_t*	actor,
  boolean	allaround )`
  - `A_KeenDie` (function, line 551) `void A_KeenDie (mobj_t* mo)`
  - `A_Look` (function, line 589) `void A_Look (mobj_t* actor)`
  - `A_Chase` (function, line 657) `void A_Chase (mobj_t*	actor)`
  - `A_FaceTarget` (function, line 767) `void A_FaceTarget (mobj_t* actor)`
  - `A_PosAttack` (function, line 787) `void A_PosAttack (mobj_t* actor)`
  - `A_SPosAttack` (function, line 805) `void A_SPosAttack (mobj_t* actor)`
  - `A_CPosAttack` (function, line 829) `void A_CPosAttack (mobj_t* actor)`
  - `A_CPosRefire` (function, line 849) `void A_CPosRefire (mobj_t* actor)`
  - `A_SpidRefire` (function, line 865) `void A_SpidRefire (mobj_t* actor)`
  - `A_BspiAttack` (function, line 882) `void A_BspiAttack (mobj_t *actor)`
  - `A_TroopAttack` (function, line 898) `void A_TroopAttack (mobj_t* actor)`
  - `A_SargAttack` (function, line 918) `void A_SargAttack (mobj_t* actor)`
  - `A_HeadAttack` (function, line 934) `void A_HeadAttack (mobj_t* actor)`
  - `A_CyberAttack` (function, line 953) `void A_CyberAttack (mobj_t* actor)`
  - `A_BruisAttack` (function, line 962) `void A_BruisAttack (mobj_t* actor)`
  - `A_SkelMissile` (function, line 987) `void A_SkelMissile (mobj_t* actor)`
  - `A_Tracer` (function, line 1005) `void A_Tracer (mobj_t* actor)`
  - `A_SkelWhoosh` (function, line 1076) `void A_SkelWhoosh (mobj_t*	actor)`
  - `A_SkelFist` (function, line 1085) `void A_SkelFist (mobj_t*	actor)`
  - `PIT_VileCheck` (function, line 1113) `boolean PIT_VileCheck (mobj_t*	thing)`
  - `A_VileChase` (function, line 1152) `void A_VileChase (mobj_t* actor)`
  - `A_VileStart` (function, line 1218) `void A_VileStart (mobj_t* actor)`
  - `A_StartFire` (function, line 1229) `void A_StartFire (mobj_t* actor)`
  - `A_FireCrackle` (function, line 1235) `void A_FireCrackle (mobj_t* actor)`
  - `A_Fire` (function, line 1241) `void A_Fire (mobj_t* actor)`
  - `A_VileTarget` (function, line 1273) `void A_VileTarget (mobj_t*	actor)`
  - `A_VileAttack` (function, line 1298) `void A_VileAttack (mobj_t* actor)`
  - `A_FatRaise` (function, line 1338) `void A_FatRaise (mobj_t *actor)`
  - `A_FatAttack1` (function, line 1344) `void A_FatAttack1 (mobj_t* actor)`
  - `A_FatAttack2` (function, line 1365) `void A_FatAttack2 (mobj_t* actor)`
  - `A_FatAttack3` (function, line 1384) `void A_FatAttack3 (mobj_t*	actor)`
  - `A_SkullAttack` (function, line 1414) `void A_SkullAttack (mobj_t* actor)`
  - `A_PainShootSkull` (function, line 1445) `void
A_PainShootSkull
( mobj_t*	actor,
  angle_t	angle )`
  - `A_PainAttack` (function, line 1508) `void A_PainAttack (mobj_t* actor)`
  - `A_PainDie` (function, line 1516) `void A_PainDie (mobj_t* actor)`
  - `A_Scream` (function, line 1525) `void A_Scream (mobj_t* actor)`
  - `A_XScream` (function, line 1566) `void A_XScream (mobj_t* actor)`
  - `A_Pain` (function, line 1572) `void A_Pain (mobj_t* actor)`
  - `A_Fall` (function, line 1578) `void A_Fall (mobj_t *actor)`
  - `A_Explode` (function, line 1594) `void A_Explode (mobj_t* thingy)`
  - `CheckBossEnd` (function, line 1604) `static boolean CheckBossEnd(mobjtype_t motype)`
  - `A_BossDeath` (function, line 1656) `void A_BossDeath (mobj_t* mo)`
  - `A_Hoof` (function, line 1755) `void A_Hoof (mobj_t* mo)`
  - `A_Metal` (function, line 1762) `void A_Metal (mobj_t* mo)`
  - `A_BabyMetal` (function, line 1768) `void A_BabyMetal (mobj_t* mo)`
  - `A_OpenShotgun2` (function, line 1774) `void
A_OpenShotgun2
( player_t*	player,
  pspdef_t*	psp )`
  - `A_LoadShotgun2` (function, line 1782) `void
A_LoadShotgun2
( player_t*	player,
  pspdef_t*	psp )`
  - `A_CloseShotgun2` (function, line 1795) `void
A_CloseShotgun2
( player_t*	player,
  pspdef_t*	psp )`
  - `A_BrainAwake` (function, line 1810) `void A_BrainAwake (mobj_t* mo)`
  - `A_BrainPain` (function, line 1839) `void A_BrainPain (mobj_t*	mo)`
  - `A_BrainScream` (function, line 1845) `void A_BrainScream (mobj_t*	mo)`
  - `A_BrainExplode` (function, line 1870) `void A_BrainExplode (mobj_t* mo)`
  - `A_BrainDie` (function, line 1892) `void A_BrainDie (mobj_t*	mo)`
  - `A_BrainSpit` (function, line 1898) `void A_BrainSpit (mobj_t*	mo)`
  - `A_SpawnSound` (function, line 1928) `void A_SpawnSound (mobj_t* mo)`
  - `A_SpawnFly` (function, line 1933) `void A_SpawnFly (mobj_t* mo)`
  - `A_PlayerScream` (function, line 1989) `void A_PlayerScream (mobj_t* mo)`
  - `FATSPREAD` (macro, line 1337)
  - `SKULLSPEED` (macro, line 1413)

## progs/doomgeneric/p_floor.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `T_MovePlane` (function, line 41) `result_e
T_MovePlane
( sector_t*	sector,
  fixed_t	speed,
  fixed_t	dest,
  boolean	crush,
  int	...`
  - `T_MoveFloor` (function, line 202) `void T_MoveFloor(floormove_t* floor)`
  - `EV_DoFloor` (function, line 250) `int
EV_DoFloor
( line_t*	line,
  floor_e	floortype )`
  - `EV_BuildStairs` (function, line 443) `int
EV_BuildStairs
( line_t*	line,
  stair_e	type )`

## progs/doomgeneric/p_inter.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `P_GiveAmmo` (function, line 64) `boolean
P_GiveAmmo
( player_t*	player,
  ammotype_t	ammo,
  int		num )`
  - `P_GiveWeapon` (function, line 159) `boolean
P_GiveWeapon
( player_t*	player,
  weapontype_t	weapon,
  boolean	dropped )`
  - `P_GiveBody` (function, line 222) `boolean
P_GiveBody
( player_t*	player,
  int		num )`
  - `P_GiveArmor` (function, line 245) `boolean
P_GiveArmor
( player_t*	player,
  int		armortype )`
  - `P_GiveCard` (function, line 267) `void
P_GiveCard
( player_t*	player,
  card_t	card )`
  - `P_GivePower` (function, line 283) `boolean
P_GivePower
( player_t*	player,
  int /*powertype_t*/	power )`
  - `P_TouchSpecialThing` (function, line 332) `void
P_TouchSpecialThing
( mobj_t*	special,
  mobj_t*	toucher )`
  - `P_KillMobj` (function, line 665) `void
P_KillMobj
( mobj_t*	source,
  mobj_t*	target )`
  - `P_DamageMobj` (function, line 778) `void
P_DamageMobj
( mobj_t*	target,
  mobj_t*	inflictor,
  mobj_t*	source,
  int 		damage )`
  - `BONUSADD` (macro, line 41)

## progs/doomgeneric/p_inter.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__P_INTER__` (macro, line 21)

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
  - `P_SpawnStrobeFlash` (function, line 173) `void
P_SpawnStrobeFlash
( sector_t*	sector,
  int		fastOrSlow,
  int		inSync )`
  - `EV_StartLightStrobing` (function, line 208) `void EV_StartLightStrobing(line_t*	line)`
  - `EV_TurnTagLightsOff` (function, line 229) `void EV_TurnTagLightsOff(line_t* line)`
  - `EV_LightTurnOn` (function, line 263) `void
EV_LightTurnOn
( line_t*	line,
  int		bright )`
  - `T_Glow` (function, line 306) `void T_Glow(glow_t*	g)`
  - `P_SpawnGlowingLight` (function, line 332) `void P_SpawnGlowingLight(sector_t*	sector)`

## progs/doomgeneric/p_local.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__P_LOCAL__` (macro, line 21)
  - `FLOATSPEED` (macro, line 26)
  - `MAXHEALTH` (macro, line 28)
  - `VIEWHEIGHT` (macro, line 31)
  - `MAPBLOCKUNITS` (macro, line 35)
  - `MAPBLOCKSIZE` (macro, line 36)
  - `MAPBLOCKSHIFT` (macro, line 37)
  - `MAPBMASK` (macro, line 38)
  - `MAPBTOFRAC` (macro, line 39)
  - `PLAYERRADIUS` (macro, line 43)
  - `MAXRADIUS` (macro, line 48)
  - `GRAVITY` (macro, line 49)
  - `MAXMOVE` (macro, line 51)
  - `USERANGE` (macro, line 52)
  - `MELEERANGE` (macro, line 54)
  - `MISSILERANGE` (macro, line 55)
  - `BASETHRESHOLD` (macro, line 58)
  - `ONFLOORZ` (macro, line 92)
  - `ONCEILINGZ` (macro, line 93)
  - `ITEMQUESIZE` (macro, line 96)
  - `MAXINTERCEPTS_ORIGINAL` (macro, line 153)
  - `MAXINTERCEPTS` (macro, line 155)
  - `PT_ADDLINES` (macro, line 178)
  - `PT_ADDTHINGS` (macro, line 180)
  - `PT_EARLYOUT` (macro, line 181)
  - `MAXSPECIALCROSS` (macro, line 218)
  - `MAXSPECIALCROSS_ORIGINAL` (macro, line 220)

## progs/doomgeneric/p_map.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard, Andrey Budko  This program is free softwar
- Language: c
- Symbols:
  - `PIT_StompThing` (function, line 97) `boolean PIT_StompThing (mobj_t* thing)`
  - `P_TeleportMove` (function, line 130) `boolean
P_TeleportMove
( mobj_t*	thing,
  fixed_t	x,
  fixed_t	y )`
  - `PIT_CheckLine` (function, line 206) `boolean PIT_CheckLine (line_t* ld)`
  - `PIT_CheckThing` (function, line 275) `boolean PIT_CheckThing (mobj_t* thing)`
  - `P_CheckPosition` (function, line 401) `boolean
P_CheckPosition
( mobj_t*	thing,
  fixed_t	x,
  fixed_t	y )`
  - `P_TryMove` (function, line 477) `boolean
P_TryMove
( mobj_t*	thing,
  fixed_t	x,
  fixed_t	y )`
  - `P_ThingHeightClip` (function, line 557) `boolean P_ThingHeightClip (mobj_t* thing)`
  - `P_HitSlideLine` (function, line 611) `void P_HitSlideLine (line_t* ld)`
  - `PTR_SlideTraverse` (function, line 663) `boolean PTR_SlideTraverse (intercept_t* in)`
  - `P_SlideMove` (function, line 722) `void P_SlideMove (mobj_t* mo)`
  - `PTR_AimTraverse` (function, line 842) `boolean
PTR_AimTraverse (intercept_t* in)`
  - `PTR_ShootTraverse` (function, line 928) `boolean PTR_ShootTraverse (intercept_t* in)`
  - `P_AimLineAttack` (function, line 1067) `fixed_t
P_AimLineAttack
( mobj_t*	t1,
  angle_t	angle,
  fixed_t	distance )`
  - `P_LineAttack` (function, line 1109) `void
P_LineAttack
( mobj_t*	t1,
  angle_t	angle,
  fixed_t	distance,
  fixed_t	slope,
  int		dama...`
  - `PTR_UseTraverse` (function, line 1141) `boolean	PTR_UseTraverse (intercept_t* in)`
  - `P_UseLines` (function, line 1177) `void P_UseLines (player_t*	player)`
  - `PIT_RadiusAttack` (function, line 1211) `boolean PIT_RadiusAttack (mobj_t* thing)`
  - `P_RadiusAttack` (function, line 1252) `void
P_RadiusAttack
( mobj_t*	spot,
  mobj_t*	source,
  int		damage )`
  - `PIT_ChangeSector` (function, line 1304) `boolean PIT_ChangeSector (mobj_t*	thing)`
  - `P_ChangeSector` (function, line 1367) `boolean
P_ChangeSector
( sector_t*	sector,
  boolean	crunch )`
  - `SpechitOverrun` (function, line 1390) `static void SpechitOverrun(line_t *ld)`
  - `DEFAULT_SPECHIT_MAGIC` (macro, line 49)

## progs/doomgeneric/p_maputl.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard Copyright(C) 2005, 2006 Andrey Budko  This 
- Language: c
- Symbols:
  - `P_AproxDistance` (function, line 42) `fixed_t
P_AproxDistance
( fixed_t	dx,
  fixed_t	dy )`
  - `P_PointOnLineSide` (function, line 60) `int
P_PointOnLineSide
( fixed_t	x,
  fixed_t	y,
  line_t*	line )`
  - `P_BoxOnLineSide` (function, line 104) `int
P_BoxOnLineSide
( fixed_t*	tmbox,
  line_t*	ld )`
  - `P_PointOnDivlineSide` (function, line 155) `int
P_PointOnDivlineSide
( fixed_t	x,
  fixed_t	y,
  divline_t*	line )`
  - `P_MakeDivline` (function, line 205) `void
P_MakeDivline
( line_t*	li,
  divline_t*	dl )`
  - `P_InterceptVector` (function, line 225) `fixed_t
P_InterceptVector
( divline_t*	v2,
  divline_t*	v1 )`
  - `P_LineOpening` (function, line 293) `void P_LineOpening (line_t* linedef)`
  - `P_UnsetThingPosition` (function, line 342) `void P_UnsetThingPosition (mobj_t* thing)`
  - `P_SetThingPosition` (function, line 390) `void
P_SetThingPosition (mobj_t* thing)`
  - `P_BlockLinesIterator` (function, line 466) `boolean
P_BlockLinesIterator
( int			x,
  int			y,
  boolean(*func)(line_t*) )`
  - `P_BlockThingsIterator` (function, line 507) `boolean
P_BlockThingsIterator
( int			x,
  int			y,
  boolean(*func)(mobj_t*) )`
  - `PIT_AddLineIntercepts` (function, line 558) `boolean
PIT_AddLineIntercepts (line_t* ld)`
  - `PIT_AddThingIntercepts` (function, line 614) `boolean PIT_AddThingIntercepts (mobj_t* thing)`
  - `P_TraverseIntercepts` (function, line 681) `boolean
P_TraverseIntercepts
( traverser_t	func,
  fixed_t	maxfrac )`
  - `InterceptsMemoryOverrun` (function, line 781) `static void InterceptsMemoryOverrun(int location, int value)`
  - `InterceptsOverrun` (function, line 826) `static void InterceptsOverrun(int num_intercepts, intercept_t *intercept)`
  - `P_PathTraverse` (function, line 860) `boolean
P_PathTraverse
( fixed_t		x1,
  fixed_t		y1,
  fixed_t		x2,
  fixed_t		y2,
  int			flags,...`

## progs/doomgeneric/p_mobj.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `P_SetMobjState` (function, line 46) `boolean
P_SetMobjState
( mobj_t*	mobj,
  statenum_t	state )`
  - `P_ExplodeMissile` (function, line 84) `void P_ExplodeMissile (mobj_t* mo)`
  - `P_XYMovement` (function, line 107) `void P_XYMovement (mobj_t* mo)`
  - `P_ZMovement` (function, line 240) `void P_ZMovement (mobj_t* mo)`
  - `P_NightmareRespawn` (function, line 382) `void
P_NightmareRespawn (mobj_t* mobj)`
  - `P_MobjThinker` (function, line 441) `void P_MobjThinker (mobj_t* mobj)`
  - `P_SpawnMobj` (function, line 505) `mobj_t*
P_SpawnMobj
( fixed_t	x,
  fixed_t	y,
  fixed_t	z,
  mobjtype_t	type )`
  - `P_RemoveMobj` (function, line 570) `void P_RemoveMobj (mobj_t* mobj)`
  - `P_RespawnSpecials` (function, line 604) `void P_RespawnSpecials (void)`
  - `P_SpawnPlayer` (function, line 668) `void P_SpawnPlayer (mapthing_t* mthing)`
  - `P_SpawnMapThing` (function, line 739) `void P_SpawnMapThing (mapthing_t* mthing)`
  - `P_SpawnPuff` (function, line 849) `void
P_SpawnPuff
( fixed_t	x,
  fixed_t	y,
  fixed_t	z )`
  - `P_SpawnBlood` (function, line 877) `void
P_SpawnBlood
( fixed_t	x,
  fixed_t	y,
  fixed_t	z,
  int		damage )`
  - `P_CheckMissileSpawn` (function, line 907) `void P_CheckMissileSpawn (mobj_t* th)`
  - `P_SubstNullMobj` (function, line 928) `mobj_t *P_SubstNullMobj(mobj_t *mobj)`
  - `P_SpawnMissile` (function, line 949) `mobj_t*
P_SpawnMissile
( mobj_t*	source,
  mobj_t*	dest,
  mobjtype_t	type )`
  - `P_SpawnPlayerMissile` (function, line 995) `void
P_SpawnPlayerMissile
( mobj_t*	source,
  mobjtype_t	type )`
  - `STOPSPEED` (macro, line 105)
  - `FRICTION` (macro, line 106)

## progs/doomgeneric/p_mobj.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `mobj_s` (struct, line 201)
  - `__P_MOBJ__` (macro, line 21)

## progs/doomgeneric/p_plats.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `T_PlatRaise` (function, line 45) `void T_PlatRaise(plat_t* plat)`
  - `EV_DoPlat` (function, line 128) `int
EV_DoPlat
( line_t*	line,
  plattype_e	type,
  int		amount )`
  - `P_ActivateInStasis` (function, line 245) `void P_ActivateInStasis(int tag)`
  - `EV_StopPlat` (function, line 262) `void EV_StopPlat(line_t* line)`
  - `P_AddActivePlat` (function, line 277) `void P_AddActivePlat(plat_t* plat)`
  - `P_RemoveActivePlat` (function, line 290) `void P_RemoveActivePlat(plat_t* plat)`

## progs/doomgeneric/p_pspr.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `P_SetPsprite` (function, line 49) `void
P_SetPsprite
( player_t*	player,
  int		position,
  statenum_t	stnum )`
  - `P_CalcSwing` (function, line 102) `void P_CalcSwing (player_t*	player)`
  - `P_BringUpWeapon` (function, line 129) `void P_BringUpWeapon (player_t* player)`
  - `P_CheckAmmo` (function, line 152) `boolean P_CheckAmmo (player_t* player)`
  - `P_FireWeapon` (function, line 237) `void P_FireWeapon (player_t* player)`
  - `P_DropWeapon` (function, line 256) `void P_DropWeapon (player_t* player)`
  - `A_WeaponReady` (function, line 272) `void
A_WeaponReady
( player_t*	player,
  pspdef_t*	psp )`
  - `A_ReFire` (function, line 334) `void A_ReFire
( player_t*	player,
  pspdef_t*	psp )`
  - `A_CheckReload` (function, line 354) `void
A_CheckReload
( player_t*	player,
  pspdef_t*	psp )`
  - `A_Lower` (function, line 375) `void
A_Lower
( player_t*	player,
  pspdef_t*	psp )`
  - `A_Raise` (function, line 413) `void
A_Raise
( player_t*	player,
  pspdef_t*	psp )`
  - `A_GunFlash` (function, line 439) `void
A_GunFlash
( player_t*	player,
  pspdef_t*	psp )`
  - `A_Punch` (function, line 458) `void
A_Punch
( player_t*	player,
  pspdef_t*	psp )`
  - `A_Saw` (function, line 492) `void
A_Saw
( player_t*	player,
  pspdef_t*	psp )`
  - `DecreaseAmmo` (function, line 541) `static void DecreaseAmmo(player_t *player, int ammonum, int amount)`
  - `A_FireMissile` (function, line 558) `void
A_FireMissile
( player_t*	player,
  pspdef_t*	psp )`
  - `A_FireBFG` (function, line 571) `void
A_FireBFG
( player_t*	player,
  pspdef_t*	psp )`
  - `A_FirePlasma` (function, line 586) `void
A_FirePlasma
( player_t*	player,
  pspdef_t*	psp )`
  - `P_BulletSlope` (function, line 608) `void P_BulletSlope (mobj_t*	mo)`
  - `P_GunShot` (function, line 634) `void
P_GunShot
( mobj_t*	mo,
  boolean	accurate )`
  - `A_FirePistol` (function, line 655) `void
A_FirePistol
( player_t*	player,
  pspdef_t*	psp )`
  - `A_FireShotgun` (function, line 677) `void
A_FireShotgun
( player_t*	player,
  pspdef_t*	psp )`
  - `A_FireShotgun2` (function, line 704) `void
A_FireShotgun2
( player_t*	player,
  pspdef_t*	psp )`
  - `A_FireCGun` (function, line 741) `void
A_FireCGun
( player_t*	player,
  pspdef_t*	psp )`
  - `A_Light0` (function, line 770) `void A_Light0 (player_t *player, pspdef_t *psp)`
  - `A_Light1` (function, line 774) `void A_Light1 (player_t *player, pspdef_t *psp)`
  - `A_Light2` (function, line 779) `void A_Light2 (player_t *player, pspdef_t *psp)`
  - `A_BFGSpray` (function, line 790) `void A_BFGSpray (mobj_t* mo)`
  - `A_BFGsound` (function, line 826) `void
A_BFGsound
( player_t*	player,
  pspdef_t*	psp )`
  - `P_SetupPsprites` (function, line 840) `void P_SetupPsprites (player_t* player)`
  - `P_MovePsprites` (function, line 860) `void P_MovePsprites (player_t* player)`
  - `LOWERSPEED` (macro, line 37)
  - `RAISESPEED` (macro, line 39)
  - `WEAPONBOTTOM` (macro, line 40)
  - `WEAPONTOP` (macro, line 42)

## progs/doomgeneric/p_pspr.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__P_PSPR__` (macro, line 21)
  - `FF_FULLBRIGHT` (macro, line 44)
  - `FF_FRAMEMASK` (macro, line 45)

## progs/doomgeneric/p_saveg.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `P_TempSaveGameFile` (function, line 46) `char *P_TempSaveGameFile(void)`
  - `P_SaveGameFile` (function, line 60) `char *P_SaveGameFile(int slot)`
  - `saveg_read8` (function, line 80) `static byte saveg_read8(void)`
  - `saveg_write8` (function, line 98) `static void saveg_write8(byte value)`
  - `saveg_read16` (function, line 111) `static short saveg_read16(void)`
  - `saveg_write16` (function, line 121) `static void saveg_write16(short value)`
  - `saveg_read32` (function, line 127) `static int saveg_read32(void)`
  - `saveg_write32` (function, line 139) `static void saveg_write32(int value)`
  - `saveg_read_pad` (function, line 149) `static void saveg_read_pad(void)`
  - `saveg_write_pad` (function, line 165) `static void saveg_write_pad(void)`
  - `saveg_readp` (function, line 184) `static void *saveg_readp(void)`
  - `saveg_writep` (function, line 189) `static void saveg_writep(void *p)`
  - `saveg_read_mapthing_t` (function, line 207) `static void saveg_read_mapthing_t(mapthing_t *str)`
  - `saveg_write_mapthing_t` (function, line 225) `static void saveg_write_mapthing_t(mapthing_t *str)`
  - `saveg_read_actionf_t` (function, line 247) `static void saveg_read_actionf_t(actionf_t *str)`
  - `saveg_write_actionf_t` (function, line 253) `static void saveg_write_actionf_t(actionf_t *str)`
  - `saveg_read_thinker_t` (function, line 272) `static void saveg_read_thinker_t(thinker_t *str)`
  - `saveg_write_thinker_t` (function, line 284) `static void saveg_write_thinker_t(thinker_t *str)`
  - `saveg_read_mobj_t` (function, line 300) `static void saveg_read_mobj_t(mobj_t *str)`
  - `saveg_write_mobj_t` (function, line 420) `static void saveg_write_mobj_t(mobj_t *str)`
  - `saveg_read_ticcmd_t` (function, line 540) `static void saveg_read_ticcmd_t(ticcmd_t *str)`
  - `saveg_write_ticcmd_t` (function, line 562) `static void saveg_write_ticcmd_t(ticcmd_t *str)`
  - `saveg_read_pspdef_t` (function, line 588) `static void saveg_read_pspdef_t(pspdef_t *str)`
  - `saveg_write_pspdef_t` (function, line 614) `static void saveg_write_pspdef_t(pspdef_t *str)`
  - `saveg_read_player_t` (function, line 640) `static void saveg_read_player_t(player_t *str)`
  - `saveg_write_player_t` (function, line 771) `static void saveg_write_player_t(player_t *str)`
  - `saveg_read_ceiling_t` (function, line 907) `static void saveg_read_ceiling_t(ceiling_t *str)`
  - `saveg_write_ceiling_t` (function, line 943) `static void saveg_write_ceiling_t(ceiling_t *str)`
  - `saveg_read_vldoor_t` (function, line 980) `static void saveg_read_vldoor_t(vldoor_t *str)`
  - `saveg_write_vldoor_t` (function, line 1010) `static void saveg_write_vldoor_t(vldoor_t *str)`
  - `saveg_read_floormove_t` (function, line 1041) `static void saveg_read_floormove_t(floormove_t *str)`
  - `saveg_write_floormove_t` (function, line 1074) `static void saveg_write_floormove_t(floormove_t *str)`
  - `saveg_read_plat_t` (function, line 1108) `static void saveg_read_plat_t(plat_t *str)`
  - `saveg_write_plat_t` (function, line 1150) `static void saveg_write_plat_t(plat_t *str)`
  - `saveg_read_lightflash_t` (function, line 1193) `static void saveg_read_lightflash_t(lightflash_t *str)`
  - `saveg_write_lightflash_t` (function, line 1220) `static void saveg_write_lightflash_t(lightflash_t *str)`
  - `saveg_read_strobe_t` (function, line 1248) `static void saveg_read_strobe_t(strobe_t *str)`
  - `saveg_write_strobe_t` (function, line 1275) `static void saveg_write_strobe_t(strobe_t *str)`
  - `saveg_read_glow_t` (function, line 1303) `static void saveg_read_glow_t(glow_t *str)`
  - `saveg_write_glow_t` (function, line 1324) `static void saveg_write_glow_t(glow_t *str)`
  - `P_WriteSaveGameHeader` (function, line 1346) `void P_WriteSaveGameHeader(char *description)`
  - `P_ReadSaveGameHeader` (function, line 1378) `boolean P_ReadSaveGameHeader(void)`
  - `P_ReadSaveGameEOF` (function, line 1418) `boolean P_ReadSaveGameEOF(void)`
  - `P_WriteSaveGameEOF` (function, line 1431) `void P_WriteSaveGameEOF(void)`
  - `P_ArchivePlayers` (function, line 1440) `void P_ArchivePlayers (void)`
  - `P_UnArchivePlayers` (function, line 1460) `void P_UnArchivePlayers (void)`
  - `P_ArchiveWorld` (function, line 1484) `void P_ArchiveWorld (void)`
  - `P_UnArchiveWorld` (function, line 1532) `void P_UnArchiveWorld (void)`
  - `P_ArchiveThinkers` (function, line 1592) `void P_ArchiveThinkers (void)`
  - `P_UnArchiveThinkers` (function, line 1620) `void P_UnArchiveThinkers (void)`
  - `P_ArchiveSpecials` (function, line 1704) `void P_ArchiveSpecials (void)`
  - `P_UnArchiveSpecials` (function, line 1793) `void P_UnArchiveSpecials (void)`
  - `SAVEGAME_EOF` (macro, line 35)
  - `VERSIONSIZE` (macro, line 37)
  - `saveg_read_enum` (macro, line 196)
  - `saveg_write_enum` (macro, line 198)
  - `saveg_read_think_t` (macro, line 265)
  - `saveg_write_think_t` (macro, line 267)

## progs/doomgeneric/p_saveg.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__P_SAVEG__` (macro, line 21)
  - `SAVESTRINGSIZE` (macro, line 26)

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
  - `PadRejectArray` (function, line 660) `static void PadRejectArray(byte *array, unsigned int len)`
  - `P_LoadReject` (function, line 711) `static void P_LoadReject(int lumpnum)`
  - `P_SetupLevel` (function, line 743) `void
P_SetupLevel
( int		episode,
  int		map,
  int		playermask,
  skill_t	skill)`
  - `P_Init` (function, line 847) `void P_Init (void)`
  - `MAX_DEATHMATCH_STARTS` (macro, line 105)

## progs/doomgeneric/p_setup.h
- Layer: infrastructure
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__P_SETUP__` (macro, line 21)

## progs/doomgeneric/p_sight.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `P_DivlineSide` (function, line 47) `int
P_DivlineSide
( fixed_t	x,
  fixed_t	y,
  divline_t*	node )`
  - `P_InterceptVector2` (function, line 101) `fixed_t
P_InterceptVector2
( divline_t*	v2,
  divline_t*	v1 )`
  - `P_CrossSubsector` (function, line 128) `boolean P_CrossSubsector (int num)`
  - `P_CrossBSPNode` (function, line 258) `boolean P_CrossBSPNode (int bspnum)`
  - `P_CheckSight` (function, line 300) `boolean
P_CheckSight
( mobj_t*	t1,
  mobj_t*	t2 )`

## progs/doomgeneric/p_spec.c
- Layer: testing
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `P_InitPicAnims` (function, line 140) `void P_InitPicAnims (void)`
  - `getSide` (function, line 202) `side_t*
getSide
( int		currentSector,
  int		line,
  int		side )`
  - `getSector` (function, line 218) `sector_t*
getSector
( int		currentSector,
  int		line,
  int		side )`
  - `twoSided` (function, line 233) `int
twoSided
( int	sector,
  int	line )`
  - `getNextSector` (function, line 249) `sector_t*
getNextSector
( line_t*	line,
  sector_t*	sec )`
  - `P_FindLowestFloorSurrounding` (function, line 269) `fixed_t	P_FindLowestFloorSurrounding(sector_t* sec)`
  - `P_FindHighestFloorSurrounding` (function, line 296) `fixed_t	P_FindHighestFloorSurrounding(sector_t *sec)`
  - `P_FindNextHighestFloor` (function, line 328) `fixed_t
P_FindNextHighestFloor
( sector_t* sec,
  int       currentheight )`
  - `P_FindLowestCeilingSurrounding` (function, line 391) `fixed_t
P_FindLowestCeilingSurrounding(sector_t* sec)`
  - `P_FindHighestCeilingSurrounding` (function, line 417) `fixed_t	P_FindHighestCeilingSurrounding(sector_t* sec)`
  - `P_FindSectorFromLineTag` (function, line 443) `int
P_FindSectorFromLineTag
( line_t*	line,
  int		start )`
  - `P_FindMinSurroundingLight` (function, line 463) `int
P_FindMinSurroundingLight
( sector_t*	sector,
  int		max )`
  - `P_CrossSpecialLine` (function, line 501) `void
P_CrossSpecialLine
( int		linenum,
  int		side,
  mobj_t*	thing )`
  - `P_ShootSpecialLine` (function, line 968) `void
P_ShootSpecialLine
( mobj_t*	thing,
  line_t*	line )`
  - `P_PlayerInSpecialSector` (function, line 1019) `void P_PlayerInSpecialSector (player_t* player)`
  - `P_UpdateSpecials` (function, line 1092) `void P_UpdateSpecials (void)`
  - `DonutOverrun` (function, line 1177) `static void DonutOverrun(fixed_t *s3_floorheight, short *s3_floorpic,
                         li...`
  - `EV_DoDonut` (function, line 1257) `int EV_DoDonut(line_t*	line)`
  - `P_SpawnSpecials` (function, line 1374) `void P_SpawnSpecials (void)`
  - `MAXANIMS` (macro, line 75)
  - `MAXLINEANIMS` (macro, line 136)
  - `MAX_ADJOINING_SECTORS` (macro, line 327)
  - `DONUT_FLOORHEIGHT_DEFAULT` (macro, line 1174)
  - `DONUT_FLOORPIC_DEFAULT` (macro, line 1176)

## progs/doomgeneric/p_spec.h
- Layer: testing
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__P_SPEC__` (macro, line 24)
  - `MO_TELEPORTMAN` (macro, line 35)
  - `GLOWSPEED` (macro, line 171)
  - `STROBEBRIGHT` (macro, line 174)
  - `FASTDARK` (macro, line 175)
  - `SLOWDARK` (macro, line 176)
  - `MAXSWITCHES` (macro, line 238)
  - `MAXBUTTONS` (macro, line 241)
  - `BUTTONTIME` (macro, line 244)
  - `PLATWAIT` (macro, line 298)
  - `PLATSPEED` (macro, line 302)
  - `MAXPLATS` (macro, line 303)
  - `VDOORSPEED` (macro, line 358)
  - `VDOORWAIT` (macro, line 362)
  - `SNUMFRAMES` (macro, line 456)
  - `SDOORWAIT` (macro, line 457)
  - `SWAITTICS` (macro, line 459)
  - `MAXSLIDEDOORS` (macro, line 462)
  - `CEILSPEED` (macro, line 508)
  - `CEILWAIT` (macro, line 514)
  - `MAXCEILINGS` (macro, line 515)
  - `FLOORSPEED` (macro, line 594)

## progs/doomgeneric/p_switch.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `P_InitSwitchList` (function, line 101) `void P_InitSwitchList(void)`
  - `P_StartButton` (function, line 148) `void
P_StartButton
( line_t*	line,
  bwhere_e	w,
  int		texture,
  int		time )`
  - `P_ChangeSwitchTexture` (function, line 194) `void
P_ChangeSwitchTexture
( line_t*	line,
  int 		useAgain )`
  - `P_UseSpecialLine` (function, line 269) `boolean
P_UseSpecialLine
( mobj_t*	thing,
  line_t*	line,
  int		side )`

## progs/doomgeneric/p_telept.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `EV_Teleport` (function, line 41) `int
EV_Teleport
( line_t*	line,
  int		side,
  mobj_t*	thing )`

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
  - `P_Ticker` (function, line 122) `void P_Ticker (void)`

## progs/doomgeneric/p_tick.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__P_TICK__` (macro, line 21)

## progs/doomgeneric/p_user.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `P_Thrust` (function, line 51) `void
P_Thrust
( player_t*	player,
  angle_t	angle,
  fixed_t	move )`
  - `P_CalcHeight` (function, line 70) `void P_CalcHeight (player_t* player)`
  - `P_MovePlayer` (function, line 141) `void P_MovePlayer (player_t* player)`
  - `P_DeathThink` (function, line 174) `void P_DeathThink (player_t* player)`
  - `P_PlayerThink` (function, line 229) `void P_PlayerThink (player_t* player)`
  - `INVERSECOLORMAP` (macro, line 34)
  - `MAXBOB` (macro, line 42)
  - `ANG5` (macro, line 173)

## progs/doomgeneric/r_bsp.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `R_ClearDrawSegs` (function, line 61) `void R_ClearDrawSegs (void)`
  - `R_ClipSolidWallSegment` (function, line 96) `void
R_ClipSolidWallSegment
( int			first,
  int			last )`
  - `R_ClipPassWallSegment` (function, line 189) `void
R_ClipPassWallSegment
( int	first,
  int	last )`
  - `R_ClearClipSegs` (function, line 238) `void R_ClearClipSegs (void)`
  - `R_AddLine` (function, line 252) `void R_AddLine (seg_t*	line)`
  - `R_CheckBBox` (function, line 372) `boolean R_CheckBBox (fixed_t*	bspcoord)`
  - `R_Subsector` (function, line 490) `void R_Subsector (int num)`
  - `R_RenderBSPNode` (function, line 545) `void R_RenderBSPNode (int bspnum)`
  - `MAXSEGS` (macro, line 79)

## progs/doomgeneric/r_bsp.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__R_BSP__` (macro, line 21)

## progs/doomgeneric/r_data.c
- Layer: data_access
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `texture_s` (struct, line 106)
  - `R_DrawColumnInCache` (function, line 185) `void
R_DrawColumnInCache
( column_t*	patch,
  byte*		cache,
  int		originy,
  int		cacheheight )`
  - `R_GenerateComposite` (function, line 226) `void R_GenerateComposite (int texnum)`
  - `R_GenerateLookup` (function, line 294) `void R_GenerateLookup (int texnum)`
  - `R_GetColumn` (function, line 382) `byte*
R_GetColumn
( int		tex,
  int		col )`
  - `GenerateTextureHashTable` (function, line 402) `static void GenerateTextureHashTable(void)`
  - `R_InitTextures` (function, line 451) `void R_InitTextures (void)`
  - `R_InitFlats` (function, line 633) `void R_InitFlats (void)`
  - `R_InitSpriteLumps` (function, line 655) `void R_InitSpriteLumps (void)`
  - `R_InitColormaps` (function, line 685) `void R_InitColormaps (void)`
  - `R_InitData` (function, line 703) `void R_InitData (void)`
  - `R_FlatNumForName` (function, line 720) `int R_FlatNumForName (char* name)`
  - `R_CheckTextureNumForName` (function, line 744) `int	R_CheckTextureNumForName (char *name)`
  - `R_TextureNumForName` (function, line 775) `int	R_TextureNumForName (char* name)`
  - `R_PrecacheLevel` (function, line 799) `void R_PrecacheLevel (void)`

## progs/doomgeneric/r_data.h
- Layer: data_access
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__R_DATA__` (macro, line 22)

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
  - `__R_DEFS__` (macro, line 21)
  - `SIL_NONE` (macro, line 46)
  - `SIL_BOTTOM` (macro, line 47)
  - `SIL_TOP` (macro, line 48)
  - `SIL_BOTH` (macro, line 49)
  - `MAXDRAWSEGS` (macro, line 50)

## progs/doomgeneric/r_draw.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `R_DrawColumn` (function, line 102) `void R_DrawColumn (void)`
  - `R_DrawColumn` (function, line 152) `void R_DrawColumn (void)`
  - `R_DrawColumnLow` (function, line 206) `void R_DrawColumnLow (void)`
  - `R_DrawFuzzColumn` (function, line 283) `void R_DrawFuzzColumn (void)`
  - `R_DrawFuzzColumnLow` (function, line 341) `void R_DrawFuzzColumnLow (void)`
  - `R_DrawTranslatedColumn` (function, line 423) `void R_DrawTranslatedColumn (void)`
  - `R_DrawTranslatedColumnLow` (function, line 467) `void R_DrawTranslatedColumnLow (void)`
  - `R_InitTranslationTables` (function, line 530) `void R_InitTranslationTables (void)`
  - `R_DrawSpan` (function, line 590) `void R_DrawSpan (void)`
  - `R_DrawSpan` (function, line 646) `void R_DrawSpan (void)`
  - `R_DrawSpanLow` (function, line 719) `void R_DrawSpanLow (void)`
  - `R_InitBuffer` (function, line 776) `void
R_InitBuffer
( int		width,
  int		height )`
  - `R_FillBackScreen` (function, line 812) `void R_FillBackScreen (void)`
  - `R_VideoErase` (function, line 918) `void
R_VideoErase
( unsigned	ofs,
  int		count )`
  - `R_DrawViewBorder` (function, line 941) `void R_DrawViewBorder (void)`
  - `MAXWIDTH` (macro, line 41)
  - `MAXHEIGHT` (macro, line 42)
  - `SBARHEIGHT` (macro, line 45)
  - `FUZZTABLE` (macro, line 257)
  - `FUZZOFF` (macro, line 258)

## progs/doomgeneric/r_draw.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__R_DRAW__` (macro, line 21)

## progs/doomgeneric/r_local.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__R_LOCAL__` (macro, line 21)

## progs/doomgeneric/r_main.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `R_AddPointToBox` (function, line 122) `void
R_AddPointToBox
( int		x,
  int		y,
  fixed_t*	box )`
  - `R_PointOnSide` (function, line 145) `int
R_PointOnSide
( fixed_t	x,
  fixed_t	y,
  node_t*	node )`
  - `R_PointOnSegSide` (function, line 196) `int
R_PointOnSegSide
( fixed_t	x,
  fixed_t	y,
  seg_t*	line )`
  - `R_PointToAngle` (function, line 271) `angle_t
R_PointToAngle
( fixed_t	x,
  fixed_t	y )`
  - `R_PointToAngle2` (function, line 359) `angle_t
R_PointToAngle2
( fixed_t	x1,
  fixed_t	y1,
  fixed_t	x2,
  fixed_t	y2 )`
  - `R_PointToDist` (function, line 373) `fixed_t
R_PointToDist
( fixed_t	x,
  fixed_t	y )`
  - `R_InitPointToAngle` (function, line 422) `void R_InitPointToAngle (void)`
  - `R_ScaleFromGlobalAngle` (function, line 449) `fixed_t R_ScaleFromGlobalAngle (angle_t visangle)`
  - `R_InitTables` (function, line 505) `void R_InitTables (void)`
  - `R_InitTextureMapping` (function, line 540) `void R_InitTextureMapping (void)`
  - `R_InitLightTables` (function, line 609) `void R_InitLightTables (void)`
  - `R_SetViewSize` (function, line 651) `void
R_SetViewSize
( int		blocks,
  int		detail )`
  - `R_ExecuteSetViewSize` (function, line 667) `void R_ExecuteSetViewSize (void)`
  - `R_Init` (function, line 764) `void R_Init (void)`
  - `R_PointInSubsector` (function, line 793) `subsector_t*
R_PointInSubsector
( fixed_t	x,
  fixed_t	y )`
  - `R_SetupFrame` (function, line 823) `void R_SetupFrame (player_t* player)`
  - `R_RenderPlayerView` (function, line 863) `void R_RenderPlayerView (player_t* player)`
  - `FIELDOFVIEW` (macro, line 43)
  - `DISTMAP` (macro, line 608)

## progs/doomgeneric/r_main.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__R_MAIN__` (macro, line 21)
  - `LIGHTLEVELS` (macro, line 61)
  - `LIGHTSEGSHIFT` (macro, line 62)
  - `MAXLIGHTSCALE` (macro, line 63)
  - `LIGHTSCALESHIFT` (macro, line 65)
  - `MAXLIGHTZ` (macro, line 66)
  - `LIGHTZSHIFT` (macro, line 67)
  - `NUMCOLORMAPS` (macro, line 79)

## progs/doomgeneric/r_plane.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `R_InitPlanes` (function, line 94) `void R_InitPlanes (void)`
  - `R_MapPlane` (function, line 113) `void
R_MapPlane
( int		y,
  int		x1,
  int		x2 )`
  - `R_ClearPlanes` (function, line 178) `void R_ClearPlanes (void)`
  - `R_FindPlane` (function, line 210) `visplane_t*
R_FindPlane
( fixed_t	height,
  int		picnum,
  int		lightlevel )`
  - `R_CheckPlane` (function, line 258) `visplane_t*
R_CheckPlane
( visplane_t*	pl,
  int		start,
  int		stop )`
  - `R_MakeSpans` (function, line 323) `void
R_MakeSpans
( int		x,
  int		t1,
  int		b1,
  int		t2,
  int		b2 )`
  - `R_DrawPlanes` (function, line 360) `void R_DrawPlanes (void)`
  - `MAXVISPLANES` (macro, line 45)
  - `MAXOPENINGS` (macro, line 52)

## progs/doomgeneric/r_plane.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__R_PLANE__` (macro, line 21)

## progs/doomgeneric/r_segs.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `R_RenderMaskedSegRange` (function, line 95) `void
R_RenderMaskedSegRange
( drawseg_t*	ds,
  int		x1,
  int		x2 )`
  - `R_RenderSegLoop` (function, line 198) `void R_RenderSegLoop (void)`
  - `R_StoreWallRange` (function, line 371) `void
R_StoreWallRange
( int	start,
  int	stop )`
  - `HEIGHTBITS` (macro, line 196)
  - `HEIGHTUNIT` (macro, line 197)

## progs/doomgeneric/r_segs.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__R_SEGS__` (macro, line 21)

## progs/doomgeneric/r_sky.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `R_InitSkyMap` (function, line 47) `void R_InitSkyMap (void)`

## progs/doomgeneric/r_sky.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__R_SKY__` (macro, line 21)
  - `SKYFLATNAME` (macro, line 26)
  - `ANGLETOSKYSHIFT` (macro, line 29)

## progs/doomgeneric/r_state.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__R_STATE__` (macro, line 21)

## progs/doomgeneric/r_things.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `R_InstallSpriteLump` (function, line 99) `void
R_InstallSpriteLump
( int		lump,
  unsigned	frame,
  unsigned	rotation,
  boolean	flipped )`
  - `R_InitSpriteDefs` (function, line 171) `void R_InitSpriteDefs (char** namelist)`
  - `R_InitSprites` (function, line 291) `void R_InitSprites (char** namelist)`
  - `R_ClearSprites` (function, line 309) `void R_ClearSprites (void)`
  - `R_NewVisSprite` (function, line 319) `vissprite_t* R_NewVisSprite (void)`
  - `R_DrawMaskedColumn` (function, line 342) `void R_DrawMaskedColumn (column_t* column)`
  - `R_DrawVisSprite` (function, line 388) `void
R_DrawVisSprite
( vissprite_t*		vis,
  int			x1,
  int			x2 )`
  - `R_ProjectSprite` (function, line 444) `void R_ProjectSprite (mobj_t* thing)`
  - `R_AddSprites` (function, line 605) `void R_AddSprites (sector_t* sec)`
  - `R_DrawPSprite` (function, line 638) `void R_DrawPSprite (pspdef_t* psp)`
  - `R_DrawPlayerSprites` (function, line 738) `void R_DrawPlayerSprites (void)`
  - `R_SortVisSprites` (function, line 777) `void R_SortVisSprites (void)`
  - `R_DrawSprite` (function, line 837) `void R_DrawSprite (vissprite_t* spr)`
  - `R_DrawMasked` (function, line 951) `void R_DrawMasked (void)`
  - `MINZ` (macro, line 37)
  - `BASEYCENTER` (macro, line 41)

## progs/doomgeneric/r_things.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__R_THINGS__` (macro, line 21)
  - `MAXVISSPRITES` (macro, line 22)

## progs/doomgeneric/s_sound.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `S_Init` (function, line 113) `void S_Init(int sfxVolume, int musicVolume)`
  - `S_Shutdown` (function, line 145) `void S_Shutdown(void)`
  - `S_StopChannel` (function, line 151) `static void S_StopChannel(int cnum)`
  - `S_Start` (function, line 190) `void S_Start(void)`
  - `S_StopSound` (function, line 242) `void S_StopSound(mobj_t *origin)`
  - `S_GetChannel` (function, line 261) `static int S_GetChannel(mobj_t *origin, sfxinfo_t *sfxinfo)`
  - `S_AdjustSoundParams` (function, line 322) `static int S_AdjustSoundParams(mobj_t *listener, mobj_t *source,
                               i...`
  - `S_StartSound` (function, line 390) `void S_StartSound(void *origin_p, int sfx_id)`
  - `S_PauseSound` (function, line 481) `void S_PauseSound(void)`
  - `S_ResumeSound` (function, line 490) `void S_ResumeSound(void)`
  - `S_UpdateSounds` (function, line 503) `void S_UpdateSounds(mobj_t *listener)`
  - `S_SetMusicVolume` (function, line 570) `void S_SetMusicVolume(int volume)`
  - `S_SetSfxVolume` (function, line 581) `void S_SetSfxVolume(int volume)`
  - `S_StartMusic` (function, line 595) `void S_StartMusic(int m_id)`
  - `S_ChangeMusic` (function, line 600) `void S_ChangeMusic(int musicnum, int looping)`
  - `S_MusicPlaying` (function, line 648) `boolean S_MusicPlaying(void)`
  - `S_StopMusic` (function, line 653) `void S_StopMusic(void)`
  - `S_CLIPPING_DIST` (macro, line 43)
  - `S_CLOSE_DIST` (macro, line 51)
  - `S_ATTENUATOR` (macro, line 55)
  - `S_STEREO_SWING` (macro, line 59)
  - `NORM_PITCH` (macro, line 61)
  - `NORM_PRIORITY` (macro, line 63)
  - `NORM_SEP` (macro, line 64)

## progs/doomgeneric/s_sound.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__S_SOUND__` (macro, line 21)

## progs/doomgeneric/sha1.c
- Layer: utility
- Doc: sha1.c - SHA1 hash function
- Language: c
- Symbols:
  - `SHA1_Init` (function, line 39) `void SHA1_Init(sha1_context_t *hd)`
  - `Transform` (function, line 55) `static void Transform(sha1_context_t *hd, byte *data)`
  - `SHA1_Update` (function, line 198) `void SHA1_Update(sha1_context_t *hd, byte *inbuf, size_t inlen)`
  - `SHA1_Final` (function, line 237) `void SHA1_Final(sha1_digest_t digest, sha1_context_t *hd)`
  - `SHA1_UpdateInt32` (function, line 302) `void SHA1_UpdateInt32(sha1_context_t *context, unsigned int val)`
  - `SHA1_UpdateString` (function, line 314) `void SHA1_UpdateString(sha1_context_t *context, char *str)`
  - `K1` (macro, line 82)
  - `K2` (macro, line 85)
  - `K3` (macro, line 86)
  - `K4` (macro, line 87)
  - `F1` (macro, line 88)
  - `F2` (macro, line 89)
  - `F3` (macro, line 90)
  - `F4` (macro, line 91)
  - `rol` (macro, line 92)
  - `M` (macro, line 94)
  - `R` (macro, line 98)
  - `X` (macro, line 288)
  - `X` (macro, line 290)

## progs/doomgeneric/sha1.h
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `sha1_context_s` (struct, line 26)
  - `__SHA1_H__` (macro, line 19)

## progs/doomgeneric/sounds.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `MUSIC` (macro, line 30)
  - `SOUND` (macro, line 110)
  - `SOUND_LINK` (macro, line 113)

## progs/doomgeneric/sounds.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__SOUNDS__` (macro, line 21)

## progs/doomgeneric/st_lib.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `STlib_init` (function, line 50) `void STlib_init(void)`
  - `STlib_initNum` (function, line 58) `void
STlib_initNum
( st_number_t*		n,
  int			x,
  int			y,
  patch_t**		pl,
  int*			num,
  bool...`
  - `STlib_drawNum` (function, line 83) `void
STlib_drawNum
( st_number_t*	n,
  boolean	refresh )`
  - `STlib_updateNum` (function, line 145) `void
STlib_updateNum
( st_number_t*		n,
  boolean		refresh )`
  - `STlib_initPercent` (function, line 155) `void
STlib_initPercent
( st_percent_t*		p,
  int			x,
  int			y,
  patch_t**		pl,
  int*			num,
 ...`
  - `STlib_updatePercent` (function, line 168) `void
STlib_updatePercent
( st_percent_t*		per,
  int			refresh )`
  - `STlib_initMultIcon` (function, line 182) `void
STlib_initMultIcon
( st_multicon_t*	i,
  int			x,
  int			y,
  patch_t**		il,
  int*			inum,...`
  - `STlib_updateMultIcon` (function, line 201) `void
STlib_updateMultIcon
( st_multicon_t*	mi,
  boolean		refresh )`
  - `STlib_initBinIcon` (function, line 232) `void
STlib_initBinIcon
( st_binicon_t*		b,
  int			x,
  int			y,
  patch_t*		i,
  boolean*		val,
...`
  - `STlib_updateBinIcon` (function, line 251) `void
STlib_updateBinIcon
( st_binicon_t*		bi,
  boolean		refresh )`

## progs/doomgeneric/st_lib.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__STLIB__` (macro, line 20)

## progs/doomgeneric/st_stuff.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `ST_refreshBackground` (function, line 415) `void ST_refreshBackground(void)`
  - `ST_Responder` (function, line 438) `boolean
ST_Responder (event_t* ev)`
  - `ST_calcPainOffset` (function, line 662) `int ST_calcPainOffset(void)`
  - `ST_updateFaceWidget` (function, line 688) `void ST_updateFaceWidget(void)`
  - `ST_updateWidgets` (function, line 859) `void ST_updateWidgets(void)`
  - `ST_Ticker` (function, line 923) `void ST_Ticker (void)`
  - `ST_doPaletteStuff` (function, line 935) `void ST_doPaletteStuff(void)`
  - `ST_drawWidgets` (function, line 1000) `void ST_drawWidgets(boolean refresh)`
  - `ST_doRefresh` (function, line 1035) `void ST_doRefresh(void)`
  - `ST_diffDraw` (function, line 1048) `void ST_diffDraw(void)`
  - `ST_Drawer` (function, line 1054) `void ST_Drawer (boolean fullscreen, boolean refresh)`
  - `ST_loadUnloadGraphics` (function, line 1075) `static void ST_loadUnloadGraphics(load_callback_t callback)`
  - `ST_loadCallback` (function, line 1161) `static void ST_loadCallback(char *lumpname, patch_t **variable)`
  - `ST_loadGraphics` (function, line 1166) `void ST_loadGraphics(void)`
  - `ST_loadData` (function, line 1171) `void ST_loadData(void)`
  - `ST_unloadCallback` (function, line 1177) `static void ST_unloadCallback(char *lumpname, patch_t **variable)`
  - `ST_unloadGraphics` (function, line 1183) `void ST_unloadGraphics(void)`
  - `ST_unloadData` (function, line 1188) `void ST_unloadData(void)`
  - `ST_initData` (function, line 1193) `void ST_initData(void)`
  - `ST_createWidgets` (function, line 1224) `void ST_createWidgets(void)`
  - `ST_Start` (function, line 1387) `void ST_Start (void)`
  - `ST_Stop` (function, line 1400) `void ST_Stop (void)`
  - `ST_Init` (function, line 1410) `void ST_Init (void)`
  - `STARTREDPALS` (macro, line 68)
  - `STARTBONUSPALS` (macro, line 69)
  - `NUMREDPALS` (macro, line 70)
  - `NUMBONUSPALS` (macro, line 71)
  - `RADIATIONPAL` (macro, line 73)
  - `ST_FACEPROBABILITY` (macro, line 77)
  - `ST_TOGGLECHAT` (macro, line 80)
  - `ST_X` (macro, line 83)
  - `ST_X2` (macro, line 84)
  - `ST_FX` (macro, line 85)
  - `ST_FY` (macro, line 87)
  - `ST_TALLNUMWIDTH` (macro, line 91)
  - `ST_NUMPAINFACES` (macro, line 94)
  - `ST_NUMSTRAIGHTFACES` (macro, line 95)
  - `ST_NUMTURNFACES` (macro, line 96)
  - `ST_NUMSPECIALFACES` (macro, line 97)
  - `ST_FACESTRIDE` (macro, line 98)
  - `ST_NUMEXTRAFACES` (macro, line 101)
  - `ST_NUMFACES` (macro, line 103)
  - `ST_TURNOFFSET` (macro, line 106)
  - `ST_OUCHOFFSET` (macro, line 108)
  - `ST_EVILGRINOFFSET` (macro, line 109)
  - `ST_RAMPAGEOFFSET` (macro, line 110)
  - `ST_GODFACE` (macro, line 111)
  - `ST_DEADFACE` (macro, line 112)
  - `ST_FACESX` (macro, line 113)
  - `ST_FACESY` (macro, line 115)
  - `ST_EVILGRINCOUNT` (macro, line 116)
  - `ST_STRAIGHTFACECOUNT` (macro, line 118)
  - `ST_TURNCOUNT` (macro, line 119)
  - `ST_OUCHCOUNT` (macro, line 120)
  - `ST_RAMPAGEDELAY` (macro, line 121)
  - `ST_MUCHPAIN` (macro, line 122)
  - `ST_AMMOWIDTH` (macro, line 135)
  - `ST_AMMOX` (macro, line 136)
  - `ST_AMMOY` (macro, line 137)
  - `ST_HEALTHWIDTH` (macro, line 140)
  - `ST_HEALTHX` (macro, line 141)
  - `ST_HEALTHY` (macro, line 142)
  - `ST_ARMSX` (macro, line 145)
  - `ST_ARMSY` (macro, line 146)
  - `ST_ARMSBGX` (macro, line 147)
  - `ST_ARMSBGY` (macro, line 148)
  - `ST_ARMSXSPACE` (macro, line 149)
  - `ST_ARMSYSPACE` (macro, line 150)
  - `ST_FRAGSX` (macro, line 153)
  - `ST_FRAGSY` (macro, line 154)
  - `ST_FRAGSWIDTH` (macro, line 155)
  - `ST_ARMORWIDTH` (macro, line 158)
  - `ST_ARMORX` (macro, line 159)
  - `ST_ARMORY` (macro, line 160)
  - `ST_KEY0WIDTH` (macro, line 163)
  - `ST_KEY0HEIGHT` (macro, line 164)
  - `ST_KEY0X` (macro, line 165)
  - `ST_KEY0Y` (macro, line 166)
  - `ST_KEY1WIDTH` (macro, line 167)
  - `ST_KEY1X` (macro, line 168)
  - `ST_KEY1Y` (macro, line 169)
  - `ST_KEY2WIDTH` (macro, line 170)
  - `ST_KEY2X` (macro, line 171)
  - `ST_KEY2Y` (macro, line 172)
  - `ST_AMMO0WIDTH` (macro, line 175)
  - `ST_AMMO0HEIGHT` (macro, line 176)
  - `ST_AMMO0X` (macro, line 177)
  - `ST_AMMO0Y` (macro, line 178)
  - `ST_AMMO1WIDTH` (macro, line 179)
  - `ST_AMMO1X` (macro, line 180)
  - `ST_AMMO1Y` (macro, line 181)
  - `ST_AMMO2WIDTH` (macro, line 182)
  - `ST_AMMO2X` (macro, line 183)
  - `ST_AMMO2Y` (macro, line 184)
  - `ST_AMMO3WIDTH` (macro, line 185)
  - `ST_AMMO3X` (macro, line 186)
  - `ST_AMMO3Y` (macro, line 187)
  - `ST_MAXAMMO0WIDTH` (macro, line 191)
  - `ST_MAXAMMO0HEIGHT` (macro, line 192)
  - `ST_MAXAMMO0X` (macro, line 193)
  - `ST_MAXAMMO0Y` (macro, line 194)
  - `ST_MAXAMMO1WIDTH` (macro, line 195)
  - `ST_MAXAMMO1X` (macro, line 196)
  - `ST_MAXAMMO1Y` (macro, line 197)
  - `ST_MAXAMMO2WIDTH` (macro, line 198)
  - `ST_MAXAMMO2X` (macro, line 199)
  - `ST_MAXAMMO2Y` (macro, line 200)
  - `ST_MAXAMMO3WIDTH` (macro, line 201)
  - `ST_MAXAMMO3X` (macro, line 202)
  - `ST_MAXAMMO3Y` (macro, line 203)
  - `ST_WEAPON0X` (macro, line 206)
  - `ST_WEAPON0Y` (macro, line 207)
  - `ST_WEAPON1X` (macro, line 210)
  - `ST_WEAPON1Y` (macro, line 211)
  - `ST_WEAPON2X` (macro, line 214)
  - `ST_WEAPON2Y` (macro, line 215)
  - `ST_WEAPON3X` (macro, line 218)
  - `ST_WEAPON3Y` (macro, line 219)
  - `ST_WEAPON4X` (macro, line 222)
  - `ST_WEAPON4Y` (macro, line 223)
  - `ST_WEAPON5X` (macro, line 226)
  - `ST_WEAPON5Y` (macro, line 227)
  - `ST_WPNSX` (macro, line 230)
  - `ST_WPNSY` (macro, line 231)
  - `ST_DETHX` (macro, line 234)
  - `ST_DETHY` (macro, line 235)
  - `ST_MSGTEXTX` (macro, line 241)
  - `ST_MSGTEXTY` (macro, line 242)
  - `ST_MSGWIDTH` (macro, line 244)
  - `ST_MSGHEIGHT` (macro, line 246)
  - `ST_OUTTEXTX` (macro, line 247)
  - `ST_OUTTEXTY` (macro, line 249)
  - `ST_OUTWIDTH` (macro, line 252)
  - `ST_OUTHEIGHT` (macro, line 254)
  - `ST_MAPTITLEX` (macro, line 255)
  - `ST_MAPTITLEY` (macro, line 258)
  - `ST_MAPHEIGHT` (macro, line 260)

## progs/doomgeneric/st_stuff.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__STSTUFF_H__` (macro, line 22)
  - `ST_HEIGHT` (macro, line 30)
  - `ST_WIDTH` (macro, line 31)
  - `ST_Y` (macro, line 32)

## progs/doomgeneric/statdump.c
- Layer: utility
- Language: c
- Symbols:
  - `DiscoverGamemode` (function, line 70) `static void DiscoverGamemode(wbstartstruct_t *stats, int num_stats)`
  - `GetNumPlayers` (function, line 129) `static int GetNumPlayers(wbstartstruct_t *stats)`
  - `PrintBanner` (function, line 149) `static void PrintBanner(FILE *stream)`
  - `PrintPercentage` (function, line 154) `static void PrintPercentage(FILE *stream, int amount, int total)`
  - `PrintPlayerStats` (function, line 179) `static void PrintPlayerStats(FILE *stream, wbstartstruct_t *stats,
        int player_num)`
  - `PrintFragsTable` (function, line 212) `static void PrintFragsTable(FILE *stream, wbstartstruct_t *stats)`
  - `PrintLevelName` (function, line 271) `static void PrintLevelName(FILE *stream, int episode, int level)`
  - `PrintStats` (function, line 300) `static void PrintStats(FILE *stream, wbstartstruct_t *stats)`
  - `StatCopy` (function, line 332) `void StatCopy(wbstartstruct_t *stats)`
  - `StatDump` (function, line 342) `void StatDump(void)`
  - `MAX_CAPTURES` (macro, line 55)

## progs/doomgeneric/statdump.h
- Layer: utility
- Language: h
- Symbols:
  - `DOOM_STATDUMP_H` (macro, line 18)

## progs/doomgeneric/tables.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `SlopeDiv` (function, line 40) `int SlopeDiv(unsigned int num, unsigned int den)`

## progs/doomgeneric/tables.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software Copyright(C) 2005-2014 Simon Howard  This
- Language: h
- Symbols:
  - `__TABLES__` (macro, line 35)
  - `FINEANGLES` (macro, line 40)
  - `FINEMASK` (macro, line 42)
  - `ANGLETOFINESHIFT` (macro, line 46)
  - `ANG45` (macro, line 62)
  - `ANG90` (macro, line 64)
  - `ANG180` (macro, line 65)
  - `ANG270` (macro, line 66)
  - `ANG_MAX` (macro, line 67)
  - `ANG1` (macro, line 68)
  - `ANG60` (macro, line 70)
  - `ANG1_X` (macro, line 74)
  - `SLOPERANGE` (macro, line 76)
  - `SLOPEBITS` (macro, line 78)
  - `DBITS` (macro, line 79)

## progs/doomgeneric/v_patch.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `V_PATCH_H` (macro, line 21)

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
  - `V_DrawPatch` (function, line 138) `void V_DrawPatch(int x, int y, patch_t *patch)`
  - `V_DrawPatchFlipped` (function, line 202) `void V_DrawPatchFlipped(int x, int y, patch_t *patch)`
  - `V_DrawPatchDirect` (function, line 267) `void V_DrawPatchDirect(int x, int y, patch_t *patch)`
  - `V_DrawTLPatch` (function, line 278) `void V_DrawTLPatch(int x, int y, patch_t * patch)`
  - `V_DrawXlaPatch` (function, line 328) `void V_DrawXlaPatch(int x, int y, patch_t * patch)`
  - `V_DrawAltTLPatch` (function, line 377) `void V_DrawAltTLPatch(int x, int y, patch_t * patch)`
  - `V_DrawShadowedPatch` (function, line 427) `void V_DrawShadowedPatch(int x, int y, patch_t *patch)`
  - `V_LoadTintTable` (function, line 481) `void V_LoadTintTable(void)`
  - `V_LoadXlaTable` (function, line 492) `void V_LoadXlaTable(void)`
  - `V_DrawBlock` (function, line 502) `void V_DrawBlock(int x, int y, int width, int height, byte *src)`
  - `V_DrawFilledBox` (function, line 528) `void V_DrawFilledBox(int x, int y, int w, int h, int c)`
  - `V_DrawHorizLine` (function, line 548) `void V_DrawHorizLine(int x, int y, int w, int c)`
  - `V_DrawVertLine` (function, line 561) `void V_DrawVertLine(int x, int y, int h, int c)`
  - `V_DrawBox` (function, line 575) `void V_DrawBox(int x, int y, int w, int h, int c)`
  - `V_DrawRawScreen` (function, line 588) `void V_DrawRawScreen(byte *raw)`
  - `V_Init` (function, line 597) `void V_Init (void)`
  - `V_UseBuffer` (function, line 605) `void V_UseBuffer(byte *buffer)`
  - `V_RestoreBuffer` (function, line 612) `void V_RestoreBuffer(void)`
  - `WritePCXfile` (function, line 652) `void WritePCXfile(char *filename, byte *data,
                  int width, int height,
          ...`
  - `error_fn` (function, line 710) `static void error_fn(png_structp p, png_const_charp s)`
  - `warning_fn` (function, line 715) `static void warning_fn(png_structp p, png_const_charp s)`
  - `WritePNGfile` (function, line 720) `void WritePNGfile(char *filename, byte *data,
                  int width, int height,
          ...`
  - `V_ScreenShot` (function, line 790) `void V_ScreenShot(char *format)`
  - `V_DrawMouseSpeedBox` (function, line 845) `void V_DrawMouseSpeedBox(int speed)`
  - `RANGECHECK` (macro, line 46)
  - `MOUSE_SPEED_BOX_WIDTH` (macro, line 842)
  - `MOUSE_SPEED_BOX_HEIGHT` (macro, line 844)

## progs/doomgeneric/v_video.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__V_VIDEO__` (macro, line 23)
  - `CENTERY` (macro, line 33)

## progs/doomgeneric/w_checksum.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `GetFileNumber` (function, line 30) `static int GetFileNumber(wad_file_t *handle)`
  - `ChecksumAddLump` (function, line 56) `static void ChecksumAddLump(sha1_context_t *sha1_context, lumpinfo_t *lump)`
  - `W_Checksum` (function, line 67) `void W_Checksum(sha1_digest_t digest)`

## progs/doomgeneric/w_checksum.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `W_CHECKSUM_H` (macro, line 20)

## progs/doomgeneric/w_file.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `W_OpenFile` (function, line 52) `wad_file_t *W_OpenFile(char *path)`
  - `W_CloseFile` (function, line 84) `void W_CloseFile(wad_file_t *wad)`
  - `W_Read` (function, line 89) `size_t W_Read(wad_file_t *wad, unsigned int offset,
              void *buffer, size_t buffer_len)`

## progs/doomgeneric/w_file.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `_wad_file_s` (struct, line 46)
  - `__W_FILE__` (macro, line 21)

## progs/doomgeneric/w_file_stdc.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `W_StdC_OpenFile` (function, line 32) `static wad_file_t *W_StdC_OpenFile(char *path)`
  - `W_StdC_CloseFile` (function, line 55) `static void W_StdC_CloseFile(wad_file_t *wad)`
  - `W_StdC_Read` (function, line 68) `size_t W_StdC_Read(wad_file_t *wad, unsigned int offset,
                   void *buffer, size_t ...`

## progs/doomgeneric/w_main.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `W_ParseCommandLine` (function, line 29) `boolean W_ParseCommandLine(void)`

## progs/doomgeneric/w_main.h
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `W_MAIN_H` (macro, line 19)

## progs/doomgeneric/w_merge.h
- Layer: utility
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the t
- Language: h
- Symbols:
  - `W_MERGE_H` (macro, line 22)
  - `W_NWT_MERGE_SPRITES` (macro, line 23)
  - `W_NWT_MERGE_FLATS` (macro, line 25)

## progs/doomgeneric/w_wad.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `W_LumpNameHash` (function, line 71) `unsigned int W_LumpNameHash(const char *s)`
  - `ExtendLumpInfo` (function, line 89) `static void ExtendLumpInfo(int newnumlumps)`
  - `W_AddFile` (function, line 140) `wad_file_t *W_AddFile (char *filename)`
  - `W_NumLumps` (function, line 246) `int W_NumLumps (void)`
  - `W_CheckNumForName` (function, line 257) `int W_CheckNumForName (char* name)`
  - `W_GetNumForName` (function, line 308) `int W_GetNumForName (char* name)`
  - `W_LumpLength` (function, line 327) `int W_LumpLength (unsigned int lump)`
  - `W_ReadLump` (function, line 344) `void W_ReadLump(unsigned int lump, void *dest)`
  - `W_CacheLumpNum` (function, line 383) `void *W_CacheLumpNum(int lumpnum, int tag)`
  - `W_CacheLumpName` (function, line 431) `void *W_CacheLumpName(char *name, int tag)`
  - `W_ReleaseLumpNum` (function, line 445) `void W_ReleaseLumpNum(int lumpnum)`
  - `W_ReleaseLumpName` (function, line 466) `void W_ReleaseLumpName(char *name)`
  - `W_Profile` (function, line 479) `void W_Profile (void)`
  - `W_GenerateHashTable` (function, line 540) `void W_GenerateHashTable(void)`
  - `W_CheckCorrectIWAD` (function, line 587) `void W_CheckCorrectIWAD(GameMission_t mission)`

## progs/doomgeneric/w_wad.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `lumpinfo_s` (struct, line 41)
  - `__W_WAD__` (macro, line 21)

## progs/doomgeneric/wi_stuff.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `WI_slamBackground` (function, line 402) `void WI_slamBackground(void)`
  - `WI_Responder` (function, line 409) `boolean WI_Responder(event_t* ev)`
  - `WI_drawLF` (function, line 416) `void WI_drawLF(void)`
  - `WI_drawEL` (function, line 452) `void WI_drawEL(void)`
  - `WI_drawOnLnode` (function, line 469) `void
WI_drawOnLnode
( int		n,
  patch_t*	c[] )`
  - `WI_initAnimatedBack` (function, line 516) `void WI_initAnimatedBack(void)`
  - `WI_updateAnimatedBack` (function, line 547) `void WI_updateAnimatedBack(void)`
  - `WI_drawAnimatedBack` (function, line 598) `void WI_drawAnimatedBack(void)`
  - `WI_drawNum` (function, line 626) `int
WI_drawNum
( int		x,
  int		y,
  int		n,
  int		digits )`
  - `WI_drawPercent` (function, line 683) `void
WI_drawPercent
( int		x,
  int		y,
  int		p )`
  - `WI_drawTime` (function, line 703) `void
WI_drawTime
( int		x,
  int		y,
  int		t )`
  - `WI_End` (function, line 738) `void WI_End(void)`
  - `WI_initNoState` (function, line 745) `void WI_initNoState(void)`
  - `WI_updateNoState` (function, line 752) `void WI_updateNoState(void)`
  - `WI_initShowNextLoc` (function, line 770) `void WI_initShowNextLoc(void)`
  - `WI_updateShowNextLoc` (function, line 780) `void WI_updateShowNextLoc(void)`
  - `WI_drawShowNextLoc` (function, line 790) `void WI_drawShowNextLoc(void)`
  - `WI_drawNoState` (function, line 831) `void WI_drawNoState(void)`
  - `WI_fragSum` (function, line 837) `int WI_fragSum(int playernum)`
  - `WI_initDeathmatchStats` (function, line 866) `void WI_initDeathmatchStats(void)`
  - `WI_updateDeathmatchStats` (function, line 895) `void WI_updateDeathmatchStats(void)`
  - `WI_drawDeathmatchStats` (function, line 998) `void WI_drawDeathmatchStats(void)`
  - `WI_initNetgameStats` (function, line 1088) `void WI_initNetgameStats(void)`
  - `WI_updateNetgameStats` (function, line 1114) `void WI_updateNetgameStats(void)`
  - `WI_drawNetgameStats` (function, line 1269) `void WI_drawNetgameStats(void)`
  - `WI_initStats` (function, line 1328) `void WI_initStats(void)`
  - `WI_updateStats` (function, line 1340) `void WI_updateStats(void)`
  - `WI_drawStats` (function, line 1446) `void WI_drawStats(void)`
  - `WI_checkForAccelerate` (function, line 1480) `void WI_checkForAccelerate(void)`
  - `WI_Ticker` (function, line 1514) `void WI_Ticker(void)`
  - `WI_loadUnloadData` (function, line 1553) `static void WI_loadUnloadData(load_callback_t callback)`
  - `WI_loadCallback` (function, line 1703) `static void WI_loadCallback(char *name, patch_t **variable)`
  - `WI_loadData` (function, line 1708) `void WI_loadData(void)`
  - `WI_unloadCallback` (function, line 1734) `static void WI_unloadCallback(char *name, patch_t **variable)`
  - `WI_unloadData` (function, line 1740) `void WI_unloadData(void)`
  - `WI_Drawer` (function, line 1751) `void WI_Drawer (void)`
  - `WI_initVariables` (function, line 1774) `void WI_initVariables(wbstartstruct_t* wbstartstruct)`
  - `WI_Start` (function, line 1817) `void WI_Start(wbstartstruct_t* wbstartstruct)`
  - `NUMEPISODES` (macro, line 61)
  - `NUMMAPS` (macro, line 62)
  - `WI_TITLEY` (macro, line 75)
  - `WI_SPACINGY` (macro, line 76)
  - `SP_STATSX` (macro, line 79)
  - `SP_STATSY` (macro, line 80)
  - `SP_TIMEX` (macro, line 81)
  - `SP_TIMEY` (macro, line 83)
  - `NG_STATSY` (macro, line 87)
  - `NG_STATSX` (macro, line 88)
  - `NG_SPACINGX` (macro, line 89)
  - `DM_MATRIXX` (macro, line 94)
  - `DM_MATRIXY` (macro, line 95)
  - `DM_SPACINGX` (macro, line 96)
  - `DM_TOTALSX` (macro, line 98)
  - `DM_KILLERSX` (macro, line 100)
  - `DM_KILLERSY` (macro, line 102)
  - `DM_VICTIMSX` (macro, line 103)
  - `DM_VICTIMSY` (macro, line 104)
  - `ANIM` (macro, line 221)
  - `SP_KILLS` (macro, line 288)
  - `SP_ITEMS` (macro, line 289)
  - `SP_SECRET` (macro, line 290)
  - `SP_FRAGS` (macro, line 291)
  - `SP_TIME` (macro, line 292)
  - `SP_PAR` (macro, line 293)
  - `SP_PAUSE` (macro, line 294)
  - `SHOWNEXTLOCDELAY` (macro, line 298)

## progs/doomgeneric/wi_stuff.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__WI_STUFF__` (macro, line 20)

## progs/doomgeneric/z_zone.c
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: c
- Symbols:
  - `memblock_s` (struct, line 39)
  - `Z_ClearZone` (function, line 71) `void Z_ClearZone (memzone_t* zone)`
  - `Z_Init` (function, line 97) `void Z_Init (void)`
  - `Z_Free` (function, line 126) `void Z_Free (void* ptr)`
  - `Z_Malloc` (function, line 182) `void*
Z_Malloc
( int		size,
  int		tag,
  void*		user )`
  - `Z_FreeTags` (function, line 297) `void
Z_FreeTags
( int		lowtag,
  int		hightag )`
  - `Z_DumpHeap` (function, line 327) `void
Z_DumpHeap
( int		lowtag,
  int		hightag )`
  - `Z_FileDumpHeap` (function, line 367) `void Z_FileDumpHeap (FILE* f)`
  - `Z_CheckHeap` (function, line 400) `void Z_CheckHeap (void)`
  - `Z_ChangeTag2` (function, line 429) `void Z_ChangeTag2(void *ptr, int tag, char *file, int line)`
  - `Z_ChangeUser` (function, line 445) `void Z_ChangeUser(void *ptr, void **user)`
  - `Z_FreeMemory` (function, line 466) `int Z_FreeMemory (void)`
  - `Z_ZoneSize` (function, line 483) `unsigned int Z_ZoneSize(void)`
  - `MEM_ALIGN` (macro, line 35)
  - `ZONEID` (macro, line 37)
  - `MINFRAGMENT` (macro, line 181)

## progs/doomgeneric/z_zone.h
- Layer: utility
- Doc: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can red
- Language: h
- Symbols:
  - `__Z_ZONE__` (macro, line 25)
  - `Z_ChangeTag` (macro, line 69)
