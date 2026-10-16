# `progs/doomgeneric/gusconf.c`

> Source: [progs/doomgeneric/gusconf.c:1](../../progs/doomgeneric/gusconf.c#L1) | language `c` | coverage 25.0% | [API index](../index.md)

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: GUS emulation code.  Actually emulating a GUS is far too much work; fortunately GUS "emulation" already exists in the form of Timidity, which supports GUS patch files. This code therefore converts Doom's DMXGUS lump into an equivalent Timidity configuration file.

## Contents

- **Structs:** [`gus_config_t`](#gus_config_t)
- **Functions:** [`GUS_WriteConfig`](#gus_writeconfig)
- **Macros:** [`MAX_INSTRUMENTS`](#max_instruments)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_progs_doomgeneric_gusconf_c__GUS_WriteConfig(["GUS_WriteConfig"])
    n_progs_doomgeneric_z_zone_h__Z_Free["z_zone.Z_Free"]
    n_progs_doomgeneric_gusconf_c__GUS_WriteConfig -.-> n_progs_doomgeneric_z_zone_h__Z_Free
```

## Structs

<a id="gus_config_t"></a>

### `gus_config_t`

`struct` | [progs/doomgeneric/gusconf.c:34](../../progs/doomgeneric/gusconf.c#L34)

```c
typedef struct
```

---

## Functions

<a id="gus_writeconfig"></a>

### `GUS_WriteConfig`

`function` | [progs/doomgeneric/gusconf.c:244](../../progs/doomgeneric/gusconf.c#L244)

```c
boolean GUS_WriteConfig(char *path)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `path` | `char *` |  |  |

**Returns:** `boolean`

*Calls:* [`Z_Free`](progs.doomgeneric.z_zone.h.md#z_free)

---

## Macros

<a id="max_instruments"></a>

### `MAX_INSTRUMENTS`

`macro` | [progs/doomgeneric/gusconf.c:32](../../progs/doomgeneric/gusconf.c#L32)

```c
#define MAX_INSTRUMENTS
```

---
