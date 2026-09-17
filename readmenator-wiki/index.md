# Second Brain

*Last synthesized: 2026-09-17 | 475 files | 16 concept pages | offline, zero tokens*

> Raw sources -> readmenator wiki -> links (Karpathy LLM Wiki Pattern, deterministic).
> Start here, then open one community page. Prefer grep over full reads.

## Vault Overview

The codebase centres on `kernel.h`, `string.c`, `doomtype.h`. Architecturally it is 5 layers, dominant utility (366 files) across 16 import-based communities. Recorded risk surface: 346 security findings and 1 dependency cycles.

Surprising tissue lives between arch/x86/boot, headers (community 1), headers (community 2): 20 extracted cross-community imports and 0 inferred bridges. Follow `connections.json` sorted by strength before refactoring.

Open work clusters around documentation (91% file coverage), 346 security findings, 20 taint paths, and 5 suggested exploration questions in `queries.md`.

## Stats

| Metric | Value |
|--------|-------|
| Files | 475 |
| Symbols | 11354 |
| Resolved imports | 1221 |
| Languages | S, c, h, lua, py, s, sh |
| Communities | 16 |
| Doc coverage | 91% (434/475 files) |
| Security findings | 346 |
| Estimated read cost | ~194167 tokens (chars/4, offline so $0) |

## Reading Order

1. Skim Stats and God Nodes below for blast radius.
2. Open the largest community page first, then follow Connections.
3. Use `queries.md` for the next question; log the answer there.

```
grep -rn '<keyword>' index.md community_*.md
readmenator query "<question>" --target miniOS
```

## Concept Wiki

- [arch/x86/boot (6 files, cohesion 0.33)](./community_0_arch_x86_boot.md)
- [headers (community 1) (11 files, cohesion 0.46)](./community_1_headers.md)
- [headers (community 2) (27 files, cohesion 0.52)](./community_2_headers.md)
- [headers (community 3) (64 files, cohesion 0.63)](./community_3_headers.md)
- [headers (community 4) (3 files, cohesion 0.40)](./community_4_headers.md)
- [progs/doomgeneric (community 5) (114 files, cohesion 0.63)](./community_5_progs_doomgeneric.md)
- [headers (community 6) (3 files, cohesion 0.67)](./community_6_headers.md)
- [headers (community 7) (10 files, cohesion 0.63)](./community_7_headers.md)
- [headers (community 8) (3 files, cohesion 0.67)](./community_8_headers.md)
- [tests (community 9) (5 files, cohesion 0.40)](./community_9_tests.md)
- [tools (21 files, cohesion 0.79)](./community_10_tools.md)
- [progs/doomgeneric (community 11) (108 files, cohesion 0.76)](./community_11_progs_doomgeneric.md)
- [progs/doomgeneric (community 12) (10 files, cohesion 0.39)](./community_12_progs_doomgeneric.md)
- [progs/src (4 files, cohesion 0.75)](./community_13_progs_src.md)
- [tests (community 14) (2 files, cohesion 1.00)](./community_14_tests.md)
- [orphans (84 files, cohesion 0.00)](./community_15_orphans.md)

## God Nodes

| File | Score |
|------|-------|
| `headers/kernel.h` | 137.6 |
| `kernel/string.c` | 125.3 |
| `progs/doomgeneric/doomtype.h` | 101.4 |
| `progs/doomgeneric/doomdef.h` | 90.9 |
| `progs/doomgeneric/d_main.c` | 89.3 |

## Strongest Connections

- 1 -> 3: depends_on (strength 0.9, EXTRACTED)
- 2 -> 3: depends_on (strength 0.9, EXTRACTED)
- 3 -> 5: depends_on (strength 0.9, EXTRACTED)
- 3 -> 9: depends_on (strength 0.9, EXTRACTED)
- 2 -> 9: depends_on (strength 0.9, EXTRACTED)
- 3 -> 10: depends_on (strength 0.9, EXTRACTED)
- 4 -> 3: depends_on (strength 0.9, EXTRACTED)
- 3 -> 0: depends_on (strength 0.9, EXTRACTED)
- 2 -> 0: depends_on (strength 0.9, EXTRACTED)
- 2 -> 8: depends_on (strength 0.9, EXTRACTED)

## Navigation Tips

- Obsidian Graph View works: every community page links back here.
- `connections.json` is machine-readable for GraphRAG pipelines.
- `REPORT.md` states what was extracted vs inferred and current limits.
- Regenerate offline: `readmenator . --rebuild` (no network, no tokens).
