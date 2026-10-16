# `progs/doomgeneric/tables.h`

> Source: [progs/doomgeneric/tables.h:1](../../progs/doomgeneric/tables.h#L1) | language `h` | coverage 22.2% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 1993-2008 Raven Software Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Lookup tables. Do not try to look them up :-). In the order of appearance:  int finetangent[4096]  - Tangens LUT. Should work with BAM fairly well (12 of 16bit, effectively, by shifting).  int finesine[10240]           - Sine lookup. Guess what, serves as cosine, too. Remarkable thing is, how to use BAMs with this?  int tantoangle[2049] - ArcTan LUT, maps tan(angle) to angle fast. Gotta search.

## Contents

- **Type Aliases:** [`angle_t`](#angle_t)
- **Functions:** [`SlopeDiv`](#slopediv)
- **Macros:** [`__TABLES__`](#__tables__), [`FINEANGLES`](#fineangles), [`FINEMASK`](#finemask), [`ANGLETOFINESHIFT`](#angletofineshift), [`ANG45`](#ang45), [`ANG90`](#ang90), [`ANG180`](#ang180), [`ANG270`](#ang270), [`ANG_MAX`](#ang_max), [`ANG1`](#ang1), [`ANG60`](#ang60), [`ANG1_X`](#ang1_x), [`SLOPERANGE`](#sloperange), [`SLOPEBITS`](#slopebits), [`DBITS`](#dbits)
- **Variables:** [`finesine`](#finesine), [`finecosine`](#finecosine), [`finetangent`](#finetangent), [`tantoangle`](#tantoangle)

## Type Aliases

<a id="angle_t"></a>

### `angle_t`

`type_alias` | [progs/doomgeneric/tables.h:80](../../progs/doomgeneric/tables.h#L80)

```c
typedef unsigned angle_t;
```

define SLOPERANGE               2048 define SLOPEBITS           11 define DBITS                 (FRACBITS-SLOPEBITS)

---

## Functions

<a id="slopediv"></a>

### `SlopeDiv`

`function` | [progs/doomgeneric/tables.h:92](../../progs/doomgeneric/tables.h#L92)

```c
int SlopeDiv(unsigned int num, unsigned int den);
```

Utility function, called by R_PointToAngle.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `num` | `unsigned int` |  |  |
| `den` | `unsigned int` |  |  |

**Returns:** `int`

---

## Macros

<a id="__tables__"></a>

### `__TABLES__`

`macro` | [progs/doomgeneric/tables.h:35](../../progs/doomgeneric/tables.h#L35)

```c
#define __TABLES__
```

---

<a id="fineangles"></a>

### `FINEANGLES`

`macro` | [progs/doomgeneric/tables.h:41](../../progs/doomgeneric/tables.h#L41)

```c
#define FINEANGLES
```

---

<a id="finemask"></a>

### `FINEMASK`

`macro` | [progs/doomgeneric/tables.h:42](../../progs/doomgeneric/tables.h#L42)

```c
#define FINEMASK
```

---

<a id="angletofineshift"></a>

### `ANGLETOFINESHIFT`

`macro` | [progs/doomgeneric/tables.h:46](../../progs/doomgeneric/tables.h#L46)

```c
#define ANGLETOFINESHIFT
```

0x100000000 to 0x2000

---

<a id="ang45"></a>

### `ANG45`

`macro` | [progs/doomgeneric/tables.h:63](../../progs/doomgeneric/tables.h#L63)

```c
#define ANG45
```

---

<a id="ang90"></a>

### `ANG90`

`macro` | [progs/doomgeneric/tables.h:64](../../progs/doomgeneric/tables.h#L64)

```c
#define ANG90
```

---

<a id="ang180"></a>

### `ANG180`

`macro` | [progs/doomgeneric/tables.h:65](../../progs/doomgeneric/tables.h#L65)

```c
#define ANG180
```

---

<a id="ang270"></a>

### `ANG270`

`macro` | [progs/doomgeneric/tables.h:66](../../progs/doomgeneric/tables.h#L66)

```c
#define ANG270
```

---

<a id="ang_max"></a>

### `ANG_MAX`

`macro` | [progs/doomgeneric/tables.h:67](../../progs/doomgeneric/tables.h#L67)

```c
#define ANG_MAX
```

---

<a id="ang1"></a>

### `ANG1`

`macro` | [progs/doomgeneric/tables.h:69](../../progs/doomgeneric/tables.h#L69)

```c
#define ANG1
```

---

<a id="ang60"></a>

### `ANG60`

`macro` | [progs/doomgeneric/tables.h:70](../../progs/doomgeneric/tables.h#L70)

```c
#define ANG60
```

---

<a id="ang1_x"></a>

### `ANG1_X`

`macro` | [progs/doomgeneric/tables.h:75](../../progs/doomgeneric/tables.h#L75)

```c
#define ANG1_X
```

---

<a id="sloperange"></a>

### `SLOPERANGE`

`macro` | [progs/doomgeneric/tables.h:77](../../progs/doomgeneric/tables.h#L77)

```c
#define SLOPERANGE
```

---

<a id="slopebits"></a>

### `SLOPEBITS`

`macro` | [progs/doomgeneric/tables.h:78](../../progs/doomgeneric/tables.h#L78)

```c
#define SLOPEBITS
```

---

<a id="dbits"></a>

### `DBITS`

`macro` | [progs/doomgeneric/tables.h:79](../../progs/doomgeneric/tables.h#L79)

```c
#define DBITS
```

---

## Variables

<a id="finesine"></a>

### `finesine`

`variable` `const` `extern` | [progs/doomgeneric/tables.h:49](../../progs/doomgeneric/tables.h#L49)

```c
extern const fixed_t finesine[5*FINEANGLES/4];
```

Effective size is 10240.

---

<a id="finecosine"></a>

### `finecosine`

`variable` `const` `extern` | [progs/doomgeneric/tables.h:52](../../progs/doomgeneric/tables.h#L52)

```c
extern const fixed_t *finecosine;
```

Re-use data, is just PI/2 pahse shift.

---

<a id="finetangent"></a>

### `finetangent`

`variable` `const` `extern` | [progs/doomgeneric/tables.h:56](../../progs/doomgeneric/tables.h#L56)

```c
extern const fixed_t finetangent[FINEANGLES/2];
```

Effective size is 4096.

---

<a id="tantoangle"></a>

### `tantoangle`

`variable` `const` `extern` | [progs/doomgeneric/tables.h:87](../../progs/doomgeneric/tables.h#L87)

```c
extern const angle_t tantoangle[SLOPERANGE+1];
```

Effective size is 2049; The +1 size is to handle the case when x==y without additional checking.

---
