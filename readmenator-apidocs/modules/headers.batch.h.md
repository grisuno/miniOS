# `headers/batch.h`

> Source: [headers/batch.h:1](../../headers/batch.h#L1) | language `h` | coverage 8.3% | [API index](../index.md)

Docstring: batch.h -- Batched synchronous syscall submission.

## Contents

- **Structs:** [`batch_op_t`](#batch_op_t)
- **Functions:** [`batch_exec`](#batch_exec)
- **Macros:** [`BATCH_MAX_OPS`](#batch_max_ops), [`BATCH_OP_NOP`](#batch_op_nop), [`BATCH_OP_YIELD`](#batch_op_yield), [`BATCH_OP_TIME`](#batch_op_time), [`BATCH_OP_GETPID`](#batch_op_getpid), [`BATCH_OK`](#batch_ok), [`BATCH_ERR_COUNT`](#batch_err_count), [`BATCH_ERR_PTR`](#batch_err_ptr), [`BATCH_ERR_OPCODE`](#batch_err_opcode)

## Structs

<a id="batch_op_t"></a>

### `batch_op_t`

`struct` | [headers/batch.h:53](../../headers/batch.h#L53)

```c
typedef struct
```

---

## Functions

<a id="batch_exec"></a>

### `batch_exec`

`function` | [headers/batch.h:62](../../headers/batch.h#L62)

```c
long batch_exec(const batch_op_t *ops, long *results, int count, int *completed, batch_handler_t dispatch);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ops` | `batch_op_t *` |  |  |
| `results` | `long *` |  |  |
| `count` | `int` |  |  |
| `completed` | `int *` |  |  |
| `dispatch` | `batch_handler_t` |  |  |

**Returns:** `long`

---

## Macros

<a id="batch_max_ops"></a>

### `BATCH_MAX_OPS`

`macro` | [headers/batch.h:41](../../headers/batch.h#L41)

```c
#define BATCH_MAX_OPS
```

---

<a id="batch_op_nop"></a>

### `BATCH_OP_NOP`

`macro` | [headers/batch.h:43](../../headers/batch.h#L43)

```c
#define BATCH_OP_NOP
```

---

<a id="batch_op_yield"></a>

### `BATCH_OP_YIELD`

`macro` | [headers/batch.h:44](../../headers/batch.h#L44)

```c
#define BATCH_OP_YIELD
```

---

<a id="batch_op_time"></a>

### `BATCH_OP_TIME`

`macro` | [headers/batch.h:45](../../headers/batch.h#L45)

```c
#define BATCH_OP_TIME
```

---

<a id="batch_op_getpid"></a>

### `BATCH_OP_GETPID`

`macro` | [headers/batch.h:46](../../headers/batch.h#L46)

```c
#define BATCH_OP_GETPID
```

---

<a id="batch_ok"></a>

### `BATCH_OK`

`macro` | [headers/batch.h:48](../../headers/batch.h#L48)

```c
#define BATCH_OK
```

---

<a id="batch_err_count"></a>

### `BATCH_ERR_COUNT`

`macro` | [headers/batch.h:49](../../headers/batch.h#L49)

```c
#define BATCH_ERR_COUNT
```

---

<a id="batch_err_ptr"></a>

### `BATCH_ERR_PTR`

`macro` | [headers/batch.h:50](../../headers/batch.h#L50)

```c
#define BATCH_ERR_PTR
```

---

<a id="batch_err_opcode"></a>

### `BATCH_ERR_OPCODE`

`macro` | [headers/batch.h:51](../../headers/batch.h#L51)

```c
#define BATCH_ERR_OPCODE
```

---
