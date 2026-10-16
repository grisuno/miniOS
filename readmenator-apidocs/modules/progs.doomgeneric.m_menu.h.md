# `progs/doomgeneric/m_menu.h`

> Source: [progs/doomgeneric/m_menu.h:1](../../progs/doomgeneric/m_menu.h#L1) | language `h` | coverage 83.3% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Menu widget stuff, episode selection and such.         MENUS  Called by main loop,

## Contents

- **Functions:** [`M_Ticker`](#m_ticker), [`M_Drawer`](#m_drawer), [`M_Init`](#m_init), [`M_StartControlPanel`](#m_startcontrolpanel)
- **Macros:** [`__M_MENU__`](#__m_menu__)
- **Variables:** [`detailLevel`](#detaillevel), [`screenblocks`](#screenblocks)

## Functions

<a id="m_ticker"></a>

### `M_Ticker`

`function` | [progs/doomgeneric/m_menu.h:40](../../progs/doomgeneric/m_menu.h#L40)

```c
void M_Ticker (void);
```

Called by main loop, only used for menu (skull cursor) animation.

---

<a id="m_drawer"></a>

### `M_Drawer`

`function` | [progs/doomgeneric/m_menu.h:44](../../progs/doomgeneric/m_menu.h#L44)

```c
void M_Drawer (void);
```

Called by main loop, draws the menus directly into the screen buffer.

*Called by:* [`D_Display`](progs.doomgeneric.d_main.c.md#d_display)

---

<a id="m_init"></a>

### `M_Init`

`function` | [progs/doomgeneric/m_menu.h:48](../../progs/doomgeneric/m_menu.h#L48)

```c
void M_Init (void);
```

Called by D_DoomMain, loads the config file.

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain)

---

<a id="m_startcontrolpanel"></a>

### `M_StartControlPanel`

`function` | [progs/doomgeneric/m_menu.h:52](../../progs/doomgeneric/m_menu.h#L52)

```c
void M_StartControlPanel (void);
```

Called by intro code to force menu up upon a keypress, does nothing if menu is already up.

*Called by:* [`G_Responder`](progs.doomgeneric.g_game.c.md#g_responder)

---

## Macros

<a id="__m_menu__"></a>

### `__M_MENU__`

`macro` | [progs/doomgeneric/m_menu.h:21](../../progs/doomgeneric/m_menu.h#L21)

```c
#define __M_MENU__
```

---

## Variables

<a id="detaillevel"></a>

### `detailLevel`

`variable` `extern` | [progs/doomgeneric/m_menu.h:56](../../progs/doomgeneric/m_menu.h#L56)

```c
extern int detailLevel;
```

---

<a id="screenblocks"></a>

### `screenblocks`

`variable` `extern` | [progs/doomgeneric/m_menu.h:57](../../progs/doomgeneric/m_menu.h#L57)

```c
extern int screenblocks;
```

---
