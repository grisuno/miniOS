# `progs/doomgeneric/st_stuff.h`

> Source: [progs/doomgeneric/st_stuff.h:1](../../progs/doomgeneric/st_stuff.h#L1) | language `h` | coverage 75.0% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Status bar code. Does the face/direction indicator animatin. Does palette indicators as well (red pain/berserk, bright pickup)     Size of statusbar. Now sensitive for scaling.

## Contents

- **Functions:** [`ST_Ticker`](#st_ticker), [`ST_Drawer`](#st_drawer), [`ST_Start`](#st_start), [`ST_Init`](#st_init)
- **Macros:** [`ST_HEIGHT`](#st_height), [`ST_WIDTH`](#st_width), [`ST_Y`](#st_y)
- **Variables:** [`st_backing_screen`](#st_backing_screen), [`cheat_mus`](#cheat_mus), [`cheat_god`](#cheat_god), [`cheat_ammo`](#cheat_ammo), [`cheat_ammonokey`](#cheat_ammonokey), [`cheat_noclip`](#cheat_noclip), [`cheat_commercial_noclip`](#cheat_commercial_noclip), [`cheat_powerup`](#cheat_powerup), [`cheat_choppers`](#cheat_choppers), [`cheat_clev`](#cheat_clev), [`cheat_mypos`](#cheat_mypos)

## Functions

<a id="st_ticker"></a>

### `ST_Ticker`

`function` | [progs/doomgeneric/st_stuff.h:43](../../progs/doomgeneric/st_stuff.h#L43)

```c
void ST_Ticker (void);
```

Called by main loop.

*Called by:* [`G_Ticker`](progs.doomgeneric.g_game.c.md#g_ticker)

---

<a id="st_drawer"></a>

### `ST_Drawer`

`function` | [progs/doomgeneric/st_stuff.h:46](../../progs/doomgeneric/st_stuff.h#L46)

```c
void ST_Drawer (boolean fullscreen, boolean refresh);
```

Called by main loop.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fullscreen` | `boolean` |  |  |
| `refresh` | `boolean` |  |  |

*Called by:* [`D_Display`](progs.doomgeneric.d_main.c.md#d_display)

---

<a id="st_start"></a>

### `ST_Start`

`function` | [progs/doomgeneric/st_stuff.h:49](../../progs/doomgeneric/st_stuff.h#L49)

```c
void ST_Start (void);
```

Called when the console player is spawned on each level.

*Called by:* [`P_SpawnPlayer`](progs.doomgeneric.p_mobj.c.md#p_spawnplayer)

---

<a id="st_init"></a>

### `ST_Init`

`function` | [progs/doomgeneric/st_stuff.h:52](../../progs/doomgeneric/st_stuff.h#L52)

```c
void ST_Init (void);
```

Called by startup code.

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain)

---

## Macros

<a id="st_height"></a>

### `ST_HEIGHT`

`macro` | [progs/doomgeneric/st_stuff.h:30](../../progs/doomgeneric/st_stuff.h#L30)

```c
#define ST_HEIGHT
```

Size of statusbar.

Now sensitive for scaling.

---

<a id="st_width"></a>

### `ST_WIDTH`

`macro` | [progs/doomgeneric/st_stuff.h:31](../../progs/doomgeneric/st_stuff.h#L31)

```c
#define ST_WIDTH
```

---

<a id="st_y"></a>

### `ST_Y`

`macro` | [progs/doomgeneric/st_stuff.h:32](../../progs/doomgeneric/st_stuff.h#L32)

```c
#define ST_Y
```

---

## Variables

<a id="st_backing_screen"></a>

### `st_backing_screen`

`variable` `extern` | [progs/doomgeneric/st_stuff.h:76](../../progs/doomgeneric/st_stuff.h#L76)

```c
extern byte *st_backing_screen;
```

---

<a id="cheat_mus"></a>

### `cheat_mus`

`variable` `extern` | [progs/doomgeneric/st_stuff.h:77](../../progs/doomgeneric/st_stuff.h#L77)

```c
extern cheatseq_t cheat_mus;
```

---

<a id="cheat_god"></a>

### `cheat_god`

`variable` `extern` | [progs/doomgeneric/st_stuff.h:78](../../progs/doomgeneric/st_stuff.h#L78)

```c
extern cheatseq_t cheat_god;
```

---

<a id="cheat_ammo"></a>

### `cheat_ammo`

`variable` `extern` | [progs/doomgeneric/st_stuff.h:79](../../progs/doomgeneric/st_stuff.h#L79)

```c
extern cheatseq_t cheat_ammo;
```

---

<a id="cheat_ammonokey"></a>

### `cheat_ammonokey`

`variable` `extern` | [progs/doomgeneric/st_stuff.h:80](../../progs/doomgeneric/st_stuff.h#L80)

```c
extern cheatseq_t cheat_ammonokey;
```

---

<a id="cheat_noclip"></a>

### `cheat_noclip`

`variable` `extern` | [progs/doomgeneric/st_stuff.h:81](../../progs/doomgeneric/st_stuff.h#L81)

```c
extern cheatseq_t cheat_noclip;
```

---

<a id="cheat_commercial_noclip"></a>

### `cheat_commercial_noclip`

`variable` `extern` | [progs/doomgeneric/st_stuff.h:82](../../progs/doomgeneric/st_stuff.h#L82)

```c
extern cheatseq_t cheat_commercial_noclip;
```

---

<a id="cheat_powerup"></a>

### `cheat_powerup`

`variable` `extern` | [progs/doomgeneric/st_stuff.h:83](../../progs/doomgeneric/st_stuff.h#L83)

```c
extern cheatseq_t cheat_powerup[7];
```

---

<a id="cheat_choppers"></a>

### `cheat_choppers`

`variable` `extern` | [progs/doomgeneric/st_stuff.h:84](../../progs/doomgeneric/st_stuff.h#L84)

```c
extern cheatseq_t cheat_choppers;
```

---

<a id="cheat_clev"></a>

### `cheat_clev`

`variable` `extern` | [progs/doomgeneric/st_stuff.h:85](../../progs/doomgeneric/st_stuff.h#L85)

```c
extern cheatseq_t cheat_clev;
```

---

<a id="cheat_mypos"></a>

### `cheat_mypos`

`variable` `extern` | [progs/doomgeneric/st_stuff.h:86](../../progs/doomgeneric/st_stuff.h#L86)

```c
extern cheatseq_t cheat_mypos;
```

---
