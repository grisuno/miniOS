# `progs/src/execho.c`

> Source: [progs/src/execho.c:1](../../progs/src/execho.c#L1) | language `c` | coverage 25.0% | [API index](../index.md)

execho -- fork(57) + execve(59) + wait4(61) probe.

## Contents

- **Functions:** [`program`](#program), [`path`](#path), [`lmain`](#lmain)

## Functions

<a id="program"></a>

### `program`

`function` | [progs/src/execho.c:5](../../progs/src/execho.c#L5)

```c
* * Proves the UNIX process composition the kernel lacked: a child * produced by fork replaces its image with execve and the parent * reaps the REPLACED program (not a clone). First child execs * bin/
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `clone` | `not a` |  |  |

**Returns:** `* * Proves the UNIX process composition the kernel lacked: a child * produced by fork replaces its image with execve and the parent * reaps the REPLACED`

---

<a id="path"></a>

### `path`

`function` | [progs/src/execho.c:7](../../progs/src/execho.c#L7)

```c
* execs a ghost path (must fail -2, exits 42). The parent checks * both wait4 results with Linux...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fail` | `must -2` |  |  |
| `exits` |  |  |  |

**Returns:** `* execs a ghost`

---

<a id="lmain"></a>

### `lmain`

`function` | [progs/src/execho.c:37](../../progs/src/execho.c#L37)

```c
int lmain(void)
```

**Returns:** `int`

---
