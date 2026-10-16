# `headers/futex.h`

> Source: [headers/futex.h:1](../../headers/futex.h#L1) | language `h` | coverage 21.4% | [API index](../index.md)

Docstring: futex.h -- Fast userspace mutex sleep/wake contract.

## Contents

- **Structs:** [`futex_bucket_t`](#futex_bucket_t)
- **Functions:** [`futex_init`](#futex_init), [`futex_wait`](#futex_wait), [`futex_wake`](#futex_wake), [`futex_forget`](#futex_forget), [`FUTEX_CLOCK_REALTIME`](#futex_clock_realtime), [`futex_linux_cmd`](#futex_linux_cmd), [`futex_timeout_remaining_us`](#futex_timeout_remaining_us)
- **Macros:** [`FUTEX_BUCKETS`](#futex_buckets), [`FUTEX_BUCKET_MASK`](#futex_bucket_mask), [`FUTEX_HASH_GOLDEN`](#futex_hash_golden), [`FUTEX_OK`](#futex_ok), [`FUTEX_NOMATCH`](#futex_nomatch), [`FUTEX_NOPROC`](#futex_noproc), [`FUTEX_WAKE_ALL`](#futex_wake_all), [`LINUX_FUTEX_WAIT`](#linux_futex_wait), [`LINUX_FUTEX_WAKE`](#linux_futex_wake), [`LINUX_FUTEX_WAIT_BITSET`](#linux_futex_wait_bitset), [`LINUX_FUTEX_WAKE_BITSET`](#linux_futex_wake_bitset), [`LINUX_FUTEX_PRIVATE_FLAG`](#linux_futex_private_flag), [`LINUX_FUTEX_CLOCK_REALTIME`](#linux_futex_clock_realtime), [`LINUX_FUTEX_BITSET_MATCH_ANY`](#linux_futex_bitset_match_any), [`FUTEX_US_PER_S`](#futex_us_per_s), [`FUTEX_NS_PER_US`](#futex_ns_per_us), [`FUTEX_NS_PER_S`](#futex_ns_per_s), [`FUTEX_TIMEOUT_INVALID`](#futex_timeout_invalid), [`FUTEX_TIMEOUT_FOREVER`](#futex_timeout_forever)

## Structs

<a id="futex_bucket_t"></a>

### `futex_bucket_t`

`struct` | [headers/futex.h:80](../../headers/futex.h#L80)

```c
typedef struct
```

---

## Functions

<a id="futex_init"></a>

### `futex_init`

`function` | [headers/futex.h:86](../../headers/futex.h#L86)

```c
void futex_init(void);
```

*Called by:* [`sched_init`](kernel.sched.c.md#sched_init)

---

<a id="futex_wait"></a>

### `futex_wait`

`function` | [headers/futex.h:87](../../headers/futex.h#L87)

```c
long futex_wait(unsigned long uaddr, int val);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `uaddr` | `unsigned long` |  |  |
| `val` | `int` |  |  |

**Returns:** `long`

---

<a id="futex_wake"></a>

### `futex_wake`

`function` | [headers/futex.h:88](../../headers/futex.h#L88)

```c
long futex_wake(unsigned long uaddr, int n);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `uaddr` | `unsigned long` |  |  |
| `n` | `int` |  |  |

**Returns:** `long`

*Called by:* [`do_exit`](kernel.sched.c.md#do_exit)

---

<a id="futex_forget"></a>

### `futex_forget`

`function` | [headers/futex.h:91](../../headers/futex.h#L91)

```c
void futex_forget(int pid);
```

Unlink pid from whatever futex queue still holds it and clear its recorded address; a no-op for a pid that is not waiting.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `pid` | `int` |  |  |

---

<a id="futex_clock_realtime"></a>

### `FUTEX_CLOCK_REALTIME`

`function` | [headers/futex.h:96](../../headers/futex.h#L96)

```c
* FUTEX_CLOCK_REALTIME (it only selects the clock of a BITSET deadline). * Returns -1 for anything unserved (REQUEUE, CMP_REQUEUE, WAKE_OP, PI/PP, * unknown flags). Host-tested (tests/test_futex.c);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `deadline` | `it only selects the clock of a BITSET` |  |  |

**Returns:** `*`

---

<a id="futex_linux_cmd"></a>

### `futex_linux_cmd`

`function` | [headers/futex.h:100](../../headers/futex.h#L100)

```c
int futex_linux_cmd(long op);
```

Decode a Linux futex(2) op to LINUX_FUTEX_WAIT/WAKE/WAIT_BITSET/ WAKE_BITSET, masking FUTEX_PRIVATE_FLAG (process-private is served on the same global buckets: same semantics, no isolation shortcut) and FUTEX_CLOCK_REALTIME (it only selects the clock of a BITSET deadline).

Returns -1 for anything unserved (REQUEUE, CMP_REQUEUE, WAKE_OP, PI/PP, unknown flags). Host-tested (tests/test_futex.c); the kernel errno mapping lives in syscalls.c, which is not host-compilable.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `op` | `long` |  |  |

**Returns:** `int`

---

<a id="futex_timeout_remaining_us"></a>

### `futex_timeout_remaining_us`

`function` | [headers/futex.h:107](../../headers/futex.h#L107)

```c
long futex_timeout_remaining_us(int cmd, long sec, long nsec, unsigned long now_us);
```

Microseconds left before a futex timeout: relative for WAIT, absolute (against now_us on the op's clock) for WAIT_BITSET.

Zero or negative means the deadline passed; FUTEX_TIMEOUT_INVALID for a negative second or a nanosecond field outside [0, 1e9); FUTEX_TIMEOUT_FOREVER when the seconds would overflow a microsecond count. Pure, host-tested.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `cmd` | `int` |  |  |
| `sec` | `long` |  |  |
| `nsec` | `long` |  |  |
| `now_us` | `unsigned long` |  |  |

**Returns:** `long`

---

## Macros

<a id="futex_buckets"></a>

### `FUTEX_BUCKETS`

`macro` | [headers/futex.h:51](../../headers/futex.h#L51)

```c
#define FUTEX_BUCKETS
```

---

<a id="futex_bucket_mask"></a>

### `FUTEX_BUCKET_MASK`

`macro` | [headers/futex.h:52](../../headers/futex.h#L52)

```c
#define FUTEX_BUCKET_MASK
```

---

<a id="futex_hash_golden"></a>

### `FUTEX_HASH_GOLDEN`

`macro` | [headers/futex.h:53](../../headers/futex.h#L53)

```c
#define FUTEX_HASH_GOLDEN
```

---

<a id="futex_ok"></a>

### `FUTEX_OK`

`macro` | [headers/futex.h:55](../../headers/futex.h#L55)

```c
#define FUTEX_OK
```

---

<a id="futex_nomatch"></a>

### `FUTEX_NOMATCH`

`macro` | [headers/futex.h:56](../../headers/futex.h#L56)

```c
#define FUTEX_NOMATCH
```

---

<a id="futex_noproc"></a>

### `FUTEX_NOPROC`

`macro` | [headers/futex.h:57](../../headers/futex.h#L57)

```c
#define FUTEX_NOPROC
```

---

<a id="futex_wake_all"></a>

### `FUTEX_WAKE_ALL`

`macro` | [headers/futex.h:58](../../headers/futex.h#L58)

```c
#define FUTEX_WAKE_ALL
```

---

<a id="linux_futex_wait"></a>

### `LINUX_FUTEX_WAIT`

`macro` | [headers/futex.h:65](../../headers/futex.h#L65)

```c
#define LINUX_FUTEX_WAIT
```

Linux futex(2) op numbers. __NR_futex is 202, the retired MINIOS_SYS_TLS_SEND number, so syscalls.c serves raw glibc futex traps here instead of a second table.

WAIT/WAKE and their BITSET forms (with FUTEX_BITSET_MATCH_ANY only, what glibc sends) run on futex_wait/ futex_wake below.

---

<a id="linux_futex_wake"></a>

### `LINUX_FUTEX_WAKE`

`macro` | [headers/futex.h:66](../../headers/futex.h#L66)

```c
#define LINUX_FUTEX_WAKE
```

---

<a id="linux_futex_wait_bitset"></a>

### `LINUX_FUTEX_WAIT_BITSET`

`macro` | [headers/futex.h:67](../../headers/futex.h#L67)

```c
#define LINUX_FUTEX_WAIT_BITSET
```

---

<a id="linux_futex_wake_bitset"></a>

### `LINUX_FUTEX_WAKE_BITSET`

`macro` | [headers/futex.h:68](../../headers/futex.h#L68)

```c
#define LINUX_FUTEX_WAKE_BITSET
```

---

<a id="linux_futex_private_flag"></a>

### `LINUX_FUTEX_PRIVATE_FLAG`

`macro` | [headers/futex.h:69](../../headers/futex.h#L69)

```c
#define LINUX_FUTEX_PRIVATE_FLAG
```

---

<a id="linux_futex_clock_realtime"></a>

### `LINUX_FUTEX_CLOCK_REALTIME`

`macro` | [headers/futex.h:70](../../headers/futex.h#L70)

```c
#define LINUX_FUTEX_CLOCK_REALTIME
```

---

<a id="linux_futex_bitset_match_any"></a>

### `LINUX_FUTEX_BITSET_MATCH_ANY`

`macro` | [headers/futex.h:71](../../headers/futex.h#L71)

```c
#define LINUX_FUTEX_BITSET_MATCH_ANY
```

---

<a id="futex_us_per_s"></a>

### `FUTEX_US_PER_S`

`macro` | [headers/futex.h:72](../../headers/futex.h#L72)

```c
#define FUTEX_US_PER_S
```

---

<a id="futex_ns_per_us"></a>

### `FUTEX_NS_PER_US`

`macro` | [headers/futex.h:73](../../headers/futex.h#L73)

```c
#define FUTEX_NS_PER_US
```

---

<a id="futex_ns_per_s"></a>

### `FUTEX_NS_PER_S`

`macro` | [headers/futex.h:74](../../headers/futex.h#L74)

```c
#define FUTEX_NS_PER_S
```

---

<a id="futex_timeout_invalid"></a>

### `FUTEX_TIMEOUT_INVALID`

`macro` | [headers/futex.h:77](../../headers/futex.h#L77)

```c
#define FUTEX_TIMEOUT_INVALID
```

futex_timeout_remaining_us results beside a microsecond count: an invalid timespec, and a deadline too far to represent (wait untimed).

---

<a id="futex_timeout_forever"></a>

### `FUTEX_TIMEOUT_FOREVER`

`macro` | [headers/futex.h:78](../../headers/futex.h#L78)

```c
#define FUTEX_TIMEOUT_FOREVER
```

---
