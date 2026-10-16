# `progs/doomgeneric/m_cheat.c`

> Source: [progs/doomgeneric/m_cheat.c:1](../../progs/doomgeneric/m_cheat.c#L1) | language `c` | coverage 33.3% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Cheat sequence checking.        CHEAT SEQUENCE PACKAGE

## Contents

- **Functions:** [`cht_CheckCheat`](#cht_checkcheat), [`cht_GetParam`](#cht_getparam)

## Functions

<a id="cht_checkcheat"></a>

### `cht_CheckCheat`

`function` | [progs/doomgeneric/m_cheat.c:35](../../progs/doomgeneric/m_cheat.c#L35)

```c
int cht_CheckCheat ( cheatseq_t* cht, char key )
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `cht` | `cheatseq_t*` |  |  |
| `key` | `char` |  |  |

**Returns:** `int`

---

<a id="cht_getparam"></a>

### `cht_GetParam`

`function` | [progs/doomgeneric/m_cheat.c:82](../../progs/doomgeneric/m_cheat.c#L82)

```c
void cht_GetParam ( cheatseq_t* cht, char* buffer )
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `cht` | `cheatseq_t*` |  |  |
| `buffer` | `char*` |  |  |

---
