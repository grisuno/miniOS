# `progs/src/w1.c`

> Source: [progs/src/w1.c:1](../../progs/src/w1.c#L1) | language `c` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`write`](#write), [`main`](#main)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_progs_src_w1_c__main(["main"])
    n_progs_src_w1_c__write(["write"])
    n_progs_src_w1_c__main --> n_progs_src_w1_c__write
```

## Functions

<a id="write"></a>

### `write`

`function` | [progs/src/w1.c:1](../../progs/src/w1.c#L1)

```c
int write(int fd, char *buf, int n);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `int` |  |  |
| `buf` | `char *` |  |  |
| `n` | `int` |  |  |

**Returns:** `int`

*Called by:* [`main`](#main)

---

<a id="main"></a>

### `main`

`function` | [progs/src/w1.c:3](../../progs/src/w1.c#L3)

```c
int main(void)
```

**Returns:** `int`

*Calls:* [`write`](#write)

---
