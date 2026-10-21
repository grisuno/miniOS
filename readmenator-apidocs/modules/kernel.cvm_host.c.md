# `kernel/cvm_host.c`

> Source: [kernel/cvm_host.c:1](../../kernel/cvm_host.c#L1) | language `c` | coverage 33.3% | [API index](../index.md)

## Contents

- **Structs:** [`kout_sink`](#kout_sink)
- **Functions:** [`cvm_main`](#cvm_main)

## Structs

<a id="kout_sink"></a>

### `kout_sink`

`struct` | [kernel/cvm_host.c:281](../../kernel/cvm_host.c#L281)

```c
typedef struct
```

Output sink for kformat: a stream (FILE*) or a bounded buffer.

The buffer form follows the C library: at most cap-1 characters plus a terminating NUL are stored, while len keeps the length the whole format would have produced (what sprintf and snprintf return).

---

## Functions

<a id="cvm_main"></a>

### `cvm_main`

`function` | [kernel/cvm_host.c:497](../../kernel/cvm_host.c#L497)

```c
int cvm_main(int argc, char **argv)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `argc` | `int` |  |  |
| `argv` | `char **` |  |  |

**Returns:** `int`

---
