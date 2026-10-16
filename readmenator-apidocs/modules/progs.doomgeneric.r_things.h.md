# `progs/doomgeneric/r_things.h`

> Source: [progs/doomgeneric/r_things.h:1](../../progs/doomgeneric/r_things.h#L1) | language `h` | coverage 8.3% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Rendering of moving objects, sprites.

## Contents

- **Functions:** [`R_DrawMaskedColumn`](#r_drawmaskedcolumn), [`R_SortVisSprites`](#r_sortvissprites), [`R_AddSprites`](#r_addsprites), [`R_AddPSprites`](#r_addpsprites), [`R_DrawSprites`](#r_drawsprites), [`R_InitSprites`](#r_initsprites), [`R_ClearSprites`](#r_clearsprites), [`R_DrawMasked`](#r_drawmasked), [`R_ClipVisSprite`](#r_clipvissprite)
- **Macros:** [`__R_THINGS__`](#__r_things__), [`MAXVISSPRITES`](#maxvissprites)
- **Variables:** [`vissprites`](#vissprites), [`vissprite_p`](#vissprite_p), [`vsprsortedhead`](#vsprsortedhead), [`negonearray`](#negonearray), [`screenheightarray`](#screenheightarray), [`mfloorclip`](#mfloorclip), [`mceilingclip`](#mceilingclip), [`spryscale`](#spryscale), [`sprtopscreen`](#sprtopscreen), [`pspritescale`](#pspritescale), [`pspriteiscale`](#pspriteiscale)

## Functions

<a id="r_drawmaskedcolumn"></a>

### `R_DrawMaskedColumn`

`function` | [progs/doomgeneric/r_things.h:46](../../progs/doomgeneric/r_things.h#L46)

```c
void R_DrawMaskedColumn (column_t* column);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `column` | `column_t*` |  |  |

---

<a id="r_sortvissprites"></a>

### `R_SortVisSprites`

`function` | [progs/doomgeneric/r_things.h:49](../../progs/doomgeneric/r_things.h#L49)

```c
void R_SortVisSprites (void);
```

---

<a id="r_addsprites"></a>

### `R_AddSprites`

`function` | [progs/doomgeneric/r_things.h:51](../../progs/doomgeneric/r_things.h#L51)

```c
void R_AddSprites (sector_t* sec);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `sec` | `sector_t*` |  |  |

*Called by:* [`R_Subsector`](progs.doomgeneric.r_bsp.c.md#r_subsector)

---

<a id="r_addpsprites"></a>

### `R_AddPSprites`

`function` | [progs/doomgeneric/r_things.h:52](../../progs/doomgeneric/r_things.h#L52)

```c
void R_AddPSprites (void);
```

---

<a id="r_drawsprites"></a>

### `R_DrawSprites`

`function` | [progs/doomgeneric/r_things.h:53](../../progs/doomgeneric/r_things.h#L53)

```c
void R_DrawSprites (void);
```

---

<a id="r_initsprites"></a>

### `R_InitSprites`

`function` | [progs/doomgeneric/r_things.h:54](../../progs/doomgeneric/r_things.h#L54)

```c
void R_InitSprites (char** namelist);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `namelist` | `char**` |  |  |

---

<a id="r_clearsprites"></a>

### `R_ClearSprites`

`function` | [progs/doomgeneric/r_things.h:55](../../progs/doomgeneric/r_things.h#L55)

```c
void R_ClearSprites (void);
```

---

<a id="r_drawmasked"></a>

### `R_DrawMasked`

`function` | [progs/doomgeneric/r_things.h:56](../../progs/doomgeneric/r_things.h#L56)

```c
void R_DrawMasked (void);
```

---

<a id="r_clipvissprite"></a>

### `R_ClipVisSprite`

`function` | [progs/doomgeneric/r_things.h:59](../../progs/doomgeneric/r_things.h#L59)

```c
void R_ClipVisSprite ( vissprite_t* vis, int xl, int xh );
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `vis` | `vissprite_t*` |  |  |
| `xl` | `int` |  |  |
| `xh` | `int` |  |  |

---

## Macros

<a id="__r_things__"></a>

### `__R_THINGS__`

`macro` | [progs/doomgeneric/r_things.h:21](../../progs/doomgeneric/r_things.h#L21)

```c
#define __R_THINGS__
```

---

<a id="maxvissprites"></a>

### `MAXVISSPRITES`

`macro` | [progs/doomgeneric/r_things.h:25](../../progs/doomgeneric/r_things.h#L25)

```c
#define MAXVISSPRITES
```

---

## Variables

<a id="vissprites"></a>

### `vissprites`

`variable` `extern` | [progs/doomgeneric/r_things.h:27](../../progs/doomgeneric/r_things.h#L27)

```c
extern vissprite_t vissprites[MAXVISSPRITES];
```

---

<a id="vissprite_p"></a>

### `vissprite_p`

`variable` `extern` | [progs/doomgeneric/r_things.h:28](../../progs/doomgeneric/r_things.h#L28)

```c
extern vissprite_t* vissprite_p;
```

---

<a id="vsprsortedhead"></a>

### `vsprsortedhead`

`variable` `extern` | [progs/doomgeneric/r_things.h:29](../../progs/doomgeneric/r_things.h#L29)

```c
extern vissprite_t vsprsortedhead;
```

---

<a id="negonearray"></a>

### `negonearray`

`variable` `extern` | [progs/doomgeneric/r_things.h:33](../../progs/doomgeneric/r_things.h#L33)

```c
extern short negonearray[SCREENWIDTH];
```

Constant arrays used for psprite clipping and initializing clipping.

---

<a id="screenheightarray"></a>

### `screenheightarray`

`variable` `extern` | [progs/doomgeneric/r_things.h:34](../../progs/doomgeneric/r_things.h#L34)

```c
extern short screenheightarray[SCREENWIDTH];
```

---

<a id="mfloorclip"></a>

### `mfloorclip`

`variable` `extern` | [progs/doomgeneric/r_things.h:37](../../progs/doomgeneric/r_things.h#L37)

```c
extern short* mfloorclip;
```

vars for R_DrawMaskedColumn

---

<a id="mceilingclip"></a>

### `mceilingclip`

`variable` `extern` | [progs/doomgeneric/r_things.h:38](../../progs/doomgeneric/r_things.h#L38)

```c
extern short* mceilingclip;
```

---

<a id="spryscale"></a>

### `spryscale`

`variable` `extern` | [progs/doomgeneric/r_things.h:39](../../progs/doomgeneric/r_things.h#L39)

```c
extern fixed_t spryscale;
```

---

<a id="sprtopscreen"></a>

### `sprtopscreen`

`variable` `extern` | [progs/doomgeneric/r_things.h:40](../../progs/doomgeneric/r_things.h#L40)

```c
extern fixed_t sprtopscreen;
```

---

<a id="pspritescale"></a>

### `pspritescale`

`variable` `extern` | [progs/doomgeneric/r_things.h:42](../../progs/doomgeneric/r_things.h#L42)

```c
extern fixed_t pspritescale;
```

---

<a id="pspriteiscale"></a>

### `pspriteiscale`

`variable` `extern` | [progs/doomgeneric/r_things.h:43](../../progs/doomgeneric/r_things.h#L43)

```c
extern fixed_t pspriteiscale;
```

---
