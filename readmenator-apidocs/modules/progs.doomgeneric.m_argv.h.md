# `progs/doomgeneric/m_argv.h`

> Source: [progs/doomgeneric/m_argv.h:1](../../progs/doomgeneric/m_argv.h#L1) | language `h` | coverage 50.0% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Nil.       MISC

## Contents

- **Functions:** [`M_CheckParm`](#m_checkparm), [`M_CheckParmWithArgs`](#m_checkparmwithargs), [`M_FindResponseFile`](#m_findresponsefile), [`M_GetExecutableName`](#m_getexecutablename)
- **Macros:** [`__M_ARGV__`](#__m_argv__)
- **Variables:** [`myargc`](#myargc), [`myargv`](#myargv)

## Functions

<a id="m_checkparm"></a>

### `M_CheckParm`

`function` | [progs/doomgeneric/m_argv.h:33](../../progs/doomgeneric/m_argv.h#L33)

```c
int M_CheckParm (char* check);
```

Returns the position of the given parameter in the arg list (0 if not found).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `check` | `char*` |  |  |

**Returns:** `int`

*Called by:* [`D_InitNetGame`](progs.doomgeneric.d_loop.c.md#d_initnetgame), [`D_StartNetGame`](progs.doomgeneric.d_loop.c.md#d_startnetgame), [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain), [`D_CheckNetGame`](progs.doomgeneric.d_net.c.md#d_checknetgame), [`D_ConnectNetGame`](progs.doomgeneric.d_net.c.md#d_connectnetgame), [`G_BeginRecording`](progs.doomgeneric.g_game.c.md#g_beginrecording), [`G_DoPlayDemo`](progs.doomgeneric.g_game.c.md#g_doplaydemo), [`G_TimeDemo`](progs.doomgeneric.g_game.c.md#g_timedemo), [`I_InitSound`](progs.doomgeneric.i_sound.c.md#i_initsound), [`W_OpenFile`](progs.doomgeneric.w_file.c.md#w_openfile)

---

<a id="m_checkparmwithargs"></a>

### `M_CheckParmWithArgs`

`function` | [progs/doomgeneric/m_argv.h:37](../../progs/doomgeneric/m_argv.h#L37)

```c
int M_CheckParmWithArgs(char *check, int num_args);
```

Same as M_CheckParm, but checks that num_args arguments are available following the specified argument.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `check` | `char *` |  |  |
| `num_args` | `int` |  |  |

**Returns:** `int`

*Called by:* [`D_FindIWAD`](progs.doomgeneric.d_iwad.c.md#d_findiwad), [`D_InitNetGame`](progs.doomgeneric.d_loop.c.md#d_initnetgame), [`D_StartNetGame`](progs.doomgeneric.d_loop.c.md#d_startnetgame), [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain), [`D_IdentifyVersion`](progs.doomgeneric.d_main.c.md#d_identifyversion), [`DG_Init`](progs.doomgeneric.doomgeneric_soso.c.md#dg_init), [`G_RecordDemo`](progs.doomgeneric.g_game.c.md#g_recorddemo), [`I_GetMemoryValue`](progs.doomgeneric.i_system.c.md#i_getmemoryvalue), [`I_ZoneBase`](progs.doomgeneric.i_system.c.md#i_zonebase), [`I_InitGraphics`](progs.doomgeneric.i_video.c.md#i_initgraphics), [`M_LoadDefaults`](progs.doomgeneric.m_config.c.md#m_loaddefaults), [`StatDump`](progs.doomgeneric.statdump.c.md#statdump) and 1 more

---

<a id="m_findresponsefile"></a>

### `M_FindResponseFile`

`function` | [progs/doomgeneric/m_argv.h:39](../../progs/doomgeneric/m_argv.h#L39)

```c
void M_FindResponseFile(void);
```

---

<a id="m_getexecutablename"></a>

### `M_GetExecutableName`

`function` | [progs/doomgeneric/m_argv.h:47](../../progs/doomgeneric/m_argv.h#L47)

```c
char *M_GetExecutableName(void);
```

**Returns:** `char *`

---

## Macros

<a id="__m_argv__"></a>

### `__M_ARGV__`

`macro` | [progs/doomgeneric/m_argv.h:21](../../progs/doomgeneric/m_argv.h#L21)

```c
#define __M_ARGV__
```

---

## Variables

<a id="myargc"></a>

### `myargc`

`variable` `extern` | [progs/doomgeneric/m_argv.h:28](../../progs/doomgeneric/m_argv.h#L28)

```c
extern int myargc;
```

MISC

---

<a id="myargv"></a>

### `myargv`

`variable` `extern` | [progs/doomgeneric/m_argv.h:29](../../progs/doomgeneric/m_argv.h#L29)

```c
extern char** myargv;
```

---
