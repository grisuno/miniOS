# `headers/vga_fx.h`

> Source: [headers/vga_fx.h:1](../../headers/vga_fx.h#L1) | language `h` | coverage 100.0% | [API index](../index.md)

Docstring: DOOM-melt desktop effect contract for MiniOS.

## Contents

- **Structs:** [`vga_fx_config_t`](#vga_fx_config_t)
- **Functions:** [`vga_fx_rand`](#vga_fx_rand), [`vga_fx_init_cols`](#vga_fx_init_cols), [`vga_fx_advance`](#vga_fx_advance), [`vga_fx_front`](#vga_fx_front), [`vga_fx_clamp_rect`](#vga_fx_clamp_rect)
- **Macros:** [`VGA_FX_CONFIG_DEFAULT`](#vga_fx_config_default), [`VGA_FX_COLS_MAX`](#vga_fx_cols_max)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_headers_vga_fx_h__vga_fx_init_cols(["vga_fx_init_cols"])
    n_headers_vga_fx_h__vga_fx_rand(["vga_fx_rand"])
    n_headers_vga_fx_h__vga_fx_init_cols --> n_headers_vga_fx_h__vga_fx_rand
```

## Structs

<a id="vga_fx_config_t"></a>

### `vga_fx_config_t`

`struct` | [headers/vga_fx.h:16](../../headers/vga_fx.h#L16)

```c
typedef struct
```

Docstring: Centralized effect configuration, no magic numbers.

---

## Functions

<a id="vga_fx_rand"></a>

### `vga_fx_rand`

`function` `inline` `static` | [headers/vga_fx.h:30](../../headers/vga_fx.h#L30)

```c
static inline unsigned long vga_fx_rand(unsigned long *s)
```

Docstring: One xorshift32 step, the melt's deterministic PRNG.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `s` | `unsigned long *` |  |  |

**Returns:** `unsigned long`

*Called by:* [`vga_fx_init_cols`](#vga_fx_init_cols)

---

<a id="vga_fx_init_cols"></a>

### `vga_fx_init_cols`

`function` `inline` `static` | [headers/vga_fx.h:47](../../headers/vga_fx.h#L47)

```c
static inline int vga_fx_init_cols(const vga_fx_config_t *cfg, int *cols, int w)
```

Docstring: Seed consecutive column fronts with staggered delays.

Mirrors f_wipe.c: first column waits a random 0..15 frames, each next column drifts by -1..+1, clamped at zero, -16 repaired to -15.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `cfg` | `vga_fx_config_t *` |  |  |
| `cols` | `int *` |  |  |
| `w` | `int` |  |  |

**Returns:** `int`

*Calls:* [`vga_fx_rand`](#vga_fx_rand)

*Called by:* [`once`](kernel.vga_fx.c.md#once)

---

<a id="vga_fx_advance"></a>

### `vga_fx_advance`

`function` `inline` `static` | [headers/vga_fx.h:71](../../headers/vga_fx.h#L71)

```c
static inline int vga_fx_advance(const vga_fx_config_t *cfg, int *cols, int w, int h)
```

Docstring: Advance every column front one melt frame.

Returns 1 when every front reached the rect bottom, 0 otherwise.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `cfg` | `vga_fx_config_t *` |  |  |
| `cols` | `int *` |  |  |
| `w` | `int` |  |  |
| `h` | `int` |  |  |

**Returns:** `int`

*Called by:* [`once`](kernel.vga_fx.c.md#once)

---

<a id="vga_fx_front"></a>

### `vga_fx_front`

`function` `inline` `static` | [headers/vga_fx.h:97](../../headers/vga_fx.h#L97)

```c
static inline int vga_fx_front(int col_y, int h)
```

Docstring: Rows [0, front) of one column already show the new frame.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `col_y` | `int` |  |  |
| `h` | `int` |  |  |

**Returns:** `int`

*Called by:* [`once`](kernel.vga_fx.c.md#once)

---

<a id="vga_fx_clamp_rect"></a>

### `vga_fx_clamp_rect`

`function` `inline` `static` | [headers/vga_fx.h:109](../../headers/vga_fx.h#L109)

```c
static inline int vga_fx_clamp_rect(int *x, int *y, int *w, int *h, int fb_w, int fb_h)
```

Docstring: Clamp a transition rect inside the framebuffer.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `int *` |  |  |
| `y` | `int *` |  |  |
| `w` | `int *` |  |  |
| `h` | `int *` |  |  |
| `fb_w` | `int` |  |  |
| `fb_h` | `int` |  |  |

**Returns:** `int`

*Called by:* [`once`](kernel.vga_fx.c.md#once), [`vga_fx_restore_rect`](kernel.vga_fx.c.md#vga_fx_restore_rect), [`vga_fx_snap_rect`](kernel.vga_fx.c.md#vga_fx_snap_rect)

---

## Macros

<a id="vga_fx_config_default"></a>

### `VGA_FX_CONFIG_DEFAULT`

`macro` | [headers/vga_fx.h:24](../../headers/vga_fx.h#L24)

```c
#define VGA_FX_CONFIG_DEFAULT
```

Docstring: Default melt pacing: 8 px per frame, 8 ms per frame.

---

<a id="vga_fx_cols_max"></a>

### `VGA_FX_COLS_MAX`

`macro` | [headers/vga_fx.h:27](../../headers/vga_fx.h#L27)

```c
#define VGA_FX_COLS_MAX
```

Docstring: Widest transition the column array can describe.

---
