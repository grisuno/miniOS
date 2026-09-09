# ADR-0002: Port I/O HAL (`hal_io.h`)

Status: accepted

## Context

Bare port literals (`0x21`, `0xFEE000B0`, PS/2 status bits) were
scattered across the scheduler ISR path, untestable on the host and one
typo away from a silent misroute (the LAPIC ICR shorthand bug cost real
debug time: bits 19:18, not 17:16).

## Decision

`arch/x86/hal_io.h`: header-only contract centralizing every port,
command and address the timer ISR path touches, with `hal_outb/inb/outw/
inw` accessors and `hal_pic_eoi/hal_lapic_eoi` sequences. Under
`HAL_IO_HOST_TEST` the accessors log to stub counters instead of
executing privileged instructions.

## Consequences

No bare port literal remains on the scheduler ISR path. The mapping is
host-testable (`make test-hal`, mutation-covered). Further drivers
migrate port by port; this ADR is step one, ADR-0012 generalizes the
pattern to whole drivers.
