# Second Brain

*Last synthesized: 2026-09-26 | 514 files | 10 concept pages | offline, zero tokens*

> Raw sources -> readmenator wiki -> links (Karpathy LLM Wiki Pattern, deterministic).
> Start here, then open one community page. Prefer grep over full reads.

## Vault Overview

The codebase centres on `kernel.h`, `string.c`, `doomtype.h`. Architecturally it is 5 layers, dominant utility (390 files) across 10 import-based communities. Recorded risk surface: 0 security findings and 1 dependency cycles.

Surprising tissue lives between headers (community 0), progs/doomgeneric (community 1), headers (community 2): 11 extracted cross-community imports and 9 inferred bridges. Follow `connections.json` sorted by strength before refactoring.

Open work clusters around documentation (89% file coverage), 0 security findings, 20 taint paths, and 5 suggested exploration questions in `queries.md`.

## Stats

| Metric | Value |
|--------|-------|
| Files | 514 |
| Symbols | 10516 |
| Resolved imports | 1305 |
| Languages | S, c, h, lua, py, s, sh |
| Communities | 10 |
| Doc coverage | 89% (455/514 files) |
| Security findings | 0 |
| Estimated read cost | ~180742 tokens (chars/4, offline so $0) |

## Reading Order

1. Skim Stats and God Nodes below for blast radius.
2. Open the largest community page first, then follow Connections.
3. Use `queries.md` for the next question; log the answer there.

```
grep -rn '<keyword>' index.md community_*.md
readmenator query "<question>" --target miniOS
```

## Concept Wiki

- [headers (community 0) (138 files, cohesion 0.91)](./community_0_headers.md)
- [progs/doomgeneric (community 1) (60 files, cohesion 0.67)](./community_1_progs_doomgeneric.md)
- [headers (community 2) (11 files, cohesion 0.63)](./community_2_headers.md)
- [headers/drivers (2 files, cohesion 0.33)](./community_3_headers_drivers.md)
- [headers (community 4) (9 files, cohesion 0.63)](./community_4_headers.md)
- [tools (21 files, cohesion 0.79)](./community_5_tools.md)
- [progs/doomgeneric (community 6) (175 files, cohesion 0.95)](./community_6_progs_doomgeneric.md)
- [progs/src (4 files, cohesion 0.75)](./community_7_progs_src.md)
- [tests (2 files, cohesion 1.00)](./community_8_tests.md)
- [orphans (92 files, cohesion 0.00)](./community_9_orphans.md)

## God Nodes

| File | Score |
|------|-------|
| `headers/kernel.h` | 164.2 |
| `kernel/string.c` | 139.3 |
| `progs/doomgeneric/doomtype.h` | 101.4 |
| `progs/doomgeneric/doomdef.h` | 90.9 |
| `progs/doomgeneric/doomstat.h` | 84.8 |

## Strongest Connections

- 0 -> 3: depends_on (strength 0.9, EXTRACTED)
- 0 -> 2: depends_on (strength 0.9, EXTRACTED)
- 0 -> 1: depends_on (strength 0.9, EXTRACTED)
- 4 -> 1: depends_on (strength 0.9, EXTRACTED)
- 4 -> 5: depends_on (strength 0.9, EXTRACTED)
- 4 -> 0: depends_on (strength 0.9, EXTRACTED)
- 2 -> 3: depends_on (strength 0.9, EXTRACTED)
- 5 -> 0: depends_on (strength 0.9, EXTRACTED)
- 6 -> 1: depends_on (strength 0.9, EXTRACTED)
- 1 -> 5: depends_on (strength 0.9, EXTRACTED)

## Navigation Tips

- Obsidian Graph View works: every community page links back here.
- `connections.json` is machine-readable for GraphRAG pipelines.
- `REPORT.md` states what was extracted vs inferred and current limits.
- Regenerate offline: `readmenator . --rebuild` (no network, no tokens).
