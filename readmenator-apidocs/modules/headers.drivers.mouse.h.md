# `headers/drivers/mouse.h`

> Source: [headers/drivers/mouse.h:1](../../headers/drivers/mouse.h#L1) | language `h` | coverage 100.0% | [API index](../index.md)

Docstring: mouse.h -- boundary of the PS/2 mouse device driver

## Contents

- **Functions:** [`mouse_hw_init`](#mouse_hw_init), [`mouse_disable`](#mouse_disable), [`mouse_enable`](#mouse_enable)

## Functions

<a id="mouse_hw_init"></a>

### `mouse_hw_init`

`function` | [headers/drivers/mouse.h:11](../../headers/drivers/mouse.h#L11)

```c
void mouse_hw_init(void);
```

Docstring: Detect the wheel mouse and enable data reporting.

*Called by:* [`sched_init`](kernel.sched.c.md#sched_init)

---

<a id="mouse_disable"></a>

### `mouse_disable`

`function` | [headers/drivers/mouse.h:14](../../headers/drivers/mouse.h#L14)

```c
void mouse_disable(void);
```

Docstring: Disable mouse data reporting.

---

<a id="mouse_enable"></a>

### `mouse_enable`

`function` | [headers/drivers/mouse.h:17](../../headers/drivers/mouse.h#L17)

```c
void mouse_enable(void);
```

Docstring: Enable mouse data reporting.

---
