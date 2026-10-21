# Symbols (page 17 of 27)
Previous: [SYMBOLS_p16.md](SYMBOLS_p16.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `rejectmatrix` | variable | `progs/doomgeneric/p_local.h:261` | `extern byte* rejectmatrix;` |
| `spechit` | variable | `progs/doomgeneric/p_local.h:222` | `extern line_t* spechit[MAXSPECIALCROSS];` |
| `thinkercap` | variable | `progs/doomgeneric/p_local.h:67` | `extern thinker_t thinkercap;` |
| `tmceilingz` | variable | `progs/doomgeneric/p_local.h:206` | `extern fixed_t tmceilingz;` |
| `tmfloorz` | variable | `progs/doomgeneric/p_local.h:205` | `extern fixed_t tmfloorz;` |
| `trace` | variable | `progs/doomgeneric/p_local.h:183` | `extern divline_t trace;` |
| `DEFAULT_SPECHIT_MAGIC` | macro | `progs/doomgeneric/p_map.c:50` | `#define DEFAULT_SPECHIT_MAGIC` |
| `PIT_ChangeSector` | function | `progs/doomgeneric/p_map.c:1304` | `boolean PIT_ChangeSector (mobj_t*	thing)` |
| `PIT_CheckLine` | function | `progs/doomgeneric/p_map.c:206` | `boolean PIT_CheckLine (line_t* ld)` |
| `PIT_CheckThing` | function | `progs/doomgeneric/p_map.c:275` | `boolean PIT_CheckThing (mobj_t* thing)` |
| `PIT_RadiusAttack` | function | `progs/doomgeneric/p_map.c:1211` | `boolean PIT_RadiusAttack (mobj_t* thing)` |
| `PIT_StompThing` | function | `progs/doomgeneric/p_map.c:97` | `boolean PIT_StompThing (mobj_t* thing)` |
| `PTR_AimTraverse` | function | `progs/doomgeneric/p_map.c:843` | `boolean PTR_AimTraverse (intercept_t* in)` |
| `PTR_ShootTraverse` | function | `progs/doomgeneric/p_map.c:928` | `boolean PTR_ShootTraverse (intercept_t* in)` |
| `PTR_SlideTraverse` | function | `progs/doomgeneric/p_map.c:663` | `boolean PTR_SlideTraverse (intercept_t* in)` |
| `PTR_UseTraverse` | function | `progs/doomgeneric/p_map.c:1142` | `boolean	PTR_UseTraverse (intercept_t* in)` |
| `P_AimLineAttack` | function | `progs/doomgeneric/p_map.c:1068` | `fixed_t P_AimLineAttack ( mobj_t*	t1,   angle_t	angle,   fixed_t	distance )` |
| `P_ChangeSector` | function | `progs/doomgeneric/p_map.c:1368` | `boolean P_ChangeSector ( sector_t*	sector,   boolean	crunch )` |
| `P_CheckPosition` | function | `progs/doomgeneric/p_map.c:402` | `boolean P_CheckPosition ( mobj_t*	thing,   fixed_t	x,   fixed_t	y )` |
| `P_HitSlideLine` | function | `progs/doomgeneric/p_map.c:611` | `void P_HitSlideLine (line_t* ld)` |
| `P_LineAttack` | function | `progs/doomgeneric/p_map.c:1110` | `void P_LineAttack ( mobj_t*	t1,   angle_t	angle,   fixed_t	distance,   fixed_t	slope,   int		dama...` |
| `P_RadiusAttack` | function | `progs/doomgeneric/p_map.c:1253` | `void P_RadiusAttack ( mobj_t*	spot,   mobj_t*	source,   int		damage )` |
| `P_SlideMove` | function | `progs/doomgeneric/p_map.c:722` | `void P_SlideMove (mobj_t* mo)` |
| `P_TeleportMove` | function | `progs/doomgeneric/p_map.c:131` | `boolean P_TeleportMove ( mobj_t*	thing,   fixed_t	x,   fixed_t	y )` |
| `P_ThingHeightClip` | function | `progs/doomgeneric/p_map.c:557` | `boolean P_ThingHeightClip (mobj_t* thing)` |
| `P_TryMove` | function | `progs/doomgeneric/p_map.c:478` | `boolean P_TryMove ( mobj_t*	thing,   fixed_t	x,   fixed_t	y )` |
| `P_UseLines` | function | `progs/doomgeneric/p_map.c:1177` | `void P_UseLines (player_t*	player)` |
| `SpechitOverrun` | function | `progs/doomgeneric/p_map.c:1391` | `static void SpechitOverrun(line_t *ld)` |
| `bottomslope` | variable | `progs/doomgeneric/p_map.c:835` | `extern fixed_t bottomslope;` |
| `topslope` | variable | `progs/doomgeneric/p_map.c:834` | `extern fixed_t topslope;` |
| `InterceptsMemoryOverrun` | function | `progs/doomgeneric/p_maputl.c:782` | `static void InterceptsMemoryOverrun(int location, int value)` |
| `InterceptsOverrun` | function | `progs/doomgeneric/p_maputl.c:827` | `static void InterceptsOverrun(int num_intercepts, intercept_t *intercept)` |
| `PIT_AddLineIntercepts` | function | `progs/doomgeneric/p_maputl.c:559` | `boolean PIT_AddLineIntercepts (line_t* ld)` |
| `PIT_AddThingIntercepts` | function | `progs/doomgeneric/p_maputl.c:614` | `boolean PIT_AddThingIntercepts (mobj_t* thing)` |
| `P_AproxDistance` | function | `progs/doomgeneric/p_maputl.c:44` | `fixed_t P_AproxDistance ( fixed_t	dx,   fixed_t	dy )` |
| `P_BlockLinesIterator` | function | `progs/doomgeneric/p_maputl.c:467` | `boolean P_BlockLinesIterator ( int			x,   int			y,   boolean(*func)(line_t*) )` |
| `P_BlockThingsIterator` | function | `progs/doomgeneric/p_maputl.c:508` | `boolean P_BlockThingsIterator ( int			x,   int			y,   boolean(*func)(mobj_t*) )` |
| `P_BoxOnLineSide` | function | `progs/doomgeneric/p_maputl.c:105` | `int P_BoxOnLineSide ( fixed_t*	tmbox,   line_t*	ld )` |
| `P_InterceptVector` | function | `progs/doomgeneric/p_maputl.c:226` | `fixed_t P_InterceptVector ( divline_t*	v2,   divline_t*	v1 )` |
| `P_LineOpening` | function | `progs/doomgeneric/p_maputl.c:295` | `void P_LineOpening (line_t* linedef)` |
| `P_MakeDivline` | function | `progs/doomgeneric/p_maputl.c:206` | `void P_MakeDivline ( line_t*	li,   divline_t*	dl )` |
| `P_PathTraverse` | function | `progs/doomgeneric/p_maputl.c:861` | `boolean P_PathTraverse ( fixed_t		x1,   fixed_t		y1,   fixed_t		x2,   fixed_t		y2,   int			flags,...` |
| `P_PointOnDivlineSide` | function | `progs/doomgeneric/p_maputl.c:156` | `int P_PointOnDivlineSide ( fixed_t	x,   fixed_t	y,   divline_t*	line )` |
| `P_PointOnLineSide` | function | `progs/doomgeneric/p_maputl.c:61` | `int P_PointOnLineSide ( fixed_t	x,   fixed_t	y,   line_t*	line )` |
| `P_SetThingPosition` | function | `progs/doomgeneric/p_maputl.c:391` | `void P_SetThingPosition (mobj_t* thing)` |
| `P_TraverseIntercepts` | function | `progs/doomgeneric/p_maputl.c:682` | `boolean P_TraverseIntercepts ( traverser_t	func,   fixed_t	maxfrac )` |
| `P_UnsetThingPosition` | function | `progs/doomgeneric/p_maputl.c:342` | `void P_UnsetThingPosition (mobj_t* thing)` |
| `bulletslope` | variable | `progs/doomgeneric/p_maputl.c:731` | `extern fixed_t bulletslope;` |
| `intercepts_overrun_t` | struct | `progs/doomgeneric/p_maputl.c:738` | `` |
| `FRICTION` | macro | `progs/doomgeneric/p_mobj.c:106` | `#define FRICTION` |
| `G_PlayerReborn` | function | `progs/doomgeneric/p_mobj.c:37` | `void G_PlayerReborn (int player);` |
| `P_CheckMissileSpawn` | function | `progs/doomgeneric/p_mobj.c:907` | `void P_CheckMissileSpawn (mobj_t* th)` |
| `P_ExplodeMissile` | function | `progs/doomgeneric/p_mobj.c:84` | `void P_ExplodeMissile (mobj_t* mo)` |
| `P_MobjThinker` | function | `progs/doomgeneric/p_mobj.c:441` | `void P_MobjThinker (mobj_t* mobj)` |
| `P_NightmareRespawn` | function | `progs/doomgeneric/p_mobj.c:383` | `void P_NightmareRespawn (mobj_t* mobj)` |
| `P_RemoveMobj` | function | `progs/doomgeneric/p_mobj.c:572` | `void P_RemoveMobj (mobj_t* mobj)` |
| `P_RespawnSpecials` | function | `progs/doomgeneric/p_mobj.c:604` | `void P_RespawnSpecials (void)` |
| `P_SetMobjState` | function | `progs/doomgeneric/p_mobj.c:48` | `boolean P_SetMobjState ( mobj_t*	mobj,   statenum_t	state )` |
| `P_SpawnBlood` | function | `progs/doomgeneric/p_mobj.c:878` | `void P_SpawnBlood ( fixed_t	x,   fixed_t	y,   fixed_t	z,   int		damage )` |
| `P_SpawnMapThing` | function | `progs/doomgeneric/p_mobj.c:739` | `void P_SpawnMapThing (mapthing_t* mthing)` |
| `P_SpawnMissile` | function | `progs/doomgeneric/p_mobj.c:950` | `mobj_t* P_SpawnMissile ( mobj_t*	source,   mobj_t*	dest,   mobjtype_t	type )` |
| `P_SpawnMobj` | function | `progs/doomgeneric/p_mobj.c:506` | `mobj_t* P_SpawnMobj ( fixed_t	x,   fixed_t	y,   fixed_t	z,   mobjtype_t	type )` |
| `P_SpawnPlayer` | function | `progs/doomgeneric/p_mobj.c:668` | `void P_SpawnPlayer (mapthing_t* mthing)` |
| `P_SpawnPlayerMissile` | function | `progs/doomgeneric/p_mobj.c:996` | `void P_SpawnPlayerMissile ( mobj_t*	source,   mobjtype_t	type )` |
| `P_SpawnPuff` | function | `progs/doomgeneric/p_mobj.c:851` | `void P_SpawnPuff ( fixed_t	x,   fixed_t	y,   fixed_t	z )` |
| `P_SubstNullMobj` | function | `progs/doomgeneric/p_mobj.c:929` | `mobj_t *P_SubstNullMobj(mobj_t *mobj)` |
| `P_XYMovement` | function | `progs/doomgeneric/p_mobj.c:108` | `void P_XYMovement (mobj_t* mo)` |
| `P_ZMovement` | function | `progs/doomgeneric/p_mobj.c:240` | `void P_ZMovement (mobj_t* mo)` |
| `STOPSPEED` | macro | `progs/doomgeneric/p_mobj.c:105` | `#define STOPSPEED` |
| `attackrange` | variable | `progs/doomgeneric/p_mobj.c:848` | `extern fixed_t attackrange;` |
| `__P_MOBJ__` | macro | `progs/doomgeneric/p_mobj.h:21` | `#define __P_MOBJ__` |
| `mobj_s` | struct | `progs/doomgeneric/p_mobj.h:201` | `` |
| `thinker` | type_alias | `progs/doomgeneric/p_mobj.h:201` | `typedef struct mobj_s { // List: thinker links. thinker_t thinker;` |
| `EV_DoPlat` | function | `progs/doomgeneric/p_plats.c:129` | `int EV_DoPlat ( line_t*	line,   plattype_e	type,   int		amount )` |
| `EV_StopPlat` | function | `progs/doomgeneric/p_plats.c:263` | `void EV_StopPlat(line_t* line)` |
| `P_ActivateInStasis` | function | `progs/doomgeneric/p_plats.c:248` | `void P_ActivateInStasis(int tag)` |
| `P_AddActivePlat` | function | `progs/doomgeneric/p_plats.c:278` | `void P_AddActivePlat(plat_t* plat)` |
| `P_RemoveActivePlat` | function | `progs/doomgeneric/p_plats.c:291` | `void P_RemoveActivePlat(plat_t* plat)` |
| `T_PlatRaise` | function | `progs/doomgeneric/p_plats.c:45` | `void T_PlatRaise(plat_t* plat)` |
| `A_BFGSpray` | function | `progs/doomgeneric/p_pspr.c:790` | `void A_BFGSpray (mobj_t* mo)` |
| `A_BFGsound` | function | `progs/doomgeneric/p_pspr.c:827` | `void A_BFGsound ( player_t*	player,   pspdef_t*	psp )` |
| `A_CheckReload` | function | `progs/doomgeneric/p_pspr.c:357` | `void A_CheckReload ( player_t*	player,   pspdef_t*	psp )` |
| `A_FireBFG` | function | `progs/doomgeneric/p_pspr.c:572` | `void A_FireBFG ( player_t*	player,   pspdef_t*	psp )` |
| `A_FireCGun` | function | `progs/doomgeneric/p_pspr.c:742` | `void A_FireCGun ( player_t*	player,   pspdef_t*	psp )` |
| `A_FireMissile` | function | `progs/doomgeneric/p_pspr.c:559` | `void A_FireMissile ( player_t*	player,   pspdef_t*	psp )` |
| `A_FirePistol` | function | `progs/doomgeneric/p_pspr.c:656` | `void A_FirePistol ( player_t*	player,   pspdef_t*	psp )` |
| `A_FirePlasma` | function | `progs/doomgeneric/p_pspr.c:587` | `void A_FirePlasma ( player_t*	player,   pspdef_t*	psp )` |
| `A_FireShotgun` | function | `progs/doomgeneric/p_pspr.c:678` | `void A_FireShotgun ( player_t*	player,   pspdef_t*	psp )` |
| `A_FireShotgun2` | function | `progs/doomgeneric/p_pspr.c:705` | `void A_FireShotgun2 ( player_t*	player,   pspdef_t*	psp )` |
| `A_GunFlash` | function | `progs/doomgeneric/p_pspr.c:440` | `void A_GunFlash ( player_t*	player,   pspdef_t*	psp )` |
| `A_Light0` | function | `progs/doomgeneric/p_pspr.c:770` | `void A_Light0 (player_t *player, pspdef_t *psp)` |
| `A_Light1` | function | `progs/doomgeneric/p_pspr.c:775` | `void A_Light1 (player_t *player, pspdef_t *psp)` |
| `A_Light2` | function | `progs/doomgeneric/p_pspr.c:780` | `void A_Light2 (player_t *player, pspdef_t *psp)` |
| `A_Lower` | function | `progs/doomgeneric/p_pspr.c:376` | `void A_Lower ( player_t*	player,   pspdef_t*	psp )` |
| `A_Punch` | function | `progs/doomgeneric/p_pspr.c:459` | `void A_Punch ( player_t*	player,   pspdef_t*	psp )` |
| `A_Raise` | function | `progs/doomgeneric/p_pspr.c:414` | `void A_Raise ( player_t*	player,   pspdef_t*	psp )` |
| `A_ReFire` | function | `progs/doomgeneric/p_pspr.c:334` | `void A_ReFire ( player_t*	player,   pspdef_t*	psp )` |
| `A_Saw` | function | `progs/doomgeneric/p_pspr.c:493` | `void A_Saw ( player_t*	player,   pspdef_t*	psp )` |
| `A_WeaponReady` | function | `progs/doomgeneric/p_pspr.c:273` | `void A_WeaponReady ( player_t*	player,   pspdef_t*	psp )` |
| `DecreaseAmmo` | function | `progs/doomgeneric/p_pspr.c:542` | `static void DecreaseAmmo(player_t *player, int ammonum, int amount)` |
| `LOWERSPEED` | macro | `progs/doomgeneric/p_pspr.c:38` | `#define LOWERSPEED` |
| `P_BringUpWeapon` | function | `progs/doomgeneric/p_pspr.c:129` | `void P_BringUpWeapon (player_t* player)` |
| `P_BulletSlope` | function | `progs/doomgeneric/p_pspr.c:610` | `void P_BulletSlope (mobj_t*	mo)` |
| `P_CalcSwing` | function | `progs/doomgeneric/p_pspr.c:103` | `void P_CalcSwing (player_t*	player)` |
| `P_CheckAmmo` | function | `progs/doomgeneric/p_pspr.c:152` | `boolean P_CheckAmmo (player_t* player)` |
| `P_DropWeapon` | function | `progs/doomgeneric/p_pspr.c:256` | `void P_DropWeapon (player_t* player)` |
| `P_FireWeapon` | function | `progs/doomgeneric/p_pspr.c:237` | `void P_FireWeapon (player_t* player)` |
| `P_GunShot` | function | `progs/doomgeneric/p_pspr.c:635` | `void P_GunShot ( mobj_t*	mo,   boolean	accurate )` |
| `P_MovePsprites` | function | `progs/doomgeneric/p_pspr.c:860` | `void P_MovePsprites (player_t* player)` |
| `P_SetPsprite` | function | `progs/doomgeneric/p_pspr.c:50` | `void P_SetPsprite ( player_t*	player,   int		position,   statenum_t	stnum )` |
| `P_SetupPsprites` | function | `progs/doomgeneric/p_pspr.c:840` | `void P_SetupPsprites (player_t* player)` |
| `RAISESPEED` | macro | `progs/doomgeneric/p_pspr.c:39` | `#define RAISESPEED` |
| `WEAPONBOTTOM` | macro | `progs/doomgeneric/p_pspr.c:41` | `#define WEAPONBOTTOM` |
| `WEAPONTOP` | macro | `progs/doomgeneric/p_pspr.c:42` | `#define WEAPONTOP` |
| `FF_FRAMEMASK` | macro | `progs/doomgeneric/p_pspr.h:45` | `#define FF_FRAMEMASK` |
| `FF_FULLBRIGHT` | macro | `progs/doomgeneric/p_pspr.h:44` | `#define FF_FULLBRIGHT` |
| `__P_PSPR__` | macro | `progs/doomgeneric/p_pspr.h:21` | `#define __P_PSPR__` |
| `pspdef_t` | struct | `progs/doomgeneric/p_pspr.h:62` | `` |
| `P_ArchivePlayers` | function | `progs/doomgeneric/p_saveg.c:1440` | `void P_ArchivePlayers (void)` |
| `P_ArchiveSpecials` | function | `progs/doomgeneric/p_saveg.c:1704` | `void P_ArchiveSpecials (void)` |
| `P_ArchiveThinkers` | function | `progs/doomgeneric/p_saveg.c:1592` | `void P_ArchiveThinkers (void)` |
| `P_ArchiveWorld` | function | `progs/doomgeneric/p_saveg.c:1484` | `void P_ArchiveWorld (void)` |
| `P_ReadSaveGameEOF` | function | `progs/doomgeneric/p_saveg.c:1419` | `boolean P_ReadSaveGameEOF(void)` |
| `P_ReadSaveGameHeader` | function | `progs/doomgeneric/p_saveg.c:1379` | `boolean P_ReadSaveGameHeader(void)` |
| `P_SaveGameFile` | function | `progs/doomgeneric/p_saveg.c:61` | `char *P_SaveGameFile(int slot)` |
| `P_TempSaveGameFile` | function | `progs/doomgeneric/p_saveg.c:47` | `char *P_TempSaveGameFile(void)` |
| `P_UnArchivePlayers` | function | `progs/doomgeneric/p_saveg.c:1460` | `void P_UnArchivePlayers (void)` |
| `P_UnArchiveSpecials` | function | `progs/doomgeneric/p_saveg.c:1793` | `void P_UnArchiveSpecials (void)` |
| `P_UnArchiveThinkers` | function | `progs/doomgeneric/p_saveg.c:1620` | `void P_UnArchiveThinkers (void)` |
| `P_UnArchiveWorld` | function | `progs/doomgeneric/p_saveg.c:1532` | `void P_UnArchiveWorld (void)` |
| `P_WriteSaveGameEOF` | function | `progs/doomgeneric/p_saveg.c:1432` | `void P_WriteSaveGameEOF(void)` |
| `P_WriteSaveGameHeader` | function | `progs/doomgeneric/p_saveg.c:1347` | `void P_WriteSaveGameHeader(char *description)` |
| `SAVEGAME_EOF` | macro | `progs/doomgeneric/p_saveg.c:36` | `#define SAVEGAME_EOF` |
| `VERSIONSIZE` | macro | `progs/doomgeneric/p_saveg.c:37` | `#define VERSIONSIZE` |
| `saveg_read16` | function | `progs/doomgeneric/p_saveg.c:112` | `static short saveg_read16(void)` |
| `saveg_read32` | function | `progs/doomgeneric/p_saveg.c:128` | `static int saveg_read32(void)` |
| `saveg_read8` | function | `progs/doomgeneric/p_saveg.c:81` | `static byte saveg_read8(void)` |
| `saveg_read_actionf_t` | function | `progs/doomgeneric/p_saveg.c:248` | `static void saveg_read_actionf_t(actionf_t *str)` |
| `saveg_read_ceiling_t` | function | `progs/doomgeneric/p_saveg.c:908` | `static void saveg_read_ceiling_t(ceiling_t *str)` |
| `saveg_read_enum` | macro | `progs/doomgeneric/p_saveg.c:197` | `#define saveg_read_enum` |
| `saveg_read_floormove_t` | function | `progs/doomgeneric/p_saveg.c:1042` | `static void saveg_read_floormove_t(floormove_t *str)` |
| `saveg_read_glow_t` | function | `progs/doomgeneric/p_saveg.c:1304` | `static void saveg_read_glow_t(glow_t *str)` |
| `saveg_read_lightflash_t` | function | `progs/doomgeneric/p_saveg.c:1194` | `static void saveg_read_lightflash_t(lightflash_t *str)` |
| `saveg_read_mapthing_t` | function | `progs/doomgeneric/p_saveg.c:208` | `static void saveg_read_mapthing_t(mapthing_t *str)` |
| `saveg_read_mobj_t` | function | `progs/doomgeneric/p_saveg.c:301` | `static void saveg_read_mobj_t(mobj_t *str)` |
| `saveg_read_pad` | function | `progs/doomgeneric/p_saveg.c:150` | `static void saveg_read_pad(void)` |
| `saveg_read_plat_t` | function | `progs/doomgeneric/p_saveg.c:1109` | `static void saveg_read_plat_t(plat_t *str)` |
| `saveg_read_player_t` | function | `progs/doomgeneric/p_saveg.c:641` | `static void saveg_read_player_t(player_t *str)` |
| `saveg_read_pspdef_t` | function | `progs/doomgeneric/p_saveg.c:589` | `static void saveg_read_pspdef_t(pspdef_t *str)` |
| `saveg_read_strobe_t` | function | `progs/doomgeneric/p_saveg.c:1249` | `static void saveg_read_strobe_t(strobe_t *str)` |
| `saveg_read_think_t` | macro | `progs/doomgeneric/p_saveg.c:266` | `#define saveg_read_think_t` |
| `saveg_read_thinker_t` | function | `progs/doomgeneric/p_saveg.c:273` | `static void saveg_read_thinker_t(thinker_t *str)` |
| `saveg_read_ticcmd_t` | function | `progs/doomgeneric/p_saveg.c:541` | `static void saveg_read_ticcmd_t(ticcmd_t *str)` |
| `saveg_read_vldoor_t` | function | `progs/doomgeneric/p_saveg.c:981` | `static void saveg_read_vldoor_t(vldoor_t *str)` |
| `saveg_readp` | function | `progs/doomgeneric/p_saveg.c:185` | `static void *saveg_readp(void)` |
| `saveg_write16` | function | `progs/doomgeneric/p_saveg.c:122` | `static void saveg_write16(short value)` |
| `saveg_write32` | function | `progs/doomgeneric/p_saveg.c:140` | `static void saveg_write32(int value)` |
| `saveg_write8` | function | `progs/doomgeneric/p_saveg.c:99` | `static void saveg_write8(byte value)` |
| `saveg_write_actionf_t` | function | `progs/doomgeneric/p_saveg.c:254` | `static void saveg_write_actionf_t(actionf_t *str)` |
| `saveg_write_ceiling_t` | function | `progs/doomgeneric/p_saveg.c:944` | `static void saveg_write_ceiling_t(ceiling_t *str)` |
| `saveg_write_enum` | macro | `progs/doomgeneric/p_saveg.c:198` | `#define saveg_write_enum` |
| `saveg_write_floormove_t` | function | `progs/doomgeneric/p_saveg.c:1075` | `static void saveg_write_floormove_t(floormove_t *str)` |
| `saveg_write_glow_t` | function | `progs/doomgeneric/p_saveg.c:1325` | `static void saveg_write_glow_t(glow_t *str)` |
| `saveg_write_lightflash_t` | function | `progs/doomgeneric/p_saveg.c:1221` | `static void saveg_write_lightflash_t(lightflash_t *str)` |
| `saveg_write_mapthing_t` | function | `progs/doomgeneric/p_saveg.c:226` | `static void saveg_write_mapthing_t(mapthing_t *str)` |
| `saveg_write_mobj_t` | function | `progs/doomgeneric/p_saveg.c:421` | `static void saveg_write_mobj_t(mobj_t *str)` |
| `saveg_write_pad` | function | `progs/doomgeneric/p_saveg.c:166` | `static void saveg_write_pad(void)` |
| `saveg_write_plat_t` | function | `progs/doomgeneric/p_saveg.c:1151` | `static void saveg_write_plat_t(plat_t *str)` |
| `saveg_write_player_t` | function | `progs/doomgeneric/p_saveg.c:772` | `static void saveg_write_player_t(player_t *str)` |
| `saveg_write_pspdef_t` | function | `progs/doomgeneric/p_saveg.c:615` | `static void saveg_write_pspdef_t(pspdef_t *str)` |
| `saveg_write_strobe_t` | function | `progs/doomgeneric/p_saveg.c:1276` | `static void saveg_write_strobe_t(strobe_t *str)` |
| `saveg_write_think_t` | macro | `progs/doomgeneric/p_saveg.c:267` | `#define saveg_write_think_t` |
| `saveg_write_thinker_t` | function | `progs/doomgeneric/p_saveg.c:285` | `static void saveg_write_thinker_t(thinker_t *str)` |
| `saveg_write_ticcmd_t` | function | `progs/doomgeneric/p_saveg.c:563` | `static void saveg_write_ticcmd_t(ticcmd_t *str)` |
| `saveg_write_vldoor_t` | function | `progs/doomgeneric/p_saveg.c:1011` | `static void saveg_write_vldoor_t(vldoor_t *str)` |
| `saveg_writep` | function | `progs/doomgeneric/p_saveg.c:190` | `static void saveg_writep(void *p)` |
| `P_ArchivePlayers` | function | `progs/doomgeneric/p_saveg.h:49` | `void P_ArchivePlayers (void);` |
| `P_ArchiveSpecials` | function | `progs/doomgeneric/p_saveg.h:55` | `void P_ArchiveSpecials (void);` |
| `P_ArchiveThinkers` | function | `progs/doomgeneric/p_saveg.h:53` | `void P_ArchiveThinkers (void);` |
| `P_ArchiveWorld` | function | `progs/doomgeneric/p_saveg.h:51` | `void P_ArchiveWorld (void);` |
| `P_SaveGameFile` | function | `progs/doomgeneric/p_saveg.h:35` | `char *P_SaveGameFile(int slot);` |
| `P_TempSaveGameFile` | function | `progs/doomgeneric/p_saveg.h:31` | `char *P_TempSaveGameFile(void);` |
| `P_UnArchivePlayers` | function | `progs/doomgeneric/p_saveg.h:50` | `void P_UnArchivePlayers (void);` |
| `P_UnArchiveSpecials` | function | `progs/doomgeneric/p_saveg.h:56` | `void P_UnArchiveSpecials (void);` |
| `P_UnArchiveThinkers` | function | `progs/doomgeneric/p_saveg.h:54` | `void P_UnArchiveThinkers (void);` |
| `P_UnArchiveWorld` | function | `progs/doomgeneric/p_saveg.h:52` | `void P_UnArchiveWorld (void);` |
| `P_WriteSaveGameEOF` | function | `progs/doomgeneric/p_saveg.h:45` | `void P_WriteSaveGameEOF(void);` |
| `P_WriteSaveGameHeader` | function | `progs/doomgeneric/p_saveg.h:40` | `void P_WriteSaveGameHeader(char *description);` |
| `SAVESTRINGSIZE` | macro | `progs/doomgeneric/p_saveg.h:27` | `#define SAVESTRINGSIZE` |
| `__P_SAVEG__` | macro | `progs/doomgeneric/p_saveg.h:21` | `#define __P_SAVEG__` |
| `save_stream` | variable | `progs/doomgeneric/p_saveg.h:58` | `extern FILE *save_stream;` |
| `savegame_error` | variable | `progs/doomgeneric/p_saveg.h:59` | `extern boolean savegame_error;` |
| `GetSectorAtNullAddress` | function | `progs/doomgeneric/p_setup.c:153` | `sector_t* GetSectorAtNullAddress(void)` |
| `MAX_DEATHMATCH_STARTS` | macro | `progs/doomgeneric/p_setup.c:105` | `#define MAX_DEATHMATCH_STARTS` |
| `P_GroupLines` | function | `progs/doomgeneric/p_setup.c:545` | `void P_GroupLines (void)` |
| `P_Init` | function | `progs/doomgeneric/p_setup.c:847` | `void P_Init (void)` |
| `P_LoadBlockMap` | function | `progs/doomgeneric/p_setup.c:504` | `void P_LoadBlockMap (int lump)` |
| `P_LoadLineDefs` | function | `progs/doomgeneric/p_setup.c:392` | `void P_LoadLineDefs (int lump)` |
| `P_LoadNodes` | function | `progs/doomgeneric/p_setup.c:298` | `void P_LoadNodes (int lump)` |
| `P_LoadReject` | function | `progs/doomgeneric/p_setup.c:712` | `static void P_LoadReject(int lumpnum)` |
| `P_LoadSectors` | function | `progs/doomgeneric/p_setup.c:265` | `void P_LoadSectors (int lump)` |
| `P_LoadSegs` | function | `progs/doomgeneric/p_setup.c:172` | `void P_LoadSegs (int lump)` |
| `P_LoadSideDefs` | function | `progs/doomgeneric/p_setup.c:473` | `void P_LoadSideDefs (int lump)` |
| `P_LoadSubsectors` | function | `progs/doomgeneric/p_setup.c:236` | `void P_LoadSubsectors (int lump)` |
| `P_LoadThings` | function | `progs/doomgeneric/p_setup.c:335` | `void P_LoadThings (int lump)` |
| `P_LoadVertexes` | function | `progs/doomgeneric/p_setup.c:118` | `void P_LoadVertexes (int lump)` |
| `P_SetupLevel` | function | `progs/doomgeneric/p_setup.c:744` | `void P_SetupLevel ( int		episode,   int		map,   int		playermask,   skill_t	skill)` |
| `P_SpawnMapThing` | function | `progs/doomgeneric/p_setup.c:44` | `void P_SpawnMapThing (mapthing_t* mthing);` |
| `PadRejectArray` | function | `progs/doomgeneric/p_setup.c:661` | `static void PadRejectArray(byte *array, unsigned int len)` |
| `P_Init` | function | `progs/doomgeneric/p_setup.h:35` | `void P_Init (void);` |
| `P_SetupLevel` | function | `progs/doomgeneric/p_setup.h:28` | `void P_SetupLevel ( int episode, int map, int playermask, skill_t skill);` |
| `__P_SETUP__` | macro | `progs/doomgeneric/p_setup.h:21` | `#define __P_SETUP__` |
| `P_CheckSight` | function | `progs/doomgeneric/p_sight.c:301` | `boolean P_CheckSight ( mobj_t*	t1,   mobj_t*	t2 )` |
| `P_CrossBSPNode` | function | `progs/doomgeneric/p_sight.c:258` | `boolean P_CrossBSPNode (int bspnum)` |
| `P_CrossSubsector` | function | `progs/doomgeneric/p_sight.c:128` | `boolean P_CrossSubsector (int num)` |
| `P_DivlineSide` | function | `progs/doomgeneric/p_sight.c:48` | `int P_DivlineSide ( fixed_t	x,   fixed_t	y,   divline_t*	node )` |
| `P_InterceptVector2` | function | `progs/doomgeneric/p_sight.c:102` | `fixed_t P_InterceptVector2 ( divline_t*	v2,   divline_t*	v1 )` |
| `DONUT_FLOORHEIGHT_DEFAULT` | macro | `progs/doomgeneric/p_spec.c:1175` | `#define DONUT_FLOORHEIGHT_DEFAULT` |
| `DONUT_FLOORPIC_DEFAULT` | macro | `progs/doomgeneric/p_spec.c:1176` | `#define DONUT_FLOORPIC_DEFAULT` |
| `DonutOverrun` | function | `progs/doomgeneric/p_spec.c:1178` | `static void DonutOverrun(fixed_t *s3_floorheight, short *s3_floorpic,                          li...` |
| `EV_DoDonut` | function | `progs/doomgeneric/p_spec.c:1257` | `int EV_DoDonut(line_t*	line)` |
| `MAXANIMS` | macro | `progs/doomgeneric/p_spec.c:78` | `#define MAXANIMS` |
| `MAXLINEANIMS` | macro | `progs/doomgeneric/p_spec.c:136` | `#define MAXLINEANIMS` |
| `MAX_ADJOINING_SECTORS` | macro | `progs/doomgeneric/p_spec.c:327` | `#define MAX_ADJOINING_SECTORS` |
| `P_CrossSpecialLine` | function | `progs/doomgeneric/p_spec.c:502` | `void P_CrossSpecialLine ( int		linenum,   int		side,   mobj_t*	thing )` |
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

Next: [SYMBOLS_p18.md](SYMBOLS_p18.md)
