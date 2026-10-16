# `progs/doomgeneric/hu_stuff.h`

> Source: [progs/doomgeneric/hu_stuff.h:1](../../progs/doomgeneric/hu_stuff.h#L1) | language `h` | coverage 18.8% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION:  Head up display       Globally visible constants.   Calculate # of glyphs in font.

## Contents

- **Functions:** [`HU_Init`](#hu_init), [`HU_Start`](#hu_start), [`HU_Ticker`](#hu_ticker), [`HU_Drawer`](#hu_drawer), [`HU_dequeueChatChar`](#hu_dequeuechatchar), [`HU_Erase`](#hu_erase)
- **Macros:** [`HU_FONTSTART`](#hu_fontstart), [`HU_FONTEND`](#hu_fontend), [`HU_FONTSIZE`](#hu_fontsize), [`HU_BROADCAST`](#hu_broadcast), [`HU_MSGX`](#hu_msgx), [`HU_MSGY`](#hu_msgy), [`HU_MSGWIDTH`](#hu_msgwidth), [`HU_MSGHEIGHT`](#hu_msgheight), [`HU_MSGTIMEOUT`](#hu_msgtimeout)
- **Variables:** [`chat_macros`](#chat_macros)

## Functions

<a id="hu_init"></a>

### `HU_Init`

`function` | [progs/doomgeneric/hu_stuff.h:46](../../progs/doomgeneric/hu_stuff.h#L46)

```c
void HU_Init(void);
```

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain)

---

<a id="hu_start"></a>

### `HU_Start`

`function` | [progs/doomgeneric/hu_stuff.h:47](../../progs/doomgeneric/hu_stuff.h#L47)

```c
void HU_Start(void);
```

*Called by:* [`P_SpawnPlayer`](progs.doomgeneric.p_mobj.c.md#p_spawnplayer)

---

<a id="hu_ticker"></a>

### `HU_Ticker`

`function` | [progs/doomgeneric/hu_stuff.h:51](../../progs/doomgeneric/hu_stuff.h#L51)

```c
void HU_Ticker(void);
```

*Called by:* [`G_Ticker`](progs.doomgeneric.g_game.c.md#g_ticker)

---

<a id="hu_drawer"></a>

### `HU_Drawer`

`function` | [progs/doomgeneric/hu_stuff.h:52](../../progs/doomgeneric/hu_stuff.h#L52)

```c
void HU_Drawer(void);
```

*Called by:* [`D_Display`](progs.doomgeneric.d_main.c.md#d_display)

---

<a id="hu_dequeuechatchar"></a>

### `HU_dequeueChatChar`

`function` | [progs/doomgeneric/hu_stuff.h:53](../../progs/doomgeneric/hu_stuff.h#L53)

```c
char HU_dequeueChatChar(void);
```

**Returns:** `char`

*Called by:* [`G_BuildTiccmd`](progs.doomgeneric.g_game.c.md#g_buildticcmd)

---

<a id="hu_erase"></a>

### `HU_Erase`

`function` | [progs/doomgeneric/hu_stuff.h:54](../../progs/doomgeneric/hu_stuff.h#L54)

```c
void HU_Erase(void);
```

*Called by:* [`D_Display`](progs.doomgeneric.d_main.c.md#d_display)

---

## Macros

<a id="hu_fontstart"></a>

### `HU_FONTSTART`

`macro` | [progs/doomgeneric/hu_stuff.h:27](../../progs/doomgeneric/hu_stuff.h#L27)

```c
#define HU_FONTSTART
```

Globally visible constants.

---

<a id="hu_fontend"></a>

### `HU_FONTEND`

`macro` | [progs/doomgeneric/hu_stuff.h:28](../../progs/doomgeneric/hu_stuff.h#L28)

```c
#define HU_FONTEND
```

---

<a id="hu_fontsize"></a>

### `HU_FONTSIZE`

`macro` | [progs/doomgeneric/hu_stuff.h:31](../../progs/doomgeneric/hu_stuff.h#L31)

```c
#define HU_FONTSIZE
```

Calculate # of glyphs in font.

---

<a id="hu_broadcast"></a>

### `HU_BROADCAST`

`macro` | [progs/doomgeneric/hu_stuff.h:33](../../progs/doomgeneric/hu_stuff.h#L33)

```c
#define HU_BROADCAST
```

---

<a id="hu_msgx"></a>

### `HU_MSGX`

`macro` | [progs/doomgeneric/hu_stuff.h:35](../../progs/doomgeneric/hu_stuff.h#L35)

```c
#define HU_MSGX
```

---

<a id="hu_msgy"></a>

### `HU_MSGY`

`macro` | [progs/doomgeneric/hu_stuff.h:36](../../progs/doomgeneric/hu_stuff.h#L36)

```c
#define HU_MSGY
```

---

<a id="hu_msgwidth"></a>

### `HU_MSGWIDTH`

`macro` | [progs/doomgeneric/hu_stuff.h:37](../../progs/doomgeneric/hu_stuff.h#L37)

```c
#define HU_MSGWIDTH
```

---

<a id="hu_msgheight"></a>

### `HU_MSGHEIGHT`

`macro` | [progs/doomgeneric/hu_stuff.h:38](../../progs/doomgeneric/hu_stuff.h#L38)

```c
#define HU_MSGHEIGHT
```

---

<a id="hu_msgtimeout"></a>

### `HU_MSGTIMEOUT`

`macro` | [progs/doomgeneric/hu_stuff.h:40](../../progs/doomgeneric/hu_stuff.h#L40)

```c
#define HU_MSGTIMEOUT
```

---

## Variables

<a id="chat_macros"></a>

### `chat_macros`

`variable` `extern` | [progs/doomgeneric/hu_stuff.h:56](../../progs/doomgeneric/hu_stuff.h#L56)

```c
extern char *chat_macros[10];
```

---
