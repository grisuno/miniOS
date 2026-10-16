# `progs/doomgeneric/wi_stuff.h`

> Source: [progs/doomgeneric/wi_stuff.h:1](../../progs/doomgeneric/wi_stuff.h#L1) | language `h` | coverage 83.3% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Intermission.    #include "v_video.h"   States for the intermission

## Contents

- **Functions:** [`WI_Ticker`](#wi_ticker), [`WI_Drawer`](#wi_drawer), [`WI_Start`](#wi_start), [`WI_End`](#wi_end)
- **Macros:** [`__WI_STUFF__`](#__wi_stuff__)

## Functions

<a id="wi_ticker"></a>

### `WI_Ticker`

`function` | [progs/doomgeneric/wi_stuff.h:36](../../progs/doomgeneric/wi_stuff.h#L36)

```c
void WI_Ticker (void);
```

Called by main loop, animate the intermission.

*Called by:* [`G_Ticker`](progs.doomgeneric.g_game.c.md#g_ticker)

---

<a id="wi_drawer"></a>

### `WI_Drawer`

`function` | [progs/doomgeneric/wi_stuff.h:40](../../progs/doomgeneric/wi_stuff.h#L40)

```c
void WI_Drawer (void);
```

Called by main loop, draws the intermission directly into the screen buffer.

*Called by:* [`D_Display`](progs.doomgeneric.d_main.c.md#d_display)

---

<a id="wi_start"></a>

### `WI_Start`

`function` | [progs/doomgeneric/wi_stuff.h:43](../../progs/doomgeneric/wi_stuff.h#L43)

```c
void WI_Start(wbstartstruct_t* wbstartstruct);
```

Setup for an intermission screen.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `wbstartstruct` | `wbstartstruct_t*` |  |  |

*Called by:* [`G_DoCompleted`](progs.doomgeneric.g_game.c.md#g_docompleted)

---

<a id="wi_end"></a>

### `WI_End`

`function` | [progs/doomgeneric/wi_stuff.h:46](../../progs/doomgeneric/wi_stuff.h#L46)

```c
void WI_End(void);
```

Shut down the intermission screen

*Called by:* [`G_Ticker`](progs.doomgeneric.g_game.c.md#g_ticker)

---

## Macros

<a id="__wi_stuff__"></a>

### `__WI_STUFF__`

`macro` | [progs/doomgeneric/wi_stuff.h:20](../../progs/doomgeneric/wi_stuff.h#L20)

```c
#define __WI_STUFF__
```

---
