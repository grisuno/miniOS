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
  fixed virtual `FB_ADDR` (0x0B200000), replacing the old 0xA0000 mapping. All
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
  (0x0B000000, RW, NX). DOOM renders its 320x200 frame there and calls
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

### SMP (Symmetric Multiprocessing) Foundation

The kernel brings up application processors (APs) at boot using the
standard INIT-edge/SIPI/SIPI sequence through the local APIC.  With
`-smp N` in QEMU, the BSP wakes N-1 APs; without it, the system runs
single-CPU exactly as before.

**Per-CPU data (`sched.h` + `sched.c`):** `cpu_t` stores the LAPIC ID,
`cur_pid`, `syscall_kstack`, idle flag, and BSP flag for each CPU.
`cpus[MAX_CPUS]` (max 8) is the global array; `cpu_count` tracks how many
 CPUs are online.  `this_cpu()` reads the current `cpu_t` via the GS base;
`current_pid` is a macro that expands to `this_cpu()->cur_pid`, so all
scheduler paths (isr_dispatch, schedule, yield, do_exit, do_waitpid)
automatically operate on the correct CPU's state.

**GS base per-CPU (`sched.c` + `syscall_entry` in `kernel.c`):** the BSP
sets `MSR_GSBASE` to `&cpus[0]` during `sched_init()`.  `syscall_entry`
uses `swapgs` to switch to the kernel GS base on entry and back on
`sysretq`/`klongjmp`, so ring-3 code never sees the kernel's per-CPU
data.  APs set their own GS base in `smp_ap_entry()`.

**AP bring-up (`smp.c`):** the BSP maps the local APIC at `0xFEE00000`
(uncached 2 MB in PDPT slot 3), enables the SVR, copies the flat AP
bootstrap stub (`ap_entry.S`) to `AP_STUB_ADDR` (0x6000, below 1 MB for
SIPI), patches the C entry point address, and sends INIT (edge-triggered,
all-excluding-self) followed by two SIPIs.  Each AP runs the stub (real
mode -> protected mode -> long mode), calls `smp_ap_entry()`, initializes
its `cpu_t`, sets GS base, loads the BSP's IDTR, enables its LAPIC SVR
(so it can receive IPIs) with the local timer and both LINT pins masked,
and enters the AP idle loop (`smp_ap_idle_loop`, which claims READY
CLONE_VM threads and otherwise halts).  The AP has no periodic timer of
its own by design: its only tick is the BSP's 100 Hz IPI broadcast, which
wakes the halted AP and drives its preemption ISR.  A LAPIC timer count
derived from `PIT_HZ` must never be used: the LAPIC counts bus clocks, so
that count fires ~84 kHz under QEMU and wedges the machine under an
interrupt storm (measured 2.6x slowdown + 176% host CPU on an idle guest).
The AP does NOT print to the serial console
during init: `kprintf`'s stack usage plus the LAPIC timer ISR trap frame
overflows the identity-mapped low-memory stub stack and cascading
exceptions result.  The BSP prints "SMP: Brought up N CPUs" after
`ap_count` confirms the APs initialized.

**LAPIC ICR bit layout (xAPIC):** the destination shorthand for
"all excluding self" is at bits 19:18 (`0xC0000`), NOT bits 17:16
(`0x30000`, reserved).  The INIT delivery mode is at bits 10:8 (`0x500`).
Level-assert is bit 14 (`0x4000`), level-trigger is bit 15 (`0x8000`).
QEMU 11 hangs on level-triggered INIT (delivery status never clears), so
edge-triggered INIT is used.

**ISR AP-awareness (`sched.c` `isr_dispatch`):** vector 32 (timer) checks
`this_cpu()->is_bsp` to decide whether to send PIC EOI + run `sb16_poll`
(BSP) or LAPIC EOI at `0xFEE000B0` (AP).  The context-switch path is
guarded by `is_bsp` so APs never corrupt the shared `procs[]` table.
APs do not own the PIC, the PS/2 mouse, or the SB16 DMA ring.

**GS validation in the timer ISR (`sched.c` `cpu_or_null`):** a ring-0
context running with a user/stale GS base makes `this_cpu()` read garbage
(typically the mapped IVT at linear 0), and the first field dereference
faults with #GP instead of failing safe.  The vector-32 path validates
the pointer against `cpus[]` first; on failure it EOIs both controllers
best-effort, counts `smp_dbg_bad_gs` (reported by the `smp` builtin, zero
in a healthy boot) and takes no scheduling action.  The known producer of
such a state is the `swapgs` dance in `k_exec_user`, which runs with
interrupts off from the dance through the `iretq` for exactly this
reason.

**AP stub stack (`ap_entry.S`):** the AP's temporary stack is at 0x78000
(identity-mapped low memory, below the LAPIC PD at 0x70000, above the
syscall kernel stack at 0x88000).  This is only needed until
`smp_ap_entry()` sets up the per-CPU context; the idle loop runs on this
same stack.  A stack at 0x80000 overlaps the syscall kernel stack and
causes exception cascades when the LAPIC timer ISR fires.

**BDD tests (`test_bdd.sh`):** `scenario_smp` boots with `-smp 2` and
asserts "SMP: Brought up 2 CPUs"; a single-CPU scenario asserts
"SMP: 1 CPU".  The SMP scenarios run alongside the existing suite.

**Mutation tests (`mutate.sh`):** `smp-icr-shorthand-broken` (wrong bit
position), `smp-init-missing` (no INIT before SIPI), `smp-sipi-vector-zero`
(zero vector), `smp-ap-no-lapic-eoi` (missing AP EOI), `smp-bsp-ctx-switch-not-guarded`
(AP corrupts process table), `smp-gs-base-not-set` (missing GS base).

### SMP Scaling: Per-CPU Runqueues, Futexes, Batch, RCU-Lite

Four additive contracts that remove SMP contention and trap overhead
without changing the scheduling model (1:1 CLONE_VM threads, shared
address space, non-preemptible kernel outside explicit points). All four
are host-tested (`make test-futex test-percpu-rq test-batch test-rcu`),
mutation-covered in `mutate.sh`, and wired into the ABI as version 2
(`MINIOS_ABI_VERSION`, checksum extended with the new numbers). Each
contract lives in exactly one kernel file plus a minimal header carrying
its config; cross-file layout constants stay in `progs/minios_abi.h`.

- **Futexes (`futex.h`, `kernel/futex.c`, syscalls 226/227).** A 32-bit
  user word is the key: `FUTEX_WAIT` sleeps while `*addr == val`,
  `FUTEX_WAKE` wakes up to `n` sleepers on that address. Waiters chain
  intrusively through `proc_t.wq_next` on one of `FUTEX_BUCKETS` hash
  buckets; each sleeper records its address in a pid-indexed table so
  colliding buckets wake by address only. The value check and the enqueue
  share the bucket lock, which makes lost wakeups impossible; the lock is
  released before `schedule()`. The syscall layer rejects kernel
  addresses with `-EFAULT` before entry. Userland (`progs/src/mthreads.h`)
  runs a 0/1/2-state mutex on top: uncontended acquire/release never
  trap, contention sleeps in the kernel, and an `-ENOSYS` reply degrades
  to the old spin+yield loop so old kernels keep working. BDD proof is
  the existing `thdemo` scenario, which now runs 10 threads over futex
  mutexes (`produced=1000 consumed=1000`).
- **Per-CPU runqueues + work stealing (`percpu_rq.h`,
  `kernel/percpu_rq.c`).** Every CPU owns a ring of `RQ_DEPTH` pid hints.
  `do_thread_spawn`/`do_clone(CLONE_VM)` record the child on the
  spawner's ring; the AP idle path pops local hints, attempts one
  non-blocking steal per remote ring (`spin_trylock`, never waited on),
  and only then takes `sched_lock` to validate a hint
  (`procs[pid].state == PROC_READY`, VM-only) or to run the legacy
  global scan. Hints are advisory: full rings drop (counted), stale hints
  are discarded, and an idle CPU that finds nothing skips `sched_lock`
  entirely until every `RQ_RESCAN_PERIOD` polls, which bounds staleness
  and keeps a hintless READY thread dispatchable. The BSP keeps the
  global scan (it owns non-VM processes, which are never hinted and never
  stolen). The `smp` builtin reports `rq_hits`/`rq_steals`/`rq_drops` per
  CPU; the BDD suite asserts they appear and that the AP steals during
  `thdemo`.
- **Batched submission (`batch.h`, `kernel/batch.c`, syscall 235).**
  `SYS_SUBMIT_BATCH(ops, results, count)` runs up to `BATCH_MAX_OPS`
  descriptors in one trap, in order, stopping at the first error with
  `completed` reporting the successes. Only side-effect-light,
  non-blocking, pointer-free opcodes are batchable (`NOP`, `YIELD`,
  `TIME`, `GETPID`); anything else is `BATCH_ERR_OPCODE` and stops the
  batch. The syscall wrapper validates both arrays against the user
  window, copies the descriptors into kernel memory (no TOCTOU through
  user-mutable opcodes), and copies results out. Number 235 was chosen
  because 228 is `clock_gettime` in the Linux switch.
- **RCU-lite (`rcu.h`, `kernel/rcu.c`).** Epoch grace periods over the
  existing 100 Hz ticks: readers bracket with `rcu_read_lock/unlock`
  (nesting, tracked depth per CPU) and never lock; writers publish with
  `rcu_publish` and retire with `rcu_call`; `rcu_note_tick`/`rcu_note_idle`
  feed quiescent states from the timer ISR and `rcu_poll` closes the grace
  and runs due callbacks in tick context. The callback queue is bounded
  (`RCU_CB_MAX`, full refuses with ownership kept) and `rcu_synchronize`
  is spin-bounded (`RCU_SYNC_SPINS`, expiry is `RCU_ERR_TIMEOUT`, never a
  hang). The timer ISR feeds ticks on both BSP and AP paths and polls on
  the BSP. Deliberately out of scope, as documented in the improvement
  plan: lock-free everything, kernel preemption, M:N threading and
  per-CPU allocators.

### ISR-driven desktop event loop (`sched.c` + `vga_fb.c`)

The desktop event loop (`vga_fb_mouse_tick`) must run continuously regardless
of whether the shell or a user program owns the CPU.  Historically it ran
only inside `raw_blocking_getc` (the shell's idle poll), so the desktop froze
whenever `k_exec_user` entered ring 3 for a child process.  The mouse cursor,
taskbar clock, window drag and scrollbar all stopped responding.

The fix is a timer-ISR-driven tick: the 100 Hz PIT handler (`isr_dispatch`,
vector 32) runs the registered desktop listeners through the tick bus
(`tick.h` + `kernel/tick.c`, predicate `tick_desktop_due`) at a configurable
interval (`DESKTOP_TICK_INTERVAL`, default 4 = 25 Hz) whenever
`user_program_active` is set.  The flag is set in `k_exec_user` before the `iretq` into ring 3 and
cleared after `klongjmp` returns, so the desktop ticks for the entire
 duration of any user program.  When no user program is active the flag is
 clear and the ISR skips the tick; the shell drives the desktop from its own
 idle loop as before. The tick stands apart from the preemption branch in
 the ISR: chained as an else-if it never ran while threads existed
 (`proc_count > 1` always took the preempt arm), freezing the cursor for
 whole threaded workloads, so it is an independent `if` behind the same
 predicate and flag.

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

### Tick listener bus (`tick.h` + `kernel/tick.c`)

The ISR no longer calls periodic effects directly. `sched_init` registers
two adapters, `sched_tick_audio` (forwards to `sb16_poll`) and
`sched_tick_desktop` (forwards to `vga_fb_mouse_tick`), and `isr_dispatch`
(vector 32) runs `tick_run_audio()` unconditionally on the BSP and
`tick_run_desktop()` when `tick_desktop_due(sys_ticks,
DESKTOP_TICK_INTERVAL)` and `user_program_active` hold. Call order,
gating and branch structure are unchanged; only the call path moved, so a
new periodic effect registers without editing the ISR. The bus is two
fixed tables (`TICK_MAX_AUDIO_LISTENERS` / `TICK_MAX_DESKTOP_LISTENERS`,
no heap, no locks): registration is boot-time only before `sti`,
dispatch only reads, a null or full registration returns -1 and changes
nothing, and `tick_reset` empties both lists. Host-tested (`make
test-tick`, mutation-covered); the live-boot proof is the existing SMP
(`SMP: Brought up 2 CPUs`) and sb16 scenarios, which exercise both
dispatch paths.

### Port I/O HAL (`arch/x86/hal_io.h`)

Header-only, single-file contract centralizing every port number,
controller command and device address the timer ISR path touches
(`HAL_PIC1_CMD`, `HAL_PIC1_DATA`, `HAL_PIC2_CMD`, `HAL_PIC2_DATA`,
`HAL_PIC_EOI`, `HAL_PIT_CMD`, `HAL_PIT_CH0`, `HAL_PS2_STATUS`,
`HAL_PS2_DATA`, `HAL_PS2_MOUSE_OBF`, `HAL_MOUSE_SYNC_BIT`,
`HAL_MOUSE_BUTTON_MASK`, `HAL_MOUSE_SCALE`, `HAL_MOUSE_PACKET_LEN`,
`HAL_LAPIC_EOI_ADDR`). The `hal_outb`/`hal_inb`/`hal_outw`/`hal_inw`
accessors emit the same instructions as the open-coded sites they
replaced; `hal_pic_eoi`/`hal_lapic_eoi` own the EOI sequences. No bare
port literal remains on the scheduler ISR path. Under
`HAL_IO_HOST_TEST` the accessors log to stub counters instead of
executing privileged instructions, which makes the mapping host-testable
(`make test-hal`, mutation-covered). First step of the HAL the
architecture plan calls for; further drivers migrate port by port.

### Userspace desktop architecture (design spec, future implementation)

The long-term goal is to move the desktop compositor to a ring-3 userspace
process, achieving proper separation of concerns: the kernel owns scheduling
and hardware access, the desktop process owns rendering and input routing,
and user programs run concurrently under preemptive scheduling.

**Desktop process:** a static ELF binary compiled on the host, shipped on
MiniFS as `bin/desktop`.  It runs at ring 3 through `k_exec_user` and
renders the desktop background, taskbar, terminal window, and composites
DOOM/Nuklear back-buffers.  The framebuffer is already mapped user-accessible
at `FB_ADDR` (0x0B200000), so the desktop process writes pixels directly
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

**Preemption blocker (lifted, revision 1):** the single-address-space limit
that deferred Phase 5 is gone for the `mrun` path. `pt_clone_user_empty`
builds a fresh user window per process (heap-owned data pages, graphics
slots re-shared), `load_exec_elf_into` loads segments into that window
without touching the live one, and `proc_spawn_elf` starts the result as a
non-`CLONE_VM` process through `user_trampoline` + `iretq`. The existing
machinery already did the rest: `switch_to` swaps CR3, the BSP timer
preempt swaps the per-process brk/mmap view, and `do_waitpid` reaps through
the extended `pt_free_user` (heap pages freed, identity pages and shared
graphics slots untouched). `mrun a.elf b.elf ...` runs isolated ELFs
concurrently; the BDD suite pins `mrun: pid 1 exit code: 55` beside `Hello`.
The legacy `run`/`k_exec_user` path is byte-for-byte unchanged.

### Preemptive multitasking + job control (OSDev model)
MiniOS follows the OSDev recommended model — kernel stack per task (the
16 KB `kstack_pool` slot per proc, TCB in `procs[]`, CR3 in `ctx`) with
preemptive multitasking: involuntary switches from the 100 Hz timer ISR
plus voluntary `yield()`s in every wait loop, so most switches stay
cooperative and preemption is the backstop, not the norm.

- **Background jobs:** `run p.elf &` / `mrun a b &` spawn isolated
  processes and return the prompt at once; the shell stays usable while
  jobs run (proven: `echo` answers mid-`thdemo` with its 10 futex
  threads, DOOM boots its WAD while the prompt serves). `jobs` lists
  them, `wait [pid]` reaps (blocking), `kill <pid>` terminates a real
  target (the old `do_kill` exited the caller; now the victim goes
  ZOMBIE for its parent, abandoned by the BSP/AP preempt paths so no
  corpse keeps running). Unreaped exits surface as `job done: pid N
  code: C` before the next prompt, so pid slots never leak. `wait4`
  honors `WNOHANG` with a `WAITPID_NONE` sentinel (a killed job's -1
  still reaps distinctly).
- **Per-process VMA (`vma.h`/`vma.c` + `sched.c`):** every non-`CLONE_VM`
  process owns a heap-backed `vma_ctx_t` (private 4096-node pool); the
  globals are a view rebound on each brk/mmap switch, and `brk`/`mmap`
  materialize pages via `mm_user_ensure_page` (no-op on the shared
  window). This fixed the DOOM-in-isolation #GP (fresh window over a
  stale shared tree with `VMA_NIL == NULL`). Threads share the pointer.
- **Signals, minimal and honest:** Ctrl+C kills the foreground set
  (prompt bell when there is none; `^C` + exit 130 path), Ctrl+D is EOF
  (empty line submits, non-empty bells). Semantics are SIGKILL-like:
  `rt_sigaction` stays a stub, no guest handler ever runs. Legacy
  blocking `run` never polls the console, so it ignores Ctrl+C.
- **Build discipline (pre-existing gap, now documented):** the Makefile
  tracks no header dependencies, so after touching any `.h` run `rm
  *.o && make` — a stale `kernel.o` keeps the old `PROC_T_SIZE` in the
  syscall-entry trampoline while `sched.o` moves on, and every spawned
  child hangs in its first syscall with no diagnostic.
- **Construction race closed:** a newborn slot stays `PROC_SWITCHING`
  (never claimable) until fully built; publishing `READY` early let a
  tick claim a half-built context (the 192 KB pool alloc widened that
  window to a whole tick, hanging the machine with no output).
- Honest limits remaining: one shared fd table, no `fork`/`execve`
  (`sys_linux_fork/vfork/execve` still answer 0; `mm_copy_user_page`
  waits for it), APs claim `CLONE_VM` threads only, no Alt-Tab
  mid-`edit`, serial sees one interleaved console (use `wm list`).

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
  unavailable", never a stale value. `rtc_read_date` adds the calendar side
  (CMOS 0x07-0x09, two-digit year mapped to 2000..2099, Feb 29 validated
  against the leap rule including the %400 century case) and
  `rtc_days_from_civil` converts to post-1970 days, so `gettimeofday(96)`
  and `clock_gettime(228)` report true epoch seconds (second resolution,
  usec/nsec zero). The old `gettimeofday` returned TSC milliseconds since
  boot — uptime, not an epoch — which silently broke every absolute-date
  consumer, notably the ring-3 TLS certificate window (days computed to 0,
  so no real chain ever verified in-guest). On RTC failure both syscalls
  report 0/0 and TLS fails the chain closed downstream.
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
  mute, and the `-`/`+`   buttons step the volume by `TASKBAR_VOL_STEP`. Left
  of the speaker an `EN`/`ES` label shows the keyboard layout and toggles it
  on click (`EN` US qwerty, `ES` Spanish qwerty with Latin-1 `ñ Ñ ¡ ¿ ´ ¨ ·
  ª º ç Ç ¬` glyphs in the framebuffer font; `^ ´ ` ¨` emit their spacing
  symbol, no composition; code characters live on Right Alt (AltGr) exactly
  like on real hardware — `AltGr+3` is `#`, `AltGr+2` `@`, `AltGr+`` `[`,
  `AltGr++` `]`, `AltGr+´` `{`, `AltGr+ç` `}`, `AltGr+º` `\`, `AltGr+1` `|`,
  `AltGr+4` `~`, `AltGr+6` `¬` — so ES is fully usable for code editing;
  only `€` is missing, it has no Latin-1 byte). Console input accepts
  printable Latin-1 (`kbd_is_printable`, 32..126 plus 160..255) in the
  prompt, the `edit` line reader and the terminal, so `ñ` travels from key
  to buffer to screen as one byte. Mouse hit-testing lives in `vga_fb_mouse_tick` beside the
  existing title-bar drag and scrollbar logic; there is no separate input
  path. The cursor tip is the sprite's top-left pixel, so a click lands where
  the arrow points; the IRQ12 phase guard also rejects first-byte overflow
  bits, so a stray init reply (`0xFA`/`0xAA`) can never shift the packet
  framing and warp the first motion after boot.
- **Tiling shortcuts (Alt = WM modifier, `kernel.c` + `vga_fb.c`):** the window
  is moved, snapped and resized from the keyboard for a tiling-WM feel. Alt is
  tracked as a modifier beside Shift and Ctrl. Alt+Enter toggles fullscreen,
  Alt+arrows snap the window to the left/right/top/bottom half of the screen,
  Alt+Home/End snap to the top-left / bottom-right quadrant, Alt+`[`/`]`
  shrink/grow width, Alt+`-`/`=` shrink/grow both dimensions, and Alt+0 resets
  the window to its default position and size. The window keeps its current
  size across redraws (resize/snap persist instead of snapping back to the
  default like the old layout engine).
- **Focus + tiling across windows (Alt-Tab, Super-Tab, `vga_fb.c` + `drivers/kbd.c`):**
  the focused window owns the keyboard; its title bar paints bright
  (`COL_TITLEBAR`) while unfocused terminals dim (`COL_SHADOW`) with a `*`
  marking the focused one. Alt+Tab cycles focus across EVERY window —
  present terminals plus the graphics window (`WM_FOCUS_GFX`), like
  Windows/Linux, never terminals-only; Super (E0 0x5B/0x5C, tracked as
  `kbd_super` beside Alt) + Tab tiles them all (one terminal fills it, two
  go left/right; with a graphics window the terminal(s) yield the right
  half — two stack vertically on the left — and a window too wide for the
  half goes right-aligned instead of centered). Super+arrows snap the
  focused window like Alt+arrows. Clicking an unfocused terminal raises it
  through the same select path, so mouse and keys agree. The `wm` builtin
  drives the same functions (`wm focus [next|0|1|2]`, `wm tile`, `wm list`,
  `wm state` reports `focus`/`nterms`) so the BDD suite asserts them over
  serial exactly like `date`/`vol` (including a background-DOOM scenario
  that focuses, tiles, lists and closes the gfx window); real scancodes are
  covered by QMP `input-send-event` (`alt`+`tab`, `meta_l`+`tab`) against
  `display none`.
- **Second terminal (`wm split`, `vga_fb.c` + `shell.c`):** two shells share
  one execution engine — the globals every terminal function uses always
  mirror the focused window, and `tw_park`/`tw_unpark` swap the whole window
  state (geometry, logical ring, active line, cursor) between the globals and
  the per-window slot. Window 0 keeps the historical static ring; window 1's
  64 KB ring lives on the kernel heap (a static would blow the
  `USER_LOAD_BASE` `.bss` budget). The shell parks its half-typed line per
  window (`shell_focus_park/restore` over `vga_fb_park/unpark_line`, with a
  generation counter so the readline loop adopts the incoming line instead
  of dropping the first keystroke after Alt-Tab); history and cwd stay
  shared, and running a program blocks both windows (one `exec_return`).
  While split, window 0 snapshots to the heap too: its slot borrows the
  static ring, which IS the live one, so sharing it merged both windows'
  content and aliased `tw_park`'s copy (src == dst), rotting scrollback
  once `lg_head` moved. `wm close` drops the split from any focus (typing
  it in window 0 still closes window 1, never a silent no-op), adopts the
  live ring into window 0 so no output is lost, frees both heap rings and
  re-homes window 0 on the static ring; window 0 never closes (it resets
  to default like the historical X button). An empty submit (Enter /
  Ctrl+D on a blank line) clears the window's live-prompt flag, or every
  refocus stacked another `miniOS> `.
  The dock's Terminal icon runs `wm split` (`progs/etc/shortcuts`), so a
  click opens/focuses the second shell with no typing — verified over QMP
  with separated button down/up (a joint down+up can land inside one tick
  and read as no click); a repeat click just refocuses window 1.
  Icons are never relative to the shell: `desktop_launch` (`kernel/shell.c`)
  pins the cwd to `/` while the shortcut command runs and restores it
  after (a click during a running program queues through the same path),
  so `run quake2generic.elf +set basedir .` resolves `baseq2/` at the
  root no matter where the shell sits — a wrong cwd used to kill Quake
  with `Couldn't load pics/colormap.pcx`, mimicking memory exhaustion.
  `tools/test_gui_icon_cwd.py` proves it over QMP (template-matched dock
  click from a shell sitting in `/cvm`).
  Honest limits: no Alt-Tab mid-`edit` (the modal editor echoes into
  whichever window is focused), serial sees one interleaved console (use
  `wm list`'s `line` flag to tell which window holds a parked line).
- **Focus-routed input (`vga_fb_ps2_owner`, `drivers/kbd.c` +
  `kernel/syscalls.c`):** one PS/2 keyboard feeds every window, so the
  focused window owns it — a background gfx job (`run doomgeneric.elf
  mini_autoframes 3000 &`, shell stays interactive) reads `SYS_KBD` only
  while the gfx window is focused, the shell's `kbd_read` only while a
  terminal is, and neither touches the port when unfocused, so the two
  never split the scancode stream. The serial console is the shell's own
  and is never shared: `GETC_RAW` (236) serves a background job from the
  PS/2-only source (`console_job_try/get`, never serial or the shell's
  cooked queue) and `read(0)` answers `-EAGAIN` when unfocused, so a
  polling game can never steal shell bytes; foreground runs (legacy
  `run`, `mrun` fg via `shell_fg_active`) keep the full multiplexer.
  The cursor has exactly one painter per mode: the tick owns it on the
  desktop, the present path (`blit_gfx_buf` erase-then-draw) owns it
  while a graphics program runs. Sharing the save/old state between
  the 25 Hz tick and ~60 fps presents raced every frame and stranded
  stale sprites (worst on the title-bar hitboxes the tick touches), so
  in gfx mode the tick never draws or restores and only invalidates
  across real repaints. `tools/test_gui_fashion.py` proves it over QMP
  (one arrow sprite after motion, stable idle frames, ESC quits).
  Taking the display also takes focus (`wm_gfx_focus_sync` inside
  `vga_fb_set_gfx_mode`): enabling graphics mode parks the shell line
  and focuses the graphics window with stale raw bytes flushed, so a
  gfx child spawned from another gfx app (file browser opening vedit)
  owns PS/2 from its first frame instead of looking hung while its keys
  and wheel land on the shell; disabling hands the focused terminal
  back silently. Raw mode is per-app state each program asserts at
  startup (piano/node editor/file set 1, vedit sets 0 because GETC_RAW
  starves while raw diverts PS/2 to the raw queue), and the file
  browser drops to 0 around every SPAWN so no child inherits its mode.
  A legacy foreground program owns
  everything (its shell is blocked, nobody to steal from). `kbd_read`
  always translates cooked for the shell even with the global raw mode on
  (a bg raw game used to deafen shell PS/2), and focusing the gfx window
  flushes stale raw bytes. Serial bypasses routing and stays a shell
  console at every focus. `sleep <secs>` (yield loop, Ctrl+C aborts) paces
  scripts across a booting bg job. Honest limits: one interactive gfx app
  at a time (two bg games race one port); PS/2 Ctrl+C reaches `wait` only
  with a terminal focused (serial Ctrl+C always works).
- **Window controls (title-bar buttons, `vga_fb.c`):** every titled window
  (terminal, DOOM, Nuklear) carries the classic three glyph buttons at the
  right end of its title bar — minimize (`_`), maximize (open square) and
  close (`X`) — drawn and hit-tested by the shared `wm_*` helpers. A click on
  minimize hides the terminal window (the content stays in the logical ring,
  so restoring repaints it with nothing lost); maximize toggles fullscreen;
  close restores the terminal to its default geometry because the shell
  cannot be closed. For a graphics window the buttons target the composited
  DOOM/Nuklear title bar: maximize is a no-op (the window is already display-
  sized) and   close arms `wm_close_request`, which the syscall dispatcher
  honours on the child's next syscall (`exec_exit_code = 130`, `klongjmp` on
  the child's own stack — never from the ISR), so a graphics program is
  terminated cleanly from its title-bar X. A background job has no fg exec
  frame, so its close request reaps it as `do_exit(130)` instead of stealing
  the shell's `klongjmp` target. Alt+M toggles minimize and
  Alt+X/Alt+Q close the active window. Fullscreen and minimize are mutually
  exclusive: entering one clears the other.
- **WM geometry and events (`wm_geom.h`, `wm_events.h`, `vga_fb.c`):** the
  tick no longer hardcodes title height or button edges. `wm_geom.h` owns
  every rectangle (title, content, scrollbar, clamp) through
  `wm_geom_config_t` derived once from `FONT_W`/`FONT_H`/`SCROLLBAR_W`;
  `wm_events.h` owns click/release/scroll/move translation through
  `wm_event_config_t` with a stateless pure translator plus the shared
  Alt/Super combo table (`WM_COMBOS`, `WM_SC_*`, `wm_combo_lookup`) used by
  cooked and raw paths, so Alt-Tab/Super-Tab/snap/resize can never diverge
  again and AltGr never triggers a combo. Drag grabs live at
  file scope (`wm_dragging`, `wm_gdrag`) so `tw_select` resets them on
  every focus change instead of leaking a stale grab. `wm_window.h` unifies
  terminal and graphics hit-testing plus focus rotation and paint order
  (`tw_hit` delegates, `tw_select` bounds-checks); `wm_render.h` owns the
  back-to-front composition plan (wallpaper, shortcuts, taskbar, terminals,
  graphics last); `wm_tiling.h` owns terminal cell layout (split, stack
  beside graphics, fullscreen single); `wm_focus.h` owns validated focus
  transitions (`vga_fb_focus_next`/`vga_fb_focus_id` delegate id selection
  and refuse invalid targets); `wm_layout.h` owns unified placement across
  `tile`/`bsp`/`cascade`/`fibonacci`/`fullscreen` (`wm_layout_compute`,
  `wm_layout_same`, `wm_layout_fullscreen_cell`, config
  `wm_layout_config_t`, spec `docs/wm_layout_spec.md`, manifest
  `docs/wm_layout_manifest.md` via `tools/wm_layout_sync.py`). Host contract is
  `make test-wm`; mutation gate covers title height, containment edges,
  click/release confusion, paint and layer order, tiling splits (odd
  widths included), bsp/cascade/fibonacci cells, fullscreen uniformity,
  plan-equality and null/degenerate fail-closed.
- **WM inside games (raw scancodes, `drivers/kbd.c`):** DOOM/Quake/Nuklear/
  piano read raw Set-1 scancodes through `SYS_KBD` (205), bypassing the
  cooked translation where Alt-Tab lives — so the WM used to die the moment
  a game owned the keyboard. `raw_track_mods`/`wm_raw_combo` (shared core)
  intercept on both raw paths (`kbd_read`'s raw branch and
  `kbd_sys_raw_filter` for the direct-port syscall read): Alt+Tab focuses,
  Super+Tab tiles, Super+arrows/Home/End snap, Alt+Enter/M/X/Q/`[`/`]`/`-`/
  `=`/`0` act, and a swallowed Tab make swallows its break too. The table is
  the single source: `wm_combo_dispatch` in `drivers/kbd.c` serves cooked,
  raw-fill and `SYS_KBD` paths, Alt+arrows stay cooked-only by path mask.
  Clicking a graphics body focuses it (`gfx_hit` over `wm_window_contains`,
  not title-only) and wheel/scroll act only when a terminal is focused.
  `SYS_MOUSE` snapshots atomically under IRQ save and honors `ps2_owner`,
  so an unfocused reader gets `-1` instead of leaked coordinates. `ps2_owner`
  validates `0 <= pid < MAX_PROCS` and `sched.h` owns `user_program_active`.
  Both blits share `blit_gfx_buf` under `GFX_TITLE_DEFAULT`, so DOOM/Nuklear
  titles always come from `SYS_GFX_SET_TITLE`. `wm state` also reports
  `kbd drops cooked/raw`. Bare keys
  always reach the game, and Alt+arrows stay with the game (DOOM strafes
  with them); Super is never a game key, so it carries the full set raw.
  The `SYS_KBD` path holds back the `0xE0` prefix while Alt/Super is held
  (no stray prefix wedges a game's key pump) and modifiers are tracked raw,
  so nothing sticks across `kbd_reset_for_shell` (which now clears every
  modifier, not just Super/AltGr). `vga_fb_tile_all` parks a fitting gfx
  window (DOOM 320px) on the right half beside the terminal(s); a full-size
  one (Nuklear/vedit 800px) stays centered. Honest limits: legacy blocking
  `run` still blocks the shell (type in a terminal while a fg game runs
  needs `run game &` + preempt), and one keyboard feeds both a bg game and
  the shell — WM combos are consumed, the rest reaches both.
- **Minimize/restore (`wm` builtin):** while the terminal is minimized the
  window is not drawn and the taskbar shows a `[]` restore button on the far
  left. The mouse tick ignores wheel/drag/scrollbar while minimized. The `wm`
  builtin (`wm state`, `wm minimize`, `wm maximize`, `wm close`) drives the
  same functions as the buttons and shortcuts and reports state over the
  serial console, so the BDD suite asserts the WM behaviour exactly like
  `date`/`vol`/`kbd`/`gfx`.
- **Layout modes (`wm layout`, `wm_layout.h`):** `tile` keeps the legacy
  dual split exactly (odd remainder goes right, like `wm_tiling.h`);
  `bsp` splits recursively alternating axes; `cascade` offsets by config
  steps; `fibonacci` carves integer-ratio strips; `fullscreen` fills focus.
  `wm layout [tile|bsp|cascade|fibonacci|cycle]` sets it, `wm state`
  reports `wm: layout <name>`, Alt+Enter stays uniform (terminal fills
  cells, gfx recenters native), and `vga_fb_tile_all` skips the redraw
  when `wm_layout_same` proves the plan unchanged, which removes the
  drag/tile flicker without touching the rasterizer.
- **Persistent graphics layer (`gfx_keep_*`, `vga_fb.c`):** every desktop
  redraw wipes the whole framebuffer, which used to bury any program that
  only composites on input — vedit/Nuklear sit blocked in `read` with no
  next frame coming, so Alt+Tab made the window vanish until the next
  keypress, with no way back. Both blits now save the finished window
  (title + content, cursor excluded) into a fixed heap buffer sized for the
  largest window, allocated once and never freed (no alloc/free races with
  the ISR tick, dims invalidate on mode-on), and `draw_desktop` re-blits it
  on top after the terminals at the current WM offset. A save racing a
  restore tears one cosmetic frame; all copies clamp.
- **Taskbar running-app button (`taskbar_render`, click):** while a graphics
  program owns the display the taskbar shows a small button right after the
  restore slot: the app's own 32x32 desktop icon downsampled to the 8px row
  plus its title, bright when focused. The icon resolves through
  `etc/shortcuts` (never a hardcoded list): `vga_fb_set_gfx_program`
  records the compositor — the shell's launch name for foreground runs,
  `procs[current_pid].name` attributed per frame for background jobs, so it
  is always whoever is actually on screen — and matches it against each
  shortcut's command binary (`run quake2generic.elf +set basedir .` matches
  `quake2generic.elf`); the window title against the shortcut name is the
  fallback (case-insensitive, `*` suffix ignored), text-only when nothing
  matches. This is why every app sets its title at startup (Nuklear, Piano
  and vedit call `SYS_GFX_SET_TITLE`; DOOM keeps the default): title-less
  programs all read "DOOM" and shared one icon. Clicking the button focuses
  the graphics window, which redraws it on top through the persistent layer
  — a buried app is always reachable. `wm list` reports it as
  `win gfxbtn x=.. w=.. icon|text` for the BDD pin.
- **Desktop art sources (`tools/gen_desktop_pngs.py` vs `gen_icons.py`):**
  custom art (wallpaper + per-app icons) converts from user PNGs at the
  repo root, pixel art (terminal) generates procedurally; the sets are
  disjoint by Makefile rule. Pokemon ships the root `pokemon.png` Pikachu
  (32x32 RGBA like every icon), never the old generated pokeball.
- **GUI proof (`tools/test_gui_wm.py`):** serial `wm` commands share the
  functions but not the reality (blocking reads, frame timing), so the WM
  is also proven headless over QMP: real Alt+Tab/Super-Tab scancodes with
  vedit in the foreground, judged on pixels (vedit painted, identical after
  Alt+Tab, still painted after tile), then a background vedit whose taskbar
  button is clicked through a real relative-mouse walk, asserting serial
  `focus 2`. Serial goes over a unix socket (pipes make QEMU block-buffer
  stdout; sends are paced ~20ms for the 16-byte 16550 FIFO), stdin is held
  open (EOF exits QEMU), RAM is 1G (256M dies silently), and in practice
  QMP +y moves the cursor down.
- **Shell surface:** `date` prints `HH:MM:SS` from `rtc_read_tod` (a failed
  read prints a diagnostic); `vol [0-100]` prints the volume and, with an
  argument, sets it after strict decimal parsing and clamping; `kbd [en|es]`
  prints the keyboard layout and, with an argument, sets it (`toggle`
  switches). This is the
  TDD hook: the BDD suite asserts `date`, `vol` and `kbd` through the serial console.

## Kernel Contracts

### Single source of truth for the memory layout (`progs/minios_abi.h`)
The user-window layout — load base, stack, brk cap, the graphics back-buffers,
the linear framebuffer and the kernel heap — is defined **once** in
`progs/minios_abi.h`, the header shared by the kernel and every ring-3 program.
The kernel derives its own constants from it (`kernel.h` -> `kernel.c`
`USER_LOAD_*`/`USER_STACK_*`/`HEAP_*`, `vga_fb.h` `FB_ADDR`/`DOOM_BACKBUF_ADDR`/
`NK_BACKBUF_ADDR`, `sched.c`), so growing the window or moving a back-buffer is
a one-line edit in one file instead of a cross-file address hunt. This is the
direct fix for the historical bug where moving an address (DOOM's back-buffer
`0x7C00000 -> 0x0B000000`, the user-window growth) left a consumer writing the
old value and silently breaking. Belt and suspenders: `_Static_assert`s in
`kernel.c` prove the kernel's values equal the ABI header, and the asm-safe
`USER_WIN_LO`/`USER_WIN_HI` syscall-return mirrors are checked too. **Rule: never
hardcode a layout address in the kernel or a ring-3 program; put it in
`minios_abi.h`.** The scheduler's old local `MY_USER_STACK_TOP` (`0x07400000`)
is gone — it went stale when the window grew and would have stacked a scheduled
process in the middle of the heap.

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
registered with a null address. Section header arithmetic uses the
overflow-safe pattern `sh_offset > size || sh_size > size - sh_offset` to
prevent unsigned wrap from bypassing the bounds check.

### Integer overflow protection
`kfread` and `kfwrite` compute `size * n` before accessing the buffer.
A ring-3 program passing `size=0xFFFFFFFF, n=2` would cause the product
to wrap to `0xFFFFFFFE`, smaller than the intended allocation, bypassing
the `bytes > RD_DATA_MAX` check. Both functions now reject the call when
`n != 0 && size > ULONG_MAX / n`, returning 0 before any buffer access.
The early-return also covers `size == 0` and `n == 0`, which the old code
handled implicitly through division-by-zero or zero-length loops.

### Stack setup bounds checking
`setup_user_stack` writes argv strings downward from the stack top. Without
a bounds check, a program with many large argv entries could write below
`sbase` and corrupt kernel memory before the user window. Each iteration now
checks `l > (p - sbase)` and returns NULL on overflow. `k_exec_user` checks
the return value and refuses to enter ring 3 with a NULL stack pointer.

### Syscall argument sanitization (`sanitize.h`)
Every MiniOS handler takes user pointers only through the `SANITIZE_*`
macros (range, string, non-negative length, and copy-in with an explicit
count-by-size wrap check), which all fail closed with `EFAULT` (-14). The
audit that motivated them found five handlers returning `-EFAULT` (+14,
which userland reads as success) and open-coded multiplications a hostile
count could wrap past the range check; both classes are gone where the
macros apply. `SANITIZE_COPY_IN` copies into kernel memory before use, so
userland cannot mutate an array between validation and execution (no
TOCTOU). The macros name only `user_range_ok`/`user_str_ok`/`kmemcpy`/
`EFAULT` and are host-tested (`make test-sanitize`, mutation-covered);
`grep SANITIZE_` lists every sanitized entry point. Boundary rule:
sanitize at the boundary, trust internally. Region-typed validation (heap
vs stack vs mmap) is deliberately deferred: the VMA tree tracks mmap
regions only, and futex/batch words legitimately live in any writable
region, so a single-type check would need a region-mask redesign plus
tagging at load/brk/stack setup first.

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
on a user stack and never touches the user red zone. The return path
discriminates on the caller RIP, never on RSP: RSP is attacker-settable
without faulting while RIP is constrained to executable mappings, so an
`RSP=0` spoof takes the `sysretq` path instead of retaining CPL0 through
`jmp *%rcx` (ring-0 ET_REL callers trap from heap code and keep the `jmp`
return). The entry range-checks the pid (`jae 98f`, fail closed with
`-EFAULT` touching no memory), so a corrupt `cur_pid` can neither index
`sc_top_save` out of bounds nor swap onto a wild kstack. The exit path
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
Up arrow (ESC `[` `A`, or PS/2 make code `E0 48`) recalls the newest older
command starting with the typed prefix (zsh `history-beginning-search`);
down arrow (ESC `[` `B`, `E0 50`) moves forward again, back to the live
line. An empty line matches every entry, i.e. plain chronological recall.
Right arrow at end of line accepts the suggestion outright: it completes
the line to the newest history entry starting with the prefix (a plain
cursor move there would be a no-op, so nothing is lost). The recalled text
replaces the line the user was typing, which is preserved while scrolling.
The history stores commands on submission (even unknown ones), skips
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
grow the registered-program table. The relocated image is freed when the
run returns (`elf_load` reports its base, `run`/`SPAWN` release it), so
repeated compiles do not bleed the heap: ten vedit builds cost no more
than one. The exit code is reported exactly as
`run` reports it; an unresolvable name falls through to
`command not found` (bare) or `run: not found` (with `run`). `objects/`
and `cvm/` are never on the bare command path — only registered programs,
the current directory, and the suffix-driven `bin/` lookup answer a bare
name, so the command path stays root-anchored and an attacker can never
run an arbitrary `.o` as a command by name alone.

TAB completes the current word from history, builtins, registered programs
and ramdisk file names: one TAB fills the longest unambiguous prefix, a
second TAB on a unique match fills the whole name, and an ambiguous prefix
lists the candidates. Completion repaints the line in place (never a stray
newline) with the cursor at the end, so the submitted command always
matches what is on screen. On the first word the newest history commands
complete too (deduplicated first tokens, most recent first), then the
builtin names, so TAB after `minigcc` offers the most recent matching
command and TAB after `pw` offers `pwd`. A bare first word (no `/`)
completes runnable-first across the ramdisk and the MiniFS root (where the
big ELFs live under bare names): the `.elf` tier, then `.cvm`, then `.o`,
and only the highest-priority non-empty tier is kept, so `poke` offers
`pokemon.elf` instead of its icon PNG. An explicit path or an argument word
keeps every match, so navigating to data files still works. The completion
is bounds-checked and never writes past the command buffer.

Terminal scrollback is a 256-line logical ring (`SB_MAX_LINES` in
`vga_fb.h`): a completed line is pushed whole on `\n` and the viewport is
repainted from the ring, so old lines scroll off the top and stay reachable
through the scrollbar/mouse-wheel (`disp_off`). A push that evicts the
oldest line always fully renders: comparing row counts alone would take the
active-line-only fast path (the count is unchanged by an eviction) and
freeze the screen with only the bottom line repainting. Blank viewport rows
are explicitly cleared, never left with stale pixels.

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

The stack is split into two contracts: the polled NIC driver
(`net/rtl8139.{c,h}`) and the protocol stack (`net/net.c`).  The driver
owns the port I/O, PCI probe, TX descriptors, the receive ring, the NIC
MAC and the PIT-calibrated clock; the stack owns addressing, ARP/IP/
UDP/DNS/ICMP/TCP, the sockets and the demux (`net_rx_handle_frame`) that
the driver reaches through `rtl_poll`.  `rtl8139.h` is the boundary:
`rtl_send`, `rtl_poll`, `rtl_present`, `rtl_get_mac`, `rtl_iobase`,
`rtl_counters`; the shared aggregate RX drop counter (`net_rx_dropped`,
declared in `net.h`) is incremented by both sides (bad frames in the
driver, dropped fragments in the stack).

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

### TLS client (userspace: tlsget/freedom over net/tls*.c)
TLS 1.2 left ring 0 (`net/tls*.c` never link into the image; 201/203
always answer `-ENOSYS` and 202 serves Linux `futex(2)`). The same sources compile
unchanged with `-DTLS_RING3` into `tlsget`/`freedom`, so `https://`
works without the kernel ever touching key material. The engine spec
below describes the shared sources, not kernel code. The scope
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
  misuse. Retired: the engine left ring 0 for good, so 201/203 always
  answer `-ENOSYS` and 202 serves Linux `futex(2)` instead (`__NR_futex`
  collides with the old TLS_SEND number; glibc's NPTL aborts without a
  real futex there). Fossil miniGCC binaries still trap all three and
  fail closed. The supported path is `tlsget`/`freedom`, which link the
  same engine in ring 3 and never trap 201-203. Multi-fetch processes
  must close through `tls_close` (frees the fd-keyed session), never raw
  `close`, or the next fetch reuses the recycled fd onto a live slot.

### Headless browser (`freedom`)
`bin/freedom` is the headless text browser: a curlfree-style engine (the
host `http.c` + `htmlfilter.c` ideas) with a FreeDom-style omnibox. It is
built from `progs/src/freedom.c` with the host toolchain linked against
the shared ring-3 TLS engine (`tlsget`/`freedom3` sources), so `https://`
works with no TLS in the kernel; `bin/freedom-mini` is the miniGCC-to-ld
twin of the same source (http only: miniGCC cannot compile the
struct-heavy TLS engine), kept as toolchain dogfood. Both talk to the
stack through the Linux socket syscalls plus the DNS
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
  dialogue runs over the ring-3 TLS engine after `tls_handshake`; a failed
  handshake fails closed with
  `freedom: https handshake with <host> failed` (BDD-pinned against a
  plain-HTTP port), with no key material crossing ring 0.
- Redirects (curlfree + FreeDom policy): a 3xx with a `Location` is chased
  up to `FREEDOM_HOPS_MAX` hops. Absolute `http://` and `https://` targets
  are followed (https through the ring-3 TLS engine); relative targets resolve
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
  syscalls 201-203, now `-ENOSYS` on a default kernel), so the toolchain
  in `ld/ld.c` and the ramdisk binary must be rebuilt together; the
  Makefile derives `bin/freedom` (host gcc + ring-3 TLS) and
  `bin/freedom-mini` (miniGCC-to-ld, http only) from `progs/src/freedom.c`.
  Two toolchain fixes this program leans on,
  both in the sibling checkouts: ld's `strip_comment` must ignore `#`
  inside string literals (`.asciz "#"` is the id/class separator in the
  dumps), and miniGCC must index a chained subscript on a pointer array
  (`argv[1][0]`, the flag check) with a byte load after the pointer
  element was loaded.

### FreeDom Wayland layer (`freedom_wl`)
`bin/freedom_wl` is the Wayland-to-MiniOS intermediate layer for FreeDom,
the same role `doomgeneric_minios.c` plays for DOOM, and a complete
graphical browser in one file (`progs/src/freedom_wl.c`): the FreeDom
omnibox policy, HTTP/1.0 fetch over the socket syscalls with DNS from
syscall 200 and https through the shared ring-3 TLS engine (no key
material crosses ring 0, exactly like `bin/freedom`), redirect chasing,
chunked decoding, an HTML-to-text filter over a 100x45 layout on the
shared 8x8 font (`progs/nuklear/font8x8.c`, one copy linked by every
NK-window program through `NUKLEAR_PLATFORM`), and an input loop with
keyboard and wheel scroll. A Wayland surface becomes the Nuklear
back-buffer window (`MINIOS_NK_W`x`MINIOS_NK_H`), present routes through
`GFX_PRESENT` with `BUF_NK`, title through `GFX_SET_TITLE`, pointer through
`SYS_MOUSE`, keyboard through `SYS_KBD`. Keysyms translate from PS/2 Set 1,
dirty rects clamp to the surface, UTF-8 sanitizes fail-closed. The browser
uploads its 768-byte graphics palette through `SYS_PALETTE` before every
present (indices 0-14 match the desktop palette, the rest mirror the Nuklear
hybrid ramp), so the terminal-style page stays visible on true-color VBE modes
instead of rendering black on black through the kernel gray-ramp default.
Every tunable
lives in `FreedomWlConfig`, every address comes from `minios_abi.h`, no
absolute paths. `FREEDOM_DIR` (`../FreeDom`, fifth sibling repo) is cloned by
`make sources` and never touched when present. MiniFS grows to 768 MB
(`MINIFS_BLOCKS` 196608) for browser assets and fonts; the growth is
disk-only and moves no memory address. Proof: `make test-freedom-wl` (host),
`freedom_wl --selftest` prints `freedom_wl: frame ok (800x360)` (BDD),
`freedom_wl --once <url>` fetches and presents with `freedom_wl: <host>
(<n> bytes)` (live boot: README is 3193 bytes and `gfx frames` climbs 0 to
1; `google.com` chases to `www.google.com` over real TLS and renders whole
at 83 KB against the 256 KB body cap), five mutants (clip, https port,
title, keysym, uname) die in `mutate.sh`, plus the palette-bg mutant dies
in the host suite (`palette bg terminal`).
See ADR-0019.

### Real FreeDom browser (`freedomui`)
`bin/freedomui` is the real FreeDom engine on MiniOS, built exactly like
DOOM and Quake 2: host gcc `-static -no-pie` links the engine core
(`url`, `link_nav`, `html_parse` over Lexbor, `ui_layout`) from the
sibling `../FreeDom` checkout with the platform layer
`progs/freedomui/freedomui_minios.c`, and the ELF ships on MiniFS. Every
Wayland and Cairo call is replaced in that one file: the NK back-buffer
window is the surface, `GFX_PRESENT` with `BUF_NK` presents, `GFX_SET_TITLE`
titles, `SYS_MOUSE`/`SYS_KBD` feed input, `SYS_PALETTE` uploads the hybrid
palette before every present (same table as Nuklear, so no black window on
true-color VBE), `SYS_TIME` paces, `VGA_MODE` claims the display, and fetch
runs over the socket syscalls with DNS plus the ring-3 TLS engine. Parsing
goes through `hp_parse` with secure defaults and layout through
`ui_wrap_text`, so what renders is engine output, not a rewritten filter.
Out of scope for v1: JS, images, video, sandbox confinement, persistence.
Build is conditional (`FREEDOMUI_AVAILABLE`, sibling plus static Lexbor)
like `Q2G_AVAILABLE`. Proof: `make test-freedomui` (host, omnibox plus
Lexbor parse plus wrap), `freedomui --selftest` prints
`freedomui: frame ok (800x360)` (BDD), `freedomui --once <url>` fetches and
presents with `freedomui: <host> (<n> bytes, <m> elems)` (live boot proves
`gfx frames` climbs 0 to 1), two mutants (palette-bg, omnibox-kind) die in
`mutate.sh`.
See ADR-0021.

### Ramdisk names
File names are at most `RAMDISK_FNAME_LEN - 1` characters. Names may
contain `/`, which is how directories are expressed (`bin/cp`, `objects/ld.o`):
the ramdisk is flat, the slash is data. `mkramdisk.py` derives each name from
the path relative to the shared parent of the packed files, so
`progs/src/cp.c` ships as `src/cp.c` and `progs/bin/cp` as `bin/cp`. A name
longer than the bound or a collision between two files is a build error,
never a silent truncation that would make a lookup miss.

### Filesystem commands
A working directory (`cwd`) and directory-aware builtins, over a merged view
of the ramdisk (flat namespace) and MiniFS (real directory-capable filesystem
on the IDE disk):

- `pwd` prints the cwd (`/` for root). `cd [dir]` changes it: bare `cd` goes
  to root, `cd ..` pops one level, anything else resolves against the current
  cwd. A directory is any ramdisk name ending in `/` **or** a MiniFS directory
  (checked via `minifs_resolve_path` + `MINIFS_S_IFDIR`). `cd` into a
  nonexistent directory is a diagnostic, never a silent no-op.
- `mkdir <name>` creates a directory entry: an empty file named
  `<resolved name>/`. The parent directory must already exist. Creating a
  directory that already exists is a diagnostic.
- `rm <file>` deletes a ramdisk file; a missing file is a diagnostic and a
  directory name (trailing `/`) is refused, never silently removed.
- `ls [dir]` lists the entries under a directory, defaulting to the cwd,
  names relative to it. At root, both ramdisk and MiniFS entries are shown
  (merged view). In subdirectories, ramdisk entries take priority; when the
  ramdisk has none for that path, MiniFS entries are shown. Directory entries
  appear with their trailing `/`.
- `cat <file> [file...]` prints files in order; with a redirection it
  concatenates them (`cat a b > c`), which is how the MCP marketplace
  reassembles sources larger than the editor buffer. File I/O (`kfopen`)
  checks the ramdisk first, then falls back to MiniFS, so `cat asm/_t.s`
  works even though `asm/` lives only on MiniFS.
- Path resolution is one choke point: `kfopen` and the builtins resolve a
  path against the cwd (leading `/` = root, `..` pops one component) into a
  buffer of `RAMDISK_FNAME_LEN`; a name that does not fit is rejected like
  a missing file, never truncated. `kfopen` refuses directory names, so
  `edit dir/`, `cat dir/` and redirects into a directory fail cleanly.
- **Write fallback to MiniFS (`kfopen`)**: a write (`w`/`a`) goes to the
  ramdisk only when the flat namespace can host it (the parent directory entry
  exists there). When it cannot — e.g. `run objects/minigcc.o p.c > asm/_t.s`
  or a program writing `tmp/...`, neither of which has a parent on the ramdisk
  — `kfopen` falls back to MiniFS, the real directory-capable filesystem,
  auto-creating the parent chain with `minifs_mkdir_p` and creating the file
  with `minifs_create`. This is what fixed the lua and MicroPython in-OS test
  suites: before it, the "refuse to create a ramdisk file when its parent is
  missing" rule silently dropped every redirect into a non-ramdisk directory,
  so `ld` could not open the freshly compiled `_t.s`. MiniFS-backed writes
  flush through `minifs_write`, and `kfclose` calls `minifs_sync` so the block/
  inode bitmaps stay consistent across reboots. `fstat`/`access`/`unlink`
  report and operate on MiniFS-backed files too.
  A latent bug in `minifs_write` (minifs.c) surfaced when this path became
  reachable: after `minifs_inode_alloc_block` mapped a fresh block into the
  *local* inode struct, an `fs_read_inode` reload wiped that mapping (the inode
  is only persisted by the `fs_write_inode` at the end of the function), so the
  data landed in a block the on-disk inode never referenced and the file read
  back as zeros. The reload was removed; the block pointer now survives to the
  end-of-function inode write.
  The ramdisk half of the parent check is ramdisk-only on purpose: the old
  code asked `fs_dir_exists` (either filesystem) but always created on the
  ramdisk, so the second and later files under a MiniFS-only directory were
  captured by volatile ramdisk and vanished on reboot (the parent test also
  appended a second `/`, which could never match a ramdisk prefix at all).
  `saves/` is the persistent user-data directory by convention (Pokemon
  battery + savestates); rebuilding the images preserves it (see below).
- **Image rebuilds preserve `saves/`**: `make minifs.bin` and `make os.img`
  extract the live `saves/` tree out of the previous `os.img`
  (`tools/minifs_saves.py`, byte-exact, fail-closed on compressed or
  double-indirect files, which the guest write path never produces) and pack
  it back into the fresh image via `mkfs.minifs.py`, so a rebuild never wipes
  runtime saves. The `os.img` rule refreshes `minifs.bin` the same way because
  a kernel-only rebuild re-embeds it and would otherwise clobber the live
  partition with the stale artifact. Not even `make clean` loses saves:
  it snapshots them to `saves-backup/` first (no-op when there is nothing
  to save), and the image rules reseed from there when `os.img` has
  nothing to carry forward — so clean + rebuild restores the partida
  byte-identical. `saves-backup/` is gitignored; copy it elsewhere for
  off-machine backup.
- `ps` lists the live process table (`pid ppid state name` from `procs[]`,
  snapshot under `sched_lock` then printed after release, so console I/O
  never runs with the scheduler lock held). `jobs` lists the shell's live
  children, `wait [pid]` reaps, `kill <pid>` terminates a real target.
- `mem` reports heap use/free (dlmalloc), ramdisk use/cap/max, MiniFS free
  blocks/inodes and live process count: the first thing to read when a
  load stops loading, before blaming the game.
- `kstack` reports kernel-stack health: per-proc high-water marks plus the
  legacy 32 KB syscall stack, ending in `kstack: ok` (or `OVERFLOW`). Every
  pool slot is paint-filled at claim time with a canary word at its bottom
  (`sched.c`), so a stack that overruns into its neighbour's slot is
  detected instead of corrupting silently; the legacy slot paints at
  `sched_init`. BDD asserts `kstack: ok` after boot and after a threaded
  run. This is the instrument for the historical intermittent black-screen
  class (a fault with no recovery halts the machine with no serial after
  the banner): the next black screen gets a `kstack` reading first instead
  of a guess.
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
A command-driven line editor over ramdisk/MiniFS files, in its own contract
`kernel/editor.c` (header `editor.h`), extracted from the shell.  The core
commands are `h l p e a i d w x q q!`; on top of them it carries a
nano-style status — `g N` go to line, `n`/`b` next/previous, `.` current,
`/ text` search, `=` status, and `l [a [b]]` range listing — and marks a
modified buffer with a `*` in the prompt and a truncated one with `!`.  Text
entry for `e`/`a`/`i` reuses the shell's arrow-key line reader
(`shell_readline_buf`, exported via `shell.h`), so editing a line has the
same mid-line cursor behaviour as the prompt.  Two invariants:
- A buffer that did not hold the whole file is marked truncated and refuses
  to be written back, because saving it would drop what was never loaded.
- `q` refuses to discard unsaved changes; `q!` discards explicitly.

### Mini IDE (`vedit`, ring 3, Nuklear)
`bin/vedit` is the fullscreen visual editor, deliberately a user-space
program, never kernel code: the kernel image ends ~1 KB below
`USER_LOAD_BASE`, so a 14 KB in-kernel visual editor overflowed the user
window and killed the boot (measured `_kernel_end 0x403220`). The editor
lives in `progs/vedit/vedit.c`, is built on the host like the piano and
the node editor (static ELF, shared `nuklear_minios.c` platform layer),
and ships on MiniFS (`vedit.elf` plus the bare-name alias, source
beside it).

- Interaction: arrow-key navigation with in-place typing (no line
  numbers to name), Enter splits with auto-indent, Tab inserts a stop,
  Backspace/Delete erase and join, Home/End/PgUp/PgDn jump, `^O`/`^S`
  save, `^N` save-as, `^W` find (wraps once), `^G` goto line, `^R`
  build/run by extension, `^L` link (prompts `elf|cvm`), `^X`
  save+quit, Esc quit without saving, `^D` dumps the buffer with ANSI
  highlight to the console (serial fallback and BDD hook; moved from
  `^L` so the linker owns `^L`). Save/Find/Name/Run/Link/Done are also
  clickable buttons; the wheel scrolls by moving the cursor (the old
  code moved only the viewport offset, which the cursor-follow pass
  snapped straight back, so wheeling long files did nothing). A
  512-line / 127-char buffer
  with the same fail-closed rules as `edit`: full lines, overflowing
  joins and full buffers refuse whole, and a truncated load refuses
  to save and to build. The frame loop polls instead of blocking on a
  key (8 ms pacing like the node editor) so wheel and mouse drain every
  frame; the ESC `[` decoder is a cross-frame state machine with a
  100 ms timeout, degrading to a bare Esc instead of hanging.
- Build/run (`^R`, `^L`, single-file contract in `progs/vedit/vedit.c`):
  `^R` saves then routes by extension through `SYS_SPAWN` (215) so the
  IDE survives the child: `.c`/`.h`/`.s` compile with
  `objects/minigcc.o <file>` redirected to `asm/<base>.s`, `.lua` runs
  with `lua <file>`, `.py` runs with `micropython <file>`; `^L`
  prompts `link elf/cvm: ` and links `asm/<base>.s` with
  `objects/ld.o -f <fmt> -o bin/<base>.elf|cvm/<base>.cvm`, then runs
  the freshly linked artifact (`cvm.o` for a `.cvm`, the ELF directly)
  so its output lands on the console without leaving the IDE. Every
  build drops `SYS_VGA_MODE` first so the desktop terminal stays
  ordered and the toolchain log lands on the console, then resumes the
  IDE and reports the exit code in the status row. `mrun` stays the
  shell-level multitask path (`mrun vedit.elf &` tiles the IDE beside
  the terminal with Super+Tab); in-IDE builds use synchronous `SPAWN`
  because `mrun` is a shell builtin, not a syscall. All bounds, keys,
  tools, directories and formats live in the centralized `VEDIT_*`
  config. The tool and artifact paths are root-anchored (`/objects/`*,
  `/asm/`, `/bin/`, `/cvm/`), never host paths, so editing a file in a
  subdirectory (`cd src`) still resolves the toolchain and outputs at
  the system root instead of under the cwd.
- Highlighting: C (`.c`/`.h`/`.s`, with `//` and `/* */` plus `#`
  directives; also the default for `untitled` until a name with an
  extension is given), MicroPython (`.py`, with `#` and triple-quoted strings)
  and Lua (`.lua`, with `--`, `--[[ ]]` blocks and `[[ ]]` strings);
  keywords, strings, comments, numbers and directives each get an ink,
  drawn as per-token runs on the canvas with a block cursor.
- Plumbing: every platform fact comes from `minios_abi.h` or a
  syscall, never a literal. Keystrokes arrive through syscall 236
  `GETC_RAW` (0 polls with `-1` when idle for the bounded ESC-sequence
  wait, nonzero blocks), the same serial+PS/2 multiplexer the console
  reads but with no line buffering, echo or scrollback detour, so
  PgUp/PgDn reach the editor; the PS/2 driver reports Ctrl+letter as
  control codes and Delete as `ESC [ 3 ~`, so both consoles drive every
  key. The app owns the display through `SYS_VGA_MODE` exactly like the
  piano, the window title carries the dirty `*`, and the kernel redraws
  the desktop on exit. `vedit --selftest` renders one frame and proves
  the composite landed, mirroring the Nuklear selftest.
  `vedit --selftest-build` checks the headless build contract (untitled
  defaults to C, extension routing, base/path joins, `elf|cvm` parsing,
  `^R`/`^L`/`^D` shortcuts) and prints `vedit: build ok`; the BDD suite
  pins it and `make test-vedit` locks the same vectors on the host
  (including a `t_lang_of` mirror of `vedit_lang_of`, so spec drift fails
  the build). The scanner shares `vedit_parse_string`/`vedit_parse_number`
  (C-only quote flag)/`vedit_parse_keyword` helpers; per-language quirks
  (C `#`/`/* */`, Python triple-quote, Lua long brackets) stay in the caller.
- The kernel `edit` stays: scripted flows (the MCP `minios_write`
  editor upload, the marketplace, the BDD suite) drive it
  non-interactively, which a fullscreen program cannot serve.

### File browser (`file`, ring 3, Nuklear)
`bin/file` is the graphical file browser, a ring-3 Nuklear app built like
vedit (host gcc `-static`, MiniFS with a bare-name alias, source beside
it at `progs/file/file.c`, one file per contract with a centralized
config). It lists the unified filesystem (ramdisk first, MiniFS fallback)
through the DIR_LIST syscall (241, `MINIOS_SYS_DIR_LIST`), which fills a
user buffer with NUL-separated names (dirs carry `/`) and returns the
count, fail closed on bad pointers, overlong names and truncation.

- Dispatch comes from `etc/association` (plain `ext|program` lines, the
  same shape as `etc/shortcuts`): text kinds (`c h s txt py sh lua html`)
  open in `/vedit` through `SYS_SPAWN`, `o|elf|cvm` run through `shell`
  semantics (ELF/o spawned directly, cvm through `/objects/cvm.o` with
  the module as `argv[0]`), `png|internal` decodes in-app with stb_image
  and blits downscaled into the NK back-buffer after rasterize. Unknown
  kinds report instead of running. Assoc parsing is fail closed: only
  `[a-z0-9]` exts, programs are absolute paths or `shell`/`internal`, and
  a `|` inside the program rejects the line.
- The dock carries `File|icons/file.png|file` beside a Terminal shortcut
  that now uses the custom `icons/shell.png` art; both PNGs convert from
  the repo-root `file.png`/`shell.png` sources through
  `tools/gen_desktop_pngs.py` like every other icon.
- Proof: `file --selftest` runs the assoc vectors plus a live `/`
  listing (`file: ok (N entries at /, theme dark)`, BDD-pinned), and
  `make test-file` locks the same parser vectors on the host.
- Every NK app quits the same way: ESC or Alt+F4 through the platform
  latch (`nk_quit_requested` in `nuklear_minios.c`, polled per frame)
  plus an on-canvas Quit control (file's `quit` button, piano's `Quit`
  pad, the node editor's existing Quit; vedit already exits on Esc/^X).
  No window depends on the title-bar X alone.

### Paint program (`paint`, ring 3, Nuklear)
`bin/paint` is the canvas paint program, a ring-3 Nuklear app built like
the file browser (host gcc `-static`, MiniFS with a bare-name alias,
source beside it at `progs/paint/paint.c`, one file per contract with a
centralized config). The canvas is 320x200 palette indices blitted into
the NK back-buffer after rasterize (the file-preview pattern); the widget
bounds from `nk_widget` are the single source for both the blit offset
and mouse hit-testing, so no screen coordinate is hardcoded. There is no
GLFW or OpenGL anywhere: MiniOS has no GPU stack, only the 8-bit
composited back-buffer, so the desktop GLFW demo layout does not apply.

- Tools: brush, line, rect, circle, fill and eraser with sizes 1/2/4; a
  16-swatch picker drawn from exact hybrid-palette entries (black, the 14
  saturated accents, white), so a saved PNG reloads pixel-identical
  (nearest-mapping ties resolve to an identical RGB, never a wrong
  color). Shape tools rubber-band from a 64 KB backup copy taken at
  stroke start. The status row always shows tool, swatch, size and the
  last file result.
- PNG save/load is self-contained: the writer emits 8-bit truecolor PNG
  with stored-deflate blocks, CRC-32 and Adler-32 (no third-party encoder
  dependency; `stb_image_write` is not vendored), and the reader decodes
  through stb_image and nearest-maps onto the hybrid palette, top-left
  clamped with white margins. Paths go through a fail-closed gate
  (printable ASCII, bounded, `.png` suffix, no `..` traversal).
- The dock carries `Paint|icons/paint.png|paint`; the icon converts from
  the repo-root `paint.png` source through `tools/gen_desktop_pngs.py`
  like every other icon. `paint <file>` opens the GUI preloading that
  file; the title `Paint` matches the shortcut name for the taskbar icon.
- Proof: `paint --selftest` runs the core vectors, a 2x2 encode/decode
  roundtrip (`paint: png ok`), a save/load roundtrip through the unified
  filesystem (`paint: file ok (/paint_selftest.png)`) and one composited
  frame (`paint: frame ok (800x360)`), all BDD-pinned; `make test-paint`
  locks the mirror vectors plus the PNG byte-layout pin (192278 bytes
  for the canvas) on the host. The frame probe scans the whole
  framebuffer for a unique 4-pixel pattern instead of trusting the window
  origin report, so it holds in any video mode (an 8-bit exact check
  would fail where the origin report is stale, which the nuklear origin
  check does on a truecolor fallback boot). Present and scan retry up
  to three times with no serial output in between: a print takes
  milliseconds over serial and opens windows for the 25 Hz desktop tick
  between them.
- Interactive strokes (drag painting) have no headless proof by
  construction; the hit-testing shares the blit rect by construction, so
  a landed blit implies aligned input.

### Nuklear themes (`nuklear_theme`, all NK apps)
`progs/nuklear/nuklear_theme.c` (header `nuklear_theme.h`) is the one
theme loader every NK app links through `NUKLEAR_PLATFORM` (file,
nuklear, piano, vedit): each calls `nk_theme_apply(&ctx, 0)` after
`nk_init_fixed`, which resolves `/etc/themes/current` (else `dark`),
loads `/etc/themes/<name>` over a compiled-in fallback and pushes the
32 colors via `nk_style_from_table`. A theme file is `key r g b` lines
(the key list is the `NK_THEME_KEY_LIST` X-macro shared with
`tests/test_theme.c`, so no copy can drift); shipped values sit on the
6x6x6 cube (multiples of 51) so the 8-bit backend maps them exactly
instead of nearest-neighbour. Fail closed: unknown keys skipped,
numbers clamped, overlong lines drained, bad names fall back to `dark`.
Switching is a write to `current` (`echo light > etc/themes/current`)
and a relaunch; no reboot, no rebuild. The taskbar shows the active
name left of EN/ES (bright, `TASKBAR_THEME_CH` wide, `TASKBAR_PAD`
breathing room like every other widget since the crowding fix) and a
click cycles `etc/themes/` in ramdisk order with wraparound, writing
the choice back; `wm state` reports it as `wm: theme <name>` (BDD-pinned)
so the widget is serial-observable. Proof: `file --selftest` prints
the active theme name (BDD pins `theme dark`), `make test-theme` pins
the contract plus all five shipped files (`dark light amber forest
slate`, 32 keys each, unique, palette-exact, `current` naming an
existing file).

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
- **Idle ticks never mix**: `sb16_pump` returns before `sb16_mix_all` when
  no stream holds data (the arm path already plays the permanent silence
  slot on underrun), so a silent machine pays no 100 Hz mixing tax; and the
  mixer walks each stream with a wrapping index instead of a per-sample
  modulo, the same sample sequence with no division in the hot loop.
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
  under-renders and starves the ring into a choppy buzz. The backlog is
  paced at `PIANO_FRAME_MS` (15 ms, under one ~93 ms DMA buffer) per frame
  with the remainder kept as debt for the frames after, so a stall drains
  over several frames instead of one giant catch-up render spiking the CPU
  and halving the mouse poll rate — identical total audio, bounded
  worst-case frame cost. A fully-filled buffer
  whose submit is refused is held and retried next frame (`sb_flush`), and a
  drop is counted only when a new submit is blocked by a still-pending buffer.
  The frame loop yields (`SYS_SCHED_YIELD`) instead of busy-spinning 8 ms,
  so input polling stays fresh while audio renders.
- **Piano keyboard**: three octaves C4..B6 (middle-C base, 21 white + 15
  black keys fitting the 800 px window) clickable with velocity, plus a
  PC-keyboard MIDI layer Fruity Loops style fed by a raw-scancode hook in
  `nuklear_minios` (`nk_set_scancode_hook`): A-row whites, Q-row blacks,
  Z-row bass whites, digits aliasing the upper blacks, comma/period for
  octave shift. Each scancode owns its voice (`sc_chan`) so chords and
  melodies are playable; the pressed mouse key is latched so releasing
  off-key cannot stick a voice.

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
    program from the interpreter while preserving it.  ET_REL children
    (`minigcc.o`, `ld.o`) run at ring 0 through `k_run_rel`; ET_EXEC/ET_DYN
    children run in a fresh isolated window via `proc_spawn_elf` (the same
    path `mrun` uses) and the caller blocks in `do_waitpid`, so the parent
    address space, FS/GS base, fd table and brk/mmap cursors are untouched.
    This drives `build.py`, `shell.py` and `test.py` on the ramdisk.  The
    exec frame's kernel stack is `EXEC_KSTACK_SZ` (64 KB, `kernel/exec.c`):
    it must hold a ring-0 toolchain child's deep recursion (minigcc/ld), and
    a child that overflowed the old 32 KB stack wrote into adjacent kernel-heap
    page tables, making the parent's `pt_free_user` spin on the corruption.

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
  back-buffer mapped into the user window at `NK_BACKBUF_ADDR` (0x0B400000,
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

## Quake 2 (quake2generic)

Quake 2 runs inside MiniOS exactly like DOOM: the upstream quake2generic
engine is cloned as a sibling checkout, built on the host with the ordinary
gcc toolchain against the static glibc, and the resulting `ET_EXEC` binary
ships on MiniFS, where it runs as a ring-3 process through the Linux syscall
ABI. The software renderer produces an 8-bit paletted framebuffer that
reuses the DOOM back-buffer infrastructure unchanged.

### Platform layer (`q2generic_minios.c`)

The platform layer lives at `progs/quake2generic/q2generic_minios.c` and
implements the quake2generic interface:

- **Video**: `SWimp_SetMode` sets `vid.buffer` to the DOOM back-buffer
  address (`DOOM_BACKBUF_ADDR`, 0x0B000000) and `vid.rowbytes` to 320.
  `SWimp_EndFrame` calls `SYS_DOOM_FRAME` (211) to composite the 320x200
  buffer onto the desktop as a titled window. The window title is set to
  "Quake 2" via `SYS_Q2G_SET_TITLE` (223) at startup.
- **Palette**: `SWimp_SetPalette` converts the engine's 256-entry RGBA
  quads (1024 bytes) to the 768-byte VGA DAC format and uploads via
  `SYS_PALETTE` (206) on the next frame.
- **Input**: PS/2 Set 1 scancodes are translated to Quake 2 keycodes
  (from `client/keys.h`) and queued through `Quake2_SendKey`. Mouse deltas
  come from `SYS_MOUSE` (219).
- **Timing**: `QG_Milliseconds` returns PIT-calibrated milliseconds via
  `SYS_TIME` (204).

### Audio

Sound is stubbed: `SNDDMA_Init` returns false, all other `SNDDMA_*` are
no-ops. The engine runs silently. This matches the DOOM PC speaker approach
before the speaker driver is enabled. The SB16 PCM path (syscalls 221/222)
could be wired in the future.

### Memory constraints

Quake 2 needs ~16-24 MB at runtime (Zone + Hunk allocations for PAK files,
BSP, models). The user window provides 184 MB (`0x400000` to `0x0C000000`),
with ~17 MB available via `brk`/`mmap` after the ELF loads. The 320x200
back-buffer (64 KB) sits in the DOOM infrastructure at `0x0B000000`, below
the 1 MB stack at the top of the user window.

### Data files

The engine requires `baseq2/pak0.pak` (shareware: ~18 MB). MiniFS supports
subdirectories, so the PAK file is packed at `baseq2/pak0.pak` in the
filesystem image. The engine searches for `basedir/baseq2/pak0.pak`; with
`+set basedir .` at launch it finds the file at the MiniFS root.

### Build

```makefile
make progs/bin/quake2generic.elf
```

The binary ships on MiniFS (not the ramdisk, same as DOOM) via
`MINIFS_Q2G_FILES`. Run inside the OS:

```
miniOS> run bin/quake2generic.elf +set basedir .
```

### Syscall surface

The kernel adds 223 (`SYS_Q2G_SET_TITLE`: copy a user string into the
graphics window title buffer so the desktop compositing shows "Quake 2"
instead of "DOOM"). All other infrastructure is reused: `SYS_DOOM_FRAME`
(211), `SYS_PALETTE` (206), `SYS_KBD` (205), `SYS_KBD_RAW` (207),
`SYS_VGA_MODE` (208), `SYS_TIME` (204), `SYS_MOUSE` (219).

### BDD

The BDD scenario `quake2generic binary exists on minifs` verifies the ELF
ships on MiniFS. A full gameplay test requires the PAK file and is not
automated in the serial-console BDD suite (same as DOOM).

## Headless "it actually plays" harness (`tools/boot_run.sh`)

A one-off manual check should not hand-roll a QEMU launch. `tools/boot_run.sh`
boots `os.img`, drives the shell over the serial console with an ordered list
of commands, and captures the full transcript to a log:

```
tools/boot_run.sh "cmd1" "cmd2" ... [--timeout N] [--log FILE]
```

It sends `poweroff` after the commands, so a healthy guest exits on its own and
the script returns 0; a hang hits the `--timeout` safety net and exits 124.
A stale guest is reaped first so the image write lock is never held across
runs. Examples:

```
tools/boot_run.sh "lua src/test.lua"
tools/boot_run.sh "gfx frames" "run doomgeneric.elf mini_autoframes 150" "gfx frames"
tools/boot_run.sh "gfx frames" \
  "run bin/quake2generic.elf +set basedir . +set minios_autoframes 400" "gfx frames"
```

### Proving a game renders, not merely launches

A game that just starts (or exists) is not proof it *plays*. The kernel counts
every frame a ring-3 graphics program composites through `SYS_DOOM_FRAME` /
`SYS_NK_FRAME` (`gfx_frames_composited`, incremented in
`vga_fb_blit_gfx_window`/`vga_fb_blit_nk_window`), and the `gfx frames` shell
builtin reports it over the serial console. So the BDD-style check is: read the
counter, run the game, read the counter again, assert it climbed.

Both engines expose a headless autoquit so the shell regains control and the
counter can be read afterwards — a game that never exits cannot be queried from
the single-threaded shell:

- **DOOM**: `run doomgeneric.elf mini_autoframes 150` renders 150 frames of
  the attract loop and then `exit(0)`s. The bundled `DOOM1.WAD` demos are an
  older version (`read 108, expected 109`), so DOOM's `-timedemo`/`-playdemo`
  skip the demo and the game then faults headless; the autoquit path avoids the
  demo entirely and still exercises the full render pipeline. `mini_autoframes`
  is parsed from `myargv` in `DG_Init` (`progs/doomgeneric/doomgeneric_minios.c`).
- **Quake 2**: `run bin/quake2generic.elf +set basedir . +set minios_autoframes 400`
  renders 400 frames and calls `Sys_Quit()` (`progs/quake2generic/q2generic_minios.c`,
  parsed from argv in `main`).

Both default to normal interactive play when the argument is absent. Also, the
MiniOS build of DOOM's `I_Error` now calls `exit(-1)` instead of
`while(true){}`, so a fatal error (e.g. a missing WAD) terminates the process
and returns to the shell instead of hanging the whole machine.

Note that Quake 2's demo (`+map demo1`) needs a `baseq2/pak0.pak` that carries
`demo1.bsp`; the shareware pak does not, so without it Q2G renders the loading
screen/console rather than a live map, but the frame count still climbs and the
autoquit still returns cleanly.

### One-boot comprehensive test (`src/test_all.sh`)

`sh src/test_all.sh` runs the full non-interactive test suite inside a single
QEMU boot.  Every command prints a `PASS:` marker; the host runner greps the
serial log for these markers.  The script ships on the ramdisk (`progs/src/`)
and is added to both `PROGS` and `MINIFS_FILES` in the Makefile.

Categories tested (68 PASS):
- **Boot/help**: boot banner, help, clear
- **Filesystem**: ls (root, objects, bin), mkdir, cd, pwd, rm, cp
- **Redirects**: `>` and `>>`
- **Builtins**: echo, date, vol (set/report/reset), kbd (report/es/en), ps, trace, net, gfx, wm, hash
- **Toolchain**: minigcc.o compile, ld.o link, run ELF, run CVM
- **Bare names**: ld.o, .elf, .cvm without `run` prefix
- **Self-host**: minigcc.elf compiles, ld.o links, run
- **Codecs**: lzss/lz4/aes roundtrips, error cases
- **JSON**: validate and query
- **ZIP**: hostile archive (traversal refused), host-produced archive
- **ELF programs**: lxhello, cpl, kmem, nx, mmreuse
- **CVM modules**: fib, w1
- **Selftests**: xxhash.o, dlmalloc.o
- **Heap stability**: repeated CVM runs
- **Tracing**: trace on/off during cp

Usage from host:
```bash
tools/boot_run.sh "sh src/test_all.sh" --timeout 120
strings boot_run.log | grep -c 'PASS:'   # expect 64
```

### In-OS test suites (Lua / MicroPython toolchain)

`lua src/test.lua` and `micropython src/test.py` run the self-hosted
toolchain from inside the machine via `minios.run()` (SYS_SPAWN). The
minigcc/ld steps now work because file writes fall back to MiniFS (see the
filesystem section): a redirect or program write into `asm/_t.s` or `tmp/...`
creates the parent directory on the real filesystem instead of being refused by
the flat ramdisk. Both files ship on the **ramdisk** (`src/test.lua` and
`src/test.py`), so `ls` shows them next to the other `src/` scripts; test.lua
is also packed onto MiniFS. The suites are fail-safe, never crashing: every
`minios.run()` result is formatted through `tostring`/`str`, so a spawn that
returns `nil` reports a clean FAIL instead of aborting the script.

The ET_EXEC tool tests (`json`, `lzss`, `lz4`, `aes`, `freedom`, and running
the freshly built `_t.elf`) used to report FAIL with `exit=nil`: SYS_SPAWN of
an ET_EXEC child from inside an interpreter was a limitation of the legacy
shared-window route (swap_out + `k_exec_user` re-cloned the boot page tables,
discarding the freshly loaded image). SYS_SPAWN's ET_EXEC/ET_DYN branch now
uses the same isolated path `mrun` does: `proc_spawn_elf` builds the child in
a fresh user window with its own CR3 and `user_trampoline` entry, and the
caller blocks in `do_waitpid` until it exits. The parent is left byte-for-byte
intact, so a ring-3 interpreter (lua, micropython, the vedit IDE) can spawn
ET_EXEC children; the interpreter suites cover the module bindings, the
filesystem and the **ET_REL** toolchain (minigcc/ld work), and the ET_EXEC
tools stay exercised at the shell level by `tools/test_codecs.sh`, which
drives the real `lzss`/`unlzss`, `lz4`/`unlz4` and `aes`/`unaes` roundtrips
through the serial console (pass=3 in the gate).

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

Known drift (open): `mutate.sh` references each mutant's source by path, and
the decomposition moved code into subdirectories AND from `kernel.c` into
`shell.c`/`syscalls.c`/`vga_fb.c`/`redirect.c`. The subdirectory path drift
(`arch/x86/boot/`, `net/`, `drivers/`, `fs/`) is fixed in this contract; the
remaining `kernel.c`→`shell.c`/`syscalls.c`/`vga_fb.c`/`redirect.c` mutant
anchors (rm/mkdir/cd/cat/ps/trace/editor/append/vol/nk/write-pointer-check)
are stale and report BROKEN until re-anchored — tracked separately, not a
regression of this release.

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
make lint           # cppcheck + -Wextra (ring-3) + clang-tidy curated + bash -n + abi-numbers, all green
sh src/test_all.sh  # one-boot comprehensive non-interactive suite (68 PASS)
./test_bdd.sh       # all scenarios green (full interactive suite)
python3 tools/test_gui_wm.py  # QMP pixel proof: gfx survives Alt+Tab/tile, taskbar button refocuses
python3 tools/test_gui_icon_cwd.py  # QMP pixel proof: dock launch ignores shell cwd
python3 tools/test_gui_fashion.py  # QMP pixel proof: one cursor, stable frames, ESC quit
./tools/test_codecs.sh   # lzss/lz4/aes roundtrips (pass=3)
./mutate.sh         # every mutant killed (BDD + host TLS + host VMA suites)
make test-tls       # host-side crypto + full-handshake suite green
make test-vma       # host-side VMA red-black tree suite green
make test-freedom-wl  # Wayland-to-MiniOS mapping suite green (ADR-0019)
make test-freedomui   # real FreeDom engine backend suite green (ADR-0021)
make test-futex test-percpu-rq test-batch test-rcu  # SMP scaling contracts green
make test-sanitize  # syscall sanitize-macro suite green
make test-tick test-hal  # tick bus + HAL port-mapping suites green
make test-driver test-sync  # device registry + sync/PI suites green
make test-rtc        # RTC civil-date math suite green
make test-vedit      # vedit IDE build-contract suite green
make test-file       # file browser assoc-contract suite green
make test-paint      # paint canvas/PNG-contract suite green
make test-theme      # shared Nuklear theme suite green
make test-wm         # WM geometry + event translator suite green
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
  rebuilt inside the OS by miniGCC and `ld` as `bin/freedom-mini` (the
  http-only twin; https needs the host-built `freedom`).
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

## Tools Doctrine
Every helper that survives a session lives in `tools/` as a reusable
contract, never as a scratch file. I build each tool self-contained in one
file per contract, DRY and SOLID, production-ready with no placeholders and
no simplifications, secure by default, with an adhoc architecture for its
problem and no hardcoded values or magic numbers: every tunable lives in a
central config class. I write each tool in English without emojis and without
inline comments, using docstrings above the code they describe, with no
absolute paths from any machine and no host assumptions. I document every
tool with its purpose, usage, inputs, outputs and failure modes so a future
session reuses it instead of rebuilding it, and I keep `tools/` free of
single-use garbage: a script that cannot be reused does not land there. I
scope tests and mutations to touched files between runs (`tools/wm_scoped.sh`
pattern); I run `mutate.sh` and `test_bdd.sh` complete only at the end of a
todo list because the full suites take hours. I debug fast from inside MiniOS
with `trace on` followed by `sh src/test_all.sh`, `micropython src/test.py`
or `lua src/test.lua`, adding cases there when they prove behavior faster
than a host reboot.

## Architectural Abstractions

### VFS (Virtual File System)
A registration-based filesystem dispatch layer (implementation in kernel.c).
Filesystem drivers register a prefix and a set of operations (`vfs_ops_t`).
The VFS layer dispatches open/read/write to the registered driver based on
path prefix matching.  Two drivers are registered at boot: ramdisk (always
available) and MiniFS (registered when the IDE disk is found and mounted).
The KFILE struct carries a `vfs_file_t *vfs` pointer for future VFS-backed
dispatch; the existing direct ramdisk/MiniFS paths remain for backward
compatibility.  New filesystem additions (FAT32, EXT2) register a prefix
and implement `vfs_ops_t` without touching the kernel core.

### VMA (Virtual Memory Areas)
A red-black tree for mmap tracking, implemented in its own contract
`vma.c` with the single header `vma.h` (previously inlined in `loader.c`
against an unwired, divergent `vma.h`).  Replaces the former flat
`mmap_used`/`mmap_free` arrays with O(log n) insert/find/delete.  Two
trees: `vma_live_root` for active allocations, `vma_free_root` for
reclaimed regions.  A static node pool (`VMA_MAX` = 4096) backs both
trees and is reset by `vma_tree_init` on every exec; a pool that is
exhausted fails closed (returns `VMA_NIL`), never overruns.  The mmap
syscall (9) searches the free tree for reusable regions before carving
fresh space from the cursor; munmap (11) moves the freed region to the
free tree.  The SPAWN syscall saves and restores the entire VMA pool and
tree roots so child mutations do not corrupt the parent state.

The tree is integer-only and free of kernel dependencies, so it is
host-tested by `tests/test_vma.c` (`make test-vma`), which asserts the
red-black invariants (root black, no double-red, equal black height,
in-order uniqueness) across insert/find/delete, pool exhaustion and full
drain.  That suite exposed and fixed a latent CLRS-conformance bug: the
two-child delete case restored the successor's color
(`y->red = y_orig_red`) instead of the deleted node's color
(`y->red = z->red`), which unbalanced black height (reproducible with
eight nodes).  Mutation coverage lives in `mutate.sh` (`vma-*` mutants,
routed to the host test, no QEMU boot).

Known growth area (pre-existing, documented): a deleted node's slot is
not recycled into the pool, so a single process is bounded to `VMA_MAX`
total tree operations before `vma_tree_init` resets the pool on the next
exec; this matches the single-address-space model and the working-set
tests the suite drives.

### Unified Audio API
A hardware-agnostic audio interface (`audio.h`, implementation in
`progs/src/audio.c`) providing tone mode (PC speaker square wave) and
PCM streaming mode (SB16 DMA).  Ring-3 programs use these wrappers instead
of raw syscalls.  The kernel dispatches to the appropriate hardware backend.

### Quake 2 Decoupling
The `SYS_Q2G_SET_TITLE` syscall is renamed to `SYS_GFX_SET_TITLE` (generic
window title).  The Q2G build is conditional: skipped when the upstream
checkout is absent (`Q2G_AVAILABLE` flag in Makefile).  The kernel contains
no Quake-2-specific logic; all Q2G coupling lives in the platform layer
(`progs/quake2generic/q2generic_minios.c`) and the Makefile.

## Security Requirements (Non-Negotiable)
- Every loader input is validated before use: ELF headers, section and
  relocation bounds, ramdisk table extents and per-file ranges.
- Size arithmetic is overflow checked before allocation.
- Failure paths report and release; no silent partial state.
- No function symbol is ever resolved to a null address.
- `size * n` in file I/O is checked for integer overflow before multiplication.
- Stack setup for user programs validates that argv writes stay within bounds.

## Unified Architectural Improvement Plan

See `ARCHITECTURE_PLAN.md` for the future-work plan and `docs/adr/` for
the decided record (ADR-0001..0013, the source of truth for *why*;
`docs/vma-complexity.md` proves the VMA bound).  This section documents the
implemented changes and the contracts they establish.

### ABI Versioning (Phase 1.1)

`progs/minios_abi.h` carries `MINIOS_ABI_VERSION` (monotonic integer) and
`MINIOS_ABI_CHECKSUM` (XOR-fold of all layout constants).  Any backwards-
incompatible change to layout constants or syscall numbers must bump the
version.  The checksum is computed at compile time from the constants
themselves, so it changes automatically when any constant changes.

Build-time drift prevention: `kernel.c` contains `_Static_assert` macros that
verify the kernel's derived constants equal the ABI header values.  Ring-3
programs include the same header, so both sides pick up changes on rebuild.

### Canonical Syscall Table (Phase 3.1)

`progs/minios_abi.h` is the single source of truth for all syscall numbers.
The table is organized as:
- 0-199: Linux ABI compatible syscalls (read, write, brk, mmap, ...)
- 200-299: MiniOS custom syscalls (networking, audio, graphics, ...)
- 300+: Reserved for future use

All runtime bindings (Lua `minios.c`, MicroPython `minios_module.c`, DOOM
`doomgeneric_minios.c`, Nuklear `nuklear_minios.c`, Quake 2
`q2generic_minios.c`, OPL3 `opl3.c`, SB16 `sbtone.c`, piano `piano.c`)
must reference the `MINIOS_SYS_*` constants instead of defining their own.
Compatibility aliases (`SYS_TIME_MS`, `SYS_PALETTE`, etc.) are provided
for backward compatibility but new code should use the canonical names.

### SMP Synchronization (Phase 1.3)

`spinlock.h` provides a lightweight xchg-based spinlock with two acquisition
modes:
- `spin_lock` / `spin_unlock`: disables interrupts on acquire, re-enables on
  release. Safe for ISR context or single-level critical sections.
- `spin_lock_irqsave` / `spin_unlock_irqrestore`: saves RFLAGS.IF before
  disabling, restores the saved state on release. Safe for nested critical
  sections where the outer lock has IF=0.

`spin_trylock` attempts acquisition without modifying interrupts.

`sched_lock` protects the shared process table (`procs[]`), `proc_count`,
and scheduler state. `smp_lock` protects the AP counter and LAPIC registers.
Per-CPU data (current PID on each core, per-CPU stacks) needs no lock.
The lock primitives are in place for when SMP scheduling is enabled; currently
APs idle in an hlt loop.

### Kernel Decomposition (Phase 1.4)

`kernel.c` is being decomposed into standalone compilation units and the
project is restructured into a Linux/BSD-style directory layout:

```
arch/x86/boot/    stage1.S, stage2.S, bootdefs.h, linker scripts
arch/x86/         isr_stubs.S, ctx_sw.S, ap_entry.S
kernel/            string.c, serial.c, sched.c, vga_fb.c, lz4_kernel.c, cvm_host.c
drivers/           ide.c, block.c, pcspk.c, sb16.c, rtc.c
fs/                minifs.c, zip.c
net/               net.c, tls.c, tls_crypto.c, tls_x509.c
third_party/       xxhash, stb, dlmalloc, miniz
```

Headers remain in the project root (accessed via `-I.`); source files live
in subdirectories. The Makefile uses `VPATH` so make finds sources in
subdirs while `.o` files stay in the root for the link line.

Extracted so far:
- `serial.c`: COM1 16550 UART driver (init, putc, getc, available, puts)
- `string.c`: kernel string/memory functions (kstrlen, kmemcpy, katol, etc.)
- `console.c`: text console, output capture and libc name table (ADR-0011;
  `kernel.c` is now only the Mediator orchestrator + syscall trampoline)
- `driver.c`: Strategy-pattern device registry (`ide0` block, `pcspk0`
  audio, consumed by `block.c` through ops); VFS exposes the
  `file_operations`/`vnode_t` facade (ADR-0012)
- Drivers: ide, block, pcspk, sb16, rtc moved to `drivers/`
- Filesystem: minifs, zip moved to `fs/`
- Network: net, tls, tls_crypto, tls_x509 moved to `net/`; the rtl8139
  driver further split into its own contract `net/rtl8139.c` with the
  boundary header `net/rtl8139.h`
- Scheduler: sched.c, vga_fb.c, lz4_kernel.c, cvm_host.c moved to `kernel/`
- Syscalls: proc-leaf handlers (clone, seccomp, nice, yield, getpid/tid,
  fork/vfork/execve stubs, exit, wait4, kill) moved to
  `kernel/syscalls_proc.c` with the boundary header `syscalls_proc.h`;
  first increment of the `syscalls.c` decomposition, tables unchanged
- Memory: VMA red-black tree moved to `vma.c` (its own contract, was inline
  in loader.c against a divergent `vma.h`)
- Editor: the built-in line editor moved to `kernel/editor.c` with the
  boundary header `editor.h`; `shell_readline_buf`/`shell_parse` and the
  `CMD_BUF_SZ`/`MAX_ARGS` bounds are shared through `shell.h`
- Boot: stage1.S, stage2.S, bootdefs.h moved to `arch/x86/boot/`
- Arch: isr_stubs.S, ctx_sw.S, ap_entry.S moved to `arch/x86/`
- WM: six header-only contracts at the root (`wm_geom.h`, `wm_events.h`,
  `wm_window.h`, `wm_render.h`, `wm_tiling.h`, `wm_focus.h`, ADR-0020);
  `kernel/vga_fb.c` consumes them for hit-testing, event edges, paint
  order, tiling cells and focus transitions, host-tested by `make test-wm`

Future extractions: shell.c (circular deps with console_getc/redirect),
loader.c (deps on static mm funcs), mm.c, and the remaining `syscalls.c`
leaves (fd table, spawn bridge, mm, net, gfx handlers, in that risk order).

### VFS Invariant Documentation (Phase 1.4)

`kernel.h` documents explicit contracts for `vfs_ops_t`, `vfs_file_t`,
`KFILE`, and `RDFile`:
- Every field has a semantic contract (what it holds, when it is valid)
- Invariants are stated (what must be true before/after operations)
- Failure modes are documented (what happens on error)

### CVM Hardening (Phase 3.3)

The CVM interpreter already has comprehensive bytecode validation:
- Module loading: magic, version, size, all section bounds checked
- Jump targets: bounds-checked against `code_size` (OP_JMP, OP_JZ, OP_JNZ)
- Function calls: bounds-checked against `num_funcs` (OP_CALL)
- Native calls: bounds-checked against `num_module_natives` + CVM_MAX_NARGS
- Memory operations: all use `mem_valid()` for bounds checking
- Stack operations: overflow/underflow checks via vp()/vo()
No additional hardening was needed.

### Shell Extraction Plan (Phase 6.1)

`shell.h` defines the public API.  The extraction of 38 shell functions
(~2070 lines) from kernel.c to shell.c is planned as a future phase.
See `tools/extract_shell.py` for the full dependency analysis.  The
extraction requires:
- Making redirect_begin/commit/suspend/resume non-static (done)
- Making shell_run_elf_buf, shell_run_elf_file, shell_run_cvm non-static
- Making shell_run_any, shell_exec_builtin, shell_report non-static (done)
- Making console_getc non-static (done)
- Breaking circular dep: kfgetc (kernel.c) -> console_getc (shell section)
- Breaking circular dep: load_exec_elf -> redirect_suspend/resume
- Exposing fs_cwd, fs_resolve, and filesystem helpers
- Updating the Makefile to compile shell.c

The circular dependencies between console_getc, kfgetc, redirect functions,
and the ELF loader make a clean extraction non-trivial.  The cross-boundary
functions are now non-static with declarations in kernel.h, ready for
extraction when the circular deps are broken.

### Architectural Governance (Phase 2)

CI gates enforce architectural constraints:
- `tools/check_cohesion.py`: fails if any root community's cohesion drops
  below 0.25 (configurable in ARCH_POLICY.yaml)
- `tools/check_complexity.py`: fails if kernel.c exceeds 350 symbols
  without explicit approval in ARCH_POLICY.yaml
- `tools/check_surprising.py`: flags new connections of 5+ hops between
  distinct communities as coupling debt
- `tools/check_kb_sync.py`: verifies KNOWLEDGE_BASE.md is in sync with code

`.github/workflows/governance.yml` runs these gates on every push.
`.github/workflows/test.yml` runs the unified test pipeline.

### Validation Gate (updated)
```bash
make                        # zero warnings
make lint                   # cppcheck + -Wextra (ring-3) + clang-tidy curated + bash -n + abi-numbers, all green
sh src/test_all.sh          # one-boot comprehensive non-interactive suite (68 PASS)
./test_bdd.sh               # all scenarios green (full interactive suite)
python3 tools/test_gui_wm.py  # QMP pixel proof: gfx survives Alt+Tab/tile, taskbar button refocuses
python3 tools/test_gui_icon_cwd.py  # QMP pixel proof: dock launch ignores shell cwd
python3 tools/test_gui_fashion.py  # QMP pixel proof: one cursor, stable frames, ESC quit
./tools/test_codecs.sh      # lzss/lz4/aes roundtrips (pass=3)
./mutate.sh                 # every mutant killed
make test-tls               # host-side crypto + handshake suite
make test-vma               # host-side VMA red-black tree suite
make test-freedom-wl  # Wayland-to-MiniOS mapping suite green (ADR-0019)
make test-freedomui   # real FreeDom engine backend suite green (ADR-0021)
make test-futex test-percpu-rq test-batch test-rcu  # SMP scaling contracts green
make test-sanitize  # syscall sanitize-macro suite green
make test-tick test-hal  # tick bus + HAL port-mapping suites green
make test-driver test-sync  # device registry + sync/PI suites green
make test-rtc        # RTC civil-date math suite green
make test-vedit      # vedit IDE build-contract suite green
make test-file       # file browser assoc-contract suite green
make test-paint      # paint canvas/PNG-contract suite green
make test-theme      # shared Nuklear theme suite green
make test-wm         # WM geometry + event translator suite green
make test-ktime test-randmix  # Phase 0 truthfulness: TSC->usec + getrandom mixer green
python3 tools/check_abi_numbers.py  # Phase 0.6: syscall numbers match Linux x86-64 (also in lint)
python3 -m unittest -v mcp/test_minios_mcp.py   # unit + QEMU BDD
mcp/mutate_mcp.sh           # every MCP mutant killed
python3 tools/check_cohesion.py KNOWLEDGE_BASE.jsonld
python3 tools/check_complexity.py --policy ARCH_POLICY.yaml
python3 tools/check_surprising.py KNOWLEDGE_BASE.jsonld
```

<!-- readmenator-agent-kb-link -->
## Project Knowledge Base (MUST read before coding)

MUST read `readmenator-agent/MANIFEST.json` first for freshness. NEVER `glob src/**` before `grep` in `readmenator-agent/INDEX.md`.

Workflow: 1) `grep -n '<keyword>' readmenator-agent/INDEX.md readmenator-agent/SYMBOLS.md` 2) `cat readmenator-agent/KB_<subsystem>.md` 3) check `readmenator-agent/GOTCHAS.md` before editing.

This project contains analysis outputs generated by [ReadMenator](https://github.com/grisuno/ReadMenator), a zero-token polyglot static analysis tool.

**For humans:** Read `KNOWLEDGE_BASE.md` -- full architecture reference.

**For agents:** Read `readmenator-agent/INDEX.md` -- grep-friendly index.
  - `readmenator-agent/MANIFEST.json` -- freshness + entrypoints (start here)
  - `readmenator-agent/INDEX.md` -- file -> purpose map
  - `readmenator-agent/SYMBOLS.md` -- symbol index (grep-friendly)
  - `readmenator-agent/API.md` -- public functions + contracts
  - `readmenator-agent/GOTCHAS.md` -- "don't change X because Y breaks"
  - `readmenator-agent/KB_<subsystem>.md` -- per-subsystem context (grep-friendly)
  - `readmenator-agent/SECURITY.md` -- findings by severity
  - `readmenator-agent/recipes/*.md` -- actionable task blocks

If MANIFEST date/commit is stale vs `git HEAD`, regenerate:

    pip install readmenator && readmenator . --rebuild
<!-- /readmenator-agent-kb-link -->
