# `progs/src/hello.c`

> Source: [progs/src/hello.c:1](../../progs/src/hello.c#L1) | language `c` | coverage 33.3% | [API index](../index.md)

## Contents

- **Functions:** [`printf`](#printf), [`main`](#main)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_progs_src_hello_c__main(["main"])
    n_progs_src_hello_c__printf(["printf"])
    n_progs_src_hello_c__main --> n_progs_src_hello_c__printf
```

## Functions

<a id="printf"></a>

### `printf`

`function` `extern` | [progs/src/hello.c:2](../../progs/src/hello.c#L2)

```c
extern int printf(const char *fmt, ...);
```

MiniOS test program — compiled as relocatable .o, loaded by kernel ELF loader

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fmt` | `char *` |  |  |
| `...` |  |  |  |

**Returns:** `int`

*Called by:* [`main`](#main)

---

<a id="main"></a>

### `main`

`function` | [progs/src/hello.c:4](../../progs/src/hello.c#L4)

```c
int main(int argc, char **argv)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `argc` | `int` |  |  |
| `argv` | `char **` |  |  |

**Returns:** `int`

*Calls:* [`printf`](#printf)

---
