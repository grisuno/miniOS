# `progs/doomgeneric/doomgeneric_xlib.c`

> Source: [progs/doomgeneric/doomgeneric_xlib.c:1](../../progs/doomgeneric/doomgeneric_xlib.c#L1) | language `c` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`DG_Init`](#dg_init), [`DG_DrawFrame`](#dg_drawframe), [`DG_SleepMs`](#dg_sleepms), [`DG_GetTicksMs`](#dg_getticksms), [`DG_GetKey`](#dg_getkey), [`DG_SetWindowTitle`](#dg_setwindowtitle)
- **Macros:** [`KEYQUEUE_SIZE`](#keyqueue_size)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_progs_doomgeneric_doomgeneric_xlib_c__DG_Init(["DG_Init"])
    n_kernel_string_c__memset["string.memset"]
    n_progs_doomgeneric_doomgeneric_xlib_c__DG_GetTicksMs(["DG_GetTicksMs"])
    n_headers_tls_port_h__gettimeofday["tls_port.gettimeofday"]
    n_progs_doomgeneric_doomgeneric_xlib_c__DG_Init -.-> n_kernel_string_c__memset
    n_progs_doomgeneric_doomgeneric_xlib_c__DG_GetTicksMs -.-> n_headers_tls_port_h__gettimeofday
```

## Functions

<a id="dg_init"></a>

### `DG_Init`

`function` | [progs/doomgeneric/doomgeneric_xlib.c:79](../../progs/doomgeneric/doomgeneric_xlib.c#L79)

```c
void DG_Init()
```

*Calls:* [`memset`](kernel.string.c.md#memset)

---

<a id="dg_drawframe"></a>

### `DG_DrawFrame`

`function` | [progs/doomgeneric/doomgeneric_xlib.c:127](../../progs/doomgeneric/doomgeneric_xlib.c#L127)

```c
void DG_DrawFrame()
```

---

<a id="dg_sleepms"></a>

### `DG_SleepMs`

`function` | [progs/doomgeneric/doomgeneric_xlib.c:172](../../progs/doomgeneric/doomgeneric_xlib.c#L172)

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

`function` | [progs/doomgeneric/doomgeneric_xlib.c:177](../../progs/doomgeneric/doomgeneric_xlib.c#L177)

```c
uint32_t DG_GetTicksMs()
```

**Returns:** `uint32_t`

*Calls:* [`gettimeofday`](headers.tls_port.h.md#gettimeofday)

---

<a id="dg_getkey"></a>

### `DG_GetKey`

`function` | [progs/doomgeneric/doomgeneric_xlib.c:187](../../progs/doomgeneric/doomgeneric_xlib.c#L187)

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

`function` | [progs/doomgeneric/doomgeneric_xlib.c:208](../../progs/doomgeneric/doomgeneric_xlib.c#L208)

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

`macro` | [progs/doomgeneric/doomgeneric_xlib.c:21](../../progs/doomgeneric/doomgeneric_xlib.c#L21)

```c
#define KEYQUEUE_SIZE
```

---
