# `progs/doomgeneric/f_finale.h`

> Source: [progs/doomgeneric/f_finale.h:1](../../progs/doomgeneric/f_finale.h#L1) | language `h` | coverage 60.0% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION:        FINALE   Called by main loop.

## Contents

- **Functions:** [`F_Ticker`](#f_ticker), [`F_Drawer`](#f_drawer), [`F_StartFinale`](#f_startfinale)
- **Macros:** [`__F_FINALE__`](#__f_finale__)

## Functions

<a id="f_ticker"></a>

### `F_Ticker`

`function` | [progs/doomgeneric/f_finale.h:34](../../progs/doomgeneric/f_finale.h#L34)

```c
void F_Ticker (void);
```

Called by main loop.

*Called by:* [`G_Ticker`](progs.doomgeneric.g_game.c.md#g_ticker)

---

<a id="f_drawer"></a>

### `F_Drawer`

`function` | [progs/doomgeneric/f_finale.h:37](../../progs/doomgeneric/f_finale.h#L37)

```c
void F_Drawer (void);
```

Called by main loop.

*Called by:* [`D_Display`](progs.doomgeneric.d_main.c.md#d_display)

---

<a id="f_startfinale"></a>

### `F_StartFinale`

`function` | [progs/doomgeneric/f_finale.h:40](../../progs/doomgeneric/f_finale.h#L40)

```c
void F_StartFinale (void);
```

*Called by:* [`G_Ticker`](progs.doomgeneric.g_game.c.md#g_ticker), [`G_WorldDone`](progs.doomgeneric.g_game.c.md#g_worlddone)

---

## Macros

<a id="__f_finale__"></a>

### `__F_FINALE__`

`macro` | [progs/doomgeneric/f_finale.h:21](../../progs/doomgeneric/f_finale.h#L21)

```c
#define __F_FINALE__
```

---
