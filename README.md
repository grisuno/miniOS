# MiniOS

A 64-bit x86 teaching kernel that carries its own toolchain. You can write a C
program inside the running system, compile it, link it and execute it without
leaving the machine.

# MiniOS Desktop Environment and Graphical Subsystem

I have implemented a primitive desktop environment within MiniOS that operates independently of the serial console. This subsystem provides a graphical user interface (GUI) with window management, mouse support, and scrollable terminal emulation.

## Key Features
*   **Shell in VGA:** Handles basic shell and focus in VGA mode to avoid serial mode
*   **Mouse Integration:** Full PS/2 mouse driver support with hardware cursor rendering.
*   **Scrollable Terminal:** A virtual terminal emulator capable of handling large buffers and scrollback history via mouse wheel or keyboard shortcuts.
*   **Speaker's Sound:** Sound support to speaker

### Desktop icons, PNG, Nuklear and low-code CVM

The desktop now supports PNG icons (via stb_image) that can be placed and launched from the graphical shell. Immediate-mode UI is powered by Nuklear, giving windows, buttons and widgets without a retained-mode toolkit. A low-code tool lets you author CVM modules in a simplified form that compile straight to bytecode and run natively on the CVM (with the existing JIT). Additional support includes xxHash for fast hashing and experimental TFT display output alongside the VESA framebuffer.

## Testing the VGA desktop (doctrine)

VGA-mode behaviour (the mouse cursor, window drag, title-bar buttons, the
desktop compositor, and the return-to-desktop transition after a ring-3
program) must be exercised with **`tools/minios_gui.py`, never headless.**
Headless boots cannot observe or trigger these events, so a GUI bug verified
by hand or assumed from code is not reproduced.

`tools/minios_gui.py` boots QEMU with the emulated std VGA device (the
linear framebuffer the desktop renders into), a QMP socket to inject PS/2
mouse motion, clicks and keyboard, and a pty serial console to drive the
shell. After each action it saves the current framebuffer to a PNG via QMP
`screendump`, so a crashed desktop, a vanished cursor or a corrupted window
is visible:

```
python3 tools/minios_gui.py send "doomgeneric.elf" sleep 10 \
    key esc key down key down key down key down key down key ret key y \
    dump after_doom
```

Actions: `send LINE`, `mouse DX DY`, `click`, `key QCODE`, `dump NAME`,
`sleep SECS`. The serial console is on a pty; the kernel's `gfx`/`gfx pixel
x y` commands probe the framebuffer state over serial (mouse present,
position, palette index at a pixel), which is the text backstop when an
image viewer is unavailable.

## Desktop icons, PNG, Nuklear and low-code CVM (continued)

```
miniOS> edit src/p.c
edit> a
int main(void) { return 7; }
edit> x
miniOS> run objects/minigcc.o src/p.c > asm/p.s
miniOS> run objects/ld.o -f elf -o bin/p.elf asm/p.s
miniOS> run objects/ld.o -f cvm -o cvm/p.cvm asm/p.s
miniOS> run bin/p.elf
exit code: 7
miniOS> run cvm/p.cvm
exit code: 7
miniOS>
```

## Taskbar, clock and volume

The bottom taskbar is a live status strip, not a hint line:

- **Clock:** reads the CMOS RTC (`rtc.c`) and shows `HH:MM:SS`, redrawn when the
  second changes. A failed RTC read leaves the clock region blank rather than
  showing a stale time. The shell `date` builtin prints the same clock over the
  serial console.
- **Volume:** a master volume `0..100` (`pcspk.c`). The PC speaker has no
  hardware amplitude and the kernel does not drive a PWM carrier, so the volume
  is a **mute switch**: the tone opens the speaker only when the volume is
  above 0 (identical to the pre-volume driver), and at 0 the speaker is silent.
  A click on the speaker icon toggles mute; the `-`/`+` buttons step the
  volume. The shell `vol [0-100]` builtin reads and sets the same state, so the
  desktop and the serial console can never disagree.

## Tiling window shortcuts

Alt is the WM modifier. From the desktop:

| Shortcut | Action |
|----------|--------|
| Alt+Enter / F11 | toggle fullscreen |
| Alt+Arrow keys | snap the window to a screen half |
| Alt+Home / Alt+End | snap to the top-left / bottom-right quadrant |
| Alt+`[` / Alt+`]` | shrink / grow width |
| Alt+`-` / Alt+`=` | shrink / grow both dimensions |
| Alt+0 / F5 | reset the window to its default position (and size) |
| Ctrl+Arrow keys | nudge the window by one cell |

The window keeps its size across redraws, so a snap or resize persists instead
of snapping back to the default.

## Shell window and desktop mouse

The shell runs in a **titled, movable window** on the desktop, not on the whole
screen:

- **Title bar** ("MiniOS Terminal"): drag it with the left mouse button to move
  the window, it stays under the pointer, and the terminal content and prompt
  survive the move.
- **Scrollbar** on the window's right edge: the mouse wheel scrolls through
  the scrollback history, and a left click on the scrollbar jumps the view to
  that position.
- **Adaptive content**: the terminal keeps its whole history as logical lines
  and re-wraps them at the current window width on every draw, so resizing or
  snapping re-flows the text instead of clipping it. A long wrapped line is
  stored whole and re-wraps cleanly at any width, and the live screen and the
  scrollback view always agree (no artifacts when scrolling over existing
  output).
- **Move and resize from the mouse**: Alt+`[`/`]` change the width, Alt+`-`/`=`
  change both dimensions, and the arrow/Home/End tiling keys above re-position
  and re-size the window. Alt+0 / F5 reset it to the default geometry.
- **Fullscreen** with F11 or Alt+Enter.

Moving, snapping and resizing never lose the current screen: the prompt and any
typed or echoed text are re-rendered from the logical buffer at the new
position and size.

## Demo

- [https://www.youtube.com/watch?v=YUYEK7lQt0U](https://www.youtube.com/watch?v=YUYEK7lQt0U)
- [https://www.youtube.com/watch?v=4aHe6T0bD1o](https://www.youtube.com/watch?v=4aHe6T0bD1o)

## Wiki

- [https://deepwiki.com/grisuno/miniOS](https://deepwiki.com/grisuno/miniOS)

## The four repositories

MiniOS is one of four projects that together make up the system. This
repository holds the kernel, the boot path and the ramdisk; the toolchain it
carries lives next door.

| Repository | Role |
|------------|------|
| [miniOS](https://github.com/grisuno/miniOS) | this repository: kernel, two-stage boot path, ramdisk, shell, editor |
| [miniGCC](https://github.com/grisuno/miniGCC) | C compiler: C to x86-64 AT&T assembly |
| [ld](https://github.com/grisuno/ld) | assembler and linker: assembly to a Linux ELF or a CVM module |
| [cvm](https://github.com/grisuno/cvm) | the CVM / cvm2 bytecode interpreter |

The ramdisk ships prebuilt objects in `progs/`, so `make` produces a bootable
image with nothing else installed. To build the whole system from source
instead, clone the other three next to this one:

```bash
make sources          # clone the missing repositories from GitHub
make toolchain        # build minigcc, ld and cvm2 from those sources
make                  # rebuild every ramdisk object and os.img
```

`make sources` never touches a directory that already exists, so a checkout
with local work is left alone. `make sources-update` pulls the latest commit
of each before rebuilding, and `make sources-status` shows which revision
each one is sitting on.

Expected layout: the directory holding this repository can have any name:

```
src/
├── miniOS/     (this repository)
├── miniGCC/
├── ld/
└── cvm/            with cvm/cvm2 inside
```

Point the build somewhere else with `MINIGCC_DIR=`, `LD_DIR=`,
`CVM_REPO_DIR=` or `CVM_DIR=`; change where `make sources` clones from with
`MINIGCC_URL=`, `LD_URL=` or `CVM_URL=`.

Everything on the ramdisk is regenerated from source by `make`: `objects/minigcc.o`,
`objects/ld.o` and `objects/cvm.o` are compiled from the sibling checkouts, and
the demo programs (`fib`, `w1`, `minigcc`) are compiled from this repository's
own C sources in `progs/src/` through the full miniGCC-to-ld chain. Nothing in
the image is a binary you have to take on trust.

The compiler on the ramdisk is self-hosted: `bin/minigcc.elf` was compiled by
minigcc itself (generation 3) and linked by `ld` (no GNU as/ld anywhere after
generation 1), and `make selfhost` verifies the bootstrap fixed point on the
host. Inside the OS the self-hosted compiler drives the same edit/compile/
link/run loop as `objects/minigcc.o`.

<img width="4082" height="7837" alt="diagram" src="https://github.com/user-attachments/assets/c3ba2575-c657-44c4-b0f5-d3c4b414da10" />


## Build and run

```bash
make            # builds os.img
make run        # boots it in QEMU with a display
make run-kvm    # boots it with KVM acceleration
make run-headless # boots it headless on the serial console (no GUI window)
make serial     # boots it headless on the serial console
make test       # behavioural suite (QEMU + serial console)
make selfhost   # compile minigcc with minigcc, link with ld, check fixed point
```

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
(see below), which took DOOM's load from ~5 minutes to ~30 s under KVM, but
the remaining data-transfer reads are inherent to PIO.

The image is attached as an IDE disk. The boot path uses INT 13h extended
(LBA) reads, which floppy emulation does not provide.

## Performance work

- **IDE PIO driver** (`ide.c`): `ide_delay` used to read the IDE control
  register 1000 times per call as a crude timer, and `ide_select_drive`
  called it twice per sector. Under KVM that turned a 4 MB WAD load into
  millions of VM-exits (~5 minutes). It is now a short CPU pause loop, which
  cut DOOM's load to ~30 s under KVM while keeping TCG fast.
- **Block cache** (`block.c`): a direct-mapped write-through cache of
  recently-read disk blocks. MiniFS's directory iteration re-reads the same
  directory block for every entry (`lsfs` was O(entries x blocks) in disk
  reads); the cache turns that into one read per directory block plus one per
  touched inode.
- **Console output** (`vga_fb.c`): the windowed terminal redrew the whole
  active line for every printable character (100 000 chars took ~14 s). It
  now draws only the changed cell, so `ls` and all console output are fast.
- **SB16 DMA buffers** (`sb16.c`, `stage2.S`, `bootdefs.h`): the DMA ring
  `[0x90000, 0x94000)` is marked uncacheable (PCD) in the boot page tables so
  the 8237 DMA controller reads freshly written PCM instead of stale cache.
  The DSP write wait no longer burns a 100 000-iteration port-read spin on
  the wrong status bit.
- **SB16 timer watchdog** (`sb16.c`, `sched.c`): DMA completion is driven by
  the SB16 IRQ *and* a timer-ISR watchdog (`sb16_poll`). QEMU raises the
  completion IRQ only once its audio engine consumes a transfer, so a host
  backend that never consumes left the 7-slot ring filled forever and every
  later submit refused (the piano buzzed / fell silent). The watchdog re-arms
  on elapsed guest time, and `sb16_arm` rate-limits both paths to one re-arm
  per buffer, so the ring always drains at the declared rate. The `sb16`
  builtin reports the counters (`irq_arms`, `poll_arms`, `submits`, `drops`).
- **Syscall trace flood** (`kernel.c`): `trace on` no longer prints
  `SYS_TIME`/`SYS_KBD`/`SYS_MOUSE` (clock/poll reads a pacing loop hammers
  thousands of times a second). Tracing those made an interactive program a
  100 ms-per-syscall crawl under TCG; the rest are traced one-to-one.
- **Multi-sector IDE PIO** (`ide.c`): `ide_read_sectors`/`ide_write_sectors`
  issue one command with `SECCOUNT = count` instead of `count` single-sector
  commands, cutting the per-sector command-setup port traffic of bulk loads.
  Data is still pulled word-by-word through the PIO data port, so the
  remaining minifs load time is bounded by QEMU's 16-bit-only IDE port.

## Network and https

The kernel owns an rtl8139 NIC under QEMU user networking (slirp): Ethernet,
ARP, IPv4, ICMP echo, UDP, DNS and a client TCP (SYN handshake, stop-and-wait
with retransmissions, FIN teardown). `net` shows the counters and
`net ping 10.0.2.2` sends one ICMP echo.

On top of TCP the kernel speaks TLS 1.2 as a client
(`tls_handshake`/`tls_send`/`tls_recv`, MiniOS syscalls 201-203):
ECDHE-RSA/ECDSA with AES-128-GCM, certificate chains verified down to 8
embedded public roots, hostnames checked against SAN or CN with
single-label wildcards. Real-world browsing works from the shell:

```
miniOS> run bin/freedom https://duckduckgo.com
miniOS> run bin/freedom mini os kernel        # DuckDuckGo search over https
miniOS> run bin/freedom https://en.wikipedia.org/wiki/Mini
miniOS> run bin/freedom --dump-dom https://example.com
miniOS> run bin/freedom --dump-css https://example.com
```

`bin/freedom` is the headless text browser: a curlfree-style HTTP engine
with a FreeDom-style omnibox (an argument that is not a URL is a DuckDuckGo
search; bare hosts are fetched as `https://`), redirect chasing, chunked
decoding, an HTML-to-text filter, and `--dump-css`/`--dump-dom` headless
dumps. The crypto and the roots are host-tested by `make test-tls` (fixed
vectors plus full TLS 1.2 handshakes against OpenSSL-driven servers,
including the negative set).

## Shell

| Command | Purpose |
|---------|---------|
| `help` | command summary |
| `ls` | list directory entries |
| `cat <file>` | print file contents |
| `echo <text>` | print text to the console |
| `mkdir <name>` | create a directory entry |
| `rm <file>` | delete a ramdisk file |
| `pwd` | print the current working directory |
| `cd [dir]` | change directory (bare cd goes to root) |
| `edit <file>` | line editor |
| `load <file>` | load an ELF (`.o` relocatable, or a Linux executable) |
| `run <name\|file> [args]` | run a program, an ELF or a `.cvm` module |
| `<cmd> [args]` | run an ELF from `bin/<cmd>`: the Linux-style command path |
| `<cmd> > <file>` | redirect command output to a ramdisk file |
| `<cmd> >> <file>` | append command output to a ramdisk file |
| `date` | print the CMOS clock (`HH:MM:SS`), the same clock the taskbar shows |
| `vol [0-100]` | print the PC-speaker volume; with an argument, set it |
| `net` | network status (MAC, IP, counters) |
| `net ping <ip>` | send one ICMP echo |
| `net dns <host>` | resolve a DNS A record |
| `catfs <file>` | print a file from the MiniFS filesystem |
| `lsfs` | list files on the MiniFS filesystem |
| `hash <file>` | print XXH64 checksum of a file |
| `ps` | list registered programs (name, kind, entry address) |
| `sb16` | Sound Blaster 16 diagnostics (presence, mode, ring fill, counters) |
| `trace` / `trace on` / `trace off` | enable or disable syscall tracing |
| `wm state` | print window manager state |
| `wm minimize` | minimize the terminal window |
| `wm maximize` | toggle fullscreen |
| `wm close` | close the active window |
| `sh <script.sh>` | run a shell script (sequential commands, `#` comments) |
| `piano` | FM piano GUI (`--selftest` for headless, `--bench` for fps) |
| `topogpt3` | TopoGPT3 transformer inference engine (`-i` for interactive) |
| `clear` / `poweroff` | console and power |

Redirection captures what the command writes, not what the shell reports
about it, so `run objects/minigcc.o p.c > asm/p.s` yields assembly a linker
can consume.

`bin/cp` is a command-path utility: `cp src/fib.c x.txt` copies a ramdisk
 file without `run` or `load`. It is compiled from this repository's own
 `progs/src/cp.c` through the miniGCC-to-ld chain, and the source ships on
 the ramdisk as `src/cp.c`, so the utility can be rebuilt inside the OS by
 the OS.

`bin/lzss` and `bin/unlzss` are the Okumura LZSS (de)compression tools, both
 built from a single `progs/src/lzss.c`: `lzss rep.txt rep.lzs` compresses,
 `unlzss rep.lzs rep.out` decompresses, and the binary picks its mode from
 `argv[0]` (`unlzss` decodes; `-d` forces decode). The on-disk format is a
 fail-closed `LZS1` magic plus the original size; decoding rejects a bad
 magic, a truncated stream and any declared size beyond the expansion bound
 derived from the input length, so a hostile header can never drive an
 oversized allocation.

`bin/lz4` and `bin/unlz4` are the LZ4 (de)compression tools, also built from a
 single `progs/src/lz4.c`: `lz4 rep.txt rep.lz4` compresses and `unlz4
rep.lz4 rep.out` decompresses, with the same `argv[0]`/`-d` dispatch as
`lzss`. The codec lives in the kernel (`lz4_kernel.c`, the same one MiniFS
uses), so the tools are thin front-ends over the MiniOS syscalls 216/217 and
the on-disk block is exactly the MiniFS LZ4 block format: a 4-byte
little-endian original size followed by the raw LZ4 stream, so `lz4` output
interops with the filesystem's own blocks.

`bin/aes` and `bin/unaes` are AES-256-CTR file encryption tools built from a
single `progs/src/aes.c`, shipped on MiniFS like DOOM and MicroPython:
`aes <key-hex64> <nonce-hex32> <src> <dst>` encrypts and the matching
`unaes ...` decrypts. The S-box is generated procedurally from the GF(2^8)
inverse plus the FIPS-197 affine transform (no magic tables), the mode is
CTR with no padding, and the fail-closed `AES1` container detects bad magic,
truncation and size tampering. CTR gives confidentiality only, pair it
with a MAC if you need integrity.

`unzip` and `zip` are shell builtins that read and write ZIP archives through
the miniz library (vendored as `third_party/miniz/`). `zip <out.zip> <file...>`
stores files with default compression; `unzip <archive.zip> [dir]` extracts
into a directory (default cwd); `unzip -l <archive.zip>` lists entries. Entry
names hostile data: traversal paths, absolute paths and empty components are
all rejected, so a crafted archive can never write outside the target
directory.

`json` (`progs/src/json.c`) is a self-contained JSON validator, pretty-printer
and query tool. `json <file>` validates and pretty-prints; `json <file> <path>`
prints the value at a dotted path (`.a.b`, `.a.3`). The parser is fail-closed:
truncated input, unbalanced braces and unknown escapes all produce a diagnostic
and exit 1.

## Nuklear node editor

MiniOS ships Nuklear as a static Linux ELF at ring 3, built from the upstream
single-header immediate-mode UI library. The demo app is a visual node editor:
a low-code tool for the CVM that compiles a dataflow graph into a `.cvm` module.

```
miniOS> nuklear                     # GUI: drag nodes, wire pins, compile
miniOS> nuklear --selftest          # headless: renders one frame, proves pipeline
miniOS> nuklear --demo cvm/demo.cvm # compiles a fixed (2+3)*4 graph
miniOS> nuklear --compile src/graph.txt cvm/out.cvm
miniOS> run cvm/out.cvm             # run the compiled module
```

The node editor supports Number, Add, Sub, Mul, Div, Neg, Print and Exit nodes.
Pins are wired by dragging; Compile writes a `.cvm` module to the ramdisk.
`--selftest` renders one frame through the full graphics pipeline and verifies
the pixel landed in the framebuffer (`nuklear: frame ok (800x360)`).

Build from source:

```bash
make progs/bin/nuklear.elf    # or just `make` to rebuild everything
```

## One-boot comprehensive test (`src/test_all.sh`)

`sh src/test_all.sh` runs the full non-interactive test suite inside a single
QEMU boot. Every command prints a `PASS:` marker; the host runner greps the
serial log for these markers. The script ships on the ramdisk.

```bash
tools/boot_run.sh "sh src/test_all.sh" --timeout 120
strings boot_run.log | grep -c 'PASS:'   # expect 61
```

Categories tested (61 PASS):
- Boot/help, filesystem (ls/mkdir/cd/pwd/rm/cp), redirects (>  >>)
- Builtins: echo, date, vol (set/report/reset), ps, trace, net, gfx, wm, hash
- Toolchain: minigcc.o compile, ld.o link, run ELF, run CVM
- Bare names without `run` prefix
- Self-host: minigcc.elf compiles, ld.o links, run
- Codecs: lzss/lz4/aes roundtrips, error cases
- JSON validate/query
- ZIP: hostile archive (traversal refused), host-produced archive
- ELF programs: lxhello, cpl, kmem, nx, mmreuse
- CVM modules: fib, w1
- Selftests: xxhash.o, dlmalloc.o
- Heap stability (repeated CVM runs), tracing

No interactive commands, no external server dependencies.

## Editor

`edit <file>` opens a nano-like line editor over a ramdisk or MiniFS file
(extracted to `kernel/editor.c`, contract in `editor.h`). The status line
shows the filename, current line number and a `*` when the buffer is modified.

| Key | Action |
|-----|--------|
| `h` | help |
| `l` | list the buffer |
| `p N` | print line N |
| `.` | print the current line (no argument) |
| `g N` | go to line N |
| `n` / `b` | next / previous line (advance or rewind the cursor) |
| `/ text` | search forward for `text` and jump to the match |
| `=` | show status (current line, total lines, modified flag) |
| `l a b` | list lines a through b |
| `e N` | replace line N with the next line typed |
| `a` | append the next line typed |
| `i N` | insert before line N |
| `d N` | delete line N |
| `w` | save |
| `x` | save and quit |
| `q` | quit, refusing to discard unsaved changes |
| `q!` | quit, discarding changes |

A file too large for the buffer is loaded read-only: the editor refuses to
write it back rather than silently dropping the part it never read.

## Program formats

MiniOS runs three kinds of program:

- **Relocatable objects** (`.o`): linked at load time against the kernel's
  libc symbol table. They run at ring 0 as kernel extensions.
  `objects/minigcc.o`, `objects/ld.o` and `objects/cvm.o` ship this way.
- **Linux executables** (`ET_EXEC` / `ET_DYN`): static binaries run
  unmodified through the x86-64 `syscall` ABI at ring 3 under hardware
  page protection. A binary built on the host can be used simply by
  copying it onto the ramdisk. This is how DOOM, Quake 2, Lua,
  MicroPython, and TopoGPT3 run.
- **CVM modules** (`.cvm`): stack bytecode produced by `ld -f cvm` and
  executed by the cvm2 interpreter in `objects/cvm.o`. An x86-64 JIT
  compiler compiles each module to native code at load time; the output
  is identical to the interpreter and the JIT is transparent to the user.

## CVM JIT compiler

Every `.cvm` module is compiled to native x86-64 code at load time by a
baseline JIT. The JIT is transparent: output is byte-identical to the
interpreter, and the full miniGCC compiler (`minigcc.cvm`) runs correctly
under JIT inside the OS.

The JIT compiles each function independently into a native code buffer on
the kernel heap (executable via 2 MB pages). Cross-function control flow
(CALL/RET) uses the interpreter's frame stack, so the ABI is unchanged.
If JIT initialization fails, the interpreter takes over transparently.

On the host the JIT buffer uses `mmap` (RWX); inside MiniOS it uses
`malloc` (the kernel heap is already executable). Source files:
`cvm_jit.c` (compiler), `cvm_jit_x86.c` (x86-64 emitter),
`cvm_jit_help.c` (runtime helpers).

## Ramdisk layout

The ramdisk ships organized by kind, and the shell's `ls <dir>` lists each
directory:

| Directory | Contents |
|-----------|----------|
| `objects/` | ET_REL toolchain: `minigcc.o`, `ld.o`, `cvm.o`, demo `.o` |
| `bin/` | Linux ELFs + command-path utilities (`cp`, `freedom`, `micropython`, `topogpt3`) |
| `cvm/` | CVM modules: `fib.cvm`, `w1.cvm`, `minigcc.cvm` |
| `src/` | C sources for every program on the ramdisk |
| `asm/` | miniGCC assembly (`*.s`) for the toolchain-built programs |
| `docs/` | HTML and other documentation fixtures |
| `topogpt3/` | TopoGPT3 model: `topogpt3.c`, `topogpt3.fp16` (47 MB weights), `vocab.bin` |

The ramdisk is flat, the `/` in a name is data, and `mkramdisk.py` derives
each name from the path relative to `progs/`.

## Doom

MiniOS ships a doomgeneric port that runs DOOM as a static Linux ELF at
ring 3. The engine compiles from `progs/doomgeneric/` with the platform
layer in `doomgeneric_minios.c`. The desktop runs on a VESA linear
framebuffer (800x600x8 by default, falling back to 640x480 and Mode 13h);
DOOM renders its 320x200 frame into a kernel back-buffer and the kernel
composites it onto the desktop in a titled window (`SYS_DOOM_FRAME`, 211),
centered on the screen, so the shell window stays visible while you play.
The shareware WAD (`doom1.wad`) is bundled on the minifs.

```
miniOS> run doomgeneric.elf
```

| Key | Action |
|-----|--------|
| WASD | move |
| Ctrl | fire |
| Space | use / open |
| Arrow keys | turn / strafe |
| 1-7 | weapon select |
| Shift | run |
| Esc | menu |

Sound effects play through the QEMU PC speaker: the kernel drives PIT
channel 2 (ports 0x42/0x43) plus the gate bit on port 0x61, and the sound
module in `i_minios_sound.c` maps each DP lump (1-byte frequency index +
1-byte duration in 70 Hz ticks, after a 2-byte priority) through the
original Doom PC-speaker frequency table. QEMU must wire the PC speaker
to the audio backend, `-machine pc,pcspk-audiodev=<id>` in addition to
`-audiodev <backend>,id=<id>` (the `run` target sets both via
`QEMU_AUDIO`). A bare `-audiodev` alone routes nothing, so the beeps are
silent without the machine option.

The level music also plays on the same PC speaker with NES-style
pseudo-polyphony. A `music_pcspeaker_module` in `i_minios_sound.c` decodes
each MUS lump (the Doom music format, `D_E1M1` etc. at the stock 140
ticks/sec) straight from its interleaved event stream, splits the sounding
notes the way a NES split its voices: the lowest bass note becomes a
sustained pedal (the triangle voice) while only the top few melody notes
are fast-arpeggiated round-robin, holding each for 7 ms. The ear hears a
strummed chord with a solid bass foundation instead of every voice chopped
at equal length, the chiptune broke-chord trick, applied so dense
arrangements stay clear. The module is
picked when `snd_musicdevice` is the PC speaker, and `S_UpdateSounds` was
re-enabled in `d_main.c` so both the sfx note sequencer and the music
decoder are advanced each frame (they were previously never polled).

The binary is built with the host toolchain (static, no-pie) and placed
at `bin/doomgeneric.elf` on the minifs. To rebuild from source:

```bash
make doomgeneric.elf    # or just `make` to rebuild everything
```

The kernel provides four custom syscalls for the port: `time_ms` (204),
`kbd` (205), `palette` (206) and `kbd_raw_mode` (207). VGA Mode 13h is
entered through `sys_vga_mode` (208), which tells the kernel to stop
touching VGA text hardware while the game runs.

## Quake 2

MiniOS ships a quake2generic port that runs Quake 2 as a static Linux ELF at
ring 3. The engine compiles from `progs/quake2generic/` with the platform
layer in `q2generic_minios.c`. It reuses the DOOM back-buffer infrastructure:
the software renderer writes 320x200 8-bit paletted pixels into the kernel
back-buffer at `DOOM_BACKBUF_ADDR` (0x0B000000), and `SYS_DOOM_FRAME` (211)
composites it onto the desktop as a titled window. The window title is set to
"Quake 2" via `SYS_Q2G_SET_TITLE` (223).

```
miniOS> run bin/quake2generic.elf +set basedir .
```

The engine requires `baseq2/pak0.pak` on the MiniFS. This image ships the
**full retail pak** (184 MB, 3307 files), so every campaign mission (Outer
Base, Warehouse, Installation, Command, Boss1/2, Fact, Hangar, Jail, Mine,
Power) and every weapon, item and monster model is present and playable. The
retail player model ships separately as `pak1.pak`. A small `pak2.pak` that
aliased the shareware demo maps as base1/2/3 was removed once the full pak
made it redundant.

Controls: WASD to move, Ctrl to fire, Space to use/open, arrow keys to
turn/strafe, the mouse to look, Shift to run, Esc for the menu. Sound is
stubbed (the engine runs silently); the SB16 PCM path could be wired in the
future. Rebuild from source with `make progs/bin/quake2generic.elf`.

## The Quake 2 bring-up: memory layout as a story

Getting Quake 2 to run was less about the game and more about the memory
model the kernel had to grow into. This is the story of those decisions and
of the two subtle bugs they uncovered, because they are the kind of bug that
only exists after you move a memory map.

**Why Quake needs so much memory.** The retail Quake 2 loads an entire
level's worth of data up front: the BSP world, every model and sprite the
mission references, the collision and drawing caches, plus the game's own
hunk/zone allocations. With the full 184 MB pak the game reaches for roughly
150-180 MB of the user window while loading a mission. The original layout
gave ring-3 programs a 128 MB window and parked the graphics back-buffer
inside it at 124 MB, which left the game roughly 120 MB to mmap into. That
was never going to be enough, and it failed in the honest way: the game ran
out of the window and the loader rejected further allocations.

So the window grew. `USER_LOAD_END` went from 128 MB to **192 MB**, and the
kernel heap moved up to sit right above it (192 MB to 384 MB). Growing the
window has a cascade of costs that all had to be paid together:

- **More page tables.** The user window runs on eager 4 KB page tables so the
  no-execute bit works. A 192 MB window needs 94 page tables (one 4 KB table
  per 2 MB PD slot). The page-table zone grew from 256 KB to **384 KB**
  (`PT_USER_TABLES_BYTES`), living at `[0x10000, 0x70000)`, below the kernel
  image. This zone is the single most dangerous address range in the kernel:
  it is dedicated, so *nothing else* may claim a page inside it.
- **Move the back-buffer up.** The DOOM/Quake back-buffer was inside the
  window at 124 MB, exactly where the game wants to mmap. It moved up to
  **176 MB** (`DOOM_BACKBUF_ADDR`), and the allocators are capped just below
  it so the game can never mmap over the pages the kernel maps for rendering.
- **Move KASLR up.** The kernel image's random physical base must sit above
  the window and the heap. `KASLR_MIN_ADDR` rose to 0x1A000000 so the kernel
  can never land inside either.
- **More RAM.** A 192 MB window, a 192 MB heap and a KASLR range that tops out
  near 600 MB simply do not fit in the old 512 MB guest. The image boots with
  **1 GB** (`-m 1G`, mirrored in `test_bdd.sh` and the MCP bridge).
- **A bigger filesystem.** The full retail pak is 184 MB. MiniFS grew from
  128 MB to **256 MB** to hold it, the engine, DOOM and MicroPython together.

With the memory in place the game stopped crashing on allocation and started
loading missions. Two bugs remained, and both were invisible until the map
grew, which is exactly why they are worth writing down.

**Bug one: the syscall trampoline silently downgraded the game to ring 0.**
The syscall entry decides how to return by inspecting the restored stack
pointer: if it lies inside the user window it returns to ring 3 with
`sysretq`, otherwise it returns to ring 0 with `jmp *%rcx` (the contract for
the ring-0 `.o` toolchain). The window bounds for that decision,
`USER_WIN_HI`, were still `0x07400000` (116 MB) after the window grew to
192 MB. The game's stack sits at the *top* of the window, near 192 MB, so
every syscall saw `rsp >= USER_WIN_HI` and took the ring-0 return path. The
game ran in supervisor mode for its whole life. The tell was the crash dump:
`cs=8` (kernel) with a user stack pointer, a combination that is impossible
for a real ring-3 fault, and it could only mean the game had been running at
ring 0. The fix was a one-line correction: `USER_WIN_HI` to `0x0C000000`.
This matters beyond Quake: any ring-3 program whose stack sits high in a
grown window would silently lose its protection.

**Bug two: the LAPIC page directory erased the user window's page tables.**
Every boot, `smp_init` parks a dedicated page directory for the local APIC
and zeroes it. It was parked at physical `0x60000`, which the comment called
"the dead boot staging buffer." It had been dead, until the page-table zone
grew. Index 82's user page table (the slot that maps roughly 165 MB of the
window) now lives at exactly `0x60000`. So on every boot `smp_init` wrote
zeros over the very page tables that made the game's 165 MB usable, and the
game faulted on a "page not present" the moment its mmap reached that region.
Diagnosis needed three steps: a page-table walk at the fault showed `pte=0`
while the boot-time dump showed it present; boot-step instrumentation isolated
the zeroing to `smp_init`; and reading the code found the collision. The fix
moved `LAPIC_PD_ADDR` to `0x70000`, just above the page-table zone and below
the syscall kernel stack. The lesson is the one the memory-map hazard contract
already warned about: the page-table zone is a jigsaw, and a fixed low-memory
address that was "dead" stays dead only until the map grows into it.

**The regression that taught the rule.** After Quake worked, DOOM showed a
black window while the game ran fine (you could hear it and drive the menu).
Quake and DOOM share the back-buffer infrastructure, so the back-buffer
mapping was not the problem, the *address DOOM wrote to* was. The kernel and
Quake had moved to `0x0B000000`, but DOOM's platform layer still rendered into
the old address `0x7C00000`, so the kernel composited an empty buffer. Every
consumer of a moved address has to move together; the fix was one constant in
`doomgeneric_minios.c`.

The takeaway is not the constants, it is why they are the way they are. A
window sized for the biggest ring-3 program, a page-table zone nothing else
may touch, a back-buffer above the mmap ceiling, a KASLR range above the heap,
and RAM and a filesystem large enough for the payload are not independent
tuning knobs. They are one layout, and changing any of them means re-checking
every fixed low-memory address that assumed it was alone.

## Piano (FM synth -> SB16)

MiniOS ships a ring-3 Nuklear piano that plays through the Sound Blaster 16
driver. The synth is Nuked-OPL3 (a cycle-accurate Yamaha chip emulator),
streaming 8-bit mono PCM at 22050 Hz to the kernel's SB16 DMA path via the
MiniOS PCM syscalls (221 open, 222 submit). On top of the FM engine the
piano adds expressive control: velocity (the click's vertical position sets
the carrier output level), a sustain pedal, octave shift, a master volume,
and live DSP effects on the mix (echo/delay, tremolo and soft clip), all from
an on-screen control bar.

```
miniOS> piano                     # GUI: click the keys to play
miniOS> piano --selftest          # headless regression hook
miniOS> piano --bench             # headless render-loop benchmark (~fps)
```

`--selftest` exercises the velocity mapping, sustain hold/release, octave
clamp, every FX stage and the audio pacing constants, and prints
`piano: selftest ok`. `--bench` runs the UI render loop for two seconds and
reports frames per second. Audio is rendered for the full wall-clock time
elapsed per frame (clamped to the SB16 ring's ~650 ms backlog) so slow frames
never under-render and starve the ring into a buzz.

## OPL3 FM Synthesizer

MiniOS ships a ring-3 OPL3 FM synthesizer (`opl3`) built from
`progs/src/opl3.c`. It is a Nuked-OPL3 (cycle-accurate Yamaha chip emulator)
that streams 8-bit mono PCM at 22050 Hz to the kernel's SB16 DMA path via
`SYS_SB16_PCM_OPEN` (221) and `SYS_SB16_PCM_SUBMIT` (222). The demo plays a
scale melody (A3 through C5 and back down) using a 2-operator FM instrument.

```
miniOS> run bin/opl3
```

This is a standalone demo of the FM synth engine that powers the piano. It
runs headless, produces audio through the SB16, and exits when the melody
completes.

## Memory Leak Detector

`mmreuse` (`progs/src/mmreuse.c`) is a ring-3 stress test for the kernel's
mmap and munmap implementation. It maps and unmaps 8 MB regions 64 times and
reports whether the address space leaked. Exit 0 means pass (no leak);
exit 1 means a map failed (address space exhausted).

```
miniOS> run bin/mmreuse.elf
exit code: 0
```

## Diagnostics

`perf` is a shell builtin that measures raw CPU speed, the `sys_time` clock
and console output throughput, pinpointing where guest time goes. `sbtone`
is a headless ring-3 program that streams a clean 440 Hz sine to the SB16
and reports submit throughput, isolating the audio path from any GUI. `sb16`
prints the SB16 driver counters (IRQ arms, watchdog poll arms, submits,
drops) and the ring fill, so ring health is observable over the serial
console without ears.

## Lua

MiniOS ships Lua 5.4 as a static Linux ELF at ring 3, built from the upstream
reference interpreter with a custom entry point (`progs/lua/lua_main.c`) and a
`minios` module (`progs/lua/minios.c`) that exposes kernel services to Lua
scripts. The binary is linked with `gcc -static -no-pie`, exactly like DOOM
and MicroPython.

```
miniOS> lua -e "print(6 * 7)"
42
miniOS> lua src/test.lua          # run the in-OS test suite
miniOS> lua                       # interactive REPL
> print(minios.time_ms())
12345
> print(minios.rtc())
8	30	15
> print(minios.fb_info())
800	600	800
> exit()
miniOS>
```

The `minios` module provides the following functions:

| Function | Purpose |
|----------|---------|
| `minios.time_ms()` | milliseconds since boot |
| `minios.rtc()` | returns hour, minute, second from the CMOS clock |
| `minios.fb_info()` | returns framebuffer width, height, pitch |
| `minios.vol([v])` | get or set PC-speaker volume (0..100) |
| `minios.pal(buf)` | load a 768-byte VGA DAC palette |
| `minios.pcspeaker(freq, ms)` | play a tone at freq Hz for ms milliseconds |
| `minios.run(path [,args] [,redirect])` | run a ramdisk program, preserving the interpreter |

`minios.run` invokes `SYS_SPAWN` (215), which runs a child program while
preserving the Lua interpreter state (user window, file descriptors, brk and
mmap cursors). This lets Lua scripts orchestrate the toolchain from inside
the OS:

```
miniOS> lua -e "minios.run('objects/minigcc.o', 'src/fib.c', nil, '>', 'asm/fib.s')"
miniOS> lua -e "minios.run('objects/ld.o', '-f', 'elf', '-o', 'bin/fib.elf', 'asm/fib.s')"
miniOS> lua -e "minios.run('bin/fib.elf')"
exit code: 0
```

The interpreter resolves through the command path (`bin/lua`) like `cp` and
`freedom`, so both `lua` and `run lua.elf` work. Scripts are opened through
the unified filesystem (ramdisk first, MiniFS fallback), and the interactive
REPL reads from the serial console. The in-OS test suite (`src/test.lua`)
exercises every `minios` binding, the filesystem, and the compression and
encryption tools.

Build from source:

```bash
make sources          # clones the Lua repository if missing
make                  # builds lua.elf and packs it into MiniFS
```

## MicroPython

MiniOS ships MicroPython as a static Linux ELF at ring 3, built from the
upstream unix port with a custom MiniOS variant. The variant enables floats,
the compiler, the `os` module and computed-goto, and disables readline
(the kernel handles echo and line editing), sockets, threading, SSL, FFI,
termios and native emitters. The binary is linked with `gcc -static -no-pie`,
exactly like DOOM.

```
miniOS> micropython -c "print(6 * 7)"
42
miniOS> micropython -c "print(1.5 * 2)"
3.0
miniOS> micropython src/hello.py
hello from python
miniOS> micropython
>>> print(40 + 2)
42
>>> exit()
miniOS>
```

MicroPython resolves through the command path (`bin/micropython`) like `cp`
and `freedom`, so both `micropython` and `run micropython.elf` work. Scripts
are opened through the unified filesystem (ramdisk first, MiniFS fallback),
and the interactive REPL reads from the serial console.

The kernel provides several syscalls for glibc-static compatibility:
`getcwd` (79) returns the shell working directory, `newfstatat` (262) reports
`S_IFREG`/`S_IFDIR` with file sizes from the unified filesystem, and
`readlink` (89) returns `EINVAL` (MiniOS has no symlinks) so glibc's
`realpath()` treats every path as a regular file and keeps resolving. A
script's `realpath()` and directory traversal work without needing a full
VFS layer.

#### Kernel fix: initial registers at the ELF entry

MicroPython previously crashed on exit (`EXCEPTION 14`). The root cause was
that `k_exec_user` did `iretq` to the ELF entry without zeroing the initial
registers, unlike Linux. glibc's `_start` does `mov %rdx,%r9` to obtain
`rtld_fini`; the leftover kernel value in `rdx` was a base-less function
pointer, which `__libc_start_main` registered as an exit handler and then
`__run_exit_handlers` demangled and called on exit, a wild jump. The fix
zeroes `rdi`, `rsi` and `rdx` before `iretq`, so `rtld_fini` is `NULL` and
every glibc binary exits cleanly.

#### `minios` module and in-OS toolchain orchestration

MicroPython ships with a `minios` C module (`progs/micropython/variants/minios/minios_module.c`)
that exposes kernel services: `time_ms()`, `rtc()`, `fb_info()`, `vol()`,
`pal()`, `pcspeaker()` and `run()`. `run(path, args, redirect)` invokes the
kernel `SYS_SPAWN` (215) boundary, which runs a ramdisk program from the
interpreter while preserving it, so scripts can chain toolchain commands.
Three scripts on the ramdisk use this:

```
miniOS> micropython src/build.py          # minigcc -> ld -> run, every target
miniOS> micropython src/shell.py          # pybash: variables, capture, run
miniOS> micropython src/test.py           # in-OS test suite (kernel + toolchain)
```

`build.py` orchestrates the self-hosted toolchain (ET_REL `minigcc.o` and
`ld.o` run at ring 0 via `SYS_SPAWN` and work), `shell.py` is a Python shell
layer with variables and output capture, and `test.py` verifies the kernel
bindings and the toolchain from inside the machine.

Build from source:

```bash
make sources          # clones micropython if missing
make                  # builds mpy-cross, the unix port, and packs the ELF
```

The variant files live in `progs/micropython/variants/minios/`; the build
runs entirely on the host and copies the resulting ELF into `progs/bin/`.

## TopoGPT3

MiniOS ships TopoGPT3 as a static Linux ELF at ring 3. TopoGPT3 is a 24.5M
parameter complex-valued autoregressive language model for code, built with
quaternion-inspired spectral operators and a Mixture-of-Experts transformer.
The C inference engine is a self-contained single-file implementation (~2000
lines) that loads flat binary weight files and runs the full forward pass:
GQA attention with RoPE, sliding window, RMSNorm, SwiGLU MoE with top-2
routing, and quaternion torus spectral layers.

```
miniOS> topogpt3 -w topogpt3.fp16 -v vocab.bin -p "def fibonacci(n):" -n 30
miniOS> topogpt3 -w topogpt3.fp16 -v vocab.bin -i
```

The engine supports three operating modes: headless (`-p` for a single
prompt), interactive (`-i` for a REPL-style session), and file-based (`-f` to
read a prompt from a file). The interactive mode provides commands for
adjusting temperature, top-k, repetition penalty, and max tokens at runtime.

Interactive session example:

```
miniOS> topogpt3 -w topogpt3.fp16 -v vocab.bin -i

TopoGPT3 Inference Engine
Model: small (d=256, heads=8, layers=6, kv=2)
Loading weights from: topogpt3.fp16
Loaded vocab: 50257 tokens (321428 bytes)
Loading 380 tensors (fp16 v2)...
  Layer 0 loaded
  ...
Weights loaded successfully (fp16).
Ready.

interactive mode. /help for commands.
> def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
    return arr

> /temp 0.1
Temperature set to 0.10

> /topk 20
Top-k set to 20

> /status
Model: small (d=256, heads=8, layers=6, kv=2, experts=4, topk=2)
Context: 32 tokens
Parameters: temp=0.10 topk=20 rep=1.10 max=256

> /quit
```

Interactive mode commands:

| Command | Purpose |
|---------|---------|
| `/help` | show available commands |
| `/quit` | exit interactive mode |
| `/clear` | clear the prompt buffer |
| `/temp N` | set temperature |
| `/topk N` | set top-k |
| `/rep N` | set repetition penalty |
| `/newtokens N` | set max new tokens |
| `/status` | show current settings and model info |

The binary is built with the host toolchain (`gcc -static -no-pie`) and
placed at `bin/topogpt3.elf` on the MiniFS. The model weights
(`topogpt3.fp16`, 47 MB) and vocabulary (`vocab.bin`, 422 KB) are also
shipped on the MiniFS.

Weight loading supports two formats, auto-detected at load time: float32
(`TG3W`, 94 MB) and float16 (`TG16`, 47 MB). The float16 format is used for
MiniOS to keep the filesystem footprint small.

Performance depends on the execution environment:

| Platform | Speed |
|----------|-------|
| Linux host (KVM) | 17-29 tok/s |
| MiniOS QEMU (no KVM) | 0.80 tok/s |
| MiniOS QEMU (with KVM) | 17-29 tok/s |

Build from source:

```bash
make progs/bin/topogpt3.elf    # compile the C engine
make minifs.bin                 # rebuild MiniFS with weights + vocab
make os.img                     # rebuild the full disk image
```

The source lives in `progs/topogpt3/topogpt3.c` with the weights and
vocabulary alongside it. The `convert_weights_minios.py` script in the
TopoGPT3 repository converts safetensors checkpoints to the float16 binary
format.

## Security: NX and KASLR

User-mode binaries (ET_EXEC / ET_DYN) run at ring 3 with hardware
no-execute (NX) page protection. The kernel builds eager 4 KB page tables
for the whole user window and sets EFER.NXE at boot; every user page starts
non-executable and `load_exec_elf` clears NX only on the pages a program's
executable segments occupy. A program cannot execute from its stack, heap
or `.data`, a jump into a non-executable page faults and the machine
resets, never silently running shellcode (proven by the `nx.elf` probe in
the BDD suite). The kernel heap keeps its 2 MB executable pages, because
the `.o` toolchain programs execute from there at ring 0 by contract.

The kernel image's physical base is randomized per boot (KASLR). Stage 2
mixes the TSC with the CMOS clock (hours, minutes, seconds fed into
separate bytes) and slides the kernel into one of 64 aligned 2 MB slots in
`[0x6000000, 0xE000000)`. The kernel always executes at virtual `0x100000`;
the boot banner reports its randomized physical base. Disable with
`make ENABLE_KASLR=0` for deterministic physical layout.

## Integer overflow protection

`kfread` and `kfwrite` compute `size * n` before accessing the buffer. A
ring-3 program passing `size=0xFFFFFFFF, n=2` would cause the product to
wrap to `0xFFFFFFFE`, smaller than the intended allocation, bypassing the
`bytes > RD_DATA_MAX` check. Both functions now reject the call when
`n != 0 && size > ULONG_MAX / n`, returning 0 before any buffer access.

## Stack setup bounds checking

`setup_user_stack` writes argv strings downward from the stack top. Without
a bounds check, a program with many large argv entries could write below
the stack base and corrupt kernel memory. Each iteration now checks that
the string fits in the remaining space and returns NULL on overflow.
`k_exec_user` checks the return value and refuses to enter ring 3 with a
NULL stack pointer.

## Architectural abstractions

### VFS (Virtual File System)
A registration-based filesystem dispatch layer.  Filesystem drivers register
a prefix and a set of operations (`vfs_ops_t`).  The VFS layer dispatches
open/read/write to the registered driver based on path prefix matching.
The existing dual-backend (ramdisk + MiniFS) remains; the VFS layer provides
the abstraction for future filesystem additions (FAT32, EXT2) without
touching the kernel core.

### VMA (Virtual Memory Areas)
A red-black tree (`vma.c`, `vma.h`) for mmap tracking, replacing the flat
`mmap_used`/`mmap_free` arrays with O(log n) insert/find/delete. Two trees:
`vma_live_root` for active allocations, `vma_free_root` for reclaimed regions.
A static node pool (`VMA_MAX` = 4096) backs both trees and is reset on every
exec; exhaustion fails closed (returns `VMA_NIL`). The mmap syscall searches
the free tree for reusable regions before carving fresh space; munmap moves the
freed region to the free tree. Host-tested by `tests/test_vma.c` (`make
test-vma`), which asserts the red-black invariants (root black, no double-red,
equal black height, in-order uniqueness) across insert/find/delete, pool
exhaustion and full drain.

### Unified Audio API
A hardware-agnostic audio interface providing tone mode (PC speaker square
wave) and PCM streaming mode (SB16 DMA).  Ring-3 programs use these wrappers
instead of raw syscalls.

### Quake 2 decoupling
The `SYS_Q2G_SET_TITLE` syscall is renamed to `SYS_GFX_SET_TITLE` (generic
window title).  The Q2G build is conditional: skipped when the upstream
checkout is absent.  The kernel contains no Quake-2-specific logic.

### Network driver/protocol split
The rtl8139 NIC driver (`net/rtl8139.c`, `net/rtl8139.h`) is separated from
the protocol stack (`net/net.c`). The driver owns port I/O, PCI probe, TX
descriptors, the receive ring, the NIC MAC and the PIT-calibrated TSC clock;
the stack owns addressing, ARP/IP/UDP/DNS/ICMP/TCP, the sockets and the
demux. The boundary header `rtl8139.h` exposes `rtl_send`, `rtl_poll`,
`rtl_present`, `rtl_get_mac`, `rtl_iobase`, `rtl_counters`. Both sides
share the aggregate RX drop counter (`net_rx_dropped`, extern in `net.h`).

## Console scrollback

A ring of 4096 lines that scrolled off the top of the 25-row VGA screen.
Captured lazily from `vga_scroll()` and viewable with PageUp/PageDown.

- **PageUp** (`\x1b[5~` serial, or PS/2 E0-49) scrolls upward through history.
- **PageDown** (`\x1b[6~` serial, or PS/2 E0-51) scrolls downward.
- The view hides the VGA cursor; any key other than the opposite page key
  exits and re-injects that key for the readline layer.
- Internally, `sb_ring` is a kmalloc'd circular buffer of `SCROLLBACK_ROWS *
  VGA_COLS` bytes, updated every time a full row leaves the screen via
  `sb_capture_row0()`.  `SCROLLBACK_ROWS` is 4096; the ring never wraps
  silently, it drops oldest entries when full.
- Serial PageUp/PageDown work natively.  PS/2 extended keys (E0-prefixed
  make codes) are translated into the same CSI sequences (`ESC [ 5 ~`
  / `ESC [ 6 ~`) by `kbd_read()` in `kernel.c:298`, the `KEY_E0` flag
  is now tested **before** the release‑bit check so that `0xE0` is not
  swallowed by the high‑bit handler.

## Layout

| File | Role |
|------|------|
| `bootdefs.h` | every constant shared by the boot path |
| `stage1.S` | 512-byte boot sector: loads stage 2 over LBA |
| `stage2.S` | loads the kernel above 1 MB, enters long mode |
| `kernel.c` / `kernel.h` | kernel: console, heap, ramdisk, loaders, shell |
| `kernel/shell.c` / `shell.h` | shell prompt, command resolution, builtins |
| `kernel/editor.c` / `editor.h` | line editor (nano-like: status, goto, search, range listing) |
| `kernel/syscalls.c` | Linux ABI syscall dispatcher, user pointer validation |
| `kernel/redirect.c` | shell I/O redirection (`>`, `>>`) |
| `kernel/sched.c` | process management, timer ISR, desktop tick |
| `kernel/vga_fb.c` | VESA framebuffer desktop, windowed terminal, mouse, WM |
| `net/rtl8139.c` / `net/rtl8139.h` | rtl8139 NIC driver: port I/O, PCI, TX/RX, TSC clock |
| `net/net.c` / `net.h` | protocol stack: ARP/IP/ICMP/UDP/DNS/TCP, sockets |
| `net/tls.c` / `net/tls_crypto.c` / `net/tls_x509.c` | kernel TLS 1.2 client, crypto, X.509 |
| `vma.c` / `vma.h` | VMA red-black tree for mmap tracking |
| `fs/ramdisk.c` | ramdisk filesystem driver |
| `fs/minifs.c` | MiniFS filesystem driver |
| `fs/kfile.c` | unified file API (ramdisk + MiniFS) |
| `fs/vfs.c` | VFS dispatch layer |
| `fs/zip.c` | ZIP archive read/write (miniz) |
| `drivers/ide.c` | IDE PIO disk driver |
| `drivers/pcspk.c` | PC speaker driver (tone, volume) |
| `drivers/sb16.c` | Sound Blaster 16 DMA driver |
| `drivers/rtc.c` | CMOS RTC clock driver |
| `tls_roots_src/` + `mkroots.sh` | the 8 embedded CA roots and their generator |
| `tls_test.py` / `tls_test.c` | host TLS suite: vectors + full handshakes |
| `cvm_host.c` | CVM interpreter + JIT integration in MiniOS |
| `progs/lua/lua_main.c` | Lua 5.4 entry point (REPL, -e, -l, script modes) |
| `progs/lua/minios.c` | Lua bindings for MiniOS kernel services |
| `progs/topogpt3/topogpt3.c` | TopoGPT3 C inference engine (~2000 lines) |
| `progs/topogpt3/topogpt3.fp16` | TopoGPT3 float16 model weights (47 MB) |
| `progs/topogpt3/vocab.bin` | GPT-2 BPE vocabulary (50257 tokens, 422 KB) |
| `progs/` | ramdisk contents organized by kind: `objects/`, `bin/`, `cvm/`, `src/`, `asm/`, `docs/` |
| `mkramdisk.py` | packs `progs/` into the ramdisk image |
| `test_bdd.sh` / `test_http_server.py` | behavioural suite and its HTTP fixture |
| `progs/src/test_all.sh` | one-boot comprehensive non-interactive test (61 PASS) |
| `mcp/minios_mcp.py` | MCP bridge: boots the OS and exposes its console as tools |
| `mcp/test_minios_mcp.py` | unit + QEMU BDD suite for the bridge |
| `mcp/mutate_mcp.sh` | mutation testing for the bridge |
| `skills/minios/SKILL.md` | agent skill: the edit/compile/link/run workflow over the bridge |
| `mutate.sh` | mutation testing |

## Agent bridge (MCP + skill)

`mcp/minios_mcp.py` exposes a running MiniOS as MCP tools: `minios_boot`,
`minios_status`, `minios_send`, `minios_expect`, `minios_snapshot`,
`minios_write`, `minios_cat`, `minios_poweroff`. On top of the shell it adds
`minios_python` (run a ramdisk `.py` script with MicroPython) and
`minios_py_eval` (evaluate a one-liner). The server owns the QEMU
child and a pty-backed serial console; the companion skill
(`skills/minios/SKILL.md`) teaches the edit/compile/link/run workflow, so an
agent can write a C program inside the OS, build it with `objects/minigcc.o` and
`objects/ld.o`, run it and read `exit code: N`, or drive the in-OS Python
toolchain (`build.py`, `shell.py`, `test.py`) or the Lua toolchain
(`test.lua`), all without leaving the machine.

```bash
python3 -m unittest -v mcp/test_minios_mcp.py   # unit + QEMU BDD (skips without QEMU)
mcp/mutate_mcp.sh                                # every bridge mutant must die
```

The bridge is driven over stdio JSON-RPC, uses only the Python standard
library, validates every input before a byte reaches the console (path
whitelist, printable ASCII, editor line and buffer limits), and never leaks
a QEMU process: the pid file under the system temp dir reaps stale
instances and every exit path terminates the child. See `CLAUDE.md` for the
full contract.

## Pokemon on MiniOS (gb-recompiled port)

MiniOS runs a recompiled Game Boy / Game Boy Color game as a ring-3 static
Linux ELF, under the same contract as the DOOM and Quake 2 ports: host clang,
`-static -no-pie`, MiniOS syscalls instead of SDL2. The port is game-agnostic:
it works with any gb-recompiled generated project, with no per-game patches.

MiniOS-owned files live in `progs/pokemon/`:

| File | Role |
|------|------|
| `platform_minios.c` | implements the `gb_platform_*` interface on MiniOS syscalls |
| `Makefile.minios` | static build of a generated project plus the runtime |
| `minios_stubs/SDL.h` | minimal `SDL.h` so `GB_HAS_SDL2`-guarded prototypes stay visible without SDL2 |
| `fetch.sh` | clones the upstream tool (recompiler plus runtime) |
| `main-minios.patch` | additive patch: `--debug` flag in generated `main.c` |
| `runtime-audio-voice.patch` | additive patch: `gb_audio_voice()` speaker accessor over live channel state |

Upstream ships no ROMs and no pre-generated game code, so the game project is
generated locally from a ROM image you legally own:

```sh
cd progs/pokemon
./fetch.sh                    # clone https://github.com/arcanite24/gb-recompiled into upstream/
# build gbrecomp per the upstream README (cmake, ninja, SDL2 dev files), then:
upstream/build/bin/gbrecomp /path/to/your/game.gbc -o game/
```

Then build the image from the repository root:

```sh
make os.img                     # POKEMON_DIR defaults to progs/pokemon/game
make POKEMON_DIR=/path/to/game os.img   # with a project kept elsewhere
make pokemon-fetch              # clone the upstream tool only
make pokemon-clean              # remove progs/pokemon/build/
```

Without a generated project the pokemon build is skipped with a hint and
`make` otherwise works normally, including offline. When present, the ELF is
packed on MiniFS (`MINIFS_POKEMON_FILES`) and a Pokemon desktop icon is
generated (`progs/icons/pokemon.png` via `tools/gen_icons.py`).

```
miniOS> run bin/pokemon.elf      # or: click the Pokemon desktop icon
miniOS> run bin/pokemon.elf --debug
```

Video: the GB screen (160x144) renders at exact 2x (320x288), centered in the
800x360 NK back-buffer (`NK_BACKBUF_ADDR`), because the 320x200 DOOM buffer
cannot fit a 2x GB frame. The palette is a 3-3-2 RGB ramp pushed once at init
(`SYS_PALETTE`, 206); frames are presented with `SYS_NK_FRAME` (220). The
window title is set with `SYS_GFX_SET_TITLE` (223).

Controls: arrows are the D-pad, Z is A, X is B, Enter is Start, Backspace is
Select. The driver consumes raw PS/2 Set 1 scancodes (`SYS_KBD_RAW`, 207).

Audio: PC speaker, DOOM-style. The runtime mixes 44100 Hz stereo PCM, but a
syscall per sample (44k/sec) would not survive emulation, so the per-sample
callback only accumulates zero crossings and energy (integer ops, no
syscalls). Once per rendered frame the live APU voices are sampled through
`gb_audio_voice()` (enabled flag, DAC, live envelope volume, master switch;
never the raw `io[]` mirror, whose channel bits are never set on that path)
for the two square channels plus the wave channel, and played as bass pedal
plus melody arpeggio with DOOM-like busy-wait slots (6 ms bass, 5 ms melody).
The noise channel is dropped, exactly like DOOM drops the percussion channel.
The PCM energy gate (`MINIOS_AUDIO_SILENCE_E`, default 256 mean-abs) keeps
envelopes, fades and silence honest so a decayed-but-on channel can never
drone; passages with no tonal voice (noise SFX, sweep zaps) fall back to the
raw mix estimate. Clamp the tunables `MINIOS_AUDIO_SILENCE_E` /
`MINIOS_AUDIO_MIN_HZ` (40) / `MINIOS_AUDIO_MAX_HZ` (12000) in
`platform_minios.c` if music sounds wrong on your speaker.

Saves: battery RAM and RTC data persist on MiniFS as `bin/<save-id>.sav` and
`bin/<save-id>.rtc` and survive reboot, unlike ramdisk files. Writes are
direct (`fopen`/`fwrite`/`fclose`); there is no atomic temp-plus-rename
because MiniOS has no `rename` syscall yet. The runtime only persists on
clean exit, which QEMU poweroff never takes, so MiniOS flushes SRAM itself
every 60 seconds (`MINIOS_AUTOSAVE_MS`), plus on-demand full emulator
savestates: F5 or Ctrl+S saves `bin/<save-id>.state`, F8 loads it. Loads are
size-checked: a short or overlong file fails closed and flags
`persistence_load_failed`, never a partial SRAM image.

Flags: `pokemon.elf --debug` enables the serial heartbeat (off by default;
serial prints cost frame rate). All other upstream runtime flags
(`--limit-frames`, `--input`, `--dump-frames`) work unchanged. The flag
arrives through `gb_platform_set_debug()`, wired by `main-minios.patch`
(marker-gated, SDL builds untouched). Do not reintroduce argv sniffing via
`_dl_argv` in a constructor: this toolchain's loader internals do not expose
a usable vector and the old scanner faulted at startup on unrelated storage.

Known limits: the NK desktop window title says "Nuklear" (kernel-side label,
cosmetic); under QEMU-TCG without KVM the frame rate is low, prefer
`make run-kvm` when available. The ported ELF is about 88 MB, so a MiniFS
carrying Quake 2 plus Pokemon approaches the image size budget (see the
Makefile note near the MiniFS size definition).

## SMP foundation

With `-smp N` in QEMU the BSP wakes N-1 application processors (max 8) with
the standard INIT-edge / SIPI / SIPI sequence through the local APIC mapped
at `0xFEE00000`; without it the system runs single-CPU exactly as before.
Each AP runs `arch/x86/ap_entry.S` from the stub at `0x6000` (below 1 MB for
SIPI, patched with the C entry address), sets its GS base to its `cpu_t`
(`cpus[]`, LAPIC ID, `cur_pid`, syscall stack, idle and BSP flags), loads the
BSP's IDTR, arms a 100 Hz LAPIC timer (vector 32, divide-by-16, periodic) and
idles on `sti; hlt; cli` with its temporary stack at `0x78000` (below the
LAPIC PD at `0x70000`, above the syscall kernel stack; `0x80000` overlaps
that stack and cascades). APs never print during init: `kprintf` stack use
plus the timer trap frame overflows the stub stack.

`this_cpu()` reads the current `cpu_t` via GS base (`MSR_GSBASE`,
`swapgs` on syscall entry/exit so ring 3 never sees it); `current_pid` is a
macro over it, so scheduler paths operate on the correct CPU. Vector 32
checks `is_bsp`: the BSP sends PIC EOI and runs `sb16_poll`, APs send LAPIC
EOI at `0xFEE000B0`, and the context-switch path is BSP-guarded so APs never
corrupt `procs[]`. APs own no PIC, PS/2 mouse or SB16 ring. The INIT
destination shorthand "all excluding self" is bits 19:18 (`0xC0000`) with
delivery mode bits 10:8 (`0x500`); INIT is edge-triggered (`0x4000` level
assert, never `0x8000` level-trigger, which hangs QEMU 11 with uncleared
delivery status).

`spinlock.h` provides xchg spinlocks (`spin_lock`/`spin_unlock` with
interrupt disable, `spin_lock_irqsave`/`spin_unlock_irqrestore` saving
RFLAGS.IF for nesting, `spin_trylock` without touching interrupts).
`sched_lock` guards `procs[]`/`proc_count`/scheduler state, `smp_lock`
guards the AP counter and LAPIC registers; the primitives are in place for
SMP scheduling while APs still idle.

## ISR-driven desktop tick

The desktop tick (`vga_fb_mouse_tick`) is driven from the 100 Hz PIT handler
(vector 32) at `DESKTOP_TICK_INTERVAL` (default 4, i.e. 25 Hz) whenever
`user_program_active` is set, so the cursor, taskbar clock, drag and
scrollbar stay live while a ring-3 child owns the CPU. The flag is set in
`k_exec_user` before `iretq` and cleared after `klongjmp`. When clear, the
shell drives the desktop from its own idle poll as before. The PS/2 mouse
stays enabled across `k_exec_user` so IRQ12 keeps `mouse_state` fresh (field
stores are atomic; the tick or the shell is the sole reader). The `iretq`
frame uses `RFLAGS=0x202` (IF=1): with IF=0 neither the timer nor IRQ12 fires
from ring 3 and the desktop freezes.

## Window manager: minimize, restore, close

Every titled window (terminal, DOOM, Nuklear) carries minimize (`_`),
maximize (square) and close (`X`) buttons drawn and hit-tested by shared
`wm_*` helpers. Minimize hides the terminal window without losing content
(the logical ring is kept, restore repaints it); maximize toggles
fullscreen; close resets the terminal to its default geometry because the
shell cannot be closed. For a graphics window, close arms `wm_close_request`,
honoured on the child's next syscall as `exec_exit_code = 130` with
`klongjmp` on the child's own stack (never from the ISR). Fullscreen and
minimize are mutually exclusive. While minimized the window is not drawn,
wheel/drag/scrollbar are ignored, and the taskbar shows a `[]` restore
button on the far left. Shortcuts: Alt+M toggles minimize, Alt+X / Alt+Q
closes the active window. The `wm` builtin drives the same paths and reports
state over serial (`wm state`, `wm minimize`, `wm maximize`, `wm close`),
which is the BDD-observable surface.

## Shell: history, editing, resolution, completion

History: the last `SHELL_HIST_MAX` submitted commands (unknown ones included,
consecutive duplicates skipped, reboot clears). Up (`ESC [ A`, PS/2 `E0 48`)
recalls older entries, Down (`ESC [ B`, `E0 50`) moves forward to the live
line, which is preserved while scrolling. A bare or truncated ESC is
discarded, never inserted; the editor is unaffected.

Mid-line editing: Left/Right (`ESC [ C`/`D`, `E0 4B`/`4D`), Home/End
(`ESC [ H`/`F`, `E0 47`/`4F`), Delete (`ESC [ 3 ~`, `E0 53`), Backspace,
Ctrl+A/E (start/end), Ctrl+U/K (kill to start/end), Ctrl+W (kill word).
Inserts shift the tail; a framebuffer block cursor tracks the position and
every operation repaints so display and serial agree. The escape reader polls
a bounded number of spins for the final byte so a serial-split sequence is
not mis-parsed, and never hangs.

Resolution order is fixed: builtin, registered program, then one
runnable-file resolver (`shell_run_any`, `shell_resolve_run`), so `run` and
bare names behave identically. Suffix picks the directory (`shell_run_dirs`):
`.cvm` to `cvm/`, `.o` to `objects/`, `.elf` and bare names to `bin/`, with
cwd first and the remaining directories as fallback. Names containing `/`
resolve against the cwd. Every candidate must be a real file
(`ramdisk_open` succeeds, directories rejected); overlong full paths are
skipped, never truncated. Content classifies the loader: `ET_REL` via
`k_run_rel` at ring 0, `ET_EXEC`/`ET_DYN` via `k_exec_user` at ring 3, `.cvm`
via the on-demand `objects/cvm.o` interpreter. Unresolvable names report
`command not found` (bare) or `run: not found` (with `run`).

TAB completes from registered programs and ramdisk names: first TAB fills the
longest unambiguous prefix, second TAB on a unique match fills the whole
name, ambiguous prefixes list candidates. Completion is bounds-checked
against the command buffer.

`sh <script>` runs sequential lines with `#` comments. `load <file>` loads an
ELF (`.o` relocatable or Linux executable) without running it.

## Filesystem: names, MiniFS fallback, unified opens

Ramdisk names are at most `RAMDISK_FNAME_LEN - 1` chars; `/` is data (that is
how `bin/cp` directories are expressed). `mkramdisk.py` derives each name
from the path relative to the shared parent, so `progs/src/cp.c` ships as
`src/cp.c`. Overlong names and collisions are build errors, never silent
truncations. `mkdir` creates a directory as an empty file named `<name>/`
(parent must exist; existing name is a diagnostic). `rm` refuses trailing-`/`
directories. `ls [dir]` merges ramdisk and MiniFS at root and prefers
ramdisk below root. `cat` concatenates (`cat a b > c`). `kfopen` checks the
ramdisk first, then MiniFS, and refuses directory names. All resolution goes
through one choke point against the cwd (leading `/` is root, `..` pops);
unfitting names are rejected like missing files.

Writes fall back to MiniFS: a write goes to the ramdisk only when its parent
directory entry exists there; otherwise (for example `> asm/_t.s` or
`tmp/...`) `kfopen` creates the parent chain with `minifs_mkdir_p`,
creates the file with `minifs_create`, writes with `minifs_write` and
persists bitmaps with `minifs_sync` on close. `fstat`/`access`/`unlink`
cover MiniFS-backed files too.

## User isolation and syscall boundary

`ET_EXEC`/`ET_DYN` run at ring 3 (CS `USER_CODE_SEL`, SS `USER_DATA_SEL`)
entered by `iretq` on a user stack carved from the top of the user window,
with `rdi`/`rsi`/`rdx` zeroed at entry so glibc `_start` sees `rtld_fini`
NULL. `ET_REL` stays a ring-0 kernel extension by contract. The user window
is eager 4 KB pages with EFER.NXE on: every page starts NX-clear and
`load_exec_elf` clears NX only under executable segments, so stack, heap,
`.data` and unmapped space never execute (a stray fetch faults and resets,
proven by `cpl.elf`, `kmem.elf`, `nx.elf`). The kernel heap keeps 2 MB
executable pages for `.o` execution. Tables live at `PT_USER_TABLES_ADDR`
(`0x10000`), below the kernel image, never in the heap. Syscalls switch to a
dedicated kernel stack (`SYS_KSTK_TOP`) and return with `sysretq`. Every
pointer argument must lie in the user window and strings must be
NUL-terminated inside it, or the call returns `-EFAULT`; `arch_prctl`
accepts only canonical bases. `brk` is capped below the user stack and
`mmap` carves from the same window, so every obtainable address is a user
page. Faulting user code resets (no IDT); scheduling is separate. The single
layout source is `progs/minios_abi.h` (`MINIOS_ABI_VERSION`,
`MINIOS_ABI_CHECKSUM`, canonical `MINIOS_SYS_*` numbers 0-199 Linux, 200-299
MiniOS, 300+ reserved); `kernel.c` static-asserts its derived constants
against it. Never hardcode a layout address elsewhere.

## Proving a game renders: `gfx frames`, autoquit, `boot_run.sh`

A game that launches is not proof it plays. The kernel counts every
`SYS_DOOM_FRAME` / `SYS_NK_FRAME` composite (`gfx_frames_composited`) and
the `gfx frames` builtin reports it over serial. The check is: read the
counter, run the game, read it again, assert it climbed.

```sh
tools/boot_run.sh "cmd1" "cmd2" ... [--timeout N] [--log FILE]
```

`boot_run.sh` boots `os.img`, drives the shell over the serial console,
appends `poweroff`, and captures the transcript (exit 0 on clean poweroff,
124 on timeout; stale guests are reaped first so the image lock is free):

```
tools/boot_run.sh "lua src/test.lua"
tools/boot_run.sh "gfx frames" "run doomgeneric.elf mini_autoframes 150" "gfx frames"
tools/boot_run.sh "gfx frames" \
  "run bin/quake2generic.elf +set basedir . +set minios_autoframes 400" "gfx frames"
```

Headless autoquit (default is interactive play): DOOM
`run doomgeneric.elf mini_autoframes 150` renders 150 attract-loop frames
then `exit(0)` (parsed in `DG_Init`; avoids the `-timedemo` path whose
bundled demos mismatch and fault headless); Quake 2
`run bin/quake2generic.elf +set basedir . +set minios_autoframes 400`
renders 400 frames then `Sys_Quit()`. Quake without a `demo1.bsp`-carrying
pak still climbs the counter from the loading screen and quits cleanly.
DOOM `I_Error` calls `exit(-1)` instead of spinning, so a missing WAD
returns to the shell instead of hanging.

## MCP marketplace and test tool

Beyond the console tools (`minios_boot`, `status`, `send`, `expect`,
`snapshot`, `write`, `cat`, `poweroff`, plus `minios_python` for a ramdisk
script and `minios_py_eval` for a one-liner), the bridge ships a reusable
harness and a package flow. `minios_test` sends shell commands and asserts
each `expect` marker appears and each `refute` marker does not, returning
`{pass, failures, transcript}` so sessions never hand-roll boot-and-assert
scripts. `minios_addons` lists `addons/*.yaml` with installed state;
`minios_install <name>` boots if needed, clones `repo_url`, uploads each
`files` entry through the editor (split to 512-line parts with sub-128-char
lines, reassembled with one `cat` per part and byte-checked modulo the
trailing newline; overlong lines rejected up front), runs the `build` lines
and asserts the `verify` exit codes. Success records the addon in the in-OS
registry `var/lib/addons.txt` and a host state file; failure aborts without
recording and removes upload parts. The YAML dialect is a strict stdlib-only
subset (whitelisted keys, bounded names, validated `dst`, printable-ASCII
lines); the host shell is never invoked. The marketplace ships `cp` and
`freedom` (the freedom addon rebuilds the browser inside the OS from git as
the end-to-end dogfood, driven by `mcp/mcp_dogfood.py` over stdio JSON-RPC).

## QEMU guest agent channel (COM2)

The kernel exposes a QEMU guest agent style channel on COM2 (ISA `0x2F8`,
IRQ 3, 115200 baud 8N1, FIFO `0xC7`, MCR `0x0B`). `qga.c`/`qga.h` frame one
JSON request per line; overlong lines past `QGA_LINE_MAX` (512, NUL
included) are rejected fail-closed and replies are capped at
`QGA_RESP_MAX` (2048, base64 for file reads). `tools/qga_client.py` speaks
it from the host (`qga_client.py guest-ping`,
`qga_client.py guest-exec '{"path":"..."}'`, `--sock` or `MINIOS_GA_SOCK`
overriding `/tmp/minios-ga.sock`), including the framing QEMU's own
`guest-agent-command` uses; `tools/qga_test.sh` exercises it. Wire the host
side with a QEMU chardev/socket mapped to COM2.

## Boot path, memory map, KASLR

Two stages because one correct stage does not fit in 512 bytes; every
address, BIOS service, descriptor and control bit lives in
`arch/x86/boot/bootdefs.h` with no bare constants in either stage. `stage1.S`
verifies INT 13h extended (LBA) support, reads stage 2 and jumps to it
(`.org`-guarded to the sector). `stage2.S` enables A20 (clearing the
fast-reset bit before port `0x92`), streams the kernel in 64 KB chunks
through the staging buffer at `0x10000`, copies each chunk above 1 MB via a
short protected-mode excursion (loop state in memory, never registers), builds
page tables (identity 2 MB leaves for the first gigabyte, low 4 MB split
into the `PT0`/`PT1` KASLR scheme), enables PAE and long mode, installs the
64-bit GDT at `0x8000` and jumps to `0x100000` (`KERNEL_SECTORS` comes from
the `kernel.bin` size; LBA constants from `bootdefs.h`). Disk layout: LBA 0
stage 1, LBA 1-8 stage 2, LBA 9+ kernel image with embedded ramdisk. VESA is
probed before long mode kills BIOS video (800x600x8, then 640x480x8, then
Mode 13h fallback) into the struct at `VBE_INFO_ADDR` (`0x7E20`); the kernel
maps that framebuffer at `FB_ADDR`.

Low memory is a fixed jigsaw: page tables at `0x1000-0x4FFF`, user page-table
zone `0x10000` (64 KB, below the kernel link base so code, data and `.bss`
can never reach it), GDT at `0x8000`, stage 2 at `0x9000`, syscall kernel
stack below `0x88000`, AP stub stack at `0x78000`, kernel image at virtual
`0x100000` (must end below `0x400000`, asserted at boot), user load base
`0x400000`, heap from `0x0C000000`. Never move the user-table zone above
`0x100000`; if the image outgrows `KASLR_IMAGE_SPAN` (3 MB), grow the span,
the KASLR `PT1` mapping and the link layout together.

KASLR (default on, `make ENABLE_KASLR=0` disables) keeps virtual `0x100000`
but randomizes the physical base: stage 2 mixes TSC with CMOS hours/minutes/
seconds in distinct bytes and picks one of 64 aligned 2 MB slots. The banner
reports the base and the BDD suite asserts it is never `0x100000`. `.bss`
relies on QEMU-zeroed RAM (NOBITS, no loader fill).

## Validation gate, governance, libraries

Every change must pass, in order: `make` (zero warnings),
`sh src/test_all.sh` (61 PASS), `./test_bdd.sh` (full serial suite),
`./tools/test_codecs.sh` (lzss/lz4/aes roundtrips, pass=3), `./mutate.sh`
(every kernel/boot mutant killed; survivors mean a missing scenario, and only
provably equivalent mutants may leave the set), `make test-tls` (host crypto
vectors plus OpenSSL-driven full handshakes and the negative set),
`make test-vma` (host red-black invariants, exhaustion, drain),
`python3 -m unittest -v mcp/test_minios_mcp.py`, and `mcp/mutate_mcp.sh`.
Methodology is SDD (spec in `CLAUDE.md` first), TDD (failing scenario first),
BDD (`test_bdd.sh` over the serial console), mutation testing, and the Boy
Scout rule (debt and security defects found en route are fixed, never
deferred). `mutate.sh` path anchors for the `kernel.c` to
`shell.c`/`syscalls.c`/`vga_fb.c`/`redirect.c` decomposition are stale
(BROKEN until re-anchored); the `arch/x86/boot/`, `net/`, `drivers/`, `fs/`
drift is already fixed.

Governance gates (`ARCH_POLICY.yaml`): `tools/check_cohesion.py` (community
cohesion floor), `tools/check_complexity.py` (kernel symbol budget),
`tools/check_surprising.py` (long-hop coupling), `tools/check_kb_sync.py`
(knowledge-base sync).

Library policy: a library lands only if it fits the freestanding kernel
(integer-only, no POSIX, allocator/libc redirected through macros) or runs
at ring 3 as an unmodified static ELF. Accepted: miniz 3.0.2 (ZIP builtins),
dlmalloc 2.8.6 (kernel heap mspace, `ONLY_MSPACES`, no `MORECORE`/`MMAP`
growth, `objects/dlmalloc.o` selftest), stb_image (vendored; kernel keeps its
8x8 bitmap font because the header is float-heavy and the kernel builds
`-mno-sse -mno-mmx`, so a font swap would rasterize on the host at build
time). Rejected: linenoise (POSIX line editor; the prompt implements editing
natively), libgit2 (pthreads/OpenSSL/POSIX surface; a future git client would
be a minimal wire client, not a port).

## Make targets

| Target | Purpose |
|--------|---------|
| `all` (default) | build `os.img` |
| `sources` | clone the missing toolchain repositories from GitHub |
| `sources-update` | pull the latest commit of each one |
| `sources-status` | show the revision each checkout is on |
| `toolchain` | build `minigcc`, `ld` and `cvm2` from those sources |
| `selfhost` | compile minigcc with minigcc, link with `ld`, verify the bootstrap fixed point |
| `test-tls` | host TLS suite: crypto vectors + full handshakes |
| `test-vma` | host VMA suite: red-black tree invariants, pool exhaustion, full drain |
| `run` | boot the image in QEMU with a display (TCG by default) |
| `run-kvm` | boot it with KVM acceleration (faster CPU, slower IDE I/O) |
| `run-headless` | boot it headless on the serial console (no GUI window) |
| `serial` / `debug` | boot the image in QEMU |
| `test` | behavioural suite |
| `test-tls` / `test-vma` | host suites (see Validation gate above) |
| `progs/bin/topogpt3.elf` | build the TopoGPT3 C inference engine |
| `progs/bin/nuklear.elf` | build the Nuklear node editor |
| `progs/bin/quake2generic.elf` | build the Quake 2 engine |
| `doomgeneric.elf` | build the DOOM engine |
| `pokemon-fetch` / `pokemon-clean` | fetch the gb-recompiled tool / remove `progs/pokemon/build/` |
| `minifs.bin` | rebuild MiniFS image (includes TopoGPT3 weights and vocab) |
| `clean` | remove every build product |

See `CLAUDE.md` for the full engineering contract.

[https://medium.com/@lazyown.redteam/because-i-can-the-most-dangerous-words-in-a-world-of-subscription-based-obedience-05f38f99cd36](https://medium.com/@lazyown.redteam/because-i-can-the-most-dangerous-words-in-a-world-of-subscription-based-obedience-05f38f99cd36)

<!-- readmenator-kb-link -->
## Knowledge Base

This project has been analyzed by [ReadMenator](https://github.com/grisuno/ReadMenator),
a zero-token polyglot static analysis tool. Analysis outputs are available:

- **[KNOWLEDGE_BASE.md](./KNOWLEDGE_BASE.md)** -- Full architecture reference with all
  classes, functions, imports, dependency graphs, UML class diagrams, security
  audit findings, community analysis, and more.
- **[readmenator-agent/](./readmenator-agent/)** -- Agent-friendly, grep-optimized index.
  - `INDEX.md` -- Quick reference: what each file does
  - `API.md` -- Public function contracts
  - `GOTCHAS.md` -- Change warnings
  - `SECURITY.md` -- Findings by severity

AI agents: Read `readmenator-agent/INDEX.md` for fast project context.
Developers: Read `KNOWLEDGE_BASE.md` for full architecture reference.
<!-- /readmenator-kb-link -->

