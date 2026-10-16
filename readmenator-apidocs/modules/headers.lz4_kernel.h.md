# `headers/lz4_kernel.h`

> Source: [headers/lz4_kernel.h:1](../../headers/lz4_kernel.h#L1) | language `h` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`LZ4_compress_default`](#lz4_compress_default), [`LZ4_compressBound`](#lz4_compressbound), [`LZ4_decompress_safe`](#lz4_decompress_safe)

## Functions

<a id="lz4_compress_default"></a>

### `LZ4_compress_default`

`function` | [headers/lz4_kernel.h:4](../../headers/lz4_kernel.h#L4)

```c
int LZ4_compress_default(const char *src, char *dst, int srcSize, int dstCapacity);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `src` | `char *` |  |  |
| `dst` | `char *` |  |  |
| `srcSize` | `int` |  |  |
| `dstCapacity` | `int` |  |  |

**Returns:** `int`

*Called by:* [`minifs_compress`](fs.minifs.c.md#minifs_compress), [`swap_out`](kernel.mm.swap.c.md#swap_out)

---

<a id="lz4_compressbound"></a>

### `LZ4_compressBound`

`function` | [headers/lz4_kernel.h:5](../../headers/lz4_kernel.h#L5)

```c
int LZ4_compressBound(int inputSize);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `inputSize` | `int` |  |  |

**Returns:** `int`

---

<a id="lz4_decompress_safe"></a>

### `LZ4_decompress_safe`

`function` | [headers/lz4_kernel.h:6](../../headers/lz4_kernel.h#L6)

```c
int LZ4_decompress_safe(const char *src, char *dst, int compressedSize, int dstCapacity);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `src` | `char *` |  |  |
| `dst` | `char *` |  |  |
| `compressedSize` | `int` |  |  |
| `dstCapacity` | `int` |  |  |

**Returns:** `int`

*Called by:* [`minifs_decompress`](fs.minifs.c.md#minifs_decompress), [`swap_in`](kernel.mm.swap.c.md#swap_in)

---
