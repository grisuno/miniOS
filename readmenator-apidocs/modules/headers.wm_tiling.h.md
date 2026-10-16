# `headers/wm_tiling.h`

> Source: [headers/wm_tiling.h:1](../../headers/wm_tiling.h#L1) | language `h` | coverage 100.0% | [API index](../index.md)

Docstring: Tiling layout contract for the MiniOS desktop.

## Contents

- **Structs:** [`wm_tile_cell_t`](#wm_tile_cell_t)
- **Functions:** [`wm_tile_layout`](#wm_tile_layout)

## Structs

<a id="wm_tile_cell_t"></a>

### `wm_tile_cell_t`

`struct` | [headers/wm_tiling.h:13](../../headers/wm_tiling.h#L13)

```c
typedef struct
```

Docstring: Terminal cell in character units.

---

## Functions

<a id="wm_tile_layout"></a>

### `wm_tile_layout`

`function` `inline` `static` | [headers/wm_tiling.h:22](../../headers/wm_tiling.h#L22)

```c
static inline int wm_tile_layout(const int *present, int nterms, int gfx_active, int max_cols, int max_rows, wm_tile_cell_t *out, int cap)
```

Docstring: Compute terminal cells for the current window set.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `present` | `int *` |  |  |
| `nterms` | `int` |  |  |
| `gfx_active` | `int` |  |  |
| `max_cols` | `int` |  |  |
| `max_rows` | `int` |  |  |
| `out` | `wm_tile_cell_t *` |  |  |
| `cap` | `int` |  |  |

**Returns:** `int`

---
