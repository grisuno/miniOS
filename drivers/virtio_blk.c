/** Docstring: drivers/virtio_blk.c -- Polled legacy virtio-blk driver.
 *
 * A virtio-blk device (QEMU -device virtio-blk-pci) behind the same
 * sector contract as the IDE driver, so the block layer can prefer
 * it with zero MiniFS changes: same 512-byte sectors, same LBA
 * addressing, same image bytes. Legacy (0.9.5) interface over the
 * BAR0 I/O ports: no MSI-X, no interrupts, completion by polling
 * the used ring with a deadline, exactly like the rtl8139 no-IRQ
 * discipline. Fail-closed throughout: absent device, feature
 * mismatch, queue refusal, descriptor exhaustion and completion
 * timeouts all refuse with -1 and leave no half-armed queue.
 *
 * DMA addressing: every heap and user page in this kernel is
 * identity-mapped (VA == PA: heap, pt_page_alloc pools and all
 * isolated user windows are heap pages), so caller buffers and the
 * vring pages serve as guest-physical addresses directly. Kernel
 * statics and the stack do NOT qualify (KASLR slides the image, so
 * their VA != PA): the request header and status byte are heap
 * objects for exactly this reason. The only non-identity user
 * mappings are the shared graphics slots, which never reach the
 * block layer. */

#include "kernel.h"
#include "drivers/pci.h"
#include "drivers/virtio_blk.h"

#define VBLK_VENDOR 0x1AF4u
#define VBLK_DEV_LEGACY 0x1001u
#define VBLK_DEV_TRANS 0x1042u

#define VBLK_F_ACK 1u
#define VBLK_F_DRIVER 2u
#define VBLK_F_OK 8u
#define VBLK_F_DRIVER_OK 4u

#define VBLK_QNUM 256u
#define VBLK_DESC_SZ 16u
/* Three-page queue for qnum <= 256: descriptors fill page 0
 * (256 x 16 = 4096), the avail ring opens page 1, the used ring
 * opens page 2. The device derives both from QueuePFN, so the area
 * must be contiguous and page-aligned (one 12 KB heap slice). */
#define VBLK_AVAIL_OFF 4096u
#define VBLK_USED_OFF 8192u
#define VBLK_QAREA 12288u

#define VBLK_DESC_NEXT 1u
#define VBLK_DESC_WRITE 2u

#define VBLK_REQ_IN 0u
#define VBLK_REQ_OUT 1u

#define VBLK_TMO_MS 5000u
#define VBLK_SECTOR 512u

typedef struct {
    unsigned type;
    unsigned reserved;
    unsigned long sector;
} vblk_req_t;

static unsigned short vblk_iobase;
static int vblk_on;
static unsigned long vblk_capacity;
static unsigned char *vblk_qraw;
static unsigned char *vblk_qpage;
static unsigned char *vblk_used;
static unsigned vblk_qnum;
static unsigned short vblk_last_used;

static void vblk_outl(unsigned short port, unsigned val) {
    __asm__ volatile("outl %0, %1" : : "a"(val), "Nd"(port));
}

static unsigned vblk_inl(unsigned short port) {
    unsigned v;
    __asm__ volatile("inl %1, %0" : "=a"(v) : "Nd"(port));
    return v;
}

static void vblk_outb(unsigned short port, unsigned char val) {
    outb(port, val);
}

static unsigned char vblk_inb(unsigned short port) {
    return inb(port);
}

static unsigned short vblk_inw(unsigned short port) {
    return inw(port);
}

static void vblk_outw(unsigned short port, unsigned short val) {
    outw(port, val);
}

/** Docstring: Probe PCI for a virtio-blk device and bring queue 0 up.
 * Idempotent: a second call reuses the live queue. Returns 1 when the
 * device is ready, 0 when absent or unusable (fail-closed, IDE stays). */
int vblk_init(void) {
    int dev;
    unsigned bar0;
    unsigned hostf;
    unsigned qmax;
    if (vblk_on) return 1;
    dev = pci_find(VBLK_VENDOR, VBLK_DEV_LEGACY, vblk_inl, vblk_outl);
    if (dev < 0)
        dev = pci_find(VBLK_VENDOR, VBLK_DEV_TRANS, vblk_inl, vblk_outl);
    if (dev < 0) return 0;
    bar0 = pci_cfg_read(0, (unsigned)dev, 0, 0x10, vblk_outl, vblk_inl);
    if (!(bar0 & 1u)) return 0;
    vblk_iobase = (unsigned short)(bar0 & ~3u);
    if (!vblk_iobase) return 0;
    vblk_outb(vblk_iobase + 0x12, 0);
    vblk_outb(vblk_iobase + 0x12, VBLK_F_ACK | VBLK_F_DRIVER);
    hostf = vblk_inl(vblk_iobase + 0x00);
    (void)hostf;
    vblk_outl(vblk_iobase + 0x04, 0);
    vblk_outb(vblk_iobase + 0x12, VBLK_F_ACK | VBLK_F_DRIVER | VBLK_F_OK);
    if (!(vblk_inb(vblk_iobase + 0x12) & VBLK_F_OK)) return 0;
    vblk_outw(vblk_iobase + 0x0E, 0);
    qmax = vblk_inw(vblk_iobase + 0x0C);
    if (qmax < 4u || qmax > 1024u) return 0;
    vblk_qnum = qmax < VBLK_QNUM ? qmax : VBLK_QNUM;
    /* The queue size defaults to 0 after reset: tell the device how
     * many descriptors this queue offers, or it processes nothing. */
    vblk_outw(vblk_iobase + 0x0C, (unsigned short)vblk_qnum);
    /* One 12 KB area, page-aligned: descriptors in page 0 (up to
     * 256 x 16), avail ring in page 1, used ring in page 2. Legacy
     * virtio derives avail/used from QueuePFN, so independent pages
     * do NOT work even when adjacent in the heap. Kept for the
     * machine's life, never freed (probe-once device). */
    vblk_qraw = kmalloc(VBLK_QAREA + 0xFFFu);
    if (!vblk_qraw) return 0;
    vblk_qpage = (unsigned char *)(((unsigned long)vblk_qraw + 0xFFFu) & ~0xFFFuL);
    vblk_used = vblk_qpage + VBLK_USED_OFF;
    {
        unsigned long pfn = (unsigned long)vblk_qpage >> 12;
        unsigned i;
        for (i = 0; i < VBLK_QAREA; i++)
            vblk_qpage[i] = 0;
        vblk_outl(vblk_iobase + 0x08, (unsigned)pfn);
    }
    {
        unsigned long cap_lo = vblk_inl(vblk_iobase + 0x14);
        unsigned long cap_hi = vblk_inl(vblk_iobase + 0x18);
        (void)cap_hi;
        vblk_capacity = cap_lo;
    }
    vblk_outb(vblk_iobase + 0x12,
        VBLK_F_ACK | VBLK_F_DRIVER | VBLK_F_OK | VBLK_F_DRIVER_OK);
    vblk_last_used = 0;
    vblk_on = 1;
    return 1;
}

/** Docstring: True once vblk_init brought the queue up. */
int vblk_present(void) {
    return vblk_on;
}

/** Docstring: Device capacity in 512-byte sectors (0 when absent). */
unsigned long vblk_sectors(void) {
    return vblk_on ? vblk_capacity : 0u;
}

static void vblk_desc(unsigned idx, unsigned long addr, unsigned len,
        unsigned short flags, unsigned short next) {
    unsigned char *d = vblk_qpage + idx * VBLK_DESC_SZ;
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

static unsigned short vblk_avail_idx(void) {
    unsigned char *a = vblk_qpage + VBLK_AVAIL_OFF;
    return (unsigned short)(a[2] | (a[3] << 8));
}

static void vblk_avail_push(unsigned short head) {
    unsigned char *a = vblk_qpage + VBLK_AVAIL_OFF;
    unsigned short idx = vblk_avail_idx();
    unsigned off = 4u + (unsigned)(idx % (unsigned short)vblk_qnum) * 2u;
    a[off] = (unsigned char)(head & 0xFFu);
    a[off + 1] = (unsigned char)((head >> 8) & 0xFFu);
    idx++;
    a[2] = (unsigned char)(idx & 0xFFu);
    a[3] = (unsigned char)((idx >> 8) & 0xFFu);
}

static unsigned short vblk_used_idx(void) {
    return (unsigned short)(vblk_used[2] | (vblk_used[3] << 8));
}

/** Docstring: One synchronous request. dir 0 reads sectors into buf,
 * 1 writes them out. Single head descriptor reused every call (one
 * in flight at a time: the shell and the block cache never overlap
 * device access on one CPU, and SMP callers serialize on fs_lock
 * upstream). The header and status byte live in the heap alongside
 * the queue: stale statics would sit in the KASLR-slid image where
 * VA != PA, and the device would DMA to the wrong RAM while the
 * guest polls a status byte that never changes. Bounded poll,
 * fail-closed past the deadline. */
static int vblk_request(unsigned dir, unsigned long sector,
        unsigned char *buf, unsigned count) {
    static vblk_req_t *req;
    static unsigned char *statusp;
    unsigned long deadline;
    if (!req) {
        req = kmalloc(sizeof(vblk_req_t));
        statusp = kmalloc(1u);
        if (!req || !statusp) return -1;
    }
    if (!vblk_on || !buf || count == 0u || count > 16u) return -1;
    if (sector + count > vblk_capacity) return -1;
    req->type = dir;
    req->reserved = 0;
    req->sector = sector;
    *statusp = 0xFF;
    vblk_desc(0, (unsigned long)req, 16u, VBLK_DESC_NEXT, 1u);
    vblk_desc(1, (unsigned long)buf, count * VBLK_SECTOR,
        (unsigned short)(VBLK_DESC_NEXT | (dir == 0u ? VBLK_DESC_WRITE : 0u)), 2u);
    vblk_desc(2, (unsigned long)statusp, 1u, VBLK_DESC_WRITE, 0u);
    vblk_avail_push(0u);
    vblk_outw(vblk_iobase + 0x10, 0u);
    deadline = ktime_ms() + VBLK_TMO_MS;
    while (vblk_used_idx() == vblk_last_used) {
        if (ktime_ms() > deadline) return -1;
        __asm__ volatile("pause");
    }
    vblk_last_used = vblk_used_idx();
    (void)vblk_inb(vblk_iobase + 0x13);
    if (*statusp != 0) return -1;
    return 0;
}

/** Docstring: Read count sectors from lba into buf. Same contract as
 * ide_read_sectors, so the block layer can prefer this device. */
int vblk_read_sectors(unsigned lba, unsigned count, void *buf) {
    if (!buf) return -1;
    return vblk_request(VBLK_REQ_IN, lba, (unsigned char *)buf, count);
}

/** Docstring: Write count sectors from buf at lba. The caller buffer
 * is DMA-safe by construction (identity-mapped heap/user pages), so
 * it is handed to the device directly, never bounced. */
int vblk_write_sectors(unsigned lba, unsigned count, const void *buf) {
    if (!buf) return -1;
    return vblk_request(VBLK_REQ_OUT, lba, (unsigned char *)buf, count);
}
