# `headers/drivers/virtio_net.h`

> Source: [headers/drivers/virtio_net.h:1](../../headers/drivers/virtio_net.h#L1) | language `h` | coverage 88.9% | [API index](../index.md)

Docstring: drivers/virtio_net.h -- virtio-net boundary.

## Contents

- **Functions:** [`vnet_init`](#vnet_init), [`vnet_present`](#vnet_present), [`failure`](#failure), [`vnet_poll`](#vnet_poll), [`vnet_get_mac`](#vnet_get_mac), [`vnet_iobase`](#vnet_iobase), [`vnet_counters`](#vnet_counters), [`vnet_link_up`](#vnet_link_up)

## Functions

<a id="vnet_init"></a>

### `vnet_init`

`function` | [headers/drivers/virtio_net.h:16](../../headers/drivers/virtio_net.h#L16)

```c
int vnet_init(void);
```

Docstring: Probe PCI for a virtio-net device and bring both queues up.

Idempotent: a second call reuses the live queues. Returns 1 when the device is ready, 0 when absent or unusable (fail-closed, rtl8139 stays).

**Returns:** `int`

*Called by:* [`unusable`](drivers.virtio_net.c.md#unusable), [`shell_exec_builtin`](kernel.shell.c.md#shell_exec_builtin), [`net_init`](net.net.c.md#net_init)

---

<a id="vnet_present"></a>

### `vnet_present`

`function` | [headers/drivers/virtio_net.h:19](../../headers/drivers/virtio_net.h#L19)

```c
int vnet_present(void);
```

Docstring: True once vnet_init brought the queues up.

**Returns:** `int`

---

<a id="failure"></a>

### `failure`

`function` | [headers/drivers/virtio_net.h:22](../../headers/drivers/virtio_net.h#L22)

```c
* 0 on failure (no device, oversize, or TX deadline expiry). Pads * short frames to 60 bytes like the rtl8139 path. */ int vnet_send(const unsigned char *frame, unsigned len);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `device` | `no` |  |  |
| `expiry` | `or TX deadline` |  |  |

**Returns:** `* 0 on`

---

<a id="vnet_poll"></a>

### `vnet_poll`

`function` | [headers/drivers/virtio_net.h:28](../../headers/drivers/virtio_net.h#L28)

```c
void vnet_poll(void);
```

Docstring: Drain completed RX buffers into net_rx_handle_frame, reposting every descriptor.

Bounded per call, never blocks.

---

<a id="vnet_get_mac"></a>

### `vnet_get_mac`

`function` | [headers/drivers/virtio_net.h:31](../../headers/drivers/virtio_net.h#L31)

```c
void vnet_get_mac(unsigned char out[6]);
```

Docstring: Copy the NIC MAC into out (NET_ETH_ALEN bytes).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `out` | `unsigned char [6]` |  |  |

*Called by:* [`shell_exec_builtin`](kernel.shell.c.md#shell_exec_builtin), [`net_init`](net.net.c.md#net_init)

---

<a id="vnet_iobase"></a>

### `vnet_iobase`

`function` | [headers/drivers/virtio_net.h:34](../../headers/drivers/virtio_net.h#L34)

```c
unsigned short vnet_iobase(void);
```

Docstring: The NIC I/O base, or 0 when the device is absent.

**Returns:** `unsigned short`

*Called by:* [`net_cmd_status`](net.net.c.md#net_cmd_status)

---

<a id="vnet_counters"></a>

### `vnet_counters`

`function` | [headers/drivers/virtio_net.h:37](../../headers/drivers/virtio_net.h#L37)

```c
void vnet_counters(unsigned int *tx_frames, unsigned int *rx_frames);
```

Docstring: Frame-level TX/RX counters.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `tx_frames` | `unsigned int *` |  |  |
| `rx_frames` | `unsigned int *` |  |  |

*Called by:* [`net_cmd_status`](net.net.c.md#net_cmd_status)

---

<a id="vnet_link_up"></a>

### `vnet_link_up`

`function` | [headers/drivers/virtio_net.h:40](../../headers/drivers/virtio_net.h#L40)

```c
int vnet_link_up(void);
```

Docstring: Link-up status from the config space.

**Returns:** `int`

---
