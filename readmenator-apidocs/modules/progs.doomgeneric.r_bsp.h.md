# `progs/doomgeneric/r_bsp.h`

> Source: [progs/doomgeneric/r_bsp.h:1](../../progs/doomgeneric/r_bsp.h#L1) | language `h` | coverage 40.0% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Refresh module, BSP traversal and handling.

## Contents

- **Functions:** [`R_ClearClipSegs`](#r_clearclipsegs), [`R_ClearDrawSegs`](#r_cleardrawsegs), [`R_RenderBSPNode`](#r_renderbspnode)
- **Macros:** [`__R_BSP__`](#__r_bsp__)
- **Variables:** [`curline`](#curline), [`sidedef`](#sidedef), [`linedef`](#linedef), [`frontsector`](#frontsector), [`backsector`](#backsector), [`rw_x`](#rw_x), [`rw_stopx`](#rw_stopx), [`segtextured`](#segtextured), [`markfloor`](#markfloor), [`markceiling`](#markceiling), [`skymap`](#skymap), [`drawsegs`](#drawsegs), [`ds_p`](#ds_p), [`hscalelight`](#hscalelight), [`vscalelight`](#vscalelight), [`dscalelight`](#dscalelight)

## Functions

<a id="r_clearclipsegs"></a>

### `R_ClearClipSegs`

`function` | [progs/doomgeneric/r_bsp.h:54](../../progs/doomgeneric/r_bsp.h#L54)

```c
void R_ClearClipSegs (void);
```

BSP?

---

<a id="r_cleardrawsegs"></a>

### `R_ClearDrawSegs`

`function` | [progs/doomgeneric/r_bsp.h:55](../../progs/doomgeneric/r_bsp.h#L55)

```c
void R_ClearDrawSegs (void);
```

---

<a id="r_renderbspnode"></a>

### `R_RenderBSPNode`

`function` | [progs/doomgeneric/r_bsp.h:58](../../progs/doomgeneric/r_bsp.h#L58)

```c
void R_RenderBSPNode (int bspnum);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bspnum` | `int` |  |  |

---

## Macros

<a id="__r_bsp__"></a>

### `__R_BSP__`

`macro` | [progs/doomgeneric/r_bsp.h:21](../../progs/doomgeneric/r_bsp.h#L21)

```c
#define __R_BSP__
```

---

## Variables

<a id="curline"></a>

### `curline`

`variable` `extern` | [progs/doomgeneric/r_bsp.h:25](../../progs/doomgeneric/r_bsp.h#L25)

```c
extern seg_t* curline;
```

---

<a id="sidedef"></a>

### `sidedef`

`variable` `extern` | [progs/doomgeneric/r_bsp.h:26](../../progs/doomgeneric/r_bsp.h#L26)

```c
extern side_t* sidedef;
```

---

<a id="linedef"></a>

### `linedef`

`variable` `extern` | [progs/doomgeneric/r_bsp.h:27](../../progs/doomgeneric/r_bsp.h#L27)

```c
extern line_t* linedef;
```

---

<a id="frontsector"></a>

### `frontsector`

`variable` `extern` | [progs/doomgeneric/r_bsp.h:28](../../progs/doomgeneric/r_bsp.h#L28)

```c
extern sector_t* frontsector;
```

---

<a id="backsector"></a>

### `backsector`

`variable` `extern` | [progs/doomgeneric/r_bsp.h:29](../../progs/doomgeneric/r_bsp.h#L29)

```c
extern sector_t* backsector;
```

---

<a id="rw_x"></a>

### `rw_x`

`variable` `extern` | [progs/doomgeneric/r_bsp.h:31](../../progs/doomgeneric/r_bsp.h#L31)

```c
extern int rw_x;
```

---

<a id="rw_stopx"></a>

### `rw_stopx`

`variable` `extern` | [progs/doomgeneric/r_bsp.h:32](../../progs/doomgeneric/r_bsp.h#L32)

```c
extern int rw_stopx;
```

---

<a id="segtextured"></a>

### `segtextured`

`variable` `extern` | [progs/doomgeneric/r_bsp.h:34](../../progs/doomgeneric/r_bsp.h#L34)

```c
extern boolean segtextured;
```

---

<a id="markfloor"></a>

### `markfloor`

`variable` `extern` | [progs/doomgeneric/r_bsp.h:37](../../progs/doomgeneric/r_bsp.h#L37)

```c
extern boolean markfloor;
```

false if the back side is the same plane

---

<a id="markceiling"></a>

### `markceiling`

`variable` `extern` | [progs/doomgeneric/r_bsp.h:38](../../progs/doomgeneric/r_bsp.h#L38)

```c
extern boolean markceiling;
```

---

<a id="skymap"></a>

### `skymap`

`variable` `extern` | [progs/doomgeneric/r_bsp.h:40](../../progs/doomgeneric/r_bsp.h#L40)

```c
extern boolean skymap;
```

---

<a id="drawsegs"></a>

### `drawsegs`

`variable` `extern` | [progs/doomgeneric/r_bsp.h:42](../../progs/doomgeneric/r_bsp.h#L42)

```c
extern drawseg_t drawsegs[MAXDRAWSEGS];
```

---

<a id="ds_p"></a>

### `ds_p`

`variable` `extern` | [progs/doomgeneric/r_bsp.h:43](../../progs/doomgeneric/r_bsp.h#L43)

```c
extern drawseg_t* ds_p;
```

---

<a id="hscalelight"></a>

### `hscalelight`

`variable` `extern` | [progs/doomgeneric/r_bsp.h:45](../../progs/doomgeneric/r_bsp.h#L45)

```c
extern lighttable_t** hscalelight;
```

---

<a id="vscalelight"></a>

### `vscalelight`

`variable` `extern` | [progs/doomgeneric/r_bsp.h:46](../../progs/doomgeneric/r_bsp.h#L46)

```c
extern lighttable_t** vscalelight;
```

---

<a id="dscalelight"></a>

### `dscalelight`

`variable` `extern` | [progs/doomgeneric/r_bsp.h:47](../../progs/doomgeneric/r_bsp.h#L47)

```c
extern lighttable_t** dscalelight;
```

---
