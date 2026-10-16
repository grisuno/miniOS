# `progs/doomgeneric/m_misc.h`

> Source: [progs/doomgeneric/m_misc.h:1](../../progs/doomgeneric/m_misc.h#L1) | language `h` | coverage 6.7% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Miscellaneous.

## Contents

- **Functions:** [`M_ReadFile`](#m_readfile), [`M_MakeDirectory`](#m_makedirectory), [`M_TempFile`](#m_tempfile), [`M_FileLength`](#m_filelength), [`M_ExtractFileBase`](#m_extractfilebase), [`M_ForceUppercase`](#m_forceuppercase), [`M_StrCaseStr`](#m_strcasestr), [`M_StringDuplicate`](#m_stringduplicate), [`M_StringReplace`](#m_stringreplace), [`M_StringJoin`](#m_stringjoin), [`M_vsnprintf`](#m_vsnprintf), [`M_snprintf`](#m_snprintf), [`M_OEMToUTF8`](#m_oemtoutf8)
- **Macros:** [`__M_MISC__`](#__m_misc__)

## Functions

<a id="m_readfile"></a>

### `M_ReadFile`

`function` | [progs/doomgeneric/m_misc.h:29](../../progs/doomgeneric/m_misc.h#L29)

```c
int M_ReadFile(char *name, byte **buffer);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `name` | `char *` |  |  |
| `buffer` | `byte **` |  |  |

**Returns:** `int`

---

<a id="m_makedirectory"></a>

### `M_MakeDirectory`

`function` | [progs/doomgeneric/m_misc.h:30](../../progs/doomgeneric/m_misc.h#L30)

```c
void M_MakeDirectory(char *dir);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `dir` | `char *` |  |  |

*Called by:* [`M_GetSaveGameDir`](progs.doomgeneric.m_config.c.md#m_getsavegamedir), [`M_SetConfigDir`](progs.doomgeneric.m_config.c.md#m_setconfigdir)

---

<a id="m_tempfile"></a>

### `M_TempFile`

`function` | [progs/doomgeneric/m_misc.h:31](../../progs/doomgeneric/m_misc.h#L31)

```c
char *M_TempFile(char *s);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `s` | `char *` |  |  |

**Returns:** `char *`

*Called by:* [`G_DoSaveGame`](progs.doomgeneric.g_game.c.md#g_dosavegame)

---

<a id="m_filelength"></a>

### `M_FileLength`

`function` | [progs/doomgeneric/m_misc.h:33](../../progs/doomgeneric/m_misc.h#L33)

```c
long M_FileLength(FILE *handle);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `handle` | `FILE *` |  |  |

**Returns:** `long`

*Called by:* [`MAXARGVS`](progs.doomgeneric.m_argv.c.md#maxargvs)

---

<a id="m_extractfilebase"></a>

### `M_ExtractFileBase`

`function` | [progs/doomgeneric/m_misc.h:35](../../progs/doomgeneric/m_misc.h#L35)

```c
void M_ExtractFileBase(char *path, char *dest);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `path` | `char *` |  |  |
| `dest` | `char *` |  |  |

*Called by:* [`W_AddFile`](progs.doomgeneric.w_wad.c.md#w_addfile)

---

<a id="m_forceuppercase"></a>

### `M_ForceUppercase`

`function` | [progs/doomgeneric/m_misc.h:36](../../progs/doomgeneric/m_misc.h#L36)

```c
void M_ForceUppercase(char *text);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `text` | `char *` |  |  |

---

<a id="m_strcasestr"></a>

### `M_StrCaseStr`

`function` | [progs/doomgeneric/m_misc.h:37](../../progs/doomgeneric/m_misc.h#L37)

```c
char *M_StrCaseStr(char *haystack, char *needle);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `haystack` | `char *` |  |  |
| `needle` | `char *` |  |  |

**Returns:** `char *`

---

<a id="m_stringduplicate"></a>

### `M_StringDuplicate`

`function` | [progs/doomgeneric/m_misc.h:38](../../progs/doomgeneric/m_misc.h#L38)

```c
char *M_StringDuplicate(const char *orig);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `orig` | `char *` |  |  |

**Returns:** `char *`

---

<a id="m_stringreplace"></a>

### `M_StringReplace`

`function` | [progs/doomgeneric/m_misc.h:41](../../progs/doomgeneric/m_misc.h#L41)

```c
char *M_StringReplace(const char *haystack, const char *needle, const char *replacement);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `haystack` | `char *` |  |  |
| `needle` | `char *` |  |  |
| `replacement` | `char *` |  |  |

**Returns:** `char *`

---

<a id="m_stringjoin"></a>

### `M_StringJoin`

`function` | [progs/doomgeneric/m_misc.h:43](../../progs/doomgeneric/m_misc.h#L43)

```c
char *M_StringJoin(const char *s, ...);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `s` | `char *` |  |  |
| `...` |  |  |  |

**Returns:** `char *`

*Called by:* [`D_FindWADByName`](progs.doomgeneric.d_iwad.c.md#d_findwadbyname), [`M_GetSaveGameDir`](progs.doomgeneric.m_config.c.md#m_getsavegamedir), [`M_LoadDefaults`](progs.doomgeneric.m_config.c.md#m_loaddefaults), [`P_TempSaveGameFile`](progs.doomgeneric.p_saveg.c.md#p_tempsavegamefile)

---

<a id="m_vsnprintf"></a>

### `M_vsnprintf`

`function` | [progs/doomgeneric/m_misc.h:46](../../progs/doomgeneric/m_misc.h#L46)

```c
int M_vsnprintf(char *buf, size_t buf_len, const char *s, va_list args);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `buf` | `char *` |  |  |
| `buf_len` | `size_t` |  |  |
| `s` | `char *` |  |  |
| `args` | `va_list` |  |  |

**Returns:** `int`

*Called by:* [`I_Error`](progs.doomgeneric.i_system.c.md#i_error)

---

<a id="m_snprintf"></a>

### `M_snprintf`

`function` | [progs/doomgeneric/m_misc.h:47](../../progs/doomgeneric/m_misc.h#L47)

```c
int M_snprintf(char *buf, size_t buf_len, const char *s, ...);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `buf` | `char *` |  |  |
| `buf_len` | `size_t` |  |  |
| `s` | `char *` |  |  |
| `...` |  |  |  |

**Returns:** `int`

*Called by:* [`AM_Responder`](progs.doomgeneric.am_map.c.md#am_responder), [`D_BindVariables`](progs.doomgeneric.d_main.c.md#d_bindvariables), [`G_RecordDemo`](progs.doomgeneric.g_game.c.md#g_recorddemo), [`G_Ticker`](progs.doomgeneric.g_game.c.md#g_ticker), [`I_BindJoystickVariables`](progs.doomgeneric.i_joystick.c.md#i_bindjoystickvariables), [`M_BindChatControls`](progs.doomgeneric.m_controls.c.md#m_bindchatcontrols), [`P_ReadSaveGameHeader`](progs.doomgeneric.p_saveg.c.md#p_readsavegameheader), [`P_SaveGameFile`](progs.doomgeneric.p_saveg.c.md#p_savegamefile), [`P_WriteSaveGameHeader`](progs.doomgeneric.p_saveg.c.md#p_writesavegameheader), [`S_ChangeMusic`](progs.doomgeneric.s_sound.c.md#s_changemusic), [`ST_Responder`](progs.doomgeneric.st_stuff.c.md#st_responder), [`V_ScreenShot`](progs.doomgeneric.v_video.c.md#v_screenshot)

---

<a id="m_oemtoutf8"></a>

### `M_OEMToUTF8`

`function` | [progs/doomgeneric/m_misc.h:48](../../progs/doomgeneric/m_misc.h#L48)

```c
char *M_OEMToUTF8(const char *ansi);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ansi` | `char *` |  |  |

**Returns:** `char *`

---

## Macros

<a id="__m_misc__"></a>

### `__M_MISC__`

`macro` | [progs/doomgeneric/m_misc.h:21](../../progs/doomgeneric/m_misc.h#L21)

```c
#define __M_MISC__
```

---
