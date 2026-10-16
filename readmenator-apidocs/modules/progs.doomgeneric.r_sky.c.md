# `progs/doomgeneric/r_sky.c`

> Source: [progs/doomgeneric/r_sky.c:1](../../progs/doomgeneric/r_sky.c#L1) | language `c` | coverage 100.0% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Sky rendering. The DOOM sky is a texture map like any wall, wrapping around. A 1024 columns equal 360 degrees. The default sky map is 256 columns and repeats 4 times on a 320 screen?      Needed for FRACUNIT.  Needed for Flat retrieval.

## Contents

- **Functions:** [`R_InitSkyMap`](#r_initskymap)

## Functions

<a id="r_initskymap"></a>

### `R_InitSkyMap`

`function` | [progs/doomgeneric/r_sky.c:47](../../progs/doomgeneric/r_sky.c#L47)

```c
void R_InitSkyMap (void)
```

R_InitSkyMap Called whenever the view size changes.

---
