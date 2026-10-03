/** Docstring: drivers/xhci.h -- boundary of the xHCI host controller driver.
 *
 * The only file that knows what an xHCI register, a TRB, a device context or
 * an endpoint context is. Everything above it (usbhid, usbblk) speaks in
 * ports, slots, interfaces and byte buffers, which is why the mass-storage
 * slice landed after the HID slice without editing a line of the controller.
 *
 * The event ring is polled, by decision: this tree has no MSI, no MSI-X, no
 * I/O-APIC and no per-vector handler registration, and the spec does not
 * require interrupts. xhc_poll is called from the tick bus and from the
 * shell's input spin. It claims no vector, adds no IDT arm and changes no
 * PIC mask.
 *
 * One consequence every caller must respect: a Transfer Event carries no
 * byte count for a non-isochronous transfer. A caller therefore requests
 * exactly the size its protocol defines -- one whole HID report, a whole
 * number of 512-byte blocks -- and the completed length is the length it
 * asked for. A short packet is a device fault, reported by the stall bit or
 * by the command status wrapper, and never by a silently smaller count.
 */

#ifndef DRIVERS_XHCI_H
#define DRIVERS_XHCI_H

/* ---- Bounds: every one of these is a refusal, never a truncation ---- */

/** Docstring: Concurrent device records. Each holds a slot, a port and a
 * heap configuration-descriptor block. */
#define XHC_MAX_DEVICES 16

/** Docstring: Concurrent root ports probed. Below what HCCPARAMS1 reports,
 * so a controller that claims more is truncated and reported, never
 * trusted. */
#define XHC_MAX_PORTS 16

/** Docstring: Endpoints tracked per interface. A HID interface has two, a
 * mass-storage interface has three. */
#define XHC_MAX_EPS 4

/** Docstring: Highest endpoint context index this driver programs,
 * exclusive. Index 0 is always the control endpoint; one IN and one OUT
 * index covers both device classes, which is why four is the bound. */
#define XHC_EP_INDEX_LIMIT 4

/** Docstring: Outstanding non-control transfers tracked at once: two for a
 * HID keyboard and mouse, two for a mass-storage read or write. */
#define XHC_MAX_PENDING 8

/** Docstring: Heap bytes for a configuration descriptor. The largest real
 * one (a HID plus a mass-storage interface) is well under 128. */
#define XHC_MAX_CONFIG_DESC 256

/** Docstring: TRBs in the command ring and in each transfer ring. A power of
 * two so the cycle is a mask, and large enough that mass-storage bring-up
 * across sixteen devices never wraps it. */
#define XHC_TRB_RING_TRBS 1024

/** Docstring: Wait budgets in milliseconds, all enforced. A driver that
 * spins past one of these is a hung kernel, and on the tick bus a hung
 * kernel takes the machine with it. */
#define XHC_RESET_BUDGET_MS 1000
#define XHC_CMD_BUDGET_MS 200
#define XHC_XFER_BUDGET_MS 500
#define XHC_PORT_BUDGET_MS 500

/** Docstring: Capability-register length below which the register layout is
 * unknown. The xHCI 1.0 minimum is 0x10. */
#define XHC_CAPLENGTH_MIN 0x10u

/** Docstring: Bus speed codes, as the PORTSC speed field reports them. */
#define XHC_SPEED_FULL 1
#define XHC_SPEED_LOW 2
#define XHC_SPEED_HIGH 3
#define XHC_SPEED_SUPER 4

/** Docstring: USB endpoint transfer types from the endpoint descriptor. */
#define XHC_EP_CONTROL 0
#define XHC_EP_ISOCHRONOUS 1
#define XHC_EP_BULK 2
#define XHC_EP_INTERRUPT 3

/** Docstring: Direction bit of an endpoint address. */
#define XHC_EP_DIR_IN 0x80

/** Docstring: USB interface classes this kernel looks for. */
#define XHC_CLASS_HID 0x03
#define XHC_SUBCLASS_BOOT 0x01
#define XHC_CLASS_MASS_STORAGE 0x08
#define XHC_SUBCLASS_SCSI 0x06
#define XHC_PROTOCOL_BULK_ONLY 0x50

/** Docstring: One interface of a device with its endpoints, recovered from a
 * configuration descriptor. Filled by xhc_open_interface. */
typedef struct {
    int cls;
    int sub;
    int proto;
    int iface;
    int num_eps;
    int ep_addr[XHC_MAX_EPS];
    int ep_type[XHC_MAX_EPS];
    int ep_maxp[XHC_MAX_EPS];
} xhc_iface_t;

/** Docstring: What one root port currently holds. Every field is read from
 * PORTSC, never inferred. */
typedef struct {
    int connected;
    int enabled;
    int speed;
    int power;
} xhc_port_t;

/** Docstring: Per-device state the class drivers read back. */
typedef struct {
    int slot;
    int port;
    int speed;
    int address;
} xhc_dev_t;

/** Docstring: Counters, so a zero is attributable rather than mysterious.
 * Every field is incremented by the code path that did the work. */
typedef struct {
    unsigned long cmd_ok;
    unsigned long cmd_failed;
    unsigned long cmd_timeout;
    unsigned long events_seen;
    unsigned long events_unmatched;
    unsigned long xfers_done;
    unsigned long xfers_failed;
    unsigned long enum_errors;
} xhc_counters_t;

/** Docstring: Bring up the first xHCI controller found. Returns 1 when a
 * controller is running and xhc_poll will service it, 0 when there is none,
 * which is the normal case on QEMU and on a machine whose firmware already
 * owns the controller. Never leaves a half-mapped BAR behind: any failure
 * restores the firmware's assignment. */
int xhc_init(void);

/** Docstring: Service the event ring. Drains every pending TRB and completes
 * the matching transfer. Safe to call from any context, any number of
 * times, with interrupts on or off; it allocates nothing and takes no lock.
 * Returns 1 when it completed something. */
int xhc_poll(void);

/** Docstring: Number of root ports the controller reports, bounded by
 * XHC_MAX_PORTS. */
int xhc_port_count(void);

/** Docstring: Read a root port's live state. Returns 1 on a valid port
 * number, 0 otherwise, and leaves out zeroed on refusal. */
int xhc_port_state(int port, xhc_port_t *out);

/** Docstring: Reset a port and wait for the device on it to be
 * addressable. Returns 1 when the port reports a connected, powered,
 * enabled device. */
int xhc_port_reset(int port);

/** Docstring: Reset, address, describe and register the device on a port.
 * Returns its index, or -1 on any failure, in which case the slot is
 * released and the error is counted. Idempotent per port: a port already
 * holding a live device returns that device's index. */
int xhc_enumerate(int port);

/** Docstring: Enumerate every port that has something attached. Returns the
 * number of devices registered by this call. */
int xhc_enumerate_all(void);

/** Docstring: Number of devices enumerated so far. */
int xhc_device_count(void);

/** Docstring: Fetch one enumerated device's state. */
int xhc_device_info(int index, xhc_dev_t *out);

/** Docstring: Find an interface of an enumerated device by class triple and
 * copy out its endpoints.
 *
 * A pure function over the cached configuration descriptor, with every
 * descriptor's bLength, type and remaining span checked before use: an
 * unterminated or zero-length descriptor ends the walk instead of looping,
 * and the endpoint count is capped by XHC_MAX_EPS. out is zeroed first, so
 * a caller that ignores the result sees a zeroed interface, never stale
 * stack. Returns 1 on a match with at least one endpoint, 0 otherwise. */
int xhc_open_interface(int index, unsigned cls, unsigned sub, unsigned proto,
                       xhc_iface_t *out);

/** Docstring: Issue a control transfer on the control endpoint of a device.
 * setup is the eight setup bytes, already packed, including the direction bit
 * of bmRequestType. host_to_device selects a write data stage. Returns 1 on
 * a completed transfer, 0 on a stall, a timeout or a short phase. */
int xhc_control(int index, const unsigned char setup[8], void *data,
                unsigned len, int host_to_device);

/** Docstring: Configure one non-control endpoint and give it a transfer
 * ring. ep_index is the endpoint context index, 1..XHC_EP_INDEX_LIMIT-1.
 * ep_addr carries the address and direction bits. Returns 1 on success, 0 on
 * a bad index, a device that is not addressed, or an allocation failure. */
int xhc_configure_endpoint(int index, int ep_index, int ep_addr, int ep_type,
                           int max_packet, int mult, int interval, int burst);

/** Docstring: Move data on a configured endpoint and wait for its transfer
 * event. len must be exactly what the endpoint's protocol transfers: one HID
 * report, or a whole number of 512-byte blocks. got receives the byte count
 * only for the zero-length case, which is how a device reports "nothing new";
 * otherwise the transfer either completed at len or failed.
 *
 * Returns 1 when the device completed the transfer, 0 on a stall, a transfer
 * error, or a timeout. */
int xhc_transfer(int index, int ep_index, void *buf, unsigned len, int *got);

/** Docstring: Stop, reset and re-point one endpoint's transfer ring after a
 * stall or a timeout, so Bulk-Only recovery continues on the same ring.
 * Returns 1 when the endpoint is usable again. */
int xhc_reset_endpoint(int index, int ep_index);

/** Docstring: Post one endpoint transfer without waiting. Returns the token
 * for xhc_poll_token, or 0 on refusal. */
int xhc_transfer_async(int index, int ep_index, void *buf, unsigned len);

/** Docstring: Non-blocking completion check: 1 on success, -1 on a failed
 * completion, -2 past the transfer budget, 0 while outstanding. A zero
 * budget never expires, for interrupt endpoints whose silence is NAKs. */
int xhc_poll_token_limit(int token, unsigned budget_ms);
int xhc_poll_token(int token);

/** Docstring: Snapshot the counters. */
void xhc_counters(xhc_counters_t *out);

/** Docstring: Why the last xhc_init failed, or NULL when it succeeded.
 * Reported by the usb builtin so an absent controller and a refused one are
 * distinguishable. */
const char *xhc_probe_note(void);

/** Docstring: Controller version and capability-derived limits for the usb
 * builtin. Returns 1 when a controller is present. */
int xhc_info(unsigned *version, unsigned *slots, unsigned *ports,
             unsigned *caplength);

#endif