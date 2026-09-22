# Second Brain

*Last synthesized: 2026-09-22 | 486 files | 13 concept pages | offline, zero tokens*

> Raw sources -> readmenator wiki -> links (Karpathy LLM Wiki Pattern, deterministic).
> Start here, then open one community page. Prefer grep over full reads.

## Vault Overview

The codebase centres on `kernel.h`, `string.c`, `doomtype.h`. Architecturally it is 5 layers, dominant utility (374 files) across 13 import-based communities. Recorded risk surface: 0 security findings and 1 dependency cycles.

Surprising tissue lives between headers (community 0), headers (community 1), progs/pokemon: 15 extracted cross-community imports and 5 inferred bridges. Follow `connections.json` sorted by strength before refactoring.

Open work clusters around documentation (88% file coverage), 0 security findings, 20 taint paths, and 5 suggested exploration questions in `queries.md`.

## Stats

| Metric | Value |
|--------|-------|
| Files | 486 |
| Symbols | 9906 |
| Resolved imports | 1248 |
| Languages | S, c, h, lua, py, s, sh |
| Communities | 13 |
| Doc coverage | 88% (428/486 files) |
| Security findings | 0 |
| Estimated read cost | ~169813 tokens (chars/4, offline so $0) |

## Reading Order

1. Skim Stats and God Nodes below for blast radius.
2. Open the largest community page first, then follow Connections.
3. Use `queries.md` for the next question; log the answer there.

```
grep -rn '<keyword>' index.md community_*.md
readmenator query "<question>" --target miniOS
```

## Concept Wiki

- [headers (community 0) (100 files, cohesion 0.84)](./community_0_headers.md)
- [headers (community 1) (11 files, cohesion 0.46)](./community_1_headers.md)
- [progs/pokemon (4 files, cohesion 0.43)](./community_2_progs_pokemon.md)
- [headers (community 3) (3 files, cohesion 0.67)](./community_3_headers.md)
- [headers (community 4) (11 files, cohesion 0.63)](./community_4_headers.md)
- [headers/drivers (2 files, cohesion 0.33)](./community_5_headers_drivers.md)
- [headers (community 6) (3 files, cohesion 0.67)](./community_6_headers.md)
- [headers (community 7) (9 files, cohesion 0.63)](./community_7_headers.md)
- [progs/src (60 files, cohesion 0.66)](./community_8_progs_src.md)
- [tools (21 files, cohesion 0.79)](./community_9_tools.md)
- [progs/doomgeneric (175 files, cohesion 0.95)](./community_10_progs_doomgeneric.md)
- [tests (2 files, cohesion 1.00)](./community_11_tests.md)
- [orphans (85 files, cohesion 0.00)](./community_12_orphans.md)

## God Nodes

| File | Score |
|------|-------|
| `headers/kernel.h` | 141.4 |
| `kernel/string.c` | 133.3 |
| `progs/doomgeneric/doomtype.h` | 101.4 |
| `progs/doomgeneric/doomdef.h` | 90.9 |
| `progs/doomgeneric/doomstat.h` | 84.8 |

## Strongest Connections

- 1 -> 0: depends_on (strength 0.9, EXTRACTED)
- 0 -> 5: depends_on (strength 0.9, EXTRACTED)
- 0 -> 4: depends_on (strength 0.9, EXTRACTED)
- 0 -> 8: depends_on (strength 0.9, EXTRACTED)
- 7 -> 8: depends_on (strength 0.9, EXTRACTED)
- 7 -> 9: depends_on (strength 0.9, EXTRACTED)
- 7 -> 0: depends_on (strength 0.9, EXTRACTED)
- 4 -> 5: depends_on (strength 0.9, EXTRACTED)
- 0 -> 6: depends_on (strength 0.9, EXTRACTED)
- 0 -> 3: depends_on (strength 0.9, EXTRACTED)

## Navigation Tips

- Obsidian Graph View works: every community page links back here.
- `connections.json` is machine-readable for GraphRAG pipelines.
- `REPORT.md` states what was extracted vs inferred and current limits.
- Regenerate offline: `readmenator . --rebuild` (no network, no tokens).
