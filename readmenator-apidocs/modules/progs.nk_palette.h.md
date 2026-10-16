# `progs/nk_palette.h`

> Source: [progs/nk_palette.h:1](../../progs/nk_palette.h#L1) | language `h` | coverage 11.1% | [API index](../index.md)

nk_palette.h - one shared hybrid palette for every NK-window app.

## Contents

- **Functions:** [`nk_palette_build`](#nk_palette_build)
- **Macros:** [`NK_PAL_BYTES`](#nk_pal_bytes), [`NK_PAL_DESK`](#nk_pal_desk), [`NK_PAL_CUBE`](#nk_pal_cube), [`NK_PAL_GRAYS`](#nk_pal_grays), [`NK_PAL_ACCENTS`](#nk_pal_accents), [`NK_PAL_ERR_OK`](#nk_pal_err_ok), [`NK_PAL_ERR_BOUND`](#nk_pal_err_bound)

## Functions

<a id="nk_palette_build"></a>

### `nk_palette_build`

`function` `static` | [progs/nk_palette.h:22](../../progs/nk_palette.h#L22)

```c
static int nk_palette_build(unsigned char *pal, long cap)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `pal` | `unsigned char *` |  |  |
| `cap` | `long` |  |  |

**Returns:** `int`

*Called by:* [`nk_build_palette`](progs.nuklear.nuklear_minios.c.md#nk_build_palette)

---

## Macros

<a id="nk_pal_bytes"></a>

### `NK_PAL_BYTES`

`macro` | [progs/nk_palette.h:14](../../progs/nk_palette.h#L14)

```c
#define NK_PAL_BYTES
```

---

<a id="nk_pal_desk"></a>

### `NK_PAL_DESK`

`macro` | [progs/nk_palette.h:15](../../progs/nk_palette.h#L15)

```c
#define NK_PAL_DESK
```

---

<a id="nk_pal_cube"></a>

### `NK_PAL_CUBE`

`macro` | [progs/nk_palette.h:16](../../progs/nk_palette.h#L16)

```c
#define NK_PAL_CUBE
```

---

<a id="nk_pal_grays"></a>

### `NK_PAL_GRAYS`

`macro` | [progs/nk_palette.h:17](../../progs/nk_palette.h#L17)

```c
#define NK_PAL_GRAYS
```

---

<a id="nk_pal_accents"></a>

### `NK_PAL_ACCENTS`

`macro` | [progs/nk_palette.h:18](../../progs/nk_palette.h#L18)

```c
#define NK_PAL_ACCENTS
```

---

<a id="nk_pal_err_ok"></a>

### `NK_PAL_ERR_OK`

`macro` | [progs/nk_palette.h:19](../../progs/nk_palette.h#L19)

```c
#define NK_PAL_ERR_OK
```

---

<a id="nk_pal_err_bound"></a>

### `NK_PAL_ERR_BOUND`

`macro` | [progs/nk_palette.h:20](../../progs/nk_palette.h#L20)

```c
#define NK_PAL_ERR_BOUND
```

---
