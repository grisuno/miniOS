# `tools.mkramdisk`

> Source: [tools/mkramdisk.py:1](../../tools/mkramdisk.py#L1) | language `py` | coverage 33.3% | [API index](../index.md)

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
    count * { char name[64]; u32 raw_size; u32 stored_size;
              u32 data_offset; u32 flags }
    payload area (concatenated, offsets relative to its start)
flags bit 0: stored_size bytes are a zlib stream, else raw.

## Contents

- **Functions:** [`pack_name`](#pack_name), [`main`](#main)
- **Constants:** [`MAGIC`](#magic), [`FNAME_BYTES`](#fname_bytes), [`NAME_MAX`](#name_max), [`MAX_FILES`](#max_files), [`ENTRY_BYTES`](#entry_bytes), [`FLAG_DEFLATE`](#flag_deflate), [`DEFLATE_LEVEL`](#deflate_level)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_tools_mkramdisk_py__main(["main"])
    n_tools_mkramdisk_py__pack_name(["pack_name"])
    n_tools_mkramdisk_py__main --> n_tools_mkramdisk_py__pack_name
```

## Functions

<a id="pack_name"></a>

### `pack_name`

`function` | [tools/mkramdisk.py:38](../../tools/mkramdisk.py#L38)

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

`function` | [tools/mkramdisk.py:48](../../tools/mkramdisk.py#L48)

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

`constant` | [tools/mkramdisk.py:29](../../tools/mkramdisk.py#L29)

```python
MAGIC = 1263748178
```

---

<a id="fname_bytes"></a>

### `FNAME_BYTES`

`constant` | [tools/mkramdisk.py:30](../../tools/mkramdisk.py#L30)

```python
FNAME_BYTES = 64
```

---

<a id="name_max"></a>

### `NAME_MAX`

`constant` | [tools/mkramdisk.py:31](../../tools/mkramdisk.py#L31)

```python
NAME_MAX = FNAME_BYTES - 1
```

---

<a id="max_files"></a>

### `MAX_FILES`

`constant` | [tools/mkramdisk.py:32](../../tools/mkramdisk.py#L32)

```python
MAX_FILES = 128
```

---

<a id="entry_bytes"></a>

### `ENTRY_BYTES`

`constant` | [tools/mkramdisk.py:33](../../tools/mkramdisk.py#L33)

```python
ENTRY_BYTES = FNAME_BYTES + 16
```

---

<a id="flag_deflate"></a>

### `FLAG_DEFLATE`

`constant` | [tools/mkramdisk.py:34](../../tools/mkramdisk.py#L34)

```python
FLAG_DEFLATE = 1
```

---

<a id="deflate_level"></a>

### `DEFLATE_LEVEL`

`constant` | [tools/mkramdisk.py:35](../../tools/mkramdisk.py#L35)

```python
DEFLATE_LEVEL = 6
```

---
