# Symbols (page 16 of 25)
Previous: [SYMBOLS_p15.md](SYMBOLS_p15.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `P_FindHighestCeilingSurrounding` | function | `progs/doomgeneric/p_spec.c:417` | `fixed_t	P_FindHighestCeilingSurrounding(sector_t* sec)` |
| `P_FindHighestFloorSurrounding` | function | `progs/doomgeneric/p_spec.c:296` | `fixed_t	P_FindHighestFloorSurrounding(sector_t *sec)` |
| `P_FindLowestCeilingSurrounding` | function | `progs/doomgeneric/p_spec.c:392` | `fixed_t P_FindLowestCeilingSurrounding(sector_t* sec)` |
| `P_FindLowestFloorSurrounding` | function | `progs/doomgeneric/p_spec.c:269` | `fixed_t	P_FindLowestFloorSurrounding(sector_t* sec)` |
| `P_FindMinSurroundingLight` | function | `progs/doomgeneric/p_spec.c:464` | `int P_FindMinSurroundingLight ( sector_t*	sector,   int		max )` |
| `P_FindNextHighestFloor` | function | `progs/doomgeneric/p_spec.c:330` | `fixed_t P_FindNextHighestFloor ( sector_t* sec,   int       currentheight )` |
| `P_FindSectorFromLineTag` | function | `progs/doomgeneric/p_spec.c:444` | `int P_FindSectorFromLineTag ( line_t*	line,   int		start )` |
| `P_InitPicAnims` | function | `progs/doomgeneric/p_spec.c:143` | `void P_InitPicAnims (void)` |
| `P_PlayerInSpecialSector` | function | `progs/doomgeneric/p_spec.c:1019` | `void P_PlayerInSpecialSector (player_t* player)` |
| `P_ShootSpecialLine` | function | `progs/doomgeneric/p_spec.c:969` | `void P_ShootSpecialLine ( mobj_t*	thing,   line_t*	line )` |
| `P_SpawnSpecials` | function | `progs/doomgeneric/p_spec.c:1374` | `void P_SpawnSpecials (void)` |
| `P_UpdateSpecials` | function | `progs/doomgeneric/p_spec.c:1093` | `void P_UpdateSpecials (void)` |
| `anim_t` | struct | `progs/doomgeneric/p_spec.c:55` | `` |
| `animdef_t` | struct | `progs/doomgeneric/p_spec.c:68` | `` |
| `anims` | variable | `progs/doomgeneric/p_spec.c:80` | `extern anim_t anims[MAXANIMS];` |
| `getNextSector` | function | `progs/doomgeneric/p_spec.c:250` | `sector_t* getNextSector ( line_t*	line,   sector_t*	sec )` |
| `getSector` | function | `progs/doomgeneric/p_spec.c:219` | `sector_t* getSector ( int		currentSector,   int		line,   int		side )` |
| `getSide` | function | `progs/doomgeneric/p_spec.c:203` | `side_t* getSide ( int		currentSector,   int		line,   int		side )` |
| `lastanim` | variable | `progs/doomgeneric/p_spec.c:81` | `extern anim_t* lastanim;` |
| `linespeciallist` | variable | `progs/doomgeneric/p_spec.c:139` | `extern line_t* linespeciallist[MAXLINEANIMS];` |
| `numflats` | variable | `progs/doomgeneric/p_spec.c:1185` | `extern int numflats;` |
| `numlinespecials` | variable | `progs/doomgeneric/p_spec.c:138` | `extern short numlinespecials;` |
| `twoSided` | function | `progs/doomgeneric/p_spec.c:234` | `int twoSided ( int	sector,   int	line )` |
| `BUTTONTIME` | macro | `progs/doomgeneric/p_spec.h:244` | `#define BUTTONTIME` |
| `CEILSPEED` | macro | `progs/doomgeneric/p_spec.h:513` | `#define CEILSPEED` |
| `CEILWAIT` | macro | `progs/doomgeneric/p_spec.h:514` | `#define CEILWAIT` |
| `EV_BuildStairs` | function | `progs/doomgeneric/p_spec.h:617` | `int EV_BuildStairs ( line_t* line, stair_e type );` |
| `EV_CeilingCrushStop` | function | `progs/doomgeneric/p_spec.h:527` | `int EV_CeilingCrushStop(line_t* line);` |
| `EV_DoCeiling` | function | `progs/doomgeneric/p_spec.h:520` | `int EV_DoCeiling ( line_t* line, ceiling_e type );` |
| `EV_DoDonut` | function | `progs/doomgeneric/p_spec.h:114` | `int EV_DoDonut(line_t* line);` |
| `EV_DoDoor` | function | `progs/doomgeneric/p_spec.h:370` | `int EV_DoDoor ( line_t* line, vldoor_e type );` |
| `EV_DoFloor` | function | `progs/doomgeneric/p_spec.h:622` | `int EV_DoFloor ( line_t* line, floor_e floortype );` |
| `EV_DoLockedDoor` | function | `progs/doomgeneric/p_spec.h:375` | `int EV_DoLockedDoor ( line_t* line, vldoor_e type, mobj_t* thing );` |
| `EV_DoPlat` | function | `progs/doomgeneric/p_spec.h:311` | `int EV_DoPlat ( line_t* line, plattype_e type, int amount );` |
| `EV_LightTurnOn` | function | `progs/doomgeneric/p_spec.h:193` | `void EV_LightTurnOn ( line_t* line, int bright );` |
| `EV_SlidingDoor` | function | `progs/doomgeneric/p_spec.h:467` | `void EV_SlidingDoor ( line_t* line, mobj_t* thing );` |
| `EV_StartLightStrobing` | function | `progs/doomgeneric/p_spec.h:189` | `void EV_StartLightStrobing(line_t* line);` |
| `EV_StopPlat` | function | `progs/doomgeneric/p_spec.h:318` | `void EV_StopPlat(line_t* line);` |
| `EV_Teleport` | function | `progs/doomgeneric/p_spec.h:632` | `int EV_Teleport ( line_t* line, int side, mobj_t* thing );` |
| `EV_TurnTagLightsOff` | function | `progs/doomgeneric/p_spec.h:190` | `void EV_TurnTagLightsOff(line_t* line);` |
| `EV_VerticalDoor` | function | `progs/doomgeneric/p_spec.h:365` | `void EV_VerticalDoor ( line_t* line, mobj_t* thing );` |
| `FASTDARK` | macro | `progs/doomgeneric/p_spec.h:175` | `#define FASTDARK` |
| `FLOORSPEED` | macro | `progs/doomgeneric/p_spec.h:597` | `#define FLOORSPEED` |
| `GLOWSPEED` | macro | `progs/doomgeneric/p_spec.h:173` | `#define GLOWSPEED` |
| `MAXBUTTONS` | macro | `progs/doomgeneric/p_spec.h:241` | `#define MAXBUTTONS` |
| `MAXCEILINGS` | macro | `progs/doomgeneric/p_spec.h:515` | `#define MAXCEILINGS` |
| `MAXPLATS` | macro | `progs/doomgeneric/p_spec.h:303` | `#define MAXPLATS` |
| `MAXSLIDEDOORS` | macro | `progs/doomgeneric/p_spec.h:462` | `#define MAXSLIDEDOORS` |
| `MAXSWITCHES` | macro | `progs/doomgeneric/p_spec.h:238` | `#define MAXSWITCHES` |
| `MO_TELEPORTMAN` | macro | `progs/doomgeneric/p_spec.h:35` | `#define MO_TELEPORTMAN` |
| `PLATSPEED` | macro | `progs/doomgeneric/p_spec.h:302` | `#define PLATSPEED` |
| `PLATWAIT` | macro | `progs/doomgeneric/p_spec.h:301` | `#define PLATWAIT` |
| `P_ActivateInStasis` | function | `progs/doomgeneric/p_spec.h:319` | `void P_ActivateInStasis(int tag);` |
| `P_ActivateInStasisCeiling` | function | `progs/doomgeneric/p_spec.h:528` | `void P_ActivateInStasisCeiling(line_t* line);` |
| `P_AddActiveCeiling` | function | `progs/doomgeneric/p_spec.h:525` | `void P_AddActiveCeiling(ceiling_t* c);` |
| `P_AddActivePlat` | function | `progs/doomgeneric/p_spec.h:316` | `void P_AddActivePlat(plat_t* plat);` |
| `P_ChangeSwitchTexture` | function | `progs/doomgeneric/p_spec.h:249` | `void P_ChangeSwitchTexture ( line_t* line, int useAgain );` |
| `P_CrossSpecialLine` | function | `progs/doomgeneric/p_spec.h:60` | `void P_CrossSpecialLine ( int linenum, int side, mobj_t* thing );` |
| `P_FindHighestCeilingSurrounding` | function | `progs/doomgeneric/p_spec.h:93` | `fixed_t P_FindHighestCeilingSurrounding(sector_t* sec);` |
| `P_FindHighestFloorSurrounding` | function | `progs/doomgeneric/p_spec.h:85` | `fixed_t P_FindHighestFloorSurrounding(sector_t* sec);` |
| `P_FindLowestCeilingSurrounding` | function | `progs/doomgeneric/p_spec.h:92` | `fixed_t P_FindLowestCeilingSurrounding(sector_t* sec);` |
| `P_FindLowestFloorSurrounding` | function | `progs/doomgeneric/p_spec.h:84` | `fixed_t P_FindLowestFloorSurrounding(sector_t* sec);` |
| `P_FindMinSurroundingLight` | function | `progs/doomgeneric/p_spec.h:101` | `int P_FindMinSurroundingLight ( sector_t* sector, int max );` |
| `P_FindNextHighestFloor` | function | `progs/doomgeneric/p_spec.h:88` | `fixed_t P_FindNextHighestFloor ( sector_t* sec, int currentheight );` |
| `P_FindSectorFromLineTag` | function | `progs/doomgeneric/p_spec.h:96` | `int P_FindSectorFromLineTag ( line_t* line, int start );` |
| `P_InitPicAnims` | function | `progs/doomgeneric/p_spec.h:39` | `void P_InitPicAnims (void);` |
| `P_InitSlidingDoorFrames` | function | `progs/doomgeneric/p_spec.h:464` | `void P_InitSlidingDoorFrames(void);` |
| `P_InitSwitchList` | function | `progs/doomgeneric/p_spec.h:253` | `void P_InitSwitchList(void);` |
| `P_PlayerInSpecialSector` | function | `progs/doomgeneric/p_spec.h:65` | `void P_PlayerInSpecialSector (player_t* player);` |
| `P_RemoveActiveCeiling` | function | `progs/doomgeneric/p_spec.h:526` | `void P_RemoveActiveCeiling(ceiling_t* c);` |
| `P_RemoveActivePlat` | function | `progs/doomgeneric/p_spec.h:317` | `void P_RemoveActivePlat(plat_t* plat);` |
| `P_ShootSpecialLine` | function | `progs/doomgeneric/p_spec.h:55` | `void P_ShootSpecialLine ( mobj_t* thing, line_t* line );` |
| `P_SpawnDoorCloseIn30` | function | `progs/doomgeneric/p_spec.h:381` | `void P_SpawnDoorCloseIn30 (sector_t* sec);` |
| `P_SpawnDoorRaiseIn5Mins` | function | `progs/doomgeneric/p_spec.h:384` | `void P_SpawnDoorRaiseIn5Mins ( sector_t* sec, int secnum );` |
| `P_SpawnFireFlicker` | function | `progs/doomgeneric/p_spec.h:178` | `void P_SpawnFireFlicker (sector_t* sector);` |
| `P_SpawnGlowingLight` | function | `progs/doomgeneric/p_spec.h:198` | `void P_SpawnGlowingLight(sector_t* sector);` |
| `P_SpawnLightFlash` | function | `progs/doomgeneric/p_spec.h:180` | `void P_SpawnLightFlash (sector_t* sector);` |
| `P_SpawnSpecials` | function | `progs/doomgeneric/p_spec.h:42` | `void P_SpawnSpecials (void);` |
| `P_SpawnStrobeFlash` | function | `progs/doomgeneric/p_spec.h:184` | `void P_SpawnStrobeFlash ( sector_t* sector, int fastOrSlow, int inSync );` |
| `P_UpdateSpecials` | function | `progs/doomgeneric/p_spec.h:45` | `void P_UpdateSpecials (void);` |
| `SDOORWAIT` | macro | `progs/doomgeneric/p_spec.h:458` | `#define SDOORWAIT` |
| `SLOWDARK` | macro | `progs/doomgeneric/p_spec.h:176` | `#define SLOWDARK` |
| `SNUMFRAMES` | macro | `progs/doomgeneric/p_spec.h:456` | `#define SNUMFRAMES` |
| `STROBEBRIGHT` | macro | `progs/doomgeneric/p_spec.h:174` | `#define STROBEBRIGHT` |
| `SWAITTICS` | macro | `progs/doomgeneric/p_spec.h:459` | `#define SWAITTICS` |
| `T_Glow` | function | `progs/doomgeneric/p_spec.h:197` | `void T_Glow(glow_t* g);` |
| `T_LightFlash` | function | `progs/doomgeneric/p_spec.h:179` | `void T_LightFlash (lightflash_t* flash);` |
| `T_MoveCeiling` | function | `progs/doomgeneric/p_spec.h:524` | `void T_MoveCeiling (ceiling_t* ceiling);` |
| `T_MoveFloor` | function | `progs/doomgeneric/p_spec.h:626` | `void T_MoveFloor( floormove_t* floor);` |
| `T_PlatRaise` | function | `progs/doomgeneric/p_spec.h:308` | `void T_PlatRaise(plat_t* plat);` |
| `T_StrobeFlash` | function | `progs/doomgeneric/p_spec.h:181` | `void T_StrobeFlash (strobe_t* flash);` |
| `T_VerticalDoor` | function | `progs/doomgeneric/p_spec.h:380` | `void T_VerticalDoor (vldoor_t* door);` |
| `VDOORSPEED` | macro | `progs/doomgeneric/p_spec.h:361` | `#define VDOORSPEED` |
| `VDOORWAIT` | macro | `progs/doomgeneric/p_spec.h:362` | `#define VDOORWAIT` |
| `__P_SPEC__` | macro | `progs/doomgeneric/p_spec.h:24` | `#define __P_SPEC__` |
| `activeceilings` | variable | `progs/doomgeneric/p_spec.h:517` | `extern ceiling_t* activeceilings[MAXCEILINGS];` |
| `activeplats` | variable | `progs/doomgeneric/p_spec.h:306` | `extern plat_t* activeplats[MAXPLATS];` |
| `button_t` | struct | `progs/doomgeneric/p_spec.h:224` | `` |
| `buttonlist` | variable | `progs/doomgeneric/p_spec.h:246` | `extern button_t buttonlist[MAXBUTTONS];` |
| `ceiling_t` | struct | `progs/doomgeneric/p_spec.h:490` | `` |
| `fireflicker_t` | struct | `progs/doomgeneric/p_spec.h:121` | `` |
| `floormove_t` | struct | `progs/doomgeneric/p_spec.h:581` | `` |
| `getNextSector` | function | `progs/doomgeneric/p_spec.h:106` | `sector_t* getNextSector ( line_t* line, sector_t* sec );` |
| `getSector` | function | `progs/doomgeneric/p_spec.h:73` | `sector_t* getSector ( int currentSector, int line, int side );` |
| `getSide` | function | `progs/doomgeneric/p_spec.h:79` | `side_t* getSide ( int currentSector, int line, int side );` |
| `glow_t` | struct | `progs/doomgeneric/p_spec.h:162` | `` |
| `levelTimeCount` | variable | `progs/doomgeneric/p_spec.h:31` | `extern int levelTimeCount;` |
| `levelTimer` | variable | `progs/doomgeneric/p_spec.h:30` | `extern boolean levelTimer;` |
| `lightflash_t` | struct | `progs/doomgeneric/p_spec.h:133` | `` |
| `plat_t` | struct | `progs/doomgeneric/p_spec.h:282` | `` |
| `slidedoor_t` | struct | `progs/doomgeneric/p_spec.h:415` | `` |
| `slideframe_t` | struct | `progs/doomgeneric/p_spec.h:446` | `` |
| `slidename_t` | struct | `progs/doomgeneric/p_spec.h:431` | `` |
| `strobe_t` | struct | `progs/doomgeneric/p_spec.h:147` | `` |
| `switchlist_t` | struct | `progs/doomgeneric/p_spec.h:206` | `` |
| `twoSided` | function | `progs/doomgeneric/p_spec.h:68` | `int twoSided ( int sector, int line );` |
| `vldoor_t` | struct | `progs/doomgeneric/p_spec.h:340` | `` |
| `P_ChangeSwitchTexture` | function | `progs/doomgeneric/p_switch.c:195` | `void P_ChangeSwitchTexture ( line_t*	line,   int 		useAgain )` |
| `P_InitSwitchList` | function | `progs/doomgeneric/p_switch.c:101` | `void P_InitSwitchList(void)` |
| `P_StartButton` | function | `progs/doomgeneric/p_switch.c:149` | `void P_StartButton ( line_t*	line,   bwhere_e	w,   int		texture,   int		time )` |
| `P_UseSpecialLine` | function | `progs/doomgeneric/p_switch.c:270` | `boolean P_UseSpecialLine ( mobj_t*	thing,   line_t*	line,   int		side )` |
| `EV_Teleport` | function | `progs/doomgeneric/p_telept.c:42` | `int EV_Teleport ( line_t*	line,   int		side,   mobj_t*	thing )` |
| `P_AddThinker` | function | `progs/doomgeneric/p_tick.c:58` | `void P_AddThinker (thinker_t* thinker)` |
| `P_AllocateThinker` | function | `progs/doomgeneric/p_tick.c:85` | `void P_AllocateThinker (thinker_t*	thinker)` |
| `P_InitThinkers` | function | `progs/doomgeneric/p_tick.c:46` | `void P_InitThinkers (void)` |
| `P_RemoveThinker` | function | `progs/doomgeneric/p_tick.c:73` | `void P_RemoveThinker (thinker_t* thinker)` |
| `P_RunThinkers` | function | `progs/doomgeneric/p_tick.c:94` | `void P_RunThinkers (void)` |
| `P_Ticker` | function | `progs/doomgeneric/p_tick.c:123` | `void P_Ticker (void)` |
| `P_Ticker` | function | `progs/doomgeneric/p_tick.h:29` | `void P_Ticker (void);` |
| `__P_TICK__` | macro | `progs/doomgeneric/p_tick.h:21` | `#define __P_TICK__` |
| `ANG5` | macro | `progs/doomgeneric/p_user.c:173` | `#define ANG5` |
| `INVERSECOLORMAP` | macro | `progs/doomgeneric/p_user.c:34` | `#define INVERSECOLORMAP` |
| `MAXBOB` | macro | `progs/doomgeneric/p_user.c:42` | `#define MAXBOB` |
| `P_CalcHeight` | function | `progs/doomgeneric/p_user.c:70` | `void P_CalcHeight (player_t* player)` |
| `P_DeathThink` | function | `progs/doomgeneric/p_user.c:175` | `void P_DeathThink (player_t* player)` |
| `P_MovePlayer` | function | `progs/doomgeneric/p_user.c:141` | `void P_MovePlayer (player_t* player)` |
| `P_PlayerThink` | function | `progs/doomgeneric/p_user.c:229` | `void P_PlayerThink (player_t* player)` |
| `P_Thrust` | function | `progs/doomgeneric/p_user.c:52` | `void P_Thrust ( player_t*	player,   angle_t	angle,   fixed_t	move )` |
| `MAXSEGS` | macro | `progs/doomgeneric/r_bsp.c:81` | `#define MAXSEGS` |
| `R_AddLine` | function | `progs/doomgeneric/r_bsp.c:252` | `void R_AddLine (seg_t*	line)` |
| `R_CheckBBox` | function | `progs/doomgeneric/r_bsp.c:374` | `boolean R_CheckBBox (fixed_t*	bspcoord)` |
| `R_ClearClipSegs` | function | `progs/doomgeneric/r_bsp.c:238` | `void R_ClearClipSegs (void)` |
| `R_ClearDrawSegs` | function | `progs/doomgeneric/r_bsp.c:61` | `void R_ClearDrawSegs (void)` |
| `R_ClipPassWallSegment` | function | `progs/doomgeneric/r_bsp.c:190` | `void R_ClipPassWallSegment ( int	first,   int	last )` |
| `R_ClipSolidWallSegment` | function | `progs/doomgeneric/r_bsp.c:97` | `void R_ClipSolidWallSegment ( int			first,   int			last )` |
| `R_RenderBSPNode` | function | `progs/doomgeneric/r_bsp.c:545` | `void R_RenderBSPNode (int bspnum)` |
| `R_StoreWallRange` | function | `progs/doomgeneric/r_bsp.c:51` | `void R_StoreWallRange ( int start, int stop );` |
| `R_Subsector` | function | `progs/doomgeneric/r_bsp.c:490` | `void R_Subsector (int num)` |
| `cliprange_t` | struct | `progs/doomgeneric/r_bsp.c:73` | `` |
| `R_ClearClipSegs` | function | `progs/doomgeneric/r_bsp.h:54` | `void R_ClearClipSegs (void);` |
| `R_ClearDrawSegs` | function | `progs/doomgeneric/r_bsp.h:55` | `void R_ClearDrawSegs (void);` |
| `R_RenderBSPNode` | function | `progs/doomgeneric/r_bsp.h:58` | `void R_RenderBSPNode (int bspnum);` |
| `__R_BSP__` | macro | `progs/doomgeneric/r_bsp.h:21` | `#define __R_BSP__` |
| `backsector` | variable | `progs/doomgeneric/r_bsp.h:29` | `extern sector_t* backsector;` |
| `curline` | variable | `progs/doomgeneric/r_bsp.h:25` | `extern seg_t* curline;` |
| `drawsegs` | variable | `progs/doomgeneric/r_bsp.h:42` | `extern drawseg_t drawsegs[MAXDRAWSEGS];` |
| `ds_p` | variable | `progs/doomgeneric/r_bsp.h:43` | `extern drawseg_t* ds_p;` |
| `dscalelight` | variable | `progs/doomgeneric/r_bsp.h:47` | `extern lighttable_t** dscalelight;` |
| `frontsector` | variable | `progs/doomgeneric/r_bsp.h:28` | `extern sector_t* frontsector;` |
| `hscalelight` | variable | `progs/doomgeneric/r_bsp.h:45` | `extern lighttable_t** hscalelight;` |
| `linedef` | variable | `progs/doomgeneric/r_bsp.h:27` | `extern line_t* linedef;` |
| `markceiling` | variable | `progs/doomgeneric/r_bsp.h:38` | `extern boolean markceiling;` |
| `markfloor` | variable | `progs/doomgeneric/r_bsp.h:37` | `extern boolean markfloor;` |
| `rw_stopx` | variable | `progs/doomgeneric/r_bsp.h:32` | `extern int rw_stopx;` |
| `rw_x` | variable | `progs/doomgeneric/r_bsp.h:31` | `extern int rw_x;` |
| `segtextured` | variable | `progs/doomgeneric/r_bsp.h:34` | `extern boolean segtextured;` |
| `sidedef` | variable | `progs/doomgeneric/r_bsp.h:26` | `extern side_t* sidedef;` |
| `skymap` | variable | `progs/doomgeneric/r_bsp.h:40` | `extern boolean skymap;` |
| `vscalelight` | variable | `progs/doomgeneric/r_bsp.h:46` | `extern lighttable_t** vscalelight;` |
| `GenerateTextureHashTable` | function | `progs/doomgeneric/r_data.c:404` | `static void GenerateTextureHashTable(void)` |
| `R_CheckTextureNumForName` | function | `progs/doomgeneric/r_data.c:744` | `int	R_CheckTextureNumForName (char *name)` |
| `R_DrawColumnInCache` | function | `progs/doomgeneric/r_data.c:186` | `void R_DrawColumnInCache ( column_t*	patch,   byte*		cache,   int		originy,   int		cacheheight )` |
| `R_FlatNumForName` | function | `progs/doomgeneric/r_data.c:720` | `int R_FlatNumForName (char* name)` |
| `R_GenerateComposite` | function | `progs/doomgeneric/r_data.c:226` | `void R_GenerateComposite (int texnum)` |
| `R_GenerateLookup` | function | `progs/doomgeneric/r_data.c:294` | `void R_GenerateLookup (int texnum)` |
| `R_GetColumn` | function | `progs/doomgeneric/r_data.c:383` | `byte* R_GetColumn ( int		tex,   int		col )` |
| `R_InitColormaps` | function | `progs/doomgeneric/r_data.c:685` | `void R_InitColormaps (void)` |
| `R_InitData` | function | `progs/doomgeneric/r_data.c:703` | `void R_InitData (void)` |
| `R_InitFlats` | function | `progs/doomgeneric/r_data.c:633` | `void R_InitFlats (void)` |
| `R_InitSpriteLumps` | function | `progs/doomgeneric/r_data.c:655` | `void R_InitSpriteLumps (void)` |
| `R_InitTextures` | function | `progs/doomgeneric/r_data.c:451` | `void R_InitTextures (void)` |
| `R_PrecacheLevel` | function | `progs/doomgeneric/r_data.c:800` | `void R_PrecacheLevel (void)` |
| `R_TextureNumForName` | function | `progs/doomgeneric/r_data.c:775` | `int	R_TextureNumForName (char* name)` |
| `texpatch_t` | struct | `progs/doomgeneric/r_data.c:89` | `` |
| `texture_s` | struct | `progs/doomgeneric/r_data.c:106` | `` |
| `texture_t` | type_alias | `progs/doomgeneric/r_data.c:103` | `typedef struct texture_s texture_t;` |
| `R_CheckTextureNumForName` | function | `progs/doomgeneric/r_data.h:49` | `int R_CheckTextureNumForName (char *name);` |
| `R_FlatNumForName` | function | `progs/doomgeneric/r_data.h:43` | `int R_FlatNumForName (char* name);` |
| `R_GetColumn` | function | `progs/doomgeneric/r_data.h:30` | `byte* R_GetColumn ( int tex, int col );` |
| `R_InitData` | function | `progs/doomgeneric/r_data.h:36` | `void R_InitData (void);` |
| `R_PrecacheLevel` | function | `progs/doomgeneric/r_data.h:37` | `void R_PrecacheLevel (void);` |
| `R_TextureNumForName` | function | `progs/doomgeneric/r_data.h:48` | `int R_TextureNumForName (char *name);` |
| `__R_DATA__` | macro | `progs/doomgeneric/r_data.h:22` | `#define __R_DATA__` |
| `MAXDRAWSEGS` | macro | `progs/doomgeneric/r_defs.h:51` | `#define MAXDRAWSEGS` |
| `SIL_BOTH` | macro | `progs/doomgeneric/r_defs.h:49` | `#define SIL_BOTH` |
| `SIL_BOTTOM` | macro | `progs/doomgeneric/r_defs.h:47` | `#define SIL_BOTTOM` |
| `SIL_NONE` | macro | `progs/doomgeneric/r_defs.h:46` | `#define SIL_NONE` |
| `SIL_TOP` | macro | `progs/doomgeneric/r_defs.h:48` | `#define SIL_TOP` |
| `__R_DEFS__` | macro | `progs/doomgeneric/r_defs.h:21` | `#define __R_DEFS__` |
| `curline` | type_alias | `progs/doomgeneric/r_defs.h:306` | `typedef struct drawseg_s { seg_t* curline;` |
| `degenmobj_t` | struct | `progs/doomgeneric/r_defs.h:84` | `` |
| `drawseg_s` | struct | `progs/doomgeneric/r_defs.h:306` | `` |
| `lighttable_t` | type_alias | `progs/doomgeneric/r_defs.h:298` | `typedef byte lighttable_t;` |
| `line_s` | struct | `progs/doomgeneric/r_defs.h:76` | `` |
| `line_s` | struct | `progs/doomgeneric/r_defs.h:175` | `` |
| `node_t` | struct | `progs/doomgeneric/r_defs.h:261` | `` |
| `prev` | type_alias | `progs/doomgeneric/r_defs.h:338` | `typedef struct vissprite_s { // Doubly linked list. struct vissprite_s* prev;` |
| `sector` | type_alias | `progs/doomgeneric/r_defs.h:223` | `typedef struct subsector_s { sector_t* sector;` |
| `sector_t` | struct | `progs/doomgeneric/r_defs.h:97` | `` |
| `seg_t` | struct | `progs/doomgeneric/r_defs.h:236` | `` |
| `side_t` | struct | `progs/doomgeneric/r_defs.h:140` | `` |
| `spritedef_t` | struct | `progs/doomgeneric/r_defs.h:411` | `` |
| `spriteframe_t` | struct | `progs/doomgeneric/r_defs.h:390` | `` |
| `subsector_s` | struct | `progs/doomgeneric/r_defs.h:223` | `` |
| `v1` | type_alias | `progs/doomgeneric/r_defs.h:172` | `typedef struct line_s { // Vertices, from v1 to v2. vertex_t* v1;` |
| `vertex_t` | struct | `progs/doomgeneric/r_defs.h:67` | `` |
| `visplane_t` | struct | `progs/doomgeneric/r_defs.h:423` | `` |
| `vissprite_s` | struct | `progs/doomgeneric/r_defs.h:338` | `` |
| `FUZZOFF` | macro | `progs/doomgeneric/r_draw.c:258` | `#define FUZZOFF` |
| `FUZZTABLE` | macro | `progs/doomgeneric/r_draw.c:257` | `#define FUZZTABLE` |
| `MAXHEIGHT` | macro | `progs/doomgeneric/r_draw.c:42` | `#define MAXHEIGHT` |
| `MAXWIDTH` | macro | `progs/doomgeneric/r_draw.c:41` | `#define MAXWIDTH` |
| `R_DrawColumn` | function | `progs/doomgeneric/r_draw.c:102` | `void R_DrawColumn (void)` |
| `R_DrawColumn` | function | `progs/doomgeneric/r_draw.c:152` | `void R_DrawColumn (void)` |
| `R_DrawColumnLow` | function | `progs/doomgeneric/r_draw.c:208` | `void R_DrawColumnLow (void)` |
| `R_DrawFuzzColumn` | function | `progs/doomgeneric/r_draw.c:283` | `void R_DrawFuzzColumn (void)` |
| `R_DrawFuzzColumnLow` | function | `progs/doomgeneric/r_draw.c:342` | `void R_DrawFuzzColumnLow (void)` |
| `R_DrawSpan` | function | `progs/doomgeneric/r_draw.c:590` | `void R_DrawSpan (void)` |
| `R_DrawSpan` | function | `progs/doomgeneric/r_draw.c:646` | `void R_DrawSpan (void)` |
| `R_DrawSpanLow` | function | `progs/doomgeneric/r_draw.c:719` | `void R_DrawSpanLow (void)` |
| `R_DrawTranslatedColumn` | function | `progs/doomgeneric/r_draw.c:424` | `void R_DrawTranslatedColumn (void)` |
| `R_DrawTranslatedColumnLow` | function | `progs/doomgeneric/r_draw.c:468` | `void R_DrawTranslatedColumnLow (void)` |
| `R_DrawViewBorder` | function | `progs/doomgeneric/r_draw.c:941` | `void R_DrawViewBorder (void)` |
| `R_FillBackScreen` | function | `progs/doomgeneric/r_draw.c:812` | `void R_FillBackScreen (void)` |
| `R_InitBuffer` | function | `progs/doomgeneric/r_draw.c:777` | `void R_InitBuffer ( int		width,   int		height )` |
| `R_InitTranslationTables` | function | `progs/doomgeneric/r_draw.c:530` | `void R_InitTranslationTables (void)` |
| `R_VideoErase` | function | `progs/doomgeneric/r_draw.c:919` | `void R_VideoErase ( unsigned	ofs,   int		count )` |
| `SBARHEIGHT` | macro | `progs/doomgeneric/r_draw.c:45` | `#define SBARHEIGHT` |
| `R_DrawColumn` | function | `progs/doomgeneric/r_draw.h:40` | `void R_DrawColumn (void);` |
| `R_DrawColumnLow` | function | `progs/doomgeneric/r_draw.h:41` | `void R_DrawColumnLow (void);` |
| `R_DrawFuzzColumn` | function | `progs/doomgeneric/r_draw.h:44` | `void R_DrawFuzzColumn (void);` |
| `R_DrawFuzzColumnLow` | function | `progs/doomgeneric/r_draw.h:45` | `void R_DrawFuzzColumnLow (void);` |
| `R_DrawSpan` | function | `progs/doomgeneric/r_draw.h:78` | `void R_DrawSpan (void);` |
| `R_DrawSpanLow` | function | `progs/doomgeneric/r_draw.h:81` | `void R_DrawSpanLow (void);` |
| `R_DrawTranslatedColumn` | function | `progs/doomgeneric/r_draw.h:50` | `void R_DrawTranslatedColumn (void);` |
| `R_DrawTranslatedColumnLow` | function | `progs/doomgeneric/r_draw.h:51` | `void R_DrawTranslatedColumnLow (void);` |
| `R_DrawViewBorder` | function | `progs/doomgeneric/r_draw.h:100` | `void R_DrawViewBorder (void);` |
| `R_FillBackScreen` | function | `progs/doomgeneric/r_draw.h:97` | `void R_FillBackScreen (void);` |
| `R_InitBuffer` | function | `progs/doomgeneric/r_draw.h:85` | `void R_InitBuffer ( int width, int height );` |
| `R_InitTranslationTables` | function | `progs/doomgeneric/r_draw.h:92` | `void R_InitTranslationTables (void);` |
| `R_VideoErase` | function | `progs/doomgeneric/r_draw.h:54` | `void R_VideoErase ( unsigned ofs, int count );` |
| `__R_DRAW__` | macro | `progs/doomgeneric/r_draw.h:21` | `#define __R_DRAW__` |
| `dc_colormap` | variable | `progs/doomgeneric/r_draw.h:26` | `extern lighttable_t* dc_colormap;` |
| `dc_iscale` | variable | `progs/doomgeneric/r_draw.h:30` | `extern fixed_t dc_iscale;` |
| `dc_source` | variable | `progs/doomgeneric/r_draw.h:34` | `extern byte* dc_source;` |
| `dc_texturemid` | variable | `progs/doomgeneric/r_draw.h:31` | `extern fixed_t dc_texturemid;` |
| `dc_translation` | variable | `progs/doomgeneric/r_draw.h:73` | `extern byte* dc_translation;` |
| `dc_x` | variable | `progs/doomgeneric/r_draw.h:27` | `extern int dc_x;` |
| `dc_yh` | variable | `progs/doomgeneric/r_draw.h:29` | `extern int dc_yh;` |
| `dc_yl` | variable | `progs/doomgeneric/r_draw.h:28` | `extern int dc_yl;` |
| `ds_colormap` | variable | `progs/doomgeneric/r_draw.h:62` | `extern lighttable_t* ds_colormap;` |
| `ds_source` | variable | `progs/doomgeneric/r_draw.h:70` | `extern byte* ds_source;` |
| `ds_x1` | variable | `progs/doomgeneric/r_draw.h:59` | `extern int ds_x1;` |
| `ds_x2` | variable | `progs/doomgeneric/r_draw.h:60` | `extern int ds_x2;` |
| `ds_xfrac` | variable | `progs/doomgeneric/r_draw.h:64` | `extern fixed_t ds_xfrac;` |
| `ds_xstep` | variable | `progs/doomgeneric/r_draw.h:66` | `extern fixed_t ds_xstep;` |
| `ds_y` | variable | `progs/doomgeneric/r_draw.h:58` | `extern int ds_y;` |
| `ds_yfrac` | variable | `progs/doomgeneric/r_draw.h:65` | `extern fixed_t ds_yfrac;` |
| `ds_ystep` | variable | `progs/doomgeneric/r_draw.h:67` | `extern fixed_t ds_ystep;` |
| `translationtables` | variable | `progs/doomgeneric/r_draw.h:72` | `extern byte* translationtables;` |
| `__R_LOCAL__` | macro | `progs/doomgeneric/r_local.h:21` | `#define __R_LOCAL__` |
| `DISTMAP` | macro | `progs/doomgeneric/r_main.c:608` | `#define DISTMAP` |
| `FIELDOFVIEW` | macro | `progs/doomgeneric/r_main.c:43` | `#define FIELDOFVIEW` |
| `R_AddPointToBox` | function | `progs/doomgeneric/r_main.c:123` | `void R_AddPointToBox ( int		x,   int		y,   fixed_t*	box )` |
| `R_ExecuteSetViewSize` | function | `progs/doomgeneric/r_main.c:667` | `void R_ExecuteSetViewSize (void)` |
| `R_Init` | function | `progs/doomgeneric/r_main.c:767` | `void R_Init (void)` |
| `R_InitLightTables` | function | `progs/doomgeneric/r_main.c:610` | `void R_InitLightTables (void)` |
| `R_InitPointToAngle` | function | `progs/doomgeneric/r_main.c:422` | `void R_InitPointToAngle (void)` |
| `R_InitTables` | function | `progs/doomgeneric/r_main.c:505` | `void R_InitTables (void)` |
| `R_InitTextureMapping` | function | `progs/doomgeneric/r_main.c:540` | `void R_InitTextureMapping (void)` |
| `R_PointInSubsector` | function | `progs/doomgeneric/r_main.c:794` | `subsector_t* R_PointInSubsector ( fixed_t	x,   fixed_t	y )` |
| `R_PointOnSegSide` | function | `progs/doomgeneric/r_main.c:199` | `int R_PointOnSegSide ( fixed_t	x,   fixed_t	y,   seg_t*	line )` |
| `R_PointOnSide` | function | `progs/doomgeneric/r_main.c:146` | `int R_PointOnSide ( fixed_t	x,   fixed_t	y,   node_t*	node )` |
| `R_PointToAngle` | function | `progs/doomgeneric/r_main.c:276` | `angle_t R_PointToAngle ( fixed_t	x,   fixed_t	y )` |
| `R_PointToAngle2` | function | `progs/doomgeneric/r_main.c:362` | `angle_t R_PointToAngle2 ( fixed_t	x1,   fixed_t	y1,   fixed_t	x2,   fixed_t	y2 )` |
| `R_PointToDist` | function | `progs/doomgeneric/r_main.c:376` | `fixed_t R_PointToDist ( fixed_t	x,   fixed_t	y )` |
| `R_RenderPlayerView` | function | `progs/doomgeneric/r_main.c:863` | `void R_RenderPlayerView (player_t* player)` |
| `R_ScaleFromGlobalAngle` | function | `progs/doomgeneric/r_main.c:449` | `fixed_t R_ScaleFromGlobalAngle (angle_t visangle)` |
| `R_SetViewSize` | function | `progs/doomgeneric/r_main.c:654` | `void R_SetViewSize ( int		blocks,   int		detail )` |
| `R_SetupFrame` | function | `progs/doomgeneric/r_main.c:823` | `void R_SetupFrame (player_t* player)` |
| `walllights` | variable | `progs/doomgeneric/r_main.c:54` | `extern lighttable_t** walllights;` |
| `LIGHTLEVELS` | macro | `progs/doomgeneric/r_main.h:61` | `#define LIGHTLEVELS` |
| `LIGHTSCALESHIFT` | macro | `progs/doomgeneric/r_main.h:65` | `#define LIGHTSCALESHIFT` |
| `LIGHTSEGSHIFT` | macro | `progs/doomgeneric/r_main.h:62` | `#define LIGHTSEGSHIFT` |
| `LIGHTZSHIFT` | macro | `progs/doomgeneric/r_main.h:67` | `#define LIGHTZSHIFT` |
| `MAXLIGHTSCALE` | macro | `progs/doomgeneric/r_main.h:64` | `#define MAXLIGHTSCALE` |
| `MAXLIGHTZ` | macro | `progs/doomgeneric/r_main.h:66` | `#define MAXLIGHTZ` |
| `NUMCOLORMAPS` | macro | `progs/doomgeneric/r_main.h:79` | `#define NUMCOLORMAPS` |
| `R_AddPointToBox` | function | `progs/doomgeneric/r_main.h:140` | `void R_AddPointToBox ( int x, int y, fixed_t* box );` |
| `R_Init` | function | `progs/doomgeneric/r_main.h:155` | `void R_Init (void);` |
| `R_PointInSubsector` | function | `progs/doomgeneric/r_main.h:135` | `subsector_t* R_PointInSubsector ( fixed_t x, fixed_t y );` |
| `R_PointOnSegSide` | function | `progs/doomgeneric/r_main.h:109` | `int R_PointOnSegSide ( fixed_t x, fixed_t y, seg_t* line );` |
| `R_PointOnSide` | function | `progs/doomgeneric/r_main.h:103` | `int R_PointOnSide ( fixed_t x, fixed_t y, node_t* node );` |
| `R_PointToAngle` | function | `progs/doomgeneric/r_main.h:115` | `angle_t R_PointToAngle ( fixed_t x, fixed_t y );` |
| `R_PointToAngle2` | function | `progs/doomgeneric/r_main.h:120` | `angle_t R_PointToAngle2 ( fixed_t x1, fixed_t y1, fixed_t x2, fixed_t y2 );` |
| `R_PointToDist` | function | `progs/doomgeneric/r_main.h:127` | `fixed_t R_PointToDist ( fixed_t x, fixed_t y );` |
| `R_RenderPlayerView` | function | `progs/doomgeneric/r_main.h:152` | `void R_RenderPlayerView (player_t *player);` |
| `R_ScaleFromGlobalAngle` | function | `progs/doomgeneric/r_main.h:132` | `fixed_t R_ScaleFromGlobalAngle (angle_t visangle);` |
| `R_SetViewSize` | function | `progs/doomgeneric/r_main.h:158` | `void R_SetViewSize (int blocks, int detail);` |
| `__R_MAIN__` | macro | `progs/doomgeneric/r_main.h:21` | `#define __R_MAIN__` |
| `centerx` | variable | `progs/doomgeneric/r_main.h:40` | `extern int centerx;` |
| `centerxfrac` | variable | `progs/doomgeneric/r_main.h:43` | `extern fixed_t centerxfrac;` |
| `centery` | variable | `progs/doomgeneric/r_main.h:41` | `extern int centery;` |
| `centeryfrac` | variable | `progs/doomgeneric/r_main.h:44` | `extern fixed_t centeryfrac;` |
| `detailshift` | variable | `progs/doomgeneric/r_main.h:85` | `extern int detailshift;` |
| `extralight` | variable | `progs/doomgeneric/r_main.h:73` | `extern int extralight;` |
| `fixedcolormap` | variable | `progs/doomgeneric/r_main.h:74` | `extern lighttable_t* fixedcolormap;` |
| `linecount` | variable | `progs/doomgeneric/r_main.h:49` | `extern int linecount;` |
| `loopcount` | variable | `progs/doomgeneric/r_main.h:50` | `extern int loopcount;` |
| `projection` | variable | `progs/doomgeneric/r_main.h:45` | `extern fixed_t projection;` |
| `scalelightfixed` | variable | `progs/doomgeneric/r_main.h:70` | `extern lighttable_t* scalelightfixed[MAXLIGHTSCALE];` |
| `validcount` | variable | `progs/doomgeneric/r_main.h:47` | `extern int validcount;` |
| `viewcos` | variable | `progs/doomgeneric/r_main.h:32` | `extern fixed_t viewcos;` |
| `viewsin` | variable | `progs/doomgeneric/r_main.h:33` | `extern fixed_t viewsin;` |
| `viewwindowx` | variable | `progs/doomgeneric/r_main.h:35` | `extern int viewwindowx;` |
| `viewwindowy` | variable | `progs/doomgeneric/r_main.h:36` | `extern int viewwindowy;` |
| `void` | function | `progs/doomgeneric/r_main.h:92` | `extern void (*colfunc) (void);` |
| `MAXOPENINGS` | macro | `progs/doomgeneric/r_plane.c:52` | `#define MAXOPENINGS` |
| `MAXVISPLANES` | macro | `progs/doomgeneric/r_plane.c:45` | `#define MAXVISPLANES` |
| `R_CheckPlane` | function | `progs/doomgeneric/r_plane.c:259` | `visplane_t* R_CheckPlane ( visplane_t*	pl,   int		start,   int		stop )` |
| `R_ClearPlanes` | function | `progs/doomgeneric/r_plane.c:178` | `void R_ClearPlanes (void)` |
| `R_DrawPlanes` | function | `progs/doomgeneric/r_plane.c:360` | `void R_DrawPlanes (void)` |
| `R_FindPlane` | function | `progs/doomgeneric/r_plane.c:211` | `visplane_t* R_FindPlane ( fixed_t	height,   int		picnum,   int		lightlevel )` |
| `R_InitPlanes` | function | `progs/doomgeneric/r_plane.c:94` | `void R_InitPlanes (void)` |
| `R_MakeSpans` | function | `progs/doomgeneric/r_plane.c:324` | `void R_MakeSpans ( int		x,   int		t1,   int		b1,   int		t2,   int		b2 )` |
| `R_MapPlane` | function | `progs/doomgeneric/r_plane.c:114` | `void R_MapPlane ( int		y,   int		x1,   int		x2 )` |
| `R_CheckPlane` | function | `progs/doomgeneric/r_plane.h:69` | `visplane_t* R_CheckPlane ( visplane_t* pl, int start, int stop );` |
| `R_ClearPlanes` | function | `progs/doomgeneric/r_plane.h:44` | `void R_ClearPlanes (void);` |
| `R_DrawPlanes` | function | `progs/doomgeneric/r_plane.h:60` | `void R_DrawPlanes (void);` |
| `R_FindPlane` | function | `progs/doomgeneric/r_plane.h:63` | `visplane_t* R_FindPlane ( fixed_t height, int picnum, int lightlevel );` |
| `R_InitPlanes` | function | `progs/doomgeneric/r_plane.h:43` | `void R_InitPlanes (void);` |
| `R_MakeSpans` | function | `progs/doomgeneric/r_plane.h:53` | `void R_MakeSpans ( int x, int t1, int b1, int t2, int b2 );` |
| `R_MapPlane` | function | `progs/doomgeneric/r_plane.h:47` | `void R_MapPlane ( int y, int x1, int x2 );` |
| `__R_PLANE__` | macro | `progs/doomgeneric/r_plane.h:21` | `#define __R_PLANE__` |
| `ceilingclip` | variable | `progs/doomgeneric/r_plane.h:38` | `extern short ceilingclip[SCREENWIDTH];` |
| `ceilingfunc_t` | variable | `progs/doomgeneric/r_plane.h:35` | `extern planefunction_t ceilingfunc_t;` |
| `distscale` | variable | `progs/doomgeneric/r_plane.h:41` | `extern fixed_t distscale[SCREENWIDTH];` |
| `floorclip` | variable | `progs/doomgeneric/r_plane.h:37` | `extern short floorclip[SCREENWIDTH];` |
| `floorfunc` | variable | `progs/doomgeneric/r_plane.h:34` | `extern planefunction_t floorfunc;` |
| `lastopening` | variable | `progs/doomgeneric/r_plane.h:29` | `extern short* lastopening;` |
| `yslope` | variable | `progs/doomgeneric/r_plane.h:40` | `extern fixed_t yslope[SCREENHEIGHT];` |
| `HEIGHTBITS` | macro | `progs/doomgeneric/r_segs.c:196` | `#define HEIGHTBITS` |
| `HEIGHTUNIT` | macro | `progs/doomgeneric/r_segs.c:197` | `#define HEIGHTUNIT` |
| `R_RenderMaskedSegRange` | function | `progs/doomgeneric/r_segs.c:96` | `void R_RenderMaskedSegRange ( drawseg_t*	ds,   int		x1,   int		x2 )` |
| `R_RenderSegLoop` | function | `progs/doomgeneric/r_segs.c:199` | `void R_RenderSegLoop (void)` |
| `R_StoreWallRange` | function | `progs/doomgeneric/r_segs.c:372` | `void R_StoreWallRange ( int	start,   int	stop )` |
| `R_RenderMaskedSegRange` | function | `progs/doomgeneric/r_segs.h:27` | `void R_RenderMaskedSegRange ( drawseg_t* ds, int x1, int x2 );` |
| `__R_SEGS__` | macro | `progs/doomgeneric/r_segs.h:21` | `#define __R_SEGS__` |
| `R_InitSkyMap` | function | `progs/doomgeneric/r_sky.c:47` | `void R_InitSkyMap (void)` |
| `ANGLETOSKYSHIFT` | macro | `progs/doomgeneric/r_sky.h:29` | `#define ANGLETOSKYSHIFT` |
| `R_InitSkyMap` | function | `progs/doomgeneric/r_sky.h:35` | `void R_InitSkyMap (void);` |
| `SKYFLATNAME` | macro | `progs/doomgeneric/r_sky.h:26` | `#define			SKYFLATNAME` |
| `__R_SKY__` | macro | `progs/doomgeneric/r_sky.h:21` | `#define __R_SKY__` |
| `skytexture` | variable | `progs/doomgeneric/r_sky.h:31` | `extern int skytexture;` |
| `skytexturemid` | variable | `progs/doomgeneric/r_sky.h:32` | `extern int skytexturemid;` |
| `__R_STATE__` | macro | `progs/doomgeneric/r_state.h:21` | `#define __R_STATE__` |
| `ceilingplane` | variable | `progs/doomgeneric/r_state.h:124` | `extern visplane_t* ceilingplane;` |
| `clipangle` | variable | `progs/doomgeneric/r_state.h:106` | `extern angle_t clipangle;` |
| `colormaps` | variable | `progs/doomgeneric/r_state.h:46` | `extern lighttable_t* colormaps;` |
| `firstflat` | variable | `progs/doomgeneric/r_state.h:52` | `extern int firstflat;` |
| `firstspritelump` | variable | `progs/doomgeneric/r_state.h:60` | `extern int firstspritelump;` |
| `flattranslation` | variable | `progs/doomgeneric/r_state.h:55` | `extern int* flattranslation;` |
| `floorplane` | variable | `progs/doomgeneric/r_state.h:123` | `extern visplane_t* floorplane;` |
| `lastspritelump` | variable | `progs/doomgeneric/r_state.h:61` | `extern int lastspritelump;` |
| `lines` | variable | `progs/doomgeneric/r_state.h:88` | `extern line_t* lines;` |
| `nodes` | variable | `progs/doomgeneric/r_state.h:85` | `extern node_t* nodes;` |
| `numlines` | variable | `progs/doomgeneric/r_state.h:87` | `extern int numlines;` |
| `numnodes` | variable | `progs/doomgeneric/r_state.h:84` | `extern int numnodes;` |
| `numsectors` | variable | `progs/doomgeneric/r_state.h:78` | `extern int numsectors;` |
| `numsegs` | variable | `progs/doomgeneric/r_state.h:75` | `extern int numsegs;` |
| `numsides` | variable | `progs/doomgeneric/r_state.h:90` | `extern int numsides;` |
| `numspritelumps` | variable | `progs/doomgeneric/r_state.h:62` | `extern int numspritelumps;` |
| `numsprites` | variable | `progs/doomgeneric/r_state.h:69` | `extern int numsprites;` |
| `numsubsectors` | variable | `progs/doomgeneric/r_state.h:81` | `extern int numsubsectors;` |
| `numvertexes` | variable | `progs/doomgeneric/r_state.h:72` | `extern int numvertexes;` |
| `rw_angle1` | variable | `progs/doomgeneric/r_state.h:118` | `extern int rw_angle1;` |
| `rw_distance` | variable | `progs/doomgeneric/r_state.h:112` | `extern fixed_t rw_distance;` |
| `rw_normalangle` | variable | `progs/doomgeneric/r_state.h:113` | `extern angle_t rw_normalangle;` |
| `scaledviewwidth` | variable | `progs/doomgeneric/r_state.h:49` | `extern int scaledviewwidth;` |
| `sectors` | variable | `progs/doomgeneric/r_state.h:79` | `extern sector_t* sectors;` |
| `segs` | variable | `progs/doomgeneric/r_state.h:76` | `extern seg_t* segs;` |
| `sides` | variable | `progs/doomgeneric/r_state.h:91` | `extern side_t* sides;` |
| `spriteoffset` | variable | `progs/doomgeneric/r_state.h:43` | `extern fixed_t* spriteoffset;` |
| `sprites` | variable | `progs/doomgeneric/r_state.h:70` | `extern spritedef_t* sprites;` |
| `spritetopoffset` | variable | `progs/doomgeneric/r_state.h:44` | `extern fixed_t* spritetopoffset;` |
| `spritewidth` | variable | `progs/doomgeneric/r_state.h:41` | `extern fixed_t* spritewidth;` |
| `sscount` | variable | `progs/doomgeneric/r_state.h:121` | `extern int sscount;` |
| `subsectors` | variable | `progs/doomgeneric/r_state.h:82` | `extern subsector_t* subsectors;` |
| `textureheight` | variable | `progs/doomgeneric/r_state.h:38` | `extern fixed_t* textureheight;` |
| `texturetranslation` | variable | `progs/doomgeneric/r_state.h:56` | `extern int* texturetranslation;` |
| `vertexes` | variable | `progs/doomgeneric/r_state.h:73` | `extern vertex_t* vertexes;` |
| `viewangle` | variable | `progs/doomgeneric/r_state.h:101` | `extern angle_t viewangle;` |
| `viewangletox` | variable | `progs/doomgeneric/r_state.h:108` | `extern int viewangletox[FINEANGLES/2];` |
| `viewheight` | variable | `progs/doomgeneric/r_state.h:50` | `extern int viewheight;` |
| `viewplayer` | variable | `progs/doomgeneric/r_state.h:102` | `extern player_t* viewplayer;` |
| `viewwidth` | variable | `progs/doomgeneric/r_state.h:48` | `extern int viewwidth;` |
| `viewx` | variable | `progs/doomgeneric/r_state.h:97` | `extern fixed_t viewx;` |
| `viewy` | variable | `progs/doomgeneric/r_state.h:98` | `extern fixed_t viewy;` |
| `viewz` | variable | `progs/doomgeneric/r_state.h:99` | `extern fixed_t viewz;` |
| `xtoviewangle` | variable | `progs/doomgeneric/r_state.h:109` | `extern angle_t xtoviewangle[SCREENWIDTH+1];` |
| `BASEYCENTER` | macro | `progs/doomgeneric/r_things.c:41` | `#define BASEYCENTER` |
| `MINZ` | macro | `progs/doomgeneric/r_things.c:40` | `#define MINZ` |
| `R_AddSprites` | function | `progs/doomgeneric/r_things.c:605` | `void R_AddSprites (sector_t* sec)` |
| `R_ClearSprites` | function | `progs/doomgeneric/r_things.c:309` | `void R_ClearSprites (void)` |
| `R_DrawMasked` | function | `progs/doomgeneric/r_things.c:951` | `void R_DrawMasked (void)` |
| `R_DrawMaskedColumn` | function | `progs/doomgeneric/r_things.c:343` | `void R_DrawMaskedColumn (column_t* column)` |
| `R_DrawPSprite` | function | `progs/doomgeneric/r_things.c:638` | `void R_DrawPSprite (pspdef_t* psp)` |
| `R_DrawPlayerSprites` | function | `progs/doomgeneric/r_things.c:738` | `void R_DrawPlayerSprites (void)` |
| `R_DrawSprite` | function | `progs/doomgeneric/r_things.c:837` | `void R_DrawSprite (vissprite_t* spr)` |
| `R_DrawVisSprite` | function | `progs/doomgeneric/r_things.c:389` | `void R_DrawVisSprite ( vissprite_t*		vis,   int			x1,   int			x2 )` |
| `R_InitSpriteDefs` | function | `progs/doomgeneric/r_things.c:171` | `void R_InitSpriteDefs (char** namelist)` |
| `R_InitSprites` | function | `progs/doomgeneric/r_things.c:291` | `void R_InitSprites (char** namelist)` |
| `R_InstallSpriteLump` | function | `progs/doomgeneric/r_things.c:100` | `void R_InstallSpriteLump ( int		lump,   unsigned	frame,   unsigned	rotation,   boolean	flipped )` |
| `R_NewVisSprite` | function | `progs/doomgeneric/r_things.c:320` | `vissprite_t* R_NewVisSprite (void)` |
| `R_ProjectSprite` | function | `progs/doomgeneric/r_things.c:444` | `void R_ProjectSprite (mobj_t* thing)` |
| `R_SortVisSprites` | function | `progs/doomgeneric/r_things.c:779` | `void R_SortVisSprites (void)` |
| `maskdraw_t` | struct | `progs/doomgeneric/r_things.c:48` | `` |
| `MAXVISSPRITES` | macro | `progs/doomgeneric/r_things.h:25` | `#define MAXVISSPRITES` |
| `R_AddPSprites` | function | `progs/doomgeneric/r_things.h:52` | `void R_AddPSprites (void);` |
| `R_AddSprites` | function | `progs/doomgeneric/r_things.h:51` | `void R_AddSprites (sector_t* sec);` |
| `R_ClearSprites` | function | `progs/doomgeneric/r_things.h:55` | `void R_ClearSprites (void);` |
| `R_ClipVisSprite` | function | `progs/doomgeneric/r_things.h:59` | `void R_ClipVisSprite ( vissprite_t* vis, int xl, int xh );` |
| `R_DrawMasked` | function | `progs/doomgeneric/r_things.h:56` | `void R_DrawMasked (void);` |
| `R_DrawMaskedColumn` | function | `progs/doomgeneric/r_things.h:46` | `void R_DrawMaskedColumn (column_t* column);` |
| `R_DrawSprites` | function | `progs/doomgeneric/r_things.h:53` | `void R_DrawSprites (void);` |
| `R_InitSprites` | function | `progs/doomgeneric/r_things.h:54` | `void R_InitSprites (char** namelist);` |
| `R_SortVisSprites` | function | `progs/doomgeneric/r_things.h:49` | `void R_SortVisSprites (void);` |
| `__R_THINGS__` | macro | `progs/doomgeneric/r_things.h:21` | `#define __R_THINGS__` |
| `mceilingclip` | variable | `progs/doomgeneric/r_things.h:38` | `extern short* mceilingclip;` |
| `mfloorclip` | variable | `progs/doomgeneric/r_things.h:37` | `extern short* mfloorclip;` |
| `negonearray` | variable | `progs/doomgeneric/r_things.h:33` | `extern short negonearray[SCREENWIDTH];` |
| `pspriteiscale` | variable | `progs/doomgeneric/r_things.h:43` | `extern fixed_t pspriteiscale;` |
| `pspritescale` | variable | `progs/doomgeneric/r_things.h:42` | `extern fixed_t pspritescale;` |
| `screenheightarray` | variable | `progs/doomgeneric/r_things.h:34` | `extern short screenheightarray[SCREENWIDTH];` |
| `sprtopscreen` | variable | `progs/doomgeneric/r_things.h:40` | `extern fixed_t sprtopscreen;` |
| `spryscale` | variable | `progs/doomgeneric/r_things.h:39` | `extern fixed_t spryscale;` |
| `vissprite_p` | variable | `progs/doomgeneric/r_things.h:28` | `extern vissprite_t* vissprite_p;` |
| `vissprites` | variable | `progs/doomgeneric/r_things.h:27` | `extern vissprite_t vissprites[MAXVISSPRITES];` |
| `vsprsortedhead` | variable | `progs/doomgeneric/r_things.h:29` | `extern vissprite_t vsprsortedhead;` |
| `NORM_PITCH` | macro | `progs/doomgeneric/s_sound.c:62` | `#define NORM_PITCH` |
| `NORM_PRIORITY` | macro | `progs/doomgeneric/s_sound.c:63` | `#define NORM_PRIORITY` |
| `NORM_SEP` | macro | `progs/doomgeneric/s_sound.c:64` | `#define NORM_SEP` |
| `S_ATTENUATOR` | macro | `progs/doomgeneric/s_sound.c:56` | `#define S_ATTENUATOR` |
| `S_AdjustSoundParams` | function | `progs/doomgeneric/s_sound.c:323` | `static int S_AdjustSoundParams(mobj_t *listener, mobj_t *source,                                i...` |
| `S_CLIPPING_DIST` | macro | `progs/doomgeneric/s_sound.c:44` | `#define S_CLIPPING_DIST` |
| `S_CLOSE_DIST` | macro | `progs/doomgeneric/s_sound.c:52` | `#define S_CLOSE_DIST` |
| `S_ChangeMusic` | function | `progs/doomgeneric/s_sound.c:601` | `void S_ChangeMusic(int musicnum, int looping)` |
| `S_GetChannel` | function | `progs/doomgeneric/s_sound.c:262` | `static int S_GetChannel(mobj_t *origin, sfxinfo_t *sfxinfo)` |
| `S_Init` | function | `progs/doomgeneric/s_sound.c:114` | `void S_Init(int sfxVolume, int musicVolume)` |
| `S_MusicPlaying` | function | `progs/doomgeneric/s_sound.c:649` | `boolean S_MusicPlaying(void)` |
| `S_PauseSound` | function | `progs/doomgeneric/s_sound.c:482` | `void S_PauseSound(void)` |
| `S_ResumeSound` | function | `progs/doomgeneric/s_sound.c:491` | `void S_ResumeSound(void)` |
| `S_STEREO_SWING` | macro | `progs/doomgeneric/s_sound.c:60` | `#define S_STEREO_SWING` |
| `S_SetMusicVolume` | function | `progs/doomgeneric/s_sound.c:571` | `void S_SetMusicVolume(int volume)` |
| `S_SetSfxVolume` | function | `progs/doomgeneric/s_sound.c:582` | `void S_SetSfxVolume(int volume)` |
| `S_Shutdown` | function | `progs/doomgeneric/s_sound.c:146` | `void S_Shutdown(void)` |
| `S_Start` | function | `progs/doomgeneric/s_sound.c:191` | `void S_Start(void)` |
| `S_StartMusic` | function | `progs/doomgeneric/s_sound.c:596` | `void S_StartMusic(int m_id)` |
| `S_StartSound` | function | `progs/doomgeneric/s_sound.c:391` | `void S_StartSound(void *origin_p, int sfx_id)` |
| `S_StopChannel` | function | `progs/doomgeneric/s_sound.c:152` | `static void S_StopChannel(int cnum)` |
| `S_StopMusic` | function | `progs/doomgeneric/s_sound.c:654` | `void S_StopMusic(void)` |
| `S_StopSound` | function | `progs/doomgeneric/s_sound.c:243` | `void S_StopSound(mobj_t *origin)` |
| `S_UpdateSounds` | function | `progs/doomgeneric/s_sound.c:504` | `void S_UpdateSounds(mobj_t *listener)` |
| `channel_t` | struct | `progs/doomgeneric/s_sound.c:66` | `` |
| `S_ChangeMusic` | function | `progs/doomgeneric/s_sound.h:65` | `void S_ChangeMusic(int music_id, int looping);` |
| `S_Init` | function | `progs/doomgeneric/s_sound.h:32` | `void S_Init(int sfxVolume, int musicVolume);` |
| `S_PauseSound` | function | `progs/doomgeneric/s_sound.h:74` | `void S_PauseSound(void);` |
| `S_ResumeSound` | function | `progs/doomgeneric/s_sound.h:75` | `void S_ResumeSound(void);` |
| `S_SetMusicVolume` | function | `progs/doomgeneric/s_sound.h:83` | `void S_SetMusicVolume(int volume);` |
| `S_SetSfxVolume` | function | `progs/doomgeneric/s_sound.h:84` | `void S_SetSfxVolume(int volume);` |
| `S_Shutdown` | function | `progs/doomgeneric/s_sound.h:37` | `void S_Shutdown(void);` |
| `S_Start` | function | `progs/doomgeneric/s_sound.h:47` | `void S_Start(void);` |
| `S_StartMusic` | function | `progs/doomgeneric/s_sound.h:61` | `void S_StartMusic(int music_id);` |
| `S_StartSound` | function | `progs/doomgeneric/s_sound.h:54` | `void S_StartSound(void *origin, int sound_id);` |
| `S_StopMusic` | function | `progs/doomgeneric/s_sound.h:71` | `void S_StopMusic(void);` |
| `S_StopSound` | function | `progs/doomgeneric/s_sound.h:57` | `void S_StopSound(mobj_t *origin);` |
| `S_UpdateSounds` | function | `progs/doomgeneric/s_sound.h:81` | `void S_UpdateSounds(mobj_t *listener);` |
| `__S_SOUND__` | macro | `progs/doomgeneric/s_sound.h:21` | `#define __S_SOUND__` |
| `snd_channels` | variable | `progs/doomgeneric/s_sound.h:86` | `extern int snd_channels;` |
| `F1` | macro | `progs/doomgeneric/sha1.c:88` | `#define F1(x,y,z)` |
| `F2` | macro | `progs/doomgeneric/sha1.c:89` | `#define F2(x,y,z)` |
| `F3` | macro | `progs/doomgeneric/sha1.c:90` | `#define F3(x,y,z)` |
| `F4` | macro | `progs/doomgeneric/sha1.c:91` | `#define F4(x,y,z)` |

Next: [SYMBOLS_p17.md](SYMBOLS_p17.md)
