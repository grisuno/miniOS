# `progs/doomgeneric/am_map.h`

> Source: [progs/doomgeneric/am_map.h:1](../../progs/doomgeneric/am_map.h#L1) | language `h` | coverage 71.4% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: AutoMap module.     Used by ST StatusBar stuff.

## Contents

- **Functions:** [`AM_Ticker`](#am_ticker), [`AM_Drawer`](#am_drawer), [`AM_Stop`](#am_stop)
- **Macros:** [`AM_MSGHEADER`](#am_msgheader), [`AM_MSGENTERED`](#am_msgentered), [`AM_MSGEXITED`](#am_msgexited)
- **Variables:** [`cheat_amap`](#cheat_amap)

## Functions

<a id="am_ticker"></a>

### `AM_Ticker`

`function` | [progs/doomgeneric/am_map.h:35](../../progs/doomgeneric/am_map.h#L35)

```c
void AM_Ticker (void);
```

Called by main loop.

*Called by:* [`G_Ticker`](progs.doomgeneric.g_game.c.md#g_ticker)

---

<a id="am_drawer"></a>

### `AM_Drawer`

`function` | [progs/doomgeneric/am_map.h:39](../../progs/doomgeneric/am_map.h#L39)

```c
void AM_Drawer (void);
```

Called by main loop, called instead of view drawer if automap active.

*Called by:* [`D_Display`](progs.doomgeneric.d_main.c.md#d_display)

---

<a id="am_stop"></a>

### `AM_Stop`

`function` | [progs/doomgeneric/am_map.h:43](../../progs/doomgeneric/am_map.h#L43)

```c
void AM_Stop (void);
```

Called to force the automap to quit if the level is completed while it is up.

*Called by:* [`G_DoCompleted`](progs.doomgeneric.g_game.c.md#g_docompleted), [`P_KillMobj`](progs.doomgeneric.p_inter.c.md#p_killmobj)

---

## Macros

<a id="am_msgheader"></a>

### `AM_MSGHEADER`

`macro` | [progs/doomgeneric/am_map.h:26](../../progs/doomgeneric/am_map.h#L26)

```c
#define AM_MSGHEADER
```

Used by ST StatusBar stuff.

---

<a id="am_msgentered"></a>

### `AM_MSGENTERED`

`macro` | [progs/doomgeneric/am_map.h:27](../../progs/doomgeneric/am_map.h#L27)

```c
#define AM_MSGENTERED
```

---

<a id="am_msgexited"></a>

### `AM_MSGEXITED`

`macro` | [progs/doomgeneric/am_map.h:28](../../progs/doomgeneric/am_map.h#L28)

```c
#define AM_MSGEXITED
```

---

## Variables

<a id="cheat_amap"></a>

### `cheat_amap`

`variable` `extern` | [progs/doomgeneric/am_map.h:46](../../progs/doomgeneric/am_map.h#L46)

```c
extern cheatseq_t cheat_amap;
```

---
