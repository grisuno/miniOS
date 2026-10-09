# Symbols (page 16 of 26)
Previous: [SYMBOLS_p15.md](SYMBOLS_p15.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `net_ticdiff_t` | struct | `progs/doomgeneric/net_defs.h:202` | `` |
| `net_waitdata_t` | struct | `progs/doomgeneric/net_defs.h:233` | `` |
| `NET_GUI_H` | macro | `progs/doomgeneric/net_gui.h:22` | `#define NET_GUI_H` |
| `NET_WaitForLaunch` | function | `progs/doomgeneric/net_gui.h:26` | `extern void NET_WaitForLaunch(void);` |
| `NET_AddModule` | function | `progs/doomgeneric/net_io.h:26` | `void NET_AddModule(net_context_t *context, net_module_t *module);` |
| `NET_AddrToString` | function | `progs/doomgeneric/net_io.h:31` | `char *NET_AddrToString(net_addr_t *addr);` |
| `NET_FreeAddress` | function | `progs/doomgeneric/net_io.h:32` | `void NET_FreeAddress(net_addr_t *addr);` |
| `NET_IO_H` | macro | `progs/doomgeneric/net_io.h:19` | `#define NET_IO_H` |
| `NET_NewContext` | function | `progs/doomgeneric/net_io.h:25` | `net_context_t *NET_NewContext(void);` |
| `NET_ResolveAddress` | function | `progs/doomgeneric/net_io.h:33` | `net_addr_t *NET_ResolveAddress(net_context_t *context, char *address);` |
| `NET_SendBroadcast` | function | `progs/doomgeneric/net_io.h:28` | `void NET_SendBroadcast(net_context_t *context, net_packet_t *packet);` |
| `NET_SendPacket` | function | `progs/doomgeneric/net_io.h:27` | `void NET_SendPacket(net_addr_t *addr, net_packet_t *packet);` |
| `net_broadcast_addr` | variable | `progs/doomgeneric/net_io.h:23` | `extern net_addr_t net_broadcast_addr;` |
| `NET_LOOP_H` | macro | `progs/doomgeneric/net_loop.h:19` | `#define NET_LOOP_H` |
| `net_loop_client_module` | variable | `progs/doomgeneric/net_loop.h:23` | `extern net_module_t net_loop_client_module;` |
| `net_loop_server_module` | variable | `progs/doomgeneric/net_loop.h:24` | `extern net_module_t net_loop_server_module;` |
| `NET_FreePacket` | function | `progs/doomgeneric/net_packet.h:25` | `void NET_FreePacket(net_packet_t *packet);` |
| `NET_NewPacket` | function | `progs/doomgeneric/net_packet.h:23` | `net_packet_t *NET_NewPacket(int initial_size);` |
| `NET_PACKET_H` | macro | `progs/doomgeneric/net_packet.h:19` | `#define NET_PACKET_H` |
| `NET_PacketDup` | function | `progs/doomgeneric/net_packet.h:24` | `net_packet_t *NET_PacketDup(net_packet_t *packet);` |
| `NET_ReadString` | function | `progs/doomgeneric/net_packet.h:35` | `char *NET_ReadString(net_packet_t *packet);` |
| `NET_WriteInt16` | function | `progs/doomgeneric/net_packet.h:38` | `void NET_WriteInt16(net_packet_t *packet, unsigned int i);` |
| `NET_WriteInt32` | function | `progs/doomgeneric/net_packet.h:39` | `void NET_WriteInt32(net_packet_t *packet, unsigned int i);` |
| `NET_WriteInt8` | function | `progs/doomgeneric/net_packet.h:37` | `void NET_WriteInt8(net_packet_t *packet, unsigned int i);` |
| `NET_WriteString` | function | `progs/doomgeneric/net_packet.h:41` | `void NET_WriteString(net_packet_t *packet, char *string);` |
| `NET_FindLANServer` | function | `progs/doomgeneric/net_query.h:34` | `extern net_addr_t *NET_FindLANServer(void);` |
| `NET_LANQuery` | function | `progs/doomgeneric/net_query.h:31` | `extern void NET_LANQuery(void);` |
| `NET_MasterQuery` | function | `progs/doomgeneric/net_query.h:32` | `extern void NET_MasterQuery(void);` |
| `NET_QUERY_H` | macro | `progs/doomgeneric/net_query.h:19` | `#define NET_QUERY_H` |
| `NET_QueryAddress` | function | `progs/doomgeneric/net_query.h:33` | `extern void NET_QueryAddress(char *addr);` |
| `NET_Query_AddToMaster` | function | `progs/doomgeneric/net_query.h:39` | `extern void NET_Query_AddToMaster(net_addr_t *master_addr);` |
| `NET_Query_CheckAddedToMaster` | function | `progs/doomgeneric/net_query.h:40` | `extern boolean NET_Query_CheckAddedToMaster(boolean *result);` |
| `NET_Query_MasterResponse` | function | `progs/doomgeneric/net_query.h:41` | `extern void NET_Query_MasterResponse(net_packet_t *packet);` |
| `NET_Query_Poll` | function | `progs/doomgeneric/net_query.h:36` | `extern int NET_Query_Poll(net_query_callback_t callback, void *user_data);` |
| `NET_Query_ResolveMaster` | function | `progs/doomgeneric/net_query.h:38` | `extern net_addr_t *NET_Query_ResolveMaster(net_context_t *context);` |
| `NET_StartLANQuery` | function | `progs/doomgeneric/net_query.h:28` | `extern int NET_StartLANQuery(void);` |
| `NET_StartMasterQuery` | function | `progs/doomgeneric/net_query.h:29` | `extern int NET_StartMasterQuery(void);` |
| `NET_SDL_H` | macro | `progs/doomgeneric/net_sdl.h:19` | `#define NET_SDL_H` |
| `net_sdl_module` | variable | `progs/doomgeneric/net_sdl.h:23` | `extern net_module_t net_sdl_module;` |
| `NET_SERVER_H` | macro | `progs/doomgeneric/net_server.h:18` | `#define NET_SERVER_H` |
| `NET_SV_AddModule` | function | `progs/doomgeneric/net_server.h:35` | `void NET_SV_AddModule(net_module_t *module);` |
| `NET_SV_Init` | function | `progs/doomgeneric/net_server.h:22` | `void NET_SV_Init(void);` |
| `NET_SV_RegisterWithMaster` | function | `progs/doomgeneric/net_server.h:39` | `void NET_SV_RegisterWithMaster(void);` |
| `NET_SV_Run` | function | `progs/doomgeneric/net_server.h:26` | `void NET_SV_Run(void);` |
| `NET_SV_Shutdown` | function | `progs/doomgeneric/net_server.h:31` | `void NET_SV_Shutdown(void);` |
| `EV_CeilingCrushStop` | function | `progs/doomgeneric/p_ceilng.c:303` | `int	EV_CeilingCrushStop(line_t	*line)` |
| `EV_DoCeiling` | function | `progs/doomgeneric/p_ceilng.c:161` | `int EV_DoCeiling ( line_t*	line,   ceiling_e	type )` |
| `P_ActivateInStasisCeiling` | function | `progs/doomgeneric/p_ceilng.c:280` | `void P_ActivateInStasisCeiling(line_t* line)` |
| `P_AddActiveCeiling` | function | `progs/doomgeneric/p_ceilng.c:240` | `void P_AddActiveCeiling(ceiling_t* c)` |
| `P_RemoveActiveCeiling` | function | `progs/doomgeneric/p_ceilng.c:259` | `void P_RemoveActiveCeiling(ceiling_t* c)` |
| `T_MoveCeiling` | function | `progs/doomgeneric/p_ceilng.c:45` | `void T_MoveCeiling (ceiling_t* ceiling)` |
| `EV_DoDoor` | function | `progs/doomgeneric/p_doors.c:252` | `int EV_DoDoor ( line_t*	line,   vldoor_e	type )` |
| `EV_DoLockedDoor` | function | `progs/doomgeneric/p_doors.c:195` | `int EV_DoLockedDoor ( line_t*	line,   vldoor_e	type,   mobj_t*	thing )` |
| `EV_SlidingDoor` | function | `progs/doomgeneric/p_doors.c:727` | `void EV_SlidingDoor ( line_t*	line,   mobj_t*	thing )` |
| `EV_VerticalDoor` | function | `progs/doomgeneric/p_doors.c:337` | `void EV_VerticalDoor ( line_t*	line,   mobj_t*	thing )` |
| `P_FindSlidingDoorType` | function | `progs/doomgeneric/p_doors.c:624` | `int P_FindSlidingDoorType(line_t*	line)` |
| `P_InitSlidingDoorFrames` | function | `progs/doomgeneric/p_doors.c:580` | `void P_InitSlidingDoorFrames(void)` |
| `P_SpawnDoorCloseIn30` | function | `progs/doomgeneric/p_doors.c:519` | `void P_SpawnDoorCloseIn30 (sector_t* sec)` |
| `P_SpawnDoorRaiseIn5Mins` | function | `progs/doomgeneric/p_doors.c:542` | `void P_SpawnDoorRaiseIn5Mins ( sector_t*	sec,   int		secnum )` |
| `T_SlidingDoor` | function | `progs/doomgeneric/p_doors.c:639` | `void T_SlidingDoor (slidedoor_t*	door)` |
| `T_VerticalDoor` | function | `progs/doomgeneric/p_doors.c:57` | `void T_VerticalDoor (vldoor_t* door)` |
| `A_BabyMetal` | function | `progs/doomgeneric/p_enemy.c:1769` | `void A_BabyMetal (mobj_t* mo)` |
| `A_BossDeath` | function | `progs/doomgeneric/p_enemy.c:1656` | `void A_BossDeath (mobj_t* mo)` |
| `A_BrainAwake` | function | `progs/doomgeneric/p_enemy.c:1811` | `void A_BrainAwake (mobj_t* mo)` |
| `A_BrainDie` | function | `progs/doomgeneric/p_enemy.c:1894` | `void A_BrainDie (mobj_t*	mo)` |
| `A_BrainExplode` | function | `progs/doomgeneric/p_enemy.c:1873` | `void A_BrainExplode (mobj_t* mo)` |
| `A_BrainPain` | function | `progs/doomgeneric/p_enemy.c:1841` | `void A_BrainPain (mobj_t*	mo)` |
| `A_BrainScream` | function | `progs/doomgeneric/p_enemy.c:1847` | `void A_BrainScream (mobj_t*	mo)` |
| `A_BrainSpit` | function | `progs/doomgeneric/p_enemy.c:1899` | `void A_BrainSpit (mobj_t*	mo)` |
| `A_BruisAttack` | function | `progs/doomgeneric/p_enemy.c:964` | `void A_BruisAttack (mobj_t* actor)` |
| `A_BspiAttack` | function | `progs/doomgeneric/p_enemy.c:883` | `void A_BspiAttack (mobj_t *actor)` |
| `A_CPosAttack` | function | `progs/doomgeneric/p_enemy.c:830` | `void A_CPosAttack (mobj_t* actor)` |
| `A_CPosRefire` | function | `progs/doomgeneric/p_enemy.c:850` | `void A_CPosRefire (mobj_t* actor)` |
| `A_Chase` | function | `progs/doomgeneric/p_enemy.c:657` | `void A_Chase (mobj_t*	actor)` |
| `A_CloseShotgun2` | function | `progs/doomgeneric/p_enemy.c:1797` | `void A_CloseShotgun2 ( player_t*	player,   pspdef_t*	psp )` |
| `A_CyberAttack` | function | `progs/doomgeneric/p_enemy.c:954` | `void A_CyberAttack (mobj_t* actor)` |
| `A_Explode` | function | `progs/doomgeneric/p_enemy.c:1594` | `void A_Explode (mobj_t* thingy)` |
| `A_FaceTarget` | function | `progs/doomgeneric/p_enemy.c:767` | `void A_FaceTarget (mobj_t* actor)` |
| `A_Fall` | function | `progs/doomgeneric/p_enemy.c:1581` | `void A_Fall (mobj_t *actor)` |
| `A_FatAttack1` | function | `progs/doomgeneric/p_enemy.c:1346` | `void A_FatAttack1 (mobj_t* actor)` |
| `A_FatAttack2` | function | `progs/doomgeneric/p_enemy.c:1366` | `void A_FatAttack2 (mobj_t* actor)` |
| `A_FatAttack3` | function | `progs/doomgeneric/p_enemy.c:1385` | `void A_FatAttack3 (mobj_t*	actor)` |
| `A_FatRaise` | function | `progs/doomgeneric/p_enemy.c:1339` | `void A_FatRaise (mobj_t *actor)` |
| `A_Fire` | function | `progs/doomgeneric/p_enemy.c:1242` | `void A_Fire (mobj_t* actor)` |
| `A_FireCrackle` | function | `progs/doomgeneric/p_enemy.c:1236` | `void A_FireCrackle (mobj_t* actor)` |
| `A_HeadAttack` | function | `progs/doomgeneric/p_enemy.c:935` | `void A_HeadAttack (mobj_t* actor)` |
| `A_Hoof` | function | `progs/doomgeneric/p_enemy.c:1757` | `void A_Hoof (mobj_t* mo)` |
| `A_KeenDie` | function | `progs/doomgeneric/p_enemy.c:551` | `void A_KeenDie (mobj_t* mo)` |
| `A_LoadShotgun2` | function | `progs/doomgeneric/p_enemy.c:1784` | `void A_LoadShotgun2 ( player_t*	player,   pspdef_t*	psp )` |
| `A_Look` | function | `progs/doomgeneric/p_enemy.c:589` | `void A_Look (mobj_t* actor)` |
| `A_Metal` | function | `progs/doomgeneric/p_enemy.c:1763` | `void A_Metal (mobj_t* mo)` |
| `A_OpenShotgun2` | function | `progs/doomgeneric/p_enemy.c:1776` | `void A_OpenShotgun2 ( player_t*	player,   pspdef_t*	psp )` |
| `A_Pain` | function | `progs/doomgeneric/p_enemy.c:1573` | `void A_Pain (mobj_t* actor)` |
| `A_PainAttack` | function | `progs/doomgeneric/p_enemy.c:1508` | `void A_PainAttack (mobj_t* actor)` |
| `A_PainDie` | function | `progs/doomgeneric/p_enemy.c:1518` | `void A_PainDie (mobj_t* actor)` |
| `A_PainShootSkull` | function | `progs/doomgeneric/p_enemy.c:1446` | `void A_PainShootSkull ( mobj_t*	actor,   angle_t	angle )` |
| `A_PlayerScream` | function | `progs/doomgeneric/p_enemy.c:1992` | `void A_PlayerScream (mobj_t* mo)` |
| `A_PosAttack` | function | `progs/doomgeneric/p_enemy.c:787` | `void A_PosAttack (mobj_t* actor)` |
| `A_ReFire` | function | `progs/doomgeneric/p_enemy.c:1792` | `void A_ReFire ( player_t* player, pspdef_t* psp );` |
| `A_SPosAttack` | function | `progs/doomgeneric/p_enemy.c:806` | `void A_SPosAttack (mobj_t* actor)` |
| `A_SargAttack` | function | `progs/doomgeneric/p_enemy.c:920` | `void A_SargAttack (mobj_t* actor)` |
| `A_Scream` | function | `progs/doomgeneric/p_enemy.c:1531` | `void A_Scream (mobj_t* actor)` |
| `A_SkelFist` | function | `progs/doomgeneric/p_enemy.c:1086` | `void A_SkelFist (mobj_t*	actor)` |
| `A_SkelMissile` | function | `progs/doomgeneric/p_enemy.c:987` | `void A_SkelMissile (mobj_t* actor)` |
| `A_SkelWhoosh` | function | `progs/doomgeneric/p_enemy.c:1078` | `void A_SkelWhoosh (mobj_t*	actor)` |
| `A_SkullAttack` | function | `progs/doomgeneric/p_enemy.c:1415` | `void A_SkullAttack (mobj_t* actor)` |
| `A_SpawnFly` | function | `progs/doomgeneric/p_enemy.c:1934` | `void A_SpawnFly (mobj_t* mo)` |
| `A_SpawnSound` | function | `progs/doomgeneric/p_enemy.c:1928` | `void A_SpawnSound (mobj_t* mo)` |
| `A_SpidRefire` | function | `progs/doomgeneric/p_enemy.c:867` | `void A_SpidRefire (mobj_t* actor)` |
| `A_StartFire` | function | `progs/doomgeneric/p_enemy.c:1230` | `void A_StartFire (mobj_t* actor)` |
| `A_Tracer` | function | `progs/doomgeneric/p_enemy.c:1006` | `void A_Tracer (mobj_t* actor)` |
| `A_TroopAttack` | function | `progs/doomgeneric/p_enemy.c:898` | `void A_TroopAttack (mobj_t* actor)` |
| `A_VileAttack` | function | `progs/doomgeneric/p_enemy.c:1298` | `void A_VileAttack (mobj_t* actor)` |
| `A_VileChase` | function | `progs/doomgeneric/p_enemy.c:1152` | `void A_VileChase (mobj_t* actor)` |
| `A_VileStart` | function | `progs/doomgeneric/p_enemy.c:1218` | `void A_VileStart (mobj_t* actor)` |
| `A_VileTarget` | function | `progs/doomgeneric/p_enemy.c:1273` | `void A_VileTarget (mobj_t*	actor)` |
| `A_XScream` | function | `progs/doomgeneric/p_enemy.c:1568` | `void A_XScream (mobj_t* actor)` |
| `CheckBossEnd` | function | `progs/doomgeneric/p_enemy.c:1605` | `static boolean CheckBossEnd(mobjtype_t motype)` |
| `FATSPREAD` | macro | `progs/doomgeneric/p_enemy.c:1337` | `#define	FATSPREAD` |
| `PIT_VileCheck` | function | `progs/doomgeneric/p_enemy.c:1114` | `boolean PIT_VileCheck (mobj_t*	thing)` |
| `P_CheckMeleeRange` | function | `progs/doomgeneric/p_enemy.c:167` | `boolean P_CheckMeleeRange (mobj_t*	actor)` |
| `P_CheckMissileRange` | function | `progs/doomgeneric/p_enemy.c:190` | `boolean P_CheckMissileRange (mobj_t* actor)` |
| `P_LookForPlayers` | function | `progs/doomgeneric/p_enemy.c:487` | `boolean P_LookForPlayers ( mobj_t*	actor,   boolean	allaround )` |
| `P_Move` | function | `progs/doomgeneric/p_enemy.c:260` | `boolean P_Move (mobj_t*	actor)` |
| `P_NewChaseDir` | function | `progs/doomgeneric/p_enemy.c:351` | `void P_NewChaseDir (mobj_t*	actor)` |
| `P_NoiseAlert` | function | `progs/doomgeneric/p_enemy.c:152` | `void P_NoiseAlert ( mobj_t*	target,   mobj_t*	emmiter )` |
| `P_RecursiveSound` | function | `progs/doomgeneric/p_enemy.c:99` | `void P_RecursiveSound ( sector_t*	sec,   int		soundblocks )` |
| `P_TryWalk` | function | `progs/doomgeneric/p_enemy.c:337` | `boolean P_TryWalk (mobj_t* actor)` |
| `SKULLSPEED` | macro | `progs/doomgeneric/p_enemy.c:1413` | `#define	SKULLSPEED` |
| `EV_BuildStairs` | function | `progs/doomgeneric/p_floor.c:444` | `int EV_BuildStairs ( line_t*	line,   stair_e	type )` |
| `EV_DoFloor` | function | `progs/doomgeneric/p_floor.c:251` | `int EV_DoFloor ( line_t*	line,   floor_e	floortype )` |
| `T_MoveFloor` | function | `progs/doomgeneric/p_floor.c:202` | `void T_MoveFloor(floormove_t* floor)` |
| `T_MovePlane` | function | `progs/doomgeneric/p_floor.c:42` | `result_e T_MovePlane ( sector_t*	sector,   fixed_t	speed,   fixed_t	dest,   boolean	crush,   int	...` |
| `BONUSADD` | macro | `progs/doomgeneric/p_inter.c:43` | `#define BONUSADD` |
| `P_DamageMobj` | function | `progs/doomgeneric/p_inter.c:779` | `void P_DamageMobj ( mobj_t*	target,   mobj_t*	inflictor,   mobj_t*	source,   int 		damage )` |
| `P_GiveAmmo` | function | `progs/doomgeneric/p_inter.c:66` | `boolean P_GiveAmmo ( player_t*	player,   ammotype_t	ammo,   int		num )` |
| `P_GiveArmor` | function | `progs/doomgeneric/p_inter.c:246` | `boolean P_GiveArmor ( player_t*	player,   int		armortype )` |
| `P_GiveBody` | function | `progs/doomgeneric/p_inter.c:223` | `boolean P_GiveBody ( player_t*	player,   int		num )` |
| `P_GiveCard` | function | `progs/doomgeneric/p_inter.c:268` | `void P_GiveCard ( player_t*	player,   card_t	card )` |
| `P_GivePower` | function | `progs/doomgeneric/p_inter.c:284` | `boolean P_GivePower ( player_t*	player,   int /*powertype_t*/	power )` |
| `P_GiveWeapon` | function | `progs/doomgeneric/p_inter.c:160` | `boolean P_GiveWeapon ( player_t*	player,   weapontype_t	weapon,   boolean	dropped )` |
| `P_KillMobj` | function | `progs/doomgeneric/p_inter.c:666` | `void P_KillMobj ( mobj_t*	source,   mobj_t*	target )` |
| `P_TouchSpecialThing` | function | `progs/doomgeneric/p_inter.c:333` | `void P_TouchSpecialThing ( mobj_t*	special,   mobj_t*	toucher )` |
| `__P_INTER__` | macro | `progs/doomgeneric/p_inter.h:21` | `#define __P_INTER__` |
| `EV_LightTurnOn` | function | `progs/doomgeneric/p_lights.c:264` | `void EV_LightTurnOn ( line_t*	line,   int		bright )` |
| `EV_StartLightStrobing` | function | `progs/doomgeneric/p_lights.c:208` | `void EV_StartLightStrobing(line_t*	line)` |
| `EV_TurnTagLightsOff` | function | `progs/doomgeneric/p_lights.c:229` | `void EV_TurnTagLightsOff(line_t* line)` |
| `P_SpawnFireFlicker` | function | `progs/doomgeneric/p_lights.c:61` | `void P_SpawnFireFlicker (sector_t*	sector)` |
| `P_SpawnGlowingLight` | function | `progs/doomgeneric/p_lights.c:334` | `void P_SpawnGlowingLight(sector_t*	sector)` |
| `P_SpawnLightFlash` | function | `progs/doomgeneric/p_lights.c:117` | `void P_SpawnLightFlash (sector_t*	sector)` |
| `P_SpawnStrobeFlash` | function | `progs/doomgeneric/p_lights.c:174` | `void P_SpawnStrobeFlash ( sector_t*	sector,   int		fastOrSlow,   int		inSync )` |
| `T_FireFlicker` | function | `progs/doomgeneric/p_lights.c:39` | `void T_FireFlicker (fireflicker_t* flick)` |
| `T_Glow` | function | `progs/doomgeneric/p_lights.c:307` | `void T_Glow(glow_t*	g)` |
| `T_LightFlash` | function | `progs/doomgeneric/p_lights.c:91` | `void T_LightFlash (lightflash_t* flash)` |
| `T_StrobeFlash` | function | `progs/doomgeneric/p_lights.c:148` | `void T_StrobeFlash (strobe_t*		flash)` |
| `BASETHRESHOLD` | macro | `progs/doomgeneric/p_local.h:58` | `#define	BASETHRESHOLD` |
| `FLOATSPEED` | macro | `progs/doomgeneric/p_local.h:27` | `#define FLOATSPEED` |
| `GRAVITY` | macro | `progs/doomgeneric/p_local.h:50` | `#define GRAVITY` |
| `ITEMQUESIZE` | macro | `progs/doomgeneric/p_local.h:96` | `#define ITEMQUESIZE` |
| `MAPBLOCKSHIFT` | macro | `progs/doomgeneric/p_local.h:37` | `#define MAPBLOCKSHIFT` |
| `MAPBLOCKSIZE` | macro | `progs/doomgeneric/p_local.h:36` | `#define MAPBLOCKSIZE` |
| `MAPBLOCKUNITS` | macro | `progs/doomgeneric/p_local.h:35` | `#define MAPBLOCKUNITS` |
| `MAPBMASK` | macro | `progs/doomgeneric/p_local.h:38` | `#define MAPBMASK` |
| `MAPBTOFRAC` | macro | `progs/doomgeneric/p_local.h:39` | `#define MAPBTOFRAC` |
| `MAXHEALTH` | macro | `progs/doomgeneric/p_local.h:30` | `#define MAXHEALTH` |
| `MAXINTERCEPTS` | macro | `progs/doomgeneric/p_local.h:155` | `#define MAXINTERCEPTS` |
| `MAXINTERCEPTS_ORIGINAL` | macro | `progs/doomgeneric/p_local.h:154` | `#define MAXINTERCEPTS_ORIGINAL` |
| `MAXMOVE` | macro | `progs/doomgeneric/p_local.h:51` | `#define MAXMOVE` |
| `MAXRADIUS` | macro | `progs/doomgeneric/p_local.h:48` | `#define MAXRADIUS` |
| `MAXSPECIALCROSS` | macro | `progs/doomgeneric/p_local.h:219` | `#define MAXSPECIALCROSS` |
| `MAXSPECIALCROSS_ORIGINAL` | macro | `progs/doomgeneric/p_local.h:220` | `#define MAXSPECIALCROSS_ORIGINAL` |
| `MELEERANGE` | macro | `progs/doomgeneric/p_local.h:54` | `#define MELEERANGE` |
| `MISSILERANGE` | macro | `progs/doomgeneric/p_local.h:55` | `#define MISSILERANGE` |
| `ONCEILINGZ` | macro | `progs/doomgeneric/p_local.h:93` | `#define ONCEILINGZ` |
| `ONFLOORZ` | macro | `progs/doomgeneric/p_local.h:92` | `#define ONFLOORZ` |
| `PLAYERRADIUS` | macro | `progs/doomgeneric/p_local.h:43` | `#define PLAYERRADIUS` |
| `PT_ADDLINES` | macro | `progs/doomgeneric/p_local.h:179` | `#define PT_ADDLINES` |
| `PT_ADDTHINGS` | macro | `progs/doomgeneric/p_local.h:180` | `#define PT_ADDTHINGS` |
| `PT_EARLYOUT` | macro | `progs/doomgeneric/p_local.h:181` | `#define PT_EARLYOUT` |
| `P_AddThinker` | function | `progs/doomgeneric/p_local.h:71` | `void P_AddThinker (thinker_t* thinker);` |
| `P_AimLineAttack` | function | `progs/doomgeneric/p_local.h:237` | `fixed_t P_AimLineAttack ( mobj_t* t1, angle_t angle, fixed_t distance );` |
| `P_AproxDistance` | function | `progs/doomgeneric/p_local.h:162` | `fixed_t P_AproxDistance (fixed_t dx, fixed_t dy);` |
| `P_BoxOnLineSide` | function | `progs/doomgeneric/p_local.h:167` | `int P_BoxOnLineSide (fixed_t* tmbox, line_t* ld);` |
| `P_DamageMobj` | function | `progs/doomgeneric/p_local.h:284` | `void P_DamageMobj ( mobj_t* target, mobj_t* inflictor, mobj_t* source, int damage );` |
| `P_DropWeapon` | function | `progs/doomgeneric/p_local.h:80` | `void P_DropWeapon (player_t* player);` |
| `P_InitThinkers` | function | `progs/doomgeneric/p_local.h:70` | `void P_InitThinkers (void);` |
| `P_InterceptVector` | function | `progs/doomgeneric/p_local.h:166` | `fixed_t P_InterceptVector (divline_t* v2, divline_t* v1);` |
| `P_LineAttack` | function | `progs/doomgeneric/p_local.h:243` | `void P_LineAttack ( mobj_t* t1, angle_t angle, fixed_t distance, fixed_t slope, int damage );` |
| `P_LineOpening` | function | `progs/doomgeneric/p_local.h:174` | `void P_LineOpening (line_t* linedef);` |
| `P_MakeDivline` | function | `progs/doomgeneric/p_local.h:165` | `void P_MakeDivline (line_t* li, divline_t* dl);` |
| `P_MobjThinker` | function | `progs/doomgeneric/p_local.h:116` | `void P_MobjThinker (mobj_t* mobj);` |
| `P_MovePsprites` | function | `progs/doomgeneric/p_local.h:79` | `void P_MovePsprites (player_t* curplayer);` |
| `P_NoiseAlert` | function | `progs/doomgeneric/p_local.h:127` | `void P_NoiseAlert (mobj_t* target, mobj_t* emmiter);` |
| `P_PlayerThink` | function | `progs/doomgeneric/p_local.h:86` | `void P_PlayerThink (player_t* player);` |
| `P_PointOnDivlineSide` | function | `progs/doomgeneric/p_local.h:164` | `int P_PointOnDivlineSide (fixed_t x, fixed_t y, divline_t* line);` |
| `P_PointOnLineSide` | function | `progs/doomgeneric/p_local.h:163` | `int P_PointOnLineSide (fixed_t x, fixed_t y, line_t* line);` |
| `P_RadiusAttack` | function | `progs/doomgeneric/p_local.h:251` | `void P_RadiusAttack ( mobj_t* spot, mobj_t* source, int damage );` |
| `P_RemoveMobj` | function | `progs/doomgeneric/p_local.h:113` | `void P_RemoveMobj (mobj_t* th);` |
| `P_RemoveThinker` | function | `progs/doomgeneric/p_local.h:72` | `void P_RemoveThinker (thinker_t* thinker);` |
| `P_RespawnSpecials` | function | `progs/doomgeneric/p_local.h:104` | `void P_RespawnSpecials (void);` |
| `P_SetThingPosition` | function | `progs/doomgeneric/p_local.h:195` | `void P_SetThingPosition (mobj_t* thing);` |
| `P_SetupPsprites` | function | `progs/doomgeneric/p_local.h:78` | `void P_SetupPsprites (player_t* curplayer);` |
| `P_SlideMove` | function | `progs/doomgeneric/p_local.h:228` | `void P_SlideMove (mobj_t* mo);` |
| `P_SpawnBlood` | function | `progs/doomgeneric/p_local.h:119` | `void P_SpawnBlood (fixed_t x, fixed_t y, fixed_t z, int damage);` |
| `P_SpawnMissile` | function | `progs/doomgeneric/p_local.h:120` | `mobj_t* P_SpawnMissile (mobj_t* source, mobj_t* dest, mobjtype_t type);` |
| `P_SpawnMobj` | function | `progs/doomgeneric/p_local.h:107` | `mobj_t* P_SpawnMobj ( fixed_t x, fixed_t y, fixed_t z, mobjtype_t type );` |
| `P_SpawnPlayerMissile` | function | `progs/doomgeneric/p_local.h:121` | `void P_SpawnPlayerMissile (mobj_t* source, mobjtype_t type);` |
| `P_SpawnPuff` | function | `progs/doomgeneric/p_local.h:118` | `void P_SpawnPuff (fixed_t x, fixed_t y, fixed_t z);` |
| `P_SubstNullMobj` | function | `progs/doomgeneric/p_local.h:114` | `mobj_t* P_SubstNullMobj (mobj_t* th);` |
| `P_TouchSpecialThing` | function | `progs/doomgeneric/p_local.h:279` | `void P_TouchSpecialThing ( mobj_t* special, mobj_t* toucher );` |
| `P_UnsetThingPosition` | function | `progs/doomgeneric/p_local.h:194` | `void P_UnsetThingPosition (mobj_t* thing);` |
| `P_UseLines` | function | `progs/doomgeneric/p_local.h:230` | `void P_UseLines (player_t* player);` |
| `USERANGE` | macro | `progs/doomgeneric/p_local.h:53` | `#define USERANGE` |
| `VIEWHEIGHT` | macro | `progs/doomgeneric/p_local.h:31` | `#define VIEWHEIGHT` |
| `__P_LOCAL__` | macro | `progs/doomgeneric/p_local.h:21` | `#define __P_LOCAL__` |
| `blocklinks` | variable | `progs/doomgeneric/p_local.h:268` | `extern mobj_t** blocklinks;` |
| `blockmap` | variable | `progs/doomgeneric/p_local.h:263` | `extern short* blockmap;` |
| `blockmaplump` | variable | `progs/doomgeneric/p_local.h:262` | `extern short* blockmaplump;` |
| `bmapheight` | variable | `progs/doomgeneric/p_local.h:265` | `extern int bmapheight;` |
| `bmaporgx` | variable | `progs/doomgeneric/p_local.h:266` | `extern fixed_t bmaporgx;` |
| `bmaporgy` | variable | `progs/doomgeneric/p_local.h:267` | `extern fixed_t bmaporgy;` |
| `bmapwidth` | variable | `progs/doomgeneric/p_local.h:264` | `extern int bmapwidth;` |
| `ceilingline` | variable | `progs/doomgeneric/p_local.h:209` | `extern line_t* ceilingline;` |
| `clipammo` | variable | `progs/doomgeneric/p_local.h:276` | `extern int clipammo[NUMAMMO];` |
| `d` | struct | `progs/doomgeneric/p_local.h:142` | `` |
| `divline_t` | struct | `progs/doomgeneric/p_local.h:133` | `` |
| `floatok` | variable | `progs/doomgeneric/p_local.h:204` | `extern boolean floatok;` |
| `intercept_p` | variable | `progs/doomgeneric/p_local.h:158` | `extern intercept_t* intercept_p;` |
| `intercepts` | variable | `progs/doomgeneric/p_local.h:157` | `extern intercept_t intercepts[MAXINTERCEPTS];` |
| `iquehead` | variable | `progs/doomgeneric/p_local.h:100` | `extern int iquehead;` |
| `iquetail` | variable | `progs/doomgeneric/p_local.h:101` | `extern int iquetail;` |
| `itemrespawnque` | variable | `progs/doomgeneric/p_local.h:98` | `extern mapthing_t itemrespawnque[ITEMQUESIZE];` |
| `itemrespawntime` | variable | `progs/doomgeneric/p_local.h:99` | `extern int itemrespawntime[ITEMQUESIZE];` |
| `linetarget` | variable | `progs/doomgeneric/p_local.h:234` | `extern mobj_t* linetarget;` |
| `lowfloor` | variable | `progs/doomgeneric/p_local.h:172` | `extern fixed_t lowfloor;` |
| `maxammo` | variable | `progs/doomgeneric/p_local.h:275` | `extern int maxammo[NUMAMMO];` |
| `numspechit` | variable | `progs/doomgeneric/p_local.h:223` | `extern int numspechit;` |
| `openbottom` | variable | `progs/doomgeneric/p_local.h:170` | `extern fixed_t openbottom;` |
| `openrange` | variable | `progs/doomgeneric/p_local.h:171` | `extern fixed_t openrange;` |
| `opentop` | variable | `progs/doomgeneric/p_local.h:169` | `extern fixed_t opentop;` |
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

Next: [SYMBOLS_p17.md](SYMBOLS_p17.md)
