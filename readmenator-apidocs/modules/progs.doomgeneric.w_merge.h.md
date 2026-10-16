# `progs/doomgeneric/w_merge.h`

> Source: [progs/doomgeneric/w_merge.h:1](../../progs/doomgeneric/w_merge.h#L1) | language `h` | coverage 14.3% | [API index](../index.md)

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Handles merging of PWADs, similar to deutex's -merge option  Ideally this should work exactly the same as in deutex, but trying to read the deutex source code made my brain hurt.     Add a new WAD and merge it into the main directory

## Contents

- **Functions:** [`W_MergeFile`](#w_mergefile), [`W_NWTMergeFile`](#w_nwtmergefile), [`W_NWTDashMerge`](#w_nwtdashmerge), [`W_PrintDirectory`](#w_printdirectory)
- **Macros:** [`W_NWT_MERGE_SPRITES`](#w_nwt_merge_sprites), [`W_NWT_MERGE_FLATS`](#w_nwt_merge_flats)

## Functions

<a id="w_mergefile"></a>

### `W_MergeFile`

`function` | [progs/doomgeneric/w_merge.h:29](../../progs/doomgeneric/w_merge.h#L29)

```c
void W_MergeFile(char *filename);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `filename` | `char *` |  |  |

*Called by:* [`W_ParseCommandLine`](progs.doomgeneric.w_main.c.md#w_parsecommandline)

---

<a id="w_nwtmergefile"></a>

### `W_NWTMergeFile`

`function` | [progs/doomgeneric/w_merge.h:33](../../progs/doomgeneric/w_merge.h#L33)

```c
void W_NWTMergeFile(char *filename, int flags);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `filename` | `char *` |  |  |
| `flags` | `int` |  |  |

*Called by:* [`W_ParseCommandLine`](progs.doomgeneric.w_main.c.md#w_parsecommandline)

---

<a id="w_nwtdashmerge"></a>

### `W_NWTDashMerge`

`function` | [progs/doomgeneric/w_merge.h:37](../../progs/doomgeneric/w_merge.h#L37)

```c
void W_NWTDashMerge(char *filename);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `filename` | `char *` |  |  |

*Called by:* [`W_ParseCommandLine`](progs.doomgeneric.w_main.c.md#w_parsecommandline)

---

<a id="w_printdirectory"></a>

### `W_PrintDirectory`

`function` | [progs/doomgeneric/w_merge.h:41](../../progs/doomgeneric/w_merge.h#L41)

```c
void W_PrintDirectory(void);
```

---

## Macros

<a id="w_nwt_merge_sprites"></a>

### `W_NWT_MERGE_SPRITES`

`macro` | [progs/doomgeneric/w_merge.h:24](../../progs/doomgeneric/w_merge.h#L24)

```c
#define W_NWT_MERGE_SPRITES
```

---

<a id="w_nwt_merge_flats"></a>

### `W_NWT_MERGE_FLATS`

`macro` | [progs/doomgeneric/w_merge.h:25](../../progs/doomgeneric/w_merge.h#L25)

```c
#define W_NWT_MERGE_FLATS
```

---
