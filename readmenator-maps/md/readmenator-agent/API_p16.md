# API (page 16 of 21)
Previous: [API_p15.md](API_p15.md)

## progs/doomgeneric/st_lib.c
Depends on: `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/st_lib.h`, `progs/doomgeneric/st_stuff.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`
- `STlib_init` (function) `progs/doomgeneric/st_lib.c:51` `void STlib_init(void)`
- `STlib_initNum` (function) `progs/doomgeneric/st_lib.c:59` `void
STlib_initNum
( st_number_t*		n,
  int			x,
  int			y,
  patch_t**		pl,
  int*			num,
  bool...`
- `STlib_drawNum` (function) `progs/doomgeneric/st_lib.c:84` `void
STlib_drawNum
( st_number_t*	n,
  boolean	refresh )`
- `STlib_updateNum` (function) `progs/doomgeneric/st_lib.c:146` `void
STlib_updateNum
( st_number_t*		n,
  boolean		refresh )`
- `STlib_initPercent` (function) `progs/doomgeneric/st_lib.c:156` `void
STlib_initPercent
( st_percent_t*		p,
  int			x,
  int			y,
  patch_t**		pl,
  int*			num,
 ...`
- `STlib_updatePercent` (function) `progs/doomgeneric/st_lib.c:173` `void
STlib_updatePercent
( st_percent_t*		per,
  int			refresh )`
- `STlib_initMultIcon` (function) `progs/doomgeneric/st_lib.c:186` `void
STlib_initMultIcon
( st_multicon_t*	i,
  int			x,
  int			y,
  patch_t**		il,
  int*			inum,...`
- `STlib_updateMultIcon` (function) `progs/doomgeneric/st_lib.c:205` `void
STlib_updateMultIcon
( st_multicon_t*	mi,
  boolean		refresh )`
- `STlib_initBinIcon` (function) `progs/doomgeneric/st_lib.c:236` `void
STlib_initBinIcon
( st_binicon_t*		b,
  int			x,
  int			y,
  patch_t*		i,
  boolean*		val,
...`
- `STlib_updateBinIcon` (function) `progs/doomgeneric/st_lib.c:255` `void
STlib_updateBinIcon
( st_binicon_t*		bi,
  boolean		refresh )`

## progs/doomgeneric/st_lib.h
Depends on: `progs/doomgeneric/r_defs.h`
Imported by: `progs/doomgeneric/st_lib.c`, `progs/doomgeneric/st_stuff.c`
- `STlib_init` (function) `progs/doomgeneric/st_lib.h:138` `void STlib_init(void);` -- Initializes widget library.
- `STlib_initNum` (function) `progs/doomgeneric/st_lib.h:144` `void STlib_initNum ( st_number_t* n, int x, int y, patch_t** pl, int* num, boolean* on, int width );`
- `STlib_updateNum` (function) `progs/doomgeneric/st_lib.h:154` `void STlib_updateNum ( st_number_t* n, boolean refresh );`
- `STlib_initPercent` (function) `progs/doomgeneric/st_lib.h:161` `void STlib_initPercent ( st_percent_t* p, int x, int y, patch_t** pl, int* num, boolean* on, patch_t* percent );`
- `STlib_updatePercent` (function) `progs/doomgeneric/st_lib.h:172` `void STlib_updatePercent ( st_percent_t* per, int refresh );`
- `STlib_initMultIcon` (function) `progs/doomgeneric/st_lib.h:179` `void STlib_initMultIcon ( st_multicon_t* mi, int x, int y, patch_t** il, int* inum, boolean* on );`
- `STlib_updateMultIcon` (function) `progs/doomgeneric/st_lib.h:189` `void STlib_updateMultIcon ( st_multicon_t* mi, boolean refresh );`
- `STlib_initBinIcon` (function) `progs/doomgeneric/st_lib.h:196` `void STlib_initBinIcon ( st_binicon_t* b, int x, int y, patch_t* i, boolean* val, boolean* on );`
- `STlib_updateBinIcon` (function) `progs/doomgeneric/st_lib.h:205` `void STlib_updateBinIcon ( st_binicon_t* bi, boolean refresh );`

## progs/doomgeneric/st_stuff.c
Depends on: `progs/doomgeneric/am_map.h`, `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/deh_misc.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/dstrings.h`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_cheat.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/p_inter.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/st_lib.h`, `progs/doomgeneric/st_stuff.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`
- `ST_refreshBackground` (function) `progs/doomgeneric/st_stuff.c:416` `void ST_refreshBackground(void)`
- `ST_Responder` (function) `progs/doomgeneric/st_stuff.c:439` `boolean
ST_Responder (event_t* ev)`
- `ST_calcPainOffset` (function) `progs/doomgeneric/st_stuff.c:665` `int ST_calcPainOffset(void)`
- `ST_updateFaceWidget` (function) `progs/doomgeneric/st_stuff.c:688` `void ST_updateFaceWidget(void)` -- This is a not-very-pretty routine which handles the face states and their timing. the precedence of expressions is...
- `ST_updateWidgets` (function) `progs/doomgeneric/st_stuff.c:860` `void ST_updateWidgets(void)`
- `ST_Ticker` (function) `progs/doomgeneric/st_stuff.c:924` `void ST_Ticker (void)`
- `ST_doPaletteStuff` (function) `progs/doomgeneric/st_stuff.c:936` `void ST_doPaletteStuff(void)`
- `ST_drawWidgets` (function) `progs/doomgeneric/st_stuff.c:1001` `void ST_drawWidgets(boolean refresh)`
- `ST_doRefresh` (function) `progs/doomgeneric/st_stuff.c:1036` `void ST_doRefresh(void)`
- `ST_diffDraw` (function) `progs/doomgeneric/st_stuff.c:1049` `void ST_diffDraw(void)`
- `ST_Drawer` (function) `progs/doomgeneric/st_stuff.c:1055` `void ST_Drawer (boolean fullscreen, boolean refresh)`
- `ST_loadUnloadGraphics` (function) `progs/doomgeneric/st_stuff.c:1076` `static void ST_loadUnloadGraphics(load_callback_t callback)`
- `ST_loadCallback` (function) `progs/doomgeneric/st_stuff.c:1162` `static void ST_loadCallback(char *lumpname, patch_t **variable)`
- `ST_loadGraphics` (function) `progs/doomgeneric/st_stuff.c:1167` `void ST_loadGraphics(void)`
- `ST_loadData` (function) `progs/doomgeneric/st_stuff.c:1172` `void ST_loadData(void)`
- `ST_unloadCallback` (function) `progs/doomgeneric/st_stuff.c:1178` `static void ST_unloadCallback(char *lumpname, patch_t **variable)`
- `ST_unloadGraphics` (function) `progs/doomgeneric/st_stuff.c:1184` `void ST_unloadGraphics(void)`
- `ST_unloadData` (function) `progs/doomgeneric/st_stuff.c:1189` `void ST_unloadData(void)`
- `ST_initData` (function) `progs/doomgeneric/st_stuff.c:1194` `void ST_initData(void)`
- `ST_createWidgets` (function) `progs/doomgeneric/st_stuff.c:1227` `void ST_createWidgets(void)`
- `ST_Start` (function) `progs/doomgeneric/st_stuff.c:1389` `void ST_Start (void)`
- `ST_Stop` (function) `progs/doomgeneric/st_stuff.c:1401` `void ST_Stop (void)`
- `ST_Init` (function) `progs/doomgeneric/st_stuff.c:1411` `void ST_Init (void)`

## progs/doomgeneric/st_stuff.h
Depends on: `progs/doomgeneric/d_event.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/m_cheat.h`
Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/p_mobj.c`, `progs/doomgeneric/st_lib.c`, `progs/doomgeneric/st_stuff.c`
- `ST_Ticker` (function) `progs/doomgeneric/st_stuff.h:43` `void ST_Ticker (void);` -- Called by main loop.
- `ST_Drawer` (function) `progs/doomgeneric/st_stuff.h:46` `void ST_Drawer (boolean fullscreen, boolean refresh);` -- Called by main loop.
- `ST_Start` (function) `progs/doomgeneric/st_stuff.h:49` `void ST_Start (void);` -- Called when the console player is spawned on each level.
- `ST_Init` (function) `progs/doomgeneric/st_stuff.h:52` `void ST_Init (void);` -- Called by startup code.

## progs/doomgeneric/statdump.c
Depends on: `kernel/string.c`, `progs/doomgeneric/d_mode.h`, `progs/doomgeneric/d_player.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/statdump.h`
- `DiscoverGamemode` (function) `progs/doomgeneric/statdump.c:71` `static void DiscoverGamemode(wbstartstruct_t *stats, int num_stats)`
- `GetNumPlayers` (function) `progs/doomgeneric/statdump.c:130` `static int GetNumPlayers(wbstartstruct_t *stats)`
- `PrintBanner` (function) `progs/doomgeneric/statdump.c:150` `static void PrintBanner(FILE *stream)`
- `PrintPercentage` (function) `progs/doomgeneric/statdump.c:155` `static void PrintPercentage(FILE *stream, int amount, int total)`
- `PrintPlayerStats` (function) `progs/doomgeneric/statdump.c:180` `static void PrintPlayerStats(FILE *stream, wbstartstruct_t *stats,
        int player_num)`
- `PrintFragsTable` (function) `progs/doomgeneric/statdump.c:213` `static void PrintFragsTable(FILE *stream, wbstartstruct_t *stats)`
- `PrintLevelName` (function) `progs/doomgeneric/statdump.c:272` `static void PrintLevelName(FILE *stream, int episode, int level)`
- `PrintStats` (function) `progs/doomgeneric/statdump.c:301` `static void PrintStats(FILE *stream, wbstartstruct_t *stats)`
- `StatCopy` (function) `progs/doomgeneric/statdump.c:333` `void StatCopy(wbstartstruct_t *stats)`
- `StatDump` (function) `progs/doomgeneric/statdump.c:343` `void StatDump(void)`

## progs/doomgeneric/statdump.h
Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/statdump.c`
- `StatCopy` (function) `progs/doomgeneric/statdump.h:20` `void StatCopy(wbstartstruct_t *stats);`
- `StatDump` (function) `progs/doomgeneric/statdump.h:21` `void StatDump(void);`

## progs/doomgeneric/tables.c
Depends on: `progs/doomgeneric/tables.h`
- `SlopeDiv` (function) `progs/doomgeneric/tables.c:41` `int SlopeDiv(unsigned int num, unsigned int den)`

## progs/doomgeneric/tables.h
Depends on: `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/m_fixed.h`
Imported by: `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_video.c`, `progs/doomgeneric/p_mobj.h`, `progs/doomgeneric/p_pspr.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/tables.c`
- `SlopeDiv` (function) `progs/doomgeneric/tables.h:92` `int SlopeDiv(unsigned int num, unsigned int den);` -- Utility function, called by R_PointToAngle.

## progs/doomgeneric/v_video.c
Depends on: `kernel/string.c`, `progs/doomgeneric/config.h`, `progs/doomgeneric/deh_str.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_bbox.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`
- `V_MarkRect` (function) `progs/doomgeneric/v_video.c:69` `void V_MarkRect(int x, int y, int width, int height)` -- V_MarkRect
- `V_CopyRect` (function) `progs/doomgeneric/v_video.c:85` `void V_CopyRect(int srcx, int srcy, byte *source,
                int width, int height,
        ...` -- V_CopyRect
- `V_SetPatchClipCallback` (function) `progs/doomgeneric/v_video.c:129` `void V_SetPatchClipCallback(vpatchclipfunc_t func)` -- V_SetPatchClipCallback  haleyjd 08/28/10: Added for Strife support.
- `V_DrawPatch` (function) `progs/doomgeneric/v_video.c:139` `void V_DrawPatch(int x, int y, patch_t *patch)`
- `V_DrawPatchFlipped` (function) `progs/doomgeneric/v_video.c:203` `void V_DrawPatchFlipped(int x, int y, patch_t *patch)`
- `V_DrawPatchDirect` (function) `progs/doomgeneric/v_video.c:268` `void V_DrawPatchDirect(int x, int y, patch_t *patch)`
- `V_DrawTLPatch` (function) `progs/doomgeneric/v_video.c:279` `void V_DrawTLPatch(int x, int y, patch_t * patch)`
- `V_DrawXlaPatch` (function) `progs/doomgeneric/v_video.c:329` `void V_DrawXlaPatch(int x, int y, patch_t * patch)`
- `V_DrawAltTLPatch` (function) `progs/doomgeneric/v_video.c:378` `void V_DrawAltTLPatch(int x, int y, patch_t * patch)`
- `V_DrawShadowedPatch` (function) `progs/doomgeneric/v_video.c:428` `void V_DrawShadowedPatch(int x, int y, patch_t *patch)`
- `V_LoadTintTable` (function) `progs/doomgeneric/v_video.c:482` `void V_LoadTintTable(void)`
- `V_LoadXlaTable` (function) `progs/doomgeneric/v_video.c:493` `void V_LoadXlaTable(void)`
- `V_DrawBlock` (function) `progs/doomgeneric/v_video.c:503` `void V_DrawBlock(int x, int y, int width, int height, byte *src)`
- `V_DrawFilledBox` (function) `progs/doomgeneric/v_video.c:529` `void V_DrawFilledBox(int x, int y, int w, int h, int c)`
- `V_DrawHorizLine` (function) `progs/doomgeneric/v_video.c:549` `void V_DrawHorizLine(int x, int y, int w, int c)`
- `V_DrawVertLine` (function) `progs/doomgeneric/v_video.c:562` `void V_DrawVertLine(int x, int y, int h, int c)`
- `V_DrawBox` (function) `progs/doomgeneric/v_video.c:576` `void V_DrawBox(int x, int y, int w, int h, int c)`
- `V_DrawRawScreen` (function) `progs/doomgeneric/v_video.c:589` `void V_DrawRawScreen(byte *raw)`
- `V_Init` (function) `progs/doomgeneric/v_video.c:597` `void V_Init (void)` -- V_Init
- `V_UseBuffer` (function) `progs/doomgeneric/v_video.c:606` `void V_UseBuffer(byte *buffer)`
- `V_RestoreBuffer` (function) `progs/doomgeneric/v_video.c:613` `void V_RestoreBuffer(void)`
- `WritePCXfile` (function) `progs/doomgeneric/v_video.c:653` `void WritePCXfile(char *filename, byte *data,
                  int width, int height,
          ...`
- `error_fn` (function) `progs/doomgeneric/v_video.c:711` `static void error_fn(png_structp p, png_const_charp s)`
- `warning_fn` (function) `progs/doomgeneric/v_video.c:716` `static void warning_fn(png_structp p, png_const_charp s)`
- `WritePNGfile` (function) `progs/doomgeneric/v_video.c:721` `void WritePNGfile(char *filename, byte *data,
                  int width, int height,
          ...`
- `V_ScreenShot` (function) `progs/doomgeneric/v_video.c:791` `void V_ScreenShot(char *format)`
- `V_DrawMouseSpeedBox` (function) `progs/doomgeneric/v_video.c:846` `void V_DrawMouseSpeedBox(int speed)`

## progs/doomgeneric/v_video.h
Depends on: `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/v_patch.h`
Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/f_finale.c`, `progs/doomgeneric/f_wipe.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/hu_lib.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_video.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/m_misc.c`, `progs/doomgeneric/r_draw.c`, `progs/doomgeneric/st_lib.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/v_video.c`, `progs/doomgeneric/wi_stuff.c`
- `V_SetPatchClipCallback` (function) `progs/doomgeneric/v_video.h:45` `void V_SetPatchClipCallback(vpatchclipfunc_t func);`
- `V_Init` (function) `progs/doomgeneric/v_video.h:49` `void V_Init (void);` -- Allocates buffer screens, call before R_Init.
- `V_CopyRect` (function) `progs/doomgeneric/v_video.h:53` `void V_CopyRect(int srcx, int srcy, byte *source, int width, int height, int destx, int desty);`
- `V_DrawPatch` (function) `progs/doomgeneric/v_video.h:57` `void V_DrawPatch(int x, int y, patch_t *patch);`
- `V_DrawPatchFlipped` (function) `progs/doomgeneric/v_video.h:58` `void V_DrawPatchFlipped(int x, int y, patch_t *patch);`
- `V_DrawTLPatch` (function) `progs/doomgeneric/v_video.h:59` `void V_DrawTLPatch(int x, int y, patch_t *patch);`
- `V_DrawAltTLPatch` (function) `progs/doomgeneric/v_video.h:60` `void V_DrawAltTLPatch(int x, int y, patch_t * patch);`
- `V_DrawShadowedPatch` (function) `progs/doomgeneric/v_video.h:61` `void V_DrawShadowedPatch(int x, int y, patch_t *patch);`
- `V_DrawXlaPatch` (function) `progs/doomgeneric/v_video.h:62` `void V_DrawXlaPatch(int x, int y, patch_t * patch);`
- `V_DrawPatchDirect` (function) `progs/doomgeneric/v_video.h:63` `void V_DrawPatchDirect(int x, int y, patch_t *patch);`
- `V_DrawBlock` (function) `progs/doomgeneric/v_video.h:67` `void V_DrawBlock(int x, int y, int width, int height, byte *src);`
- `V_MarkRect` (function) `progs/doomgeneric/v_video.h:69` `void V_MarkRect(int x, int y, int width, int height);`
- `V_DrawFilledBox` (function) `progs/doomgeneric/v_video.h:71` `void V_DrawFilledBox(int x, int y, int w, int h, int c);`
- `V_DrawHorizLine` (function) `progs/doomgeneric/v_video.h:72` `void V_DrawHorizLine(int x, int y, int w, int c);`
- `V_DrawVertLine` (function) `progs/doomgeneric/v_video.h:73` `void V_DrawVertLine(int x, int y, int h, int c);`
- `V_DrawBox` (function) `progs/doomgeneric/v_video.h:74` `void V_DrawBox(int x, int y, int w, int h, int c);`
- `V_DrawRawScreen` (function) `progs/doomgeneric/v_video.h:78` `void V_DrawRawScreen(byte *raw);`
- `V_UseBuffer` (function) `progs/doomgeneric/v_video.h:82` `void V_UseBuffer(byte *buffer);`
- `V_RestoreBuffer` (function) `progs/doomgeneric/v_video.h:86` `void V_RestoreBuffer(void);`
- `V_ScreenShot` (function) `progs/doomgeneric/v_video.h:92` `void V_ScreenShot(char *format);`
- `V_LoadTintTable` (function) `progs/doomgeneric/v_video.h:97` `void V_LoadTintTable(void);`
- `V_LoadXlaTable` (function) `progs/doomgeneric/v_video.h:103` `void V_LoadXlaTable(void);`
- `V_DrawMouseSpeedBox` (function) `progs/doomgeneric/v_video.h:105` `void V_DrawMouseSpeedBox(int speed);`

## progs/doomgeneric/w_checksum.c
Depends on: `kernel/string.c`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/sha1.h`, `progs/doomgeneric/w_checksum.h`, `progs/doomgeneric/w_wad.h`
- `GetFileNumber` (function) `progs/doomgeneric/w_checksum.c:31` `static int GetFileNumber(wad_file_t *handle)`
- `ChecksumAddLump` (function) `progs/doomgeneric/w_checksum.c:57` `static void ChecksumAddLump(sha1_context_t *sha1_context, lumpinfo_t *lump)`
- `W_Checksum` (function) `progs/doomgeneric/w_checksum.c:68` `void W_Checksum(sha1_digest_t digest)`

## progs/doomgeneric/w_checksum.h
Depends on: `progs/doomgeneric/doomtype.h`
Imported by: `progs/doomgeneric/d_net.c`, `progs/doomgeneric/w_checksum.c`
- `W_Checksum` (function) `progs/doomgeneric/w_checksum.h:24` `extern void W_Checksum(sha1_digest_t digest);`

## progs/doomgeneric/w_file.c
Depends on: `progs/doomgeneric/config.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/w_file.h`
- `W_OpenFile` (function) `progs/doomgeneric/w_file.c:53` `wad_file_t *W_OpenFile(char *path)`
- `W_CloseFile` (function) `progs/doomgeneric/w_file.c:85` `void W_CloseFile(wad_file_t *wad)`
- `W_Read` (function) `progs/doomgeneric/w_file.c:90` `size_t W_Read(wad_file_t *wad, unsigned int offset,
              void *buffer, size_t buffer_len)`

## progs/doomgeneric/w_file.h
Depends on: `progs/doomgeneric/doomtype.h`
Imported by: `progs/doomgeneric/w_file.c`, `progs/doomgeneric/w_file_stdc.c`, `progs/doomgeneric/w_wad.h`
- `W_OpenFile` (function) `progs/doomgeneric/w_file.h:65` `wad_file_t *W_OpenFile(char *path);`
- `W_CloseFile` (function) `progs/doomgeneric/w_file.h:69` `void W_CloseFile(wad_file_t *wad);`
- `W_Read` (function) `progs/doomgeneric/w_file.h:75` `size_t W_Read(wad_file_t *wad, unsigned int offset, void *buffer, size_t buffer_len);`

## progs/doomgeneric/w_file_stdc.c
Depends on: `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/w_file.h`, `progs/doomgeneric/z_zone.h`
- `W_StdC_OpenFile` (function) `progs/doomgeneric/w_file_stdc.c:33` `static wad_file_t *W_StdC_OpenFile(char *path)`
- `W_StdC_CloseFile` (function) `progs/doomgeneric/w_file_stdc.c:56` `static void W_StdC_CloseFile(wad_file_t *wad)`
- `W_StdC_Read` (function) `progs/doomgeneric/w_file_stdc.c:69` `size_t W_StdC_Read(wad_file_t *wad, unsigned int offset,
                   void *buffer, size_t ...`

## progs/doomgeneric/w_main.c
Depends on: `progs/doomgeneric/d_iwad.h`, `progs/doomgeneric/doomfeatures.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/w_main.h`, `progs/doomgeneric/w_merge.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`
- `W_ParseCommandLine` (function) `progs/doomgeneric/w_main.c:30` `boolean W_ParseCommandLine(void)`

## progs/doomgeneric/w_merge.h
Imported by: `progs/doomgeneric/w_main.c`
- `W_MergeFile` (function) `progs/doomgeneric/w_merge.h:29` `void W_MergeFile(char *filename);`
- `W_NWTMergeFile` (function) `progs/doomgeneric/w_merge.h:33` `void W_NWTMergeFile(char *filename, int flags);`
- `W_NWTDashMerge` (function) `progs/doomgeneric/w_merge.h:37` `void W_NWTDashMerge(char *filename);`
- `W_PrintDirectory` (function) `progs/doomgeneric/w_merge.h:41` `void W_PrintDirectory(void);`

## progs/doomgeneric/w_wad.c
Depends on: `kernel/string.c`, `progs/doomgeneric/config.h`, `progs/doomgeneric/d_iwad.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`
- `I_EndRead` (function) `progs/doomgeneric/w_wad.c:39` `void I_EndRead (void);`
- `W_LumpNameHash` (function) `progs/doomgeneric/w_wad.c:72` `unsigned int W_LumpNameHash(const char *s)`
- `ExtendLumpInfo` (function) `progs/doomgeneric/w_wad.c:89` `static void ExtendLumpInfo(int newnumlumps)` -- Increase the size of the lumpinfo[] array to the specified size.
- `W_AddFile` (function) `progs/doomgeneric/w_wad.c:141` `wad_file_t *W_AddFile (char *filename)`
- `W_NumLumps` (function) `progs/doomgeneric/w_wad.c:246` `int W_NumLumps (void)` -- W_NumLumps
- `W_CheckNumForName` (function) `progs/doomgeneric/w_wad.c:258` `int W_CheckNumForName (char* name)`
- `W_GetNumForName` (function) `progs/doomgeneric/w_wad.c:308` `int W_GetNumForName (char* name)` -- W_GetNumForName Calls W_CheckNumForName, but bombs out if not found.
- `W_LumpLength` (function) `progs/doomgeneric/w_wad.c:327` `int W_LumpLength (unsigned int lump)` -- W_LumpLength Returns the buffer size needed to load the given lump.
- `W_ReadLump` (function) `progs/doomgeneric/w_wad.c:344` `void W_ReadLump(unsigned int lump, void *dest)` -- W_ReadLump Loads the lump into the given buffer, which must be >= W_LumpLength().
- `W_CacheLumpNum` (function) `progs/doomgeneric/w_wad.c:384` `void *W_CacheLumpNum(int lumpnum, int tag)`
- `W_CacheLumpName` (function) `progs/doomgeneric/w_wad.c:431` `void *W_CacheLumpName(char *name, int tag)` -- W_CacheLumpName
- `W_ReleaseLumpNum` (function) `progs/doomgeneric/w_wad.c:446` `void W_ReleaseLumpNum(int lumpnum)`
- `W_ReleaseLumpName` (function) `progs/doomgeneric/w_wad.c:467` `void W_ReleaseLumpName(char *name)`
- `W_Profile` (function) `progs/doomgeneric/w_wad.c:480` `void W_Profile (void)`
- `W_GenerateHashTable` (function) `progs/doomgeneric/w_wad.c:541` `void W_GenerateHashTable(void)`
- `W_CheckCorrectIWAD` (function) `progs/doomgeneric/w_wad.c:588` `void W_CheckCorrectIWAD(GameMission_t mission)`

## progs/doomgeneric/w_wad.h
Depends on: `progs/doomgeneric/d_mode.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/w_file.h`
Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_iwad.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/f_finale.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/gusconf.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_minios_sound.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/m_misc.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/r_data.c`, `progs/doomgeneric/r_draw.c`, `progs/doomgeneric/r_plane.c`, `progs/doomgeneric/r_things.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/st_lib.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/v_video.c`, `progs/doomgeneric/w_checksum.c`, `progs/doomgeneric/w_main.c`, `progs/doomgeneric/w_wad.c`, `progs/doomgeneric/wi_stuff.c`
- `W_AddFile` (function) `progs/doomgeneric/w_wad.h:58` `wad_file_t *W_AddFile (char *filename);`
- `W_CheckNumForName` (function) `progs/doomgeneric/w_wad.h:60` `int W_CheckNumForName (char* name);`
- `W_GetNumForName` (function) `progs/doomgeneric/w_wad.h:61` `int W_GetNumForName (char* name);`
- `W_LumpLength` (function) `progs/doomgeneric/w_wad.h:63` `int W_LumpLength (unsigned int lump);`
- `W_ReadLump` (function) `progs/doomgeneric/w_wad.h:64` `void W_ReadLump (unsigned int lump, void *dest);`
- `W_CacheLumpNum` (function) `progs/doomgeneric/w_wad.h:66` `void* W_CacheLumpNum (int lump, int tag);`
- `W_CacheLumpName` (function) `progs/doomgeneric/w_wad.h:67` `void* W_CacheLumpName (char* name, int tag);`
- `W_GenerateHashTable` (function) `progs/doomgeneric/w_wad.h:69` `void W_GenerateHashTable(void);`
- `W_LumpNameHash` (function) `progs/doomgeneric/w_wad.h:71` `extern unsigned int W_LumpNameHash(const char *s);`
- `W_ReleaseLumpNum` (function) `progs/doomgeneric/w_wad.h:73` `void W_ReleaseLumpNum(int lump);`
- `W_ReleaseLumpName` (function) `progs/doomgeneric/w_wad.h:74` `void W_ReleaseLumpName(char *name);`
- `W_CheckCorrectIWAD` (function) `progs/doomgeneric/w_wad.h:76` `void W_CheckCorrectIWAD(GameMission_t mission);`

## progs/doomgeneric/wi_stuff.c
Depends on: `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/wi_stuff.h`, `progs/doomgeneric/z_zone.h`
- `WI_slamBackground` (function) `progs/doomgeneric/wi_stuff.c:402` `void WI_slamBackground(void)` -- slam background
- `WI_Responder` (function) `progs/doomgeneric/wi_stuff.c:409` `boolean WI_Responder(event_t* ev)` -- The ticker is used to detect keys because of timing issues in netgames.
- `WI_drawLF` (function) `progs/doomgeneric/wi_stuff.c:416` `void WI_drawLF(void)` -- Draws "<Levelname> Finished!"
- `WI_drawEL` (function) `progs/doomgeneric/wi_stuff.c:452` `void WI_drawEL(void)` -- Draws "Entering <LevelName>"
- `WI_drawOnLnode` (function) `progs/doomgeneric/wi_stuff.c:471` `void
WI_drawOnLnode
( int		n,
  patch_t*	c[] )`
- `WI_initAnimatedBack` (function) `progs/doomgeneric/wi_stuff.c:519` `void WI_initAnimatedBack(void)`
- `WI_updateAnimatedBack` (function) `progs/doomgeneric/wi_stuff.c:548` `void WI_updateAnimatedBack(void)`
- `WI_drawAnimatedBack` (function) `progs/doomgeneric/wi_stuff.c:599` `void WI_drawAnimatedBack(void)`
- `WI_drawNum` (function) `progs/doomgeneric/wi_stuff.c:628` `int
WI_drawNum
( int		x,
  int		y,
  int		n,
  int		digits )`
- `WI_drawPercent` (function) `progs/doomgeneric/wi_stuff.c:685` `void
WI_drawPercent
( int		x,
  int		y,
  int		p )`
- `WI_drawTime` (function) `progs/doomgeneric/wi_stuff.c:704` `void
WI_drawTime
( int		x,
  int		y,
  int		t )`
- `WI_End` (function) `progs/doomgeneric/wi_stuff.c:740` `void WI_End(void)`
- `WI_initNoState` (function) `progs/doomgeneric/wi_stuff.c:746` `void WI_initNoState(void)`
- `WI_updateNoState` (function) `progs/doomgeneric/wi_stuff.c:753` `void WI_updateNoState(void)`
- `WI_initShowNextLoc` (function) `progs/doomgeneric/wi_stuff.c:772` `void WI_initShowNextLoc(void)`
- `WI_updateShowNextLoc` (function) `progs/doomgeneric/wi_stuff.c:781` `void WI_updateShowNextLoc(void)`
- `WI_drawShowNextLoc` (function) `progs/doomgeneric/wi_stuff.c:791` `void WI_drawShowNextLoc(void)`
- `WI_drawNoState` (function) `progs/doomgeneric/wi_stuff.c:832` `void WI_drawNoState(void)`
- `WI_fragSum` (function) `progs/doomgeneric/wi_stuff.c:838` `int WI_fragSum(int playernum)`
- `WI_initDeathmatchStats` (function) `progs/doomgeneric/wi_stuff.c:869` `void WI_initDeathmatchStats(void)`
- `WI_updateDeathmatchStats` (function) `progs/doomgeneric/wi_stuff.c:898` `void WI_updateDeathmatchStats(void)`
- `WI_drawDeathmatchStats` (function) `progs/doomgeneric/wi_stuff.c:1001` `void WI_drawDeathmatchStats(void)`
- `WI_initNetgameStats` (function) `progs/doomgeneric/wi_stuff.c:1089` `void WI_initNetgameStats(void)`
- `WI_updateNetgameStats` (function) `progs/doomgeneric/wi_stuff.c:1117` `void WI_updateNetgameStats(void)`
- `WI_drawNetgameStats` (function) `progs/doomgeneric/wi_stuff.c:1272` `void WI_drawNetgameStats(void)`
- `WI_initStats` (function) `progs/doomgeneric/wi_stuff.c:1329` `void WI_initStats(void)`
- `WI_updateStats` (function) `progs/doomgeneric/wi_stuff.c:1341` `void WI_updateStats(void)`
- `WI_drawStats` (function) `progs/doomgeneric/wi_stuff.c:1447` `void WI_drawStats(void)`
- `WI_checkForAccelerate` (function) `progs/doomgeneric/wi_stuff.c:1481` `void WI_checkForAccelerate(void)`
- `WI_Ticker` (function) `progs/doomgeneric/wi_stuff.c:1514` `void WI_Ticker(void)` -- Updates stuff each tick
- `WI_loadUnloadData` (function) `progs/doomgeneric/wi_stuff.c:1554` `static void WI_loadUnloadData(load_callback_t callback)`
- `WI_loadCallback` (function) `progs/doomgeneric/wi_stuff.c:1704` `static void WI_loadCallback(char *name, patch_t **variable)`
- `WI_loadData` (function) `progs/doomgeneric/wi_stuff.c:1709` `void WI_loadData(void)`
- `WI_unloadCallback` (function) `progs/doomgeneric/wi_stuff.c:1735` `static void WI_unloadCallback(char *name, patch_t **variable)`
- `WI_unloadData` (function) `progs/doomgeneric/wi_stuff.c:1741` `void WI_unloadData(void)`
- `WI_Drawer` (function) `progs/doomgeneric/wi_stuff.c:1752` `void WI_Drawer (void)`
- `WI_initVariables` (function) `progs/doomgeneric/wi_stuff.c:1776` `void WI_initVariables(wbstartstruct_t* wbstartstruct)`
- `WI_Start` (function) `progs/doomgeneric/wi_stuff.c:1818` `void WI_Start(wbstartstruct_t* wbstartstruct)`

## progs/doomgeneric/wi_stuff.h
Depends on: `progs/doomgeneric/doomdef.h`
Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/wi_stuff.c`
- `WI_Ticker` (function) `progs/doomgeneric/wi_stuff.h:36` `void WI_Ticker (void);` -- Called by main loop, animate the intermission.
- `WI_Drawer` (function) `progs/doomgeneric/wi_stuff.h:40` `void WI_Drawer (void);` -- Called by main loop, draws the intermission directly into the screen buffer.
- `WI_Start` (function) `progs/doomgeneric/wi_stuff.h:43` `void WI_Start(wbstartstruct_t* wbstartstruct);` -- Setup for an intermission screen.
- `WI_End` (function) `progs/doomgeneric/wi_stuff.h:46` `void WI_End(void);` -- Shut down the intermission screen

## progs/doomgeneric/z_zone.c
Depends on: `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/z_zone.h`
- `Z_ClearZone` (function) `progs/doomgeneric/z_zone.c:71` `void Z_ClearZone (memzone_t* zone)` -- Z_ClearZone
- `Z_Init` (function) `progs/doomgeneric/z_zone.c:97` `void Z_Init (void)` -- Z_Init
- `Z_Free` (function) `progs/doomgeneric/z_zone.c:126` `void Z_Free (void* ptr)` -- Z_Free
- `Z_Malloc` (function) `progs/doomgeneric/z_zone.c:185` `void*
Z_Malloc
( int		size,
  int		tag,
  void*		user )`
- `Z_FreeTags` (function) `progs/doomgeneric/z_zone.c:298` `void
Z_FreeTags
( int		lowtag,
  int		hightag )`
- `Z_DumpHeap` (function) `progs/doomgeneric/z_zone.c:328` `void
Z_DumpHeap
( int		lowtag,
  int		hightag )`
- `Z_FileDumpHeap` (function) `progs/doomgeneric/z_zone.c:367` `void Z_FileDumpHeap (FILE* f)` -- Z_FileDumpHeap
- `Z_CheckHeap` (function) `progs/doomgeneric/z_zone.c:400` `void Z_CheckHeap (void)` -- Z_CheckHeap
- `Z_ChangeTag2` (function) `progs/doomgeneric/z_zone.c:429` `void Z_ChangeTag2(void *ptr, int tag, char *file, int line)` -- Z_ChangeTag
- `Z_ChangeUser` (function) `progs/doomgeneric/z_zone.c:446` `void Z_ChangeUser(void *ptr, void **user)`
- `Z_FreeMemory` (function) `progs/doomgeneric/z_zone.c:466` `int Z_FreeMemory (void)` -- Z_FreeMemory
- `Z_ZoneSize` (function) `progs/doomgeneric/z_zone.c:484` `unsigned int Z_ZoneSize(void)`

## progs/doomgeneric/z_zone.h
Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_iwad.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/f_finale.c`, `progs/doomgeneric/f_wipe.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/gusconf.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_minios_sound.c`, `progs/doomgeneric/i_scale.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/i_video.c`, `progs/doomgeneric/m_config.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/m_misc.c`, `progs/doomgeneric/memio.c`, `progs/doomgeneric/p_ceilng.c`, `progs/doomgeneric/p_doors.c`, `progs/doomgeneric/p_floor.c`, `progs/doomgeneric/p_lights.c`, `progs/doomgeneric/p_mobj.c`, `progs/doomgeneric/p_plats.c`, `progs/doomgeneric/p_saveg.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/p_tick.c`, `progs/doomgeneric/r_data.c`, `progs/doomgeneric/r_draw.c`, `progs/doomgeneric/r_plane.c`, `progs/doomgeneric/r_things.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/st_lib.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/v_video.c`, `progs/doomgeneric/w_file_stdc.c`, `progs/doomgeneric/w_main.c`, `progs/doomgeneric/w_wad.c`, `progs/doomgeneric/wi_stuff.c`, `progs/doomgeneric/z_zone.c`
- `Z_Init` (function) `progs/doomgeneric/z_zone.h:53` `void Z_Init (void);`
- `Z_Malloc` (function) `progs/doomgeneric/z_zone.h:54` `void* Z_Malloc (int size, int tag, void *ptr);`
- `Z_Free` (function) `progs/doomgeneric/z_zone.h:55` `void Z_Free (void *ptr);`
- `Z_FreeTags` (function) `progs/doomgeneric/z_zone.h:56` `void Z_FreeTags (int lowtag, int hightag);`
- `Z_DumpHeap` (function) `progs/doomgeneric/z_zone.h:57` `void Z_DumpHeap (int lowtag, int hightag);`
- `Z_FileDumpHeap` (function) `progs/doomgeneric/z_zone.h:58` `void Z_FileDumpHeap (FILE *f);`
- `Z_CheckHeap` (function) `progs/doomgeneric/z_zone.h:59` `void Z_CheckHeap (void);`
- `Z_ChangeTag2` (function) `progs/doomgeneric/z_zone.h:60` `void Z_ChangeTag2 (void *ptr, int tag, char *file, int line);`
- `Z_ChangeUser` (function) `progs/doomgeneric/z_zone.h:61` `void Z_ChangeUser(void *ptr, void **user);`
- `Z_FreeMemory` (function) `progs/doomgeneric/z_zone.h:62` `int Z_FreeMemory (void);`
- `Z_ZoneSize` (function) `progs/doomgeneric/z_zone.h:63` `unsigned int Z_ZoneSize(void);`

## progs/file/file.c
Depends on: `headers/leakcheck.h`, `kernel/string.c`, `progs/file/file_assoc.h`, `progs/minios_abi.h`, `progs/minios_png.h`, `progs/nuklear/nuklear_minios.h`, `progs/nuklear/nuklear_theme.h`
- `file_sys_dir_list` (function) `progs/file/file.c:101` `static long file_sys_dir_list(const char *path, char *buf, long cap)` -- static unsigned char file_icon_mask[FILE_ICON_N][FILE_ICON_MAX * FILE_ICON_MAX]; static struct nk_minios_img...
- `file_sys_spawn` (function) `progs/file/file.c:111` `static long file_sys_spawn(const char *path, int argc, const char **argv)` -- static int file_preview_h; static int file_preview_on; /** Raw DIR_LIST syscall (241): names land NUL-separated in...
- `file_ext_of` (function) `progs/file/file.c:122` `static void file_ext_of(const char *fname, char *dst, unsigned cap)` -- } /** Raw SPAWN syscall (215) preserving this app across the child. static long file_sys_spawn(const char *path, int...
- `file_icon_kind` (function) `progs/file/file.c:146` `static int file_icon_kind(const char *fname, int isdir)` -- Icon kind for an entry: folder for dirs, image for .png, object for .o/.elf/.cvm, files for the text kinds...
- `file_icon_sz` (function) `progs/file/file.c:158` `static int file_icon_sz(void)` -- and for anything else.
- `file_icon_decode` (function) `progs/file/file.c:165` `static int file_icon_decode(const char *path, unsigned char *px,
                            unsi...` -- Decode one RGBA icon into indexed pixels plus an alpha mask, scaled to the live size.
- `file_icons_load` (function) `progs/file/file.c:213` `static int file_icons_load(void)` -- Load the four kind icons; all-or-nothing so the UI never mixes icon * and text rows.
- `file_toggle_icons` (function) `progs/file/file.c:238` `static int file_toggle_icons(void)` -- Flip the icon size and reload the four kind icons.
- `file_join` (function) `progs/file/file.c:245` `static int file_join(const char *dir, const char *name, char *dst, unsigned cap)` -- Flip the icon size and reload the four kind icons.
- `file_parent` (function) `progs/file/file.c:259` `static void file_parent(char *path)` -- static int file_join(const char *dir, const char *name, char *dst, unsigned cap) { unsigned a = 0; unsigned b = 0...
- `file_assoc_line` (function) `progs/file/file.c:269` `static int file_assoc_line(const char *line, char *ext, char *prog)` -- return 0; } /** Parent of an absolute path, root stays root. static void file_parent(char *path) { unsigned n = 0...
- `file_assoc_load` (function) `progs/file/file.c:302` `static void file_assoc_load(void)` -- } if (line[p + k] && line[p + k] != '\n' && line[p + k] != '\r') return -1; while (p > 0 && (prog[p - 1] == ' ' ||...
- `file_assoc_lookup` (function) `progs/file/file.c:318` `static const char *file_assoc_lookup(const char *ext)` -- char line[FILE_LOG_LINE]; char ext[FILE_EXT_MAX + 1]; char prog[FILE_PROG_MAX + 1]; fassoc_clear(&file_assocs); f =...
- `file_action_of` (function) `progs/file/file.c:323` `static int file_action_of(const char *fname, const char **prog_out)` -- if (!f) return; while (fgets(line, sizeof(line), f)) { if (file_assoc_line(line, ext, prog) != 0) continue; if...
- `file_refresh` (function) `progs/file/file.c:336` `static void file_refresh(void)` -- /** Dispatch kind for a file name through the association table. static int file_action_of(const char *fname, const...
- `file_preview_load` (function) `progs/file/file.c:351` `static int file_preview_load(const char *path)` -- long rc = file_sys_dir_list(file_cwd, file_entries, FILE_LIST_CAP); if (rc < 0) { file_entry_count = 0...
- `file_preview_blit` (function) `progs/file/file.c:385` `static void file_preview_blit(int ox, int oy)` -- Blit the preview buffer into the NK back-buffer after rasterize (and its * RGB twin when the kernel maps it).
- `file_spawn_visible` (function) `progs/file/file.c:407` `static long file_spawn_visible(const char *tool, int argc, const char **argv,
                   ...` -- int dx = ox + x; int dy = oy + y; unsigned char r, g, b; volatile uint8_t *d; if (dx < 0 || dx >= NK_W || dy < 0 ||...
- `file_open_text` (function) `progs/file/file.c:430` `static void file_open_text(const char *path)` -- printf("file: %s exit code: %ld\n", label, rc); fflush(stdout); nk_sys_vga_mode(1); nk_build_palette(pal768)...
- `file_run_shell` (function) `progs/file/file.c:441` `static void file_run_shell(const char *path)` -- } /** Open a text file in vedit, preserving this browser. static void file_open_text(const char *path) { const char...
- `file_activate` (function) `progs/file/file.c:480` `static void file_activate(const char *dir, const char *name)` -- if (strcmp(ext, "cvm") == 0) { args[0] = path; args[1] = 0; snprintf(label, sizeof(label), "run %s", path)...
- `file_ui_build` (function) `progs/file/file.c:511` `static void file_ui_build(struct nk_context *ctx)` -- snprintf(file_preview_path, sizeof(file_preview_path), "%s", path); snprintf(file_status, sizeof(file_status)...
- `file_selftest` (function) `progs/file/file.c:613` `static int file_selftest(void)` -- Headless selftest for BDD: assoc vectors plus a live listing.
- `file_gui_run` (function) `progs/file/file.c:779` `static void file_gui_run(void)`
- `main` (function) `progs/file/file.c:838` `int main(int argc, char **argv)`

## progs/file/file_assoc.h
Depends on: `kernel/string.c`
Imported by: `progs/file/file.c`, `tests/test_file_assoc.c`, `tests/test_leakcheck.c`
- `fassoc_ext_ok` (function) `progs/file/file_assoc.h:59` `static int fassoc_ext_ok(const char *ext)` -- /** Docstring: one validated association entry, ext without dot. struct fassoc_entry { char ext[FASSOC_EXT_MAX + 1]...
- `fassoc_prog_ok` (function) `progs/file/file_assoc.h:73` `static int fassoc_prog_ok(const char *prog)` -- static int fassoc_ext_ok(const char *ext) { size_t n = 0; size_t k = 0; if (ext == NULL) return 0; while (ext[n] !=...
- `fassoc_clear` (function) `progs/file/file_assoc.h:89` `static void fassoc_clear(struct fassoc_table *t)` -- size_t k = 0; if (prog == NULL) return 0; while (prog[n] != 0) n++; if (n == 0 || n > (size_t)FASSOC_PROG_MAX)...
- `fassoc_free` (function) `progs/file/file_assoc.h:95` `static void fassoc_free(struct fassoc_table *t)` -- if (prog[0] != '/') return 0; for (k = 0; k < n; k++) { if (prog[k] == '|') return 0; } return 1; } /** Docstring...
- `fassoc_reserve` (function) `progs/file/file_assoc.h:104` `static int fassoc_reserve(struct fassoc_table *t, size_t want)` -- if (t == NULL) return; t->cnt = 0; } /** Docstring: release backing store and reset to zero init state. static void...
- `fassoc_push` (function) `progs/file/file_assoc.h:125` `static int fassoc_push(struct fassoc_table *t, const char *ext, const char *prog)` -- while (ncap < want) { size_t nxt = ncap * (size_t)FASSOC_GROW_NUM / (size_t)FASSOC_GROW_DEN + 1; if (nxt <= ncap)...
- `fassoc_lookup` (function) `progs/file/file_assoc.h:140` `static const char *fassoc_lookup(const struct fassoc_table *t, const char *ext)` -- if (t == NULL) return -1; if (!fassoc_ext_ok(ext)) return -1; if (!fassoc_prog_ok(prog)) return -1; if (t->cnt >=...
- `fassoc_count` (function) `progs/file/file_assoc.h:150` `static size_t fassoc_count(const struct fassoc_table *t)` -- return 0; } /** Docstring: program for ext in file order, empty string when unmapped. static const char...

## progs/freedomui/freedomui_minios.c
Depends on: `kernel/string.c`, `progs/minios_abi.h`, `progs/nk_palette.h`
Imported by: `tests/test_freedomui.c`
- `net_dns_resolve` (function) `progs/freedomui/freedomui_minios.c:44` `int net_dns_resolve(const char *host);`
- `tls_handshake` (function) `progs/freedomui/freedomui_minios.c:45` `int tls_handshake(int fd, char *host);`
- `tls_send` (function) `progs/freedomui/freedomui_minios.c:46` `int tls_send(int fd, char *buf, int len);`
- `tls_recv` (function) `progs/freedomui/freedomui_minios.c:47` `int tls_recv(int fd, char *buf, int len);`
- `tls_close` (function) `progs/freedomui/freedomui_minios.c:48` `void tls_close(int fd);`
- `freedomui_default` (function) `progs/freedomui/freedomui_minios.c:97` `static FreedomUiConfig freedomui_default(void)` -- long path_max; long url_max; long hops_max; long font_w; long font_h; long port_http; long port_https; long ink_bg...
- `freedomui_build_palette` (function) `progs/freedomui/freedomui_minios.c:130` `static long freedomui_build_palette(unsigned char *pal, long cap)` -- Shared hybrid palette, one table for every NK-window app (progs/nk_palette.h); this wrapper keeps the historic name...
- `freedomui_engine_text` (function) `progs/freedomui/freedomui_minios.c:145` `static long freedomui_engine_text(char *body, long n, char **title, char **text)` -- Parse a fetched body through the real engine into owned title and text.
- `freedomui_sys_present` (function) `progs/freedomui/freedomui_minios.c:193` `static long freedomui_sys_present(long buf, long origin)` -- static char f_path[FUI_PATH_MAX]; static char f_loc[FUI_URL_MAX]; static char f_hdr[FUI_HDR_MAX]; static char...
- `freedomui_sys_title` (function) `progs/freedomui/freedomui_minios.c:200` `static long freedomui_sys_title(char *t)` -- static long f_nbytes; static long f_secure; static long f_port; static long f_status; static long f_truncated; /**...
- `freedomui_sys_palette` (function) `progs/freedomui/freedomui_minios.c:207` `static long freedomui_sys_palette(unsigned char *pal)` -- static long freedomui_sys_present(long buf, long origin) { long ret; __asm__ volatile("syscall" : "=a"(ret)...
- `freedomui_sys_mouse` (function) `progs/freedomui/freedomui_minios.c:214` `static long freedomui_sys_mouse(long *m)` -- static long freedomui_sys_title(char *t) { long ret; __asm__ volatile("syscall" : "=a"(ret)...
- `freedomui_sys_kbd` (function) `progs/freedomui/freedomui_minios.c:221` `static long freedomui_sys_kbd(void)` -- static long freedomui_sys_palette(unsigned char *pal) { long ret; __asm__ volatile("syscall" : "=a"(ret)...
- `freedomui_sys_vga_mode` (function) `progs/freedomui/freedomui_minios.c:228` `static long freedomui_sys_vga_mode(long on)` -- static long freedomui_sys_mouse(long *m) { long ret; __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_MOUSE)...
- `freedomui_sys_kbd_raw` (function) `progs/freedomui/freedomui_minios.c:235` `static long freedomui_sys_kbd_raw(long on)` -- static long freedomui_sys_kbd(void) { long ret; __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_KBD), "D"(0)...
- `freedomui_sys_yield` (function) `progs/freedomui/freedomui_minios.c:242` `static long freedomui_sys_yield(void)` -- static long freedomui_sys_vga_mode(long on) { long ret; __asm__ volatile("syscall" : "=a"(ret)...
- `fui_append` (function) `progs/freedomui/freedomui_minios.c:249` `static long fui_append(char *dst, long pos, char *src, long cap)` -- static long freedomui_sys_kbd_raw(long on) { long ret; __asm__ volatile("syscall" : "=a"(ret)...
- `fui_strlen` (function) `progs/freedomui/freedomui_minios.c:267` `static long fui_strlen(char *s, long cap)` -- } i = 0L; while (src[i] != 0) { if (pos + i + 1L >= cap) { return -1L; } dst[pos + i] = src[i]; i++; } dst[pos + i]...
- `fui_has_scheme` (function) `progs/freedomui/freedomui_minios.c:285` `static int fui_has_scheme(const char *s, const char *scheme)` -- Nonzero when the target starts with the given scheme (case-insensitive).
- `fui_is_http_scheme` (function) `progs/freedomui/freedomui_minios.c:309` `static int fui_is_http_scheme(const char *s)` -- Nonzero when the target starts with the explicit "http://" scheme (case-insensitive).
- `fui_split_url` (function) `progs/freedomui/freedomui_minios.c:314` `static long fui_split_url(FreedomUiConfig *c, char *url, char *host, char *path, long *port, long...` -- Nonzero when the target starts with the explicit "http://" scheme (case-insensitive).
- `fui_parse_headers` (function) `progs/freedomui/freedomui_minios.c:383` `static long fui_parse_headers(FreedomUiConfig *c, char *hdr, long *status, long *clen, long *hasc...` -- return 0L; } path[k] = p[hl + k]; k++; } path[k] = 0; } else { path[0] = '/'; path[1] = 0; } return 1L; } /** Parse...
- `fui_fetch_raw` (function) `progs/freedomui/freedomui_minios.c:501` `static long fui_fetch_raw(FreedomUiConfig *c, char *host, char *path, long port, long secure)` -- } k++; } } } line++; while (hdr[i] == '\r' || hdr[i] == '\n') { i++; } } return 0L; } /** Fetch one response body...
- `fui_render` (function) `progs/freedomui/freedomui_minios.c:729` `static long fui_render(FreedomUiConfig *c, size_t off)` -- if (got < c->body_cap) { f_body[got] = (char)ch; got++; } else { f_truncated = 1L; } } } } tls_close((int)fd)...
- `fui_browse` (function) `progs/freedomui/freedomui_minios.c:848` `static long fui_browse(FreedomUiConfig *c)` -- long ink; if (bits & (0x80 >> px)) { ink = c->bar_fg; } else { ink = c->bar_bg; } fb[((size_t)c->text_rows *...
- `freedomui_selftest` (function) `progs/freedomui/freedomui_minios.c:927` `static long freedomui_selftest(void)` -- } off = ui_clamp_scroll((size_t)want, f_lay.count, (size_t)c->text_rows); changed = 1L; } if (changed) { if...
- `freedomui_host_probe` (function) `progs/freedomui/freedomui_minios.c:1015` `static long freedomui_host_probe(FreedomUiConfig *c)` -- return 1L; } if (freedomui_sys_kbd() > 0x7FFFFFFFL) { printf("freedomui: kbd out of range\n"); return 1L; }...
- `freedomui_host_entry` (function) `progs/freedomui/freedomui_minios.c:1098` `int freedomui_host_entry(FreedomUiConfig *c)` -- if (title) { hp_free(title); } return -1L; } ui_layout_free(&lay); hp_free(text); if (title) { hp_free(title); }...
- `main` (function) `progs/freedomui/freedomui_minios.c:1103` `int main(int argc, char **argv)` -- ui_layout_free(&lay); hp_free(text); if (title) { hp_free(title); } return 0L; } /** Host harness entry for pure...

## progs/freedomui/media_unavailable.c
Depends on: `kernel/string.c`
- `write_all` (function) `progs/freedomui/media_unavailable.c:20` `static void write_all(int fd, const void *buf, size_t len)` -- closed: no decoder process is ever started, and a direct --media-decoder invocation answers with one MD_ERROR and...
- `media_decoder_run` (function) `progs/freedomui/media_unavailable.c:41` `void media_decoder_run(int out_fd, int cmd_fd)` -- Refuses to start a decoder: the caller reports the failure and stays * responsive (browser_ui video_play already...

## progs/freedomui/platform_minios.c
Depends on: `kernel/string.c`, `progs/freedomui/ps2_keymap.h`, `progs/minios_abi.h`
- `sys_fb_info_rgb` (function) `progs/freedomui/platform_minios.c:83` `static long sys_fb_info_rgb(int *rgb)`
- `now_ms` (function) `progs/freedomui/platform_minios.c:94` `static long now_ms(void)`
- `set_title` (function) `progs/freedomui/platform_minios.c:98` `static void set_title(const char *title)`
- `pf_display_open` (function) `progs/freedomui/platform_minios.c:137` `pf_status pf_display_open(pf_display **out)`
- `pf_display_close` (function) `progs/freedomui/platform_minios.c:153` `void pf_display_close(pf_display *d)`
- `pf_display_flush` (function) `progs/freedomui/platform_minios.c:162` `void pf_display_flush(pf_display *d)`
- `pf_display_set_cursor` (function) `progs/freedomui/platform_minios.c:166` `void pf_display_set_cursor(pf_display *d, pf_cursor c)`
- `deliver_pending` (function) `progs/freedomui/platform_minios.c:173` `static int deliver_pending(pf_display *d)`
- `key_event` (function) `progs/freedomui/platform_minios.c:183` `static void key_event(pf_display *d, const ps2_key *k, int kind)`
- `pump_keyboard` (function) `progs/freedomui/platform_minios.c:210` `static int pump_keyboard(pf_display *d)`
- `pump_mouse` (function) `progs/freedomui/platform_minios.c:224` `static int pump_mouse(pf_display *d)`
- `pf_display_wait` (function) `progs/freedomui/platform_minios.c:268` `int pf_display_wait(pf_display *d, struct pollfd *extra, int n, int timeout_ms)`
- `pf_clipboard_available` (function) `progs/freedomui/platform_minios.c:293` `int pf_clipboard_available(const pf_display *d)`
- `pf_clipboard_set_text` (function) `progs/freedomui/platform_minios.c:297` `pf_status pf_clipboard_set_text(pf_display *d, const char *text)`
- `pf_clipboard_get_text` (function) `progs/freedomui/platform_minios.c:304` `pf_status pf_clipboard_get_text(pf_display *d, char **out, size_t *out_len)`
- `pf_window_open` (function) `progs/freedomui/platform_minios.c:320` `pf_status pf_window_open(pf_display *d, const pf_window_opts *o,
                         const p...`
- `pf_window_close` (function) `progs/freedomui/platform_minios.c:342` `void pf_window_close(pf_window *w)`
- `pf_window_surface` (function) `progs/freedomui/platform_minios.c:359` `cairo_surface_t *pf_window_surface(pf_window *w, int width, int height)`
- `pf_window_present` (function) `progs/freedomui/platform_minios.c:374` `void pf_window_present(pf_window *w)`
- `pf_window_set_title` (function) `progs/freedomui/platform_minios.c:408` `void pf_window_set_title(pf_window *w, const char *title)`
- `set_zoom_state` (function) `progs/freedomui/platform_minios.c:414` `static void set_zoom_state(pf_window *w, unsigned bit, int on)`
- `pf_window_set_maximized` (function) `progs/freedomui/platform_minios.c:424` `void pf_window_set_maximized(pf_window *w, int on)`
- `pf_window_set_fullscreen` (function) `progs/freedomui/platform_minios.c:428` `void pf_window_set_fullscreen(pf_window *w, int on)`
- `pf_window_minimize` (function) `progs/freedomui/platform_minios.c:432` `void pf_window_minimize(pf_window *w)`
- `pf_window_begin_move` (function) `progs/freedomui/platform_minios.c:436` `void pf_window_begin_move(pf_window *w)`
- `pf_window_begin_resize` (function) `progs/freedomui/platform_minios.c:440` `void pf_window_begin_resize(pf_window *w, pf_edge edge)`


Next: [API_p17.md](API_p17.md)
