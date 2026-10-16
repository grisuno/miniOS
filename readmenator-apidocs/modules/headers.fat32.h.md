# `headers/fat32.h`

> Source: [headers/fat32.h:1](../../headers/fat32.h#L1) | language `h` | coverage 33.3% | [API index](../index.md)

fat32.h -- Read-only FAT32 loopback driver over ramdisk/MiniFS images.

## Contents

- **Structs:** [`fat32_handle_t`](#fat32_handle_t)
- **Functions:** [`file`](#file), [`fat32_list`](#fat32_list), [`fat_dev_base`](#fat_dev_base), [`fat32_vfs_open`](#fat32_vfs_open), [`fat32_vfs_read`](#fat32_vfs_read), [`fat32_vfs_write`](#fat32_vfs_write), [`fat32_vfs_close`](#fat32_vfs_close), [`fat32_vfs_fstat`](#fat32_vfs_fstat), [`fat32_vfs_truncate`](#fat32_vfs_truncate)
- **Macros:** [`FAT32_NAME_MAX`](#fat32_name_max), [`FAT32_MAX_DEPTH`](#fat32_max_depth), [`FAT32_LIST_CAP`](#fat32_list_cap), [`FAT32_CLUS_MAX`](#fat32_clus_max)
- **Variables:** [`fat32_vfs_ops`](#fat32_vfs_ops)

## Structs

<a id="fat32_handle_t"></a>

### `fat32_handle_t`

`struct` | [headers/fat32.h:25](../../headers/fat32.h#L25)

```c
typedef struct
```

One open FAT file: image backend plus the located entry.

A loopback image reads through ramdisk/minifs at file offsets; a real disk partition (`hd0`, first FAT32 found) reads absolute LBA sectors through the IDE driver at dev_lba + offset.

---

## Functions

<a id="file"></a>

### `file`

`function` | [headers/fat32.h:6](../../headers/fat32.h#L6)

```c
* * A FAT32 disk image stored as a regular file (built on the host with * mkfs.vfat, packed into minifs.bin) is parsed here: BPB validation, * cluster-chain walking and 8.3 directory traversal. Only t
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `vfat` | `built on the host with * mkfs.` |  |  |
| `bin` | `packed into minifs.` |  |  |

**Returns:** `* * A FAT32 disk image stored as a regular`

---

<a id="fat32_list"></a>

### `fat32_list`

`function` | [headers/fat32.h:45](../../headers/fat32.h#L45)

```c
int fat32_list(const char *imgpath, const char *dirpath, char names[][FAT32_NAME_MAX], int *isdir, int cap);
```

List one directory: names (dirs with trailing '/') up to cap.

Returns the entry count, or -1 when the image, path or walk fails.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `imgpath` | `char *` |  |  |
| `dirpath` | `char *` |  |  |
| `FAT32_NAME_MAX` | `char names[][ ]` |  |  |
| `isdir` | `int *` |  |  |
| `cap` | `int` |  |  |

**Returns:** `int`

---

<a id="fat_dev_base"></a>

### `fat_dev_base`

`function` | [headers/fat32.h:54](../../headers/fat32.h#L54)

```c
long fat_dev_base(void);
```

Locate the first FAT32 partition on the primary IDE master: a real MBR FAT32 entry first (real hardware with a partition table), then a magic scan over 2048-aligned LBAs (superfloppy images with no table, like the os.img tail).

Returns the base LBA, or -1 when no FAT32 is present. Result is cached; the disk never changes under a running guest.

**Returns:** `long`

---

<a id="fat32_vfs_open"></a>

### `fat32_vfs_open`

`function` | [headers/fat32.h:58](../../headers/fat32.h#L58)

```c
int fat32_vfs_open(const char *path, int mode, void **handle);
```

VFS verbs: open "imgpath:fatpath" (first ':' splits), read, close, fstat.

Write/truncate refuse. All fail closed with -1.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `path` | `char *` |  |  |
| `mode` | `int` |  |  |
| `handle` | `void **` |  |  |

**Returns:** `int`

---

<a id="fat32_vfs_read"></a>

### `fat32_vfs_read`

`function` | [headers/fat32.h:59](../../headers/fat32.h#L59)

```c
int fat32_vfs_read(void *handle, void *buf, unsigned long pos, unsigned long len);
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

<a id="fat32_vfs_write"></a>

### `fat32_vfs_write`

`function` | [headers/fat32.h:61](../../headers/fat32.h#L61)

```c
int fat32_vfs_write(void *handle, const void *buf, unsigned long pos, unsigned long len);
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

<a id="fat32_vfs_close"></a>

### `fat32_vfs_close`

`function` | [headers/fat32.h:63](../../headers/fat32.h#L63)

```c
int fat32_vfs_close(void *handle);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `handle` | `void *` |  |  |

**Returns:** `int`

---

<a id="fat32_vfs_fstat"></a>

### `fat32_vfs_fstat`

`function` | [headers/fat32.h:64](../../headers/fat32.h#L64)

```c
int fat32_vfs_fstat(void *handle, unsigned long *size_out);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `handle` | `void *` |  |  |
| `size_out` | `unsigned long *` |  |  |

**Returns:** `int`

---

<a id="fat32_vfs_truncate"></a>

### `fat32_vfs_truncate`

`function` | [headers/fat32.h:65](../../headers/fat32.h#L65)

```c
int fat32_vfs_truncate(void *handle, unsigned long size);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `handle` | `void *` |  |  |
| `size` | `unsigned long` |  |  |

**Returns:** `int`

---

## Macros

<a id="fat32_name_max"></a>

### `FAT32_NAME_MAX`

`macro` | [headers/fat32.h:16](../../headers/fat32.h#L16)

```c
#define FAT32_NAME_MAX
```

---

<a id="fat32_max_depth"></a>

### `FAT32_MAX_DEPTH`

`macro` | [headers/fat32.h:17](../../headers/fat32.h#L17)

```c
#define FAT32_MAX_DEPTH
```

---

<a id="fat32_list_cap"></a>

### `FAT32_LIST_CAP`

`macro` | [headers/fat32.h:18](../../headers/fat32.h#L18)

```c
#define FAT32_LIST_CAP
```

---

<a id="fat32_clus_max"></a>

### `FAT32_CLUS_MAX`

`macro` | [headers/fat32.h:19](../../headers/fat32.h#L19)

```c
#define FAT32_CLUS_MAX
```

---

## Variables

<a id="fat32_vfs_ops"></a>

### `fat32_vfs_ops`

`variable` `const` `extern` | [headers/fat32.h:67](../../headers/fat32.h#L67)

```c
extern const vfs_ops_t fat32_vfs_ops;
```

---
