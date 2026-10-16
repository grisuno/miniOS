# `progs/doomgeneric/r_segs.h`

> Source: [progs/doomgeneric/r_segs.h:1](../../progs/doomgeneric/r_segs.h#L1) | language `h` | coverage 33.3% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Refresh module, drawing LineSegs from BSP.

## Contents

- **Functions:** [`R_RenderMaskedSegRange`](#r_rendermaskedsegrange)
- **Macros:** [`__R_SEGS__`](#__r_segs__)

## Functions

<a id="r_rendermaskedsegrange"></a>

### `R_RenderMaskedSegRange`

`function` | [progs/doomgeneric/r_segs.h:27](../../progs/doomgeneric/r_segs.h#L27)

```c
void R_RenderMaskedSegRange ( drawseg_t* ds, int x1, int x2 );
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ds` | `drawseg_t*` |  |  |
| `x1` | `int` |  |  |
| `x2` | `int` |  |  |

---

## Macros

<a id="__r_segs__"></a>

### `__R_SEGS__`

`macro` | [progs/doomgeneric/r_segs.h:21](../../progs/doomgeneric/r_segs.h#L21)

```c
#define __R_SEGS__
```

---
