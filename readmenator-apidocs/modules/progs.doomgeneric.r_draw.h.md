# `progs/doomgeneric/r_draw.h`

> Source: [progs/doomgeneric/r_draw.h:1](../../progs/doomgeneric/r_draw.h#L1) | language `h` | coverage 60.0% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: System specific interface stuff.

## Contents

- **Functions:** [`R_DrawColumn`](#r_drawcolumn), [`R_DrawColumnLow`](#r_drawcolumnlow), [`R_DrawFuzzColumn`](#r_drawfuzzcolumn), [`R_DrawFuzzColumnLow`](#r_drawfuzzcolumnlow), [`R_DrawTranslatedColumn`](#r_drawtranslatedcolumn), [`R_DrawTranslatedColumnLow`](#r_drawtranslatedcolumnlow), [`R_VideoErase`](#r_videoerase), [`R_DrawSpan`](#r_drawspan), [`R_DrawSpanLow`](#r_drawspanlow), [`R_InitBuffer`](#r_initbuffer), [`R_InitTranslationTables`](#r_inittranslationtables), [`R_FillBackScreen`](#r_fillbackscreen), [`R_DrawViewBorder`](#r_drawviewborder)
- **Macros:** [`__R_DRAW__`](#__r_draw__)
- **Variables:** [`dc_colormap`](#dc_colormap), [`dc_x`](#dc_x), [`dc_yl`](#dc_yl), [`dc_yh`](#dc_yh), [`dc_iscale`](#dc_iscale), [`dc_texturemid`](#dc_texturemid), [`dc_source`](#dc_source), [`ds_y`](#ds_y), [`ds_x1`](#ds_x1), [`ds_x2`](#ds_x2), [`ds_colormap`](#ds_colormap), [`ds_xfrac`](#ds_xfrac), [`ds_yfrac`](#ds_yfrac), [`ds_xstep`](#ds_xstep), [`ds_ystep`](#ds_ystep), [`ds_source`](#ds_source), [`translationtables`](#translationtables), [`dc_translation`](#dc_translation)

## Functions

<a id="r_drawcolumn"></a>

### `R_DrawColumn`

`function` | [progs/doomgeneric/r_draw.h:40](../../progs/doomgeneric/r_draw.h#L40)

```c
void R_DrawColumn (void);
```

The span blitting interface.

Hook in assembler or system specific BLT here.

---

<a id="r_drawcolumnlow"></a>

### `R_DrawColumnLow`

`function` | [progs/doomgeneric/r_draw.h:41](../../progs/doomgeneric/r_draw.h#L41)

```c
void R_DrawColumnLow (void);
```

---

<a id="r_drawfuzzcolumn"></a>

### `R_DrawFuzzColumn`

`function` | [progs/doomgeneric/r_draw.h:44](../../progs/doomgeneric/r_draw.h#L44)

```c
void R_DrawFuzzColumn (void);
```

The Spectre/Invisibility effect.

---

<a id="r_drawfuzzcolumnlow"></a>

### `R_DrawFuzzColumnLow`

`function` | [progs/doomgeneric/r_draw.h:45](../../progs/doomgeneric/r_draw.h#L45)

```c
void R_DrawFuzzColumnLow (void);
```

---

<a id="r_drawtranslatedcolumn"></a>

### `R_DrawTranslatedColumn`

`function` | [progs/doomgeneric/r_draw.h:50](../../progs/doomgeneric/r_draw.h#L50)

```c
void R_DrawTranslatedColumn (void);
```

Draw with color translation tables, for player sprite rendering, Green/Red/Blue/Indigo shirts.

---

<a id="r_drawtranslatedcolumnlow"></a>

### `R_DrawTranslatedColumnLow`

`function` | [progs/doomgeneric/r_draw.h:51](../../progs/doomgeneric/r_draw.h#L51)

```c
void R_DrawTranslatedColumnLow (void);
```

---

<a id="r_videoerase"></a>

### `R_VideoErase`

`function` | [progs/doomgeneric/r_draw.h:54](../../progs/doomgeneric/r_draw.h#L54)

```c
void R_VideoErase ( unsigned ofs, int count );
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ofs` | `unsigned` |  |  |
| `count` | `int` |  |  |

*Called by:* [`HUlib_eraseTextLine`](progs.doomgeneric.hu_lib.c.md#hulib_erasetextline)

---

<a id="r_drawspan"></a>

### `R_DrawSpan`

`function` | [progs/doomgeneric/r_draw.h:78](../../progs/doomgeneric/r_draw.h#L78)

```c
void R_DrawSpan (void);
```

Span blitting for rows, floor/ceiling.

No Sepctre effect needed.

---

<a id="r_drawspanlow"></a>

### `R_DrawSpanLow`

`function` | [progs/doomgeneric/r_draw.h:81](../../progs/doomgeneric/r_draw.h#L81)

```c
void R_DrawSpanLow (void);
```

Low resolution mode, 160x200?

---

<a id="r_initbuffer"></a>

### `R_InitBuffer`

`function` | [progs/doomgeneric/r_draw.h:85](../../progs/doomgeneric/r_draw.h#L85)

```c
void R_InitBuffer ( int width, int height );
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `width` | `int` |  |  |
| `height` | `int` |  |  |

---

<a id="r_inittranslationtables"></a>

### `R_InitTranslationTables`

`function` | [progs/doomgeneric/r_draw.h:92](../../progs/doomgeneric/r_draw.h#L92)

```c
void R_InitTranslationTables (void);
```

Initialize color translation tables, for player rendering etc.

---

<a id="r_fillbackscreen"></a>

### `R_FillBackScreen`

`function` | [progs/doomgeneric/r_draw.h:97](../../progs/doomgeneric/r_draw.h#L97)

```c
void R_FillBackScreen (void);
```

Rendering function.

---

<a id="r_drawviewborder"></a>

### `R_DrawViewBorder`

`function` | [progs/doomgeneric/r_draw.h:100](../../progs/doomgeneric/r_draw.h#L100)

```c
void R_DrawViewBorder (void);
```

If the view size is not full screen, draws a border around it.

---

## Macros

<a id="__r_draw__"></a>

### `__R_DRAW__`

`macro` | [progs/doomgeneric/r_draw.h:21](../../progs/doomgeneric/r_draw.h#L21)

```c
#define __R_DRAW__
```

---

## Variables

<a id="dc_colormap"></a>

### `dc_colormap`

`variable` `extern` | [progs/doomgeneric/r_draw.h:26](../../progs/doomgeneric/r_draw.h#L26)

```c
extern lighttable_t* dc_colormap;
```

---

<a id="dc_x"></a>

### `dc_x`

`variable` `extern` | [progs/doomgeneric/r_draw.h:27](../../progs/doomgeneric/r_draw.h#L27)

```c
extern int dc_x;
```

---

<a id="dc_yl"></a>

### `dc_yl`

`variable` `extern` | [progs/doomgeneric/r_draw.h:28](../../progs/doomgeneric/r_draw.h#L28)

```c
extern int dc_yl;
```

---

<a id="dc_yh"></a>

### `dc_yh`

`variable` `extern` | [progs/doomgeneric/r_draw.h:29](../../progs/doomgeneric/r_draw.h#L29)

```c
extern int dc_yh;
```

---

<a id="dc_iscale"></a>

### `dc_iscale`

`variable` `extern` | [progs/doomgeneric/r_draw.h:30](../../progs/doomgeneric/r_draw.h#L30)

```c
extern fixed_t dc_iscale;
```

---

<a id="dc_texturemid"></a>

### `dc_texturemid`

`variable` `extern` | [progs/doomgeneric/r_draw.h:31](../../progs/doomgeneric/r_draw.h#L31)

```c
extern fixed_t dc_texturemid;
```

---

<a id="dc_source"></a>

### `dc_source`

`variable` `extern` | [progs/doomgeneric/r_draw.h:34](../../progs/doomgeneric/r_draw.h#L34)

```c
extern byte* dc_source;
```

first pixel in a column

---

<a id="ds_y"></a>

### `ds_y`

`variable` `extern` | [progs/doomgeneric/r_draw.h:58](../../progs/doomgeneric/r_draw.h#L58)

```c
extern int ds_y;
```

---

<a id="ds_x1"></a>

### `ds_x1`

`variable` `extern` | [progs/doomgeneric/r_draw.h:59](../../progs/doomgeneric/r_draw.h#L59)

```c
extern int ds_x1;
```

---

<a id="ds_x2"></a>

### `ds_x2`

`variable` `extern` | [progs/doomgeneric/r_draw.h:60](../../progs/doomgeneric/r_draw.h#L60)

```c
extern int ds_x2;
```

---

<a id="ds_colormap"></a>

### `ds_colormap`

`variable` `extern` | [progs/doomgeneric/r_draw.h:62](../../progs/doomgeneric/r_draw.h#L62)

```c
extern lighttable_t* ds_colormap;
```

---

<a id="ds_xfrac"></a>

### `ds_xfrac`

`variable` `extern` | [progs/doomgeneric/r_draw.h:64](../../progs/doomgeneric/r_draw.h#L64)

```c
extern fixed_t ds_xfrac;
```

---

<a id="ds_yfrac"></a>

### `ds_yfrac`

`variable` `extern` | [progs/doomgeneric/r_draw.h:65](../../progs/doomgeneric/r_draw.h#L65)

```c
extern fixed_t ds_yfrac;
```

---

<a id="ds_xstep"></a>

### `ds_xstep`

`variable` `extern` | [progs/doomgeneric/r_draw.h:66](../../progs/doomgeneric/r_draw.h#L66)

```c
extern fixed_t ds_xstep;
```

---

<a id="ds_ystep"></a>

### `ds_ystep`

`variable` `extern` | [progs/doomgeneric/r_draw.h:67](../../progs/doomgeneric/r_draw.h#L67)

```c
extern fixed_t ds_ystep;
```

---

<a id="ds_source"></a>

### `ds_source`

`variable` `extern` | [progs/doomgeneric/r_draw.h:70](../../progs/doomgeneric/r_draw.h#L70)

```c
extern byte* ds_source;
```

start of a 64*64 tile image

---

<a id="translationtables"></a>

### `translationtables`

`variable` `extern` | [progs/doomgeneric/r_draw.h:72](../../progs/doomgeneric/r_draw.h#L72)

```c
extern byte* translationtables;
```

---

<a id="dc_translation"></a>

### `dc_translation`

`variable` `extern` | [progs/doomgeneric/r_draw.h:73](../../progs/doomgeneric/r_draw.h#L73)

```c
extern byte* dc_translation;
```

---
