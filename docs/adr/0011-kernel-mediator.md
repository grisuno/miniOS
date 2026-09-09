# ADR-0011: Kernel as Mediator (bounded contexts, thin `kernel.c`)

Status: accepted

## Context

`kernel.c` coupled memory management, scheduler, console and VFS in one
translation unit, and `ARCH_POLICY.yaml` carried a self-approved
exemption letting it exceed the 350-symbol gate ("reduction is Phase
6"). Systematic deferral of structural debt is not acceptable at thesis
level.

## Decision

Domain-Driven Design adapted to systems: `kernel.c` survives only as
the Mediator, an init orchestrator (`kmain` injects subsystem init
order) plus the position-sensitive syscall-entry trampoline, owning no
subsystem state. Execution context: `kernel/console.c` (text console,
output capture, libc name table), `kernel/sched.c`, `kernel/sync.c`;
memory: `kernel/mm.c`, `vma.c`; interface: `kernel/shell.c`,
`kernel/editor.c`, `fs/`. `ARCH_POLICY.yaml` carries no exemption: the
gate counts 2 symbols in `kernel.c`, two orders of magnitude under the
limit. Shell extraction circulars were broken with forward declarations
and the console event path (`console_getc`, `redirect_*`), not new
coupling.

## Consequences

New logic belongs in a subsystem file, never in `kernel.c`; the file
header states the bounded-context map normatively. Any future growth
past the gate fails CI without an explicit, expiring policy entry.
