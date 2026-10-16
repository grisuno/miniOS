# Symbols (page 19 of 26)
Previous: [SYMBOLS_p18.md](SYMBOLS_p18.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `W_NWTMergeFile` | function | `progs/doomgeneric/w_merge.h:33` | `void W_NWTMergeFile(char *filename, int flags);` |
| `W_NWT_MERGE_FLATS` | macro | `progs/doomgeneric/w_merge.h:25` | `#define W_NWT_MERGE_FLATS` |
| `W_NWT_MERGE_SPRITES` | macro | `progs/doomgeneric/w_merge.h:24` | `#define W_NWT_MERGE_SPRITES` |
| `W_PrintDirectory` | function | `progs/doomgeneric/w_merge.h:41` | `void W_PrintDirectory(void);` |
| `ExtendLumpInfo` | function | `progs/doomgeneric/w_wad.c:89` | `static void ExtendLumpInfo(int newnumlumps)` |
| `I_EndRead` | function | `progs/doomgeneric/w_wad.c:39` | `void I_EndRead (void);` |
| `W_AddFile` | function | `progs/doomgeneric/w_wad.c:141` | `wad_file_t *W_AddFile (char *filename)` |
| `W_CacheLumpName` | function | `progs/doomgeneric/w_wad.c:431` | `void *W_CacheLumpName(char *name, int tag)` |
| `W_CacheLumpNum` | function | `progs/doomgeneric/w_wad.c:384` | `void *W_CacheLumpNum(int lumpnum, int tag)` |
| `W_CheckCorrectIWAD` | function | `progs/doomgeneric/w_wad.c:588` | `void W_CheckCorrectIWAD(GameMission_t mission)` |
| `W_CheckNumForName` | function | `progs/doomgeneric/w_wad.c:258` | `int W_CheckNumForName (char* name)` |
| `W_GenerateHashTable` | function | `progs/doomgeneric/w_wad.c:541` | `void W_GenerateHashTable(void)` |
| `W_GetNumForName` | function | `progs/doomgeneric/w_wad.c:308` | `int W_GetNumForName (char* name)` |
| `W_LumpLength` | function | `progs/doomgeneric/w_wad.c:327` | `int W_LumpLength (unsigned int lump)` |
| `W_LumpNameHash` | function | `progs/doomgeneric/w_wad.c:72` | `unsigned int W_LumpNameHash(const char *s)` |
| `W_NumLumps` | function | `progs/doomgeneric/w_wad.c:246` | `int W_NumLumps (void)` |
| `W_Profile` | function | `progs/doomgeneric/w_wad.c:480` | `void W_Profile (void)` |
| `W_ReadLump` | function | `progs/doomgeneric/w_wad.c:344` | `void W_ReadLump(unsigned int lump, void *dest)` |
| `W_ReleaseLumpName` | function | `progs/doomgeneric/w_wad.c:467` | `void W_ReleaseLumpName(char *name)` |
| `W_ReleaseLumpNum` | function | `progs/doomgeneric/w_wad.c:446` | `void W_ReleaseLumpNum(int lumpnum)` |
| `W_AddFile` | function | `progs/doomgeneric/w_wad.h:58` | `wad_file_t *W_AddFile (char *filename);` |
| `W_CacheLumpName` | function | `progs/doomgeneric/w_wad.h:67` | `void* W_CacheLumpName (char* name, int tag);` |
| `W_CacheLumpNum` | function | `progs/doomgeneric/w_wad.h:66` | `void* W_CacheLumpNum (int lump, int tag);` |
| `W_CheckCorrectIWAD` | function | `progs/doomgeneric/w_wad.h:76` | `void W_CheckCorrectIWAD(GameMission_t mission);` |
| `W_CheckNumForName` | function | `progs/doomgeneric/w_wad.h:60` | `int W_CheckNumForName (char* name);` |
| `W_GenerateHashTable` | function | `progs/doomgeneric/w_wad.h:69` | `void W_GenerateHashTable(void);` |
| `W_GetNumForName` | function | `progs/doomgeneric/w_wad.h:61` | `int W_GetNumForName (char* name);` |
| `W_LumpLength` | function | `progs/doomgeneric/w_wad.h:63` | `int W_LumpLength (unsigned int lump);` |
| `W_LumpNameHash` | function | `progs/doomgeneric/w_wad.h:71` | `extern unsigned int W_LumpNameHash(const char *s);` |
| `W_ReadLump` | function | `progs/doomgeneric/w_wad.h:64` | `void W_ReadLump (unsigned int lump, void *dest);` |
| `W_ReleaseLumpName` | function | `progs/doomgeneric/w_wad.h:74` | `void W_ReleaseLumpName(char *name);` |
| `W_ReleaseLumpNum` | function | `progs/doomgeneric/w_wad.h:73` | `void W_ReleaseLumpNum(int lump);` |
| `__W_WAD__` | macro | `progs/doomgeneric/w_wad.h:21` | `#define __W_WAD__` |
| `lumpinfo` | variable | `progs/doomgeneric/w_wad.h:55` | `extern lumpinfo_t *lumpinfo;` |
| `lumpinfo_s` | struct | `progs/doomgeneric/w_wad.h:41` | `` |
| `lumpinfo_t` | type_alias | `progs/doomgeneric/w_wad.h:38` | `typedef struct lumpinfo_s lumpinfo_t;` |
| `numlumps` | variable | `progs/doomgeneric/w_wad.h:56` | `extern unsigned int numlumps;` |
| `ANIM` | macro | `progs/doomgeneric/wi_stuff.c:222` | `#define ANIM(type, period, nanims, x, y, nexttic)` |
| `DM_KILLERSX` | macro | `progs/doomgeneric/wi_stuff.c:101` | `#define DM_KILLERSX` |
| `DM_KILLERSY` | macro | `progs/doomgeneric/wi_stuff.c:102` | `#define DM_KILLERSY` |
| `DM_MATRIXX` | macro | `progs/doomgeneric/wi_stuff.c:94` | `#define DM_MATRIXX` |
| `DM_MATRIXY` | macro | `progs/doomgeneric/wi_stuff.c:95` | `#define DM_MATRIXY` |
| `DM_SPACINGX` | macro | `progs/doomgeneric/wi_stuff.c:97` | `#define DM_SPACINGX` |
| `DM_TOTALSX` | macro | `progs/doomgeneric/wi_stuff.c:99` | `#define DM_TOTALSX` |
| `DM_VICTIMSX` | macro | `progs/doomgeneric/wi_stuff.c:103` | `#define DM_VICTIMSX` |
| `DM_VICTIMSY` | macro | `progs/doomgeneric/wi_stuff.c:104` | `#define DM_VICTIMSY` |
| `NG_SPACINGX` | macro | `progs/doomgeneric/wi_stuff.c:90` | `#define NG_SPACINGX` |
| `NG_STATSX` | macro | `progs/doomgeneric/wi_stuff.c:88` | `#define NG_STATSX` |
| `NG_STATSY` | macro | `progs/doomgeneric/wi_stuff.c:87` | `#define NG_STATSY` |
| `NUMEPISODES` | macro | `progs/doomgeneric/wi_stuff.c:61` | `#define NUMEPISODES` |
| `NUMMAPS` | macro | `progs/doomgeneric/wi_stuff.c:62` | `#define NUMMAPS` |
| `SHOWNEXTLOCDELAY` | macro | `progs/doomgeneric/wi_stuff.c:298` | `#define SHOWNEXTLOCDELAY` |
| `SP_FRAGS` | macro | `progs/doomgeneric/wi_stuff.c:291` | `#define SP_FRAGS` |
| `SP_ITEMS` | macro | `progs/doomgeneric/wi_stuff.c:289` | `#define SP_ITEMS` |
| `SP_KILLS` | macro | `progs/doomgeneric/wi_stuff.c:288` | `#define SP_KILLS` |
| `SP_PAR` | macro | `progs/doomgeneric/wi_stuff.c:293` | `#define SP_PAR` |
| `SP_PAUSE` | macro | `progs/doomgeneric/wi_stuff.c:295` | `#define SP_PAUSE` |
| `SP_SECRET` | macro | `progs/doomgeneric/wi_stuff.c:290` | `#define SP_SECRET` |
| `SP_STATSX` | macro | `progs/doomgeneric/wi_stuff.c:79` | `#define SP_STATSX` |
| `SP_STATSY` | macro | `progs/doomgeneric/wi_stuff.c:80` | `#define SP_STATSY` |
| `SP_TIME` | macro | `progs/doomgeneric/wi_stuff.c:292` | `#define SP_TIME` |
| `SP_TIMEX` | macro | `progs/doomgeneric/wi_stuff.c:82` | `#define SP_TIMEX` |
| `SP_TIMEY` | macro | `progs/doomgeneric/wi_stuff.c:83` | `#define SP_TIMEY` |
| `WI_Drawer` | function | `progs/doomgeneric/wi_stuff.c:1752` | `void WI_Drawer (void)` |
| `WI_End` | function | `progs/doomgeneric/wi_stuff.c:740` | `void WI_End(void)` |
| `WI_Responder` | function | `progs/doomgeneric/wi_stuff.c:409` | `boolean WI_Responder(event_t* ev)` |
| `WI_SPACINGY` | macro | `progs/doomgeneric/wi_stuff.c:76` | `#define WI_SPACINGY` |
| `WI_Start` | function | `progs/doomgeneric/wi_stuff.c:1818` | `void WI_Start(wbstartstruct_t* wbstartstruct)` |
| `WI_TITLEY` | macro | `progs/doomgeneric/wi_stuff.c:75` | `#define WI_TITLEY` |
| `WI_Ticker` | function | `progs/doomgeneric/wi_stuff.c:1514` | `void WI_Ticker(void)` |
| `WI_checkForAccelerate` | function | `progs/doomgeneric/wi_stuff.c:1481` | `void WI_checkForAccelerate(void)` |
| `WI_drawAnimatedBack` | function | `progs/doomgeneric/wi_stuff.c:599` | `void WI_drawAnimatedBack(void)` |
| `WI_drawDeathmatchStats` | function | `progs/doomgeneric/wi_stuff.c:1001` | `void WI_drawDeathmatchStats(void)` |
| `WI_drawEL` | function | `progs/doomgeneric/wi_stuff.c:452` | `void WI_drawEL(void)` |
| `WI_drawLF` | function | `progs/doomgeneric/wi_stuff.c:416` | `void WI_drawLF(void)` |
| `WI_drawNetgameStats` | function | `progs/doomgeneric/wi_stuff.c:1272` | `void WI_drawNetgameStats(void)` |
| `WI_drawNoState` | function | `progs/doomgeneric/wi_stuff.c:832` | `void WI_drawNoState(void)` |
| `WI_drawNum` | function | `progs/doomgeneric/wi_stuff.c:628` | `int WI_drawNum ( int		x,   int		y,   int		n,   int		digits )` |
| `WI_drawOnLnode` | function | `progs/doomgeneric/wi_stuff.c:471` | `void WI_drawOnLnode ( int		n,   patch_t*	c[] )` |
| `WI_drawPercent` | function | `progs/doomgeneric/wi_stuff.c:685` | `void WI_drawPercent ( int		x,   int		y,   int		p )` |
| `WI_drawShowNextLoc` | function | `progs/doomgeneric/wi_stuff.c:791` | `void WI_drawShowNextLoc(void)` |
| `WI_drawStats` | function | `progs/doomgeneric/wi_stuff.c:1447` | `void WI_drawStats(void)` |
| `WI_drawTime` | function | `progs/doomgeneric/wi_stuff.c:704` | `void WI_drawTime ( int		x,   int		y,   int		t )` |
| `WI_fragSum` | function | `progs/doomgeneric/wi_stuff.c:838` | `int WI_fragSum(int playernum)` |
| `WI_initAnimatedBack` | function | `progs/doomgeneric/wi_stuff.c:519` | `void WI_initAnimatedBack(void)` |
| `WI_initDeathmatchStats` | function | `progs/doomgeneric/wi_stuff.c:869` | `void WI_initDeathmatchStats(void)` |
| `WI_initNetgameStats` | function | `progs/doomgeneric/wi_stuff.c:1089` | `void WI_initNetgameStats(void)` |
| `WI_initNoState` | function | `progs/doomgeneric/wi_stuff.c:746` | `void WI_initNoState(void)` |
| `WI_initShowNextLoc` | function | `progs/doomgeneric/wi_stuff.c:772` | `void WI_initShowNextLoc(void)` |
| `WI_initStats` | function | `progs/doomgeneric/wi_stuff.c:1329` | `void WI_initStats(void)` |
| `WI_initVariables` | function | `progs/doomgeneric/wi_stuff.c:1776` | `void WI_initVariables(wbstartstruct_t* wbstartstruct)` |
| `WI_loadCallback` | function | `progs/doomgeneric/wi_stuff.c:1704` | `static void WI_loadCallback(char *name, patch_t **variable)` |
| `WI_loadData` | function | `progs/doomgeneric/wi_stuff.c:1709` | `void WI_loadData(void)` |
| `WI_loadUnloadData` | function | `progs/doomgeneric/wi_stuff.c:1554` | `static void WI_loadUnloadData(load_callback_t callback)` |
| `WI_slamBackground` | function | `progs/doomgeneric/wi_stuff.c:402` | `void WI_slamBackground(void)` |
| `WI_unloadCallback` | function | `progs/doomgeneric/wi_stuff.c:1735` | `static void WI_unloadCallback(char *name, patch_t **variable)` |
| `WI_unloadData` | function | `progs/doomgeneric/wi_stuff.c:1741` | `void WI_unloadData(void)` |
| `WI_updateAnimatedBack` | function | `progs/doomgeneric/wi_stuff.c:548` | `void WI_updateAnimatedBack(void)` |
| `WI_updateDeathmatchStats` | function | `progs/doomgeneric/wi_stuff.c:898` | `void WI_updateDeathmatchStats(void)` |
| `WI_updateNetgameStats` | function | `progs/doomgeneric/wi_stuff.c:1117` | `void WI_updateNetgameStats(void)` |
| `WI_updateNoState` | function | `progs/doomgeneric/wi_stuff.c:753` | `void WI_updateNoState(void)` |
| `WI_updateShowNextLoc` | function | `progs/doomgeneric/wi_stuff.c:781` | `void WI_updateShowNextLoc(void)` |
| `WI_updateStats` | function | `progs/doomgeneric/wi_stuff.c:1341` | `void WI_updateStats(void)` |
| `anim_t` | struct | `progs/doomgeneric/wi_stuff.c:129` | `` |
| `point_t` | struct | `progs/doomgeneric/wi_stuff.c:117` | `` |
| `WI_Drawer` | function | `progs/doomgeneric/wi_stuff.h:40` | `void WI_Drawer (void);` |
| `WI_End` | function | `progs/doomgeneric/wi_stuff.h:46` | `void WI_End(void);` |
| `WI_Start` | function | `progs/doomgeneric/wi_stuff.h:43` | `void WI_Start(wbstartstruct_t* wbstartstruct);` |
| `WI_Ticker` | function | `progs/doomgeneric/wi_stuff.h:36` | `void WI_Ticker (void);` |
| `__WI_STUFF__` | macro | `progs/doomgeneric/wi_stuff.h:20` | `#define __WI_STUFF__` |
| `MEM_ALIGN` | macro | `progs/doomgeneric/z_zone.c:36` | `#define MEM_ALIGN` |
| `MINFRAGMENT` | macro | `progs/doomgeneric/z_zone.c:181` | `#define MINFRAGMENT` |
| `ZONEID` | macro | `progs/doomgeneric/z_zone.c:37` | `#define ZONEID` |
| `Z_ChangeTag2` | function | `progs/doomgeneric/z_zone.c:429` | `void Z_ChangeTag2(void *ptr, int tag, char *file, int line)` |
| `Z_ChangeUser` | function | `progs/doomgeneric/z_zone.c:446` | `void Z_ChangeUser(void *ptr, void **user)` |
| `Z_CheckHeap` | function | `progs/doomgeneric/z_zone.c:400` | `void Z_CheckHeap (void)` |
| `Z_ClearZone` | function | `progs/doomgeneric/z_zone.c:71` | `void Z_ClearZone (memzone_t* zone)` |
| `Z_DumpHeap` | function | `progs/doomgeneric/z_zone.c:328` | `void Z_DumpHeap ( int		lowtag,   int		hightag )` |
| `Z_FileDumpHeap` | function | `progs/doomgeneric/z_zone.c:367` | `void Z_FileDumpHeap (FILE* f)` |
| `Z_Free` | function | `progs/doomgeneric/z_zone.c:126` | `void Z_Free (void* ptr)` |
| `Z_FreeMemory` | function | `progs/doomgeneric/z_zone.c:466` | `int Z_FreeMemory (void)` |
| `Z_FreeTags` | function | `progs/doomgeneric/z_zone.c:298` | `void Z_FreeTags ( int		lowtag,   int		hightag )` |
| `Z_Init` | function | `progs/doomgeneric/z_zone.c:97` | `void Z_Init (void)` |
| `Z_Malloc` | function | `progs/doomgeneric/z_zone.c:185` | `void* Z_Malloc ( int		size,   int		tag,   void*		user )` |
| `Z_ZoneSize` | function | `progs/doomgeneric/z_zone.c:484` | `unsigned int Z_ZoneSize(void)` |
| `memblock_s` | struct | `progs/doomgeneric/z_zone.c:39` | `` |
| `memzone_t` | struct | `progs/doomgeneric/z_zone.c:50` | `` |
| `size` | type_alias | `progs/doomgeneric/z_zone.c:38` | `typedef struct memblock_s { int size;` |
| `Z_ChangeTag` | macro | `progs/doomgeneric/z_zone.h:69` | `#define Z_ChangeTag(p,t)` |
| `Z_ChangeTag2` | function | `progs/doomgeneric/z_zone.h:60` | `void Z_ChangeTag2 (void *ptr, int tag, char *file, int line);` |
| `Z_ChangeUser` | function | `progs/doomgeneric/z_zone.h:61` | `void Z_ChangeUser(void *ptr, void **user);` |
| `Z_CheckHeap` | function | `progs/doomgeneric/z_zone.h:59` | `void Z_CheckHeap (void);` |
| `Z_DumpHeap` | function | `progs/doomgeneric/z_zone.h:57` | `void Z_DumpHeap (int lowtag, int hightag);` |
| `Z_FileDumpHeap` | function | `progs/doomgeneric/z_zone.h:58` | `void Z_FileDumpHeap (FILE *f);` |
| `Z_Free` | function | `progs/doomgeneric/z_zone.h:55` | `void Z_Free (void *ptr);` |
| `Z_FreeMemory` | function | `progs/doomgeneric/z_zone.h:62` | `int Z_FreeMemory (void);` |
| `Z_FreeTags` | function | `progs/doomgeneric/z_zone.h:56` | `void Z_FreeTags (int lowtag, int hightag);` |
| `Z_Init` | function | `progs/doomgeneric/z_zone.h:53` | `void Z_Init (void);` |
| `Z_Malloc` | function | `progs/doomgeneric/z_zone.h:54` | `void* Z_Malloc (int size, int tag, void *ptr);` |
| `Z_ZoneSize` | function | `progs/doomgeneric/z_zone.h:63` | `unsigned int Z_ZoneSize(void);` |
| `__Z_ZONE__` | macro | `progs/doomgeneric/z_zone.h:25` | `#define __Z_ZONE__` |
| `FILE_ACTION_INTERNAL` | macro | `progs/file/file.c:49` | `#define FILE_ACTION_INTERNAL` |
| `FILE_ACTION_SHELL` | macro | `progs/file/file.c:48` | `#define FILE_ACTION_SHELL` |
| `FILE_ACT_INTERNAL` | macro | `progs/file/file.c:73` | `#define FILE_ACT_INTERNAL` |
| `FILE_ACT_SHELL` | macro | `progs/file/file.c:72` | `#define FILE_ACT_SHELL` |
| `FILE_ACT_TEXT` | macro | `progs/file/file.c:71` | `#define FILE_ACT_TEXT` |
| `FILE_ACT_UNKNOWN` | macro | `progs/file/file.c:74` | `#define FILE_ACT_UNKNOWN` |
| `FILE_ASSOC_PATH` | macro | `progs/file/file.c:37` | `#define FILE_ASSOC_PATH` |
| `FILE_EXT_MAX` | macro | `progs/file/file.c:38` | `#define FILE_EXT_MAX` |
| `FILE_ICON_BIG` | macro | `progs/file/file.c:58` | `#define FILE_ICON_BIG` |
| `FILE_ICON_FILES` | macro | `progs/file/file.c:62` | `#define FILE_ICON_FILES` |
| `FILE_ICON_FOLDER` | macro | `progs/file/file.c:61` | `#define FILE_ICON_FOLDER` |
| `FILE_ICON_IMAGE` | macro | `progs/file/file.c:63` | `#define FILE_ICON_IMAGE` |
| `FILE_ICON_MAX` | macro | `progs/file/file.c:59` | `#define FILE_ICON_MAX` |
| `FILE_ICON_N` | macro | `progs/file/file.c:60` | `#define FILE_ICON_N` |
| `FILE_ICON_OBJECT` | macro | `progs/file/file.c:64` | `#define FILE_ICON_OBJECT` |
| `FILE_ICON_PATH_FILES` | macro | `progs/file/file.c:66` | `#define FILE_ICON_PATH_FILES` |
| `FILE_ICON_PATH_FOLDER` | macro | `progs/file/file.c:65` | `#define FILE_ICON_PATH_FOLDER` |
| `FILE_ICON_PATH_IMAGE` | macro | `progs/file/file.c:67` | `#define FILE_ICON_PATH_IMAGE` |
| `FILE_ICON_PATH_OBJECT` | macro | `progs/file/file.c:68` | `#define FILE_ICON_PATH_OBJECT` |
| `FILE_ICON_SMALL` | macro | `progs/file/file.c:57` | `#define FILE_ICON_SMALL` |
| `FILE_LIST_CAP` | macro | `progs/file/file.c:36` | `#define FILE_LIST_CAP` |
| `FILE_LOG_LINE` | macro | `progs/file/file.c:50` | `#define FILE_LOG_LINE` |
| `FILE_MAX_ENTRIES` | macro | `progs/file/file.c:34` | `#define FILE_MAX_ENTRIES` |
| `FILE_MAX_PATH` | macro | `progs/file/file.c:33` | `#define FILE_MAX_PATH` |
| `FILE_NAME_MAX` | macro | `progs/file/file.c:35` | `#define FILE_NAME_MAX` |
| `FILE_PREVIEW_FILE_MAX` | macro | `progs/file/file.c:46` | `#define FILE_PREVIEW_FILE_MAX` |
| `FILE_PREVIEW_H` | macro | `progs/file/file.c:45` | `#define FILE_PREVIEW_H` |
| `FILE_PREVIEW_W` | macro | `progs/file/file.c:44` | `#define FILE_PREVIEW_W` |
| `FILE_PROG_MAX` | macro | `progs/file/file.c:39` | `#define FILE_PROG_MAX` |
| `FILE_STATUS_MAX` | macro | `progs/file/file.c:42` | `#define FILE_STATUS_MAX` |
| `FILE_TITLE` | macro | `progs/file/file.c:47` | `#define FILE_TITLE` |
| `FILE_TOOL_CVM` | macro | `progs/file/file.c:41` | `#define FILE_TOOL_CVM` |
| `FILE_TOOL_VEDIT` | macro | `progs/file/file.c:40` | `#define FILE_TOOL_VEDIT` |
| `FILE_UI_MEMORY` | macro | `progs/file/file.c:43` | `#define FILE_UI_MEMORY` |
| `MINIOS_LEAKCHECK_IMPL` | macro | `progs/file/file.c:28` | `#define MINIOS_LEAKCHECK_IMPL` |
| `MINIOS_LK_ENABLE` | macro | `progs/file/file.c:29` | `#define MINIOS_LK_ENABLE` |
| `STBI_NO_STDIO` | macro | `progs/file/file.c:26` | `#define STBI_NO_STDIO` |
| `STBI_ONLY_PNG` | macro | `progs/file/file.c:25` | `#define STBI_ONLY_PNG` |
| `STB_IMAGE_IMPLEMENTATION` | macro | `progs/file/file.c:24` | `#define STB_IMAGE_IMPLEMENTATION` |
| `file_action_of` | function | `progs/file/file.c:323` | `static int file_action_of(const char *fname, const char **prog_out)` |
| `file_activate` | function | `progs/file/file.c:480` | `static void file_activate(const char *dir, const char *name)` |
| `file_assoc` | struct | `progs/file/file.c:76` | `` |
| `file_assoc_line` | function | `progs/file/file.c:269` | `static int file_assoc_line(const char *line, char *ext, char *prog)` |
| `file_assoc_load` | function | `progs/file/file.c:302` | `static void file_assoc_load(void)` |
| `file_assoc_lookup` | function | `progs/file/file.c:318` | `static const char *file_assoc_lookup(const char *ext)` |
| `file_ext_of` | function | `progs/file/file.c:122` | `static void file_ext_of(const char *fname, char *dst, unsigned cap)` |
| `file_gui_run` | function | `progs/file/file.c:779` | `static void file_gui_run(void)` |
| `file_icon_decode` | function | `progs/file/file.c:165` | `static int file_icon_decode(const char *path, unsigned char *px,                             unsi...` |
| `file_icon_kind` | function | `progs/file/file.c:146` | `static int file_icon_kind(const char *fname, int isdir)` |
| `file_icon_sz` | function | `progs/file/file.c:158` | `static int file_icon_sz(void)` |
| `file_icons_load` | function | `progs/file/file.c:213` | `static int file_icons_load(void)` |
| `file_join` | function | `progs/file/file.c:245` | `static int file_join(const char *dir, const char *name, char *dst, unsigned cap)` |
| `file_open_text` | function | `progs/file/file.c:430` | `static void file_open_text(const char *path)` |
| `file_parent` | function | `progs/file/file.c:259` | `static void file_parent(char *path)` |
| `file_preview_blit` | function | `progs/file/file.c:385` | `static void file_preview_blit(int ox, int oy)` |
| `file_preview_load` | function | `progs/file/file.c:351` | `static int file_preview_load(const char *path)` |
| `file_refresh` | function | `progs/file/file.c:336` | `static void file_refresh(void)` |
| `file_run_shell` | function | `progs/file/file.c:441` | `static void file_run_shell(const char *path)` |
| `file_selftest` | function | `progs/file/file.c:613` | `static int file_selftest(void)` |
| `file_spawn_visible` | function | `progs/file/file.c:407` | `static long file_spawn_visible(const char *tool, int argc, const char **argv,                    ...` |
| `file_sys_dir_list` | function | `progs/file/file.c:101` | `static long file_sys_dir_list(const char *path, char *buf, long cap)` |
| `file_sys_spawn` | function | `progs/file/file.c:111` | `static long file_sys_spawn(const char *path, int argc, const char **argv)` |
| `file_toggle_icons` | function | `progs/file/file.c:238` | `static int file_toggle_icons(void)` |
| `file_ui_build` | function | `progs/file/file.c:511` | `static void file_ui_build(struct nk_context *ctx)` |
| `main` | function | `progs/file/file.c:838` | `int main(int argc, char **argv)` |
| `FASSOC_EXT_MAX` | macro | `progs/file/file_assoc.h:22` | `#define FASSOC_EXT_MAX` |
| `FASSOC_GROW_DEN` | macro | `progs/file/file_assoc.h:42` | `#define FASSOC_GROW_DEN` |
| `FASSOC_GROW_NUM` | macro | `progs/file/file_assoc.h:38` | `#define FASSOC_GROW_NUM` |
| `FASSOC_HARD_MAX` | macro | `progs/file/file_assoc.h:34` | `#define FASSOC_HARD_MAX` |
| `FASSOC_INIT_CAP` | macro | `progs/file/file_assoc.h:30` | `#define FASSOC_INIT_CAP` |
| `FASSOC_PROG_MAX` | macro | `progs/file/file_assoc.h:26` | `#define FASSOC_PROG_MAX` |
| `MINIOS_FILE_ASSOC_H` | macro | `progs/file/file_assoc.h:15` | `#define MINIOS_FILE_ASSOC_H` |
| `fassoc_clear` | function | `progs/file/file_assoc.h:89` | `static void fassoc_clear(struct fassoc_table *t)` |
| `fassoc_count` | function | `progs/file/file_assoc.h:150` | `static size_t fassoc_count(const struct fassoc_table *t)` |
| `fassoc_entry` | struct | `progs/file/file_assoc.h:46` | `` |
| `fassoc_ext_ok` | function | `progs/file/file_assoc.h:59` | `static int fassoc_ext_ok(const char *ext)` |
| `fassoc_free` | function | `progs/file/file_assoc.h:95` | `static void fassoc_free(struct fassoc_table *t)` |
| `fassoc_lookup` | function | `progs/file/file_assoc.h:140` | `static const char *fassoc_lookup(const struct fassoc_table *t, const char *ext)` |
| `fassoc_prog_ok` | function | `progs/file/file_assoc.h:73` | `static int fassoc_prog_ok(const char *prog)` |
| `fassoc_push` | function | `progs/file/file_assoc.h:125` | `static int fassoc_push(struct fassoc_table *t, const char *ext, const char *prog)` |
| `fassoc_reserve` | function | `progs/file/file_assoc.h:104` | `static int fassoc_reserve(struct fassoc_table *t, size_t want)` |
| `fassoc_table` | struct | `progs/file/file_assoc.h:52` | `` |
| `FUI_BODY_CAP` | macro | `progs/freedomui/freedomui_minios.c:53` | `#define FUI_BODY_CAP` |
| `FUI_COLS` | macro | `progs/freedomui/freedomui_minios.c:51` | `#define FUI_COLS` |
| `FUI_FONT_H` | macro | `progs/freedomui/freedomui_minios.c:62` | `#define FUI_FONT_H` |
| `FUI_FONT_W` | macro | `progs/freedomui/freedomui_minios.c:61` | `#define FUI_FONT_W` |
| `FUI_HDR_MAX` | macro | `progs/freedomui/freedomui_minios.c:54` | `#define FUI_HDR_MAX` |
| `FUI_HOPS_MAX` | macro | `progs/freedomui/freedomui_minios.c:60` | `#define FUI_HOPS_MAX` |
| `FUI_HOST_MAX` | macro | `progs/freedomui/freedomui_minios.c:57` | `#define FUI_HOST_MAX` |
| `FUI_NET_BUF` | macro | `progs/freedomui/freedomui_minios.c:55` | `#define FUI_NET_BUF` |
| `FUI_PATH_MAX` | macro | `progs/freedomui/freedomui_minios.c:58` | `#define FUI_PATH_MAX` |
| `FUI_REQ_MAX` | macro | `progs/freedomui/freedomui_minios.c:56` | `#define FUI_REQ_MAX` |
| `FUI_TEXT_ROWS` | macro | `progs/freedomui/freedomui_minios.c:52` | `#define FUI_TEXT_ROWS` |
| `FUI_TITLE_MAX` | macro | `progs/freedomui/freedomui_minios.c:63` | `#define FUI_TITLE_MAX` |
| `FUI_URL_MAX` | macro | `progs/freedomui/freedomui_minios.c:59` | `#define FUI_URL_MAX` |
| `FreedomUiConfig` | struct | `progs/freedomui/freedomui_minios.c:69` | `` |
| `freedomui_build_palette` | function | `progs/freedomui/freedomui_minios.c:130` | `static long freedomui_build_palette(unsigned char *pal, long cap)` |
| `freedomui_default` | function | `progs/freedomui/freedomui_minios.c:97` | `static FreedomUiConfig freedomui_default(void)` |
| `freedomui_engine_text` | function | `progs/freedomui/freedomui_minios.c:145` | `static long freedomui_engine_text(char *body, long n, char **title, char **text)` |
| `freedomui_host_entry` | function | `progs/freedomui/freedomui_minios.c:1067` | `int freedomui_host_entry(FreedomUiConfig *c)` |
| `freedomui_host_probe` | function | `progs/freedomui/freedomui_minios.c:984` | `static long freedomui_host_probe(FreedomUiConfig *c)` |
| `freedomui_selftest` | function | `progs/freedomui/freedomui_minios.c:896` | `static long freedomui_selftest(void)` |
| `freedomui_sys_kbd` | function | `progs/freedomui/freedomui_minios.c:221` | `static long freedomui_sys_kbd(void)` |
| `freedomui_sys_kbd_raw` | function | `progs/freedomui/freedomui_minios.c:235` | `static long freedomui_sys_kbd_raw(long on)` |
| `freedomui_sys_mouse` | function | `progs/freedomui/freedomui_minios.c:214` | `static long freedomui_sys_mouse(long *m)` |
| `freedomui_sys_palette` | function | `progs/freedomui/freedomui_minios.c:207` | `static long freedomui_sys_palette(unsigned char *pal)` |
| `freedomui_sys_present` | function | `progs/freedomui/freedomui_minios.c:193` | `static long freedomui_sys_present(long buf, long origin)` |
| `freedomui_sys_title` | function | `progs/freedomui/freedomui_minios.c:200` | `static long freedomui_sys_title(char *t)` |
| `freedomui_sys_vga_mode` | function | `progs/freedomui/freedomui_minios.c:228` | `static long freedomui_sys_vga_mode(long on)` |
| `freedomui_sys_yield` | function | `progs/freedomui/freedomui_minios.c:242` | `static long freedomui_sys_yield(void)` |
| `fui_append` | function | `progs/freedomui/freedomui_minios.c:249` | `static long fui_append(char *dst, long pos, char *src, long cap)` |
| `fui_browse` | function | `progs/freedomui/freedomui_minios.c:817` | `static long fui_browse(FreedomUiConfig *c)` |
| `fui_fetch_raw` | function | `progs/freedomui/freedomui_minios.c:470` | `static long fui_fetch_raw(FreedomUiConfig *c, char *host, char *path, long port, long secure)` |
| `fui_parse_headers` | function | `progs/freedomui/freedomui_minios.c:352` | `static long fui_parse_headers(FreedomUiConfig *c, char *hdr, long *status, long *clen, long *hasc...` |
| `fui_render` | function | `progs/freedomui/freedomui_minios.c:698` | `static long fui_render(FreedomUiConfig *c, size_t off)` |
| `fui_split_url` | function | `progs/freedomui/freedomui_minios.c:283` | `static long fui_split_url(FreedomUiConfig *c, char *url, char *host, char *path, long *port, long...` |
| `fui_strlen` | function | `progs/freedomui/freedomui_minios.c:267` | `static long fui_strlen(char *s, long cap)` |
| `main` | function | `progs/freedomui/freedomui_minios.c:1072` | `int main(int argc, char **argv)` |
| `net_dns_resolve` | function | `progs/freedomui/freedomui_minios.c:44` | `int net_dns_resolve(const char *host);` |
| `present_buf` | type_alias | `progs/freedomui/freedomui_minios.c:69` | `typedef struct FreedomUiConfig { long present_buf;` |
| `tls_close` | function | `progs/freedomui/freedomui_minios.c:48` | `void tls_close(int fd);` |
| `tls_handshake` | function | `progs/freedomui/freedomui_minios.c:45` | `int tls_handshake(int fd, char *host);` |
| `tls_recv` | function | `progs/freedomui/freedomui_minios.c:47` | `int tls_recv(int fd, char *buf, int len);` |
| `tls_send` | function | `progs/freedomui/freedomui_minios.c:46` | `int tls_send(int fd, char *buf, int len);` |
| `media_decoder_run` | function | `progs/freedomui/media_unavailable.c:41` | `void media_decoder_run(int out_fd, int cmd_fd)` |
| `write_all` | function | `progs/freedomui/media_unavailable.c:20` | `static void write_all(int fd, const void *buf, size_t len)` |
| `FREEDOM_GUI_BUTTONS` | macro | `progs/freedomui/platform_minios.c:44` | `#define FREEDOM_GUI_BUTTONS` |
| `FREEDOM_GUI_CLIP_MAX` | macro | `progs/freedomui/platform_minios.c:33` | `#define FREEDOM_GUI_CLIP_MAX` |
| `FREEDOM_GUI_KBD_DRAIN_MAX` | macro | `progs/freedomui/platform_minios.c:29` | `#define FREEDOM_GUI_KBD_DRAIN_MAX` |
| `FREEDOM_GUI_KEY_F4` | macro | `progs/freedomui/platform_minios.c:46` | `#define FREEDOM_GUI_KEY_F4` |
| `FREEDOM_GUI_MALLOC_ARENAS` | macro | `progs/freedomui/platform_minios.c:35` | `#define FREEDOM_GUI_MALLOC_ARENAS` |
| `FREEDOM_GUI_MOUSE_BUTTONS` | macro | `progs/freedomui/platform_minios.c:41` | `#define FREEDOM_GUI_MOUSE_BUTTONS` |
| `FREEDOM_GUI_MOUSE_WHEEL` | macro | `progs/freedomui/platform_minios.c:42` | `#define FREEDOM_GUI_MOUSE_WHEEL` |
| `FREEDOM_GUI_MOUSE_WORDS` | macro | `progs/freedomui/platform_minios.c:38` | `#define FREEDOM_GUI_MOUSE_WORDS` |
| `FREEDOM_GUI_MOUSE_X` | macro | `progs/freedomui/platform_minios.c:39` | `#define FREEDOM_GUI_MOUSE_X` |
| `FREEDOM_GUI_MOUSE_Y` | macro | `progs/freedomui/platform_minios.c:40` | `#define FREEDOM_GUI_MOUSE_Y` |
| `FREEDOM_GUI_RGB_BPP` | macro | `progs/freedomui/platform_minios.c:48` | `#define FREEDOM_GUI_RGB_BPP` |
| `FREEDOM_GUI_RGB_PRESENT` | macro | `progs/freedomui/platform_minios.c:50` | `#define FREEDOM_GUI_RGB_PRESENT` |
| `FREEDOM_GUI_TICK_MS` | macro | `progs/freedomui/platform_minios.c:27` | `#define FREEDOM_GUI_TICK_MS` |
| `FREEDOM_GUI_TITLE_MAX` | macro | `progs/freedomui/platform_minios.c:31` | `#define FREEDOM_GUI_TITLE_MAX` |
| `_GNU_SOURCE` | macro | `progs/freedomui/platform_minios.c:11` | `#define _GNU_SOURCE` |
| `deliver_pending` | function | `progs/freedomui/platform_minios.c:173` | `static int deliver_pending(pf_display *d)` |
| `key_event` | function | `progs/freedomui/platform_minios.c:183` | `static void key_event(pf_display *d, const ps2_key *k, int kind)` |
| `minios_process_note` | struct | `progs/freedomui/platform_minios.c:124` | `` |
| `now_ms` | function | `progs/freedomui/platform_minios.c:94` | `static long now_ms(void)` |
| `pf_clipboard_available` | function | `progs/freedomui/platform_minios.c:292` | `int pf_clipboard_available(const pf_display *d)` |
| `pf_clipboard_get_text` | function | `progs/freedomui/platform_minios.c:303` | `pf_status pf_clipboard_get_text(pf_display *d, char **out, size_t *out_len)` |
| `pf_clipboard_set_text` | function | `progs/freedomui/platform_minios.c:296` | `pf_status pf_clipboard_set_text(pf_display *d, const char *text)` |
| `pf_display` | struct | `progs/freedomui/platform_minios.c:68` | `` |
| `pf_display_close` | function | `progs/freedomui/platform_minios.c:153` | `void pf_display_close(pf_display *d)` |
| `pf_display_flush` | function | `progs/freedomui/platform_minios.c:162` | `void pf_display_flush(pf_display *d)` |
| `pf_display_open` | function | `progs/freedomui/platform_minios.c:137` | `pf_status pf_display_open(pf_display **out)` |
| `pf_display_set_cursor` | function | `progs/freedomui/platform_minios.c:166` | `void pf_display_set_cursor(pf_display *d, pf_cursor c)` |
| `pf_display_wait` | function | `progs/freedomui/platform_minios.c:267` | `int pf_display_wait(pf_display *d, struct pollfd *extra, int n, int timeout_ms)` |
| `pf_window` | struct | `progs/freedomui/platform_minios.c:56` | `` |
| `pf_window_begin_move` | function | `progs/freedomui/platform_minios.c:434` | `void pf_window_begin_move(pf_window *w)` |
| `pf_window_begin_resize` | function | `progs/freedomui/platform_minios.c:438` | `void pf_window_begin_resize(pf_window *w, pf_edge edge)` |
| `pf_window_close` | function | `progs/freedomui/platform_minios.c:341` | `void pf_window_close(pf_window *w)` |
| `pf_window_minimize` | function | `progs/freedomui/platform_minios.c:430` | `void pf_window_minimize(pf_window *w)` |
| `pf_window_open` | function | `progs/freedomui/platform_minios.c:319` | `pf_status pf_window_open(pf_display *d, const pf_window_opts *o,                          const p...` |
| `pf_window_present` | function | `progs/freedomui/platform_minios.c:373` | `void pf_window_present(pf_window *w)` |
| `pf_window_set_fullscreen` | function | `progs/freedomui/platform_minios.c:426` | `void pf_window_set_fullscreen(pf_window *w, int on)` |
| `pf_window_set_maximized` | function | `progs/freedomui/platform_minios.c:422` | `void pf_window_set_maximized(pf_window *w, int on)` |
| `pf_window_set_title` | function | `progs/freedomui/platform_minios.c:407` | `void pf_window_set_title(pf_window *w, const char *title)` |
| `pf_window_surface` | function | `progs/freedomui/platform_minios.c:358` | `cairo_surface_t *pf_window_surface(pf_window *w, int width, int height)` |
| `pump_keyboard` | function | `progs/freedomui/platform_minios.c:210` | `static int pump_keyboard(pf_display *d)` |
| `pump_mouse` | function | `progs/freedomui/platform_minios.c:224` | `static int pump_mouse(pf_display *d)` |
| `set_title` | function | `progs/freedomui/platform_minios.c:98` | `static void set_title(const char *title)` |
| `set_zoom_state` | function | `progs/freedomui/platform_minios.c:413` | `static void set_zoom_state(pf_window *w, unsigned bit, int on)` |
| `sys_fb_info_rgb` | function | `progs/freedomui/platform_minios.c:83` | `static long sys_fb_info_rgb(int *rgb)` |
| `ASCII_BS` | macro | `progs/freedomui/ps2_keymap.c:84` | `#define ASCII_BS` |
| `ASCII_CR` | macro | `progs/freedomui/ps2_keymap.c:86` | `#define ASCII_CR` |
| `ASCII_DEL` | macro | `progs/freedomui/ps2_keymap.c:88` | `#define ASCII_DEL` |
| `ASCII_ESC` | macro | `progs/freedomui/ps2_keymap.c:87` | `#define ASCII_ESC` |
| `ASCII_TAB` | macro | `progs/freedomui/ps2_keymap.c:85` | `#define ASCII_TAB` |
| `KS_F1` | macro | `progs/freedomui/ps2_keymap.c:61` | `#define KS_F1` |
| `KS_F11` | macro | `progs/freedomui/ps2_keymap.c:62` | `#define KS_F11` |
| `KS_INSERT` | macro | `progs/freedomui/ps2_keymap.c:63` | `#define KS_INSERT` |
| `KS_KP_BEGIN` | macro | `progs/freedomui/ps2_keymap.c:78` | `#define KS_KP_BEGIN` |
| `KS_KP_DECIMAL` | macro | `progs/freedomui/ps2_keymap.c:81` | `#define KS_KP_DECIMAL` |
| `KS_KP_DIVIDE` | macro | `progs/freedomui/ps2_keymap.c:82` | `#define KS_KP_DIVIDE` |
| `KS_KP_DOWN` | macro | `progs/freedomui/ps2_keymap.c:74` | `#define KS_KP_DOWN` |
| `KS_KP_END` | macro | `progs/freedomui/ps2_keymap.c:77` | `#define KS_KP_END` |
| `KS_KP_HOME` | macro | `progs/freedomui/ps2_keymap.c:70` | `#define KS_KP_HOME` |
| `KS_KP_INSERT` | macro | `progs/freedomui/ps2_keymap.c:79` | `#define KS_KP_INSERT` |
| `KS_KP_LEFT` | macro | `progs/freedomui/ps2_keymap.c:71` | `#define KS_KP_LEFT` |
| `KS_KP_MULTIPLY` | macro | `progs/freedomui/ps2_keymap.c:80` | `#define KS_KP_MULTIPLY` |
| `KS_KP_NEXT` | macro | `progs/freedomui/ps2_keymap.c:76` | `#define KS_KP_NEXT` |
| `KS_KP_PRIOR` | macro | `progs/freedomui/ps2_keymap.c:75` | `#define KS_KP_PRIOR` |
| `KS_KP_RIGHT` | macro | `progs/freedomui/ps2_keymap.c:73` | `#define KS_KP_RIGHT` |
| `KS_KP_UP` | macro | `progs/freedomui/ps2_keymap.c:72` | `#define KS_KP_UP` |
| `KS_MENU` | macro | `progs/freedomui/ps2_keymap.c:65` | `#define KS_MENU` |
| `KS_NUM_LOCK` | macro | `progs/freedomui/ps2_keymap.c:67` | `#define KS_NUM_LOCK` |
| `KS_PRINT` | macro | `progs/freedomui/ps2_keymap.c:64` | `#define KS_PRINT` |
| `KS_SCROLL_LOCK` | macro | `progs/freedomui/ps2_keymap.c:66` | `#define KS_SCROLL_LOCK` |
| `KS_SUPER_L` | macro | `progs/freedomui/ps2_keymap.c:68` | `#define KS_SUPER_L` |
| `KS_SUPER_R` | macro | `progs/freedomui/ps2_keymap.c:69` | `#define KS_SUPER_R` |
| `PS2_BREAK_BIT` | macro | `progs/freedomui/ps2_keymap.c:16` | `#define PS2_BREAK_BIT` |
| `PS2_CODE_MASK` | macro | `progs/freedomui/ps2_keymap.c:17` | `#define PS2_CODE_MASK` |
| `PS2_HELD_LALT` | macro | `progs/freedomui/ps2_keymap.c:24` | `#define PS2_HELD_LALT` |
| `PS2_HELD_LCTRL` | macro | `progs/freedomui/ps2_keymap.c:22` | `#define PS2_HELD_LCTRL` |
| `PS2_HELD_LSHIFT` | macro | `progs/freedomui/ps2_keymap.c:20` | `#define PS2_HELD_LSHIFT` |
| `PS2_HELD_RALT` | macro | `progs/freedomui/ps2_keymap.c:25` | `#define PS2_HELD_RALT` |
| `PS2_HELD_RCTRL` | macro | `progs/freedomui/ps2_keymap.c:23` | `#define PS2_HELD_RCTRL` |
| `PS2_HELD_RSHIFT` | macro | `progs/freedomui/ps2_keymap.c:21` | `#define PS2_HELD_RSHIFT` |
| `PS2_PAUSE_TAIL` | macro | `progs/freedomui/ps2_keymap.c:15` | `#define PS2_PAUSE_TAIL` |
| `PS2_PREFIX_EXTENDED` | macro | `progs/freedomui/ps2_keymap.c:13` | `#define PS2_PREFIX_EXTENDED` |
| `PS2_PREFIX_PAUSE` | macro | `progs/freedomui/ps2_keymap.c:14` | `#define PS2_PREFIX_PAUSE` |
| `PS2_TABLE_SIZE` | macro | `progs/freedomui/ps2_keymap.c:18` | `#define PS2_TABLE_SIZE` |
| `SC_ALT` | macro | `progs/freedomui/ps2_keymap.c:35` | `#define SC_ALT` |
| `SC_BACKSPACE` | macro | `progs/freedomui/ps2_keymap.c:28` | `#define SC_BACKSPACE` |
| `SC_CAPS` | macro | `progs/freedomui/ps2_keymap.c:36` | `#define SC_CAPS` |
| `SC_CTRL` | macro | `progs/freedomui/ps2_keymap.c:31` | `#define SC_CTRL` |
| `SC_E0_DELETE` | macro | `progs/freedomui/ps2_keymap.c:56` | `#define SC_E0_DELETE` |
| `SC_E0_DOWN` | macro | `progs/freedomui/ps2_keymap.c:53` | `#define SC_E0_DOWN` |
| `SC_E0_END` | macro | `progs/freedomui/ps2_keymap.c:52` | `#define SC_E0_END` |
| `SC_E0_HOME` | macro | `progs/freedomui/ps2_keymap.c:47` | `#define SC_E0_HOME` |
| `SC_E0_INSERT` | macro | `progs/freedomui/ps2_keymap.c:55` | `#define SC_E0_INSERT` |
| `SC_E0_KP_DIV` | macro | `progs/freedomui/ps2_keymap.c:45` | `#define SC_E0_KP_DIV` |
| `SC_E0_LEFT` | macro | `progs/freedomui/ps2_keymap.c:50` | `#define SC_E0_LEFT` |
| `SC_E0_MENU` | macro | `progs/freedomui/ps2_keymap.c:59` | `#define SC_E0_MENU` |
| `SC_E0_NEXT` | macro | `progs/freedomui/ps2_keymap.c:54` | `#define SC_E0_NEXT` |
| `SC_E0_PRINT` | macro | `progs/freedomui/ps2_keymap.c:46` | `#define SC_E0_PRINT` |
| `SC_E0_PRIOR` | macro | `progs/freedomui/ps2_keymap.c:49` | `#define SC_E0_PRIOR` |
| `SC_E0_RIGHT` | macro | `progs/freedomui/ps2_keymap.c:51` | `#define SC_E0_RIGHT` |
| `SC_E0_SUPERL` | macro | `progs/freedomui/ps2_keymap.c:57` | `#define SC_E0_SUPERL` |
| `SC_E0_SUPERR` | macro | `progs/freedomui/ps2_keymap.c:58` | `#define SC_E0_SUPERR` |
| `SC_E0_UP` | macro | `progs/freedomui/ps2_keymap.c:48` | `#define SC_E0_UP` |
| `SC_ESCAPE` | macro | `progs/freedomui/ps2_keymap.c:27` | `#define SC_ESCAPE` |
| `SC_F1` | macro | `progs/freedomui/ps2_keymap.c:37` | `#define SC_F1` |
| `SC_F10` | macro | `progs/freedomui/ps2_keymap.c:38` | `#define SC_F10` |
| `SC_F11` | macro | `progs/freedomui/ps2_keymap.c:43` | `#define SC_F11` |
| `SC_F12` | macro | `progs/freedomui/ps2_keymap.c:44` | `#define SC_F12` |
| `SC_KP_FIRST` | macro | `progs/freedomui/ps2_keymap.c:41` | `#define SC_KP_FIRST` |
| `SC_KP_LAST` | macro | `progs/freedomui/ps2_keymap.c:42` | `#define SC_KP_LAST` |
| `SC_KP_MUL` | macro | `progs/freedomui/ps2_keymap.c:34` | `#define SC_KP_MUL` |
| `SC_LSHIFT` | macro | `progs/freedomui/ps2_keymap.c:32` | `#define SC_LSHIFT` |
| `SC_NUMLOCK` | macro | `progs/freedomui/ps2_keymap.c:39` | `#define SC_NUMLOCK` |
| `SC_RETURN` | macro | `progs/freedomui/ps2_keymap.c:30` | `#define SC_RETURN` |
| `SC_RSHIFT` | macro | `progs/freedomui/ps2_keymap.c:33` | `#define SC_RSHIFT` |
| `SC_SCROLL` | macro | `progs/freedomui/ps2_keymap.c:40` | `#define SC_SCROLL` |
| `SC_TAB` | macro | `progs/freedomui/ps2_keymap.c:29` | `#define SC_TAB` |
| `extended_key` | function | `progs/freedomui/ps2_keymap.c:195` | `static uint32_t extended_key(unsigned code, ps2_key *k)` |
| `held_mods` | function | `progs/freedomui/ps2_keymap.c:150` | `static unsigned held_mods(const ps2_state *s)` |
| `is_letter` | function | `progs/freedomui/ps2_keymap.c:164` | `static int is_letter(char c)` |
| `modifier_key` | function | `progs/freedomui/ps2_keymap.c:169` | `static uint32_t modifier_key(ps2_state *s, unsigned code, int extended, int make)` |
| `num_sym` | type_alias | `progs/freedomui/ps2_keymap.c:122` | `typedef struct ps2_keypad { uint32_t num_sym;` |
| `plain_key` | function | `progs/freedomui/ps2_keymap.c:218` | `static uint32_t plain_key(const ps2_state *s, unsigned code, ps2_key *k)` |
| `ps2_feed` | function | `progs/freedomui/ps2_keymap.c:253` | `int ps2_feed(ps2_state *s, uint8_t byte, ps2_key *out)` |
| `ps2_init` | function | `progs/freedomui/ps2_keymap.c:144` | `void ps2_init(ps2_state *s)` |
| `ps2_keypad` | struct | `progs/freedomui/ps2_keymap.c:122` | `` |
| `set_text` | function | `progs/freedomui/ps2_keymap.c:158` | `static void set_text(ps2_key *k, char c)` |
| `MINIOS_PS2_KEYMAP_H` | macro | `progs/freedomui/ps2_keymap.h:10` | `#define MINIOS_PS2_KEYMAP_H` |
| `PS2_CODE_EXTENDED` | macro | `progs/freedomui/ps2_keymap.h:21` | `#define PS2_CODE_EXTENDED` |
| `PS2_CODE_LIMIT` | macro | `progs/freedomui/ps2_keymap.h:24` | `#define PS2_CODE_LIMIT` |
| `PS2_EV_NONE` | macro | `progs/freedomui/ps2_keymap.h:16` | `#define PS2_EV_NONE` |
| `PS2_EV_PRESS` | macro | `progs/freedomui/ps2_keymap.h:17` | `#define PS2_EV_PRESS` |
| `PS2_EV_RELEASE` | macro | `progs/freedomui/ps2_keymap.h:18` | `#define PS2_EV_RELEASE` |
| `PS2_TEXT_MAX` | macro | `progs/freedomui/ps2_keymap.h:26` | `#define PS2_TEXT_MAX` |
| `arguments` | function | `progs/freedomui/ps2_keymap.h:51` | `* arguments (out is then left untouched). */ int ps2_feed(ps2_state *s, uint8_t byte, ps2_key *out);` |
| `held` | type_alias | `progs/freedomui/ps2_keymap.h:29` | `typedef struct ps2_state { unsigned held;` |
| `ps2_init` | function | `progs/freedomui/ps2_keymap.h:47` | `void ps2_init(ps2_state *s);` |
| `ps2_key` | struct | `progs/freedomui/ps2_keymap.h:38` | `` |
| `ps2_state` | struct | `progs/freedomui/ps2_keymap.h:29` | `` |
| `sym` | type_alias | `progs/freedomui/ps2_keymap.h:38` | `typedef struct ps2_key { uint32_t sym;` |
| `AllocTracker` | type_alias | `progs/lisp/lisp.c:70` | `typedef struct AllocTracker AllocTracker;` |
| `AllocTracker` | struct | `progs/lisp/lisp.c:157` | `` |
| `Binding` | type_alias | `progs/lisp/lisp.c:69` | `typedef struct Binding Binding;` |
| `Binding` | struct | `progs/lisp/lisp.c:140` | `` |
| `Env` | type_alias | `progs/lisp/lisp.c:68` | `typedef struct Env Env;` |
| `Env` | struct | `progs/lisp/lisp.c:149` | `` |
| `LispConfig` | enum | `progs/lisp/lisp.c:41` | `` |
| `Node` | type_alias | `progs/lisp/lisp.c:67` | `typedef struct Node Node;` |
| `Node` | struct | `progs/lisp/lisp.c:113` | `` |
| `ParseResult` | struct | `progs/lisp/lisp.c:104` | `` |
| `PrimEntry` | struct | `progs/lisp/lisp.c:1960` | `` |
| `Reader` | struct | `progs/lisp/lisp.c:181` | `` |
| `Runtime` | type_alias | `progs/lisp/lisp.c:65` | `typedef struct Runtime Runtime;` |
| `Runtime` | struct | `progs/lisp/lisp.c:165` | `` |
| `StringBuilder` | struct | `progs/lisp/lisp.c:192` | `` |
| `arg_at` | function | `progs/lisp/lisp.c:775` | `static Node *arg_at(Runtime *rt, Node *args, size_t index)` |
| `arg_matches` | function | `progs/lisp/lisp.c:815` | `static bool arg_matches(const Node *value, ArgKind kind)` |
| `arity` | function | `progs/lisp/lisp.c:1300` | `* * Variable arity (0 or 1);` |
| `arity0` | function | `progs/lisp/lisp.c:861` | `static bool arity0(Runtime *rt, Node *args)` |
| `bind_argv` | function | `progs/lisp/lisp.c:2017` | `static void bind_argv(Runtime *rt, Env *env, int argc, char **argv, int first)` |
| `bind_primitive` | function | `progs/lisp/lisp.c:1948` | `static void bind_primitive(Runtime *rt, Env *env, const char *name,     PrimFn function)` |
| `check_args` | function | `progs/lisp/lisp.c:841` | `static bool check_args(Runtime *rt, Node *args, const ArgKind *kinds,     size_t n, Node **out)` |
| `cleanup` | function | `progs/lisp/lisp.c:377` | `static void cleanup(Runtime *rt)` |
| `cons` | function | `progs/lisp/lisp.c:338` | `static Node *cons(Runtime *rt, Node *car, Node *cdr)` |
| `env_bind` | function | `progs/lisp/lisp.c:421` | `static void env_bind(Runtime *rt, Env *env, Node *symbol, Node *value)` |
| `env_lookup` | function | `progs/lisp/lisp.c:454` | `static Node *env_lookup(Env *env, Node *symbol)` |
| `env_new` | function | `progs/lisp/lisp.c:411` | `static Env *env_new(Runtime *rt, Env *parent)` |
| `env_set` | function | `progs/lisp/lisp.c:432` | `static bool env_set(Env *env, Node *symbol, Node *value)` |
| `eval` | function | `progs/lisp/lisp.c:1583` | `static Node *eval(Runtime *rt, Node *expression, Env *env)` |
| `eval_list` | function | `progs/lisp/lisp.c:1527` | `static Node *eval_list(Runtime *rt, Node *list, Env *env)` |
| `eval_sequence` | function | `progs/lisp/lisp.c:1551` | `static Node *eval_sequence(Runtime *rt, Node *body, Env *env)` |
| `fatal` | function | `progs/lisp/lisp.c:233` | `static void fatal(Runtime *rt, const char *message)` |
| `file_mode_allowed` | function | `progs/lisp/lisp.c:1123` | `static bool file_mode_allowed(const char *mode)` |
| `has_arity` | function | `progs/lisp/lisp.c:767` | `static bool has_arity(Runtime *rt, Node *args, size_t expected)` |
| `init_env` | function | `progs/lisp/lisp.c:2004` | `static Env *init_env(Runtime *rt)` |
| `is_nil` | function | `progs/lisp/lisp.c:348` | `static bool is_nil(Runtime *rt, const Node *node)` |
| `lisp_version` | function | `progs/lisp/lisp.c:62` | `static const char *lisp_version(void)` |
| `list_count` | function | `progs/lisp/lisp.c:750` | `static size_t list_count(Runtime *rt, Node *list, bool *proper)` |
| `main` | function | `progs/lisp/lisp.c:2190` | `int main(int argc, char **argv)` |
| `make_error` | function | `progs/lisp/lisp.c:293` | `static Node *make_error(Runtime *rt, const char *message)` |
| `make_file` | function | `progs/lisp/lisp.c:355` | `static Node *make_file(Runtime *rt, FILE *handle)` |
| `make_node` | function | `progs/lisp/lisp.c:284` | `static Node *make_node(Runtime *rt, NodeType type)` |
| `make_num` | function | `progs/lisp/lisp.c:302` | `static Node *make_num(Runtime *rt, int64_t value)` |
| `make_prim` | function | `progs/lisp/lisp.c:329` | `static Node *make_prim(Runtime *rt, PrimFn function)` |
| `make_str` | function | `progs/lisp/lisp.c:311` | `static Node *make_str(Runtime *rt, const char *value)` |
| `make_sym` | function | `progs/lisp/lisp.c:320` | `static Node *make_sym(Runtime *rt, const char *value)` |
| `msys` | function | `progs/lisp/lisp.c:205` | `static long msys(long n, long a1, long a2, long a3)` |
| `msys5` | function | `progs/lisp/lisp.c:218` | `static long msys5(long n, long a1, long a2, long a3, long a4, long a5)` |
| `numbers` | function | `progs/lisp/lisp.c:9` | `* * Language surface: numbers (int64), strings, symbols, cons cells, closures * with lexical scope, and the special...` |
| `parse_eof` | function | `progs/lisp/lisp.c:573` | `static ParseResult parse_eof(void)` |
| `parse_error` | function | `progs/lisp/lisp.c:584` | `static ParseResult parse_error(const char *message)` |
| `parse_ok` | function | `progs/lisp/lisp.c:562` | `static ParseResult parse_ok(Node *value)` |
| `prim_add` | function | `progs/lisp/lisp.c:869` | `static Node *prim_add(Runtime *rt, Node *args)` |
| `prim_car` | function | `progs/lisp/lisp.c:963` | `static Node *prim_car(Runtime *rt, Node *args)` |
| `prim_cdr` | function | `progs/lisp/lisp.c:975` | `static Node *prim_cdr(Runtime *rt, Node *args)` |
| `prim_char_code` | function | `progs/lisp/lisp.c:1072` | `static Node *prim_char_code(Runtime *rt, Node *args)` |
| `prim_close_file` | function | `progs/lisp/lisp.c:1224` | `static Node *prim_close_file(Runtime *rt, Node *args)` |
| `prim_cons` | function | `progs/lisp/lisp.c:987` | `static Node *prim_cons(Runtime *rt, Node *args)` |
| `prim_div` | function | `progs/lisp/lisp.c:917` | `static Node *prim_div(Runtime *rt, Node *args)` |
| `prim_eq` | function | `progs/lisp/lisp.c:939` | `static Node *prim_eq(Runtime *rt, Node *args)` |
| `prim_error_message` | function | `progs/lisp/lisp.c:1285` | `static Node *prim_error_message(Runtime *rt, Node *args)` |
| `prim_exit` | function | `progs/lisp/lisp.c:1303` | `static Node *prim_exit(Runtime *rt, Node *args)` |
| `prim_fb_info` | function | `progs/lisp/lisp.c:1357` | `static Node *prim_fb_info(Runtime *rt, Node *args)` |
| `prim_lt` | function | `progs/lisp/lisp.c:951` | `static Node *prim_lt(Runtime *rt, Node *args)` |
| `prim_minios_run` | function | `progs/lisp/lisp.c:1465` | `static Node *prim_minios_run(Runtime *rt, Node *args)` |
| `prim_mul` | function | `progs/lisp/lisp.c:901` | `static Node *prim_mul(Runtime *rt, Node *args)` |
| `prim_null_p` | function | `progs/lisp/lisp.c:1249` | `static Node *prim_null_p(Runtime *rt, Node *args)` |
| `prim_number_p` | function | `progs/lisp/lisp.c:1261` | `static Node *prim_number_p(Runtime *rt, Node *args)` |
| `prim_pal` | function | `progs/lisp/lisp.c:1405` | `static Node *prim_pal(Runtime *rt, Node *args)` |
| `prim_pcspeaker` | function | `progs/lisp/lisp.c:1421` | `static Node *prim_pcspeaker(Runtime *rt, Node *args)` |
| `prim_print` | function | `progs/lisp/lisp.c:1094` | `static Node *prim_print(Runtime *rt, Node *args)` |
| `prim_println` | function | `progs/lisp/lisp.c:1108` | `static Node *prim_println(Runtime *rt, Node *args)` |
| `prim_read_char` | function | `progs/lisp/lisp.c:1183` | `static Node *prim_read_char(Runtime *rt, Node *args)` |
| `prim_rtc` | function | `progs/lisp/lisp.c:1340` | `static Node *prim_rtc(Runtime *rt, Node *args)` |
| `prim_string_at` | function | `progs/lisp/lisp.c:1050` | `static Node *prim_string_at(Runtime *rt, Node *args)` |
| `prim_string_concat` | function | `progs/lisp/lisp.c:999` | `static Node *prim_string_concat(Runtime *rt, Node *args)` |
| `prim_string_eq` | function | `progs/lisp/lisp.c:1026` | `static Node *prim_string_eq(Runtime *rt, Node *args)` |
| `prim_string_length` | function | `progs/lisp/lisp.c:1038` | `static Node *prim_string_length(Runtime *rt, Node *args)` |
| `prim_string_p` | function | `progs/lisp/lisp.c:1273` | `static Node *prim_string_p(Runtime *rt, Node *args)` |
| `prim_sub` | function | `progs/lisp/lisp.c:885` | `static Node *prim_sub(Runtime *rt, Node *args)` |
| `prim_time_ms` | function | `progs/lisp/lisp.c:1330` | `static Node *prim_time_ms(Runtime *rt, Node *args)` |
| `prim_vol` | function | `progs/lisp/lisp.c:1377` | `static Node *prim_vol(Runtime *rt, Node *args)` |
| `prim_write` | function | `progs/lisp/lisp.c:1200` | `static Node *prim_write(Runtime *rt, Node *args)` |
| `print_escaped_string` | function | `progs/lisp/lisp.c:1846` | `static void print_escaped_string(FILE *out, const char *value)` |
| `print_node` | function | `progs/lisp/lisp.c:1877` | `static void print_node(Runtime *rt, Node *node, bool readable)` |
| `print_usage` | function | `progs/lisp/lisp.c:2136` | `static void print_usage(Runtime *rt)` |
| `process_inline` | function | `progs/lisp/lisp.c:2129` | `static int process_inline(Runtime *rt, const char *code)` |

Next: [SYMBOLS_p20.md](SYMBOLS_p20.md)
