# Subsystem: doomgeneric (page 10 of 12)
Previous: [KB_doomgeneric_p9.md](KB_doomgeneric_p9.md)

## progs/doomgeneric/r_plane.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `R_InitPlanes` (function, line 94) `void R_InitPlanes (void)`
  - `R_MapPlane` (function, line 114) `void
R_MapPlane
( int		y,
  int		x1,
  int		x2 )`
  - `R_ClearPlanes` (function, line 178) `void R_ClearPlanes (void)`
  - `R_FindPlane` (function, line 211) `visplane_t*
R_FindPlane
( fixed_t	height,
  int		picnum,
  int		lightlevel )`
  - `R_CheckPlane` (function, line 259) `visplane_t*
R_CheckPlane
( visplane_t*	pl,
  int		start,
  int		stop )`
  - `R_MakeSpans` (function, line 324) `void
R_MakeSpans
( int		x,
  int		t1,
  int		b1,
  int		t2,
  int		b2 )`
  - `R_DrawPlanes` (function, line 360) `void R_DrawPlanes (void)`
  - `MAXVISPLANES` (macro, line 45) `#define MAXVISPLANES`
  - `MAXOPENINGS` (macro, line 52) `#define MAXOPENINGS`
- Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/r_sky.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/r_plane.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `R_InitPlanes` (function, line 43) `void R_InitPlanes (void);`
  - `R_ClearPlanes` (function, line 44) `void R_ClearPlanes (void);`
  - `R_MapPlane` (function, line 47) `void R_MapPlane ( int y, int x1, int x2 );`
  - `R_MakeSpans` (function, line 53) `void R_MakeSpans ( int x, int t1, int b1, int t2, int b2 );`
  - `R_DrawPlanes` (function, line 60) `void R_DrawPlanes (void);`
  - `R_FindPlane` (function, line 63) `visplane_t* R_FindPlane ( fixed_t height, int picnum, int lightlevel );`
  - `R_CheckPlane` (function, line 69) `visplane_t* R_CheckPlane ( visplane_t* pl, int start, int stop );`
  - `lastopening` (variable, line 29) `extern short* lastopening;`
  - `floorfunc` (variable, line 34) `extern planefunction_t floorfunc;`
  - `ceilingfunc_t` (variable, line 35) `extern planefunction_t ceilingfunc_t;`
  - `floorclip` (variable, line 37) `extern short floorclip[SCREENWIDTH];`
  - `ceilingclip` (variable, line 38) `extern short ceilingclip[SCREENWIDTH];`
  - `yslope` (variable, line 40) `extern fixed_t yslope[SCREENHEIGHT];`
  - `distscale` (variable, line 41) `extern fixed_t distscale[SCREENWIDTH];`
  - `__R_PLANE__` (macro, line 21) `#define __R_PLANE__`
- Depends on: `progs/doomgeneric/r_data.h`
- Imported by: `progs/doomgeneric/r_bsp.c`, `progs/doomgeneric/r_local.h`

## progs/doomgeneric/r_segs.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `R_RenderMaskedSegRange` (function, line 96) `void
R_RenderMaskedSegRange
( drawseg_t*	ds,
  int		x1,
  int		x2 )`
  - `R_RenderSegLoop` (function, line 199) `void R_RenderSegLoop (void)`
  - `R_StoreWallRange` (function, line 372) `void
R_StoreWallRange
( int	start,
  int	stop )`
  - `HEIGHTBITS` (macro, line 196) `#define HEIGHTBITS`
  - `HEIGHTUNIT` (macro, line 197) `#define HEIGHTUNIT`
- Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/r_sky.h`

## progs/doomgeneric/r_segs.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `R_RenderMaskedSegRange` (function, line 27) `void R_RenderMaskedSegRange ( drawseg_t* ds, int x1, int x2 );`
  - `__R_SEGS__` (macro, line 21) `#define __R_SEGS__`
- Imported by: `progs/doomgeneric/r_local.h`

## progs/doomgeneric/r_sky.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `R_InitSkyMap` (function, line 47) `void R_InitSkyMap (void)`
- Depends on: `progs/doomgeneric/m_fixed.h`, `progs/doomgeneric/r_data.h`, `progs/doomgeneric/r_sky.h`

## progs/doomgeneric/r_sky.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `R_InitSkyMap` (function, line 35) `void R_InitSkyMap (void);`
  - `skytexture` (variable, line 31) `extern int skytexture;`
  - `skytexturemid` (variable, line 32) `extern int skytexturemid;`
  - `__R_SKY__` (macro, line 21) `#define __R_SKY__`
  - `SKYFLATNAME` (macro, line 26) `#define			SKYFLATNAME`
  - `ANGLETOSKYSHIFT` (macro, line 29) `#define ANGLETOSKYSHIFT`
- Imported by: `progs/doomgeneric/g_game.c`, `progs/doomgeneric/r_data.c`, `progs/doomgeneric/r_main.c`, `progs/doomgeneric/r_plane.c`, `progs/doomgeneric/r_segs.c`, `progs/doomgeneric/r_sky.c`

## progs/doomgeneric/r_state.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `textureheight` (variable, line 38) `extern fixed_t* textureheight;`
  - `spritewidth` (variable, line 41) `extern fixed_t* spritewidth;`
  - `spriteoffset` (variable, line 43) `extern fixed_t* spriteoffset;`
  - `spritetopoffset` (variable, line 44) `extern fixed_t* spritetopoffset;`
  - `colormaps` (variable, line 46) `extern lighttable_t* colormaps;`
  - `viewwidth` (variable, line 48) `extern int viewwidth;`
  - `scaledviewwidth` (variable, line 49) `extern int scaledviewwidth;`
  - `viewheight` (variable, line 50) `extern int viewheight;`
  - `firstflat` (variable, line 52) `extern int firstflat;`
  - `flattranslation` (variable, line 55) `extern int* flattranslation;`
  - `texturetranslation` (variable, line 56) `extern int* texturetranslation;`
  - `firstspritelump` (variable, line 60) `extern int firstspritelump;`
  - `lastspritelump` (variable, line 61) `extern int lastspritelump;`
  - `numspritelumps` (variable, line 62) `extern int numspritelumps;`
  - `numsprites` (variable, line 69) `extern int numsprites;`
  - `sprites` (variable, line 70) `extern spritedef_t* sprites;`
  - `numvertexes` (variable, line 72) `extern int numvertexes;`
  - `vertexes` (variable, line 73) `extern vertex_t* vertexes;`
  - `numsegs` (variable, line 75) `extern int numsegs;`
  - `segs` (variable, line 76) `extern seg_t* segs;`
  - `numsectors` (variable, line 78) `extern int numsectors;`
  - `sectors` (variable, line 79) `extern sector_t* sectors;`
  - `numsubsectors` (variable, line 81) `extern int numsubsectors;`
  - `subsectors` (variable, line 82) `extern subsector_t* subsectors;`
  - `numnodes` (variable, line 84) `extern int numnodes;`
  - `nodes` (variable, line 85) `extern node_t* nodes;`
  - `numlines` (variable, line 87) `extern int numlines;`
  - `lines` (variable, line 88) `extern line_t* lines;`
  - `numsides` (variable, line 90) `extern int numsides;`
  - `sides` (variable, line 91) `extern side_t* sides;`
  - `viewx` (variable, line 97) `extern fixed_t viewx;`
  - `viewy` (variable, line 98) `extern fixed_t viewy;`
  - `viewz` (variable, line 99) `extern fixed_t viewz;`
  - `viewangle` (variable, line 101) `extern angle_t viewangle;`
  - `viewplayer` (variable, line 102) `extern player_t* viewplayer;`
  - `clipangle` (variable, line 106) `extern angle_t clipangle;`
  - `viewangletox` (variable, line 108) `extern int viewangletox[FINEANGLES/2];`
  - `xtoviewangle` (variable, line 109) `extern angle_t xtoviewangle[SCREENWIDTH+1];`
  - `rw_distance` (variable, line 112) `extern fixed_t rw_distance;`
  - `rw_normalangle` (variable, line 113) `extern angle_t rw_normalangle;`
  - `rw_angle1` (variable, line 118) `extern int rw_angle1;`
  - `sscount` (variable, line 121) `extern int sscount;`
  - `floorplane` (variable, line 123) `extern visplane_t* floorplane;`
  - `ceilingplane` (variable, line 124) `extern visplane_t* ceilingplane;`
  - `__R_STATE__` (macro, line 21) `#define __R_STATE__`
- Depends on: `progs/doomgeneric/d_player.h`, `progs/doomgeneric/r_data.h`
- Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/f_finale.c`, `progs/doomgeneric/p_ceilng.c`, `progs/doomgeneric/p_doors.c`, `progs/doomgeneric/p_enemy.c`, `progs/doomgeneric/p_floor.c`, `progs/doomgeneric/p_lights.c`, `progs/doomgeneric/p_map.c`, `progs/doomgeneric/p_maputl.c`, `progs/doomgeneric/p_plats.c`, `progs/doomgeneric/p_saveg.c`, `progs/doomgeneric/p_sight.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/p_switch.c`, `progs/doomgeneric/p_telept.c`, `progs/doomgeneric/r_bsp.c`, `progs/doomgeneric/r_data.h`

## progs/doomgeneric/r_things.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `maskdraw_t` (struct, line 48)
  - `R_InstallSpriteLump` (function, line 100) `void
R_InstallSpriteLump
( int		lump,
  unsigned	frame,
  unsigned	rotation,
  boolean	flipped )`
  - `R_InitSpriteDefs` (function, line 171) `void R_InitSpriteDefs (char** namelist)`
  - `R_InitSprites` (function, line 291) `void R_InitSprites (char** namelist)`
  - `R_ClearSprites` (function, line 309) `void R_ClearSprites (void)`
  - `R_NewVisSprite` (function, line 320) `vissprite_t* R_NewVisSprite (void)`
  - `R_DrawMaskedColumn` (function, line 343) `void R_DrawMaskedColumn (column_t* column)`
  - `R_DrawVisSprite` (function, line 389) `void
R_DrawVisSprite
( vissprite_t*		vis,
  int			x1,
  int			x2 )`
  - `R_ProjectSprite` (function, line 444) `void R_ProjectSprite (mobj_t* thing)`
  - `R_AddSprites` (function, line 605) `void R_AddSprites (sector_t* sec)`
  - `R_DrawPSprite` (function, line 638) `void R_DrawPSprite (pspdef_t* psp)`
  - `R_DrawPlayerSprites` (function, line 738) `void R_DrawPlayerSprites (void)`
  - `R_SortVisSprites` (function, line 779) `void R_SortVisSprites (void)`
  - `R_DrawSprite` (function, line 837) `void R_DrawSprite (vissprite_t* spr)`
  - `R_DrawMasked` (function, line 951) `void R_DrawMasked (void)`
  - `MINZ` (macro, line 40) `#define MINZ`
  - `BASEYCENTER` (macro, line 41) `#define BASEYCENTER`
- Depends on: `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/r_things.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `R_DrawMaskedColumn` (function, line 46) `void R_DrawMaskedColumn (column_t* column);`
  - `R_SortVisSprites` (function, line 49) `void R_SortVisSprites (void);`
  - `R_AddSprites` (function, line 51) `void R_AddSprites (sector_t* sec);`
  - `R_AddPSprites` (function, line 52) `void R_AddPSprites (void);`
  - `R_DrawSprites` (function, line 53) `void R_DrawSprites (void);`
  - `R_InitSprites` (function, line 54) `void R_InitSprites (char** namelist);`
  - `R_ClearSprites` (function, line 55) `void R_ClearSprites (void);`
  - `R_DrawMasked` (function, line 56) `void R_DrawMasked (void);`
  - `R_ClipVisSprite` (function, line 59) `void R_ClipVisSprite ( vissprite_t* vis, int xl, int xh );`
  - `vissprites` (variable, line 27) `extern vissprite_t vissprites[MAXVISSPRITES];`
  - `vissprite_p` (variable, line 28) `extern vissprite_t* vissprite_p;`
  - `vsprsortedhead` (variable, line 29) `extern vissprite_t vsprsortedhead;`
  - `negonearray` (variable, line 33) `extern short negonearray[SCREENWIDTH];`
  - `screenheightarray` (variable, line 34) `extern short screenheightarray[SCREENWIDTH];`
  - `mfloorclip` (variable, line 37) `extern short* mfloorclip;`
  - `mceilingclip` (variable, line 38) `extern short* mceilingclip;`
  - `spryscale` (variable, line 39) `extern fixed_t spryscale;`
  - `sprtopscreen` (variable, line 40) `extern fixed_t sprtopscreen;`
  - `pspritescale` (variable, line 42) `extern fixed_t pspritescale;`
  - `pspriteiscale` (variable, line 43) `extern fixed_t pspriteiscale;`
  - `__R_THINGS__` (macro, line 21) `#define __R_THINGS__`
  - `MAXVISSPRITES` (macro, line 25) `#define MAXVISSPRITES`
- Imported by: `progs/doomgeneric/r_bsp.c`, `progs/doomgeneric/r_local.h`

## progs/doomgeneric/s_sound.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `channel_t` (struct, line 66)
  - `S_Init` (function, line 114) `void S_Init(int sfxVolume, int musicVolume)`
  - `S_Shutdown` (function, line 146) `void S_Shutdown(void)`
  - `S_StopChannel` (function, line 152) `static void S_StopChannel(int cnum)`
  - `S_Start` (function, line 191) `void S_Start(void)`
  - `S_StopSound` (function, line 243) `void S_StopSound(mobj_t *origin)`
  - `S_GetChannel` (function, line 262) `static int S_GetChannel(mobj_t *origin, sfxinfo_t *sfxinfo)`
  - `S_AdjustSoundParams` (function, line 323) `static int S_AdjustSoundParams(mobj_t *listener, mobj_t *source,
                               i...`
  - `S_StartSound` (function, line 391) `void S_StartSound(void *origin_p, int sfx_id)`
  - `S_PauseSound` (function, line 482) `void S_PauseSound(void)`
  - `S_ResumeSound` (function, line 491) `void S_ResumeSound(void)`
  - `S_UpdateSounds` (function, line 504) `void S_UpdateSounds(mobj_t *listener)`
  - `S_SetMusicVolume` (function, line 571) `void S_SetMusicVolume(int volume)`
  - `S_SetSfxVolume` (function, line 582) `void S_SetSfxVolume(int volume)`
  - `S_StartMusic` (function, line 596) `void S_StartMusic(int m_id)`
  - `S_ChangeMusic` (function, line 601) `void S_ChangeMusic(int musicnum, int looping)`
  - `S_MusicPlaying` (function, line 649) `boolean S_MusicPlaying(void)`
  - `S_StopMusic` (function, line 654) `void S_StopMusic(void)`
  - `S_CLIPPING_DIST` (macro, line 44) `#define S_CLIPPING_DIST`
  - `S_CLOSE_DIST` (macro, line 52) `#define S_CLOSE_DIST`
  - `S_ATTENUATOR` (macro, line 56) `#define S_ATTENUATOR`
  - `S_STEREO_SWING` (macro, line 60) `#define S_STEREO_SWING`
  - `NORM_PITCH` (macro, line 62) `#define NORM_PITCH`
  - `NORM_PRIORITY` (macro, line 63) `#define NORM_PRIORITY`
  - `NORM_SEP` (macro, line 64) `#define NORM_SEP`
- Depends on: `progs/doomgeneric/deh_str.h`, `progs/doomgeneric/doomfeatures.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_sound.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/s_sound.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `S_Init` (function, line 32) `void S_Init(int sfxVolume, int musicVolume);`
  - `S_Shutdown` (function, line 37) `void S_Shutdown(void);`
  - `S_Start` (function, line 47) `void S_Start(void);`
  - `S_StartSound` (function, line 54) `void S_StartSound(void *origin, int sound_id);`
  - `S_StopSound` (function, line 57) `void S_StopSound(mobj_t *origin);`
  - `S_StartMusic` (function, line 61) `void S_StartMusic(int music_id);`
  - `S_ChangeMusic` (function, line 65) `void S_ChangeMusic(int music_id, int looping);`
  - `S_StopMusic` (function, line 71) `void S_StopMusic(void);`
  - `S_PauseSound` (function, line 74) `void S_PauseSound(void);`
  - `S_ResumeSound` (function, line 75) `void S_ResumeSound(void);`
  - `S_UpdateSounds` (function, line 81) `void S_UpdateSounds(mobj_t *listener);`
  - `S_SetMusicVolume` (function, line 83) `void S_SetMusicVolume(int volume);`
  - `S_SetSfxVolume` (function, line 84) `void S_SetSfxVolume(int volume);`
  - `snd_channels` (variable, line 86) `extern int snd_channels;`
  - `__S_SOUND__` (macro, line 21) `#define __S_SOUND__`
- Depends on: `progs/doomgeneric/p_mobj.h`, `progs/doomgeneric/sounds.h`
- Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/doomgeneric_minios.c`, `progs/doomgeneric/f_finale.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/p_ceilng.c`, `progs/doomgeneric/p_doors.c`, `progs/doomgeneric/p_enemy.c`, `progs/doomgeneric/p_floor.c`, `progs/doomgeneric/p_inter.c`, `progs/doomgeneric/p_map.c`, `progs/doomgeneric/p_mobj.c`, `progs/doomgeneric/p_plats.c`, `progs/doomgeneric/p_pspr.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/p_switch.c`, `progs/doomgeneric/p_telept.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/wi_stuff.c`

## progs/doomgeneric/sha1.c
- Doc: SHA1 hash function
- Layer: utility
- Language: c
- Symbols:
  - `SHA1_Init` (function, line 40) `void SHA1_Init(sha1_context_t *hd)`
  - `Transform` (function, line 55) `static void Transform(sha1_context_t *hd, byte *data)`
  - `SHA1_Update` (function, line 198) `void SHA1_Update(sha1_context_t *hd, byte *inbuf, size_t inlen)`
  - `SHA1_Final` (function, line 238) `void SHA1_Final(sha1_digest_t digest, sha1_context_t *hd)`
  - `SHA1_UpdateInt32` (function, line 303) `void SHA1_UpdateInt32(sha1_context_t *context, unsigned int val)`
  - `SHA1_UpdateString` (function, line 315) `void SHA1_UpdateString(sha1_context_t *context, char *str)`
  - `K1` (macro, line 84) `#define K1`
  - `K2` (macro, line 85) `#define K2`
  - `K3` (macro, line 86) `#define K3`
  - `K4` (macro, line 87) `#define K4`
  - `F1` (macro, line 88) `#define F1(x,y,z)`
  - `F2` (macro, line 89) `#define F2(x,y,z)`
  - `F3` (macro, line 90) `#define F3(x,y,z)`
  - `F4` (macro, line 91) `#define F4(x,y,z)`
  - `rol` (macro, line 93) `#define rol(x,n)`
  - `M` (macro, line 95) `#define M(i)`
  - `R` (macro, line 99) `#define R(a,b,c,d,e,f,k,m)`
  - `X` (macro, line 288) `#define X(a)`
  - `X` (macro, line 290) `#define X(a)`
- Depends on: `kernel/string.c`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/sha1.h`

## progs/doomgeneric/sha1.h
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it...
- Layer: utility
- Language: h
- Symbols:
  - `sha1_context_s` (struct, line 26)
  - `sha1_context_t` (type_alias, line 22) `typedef struct sha1_context_s sha1_context_t;`
  - `sha1_digest_t` (type_alias, line 24) `typedef byte sha1_digest_t[20];`
  - `SHA1_Init` (function, line 33) `void SHA1_Init(sha1_context_t *context);`
  - `SHA1_Update` (function, line 34) `void SHA1_Update(sha1_context_t *context, byte *buf, size_t len);`
  - `SHA1_Final` (function, line 35) `void SHA1_Final(sha1_digest_t digest, sha1_context_t *context);`
  - `SHA1_UpdateInt32` (function, line 36) `void SHA1_UpdateInt32(sha1_context_t *context, unsigned int val);`
  - `SHA1_UpdateString` (function, line 37) `void SHA1_UpdateString(sha1_context_t *context, char *str);`
  - `__SHA1_H__` (macro, line 19) `#define __SHA1_H__`
- Depends on: `progs/doomgeneric/doomtype.h`
- Imported by: `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/net_client.h`, `progs/doomgeneric/net_defs.h`, `progs/doomgeneric/sha1.c`, `progs/doomgeneric/w_checksum.c`

## progs/doomgeneric/sounds.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `MUSIC` (macro, line 31) `#define MUSIC(name)`
  - `SOUND` (macro, line 111) `#define SOUND(name, priority)`
  - `SOUND_LINK` (macro, line 113) `#define SOUND_LINK(name, priority, link_id, pitch, volume)`
- Depends on: `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/sounds.h`

## progs/doomgeneric/sounds.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `S_sfx` (variable, line 26) `extern sfxinfo_t S_sfx[];`
  - `S_music` (variable, line 29) `extern musicinfo_t S_music[];`
  - `__SOUNDS__` (macro, line 21) `#define __SOUNDS__`
- Depends on: `progs/doomgeneric/i_sound.h`
- Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/f_finale.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/info.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/p_ceilng.c`, `progs/doomgeneric/p_doors.c`, `progs/doomgeneric/p_enemy.c`, `progs/doomgeneric/p_floor.c`, `progs/doomgeneric/p_inter.c`, `progs/doomgeneric/p_map.c`, `progs/doomgeneric/p_mobj.c`, `progs/doomgeneric/p_plats.c`, `progs/doomgeneric/p_pspr.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/p_switch.c`, `progs/doomgeneric/p_telept.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/wi_stuff.c`

## progs/doomgeneric/st_lib.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `STlib_init` (function, line 51) `void STlib_init(void)`
  - `STlib_initNum` (function, line 59) `void
STlib_initNum
( st_number_t*		n,
  int			x,
  int			y,
  patch_t**		pl,
  int*			num,
  bool...`
  - `STlib_drawNum` (function, line 84) `void
STlib_drawNum
( st_number_t*	n,
  boolean	refresh )`
  - `STlib_updateNum` (function, line 146) `void
STlib_updateNum
( st_number_t*		n,
  boolean		refresh )`
  - `STlib_initPercent` (function, line 156) `void
STlib_initPercent
( st_percent_t*		p,
  int			x,
  int			y,
  patch_t**		pl,
  int*			num,
 ...`
  - `STlib_updatePercent` (function, line 173) `void
STlib_updatePercent
( st_percent_t*		per,
  int			refresh )`
  - `STlib_initMultIcon` (function, line 186) `void
STlib_initMultIcon
( st_multicon_t*	i,
  int			x,
  int			y,
  patch_t**		il,
  int*			inum,...`
  - `STlib_updateMultIcon` (function, line 205) `void
STlib_updateMultIcon
( st_multicon_t*	mi,
  boolean		refresh )`
  - `STlib_initBinIcon` (function, line 236) `void
STlib_initBinIcon
( st_binicon_t*		b,
  int			x,
  int			y,
  patch_t*		i,
  boolean*		val,
...`
  - `STlib_updateBinIcon` (function, line 255) `void
STlib_updateBinIcon
( st_binicon_t*		bi,
  boolean		refresh )`
  - `automapactive` (variable, line 40) `extern boolean automapactive;`
- Depends on: `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/st_lib.h`, `progs/doomgeneric/st_stuff.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/st_lib.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `st_number_t` (struct, line 32)
  - `st_percent_t` (struct, line 64)
  - `st_multicon_t` (struct, line 77)
  - `st_binicon_t` (struct, line 106)
  - `STlib_init` (function, line 138) `void STlib_init(void);`
  - `STlib_initNum` (function, line 144) `void STlib_initNum ( st_number_t* n, int x, int y, patch_t** pl, int* num, boolean* on, int width );`
  - `STlib_updateNum` (function, line 154) `void STlib_updateNum ( st_number_t* n, boolean refresh );`
  - `STlib_initPercent` (function, line 161) `void STlib_initPercent ( st_percent_t* p, int x, int y, patch_t** pl, int* num, boolean* on, patch_t* percent );`
  - `STlib_updatePercent` (function, line 172) `void STlib_updatePercent ( st_percent_t* per, int refresh );`
  - `STlib_initMultIcon` (function, line 179) `void STlib_initMultIcon ( st_multicon_t* mi, int x, int y, patch_t** il, int* inum, boolean* on );`
  - `STlib_updateMultIcon` (function, line 189) `void STlib_updateMultIcon ( st_multicon_t* mi, boolean refresh );`
  - `STlib_initBinIcon` (function, line 196) `void STlib_initBinIcon ( st_binicon_t* b, int x, int y, patch_t* i, boolean* val, boolean* on );`
  - `STlib_updateBinIcon` (function, line 205) `void STlib_updateBinIcon ( st_binicon_t* bi, boolean refresh );`
  - `__STLIB__` (macro, line 20) `#define __STLIB__`
- Depends on: `progs/doomgeneric/r_defs.h`
- Imported by: `progs/doomgeneric/st_lib.c`, `progs/doomgeneric/st_stuff.c`


Next: [KB_doomgeneric_p11.md](KB_doomgeneric_p11.md)
