# `headers/pcm2.h`

> Source: [headers/pcm2.h:1](../../headers/pcm2.h#L1) | language `h` | coverage 4.8% | [API index](../index.md)

pcm2.h -- low-latency PCM audio path over SB16 single-cycle DMA.

## Contents

- **Structs:** [`pcm2_counters_t`](#pcm2_counters_t)
- **Functions:** [`pcm2_active`](#pcm2_active), [`pcm2_open`](#pcm2_open), [`pcm2_write`](#pcm2_write), [`pcm2_close`](#pcm2_close), [`pcm2_irq`](#pcm2_irq), [`pcm2_poll`](#pcm2_poll), [`pcm2_counters`](#pcm2_counters)
- **Macros:** [`PCM2_RATE`](#pcm2_rate), [`PCM2_FRAG`](#pcm2_frag), [`PCM2_FRAGS`](#pcm2_frags), [`PCM2_DMA_BYTES`](#pcm2_dma_bytes), [`PCM2_RING`](#pcm2_ring), [`PCM2_FLAG_NONBLOCK`](#pcm2_flag_nonblock), [`PCM2_ERR_BUSY`](#pcm2_err_busy), [`PCM2_ERR_NODEV`](#pcm2_err_nodev), [`PCM2_ERR_NOMEM`](#pcm2_err_nomem), [`PCM2_ERR_PERM`](#pcm2_err_perm), [`PCM2_ERR_PIPE`](#pcm2_err_pipe), [`PCM2_ERR_INVAL`](#pcm2_err_inval)

## Structs

<a id="pcm2_counters_t"></a>

### `pcm2_counters_t`

`struct` | [headers/pcm2.h:67](../../headers/pcm2.h#L67)

```c
typedef struct
```

---

## Functions

<a id="pcm2_active"></a>

### `pcm2_active`

`function` | [headers/pcm2.h:77](../../headers/pcm2.h#L77)

```c
int pcm2_active(void);
```

**Returns:** `int`

*Called by:* [`sb16_irq`](drivers.sb16.c.md#sb16_irq), [`sb16_pcm_open`](drivers.sb16.c.md#sb16_pcm_open), [`sb16_pcm_submit`](drivers.sb16.c.md#sb16_pcm_submit), [`sb16_pump`](drivers.sb16.c.md#sb16_pump), [`sb16_tone`](drivers.sb16.c.md#sb16_tone), [`isr_dispatch`](kernel.sched.c.md#isr_dispatch)

---

<a id="pcm2_open"></a>

### `pcm2_open`

`function` | [headers/pcm2.h:78](../../headers/pcm2.h#L78)

```c
int pcm2_open(unsigned flags, int owner);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `flags` | `unsigned` |  |  |
| `owner` | `int` |  |  |

**Returns:** `int`

---

<a id="pcm2_write"></a>

### `pcm2_write`

`function` | [headers/pcm2.h:79](../../headers/pcm2.h#L79)

```c
int pcm2_write(const unsigned char *user, unsigned len, int owner);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `user` | `unsigned char *` |  |  |
| `len` | `unsigned` |  |  |
| `owner` | `int` |  |  |

**Returns:** `int`

---

<a id="pcm2_close"></a>

### `pcm2_close`

`function` | [headers/pcm2.h:80](../../headers/pcm2.h#L80)

```c
void pcm2_close(int owner);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `owner` | `int` |  |  |

---

<a id="pcm2_irq"></a>

### `pcm2_irq`

`function` | [headers/pcm2.h:81](../../headers/pcm2.h#L81)

```c
void pcm2_irq(void);
```

*Called by:* [`isr_dispatch`](kernel.sched.c.md#isr_dispatch)

---

<a id="pcm2_poll"></a>

### `pcm2_poll`

`function` | [headers/pcm2.h:82](../../headers/pcm2.h#L82)

```c
void pcm2_poll(void);
```

*Called by:* [`sb16_poll`](drivers.sb16.c.md#sb16_poll)

---

<a id="pcm2_counters"></a>

### `pcm2_counters`

`function` | [headers/pcm2.h:83](../../headers/pcm2.h#L83)

```c
void pcm2_counters(pcm2_counters_t *out);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `out` | `pcm2_counters_t *` |  |  |

---

## Macros

<a id="pcm2_rate"></a>

### `PCM2_RATE`

`macro` | [headers/pcm2.h:52](../../headers/pcm2.h#L52)

```c
#define PCM2_RATE
```

---

<a id="pcm2_frag"></a>

### `PCM2_FRAG`

`macro` | [headers/pcm2.h:53](../../headers/pcm2.h#L53)

```c
#define PCM2_FRAG
```

---

<a id="pcm2_frags"></a>

### `PCM2_FRAGS`

`macro` | [headers/pcm2.h:54](../../headers/pcm2.h#L54)

```c
#define PCM2_FRAGS
```

---

<a id="pcm2_dma_bytes"></a>

### `PCM2_DMA_BYTES`

`macro` | [headers/pcm2.h:55](../../headers/pcm2.h#L55)

```c
#define PCM2_DMA_BYTES
```

---

<a id="pcm2_ring"></a>

### `PCM2_RING`

`macro` | [headers/pcm2.h:56](../../headers/pcm2.h#L56)

```c
#define PCM2_RING
```

---

<a id="pcm2_flag_nonblock"></a>

### `PCM2_FLAG_NONBLOCK`

`macro` | [headers/pcm2.h:58](../../headers/pcm2.h#L58)

```c
#define PCM2_FLAG_NONBLOCK
```

---

<a id="pcm2_err_busy"></a>

### `PCM2_ERR_BUSY`

`macro` | [headers/pcm2.h:60](../../headers/pcm2.h#L60)

```c
#define PCM2_ERR_BUSY
```

---

<a id="pcm2_err_nodev"></a>

### `PCM2_ERR_NODEV`

`macro` | [headers/pcm2.h:61](../../headers/pcm2.h#L61)

```c
#define PCM2_ERR_NODEV
```

---

<a id="pcm2_err_nomem"></a>

### `PCM2_ERR_NOMEM`

`macro` | [headers/pcm2.h:62](../../headers/pcm2.h#L62)

```c
#define PCM2_ERR_NOMEM
```

---

<a id="pcm2_err_perm"></a>

### `PCM2_ERR_PERM`

`macro` | [headers/pcm2.h:63](../../headers/pcm2.h#L63)

```c
#define PCM2_ERR_PERM
```

---

<a id="pcm2_err_pipe"></a>

### `PCM2_ERR_PIPE`

`macro` | [headers/pcm2.h:64](../../headers/pcm2.h#L64)

```c
#define PCM2_ERR_PIPE
```

---

<a id="pcm2_err_inval"></a>

### `PCM2_ERR_INVAL`

`macro` | [headers/pcm2.h:65](../../headers/pcm2.h#L65)

```c
#define PCM2_ERR_INVAL
```

---
