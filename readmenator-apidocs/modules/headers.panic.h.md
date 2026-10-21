# `headers/panic.h`

> Source: [headers/panic.h:1](../../headers/panic.h#L1) | language `h` | coverage 80.0% | [API index](../index.md)

Docstring: panic.h -- Kernel panic backtrace contract (header-only).

## Contents

- **Functions:** [`panic_hex_str`](#panic_hex_str), [`panic_backtrace`](#panic_backtrace)
- **Macros:** [`PANIC_BT_MAX`](#panic_bt_max), [`PANIC_HEX_MAX_DIGITS`](#panic_hex_max_digits)

## Functions

<a id="panic_hex_str"></a>

### `panic_hex_str`

`function` `inline` `static` | [headers/panic.h:28](../../headers/panic.h#L28)

```c
static inline int panic_hex_str(char *buf, int cap, unsigned long v, int digits)
```

Docstring: Format an unsigned long as fixed-width lowercase hex into buf, writing exactly digits characters plus a NUL terminator, so the buffer must hold digits + 1 bytes. digits is clamped to [0, PANIC_HEX_MAX_DIGITS] and to the buffer capacity, so the widest field never writes past the terminator.

Returns the number of characters written.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `buf` | `char *` |  |  |
| `cap` | `int` |  |  |
| `v` | `unsigned long` |  |  |
| `digits` | `int` |  |  |

**Returns:** `int`

---

<a id="panic_backtrace"></a>

### `panic_backtrace`

`function` `inline` `static` | [headers/panic.h:51](../../headers/panic.h#L51)

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

<a id="panic_hex_max_digits"></a>

### `PANIC_HEX_MAX_DIGITS`

`macro` | [headers/panic.h:20](../../headers/panic.h#L20)

```c
#define PANIC_HEX_MAX_DIGITS
```

Docstring: Widest hex field the banner prints: a 64-bit value.

---
