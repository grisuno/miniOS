# Project Memory

> Cross-session context for agents. Sections 1-6 are regenerated from the source tree with zero LLM tokens: declared rules are quoted verbatim with `file:line`, measured baselines come from the scan. Section 7 is written by agents and humans and is preserved across rebuilds.

Generated from 557 files at commit `f352c8e67452`. Read this first, then `readmenator-wiki/index.md`, then `readmenator . ask "<question>"` for anything specific.

## 1. Purpose and domain

- What it is: I had some things programmed, a [kernel](https://github.com/grisuno/miniOS), [a C to ASM transpiler](https://github.com/grisuno/miniGCC), [compiler/linker](https://github.com/grisuno/ld), [a browser](https://github.com/grisuno/FreeDom), I had a [beacon](https://github.com/grisuno/blacksandbeacon) with an ELF loader which was basically the first prototype of [CVM](https://github.com/grisuno/cvm). (`README.md:10`)
- Domain vocabulary (term, files): `progs` (304), `free` (230), `without` (227), `any` (225), `can` (217), `program` (215), `under` (205), `doomgeneric` (188), `see` (187), `version` (186), `later` (183), `but` (183), `either` (181), `more` (179), `public` (176)
- Subsystem `headers: kernel`: 138 files, core `headers/kernel.h`: The user-window memory layout (load base, stack, brk cap, graphics
- Subsystem `progs/doomgeneric: d_englsh`: 99 files, core `progs/doomgeneric/d_englsh.h`: Copyright(C) 1993-1996 Id Software, Inc.
- Subsystem `progs/doomgeneric: p_spec`: 69 files, core `progs/doomgeneric/p_spec.h`: Copyright(C) 1993-1996 Id Software, Inc.
- Subsystem `progs/src`: 67 files, core `progs/vedit/vedit.c`: vedit IDE build and run contract.
- Subsystem `tools: minios_hyper`: 29 files, core `tools/minios_hyper.py`: host-side ring-minus-one debugger for MiniOS.
- Subsystem `headers: vga_fb`: 18 files, core `kernel/vga_fb.c`: wm_geom_cfg: /** Docstring: Focus ids share one space across terminals and graphics....
- Subsystem `headers: tls_crypto`: 15 files, core `net/tls_crypto.c`: the crypto behind the kernel TLS 1.2 client.
- Subsystem `progs/doomgeneric: net_defs`: 13 files, core `progs/doomgeneric/net_defs.h`: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it...
- Business rules that the code cannot show live in section 7: record them there.

## 2. Workflow

Detected commands:
- `python -m pytest -q` (tests/ layout)
- `make all` (Makefile)
- `make sources` (Makefile)
- `make sources-update` (Makefile)
- `make sources-status` (Makefile)
- `make addons` (Makefile)
- `make toolchain` (Makefile)
- `make pokemon-fetch` (Makefile)
- `make pokemon-clean` (Makefile)
- `make lisp-host` (Makefile)
- `make test-lisp` (Makefile)
- `make minicraft-host` (Makefile)

Session protocol:
1. Start: read this file, then `readmenator . fresh` (exit 1 means run `readmenator . --rebuild`).
2. Orient: `readmenator-wiki/index.md`; for a question use `readmenator . ask "<question>"` (local = entities + sources, `--global` = community reports).
3. Before editing a file: `grep -n '<file>' readmenator-agent/GOTCHAS.md readmenator-agent/SECURITY.md`.
4. After the change: run the tests above, then `readmenator . --rebuild` so the maps, wiki, and this file stay true.
5. End: record decisions, business rules, and gotchas with `readmenator . remember "<note>" --kind decision`.

## 3. Rules and constraints

Declared:
- **Layout addresses** live once in `progs/minios_abi.h`; never hardcode one in (`CLAUDE.md:43`)
- **Low 4 MB**: user page-table zone stays at `0x10000`; kernel image + `.bss` (`CLAUDE.md:45`)
- **Kernel stacks**: 16 KB per proc, `-Werror=frame-larger-than=2048`; (`CLAUDE.md:49`)
- **Syscalls** take user pointers only through `SANITIZE_*` (`-EFAULT` on (`CLAUDE.md:51`)
- **SB16/DMA**: never auto-init DMA; one single-cycle block per terminal-count (`CLAUDE.md:53`)
- **Build**: per-object header deps live in the Makefile; a new `#include` (`CLAUDE.md:55`)
- **Graphics apps**: present through `GFX_PRESENT`; mouse via the origin the (`CLAUDE.md:57`)
- **USB**: PCI MMIO is mapped only through `kmm_map_uncached()` (write-back (`CLAUDE.md:60`)
- **Heavy ring-3 overlap** (two big glibc processes) is known-red until (`CLAUDE.md:68`)
- Every loader input is validated before use: ELF headers, section and (`CLAUDE.md:145`)
- Size arithmetic is overflow checked before allocation (`size * n` included). (`CLAUDE.md:147`)
- Failure paths report and release; no silent partial state. (`CLAUDE.md:148`)
- No function symbol is ever resolved to a null address. (`CLAUDE.md:149`)
- User stack setup validates that argv writes stay within bounds. (`CLAUDE.md:150`)

Measured baseline:
- Security findings at medium or above: 0 (see `readmenator-agent/SECURITY.md`); do not add new ones.
- Dependency cycles: 1; layer violations: 3 (see `readmenator-agent/GOTCHAS.md`).

## 4. Style norms

Declared:
- none declared in instruction files (add them to AGENTS.md or record them in section 7)

Measured baseline:
- c: 272 files, 6447 symbols; docstrings on 21% of symbols; functions snake_case (74%); types PascalCase (20%); median file 261 lines, max 4886.
- h: 191 files, 4388 symbols; docstrings on 17% of symbols; functions snake_case (69%); types PascalCase (7%); median file 69 lines, max 1331.
- py: 59 files, 662 symbols; docstrings on 34% of symbols; functions snake_case (97%); types PascalCase (98%); median file 135 lines, max 957.
- sh: 17 files, 43 symbols; docstrings on 19% of symbols; functions snake_case (100%); median file 80 lines, max 2139.
- Tests: 63 files under mcp, progs/src, tests; follow the existing naming (e.g. `test_minios_mcp.py`).

## 5. Minimum deliverables

Declared:
- none declared in instruction files (add them to AGENTS.md or record them in section 7)

Measured baseline:
- Tests pass: `python -m pytest -q`.
- Docstring coverage stays at or above 19%.
- No new security findings at medium or above (current: 0).
- No new dependency cycles (current: 1).
- Files stay under 300 lines where possible (`readmenator . lint`).
- Docs refreshed: `readmenator . --rebuild`, and decisions recorded in section 7.

## 6. Risks to respect

- God nodes (changes ripple widely): `kernel/string.c`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/z_zone.h`
- Hotspots (complex and central): `progs/doomgeneric/d_main.c`, `kernel/string.c`, `kernel/syscalls.c`, `progs/doomgeneric/g_game.c`, `kernel/shell.c`
- Cycle: `progs/doomgeneric/r_data.h` -> `progs/doomgeneric/r_state.h` -> `progs/doomgeneric/r_data.h`
- Full blast radius: `readmenator-agent/GOTCHAS.md`; findings: `readmenator-agent/SECURITY.md`.

## 7. Session log (preserved across rebuilds)

Append with `readmenator . remember "<note>" --kind <kind>` (kinds: business, decision, rule, workflow, style, deliverable, gotcha, todo, note) or the MCP tool `readmenator.remember`. Record business rules, decisions and their reasons, workflow changes, and anything the next session must not rediscover.

<!-- readmenator:memory:notes:begin -->
<!-- readmenator:memory:notes:end -->
