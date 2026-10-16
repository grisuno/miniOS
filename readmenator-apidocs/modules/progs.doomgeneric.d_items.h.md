# `progs/doomgeneric/d_items.h`

> Source: [progs/doomgeneric/d_items.h:1](../../progs/doomgeneric/d_items.h#L1) | language `h` | coverage 66.7% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Items: key cards, artifacts, weapon, ammunition.        Weapon info: sprite frames, ammunition use.

## Contents

- **Structs:** [`weaponinfo_t`](#weaponinfo_t)
- **Macros:** [`__D_ITEMS__`](#__d_items__)
- **Variables:** [`weaponinfo`](#weaponinfo)

## Structs

<a id="weaponinfo_t"></a>

### `weaponinfo_t`

`struct` | [progs/doomgeneric/d_items.h:28](../../progs/doomgeneric/d_items.h#L28)

```c
typedef struct
```

Weapon info: sprite frames, ammunition use.

---

## Macros

<a id="__d_items__"></a>

### `__D_ITEMS__`

`macro` | [progs/doomgeneric/d_items.h:21](../../progs/doomgeneric/d_items.h#L21)

```c
#define __D_ITEMS__
```

---

## Variables

<a id="weaponinfo"></a>

### `weaponinfo`

`variable` `extern` | [progs/doomgeneric/d_items.h:39](../../progs/doomgeneric/d_items.h#L39)

```c
extern weaponinfo_t weaponinfo[NUMWEAPONS];
```

---
