#ifndef RTL8139_H
#define RTL8139_H

/*
 * rtl8139 NIC driver interface.
 *
 * This header is the boundary between the polled rtl8139 driver
 * (rtl8139.c) and the protocol stack (net.c).  The driver owns the port
 * I/O, PCI probe, TX/RX rings, the NIC MAC and the PIT-calibrated clock;
 * the stack owns addressing, sockets and the demux that the driver
 * reaches through rtl_poll.  All frame sizes and MAC constants come from
 * net.h.
 */

#include "net.h"

/* Nonzero when the rtl8139 was found and initialized. */
int rtl_present(void);

/* Calibrate the clock, probe the NIC and set up the TX/RX rings. */
void rtl_init(void);

/* Transmit one raw Ethernet frame.  Returns 1 on success, 0 on failure
 * (no device, frame too large for a slot, or a TX deadline expiry). */
int rtl_send(const unsigned char *frame, unsigned len);

/* Drain the RX ring once; every received frame is handed to
 * net_rx_handle_frame (the protocol demux in net.c). */
void rtl_poll(void);

/* Copy the NIC MAC into out (NET_ETH_ALEN bytes). */
void rtl_get_mac(unsigned char out[NET_ETH_ALEN]);

/* The NIC I/O base, or 0 when the device is absent. */
unsigned short rtl_iobase(void);

/* Frame-level TX/RX counters (bytes are protocol counters in net.c). */
void rtl_counters(unsigned int *tx_frames, unsigned int *rx_frames);

#endif /* RTL8139_H */