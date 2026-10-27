# `progs/src/apsse.c`

> Source: [progs/src/apsse.c:1](../../progs/src/apsse.c#L1) | language `c` | coverage 7.1% | [API index](../index.md)

## Contents

- **Structs:** [`apsse_job`](#apsse_job)
- **Functions:** [`main`](#main)
- **Macros:** [`_GNU_SOURCE`](#_gnu_source), [`APSSE_THREADS`](#apsse_threads), [`APSSE_ROUNDS`](#apsse_rounds), [`APSSE_SEED`](#apsse_seed), [`APSSE_BUF`](#apsse_buf), [`APSSE_NEEDLE`](#apsse_needle), [`APSSE_MAP_ROUNDS`](#apsse_map_rounds), [`APSSE_MAP_BYTES`](#apsse_map_bytes), [`APSSE_MAP_FILL`](#apsse_map_fill), [`APSSE_OK`](#apsse_ok), [`APSSE_BAD`](#apsse_bad)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_progs_src_apsse_c__main(["main"])
    n_kernel_string_c__memset["string.memset"]
    n_progs_src_apsse_c__main -.-> n_kernel_string_c__memset
```

## Structs

<a id="apsse_job"></a>

### `apsse_job`

`struct` | [progs/src/apsse.c:42](../../progs/src/apsse.c#L42)

```c
struct apsse_job
```

---

## Functions

<a id="main"></a>

### `main`

`function` | [progs/src/apsse.c:81](../../progs/src/apsse.c#L81)

```c
int main(void)
```

**Returns:** `int`

*Calls:* [`memset`](kernel.string.c.md#memset)

---

## Macros

<a id="_gnu_source"></a>

### `_GNU_SOURCE`

`macro` | [progs/src/apsse.c:23](../../progs/src/apsse.c#L23)

```c
#define _GNU_SOURCE
```

apsse.c - SSE in glibc threads on every CPU (docs/spec/smp-sched.md, "Per-CPU control registers").

CR0 and CR4 are per-CPU: an AP that never sets CR4.OSFXSR raises #UD on
the first XMM instruction a thread executes there, which is how the
FreeDom browser's fetch threads died under -smp 2 (glibc's string
routines are SSE2). Each worker grinds SSE2 integer and double arithmetic
plus memchr for a needle that moves every round through a private buffer
(so no round can be hoisted) for APSSE_ROUNDS rounds (many timer
ticks each, so idle APs claim them) and checks every result against one
reference the main thread computes first; the scheduler hands CLONE_VM
threads to idle APs, so with -smp 2 the work lands there.

While the workers run, the main thread maps, fills and unmaps an anonymous
region APSSE_MAP_ROUNDS times: each munmap frees frames a worker's CPU
shares the address space with, which is the TLB shootdown path (the smp
builtin counts tlb_shootdowns).

Prints "apsse: ok threads=<n>" and exits 0, or "apsse: FAIL <detail>" and
exits 1. A CPU without SSE kills the process with an exception dump
before either line.

---

<a id="apsse_threads"></a>

### `APSSE_THREADS`

`macro` | [progs/src/apsse.c:31](../../progs/src/apsse.c#L31)

```c
#define APSSE_THREADS
```

---

<a id="apsse_rounds"></a>

### `APSSE_ROUNDS`

`macro` | [progs/src/apsse.c:32](../../progs/src/apsse.c#L32)

```c
#define APSSE_ROUNDS
```

---

<a id="apsse_seed"></a>

### `APSSE_SEED`

`macro` | [progs/src/apsse.c:33](../../progs/src/apsse.c#L33)

```c
#define APSSE_SEED
```

---

<a id="apsse_buf"></a>

### `APSSE_BUF`

`macro` | [progs/src/apsse.c:34](../../progs/src/apsse.c#L34)

```c
#define APSSE_BUF
```

---

<a id="apsse_needle"></a>

### `APSSE_NEEDLE`

`macro` | [progs/src/apsse.c:35](../../progs/src/apsse.c#L35)

```c
#define APSSE_NEEDLE
```

---

<a id="apsse_map_rounds"></a>

### `APSSE_MAP_ROUNDS`

`macro` | [progs/src/apsse.c:36](../../progs/src/apsse.c#L36)

```c
#define APSSE_MAP_ROUNDS
```

---

<a id="apsse_map_bytes"></a>

### `APSSE_MAP_BYTES`

`macro` | [progs/src/apsse.c:37](../../progs/src/apsse.c#L37)

```c
#define APSSE_MAP_BYTES
```

---

<a id="apsse_map_fill"></a>

### `APSSE_MAP_FILL`

`macro` | [progs/src/apsse.c:38](../../progs/src/apsse.c#L38)

```c
#define APSSE_MAP_FILL
```

---

<a id="apsse_ok"></a>

### `APSSE_OK`

`macro` | [progs/src/apsse.c:39](../../progs/src/apsse.c#L39)

```c
#define APSSE_OK
```

---

<a id="apsse_bad"></a>

### `APSSE_BAD`

`macro` | [progs/src/apsse.c:40](../../progs/src/apsse.c#L40)

```c
#define APSSE_BAD
```

---
