# `progs/doomgeneric/r_data.h`

> Source: [progs/doomgeneric/r_data.h:1](../../progs/doomgeneric/r_data.h#L1) | language `h` | coverage 50.0% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Refresh module, data I/O, caching, retrieval of graphics by name.       Retrieve column data for span blitting.

## Contents

- **Functions:** [`R_GetColumn`](#r_getcolumn), [`R_InitData`](#r_initdata), [`R_PrecacheLevel`](#r_precachelevel), [`R_FlatNumForName`](#r_flatnumforname), [`R_TextureNumForName`](#r_texturenumforname), [`R_CheckTextureNumForName`](#r_checktexturenumforname)
- **Macros:** [`__R_DATA__`](#__r_data__)

## Functions

<a id="r_getcolumn"></a>

### `R_GetColumn`

`function` | [progs/doomgeneric/r_data.h:30](../../progs/doomgeneric/r_data.h#L30)

```c
byte* R_GetColumn ( int tex, int col );
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `tex` | `int` |  |  |
| `col` | `int` |  |  |

**Returns:** `byte*`

---

<a id="r_initdata"></a>

### `R_InitData`

`function` | [progs/doomgeneric/r_data.h:36](../../progs/doomgeneric/r_data.h#L36)

```c
void R_InitData (void);
```

I/O, setting up the stuff.

---

<a id="r_precachelevel"></a>

### `R_PrecacheLevel`

`function` | [progs/doomgeneric/r_data.h:37](../../progs/doomgeneric/r_data.h#L37)

```c
void R_PrecacheLevel (void);
```

---

<a id="r_flatnumforname"></a>

### `R_FlatNumForName`

`function` | [progs/doomgeneric/r_data.h:43](../../progs/doomgeneric/r_data.h#L43)

```c
int R_FlatNumForName (char* name);
```

Retrieval.

Floor/ceiling opaque texture tiles, lookup by name. For animation?

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `name` | `char*` |  |  |

**Returns:** `int`

*Called by:* [`G_DoLoadLevel`](progs.doomgeneric.g_game.c.md#g_doloadlevel)

---

<a id="r_texturenumforname"></a>

### `R_TextureNumForName`

`function` | [progs/doomgeneric/r_data.h:48](../../progs/doomgeneric/r_data.h#L48)

```c
int R_TextureNumForName (char *name);
```

Called by P_Ticker for switches and animations, returns the texture number for the texture name.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `name` | `char *` |  |  |

**Returns:** `int`

*Called by:* [`G_DoLoadLevel`](progs.doomgeneric.g_game.c.md#g_doloadlevel), [`G_InitNew`](progs.doomgeneric.g_game.c.md#g_initnew)

---

<a id="r_checktexturenumforname"></a>

### `R_CheckTextureNumForName`

`function` | [progs/doomgeneric/r_data.h:49](../../progs/doomgeneric/r_data.h#L49)

```c
int R_CheckTextureNumForName (char *name);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `name` | `char *` |  |  |

**Returns:** `int`

---

## Macros

<a id="__r_data__"></a>

### `__R_DATA__`

`macro` | [progs/doomgeneric/r_data.h:22](../../progs/doomgeneric/r_data.h#L22)

```c
#define __R_DATA__
```

---
