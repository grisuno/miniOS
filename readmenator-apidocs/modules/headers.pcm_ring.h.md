# `headers/pcm_ring.h`

> Source: [headers/pcm_ring.h:1](../../headers/pcm_ring.h#L1) | language `h` | coverage 14.3% | [API index](../index.md)

pcm_ring.h -- single-producer/single-consumer byte ring for PCM audio.

## Contents

- **Structs:** [`pcm_ring_t`](#pcm_ring_t)
- **Functions:** [`pcm_ring_init`](#pcm_ring_init), [`pcm_ring_used`](#pcm_ring_used), [`pcm_ring_free`](#pcm_ring_free), [`pcm_ring_write`](#pcm_ring_write), [`pcm_ring_read`](#pcm_ring_read)

## Structs

<a id="pcm_ring_t"></a>

### `pcm_ring_t`

`struct` | [headers/pcm_ring.h:26](../../headers/pcm_ring.h#L26)

```c
typedef struct
```

---

## Functions

<a id="pcm_ring_init"></a>

### `pcm_ring_init`

`function` `inline` `static` | [headers/pcm_ring.h:36](../../headers/pcm_ring.h#L36)

```c
static inline void pcm_ring_init(pcm_ring_t *r, unsigned char *buf, unsigned cap)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `r` | `pcm_ring_t *` |  |  |
| `buf` | `unsigned char *` |  |  |
| `cap` | `unsigned` |  |  |

*Called by:* [`pcm2_open`](drivers.pcm2.c.md#pcm2_open)

---

<a id="pcm_ring_used"></a>

### `pcm_ring_used`

`function` `inline` `static` | [headers/pcm_ring.h:47](../../headers/pcm_ring.h#L47)

```c
static inline unsigned pcm_ring_used(const pcm_ring_t *r)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `r` | `pcm_ring_t *` |  |  |

**Returns:** `unsigned`

---

<a id="pcm_ring_free"></a>

### `pcm_ring_free`

`function` `inline` `static` | [headers/pcm_ring.h:51](../../headers/pcm_ring.h#L51)

```c
static inline unsigned pcm_ring_free(const pcm_ring_t *r)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `r` | `pcm_ring_t *` |  |  |

**Returns:** `unsigned`

*Called by:* [`pcm2_write`](drivers.pcm2.c.md#pcm2_write)

---

<a id="pcm_ring_write"></a>

### `pcm_ring_write`

`function` `inline` `static` | [headers/pcm_ring.h:55](../../headers/pcm_ring.h#L55)

```c
static inline unsigned pcm_ring_write(pcm_ring_t *r, const unsigned char *src, unsigned len)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `r` | `pcm_ring_t *` |  |  |
| `src` | `unsigned char *` |  |  |
| `len` | `unsigned` |  |  |

**Returns:** `unsigned`

*Called by:* [`pcm2_write`](drivers.pcm2.c.md#pcm2_write)

---

<a id="pcm_ring_read"></a>

### `pcm_ring_read`

`function` `inline` `static` | [headers/pcm_ring.h:76](../../headers/pcm_ring.h#L76)

```c
static inline unsigned pcm_ring_read(pcm_ring_t *r, unsigned char *dst, unsigned len)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `r` | `pcm_ring_t *` |  |  |
| `dst` | `unsigned char *` |  |  |
| `len` | `unsigned` |  |  |

**Returns:** `unsigned`

---
