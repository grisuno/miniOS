/* xhci.c -- xHCI host controller driver, polled event ring.
 *
 * The controller is found by class code (0x0C/0x03/0x30), its BAR0 is
 * size-probed and relocated into the reserved uncached window, and from there
 * it is driven with the minimum xHCI needs to address a device and move
 * bytes.
 *
 * Structure of the driver's rings, which is the part worth knowing before
 * reading any of it:
 *
 *   DCBAA[2] is both the command ring and the control endpoint's ring. That
 *   is not a shortcut: the xHCI spec assigns the EP0 Command Ring to DCBAA
 *   index 2 for USB 3.0 devices and the EP0 In Transfer Ring to the same
 *   index for USB 2.0 devices, so a control transfer and a command are
 *   posted into the same ring behind the same doorbell either way. The
 *   driver keeps one ring, one enqueue index and one generation for both.
 *
 *   Control TRBs carry cycle 0, always. Command TRBs carry the ring
 *   generation. So when the ring wraps, the control endpoint's Dequeue Cycle
 *   State has to follow: xhc_ep0_resync writes DCS = 1 - generation into
 *   every addressed device's EP0 context, which is what the spec requires
 *   after an EP0 ring wrap.
 *
 *   Non-control endpoints get one transfer ring each. On USB 2.0 the
 *   controller reads the ring address from the DCBAA, so the endpoint
 *   context's TR dequeue pointer is reserved and must be zero; on USB 3.0 it
 *   is the other way round. xhc_configure_endpoint picks per device speed.
 *
 * Everything the controller can reach is on the heap: KASLR slides the image,
 * so a .bss address is not a physical address the controller can use. Every
 * wait is bounded. Nothing here claims an interrupt vector.
 */

#include "kernel.h"
#include "arch/x86/hal_io.h"
#include "drivers/pci.h"
#include "drivers/xhci.h"

/* ---- Register-space layout ----
 *
 * Four windows, and mixing them up produces a driver that reads plausible
 * values and silently writes them nowhere:
 *
 *   0x0000            capability registers (CAPLENGTH, HCSPARAMS, ...)
 *   CAPLENGTH         operational registers
 *   0x1000            runtime registers and the interrupter array
 *   0x2000            doorbell array
 *
 * The operational window starts at CAPLENGTH, not at a fixed offset, and the
 * capability block is read-only: writing USBCMD at offset 0 lands in
 * CAPLENGTH, is dropped, and the controller never runs -- a failure that
 * looks like dead hardware rather than a wrong address.
 *
 * These are the xHCI 1.x register offsets, not a private layout. */
#define XHC_CAP_OFF 0x0000u

/* ---- Operational register offsets, from the operational window ---- */
#define XHC_OP_USBCMD 0x00u
#define XHC_OP_USBSTS 0x04u
#define XHC_OP_PAGESIZE 0x08u
#define XHC_OP_CRCR 0x18u
#define XHC_OP_DCBAAP 0x30u
#define XHC_OP_CONFIG 0x38u
#define XHC_OP_PORTSC 0x400u
#define XHC_PORT_STRIDE 0x10u

/* ---- Runtime register offsets, from the RTSOFF window ----
 *
 * The interrupter array starts 0x20 into the runtime window, one 0x20 entry
 * per interrupter, and one interrupter is all this driver uses. */
#define XHC_RUN_INTR0 0x20u
#define XHC_RUN_IMAN 0x00u
#define XHC_RUN_IMOD 0x04u
#define XHC_RUN_ERSTSZ 0x08u
#define XHC_RUN_ERSTBA 0x10u
#define XHC_RUN_ERDP 0x18u
#define XHC_IMAN_IP 0x00000001u
#define XHC_IMAN_IE 0x00000002u
#define XHC_ERDP_EHB 0x00000008u

/* ---- Capability register offsets ---- */
#define XHC_CAP_HCSP1 0x04u
#define XHC_CAP_HCSP2 0x08u
#define XHC_CAP_HCSP3 0x0Cu
#define XHC_CAP_HCCP1 0x10u
#define XHC_CAP_DBOFF 0x14u
#define XHC_CAP_RTSOFF 0x18u
#define XHC_HCC_AC64 0x00000001u
#define XHC_HCC_CSZ 0x00000004u

/* ---- USBCMD / USBSTS ---- */
#define XHC_CMD_RUN 0x00000001u
#define XHC_CMD_RESET 0x00000002u
/* Bit 0 of USBSTS is Host Controller Halted: set while the controller is
 * stopped, cleared once it is running. */
#define XHC_STS_HALTED 0x00000001u
#define XHC_STS_ATE 0x00020000u

/* ---- PORTSC ---- */
#define XHC_PORT_CCS 0x00000001u
#define XHC_PORT_PED 0x00000002u
#define XHC_PORT_PR 0x00000010u
#define XHC_PORT_PP 0x00000200u
#define XHC_PORT_SPEED_SHIFT 10
#define XHC_PORT_SPEED_MASK 0x00003C00u
#define XHC_PORT_CHG_MASK 0x00FE0000u

/* ---- TRB control field ---- */
#define XHC_TRB_TYPE(t) ((unsigned)(((t)->control >> 10) & 0x3Fu))
#define XHC_TRB_CYCLE(t) ((unsigned)((t)->control & 1u))
#define XHC_TRB_MAKE_TYPE(v) ((unsigned long long)((unsigned long long)(v) << 10))

#define XHC_TRB_TYPE_NORMAL 1u
#define XHC_TRB_TYPE_SETUP 2u
#define XHC_TRB_TYPE_DATA 3u
#define XHC_TRB_TYPE_STATUS 4u
#define XHC_TRB_TYPE_LINK 6u
#define XHC_TRB_TYPE_NOOP_TRB 8u
#define XHC_TRB_TYPE_ENABLE_SLOT 9u
#define XHC_TRB_TYPE_ADDRESS_DEVICE 11u
#define XHC_TRB_TYPE_CONFIGURE_ENDPOINT 12u
#define XHC_TRB_TYPE_RESET_ENDPOINT 14u
#define XHC_TRB_TYPE_STOP_ENDPOINT 15u
#define XHC_TRB_TYPE_SET_DEQUEUE 16u
#define XHC_TRB_TYPE_NOOP_CMD 23u
#define XHC_TRB_TYPE_TRANSFER_EVENT 32u
#define XHC_TRB_TYPE_CMD_COMPLETION 33u
#define XHC_TRB_TYPE_PORT_STATUS 34u

/* ---- Command completion codes ---- */
#define XHC_CC_SUCCESS 1u
#define XHC_CC_SHORT_PACKET 13u

/* ---- Event TRB types ---- */
#define XHC_EVT_TYPE(e) ((unsigned)(((e)->control >> 10) & 0x3Fu))
#define XHC_EVT_CC(e) ((unsigned)(((e)->status >> 24) & 0xFFu))
#define XHC_EVT_SLOT(e) ((unsigned)(((e)->control >> 24) & 0xFFu))
#define XHC_EVT_LEN(e) ((unsigned)((e)->status & 0x00FFFFFFu))
#define XHC_EVT_TRANSFER XHC_TRB_TYPE_TRANSFER_EVENT
#define XHC_EVT_CMD_COMPLETION XHC_TRB_TYPE_CMD_COMPLETION

/* ---- Endpoint context state is programmed zero (disabled) at build; the
 * controller publishes running states back into the output context. ---- */

/* ---- Endpoint context, 32 bytes per spec Table 140 ----
 * DW0 off0: state[2:0] mult[10:8] maxstreams[14:11] lsa[15] interval[23:16]
 * DW1 off4: cerr[1:0] type[5:3] hid[7] burst[15:8] maxp[31:16]
 * DW2-3 off8: dequeue[63:4] dcs[0]
 * DW4 off16: avglen[15:0] esit[31:16] */
#define XHC_EP_DW0_OFF 0x00u
#define XHC_EP_DW1_OFF 0x04u
#define XHC_EP_DEQ_OFF 0x08u
#define XHC_EP_AVG_OFF 0x10u
#define XHC_EP_MULT_SHIFT 8u
#define XHC_EP_INTERVAL_SHIFT 16u
#define XHC_EP_TYPE_SHIFT 3u
#define XHC_EP_BURST_SHIFT 8u
#define XHC_EP_MAXP_SHIFT 16u
#define XHC_EP_DCS_BIT 0x1u

/* ---- Endpoint types, spec Table 140: 0 is Not Valid, control is 4 ---- */
#define XHC_EPT_CONTROL 4u
#define XHC_EPT_ISO_OUT 1u
#define XHC_EPT_BULK_OUT 2u
#define XHC_EPT_INT_OUT 3u
#define XHC_EPT_ISO_IN 5u
#define XHC_EPT_BULK_IN 6u
#define XHC_EPT_INT_IN 7u
#define XHC_EP_CERR 3u

/* ---- Context geometry: 32 or 64 bytes per context per HCC CSZ ----
 * The stride covers the slot plus all 31 endpoint contexts. */
#define XHC_CTX_SLOT_STRIDE 1024u
#define XHC_CTX_SLOT_STRIDE64 2048u
#define XHC_CTX_DEVICE_BYTES 32u
#define XHC_CTX_EP_BYTES 32u
#define XHC_ICTX_BYTES 4096u
/* ---- Slot context, 32 bytes per spec: DW0 off0 route[19:0] speed[23:20]
 * mtt[25] hub[26] entries[31:27]; DW1 off4 exitlat[15:0] roothub[23:16]
 * ports[31:24]; DW3 off12 addr[7:0] state[31:27] */
#define XHC_SLOT_DW0_OFF 0x00u
#define XHC_SLOT_DW1_OFF 0x04u
#define XHC_SLOT_ADDR_OFF 0x0Cu
#define XHC_SLOT_SPEED_SHIFT 20u
#define XHC_SLOT_ENTRIES_SHIFT 27u
#define XHC_SLOT_RHPORT_SHIFT 16u

/* ---- Input context: DW0-1 off0 drop/add flags, slot and EPs after ---- */
#define XHC_ICTX_DROP_OFF 0x00u
#define XHC_ICTX_ADD_OFF 0x04u

/* ---- DCBAA: entry per slot, entry 0 unused, entry N = device context N ---- */
#define XHC_DCBAA_ENTRIES (XHC_MAX_DEVICES + 2u)

/* ---- ERST entry, in 32-bit words ---- */
#define XHC_ERST_RING_LO 0u
#define XHC_ERST_RING_HI 1u
#define XHC_ERST_SIZE 2u
#define XHC_ERST_CYCLE 3u
#define XHC_ERST_BYTES 16u

/* ---- DMA alignment ----
 *
 * 64 bytes, and this is not alignment for its own sake: the hardware masks
 * the low bits of DCBAAP, of the command ring configuration register and of
 * the event ring segment table base. A ring allocated on 16 bytes and handed
 * over silently moves, and the controller then reads a command ring full of
 * zeros -- which looks exactly like a controller that ignores the doorbell.
 *
 * Contexts need 32 and the context array 64, so one alignment covers every
 * structure the controller walks. */
#define XHC_DMA_ALIGN 64u

/* ---- Ring geometry: the last TRB of a ring is its link ---- */
#define XHC_RING_USABLE (XHC_TRB_RING_TRBS - 1u)

/* ---- USB descriptor types ---- */
#define XHC_DT_DEVICE 1u
#define XHC_DT_CONFIG 2u
#define XHC_DT_INTERFACE 4u
#define XHC_DT_ENDPOINT 5u

/* ---- Descriptor field offsets ---- */
#define XHC_DEV_DESC_LEN_OFF 0x00u
#define XHC_DEV_DESC_TYPE_OFF 0x01u
#define XHC_DEV_DESC_NUM_CFG_OFF 17u
#define XHC_CFG_TOTAL_LEN_OFF 2u
#define XHC_IFACE_OFF 2u
#define XHC_IFACE_CLASS_OFF 5u
#define XHC_IFACE_SUBCLASS_OFF 6u
#define XHC_IFACE_PROTO_OFF 7u
#define XHC_EP_DESC_ADDR_OFF 2u
#define XHC_EP_DESC_TYPE_OFF 3u
#define XHC_EP_DESC_MAXP_OFF 4u

/** Docstring: A Transfer Request Block, 16 bytes per spec: 8-byte parameter,
 * 4-byte status, 4-byte control. This size is load-bearing: a 24-byte struct
 * spaces the ring wrong and the controller walks garbage. */
typedef struct {
    unsigned long long param;
    unsigned status;
    unsigned control;
} xhc_trb_t;

/** Docstring: A non-control endpoint's transfer ring plus the producer's
 * place in it. dci is the doorbell target and context index plus one.
 * rearm requests a link re-arm once the producer is halfway round the
 * new lap (see xhc_cmd_rearm: re-arming at the wrap itself races the
 * controller into reading the link stale). */
typedef struct {
    xhc_trb_t *trbs;
    unsigned enq;
    unsigned gen;
    int configured;
    int is_out;
    int dci;
    int rearm;
} xhc_ring_t;

/** Docstring: A transfer waiting for its event. The caller-visible token is
 * the index plus one, so 0 is always "refused" and never a valid token.
 * since dates the post for the async reap budget. len is the asked length
 * and got the bytes the device actually moved, from the event's residue. */
typedef struct {
    xhc_trb_t *trb;
    unsigned len;
    unsigned got;
    int status;
    int done;
    int used;
    unsigned long since;
} xhc_pending_t;

/** Docstring: One enumerated device, with its cached configuration
 * descriptor on the heap. */
typedef struct {
    int used;
    int slot;
    int port;
    int speed;
    int address;
    unsigned char *config;
    unsigned config_len;
} xhc_devrec_t;

static volatile unsigned char *xhc_mmio;
static volatile unsigned char *xhc_op;
static volatile unsigned char *xhc_run;
static volatile unsigned char *xhc_db;
static unsigned xhc_caplength;
static unsigned xhc_version;
static unsigned xhc_max_slots;
static unsigned xhc_port_limit;
static int xhc_csz;

static unsigned xhc_ep_b(void) {
    return xhc_csz ? 64u : 32u;
}

static unsigned xhc_stride(void) {
    return xhc_csz ? XHC_CTX_SLOT_STRIDE64 : XHC_CTX_SLOT_STRIDE;
}

static xhc_trb_t *xhc_cmd;
static unsigned xhc_cmd_enq;
static unsigned xhc_cmd_gen;
static xhc_trb_t *xhc_evt;
static unsigned xhc_evt_deq;
static unsigned xhc_evt_expect;
static unsigned long long *xhc_dbaa;
static unsigned char *xhc_ctx;
static unsigned char *xhc_in_ctx;
static unsigned char *xhc_out_ctx;
static unsigned long long *xhc_erst;

static xhc_devrec_t xhc_devs[XHC_MAX_DEVICES];
static xhc_ring_t xhc_rings[XHC_MAX_DEVICES][XHC_EP_INDEX_LIMIT];
static xhc_pending_t xhc_pending[XHC_MAX_PENDING];
static xhc_counters_t xhc_ctr;
/** Docstring: Why the probe failed, for the usb builtin. A driver that
 * reports only "no controller" makes an absent controller and a broken one
 * indistinguishable, which is the opposite of what a debug readout is for. */
static const char *xhc_note = "no xHCI class match";

/* ---- Little-endian field access ---- */

static void xhc_put32(unsigned char *base, unsigned off, unsigned val) {
    base[off + 0] = (unsigned char)(val & 0xFFu);
    base[off + 1] = (unsigned char)((val >> 8) & 0xFFu);
    base[off + 2] = (unsigned char)((val >> 16) & 0xFFu);
    base[off + 3] = (unsigned char)((val >> 24) & 0xFFu);
}

static unsigned xhc_get32(const unsigned char *base, unsigned off) {
    return (unsigned)base[off + 0] | ((unsigned)base[off + 1] << 8) |
           ((unsigned)base[off + 2] << 16) | ((unsigned)base[off + 3] << 24);
}

static void xhc_put64(unsigned char *base, unsigned off,
                      unsigned long long val) {
    xhc_put32(base, off, (unsigned)(val & 0xFFFFFFFFu));
    xhc_put32(base, off + 4u, (unsigned)(val >> 32));
}

static void xhc_put16(unsigned char *base, unsigned off, unsigned val) {
    base[off + 0] = (unsigned char)(val & 0xFFu);
    base[off + 1] = (unsigned char)((val >> 8) & 0xFFu);
}

static void xhc_puttrb(xhc_trb_t *trb, unsigned long long param,
                       unsigned status, unsigned control) {
    trb->param = param;
    trb->status = status;
    trb->control = control;
}

/* ---- Register access ---- */

static unsigned xhc_op_read32(unsigned off) {
    return hal_mmio_read32((volatile unsigned *)(xhc_op + off));
}

static void xhc_op_write32(unsigned off, unsigned val) {
    hal_mmio_write32((volatile unsigned *)(xhc_op + off), val);
}

static void xhc_run_write32(unsigned off, unsigned val) {
    hal_mmio_write32((volatile unsigned *)(xhc_run + off), val);
}

static unsigned xhc_run_read32(unsigned off) {
    return hal_mmio_read32((volatile unsigned *)(xhc_run + off));
}

static unsigned long xhc_now_ms(void) {
    return ktime_ms();
}

/** Docstring: Write back and invalidate the cache lines covering a range the
 * controller can reach. QEMU (and non-coherent silicon) reads device memory
 * out of RAM rather than out of the CPU's caches, so a TRB that is still
 * dirty in a write-back line is invisible to the controller, and an event
 * TRB the controller just wrote is invisible to a guest that holds a stale
 * cached copy. Flushing both hands the buffer over explicitly. On coherent
 * hardware this is a cheap no-op for correctness, never a requirement. */
static void xhc_flush(const void *p, unsigned long len) {
    unsigned long a = (unsigned long)p & ~63UL;
    unsigned long e = (unsigned long)p + len;
    for (; a < e; a += 64)
        __asm__ volatile("clflush (%0)" :: "r"(a) : "memory");
}

static void xhc_idle(unsigned spin) {
    for (volatile unsigned i = 0; i < spin; i++)
        __asm__ volatile("pause");
}

/* ---- Context addressing ----
 * Device context N lives at xhc_ctx + N * stride; slot 0 is unused. */
static unsigned char *xhc_slot_ctx(int slot) {
    return xhc_ctx + (unsigned long)(unsigned)slot * xhc_stride();
}

static unsigned char *xhc_ep_ctx(int slot, int ep) {
    return xhc_slot_ctx(slot) + xhc_ep_b() +
           (unsigned long)(unsigned)ep * xhc_ep_b();
}

static unsigned char *xhc_in_slot(void) {
    return xhc_in_ctx + xhc_ep_b();
}

static unsigned char *xhc_in_ep(int ci) {
    return xhc_in_slot() + xhc_ep_b() + (unsigned long)(unsigned)ci * xhc_ep_b();
}

/** Docstring: Build one 32-byte endpoint context per spec Table 140. */
static void xhc_ep_ctx_build(unsigned char *ep, unsigned type,
                             unsigned maxp, unsigned mult, unsigned burst,
                             unsigned interval, unsigned dcs,
                             unsigned long long dequeue) {
    unsigned dw0;
    unsigned dw1;
    kmemset(ep, 0, xhc_ep_b());
    dw0 = ((mult & 0x3u) << XHC_EP_MULT_SHIFT) |
          ((interval & 0xFFu) << XHC_EP_INTERVAL_SHIFT);
    dw1 = (XHC_EP_CERR & 0x3u) |
          ((type & 0x7u) << XHC_EP_TYPE_SHIFT) |
          ((burst & 0xFFu) << XHC_EP_BURST_SHIFT) |
          ((maxp & 0xFFFFu) << XHC_EP_MAXP_SHIFT);
    xhc_put32(ep, XHC_EP_DW0_OFF, dw0);
    xhc_put32(ep, XHC_EP_DW1_OFF, dw1);
    xhc_put64(ep, XHC_EP_DEQ_OFF,
              (dequeue & ~0xFu) | (dcs ? XHC_EP_DCS_BIT : 0u));
    xhc_put32(ep, XHC_EP_AVG_OFF, 8u);
}

/** Docstring: Build one 32-byte slot context: speed, entries and root port. */
static void xhc_slot_ctx_build(unsigned char *sc, unsigned speed,
                               unsigned entries, unsigned rhport) {
    unsigned dw0;
    kmemset(sc, 0, xhc_ep_b());
    dw0 = ((speed & 0xFu) << XHC_SLOT_SPEED_SHIFT) |
          ((entries & 0x1Fu) << XHC_SLOT_ENTRIES_SHIFT);
    xhc_put32(sc, XHC_SLOT_DW0_OFF, dw0);
    xhc_put32(sc, XHC_SLOT_DW1_OFF,
              (rhport & 0xFFu) << XHC_SLOT_RHPORT_SHIFT);
}

/* ---- Command ring ---- */

/** Docstring: Toggle-cycle bit of a Link TRB. Set, so the controller toggles
 * its expected cycle when it follows the link instead of reading the next
 * generation as stale. */
#define XF_LINK_TC 2u

/** Docstring: Arm the link TRB with the current generation. */
static void xhc_arm_link_trb(xhc_trb_t *ring, unsigned gen) {
    xhc_trb_t *link = &ring[XHC_RING_USABLE];
    xhc_puttrb(link, (unsigned long long)(unsigned long)ring, 0,
               (unsigned)(XHC_TRB_MAKE_TYPE(XHC_TRB_TYPE_LINK) |
                          (unsigned long long)gen | XF_LINK_TC));
}

static void xhc_arm_link(void) {
    xhc_arm_link_trb(xhc_cmd, xhc_cmd_gen);
}

/** Docstring: Re-arm a ring's link, but never at the wrap itself. The
 * controller trails the producer by at most one transfer here, so at wrap
 * time it is about to fetch the link with the old generation: flipping
 * the link then reads as stale and the ring stops forever. The re-arm
 * waits until the producer is halfway round the new lap, when the link
 * is a full lap behind the controller. */
static int xhc_cmd_rearm;

static void xhc_cmd_wrap(void) {
    xhc_cmd_enq = 0;
    xhc_cmd_gen ^= 1u;
    xhc_cmd_rearm = 1;
}

static void xhc_cmd_maybe_arm(void) {
    if (xhc_cmd_rearm && xhc_cmd_enq >= XHC_RING_USABLE / 2u) {
        xhc_arm_link();
        xhc_cmd_rearm = 0;
    }
}

/** Docstring: Fill one command-ring slot without ringing the doorbell. The
 * caller batches its TRBs and rings once. Wraps instead of refusing: a
 * ring that goes deaf after 1023 commands turns a long-lived machine
 * into a hang. */
static xhc_trb_t *xhc_cmd_slot(void) {
    xhc_trb_t *trb;
    if (!xhc_cmd) return 0;
    if (xhc_cmd_enq >= XHC_RING_USABLE) xhc_cmd_wrap();
    trb = &xhc_cmd[xhc_cmd_enq++];
    xhc_cmd_maybe_arm();
    return trb;
}

/** Docstring: Ring the command doorbell. Per spec section 5.4 the host
 * controller doorbell is array entry 0 written with target 0: the controller
 * tracks the ring itself and any other value is undefined. */
static void xhc_cmd_ring_doorbell(void) {
    hal_mmio_wmb();
    hal_mmio_write32((volatile unsigned *)xhc_db, 0u);
}

/* ---- Doorbell array: entry N lives at byte offset N * 4, carrying the
 * DCI target in its low byte. Entry 0 is the controller doorbell, rung with
 * zero. ---- */
#define XHC_DB_STRIDE 4u
#define XHC_DB_COMMAND 0u

/** Docstring: Ring a slot doorbell for endpoint context index ep: DCI is the
 * index plus one, and EP0 rings target 1. */
static void xhc_slot_doorbell(int slot, int ep) {
    unsigned target = (unsigned)ep + 1u;
    hal_mmio_wmb();
    hal_mmio_write32(
        (volatile unsigned *)(xhc_db + (unsigned)slot * XHC_DB_STRIDE),
        target);
}

/* ---- Event ring ---- */

/** Docstring: Next event TRB, or 0 when the ring is empty.
 *
 * The cycle bit separates generations, so a slot the controller has not
 * written reads as "not mine" and the drain stops without needing a count.
 * The read is fenced before the slot is released, or the next poll re-reads
 * a stale cached copy as a fresh event. */
static xhc_trb_t *xhc_evt_next(void) {
    xhc_trb_t *trb = &xhc_evt[xhc_evt_deq];
    xhc_flush(trb, sizeof(*trb));
    if (XHC_TRB_CYCLE(trb) != xhc_evt_expect) return 0;
    xhc_evt_deq++;
    if (xhc_evt_deq >= XHC_TRB_RING_TRBS) {
        xhc_evt_deq = 0;
        xhc_evt_expect ^= 1u;
    }
    hal_mmio_rmb();
    xhc_ctr.events_seen++;
    return trb;
}

/** Docstring: The TRB a completion names, as a host pointer. The value is a
 * physical address and the kernel is identity mapped there, which is the
 * reason every ring here is a heap object. */
static xhc_trb_t *xhc_evt_trb_ptr(xhc_trb_t *ev) {
    return (xhc_trb_t *)(unsigned long)ev->param;
}

/** Docstring: Tell the controller the event ring was drained: ERDP advances
 * to the dequeue pointer with EHB set to clear the handler-busy latch, so a
 * poll that never reports back stalls the ring after one segment. */
static void xhc_evt_advance(void) {
    unsigned long long phys =
        (unsigned long long)(unsigned long)&xhc_evt[xhc_evt_deq];
    unsigned lo = (unsigned)(phys & 0xFFFFFFF0u) | XHC_ERDP_EHB;
    unsigned hi = (unsigned)(phys >> 32);
    xhc_run_write32(XHC_RUN_INTR0 + XHC_RUN_ERDP, lo);
    xhc_run_write32(XHC_RUN_INTR0 + XHC_RUN_ERDP + 4u, hi);
}

/* ---- Pending transfer table ---- */

static int xhc_pending_claim_len(xhc_trb_t *trb, unsigned len) {
    int i;
    for (i = 0; i < XHC_MAX_PENDING; i++) {
        if (xhc_pending[i].used) continue;
        xhc_pending[i].trb = trb;
        xhc_pending[i].len = len;
        xhc_pending[i].got = 0;
        xhc_pending[i].status = 0;
        xhc_pending[i].done = 0;
        xhc_pending[i].used = 1;
        xhc_pending[i].since = xhc_now_ms();
        return i + 1;
    }
    return 0;
}

static int xhc_pending_claim(xhc_trb_t *trb) {
    return xhc_pending_claim_len(trb, 0);
}

static void xhc_pending_drop(int token) {
    if (token < 1 || token > XHC_MAX_PENDING) return;
    xhc_pending[token - 1].used = 0;
}

int xhc_poll(void) {
    xhc_trb_t *ev;
    int handled = 0;
    if (!xhc_evt) return 0;
    while ((ev = xhc_evt_next()) != 0) {
        handled = 1;
        if (XHC_EVT_TYPE(ev) != XHC_EVT_TRANSFER) {
            /* Command completions are collected by xhc_cmd_wait, which
             * drains the same ring, so anything left here belongs to a
             * command nobody is waiting for and is only counted. */
            xhc_ctr.events_unmatched++;
            continue;
        }
        {
            unsigned cc = XHC_EVT_CC(ev);
            xhc_trb_t *target = xhc_evt_trb_ptr(ev);
            int i;
            for (i = 0; i < XHC_MAX_PENDING; i++) {
                xhc_pending_t *p = &xhc_pending[i];
                unsigned left;
                if (!p->used || p->done) continue;
                if (p->trb != target) continue;
                p->done = 1;
                p->status = (cc == XHC_CC_SUCCESS ||
                             cc == XHC_CC_SHORT_PACKET) ? 1 : 0;
                left = XHC_EVT_LEN(ev);
                if (left > p->len) left = p->len;
                p->got = p->len - left;
                break;
            }
            if (cc == XHC_CC_SUCCESS || cc == XHC_CC_SHORT_PACKET)
                xhc_ctr.xfers_done++;
            else
                xhc_ctr.xfers_failed++;
        }
    }
    if (handled) xhc_evt_advance();
    return handled;
}

/** Docstring: Wait for a pending transfer to complete. Returns 1 on
 * completion, 0 on timeout, and drops the claim either way so a timed-out
 * waiter cannot hold the table shut forever. */
static int xhc_wait(int token, unsigned budget_ms) {
    unsigned long end;
    if (token < 1 || token > XHC_MAX_PENDING) return 0;
    end = xhc_now_ms() + budget_ms;
    for (;;) {
        xhc_poll();
        if (xhc_pending[token - 1].done) return 1;
        if ((long)(xhc_now_ms() - end) >= 0) {
            xhc_pending_drop(token);
            return 0;
        }
        xhc_idle(256);
    }
}

/** Docstring: Outcome of a completed transfer. */
static int xhc_status(int token) {
    if (token < 1 || token > XHC_MAX_PENDING) return 0;
    return xhc_pending[token - 1].status;
}

/** Docstring: Submit one command TRB and wait for its completion, by TRB
 * pointer so a completion for anything else is counted rather than handed to
 * the wrong waiter. Returns 1 when the controller reported success, 0
 * otherwise, with the raw completion code and any returned slot id. */
static int xhc_cmd_run_ep(unsigned type, unsigned long long param,
                            unsigned slot, unsigned epid, unsigned *code,
                            unsigned *slot_id) {
    xhc_trb_t *trb = xhc_cmd_slot();
    unsigned long end;
    if (!trb) return 0;
    xhc_puttrb(trb, param, 0,
               (unsigned)(XHC_TRB_MAKE_TYPE(type) | xhc_cmd_gen |
                          ((slot & 0xFFu) << 24) |
                          ((epid & 0x1Fu) << 16)));
    xhc_flush(trb, sizeof(*trb));
    xhc_cmd_ring_doorbell();
    end = xhc_now_ms() + XHC_CMD_BUDGET_MS;
    for (;;) {
        xhc_trb_t *ev = xhc_evt_next();
        if (ev) {
            if (XHC_EVT_TYPE(ev) == XHC_EVT_CMD_COMPLETION &&
                xhc_evt_trb_ptr(ev) == trb) {
                unsigned c = XHC_EVT_CC(ev);
                if (code) *code = c;
                if (slot_id) *slot_id = XHC_EVT_SLOT(ev);
                if (c == XHC_CC_SUCCESS) xhc_ctr.cmd_ok++;
                else {
                    xhc_ctr.cmd_failed++;
                    kprintf("usb dbg: cmd type %u failed cc=%u slot=%u\n",
                            type, c, XHC_EVT_SLOT(ev));
                }
                xhc_evt_advance();
                return c == XHC_CC_SUCCESS;
            }
            if (XHC_EVT_TYPE(ev) == XHC_EVT_TRANSFER) {
                xhc_ctr.events_unmatched++;
            } else {
                xhc_ctr.events_unmatched++;
            }
            xhc_evt_advance();
            continue;
        }
        if ((long)(xhc_now_ms() - end) >= 0) {
            xhc_ctr.cmd_timeout++;
            return 0;
        }
        xhc_idle(256);
    }
}

static int xhc_cmd_run(unsigned type, unsigned long long param, unsigned slot,
                       unsigned *code, unsigned *slot_id) {
    return xhc_cmd_run_ep(type, param, slot, 0, code, slot_id);
}

/** Docstring: Stop, reset and re-point one endpoint's transfer ring. Stop
 * works from any state and drops whatever the endpoint was chewing on;
 * reset clears a halt; set-dequeue hands the ring back at the producer's
 * current position with its generation, so a Bulk-Only recovery can
 * continue on the same ring instead of rebuilding the endpoint. */
static int xhc_ep_command(unsigned type, int slot, int dci) {
    return xhc_cmd_run_ep(type, 0, (unsigned)slot, (unsigned)dci, 0, 0);
}

int xhc_reset_endpoint(int index, int ep_index) {
    int slot;
    int dci;
    xhc_ring_t *ring;
    unsigned long long dequeue;
    if (index < 0 || index >= XHC_MAX_DEVICES) return 0;
    if (!xhc_devs[index].used && !xhc_rings[index][ep_index].trbs) return 0;
    if (ep_index < 1 || ep_index >= XHC_EP_INDEX_LIMIT) return 0;
    ring = &xhc_rings[index][ep_index];
    if (!ring->trbs || ring->dci < 2) return 0;
    slot = xhc_devs[index].slot;
    dci = ring->dci;
    xhc_ep_command(XHC_TRB_TYPE_STOP_ENDPOINT, slot, dci);
    xhc_ep_command(XHC_TRB_TYPE_RESET_ENDPOINT, slot, dci);
    dequeue = (unsigned long long)(unsigned long)&ring->trbs[ring->enq];
    xhc_cmd_run_ep(XHC_TRB_TYPE_SET_DEQUEUE, dequeue | (ring->gen & 1u),
                   (unsigned)slot, (unsigned)dci, 0, 0);
    hal_mmio_wmb();
    hal_mmio_write32(
        (volatile unsigned *)(xhc_db + (unsigned)slot * XHC_DB_STRIDE),
        (unsigned)dci);
    return 1;
}

/* ---- Ports ---- */

int xhc_port_count(void) {
    return (int)xhc_port_limit;
}

int xhc_port_state(int port, xhc_port_t *out) {
    unsigned sc;
    if (out) {
        out->connected = 0;
        out->enabled = 0;
        out->speed = 0;
        out->power = 0;
    }
    if (!xhc_mmio) return 0;
    if (port < 0 || (unsigned)port >= xhc_port_limit) return 0;
    sc = xhc_op_read32(XHC_OP_PORTSC + (unsigned)port * XHC_PORT_STRIDE);
    if (out) {
        out->connected = (sc & XHC_PORT_CCS) != 0;
        out->enabled = (sc & XHC_PORT_PED) != 0;
        out->power = (sc & XHC_PORT_PP) != 0;
        out->speed = (int)((sc & XHC_PORT_SPEED_MASK) >> XHC_PORT_SPEED_SHIFT);
    }
    return 1;
}

/** Docstring: Ask a port to reset, and wait for it to settle. Per spec the
 * reset bit is PORTSC bit 4: set it with the W1C change bits written clear,
 * then wait for PED set and PR clear. Returns 1 on a connected device. */
int xhc_port_reset(int port) {
    unsigned sc;
    unsigned long end;
    if (!xhc_mmio) return 0;
    if (port < 0 || (unsigned)port >= xhc_port_limit) return 0;
    {
        sc = xhc_op_read32(XHC_OP_PORTSC + (unsigned)port * XHC_PORT_STRIDE);
        sc = (sc & ~XHC_PORT_CHG_MASK) | XHC_PORT_PR;
        xhc_op_write32(XHC_OP_PORTSC + (unsigned)port * XHC_PORT_STRIDE, sc);
        end = xhc_now_ms() + XHC_PORT_BUDGET_MS;
        for (;;) {
            sc = xhc_op_read32(XHC_OP_PORTSC + (unsigned)port *
                               XHC_PORT_STRIDE);
            if ((sc & XHC_PORT_PED) && !(sc & XHC_PORT_PR)) break;
            if ((long)(xhc_now_ms() - end) >= 0) break;
            xhc_idle(1024);
        }
        if ((sc & XHC_PORT_PED) && !(sc & XHC_PORT_PR)) {
            /* A settled reset is reported by the change bit and a connected
             * device. Enabled and Power are not demanded: a controller that
             * does not publish them is still usable, and refusing on their
             * absence would reject a working port. */
            return (sc & XHC_PORT_CCS) != 0;
        }
    }
    return 0;
}

/* ---- Device records ---- */

int xhc_device_count(void) {
    int n = 0;
    int i;
    for (i = 0; i < XHC_MAX_DEVICES; i++)
        if (xhc_devs[i].used) n++;
    return n;
}

int xhc_device_info(int index, xhc_dev_t *out) {
    if (out) {
        out->slot = -1;
        out->port = -1;
        out->speed = 0;
        out->address = 0;
    }
    if (index < 0 || index >= XHC_MAX_DEVICES) return 0;
    if (!xhc_devs[index].used) return 0;
    if (out) {
        out->slot = xhc_devs[index].slot;
        out->port = xhc_devs[index].port;
        out->speed = xhc_devs[index].speed;
        out->address = xhc_devs[index].address;
    }
    return 1;
}

/** Docstring: Allocate a free device record, or -1. */
static int xhc_dev_alloc(void) {
    int i;
    for (i = 0; i < XHC_MAX_DEVICES; i++)
        if (!xhc_devs[i].used) return i;
    return -1;
}

/** Docstring: Release one device record after a failed enumeration: its EP0
 * ring and cached descriptor go back, so a retry starts clean instead of
 * refusing on its own leftover ring. */
static void xhc_dev_release(int index) {
    int e;
    if (index < 0 || index >= XHC_MAX_DEVICES) return;
    for (e = 0; e < XHC_EP_INDEX_LIMIT; e++) {
        if (xhc_rings[index][e].trbs) {
            kfree(xhc_rings[index][e].trbs);
            xhc_rings[index][e].trbs = 0;
            xhc_rings[index][e].configured = 0;
        }
    }
    if (xhc_devs[index].config) {
        kfree(xhc_devs[index].config);
        xhc_devs[index].config = 0;
    }
    xhc_devs[index].used = 0;
    xhc_devs[index].slot = 0;
}

/* ---- Interface walk ---- */

int xhc_open_interface(int index, unsigned cls, unsigned sub, unsigned proto,
                       xhc_iface_t *out) {
    const unsigned char *cfg;
    unsigned len;
    unsigned pos;
    int cur = 0;
    int iface = 0;
    int n_ep = 0;
    if (!out) return 0;
    out->cls = 0;
    out->sub = 0;
    out->proto = 0;
    out->iface = 0;
    out->num_eps = 0;
    if (index < 0 || index >= XHC_MAX_DEVICES) return 0;
    if (!xhc_devs[index].used) return 0;
    cfg = xhc_devs[index].config;
    len = xhc_devs[index].config_len;
    if (!cfg || len < 9) return 0;
    pos = 0;
    while (pos + 2 <= len) {
        unsigned bLength = cfg[pos];
        unsigned bType = cfg[pos + 1];
        /* A zero or short bLength would either loop forever or read past the
         * buffer, so the walk ends instead of trusting it. */
        if (bLength < 2 || pos + bLength > len) break;
        if (bType == XHC_DT_INTERFACE && bLength >= 9) {
            if (cur && n_ep) break;
            cur = ((cls == 0xFFu ||
                    cfg[pos + XHC_IFACE_CLASS_OFF] == cls) &&
                   (sub == 0xFFu ||
                    cfg[pos + XHC_IFACE_SUBCLASS_OFF] == sub) &&
                   (proto == 0xFFu ||
                    cfg[pos + XHC_IFACE_PROTO_OFF] == proto));
            iface = cfg[pos + XHC_IFACE_OFF];
            n_ep = 0;
        } else if (bType == XHC_DT_ENDPOINT && bLength >= 7 && cur) {
            if (n_ep < XHC_MAX_EPS) {
                out->ep_addr[n_ep] = (int)cfg[pos + XHC_EP_DESC_ADDR_OFF];
                out->ep_type[n_ep] =
                    (int)(cfg[pos + XHC_EP_DESC_TYPE_OFF] & 3u);
                out->ep_maxp[n_ep] = (int)(cfg[pos + XHC_EP_DESC_MAXP_OFF] |
                    ((unsigned)cfg[pos + XHC_EP_DESC_MAXP_OFF + 1u] << 8));
                n_ep++;
            }
        }
        pos += bLength;
    }
    if (cur && n_ep) {
        out->cls = (int)cls;
        out->sub = (int)sub;
        out->proto = (int)proto;
        out->iface = iface;
        out->num_eps = n_ep;
        return 1;
    }
    out->num_eps = 0;
    return 0;
}

/* ---- Control transfers ---- */
#define XHC_TRB_IOC (1u << 5)
#define XHC_TRB_IDT (1u << 6)
#define XHC_TRB_DIR (1u << 16)
#define XHC_TRT_OUT 2u
#define XHC_TRT_IN 3u

/** Docstring: Wrap a transfer ring instead of refusing after a thousand
 * transfers: the producer goes back to slot zero with the toggled
 * generation and the endpoint context DCS follows it at once, while the
 * link keeps the old generation until the producer is halfway round
 * (see xhc_cmd_rearm: re-arming at the wrap itself races the controller
 * into reading the link stale and the ring stops forever). */
static void xhc_ring_wrap(int index, xhc_ring_t *ring, int ep) {
    unsigned char *ctx;
    unsigned deq;
    ring->enq = 0;
    ring->gen ^= 1u;
    ring->rearm = 1;
    ctx = xhc_ep_ctx(xhc_devs[index].slot, ep);
    deq = xhc_get32(ctx, XHC_EP_DEQ_OFF);
    if (ring->gen) deq |= XHC_EP_DCS_BIT;
    else deq &= ~XHC_EP_DCS_BIT;
    xhc_put32(ctx, XHC_EP_DEQ_OFF, deq);
}

static void xhc_ring_maybe_arm(xhc_ring_t *ring) {
    if (ring->rearm && ring->enq >= XHC_RING_USABLE / 2u) {
        xhc_arm_link_trb(ring->trbs, ring->gen);
        ring->rearm = 0;
    }
}

/** Docstring: Post one TRB on a device EP0 transfer ring, wrapping instead
 * of refusing. The gate is the ring, not the used flag: control transfers
 * run during enumeration, before the record is marked used. */
static xhc_trb_t *xhc_ep0_slot(int index) {
    xhc_ring_t *ring;
    xhc_trb_t *trb;
    if (index < 0 || index >= XHC_MAX_DEVICES) return 0;
    ring = &xhc_rings[index][0];
    if (!ring->trbs) return 0;
    if (ring->enq >= XHC_RING_USABLE) xhc_ring_wrap(index, ring, 0);
    trb = &ring->trbs[ring->enq++];
    xhc_ring_maybe_arm(ring);
    return trb;
}

static void xhc_ep0_bump(int index) {
    hal_mmio_wmb();
    xhc_slot_doorbell(xhc_devs[index].slot, 0);
}

/** Docstring: One control transfer on the device EP0 transfer ring: a setup
 * TRB with IDT, an optional data TRB and a status TRB with IOC, behind one
 * slot doorbell. Only the status stage is waited on. */
static int xhc_control_stage(int index, const unsigned char setup[8],
                              void *data, unsigned len, int host_to_device) {
    xhc_ring_t *ring;
    xhc_trb_t *trb;
    int token;
    unsigned long long sparam;
    unsigned trt;
    unsigned data_dir;
    unsigned status_dir;
    int is_in;
    if (index < 0 || index >= XHC_MAX_DEVICES) return 0;
    if (len > 0xFFFFu) return 0;
    ring = &xhc_rings[index][0];
    if (!ring->trbs) return 0;
    if (ring->enq + (len ? 3u : 2u) > XHC_RING_USABLE)
        xhc_ring_wrap(index, ring, 0);

    is_in = (setup[0] & 0x80) != 0;
    if (!len) trt = 0;
    else if (host_to_device || !is_in) trt = XHC_TRT_OUT;
    else trt = XHC_TRT_IN;
    data_dir = host_to_device ? 0u : XHC_TRB_DIR;
    if (!len) status_dir = is_in ? 0u : XHC_TRB_DIR;
    else status_dir = host_to_device ? XHC_TRB_DIR : 0u;

    sparam = (unsigned long long)setup[0] |
             ((unsigned long long)setup[1] << 8) |
             ((unsigned long long)setup[2] << 16) |
             ((unsigned long long)setup[3] << 24) |
             ((unsigned long long)setup[4] << 32) |
             ((unsigned long long)setup[5] << 40) |
             ((unsigned long long)setup[6] << 48) |
             ((unsigned long long)setup[7] << 56);

    trb = xhc_ep0_slot(index);
    if (!trb) return 0;
    xhc_puttrb(trb, sparam, 8,
               (unsigned)(XHC_TRB_MAKE_TYPE(XHC_TRB_TYPE_SETUP) |
                          ring->gen | XHC_TRB_IDT | (trt << 16)));
    xhc_flush(trb, sizeof(*trb));

    if (len) {
        trb = xhc_ep0_slot(index);
        if (!trb) return 0;
        xhc_puttrb(trb, (unsigned long long)(unsigned long)data,
                   len & 0x1FFFFu,
                   (unsigned)(XHC_TRB_MAKE_TYPE(XHC_TRB_TYPE_DATA) |
                              ring->gen | data_dir));
        xhc_flush(trb, sizeof(*trb));
        xhc_flush(data, len);
    }

    trb = xhc_ep0_slot(index);
    if (!trb) return 0;
    xhc_puttrb(trb, 0, 0,
               (unsigned)(XHC_TRB_MAKE_TYPE(XHC_TRB_TYPE_STATUS) |
                          ring->gen | status_dir | XHC_TRB_IOC));
    xhc_flush(trb, sizeof(*trb));
    token = xhc_pending_claim(trb);
    if (!token) return 0;
    xhc_ep0_bump(index);
    return token;
}

/** Docstring: USB is lossy and emulated controllers occasionally drop a
 * completion, so a control transfer retries its whole setup-data-status
 * stage up to three times before reporting failure. A stall or a refused
 * stage is not retried: only a missing or failed completion is. */
#define XHC_CONTROL_TRIES 3u
int xhc_control(int index, const unsigned char setup[8], void *data,
                unsigned len, int host_to_device) {
    unsigned t;
    for (t = 0; t < XHC_CONTROL_TRIES; t++) {
        int token = xhc_control_stage(index, setup, data, len,
                                      host_to_device);
        if (!token) return 0;
        if (!xhc_wait(token, XHC_XFER_BUDGET_MS)) continue;
        if (xhc_status(token) != 1) {
            xhc_pending_drop(token);
            continue;
        }
        if (data && len && !host_to_device) xhc_flush(data, len);
        xhc_pending_drop(token);
        return 1;
    }
    return 0;
}

/** Docstring: Pack a standard request with no data stage: bmRequestType,
 * bRequest, wValue, wIndex. */
static void xhc_setup_nodata(unsigned char *setup, unsigned char type,
                             unsigned char req, unsigned value,
                             unsigned index) {
    setup[0] = type;
    setup[1] = req;
    xhc_put16(setup, 2, value);
    xhc_put16(setup, 4, index);
    setup[6] = 0;
    setup[7] = 0;
}

/** Docstring: Pack a standard request with a data stage of a known length:
 * same as above with wLength filled in. */
static void xhc_setup_data(unsigned char *setup, unsigned char type,
                           unsigned char req, unsigned value,
                           unsigned index, unsigned len) {
    xhc_setup_nodata(setup, type, req, value, index);
    xhc_put16(setup, 6, len);
}

/* ---- Endpoints ---- */

/** Docstring: Endpoint context index for a USB endpoint address: DCI is one
 * plus twice the endpoint number plus the direction, with EP0 at DCI 1. */
static int xhc_dci(int ep_addr) {
    int num = ep_addr & 0x0F;
    int dir = (ep_addr & XHC_EP_DIR_IN) != 0;
    if (num == 0) return 1;
    return 2 * num + dir;
}

int xhc_configure_endpoint(int index, int ep_index, int ep_addr, int ep_type,
                           int max_packet, int mult, int interval, int burst) {
    int slot;
    int is_out;
    int dci;
    unsigned etype;
    xhc_ring_t *ring;
    unsigned long long ring_addr;
    unsigned char *ep_new;

    if (index < 0 || index >= XHC_MAX_DEVICES) return 0;
    if (!xhc_devs[index].used) return 0;
    if (ep_index < 1 || ep_index >= XHC_EP_INDEX_LIMIT) return 0;
    if (max_packet <= 0 || max_packet > 1024) return 0;

    slot = xhc_devs[index].slot;
    is_out = (ep_addr & XHC_EP_DIR_IN) == 0;
    ring = &xhc_rings[index][ep_index];
    if (ring->trbs) return 0;

    if (XHC_TRB_RING_TRBS > (0xFFFFFFFFu / sizeof(xhc_trb_t))) return 0;
    ring->trbs = (xhc_trb_t *)kmalloc_aligned(
        (unsigned long)XHC_TRB_RING_TRBS * sizeof(xhc_trb_t), XHC_DMA_ALIGN);
    if (!ring->trbs) return 0;
    kmemset(ring->trbs, 0,
            (unsigned long)XHC_TRB_RING_TRBS * sizeof(xhc_trb_t));
    ring->enq = 0;
    ring->gen = 1;
    ring->is_out = is_out;
    ring->configured = 1;
    ring->rearm = 0;
    ring_addr = (unsigned long long)(unsigned long)ring->trbs;
    xhc_arm_link_trb(ring->trbs, ring->gen);
    kmm_make_uncached((unsigned long)ring->trbs,
                      (unsigned long)XHC_TRB_RING_TRBS * sizeof(xhc_trb_t));

    dci = xhc_dci(ep_addr);
    if (dci < 2 || dci > 31) return 0;
    if (ep_type == XHC_EP_BULK) etype = is_out ? XHC_EPT_BULK_OUT : XHC_EPT_BULK_IN;
    else etype = is_out ? XHC_EPT_INT_OUT : XHC_EPT_INT_IN;
    ring->dci = dci;
    ep_new = xhc_ep_ctx(slot, dci - 1);
    xhc_ep_ctx_build(ep_new, etype, (unsigned)max_packet, (unsigned)mult,
                     (unsigned)burst, (unsigned)interval, 1, ring_addr);

    xhc_put32(xhc_in_ctx, XHC_ICTX_DROP_OFF, 0);
    xhc_put32(xhc_in_ctx, XHC_ICTX_ADD_OFF,
              0x01u | (1u << (unsigned)dci));
    kmemcpy(xhc_in_slot(), xhc_slot_ctx(slot), xhc_ep_b());
    kmemcpy(xhc_in_ep(0), xhc_ep_ctx(slot, 0), xhc_ep_b());
    kmemcpy(xhc_in_ep(dci - 1), ep_new, xhc_ep_b());
    hal_mmio_wmb();
    xhc_flush(xhc_in_ctx, XHC_ICTX_BYTES);
    if (!xhc_cmd_run(XHC_TRB_TYPE_CONFIGURE_ENDPOINT,
                     (unsigned long long)(unsigned long)xhc_in_ctx,
                     (unsigned)slot, 0, 0))
        return 0;
    return 1;
}

/** Docstring: Post one Normal TRB with IOC on an endpoint's ring and ring its
 * slot doorbell. Returns the pending token, or 0 on refusal. */
static int xhc_ep_post(int index, int ep_index, void *buf, unsigned len) {
    xhc_ring_t *ring;
    xhc_trb_t *trb;
    int token;
    int slot;

    if (index < 0 || index >= XHC_MAX_DEVICES) return 0;
    if (!xhc_devs[index].used) return 0;
    if (ep_index < 1 || ep_index >= XHC_EP_INDEX_LIMIT) return 0;
    ring = &xhc_rings[index][ep_index];
    if (!ring->configured || !ring->trbs) return 0;
    if (ring->enq >= XHC_RING_USABLE)
        xhc_ring_wrap(index, ring, ring->dci - 1);
    trb = &ring->trbs[ring->enq++];
    xhc_ring_maybe_arm(ring);
    token = xhc_pending_claim_len(trb, len);
    if (!token) {
        ring->enq--;
        return 0;
    }
    xhc_puttrb(trb, (unsigned long long)(unsigned long)buf,
               len & 0x1FFFFu,
               (unsigned)(XHC_TRB_MAKE_TYPE(XHC_TRB_TYPE_NORMAL) |
                          ring->gen | XHC_TRB_IOC));
    xhc_flush(trb, sizeof(*trb));
    if (ring->is_out) xhc_flush(buf, len);
    slot = xhc_devs[index].slot;
    hal_mmio_wmb();
    hal_mmio_write32(
        (volatile unsigned *)(xhc_db + (unsigned)slot * XHC_DB_STRIDE),
        (unsigned)ring->dci);
    return token;
}

/** Docstring: Actual bytes moved, for short-packet honesty. */
static int xhc_got(int token) {
    if (token < 1 || token > XHC_MAX_PENDING) return 0;
    return (int)xhc_pending[token - 1].got;
}

int xhc_transfer(int index, int ep_index, void *buf, unsigned len, int *got) {
    int token = xhc_ep_post(index, ep_index, buf, len);
    int moved;
    if (got) *got = 0;
    if (!token) return 0;
    if (!xhc_wait(token, XHC_XFER_BUDGET_MS)) return 0;
    if (xhc_status(token) != 1) {
        xhc_pending_drop(token);
        return 0;
    }
    moved = xhc_got(token);
    if (buf && len) xhc_flush(buf, len);
    if (got) *got = moved;
    xhc_pending_drop(token);
    return 1;
}

/** Docstring: Post one endpoint transfer without waiting: the completion
 * arrives on the event ring and is collected by xhc_poll_token. Returns the
 * token, or 0 on refusal. */
int xhc_transfer_async(int index, int ep_index, void *buf, unsigned len) {
    return xhc_ep_post(index, ep_index, buf, len);
}

/** Docstring: Non-blocking completion check for xhc_transfer_async. Drains
 * the ring, then reports 1 on success, -1 on a failed completion, -2 on a
 * wait past the budget, and 0 while still outstanding. Consumed tokens are
 * dropped, so a caller that polls to completion never leaks the table. A
 * zero budget never expires: an interrupt endpoint with nothing to say
 * answers NAK rather than an event, and expiring its only transfer orphans
 * the report it eventually delivers to a token nobody holds. */
int xhc_poll_token_limit(int token, unsigned budget_ms) {
    unsigned long age;
    if (token < 1 || token > XHC_MAX_PENDING) return -1;
    xhc_poll();
    if (xhc_pending[token - 1].done) {
        int ok = xhc_status(token) == 1;
        xhc_pending_drop(token);
        return ok ? 1 : -1;
    }
    if (budget_ms) {
        age = xhc_now_ms() - xhc_pending[token - 1].since;
        if ((long)age >= (long)budget_ms) {
            xhc_pending_drop(token);
            return -2;
        }
    }
    return 0;
}

int xhc_poll_token(int token) {
    return xhc_poll_token_limit(token, XHC_XFER_BUDGET_MS);
}

/* ---- Enumeration ---- */

/** Docstring: Enable a slot and build its device context with a working
 * control endpoint on its own transfer ring. The input context adds the slot
 * and EP0; the DCBAA entry points at the output device context. */
static int xhc_address(int index, int slot, int port, int speed) {
    unsigned char *dctx = xhc_slot_ctx(slot);
    unsigned char *ep0 = xhc_ep_ctx(slot, 0);
    xhc_ring_t *ring = &xhc_rings[index][0];
    unsigned long long ring_addr;
    unsigned code = 0;
    unsigned got_slot = 0;

    if (ring->trbs) return 0;
    ring->trbs = (xhc_trb_t *)kmalloc_aligned(
        (unsigned long)XHC_TRB_RING_TRBS * sizeof(xhc_trb_t), XHC_DMA_ALIGN);
    if (!ring->trbs) return 0;
    kmemset(ring->trbs, 0,
            (unsigned long)XHC_TRB_RING_TRBS * sizeof(xhc_trb_t));
    ring->enq = 0;
    ring->gen = 1;
    ring->is_out = 0;
    ring->configured = 1;
    ring->dci = 1;
    ring->rearm = 0;
    ring_addr = (unsigned long long)(unsigned long)ring->trbs;
    xhc_arm_link_trb(ring->trbs, ring->gen);
    kmm_make_uncached((unsigned long)ring->trbs,
                      (unsigned long)XHC_TRB_RING_TRBS * sizeof(xhc_trb_t));

    xhc_slot_ctx_build(dctx, (unsigned)speed, 1, (unsigned)port + 1u);
    xhc_put32(dctx, XHC_SLOT_ADDR_OFF, (unsigned)slot & 0xFFu);
    xhc_devs[index].slot = slot;
    xhc_devs[index].port = port;
    xhc_devs[index].speed = speed;
    xhc_devs[index].address = slot;
    xhc_ep_ctx_build(ep0, XHC_EPT_CONTROL,
                     speed >= XHC_SPEED_SUPER ? 512u :
                     speed >= XHC_SPEED_HIGH ? 64u : 8u,
                     0, 0, 0, 1, ring_addr);
    xhc_dbaa[slot] = (unsigned long long)(unsigned long)dctx;

    xhc_put32(xhc_in_ctx, XHC_ICTX_DROP_OFF, 0);
    xhc_put32(xhc_in_ctx, XHC_ICTX_ADD_OFF, 0x03u);
    kmemcpy(xhc_in_slot(), dctx, xhc_ep_b());
    kmemcpy(xhc_in_ep(0), ep0, xhc_ep_b());
    hal_mmio_wmb();
    xhc_flush(xhc_in_ctx, XHC_ICTX_BYTES);
    xhc_flush(dctx, xhc_stride());

    if (!xhc_cmd_run(XHC_TRB_TYPE_ADDRESS_DEVICE,
                     (unsigned long long)(unsigned long)xhc_in_ctx,
                     (unsigned)slot, &code, &got_slot))
        return 0;
    if (got_slot != (unsigned)slot) return 0;
    return 1;
}

/** Docstring: Fetch the device descriptor. wValue packs the descriptor type
 * above the index: a device descriptor is type 1, so 0x0100, not zero. */
static int xhc_get_device_desc(int index, unsigned char *buf) {
    unsigned char setup[8];
    xhc_setup_data(setup, 0x80, 0x06, 0x0100, 0, 18);
    return xhc_control(index, setup, buf, 18, 0);
}

/** Docstring: Fetch the configuration descriptor.
 *
 * The first request is for nine bytes, which is the fixed prefix every USB
 * configuration descriptor starts with and the only place wTotalLength lives.
 * Asking for the maximum on the first request instead is the classic mistake:
 * a device with a longer descriptor set answers with wTotalLength bytes, and
 * one with a shorter set answers a short packet, so either way the caller
 * cannot tell how much it got without reading the length back first. The
 * second request asks for that length, capped at XHC_MAX_CONFIG_DESC, and the
 * length reported back is re-read from the device so a truncated copy is
 * never described as complete. */
static int xhc_get_config_desc(int index, unsigned char *buf, unsigned *len) {
    unsigned char setup[8];
    unsigned total;
    unsigned want;
    xhc_setup_data(setup, 0x80, 0x06, 0x0200, 0, 9);
    if (!xhc_control(index, setup, buf, 9, 0)) return 0;
    total = (unsigned)buf[XHC_CFG_TOTAL_LEN_OFF] |
            ((unsigned)buf[XHC_CFG_TOTAL_LEN_OFF + 1u] << 8);
    if (total < 9) return 0;
    if (total <= 9) {
        *len = 9;
        return 1;
    }
    want = total;
    if (want > XHC_MAX_CONFIG_DESC) want = XHC_MAX_CONFIG_DESC;
    xhc_setup_data(setup, 0x80, 0x06, 0x0200, 0, want);
    if (!xhc_control(index, setup, buf, want, 0)) return 0;
    total = (unsigned)buf[XHC_CFG_TOTAL_LEN_OFF] |
            ((unsigned)buf[XHC_CFG_TOTAL_LEN_OFF + 1u] << 8);
    if (total < want) want = total;
    if (want < 9) return 0;
    *len = want;
    return 1;
}

int xhc_enumerate(int port) {
    xhc_port_t ps;
    int index;
    int slot;
    unsigned code = 0;
    unsigned got_slot = 0;
    unsigned char *desc;
    unsigned len = 0;

    if (!xhc_mmio) return -1;
    if (port < 0 || (unsigned)port >= xhc_port_limit) return -1;

    for (index = 0; index < XHC_MAX_DEVICES; index++)
        if (xhc_devs[index].used && xhc_devs[index].port == port) return index;

    if (!xhc_port_state(port, &ps)) return -1;
    if (!ps.connected) return -1;
    /* Reset only a port that is not already usable. A port that reports a
     * connected and enabled device does not need one, and skipping it saves
     * the wait and avoids a needless dis enumeration; a port that does need
     * a reset gets one, and its failure is a hard error rather than an
     * attempt to talk to a device in an unknown state. */
    if (!ps.enabled) {
        if (!xhc_port_reset(port)) {
            xhc_ctr.enum_errors++;
            return -1;
        }
        if (!xhc_port_state(port, &ps)) return -1;
    }

    index = xhc_dev_alloc();
    if (index < 0) {
        xhc_ctr.enum_errors++;
        return -1;
    }
    desc = (unsigned char *)kmalloc(XHC_MAX_CONFIG_DESC);
    if (!desc) {
        xhc_ctr.enum_errors++;
        return -1;
    }
    kmm_make_uncached((unsigned long)desc, XHC_MAX_CONFIG_DESC);
    if (!xhc_cmd_run(XHC_TRB_TYPE_ENABLE_SLOT, 0, 0, &code, &got_slot) ||
        got_slot == 0 || got_slot > xhc_max_slots) {
        xhc_ctr.enum_errors++;
        kfree(desc);
        return -1;
    }
    slot = (int)got_slot;
    if (!xhc_address(index, slot, port, ps.speed)) {
        xhc_ctr.enum_errors++;
        xhc_dev_release(index);
        kfree(desc);
        kprintf("usb dbg: port %d address failed\n", port);
        return -1;
    }
    if (!xhc_get_device_desc(index, desc)) {
        xhc_ctr.enum_errors++;
        xhc_dev_release(index);
        kfree(desc);
        return -1;
    }
    if (desc[XHC_DEV_DESC_TYPE_OFF] != XHC_DT_DEVICE ||
        desc[XHC_DEV_DESC_LEN_OFF] < 18 ||
        desc[XHC_DEV_DESC_NUM_CFG_OFF] == 0) {
        xhc_ctr.enum_errors++;
        xhc_dev_release(index);
        kfree(desc);
        return -1;
    }
    if (!xhc_get_config_desc(index, desc, &len)) {
        xhc_ctr.enum_errors++;
        xhc_dev_release(index);
        kfree(desc);
        return -1;
    }

    xhc_devs[index].used = 1;
    xhc_devs[index].slot = slot;
    xhc_devs[index].port = port;
    xhc_devs[index].speed = ps.speed;
    xhc_devs[index].address = slot;
    xhc_devs[index].config = desc;
    xhc_devs[index].config_len = len;
    return index;
}

int xhc_enumerate_all(void) {
    int found = 0;
    int port;
    for (port = 0; port < xhc_port_count(); port++)
        if (xhc_enumerate(port) >= 0) found++;
    return found;
}

/* ---- Bring-up ---- */

static void xhc_outl(unsigned short port, unsigned val) {
    __asm__ volatile("outl %0, %1" : : "a"(val), "Nd"(port));
}

static unsigned xhc_inl(unsigned short port) {
    unsigned v;
    __asm__ volatile("inl %1, %0" : "=a"(v) : "Nd"(port));
    return v;
}

static void xhc_free_all(void) {
    int i;
    int e;
    if (xhc_cmd) { kfree(xhc_cmd); xhc_cmd = 0; }
    if (xhc_evt) { kfree(xhc_evt); xhc_evt = 0; }
    if (xhc_dbaa) { kfree(xhc_dbaa); xhc_dbaa = 0; }
    if (xhc_ctx) { kfree(xhc_ctx); xhc_ctx = 0; }
    if (xhc_in_ctx) { kfree(xhc_in_ctx); xhc_in_ctx = 0; }
    if (xhc_out_ctx) { kfree(xhc_out_ctx); xhc_out_ctx = 0; }
    if (xhc_erst) { kfree(xhc_erst); xhc_erst = 0; }
    for (i = 0; i < XHC_MAX_DEVICES; i++) {
        for (e = 0; e < XHC_EP_INDEX_LIMIT; e++) {
            if (xhc_rings[i][e].trbs) {
                kfree(xhc_rings[i][e].trbs);
                xhc_rings[i][e].trbs = 0;
                xhc_rings[i][e].configured = 0;
            }
        }
        if (xhc_devs[i].config) {
            kfree(xhc_devs[i].config);
            xhc_devs[i].config = 0;
        }
        xhc_devs[i].used = 0;
    }
}

/** Docstring: Allocate the command ring, the event ring, the ERST, the DCBAA
 * and the context array. Returns 1 on success; on any failure everything
 * allocated so far is released, so a controller that runs out of memory
 * leaves no half-built rings behind. */
static int xhc_alloc_all(unsigned max_slots) {
    unsigned long long ring_bytes;
    unsigned long long dbaa_bytes;
    unsigned long long ctx_bytes;
    unsigned i;

    if (max_slots == 0 || max_slots > XHC_MAX_DEVICES) return 0;
    if (XHC_TRB_RING_TRBS > (0xFFFFFFFFu / sizeof(xhc_trb_t))) return 0;
    ring_bytes = (unsigned long long)XHC_TRB_RING_TRBS * sizeof(xhc_trb_t);
    dbaa_bytes = (unsigned long long)XHC_DCBAA_ENTRIES * 8u;
    if ((unsigned long long)(max_slots + 1u) > (0xFFFFFFFFu / XHC_CTX_SLOT_STRIDE64))
        return 0;
    ctx_bytes = (unsigned long long)(max_slots + 1u) * xhc_stride();

    xhc_cmd = (xhc_trb_t *)kmalloc_aligned((unsigned long)ring_bytes, XHC_DMA_ALIGN);
    if (!xhc_cmd) goto fail;
    xhc_evt = (xhc_trb_t *)kmalloc_aligned((unsigned long)ring_bytes, XHC_DMA_ALIGN);
    if (!xhc_evt) goto fail;
    xhc_erst = (unsigned long long *)kmalloc_aligned(XHC_ERST_BYTES, XHC_DMA_ALIGN);
    if (!xhc_erst) goto fail;
    xhc_dbaa = (unsigned long long *)kmalloc_aligned(
        (unsigned long)dbaa_bytes, XHC_DMA_ALIGN);
    if (!xhc_dbaa) goto fail;
    xhc_ctx = (unsigned char *)kmalloc_aligned((unsigned long)ctx_bytes,
                                            XHC_DMA_ALIGN);
    if (!xhc_ctx) goto fail;
    xhc_in_ctx = (unsigned char *)kmalloc_aligned(XHC_ICTX_BYTES,
                                              XHC_DMA_ALIGN);
    if (!xhc_in_ctx) goto fail;
    xhc_out_ctx = (unsigned char *)kmalloc_aligned(XHC_ICTX_BYTES,
                                               XHC_DMA_ALIGN);
    if (!xhc_out_ctx) goto fail;

    kmemset(xhc_cmd, 0, (unsigned long)ring_bytes);
    kmemset(xhc_evt, 0, (unsigned long)ring_bytes);
    kmemset(xhc_dbaa, 0, (unsigned long)dbaa_bytes);
    kmemset(xhc_ctx, 0, (unsigned long)ctx_bytes);
    kmemset(xhc_in_ctx, 0, XHC_ICTX_BYTES);
    kmemset(xhc_out_ctx, 0, XHC_ICTX_BYTES);

    /* The event ring starts as all zeroes: No-op TRBs with cycle 0. The
     * controller's first event carries cycle 1, so a slot it has not written
     * is distinguishable by the cycle bit alone -- which is what lets the
     * drain stop without a count. Initialising the ring to the *same* cycle
     * the controller will use makes every untouched slot look like a real
     * event and turns the poll into a garbage stream. */
    for (i = 0; i < XHC_TRB_RING_TRBS; i++)
        xhc_puttrb(&xhc_evt[i], 0, 0, 0);
    /* Every structure the controller walks is made uncached before it is
     * used: cache-coherent DMA is not something to assume, and a controller
     * that reads a write-back line sees the zeros the page was zeroed with
     * instead of the descriptor just written. */
    kmm_make_uncached((unsigned long)xhc_cmd, (unsigned long)ring_bytes);
    kmm_make_uncached((unsigned long)xhc_evt, (unsigned long)ring_bytes);
    kmm_make_uncached((unsigned long)xhc_erst, XHC_ERST_BYTES);
    kmm_make_uncached((unsigned long)xhc_dbaa, (unsigned long)dbaa_bytes);
    kmm_make_uncached((unsigned long)xhc_ctx, (unsigned long)ctx_bytes);
    kmm_make_uncached((unsigned long)xhc_in_ctx, XHC_ICTX_BYTES);
    kmm_make_uncached((unsigned long)xhc_out_ctx, XHC_ICTX_BYTES);
    xhc_evt_expect = 1;
    xhc_evt_deq = 0;
    /* The command ring starts at cycle 1 and the CRCR says so: the hardware
     * masks the ring base to 64 bytes and takes the cycle from the RCS bit,
     * so a ring that starts at 0 with an RCS of 0 is fetched as stale. */
    xhc_cmd_enq = 0;
    xhc_cmd_gen = 1;
    xhc_cmd_rearm = 0;
    xhc_arm_link();
    for (i = 0; i < XHC_MAX_DEVICES; i++)
        for (unsigned e = 0; e < XHC_EP_INDEX_LIMIT; e++) {
            xhc_rings[i][e].trbs = 0;
            xhc_rings[i][e].enq = 0;
            xhc_rings[i][e].gen = 0;
            xhc_rings[i][e].configured = 0;
            xhc_rings[i][e].is_out = 0;
            xhc_rings[i][e].dci = 0;
            xhc_rings[i][e].rearm = 0;
        }
    return 1;
fail:
    xhc_free_all();
    return 0;
}

/** Docstring: Program the runtime state and bring the controller to run.
 * Returns 1 when it reports running, 0 on a reset or run timeout. Both waits
 * are bounded: an unbounded spin here is an unusable machine, not a slow one.
 */
/** Docstring: Reset the controller, program its ring state, and bring it to
 * run. Returns 1 when it leaves reset and reports itself un-halted, 0 on a
 * reset or run timeout. Both waits are bounded: an unbounded spin here is an
 * unusable machine, not a slow one.
 *
 * The order is the whole trick, and getting it backwards produces a driver
 * that appears to hang forever: HCRESET clears the command ring pointer, the
 * DCBAA pointer, CONFIG and every interrupter register, so a sequence that
 * programs the rings first and then resets leaves the controller running with
 * nothing programmed and no command ever completing. Reset, then program, then
 * Run. */
static int xhc_start(unsigned contexts) {
    unsigned long end;
    unsigned cmd;

    /* 1. Reset. Nothing below survives it. */
    cmd = xhc_op_read32(XHC_OP_USBCMD) | XHC_CMD_RESET;
    xhc_op_write32(XHC_OP_USBCMD, cmd);
    end = xhc_now_ms() + XHC_RESET_BUDGET_MS;
    while (xhc_op_read32(XHC_OP_USBCMD) & XHC_CMD_RESET) {
        if ((long)(xhc_now_ms() - end) >= 0) return 0;
        xhc_idle(4096);
    }

    /* 2. Host-side ring descriptors. Entry 0 unused; entry N will point at
     * device context N once its slot is enabled. */
    {
        unsigned i;
        for (i = 0; i < XHC_DCBAA_ENTRIES; i++) xhc_dbaa[i] = 0;
    }
    kmemset(xhc_erst, 0, XHC_ERST_BYTES);
    xhc_put64((unsigned char *)xhc_erst, XHC_ERST_RING_LO * 4u,
              (unsigned long long)(unsigned long)xhc_evt);
    xhc_put32((unsigned char *)xhc_erst, XHC_ERST_SIZE * 4u, XHC_TRB_RING_TRBS);
    xhc_put32((unsigned char *)xhc_erst, XHC_ERST_CYCLE * 4u, 0);
    hal_mmio_wmb();
    xhc_flush(xhc_dbaa, (unsigned long)XHC_DCBAA_ENTRIES * 8u);
    xhc_flush(xhc_erst, XHC_ERST_BYTES);

    /* 3. Controller-side ring state. The command ring is programmed through
     * the CRCR pair with RCS set; both are 64-byte aligned by the hardware. */
    xhc_op_write32(XHC_OP_CRCR,
                     ((unsigned)(unsigned long)xhc_cmd & ~0x3Fu) | 1u);
    xhc_op_write32(XHC_OP_CRCR + 4u,
                   (unsigned)((unsigned long)xhc_cmd >> 32));
    xhc_op_write32(XHC_OP_DCBAAP, (unsigned)(unsigned long)xhc_dbaa);
    xhc_op_write32(XHC_OP_DCBAAP + 4u,
                   (unsigned)((unsigned long)xhc_dbaa >> 32));

    /* Interrupter 0: one ERST entry, dequeued at 0, polling so IE stays
     * clear and any pending IP is acknowledged. */
    xhc_run_write32(XHC_RUN_INTR0 + XHC_RUN_ERSTSZ, 1);
    xhc_run_write32(XHC_RUN_INTR0 + XHC_RUN_ERSTBA,
                    (unsigned)(unsigned long)xhc_erst);
    xhc_run_write32(XHC_RUN_INTR0 + XHC_RUN_ERSTBA + 4u,
                    (unsigned)((unsigned long)xhc_erst >> 32));
    xhc_evt_advance();
    xhc_run_write32(XHC_RUN_INTR0 + XHC_RUN_IMAN,
                    xhc_run_read32(XHC_RUN_INTR0 + XHC_RUN_IMAN) |
                    XHC_IMAN_IP);

    /* MaxSlotsEn is the slot count. */
    xhc_op_write32(XHC_OP_CONFIG, contexts);

    /* 4. Run. USBSTS bit 0 is Host Controller Halted: it is set while
     * stopped and cleared once running, so waiting for it to become set
     * waits for the opposite of progress and never returns. */
    xhc_op_write32(XHC_OP_USBCMD, xhc_op_read32(XHC_OP_USBCMD) | XHC_CMD_RUN);
    end = xhc_now_ms() + XHC_RESET_BUDGET_MS;
    while (xhc_op_read32(XHC_OP_USBSTS) & XHC_STS_HALTED) {
        if ((long)(xhc_now_ms() - end) >= 0) return 0;
        xhc_idle(4096);
    }
    return 1;
}

int xhc_init(void) {
    pci_bdf_t bdf;
    unsigned orig_bar;
    unsigned orig_hi;
    unsigned orig_cmd;
    unsigned long long size;
    unsigned long long bar_base;
    unsigned long mapped;
    unsigned hcsparms1;
    unsigned hccparms1;
    unsigned dboff;
    unsigned rtsoff;
    unsigned ports;
    unsigned slots;

    if (!pci_find_class(&bdf, PCI_CLASS_XHCI, PCI_SUBCLASS_XHCI,
                        PCI_PROGIF_XHCI, xhc_outl, xhc_inl)) {
        xhc_note = "no xHCI class match on any bus";
        return 0;
    }

    orig_cmd = pci_cfg_read(bdf.bus, bdf.dev, bdf.func, PCI_REG_COMMAND,
                            xhc_outl, xhc_inl);
    /* Memory decoding off before the BAR is probed: an all-ones probe leaves
     * the device decoding an address the command register does not
     * authorise, and a device that is still decoding sees its own probe. */
    pci_cfg_write(bdf.bus, bdf.dev, bdf.func, PCI_REG_COMMAND,
                  orig_cmd & ~(PCI_COMMAND_MEMORY | PCI_COMMAND_BUS_MASTER),
                  xhc_outl);

    orig_bar = pci_cfg_read(bdf.bus, bdf.dev, bdf.func, PCI_REG_BAR0,
                            xhc_outl, xhc_inl);
    orig_hi = pci_cfg_read(bdf.bus, bdf.dev, bdf.func, PCI_REG_BAR0 + 4u,
                           xhc_outl, xhc_inl);
    if (pci_bar_is_io(bdf.bus, bdf.dev, bdf.func, 0, xhc_outl, xhc_inl)) {
        xhc_note = "BAR0 is an I/O range, not memory";
        pci_cfg_write(bdf.bus, bdf.dev, bdf.func, PCI_REG_COMMAND, orig_cmd,
                      xhc_outl);
        return 0;
    }
    size = pci_bar_size(bdf.bus, bdf.dev, bdf.func, 0, xhc_outl, xhc_inl);
    /* A 32-bit BAR leaves the high half unused, so the base is read from
     * whichever half is not zero. Asking the probe for the length and then
     * taking the address from the register is the pairing that matters: a
     * length assumed from a spec table overruns hardware that disagrees. */
    bar_base = pci_bar_base(bdf.bus, bdf.dev, bdf.func, 0, xhc_outl, xhc_inl);
    if (size == 0 || size > PCI_MMIO_SIZE || bar_base == 0) {
        xhc_note = "BAR0 is not a memory BAR of a usable size";
        pci_bar_restore(bdf.bus, bdf.dev, bdf.func, 0, orig_bar, orig_hi,
                        xhc_outl);
        pci_cfg_write(bdf.bus, bdf.dev, bdf.func, PCI_REG_COMMAND, orig_cmd,
                      xhc_outl);
        return 0;
    }
    pci_cfg_write(bdf.bus, bdf.dev, bdf.func, PCI_REG_COMMAND,
                  orig_cmd | PCI_COMMAND_MEMORY | PCI_COMMAND_BUS_MASTER,
                  xhc_outl);

    /* The BAR keeps the address firmware gave it. Relocating it into the
     * boot identity window does not work: that region above the heap is
     * guest RAM rather than a host-bridge hole, so a BAR pointed there is
     * decoded as RAM and every register reads back as the heap's contents.
     * The kernel maps the BAR's own physical address into a virtual window
     * it owns instead, which also means a controller above 4 GB needs no
     * special case. */
    mapped = kmm_map_device((unsigned long)bar_base, (unsigned long)size);
    if (!mapped) {
        xhc_note = "uncached mapping of the BAR refused";
        pci_bar_restore(bdf.bus, bdf.dev, bdf.func, 0, orig_bar, orig_hi,
                        xhc_outl);
        pci_cfg_write(bdf.bus, bdf.dev, bdf.func, PCI_REG_COMMAND, orig_cmd,
                      xhc_outl);
        return 0;
    }
    xhc_mmio = (volatile unsigned char *)mapped;
    xhc_caplength = xhc_mmio[0];
    /* HCIVERSION is bits 31:16 of the capability dword: major in bits 23:16,
     * minor in bits 31:24. Reading it as a byte pair in the wrong order turns
     * a reported 1.00 into 0.0 and makes a working controller look ancient. */
    xhc_version = (unsigned)(((unsigned)xhc_mmio[2] << 8) |
                             (unsigned)xhc_mmio[3]);
    /* CAPLENGTH is the register-layout authority, so it is the hard gate:
     * below the xHCI 1.0 minimum of 0x10 the offsets used here are unknown
     * and the controller cannot be driven safely.
     *
     * HCIVERSION is deliberately not a hard gate. Silicon reports 1.00 or
     * newer, but a version of 0.0 means "unspecified" rather than broken,
     * and Linux accepts it; refusing it here would make this driver untestable
     * against the common hardware model, which leaves it zero. It is reported
     * by the usb builtin so an unspecified version is visible. */
    if (xhc_caplength < XHC_CAPLENGTH_MIN) {
        xhc_note = "caplength below the xHCI 1.0 minimum";
        xhc_mmio = 0;
        return 0;
    }
    xhc_op = xhc_mmio + xhc_caplength;
    dboff = hal_mmio_read32((volatile unsigned *)
                            (xhc_mmio + XHC_CAP_OFF + XHC_CAP_DBOFF));
    rtsoff = hal_mmio_read32((volatile unsigned *)
                             (xhc_mmio + XHC_CAP_OFF + XHC_CAP_RTSOFF));
    xhc_db = xhc_mmio + (dboff & ~0x3u);
    xhc_run = xhc_mmio + (rtsoff & ~0x1Fu);


    hcsparms1 = hal_mmio_read32((volatile unsigned *)
                                (xhc_mmio + XHC_CAP_OFF + XHC_CAP_HCSP1));
    hccparms1 = hal_mmio_read32((volatile unsigned *)
                                (xhc_mmio + XHC_CAP_OFF + XHC_CAP_HCCP1));
    xhc_csz = (hccparms1 & XHC_HCC_CSZ) != 0;
    slots = hcsparms1 & 0xFFu;
    ports = (hcsparms1 >> 24) & 0xFFu;
    if (ports > XHC_MAX_PORTS) ports = XHC_MAX_PORTS;
    if (slots > XHC_MAX_DEVICES) slots = XHC_MAX_DEVICES;
    if (slots == 0) slots = 1u;
    if (ports == 0) ports = 1u;
    xhc_max_slots = slots;
    xhc_port_limit = ports;

    if (!xhc_alloc_all(slots)) {
        xhc_note = "no memory for the rings and contexts";
        xhc_mmio = 0;
        return 0;
    }
    if (!xhc_start(slots)) {
        xhc_note = "controller did not reach run";
        xhc_free_all();
        xhc_mmio = 0;
        return 0;
    }
    return 1;
}

void xhc_counters(xhc_counters_t *out) {
    if (out) *out = xhc_ctr;
}

const char *xhc_probe_note(void) {
    return xhc_note;
}

int xhc_info(unsigned *version, unsigned *slots, unsigned *ports,
             unsigned *caplength) {
    if (!xhc_mmio) return 0;
    if (version) *version = xhc_version & 0xFFFFu;
    if (slots) *slots = xhc_max_slots;
    if (ports) *ports = xhc_port_limit;
    if (caplength) *caplength = xhc_caplength;
    return 1;
}