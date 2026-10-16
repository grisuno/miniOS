# `progs/nuklear/nuklear_theme.h`

> Source: [progs/nuklear/nuklear_theme.h:1](../../progs/nuklear/nuklear_theme.h#L1) | language `h` | coverage 38.5% | [API index](../index.md)

Docstring: shared Nuklear theme contract for every MiniOS NK app.

## Contents

- **Structs:** [`nk_context`](#nk_context)
- **Functions:** [`nk_theme_active`](#nk_theme_active), [`nk_theme_probe`](#nk_theme_probe), [`nk_theme_apply`](#nk_theme_apply)
- **Macros:** [`NK_THEME_NAME_MAX`](#nk_theme_name_max), [`NK_THEME_KEY_MAX`](#nk_theme_key_max), [`NK_THEME_LINE_MAX`](#nk_theme_line_max), [`NK_THEME_PATH_DIR`](#nk_theme_path_dir), [`NK_THEME_PATH_CURRENT`](#nk_theme_path_current), [`NK_THEME_DEFAULT`](#nk_theme_default), [`NK_THEME_KEY_LIST`](#nk_theme_key_list), [`NK_THEME_KEY_COUNT`](#nk_theme_key_count)

## Structs

<a id="nk_context"></a>

### `nk_context`

`struct` | [progs/nuklear/nuklear_theme.h:59](../../progs/nuklear/nuklear_theme.h#L59)

```c
struct nk_context;
```

---

## Functions

<a id="nk_theme_active"></a>

### `nk_theme_active`

`function` | [progs/nuklear/nuklear_theme.h:62](../../progs/nuklear/nuklear_theme.h#L62)

```c
int nk_theme_active(char *dst, int cap);
```

Resolve the active theme name (current file, else the default).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `dst` | `char *` |  |  |
| `cap` | `int` |  |  |

**Returns:** `int`

---

<a id="nk_theme_probe"></a>

### `nk_theme_probe`

`function` | [progs/nuklear/nuklear_theme.h:65](../../progs/nuklear/nuklear_theme.h#L65)

```c
int nk_theme_probe(const char *name, unsigned char rgb[NK_THEME_KEY_COUNT][3]);
```

Load name (or active when 0) into rgb[32][3]; 0 ok, <0 fallback used.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `name` | `char *` |  |  |
| `NK_THEME_KEY_COUNT` | `unsigned char rgb[ ][3]` |  |  |

**Returns:** `int`

---

<a id="nk_theme_apply"></a>

### `nk_theme_apply`

`function` | [progs/nuklear/nuklear_theme.h:68](../../progs/nuklear/nuklear_theme.h#L68)

```c
int nk_theme_apply(struct nk_context *ctx, const char *name);
```

Apply name (or active when 0) to ctx; 0 ok, <0 fallback applied.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `struct nk_context *` |  |  |
| `name` | `char *` |  |  |

**Returns:** `int`

---

## Macros

<a id="nk_theme_name_max"></a>

### `NK_THEME_NAME_MAX`

`macro` | [progs/nuklear/nuklear_theme.h:15](../../progs/nuklear/nuklear_theme.h#L15)

```c
#define NK_THEME_NAME_MAX
```

---

<a id="nk_theme_key_max"></a>

### `NK_THEME_KEY_MAX`

`macro` | [progs/nuklear/nuklear_theme.h:16](../../progs/nuklear/nuklear_theme.h#L16)

```c
#define NK_THEME_KEY_MAX
```

---

<a id="nk_theme_line_max"></a>

### `NK_THEME_LINE_MAX`

`macro` | [progs/nuklear/nuklear_theme.h:17](../../progs/nuklear/nuklear_theme.h#L17)

```c
#define NK_THEME_LINE_MAX
```

---

<a id="nk_theme_path_dir"></a>

### `NK_THEME_PATH_DIR`

`macro` | [progs/nuklear/nuklear_theme.h:18](../../progs/nuklear/nuklear_theme.h#L18)

```c
#define NK_THEME_PATH_DIR
```

---

<a id="nk_theme_path_current"></a>

### `NK_THEME_PATH_CURRENT`

`macro` | [progs/nuklear/nuklear_theme.h:19](../../progs/nuklear/nuklear_theme.h#L19)

```c
#define NK_THEME_PATH_CURRENT
```

---

<a id="nk_theme_default"></a>

### `NK_THEME_DEFAULT`

`macro` | [progs/nuklear/nuklear_theme.h:20](../../progs/nuklear/nuklear_theme.h#L20)

```c
#define NK_THEME_DEFAULT
```

---

<a id="nk_theme_key_list"></a>

### `NK_THEME_KEY_LIST`

`macro` | [progs/nuklear/nuklear_theme.h:23](../../progs/nuklear/nuklear_theme.h#L23)

```c
#define NK_THEME_KEY_LIST
```

Single source of truth for theme keys (X-macro: no table drift).

---

<a id="nk_theme_key_count"></a>

### `NK_THEME_KEY_COUNT`

`macro` | [progs/nuklear/nuklear_theme.h:57](../../progs/nuklear/nuklear_theme.h#L57)

```c
#define NK_THEME_KEY_COUNT
```

---
