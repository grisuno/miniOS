# `headers/net/rtl8139.h`

> Source: [headers/net/rtl8139.h:1](../../headers/net/rtl8139.h#L1) | language `h` | coverage 87.5% | [API index](../index.md)

## Contents

- **Functions:** [`rtl_present`](#rtl_present), [`rtl_init`](#rtl_init), [`rtl_send`](#rtl_send), [`net_rx_handle_frame`](#net_rx_handle_frame), [`rtl_get_mac`](#rtl_get_mac), [`rtl_iobase`](#rtl_iobase), [`rtl_counters`](#rtl_counters)

## Functions

<a id="rtl_present"></a>

### `rtl_present`

`function` | [headers/net/rtl8139.h:18](../../headers/net/rtl8139.h#L18)

```c
int rtl_present(void);
```

Nonzero when the rtl8139 was found and initialized.

**Returns:** `int`

---

<a id="rtl_init"></a>

### `rtl_init`

`function` | [headers/net/rtl8139.h:21](../../headers/net/rtl8139.h#L21)

```c
void rtl_init(void);
```

Calibrate the clock, probe the NIC and set up the TX/RX rings.

*Called by:* [`net_init`](net.net.c.md#net_init)

---

<a id="rtl_send"></a>

### `rtl_send`

`function` | [headers/net/rtl8139.h:25](../../headers/net/rtl8139.h#L25)

```c
int rtl_send(const unsigned char *frame, unsigned len);
```

Transmit one raw Ethernet frame.

Returns 1 on success, 0 on failure (no device, frame too large for a slot, or a TX deadline expiry).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `frame` | `unsigned char *` |  |  |
| `len` | `unsigned` |  |  |

**Returns:** `int`

---

<a id="net_rx_handle_frame"></a>

### `net_rx_handle_frame`

`function` | [headers/net/rtl8139.h:28](../../headers/net/rtl8139.h#L28)

```c
* net_rx_handle_frame (the protocol demux in net.c). */ void rtl_poll(void);
```

Demux entry point the rtl8139 driver (rtl8139.c) calls for every frame drained from the RX ring; lives in net.c.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `c` | `the protocol demux in net.` |  |  |

**Returns:** `*`

> **Inherited:** Documentation from [`net_rx_handle_frame`](#net_rx_handle_frame) (headers/net.h:159).

---

<a id="rtl_get_mac"></a>

### `rtl_get_mac`

`function` | [headers/net/rtl8139.h:32](../../headers/net/rtl8139.h#L32)

```c
void rtl_get_mac(unsigned char out[NET_ETH_ALEN]);
```

Copy the NIC MAC into out (NET_ETH_ALEN bytes).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `NET_ETH_ALEN` | `unsigned char out[ ]` |  |  |

*Called by:* [`net_init`](net.net.c.md#net_init)

---

<a id="rtl_iobase"></a>

### `rtl_iobase`

`function` | [headers/net/rtl8139.h:35](../../headers/net/rtl8139.h#L35)

```c
unsigned short rtl_iobase(void);
```

The NIC I/O base, or 0 when the device is absent.

**Returns:** `unsigned short`

*Called by:* [`net_cmd_status`](net.net.c.md#net_cmd_status)

---

<a id="rtl_counters"></a>

### `rtl_counters`

`function` | [headers/net/rtl8139.h:38](../../headers/net/rtl8139.h#L38)

```c
void rtl_counters(unsigned int *tx_frames, unsigned int *rx_frames);
```

Frame-level TX/RX counters (bytes are protocol counters in net.c).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `tx_frames` | `unsigned int *` |  |  |
| `rx_frames` | `unsigned int *` |  |  |

*Called by:* [`net_cmd_status`](net.net.c.md#net_cmd_status)

---
