# Subsystem: doomgeneric (page 8 of 12)
Previous: [KB_doomgeneric_p7.md](KB_doomgeneric_p7.md)

## progs/doomgeneric/p_maputl.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
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
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
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
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `mobj_s` (struct, line 201)
  - `thinker` (type_alias, line 201) `typedef struct mobj_s { // List: thinker links. thinker_t thinker;`
  - `__P_MOBJ__` (macro, line 21) `#define __P_MOBJ__`
- Depends on: `progs/doomgeneric/d_think.h`, `progs/doomgeneric/doomdata.h`, `progs/doomgeneric/info.h`, `progs/doomgeneric/m_fixed.h`, `progs/doomgeneric/tables.h`
- Imported by: `progs/doomgeneric/d_player.h`, `progs/doomgeneric/info.c`, `progs/doomgeneric/r_defs.h`, `progs/doomgeneric/s_sound.h`

## progs/doomgeneric/p_plats.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
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
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
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
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `pspdef_t` (struct, line 62)
  - `__P_PSPR__` (macro, line 21) `#define __P_PSPR__`
  - `FF_FULLBRIGHT` (macro, line 44) `#define FF_FULLBRIGHT`
  - `FF_FRAMEMASK` (macro, line 45) `#define FF_FRAMEMASK`
- Depends on: `progs/doomgeneric/info.h`, `progs/doomgeneric/m_fixed.h`, `progs/doomgeneric/tables.h`
- Imported by: `progs/doomgeneric/d_player.h`, `progs/doomgeneric/p_pspr.c`

## progs/doomgeneric/p_saveg.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
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
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
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
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: infrastructure
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
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: infrastructure
- Language: h
- Symbols:
  - `P_SetupLevel` (function, line 28) `void P_SetupLevel ( int episode, int map, int playermask, skill_t skill);`
  - `P_Init` (function, line 35) `void P_Init (void);`
  - `__P_SETUP__` (macro, line 21) `#define __P_SETUP__`
- Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/g_game.c`

## progs/doomgeneric/p_sight.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
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
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: testing
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


Next: [KB_doomgeneric_p9.md](KB_doomgeneric_p9.md)
