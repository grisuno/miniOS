# `progs/src/lxsel.c`

> Source: [progs/src/lxsel.c:1](../../progs/src/lxsel.c#L1) | language `c` | coverage 25.0% | [API index](../index.md)

lxsel.c -- select(2)/pselect6(2) ABI probe (docs/spec/python.md).

## Contents

- **Functions:** [`main`](#main)
- **Macros:** [`_GNU_SOURCE`](#_gnu_source), [`LXSEL_NFDS_OUT_OF_RANGE`](#lxsel_nfds_out_of_range), [`LXSEL_BAD_FD`](#lxsel_bad_fd), [`LXSEL_TIMEOUT_US`](#lxsel_timeout_us), [`LXSEL_TIMEOUT_MS_MIN`](#lxsel_timeout_ms_min), [`LXSEL_PSELECT_TIMEOUT_NS`](#lxsel_pselect_timeout_ns)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_progs_src_lxsel_c__main(["main"])
    n_kernel_syscalls_c__clock_gettime["syscalls.clock_gettime"]
    n_progs_src_lxsel_c__main -.-> n_kernel_syscalls_c__clock_gettime
```

## Functions

<a id="main"></a>

### `main`

`function` | [progs/src/lxsel.c:60](../../progs/src/lxsel.c#L60)

```c
int main(void)
```

**Returns:** `int`

*Calls:* [`clock_gettime`](kernel.syscalls.c.md#clock_gettime)

---

## Macros

<a id="_gnu_source"></a>

### `_GNU_SOURCE`

`macro` | [progs/src/lxsel.c:17](../../progs/src/lxsel.c#L17)

```c
#define _GNU_SOURCE
```

---

<a id="lxsel_nfds_out_of_range"></a>

### `LXSEL_NFDS_OUT_OF_RANGE`

`macro` | [progs/src/lxsel.c:28](../../progs/src/lxsel.c#L28)

```c
#define LXSEL_NFDS_OUT_OF_RANGE
```

The kernel's real fd_set is the Linux 1024-fd form; glibc's FD_SET covers it, and 1025 is out of range on either side.

---

<a id="lxsel_bad_fd"></a>

### `LXSEL_BAD_FD`

`macro` | [progs/src/lxsel.c:29](../../progs/src/lxsel.c#L29)

```c
#define LXSEL_BAD_FD
```

---

<a id="lxsel_timeout_us"></a>

### `LXSEL_TIMEOUT_US`

`macro` | [progs/src/lxsel.c:30](../../progs/src/lxsel.c#L30)

```c
#define LXSEL_TIMEOUT_US
```

---

<a id="lxsel_timeout_ms_min"></a>

### `LXSEL_TIMEOUT_MS_MIN`

`macro` | [progs/src/lxsel.c:31](../../progs/src/lxsel.c#L31)

```c
#define LXSEL_TIMEOUT_MS_MIN
```

---

<a id="lxsel_pselect_timeout_ns"></a>

### `LXSEL_PSELECT_TIMEOUT_NS`

`macro` | [progs/src/lxsel.c:32](../../progs/src/lxsel.c#L32)

```c
#define LXSEL_PSELECT_TIMEOUT_NS
```

---
