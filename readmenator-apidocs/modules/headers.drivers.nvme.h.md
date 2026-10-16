# `headers/drivers/nvme.h`

> Source: [headers/drivers/nvme.h:1](../../headers/drivers/nvme.h#L1) | language `h` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`nvme_init`](#nvme_init), [`nvme_present`](#nvme_present), [`nvme_version`](#nvme_version), [`nvme_note`](#nvme_note), [`nvme_sectors`](#nvme_sectors), [`nvme_read_sectors`](#nvme_read_sectors)

## Functions

<a id="nvme_init"></a>

### `nvme_init`

`function` | [headers/drivers/nvme.h:4](../../headers/drivers/nvme.h#L4)

```c
int nvme_init(void);
```

**Returns:** `int`

*Called by:* [`block_init`](drivers.block.c.md#block_init), [`shell_exec_builtin`](kernel.shell.c.md#shell_exec_builtin)

---

<a id="nvme_present"></a>

### `nvme_present`

`function` | [headers/drivers/nvme.h:5](../../headers/drivers/nvme.h#L5)

```c
int nvme_present(void);
```

**Returns:** `int`

*Called by:* [`shell_exec_builtin`](kernel.shell.c.md#shell_exec_builtin)

---

<a id="nvme_version"></a>

### `nvme_version`

`function` | [headers/drivers/nvme.h:6](../../headers/drivers/nvme.h#L6)

```c
unsigned nvme_version(void);
```

**Returns:** `unsigned`

*Called by:* [`block_init`](drivers.block.c.md#block_init), [`shell_exec_builtin`](kernel.shell.c.md#shell_exec_builtin)

---

<a id="nvme_note"></a>

### `nvme_note`

`function` `const` | [headers/drivers/nvme.h:7](../../headers/drivers/nvme.h#L7)

```c
const char *nvme_note(void);
```

**Returns:** `char *`

*Called by:* [`block_init`](drivers.block.c.md#block_init), [`shell_exec_builtin`](kernel.shell.c.md#shell_exec_builtin)

---

<a id="nvme_sectors"></a>

### `nvme_sectors`

`function` | [headers/drivers/nvme.h:8](../../headers/drivers/nvme.h#L8)

```c
unsigned long nvme_sectors(void);
```

**Returns:** `unsigned long`

*Called by:* [`block_init`](drivers.block.c.md#block_init), [`shell_exec_builtin`](kernel.shell.c.md#shell_exec_builtin)

---

<a id="nvme_read_sectors"></a>

### `nvme_read_sectors`

`function` | [headers/drivers/nvme.h:9](../../headers/drivers/nvme.h#L9)

```c
int nvme_read_sectors(unsigned lba, unsigned count, void *buf);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `lba` | `unsigned` |  |  |
| `count` | `unsigned` |  |  |
| `buf` | `void *` |  |  |

**Returns:** `int`

*Called by:* [`shell_exec_builtin`](kernel.shell.c.md#shell_exec_builtin)

---
