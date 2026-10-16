# `progs/doomgeneric/m_random.c`

> Source: [progs/doomgeneric/m_random.c:1](../../progs/doomgeneric/m_random.c#L1) | language `c` | coverage 100.0% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Random number LUT.    M_Random Returns a 0-255 number

## Contents

- **Functions:** [`P_Random`](#p_random), [`M_Random`](#m_random), [`M_ClearRandom`](#m_clearrandom)

## Functions

<a id="p_random"></a>

### `P_Random`

`function` | [progs/doomgeneric/m_random.c:50](../../progs/doomgeneric/m_random.c#L50)

```c
int P_Random (void)
```

Which one is deterministic?

**Returns:** `int`

---

<a id="m_random"></a>

### `M_Random`

`function` | [progs/doomgeneric/m_random.c:56](../../progs/doomgeneric/m_random.c#L56)

```c
int M_Random (void)
```

Returns a number from 0 to 255, from a lookup table.

**Returns:** `int`

> **Inherited:** Documentation from [`M_Random`](#m_random) (progs/doomgeneric/m_random.h:30).

---

<a id="m_clearrandom"></a>

### `M_ClearRandom`

`function` | [progs/doomgeneric/m_random.c:62](../../progs/doomgeneric/m_random.c#L62)

```c
void M_ClearRandom (void)
```

Fix randoms for demos.

> **Inherited:** Documentation from [`M_ClearRandom`](#m_clearrandom) (progs/doomgeneric/m_random.h:36).

---
