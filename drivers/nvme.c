#include "kernel.h"
#include "drivers/pci.h"
#include "drivers/nvme.h"
#include "arch/x86/hal_io.h"

#define NVME_CLASS_BASE 0x01u
#define NVME_CLASS_SUB 0x08u
#define NVME_CLASS_PI 0x02u

#define NVME_REG_VS 0x08u
#define NVME_REG_CAP 0x00u
#define NVME_REG_CC 0x14u
#define NVME_REG_CSTS 0x1Cu
#define NVME_REG_AQA 0x24u
#define NVME_REG_ASQ 0x28u
#define NVME_REG_ACQ 0x30u
#define NVME_DB_BASE 0x1000u

#define NVME_CC_EN 1u
#define NVME_CC_IOSQES 6u
#define NVME_CC_IOCQES 4u
#define NVME_CSTS_RDY 1u

#define NVME_QSIZE 16u
#define NVME_SQE_LEN 64u
#define NVME_CQE_LEN 16u
#define NVME_QPAGES 7u

#define NVME_OPC_CREATE_IOSQ 0x01u
#define NVME_OPC_READ 0x02u
#define NVME_OPC_CREATE_IOCQ 0x05u
#define NVME_OPC_IDENTIFY 0x06u
#define NVME_NSID 1u
#define NVME_CNS_NS 0u
#define NVME_LBADS_512 9u

#define NVME_MAX_SECTORS 16u
#define NVME_SECTOR 512u
#define NVME_TMO_MS 5000u

static int xnv_on;
static volatile unsigned char *xnv_mmio;
static unsigned long xnv_mapped;
static unsigned long long xnv_bar;
static unsigned xnv_version;
static const char *xnv_note = "not probed";

static void xnv_outl(unsigned short port, unsigned val) {
    __asm__ volatile("outl %0, %1" : : "a"(val), "Nd"(port));
}

static unsigned xnv_inl(unsigned short port) {
    unsigned v;
    __asm__ volatile("inl %1, %0" : "=a"(v) : "Nd"(port));
    return v;
}

int nvme_present(void) {
    return xnv_on;
}

unsigned nvme_version(void) {
    return xnv_version;
}

const char *nvme_note(void) {
    return xnv_note;
}

static unsigned char *xnv_raw;
static unsigned char *xnv_asq;
static unsigned char *xnv_acq;
static unsigned char *xnv_sq;
static unsigned char *xnv_cq;
static unsigned char *xnv_id;
static unsigned char *xnv_stage;
static unsigned long xnv_nsze;
static unsigned xnv_stride;
static unsigned short xnv_atail;
static unsigned short xnv_ahead;
static unsigned short xnv_aphase;
static unsigned short xnv_stail;
static unsigned short xnv_shead;
static unsigned short xnv_sphase;
static unsigned short xnv_cid;
static unsigned long xnv_last_dw3;
static int xnv_last_tmo;

static unsigned xnv_r32(unsigned off) {
    return hal_mmio_read32((const volatile unsigned *)(xnv_mmio + off));
}

static void xnv_w32(unsigned off, unsigned val) {
    hal_mmio_write32((volatile unsigned *)(xnv_mmio + off), val);
}

static unsigned long long xnv_r64(unsigned off) {
    return hal_mmio_read64(
        (const volatile unsigned long long *)(xnv_mmio + off));
}

static void xnv_w64(unsigned off, unsigned long long val) {
    hal_mmio_write64((volatile unsigned long long *)(xnv_mmio + off), val);
}

static void xnv_put16(unsigned char *p, unsigned short v) {
    p[0] = (unsigned char)(v & 0xFFu);
    p[1] = (unsigned char)((v >> 8) & 0xFFu);
}

static void xnv_put32(unsigned char *p, unsigned long v) {
    p[0] = (unsigned char)(v & 0xFFu);
    p[1] = (unsigned char)((v >> 8) & 0xFFu);
    p[2] = (unsigned char)((v >> 16) & 0xFFu);
    p[3] = (unsigned char)((v >> 24) & 0xFFu);
}

static void xnv_put64(unsigned char *p, unsigned long long v) {
    unsigned i;
    for (i = 0; i < 8; i++)
        p[i] = (unsigned char)((v >> (i * 8)) & 0xFFu);
}

static unsigned long xnv_get32(const unsigned char *p) {
    return (unsigned long)p[0] | ((unsigned long)p[1] << 8) |
           ((unsigned long)p[2] << 16) | ((unsigned long)p[3] << 24);
}

static int xnv_wait_rdy(unsigned want) {
    unsigned long deadline = ktime_ms() + NVME_TMO_MS;
    for (;;) {
        unsigned csts = xnv_r32(NVME_REG_CSTS);
        if (((csts & NVME_CSTS_RDY) != 0) == (want != 0)) return 1;
        if ((long)(ktime_ms() - deadline) >= 0) return 0;
        __asm__ volatile("pause");
    }
}

static unsigned short xnv_next_cid(void) {
    xnv_cid++;
    if (xnv_cid == 0 || xnv_cid == 0xFFFFu) xnv_cid = 1;
    return xnv_cid;
}

static int xnv_poll(unsigned char *cq, unsigned cq_db, unsigned short *head,
        unsigned short *phase, unsigned short want_cid) {
    unsigned long deadline = ktime_ms() + NVME_TMO_MS;
    for (;;) {
        unsigned char *e = cq + (unsigned)(*head) * NVME_CQE_LEN;
        unsigned long dw3 = xnv_get32(e + 12);
        if (((dw3 >> 16) & 1u) == (unsigned long)*phase) {
            unsigned short cid = (unsigned short)(dw3 & 0xFFFFu);
            int ok = (dw3 >> 17) == 0 && cid == want_cid;
            xnv_last_dw3 = dw3;
            xnv_last_tmo = 0;
            *head = (unsigned short)(((unsigned)*head + 1) % NVME_QSIZE);
            if (*head == 0) *phase ^= 1u;
            xnv_w32(cq_db, (unsigned)*head);
            return ok;
        }
        if ((long)(ktime_ms() - deadline) >= 0) {
            xnv_last_tmo = 1;
            return 0;
        }
        __asm__ volatile("pause");
    }
}

static int xnv_cmd(unsigned char *sq, unsigned sq_db, unsigned char *cq,
        unsigned cq_db, unsigned short *tail, unsigned short *head,
        unsigned short *phase, unsigned opc, unsigned nsid,
        unsigned cdw10, unsigned cdw11, unsigned cdw12,
        unsigned long long prp1, unsigned long long prp2) {
    unsigned char cmd[NVME_SQE_LEN];
    unsigned short cid;
    unsigned i;
    for (i = 0; i < NVME_SQE_LEN; i++) cmd[i] = 0;
    cmd[0] = (unsigned char)opc;
    cid = xnv_next_cid();
    xnv_put16(cmd + 2, cid);
    xnv_put32(cmd + 4, nsid);
    xnv_put32(cmd + 8, 0u);
    xnv_put32(cmd + 12, 0u);
    xnv_put64(cmd + 24, prp1);
    xnv_put64(cmd + 32, prp2);
    xnv_put32(cmd + 40, cdw10);
    xnv_put32(cmd + 44, cdw11);
    xnv_put32(cmd + 48, cdw12);
    for (i = 0; i < NVME_SQE_LEN; i++)
        sq[(unsigned)(*tail) * NVME_SQE_LEN + i] = cmd[i];
    *tail = (unsigned short)(((unsigned)*tail + 1) % NVME_QSIZE);
    xnv_w32(sq_db, (unsigned)*tail);
    return xnv_poll(cq, cq_db, head, phase, cid);
}

static int xnv_queues(void) {
    unsigned long long cap;
    unsigned mqes;
    unsigned char *chunk;
    unsigned i;
    unsigned long long id_pa;
    unsigned long long nsze;
    unsigned char flbas;
    unsigned char lbads;
    cap = xnv_r64(NVME_REG_CAP);
    mqes = (unsigned)(cap & 0xFFFFu);
    xnv_stride = 4u << (unsigned)((cap >> 32) & 0xFu);
    if (mqes < NVME_QSIZE - 1) {
        xnv_note = "CAP.MQES below the 16-entry queues";
        return 0;
    }
    if (xnv_r32(NVME_REG_CSTS) & NVME_CSTS_RDY) {
        xnv_w32(NVME_REG_CC, xnv_r32(NVME_REG_CC) & ~NVME_CC_EN);
        if (!xnv_wait_rdy(0)) {
            xnv_note = "controller never quiesced, refusing to steal it";
            return 0;
        }
    }
    xnv_raw = kmalloc(NVME_QPAGES * 4096u + 0xFFFu);
    if (!xnv_raw) {
        xnv_note = "out of memory for queues";
        return 0;
    }
    chunk = (unsigned char *)(((unsigned long)xnv_raw + 0xFFFu) & ~0xFFFuL);
    for (i = 0; i < NVME_QPAGES * 4096u; i++) chunk[i] = 0;
    xnv_asq = chunk;
    xnv_acq = chunk + 4096u;
    xnv_sq = chunk + 8192u;
    xnv_cq = chunk + 12288u;
    xnv_id = chunk + 16384u;
    xnv_stage = chunk + 20480u;
    xnv_w32(NVME_REG_AQA, ((NVME_QSIZE - 1) << 16) | (NVME_QSIZE - 1));
    xnv_w64(NVME_REG_ASQ, (unsigned long)xnv_asq);
    xnv_w64(NVME_REG_ACQ, (unsigned long)xnv_acq);
    xnv_w32(NVME_REG_CC, NVME_CC_EN | (NVME_CC_IOSQES << 16) |
             (NVME_CC_IOCQES << 20));
    if (!xnv_wait_rdy(1)) {
        xnv_note = "CSTS.RDY never asserted past the deadline";
        return 0;
    }
    xnv_atail = 0;
    xnv_ahead = 0;
    xnv_aphase = 1;
    id_pa = (unsigned long)xnv_id;
    if (!xnv_cmd(xnv_asq, NVME_DB_BASE, xnv_acq, NVME_DB_BASE + xnv_stride,
                 &xnv_atail, &xnv_ahead, &xnv_aphase, NVME_OPC_IDENTIFY,
                 NVME_NSID, NVME_CNS_NS, 0u, 0u, id_pa, 0u)) {
        xnv_note = "Identify namespace failed";
        return 0;
    }
    nsze = 0;
    for (i = 0; i < 8; i++)
        nsze |= (unsigned long)xnv_id[i] << (i * 8);
    flbas = xnv_id[26];
    lbads = xnv_id[128 + (unsigned)(flbas & 0xFu) * 4u + 2u];
    if (lbads != NVME_LBADS_512) {
        xnv_note = "namespace LBA format is not 512 bytes";
        return 0;
    }
    if (nsze == 0) {
        xnv_note = "namespace reports zero sectors";
        return 0;
    }
    if (!xnv_cmd(xnv_asq, NVME_DB_BASE, xnv_acq, NVME_DB_BASE + xnv_stride,
                 &xnv_atail, &xnv_ahead, &xnv_aphase, NVME_OPC_CREATE_IOCQ,
                 0u, ((NVME_QSIZE - 1) << 16) | 1u, 1u, 0u,
                 (unsigned long)xnv_cq, 0u)) {
        xnv_note = "Create IOCQ failed";
        kprintf("nvme: dbg dw3=0x%lx tmo=%d\n", xnv_last_dw3, xnv_last_tmo);
        return 0;
    }
    if (!xnv_cmd(xnv_asq, NVME_DB_BASE, xnv_acq, NVME_DB_BASE + xnv_stride,
                 &xnv_atail, &xnv_ahead, &xnv_aphase, NVME_OPC_CREATE_IOSQ,
                 0u, ((NVME_QSIZE - 1) << 16) | 1u, (1u << 16) | 1u, 0u,
                 (unsigned long)xnv_sq, 0u)) {
        xnv_note = "Create IOSQ failed";
        return 0;
    }
    xnv_stail = 0;
    xnv_shead = 0;
    xnv_sphase = 1;
    xnv_nsze = nsze;
    return 1;
}

unsigned long nvme_sectors(void) {
    return xnv_on ? xnv_nsze : 0u;
}

int nvme_read_sectors(unsigned lba, unsigned count, void *buf) {
    unsigned long bytes;
    unsigned long long p1;
    unsigned long long p2;
    unsigned i;
    if (!xnv_on || !buf) return -1;
    if (count == 0 || count > NVME_MAX_SECTORS) return -1;
    if (lba >= xnv_nsze || count > xnv_nsze - lba) return -1;
    bytes = (unsigned long)count * NVME_SECTOR;
    p1 = (unsigned long)xnv_stage;
    p2 = bytes > 4096u ? (unsigned long)(xnv_stage + 4096u) : 0u;
    if (!xnv_cmd(xnv_sq, NVME_DB_BASE + 2u * xnv_stride, xnv_cq,
                 NVME_DB_BASE + 3u * xnv_stride, &xnv_stail, &xnv_shead,
                 &xnv_sphase, NVME_OPC_READ, NVME_NSID, lba, 0u, count - 1u,
                 p1, p2)) return -1;
    for (i = 0; i < bytes; i++)
        ((unsigned char *)buf)[i] = xnv_stage[i];
    return 0;
}

int nvme_init(void) {
    pci_bdf_t bdf;
    unsigned orig_cmd;
    unsigned orig_bar;
    unsigned orig_hi;
    unsigned long long size;
    unsigned long long bar_base;
    unsigned long mapped;
    unsigned vs;
    if (xnv_on) return 1;
    xnv_note = "no NVMe controller in PCI class 01:08:02";
    if (!pci_find_class(&bdf, NVME_CLASS_BASE, NVME_CLASS_SUB, NVME_CLASS_PI,
                        xnv_outl, xnv_inl)) return 0;
    orig_cmd = pci_cfg_read(bdf.bus, bdf.dev, bdf.func, PCI_REG_COMMAND,
                            xnv_outl, xnv_inl);
    pci_cfg_write(bdf.bus, bdf.dev, bdf.func, PCI_REG_COMMAND,
                  orig_cmd & ~(PCI_COMMAND_MEMORY | PCI_COMMAND_BUS_MASTER),
                  xnv_outl);
    orig_bar = pci_cfg_read(bdf.bus, bdf.dev, bdf.func, PCI_REG_BAR0,
                            xnv_outl, xnv_inl);
    orig_hi = pci_cfg_read(bdf.bus, bdf.dev, bdf.func, PCI_REG_BAR0 + 4u,
                           xnv_outl, xnv_inl);
    if (pci_bar_is_io(bdf.bus, bdf.dev, bdf.func, 0, xnv_outl, xnv_inl)) {
        xnv_note = "BAR0 is an I/O range, not memory";
        pci_cfg_write(bdf.bus, bdf.dev, bdf.func, PCI_REG_COMMAND, orig_cmd,
                      xnv_outl);
        return 0;
    }
    size = pci_bar_size(bdf.bus, bdf.dev, bdf.func, 0, xnv_outl, xnv_inl);
    bar_base = pci_bar_base(bdf.bus, bdf.dev, bdf.func, 0, xnv_outl, xnv_inl);
    if (size == 0 || size > (unsigned long long)PCI_MMIO_SIZE ||
            bar_base == 0) {
        xnv_note = "BAR0 is not a memory BAR of a usable size";
        pci_bar_restore(bdf.bus, bdf.dev, bdf.func, 0, orig_bar, orig_hi,
                        xnv_outl);
        pci_cfg_write(bdf.bus, bdf.dev, bdf.func, PCI_REG_COMMAND, orig_cmd,
                      xnv_outl);
        return 0;
    }
    pci_cfg_write(bdf.bus, bdf.dev, bdf.func, PCI_REG_COMMAND,
                  orig_cmd | PCI_COMMAND_MEMORY | PCI_COMMAND_BUS_MASTER,
                  xnv_outl);
    if (xnv_mapped && bar_base == xnv_bar) {
        mapped = xnv_mapped;
    } else {
        mapped = kmm_map_device((unsigned long)bar_base,
                                (unsigned long)size);
        if (!mapped) {
            xnv_note = "uncached mapping of the BAR refused";
            pci_bar_restore(bdf.bus, bdf.dev, bdf.func, 0, orig_bar, orig_hi,
                            xnv_outl);
            pci_cfg_write(bdf.bus, bdf.dev, bdf.func, PCI_REG_COMMAND,
                          orig_cmd, xnv_outl);
            return 0;
        }
        xnv_mapped = mapped;
        xnv_bar = bar_base;
    }
    xnv_mmio = (volatile unsigned char *)mapped;
    vs = hal_mmio_read32((const volatile unsigned *)(xnv_mmio + NVME_REG_VS));
    if (vs == 0) {
        xnv_note = "VS reports 0.0, refusing unspecified hardware";
        xnv_mmio = 0;
        pci_bar_restore(bdf.bus, bdf.dev, bdf.func, 0, orig_bar, orig_hi,
                        xnv_outl);
        pci_cfg_write(bdf.bus, bdf.dev, bdf.func, PCI_REG_COMMAND, orig_cmd,
                      xnv_outl);
        return 0;
    }
    xnv_version = vs;
    if (!xnv_queues()) {
        xnv_mmio = 0;
        pci_bar_restore(bdf.bus, bdf.dev, bdf.func, 0, orig_bar, orig_hi,
                        xnv_outl);
        pci_cfg_write(bdf.bus, bdf.dev, bdf.func, PCI_REG_COMMAND, orig_cmd,
                      xnv_outl);
        return 0;
    }
    xnv_on = 1;
    xnv_note = "queues ok, read-only";
    return 1;
}
