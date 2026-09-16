# ADR-0025: Wayland-mini session layer over any byte transport

Status: accepted (phased, ring-3 first)

## Context

Fase 1 gave the compositor tiling, pixel blit and the attach/commit
wire, but no session: nothing frames a byte stream into messages or
routes a request to the compositor state. The two references I studied
agree on the missing shape. NovaOS (`Wayland/`) lays `af_unix` transport
under `protocol` plus `server` plus `compositor` plus `surface` with a
32-client table (`client.h`: used, socket, id). Freedesktop `src/`
could not be fetched live (Anubis gate), so I take only its mechanism
from the protocol design itself: the fixed header framing, the
`wl_message` plus `wl_interface` descriptor tables, the id to object map
and the fd passing that miniOS replaces with validated pool ids. The
kernel was audited first: `pipe()` (Linux nr 22) has no handler, the
socket syscalls serve TCP only (`net/net.c` answers `-22` unless
`AF_INET` plus `SOCK_STREAM`), and there is no `AF_UNIX`, `socketpair`,
`SCM_RIGHTS` or `dup`. A live multi-process transport therefore needs
kernel work that does not exist yet.

## Decision

I split the session from the transport. The session (stream reassembly
plus request dispatch) lands now in `progs/wl/wl_mini.h`, header-only
like every `wm_*.h` contract, pure and host-tested, working over any
byte source: `wl_stream_t` reassembles split messages with a bounded
buffer (`WL_STREAM_CAP`), `wl_iface_t` carries the hand-written
descriptor tables (ten interfaces, names plus request and event counts,
no scanner at this scale), and `wl_dispatch` routes every request of
the subset to the existing `wl_comp_*` operations, fail-closed on wild
ids, unknown opcodes and truncated payloads. `wlcomp --selftest` proves
it with a synthetic session fed in two chunks split mid-header. No
layout address moves, no syscall number changes, so the ABI version
does not move.

## Transport (Fase 3, explicit later phase behind its own work)

Live bytes between processes need one of two carriers, in this order:
kernel `pipe()` (new nr 22 handler over fd-table rings with yield-spin
blocking reads, plus `poll` integration so the compositor wakes instead
of spinning), or, as a zero-kernel interim, mailbox files under MiniFS
with sequence numbers. Either carrier feeds `wl_stream_t` unchanged,
which is why the session lands first: the framing and dispatch never
depend on where the bytes came from.

## Proof

`make test-wl` pins stream split reassembly, consume, overflow refusal,
the full seven-message session, and the fail-closed set (wild id,
unknown opcode, short attach, truncated commit). Five scoped mutants
over the new paths die in `make test-wl`; the runner is
`tools/wl_scoped.sh`. The BDD strings are unchanged.

## Consequences

`freedom_wl` stays a logical client until Fase 3 gives it live bytes.
Full `xdg-shell` states, client decoration, DMA-BUF and real `AF_UNIX`
stay out of scope. The kernel stays a single-window compositor.
