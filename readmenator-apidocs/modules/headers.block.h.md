# `headers/block.h`

> Source: [headers/block.h:1](../../headers/block.h#L1) | language `h` | coverage 64.3% | [API index](../index.md)

Block device abstraction for MiniFS.

Maps 4096-byte logical blocks to 512-byte IDE sectors.

## Contents

- **Functions:** [`block_init`](#block_init), [`block_set_base`](#block_set_base), [`block_read`](#block_read), [`block_write`](#block_write), [`block_read_multi`](#block_read_multi), [`block_write_multi`](#block_write_multi), [`block_flush`](#block_flush), [`block_total`](#block_total), [`block_read_sectors`](#block_read_sectors), [`block_disk_sectors`](#block_disk_sectors)
- **Macros:** [`BLOCK_SIZE`](#block_size), [`BLOCK_SHIFT`](#block_shift), [`SECTORS_PER_BLOCK`](#sectors_per_block)

## Functions

<a id="block_init"></a>

### `block_init`

`function` | [headers/block.h:12](../../headers/block.h#L12)

```c
void block_init(void);
```

Initialize the block layer.

Calls ide_init() internally.

*Called by:* [`__attribute__`](kernel.c.md#__attribute__)

---

<a id="block_set_base"></a>

### `block_set_base`

`function` | [headers/block.h:15](../../headers/block.h#L15)

```c
void block_set_base(unsigned int lba_base);
```

Set the base LBA offset for all block I/O.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `lba_base` | `unsigned int` |  |  |

*Called by:* [`minifs_mount`](fs.minifs.c.md#minifs_mount)

---

<a id="block_read"></a>

### `block_read`

`function` | [headers/block.h:18](../../headers/block.h#L18)

```c
int block_read(unsigned int block_num, void *buf);
```

Read/write one 4096-byte block.

Returns 0 on success.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `block_num` | `unsigned int` |  |  |
| `buf` | `void *` |  |  |

**Returns:** `int`

*Called by:* [`first`](fs.minifs.c.md#first), [`minifs_dir_add_entry`](fs.minifs.c.md#minifs_dir_add_entry), [`minifs_dir_lookup`](fs.minifs.c.md#minifs_dir_lookup), [`minifs_dir_read`](fs.minifs.c.md#minifs_dir_read), [`minifs_dir_remove_entry`](fs.minifs.c.md#minifs_dir_remove_entry), [`minifs_inode_get_block`](fs.minifs.c.md#minifs_inode_get_block), [`minifs_journal_abort`](fs.minifs.c.md#minifs_journal_abort), [`minifs_journal_recover`](fs.minifs.c.md#minifs_journal_recover), [`minifs_mount`](fs.minifs.c.md#minifs_mount), [`minifs_read`](fs.minifs.c.md#minifs_read), [`minifs_write`](fs.minifs.c.md#minifs_write)

---

<a id="block_write"></a>

### `block_write`

`function` | [headers/block.h:19](../../headers/block.h#L19)

```c
int block_write(unsigned int block_num, const void *buf);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `block_num` | `unsigned int` |  |  |
| `buf` | `void *` |  |  |

**Returns:** `int`

*Called by:* [`first`](fs.minifs.c.md#first), [`minifs_dir_add_entry`](fs.minifs.c.md#minifs_dir_add_entry), [`minifs_dir_remove_entry`](fs.minifs.c.md#minifs_dir_remove_entry), [`minifs_inode_alloc_block`](fs.minifs.c.md#minifs_inode_alloc_block), [`minifs_journal_abort`](fs.minifs.c.md#minifs_journal_abort), [`minifs_journal_recover`](fs.minifs.c.md#minifs_journal_recover), [`minifs_sync`](fs.minifs.c.md#minifs_sync), [`minifs_write`](fs.minifs.c.md#minifs_write)

---

<a id="block_read_multi"></a>

### `block_read_multi`

`function` | [headers/block.h:23](../../headers/block.h#L23)

```c
int block_read_multi(unsigned int block_num, unsigned int count, void *buf);
```

Read/write multiple contiguous blocks.

Returns 0 on success.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `block_num` | `unsigned int` |  |  |
| `count` | `unsigned int` |  |  |
| `buf` | `void *` |  |  |

**Returns:** `int`

---

<a id="block_write_multi"></a>

### `block_write_multi`

`function` | [headers/block.h:24](../../headers/block.h#L24)

```c
int block_write_multi(unsigned int block_num, unsigned int count, const void *buf);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `block_num` | `unsigned int` |  |  |
| `count` | `unsigned int` |  |  |
| `buf` | `void *` |  |  |

**Returns:** `int`

---

<a id="block_flush"></a>

### `block_flush`

`function` | [headers/block.h:27](../../headers/block.h#L27)

```c
void block_flush(void);
```

Flush any cached writes (currently a no-op, IDE is synchronous).

---

<a id="block_total"></a>

### `block_total`

`function` | [headers/block.h:30](../../headers/block.h#L30)

```c
unsigned int block_total(void);
```

Total blocks available, 0 if no disk.

**Returns:** `unsigned int`

---

<a id="block_read_sectors"></a>

### `block_read_sectors`

`function` | [headers/block.h:37](../../headers/block.h#L37)

```c
int block_read_sectors(unsigned lba, unsigned count, void *buf);
```

Docstring: Backend-aware sector I/O on absolute LBAs, bypassing the block cache and the MiniFS base offset.

This is what partition scanners and foreign filesystems use, so a FAT on a USB stick reads from USB and not from IDE. buf must be DMA-safe (heap): the USB backend hands it to the controller as a physical address. Returns 0 on success.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `lba` | `unsigned` |  |  |
| `count` | `unsigned` |  |  |
| `buf` | `void *` |  |  |

**Returns:** `int`

*Called by:* [`ext_dev_base`](fs.ext4.c.md#ext_dev_base), [`fat_dev_base`](fs.fat32.c.md#fat_dev_base)

---

<a id="block_disk_sectors"></a>

### `block_disk_sectors`

`function` | [headers/block.h:40](../../headers/block.h#L40)

```c
unsigned long block_disk_sectors(void);
```

Docstring: Backend-aware disk size in 512-byte sectors, 0 if no disk.

**Returns:** `unsigned long`

*Called by:* [`ext4_list`](fs.ext4.c.md#ext4_list), [`ext4_vfs_open`](fs.ext4.c.md#ext4_vfs_open), [`ext_dev_base`](fs.ext4.c.md#ext_dev_base), [`fat_dev_base`](fs.fat32.c.md#fat_dev_base), [`fsimg_open_dev`](fs.fsimg.c.md#fsimg_open_dev), [`minifs_mount`](fs.minifs.c.md#minifs_mount)

---

## Macros

<a id="block_size"></a>

### `BLOCK_SIZE`

`macro` | [headers/block.h:7](../../headers/block.h#L7)

```c
#define BLOCK_SIZE
```

---

<a id="block_shift"></a>

### `BLOCK_SHIFT`

`macro` | [headers/block.h:8](../../headers/block.h#L8)

```c
#define BLOCK_SHIFT
```

---

<a id="sectors_per_block"></a>

### `SECTORS_PER_BLOCK`

`macro` | [headers/block.h:9](../../headers/block.h#L9)

```c
#define SECTORS_PER_BLOCK
```

---
