# `progs/doomgeneric/tables.c`

> Source: [progs/doomgeneric/tables.c:1](../../progs/doomgeneric/tables.c#L1) | language `c` | coverage 100.0% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Lookup tables. Do not try to look them up :-). In the order of appearance:  int finetangent[4096]        - Tangens LUT. Should work with BAM fairly well (12 of 16bit, effectively, by shifting).  int finesine[10240]           - Sine lookup. Guess what, serves as cosine, too. Remarkable thing is, how to use BAMs with this?  int tantoangle[2049] - ArcTan LUT, maps tan(angle) to angle fast. Gotta search.

## Contents

- **Functions:** [`SlopeDiv`](#slopediv)

## Functions

<a id="slopediv"></a>

### `SlopeDiv`

`function` | [progs/doomgeneric/tables.c:41](../../progs/doomgeneric/tables.c#L41)

```c
int SlopeDiv(unsigned int num, unsigned int den)
```

Utility function, called by R_PointToAngle.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `num` | `unsigned int` |  |  |
| `den` | `unsigned int` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`SlopeDiv`](#slopediv) (progs/doomgeneric/tables.h:92).

---
