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

### One-boot comprehensive test (`src/test_all.sh`)

`sh src/test_all.sh` runs the full non-interactive test suite inside a single
QEMU boot.  Every command prints a `PASS:` marker; the host runner greps the
serial log for these markers.  The script ships on the ramdisk (`progs/src/`)
and is added to both `PROGS` and `MINIFS_FILES` in the Makefile.

Categories tested (96 PASS):
- **Boot/help**: boot banner, help, clear
- **Filesystem**: ls (root, objects, bin), mkdir, cd, pwd, rm, cp
- **Redirects**: `>`, `>>` and `2>` (merged-streams alias)
- **Pipes**: `|` basic, chained, `cat` stdin terminator
- **Builtins**: echo, date, vol (set/report/reset), kbd (report/es/en), ps, trace, net, gfx, wm, fx (report, melts climb on minimize/restore), hash
- **Observability**: trace verbose, strace, ltrace, vmmap, schedtop, irqstat, bootlog, gdb, gdb-regs, gdb-dump-hex
- **Panic/VFS/clip/fork/httpd/vblk**: panic demo, mount/vfstest, clipboard set/clear, CoW forktest, httpd selftest, vblk absent-proof
- **Observability**: trace verbose, strace, ltrace, vmmap, schedtop, irqstat, bootlog, gdb, gdb-regs, gdb-dump-hex
- **Toolchain**: minigcc.o compile, ld.o link, run ELF, run CVM
- **Bare names**: ld.o, .elf, .cvm without `run` prefix
- **Self-host**: minigcc.elf compiles, ld.o links, run
- **Codecs**: lzss/lz4/aes roundtrips, error cases
- **JSON**: validate and query
- **ZIP**: hostile archive (traversal refused), host-produced archive
- **ELF programs**: lxhello, cpl, kmem, nx, mmreuse
- **CVM modules**: fib, w1
- **Lisp**: inline eval, in-OS suite
- **Selftests**: xxhash.o, dlmalloc.o
- **Heap stability**: repeated CVM runs
- **Tracing**: trace on/off during cp

Usage from host:
```bash
tools/boot_run.sh "sh src/test_all.sh" --timeout 120
strings boot_run.log | grep -c 'PASS:'   # expect 96
```

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
boots (ASLR-proof: addresses never enter the hash, only codes and data).
All fuzz maps stay inside one private 4 MB arena (per-thread partitions
plus one shared atomic page) and transient single pages, so a fault always
names a kernel bug: the oracle already proved itself when a fuzzer-side
prot confusion (treating R|X as writable) faulted exactly like a real
violation instead of passing silently. Bounded (400 ops/thread), raw
syscalls, no libc, no malloc in workers; a wedge shows up as a BDD
timeout, never a silent pass.

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
`kfree` fails loud instead of cryptic: a pointer outside
`[HEAP_BASE, HEAP_BASE+HEAP_SIZE)` reports through `panic_screen` (vector 13,
serial forensics plus framebuffer backtrace, then halt) naming the culprit,
because a wild free inside dlmalloc
surfaces far away as a poisoned-pointer `#GP` with no attribution (seen
once as a Quake 2 shutdown crash that clean headless runs never
reproduced: `minios_autoframes 400` climbs `gfx frames` 0 to 400).

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
sh src/test_all.sh  # one-boot comprehensive non-interactive suite (96 PASS)
./tools/test_bdd.sh  # all scenarios green (full interactive suite)
python3 tools/test_gui_wm.py  # QMP pixel proof: gfx survives Alt+Tab/tile, taskbar button refocuses
python3 tools/test_gui_icon_cwd.py  # QMP pixel proof: dock launch ignores shell cwd
python3 tools/test_gui_fashion.py  # QMP pixel proof: one cursor, stable frames, ESC quit
python3 tools/test_gui_gfxview.py  # QMP pixel proof: fullscreen DOOM, Alt+Enter, tile, minimize, close
./tools/test_codecs.sh   # lzss/lz4/aes roundtrips (pass=3)
./tools/mutate.sh    # every mutant killed (BDD + host TLS + host VMA + host Lisp suites)
make test-tls       # host-side crypto + full-handshake suite green
make test-vma       # host-side VMA red-black tree suite green
make test-lisp      # host-side Lisp interpreter suite green
make test-wl        # host-side Wayland-mini wire suite green (ADR-0024)
make test-freedom-wl  # Wayland-to-MiniOS mapping suite green (ADR-0019)
make test-freedomui   # real FreeDom engine backend suite green (ADR-0021)
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
