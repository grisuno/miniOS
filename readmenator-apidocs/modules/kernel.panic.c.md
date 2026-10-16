# `kernel/panic.c`

> Source: [kernel/panic.c:1](../../kernel/panic.c#L1) | language `c` | coverage 100.0% | [API index](../index.md)

Docstring: kernel/panic.c -- Kernel panic screen.

## Contents

- **Functions:** [`panic_screen`](#panic_screen)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_kernel_panic_c__panic_screen(["panic_screen"])
    n_headers_panic_h__panic_backtrace["panic.panic_backtrace"]
    n_kernel_panic_c__panic_screen -.-> n_headers_panic_h__panic_backtrace
```

## Functions

<a id="panic_screen"></a>

### `panic_screen`

`function` | [kernel/panic.c:96](../../kernel/panic.c#L96)

```c
void panic_screen(unsigned long vector, unsigned long err, unsigned long rip, unsigned long rsp, unsigned long rbp, int halt)
```

Docstring: Paint the panic screen for an unrecoverable fault and halt when asked. vector/err/rip/rsp come from the trap frame, rbp is the faulting frame pointer. halt != 0 ends in hlt (real faults); halt == 0 returns (the `panic` builtin demo).

Re-entry halts silently: the banner path itself faulted, nothing more can print.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `vector` | `unsigned long` |  |  |
| `err` | `unsigned long` |  |  |
| `rip` | `unsigned long` |  |  |
| `rsp` | `unsigned long` |  |  |
| `rbp` | `unsigned long` |  |  |
| `halt` | `int` |  |  |

*Calls:* [`panic_backtrace`](headers.panic.h.md#panic_backtrace)

---
