# `kernel/clip.c`

> Source: [kernel/clip.c:1](../../kernel/clip.c#L1) | language `c` | coverage 80.0% | [API index](../index.md)

Docstring: kernel/clip.c -- Shared text clipboard.

## Contents

- **Functions:** [`clip_set`](#clip_set), [`clip_clear`](#clip_clear), [`clip_len_get`](#clip_len_get)
- **Macros:** [`CLIP_MAX`](#clip_max)

## Functions

<a id="clip_set"></a>

### `clip_set`

`function` | [kernel/clip.c:25](../../kernel/clip.c#L25)

```c
int clip_set(const char *data, unsigned long len)
```

Docstring: Replace the clipboard with len bytes from data.

Refused (return -1) on null data or past CLIP_MAX; empty clears.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `data` | `char *` |  |  |
| `len` | `unsigned long` |  |  |

**Returns:** `int`

---

<a id="clip_clear"></a>

### `clip_clear`

`function` | [kernel/clip.c:48](../../kernel/clip.c#L48)

```c
void clip_clear(void)
```

Docstring: Empty the clipboard.

Reads then report -1 (empty).

---

<a id="clip_len_get"></a>

### `clip_len_get`

`function` | [kernel/clip.c:55](../../kernel/clip.c#L55)

```c
int clip_len_get(void)
```

Docstring: Current length, or -1 when empty.

Lets callers size the read buffer before getting.

**Returns:** `int`

---

## Macros

<a id="clip_max"></a>

### `CLIP_MAX`

`macro` | [kernel/clip.c:17](../../kernel/clip.c#L17)

```c
#define CLIP_MAX
```

---
