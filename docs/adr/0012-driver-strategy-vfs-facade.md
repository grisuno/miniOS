# ADR-0012: Driver Strategy registry and VFS file_operations facade

Status: accepted

## Context

`hal_io.h` centralized ports but drivers kept ad-hoc logic: the kernel
knew how to read an IDE sector by calling `ide_read_sectors` directly,
so an ARM/RISC-V port would rewrite callers. The VFS already dispatched
through `vfs_ops_t` but lacked the 4.4BSD/Linux names, and `KFILE`
branched on backing store, risking an if/else cascade on every new
filesystem (Open/Closed violation).

## Decision

Strategy: `driver.h` (canonical path `include/kernel/driver.h`; lives
at the root because all MiniOS headers do) defines `block_ops_t` /
`audio_ops_t` and `device_t`. `drivers/driver.c` is a dependency-free
static registry (no heap, boot-time registration, read-only dispatch).
`ide` publishes `ide0` (block), `pcspk` publishes `pcspk0` (audio) from
their existing init paths; `drivers/block.c` consumes sectors through
`device_find("ide0")->ops` with a fail-closed direct fallback for the
pre-publish window. Facade: `file_operations` / `vnode_t` aliases over
`vfs_ops_t` / `vfs_file_t`, plus `vfs_read/write/close/fstat` in
`fs/vfs.c` that dispatch purely through `ops` with no
which-filesystem branch.

## Consequences

Porting a driver means a new ops table, never a caller rewrite; adding
a filesystem means a new table registration, never a dispatch edit.
Host-tested (`make test-driver`), kernel behavior unchanged (same
sectors, same bytes).
