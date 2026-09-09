# ADR-0006: Syscall argument sanitization macros

Status: accepted

## Context

Audit found five handlers returning `-EFAULT` as `+14` (userland reads
success) and open-coded multiplications a hostile count could wrap past
the range check, plus TOCTOU windows between validation and use of
user arrays.

## Decision

`sanitize.h`: every MiniOS handler takes user pointers only through
`SANITIZE_*` (range, string, non-negative length, copy-in with an
explicit count-by-size wrap check), all fail-closed with `EFAULT`
(-14). `SANITIZE_COPY_IN` copies into kernel memory before use.
Boundary rule: sanitize at the boundary, trust internally. Region-typed
validation (heap vs stack vs mmap) is deferred: it needs a region-mask
redesign plus tagging at load/brk/stack setup first.

## Consequences

`grep SANITIZE_` lists every sanitized entry point. Host-tested (`make
test-sanitize`, mutation-covered).
