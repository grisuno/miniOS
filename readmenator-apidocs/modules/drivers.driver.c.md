# `drivers/driver.c`

> Source: [drivers/driver.c:1](../../drivers/driver.c#L1) | language `c` | coverage 16.7% | [API index](../index.md)

driver.c -- Device registry for the Strategy-pattern driver layer.

## Contents

- **Functions:** [`device_reset`](#device_reset), [`device_register`](#device_register), [`device_find`](#device_find), [`device_find_by_type`](#device_find_by_type), [`device_count`](#device_count)

## Functions

<a id="device_reset"></a>

### `device_reset`

`function` | [drivers/driver.c:32](../../drivers/driver.c#L32)

```c
void device_reset(void)
```

---

<a id="device_register"></a>

### `device_register`

`function` | [drivers/driver.c:44](../../drivers/driver.c#L44)

```c
int device_register(device_t *dev)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `dev` | `device_t *` |  |  |

**Returns:** `int`

---

<a id="device_find"></a>

### `device_find`

`function` | [drivers/driver.c:66](../../drivers/driver.c#L66)

```c
device_t *device_find(const char *name)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `name` | `char *` |  |  |

**Returns:** `device_t *`

---

<a id="device_find_by_type"></a>

### `device_find_by_type`

`function` | [drivers/driver.c:76](../../drivers/driver.c#L76)

```c
device_t *device_find_by_type(int type)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `type` | `int` |  |  |

**Returns:** `device_t *`

---

<a id="device_count"></a>

### `device_count`

`function` | [drivers/driver.c:85](../../drivers/driver.c#L85)

```c
int device_count(void)
```

**Returns:** `int`

---
