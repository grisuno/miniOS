# `headers/drivers/ahci.h`

> Source: [headers/drivers/ahci.h:1](../../headers/drivers/ahci.h#L1) | language `h` | coverage 100.0% | [API index](../index.md)

Docstring: drivers/ahci.h -- AHCI (SATA) host controller, polled.

## Contents

- **Functions:** [`ahci_init`](#ahci_init), [`ahci_present`](#ahci_present), [`ahci_version`](#ahci_version), [`ahci_port`](#ahci_port), [`ahci_ports_implemented`](#ahci_ports_implemented), [`ahci_note`](#ahci_note), [`ahci_sectors`](#ahci_sectors), [`ahci_read_sectors`](#ahci_read_sectors), [`ahci_write_sectors`](#ahci_write_sectors), [`ahci_register_device`](#ahci_register_device)

## Functions

<a id="ahci_init"></a>

### `ahci_init`

`function` | [headers/drivers/ahci.h:16](../../headers/drivers/ahci.h#L16)

```c
int ahci_init(void);
```

Docstring: Probe PCI for an AHCI function and bring up the first ATA disk.

Idempotent: a second call returns the cached result. Returns 1 when a disk is ready for I/O, 0 otherwise (ahci_note says why).

**Returns:** `int`

*Called by:* [`block_init`](drivers.block.c.md#block_init)

---

<a id="ahci_present"></a>

### `ahci_present`

`function` | [headers/drivers/ahci.h:19](../../headers/drivers/ahci.h#L19)

```c
int ahci_present(void);
```

Docstring: True once ahci_init brought a disk up.

**Returns:** `int`

*Called by:* [`__attribute__`](kernel.c.md#__attribute__)

---

<a id="ahci_version"></a>

### `ahci_version`

`function` | [headers/drivers/ahci.h:22](../../headers/drivers/ahci.h#L22)

```c
unsigned ahci_version(void);
```

Docstring: HBA version register (major in bits 31:16, minor 15:0).

**Returns:** `unsigned`

*Called by:* [`block_init`](drivers.block.c.md#block_init)

---

<a id="ahci_port"></a>

### `ahci_port`

`function` | [headers/drivers/ahci.h:25](../../headers/drivers/ahci.h#L25)

```c
int ahci_port(void);
```

Docstring: Port number of the claimed disk, or -1 when none.

**Returns:** `int`

*Called by:* [`block_init`](drivers.block.c.md#block_init)

---

<a id="ahci_ports_implemented"></a>

### `ahci_ports_implemented`

`function` | [headers/drivers/ahci.h:28](../../headers/drivers/ahci.h#L28)

```c
unsigned ahci_ports_implemented(void);
```

Docstring: Bitmap of ports the HBA implements (PI register).

**Returns:** `unsigned`

---

<a id="ahci_note"></a>

### `ahci_note`

`function` `const` | [headers/drivers/ahci.h:31](../../headers/drivers/ahci.h#L31)

```c
const char *ahci_note(void);
```

Docstring: Human-readable state of the last probe.

**Returns:** `char *`

*Called by:* [`block_init`](drivers.block.c.md#block_init)

---

<a id="ahci_sectors"></a>

### `ahci_sectors`

`function` | [headers/drivers/ahci.h:34](../../headers/drivers/ahci.h#L34)

```c
unsigned long ahci_sectors(void);
```

Docstring: Capacity of the claimed disk in 512-byte sectors.

**Returns:** `unsigned long`

*Called by:* [`block_init`](drivers.block.c.md#block_init)

---

<a id="ahci_read_sectors"></a>

### `ahci_read_sectors`

`function` | [headers/drivers/ahci.h:40](../../headers/drivers/ahci.h#L40)

```c
int ahci_read_sectors(unsigned lba, unsigned count, void *buf);
```

Docstring: Read count sectors starting at lba into buf.

Any count is accepted; it is split into AHCI_MAX_SECTORS commands. Returns 0 on success, -1 on a bad argument, a range past the disk, a device error or a timeout.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `lba` | `unsigned` |  |  |
| `count` | `unsigned` |  |  |
| `buf` | `void *` |  |  |

**Returns:** `int`

---

<a id="ahci_write_sectors"></a>

### `ahci_write_sectors`

`function` | [headers/drivers/ahci.h:45](../../headers/drivers/ahci.h#L45)

```c
int ahci_write_sectors(unsigned lba, unsigned count, const void *buf);
```

Docstring: Write count sectors starting at lba from buf, followed by FLUSH CACHE EXT so the data survives a power cut.

Same contract as the read.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `lba` | `unsigned` |  |  |
| `count` | `unsigned` |  |  |
| `buf` | `void *` |  |  |

**Returns:** `int`

---

<a id="ahci_register_device"></a>

### `ahci_register_device`

`function` | [headers/drivers/ahci.h:48](../../headers/drivers/ahci.h#L48)

```c
void ahci_register_device(void);
```

Docstring: Publish the disk as "ahci0" in the device registry.

*Called by:* [`block_init`](drivers.block.c.md#block_init)

---
