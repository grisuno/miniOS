# `kernel/abi.c`

> Source: [kernel/abi.c:1](../../kernel/abi.c#L1) | language `c` | coverage 100.0% | [API index](../index.md)

Docstring: kernel/abi.c -- Boot-time ABI manifest gate.

## Contents

- **Functions:** [`abi_verify`](#abi_verify), [`abi_check_manifest`](#abi_check_manifest)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_kernel_abi_c__abi_check_manifest(["abi_check_manifest"])
    n_kernel_abi_c__abi_verify(["abi_verify"])
    n_kernel_abi_c__abi_check_manifest --> n_kernel_abi_c__abi_verify
```

## Functions

<a id="abi_verify"></a>

### `abi_verify`

`function` | [kernel/abi.c:38](../../kernel/abi.c#L38)

```c
int abi_verify(const char *text, long version, unsigned long checksum)
```

Docstring: Verify manifest text against the running ABI.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `text` | `char *` |  |  |
| `version` | `long` |  |  |
| `checksum` | `unsigned long` |  |  |

**Returns:** `int`

*Called by:* [`abi_check_manifest`](#abi_check_manifest)

---

<a id="abi_check_manifest"></a>

### `abi_check_manifest`

`function` | [kernel/abi.c:74](../../kernel/abi.c#L74)

```c
int abi_check_manifest(void)
```

Docstring: Read etc/abi from the ramdisk and verify the running ABI.

**Returns:** `int`

*Calls:* [`abi_verify`](#abi_verify)

---
