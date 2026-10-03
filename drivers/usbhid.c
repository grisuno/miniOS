/* usbhid.c -- USB HID boot-protocol keyboard and mouse.
 *
 * Both device classes report *state*, not events: a keyboard report is the
 * set of keys held right now, a mouse report is where the pointer is and
 * which buttons are down. So this driver differences each report against the
 * previous one and synthesises the make and break events a PS/2 controller
 * would have produced, then pushes them through the existing keyboard decode
 * path. That is the whole integration strategy: MiniOS keeps one keyboard
 * path, with the window manager's combos, the AltGr layer and both layouts
 * upstream of the injection point rather than forked into it.
 *
 * The usage-to-scancode table is the part that has to be right. HID usage ids
 * coincide with scancode set 1 only from 0x04 to 0x27. Above that they
 * diverge -- usage 0x28 is Return while set-1 Return is 0x1C -- so a table
 * exists for everything from 0x28 up. The table also decides when the 0xE0
 * prefix has to be synthesised, because a USB keyboard sends the navigation
 * cluster and the keypad unprefixed while set-1 uses the prefix to tell them
 * from their left-hand twins.
 *
 * The decoders below are pure functions over two reports: no hardware, no
 * kernel state, no allocation. That is what makes them host-testable, and it
 * is where a bug would otherwise hide -- a wrong scancode types a character
 * nobody pressed, and nothing in a QEMU run would show it.
 */

#include "kernel.h"
#include "arch/x86/hal_io.h"
#include "drivers/xhci.h"
#include "drivers/usbhid.h"
#include "drivers/kbd.h"
#include "drivers/modifiers.h"
#include "vga_fb.h"

/* ---- One HID keyboard and one HID mouse is what this kernel drives ---- */
#define USBHID_MAX_DEVS 2

/** Docstring: A claimed HID interface: the device record, the endpoint index
 * that serves it, and the previous report so the next one can be
 * differenced against it. */
typedef struct {
    int used;
    int device;
    int ep_index;
    int ep_in;
    unsigned ep_maxp;
    unsigned char prev[USBHID_MAX_REPORT_LEN];
    unsigned char *rep;
    int token;
    int is_mouse;
} usbhid_dev_t;

/** Docstring: Endpoint interval in the units the context field counts. One
 * frame at high speed, one millisecond at full speed: the smallest values
 * that do not lose reports on a busy bus. */
#define USBHID_INTERVAL 1u

static usbhid_dev_t usbhid_kbd[USBHID_MAX_DEVS];
static usbhid_dev_t usbhid_mouse[USBHID_MAX_DEVS];
static usbhid_counters_t usbhid_ctr;

/* ---- Usage to scancode set 1 ---- */

/** Docstring: Set-1 make code for a HID usage, designated by the usage it
 * translates so no entry can be counted into the wrong row. HID usages are
 * not set-1 codes: usage 0x04 is the letter a while set-1 0x04 is the digit
 * 3, so every usage carries its own entry. */
static const unsigned char usbhid_usage_sc[0x80] = {
    [0x04] = 0x1E, [0x05] = 0x30, [0x06] = 0x2E, [0x07] = 0x20,
    [0x08] = 0x12, [0x09] = 0x21, [0x0A] = 0x22, [0x0B] = 0x23,
    [0x0C] = 0x17, [0x0D] = 0x24, [0x0E] = 0x25, [0x0F] = 0x26,
    [0x10] = 0x32, [0x11] = 0x31, [0x12] = 0x18, [0x13] = 0x19,
    [0x14] = 0x10, [0x15] = 0x13, [0x16] = 0x1F, [0x17] = 0x14,
    [0x18] = 0x16, [0x19] = 0x2F, [0x1A] = 0x11, [0x1B] = 0x2D,
    [0x1C] = 0x15, [0x1D] = 0x2C,
    [0x1E] = 0x02, [0x1F] = 0x03, [0x20] = 0x04, [0x21] = 0x05,
    [0x22] = 0x06, [0x23] = 0x07, [0x24] = 0x08, [0x25] = 0x09,
    [0x26] = 0x0A, [0x27] = 0x0B,
    [0x28] = 0x1C, [0x29] = 0x1B, [0x2A] = 0x0E, [0x2B] = 0x0F,
    [0x2C] = 0x39, [0x2D] = 0x0C, [0x2E] = 0x0D, [0x2F] = 0x1A,
    [0x30] = 0x1B, [0x31] = 0x2B, [0x32] = 0x2B, [0x33] = 0x27,
    [0x34] = 0x28, [0x35] = 0x29, [0x36] = 0x33, [0x37] = 0x34,
    [0x38] = 0x35, [0x39] = 0x3A, [0x3A] = 0x3B, [0x3B] = 0x3C,
    [0x3C] = 0x3D, [0x3D] = 0x3E, [0x3E] = 0x3F, [0x3F] = 0x40,
    [0x40] = 0x41, [0x41] = 0x42, [0x42] = 0x43, [0x43] = 0x44,
    [0x44] = 0x57, [0x45] = 0x58, [0x46] = 0x37, [0x47] = 0x46,
    [0x49] = 0x52, [0x4A] = 0x47, [0x4B] = 0x49,
    [0x4C] = 0x53, [0x4D] = 0x4F, [0x4E] = 0x51, [0x4F] = 0x4D,
    [0x50] = 0x4B, [0x51] = 0x50, [0x52] = 0x48,
    [0x53] = 0x45,
    [0x54] = 0x35, [0x55] = 0x37, [0x56] = 0x4A, [0x57] = 0x4E,
    [0x58] = 0x1C,
    [0x59] = 0x4F, [0x5A] = 0x50, [0x5B] = 0x51, [0x5C] = 0x4B,
    [0x5D] = 0x4C, [0x5E] = 0x4D, [0x5F] = 0x47, [0x60] = 0x48,
    [0x61] = 0x49, [0x62] = 0x52, [0x63] = 0x53,
    [0x65] = 0x5D
};

/** Docstring: Usages that need the 0xE0 prefix in scancode set 1: the
 * navigation cluster, the menu key and the keypad enter. Keypad digits and
 * operators are plain codes, exactly like their main-block twins. */
static const unsigned char usbhid_usage_e0[0x80] = {
    [0x46] = 1, [0x49] = 1, [0x4A] = 1, [0x4B] = 1, [0x4C] = 1,
    [0x4D] = 1, [0x4E] = 1, [0x4F] = 1, [0x50] = 1, [0x51] = 1,
    [0x52] = 1, [0x58] = 1, [0x65] = 1
};

/** Docstring: Modifier bit to set-1 make code. Index follows the HID
 * bitfield order: left control, shift, alt, GUI, then the right-hand set. */
static const unsigned char usbhid_mod_sc[8] = {
    0x1D, 0x2A, 0x38, 0x5B, 0x1D, 0x36, 0x38, 0x5C
};

/** Docstring: Which modifier bits need the 0xE0 prefix. Right Ctrl, Right Alt
 * and both GUI keys do; left ones never do. */
static const unsigned char usbhid_mod_e0[8] = { 0, 0, 0, 0, 1, 0, 1, 1 };

int usbhid_set1_from_usage(unsigned usage, unsigned char *sc, int *e0) {
    if (usage >= 0x80u) return 0;
    if (!usbhid_usage_sc[usage]) return 0;
    if (sc) *sc = usbhid_usage_sc[usage];
    if (e0) *e0 = usbhid_usage_e0[usage] ? 1 : 0;
    return 1;
}

/** Docstring: Set-1 make code for any usage, 0x04..0xDD. Returns 0 when the
 * usage has no set-1 equivalent so the caller drops it rather than inventing
 * a scancode. */
static int usbhid_usage_make(unsigned usage, unsigned char *sc, int *e0) {
    if (usage < HID_USAGE_MIN || usage > HID_USAGE_MAX) return 0;
    return usbhid_set1_from_usage(usage, sc, e0);
}

/** Docstring: True when a report lists a usage in any slot but the given
 * one. The array is not ordered -- a device may reorder it at any report --
 * so a naive slot-by-slot compare would emit a break for a key that merely
 * moved position, which the keyboard layer sees as the user releasing and
 * re-pressing it. */
static int usbhid_report_has(const unsigned char report[HID_KBD_REPORT_LEN],
                             unsigned usage, int except) {
    int i;
    for (i = 0; i < HID_KBD_SLOTS; i++)
        if (i != except && report[2 + i] == (unsigned char)usage) return 1;
    return 0;
}

/** Docstring: Append one scancode or return USBHID_TRUNCATED.
 *
 * Truncation is a hard signal, not a silent clamp: a half-emitted key event
 * leaves the keyboard layer with a make and no break, which wedges the
 * modifier state for the next report. The buffer is sized so this cannot
 * happen for a legal report, so a report that does reach it is a bug worth
 * seeing. */
static int usbhid_put(unsigned char *out, int max, int n, unsigned char sc) {
    if (n < 0 || n >= max) return USBHID_TRUNCATED;
    out[n] = sc;
    return n + 1;
}

/** Docstring: Append the make or break bytes for one modifier bit.
 *
 * A press is prefix, then make. A release is break, then the prefix break.
 * That asymmetry is not cosmetic: the keyboard decode path treats a break
 * with a pending prefix as "finish the pair", so releasing this way leaves no
 * dangling 0xE0 for the next report to complete by accident. */
static int usbhid_emit_mod(unsigned char *out, int max, int n, unsigned bit,
                           int pressed) {
    unsigned char sc = usbhid_mod_sc[bit];
    int e0 = usbhid_mod_e0[bit];
    if (pressed) {
        if (e0) {
            n = usbhid_put(out, max, n, 0xE0);
            if (n < 0) return n;
        }
        return usbhid_put(out, max, n, sc);
    }
    n = usbhid_put(out, max, n, (unsigned char)(sc | 0x80u));
    if (n < 0) return n;
    if (e0) n = usbhid_put(out, max, n, 0xE0 | 0x80u);
    return n;
}

/** Docstring: Append the make or break bytes for one usage. */
static int usbhid_emit_usage(unsigned char *out, int max, int n,
                             unsigned usage, int pressed) {
    unsigned char sc;
    int e0;
    if (!usbhid_usage_make(usage, &sc, &e0)) return n;
    if (pressed) {
        if (e0) {
            n = usbhid_put(out, max, n, 0xE0);
            if (n < 0) return n;
        }
        return usbhid_put(out, max, n, sc);
    }
    n = usbhid_put(out, max, n, (unsigned char)(sc | 0x80u));
    if (n < 0) return n;
    if (e0) n = usbhid_put(out, max, n, 0xE0 | 0x80u);
    return n;
}

/** Docstring: How many scancodes a keyboard report transition can produce at
 * worst: six keys each able to emit prefix plus make or break plus prefix
 * break, plus eight modifier bits. Sized so the buffer is never the limit. */
#define USBHID_MAX_SCANCODES (2 * HID_KBD_SLOTS * 3 + 8 * 2)

int usbhid_kbd_scancodes(const unsigned char prev[HID_KBD_REPORT_LEN],
                         const unsigned char cur[HID_KBD_REPORT_LEN],
                         unsigned char *out, int max) {
    int n = 0;
    int bit;
    int i;
    if (!prev || !cur || !out || max <= 0) return 0;
    /* Breaks before makes for both groups: a burst that changes several keys
     * at once must not look like a held-key repeat to the layer above, and
     * the modifier bits have to settle before the keys are decoded. */
    for (bit = 0; bit < 8; bit++) {
        unsigned char mask = HID_MODIFIER_BIT(bit + 1u);
        if ((prev[0] & mask) && !(cur[0] & mask))
            n = usbhid_emit_mod(out, max, n, (unsigned)bit, 0);
    }
    for (i = 0; i < HID_KBD_SLOTS; i++) {
        unsigned char p = prev[2 + i];
        unsigned char c = cur[2 + i];
        if (p && p != c && !usbhid_report_has(cur, p, i))
            n = usbhid_emit_usage(out, max, n, p, 0);
    }
    for (bit = 0; bit < 8; bit++) {
        unsigned char mask = HID_MODIFIER_BIT(bit + 1u);
        if (!(prev[0] & mask) && (cur[0] & mask))
            n = usbhid_emit_mod(out, max, n, (unsigned)bit, 1);
    }
    for (i = 0; i < HID_KBD_SLOTS; i++) {
        unsigned char p = prev[2 + i];
        unsigned char c = cur[2 + i];
        if (c && c != p && !usbhid_report_has(prev, c, i))
            n = usbhid_emit_usage(out, max, n, c, 1);
    }
    return n;
}

void usbhid_mouse_decode(const unsigned char prev[HID_MOUSE_REPORT_LEN],
                         const unsigned char cur[HID_MOUSE_REPORT_LEN],
                         int *dx, int *dy, int *buttons, int *wheel) {
    if (dx) *dx = (int)(signed char)cur[1];
    if (dy) *dy = (int)(signed char)cur[2];
    if (buttons) *buttons = (int)(cur[0] & HID_MOUSE_BUTTON_MASK);
    if (wheel) {
        /* The wheel is a signed four-bit field in the low nibble; the high
         * nibble of byte 3 is unused on a three-button mouse and must not
         * leak into the count. */
        *wheel = (int)(signed char)((cur[3] << 4)) >> 4;
        (void)prev;
    }
}

int usbhid_keyboard_present(void) {
    int i;
    for (i = 0; i < USBHID_MAX_DEVS; i++)
        if (usbhid_kbd[i].used) return 1;
    return 0;
}

int usbhid_mouse_present(void) {
    int i;
    for (i = 0; i < USBHID_MAX_DEVS; i++)
        if (usbhid_mouse[i].used) return 1;
    return 0;
}

void usbhid_counters(usbhid_counters_t *out) {
    if (out) *out = usbhid_ctr;
}

int usbhid_press_kbd_report(const unsigned char report[HID_KBD_REPORT_LEN]) {
    usbhid_dev_t *d = usbhid_kbd[0].used ? &usbhid_kbd[0] : 0;
    unsigned char sc[USBHID_MAX_SCANCODES];
    int n;
    if (!d || !report) return 0;
    n = usbhid_kbd_scancodes(d->prev, report, sc, (int)sizeof(sc));
    if (n < 0) return n;
    for (int i = 0; i < n; i++) {
        int c = kbd_feed_scancode(sc[i]);
        if (c >= 0) kbd_q_push((unsigned char)c);
    }
    kmemcpy(d->prev, report, HID_KBD_REPORT_LEN);
    return n;
}

/* ---- Claiming an interface ---- */

/** Docstring: Ask a HID device for boot protocol, so its reports use the fixed
 * layout this driver decodes. Without it a keyboard may answer with the
 * report-descriptor-defined layout, whose key order and size are arbitrary,
 * and every decode above would be a guess. */
static int usbhid_set_boot_protocol(int device, int iface) {
    unsigned char setup[8];
    setup[0] = 0x21;
    setup[1] = HID_REQ_SET_PROTOCOL;
    setup[2] = HID_PROTOCOL_BOOT;
    setup[3] = 0;
    setup[4] = (unsigned char)(iface & 0xFF);
    setup[5] = (unsigned char)((iface >> 8) & 0xFF);
    setup[6] = 0;
    setup[7] = 0;
    return xhc_control(device, setup, 0, 0, 1);
}

/** Docstring: True when an endpoint index is already spoken for. Two HID
 * devices cannot share one endpoint context, so the second claim walks past
 * the first one's index instead of reconfiguring it under the controller's
 * feet. */
static int usbhid_ep_taken(int ep_index) {
    int i;
    for (i = 0; i < USBHID_MAX_DEVS; i++) {
        if (usbhid_kbd[i].used && usbhid_kbd[i].ep_index == ep_index) return 1;
        if (usbhid_mouse[i].used && usbhid_mouse[i].ep_index == ep_index)
            return 1;
    }
    return 0;
}

/** Docstring: Take an interrupt IN endpoint from a claimed interface and
 * program it, at the first free endpoint index. Returns the index, or -1
 * when the interface has no interrupt IN endpoint or none can be configured. */
static int usbhid_take_ep(int device, const xhc_iface_t *iface,
                          int *maxp) {
    int idx;
    for (idx = 1; idx < XHC_EP_INDEX_LIMIT; idx++) {
        int k;
        if (usbhid_ep_taken(idx)) continue;
        for (k = 0; k < iface->num_eps; k++) {
            if (!(iface->ep_addr[k] & XHC_EP_DIR_IN)) continue;
            if (iface->ep_type[k] != XHC_EP_INTERRUPT) continue;
            if (!xhc_configure_endpoint(device, idx, iface->ep_addr[k],
                                        XHC_EP_INTERRUPT,
                                        iface->ep_maxp[k], 1,
                                        USBHID_INTERVAL, 0))
                return -1;
            if (maxp) *maxp = (unsigned)iface->ep_maxp[k];
            return idx;
        }
        return -1;
    }
    return -1;
}

/** Docstring: Claim a HID interface as a keyboard or a mouse.
 *
 * Which one it is comes from the endpoint's packet size, not from a guess on
 * the device name or vendor: a boot keyboard endpoint is eight bytes and a
 * boot mouse endpoint is three or four, and the reports are fixed-length by
 * the boot protocol, so the size is the type. */
static int usbhid_claim(int device, const xhc_iface_t *iface, int is_mouse) {
    usbhid_dev_t *table = is_mouse ? usbhid_mouse : usbhid_kbd;
    int slot;
    int ep_index = 0;
    int maxp = 0;
    for (slot = 0; slot < USBHID_MAX_DEVS; slot++)
        if (!table[slot].used) break;
    if (slot >= USBHID_MAX_DEVS) return 0;
    if (!usbhid_set_boot_protocol(device, iface->iface)) return 0;
    ep_index = usbhid_take_ep(device, iface, &maxp);
    if (ep_index < 0) return 0;
    table[slot].rep = (unsigned char *)kmalloc(USBHID_MAX_REPORT_LEN);
    if (!table[slot].rep) return 0;
    kmm_make_uncached((unsigned long)table[slot].rep, USBHID_MAX_REPORT_LEN);
    table[slot].used = 1;
    table[slot].device = device;
    table[slot].ep_index = ep_index;
    table[slot].ep_in = iface->ep_addr[0];
    table[slot].ep_maxp = (unsigned)maxp;
    table[slot].is_mouse = is_mouse;
    kmemset(table[slot].prev, 0, sizeof(table[slot].prev));
    return 1;
}

/** Docstring: Endpoint packet size that distinguishes a boot keyboard (eight
 * bytes) from a boot mouse (three or four). Anything else is a HID device
 * this driver does not speak, and is left alone rather than misread. */
static int usbhid_is_mouse_maxp(int maxp) {
    return maxp == HID_MOUSE_REPORT_LEN || maxp == HID_MOUSE_REPORT_LEN + 1;
}

int usbhid_init(void) {
    int n = xhc_device_count();
    int d;
    int claimed = 0;
    for (d = 0; d < n; d++) {
        xhc_iface_t iface;
        int in_maxp = 0;
        int k;
        if (!xhc_open_interface(d, XHC_CLASS_HID, XHC_SUBCLASS_BOOT,
                                USBHID_PROTO_NONE, &iface))
            continue;
        for (k = 0; k < iface.num_eps; k++) {
            if (!(iface.ep_addr[k] & XHC_EP_DIR_IN)) continue;
            if (iface.ep_type[k] != XHC_EP_INTERRUPT) continue;
            in_maxp = iface.ep_maxp[k];
            break;
        }
        if (in_maxp == HID_KBD_REPORT_LEN)
            claimed += usbhid_claim(d, &iface, 0);
        else if (usbhid_is_mouse_maxp(in_maxp))
            claimed += usbhid_claim(d, &iface, 1);
    }
    return claimed;
}

/* ---- Polling ---- */

/** Docstring: One interrupt-in report from a device and hand it to a decoder.
 * The request is exactly the boot report size, because xHCI reports no byte
 * count for a non-isochronous transfer: asking for the endpoint's maximum
 * and accepting whatever length came back would be unsound, and asking for
 * the report size is what the boot protocol specifies.
 *
 * Never waits: at most one transfer is outstanding per device, posted on one
 * poll and collected on a later one. An endpoint with nothing to say NAKs,
 * which is not an event but continued silence, so a pending transfer simply
 * stays out until it completes or ages past the budget. Either way this
 * function returns immediately, which is what makes it safe from the tick. */
static int usbhid_poll_one(usbhid_dev_t *d) {
    unsigned char *report;
    unsigned want = d->is_mouse ? HID_MOUSE_REPORT_LEN : HID_KBD_REPORT_LEN;
    int rc;
    if (!d->used) return 0;
    if (!d->rep) return 0;
    if (d->ep_maxp < want) return 0;
    report = d->rep;
    if (d->token) {
        rc = xhc_poll_token_limit(d->token, 0);
        if (rc == 0) return 0;
        d->token = 0;
        if (rc < 0) {
            usbhid_ctr.transfer_errors++;
            return 0;
        }
    } else {
        kmemset(report, 0, USBHID_MAX_REPORT_LEN);
        d->token = xhc_transfer_async(d->device, d->ep_index, report, want);
        return 0;
    }
    if (d->is_mouse) {
        int dx;
        int dy;
        int buttons;
        int wheel;
        usbhid_mouse_decode(d->prev, report, &dx, &dy, &buttons, &wheel);
        if (dx || dy || buttons) {
            irqflags_t flags = spin_save_irq();
            mouse_state.x += dx * HAL_MOUSE_SCALE;
            mouse_state.y -= dy * HAL_MOUSE_SCALE;
            mouse_state.buttons = buttons;
            mouse_state.wheel += wheel;
            mouse_state.present = 1;
            spin_restore_irq(flags);
        }
        usbhid_ctr.mouse_reports++;
        kmemcpy(d->prev, report, HID_MOUSE_REPORT_LEN);
    } else {
        unsigned char sc[USBHID_MAX_SCANCODES];
        int n = usbhid_kbd_scancodes(d->prev, report, sc, (int)sizeof(sc));
        int i;
        if (n < 0) {
            /* A truncated stream would leave the keyboard layer with an
             * unpaired make, so nothing is fed and the event is counted as a
             * failure rather than half-applied. */
            usbhid_ctr.transfer_errors++;
            return 0;
        }
        for (i = 0; i < n; i++) {
            int c = kbd_feed_scancode(sc[i]);
            if (c >= 0) kbd_q_push((unsigned char)c);
        }
        usbhid_ctr.scancodes += (unsigned long)n;
        usbhid_ctr.kbd_reports++;
        kmemcpy(d->prev, report, HID_KBD_REPORT_LEN);
    }
    d->token = xhc_transfer_async(d->device, d->ep_index, report, want);
    return 1;
}

int usbhid_poll_keyboard(void) {
    int i;
    int n = 0;
    for (i = 0; i < USBHID_MAX_DEVS; i++)
        n += usbhid_poll_one(&usbhid_kbd[i]);
    return n;
}

int usbhid_poll_mouse(void) {
    int i;
    int n = 0;
    for (i = 0; i < USBHID_MAX_DEVS; i++)
        n += usbhid_poll_one(&usbhid_mouse[i]);
    return n;
}

int usbhid_poll(void) {
    return usbhid_poll_keyboard() + usbhid_poll_mouse();
}