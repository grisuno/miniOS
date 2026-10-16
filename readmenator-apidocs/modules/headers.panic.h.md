# `headers/panic.h`

> Source: [headers/panic.h:1](../../headers/panic.h#L1) | language `h` | coverage 66.7% | [API index](../index.md)

Docstring: panic.h -- Kernel panic backtrace contract (header-only).

## Contents

- **Functions:** [`panic_backtrace`](#panic_backtrace)
- **Macros:** [`PANIC_BT_MAX`](#panic_bt_max)

## Functions

<a id="panic_backtrace"></a>

### `panic_backtrace`

`function` `inline` `static` | [headers/panic.h:25](../../headers/panic.h#L25)

```c
static inline int panic_backtrace(unsigned long rbp, panic_valid_fn valid, unsigned long *out, int max)
```

Docstring: Walk up to max frame pointers from rbp, storing each frame's return address (*(rbp+8)) into out.

Stops on null rbp, failed predicate, a non-advancing frame or a null return address. Returns the stored count. Fail-closed on null out or null predicate.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `rbp` | `unsigned long` |  |  |
| `valid` | `panic_valid_fn` |  |  |
| `out` | `unsigned long *` |  |  |
| `max` | `int` |  |  |

**Returns:** `int`

*Called by:* [`panic_screen`](kernel.panic.c.md#panic_screen)

---

## Macros

<a id="panic_bt_max"></a>

### `PANIC_BT_MAX`

`macro` | [headers/panic.h:17](../../headers/panic.h#L17)

```c
#define PANIC_BT_MAX
```

---
