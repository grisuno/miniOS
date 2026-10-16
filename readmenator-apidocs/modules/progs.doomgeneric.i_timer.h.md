# `progs/doomgeneric/i_timer.h`

> Source: [progs/doomgeneric/i_timer.h:1](../../progs/doomgeneric/i_timer.h#L1) | language `h` | coverage 75.0% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: System-specific timer interface      Called by D_DoomLoop, returns current time in tics.

## Contents

- **Functions:** [`I_GetTime`](#i_gettime), [`I_GetTimeMS`](#i_gettimems), [`I_Sleep`](#i_sleep), [`I_InitTimer`](#i_inittimer), [`I_WaitVBL`](#i_waitvbl)
- **Macros:** [`__I_TIMER__`](#__i_timer__), [`TICRATE`](#ticrate)

## Functions

<a id="i_gettime"></a>

### `I_GetTime`

`function` | [progs/doomgeneric/i_timer.h:27](../../progs/doomgeneric/i_timer.h#L27)

```c
int I_GetTime (void);
```

Called by D_DoomLoop, returns current time in tics.

**Returns:** `int`

*Called by:* [`TryRunTics`](progs.doomgeneric.d_loop.c.md#tryruntics), [`D_Display`](progs.doomgeneric.d_main.c.md#d_display), [`G_CheckDemoStatus`](progs.doomgeneric.g_game.c.md#g_checkdemostatus), [`G_DoPlayDemo`](progs.doomgeneric.g_game.c.md#g_doplaydemo), [`M_Responder`](progs.doomgeneric.m_menu.c.md#m_responder)

---

<a id="i_gettimems"></a>

### `I_GetTimeMS`

`function` | [progs/doomgeneric/i_timer.h:30](../../progs/doomgeneric/i_timer.h#L30)

```c
int I_GetTimeMS (void);
```

returns current time in ms

**Returns:** `int`

---

<a id="i_sleep"></a>

### `I_Sleep`

`function` | [progs/doomgeneric/i_timer.h:33](../../progs/doomgeneric/i_timer.h#L33)

```c
void I_Sleep(int ms);
```

Pause for a specified number of ms

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ms` | `int` |  |  |

*Called by:* [`TryRunTics`](progs.doomgeneric.d_loop.c.md#tryruntics), [`D_Display`](progs.doomgeneric.d_main.c.md#d_display)

---

<a id="i_inittimer"></a>

### `I_InitTimer`

`function` | [progs/doomgeneric/i_timer.h:36](../../progs/doomgeneric/i_timer.h#L36)

```c
void I_InitTimer(void);
```

Initialize timer

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain)

---

<a id="i_waitvbl"></a>

### `I_WaitVBL`

`function` | [progs/doomgeneric/i_timer.h:39](../../progs/doomgeneric/i_timer.h#L39)

```c
void I_WaitVBL(int count);
```

Wait for vertical retrace or pause a bit.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `count` | `int` |  |  |

*Called by:* [`M_QuitResponse`](progs.doomgeneric.m_menu.c.md#m_quitresponse)

---

## Macros

<a id="__i_timer__"></a>

### `__I_TIMER__`

`macro` | [progs/doomgeneric/i_timer.h:21](../../progs/doomgeneric/i_timer.h#L21)

```c
#define __I_TIMER__
```

---

<a id="ticrate"></a>

### `TICRATE`

`macro` | [progs/doomgeneric/i_timer.h:23](../../progs/doomgeneric/i_timer.h#L23)

```c
#define TICRATE
```

---
