#include "kernel.h"
#include "net.h"
#include "rtl8139.h"

/*
 * Polled rtl8139 NIC driver (QEMU slirp user networking target).
 *
 * The driver owns the port I/O, PCI discovery, the transmit descriptors
 * and the classic 8 KB receive ring.  There is no interrupt controller
 * configured, so the stack drives receive through rtl_poll and the
 * driver busy-waits on the TX descriptor owner bit with a deadline.
 *
 * The TSC clock is calibrated once against a PIT channel 2 one-shot; the
 * resulting net_time_ms clock is shared with the protocol stack for its
 * retransmission and timeout logic.
 */

/* ================================================================
 *  Port and PCI access
 * ================================================================ */

static unsigned short rtl_iobase_val;

static void outb_port(unsigned short port, unsigned char val) {
    __asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

static unsigned char inb_port(unsigned short port) {
    unsigned char v;
    __asm__ volatile("inb %1, %0" : "=a"(v) : "Nd"(port));
    return v;
}

static void outw_port(unsigned short port, unsigned short val) {
    __asm__ volatile("outw %0, %1" : : "a"(val), "Nd"(port));
}

static void outl_port(unsigned short port, unsigned int val) {
    __asm__ volatile("outl %0, %1" : : "a"(val), "Nd"(port));
}

static unsigned short inw_port(unsigned short port) {
    unsigned short v;
    __asm__ volatile("inw %1, %0" : "=a"(v) : "Nd"(port));
    return v;
}

static unsigned int inl_port(unsigned short port) {
    unsigned int v;
    __asm__ volatile("inl %1, %0" : "=a"(v) : "Nd"(port));
    return v;
}

static unsigned char rtl_reg8(unsigned short off) { return inb_port((unsigned short)(rtl_iobase_val + off)); }
static void rtl_reg8_w(unsigned short off, unsigned char v) { outb_port((unsigned short)(rtl_iobase_val + off), v); }
static unsigned short rtl_reg16(unsigned short off) { return inw_port((unsigned short)(rtl_iobase_val + off)); }
static void rtl_reg16_w(unsigned short off, unsigned short v) { outw_port((unsigned short)(rtl_iobase_val + off), v); }
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

static unsigned int pci_read32(unsigned bus, unsigned dev, unsigned func, unsigned reg) {
    outl_port(0xCF8, 0x80000000u | (bus << 16) | (dev << 11) | (func << 8) | (reg & 0xFC));
    return inl_port(0xCFC);
}

static void pci_write32(unsigned bus, unsigned dev, unsigned func, unsigned reg, unsigned int val) {
    outl_port(0xCF8, 0x80000000u | (bus << 16) | (dev << 11) | (func << 8) | (reg & 0xFC));
    outl_port(0xCFC, val);
}

static unsigned short rtl_find(void) {
    unsigned dev;
    for (dev = 0; dev < 32; dev++) {
        unsigned int id = pci_read32(0, dev, 0, 0);
        if ((id & 0xFFFF) == NET_PCI_VENDOR && ((id >> 16) & 0xFFFF) == NET_PCI_DEVICE) {
            unsigned int cmd = pci_read32(0, dev, 0, 4);
            pci_write32(0, dev, 0, 4, cmd | 0x7);
            unsigned int bar0 = pci_read32(0, dev, 0, 0x10);
            if (bar0 & 1) return (unsigned short)(bar0 & ~3u);
            return 0;
        }
    }
    return 0;
}

/* ================================================================
 *  TSC clock (PIT channel 2 one-shot calibration)
 * ================================================================ */

static unsigned long rtl_tsc_base;
static unsigned long rtl_tsc_per_ms;

static unsigned long rtl_rdtsc(void) {
    unsigned int lo, hi;
    __asm__ volatile("rdtsc" : "=a"(lo), "=d"(hi));
    return ((unsigned long)hi << 32) | lo;
}

static void net_time_init(void) {
    unsigned long t0, t1;
    outb_port(0x61, (unsigned char)((inb_port(0x61) & 0x0F) | 0x01));
    outb_port(0x43, 0xB0);
    outb_port(0x42, 0x96);
    outb_port(0x42, 0x04);
    t0 = rtl_rdtsc();
    while (!(inb_port(0x61) & 0x20));
    t1 = rtl_rdtsc();
    outb_port(0x61, (unsigned char)(inb_port(0x61) & 0x0F));
    rtl_tsc_per_ms = t1 - t0;
    rtl_tsc_base = t1;
}

unsigned long net_time_ms(void) {
    return rtl_tsc_per_ms ? (rtl_rdtsc() - rtl_tsc_base) / rtl_tsc_per_ms : 0;
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
    net_time_init();
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
            while (!(rtl_reg32((unsigned short)(RTL_REG_TSD0 + slot * 4)) & 0x2000)) {
                if (net_time_ms() > deadline) return 0;
            }
        }
        rtl_reg32_w((unsigned short)(RTL_REG_TSAD0 + slot * 4), (unsigned int)(unsigned long)frame);
        rtl_reg32_w((unsigned short)(RTL_REG_TSD0 + slot * 4), len & 0x1FFF);
        deadline = net_time_ms() + 2000;
        while (!(rtl_reg32((unsigned short)(RTL_REG_TSD0 + slot * 4)) & 0x2000)) {
            if (net_time_ms() > deadline) return 0;
        }
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
 * wrapping at the ring end, then hand it to the protocol demux. */
static void rtl_rx_frame_wrapped(unsigned length) {
    unsigned n = length - 4;
    unsigned pos = rtl_rx_capr + 4;
    unsigned k;
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