# `progs/doomgeneric/r_state.h`

> Source: [progs/doomgeneric/r_state.h:1](../../progs/doomgeneric/r_state.h#L1) | language `h` | coverage 50.0% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Refresh/render internal state variables (global).     Need data structure definitions.

## Contents

- **Macros:** [`__R_STATE__`](#__r_state__)
- **Variables:** [`textureheight`](#textureheight), [`spritewidth`](#spritewidth), [`spriteoffset`](#spriteoffset), [`spritetopoffset`](#spritetopoffset), [`colormaps`](#colormaps), [`viewwidth`](#viewwidth), [`scaledviewwidth`](#scaledviewwidth), [`viewheight`](#viewheight), [`firstflat`](#firstflat), [`flattranslation`](#flattranslation), [`texturetranslation`](#texturetranslation), [`firstspritelump`](#firstspritelump), [`lastspritelump`](#lastspritelump), [`numspritelumps`](#numspritelumps), [`numsprites`](#numsprites), [`sprites`](#sprites), [`numvertexes`](#numvertexes), [`vertexes`](#vertexes), [`numsegs`](#numsegs), [`segs`](#segs), [`numsectors`](#numsectors), [`sectors`](#sectors), [`numsubsectors`](#numsubsectors), [`subsectors`](#subsectors), [`numnodes`](#numnodes), [`nodes`](#nodes), [`numlines`](#numlines), [`lines`](#lines), [`numsides`](#numsides), [`sides`](#sides), [`viewx`](#viewx), [`viewy`](#viewy), [`viewz`](#viewz), [`viewangle`](#viewangle), [`viewplayer`](#viewplayer), [`clipangle`](#clipangle), [`viewangletox`](#viewangletox), [`xtoviewangle`](#xtoviewangle), [`rw_distance`](#rw_distance), [`rw_normalangle`](#rw_normalangle), [`rw_angle1`](#rw_angle1), [`sscount`](#sscount), [`floorplane`](#floorplane), [`ceilingplane`](#ceilingplane)

## Macros

<a id="__r_state__"></a>

### `__R_STATE__`

`macro` | [progs/doomgeneric/r_state.h:21](../../progs/doomgeneric/r_state.h#L21)

```c
#define __R_STATE__
```

---

## Variables

<a id="textureheight"></a>

### `textureheight`

`variable` `extern` | [progs/doomgeneric/r_state.h:38](../../progs/doomgeneric/r_state.h#L38)

```c
extern fixed_t* textureheight;
```

needed for texture pegging

---

<a id="spritewidth"></a>

### `spritewidth`

`variable` `extern` | [progs/doomgeneric/r_state.h:41](../../progs/doomgeneric/r_state.h#L41)

```c
extern fixed_t* spritewidth;
```

needed for pre rendering (fracs)

---

<a id="spriteoffset"></a>

### `spriteoffset`

`variable` `extern` | [progs/doomgeneric/r_state.h:43](../../progs/doomgeneric/r_state.h#L43)

```c
extern fixed_t* spriteoffset;
```

---

<a id="spritetopoffset"></a>

### `spritetopoffset`

`variable` `extern` | [progs/doomgeneric/r_state.h:44](../../progs/doomgeneric/r_state.h#L44)

```c
extern fixed_t* spritetopoffset;
```

---

<a id="colormaps"></a>

### `colormaps`

`variable` `extern` | [progs/doomgeneric/r_state.h:46](../../progs/doomgeneric/r_state.h#L46)

```c
extern lighttable_t* colormaps;
```

---

<a id="viewwidth"></a>

### `viewwidth`

`variable` `extern` | [progs/doomgeneric/r_state.h:48](../../progs/doomgeneric/r_state.h#L48)

```c
extern int viewwidth;
```

---

<a id="scaledviewwidth"></a>

### `scaledviewwidth`

`variable` `extern` | [progs/doomgeneric/r_state.h:49](../../progs/doomgeneric/r_state.h#L49)

```c
extern int scaledviewwidth;
```

---

<a id="viewheight"></a>

### `viewheight`

`variable` `extern` | [progs/doomgeneric/r_state.h:50](../../progs/doomgeneric/r_state.h#L50)

```c
extern int viewheight;
```

---

<a id="firstflat"></a>

### `firstflat`

`variable` `extern` | [progs/doomgeneric/r_state.h:52](../../progs/doomgeneric/r_state.h#L52)

```c
extern int firstflat;
```

---

<a id="flattranslation"></a>

### `flattranslation`

`variable` `extern` | [progs/doomgeneric/r_state.h:55](../../progs/doomgeneric/r_state.h#L55)

```c
extern int* flattranslation;
```

for global animation

---

<a id="texturetranslation"></a>

### `texturetranslation`

`variable` `extern` | [progs/doomgeneric/r_state.h:56](../../progs/doomgeneric/r_state.h#L56)

```c
extern int* texturetranslation;
```

---

<a id="firstspritelump"></a>

### `firstspritelump`

`variable` `extern` | [progs/doomgeneric/r_state.h:60](../../progs/doomgeneric/r_state.h#L60)

```c
extern int firstspritelump;
```

Sprite....

---

<a id="lastspritelump"></a>

### `lastspritelump`

`variable` `extern` | [progs/doomgeneric/r_state.h:61](../../progs/doomgeneric/r_state.h#L61)

```c
extern int lastspritelump;
```

---

<a id="numspritelumps"></a>

### `numspritelumps`

`variable` `extern` | [progs/doomgeneric/r_state.h:62](../../progs/doomgeneric/r_state.h#L62)

```c
extern int numspritelumps;
```

---

<a id="numsprites"></a>

### `numsprites`

`variable` `extern` | [progs/doomgeneric/r_state.h:69](../../progs/doomgeneric/r_state.h#L69)

```c
extern int numsprites;
```

Lookup tables for map data.

---

<a id="sprites"></a>

### `sprites`

`variable` `extern` | [progs/doomgeneric/r_state.h:70](../../progs/doomgeneric/r_state.h#L70)

```c
extern spritedef_t* sprites;
```

---

<a id="numvertexes"></a>

### `numvertexes`

`variable` `extern` | [progs/doomgeneric/r_state.h:72](../../progs/doomgeneric/r_state.h#L72)

```c
extern int numvertexes;
```

---

<a id="vertexes"></a>

### `vertexes`

`variable` `extern` | [progs/doomgeneric/r_state.h:73](../../progs/doomgeneric/r_state.h#L73)

```c
extern vertex_t* vertexes;
```

---

<a id="numsegs"></a>

### `numsegs`

`variable` `extern` | [progs/doomgeneric/r_state.h:75](../../progs/doomgeneric/r_state.h#L75)

```c
extern int numsegs;
```

---

<a id="segs"></a>

### `segs`

`variable` `extern` | [progs/doomgeneric/r_state.h:76](../../progs/doomgeneric/r_state.h#L76)

```c
extern seg_t* segs;
```

---

<a id="numsectors"></a>

### `numsectors`

`variable` `extern` | [progs/doomgeneric/r_state.h:78](../../progs/doomgeneric/r_state.h#L78)

```c
extern int numsectors;
```

---

<a id="sectors"></a>

### `sectors`

`variable` `extern` | [progs/doomgeneric/r_state.h:79](../../progs/doomgeneric/r_state.h#L79)

```c
extern sector_t* sectors;
```

---

<a id="numsubsectors"></a>

### `numsubsectors`

`variable` `extern` | [progs/doomgeneric/r_state.h:81](../../progs/doomgeneric/r_state.h#L81)

```c
extern int numsubsectors;
```

---

<a id="subsectors"></a>

### `subsectors`

`variable` `extern` | [progs/doomgeneric/r_state.h:82](../../progs/doomgeneric/r_state.h#L82)

```c
extern subsector_t* subsectors;
```

---

<a id="numnodes"></a>

### `numnodes`

`variable` `extern` | [progs/doomgeneric/r_state.h:84](../../progs/doomgeneric/r_state.h#L84)

```c
extern int numnodes;
```

---

<a id="nodes"></a>

### `nodes`

`variable` `extern` | [progs/doomgeneric/r_state.h:85](../../progs/doomgeneric/r_state.h#L85)

```c
extern node_t* nodes;
```

---

<a id="numlines"></a>

### `numlines`

`variable` `extern` | [progs/doomgeneric/r_state.h:87](../../progs/doomgeneric/r_state.h#L87)

```c
extern int numlines;
```

---

<a id="lines"></a>

### `lines`

`variable` `extern` | [progs/doomgeneric/r_state.h:88](../../progs/doomgeneric/r_state.h#L88)

```c
extern line_t* lines;
```

---

<a id="numsides"></a>

### `numsides`

`variable` `extern` | [progs/doomgeneric/r_state.h:90](../../progs/doomgeneric/r_state.h#L90)

```c
extern int numsides;
```

---

<a id="sides"></a>

### `sides`

`variable` `extern` | [progs/doomgeneric/r_state.h:91](../../progs/doomgeneric/r_state.h#L91)

```c
extern side_t* sides;
```

---

<a id="viewx"></a>

### `viewx`

`variable` `extern` | [progs/doomgeneric/r_state.h:97](../../progs/doomgeneric/r_state.h#L97)

```c
extern fixed_t viewx;
```

POV data.

---

<a id="viewy"></a>

### `viewy`

`variable` `extern` | [progs/doomgeneric/r_state.h:98](../../progs/doomgeneric/r_state.h#L98)

```c
extern fixed_t viewy;
```

---

<a id="viewz"></a>

### `viewz`

`variable` `extern` | [progs/doomgeneric/r_state.h:99](../../progs/doomgeneric/r_state.h#L99)

```c
extern fixed_t viewz;
```

---

<a id="viewangle"></a>

### `viewangle`

`variable` `extern` | [progs/doomgeneric/r_state.h:101](../../progs/doomgeneric/r_state.h#L101)

```c
extern angle_t viewangle;
```

---

<a id="viewplayer"></a>

### `viewplayer`

`variable` `extern` | [progs/doomgeneric/r_state.h:102](../../progs/doomgeneric/r_state.h#L102)

```c
extern player_t* viewplayer;
```

---

<a id="clipangle"></a>

### `clipangle`

`variable` `extern` | [progs/doomgeneric/r_state.h:106](../../progs/doomgeneric/r_state.h#L106)

```c
extern angle_t clipangle;
```

?

---

<a id="viewangletox"></a>

### `viewangletox`

`variable` `extern` | [progs/doomgeneric/r_state.h:108](../../progs/doomgeneric/r_state.h#L108)

```c
extern int viewangletox[FINEANGLES/2];
```

---

<a id="xtoviewangle"></a>

### `xtoviewangle`

`variable` `extern` | [progs/doomgeneric/r_state.h:109](../../progs/doomgeneric/r_state.h#L109)

```c
extern angle_t xtoviewangle[SCREENWIDTH+1];
```

---

<a id="rw_distance"></a>

### `rw_distance`

`variable` `extern` | [progs/doomgeneric/r_state.h:112](../../progs/doomgeneric/r_state.h#L112)

```c
extern fixed_t rw_distance;
```

---

<a id="rw_normalangle"></a>

### `rw_normalangle`

`variable` `extern` | [progs/doomgeneric/r_state.h:113](../../progs/doomgeneric/r_state.h#L113)

```c
extern angle_t rw_normalangle;
```

---

<a id="rw_angle1"></a>

### `rw_angle1`

`variable` `extern` | [progs/doomgeneric/r_state.h:118](../../progs/doomgeneric/r_state.h#L118)

```c
extern int rw_angle1;
```

angle to line origin

---

<a id="sscount"></a>

### `sscount`

`variable` `extern` | [progs/doomgeneric/r_state.h:121](../../progs/doomgeneric/r_state.h#L121)

```c
extern int sscount;
```

Segs count?

---

<a id="floorplane"></a>

### `floorplane`

`variable` `extern` | [progs/doomgeneric/r_state.h:123](../../progs/doomgeneric/r_state.h#L123)

```c
extern visplane_t* floorplane;
```

---

<a id="ceilingplane"></a>

### `ceilingplane`

`variable` `extern` | [progs/doomgeneric/r_state.h:124](../../progs/doomgeneric/r_state.h#L124)

```c
extern visplane_t* ceilingplane;
```

---
