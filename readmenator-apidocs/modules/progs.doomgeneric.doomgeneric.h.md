# `progs/doomgeneric/doomgeneric.h`

> Source: [progs/doomgeneric/doomgeneric.h:1](../../progs/doomgeneric/doomgeneric.h#L1) | language `h` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`DG_Init`](#dg_init), [`DG_DrawFrame`](#dg_drawframe), [`DG_SleepMs`](#dg_sleepms), [`DG_GetTicksMs`](#dg_getticksms), [`DG_GetKey`](#dg_getkey), [`DG_SetWindowTitle`](#dg_setwindowtitle)
- **Macros:** [`DOOM_GENERIC`](#doom_generic), [`DOOMGENERIC_RESX`](#doomgeneric_resx), [`DOOMGENERIC_RESY`](#doomgeneric_resy)
- **Variables:** [`DG_ScreenBuffer`](#dg_screenbuffer)

## Functions

<a id="dg_init"></a>

### `DG_Init`

`function` | [progs/doomgeneric/doomgeneric.h:14](../../progs/doomgeneric/doomgeneric.h#L14)

```c
void DG_Init();
```

*Called by:* [`dg_Create`](progs.doomgeneric.doomgeneric.c.md#dg_create)

---

<a id="dg_drawframe"></a>

### `DG_DrawFrame`

`function` | [progs/doomgeneric/doomgeneric.h:15](../../progs/doomgeneric/doomgeneric.h#L15)

```c
void DG_DrawFrame();
```

*Called by:* [`I_FinishUpdate`](progs.doomgeneric.i_video.c.md#i_finishupdate)

---

<a id="dg_sleepms"></a>

### `DG_SleepMs`

`function` | [progs/doomgeneric/doomgeneric.h:16](../../progs/doomgeneric/doomgeneric.h#L16)

```c
void DG_SleepMs(uint32_t ms);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ms` | `uint32_t` |  |  |

*Called by:* [`I_Sleep`](progs.doomgeneric.i_timer.c.md#i_sleep)

---

<a id="dg_getticksms"></a>

### `DG_GetTicksMs`

`function` | [progs/doomgeneric/doomgeneric.h:17](../../progs/doomgeneric/doomgeneric.h#L17)

```c
uint32_t DG_GetTicksMs();
```

**Returns:** `uint32_t`

*Called by:* [`I_GetTicks`](progs.doomgeneric.i_timer.c.md#i_getticks)

---

<a id="dg_getkey"></a>

### `DG_GetKey`

`function` | [progs/doomgeneric/doomgeneric.h:18](../../progs/doomgeneric/doomgeneric.h#L18)

```c
int DG_GetKey(int* pressed, unsigned char* key);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `pressed` | `int*` |  |  |
| `key` | `unsigned char*` |  |  |

**Returns:** `int`

*Called by:* [`I_GetEvent`](progs.doomgeneric.i_input.c.md#i_getevent)

---

<a id="dg_setwindowtitle"></a>

### `DG_SetWindowTitle`

`function` | [progs/doomgeneric/doomgeneric.h:19](../../progs/doomgeneric/doomgeneric.h#L19)

```c
void DG_SetWindowTitle(const char * title);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `title` | `char *` |  |  |

*Called by:* [`I_SetWindowTitle`](progs.doomgeneric.i_video.c.md#i_setwindowtitle)

---

## Macros

<a id="doom_generic"></a>

### `DOOM_GENERIC`

`macro` | [progs/doomgeneric/doomgeneric.h:2](../../progs/doomgeneric/doomgeneric.h#L2)

```c
#define DOOM_GENERIC
```

---

<a id="doomgeneric_resx"></a>

### `DOOMGENERIC_RESX`

`macro` | [progs/doomgeneric/doomgeneric.h:7](../../progs/doomgeneric/doomgeneric.h#L7)

```c
#define DOOMGENERIC_RESX
```

---

<a id="doomgeneric_resy"></a>

### `DOOMGENERIC_RESY`

`macro` | [progs/doomgeneric/doomgeneric.h:8](../../progs/doomgeneric/doomgeneric.h#L8)

```c
#define DOOMGENERIC_RESY
```

---

## Variables

<a id="dg_screenbuffer"></a>

### `DG_ScreenBuffer`

`variable` `extern` | [progs/doomgeneric/doomgeneric.h:11](../../progs/doomgeneric/doomgeneric.h#L11)

```c
extern uint32_t* DG_ScreenBuffer;
```

---
