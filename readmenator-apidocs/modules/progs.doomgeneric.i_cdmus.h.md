# `progs/doomgeneric/i_cdmus.h`

> Source: [progs/doomgeneric/i_cdmus.h:1](../../progs/doomgeneric/i_cdmus.h#L1) | language `h` | coverage 5.6% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 1993-2008 Raven Software  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.   i_cdmus.h

## Contents

- **Functions:** [`I_CDMusInit`](#i_cdmusinit), [`I_CDMusPrintStartup`](#i_cdmusprintstartup), [`I_CDMusPlay`](#i_cdmusplay), [`I_CDMusStop`](#i_cdmusstop), [`I_CDMusResume`](#i_cdmusresume), [`I_CDMusSetVolume`](#i_cdmussetvolume), [`I_CDMusFirstTrack`](#i_cdmusfirsttrack), [`I_CDMusLastTrack`](#i_cdmuslasttrack), [`I_CDMusTrackLength`](#i_cdmustracklength)
- **Macros:** [`__ICDMUS__`](#__icdmus__), [`CDERR_NOTINSTALLED`](#cderr_notinstalled), [`CDERR_NOAUDIOSUPPORT`](#cderr_noaudiosupport), [`CDERR_NOAUDIOTRACKS`](#cderr_noaudiotracks), [`CDERR_BADDRIVE`](#cderr_baddrive), [`CDERR_BADTRACK`](#cderr_badtrack), [`CDERR_IOCTLBUFFMEM`](#cderr_ioctlbuffmem), [`CDERR_DEVREQBASE`](#cderr_devreqbase)
- **Variables:** [`cd_Error`](#cd_error)

## Functions

<a id="i_cdmusinit"></a>

### `I_CDMusInit`

`function` | [progs/doomgeneric/i_cdmus.h:31](../../progs/doomgeneric/i_cdmus.h#L31)

```c
int I_CDMusInit(void);
```

**Returns:** `int`

---

<a id="i_cdmusprintstartup"></a>

### `I_CDMusPrintStartup`

`function` | [progs/doomgeneric/i_cdmus.h:32](../../progs/doomgeneric/i_cdmus.h#L32)

```c
void I_CDMusPrintStartup(void);
```

---

<a id="i_cdmusplay"></a>

### `I_CDMusPlay`

`function` | [progs/doomgeneric/i_cdmus.h:33](../../progs/doomgeneric/i_cdmus.h#L33)

```c
int I_CDMusPlay(int track);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `track` | `int` |  |  |

**Returns:** `int`

---

<a id="i_cdmusstop"></a>

### `I_CDMusStop`

`function` | [progs/doomgeneric/i_cdmus.h:34](../../progs/doomgeneric/i_cdmus.h#L34)

```c
int I_CDMusStop(void);
```

**Returns:** `int`

---

<a id="i_cdmusresume"></a>

### `I_CDMusResume`

`function` | [progs/doomgeneric/i_cdmus.h:35](../../progs/doomgeneric/i_cdmus.h#L35)

```c
int I_CDMusResume(void);
```

**Returns:** `int`

---

<a id="i_cdmussetvolume"></a>

### `I_CDMusSetVolume`

`function` | [progs/doomgeneric/i_cdmus.h:36](../../progs/doomgeneric/i_cdmus.h#L36)

```c
int I_CDMusSetVolume(int volume);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `volume` | `int` |  |  |

**Returns:** `int`

---

<a id="i_cdmusfirsttrack"></a>

### `I_CDMusFirstTrack`

`function` | [progs/doomgeneric/i_cdmus.h:37](../../progs/doomgeneric/i_cdmus.h#L37)

```c
int I_CDMusFirstTrack(void);
```

**Returns:** `int`

---

<a id="i_cdmuslasttrack"></a>

### `I_CDMusLastTrack`

`function` | [progs/doomgeneric/i_cdmus.h:38](../../progs/doomgeneric/i_cdmus.h#L38)

```c
int I_CDMusLastTrack(void);
```

**Returns:** `int`

---

<a id="i_cdmustracklength"></a>

### `I_CDMusTrackLength`

`function` | [progs/doomgeneric/i_cdmus.h:39](../../progs/doomgeneric/i_cdmus.h#L39)

```c
int I_CDMusTrackLength(int track);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `track` | `int` |  |  |

**Returns:** `int`

---

## Macros

<a id="__icdmus__"></a>

### `__ICDMUS__`

`macro` | [progs/doomgeneric/i_cdmus.h:19](../../progs/doomgeneric/i_cdmus.h#L19)

```c
#define __ICDMUS__
```

---

<a id="cderr_notinstalled"></a>

### `CDERR_NOTINSTALLED`

`macro` | [progs/doomgeneric/i_cdmus.h:21](../../progs/doomgeneric/i_cdmus.h#L21)

```c
#define CDERR_NOTINSTALLED
```

---

<a id="cderr_noaudiosupport"></a>

### `CDERR_NOAUDIOSUPPORT`

`macro` | [progs/doomgeneric/i_cdmus.h:22](../../progs/doomgeneric/i_cdmus.h#L22)

```c
#define CDERR_NOAUDIOSUPPORT
```

---

<a id="cderr_noaudiotracks"></a>

### `CDERR_NOAUDIOTRACKS`

`macro` | [progs/doomgeneric/i_cdmus.h:23](../../progs/doomgeneric/i_cdmus.h#L23)

```c
#define CDERR_NOAUDIOTRACKS
```

---

<a id="cderr_baddrive"></a>

### `CDERR_BADDRIVE`

`macro` | [progs/doomgeneric/i_cdmus.h:24](../../progs/doomgeneric/i_cdmus.h#L24)

```c
#define CDERR_BADDRIVE
```

---

<a id="cderr_badtrack"></a>

### `CDERR_BADTRACK`

`macro` | [progs/doomgeneric/i_cdmus.h:25](../../progs/doomgeneric/i_cdmus.h#L25)

```c
#define CDERR_BADTRACK
```

---

<a id="cderr_ioctlbuffmem"></a>

### `CDERR_IOCTLBUFFMEM`

`macro` | [progs/doomgeneric/i_cdmus.h:26](../../progs/doomgeneric/i_cdmus.h#L26)

```c
#define CDERR_IOCTLBUFFMEM
```

---

<a id="cderr_devreqbase"></a>

### `CDERR_DEVREQBASE`

`macro` | [progs/doomgeneric/i_cdmus.h:27](../../progs/doomgeneric/i_cdmus.h#L27)

```c
#define CDERR_DEVREQBASE
```

---

## Variables

<a id="cd_error"></a>

### `cd_Error`

`variable` `extern` | [progs/doomgeneric/i_cdmus.h:29](../../progs/doomgeneric/i_cdmus.h#L29)

```c
extern int cd_Error;
```

---
