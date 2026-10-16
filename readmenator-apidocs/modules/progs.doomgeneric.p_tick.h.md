# `progs/doomgeneric/p_tick.h`

> Source: [progs/doomgeneric/p_tick.h:1](../../progs/doomgeneric/p_tick.h#L1) | language `h` | coverage 66.7% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: ?        Called by C_Ticker, can call G_PlayerExited. Carries out all thinking of monsters and players.

## Contents

- **Functions:** [`P_Ticker`](#p_ticker)
- **Macros:** [`__P_TICK__`](#__p_tick__)

## Functions

<a id="p_ticker"></a>

### `P_Ticker`

`function` | [progs/doomgeneric/p_tick.h:29](../../progs/doomgeneric/p_tick.h#L29)

```c
void P_Ticker (void);
```

Called by C_Ticker, can call G_PlayerExited.

Carries out all thinking of monsters and players.

*Called by:* [`G_Ticker`](progs.doomgeneric.g_game.c.md#g_ticker)

---

## Macros

<a id="__p_tick__"></a>

### `__P_TICK__`

`macro` | [progs/doomgeneric/p_tick.h:21](../../progs/doomgeneric/p_tick.h#L21)

```c
#define __P_TICK__
```

---
