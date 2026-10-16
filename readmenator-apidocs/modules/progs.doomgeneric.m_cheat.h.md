# `progs/doomgeneric/m_cheat.h`

> Source: [progs/doomgeneric/m_cheat.h:1](../../progs/doomgeneric/m_cheat.h#L1) | language `h` | coverage 12.5% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Cheat code checking.      CHEAT SEQUENCE PACKAGE   declaring a cheat

## Contents

- **Structs:** [`cheatseq_t`](#cheatseq_t)
- **Functions:** [`cht_CheckCheat`](#cht_checkcheat), [`cht_GetParam`](#cht_getparam)
- **Macros:** [`__M_CHEAT__`](#__m_cheat__), [`CHEAT`](#cheat), [`MAX_CHEAT_LEN`](#max_cheat_len), [`MAX_CHEAT_PARAMS`](#max_cheat_params)

## Structs

<a id="cheatseq_t"></a>

### `cheatseq_t`

`struct` | [progs/doomgeneric/m_cheat.h:35](../../progs/doomgeneric/m_cheat.h#L35)

```c
typedef struct
```

---

## Functions

<a id="cht_checkcheat"></a>

### `cht_CheckCheat`

`function` | [progs/doomgeneric/m_cheat.h:51](../../progs/doomgeneric/m_cheat.h#L51)

```c
int cht_CheckCheat ( cheatseq_t* cht, char key );
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `cht` | `cheatseq_t*` |  |  |
| `key` | `char` |  |  |

**Returns:** `int`

*Called by:* [`AM_Responder`](progs.doomgeneric.am_map.c.md#am_responder), [`ST_Responder`](progs.doomgeneric.st_stuff.c.md#st_responder)

---

<a id="cht_getparam"></a>

### `cht_GetParam`

`function` | [progs/doomgeneric/m_cheat.h:57](../../progs/doomgeneric/m_cheat.h#L57)

```c
void cht_GetParam ( cheatseq_t* cht, char* buffer );
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `cht` | `cheatseq_t*` |  |  |
| `buffer` | `char*` |  |  |

*Called by:* [`ST_Responder`](progs.doomgeneric.st_stuff.c.md#st_responder)

---

## Macros

<a id="__m_cheat__"></a>

### `__M_CHEAT__`

`macro` | [progs/doomgeneric/m_cheat.h:21](../../progs/doomgeneric/m_cheat.h#L21)

```c
#define __M_CHEAT__
```

---

<a id="cheat"></a>

### `CHEAT`

`macro` | [progs/doomgeneric/m_cheat.h:29](../../progs/doomgeneric/m_cheat.h#L29)

```c
#define CHEAT(value, parameters)
```

---

<a id="max_cheat_len"></a>

### `MAX_CHEAT_LEN`

`macro` | [progs/doomgeneric/m_cheat.h:32](../../progs/doomgeneric/m_cheat.h#L32)

```c
#define MAX_CHEAT_LEN
```

---

<a id="max_cheat_params"></a>

### `MAX_CHEAT_PARAMS`

`macro` | [progs/doomgeneric/m_cheat.h:33](../../progs/doomgeneric/m_cheat.h#L33)

```c
#define MAX_CHEAT_PARAMS
```

---
