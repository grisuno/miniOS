# `progs/doomgeneric/i_scale.h`

> Source: [progs/doomgeneric/i_scale.h:1](../../progs/doomgeneric/i_scale.h#L1) | language `h` | coverage 25.0% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Pixel-doubling scale up functions.

## Contents

- **Functions:** [`I_InitScale`](#i_initscale), [`I_ResetScaleTables`](#i_resetscaletables)
- **Macros:** [`__I_SCALE__`](#__i_scale__)
- **Variables:** [`mode_scale_1x`](#mode_scale_1x), [`mode_scale_2x`](#mode_scale_2x), [`mode_scale_3x`](#mode_scale_3x), [`mode_scale_4x`](#mode_scale_4x), [`mode_scale_5x`](#mode_scale_5x), [`mode_stretch_1x`](#mode_stretch_1x), [`mode_stretch_2x`](#mode_stretch_2x), [`mode_stretch_3x`](#mode_stretch_3x), [`mode_stretch_4x`](#mode_stretch_4x), [`mode_stretch_5x`](#mode_stretch_5x), [`mode_squash_1x`](#mode_squash_1x), [`mode_squash_2x`](#mode_squash_2x), [`mode_squash_3x`](#mode_squash_3x), [`mode_squash_4x`](#mode_squash_4x), [`mode_squash_5x`](#mode_squash_5x)

## Functions

<a id="i_initscale"></a>

### `I_InitScale`

`function` | [progs/doomgeneric/i_scale.h:25](../../progs/doomgeneric/i_scale.h#L25)

```c
void I_InitScale(byte *_src_buffer, byte *_dest_buffer, int _dest_pitch);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `_src_buffer` | `byte *` |  |  |
| `_dest_buffer` | `byte *` |  |  |
| `_dest_pitch` | `int` |  |  |

---

<a id="i_resetscaletables"></a>

### `I_ResetScaleTables`

`function` | [progs/doomgeneric/i_scale.h:26](../../progs/doomgeneric/i_scale.h#L26)

```c
void I_ResetScaleTables(byte *palette);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `palette` | `byte *` |  |  |

---

## Macros

<a id="__i_scale__"></a>

### `__I_SCALE__`

`macro` | [progs/doomgeneric/i_scale.h:21](../../progs/doomgeneric/i_scale.h#L21)

```c
#define __I_SCALE__
```

---

## Variables

<a id="mode_scale_1x"></a>

### `mode_scale_1x`

`variable` `extern` | [progs/doomgeneric/i_scale.h:30](../../progs/doomgeneric/i_scale.h#L30)

```c
extern screen_mode_t mode_scale_1x;
```

---

<a id="mode_scale_2x"></a>

### `mode_scale_2x`

`variable` `extern` | [progs/doomgeneric/i_scale.h:31](../../progs/doomgeneric/i_scale.h#L31)

```c
extern screen_mode_t mode_scale_2x;
```

---

<a id="mode_scale_3x"></a>

### `mode_scale_3x`

`variable` `extern` | [progs/doomgeneric/i_scale.h:32](../../progs/doomgeneric/i_scale.h#L32)

```c
extern screen_mode_t mode_scale_3x;
```

---

<a id="mode_scale_4x"></a>

### `mode_scale_4x`

`variable` `extern` | [progs/doomgeneric/i_scale.h:33](../../progs/doomgeneric/i_scale.h#L33)

```c
extern screen_mode_t mode_scale_4x;
```

---

<a id="mode_scale_5x"></a>

### `mode_scale_5x`

`variable` `extern` | [progs/doomgeneric/i_scale.h:34](../../progs/doomgeneric/i_scale.h#L34)

```c
extern screen_mode_t mode_scale_5x;
```

---

<a id="mode_stretch_1x"></a>

### `mode_stretch_1x`

`variable` `extern` | [progs/doomgeneric/i_scale.h:38](../../progs/doomgeneric/i_scale.h#L38)

```c
extern screen_mode_t mode_stretch_1x;
```

---

<a id="mode_stretch_2x"></a>

### `mode_stretch_2x`

`variable` `extern` | [progs/doomgeneric/i_scale.h:39](../../progs/doomgeneric/i_scale.h#L39)

```c
extern screen_mode_t mode_stretch_2x;
```

---

<a id="mode_stretch_3x"></a>

### `mode_stretch_3x`

`variable` `extern` | [progs/doomgeneric/i_scale.h:40](../../progs/doomgeneric/i_scale.h#L40)

```c
extern screen_mode_t mode_stretch_3x;
```

---

<a id="mode_stretch_4x"></a>

### `mode_stretch_4x`

`variable` `extern` | [progs/doomgeneric/i_scale.h:41](../../progs/doomgeneric/i_scale.h#L41)

```c
extern screen_mode_t mode_stretch_4x;
```

---

<a id="mode_stretch_5x"></a>

### `mode_stretch_5x`

`variable` `extern` | [progs/doomgeneric/i_scale.h:42](../../progs/doomgeneric/i_scale.h#L42)

```c
extern screen_mode_t mode_stretch_5x;
```

---

<a id="mode_squash_1x"></a>

### `mode_squash_1x`

`variable` `extern` | [progs/doomgeneric/i_scale.h:46](../../progs/doomgeneric/i_scale.h#L46)

```c
extern screen_mode_t mode_squash_1x;
```

---

<a id="mode_squash_2x"></a>

### `mode_squash_2x`

`variable` `extern` | [progs/doomgeneric/i_scale.h:47](../../progs/doomgeneric/i_scale.h#L47)

```c
extern screen_mode_t mode_squash_2x;
```

---

<a id="mode_squash_3x"></a>

### `mode_squash_3x`

`variable` `extern` | [progs/doomgeneric/i_scale.h:48](../../progs/doomgeneric/i_scale.h#L48)

```c
extern screen_mode_t mode_squash_3x;
```

---

<a id="mode_squash_4x"></a>

### `mode_squash_4x`

`variable` `extern` | [progs/doomgeneric/i_scale.h:49](../../progs/doomgeneric/i_scale.h#L49)

```c
extern screen_mode_t mode_squash_4x;
```

---

<a id="mode_squash_5x"></a>

### `mode_squash_5x`

`variable` `extern` | [progs/doomgeneric/i_scale.h:50](../../progs/doomgeneric/i_scale.h#L50)

```c
extern screen_mode_t mode_squash_5x;
```

---
