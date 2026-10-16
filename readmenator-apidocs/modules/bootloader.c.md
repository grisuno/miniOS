# `bootloader.c`

> Source: [bootloader.c:1](../../bootloader.c#L1) | language `c` | coverage 33.3% | [API index](../index.md)

## Contents

- **Functions:** [`main`](#main)
- **Macros:** [`KSECTORS`](#ksectors)

## Functions

<a id="main"></a>

### `main`

`function` | [bootloader.c:21](../../bootloader.c#L21)

```c
void main(void)
```

---

## Macros

<a id="ksectors"></a>

### `KSECTORS`

`macro` | [bootloader.c:19](../../bootloader.c#L19)

```c
#define KSECTORS
```

Number of 512-byte sectors of kernel to load from LBA 1 to phys 0x10000.

---
