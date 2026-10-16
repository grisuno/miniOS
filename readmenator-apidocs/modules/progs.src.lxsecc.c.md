# `progs/src/lxsecc.c`

> Source: [progs/src/lxsecc.c:1](../../progs/src/lxsecc.c#L1) | language `c` | coverage 6.2% | [API index](../index.md)

## Contents

- **Functions:** [`main`](#main)
- **Macros:** [`_GNU_SOURCE`](#_gnu_source), [`LXSECC_EXEC_FLAG`](#lxsecc_exec_flag), [`LXSECC_EXEC_CODE`](#lxsecc_exec_code), [`LXSECC_OK_CODE`](#lxsecc_ok_code), [`LXSECC_BAD_CODE`](#lxsecc_bad_code), [`LXSECC_EXE_MAX`](#lxsecc_exe_max), [`LXSECC_NAME`](#lxsecc_name), [`LXSECC_NAME_MAX`](#lxsecc_name_max), [`LXSECC_ERRNO_A`](#lxsecc_errno_a), [`LXSECC_ERRNO_B`](#lxsecc_errno_b), [`LXSECC_PAGE`](#lxsecc_page), [`LXSECC_STATUS_MASK`](#lxsecc_status_mask), [`LXSECC_STATUS_SHIFT`](#lxsecc_status_shift), [`LXSECC_STATUS_BYTE`](#lxsecc_status_byte)

## Functions

<a id="main"></a>

### `main`

`function` | [progs/src/lxsecc.c:215](../../progs/src/lxsecc.c#L215)

```c
int main(int argc, char **argv)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `argc` | `int` |  |  |
| `argv` | `char **` |  |  |

**Returns:** `int`

---

## Macros

<a id="_gnu_source"></a>

### `_GNU_SOURCE`

`macro` | [progs/src/lxsecc.c:13](../../progs/src/lxsecc.c#L13)

```c
#define _GNU_SOURCE
```

lxsecc.c - Linux seccomp-bpf, prctl and /proc/self/exe probe (FreeDom readiness step 5, docs/spec/kernel.md "Linux seccomp-bpf, prctl and /proc/self/exe").

Exercises exactly what FreeDom's tab worker relies on: re-exec through
/proc/self/exe, no_new_privs, the dumpable flag, and a seccomp filter whose
allowlist, ERRNO and KILL actions, W^X argument check, inheritance across
fork, stacking and strict mode all behave like Linux. Every filter is
installed in a forked child so the probe itself stays unconfined. Prints
"lxsecc: <check> ok" or "lxsecc: <check> FAIL <detail>", then "lxsecc: all
ok" with exit 0, or "lxsecc: <n> failed" with exit 1.

---

<a id="lxsecc_exec_flag"></a>

### `LXSECC_EXEC_FLAG`

`macro` | [progs/src/lxsecc.c:28](../../progs/src/lxsecc.c#L28)

```c
#define LXSECC_EXEC_FLAG
```

---

<a id="lxsecc_exec_code"></a>

### `LXSECC_EXEC_CODE`

`macro` | [progs/src/lxsecc.c:29](../../progs/src/lxsecc.c#L29)

```c
#define LXSECC_EXEC_CODE
```

---

<a id="lxsecc_ok_code"></a>

### `LXSECC_OK_CODE`

`macro` | [progs/src/lxsecc.c:30](../../progs/src/lxsecc.c#L30)

```c
#define LXSECC_OK_CODE
```

---

<a id="lxsecc_bad_code"></a>

### `LXSECC_BAD_CODE`

`macro` | [progs/src/lxsecc.c:31](../../progs/src/lxsecc.c#L31)

```c
#define LXSECC_BAD_CODE
```

---

<a id="lxsecc_exe_max"></a>

### `LXSECC_EXE_MAX`

`macro` | [progs/src/lxsecc.c:32](../../progs/src/lxsecc.c#L32)

```c
#define LXSECC_EXE_MAX
```

---

<a id="lxsecc_name"></a>

### `LXSECC_NAME`

`macro` | [progs/src/lxsecc.c:33](../../progs/src/lxsecc.c#L33)

```c
#define LXSECC_NAME
```

---

<a id="lxsecc_name_max"></a>

### `LXSECC_NAME_MAX`

`macro` | [progs/src/lxsecc.c:34](../../progs/src/lxsecc.c#L34)

```c
#define LXSECC_NAME_MAX
```

---

<a id="lxsecc_errno_a"></a>

### `LXSECC_ERRNO_A`

`macro` | [progs/src/lxsecc.c:35](../../progs/src/lxsecc.c#L35)

```c
#define LXSECC_ERRNO_A
```

---

<a id="lxsecc_errno_b"></a>

### `LXSECC_ERRNO_B`

`macro` | [progs/src/lxsecc.c:36](../../progs/src/lxsecc.c#L36)

```c
#define LXSECC_ERRNO_B
```

---

<a id="lxsecc_page"></a>

### `LXSECC_PAGE`

`macro` | [progs/src/lxsecc.c:37](../../progs/src/lxsecc.c#L37)

```c
#define LXSECC_PAGE
```

---

<a id="lxsecc_status_mask"></a>

### `LXSECC_STATUS_MASK`

`macro` | [progs/src/lxsecc.c:38](../../progs/src/lxsecc.c#L38)

```c
#define LXSECC_STATUS_MASK
```

---

<a id="lxsecc_status_shift"></a>

### `LXSECC_STATUS_SHIFT`

`macro` | [progs/src/lxsecc.c:39](../../progs/src/lxsecc.c#L39)

```c
#define LXSECC_STATUS_SHIFT
```

---

<a id="lxsecc_status_byte"></a>

### `LXSECC_STATUS_BYTE`

`macro` | [progs/src/lxsecc.c:40](../../progs/src/lxsecc.c#L40)

```c
#define LXSECC_STATUS_BYTE
```

---
