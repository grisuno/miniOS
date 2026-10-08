# API (page 13 of 19)
Previous: [API_p12.md](API_p12.md)

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

## progs/doomgeneric/r_draw.c
Depends on: `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`
- `R_DrawColumn` (function) `progs/doomgeneric/r_draw.c:102` `void R_DrawColumn (void)` -- A column is a vertical slice/span from a wall texture that, given the DOOM style restrictions on the view...
- `R_DrawColumn` (function) `progs/doomgeneric/r_draw.c:152` `void R_DrawColumn (void)` -- UNUSED.
- `R_DrawColumnLow` (function) `progs/doomgeneric/r_draw.c:208` `void R_DrawColumnLow (void)`
- `R_DrawFuzzColumn` (function) `progs/doomgeneric/r_draw.c:283` `void R_DrawFuzzColumn (void)` -- Framebuffer postprocessing.
- `R_DrawFuzzColumnLow` (function) `progs/doomgeneric/r_draw.c:342` `void R_DrawFuzzColumnLow (void)`
- `R_DrawTranslatedColumn` (function) `progs/doomgeneric/r_draw.c:424` `void R_DrawTranslatedColumn (void)`
- `R_DrawTranslatedColumnLow` (function) `progs/doomgeneric/r_draw.c:468` `void R_DrawTranslatedColumnLow (void)`
- `R_InitTranslationTables` (function) `progs/doomgeneric/r_draw.c:530` `void R_InitTranslationTables (void)` -- R_InitTranslationTables Creates the translation tables to map the green color ramp to gray, brown, red.
- `R_DrawSpan` (function) `progs/doomgeneric/r_draw.c:590` `void R_DrawSpan (void)` -- Draws the actual span.
- `R_DrawSpan` (function) `progs/doomgeneric/r_draw.c:646` `void R_DrawSpan (void)` -- UNUSED.
- `R_DrawSpanLow` (function) `progs/doomgeneric/r_draw.c:719` `void R_DrawSpanLow (void)` -- Again..
- `R_InitBuffer` (function) `progs/doomgeneric/r_draw.c:777` `void
R_InitBuffer
( int		width,
  int		height )`
- `R_FillBackScreen` (function) `progs/doomgeneric/r_draw.c:812` `void R_FillBackScreen (void)` -- R_FillBackScreen Fills the back screen with a pattern for variable screen sizes Also draws a beveled edge.
- `R_VideoErase` (function) `progs/doomgeneric/r_draw.c:919` `void
R_VideoErase
( unsigned	ofs,
  int		count )`
- `R_DrawViewBorder` (function) `progs/doomgeneric/r_draw.c:941` `void R_DrawViewBorder (void)` -- R_DrawViewBorder Draws the border around the view for different size windows?

## progs/doomgeneric/r_draw.h
Imported by: `progs/doomgeneric/hu_lib.c`, `progs/doomgeneric/r_local.h`
- `R_DrawColumn` (function) `progs/doomgeneric/r_draw.h:40` `void R_DrawColumn (void);` -- The span blitting interface.
- `R_DrawColumnLow` (function) `progs/doomgeneric/r_draw.h:41` `void R_DrawColumnLow (void);`
- `R_DrawFuzzColumn` (function) `progs/doomgeneric/r_draw.h:44` `void R_DrawFuzzColumn (void);` -- The Spectre/Invisibility effect.
- `R_DrawFuzzColumnLow` (function) `progs/doomgeneric/r_draw.h:45` `void R_DrawFuzzColumnLow (void);`
- `R_DrawTranslatedColumn` (function) `progs/doomgeneric/r_draw.h:50` `void R_DrawTranslatedColumn (void);` -- Draw with color translation tables, for player sprite rendering, Green/Red/Blue/Indigo shirts.
- `R_DrawTranslatedColumnLow` (function) `progs/doomgeneric/r_draw.h:51` `void R_DrawTranslatedColumnLow (void);`
- `R_VideoErase` (function) `progs/doomgeneric/r_draw.h:54` `void R_VideoErase ( unsigned ofs, int count );`
- `R_DrawSpan` (function) `progs/doomgeneric/r_draw.h:78` `void R_DrawSpan (void);` -- Span blitting for rows, floor/ceiling.
- `R_DrawSpanLow` (function) `progs/doomgeneric/r_draw.h:81` `void R_DrawSpanLow (void);` -- Low resolution mode, 160x200?
- `R_InitBuffer` (function) `progs/doomgeneric/r_draw.h:85` `void R_InitBuffer ( int width, int height );`
- `R_InitTranslationTables` (function) `progs/doomgeneric/r_draw.h:92` `void R_InitTranslationTables (void);` -- Initialize color translation tables, for player rendering etc.
- `R_FillBackScreen` (function) `progs/doomgeneric/r_draw.h:97` `void R_FillBackScreen (void);` -- Rendering function.
- `R_DrawViewBorder` (function) `progs/doomgeneric/r_draw.h:100` `void R_DrawViewBorder (void);` -- If the view size is not full screen, draws a border around it.

## progs/doomgeneric/r_main.c
Depends on: `progs/doomgeneric/d_loop.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/m_bbox.h`, `progs/doomgeneric/m_menu.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/r_sky.h`
- `R_AddPointToBox` (function) `progs/doomgeneric/r_main.c:123` `void
R_AddPointToBox
( int		x,
  int		y,
  fixed_t*	box )`
- `R_PointOnSide` (function) `progs/doomgeneric/r_main.c:146` `int
R_PointOnSide
( fixed_t	x,
  fixed_t	y,
  node_t*	node )`
- `R_PointOnSegSide` (function) `progs/doomgeneric/r_main.c:199` `int
R_PointOnSegSide
( fixed_t	x,
  fixed_t	y,
  seg_t*	line )`
- `R_PointToAngle` (function) `progs/doomgeneric/r_main.c:276` `angle_t
R_PointToAngle
( fixed_t	x,
  fixed_t	y )`
- `R_PointToAngle2` (function) `progs/doomgeneric/r_main.c:362` `angle_t
R_PointToAngle2
( fixed_t	x1,
  fixed_t	y1,
  fixed_t	x2,
  fixed_t	y2 )`
- `R_PointToDist` (function) `progs/doomgeneric/r_main.c:376` `fixed_t
R_PointToDist
( fixed_t	x,
  fixed_t	y )`
- `R_InitPointToAngle` (function) `progs/doomgeneric/r_main.c:422` `void R_InitPointToAngle (void)` -- R_InitPointToAngle
- `R_ScaleFromGlobalAngle` (function) `progs/doomgeneric/r_main.c:449` `fixed_t R_ScaleFromGlobalAngle (angle_t visangle)` -- R_ScaleFromGlobalAngle Returns the texture mapping scale for the current line (horizontal span) at the given angle....
- `R_InitTables` (function) `progs/doomgeneric/r_main.c:505` `void R_InitTables (void)` -- R_InitTables
- `R_InitTextureMapping` (function) `progs/doomgeneric/r_main.c:540` `void R_InitTextureMapping (void)` -- R_InitTextureMapping
- `R_InitLightTables` (function) `progs/doomgeneric/r_main.c:610` `void R_InitLightTables (void)`
- `R_SetViewSize` (function) `progs/doomgeneric/r_main.c:654` `void
R_SetViewSize
( int		blocks,
  int		detail )`
- `R_ExecuteSetViewSize` (function) `progs/doomgeneric/r_main.c:667` `void R_ExecuteSetViewSize (void)` -- R_ExecuteSetViewSize
- `R_Init` (function) `progs/doomgeneric/r_main.c:767` `void R_Init (void)`
- `R_PointInSubsector` (function) `progs/doomgeneric/r_main.c:794` `subsector_t*
R_PointInSubsector
( fixed_t	x,
  fixed_t	y )`
- `R_SetupFrame` (function) `progs/doomgeneric/r_main.c:823` `void R_SetupFrame (player_t* player)` -- R_SetupFrame
- `R_RenderPlayerView` (function) `progs/doomgeneric/r_main.c:863` `void R_RenderPlayerView (player_t* player)` -- R_RenderView

## progs/doomgeneric/r_main.h
Depends on: `progs/doomgeneric/d_player.h`, `progs/doomgeneric/r_data.h`
Imported by: `progs/doomgeneric/r_bsp.c`, `progs/doomgeneric/r_local.h`
- `void` (function) `progs/doomgeneric/r_main.h:92` `extern void (*colfunc) (void);` -- Function pointers to switch refresh/drawing functions.
- `R_PointOnSide` (function) `progs/doomgeneric/r_main.h:103` `int R_PointOnSide ( fixed_t x, fixed_t y, node_t* node );`
- `R_PointOnSegSide` (function) `progs/doomgeneric/r_main.h:109` `int R_PointOnSegSide ( fixed_t x, fixed_t y, seg_t* line );`
- `R_PointToAngle` (function) `progs/doomgeneric/r_main.h:115` `angle_t R_PointToAngle ( fixed_t x, fixed_t y );`
- `R_PointToAngle2` (function) `progs/doomgeneric/r_main.h:120` `angle_t R_PointToAngle2 ( fixed_t x1, fixed_t y1, fixed_t x2, fixed_t y2 );`
- `R_PointToDist` (function) `progs/doomgeneric/r_main.h:127` `fixed_t R_PointToDist ( fixed_t x, fixed_t y );`
- `R_ScaleFromGlobalAngle` (function) `progs/doomgeneric/r_main.h:132` `fixed_t R_ScaleFromGlobalAngle (angle_t visangle);`
- `R_PointInSubsector` (function) `progs/doomgeneric/r_main.h:135` `subsector_t* R_PointInSubsector ( fixed_t x, fixed_t y );`
- `R_AddPointToBox` (function) `progs/doomgeneric/r_main.h:140` `void R_AddPointToBox ( int x, int y, fixed_t* box );`
- `R_RenderPlayerView` (function) `progs/doomgeneric/r_main.h:152` `void R_RenderPlayerView (player_t *player);` -- Called by G_Drawer.
- `R_Init` (function) `progs/doomgeneric/r_main.h:155` `void R_Init (void);` -- Called by startup code.
- `R_SetViewSize` (function) `progs/doomgeneric/r_main.h:158` `void R_SetViewSize (int blocks, int detail);` -- Called by M_Responder.

## progs/doomgeneric/r_plane.c
Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/r_sky.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`
- `R_InitPlanes` (function) `progs/doomgeneric/r_plane.c:94` `void R_InitPlanes (void)` -- R_InitPlanes Only at game startup.
- `R_MapPlane` (function) `progs/doomgeneric/r_plane.c:114` `void
R_MapPlane
( int		y,
  int		x1,
  int		x2 )`
- `R_ClearPlanes` (function) `progs/doomgeneric/r_plane.c:178` `void R_ClearPlanes (void)` -- R_ClearPlanes At begining of frame.
- `R_FindPlane` (function) `progs/doomgeneric/r_plane.c:211` `visplane_t*
R_FindPlane
( fixed_t	height,
  int		picnum,
  int		lightlevel )`
- `R_CheckPlane` (function) `progs/doomgeneric/r_plane.c:259` `visplane_t*
R_CheckPlane
( visplane_t*	pl,
  int		start,
  int		stop )`
- `R_MakeSpans` (function) `progs/doomgeneric/r_plane.c:324` `void
R_MakeSpans
( int		x,
  int		t1,
  int		b1,
  int		t2,
  int		b2 )`
- `R_DrawPlanes` (function) `progs/doomgeneric/r_plane.c:360` `void R_DrawPlanes (void)` -- R_DrawPlanes At the end of each frame.

## progs/doomgeneric/r_plane.h
Depends on: `progs/doomgeneric/r_data.h`
Imported by: `progs/doomgeneric/r_bsp.c`, `progs/doomgeneric/r_local.h`
- `R_InitPlanes` (function) `progs/doomgeneric/r_plane.h:43` `void R_InitPlanes (void);`
- `R_ClearPlanes` (function) `progs/doomgeneric/r_plane.h:44` `void R_ClearPlanes (void);`
- `R_MapPlane` (function) `progs/doomgeneric/r_plane.h:47` `void R_MapPlane ( int y, int x1, int x2 );`
- `R_MakeSpans` (function) `progs/doomgeneric/r_plane.h:53` `void R_MakeSpans ( int x, int t1, int b1, int t2, int b2 );`
- `R_DrawPlanes` (function) `progs/doomgeneric/r_plane.h:60` `void R_DrawPlanes (void);`
- `R_FindPlane` (function) `progs/doomgeneric/r_plane.h:63` `visplane_t* R_FindPlane ( fixed_t height, int picnum, int lightlevel );`
- `R_CheckPlane` (function) `progs/doomgeneric/r_plane.h:69` `visplane_t* R_CheckPlane ( visplane_t* pl, int start, int stop );`

## progs/doomgeneric/r_segs.c
Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/r_sky.h`
- `R_RenderMaskedSegRange` (function) `progs/doomgeneric/r_segs.c:96` `void
R_RenderMaskedSegRange
( drawseg_t*	ds,
  int		x1,
  int		x2 )`
- `R_RenderSegLoop` (function) `progs/doomgeneric/r_segs.c:199` `void R_RenderSegLoop (void)`
- `R_StoreWallRange` (function) `progs/doomgeneric/r_segs.c:372` `void
R_StoreWallRange
( int	start,
  int	stop )`

## progs/doomgeneric/r_segs.h
Imported by: `progs/doomgeneric/r_local.h`
- `R_RenderMaskedSegRange` (function) `progs/doomgeneric/r_segs.h:27` `void R_RenderMaskedSegRange ( drawseg_t* ds, int x1, int x2 );`

## progs/doomgeneric/r_sky.c
Depends on: `progs/doomgeneric/m_fixed.h`, `progs/doomgeneric/r_data.h`, `progs/doomgeneric/r_sky.h`
- `R_InitSkyMap` (function) `progs/doomgeneric/r_sky.c:47` `void R_InitSkyMap (void)` -- R_InitSkyMap Called whenever the view size changes.

## progs/doomgeneric/r_sky.h
Imported by: `progs/doomgeneric/g_game.c`, `progs/doomgeneric/r_data.c`, `progs/doomgeneric/r_main.c`, `progs/doomgeneric/r_plane.c`, `progs/doomgeneric/r_segs.c`, `progs/doomgeneric/r_sky.c`
- `R_InitSkyMap` (function) `progs/doomgeneric/r_sky.h:35` `void R_InitSkyMap (void);` -- Called whenever the view size changes.


Next: [API_p14.md](API_p14.md)
