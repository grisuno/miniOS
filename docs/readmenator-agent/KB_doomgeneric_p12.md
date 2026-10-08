# Subsystem: doomgeneric (page 12 of 12)
Previous: [KB_doomgeneric_p11.md](KB_doomgeneric_p11.md)

## progs/doomgeneric/wi_stuff.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `point_t` (struct, line 117)
  - `anim_t` (struct, line 129)
  - `WI_slamBackground` (function, line 402) `void WI_slamBackground(void)`
  - `WI_Responder` (function, line 409) `boolean WI_Responder(event_t* ev)`
  - `WI_drawLF` (function, line 416) `void WI_drawLF(void)`
  - `WI_drawEL` (function, line 452) `void WI_drawEL(void)`
  - `WI_drawOnLnode` (function, line 471) `void
WI_drawOnLnode
( int		n,
  patch_t*	c[] )`
  - `WI_initAnimatedBack` (function, line 519) `void WI_initAnimatedBack(void)`
  - `WI_updateAnimatedBack` (function, line 548) `void WI_updateAnimatedBack(void)`
  - `WI_drawAnimatedBack` (function, line 599) `void WI_drawAnimatedBack(void)`
  - `WI_drawNum` (function, line 628) `int
WI_drawNum
( int		x,
  int		y,
  int		n,
  int		digits )`
  - `WI_drawPercent` (function, line 685) `void
WI_drawPercent
( int		x,
  int		y,
  int		p )`
  - `WI_drawTime` (function, line 704) `void
WI_drawTime
( int		x,
  int		y,
  int		t )`
  - `WI_End` (function, line 740) `void WI_End(void)`
  - `WI_initNoState` (function, line 746) `void WI_initNoState(void)`
  - `WI_updateNoState` (function, line 753) `void WI_updateNoState(void)`
  - `WI_initShowNextLoc` (function, line 772) `void WI_initShowNextLoc(void)`
  - `WI_updateShowNextLoc` (function, line 781) `void WI_updateShowNextLoc(void)`
  - `WI_drawShowNextLoc` (function, line 791) `void WI_drawShowNextLoc(void)`
  - `WI_drawNoState` (function, line 832) `void WI_drawNoState(void)`
  - `WI_fragSum` (function, line 838) `int WI_fragSum(int playernum)`
  - `WI_initDeathmatchStats` (function, line 869) `void WI_initDeathmatchStats(void)`
  - `WI_updateDeathmatchStats` (function, line 898) `void WI_updateDeathmatchStats(void)`
  - `WI_drawDeathmatchStats` (function, line 1001) `void WI_drawDeathmatchStats(void)`
  - `WI_initNetgameStats` (function, line 1089) `void WI_initNetgameStats(void)`
  - `WI_updateNetgameStats` (function, line 1117) `void WI_updateNetgameStats(void)`
  - `WI_drawNetgameStats` (function, line 1272) `void WI_drawNetgameStats(void)`
  - `WI_initStats` (function, line 1329) `void WI_initStats(void)`
  - `WI_updateStats` (function, line 1341) `void WI_updateStats(void)`
  - `WI_drawStats` (function, line 1447) `void WI_drawStats(void)`
  - `WI_checkForAccelerate` (function, line 1481) `void WI_checkForAccelerate(void)`
  - `WI_Ticker` (function, line 1514) `void WI_Ticker(void)`
  - `WI_loadUnloadData` (function, line 1554) `static void WI_loadUnloadData(load_callback_t callback)`
  - `WI_loadCallback` (function, line 1704) `static void WI_loadCallback(char *name, patch_t **variable)`
  - `WI_loadData` (function, line 1709) `void WI_loadData(void)`
  - `WI_unloadCallback` (function, line 1735) `static void WI_unloadCallback(char *name, patch_t **variable)`
  - `WI_unloadData` (function, line 1741) `void WI_unloadData(void)`
  - `WI_Drawer` (function, line 1752) `void WI_Drawer (void)`
  - `WI_initVariables` (function, line 1776) `void WI_initVariables(wbstartstruct_t* wbstartstruct)`
  - `WI_Start` (function, line 1818) `void WI_Start(wbstartstruct_t* wbstartstruct)`
  - `NUMEPISODES` (macro, line 61) `#define NUMEPISODES`
  - `NUMMAPS` (macro, line 62) `#define NUMMAPS`
  - `WI_TITLEY` (macro, line 75) `#define WI_TITLEY`
  - `WI_SPACINGY` (macro, line 76) `#define WI_SPACINGY`
  - `SP_STATSX` (macro, line 79) `#define SP_STATSX`
  - `SP_STATSY` (macro, line 80) `#define SP_STATSY`
  - `SP_TIMEX` (macro, line 82) `#define SP_TIMEX`
  - `SP_TIMEY` (macro, line 83) `#define SP_TIMEY`
  - `NG_STATSY` (macro, line 87) `#define NG_STATSY`
  - `NG_STATSX` (macro, line 88) `#define NG_STATSX`
  - `NG_SPACINGX` (macro, line 90) `#define NG_SPACINGX`
  - `DM_MATRIXX` (macro, line 94) `#define DM_MATRIXX`
  - `DM_MATRIXY` (macro, line 95) `#define DM_MATRIXY`
  - `DM_SPACINGX` (macro, line 97) `#define DM_SPACINGX`
  - `DM_TOTALSX` (macro, line 99) `#define DM_TOTALSX`
  - `DM_KILLERSX` (macro, line 101) `#define DM_KILLERSX`
  - `DM_KILLERSY` (macro, line 102) `#define DM_KILLERSY`
  - `DM_VICTIMSX` (macro, line 103) `#define DM_VICTIMSX`
  - `DM_VICTIMSY` (macro, line 104) `#define DM_VICTIMSY`
  - `ANIM` (macro, line 222) `#define ANIM(type, period, nanims, x, y, nexttic)`
  - `SP_KILLS` (macro, line 288) `#define SP_KILLS`
  - `SP_ITEMS` (macro, line 289) `#define SP_ITEMS`
  - `SP_SECRET` (macro, line 290) `#define SP_SECRET`
  - `SP_FRAGS` (macro, line 291) `#define SP_FRAGS`
  - `SP_TIME` (macro, line 292) `#define SP_TIME`
  - `SP_PAR` (macro, line 293) `#define SP_PAR`
  - `SP_PAUSE` (macro, line 295) `#define SP_PAUSE`
  - `SHOWNEXTLOCDELAY` (macro, line 298) `#define SHOWNEXTLOCDELAY`
- Depends on: `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/wi_stuff.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/wi_stuff.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `WI_Ticker` (function, line 36) `void WI_Ticker (void);`
  - `WI_Drawer` (function, line 40) `void WI_Drawer (void);`
  - `WI_Start` (function, line 43) `void WI_Start(wbstartstruct_t* wbstartstruct);`
  - `WI_End` (function, line 46) `void WI_End(void);`
  - `__WI_STUFF__` (macro, line 20) `#define __WI_STUFF__`
- Depends on: `progs/doomgeneric/doomdef.h`
- Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/wi_stuff.c`

## progs/doomgeneric/z_zone.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `memblock_s` (struct, line 39)
  - `memzone_t` (struct, line 50)
  - `size` (type_alias, line 38) `typedef struct memblock_s { int size;`
  - `Z_ClearZone` (function, line 71) `void Z_ClearZone (memzone_t* zone)`
  - `Z_Init` (function, line 97) `void Z_Init (void)`
  - `Z_Free` (function, line 126) `void Z_Free (void* ptr)`
  - `Z_Malloc` (function, line 185) `void*
Z_Malloc
( int		size,
  int		tag,
  void*		user )`
  - `Z_FreeTags` (function, line 298) `void
Z_FreeTags
( int		lowtag,
  int		hightag )`
  - `Z_DumpHeap` (function, line 328) `void
Z_DumpHeap
( int		lowtag,
  int		hightag )`
  - `Z_FileDumpHeap` (function, line 367) `void Z_FileDumpHeap (FILE* f)`
  - `Z_CheckHeap` (function, line 400) `void Z_CheckHeap (void)`
  - `Z_ChangeTag2` (function, line 429) `void Z_ChangeTag2(void *ptr, int tag, char *file, int line)`
  - `Z_ChangeUser` (function, line 446) `void Z_ChangeUser(void *ptr, void **user)`
  - `Z_FreeMemory` (function, line 466) `int Z_FreeMemory (void)`
  - `Z_ZoneSize` (function, line 484) `unsigned int Z_ZoneSize(void)`
  - `MEM_ALIGN` (macro, line 36) `#define MEM_ALIGN`
  - `ZONEID` (macro, line 37) `#define ZONEID`
  - `MINFRAGMENT` (macro, line 181) `#define MINFRAGMENT`
- Depends on: `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/z_zone.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `Z_Init` (function, line 53) `void Z_Init (void);`
  - `Z_Malloc` (function, line 54) `void* Z_Malloc (int size, int tag, void *ptr);`
  - `Z_Free` (function, line 55) `void Z_Free (void *ptr);`
  - `Z_FreeTags` (function, line 56) `void Z_FreeTags (int lowtag, int hightag);`
  - `Z_DumpHeap` (function, line 57) `void Z_DumpHeap (int lowtag, int hightag);`
  - `Z_FileDumpHeap` (function, line 58) `void Z_FileDumpHeap (FILE *f);`
  - `Z_CheckHeap` (function, line 59) `void Z_CheckHeap (void);`
  - `Z_ChangeTag2` (function, line 60) `void Z_ChangeTag2 (void *ptr, int tag, char *file, int line);`
  - `Z_ChangeUser` (function, line 61) `void Z_ChangeUser(void *ptr, void **user);`
  - `Z_FreeMemory` (function, line 62) `int Z_FreeMemory (void);`
  - `Z_ZoneSize` (function, line 63) `unsigned int Z_ZoneSize(void);`
  - `__Z_ZONE__` (macro, line 25) `#define __Z_ZONE__`
  - `Z_ChangeTag` (macro, line 69) `#define Z_ChangeTag(p,t)`
- Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_iwad.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/f_finale.c`, `progs/doomgeneric/f_wipe.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/gusconf.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_minios_sound.c`, `progs/doomgeneric/i_scale.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/i_video.c`, `progs/doomgeneric/m_config.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/m_misc.c`, `progs/doomgeneric/memio.c`, `progs/doomgeneric/p_ceilng.c`, `progs/doomgeneric/p_doors.c`, `progs/doomgeneric/p_floor.c`, `progs/doomgeneric/p_lights.c`, `progs/doomgeneric/p_mobj.c`, `progs/doomgeneric/p_plats.c`, `progs/doomgeneric/p_saveg.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/p_tick.c`, `progs/doomgeneric/r_data.c`, `progs/doomgeneric/r_draw.c`, `progs/doomgeneric/r_plane.c`, `progs/doomgeneric/r_things.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/st_lib.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/v_video.c`, `progs/doomgeneric/w_file_stdc.c`, `progs/doomgeneric/w_main.c`, `progs/doomgeneric/w_wad.c`, `progs/doomgeneric/wi_stuff.c`, `progs/doomgeneric/z_zone.c`

