# `kernel/time.c`

> Source: [kernel/time.c:1](../../kernel/time.c#L1) | language `c` | coverage 100.0% | [API index](../index.md)

================================================================

## Contents

- **Functions:** [`ktime_ms`](#ktime_ms), [`ktime_us`](#ktime_us)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_kernel_time_c__ktime_us(["ktime_us"])
    n_headers_ktime_h__ktime_us_from_delta["ktime.ktime_us_from_delta"]
    n_kernel_time_c__ktime_us -.-> n_headers_ktime_h__ktime_us_from_delta
```

## Functions

<a id="ktime_ms"></a>

### `ktime_ms`

`function` | [kernel/time.c:33](../../kernel/time.c#L33)

```c
unsigned long ktime_ms(void)
```

Forward: PIT-calibrated wall clock (defined in kernel/time.c); valid once pit_init has run.

Used only by the deadline polls below.

**Returns:** `unsigned long`

> **Inherited:** Documentation from [`ktime_ms`](#ktime_ms) (headers/kernel.h:25).

---

<a id="ktime_us"></a>

### `ktime_us`

`function` | [kernel/time.c:41](../../kernel/time.c#L41)

```c
unsigned long ktime_us(void)
```

Microsecond resolution over the same calibrated ratio (Phase 0.2/0.3: clock_gettime nsec and gettimeofday usec both derive from here, so the two clocks share one source and never disagree about ordering).

**Returns:** `unsigned long`

*Calls:* [`ktime_us_from_delta`](headers.ktime.h.md#ktime_us_from_delta)

---
