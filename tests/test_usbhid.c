/** Docstring: Host test for the USB HID driver (make test-usbhid).
 *
 * Compiles the real drivers/usbhid.c (plus drivers/xhci.c for its transfer
 * API) against tests/stubs/kernel.h, so the usage-to-set-1 table, the report
 * differ and the mouse decoder run on the host with no QEMU boot. Verifies
 * the letter/digit rows of the table (HID usages are not set-1 codes above
 * or below 0x28, so identity mapping would mistype), the E0 decisions, the
 * breaks-before-makes ordering, slot-move silence, modifier press/release
 * and the mouse motion/button/wheel decode including the signed nibble.
 */

#include <stdio.h>
#include <string.h>

#include "drivers/usbhid.h"

unsigned long stub_ms_now;

static unsigned char fed[256];
static int fed_n;

int kbd_feed_scancode(unsigned char sc) {
    if (fed_n < (int)sizeof(fed)) fed[fed_n++] = sc;
    return sc;
}

static unsigned char queued[256];
static int queued_n;

void kbd_q_push(unsigned char c) {
    if (queued_n < (int)sizeof(queued)) queued[queued_n++] = c;
}

#include "drivers/xhci.c"
#include "drivers/usbhid.c"

mouse_state_t mouse_state;

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

static void check_usage(unsigned usage, unsigned char want_sc, int want_e0,
                        const char *msg) {
    unsigned char sc = 0;
    int e0 = -1;
    int ok = usbhid_set1_from_usage(usage, &sc, &e0);
    if (!ok || sc != want_sc || e0 != want_e0) {
        failures++;
        fprintf(stderr, "FAIL: %s (line %d)\n", msg, __LINE__);
    }
}

int main(void) {
    unsigned char prev[HID_KBD_REPORT_LEN];
    unsigned char cur[HID_KBD_REPORT_LEN];
    unsigned char out[USBHID_MAX_SCANCODES];
    int dx;
    int dy;
    int buttons;
    int wheel;
    int n;
    int i;

    check_usage(0x04, 0x1E, 0, "a maps to set-1 0x1E");
    check_usage(0x05, 0x30, 0, "b maps to set-1 0x30");
    check_usage(0x1D, 0x2C, 0, "z maps to set-1 0x2C");
    check_usage(0x1E, 0x02, 0, "1 maps to set-1 0x02");
    check_usage(0x27, 0x0B, 0, "0 maps to set-1 0x0B");
    check_usage(0x28, 0x1C, 0, "Return maps to set-1 0x1C, not usage 0x28");
    check_usage(0x2B, 0x0F, 0, "Tab maps to set-1 0x0F");
    check_usage(0x39, 0x3A, 0, "CapsLock needs no E0");
    check_usage(0x49, 0x52, 1, "Insert maps to set-1 0x52 with E0");
    check_usage(0x4A, 0x47, 1, "Home maps with E0");
    check_usage(0x4F, 0x4D, 1, "RightArrow needs E0");
    check_usage(0x53, 0x45, 0, "NumLock needs no E0");
    check_usage(0x54, 0x35, 0, "keypad slash is plain");
    check_usage(0x58, 0x1C, 1, "keypad enter needs E0");
    check_usage(0x59, 0x4F, 0, "keypad 1 is plain");
    check_usage(0x65, 0x5D, 1, "Menu key maps with E0");
    CHECK(usbhid_set1_from_usage(0x00, 0, 0) == 0, "usage 0 has no code");
    CHECK(usbhid_set1_from_usage(0x01, 0, 0) == 0, "usage 1 has no code");
    CHECK(usbhid_set1_from_usage(0x48, 0, 0) == 0, "Pause is dropped");
    CHECK(usbhid_set1_from_usage(0x66, 0, 0) == 0, "Power is dropped");
    CHECK(usbhid_set1_from_usage(0x68, 0, 0) == 0, "F13 is dropped");
    CHECK(usbhid_set1_from_usage(0x80, 0, 0) == 0, "usage 0x80 refused");
    for (i = 0x04; i <= 0x27; i++) {
        unsigned char sc = 0;
        int e0 = -1;
        if (!usbhid_set1_from_usage((unsigned)i, &sc, &e0) || e0 != 0) {
            failures++;
            fprintf(stderr, "FAIL: letter/digit %02x unmapped\n", i);
        }
    }

    memset(prev, 0, sizeof(prev));
    memset(cur, 0, sizeof(cur));
    cur[2] = 0x04;
    n = usbhid_kbd_scancodes(prev, cur, out, (int)sizeof(out));
    CHECK(n == 1 && out[0] == 0x1E, "press a emits make 0x1E");
    memcpy(prev, cur, sizeof(prev));
    memset(cur, 0, sizeof(cur));
    n = usbhid_kbd_scancodes(prev, cur, out, (int)sizeof(out));
    CHECK(n == 1 && out[0] == (0x1E | 0x80u), "release a emits break");

    memset(prev, 0, sizeof(prev));
    memset(cur, 0, sizeof(cur));
    cur[2] = 0x04;
    cur[3] = 0x05;
    n = usbhid_kbd_scancodes(prev, cur, out, (int)sizeof(out));
    CHECK(n == 2 && out[0] == 0x1E && out[1] == 0x30,
          "two makes in slot order");

    memset(prev, 0, sizeof(prev));
    prev[2] = 0x04;
    prev[3] = 0x05;
    memset(cur, 0, sizeof(cur));
    cur[2] = 0x05;
    cur[3] = 0x04;
    n = usbhid_kbd_scancodes(prev, cur, out, (int)sizeof(out));
    CHECK(n == 0, "slot reorder emits nothing");

    memset(prev, 0, sizeof(prev));
    prev[2] = 0x04;
    memset(cur, 0, sizeof(cur));
    cur[2] = 0x05;
    n = usbhid_kbd_scancodes(prev, cur, out, (int)sizeof(out));
    CHECK(n == 2 && out[0] == (0x1E | 0x80u) && out[1] == 0x30,
          "break comes before make on a swap");

    memset(prev, 0, sizeof(prev));
    memset(cur, 0, sizeof(cur));
    cur[0] = HID_MOD_LEFT_SHIFT;
    cur[2] = 0x04;
    n = usbhid_kbd_scancodes(prev, cur, out, (int)sizeof(out));
    CHECK(n == 2 && out[0] == 0x2A && out[1] == 0x1E,
          "shift+a emits shift make then a make");

    memset(prev, 0, sizeof(prev));
    prev[0] = HID_MOD_LEFT_SHIFT;
    memset(cur, 0, sizeof(cur));
    n = usbhid_kbd_scancodes(prev, cur, out, (int)sizeof(out));
    CHECK(n == 1 && out[0] == (0x2A | 0x80u), "shift release emits break");

    memset(prev, 0, sizeof(prev));
    memset(cur, 0, sizeof(cur));
    cur[0] = HID_MOD_RIGHT_ALT;
    n = usbhid_kbd_scancodes(prev, cur, out, (int)sizeof(out));
    CHECK(n == 2 && out[0] == 0xE0 && out[1] == 0x38,
          "right alt emits E0 prefix plus make");

    {
        unsigned char mprev[HID_MOUSE_REPORT_LEN] = { 0, 0, 0, 0 };
        unsigned char mcur[HID_MOUSE_REPORT_LEN] = { 0x01, 10, 0xFD, 0x0F };
        usbhid_mouse_decode(mprev, mcur, &dx, &dy, &buttons, &wheel);
        CHECK(dx == 10 && dy == -3 && buttons == 1 && wheel == -1,
              "mouse decodes motion buttons and signed wheel");
    }

    if (failures == 0) printf("usbhid: ok\n");
    return failures != 0;
}
