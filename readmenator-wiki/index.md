# Second Brain

*Last synthesized: 2026-10-04 | 549 files | 21 concept pages | offline, zero tokens*

> Raw sources -> readmenator wiki -> links (Karpathy LLM Wiki Pattern, deterministic).
> Start here, then open one community page. Prefer grep over full reads.

## Vault Overview

The codebase centres on `string.c`, `doomtype.h`, `doomdef.h`. Architecturally it is 5 layers, dominant utility (402 files) across 21 import-based communities. Recorded risk surface: 0 security findings and 1 dependency cycles.

Surprising tissue lives between headers (community 0), arch/x86, drivers (community 2): 20 extracted cross-community imports and 0 inferred bridges. Follow `connections.json` sorted by strength before refactoring.

Open work clusters around documentation (89% file coverage), 0 security findings, 20 taint paths, and 5 suggested exploration questions in `queries.md`.

## Stats

| Metric | Value |
|--------|-------|
| Files | 549 |
| Symbols | 11646 |
| Resolved imports | 1333 |
| Languages | S, c, h, lua, py, s, sh |
| Communities | 21 |
| Doc coverage | 89% (486/549 files) |
| Security findings | 0 |
| Estimated read cost | ~206683 tokens (chars/4, offline so $0) |

## Reading Order

1. Skim Stats and God Nodes below for blast radius.
2. Open the largest community page first, then follow Connections.
3. Use `queries.md` for the next question; log the answer there.

```
grep -rn '<keyword>' index.md community_*.md
readmenator query "<question>" --target miniOS
```

## Concept Wiki

- [headers (community 0) (40 files, cohesion 0.55)](./community_0_headers.md)
- [arch/x86 (2 files, cohesion 0.50)](./community_1_arch_x86.md)
- [drivers (community 2) (12 files, cohesion 0.41)](./community_2_drivers.md)
- [drivers (community 3) (6 files, cohesion 0.37)](./community_3_drivers.md)
- [headers (community 4) (33 files, cohesion 0.63)](./community_4_headers.md)
- [headers (community 5) (27 files, cohesion 0.42)](./community_5_headers.md)
- [headers (community 6) (3 files, cohesion 0.50)](./community_6_headers.md)
- [progs/doomgeneric (221 files, cohesion 0.95)](./community_7_progs_doomgeneric.md)
- [headers (community 8) (3 files, cohesion 0.67)](./community_8_headers.md)
- [headers (community 9) (11 files, cohesion 0.42)](./community_9_headers.md)
- [headers (community 10) (20 files, cohesion 0.38)](./community_10_headers.md)
- [headers (community 11) (2 files, cohesion 0.33)](./community_11_headers.md)
- [progs/nuklear (18 files, cohesion 0.51)](./community_12_progs_nuklear.md)
- [headers (community 13) (2 files, cohesion 0.50)](./community_13_headers.md)
- [headers (community 14) (3 files, cohesion 0.40)](./community_14_headers.md)
- [headers (community 15) (3 files, cohesion 0.67)](./community_15_headers.md)
- [headers (community 16) (9 files, cohesion 0.63)](./community_16_headers.md)
- [tools (22 files, cohesion 0.83)](./community_17_tools.md)
- [progs/src (4 files, cohesion 0.75)](./community_18_progs_src.md)
- [tests (2 files, cohesion 1.00)](./community_19_tests.md)
- [orphans (106 files, cohesion 0.00)](./community_20_orphans.md)

## God Nodes

| File | Score |
|------|-------|
| `kernel/string.c` | 153.3 |
| `progs/doomgeneric/doomtype.h` | 101.4 |
| `progs/doomgeneric/doomdef.h` | 90.9 |
| `progs/doomgeneric/doomstat.h` | 84.8 |
| `progs/doomgeneric/z_zone.h` | 81.3 |

## Strongest Connections

- 2 -> 3: depends_on (strength 0.9, EXTRACTED)
- 2 -> 0: depends_on (strength 0.9, EXTRACTED)
- 4 -> 10: depends_on (strength 0.9, EXTRACTED)
- 4 -> 0: depends_on (strength 0.9, EXTRACTED)
- 2 -> 4: depends_on (strength 0.9, EXTRACTED)
- 5 -> 10: depends_on (strength 0.9, EXTRACTED)
- 5 -> 0: depends_on (strength 0.9, EXTRACTED)
- 5 -> 3: depends_on (strength 0.9, EXTRACTED)
- 3 -> 4: depends_on (strength 0.9, EXTRACTED)
- 5 -> 2: depends_on (strength 0.9, EXTRACTED)

## Navigation Tips

- Obsidian Graph View works: every community page links back here.
- `connections.json` is machine-readable for GraphRAG pipelines.
- `REPORT.md` states what was extracted vs inferred and current limits.
- Regenerate offline: `readmenator . --rebuild` (no network, no tokens).
