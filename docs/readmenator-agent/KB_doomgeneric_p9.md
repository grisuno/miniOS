# Subsystem: doomgeneric (page 9 of 12)
Previous: [KB_doomgeneric_p8.md](KB_doomgeneric_p8.md)

## progs/doomgeneric/p_spec.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: testing
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
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
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
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `EV_Teleport` (function, line 42) `int
EV_Teleport
( line_t*	line,
  int		side,
  mobj_t*	thing )`
- Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`

## progs/doomgeneric/p_tick.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
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
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `P_Ticker` (function, line 29) `void P_Ticker (void);`
  - `__P_TICK__` (macro, line 21) `#define __P_TICK__`
- Imported by: `progs/doomgeneric/g_game.c`

## progs/doomgeneric/p_user.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
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
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
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
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
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
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: data_access
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
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: data_access
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
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
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
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
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
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
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
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `__R_LOCAL__` (macro, line 21) `#define __R_LOCAL__`
- Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/r_bsp.h`, `progs/doomgeneric/r_data.h`, `progs/doomgeneric/r_draw.h`, `progs/doomgeneric/r_main.h`, `progs/doomgeneric/r_plane.h`, `progs/doomgeneric/r_segs.h`, `progs/doomgeneric/r_things.h`, `progs/doomgeneric/tables.h`
- Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/hu_lib.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/r_data.c`, `progs/doomgeneric/r_draw.c`, `progs/doomgeneric/r_main.c`, `progs/doomgeneric/r_plane.c`, `progs/doomgeneric/r_segs.c`, `progs/doomgeneric/r_things.c`, `progs/doomgeneric/st_lib.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/wi_stuff.c`, `progs/quake2generic/q2generic_minios.c`

## progs/doomgeneric/r_main.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
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
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
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


Next: [KB_doomgeneric_p10.md](KB_doomgeneric_p10.md)
