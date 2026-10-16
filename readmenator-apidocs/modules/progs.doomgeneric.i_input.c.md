# `progs/doomgeneric/i_input.c`

> Source: [progs/doomgeneric/i_input.c:1](../../progs/doomgeneric/i_input.c#L1) | language `c` | coverage 33.3% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

## Contents

- **Functions:** [`I_GetEvent`](#i_getevent), [`I_InitInput`](#i_initinput)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_progs_doomgeneric_i_input_c__I_GetEvent(["I_GetEvent"])
    n_progs_doomgeneric_doomgeneric_h__DG_GetKey["doomgeneric.DG_GetKey"]
    n_progs_doomgeneric_i_input_c__I_GetEvent -.-> n_progs_doomgeneric_doomgeneric_h__DG_GetKey
```

## Functions

<a id="i_getevent"></a>

### `I_GetEvent`

`function` | [progs/doomgeneric/i_input.c:279](../../progs/doomgeneric/i_input.c#L279)

```c
void I_GetEvent(void)
```

*Calls:* [`DG_GetKey`](progs.doomgeneric.doomgeneric.h.md#dg_getkey)

---

<a id="i_initinput"></a>

### `I_InitInput`

`function` | [progs/doomgeneric/i_input.c:338](../../progs/doomgeneric/i_input.c#L338)

```c
void I_InitInput(void)
```

---
