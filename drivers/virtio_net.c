/** Docstring: drivers/virtio_net.c -- Polled legacy virtio-net driver.
 *
 * A virtio-net device (QEMU -device virtio-net-pci or -nic
 * user,model=virtio-net-pci) behind the rtl8139 verbs, so net.c
 * prefers it with zero stack changes: same raw frames, same
 * synchronous poll discipline. Legacy (0.9.5) interface over the
 * BAR0 I/O ports: no MSI-X, no interrupts, completion by polling
 * the used rings with a deadline, exactly like the rtl8139 no-IRQ
 * discipline and the virtio-blk sibling. Fail-closed throughout:
 * absent device, feature mismatch, queue refusal and completion
 * timeouts all refuse with 0 and leave no half-armed queue.
 *
 * Two queues: RX is queue 0, TX is queue 1, each with its own
 * three-page area (descriptors, avail, used) derived from QueuePFN
 * exactly like the block sibling. Every heap buffer doubles as its
 * guest-physical address by the identity-map rule (VA == PA); the
 * virtio-net header and the TX staging area are heap objects for
 * exactly this reason, never image statics. Without mergeable
 * buffers every packet carries the 10-byte header on both paths.
 * One TX in flight at a time: the stack never overlaps device
 * access on one CPU, and SMP callers serialize upstream exactly
 * like the block sibling documents. */

#include "kernel.h"
#include "net.h"
#include "drivers/pci.h"
#include "drivers/virtio_net.h"

#define VNET_VENDOR 0x1AF4u
#define VNET_DEV_LEGACY 0x1000u
#define VNET_DEV_TRANS 0x1041u

#define VNET_F_ACK 1u
#define VNET_F_DRIVER 2u
#define VNET_F_OK 8u
#define VNET_F_DRIVER_OK 4u

#define VNET_QNUM 256u
#define VNET_DESC_SZ 16u
#define VNET_AVAIL_OFF 4096u
#define VNET_USED_OFF 8192u
#define VNET_QAREA 12288u

#define VNET_DESC_NEXT 1u
#define VNET_DESC_WRITE 2u

#define VNET_Q_RX 0u
#define VNET_Q_TX 1u

#define VNET_HDR_LEN 10u
#define VNET_RX_BUFS 32u
#define VNET_RX_SIZE 2048u
#define VNET_TX_SIZE 2048u
#define VNET_MIN_FRAME 60u
#define VNET_MAX_FRAME 1514u
#define VNET_TMO_MS 5000u
#define VNET_POLL_MAX 64u

#define VNET_CFG_MAC 0x14u
#define VNET_CFG_STATUS 0x1Au
#define VNET_ST_LINK_UP 1u

static unsigned short vnet_io;
static int vnet_on;
static unsigned char vnet_mac[6];
static unsigned int vnet_tx_packets;
static unsigned int vnet_rx_packets;

static unsigned char *vnet_rx_page;
static unsigned char *vnet_rx_used;
static unsigned short vnet_rx_last;
static unsigned vnet_rx_qnum;
static unsigned char *vnet_rx_bufs;

static unsigned char *vnet_tx_page;
static unsigned char *vnet_tx_used;
static unsigned short vnet_tx_last;
static unsigned vnet_tx_qnum;
static unsigned char *vnet_tx_stage;

static void vnet_outb(unsigned short port, unsigned char v) {
    __asm__ volatile("outb %0, %1" : : "a"(v), "Nd"(port));
}

static void vnet_outw(unsigned short port, unsigned short v) {
    __asm__ volatile("outw %0, %1" : : "a"(v), "Nd"(port));
}

static void vnet_outl(unsigned short port, unsigned v) {
    __asm__ volatile("outl %0, %1" : : "a"(v), "Nd"(port));
}

static unsigned char vnet_inb(unsigned short port) {
    unsigned char v;
    __asm__ volatile("inb %1, %0" : "=a"(v) : "Nd"(port));
    return v;
}

static unsigned short vnet_inw(unsigned short port) {
    unsigned short v;
    __asm__ volatile("inw %1, %0" : "=a"(v) : "Nd"(port));
    return v;
}

static unsigned vnet_inl(unsigned short port) {
    unsigned v;
    __asm__ volatile("inl %1, %0" : "=a"(v) : "Nd"(port));
    return v;
}

/** Docstring: Bring one queue up: negotiate no features, size it,
 * publish its page area, return its depth. Shared by RX and TX so
 * the two setups cannot drift apart. */
static unsigned vnet_queue_up(unsigned qsel) {
    unsigned qmax;
    unsigned char *raw;
    unsigned char *page;
    unsigned long pfn;
    unsigned i;
    vnet_outw(vnet_io + 0x0E, (unsigned short)qsel);
    qmax = vnet_inw(vnet_io + 0x0C);
    if (qmax < 4u || qmax > 1024u) return 0;
    qmax = qmax < VNET_QNUM ? qmax : VNET_QNUM;
    vnet_outw(vnet_io + 0x0C, (unsigned short)qmax);
    raw = kmalloc(VNET_QAREA + 0xFFFu);
    if (!raw) return 0;
    page = (unsigned char *)(((unsigned long)raw + 0xFFFu) & ~0xFFFuL);
    for (i = 0; i < VNET_QAREA; i++) page[i] = 0;
    pfn = (unsigned long)page >> 12;
    vnet_outl(vnet_io + 0x08, (unsigned)pfn);
    if (qsel == VNET_Q_RX) {
        vnet_rx_page = page;
        vnet_rx_used = page + VNET_USED_OFF;
        vnet_rx_qnum = qmax;
    } else {
        vnet_tx_page = page;
        vnet_tx_used = page + VNET_USED_OFF;
        vnet_tx_qnum = qmax;
    }
    return qmax;
}

/** Docstring: Write one descriptor into the given queue area. */
static void vnet_desc(unsigned char *page, unsigned idx, unsigned long addr,
        unsigned len, unsigned short flags, unsigned short next) {
    unsigned char *d = page + idx * VNET_DESC_SZ;
    unsigned i;
    for (i = 0; i < 8; i++)
        d[i] = (unsigned char)((addr >> (i * 8)) & 0xFFu);
    d[8] = (unsigned char)(len & 0xFFu);
    d[9] = (unsigned char)((len >> 8) & 0xFFu);
    d[10] = (unsigned char)((len >> 16) & 0xFFu);
    d[11] = (unsigned char)((len >> 24) & 0xFFu);
    d[12] = (unsigned char)(flags & 0xFFu);
    d[13] = (unsigned char)((flags >> 8) & 0xFFu);
    d[14] = (unsigned char)(next & 0xFFu);
    d[15] = (unsigned char)((next >> 8) & 0xFFu);
}

/** Docstring: Push one head descriptor index onto a queue avail ring. */
static void vnet_avail_push(unsigned char *page, unsigned qnum,
        unsigned short head) {
    unsigned char *a = page + VNET_AVAIL_OFF;
    unsigned short idx = (unsigned short)(a[2] | (a[3] << 8));
    unsigned off = 4u + (unsigned)(idx % (unsigned short)qnum) * 2u;
    a[off] = (unsigned char)(head & 0xFFu);
    a[off + 1] = (unsigned char)((head >> 8) & 0xFFu);
    idx++;
    a[2] = (unsigned char)(idx & 0xFFu);
    a[3] = (unsigned char)((idx >> 8) & 0xFFu);
}

/** Docstring: Read the used-ring index of a queue area. */
static unsigned short vnet_used_idx(unsigned char *used) {
    return (unsigned short)(used[2] | (used[3] << 8));
}

/** Docstring: Probe PCI for a virtio-net device and bring queue 0 (RX)
 * and queue 1 (TX) up. Idempotent: a second call reuses the live
 * queues. Returns 1 when the device is ready, 0 when absent or
 * unusable (fail-closed, rtl8139 stays). */
int vnet_init(void) {
    int dev;
    unsigned bar0;
    unsigned i;
    if (vnet_on) return 1;
    dev = pci_find(VNET_VENDOR, VNET_DEV_LEGACY, vnet_inl, vnet_outl);
    if (dev < 0)
        dev = pci_find(VNET_VENDOR, VNET_DEV_TRANS, vnet_inl, vnet_outl);
    if (dev < 0) return 0;
    bar0 = pci_cfg_read(0, (unsigned)dev, 0, 0x10, vnet_outl, vnet_inl);
    if (!(bar0 & 1u)) return 0;
    vnet_io = (unsigned short)(bar0 & ~3u);
    if (!vnet_io) return 0;
    vnet_outb(vnet_io + 0x12, 0);
    vnet_outb(vnet_io + 0x12, VNET_F_ACK | VNET_F_DRIVER);
    vnet_outl(vnet_io + 0x04, 0);
    vnet_outb(vnet_io + 0x12, VNET_F_ACK | VNET_F_DRIVER | VNET_F_OK);
    if (!(vnet_inb(vnet_io + 0x12) & VNET_F_OK)) return 0;
    if (!vnet_queue_up(VNET_Q_RX)) return 0;
    if (!vnet_queue_up(VNET_Q_TX)) return 0;
    vnet_rx_bufs = kmalloc(VNET_RX_BUFS * VNET_RX_SIZE);
    if (!vnet_rx_bufs) return 0;
    for (i = 0; i < 6; i++)
        vnet_mac[i] = vnet_inb((unsigned short)(vnet_io + VNET_CFG_MAC + i));
    vnet_tx_stage = kmalloc(VNET_TX_SIZE);
    if (!vnet_tx_stage) return 0;
    for (i = 0; i < VNET_RX_BUFS; i++) {
        vnet_desc(vnet_rx_page, i,
            (unsigned long)(vnet_rx_bufs + i * VNET_RX_SIZE),
            VNET_RX_SIZE, VNET_DESC_WRITE, 0u);
        vnet_avail_push(vnet_rx_page, vnet_rx_qnum, (unsigned short)i);
    }
    vnet_outb(vnet_io + 0x12,
        VNET_F_ACK | VNET_F_DRIVER | VNET_F_OK | VNET_F_DRIVER_OK);
    vnet_rx_last = 0;
    vnet_tx_last = 0;
    vnet_on = 1;
    return 1;
}

/** Docstring: True once vnet_init brought the queues up. */
int vnet_present(void) {
    return vnet_on;
}

/** Docstring: Copy the NIC MAC into out (NET_ETH_ALEN bytes). */
void vnet_get_mac(unsigned char out[6]) {
    unsigned i;
    for (i = 0; i < 6; i++) out[i] = vnet_mac[i];
}

/** Docstring: The NIC I/O base, or 0 when the device is absent. */
unsigned short vnet_iobase(void) {
    return vnet_io;
}

/** Docstring: Frame-level TX/RX counters. */
void vnet_counters(unsigned int *tx_frames, unsigned int *rx_frames) {
    if (tx_frames) *tx_frames = vnet_tx_packets;
    if (rx_frames) *rx_frames = vnet_rx_packets;
}

/** Docstring: Transmit one raw Ethernet frame. Single head descriptor
 * reused every call (one in flight at a time, same discipline as the
 * block sibling): the 10-byte header plus the frame stage through
 * one heap buffer, the device reports completion on the TX used
 * ring, and the poll is deadline-bounded, fail-closed past it. */
int vnet_send(const unsigned char *frame, unsigned len) {
    unsigned long deadline;
    unsigned orig;
    unsigned i;
    if (!vnet_on || !frame) return 0;
    if (len > VNET_MAX_FRAME) return 0;
    orig = len;
    if (len < VNET_MIN_FRAME) len = VNET_MIN_FRAME;
    if (VNET_HDR_LEN + len > VNET_TX_SIZE) return 0;
    for (i = 0; i < VNET_HDR_LEN; i++) vnet_tx_stage[i] = 0;
    for (i = 0; i < orig; i++) vnet_tx_stage[VNET_HDR_LEN + i] = frame[i];
    for (i = orig; i < len; i++) vnet_tx_stage[VNET_HDR_LEN + i] = 0;
    vnet_desc(vnet_tx_page, 0, (unsigned long)vnet_tx_stage,
        VNET_HDR_LEN + len, 0u, 0u);
    vnet_avail_push(vnet_tx_page, vnet_tx_qnum, 0u);
    vnet_outw(vnet_io + 0x10, (unsigned short)VNET_Q_TX);
    deadline = ktime_ms() + VNET_TMO_MS;
    while (vnet_used_idx(vnet_tx_used) == vnet_tx_last) {
        if (ktime_ms() > deadline) return 0;
        __asm__ volatile("pause");
    }
    vnet_tx_last = vnet_used_idx(vnet_tx_used);
    (void)vnet_inb(vnet_io + 0x13);
    vnet_tx_packets++;
    return 1;
}

/** Docstring: Link-up status from the config space. */
int vnet_link_up(void) {
    if (!vnet_on) return 0;
    return (vnet_inw((unsigned short)(vnet_io + VNET_CFG_STATUS)) &
        VNET_ST_LINK_UP) != 0;
}

/** Docstring: Drain completed RX buffers into net_rx_handle_frame,
 * reposting every descriptor. The 10-byte device header is skipped;
 * frames outside 14..1514 payload bytes are dropped and counted,
 * exactly like the rtl8139 path. Bounded per call, never blocks. */
void vnet_poll(void) {
    unsigned n = 0;
    if (!vnet_on) return;
    while (vnet_used_idx(vnet_rx_used) != vnet_rx_last && n < VNET_POLL_MAX) {
        unsigned at = (unsigned)(vnet_rx_last % (unsigned short)vnet_rx_qnum);
        unsigned char *e = vnet_rx_used + 4u + at * 8u;
        unsigned id = (unsigned)(e[0] | (e[1] << 8) | (e[2] << 16) | (e[3] << 24));
        unsigned len = (unsigned)(e[4] | (e[5] << 8) | (e[6] << 16) | (e[7] << 24));
        vnet_rx_last++;
        n++;
        if (id >= VNET_RX_BUFS) {
            net_rx_dropped++;
            continue;
        }
        if (len < VNET_HDR_LEN + 14u || len > VNET_HDR_LEN + VNET_MAX_FRAME) {
            net_rx_dropped++;
        } else {
            unsigned char *buf = vnet_rx_bufs + id * VNET_RX_SIZE;
            vnet_rx_packets++;
            net_rx_handle_frame(buf + VNET_HDR_LEN, len - VNET_HDR_LEN);
        }
        vnet_desc(vnet_rx_page, id,
            (unsigned long)(vnet_rx_bufs + id * VNET_RX_SIZE),
            VNET_RX_SIZE, VNET_DESC_WRITE, 0u);
        vnet_avail_push(vnet_rx_page, vnet_rx_qnum, (unsigned short)id);
    }
    (void)vnet_inb(vnet_io + 0x13);
}
