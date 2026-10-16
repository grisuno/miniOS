# `progs/doomgeneric/v_patch.h`

> Source: [progs/doomgeneric/v_patch.h:1](../../progs/doomgeneric/v_patch.h#L1) | language `h` | coverage 100.0% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Refresh/rendering module, shared data struct definitions.     Patches. A patch holds one or more columns. Patches are used for sprites and all masked pictures, and we compose textures from the TEXTURE1/2 lists of patches.

## Contents

- **Type Aliases:** [`column_t`](#column_t)

## Type Aliases

<a id="column_t"></a>

### `column_t`

`type_alias` | [progs/doomgeneric/v_patch.h:47](../../progs/doomgeneric/v_patch.h#L47)

```c
typedef post_t column_t;
```

column_t is a list of 0 or more post_t, (byte)-1 terminated

---
