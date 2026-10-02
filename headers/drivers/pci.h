/** Docstring: drivers/pci.h -- PCI configuration-space access.
 *
 * Single home for the CF8/CFC mechanism every PCI device uses
 * (rtl8139 NIC, virtio-blk, xHCI). Header-only: integer ops,
 * host-testable by construction (no kernel state). Replaces the
 * per-driver static copies (rtl8139's pci_read32/pci_write32), so
 * the next device adds an ID table, never a third copy of the
 * mechanism. */

#ifndef DRIVERS_PCI_H
#define DRIVERS_PCI_H

#define PCI_CFG_ADDR 0xCF8u
#define PCI_CFG_DATA 0xCFCu
#define PCI_MAX_BUS  256u
#define PCI_MAX_DEV  32u
#define PCI_MAX_FUNC 8u

/* ---- Config space register offsets ---- */
#define PCI_REG_VENDOR_ID   0x00u
#define PCI_REG_COMMAND     0x04u
#define PCI_REG_CLASS_REV   0x08u
#define PCI_REG_CLASS_PROGIF 0x09u
#define PCI_REG_HEADER_TYPE 0x0Eu
#define PCI_REG_BAR0        0x10u
#define PCI_REG_CARD_BUS    0x18u
#define PCI_REG_BRIDGE_SECONDARY 0x19u
#define PCI_REG_CAP_PTR     0x34u
#define PCI_REG_BAR_COUNT   6u

/* ---- Command register bits ---- */
#define PCI_COMMAND_IO           0x0001u
#define PCI_COMMAND_MEMORY       0x0002u
#define PCI_COMMAND_BUS_MASTER   0x0004u

/* ---- BAR type bits (low nibble) ---- */
#define PCI_BAR_TYPE_MASK   0x0006u
#define PCI_BAR_IO          0x0001u
#define PCI_BAR_64BIT       0x0004u
#define PCI_BAR_PREFETCH    0x0008u
#define PCI_BAR_ADDR_MASK   0xFFFFFFF0u

/* ---- Device identity sentinels and shapes ---- */
#define PCI_ABSENT_ID       0xFFFFFFFFu
#define PCI_HEADER_MULTIFUNC 0x80u
#define PCI_HEADER_TYPE_MASK 0x7Fu
#define PCI_HDR_TYPE_BRIDGE  0x06u

/* ---- Class codes this kernel matches on ----
 *
 * Matching by class rather than vendor/device is what makes a driver work
 * on real silicon: xHCI is class 0x0C/0x03/0x30 on every Intel PCH, AMD
 * chipset and ASMedia bridge, so no vendor table is needed and no chipset
 * is missed. */
#define PCI_CLASS_BRIDGE        0x06u
#define PCI_SUBCLASS_PCI_BRIDGE 0x04u
#define PCI_CLASS_XHCI          0x0Cu
#define PCI_SUBCLASS_XHCI       0x03u
#define PCI_PROGIF_XHCI         0x30u

/** Docstring: Wildcard for a class-match component: any value matches. */
#define PCI_CLASS_ANY 0xFFu

/** Docstring: Sweeps of the bus walk before it gives up. One sweep visits
 * every bus number, so a second sweep only happens when a bridge led to a
 * bus numbered below the bridge itself; four covers any real topology with
 * room to spare and keeps the walk finite. */
#define PCI_CLASS_MAX_PASSES 4u

/** Docstring: Address of a device on the bus, as found by the walk. */
typedef struct {
    unsigned bus;
    unsigned dev;
    unsigned func;
} pci_bdf_t;

/** Docstring: Read one config dword. (bus, dev, func, reg) with reg
 * dword-aligned by construction (low two bits masked, never a
 * misaligned access). */
static inline unsigned pci_cfg_read(unsigned bus, unsigned dev,
        unsigned func, unsigned reg,
        void (*outl)(unsigned short, unsigned),
        unsigned (*inl)(unsigned short)) {
    outl(PCI_CFG_ADDR,
        0x80000000u | (bus << 16) | (dev << 11) | (func << 8) | (reg & 0xFCu));
    return inl(PCI_CFG_DATA);
}

/** Docstring: Write one config dword. Same addressing as read. */
static inline void pci_cfg_write(unsigned bus, unsigned dev,
        unsigned func, unsigned reg, unsigned val,
        void (*outl)(unsigned short, unsigned)) {
    outl(PCI_CFG_ADDR,
        0x80000000u | (bus << 16) | (dev << 11) | (func << 8) | (reg & 0xFCu));
    outl(PCI_CFG_DATA, val);
}

/** Docstring: Read a config byte. The window is dword aligned once; the
 * byte selector rides in the low address bits, never a byte port op. */
static inline unsigned char pci_cfg_read8(unsigned bus, unsigned dev,
        unsigned func, unsigned reg,
        void (*outl)(unsigned short, unsigned),
        unsigned (*inl)(unsigned short)) {
    unsigned dword = pci_cfg_read(bus, dev, func, reg, outl, inl);
    return (unsigned char)((dword >> ((reg & 3u) * 8u)) & 0xFFu);
}

/** Docstring: Write a config byte, read-modify-write on the window. */
static inline void pci_cfg_write8(unsigned bus, unsigned dev,
        unsigned func, unsigned reg, unsigned char val,
        void (*outl)(unsigned short, unsigned),
        unsigned (*inl)(unsigned short)) {
    unsigned dword = pci_cfg_read(bus, dev, func, reg, outl, inl);
    unsigned shift = (reg & 3u) * 8u;
    dword = (dword & ~(0xFFu << shift)) | ((unsigned)val << shift);
    pci_cfg_write(bus, dev, func, reg, dword, outl);
}

/** Docstring: True when a function is populated. A dword read of vendor id
 * returns all ones for an unpopulated function, which is also what a bus
 * with nothing behind bridge 0 returns, so this doubles as a bus probe. */
static inline int pci_present(unsigned bus, unsigned dev, unsigned func,
        void (*outl)(unsigned short, unsigned),
        unsigned (*inl)(unsigned short)) {
    return pci_cfg_read(bus, dev, func, PCI_REG_VENDOR_ID, outl, inl) !=
           PCI_ABSENT_ID;
}

/** Docstring: True when a function matches a class triple.
 *
 * The three class bytes sit in the class/revision dword at bits 31:8, in the
 * order base class, subclass, programming interface, with the revision id in
 * bits 7:0. Reading them a byte lower would compare the subclass against the
 * base class: an xHCI (0x0C/0x03/0x30) would look for class 0x03, and a PCI
 * bridge (0x06/0x04) for 0x04 -- every lookup silently misses. */
static inline int pci_class_matches(unsigned bus, unsigned dev,
        unsigned func, unsigned cls, unsigned subclass, unsigned prog_if,
        void (*outl)(unsigned short, unsigned),
        unsigned (*inl)(unsigned short)) {
    unsigned dword = pci_cfg_read(bus, dev, func, PCI_REG_CLASS_REV, outl, inl);
    unsigned f_class = (dword >> 24) & 0xFFu;
    unsigned f_sub = (dword >> 16) & 0xFFu;
    unsigned f_prog = (dword >> 8) & 0xFFu;
    if (cls != PCI_CLASS_ANY && f_class != cls) return 0;
    if (subclass != PCI_CLASS_ANY && f_sub != subclass) return 0;
    if (prog_if != PCI_CLASS_ANY && f_prog != prog_if) return 0;
    return 1;
}

/** Docstring: True when a function advertises more than one function in its
 * slot, so the walk must visit every function number, not just function 0. */
static inline int pci_is_multifunction(unsigned bus, unsigned dev,
        void (*outl)(unsigned short, unsigned),
        unsigned (*inl)(unsigned short)) {
    unsigned ht = pci_cfg_read(bus, dev, 0, PCI_REG_HEADER_TYPE, outl, inl);
    return (ht & PCI_HEADER_MULTIFUNC) != 0;
}

/** Docstring: Find a device by vendor/device ID on bus 0.
 *
 * Returns the dev number, or -1 when absent. Bus-0 function-0 only: this is
 * the QEMU seabios/OVMF layout, which is all the emulated single-function
 * devices needed. A device that must also be found behind a chipset bridge
 * (any xHCI) uses pci_find_class, which walks. */
static inline int pci_find(unsigned vendor, unsigned device,
        unsigned (*inl)(unsigned short),
        void (*outl)(unsigned short, unsigned)) {
    unsigned dev;
    for (dev = 0; dev < PCI_MAX_DEV; dev++) {
        unsigned id = pci_cfg_read(0, dev, 0, PCI_REG_VENDOR_ID, outl, inl);
        if ((id & 0xFFFFu) == vendor && ((id >> 16) & 0xFFFFu) == device)
            return (int)dev;
    }
    return -1;
}

/** Docstring: Find the first function anywhere on the PCI tree matching a
 * class triple, and report its bus/device/function.
 *
 * The walk starts at bus 0 and follows each PCI-to-PCI bridge's secondary
 * bus number, so a controller behind a chipset bridge on real hardware is
 * found exactly as one on QEMU's bus 0. Two 256-bit masks, 32 bytes of stack
 * each: "reachable" (a bridge leads here) and "scanned" (already looked at).
 * Reachability and scanning are separate so a bus numbered *below* the bridge
 * that leads to it -- a forward reference, legal and real -- is still visited:
 * the sweep runs again while it keeps reaching unscanned buses, bounded by
 * PCI_CLASS_MAX_PASSES. A bus whose function 0 is empty is skipped whole,
 * which makes an unpopulated range cost two reads per bus. Any class
 * component may be PCI_CLASS_ANY.
 *
 * Returns 1 and fills out on a hit, 0 when nothing matches (out is then
 * zeroed, so a caller that ignores the result still fails closed). */
static inline int pci_find_class(pci_bdf_t *out,
        unsigned cls, unsigned subclass, unsigned prog_if,
        void (*outl)(unsigned short, unsigned),
        unsigned (*inl)(unsigned short)) {
    unsigned long long seen[4] = { 0ULL, 0ULL, 0ULL, 0ULL };
    unsigned long long reach[4] = { 1ULL, 0ULL, 0ULL, 0ULL };
    unsigned pass;
    if (out) out->bus = out->dev = out->func = 0;
    for (pass = 0; pass < PCI_CLASS_MAX_PASSES; pass++) {
        int progress = 0;
        unsigned bus;
        for (bus = 0; bus < PCI_MAX_BUS; bus++) {
            unsigned dev;
            unsigned word = bus >> 6;
            unsigned bit = bus & 63u;
            if (!(reach[word] & (1ULL << bit))) continue;
            if (seen[word] & (1ULL << bit)) continue;
            seen[word] |= 1ULL << bit;
            progress = 1;
            if (!pci_present(bus, 0, 0, outl, inl)) continue;
            for (dev = 0; dev < PCI_MAX_DEV; dev++) {
                unsigned maxfunc;
                unsigned func;
                if (!pci_present(bus, dev, 0, outl, inl)) continue;
                maxfunc = pci_is_multifunction(bus, dev, outl, inl) ?
                          PCI_MAX_FUNC : 1u;
                for (func = 0; func < maxfunc; func++) {
                    if (func && !pci_present(bus, dev, func, outl, inl))
                        continue;
                    if (pci_class_matches(bus, dev, func, cls, subclass,
                                          prog_if, outl, inl)) {
                        if (out) {
                            out->bus = bus;
                            out->dev = dev;
                            out->func = func;
                        }
                        return 1;
                    }
                }
                if (pci_class_matches(bus, dev, 0, PCI_CLASS_BRIDGE,
                                      PCI_SUBCLASS_PCI_BRIDGE, PCI_CLASS_ANY,
                                      outl, inl)) {
                    unsigned sec = pci_cfg_read8(bus, dev, 0,
                        PCI_REG_BRIDGE_SECONDARY, outl, inl);
                    if (sec != 0u && sec < PCI_MAX_BUS &&
                        !(seen[sec >> 6] & (1ULL << (sec & 63u))))
                        reach[sec >> 6] |= 1ULL << (sec & 63u);
                }
            }
        }
        if (!progress) break;
    }
    return 0;
}
/** Docstring: Number of 64-bit BARs in the bar/6 dword. */
static inline unsigned pci_bar_count(unsigned bus, unsigned dev, unsigned func,
        void (*outl)(unsigned short, unsigned),
        unsigned (*inl)(unsigned short)) {
    unsigned n = 0;
    while (n < PCI_REG_BAR_COUNT) {
        unsigned bar = pci_cfg_read(bus, dev, func, PCI_REG_BAR0 + n * 4u,
                                    outl, inl);
        if (bar == 0u || bar == PCI_ABSENT_ID) break;
        n++;
        if (bar & PCI_BAR_64BIT) n++;
    }
    return n;
}

/** Docstring: True when a BAR is an I/O port range rather than memory. */
static inline int pci_bar_is_io(unsigned bus, unsigned dev, unsigned func,
        unsigned bar,
        void (*outl)(unsigned short, unsigned),
        unsigned (*inl)(unsigned short)) {
    unsigned val = pci_cfg_read(bus, dev, func, PCI_REG_BAR0 + bar * 4u,
                                 outl, inl);
    return (val & PCI_BAR_IO) != 0;
}

/** Docstring: True when a BAR is a 64-bit memory BAR, so its high dword is
 * the next BAR slot and must be programmed together with it. */
static inline int pci_bar_is_64bit(unsigned bus, unsigned dev, unsigned func,
        unsigned bar,
        void (*outl)(unsigned short, unsigned),
        unsigned (*inl)(unsigned short)) {
    unsigned val = pci_cfg_read(bus, dev, func, PCI_REG_BAR0 + bar * 4u,
                                 outl, inl);
    return (val & PCI_BAR_IO) == 0 && (val & PCI_BAR_64BIT) != 0;
}

/** Docstring: Count of trailing zero bits in a 32-bit word, 32 for zero. */
static inline unsigned pci_bar_ctz32(unsigned val) {
    unsigned n = 0;
    if (val == 0) return 32;
    while ((val & 1u) == 0u) {
        val >>= 1;
        n++;
    }
    return n;
}

/** Docstring: Size in bytes a probed BAR address mask describes.
 *
 * A BAR's address lines are contiguous, so the zero bits of its mask are
 * exactly the unimplemented low-order address lines and the region is
 * 2^(that count) bytes. Two things this must not do:
 *
 *   Read the mask as a flat 64-bit complement. A 32-bit BAR has no upper
 *   half, so the complement finds zeros up there and reports a region
 *   billions of times too large.
 *
 *   Count the zeros of the whole 64-bit word at once. A 64-bit BAR whose
 *   high half has address lines describes a region above 4 GB, and its size
 *   is 2^(32 + trailing zeros of the high half), not 2^(trailing zeros of
 *   the low half).
 *
 * The low nibble carries the type bits, which are fields rather than address
 * lines, so it is cleared first. A mask with no zero bits at all describes
 * no window and is refused, which is the fail-closed answer a caller must
 * refuse on. */
static inline unsigned long long pci_bar_size_from_mask(unsigned long long mask)
{
    unsigned hi;
    mask &= ~0xFULL;
    if (mask == 0 || mask == 0xFFFFFFFFFFFFFFF0ULL) return 0;
    hi = (unsigned)(mask >> 32);
    if (hi != 0) return 1ULL << (32u + pci_bar_ctz32(hi));
    return 1ULL << pci_bar_ctz32((unsigned)mask);
}

/** Docstring: Probed size in bytes of a memory BAR, restoring its value.
 *
 * The mask is what proves the region is big enough; a size is never assumed
 * from a spec table because a wrong answer is a window overrun on hardware
 * that disagrees. Writing all ones makes the device drive its address lines
 * with the unmasked bits, so the read-back mask has zeroes exactly where
 * address lines exist. The original value is restored before returning, so
 * a caller that then relocates the BAR starts from the firmware assignment
 * rather than from all ones.
 *
 * Returns 0 for an absent function, an I/O BAR, or a BAR with no address
 * bits at all -- all of which are hard failures for an MMIO driver.
 *
 * The caller must clear PCI_COMMAND_MEMORY first: writing all ones leaves
 * the device decoding a different address than the one the command register
 * authorizes, and a device that is still decoding sees its own probe. */
static inline unsigned long long pci_bar_size(unsigned bus, unsigned dev,
        unsigned func, unsigned bar,
        void (*outl)(unsigned short, unsigned),
        unsigned (*inl)(unsigned short)) {
    unsigned reg = PCI_REG_BAR0 + bar * 4u;
    unsigned orig = pci_cfg_read(bus, dev, func, reg, outl, inl);
    unsigned long long mask = 0;
    if (orig == PCI_ABSENT_ID) return 0;
    if (orig & PCI_BAR_IO) return 0;
    if (orig & PCI_BAR_64BIT) {
        unsigned orig_hi = pci_cfg_read(bus, dev, func, reg + 4u, outl, inl);
        pci_cfg_write(bus, dev, func, reg, 0xFFFFFFFFu, outl);
        mask = (unsigned long long)(pci_cfg_read(bus, dev, func, reg, outl,
                                                 inl) & PCI_BAR_ADDR_MASK);
        pci_cfg_write(bus, dev, func, reg + 4u, 0xFFFFFFFFu, outl);
        mask |= (unsigned long long)(pci_cfg_read(bus, dev, func, reg + 4u,
                                                  outl, inl) &
                                     PCI_BAR_ADDR_MASK) << 32;
        pci_cfg_write(bus, dev, func, reg, orig, outl);
        pci_cfg_write(bus, dev, func, reg + 4u, orig_hi, outl);
    } else {
        pci_cfg_write(bus, dev, func, reg, 0xFFFFFFFFu, outl);
        mask = (unsigned long long)(pci_cfg_read(bus, dev, func, reg, outl,
                                                 inl) & PCI_BAR_ADDR_MASK);
        pci_cfg_write(bus, dev, func, reg, orig, outl);
    }
    return pci_bar_size_from_mask(mask);
}

/** Docstring: Program a memory BAR with a physical base address.
 *
 * Legal only while the command register's memory-space-enable bit is clear:
 * the device must not be decoding at the old address while the BAR changes.
 * A 64-bit BAR takes its high dword from base's upper half, so a caller
 * relocating into a 32-bit window must pass a base whose upper half is zero
 * rather than expecting truncation. Returns 1 on success, 0 when the device
 * is absent or the BAR is an I/O range. */
static inline int pci_bar_relocate(unsigned bus, unsigned dev, unsigned func,
        unsigned bar, unsigned long long base,
        void (*outl)(unsigned short, unsigned),
        unsigned (*inl)(unsigned short)) {
    unsigned reg = PCI_REG_BAR0 + bar * 4u;
    unsigned orig = pci_cfg_read(bus, dev, func, reg, outl, inl);
    if (orig == PCI_ABSENT_ID) return 0;
    if (orig & PCI_BAR_IO) return 0;
    pci_cfg_write(bus, dev, func, reg,
                  ((unsigned)base & PCI_BAR_ADDR_MASK) | (orig & 0x0Fu),
                  outl);
    if (orig & PCI_BAR_64BIT)
        pci_cfg_write(bus, dev, func, reg + 4u, (unsigned)(base >> 32), outl);
    return 1;
}

/** Docstring: Restore a BAR pair to previously saved raw values. Used to put
 * a device back exactly as firmware left it when a probe bails, so a later
 * driver or a warm reboot sees the original assignment. */
static inline void pci_bar_restore(unsigned bus, unsigned dev,
        unsigned func, unsigned bar, unsigned orig, unsigned orig_hi,
        void (*outl)(unsigned short, unsigned)) {
    unsigned reg = PCI_REG_BAR0 + bar * 4u;
    pci_cfg_write(bus, dev, func, reg, orig, outl);
    if (orig & PCI_BAR_64BIT)
        pci_cfg_write(bus, dev, func, reg + 4u, orig_hi, outl);
}

#endif
