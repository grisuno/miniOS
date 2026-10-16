# `progs/src/sbtone.c`

> Source: [progs/src/sbtone.c:1](../../progs/src/sbtone.c#L1) | language `c` | coverage 11.1% | [API index](../index.md)

sbtone.c — headless SB16 diagnostic (ring-3, no GUI).

## Contents

- **Functions:** [`buffers`](#buffers), [`main`](#main)
- **Macros:** [`SYS_SB16_OPEN`](#sys_sb16_open), [`SYS_SB16_SUBMIT`](#sys_sb16_submit), [`SYS_TIME`](#sys_time), [`RATE`](#rate), [`BUF`](#buf), [`WINDOW_MS`](#window_ms)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_progs_src_sbtone_c__main(["main"])
    n_progs_src_sbtone_c__buffers(["buffers"])
    n_progs_src_sbtone_c__main --> n_progs_src_sbtone_c__buffers
```

## Functions

<a id="buffers"></a>

### `buffers`

`function` | [progs/src/sbtone.c:14](../../progs/src/sbtone.c#L14)

```c
* * Exit code is the number of submitted buffers (0 on failure to open). */ #include <stdio.h>...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `open` | `0 on failure to` |  |  |

**Returns:** `* * Exit code is the number of submitted`

*Called by:* [`rtl_init`](net.rtl8139.c.md#rtl_init), [`main`](#main)

---

<a id="main"></a>

### `main`

`function` | [progs/src/sbtone.c:36](../../progs/src/sbtone.c#L36)

```c
int main(void)
```

**Returns:** `int`

*Calls:* [`buffers`](#buffers)

---

## Macros

<a id="sys_sb16_open"></a>

### `SYS_SB16_OPEN`

`macro` | [progs/src/sbtone.c:21](../../progs/src/sbtone.c#L21)

```c
#define SYS_SB16_OPEN
```

---

<a id="sys_sb16_submit"></a>

### `SYS_SB16_SUBMIT`

`macro` | [progs/src/sbtone.c:22](../../progs/src/sbtone.c#L22)

```c
#define SYS_SB16_SUBMIT
```

---

<a id="sys_time"></a>

### `SYS_TIME`

`macro` | [progs/src/sbtone.c:23](../../progs/src/sbtone.c#L23)

```c
#define SYS_TIME
```

---

<a id="rate"></a>

### `RATE`

`macro` | [progs/src/sbtone.c:25](../../progs/src/sbtone.c#L25)

```c
#define RATE
```

---

<a id="buf"></a>

### `BUF`

`macro` | [progs/src/sbtone.c:26](../../progs/src/sbtone.c#L26)

```c
#define BUF
```

---

<a id="window_ms"></a>

### `WINDOW_MS`

`macro` | [progs/src/sbtone.c:27](../../progs/src/sbtone.c#L27)

```c
#define WINDOW_MS
```

---
