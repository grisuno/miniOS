/** Docstring: Host test for the xHCI controller driver (make test-xhci).
 *
 * Compiles the real drivers/xhci.c against tests/stubs/kernel.h, so the
 * hardware-independent parts run on the host with no QEMU boot. Verifies
 * the load-bearing TRB size (a 24-byte TRB spaces every ring wrong and the
 * controller walks garbage), the endpoint-address to DCI mapping the
 * doorbells and contexts share, and the configuration-descriptor walk with
 * its wildcard match and its refusal of truncated descriptors.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "drivers/xhci.h"

unsigned long stub_ms_now;

#include "drivers/xhci.c"

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

int main(void) {
    xhc_iface_t iface;
    unsigned char *cfg;
    int ok;

    CHECK(sizeof(xhc_trb_t) == 16, "TRB is 16 bytes");
    CHECK(XHC_TRB_RING_TRBS * sizeof(xhc_trb_t) == 16384u, "ring is 16 KB");

    CHECK(xhc_dci(0x00) == 1, "EP0 rings doorbell target 1");
    CHECK(xhc_dci(0x01) == 2, "EP1 OUT is DCI 2");
    CHECK(xhc_dci(0x81) == 3, "EP1 IN is DCI 3");
    CHECK(xhc_dci(0x02) == 4, "EP2 OUT is DCI 4");
    CHECK(xhc_dci(0x82) == 5, "EP2 IN is DCI 5");

    xhc_devs[0].used = 1;
    xhc_devs[0].config = (unsigned char *)malloc(XHC_MAX_CONFIG_DESC);
    CHECK(xhc_devs[0].config != 0, "config scratch allocated");
    cfg = xhc_devs[0].config;
    cfg[0] = 9;
    cfg[1] = 2;
    cfg[2] = 48;
    cfg[3] = 0;
    cfg[4] = 2;
    cfg[5] = 1;
    cfg[6] = 0;
    cfg[7] = 0x40;
    cfg[8] = 0;
    cfg[9] = 9;
    cfg[10] = 4;
    cfg[11] = 0;
    cfg[12] = 0;
    cfg[13] = 1;
    cfg[14] = 3;
    cfg[15] = 1;
    cfg[16] = 1;
    cfg[17] = 0;
    cfg[18] = 7;
    cfg[19] = 5;
    cfg[20] = 0x81;
    cfg[21] = 3;
    cfg[22] = 8;
    cfg[23] = 0;
    cfg[24] = 10;
    cfg[25] = 9;
    cfg[26] = 4;
    cfg[27] = 1;
    cfg[28] = 0;
    cfg[29] = 2;
    cfg[30] = 8;
    cfg[31] = 6;
    cfg[32] = 0x50;
    cfg[33] = 0;
    cfg[34] = 7;
    cfg[35] = 5;
    cfg[36] = 0x02;
    cfg[37] = 2;
    cfg[38] = 0;
    cfg[39] = 2;
    cfg[40] = 0;
    cfg[41] = 7;
    cfg[42] = 5;
    cfg[43] = 0x83;
    cfg[44] = 2;
    cfg[45] = 0;
    cfg[46] = 2;
    cfg[47] = 0;
    xhc_devs[0].config_len = 48;

    memset(&iface, 0xAA, sizeof(iface));
    ok = xhc_open_interface(0, XHC_CLASS_HID, XHC_SUBCLASS_BOOT, 0xFFu,
                            &iface);
    CHECK(ok == 1 && iface.num_eps == 1 && iface.ep_addr[0] == 0x81 &&
          iface.ep_maxp[0] == 8, "HID boot interface matches wildcard");
    CHECK(iface.ep_type[0] == 3, "interrupt endpoint type decodes as 3");

    memset(&iface, 0, sizeof(iface));
    ok = xhc_open_interface(0, XHC_CLASS_MASS_STORAGE, XHC_SUBCLASS_SCSI,
                            XHC_PROTOCOL_BULK_ONLY, &iface);
    CHECK(ok == 1 && iface.num_eps == 2 && iface.ep_addr[0] == 0x02 &&
          iface.ep_addr[1] == 0x83, "BOT interface matches with two bulk EPs");

    memset(&iface, 0, sizeof(iface));
    ok = xhc_open_interface(0, 0xFFu, 0xFFu, 0xFFu, &iface);
    CHECK(ok == 1 && iface.ep_addr[0] == 0x81,
          "all-wildcard matches the first interface with an endpoint");

    cfg[9] = 0;
    memset(&iface, 0, sizeof(iface));
    ok = xhc_open_interface(0, XHC_CLASS_HID, XHC_SUBCLASS_BOOT, 0xFFu,
                            &iface);
    CHECK(ok == 0, "zero-length interface descriptor ends the walk");

    if (failures == 0) printf("xhci: ok\n");
    return failures != 0;
}
