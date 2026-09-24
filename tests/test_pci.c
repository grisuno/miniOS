/** Docstring: Host test for headers/drivers/pci.h (make test-pci).
 *
 * Drives the config-space helpers against a fake 32-device bus.
 * Verifies find by vendor/device, find-miss, read/write roundtrip
 * and dword alignment masking, so a mutant that breaks the CF8
 * address composition dies on the host with no QEMU boot.
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

static unsigned cfg[32][64];
static unsigned last_addr;

static void fake_outl(unsigned short port, unsigned val) {
    if (port == PCI_CFG_ADDR)
        last_addr = val;
    else if (port == PCI_CFG_DATA) {
        unsigned dev = (last_addr >> 11) & 31u;
        unsigned reg = (last_addr & 0xFCu) >> 2;
        if (dev < 32 && reg < 64)
            cfg[dev][reg] = val;
    }
}

static unsigned fake_inl(unsigned short port) {
    if (port == PCI_CFG_DATA) {
        unsigned dev = (last_addr >> 11) & 31u;
        unsigned reg = (last_addr & 0xFCu) >> 2;
        if (dev < 32 && reg < 64)
            return cfg[dev][reg];
        return 0xFFFFFFFFu;
    }
    return 0;
}

int main(void) {
    unsigned i;
    for (i = 0; i < 32; i++) {
        unsigned k;
        for (k = 0; k < 64; k++)
            cfg[i][k] = 0xFFFFFFFFu;
    }
    cfg[5][0] = 0x813910ECu;
    cfg[5][1] = 0x00000007u;
    cfg[5][4] = 0xC0010001u;
    cfg[9][0] = 0x10011AF4u;

    CHECK(pci_find(0x10ECu, 0x8139u, fake_inl, fake_outl) == 5, "find rtl8139");
    CHECK(pci_find(0x1AF4u, 0x1001u, fake_inl, fake_outl) == 9, "find virtio-blk");
    CHECK(pci_find(0x1234u, 0x5678u, fake_inl, fake_outl) == -1, "find miss");

    CHECK(pci_cfg_read(0, 5, 0, 4, fake_outl, fake_inl) == 0x00000007u, "read cmd");
    pci_cfg_write(0, 5, 0, 4, 0x00000003u, fake_outl);
    CHECK(cfg[5][1] == 0x00000003u, "write cmd");
    CHECK(pci_cfg_read(0, 5, 0, 0x11, fake_outl, fake_inl) == cfg[5][4], "read aligns reg");

    if (failures == 0)
        printf("pci: ok\n");
    return failures != 0;
}
