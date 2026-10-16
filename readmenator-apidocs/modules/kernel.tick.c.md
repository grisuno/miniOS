# `kernel/tick.c`

> Source: [kernel/tick.c:1](../../kernel/tick.c#L1) | language `c` | coverage 100.0% | [API index](../index.md)

Docstring: Tick listener bus implementation.

## Contents

- **Structs:** [`tick_slot_t`](#tick_slot_t)
- **Functions:** [`tick_reset`](#tick_reset), [`tick_register_audio`](#tick_register_audio), [`tick_register_desktop`](#tick_register_desktop), [`tick_register_usb`](#tick_register_usb), [`tick_run_usb`](#tick_run_usb), [`tick_run_audio`](#tick_run_audio), [`tick_run_desktop`](#tick_run_desktop), [`tick_audio_count`](#tick_audio_count), [`tick_desktop_count`](#tick_desktop_count), [`tick_desktop_due`](#tick_desktop_due)

## Structs

<a id="tick_slot_t"></a>

### `tick_slot_t`

`struct` | [kernel/tick.c:15](../../kernel/tick.c#L15)

```c
typedef struct
```

Docstring: Single registered listener slot.

---

## Functions

<a id="tick_reset"></a>

### `tick_reset`

`function` | [kernel/tick.c:34](../../kernel/tick.c#L34)

```c
void tick_reset(void)
```

Docstring: Reset every listener list to empty.

---

<a id="tick_register_audio"></a>

### `tick_register_audio`

`function` | [kernel/tick.c:58](../../kernel/tick.c#L58)

```c
int tick_register_audio(tick_fn_t fn, void *ctx)
```

Docstring: Register an unconditional BSP audio effect.

Returns 0 on success, -1 when the handler is null or the audio
table is full. A refusal changes nothing.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fn` | `tick_fn_t` |  |  |
| `ctx` | `void *` |  |  |

**Returns:** `int`

---

<a id="tick_register_desktop"></a>

### `tick_register_desktop`

`function` | [kernel/tick.c:76](../../kernel/tick.c#L76)

```c
int tick_register_desktop(tick_fn_t fn, void *ctx)
```

Docstring: Register a gated desktop effect.

Returns 0 on success, -1 when the handler is null or the desktop
table is full. A refusal changes nothing.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fn` | `tick_fn_t` |  |  |
| `ctx` | `void *` |  |  |

**Returns:** `int`

---

<a id="tick_register_usb"></a>

### `tick_register_usb`

`function` | [kernel/tick.c:89](../../kernel/tick.c#L89)

```c
int tick_register_usb(tick_fn_t fn, void *ctx)
```

Docstring: Register a polled USB controller effect.

The xHCI event ring is polled by decision rather than interrupt-driven, so
this listener is the polling trigger. Returns 0 on success, -1 when the
handler is null or the USB table is full. A refusal changes nothing.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fn` | `tick_fn_t` |  |  |
| `ctx` | `void *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`tick_register_usb`](#tick_register_usb) (headers/tick.h:69).

---

<a id="tick_run_usb"></a>

### `tick_run_usb`

`function` | [kernel/tick.c:103](../../kernel/tick.c#L103)

```c
void tick_run_usb(void)
```

Docstring: Run USB listeners in registration order.

---

<a id="tick_run_audio"></a>

### `tick_run_audio`

`function` | [kernel/tick.c:113](../../kernel/tick.c#L113)

```c
void tick_run_audio(void)
```

Docstring: Run audio listeners in registration order.

---

<a id="tick_run_desktop"></a>

### `tick_run_desktop`

`function` | [kernel/tick.c:123](../../kernel/tick.c#L123)

```c
void tick_run_desktop(void)
```

Docstring: Run desktop listeners in registration order.

---

<a id="tick_audio_count"></a>

### `tick_audio_count`

`function` | [kernel/tick.c:133](../../kernel/tick.c#L133)

```c
int tick_audio_count(void)
```

Docstring: Count registered audio listeners.

**Returns:** `int`

---

<a id="tick_desktop_count"></a>

### `tick_desktop_count`

`function` | [kernel/tick.c:144](../../kernel/tick.c#L144)

```c
int tick_desktop_count(void)
```

Docstring: Count registered desktop listeners.

**Returns:** `int`

---

<a id="tick_desktop_due"></a>

### `tick_desktop_due`

`function` | [kernel/tick.c:160](../../kernel/tick.c#L160)

```c
int tick_desktop_due(unsigned long long ticks, unsigned interval)
```

Docstring: Pure desktop gating predicate.

Returns nonzero when the given tick count falls on a desktop tick
for the given interval. A non-positive interval never fires. Holds
for every tick value including zero.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ticks` | `unsigned long long` |  |  |
| `interval` | `unsigned` |  |  |

**Returns:** `int`

---
