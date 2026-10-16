# `progs/doomgeneric/d_mode.h`

> Source: [progs/doomgeneric/d_mode.h:1](../../progs/doomgeneric/d_mode.h#L1) | language `h` | coverage 25.0% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Functions and definitions relating to the game type and operational mode.     The "mission" controls what game we are playing.

## Contents

- **Functions:** [`D_GetNumEpisodes`](#d_getnumepisodes), [`D_GameMissionString`](#d_gamemissionstring)
- **Macros:** [`__D_MODE__`](#__d_mode__)

## Functions

<a id="d_getnumepisodes"></a>

### `D_GetNumEpisodes`

`function` | [progs/doomgeneric/d_mode.h:93](../../progs/doomgeneric/d_mode.h#L93)

```c
int D_GetNumEpisodes(GameMission_t mission, GameMode_t mode);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `mission` | `GameMission_t` |  |  |
| `mode` | `GameMode_t` |  |  |

**Returns:** `int`

---

<a id="d_gamemissionstring"></a>

### `D_GameMissionString`

`function` | [progs/doomgeneric/d_mode.h:95](../../progs/doomgeneric/d_mode.h#L95)

```c
char *D_GameMissionString(GameMission_t mission);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `mission` | `GameMission_t` |  |  |

**Returns:** `char *`

---

## Macros

<a id="__d_mode__"></a>

### `__D_MODE__`

`macro` | [progs/doomgeneric/d_mode.h:21](../../progs/doomgeneric/d_mode.h#L21)

```c
#define __D_MODE__
```

---
