# `kernel/printf.c`

> Source: [kernel/printf.c:1](../../kernel/printf.c#L1) | language `c` | coverage 20.0% | [API index](../index.md)

================================================================

## Contents

- **Structs:** [`snctx`](#snctx)
- **Functions:** [`kfprintf`](#kfprintf), [`ksprintf`](#ksprintf), [`ksnprintf`](#ksnprintf)

## Structs

<a id="snctx"></a>

### `snctx`

`struct` | [kernel/printf.c:177](../../kernel/printf.c#L177)

```c
struct snctx { char *p; unsigned long rem; };
```

---

## Functions

<a id="kfprintf"></a>

### `kfprintf`

`function` | [kernel/printf.c:157](../../kernel/printf.c#L157)

```c
int kfprintf(KFILE *f, const char *fmt, ...)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `f` | `KFILE *` |  |  |
| `fmt` | `char *` |  |  |
| `...` |  |  |  |

**Returns:** `int`

---

<a id="ksprintf"></a>

### `ksprintf`

`function` | [kernel/printf.c:166](../../kernel/printf.c#L166)

```c
int ksprintf(char *buf, const char *fmt, ...)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `buf` | `char *` |  |  |
| `fmt` | `char *` |  |  |
| `...` |  |  |  |

**Returns:** `int`

---

<a id="ksnprintf"></a>

### `ksnprintf`

`function` | [kernel/printf.c:184](../../kernel/printf.c#L184)

```c
int ksnprintf(char *buf, unsigned long size, const char *fmt, ...)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `buf` | `char *` |  |  |
| `size` | `unsigned long` |  |  |
| `fmt` | `char *` |  |  |
| `...` |  |  |  |

**Returns:** `int`

---
