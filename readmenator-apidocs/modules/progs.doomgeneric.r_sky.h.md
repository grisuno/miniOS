# `progs/doomgeneric/r_sky.h`

> Source: [progs/doomgeneric/r_sky.h:1](../../progs/doomgeneric/r_sky.h#L1) | language `h` | coverage 80.0% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Sky rendering.       SKY, store the number for name.  The sky map is 256*128*4 maps.

## Contents

- **Functions:** [`R_InitSkyMap`](#r_initskymap)
- **Macros:** [`__R_SKY__`](#__r_sky__), [`SKYFLATNAME`](#skyflatname), [`ANGLETOSKYSHIFT`](#angletoskyshift)
- **Variables:** [`skytexture`](#skytexture), [`skytexturemid`](#skytexturemid)

## Functions

<a id="r_initskymap"></a>

### `R_InitSkyMap`

`function` | [progs/doomgeneric/r_sky.h:35](../../progs/doomgeneric/r_sky.h#L35)

```c
void R_InitSkyMap (void);
```

Called whenever the view size changes.

*Called by:* [`R_Init`](progs.doomgeneric.r_main.c.md#r_init)

---

## Macros

<a id="__r_sky__"></a>

### `__R_SKY__`

`macro` | [progs/doomgeneric/r_sky.h:21](../../progs/doomgeneric/r_sky.h#L21)

```c
#define __R_SKY__
```

---

<a id="skyflatname"></a>

### `SKYFLATNAME`

`macro` | [progs/doomgeneric/r_sky.h:26](../../progs/doomgeneric/r_sky.h#L26)

```c
#define SKYFLATNAME
```

SKY, store the number for name.

---

<a id="angletoskyshift"></a>

### `ANGLETOSKYSHIFT`

`macro` | [progs/doomgeneric/r_sky.h:29](../../progs/doomgeneric/r_sky.h#L29)

```c
#define ANGLETOSKYSHIFT
```

The sky map is 256*128*4 maps.

---

## Variables

<a id="skytexture"></a>

### `skytexture`

`variable` `extern` | [progs/doomgeneric/r_sky.h:31](../../progs/doomgeneric/r_sky.h#L31)

```c
extern int skytexture;
```

---

<a id="skytexturemid"></a>

### `skytexturemid`

`variable` `extern` | [progs/doomgeneric/r_sky.h:32](../../progs/doomgeneric/r_sky.h#L32)

```c
extern int skytexturemid;
```

---
