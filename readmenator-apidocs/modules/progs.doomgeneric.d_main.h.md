# `progs/doomgeneric/d_main.h`

> Source: [progs/doomgeneric/d_main.h:1](../../progs/doomgeneric/d_main.h#L1) | language `h` | coverage 25.0% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: System specific interface stuff.         Read events from all input devices

## Contents

- **Functions:** [`D_ProcessEvents`](#d_processevents), [`D_PageTicker`](#d_pageticker), [`D_PageDrawer`](#d_pagedrawer), [`D_AdvanceDemo`](#d_advancedemo), [`D_DoAdvanceDemo`](#d_doadvancedemo), [`D_StartTitle`](#d_starttitle)
- **Macros:** [`__D_MAIN__`](#__d_main__)
- **Variables:** [`gameaction`](#gameaction)

## Functions

<a id="d_processevents"></a>

### `D_ProcessEvents`

`function` | [progs/doomgeneric/d_main.h:30](../../progs/doomgeneric/d_main.h#L30)

```c
void D_ProcessEvents (void);
```

---

<a id="d_pageticker"></a>

### `D_PageTicker`

`function` | [progs/doomgeneric/d_main.h:36](../../progs/doomgeneric/d_main.h#L36)

```c
void D_PageTicker (void);
```

BASE LEVEL

*Called by:* [`G_Ticker`](progs.doomgeneric.g_game.c.md#g_ticker)

---

<a id="d_pagedrawer"></a>

### `D_PageDrawer`

`function` | [progs/doomgeneric/d_main.h:37](../../progs/doomgeneric/d_main.h#L37)

```c
void D_PageDrawer (void);
```

---

<a id="d_advancedemo"></a>

### `D_AdvanceDemo`

`function` | [progs/doomgeneric/d_main.h:38](../../progs/doomgeneric/d_main.h#L38)

```c
void D_AdvanceDemo (void);
```

*Called by:* [`G_CheckDemoStatus`](progs.doomgeneric.g_game.c.md#g_checkdemostatus)

---

<a id="d_doadvancedemo"></a>

### `D_DoAdvanceDemo`

`function` | [progs/doomgeneric/d_main.h:39](../../progs/doomgeneric/d_main.h#L39)

```c
void D_DoAdvanceDemo (void);
```

---

<a id="d_starttitle"></a>

### `D_StartTitle`

`function` | [progs/doomgeneric/d_main.h:40](../../progs/doomgeneric/d_main.h#L40)

```c
void D_StartTitle (void);
```

*Called by:* [`G_DoPlayDemo`](progs.doomgeneric.g_game.c.md#g_doplaydemo), [`M_EndGameResponse`](progs.doomgeneric.m_menu.c.md#m_endgameresponse)

---

## Macros

<a id="__d_main__"></a>

### `__D_MAIN__`

`macro` | [progs/doomgeneric/d_main.h:21](../../progs/doomgeneric/d_main.h#L21)

```c
#define __D_MAIN__
```

---

## Variables

<a id="gameaction"></a>

### `gameaction`

`variable` `extern` | [progs/doomgeneric/d_main.h:46](../../progs/doomgeneric/d_main.h#L46)

```c
extern gameaction_t gameaction;
```

---
