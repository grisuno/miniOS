#include "kernel.h"
#include "net.h"
#include "net/rtl8139.h"
#include "drivers/pci.h"
#include "sched.h"

/*
 * Polled rtl8139 NIC driver (QEMU slirp user networking target).
 *
 * The driver owns the port I/O, PCI discovery, the transmit descriptors
 * and the classic 8 KB receive ring.  There is no interrupt controller
 * configured, so the stack drives receive through rtl_poll and TX waits
 * on the descriptor owner bit with a deadline, yielding the CPU while
 * it waits instead of spinning it away.
 *
 * Time is queried, never calibrated here: net_time_ms is a thin query
 * over the central PIT-calibrated TSC clock (kernel/time.c ktime_ms),
 * which is owned by the early boot path. Drivers must never calibrate.
 */

/* ================================================================
 *  Port and PCI access
 * ================================================================ */

static unsigned short rtl_iobase_val;

/* Byte/word port I/O comes from kernel.h (outb/inb/outw/inw, same asm).
 * Only the dword pair stays local: the shared header has no outl/inl. */
static void outl_port(unsigned short port, unsigned int val) {
    __asm__ volatile("outl %0, %1" : : "a"(val), "Nd"(port));
}

static unsigned int inl_port(unsigned short port) {
    unsigned int v;
    __asm__ volatile("inl %1, %0" : "=a"(v) : "Nd"(port));
    return v;
}

static unsigned char rtl_reg8(unsigned short off) { return inb((unsigned short)(rtl_iobase_val + off)); }
static void rtl_reg8_w(unsigned short off, unsigned char v) { outb((unsigned short)(rtl_iobase_val + off), v); }
static unsigned short rtl_reg16(unsigned short off) { return inw((unsigned short)(rtl_iobase_val + off)); }
static void rtl_reg16_w(unsigned short off, unsigned short v) { outw((unsigned short)(rtl_iobase_val + off), v); }
static unsigned int rtl_reg32(unsigned short off) { return inl_port((unsigned short)(rtl_iobase_val + off)); }
static void rtl_reg32_w(unsigned short off, unsigned int v) { outl_port((unsigned short)(rtl_iobase_val + off), v); }

#define RTL_REG_CR      0x37
#define RTL_REG_TSD0    0x10
#define RTL_REG_TSAD0   0x20
#define RTL_REG_RBSTART 0x30
#define RTL_REG_CAPR    0x38
#define RTL_REG_CBR     0x3A
#define RTL_REG_9346CR  0x50
#define RTL_REG_CONFIG1 0x52

/* PCI config space lives in drivers/pci.h now (shared with
 * virtio-blk and future devices); only the dword port pair stays
 * local, passed in as callbacks. */
static unsigned short rtl_find(void) {
    int dev = pci_find(NET_PCI_VENDOR, NET_PCI_DEVICE, inl_port, outl_port);
    if (dev < 0) return 0;
    {
        unsigned int cmd = pci_cfg_read(0, (unsigned)dev, 0, 4, outl_port, inl_port);
        pci_cfg_write(0, (unsigned)dev, 0, 4, cmd | 0x7, outl_port);
        {
            unsigned int bar0 = pci_cfg_read(0, (unsigned)dev, 0, 0x10, outl_port, inl_port);
            if (bar0 & 1) return (unsigned short)(bar0 & ~3u);
            return 0;
        }
    }
}

/* ================================================================
 *  Time query (owned by kernel/time.c, queried here)
 * ================================================================
 *
 * The central ktime_ms clock is PIT-calibrated on first use by the
 * early boot path. This driver only queries it for its TX/reset
 * deadlines; the private TSC calibration used to live here and has
 * been deleted (a second base/per-ms pair beside ktime's is a second
 * clock, and drivers must never calibrate).
 */

unsigned long net_time_ms(void) {
    return ktime_ms();
}

/* ================================================================
 *  Device state
 * ================================================================ */

static unsigned char *rtl_rx_ring;      /* NET_RX_BUF_LEN bytes, aligned */
static unsigned char rtl_rx_scratch[NET_MAX_FRAME];
static unsigned short rtl_rx_capr;
static unsigned char rtl_mac[NET_ETH_ALEN];
static unsigned int  rtl_tx_packets;
static unsigned int  rtl_rx_packets;
static unsigned      rtl_tx_slot;

int rtl_present(void) {
    return rtl_iobase_val ? 1 : 0;
}

static void rtl_reset(void) {
    unsigned long deadline;
    rtl_reg8_w(RTL_REG_CR, 0x10);
    deadline = net_time_ms() + 200;
    while (rtl_reg8(RTL_REG_CR) & 0x10) {
        if (net_time_ms() > deadline) break;
    }
}

void rtl_init(void) {
    unsigned long ptr;
    rtl_iobase_val = rtl_find();
    if (!rtl_iobase_val) return;

    rtl_reset();

    rtl_reg8_w(RTL_REG_9346CR, 0xC0);
    rtl_reg8_w(RTL_REG_CONFIG1, 0x00);

    rtl_rx_ring = kmalloc(NET_RX_BUF_LEN + NET_RX_ALIGN);
    if (!rtl_rx_ring) return;
    ptr = (unsigned long)rtl_rx_ring;
    ptr = (ptr + NET_RX_ALIGN - 1) & ~(unsigned long)(NET_RX_ALIGN - 1);
    rtl_rx_ring = (unsigned char *)ptr;
    rtl_reg32_w(RTL_REG_RBSTART, (unsigned int)ptr);
    rtl_rx_capr = 0;

    rtl_mac[0] = rtl_reg8(0x00);
    rtl_mac[1] = rtl_reg8(0x01);
    rtl_mac[2] = rtl_reg8(0x02);
    rtl_mac[3] = rtl_reg8(0x03);
    rtl_mac[4] = rtl_reg8(0x04);
    rtl_mac[5] = rtl_reg8(0x05);

    rtl_reg16_w(0x3C, 0x0000);
    rtl_reg16_w(0x44, NET_RCR);
    rtl_reg8_w(RTL_REG_CR, 0x0D);
}

/* Cooperative TX wait: the NIC owns no interrupt line in this build,
 * so completion is polled, but a congested descriptor must not spin
 * the CPU away from every other thread. The wait yields every
 * RTL_TX_YIELD_EVERY spins and stays deadline-bounded (fail closed
 * with 0 past the deadline, exactly like the old busy-wait). */
#define RTL_TX_YIELD_EVERY 1024u

static int rtl_tx_wait(unsigned slot, unsigned long deadline) {
    unsigned spins = 0;
    while (!(rtl_reg32((unsigned short)(RTL_REG_TSD0 + slot * 4)) & 0x2000)) {
        if (net_time_ms() > deadline) return 0;
        if ((++spins & (RTL_TX_YIELD_EVERY - 1u)) == 0) yield();
    }
    return 1;
}

int rtl_send(const unsigned char *frame, unsigned len) {
    unsigned long deadline;
    unsigned attempt;
    if (!rtl_iobase_val) return 0;
    if (len < 60) len = 60;
    if (len > NET_TX_MAX) return 0;
    for (attempt = 0; attempt < NET_TX_SLOTS; attempt++) {
        unsigned slot = rtl_tx_slot;
        unsigned int tsd = rtl_reg32((unsigned short)(RTL_REG_TSD0 + slot * 4));
        if (!(tsd & 0x2000)) {
            deadline = net_time_ms() + 2000;
            if (!rtl_tx_wait(slot, deadline)) return 0;
        }
        rtl_reg32_w((unsigned short)(RTL_REG_TSAD0 + slot * 4), (unsigned int)(unsigned long)frame);
        rtl_reg32_w((unsigned short)(RTL_REG_TSD0 + slot * 4), len & 0x1FFF);
        deadline = net_time_ms() + 2000;
        if (!rtl_tx_wait(slot, deadline)) return 0;
        rtl_tx_slot = (slot + 1) % NET_TX_SLOTS;
        rtl_tx_packets++;
        return 1;
    }
    return 0;
}

void rtl_get_mac(unsigned char out[NET_ETH_ALEN]) {
    unsigned i;
    for (i = 0; i < NET_ETH_ALEN; i++) out[i] = rtl_mac[i];
}

unsigned short rtl_iobase(void) {
    return rtl_iobase_val;
}

void rtl_counters(unsigned int *tx_frames, unsigned int *rx_frames) {
    *tx_frames = rtl_tx_packets;
    *rx_frames = rtl_rx_packets;
}

/* Copy one received frame out of the ring into the scratch buffer,
 * wrapping at the ring end, then hand it to the protocol demux.
 * Fail closed on a hostile length: the caller validates, but this
 * function must never trust it (an underflowed n would copy ~4 GB,
 * an oversized one would overflow the scratch). */
static void rtl_rx_frame_wrapped(unsigned length) {
    unsigned n;
    unsigned pos = rtl_rx_capr + 4;
    unsigned k;
    if (length < 4) { net_rx_dropped++; return; }
    n = length - 4;
    if (n > sizeof(rtl_rx_scratch)) { net_rx_dropped++; return; }
    for (k = 0; k < n; k++) {
        rtl_rx_scratch[k] = rtl_rx_ring[pos & (NET_RX_BUF_LEN - 1)];
        pos++;
    }
    net_rx_handle_frame(rtl_rx_scratch, n);
}

void rtl_poll(void) {
    unsigned short cbr;
    unsigned i = 0;
    if (!rtl_iobase_val) return;
    cbr = rtl_reg16(RTL_REG_CBR);
    while (rtl_rx_capr != cbr) {
        unsigned char hdr[4];
        unsigned short status, length;
        int k;
        for (k = 0; k < 4; k++)
            hdr[k] = rtl_rx_ring[(rtl_rx_capr + k) & (NET_RX_BUF_LEN - 1)];
        status = (unsigned short)(hdr[0] | (hdr[1] << 8));
        length = (unsigned short)(hdr[2] | (hdr[3] << 8));
        if (status & 0x1) {
            if (length >= 14 && length <= NET_MAX_FRAME) {
                rtl_rx_packets++;
                rtl_rx_frame_wrapped((unsigned)length);
            } else {
                net_rx_dropped++;
            }
        }
        rtl_rx_capr = (unsigned short)((rtl_rx_capr + length + 4 + 3) & ~3u)
                      & (unsigned short)(NET_RX_BUF_LEN - 1);
        rtl_reg16_w(RTL_REG_CAPR, (unsigned short)(rtl_rx_capr - 16));
        cbr = rtl_reg16(RTL_REG_CBR);
        if (++i > 64) break;
    }
    rtl_reg16_w(RTL_REG_CAPR, (unsigned short)(rtl_rx_capr - 16));
}