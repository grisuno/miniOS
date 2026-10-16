# `progs/doomgeneric/deh_main.h`

> Source: [progs/doomgeneric/deh_main.h:1](../../progs/doomgeneric/deh_main.h#L1) | language `h` | coverage 12.5% | [API index](../index.md)

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.   Dehacked entrypoint and common code     These are the limits that dehacked uses (from dheinit.h in the dehacked source).  If these limits are exceeded, it does not generate an error, but a warning is displayed.

## Contents

- **Functions:** [`DEH_ParseCommandLine`](#deh_parsecommandline), [`DEH_LoadFile`](#deh_loadfile), [`DEH_LoadLump`](#deh_loadlump), [`DEH_LoadLumpByName`](#deh_loadlumpbyname), [`DEH_Checksum`](#deh_checksum)
- **Macros:** [`DEH_VANILLA_NUMSTATES`](#deh_vanilla_numstates), [`DEH_VANILLA_NUMSFX`](#deh_vanilla_numsfx)
- **Variables:** [`deh_allow_extended_strings`](#deh_allow_extended_strings), [`deh_allow_long_strings`](#deh_allow_long_strings), [`deh_allow_long_cheats`](#deh_allow_long_cheats), [`deh_apply_cheats`](#deh_apply_cheats)

## Functions

<a id="deh_parsecommandline"></a>

### `DEH_ParseCommandLine`

`function` | [progs/doomgeneric/deh_main.h:33](../../progs/doomgeneric/deh_main.h#L33)

```c
void DEH_ParseCommandLine(void);
```

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain)

---

<a id="deh_loadfile"></a>

### `DEH_LoadFile`

`function` | [progs/doomgeneric/deh_main.h:34](../../progs/doomgeneric/deh_main.h#L34)

```c
int DEH_LoadFile(char *filename);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `filename` | `char *` |  |  |

**Returns:** `int`

---

<a id="deh_loadlump"></a>

### `DEH_LoadLump`

`function` | [progs/doomgeneric/deh_main.h:35](../../progs/doomgeneric/deh_main.h#L35)

```c
int DEH_LoadLump(int lumpnum, boolean allow_long, boolean allow_error);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `lumpnum` | `int` |  |  |
| `allow_long` | `boolean` |  |  |
| `allow_error` | `boolean` |  |  |

**Returns:** `int`

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain)

---

<a id="deh_loadlumpbyname"></a>

### `DEH_LoadLumpByName`

`function` | [progs/doomgeneric/deh_main.h:36](../../progs/doomgeneric/deh_main.h#L36)

```c
int DEH_LoadLumpByName(char *name, boolean allow_long, boolean allow_error);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `name` | `char *` |  |  |
| `allow_long` | `boolean` |  |  |
| `allow_error` | `boolean` |  |  |

**Returns:** `int`

---

<a id="deh_checksum"></a>

### `DEH_Checksum`

`function` | [progs/doomgeneric/deh_main.h:40](../../progs/doomgeneric/deh_main.h#L40)

```c
void DEH_Checksum(sha1_digest_t digest);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `digest` | `sha1_digest_t` |  |  |

---

## Macros

<a id="deh_vanilla_numstates"></a>

### `DEH_VANILLA_NUMSTATES`

`macro` | [progs/doomgeneric/deh_main.h:30](../../progs/doomgeneric/deh_main.h#L30)

```c
#define DEH_VANILLA_NUMSTATES
```

---

<a id="deh_vanilla_numsfx"></a>

### `DEH_VANILLA_NUMSFX`

`macro` | [progs/doomgeneric/deh_main.h:31](../../progs/doomgeneric/deh_main.h#L31)

```c
#define DEH_VANILLA_NUMSFX
```

---

## Variables

<a id="deh_allow_extended_strings"></a>

### `deh_allow_extended_strings`

`variable` `extern` | [progs/doomgeneric/deh_main.h:42](../../progs/doomgeneric/deh_main.h#L42)

```c
extern boolean deh_allow_extended_strings;
```

---

<a id="deh_allow_long_strings"></a>

### `deh_allow_long_strings`

`variable` `extern` | [progs/doomgeneric/deh_main.h:43](../../progs/doomgeneric/deh_main.h#L43)

```c
extern boolean deh_allow_long_strings;
```

---

<a id="deh_allow_long_cheats"></a>

### `deh_allow_long_cheats`

`variable` `extern` | [progs/doomgeneric/deh_main.h:44](../../progs/doomgeneric/deh_main.h#L44)

```c
extern boolean deh_allow_long_cheats;
```

---

<a id="deh_apply_cheats"></a>

### `deh_apply_cheats`

`variable` `extern` | [progs/doomgeneric/deh_main.h:45](../../progs/doomgeneric/deh_main.h#L45)

```c
extern boolean deh_apply_cheats;
```

---
