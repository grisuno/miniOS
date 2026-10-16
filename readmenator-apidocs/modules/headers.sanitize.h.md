# `headers/sanitize.h`

> Source: [headers/sanitize.h:1](../../headers/sanitize.h#L1) | language `h` | coverage 20.0% | [API index](../index.md)

Docstring: sanitize.h -- Single choke point for syscall argument checks.

## Contents

- **Macros:** [`SANITIZE_LEN_NEG`](#sanitize_len_neg), [`SANITIZE_RANGE`](#sanitize_range), [`SANITIZE_STR`](#sanitize_str), [`SANITIZE_COPY_IN`](#sanitize_copy_in)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_headers_sanitize_h__SANITIZE_STR(["SANITIZE_STR"])
    n_headers_kernel_h__user_str_ok["kernel.user_str_ok"]
    n_headers_sanitize_h__SANITIZE_STR -.-> n_headers_kernel_h__user_str_ok
```

## Macros

<a id="sanitize_len_neg"></a>

### `SANITIZE_LEN_NEG`

`macro` | [headers/sanitize.h:32](../../headers/sanitize.h#L32)

```c
#define SANITIZE_LEN_NEG(var)
```

---

<a id="sanitize_range"></a>

### `SANITIZE_RANGE`

`macro` | [headers/sanitize.h:37](../../headers/sanitize.h#L37)

```c
#define SANITIZE_RANGE(ptr, len)
```

*Called by:* [`proc_sec_prctl`](kernel.proc_sec.c.md#proc_sec_prctl), [`proc_sec_seccomp`](kernel.proc_sec.c.md#proc_sec_seccomp), [`DOOM_FRAME`](kernel.syscalls.c.md#doom_frame), [`FIONREAD`](kernel.syscalls.c.md#fionread), [`PROC_SELF_EXE`](kernel.syscalls.c.md#proc_self_exe), [`clock_gettime`](kernel.syscalls.c.md#clock_gettime), [`node`](kernel.syscalls.c.md#node), [`view`](kernel.syscalls.c.md#view)

---

<a id="sanitize_str"></a>

### `SANITIZE_STR`

`macro` | [headers/sanitize.h:43](../../headers/sanitize.h#L43)

```c
#define SANITIZE_STR(ptr, maxlen)
```

*Calls:* [`user_str_ok`](headers.kernel.h.md#user_str_ok)

*Called by:* [`PROC_SELF_EXE`](kernel.syscalls.c.md#proc_self_exe), [`sys_linux_execve`](kernel.syscalls_proc.c.md#sys_linux_execve)

---

<a id="sanitize_copy_in"></a>

### `SANITIZE_COPY_IN`

`macro` | [headers/sanitize.h:49](../../headers/sanitize.h#L49)

```c
#define SANITIZE_COPY_IN(kbuf, uptr, count, elemsz)
```

---
