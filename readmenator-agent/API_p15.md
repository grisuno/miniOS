# API (page 15 of 21)
Previous: [API_p14.md](API_p14.md)

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

## progs/doomgeneric/r_things.c
Depends on: `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`
- `R_InstallSpriteLump` (function) `progs/doomgeneric/r_things.c:100` `void
R_InstallSpriteLump
( int		lump,
  unsigned	frame,
  unsigned	rotation,
  boolean	flipped )`
- `R_InitSpriteDefs` (function) `progs/doomgeneric/r_things.c:171` `void R_InitSpriteDefs (char** namelist)` -- R_InitSpriteDefs Pass a null terminated list of sprite names (4 chars exactly) to be used.
- `R_InitSprites` (function) `progs/doomgeneric/r_things.c:291` `void R_InitSprites (char** namelist)` -- R_InitSprites Called at program start.
- `R_ClearSprites` (function) `progs/doomgeneric/r_things.c:309` `void R_ClearSprites (void)` -- R_ClearSprites Called at frame start.
- `R_NewVisSprite` (function) `progs/doomgeneric/r_things.c:320` `vissprite_t* R_NewVisSprite (void)`
- `R_DrawMaskedColumn` (function) `progs/doomgeneric/r_things.c:343` `void R_DrawMaskedColumn (column_t* column)`
- `R_DrawVisSprite` (function) `progs/doomgeneric/r_things.c:389` `void
R_DrawVisSprite
( vissprite_t*		vis,
  int			x1,
  int			x2 )`
- `R_ProjectSprite` (function) `progs/doomgeneric/r_things.c:444` `void R_ProjectSprite (mobj_t* thing)` -- R_ProjectSprite Generates a vissprite for a thing if it might be visible.
- `R_AddSprites` (function) `progs/doomgeneric/r_things.c:605` `void R_AddSprites (sector_t* sec)` -- R_AddSprites During BSP traversal, this adds sprites by sector.
- `R_DrawPSprite` (function) `progs/doomgeneric/r_things.c:638` `void R_DrawPSprite (pspdef_t* psp)` -- R_DrawPSprite
- `R_DrawPlayerSprites` (function) `progs/doomgeneric/r_things.c:738` `void R_DrawPlayerSprites (void)` -- R_DrawPlayerSprites
- `R_SortVisSprites` (function) `progs/doomgeneric/r_things.c:779` `void R_SortVisSprites (void)`
- `R_DrawSprite` (function) `progs/doomgeneric/r_things.c:837` `void R_DrawSprite (vissprite_t* spr)`
- `R_DrawMasked` (function) `progs/doomgeneric/r_things.c:951` `void R_DrawMasked (void)` -- R_DrawMasked

## progs/doomgeneric/r_things.h
Imported by: `progs/doomgeneric/r_bsp.c`, `progs/doomgeneric/r_local.h`
- `R_DrawMaskedColumn` (function) `progs/doomgeneric/r_things.h:46` `void R_DrawMaskedColumn (column_t* column);`
- `R_SortVisSprites` (function) `progs/doomgeneric/r_things.h:49` `void R_SortVisSprites (void);`
- `R_AddSprites` (function) `progs/doomgeneric/r_things.h:51` `void R_AddSprites (sector_t* sec);`
- `R_AddPSprites` (function) `progs/doomgeneric/r_things.h:52` `void R_AddPSprites (void);`
- `R_DrawSprites` (function) `progs/doomgeneric/r_things.h:53` `void R_DrawSprites (void);`
- `R_InitSprites` (function) `progs/doomgeneric/r_things.h:54` `void R_InitSprites (char** namelist);`
- `R_ClearSprites` (function) `progs/doomgeneric/r_things.h:55` `void R_ClearSprites (void);`
- `R_DrawMasked` (function) `progs/doomgeneric/r_things.h:56` `void R_DrawMasked (void);`
- `R_ClipVisSprite` (function) `progs/doomgeneric/r_things.h:59` `void R_ClipVisSprite ( vissprite_t* vis, int xl, int xh );`

## progs/doomgeneric/s_sound.c
Depends on: `progs/doomgeneric/deh_str.h`, `progs/doomgeneric/doomfeatures.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_sound.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`
- `S_Init` (function) `progs/doomgeneric/s_sound.c:114` `void S_Init(int sfxVolume, int musicVolume)`
- `S_Shutdown` (function) `progs/doomgeneric/s_sound.c:146` `void S_Shutdown(void)`
- `S_StopChannel` (function) `progs/doomgeneric/s_sound.c:152` `static void S_StopChannel(int cnum)`
- `S_Start` (function) `progs/doomgeneric/s_sound.c:191` `void S_Start(void)`
- `S_StopSound` (function) `progs/doomgeneric/s_sound.c:243` `void S_StopSound(mobj_t *origin)`
- `S_GetChannel` (function) `progs/doomgeneric/s_sound.c:262` `static int S_GetChannel(mobj_t *origin, sfxinfo_t *sfxinfo)`
- `S_AdjustSoundParams` (function) `progs/doomgeneric/s_sound.c:323` `static int S_AdjustSoundParams(mobj_t *listener, mobj_t *source,
                               i...`
- `S_StartSound` (function) `progs/doomgeneric/s_sound.c:391` `void S_StartSound(void *origin_p, int sfx_id)`
- `S_PauseSound` (function) `progs/doomgeneric/s_sound.c:482` `void S_PauseSound(void)`
- `S_ResumeSound` (function) `progs/doomgeneric/s_sound.c:491` `void S_ResumeSound(void)`
- `S_UpdateSounds` (function) `progs/doomgeneric/s_sound.c:504` `void S_UpdateSounds(mobj_t *listener)`
- `S_SetMusicVolume` (function) `progs/doomgeneric/s_sound.c:571` `void S_SetMusicVolume(int volume)`
- `S_SetSfxVolume` (function) `progs/doomgeneric/s_sound.c:582` `void S_SetSfxVolume(int volume)`
- `S_StartMusic` (function) `progs/doomgeneric/s_sound.c:596` `void S_StartMusic(int m_id)`
- `S_ChangeMusic` (function) `progs/doomgeneric/s_sound.c:601` `void S_ChangeMusic(int musicnum, int looping)`
- `S_MusicPlaying` (function) `progs/doomgeneric/s_sound.c:649` `boolean S_MusicPlaying(void)`
- `S_StopMusic` (function) `progs/doomgeneric/s_sound.c:654` `void S_StopMusic(void)`

## progs/doomgeneric/s_sound.h
Depends on: `progs/doomgeneric/p_mobj.h`, `progs/doomgeneric/sounds.h`
Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/doomgeneric_minios.c`, `progs/doomgeneric/f_finale.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/p_ceilng.c`, `progs/doomgeneric/p_doors.c`, `progs/doomgeneric/p_enemy.c`, `progs/doomgeneric/p_floor.c`, `progs/doomgeneric/p_inter.c`, `progs/doomgeneric/p_map.c`, `progs/doomgeneric/p_mobj.c`, `progs/doomgeneric/p_plats.c`, `progs/doomgeneric/p_pspr.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/p_switch.c`, `progs/doomgeneric/p_telept.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/wi_stuff.c`
- `S_Init` (function) `progs/doomgeneric/s_sound.h:32` `void S_Init(int sfxVolume, int musicVolume);`
- `S_Shutdown` (function) `progs/doomgeneric/s_sound.h:37` `void S_Shutdown(void);`
- `S_Start` (function) `progs/doomgeneric/s_sound.h:47` `void S_Start(void);`
- `S_StartSound` (function) `progs/doomgeneric/s_sound.h:54` `void S_StartSound(void *origin, int sound_id);`
- `S_StopSound` (function) `progs/doomgeneric/s_sound.h:57` `void S_StopSound(mobj_t *origin);` -- Stop sound for thing at <origin>
- `S_StartMusic` (function) `progs/doomgeneric/s_sound.h:61` `void S_StartMusic(int music_id);` -- Start music using <music_id> from sounds.h
- `S_ChangeMusic` (function) `progs/doomgeneric/s_sound.h:65` `void S_ChangeMusic(int music_id, int looping);` -- Start music using <music_id> from sounds.h, and set whether looping
- `S_StopMusic` (function) `progs/doomgeneric/s_sound.h:71` `void S_StopMusic(void);` -- Stops the music fer sure.
- `S_PauseSound` (function) `progs/doomgeneric/s_sound.h:74` `void S_PauseSound(void);` -- Stop and resume music, during game PAUSE.
- `S_ResumeSound` (function) `progs/doomgeneric/s_sound.h:75` `void S_ResumeSound(void);`
- `S_UpdateSounds` (function) `progs/doomgeneric/s_sound.h:81` `void S_UpdateSounds(mobj_t *listener);` -- Updates music & sounds
- `S_SetMusicVolume` (function) `progs/doomgeneric/s_sound.h:83` `void S_SetMusicVolume(int volume);`
- `S_SetSfxVolume` (function) `progs/doomgeneric/s_sound.h:84` `void S_SetSfxVolume(int volume);`

## progs/doomgeneric/sha1.c
Depends on: `kernel/string.c`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/sha1.h`
- `SHA1_Init` (function) `progs/doomgeneric/sha1.c:40` `void SHA1_Init(sha1_context_t *hd)`
- `Transform` (function) `progs/doomgeneric/sha1.c:55` `static void Transform(sha1_context_t *hd, byte *data)` -- Transform the message X which consists of 16 32-bit-words
- `SHA1_Update` (function) `progs/doomgeneric/sha1.c:198` `void SHA1_Update(sha1_context_t *hd, byte *inbuf, size_t inlen)` -- Update the message digest with the contents of INBUF with length INLEN.
- `SHA1_Final` (function) `progs/doomgeneric/sha1.c:238` `void SHA1_Final(sha1_digest_t digest, sha1_context_t *hd)`
- `SHA1_UpdateInt32` (function) `progs/doomgeneric/sha1.c:303` `void SHA1_UpdateInt32(sha1_context_t *context, unsigned int val)`
- `SHA1_UpdateString` (function) `progs/doomgeneric/sha1.c:315` `void SHA1_UpdateString(sha1_context_t *context, char *str)`

## progs/doomgeneric/sha1.h
Depends on: `progs/doomgeneric/doomtype.h`
Imported by: `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/net_client.h`, `progs/doomgeneric/net_defs.h`, `progs/doomgeneric/sha1.c`, `progs/doomgeneric/w_checksum.c`
- `SHA1_Init` (function) `progs/doomgeneric/sha1.h:33` `void SHA1_Init(sha1_context_t *context);`
- `SHA1_Update` (function) `progs/doomgeneric/sha1.h:34` `void SHA1_Update(sha1_context_t *context, byte *buf, size_t len);`
- `SHA1_Final` (function) `progs/doomgeneric/sha1.h:35` `void SHA1_Final(sha1_digest_t digest, sha1_context_t *context);`
- `SHA1_UpdateInt32` (function) `progs/doomgeneric/sha1.h:36` `void SHA1_UpdateInt32(sha1_context_t *context, unsigned int val);`
- `SHA1_UpdateString` (function) `progs/doomgeneric/sha1.h:37` `void SHA1_UpdateString(sha1_context_t *context, char *str);`

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


Next: [API_p16.md](API_p16.md)
