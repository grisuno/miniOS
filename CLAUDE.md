# MiniOS Contract

## Purpose
MiniOS is a 64-bit x86 teaching kernel that hosts the miniGCC toolchain. It
boots from a raw disk image, runs programs in three formats, and carries the
whole toolchain on its ramdisk so that programs can be written, compiled,
linked and executed without ever leaving the machine:

```
edit src/p.c                          write C inside the OS
run objects/minigcc.o src/p.c > asm/p.s   compile to x86-64 AT&T assembly
run objects/ld.o -f elf -o bin/p.elf asm/p.s   assemble and link
run bin/p.elf                         execute
```

`ld -f cvm` produces a CVM module instead, executed by the cvm2 interpreter
that ships as `cvm.o`.

## Execution Formats
| Format | Loader | Notes |
|--------|--------|-------|
| `ET_REL` (`.o`) | `elf_load` | relocatable, linked against the kernel symbol table |
| `ET_EXEC` / `ET_DYN` | `load_exec_elf` | Linux binaries, syscall ABI, run unmodified |
| `.cvm` | `cvm.o` | CVM v2 stack bytecode |

Linux compatibility is a hard requirement: a static binary built by the host
toolchain must run by copying it onto the ramdisk, with no translation.

### CVM modules (`.cvm`)
A CVM v2 module runs with a Linux-style argv: `run <file>.cvm [args...]`
passes the module path as `argv[0]` and the remaining words as `argv[1..]`,
so the startup code every `ld -f cvm` module carries reads `argc` and
`argv` exactly as on real hardware, and a program like
`run minigcc.cvm test.c` works without extra ceremony. The data section is
laid out so that argument passing can never corrupt module data: globals,
string blobs and extern slots precede the x86 stack region, `ld` stores the
region's offset and size in the module ABI area, and the interpreter reads
those values at run time (older modules without the stored offset fall back
to the fixed layout). `cvm_set_args` copies the argument strings into the
module heap and builds the argv pointer array in the reserved area above the
stack region; a module whose layout cannot hold the argument list is
rejected with a diagnostic, never silently corrupted.

## Source Contract
The system spans four repositories: this one plus
[miniGCC](https://github.com/grisuno/miniGCC),
[ld](https://github.com/grisuno/ld) and
[cvm](https://github.com/grisuno/cvm). The build must be reproducible from
those upstreams alone, so:

- `make sources` clones the missing ones and `make sources-update` pulls
  them. Neither ever modifies a directory that already exists, so a checkout
  with local work is never clobbered.
- Every location is overridable (`MINIGCC_DIR`, `LD_DIR`, `CVM_REPO_DIR`,
  `CVM_DIR`) and so is every origin (`MINIGCC_URL`, `LD_URL`, `CVM_URL`).
  Nothing in the build assumes an absolute path.
- Everything on the ramdisk is regenerated from source: `minigcc.o`, `ld.o`
  and `cvm.o` from the sibling checkouts, and the demo programs from this
  repository's own C sources in `progs/`, driven through miniGCC and `ld`.
  The prebuilt objects in `progs/` are a convenience for a first boot, never
  an input the build depends on.
- Ramdisk content is owned here. Reaching into another project's test
  fixtures for files to ship would break the moment that project reorganizes
  them, which is exactly what happened when the image was built from
  `ld/tests/*.s`.
- `ramdisk.bin` lists the `Makefile` among its prerequisites: the file list
  lives there, so editing it must invalidate the image even when no
  individual file changed.  `minifs.bin` carries the same rule for the same reason.
- `progs/bin/` ships the command-path utilities: `cp`, `freedom`, `lzss`
  and `unlzss`, compiled from this repository's own sources in `progs/src/`
  through the miniGCC-to-ld chain, with the sources on the ramdisk too so the
  OS can rebuild the utilities from scratch without leaving the machine.
  The ramdisk tree is organized by kind: `objects/` (ET_REL toolchain),
  `bin/` (Linux ELFs + command path), `cvm/` (CVM modules), `src/` (C
  sources), `asm/` (miniGCC assembly), `docs/`.

### Compression tools (`lzss` / `unlzss`)
`progs/src/lzss.c` is a single source that builds two command-path binaries:
the linker emits the same program as `bin/lzss` and `bin/unlzss`, and the
program selects its mode from `argv[0]` (any invocation path containing
`unlzss` decodes; `-d` forces decode explicitly).

- The codec is Okumura LZSS (window `LZSS_N` 2048, lookahead `LZSS_F` 17,
  threshold `LZSS_P` 1, MSB-first bit stream) so in-OS output interops with
  a host reference implementation; the window is pre-filled with 0x20
  exactly as the reference.
- The on-disk format is fail-closed: 4-byte magic `LZS1`, then the original
  size as a little-endian u32, then the bit stream. `unlzss` rejects a bad
  magic, a truncated stream and any declared size larger than the expansion
  bound derived from the input length (`LZSS_EXPAND_NUM`/
  `LZSS_EXPAND_DEN`), so a hostile header can never drive an oversized
  allocation, and a stream that would write past the declared size aborts
  before touching the output file.
- The codec works whole-file in memory (bounded, one `malloc` per side,
  sized from the input file and the derived expansion bound), compresses
  only when the result is reported with exact byte counts, and every I/O
  shortfall is a diagnostic plus a nonzero exit code, never a partial
  silent write.

### Compression tools (`lz4` / `unlz4`)
`progs/src/lz4.c` builds `bin/lz4` and `bin/unlz4` from a single source, with
the same `argv[0]` dispatch as `lzss` (any invocation path containing
`unlz4` decodes; `-d` forces decode). The codec itself lives in the kernel
(`lz4_kernel.c`, the same one MiniFS uses), so the tools are thin syscall
front-ends over two MiniOS syscalls, 216 `lz4_compress` and 217
`lz4_decompress`, which mirror `minifs_compress`/`minifs_decompress` byte
for byte. A call passes a user pointer validated to lie inside the user
window; a violating pointer returns `-EFAULT`.

- The on-disk block is the MiniFS block format, so `lz4` output interops
  with the filesystem's own LZ4 blocks: a 4-byte little-endian original
  size, then the raw LZ4 stream. `lz4_compress` refuses to write (returns
  0) unless the compressed stream is strictly shorter than the input, and
  `lz4_decompress` refuses a header whose declared size exceeds the output
  capacity or a stream that fails to decode to exactly that size.
- The front-ends work whole-file in memory (one `malloc` per side, the
  output side sized from `LZ4_COMPRESSBOUND` or the declared size), report
  exact byte counts, and every I/O shortfall or implausible declared size
  is a diagnostic plus a nonzero exit code, never a partial silent write.
- The ld stub set grows the `lz4_compress`/`lz4_decompress` entries (216,
  217) beside the other MiniOS syscalls, so the toolchain and the ramdisk
  binary rebuild together.
- The kernel `lz4_kernel.c` decompressor handles the literal-only tail of a
  stream correctly (a valid LZ4 block may end with a final literal sequence
  and no trailing match), so its own compressor round-trips and its output
  interops with a host reference decoder.

### Zip builtins (`unzip` / `zip`)
The shell's `unzip` and `zip` builtins read and write ZIP archives through
the miniz zip library, compiled into the kernel as a pristine upstream
amalgamation (3.0.2) in `third_party/miniz/` with the allocator redirected to
the kernel heap and stdio/time stripped (`MINIZ_NO_STDIO`, `MINIZ_NO_TIME`).
`miniz_impl.c` applies every knob through macros, the same pattern as the stb
wrapper; the amalgamated header forward-declares the writer's internal state,
so the heap writer's output buffer is exposed through two accessors
(`mz_zip_writer_mem_ptr`/`mz_zip_writer_mem_size`) defined where the full
struct is visible.

- Usage: `zip <out.zip> <file...>` stores each file (under its sanitized
  relative name) with the default compression level; `unzip <archive.zip>
  [dir]` extracts into `dir` (default the cwd), creating missing directories,
  and `unzip -l <archive.zip>` lists the entries. Both builtins work
  whole-file in memory over the unified file API (ramdisk first, MiniFS
  fallback), matching the compression tools contract: the archive is fully
  validated before any entry is published, output is written only after the
  whole archive was read, and every failure path reports a diagnostic and
  releases. The ld stub set is untouched: the builtins are shell features,
  not toolchain programs.
- Entry names are hostile data. Each is normalized to forward slashes,
  stripped of leading `/` and `./` repetitions, and **rejected when a
  component is `.`/`..` or empty** (`zip_sanitize_name`), so a crafted
  archive can never write outside the directory the user named — an absolute
  name degrades to a relative one, a traversal name is skipped. The BDD
  fixture `etc/hostile.zip` (generated by `tools/gen_zip_fixtures.py`, one
  entry `../escape.txt` beside a plain file, a directory marker and an
  absolute name) proves `escape.txt` is never created.
- `etc/host.zip` is a second generated fixture: a host-produced archive with
  a nested directory, proving the extractor interops with a reference ZIP
  writer and not just its own output. Both fixtures are regenerated from
  source at build time (fixed timestamps, reproducible) like the desktop
  icons.
- Fail-closed surface: a non-zip input is `unzip: <f>: not a zip archive`, a
  missing file is `unzip: <f>: cannot read`, an entry whose declared size does
  not match what the extractor produced aborts that entry, and a destination
  that is an existing file is refused. The mutation suite kills a traversal
  bypass (the hostile fixture), a bad-magic accept and a skipped finalize.

### JSON tool (`json`)
`bin/json` is a self-contained JSON validator, pretty-printer and query tool
built from `progs/src/json.c` through the miniGCC-to-ld chain; like DOOM and
MicroPython it ships on MiniFS (bare-name command at the MiniFS root), not on
the size-budgeted ramdisk. It is written
in the miniGCC subset, which has no structs, so the parsed value is a flat
node table of parallel arrays (`js_type`/`js_num`/`js_str`/`js_key`/
`js_first`/`js_count`/`js_next`); object members keep their key in `js_key`
and their value in the node itself.

- Usage: `json <file>` validates and pretty-prints; `json <file> <path>`
  prints the value at a dotted path (`.a.b`, `.a.3`, bare `.a`). A missing
  path is `json: <path>: not found` with exit 1, never a crash.
- The parser is fail-closed: truncated input, a trailing non-whitespace
  token, an unbalanced `}`/`]` and an unknown escape all report
  `json: <file>: invalid JSON` with exit 1. String escapes (`\n \t \r \b \f
  \" \\ \/`, and `\u` mapped to `?`) decode into a bounded string pool, and
  the pretty-printer re-escapes them so its output is itself valid JSON.
- The node table, string pool and query segment are all size-bounded by named
  constants (`JS_MAX_NODES`, `JS_POOL`); an input that would exceed a bound
  is a diagnostic plus exit 1, never a silent overflow.
- cJSON (single-file, struct-based) was tried as a portable engine and does
  not compile under miniGCC (structs, `->`, `double`, `CJSON_PUBLIC`), which
  is why this hand-rolled flat-table parser exists.

### Encryption tool (`aes` / `unaes`)
`progs/src/aes.c` builds `bin/aes` and `bin/un aes` from a single source with
the same `argv[0]` dispatch as the other command pairs (a path containing
`unaes` decrypts; `-d` forces decrypt). Like DOOM, MicroPython and `json` it
ships on MiniFS (bare-name commands at the MiniFS root) instead of the
size-budgeted ramdisk.

- The cipher is AES-256 (NIST FIPS-197) written in the miniGCC subset: no
  structs, flat int arrays masked to bytes at every step, and an S-box
  generated procedurally from the GF(2^8) multiplicative inverse plus the
  FIPS-197 affine transform, so the file carries no magic tables.  Round
  expansion follows FIPS-197 for Nk=8/Nr=14, including the extra SubWord
  pass every Nk/2 words.
- The mode is CTR (NIST SP 800-38A): no padding, encrypt and decrypt share
  one code path, and the big-endian counter increments over the full block.
  Usage: `aes [-d] <key-hex64> <nonce-hex32> <src> <dst>`; a nonce must
  never repeat under the same key.  CTR gives confidentiality only, not
  authentication - a flipped ciphertext byte flips the matching plaintext
  byte, so integrity needs a MAC layered above this tool.
- The container is fail-closed: 4-byte magic `AES1`, then the original size
  as a little-endian u32, then the raw keystream XOR.  Decoding refuses a
  bad magic, a truncated header, and any body whose length does not equal
  the declared size exactly; key and nonce hex are length- and alphabet-
  validated before anything runs.
- Host verification lives in `tests/host_aes.sh`: the NIST F.5.5 CTR-AES256
  known answer, byte-for-byte ciphertext equality against OpenSSL across a
  multi-block stream, reverse-direction interop (OpenSSL ciphertext decoded
  by `unaes`), dispatch modes, empty input, and the fail-closed set.  Five
  one-line mutants of the codec (ShiftRows drop, polynomial, affine
  constant, AES-256 extra SubWord, size-mismatch check) all die against it.

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
0x90000          protected/long mode stack top
0x100000         kernel image (virtual; physical base random per boot, see
                 KASLR). The whole kernel, code + .bss, maps contiguously and
                 must end below 0x400000; mm_setup_protections asserts it.
0x400000         user program load base
0x1FC0000        user stack base (USER_STACK_BASE, 256 KB)
0x2000000        kernel heap (64 MB)
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
   kernel. If the kernel outgrows 3 MB, grow `KASLR_IMAGE_SPAN` (bootdefs.h)
   AND the KASLR PT1 mapping (stage2.S) AND the link layout together — never
   shrink the gap by re-homing the page tables into the image footprint.
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

## VESA Hi-Res Desktop and Windowed DOOM

**Testing doctrine: VGA-mode work is driven with `tools/minios_gui.py`, never
headless.** A headless boot cannot observe or trigger desktop events (mouse
cursor, window drag, title-bar buttons, the return-to-desktop transition after
a ring-3 program), so a GUI bug seen by hand or assumed from code is not
reproduced. `minios_gui.py` boots QEMU with the std VGA device, a QMP socket
to inject PS/2 mouse motion, clicks and keyboard, and a pty serial console;
after each action it saves the framebuffer to a PNG via QMP `screendump`.
`gfx` / `gfx pixel x y` probe the framebuffer over serial as a text backstop.

The desktop runs at a VESA linear-framebuffer resolution (800x600x8 by
default) instead of VGA Mode 13h, and DOOM runs in a titled window at its
native 320x200 instead of stealing the whole display.

- **Boot path (stage2.S + bootdefs.h):** after the kernel image is loaded and
  before long mode kills the BIOS video services, stage 2 probes VESA BIOS
  Extensions for an 8-bit-palette linear-framebuffer mode: 800x600x8
  (`VBE_MODE_800x600x8`), then 640x480x8, then VGA Mode 13h as a fallback. It
  writes `{phys_base, pitch, width, height, valid}` to the fixed low-memory
  struct `VBE_INFO_ADDR` (0x7E20). The 8-bit modes keep the 256-entry VGA DAC
  path the desktop and DOOM share. No bare VBE constant appears in the
  assembly; every mode number, offset and attribute lives in `bootdefs.h`.
- **Kernel mapping (kernel.c `mm_setup_protections`):** `vga_fb_boot_config`
  loads the VBE struct into `fb_width`/`fb_height`/`fb_pitch`/`fb_phys_base`,
  and the kernel maps that physical framebuffer into the user window at the
  fixed virtual `FB_ADDR` (0x1F00000), replacing the old 0xA0000 mapping. All
  drawing addresses through `FB_ADDR` (desktop and graphics programs) work
  unchanged; pixel addressing honors `fb_pitch`.
- **Movable shell window (vga_fb.c):** the shell runs in a window (default
  72x40 cells, clamped to the framebuffer) with a title bar on top and a
  scrollbar on the window's right edge, over a desktop background with a
  bottom taskbar. Click-and-drag on the title bar moves the window with the
  mouse; F11 toggles fullscreen, F5 resets the position. Window geometry is
  independent of the framebuffer dimensions.
- **Windowed DOOM (syscall 211 + doomgeneric_minios.c):** the kernel maps a
  64 KB kernel-heap back-buffer into the user window at `DOOM_BACKBUF_ADDR`
  (0x1FE0000, RW, NX). DOOM renders its 320x200 frame there and calls
  `SYS_DOOM_FRAME`; the kernel composites the buffer 1:1 onto the desktop in a
  titled window, centered on the screen (`vga_fb_blit_gfx_window`), leaving the
  shell window and desktop visible. The window is centered because a graphics
  program owns the display while it runs (no mouse), so it cannot be dragged
  into a better spot during play. When a graphics program exits the kernel
  redraws the desktop and restores the 15-color desktop palette.
 - **Known limitation:** an 8-bit palette mode has one global 256-color DAC, so
   while DOOM runs its 256-color palette recolor the desktop behind the window.
   The window geometry and shell remain correct; only the desktop's colors
   shift until the next `vga_fb_draw_desktop`. A 16/24-bit VBE mode would fix
   this but is out of scope.

### ISR-driven desktop event loop (`sched.c` + `vga_fb.c`)

The desktop event loop (`vga_fb_mouse_tick`) must run continuously regardless
of whether the shell or a user program owns the CPU.  Historically it ran
only inside `raw_blocking_getc` (the shell's idle poll), so the desktop froze
whenever `k_exec_user` entered ring 3 for a child process.  The mouse cursor,
taskbar clock, window drag and scrollbar all stopped responding.

The fix is a timer-ISR-driven tick: the 100 Hz PIT handler (`isr_dispatch`,
vector 32) calls `vga_fb_mouse_tick` at a configurable interval
(`DESKTOP_TICK_INTERVAL`, default 4 = 25 Hz) whenever `user_program_active`
is set.  The flag is set in `k_exec_user` before the `iretq` into ring 3 and
cleared after `klongjmp` returns, so the desktop ticks for the entire
duration of any user program.  When no user program is active the flag is
clear and the ISR skips the tick; the shell drives the desktop from its own
idle loop as before.

The PS/2 mouse is no longer disabled around `k_exec_user`.  Disabling the
mouse stopped IRQ12 delivery and froze `mouse_state` for the whole child
execution, which defeated the ISR tick.  With the mouse always enabled the
IRQ12 handler updates `mouse_state` continuously, and the ISR tick or the
shell idle loop consumes it.  There is no reentrancy hazard: the timer ISR
preempts ring-3 code and the IRQ12 handler runs at a lower priority; both
access the same `mouse_state` struct, but x86 field-width stores are atomic
and the consumer (tick or shell) is the sole reader.

The iretq frame now uses `RFLAGS=0x202` (IF=1) instead of the original
`0x002` (IF=0).  With IF=0 the CPU ignores all maskable hardware interrupts
while a ring-3 user program runs, so neither the timer ISR nor the PS/2
mouse IRQ fires and the desktop is completely frozen.  With IF=1 the timer
fires at 100 Hz from ring 3, driving the desktop tick, and IRQ12 delivers
mouse packets continuously.  The kernel's IDT (installed by `sched_init`
before any user program runs) handles all interrupts from ring 3; the user
program does not need its own IDT.

Configuration constants:
- `DESKTOP_TICK_INTERVAL` (`sched.h`): ISR ticks between desktop updates
  when a user program is active.  4 = 25 Hz at 100 Hz PIT.  Lower values
  produce smoother cursor tracking at the cost of ISR overhead; higher
  values reduce overhead at the cost of visible cursor lag.

The `user_program_active` flag is `volatile int` declared in `sched.h` and
defined in `sched.c`.  It is set only in `k_exec_user` and read only in
`isr_dispatch`, both in ring 0, so no memory barrier is needed beyond the
`volatile` qualifier.

### Userspace desktop architecture (design spec, future implementation)

The long-term goal is to move the desktop compositor to a ring-3 userspace
process, achieving proper separation of concerns: the kernel owns scheduling
and hardware access, the desktop process owns rendering and input routing,
and user programs run concurrently under preemptive scheduling.

**Desktop process:** a static ELF binary compiled on the host, shipped on
MiniFS as `bin/desktop`.  It runs at ring 3 through `k_exec_user` and
renders the desktop background, taskbar, terminal window, and composites
DOOM/Nuklear back-buffers.  The framebuffer is already mapped user-accessible
at `FB_ADDR` (0x1F00000), so the desktop process writes pixels directly
without kernel mediation.

**Input routing:** the desktop process reads mouse events via `SYS_MOUSE`
(219) and keyboard events via `SYS_KBD` (205).  Keyboard events that belong
to the shell (typing) are forwarded through a shared ring buffer at a fixed
address in the user window (`DESKTOP_KBD_BUF`, size `DESKTOP_KBD_BUF_SZ`).
The shell reads from this buffer instead of polling the PS/2 keyboard
directly.  The desktop process owns the keyboard and decides what reaches
the shell.

**Shell output routing:** the shell writes text output to a shared terminal
ring buffer at `DESKTOP_TERM_BUF` (size `DESKTOP_TERM_BUF_SZ`).  The
desktop process reads from this buffer and renders it in the terminal window.
This replaces the current path where `vga_putc` writes directly to the
framebuffer.  The kernel's `vga_fb_putc_term` writes to the ring buffer
instead; the desktop process handles line wrapping, scrollback, and
rendering.

**Window compositing:** DOOM and Nuklear already render to kernel-heap
back-buffers and call `SYS_DOOM_FRAME`/`SYS_NK_FRAME` to composite.  In the
userspace model, the desktop process reads these back-buffers (mapped
read-only in the user window) and composites them itself, removing the
kernel-side compositing code.

**Preemptive scheduling:** the timer ISR preempts the desktop process,
giving CPU time to DOOM, Nuklear, or other user programs.  The desktop
process yields explicitly via `SYS_SCHED_YIELD` (24) when idle.  The
scheduler's round-robin policy ensures all processes get fair CPU time.

**Security model:** the desktop process runs at ring 3 with user page
protections.  It cannot access kernel memory, page tables, or hardware
ports directly.  All hardware access goes through syscalls with validated
user pointers.  The shared ring buffers live in the user window, so a
compromised desktop process cannot corrupt kernel state.  The kernel
validates all buffer addresses against `USER_LOAD_BASE..USER_LOAD_END`.

**Phased implementation:**
1. Phase 1 (done): ISR-driven desktop tick keeps the desktop responsive
   during user program execution.
2. Phase 2: add `SYS_DESKTOP_KBD_READ` and `SYS_DESKTOP_TERM_READ` syscalls
   that expose the shared ring buffers.
3. Phase 3: create the desktop binary, route shell I/O through ring buffers.
4. Phase 4: remove kernel-side compositing, let the desktop process own it.
5. Phase 5: enable preemptive scheduling for all user processes.

**Preemption blocker (deferred):** the full preemptive track (Phase 5 and a
non-blocking shell) is NOT implementable on the current single-address-space
model: `load_exec_elf` loads every ring-3 program at `USER_LOAD_BASE` into one
shared address space, so two concurrent programs would clobber each other's
user memory. It requires per-process page tables (a per-process CR3 switch in
`switch_to`, currently shared) plus per-process brk/mmap cursors and the
desktop-process phases above. This is the documented Phase 5 plan above; it is
deferred because it is a large, high-risk rewrite that would destabilise the
boot/test contract, not a small fix. It does not block the audio/perf work:
the piano's slowness was the SB16 ring wedge and the trace console flood, not
an absence of preemption.

### Taskbar with clock and volume (`vga_fb.c` + `rtc.c` + `pcspk.c`)
The bottom taskbar is the desktop's status strip, not a hint line. It shows
the current time and a speaker icon with volume control, both live, and both
wired to the same kernel state the shell's `date` and `vol` builtins expose
so the behaviour is serial-observable and BDD-testable even though the
framebuffer is not.

- **Clock (`rtc.c`):** `rtc_read_tod` reads the CMOS RTC time-of-day through
  the named ports and registers in `rtc.c`. It waits out the update-in-progress
  flag, decodes the binary-coded-decimal fields, and **fails closed**: a
  non-BCD field, an impossible hour/minute/second, or a clock that never stops
  updating returns failure, never a plausible-but-wrong time. The taskbar
  redraws the clock when the second changes and treats a failed read as "clock
  unavailable", never a stale value.
- **Volume (`pcspk.c`):** a master volume 0..100, `PCSPK_VOL_DEFAULT` at boot,
  clamped on set. The PC speaker has no hardware amplitude and this kernel does
  not drive a PWM carrier, so volume is a **mute switch**: `pcspk_tone` opens
  the speaker (port 0x61 bits 0 and 1, both required for the PIT2 square wave
  to sound) only when the volume is above `PCSPK_VOL_MIN`, exactly as the
  pre-volume driver did, so a default boot is byte-for-byte compatible and a
  tone always sounds. At volume 0 the bits stay low and the speaker is silent.
  Keeping the tone path identical to the original is deliberate: it is the
  guarantee that sound never regresses.
- **Taskbar widgets:** the speaker icon sits in the taskbar with `-`/`+`
  buttons that call `pcspk_set_volume`; a left click on the icon toggles
  mute, and the `-`/`+` buttons step the volume by `TASKBAR_VOL_STEP`. Mouse
  hit-testing lives in `vga_fb_mouse_tick` beside the existing title-bar drag
  and scrollbar logic; there is no separate input path.
- **Tiling shortcuts (Alt = WM modifier, `kernel.c` + `vga_fb.c`):** the window
  is moved, snapped and resized from the keyboard for a tiling-WM feel. Alt is
  tracked as a modifier beside Shift and Ctrl. Alt+Enter toggles fullscreen,
  Alt+arrows snap the window to the left/right/top/bottom half of the screen,
  Alt+Home/End snap to the top-left / bottom-right quadrant, Alt+`[`/`]`
  shrink/grow width, Alt+`-`/`=` shrink/grow both dimensions, and Alt+0 resets
  the window to its default position and size. The window keeps its current
  size across redraws (resize/snap persist instead of snapping back to the
  default like the old layout engine).
- **Window controls (title-bar buttons, `vga_fb.c`):** every titled window
  (terminal, DOOM, Nuklear) carries the classic three glyph buttons at the
  right end of its title bar — minimize (`_`), maximize (open square) and
  close (`X`) — drawn and hit-tested by the shared `wm_*` helpers. A click on
  minimize hides the terminal window (the content stays in the logical ring,
  so restoring repaints it with nothing lost); maximize toggles fullscreen;
  close restores the terminal to its default geometry because the shell
  cannot be closed. For a graphics window the buttons target the composited
  DOOM/Nuklear title bar: maximize is a no-op (the window is already display-
  sized) and close arms `wm_close_request`, which the syscall dispatcher
  honours on the child's next syscall (`exec_exit_code = 130`, `klongjmp` on
  the child's own stack — never from the ISR), so a graphics program is
  terminated cleanly from its title-bar X. Alt+M toggles minimize and
  Alt+X/Alt+Q close the active window. Fullscreen and minimize are mutually
  exclusive: entering one clears the other.
- **Minimize/restore (`wm` builtin):** while the terminal is minimized the
  window is not drawn and the taskbar shows a `[]` restore button on the far
  left. The mouse tick ignores wheel/drag/scrollbar while minimized. The `wm`
  builtin (`wm state`, `wm minimize`, `wm maximize`, `wm close`) drives the
  same functions as the buttons and shortcuts and reports state over the
  serial console, so the BDD suite asserts the WM behaviour exactly like
  `date`/`vol`/`gfx`.
- **Shell surface:** `date` prints `HH:MM:SS` from `rtc_read_tod` (a failed
  read prints a diagnostic); `vol [0-100]` prints the volume and, with an
  argument, sets it after strict decimal parsing and clamping. This is the
  TDD hook: the BDD suite asserts `date` and `vol` through the serial console.

## Kernel Contracts

### Ramdisk
The data area is sized from the image that is loaded plus a spare margin, and
grows on demand up to `RD_DATA_MAX`; it is never a fixed reservation that the
payload can silently outgrow. `ramdisk_setup_from` validates the whole image
(header, table extent, per-file offset and size, total against the maximum)
**before** publishing any entry, so a rejected image leaves the directory
untouched instead of advertising files whose data was never copied.

### ELF loaders
Relocation is fail-closed. Every relocation is bounds checked against the
section it patches; a relocation symbol index outside the symbol table, an
unsupported relocation type, or a symbol that the kernel cannot resolve
aborts the load with a diagnostic. An unapplied relocation would hand the
program a wild call target, so it is never skipped. No libc name is ever
registered with a null address.

### User-mode isolation
ET_EXEC / ET_DYN binaries run at ring 3 under hardware page protection;
ET_REL objects (the toolchain) remain ring-0 kernel extensions by contract,
because they are linked against the kernel symbol table. The boot path
installs user code/data segments (`GDT64_USER_CODE_SEL` 0x20, `GDT64_USER_DATA_SEL`
0x18, DPL 3) beside the kernel segments and the kernel marks the user window
`USER_LOAD_BASE`..`USER_LOAD_END` as user-accessible (`PT_FLAGS_USER`). Every
other page — page tables, kernel image, kernel heap, VGA, MMIO — stays
supervisor, so a user binary cannot read or write kernel memory: the U/S bit
stops it in hardware. Identity mapping remains a single address space: per-
process page tables (CR3 switch) belong to the preemption track, not this one.

The user window runs on eager 4 KB page tables for the whole
`USER_LOAD_BASE`..`USER_LOAD_END` range (`mm_setup_protections`), not on the
2 MB kernel pages, so the no-execute bit works: every user page starts
NX-clear (EFER.NXE is enabled), and `load_exec_elf` clears NX only on the
pages a program's executable segments occupy. A program cannot execute from
its stack, heap, `.data` or unmapped space — a jump into a non-executable
page faults and the machine resets (no IDT), never silently running
shellcode. The kernel heap keeps its 2 MB executable pages: `.o` toolchain
programs execute from the heap at ring 0 by contract. The page tables live
in the dedicated identity-mapped zone `PT_USER_TABLES_ADDR` (`0x10000`),
below the kernel image and never in the kernel heap, so neither the ramdisk
data buffer nor kernel `.bss` growth can ever clobber them.
The BDD suite proves the isolation with `cpl.elf` (reports ring 3),
`kmem.elf` (kernel pointers rejected) and `nx.elf` (a `ret` written to the
stack faults on fetch, so `poweroff` is never reached).

A user program is entered with `iretq` to ring 3 (CS `USER_CODE_SEL`, SS
`USER_DATA_SEL`, RPL 3) on a user stack carved from the top of the user
window (`USER_STACK_BASE`..`USER_STACK_TOP`). The program break is bounded
below that stack (`USER_BRK_END`) and anonymous `mmap` allocations are carved
from the same window, so every address a user program can obtain is a user
page. Syscalls switch to a dedicated kernel stack (`syscall_kstack`, exchanged
on entry, `SYS_KSTK_TOP`) and return with `sysretq`, so the kernel never runs
on a user stack and never touches the user red zone. The exit path
(`klongjmp` back to the shell) restores the kernel data segments and resets
the syscall kernel stack for the next program.

The syscall dispatcher is the hardened boundary. Every pointer argument is
validated to lie inside the user window before it is dereferenced (`write`,
`read`, `writev` buffers, `open` paths, `poll` fd arrays, socket `sockaddr`s
and payload buffers, `clock_gettime` timespec, DNS hostnames, TLS buffers);
string arguments must be NUL-terminated inside the window; a violating call
returns `-EFAULT`. `arch_prctl` accepts only canonical bases. Faulting user
code still resets the machine (no IDT): interrupt delivery, fault handlers
and a scheduler are the preemption track, not part of this contract.

### Shell
`cmd > file` redirects the command's console output into a ramdisk file
(truncating it); `cmd >> file` appends. Shell status text — exit codes and
the shell's own diagnostics — is lifted out of the capture: a redirection
captures what the command wrote, not what the shell reported about it.
This is what makes `run objects/minigcc.o p.c > asm/p.s` produce assembly a linker can
consume.

The prompt keeps a bounded command history (`SHELL_HIST_MAX` entries).
Up arrow (ESC `[` `A`, or PS/2 make code `E0 48`) recalls the previous
command onto the edit line; down arrow (ESC `[` `B`, `E0 50`) moves
forward again, back to the live line. The recalled text replaces the
line the user was typing, which is preserved while scrolling. The
history stores commands on submission (even unknown ones), skips
consecutive duplicates, and survives only until reboot. A bare ESC or
an incomplete escape sequence is discarded, never inserted into the
line, and the editor (`edit`) is unaffected: history is a shell-prompt
feature, not a readline library.

The prompt is a full mid-line editor, not an append-only line: the
cursor moves with Left/Right (ESC `[` `C`/`D`, PS/2 `E0 4B`/`4D`) and
Home/End (ESC `[` `H`/`F`, `E0 47`/`4F`); Delete (ESC `[` `3~`, `E0 53`)
removes the character at the cursor; backspace removes the one before it;
Ctrl+A/E jump to start/end; Ctrl+U kills to the start; Ctrl+K kills to
the end; Ctrl+W kills the word before the cursor. Inserting in the middle
of a line shifts the tail right, and a framebuffer block cursor
(`vga_fb_text_cursor`) tracks the edit position on the terminal window.
Every operation repaints the line (erase + rewrite + back the console
cursor up), so the display and the serial console agree. The escape
sequence reader (`consume_page_after_esc` + `raw_wait_seq`) polls a
bounded number of spins for the sequence's final byte, because a
serial-delivered escape arrives byte by byte: without that wait an
arrow/Home/End/Delete key arriving right after a command could be split
across reads and mis-parsed. A bare ESC that never completes a sequence
still degrades to a discarded key, never a hang.

Command resolution is a fixed order: builtin, registered program, then a
single runnable-file resolver. Every non-builtin command — whether typed
with `run` or bare — funnels through `shell_run_any`, so `run ld.o`,
bare `ld.o`, `run fib.elf`, bare `fib.elf`, `run fib.cvm` and bare
`fib.cvm` all behave identically.

The runnable-file resolver (`shell_resolve_run`) maps a bare name to a
full ramdisk path by suffix, through the toolchain directories `objects/`,
`bin/` and `cvm/` (`shell_run_dirs`, `SHELL_RUN_DIRS`):

| suffix | directory | example |
|--------|-----------|---------|
| `.cvm` | `cvm/` | `w1.cvm` |
| `.o`   | `objects/` | `ld.o`, `minigcc.o` |
| `.elf` | `bin/` | `fib.elf` |
| (none) | `bin/` | `cp`, `freedom` (command path) |

Resolution order is fail-closed and never truncates: a name with a `/` is
resolved against the cwd; a bare name is tried first against the cwd and
then through the suffix-picked directory and the remaining directories as
fallback. Every candidate must exist as a real file (`fs_is_dir` is
rejected, `ramdisk_open` must succeed) before it is run. A candidate whose
full path cannot fit `RAMDISK_FNAME_LEN` is skipped like a missing file,
never truncated.

A resolved file is then classified by content and run by the matching
loader (`shell_run_elf_buf`): `ET_REL` `.o` objects run at ring 0 through
`k_run_rel`, `ET_EXEC`/`ET_DYN` binaries run as ring-3 processes through
`k_exec_user`, and `.cvm` modules run on the `objects/cvm.o` interpreter
loaded on demand (`shell_run_cvm`). Because the file is reloaded and
relocated fresh on every invocation, running a toolchain object does not
grow the registered-program table. The exit code is reported exactly as
`run` reports it; an unresolvable name falls through to
`command not found` (bare) or `run: not found` (with `run`). `objects/`
and `cvm/` are never on the bare command path — only registered programs,
the current directory, and the suffix-driven `bin/` lookup answer a bare
name, so the command path stays root-anchored and an attacker can never
run an arbitrary `.o` as a command by name alone.

TAB completes the current word from registered programs and ramdisk file
names: one TAB fills the longest unambiguous prefix, a second TAB on a
unique match fills the whole name, and an ambiguous prefix lists the
candidates. The completion is bounds-checked and never writes past the
command buffer.

Known limitation (pre-existing, desktop-only): console scrollback is
windowed. The text-console PageUp scrollback ring is populated from the
80x25 `VGA_BASE` layer, so it stays empty while the windowed desktop is
active (shell output renders to the framebuffer window instead). The
desktop exposes its own scrollback through the terminal window's
mouse-wheel/scrollbar (`disp_off`), which redraws the framebuffer only and
does not re-emit lines to the serial console. The BDD scenario
`page up scrolls back to the boot banner` therefore asserts the serial
text-console behaviour and is expected to fail under the windowed desktop;
this is a pre-existing gap, not a regression.

Known limitation (pre-existing, under investigation): the BDD scenario
`stb image selftest loads test.png and checks pixel` times out — the guest
never reaches `poweroff`, so the kernel hangs (or the machine resets) while
the ring-0 `stb.o` selftest runs. It fails deterministically and predates
the zip/miniz work; it is tracked separately from this feature and is not a
regression.

### Network (rtl8139 + slirp)
The kernel owns an rtl8139 NIC under QEMU user networking (slirp) with the
standard fixed configuration: address `10.0.2.15`, netmask `255.255.255.0`,
gateway `10.0.2.2` (the host), DNS `10.0.2.3`. Every QEMU launch in the
build, the BDD suite and the MCP attaches `-nic user,model=rtl8139`.

- The driver polls the NIC (no interrupt controller is configured): TX
  waits for the descriptor owner bit, RX drains the classic ring by
  comparing CAPR against CBR. QEMU forces the legacy receive ring to
  8 KB (it masks the RCR ring-size bits out of writes), so the guest
  ring is 8 KB too; a frame that straddles the ring end is copied
  wrap-aware into a scratch buffer before it reaches the stack. The MAC
  is read from the NIC IDR registers.
- Stack: Ethernet (ARP cache, broadcast requests, replies to our address),
  IPv4 (checksum verified; fragmented datagrams are dropped, fail closed),
  ICMP echo, UDP and a minimal client TCP: SYN/SYN-ACK/ACK handshake,
  stop-and-wait with retransmission timeouts (PIT-calibrated TSC clock),
  FIN teardown, fixed 536-byte MSS and a bounded window. Every accepted
  segment advances the ACK number (a stale ACK stalls real servers that
  wait for acknowledgement before sending more), an out-of-order FIN is
  never reported as EOF before the data before it has arrived, and the
  receive buffer compacts instead of dropping when it is partially
  consumed. A kernel DNS client resolves A records against `10.0.2.3`
  (UDP, retries, bounded timeout).
- Programs reach the stack two ways. ET_REL programs get the libc-style
  symbols `net_open`, `net_connect` (resolves the hostname itself),
  `net_send`, `net_recv` (0 = EOF) and `net_close`. Linux binaries get
  the socket syscalls: `socket`, `connect`, `sendto`, `recvfrom`,
  `shutdown`, `close` and a minimal `poll` (POLLIN when data is ready,
  bounded timeout otherwise) — enough for a static glibc resolver.
- The shell gets `net` (status: MAC, IP, counters) and `net ping <ip>`
  (one ICMP echo, reported as `reply from <ip>` or a timeout diagnostic).
- All constants are named in `net.h` (`NET_*`); none of the fixed
  addresses, ports or timeouts appears as a bare literal.

### TLS client (tls.c + tls_crypto.c + tls_x509.c)
The kernel speaks TLS 1.2 as a client over an established TCP socket, so
`https://` works without the browser ever touching key material. The scope
is fixed and fail-closed: no downgrade, no fallback, no session resumption.

- Handshake: `TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256` (0xC02F) and
  `TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256` (0xC02B). ClientHello carries
  SNI (the request host), the secp256r1 (23) group only and both signature
  algorithms; every message feeds the running handshake hash, and the
  server's Finished is verified before the first application byte is
  accepted. Application data is AES-128-GCM, one record = one TLS record,
  GCM tag verified before any plaintext byte is released.
- Crypto (all constant-time where it counts, no table lookups indexed by
  secret bytes): SHA-256/384, HMAC-SHA256, the TLS 1.2 PRF, AES-128-GCM
  with a GHASH that never branches on key bits, P-256 and P-384 field
  arithmetic for ECDSA verify and P-256 ECDHE, and RSA PKCS#1 v1.5 verify
  (SHA-256 and SHA-384) up to 4096-bit moduli for the chain and the
  ServerKeyExchange signature. The Montgomery multiplier's temporaries
  are sized for 128 limbs (4096-bit keys exercise the full width; the
  host suite signs vectors with a 4096-bit key so that path is covered).
  The ECDHE private scalar is rejected unless it is a valid non-zero
  scalar, so invalid-curve attacks have nothing to land on.
- Certificate chain: X.509 DER parsed from the Certificate message (up to
  4 certs, each bounded); the leaf is verified against the presented
  chain down to an embedded root, the leaf public key must match the
  handshake signature, the hostname must match a SAN `dNSName` or the
  subject CN (exact or `*.`-single-label wildcard), and the validity
  window is checked against the CMOS RTC. Any parse error, unknown
  signature algorithm, expired chain, wrong hostname or bad signature
  aborts with `freedom: tls: <stage>: <reason>` and the session is freed.
- Embedded roots (8, DER in `tls_roots_src/`, regenerated into
  `tls_roots.h` by `mkroots.sh`; the build never trusts anything outside
  the table): ISRG Root X1/X2, DigiCert Global Root G2, GlobalSign Root
  CA R3, Google Trust Services Root R1/R4, SSL.com TLS ECC/RSA Root CA
  2022. Real roots are often presented as cross-signed copies (the
  SSL.com 2022 roots are signed by Comodo AAA, ISRG X2 by X1, GTS R1 by
  GlobalSign), so the top cert is anchored by public-key equality with an
  embedded root, or by the root's key verifying the top's signature when
  the server truncates the chain at the leaf. Key equality is safe
  because every link below the top is still signature-verified.
- Session state is heap-allocated per handshake and freed on `close`; a
  socket without TLS costs nothing. Handshake reads are deadline-bounded
  (`net_recv_timeout`), so a silent peer cannot hang the shell forever.
- Client random: the kernel has no CSPRNG; the ClientRandom mixes the TSC,
  accumulated RX bytes/frames and the retransmit counters. Documented,
  not hidden.
- Syscall surface (ld stubs, MiniOS namespace like 200 = dns): 201
  `tls_handshake(fd, host)` on an already connected TCP socket, 202
  `tls_send(fd, buf, len)` (all-or-error, no partial TLS record), 203
  `tls_recv(fd, buf, len)` (decrypted application bytes; 0 = clean EOF:
  close_notify or FIN at a record boundary, truncation is reported; alert
  records are decrypted before their level/description is read, so an
  encrypted close_notify is a clean EOF and never a bogus diagnostic).
  All three validate fd and length and return -1 with a diagnostic on
  misuse.

### Headless browser (`freedom`)
`bin/freedom` is the headless text browser: a curlfree-style engine (the
host `http.c` + `htmlfilter.c` ideas) with a FreeDom-style omnibox. It is
built from `progs/src/freedom.c` through the miniGCC-to-ld chain, like `bin/cp`,
and talks to the stack through the Linux socket syscalls plus the DNS
syscall; every timeout, retransmission and EOF (0 = FIN) semantics it leans
on is already implemented in the network driver, so the program owns only
HTTP semantics.

- Omnibox (FreeDom): an argument that is not a URL is a DuckDuckGo HTML
  (no-JS) search over https; `javascript:`/`data:` (any non-http scheme) is
  searched, never executed; the User-Agent is a fixed anti-fingerprinting
  identity. Secure by Default: a bare host (no scheme) is fetched as
  `https://`. Explicit `http://` stays http: the host dev loop serves the
  BDD fixtures over plain HTTP, so the upgrade FreeDom applies to
  `http://` input is not applied here (documented deviation).
- Engine (curlfree): a header phase reads the response head into a bounded
  buffer (`FREEDOM_HDR_MAX`, sized for real-world header blocks), then the
  body is read either to `Content-Length` (never waiting for the FIN past
  the announced body) or to EOF, decoding `Transfer-Encoding: chunked`
  in place. Header names match case-insensitively. On `https://` the same
  dialogue runs over the TLS syscalls after `tls_handshake`.
- Redirects (curlfree + FreeDom policy): a 3xx with a `Location` is chased
  up to `FREEDOM_HOPS_MAX` hops. Absolute `http://` and `https://` targets
  are followed (https through the TLS syscalls); relative targets resolve
  against the current path; any other explicit scheme in a `Location` is
  refused, fail closed.
- HTML filter (htmlfilter.c): comments are skipped, `script`/`style`
  contents are suppressed, block tags (`p`, `div`, `h1`-`h6`, `li`, `tr`)
  and `br` become newlines, entities (named and numeric, decimal and hex)
  are decoded, whitespace collapses. Filter state carries across network
  chunk boundaries, so a tag or entity split between two segments is still
  decoded.
- Remote pages are hostile data (FreeDom): every byte printed to the
  console passes a UTF-8 gate that replaces bytes outside a valid sequence
  (overlong, surrogate, out of range) with `?`.
- Headless dumps (the FreeDom agent surface MiniOS can carry, no JS):
  `freedom --dump-css <url>` prints `=== freedom css ===` then every
  stylesheet the page carries — `<style>` blocks captured in document
  order, inline `style="..."` attributes as `tag#id.class { ... }` lines
  (the declaration is normalized with a trailing `;`), and
  `<link rel=stylesheet>` targets fetched (bounded count
  `FREEDOM_CSS_MAX`, each bounded bytes) and printed with their source.
  `freedom --dump-dom <url>` prints `=== freedom dom ===` then the
  element outline: one depth-indented `tag#id.class` line per element in
  document order (bounded buffer `FREEDOM_DOM_MAX`). Dump modes suppress
  the normal filtered text. Both flags validate argv and refuse unknown
  flags with a usage diagnostic.
- Diagnostics are `freedom: ...` lines; the fetch ends with
  `freedom: <host> (<n> bytes)`.
- Build: the ld stubs grew `tls_handshake`/`tls_send`/`tls_recv` (MiniOS
  syscalls 201-203), so the toolchain in `ld/ld.c` and the ramdisk binary
  must be rebuilt together; the Makefile already derives `bin/freedom`
  from `progs/src/freedom.c`. Two toolchain fixes this program leans on,
  both in the sibling checkouts: ld's `strip_comment` must ignore `#`
  inside string literals (`.asciz "#"` is the id/class separator in the
  dumps), and miniGCC must index a chained subscript on a pointer array
  (`argv[1][0]`, the flag check) with a byte load after the pointer
  element was loaded.

### Ramdisk names
File names are at most `RAMDISK_FNAME_LEN - 1` characters. Names may
contain `/`, which is how directories are expressed (`bin/cp`, `objects/ld.o`):
the ramdisk is flat, the slash is data. `mkramdisk.py` derives each name from
the path relative to the shared parent of the packed files, so
`progs/src/cp.c` ships as `src/cp.c` and `progs/bin/cp` as `bin/cp`. A name
longer than the bound or a collision between two files is a build error,
never a silent truncation that would make a lookup miss.

### Filesystem commands
A working directory (`cwd`) and directory-aware builtins, over the same flat
namespace the ramdisk names describe:

- `pwd` prints the cwd (`/` for root). `cd [dir]` changes it: bare `cd` goes
  to root, `cd ..` pops one level, anything else resolves against the current
  cwd. A directory is any ramdisk name ending in `/`; it exists when the
  exact entry exists or some file name starts with it. `cd` into a
  nonexistent directory is a diagnostic, never a silent no-op.
- `mkdir <name>` creates a directory entry: an empty file named
  `<resolved name>/`. The parent directory must already exist. Creating a
  directory that already exists is a diagnostic.
- `rm <file>` deletes a ramdisk file; a missing file is a diagnostic and a
  directory name (trailing `/`) is refused, never silently removed.
- `ls [dir]` lists the entries under a directory, defaulting to the cwd,
  names relative to it. Directory entries appear with their trailing `/`.
- `cat <file> [file...]` prints files in order; with a redirection it
  concatenates them (`cat a b > c`), which is how the MCP marketplace
  reassembles sources larger than the editor buffer.
- Path resolution is one choke point: `kfopen` and the builtins resolve a
  path against the cwd (leading `/` = root, `..` pops one component) into a
  buffer of `RAMDISK_FNAME_LEN`; a name that does not fit is rejected like
  a missing file, never truncated. `kfopen` refuses directory names, so
  `edit dir/`, `cat dir/` and redirects into a directory fail cleanly.
- `ps` lists the registered programs (name, kind, entry address).
- The prompt stays `miniOS> `: the cwd is reported by `pwd`, so the MCP
  marker wait keeps working unchanged.

### Syscall tracing
`trace` prints the current state; `trace on` / `trace off` set it (off by
default). While tracing, every Linux-ABI syscall is reported on the console
as `syscall <n>(a1, a2, a3, ...) = <result>`, so a program's dialogue with
the kernel can be watched from outside without a debugger. Three syscalls are
never traced — `SYS_TIME` (204), `SYS_KBD` (205), `SYS_MOUSE` (219) — because
they are poll/clock reads that a pacing spin loop hammers thousands of times
a second; tracing them flooded the console and made `trace on` turn an
interactive program into a 100 ms-per-syscall crawl. All other syscalls are
traced one-to-one so a short program's full dialogue stays visible. `make gdb`
boots QEMU with the gdb stub (`-s -S`) for register-level debugging;
`gdb -ex 'target remote :1234' -ex 'add-symbol-file kernel.elf 0x100000'`
attaches to the 64-bit kernel.

### Editor (`edit`)
A line editor over ramdisk files: `h l p e a i d w x q q!`. Two invariants:
- A buffer that did not hold the whole file is marked truncated and refuses
  to be written back, because saving it would drop what was never loaded.
- `q` refuses to discard unsaved changes; `q!` discards explicitly.

### PC speaker audio (`pcspk.c` + Doom)
The kernel owns the QEMU PC speaker through two syscalls: 209 `pcspk_init`
and 210 `pcspk_tone(freq)` (0 = off). The driver programs PIT channel 2
(ports 0x42/0x43, divisor `1193182/freq`) and gates the speaker on/off via
bit 1 of port 0x61; frequencies are clamped to the audible 20..20000 Hz
range and no other sound device is emulated. QEMU does **not** route the
PC speaker to the host with a bare `-audiodev`: the machine option
`-machine pc,pcspk-audiodev=<id>` is required in addition. The Makefile's
`QEMU_AUDIO` carries both (`-audiodev pa,id=snd0 -machine pc,pcspk-audiodev=snd0`).

Doom (a ring-3 Linux ELF) reaches the speaker through `i_minios_sound.c`,
selected when `snd_sfxdevice == SNDDEVICE_PCSPEAKER` and `I_InitSound(true)`
runs (it was once commented out in `d_main.c`, which left `sound_module`
NULL and every `I_StartSound` a silent no-op). Each DP lump is a PC-speaker
sequence: 2-byte big-endian priority, then pairs of (1-byte index into the
original Doom frequency table 178..2690 Hz, 1-byte duration in 70 Hz
ticks); index 0 ends the sequence. `PCSPK_StartSound` loads the lump and
starts a tone immediately, and `PCSPK_Update` (per game tic) advances
through the note sequence by elapsed time and programs the highest-priority
active channel, turning the speaker off when none remain. `S_UpdateSounds`
in `d_main.c` was re-enabled so `I_UpdateSound` actually runs each frame;
before that neither the sfx sequencer nor the music decoder was ever polled.

The level music is played over the same speaker by a
`music_pcspeaker_module` in `i_minios_sound.c`, selected when
`snd_musicdevice == SNDDEVICE_PCSPEAKER`. It decodes each MUS lump (Doom's
music format, `D_E1M1` etc.) straight from its interleaved event stream at
the stock 140 ticks/sec: a block of events at one tick ends when a
descriptor byte's bit 7 is set, then a variable-length delta leads to the
next block. The speaker is one square-wave channel, so chords are faked
with the NES pseudo-polyphony trick: the lowest sounding bass note (below
`MUS_BASS_LINE_MIDI`, midi 43) becomes a pedal held for `MUS_BASS_HOLD_MS`
like the NES triangle voice, and only the highest `MUS_ARP_MAX` melody
notes are fast-arpeggiated round-robin at `MUS_ARP_SLOT_MS` (7 ms) each by
busy-waiting on `sys_time` (the percussion channel 15 is dropped in the
decoder).  Capping the arpeggio to the top few melody notes keeps dense
arrangements from degrading into mud — every active voice is no longer
chopped at equal length, and the bass keeps its foundation instead of
getting a fraction of the cycle.  At that cadence the ear integrates the
rapid cycle into a single strummed chord instead of hearing one voice, the
classic chiptune broke-chord sound. A handle is allocated in
`MUS_RegisterSong` (validated against the `MUS\x1a`
magic and the 12-byte header), `MUS_PlaySong` resets the cursor, active
notes and chord, `MUS_Poll` advances by elapsed ms (`sys_tone`/`sys_time`
syscalls 204/210) and loops by rewinding to the score start, and
`MUS_StopSong` silences the speaker. The
`music_sdl_module`/`music_opl_module` stubs stay
all-zero; the PC speaker module is the only music source.

### Sound Blaster 16 DMA audio (`sb16.c` + piano)
The kernel owns a real PCM audio device (QEMU `-device sb16`, 8-bit mono at
`SB16_PCM_RATE` 22050 Hz through the 8237 DMA controller on channel 1) and
exposes two sinks: `sb16_tone` (square wave, the `sys_tone` sink) and
`sb16_pcm_open`/`sb16_pcm_submit` (raw 8-bit PCM streamed from a ring-3
renderer, the piano's FM synth path). The rate is programmed with the DSP 0x41
command (two frequency bytes, low then high) so the clock matches the declared
`SB16_PCM_RATE` exactly.

- **DMA completion is driven by an interrupt AND a timer watchdog.** QEMU
  raises the SB16 completion IRQ (vector 37) only once its audio engine has
  consumed the transferred block; a host backend that never consumes (a
  suspended PulseAudio stream, a full buffer, or the `none` backend) therefore
  never raises it. A driver that re-arms solely from the IRQ wedges: the
  7-slot ring fills once and every later submit is refused, deadening the
  audio. `sb16_poll`, called from the 100 Hz timer ISR, re-arms on elapsed
  guest time as a fallback, and both paths funnel through `sb16_arm`, which
  gates re-arms to at most one per `SB16_ARM_PERIOD_MS` so the two are
  idempotent and a fast backend can never drive an interrupt storm.
- **Ring accounting is guest-side**: `pcm_free` is incremented when a queued
  slot is armed, independent of whether QEMU actually consumed it, so the
  guest-side ring always drains at the declared rate.
- **Observability**: the `sb16` builtin prints presence, mode, ring free
  count and the driver counters (`irq_arms`, `poll_arms`, `submits`, `drops`),
  so ring health is testable over the serial console without ears.
- The DMA buffers live in the reserved identity-mapped low region
  `[0x90000, 0x94000)` (8 slots of 2 KB, the last is the permanent silence
  buffer); no kernel-static array is used because under KASLR the kernel
  image's physical base can land above the 16 MB the 8237 can reach.
- **Piano pacing**: `progs/piano/piano.c` renders the wall-clock time elapsed
  per frame clamped to `MAX_AUDIO_MS` (600 ms, just under the ring's ~650 ms
  capacity) instead of the old 50 ms cap, so a slow frame no longer
  under-renders and starves the ring into a choppy buzz. A fully-filled buffer
  whose submit is refused is held and retried next frame (`sb_flush`), and a
  drop is counted only when a new submit is blocked by a still-pending buffer.

## MicroPython (`micropython.elf`)
MicroPython runs inside MiniOS exactly like DOOM does: the upstream project
is cloned as a sibling repository, built on the host with the ordinary gcc
toolchain against the static glibc, and the resulting `ET_EXEC` binary ships
on MiniFS, where it runs as a ring-3 process through the Linux syscall ABI.
No MicroPython source is ever compiled by miniGCC, and nothing reaches into
the MicroPython checkout for content MiniOS owns: the port lives in this
repository as an out-of-tree unix-port variant.

- **Source**: `MICROPYTHON_DIR` (default `../micropython`), overridable like
  every toolchain location; `MICROPYTHON_URL` and the pinned release tag
  `MICROPYTHON_REF` are overridable too. `make sources` clones it with
  `--depth 1 -b $MICROPYTHON_REF`; an existing checkout is never touched.
  The shallow clone is enough: the MiniOS build needs no git submodules
  (no FFI, no SSL, no berkeley-db).
- **Variant**: `progs/micropython/variants/minios/{mpconfigvariant.h,
  mpconfigvariant.mk}` is a variant of `ports/unix` selected at build time
  through the `VARIANT_DIR` mechanism, so the upstream checkout carries no
  modifications. The configuration keeps the compiler, floats and the `os`
  module, and disables readline (the kernel console is a cooked, line-based
  device with its own echo), sockets, threading, SSL, FFI, termios, VFS
  layers and native emitters.
- **Build**: `make` builds `mpy-cross` and then the port with
  `LDFLAGS_EXTRA="-static -no-pie"`, exactly the linking contract DOOM
  follows; the ELF is copied to `progs/bin/micropython.elf` and packed into
  `minifs.bin` at its root together with the `micropython` bare-name alias,
  so it never inflates the kernel image (`< 3 MB` contract). `run
  micropython.elf`, bare `micropython.elf` and bare `micropython` all work;
  `micropython -c "expr"` evaluates, `micropython src/script.py` runs a file
  (opened through the unified fs: ramdisk first, MiniFS fallback), and bare
  `micropython` reads the interactive REPL from stdin. The process exits
  with `exit code: N` like any other program.
 - **Kernel ABI**: the binary leans on the same glibc-static stub set DOOM
   proved (`open/openat`, `read`, `write`, `brk`, `mmap`, `fstat`, ...). The
   unix port's `realpath()` of script paths needs the cwd and directory/type
   information, so the kernel implements `getcwd` (79, returns the shell
   `fs_cwd`), `newfstatat` (262, reports `S_IFREG`/`S_IFDIR` with size from
   the unified filesystem, `ENOENT` when missing) and `readlink` (89, returns
   `EINVAL` since MiniOS has no symlinks, so glibc's `realpath()` keeps
   resolving) with the same user-pointer validation as every other dispatcher
   case. Anything else the C library probes (`statx`, signals, ioctls)
   degrades through `-ENOSYS` or existing stubs, never through kernel crashes.

 - **ELF entry registers**: `k_exec_user` zeroes `rdi`, `rsi` and `rdx` before
   the `iretq` to the program entry, exactly as Linux does at `exec`. glibc's
   `_start` reads `%rdx` as `rtld_fini`; a leftover kernel value would make
   `__libc_start_main` register that garbage address as an exit handler and
   `__run_exit_handlers` would demangle and call it on exit — the historical
   MicroPython crash (`EXCEPTION 14`). This is a hard requirement for any
   ring-3 glibc binary.

- **`minios` module + `SYS_SPAWN` (215)**: the variant ships a `minios` C
    module exposing kernel services and `run()`; `SYS_SPAWN` runs a ramdisk
    program from the interpreter while preserving it (saving the user window,
    FS/GS base, fd table and brk/mmap cursors across an ET_EXEC/DYN child).
    ET_REL children (`minigcc.o`, `ld.o`) run at ring 0 and work; this drives
    `build.py`, `shell.py` and `test.py` on the ramdisk.

## Nuklear node editor (`nuklear`)

Nuklear runs inside MiniOS exactly like DOOM and MicroPython: the upstream
single-header immediate-mode UI library is cloned as a sibling repository and
built on the host with the ordinary gcc toolchain against a static libc. The
resulting ring-3 `ET_EXEC` binary ships on MiniFS and renders through the
same kernel compositing path the DOOM window uses. The demo app is a visual
node editor: a "low-code tool for the CVM" that compiles a dataflow graph
into a `.cvm` module the interpreter runs.

- **Source**: `NUKLEAR_DIR` (default `../nuklear`), overridable like every
  toolchain location, cloned by `make sources`; `NUKLEAR_URL` is overridable
  too. The build compiles `progs/nuklear/{nuklear_minios.c,node_editor.c,
  cvm_emit.c}` with `-I$(NUKLEAR_DIR)` into `progs/bin/nuklear.elf`
  (`-static -no-pie`, the same linking contract DOOM follows), plus the
  bare-name alias `progs/bin/nuklear`, both packed into MiniFS. The node
  editor's compiler lives in this repository (`progs/nuklear/cvm_emit.c`),
  never in the Nuklear checkout.
- **Platform layer (`nuklear_minios.c`)**: the app renders Nuklear's abstract
  draw commands (`nk__begin`/`nk__next`) into an 8-bit palette-indexed
  back-buffer mapped into the user window at `NK_BACKBUF_ADDR` (0x1000000,
  `NK_W`x`NK_H` = 800x360) and calls `SYS_NK_FRAME` (220); the kernel
  composites it as a titled window on the desktop, identical to the DOOM
  window, leaving the shell visible. A software rasterizer handles the full
  command set (scissor, line, rect, circle, arc, triangle, polygon, text)
  with clipping and a built-in 8x8 bitmap font. The hybrid palette keeps
  indices 0-14 exactly equal to the desktop palette (so the desktop behind
  the window is never recolored) and uses 15-255 as a UI ramp; colours are
  mapped by nearest neighbour. Input comes from `SYS_MOUSE` (219, new: x, y,
  buttons, wheel, wheel consumed on read) and raw PS/2 scancodes translated
  to Nuklear keys and unicode.
- **Node editor (`node_editor.c`)**: a canvas with draggable nodes (Number,
  Add, Sub, Mul, Div, Neg, Print, Exit), pin wiring by drag, and Compile,
  which writes `cvm/nodes.cvm` to the ramdisk through the ordinary open/write
  syscalls. Running it (bare `nuklear`, or `nuklear.elf`) opens the GUI; the
  headless modes are the serial-observable surface:
  - `nuklear --selftest` renders one UI frame through the whole graphics
    pipeline and proves it end to end: it writes a marker pixel into the
    back-buffer, calls SYS_NK_FRAME, reads the desktop framebuffer at the
    reported window origin and requires the pixel to have landed there; it
    also checks that SYS_MOUSE accepts a user pointer and rejects a kernel
    pointer with `-EFAULT`. Only then does it print
    `nuklear: frame ok (800x360)` — so a mutant that drops the composite,
    the origin reporting or the mouse bounds check is killed.
  - `nuklear --demo <out.cvm>` compiles a fixed demo graph `(2+3)*4` and
    writes the module.
  - `nuklear --compile <graph.txt> <out.cvm>` parses a simple graph
    description (`num a 2`, `add b a a`, `print p b`) and compiles it.
  A compiled module is a self-contained cvm2 file the interpreter runs with
  `run cvm/demo.cvm` (prints `20`, exit 0). The compiler (`cvm_emit.c`)
  topologically sorts the graph, detects cycles and feed-an-output-node
  errors with diagnostics, computes every node value into a local slot,
  prints through the `printf` native and exits with `OP_HALT`; division by
  zero fails closed (`cvm: runtime error: division by zero`, exit 1).
- **Syscall surface**: the kernel adds 219 (`SYS_MOUSE`: read the desktop
  mouse state into a user int[4], resetting the wheel) and 220
  (`SYS_NK_FRAME`: composite the Nuklear back-buffer as a titled window,
  optionally returning the window content origin so the app can translate
  mouse coordinates). The `NK_W`/`NK_H`/`NK_BACKBUF_ADDR` constants live in
  `vga_fb.h`; the buffer sits at the middle of the user window, far from both
  the program heap (grows up from the load base) and its mmap zone (grows
  down from the stack base). The ld stub set grew `minios_mouse`/`nk_frame`
  beside the other MiniOS syscalls.
- **CVM host fix**: the JIT encodes runtime faults (division by zero, bad
  address) as a *negative* exit code because `cvm_jit_error` only stops the
  machine, so the interpreter's host must translate `cvm_exit_code < 0` back
  into `cvm: runtime error: <reason>` with exit 1 instead of leaking a
  negative status to the shell. This lives in `cvm_host.c` `cvm_main`.

## Library integration assessments
A library lands in MiniOS only when it fits the freestanding kernel's rules
(integer-only, no POSIX, allocator and libc callbacks redirected through
macros like the stb/miniz wrappers) or runs at ring 3 as an unmodified
static ELF (DOOM, MicroPython, Nuklear). Candidates that pass are vendored;
candidates that do not are assessed honestly and documented here, never
silently forced in.

- **miniz 3.0.2** (ZIP read/write): accepted, shipped as `unzip`/`zip`
  builtins — see the Zip builtins section. Integer-only, allocator hooks, and
  the whole archive API works whole-file in memory.
- **dlmalloc 2.8.6** (kernel heap allocator): accepted, shipped as the
  backend for `kmalloc`/`kfree`/`kcalloc`/`krealloc`. See the Memory
  allocator contract below.
- **stb_truetype** (TTF rasterization): vendored, accepted for **build-time
  only**. The header is float-heavy and the kernel compiles
  `-mno-sse -mno-mmx`, so TTF can never run in the kernel; a font swap would
  rasterize glyphs on the host into an embedded bitmap atlas at build time
  (like the desktop icons). Not wired up: no font is vendored yet (a swap
  needs a redistributable TTF in-tree and a FONT_W/FONT_H resize through the
  whole terminal/taskbar/title-bar geometry), so the kernel keeps its
  embedded 8x8 CP437 bitmap font.
- **linenoise**: rejected. It is a POSIX line editor (termios, `isatty`,
  `read`); the equivalent mid-line editing feature set was implemented natively
  in the shell prompt instead (see the Shell section).
- **libgit2**: rejected as infeasible. ~400K LOC of C depending on pthreads,
  OpenSSL, POSIX `rename`/`getdents64` and the full fd/stat surface; it is
  not buildable in the freestanding kernel, and porting it would duplicate
  the network/TLS stack MiniOS already owns. Git integration, if ever wanted,
  would be a minimal custom wire-protocol client (git://, not the full
  library), not a libgit2 port. Not scheduled.

### Memory allocator contract (dlmalloc)
`kmalloc`/`kfree`/`kcalloc`/`krealloc` delegate to a private dlmalloc 2.8.6
mspace (Doug Lea, MIT-0, pristine upstream in `third_party/dlmalloc/`)
compiled into the kernel through `dlmalloc_impl.c`. The space is rooted at the
fixed kernel heap via `create_mspace_with_base(HEAP_BASE, HEAP_SIZE, 0)`, so
the 64 MB reservation is unchanged and the physical memory map is untouched.

- `ONLY_MSPACES` is set: no global `malloc`/`free` symbols are emitted, so the
  kernel's own libc stubs (`malloc`→`kmalloc`, etc., `register_libc_symbols`)
  stay the sole names the toolchain resolves against.
- `HAVE_MORECORE=0` and `HAVE_MMAP=0`: the space can **never grow past the
  fixed heap**. An exhausted heap returns 0 exactly like the first-fit
  allocator it replaced — fail closed, never a wild expansion. `time(0)` in
  the magic-seed path is mapped to a constant and `NO_MALLOC_STATS` strips the
  stdio dependency; `ABORT` is an infinite loop (internal corruption hangs the
  machine rather than proceeding); `MALLOC_FAILURE_ACTION` is empty.
- Replaces the former first-fit free-list allocator, which was O(n) per
  malloc/free and fragmented; dlmalloc brings segregated bins, coalescing and
  a lower per-allocation overhead on the same heap.
- The ring-0 selftest `objects/dlmalloc.o` (from `dlmalloc_selftest.c`, the
  same ET_REL pattern as `xxhash.o`/`stb.o`) exercises a malloc burst,
  realloc grow/shrink (verifying data copy), zeroed calloc, live-neighbour
  integrity across frees and a multi-MB allocation. BDD: `dlmalloc: ok`.

The two kernel allocator entry points that matter for isolation are unchanged:
`kallocator_init` still builds the heap once at boot, and every kmalloc path
still fails closed (returns 0) rather than faulting on an exhausted heap.

## Development Methodology (SDD + TDD + BDD)
1. **SDD**: every feature begins with a spec in this file.
2. **TDD**: add a failing scenario first, then implement.
3. **BDD**: `test_bdd.sh` boots the image in QEMU and drives the shell over
   the serial console, asserting observable behaviour.
4. **Mutation testing**: `mutate.sh` injects one-line mutations into the
   kernel and the boot path, rebuilds and runs the suite. A mutant that
   survives is a test gap and must be closed by adding a scenario, never by
   deleting the mutant.
5. **Boy Scout rule**: technical debt and security defects found on the way
   are fixed, never deferred as out of scope.

A mutant may only leave the set when it is provably *equivalent* — no input
can distinguish it from the original. That was the case for a mutant that
stopped `redirect_resume` from restoring the capture: every shell status
print is the last thing a command does, so nothing observable followed the
missed resume. It was replaced by `redirect-captures-nothing` and
`status-leaks-into-redirect`, which exercise the same contract through
effects the suite can actually see. Removing a mutant for any other reason
is forbidden; the answer to a survivor is a new scenario.

## Validation Gate (must pass before any commit)
```bash
make                # zero warnings
./test_bdd.sh       # all scenarios green
./mutate.sh         # every mutant killed (BDD + host TLS suite)
make test-tls       # host-side crypto + full-handshake suite green
python3 -m unittest -v mcp/test_minios_mcp.py   # unit + QEMU BDD green
mcp/mutate_mcp.sh                                # every MCP mutant killed
```

The TLS engine is host-tested because the BDD gate boots a machine that can
only see plain-HTTP fixtures: `make test-tls` builds `tls.c`/`tls_crypto.c`/
`tls_x509.c` against the host libc with a compile-time test root injected,
runs fixed-vector checks (SHA-256/384, AES-GCM, P-256 ECDH, RSA PKCS#1 v1.5
with 2048- and 4096-bit moduli) and then full TLS 1.2 handshakes against
OpenSSL-driven servers (RSA and ECDSA chains, a presented leaf+CA chain,
wildcard hostname matching, correct hostname), plus the negative set
(unknown CA, wrong hostname, bare-domain and two-label wildcard misses,
tampered record, expired certificate) and a close_notify clean-EOF
scenario driven by `openssl s_server` (the Python ssl server does not
send close_notify). Mutants of the TLS files are killed by that host
suite; the BDD scenarios cover the in-OS wiring fail-closed (https
against a plain-HTTP port, https redirect landing on plain HTTP), the
TCP ack-advancement contract (a fixture that holds its second half until
the guest ACKs the first) and the dump modes over the host fixture
server.

## MCP Bridge Contract

### Purpose
`mcp/minios_mcp.py` exposes MiniOS as a programmable environment over the
MCP protocol. It boots `os.img` in QEMU, drives the shell over a pty-backed
serial console, and gives an agent tools to write, compile, link and run
software inside the OS. The companion skill `skills/minios/SKILL.md` teaches
the workflow; this section is the engineering contract.

### Architecture
One file per contract, Python 3 standard library only, no dependencies.

- Transport: stdio JSON-RPC 2.0 (MCP): `initialize`, `tools/list`,
  `tools/call`, `ping`; notifications are accepted and not answered.
- QEMU is a child process owning a pty: serial console on the slave, server
  on the master. The slave runs raw (no echo, no line discipline): the
  kernel echoes input itself, so a cooked pty would duplicate every line.
- A reader thread appends console output to a bounded ring buffer (oldest
  bytes dropped, total counted). Marker waits search from a consume cursor,
  so output already seen can never satisfy a later wait.
- One QEMU child per server, guarded by a pid file (system temp dir by
  default, overridable with `MINIOS_PIDFILE`). A stale QEMU process is
  reaped on boot; the child is terminated on server exit and never left
  behind.

### Tools
| Tool | Contract |
|------|----------|
| `minios_status` | `{booted, pid, log_bytes, log_cap}`; never fails |
| `minios_boot` | spawn QEMU, wait for the `miniOS> ` prompt, return boot log; idempotent when already booted |
| `minios_snapshot` | tail of the log since the consume cursor (peek, does not consume) |
| `minios_send` | send one shell line, wait for the next prompt, return the output in between (this is how `run p.elf` reports `exit code: N`) |
| `minios_expect` | wait for a marker after the cursor; cursor advances to the end of the match |
| `minios_write` | create or replace a ramdisk file through the editor (`edit`, `a` per line, `x`); returns the editor transcript |
| `minios_cat` | print a ramdisk file |
| `minios_test` | generic scenario harness: send a list of shell commands, assert each `expect` marker appears and each `refute` marker does not in the produced output; returns `{pass, failures, transcript}`. This is the reusable in-OS test tool, so a session never hand-rolls a boot-and-assert script. |
| `minios_poweroff` | `poweroff`, wait for `powering off` and QEMU exit, release the pid file |

Every tool carries a `timeout_ms` parameter capped by a config constant; a
wait that expires is an error, never a silent hang. A caller's budget is a
budget for the whole job: boot is bounded on its own, its marker waits are
capped by the boot timeout, so a stuck prompt can never burn an install's
full budget before failing. The host shell is never invoked
(`shell=False` everywhere); the only shell driven is the one inside
MiniOS.

For host-side verification of the miniGCC-built command tools there is a
reusable harness, `tests/host_codecs.sh <progs_dir>`: it drives the static
ELF tools on the host (lzss/unlzss roundtrip + fail-closed + bidirectional
interop against the reference Okumura codec; lz4's fail-closed path; the lz4
roundtrip needs MiniOS syscalls 216/217 and is covered in-OS instead).

### Addon marketplace (lazyaddons-style)
Addons are YAML files in `addons/`, one per package, inspired by LazyOwn's
lazyaddons: metadata plus an `install` block that says where the code comes
from and how it is built *inside* the OS. The marketplace is how new
programs travel from GitHub into a running MiniOS without ever rebuilding
the image.

```yaml
name: cp
description: Command-path utility cp, rebuilt from its C source in the OS.
author: miniOS
version: "1.0.0"
install:
  repo_url: https://github.com/grisuno/miniOS.git
  files:
    - src: progs/src/cp.c
      dst: build/cp.c
  build:
    - run objects/minigcc.o build/cp.c > build/cp.s
    - run objects/ld.o -f elf -o bin/cp build/cp.s
  verify:
    - line: cp src/cp.c build/cp2.c
      exit_code: 0
```

- `minios_addons` lists the addons and whether each is installed. The
  marketplace ships `cp` and `freedom`; the freedom addon is the dogfood
  of the whole system: its source travels from git into the OS and is
  rebuilt inside the OS by miniGCC and `ld`.
- `minios_install <name>` boots the machine if needed, clones `repo_url`
  (`git clone`, `shell=False`, bounded timeout), uploads each `files` entry
  into the OS through the editor, builds with the `build` shell lines and
  asserts the `verify` exit codes. Success records the addon in the in-OS
  registry `var/lib/addons.txt` and in a host state file under the system
  temp dir; a failure at any step reports and aborts, never records a
  half-installed package, and removes its upload parts.
- Editor limits are the upload contract: a source is split into parts of at
  most 512 lines with lines shorter than 128 chars, written as
  `<dst>.partN` and reassembled one `cat` invocation per part
  (`cat <dst>.part0 > <dst>` then `cat <dst>.partN >> <dst>`), because each
  invocation contributes exactly one trailing newline, which is what joins
  the parts; the reassembled file is read back and must equal the source
  byte for byte (modulo the trailing newline). A source with a line the
  kernel readline cannot carry is rejected up front.
- The YAML dialect is a strict subset parsed by stdlib-only code (no
  PyYAML): keys are whitelisted, names bounded, `dst` paths validated like
  tool paths, build/verify lines printable ASCII. The host shell is never
  invoked; the only shell driven is the one inside MiniOS.
- `mcp/mcp_dogfood.py <addons-dir>` is the end-to-end marketplace check:
  it drives the MCP server over stdio JSON-RPC, installs `freedom` from a
  git repo into the booted OS, then browses with the installed binary
  (plain command path, no `run`).

### Validation
- `minios_write` and `minios_cat` accept file names over a strict
  character whitelist (`[A-Za-z0-9._/-]`, no leading `/`, no `..`, bounded
  length). Content lines must be printable ASCII (32..126): that is what
  the kernel readline can carry. Content is also bounded by the editor
  limits (`EDIT_LINE_MAX` chars per line, `EDIT_MAX_LINES` lines): longer
  input is rejected up front, because the kernel would truncate it
  silently. Anything invalid is rejected before a single byte reaches the
  console.
- JSON-RPC input is parsed and validated; a malformed message is answered
  with a JSON-RPC error, never an exception.
- Buffer sizes and timeouts are bounded by named constants; the reader
  thread is daemonized and the child is reaped through `atexit` and signal
  handlers so no error path leaks a QEMU process or a pty.

### Config
Defaults are named constants; the environment overrides them
(`MINIOS_IMAGE`, `QEMU`, `MINIOS_MEM`, `MINIOS_LOG_CAP`, `MINIOS_PIDFILE`,
`MINIOS_ADDON_STATE`, the timeout family). The default image path is
derived from the script's own directory, never from a host assumption.

### Tests
- `mcp/test_minios_mcp.py`: unit tests (protocol dispatch, validation,
  buffer and cursor semantics, config) plus BDD scenarios that boot the
  real image in QEMU and exercise the full edit/compile/link/run loop,
  including the self-hosted `minigcc.elf`. QEMU scenarios skip cleanly
  when QEMU or `os.img` is absent. The QEMU-backed classes fail fast:
  once a tool call has hit a console wait timeout, the bridge is stuck
  and the remaining tests are skipped instead of each burning a full
  timeout.
- `mcp/mutate_mcp.sh`: one-line mutations of `minios_mcp.py`; every mutant
  must be killed by the suite. A survivor is a test gap. Mutant suites run
  in parallel (`MUTATE_JOBS`, default 4) with a per-mutant pid file and
  addon state, so the runs stay independent; the shortened timeout family
  bounds the waits of a mutant that breaks the console.

### Skill
`skills/minios/SKILL.md` documents the workflow an agent follows: boot once,
write sources with `minios_write`, compile with `run objects/minigcc.o f.c > asm/f.s`,
link with `run objects/ld.o -f elf -o bin/f.elf asm/f.s`, run and read `exit code: N`,
power off when done. It also documents the headless browser (`freedom`,
plain command path, http only) and the addon marketplace
(`minios_addons` / `minios_install`, dogfooded by `mcp/mcp_dogfood.py`).
Extending miniGCC, `ld` or cvm/cvm2 happens on the host against the
sibling repositories (clone to a scratch dir, `make`, suites); only the
result travels into the OS.

## Code Standards
- English only, no emojis, no inline commentary; docstrings above the code
  they describe.
- Production-ready: no placeholders, no simplifications.
- Every constant named; boot-path constants live in `bootdefs.h`, kernel
  constants at the top of their subsystem.
- No absolute filesystem paths and no host assumptions in the build.

## Security Requirements (Non-Negotiable)
- Every loader input is validated before use: ELF headers, section and
  relocation bounds, ramdisk table extents and per-file ranges.
- Size arithmetic is overflow checked before allocation.
- Failure paths report and release; no silent partial state.
- No function symbol is ever resolved to a null address.
