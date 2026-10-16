# `progs/doomgeneric/z_zone.h`

> Source: [progs/doomgeneric/z_zone.h:1](../../progs/doomgeneric/z_zone.h#L1) | language `h` | coverage 14.3% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Zone Memory Allocation, perhaps NeXT ObjectiveC inspired. Remark: this was the only stuff that, according to John Carmack, might have been useful for Quake.        ZONE MEMORY

## Contents

- **Functions:** [`Z_Init`](#z_init), [`Z_Malloc`](#z_malloc), [`Z_Free`](#z_free), [`Z_FreeTags`](#z_freetags), [`Z_DumpHeap`](#z_dumpheap), [`Z_FileDumpHeap`](#z_filedumpheap), [`Z_CheckHeap`](#z_checkheap), [`Z_ChangeTag2`](#z_changetag2), [`Z_ChangeUser`](#z_changeuser), [`Z_FreeMemory`](#z_freememory), [`Z_ZoneSize`](#z_zonesize)
- **Macros:** [`__Z_ZONE__`](#__z_zone__), [`Z_ChangeTag`](#z_changetag)

## Functions

<a id="z_init"></a>

### `Z_Init`

`function` | [progs/doomgeneric/z_zone.h:53](../../progs/doomgeneric/z_zone.h#L53)

```c
void Z_Init (void);
```

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain)

---

<a id="z_malloc"></a>

### `Z_Malloc`

`function` | [progs/doomgeneric/z_zone.h:54](../../progs/doomgeneric/z_zone.h#L54)

```c
void* Z_Malloc (int size, int tag, void *ptr);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `size` | `int` |  |  |
| `tag` | `int` |  |  |
| `ptr` | `void *` |  |  |

**Returns:** `void*`

*Called by:* [`wipe_EndScreen`](progs.doomgeneric.f_wipe.c.md#wipe_endscreen), [`wipe_StartScreen`](progs.doomgeneric.f_wipe.c.md#wipe_startscreen), [`wipe_initMelt`](progs.doomgeneric.f_wipe.c.md#wipe_initmelt), [`wipe_shittyColMajorXform`](progs.doomgeneric.f_wipe.c.md#wipe_shittycolmajorxform), [`G_RecordDemo`](progs.doomgeneric.g_game.c.md#g_recorddemo), [`I_InitGraphics`](progs.doomgeneric.i_video.c.md#i_initgraphics), [`M_ReadFile`](progs.doomgeneric.m_misc.c.md#m_readfile), [`mem_fopen_read`](progs.doomgeneric.memio.c.md#mem_fopen_read), [`mem_fopen_write`](progs.doomgeneric.memio.c.md#mem_fopen_write), [`mem_fwrite`](progs.doomgeneric.memio.c.md#mem_fwrite), [`EV_DoCeiling`](progs.doomgeneric.p_ceilng.c.md#ev_doceiling), [`EV_DoDoor`](progs.doomgeneric.p_doors.c.md#ev_dodoor) and 39 more

---

<a id="z_free"></a>

### `Z_Free`

`function` | [progs/doomgeneric/z_zone.h:55](../../progs/doomgeneric/z_zone.h#L55)

```c
void Z_Free (void *ptr);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ptr` | `void *` |  |  |

*Called by:* [`wipe_exitMelt`](progs.doomgeneric.f_wipe.c.md#wipe_exitmelt), [`wipe_shittyColMajorXform`](progs.doomgeneric.f_wipe.c.md#wipe_shittycolmajorxform), [`G_CheckDemoStatus`](progs.doomgeneric.g_game.c.md#g_checkdemostatus), [`GUS_WriteConfig`](progs.doomgeneric.gusconf.c.md#gus_writeconfig), [`I_ResetScaleTables`](progs.doomgeneric.i_scale.c.md#i_resetscaletables), [`I_ShutdownGraphics`](progs.doomgeneric.i_video.c.md#i_shutdowngraphics), [`mem_fclose`](progs.doomgeneric.memio.c.md#mem_fclose), [`mem_fwrite`](progs.doomgeneric.memio.c.md#mem_fwrite), [`P_UnArchiveThinkers`](progs.doomgeneric.p_saveg.c.md#p_unarchivethinkers), [`P_RunThinkers`](progs.doomgeneric.p_tick.c.md#p_runthinkers), [`R_GenerateLookup`](progs.doomgeneric.r_data.c.md#r_generatelookup), [`R_InitTextures`](progs.doomgeneric.r_data.c.md#r_inittextures) and 5 more

---

<a id="z_freetags"></a>

### `Z_FreeTags`

`function` | [progs/doomgeneric/z_zone.h:56](../../progs/doomgeneric/z_zone.h#L56)

```c
void Z_FreeTags (int lowtag, int hightag);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `lowtag` | `int` |  |  |
| `hightag` | `int` |  |  |

*Called by:* [`P_SetupLevel`](progs.doomgeneric.p_setup.c.md#p_setuplevel)

---

<a id="z_dumpheap"></a>

### `Z_DumpHeap`

`function` | [progs/doomgeneric/z_zone.h:57](../../progs/doomgeneric/z_zone.h#L57)

```c
void Z_DumpHeap (int lowtag, int hightag);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `lowtag` | `int` |  |  |
| `hightag` | `int` |  |  |

---

<a id="z_filedumpheap"></a>

### `Z_FileDumpHeap`

`function` | [progs/doomgeneric/z_zone.h:58](../../progs/doomgeneric/z_zone.h#L58)

```c
void Z_FileDumpHeap (FILE *f);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `f` | `FILE *` |  |  |

---

<a id="z_checkheap"></a>

### `Z_CheckHeap`

`function` | [progs/doomgeneric/z_zone.h:59](../../progs/doomgeneric/z_zone.h#L59)

```c
void Z_CheckHeap (void);
```

*Called by:* [`G_DoLoadLevel`](progs.doomgeneric.g_game.c.md#g_doloadlevel)

---

<a id="z_changetag2"></a>

### `Z_ChangeTag2`

`function` | [progs/doomgeneric/z_zone.h:60](../../progs/doomgeneric/z_zone.h#L60)

```c
void Z_ChangeTag2 (void *ptr, int tag, char *file, int line);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ptr` | `void *` |  |  |
| `tag` | `int` |  |  |
| `file` | `char *` |  |  |
| `line` | `int` |  |  |

---

<a id="z_changeuser"></a>

### `Z_ChangeUser`

`function` | [progs/doomgeneric/z_zone.h:61](../../progs/doomgeneric/z_zone.h#L61)

```c
void Z_ChangeUser(void *ptr, void **user);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ptr` | `void *` |  |  |
| `user` | `void **` |  |  |

---

<a id="z_freememory"></a>

### `Z_FreeMemory`

`function` | [progs/doomgeneric/z_zone.h:62](../../progs/doomgeneric/z_zone.h#L62)

```c
int Z_FreeMemory (void);
```

**Returns:** `int`

---

<a id="z_zonesize"></a>

### `Z_ZoneSize`

`function` | [progs/doomgeneric/z_zone.h:63](../../progs/doomgeneric/z_zone.h#L63)

```c
unsigned int Z_ZoneSize(void);
```

**Returns:** `unsigned int`

---

## Macros

<a id="__z_zone__"></a>

### `__Z_ZONE__`

`macro` | [progs/doomgeneric/z_zone.h:25](../../progs/doomgeneric/z_zone.h#L25)

```c
#define __Z_ZONE__
```

---

<a id="z_changetag"></a>

### `Z_ChangeTag`

`macro` | [progs/doomgeneric/z_zone.h:69](../../progs/doomgeneric/z_zone.h#L69)

```c
#define Z_ChangeTag(p,t)
```

This is used to get the local FILE:LINE info from CPP prior to really call the function in question.

*Called by:* [`G_DoPlayDemo`](progs.doomgeneric.g_game.c.md#g_doplaydemo), [`R_GenerateComposite`](progs.doomgeneric.r_data.c.md#r_generatecomposite), [`W_CacheLumpNum`](progs.doomgeneric.w_wad.c.md#w_cachelumpnum), [`W_ReleaseLumpNum`](progs.doomgeneric.w_wad.c.md#w_releaselumpnum)

---
