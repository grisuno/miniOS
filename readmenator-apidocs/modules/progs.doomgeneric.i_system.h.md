# `progs/doomgeneric/i_system.h`

> Source: [progs/doomgeneric/i_system.h:1](../../progs/doomgeneric/i_system.h#L1) | language `h` | coverage 38.5% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: System specific interface stuff.

## Contents

- **Functions:** [`I_Init`](#i_init), [`I_ZoneBase`](#i_zonebase), [`I_BaseTiccmd`](#i_baseticcmd), [`I_Quit`](#i_quit), [`I_Error`](#i_error), [`I_Tactile`](#i_tactile), [`I_AtExit`](#i_atexit), [`I_BindVariables`](#i_bindvariables), [`I_PrintStartupBanner`](#i_printstartupbanner), [`I_PrintBanner`](#i_printbanner), [`I_PrintDivider`](#i_printdivider)
- **Macros:** [`__I_SYSTEM__`](#__i_system__)

## Functions

<a id="i_init"></a>

### `I_Init`

`function` | [progs/doomgeneric/i_system.h:30](../../progs/doomgeneric/i_system.h#L30)

```c
void I_Init (void);
```

Called by DoomMain.

---

<a id="i_zonebase"></a>

### `I_ZoneBase`

`function` | [progs/doomgeneric/i_system.h:35](../../progs/doomgeneric/i_system.h#L35)

```c
byte* I_ZoneBase (int *size);
```

Called by startup code to get the ammount of memory to malloc for the zone management.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `size` | `int *` |  |  |

**Returns:** `byte*`

*Called by:* [`Z_Init`](progs.doomgeneric.z_zone.c.md#z_init)

---

<a id="i_baseticcmd"></a>

### `I_BaseTiccmd`

`function` | [progs/doomgeneric/i_system.h:48](../../progs/doomgeneric/i_system.h#L48)

```c
ticcmd_t* I_BaseTiccmd (void);
```

Either returns a null ticcmd, or calls a loadable driver to build it.

This ticcmd will then be modified by the gameloop for normal input.

**Returns:** `ticcmd_t*`

---

<a id="i_quit"></a>

### `I_Quit`

`function` | [progs/doomgeneric/i_system.h:53](../../progs/doomgeneric/i_system.h#L53)

```c
void I_Quit (void);
```

Called by M_Responder when quit is selected.

Clean exit, displays sell blurb.

*Called by:* [`G_CheckDemoStatus`](progs.doomgeneric.g_game.c.md#g_checkdemostatus), [`M_QuitResponse`](progs.doomgeneric.m_menu.c.md#m_quitresponse), [`M_Responder`](progs.doomgeneric.m_menu.c.md#m_responder)

---

<a id="i_error"></a>

### `I_Error`

`function` | [progs/doomgeneric/i_system.h:55](../../progs/doomgeneric/i_system.h#L55)

```c
void I_Error (char *error, ...);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `error` | `char *` |  |  |
| `...` |  |  |  |

*Called by:* [`D_FindIWAD`](progs.doomgeneric.d_iwad.c.md#d_findiwad), [`D_InitNetGame`](progs.doomgeneric.d_loop.c.md#d_initnetgame), [`TryRunTics`](progs.doomgeneric.d_loop.c.md#tryruntics), [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain), [`D_IdentifyVersion`](progs.doomgeneric.d_main.c.md#d_identifyversion), [`G_CheckDemoStatus`](progs.doomgeneric.g_game.c.md#g_checkdemostatus), [`G_CheckSpot`](progs.doomgeneric.g_game.c.md#g_checkspot), [`G_DeathMatchSpawnPlayer`](progs.doomgeneric.g_game.c.md#g_deathmatchspawnplayer), [`G_DoLoadGame`](progs.doomgeneric.g_game.c.md#g_doloadgame), [`G_DoSaveGame`](progs.doomgeneric.g_game.c.md#g_dosavegame), [`G_Ticker`](progs.doomgeneric.g_game.c.md#g_ticker), [`G_VanillaVersionCode`](progs.doomgeneric.g_game.c.md#g_vanillaversioncode) and 68 more

---

<a id="i_tactile"></a>

### `I_Tactile`

`function` | [progs/doomgeneric/i_system.h:57](../../progs/doomgeneric/i_system.h#L57)

```c
void I_Tactile (int on, int off, int total);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `on` | `int` |  |  |
| `off` | `int` |  |  |
| `total` | `int` |  |  |

*Called by:* [`P_DamageMobj`](progs.doomgeneric.p_inter.c.md#p_damagemobj)

---

<a id="i_atexit"></a>

### `I_AtExit`

`function` | [progs/doomgeneric/i_system.h:65](../../progs/doomgeneric/i_system.h#L65)

```c
void I_AtExit(atexit_func_t func, boolean run_if_error);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `func` | `atexit_func_t` |  |  |
| `run_if_error` | `boolean` |  |  |

*Called by:* [`D_InitNetGame`](progs.doomgeneric.d_loop.c.md#d_initnetgame), [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain), [`I_InitJoystick`](progs.doomgeneric.i_joystick.c.md#i_initjoystick), [`S_Init`](progs.doomgeneric.s_sound.c.md#s_init)

---

<a id="i_bindvariables"></a>

### `I_BindVariables`

`function` | [progs/doomgeneric/i_system.h:69](../../progs/doomgeneric/i_system.h#L69)

```c
void I_BindVariables(void);
```

---

<a id="i_printstartupbanner"></a>

### `I_PrintStartupBanner`

`function` | [progs/doomgeneric/i_system.h:73](../../progs/doomgeneric/i_system.h#L73)

```c
void I_PrintStartupBanner(char *gamedescription);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `gamedescription` | `char *` |  |  |

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain)

---

<a id="i_printbanner"></a>

### `I_PrintBanner`

`function` | [progs/doomgeneric/i_system.h:77](../../progs/doomgeneric/i_system.h#L77)

```c
void I_PrintBanner(char *text);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `text` | `char *` |  |  |

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain)

---

<a id="i_printdivider"></a>

### `I_PrintDivider`

`function` | [progs/doomgeneric/i_system.h:81](../../progs/doomgeneric/i_system.h#L81)

```c
void I_PrintDivider(void);
```

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain)

---

## Macros

<a id="__i_system__"></a>

### `__I_SYSTEM__`

`macro` | [progs/doomgeneric/i_system.h:21](../../progs/doomgeneric/i_system.h#L21)

```c
#define __I_SYSTEM__
```

---
