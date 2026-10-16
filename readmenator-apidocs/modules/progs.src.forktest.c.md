# `progs/src/forktest.c`

> Source: [progs/src/forktest.c:1](../../progs/src/forktest.c#L1) | language `c` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`_start`](#_start), [`this`](#this)
- **Macros:** [`SYS_read`](#sys_read), [`SYS_write`](#sys_write), [`SYS_close`](#sys_close), [`SYS_pipe`](#sys_pipe), [`SYS_yield`](#sys_yield), [`SYS_fork`](#sys_fork), [`SYS_exit`](#sys_exit), [`SYS_wait4`](#sys_wait4)

## Functions

<a id="_start"></a>

### `_start`

`function` | [progs/src/forktest.c:56](../../progs/src/forktest.c#L56)

```c
void _start(void)
```

---

<a id="this"></a>

### `this`

`function` | [progs/src/forktest.c:115](../../progs/src/forktest.c#L115)

```c
* this (and the child's closes must survive below). */ fx_syscall6(SYS_close, pfd[1], 0, 0, 0, 0, 0);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `below` | `and the child's closes must survive` |  |  |

**Returns:** `*`

---

## Macros

<a id="sys_read"></a>

### `SYS_read`

`macro` | [progs/src/forktest.c:30](../../progs/src/forktest.c#L30)

```c
#define SYS_read
```

---

<a id="sys_write"></a>

### `SYS_write`

`macro` | [progs/src/forktest.c:31](../../progs/src/forktest.c#L31)

```c
#define SYS_write
```

---

<a id="sys_close"></a>

### `SYS_close`

`macro` | [progs/src/forktest.c:32](../../progs/src/forktest.c#L32)

```c
#define SYS_close
```

---

<a id="sys_pipe"></a>

### `SYS_pipe`

`macro` | [progs/src/forktest.c:33](../../progs/src/forktest.c#L33)

```c
#define SYS_pipe
```

---

<a id="sys_yield"></a>

### `SYS_yield`

`macro` | [progs/src/forktest.c:34](../../progs/src/forktest.c#L34)

```c
#define SYS_yield
```

---

<a id="sys_fork"></a>

### `SYS_fork`

`macro` | [progs/src/forktest.c:35](../../progs/src/forktest.c#L35)

```c
#define SYS_fork
```

---

<a id="sys_exit"></a>

### `SYS_exit`

`macro` | [progs/src/forktest.c:36](../../progs/src/forktest.c#L36)

```c
#define SYS_exit
```

---

<a id="sys_wait4"></a>

### `SYS_wait4`

`macro` | [progs/src/forktest.c:37](../../progs/src/forktest.c#L37)

```c
#define SYS_wait4
```

---
