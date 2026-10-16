# `headers/abi.h`

> Source: [headers/abi.h:1](../../headers/abi.h#L1) | language `h` | coverage 20.0% | [API index](../index.md)

Docstring: abi.h -- Boot-time ABI manifest gate contract.

## Contents

- **Functions:** [`abi_verify`](#abi_verify), [`abi_check_manifest`](#abi_check_manifest)
- **Macros:** [`ABI_OK`](#abi_ok), [`ABI_NO_MANIFEST`](#abi_no_manifest), [`ABI_BAD_FORMAT`](#abi_bad_format), [`ABI_VERSION_MISMATCH`](#abi_version_mismatch), [`ABI_CHECKSUM_MISMATCH`](#abi_checksum_mismatch), [`ABI_MANIFEST_NAME`](#abi_manifest_name), [`ABI_MANIFEST_MAX`](#abi_manifest_max)

## Functions

<a id="abi_verify"></a>

### `abi_verify`

`function` | [headers/abi.h:25](../../headers/abi.h#L25)

```c
int abi_verify(const char *text, long version, unsigned long checksum);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `text` | `char *` |  |  |
| `version` | `long` |  |  |
| `checksum` | `unsigned long` |  |  |

**Returns:** `int`

---

<a id="abi_check_manifest"></a>

### `abi_check_manifest`

`function` | [headers/abi.h:28](../../headers/abi.h#L28)

```c
int abi_check_manifest(void);
```

ifndef ABI_HOST_TEST

**Returns:** `int`

*Called by:* [`__attribute__`](kernel.c.md#__attribute__)

---

## Macros

<a id="abi_ok"></a>

### `ABI_OK`

`macro` | [headers/abi.h:16](../../headers/abi.h#L16)

```c
#define ABI_OK
```

---

<a id="abi_no_manifest"></a>

### `ABI_NO_MANIFEST`

`macro` | [headers/abi.h:17](../../headers/abi.h#L17)

```c
#define ABI_NO_MANIFEST
```

---

<a id="abi_bad_format"></a>

### `ABI_BAD_FORMAT`

`macro` | [headers/abi.h:18](../../headers/abi.h#L18)

```c
#define ABI_BAD_FORMAT
```

---

<a id="abi_version_mismatch"></a>

### `ABI_VERSION_MISMATCH`

`macro` | [headers/abi.h:19](../../headers/abi.h#L19)

```c
#define ABI_VERSION_MISMATCH
```

---

<a id="abi_checksum_mismatch"></a>

### `ABI_CHECKSUM_MISMATCH`

`macro` | [headers/abi.h:20](../../headers/abi.h#L20)

```c
#define ABI_CHECKSUM_MISMATCH
```

---

<a id="abi_manifest_name"></a>

### `ABI_MANIFEST_NAME`

`macro` | [headers/abi.h:22](../../headers/abi.h#L22)

```c
#define ABI_MANIFEST_NAME
```

---

<a id="abi_manifest_max"></a>

### `ABI_MANIFEST_MAX`

`macro` | [headers/abi.h:23](../../headers/abi.h#L23)

```c
#define ABI_MANIFEST_MAX
```

---
