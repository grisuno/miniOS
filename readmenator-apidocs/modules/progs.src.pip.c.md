# `progs/src/pip.c`

> Source: [progs/src/pip.c:1](../../progs/src/pip.c#L1) | language `c` | coverage 87.5% | [API index](../index.md)

pip -- launcher for `python3 -m pip`, and pip3 as a copy of this image.

## Contents

- **Structs:** [`pip_note`](#pip_note)
- **Functions:** [`main`](#main)
- **Macros:** [`PIP_PYTHON_PATH`](#pip_python_path), [`PIP_MODULE_FLAG`](#pip_module_flag), [`PIP_MODULE_NAME`](#pip_module_name), [`PIP_PREFIX_WORDS`](#pip_prefix_words), [`PIP_EXEC_FAILED`](#pip_exec_failed)

## Structs

<a id="pip_note"></a>

### `pip_note`

`struct` | [progs/src/pip.c:30](../../progs/src/pip.c#L30)

```c
struct pip_note
```

MiniOS process note: name, 4-byte descriptor, both 4-byte padded.

---

## Functions

<a id="main"></a>

### `main`

`function` | [progs/src/pip.c:45](../../progs/src/pip.c#L45)

```c
int main(int argc, char **argv)
```

Build argv and exec the interpreter; returns only on failure.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `argc` | `int` |  |  |
| `argv` | `char **` |  |  |

**Returns:** `int`

---

## Macros

<a id="pip_python_path"></a>

### `PIP_PYTHON_PATH`

`macro` | [progs/src/pip.c:19](../../progs/src/pip.c#L19)

```c
#define PIP_PYTHON_PATH
```

Interpreter path inside the guest; cwd independent.

---

<a id="pip_module_flag"></a>

### `PIP_MODULE_FLAG`

`macro` | [progs/src/pip.c:21](../../progs/src/pip.c#L21)

```c
#define PIP_MODULE_FLAG
```

Python arguments that select the pip module.

---

<a id="pip_module_name"></a>

### `PIP_MODULE_NAME`

`macro` | [progs/src/pip.c:22](../../progs/src/pip.c#L22)

```c
#define PIP_MODULE_NAME
```

---

<a id="pip_prefix_words"></a>

### `PIP_PREFIX_WORDS`

`macro` | [progs/src/pip.c:24](../../progs/src/pip.c#L24)

```c
#define PIP_PREFIX_WORDS
```

Prefix words added in front of the caller's arguments.

---

<a id="pip_exec_failed"></a>

### `PIP_EXEC_FAILED`

`macro` | [progs/src/pip.c:26](../../progs/src/pip.c#L26)

```c
#define PIP_EXEC_FAILED
```

Exit status for a failed execve.

---
