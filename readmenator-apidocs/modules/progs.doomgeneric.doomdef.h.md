# `progs/doomgeneric/doomdef.h`

> Source: [progs/doomgeneric/doomdef.h:1](../../progs/doomgeneric/doomdef.h#L1) | language `h` | coverage 70.0% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Internally used data structures for virtually everything, lots of other stuff.

## Contents

- **Macros:** [`__DOOMDEF__`](#__doomdef__), [`DOOM_VERSION`](#doom_version), [`DOOM_191_VERSION`](#doom_191_version), [`RANGECHECK`](#rangecheck), [`MAXPLAYERS`](#maxplayers), [`MTF_EASY`](#mtf_easy), [`MTF_NORMAL`](#mtf_normal), [`MTF_HARD`](#mtf_hard), [`MTF_AMBUSH`](#mtf_ambush)

## Macros

<a id="__doomdef__"></a>

### `__DOOMDEF__`

`macro` | [progs/doomgeneric/doomdef.h:21](../../progs/doomgeneric/doomdef.h#L21)

```c
#define __DOOMDEF__
```

---

<a id="doom_version"></a>

### `DOOM_VERSION`

`macro` | [progs/doomgeneric/doomdef.h:34](../../progs/doomgeneric/doomdef.h#L34)

```c
#define DOOM_VERSION
```

Global parameters/defines.

DOOM version

---

<a id="doom_191_version"></a>

### `DOOM_191_VERSION`

`macro` | [progs/doomgeneric/doomdef.h:37](../../progs/doomgeneric/doomdef.h#L37)

```c
#define DOOM_191_VERSION
```

Version code for cph's longtics hack ("v1.91")

---

<a id="rangecheck"></a>

### `RANGECHECK`

`macro` | [progs/doomgeneric/doomdef.h:42](../../progs/doomgeneric/doomdef.h#L42)

```c
#define RANGECHECK
```

If rangecheck is undefined, most parameter validation debugging code will not be compiled

---

<a id="maxplayers"></a>

### `MAXPLAYERS`

`macro` | [progs/doomgeneric/doomdef.h:45](../../progs/doomgeneric/doomdef.h#L45)

```c
#define MAXPLAYERS
```

The maximum number of players, multiplayer/networking.

---

<a id="mtf_easy"></a>

### `MTF_EASY`

`macro` | [progs/doomgeneric/doomdef.h:77](../../progs/doomgeneric/doomdef.h#L77)

```c
#define MTF_EASY
```

Skill flags.

---

<a id="mtf_normal"></a>

### `MTF_NORMAL`

`macro` | [progs/doomgeneric/doomdef.h:78](../../progs/doomgeneric/doomdef.h#L78)

```c
#define MTF_NORMAL
```

---

<a id="mtf_hard"></a>

### `MTF_HARD`

`macro` | [progs/doomgeneric/doomdef.h:79](../../progs/doomgeneric/doomdef.h#L79)

```c
#define MTF_HARD
```

---

<a id="mtf_ambush"></a>

### `MTF_AMBUSH`

`macro` | [progs/doomgeneric/doomdef.h:82](../../progs/doomgeneric/doomdef.h#L82)

```c
#define MTF_AMBUSH
```

Deaf monsters/do not react to sound.

---
