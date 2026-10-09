# Subsystem: doomgeneric (page 7 of 12)
Previous: [KB_doomgeneric_p6.md](KB_doomgeneric_p6.md)

## progs/doomgeneric/net_query.h
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it...
- Layer: data_access
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
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it...
- Layer: utility
- Language: h
- Symbols:
  - `net_sdl_module` (variable, line 23) `extern net_module_t net_sdl_module;`
  - `NET_SDL_H` (macro, line 19) `#define NET_SDL_H`
- Depends on: `progs/doomgeneric/net_defs.h`
- Imported by: `progs/doomgeneric/d_loop.c`

## progs/doomgeneric/net_server.h
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it...
- Layer: utility
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
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
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
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
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
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
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
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
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
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
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
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `__P_INTER__` (macro, line 21) `#define __P_INTER__`
- Imported by: `progs/doomgeneric/p_inter.c`, `progs/doomgeneric/st_stuff.c`

## progs/doomgeneric/p_lights.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
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
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
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
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
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


Next: [KB_doomgeneric_p8.md](KB_doomgeneric_p8.md)
