# Build, run and hypervisors

How the image is produced, how it is booted, and what the reference
platform is. The source contract for the sibling checkouts is in
`docs/spec/source.md`; the boot path, disk layout and memory map are in
`docs/spec/boot-memory.md`; the USB stack is in `docs/spec/usb.md`.

### Make targets (host)

`make` builds `os.img`; the table below is the full host target list.
`CLAUDE.md` keeps the engineering contract, `docs/spec/testing.md` keeps
the validation gate.

| Target | Purpose |
|--------|---------|
| `all` (default) | build `os.img` |
| `sources` | clone the missing toolchain repositories from GitHub |
| `sources-update` | pull the latest commit of each one |
| `sources-status` | show the revision each checkout is on |
| `toolchain` | build `minigcc`, `ld` and `cvm2` from those sources |
| `selfhost` | compile minigcc with minigcc, link with `ld`, verify the bootstrap fixed point (`g3.s == g4.s`) |
| `run` | boot the image in QEMU with a display (TCG by default) |
| `run-kvm` | boot it with KVM acceleration (faster CPU, slower IDE I/O) |
| `run-headless` | boot it headless on the serial console (no GUI window, SB16 audio kept) |
| `serial` | boot it headless on the serial console |
| `debug` | boot it with the QEMU monitor on stdio (`-monitor stdio -no-reboot`) |
| `gdb` | boot it paused under the gdb stub (`-s -S`, port 1234) |
| `test` | behavioural suite (`tools/test_bdd.sh`) |
| `run-iso` | boot the partitioned image (`os.usb.img`) in QEMU over IDE |
| `run-usb` | boot the partitioned image in QEMU over USB-HDD emulation |
| `run-usb-fake` | IDE system disk + FAT32 test pendrive on xHCI (see below) |
| `run-usb-host BUS=2 ADDR=5` | physical pendrive via QEMU USB passthrough (`lsusb` for the numbers) |
| `run-usb-boot` | boot `os.usb.img` as the system disk over xHCI, no IDE |
| `pendrive.img` | build the 64 MB FAT32 test pendrive (HELLO.TXT + README.TXT) |
| `usb-list` | list candidate target devices for USB writing |
| `usb USB=/dev/sdX` | write the bootable image to a USB pendrive (DD mode) |
| `vdi` | convert the image to `os.vdi` for VirtualBox (hard disk) |
| `vb` | boot the same image in VirtualBox (`VB_TYPE=headless` for a headless start) |
| `os.iso` | the raw disk image renamed for distribution (not ISO9660) |
| `uefi` | build `uefi.img` (FAT image carrying `BOOTX64.EFI` and `kernel.bin`) |
| `minifs.bin` | rebuild the MiniFS image (includes the TopoGPT3 weights and vocab) |
| `minifs-mkfs` / `minifs-dump` / `minifs-fsck` | create / dump / check the MiniFS image (`tools/mkfs.minifs.py`, `tools/minifs_dump.py`, `tools/minifs_fsck.py`) |
| `test-tls` | host TLS suite: crypto vectors + full handshakes |
| `test-vma` | host VMA suite: red-black tree invariants, pool exhaustion, full drain |
| `test-sync` | host sync suite: wait queues, mutex/sem/cond/rwlock over the real `kernel/sync.c` |
| `test-fat` | host FAT32 suite: BPB units, multi-cluster reads, fail-closed edges over a synthetic image |
| `test-tick` | host tick suite: listener order, separation, gating, bounds over the real `kernel/tick.c` |
| `test-hal` | host HAL suite: port/device constants and stub routing for `headers/arch/x86/hal_io.h` |
| `test-wm` | host WM suite: geometry, events, window model, render plan, tiling and focus over the header-only `wm_*.h` contracts |
| `test-host` | every fast host suite at once |
| `progs/bin/topogpt3.elf` | build the TopoGPT3 C inference engine |
| `progs/bin/nuklear.elf` | build the Nuklear node editor |
| `progs/bin/quake2generic.elf` | build the Quake 2 engine |
| `progs/bin/doomgeneric.elf` | build the DOOM engine |
| `pokemon-fetch` / `pokemon-clean` | fetch the gb-recompiled tool / remove `progs/pokemon/build/` |
| `lint` | cppcheck, `-Wextra` (ring-3), clang-tidy, `bash -n`, abi-numbers, fork-stubs, sanitize, addons, anchors |
| `clean` | remove every build product (snapshots `saves/` into `saves-backup/` first) |

The QEMU launch flags of the `os.img` targets (`run`, `run-kvm`,
`run-headless`, `serial`, `debug`, `gdb`) share the drive, the memory and
the NIC: `-drive file=os.img,format=raw,if=ide`, `-m 1G` and
`-nic user,model=rtl8139 -smp 2`. `run`, `run-kvm` and `run-headless` add
the SB16 audio device (`-device sb16,iobase=0x220,irq=5,dma=1`); `run`
also keeps the GUI window, `run-headless` replaces it with
`-display none -serial stdio` (the audio backend stays, so tone and sbtone
are still audible), `debug` uses `-monitor stdio -no-reboot` and `gdb`
uses `-s -S` to boot paused under the stub. `QEMU_ACCEL` is empty by
default, so `make run` runs TCG; `make run-kvm` passes `-accel kvm` instead
(`QEMU_ACCEL=-accel kvm` cannot be set on the command line: the space
splits the value). The USB targets attach their own drives (see
`docs/spec/usb.md`).

### Choosing KVM vs TCG

The default `make run` uses **no acceleration (TCG)**. Use `make run-kvm` for
KVM. There is a real trade-off, and it is deliberately left to the user:

| Workload | TCG (`make run`) | KVM (`make run-kvm`) |
|----------|------------------|----------------------|
| CPU-bound (ring-3 GUI: `piano --bench`) | ~20 fps | ~60 fps |
| IDE disk I/O (loading DOOM's WAD) | seconds | ~30 s |

KVM makes pure CPU-bound work much faster, but every IDE PIO port access
becomes a VM-exit, so disk-heavy loads are slower than under TCG, which
handles port I/O inline. The IDE driver was optimized to reduce those exits
(`docs/spec/performance.md`), which took DOOM's load from ~5 minutes to
~30 s under KVM, but the remaining data-transfer reads are inherent to PIO.

The image is attached as an IDE disk. The boot path uses INT 13h extended
(LBA) reads, which floppy emulation does not provide.

### USB sticks, `os.iso` and VirtualBox

`os.usb.img` is `os.img` plus a one-partition MBR table (the partition
starts at LBA 2048; the stage 1 code ends before the partition area, so
nothing executable is overwritten, and the loader reads raw LBAs and
ignores the table, so booting is unchanged); `os.iso` is that same raw disk
image renamed for distribution. It is not an ISO9660 filesystem and carries no
El Torito CD boot record and no UEFI loader, so it must always be written
in DD mode (`make usb USB=/dev/sdX`, Rufus in DD mode, Balena Etcher) and
never as an ISO-mode CD. For the same reason VirtualBox must attach the
image as a hard disk (`make vdi`, then attach `os.vdi` on IDE/SATA), never
as an optical drive: a virtual CD device expects ISO9660 and will not boot.
`make usb` refuses the disk holding the running root filesystem and any
target smaller than the image, and asks for `YES` before writing.

### Reading a USB pendrive (xHCI)

The kernel drives USB 3 controllers (`drivers/xhci.c`, polled event
ring, no interrupts), HID boot keyboards and mice
(`drivers/usbhid.c`, typed through the same set-1 path as PS/2 so
window-manager combos keep working) and USB sticks over Bulk-Only
Transport (`drivers/usbblk.c`, registered as the `usb` block device).
`usb` prints the controller, the devices, the HID state and the disk
with its counters. Three ways to attach a stick:

```bash
make run-usb-fake    # 1. fake: 64 MB FAT32 pendrive.img on xHCI (rootless)
make run-usb-host BUS=2 ADDR=5   # 2. physical stick via passthrough (lsusb)
make run-usb-boot    # 3. boot os.usb.img itself from USB, no IDE
```

Form 3 hangs the system disk on the xHCI controller, and QEMU's SeaBIOS
does not boot from xHCI, so under QEMU that form never reaches the kernel:
it targets real hardware and VirtualBox (USB-HDD boot). `make run-usb`
is the QEMU-reachable USB boot form (UHCI emulation).

Inside MiniOS a data stick reads through the `hd0` disk device:

```
usb                 # disk present sectors=131072
fat ls hd0 /        # HELLO.TXT, README.TXT
fat cat hd0 HELLO.TXT
```

A present USB disk becomes the block backend (virtio, then USB, then
IDE). With a FAT data stick attached the backend is the stick, so the
MiniFS that lives on the IDE image is shadowed while the stick is
attached: read the stick with `fat`, not MiniFS. Booting from the
stick itself (`make run-usb-boot`, `make usb`) keeps MiniFS on USB
with no shadow.

### Other hypervisors and real hardware

QEMU is the reference platform, and every scenario in `test_bdd.sh` runs on
it. Work is starting to boot the same image on other hypervisors as a
stepping stone to real hardware, with no changes to the guest image: the
file under test is always the stock `os.usb.img`.

| Platform | How | Status |
|----------|-----|--------|
| VirtualBox | `make vdi`, attach `os.vdi` as IDE/SATA hard disk (or `make vb`, which builds the VDI and boots it) | boots (optical attach does not, see above; networking is unavailable, see below) |
| VMware | `qemu-img convert -O vmdk os.usb.img os.vmdk`, attach as IDE hard disk | to be tested |
| GNOME Boxes / virt-manager | attach `os.usb.img` directly as an existing IDE disk image | to be tested |
| Real hardware (USB) | `make usb USB=/dev/sdX`, Legacy/CSM boot, Secure Boot off, USB-HDD first | to be tested |

VirtualBox 7 dropped the rtl8139 NIC type, so the guest NIC is the default
NAT device, `net/rtl8139.c` reports the NIC absent (fail closed) and
networking is unavailable under VirtualBox. Everything else (console,
MiniFS, audio, graphics) is unchanged.

Results from each platform will be recorded here as they land: what
booted, what failed, and which driver gap it maps to.

### Known constraints off QEMU

- Boot is legacy MBR only (INT 13h LBA). Neither `os.img` nor `os.usb.img`
  carries a UEFI loader, and there is no El Torito support, so UEFI-only
  firmware without a CSM module cannot boot the image. The CSM-less path is
  a different image: `make uefi` builds `uefi.img` (a FAT image carrying
  `BOOTX64.EFI` from `boot/uefi_stub.c` plus `kernel.bin`), which reaches
  the kernel shell under OVMF (`docs/spec/boot-memory.md`).
- Disk drivers are IDE PIO (`drivers/ide.c`), virtio-blk and USB mass
  storage over xHCI (`drivers/usbblk.c`). A machine or VM exposing the
  disk exclusively through AHCI/SATA or NVMe will boot stage 1 and stage
  2 (BIOS reads) but the kernel will not find its MiniFS partition: the
  block-layer preference stays virtio > USB > IDE and the NVMe driver is
  probe plus read-only queues, not a backend yet. Keep an IDE/compatibility
  mode available where possible.
- The NIC backends are rtl8139 (the QEMU user-networking default) and a
  polled legacy virtio-net (`drivers/virtio_net.c`), which `net/net.c`
  prefers when present (`net: backend=virtio`). Other hypervisors need
  their rtl8139 (or equivalent emulated) device, or the network stays
  down while everything else works.
- Audio is the PC speaker plus Sound Blaster 16; input is PS/2
  keyboard and mouse plus USB HID keyboard and mouse through the xHCI
  driver (`drivers/xhci.c`, `drivers/usbhid.c`, polled, no interrupts).
  On machines without PS/2 ports the USB keyboard is the console
  keyboard: type at the prompt and it answers.
- Video needs VESA BIOS Extensions (true color preferred at each
  resolution, 8-bit palette as the fallback, VGA Mode 13h when VBE is
  absent). Headless BMC/KVM consoles without VBE will get the serial
  console only.
