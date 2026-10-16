# `headers/arena.h`

> Source: [headers/arena.h:1](../../headers/arena.h#L1) | language `h` | coverage 93.3% | [API index](../index.md)

Docstring: bump arena for MiniOS, kernel and ring-3 alike.

## Contents

- **Structs:** [`minios_arena`](#minios_arena)
- **Functions:** [`kmalloc`](#kmalloc), [`kfree`](#kfree), [`arena_init`](#arena_init), [`arena_align_up`](#arena_align_up), [`arena_bytes_for`](#arena_bytes_for), [`arena_alloc`](#arena_alloc), [`arena_used`](#arena_used), [`arena_free_bytes`](#arena_free_bytes), [`arena_reset`](#arena_reset), [`arena_checkpoint`](#arena_checkpoint), [`arena_rewind`](#arena_rewind), [`arena_contains`](#arena_contains)
- **Macros:** [`ARENA_DEFAULT_ALIGN`](#arena_default_align)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_headers_arena_h__arena_alloc(["arena_alloc"])
    n_headers_arena_h__arena_align_up(["arena_align_up"])
    n_headers_arena_h__arena_alloc --> n_headers_arena_h__arena_align_up
```

## Structs

<a id="minios_arena"></a>

### `minios_arena`

`struct` | [headers/arena.h:41](../../headers/arena.h#L41)

```c
typedef struct minios_arena
```

Docstring: one bump scope over a caller-owned backing block.

---

## Functions

<a id="kmalloc"></a>

### `kmalloc`

`function` | [headers/arena.h:3](../../headers/arena.h#L3)

```c
* * A bump arena serves one kmalloc (kernel) or malloc (ring-3) with pointer * bumps instead of N allocator round trips, then releases the whole scope * with a single free. That is the exact shape of
```

ifdef MINIOS_LK_KERNEL

**Returns:** `* * A bump arena serves one`

> **Inherited:** Documentation from [`kmalloc`](#kmalloc) (headers/leakcheck.h:79).

*Called by:* [`spawn_backup`](kernel.spawn.c.md#spawn_backup), [`spawn_copy_argv`](kernel.spawn.c.md#spawn_copy_argv), [`spawn_load_image`](kernel.spawn.c.md#spawn_load_image)

---

<a id="kfree"></a>

### `kfree`

`function` | [headers/arena.h:25](../../headers/arena.h#L25)

```c
* kfree(back);
```

**Returns:** `*`

*Called by:* [`spawn_copy_argv`](kernel.spawn.c.md#spawn_copy_argv), [`spawn_free_argv`](kernel.spawn.c.md#spawn_free_argv), [`spawn_restore`](kernel.spawn.c.md#spawn_restore)

---

<a id="arena_init"></a>

### `arena_init`

`function` `inline` `static` | [headers/arena.h:48](../../headers/arena.h#L48)

```c
static inline void arena_init(arena_t *a, void *block, size_t size)
```

Docstring: bind an arena to a backing block, empty when block is null.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a` | `arena_t *` |  |  |
| `block` | `void *` |  |  |
| `size` | `size_t` |  |  |

*Called by:* [`spawn_copy_argv`](kernel.spawn.c.md#spawn_copy_argv)

---

<a id="arena_align_up"></a>

### `arena_align_up`

`function` `inline` `static` | [headers/arena.h:62](../../headers/arena.h#L62)

```c
static inline size_t arena_align_up(size_t n, size_t align)
```

Docstring: round n up to align, 0 on overflow or non-power-of-two align.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `n` | `size_t` |  |  |
| `align` | `size_t` |  |  |

**Returns:** `size_t`

*Called by:* [`arena_alloc`](#arena_alloc)

---

<a id="arena_bytes_for"></a>

### `arena_bytes_for`

`function` `inline` `static` | [headers/arena.h:74](../../headers/arena.h#L74)

```c
static inline size_t arena_bytes_for(size_t count, size_t elem_size)
```

Docstring: overflow checked bytes for count items of elem_size.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `count` | `size_t` |  |  |
| `elem_size` | `size_t` |  |  |

**Returns:** `size_t`

*Called by:* [`spawn_copy_argv`](kernel.spawn.c.md#spawn_copy_argv)

---

<a id="arena_alloc"></a>

### `arena_alloc`

`function` `inline` `static` | [headers/arena.h:81](../../headers/arena.h#L81)

```c
static inline void *arena_alloc(arena_t *a, size_t size, size_t align)
```

Docstring: borrow size bytes at align, null when the scope is exhausted.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a` | `arena_t *` |  |  |
| `size` | `size_t` |  |  |
| `align` | `size_t` |  |  |

**Returns:** `void *`

*Calls:* [`arena_align_up`](#arena_align_up)

*Called by:* [`spawn_copy_argv`](kernel.spawn.c.md#spawn_copy_argv)

---

<a id="arena_used"></a>

### `arena_used`

`function` `inline` `static` | [headers/arena.h:95](../../headers/arena.h#L95)

```c
static inline size_t arena_used(const arena_t *a)
```

Docstring: bytes borrowed so far, 0 for a null or empty arena.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a` | `arena_t *` |  |  |

**Returns:** `size_t`

---

<a id="arena_free_bytes"></a>

### `arena_free_bytes`

`function` `inline` `static` | [headers/arena.h:101](../../headers/arena.h#L101)

```c
static inline size_t arena_free_bytes(const arena_t *a)
```

Docstring: bytes still borrowable, 0 for a null or empty arena.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a` | `arena_t *` |  |  |

**Returns:** `size_t`

---

<a id="arena_reset"></a>

### `arena_reset`

`function` `inline` `static` | [headers/arena.h:107](../../headers/arena.h#L107)

```c
static inline void arena_reset(arena_t *a)
```

Docstring: rewind the scope to empty without releasing the backing block.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a` | `arena_t *` |  |  |

---

<a id="arena_checkpoint"></a>

### `arena_checkpoint`

`function` `inline` `static` | [headers/arena.h:113](../../headers/arena.h#L113)

```c
static inline size_t arena_checkpoint(const arena_t *a)
```

Docstring: bookmark the cursor for a later partial rewind.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a` | `arena_t *` |  |  |

**Returns:** `size_t`

---

<a id="arena_rewind"></a>

### `arena_rewind`

`function` `inline` `static` | [headers/arena.h:119](../../headers/arena.h#L119)

```c
static inline int arena_rewind(arena_t *a, size_t checkpoint)
```

Docstring: rewind to a checkpoint, -1 when the mark is out of range.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a` | `arena_t *` |  |  |
| `checkpoint` | `size_t` |  |  |

**Returns:** `int`

---

<a id="arena_contains"></a>

### `arena_contains`

`function` `inline` `static` | [headers/arena.h:128](../../headers/arena.h#L128)

```c
static inline int arena_contains(const arena_t *a, const void *ptr)
```

Docstring: true when ptr lies inside the backing block.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a` | `arena_t *` |  |  |
| `ptr` | `void *` |  |  |

**Returns:** `int`

---

## Macros

<a id="arena_default_align"></a>

### `ARENA_DEFAULT_ALIGN`

`macro` | [headers/arena.h:38](../../headers/arena.h#L38)

```c
#define ARENA_DEFAULT_ALIGN
```

Docstring: default borrow alignment when the caller passes align 0.

---
