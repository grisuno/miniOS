# Second Brain

*Last synthesized: 2026-09-17 | 476 files | 9 concept pages | offline, zero tokens*

> Raw sources -> readmenator wiki -> links (Karpathy LLM Wiki Pattern, deterministic).
> Start here, then open one community page. Prefer grep over full reads.

## Vault Overview

The codebase centres on `kernel.h`, `string.c`, `doomtype.h`. Architecturally it is 5 layers, dominant utility (367 files) across 9 import-based communities. Recorded risk surface: 0 security findings and 1 dependency cycles.

Surprising tissue lives between headers (community 0), headers (community 1), progs/doomgeneric: 9 extracted cross-community imports and 11 inferred bridges. Follow `connections.json` sorted by strength before refactoring.

Open work clusters around documentation (88% file coverage), 0 security findings, 20 taint paths, and 5 suggested exploration questions in `queries.md`.

## Stats

| Metric | Value |
|--------|-------|
| Files | 476 |
| Symbols | 9616 |
| Resolved imports | 1221 |
| Languages | S, c, h, lua, py, s, sh |
| Communities | 9 |
| Doc coverage | 88% (418/476 files) |
| Security findings | 0 |
| Estimated read cost | ~163045 tokens (chars/4, offline so $0) |

## Reading Order

1. Skim Stats and God Nodes below for blast radius.
2. Open the largest community page first, then follow Connections.
3. Use `queries.md` for the next question; log the answer there.

```
grep -rn '<keyword>' index.md community_*.md
readmenator query "<question>" --target miniOS
```

## Concept Wiki

- [headers (community 0) (113 files, cohesion 0.90)](./community_0_headers.md)
- [headers (community 1) (7 files, cohesion 0.40)](./community_1_headers.md)
- [progs/doomgeneric (232 files, cohesion 0.98)](./community_2_progs_doomgeneric.md)
- [headers (community 3) (3 files, cohesion 0.67)](./community_3_headers.md)
- [headers (community 4) (9 files, cohesion 0.63)](./community_4_headers.md)
- [tools (21 files, cohesion 0.79)](./community_5_tools.md)
- [progs/src (4 files, cohesion 0.75)](./community_6_progs_src.md)
- [tests (2 files, cohesion 1.00)](./community_7_tests.md)
- [orphans (85 files, cohesion 0.00)](./community_8_orphans.md)

## God Nodes

| File | Score |
|------|-------|
| `headers/kernel.h` | 137.4 |
| `kernel/string.c` | 125.3 |
| `progs/doomgeneric/doomtype.h` | 101.4 |
| `progs/doomgeneric/doomdef.h` | 90.9 |
| `progs/doomgeneric/doomstat.h` | 84.8 |

## Strongest Connections

- 1 -> 0: depends_on (strength 0.9, EXTRACTED)
- 0 -> 2: depends_on (strength 0.9, EXTRACTED)
- 4 -> 2: depends_on (strength 0.9, EXTRACTED)
- 4 -> 5: depends_on (strength 0.9, EXTRACTED)
- 4 -> 0: depends_on (strength 0.9, EXTRACTED)
- 0 -> 3: depends_on (strength 0.9, EXTRACTED)
- 5 -> 0: depends_on (strength 0.9, EXTRACTED)
- 2 -> 5: depends_on (strength 0.9, EXTRACTED)
- 6 -> 2: depends_on (strength 0.9, EXTRACTED)
- 0 -> 6: shares_context (strength 0.5, INFERRED)

## Navigation Tips

- Obsidian Graph View works: every community page links back here.
- `connections.json` is machine-readable for GraphRAG pipelines.
- `REPORT.md` states what was extracted vs inferred and current limits.
- Regenerate offline: `readmenator . --rebuild` (no network, no tokens).
