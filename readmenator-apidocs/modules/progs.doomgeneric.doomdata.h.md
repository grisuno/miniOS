# `progs/doomgeneric/doomdata.h`

> Source: [progs/doomgeneric/doomdata.h:1](../../progs/doomgeneric/doomdata.h#L1) | language `h` | coverage 91.7% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: all external data is defined here most of the data is loaded into different structures at run time some internal structures shared by many modules are here    The most basic types we use, portability.  Some global defines, that configure the game.

## Contents

- **Macros:** [`__DOOMDATA__`](#__doomdata__), [`ML_BLOCKING`](#ml_blocking), [`ML_BLOCKMONSTERS`](#ml_blockmonsters), [`ML_TWOSIDED`](#ml_twosided), [`ML_DONTPEGTOP`](#ml_dontpegtop), [`ML_DONTPEGBOTTOM`](#ml_dontpegbottom), [`ML_SECRET`](#ml_secret), [`ML_SOUNDBLOCK`](#ml_soundblock), [`ML_DONTDRAW`](#ml_dontdraw), [`ML_MAPPED`](#ml_mapped), [`NF_SUBSECTOR`](#nf_subsector)

## Macros

<a id="__doomdata__"></a>

### `__DOOMDATA__`

`macro` | [progs/doomgeneric/doomdata.h:22](../../progs/doomgeneric/doomdata.h#L22)

```c
#define __DOOMDATA__
```

---

<a id="ml_blocking"></a>

### `ML_BLOCKING`

`macro` | [progs/doomgeneric/doomdata.h:98](../../progs/doomgeneric/doomdata.h#L98)

```c
#define ML_BLOCKING
```

Solid, is an obstacle.

---

<a id="ml_blockmonsters"></a>

### `ML_BLOCKMONSTERS`

`macro` | [progs/doomgeneric/doomdata.h:101](../../progs/doomgeneric/doomdata.h#L101)

```c
#define ML_BLOCKMONSTERS
```

Blocks monsters only.

---

<a id="ml_twosided"></a>

### `ML_TWOSIDED`

`macro` | [progs/doomgeneric/doomdata.h:105](../../progs/doomgeneric/doomdata.h#L105)

```c
#define ML_TWOSIDED
```

Backside will not be present at all if not two sided.

---

<a id="ml_dontpegtop"></a>

### `ML_DONTPEGTOP`

`macro` | [progs/doomgeneric/doomdata.h:117](../../progs/doomgeneric/doomdata.h#L117)

```c
#define ML_DONTPEGTOP
```

upper texture unpegged

---

<a id="ml_dontpegbottom"></a>

### `ML_DONTPEGBOTTOM`

`macro` | [progs/doomgeneric/doomdata.h:120](../../progs/doomgeneric/doomdata.h#L120)

```c
#define ML_DONTPEGBOTTOM
```

lower texture unpegged

---

<a id="ml_secret"></a>

### `ML_SECRET`

`macro` | [progs/doomgeneric/doomdata.h:123](../../progs/doomgeneric/doomdata.h#L123)

```c
#define ML_SECRET
```

In AutoMap: don't map as two sided: IT'S A SECRET!

---

<a id="ml_soundblock"></a>

### `ML_SOUNDBLOCK`

`macro` | [progs/doomgeneric/doomdata.h:126](../../progs/doomgeneric/doomdata.h#L126)

```c
#define ML_SOUNDBLOCK
```

Sound rendering: don't let sound cross two of these.

---

<a id="ml_dontdraw"></a>

### `ML_DONTDRAW`

`macro` | [progs/doomgeneric/doomdata.h:129](../../progs/doomgeneric/doomdata.h#L129)

```c
#define ML_DONTDRAW
```

Don't draw on the automap at all.

---

<a id="ml_mapped"></a>

### `ML_MAPPED`

`macro` | [progs/doomgeneric/doomdata.h:132](../../progs/doomgeneric/doomdata.h#L132)

```c
#define ML_MAPPED
```

Set if already seen, thus drawn in automap.

---

<a id="nf_subsector"></a>

### `NF_SUBSECTOR`

`macro` | [progs/doomgeneric/doomdata.h:175](../../progs/doomgeneric/doomdata.h#L175)

```c
#define NF_SUBSECTOR
```

Indicate a leaf.

---
