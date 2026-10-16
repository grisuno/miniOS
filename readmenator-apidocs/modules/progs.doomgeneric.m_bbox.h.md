# `progs/doomgeneric/m_bbox.h`

> Source: [progs/doomgeneric/m_bbox.h:1](../../progs/doomgeneric/m_bbox.h#L1) | language `h` | coverage 50.0% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Nil.        Bounding box coordinate storage.

## Contents

- **Functions:** [`M_ClearBox`](#m_clearbox), [`M_AddToBox`](#m_addtobox)
- **Macros:** [`__M_BBOX__`](#__m_bbox__)

## Functions

<a id="m_clearbox"></a>

### `M_ClearBox`

`function` | [progs/doomgeneric/m_bbox.h:38](../../progs/doomgeneric/m_bbox.h#L38)

```c
void M_ClearBox (fixed_t* box);
```

Bounding box functions.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `box` | `fixed_t*` |  |  |

*Called by:* [`P_GroupLines`](progs.doomgeneric.p_setup.c.md#p_grouplines)

---

<a id="m_addtobox"></a>

### `M_AddToBox`

`function` | [progs/doomgeneric/m_bbox.h:41](../../progs/doomgeneric/m_bbox.h#L41)

```c
void M_AddToBox ( fixed_t* box, fixed_t x, fixed_t y );
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `box` | `fixed_t*` |  |  |
| `x` | `fixed_t` |  |  |
| `y` | `fixed_t` |  |  |

*Called by:* [`P_GroupLines`](progs.doomgeneric.p_setup.c.md#p_grouplines), [`V_MarkRect`](progs.doomgeneric.v_video.c.md#v_markrect)

---

## Macros

<a id="__m_bbox__"></a>

### `__M_BBOX__`

`macro` | [progs/doomgeneric/m_bbox.h:21](../../progs/doomgeneric/m_bbox.h#L21)

```c
#define __M_BBOX__
```

---
