/** Docstring: drivers/usbhid.h -- boundary of the USB HID boot-protocol driver.
 *
 * Turns a USB HID keyboard or mouse into the input events the rest of
 * MiniOS already consumes: set-1 scancodes for the keyboard (through
 * kbd_feed_scancode, so the window manager's combos and the English and
 * Spanish layouts keep working) and mouse_state writes for the pointer.
 *
 * Nothing here knows what a TRB or an endpoint context is.
 */

#ifndef DRIVERS_USBHID_H
#define DRIVERS_USBHID_H

/* ---- HID usage codes the driver needs ---- */
#define HID_USAGE_MIN 0x04u
#define HID_USAGE_MAX 0xDDu
#define HID_MODIFIER_BIT(n) ((unsigned char)(1u << ((n) - 1u)))
#define HID_MOD_LEFT_CTRL 1u
#define HID_MOD_LEFT_SHIFT 2u
#define HID_MOD_LEFT_ALT 4u
#define HID_MOD_LEFT_GUI 8u
#define HID_MOD_RIGHT_CTRL 16u
#define HID_MOD_RIGHT_SHIFT 32u
#define HID_MOD_RIGHT_ALT 64u
#define HID_MOD_RIGHT_GUI 128u

/** Docstring: Boot-protocol keyboard input report: a modifier bitfield, a
 * reserved byte, then up to six keycodes. */
#define HID_KBD_REPORT_LEN 8
#define HID_KBD_SLOTS 6

/** Docstring: Boot-protocol mouse input report: buttons, then signed X, Y
 * and a signed four-bit wheel. A mouse with a pan button reports five bytes;
 * the driver asks for four and discards nothing, so the size is asserted
 * against the endpoint's own maximum rather than assumed. */
#define HID_MOUSE_REPORT_LEN 4
#define HID_MOUSE_BUTTON_MASK 0x07

/** Docstring: Longest report the driver keeps between polls, which is the
 * keyboard's. */
#define USBHID_MAX_REPORT_LEN HID_KBD_REPORT_LEN

/** Docstring: Returned by the scancode differ when the output buffer cannot
 * hold the whole event stream. A half-emitted event would leave the keyboard
 * layer with a make and no break, so this is reported rather than clamped. */
#define USBHID_TRUNCATED (-1)

/** Docstring: HID interface protocol codes. A boot-protocol keyboard and
 * mouse advertise none, so the driver matches the wildcard and identifies
 * the device by its endpoint size. */
#define USBHID_PROTO_NONE 0xFFu

/** Docstring: HID request SET_PROTOCOL, and the boot-protocol value. */
#define HID_REQ_SET_PROTOCOL 0x0Bu
#define HID_PROTOCOL_BOOT 0x00u

/** Docstring: Bring up HID on every enumerated device and report what was
 * found. Returns the number of HID interfaces claimed, which is 0 on a
 * machine with no HID device and is not an error. */
int usbhid_init(void);

/** Docstring: Service the interrupt endpoint of a claimed keyboard. One
 * report per call; returns 1 when a report was processed. */
int usbhid_poll_keyboard(void);

/** Docstring: Service the interrupt endpoint of a claimed mouse. One report
 * per call; returns 1 when a report was processed. */
int usbhid_poll_mouse(void);

/** Docstring: Service both, for the tick bus. Returns the reports handled. */
int usbhid_poll(void);

/** Docstring: True when a USB keyboard is driving the input path, so the
 * keyboard driver can skip the PS/2 port instead of spinning on a controller
 * that does not exist on modern hardware. */
int usbhid_keyboard_present(void);

/** Docstring: True when a USB mouse is driving mouse_state. */
int usbhid_mouse_present(void);

/** Docstring: Feed a boot keyboard report through the differ, for the
 * host test and the in-OS self test. Uses the first claimed keyboard's
 * stored previous report and updates it. Returns the scancodes emitted. */
int usbhid_press_kbd_report(const unsigned char report[HID_KBD_REPORT_LEN]);

/** Docstring: Set-1 scancode stream for one keyboard report transition.
 *
 * Pure: no hardware, no kernel state, no allocation, which is what makes it
 * host-testable. Breaks are emitted before makes, for modifiers and for keys
 * alike, so a burst never reads as a held-key repeat. A key that merely moved
 * slot within the array produces nothing, because the array order is the
 * device's choice. Returns the number of scancodes written, which is less
 * than max only when the report produced no events. */
int usbhid_kbd_scancodes(const unsigned char prev[HID_KBD_REPORT_LEN],
                         const unsigned char cur[HID_KBD_REPORT_LEN],
                         unsigned char *out, int max);

/** Docstring: Decode one boot mouse report transition into screen-space
 * motion, buttons and wheel. Pure, for the same reason. dx and dy are raw
 * report deltas; the caller applies the motion scale, matching the PS/2
 * path so both sources move the pointer identically. */
void usbhid_mouse_decode(const unsigned char prev[HID_MOUSE_REPORT_LEN],
                         const unsigned char cur[HID_MOUSE_REPORT_LEN],
                         int *dx, int *dy, int *buttons, int *wheel);

/** Docstring: Counters, so a device that is absent is distinguishable from a
 * driver that is broken. */
typedef struct {
    unsigned long kbd_reports;
    unsigned long mouse_reports;
    unsigned long scancodes;
    unsigned long transfer_errors;
} usbhid_counters_t;

/** Docstring: Snapshot the counters. */
void usbhid_counters(usbhid_counters_t *out);

/** Docstring: Translate a HID usage code to its PS/2 set-1 make code and
 * whether it needs the 0xE0 prefix. Returns 0 for a usage with no set-1
 * equivalent, which the caller drops rather than inventing a scancode for.
 *
 * A pure function over a table, host-testable: HID usage ids are not
 * scancodes above 0x27 (usage 0x28 is Return while set-1 Return is 0x1C), and
 * the navigation cluster and the right-hand modifiers exist in one place on
 * a USB keyboard while set-1 needs the prefix to tell them from their
 * left-hand twins. Both decisions live here so no caller has to know them. */
int usbhid_set1_from_usage(unsigned usage, unsigned char *sc, int *e0);

#endif