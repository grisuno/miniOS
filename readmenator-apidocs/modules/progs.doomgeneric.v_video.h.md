# `progs/doomgeneric/v_video.h`

> Source: [progs/doomgeneric/v_video.h:1](../../progs/doomgeneric/v_video.h#L1) | language `h` | coverage 7.7% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Gamma correction LUT. Functions to draw patches (by post) directly to screen. Functions to blit a block to the screen.      Needed because we are refering to patches.

## Contents

- **Functions:** [`V_SetPatchClipCallback`](#v_setpatchclipcallback), [`V_Init`](#v_init), [`V_CopyRect`](#v_copyrect), [`V_DrawPatch`](#v_drawpatch), [`V_DrawPatchFlipped`](#v_drawpatchflipped), [`V_DrawTLPatch`](#v_drawtlpatch), [`V_DrawAltTLPatch`](#v_drawalttlpatch), [`V_DrawShadowedPatch`](#v_drawshadowedpatch), [`V_DrawXlaPatch`](#v_drawxlapatch), [`V_DrawPatchDirect`](#v_drawpatchdirect), [`V_DrawBlock`](#v_drawblock), [`V_MarkRect`](#v_markrect), [`V_DrawFilledBox`](#v_drawfilledbox), [`V_DrawHorizLine`](#v_drawhorizline), [`V_DrawVertLine`](#v_drawvertline), [`V_DrawBox`](#v_drawbox), [`V_DrawRawScreen`](#v_drawrawscreen), [`V_UseBuffer`](#v_usebuffer), [`V_RestoreBuffer`](#v_restorebuffer), [`V_ScreenShot`](#v_screenshot), [`V_LoadTintTable`](#v_loadtinttable), [`V_LoadXlaTable`](#v_loadxlatable), [`V_DrawMouseSpeedBox`](#v_drawmousespeedbox)
- **Macros:** [`__V_VIDEO__`](#__v_video__), [`CENTERY`](#centery)
- **Variables:** [`dirtybox`](#dirtybox), [`tinttable`](#tinttable)

## Functions

<a id="v_setpatchclipcallback"></a>

### `V_SetPatchClipCallback`

`function` | [progs/doomgeneric/v_video.h:45](../../progs/doomgeneric/v_video.h#L45)

```c
void V_SetPatchClipCallback(vpatchclipfunc_t func);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `func` | `vpatchclipfunc_t` |  |  |

---

<a id="v_init"></a>

### `V_Init`

`function` | [progs/doomgeneric/v_video.h:49](../../progs/doomgeneric/v_video.h#L49)

```c
void V_Init (void);
```

Allocates buffer screens, call before R_Init.

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain)

---

<a id="v_copyrect"></a>

### `V_CopyRect`

`function` | [progs/doomgeneric/v_video.h:53](../../progs/doomgeneric/v_video.h#L53)

```c
void V_CopyRect(int srcx, int srcy, byte *source, int width, int height, int destx, int desty);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `srcx` | `int` |  |  |
| `srcy` | `int` |  |  |
| `source` | `byte *` |  |  |
| `width` | `int` |  |  |
| `height` | `int` |  |  |
| `destx` | `int` |  |  |
| `desty` | `int` |  |  |

*Called by:* [`STlib_drawNum`](progs.doomgeneric.st_lib.c.md#stlib_drawnum), [`STlib_updateBinIcon`](progs.doomgeneric.st_lib.c.md#stlib_updatebinicon), [`STlib_updateMultIcon`](progs.doomgeneric.st_lib.c.md#stlib_updatemulticon), [`ST_refreshBackground`](progs.doomgeneric.st_stuff.c.md#st_refreshbackground)

---

<a id="v_drawpatch"></a>

### `V_DrawPatch`

`function` | [progs/doomgeneric/v_video.h:57](../../progs/doomgeneric/v_video.h#L57)

```c
void V_DrawPatch(int x, int y, patch_t *patch);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `y` | `int` |  |  |
| `patch` | `patch_t *` |  |  |

*Called by:* [`AM_drawMarks`](progs.doomgeneric.am_map.c.md#am_drawmarks), [`D_PageDrawer`](progs.doomgeneric.d_main.c.md#d_pagedrawer), [`F_BunnyScroll`](progs.doomgeneric.f_finale.c.md#f_bunnyscroll), [`F_CastDrawer`](progs.doomgeneric.f_finale.c.md#f_castdrawer), [`F_CastPrint`](progs.doomgeneric.f_finale.c.md#f_castprint), [`F_TextWrite`](progs.doomgeneric.f_finale.c.md#f_textwrite), [`R_FillBackScreen`](progs.doomgeneric.r_draw.c.md#r_fillbackscreen), [`STlib_drawNum`](progs.doomgeneric.st_lib.c.md#stlib_drawnum), [`STlib_updateBinIcon`](progs.doomgeneric.st_lib.c.md#stlib_updatebinicon), [`STlib_updateMultIcon`](progs.doomgeneric.st_lib.c.md#stlib_updatemulticon), [`STlib_updatePercent`](progs.doomgeneric.st_lib.c.md#stlib_updatepercent), [`ST_refreshBackground`](progs.doomgeneric.st_stuff.c.md#st_refreshbackground) and 11 more

---

<a id="v_drawpatchflipped"></a>

### `V_DrawPatchFlipped`

`function` | [progs/doomgeneric/v_video.h:58](../../progs/doomgeneric/v_video.h#L58)

```c
void V_DrawPatchFlipped(int x, int y, patch_t *patch);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `y` | `int` |  |  |
| `patch` | `patch_t *` |  |  |

*Called by:* [`F_CastDrawer`](progs.doomgeneric.f_finale.c.md#f_castdrawer)

---

<a id="v_drawtlpatch"></a>

### `V_DrawTLPatch`

`function` | [progs/doomgeneric/v_video.h:59](../../progs/doomgeneric/v_video.h#L59)

```c
void V_DrawTLPatch(int x, int y, patch_t *patch);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `y` | `int` |  |  |
| `patch` | `patch_t *` |  |  |

---

<a id="v_drawalttlpatch"></a>

### `V_DrawAltTLPatch`

`function` | [progs/doomgeneric/v_video.h:60](../../progs/doomgeneric/v_video.h#L60)

```c
void V_DrawAltTLPatch(int x, int y, patch_t * patch);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `y` | `int` |  |  |
| `patch` | `patch_t *` |  |  |

---

<a id="v_drawshadowedpatch"></a>

### `V_DrawShadowedPatch`

`function` | [progs/doomgeneric/v_video.h:61](../../progs/doomgeneric/v_video.h#L61)

```c
void V_DrawShadowedPatch(int x, int y, patch_t *patch);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `y` | `int` |  |  |
| `patch` | `patch_t *` |  |  |

---

<a id="v_drawxlapatch"></a>

### `V_DrawXlaPatch`

`function` | [progs/doomgeneric/v_video.h:62](../../progs/doomgeneric/v_video.h#L62)

```c
void V_DrawXlaPatch(int x, int y, patch_t * patch);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `y` | `int` |  |  |
| `patch` | `patch_t *` |  |  |

---

<a id="v_drawpatchdirect"></a>

### `V_DrawPatchDirect`

`function` | [progs/doomgeneric/v_video.h:63](../../progs/doomgeneric/v_video.h#L63)

```c
void V_DrawPatchDirect(int x, int y, patch_t *patch);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `y` | `int` |  |  |
| `patch` | `patch_t *` |  |  |

*Called by:* [`D_Display`](progs.doomgeneric.d_main.c.md#d_display), [`HUlib_drawTextLine`](progs.doomgeneric.hu_lib.c.md#hulib_drawtextline), [`M_DrawEmptyCell`](progs.doomgeneric.m_menu.c.md#m_drawemptycell), [`M_DrawEpisode`](progs.doomgeneric.m_menu.c.md#m_drawepisode), [`M_DrawLoad`](progs.doomgeneric.m_menu.c.md#m_drawload), [`M_DrawMainMenu`](progs.doomgeneric.m_menu.c.md#m_drawmainmenu), [`M_DrawNewGame`](progs.doomgeneric.m_menu.c.md#m_drawnewgame), [`M_DrawOptions`](progs.doomgeneric.m_menu.c.md#m_drawoptions), [`M_DrawReadThis1`](progs.doomgeneric.m_menu.c.md#m_drawreadthis1), [`M_DrawReadThis2`](progs.doomgeneric.m_menu.c.md#m_drawreadthis2), [`M_DrawSave`](progs.doomgeneric.m_menu.c.md#m_drawsave), [`M_DrawSaveLoadBorder`](progs.doomgeneric.m_menu.c.md#m_drawsaveloadborder) and 5 more

---

<a id="v_drawblock"></a>

### `V_DrawBlock`

`function` | [progs/doomgeneric/v_video.h:67](../../progs/doomgeneric/v_video.h#L67)

```c
void V_DrawBlock(int x, int y, int width, int height, byte *src);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `y` | `int` |  |  |
| `width` | `int` |  |  |
| `height` | `int` |  |  |
| `src` | `byte *` |  |  |

*Called by:* [`wipe_EndScreen`](progs.doomgeneric.f_wipe.c.md#wipe_endscreen)

---

<a id="v_markrect"></a>

### `V_MarkRect`

`function` | [progs/doomgeneric/v_video.h:69](../../progs/doomgeneric/v_video.h#L69)

```c
void V_MarkRect(int x, int y, int width, int height);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `y` | `int` |  |  |
| `width` | `int` |  |  |
| `height` | `int` |  |  |

*Called by:* [`AM_Drawer`](progs.doomgeneric.am_map.c.md#am_drawer), [`F_BunnyScroll`](progs.doomgeneric.f_finale.c.md#f_bunnyscroll), [`F_TextWrite`](progs.doomgeneric.f_finale.c.md#f_textwrite), [`wipe_ScreenWipe`](progs.doomgeneric.f_wipe.c.md#wipe_screenwipe), [`R_DrawViewBorder`](progs.doomgeneric.r_draw.c.md#r_drawviewborder)

---

<a id="v_drawfilledbox"></a>

### `V_DrawFilledBox`

`function` | [progs/doomgeneric/v_video.h:71](../../progs/doomgeneric/v_video.h#L71)

```c
void V_DrawFilledBox(int x, int y, int w, int h, int c);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `y` | `int` |  |  |
| `w` | `int` |  |  |
| `h` | `int` |  |  |
| `c` | `int` |  |  |

---

<a id="v_drawhorizline"></a>

### `V_DrawHorizLine`

`function` | [progs/doomgeneric/v_video.h:72](../../progs/doomgeneric/v_video.h#L72)

```c
void V_DrawHorizLine(int x, int y, int w, int c);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `y` | `int` |  |  |
| `w` | `int` |  |  |
| `c` | `int` |  |  |

---

<a id="v_drawvertline"></a>

### `V_DrawVertLine`

`function` | [progs/doomgeneric/v_video.h:73](../../progs/doomgeneric/v_video.h#L73)

```c
void V_DrawVertLine(int x, int y, int h, int c);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `y` | `int` |  |  |
| `h` | `int` |  |  |
| `c` | `int` |  |  |

---

<a id="v_drawbox"></a>

### `V_DrawBox`

`function` | [progs/doomgeneric/v_video.h:74](../../progs/doomgeneric/v_video.h#L74)

```c
void V_DrawBox(int x, int y, int w, int h, int c);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int` |  |  |
| `y` | `int` |  |  |
| `w` | `int` |  |  |
| `h` | `int` |  |  |
| `c` | `int` |  |  |

---

<a id="v_drawrawscreen"></a>

### `V_DrawRawScreen`

`function` | [progs/doomgeneric/v_video.h:78](../../progs/doomgeneric/v_video.h#L78)

```c
void V_DrawRawScreen(byte *raw);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `raw` | `byte *` |  |  |

---

<a id="v_usebuffer"></a>

### `V_UseBuffer`

`function` | [progs/doomgeneric/v_video.h:82](../../progs/doomgeneric/v_video.h#L82)

```c
void V_UseBuffer(byte *buffer);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `buffer` | `byte *` |  |  |

*Called by:* [`R_FillBackScreen`](progs.doomgeneric.r_draw.c.md#r_fillbackscreen), [`ST_refreshBackground`](progs.doomgeneric.st_stuff.c.md#st_refreshbackground)

---

<a id="v_restorebuffer"></a>

### `V_RestoreBuffer`

`function` | [progs/doomgeneric/v_video.h:86](../../progs/doomgeneric/v_video.h#L86)

```c
void V_RestoreBuffer(void);
```

*Called by:* [`D_DoomLoop`](progs.doomgeneric.d_main.c.md#d_doomloop), [`R_FillBackScreen`](progs.doomgeneric.r_draw.c.md#r_fillbackscreen), [`ST_refreshBackground`](progs.doomgeneric.st_stuff.c.md#st_refreshbackground)

---

<a id="v_screenshot"></a>

### `V_ScreenShot`

`function` | [progs/doomgeneric/v_video.h:92](../../progs/doomgeneric/v_video.h#L92)

```c
void V_ScreenShot(char *format);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `format` | `char *` |  |  |

*Called by:* [`G_Ticker`](progs.doomgeneric.g_game.c.md#g_ticker)

---

<a id="v_loadtinttable"></a>

### `V_LoadTintTable`

`function` | [progs/doomgeneric/v_video.h:97](../../progs/doomgeneric/v_video.h#L97)

```c
void V_LoadTintTable(void);
```

---

<a id="v_loadxlatable"></a>

### `V_LoadXlaTable`

`function` | [progs/doomgeneric/v_video.h:103](../../progs/doomgeneric/v_video.h#L103)

```c
void V_LoadXlaTable(void);
```

---

<a id="v_drawmousespeedbox"></a>

### `V_DrawMouseSpeedBox`

`function` | [progs/doomgeneric/v_video.h:105](../../progs/doomgeneric/v_video.h#L105)

```c
void V_DrawMouseSpeedBox(int speed);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `speed` | `int` |  |  |

*Called by:* [`D_Display`](progs.doomgeneric.d_main.c.md#d_display)

---

## Macros

<a id="__v_video__"></a>

### `__V_VIDEO__`

`macro` | [progs/doomgeneric/v_video.h:23](../../progs/doomgeneric/v_video.h#L23)

```c
#define __V_VIDEO__
```

---

<a id="centery"></a>

### `CENTERY`

`macro` | [progs/doomgeneric/v_video.h:34](../../progs/doomgeneric/v_video.h#L34)

```c
#define CENTERY
```

---

## Variables

<a id="dirtybox"></a>

### `dirtybox`

`variable` `extern` | [progs/doomgeneric/v_video.h:37](../../progs/doomgeneric/v_video.h#L37)

```c
extern int dirtybox[4];
```

---

<a id="tinttable"></a>

### `tinttable`

`variable` `extern` | [progs/doomgeneric/v_video.h:39](../../progs/doomgeneric/v_video.h#L39)

```c
extern byte *tinttable;
```

---
