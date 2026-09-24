/** Docstring: drivers/pci.h -- PCI configuration-space access.
 *
 * Single home for the CF8/CFC mechanism every PCI device uses
 * (rtl8139 NIC, virtio-blk, future e1000/AHCI). Header-only: two
 * integer ops, host-testable by construction (no kernel state).
 * Replaces the per-driver static copies (rtl8139's pci_read32/
 * pci_write32), so the next device adds an ID table, never a third
 * copy of the mechanism. */

#ifndef DRIVERS_PCI_H
#define DRIVERS_PCI_H

#define PCI_CFG_ADDR 0xCF8u
#define PCI_CFG_DATA 0xCFCu
#define PCI_MAX_BUS  256u
#define PCI_MAX_DEV  32u
#define PCI_MAX_FUNC 8u

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

/** Docstring: Find a device by vendor/device ID on bus 0 (the QEMU
 * seabios/OVMF layout; multifunction and multi-bus walks are future
 * work, documented). Returns the dev number, or -1 when absent.
 * The id read double-tasks as the probe: 0xFFFFFFFF means no device. */
static inline int pci_find(unsigned vendor, unsigned device,
        unsigned (*inl)(unsigned short),
        void (*outl)(unsigned short, unsigned)) {
    unsigned dev;
    for (dev = 0; dev < PCI_MAX_DEV; dev++) {
        unsigned id = pci_cfg_read(0, dev, 0, 0, outl, inl);
        if ((id & 0xFFFFu) == vendor && ((id >> 16) & 0xFFFFu) == device)
            return (int)dev;
    }
    return -1;
}

#endif
