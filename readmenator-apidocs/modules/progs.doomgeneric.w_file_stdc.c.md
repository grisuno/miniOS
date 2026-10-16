# `progs/doomgeneric/w_file_stdc.c`

> Source: [progs/doomgeneric/w_file_stdc.c:1](../../progs/doomgeneric/w_file_stdc.c#L1) | language `c` | coverage 33.3% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: WAD I/O functions.

## Contents

- **Structs:** [`stdc_wad_file_t`](#stdc_wad_file_t)
- **Functions:** [`W_StdC_Read`](#w_stdc_read)
- **Variables:** [`stdc_wad_file`](#stdc_wad_file)

## Structs

<a id="stdc_wad_file_t"></a>

### `stdc_wad_file_t`

`struct` | [progs/doomgeneric/w_file_stdc.c:25](../../progs/doomgeneric/w_file_stdc.c#L25)

```c
typedef struct
```

---

## Functions

<a id="w_stdc_read"></a>

### `W_StdC_Read`

`function` | [progs/doomgeneric/w_file_stdc.c:69](../../progs/doomgeneric/w_file_stdc.c#L69)

```c
size_t W_StdC_Read(wad_file_t *wad, unsigned int offset, void *buffer, size_t buffer_len)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `wad` | `wad_file_t *` |  |  |
| `offset` | `unsigned int` |  |  |
| `buffer` | `void *` |  |  |
| `buffer_len` | `size_t` |  |  |

**Returns:** `size_t`

---

## Variables

<a id="stdc_wad_file"></a>

### `stdc_wad_file`

`variable` `extern` | [progs/doomgeneric/w_file_stdc.c:31](../../progs/doomgeneric/w_file_stdc.c#L31)

```c
extern wad_file_class_t stdc_wad_file;
```

---
