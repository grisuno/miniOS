# Boot path, disk layout, physical memory map, KASLR, ASLR and the low-4MB hazard contract

Moved verbatim from CLAUDE.md (2026-09-29 compaction); CLAUDE.md keeps the
rules and hazards and indexes this file.

## Boot Path Contract
Two stages, because a correct single-stage loader does not fit in 512 bytes.
Every address, BIOS service, descriptor and control-register bit used by the
boot path is named in `bootdefs.h`; neither stage may carry a bare constant.

- `stage1.S` — the boot sector. Verifies INT 13h extended (LBA) support, reads
  stage 2 and jumps to it. Ends with `.org` so the assembler fails if the code
  ever outgrows the sector.
- `stage2.S` — the loader. Enables A20 (clearing the fast-reset bit before
  writing port 0x92), streams the kernel in 64 KB chunks through the staging
  buffer at 0x10000, copies each chunk above 1 MB during a short excursion
  into protected mode, builds the page tables (identity 2 MB leaves for the
  first gigabyte, with the low 4 MB split into the `PT0`/`PT1` KASLR scheme
  described below, which maps the whole kernel image + `.bss` contiguously
  at `[base, base+KASLR_IMAGE_SPAN)`), enables PAE and long mode, installs
  the 64-bit GDT at 0x8000 and jumps to the kernel at 0x100000. Loop state
  lives in memory, never in registers, so nothing is assumed about what the
  firmware preserves across INT 13h. Ends with `.org` to enforce its sector
  reservation.

The image is attached as an IDE disk: LBA addressing is not available for
floppies.

### UEFI native boot, Phase 2a landed, (b)(c) specified (T7)
`boot/uefi_stub.c` proves the firmware handshake under OVMF
(GOP mode query, memory map, LBA0 read; BDD `scenario_uefi`), and
slice (a) landed: the stub opens its own volume through LoadedImage
+ SimpleFileSystem, reads `kernel.bin` whole (AllocatePool,
`kernel.bin` sits at the FAT root of `uefi.img` since the `uefi.img`
rule copies it), validates a 4 KB..32 MB size plus a non-zero head,
calls ExitBootServices with a fresh map key, and jumps to a 64-bit
entry that prints `uefi: handoff kernel=<n> mmap=<m>` over COM1 and
halts, with no kernel changes. Two hand-rolled facts this slice
taught, kept here so nobody re-learns them: GUID Data1/Data2 are
byte-checked against EDK2, never memory (LoadedImage is 5B1B31A1,
SFS Data2 is 0x6459; each wrong byte is a silent EFI_NOT_FOUND),
and EFI error codes carry bit 63 (BUFFER_TOO_SMALL is
0x8000000000000005, never 5). Pinned by `uefi-sfs-guid-wrong`,
`uefi-kernel-name-wrong` and `uefi-errbit-dropped` under
`MATCH="uefi"`. Slice (a) landed above.
Slice (b/c) Phase2b landed: the stub AllocateAddresses its low zones
(page tables, GDT/trampoline/scratch, user-table zone; the 0x80000
stack zone is map-verified post-exit-borrowed instead, one
BootServicesData page there refuses AllocateAddress), writes the
stage2 contract (KASLR dword, GOP-fed VBE block or zeroed fallback,
5-entry GDT, 1 GB identity 2 MB tables), and jumps through a 67-byte
trampoline (RETF with CS 0x08 pushed: EA ptr16:32 is #UD and FF/5
m16:64 #GPs in long mode; LGDT is /2, /3 loads the IDT instead, found
by objdump of kmain+0x15 faulting on its SS load). The kernel reaches
a serial shell prompt under OVMF (`MiniOS Kernel`, `kernel:
physical base 0x100000`, `miniOS> `, all `MATCH="uefi"`). Pinned by
`uefi-tramp-cs-wrong`, `uefi-pt-flags-nops`, `uefi-gdt-code-data`.
Remains: GOP-present validation (this OVMF build reports GOP
unavailable, so the VBE-from-GOP path is written but unproven),
UEFI KASLR (base is the plain link address), and booting os.img
itself (FAT partition carrying BOOTX64.EFI) for the full BDD suite.
`boot/uefi_stub.c` already proves the firmware handshake under OVMF
(GOP mode query, memory map, LBA0 read; BDD `scenario_uefi`), but the
kernel still boots only through stage1/stage2, so CSM-less hardware
is out of reach. The handoff lands in three slices. (a) The stub
reads `kernel.bin` whole through SimpleFileSystem (ramdisk rides
embedded, so one blob), calls ExitBootServices, and jumps to a
64-bit UEFI entry that prints its handoff block over serial and
halts: proves load + exit + jump with no kernel changes, BDD-visible
over OVMF COM1. (b) Dynamic framebuffer: `FB_ADDR` is ABI-fixed in
`minios_abi.h` today and no GOP mode is guaranteed to match it, so
`vga_fb` must accept the handoff framebuffer (base/pitch/geometry)
with an ABI version bump; VESA/VGA text stays as the fallback, never
removed in the same slice. (c) Full boot to shell under OVMF with the
BDD suite re-run against the UEFI image (the `scenario_uefi` harness
already exists; it asserts handshake lines today, shell markers
after). The page-table scheme reuses the PT0/PT1 KASLR layout (an
identity region for the loaded image, built by the entry, not by
firmware), and INT 13h code paths stay untouched: one image boots
both ways, selected by firmware, never by build flag.

### Disk layout
```
LBA 0        stage 1
LBA 1 .. 8   stage 2
LBA 9 ..     kernel image (kernel.bin, ramdisk embedded)
2048-aligned MiniFS partition (minifs.bin), found by superblock probe
64 MB swap hole (131072 sectors), reserved, no writer today
FAT32 reference image (etc/fat.img), superfloppy, no MBR entry
ext4 reference image (etc/ext4.img), superfloppy, no MBR entry
```
`KERNEL_SECTORS` is supplied by the build from the size of `kernel.bin`; the
LBA constants come from `bootdefs.h` so the Makefile and the assembly cannot
disagree.

The tail of the image is assembled by the `os.img` rule (`Makefile:2662-2685`)
and every part of it is located by a PROBE, never by a computed offset:

- The MiniFS partition starts at the first 2048-sector boundary at or after
  the kernel image (`DISK_ALIGN_SECTORS = 2048`). The kernel does not trust
  that arithmetic: `minifs_mount` tries the computed guess first and then
  every 2048-aligned candidate, accepting the first superblock whose magic,
  version and block size all match, and failing closed when none does
  (`fs/minifs.c:1492-1539`). The reason is in the code: the `KERNEL_SECTORS`
  fast path is compiled into stage2 only, so the C unit sees the
  ramdisk-size fallback, which underestimates the kernel image and lands
  before the real partition. See `docs/spec/shell-fs.md` ("MiniFS mount is a
  superblock probe").
- The 64 MB hole after MiniFS is the reserved swap area (131072 sectors,
  the same size as `SWAP_MAX_SECTORS` in `kernel/mm/swap.c:21`). Nothing
  writes it today: the swap-out path is unwired (the isolated-window spawn
  path superseded it) and, when it does run, it addresses the LAST 131072
  sectors of the disk (`kernel/mm/swap.c:41-45`), not this hole.
- The FAT32 and ext4 reference images are appended past the swap hole as
  superfloppies: `os.img` carries no partition table for them, so the
  drivers find them exactly as they find a filesystem on real hardware —
  a genuine MBR entry proven by a BPB/superblock read first, then a
  2048-aligned magic scan for superfloppy layouts (GPT protective degrades
  to the scan). That is what lets `fat ls hd0` and `ext4 ls hd0` exercise
  the device path end to end against `os.img` (`docs/spec/shell-fs.md`).
  The USB image (`os.usb.img`) adds one MBR partition over the whole tail
  for `fdisk`/`parted`; the bootloader reads raw LBAs and ignores it.

### VESA/VBE probe (before long mode kills BIOS video)
Stage 2 probes VESA BIOS Extensions while the BIOS video services are still
alive. The probe runs in real mode after the kernel image is fully loaded and
must complete before the transition to long mode, which kills INT 10h
(`arch/x86/boot/stage2.S:315-324`).

The mode ladder (`vbe_probe`, `arch/x86/boot/stage2.S:325-357`) is:
1024x768x32 (0x0118), 1024x768x8 (0x0105), 800x600x32 (0x0115), 800x600x8
(0x0103), 640x480x32 (0x0112), 640x480x8 (0x0101), and finally the VGA Mode
13h fallback (320x200x8, framebuffer at 0xA0000). A candidate is accepted
only when INT 10h AX=4F01 returns the 0x4F signature, the mode-attribute word
claims supported (0x01) and linear framebuffer (0x80), and the bpp byte is
8, 24 or 32 — a 15/16-bit mode is skipped because the kernel carries no
RGB565 packer. True color is preferred at each resolution, so the desktop is
never quantized when the mode exists; the 8-bit modes keep the 256-entry VGA
DAC path.

The handoff is a fixed struct at `VBE_INFO_ADDR` (0x7E20,
`headers/arch/x86/boot/bootdefs.h:149`): physical framebuffer base, pitch,
width, height, a valid byte and the bpp. The Mode 13h fallback fills the
same struct with its own defaults, so the kernel always finds a complete
record. The kernel reads it once at boot (`vga_fb_boot_config`,
`kernel/vga_fb.c:90-115`) and maps the physical framebuffer into the user
window at `FB_ADDR` (0x0B200000, `MINIOS_FB_ADDR`) page by page and slot by
slot, so a multi-megabyte framebuffer spanning two 2 MB PD slots is fully
mapped (`kernel/mm/paging.c:84-106`).

### Physical memory map
```
0x00000-0x004FF  IVT and BIOS data area
0x01000-0x04FFF  long-mode page tables (PML4, PDPT, PD)
0x10000-0x1FFFF  user page table zone (64 KB, PT_USER_TABLES_ADDR)
0x07C00-0x07DFF  stage 1
0x07E00-0x07E14  disk address packet, boot drive and KASLR base scratch
0x07E20-0x07E2B  VBE handoff struct (VBE_INFO_ADDR: framebuffer base, pitch,
                 width, height, valid, bpp)
0x08000-0x08027  long-mode GDT handed to the kernel (kernel + user segments)
0x09000-0x0AFFF  stage 2
0x10000-0x8FFFF  kernel staging buffer (64 KB chunks, reused; the first
                 64 KB are reclaimed by the user page table zone)
0x80000-0x87FFF  syscall kernel stack (SYS_KSTK_TOP 0x88000)
0x78000          AP stub stack (identity-mapped, below LAPIC PD)
0x90000          protected/long mode stack top
0x100000         kernel image (virtual; physical base random per boot, see
                 KASLR). The whole kernel, code + .bss, maps contiguously and
                 must end below 0x400000; mm_setup_protections asserts it.
0x400000         user program load base
0x0B000000       DOOM back-buffer (DOOM_BACKBUF_ADDR, brk cap)
0x0B200000       linear framebuffer (FB_ADDR)
0x0B400000       Nuklear back-buffer (NK_BACKBUF_ADDR)
0x0B000000       user stack base (USER_STACK_BASE, 1 MB)
0x0C000000       kernel heap start (HEAP_BASE, 448 MB max: clamped to the
                 RAM CMOS reports, kheap_size; ends at 0x28000000)
0x28000000       KASLR window for the kernel image (64 x 2 MB slots,
                 [0x28000000, 0x30000000); a BIOS boot needs >= 768 MB)
```

The user page table zone at `0x10000` is a hard contract: it sits BELOW the
kernel link base, so no kernel code, data or `.bss` can ever land on it, in
the plain build or under KASLR. It is deliberately **not** placed "between
the kernel image and the user window": the kernel `.bss` is ~1.4 MB and
grows, so a zone at `0x300000` sits exactly where the `.bss` lands once the
image outgrows 2 MB. That collision used to corrupt the user page tables
every time the shell wrote a terminal line (the terminal line buffer lived
in the `.bss` tail), which is why user programs crashed intermittently at
"unmapped" addresses. Do not move this zone above `0x100000`; if the kernel
needs more than 3 MB of image, grow `KASLR_IMAGE_SPAN` and the link layout
together, never re-home the page tables into the image footprint.

### KASLR
The kernel image always executes at virtual `0x100000`, but its physical
base is randomized at boot when built with KASLR (the default; disable with
`make ENABLE_KASLR=0`). Stage 2 reads the TSC and the CMOS clock
(seconds, minutes and hours shifted into distinct bytes) and slides the
copy destination to `KASLR_MIN_ADDR + (entropy & (KASLR_MAX_UNITS-1)) *
KASLR_ALIGN` — 64 aligned 2 MB slots in `[0x28000000, 0x30000000)`, right
above the kernel heap (`kernel.c` asserts at compile time that the heap ends
at or below `KASLR_MIN_ADDR`). The choice is written to `BOOT_KASLR_ADDR`
so the kernel can report its own physical base.

The low 4 MB stay identity mapped with a twist: `PT0` maps `[0x100000,0x200000)`
to the kernel base and `PT1` maps `[0x200000,0x400000)` to `base+0x100000`
through `base+0x300000` (the tail of the kernel image, the embedded ramdisk
and the whole `.bss`). The kernel therefore spans ONE contiguous physical
range `[base, base+KASLR_IMAGE_SPAN)`; a `.bss` that grows past 2 MB can no
longer spill onto the identity-mapped low-memory reserved zones. This is the
fix for the historical bug where the `.bss` tail landed on the user page
table zone and corrupted it on every terminal line. The user page table zone
itself lives at `0x10000`, below the kernel image, and is reached through
the `PT0` low identity mapping. In the non-KASLR build the whole low 4 MB
are identity mapped as before, and the zone still sits at `0x10000`, below
the image, so it can never collide.

Entropy mixing keeps its strength independent of boot timing: hours,
minutes and seconds feed separate bytes, so two boots in the same second
still differ by the RDTSC term. The kernel heap and user window are
 unaffected; KASLR randomizes only the kernel image's physical base. A KASLR
 kernel spans physical `[X, X+KASLR_IMAGE_SPAN)` and the BDD suite asserts
 the banner never reports base `0x100000`.

### Userspace ASLR
Every exec (legacy `run`, `mrun`/SPAWN, `execve`) jitters the new
 program's addresses with fresh TSC+ticks+counter entropy
 (`aslr_mix` in `kernel/sched.c`, declared in `sched.h`): the stack
 top slides 1..4096 bytes (same pages ensured, the unused top is a
 guard gap), brk starts 1..256 pages past the image (clamped to the
 cap, never past it), the mmap cursor starts up to 255 pages down
 (clamped above brk_limit), and an ET_DYN base slides up to 47 2 MB
 slots (loader bounds still fail closed). Slides are never zero for
 stack/brk, so consecutive execs differ observably. Fork never
 re-randomizes (children share by definition). Proven by
 `progs/src/aslr.c`: a self-exec chain prints sp/brk/mmap in gen0,
 re-execs carrying them, and gen1 prints `aslr: ok` when any
 dimension differs (`SAME` otherwise, exit 1); the BDD scenario runs
 it with `mrun` and the `aslr-no-entropy` mutant (mixer forced to
 zero, every slide constant) dies on it. No in-tree ET_DYN binary
 exists yet, so the DYN slide shares the mutant-pinned mixer but
 waits for the first PIE for live proof.

### Memory-layout hazard contract (read before touching the low 4 MB)
The low 4 MB are a deliberately hand-arranged jigsaw: kernel image + `.bss`,
user page tables, boot data and the user window all coexist in one identity
space. Getting it wrong silently corrupts the user page tables and makes
user programs crash at "unmapped" addresses — that is the historical
`EXCEPTION 14` that has bitten this codebase more than once. The invariants:

1. The user page table zone is `PT_USER_TABLES_ADDR` (`0x10000`), 64 KB of
   the boot staging buffer that is dead once the kernel runs. It is BELOW
   the kernel link base (`0x100000`), so kernel code, data and `.bss` can
   never reach it — in the plain build or under KASLR. Never move it above
   `0x100000`, and never size it down: `mm_setup_protections` writes one
   4 KB table per 2 MB PD slot of the user window.
2. The kernel image (code + `.bss`) must stay inside
   `[0x100000, KASLR_IMAGE_SPAN)` — below `0x400000`, the user window. The
   kernel `.bss` is ~1.4 MB and grows, so `KASLR_IMAGE_SPAN` is 3 MB; a
   growing `.bss` is what used to spill onto the `0x300000` page table zone.
   `mm_setup_protections` asserts `_kernel_end <= USER_LOAD_BASE` at boot and
   prints a diagnostic instead of silently mapping the user window over the
   kernel. The same bound is enforced fail-closed at build time: `make
   check-size` (a prerequisite of `kernel.bin`, so every `make os.img` runs
   it) compares `_kernel_end` from `kernel.elf` against `USER_LOAD_BASE`
   from `progs/minios_abi.h` and fails the build on overflow — a few
   kilobytes over kills the framebuffer mapping (black screen) and every
   ring-3 ELF, so this must never be discovered in QEMU. If the kernel outgrows 3 MB, grow `KASLR_IMAGE_SPAN` (bootdefs.h)
   AND the KASLR PT1 mapping (stage2.S) AND the link layout together — never
   shrink the gap by re-homing the page tables into the image footprint.
   Because the gate is binding, size-critical translation units may carry
   their own optimization flag with a NOTE at the rule: `shell.o` (the
   largest TU) builds `-Os` against the kernel-wide `-O1`, the same pattern
   the ramdisk `cvm.o` objects already use. A per-TU flag changes codegen
   for the whole unit, so it must be revalidated by the shell-heavy suites
   (`test_all.sh`, the editor/vol/kill BDD scenarios), never assumed safe.
3. The kernel `.bss` is NOBITS and relies on zeroed RAM: QEMU zeroes memory
   at boot, so `.bss` needs no loader zero-fill. Do not rely on this for
   anything except `.bss`; anything with file content must be loaded.
4. The KASLR `PT0`/`PT1` split exists only to slide the kernel image to a
   random physical base. `PT0` maps `[0x100000,0x200000)` to `base`,
   `PT1` maps `[0x200000,0x400000)` to `base+0x100000..base+0x300000`.
   There is no identity mapping left in `[0x300000,0x400000)` on a KASLR
   build; if you need low-memory identity beyond the first MB, add it to
   `PT0`'s low half, never steal it from the kernel image's contiguous span.
5. The DOOM back-buffer and the VESA framebuffer are mapped into the user
   window by writing PTEs inside the `PT_USER_TABLES_ADDR` zone (see
   `mm_setup_protections`); any new "map kernel memory into the user
   window" feature must write into those tables the same way, never into
   the PD leaves or the kernel image.
6. A kernel-heap buffer mapped page-by-page into the user window MUST be
   page-aligned. x86 masks a PTE's low 12 bits into flags, so a
   16-byte-aligned `kmalloc` pointer makes the first mapped page start at
   `buf & ~0xFFF` — up to 4095 bytes BEFORE the buffer. A guest writing
   its whole frame to the mapped VA then overwrites the heap chunk in
   front of it; when that chunk is a live `KFILE` the next seek/close hits
   the corrupt fields (the historical `kfile: corrupt handle` /
   `kfree: wild pointer` black screen, seen through SYS_SPAWN and after
   several spawned programs). `mm_setup_protections` allocates the DOOM
   and Nuklear back-buffers through `mm_page_aligned_alloc` (over-allocates
   one page, rounds the base up) and asserts `phys & 0xFFF == 0` for both.
   Never map a raw `kmalloc` pointer page-by-page without aligning it.

### Image budget gate and its levers
The build-time half of hazard contract item 2. `make check-size` is a
prerequisite of `kernel.bin` (`Makefile:2567`), so every `make os.img` runs
it. It reads `_kernel_end` from `kernel.elf` and compares it against
`USER_LOAD_BASE` taken from `progs/minios_abi.h` (the same header the kernel
derives its layout from, so the two cannot disagree), and fails the build
on overflow (`Makefile:2577`, `Makefile:2589-2606`). It also proves the
`kernel.ld` mirrors of the user window equal the ABI header, so editing the
window in one file without the other fails here, never at boot
(`Makefile:2583-2597`).

The image is code + data + the embedded ramdisk + `.bss` (`Makefile:2572`),
and the documented levers are:

- **Per-TU `-Os`** against the kernel-wide `-O1`: `shell.o` is the precedent
  (`Makefile:2171-2177`), the ramdisk `cvm.o` objects use the same pattern.
  A per-TU flag changes codegen for the whole unit, so it must be
  revalidated by the shell-heavy suites, never assumed safe.
- **Trimming the ramdisk.** The ramdisk is packed into the image as the
  `.ramdisk` section (`ramdisk.bin` -> `ramdisk_data.c` -> `ramdisk_data.o`,
  `Makefile:2112-2116`, `Makefile:2307`), so dropping files from the ramdisk
  list shrinks the kernel image directly.
- **The `VMA_MAX` pool bound.** `VMA_MAX` is 2048 nodes
  (`headers/vma.h:31`). One static pool lives in `.bss` — `vma_pool[VMA_MAX]`
  at `vma.c:13`, 64 bytes per node, 128 KB — and the per-process pool is a
  kernel-heap allocation of the same size (`kernel/sched.c:346`), so the
  bound scales both. Lowering it shrinks `.bss` at the cost of how many live
  VMAs one program may hold; the pool fails closed when exhausted, and a
  node that is deleted is recycled before the pool grows
  (`vma.c:31-34`).
