# `headers/fsimg.h`

> Source: [headers/fsimg.h:1](../../headers/fsimg.h#L1) | language `h` | coverage 83.3% | [API index](../index.md)

fsimg.h -- One image backend for read-only filesystem drivers.

## Contents

- **Structs:** [`fsimg_t`](#fsimg_t)
- **Functions:** [`fsimg_open_file`](#fsimg_open_file), [`fsimg_open_dev`](#fsimg_open_dev), [`fsimg_read`](#fsimg_read), [`fsimg_split`](#fsimg_split)

## Structs

<a id="fsimg_t"></a>

### `fsimg_t`

`struct` | [headers/fsimg.h:13](../../headers/fsimg.h#L13)

```c
typedef struct
```

---

## Functions

<a id="fsimg_open_file"></a>

### `fsimg_open_file`

`function` | [headers/fsimg.h:23](../../headers/fsimg.h#L23)

```c
int fsimg_open_file(const char *resolved, fsimg_t *img);
```

Open a resolved path as a loopback image.

Refuses past 4 GB (all sector math below is 32-bit).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `resolved` | `char *` |  |  |
| `img` | `fsimg_t *` |  |  |

**Returns:** `int`

*Called by:* [`ext4_list`](fs.ext4.c.md#ext4_list), [`ext4_vfs_open`](fs.ext4.c.md#ext4_vfs_open)

---

<a id="fsimg_open_dev"></a>

### `fsimg_open_dev`

`function` | [headers/fsimg.h:27](../../headers/fsimg.h#L27)

```c
int fsimg_open_dev(unsigned long base_lba, unsigned long nsec, fsimg_t *img);
```

Open an absolute disk region [base_lba, base_lba + nsec) as an image.

Bounds are 64-bit and fenced to the drive size.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `base_lba` | `unsigned long` |  |  |
| `nsec` | `unsigned long` |  |  |
| `img` | `fsimg_t *` |  |  |

**Returns:** `int`

*Called by:* [`ext4_list`](fs.ext4.c.md#ext4_list), [`ext4_vfs_open`](fs.ext4.c.md#ext4_vfs_open)

---

<a id="fsimg_read"></a>

### `fsimg_read`

`function` | [headers/fsimg.h:32](../../headers/fsimg.h#L32)

```c
int fsimg_read(const fsimg_t *img, unsigned long off, void *buf, unsigned long len);
```

Read len bytes at off into buf.

Fails closed on any bound violation, short backend transfer, or missing device.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `img` | `fsimg_t *` |  |  |
| `off` | `unsigned long` |  |  |
| `buf` | `void *` |  |  |
| `len` | `unsigned long` |  |  |

**Returns:** `int`

*Called by:* [`fat32_list`](fs.fat32.c.md#fat32_list), [`fat32_vfs_read`](fs.fat32.c.md#fat32_vfs_read)

---

<a id="fsimg_split"></a>

### `fsimg_split`

`function` | [headers/fsimg.h:40](../../headers/fsimg.h#L40)

```c
int fsimg_split(const char *path, char *left, unsigned llen, char *right, unsigned rlen);
```

Split "left:right" at the first ':' (image names never carry one).

Bounds are per side: image paths resolve under RAMDISK_FNAME_LEN, in-image paths may run deeper. Refuses empty sides and overlong parts. Shared by the fat: and ext4: VFS addressings, which have the same shape.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `path` | `char *` |  |  |
| `left` | `char *` |  |  |
| `llen` | `unsigned` |  |  |
| `right` | `char *` |  |  |
| `rlen` | `unsigned` |  |  |

**Returns:** `int`

*Called by:* [`fat32_vfs_open`](fs.fat32.c.md#fat32_vfs_open)

---
