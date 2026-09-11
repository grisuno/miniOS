# ADR-0019: FreeDom Wayland intermediate layer and MiniFS growth

Status: accepted

## Context

FreeDom renders through Wayland with a Cairo shm buffer. MiniOS has no
Wayland, no Cairo, and no shm. The DOOM precedent shows the correct
shape: a thin ring-3 platform layer that speaks the native toolkit
subset on one side and MiniOS syscalls on the other. The browser also
needs room for assets and fonts, so MiniFS must grow. Growth must not
move memory addresses.

## Decision

**Wayland subset.** `progs/src/freedom_wl.c` owns the mapping in one
file. A Wayland surface becomes the Nuklear back-buffer window
(`MINIOS_NK_W` x `MINIOS_NK_H`). Present uses `GFX_PRESENT` with
`BUF_NK`. Title uses `GFX_SET_TITLE`. Pointer uses `SYS_MOUSE`.
Keyboard uses `SYS_KBD`. Keysyms translate from PS/2 Set 1. Dirty rects
clamp to the surface. UTF-8 sanitizes fail-closed. Every tunable lives
in `FreedomWlConfig`. Every address comes from `minios_abi.h`.

**Full browser, not a stub.** The same file is a complete graphical
browser: the FreeDom omnibox policy, HTTP/1.0 fetch over the socket
syscalls with DNS from syscall 200 and https through the shared
ring-3 TLS engine (no key material crosses ring 0, exactly like
`bin/freedom`), redirect chasing with a hop bound, chunked decoding,
an HTML to text filter over a 100x45 layout, and an input loop with
keyboard and wheel scroll. `freedom_wl <url-or-query>` browses,
`freedom_wl --once <url-or-query>` renders one frame and exits for
scripts and the BDD suite. Remote pages are hostile data: Content-Type
gates non-text bodies, every byte passes a gate before the
back-buffer, all sizes are bounded by named limits (256 KB body,
2048 lines: a 226 KB script-bloated page and the live google.com
homepage at 83 KB both render whole, never truncated).

**Shared font.** The public-domain 8x8 font lived inside
`nuklear_minios.c`. It now lives in `progs/nuklear/font8x8.c` with the
declaration already in `nuklear_minios.h`, and every NK-window program
links `NUKLEAR_PLATFORM` (rasterizer plus the one font copy):
nuklear, piano, vedit, freedom_wl. Moving it without the shared
variable broke piano and vedit at link time; the variable is the
fix, and full `make` is the guard.

**MiniFS growth.** `MINIFS_BLOCKS` moves 131072 to 196608. Disk-only
change. Memory layout derives from `minios_abi.h` and never moves with
this number. The swap reservation at end of disk shifts LBA only.

**Fifth repo.** `FREEDOM_DIR` defaults to `../FreeDom` beside miniGCC,
ld, cvm, and nuklear. `make sources` clones it when absent and never
touches an existing checkout. No absolute paths.

## Proof

Host suite `make test-freedom-wl` pins clip, frame bytes, keysym,
UTF-8, title bound, URL split, redirect resolve, filter, scroll and
status. Guest binary `bin/freedom_wl` ships on MiniFS. BDD pins
`freedom_wl --selftest` (`frame ok (800x360)`) and
`freedom_wl --once http://10.0.2.2:8899/README.txt`
(`freedom_wl: 10.0.2.2 (`) with a `refute UNIMPL` that pins the new
uname(63) handler. Live boot proves more: the README fetch
reports 3193 bytes with exit 0 and the `gfx frames` counter climbs
from 0 to 1, so the page really composited; `google.com` chases to
`www.google.com` over real TLS and renders whole. Five mutants (clip
sign, https port, title bound, keysym, uname) die in `mutate.sh`.

## uname(63), found on the way

Every static glibc binary traps uname at startup and got ENOSYS plus
a scary `UNIMPL SYSCALL 63` line. `sys_linux_uname` answers 0 with
honest MiniOS values over a validated 390-byte span, silencing every
static ELF. `MINIOS_SYS_UNAME` joins the canonical table at the true
Linux number (checksum untouched, old binaries unaffected).

## Boy-scout repairs in the mutant table

Bare double quotes do not survive the double-quoted MUTATIONS block;
the convention is escaped quotes. The new uname mutant taught this,
and the pre-existing `clock-backwards` mutant carried the same
disease (its pattern silently matched nothing at runtime). Both now
use escaped quotes and both die.

## Consequences

The FreeDom `gui/minios` backend targets this shim instead of raw
syscalls. Full Cairo, HarfBuzz, and font work stays in Phase 3 behind
new ADRs. No syscall number changes in this ADR, so the ABI version
does not move.

## Host environment note

On the build host used for this work, the first NK-window composite
readback after boot fails (`composite did not land at the window
origin` for `nuklear --selftest` and `vedit --selftest`), while a
second composite in the same boot passes. A pristine HEAD tree fails
identically, so this predates the font move and the MiniFS growth;
it smells like a first-composite state or VBE-mode timing issue in
this QEMU, not a regression. Tracked separately; the freedom_wl
scenarios do not depend on readback and pass here.
