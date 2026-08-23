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

## Demo

- [https://www.youtube.com/watch?v=4aHe6T0bD1o](https://www.youtube.com/watch?v=4aHe6T0bD1o)


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

Expected layout — the directory holding this repository can have any name:

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
make serial     # boots it headless on the serial console
make test       # behavioural suite (QEMU + serial console)
make selfhost   # compile minigcc with minigcc, link with ld, check fixed point
```

The image is attached as an IDE disk. The boot path uses INT 13h extended
(LBA) reads, which floppy emulation does not provide.

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
| `ls` / `cat <file>` / `echo <text>` | ramdisk browsing |
| `edit <file>` | line editor |
| `load <file>` | load an ELF (`.o` relocatable, or a Linux executable) |
| `run <name\|file> [args]` | run a program, an ELF or a `.cvm` module |
| `<cmd> [args]` | run an ELF from `bin/<cmd>`: the Linux-style command path |
| `<cmd> > <file>` | redirect command output to a ramdisk file |
| `net` / `net ping <ip>` | network status and one ICMP echo |
| `clear` / `poweroff` | console and power |

Redirection captures what the command writes, not what the shell reports
about it, so `run objects/minigcc.o p.c > asm/p.s` yields assembly a linker
can consume.

`bin/cp` is a command-path utility: `cp src/fib.c x.txt` copies a ramdisk
file without `run` or `load`. It is compiled from this repository's own
`progs/src/cp.c` through the miniGCC-to-ld chain, and the source ships on
the ramdisk as `src/cp.c`, so the utility can be rebuilt inside the OS by
the OS.

## Editor

`edit <file>` opens a line editor over a ramdisk file.

| Key | Action |
|-----|--------|
| `h` | help |
| `l` | list the buffer |
| `p N` | print line N |
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

- **Relocatable objects** (`.o`) — linked at load time against the kernel's
  libc symbol table. They run at ring 0 as kernel extensions.
  `objects/minigcc.o`, `objects/ld.o` and `objects/cvm.o` ship this way.
- **Linux executables** (`ET_EXEC` / `ET_DYN`) — static binaries run
  unmodified through the x86-64 `syscall` ABI at ring 3 under hardware
  page protection. A binary built on the host can be used simply by
  copying it onto the ramdisk.
- **CVM modules** (`.cvm`) — stack bytecode produced by `ld -f cvm` and
  executed by the cvm2 interpreter in `objects/cvm.o`.

## Ramdisk layout

The ramdisk ships organized by kind, and the shell's `ls <dir>` lists each
directory:

| Directory | Contents |
|-----------|----------|
| `objects/` | ET_REL toolchain: `minigcc.o`, `ld.o`, `cvm.o`, demo `.o` |
| `bin/` | Linux ELFs + command-path utilities (`cp`, `freedom`, probes) |
| `cvm/` | CVM modules: `fib.cvm`, `w1.cvm`, `minigcc.cvm` |
| `src/` | C sources for every program on the ramdisk |
| `asm/` | miniGCC assembly (`*.s`) for the toolchain-built programs |
| `docs/` | HTML and other documentation fixtures |

The ramdisk is flat — the `/` in a name is data, and `mkramdisk.py` derives
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
to the audio backend — `-machine pc,pcspk-audiodev=<id>` in addition to
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
at equal length — the chiptune broke-chord trick, applied so dense
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

## Security: NX and KASLR

User-mode binaries (ET_EXEC / ET_DYN) run at ring 3 with hardware
no-execute (NX) page protection. The kernel builds eager 4 KB page tables
for the whole user window and sets EFER.NXE at boot; every user page starts
non-executable and `load_exec_elf` clears NX only on the pages a program's
executable segments occupy. A program cannot execute from its stack, heap
or `.data` — a jump into a non-executable page faults and the machine
resets, never silently running shellcode (proven by the `nx.elf` probe in
the BDD suite). The kernel heap keeps its 2 MB executable pages, because
the `.o` toolchain programs execute from there at ring 0 by contract.

The kernel image's physical base is randomized per boot (KASLR). Stage 2
mixes the TSC with the CMOS clock (hours, minutes, seconds fed into
separate bytes) and slides the kernel into one of 64 aligned 2 MB slots in
`[0x6000000, 0xE000000)`. The kernel always executes at virtual `0x100000`;
the boot banner reports its randomized physical base. Disable with
`make ENABLE_KASLR=0` for deterministic physical layout.

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
  silently — it drops oldest entries when full.
- Serial PageUp/PageDown work natively.  PS/2 extended keys (E0-prefixed
  make codes) are translated into the same CSI sequences (`ESC [ 5 ~`
  / `ESC [ 6 ~`) by `kbd_read()` in `kernel.c:298` — the `KEY_E0` flag
  is now tested **before** the release‑bit check so that `0xE0` is not
  swallowed by the high‑bit handler.

## Layout

| File | Role |
|------|------|
| `bootdefs.h` | every constant shared by the boot path |
| `stage1.S` | 512-byte boot sector: loads stage 2 over LBA |
| `stage2.S` | loads the kernel above 1 MB, enters long mode |
| `kernel.c` / `kernel.h` | kernel: console, heap, ramdisk, loaders, shell, editor |
| `net.c` / `net.h` | rtl8139 driver, ARP/IP/ICMP/UDP/DNS/TCP |
| `tls.c` / `tls_crypto.c` / `tls_x509.c` | kernel TLS 1.2 client, crypto, X.509 |
| `tls_roots_src/` + `mkroots.sh` | the 8 embedded CA roots and their generator |
| `tls_test.py` / `tls_test.c` | host TLS suite: vectors + full handshakes |
| `cvm_host.c` | host glue for the CVM interpreter |
| `progs/` | ramdisk contents organized by kind: `objects/`, `bin/`, `cvm/`, `src/`, `asm/`, `docs/` |
| `mkramdisk.py` | packs `progs/` into the ramdisk image |
| `test_bdd.sh` / `test_http_server.py` | behavioural suite and its HTTP fixture |
| `mcp/minios_mcp.py` | MCP bridge: boots the OS and exposes its console as tools |
| `mcp/test_minios_mcp.py` | unit + QEMU BDD suite for the bridge |
| `mcp/mutate_mcp.sh` | mutation testing for the bridge |
| `skills/minios/SKILL.md` | agent skill: the edit/compile/link/run workflow over the bridge |
| `mutate.sh` | mutation testing |

## Agent bridge (MCP + skill)

`mcp/minios_mcp.py` exposes a running MiniOS as MCP tools: `minios_boot`,
`minios_status`, `minios_send`, `minios_expect`, `minios_snapshot`,
`minios_write`, `minios_cat`, `minios_poweroff`. The server owns the QEMU
child and a pty-backed serial console; the companion skill
(`skills/minios/SKILL.md`) teaches the edit/compile/link/run workflow, so an
agent can write a C program inside the OS, build it with `objects/minigcc.o` and
`objects/ld.o`, run it and read `exit code: N`, all without leaving the machine.

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
| `run` / `serial` / `debug` | boot the image in QEMU |
| `test` | behavioural suite |
| `clean` | remove every build product |

See `CLAUDE.md` for the full engineering contract.

[https://medium.com/@lazyown.redteam/because-i-can-the-most-dangerous-words-in-a-world-of-subscription-based-obedience-05f38f99cd36](https://medium.com/@lazyown.redteam/because-i-can-the-most-dangerous-words-in-a-world-of-subscription-based-obedience-05f38f99cd36)

<!-- readmenator-kb-link -->
## Knowledge Base

This project has been analyzed by [ReadMenator](https://github.com/grisuno/ReadMenator),
a zero-token polyglot static analysis tool. A comprehensive knowledge base is available:

- **[KNOWLEDGE_BASE.md](./KNOWLEDGE_BASE.md)** -- Architecture reference with all
  classes, functions, imports, dependency graphs, UML class diagrams, security
  audit findings, community analysis, and more.

AI agents and developers: Read `KNOWLEDGE_BASE.md` for full project context
without LLM token cost.
<!-- /readmenator-kb-link -->
