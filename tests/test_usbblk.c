/** Docstring: Host test for the USB mass-storage driver (make test-usbblk).
 *
 * Compiles the real drivers/usbblk.c (plus drivers/xhci.c for its transfer
 * API) against tests/stubs/kernel.h, so the Bulk-Only Transport framing
 * runs on the host with no QEMU boot. Verifies the CBW field layout
 * (signature, tag and length in little-endian, direction flag, ten-byte
 * CDB with big-endian LBA and block count) and the CSW acceptance rule
 * (signature, tag, zero residue, passed status).
 */

#include <stdio.h>

#include "driver.h"
#include "drivers/usbblk.h"

unsigned long stub_ms_now;

static int registered;

int device_register(device_t *dev) {
    (void)dev;
    registered++;
    return 0;
}

device_t *device_find(const char *name) {
    (void)name;
    return 0;
}

#include "drivers/xhci.c"
#include "drivers/usbblk.c"

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

int main(void) {
    unsigned char cbw[31];
    unsigned char csw[13];

    ubk_build_cbw(cbw, 0x12345678u, 0x01020304u, 16, 1, 8192);
    CHECK(cbw[0] == 0x55 && cbw[1] == 0x53 && cbw[2] == 0x42 &&
          cbw[3] == 0x43, "CBW signature 0x43425355");
    CHECK(cbw[4] == 0x78 && cbw[5] == 0x56 && cbw[6] == 0x34 &&
          cbw[7] == 0x12, "CBW tag little-endian");
    CHECK(cbw[8] == 0x00 && cbw[9] == 0x20 && cbw[10] == 0x00 &&
          cbw[11] == 0x00, "CBW length 8192 little-endian");
    CHECK(cbw[12] == 0x80, "CBW read flag set for device-to-host");
    CHECK(cbw[13] == 0 && cbw[14] == 10, "CBW LUN zero and CDB length 10");
    CHECK(cbw[15] == 0x28, "CBW CDB is READ(10)");
    CHECK(cbw[17] == 0x01 && cbw[18] == 0x02 && cbw[19] == 0x03 &&
          cbw[20] == 0x04, "CBW CDB LBA big-endian");
    CHECK(cbw[22] == 0x00 && cbw[23] == 0x10, "CBW CDB blocks big-endian");

    ubk_build_cbw(cbw, 1, 0, 1, 0, 512);
    CHECK(cbw[12] == 0x00, "CBW write flag clear for host-to-device");
    CHECK(cbw[15] == 0x2A, "CBW CDB is WRITE(10)");

    csw[0] = 0x55;
    csw[1] = 0x53;
    csw[2] = 0x42;
    csw[3] = 0x53;
    csw[4] = 0x78;
    csw[5] = 0x56;
    csw[6] = 0x34;
    csw[7] = 0x12;
    csw[8] = 0;
    csw[9] = 0;
    csw[10] = 0;
    csw[11] = 0;
    csw[12] = 0;
    CHECK(ubk_check_csw(csw, 0x12345678u, 8192) == 1, "good CSW accepted");
    csw[0] ^= 0xFF;
    CHECK(ubk_check_csw(csw, 0x12345678u, 8192) == 0, "bad signature refused");
    csw[0] ^= 0xFF;
    csw[4] ^= 0xFF;
    CHECK(ubk_check_csw(csw, 0x12345678u, 8192) == 0, "wrong tag refused");
    csw[4] ^= 0xFF;
    csw[8] = 0x01;
    CHECK(ubk_check_csw(csw, 0x12345678u, 8192) == 0, "residue refused");
    csw[8] = 0x00;
    csw[12] = 0x01;
    CHECK(ubk_check_csw(csw, 0x12345678u, 8192) == 0, "failed status refused");
    CHECK(ubk_check_csw(0, 0, 0) == 0, "null CSW refused");

    if (failures == 0) printf("usbblk: ok\n");
    return failures != 0;
}
