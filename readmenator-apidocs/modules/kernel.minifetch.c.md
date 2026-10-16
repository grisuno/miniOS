# `kernel/minifetch.c`

> Source: [kernel/minifetch.c:1](../../kernel/minifetch.c#L1) | language `c` | coverage 50.0% | [API index](../index.md)

Docstring: kernel/minifetch.c -- neofetch-style system screen.

## Contents

- **Structs:** [`minifetch_cfg`](#minifetch_cfg)
- **Functions:** [`shell_cmd_minifetch`](#shell_cmd_minifetch), [`frame`](#frame)

## Structs

<a id="minifetch_cfg"></a>

### `minifetch_cfg`

`struct` | [kernel/minifetch.c:21](../../kernel/minifetch.c#L21)

```c
typedef struct minifetch_cfg
```

---

## Functions

<a id="shell_cmd_minifetch"></a>

### `shell_cmd_minifetch`

`function` | [kernel/minifetch.c:156](../../kernel/minifetch.c#L156)

```c
void shell_cmd_minifetch(void)
```

Docstring: Print the two-column fetch screen.

---

<a id="frame"></a>

### `frame`

`function` | [kernel/minifetch.c:159](../../kernel/minifetch.c#L159)

```c
* frame (stack discipline, CLAUDE.md). Fail-closed on OOM. */ char (*specs)[96] = (char (*)[96])kmalloc(20 * 96);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `discipline` | `stack` |  |  |
| `md` | `CLAUDE.` |  |  |

**Returns:** `*`

---
