/** Docstring: Host test for headers/drivers/pci.h (make test-pci).
 *
 * Drives the config-space helpers against a fake PCI tree with more than one
 * bus, so the bus walk, the bridge traversal, the class match and the BAR size
 * probe are all exercised on the host with no QEMU boot. Verifies find by
 * vendor/device, find-miss, read/write roundtrip and dword alignment masking
 * (so a mutant that breaks the CF8 address composition dies here), plus the
 * multi-bus walk, the multifunction bit, the class triple with its wildcard,
 * the byte accessors the secondary-bus read needs, and the BAR size probe
 * with its restore and its refusals.
 *
 * Fake topology:
 *   bus 0: dev 5 func 0 = rtl8139, dev 9 func 0 = virtio-blk,
 *          dev 20 func 0 = PCI-PCI bridge with secondary bus 1
 *   bus 1: dev 3 func 0 = xHCI (0C/03/30), dev 3 func 1 = a second function
 *          (only reachable because dev 3 advertises the multifunction bit)
 *   bus 2: dev 1 func 0 = a class the driver does not want
 */

#include <stdio.h>

#include "drivers/pci.h"

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

#define FAKE_BUSES 4
#define FAKE_REGS 64
static unsigned cfg[FAKE_BUSES][32][8][FAKE_REGS];
static unsigned bar_mask[FAKE_BUSES][32][8][FAKE_REGS];
static unsigned last_addr;

static void fake_outl(unsigned short port, unsigned val) {
    if (port == PCI_CFG_ADDR) {
        last_addr = val;
    } else if (port == PCI_CFG_DATA) {
        unsigned bus = (last_addr >> 16) & 0xFFu;
        unsigned dev = (last_addr >> 11) & 31u;
        unsigned func = (last_addr >> 8) & 7u;
        unsigned reg = (last_addr & 0xFCu) >> 2;
        if (bus < FAKE_BUSES && reg < FAKE_REGS) {
            /* A BAR probed with all ones answers with its address mask, which
             * is what real hardware does and what makes the size formula
             * testable; a register that is not a BAR echoes the value back. */
            if (reg >= (PCI_REG_BAR0 >> 2) && reg < (PCI_REG_BAR0 >> 2) + 6u &&
                val == 0xFFFFFFFFu)
                cfg[bus][dev][func][reg] = bar_mask[bus][dev][func][reg];
            else
                cfg[bus][dev][func][reg] = val;
        }
    }
}

static unsigned fake_inl(unsigned short port) {
    if (port == PCI_CFG_DATA) {
        unsigned bus = (last_addr >> 16) & 0xFFu;
        unsigned dev = (last_addr >> 11) & 31u;
        unsigned func = (last_addr >> 8) & 7u;
        unsigned reg = (last_addr & 0xFCu) >> 2;
        if (bus < FAKE_BUSES && reg < FAKE_REGS)
            return cfg[bus][dev][func][reg];
        return 0xFFFFFFFFu;
    }
    return 0;
}

static void set_dev(unsigned bus, unsigned dev, unsigned func,
                    unsigned id, unsigned class_rev) {
    cfg[bus][dev][func][0] = id;
    cfg[bus][dev][func][2] = class_rev;
}

int main(void) {
    unsigned i, k, f, b;
    pci_bdf_t bdf;

    for (b = 0; b < FAKE_BUSES; b++)
        for (i = 0; i < 32; i++)
            for (f = 0; f < 8; f++) {
                for (k = 0; k < FAKE_REGS; k++) {
                    cfg[b][i][f][k] = 0xFFFFFFFFu;
                    bar_mask[b][i][f][k] = 0x00000000u;
                }
                /* A default BAR mask with twelve unimplemented address lines:
                 * a 4 KB window, the usual register block size. */
                for (k = PCI_REG_BAR0 >> 2; k < (PCI_REG_BAR0 >> 2) + 6u; k++)
                    bar_mask[b][i][f][k] = 0xFFFFF000u;
            }

    set_dev(0, 0, 0, 0x12348086u, 0x06000000u);
    cfg[0][0][0][PCI_REG_HEADER_TYPE >> 2] = 0x00000000u;
    set_dev(1, 0, 0, 0x12348086u, 0x06000000u);
    cfg[1][0][0][PCI_REG_HEADER_TYPE >> 2] = 0x00000000u;

    set_dev(0, 5, 0, 0x813910ECu, 0x02000000u);
    cfg[0][5][0][1] = 0x00000007u;
    cfg[0][5][0][4] = 0xC0010001u;
    cfg[0][5][0][PCI_REG_HEADER_TYPE >> 2] = 0x00000000u;
    set_dev(0, 9, 0, 0x10011AF4u, 0x01000000u);
    cfg[0][9][0][PCI_REG_HEADER_TYPE >> 2] = 0x00000000u;
    set_dev(0, 20, 0, 0x12348086u, 0x06040000u);
    cfg[0][20][0][PCI_REG_HEADER_TYPE >> 2] = 0x00000000u;
    cfg[0][20][0][6] = 0x00000001u;
    cfg[0][20][0][PCI_REG_BRIDGE_SECONDARY >> 2] = 0x00010100u;

    set_dev(1, 3, 0, 0x10001B36u, 0x0C033000u);
    cfg[1][3][0][PCI_REG_HEADER_TYPE >> 2] = 0x00000080u;
    set_dev(1, 3, 1, 0x10021B36u, 0x0C033000u);
    set_dev(2, 1, 0, 0x55555555u, 0x0A000000u);
    cfg[2][1][0][PCI_REG_HEADER_TYPE >> 2] = 0x00000000u;

    CHECK(pci_find(0x10ECu, 0x8139u, fake_inl, fake_outl) == 5, "find rtl8139");
    CHECK(pci_find(0x1AF4u, 0x1001u, fake_inl, fake_outl) == 9, "find virtio-blk");
    CHECK(pci_find(0x1234u, 0x5678u, fake_inl, fake_outl) == -1, "find miss");

    CHECK(pci_cfg_read(0, 5, 0, 4, fake_outl, fake_inl) == 0x00000007u, "read cmd");
    pci_cfg_write(0, 5, 0, 4, 0x00000003u, fake_outl);
    CHECK(cfg[0][5][0][1] == 0x00000003u, "write cmd");
    CHECK(pci_cfg_read(0, 5, 0, 0x11, fake_outl, fake_inl) == cfg[0][5][0][4], "read aligns reg");

    CHECK(pci_present(0, 5, 0, fake_outl, fake_inl), "present dev 5");
    CHECK(!pci_present(0, 6, 0, fake_outl, fake_inl), "absent dev 6");
    CHECK(!pci_present(3, 0, 0, fake_outl, fake_inl), "absent bus");

    CHECK(pci_is_multifunction(1, 3, fake_outl, fake_inl), "multifunc bit read");
    CHECK(!pci_is_multifunction(0, 5, fake_outl, fake_inl), "single func bit clear");
    CHECK(pci_cfg_read8(0, 20, 0, PCI_REG_BRIDGE_SECONDARY, fake_outl, fake_inl)
          == 1u, "read secondary bus byte");

    CHECK(pci_class_matches(1, 3, 0, PCI_CLASS_XHCI, PCI_SUBCLASS_XHCI,
                            PCI_PROGIF_XHCI, fake_outl, fake_inl),
          "class triple match");
    CHECK(!pci_class_matches(1, 3, 0, PCI_CLASS_XHCI, PCI_SUBCLASS_XHCI,
                             0x31u, fake_outl, fake_inl),
          "class triple prog-if mismatch rejected");
    CHECK(pci_class_matches(1, 3, 0, PCI_CLASS_XHCI, PCI_SUBCLASS_XHCI,
                            PCI_CLASS_ANY, fake_outl, fake_inl),
          "class triple wildcard prog-if");
    CHECK(!pci_class_matches(2, 1, 0, PCI_CLASS_XHCI, PCI_SUBCLASS_XHCI,
                             PCI_PROGIF_XHCI, fake_outl, fake_inl),
          "class triple non-xhci rejected");

    CHECK(pci_find_class(&bdf, PCI_CLASS_XHCI, PCI_SUBCLASS_XHCI,
                         PCI_PROGIF_XHCI, fake_outl, fake_inl),
          "walk finds xhci behind a bridge");
    CHECK(bdf.bus == 1 && bdf.dev == 3 && bdf.func == 0,
          "xhci is bus 1 dev 3 func 0");
    bdf.bus = 99;
    CHECK(pci_find_class(&bdf, 0x99, 0x99, 0x99, fake_outl, fake_inl) == 0,
          "walk miss returns 0");
    CHECK(bdf.bus == 0 && bdf.dev == 0 && bdf.func == 0,
          "walk miss zeroes the result");
    CHECK(pci_find_class(&bdf, PCI_CLASS_ANY, PCI_CLASS_ANY, PCI_CLASS_ANY,
                         fake_outl, fake_inl),
          "wildcard walk finds something");
    CHECK(pci_find_class(&bdf, PCI_CLASS_ANY, PCI_SUBCLASS_PCI_BRIDGE,
                         PCI_CLASS_ANY, fake_outl, fake_inl),
          "wildcard class finds the bridge by subclass");
    CHECK(bdf.bus == 0 && bdf.dev == 20, "the bridge is bus 0 dev 20");
    bdf.bus = 77;
    CHECK(pci_find_class(&bdf, 0x08, 0x06, 0x50, fake_outl, fake_inl) == 0,
          "mass-storage class is absent from the fake tree");

    cfg[0][9][0][PCI_REG_BAR0 >> 2] = 0xE0000000u | PCI_BAR_64BIT;
    cfg[0][9][0][(PCI_REG_BAR0 >> 2) + 1] = 0x00000000u;
    bar_mask[0][9][0][PCI_REG_BAR0 >> 2] = 0xFFFFF000u;
    bar_mask[0][9][0][(PCI_REG_BAR0 >> 2) + 1] = 0x00000000u;
    CHECK(pci_bar_size(0, 9, 0, 0, fake_outl, fake_inl) == 0x1000u,
          "64-bit BAR size probe composes both halves");
    CHECK(cfg[0][9][0][PCI_REG_BAR0 >> 2] == (0xE0000000u | PCI_BAR_64BIT),
          "BAR size probe restores the low half");
    CHECK(cfg[0][9][0][(PCI_REG_BAR0 >> 2) + 1] == 0u,
          "BAR size probe restores the high half");

    /* A window above 4 GB implements every low-order address line, so the
     * low half masks to zero and only the high half carries the count. A low
     * half that still has an unimplemented line means the window is below
     * 4 GB, whatever the high half says. */
    bar_mask[0][9][0][PCI_REG_BAR0 >> 2] = 0x00000000u;
    bar_mask[0][9][0][(PCI_REG_BAR0 >> 2) + 1] = 0xFFFFFF00u;
    CHECK(pci_bar_size(0, 9, 0, 0, fake_outl, fake_inl) == (1ULL << 40),
          "64-bit BAR above 4 GB counts the high half");
    bar_mask[0][9][0][(PCI_REG_BAR0 >> 2) + 1] = 0xFFFFFFFFu;
    CHECK(pci_bar_size(0, 9, 0, 0, fake_outl, fake_inl) == 0u,
          "64-bit BAR with no unimplemented line is refused");
    /* QEMU's xHCI shape: a 16 KB window, low half carrying the count, high
     * half all ones. Reading the high half as the answer reports 2^32 here
     * and refuses the controller. */
    bar_mask[0][9][0][PCI_REG_BAR0 >> 2] = 0xFFFFC000u;
    CHECK(pci_bar_size(0, 9, 0, 0, fake_outl, fake_inl) == 0x4000u,
          "low half decides a below-4GB 64-bit BAR");
    bar_mask[0][9][0][PCI_REG_BAR0 >> 2] = 0xFFFFF000u;
    bar_mask[0][9][0][(PCI_REG_BAR0 >> 2) + 1] = 0x00000000u;

    cfg[0][9][0][PCI_REG_BAR0 >> 2] = 0xE0000000u;
    bar_mask[0][9][0][PCI_REG_BAR0 >> 2] = 0xFFFF0000u;
    CHECK(pci_bar_size(0, 9, 0, 0, fake_outl, fake_inl) == 0x10000u,
          "32-bit BAR size probe ignores the non-existent high half");
    CHECK(cfg[0][9][0][PCI_REG_BAR0 >> 2] == 0xE0000000u,
          "32-bit BAR probe does not write a high half");

    bar_mask[0][9][0][PCI_REG_BAR0 >> 2] = 0x00000000u;
    CHECK(pci_bar_size(0, 9, 0, 0, fake_outl, fake_inl) == 0u,
          "a BAR with no address bits is refused");

    CHECK(pci_bar_size_from_mask(0xFFFFF000ull) == 0x1000u,
          "mask decode of a 4 KB window");
    CHECK(pci_bar_size_from_mask(0xFFFF0000ull) == 0x10000u,
          "mask decode of a 64 KB window");
    CHECK(pci_bar_size_from_mask(0xFFFFFF00ull) == 0x100ull,
          "mask decode of a 256-byte window");
    CHECK(pci_bar_size_from_mask(0x00000000ull) == 0u,
          "all-zero mask is refused");
    CHECK(pci_bar_size_from_mask(0xFFFFFFFFFFFFC000ull) == 0x4000u,
          "low half decides a below-4GB 64-bit BAR");
    CHECK(pci_bar_size_from_mask(0xFFFFFF0000000000ull) == (1ULL << 40),
          "high half decides an above-4GB 64-bit BAR");
    CHECK(pci_bar_size_from_mask(0xFFFFFFFF00000000ull) == 0u,
          "no unimplemented line in either half is refused");

    cfg[0][5][0][PCI_REG_BAR0 >> 2] = 0xE0000001u;
    CHECK(pci_bar_size(0, 5, 0, 0, fake_outl, fake_inl) == 0u,
          "I/O BAR has no MMIO size");
    CHECK(cfg[0][5][0][PCI_REG_BAR0 >> 2] == 0xE0000001u,
          "I/O BAR value restored");

    CHECK(pci_bar_size(0, 6, 0, 0, fake_outl, fake_inl) == 0u,
          "absent function has no BAR size");

    cfg[0][9][0][PCI_REG_BAR0 >> 2] = 0xE0000000u | PCI_BAR_64BIT;
    CHECK(pci_bar_relocate(0, 9, 0, 0, 0x18000000ull, fake_outl, fake_inl),
          "relocate 64-bit BAR accepted");
    CHECK(cfg[0][9][0][PCI_REG_BAR0 >> 2] == (0x18000000u | PCI_BAR_64BIT),
          "relocate wrote the address and kept the type bits");
    CHECK(cfg[0][9][0][(PCI_REG_BAR0 >> 2) + 1] == 0u,
          "relocate zeroed the high half");
    CHECK(!pci_bar_relocate(0, 5, 0, 0, 0x18000000ull, fake_outl, fake_inl),
          "relocate refuses an I/O BAR");
    CHECK(!pci_bar_relocate(0, 6, 0, 0, 0x18000000ull, fake_outl, fake_inl),
          "relocate refuses an absent function");

    pci_bar_restore(0, 9, 0, 0, 0xE0000000u | PCI_BAR_64BIT, 0u, fake_outl);
    CHECK(cfg[0][9][0][PCI_REG_BAR0 >> 2] == (0xE0000000u | PCI_BAR_64BIT),
          "BAR restore puts the firmware value back");

    cfg[0][5][0][PCI_REG_BAR0 >> 2] = 0xE0000000u;
    CHECK(pci_bar_is_io(0, 5, 0, 0, fake_outl, fake_inl) == 0,
          "memory BAR is not I/O");
    CHECK(pci_bar_is_64bit(0, 5, 0, 0, fake_outl, fake_inl) == 0,
          "32-bit BAR reports 64-bit clear");

    if (failures == 0)
        printf("pci: ok\n");
    return failures != 0;
}
