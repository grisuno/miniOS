# Project Memory

> Cross-session context for agents. Sections 1-6 are regenerated from the source tree with zero LLM tokens: declared rules are quoted verbatim with `file:line`, measured baselines come from the scan. Section 7 is written by agents and humans and is preserved across rebuilds.

Generated from 587 files at commit `7cc22fee05ed`. Read this first, then `readmenator-wiki/index.md`, then `readmenator . ask "<question>"` for anything specific.

## 1. Purpose and domain

- What it is: I had some things programmed, a [kernel](https://github.com/grisuno/miniOS), [a C to ASM transpiler](https://github.com/grisuno/miniGCC), [compiler/linker](https://github.com/grisuno/ld), [a browser](https://github.com/grisuno/FreeDom), I had a [beacon](https://github.com/grisuno/blacksandbeacon) with an ELF loader which was basically the first prototype of [CVM](https://github.com/grisuno/cvm). (`README.md:10`)
- Domain vocabulary (term, files): `progs` (317), `free` (240), `any` (238), `without` (230), `program` (221), `can` (218), `under` (211), `see` (192), `doomgeneric` (188), `version` (186), `but` (185), `later` (184), `either` (183), `more` (181), `public` (179)
- Subsystem `headers: kernel`: 137 files, core `headers/kernel.h`: The user-window memory layout (load base, stack, brk cap, graphics
- Subsystem `progs/doomgeneric: d_englsh`: 99 files, core `progs/doomgeneric/d_englsh.h`: Copyright(C) 1993-1996 Id Software, Inc.
- Subsystem `progs/src`: 85 files, core `progs/vedit/vedit.c`: vedit IDE build and run contract.
- Subsystem `progs/doomgeneric: p_spec`: 69 files, core `progs/doomgeneric/p_spec.h`: Copyright(C) 1993-1996 Id Software, Inc.
- Subsystem `tools: tls_crypto`: 44 files, core `net/tls_crypto.c`: the crypto behind the kernel TLS 1.2 client.
- Subsystem `headers: vga_fb`: 17 files, core `kernel/vga_fb.c`: wm_geom_cfg: /** Docstring: Focus ids share one space across terminals and graphics....
- Subsystem `progs/doomgeneric: net_defs`: 13 files, core `progs/doomgeneric/net_defs.h`: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it...
- Subsystem `headers: batch`: 3 files, core `headers/batch.h`: Docstring: batch.h -- Batched synchronous syscall submission.
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
- **Layout addresses** live once in `progs/minios_abi.h`; never hardcode one in (`CLAUDE.md:45`)
- **Low 4 MB**: user page-table zone stays at `0x10000`; kernel image + `.bss` (`CLAUDE.md:47`)
- **Kernel stacks**: 16 KB per proc, `-Werror=frame-larger-than=2048`; (`CLAUDE.md:51`)
- **Syscalls** take user pointers only through `SANITIZE_*` (`-EFAULT` on (`CLAUDE.md:53`)
- **SB16/DMA**: never auto-init DMA; one single-cycle block per terminal-count (`CLAUDE.md:55`)
- **Build**: per-object header deps live in the Makefile; a new `#include` (`CLAUDE.md:57`)
- **Graphics apps**: present through `GFX_PRESENT`; mouse via the origin the (`CLAUDE.md:59`)
- **USB**: PCI MMIO is mapped only through `kmm_map_uncached()` (write-back (`CLAUDE.md:62`)
- **Foreground processes**: the shell's pid-0 exec frame has no fork/execve; (`CLAUDE.md:70`)
- **Heavy ring-3 overlap** (two big glibc processes) is known-red until (`CLAUDE.md:75`)
- Every loader input is validated before use: ELF headers, section and (`CLAUDE.md:154`)
- Size arithmetic is overflow checked before allocation (`size * n` included). (`CLAUDE.md:156`)
- Failure paths report and release; no silent partial state. (`CLAUDE.md:157`)
- No function symbol is ever resolved to a null address. (`CLAUDE.md:158`)
- User stack setup validates that argv writes stay within bounds. (`CLAUDE.md:159`)

Measured baseline:
- Security findings at medium or above: 0 (see `readmenator-agent/SECURITY.md`); do not add new ones.
- Dependency cycles: 1; layer violations: 3 (see `readmenator-agent/GOTCHAS.md`).

## 4. Style norms

Declared:
- none declared in instruction files (add them to AGENTS.md or record them in section 7)

Measured baseline:
- c: 287 files, 7083 symbols; docstrings on 22% of symbols; functions snake_case (76%); types PascalCase (18%); median file 259 lines, max 4902.
- h: 197 files, 4610 symbols; docstrings on 17% of symbols; functions snake_case (70%); types PascalCase (7%); median file 69 lines, max 1331.
- py: 66 files, 783 symbols; docstrings on 37% of symbols; functions snake_case (97%); types PascalCase (99%); median file 135 lines, max 957.
- sh: 17 files, 45 symbols; docstrings on 18% of symbols; functions snake_case (100%); median file 80 lines, max 2326.
- Tests: 70 files under mcp, progs/src, tests; follow the existing naming (e.g. `test_minios_mcp.py`).

## 5. Minimum deliverables

Declared:
- none declared in instruction files (add them to AGENTS.md or record them in section 7)

Measured baseline:
- Tests pass: `python -m pytest -q`.
- Docstring coverage stays at or above 20%.
- No new security findings at medium or above (current: 0).
- No new dependency cycles (current: 1).
- Files stay under 300 lines where possible (`readmenator . lint`).
- Docs refreshed: `readmenator . --rebuild`, and decisions recorded in section 7.

## 6. Risks to respect

- God nodes (changes ripple widely): `kernel/string.c`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/doomdef.h`, `kernel/syscalls.c`, `progs/doomgeneric/doomstat.h`
- Hotspots (complex and central): `kernel/syscalls.c`, `kernel/string.c`, `progs/doomgeneric/d_main.c`, `kernel/shell.c`, `progs/doomgeneric/g_game.c`
- Cycle: `progs/doomgeneric/r_data.h` -> `progs/doomgeneric/r_state.h` -> `progs/doomgeneric/r_data.h`
- Full blast radius: `readmenator-agent/GOTCHAS.md`; findings: `readmenator-agent/SECURITY.md`.

## 7. Session log (preserved across rebuilds)

Append with `readmenator . remember "<note>" --kind <kind>` (kinds: business, decision, rule, workflow, style, deliverable, gotcha, todo, note) or the MCP tool `readmenator.remember`. Record business rules, decisions and their reasons, workflow changes, and anything the next session must not rediscover.

<!-- readmenator:memory:notes:begin -->
<!-- readmenator:memory:notes:end -->
