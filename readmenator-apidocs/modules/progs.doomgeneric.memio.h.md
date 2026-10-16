# `progs/doomgeneric/memio.h`

> Source: [progs/doomgeneric/memio.h:1](../../progs/doomgeneric/memio.h#L1) | language `h` | coverage 20.0% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

## Contents

- **Type Aliases:** [`MEMFILE`](#memfile)
- **Functions:** [`mem_fopen_read`](#mem_fopen_read), [`mem_fread`](#mem_fread), [`mem_fopen_write`](#mem_fopen_write), [`mem_fwrite`](#mem_fwrite), [`mem_get_buf`](#mem_get_buf), [`mem_fclose`](#mem_fclose), [`mem_ftell`](#mem_ftell), [`mem_fseek`](#mem_fseek)

## Type Aliases

<a id="memfile"></a>

### `MEMFILE`

`type_alias` | [progs/doomgeneric/memio.h:18](../../progs/doomgeneric/memio.h#L18)

```c
typedef struct _MEMFILE MEMFILE;
```

ifndef MEMIO_H define MEMIO_H

---

## Functions

<a id="mem_fopen_read"></a>

### `mem_fopen_read`

`function` | [progs/doomgeneric/memio.h:28](../../progs/doomgeneric/memio.h#L28)

```c
MEMFILE *mem_fopen_read(void *buf, size_t buflen);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `buf` | `void *` |  |  |
| `buflen` | `size_t` |  |  |

**Returns:** `MEMFILE *`

---

<a id="mem_fread"></a>

### `mem_fread`

`function` | [progs/doomgeneric/memio.h:29](../../progs/doomgeneric/memio.h#L29)

```c
size_t mem_fread(void *buf, size_t size, size_t nmemb, MEMFILE *stream);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `buf` | `void *` |  |  |
| `size` | `size_t` |  |  |
| `nmemb` | `size_t` |  |  |
| `stream` | `MEMFILE *` |  |  |

**Returns:** `size_t`

---

<a id="mem_fopen_write"></a>

### `mem_fopen_write`

`function` | [progs/doomgeneric/memio.h:30](../../progs/doomgeneric/memio.h#L30)

```c
MEMFILE *mem_fopen_write(void);
```

**Returns:** `MEMFILE *`

---

<a id="mem_fwrite"></a>

### `mem_fwrite`

`function` | [progs/doomgeneric/memio.h:31](../../progs/doomgeneric/memio.h#L31)

```c
size_t mem_fwrite(const void *ptr, size_t size, size_t nmemb, MEMFILE *stream);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ptr` | `void *` |  |  |
| `size` | `size_t` |  |  |
| `nmemb` | `size_t` |  |  |
| `stream` | `MEMFILE *` |  |  |

**Returns:** `size_t`

---

<a id="mem_get_buf"></a>

### `mem_get_buf`

`function` | [progs/doomgeneric/memio.h:32](../../progs/doomgeneric/memio.h#L32)

```c
void mem_get_buf(MEMFILE *stream, void **buf, size_t *buflen);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `stream` | `MEMFILE *` |  |  |
| `buf` | `void **` |  |  |
| `buflen` | `size_t *` |  |  |

---

<a id="mem_fclose"></a>

### `mem_fclose`

`function` | [progs/doomgeneric/memio.h:33](../../progs/doomgeneric/memio.h#L33)

```c
void mem_fclose(MEMFILE *stream);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `stream` | `MEMFILE *` |  |  |

---

<a id="mem_ftell"></a>

### `mem_ftell`

`function` | [progs/doomgeneric/memio.h:34](../../progs/doomgeneric/memio.h#L34)

```c
long mem_ftell(MEMFILE *stream);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `stream` | `MEMFILE *` |  |  |

**Returns:** `long`

---

<a id="mem_fseek"></a>

### `mem_fseek`

`function` | [progs/doomgeneric/memio.h:35](../../progs/doomgeneric/memio.h#L35)

```c
int mem_fseek(MEMFILE *stream, signed long offset, mem_rel_t whence);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `stream` | `MEMFILE *` |  |  |
| `offset` | `signed long` |  |  |
| `whence` | `mem_rel_t` |  |  |

**Returns:** `int`

---
