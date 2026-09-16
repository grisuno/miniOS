# ADR-0026: Mailbox transport for Wayland-mini multiprocess windows

Status: accepted (interim carrier, kernel pipe stays the proper one)

## Context

ADR-0025 split the session from the transport and left two candidate
carriers: kernel `pipe()` or MiniFS mailbox files. The kernel audit
stands (no `pipe()` handler, TCP-only sockets, no `AF_UNIX` or `dup`),
and the wlcomp demo proved a second gap first: it never uploaded the
hybrid palette, so every present on a true-color VBE mode expanded
through the kernel gray-ramp default and looked glitched, and it
presented once and exited, so nothing was interactive. A desktop that
only paints once is not a desktop. I fix the glitch and the dead demo
in the same phase that carries the first live multiprocess bytes,
because all three ride the same present path.

## Decision

Mailbox files are the interim carrier because they need zero kernel
changes: `open` with `O_CREAT` already creates through the MiniFS
fallback (parents auto-created), `unlink` (nr 87) and `DIR_LIST` (241)
already exist, and every ring-3 file flow (`paint` saves, `file`
assoc reads) already proves the primitives. One wire message travels
per file under `/shm/wl/<box>-<seq>.msg` with an 8-byte frame
(`WLMB` magic plus sequence); client pixels travel beside it as
`/shm/wl/<box>.raw` sized exactly `w*h` from the last attach. The
server drains at most `WL_MBOX_POLL_MAX` files per tick in sequence
order, validates every frame before dispatch, unlinks what it consumed
and skips anything short or torn for the next poll instead of dying.
One surface maps per connection (the box owns its slot), which bounds
the server to `WL_MAX_SURFACES` mailboxes with no id translation table;
the full id space stays available for the later pipe carrier, where
each connection keeps its own `wl_client_t` like NovaOS keeps its own
row. Kernel `pipe()` (new nr 22 handler over fd-table rings with
yield-spin blocking reads plus `poll` integration) stays the proper
carrier behind its own phase because mailboxes poll instead of waking
and cost one file per message.

## Compositor behaviour

`wlcomp` grows from a one-shot demo into the desktop: `--server` owns
the display through `SYS_VGA_MODE`, uploads the shared hybrid palette
before every present, drains mailboxes, focuses on click, drags the
focused surface through `wl_comp_set_rect` and quits cleanly on ESC
with the desktop redrawn behind it. `--once` drains once and exits so
scripts and the BDD suite prove multiprocess composition through the
existing `gfx frames` counter. `--client <box> <pattern>` attaches one
surface from a second process. `--clean` unlinks the directory.
Bare `wlcomp` keeps its one-shot demo and its BDD strings.

## Palette

The 768-byte hybrid palette lived in three identical copies
(`nuklear_minios.c`, `freedom_wl.c`, `freedomui_minios.c`) while the
one program that needed it most (`wlcomp`) had none. It moves to one
header, `progs/nk_palette.h`, with the three call sites kept as thin
wrappers so every existing host vector still names the same function.
`wlcomp` uploads it before every present like every other NK-window
app, which closes the truecolor glitch.

## Proof

`make test-wl` pins the mailbox filename grammar, frame roundtrip,
sequence ordering, torn-file refusal and the box to surface mapping;
`make test-freedom-wl` and `make test-freedomui` pin the wrappers
byte-identical; `tools/wl_scoped.sh` carries the new mutants. Live
proof is `wlcomp --client` plus `wlcomp --once` beside the `gfx
frames` climb, the same counter that proved every game so far.

## Consequences

Polling latency and one file per message are accepted costs of the
interim; neither shapes the protocol, so the pipe carrier reuses the
wire, the stream and the dispatch unchanged. Client decoration,
`xdg-shell` states and multi-surface connections stay out of scope.
