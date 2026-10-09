# Symbols (page 17 of 26)
Previous: [SYMBOLS_p16.md](SYMBOLS_p16.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
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
| `ds_ystep` | variable | `progs/doomgeneric/r_draw.h:67` | `extern fixed_t ds_ystep;` |
| `translationtables` | variable | `progs/doomgeneric/r_draw.h:72` | `extern byte* translationtables;` |
| `__R_LOCAL__` | macro | `progs/doomgeneric/r_local.h:21` | `#define __R_LOCAL__` |
| `DISTMAP` | macro | `progs/doomgeneric/r_main.c:608` | `#define DISTMAP` |
| `FIELDOFVIEW` | macro | `progs/doomgeneric/r_main.c:43` | `#define FIELDOFVIEW` |
| `R_AddPointToBox` | function | `progs/doomgeneric/r_main.c:123` | `void R_AddPointToBox ( int		x,   int		y,   fixed_t*	box )` |
| `R_ExecuteSetViewSize` | function | `progs/doomgeneric/r_main.c:667` | `void R_ExecuteSetViewSize (void)` |
| `R_Init` | function | `progs/doomgeneric/r_main.c:767` | `void R_Init (void)` |
| `R_InitLightTables` | function | `progs/doomgeneric/r_main.c:610` | `void R_InitLightTables (void)` |
| `R_InitPointToAngle` | function | `progs/doomgeneric/r_main.c:422` | `void R_InitPointToAngle (void)` |
| `R_InitTables` | function | `progs/doomgeneric/r_main.c:505` | `void R_InitTables (void)` |
| `R_InitTextureMapping` | function | `progs/doomgeneric/r_main.c:540` | `void R_InitTextureMapping (void)` |
| `R_PointInSubsector` | function | `progs/doomgeneric/r_main.c:794` | `subsector_t* R_PointInSubsector ( fixed_t	x,   fixed_t	y )` |
| `R_PointOnSegSide` | function | `progs/doomgeneric/r_main.c:199` | `int R_PointOnSegSide ( fixed_t	x,   fixed_t	y,   seg_t*	line )` |
| `R_PointOnSide` | function | `progs/doomgeneric/r_main.c:146` | `int R_PointOnSide ( fixed_t	x,   fixed_t	y,   node_t*	node )` |
| `R_PointToAngle` | function | `progs/doomgeneric/r_main.c:276` | `angle_t R_PointToAngle ( fixed_t	x,   fixed_t	y )` |
| `R_PointToAngle2` | function | `progs/doomgeneric/r_main.c:362` | `angle_t R_PointToAngle2 ( fixed_t	x1,   fixed_t	y1,   fixed_t	x2,   fixed_t	y2 )` |
| `R_PointToDist` | function | `progs/doomgeneric/r_main.c:376` | `fixed_t R_PointToDist ( fixed_t	x,   fixed_t	y )` |
| `R_RenderPlayerView` | function | `progs/doomgeneric/r_main.c:863` | `void R_RenderPlayerView (player_t* player)` |
| `R_ScaleFromGlobalAngle` | function | `progs/doomgeneric/r_main.c:449` | `fixed_t R_ScaleFromGlobalAngle (angle_t visangle)` |
| `R_SetViewSize` | function | `progs/doomgeneric/r_main.c:654` | `void R_SetViewSize ( int		blocks,   int		detail )` |
| `R_SetupFrame` | function | `progs/doomgeneric/r_main.c:823` | `void R_SetupFrame (player_t* player)` |
| `walllights` | variable | `progs/doomgeneric/r_main.c:54` | `extern lighttable_t** walllights;` |
| `LIGHTLEVELS` | macro | `progs/doomgeneric/r_main.h:61` | `#define LIGHTLEVELS` |
| `LIGHTSCALESHIFT` | macro | `progs/doomgeneric/r_main.h:65` | `#define LIGHTSCALESHIFT` |
| `LIGHTSEGSHIFT` | macro | `progs/doomgeneric/r_main.h:62` | `#define LIGHTSEGSHIFT` |
| `LIGHTZSHIFT` | macro | `progs/doomgeneric/r_main.h:67` | `#define LIGHTZSHIFT` |
| `MAXLIGHTSCALE` | macro | `progs/doomgeneric/r_main.h:64` | `#define MAXLIGHTSCALE` |
| `MAXLIGHTZ` | macro | `progs/doomgeneric/r_main.h:66` | `#define MAXLIGHTZ` |
| `NUMCOLORMAPS` | macro | `progs/doomgeneric/r_main.h:79` | `#define NUMCOLORMAPS` |
| `R_AddPointToBox` | function | `progs/doomgeneric/r_main.h:140` | `void R_AddPointToBox ( int x, int y, fixed_t* box );` |
| `R_Init` | function | `progs/doomgeneric/r_main.h:155` | `void R_Init (void);` |
| `R_PointInSubsector` | function | `progs/doomgeneric/r_main.h:135` | `subsector_t* R_PointInSubsector ( fixed_t x, fixed_t y );` |
| `R_PointOnSegSide` | function | `progs/doomgeneric/r_main.h:109` | `int R_PointOnSegSide ( fixed_t x, fixed_t y, seg_t* line );` |
| `R_PointOnSide` | function | `progs/doomgeneric/r_main.h:103` | `int R_PointOnSide ( fixed_t x, fixed_t y, node_t* node );` |
| `R_PointToAngle` | function | `progs/doomgeneric/r_main.h:115` | `angle_t R_PointToAngle ( fixed_t x, fixed_t y );` |
| `R_PointToAngle2` | function | `progs/doomgeneric/r_main.h:120` | `angle_t R_PointToAngle2 ( fixed_t x1, fixed_t y1, fixed_t x2, fixed_t y2 );` |
| `R_PointToDist` | function | `progs/doomgeneric/r_main.h:127` | `fixed_t R_PointToDist ( fixed_t x, fixed_t y );` |
| `R_RenderPlayerView` | function | `progs/doomgeneric/r_main.h:152` | `void R_RenderPlayerView (player_t *player);` |
| `R_ScaleFromGlobalAngle` | function | `progs/doomgeneric/r_main.h:132` | `fixed_t R_ScaleFromGlobalAngle (angle_t visangle);` |
| `R_SetViewSize` | function | `progs/doomgeneric/r_main.h:158` | `void R_SetViewSize (int blocks, int detail);` |
| `__R_MAIN__` | macro | `progs/doomgeneric/r_main.h:21` | `#define __R_MAIN__` |
| `centerx` | variable | `progs/doomgeneric/r_main.h:40` | `extern int centerx;` |
| `centerxfrac` | variable | `progs/doomgeneric/r_main.h:43` | `extern fixed_t centerxfrac;` |
| `centery` | variable | `progs/doomgeneric/r_main.h:41` | `extern int centery;` |
| `centeryfrac` | variable | `progs/doomgeneric/r_main.h:44` | `extern fixed_t centeryfrac;` |
| `detailshift` | variable | `progs/doomgeneric/r_main.h:85` | `extern int detailshift;` |
| `extralight` | variable | `progs/doomgeneric/r_main.h:73` | `extern int extralight;` |
| `fixedcolormap` | variable | `progs/doomgeneric/r_main.h:74` | `extern lighttable_t* fixedcolormap;` |
| `linecount` | variable | `progs/doomgeneric/r_main.h:49` | `extern int linecount;` |
| `loopcount` | variable | `progs/doomgeneric/r_main.h:50` | `extern int loopcount;` |
| `projection` | variable | `progs/doomgeneric/r_main.h:45` | `extern fixed_t projection;` |
| `scalelightfixed` | variable | `progs/doomgeneric/r_main.h:70` | `extern lighttable_t* scalelightfixed[MAXLIGHTSCALE];` |
| `validcount` | variable | `progs/doomgeneric/r_main.h:47` | `extern int validcount;` |
| `viewcos` | variable | `progs/doomgeneric/r_main.h:32` | `extern fixed_t viewcos;` |
| `viewsin` | variable | `progs/doomgeneric/r_main.h:33` | `extern fixed_t viewsin;` |
| `viewwindowx` | variable | `progs/doomgeneric/r_main.h:35` | `extern int viewwindowx;` |
| `viewwindowy` | variable | `progs/doomgeneric/r_main.h:36` | `extern int viewwindowy;` |
| `void` | function | `progs/doomgeneric/r_main.h:92` | `extern void (*colfunc) (void);` |
| `MAXOPENINGS` | macro | `progs/doomgeneric/r_plane.c:52` | `#define MAXOPENINGS` |
| `MAXVISPLANES` | macro | `progs/doomgeneric/r_plane.c:45` | `#define MAXVISPLANES` |
| `R_CheckPlane` | function | `progs/doomgeneric/r_plane.c:259` | `visplane_t* R_CheckPlane ( visplane_t*	pl,   int		start,   int		stop )` |
| `R_ClearPlanes` | function | `progs/doomgeneric/r_plane.c:178` | `void R_ClearPlanes (void)` |
| `R_DrawPlanes` | function | `progs/doomgeneric/r_plane.c:360` | `void R_DrawPlanes (void)` |
| `R_FindPlane` | function | `progs/doomgeneric/r_plane.c:211` | `visplane_t* R_FindPlane ( fixed_t	height,   int		picnum,   int		lightlevel )` |
| `R_InitPlanes` | function | `progs/doomgeneric/r_plane.c:94` | `void R_InitPlanes (void)` |
| `R_MakeSpans` | function | `progs/doomgeneric/r_plane.c:324` | `void R_MakeSpans ( int		x,   int		t1,   int		b1,   int		t2,   int		b2 )` |
| `R_MapPlane` | function | `progs/doomgeneric/r_plane.c:114` | `void R_MapPlane ( int		y,   int		x1,   int		x2 )` |
| `R_CheckPlane` | function | `progs/doomgeneric/r_plane.h:69` | `visplane_t* R_CheckPlane ( visplane_t* pl, int start, int stop );` |
| `R_ClearPlanes` | function | `progs/doomgeneric/r_plane.h:44` | `void R_ClearPlanes (void);` |
| `R_DrawPlanes` | function | `progs/doomgeneric/r_plane.h:60` | `void R_DrawPlanes (void);` |
| `R_FindPlane` | function | `progs/doomgeneric/r_plane.h:63` | `visplane_t* R_FindPlane ( fixed_t height, int picnum, int lightlevel );` |
| `R_InitPlanes` | function | `progs/doomgeneric/r_plane.h:43` | `void R_InitPlanes (void);` |
| `R_MakeSpans` | function | `progs/doomgeneric/r_plane.h:53` | `void R_MakeSpans ( int x, int t1, int b1, int t2, int b2 );` |
| `R_MapPlane` | function | `progs/doomgeneric/r_plane.h:47` | `void R_MapPlane ( int y, int x1, int x2 );` |
| `__R_PLANE__` | macro | `progs/doomgeneric/r_plane.h:21` | `#define __R_PLANE__` |
| `ceilingclip` | variable | `progs/doomgeneric/r_plane.h:38` | `extern short ceilingclip[SCREENWIDTH];` |
| `ceilingfunc_t` | variable | `progs/doomgeneric/r_plane.h:35` | `extern planefunction_t ceilingfunc_t;` |
| `distscale` | variable | `progs/doomgeneric/r_plane.h:41` | `extern fixed_t distscale[SCREENWIDTH];` |
| `floorclip` | variable | `progs/doomgeneric/r_plane.h:37` | `extern short floorclip[SCREENWIDTH];` |
| `floorfunc` | variable | `progs/doomgeneric/r_plane.h:34` | `extern planefunction_t floorfunc;` |
| `lastopening` | variable | `progs/doomgeneric/r_plane.h:29` | `extern short* lastopening;` |
| `yslope` | variable | `progs/doomgeneric/r_plane.h:40` | `extern fixed_t yslope[SCREENHEIGHT];` |
| `HEIGHTBITS` | macro | `progs/doomgeneric/r_segs.c:196` | `#define HEIGHTBITS` |
| `HEIGHTUNIT` | macro | `progs/doomgeneric/r_segs.c:197` | `#define HEIGHTUNIT` |
| `R_RenderMaskedSegRange` | function | `progs/doomgeneric/r_segs.c:96` | `void R_RenderMaskedSegRange ( drawseg_t*	ds,   int		x1,   int		x2 )` |
| `R_RenderSegLoop` | function | `progs/doomgeneric/r_segs.c:199` | `void R_RenderSegLoop (void)` |
| `R_StoreWallRange` | function | `progs/doomgeneric/r_segs.c:372` | `void R_StoreWallRange ( int	start,   int	stop )` |
| `R_RenderMaskedSegRange` | function | `progs/doomgeneric/r_segs.h:27` | `void R_RenderMaskedSegRange ( drawseg_t* ds, int x1, int x2 );` |
| `__R_SEGS__` | macro | `progs/doomgeneric/r_segs.h:21` | `#define __R_SEGS__` |
| `R_InitSkyMap` | function | `progs/doomgeneric/r_sky.c:47` | `void R_InitSkyMap (void)` |
| `ANGLETOSKYSHIFT` | macro | `progs/doomgeneric/r_sky.h:29` | `#define ANGLETOSKYSHIFT` |
| `R_InitSkyMap` | function | `progs/doomgeneric/r_sky.h:35` | `void R_InitSkyMap (void);` |
| `SKYFLATNAME` | macro | `progs/doomgeneric/r_sky.h:26` | `#define			SKYFLATNAME` |
| `__R_SKY__` | macro | `progs/doomgeneric/r_sky.h:21` | `#define __R_SKY__` |
| `skytexture` | variable | `progs/doomgeneric/r_sky.h:31` | `extern int skytexture;` |
| `skytexturemid` | variable | `progs/doomgeneric/r_sky.h:32` | `extern int skytexturemid;` |
| `__R_STATE__` | macro | `progs/doomgeneric/r_state.h:21` | `#define __R_STATE__` |
| `ceilingplane` | variable | `progs/doomgeneric/r_state.h:124` | `extern visplane_t* ceilingplane;` |
| `clipangle` | variable | `progs/doomgeneric/r_state.h:106` | `extern angle_t clipangle;` |
| `colormaps` | variable | `progs/doomgeneric/r_state.h:46` | `extern lighttable_t* colormaps;` |
| `firstflat` | variable | `progs/doomgeneric/r_state.h:52` | `extern int firstflat;` |
| `firstspritelump` | variable | `progs/doomgeneric/r_state.h:60` | `extern int firstspritelump;` |
| `flattranslation` | variable | `progs/doomgeneric/r_state.h:55` | `extern int* flattranslation;` |
| `floorplane` | variable | `progs/doomgeneric/r_state.h:123` | `extern visplane_t* floorplane;` |
| `lastspritelump` | variable | `progs/doomgeneric/r_state.h:61` | `extern int lastspritelump;` |
| `lines` | variable | `progs/doomgeneric/r_state.h:88` | `extern line_t* lines;` |
| `nodes` | variable | `progs/doomgeneric/r_state.h:85` | `extern node_t* nodes;` |
| `numlines` | variable | `progs/doomgeneric/r_state.h:87` | `extern int numlines;` |
| `numnodes` | variable | `progs/doomgeneric/r_state.h:84` | `extern int numnodes;` |
| `numsectors` | variable | `progs/doomgeneric/r_state.h:78` | `extern int numsectors;` |
| `numsegs` | variable | `progs/doomgeneric/r_state.h:75` | `extern int numsegs;` |
| `numsides` | variable | `progs/doomgeneric/r_state.h:90` | `extern int numsides;` |
| `numspritelumps` | variable | `progs/doomgeneric/r_state.h:62` | `extern int numspritelumps;` |
| `numsprites` | variable | `progs/doomgeneric/r_state.h:69` | `extern int numsprites;` |
| `numsubsectors` | variable | `progs/doomgeneric/r_state.h:81` | `extern int numsubsectors;` |
| `numvertexes` | variable | `progs/doomgeneric/r_state.h:72` | `extern int numvertexes;` |
| `rw_angle1` | variable | `progs/doomgeneric/r_state.h:118` | `extern int rw_angle1;` |
| `rw_distance` | variable | `progs/doomgeneric/r_state.h:112` | `extern fixed_t rw_distance;` |
| `rw_normalangle` | variable | `progs/doomgeneric/r_state.h:113` | `extern angle_t rw_normalangle;` |
| `scaledviewwidth` | variable | `progs/doomgeneric/r_state.h:49` | `extern int scaledviewwidth;` |
| `sectors` | variable | `progs/doomgeneric/r_state.h:79` | `extern sector_t* sectors;` |
| `segs` | variable | `progs/doomgeneric/r_state.h:76` | `extern seg_t* segs;` |
| `sides` | variable | `progs/doomgeneric/r_state.h:91` | `extern side_t* sides;` |
| `spriteoffset` | variable | `progs/doomgeneric/r_state.h:43` | `extern fixed_t* spriteoffset;` |
| `sprites` | variable | `progs/doomgeneric/r_state.h:70` | `extern spritedef_t* sprites;` |
| `spritetopoffset` | variable | `progs/doomgeneric/r_state.h:44` | `extern fixed_t* spritetopoffset;` |
| `spritewidth` | variable | `progs/doomgeneric/r_state.h:41` | `extern fixed_t* spritewidth;` |
| `sscount` | variable | `progs/doomgeneric/r_state.h:121` | `extern int sscount;` |
| `subsectors` | variable | `progs/doomgeneric/r_state.h:82` | `extern subsector_t* subsectors;` |
| `textureheight` | variable | `progs/doomgeneric/r_state.h:38` | `extern fixed_t* textureheight;` |
| `texturetranslation` | variable | `progs/doomgeneric/r_state.h:56` | `extern int* texturetranslation;` |
| `vertexes` | variable | `progs/doomgeneric/r_state.h:73` | `extern vertex_t* vertexes;` |
| `viewangle` | variable | `progs/doomgeneric/r_state.h:101` | `extern angle_t viewangle;` |
| `viewangletox` | variable | `progs/doomgeneric/r_state.h:108` | `extern int viewangletox[FINEANGLES/2];` |
| `viewheight` | variable | `progs/doomgeneric/r_state.h:50` | `extern int viewheight;` |
| `viewplayer` | variable | `progs/doomgeneric/r_state.h:102` | `extern player_t* viewplayer;` |
| `viewwidth` | variable | `progs/doomgeneric/r_state.h:48` | `extern int viewwidth;` |
| `viewx` | variable | `progs/doomgeneric/r_state.h:97` | `extern fixed_t viewx;` |
| `viewy` | variable | `progs/doomgeneric/r_state.h:98` | `extern fixed_t viewy;` |
| `viewz` | variable | `progs/doomgeneric/r_state.h:99` | `extern fixed_t viewz;` |
| `xtoviewangle` | variable | `progs/doomgeneric/r_state.h:109` | `extern angle_t xtoviewangle[SCREENWIDTH+1];` |
| `BASEYCENTER` | macro | `progs/doomgeneric/r_things.c:41` | `#define BASEYCENTER` |
| `MINZ` | macro | `progs/doomgeneric/r_things.c:40` | `#define MINZ` |
| `R_AddSprites` | function | `progs/doomgeneric/r_things.c:605` | `void R_AddSprites (sector_t* sec)` |
| `R_ClearSprites` | function | `progs/doomgeneric/r_things.c:309` | `void R_ClearSprites (void)` |
| `R_DrawMasked` | function | `progs/doomgeneric/r_things.c:951` | `void R_DrawMasked (void)` |
| `R_DrawMaskedColumn` | function | `progs/doomgeneric/r_things.c:343` | `void R_DrawMaskedColumn (column_t* column)` |
| `R_DrawPSprite` | function | `progs/doomgeneric/r_things.c:638` | `void R_DrawPSprite (pspdef_t* psp)` |
| `R_DrawPlayerSprites` | function | `progs/doomgeneric/r_things.c:738` | `void R_DrawPlayerSprites (void)` |
| `R_DrawSprite` | function | `progs/doomgeneric/r_things.c:837` | `void R_DrawSprite (vissprite_t* spr)` |
| `R_DrawVisSprite` | function | `progs/doomgeneric/r_things.c:389` | `void R_DrawVisSprite ( vissprite_t*		vis,   int			x1,   int			x2 )` |
| `R_InitSpriteDefs` | function | `progs/doomgeneric/r_things.c:171` | `void R_InitSpriteDefs (char** namelist)` |
| `R_InitSprites` | function | `progs/doomgeneric/r_things.c:291` | `void R_InitSprites (char** namelist)` |
| `R_InstallSpriteLump` | function | `progs/doomgeneric/r_things.c:100` | `void R_InstallSpriteLump ( int		lump,   unsigned	frame,   unsigned	rotation,   boolean	flipped )` |
| `R_NewVisSprite` | function | `progs/doomgeneric/r_things.c:320` | `vissprite_t* R_NewVisSprite (void)` |
| `R_ProjectSprite` | function | `progs/doomgeneric/r_things.c:444` | `void R_ProjectSprite (mobj_t* thing)` |
| `R_SortVisSprites` | function | `progs/doomgeneric/r_things.c:779` | `void R_SortVisSprites (void)` |
| `maskdraw_t` | struct | `progs/doomgeneric/r_things.c:48` | `` |
| `MAXVISSPRITES` | macro | `progs/doomgeneric/r_things.h:25` | `#define MAXVISSPRITES` |
| `R_AddPSprites` | function | `progs/doomgeneric/r_things.h:52` | `void R_AddPSprites (void);` |
| `R_AddSprites` | function | `progs/doomgeneric/r_things.h:51` | `void R_AddSprites (sector_t* sec);` |
| `R_ClearSprites` | function | `progs/doomgeneric/r_things.h:55` | `void R_ClearSprites (void);` |
| `R_ClipVisSprite` | function | `progs/doomgeneric/r_things.h:59` | `void R_ClipVisSprite ( vissprite_t* vis, int xl, int xh );` |
| `R_DrawMasked` | function | `progs/doomgeneric/r_things.h:56` | `void R_DrawMasked (void);` |
| `R_DrawMaskedColumn` | function | `progs/doomgeneric/r_things.h:46` | `void R_DrawMaskedColumn (column_t* column);` |
| `R_DrawSprites` | function | `progs/doomgeneric/r_things.h:53` | `void R_DrawSprites (void);` |
| `R_InitSprites` | function | `progs/doomgeneric/r_things.h:54` | `void R_InitSprites (char** namelist);` |
| `R_SortVisSprites` | function | `progs/doomgeneric/r_things.h:49` | `void R_SortVisSprites (void);` |
| `__R_THINGS__` | macro | `progs/doomgeneric/r_things.h:21` | `#define __R_THINGS__` |
| `mceilingclip` | variable | `progs/doomgeneric/r_things.h:38` | `extern short* mceilingclip;` |
| `mfloorclip` | variable | `progs/doomgeneric/r_things.h:37` | `extern short* mfloorclip;` |
| `negonearray` | variable | `progs/doomgeneric/r_things.h:33` | `extern short negonearray[SCREENWIDTH];` |
| `pspriteiscale` | variable | `progs/doomgeneric/r_things.h:43` | `extern fixed_t pspriteiscale;` |
| `pspritescale` | variable | `progs/doomgeneric/r_things.h:42` | `extern fixed_t pspritescale;` |
| `screenheightarray` | variable | `progs/doomgeneric/r_things.h:34` | `extern short screenheightarray[SCREENWIDTH];` |
| `sprtopscreen` | variable | `progs/doomgeneric/r_things.h:40` | `extern fixed_t sprtopscreen;` |
| `spryscale` | variable | `progs/doomgeneric/r_things.h:39` | `extern fixed_t spryscale;` |
| `vissprite_p` | variable | `progs/doomgeneric/r_things.h:28` | `extern vissprite_t* vissprite_p;` |
| `vissprites` | variable | `progs/doomgeneric/r_things.h:27` | `extern vissprite_t vissprites[MAXVISSPRITES];` |
| `vsprsortedhead` | variable | `progs/doomgeneric/r_things.h:29` | `extern vissprite_t vsprsortedhead;` |
| `NORM_PITCH` | macro | `progs/doomgeneric/s_sound.c:62` | `#define NORM_PITCH` |
| `NORM_PRIORITY` | macro | `progs/doomgeneric/s_sound.c:63` | `#define NORM_PRIORITY` |
| `NORM_SEP` | macro | `progs/doomgeneric/s_sound.c:64` | `#define NORM_SEP` |
| `S_ATTENUATOR` | macro | `progs/doomgeneric/s_sound.c:56` | `#define S_ATTENUATOR` |
| `S_AdjustSoundParams` | function | `progs/doomgeneric/s_sound.c:323` | `static int S_AdjustSoundParams(mobj_t *listener, mobj_t *source,                                i...` |
| `S_CLIPPING_DIST` | macro | `progs/doomgeneric/s_sound.c:44` | `#define S_CLIPPING_DIST` |
| `S_CLOSE_DIST` | macro | `progs/doomgeneric/s_sound.c:52` | `#define S_CLOSE_DIST` |
| `S_ChangeMusic` | function | `progs/doomgeneric/s_sound.c:601` | `void S_ChangeMusic(int musicnum, int looping)` |
| `S_GetChannel` | function | `progs/doomgeneric/s_sound.c:262` | `static int S_GetChannel(mobj_t *origin, sfxinfo_t *sfxinfo)` |
| `S_Init` | function | `progs/doomgeneric/s_sound.c:114` | `void S_Init(int sfxVolume, int musicVolume)` |
| `S_MusicPlaying` | function | `progs/doomgeneric/s_sound.c:649` | `boolean S_MusicPlaying(void)` |
| `S_PauseSound` | function | `progs/doomgeneric/s_sound.c:482` | `void S_PauseSound(void)` |
| `S_ResumeSound` | function | `progs/doomgeneric/s_sound.c:491` | `void S_ResumeSound(void)` |
| `S_STEREO_SWING` | macro | `progs/doomgeneric/s_sound.c:60` | `#define S_STEREO_SWING` |
| `S_SetMusicVolume` | function | `progs/doomgeneric/s_sound.c:571` | `void S_SetMusicVolume(int volume)` |
| `S_SetSfxVolume` | function | `progs/doomgeneric/s_sound.c:582` | `void S_SetSfxVolume(int volume)` |
| `S_Shutdown` | function | `progs/doomgeneric/s_sound.c:146` | `void S_Shutdown(void)` |
| `S_Start` | function | `progs/doomgeneric/s_sound.c:191` | `void S_Start(void)` |
| `S_StartMusic` | function | `progs/doomgeneric/s_sound.c:596` | `void S_StartMusic(int m_id)` |
| `S_StartSound` | function | `progs/doomgeneric/s_sound.c:391` | `void S_StartSound(void *origin_p, int sfx_id)` |
| `S_StopChannel` | function | `progs/doomgeneric/s_sound.c:152` | `static void S_StopChannel(int cnum)` |
| `S_StopMusic` | function | `progs/doomgeneric/s_sound.c:654` | `void S_StopMusic(void)` |
| `S_StopSound` | function | `progs/doomgeneric/s_sound.c:243` | `void S_StopSound(mobj_t *origin)` |
| `S_UpdateSounds` | function | `progs/doomgeneric/s_sound.c:504` | `void S_UpdateSounds(mobj_t *listener)` |
| `channel_t` | struct | `progs/doomgeneric/s_sound.c:66` | `` |
| `S_ChangeMusic` | function | `progs/doomgeneric/s_sound.h:65` | `void S_ChangeMusic(int music_id, int looping);` |
| `S_Init` | function | `progs/doomgeneric/s_sound.h:32` | `void S_Init(int sfxVolume, int musicVolume);` |
| `S_PauseSound` | function | `progs/doomgeneric/s_sound.h:74` | `void S_PauseSound(void);` |
| `S_ResumeSound` | function | `progs/doomgeneric/s_sound.h:75` | `void S_ResumeSound(void);` |
| `S_SetMusicVolume` | function | `progs/doomgeneric/s_sound.h:83` | `void S_SetMusicVolume(int volume);` |
| `S_SetSfxVolume` | function | `progs/doomgeneric/s_sound.h:84` | `void S_SetSfxVolume(int volume);` |
| `S_Shutdown` | function | `progs/doomgeneric/s_sound.h:37` | `void S_Shutdown(void);` |
| `S_Start` | function | `progs/doomgeneric/s_sound.h:47` | `void S_Start(void);` |
| `S_StartMusic` | function | `progs/doomgeneric/s_sound.h:61` | `void S_StartMusic(int music_id);` |
| `S_StartSound` | function | `progs/doomgeneric/s_sound.h:54` | `void S_StartSound(void *origin, int sound_id);` |
| `S_StopMusic` | function | `progs/doomgeneric/s_sound.h:71` | `void S_StopMusic(void);` |
| `S_StopSound` | function | `progs/doomgeneric/s_sound.h:57` | `void S_StopSound(mobj_t *origin);` |
| `S_UpdateSounds` | function | `progs/doomgeneric/s_sound.h:81` | `void S_UpdateSounds(mobj_t *listener);` |
| `__S_SOUND__` | macro | `progs/doomgeneric/s_sound.h:21` | `#define __S_SOUND__` |
| `snd_channels` | variable | `progs/doomgeneric/s_sound.h:86` | `extern int snd_channels;` |
| `F1` | macro | `progs/doomgeneric/sha1.c:88` | `#define F1(x,y,z)` |
| `F2` | macro | `progs/doomgeneric/sha1.c:89` | `#define F2(x,y,z)` |
| `F3` | macro | `progs/doomgeneric/sha1.c:90` | `#define F3(x,y,z)` |
| `F4` | macro | `progs/doomgeneric/sha1.c:91` | `#define F4(x,y,z)` |
| `K1` | macro | `progs/doomgeneric/sha1.c:84` | `#define K1` |
| `K2` | macro | `progs/doomgeneric/sha1.c:85` | `#define K2` |
| `K3` | macro | `progs/doomgeneric/sha1.c:86` | `#define K3` |
| `K4` | macro | `progs/doomgeneric/sha1.c:87` | `#define K4` |
| `M` | macro | `progs/doomgeneric/sha1.c:95` | `#define M(i)` |
| `R` | macro | `progs/doomgeneric/sha1.c:99` | `#define R(a,b,c,d,e,f,k,m)` |
| `SHA1_Final` | function | `progs/doomgeneric/sha1.c:238` | `void SHA1_Final(sha1_digest_t digest, sha1_context_t *hd)` |
| `SHA1_Init` | function | `progs/doomgeneric/sha1.c:40` | `void SHA1_Init(sha1_context_t *hd)` |
| `SHA1_Update` | function | `progs/doomgeneric/sha1.c:198` | `void SHA1_Update(sha1_context_t *hd, byte *inbuf, size_t inlen)` |
| `SHA1_UpdateInt32` | function | `progs/doomgeneric/sha1.c:303` | `void SHA1_UpdateInt32(sha1_context_t *context, unsigned int val)` |
| `SHA1_UpdateString` | function | `progs/doomgeneric/sha1.c:315` | `void SHA1_UpdateString(sha1_context_t *context, char *str)` |
| `Transform` | function | `progs/doomgeneric/sha1.c:55` | `static void Transform(sha1_context_t *hd, byte *data)` |
| `X` | macro | `progs/doomgeneric/sha1.c:288` | `#define X(a)` |
| `X` | macro | `progs/doomgeneric/sha1.c:290` | `#define X(a)` |
| `rol` | macro | `progs/doomgeneric/sha1.c:93` | `#define rol(x,n)` |
| `SHA1_Final` | function | `progs/doomgeneric/sha1.h:35` | `void SHA1_Final(sha1_digest_t digest, sha1_context_t *context);` |
| `SHA1_Init` | function | `progs/doomgeneric/sha1.h:33` | `void SHA1_Init(sha1_context_t *context);` |
| `SHA1_Update` | function | `progs/doomgeneric/sha1.h:34` | `void SHA1_Update(sha1_context_t *context, byte *buf, size_t len);` |
| `SHA1_UpdateInt32` | function | `progs/doomgeneric/sha1.h:36` | `void SHA1_UpdateInt32(sha1_context_t *context, unsigned int val);` |
| `SHA1_UpdateString` | function | `progs/doomgeneric/sha1.h:37` | `void SHA1_UpdateString(sha1_context_t *context, char *str);` |
| `__SHA1_H__` | macro | `progs/doomgeneric/sha1.h:19` | `#define __SHA1_H__` |
| `sha1_context_s` | struct | `progs/doomgeneric/sha1.h:26` | `` |
| `sha1_context_t` | type_alias | `progs/doomgeneric/sha1.h:22` | `typedef struct sha1_context_s sha1_context_t;` |
| `sha1_digest_t` | type_alias | `progs/doomgeneric/sha1.h:24` | `typedef byte sha1_digest_t[20];` |
| `MUSIC` | macro | `progs/doomgeneric/sounds.c:31` | `#define MUSIC(name)` |
| `SOUND` | macro | `progs/doomgeneric/sounds.c:111` | `#define SOUND(name, priority)` |
| `SOUND_LINK` | macro | `progs/doomgeneric/sounds.c:113` | `#define SOUND_LINK(name, priority, link_id, pitch, volume)` |
| `S_music` | variable | `progs/doomgeneric/sounds.h:29` | `extern musicinfo_t S_music[];` |
| `S_sfx` | variable | `progs/doomgeneric/sounds.h:26` | `extern sfxinfo_t S_sfx[];` |
| `__SOUNDS__` | macro | `progs/doomgeneric/sounds.h:21` | `#define __SOUNDS__` |
| `STlib_drawNum` | function | `progs/doomgeneric/st_lib.c:84` | `void STlib_drawNum ( st_number_t*	n,   boolean	refresh )` |
| `STlib_init` | function | `progs/doomgeneric/st_lib.c:51` | `void STlib_init(void)` |
| `STlib_initBinIcon` | function | `progs/doomgeneric/st_lib.c:236` | `void STlib_initBinIcon ( st_binicon_t*		b,   int			x,   int			y,   patch_t*		i,   boolean*		val, ...` |
| `STlib_initMultIcon` | function | `progs/doomgeneric/st_lib.c:186` | `void STlib_initMultIcon ( st_multicon_t*	i,   int			x,   int			y,   patch_t**		il,   int*			inum,...` |
| `STlib_initNum` | function | `progs/doomgeneric/st_lib.c:59` | `void STlib_initNum ( st_number_t*		n,   int			x,   int			y,   patch_t**		pl,   int*			num,   bool...` |
| `STlib_initPercent` | function | `progs/doomgeneric/st_lib.c:156` | `void STlib_initPercent ( st_percent_t*		p,   int			x,   int			y,   patch_t**		pl,   int*			num,  ...` |
| `STlib_updateBinIcon` | function | `progs/doomgeneric/st_lib.c:255` | `void STlib_updateBinIcon ( st_binicon_t*		bi,   boolean		refresh )` |
| `STlib_updateMultIcon` | function | `progs/doomgeneric/st_lib.c:205` | `void STlib_updateMultIcon ( st_multicon_t*	mi,   boolean		refresh )` |
| `STlib_updateNum` | function | `progs/doomgeneric/st_lib.c:146` | `void STlib_updateNum ( st_number_t*		n,   boolean		refresh )` |
| `STlib_updatePercent` | function | `progs/doomgeneric/st_lib.c:173` | `void STlib_updatePercent ( st_percent_t*		per,   int			refresh )` |
| `automapactive` | variable | `progs/doomgeneric/st_lib.c:40` | `extern boolean automapactive;` |
| `STlib_init` | function | `progs/doomgeneric/st_lib.h:138` | `void STlib_init(void);` |
| `STlib_initBinIcon` | function | `progs/doomgeneric/st_lib.h:196` | `void STlib_initBinIcon ( st_binicon_t* b, int x, int y, patch_t* i, boolean* val, boolean* on );` |
| `STlib_initMultIcon` | function | `progs/doomgeneric/st_lib.h:179` | `void STlib_initMultIcon ( st_multicon_t* mi, int x, int y, patch_t** il, int* inum, boolean* on );` |
| `STlib_initNum` | function | `progs/doomgeneric/st_lib.h:144` | `void STlib_initNum ( st_number_t* n, int x, int y, patch_t** pl, int* num, boolean* on, int width );` |
| `STlib_initPercent` | function | `progs/doomgeneric/st_lib.h:161` | `void STlib_initPercent ( st_percent_t* p, int x, int y, patch_t** pl, int* num, boolean* on, patch_t* percent );` |
| `STlib_updateBinIcon` | function | `progs/doomgeneric/st_lib.h:205` | `void STlib_updateBinIcon ( st_binicon_t* bi, boolean refresh );` |
| `STlib_updateMultIcon` | function | `progs/doomgeneric/st_lib.h:189` | `void STlib_updateMultIcon ( st_multicon_t* mi, boolean refresh );` |
| `STlib_updateNum` | function | `progs/doomgeneric/st_lib.h:154` | `void STlib_updateNum ( st_number_t* n, boolean refresh );` |
| `STlib_updatePercent` | function | `progs/doomgeneric/st_lib.h:172` | `void STlib_updatePercent ( st_percent_t* per, int refresh );` |
| `__STLIB__` | macro | `progs/doomgeneric/st_lib.h:20` | `#define __STLIB__` |
| `st_binicon_t` | struct | `progs/doomgeneric/st_lib.h:106` | `` |
| `st_multicon_t` | struct | `progs/doomgeneric/st_lib.h:77` | `` |
| `st_number_t` | struct | `progs/doomgeneric/st_lib.h:32` | `` |
| `st_percent_t` | struct | `progs/doomgeneric/st_lib.h:64` | `` |
| `NUMBONUSPALS` | macro | `progs/doomgeneric/st_stuff.c:71` | `#define NUMBONUSPALS` |
| `NUMREDPALS` | macro | `progs/doomgeneric/st_stuff.c:70` | `#define NUMREDPALS` |
| `RADIATIONPAL` | macro | `progs/doomgeneric/st_stuff.c:73` | `#define RADIATIONPAL` |
| `STARTBONUSPALS` | macro | `progs/doomgeneric/st_stuff.c:69` | `#define STARTBONUSPALS` |
| `STARTREDPALS` | macro | `progs/doomgeneric/st_stuff.c:68` | `#define STARTREDPALS` |
| `ST_AMMO0HEIGHT` | macro | `progs/doomgeneric/st_stuff.c:176` | `#define ST_AMMO0HEIGHT` |
| `ST_AMMO0WIDTH` | macro | `progs/doomgeneric/st_stuff.c:175` | `#define ST_AMMO0WIDTH` |
| `ST_AMMO0X` | macro | `progs/doomgeneric/st_stuff.c:177` | `#define ST_AMMO0X` |
| `ST_AMMO0Y` | macro | `progs/doomgeneric/st_stuff.c:178` | `#define ST_AMMO0Y` |
| `ST_AMMO1WIDTH` | macro | `progs/doomgeneric/st_stuff.c:179` | `#define ST_AMMO1WIDTH` |
| `ST_AMMO1X` | macro | `progs/doomgeneric/st_stuff.c:180` | `#define ST_AMMO1X` |
| `ST_AMMO1Y` | macro | `progs/doomgeneric/st_stuff.c:181` | `#define ST_AMMO1Y` |
| `ST_AMMO2WIDTH` | macro | `progs/doomgeneric/st_stuff.c:182` | `#define ST_AMMO2WIDTH` |
| `ST_AMMO2X` | macro | `progs/doomgeneric/st_stuff.c:183` | `#define ST_AMMO2X` |
| `ST_AMMO2Y` | macro | `progs/doomgeneric/st_stuff.c:184` | `#define ST_AMMO2Y` |
| `ST_AMMO3WIDTH` | macro | `progs/doomgeneric/st_stuff.c:185` | `#define ST_AMMO3WIDTH` |
| `ST_AMMO3X` | macro | `progs/doomgeneric/st_stuff.c:186` | `#define ST_AMMO3X` |
| `ST_AMMO3Y` | macro | `progs/doomgeneric/st_stuff.c:187` | `#define ST_AMMO3Y` |
| `ST_AMMOWIDTH` | macro | `progs/doomgeneric/st_stuff.c:135` | `#define ST_AMMOWIDTH` |
| `ST_AMMOX` | macro | `progs/doomgeneric/st_stuff.c:136` | `#define ST_AMMOX` |
| `ST_AMMOY` | macro | `progs/doomgeneric/st_stuff.c:137` | `#define ST_AMMOY` |
| `ST_ARMORWIDTH` | macro | `progs/doomgeneric/st_stuff.c:158` | `#define ST_ARMORWIDTH` |
| `ST_ARMORX` | macro | `progs/doomgeneric/st_stuff.c:159` | `#define ST_ARMORX` |
| `ST_ARMORY` | macro | `progs/doomgeneric/st_stuff.c:160` | `#define ST_ARMORY` |
| `ST_ARMSBGX` | macro | `progs/doomgeneric/st_stuff.c:147` | `#define ST_ARMSBGX` |
| `ST_ARMSBGY` | macro | `progs/doomgeneric/st_stuff.c:148` | `#define ST_ARMSBGY` |
| `ST_ARMSX` | macro | `progs/doomgeneric/st_stuff.c:145` | `#define ST_ARMSX` |
| `ST_ARMSXSPACE` | macro | `progs/doomgeneric/st_stuff.c:149` | `#define ST_ARMSXSPACE` |
| `ST_ARMSY` | macro | `progs/doomgeneric/st_stuff.c:146` | `#define ST_ARMSY` |
| `ST_ARMSYSPACE` | macro | `progs/doomgeneric/st_stuff.c:150` | `#define ST_ARMSYSPACE` |
| `ST_DEADFACE` | macro | `progs/doomgeneric/st_stuff.c:112` | `#define ST_DEADFACE` |
| `ST_DETHX` | macro | `progs/doomgeneric/st_stuff.c:234` | `#define ST_DETHX` |
| `ST_DETHY` | macro | `progs/doomgeneric/st_stuff.c:235` | `#define ST_DETHY` |
| `ST_Drawer` | function | `progs/doomgeneric/st_stuff.c:1055` | `void ST_Drawer (boolean fullscreen, boolean refresh)` |
| `ST_EVILGRINCOUNT` | macro | `progs/doomgeneric/st_stuff.c:117` | `#define ST_EVILGRINCOUNT` |
| `ST_EVILGRINOFFSET` | macro | `progs/doomgeneric/st_stuff.c:109` | `#define ST_EVILGRINOFFSET` |
| `ST_FACEPROBABILITY` | macro | `progs/doomgeneric/st_stuff.c:77` | `#define ST_FACEPROBABILITY` |
| `ST_FACESTRIDE` | macro | `progs/doomgeneric/st_stuff.c:99` | `#define ST_FACESTRIDE` |
| `ST_FACESX` | macro | `progs/doomgeneric/st_stuff.c:114` | `#define ST_FACESX` |
| `ST_FACESY` | macro | `progs/doomgeneric/st_stuff.c:115` | `#define ST_FACESY` |
| `ST_FRAGSWIDTH` | macro | `progs/doomgeneric/st_stuff.c:155` | `#define ST_FRAGSWIDTH` |
| `ST_FRAGSX` | macro | `progs/doomgeneric/st_stuff.c:153` | `#define ST_FRAGSX` |
| `ST_FRAGSY` | macro | `progs/doomgeneric/st_stuff.c:154` | `#define ST_FRAGSY` |
| `ST_FX` | macro | `progs/doomgeneric/st_stuff.c:86` | `#define ST_FX` |
| `ST_FY` | macro | `progs/doomgeneric/st_stuff.c:87` | `#define ST_FY` |
| `ST_GODFACE` | macro | `progs/doomgeneric/st_stuff.c:111` | `#define ST_GODFACE` |
| `ST_HEALTHWIDTH` | macro | `progs/doomgeneric/st_stuff.c:140` | `#define ST_HEALTHWIDTH` |
| `ST_HEALTHX` | macro | `progs/doomgeneric/st_stuff.c:141` | `#define ST_HEALTHX` |
| `ST_HEALTHY` | macro | `progs/doomgeneric/st_stuff.c:142` | `#define ST_HEALTHY` |
| `ST_Init` | function | `progs/doomgeneric/st_stuff.c:1411` | `void ST_Init (void)` |
| `ST_KEY0HEIGHT` | macro | `progs/doomgeneric/st_stuff.c:164` | `#define ST_KEY0HEIGHT` |
| `ST_KEY0WIDTH` | macro | `progs/doomgeneric/st_stuff.c:163` | `#define ST_KEY0WIDTH` |
| `ST_KEY0X` | macro | `progs/doomgeneric/st_stuff.c:165` | `#define ST_KEY0X` |
| `ST_KEY0Y` | macro | `progs/doomgeneric/st_stuff.c:166` | `#define ST_KEY0Y` |
| `ST_KEY1WIDTH` | macro | `progs/doomgeneric/st_stuff.c:167` | `#define ST_KEY1WIDTH` |
| `ST_KEY1X` | macro | `progs/doomgeneric/st_stuff.c:168` | `#define ST_KEY1X` |
| `ST_KEY1Y` | macro | `progs/doomgeneric/st_stuff.c:169` | `#define ST_KEY1Y` |
| `ST_KEY2WIDTH` | macro | `progs/doomgeneric/st_stuff.c:170` | `#define ST_KEY2WIDTH` |
| `ST_KEY2X` | macro | `progs/doomgeneric/st_stuff.c:171` | `#define ST_KEY2X` |
| `ST_KEY2Y` | macro | `progs/doomgeneric/st_stuff.c:172` | `#define ST_KEY2Y` |
| `ST_MAPHEIGHT` | macro | `progs/doomgeneric/st_stuff.c:260` | `#define ST_MAPHEIGHT` |
| `ST_MAPTITLEX` | macro | `progs/doomgeneric/st_stuff.c:256` | `#define ST_MAPTITLEX` |
| `ST_MAPTITLEY` | macro | `progs/doomgeneric/st_stuff.c:259` | `#define ST_MAPTITLEY` |
| `ST_MAXAMMO0HEIGHT` | macro | `progs/doomgeneric/st_stuff.c:192` | `#define ST_MAXAMMO0HEIGHT` |
| `ST_MAXAMMO0WIDTH` | macro | `progs/doomgeneric/st_stuff.c:191` | `#define ST_MAXAMMO0WIDTH` |
| `ST_MAXAMMO0X` | macro | `progs/doomgeneric/st_stuff.c:193` | `#define ST_MAXAMMO0X` |
| `ST_MAXAMMO0Y` | macro | `progs/doomgeneric/st_stuff.c:194` | `#define ST_MAXAMMO0Y` |
| `ST_MAXAMMO1WIDTH` | macro | `progs/doomgeneric/st_stuff.c:195` | `#define ST_MAXAMMO1WIDTH` |
| `ST_MAXAMMO1X` | macro | `progs/doomgeneric/st_stuff.c:196` | `#define ST_MAXAMMO1X` |
| `ST_MAXAMMO1Y` | macro | `progs/doomgeneric/st_stuff.c:197` | `#define ST_MAXAMMO1Y` |
| `ST_MAXAMMO2WIDTH` | macro | `progs/doomgeneric/st_stuff.c:198` | `#define ST_MAXAMMO2WIDTH` |
| `ST_MAXAMMO2X` | macro | `progs/doomgeneric/st_stuff.c:199` | `#define ST_MAXAMMO2X` |
| `ST_MAXAMMO2Y` | macro | `progs/doomgeneric/st_stuff.c:200` | `#define ST_MAXAMMO2Y` |
| `ST_MAXAMMO3WIDTH` | macro | `progs/doomgeneric/st_stuff.c:201` | `#define ST_MAXAMMO3WIDTH` |
| `ST_MAXAMMO3X` | macro | `progs/doomgeneric/st_stuff.c:202` | `#define ST_MAXAMMO3X` |
| `ST_MAXAMMO3Y` | macro | `progs/doomgeneric/st_stuff.c:203` | `#define ST_MAXAMMO3Y` |
| `ST_MSGHEIGHT` | macro | `progs/doomgeneric/st_stuff.c:246` | `#define ST_MSGHEIGHT` |
| `ST_MSGTEXTX` | macro | `progs/doomgeneric/st_stuff.c:241` | `#define ST_MSGTEXTX` |
| `ST_MSGTEXTY` | macro | `progs/doomgeneric/st_stuff.c:242` | `#define ST_MSGTEXTY` |
| `ST_MSGWIDTH` | macro | `progs/doomgeneric/st_stuff.c:244` | `#define ST_MSGWIDTH` |
| `ST_MUCHPAIN` | macro | `progs/doomgeneric/st_stuff.c:123` | `#define ST_MUCHPAIN` |
| `ST_NUMEXTRAFACES` | macro | `progs/doomgeneric/st_stuff.c:102` | `#define ST_NUMEXTRAFACES` |
| `ST_NUMFACES` | macro | `progs/doomgeneric/st_stuff.c:104` | `#define ST_NUMFACES` |
| `ST_NUMPAINFACES` | macro | `progs/doomgeneric/st_stuff.c:94` | `#define ST_NUMPAINFACES` |
| `ST_NUMSPECIALFACES` | macro | `progs/doomgeneric/st_stuff.c:97` | `#define ST_NUMSPECIALFACES` |
| `ST_NUMSTRAIGHTFACES` | macro | `progs/doomgeneric/st_stuff.c:95` | `#define ST_NUMSTRAIGHTFACES` |
| `ST_NUMTURNFACES` | macro | `progs/doomgeneric/st_stuff.c:96` | `#define ST_NUMTURNFACES` |
| `ST_OUCHCOUNT` | macro | `progs/doomgeneric/st_stuff.c:120` | `#define ST_OUCHCOUNT` |
| `ST_OUCHOFFSET` | macro | `progs/doomgeneric/st_stuff.c:108` | `#define ST_OUCHOFFSET` |
| `ST_OUTHEIGHT` | macro | `progs/doomgeneric/st_stuff.c:254` | `#define ST_OUTHEIGHT` |
| `ST_OUTTEXTX` | macro | `progs/doomgeneric/st_stuff.c:248` | `#define ST_OUTTEXTX` |
| `ST_OUTTEXTY` | macro | `progs/doomgeneric/st_stuff.c:249` | `#define ST_OUTTEXTY` |
| `ST_OUTWIDTH` | macro | `progs/doomgeneric/st_stuff.c:252` | `#define ST_OUTWIDTH` |
| `ST_RAMPAGEDELAY` | macro | `progs/doomgeneric/st_stuff.c:121` | `#define ST_RAMPAGEDELAY` |
| `ST_RAMPAGEOFFSET` | macro | `progs/doomgeneric/st_stuff.c:110` | `#define ST_RAMPAGEOFFSET` |
| `ST_Responder` | function | `progs/doomgeneric/st_stuff.c:439` | `boolean ST_Responder (event_t* ev)` |

Next: [SYMBOLS_p18.md](SYMBOLS_p18.md)
