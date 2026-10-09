# API (page 12 of 19)
Previous: [API_p11.md](API_p11.md)

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

## progs/doomgeneric/net_query.h
Depends on: `progs/doomgeneric/net_defs.h`
Imported by: `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/d_main.c`
- `NET_StartLANQuery` (function) `progs/doomgeneric/net_query.h:28` `extern int NET_StartLANQuery(void);`
- `NET_StartMasterQuery` (function) `progs/doomgeneric/net_query.h:29` `extern int NET_StartMasterQuery(void);`
- `NET_LANQuery` (function) `progs/doomgeneric/net_query.h:31` `extern void NET_LANQuery(void);`
- `NET_MasterQuery` (function) `progs/doomgeneric/net_query.h:32` `extern void NET_MasterQuery(void);`
- `NET_QueryAddress` (function) `progs/doomgeneric/net_query.h:33` `extern void NET_QueryAddress(char *addr);`
- `NET_FindLANServer` (function) `progs/doomgeneric/net_query.h:34` `extern net_addr_t *NET_FindLANServer(void);`
- `NET_Query_Poll` (function) `progs/doomgeneric/net_query.h:36` `extern int NET_Query_Poll(net_query_callback_t callback, void *user_data);`
- `NET_Query_ResolveMaster` (function) `progs/doomgeneric/net_query.h:38` `extern net_addr_t *NET_Query_ResolveMaster(net_context_t *context);`
- `NET_Query_AddToMaster` (function) `progs/doomgeneric/net_query.h:39` `extern void NET_Query_AddToMaster(net_addr_t *master_addr);`
- `NET_Query_CheckAddedToMaster` (function) `progs/doomgeneric/net_query.h:40` `extern boolean NET_Query_CheckAddedToMaster(boolean *result);`
- `NET_Query_MasterResponse` (function) `progs/doomgeneric/net_query.h:41` `extern void NET_Query_MasterResponse(net_packet_t *packet);`

## progs/doomgeneric/net_server.h
Imported by: `progs/doomgeneric/d_loop.c`
- `NET_SV_Init` (function) `progs/doomgeneric/net_server.h:22` `void NET_SV_Init(void);`
- `NET_SV_Run` (function) `progs/doomgeneric/net_server.h:26` `void NET_SV_Run(void);`
- `NET_SV_Shutdown` (function) `progs/doomgeneric/net_server.h:31` `void NET_SV_Shutdown(void);`
- `NET_SV_AddModule` (function) `progs/doomgeneric/net_server.h:35` `void NET_SV_AddModule(net_module_t *module);`
- `NET_SV_RegisterWithMaster` (function) `progs/doomgeneric/net_server.h:39` `void NET_SV_RegisterWithMaster(void);`

## progs/doomgeneric/p_ceilng.c
Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/z_zone.h`
- `T_MoveCeiling` (function) `progs/doomgeneric/p_ceilng.c:45` `void T_MoveCeiling (ceiling_t* ceiling)`
- `EV_DoCeiling` (function) `progs/doomgeneric/p_ceilng.c:161` `int
EV_DoCeiling
( line_t*	line,
  ceiling_e	type )`
- `P_AddActiveCeiling` (function) `progs/doomgeneric/p_ceilng.c:240` `void P_AddActiveCeiling(ceiling_t* c)` -- Add an active ceiling
- `P_RemoveActiveCeiling` (function) `progs/doomgeneric/p_ceilng.c:259` `void P_RemoveActiveCeiling(ceiling_t* c)` -- Remove a ceiling's thinker
- `P_ActivateInStasisCeiling` (function) `progs/doomgeneric/p_ceilng.c:280` `void P_ActivateInStasisCeiling(line_t* line)` -- Restart a ceiling that's in-stasis
- `EV_CeilingCrushStop` (function) `progs/doomgeneric/p_ceilng.c:303` `int	EV_CeilingCrushStop(line_t	*line)` -- EV_CeilingCrushStop Stop a ceiling from crushing!

## progs/doomgeneric/p_doors.c
Depends on: `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/dstrings.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/z_zone.h`
- `T_VerticalDoor` (function) `progs/doomgeneric/p_doors.c:57` `void T_VerticalDoor (vldoor_t* door)` -- T_VerticalDoor
- `EV_DoLockedDoor` (function) `progs/doomgeneric/p_doors.c:195` `int
EV_DoLockedDoor
( line_t*	line,
  vldoor_e	type,
  mobj_t*	thing )`
- `EV_DoDoor` (function) `progs/doomgeneric/p_doors.c:252` `int
EV_DoDoor
( line_t*	line,
  vldoor_e	type )`
- `EV_VerticalDoor` (function) `progs/doomgeneric/p_doors.c:337` `void
EV_VerticalDoor
( line_t*	line,
  mobj_t*	thing )`
- `P_SpawnDoorCloseIn30` (function) `progs/doomgeneric/p_doors.c:519` `void P_SpawnDoorCloseIn30 (sector_t* sec)` -- Spawn a door that closes after 30 seconds
- `P_SpawnDoorRaiseIn5Mins` (function) `progs/doomgeneric/p_doors.c:542` `void
P_SpawnDoorRaiseIn5Mins
( sector_t*	sec,
  int		secnum )`
- `P_InitSlidingDoorFrames` (function) `progs/doomgeneric/p_doors.c:580` `void P_InitSlidingDoorFrames(void)`
- `P_FindSlidingDoorType` (function) `progs/doomgeneric/p_doors.c:624` `int P_FindSlidingDoorType(line_t*	line)` -- Return index into "slideFrames" array for which door type to use
- `T_SlidingDoor` (function) `progs/doomgeneric/p_doors.c:639` `void T_SlidingDoor (slidedoor_t*	door)`
- `EV_SlidingDoor` (function) `progs/doomgeneric/p_doors.c:727` `void
EV_SlidingDoor
( line_t*	line,
  mobj_t*	thing )`

## progs/doomgeneric/p_enemy.c
Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`
- `P_RecursiveSound` (function) `progs/doomgeneric/p_enemy.c:99` `void
P_RecursiveSound
( sector_t*	sec,
  int		soundblocks )`
- `P_NoiseAlert` (function) `progs/doomgeneric/p_enemy.c:152` `void
P_NoiseAlert
( mobj_t*	target,
  mobj_t*	emmiter )`
- `P_CheckMeleeRange` (function) `progs/doomgeneric/p_enemy.c:167` `boolean P_CheckMeleeRange (mobj_t*	actor)` -- P_CheckMeleeRange
- `P_CheckMissileRange` (function) `progs/doomgeneric/p_enemy.c:190` `boolean P_CheckMissileRange (mobj_t* actor)` -- P_CheckMissileRange
- `P_Move` (function) `progs/doomgeneric/p_enemy.c:260` `boolean P_Move (mobj_t*	actor)`
- `P_TryWalk` (function) `progs/doomgeneric/p_enemy.c:337` `boolean P_TryWalk (mobj_t* actor)` -- TryWalk Attempts to move actor on in its current (ob->moveangle) direction.
- `P_NewChaseDir` (function) `progs/doomgeneric/p_enemy.c:351` `void P_NewChaseDir (mobj_t*	actor)`
- `P_LookForPlayers` (function) `progs/doomgeneric/p_enemy.c:487` `boolean
P_LookForPlayers
( mobj_t*	actor,
  boolean	allaround )`
- `A_KeenDie` (function) `progs/doomgeneric/p_enemy.c:551` `void A_KeenDie (mobj_t* mo)` -- A_KeenDie DOOM II special, map 32.
- `A_Look` (function) `progs/doomgeneric/p_enemy.c:589` `void A_Look (mobj_t* actor)` -- A_Look Stay in state until a player is sighted.
- `A_Chase` (function) `progs/doomgeneric/p_enemy.c:657` `void A_Chase (mobj_t*	actor)` -- A_Chase Actor has a melee attack, so it tries to close as fast as possible
- `A_FaceTarget` (function) `progs/doomgeneric/p_enemy.c:767` `void A_FaceTarget (mobj_t* actor)` -- A_FaceTarget
- `A_PosAttack` (function) `progs/doomgeneric/p_enemy.c:787` `void A_PosAttack (mobj_t* actor)` -- A_PosAttack
- `A_SPosAttack` (function) `progs/doomgeneric/p_enemy.c:806` `void A_SPosAttack (mobj_t* actor)`
- `A_CPosAttack` (function) `progs/doomgeneric/p_enemy.c:830` `void A_CPosAttack (mobj_t* actor)`
- `A_CPosRefire` (function) `progs/doomgeneric/p_enemy.c:850` `void A_CPosRefire (mobj_t* actor)`
- `A_SpidRefire` (function) `progs/doomgeneric/p_enemy.c:867` `void A_SpidRefire (mobj_t* actor)`
- `A_BspiAttack` (function) `progs/doomgeneric/p_enemy.c:883` `void A_BspiAttack (mobj_t *actor)`
- `A_TroopAttack` (function) `progs/doomgeneric/p_enemy.c:898` `void A_TroopAttack (mobj_t* actor)` -- A_TroopAttack
- `A_SargAttack` (function) `progs/doomgeneric/p_enemy.c:920` `void A_SargAttack (mobj_t* actor)`
- `A_HeadAttack` (function) `progs/doomgeneric/p_enemy.c:935` `void A_HeadAttack (mobj_t* actor)`
- `A_CyberAttack` (function) `progs/doomgeneric/p_enemy.c:954` `void A_CyberAttack (mobj_t* actor)`
- `A_BruisAttack` (function) `progs/doomgeneric/p_enemy.c:964` `void A_BruisAttack (mobj_t* actor)`
- `A_SkelMissile` (function) `progs/doomgeneric/p_enemy.c:987` `void A_SkelMissile (mobj_t* actor)` -- A_SkelMissile
- `A_Tracer` (function) `progs/doomgeneric/p_enemy.c:1006` `void A_Tracer (mobj_t* actor)`
- `A_SkelWhoosh` (function) `progs/doomgeneric/p_enemy.c:1078` `void A_SkelWhoosh (mobj_t*	actor)`
- `A_SkelFist` (function) `progs/doomgeneric/p_enemy.c:1086` `void A_SkelFist (mobj_t*	actor)`
- `PIT_VileCheck` (function) `progs/doomgeneric/p_enemy.c:1114` `boolean PIT_VileCheck (mobj_t*	thing)`
- `A_VileChase` (function) `progs/doomgeneric/p_enemy.c:1152` `void A_VileChase (mobj_t* actor)` -- A_VileChase Check for ressurecting a body
- `A_VileStart` (function) `progs/doomgeneric/p_enemy.c:1218` `void A_VileStart (mobj_t* actor)` -- A_VileStart
- `A_StartFire` (function) `progs/doomgeneric/p_enemy.c:1230` `void A_StartFire (mobj_t* actor)`
- `A_FireCrackle` (function) `progs/doomgeneric/p_enemy.c:1236` `void A_FireCrackle (mobj_t* actor)`
- `A_Fire` (function) `progs/doomgeneric/p_enemy.c:1242` `void A_Fire (mobj_t* actor)`
- `A_VileTarget` (function) `progs/doomgeneric/p_enemy.c:1273` `void A_VileTarget (mobj_t*	actor)` -- A_VileTarget Spawn the hellfire
- `A_VileAttack` (function) `progs/doomgeneric/p_enemy.c:1298` `void A_VileAttack (mobj_t* actor)` -- A_VileAttack
- `A_FatRaise` (function) `progs/doomgeneric/p_enemy.c:1339` `void A_FatRaise (mobj_t *actor)`
- `A_FatAttack1` (function) `progs/doomgeneric/p_enemy.c:1346` `void A_FatAttack1 (mobj_t* actor)`
- `A_FatAttack2` (function) `progs/doomgeneric/p_enemy.c:1366` `void A_FatAttack2 (mobj_t* actor)`
- `A_FatAttack3` (function) `progs/doomgeneric/p_enemy.c:1385` `void A_FatAttack3 (mobj_t*	actor)`
- `A_SkullAttack` (function) `progs/doomgeneric/p_enemy.c:1415` `void A_SkullAttack (mobj_t* actor)`
- `A_PainShootSkull` (function) `progs/doomgeneric/p_enemy.c:1446` `void
A_PainShootSkull
( mobj_t*	actor,
  angle_t	angle )`
- `A_PainAttack` (function) `progs/doomgeneric/p_enemy.c:1508` `void A_PainAttack (mobj_t* actor)` -- A_PainAttack Spawn a lost soul and launch it at the target
- `A_PainDie` (function) `progs/doomgeneric/p_enemy.c:1518` `void A_PainDie (mobj_t* actor)`
- `A_Scream` (function) `progs/doomgeneric/p_enemy.c:1531` `void A_Scream (mobj_t* actor)`
- `A_XScream` (function) `progs/doomgeneric/p_enemy.c:1568` `void A_XScream (mobj_t* actor)`
- `A_Pain` (function) `progs/doomgeneric/p_enemy.c:1573` `void A_Pain (mobj_t* actor)`
- `A_Fall` (function) `progs/doomgeneric/p_enemy.c:1581` `void A_Fall (mobj_t *actor)`
- `A_Explode` (function) `progs/doomgeneric/p_enemy.c:1594` `void A_Explode (mobj_t* thingy)` -- A_Explode
- `CheckBossEnd` (function) `progs/doomgeneric/p_enemy.c:1605` `static boolean CheckBossEnd(mobjtype_t motype)`
- `A_BossDeath` (function) `progs/doomgeneric/p_enemy.c:1656` `void A_BossDeath (mobj_t* mo)` -- A_BossDeath Possibly trigger special effects if on first boss level
- `A_Hoof` (function) `progs/doomgeneric/p_enemy.c:1757` `void A_Hoof (mobj_t* mo)`
- `A_Metal` (function) `progs/doomgeneric/p_enemy.c:1763` `void A_Metal (mobj_t* mo)`
- `A_BabyMetal` (function) `progs/doomgeneric/p_enemy.c:1769` `void A_BabyMetal (mobj_t* mo)`
- `A_OpenShotgun2` (function) `progs/doomgeneric/p_enemy.c:1776` `void
A_OpenShotgun2
( player_t*	player,
  pspdef_t*	psp )`
- `A_LoadShotgun2` (function) `progs/doomgeneric/p_enemy.c:1784` `void
A_LoadShotgun2
( player_t*	player,
  pspdef_t*	psp )`
- `A_ReFire` (function) `progs/doomgeneric/p_enemy.c:1792` `void A_ReFire ( player_t* player, pspdef_t* psp );`
- `A_CloseShotgun2` (function) `progs/doomgeneric/p_enemy.c:1797` `void
A_CloseShotgun2
( player_t*	player,
  pspdef_t*	psp )`
- `A_BrainAwake` (function) `progs/doomgeneric/p_enemy.c:1811` `void A_BrainAwake (mobj_t* mo)`
- `A_BrainPain` (function) `progs/doomgeneric/p_enemy.c:1841` `void A_BrainPain (mobj_t*	mo)`
- `A_BrainScream` (function) `progs/doomgeneric/p_enemy.c:1847` `void A_BrainScream (mobj_t*	mo)`
- `A_BrainExplode` (function) `progs/doomgeneric/p_enemy.c:1873` `void A_BrainExplode (mobj_t* mo)`
- `A_BrainDie` (function) `progs/doomgeneric/p_enemy.c:1894` `void A_BrainDie (mobj_t*	mo)`
- `A_BrainSpit` (function) `progs/doomgeneric/p_enemy.c:1899` `void A_BrainSpit (mobj_t*	mo)`
- `A_SpawnSound` (function) `progs/doomgeneric/p_enemy.c:1928` `void A_SpawnSound (mobj_t* mo)` -- travelling cube sound
- `A_SpawnFly` (function) `progs/doomgeneric/p_enemy.c:1934` `void A_SpawnFly (mobj_t* mo)`
- `A_PlayerScream` (function) `progs/doomgeneric/p_enemy.c:1992` `void A_PlayerScream (mobj_t* mo)`

## progs/doomgeneric/p_floor.c
Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/z_zone.h`
- `T_MovePlane` (function) `progs/doomgeneric/p_floor.c:42` `result_e
T_MovePlane
( sector_t*	sector,
  fixed_t	speed,
  fixed_t	dest,
  boolean	crush,
  int	...`
- `T_MoveFloor` (function) `progs/doomgeneric/p_floor.c:202` `void T_MoveFloor(floormove_t* floor)` -- MOVE A FLOOR TO IT'S DESTINATION (UP OR DOWN)
- `EV_DoFloor` (function) `progs/doomgeneric/p_floor.c:251` `int
EV_DoFloor
( line_t*	line,
  floor_e	floortype )`
- `EV_BuildStairs` (function) `progs/doomgeneric/p_floor.c:444` `int
EV_BuildStairs
( line_t*	line,
  stair_e	type )`

## progs/doomgeneric/p_inter.c
Depends on: `progs/doomgeneric/am_map.h`, `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/deh_misc.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/dstrings.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/p_inter.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`
- `P_GiveAmmo` (function) `progs/doomgeneric/p_inter.c:66` `boolean
P_GiveAmmo
( player_t*	player,
  ammotype_t	ammo,
  int		num )`
- `P_GiveWeapon` (function) `progs/doomgeneric/p_inter.c:160` `boolean
P_GiveWeapon
( player_t*	player,
  weapontype_t	weapon,
  boolean	dropped )`
- `P_GiveBody` (function) `progs/doomgeneric/p_inter.c:223` `boolean
P_GiveBody
( player_t*	player,
  int		num )`
- `P_GiveArmor` (function) `progs/doomgeneric/p_inter.c:246` `boolean
P_GiveArmor
( player_t*	player,
  int		armortype )`
- `P_GiveCard` (function) `progs/doomgeneric/p_inter.c:268` `void
P_GiveCard
( player_t*	player,
  card_t	card )`
- `P_GivePower` (function) `progs/doomgeneric/p_inter.c:284` `boolean
P_GivePower
( player_t*	player,
  int /*powertype_t*/	power )`
- `P_TouchSpecialThing` (function) `progs/doomgeneric/p_inter.c:333` `void
P_TouchSpecialThing
( mobj_t*	special,
  mobj_t*	toucher )`
- `P_KillMobj` (function) `progs/doomgeneric/p_inter.c:666` `void
P_KillMobj
( mobj_t*	source,
  mobj_t*	target )`
- `P_DamageMobj` (function) `progs/doomgeneric/p_inter.c:779` `void
P_DamageMobj
( mobj_t*	target,
  mobj_t*	inflictor,
  mobj_t*	source,
  int 		damage )`

## progs/doomgeneric/p_lights.c
Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/z_zone.h`
- `T_FireFlicker` (function) `progs/doomgeneric/p_lights.c:39` `void T_FireFlicker (fireflicker_t* flick)` -- T_FireFlicker
- `P_SpawnFireFlicker` (function) `progs/doomgeneric/p_lights.c:61` `void P_SpawnFireFlicker (sector_t*	sector)` -- P_SpawnFireFlicker
- `T_LightFlash` (function) `progs/doomgeneric/p_lights.c:91` `void T_LightFlash (lightflash_t* flash)` -- T_LightFlash Do flashing lights.
- `P_SpawnLightFlash` (function) `progs/doomgeneric/p_lights.c:117` `void P_SpawnLightFlash (sector_t*	sector)` -- P_SpawnLightFlash After the map has been loaded, scan each sector for specials that spawn thinkers
- `T_StrobeFlash` (function) `progs/doomgeneric/p_lights.c:148` `void T_StrobeFlash (strobe_t*		flash)` -- T_StrobeFlash
- `P_SpawnStrobeFlash` (function) `progs/doomgeneric/p_lights.c:174` `void
P_SpawnStrobeFlash
( sector_t*	sector,
  int		fastOrSlow,
  int		inSync )`
- `EV_StartLightStrobing` (function) `progs/doomgeneric/p_lights.c:208` `void EV_StartLightStrobing(line_t*	line)` -- Start strobing lights (usually from a trigger)
- `EV_TurnTagLightsOff` (function) `progs/doomgeneric/p_lights.c:229` `void EV_TurnTagLightsOff(line_t* line)` -- TURN LINE'S TAG LIGHTS OFF
- `EV_LightTurnOn` (function) `progs/doomgeneric/p_lights.c:264` `void
EV_LightTurnOn
( line_t*	line,
  int		bright )`
- `T_Glow` (function) `progs/doomgeneric/p_lights.c:307` `void T_Glow(glow_t*	g)`
- `P_SpawnGlowingLight` (function) `progs/doomgeneric/p_lights.c:334` `void P_SpawnGlowingLight(sector_t*	sector)`

## progs/doomgeneric/p_local.h
Depends on: `progs/doomgeneric/p_spec.h`, `progs/doomgeneric/r_local.h`
Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/p_ceilng.c`, `progs/doomgeneric/p_doors.c`, `progs/doomgeneric/p_enemy.c`, `progs/doomgeneric/p_floor.c`, `progs/doomgeneric/p_inter.c`, `progs/doomgeneric/p_lights.c`, `progs/doomgeneric/p_map.c`, `progs/doomgeneric/p_maputl.c`, `progs/doomgeneric/p_mobj.c`, `progs/doomgeneric/p_plats.c`, `progs/doomgeneric/p_pspr.c`, `progs/doomgeneric/p_saveg.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/p_sight.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/p_switch.c`, `progs/doomgeneric/p_telept.c`, `progs/doomgeneric/p_tick.c`, `progs/doomgeneric/p_user.c`, `progs/doomgeneric/r_data.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/st_stuff.c`
- `P_InitThinkers` (function) `progs/doomgeneric/p_local.h:70` `void P_InitThinkers (void);`
- `P_AddThinker` (function) `progs/doomgeneric/p_local.h:71` `void P_AddThinker (thinker_t* thinker);`
- `P_RemoveThinker` (function) `progs/doomgeneric/p_local.h:72` `void P_RemoveThinker (thinker_t* thinker);`
- `P_SetupPsprites` (function) `progs/doomgeneric/p_local.h:78` `void P_SetupPsprites (player_t* curplayer);` -- P_PSPR
- `P_MovePsprites` (function) `progs/doomgeneric/p_local.h:79` `void P_MovePsprites (player_t* curplayer);`
- `P_DropWeapon` (function) `progs/doomgeneric/p_local.h:80` `void P_DropWeapon (player_t* player);`
- `P_PlayerThink` (function) `progs/doomgeneric/p_local.h:86` `void P_PlayerThink (player_t* player);` -- P_USER
- `P_RespawnSpecials` (function) `progs/doomgeneric/p_local.h:104` `void P_RespawnSpecials (void);`
- `P_SpawnMobj` (function) `progs/doomgeneric/p_local.h:107` `mobj_t* P_SpawnMobj ( fixed_t x, fixed_t y, fixed_t z, mobjtype_t type );`
- `P_RemoveMobj` (function) `progs/doomgeneric/p_local.h:113` `void P_RemoveMobj (mobj_t* th);`
- `P_SubstNullMobj` (function) `progs/doomgeneric/p_local.h:114` `mobj_t* P_SubstNullMobj (mobj_t* th);`
- `P_MobjThinker` (function) `progs/doomgeneric/p_local.h:116` `void P_MobjThinker (mobj_t* mobj);`
- `P_SpawnPuff` (function) `progs/doomgeneric/p_local.h:118` `void P_SpawnPuff (fixed_t x, fixed_t y, fixed_t z);`
- `P_SpawnBlood` (function) `progs/doomgeneric/p_local.h:119` `void P_SpawnBlood (fixed_t x, fixed_t y, fixed_t z, int damage);`
- `P_SpawnMissile` (function) `progs/doomgeneric/p_local.h:120` `mobj_t* P_SpawnMissile (mobj_t* source, mobj_t* dest, mobjtype_t type);`
- `P_SpawnPlayerMissile` (function) `progs/doomgeneric/p_local.h:121` `void P_SpawnPlayerMissile (mobj_t* source, mobjtype_t type);`
- `P_NoiseAlert` (function) `progs/doomgeneric/p_local.h:127` `void P_NoiseAlert (mobj_t* target, mobj_t* emmiter);` -- P_ENEMY
- `P_AproxDistance` (function) `progs/doomgeneric/p_local.h:162` `fixed_t P_AproxDistance (fixed_t dx, fixed_t dy);`
- `P_PointOnLineSide` (function) `progs/doomgeneric/p_local.h:163` `int P_PointOnLineSide (fixed_t x, fixed_t y, line_t* line);`
- `P_PointOnDivlineSide` (function) `progs/doomgeneric/p_local.h:164` `int P_PointOnDivlineSide (fixed_t x, fixed_t y, divline_t* line);`
- `P_MakeDivline` (function) `progs/doomgeneric/p_local.h:165` `void P_MakeDivline (line_t* li, divline_t* dl);`
- `P_InterceptVector` (function) `progs/doomgeneric/p_local.h:166` `fixed_t P_InterceptVector (divline_t* v2, divline_t* v1);`
- `P_BoxOnLineSide` (function) `progs/doomgeneric/p_local.h:167` `int P_BoxOnLineSide (fixed_t* tmbox, line_t* ld);`
- `P_LineOpening` (function) `progs/doomgeneric/p_local.h:174` `void P_LineOpening (line_t* linedef);`
- `P_UnsetThingPosition` (function) `progs/doomgeneric/p_local.h:194` `void P_UnsetThingPosition (mobj_t* thing);`
- `P_SetThingPosition` (function) `progs/doomgeneric/p_local.h:195` `void P_SetThingPosition (mobj_t* thing);`
- `P_SlideMove` (function) `progs/doomgeneric/p_local.h:228` `void P_SlideMove (mobj_t* mo);`
- `P_UseLines` (function) `progs/doomgeneric/p_local.h:230` `void P_UseLines (player_t* player);`
- `P_AimLineAttack` (function) `progs/doomgeneric/p_local.h:237` `fixed_t P_AimLineAttack ( mobj_t* t1, angle_t angle, fixed_t distance );`
- `P_LineAttack` (function) `progs/doomgeneric/p_local.h:243` `void P_LineAttack ( mobj_t* t1, angle_t angle, fixed_t distance, fixed_t slope, int damage );`
- `P_RadiusAttack` (function) `progs/doomgeneric/p_local.h:251` `void P_RadiusAttack ( mobj_t* spot, mobj_t* source, int damage );`
- `P_TouchSpecialThing` (function) `progs/doomgeneric/p_local.h:279` `void P_TouchSpecialThing ( mobj_t* special, mobj_t* toucher );`
- `P_DamageMobj` (function) `progs/doomgeneric/p_local.h:284` `void P_DamageMobj ( mobj_t* target, mobj_t* inflictor, mobj_t* source, int damage );`

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


Next: [API_p13.md](API_p13.md)
