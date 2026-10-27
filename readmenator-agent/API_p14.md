# API (page 14 of 21)
Previous: [API_p13.md](API_p13.md)

## progs/doomgeneric/p_map.c
Depends on: `progs/doomgeneric/deh_misc.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_bbox.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`
- `PIT_StompThing` (function) `progs/doomgeneric/p_map.c:97` `boolean PIT_StompThing (mobj_t* thing)` -- PIT_StompThing
- `P_TeleportMove` (function) `progs/doomgeneric/p_map.c:131` `boolean
P_TeleportMove
( mobj_t*	thing,
  fixed_t	x,
  fixed_t	y )`
- `PIT_CheckLine` (function) `progs/doomgeneric/p_map.c:206` `boolean PIT_CheckLine (line_t* ld)` -- PIT_CheckLine Adjusts tmfloorz and tmceilingz as lines are contacted
- `PIT_CheckThing` (function) `progs/doomgeneric/p_map.c:275` `boolean PIT_CheckThing (mobj_t* thing)` -- PIT_CheckThing
- `P_CheckPosition` (function) `progs/doomgeneric/p_map.c:402` `boolean
P_CheckPosition
( mobj_t*	thing,
  fixed_t	x,
  fixed_t	y )`
- `P_TryMove` (function) `progs/doomgeneric/p_map.c:478` `boolean
P_TryMove
( mobj_t*	thing,
  fixed_t	x,
  fixed_t	y )`
- `P_ThingHeightClip` (function) `progs/doomgeneric/p_map.c:557` `boolean P_ThingHeightClip (mobj_t* thing)` -- P_ThingHeightClip Takes a valid thing and adjusts the thing->floorz, thing->ceilingz, and possibly thing->z.
- `P_HitSlideLine` (function) `progs/doomgeneric/p_map.c:611` `void P_HitSlideLine (line_t* ld)` -- P_HitSlideLine Adjusts the xmove / ymove so that the next move will slide along the wall.
- `PTR_SlideTraverse` (function) `progs/doomgeneric/p_map.c:663` `boolean PTR_SlideTraverse (intercept_t* in)` -- PTR_SlideTraverse
- `P_SlideMove` (function) `progs/doomgeneric/p_map.c:722` `void P_SlideMove (mobj_t* mo)` -- P_SlideMove The momx / momy move is bad, so try to slide along a wall.
- `PTR_AimTraverse` (function) `progs/doomgeneric/p_map.c:843` `boolean
PTR_AimTraverse (intercept_t* in)`
- `PTR_ShootTraverse` (function) `progs/doomgeneric/p_map.c:928` `boolean PTR_ShootTraverse (intercept_t* in)` -- PTR_ShootTraverse
- `P_AimLineAttack` (function) `progs/doomgeneric/p_map.c:1068` `fixed_t
P_AimLineAttack
( mobj_t*	t1,
  angle_t	angle,
  fixed_t	distance )`
- `P_LineAttack` (function) `progs/doomgeneric/p_map.c:1110` `void
P_LineAttack
( mobj_t*	t1,
  angle_t	angle,
  fixed_t	distance,
  fixed_t	slope,
  int		dama...`
- `PTR_UseTraverse` (function) `progs/doomgeneric/p_map.c:1142` `boolean	PTR_UseTraverse (intercept_t* in)`
- `P_UseLines` (function) `progs/doomgeneric/p_map.c:1177` `void P_UseLines (player_t*	player)` -- P_UseLines Looks for special lines in front of the player to activate.
- `PIT_RadiusAttack` (function) `progs/doomgeneric/p_map.c:1211` `boolean PIT_RadiusAttack (mobj_t* thing)` -- PIT_RadiusAttack "bombsource" is the creature that caused the explosion at "bombspot".
- `P_RadiusAttack` (function) `progs/doomgeneric/p_map.c:1253` `void
P_RadiusAttack
( mobj_t*	spot,
  mobj_t*	source,
  int		damage )`
- `PIT_ChangeSector` (function) `progs/doomgeneric/p_map.c:1304` `boolean PIT_ChangeSector (mobj_t*	thing)` -- PIT_ChangeSector
- `P_ChangeSector` (function) `progs/doomgeneric/p_map.c:1368` `boolean
P_ChangeSector
( sector_t*	sector,
  boolean	crunch )`
- `SpechitOverrun` (function) `progs/doomgeneric/p_map.c:1391` `static void SpechitOverrun(line_t *ld)`

## progs/doomgeneric/p_maputl.c
Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/m_bbox.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_state.h`
- `P_AproxDistance` (function) `progs/doomgeneric/p_maputl.c:44` `fixed_t
P_AproxDistance
( fixed_t	dx,
  fixed_t	dy )`
- `P_PointOnLineSide` (function) `progs/doomgeneric/p_maputl.c:61` `int
P_PointOnLineSide
( fixed_t	x,
  fixed_t	y,
  line_t*	line )`
- `P_BoxOnLineSide` (function) `progs/doomgeneric/p_maputl.c:105` `int
P_BoxOnLineSide
( fixed_t*	tmbox,
  line_t*	ld )`
- `P_PointOnDivlineSide` (function) `progs/doomgeneric/p_maputl.c:156` `int
P_PointOnDivlineSide
( fixed_t	x,
  fixed_t	y,
  divline_t*	line )`
- `P_MakeDivline` (function) `progs/doomgeneric/p_maputl.c:206` `void
P_MakeDivline
( line_t*	li,
  divline_t*	dl )`
- `P_InterceptVector` (function) `progs/doomgeneric/p_maputl.c:226` `fixed_t
P_InterceptVector
( divline_t*	v2,
  divline_t*	v1 )`
- `P_LineOpening` (function) `progs/doomgeneric/p_maputl.c:295` `void P_LineOpening (line_t* linedef)`
- `P_UnsetThingPosition` (function) `progs/doomgeneric/p_maputl.c:342` `void P_UnsetThingPosition (mobj_t* thing)` -- P_UnsetThingPosition Unlinks a thing from block map and sectors.
- `P_SetThingPosition` (function) `progs/doomgeneric/p_maputl.c:391` `void
P_SetThingPosition (mobj_t* thing)`
- `P_BlockLinesIterator` (function) `progs/doomgeneric/p_maputl.c:467` `boolean
P_BlockLinesIterator
( int			x,
  int			y,
  boolean(*func)(line_t*) )`
- `P_BlockThingsIterator` (function) `progs/doomgeneric/p_maputl.c:508` `boolean
P_BlockThingsIterator
( int			x,
  int			y,
  boolean(*func)(mobj_t*) )`
- `PIT_AddLineIntercepts` (function) `progs/doomgeneric/p_maputl.c:559` `boolean
PIT_AddLineIntercepts (line_t* ld)`
- `PIT_AddThingIntercepts` (function) `progs/doomgeneric/p_maputl.c:614` `boolean PIT_AddThingIntercepts (mobj_t* thing)` -- PIT_AddThingIntercepts
- `P_TraverseIntercepts` (function) `progs/doomgeneric/p_maputl.c:682` `boolean
P_TraverseIntercepts
( traverser_t	func,
  fixed_t	maxfrac )`
- `InterceptsMemoryOverrun` (function) `progs/doomgeneric/p_maputl.c:782` `static void InterceptsMemoryOverrun(int location, int value)`
- `InterceptsOverrun` (function) `progs/doomgeneric/p_maputl.c:827` `static void InterceptsOverrun(int num_intercepts, intercept_t *intercept)`
- `P_PathTraverse` (function) `progs/doomgeneric/p_maputl.c:861` `boolean
P_PathTraverse
( fixed_t		x1,
  fixed_t		y1,
  fixed_t		x2,
  fixed_t		y2,
  int			flags,...`

## progs/doomgeneric/p_mobj.c
Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/hu_stuff.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/st_stuff.h`, `progs/doomgeneric/z_zone.h`
- `G_PlayerReborn` (function) `progs/doomgeneric/p_mobj.c:37` `void G_PlayerReborn (int player);`
- `P_SetMobjState` (function) `progs/doomgeneric/p_mobj.c:48` `boolean
P_SetMobjState
( mobj_t*	mobj,
  statenum_t	state )`
- `P_ExplodeMissile` (function) `progs/doomgeneric/p_mobj.c:84` `void P_ExplodeMissile (mobj_t* mo)` -- P_ExplodeMissile
- `P_XYMovement` (function) `progs/doomgeneric/p_mobj.c:108` `void P_XYMovement (mobj_t* mo)`
- `P_ZMovement` (function) `progs/doomgeneric/p_mobj.c:240` `void P_ZMovement (mobj_t* mo)` -- P_ZMovement
- `P_NightmareRespawn` (function) `progs/doomgeneric/p_mobj.c:383` `void
P_NightmareRespawn (mobj_t* mobj)`
- `P_MobjThinker` (function) `progs/doomgeneric/p_mobj.c:441` `void P_MobjThinker (mobj_t* mobj)` -- P_MobjThinker
- `P_SpawnMobj` (function) `progs/doomgeneric/p_mobj.c:506` `mobj_t*
P_SpawnMobj
( fixed_t	x,
  fixed_t	y,
  fixed_t	z,
  mobjtype_t	type )`
- `P_RemoveMobj` (function) `progs/doomgeneric/p_mobj.c:572` `void P_RemoveMobj (mobj_t* mobj)`
- `P_RespawnSpecials` (function) `progs/doomgeneric/p_mobj.c:604` `void P_RespawnSpecials (void)` -- P_RespawnSpecials
- `P_SpawnPlayer` (function) `progs/doomgeneric/p_mobj.c:668` `void P_SpawnPlayer (mapthing_t* mthing)` -- P_SpawnPlayer Called when a player is spawned on the level.
- `P_SpawnMapThing` (function) `progs/doomgeneric/p_mobj.c:739` `void P_SpawnMapThing (mapthing_t* mthing)` -- P_SpawnMapThing The fields of the mapthing should already be in host byte order.
- `P_SpawnPuff` (function) `progs/doomgeneric/p_mobj.c:851` `void
P_SpawnPuff
( fixed_t	x,
  fixed_t	y,
  fixed_t	z )`
- `P_SpawnBlood` (function) `progs/doomgeneric/p_mobj.c:878` `void
P_SpawnBlood
( fixed_t	x,
  fixed_t	y,
  fixed_t	z,
  int		damage )`
- `P_CheckMissileSpawn` (function) `progs/doomgeneric/p_mobj.c:907` `void P_CheckMissileSpawn (mobj_t* th)` -- P_CheckMissileSpawn Moves the missile forward a bit and possibly explodes it right there.
- `P_SubstNullMobj` (function) `progs/doomgeneric/p_mobj.c:929` `mobj_t *P_SubstNullMobj(mobj_t *mobj)`
- `P_SpawnMissile` (function) `progs/doomgeneric/p_mobj.c:950` `mobj_t*
P_SpawnMissile
( mobj_t*	source,
  mobj_t*	dest,
  mobjtype_t	type )`
- `P_SpawnPlayerMissile` (function) `progs/doomgeneric/p_mobj.c:996` `void
P_SpawnPlayerMissile
( mobj_t*	source,
  mobjtype_t	type )`

## progs/doomgeneric/p_plats.c
Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/z_zone.h`
- `T_PlatRaise` (function) `progs/doomgeneric/p_plats.c:45` `void T_PlatRaise(plat_t* plat)` -- Move a plat up and down
- `EV_DoPlat` (function) `progs/doomgeneric/p_plats.c:129` `int
EV_DoPlat
( line_t*	line,
  plattype_e	type,
  int		amount )`
- `P_ActivateInStasis` (function) `progs/doomgeneric/p_plats.c:248` `void P_ActivateInStasis(int tag)`
- `EV_StopPlat` (function) `progs/doomgeneric/p_plats.c:263` `void EV_StopPlat(line_t* line)`
- `P_AddActivePlat` (function) `progs/doomgeneric/p_plats.c:278` `void P_AddActivePlat(plat_t* plat)`
- `P_RemoveActivePlat` (function) `progs/doomgeneric/p_plats.c:291` `void P_RemoveActivePlat(plat_t* plat)`

## progs/doomgeneric/p_pspr.c
Depends on: `progs/doomgeneric/d_event.h`, `progs/doomgeneric/deh_misc.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/p_pspr.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`
- `P_SetPsprite` (function) `progs/doomgeneric/p_pspr.c:50` `void
P_SetPsprite
( player_t*	player,
  int		position,
  statenum_t	stnum )`
- `P_CalcSwing` (function) `progs/doomgeneric/p_pspr.c:103` `void P_CalcSwing (player_t*	player)`
- `P_BringUpWeapon` (function) `progs/doomgeneric/p_pspr.c:129` `void P_BringUpWeapon (player_t* player)` -- P_BringUpWeapon Starts bringing the pending weapon up from the bottom of the screen.
- `P_CheckAmmo` (function) `progs/doomgeneric/p_pspr.c:152` `boolean P_CheckAmmo (player_t* player)` -- P_CheckAmmo Returns true if there is enough ammo to shoot.
- `P_FireWeapon` (function) `progs/doomgeneric/p_pspr.c:237` `void P_FireWeapon (player_t* player)` -- P_FireWeapon.
- `P_DropWeapon` (function) `progs/doomgeneric/p_pspr.c:256` `void P_DropWeapon (player_t* player)` -- P_DropWeapon Player died, so put the weapon away.
- `A_WeaponReady` (function) `progs/doomgeneric/p_pspr.c:273` `void
A_WeaponReady
( player_t*	player,
  pspdef_t*	psp )`
- `A_ReFire` (function) `progs/doomgeneric/p_pspr.c:334` `void A_ReFire
( player_t*	player,
  pspdef_t*	psp )` -- A_ReFire The player can re-fire the weapon without lowering it entirely.
- `A_CheckReload` (function) `progs/doomgeneric/p_pspr.c:357` `void
A_CheckReload
( player_t*	player,
  pspdef_t*	psp )`
- `A_Lower` (function) `progs/doomgeneric/p_pspr.c:376` `void
A_Lower
( player_t*	player,
  pspdef_t*	psp )`
- `A_Raise` (function) `progs/doomgeneric/p_pspr.c:414` `void
A_Raise
( player_t*	player,
  pspdef_t*	psp )`
- `A_GunFlash` (function) `progs/doomgeneric/p_pspr.c:440` `void
A_GunFlash
( player_t*	player,
  pspdef_t*	psp )`
- `A_Punch` (function) `progs/doomgeneric/p_pspr.c:459` `void
A_Punch
( player_t*	player,
  pspdef_t*	psp )`
- `A_Saw` (function) `progs/doomgeneric/p_pspr.c:493` `void
A_Saw
( player_t*	player,
  pspdef_t*	psp )`
- `DecreaseAmmo` (function) `progs/doomgeneric/p_pspr.c:542` `static void DecreaseAmmo(player_t *player, int ammonum, int amount)`
- `A_FireMissile` (function) `progs/doomgeneric/p_pspr.c:559` `void
A_FireMissile
( player_t*	player,
  pspdef_t*	psp )`
- `A_FireBFG` (function) `progs/doomgeneric/p_pspr.c:572` `void
A_FireBFG
( player_t*	player,
  pspdef_t*	psp )`
- `A_FirePlasma` (function) `progs/doomgeneric/p_pspr.c:587` `void
A_FirePlasma
( player_t*	player,
  pspdef_t*	psp )`
- `P_BulletSlope` (function) `progs/doomgeneric/p_pspr.c:610` `void P_BulletSlope (mobj_t*	mo)`
- `P_GunShot` (function) `progs/doomgeneric/p_pspr.c:635` `void
P_GunShot
( mobj_t*	mo,
  boolean	accurate )`
- `A_FirePistol` (function) `progs/doomgeneric/p_pspr.c:656` `void
A_FirePistol
( player_t*	player,
  pspdef_t*	psp )`
- `A_FireShotgun` (function) `progs/doomgeneric/p_pspr.c:678` `void
A_FireShotgun
( player_t*	player,
  pspdef_t*	psp )`
- `A_FireShotgun2` (function) `progs/doomgeneric/p_pspr.c:705` `void
A_FireShotgun2
( player_t*	player,
  pspdef_t*	psp )`
- `A_FireCGun` (function) `progs/doomgeneric/p_pspr.c:742` `void
A_FireCGun
( player_t*	player,
  pspdef_t*	psp )`
- `A_Light0` (function) `progs/doomgeneric/p_pspr.c:770` `void A_Light0 (player_t *player, pspdef_t *psp)`
- `A_Light1` (function) `progs/doomgeneric/p_pspr.c:775` `void A_Light1 (player_t *player, pspdef_t *psp)`
- `A_Light2` (function) `progs/doomgeneric/p_pspr.c:780` `void A_Light2 (player_t *player, pspdef_t *psp)`
- `A_BFGSpray` (function) `progs/doomgeneric/p_pspr.c:790` `void A_BFGSpray (mobj_t* mo)` -- A_BFGSpray Spawn a BFG explosion on every monster in view
- `A_BFGsound` (function) `progs/doomgeneric/p_pspr.c:827` `void
A_BFGsound
( player_t*	player,
  pspdef_t*	psp )`
- `P_SetupPsprites` (function) `progs/doomgeneric/p_pspr.c:840` `void P_SetupPsprites (player_t* player)` -- P_SetupPsprites Called at start of level for each player.
- `P_MovePsprites` (function) `progs/doomgeneric/p_pspr.c:860` `void P_MovePsprites (player_t* player)` -- P_MovePsprites Called every tic by player thinking routine.

## progs/doomgeneric/p_saveg.c
Depends on: `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/dstrings.h`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/p_saveg.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/z_zone.h`
- `P_TempSaveGameFile` (function) `progs/doomgeneric/p_saveg.c:47` `char *P_TempSaveGameFile(void)`
- `P_SaveGameFile` (function) `progs/doomgeneric/p_saveg.c:61` `char *P_SaveGameFile(int slot)`
- `saveg_read8` (function) `progs/doomgeneric/p_saveg.c:81` `static byte saveg_read8(void)`
- `saveg_write8` (function) `progs/doomgeneric/p_saveg.c:99` `static void saveg_write8(byte value)`
- `saveg_read16` (function) `progs/doomgeneric/p_saveg.c:112` `static short saveg_read16(void)`
- `saveg_write16` (function) `progs/doomgeneric/p_saveg.c:122` `static void saveg_write16(short value)`
- `saveg_read32` (function) `progs/doomgeneric/p_saveg.c:128` `static int saveg_read32(void)`
- `saveg_write32` (function) `progs/doomgeneric/p_saveg.c:140` `static void saveg_write32(int value)`
- `saveg_read_pad` (function) `progs/doomgeneric/p_saveg.c:150` `static void saveg_read_pad(void)`
- `saveg_write_pad` (function) `progs/doomgeneric/p_saveg.c:166` `static void saveg_write_pad(void)`
- `saveg_readp` (function) `progs/doomgeneric/p_saveg.c:185` `static void *saveg_readp(void)`
- `saveg_writep` (function) `progs/doomgeneric/p_saveg.c:190` `static void saveg_writep(void *p)`
- `saveg_read_mapthing_t` (function) `progs/doomgeneric/p_saveg.c:208` `static void saveg_read_mapthing_t(mapthing_t *str)`
- `saveg_write_mapthing_t` (function) `progs/doomgeneric/p_saveg.c:226` `static void saveg_write_mapthing_t(mapthing_t *str)`
- `saveg_read_actionf_t` (function) `progs/doomgeneric/p_saveg.c:248` `static void saveg_read_actionf_t(actionf_t *str)`
- `saveg_write_actionf_t` (function) `progs/doomgeneric/p_saveg.c:254` `static void saveg_write_actionf_t(actionf_t *str)`
- `saveg_read_thinker_t` (function) `progs/doomgeneric/p_saveg.c:273` `static void saveg_read_thinker_t(thinker_t *str)`
- `saveg_write_thinker_t` (function) `progs/doomgeneric/p_saveg.c:285` `static void saveg_write_thinker_t(thinker_t *str)`
- `saveg_read_mobj_t` (function) `progs/doomgeneric/p_saveg.c:301` `static void saveg_read_mobj_t(mobj_t *str)`
- `saveg_write_mobj_t` (function) `progs/doomgeneric/p_saveg.c:421` `static void saveg_write_mobj_t(mobj_t *str)`
- `saveg_read_ticcmd_t` (function) `progs/doomgeneric/p_saveg.c:541` `static void saveg_read_ticcmd_t(ticcmd_t *str)`
- `saveg_write_ticcmd_t` (function) `progs/doomgeneric/p_saveg.c:563` `static void saveg_write_ticcmd_t(ticcmd_t *str)`
- `saveg_read_pspdef_t` (function) `progs/doomgeneric/p_saveg.c:589` `static void saveg_read_pspdef_t(pspdef_t *str)`
- `saveg_write_pspdef_t` (function) `progs/doomgeneric/p_saveg.c:615` `static void saveg_write_pspdef_t(pspdef_t *str)`
- `saveg_read_player_t` (function) `progs/doomgeneric/p_saveg.c:641` `static void saveg_read_player_t(player_t *str)`
- `saveg_write_player_t` (function) `progs/doomgeneric/p_saveg.c:772` `static void saveg_write_player_t(player_t *str)`
- `saveg_read_ceiling_t` (function) `progs/doomgeneric/p_saveg.c:908` `static void saveg_read_ceiling_t(ceiling_t *str)`
- `saveg_write_ceiling_t` (function) `progs/doomgeneric/p_saveg.c:944` `static void saveg_write_ceiling_t(ceiling_t *str)`
- `saveg_read_vldoor_t` (function) `progs/doomgeneric/p_saveg.c:981` `static void saveg_read_vldoor_t(vldoor_t *str)`
- `saveg_write_vldoor_t` (function) `progs/doomgeneric/p_saveg.c:1011` `static void saveg_write_vldoor_t(vldoor_t *str)`
- `saveg_read_floormove_t` (function) `progs/doomgeneric/p_saveg.c:1042` `static void saveg_read_floormove_t(floormove_t *str)`
- `saveg_write_floormove_t` (function) `progs/doomgeneric/p_saveg.c:1075` `static void saveg_write_floormove_t(floormove_t *str)`
- `saveg_read_plat_t` (function) `progs/doomgeneric/p_saveg.c:1109` `static void saveg_read_plat_t(plat_t *str)`
- `saveg_write_plat_t` (function) `progs/doomgeneric/p_saveg.c:1151` `static void saveg_write_plat_t(plat_t *str)`
- `saveg_read_lightflash_t` (function) `progs/doomgeneric/p_saveg.c:1194` `static void saveg_read_lightflash_t(lightflash_t *str)`
- `saveg_write_lightflash_t` (function) `progs/doomgeneric/p_saveg.c:1221` `static void saveg_write_lightflash_t(lightflash_t *str)`
- `saveg_read_strobe_t` (function) `progs/doomgeneric/p_saveg.c:1249` `static void saveg_read_strobe_t(strobe_t *str)`
- `saveg_write_strobe_t` (function) `progs/doomgeneric/p_saveg.c:1276` `static void saveg_write_strobe_t(strobe_t *str)`
- `saveg_read_glow_t` (function) `progs/doomgeneric/p_saveg.c:1304` `static void saveg_read_glow_t(glow_t *str)`
- `saveg_write_glow_t` (function) `progs/doomgeneric/p_saveg.c:1325` `static void saveg_write_glow_t(glow_t *str)`
- `P_WriteSaveGameHeader` (function) `progs/doomgeneric/p_saveg.c:1347` `void P_WriteSaveGameHeader(char *description)`
- `P_ReadSaveGameHeader` (function) `progs/doomgeneric/p_saveg.c:1379` `boolean P_ReadSaveGameHeader(void)`
- `P_ReadSaveGameEOF` (function) `progs/doomgeneric/p_saveg.c:1419` `boolean P_ReadSaveGameEOF(void)`
- `P_WriteSaveGameEOF` (function) `progs/doomgeneric/p_saveg.c:1432` `void P_WriteSaveGameEOF(void)`
- `P_ArchivePlayers` (function) `progs/doomgeneric/p_saveg.c:1440` `void P_ArchivePlayers (void)` -- P_ArchivePlayers
- `P_UnArchivePlayers` (function) `progs/doomgeneric/p_saveg.c:1460` `void P_UnArchivePlayers (void)` -- P_UnArchivePlayers
- `P_ArchiveWorld` (function) `progs/doomgeneric/p_saveg.c:1484` `void P_ArchiveWorld (void)` -- P_ArchiveWorld
- `P_UnArchiveWorld` (function) `progs/doomgeneric/p_saveg.c:1532` `void P_UnArchiveWorld (void)` -- P_UnArchiveWorld
- `P_ArchiveThinkers` (function) `progs/doomgeneric/p_saveg.c:1592` `void P_ArchiveThinkers (void)` -- P_ArchiveThinkers
- `P_UnArchiveThinkers` (function) `progs/doomgeneric/p_saveg.c:1620` `void P_UnArchiveThinkers (void)` -- P_UnArchiveThinkers
- `P_ArchiveSpecials` (function) `progs/doomgeneric/p_saveg.c:1704` `void P_ArchiveSpecials (void)` -- Things to handle:  T_MoveCeiling, (ceiling_t: sector_t * swizzle), - active list T_VerticalDoor, (vldoor_t: sector_t...
- `P_UnArchiveSpecials` (function) `progs/doomgeneric/p_saveg.c:1793` `void P_UnArchiveSpecials (void)` -- P_UnArchiveSpecials

## progs/doomgeneric/p_saveg.h
Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/p_saveg.c`
- `P_TempSaveGameFile` (function) `progs/doomgeneric/p_saveg.h:31` `char *P_TempSaveGameFile(void);`
- `P_SaveGameFile` (function) `progs/doomgeneric/p_saveg.h:35` `char *P_SaveGameFile(int slot);`
- `P_WriteSaveGameHeader` (function) `progs/doomgeneric/p_saveg.h:40` `void P_WriteSaveGameHeader(char *description);`
- `P_WriteSaveGameEOF` (function) `progs/doomgeneric/p_saveg.h:45` `void P_WriteSaveGameEOF(void);`
- `P_ArchivePlayers` (function) `progs/doomgeneric/p_saveg.h:49` `void P_ArchivePlayers (void);` -- Persistent storage/archiving.
- `P_UnArchivePlayers` (function) `progs/doomgeneric/p_saveg.h:50` `void P_UnArchivePlayers (void);`
- `P_ArchiveWorld` (function) `progs/doomgeneric/p_saveg.h:51` `void P_ArchiveWorld (void);`
- `P_UnArchiveWorld` (function) `progs/doomgeneric/p_saveg.h:52` `void P_UnArchiveWorld (void);`
- `P_ArchiveThinkers` (function) `progs/doomgeneric/p_saveg.h:53` `void P_ArchiveThinkers (void);`
- `P_UnArchiveThinkers` (function) `progs/doomgeneric/p_saveg.h:54` `void P_UnArchiveThinkers (void);`
- `P_ArchiveSpecials` (function) `progs/doomgeneric/p_saveg.h:55` `void P_ArchiveSpecials (void);`
- `P_UnArchiveSpecials` (function) `progs/doomgeneric/p_saveg.h:56` `void P_UnArchiveSpecials (void);`

## progs/doomgeneric/p_setup.c
Depends on: `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_bbox.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`
- `P_SpawnMapThing` (function) `progs/doomgeneric/p_setup.c:44` `void P_SpawnMapThing (mapthing_t* mthing);`
- `P_LoadVertexes` (function) `progs/doomgeneric/p_setup.c:118` `void P_LoadVertexes (int lump)` -- P_LoadVertexes
- `GetSectorAtNullAddress` (function) `progs/doomgeneric/p_setup.c:153` `sector_t* GetSectorAtNullAddress(void)` -- GetSectorAtNullAddress
- `P_LoadSegs` (function) `progs/doomgeneric/p_setup.c:172` `void P_LoadSegs (int lump)` -- P_LoadSegs
- `P_LoadSubsectors` (function) `progs/doomgeneric/p_setup.c:236` `void P_LoadSubsectors (int lump)` -- P_LoadSubsectors
- `P_LoadSectors` (function) `progs/doomgeneric/p_setup.c:265` `void P_LoadSectors (int lump)` -- P_LoadSectors
- `P_LoadNodes` (function) `progs/doomgeneric/p_setup.c:298` `void P_LoadNodes (int lump)` -- P_LoadNodes
- `P_LoadThings` (function) `progs/doomgeneric/p_setup.c:335` `void P_LoadThings (int lump)` -- P_LoadThings
- `P_LoadLineDefs` (function) `progs/doomgeneric/p_setup.c:392` `void P_LoadLineDefs (int lump)` -- P_LoadLineDefs Also counts secret lines for intermissions.
- `P_LoadSideDefs` (function) `progs/doomgeneric/p_setup.c:473` `void P_LoadSideDefs (int lump)` -- P_LoadSideDefs
- `P_LoadBlockMap` (function) `progs/doomgeneric/p_setup.c:504` `void P_LoadBlockMap (int lump)` -- P_LoadBlockMap
- `P_GroupLines` (function) `progs/doomgeneric/p_setup.c:545` `void P_GroupLines (void)` -- P_GroupLines Builds sector line lists and subsector sector numbers.
- `PadRejectArray` (function) `progs/doomgeneric/p_setup.c:661` `static void PadRejectArray(byte *array, unsigned int len)`
- `P_LoadReject` (function) `progs/doomgeneric/p_setup.c:712` `static void P_LoadReject(int lumpnum)`
- `P_SetupLevel` (function) `progs/doomgeneric/p_setup.c:744` `void
P_SetupLevel
( int		episode,
  int		map,
  int		playermask,
  skill_t	skill)`
- `P_Init` (function) `progs/doomgeneric/p_setup.c:847` `void P_Init (void)` -- P_Init

## progs/doomgeneric/p_setup.h
Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/g_game.c`
- `P_SetupLevel` (function) `progs/doomgeneric/p_setup.h:28` `void P_SetupLevel ( int episode, int map, int playermask, skill_t skill);`
- `P_Init` (function) `progs/doomgeneric/p_setup.h:35` `void P_Init (void);` -- Called by startup code.

## progs/doomgeneric/p_sight.c
Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_state.h`
- `P_DivlineSide` (function) `progs/doomgeneric/p_sight.c:48` `int
P_DivlineSide
( fixed_t	x,
  fixed_t	y,
  divline_t*	node )`
- `P_InterceptVector2` (function) `progs/doomgeneric/p_sight.c:102` `fixed_t
P_InterceptVector2
( divline_t*	v2,
  divline_t*	v1 )`
- `P_CrossSubsector` (function) `progs/doomgeneric/p_sight.c:128` `boolean P_CrossSubsector (int num)` -- P_CrossSubsector Returns true if strace crosses the given subsector successfully.
- `P_CrossBSPNode` (function) `progs/doomgeneric/p_sight.c:258` `boolean P_CrossBSPNode (int bspnum)` -- P_CrossBSPNode Returns true if strace crosses the given node successfully.
- `P_CheckSight` (function) `progs/doomgeneric/p_sight.c:301` `boolean
P_CheckSight
( mobj_t*	t1,
  mobj_t*	t2 )`

## progs/doomgeneric/p_switch.c
Depends on: `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`
- `P_InitSwitchList` (function) `progs/doomgeneric/p_switch.c:101` `void P_InitSwitchList(void)` -- P_InitSwitchList Only called at game initialization.
- `P_StartButton` (function) `progs/doomgeneric/p_switch.c:149` `void
P_StartButton
( line_t*	line,
  bwhere_e	w,
  int		texture,
  int		time )`
- `P_ChangeSwitchTexture` (function) `progs/doomgeneric/p_switch.c:195` `void
P_ChangeSwitchTexture
( line_t*	line,
  int 		useAgain )`
- `P_UseSpecialLine` (function) `progs/doomgeneric/p_switch.c:270` `boolean
P_UseSpecialLine
( mobj_t*	thing,
  line_t*	line,
  int		side )`

## progs/doomgeneric/p_telept.c
Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`
- `EV_Teleport` (function) `progs/doomgeneric/p_telept.c:42` `int
EV_Teleport
( line_t*	line,
  int		side,
  mobj_t*	thing )`

## progs/doomgeneric/p_tick.c
Depends on: `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/z_zone.h`
- `P_InitThinkers` (function) `progs/doomgeneric/p_tick.c:46` `void P_InitThinkers (void)` -- P_InitThinkers
- `P_AddThinker` (function) `progs/doomgeneric/p_tick.c:58` `void P_AddThinker (thinker_t* thinker)` -- P_AddThinker Adds a new thinker at the end of the list.
- `P_RemoveThinker` (function) `progs/doomgeneric/p_tick.c:73` `void P_RemoveThinker (thinker_t* thinker)` -- P_RemoveThinker Deallocation is lazy -- it will not actually be freed until its thinking turn comes up.
- `P_AllocateThinker` (function) `progs/doomgeneric/p_tick.c:85` `void P_AllocateThinker (thinker_t*	thinker)` -- P_AllocateThinker Allocates memory and adds a new thinker at the end of the list.
- `P_RunThinkers` (function) `progs/doomgeneric/p_tick.c:94` `void P_RunThinkers (void)` -- P_RunThinkers
- `P_Ticker` (function) `progs/doomgeneric/p_tick.c:123` `void P_Ticker (void)`

## progs/doomgeneric/p_tick.h
Imported by: `progs/doomgeneric/g_game.c`
- `P_Ticker` (function) `progs/doomgeneric/p_tick.h:29` `void P_Ticker (void);` -- Called by C_Ticker, can call G_PlayerExited.

## progs/doomgeneric/p_user.c
Depends on: `progs/doomgeneric/d_event.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/p_local.h`
- `P_Thrust` (function) `progs/doomgeneric/p_user.c:52` `void
P_Thrust
( player_t*	player,
  angle_t	angle,
  fixed_t	move )`
- `P_CalcHeight` (function) `progs/doomgeneric/p_user.c:70` `void P_CalcHeight (player_t* player)` -- P_CalcHeight Calculate the walking / running height adjustment
- `P_MovePlayer` (function) `progs/doomgeneric/p_user.c:141` `void P_MovePlayer (player_t* player)` -- P_MovePlayer
- `P_DeathThink` (function) `progs/doomgeneric/p_user.c:175` `void P_DeathThink (player_t* player)`
- `P_PlayerThink` (function) `progs/doomgeneric/p_user.c:229` `void P_PlayerThink (player_t* player)` -- P_PlayerThink

## progs/doomgeneric/r_bsp.c
Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_bbox.h`, `progs/doomgeneric/r_main.h`, `progs/doomgeneric/r_plane.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/r_things.h`
- `R_StoreWallRange` (function) `progs/doomgeneric/r_bsp.c:51` `void R_StoreWallRange ( int start, int stop );`
- `R_ClearDrawSegs` (function) `progs/doomgeneric/r_bsp.c:61` `void R_ClearDrawSegs (void)` -- R_ClearDrawSegs
- `R_ClipSolidWallSegment` (function) `progs/doomgeneric/r_bsp.c:97` `void
R_ClipSolidWallSegment
( int			first,
  int			last )`
- `R_ClipPassWallSegment` (function) `progs/doomgeneric/r_bsp.c:190` `void
R_ClipPassWallSegment
( int	first,
  int	last )`
- `R_ClearClipSegs` (function) `progs/doomgeneric/r_bsp.c:238` `void R_ClearClipSegs (void)` -- R_ClearClipSegs
- `R_AddLine` (function) `progs/doomgeneric/r_bsp.c:252` `void R_AddLine (seg_t*	line)` -- R_AddLine Clips the given segment and adds any visible pieces to the line list.
- `R_CheckBBox` (function) `progs/doomgeneric/r_bsp.c:374` `boolean R_CheckBBox (fixed_t*	bspcoord)`
- `R_Subsector` (function) `progs/doomgeneric/r_bsp.c:490` `void R_Subsector (int num)` -- R_Subsector Determine floor/ceiling planes.
- `R_RenderBSPNode` (function) `progs/doomgeneric/r_bsp.c:545` `void R_RenderBSPNode (int bspnum)` -- RenderBSPNode Renders all subsectors below a given node, traversing subtree recursively.

## progs/doomgeneric/r_bsp.h
Imported by: `progs/doomgeneric/r_local.h`
- `R_ClearClipSegs` (function) `progs/doomgeneric/r_bsp.h:54` `void R_ClearClipSegs (void);` -- BSP?
- `R_ClearDrawSegs` (function) `progs/doomgeneric/r_bsp.h:55` `void R_ClearDrawSegs (void);`
- `R_RenderBSPNode` (function) `progs/doomgeneric/r_bsp.h:58` `void R_RenderBSPNode (int bspnum);`

## progs/doomgeneric/r_data.c
Depends on: `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_data.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/r_sky.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`
- `R_DrawColumnInCache` (function) `progs/doomgeneric/r_data.c:186` `void
R_DrawColumnInCache
( column_t*	patch,
  byte*		cache,
  int		originy,
  int		cacheheight )`
- `R_GenerateComposite` (function) `progs/doomgeneric/r_data.c:226` `void R_GenerateComposite (int texnum)` -- R_GenerateComposite Using the texture definition, the composite texture is created from the patches, and each column...
- `R_GenerateLookup` (function) `progs/doomgeneric/r_data.c:294` `void R_GenerateLookup (int texnum)` -- R_GenerateLookup
- `R_GetColumn` (function) `progs/doomgeneric/r_data.c:383` `byte*
R_GetColumn
( int		tex,
  int		col )`
- `GenerateTextureHashTable` (function) `progs/doomgeneric/r_data.c:404` `static void GenerateTextureHashTable(void)`
- `R_InitTextures` (function) `progs/doomgeneric/r_data.c:451` `void R_InitTextures (void)` -- R_InitTextures Initializes the texture list with the textures from the world map.
- `R_InitFlats` (function) `progs/doomgeneric/r_data.c:633` `void R_InitFlats (void)` -- R_InitFlats
- `R_InitSpriteLumps` (function) `progs/doomgeneric/r_data.c:655` `void R_InitSpriteLumps (void)` -- R_InitSpriteLumps Finds the width and hoffset of all sprites in the wad, so the sprite does not need to be cached...
- `R_InitColormaps` (function) `progs/doomgeneric/r_data.c:685` `void R_InitColormaps (void)` -- R_InitColormaps
- `R_InitData` (function) `progs/doomgeneric/r_data.c:703` `void R_InitData (void)` -- R_InitData Locates all the lumps that will be used by all views Must be called after W_Init.
- `R_FlatNumForName` (function) `progs/doomgeneric/r_data.c:720` `int R_FlatNumForName (char* name)` -- R_FlatNumForName Retrieval, get a flat number for a flat name.
- `R_CheckTextureNumForName` (function) `progs/doomgeneric/r_data.c:744` `int	R_CheckTextureNumForName (char *name)` -- R_CheckTextureNumForName Check whether texture is available.
- `R_TextureNumForName` (function) `progs/doomgeneric/r_data.c:775` `int	R_TextureNumForName (char* name)` -- R_TextureNumForName Calls R_CheckTextureNumForName, aborts with error message.
- `R_PrecacheLevel` (function) `progs/doomgeneric/r_data.c:800` `void R_PrecacheLevel (void)`

## progs/doomgeneric/r_data.h
Depends on: `progs/doomgeneric/r_defs.h`, `progs/doomgeneric/r_state.h`
Imported by: `progs/doomgeneric/g_game.c`, `progs/doomgeneric/r_data.c`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/r_main.h`, `progs/doomgeneric/r_plane.h`, `progs/doomgeneric/r_sky.c`, `progs/doomgeneric/r_state.h`
- `R_GetColumn` (function) `progs/doomgeneric/r_data.h:30` `byte* R_GetColumn ( int tex, int col );`
- `R_InitData` (function) `progs/doomgeneric/r_data.h:36` `void R_InitData (void);` -- I/O, setting up the stuff.
- `R_PrecacheLevel` (function) `progs/doomgeneric/r_data.h:37` `void R_PrecacheLevel (void);`
- `R_FlatNumForName` (function) `progs/doomgeneric/r_data.h:43` `int R_FlatNumForName (char* name);` -- Retrieval.
- `R_TextureNumForName` (function) `progs/doomgeneric/r_data.h:48` `int R_TextureNumForName (char *name);` -- Called by P_Ticker for switches and animations, returns the texture number for the texture name.
- `R_CheckTextureNumForName` (function) `progs/doomgeneric/r_data.h:49` `int R_CheckTextureNumForName (char *name);`


Next: [API_p15.md](API_p15.md)
