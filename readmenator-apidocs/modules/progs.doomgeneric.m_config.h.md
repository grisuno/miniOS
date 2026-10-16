# `progs/doomgeneric/m_config.h`

> Source: [progs/doomgeneric/m_config.h:1](../../progs/doomgeneric/m_config.h#L1) | language `h` | coverage 8.3% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Configuration file interface.

## Contents

- **Functions:** [`M_LoadDefaults`](#m_loaddefaults), [`M_SaveDefaults`](#m_savedefaults), [`M_SaveDefaultsAlternate`](#m_savedefaultsalternate), [`M_SetConfigDir`](#m_setconfigdir), [`M_BindVariable`](#m_bindvariable), [`M_GetIntVariable`](#m_getintvariable), [`M_GetStrVariable`](#m_getstrvariable), [`M_GetFloatVariable`](#m_getfloatvariable), [`M_SetConfigFilenames`](#m_setconfigfilenames), [`M_GetSaveGameDir`](#m_getsavegamedir)
- **Macros:** [`__M_CONFIG__`](#__m_config__)
- **Variables:** [`configdir`](#configdir)

## Functions

<a id="m_loaddefaults"></a>

### `M_LoadDefaults`

`function` | [progs/doomgeneric/m_config.h:25](../../progs/doomgeneric/m_config.h#L25)

```c
void M_LoadDefaults(void);
```

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain)

---

<a id="m_savedefaults"></a>

### `M_SaveDefaults`

`function` | [progs/doomgeneric/m_config.h:26](../../progs/doomgeneric/m_config.h#L26)

```c
void M_SaveDefaults(void);
```

---

<a id="m_savedefaultsalternate"></a>

### `M_SaveDefaultsAlternate`

`function` | [progs/doomgeneric/m_config.h:27](../../progs/doomgeneric/m_config.h#L27)

```c
void M_SaveDefaultsAlternate(char *main, char *extra);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `main` | `char *` |  |  |
| `extra` | `char *` |  |  |

---

<a id="m_setconfigdir"></a>

### `M_SetConfigDir`

`function` | [progs/doomgeneric/m_config.h:28](../../progs/doomgeneric/m_config.h#L28)

```c
void M_SetConfigDir(char *dir);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `dir` | `char *` |  |  |

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain)

---

<a id="m_bindvariable"></a>

### `M_BindVariable`

`function` | [progs/doomgeneric/m_config.h:29](../../progs/doomgeneric/m_config.h#L29)

```c
void M_BindVariable(char *name, void *variable);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `name` | `char *` |  |  |
| `variable` | `void *` |  |  |

*Called by:* [`D_BindVariables`](progs.doomgeneric.d_main.c.md#d_bindvariables), [`I_BindJoystickVariables`](progs.doomgeneric.i_joystick.c.md#i_bindjoystickvariables), [`I_BindSoundVariables`](progs.doomgeneric.i_sound.c.md#i_bindsoundvariables), [`M_BindBaseControls`](progs.doomgeneric.m_controls.c.md#m_bindbasecontrols), [`M_BindChatControls`](progs.doomgeneric.m_controls.c.md#m_bindchatcontrols), [`M_BindHereticControls`](progs.doomgeneric.m_controls.c.md#m_bindhereticcontrols), [`M_BindHexenControls`](progs.doomgeneric.m_controls.c.md#m_bindhexencontrols), [`M_BindMapControls`](progs.doomgeneric.m_controls.c.md#m_bindmapcontrols), [`M_BindMenuControls`](progs.doomgeneric.m_controls.c.md#m_bindmenucontrols), [`M_BindStrifeControls`](progs.doomgeneric.m_controls.c.md#m_bindstrifecontrols), [`M_BindWeaponControls`](progs.doomgeneric.m_controls.c.md#m_bindweaponcontrols)

---

<a id="m_getintvariable"></a>

### `M_GetIntVariable`

`function` | [progs/doomgeneric/m_config.h:31](../../progs/doomgeneric/m_config.h#L31)

```c
int M_GetIntVariable(char *name);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `name` | `char *` |  |  |

**Returns:** `int`

---

<a id="m_getstrvariable"></a>

### `M_GetStrVariable`

`function` `const` | [progs/doomgeneric/m_config.h:32](../../progs/doomgeneric/m_config.h#L32)

```c
const char *M_GetStrVariable(char *name);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `name` | `char *` |  |  |

**Returns:** `char *`

---

<a id="m_getfloatvariable"></a>

### `M_GetFloatVariable`

`function` | [progs/doomgeneric/m_config.h:33](../../progs/doomgeneric/m_config.h#L33)

```c
float M_GetFloatVariable(char *name);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `name` | `char *` |  |  |

**Returns:** `float`

---

<a id="m_setconfigfilenames"></a>

### `M_SetConfigFilenames`

`function` | [progs/doomgeneric/m_config.h:34](../../progs/doomgeneric/m_config.h#L34)

```c
void M_SetConfigFilenames(char *main_config, char *extra_config);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `main_config` | `char *` |  |  |
| `extra_config` | `char *` |  |  |

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain)

---

<a id="m_getsavegamedir"></a>

### `M_GetSaveGameDir`

`function` | [progs/doomgeneric/m_config.h:35](../../progs/doomgeneric/m_config.h#L35)

```c
char *M_GetSaveGameDir(char *iwadname);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `iwadname` | `char *` |  |  |

**Returns:** `char *`

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain)

---

## Macros

<a id="__m_config__"></a>

### `__M_CONFIG__`

`macro` | [progs/doomgeneric/m_config.h:21](../../progs/doomgeneric/m_config.h#L21)

```c
#define __M_CONFIG__
```

---

## Variables

<a id="configdir"></a>

### `configdir`

`variable` `extern` | [progs/doomgeneric/m_config.h:37](../../progs/doomgeneric/m_config.h#L37)

```c
extern char *configdir;
```

---
