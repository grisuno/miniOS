# `progs/doomgeneric/p_saveg.h`

> Source: [progs/doomgeneric/p_saveg.h:1](../../progs/doomgeneric/p_saveg.h#L1) | language `h` | coverage 13.3% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Savegame I/O, archiving, persistence.      maximum size of a savegame description   temporary filename to use while saving.

## Contents

- **Functions:** [`P_TempSaveGameFile`](#p_tempsavegamefile), [`P_SaveGameFile`](#p_savegamefile), [`P_WriteSaveGameHeader`](#p_writesavegameheader), [`P_WriteSaveGameEOF`](#p_writesavegameeof), [`P_ArchivePlayers`](#p_archiveplayers), [`P_UnArchivePlayers`](#p_unarchiveplayers), [`P_ArchiveWorld`](#p_archiveworld), [`P_UnArchiveWorld`](#p_unarchiveworld), [`P_ArchiveThinkers`](#p_archivethinkers), [`P_UnArchiveThinkers`](#p_unarchivethinkers), [`P_ArchiveSpecials`](#p_archivespecials), [`P_UnArchiveSpecials`](#p_unarchivespecials)
- **Macros:** [`__P_SAVEG__`](#__p_saveg__), [`SAVESTRINGSIZE`](#savestringsize)
- **Variables:** [`save_stream`](#save_stream), [`savegame_error`](#savegame_error)

## Functions

<a id="p_tempsavegamefile"></a>

### `P_TempSaveGameFile`

`function` | [progs/doomgeneric/p_saveg.h:31](../../progs/doomgeneric/p_saveg.h#L31)

```c
char *P_TempSaveGameFile(void);
```

**Returns:** `char *`

*Called by:* [`G_DoSaveGame`](progs.doomgeneric.g_game.c.md#g_dosavegame)

---

<a id="p_savegamefile"></a>

### `P_SaveGameFile`

`function` | [progs/doomgeneric/p_saveg.h:35](../../progs/doomgeneric/p_saveg.h#L35)

```c
char *P_SaveGameFile(int slot);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `slot` | `int` |  |  |

**Returns:** `char *`

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain), [`G_DoSaveGame`](progs.doomgeneric.g_game.c.md#g_dosavegame), [`M_LoadSelect`](progs.doomgeneric.m_menu.c.md#m_loadselect), [`M_ReadSaveStrings`](progs.doomgeneric.m_menu.c.md#m_readsavestrings)

---

<a id="p_writesavegameheader"></a>

### `P_WriteSaveGameHeader`

`function` | [progs/doomgeneric/p_saveg.h:40](../../progs/doomgeneric/p_saveg.h#L40)

```c
void P_WriteSaveGameHeader(char *description);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `description` | `char *` |  |  |

*Called by:* [`G_DoSaveGame`](progs.doomgeneric.g_game.c.md#g_dosavegame)

---

<a id="p_writesavegameeof"></a>

### `P_WriteSaveGameEOF`

`function` | [progs/doomgeneric/p_saveg.h:45](../../progs/doomgeneric/p_saveg.h#L45)

```c
void P_WriteSaveGameEOF(void);
```

*Called by:* [`G_DoSaveGame`](progs.doomgeneric.g_game.c.md#g_dosavegame)

---

<a id="p_archiveplayers"></a>

### `P_ArchivePlayers`

`function` | [progs/doomgeneric/p_saveg.h:49](../../progs/doomgeneric/p_saveg.h#L49)

```c
void P_ArchivePlayers (void);
```

Persistent storage/archiving.

These are the load / save game routines.

*Called by:* [`G_DoSaveGame`](progs.doomgeneric.g_game.c.md#g_dosavegame)

---

<a id="p_unarchiveplayers"></a>

### `P_UnArchivePlayers`

`function` | [progs/doomgeneric/p_saveg.h:50](../../progs/doomgeneric/p_saveg.h#L50)

```c
void P_UnArchivePlayers (void);
```

*Called by:* [`G_DoLoadGame`](progs.doomgeneric.g_game.c.md#g_doloadgame)

---

<a id="p_archiveworld"></a>

### `P_ArchiveWorld`

`function` | [progs/doomgeneric/p_saveg.h:51](../../progs/doomgeneric/p_saveg.h#L51)

```c
void P_ArchiveWorld (void);
```

*Called by:* [`G_DoSaveGame`](progs.doomgeneric.g_game.c.md#g_dosavegame)

---

<a id="p_unarchiveworld"></a>

### `P_UnArchiveWorld`

`function` | [progs/doomgeneric/p_saveg.h:52](../../progs/doomgeneric/p_saveg.h#L52)

```c
void P_UnArchiveWorld (void);
```

*Called by:* [`G_DoLoadGame`](progs.doomgeneric.g_game.c.md#g_doloadgame)

---

<a id="p_archivethinkers"></a>

### `P_ArchiveThinkers`

`function` | [progs/doomgeneric/p_saveg.h:53](../../progs/doomgeneric/p_saveg.h#L53)

```c
void P_ArchiveThinkers (void);
```

*Called by:* [`G_DoSaveGame`](progs.doomgeneric.g_game.c.md#g_dosavegame)

---

<a id="p_unarchivethinkers"></a>

### `P_UnArchiveThinkers`

`function` | [progs/doomgeneric/p_saveg.h:54](../../progs/doomgeneric/p_saveg.h#L54)

```c
void P_UnArchiveThinkers (void);
```

*Called by:* [`G_DoLoadGame`](progs.doomgeneric.g_game.c.md#g_doloadgame)

---

<a id="p_archivespecials"></a>

### `P_ArchiveSpecials`

`function` | [progs/doomgeneric/p_saveg.h:55](../../progs/doomgeneric/p_saveg.h#L55)

```c
void P_ArchiveSpecials (void);
```

*Called by:* [`G_DoSaveGame`](progs.doomgeneric.g_game.c.md#g_dosavegame)

---

<a id="p_unarchivespecials"></a>

### `P_UnArchiveSpecials`

`function` | [progs/doomgeneric/p_saveg.h:56](../../progs/doomgeneric/p_saveg.h#L56)

```c
void P_UnArchiveSpecials (void);
```

*Called by:* [`G_DoLoadGame`](progs.doomgeneric.g_game.c.md#g_doloadgame)

---

## Macros

<a id="__p_saveg__"></a>

### `__P_SAVEG__`

`macro` | [progs/doomgeneric/p_saveg.h:21](../../progs/doomgeneric/p_saveg.h#L21)

```c
#define __P_SAVEG__
```

---

<a id="savestringsize"></a>

### `SAVESTRINGSIZE`

`macro` | [progs/doomgeneric/p_saveg.h:27](../../progs/doomgeneric/p_saveg.h#L27)

```c
#define SAVESTRINGSIZE
```

---

## Variables

<a id="save_stream"></a>

### `save_stream`

`variable` `extern` | [progs/doomgeneric/p_saveg.h:58](../../progs/doomgeneric/p_saveg.h#L58)

```c
extern FILE *save_stream;
```

---

<a id="savegame_error"></a>

### `savegame_error`

`variable` `extern` | [progs/doomgeneric/p_saveg.h:59](../../progs/doomgeneric/p_saveg.h#L59)

```c
extern boolean savegame_error;
```

---
