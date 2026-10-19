# Symbols (page 18 of 27)
Previous: [SYMBOLS_p17.md](SYMBOLS_p17.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
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
| `ST_STRAIGHTFACECOUNT` | macro | `progs/doomgeneric/st_stuff.c:118` | `#define ST_STRAIGHTFACECOUNT` |
| `ST_Start` | function | `progs/doomgeneric/st_stuff.c:1389` | `void ST_Start (void)` |
| `ST_Stop` | function | `progs/doomgeneric/st_stuff.c:1401` | `void ST_Stop (void)` |
| `ST_TALLNUMWIDTH` | macro | `progs/doomgeneric/st_stuff.c:91` | `#define ST_TALLNUMWIDTH` |
| `ST_TOGGLECHAT` | macro | `progs/doomgeneric/st_stuff.c:80` | `#define ST_TOGGLECHAT` |
| `ST_TURNCOUNT` | macro | `progs/doomgeneric/st_stuff.c:119` | `#define ST_TURNCOUNT` |
| `ST_TURNOFFSET` | macro | `progs/doomgeneric/st_stuff.c:107` | `#define ST_TURNOFFSET` |
| `ST_Ticker` | function | `progs/doomgeneric/st_stuff.c:924` | `void ST_Ticker (void)` |
| `ST_WEAPON0X` | macro | `progs/doomgeneric/st_stuff.c:206` | `#define ST_WEAPON0X` |
| `ST_WEAPON0Y` | macro | `progs/doomgeneric/st_stuff.c:207` | `#define ST_WEAPON0Y` |
| `ST_WEAPON1X` | macro | `progs/doomgeneric/st_stuff.c:210` | `#define ST_WEAPON1X` |
| `ST_WEAPON1Y` | macro | `progs/doomgeneric/st_stuff.c:211` | `#define ST_WEAPON1Y` |
| `ST_WEAPON2X` | macro | `progs/doomgeneric/st_stuff.c:214` | `#define ST_WEAPON2X` |
| `ST_WEAPON2Y` | macro | `progs/doomgeneric/st_stuff.c:215` | `#define ST_WEAPON2Y` |
| `ST_WEAPON3X` | macro | `progs/doomgeneric/st_stuff.c:218` | `#define ST_WEAPON3X` |
| `ST_WEAPON3Y` | macro | `progs/doomgeneric/st_stuff.c:219` | `#define ST_WEAPON3Y` |
| `ST_WEAPON4X` | macro | `progs/doomgeneric/st_stuff.c:222` | `#define ST_WEAPON4X` |
| `ST_WEAPON4Y` | macro | `progs/doomgeneric/st_stuff.c:223` | `#define ST_WEAPON4Y` |
| `ST_WEAPON5X` | macro | `progs/doomgeneric/st_stuff.c:226` | `#define ST_WEAPON5X` |
| `ST_WEAPON5Y` | macro | `progs/doomgeneric/st_stuff.c:227` | `#define ST_WEAPON5Y` |
| `ST_WPNSX` | macro | `progs/doomgeneric/st_stuff.c:230` | `#define ST_WPNSX` |
| `ST_WPNSY` | macro | `progs/doomgeneric/st_stuff.c:231` | `#define ST_WPNSY` |
| `ST_X` | macro | `progs/doomgeneric/st_stuff.c:83` | `#define ST_X` |
| `ST_X2` | macro | `progs/doomgeneric/st_stuff.c:84` | `#define ST_X2` |
| `ST_calcPainOffset` | function | `progs/doomgeneric/st_stuff.c:665` | `int ST_calcPainOffset(void)` |
| `ST_createWidgets` | function | `progs/doomgeneric/st_stuff.c:1227` | `void ST_createWidgets(void)` |
| `ST_diffDraw` | function | `progs/doomgeneric/st_stuff.c:1049` | `void ST_diffDraw(void)` |
| `ST_doPaletteStuff` | function | `progs/doomgeneric/st_stuff.c:936` | `void ST_doPaletteStuff(void)` |
| `ST_doRefresh` | function | `progs/doomgeneric/st_stuff.c:1036` | `void ST_doRefresh(void)` |
| `ST_drawWidgets` | function | `progs/doomgeneric/st_stuff.c:1001` | `void ST_drawWidgets(boolean refresh)` |
| `ST_initData` | function | `progs/doomgeneric/st_stuff.c:1194` | `void ST_initData(void)` |
| `ST_loadCallback` | function | `progs/doomgeneric/st_stuff.c:1162` | `static void ST_loadCallback(char *lumpname, patch_t **variable)` |
| `ST_loadData` | function | `progs/doomgeneric/st_stuff.c:1172` | `void ST_loadData(void)` |
| `ST_loadGraphics` | function | `progs/doomgeneric/st_stuff.c:1167` | `void ST_loadGraphics(void)` |
| `ST_loadUnloadGraphics` | function | `progs/doomgeneric/st_stuff.c:1076` | `static void ST_loadUnloadGraphics(load_callback_t callback)` |
| `ST_refreshBackground` | function | `progs/doomgeneric/st_stuff.c:416` | `void ST_refreshBackground(void)` |
| `ST_unloadCallback` | function | `progs/doomgeneric/st_stuff.c:1178` | `static void ST_unloadCallback(char *lumpname, patch_t **variable)` |
| `ST_unloadData` | function | `progs/doomgeneric/st_stuff.c:1189` | `void ST_unloadData(void)` |
| `ST_unloadGraphics` | function | `progs/doomgeneric/st_stuff.c:1184` | `void ST_unloadGraphics(void)` |
| `ST_updateFaceWidget` | function | `progs/doomgeneric/st_stuff.c:688` | `void ST_updateFaceWidget(void)` |
| `ST_updateWidgets` | function | `progs/doomgeneric/st_stuff.c:860` | `void ST_updateWidgets(void)` |
| `ST_Drawer` | function | `progs/doomgeneric/st_stuff.h:46` | `void ST_Drawer (boolean fullscreen, boolean refresh);` |
| `ST_HEIGHT` | macro | `progs/doomgeneric/st_stuff.h:30` | `#define ST_HEIGHT` |
| `ST_Init` | function | `progs/doomgeneric/st_stuff.h:52` | `void ST_Init (void);` |
| `ST_Start` | function | `progs/doomgeneric/st_stuff.h:49` | `void ST_Start (void);` |
| `ST_Ticker` | function | `progs/doomgeneric/st_stuff.h:43` | `void ST_Ticker (void);` |
| `ST_WIDTH` | macro | `progs/doomgeneric/st_stuff.h:31` | `#define ST_WIDTH` |
| `ST_Y` | macro | `progs/doomgeneric/st_stuff.h:32` | `#define ST_Y` |
| `__STSTUFF_H__` | macro | `progs/doomgeneric/st_stuff.h:22` | `#define __STSTUFF_H__` |
| `cheat_ammo` | variable | `progs/doomgeneric/st_stuff.h:79` | `extern cheatseq_t cheat_ammo;` |
| `cheat_ammonokey` | variable | `progs/doomgeneric/st_stuff.h:80` | `extern cheatseq_t cheat_ammonokey;` |
| `cheat_choppers` | variable | `progs/doomgeneric/st_stuff.h:84` | `extern cheatseq_t cheat_choppers;` |
| `cheat_clev` | variable | `progs/doomgeneric/st_stuff.h:85` | `extern cheatseq_t cheat_clev;` |
| `cheat_commercial_noclip` | variable | `progs/doomgeneric/st_stuff.h:82` | `extern cheatseq_t cheat_commercial_noclip;` |
| `cheat_god` | variable | `progs/doomgeneric/st_stuff.h:78` | `extern cheatseq_t cheat_god;` |
| `cheat_mus` | variable | `progs/doomgeneric/st_stuff.h:77` | `extern cheatseq_t cheat_mus;` |
| `cheat_mypos` | variable | `progs/doomgeneric/st_stuff.h:86` | `extern cheatseq_t cheat_mypos;` |
| `cheat_noclip` | variable | `progs/doomgeneric/st_stuff.h:81` | `extern cheatseq_t cheat_noclip;` |
| `cheat_powerup` | variable | `progs/doomgeneric/st_stuff.h:83` | `extern cheatseq_t cheat_powerup[7];` |
| `st_backing_screen` | variable | `progs/doomgeneric/st_stuff.h:76` | `extern byte *st_backing_screen;` |
| `DiscoverGamemode` | function | `progs/doomgeneric/statdump.c:71` | `static void DiscoverGamemode(wbstartstruct_t *stats, int num_stats)` |
| `GetNumPlayers` | function | `progs/doomgeneric/statdump.c:130` | `static int GetNumPlayers(wbstartstruct_t *stats)` |
| `MAX_CAPTURES` | macro | `progs/doomgeneric/statdump.c:56` | `#define MAX_CAPTURES` |
| `PrintBanner` | function | `progs/doomgeneric/statdump.c:150` | `static void PrintBanner(FILE *stream)` |
| `PrintFragsTable` | function | `progs/doomgeneric/statdump.c:213` | `static void PrintFragsTable(FILE *stream, wbstartstruct_t *stats)` |
| `PrintLevelName` | function | `progs/doomgeneric/statdump.c:272` | `static void PrintLevelName(FILE *stream, int episode, int level)` |
| `PrintPercentage` | function | `progs/doomgeneric/statdump.c:155` | `static void PrintPercentage(FILE *stream, int amount, int total)` |
| `PrintPlayerStats` | function | `progs/doomgeneric/statdump.c:180` | `static void PrintPlayerStats(FILE *stream, wbstartstruct_t *stats,         int player_num)` |
| `PrintStats` | function | `progs/doomgeneric/statdump.c:301` | `static void PrintStats(FILE *stream, wbstartstruct_t *stats)` |
| `StatCopy` | function | `progs/doomgeneric/statdump.c:333` | `void StatCopy(wbstartstruct_t *stats)` |
| `StatDump` | function | `progs/doomgeneric/statdump.c:343` | `void StatDump(void)` |
| `DOOM_STATDUMP_H` | macro | `progs/doomgeneric/statdump.h:18` | `#define DOOM_STATDUMP_H` |
| `StatCopy` | function | `progs/doomgeneric/statdump.h:20` | `void StatCopy(wbstartstruct_t *stats);` |
| `StatDump` | function | `progs/doomgeneric/statdump.h:21` | `void StatDump(void);` |
| `SlopeDiv` | function | `progs/doomgeneric/tables.c:41` | `int SlopeDiv(unsigned int num, unsigned int den)` |
| `ANG1` | macro | `progs/doomgeneric/tables.h:69` | `#define ANG1` |
| `ANG180` | macro | `progs/doomgeneric/tables.h:65` | `#define ANG180` |
| `ANG1_X` | macro | `progs/doomgeneric/tables.h:75` | `#define ANG1_X` |
| `ANG270` | macro | `progs/doomgeneric/tables.h:66` | `#define ANG270` |
| `ANG45` | macro | `progs/doomgeneric/tables.h:63` | `#define ANG45` |
| `ANG60` | macro | `progs/doomgeneric/tables.h:70` | `#define ANG60` |
| `ANG90` | macro | `progs/doomgeneric/tables.h:64` | `#define ANG90` |
| `ANGLETOFINESHIFT` | macro | `progs/doomgeneric/tables.h:46` | `#define ANGLETOFINESHIFT` |
| `ANG_MAX` | macro | `progs/doomgeneric/tables.h:67` | `#define ANG_MAX` |
| `DBITS` | macro | `progs/doomgeneric/tables.h:79` | `#define DBITS` |
| `FINEANGLES` | macro | `progs/doomgeneric/tables.h:41` | `#define FINEANGLES` |
| `FINEMASK` | macro | `progs/doomgeneric/tables.h:42` | `#define FINEMASK` |
| `SLOPEBITS` | macro | `progs/doomgeneric/tables.h:78` | `#define SLOPEBITS` |
| `SLOPERANGE` | macro | `progs/doomgeneric/tables.h:77` | `#define SLOPERANGE` |
| `SlopeDiv` | function | `progs/doomgeneric/tables.h:92` | `int SlopeDiv(unsigned int num, unsigned int den);` |
| `__TABLES__` | macro | `progs/doomgeneric/tables.h:35` | `#define __TABLES__` |
| `angle_t` | type_alias | `progs/doomgeneric/tables.h:80` | `typedef unsigned angle_t;` |
| `finecosine` | variable | `progs/doomgeneric/tables.h:52` | `extern const fixed_t *finecosine;` |
| `finesine` | variable | `progs/doomgeneric/tables.h:49` | `extern const fixed_t finesine[5*FINEANGLES/4];` |
| `finetangent` | variable | `progs/doomgeneric/tables.h:56` | `extern const fixed_t finetangent[FINEANGLES/2];` |
| `tantoangle` | variable | `progs/doomgeneric/tables.h:87` | `extern const angle_t tantoangle[SLOPERANGE+1];` |
| `V_PATCH_H` | macro | `progs/doomgeneric/v_patch.h:21` | `#define V_PATCH_H` |
| `column_t` | type_alias | `progs/doomgeneric/v_patch.h:47` | `typedef post_t column_t;` |
| `MOUSE_SPEED_BOX_HEIGHT` | macro | `progs/doomgeneric/v_video.c:844` | `#define MOUSE_SPEED_BOX_HEIGHT` |
| `MOUSE_SPEED_BOX_WIDTH` | macro | `progs/doomgeneric/v_video.c:843` | `#define MOUSE_SPEED_BOX_WIDTH` |
| `RANGECHECK` | macro | `progs/doomgeneric/v_video.c:46` | `#define RANGECHECK` |
| `V_CopyRect` | function | `progs/doomgeneric/v_video.c:85` | `void V_CopyRect(int srcx, int srcy, byte *source,                 int width, int height,         ...` |
| `V_DrawAltTLPatch` | function | `progs/doomgeneric/v_video.c:378` | `void V_DrawAltTLPatch(int x, int y, patch_t * patch)` |
| `V_DrawBlock` | function | `progs/doomgeneric/v_video.c:503` | `void V_DrawBlock(int x, int y, int width, int height, byte *src)` |
| `V_DrawBox` | function | `progs/doomgeneric/v_video.c:576` | `void V_DrawBox(int x, int y, int w, int h, int c)` |
| `V_DrawFilledBox` | function | `progs/doomgeneric/v_video.c:529` | `void V_DrawFilledBox(int x, int y, int w, int h, int c)` |
| `V_DrawHorizLine` | function | `progs/doomgeneric/v_video.c:549` | `void V_DrawHorizLine(int x, int y, int w, int c)` |
| `V_DrawMouseSpeedBox` | function | `progs/doomgeneric/v_video.c:846` | `void V_DrawMouseSpeedBox(int speed)` |
| `V_DrawPatch` | function | `progs/doomgeneric/v_video.c:139` | `void V_DrawPatch(int x, int y, patch_t *patch)` |
| `V_DrawPatchDirect` | function | `progs/doomgeneric/v_video.c:268` | `void V_DrawPatchDirect(int x, int y, patch_t *patch)` |
| `V_DrawPatchFlipped` | function | `progs/doomgeneric/v_video.c:203` | `void V_DrawPatchFlipped(int x, int y, patch_t *patch)` |
| `V_DrawRawScreen` | function | `progs/doomgeneric/v_video.c:589` | `void V_DrawRawScreen(byte *raw)` |
| `V_DrawShadowedPatch` | function | `progs/doomgeneric/v_video.c:428` | `void V_DrawShadowedPatch(int x, int y, patch_t *patch)` |
| `V_DrawTLPatch` | function | `progs/doomgeneric/v_video.c:279` | `void V_DrawTLPatch(int x, int y, patch_t * patch)` |
| `V_DrawVertLine` | function | `progs/doomgeneric/v_video.c:562` | `void V_DrawVertLine(int x, int y, int h, int c)` |
| `V_DrawXlaPatch` | function | `progs/doomgeneric/v_video.c:329` | `void V_DrawXlaPatch(int x, int y, patch_t * patch)` |
| `V_Init` | function | `progs/doomgeneric/v_video.c:597` | `void V_Init (void)` |
| `V_LoadTintTable` | function | `progs/doomgeneric/v_video.c:482` | `void V_LoadTintTable(void)` |
| `V_LoadXlaTable` | function | `progs/doomgeneric/v_video.c:493` | `void V_LoadXlaTable(void)` |
| `V_MarkRect` | function | `progs/doomgeneric/v_video.c:69` | `void V_MarkRect(int x, int y, int width, int height)` |
| `V_RestoreBuffer` | function | `progs/doomgeneric/v_video.c:613` | `void V_RestoreBuffer(void)` |
| `V_ScreenShot` | function | `progs/doomgeneric/v_video.c:791` | `void V_ScreenShot(char *format)` |
| `V_SetPatchClipCallback` | function | `progs/doomgeneric/v_video.c:129` | `void V_SetPatchClipCallback(vpatchclipfunc_t func)` |
| `V_UseBuffer` | function | `progs/doomgeneric/v_video.c:606` | `void V_UseBuffer(byte *buffer)` |
| `WritePCXfile` | function | `progs/doomgeneric/v_video.c:653` | `void WritePCXfile(char *filename, byte *data,                   int width, int height,           ...` |
| `WritePNGfile` | function | `progs/doomgeneric/v_video.c:721` | `void WritePNGfile(char *filename, byte *data,                   int width, int height,           ...` |
| `error_fn` | function | `progs/doomgeneric/v_video.c:711` | `static void error_fn(png_structp p, png_const_charp s)` |
| `png_screenshots` | variable | `progs/doomgeneric/v_video.c:800` | `extern int png_screenshots;` |
| `usemouse` | variable | `progs/doomgeneric/v_video.c:848` | `extern int usemouse;` |
| `warning_fn` | function | `progs/doomgeneric/v_video.c:716` | `static void warning_fn(png_structp p, png_const_charp s)` |
| `CENTERY` | macro | `progs/doomgeneric/v_video.h:34` | `#define CENTERY` |
| `V_CopyRect` | function | `progs/doomgeneric/v_video.h:53` | `void V_CopyRect(int srcx, int srcy, byte *source, int width, int height, int destx, int desty);` |
| `V_DrawAltTLPatch` | function | `progs/doomgeneric/v_video.h:60` | `void V_DrawAltTLPatch(int x, int y, patch_t * patch);` |
| `V_DrawBlock` | function | `progs/doomgeneric/v_video.h:67` | `void V_DrawBlock(int x, int y, int width, int height, byte *src);` |
| `V_DrawBox` | function | `progs/doomgeneric/v_video.h:74` | `void V_DrawBox(int x, int y, int w, int h, int c);` |
| `V_DrawFilledBox` | function | `progs/doomgeneric/v_video.h:71` | `void V_DrawFilledBox(int x, int y, int w, int h, int c);` |
| `V_DrawHorizLine` | function | `progs/doomgeneric/v_video.h:72` | `void V_DrawHorizLine(int x, int y, int w, int c);` |
| `V_DrawMouseSpeedBox` | function | `progs/doomgeneric/v_video.h:105` | `void V_DrawMouseSpeedBox(int speed);` |
| `V_DrawPatch` | function | `progs/doomgeneric/v_video.h:57` | `void V_DrawPatch(int x, int y, patch_t *patch);` |
| `V_DrawPatchDirect` | function | `progs/doomgeneric/v_video.h:63` | `void V_DrawPatchDirect(int x, int y, patch_t *patch);` |
| `V_DrawPatchFlipped` | function | `progs/doomgeneric/v_video.h:58` | `void V_DrawPatchFlipped(int x, int y, patch_t *patch);` |
| `V_DrawRawScreen` | function | `progs/doomgeneric/v_video.h:78` | `void V_DrawRawScreen(byte *raw);` |
| `V_DrawShadowedPatch` | function | `progs/doomgeneric/v_video.h:61` | `void V_DrawShadowedPatch(int x, int y, patch_t *patch);` |
| `V_DrawTLPatch` | function | `progs/doomgeneric/v_video.h:59` | `void V_DrawTLPatch(int x, int y, patch_t *patch);` |
| `V_DrawVertLine` | function | `progs/doomgeneric/v_video.h:73` | `void V_DrawVertLine(int x, int y, int h, int c);` |
| `V_DrawXlaPatch` | function | `progs/doomgeneric/v_video.h:62` | `void V_DrawXlaPatch(int x, int y, patch_t * patch);` |
| `V_Init` | function | `progs/doomgeneric/v_video.h:49` | `void V_Init (void);` |
| `V_LoadTintTable` | function | `progs/doomgeneric/v_video.h:97` | `void V_LoadTintTable(void);` |

Next: [SYMBOLS_p19.md](SYMBOLS_p19.md)
