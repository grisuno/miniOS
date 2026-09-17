# Second Brain

*Last synthesized: 2026-09-17 | 478 files | 13 concept pages | offline, zero tokens*

> Raw sources -> readmenator wiki -> links (Karpathy LLM Wiki Pattern, deterministic).
> Start here, then open one community page. Prefer grep over full reads.

## Vault Overview

The codebase centres on `kernel.h`, `string.c`, `doomtype.h`. Architecturally it is 5 layers, dominant utility (369 files) across 13 import-based communities. Recorded risk surface: 0 security findings and 1 dependency cycles.

Surprising tissue lives between headers (community 0), headers (community 1), headers (community 2): 13 extracted cross-community imports and 7 inferred bridges. Follow `connections.json` sorted by strength before refactoring.

Open work clusters around documentation (88% file coverage), 0 security findings, 20 taint paths, and 5 suggested exploration questions in `queries.md`.

## Stats

| Metric | Value |
|--------|-------|
| Files | 478 |
| Symbols | 9650 |
| Resolved imports | 1227 |
| Languages | S, c, h, lua, py, s, sh |
| Communities | 13 |
| Doc coverage | 88% (420/478 files) |
| Security findings | 0 |
| Estimated read cost | ~165206 tokens (chars/4, offline so $0) |

## Reading Order

1. Skim Stats and God Nodes below for blast radius.
2. Open the largest community page first, then follow Connections.
3. Use `queries.md` for the next question; log the answer there.

```
grep -rn '<keyword>' index.md community_*.md
readmenator query "<question>" --target miniOS
```

## Concept Wiki

- [headers (community 0) (97 files, cohesion 0.83)](./community_0_headers.md)
- [headers (community 1) (11 files, cohesion 0.46)](./community_1_headers.md)
- [headers (community 2) (3 files, cohesion 0.40)](./community_2_headers.md)
- [progs/doomgeneric (community 3) (59 files, cohesion 0.69)](./community_3_progs_doomgeneric.md)
- [headers (community 4) (3 files, cohesion 0.67)](./community_4_headers.md)
- [headers (community 5) (10 files, cohesion 0.33)](./community_5_headers.md)
- [headers (community 6) (3 files, cohesion 0.67)](./community_6_headers.md)
- [headers (community 7) (5 files, cohesion 0.50)](./community_7_headers.md)
- [tools (21 files, cohesion 0.79)](./community_8_tools.md)
- [progs/doomgeneric (community 9) (175 files, cohesion 0.95)](./community_9_progs_doomgeneric.md)
- [progs/src (4 files, cohesion 0.75)](./community_10_progs_src.md)
- [tests (2 files, cohesion 1.00)](./community_11_tests.md)
- [orphans (85 files, cohesion 0.00)](./community_12_orphans.md)

## God Nodes

| File | Score |
|------|-------|
| `headers/kernel.h` | 137.4 |
| `kernel/string.c` | 129.3 |
| `progs/doomgeneric/doomtype.h` | 101.4 |
| `progs/doomgeneric/doomdef.h` | 90.9 |
| `progs/doomgeneric/doomstat.h` | 84.8 |

## Strongest Connections

- 1 -> 0: depends_on (strength 0.9, EXTRACTED)
- 0 -> 5: depends_on (strength 0.9, EXTRACTED)
- 0 -> 3: depends_on (strength 0.9, EXTRACTED)
- 0 -> 8: depends_on (strength 0.9, EXTRACTED)
- 2 -> 0: depends_on (strength 0.9, EXTRACTED)
- 0 -> 6: depends_on (strength 0.9, EXTRACTED)
- 0 -> 4: depends_on (strength 0.9, EXTRACTED)
- 5 -> 7: depends_on (strength 0.9, EXTRACTED)
- 9 -> 3: depends_on (strength 0.9, EXTRACTED)
- 3 -> 8: depends_on (strength 0.9, EXTRACTED)

## Navigation Tips

- Obsidian Graph View works: every community page links back here.
- `connections.json` is machine-readable for GraphRAG pipelines.
- `REPORT.md` states what was extracted vs inferred and current limits.
- Regenerate offline: `readmenator . --rebuild` (no network, no tokens).
