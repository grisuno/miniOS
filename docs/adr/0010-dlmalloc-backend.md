# ADR-0010: dlmalloc mspace as the kernel heap backend

Status: accepted

## Context

The first-fit free-list allocator was $O(n)$ per malloc/free and
fragmented on the fixed 64 MB heap, while the physical memory map could
not change.

## Decision

Private dlmalloc 2.8.6 mspace (`third_party/dlmalloc/`,
`dlmalloc_impl.c`) rooted with `create_mspace_with_base(HEAP_BASE,
HEAP_SIZE, 0)`. `ONLY_MSPACES` (no global malloc symbols: the kernel's
libc stubs stay the sole names), `HAVE_MORECORE=0` + `HAVE_MMAP=0` (the
space can never grow past the heap: exhaustion returns 0, fail closed),
`NO_MALLOC_STATS`, `ABORT` as an infinite loop.

## Consequences

Segregated bins, coalescing and lower per-allocation overhead on the
same reservation; map untouched. Ring-0 selftest `objects/dlmalloc.o`
(burst, realloc grow/shrink with copy check, zeroed calloc, neighbour
integrity, multi-MB); BDD: `dlmalloc: ok`.
