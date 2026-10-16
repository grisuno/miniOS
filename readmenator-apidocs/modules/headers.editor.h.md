# `headers/editor.h`

> Source: [headers/editor.h:1](../../headers/editor.h#L1) | language `h` | coverage 50.0% | [API index](../index.md)

editor.h -- the built-in line editor contract.

## Contents

- **Functions:** [`shell_cmd_edit`](#shell_cmd_edit)

## Functions

<a id="shell_cmd_edit"></a>

### `shell_cmd_edit`

`function` | [headers/editor.h:15](../../headers/editor.h#L15)

```c
void shell_cmd_edit(int argc, char **argv);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `argc` | `int` |  |  |
| `argv` | `char **` |  |  |

*Called by:* [`shell_exec_builtin`](kernel.shell.c.md#shell_exec_builtin)

---
