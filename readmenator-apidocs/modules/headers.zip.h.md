# `headers/zip.h`

> Source: [headers/zip.h:1](../../headers/zip.h#L1) | language `h` | coverage 33.3% | [API index](../index.md)

zip.h — MiniOS integration API for the miniz zip library.

## Contents

- **Functions:** [`miniz`](#miniz), [`shell_cmd_zip`](#shell_cmd_zip)

## Functions

<a id="miniz"></a>

### `miniz`

`function` | [headers/zip.h:6](../../headers/zip.h#L6)

```c
* * The shell builtins over miniz (see zip.c) are declared here so kernel.c's * shell dispatcher can route the unzip/zip commands. Both builtins work * whole-file in memory over the unified file API (
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `c` | `see zip.` |  |  |

**Returns:** `* * The shell builtins over`

---

<a id="shell_cmd_zip"></a>

### `shell_cmd_zip`

`function` | [headers/zip.h:15](../../headers/zip.h#L15)

```c
void shell_cmd_zip(int argc, char **argv);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `argc` | `int` |  |  |
| `argv` | `char **` |  |  |

---
