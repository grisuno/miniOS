# Headless harnesses, one-boot suite, in-OS suites, library assessments, host TLS gate

Moved verbatim from CLAUDE.md (2026-09-29 compaction); CLAUDE.md keeps the
rules and hazards and indexes this file.

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

### README desktop image (`tools/test_readme_shot.py`, `make readme-shot`)

The picture the README presents is a test artifact, not a hand-pasted
upload. The test boots `os.img` headless in QEMU, runs `minifetch` in the
terminal over the wallpaper, takes a QMP screendump and asserts the desktop
is really painted before publishing it: the frame is 1024x768, lit, rich in
colors, the profile-card avatar ring is bright, the terminal text is green
and the dock is lit. Only then `docs/img/desktop.png` is replaced, through a
temporary file renamed over it with mode 0644, so a black, partial or
crashed frame can never reach the README (fail-closed; exit 2 when `os.img`
or QEMU is absent, which blocks a release rather than shipping a stale
picture). `deploynator.toml` lists `make test-host` and `make readme-shot`
as the release test commands; deploynator runs tests before it stages and
commits, so every release carries the refreshed image and the README that
references it by relative path (`docs/img/desktop.png`). Thresholds live in
the `Config` class of the tool.

### One-boot comprehensive test (`src/test_all.sh`)

`sh src/test_all.sh` runs the full non-interactive test suite inside a single
QEMU boot.  Every command prints a `PASS:` marker; the host runner greps the
serial log for these markers.  The script ships on the ramdisk (`progs/src/`)
and is added to both `PROGS` and `MINIFS_FILES` in the Makefile.

Categories tested (112 PASS):
- **Boot/help**: boot banner, help, clear
- **Filesystem**: ls (root, objects, bin), mkdir, cd, pwd, rm, cp
- **Movements**: `mv` on the ramdisk, `mv` on MiniFS, missing source, existing destination
- **Redirects**: `>`, `>>` and `2>` (merged-streams alias)
- **Pipes**: `|` basic, chained, `cat` stdin terminator
- **Builtins**: echo, date, clock, vol (set/report/reset), kbd (report/es/en), ps, minifetch, trace, net (ping), gfx, wm, fx (report, melts climb on minimize/restore), hash
- **Panic/VFS/clip/fork/httpd/vblk**: panic demo, mount/vfstest, clipboard set/clear, CoW forktest, httpd selftest, vblk absent-proof
- **Toolchain**: minigcc.o compile, ld.o link, sign, run ELF, run CVM
- **Bare names**: ld.o, .elf, .cvm without `run` prefix
- **Self-host**: minigcc.elf compiles, ld.o links, sign, run
- **Codecs**: lzss/lz4/aes roundtrips, error cases
- **JSON**: validate and query
- **ZIP**: hostile archive (traversal refused), host-produced archive
- **ELF programs**: lxhello, cpl, kmem, nx, mmreuse
- **CVM modules**: fib, w1
- **Lisp**: inline eval, in-OS suite
- **Python**: `micropython src/test_py.py` (in-OS suite), static CPython 3.12, `import pip`
- **Selftests**: xxhash.o, dlmalloc.o, fptest, `file --selftest`, `paint --selftest`, `run bin/lxsel` (select/poll ABI)
- **Heap stability**: repeated CVM runs
- **Tracing**: trace on/off during cp
- **Observability**: trace verbose, strace, ltrace, vmmap, schedtop, irqstat, bootlog, gdb, gdb-regs, gdb-dump-hex

Usage from host:
```bash
tools/boot_run.sh "sh src/test_all.sh" --timeout 120
strings boot_run.log | grep -c 'PASS:'   # expect 112
```

### One-boot marker accounting

The suite prints one `PASS:` marker per scenario and the host runner counts
them in the serial log. A green boot logs **112** markers, composed of:

- 103 from `progs/src/test_all.sh` itself: 102 scenarios plus the
  `PASS: ALL-TESTS-DONE` terminator (`progs/src/test_all.sh:339`).
- 9 from the in-OS Python suite the script invokes
  (`micropython src/test_py.py`, `progs/src/test_all.sh:303`), which prints
  the same marker shape (`progs/src/test_py.py:13`). Two of its eleven
  checks (`py-uid-ok`, `py-listdir-ok`) are gated on `os.getuid` existing
  (`progs/src/test_py.py:38`); the guest MicroPython build has no
  `os.getuid`, so nine of the eleven run.

A green run prints zero `FAIL:` lines. The figures quoted in older
documents (81, 96) predate the `mv`, Python, select-ABI and self-host
scenarios and are stale.

### `mmreuse`: mmap/munmap reclaim contract

`mmreuse` (`progs/src/mmreuse.c`) is the ring-3 leak detector for the
kernel's mmap/munmap pair. It maps an 8 MB anonymous private region
(`MAP_PRIVATE|MAP_ANONYMOUS`, `PROT_READ|PROT_WRITE`), writes to it so the
mapping is really used, unmaps it, and repeats that 64 times
(`progs/src/mmreuse.c:36-43`). The verdict is the exit code; the program
prints nothing:

- exit 0: every region was reclaimed, the address space did not leak.
- exit 1: a mapping failed with ENOMEM, the downward mmap cursor drained
  and the region was never given back (the leak it guards against).
- exit 2: the unmap itself failed.

The shell surfaces it as `exit code: 0`, and the one-boot suite asserts it
as `PASS: mmreuse-ok` (`progs/src/test_all.sh:267-268`).

### In-OS test suites (Lua / MicroPython / Lisp toolchain)

`lua src/test.lua`, `micropython src/test.py` and `lisp src/test.lisp` run
the self-hosted
toolchain from inside the machine via `minios.run()` (SYS_SPAWN;
`minios-run` in Lisp). The
minigcc/ld steps now work because file writes fall back to MiniFS (see the
filesystem section): a redirect or program write into `asm/_t.s` or `tmp/...`
creates the parent directory on the real filesystem instead of being refused by
the flat ramdisk. All three files ship on the **ramdisk** (`src/test.lua`,
`src/test.py`, `src/test.lisp`), so `ls` shows them next to the other `src/` scripts; test.lua
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
intact, so a ring-3 interpreter (lua, micropython, lisp, the vedit IDE) can spawn
ET_EXEC children; the interpreter suites cover the module bindings, the
filesystem and the **ET_REL** toolchain (minigcc/ld work), and the ET_EXEC
tools stay exercised at the shell level by `tools/test_codecs.sh`, which
drives the real `lzss`/`unlzss`, `lz4`/`unlz4` and `aes`/`unaes` roundtrips
through the serial console (pass=3 in the gate).

### Syscall fuzzer (`bin/scfuzz.elf`, syzkaller spirit at BDD scale)
Two 1:1 threads (`progs/src/mthreads.h`) hammer mmap/munmap/mprotect/yield
with seeded, interleaved operation streams and fold every return code and
readback into an FNV-1a checksum; the BDD scenario pins the exact hash, so
any race, lost update or behavioral drift fails it deterministically across
boots (ASLR-proof: addresses never enter the hash, only codes and data). A
transient mapping contributes its success, its page alignment and the fact
that it does not overlap the arena, never its address, so the pinned hash
is the same on every boot.
All fuzz maps stay inside one private 4 MB arena (per-thread partitions
plus one shared atomic page) and transient single pages, so a fault always
names a kernel bug: the oracle already proved itself when a fuzzer-side
prot confusion (treating R|X as writable) faulted exactly like a real
violation instead of passing silently. Bounded (400 ops/thread), raw
syscalls, no libc, no malloc in workers; a wedge shows up as a BDD
timeout, never a silent pass.

### Linux ABI probes and diagnostics (`progs/src/lx*.c`)
Static glibc programs, each valid on Linux first (the host build must pass
before the guest run counts), each printing one `lx<name>: <check> ok` line
per point and `lx<name>: all ok`:

- `bin/lxabi` (`mrun`): process, thread, descriptor, signal, sleep, limit and
  `ioctl` ABI (docs/spec/smp-sched.md); host build:
  `gcc -static -O2 -Wall -Wextra -Werror progs/src/lxabi.c -lpthread`.
- `bin/lxsecc` (`mrun`): seccomp-bpf, prctl, `/proc/self/exe`
  (docs/spec/kernel.md).
- `bin/lxnet <ip> <port>` against `tools/test_net_fixture.py`: the socket
  ABI (docs/spec/network.md); `lxnet --dial <host> <port>` resolves through
  glibc and dials like libcurl.
- `lxtls <url>` / `lxtls --rand` (built with freedom-gui): libcurl and
  OpenSSL on their own, with the verbose transcript; run it as a job
  (`run lxtls URL &`).

When a ring-3 program misbehaves, `sclog <pid>` prints its last syscalls
from the kernel flight recorder (live or exited) without the timing change
`trace` causes, and `ps` shows the exit code of finished processes. A ring-3
crash dump carries the same log plus a census of every kernel stack slot.

### Performance and audio diagnostics (`perf`, `sbtone`, `sb16`)

Three probes answer "where did the time, and the sound, go" without a GUI:

- `perf` (shell builtin, `kernel/shell.c:2985`): three timed loops — 1M
  `nop` (raw CPU speed), 100k `ktime_ms()` calls (clock-read overhead) and
  1000 100-char `kprintf`s (console output throughput). The last line
  carries the accumulated sink so no loop can be optimised away.
- `sbtone` (ring-3, `run bin/sbtone`, ships on MiniFS): opens the SB16
  PCM sink and streams a clean 440 Hz sine (22050 Hz, 2048-byte buffers,
  about 93 ms of audio each) paced to real time over a 3000 ms window. It
  reports the submitted buffer count, the audio milliseconds and the guest
  milliseconds, and its exit code is the number of submitted buffers (0 when
  the SB16 does not open). The oracle: a clean tone with about 32 buffers in
  about 3000 ms means the SB16 driver is correct and any garbage is the
  piano's GUI; garbage audio, or a submit count far below real time, points
  at the SB16 DMA/driver.
- `sb16` (shell builtin, `kernel/shell.c:3941`): the driver counters over
  serial — presence, mode, ring free/capacity, stream count, IRQ arms, poll
  arms, submits, drops, stalls, pump fills and mixes, plus the `pcm2`
  counters (active, irqs, polls, spurious, bytes, underruns, drops, wakes).
  Ring health is observable over the console without ears.

The rest of the dissection toolbox (`trace`/`strace`/`ltrace`, `vmmap`,
`schedtop`, `irqstat`, `bootlog`, `gdb` with the `make gdb` remote hookup,
the MCP bridge and the host harnesses) is documented in
`docs/debug_tools.md`.

## Library integration assessments
A library lands in MiniOS only when it fits the freestanding kernel's rules
(integer-only, no POSIX, allocator and libc callbacks redirected through
macros like the stb/miniz wrappers) or runs at ring 3 as an unmodified
static ELF (DOOM, MicroPython, Nuklear). Candidates that pass are vendored;
candidates that do not are assessed honestly and documented here, never
silently forced in.

- **miniz 3.0.0** (ZIP read/write): accepted, shipped as `unzip`/`zip`
  builtins — see the Zip builtins section. Integer-only, allocator hooks, and
  the whole archive API works whole-file in memory. The vendored copy is
  upstream 3.0.0 (`third_party/miniz/miniz.h:4`); its `MZ_VERSION` is the
  zlib-compatibility string `11.0.2` (`third_party/miniz/miniz.h:278`), not
  the library version.
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
- **stb_image** (PNG/TGA decode): vendored, accepted and wired at runtime,
  not build-time only. `third_party/stb/stb_impl.c` compiles the pristine
  header into the kernel with the allocator and the `mem*` calls redirected
  to the kernel ones and every codec but PNG/TGA disabled (`STBI_NO_JPEG`,
  `STBI_NO_HDR`, `STBI_NO_LINEAR`, ...), so the kernel path is integer-only
  and matches the `-mno-sse -mno-mmx` build; stb's thread-locals are
  disabled because the kernel has no TLS segments. The entry points
  (`stbi_load_file`, `stbi_load_from_memory`, `stbi_image_free`) are the
  shared surface of `third_party/stb/stb_api.h`, exported through the
  kernel symbol table (`kernel/console.c:293-295`), and are used by the
  desktop wallpaper and the 32x32 dock icons (`kernel/vga_fb.c:3546`,
  `kernel/vga_fb.c:3677`) and the minifetch logo (`kernel/minifetch.c:84`);
  ring-3 programs compile the same header themselves
  (`progs/file/file.c:179`). The float-heavy, build-time-only caveat above
  belongs to stb_truetype, not to stb_image.
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
`kfree` fails loud instead of cryptic: a pointer outside
`[HEAP_BASE, HEAP_BASE+HEAP_SIZE)` reports through `panic_screen` (vector 13,
serial forensics plus framebuffer backtrace, then halt) naming the culprit,
because a wild free inside dlmalloc
surfaces far away as a poisoned-pointer `#GP` with no attribution (seen
once as a Quake 2 shutdown crash that clean headless runs never
reproduced: `minios_autoframes 400` climbs `gfx frames` 0 to 400).

### Slab verdict (T6, deferred with evidence, not scheduled)
A slab/SLUB for kernel objects would cut per-allocation cost and
fragmentation, but it is optimizing the wrong layer today: the SMP
blocker is the global memory-management VIEW (`g_brk`,
`user_mmap_cur`, the VMA roots, 112 sites), not the dlmalloc lock,
and `smp-sched.md` already specs that migration (per-CPU views)
ahead of any allocator work. The dlmalloc sections are pure heap
math under one spin (short, never blocking), and every newer
subsystem (pcache, file-mmap fault paths) deliberately funnels
through the same `mm_lock` leaf discipline, which is exactly the
shape the per-CPU migration needs to visit. Revisit T6 the day a
two-CPU malloc-churn probe stops scaling: until a measurement says
otherwise, the lock is not the ceiling.

### Aligned allocation contract (`kmalloc_aligned` / `kfree_aligned`)
Page-aligned kernel buffers are allocated through `kmalloc_aligned(size,
align)` (`kernel/mm.c`), which requires a nonzero power-of-two alignment,
overflow-checks `size + align + sizeof(void *)` and stores the raw
`kmalloc` pointer in the word below the aligned base. `kfree_aligned`
releases that stored raw pointer, so an aligned buffer is always safely
freeable. `mm_page_aligned_alloc` (`kernel/mm/paging.c`) delegates to it
for the DOOM/Nuklear back-buffers; the historical untracked-raw pattern
(boot-only leak by documentation) is gone. `kmalloc_percpu` is deleted:
it had zero callers and the same untracked-aligned defect, so removal
beat repair (a future per-CPU allocator starts from `kmalloc_aligned`).


## Validation Gate (must pass before any commit)
```bash
make                # zero warnings
make lint           # cppcheck + -Wextra (ring-3) + clang-tidy curated + bash -n + abi-numbers + fork-stubs + sanitize-audit + addons, all green
sh src/test_all.sh  # one-boot comprehensive non-interactive suite (112 PASS)
./tools/test_bdd.sh  # all scenarios green (full interactive suite)
python3 tools/test_gui_wm.py  # QMP pixel proof: gfx survives Alt+Tab/tile, taskbar button refocuses
python3 tools/test_gui_icon_cwd.py  # QMP pixel proof: dock launch ignores shell cwd
python3 tools/test_gui_fashion.py  # QMP pixel proof: one cursor, stable frames, ESC quit
python3 tools/test_gui_gfxview.py  # QMP pixel proof: fullscreen DOOM, Alt+Enter, tile, minimize, close
python3 tools/test_gui_freedom.py  # QMP pixel proof: foreground run (pointer follows, no dead arrow, Ctrl+C), typing, clipboard, menu click
./tools/test_codecs.sh   # lzss/lz4/aes roundtrips (pass=3)
./tools/mutate.sh    # every mutant killed (BDD + host TLS + host VMA + host Lisp suites)
make test-tls       # host-side crypto + full-handshake suite green
make test-vma       # host-side VMA red-black tree suite green
make test-lisp      # host-side Lisp interpreter suite green
make test-wl        # host-side Wayland-mini wire suite green (ADR-0024)
make test-freedom-wl  # Wayland-to-MiniOS mapping suite green (ADR-0019)
make test-freedomui   # real FreeDom engine backend suite green (ADR-0021)
make test-freedom-gui # full FreeDom GUI port: PS/2 set 1 keymap vectors green
make test-futex test-percpu-rq test-batch test-rcu  # SMP scaling contracts green
make test-sanitize  # syscall sanitize-macro suite green
make test-tick test-hal  # tick bus + HAL port-mapping suites green
make test-driver test-sync  # device registry + sync/PI suites green
make test-pcm        # low-latency PCM ring suite green
make test-rtc        # RTC civil-date math suite green
make test-vedit      # vedit IDE build-contract suite green
make test-file       # file browser assoc-contract suite green
make test-paint      # paint canvas/PNG-contract suite green
make test-png        # shared ring-3 PNG helpers + pokemon side-art policy green
make test-doomedit   # doom PWAD writer + C/Python roundtrip green
make test-theme      # shared Nuklear theme suite green
make test-wm         # WM geometry + event translator suite green
make test-fx         # DOOM-melt column contract suite green
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

### Gate contract and ordering

`CLAUDE.md` ("Validation Gate") is the normative command list; the block
above is a snapshot of it, not the whole set. The targets it also requires
and that the snapshot omits are `make test-pipe test-panic test-pci
test-httpd`, `make test-fat test-ext4`, `make test-ktime test-randmix`,
`make test-mip test-select-map`, `make test-seccomp-bpf test-minifs-tools`
and `make test-arena test-leakcheck test-pcache`. Beyond that list,
`make uefi` builds the OVMF stub image that has to boot under QEMU
(`Makefile:2162`). `make test-host` runs the fast host unit suites in
one shot (`Makefile:2052`); it excludes `test-tls` (it drives OpenSSL
servers) and the QEMU-backed BDD/MCP suites.

The order is part of the contract: `make` (zero warnings) first, then the
one-boot suite (`sh src/test_all.sh`, 112 PASS), then the full interactive
suite (`./tools/test_bdd.sh`), then the host suites and the mutation gate.
The methodology behind that order (SDD, TDD, BDD, mutation testing, Boy
Scout) lives in `CLAUDE.md` ("Development Methodology"); this file is the
subsystem contract for the harnesses themselves.

What the host suites prove, beyond the one-line summaries above:

- `test-vma`: the VMA red-black tree invariants, pool exhaustion and a full
  drain (`tests/test_vma.c:102`, `tests/test_vma.c:136`,
  `tests/test_vma.c:153`).
- `test-lisp`: the host interpreter assertion vectors (arithmetic,
  fail-closed errors, closures, strings, files, predicates, CLI flags) plus
  the in-OS suite file in language-only mode (`tools/test_lisp.py`).
- `test-wm`: WM geometry, events, window model, render plan, tiling, focus,
  layout and gfx-view contracts (`Makefile:2033`).
- `test-fat`: the FAT32 loopback driver over a synthetic in-memory image
  (units, multi-cluster reads, fail-closed edges) (`Makefile:2077`).
- `test-wl`: the Wayland-mini wire roundtrip and fail-closed bounds
  (`Makefile:2040`).

### Governance gates (`ARCH_POLICY.yaml`)

`ARCH_POLICY.yaml` is the single source of truth for the architectural
thresholds; the gate scripts read it and fail on a regression:

- `python3 tools/check_complexity.py --policy ARCH_POLICY.yaml`: the kernel
  God-object symbol budget, 350 (`ARCH_POLICY.yaml:7`). The measured count
  today is 12 symbols (`OK (12 symbols, limit=350)`), and any growth needs
  an explicit, expiring entry in `approvals` (`ARCH_POLICY.yaml:20-25`).
- `python3 tools/check_cohesion.py`: the root-community cohesion floor,
  0.25 (`ARCH_POLICY.yaml:11`).
- `python3 tools/check_surprising.py`: the long-hop coupling floor, 5 hops
  (`ARCH_POLICY.yaml:14`).
- `python3 tools/check_kb_sync.py`: knowledge-base drift.

Caveat: the cohesion and surprising gates consume the readmenator CPG
(`KNOWLEDGE_BASE.jsonld`), a generated artifact that is not committed; with
it absent both gates print "not found, skipping" and exit 0, so they are
green no-ops until readmenator regenerates the CPG. `check_kb_sync.py` is a
no-op as well unless `--regenerate` is passed
(`tools/check_kb_sync.py:55-57`), and even then it needs
`tools/readmenator.py`, which is not in the tree.

### Mutant survival rule and anchor hygiene

A mutant that survives a full green suite is a test gap: close it with a
new scenario, never by deleting the mutant. Only a provably equivalent
mutant (no input distinguishes it, recorded in
`docs/spec/architecture.md`) may leave the set.

Anchor hygiene is what keeps the gate honest. `SOURCES`
(`tools/mutate.sh:85`) is the backup/restore allowlist, not documentation:
every file named by the mutation table must appear in it, or the mutant is
never restored, leaks into the tree and stacks under the next mutant, whose
kill is then vacuous (`tools/mutate.sh:95-99`; the `progs/paint/paint.c`
incident). `tools/check_mutant_anchors.py` (run by `make lint`,
`Makefile:1759`) verifies that every mutation expression still matches its
target file: a no-match anchor is reported BROKEN
(`tools/check_mutant_anchors.py:115`) instead of silently rebuilding
pristine sources, which would look like a test gap. The check fails closed.

A run interrupted mid-way leaves `os.img` built from the mutant: rebuild
before trusting any boot.
