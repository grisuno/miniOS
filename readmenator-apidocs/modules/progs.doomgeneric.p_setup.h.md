# `progs/doomgeneric/p_setup.h`

> Source: [progs/doomgeneric/p_setup.h:1](../../progs/doomgeneric/p_setup.h#L1) | language `h` | coverage 50.0% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Setup a game, startup stuff.        NOT called by W_Ticker. Fixme.

## Contents

- **Functions:** [`P_SetupLevel`](#p_setuplevel), [`P_Init`](#p_init)
- **Macros:** [`__P_SETUP__`](#__p_setup__)

## Functions

<a id="p_setuplevel"></a>

### `P_SetupLevel`

`function` | [progs/doomgeneric/p_setup.h:28](../../progs/doomgeneric/p_setup.h#L28)

```c
void P_SetupLevel ( int episode, int map, int playermask, skill_t skill);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `episode` | `int` |  |  |
| `map` | `int` |  |  |
| `playermask` | `int` |  |  |
| `skill` | `skill_t` |  |  |

*Called by:* [`G_DoLoadLevel`](progs.doomgeneric.g_game.c.md#g_doloadlevel)

---

<a id="p_init"></a>

### `P_Init`

`function` | [progs/doomgeneric/p_setup.h:35](../../progs/doomgeneric/p_setup.h#L35)

```c
void P_Init (void);
```

Called by startup code.

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain)

---

## Macros

<a id="__p_setup__"></a>

### `__P_SETUP__`

`macro` | [progs/doomgeneric/p_setup.h:21](../../progs/doomgeneric/p_setup.h#L21)

```c
#define __P_SETUP__
```

---
