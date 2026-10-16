# `progs/doomgeneric/doomgeneric_win.c`

> Source: [progs/doomgeneric/doomgeneric_win.c:1](../../progs/doomgeneric/doomgeneric_win.c#L1) | language `c` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`DG_Init`](#dg_init), [`DG_DrawFrame`](#dg_drawframe), [`DG_SleepMs`](#dg_sleepms), [`DG_GetTicksMs`](#dg_getticksms), [`DG_GetKey`](#dg_getkey), [`DG_SetWindowTitle`](#dg_setwindowtitle)
- **Macros:** [`KEYQUEUE_SIZE`](#keyqueue_size)

## Functions

<a id="dg_init"></a>

### `DG_Init`

`function` | [progs/doomgeneric/doomgeneric_win.c:95](../../progs/doomgeneric/doomgeneric_win.c#L95)

```c
void DG_Init()
```

---

<a id="dg_drawframe"></a>

### `DG_DrawFrame`

`function` | [progs/doomgeneric/doomgeneric_win.c:146](../../progs/doomgeneric/doomgeneric_win.c#L146)

```c
void DG_DrawFrame()
```

---

<a id="dg_sleepms"></a>

### `DG_SleepMs`

`function` | [progs/doomgeneric/doomgeneric_win.c:162](../../progs/doomgeneric/doomgeneric_win.c#L162)

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

`function` | [progs/doomgeneric/doomgeneric_win.c:167](../../progs/doomgeneric/doomgeneric_win.c#L167)

```c
uint32_t DG_GetTicksMs()
```

**Returns:** `uint32_t`

---

<a id="dg_getkey"></a>

### `DG_GetKey`

`function` | [progs/doomgeneric/doomgeneric_win.c:172](../../progs/doomgeneric/doomgeneric_win.c#L172)

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

`function` | [progs/doomgeneric/doomgeneric_win.c:193](../../progs/doomgeneric/doomgeneric_win.c#L193)

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

`macro` | [progs/doomgeneric/doomgeneric_win.c:14](../../progs/doomgeneric/doomgeneric_win.c#L14)

```c
#define KEYQUEUE_SIZE
```

---
