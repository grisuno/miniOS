# `headers/ktime.h`

> Source: [headers/ktime.h:1](../../headers/ktime.h#L1) | language `h` | coverage 66.7% | [API index](../index.md)

ktime.h -- pure time-conversion helpers shared by the kernel clock

## Contents

- **Functions:** [`ktime_us_from_delta`](#ktime_us_from_delta), [`wall_us_from_parts`](#wall_us_from_parts)

## Functions

<a id="ktime_us_from_delta"></a>

### `ktime_us_from_delta`

`function` `inline` `static` | [headers/ktime.h:19](../../headers/ktime.h#L19)

```c
static inline unsigned long ktime_us_from_delta(unsigned long delta_ticks, unsigned long tsc_per_ms)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `delta_ticks` | `unsigned long` |  |  |
| `tsc_per_ms` | `unsigned long` |  |  |

**Returns:** `unsigned long`

*Called by:* [`ktime_us`](kernel.time.c.md#ktime_us)

---

<a id="wall_us_from_parts"></a>

### `wall_us_from_parts`

`function` `inline` `static` | [headers/ktime.h:30](../../headers/ktime.h#L30)

```c
static inline unsigned long wall_us_from_parts(unsigned long base_sec, unsigned long base_ktime_us, unsigned long now_ktime_us)
```

wall_us_from_parts: wall-clock microseconds from an RTC-anchored base. base_sec is the last seen RTC second, base_ktime_us the monotonic clock then, now_ktime_us the monotonic clock now.

Pure so the host suite pins the rollover math; the kernel feeds it live values.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `base_sec` | `unsigned long` |  |  |
| `base_ktime_us` | `unsigned long` |  |  |
| `now_ktime_us` | `unsigned long` |  |  |

**Returns:** `unsigned long`

*Called by:* [`wall_us_now`](kernel.syscalls.c.md#wall_us_now)

---
