# `progs/doomgeneric/d_event.h`

> Source: [progs/doomgeneric/d_event.h:1](../../progs/doomgeneric/d_event.h#L1) | language `h` | coverage 60.0% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION:          Event handling.

## Contents

- **Structs:** [`event_t`](#event_t)
- **Functions:** [`D_PostEvent`](#d_postevent), [`D_PopEvent`](#d_popevent)
- **Macros:** [`__D_EVENT__`](#__d_event__)

## Structs

<a id="event_t"></a>

### `event_t`

`struct` | [progs/doomgeneric/d_event.h:42](../../progs/doomgeneric/d_event.h#L42)

```c
typedef struct
```

Event structure.

---

## Functions

<a id="d_postevent"></a>

### `D_PostEvent`

`function` | [progs/doomgeneric/d_event.h:129](../../progs/doomgeneric/d_event.h#L129)

```c
void D_PostEvent (event_t *ev);
```

Called by IO functions when input is detected.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ev` | `event_t *` |  |  |

*Called by:* [`I_UpdateJoystick`](progs.doomgeneric.i_joystick.c.md#i_updatejoystick)

---

<a id="d_popevent"></a>

### `D_PopEvent`

`function` | [progs/doomgeneric/d_event.h:133](../../progs/doomgeneric/d_event.h#L133)

```c
event_t *D_PopEvent(void);
```

**Returns:** `event_t *`

---

## Macros

<a id="__d_event__"></a>

### `__D_EVENT__`

`macro` | [progs/doomgeneric/d_event.h:21](../../progs/doomgeneric/d_event.h#L21)

```c
#define __D_EVENT__
```

---
