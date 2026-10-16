# `headers/rcu.h`

> Source: [headers/rcu.h:1](../../headers/rcu.h#L1) | language `h` | coverage 5.9% | [API index](../index.md)

Docstring: rcu.h -- Read-copy-update, lite epoch edition.

## Contents

- **Functions:** [`retirement`](#retirement), [`rcu_init`](#rcu_init), [`rcu_read_lock`](#rcu_read_lock), [`rcu_read_unlock`](#rcu_read_unlock), [`rcu_deref`](#rcu_deref), [`rcu_publish`](#rcu_publish), [`rcu_call`](#rcu_call), [`rcu_note_tick`](#rcu_note_tick), [`rcu_note_idle`](#rcu_note_idle), [`rcu_poll`](#rcu_poll), [`rcu_synchronize`](#rcu_synchronize)
- **Macros:** [`RCU_CB_MAX`](#rcu_cb_max), [`RCU_SYNC_SPINS`](#rcu_sync_spins), [`RCU_OK`](#rcu_ok), [`RCU_ERR_FULL`](#rcu_err_full), [`RCU_ERR_TIMEOUT`](#rcu_err_timeout)

## Functions

<a id="retirement"></a>

### `retirement`

`function` | [headers/rcu.h:30](../../headers/rcu.h#L30)

```c
* retirement (the writer keeps ownership) instead of dropping the free. * Callbacks run in tick context with interrupts disabled, so they must * be short and non-blocking. rcu_synchronize spins on qui
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ownership` | `the writer keeps` |  |  |

**Returns:** `*`

---

<a id="rcu_init"></a>

### `rcu_init`

`function` | [headers/rcu.h:51](../../headers/rcu.h#L51)

```c
void rcu_init(void);
```

*Called by:* [`sched_init`](kernel.sched.c.md#sched_init)

---

<a id="rcu_read_lock"></a>

### `rcu_read_lock`

`function` | [headers/rcu.h:52](../../headers/rcu.h#L52)

```c
void rcu_read_lock(void);
```

---

<a id="rcu_read_unlock"></a>

### `rcu_read_unlock`

`function` | [headers/rcu.h:53](../../headers/rcu.h#L53)

```c
void rcu_read_unlock(void);
```

---

<a id="rcu_deref"></a>

### `rcu_deref`

`function` | [headers/rcu.h:54](../../headers/rcu.h#L54)

```c
void *rcu_deref(void *volatile *pp);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `pp` | `void *volatile *` |  |  |

**Returns:** `void *`

---

<a id="rcu_publish"></a>

### `rcu_publish`

`function` | [headers/rcu.h:55](../../headers/rcu.h#L55)

```c
void rcu_publish(void *volatile *pp, void *v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `pp` | `void *volatile *` |  |  |
| `v` | `void *` |  |  |

---

<a id="rcu_call"></a>

### `rcu_call`

`function` | [headers/rcu.h:56](../../headers/rcu.h#L56)

```c
long rcu_call(rcu_cb_t fn, void *arg);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fn` | `rcu_cb_t` |  |  |
| `arg` | `void *` |  |  |

**Returns:** `long`

---

<a id="rcu_note_tick"></a>

### `rcu_note_tick`

`function` | [headers/rcu.h:57](../../headers/rcu.h#L57)

```c
void rcu_note_tick(int cpu);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `cpu` | `int` |  |  |

*Called by:* [`isr_dispatch`](kernel.sched.c.md#isr_dispatch)

---

<a id="rcu_note_idle"></a>

### `rcu_note_idle`

`function` | [headers/rcu.h:58](../../headers/rcu.h#L58)

```c
void rcu_note_idle(int cpu);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `cpu` | `int` |  |  |

---

<a id="rcu_poll"></a>

### `rcu_poll`

`function` | [headers/rcu.h:59](../../headers/rcu.h#L59)

```c
void rcu_poll(void);
```

*Called by:* [`isr_dispatch`](kernel.sched.c.md#isr_dispatch)

---

<a id="rcu_synchronize"></a>

### `rcu_synchronize`

`function` | [headers/rcu.h:60](../../headers/rcu.h#L60)

```c
long rcu_synchronize(void);
```

**Returns:** `long`

*Called by:* [`expires`](kernel.rcu.c.md#expires)

---

## Macros

<a id="rcu_cb_max"></a>

### `RCU_CB_MAX`

`macro` | [headers/rcu.h:42](../../headers/rcu.h#L42)

```c
#define RCU_CB_MAX
```

---

<a id="rcu_sync_spins"></a>

### `RCU_SYNC_SPINS`

`macro` | [headers/rcu.h:43](../../headers/rcu.h#L43)

```c
#define RCU_SYNC_SPINS
```

---

<a id="rcu_ok"></a>

### `RCU_OK`

`macro` | [headers/rcu.h:45](../../headers/rcu.h#L45)

```c
#define RCU_OK
```

---

<a id="rcu_err_full"></a>

### `RCU_ERR_FULL`

`macro` | [headers/rcu.h:46](../../headers/rcu.h#L46)

```c
#define RCU_ERR_FULL
```

---

<a id="rcu_err_timeout"></a>

### `RCU_ERR_TIMEOUT`

`macro` | [headers/rcu.h:47](../../headers/rcu.h#L47)

```c
#define RCU_ERR_TIMEOUT
```

---
