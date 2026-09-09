# ADR-0009: ZIP builtins over vendored miniz

Status: accepted

## Context

The shell needed archive handling, but zlib-style code with stdio/time
dependencies cannot run in the freestanding kernel.

## Decision

Pristine upstream miniz 3.0.2 in `third_party/miniz/`, allocator
redirected to the kernel heap, stdio/time stripped (`MINIZ_NO_STDIO`,
`MINIZ_NO_TIME`), same macro-knob pattern as the stb wrapper. `zip` /
`unzip` are shell builtins (no ld stub changes), whole-file in memory
over the unified file API, validated before publishing. Entry names are
hostile data: normalized and rejected on `.`/`..`/empty components, so
a crafted archive can never write outside the target directory.

## Consequences

`etc/hostile.zip` (traversal refused) and `etc/host.zip` (reference
interops) are generated reproducibly at build time. Mutation suite kills
traversal-bypass, bad-magic-accept and skipped-finalize mutants.
