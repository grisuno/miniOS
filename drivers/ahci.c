/** Docstring: drivers/ahci.c -- Polled AHCI (SATA) disk driver.
 *
 * Real machines expose their SATA ports through an AHCI host bus adapter
 * (PCI class 01:06:01, registers behind BAR5 "ABAR"), and UEFI-era firmware
 * rarely offers the legacy IDE mode drivers/ide.c needs. This driver is the
 * block backend for that hardware:
 *
 * - Locate the HBA by class (never by vendor table), map ABAR through
 *   kmm_map_device, take ownership from firmware with the BIOS/OS handoff
 *   when CAP2.BOH advertises it, and set GHC.AE.
 * - Claim the first implemented port whose link is established
 *   (SSTS.DET=3, IPM=1) and whose signature is an ATA disk. A port with a
 *   device but no link gets one COMRESET; ATAPI and port multipliers are
 *   skipped.
 * - Stop the port engine, point it at a heap command list, received-FIS
 *   area and one command table, restart it, and run IDENTIFY DEVICE.
 *   Drives without 48-bit addressing or with logical sectors other than
 *   512 bytes are refused: the block layer addresses 512-byte LBAs.
 * - Serve reads and writes with READ/WRITE DMA EXT on command slot 0
 *   through one physically contiguous staging buffer, AHCI_MAX_SECTORS per
 *   command. A write is followed by FLUSH CACHE EXT, because a real disk
 *   acknowledges into its volatile cache.
 *
 * Every wait is bounded by a named millisecond budget against ktime_ms,
 * which is TSC based and therefore advances with interrupts masked. A task
 * file error, a timeout or an unclaimed port fails the request closed; no
 * vector, IDT entry or PIC mask is touched (completion is polled through
 * PxCI). The heap is identity mapped, so heap addresses are the bus
 * addresses the HBA receives; an address above 4 GB on an HBA without
 * CAP.S64A is refused instead of truncated. */

#include "kernel.h"
#include "driver.h"
#include "drivers/pci.h"
#include "drivers/ahci.h"
#include "arch/x86/hal_io.h"

#define AHCI_CLASS_BASE 0x01u
#define AHCI_CLASS_SUB 0x06u
#define AHCI_CLASS_PI 0x01u
#define AHCI_ABAR_INDEX 5u

#define AHCI_REG_CAP 0x00u
#define AHCI_REG_GHC 0x04u
#define AHCI_REG_IS 0x08u
#define AHCI_REG_PI 0x0Cu
#define AHCI_REG_VS 0x10u
#define AHCI_REG_CAP2 0x24u
#define AHCI_REG_BOHC 0x28u

#define AHCI_CAP_S64A 0x80000000u
#define AHCI_CAP_SSS 0x08000000u
#define AHCI_GHC_AE 0x80000000u
#define AHCI_GHC_IE 0x00000002u
#define AHCI_CAP2_BOH 0x00000001u
#define AHCI_BOHC_BOS 0x00000001u
#define AHCI_BOHC_OOS 0x00000002u
#define AHCI_BOHC_BB 0x00000010u

#define AHCI_MAX_PORTS 32u
#define AHCI_PORT_BASE 0x100u
#define AHCI_PORT_STRIDE 0x80u
#define AHCI_PX_CLB 0x00u
#define AHCI_PX_CLBU 0x04u
#define AHCI_PX_FB 0x08u
#define AHCI_PX_FBU 0x0Cu
#define AHCI_PX_IS 0x10u
#define AHCI_PX_IE 0x14u
#define AHCI_PX_CMD 0x18u
#define AHCI_PX_TFD 0x20u
#define AHCI_PX_SIG 0x24u
#define AHCI_PX_SSTS 0x28u
#define AHCI_PX_SCTL 0x2Cu
#define AHCI_PX_SERR 0x30u
#define AHCI_PX_CI 0x38u

#define AHCI_CMD_ST 0x00000001u
#define AHCI_CMD_SUD 0x00000002u
#define AHCI_CMD_POD 0x00000004u
#define AHCI_CMD_FRE 0x00000010u
#define AHCI_CMD_FR 0x00004000u
#define AHCI_CMD_CR 0x00008000u
#define AHCI_CMD_ICC_MASK 0xF0000000u
#define AHCI_CMD_ICC_ACTIVE 0x10000000u

#define AHCI_TFD_ERR 0x01u
#define AHCI_TFD_DRQ 0x08u
#define AHCI_TFD_BSY 0x80u
#define AHCI_IS_TFES 0x40000000u
#define AHCI_ALL_ONES 0xFFFFFFFFu

#define AHCI_SSTS_DET_MASK 0x0Fu
#define AHCI_SSTS_DET_PRESENT 0x01u
#define AHCI_SSTS_DET_ONLINE 0x03u
#define AHCI_SSTS_IPM_SHIFT 8u
#define AHCI_SSTS_IPM_MASK 0x0Fu
#define AHCI_SSTS_IPM_ACTIVE 0x01u
#define AHCI_SCTL_DET_MASK 0x0Fu
#define AHCI_SCTL_DET_COMRESET 0x01u

#define AHCI_SIG_ATA 0x00000101u

#define AHCI_CL_BYTES 1024u
#define AHCI_CL_ALIGN 1024u
#define AHCI_FIS_BYTES 256u
#define AHCI_FIS_ALIGN 256u
#define AHCI_CT_BYTES 256u
#define AHCI_CT_ALIGN 128u
#define AHCI_CT_PRDT_OFF 0x80u
#define AHCI_PRD_BYTES 16u
#define AHCI_CH_BYTES 32u

#define AHCI_CH_CFL_H2D 5u
#define AHCI_CH_WRITE 0x40u
#define AHCI_CH_PRDTL_SHIFT 16u
#define AHCI_PRD_DBC_MASK 0x003FFFFFu

#define AHCI_FIS_TYPE_H2D 0x27u
#define AHCI_FIS_H2D_CMD 0x80u
#define AHCI_FIS_DEV_LBA 0x40u
#define AHCI_FIS_BYTES_H2D 20u

#define ATA_CMD_IDENTIFY 0xECu
#define ATA_CMD_READ_DMA_EXT 0x25u
#define ATA_CMD_WRITE_DMA_EXT 0x35u
#define ATA_CMD_FLUSH_EXT 0xEAu

#define ATA_ID_WORDS 256u
#define ATA_ID_CMDSET2 83u
#define ATA_ID_LBA48_BIT 0x0400u
#define ATA_ID_LBA48_SECTORS 100u
#define ATA_ID_SECTOR_SIZE 106u
#define ATA_ID_SS_VALID_MASK 0xC000u
#define ATA_ID_SS_VALID 0x4000u
#define ATA_ID_SS_LONG 0x1000u

#define AHCI_SECTOR 512u
#define AHCI_MAX_SECTORS 128u
#define AHCI_STAGE_BYTES (AHCI_MAX_SECTORS * AHCI_SECTOR)
#define AHCI_STAGE_ALIGN 4096u
#define AHCI_LBA48_LIMIT 0x0001000000000000ULL
#define AHCI_DMA_LIMIT_32 0x100000000ULL

#define AHCI_TMO_HANDOFF_MS 2000u
#define AHCI_TMO_ENGINE_MS 500u
#define AHCI_TMO_LINK_MS 1000u
#define AHCI_TMO_COMRESET_HOLD_MS 2u
#define AHCI_TMO_CMD_MS 10000u

static int ahc_on;
static int ahc_probed;
static volatile unsigned char *ahc_mmio;
static volatile unsigned char *ahc_px;
static unsigned ahc_version;
static unsigned ahc_cap;
static unsigned ahc_pi;
static int ahc_portno = -1;
static unsigned long ahc_nsec;
static const char *ahc_note = "not probed";

static unsigned char *ahc_cl;
static unsigned char *ahc_fis;
static unsigned char *ahc_ct;
static unsigned char *ahc_stage;

/** Docstring: Serializes slot 0 and the staging buffer. irqsave because the
 * block cache calls in with its own irqsave lock held. */
static spinlock_t ahc_lock = SPINLOCK_INIT;

/** Docstring: Port I/O used for PCI configuration access. */
static void ahc_outl(unsigned short port, unsigned val) {
    __asm__ volatile("outl %0, %1" : : "a"(val), "Nd"(port));
}

/** Docstring: Port I/O used for PCI configuration access. */
static unsigned ahc_inl(unsigned short port) {
    unsigned v;
    __asm__ volatile("inl %1, %0" : "=a"(v) : "Nd"(port));
    return v;
}

/** Docstring: Read an HBA global register. */
static unsigned ahc_r32(unsigned off) {
    return hal_mmio_read32((const volatile unsigned *)(ahc_mmio + off));
}

/** Docstring: Write an HBA global register. */
static void ahc_w32(unsigned off, unsigned val) {
    hal_mmio_write32((volatile unsigned *)(ahc_mmio + off), val);
}

/** Docstring: Read a register of the port block at px. */
static unsigned ahc_pr32(volatile unsigned char *px, unsigned off) {
    return hal_mmio_read32((const volatile unsigned *)(px + off));
}

/** Docstring: Write a register of the port block at px. */
static void ahc_pw32(volatile unsigned char *px, unsigned off, unsigned val) {
    hal_mmio_write32((volatile unsigned *)(px + off), val);
}

/** Docstring: Little-endian 32-bit store into a DMA structure. */
static void ahc_put32(unsigned char *p, unsigned v) {
    p[0] = (unsigned char)(v & 0xFFu);
    p[1] = (unsigned char)((v >> 8) & 0xFFu);
    p[2] = (unsigned char)((v >> 16) & 0xFFu);
    p[3] = (unsigned char)((v >> 24) & 0xFFu);
}

/** Docstring: Little-endian 16-bit load of IDENTIFY word idx. */
static unsigned ahc_id_word(const unsigned char *id, unsigned idx) {
    return (unsigned)id[idx * 2u] | ((unsigned)id[idx * 2u + 1u] << 8);
}

int ahci_present(void) {
    return ahc_on;
}

unsigned ahci_version(void) {
    return ahc_version;
}

int ahci_port(void) {
    return ahc_on ? ahc_portno : -1;
}

unsigned ahci_ports_implemented(void) {
    return ahc_pi;
}

const char *ahci_note(void) {
    return ahc_note;
}

unsigned long ahci_sectors(void) {
    return ahc_on ? ahc_nsec : 0u;
}

/** Docstring: Wait until (reg & mask) == want on the port block, within
 * budget_ms. Returns 1 on success, 0 on timeout. */
static int ahc_wait_port(volatile unsigned char *px, unsigned off,
                         unsigned mask, unsigned want,
                         unsigned long budget_ms) {
    unsigned long deadline = ktime_ms() + budget_ms;
    for (;;) {
        if ((ahc_pr32(px, off) & mask) == want) return 1;
        if ((long)(ktime_ms() - deadline) >= 0) return 0;
        __asm__ volatile("pause");
    }
}

/** Docstring: Take the HBA from firmware. With CAP2.BOH the OS sets OOS
 * and waits for BOS to drop, then for BIOS busy to clear; without it the
 * firmware has no claim to release. Returns 0 when firmware never lets go. */
static int ahc_handoff(void) {
    unsigned long deadline;
    if ((ahc_r32(AHCI_REG_CAP2) & AHCI_CAP2_BOH) == 0) return 1;
    ahc_w32(AHCI_REG_BOHC, ahc_r32(AHCI_REG_BOHC) | AHCI_BOHC_OOS);
    deadline = ktime_ms() + AHCI_TMO_HANDOFF_MS;
    for (;;) {
        unsigned bohc = ahc_r32(AHCI_REG_BOHC);
        if ((bohc & (AHCI_BOHC_BOS | AHCI_BOHC_BB)) == 0) return 1;
        if ((long)(ktime_ms() - deadline) >= 0) return 0;
        __asm__ volatile("pause");
    }
}

/** Docstring: Stop a port's command and FIS engines, as the spec requires
 * before CLB/FB may change. Returns 0 when the engine never idles. */
static int ahc_port_stop(volatile unsigned char *px) {
    unsigned cmd = ahc_pr32(px, AHCI_PX_CMD);
    if (cmd & AHCI_CMD_ST)
        ahc_pw32(px, AHCI_PX_CMD, cmd & ~AHCI_CMD_ST);
    if (!ahc_wait_port(px, AHCI_PX_CMD, AHCI_CMD_CR, 0u, AHCI_TMO_ENGINE_MS))
        return 0;
    cmd = ahc_pr32(px, AHCI_PX_CMD);
    if (cmd & AHCI_CMD_FRE)
        ahc_pw32(px, AHCI_PX_CMD, cmd & ~AHCI_CMD_FRE);
    return ahc_wait_port(px, AHCI_PX_CMD, AHCI_CMD_FR, 0u,
                         AHCI_TMO_ENGINE_MS);
}

/** Docstring: True when SSTS reports a device with phy communication in
 * the active power state. */
static int ahc_link_up(volatile unsigned char *px) {
    unsigned ssts = ahc_pr32(px, AHCI_PX_SSTS);
    unsigned det = ssts & AHCI_SSTS_DET_MASK;
    unsigned ipm = (ssts >> AHCI_SSTS_IPM_SHIFT) & AHCI_SSTS_IPM_MASK;
    return det == AHCI_SSTS_DET_ONLINE && ipm == AHCI_SSTS_IPM_ACTIVE;
}

/** Docstring: Bring a port's link up: spin up and power on the device when
 * staggered spin-up is supported, then, if a device is present without
 * phy communication, issue one COMRESET and wait for the link. Returns 1
 * when the link is established. */
static int ahc_port_link(volatile unsigned char *px) {
    unsigned long hold;
    unsigned sctl;
    if (ahc_cap & AHCI_CAP_SSS)
        ahc_pw32(px, AHCI_PX_CMD,
                 ahc_pr32(px, AHCI_PX_CMD) | AHCI_CMD_SUD | AHCI_CMD_POD);
    if (ahc_link_up(px)) return 1;
    if ((ahc_pr32(px, AHCI_PX_SSTS) & AHCI_SSTS_DET_MASK) == 0u &&
            !(ahc_cap & AHCI_CAP_SSS))
        return 0;
    sctl = ahc_pr32(px, AHCI_PX_SCTL) & ~AHCI_SCTL_DET_MASK;
    ahc_pw32(px, AHCI_PX_SCTL, sctl | AHCI_SCTL_DET_COMRESET);
    hold = ktime_ms() + AHCI_TMO_COMRESET_HOLD_MS;
    while ((long)(ktime_ms() - hold) < 0)
        __asm__ volatile("pause");
    ahc_pw32(px, AHCI_PX_SCTL, sctl);
    if (!ahc_wait_port(px, AHCI_PX_SSTS, AHCI_SSTS_DET_MASK,
                       AHCI_SSTS_DET_ONLINE, AHCI_TMO_LINK_MS))
        return 0;
    ahc_pw32(px, AHCI_PX_SERR, AHCI_ALL_ONES);
    return ahc_link_up(px);
}

/** Docstring: True when a heap address can be handed to the HBA: always
 * with CAP.S64A, below 4 GB otherwise. */
static int ahc_dma_ok(const void *p, unsigned long len) {
    unsigned long long a = (unsigned long long)(unsigned long)p;
    if (ahc_cap & AHCI_CAP_S64A) return 1;
    return a + len <= AHCI_DMA_LIMIT_32;
}

/** Docstring: Point the stopped port at the command list and FIS area,
 * clear stale status, and start the FIS then the command engine. Returns
 * 0 when the device stays busy. */
static int ahc_port_start(volatile unsigned char *px) {
    unsigned long long clb = (unsigned long long)(unsigned long)ahc_cl;
    unsigned long long fb = (unsigned long long)(unsigned long)ahc_fis;
    unsigned cmd;
    ahc_pw32(px, AHCI_PX_CLB, (unsigned)(clb & AHCI_ALL_ONES));
    ahc_pw32(px, AHCI_PX_CLBU, (unsigned)(clb >> 32));
    ahc_pw32(px, AHCI_PX_FB, (unsigned)(fb & AHCI_ALL_ONES));
    ahc_pw32(px, AHCI_PX_FBU, (unsigned)(fb >> 32));
    ahc_pw32(px, AHCI_PX_SERR, AHCI_ALL_ONES);
    ahc_pw32(px, AHCI_PX_IE, 0u);
    ahc_pw32(px, AHCI_PX_IS, AHCI_ALL_ONES);
    cmd = ahc_pr32(px, AHCI_PX_CMD);
    ahc_pw32(px, AHCI_PX_CMD, cmd | AHCI_CMD_FRE);
    if (!ahc_wait_port(px, AHCI_PX_TFD, AHCI_TFD_BSY | AHCI_TFD_DRQ, 0u,
                       AHCI_TMO_LINK_MS))
        return 0;
    cmd = ahc_pr32(px, AHCI_PX_CMD) & ~AHCI_CMD_ICC_MASK;
    ahc_pw32(px, AHCI_PX_CMD, cmd | AHCI_CMD_ICC_ACTIVE | AHCI_CMD_ST);
    return 1;
}

/** Docstring: Issue one ATA command on slot 0 and poll it to completion.
 *
 * Builds the H2D register FIS (48-bit LBA, sector count), one PRD over
 * bytes of the staging buffer (none when bytes is 0), the command header
 * with the write bit when the data flows to the device, then sets PxCI
 * bit 0 and polls until it clears. A task-file error bit or TFES, or the
 * AHCI_TMO_CMD_MS budget expiring, fails the command. Caller holds
 * ahc_lock. */
static int ahc_exec(unsigned char ata_cmd, unsigned long long lba,
                    unsigned count, unsigned long bytes, int write) {
    volatile unsigned char *px = ahc_px;
    unsigned long long stage = (unsigned long long)(unsigned long)ahc_stage;
    unsigned long long ctba = (unsigned long long)(unsigned long)ahc_ct;
    unsigned char *fis = ahc_ct;
    unsigned char *prd = ahc_ct + AHCI_CT_PRDT_OFF;
    unsigned prdtl = bytes ? 1u : 0u;
    unsigned long deadline;
    unsigned i;

    if (!px) return -1;
    for (i = 0; i < AHCI_CT_BYTES; i++) ahc_ct[i] = 0;
    for (i = 0; i < AHCI_CH_BYTES; i++) ahc_cl[i] = 0;
    fis[0] = AHCI_FIS_TYPE_H2D;
    fis[1] = AHCI_FIS_H2D_CMD;
    fis[2] = ata_cmd;
    fis[4] = (unsigned char)(lba & 0xFFu);
    fis[5] = (unsigned char)((lba >> 8) & 0xFFu);
    fis[6] = (unsigned char)((lba >> 16) & 0xFFu);
    fis[7] = AHCI_FIS_DEV_LBA;
    fis[8] = (unsigned char)((lba >> 24) & 0xFFu);
    fis[9] = (unsigned char)((lba >> 32) & 0xFFu);
    fis[10] = (unsigned char)((lba >> 40) & 0xFFu);
    fis[12] = (unsigned char)(count & 0xFFu);
    fis[13] = (unsigned char)((count >> 8) & 0xFFu);
    if (bytes) {
        ahc_put32(prd, (unsigned)(stage & AHCI_ALL_ONES));
        ahc_put32(prd + 4, (unsigned)(stage >> 32));
        ahc_put32(prd + 12, (unsigned)((bytes - 1u) & AHCI_PRD_DBC_MASK));
    }
    ahc_put32(ahc_cl, (AHCI_FIS_BYTES_H2D / 4u) |
              (write ? AHCI_CH_WRITE : 0u) |
              (prdtl << AHCI_CH_PRDTL_SHIFT));
    ahc_put32(ahc_cl + 8, (unsigned)(ctba & AHCI_ALL_ONES));
    ahc_put32(ahc_cl + 12, (unsigned)(ctba >> 32));
    __asm__ volatile("mfence" ::: "memory");

    if (!ahc_wait_port(px, AHCI_PX_TFD, AHCI_TFD_BSY | AHCI_TFD_DRQ, 0u,
                       AHCI_TMO_CMD_MS))
        return -1;
    ahc_pw32(px, AHCI_PX_IS, AHCI_ALL_ONES);
    ahc_pw32(px, AHCI_PX_CI, 1u);
    deadline = ktime_ms() + AHCI_TMO_CMD_MS;
    for (;;) {
        if (ahc_pr32(px, AHCI_PX_IS) & AHCI_IS_TFES) return -1;
        if ((ahc_pr32(px, AHCI_PX_CI) & 1u) == 0u) break;
        if ((long)(ktime_ms() - deadline) >= 0) return -1;
        __asm__ volatile("pause");
    }
    __asm__ volatile("mfence" ::: "memory");
    if (ahc_pr32(px, AHCI_PX_TFD) & AHCI_TFD_ERR) return -1;
    return 0;
}

/** Docstring: IDENTIFY the claimed disk and record its capacity. Refuses a
 * drive without 48-bit addressing, with a zero capacity, or with logical
 * sectors that are not 512 bytes. */
static int ahc_identify(void) {
    unsigned long long n;
    unsigned ss;
    if (ahc_exec(ATA_CMD_IDENTIFY, 0u, 0u, ATA_ID_WORDS * 2u, 0) != 0) {
        ahc_note = "IDENTIFY DEVICE failed";
        return 0;
    }
    if ((ahc_id_word(ahc_stage, ATA_ID_CMDSET2) & ATA_ID_LBA48_BIT) == 0) {
        ahc_note = "disk has no 48-bit LBA";
        return 0;
    }
    ss = ahc_id_word(ahc_stage, ATA_ID_SECTOR_SIZE);
    if ((ss & ATA_ID_SS_VALID_MASK) == ATA_ID_SS_VALID &&
            (ss & ATA_ID_SS_LONG) != 0) {
        ahc_note = "logical sector is not 512 bytes";
        return 0;
    }
    n = (unsigned long long)ahc_id_word(ahc_stage, ATA_ID_LBA48_SECTORS) |
        ((unsigned long long)ahc_id_word(ahc_stage,
                                         ATA_ID_LBA48_SECTORS + 1u) << 16) |
        ((unsigned long long)ahc_id_word(ahc_stage,
                                         ATA_ID_LBA48_SECTORS + 2u) << 32) |
        ((unsigned long long)ahc_id_word(ahc_stage,
                                         ATA_ID_LBA48_SECTORS + 3u) << 48);
    if (n == 0 || n >= AHCI_LBA48_LIMIT) {
        ahc_note = "IDENTIFY reports no usable capacity";
        return 0;
    }
    ahc_nsec = (unsigned long)n;
    return 1;
}

/** Docstring: Allocate the DMA structures once, aligned as the spec
 * requires, and make the control structures uncached. Returns 0 on
 * exhaustion or when an address is out of the HBA's reach. */
static int ahc_alloc(void) {
    if (!ahc_cl) ahc_cl = kmalloc_aligned(AHCI_CL_BYTES, AHCI_CL_ALIGN);
    if (!ahc_fis) ahc_fis = kmalloc_aligned(AHCI_FIS_BYTES, AHCI_FIS_ALIGN);
    if (!ahc_ct) ahc_ct = kmalloc_aligned(AHCI_CT_BYTES, AHCI_CT_ALIGN);
    if (!ahc_stage)
        ahc_stage = kmalloc_aligned(AHCI_STAGE_BYTES, AHCI_STAGE_ALIGN);
    if (!ahc_cl || !ahc_fis || !ahc_ct || !ahc_stage) {
        ahc_note = "out of memory for DMA structures";
        return 0;
    }
    if (!ahc_dma_ok(ahc_cl, AHCI_CL_BYTES) ||
            !ahc_dma_ok(ahc_fis, AHCI_FIS_BYTES) ||
            !ahc_dma_ok(ahc_ct, AHCI_CT_BYTES) ||
            !ahc_dma_ok(ahc_stage, AHCI_STAGE_BYTES)) {
        ahc_note = "DMA memory above 4 GB on a 32-bit HBA";
        return 0;
    }
    kmemset(ahc_cl, 0, AHCI_CL_BYTES);
    kmemset(ahc_fis, 0, AHCI_FIS_BYTES);
    kmemset(ahc_ct, 0, AHCI_CT_BYTES);
    kmm_make_uncached((unsigned long)ahc_cl, AHCI_CL_BYTES);
    kmm_make_uncached((unsigned long)ahc_fis, AHCI_FIS_BYTES);
    kmm_make_uncached((unsigned long)ahc_ct, AHCI_CT_BYTES);
    return 1;
}

/** Docstring: Walk the implemented ports and claim the first ATA disk with
 * an established link that starts and answers IDENTIFY. */
static int ahc_claim_port(void) {
    unsigned p;
    int seen_atapi = 0;
    ahc_note = "no ATA disk with an established link";
    for (p = 0; p < AHCI_MAX_PORTS; p++) {
        volatile unsigned char *px;
        if ((ahc_pi & (1u << p)) == 0u) continue;
        px = ahc_mmio + AHCI_PORT_BASE + p * AHCI_PORT_STRIDE;
        if (!ahc_port_stop(px)) continue;
        if (!ahc_port_link(px)) continue;
        if (ahc_pr32(px, AHCI_PX_SIG) != AHCI_SIG_ATA) {
            seen_atapi = 1;
            continue;
        }
        if (!ahc_port_start(px)) continue;
        ahc_px = px;
        ahc_portno = (int)p;
        if (ahc_identify()) return 1;
        ahc_port_stop(px);
        ahc_px = 0;
        ahc_portno = -1;
    }
    if (seen_atapi && ahc_portno < 0)
        ahc_note = "only non-disk devices (ATAPI or multiplier) on the HBA";
    return 0;
}

int ahci_init(void) {
    pci_bdf_t bdf;
    unsigned orig_cmd;
    unsigned long long size;
    unsigned long long bar_base;
    unsigned long mapped;
    if (ahc_probed) return ahc_on;
    ahc_probed = 1;
    ahc_note = "no AHCI controller in PCI class 01:06:01";
    if (!pci_find_class(&bdf, AHCI_CLASS_BASE, AHCI_CLASS_SUB, AHCI_CLASS_PI,
                        ahc_outl, ahc_inl)) return 0;
    orig_cmd = pci_cfg_read(bdf.bus, bdf.dev, bdf.func, PCI_REG_COMMAND,
                            ahc_outl, ahc_inl);
    if (pci_bar_is_io(bdf.bus, bdf.dev, bdf.func, AHCI_ABAR_INDEX,
                      ahc_outl, ahc_inl)) {
        ahc_note = "ABAR is an I/O range, not memory";
        return 0;
    }
    pci_cfg_write(bdf.bus, bdf.dev, bdf.func, PCI_REG_COMMAND,
                  orig_cmd & ~(PCI_COMMAND_MEMORY | PCI_COMMAND_BUS_MASTER),
                  ahc_outl);
    size = pci_bar_size(bdf.bus, bdf.dev, bdf.func, AHCI_ABAR_INDEX,
                        ahc_outl, ahc_inl);
    bar_base = pci_bar_base(bdf.bus, bdf.dev, bdf.func, AHCI_ABAR_INDEX,
                            ahc_outl, ahc_inl);
    if (size < AHCI_PORT_BASE || size > (unsigned long long)PCI_MMIO_SIZE ||
            bar_base == 0) {
        ahc_note = "ABAR is not a memory BAR of a usable size";
        pci_cfg_write(bdf.bus, bdf.dev, bdf.func, PCI_REG_COMMAND, orig_cmd,
                      ahc_outl);
        return 0;
    }
    pci_cfg_write(bdf.bus, bdf.dev, bdf.func, PCI_REG_COMMAND,
                  orig_cmd | PCI_COMMAND_MEMORY | PCI_COMMAND_BUS_MASTER,
                  ahc_outl);
    mapped = kmm_map_device((unsigned long)bar_base, (unsigned long)size);
    if (!mapped) {
        ahc_note = "uncached mapping of ABAR refused";
        pci_cfg_write(bdf.bus, bdf.dev, bdf.func, PCI_REG_COMMAND, orig_cmd,
                      ahc_outl);
        return 0;
    }
    ahc_mmio = (volatile unsigned char *)mapped;
    ahc_version = ahc_r32(AHCI_REG_VS);
    if (ahc_version == 0 || ahc_version == AHCI_ALL_ONES) {
        ahc_note = "VS reports no AHCI revision, refusing";
        ahc_mmio = 0;
        pci_cfg_write(bdf.bus, bdf.dev, bdf.func, PCI_REG_COMMAND, orig_cmd,
                      ahc_outl);
        return 0;
    }
    if (!ahc_handoff()) {
        ahc_note = "firmware kept ownership (BIOS/OS handoff timed out)";
        ahc_mmio = 0;
        return 0;
    }
    ahc_w32(AHCI_REG_GHC,
            (ahc_r32(AHCI_REG_GHC) | AHCI_GHC_AE) & ~AHCI_GHC_IE);
    ahc_cap = ahc_r32(AHCI_REG_CAP);
    ahc_pi = ahc_r32(AHCI_REG_PI);
    ahc_w32(AHCI_REG_IS, AHCI_ALL_ONES);
    if (ahc_pi == 0) {
        ahc_note = "HBA implements no ports";
        return 0;
    }
    if (!ahc_alloc()) return 0;
    if (!ahc_claim_port()) return 0;
    ahc_on = 1;
    ahc_note = "disk ready, read-write";
    return 1;
}

/** Docstring: Shared range check for both directions. */
static int ahc_range_ok(unsigned lba, unsigned count, const void *buf) {
    if (!ahc_on || !buf || count == 0) return 0;
    if ((unsigned long)lba >= ahc_nsec) return 0;
    if ((unsigned long)count > ahc_nsec - (unsigned long)lba) return 0;
    return 1;
}

int ahci_read_sectors(unsigned lba, unsigned count, void *buf) {
    unsigned char *out = (unsigned char *)buf;
    irqflags_t flags;
    if (!ahc_range_ok(lba, count, buf)) return -1;
    while (count) {
        unsigned n = count > AHCI_MAX_SECTORS ? AHCI_MAX_SECTORS : count;
        unsigned long bytes = (unsigned long)n * AHCI_SECTOR;
        int r;
        spin_lock_irqsave(&ahc_lock, &flags);
        r = ahc_exec(ATA_CMD_READ_DMA_EXT, lba, n, bytes, 0);
        if (r == 0) kmemcpy(out, ahc_stage, bytes);
        spin_unlock_irqrestore(&ahc_lock, flags);
        if (r != 0) return -1;
        out += bytes;
        lba += n;
        count -= n;
    }
    return 0;
}

int ahci_write_sectors(unsigned lba, unsigned count, const void *buf) {
    const unsigned char *in = (const unsigned char *)buf;
    irqflags_t flags;
    int r = 0;
    if (!ahc_range_ok(lba, count, buf)) return -1;
    while (count) {
        unsigned n = count > AHCI_MAX_SECTORS ? AHCI_MAX_SECTORS : count;
        unsigned long bytes = (unsigned long)n * AHCI_SECTOR;
        spin_lock_irqsave(&ahc_lock, &flags);
        kmemcpy(ahc_stage, in, bytes);
        r = ahc_exec(ATA_CMD_WRITE_DMA_EXT, lba, n, bytes, 1);
        spin_unlock_irqrestore(&ahc_lock, flags);
        if (r != 0) return -1;
        in += bytes;
        lba += n;
        count -= n;
    }
    spin_lock_irqsave(&ahc_lock, &flags);
    r = ahc_exec(ATA_CMD_FLUSH_EXT, 0u, 0u, 0u, 0);
    spin_unlock_irqrestore(&ahc_lock, flags);
    return r == 0 ? 0 : -1;
}

/** Docstring: Registry read op. */
static int ahc_ops_read(device_t *dev, unsigned lba, unsigned count,
                        void *buf) {
    (void)dev;
    return ahci_read_sectors(lba, count, buf);
}

/** Docstring: Registry write op. */
static int ahc_ops_write(device_t *dev, unsigned lba, unsigned count,
                         const void *buf) {
    (void)dev;
    return ahci_write_sectors(lba, count, buf);
}

/** Docstring: Registry capacity op, clamped to the 32-bit registry field. */
static unsigned ahc_ops_total(device_t *dev) {
    (void)dev;
    return ahc_nsec > AHCI_ALL_ONES ? AHCI_ALL_ONES : (unsigned)ahc_nsec;
}

/** Docstring: Registry presence op. */
static int ahc_ops_present(device_t *dev) {
    (void)dev;
    return ahc_on;
}

/** Docstring: Block ops table published as ahci0. */
static const block_ops_t ahc_block_ops = {
    ahc_ops_read,
    ahc_ops_write,
    ahc_ops_total,
    ahc_ops_present,
};

/** Docstring: Registry entry for the claimed SATA disk. */
static device_t ahc_device = {
    "ahci0",
    DEV_TYPE_BLOCK,
    &ahc_block_ops,
    0,
    0,
};

void ahci_register_device(void) {
    device_register(&ahc_device);
}
