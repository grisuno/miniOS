# `progs/doomgeneric/d_ticcmd.h`

> Source: [progs/doomgeneric/d_ticcmd.h:1](../../progs/doomgeneric/d_ticcmd.h#L1) | language `h` | coverage 33.3% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 1993-2008 Raven Software Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: System specific interface stuff.       The data sampled per tick (single player) and transmitted to other peers (multiplayer). Mainly movements/button commands per game tick, plus a checksum for internal state consistency.

## Contents

- **Structs:** [`ticcmd_t`](#ticcmd_t)
- **Macros:** [`__D_TICCMD__`](#__d_ticcmd__)

## Structs

<a id="ticcmd_t"></a>

### `ticcmd_t`

`struct` | [progs/doomgeneric/d_ticcmd.h:32](../../progs/doomgeneric/d_ticcmd.h#L32)

```c
typedef struct
```

---

## Macros

<a id="__d_ticcmd__"></a>

### `__D_TICCMD__`

`macro` | [progs/doomgeneric/d_ticcmd.h:22](../../progs/doomgeneric/d_ticcmd.h#L22)

```c
#define __D_TICCMD__
```

---
