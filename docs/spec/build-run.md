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
| `update [repo...]` | bring the newest sources: every checkout, or only the named ones (`make update freedom`) |
| `update-status` | show the revision each checkout is on, no network access |
| `update-list` | list the managed checkouts, their mode and their path |
| `update-rollback` | restore the revisions the last update replaced |
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

### SATA (AHCI) backend

`drivers/ahci.c` is the disk driver of UEFI-era PCs, whose firmware rarely
offers the IDE compatibility mode `drivers/ide.c` needs.

- Found by PCI class 01:06:01 through `pci_find_class` (never a vendor
  table); registers are ABAR (BAR5), mapped through `kmm_map_device`.
- Firmware ownership is released with the BIOS/OS handoff when CAP2.BOH
  is set; GHC.AE is set and GHC.IE cleared (polled, no vector, no IDT
  entry, no PIC mask, the same doctrine as xHCI).
- The first implemented port with an established link (SSTS.DET=3,
  IPM=1) and an ATA signature (0x00000101) is claimed. A device with no
  phy communication gets one COMRESET; staggered spin-up is honoured;
  ATAPI and port multipliers are skipped.
- IDENTIFY DEVICE must report 48-bit LBA and 512-byte logical sectors
  (4Kn drives are refused, the block layer addresses 512-byte LBAs).
- I/O is READ/WRITE DMA EXT on command slot 0, `AHCI_MAX_SECTORS` (64 KB)
  per command through one heap staging buffer; every write is followed
  by FLUSH CACHE EXT because a real disk acknowledges into volatile cache.
  Heap addresses are bus addresses (identity map); an address above 4 GB
  on an HBA without CAP.S64A is refused, never truncated.
- Every wait is bounded by a named `AHCI_TMO_*` budget on `ktime_ms`
  (TSC, so it advances with interrupts masked). A task-file error, TFES
  or a timeout fails the request closed.
- Selection: AHCI becomes the backend when neither virtio nor USB won and
  either no legacy IDE disk answered or the IDE disk has the same sector
  count (the same drive seen through a compatibility window).
- Shell probe: `ahci` prints port/PI/VS/capacity, checks the LBA 0 boot
  signature and the LBA 2048 MiniFS superblock, and rewrites LBA 2048
  with its own bytes to prove the write + flush path.
- Known limit: with several ATA disks the first linked port wins; the
  boot disk is not yet identified by content.

BDD: `MATCH=ahci` boots the stock image on `-machine q35,smm=off` (disk on
the ICH9 HBA at 00:1f.2, no IDE ports, an xHCI alongside so the HBA is the
second device window) and proves the probe plus a MiniFS write that
survives a reboot. `smm=off` is a TCG artifact: SeaBIOS serves INT 13h
from its own AHCI driver through an SMI call32 trampoline that TCG
emulates too slowly for stage 2 to finish; KVM and real firmware are not
affected. Mutants: `ahci-*` (class, signature, FIS count, write opcode,
IDENTIFY capacity word, backend preference, single device window).

Two defects this slice found on the way, both of which made real
hardware invisible:

- `pci_is_multifunction` tested bit 7 of the 0x0C dword (cache line
  size) instead of bit 7 of the header-type byte at 0x0E, so functions
  1..7 of every chipset device were never walked: the PCH SATA HBA at
  00:1f.2 and the PCIe root ports at 00:1c.x did not exist. Bridges are
  now also followed on any function, not just function 0. Pinned by
  `make test-pci` (Intel PCH fixture) and the `pci-multifunc-wrong-byte`
  / `pci-bridge-func0-only` mutants.
- `kmm_map_device` owned a single 2 MB window and refused a second
  mapping, so on a machine with xHCI plus a disk controller the second
  driver failed closed. It now hands out one window per call (512 per
  device PDPT slot, never reused). Pinned by `ahci-kmm-single-window`.

### Road to real hardware

Status of each gap between QEMU and a physical PC, in the order they
block a boot. A slice lands with its spec here, a BDD proof under QEMU
and mutants, before the next one starts.

| # | Gap | Why it blocks | Plan | Status |
|---|-----|---------------|------|--------|
| 1 | PCI multifunction walk | SATA, root ports and everything behind them invisible | header-type byte, bridges on any function | landed |
| 2 | One MMIO window | second controller refused | per-call 2 MB windows | landed |
| 3 | SATA disk | no IDE mode on UEFI-era firmware | `drivers/ahci.c` backend | landed |
| 4 | One image, both firmwares | `uefi.img` and `os.img` are separate, so a stick boots only one way | GPT/MBR hybrid `os.img`: stage1 in the MBR boot code, an ESP partition carrying `BOOTX64.EFI` + `kernel.bin`, MiniFS located by the existing superblock probe | open |
| 5 | GOP framebuffer | UEFI has no VBE; the desktop needs a linear framebuffer | handoff block carries GOP base/pitch/geometry, `vga_fb` accepts it (ABI bump), VGA text stays the fallback | written, unproven (OVMF here reports no GOP) |
| 6 | ACPI | CPU count, IOAPIC, HPET and PM timer live in MADT/HPET/FADT; poweroff and reboot need FADT/`_S5` | RSDP from the EFI config table or the BIOS EBDA scan, validated (checksums, lengths) before use | open |
| 7 | Timers | the 8254 PIT is clock-gated on recent Intel PCHs, which breaks TSC calibration and the 100 Hz tick | calibrate against HPET or the ACPI PM timer, tick from the LAPIC timer | open |
| 8 | NVMe as a backend | many laptops have NVMe only | write path, multi-PRP transfers, registry entry, preference after AHCI | open |
| 9 | Console without COM1 | most laptops have no serial port | framebuffer console is the primary console; serial stays optional | open |
| 10 | NIC | rtl8139/virtio do not exist on hardware | e1000e / r8169 (Realtek 8111 is the common desktop NIC) | open |
| 11 | Input without PS/2 emulation | some firmware drops legacy USB emulation after ExitBootServices | already covered by xHCI HID; verify on hardware | verify |

Real-hardware results land in the platform table above, each with the
exact failure and the gap it maps to.

### Known constraints off QEMU

- Boot is legacy MBR only (INT 13h LBA). Neither `os.img` nor `os.usb.img`
  carries a UEFI loader, and there is no El Torito support, so UEFI-only
  firmware without a CSM module cannot boot the image. The CSM-less path is
  a different image: `make uefi` builds `uefi.img` (a FAT image carrying
  `BOOTX64.EFI` from `boot/uefi_stub.c` plus `kernel.bin`), which reaches
  the kernel shell under OVMF (`docs/spec/boot-memory.md`).
- Disk drivers are IDE PIO (`drivers/ide.c`), virtio-blk, USB mass
  storage over xHCI (`drivers/usbblk.c`) and AHCI/SATA
  (`drivers/ahci.c`, below). Block backend preference is
  virtio > USB > AHCI > IDE, frozen at boot (`block: backend=...`). NVMe
  is still probe plus read-only queues, not a backend: a machine whose
  only disk is NVMe boots stage 1/2 through the firmware but the kernel
  will not find its MiniFS partition.
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
