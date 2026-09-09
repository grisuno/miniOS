# ADR-0003: SMP bring-up and per-CPU state

Status: accepted

## Context

The kernel ran on the BSP only; `-smp N` left APs parked in firmware.
Enabling them requires a correct INIT-edge/SIPI/SIPI sequence, per-CPU
identity (GS base), and an ISR that knows which CPU it runs on, without
breaking the single-CPU boot contract.

## Decision

`cpu_t` in `sched.h` (LAPIC ID, `cur_pid`, stacks, BSP flag);
`MSR_GSBASE` set per CPU; AP stub at 0x6000 with its stack at 0x78000
(never 0x80000: that overlaps the syscall kernel stack and cascades
under the LAPIC ISR); edge-triggered INIT (QEMU 11 hangs on
level-triggered); ISR validates GS via `cpu_or_null` and EOIs
best-effort on failure. APs have no periodic timer of their own: their
only tick is the BSP's 100 Hz IPI broadcast.

## Consequences

`-smp N` wakes N-1 APs that run CLONE_VM threads and otherwise halt;
single-CPU boots are unchanged. BDD asserts both. Six `smp-*` mutants in
`mutate.sh` guard the ICR layout, the INIT/SIPI order, the AP EOI and
the BSP-only context-switch path.
