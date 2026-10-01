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

### UEFI native boot, Phase 2 (T7, specified, stub proven)
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
```
`KERNEL_SECTORS` is supplied by the build from the size of `kernel.bin`; the
LBA constants come from `bootdefs.h` so the Makefile and the assembly cannot
disagree.

### Physical memory map
```
0x00000-0x004FF  IVT and BIOS data area
0x01000-0x04FFF  long-mode page tables (PML4, PDPT, PD)
0x10000-0x1FFFF  user page table zone (64 KB, PT_USER_TABLES_ADDR)
0x07C00-0x07DFF  stage 1
0x07E00-0x07E14  disk address packet, boot drive and KASLR base scratch
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
0x0C000000       kernel heap start (HEAP_BASE, 192 MB)
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
KASLR_ALIGN` — 64 aligned 2 MB slots in `[0x6000000, 0xE000000)`, inside
the 256 MB RAM the image targets. The choice is written to `BOOT_KASLR_ADDR`
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
