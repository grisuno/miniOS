# `headers/spawn.h`

> Source: [headers/spawn.h:1](../../headers/spawn.h#L1) | language `h` | coverage 88.9% | [API index](../index.md)

## Contents

- **Structs:** [`spawn_ctx_t`](#spawn_ctx_t)
- **Functions:** [`spawn_backup`](#spawn_backup), [`spawn_restore`](#spawn_restore), [`spawn_validate_argv`](#spawn_validate_argv), [`spawn_copy_argv`](#spawn_copy_argv), [`spawn_free_argv`](#spawn_free_argv), [`spawn_load_image`](#spawn_load_image), [`spawn_execute`](#spawn_execute)

## Structs

<a id="spawn_ctx_t"></a>

### `spawn_ctx_t`

`struct` | [headers/spawn.h:9](../../headers/spawn.h#L9)

```c
typedef struct
```

Docstring: Scalar shared-window view saved across a child run.

---

## Functions

<a id="spawn_backup"></a>

### `spawn_backup`

`function` | [headers/spawn.h:28](../../headers/spawn.h#L28)

```c
int spawn_backup(spawn_ctx_t *ctx);
```

Docstring: Save the caller shared-window view into ctx.

Heap-owns the VMA pool copy (only the live prefix, never the whole VMA_MAX array), so nested spawns no longer alias one file-static buffer. Returns 0 when the copy cannot be allocated; the caller must refuse the spawn fail-closed.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `spawn_ctx_t *` |  |  |

**Returns:** `int`

---

<a id="spawn_restore"></a>

### `spawn_restore`

`function` | [headers/spawn.h:31](../../headers/spawn.h#L31)

```c
void spawn_restore(spawn_ctx_t *ctx);
```

Docstring: Restore a view previously saved by spawn_backup.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `spawn_ctx_t *` |  |  |

---

<a id="spawn_validate_argv"></a>

### `spawn_validate_argv`

`function` | [headers/spawn.h:34](../../headers/spawn.h#L34)

```c
int spawn_validate_argv(int argc, const char **uargv);
```

Docstring: Validate user argv words against the user window.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `argc` | `int` |  |  |
| `uargv` | `char **` |  |  |

**Returns:** `int`

---

<a id="spawn_copy_argv"></a>

### `spawn_copy_argv`

`function` | [headers/spawn.h:39](../../headers/spawn.h#L39)

```c
char **spawn_copy_argv(int argc, const char **uargv);
```

Docstring: Copy user argv into kernel memory, zero terminated.

One heap block serves the vector plus every word through a bump arena; the caller releases the whole scope with spawn_free_argv.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `argc` | `int` |  |  |
| `uargv` | `char **` |  |  |

**Returns:** `char **`

---

<a id="spawn_free_argv"></a>

### `spawn_free_argv`

`function` | [headers/spawn.h:42](../../headers/spawn.h#L42)

```c
void spawn_free_argv(char **kargv, int argc);
```

Docstring: Release a copy produced by spawn_copy_argv with one kfree.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `kargv` | `char **` |  |  |
| `argc` | `int` |  |  |

---

<a id="spawn_load_image"></a>

### `spawn_load_image`

`function` | [headers/spawn.h:45](../../headers/spawn.h#L45)

```c
unsigned char *spawn_load_image(const char *resolved, unsigned *size_out);
```

Docstring: Snapshot a resolved path into a kernel buffer.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `resolved` | `char *` |  |  |
| `size_out` | `unsigned *` |  |  |

**Returns:** `unsigned char *`

*Called by:* [`do_execve`](kernel.sched.c.md#do_execve)

---

<a id="spawn_execute"></a>

### `spawn_execute`

`function` | [headers/spawn.h:48](../../headers/spawn.h#L48)

```c
int spawn_execute(const char *resolved, const char *redirect, unsigned char *data, unsigned data_size, int argc, char **kargv, const char **uargv_fallback);
```

Docstring: Run a loaded image by ELF type, return child status.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `resolved` | `char *` |  |  |
| `redirect` | `char *` |  |  |
| `data` | `unsigned char *` |  |  |
| `data_size` | `unsigned` |  |  |
| `argc` | `int` |  |  |
| `kargv` | `char **` |  |  |
| `uargv_fallback` | `char **` |  |  |

**Returns:** `int`

---
