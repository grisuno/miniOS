# ADR-0007: KASLR and the low-4 MB layout contract

Status: accepted

## Context

The kernel image, `.bss` growth, user page tables, boot data and the
user window share one identity-mapped space. A page-table zone placed
at 0x300000 sat exactly where the growing `.bss` lands past 2 MB and
corrupted user page tables on every terminal line: ring-3 programs died
with `EXCEPTION 14` at "unmapped" addresses.

## Decision

KASLR (default on, `make ENABLE_KASLR=0` disables): stage 2 mixes TSC
with CMOS hours/minutes/seconds in distinct bytes and slides the image
to one of 64 aligned 2 MB slots in `[0x6000000, 0xE000000)`, reporting
the base at `BOOT_KASLR_ADDR`. The user page table zone sits at
`PT_USER_TABLES_ADDR` (0x10000), below the link base, unreachable by any
image growth. The low 4 MB split into `PT0`/`PT1` maps the whole image +
`.bss` contiguously at `[base, base+KASLR_IMAGE_SPAN)` (3 MB);
`mm_setup_protections` asserts `_kernel_end <= USER_LOAD_BASE` and `make
check-size` enforces it fail-closed at build time.

## Consequences

Entropy is boot-timing independent per byte lane; heap and user window
are unaffected. The five memory-layout hazard invariants in CLAUDE.md
are normative for any future low-memory change: never move the zone
above 0x100000, never shrink it, grow `KASLR_IMAGE_SPAN`/PT1/link
layout together.
