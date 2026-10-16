# `kernel/redirect.c`

> Source: [kernel/redirect.c:1](../../kernel/redirect.c#L1) | language `c` | coverage 25.0% | [API index](../index.md)

================================================================

## Contents

- **Functions:** [`shell_report_exit`](#shell_report_exit), [`shell_report`](#shell_report), [`shell_take_redirect`](#shell_take_redirect)

## Functions

<a id="shell_report_exit"></a>

### `shell_report_exit`

`function` | [kernel/redirect.c:11](../../kernel/redirect.c#L11)

```c
void shell_report_exit(int code)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `code` | `int` |  |  |

---

<a id="shell_report"></a>

### `shell_report`

`function` | [kernel/redirect.c:17](../../kernel/redirect.c#L17)

```c
void shell_report(const char *what, const char *detail)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `what` | `char *` |  |  |
| `detail` | `char *` |  |  |

---

<a id="shell_take_redirect"></a>

### `shell_take_redirect`

`function` | [kernel/redirect.c:25](../../kernel/redirect.c#L25)

```c
int shell_take_redirect(int *argc, char **argv, char **path, int *append_mode)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `argc` | `int *` |  |  |
| `argv` | `char **` |  |  |
| `path` | `char **` |  |  |
| `append_mode` | `int *` |  |  |

**Returns:** `int`

---
