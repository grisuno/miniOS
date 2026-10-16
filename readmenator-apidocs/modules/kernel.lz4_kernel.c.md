# `kernel/lz4_kernel.c`

> Source: [kernel/lz4_kernel.c:1](../../kernel/lz4_kernel.c#L1) | language `c` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`LZ4_compressBound`](#lz4_compressbound), [`LZ4_compress_default`](#lz4_compress_default), [`slots`](#slots), [`LZ4_decompress_safe`](#lz4_decompress_safe)
- **Macros:** [`HASH_BITS`](#hash_bits), [`HASH_SIZE`](#hash_size)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_kernel_lz4_kernel_c__LZ4_compress_default(["LZ4_compress_default"])
    n_kernel_lz4_kernel_c__LZ4_compressBound(["LZ4_compressBound"])
    n_kernel_lz4_kernel_c__LZ4_compress_default --> n_kernel_lz4_kernel_c__LZ4_compressBound
```

## Functions

<a id="lz4_compressbound"></a>

### `LZ4_compressBound`

`function` | [kernel/lz4_kernel.c:33](../../kernel/lz4_kernel.c#L33)

```c
int LZ4_compressBound(int inputSize)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `inputSize` | `int` |  |  |

**Returns:** `int`

*Called by:* [`LZ4_compress_default`](#lz4_compress_default)

---

<a id="lz4_compress_default"></a>

### `LZ4_compress_default`

`function` | [kernel/lz4_kernel.c:40](../../kernel/lz4_kernel.c#L40)

```c
int LZ4_compress_default(const char *src, char *dst, int srcSize, int dstCapacity)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `src` | `char *` |  |  |
| `dst` | `char *` |  |  |
| `srcSize` | `int` |  |  |
| `dstCapacity` | `int` |  |  |

**Returns:** `int`

*Calls:* [`LZ4_compressBound`](#lz4_compressbound)

---

<a id="slots"></a>

### `slots`

`function` | [kernel/lz4_kernel.c:43](../../kernel/lz4_kernel.c#L43)

```c
* runs from file writes on 16 KB proc slots (stack discipline, * CLAUDE.md). OOM returns 0 and the caller stores uncompressed. */ int *hash_table = (int *)kmalloc(sizeof(int) * HASH_SIZE);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `discipline` | `stack` |  |  |
| `md` | `* CLAUDE.` |  |  |

**Returns:** `* runs from file writes on 16 KB`

---

<a id="lz4_decompress_safe"></a>

### `LZ4_decompress_safe`

`function` | [kernel/lz4_kernel.c:176](../../kernel/lz4_kernel.c#L176)

```c
int LZ4_decompress_safe(const char *src, char *dst, int compressedSize, int dstCapacity)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `src` | `char *` |  |  |
| `dst` | `char *` |  |  |
| `compressedSize` | `int` |  |  |
| `dstCapacity` | `int` |  |  |

**Returns:** `int`

---

## Macros

<a id="hash_bits"></a>

### `HASH_BITS`

`macro` | [kernel/lz4_kernel.c:4](../../kernel/lz4_kernel.c#L4)

```c
#define HASH_BITS
```

---

<a id="hash_size"></a>

### `HASH_SIZE`

`macro` | [kernel/lz4_kernel.c:5](../../kernel/lz4_kernel.c#L5)

```c
#define HASH_SIZE
```

---
