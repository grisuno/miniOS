# `headers/pcspk.h`

> Source: [headers/pcspk.h:1](../../headers/pcspk.h#L1) | language `h` | coverage 11.1% | [API index](../index.md)

## Contents

- **Functions:** [`pcspk_init`](#pcspk_init), [`pcspk_tone`](#pcspk_tone), [`pcspk_off`](#pcspk_off), [`pcspk_set_volume`](#pcspk_set_volume), [`pcspk_get_volume`](#pcspk_get_volume)
- **Macros:** [`PCSPK_VOL_MIN`](#pcspk_vol_min), [`PCSPK_VOL_MAX`](#pcspk_vol_max), [`PCSPK_VOL_DEFAULT`](#pcspk_vol_default)

## Functions

<a id="pcspk_init"></a>

### `pcspk_init`

`function` | [headers/pcspk.h:8](../../headers/pcspk.h#L8)

```c
void pcspk_init(void);
```

========== PC speaker ==========

> **Inherited:** Documentation from [`pcspk_init`](#pcspk_init) (headers/kernel.h:905).

---

<a id="pcspk_tone"></a>

### `pcspk_tone`

`function` | [headers/pcspk.h:9](../../headers/pcspk.h#L9)

```c
void pcspk_tone(unsigned freq);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `freq` | `unsigned` |  |  |

---

<a id="pcspk_off"></a>

### `pcspk_off`

`function` | [headers/pcspk.h:10](../../headers/pcspk.h#L10)

```c
void pcspk_off(void);
```

---

<a id="pcspk_set_volume"></a>

### `pcspk_set_volume`

`function` | [headers/pcspk.h:11](../../headers/pcspk.h#L11)

```c
void pcspk_set_volume(unsigned volume);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `volume` | `unsigned` |  |  |

---

<a id="pcspk_get_volume"></a>

### `pcspk_get_volume`

`function` | [headers/pcspk.h:12](../../headers/pcspk.h#L12)

```c
unsigned pcspk_get_volume(void);
```

**Returns:** `unsigned`

---

## Macros

<a id="pcspk_vol_min"></a>

### `PCSPK_VOL_MIN`

`macro` | [headers/pcspk.h:4](../../headers/pcspk.h#L4)

```c
#define PCSPK_VOL_MIN
```

---

<a id="pcspk_vol_max"></a>

### `PCSPK_VOL_MAX`

`macro` | [headers/pcspk.h:5](../../headers/pcspk.h#L5)

```c
#define PCSPK_VOL_MAX
```

---

<a id="pcspk_vol_default"></a>

### `PCSPK_VOL_DEFAULT`

`macro` | [headers/pcspk.h:6](../../headers/pcspk.h#L6)

```c
#define PCSPK_VOL_DEFAULT
```

---
