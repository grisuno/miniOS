# `headers/percpu_rq.h`

> Source: [headers/percpu_rq.h:1](../../headers/percpu_rq.h#L1) | language `h` | coverage 7.1% | [API index](../index.md)

Docstring: percpu_rq.h -- Per-CPU runqueues with work stealing.

## Contents

- **Structs:** [`percpu_rq_t`](#percpu_rq_t)
- **Functions:** [`rq_init`](#rq_init), [`rq_enqueue`](#rq_enqueue), [`rq_pop_local`](#rq_pop_local), [`rq_steal_once`](#rq_steal_once), [`rq_empty`](#rq_empty), [`rq_should_rescan`](#rq_should_rescan), [`rq_note_poll`](#rq_note_poll), [`rq_stats`](#rq_stats)
- **Macros:** [`RQ_DEPTH`](#rq_depth), [`RQ_RESCAN_PERIOD`](#rq_rescan_period), [`RQ_VALIDATE_ATTEMPTS`](#rq_validate_attempts), [`WQ_NONE_HINT`](#wq_none_hint)

## Structs

<a id="percpu_rq_t"></a>

### `percpu_rq_t`

`struct` | [headers/percpu_rq.h:50](../../headers/percpu_rq.h#L50)

```c
typedef struct
```

---

## Functions

<a id="rq_init"></a>

### `rq_init`

`function` | [headers/percpu_rq.h:61](../../headers/percpu_rq.h#L61)

```c
void rq_init(void);
```

*Called by:* [`sched_init`](kernel.sched.c.md#sched_init)

---

<a id="rq_enqueue"></a>

### `rq_enqueue`

`function` | [headers/percpu_rq.h:62](../../headers/percpu_rq.h#L62)

```c
void rq_enqueue(int cpu, int pid);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `cpu` | `int` |  |  |
| `pid` | `int` |  |  |

*Called by:* [`do_thread_spawn`](kernel.sched.c.md#do_thread_spawn)

---

<a id="rq_pop_local"></a>

### `rq_pop_local`

`function` | [headers/percpu_rq.h:63](../../headers/percpu_rq.h#L63)

```c
int rq_pop_local(int cpu);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `cpu` | `int` |  |  |

**Returns:** `int`

---

<a id="rq_steal_once"></a>

### `rq_steal_once`

`function` | [headers/percpu_rq.h:64](../../headers/percpu_rq.h#L64)

```c
int rq_steal_once(int self_cpu, int *from_cpu);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `self_cpu` | `int` |  |  |
| `from_cpu` | `int *` |  |  |

**Returns:** `int`

---

<a id="rq_empty"></a>

### `rq_empty`

`function` | [headers/percpu_rq.h:65](../../headers/percpu_rq.h#L65)

```c
int rq_empty(int cpu);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `cpu` | `int` |  |  |

**Returns:** `int`

---

<a id="rq_should_rescan"></a>

### `rq_should_rescan`

`function` | [headers/percpu_rq.h:66](../../headers/percpu_rq.h#L66)

```c
int rq_should_rescan(int cpu);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `cpu` | `int` |  |  |

**Returns:** `int`

---

<a id="rq_note_poll"></a>

### `rq_note_poll`

`function` | [headers/percpu_rq.h:67](../../headers/percpu_rq.h#L67)

```c
void rq_note_poll(int cpu);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `cpu` | `int` |  |  |

---

<a id="rq_stats"></a>

### `rq_stats`

`function` | [headers/percpu_rq.h:68](../../headers/percpu_rq.h#L68)

```c
void rq_stats(int cpu, unsigned long *hits, unsigned long *steals, unsigned long *drops);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `cpu` | `int` |  |  |
| `hits` | `unsigned long *` |  |  |
| `steals` | `unsigned long *` |  |  |
| `drops` | `unsigned long *` |  |  |

---

## Macros

<a id="rq_depth"></a>

### `RQ_DEPTH`

`macro` | [headers/percpu_rq.h:45](../../headers/percpu_rq.h#L45)

```c
#define RQ_DEPTH
```

---

<a id="rq_rescan_period"></a>

### `RQ_RESCAN_PERIOD`

`macro` | [headers/percpu_rq.h:46](../../headers/percpu_rq.h#L46)

```c
#define RQ_RESCAN_PERIOD
```

---

<a id="rq_validate_attempts"></a>

### `RQ_VALIDATE_ATTEMPTS`

`macro` | [headers/percpu_rq.h:47](../../headers/percpu_rq.h#L47)

```c
#define RQ_VALIDATE_ATTEMPTS
```

---

<a id="wq_none_hint"></a>

### `WQ_NONE_HINT`

`macro` | [headers/percpu_rq.h:48](../../headers/percpu_rq.h#L48)

```c
#define WQ_NONE_HINT
```

---
