# `headers/tick.h`

> Source: [headers/tick.h:1](../../headers/tick.h#L1) | language `h` | coverage 100.0% | [API index](../index.md)

Docstring: Tick listener bus contract.

## Contents

- **Structs:** [`tick_config_t`](#tick_config_t)
- **Functions:** [`tick_reset`](#tick_reset), [`tick_register_audio`](#tick_register_audio), [`tick_register_desktop`](#tick_register_desktop), [`tick_register_usb`](#tick_register_usb), [`tick_run_usb`](#tick_run_usb), [`tick_run_audio`](#tick_run_audio), [`tick_run_desktop`](#tick_run_desktop), [`tick_audio_count`](#tick_audio_count), [`tick_desktop_count`](#tick_desktop_count), [`tick_desktop_due`](#tick_desktop_due)
- **Macros:** [`TICK_MAX_AUDIO_LISTENERS`](#tick_max_audio_listeners), [`TICK_MAX_DESKTOP_LISTENERS`](#tick_max_desktop_listeners), [`TICK_MAX_USB_LISTENERS`](#tick_max_usb_listeners), [`TICK_CONFIG_DEFAULT`](#tick_config_default)

## Structs

<a id="tick_config_t"></a>

### `tick_config_t`

`struct` | [headers/tick.h:22](../../headers/tick.h#L22)

```c
typedef struct
```

Docstring: Centralized bounds for the tick listener bus.

---

## Functions

<a id="tick_reset"></a>

### `tick_reset`

`function` | [headers/tick.h:47](../../headers/tick.h#L47)

```c
void tick_reset(void);
```

Docstring: Reset both listener lists to empty.

*Called by:* [`sched_init`](kernel.sched.c.md#sched_init)

---

<a id="tick_register_audio"></a>

### `tick_register_audio`

`function` | [headers/tick.h:54](../../headers/tick.h#L54)

```c
int tick_register_audio(tick_fn_t fn, void *ctx);
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

*Called by:* [`sched_init`](kernel.sched.c.md#sched_init)

---

<a id="tick_register_desktop"></a>

### `tick_register_desktop`

`function` | [headers/tick.h:61](../../headers/tick.h#L61)

```c
int tick_register_desktop(tick_fn_t fn, void *ctx);
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

*Called by:* [`sched_init`](kernel.sched.c.md#sched_init)

---

<a id="tick_register_usb"></a>

### `tick_register_usb`

`function` | [headers/tick.h:69](../../headers/tick.h#L69)

```c
int tick_register_usb(tick_fn_t fn, void *ctx);
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

*Called by:* [`sched_init`](kernel.sched.c.md#sched_init)

---

<a id="tick_run_usb"></a>

### `tick_run_usb`

`function` | [headers/tick.h:72](../../headers/tick.h#L72)

```c
void tick_run_usb(void);
```

Docstring: Run USB listeners in registration order.

*Called by:* [`isr_dispatch`](kernel.sched.c.md#isr_dispatch)

---

<a id="tick_run_audio"></a>

### `tick_run_audio`

`function` | [headers/tick.h:75](../../headers/tick.h#L75)

```c
void tick_run_audio(void);
```

Docstring: Run audio listeners in registration order.

*Called by:* [`isr_dispatch`](kernel.sched.c.md#isr_dispatch)

---

<a id="tick_run_desktop"></a>

### `tick_run_desktop`

`function` | [headers/tick.h:78](../../headers/tick.h#L78)

```c
void tick_run_desktop(void);
```

Docstring: Run desktop listeners in registration order.

*Called by:* [`isr_dispatch`](kernel.sched.c.md#isr_dispatch)

---

<a id="tick_audio_count"></a>

### `tick_audio_count`

`function` | [headers/tick.h:81](../../headers/tick.h#L81)

```c
int tick_audio_count(void);
```

Docstring: Count registered audio listeners.

**Returns:** `int`

---

<a id="tick_desktop_count"></a>

### `tick_desktop_count`

`function` | [headers/tick.h:84](../../headers/tick.h#L84)

```c
int tick_desktop_count(void);
```

Docstring: Count registered desktop listeners.

**Returns:** `int`

---

<a id="tick_desktop_due"></a>

### `tick_desktop_due`

`function` | [headers/tick.h:92](../../headers/tick.h#L92)

```c
int tick_desktop_due(unsigned long long ticks, unsigned interval);
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

*Called by:* [`isr_dispatch`](kernel.sched.c.md#isr_dispatch)

---

## Macros

<a id="tick_max_audio_listeners"></a>

### `TICK_MAX_AUDIO_LISTENERS`

`macro` | [headers/tick.h:29](../../headers/tick.h#L29)

```c
#define TICK_MAX_AUDIO_LISTENERS
```

Docstring: Default bus capacities.

---

<a id="tick_max_desktop_listeners"></a>

### `TICK_MAX_DESKTOP_LISTENERS`

`macro` | [headers/tick.h:31](../../headers/tick.h#L31)

```c
#define TICK_MAX_DESKTOP_LISTENERS
```

Docstring: Default desktop bus capacity.

---

<a id="tick_max_usb_listeners"></a>

### `TICK_MAX_USB_LISTENERS`

`macro` | [headers/tick.h:34](../../headers/tick.h#L34)

```c
#define TICK_MAX_USB_LISTENERS
```

Docstring: Default USB bus capacity.

One listener is all the USB stack needs; the bound exists so the tables stay fixed-size.

---

<a id="tick_config_default"></a>

### `TICK_CONFIG_DEFAULT`

`macro` | [headers/tick.h:37](../../headers/tick.h#L37)

```c
#define TICK_CONFIG_DEFAULT
```

Docstring: Default bus configuration.

---
