# `progs/doomgeneric/i_swap.h`

> Source: [progs/doomgeneric/i_swap.h:1](../../progs/doomgeneric/i_swap.h#L1) | language `h` | coverage 11.1% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Endianess handling, swapping 16bit and 32bit.      Endianess handling. WAD files are stored little endian.  Just use SDL's endianness swapping functions.

## Contents

- **Macros:** [`__I_SWAP__`](#__i_swap__), [`SHORT`](#short), [`LONG`](#long), [`SYS_LITTLE_ENDIAN`](#sys_little_endian), [`SYS_BIG_ENDIAN`](#sys_big_endian), [`SHORT`](#short), [`LONG`](#long), [`SYS_LITTLE_ENDIAN`](#sys_little_endian)

## Macros

<a id="__i_swap__"></a>

### `__I_SWAP__`

`macro` | [progs/doomgeneric/i_swap.h:21](../../progs/doomgeneric/i_swap.h#L21)

```c
#define __I_SWAP__
```

---

<a id="short"></a>

### `SHORT`

`macro` | [progs/doomgeneric/i_swap.h:34](../../progs/doomgeneric/i_swap.h#L34)

```c
#define SHORT(x)
```

*Called by:* [`F_CastPrint`](progs.doomgeneric.f_finale.c.md#f_castprint), [`F_TextWrite`](progs.doomgeneric.f_finale.c.md#f_textwrite), [`HUlib_drawTextLine`](progs.doomgeneric.hu_lib.c.md#hulib_drawtextline), [`HUlib_eraseTextLine`](progs.doomgeneric.hu_lib.c.md#hulib_erasetextline), [`HUlib_initSText`](progs.doomgeneric.hu_lib.c.md#hulib_initstext), [`M_Drawer`](progs.doomgeneric.m_menu.c.md#m_drawer), [`M_StringHeight`](progs.doomgeneric.m_menu.c.md#m_stringheight), [`M_StringWidth`](progs.doomgeneric.m_menu.c.md#m_stringwidth), [`M_WriteText`](progs.doomgeneric.m_menu.c.md#m_writetext), [`P_LoadBlockMap`](progs.doomgeneric.p_setup.c.md#p_loadblockmap), [`P_LoadLineDefs`](progs.doomgeneric.p_setup.c.md#p_loadlinedefs), [`P_LoadNodes`](progs.doomgeneric.p_setup.c.md#p_loadnodes) and 29 more

---

<a id="long"></a>

### `LONG`

`macro` | [progs/doomgeneric/i_swap.h:35](../../progs/doomgeneric/i_swap.h#L35)

```c
#define LONG(x)
```

*Called by:* [`F_DrawPatchCol`](progs.doomgeneric.f_finale.c.md#f_drawpatchcol), [`R_GenerateComposite`](progs.doomgeneric.r_data.c.md#r_generatecomposite), [`R_GenerateLookup`](progs.doomgeneric.r_data.c.md#r_generatelookup), [`R_InitTextures`](progs.doomgeneric.r_data.c.md#r_inittextures), [`R_DrawVisSprite`](progs.doomgeneric.r_things.c.md#r_drawvissprite), [`V_DrawAltTLPatch`](progs.doomgeneric.v_video.c.md#v_drawalttlpatch), [`V_DrawPatch`](progs.doomgeneric.v_video.c.md#v_drawpatch), [`V_DrawPatchFlipped`](progs.doomgeneric.v_video.c.md#v_drawpatchflipped), [`V_DrawShadowedPatch`](progs.doomgeneric.v_video.c.md#v_drawshadowedpatch), [`V_DrawTLPatch`](progs.doomgeneric.v_video.c.md#v_drawtlpatch), [`V_DrawXlaPatch`](progs.doomgeneric.v_video.c.md#v_drawxlapatch), [`W_AddFile`](progs.doomgeneric.w_wad.c.md#w_addfile)

---

<a id="sys_little_endian"></a>

### `SYS_LITTLE_ENDIAN`

`macro` | [progs/doomgeneric/i_swap.h:40](../../progs/doomgeneric/i_swap.h#L40)

```c
#define SYS_LITTLE_ENDIAN
```

---

<a id="sys_big_endian"></a>

### `SYS_BIG_ENDIAN`

`macro` | [progs/doomgeneric/i_swap.h:42](../../progs/doomgeneric/i_swap.h#L42)

```c
#define SYS_BIG_ENDIAN
```

---

<a id="short"></a>

### `SHORT`

`macro` | [progs/doomgeneric/i_swap.h:47](../../progs/doomgeneric/i_swap.h#L47)

```c
#define SHORT(x)
```

---

<a id="long"></a>

### `LONG`

`macro` | [progs/doomgeneric/i_swap.h:48](../../progs/doomgeneric/i_swap.h#L48)

```c
#define LONG(x)
```

---

<a id="sys_little_endian"></a>

### `SYS_LITTLE_ENDIAN`

`macro` | [progs/doomgeneric/i_swap.h:50](../../progs/doomgeneric/i_swap.h#L50)

```c
#define SYS_LITTLE_ENDIAN
```

---
