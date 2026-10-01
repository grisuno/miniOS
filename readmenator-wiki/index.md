# Second Brain

*Last synthesized: 2026-10-01 | 535 files | 11 concept pages | offline, zero tokens*

> Raw sources -> readmenator wiki -> links (Karpathy LLM Wiki Pattern, deterministic).
> Start here, then open one community page. Prefer grep over full reads.

## Vault Overview

The codebase centres on `kernel.h`, `string.c`, `doomtype.h`. Architecturally it is 5 layers, dominant utility (400 files) across 11 import-based communities. Recorded risk surface: 0 security findings and 1 dependency cycles.

Surprising tissue lives between headers (community 0), arch/x86, progs/doomgeneric (community 2): 11 extracted cross-community imports and 9 inferred bridges. Follow `connections.json` sorted by strength before refactoring.

Open work clusters around documentation (89% file coverage), 0 security findings, 20 taint paths, and 5 suggested exploration questions in `queries.md`.

## Stats

| Metric | Value |
|--------|-------|
| Files | 535 |
| Symbols | 10984 |
| Resolved imports | 1353 |
| Languages | S, c, h, lua, py, s, sh |
| Communities | 11 |
| Doc coverage | 89% (475/535 files) |
| Security findings | 0 |
| Estimated read cost | ~193826 tokens (chars/4, offline so $0) |

## Reading Order

1. Skim Stats and God Nodes below for blast radius.
2. Open the largest community page first, then follow Connections.
3. Use `queries.md` for the next question; log the answer there.

```
grep -rn '<keyword>' index.md community_*.md
readmenator query "<question>" --target miniOS
```

## Concept Wiki

- [headers (community 0) (154 files, cohesion 0.94)](./community_0_headers.md)
- [arch/x86 (2 files, cohesion 0.50)](./community_1_arch_x86.md)
- [progs/doomgeneric (community 2) (62 files, cohesion 0.67)](./community_2_progs_doomgeneric.md)
- [headers (community 3) (3 files, cohesion 0.67)](./community_3_headers.md)
- [tools (25 files, cohesion 0.82)](./community_4_tools.md)
- [headers (community 5) (3 files, cohesion 0.67)](./community_5_headers.md)
- [headers (community 6) (9 files, cohesion 0.63)](./community_6_headers.md)
- [progs/doomgeneric (community 7) (175 files, cohesion 0.95)](./community_7_progs_doomgeneric.md)
- [progs/src (4 files, cohesion 0.75)](./community_8_progs_src.md)
- [tests (2 files, cohesion 1.00)](./community_9_tests.md)
- [orphans (96 files, cohesion 0.00)](./community_10_orphans.md)

## God Nodes

| File | Score |
|------|-------|
| `headers/kernel.h` | 175.6 |
| `kernel/string.c` | 149.3 |
| `progs/doomgeneric/doomtype.h` | 101.4 |
| `progs/doomgeneric/doomdef.h` | 90.9 |
| `progs/doomgeneric/doomstat.h` | 84.8 |

## Strongest Connections

- 0 -> 2: depends_on (strength 0.9, EXTRACTED)
- 6 -> 2: depends_on (strength 0.9, EXTRACTED)
- 6 -> 4: depends_on (strength 0.9, EXTRACTED)
- 6 -> 0: depends_on (strength 0.9, EXTRACTED)
- 0 -> 5: depends_on (strength 0.9, EXTRACTED)
- 0 -> 3: depends_on (strength 0.9, EXTRACTED)
- 0 -> 4: depends_on (strength 0.9, EXTRACTED)
- 0 -> 1: depends_on (strength 0.9, EXTRACTED)
- 7 -> 2: depends_on (strength 0.9, EXTRACTED)
- 2 -> 4: depends_on (strength 0.9, EXTRACTED)

## Navigation Tips

- Obsidian Graph View works: every community page links back here.
- `connections.json` is machine-readable for GraphRAG pipelines.
- `REPORT.md` states what was extracted vs inferred and current limits.
- Regenerate offline: `readmenator . --rebuild` (no network, no tokens).
