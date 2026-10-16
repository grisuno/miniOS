# `headers/ext4.h`

> Source: [headers/ext4.h:1](../../headers/ext4.h#L1) | language `h` | coverage 28.6% | [API index](../index.md)

ext4.h -- Read-only ext4 loopback/device driver.

## Contents

- **Structs:** [`ext4_handle_t`](#ext4_handle_t)
- **Functions:** [`ext4_list`](#ext4_list), [`ext4_vfs_open`](#ext4_vfs_open), [`ext4_vfs_read`](#ext4_vfs_read), [`ext4_vfs_write`](#ext4_vfs_write), [`ext4_vfs_close`](#ext4_vfs_close), [`ext4_vfs_fstat`](#ext4_vfs_fstat), [`ext4_vfs_truncate`](#ext4_vfs_truncate), [`first`](#first)
- **Macros:** [`EXT4_NAME_MAX`](#ext4_name_max), [`EXT4_MAX_DEPTH`](#ext4_max_depth), [`EXT4_LIST_CAP`](#ext4_list_cap), [`EXT4_PATH_MAX`](#ext4_path_max)
- **Variables:** [`ext4_vfs_ops`](#ext4_vfs_ops)

## Structs

<a id="ext4_handle_t"></a>

### `ext4_handle_t`

`struct` | [headers/ext4.h:22](../../headers/ext4.h#L22)

```c
typedef struct
```

One open ext4 file: image backend plus the located inode.

---

## Functions

<a id="ext4_list"></a>

### `ext4_list`

`function` | [headers/ext4.h:35](../../headers/ext4.h#L35)

```c
int ext4_list(const char *imgpath, const char *dirpath, char names[][EXT4_NAME_MAX + 1], int *isdir, int cap);
```

List one directory: names (dirs with trailing '/') up to cap.

Returns the entry count, or -1 when the image, path or walk fails.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `imgpath` | `char *` |  |  |
| `dirpath` | `char *` |  |  |
| `EXT4_NAME_MAX` | `char names[][ + 1]` |  |  |
| `isdir` | `int *` |  |  |
| `cap` | `int` |  |  |

**Returns:** `int`

---

<a id="ext4_vfs_open"></a>

### `ext4_vfs_open`

`function` | [headers/ext4.h:40](../../headers/ext4.h#L40)

```c
int ext4_vfs_open(const char *path, int mode, void **handle);
```

VFS verbs: open "imgpath:extpath" (first ':' splits), read, close, fstat.

Write/truncate refuse. All fail closed with -1.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `path` | `char *` |  |  |
| `mode` | `int` |  |  |
| `handle` | `void **` |  |  |

**Returns:** `int`

---

<a id="ext4_vfs_read"></a>

### `ext4_vfs_read`

`function` | [headers/ext4.h:41](../../headers/ext4.h#L41)

```c
int ext4_vfs_read(void *handle, void *buf, unsigned long pos, unsigned long len);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `handle` | `void *` |  |  |
| `buf` | `void *` |  |  |
| `pos` | `unsigned long` |  |  |
| `len` | `unsigned long` |  |  |

**Returns:** `int`

---

<a id="ext4_vfs_write"></a>

### `ext4_vfs_write`

`function` | [headers/ext4.h:43](../../headers/ext4.h#L43)

```c
int ext4_vfs_write(void *handle, const void *buf, unsigned long pos, unsigned long len);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `handle` | `void *` |  |  |
| `buf` | `void *` |  |  |
| `pos` | `unsigned long` |  |  |
| `len` | `unsigned long` |  |  |

**Returns:** `int`

---

<a id="ext4_vfs_close"></a>

### `ext4_vfs_close`

`function` | [headers/ext4.h:45](../../headers/ext4.h#L45)

```c
int ext4_vfs_close(void *handle);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `handle` | `void *` |  |  |

**Returns:** `int`

---

<a id="ext4_vfs_fstat"></a>

### `ext4_vfs_fstat`

`function` | [headers/ext4.h:46](../../headers/ext4.h#L46)

```c
int ext4_vfs_fstat(void *handle, unsigned long *size_out);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `handle` | `void *` |  |  |
| `size_out` | `unsigned long *` |  |  |

**Returns:** `int`

---

<a id="ext4_vfs_truncate"></a>

### `ext4_vfs_truncate`

`function` | [headers/ext4.h:47](../../headers/ext4.h#L47)

```c
int ext4_vfs_truncate(void *handle, unsigned long size);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `handle` | `void *` |  |  |
| `size` | `unsigned long` |  |  |

**Returns:** `int`

---

<a id="first"></a>

### `first`

`function` | [headers/ext4.h:50](../../headers/ext4.h#L50)

```c
* MBR 0x83 entry first (proven by a superblock read), then a magic * scan over 2048-aligned LBAs for superfloppy layouts. Returns the * base LBA, or -1 when no ext4 is present. Cached. */ long ext_dev
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `read` | `proven by a superblock` |  |  |

**Returns:** `* MBR 0x83 entry`

---

## Macros

<a id="ext4_name_max"></a>

### `EXT4_NAME_MAX`

`macro` | [headers/ext4.h:16](../../headers/ext4.h#L16)

```c
#define EXT4_NAME_MAX
```

---

<a id="ext4_max_depth"></a>

### `EXT4_MAX_DEPTH`

`macro` | [headers/ext4.h:17](../../headers/ext4.h#L17)

```c
#define EXT4_MAX_DEPTH
```

---

<a id="ext4_list_cap"></a>

### `EXT4_LIST_CAP`

`macro` | [headers/ext4.h:18](../../headers/ext4.h#L18)

```c
#define EXT4_LIST_CAP
```

---

<a id="ext4_path_max"></a>

### `EXT4_PATH_MAX`

`macro` | [headers/ext4.h:19](../../headers/ext4.h#L19)

```c
#define EXT4_PATH_MAX
```

---

## Variables

<a id="ext4_vfs_ops"></a>

### `ext4_vfs_ops`

`variable` `const` `extern` | [headers/ext4.h:55](../../headers/ext4.h#L55)

```c
extern const vfs_ops_t ext4_vfs_ops;
```

---
