# `headers/drivers/usbblk.h`

> Source: [headers/drivers/usbblk.h:1](../../headers/drivers/usbblk.h#L1) | language `h` | coverage 76.9% | [API index](../index.md)

Docstring: drivers/usbblk.h -- boundary of the USB mass-storage driver.

## Contents

- **Structs:** [`ubk_counters_t`](#ubk_counters_t)
- **Functions:** [`ubk_init`](#ubk_init), [`ubk_present`](#ubk_present), [`ubk_sectors`](#ubk_sectors), [`ubk_read_sectors`](#ubk_read_sectors), [`ubk_write_sectors`](#ubk_write_sectors), [`ubk_counters`](#ubk_counters), [`ubk_build_cbw`](#ubk_build_cbw), [`ubk_check_csw`](#ubk_check_csw)
- **Macros:** [`UBK_BLOCK_SIZE`](#ubk_block_size), [`UBK_MAX_BLOCKS`](#ubk_max_blocks), [`UBK_MAX_SECTORS`](#ubk_max_sectors)

## Structs

<a id="ubk_counters_t"></a>

### `ubk_counters_t`

`struct` | [headers/drivers/usbblk.h:37](../../headers/drivers/usbblk.h#L37)

```c
typedef struct
```

Docstring: Counters, so a disk that is absent is distinguishable from a driver that is broken.

---

## Functions

<a id="ubk_init"></a>

### `ubk_init`

`function` | [headers/drivers/usbblk.h:21](../../headers/drivers/usbblk.h#L21)

```c
int ubk_init(void);
```

Docstring: Bring up mass storage on every enumerated device.

Returns the number of disks registered, which is 0 on a machine with none and is not an error.

**Returns:** `int`

*Called by:* [`block_init`](drivers.block.c.md#block_init)

---

<a id="ubk_present"></a>

### `ubk_present`

`function` | [headers/drivers/usbblk.h:24](../../headers/drivers/usbblk.h#L24)

```c
int ubk_present(void);
```

Docstring: True when a USB disk was registered and is the active backend.

**Returns:** `int`

*Called by:* [`__attribute__`](kernel.c.md#__attribute__)

---

<a id="ubk_sectors"></a>

### `ubk_sectors`

`function` | [headers/drivers/usbblk.h:27](../../headers/drivers/usbblk.h#L27)

```c
unsigned long ubk_sectors(void);
```

Docstring: Sector count of the registered disk.

**Returns:** `unsigned long`

*Called by:* [`block_init`](drivers.block.c.md#block_init)

---

<a id="ubk_read_sectors"></a>

### `ubk_read_sectors`

`function` | [headers/drivers/usbblk.h:32](../../headers/drivers/usbblk.h#L32)

```c
int ubk_read_sectors(unsigned long lba, unsigned count, void *buf);
```

Docstring: Read or write whole 512-byte sectors.

Returns 1 on success, 0 on a refused request: a range outside the disk, a short transfer, a command failure or a stale CSW. Never reports a partial block as read.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `lba` | `unsigned long` |  |  |
| `count` | `unsigned` |  |  |
| `buf` | `void *` |  |  |

**Returns:** `int`

---

<a id="ubk_write_sectors"></a>

### `ubk_write_sectors`

`function` | [headers/drivers/usbblk.h:33](../../headers/drivers/usbblk.h#L33)

```c
int ubk_write_sectors(unsigned long lba, unsigned count, const void *buf);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `lba` | `unsigned long` |  |  |
| `count` | `unsigned` |  |  |
| `buf` | `void *` |  |  |

**Returns:** `int`

---

<a id="ubk_counters"></a>

### `ubk_counters`

`function` | [headers/drivers/usbblk.h:46](../../headers/drivers/usbblk.h#L46)

```c
void ubk_counters(ubk_counters_t *out);
```

Docstring: Snapshot the counters.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `out` | `ubk_counters_t *` |  |  |

---

<a id="ubk_build_cbw"></a>

### `ubk_build_cbw`

`function` | [headers/drivers/usbblk.h:52](../../headers/drivers/usbblk.h#L52)

```c
void ubk_build_cbw(unsigned char *out, unsigned tag, unsigned long lba, unsigned blocks, int read, int data_len);
```

Docstring: Build a Command Block Wrapper into out, which must have room for UBK_CBW_LEN bytes.

Pure, for the host test: a CBW whose fields disagree with its arguments is a command the device must reject, and getting the residue wrong makes a short write look complete.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `out` | `unsigned char *` |  |  |
| `tag` | `unsigned` |  |  |
| `lba` | `unsigned long` |  |  |
| `blocks` | `unsigned` |  |  |
| `read` | `int` |  |  |
| `data_len` | `int` |  |  |

---

<a id="ubk_check_csw"></a>

### `ubk_check_csw`

`function` | [headers/drivers/usbblk.h:60](../../headers/drivers/usbblk.h#L60)

```c
int ubk_check_csw(const unsigned char *csw, unsigned tag, unsigned expect_len);
```

Docstring: Check a Command Status Wrapper.

Returns 1 when the CSW matches the CBW it was sent with and reports success, 0 otherwise. Pure, for the same reason. The residue check is what catches a device that moved fewer bytes than asked for: without it a truncated sector read would be handed back as good data.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `csw` | `unsigned char *` |  |  |
| `tag` | `unsigned` |  |  |
| `expect_len` | `unsigned` |  |  |

**Returns:** `int`

---

## Macros

<a id="ubk_block_size"></a>

### `UBK_BLOCK_SIZE`

`macro` | [headers/drivers/usbblk.h:14](../../headers/drivers/usbblk.h#L14)

```c
#define UBK_BLOCK_SIZE
```

---- SCSI logical block size and the READ(10)/WRITE(10) ceiling ----

---

<a id="ubk_max_blocks"></a>

### `UBK_MAX_BLOCKS`

`macro` | [headers/drivers/usbblk.h:15](../../headers/drivers/usbblk.h#L15)

```c
#define UBK_MAX_BLOCKS
```

---

<a id="ubk_max_sectors"></a>

### `UBK_MAX_SECTORS`

`macro` | [headers/drivers/usbblk.h:16](../../headers/drivers/usbblk.h#L16)

```c
#define UBK_MAX_SECTORS
```

---
