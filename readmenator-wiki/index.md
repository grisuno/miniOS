# Second Brain

*Last synthesized: 2026-09-26 | 515 files | 12 concept pages | offline, zero tokens*

> Raw sources -> readmenator wiki -> links (Karpathy LLM Wiki Pattern, deterministic).
> Start here, then open one community page. Prefer grep over full reads.

## Vault Overview

The codebase centres on `kernel.h`, `string.c`, `doomtype.h`. Architecturally it is 5 layers, dominant utility (391 files) across 12 import-based communities. Recorded risk surface: 0 security findings and 1 dependency cycles.

Surprising tissue lives between headers (community 0), headers/drivers (community 1), progs/pokemon: 15 extracted cross-community imports and 5 inferred bridges. Follow `connections.json` sorted by strength before refactoring.

Open work clusters around documentation (89% file coverage), 0 security findings, 20 taint paths, and 5 suggested exploration questions in `queries.md`.

## Stats

| Metric | Value |
|--------|-------|
| Files | 515 |
| Symbols | 10521 |
| Resolved imports | 1305 |
| Languages | S, c, h, lua, py, s, sh |
| Communities | 12 |
| Doc coverage | 89% (456/515 files) |
| Security findings | 0 |
| Estimated read cost | ~181108 tokens (chars/4, offline so $0) |

## Reading Order

1. Skim Stats and God Nodes below for blast radius.
2. Open the largest community page first, then follow Connections.
3. Use `queries.md` for the next question; log the answer there.

```
grep -rn '<keyword>' index.md community_*.md
readmenator query "<question>" --target miniOS
```

## Concept Wiki

- [headers (community 0) (132 files, cohesion 0.90)](./community_0_headers.md)
- [headers/drivers (community 1) (4 files, cohesion 0.50)](./community_1_headers_drivers.md)
- [progs/pokemon (4 files, cohesion 0.43)](./community_2_progs_pokemon.md)
- [headers (community 3) (13 files, cohesion 0.66)](./community_3_headers.md)
- [headers/drivers (community 4) (2 files, cohesion 0.33)](./community_4_headers_drivers.md)
- [headers (community 5) (9 files, cohesion 0.63)](./community_5_headers.md)
- [progs/doomgeneric (192 files, cohesion 0.95)](./community_6_progs_doomgeneric.md)
- [tools (21 files, cohesion 0.79)](./community_7_tools.md)
- [progs/nuklear (39 files, cohesion 0.66)](./community_8_progs_nuklear.md)
- [progs/src (4 files, cohesion 0.75)](./community_9_progs_src.md)
- [tests (2 files, cohesion 1.00)](./community_10_tests.md)
- [orphans (93 files, cohesion 0.00)](./community_11_orphans.md)

## God Nodes

| File | Score |
|------|-------|
| `headers/kernel.h` | 164.2 |
| `kernel/string.c` | 139.3 |
| `progs/doomgeneric/doomtype.h` | 101.4 |
| `progs/doomgeneric/doomdef.h` | 90.9 |
| `progs/doomgeneric/doomstat.h` | 84.8 |

## Strongest Connections

- 0 -> 4: depends_on (strength 0.9, EXTRACTED)
- 0 -> 3: depends_on (strength 0.9, EXTRACTED)
- 1 -> 0: depends_on (strength 0.9, EXTRACTED)
- 0 -> 8: depends_on (strength 0.9, EXTRACTED)
- 5 -> 6: depends_on (strength 0.9, EXTRACTED)
- 5 -> 7: depends_on (strength 0.9, EXTRACTED)
- 5 -> 0: depends_on (strength 0.9, EXTRACTED)
- 3 -> 4: depends_on (strength 0.9, EXTRACTED)
- 6 -> 0: depends_on (strength 0.9, EXTRACTED)
- 7 -> 0: depends_on (strength 0.9, EXTRACTED)

## Navigation Tips

- Obsidian Graph View works: every community page links back here.
- `connections.json` is machine-readable for GraphRAG pipelines.
- `REPORT.md` states what was extracted vs inferred and current limits.
- Regenerate offline: `readmenator . --rebuild` (no network, no tokens).
