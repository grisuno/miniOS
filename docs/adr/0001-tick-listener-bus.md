# ADR-0001: Tick listener bus (Observer)

Status: accepted

## Context

The 100 Hz PIT handler called periodic effects directly (`sb16_poll`,
`vga_fb_mouse_tick`). Every new effect meant editing the ISR, and the
desktop tick was chained as an else-if behind the preemption branch, so
it never ran while threads existed and the cursor froze under load.

## Decision

`tick.h` + `kernel/tick.c`: two fixed listener tables (audio, desktop),
no heap, no locks. Registration is boot-time only before `sti`;
dispatch only reads. `sched_init` registers `sched_tick_audio` and
`sched_tick_desktop`; `isr_dispatch` (vector 32) runs audio
unconditionally on the BSP and desktop when `tick_desktop_due` and
`user_program_active` hold, as an independent `if`, never chained behind
preemption.

## Consequences

New periodic effects register without touching the ISR. A null or full
registration returns -1 and changes nothing. Host-tested (`make
test-tick`, mutation-covered); live-boot proof is the SMP and sb16 BDD
scenarios.
