# `progs/doomgeneric/p_pspr.h`

> Source: [progs/doomgeneric/p_pspr.h:1](../../progs/doomgeneric/p_pspr.h#L1) | language `h` | coverage 40.0% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Sprite animation.     Basic data types. Needs fixed point, and BAM angles.    Needs to include the precompiled

## Contents

- **Structs:** [`pspdef_t`](#pspdef_t)
- **Macros:** [`__P_PSPR__`](#__p_pspr__), [`FF_FULLBRIGHT`](#ff_fullbright), [`FF_FRAMEMASK`](#ff_framemask)

## Structs

<a id="pspdef_t"></a>

### `pspdef_t`

`struct` | [progs/doomgeneric/p_pspr.h:62](../../progs/doomgeneric/p_pspr.h#L62)

```c
typedef struct
```

---

## Macros

<a id="__p_pspr__"></a>

### `__P_PSPR__`

`macro` | [progs/doomgeneric/p_pspr.h:21](../../progs/doomgeneric/p_pspr.h#L21)

```c
#define __P_PSPR__
```

---

<a id="ff_fullbright"></a>

### `FF_FULLBRIGHT`

`macro` | [progs/doomgeneric/p_pspr.h:44](../../progs/doomgeneric/p_pspr.h#L44)

```c
#define FF_FULLBRIGHT
```

Frame flags: handles maximum brightness (torches, muzzle flare, light sources)

---

<a id="ff_framemask"></a>

### `FF_FRAMEMASK`

`macro` | [progs/doomgeneric/p_pspr.h:45](../../progs/doomgeneric/p_pspr.h#L45)

```c
#define FF_FRAMEMASK
```

---
