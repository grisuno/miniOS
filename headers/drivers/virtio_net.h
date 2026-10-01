/** Docstring: drivers/virtio_net.h -- virtio-net boundary.
 *
 * Polled legacy virtio-net (drivers/virtio_net.c) behind the same
 * verbs as the rtl8139 driver, so net.c prefers it with no stack
 * changes: probe once, send raw frames, drain RX into the demux. The
 * `vnet` builtin and the net-layer preference are the only
 * consumers; sockets never name a device. */

#ifndef DRIVERS_VIRTIO_NET_H
#define DRIVERS_VIRTIO_NET_H

/** Docstring: Probe PCI for a virtio-net device and bring both queues
 * up. Idempotent: a second call reuses the live queues. Returns 1
 * when the device is ready, 0 when absent or unusable (fail-closed,
 * rtl8139 stays). */
int vnet_init(void);

/** Docstring: True once vnet_init brought the queues up. */
int vnet_present(void);

/** Docstring: Transmit one raw Ethernet frame. Returns 1 on success,
 * 0 on failure (no device, oversize, or TX deadline expiry). Pads
 * short frames to 60 bytes like the rtl8139 path. */
int vnet_send(const unsigned char *frame, unsigned len);

/** Docstring: Drain completed RX buffers into net_rx_handle_frame,
 * reposting every descriptor. Bounded per call, never blocks. */
void vnet_poll(void);

/** Docstring: Copy the NIC MAC into out (NET_ETH_ALEN bytes). */
void vnet_get_mac(unsigned char out[6]);

/** Docstring: The NIC I/O base, or 0 when the device is absent. */
unsigned short vnet_iobase(void);

/** Docstring: Frame-level TX/RX counters. */
void vnet_counters(unsigned int *tx_frames, unsigned int *rx_frames);

/** Docstring: Link-up status from the config space. */
int vnet_link_up(void);

#endif
