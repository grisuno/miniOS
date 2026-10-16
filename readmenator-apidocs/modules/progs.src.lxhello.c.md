# `progs/src/lxhello.c`

> Source: [progs/src/lxhello.c:1](../../progs/src/lxhello.c#L1) | language `c` | coverage 25.0% | [API index](../index.md)

## Contents

- **Functions:** [`lmain`](#lmain)
- **Macros:** [`SYS_write`](#sys_write), [`SYS_exit`](#sys_exit)

## Functions

<a id="lmain"></a>

### `lmain`

`function` | [progs/src/lxhello.c:46](../../progs/src/lxhello.c#L46)

```c
int lmain(long argc, char **argv)
```

Entry called by _start with the real argc/argv pulled off the stack.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `argc` | `long` |  |  |
| `argv` | `char **` |  |  |

**Returns:** `int`

---

## Macros

<a id="sys_write"></a>

### `SYS_write`

`macro` | [progs/src/lxhello.c:20](../../progs/src/lxhello.c#L20)

```c
#define SYS_write
```

---

<a id="sys_exit"></a>

### `SYS_exit`

`macro` | [progs/src/lxhello.c:21](../../progs/src/lxhello.c#L21)

```c
#define SYS_exit
```

---
