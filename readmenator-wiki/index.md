# Second Brain

*Last synthesized: 2026-10-08 | 557 files | 10 concept pages | offline, zero tokens*

> Raw sources -> readmenator wiki -> links (Karpathy LLM Wiki Pattern, deterministic).
> Start here, then open one community page. Prefer grep over full reads.

## Vault Overview

The codebase centres on `string.c`, `doomtype.h`, `doomdef.h`. Architecturally it is 5 layers, dominant utility (433 files) across 10 import-based communities. Recorded risk surface: 0 security findings and 1 dependency cycles.

Surprising tissue lives between headers: kernel, progs/doomgeneric: d_englsh, progs/doomgeneric: p_spec: 14 extracted cross-community imports and 6 inferred bridges. Follow `connections.json` sorted by strength before refactoring.

Open work clusters around documentation (89% file coverage), 0 security findings, 20 taint paths, and 5 suggested exploration questions in `queries.md`.

## Stats

| Metric | Value |
|--------|-------|
| Files | 557 |
| Symbols | 11896 |
| Resolved imports | 1345 |
| Languages | S, c, h, lua, py, s, sh |
| Communities | 10 |
| Doc coverage | 89% (494/557 files) |
| Security findings | 0 |
| Estimated read cost | ~210322 tokens (chars/4, offline so $0) |

## Reading Order

1. Skim Stats and God Nodes below for blast radius.
2. Open the largest community page first, then follow Connections.
3. Use `queries.md` for the next question; log the answer there.

```
grep -rn '<keyword>' index.md community_*.md
readmenator query "<question>" --target miniOS
```

## Concept Wiki

- [headers: kernel (138 files, cohesion 0.88)](./community_0_headers_kernel.md)
- [progs/doomgeneric: d_englsh (99 files, cohesion 0.66)](./community_1_progs_doomgeneric_d_englsh.md)
- [progs/doomgeneric: p_spec (69 files, cohesion 0.56)](./community_2_progs_doomgeneric_p_spec.md)
- [progs/src (67 files, cohesion 0.70)](./community_3_progs_src.md)
- [tools: minios_hyper (29 files, cohesion 0.80)](./community_4_tools_minios_hyper.md)
- [headers: vga_fb (18 files, cohesion 0.70)](./community_5_headers_vga_fb.md)
- [headers: tls_crypto (15 files, cohesion 0.63)](./community_6_headers_tls_crypto.md)
- [progs/doomgeneric: net_defs (13 files, cohesion 0.42)](./community_7_progs_doomgeneric_net_defs.md)
- [tools: doom_pwad (2 files, cohesion 1.00)](./community_8_tools_doom_pwad.md)
- [orphans (107 files, cohesion 0.00)](./community_9_orphans.md)

## God Nodes

| File | Score |
|------|-------|
| `kernel/string.c` | 163.3 |
| `progs/doomgeneric/doomtype.h` | 101.4 |
| `progs/doomgeneric/doomdef.h` | 90.9 |
| `progs/doomgeneric/doomstat.h` | 84.8 |
| `progs/doomgeneric/z_zone.h` | 81.3 |

## Strongest Connections

- 6 -> 0: depends_on (strength 0.9, EXTRACTED)
- 0 -> 3: depends_on (strength 0.9, EXTRACTED)
- 6 -> 3: depends_on (strength 0.9, EXTRACTED)
- 6 -> 4: depends_on (strength 0.9, EXTRACTED)
- 0 -> 5: depends_on (strength 0.9, EXTRACTED)
- 0 -> 4: depends_on (strength 0.9, EXTRACTED)
- 1 -> 2: depends_on (strength 0.9, EXTRACTED)
- 1 -> 3: depends_on (strength 0.9, EXTRACTED)
- 7 -> 3: depends_on (strength 0.9, EXTRACTED)
- 7 -> 1: depends_on (strength 0.9, EXTRACTED)

## Navigation Tips

- Obsidian Graph View works: every community page links back here.
- `connections.json` is machine-readable for GraphRAG pipelines.
- `REPORT.md` states what was extracted vs inferred and current limits.
- Regenerate offline: `readmenator . --rebuild` (no network, no tokens).
