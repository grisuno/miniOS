# `progs/doomgeneric/m_bbox.c`

> Source: [progs/doomgeneric/m_bbox.c:1](../../progs/doomgeneric/m_bbox.c#L1) | language `c` | coverage 66.7% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Main loop menu stuff. Random number LUT. Default Config File. PCX Screenshots.

## Contents

- **Functions:** [`M_ClearBox`](#m_clearbox), [`M_AddToBox`](#m_addtobox)

## Functions

<a id="m_clearbox"></a>

### `M_ClearBox`

`function` | [progs/doomgeneric/m_bbox.c:29](../../progs/doomgeneric/m_bbox.c#L29)

```c
void M_ClearBox (fixed_t *box)
```

Bounding box functions.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `box` | `fixed_t *` |  |  |

> **Inherited:** Documentation from [`M_ClearBox`](#m_clearbox) (progs/doomgeneric/m_bbox.h:38).

---

<a id="m_addtobox"></a>

### `M_AddToBox`

`function` | [progs/doomgeneric/m_bbox.c:36](../../progs/doomgeneric/m_bbox.c#L36)

```c
void M_AddToBox ( fixed_t* box, fixed_t x, fixed_t y )
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `box` | `fixed_t*` |  |  |
| `x` | `fixed_t` |  |  |
| `y` | `fixed_t` |  |  |

---
