# `progs/doomgeneric/i_scale.c`

> Source: [progs/doomgeneric/i_scale.c:1](../../progs/doomgeneric/i_scale.c#L1) | language `c` | coverage 12.5% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Screen scale-up code: 1x,2x,3x,4x pixel doubling Aspect ratio-correcting stretch functions

## Contents

- **Functions:** [`I_InitScale`](#i_initscale), [`I_ResetScaleTables`](#i_resetscaletables)
- **Macros:** [`inline`](#inline), [`DRAW_PIXEL2`](#draw_pixel2), [`DRAW_PIXEL3`](#draw_pixel3), [`DRAW_PIXEL4`](#draw_pixel4), [`DRAW_PIXEL5`](#draw_pixel5)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_progs_doomgeneric_i_scale_c__I_ResetScaleTables(["I_ResetScaleTables"])
    n_progs_doomgeneric_z_zone_h__Z_Free["z_zone.Z_Free"]
    n_progs_doomgeneric_i_scale_c__I_ResetScaleTables -.-> n_progs_doomgeneric_z_zone_h__Z_Free
```

## Functions

<a id="i_initscale"></a>

### `I_InitScale`

`function` | [progs/doomgeneric/i_scale.c:61](../../progs/doomgeneric/i_scale.c#L61)

```c
void I_InitScale(byte *_src_buffer, byte *_dest_buffer, int _dest_pitch)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `_src_buffer` | `byte *` |  |  |
| `_dest_buffer` | `byte *` |  |  |
| `_dest_pitch` | `int` |  |  |

---

<a id="i_resetscaletables"></a>

### `I_ResetScaleTables`

`function` | [progs/doomgeneric/i_scale.c:404](../../progs/doomgeneric/i_scale.c#L404)

```c
void I_ResetScaleTables(byte *palette)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `palette` | `byte *` |  |  |

*Calls:* [`Z_Free`](progs.doomgeneric.z_zone.h.md#z_free)

---

## Macros

<a id="inline"></a>

### `inline`

`macro` `inline` | [progs/doomgeneric/i_scale.c:32](../../progs/doomgeneric/i_scale.c#L32)

```c
#define inline
```

---

<a id="draw_pixel2"></a>

### `DRAW_PIXEL2`

`macro` | [progs/doomgeneric/i_scale.c:1099](../../progs/doomgeneric/i_scale.c#L1099)

```c
#define DRAW_PIXEL2
```

---

<a id="draw_pixel3"></a>

### `DRAW_PIXEL3`

`macro` | [progs/doomgeneric/i_scale.c:1194](../../progs/doomgeneric/i_scale.c#L1194)

```c
#define DRAW_PIXEL3
```

---

<a id="draw_pixel4"></a>

### `DRAW_PIXEL4`

`macro` | [progs/doomgeneric/i_scale.c:1276](../../progs/doomgeneric/i_scale.c#L1276)

```c
#define DRAW_PIXEL4
```

---

<a id="draw_pixel5"></a>

### `DRAW_PIXEL5`

`macro` | [progs/doomgeneric/i_scale.c:1387](../../progs/doomgeneric/i_scale.c#L1387)

```c
#define DRAW_PIXEL5
```

---
