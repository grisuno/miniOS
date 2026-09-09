# ADR-0005: VMA red-black tree for mmap tracking

Status: accepted

## Context

`mmap`/`munmap` tracked regions in flat `mmap_used`/`mmap_free` arrays:
$O(n)$ scans on every fault-adjacent path, and the tree header
(`vma.h`) had diverged from the inline implementation it described.

## Decision

`vma.c` with the single header `vma.h`: two red-black trees (live and
free), a static `VMA_MAX` (4096) node pool reset by `vma_tree_init` on
every exec, exhaustion fail-closed (`VMA_NIL`, never overrun). `mmap`
reuses free-tree regions before carving from the cursor; `munmap`
returns regions to the free tree; SPAWN saves/restores pool and roots.
Integer-only, kernel-dependency-free.

## Consequences

`mmap`/`munmap` are $O(\log n)$; the formal proof is
[../vma-complexity.md](../vma-complexity.md). Host-tested (`make
test-vma`: red-black invariants across insert/find/delete, exhaustion,
full drain; caught and fixed a real two-child-delete color bug),
mutation-covered (`vma-*` mutants run host-side, no QEMU). Known bound:
deleted node slots are not recycled, so one process is limited to
`VMA_MAX` total tree operations per exec.
