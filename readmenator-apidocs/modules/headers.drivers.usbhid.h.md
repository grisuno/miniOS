# `headers/drivers/usbhid.h`

> Source: [headers/drivers/usbhid.h:1](../../headers/drivers/usbhid.h#L1) | language `h` | coverage 60.6% | [API index](../index.md)

Docstring: drivers/usbhid.h -- boundary of the USB HID boot-protocol driver.

## Contents

- **Structs:** [`usbhid_counters_t`](#usbhid_counters_t)
- **Functions:** [`usbhid_init`](#usbhid_init), [`usbhid_poll_keyboard`](#usbhid_poll_keyboard), [`usbhid_poll_mouse`](#usbhid_poll_mouse), [`usbhid_poll`](#usbhid_poll), [`usbhid_keyboard_present`](#usbhid_keyboard_present), [`usbhid_mouse_present`](#usbhid_mouse_present), [`usbhid_press_kbd_report`](#usbhid_press_kbd_report), [`usbhid_kbd_scancodes`](#usbhid_kbd_scancodes), [`usbhid_mouse_decode`](#usbhid_mouse_decode), [`usbhid_counters`](#usbhid_counters), [`usbhid_set1_from_usage`](#usbhid_set1_from_usage)
- **Macros:** [`HID_USAGE_MIN`](#hid_usage_min), [`HID_USAGE_MAX`](#hid_usage_max), [`HID_MODIFIER_BIT`](#hid_modifier_bit), [`HID_MOD_LEFT_CTRL`](#hid_mod_left_ctrl), [`HID_MOD_LEFT_SHIFT`](#hid_mod_left_shift), [`HID_MOD_LEFT_ALT`](#hid_mod_left_alt), [`HID_MOD_LEFT_GUI`](#hid_mod_left_gui), [`HID_MOD_RIGHT_CTRL`](#hid_mod_right_ctrl), [`HID_MOD_RIGHT_SHIFT`](#hid_mod_right_shift), [`HID_MOD_RIGHT_ALT`](#hid_mod_right_alt), [`HID_MOD_RIGHT_GUI`](#hid_mod_right_gui), [`HID_KBD_REPORT_LEN`](#hid_kbd_report_len), [`HID_KBD_SLOTS`](#hid_kbd_slots), [`HID_MOUSE_REPORT_LEN`](#hid_mouse_report_len), [`HID_MOUSE_BUTTON_MASK`](#hid_mouse_button_mask), [`USBHID_MAX_REPORT_LEN`](#usbhid_max_report_len), [`USBHID_TRUNCATED`](#usbhid_truncated), [`USBHID_PROTO_NONE`](#usbhid_proto_none), [`HID_REQ_SET_PROTOCOL`](#hid_req_set_protocol), [`HID_PROTOCOL_BOOT`](#hid_protocol_boot)

## Structs

<a id="usbhid_counters_t"></a>

### `usbhid_counters_t`

`struct` | [headers/drivers/usbhid.h:108](../../headers/drivers/usbhid.h#L108)

```c
typedef struct
```

Docstring: Counters, so a device that is absent is distinguishable from a driver that is broken.

---

## Functions

<a id="usbhid_init"></a>

### `usbhid_init`

`function` | [headers/drivers/usbhid.h:60](../../headers/drivers/usbhid.h#L60)

```c
int usbhid_init(void);
```

Docstring: Bring up HID on every enumerated device and report what was found.

Returns the number of HID interfaces claimed, which is 0 on a machine with no HID device and is not an error.

**Returns:** `int`

*Called by:* [`tables`](kernel.c.md#tables)

---

<a id="usbhid_poll_keyboard"></a>

### `usbhid_poll_keyboard`

`function` | [headers/drivers/usbhid.h:64](../../headers/drivers/usbhid.h#L64)

```c
int usbhid_poll_keyboard(void);
```

Docstring: Service the interrupt endpoint of a claimed keyboard.

One report per call; returns 1 when a report was processed.

**Returns:** `int`

---

<a id="usbhid_poll_mouse"></a>

### `usbhid_poll_mouse`

`function` | [headers/drivers/usbhid.h:68](../../headers/drivers/usbhid.h#L68)

```c
int usbhid_poll_mouse(void);
```

Docstring: Service the interrupt endpoint of a claimed mouse.

One report per call; returns 1 when a report was processed.

**Returns:** `int`

---

<a id="usbhid_poll"></a>

### `usbhid_poll`

`function` | [headers/drivers/usbhid.h:71](../../headers/drivers/usbhid.h#L71)

```c
int usbhid_poll(void);
```

Docstring: Service both, for the tick bus.

Returns the reports handled.

**Returns:** `int`

---

<a id="usbhid_keyboard_present"></a>

### `usbhid_keyboard_present`

`function` | [headers/drivers/usbhid.h:76](../../headers/drivers/usbhid.h#L76)

```c
int usbhid_keyboard_present(void);
```

Docstring: True when a USB keyboard is driving the input path, so the keyboard driver can skip the PS/2 port instead of spinning on a controller that does not exist on modern hardware.

**Returns:** `int`

*Called by:* [`tables`](kernel.c.md#tables)

---

<a id="usbhid_mouse_present"></a>

### `usbhid_mouse_present`

`function` | [headers/drivers/usbhid.h:79](../../headers/drivers/usbhid.h#L79)

```c
int usbhid_mouse_present(void);
```

Docstring: True when a USB mouse is driving mouse_state.

**Returns:** `int`

*Called by:* [`tables`](kernel.c.md#tables)

---

<a id="usbhid_press_kbd_report"></a>

### `usbhid_press_kbd_report`

`function` | [headers/drivers/usbhid.h:84](../../headers/drivers/usbhid.h#L84)

```c
int usbhid_press_kbd_report(const unsigned char report[HID_KBD_REPORT_LEN]);
```

Docstring: Feed a boot keyboard report through the differ, for the host test and the in-OS self test.

Uses the first claimed keyboard's stored previous report and updates it. Returns the scancodes emitted.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `HID_KBD_REPORT_LEN` | `unsigned char report[ ]` |  |  |

**Returns:** `int`

---

<a id="usbhid_kbd_scancodes"></a>

### `usbhid_kbd_scancodes`

`function` | [headers/drivers/usbhid.h:94](../../headers/drivers/usbhid.h#L94)

```c
int usbhid_kbd_scancodes(const unsigned char prev[HID_KBD_REPORT_LEN], const unsigned char cur[HID_KBD_REPORT_LEN], unsigned char *out, int max);
```

Docstring: Set-1 scancode stream for one keyboard report transition.

Pure: no hardware, no kernel state, no allocation, which is what makes it
host-testable. Breaks are emitted before makes, for modifiers and for keys
alike, so a burst never reads as a held-key repeat. A key that merely moved
slot within the array produces nothing, because the array order is the
device's choice. Returns the number of scancodes written, which is less
than max only when the report produced no events.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `HID_KBD_REPORT_LEN` | `unsigned char prev[ ]` |  |  |
| `HID_KBD_REPORT_LEN` | `unsigned char cur[ ]` |  |  |
| `out` | `unsigned char *` |  |  |
| `max` | `int` |  |  |

**Returns:** `int`

---

<a id="usbhid_mouse_decode"></a>

### `usbhid_mouse_decode`

`function` | [headers/drivers/usbhid.h:102](../../headers/drivers/usbhid.h#L102)

```c
void usbhid_mouse_decode(const unsigned char prev[HID_MOUSE_REPORT_LEN], const unsigned char cur[HID_MOUSE_REPORT_LEN], int *dx, int *dy, int *buttons, int *wheel);
```

Docstring: Decode one boot mouse report transition into screen-space motion, buttons and wheel.

Pure, for the same reason. dx and dy are raw report deltas; the caller applies the motion scale, matching the PS/2 path so both sources move the pointer identically.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `HID_MOUSE_REPORT_LEN` | `unsigned char prev[ ]` |  |  |
| `HID_MOUSE_REPORT_LEN` | `unsigned char cur[ ]` |  |  |
| `dx` | `int *` |  |  |
| `dy` | `int *` |  |  |
| `buttons` | `int *` |  |  |
| `wheel` | `int *` |  |  |

---

<a id="usbhid_counters"></a>

### `usbhid_counters`

`function` | [headers/drivers/usbhid.h:116](../../headers/drivers/usbhid.h#L116)

```c
void usbhid_counters(usbhid_counters_t *out);
```

Docstring: Snapshot the counters.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `out` | `usbhid_counters_t *` |  |  |

---

<a id="usbhid_set1_from_usage"></a>

### `usbhid_set1_from_usage`

`function` | [headers/drivers/usbhid.h:127](../../headers/drivers/usbhid.h#L127)

```c
int usbhid_set1_from_usage(unsigned usage, unsigned char *sc, int *e0);
```

Docstring: Translate a HID usage code to its PS/2 set-1 make code and whether it needs the 0xE0 prefix.

Returns 0 for a usage with no set-1 equivalent, which the caller drops rather than inventing a scancode for.

A pure function over a table, host-testable: HID usage ids are not
scancodes above 0x27 (usage 0x28 is Return while set-1 Return is 0x1C), and
the navigation cluster and the right-hand modifiers exist in one place on
a USB keyboard while set-1 needs the prefix to tell them from their
left-hand twins. Both decisions live here so no caller has to know them.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `usage` | `unsigned` |  |  |
| `sc` | `unsigned char *` |  |  |
| `e0` | `int *` |  |  |

**Returns:** `int`

---

## Macros

<a id="hid_usage_min"></a>

### `HID_USAGE_MIN`

`macro` | [headers/drivers/usbhid.h:15](../../headers/drivers/usbhid.h#L15)

```c
#define HID_USAGE_MIN
```

---- HID usage codes the driver needs ----

---

<a id="hid_usage_max"></a>

### `HID_USAGE_MAX`

`macro` | [headers/drivers/usbhid.h:16](../../headers/drivers/usbhid.h#L16)

```c
#define HID_USAGE_MAX
```

---

<a id="hid_modifier_bit"></a>

### `HID_MODIFIER_BIT`

`macro` | [headers/drivers/usbhid.h:17](../../headers/drivers/usbhid.h#L17)

```c
#define HID_MODIFIER_BIT(n)
```

*Called by:* [`usbhid_kbd_scancodes`](drivers.usbhid.c.md#usbhid_kbd_scancodes)

---

<a id="hid_mod_left_ctrl"></a>

### `HID_MOD_LEFT_CTRL`

`macro` | [headers/drivers/usbhid.h:18](../../headers/drivers/usbhid.h#L18)

```c
#define HID_MOD_LEFT_CTRL
```

---

<a id="hid_mod_left_shift"></a>

### `HID_MOD_LEFT_SHIFT`

`macro` | [headers/drivers/usbhid.h:19](../../headers/drivers/usbhid.h#L19)

```c
#define HID_MOD_LEFT_SHIFT
```

---

<a id="hid_mod_left_alt"></a>

### `HID_MOD_LEFT_ALT`

`macro` | [headers/drivers/usbhid.h:20](../../headers/drivers/usbhid.h#L20)

```c
#define HID_MOD_LEFT_ALT
```

---

<a id="hid_mod_left_gui"></a>

### `HID_MOD_LEFT_GUI`

`macro` | [headers/drivers/usbhid.h:21](../../headers/drivers/usbhid.h#L21)

```c
#define HID_MOD_LEFT_GUI
```

---

<a id="hid_mod_right_ctrl"></a>

### `HID_MOD_RIGHT_CTRL`

`macro` | [headers/drivers/usbhid.h:22](../../headers/drivers/usbhid.h#L22)

```c
#define HID_MOD_RIGHT_CTRL
```

---

<a id="hid_mod_right_shift"></a>

### `HID_MOD_RIGHT_SHIFT`

`macro` | [headers/drivers/usbhid.h:23](../../headers/drivers/usbhid.h#L23)

```c
#define HID_MOD_RIGHT_SHIFT
```

---

<a id="hid_mod_right_alt"></a>

### `HID_MOD_RIGHT_ALT`

`macro` | [headers/drivers/usbhid.h:24](../../headers/drivers/usbhid.h#L24)

```c
#define HID_MOD_RIGHT_ALT
```

---

<a id="hid_mod_right_gui"></a>

### `HID_MOD_RIGHT_GUI`

`macro` | [headers/drivers/usbhid.h:25](../../headers/drivers/usbhid.h#L25)

```c
#define HID_MOD_RIGHT_GUI
```

---

<a id="hid_kbd_report_len"></a>

### `HID_KBD_REPORT_LEN`

`macro` | [headers/drivers/usbhid.h:29](../../headers/drivers/usbhid.h#L29)

```c
#define HID_KBD_REPORT_LEN
```

Docstring: Boot-protocol keyboard input report: a modifier bitfield, a reserved byte, then up to six keycodes.

---

<a id="hid_kbd_slots"></a>

### `HID_KBD_SLOTS`

`macro` | [headers/drivers/usbhid.h:30](../../headers/drivers/usbhid.h#L30)

```c
#define HID_KBD_SLOTS
```

---

<a id="hid_mouse_report_len"></a>

### `HID_MOUSE_REPORT_LEN`

`macro` | [headers/drivers/usbhid.h:36](../../headers/drivers/usbhid.h#L36)

```c
#define HID_MOUSE_REPORT_LEN
```

Docstring: Boot-protocol mouse input report: buttons, then signed X, Y and a signed four-bit wheel.

A mouse with a pan button reports five bytes; the driver asks for four and discards nothing, so the size is asserted against the endpoint's own maximum rather than assumed.

---

<a id="hid_mouse_button_mask"></a>

### `HID_MOUSE_BUTTON_MASK`

`macro` | [headers/drivers/usbhid.h:37](../../headers/drivers/usbhid.h#L37)

```c
#define HID_MOUSE_BUTTON_MASK
```

---

<a id="usbhid_max_report_len"></a>

### `USBHID_MAX_REPORT_LEN`

`macro` | [headers/drivers/usbhid.h:41](../../headers/drivers/usbhid.h#L41)

```c
#define USBHID_MAX_REPORT_LEN
```

Docstring: Longest report the driver keeps between polls, which is the keyboard's.

---

<a id="usbhid_truncated"></a>

### `USBHID_TRUNCATED`

`macro` | [headers/drivers/usbhid.h:46](../../headers/drivers/usbhid.h#L46)

```c
#define USBHID_TRUNCATED
```

Docstring: Returned by the scancode differ when the output buffer cannot hold the whole event stream.

A half-emitted event would leave the keyboard layer with a make and no break, so this is reported rather than clamped.

---

<a id="usbhid_proto_none"></a>

### `USBHID_PROTO_NONE`

`macro` | [headers/drivers/usbhid.h:51](../../headers/drivers/usbhid.h#L51)

```c
#define USBHID_PROTO_NONE
```

Docstring: HID interface protocol codes.

A boot-protocol keyboard and mouse advertise none, so the driver matches the wildcard and identifies the device by its endpoint size.

---

<a id="hid_req_set_protocol"></a>

### `HID_REQ_SET_PROTOCOL`

`macro` | [headers/drivers/usbhid.h:54](../../headers/drivers/usbhid.h#L54)

```c
#define HID_REQ_SET_PROTOCOL
```

Docstring: HID request SET_PROTOCOL, and the boot-protocol value.

---

<a id="hid_protocol_boot"></a>

### `HID_PROTOCOL_BOOT`

`macro` | [headers/drivers/usbhid.h:55](../../headers/drivers/usbhid.h#L55)

```c
#define HID_PROTOCOL_BOOT
```

---
