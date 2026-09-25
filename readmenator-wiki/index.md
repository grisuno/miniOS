# Second Brain

*Last synthesized: 2026-09-25 | 501 files | 13 concept pages | offline, zero tokens*

> Raw sources -> readmenator wiki -> links (Karpathy LLM Wiki Pattern, deterministic).
> Start here, then open one community page. Prefer grep over full reads.

## Vault Overview

The codebase centres on `kernel.h`, `string.c`, `doomtype.h`. Architecturally it is 5 layers, dominant utility (379 files) across 13 import-based communities. Recorded risk surface: 0 security findings and 1 dependency cycles.

Surprising tissue lives between headers (community 0), headers (community 1), headers (community 2): 17 extracted cross-community imports and 3 inferred bridges. Follow `connections.json` sorted by strength before refactoring.

Open work clusters around documentation (88% file coverage), 0 security findings, 20 taint paths, and 5 suggested exploration questions in `queries.md`.

## Stats

| Metric | Value |
|--------|-------|
| Files | 501 |
| Symbols | 10278 |
| Resolved imports | 1270 |
| Languages | S, c, h, lua, py, s, sh |
| Communities | 13 |
| Doc coverage | 88% (442/501 files) |
| Security findings | 0 |
| Estimated read cost | ~177081 tokens (chars/4, offline so $0) |

## Reading Order

1. Skim Stats and God Nodes below for blast radius.
2. Open the largest community page first, then follow Connections.
3. Use `queries.md` for the next question; log the answer there.

```
grep -rn '<keyword>' index.md community_*.md
readmenator query "<question>" --target miniOS
```

## Concept Wiki

- [headers (community 0) (33 files, cohesion 0.48)](./community_0_headers.md)
- [headers (community 1) (13 files, cohesion 0.47)](./community_1_headers.md)
- [headers (community 2) (89 files, cohesion 0.73)](./community_2_headers.md)
- [headers/arch/x86 (4 files, cohesion 0.33)](./community_3_headers_arch_x86.md)
- [headers/drivers (4 files, cohesion 0.50)](./community_4_headers_drivers.md)
- [headers (community 5) (3 files, cohesion 0.40)](./community_5_headers.md)
- [progs/doomgeneric (235 files, cohesion 0.98)](./community_6_progs_doomgeneric.md)
- [headers (community 7) (3 files, cohesion 0.67)](./community_7_headers.md)
- [headers (community 8) (3 files, cohesion 0.67)](./community_8_headers.md)
- [tools (21 files, cohesion 0.79)](./community_9_tools.md)
- [progs/src (4 files, cohesion 0.75)](./community_10_progs_src.md)
- [tests (2 files, cohesion 1.00)](./community_11_tests.md)
- [orphans (87 files, cohesion 0.00)](./community_12_orphans.md)

## God Nodes

| File | Score |
|------|-------|
| `headers/kernel.h` | 153.9 |
| `kernel/string.c` | 135.3 |
| `progs/doomgeneric/doomtype.h` | 101.4 |
| `progs/doomgeneric/doomdef.h` | 90.9 |
| `progs/doomgeneric/doomstat.h` | 84.8 |

## Strongest Connections

- 1 -> 2: depends_on (strength 0.9, EXTRACTED)
- 2 -> 3: depends_on (strength 0.9, EXTRACTED)
- 0 -> 2: depends_on (strength 0.9, EXTRACTED)
- 0 -> 1: depends_on (strength 0.9, EXTRACTED)
- 4 -> 2: depends_on (strength 0.9, EXTRACTED)
- 2 -> 6: depends_on (strength 0.9, EXTRACTED)
- 2 -> 9: depends_on (strength 0.9, EXTRACTED)
- 5 -> 2: depends_on (strength 0.9, EXTRACTED)
- 0 -> 8: depends_on (strength 0.9, EXTRACTED)
- 0 -> 3: depends_on (strength 0.9, EXTRACTED)

## Navigation Tips

- Obsidian Graph View works: every community page links back here.
- `connections.json` is machine-readable for GraphRAG pipelines.
- `REPORT.md` states what was extracted vs inferred and current limits.
- Regenerate offline: `readmenator . --rebuild` (no network, no tokens).
