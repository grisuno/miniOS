# USB: xHCI host controller, HID boot input, mass storage

## Why this file exists

MiniOS was PS/2 and UART only. On QEMU that is enough, because the firmware
emulates an 8042; on real hardware it is not: a 2012-or-later machine has no
PS/2 controller at all, and its keyboard and mouse hang off an xHCI host
controller (USB 3.x) whose only legacy compatibility layer is a
software-emulated 8042 shim. The same is true of a USB stick, which is how
most people will want to carry `os.img` in. This file is the contract for the
xHCI path.

The slice covered here is deliberately narrow and complete: enumerate the
controller, enumerate the ports, address devices, run control transfers, read
interrupt endpoints, and drive exactly two device classes end to end --
HID (boot-protocol keyboard and mouse) and mass storage (USB Mass Storage
Class, Bulk-Only Transport). It does not implement isochronous audio, USB
2.0 high-speed bandwidth negotiation, hubs, Type-C, or function-level
drivers beyond those two.

## Design decisions, and why

**The event ring is polled, not interrupt-driven.** This is a decision, not a
shortcut. The tree has no MSI, no MSI-X, no I/O-APIC, no ACPI/MADT and no
per-vector handler registration; the only existing dispatch is a flat `if`
chain in `isr_dispatch` and the only 8259 masks are literals in `pic_init`.
Building MSI-X properly means a capability walk, MSI-X table entry
programming, a new IDT vector, a new `isr_dispatch` arm and either a PIC
unmask or a full I/O-APIC redirection table -- roughly as much new code again
as the driver itself, and none of it testable without real hardware. The xHCI
spec does not require interrupts: the event ring is ordinary memory and
`RTDEVP` may be polled at any time. So this slice polls, exactly as
`net/rtl8139.c` and both virtio drivers already do (they document "no MSI-X,
completion by polling"). Input latency is bounded by the poll period; the poll
runs both on the 100 Hz tick bus *and* inside the shell's existing
`console_getc` spin, so a keystroke lands on the next spin, not on the next
tick. Porting to MSI-X later is additive: it replaces the poll trigger and
touches nothing in the ring code.

**The BAR is relocated into a reserved window, and mapped uncached.** The only
virtual window MiniOS has is stage 2's 1 GB identity map, and firmware puts
PCI MMIO wherever it likes -- commonly `0xE0000000`, outside it. Rather than
grow `PT_FILL_*`, `KASLR_IMAGE_SPAN` and the stage1/stage2 table scheme
together (the low-4MB hazard forbids moving them piecemeal), the driver
size-probes BAR0, relocates it into `[MINIOS_PCI_MMIO_BASE,
MINIOS_PCI_MMIO_BASE + MINIOS_PCI_MMIO_SIZE)` -- identity-mapped, unclaimed
physical RAM immediately above the heap -- and then converts just those pages
from the boot write-back 2 MB leaf into a 4 KB page table with `PCD|PWT` set.
The result is what Linux's `ioremap` produces, and it is required rather than
tidy: a write-back *register* read can be served from cache, and a stale
event-ring status register means a keyboard that never types. The mapping is
`kmm_map_uncached()` in `kernel/mm/paging.c`; it fails closed above
`KMM_MAX_IDENTITY` instead of guessing.

**Everything the controller touches lives on the heap.** The whole kernel
assumes `VA == PA` for DMA because KASLR slides the image, so a device
descriptor or TRB in `.bss` or on a stack is unreachable by the controller.
Every ring, context, buffer and CBW/CSW is `kmalloc_aligned` or `kmalloc`,
never a static. This is the same rule `drivers/virtio_blk.c` states for the
vring pages and the same one `drivers/sb16.c` works around with its fixed
`SB16_DMA_BUF0` window.

**Input reuses the PS/2 decode path rather than forking it.** USB HID boot
keyboards report *state*, not events, and they report it in HID usage codes.
MiniOS's keyboard driver, the window manager's combos, `wm_raw_swallow_tab_break`
and the Spanish/English layout tables all live behind one function that
consumes a PS/2 set-1 *scancode*. Rather than a second keyboard path, HID
state is differenced against the previous report into set-1 make/break pairs
and pushed through that same function. Two consequences worth stating: HID
usage codes are **not** scancodes above `0x27` (usage `0x28` is Return while
set-1 Return is `0x1C`), so a real usage-to-set-1 table is required and
tested; and HID reports the navigation cluster and the right-hand modifiers
*without* the `0xE0` prefix that set 1 uses to disambiguate them, so the table
also decides when to synthesize `0xE0`. This is the only way Alt+Tab keeps
working on a USB keyboard.

## Layers

| File | Contract |
|------|----------|
| `headers/arch/x86/hal_io.h` | `hal_mmio_read32/write32`, `hal_mmio_read64/write64`, `hal_mmio_wmb/rmb/mb` |
| `headers/drivers/pci.h` | `pci_bdf_t`, class-code match, full bus walk, `pci_bar_size`, `pci_bar_relocate` |
| `kernel/mm/paging.c` | `kmm_map_uncached(phys, len)` -- 2 MB leaf to 4 KB PT split, identity, `PCD|PWT` |
| `headers/drivers/xhci.h` | controller boundary: `xhc_init`, `xhc_poll`, `xhc_report`, transfer API |
| `drivers/xhci.c` | caps, reset, command ring, event ring, slots, contexts, endpoints, TRBs |
| `headers/drivers/usbhid.h` | `usbhid_init`, `usbhid_poll_keyboard`, `usbhid_poll_mouse`, usage tables |
| `drivers/usbhid.c` | HID boot reports, `SET_PROTOCOL`, report differencing, injection |
| `headers/drivers/usbblk.h` | `ubk_init`, `ubk_present`, `ubk_sectors`, `ubk_read/write_sectors` |
| `drivers/usbblk.c` | BOT CBW/CSW, SCSI `READ(10)`/`WRITE(10)`, block device registration |

`xhc.h` is the only thing `usbhid.c` and `usbblk.c` know: they never touch a
register or a TRB. `xhc.c` knows nothing about HID or SCSI. That split is the
whole point of the boundary -- the mass-storage slice landed after the HID one
without editing the controller.

## Controller bring-up

Probe is by **class code**, not vendor/device: class `0x0C`, subclass `0x03`,
programming interface `0x30` is xHCI, and that is true of every Intel PCH,
AMD chipset and ASMedia bridge in the field, so no vendor table is needed.
The walk visits bus 0 and then follows each bridge's secondary bus number, and
honours the multifunction bit in header type 0x0E -- the old
`pci_find()` looked at bus 0, function 0 only and was fine for QEMU's two
single-function emulated NICs, not for a real chipset.

Bring-up order, and the reason for each step:

1. Save BAR0's original value so a probe that bails can put it back.
2. `PCI_COMMAND`: clear `MEMORY_SPACE_ENABLE` before touching the BAR.
3. Size BAR0: write all ones, read the mask back, restore. A zero mask means
   the device is absent or BAR0 is an I/O BAR; xHCI is memory-only, so that
   is a hard fail. The mask is what proves the window is big enough --
   relocation is refused when the probed size exceeds `MINIOS_PCI_MMIO_SIZE`,
   and it is never assumed.
4. Write the window base into BAR0 and, for a 64-bit BAR, zero the high half.
5. Re-enable `MEMORY_SPACE_ENABLE` and `BUS_MASTER_ENABLE`; without bus master
   the controller cannot DMA at all and the failure looks like a hang.
6. `kmm_map_uncached()` the window, then read back `CAPLENGTH` and
   `HCIVERSION`. A CAPLENGTH below the documented minimum of 0x10, or a
   controller version below 1.0, is a fail-closed bail, not a guess.
7. `USBCMD` reset (A64, HCRESET), then `USBCMD` `RUN`. A controller that does
   reach `RUN` within `XHC_RESET_BUDGET_MS` with `USBCMD` bit 0 clear is
   healthy; the budget is enforced and a timeout is reported, never ignored.
8. Parse `HCSPARAMS1` for the device slot count and `PORTSC` for the port
   count. Both are bounded by `XHC_MAX_DEVICES` and `XHC_MAX_PORTS`, and a
   controller that reports more is truncated and reported, never trusted.

Ring allocation, all `kmalloc_aligned` to 16 bytes (TRB alignment) with sizes
derived from the caps fields and every `size * count` overflow-checked before
the call: the command ring segment (link TRB closing the cycle), the primary
event ring segment table, the event ring segment, and the device context
array sized `max_slot` 1 KB contexts. The event ring segment table holds one
entry pointing at the event ring, with the cycle bit clear.

## Command and event rings

A command is a TRB in the command ring plus a doorbell; the completion arrives
on the event ring. Because there are no interrupts, every wait is a bounded
spin over `xhc_poll()` with a `XHC_CMD_BUDGET_MS` deadline:

- `xhc_cmd_enable_slot()` -> `ENABLE_SLOT`, remembers the returned slot id.
- `xhc_addr_device()` -> `ADDRESS_DEVICE` with an input context: a contiguous
  `INPUT_CONTEXT` whose drop flag is set, holding an `OUTPUT_CONTEXT` and a
  `DEVICE_CONTEXT`. The drop flag is what makes the controller *add* context
  entries instead of replacing the table, which is the only legal way to
  build it incrementally.
- `xhc_config_endpoint()` -> `CONFIGURE_ENDPOINT` with an input context
  carrying the control endpoint first (it must be EP0) and then the target.

`xhc_poll()` drains the event ring, copying each TRB out under a read fence
before the cycle is cleared, and matches completions to waiters by TRB
pointer. Every command reports its own completion code; a non-success code is
propagated to the caller and also counted. Unknown and non-transfer event
TRB types (including vendor and host-controller events) are counted and
skipped rather than misparsed, and the ring is resynchronised on the cycle
bit.

Ordering is the other half of correctness. TRB writes are fenced before the
doorbell MMIO store (`hal_mmio_wmb`), and event TRB reads are fenced before
the cycle bit is released (`hal_mmio_rmb`). Without both, a doorbell can
reach the controller ahead of the descriptor it points at.

## Endpoint context and transfer rings

One transfer ring per endpoint, allocated from the heap at
`XHC_TRB_RING_TRBS` (1024) TRBs, 16-byte aligned, with a normal and a link
TRB so the ring can stay a power-of-two cycle mask. The endpoint context's
address is 0 for EP0 and the ring's physical address for every other endpoint,
which is what makes the `dequeue`/`enqueue` pointers in the context the ring
cycle and not a byte offset.

Bulk and interrupt endpoints differ in exactly two fields (`MAX_PACKET` and
the `CM`/`MAX_BURST` and `INTERVAL` values), and both are written from the
endpoint descriptor's own `wMaxPacketSize` rather than a constant.

## HID boot protocol

`usbhid_init()` runs once per controller and then scans the ports. For each
port with a connected device it reads the configuration descriptor, finds
interface 0 and its IN endpoint, and checks the interface class (3 = HID) and
subclass (1 = boot) before touching anything -- a non-HID device on the same
hub is skipped, not misparsed. A boot-protocol device is then switched with a
class request `SET_PROTOCOL(0)` over EP0, and the endpoint is armed with a
one-TRB-per-report interrupt ring.

The keyboard report is 8 bytes: a modifier bitfield, a reserved byte and six
set-1 keycode slots. Each poll differences it against the previous report and
emits, for every key whose presence changed, a set-1 make (usage) or break
(usage | `0x80`) through `kbd_feed_scancode()`. Release-before-press ordering
is not required by the keyboard, but the differ is written to emit breaks
first so a burst never looks like a held-key repeat. The modifier bitfield
maps to the same E0-disambiguated set-1 codes as a PS/2 keyboard, so
`kbd_mods` stays the single source of truth for the window manager.

The mouse report is 4 bytes (boot protocol, the report descriptor's byte 3
byte if present is read and discarded, never assumed) and differs in the same
way: `dx`/`dy` accumulate into `mouse_state.x`/`y` with the same
`HAL_MOUSE_SCALE` the PS/2 path uses, the button bitmask is copied, and the
signed 4-bit wheel nibble is added to the `mouse_state.wheel` accumulator.
Writes go under `spin_save_irq()` because the desktop tick drains that
accumulator concurrently.

`usbhid` never invents a device it did not see: every counter it exposes
(`usbhid` builtin line) is incremented by the code path that did the work, so
a zero means the device is absent, not that the driver is broken.

## Mass storage (Bulk-Only Transport)

`ubk_init()` scans the same ports for interface class 8 (mass storage),
subclass 6 (SCSI transparent command set), protocol 80 (Bulk-Only
Transport). One such device is taken as the system disk candidate and
registered with `device_register()` through the existing `block_ops_t`, so
VFS, `pcache` and the `ls`/`cat` paths work on a USB stick with no change and
no new syscall. Preference order in `drivers/block.c` becomes
virtio-blk, then USB, then IDE; a device that fails `READ CAPACITY` is not
registered and never becomes the backend.

A transfer is: build a CBW (31 bytes, magic `0x43425355`), post the data-out
stage, post the status-in stage, wait for the CSW (13 bytes, magic
`0x53425355`), then check the CSW status and the CBW residue. Every stage is
checked: a short data phase, a bad magic or a non-zero status is an error, and
an error never leaves a partial buffer described as good data. Commands are
SCSI `TEST UNIT READY`, `INQUIRY`, `READ CAPACITY(10)`, `READ(10)` and
`WRITE(10)`; a disk larger than 2 TiB (the `READ(10)` ceiling) is reported as
unsupported rather than silently truncated, because a wrong sector count is
data corruption.

Buffers are heap, page-cache pages handed down by the block layer, never
statics, and the CBW/CSW are heap objects for the KASLR reason above.

## Observability

The `usb` shell builtin prints the controller (caps-derived slot and port
counts, the run state), each port with its address and speed, each attached
device with class/subclass/protocol and its slot, and the counters: command
completions by code, event TRBs seen, unknown event TRBs, HID keyboard and
mouse reports, and mass-storage read/write blocks. A machine with no xHCI
prints `usb: none` and boots exactly as before -- the driver is a probe that
finds nothing, not an assertion that hardware must exist.

## Testing

- **Host tests** (`make test-xhci`, `make test-usbhid`, `make test-usbblk`,
  `make test-pci`): the PCI bus walk against a fake config space, the BAR
  size probe and relocation refusal, TRB encode/decode round-trips, ring
  cycle and link handling, the usage-to-set-1 table (every usage, including
  the `0xE0` decisions), the HID report differ, and the CBW/CSW builder. These
  are the parts where a bug is silent on QEMU but fatal on silicon.
- **BDD** (`tools/test_bdd.sh`): a scenario boots with
  `-device nec-usb-xhci -usb -device usb-kbd -device usb-mouse -device
  usb-storage` and asserts the `usb` report shows the controller running, the
  keyboard and mouse addressed with boot protocol, the disk registered with a
  non-zero sector count, and that a read of LBA 0 through the block layer
  returns the same bytes a direct read returns. The no-USB path is asserted
  too, so the driver cannot start *requiring* a controller.
- **Mutation**: every target file is in `SOURCES` and carries at least one
  anchor-checked mutant -- cycle-bit handling, doorbell ordering, TRB cycle
  field, the usage table, the differ, the CSW status check, the residue check.

## Hard rules and hazards

- **MMIO is uncached.** `kmm_map_uncached()` or nothing; a cached register
  read is a silently dead driver.
- **BAR relocation is probed, never assumed.** A size mask of zero, or a mask
  larger than the window, is a hard fail. The original BAR value is restored
  on any bail.
- **Bus master enable is mandatory** before any ring is touched.
- **Device memory is heap only.** `.bss` and stack addresses are not reachable
  by the controller under KASLR.
- **`size * count` is overflow-checked** before every ring or table
  allocation.
- **Every wait is bounded.** Reset, command completion and transfer
  completion all have named budgets and report a timeout instead of spinning
  forever; the poll runs on the tick bus where a hang is a hung kernel.
- **Polled, by decision.** No vector is claimed, no IDT arm is added, no PIC
  mask changes. A second input source must not make interrupts a prerequisite
  for typing.
- **Descriptor bounds are validated** before use: every configuration
  descriptor walk checks `bLength`, `bDescriptorType` and the remaining
  length, and every endpoint index is checked against the context array.
- **HID injection goes through `kbd_feed_scancode()`**, never straight into
  `kbd_q_push()`: pushing cooked bytes would silently disable every window
  manager combo on USB keyboards.
- **`MINIOS_PCI_MMIO_BASE` and `MINIOS_PCI_MMIO_SIZE` live in
  `progs/minios_abi.h`** and nowhere else, above the heap and below the 1 GB
  identity limit, so `python3 tools/check_abi_numbers.py` keeps them honest.
