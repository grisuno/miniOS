# `kernel/batch.c`

> Source: [kernel/batch.c:1](../../kernel/batch.c#L1) | language `c` | coverage 100.0% | [API index](../index.md)

Docstring: kernel/batch.c -- Ordered batch executor.

## Contents

- **Functions:** [`batch_exec`](#batch_exec)

## Functions

<a id="batch_exec"></a>

### `batch_exec`

`function` | [kernel/batch.c:19](../../kernel/batch.c#L19)

```c
long batch_exec(const batch_op_t *ops, long *results, int count, int *completed, batch_handler_t dispatch)
```

Docstring: Run ops in order, storing one result per index.

Returns BATCH_OK when every operation dispatched without a negative
result. On the first negative dispatch result, stops immediately and
returns that error. completed always reports the number of successful
operations, including on early refusal (zero). A null dispatch table
entry for a known opcode is treated as BATCH_ERR_OPCODE, never called.

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
