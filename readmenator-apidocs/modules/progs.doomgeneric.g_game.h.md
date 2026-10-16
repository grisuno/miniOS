# `progs/doomgeneric/g_game.h`

> Source: [progs/doomgeneric/g_game.h:1](../../progs/doomgeneric/g_game.h#L1) | language `h` | coverage 28.6% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Duh.        GAME

## Contents

- **Functions:** [`G_DeathMatchSpawnPlayer`](#g_deathmatchspawnplayer), [`G_InitNew`](#g_initnew), [`G_DeferedInitNew`](#g_deferedinitnew), [`G_DeferedPlayDemo`](#g_deferedplaydemo), [`G_LoadGame`](#g_loadgame), [`G_DoLoadGame`](#g_doloadgame), [`G_SaveGame`](#g_savegame), [`G_RecordDemo`](#g_recorddemo), [`G_BeginRecording`](#g_beginrecording), [`G_PlayDemo`](#g_playdemo), [`G_TimeDemo`](#g_timedemo), [`G_ExitLevel`](#g_exitlevel), [`G_SecretExitLevel`](#g_secretexitlevel), [`G_WorldDone`](#g_worlddone), [`G_BuildTiccmd`](#g_buildticcmd), [`G_Ticker`](#g_ticker), [`G_ScreenShot`](#g_screenshot), [`G_DrawMouseSpeedBox`](#g_drawmousespeedbox), [`G_VanillaVersionCode`](#g_vanillaversioncode)
- **Macros:** [`__G_GAME__`](#__g_game__)
- **Variables:** [`vanilla_savegame_limit`](#vanilla_savegame_limit), [`vanilla_demo_limit`](#vanilla_demo_limit)

## Functions

<a id="g_deathmatchspawnplayer"></a>

### `G_DeathMatchSpawnPlayer`

`function` | [progs/doomgeneric/g_game.h:31](../../progs/doomgeneric/g_game.h#L31)

```c
void G_DeathMatchSpawnPlayer (int playernum);
```

GAME

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `playernum` | `int` |  |  |

*Called by:* [`P_SetupLevel`](progs.doomgeneric.p_setup.c.md#p_setuplevel)

---

<a id="g_initnew"></a>

### `G_InitNew`

`function` | [progs/doomgeneric/g_game.h:33](../../progs/doomgeneric/g_game.h#L33)

```c
void G_InitNew (skill_t skill, int episode, int map);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `skill` | `skill_t` |  |  |
| `episode` | `int` |  |  |
| `map` | `int` |  |  |

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain)

---

<a id="g_deferedinitnew"></a>

### `G_DeferedInitNew`

`function` | [progs/doomgeneric/g_game.h:38](../../progs/doomgeneric/g_game.h#L38)

```c
void G_DeferedInitNew (skill_t skill, int episode, int map);
```

Can be called by the startup code or M_Responder.

A normal game starts at map 1, but a warp test can start elsewhere

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `skill` | `skill_t` |  |  |
| `episode` | `int` |  |  |
| `map` | `int` |  |  |

*Called by:* [`M_ChooseSkill`](progs.doomgeneric.m_menu.c.md#m_chooseskill), [`M_VerifyNightmare`](progs.doomgeneric.m_menu.c.md#m_verifynightmare), [`ST_Responder`](progs.doomgeneric.st_stuff.c.md#st_responder)

---

<a id="g_deferedplaydemo"></a>

### `G_DeferedPlayDemo`

`function` | [progs/doomgeneric/g_game.h:40](../../progs/doomgeneric/g_game.h#L40)

```c
void G_DeferedPlayDemo (char* demo);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `demo` | `char*` |  |  |

*Called by:* [`D_DoAdvanceDemo`](progs.doomgeneric.d_main.c.md#d_doadvancedemo), [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain)

---

<a id="g_loadgame"></a>

### `G_LoadGame`

`function` | [progs/doomgeneric/g_game.h:44](../../progs/doomgeneric/g_game.h#L44)

```c
void G_LoadGame (char* name);
```

Can be called by the startup code or M_Responder, calls P_SetupLevel or W_EnterWorld.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `name` | `char*` |  |  |

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain), [`M_LoadSelect`](progs.doomgeneric.m_menu.c.md#m_loadselect)

---

<a id="g_doloadgame"></a>

### `G_DoLoadGame`

`function` | [progs/doomgeneric/g_game.h:46](../../progs/doomgeneric/g_game.h#L46)

```c
void G_DoLoadGame (void);
```

---

<a id="g_savegame"></a>

### `G_SaveGame`

`function` | [progs/doomgeneric/g_game.h:49](../../progs/doomgeneric/g_game.h#L49)

```c
void G_SaveGame (int slot, char* description);
```

Called by M_Responder.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `slot` | `int` |  |  |
| `description` | `char*` |  |  |

*Called by:* [`M_DoSave`](progs.doomgeneric.m_menu.c.md#m_dosave)

---

<a id="g_recorddemo"></a>

### `G_RecordDemo`

`function` | [progs/doomgeneric/g_game.h:52](../../progs/doomgeneric/g_game.h#L52)

```c
void G_RecordDemo (char* name);
```

Only called by startup code.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `name` | `char*` |  |  |

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain)

---

<a id="g_beginrecording"></a>

### `G_BeginRecording`

`function` | [progs/doomgeneric/g_game.h:54](../../progs/doomgeneric/g_game.h#L54)

```c
void G_BeginRecording (void);
```

*Called by:* [`D_DoomLoop`](progs.doomgeneric.d_main.c.md#d_doomloop)

---

<a id="g_playdemo"></a>

### `G_PlayDemo`

`function` | [progs/doomgeneric/g_game.h:56](../../progs/doomgeneric/g_game.h#L56)

```c
void G_PlayDemo (char* name);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `name` | `char*` |  |  |

---

<a id="g_timedemo"></a>

### `G_TimeDemo`

`function` | [progs/doomgeneric/g_game.h:57](../../progs/doomgeneric/g_game.h#L57)

```c
void G_TimeDemo (char* name);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `name` | `char*` |  |  |

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain)

---

<a id="g_exitlevel"></a>

### `G_ExitLevel`

`function` | [progs/doomgeneric/g_game.h:60](../../progs/doomgeneric/g_game.h#L60)

```c
void G_ExitLevel (void);
```

*Called by:* [`A_BossDeath`](progs.doomgeneric.p_enemy.c.md#a_bossdeath), [`A_BrainDie`](progs.doomgeneric.p_enemy.c.md#a_braindie), [`P_UseSpecialLine`](progs.doomgeneric.p_switch.c.md#p_usespecialline)

---

<a id="g_secretexitlevel"></a>

### `G_SecretExitLevel`

`function` | [progs/doomgeneric/g_game.h:61](../../progs/doomgeneric/g_game.h#L61)

```c
void G_SecretExitLevel (void);
```

*Called by:* [`P_UseSpecialLine`](progs.doomgeneric.p_switch.c.md#p_usespecialline)

---

<a id="g_worlddone"></a>

### `G_WorldDone`

`function` | [progs/doomgeneric/g_game.h:63](../../progs/doomgeneric/g_game.h#L63)

```c
void G_WorldDone (void);
```

*Called by:* [`WI_updateNoState`](progs.doomgeneric.wi_stuff.c.md#wi_updatenostate)

---

<a id="g_buildticcmd"></a>

### `G_BuildTiccmd`

`function` | [progs/doomgeneric/g_game.h:67](../../progs/doomgeneric/g_game.h#L67)

```c
void G_BuildTiccmd (ticcmd_t *cmd, int maketic);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `cmd` | `ticcmd_t *` |  |  |
| `maketic` | `int` |  |  |

---

<a id="g_ticker"></a>

### `G_Ticker`

`function` | [progs/doomgeneric/g_game.h:69](../../progs/doomgeneric/g_game.h#L69)

```c
void G_Ticker (void);
```

---

<a id="g_screenshot"></a>

### `G_ScreenShot`

`function` | [progs/doomgeneric/g_game.h:72](../../progs/doomgeneric/g_game.h#L72)

```c
void G_ScreenShot (void);
```

*Called by:* [`M_Responder`](progs.doomgeneric.m_menu.c.md#m_responder)

---

<a id="g_drawmousespeedbox"></a>

### `G_DrawMouseSpeedBox`

`function` | [progs/doomgeneric/g_game.h:74](../../progs/doomgeneric/g_game.h#L74)

```c
void G_DrawMouseSpeedBox(void);
```

---

<a id="g_vanillaversioncode"></a>

### `G_VanillaVersionCode`

`function` | [progs/doomgeneric/g_game.h:75](../../progs/doomgeneric/g_game.h#L75)

```c
int G_VanillaVersionCode(void);
```

**Returns:** `int`

*Called by:* [`P_ReadSaveGameHeader`](progs.doomgeneric.p_saveg.c.md#p_readsavegameheader), [`P_WriteSaveGameHeader`](progs.doomgeneric.p_saveg.c.md#p_writesavegameheader)

---

## Macros

<a id="__g_game__"></a>

### `__G_GAME__`

`macro` | [progs/doomgeneric/g_game.h:21](../../progs/doomgeneric/g_game.h#L21)

```c
#define __G_GAME__
```

---

## Variables

<a id="vanilla_savegame_limit"></a>

### `vanilla_savegame_limit`

`variable` `extern` | [progs/doomgeneric/g_game.h:77](../../progs/doomgeneric/g_game.h#L77)

```c
extern int vanilla_savegame_limit;
```

---

<a id="vanilla_demo_limit"></a>

### `vanilla_demo_limit`

`variable` `extern` | [progs/doomgeneric/g_game.h:78](../../progs/doomgeneric/g_game.h#L78)

```c
extern int vanilla_demo_limit;
```

---
