# Architectural Decision Records

This directory is the source of truth for *why* MiniOS looks the way it
does. `ARCHITECTURE_PLAN.md` tracks future work only; every completed
architectural decision lives here as a short record with Context,
Decision and Consequences. New major decisions add a record; the plan
never grows a retrospective section again.

Format: `NNNN-short-title.md` with Status, Context, Decision,
Consequences. Numbers are monotonic; status is `accepted` (shipped),
`proposed` (design on record, not shipped), `partially implemented`
(only some slices landed) or `superseded` (with a pointer to the
replacement).

## Index

| ADR | Title | Status |
|-----|-------|--------|
| [0001](0001-tick-listener-bus.md) | Tick listener bus (Observer) | accepted |
| [0002](0002-hal-port-layer.md) | Port I/O HAL (`hal_io.h`) | accepted |
| [0003](0003-smp-bringup.md) | SMP bring-up and per-CPU state | accepted |
| [0004](0004-smp-scaling.md) | SMP scaling: futex, per-CPU runqueues, batch, RCU-lite | accepted |
| [0005](0005-vma-red-black-tree.md) | VMA red-black tree for mmap tracking | accepted |
| [0006](0006-syscall-sanitize.md) | Syscall argument sanitization macros | accepted |
| [0007](0007-kaslr-low-memory-layout.md) | KASLR and the low-4 MB layout contract | accepted |
| [0008](0008-tls-client-scope.md) | TLS 1.2 client scope | accepted |
| [0009](0009-zip-builtins.md) | ZIP builtins over vendored miniz | accepted |
| [0010](0010-dlmalloc-backend.md) | dlmalloc mspace as the kernel heap backend | accepted |
| [0011](0011-kernel-mediator.md) | Kernel as Mediator: bounded contexts, thin `kernel.c` | accepted |
| [0012](0012-driver-strategy-vfs-facade.md) | Driver Strategy registry and VFS file_operations facade | accepted |
| [0013](0013-priority-inheritance.md) | Priority inheritance on blocking mutexes | accepted |
| [0014](0014-syscall-truthfulness.md) | Syscall truthfulness pass (FreeDom readiness Phase 0) | accepted |
| [0019](0019-freedom-wl-shim.md) | FreeDom Wayland intermediate layer and MiniFS growth | accepted |
| [0020](0020-wm-contracts.md) | Window manager header contracts (`wm_*.h`) | accepted |
| [0021](0021-freedomui-real-port.md) | Real FreeDom browser on MiniOS (DOOM/Q2G pattern) | accepted |
| [0022](0022-doomedit-pwad-snapshot.md) | Doom Map Editor with Immutable IWAD and PWAD Snapshots | proposed (design on record) |
| [0023](0023-doomedit-multi-sector.md) | Multi-Sector DoomEdit Maps Without a BSP Compiler | accepted (Phase 2 slice: real sectors, trivial BSP) |
| [0024](0024-wayland-mini.md) | Wayland-mini subset and ring-3 compositor | accepted (phased F0-F3, shim-first) |
| [0025](0025-wayland-session.md) | Wayland-mini session layer over any byte transport | accepted (phased, ring-3 first) |
| [0026](0026-wayland-mailbox.md) | Mailbox transport for Wayland-mini multiprocess windows | accepted (interim carrier, kernel pipe stays the proper one) |
| [0027](0027-pipe-carrier-tile-wm.md) | Pipe carrier and tile WM unification | partially implemented (FS layer landed, pipe deferred, heavyweight-live still open) |

The numbering skips 0015-0018: no record ever carried those numbers.

Formal analysis: [../vma-complexity.md](../vma-complexity.md) proves the
$O(\log n)$ bound claimed in ADR-0005.
