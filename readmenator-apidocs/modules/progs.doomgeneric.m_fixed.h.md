# `progs/doomgeneric/m_fixed.h`

> Source: [progs/doomgeneric/m_fixed.h:1](../../progs/doomgeneric/m_fixed.h#L1) | language `h` | coverage 42.9% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Fixed point arithemtics, implementation.         Fixed point, 32bit as 16.16.

## Contents

- **Type Aliases:** [`fixed_t`](#fixed_t)
- **Functions:** [`FixedMul`](#fixedmul), [`FixedDiv`](#fixeddiv)
- **Macros:** [`__M_FIXED__`](#__m_fixed__), [`FRACBITS`](#fracbits), [`FRACUNIT`](#fracunit)

## Type Aliases

<a id="fixed_t"></a>

### `fixed_t`

`type_alias` | [progs/doomgeneric/m_fixed.h:31](../../progs/doomgeneric/m_fixed.h#L31)

```c
typedef int fixed_t;
```

Fixed point, 32bit as 16.16.  define FRACBITS           16 define FRACUNIT              (1<<FRACBITS)

---

## Functions

<a id="fixedmul"></a>

### `FixedMul`

`function` | [progs/doomgeneric/m_fixed.h:34](../../progs/doomgeneric/m_fixed.h#L34)

```c
fixed_t FixedMul (fixed_t a, fixed_t b);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a` | `fixed_t` |  |  |
| `b` | `fixed_t` |  |  |

**Returns:** `fixed_t`

---

<a id="fixeddiv"></a>

### `FixedDiv`

`function` | [progs/doomgeneric/m_fixed.h:35](../../progs/doomgeneric/m_fixed.h#L35)

```c
fixed_t FixedDiv (fixed_t a, fixed_t b);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a` | `fixed_t` |  |  |
| `b` | `fixed_t` |  |  |

**Returns:** `fixed_t`

---

## Macros

<a id="__m_fixed__"></a>

### `__M_FIXED__`

`macro` | [progs/doomgeneric/m_fixed.h:21](../../progs/doomgeneric/m_fixed.h#L21)

```c
#define __M_FIXED__
```

---

<a id="fracbits"></a>

### `FRACBITS`

`macro` | [progs/doomgeneric/m_fixed.h:29](../../progs/doomgeneric/m_fixed.h#L29)

```c
#define FRACBITS
```

Fixed point, 32bit as 16.16.

---

<a id="fracunit"></a>

### `FRACUNIT`

`macro` | [progs/doomgeneric/m_fixed.h:30](../../progs/doomgeneric/m_fixed.h#L30)

```c
#define FRACUNIT
```

---
