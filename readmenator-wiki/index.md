# Second Brain

*Last synthesized: 2026-09-30 | 524 files | 14 concept pages | offline, zero tokens*

> Raw sources -> readmenator wiki -> links (Karpathy LLM Wiki Pattern, deterministic).
> Start here, then open one community page. Prefer grep over full reads.

## Vault Overview

The codebase centres on `kernel.h`, `string.c`, `doomtype.h`. Architecturally it is 5 layers, dominant utility (395 files) across 14 import-based communities. Recorded risk surface: 0 security findings and 1 dependency cycles.

Surprising tissue lives between headers (community 0), headers (community 1), headers (community 2): 15 extracted cross-community imports and 5 inferred bridges. Follow `connections.json` sorted by strength before refactoring.

Open work clusters around documentation (89% file coverage), 0 security findings, 20 taint paths, and 5 suggested exploration questions in `queries.md`.

## Stats

| Metric | Value |
|--------|-------|
| Files | 524 |
| Symbols | 10695 |
| Resolved imports | 1321 |
| Languages | S, c, h, lua, py, s, sh |
| Communities | 14 |
| Doc coverage | 89% (464/524 files) |
| Security findings | 0 |
| Estimated read cost | ~187730 tokens (chars/4, offline so $0) |

## Reading Order

1. Skim Stats and God Nodes below for blast radius.
2. Open the largest community page first, then follow Connections.
3. Use `queries.md` for the next question; log the answer there.

```
grep -rn '<keyword>' index.md community_*.md
readmenator query "<question>" --target miniOS
```

## Concept Wiki

- [headers (community 0) (101 files, cohesion 0.77)](./community_0_headers.md)
- [headers (community 1) (22 files, cohesion 0.57)](./community_1_headers.md)
- [headers (community 2) (5 files, cohesion 0.44)](./community_2_headers.md)
- [headers/drivers (4 files, cohesion 0.50)](./community_3_headers_drivers.md)
- [progs/doomgeneric (community 4) (124 files, cohesion 0.64)](./community_4_progs_doomgeneric.md)
- [headers (community 5) (3 files, cohesion 0.67)](./community_5_headers.md)
- [headers (community 6) (18 files, cohesion 0.69)](./community_6_headers.md)
- [headers (community 7) (3 files, cohesion 0.67)](./community_7_headers.md)
- [headers (community 8) (9 files, cohesion 0.63)](./community_8_headers.md)
- [tools (22 files, cohesion 0.81)](./community_9_tools.md)
- [progs/doomgeneric (community 10) (113 files, cohesion 0.79)](./community_10_progs_doomgeneric.md)
- [progs/src (4 files, cohesion 0.75)](./community_11_progs_src.md)
- [tests (2 files, cohesion 1.00)](./community_12_tests.md)
- [orphans (94 files, cohesion 0.00)](./community_13_orphans.md)

## God Nodes

| File | Score |
|------|-------|
| `headers/kernel.h` | 164.6 |
| `kernel/string.c` | 145.3 |
| `progs/doomgeneric/doomtype.h` | 101.4 |
| `progs/doomgeneric/doomdef.h` | 90.9 |
| `progs/doomgeneric/doomstat.h` | 84.8 |

## Strongest Connections

- 1 -> 0: depends_on (strength 0.9, EXTRACTED)
- 0 -> 6: depends_on (strength 0.9, EXTRACTED)
- 2 -> 0: depends_on (strength 0.9, EXTRACTED)
- 3 -> 0: depends_on (strength 0.9, EXTRACTED)
- 0 -> 4: depends_on (strength 0.9, EXTRACTED)
- 8 -> 4: depends_on (strength 0.9, EXTRACTED)
- 8 -> 9: depends_on (strength 0.9, EXTRACTED)
- 8 -> 0: depends_on (strength 0.9, EXTRACTED)
- 0 -> 7: depends_on (strength 0.9, EXTRACTED)
- 0 -> 5: depends_on (strength 0.9, EXTRACTED)

## Navigation Tips

- Obsidian Graph View works: every community page links back here.
- `connections.json` is machine-readable for GraphRAG pipelines.
- `REPORT.md` states what was extracted vs inferred and current limits.
- Regenerate offline: `readmenator . --rebuild` (no network, no tokens).
