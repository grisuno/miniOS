# `progs/doomgeneric/r_main.h`

> Source: [progs/doomgeneric/r_main.h:1](../../progs/doomgeneric/r_main.h#L1) | language `h` | coverage 33.3% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: System specific interface stuff.          POV related.

## Contents

- **Functions:** [`void`](#void), [`R_PointOnSide`](#r_pointonside), [`R_PointOnSegSide`](#r_pointonsegside), [`R_PointToAngle`](#r_pointtoangle), [`R_PointToAngle2`](#r_pointtoangle2), [`R_PointToDist`](#r_pointtodist), [`R_ScaleFromGlobalAngle`](#r_scalefromglobalangle), [`R_PointInSubsector`](#r_pointinsubsector), [`R_AddPointToBox`](#r_addpointtobox), [`R_RenderPlayerView`](#r_renderplayerview), [`R_Init`](#r_init), [`R_SetViewSize`](#r_setviewsize)
- **Macros:** [`__R_MAIN__`](#__r_main__), [`LIGHTLEVELS`](#lightlevels), [`LIGHTSEGSHIFT`](#lightsegshift), [`MAXLIGHTSCALE`](#maxlightscale), [`LIGHTSCALESHIFT`](#lightscaleshift), [`MAXLIGHTZ`](#maxlightz), [`LIGHTZSHIFT`](#lightzshift), [`NUMCOLORMAPS`](#numcolormaps)
- **Variables:** [`viewcos`](#viewcos), [`viewsin`](#viewsin), [`viewwindowx`](#viewwindowx), [`viewwindowy`](#viewwindowy), [`centerx`](#centerx), [`centery`](#centery), [`centerxfrac`](#centerxfrac), [`centeryfrac`](#centeryfrac), [`projection`](#projection), [`validcount`](#validcount), [`linecount`](#linecount), [`loopcount`](#loopcount), [`scalelightfixed`](#scalelightfixed), [`extralight`](#extralight), [`fixedcolormap`](#fixedcolormap), [`detailshift`](#detailshift)

## Functions

<a id="void"></a>

### `void`

`function` `extern` | [progs/doomgeneric/r_main.h:92](../../progs/doomgeneric/r_main.h#L92)

```c
extern void (*colfunc) (void);
```

Function pointers to switch refresh/drawing functions.

Used to select shadow mode etc.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `colfunc` |  |  |  |

*Called by:* [`pci_bar_base`](headers.drivers.pci.h.md#pci_bar_base), [`pci_bar_count`](headers.drivers.pci.h.md#pci_bar_count), [`pci_bar_is_64bit`](headers.drivers.pci.h.md#pci_bar_is_64bit), [`pci_bar_is_io`](headers.drivers.pci.h.md#pci_bar_is_io), [`pci_bar_relocate`](headers.drivers.pci.h.md#pci_bar_relocate), [`pci_bar_restore`](headers.drivers.pci.h.md#pci_bar_restore), [`pci_bar_size`](headers.drivers.pci.h.md#pci_bar_size), [`pci_cfg_read`](headers.drivers.pci.h.md#pci_cfg_read), [`pci_cfg_read8`](headers.drivers.pci.h.md#pci_cfg_read8), [`pci_cfg_write`](headers.drivers.pci.h.md#pci_cfg_write), [`pci_cfg_write8`](headers.drivers.pci.h.md#pci_cfg_write8), [`pci_find`](headers.drivers.pci.h.md#pci_find) and 5 more

---

<a id="r_pointonside"></a>

### `R_PointOnSide`

`function` | [progs/doomgeneric/r_main.h:103](../../progs/doomgeneric/r_main.h#L103)

```c
int R_PointOnSide ( fixed_t x, fixed_t y, node_t* node );
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `fixed_t` |  |  |
| `y` | `fixed_t` |  |  |
| `node` | `node_t*` |  |  |

**Returns:** `int`

*Called by:* [`R_RenderBSPNode`](progs.doomgeneric.r_bsp.c.md#r_renderbspnode)

---

<a id="r_pointonsegside"></a>

### `R_PointOnSegSide`

`function` | [progs/doomgeneric/r_main.h:109](../../progs/doomgeneric/r_main.h#L109)

```c
int R_PointOnSegSide ( fixed_t x, fixed_t y, seg_t* line );
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `fixed_t` |  |  |
| `y` | `fixed_t` |  |  |
| `line` | `seg_t*` |  |  |

**Returns:** `int`

---

<a id="r_pointtoangle"></a>

### `R_PointToAngle`

`function` | [progs/doomgeneric/r_main.h:115](../../progs/doomgeneric/r_main.h#L115)

```c
angle_t R_PointToAngle ( fixed_t x, fixed_t y );
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `fixed_t` |  |  |
| `y` | `fixed_t` |  |  |

**Returns:** `angle_t`

*Called by:* [`R_AddLine`](progs.doomgeneric.r_bsp.c.md#r_addline), [`R_CheckBBox`](progs.doomgeneric.r_bsp.c.md#r_checkbbox)

---

<a id="r_pointtoangle2"></a>

### `R_PointToAngle2`

`function` | [progs/doomgeneric/r_main.h:120](../../progs/doomgeneric/r_main.h#L120)

```c
angle_t R_PointToAngle2 ( fixed_t x1, fixed_t y1, fixed_t x2, fixed_t y2 );
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x1` | `fixed_t` |  |  |
| `y1` | `fixed_t` |  |  |
| `x2` | `fixed_t` |  |  |
| `y2` | `fixed_t` |  |  |

**Returns:** `angle_t`

---

<a id="r_pointtodist"></a>

### `R_PointToDist`

`function` | [progs/doomgeneric/r_main.h:127](../../progs/doomgeneric/r_main.h#L127)

```c
fixed_t R_PointToDist ( fixed_t x, fixed_t y );
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `fixed_t` |  |  |
| `y` | `fixed_t` |  |  |

**Returns:** `fixed_t`

---

<a id="r_scalefromglobalangle"></a>

### `R_ScaleFromGlobalAngle`

`function` | [progs/doomgeneric/r_main.h:132](../../progs/doomgeneric/r_main.h#L132)

```c
fixed_t R_ScaleFromGlobalAngle (angle_t visangle);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `visangle` | `angle_t` |  |  |

**Returns:** `fixed_t`

---

<a id="r_pointinsubsector"></a>

### `R_PointInSubsector`

`function` | [progs/doomgeneric/r_main.h:135](../../progs/doomgeneric/r_main.h#L135)

```c
subsector_t* R_PointInSubsector ( fixed_t x, fixed_t y );
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `fixed_t` |  |  |
| `y` | `fixed_t` |  |  |

**Returns:** `subsector_t*`

---

<a id="r_addpointtobox"></a>

### `R_AddPointToBox`

`function` | [progs/doomgeneric/r_main.h:140](../../progs/doomgeneric/r_main.h#L140)

```c
void R_AddPointToBox ( int x, int y, fixed_t* box );
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `y` | `int` |  |  |
| `box` | `fixed_t*` |  |  |

---

<a id="r_renderplayerview"></a>

### `R_RenderPlayerView`

`function` | [progs/doomgeneric/r_main.h:152](../../progs/doomgeneric/r_main.h#L152)

```c
void R_RenderPlayerView (player_t *player);
```

Called by G_Drawer.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `player` | `player_t *` |  |  |

---

<a id="r_init"></a>

### `R_Init`

`function` | [progs/doomgeneric/r_main.h:155](../../progs/doomgeneric/r_main.h#L155)

```c
void R_Init (void);
```

Called by startup code.

---

<a id="r_setviewsize"></a>

### `R_SetViewSize`

`function` | [progs/doomgeneric/r_main.h:158](../../progs/doomgeneric/r_main.h#L158)

```c
void R_SetViewSize (int blocks, int detail);
```

Called by M_Responder.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `blocks` | `int` |  |  |
| `detail` | `int` |  |  |

---

## Macros

<a id="__r_main__"></a>

### `__R_MAIN__`

`macro` | [progs/doomgeneric/r_main.h:21](../../progs/doomgeneric/r_main.h#L21)

```c
#define __R_MAIN__
```

---

<a id="lightlevels"></a>

### `LIGHTLEVELS`

`macro` | [progs/doomgeneric/r_main.h:61](../../progs/doomgeneric/r_main.h#L61)

```c
#define LIGHTLEVELS
```

Lighting constants.

Now why not 32 levels here?

---

<a id="lightsegshift"></a>

### `LIGHTSEGSHIFT`

`macro` | [progs/doomgeneric/r_main.h:62](../../progs/doomgeneric/r_main.h#L62)

```c
#define LIGHTSEGSHIFT
```

---

<a id="maxlightscale"></a>

### `MAXLIGHTSCALE`

`macro` | [progs/doomgeneric/r_main.h:64](../../progs/doomgeneric/r_main.h#L64)

```c
#define MAXLIGHTSCALE
```

---

<a id="lightscaleshift"></a>

### `LIGHTSCALESHIFT`

`macro` | [progs/doomgeneric/r_main.h:65](../../progs/doomgeneric/r_main.h#L65)

```c
#define LIGHTSCALESHIFT
```

---

<a id="maxlightz"></a>

### `MAXLIGHTZ`

`macro` | [progs/doomgeneric/r_main.h:66](../../progs/doomgeneric/r_main.h#L66)

```c
#define MAXLIGHTZ
```

---

<a id="lightzshift"></a>

### `LIGHTZSHIFT`

`macro` | [progs/doomgeneric/r_main.h:67](../../progs/doomgeneric/r_main.h#L67)

```c
#define LIGHTZSHIFT
```

---

<a id="numcolormaps"></a>

### `NUMCOLORMAPS`

`macro` | [progs/doomgeneric/r_main.h:79](../../progs/doomgeneric/r_main.h#L79)

```c
#define NUMCOLORMAPS
```

Number of diminishing brightness levels.

There a 0-31, i.e. 32 LUT in the COLORMAP lump.

---

## Variables

<a id="viewcos"></a>

### `viewcos`

`variable` `extern` | [progs/doomgeneric/r_main.h:32](../../progs/doomgeneric/r_main.h#L32)

```c
extern fixed_t viewcos;
```

POV related.

---

<a id="viewsin"></a>

### `viewsin`

`variable` `extern` | [progs/doomgeneric/r_main.h:33](../../progs/doomgeneric/r_main.h#L33)

```c
extern fixed_t viewsin;
```

---

<a id="viewwindowx"></a>

### `viewwindowx`

`variable` `extern` | [progs/doomgeneric/r_main.h:35](../../progs/doomgeneric/r_main.h#L35)

```c
extern int viewwindowx;
```

---

<a id="viewwindowy"></a>

### `viewwindowy`

`variable` `extern` | [progs/doomgeneric/r_main.h:36](../../progs/doomgeneric/r_main.h#L36)

```c
extern int viewwindowy;
```

---

<a id="centerx"></a>

### `centerx`

`variable` `extern` | [progs/doomgeneric/r_main.h:40](../../progs/doomgeneric/r_main.h#L40)

```c
extern int centerx;
```

---

<a id="centery"></a>

### `centery`

`variable` `extern` | [progs/doomgeneric/r_main.h:41](../../progs/doomgeneric/r_main.h#L41)

```c
extern int centery;
```

---

<a id="centerxfrac"></a>

### `centerxfrac`

`variable` `extern` | [progs/doomgeneric/r_main.h:43](../../progs/doomgeneric/r_main.h#L43)

```c
extern fixed_t centerxfrac;
```

---

<a id="centeryfrac"></a>

### `centeryfrac`

`variable` `extern` | [progs/doomgeneric/r_main.h:44](../../progs/doomgeneric/r_main.h#L44)

```c
extern fixed_t centeryfrac;
```

---

<a id="projection"></a>

### `projection`

`variable` `extern` | [progs/doomgeneric/r_main.h:45](../../progs/doomgeneric/r_main.h#L45)

```c
extern fixed_t projection;
```

---

<a id="validcount"></a>

### `validcount`

`variable` `extern` | [progs/doomgeneric/r_main.h:47](../../progs/doomgeneric/r_main.h#L47)

```c
extern int validcount;
```

---

<a id="linecount"></a>

### `linecount`

`variable` `extern` | [progs/doomgeneric/r_main.h:49](../../progs/doomgeneric/r_main.h#L49)

```c
extern int linecount;
```

---

<a id="loopcount"></a>

### `loopcount`

`variable` `extern` | [progs/doomgeneric/r_main.h:50](../../progs/doomgeneric/r_main.h#L50)

```c
extern int loopcount;
```

---

<a id="scalelightfixed"></a>

### `scalelightfixed`

`variable` `extern` | [progs/doomgeneric/r_main.h:70](../../progs/doomgeneric/r_main.h#L70)

```c
extern lighttable_t* scalelightfixed[MAXLIGHTSCALE];
```

---

<a id="extralight"></a>

### `extralight`

`variable` `extern` | [progs/doomgeneric/r_main.h:73](../../progs/doomgeneric/r_main.h#L73)

```c
extern int extralight;
```

---

<a id="fixedcolormap"></a>

### `fixedcolormap`

`variable` `extern` | [progs/doomgeneric/r_main.h:74](../../progs/doomgeneric/r_main.h#L74)

```c
extern lighttable_t* fixedcolormap;
```

---

<a id="detailshift"></a>

### `detailshift`

`variable` `extern` | [progs/doomgeneric/r_main.h:85](../../progs/doomgeneric/r_main.h#L85)

```c
extern int detailshift;
```

Blocky/low detail mode.

B remove this? 0 = high, 1 = low

---
