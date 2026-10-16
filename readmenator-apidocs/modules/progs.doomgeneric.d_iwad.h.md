# `progs/doomgeneric/d_iwad.h`

> Source: [progs/doomgeneric/d_iwad.h:1](../../progs/doomgeneric/d_iwad.h#L1) | language `h` | coverage 6.7% | [API index](../index.md)

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Find IWAD and initialize according to IWAD type.

## Contents

- **Structs:** [`iwad_t`](#iwad_t)
- **Functions:** [`D_FindWADByName`](#d_findwadbyname), [`D_TryFindWADByName`](#d_tryfindwadbyname), [`D_FindIWAD`](#d_findiwad), [`D_FindAllIWADs`](#d_findalliwads), [`D_SaveGameIWADName`](#d_savegameiwadname), [`D_SuggestIWADName`](#d_suggestiwadname), [`D_SuggestGameName`](#d_suggestgamename), [`D_CheckCorrectIWAD`](#d_checkcorrectiwad)
- **Macros:** [`__D_IWAD__`](#__d_iwad__), [`IWAD_MASK_DOOM`](#iwad_mask_doom), [`IWAD_MASK_HERETIC`](#iwad_mask_heretic), [`IWAD_MASK_HEXEN`](#iwad_mask_hexen), [`IWAD_MASK_STRIFE`](#iwad_mask_strife)

## Structs

<a id="iwad_t"></a>

### `iwad_t`

`struct` | [progs/doomgeneric/d_iwad.h:34](../../progs/doomgeneric/d_iwad.h#L34)

```c
typedef struct
```

---

## Functions

<a id="d_findwadbyname"></a>

### `D_FindWADByName`

`function` | [progs/doomgeneric/d_iwad.h:42](../../progs/doomgeneric/d_iwad.h#L42)

```c
char *D_FindWADByName(char *filename);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `filename` | `char *` |  |  |

**Returns:** `char *`

---

<a id="d_tryfindwadbyname"></a>

### `D_TryFindWADByName`

`function` | [progs/doomgeneric/d_iwad.h:43](../../progs/doomgeneric/d_iwad.h#L43)

```c
char *D_TryFindWADByName(char *filename);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `filename` | `char *` |  |  |

**Returns:** `char *`

*Called by:* [`W_ParseCommandLine`](progs.doomgeneric.w_main.c.md#w_parsecommandline)

---

<a id="d_findiwad"></a>

### `D_FindIWAD`

`function` | [progs/doomgeneric/d_iwad.h:44](../../progs/doomgeneric/d_iwad.h#L44)

```c
char *D_FindIWAD(int mask, GameMission_t *mission);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `mask` | `int` |  |  |
| `mission` | `GameMission_t *` |  |  |

**Returns:** `char *`

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain)

---

<a id="d_findalliwads"></a>

### `D_FindAllIWADs`

`function` `const` | [progs/doomgeneric/d_iwad.h:45](../../progs/doomgeneric/d_iwad.h#L45)

```c
const iwad_t **D_FindAllIWADs(int mask);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `mask` | `int` |  |  |

**Returns:** `iwad_t **`

---

<a id="d_savegameiwadname"></a>

### `D_SaveGameIWADName`

`function` | [progs/doomgeneric/d_iwad.h:46](../../progs/doomgeneric/d_iwad.h#L46)

```c
char *D_SaveGameIWADName(GameMission_t gamemission);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `gamemission` | `GameMission_t` |  |  |

**Returns:** `char *`

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain)

---

<a id="d_suggestiwadname"></a>

### `D_SuggestIWADName`

`function` | [progs/doomgeneric/d_iwad.h:47](../../progs/doomgeneric/d_iwad.h#L47)

```c
char *D_SuggestIWADName(GameMission_t mission, GameMode_t mode);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `mission` | `GameMission_t` |  |  |
| `mode` | `GameMode_t` |  |  |

**Returns:** `char *`

---

<a id="d_suggestgamename"></a>

### `D_SuggestGameName`

`function` | [progs/doomgeneric/d_iwad.h:48](../../progs/doomgeneric/d_iwad.h#L48)

```c
char *D_SuggestGameName(GameMission_t mission, GameMode_t mode);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `mission` | `GameMission_t` |  |  |
| `mode` | `GameMode_t` |  |  |

**Returns:** `char *`

*Called by:* [`W_CheckCorrectIWAD`](progs.doomgeneric.w_wad.c.md#w_checkcorrectiwad)

---

<a id="d_checkcorrectiwad"></a>

### `D_CheckCorrectIWAD`

`function` | [progs/doomgeneric/d_iwad.h:49](../../progs/doomgeneric/d_iwad.h#L49)

```c
void D_CheckCorrectIWAD(GameMission_t mission);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `mission` | `GameMission_t` |  |  |

---

## Macros

<a id="__d_iwad__"></a>

### `__D_IWAD__`

`macro` | [progs/doomgeneric/d_iwad.h:20](../../progs/doomgeneric/d_iwad.h#L20)

```c
#define __D_IWAD__
```

---

<a id="iwad_mask_doom"></a>

### `IWAD_MASK_DOOM`

`macro` | [progs/doomgeneric/d_iwad.h:24](../../progs/doomgeneric/d_iwad.h#L24)

```c
#define IWAD_MASK_DOOM
```

---

<a id="iwad_mask_heretic"></a>

### `IWAD_MASK_HERETIC`

`macro` | [progs/doomgeneric/d_iwad.h:30](../../progs/doomgeneric/d_iwad.h#L30)

```c
#define IWAD_MASK_HERETIC
```

---

<a id="iwad_mask_hexen"></a>

### `IWAD_MASK_HEXEN`

`macro` | [progs/doomgeneric/d_iwad.h:31](../../progs/doomgeneric/d_iwad.h#L31)

```c
#define IWAD_MASK_HEXEN
```

---

<a id="iwad_mask_strife"></a>

### `IWAD_MASK_STRIFE`

`macro` | [progs/doomgeneric/d_iwad.h:32](../../progs/doomgeneric/d_iwad.h#L32)

```c
#define IWAD_MASK_STRIFE
```

---
