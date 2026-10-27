# Second Brain

*Last synthesized: 2026-10-27 | 594 files | 11 concept pages | offline, zero tokens*

> Raw sources -> readmenator wiki -> links (Karpathy LLM Wiki Pattern, deterministic).
> Start here, then open one community page. Prefer grep over full reads.

## Vault Overview

The codebase centres on `string.c`, `doomtype.h`, `doomdef.h`. Architecturally it is 5 layers, dominant utility (460 files) across 11 import-based communities. Recorded risk surface: 0 security findings and 1 dependency cycles.

Surprising tissue lives between headers: kernel, progs/doomgeneric: d_englsh, progs/src: 13 extracted cross-community imports and 7 inferred bridges. Follow `connections.json` sorted by strength before refactoring.

Open work clusters around documentation (89% file coverage), 0 security findings, 20 taint paths, and 5 suggested exploration questions in `queries.md`.

## Stats

| Metric | Value |
|--------|-------|
| Files | 594 |
| Symbols | 13106 |
| Resolved imports | 1399 |
| Languages | S, c, h, lua, py, s, sh |
| Communities | 11 |
| Doc coverage | 89% (528/594 files) |
| Security findings | 0 |
| Estimated read cost | ~241089 tokens (chars/4, offline so $0) |
| Large files (>256KB, maybe generated) | 1: `sign.s` |

## Reading Order

1. Skim Stats and God Nodes below for blast radius.
2. Open the largest community page first, then follow Connections.
3. Use `queries.md` for the next question; log the answer there.

```
grep -rn '<keyword>' index.md community_*.md
readmenator query "<question>" --target miniOS
```

## Concept Wiki

- [headers: kernel (137 files, cohesion 0.90)](./community_0_headers_kernel.md)
- [progs/doomgeneric: d_englsh (99 files, cohesion 0.66)](./community_1_progs_doomgeneric_d_englsh.md)
- [progs/src (86 files, cohesion 0.71)](./community_2_progs_src.md)
- [progs/doomgeneric: p_spec (69 files, cohesion 0.56)](./community_3_progs_doomgeneric_p_spec.md)
- [tools: tls_crypto (44 files, cohesion 0.78)](./community_4_tools_tls_crypto.md)
- [headers: vga_fb (20 files, cohesion 0.74)](./community_5_headers_vga_fb.md)
- [progs/doomgeneric: net_defs (13 files, cohesion 0.42)](./community_6_progs_doomgeneric_net_defs.md)
- [headers: batch (3 files, cohesion 0.67)](./community_7_headers_batch.md)
- [headers: tick (3 files, cohesion 0.67)](./community_8_headers_tick.md)
- [tools: doom_pwad (2 files, cohesion 1.00)](./community_9_tools_doom_pwad.md)
- [orphans (118 files, cohesion 0.00)](./community_10_orphans.md)

## God Nodes

| File | Score |
|------|-------|
| `kernel/string.c` | 181.8 |
| `progs/doomgeneric/doomtype.h` | 101.4 |
| `progs/doomgeneric/doomdef.h` | 90.9 |
| `kernel/syscalls.c` | 90.3 |
| `progs/doomgeneric/doomstat.h` | 84.8 |

## Strongest Connections

- 0 -> 5: depends_on (strength 0.9, EXTRACTED)
- 0 -> 2: depends_on (strength 0.9, EXTRACTED)
- 4 -> 2: depends_on (strength 0.9, EXTRACTED)
- 4 -> 0: depends_on (strength 0.9, EXTRACTED)
- 0 -> 8: depends_on (strength 0.9, EXTRACTED)
- 0 -> 7: depends_on (strength 0.9, EXTRACTED)
- 1 -> 3: depends_on (strength 0.9, EXTRACTED)
- 1 -> 2: depends_on (strength 0.9, EXTRACTED)
- 6 -> 2: depends_on (strength 0.9, EXTRACTED)
- 6 -> 1: depends_on (strength 0.9, EXTRACTED)

## Navigation Tips

- Obsidian Graph View works: every community page links back here.
- `connections.json` is machine-readable for GraphRAG pipelines.
- `REPORT.md` states what was extracted vs inferred and current limits.
- Regenerate offline: `readmenator . --rebuild` (no network, no tokens).
