# `progs/doomgeneric/f_wipe.h`

> Source: [progs/doomgeneric/f_wipe.h:1](../../progs/doomgeneric/f_wipe.h#L1) | language `h` | coverage 25.0% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Mission start screen wipe/melt, special effects.      SCREEN WIPE PACKAGE

## Contents

- **Functions:** [`wipe_StartScreen`](#wipe_startscreen), [`wipe_EndScreen`](#wipe_endscreen), [`wipe_ScreenWipe`](#wipe_screenwipe)

## Functions

<a id="wipe_startscreen"></a>

### `wipe_StartScreen`

`function` | [progs/doomgeneric/f_wipe.h:39](../../progs/doomgeneric/f_wipe.h#L39)

```c
int wipe_StartScreen ( int x, int y, int width, int height );
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `y` | `int` |  |  |
| `width` | `int` |  |  |
| `height` | `int` |  |  |

**Returns:** `int`

*Called by:* [`D_Display`](progs.doomgeneric.d_main.c.md#d_display)

---

<a id="wipe_endscreen"></a>

### `wipe_EndScreen`

`function` | [progs/doomgeneric/f_wipe.h:47](../../progs/doomgeneric/f_wipe.h#L47)

```c
int wipe_EndScreen ( int x, int y, int width, int height );
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `y` | `int` |  |  |
| `width` | `int` |  |  |
| `height` | `int` |  |  |

**Returns:** `int`

*Called by:* [`D_Display`](progs.doomgeneric.d_main.c.md#d_display)

---

<a id="wipe_screenwipe"></a>

### `wipe_ScreenWipe`

`function` | [progs/doomgeneric/f_wipe.h:55](../../progs/doomgeneric/f_wipe.h#L55)

```c
int wipe_ScreenWipe ( int wipeno, int x, int y, int width, int height, int ticks );
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `wipeno` | `int` |  |  |
| `x` | `int` |  |  |
| `y` | `int` |  |  |
| `width` | `int` |  |  |
| `height` | `int` |  |  |
| `ticks` | `int` |  |  |

**Returns:** `int`

*Called by:* [`D_Display`](progs.doomgeneric.d_main.c.md#d_display)

---
