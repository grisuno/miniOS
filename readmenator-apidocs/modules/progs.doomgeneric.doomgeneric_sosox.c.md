# `progs/doomgeneric/doomgeneric_sosox.c`

> Source: [progs/doomgeneric/doomgeneric_sosox.c:1](../../progs/doomgeneric/doomgeneric_sosox.c#L1) | language `c` | coverage 10.0% | [API index](../index.md)

doomgeneric for soso os (nano-x version) TODO: get keys from X, not using direct keyboard access!

## Contents

- **Functions:** [`disable_raw_mode`](#disable_raw_mode), [`enable_raw_mode`](#enable_raw_mode), [`DG_Init`](#dg_init), [`DG_DrawFrame`](#dg_drawframe), [`DG_SleepMs`](#dg_sleepms), [`DG_GetTicksMs`](#dg_getticksms), [`DG_GetKey`](#dg_getkey), [`DG_SetWindowTitle`](#dg_setwindowtitle)
- **Macros:** [`KEYQUEUE_SIZE`](#keyqueue_size)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_progs_doomgeneric_doomgeneric_sosox_c__DG_Init(["DG_Init"])
    n_progs_doomgeneric_doomgeneric_sosox_c__enable_raw_mode(["enable_raw_mode"])
    n_progs_doomgeneric_doomgeneric_sosox_c__DG_DrawFrame(["DG_DrawFrame"])
    n_kernel_string_c__memcpy["string.memcpy"]
    n_progs_doomgeneric_doomgeneric_sosox_c__DG_Init --> n_progs_doomgeneric_doomgeneric_sosox_c__enable_raw_mode
    n_progs_doomgeneric_doomgeneric_sosox_c__DG_DrawFrame -.-> n_kernel_string_c__memcpy
```

## Functions

<a id="disable_raw_mode"></a>

### `disable_raw_mode`

`function` | [progs/doomgeneric/doomgeneric_sosox.c:102](../../progs/doomgeneric/doomgeneric_sosox.c#L102)

```c
void disable_raw_mode()
```

---

<a id="enable_raw_mode"></a>

### `enable_raw_mode`

`function` | [progs/doomgeneric/doomgeneric_sosox.c:107](../../progs/doomgeneric/doomgeneric_sosox.c#L107)

```c
void enable_raw_mode()
```

*Called by:* [`DG_Init`](#dg_init)

---

<a id="dg_init"></a>

### `DG_Init`

`function` | [progs/doomgeneric/doomgeneric_sosox.c:117](../../progs/doomgeneric/doomgeneric_sosox.c#L117)

```c
void DG_Init()
```

*Calls:* [`enable_raw_mode`](#enable_raw_mode)

---

<a id="dg_drawframe"></a>

### `DG_DrawFrame`

`function` | [progs/doomgeneric/doomgeneric_sosox.c:187](../../progs/doomgeneric/doomgeneric_sosox.c#L187)

```c
void DG_DrawFrame()
```

*Calls:* [`memcpy`](kernel.string.c.md#memcpy)

---

<a id="dg_sleepms"></a>

### `DG_SleepMs`

`function` | [progs/doomgeneric/doomgeneric_sosox.c:225](../../progs/doomgeneric/doomgeneric_sosox.c#L225)

```c
void DG_SleepMs(uint32_t ms)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ms` | `uint32_t` |  |  |

---

<a id="dg_getticksms"></a>

### `DG_GetTicksMs`

`function` | [progs/doomgeneric/doomgeneric_sosox.c:230](../../progs/doomgeneric/doomgeneric_sosox.c#L230)

```c
uint32_t DG_GetTicksMs()
```

**Returns:** `uint32_t`

---

<a id="dg_getkey"></a>

### `DG_GetKey`

`function` | [progs/doomgeneric/doomgeneric_sosox.c:235](../../progs/doomgeneric/doomgeneric_sosox.c#L235)

```c
int DG_GetKey(int* pressed, unsigned char* doomKey)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `pressed` | `int*` |  |  |
| `doomKey` | `unsigned char*` |  |  |

**Returns:** `int`

---

<a id="dg_setwindowtitle"></a>

### `DG_SetWindowTitle`

`function` | [progs/doomgeneric/doomgeneric_sosox.c:256](../../progs/doomgeneric/doomgeneric_sosox.c#L256)

```c
void DG_SetWindowTitle(const char * title)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `title` | `char *` |  |  |

---

## Macros

<a id="keyqueue_size"></a>

### `KEYQUEUE_SIZE`

`macro` | [progs/doomgeneric/doomgeneric_sosox.c:24](../../progs/doomgeneric/doomgeneric_sosox.c#L24)

```c
#define KEYQUEUE_SIZE
```

---
