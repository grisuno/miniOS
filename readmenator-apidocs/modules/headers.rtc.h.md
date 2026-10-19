# `headers/rtc.h`

> Source: [headers/rtc.h:1](../../headers/rtc.h#L1) | language `h` | coverage 66.7% | [API index](../index.md)

## Contents

- **Functions:** [`rtc_read_tod`](#rtc_read_tod), [`rtc_read_date`](#rtc_read_date), [`suite`](#suite), [`rtc_days_from_civil`](#rtc_days_from_civil), [`rtc_wall_seconds`](#rtc_wall_seconds)

## Functions

<a id="rtc_read_tod"></a>

### `rtc_read_tod`

`function` | [headers/rtc.h:4](../../headers/rtc.h#L4)

```c
int rtc_read_tod(int *hour, int *min, int *sec);
```

========== RTC time-of-day ==========

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `hour` | `int *` |  |  |
| `min` | `int *` |  |  |
| `sec` | `int *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`rtc_read_tod`](#rtc_read_tod) (headers/kernel.h:928).

---

<a id="rtc_read_date"></a>

### `rtc_read_date`

`function` | [headers/rtc.h:11](../../headers/rtc.h#L11)

```c
int rtc_read_date(int *year, int *mon, int *day);
```

Calendar date from the CMOS RTC (registers 0x07-0x09).

Full year (CMOS carries two digits; 0..99 maps to 2000..2099). Fail-closed like the time reader: impossible month/day (including Feb 29 on a non-leap year) or a clock that never stops updating returns 0 and writes nothing.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `year` | `int *` |  |  |
| `mon` | `int *` |  |  |
| `day` | `int *` |  |  |

**Returns:** `int`

---

<a id="suite"></a>

### `suite`

`function` | [headers/rtc.h:15](../../headers/rtc.h#L15)

```c
* host suite (tests/test_rtc.c);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `c` | `tests/test_rtc.` |  |  |

**Returns:** `* host`

*Called by:* [`shell_exec_builtin`](kernel.shell.c.md#shell_exec_builtin)

---

<a id="rtc_days_from_civil"></a>

### `rtc_days_from_civil`

`function` `inline` `static` | [headers/rtc.h:18](../../headers/rtc.h#L18)

```c
static inline long rtc_days_from_civil(long y, long m, long d)
```

Days since 1970-01-01 for a civil date (Howard Hinnant's algorithm, pure integer arithmetic, no tables).

Powers rtc_wall_seconds and the host suite (tests/test_rtc.c); valid for the full 2000..2099 CMOS window and far beyond. Lives here (not in rtc.c) so the host test can compile it without the port-I/O half of the driver.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `y` | `long` |  |  |
| `m` | `long` |  |  |
| `d` | `long` |  |  |

**Returns:** `long`

*Called by:* [`rtc_wall_seconds`](drivers.rtc.c.md#rtc_wall_seconds)

---

<a id="rtc_wall_seconds"></a>

### `rtc_wall_seconds`

`function` | [headers/rtc.h:33](../../headers/rtc.h#L33)

```c
int rtc_wall_seconds(unsigned long *out);
```

Wall-clock seconds since the Unix epoch from one RTC snapshot.

Returns 1 and stores the value, or 0 on any RTC failure (caller decides the fallback; TLS treats 0 as "no clock" and fails the chain check closed downstream).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `out` | `unsigned long *` |  |  |

**Returns:** `int`

*Called by:* [`wall_us_now`](kernel.syscalls.c.md#wall_us_now)

---
