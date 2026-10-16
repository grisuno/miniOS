# `progs/src/lxproc.c`

> Source: [progs/src/lxproc.c:1](../../progs/src/lxproc.c#L1) | language `c` | coverage 50.0% | [API index](../index.md)

## Contents

- **Structs:** [`lxproc_note`](#lxproc_note)
- **Functions:** [`main`](#main)
- **Macros:** [`_GNU_SOURCE`](#_gnu_source), [`LXPROC_EXE_MAX`](#lxproc_exe_max), [`LXPROC_CHILD_CODE`](#lxproc_child_code), [`LXPROC_OK`](#lxproc_ok), [`LXPROC_BAD`](#lxproc_bad)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_progs_src_lxproc_c__main(["main"])
    n_progs_topogpt3_topogpt3_c__fflush["topogpt3.fflush"]
    n_progs_src_lxproc_c__main -.-> n_progs_topogpt3_topogpt3_c__fflush
```

## Structs

<a id="lxproc_note"></a>

### `lxproc_note`

`struct` | [progs/src/lxproc.c:35](../../progs/src/lxproc.c#L35)

```c
struct lxproc_note
```

MiniOS process note: name, 4-byte descriptor, both 4-byte padded.

---

## Functions

<a id="main"></a>

### `main`

`function` | [progs/src/lxproc.c:91](../../progs/src/lxproc.c#L91)

```c
int main(void)
```

**Returns:** `int`

*Calls:* [`fflush`](progs.topogpt3.topogpt3.c.md#fflush)

---

## Macros

<a id="_gnu_source"></a>

### `_GNU_SOURCE`

`macro` | [progs/src/lxproc.c:17](../../progs/src/lxproc.c#L17)

```c
#define _GNU_SOURCE
```

lxproc.c - foreground process-note probe (docs/spec/shell-fs.md, "Process note", and progs/minios_abi.h).

Built twice from this one file: bin/lxproc carries the MiniOS process note
(LXPROC_PROCESS_NOTE defined), bin/lxframe does not. Run bare in the
foreground, the shell executes lxframe in its pid-0 exec frame and lxproc
as an isolated process, and the probe reports what that gives it:

  lxproc: exe /<path>         what readlink("/proc/self/exe") answers
  lxproc: fork ok             a forked child ran and was reaped (process)
  lxproc: fork unavailable    fork answered ENOSYS (exec frame)
  lxproc: fork FAIL <errno>   any other outcome

Exit code: 0 when every line is one of the expected outcomes, 1 otherwise.
The BDD scenario pins which fork line each variant prints.

---

<a id="lxproc_exe_max"></a>

### `LXPROC_EXE_MAX`

`macro` | [progs/src/lxproc.c:27](../../progs/src/lxproc.c#L27)

```c
#define LXPROC_EXE_MAX
```

Bytes kept from the /proc/self/exe answer.

---

<a id="lxproc_child_code"></a>

### `LXPROC_CHILD_CODE`

`macro` | [progs/src/lxproc.c:29](../../progs/src/lxproc.c#L29)

```c
#define LXPROC_CHILD_CODE
```

Exit status the forked child reports, so the reap proves it ran.

---

<a id="lxproc_ok"></a>

### `LXPROC_OK`

`macro` | [progs/src/lxproc.c:30](../../progs/src/lxproc.c#L30)

```c
#define LXPROC_OK
```

---

<a id="lxproc_bad"></a>

### `LXPROC_BAD`

`macro` | [progs/src/lxproc.c:31](../../progs/src/lxproc.c#L31)

```c
#define LXPROC_BAD
```

---
