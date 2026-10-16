# `headers/shell.h`

> Source: [headers/shell.h:1](../../headers/shell.h#L1) | language `h` | coverage 75.0% | [API index](../index.md)

shell.h -- shared shell constants and the line reader/parser reused by

## Contents

- **Functions:** [`shell_readline_buf`](#shell_readline_buf), [`shell_parse`](#shell_parse), [`shell_parse_long`](#shell_parse_long), [`shell_parse_pid`](#shell_parse_pid), [`shell_cmd_sh`](#shell_cmd_sh)
- **Macros:** [`CMD_BUF_SZ`](#cmd_buf_sz), [`MAX_ARGS`](#max_args)

## Functions

<a id="shell_readline_buf"></a>

### `shell_readline_buf`

`function` | [headers/shell.h:18](../../headers/shell.h#L18)

```c
void shell_readline_buf(char *buf, int size);
```

Read one line into buf with arrow-key editing; used by the built-in editor to edit file text.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `buf` | `char *` |  |  |
| `size` | `int` |  |  |

---

<a id="shell_parse"></a>

### `shell_parse`

`function` | [headers/shell.h:21](../../headers/shell.h#L21)

```c
int shell_parse(char *line, char **argv, int max_args);
```

Tokenize `line` into up to `max_args` argv entries; returns argc.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `line` | `char *` |  |  |
| `argv` | `char **` |  |  |
| `max_args` | `int` |  |  |

**Returns:** `int`

---

<a id="shell_parse_long"></a>

### `shell_parse_long`

`function` | [headers/shell.h:29](../../headers/shell.h#L29)

```c
int shell_parse_long(const char *s, long *out);
```

Strict signed decimal parse for numeric shell/editor operands: an optional sign followed by at least one digit, whole string consumed, fail-closed on empty input, trailing garbage or overflow.

Returns 1 and sets *out on success, 0 otherwise. Replaces katol (which stops at the first non-digit and wraps on overflow) at every builtin call site, so `kill 12abc` is a diagnostic instead of pid 12.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `s` | `char *` |  |  |
| `out` | `long *` |  |  |

**Returns:** `int`

---

<a id="shell_parse_pid"></a>

### `shell_parse_pid`

`function` | [headers/shell.h:34](../../headers/shell.h#L34)

```c
int shell_parse_pid(const char *s, int min_pid, int *out);
```

Bounded pid parse: strict shell_parse_long plus min_pid <= pid < MAX_PROCS.

Unifies the wait/kill/vmmap range checks so the bound cannot drift per call site. Returns 1 and sets *out on success, 0 otherwise.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `s` | `char *` |  |  |
| `min_pid` | `int` |  |  |
| `out` | `int *` |  |  |

**Returns:** `int`

---

<a id="shell_cmd_sh"></a>

### `shell_cmd_sh`

`function` | [headers/shell.h:39](../../headers/shell.h#L39)

```c
int shell_cmd_sh(int argc, char **argv);
```

Execute a shell script: read `path` line by line, skip blanks and `#` comments, parse each line and dispatch it through the normal builtin/ program path.

Returns 0 on success, 1 on file error.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `argc` | `int` |  |  |
| `argv` | `char **` |  |  |

**Returns:** `int`

---

## Macros

<a id="cmd_buf_sz"></a>

### `CMD_BUF_SZ`

`macro` | [headers/shell.h:13](../../headers/shell.h#L13)

```c
#define CMD_BUF_SZ
```

---

<a id="max_args"></a>

### `MAX_ARGS`

`macro` | [headers/shell.h:14](../../headers/shell.h#L14)

```c
#define MAX_ARGS
```

---
