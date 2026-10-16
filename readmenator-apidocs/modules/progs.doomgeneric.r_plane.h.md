# `progs/doomgeneric/r_plane.h`

> Source: [progs/doomgeneric/r_plane.h:1](../../progs/doomgeneric/r_plane.h#L1) | language `h` | coverage 11.1% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Refresh, visplane stuff (floor, ceilings).         Visplane related.

## Contents

- **Functions:** [`R_InitPlanes`](#r_initplanes), [`R_ClearPlanes`](#r_clearplanes), [`R_MapPlane`](#r_mapplane), [`R_MakeSpans`](#r_makespans), [`R_DrawPlanes`](#r_drawplanes), [`R_FindPlane`](#r_findplane), [`R_CheckPlane`](#r_checkplane)
- **Macros:** [`__R_PLANE__`](#__r_plane__)
- **Variables:** [`lastopening`](#lastopening), [`floorfunc`](#floorfunc), [`ceilingfunc_t`](#ceilingfunc_t), [`floorclip`](#floorclip), [`ceilingclip`](#ceilingclip), [`yslope`](#yslope), [`distscale`](#distscale)

## Functions

<a id="r_initplanes"></a>

### `R_InitPlanes`

`function` | [progs/doomgeneric/r_plane.h:43](../../progs/doomgeneric/r_plane.h#L43)

```c
void R_InitPlanes (void);
```

---

<a id="r_clearplanes"></a>

### `R_ClearPlanes`

`function` | [progs/doomgeneric/r_plane.h:44](../../progs/doomgeneric/r_plane.h#L44)

```c
void R_ClearPlanes (void);
```

---

<a id="r_mapplane"></a>

### `R_MapPlane`

`function` | [progs/doomgeneric/r_plane.h:47](../../progs/doomgeneric/r_plane.h#L47)

```c
void R_MapPlane ( int y, int x1, int x2 );
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `y` | `int` |  |  |
| `x1` | `int` |  |  |
| `x2` | `int` |  |  |

---

<a id="r_makespans"></a>

### `R_MakeSpans`

`function` | [progs/doomgeneric/r_plane.h:53](../../progs/doomgeneric/r_plane.h#L53)

```c
void R_MakeSpans ( int x, int t1, int b1, int t2, int b2 );
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `t1` | `int` |  |  |
| `b1` | `int` |  |  |
| `t2` | `int` |  |  |
| `b2` | `int` |  |  |

---

<a id="r_drawplanes"></a>

### `R_DrawPlanes`

`function` | [progs/doomgeneric/r_plane.h:60](../../progs/doomgeneric/r_plane.h#L60)

```c
void R_DrawPlanes (void);
```

---

<a id="r_findplane"></a>

### `R_FindPlane`

`function` | [progs/doomgeneric/r_plane.h:63](../../progs/doomgeneric/r_plane.h#L63)

```c
visplane_t* R_FindPlane ( fixed_t height, int picnum, int lightlevel );
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `height` | `fixed_t` |  |  |
| `picnum` | `int` |  |  |
| `lightlevel` | `int` |  |  |

**Returns:** `visplane_t*`

*Called by:* [`R_Subsector`](progs.doomgeneric.r_bsp.c.md#r_subsector)

---

<a id="r_checkplane"></a>

### `R_CheckPlane`

`function` | [progs/doomgeneric/r_plane.h:69](../../progs/doomgeneric/r_plane.h#L69)

```c
visplane_t* R_CheckPlane ( visplane_t* pl, int start, int stop );
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `pl` | `visplane_t*` |  |  |
| `start` | `int` |  |  |
| `stop` | `int` |  |  |

**Returns:** `visplane_t*`

---

## Macros

<a id="__r_plane__"></a>

### `__R_PLANE__`

`macro` | [progs/doomgeneric/r_plane.h:21](../../progs/doomgeneric/r_plane.h#L21)

```c
#define __R_PLANE__
```

---

## Variables

<a id="lastopening"></a>

### `lastopening`

`variable` `extern` | [progs/doomgeneric/r_plane.h:29](../../progs/doomgeneric/r_plane.h#L29)

```c
extern short* lastopening;
```

Visplane related.

---

<a id="floorfunc"></a>

### `floorfunc`

`variable` `extern` | [progs/doomgeneric/r_plane.h:34](../../progs/doomgeneric/r_plane.h#L34)

```c
extern planefunction_t floorfunc;
```

---

<a id="ceilingfunc_t"></a>

### `ceilingfunc_t`

`variable` `extern` | [progs/doomgeneric/r_plane.h:35](../../progs/doomgeneric/r_plane.h#L35)

```c
extern planefunction_t ceilingfunc_t;
```

---

<a id="floorclip"></a>

### `floorclip`

`variable` `extern` | [progs/doomgeneric/r_plane.h:37](../../progs/doomgeneric/r_plane.h#L37)

```c
extern short floorclip[SCREENWIDTH];
```

---

<a id="ceilingclip"></a>

### `ceilingclip`

`variable` `extern` | [progs/doomgeneric/r_plane.h:38](../../progs/doomgeneric/r_plane.h#L38)

```c
extern short ceilingclip[SCREENWIDTH];
```

---

<a id="yslope"></a>

### `yslope`

`variable` `extern` | [progs/doomgeneric/r_plane.h:40](../../progs/doomgeneric/r_plane.h#L40)

```c
extern fixed_t yslope[SCREENHEIGHT];
```

---

<a id="distscale"></a>

### `distscale`

`variable` `extern` | [progs/doomgeneric/r_plane.h:41](../../progs/doomgeneric/r_plane.h#L41)

```c
extern fixed_t distscale[SCREENWIDTH];
```

---
