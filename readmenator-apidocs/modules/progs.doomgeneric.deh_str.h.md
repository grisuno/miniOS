# `progs/doomgeneric/deh_str.h`

> Source: [progs/doomgeneric/deh_str.h:1](../../progs/doomgeneric/deh_str.h#L1) | language `h` | coverage 9.1% | [API index](../index.md)

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.   Dehacked string replacements      Used to do dehacked text substitutions throughout the program

## Contents

- **Functions:** [`DEH_String`](#deh_string), [`DEH_printf`](#deh_printf), [`DEH_fprintf`](#deh_fprintf), [`DEH_snprintf`](#deh_snprintf), [`DEH_AddStringReplacement`](#deh_addstringreplacement)
- **Macros:** [`DEH_String`](#deh_string), [`DEH_printf`](#deh_printf), [`DEH_fprintf`](#deh_fprintf), [`DEH_snprintf`](#deh_snprintf), [`DEH_AddStringReplacement`](#deh_addstringreplacement)

## Functions

<a id="deh_string"></a>

### `DEH_String`

`function` | [progs/doomgeneric/deh_str.h:29](../../progs/doomgeneric/deh_str.h#L29)

```c
char *DEH_String(char *s);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `s` | `char *` |  |  |

**Returns:** `char *`

*Called by:* [`AM_Responder`](progs.doomgeneric.am_map.c.md#am_responder), [`D_Display`](progs.doomgeneric.d_main.c.md#d_display), [`D_DoAdvanceDemo`](progs.doomgeneric.d_main.c.md#d_doadvancedemo), [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain), [`PrintDehackedBanners`](progs.doomgeneric.d_main.c.md#printdehackedbanners), [`F_BunnyScroll`](progs.doomgeneric.f_finale.c.md#f_bunnyscroll), [`F_CastDrawer`](progs.doomgeneric.f_finale.c.md#f_castdrawer), [`F_StartFinale`](progs.doomgeneric.f_finale.c.md#f_startfinale), [`G_DoLoadLevel`](progs.doomgeneric.g_game.c.md#g_doloadlevel), [`G_DoSaveGame`](progs.doomgeneric.g_game.c.md#g_dosavegame), [`G_InitNew`](progs.doomgeneric.g_game.c.md#g_initnew), [`G_Ticker`](progs.doomgeneric.g_game.c.md#g_ticker) and 45 more

---

<a id="deh_printf"></a>

### `DEH_printf`

`function` | [progs/doomgeneric/deh_str.h:30](../../progs/doomgeneric/deh_str.h#L30)

```c
void DEH_printf(char *fmt, ...);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fmt` | `char *` |  |  |
| `...` |  |  |  |

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain), [`D_CheckNetGame`](progs.doomgeneric.d_net.c.md#d_checknetgame)

---

<a id="deh_fprintf"></a>

### `DEH_fprintf`

`function` | [progs/doomgeneric/deh_str.h:31](../../progs/doomgeneric/deh_str.h#L31)

```c
void DEH_fprintf(FILE *fstream, char *fmt, ...);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fstream` | `FILE *` |  |  |
| `fmt` | `char *` |  |  |
| `...` |  |  |  |

*Called by:* [`AM_drawFline`](progs.doomgeneric.am_map.c.md#am_drawfline)

---

<a id="deh_snprintf"></a>

### `DEH_snprintf`

`function` | [progs/doomgeneric/deh_str.h:32](../../progs/doomgeneric/deh_str.h#L32)

```c
void DEH_snprintf(char *buffer, size_t len, char *fmt, ...);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `buffer` | `char *` |  |  |
| `len` | `size_t` |  |  |
| `fmt` | `char *` |  |  |
| `...` |  |  |  |

*Called by:* [`AM_loadPics`](progs.doomgeneric.am_map.c.md#am_loadpics), [`AM_unloadPics`](progs.doomgeneric.am_map.c.md#am_unloadpics), [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain), [`F_BunnyScroll`](progs.doomgeneric.f_finale.c.md#f_bunnyscroll), [`HU_Init`](progs.doomgeneric.hu_stuff.c.md#hu_init), [`M_QuickLoad`](progs.doomgeneric.m_menu.c.md#m_quickload), [`M_QuickSave`](progs.doomgeneric.m_menu.c.md#m_quicksave), [`M_QuitDOOM`](progs.doomgeneric.m_menu.c.md#m_quitdoom), [`P_SaveGameFile`](progs.doomgeneric.p_saveg.c.md#p_savegamefile), [`P_SetupLevel`](progs.doomgeneric.p_setup.c.md#p_setuplevel)

---

<a id="deh_addstringreplacement"></a>

### `DEH_AddStringReplacement`

`function` | [progs/doomgeneric/deh_str.h:33](../../progs/doomgeneric/deh_str.h#L33)

```c
void DEH_AddStringReplacement(char *from_text, char *to_text);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `from_text` | `char *` |  |  |
| `to_text` | `char *` |  |  |

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain)

---

## Macros

<a id="deh_string"></a>

### `DEH_String`

`macro` | [progs/doomgeneric/deh_str.h:38](../../progs/doomgeneric/deh_str.h#L38)

```c
#define DEH_String(x)
```

---

<a id="deh_printf"></a>

### `DEH_printf`

`macro` | [progs/doomgeneric/deh_str.h:39](../../progs/doomgeneric/deh_str.h#L39)

```c
#define DEH_printf
```

---

<a id="deh_fprintf"></a>

### `DEH_fprintf`

`macro` | [progs/doomgeneric/deh_str.h:40](../../progs/doomgeneric/deh_str.h#L40)

```c
#define DEH_fprintf
```

---

<a id="deh_snprintf"></a>

### `DEH_snprintf`

`macro` | [progs/doomgeneric/deh_str.h:41](../../progs/doomgeneric/deh_str.h#L41)

```c
#define DEH_snprintf
```

---

<a id="deh_addstringreplacement"></a>

### `DEH_AddStringReplacement`

`macro` | [progs/doomgeneric/deh_str.h:42](../../progs/doomgeneric/deh_str.h#L42)

```c
#define DEH_AddStringReplacement(x, y)
```

---
