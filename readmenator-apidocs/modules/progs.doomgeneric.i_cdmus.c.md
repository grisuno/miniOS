# `progs/doomgeneric/i_cdmus.c`

> Source: [progs/doomgeneric/i_cdmus.c:1](../../progs/doomgeneric/i_cdmus.c#L1) | language `c` | coverage 10.0% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 1993-2008 Raven Software  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.   SDL implementation of the Hexen CD interface.

## Contents

- **Functions:** [`I_CDMusInit`](#i_cdmusinit), [`I_CDMusPrintStartup`](#i_cdmusprintstartup), [`I_CDMusPlay`](#i_cdmusplay), [`I_CDMusStop`](#i_cdmusstop), [`I_CDMusResume`](#i_cdmusresume), [`I_CDMusSetVolume`](#i_cdmussetvolume), [`I_CDMusFirstTrack`](#i_cdmusfirsttrack), [`I_CDMusLastTrack`](#i_cdmuslasttrack), [`I_CDMusTrackLength`](#i_cdmustracklength)

## Functions

<a id="i_cdmusinit"></a>

### `I_CDMusInit`

`function` | [progs/doomgeneric/i_cdmus.c:38](../../progs/doomgeneric/i_cdmus.c#L38)

```c
int I_CDMusInit(void)
```

**Returns:** `int`

---

<a id="i_cdmusprintstartup"></a>

### `I_CDMusPrintStartup`

`function` | [progs/doomgeneric/i_cdmus.c:92](../../progs/doomgeneric/i_cdmus.c#L92)

```c
void I_CDMusPrintStartup(void)
```

---

<a id="i_cdmusplay"></a>

### `I_CDMusPlay`

`function` | [progs/doomgeneric/i_cdmus.c:107](../../progs/doomgeneric/i_cdmus.c#L107)

```c
int I_CDMusPlay(int track)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `track` | `int` |  |  |

**Returns:** `int`

---

<a id="i_cdmusstop"></a>

### `I_CDMusStop`

`function` | [progs/doomgeneric/i_cdmus.c:130](../../progs/doomgeneric/i_cdmus.c#L130)

```c
int I_CDMusStop(void)
```

**Returns:** `int`

---

<a id="i_cdmusresume"></a>

### `I_CDMusResume`

`function` | [progs/doomgeneric/i_cdmus.c:145](../../progs/doomgeneric/i_cdmus.c#L145)

```c
int I_CDMusResume(void)
```

**Returns:** `int`

---

<a id="i_cdmussetvolume"></a>

### `I_CDMusSetVolume`

`function` | [progs/doomgeneric/i_cdmus.c:160](../../progs/doomgeneric/i_cdmus.c#L160)

```c
int I_CDMusSetVolume(int volume)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `volume` | `int` |  |  |

**Returns:** `int`

---

<a id="i_cdmusfirsttrack"></a>

### `I_CDMusFirstTrack`

`function` | [progs/doomgeneric/i_cdmus.c:169](../../progs/doomgeneric/i_cdmus.c#L169)

```c
int I_CDMusFirstTrack(void)
```

**Returns:** `int`

---

<a id="i_cdmuslasttrack"></a>

### `I_CDMusLastTrack`

`function` | [progs/doomgeneric/i_cdmus.c:202](../../progs/doomgeneric/i_cdmus.c#L202)

```c
int I_CDMusLastTrack(void)
```

**Returns:** `int`

---

<a id="i_cdmustracklength"></a>

### `I_CDMusTrackLength`

`function` | [progs/doomgeneric/i_cdmus.c:219](../../progs/doomgeneric/i_cdmus.c#L219)

```c
int I_CDMusTrackLength(int track_num)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `track_num` | `int` |  |  |

**Returns:** `int`

---
