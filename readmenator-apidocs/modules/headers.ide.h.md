# `headers/ide.h`

> Source: [headers/ide.h:1](../../headers/ide.h#L1) | language `h` | coverage 77.1% | [API index](../index.md)

IDE/ATA PIO driver for MiniOS.

## Contents

- **Functions:** [`ide_init`](#ide_init), [`ide_read_sectors`](#ide_read_sectors), [`ide_write_sectors`](#ide_write_sectors), [`ide_read_sector`](#ide_read_sector), [`ide_write_sector`](#ide_write_sector), [`ide_total_sectors`](#ide_total_sectors), [`ide_present`](#ide_present), [`ide_register_device`](#ide_register_device)
- **Macros:** [`IDE_PRIMARY_BASE`](#ide_primary_base), [`IDE_PRIMARY_CTRL`](#ide_primary_ctrl), [`IDE_REG_DATA`](#ide_reg_data), [`IDE_REG_ERROR`](#ide_reg_error), [`IDE_REG_SECCOUNT`](#ide_reg_seccount), [`IDE_REG_LBA_LO`](#ide_reg_lba_lo), [`IDE_REG_LBA_MID`](#ide_reg_lba_mid), [`IDE_REG_LBA_HI`](#ide_reg_lba_hi), [`IDE_REG_DRIVE`](#ide_reg_drive), [`IDE_REG_STATUS`](#ide_reg_status), [`IDE_REG_ALTSTATUS`](#ide_reg_altstatus), [`IDE_STATUS_ERR`](#ide_status_err), [`IDE_STATUS_DRQ`](#ide_status_drq), [`IDE_STATUS_SRV`](#ide_status_srv), [`IDE_STATUS_DF`](#ide_status_df), [`IDE_STATUS_RDY`](#ide_status_rdy), [`IDE_STATUS_BSY`](#ide_status_bsy), [`IDE_CMD_READ`](#ide_cmd_read), [`IDE_CMD_WRITE`](#ide_cmd_write), [`IDE_CMD_IDENTIFY`](#ide_cmd_identify), [`IDE_CMD_FLUSH`](#ide_cmd_flush), [`IDE_DRIVE_LBA`](#ide_drive_lba), [`IDE_DRIVE_MASTER`](#ide_drive_master), [`IDE_DRIVE_SLAVE`](#ide_drive_slave), [`IDE_TIMEOUT`](#ide_timeout), [`IDE_SECTOR_SIZE`](#ide_sector_size)

## Functions

<a id="ide_init"></a>

### `ide_init`

`function` | [headers/ide.h:49](../../headers/ide.h#L49)

```c
void ide_init(void);
```

Initialize the IDE driver: probe, IDENTIFY, report geometry.

*Called by:* [`block_init`](drivers.block.c.md#block_init)

---

<a id="ide_read_sectors"></a>

### `ide_read_sectors`

`function` | [headers/ide.h:53](../../headers/ide.h#L53)

```c
int ide_read_sectors(unsigned int lba, unsigned int count, void *buf);
```

Read/write sectors using 28-bit LBA.

Returns 0 on success, -1 on error.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `lba` | `unsigned int` |  |  |
| `count` | `unsigned int` |  |  |
| `buf` | `void *` |  |  |

**Returns:** `int`

*Called by:* [`table`](drivers.block.c.md#table), [`swap_in`](kernel.mm.swap.c.md#swap_in)

---

<a id="ide_write_sectors"></a>

### `ide_write_sectors`

`function` | [headers/ide.h:54](../../headers/ide.h#L54)

```c
int ide_write_sectors(unsigned int lba, unsigned int count, const void *buf);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `lba` | `unsigned int` |  |  |
| `count` | `unsigned int` |  |  |
| `buf` | `void *` |  |  |

**Returns:** `int`

*Called by:* [`swap_out`](kernel.mm.swap.c.md#swap_out)

---

<a id="ide_read_sector"></a>

### `ide_read_sector`

`function` | [headers/ide.h:57](../../headers/ide.h#L57)

```c
int ide_read_sector(unsigned int lba, void *buf);
```

Convenience: single sector read/write.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `lba` | `unsigned int` |  |  |
| `buf` | `void *` |  |  |

**Returns:** `int`

---

<a id="ide_write_sector"></a>

### `ide_write_sector`

`function` | [headers/ide.h:58](../../headers/ide.h#L58)

```c
int ide_write_sector(unsigned int lba, const void *buf);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `lba` | `unsigned int` |  |  |
| `buf` | `void *` |  |  |

**Returns:** `int`

---

<a id="ide_total_sectors"></a>

### `ide_total_sectors`

`function` | [headers/ide.h:61](../../headers/ide.h#L61)

```c
unsigned int ide_total_sectors(void);
```

Returns total sectors on the disk, or 0 if not detected.

**Returns:** `unsigned int`

*Called by:* [`block_init`](drivers.block.c.md#block_init)

---

<a id="ide_present"></a>

### `ide_present`

`function` | [headers/ide.h:64](../../headers/ide.h#L64)

```c
int ide_present(void);
```

Returns 1 if a disk was successfully detected.

**Returns:** `int`

*Called by:* [`__attribute__`](kernel.c.md#__attribute__)

---

<a id="ide_register_device"></a>

### `ide_register_device`

`function` | [headers/ide.h:68](../../headers/ide.h#L68)

```c
void ide_register_device(void);
```

Publish the Strategy ops table to the device registry (driver.h).

Called from ide_init; re-registration is a no-op (duplicate refused).

---

## Macros

<a id="ide_primary_base"></a>

### `IDE_PRIMARY_BASE`

`macro` | [headers/ide.h:9](../../headers/ide.h#L9)

```c
#define IDE_PRIMARY_BASE
```

Primary ATA controller ports

---

<a id="ide_primary_ctrl"></a>

### `IDE_PRIMARY_CTRL`

`macro` | [headers/ide.h:10](../../headers/ide.h#L10)

```c
#define IDE_PRIMARY_CTRL
```

---

<a id="ide_reg_data"></a>

### `IDE_REG_DATA`

`macro` | [headers/ide.h:13](../../headers/ide.h#L13)

```c
#define IDE_REG_DATA
```

Register offsets from base

---

<a id="ide_reg_error"></a>

### `IDE_REG_ERROR`

`macro` | [headers/ide.h:14](../../headers/ide.h#L14)

```c
#define IDE_REG_ERROR
```

R/W: data port (16-bit)

---

<a id="ide_reg_seccount"></a>

### `IDE_REG_SECCOUNT`

`macro` | [headers/ide.h:15](../../headers/ide.h#L15)

```c
#define IDE_REG_SECCOUNT
```

R: error, W: features

---

<a id="ide_reg_lba_lo"></a>

### `IDE_REG_LBA_LO`

`macro` | [headers/ide.h:16](../../headers/ide.h#L16)

```c
#define IDE_REG_LBA_LO
```

R/W: sector count / LBA low (48-bit)

---

<a id="ide_reg_lba_mid"></a>

### `IDE_REG_LBA_MID`

`macro` | [headers/ide.h:17](../../headers/ide.h#L17)

```c
#define IDE_REG_LBA_MID
```

R/W: LBA bits 0-7

---

<a id="ide_reg_lba_hi"></a>

### `IDE_REG_LBA_HI`

`macro` | [headers/ide.h:18](../../headers/ide.h#L18)

```c
#define IDE_REG_LBA_HI
```

R/W: LBA bits 8-15

---

<a id="ide_reg_drive"></a>

### `IDE_REG_DRIVE`

`macro` | [headers/ide.h:19](../../headers/ide.h#L19)

```c
#define IDE_REG_DRIVE
```

R/W: LBA bits 16-23

---

<a id="ide_reg_status"></a>

### `IDE_REG_STATUS`

`macro` | [headers/ide.h:20](../../headers/ide.h#L20)

```c
#define IDE_REG_STATUS
```

R/W: drive/head register

---

<a id="ide_reg_altstatus"></a>

### `IDE_REG_ALTSTATUS`

`macro` | [headers/ide.h:21](../../headers/ide.h#L21)

```c
#define IDE_REG_ALTSTATUS
```

R: status, W: command

---

<a id="ide_status_err"></a>

### `IDE_STATUS_ERR`

`macro` | [headers/ide.h:24](../../headers/ide.h#L24)

```c
#define IDE_STATUS_ERR
```

Status register bits

---

<a id="ide_status_drq"></a>

### `IDE_STATUS_DRQ`

`macro` | [headers/ide.h:25](../../headers/ide.h#L25)

```c
#define IDE_STATUS_DRQ
```

---

<a id="ide_status_srv"></a>

### `IDE_STATUS_SRV`

`macro` | [headers/ide.h:26](../../headers/ide.h#L26)

```c
#define IDE_STATUS_SRV
```

---

<a id="ide_status_df"></a>

### `IDE_STATUS_DF`

`macro` | [headers/ide.h:27](../../headers/ide.h#L27)

```c
#define IDE_STATUS_DF
```

---

<a id="ide_status_rdy"></a>

### `IDE_STATUS_RDY`

`macro` | [headers/ide.h:28](../../headers/ide.h#L28)

```c
#define IDE_STATUS_RDY
```

---

<a id="ide_status_bsy"></a>

### `IDE_STATUS_BSY`

`macro` | [headers/ide.h:29](../../headers/ide.h#L29)

```c
#define IDE_STATUS_BSY
```

---

<a id="ide_cmd_read"></a>

### `IDE_CMD_READ`

`macro` | [headers/ide.h:32](../../headers/ide.h#L32)

```c
#define IDE_CMD_READ
```

Commands

---

<a id="ide_cmd_write"></a>

### `IDE_CMD_WRITE`

`macro` | [headers/ide.h:33](../../headers/ide.h#L33)

```c
#define IDE_CMD_WRITE
```

READ SECTORS (28-bit LBA)

---

<a id="ide_cmd_identify"></a>

### `IDE_CMD_IDENTIFY`

`macro` | [headers/ide.h:34](../../headers/ide.h#L34)

```c
#define IDE_CMD_IDENTIFY
```

WRITE SECTORS (28-bit LBA)

---

<a id="ide_cmd_flush"></a>

### `IDE_CMD_FLUSH`

`macro` | [headers/ide.h:35](../../headers/ide.h#L35)

```c
#define IDE_CMD_FLUSH
```

IDENTIFY DEVICE

---

<a id="ide_drive_lba"></a>

### `IDE_DRIVE_LBA`

`macro` | [headers/ide.h:38](../../headers/ide.h#L38)

```c
#define IDE_DRIVE_LBA
```

Drive/Head register bits

---

<a id="ide_drive_master"></a>

### `IDE_DRIVE_MASTER`

`macro` | [headers/ide.h:39](../../headers/ide.h#L39)

```c
#define IDE_DRIVE_MASTER
```

LBA mode

---

<a id="ide_drive_slave"></a>

### `IDE_DRIVE_SLAVE`

`macro` | [headers/ide.h:40](../../headers/ide.h#L40)

```c
#define IDE_DRIVE_SLAVE
```

master drive

---

<a id="ide_timeout"></a>

### `IDE_TIMEOUT`

`macro` | [headers/ide.h:43](../../headers/ide.h#L43)

```c
#define IDE_TIMEOUT
```

Timeout in PIT ticks (approximate)

---

<a id="ide_sector_size"></a>

### `IDE_SECTOR_SIZE`

`macro` | [headers/ide.h:46](../../headers/ide.h#L46)

```c
#define IDE_SECTOR_SIZE
```

Sector size in bytes

---
