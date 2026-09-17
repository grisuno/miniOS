# ADR-0027: Pipe carrier and tile WM unification

Status: partially implemented (FS layer landed, pipe deferred, heavyweight-live still open)

## Context

I run the Wayland-mini desktop on mailbox files under `/shm/wl` (ADR-0026).
That carrier needs zero kernel changes, and it proves live multiprocess
composition, but it polls instead of waking and it costs one file per
message plus a stray GC pass. The kernel audit still stands: no `pipe()`
handler exists, sockets serve TCP only, and there is no `AF_UNIX`,
`socketpair`, `SCM_RIGHTS` or `dup`. I also own tile geometry twice: the
kernel `wm_layout.h` family and the compositor `wl_comp_layout_tile` path
in `progs/wl/wl_mini.h`. Two owners of one rectangle set will diverge.

## Decision

I add one minimal kernel `pipe()` handler as Linux number 22 and I keep
everything else unchanged. The pipe carries the existing `wl_stream_t`
frames byte for byte, so the wire, dispatch, iface, attach, commit, ev
and scaler contracts do not move. Mailbox files stay as the zero-kernel
fallback. Syscalls 243/244/245 stay reserved outside the checksum until
the kernel answers them, and number 22 joins the checksum only when the
handler lands, with the ABI version bumped once at that point.

I unify geometry the other way round from what one might expect: the
kernel `wm_geom.h` stays the single source of rectangles and the
compositor delegates to it. `WL_SURF_MAX_W/H` become call-site derivations
of `MINIOS_NK_W/H` from `progs/minios_abi.h`, never independent bounds.
Odd-width remainder goes right, matching the kernel tile rule, so both
tilers produce the same plan for the same frame.

## Pipe contract

The handler answers Linux `pipe()` number 22 with two fds backed by one
bounded kernel ring per pipe. Writes that fit never block. Reads sleep on
yield while empty and return available bytes otherwise. A full write
returns what fits or a short count, never a silent drop. Both fds validate
through the existing `SANITIZE_*` boundary and reject kernel addresses
with `EFAULT`. The fd table stays shared in this phase; per-process tables
arrive as their own phase because they change every spawn path.

## Layout contract

One surface fills the frame. Two split vertically. Three or more form a
grid with the remainder absorbed by the last row. Minimized and unmapped
surfaces skip hit, tile and composite. The focused surface paints its
title bright. These rules already hold in both tilers; after this ADR
they hold in one implementation with two thin callers.

## Input contract

Kernel `WM_COMBOS` stays the single combo table. The server keeps its
Alt-held shortcuts (`Alt+T/M/U/Q`) and the `.ev` frame keeps its queued
scancode batch with clear-after-write semantics. A lost `.ev` is a lost
frame, never a replay. Sequence numbers detect the loss.

## Test surface

Host `make test-wl` owns wire, layout, chrome, scaler, stream, mailbox
and palette vectors. This ADR adds odd-width tile, degenerate frame and
ev-title refusal vectors there. Live proof stays `wlcomp --server` with
two NK clients, `gfx frames` climbing, focus by click, and the scoped
`tools/wl_scoped.sh` mutants dying. Full `mutate.sh` and `test_bdd.sh`
run once at the end of the todo list.

## Consequence

I remove one geometry owner, one polling carrier on the hot path, and the
duplicated syscall define that this phase found (`MINIOS_SYS_READLINK`
was defined twice). I gain wake-based client bytes and one tile plan.
Functionality never shrinks: mailbox fallback, demo mode, selftests and
BDD strings stay intact.

## Implementation report

I landed the FS half and deferred the pipe half, because live debugging
showed the TLS base was the layer actually killing multitask, not the
carrier. Per-proc `fsbase` rides `switch_to`/`switch_to_notrap` plus the
preempt park (`headers/sched.h`, `arch/x86/ctx_sw.S`, `kernel/sched.c`);
the fault dumper prints `fs=`. The pipe stays reserved (nr 22, syscalls
243/244/245 outside the checksum) since the mailbox carries live bytes
fine at this scale. Odd-width tile and ABI-drift vectors landed in
`tests/test_wl.c`. `progs/src/spin.c` is the tiny live publisher that
proves concurrent multitask (server plus two live clients, both exit
43, 36 presents, `server done (2 surfaces)`). A `wlcomp --live` mode
was built for the same role and then removed: the 800 KB binary dies
at entry beside a running server exactly like `paint`, so it proved
nothing the tiny client does not, and dead code stays deleted.
Big glibc live clients remain the open layer (entry NX fetch with
`fs=0`, entry bytes intact at load): first-schedule/entry under
constant tick plus concurrent MiniFS traffic, not TLS and not the
Wayland wire. The `Makefile` gained the missing `kernel.o: sched.h`
dependency (a stale `kernel.o` kept the old `PROC_T_SIZE` in the
syscall-entry trampoline while `sched.o` moved on, hanging every
spawned child in its first syscall with no diagnostic).
