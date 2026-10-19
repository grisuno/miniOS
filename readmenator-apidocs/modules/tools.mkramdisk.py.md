# `tools.mkramdisk`

> Source: [tools/mkramdisk.py:1](../../tools/mkramdisk.py#L1) | language `py` | coverage 50.0% | [API index](../index.md)

Build a MiniOS ramdisk image from files in a directory tree.

Each packed file is named by its path relative to the shared parent of
all inputs, so progs/src/cp.c ships as src/cp.c and directories are carried
as slashes inside flat names. Names longer than NAME_MAX or two inputs
mapping to the same name are hard errors: a silently truncated or
overwritten name would make every later lookup miss.

Payloads are deflate compressed (a zlib stream, exactly what the kernel
miniz mz_uncompress consumes). The kernel decompresses every entry once
at boot into its working ramdisk area, so runtime reads and writes see
plain bytes and lose no performance; only the on-disk/embedded image
shrinks. A payload that does not compress (tiny or incompressible) is
stored raw and flagged so.

Layout (little endian):
    u32 magic, u32 count
    count * { char name[RAMDISK_FNAME_LEN]; u32 raw_size; u32 stored_size;
              u32 data_offset; u32 flags }
    payload area (concatenated, offsets relative to its start)
flags bit 0: stored_size bytes are a zlib stream, else raw.

The name slot width is RAMDISK_FNAME_LEN parsed from headers/kernel.h
(the single source of truth): the kernel's RDFile table reads the same
width, and a mismatch silently misaligns every entry; changing the
constant there and rebuilding is the only way to move it.

## Contents

- **Functions:** [`read_fname_bytes`](#read_fname_bytes), [`pack_name`](#pack_name), [`main`](#main)
- **Constants:** [`MAGIC`](#magic), [`MAX_FILES`](#max_files), [`FLAG_DEFLATE`](#flag_deflate), [`DEFLATE_LEVEL`](#deflate_level), [`FNAME_BYTES`](#fname_bytes), [`NAME_MAX`](#name_max), [`ENTRY_BYTES`](#entry_bytes)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_tools_mkramdisk_py__main(["main"])
    n_tools_mkramdisk_py__pack_name(["pack_name"])
    n_tools_mkramdisk_py__main --> n_tools_mkramdisk_py__pack_name
```

## Functions

<a id="read_fname_bytes"></a>

### `read_fname_bytes`

`function` | [tools/mkramdisk.py:41](../../tools/mkramdisk.py#L41)

```python
def read_fname_bytes(kernel_h_path)
```

Parse RAMDISK_FNAME_LEN from headers/kernel.h; fail closed.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `kernel_h_path` |  |  |  |

**Raises**

- `SystemExit`: (raised in the body, not documented)

---

<a id="pack_name"></a>

### `pack_name`

`function` | [tools/mkramdisk.py:64](../../tools/mkramdisk.py#L64)

```python
def pack_name(path, common)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `path` |  |  |  |
| `common` |  |  |  |

**Raises**

- `SystemExit`: (raised in the body, not documented)

*Called by:* [`main`](#main)

---

<a id="main"></a>

### `main`

`function` | [tools/mkramdisk.py:74](../../tools/mkramdisk.py#L74)

```python
def main()
```

**Raises**

- `SystemExit`: (raised in the body, not documented)

*Calls:* [`pack_name`](#pack_name)

---

## Constants

<a id="magic"></a>

### `MAGIC`

`constant` | [tools/mkramdisk.py:35](../../tools/mkramdisk.py#L35)

```python
MAGIC = 1263748178
```

---

<a id="max_files"></a>

### `MAX_FILES`

`constant` | [tools/mkramdisk.py:36](../../tools/mkramdisk.py#L36)

```python
MAX_FILES = 128
```

---

<a id="flag_deflate"></a>

### `FLAG_DEFLATE`

`constant` | [tools/mkramdisk.py:37](../../tools/mkramdisk.py#L37)

```python
FLAG_DEFLATE = 1
```

---

<a id="deflate_level"></a>

### `DEFLATE_LEVEL`

`constant` | [tools/mkramdisk.py:38](../../tools/mkramdisk.py#L38)

```python
DEFLATE_LEVEL = 6
```

---

<a id="fname_bytes"></a>

### `FNAME_BYTES`

`constant` | [tools/mkramdisk.py:57](../../tools/mkramdisk.py#L57)

```python
FNAME_BYTES
```

---

<a id="name_max"></a>

### `NAME_MAX`

`constant` | [tools/mkramdisk.py:60](../../tools/mkramdisk.py#L60)

```python
NAME_MAX = FNAME_BYTES - 1
```

---

<a id="entry_bytes"></a>

### `ENTRY_BYTES`

`constant` | [tools/mkramdisk.py:61](../../tools/mkramdisk.py#L61)

```python
ENTRY_BYTES = FNAME_BYTES + 16
```

---
