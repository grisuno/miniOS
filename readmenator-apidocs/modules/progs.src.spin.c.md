# `progs/src/spin.c`

> Source: [progs/src/spin.c:1](../../progs/src/spin.c#L1) | language `c` | coverage 16.7% | [API index](../index.md)

## Contents

- **Functions:** [`lmain`](#lmain)
- **Macros:** [`SPIN_WLW`](#spin_wlw), [`SPIN_WLH`](#spin_wlh), [`SPIN_WLA`](#spin_wla), [`SPIN_WLB`](#spin_wlb)

## Functions

<a id="lmain"></a>

### `lmain`

`function` | [progs/src/spin.c:225](../../progs/src/spin.c#L225)

```c
int lmain(long argc, char **argv)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `argc` | `long` |  |  |
| `argv` | `char **` |  |  |

**Returns:** `int`

---

## Macros

<a id="spin_wlw"></a>

### `SPIN_WLW`

`macro` | [progs/src/spin.c:56](../../progs/src/spin.c#L56)

```c
#define SPIN_WLW
```

---- Live Wayland-mini publisher (same wire, no libc) ----
Attaches one 200x90 stripe surface, then republishes a shifting
stripe plus a commit per frame. Tiny enough to survive startup
preempts that kill glibc-heavy clients, so the server tiles live
multiprocess frames while the scheduler proof stays honest.

---

<a id="spin_wlh"></a>

### `SPIN_WLH`

`macro` | [progs/src/spin.c:57](../../progs/src/spin.c#L57)

```c
#define SPIN_WLH
```

---

<a id="spin_wla"></a>

### `SPIN_WLA`

`macro` | [progs/src/spin.c:58](../../progs/src/spin.c#L58)

```c
#define SPIN_WLA
```

---

<a id="spin_wlb"></a>

### `SPIN_WLB`

`macro` | [progs/src/spin.c:59](../../progs/src/spin.c#L59)

```c
#define SPIN_WLB
```

---
