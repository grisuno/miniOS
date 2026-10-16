# `headers/drivers/virtio_blk.h`

> Source: [headers/drivers/virtio_blk.h:1](../../headers/drivers/virtio_blk.h#L1) | language `h` | coverage 28.6% | [API index](../index.md)

Docstring: drivers/virtio_blk.h -- virtio-blk boundary.

## Contents

- **Functions:** [`vblk_init`](#vblk_init), [`vblk_present`](#vblk_present), [`vblk_sectors`](#vblk_sectors), [`vblk_read_sectors`](#vblk_read_sectors), [`vblk_write_sectors`](#vblk_write_sectors), [`vblk_register_device`](#vblk_register_device)

## Functions

<a id="vblk_init"></a>

### `vblk_init`

`function` | [headers/drivers/virtio_blk.h:11](../../headers/drivers/virtio_blk.h#L11)

```c
int vblk_init(void);
```

**Returns:** `int`

*Called by:* [`block_init`](drivers.block.c.md#block_init), [`shell_exec_builtin`](kernel.shell.c.md#shell_exec_builtin)

---

<a id="vblk_present"></a>

### `vblk_present`

`function` | [headers/drivers/virtio_blk.h:12](../../headers/drivers/virtio_blk.h#L12)

```c
int vblk_present(void);
```

**Returns:** `int`

*Called by:* [`__attribute__`](kernel.c.md#__attribute__)

---

<a id="vblk_sectors"></a>

### `vblk_sectors`

`function` | [headers/drivers/virtio_blk.h:13](../../headers/drivers/virtio_blk.h#L13)

```c
unsigned long vblk_sectors(void);
```

**Returns:** `unsigned long`

*Called by:* [`block_init`](drivers.block.c.md#block_init), [`shell_exec_builtin`](kernel.shell.c.md#shell_exec_builtin)

---

<a id="vblk_read_sectors"></a>

### `vblk_read_sectors`

`function` | [headers/drivers/virtio_blk.h:14](../../headers/drivers/virtio_blk.h#L14)

```c
int vblk_read_sectors(unsigned lba, unsigned count, void *buf);
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

<a id="vblk_write_sectors"></a>

### `vblk_write_sectors`

`function` | [headers/drivers/virtio_blk.h:15](../../headers/drivers/virtio_blk.h#L15)

```c
int vblk_write_sectors(unsigned lba, unsigned count, const void *buf);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `lba` | `unsigned` |  |  |
| `count` | `unsigned` |  |  |
| `buf` | `void *` |  |  |

**Returns:** `int`

---

<a id="vblk_register_device"></a>

### `vblk_register_device`

`function` | [headers/drivers/virtio_blk.h:18](../../headers/drivers/virtio_blk.h#L18)

```c
void vblk_register_device(void);
```

Docstring: Publish vblk0 for the block layer preference.

*Called by:* [`block_init`](drivers.block.c.md#block_init)

---
