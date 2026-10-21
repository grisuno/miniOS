# MiniOS

[![GitHub stars](https://img.shields.io/github/stars/grisuno/miniOS?style=social)](https://github.com/grisuno/miniOS)
[![License: AGPL](https://img.shields.io/badge/License-AGPL-yellow.svg)](https://opensource.org/licenses/AGPL)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg)](https://makeapullrequest.com)
[![Sponsor](https://img.shields.io/badge/Sponsor-%E2%9D%A4-pink?logo=github)](https://ko-fi.com/grisuno)
[![Download the app](https://img.shields.io/github/v/release/grisuno/miniOS?label=Download%20app&color=2563eb)](https://github.com/grisuno/miniOS/releases/latest)
[![Ask DeepWiki](https://deepwiki.com/badge.svg)](https://deepwiki.com/grisuno/miniOS)

I had some things programmed, a [kernel](https://github.com/grisuno/miniOS), [a C to ASM transpiler](https://github.com/grisuno/miniGCC), [compiler/linker](https://github.com/grisuno/ld), [a browser](https://github.com/grisuno/FreeDom), I had a [beacon](https://github.com/grisuno/blacksandbeacon) with an ELF loader which was basically the first prototype of [CVM](https://github.com/grisuno/cvm). That same [beacon](https://github.com/grisuno/blacksandbeacon), [TopoGPT3](https://github.com/grisuno/TopoGPT3), already had some things that I reused, like AES and the JSON implementation. LZSS comes from [CompressLoader](https://github.com/grisuno/CompressLoader), another tool, and at one point I said, "Can I run this on my kernel?" And well, here we are.

<img width="1029" height="829" alt="image" src="https://github.com/user-attachments/assets/c08520bc-60d9-4cc6-b663-eada68b7b20f" />

[LazyOwn](https://github.com/grisuno/LazyOwn) [RedTeam](https://medium.com/@lazyown.redteam) has released an educational 64-bit x86 teaching kernel and operating system, with [basic security](docs/spec/kernel.md), that carries its own complete [toolchain](docs/spec/source.md) of a subset of C, [MicroPython](docs/spec/python.md), [Lua](docs/spec/apps.md), [Lisp](docs/spec/apps.md) and a full [CPython](docs/spec/python.md) with [pip](docs/spec/python.md). You can write a C program inside the running system, compile it, link it and execute it without leaving the machine or even vedit. With some [games](docs/spec/games.md), like [Quake 2](docs/spec/games.md), [MiniCraft](docs/spec/games.md), [Pokemon](docs/spec/games.md), [MCP](docs/spec/mcp.md), [internet](docs/spec/network.md), and [terminal utilities](docs/spec/shell-fs.md) like a [llm](docs/spec/topogpt3.md), [Paint](docs/spec/apps.md), [Nuklear](docs/spec/apps.md) node editor, [Piano](docs/spec/audio.md). It has been [developed with love](docs/acknowledgments.md).

## Build and run

```bash
git clone https://github.com/grisuno/miniOS.git
cd miniOS
make sources        # clone the toolchain siblings (miniGCC, ld, cvm, ...)
make                # build os.img

make run-kvm        # boot it in KVM mode
make run-headless   # boot it on the serial console
make run            # boot it in QEMU
```

Full walkthrough: **[docs/quickstart.md](docs/quickstart.md)**. One-line lookups for
the shell, the editor, the make targets and the syscall numbers:
**[docs/cheatsheet.md](docs/cheatsheet.md)**.

```bash
miniOS> edit src/p.c
miniOS> run objects/minigcc.o src/p.c > asm/p.s
miniOS> run objects/ld.o -f elf -o bin/p.elf asm/p.s
miniOS> run sign bin/p.elf
miniOS> run bin/p.elf
```

## Documentation

Every section below has one document with the complete implementation.
`CLAUDE.md` holds the normative engineering contract (rules, hazards, gates)
and indexes the same documents.

### Platform

| Section | Document |
|---------|----------|
| Boot path, disk layout, physical memory map, KASLR and userspace ASLR | [docs/spec/boot-memory.md](docs/spec/boot-memory.md) |
| Kernel contracts: ABI layout, loaders, program formats, CVM JIT, ramdisk, user isolation, overflow and syscall hardening | [docs/spec/kernel.md](docs/spec/kernel.md) |
| SMP, per-CPU views, threads, futexes, tick bus, HAL, preemption, job control, execve | [docs/spec/smp-sched.md](docs/spec/smp-sched.md) |
| Architectural abstractions: VFS, page cache, dynamic linking, mounts, pipes, clipboard, fork, httpd, governance plan | [docs/spec/architecture.md](docs/spec/architecture.md) |
| ABI manual for ring-3 programmers | [docs/ABI.md](docs/ABI.md) |

### Building and running

| Section | Document |
|---------|----------|
| Source contract: the sibling repositories, the toolchain bootstrap, the codec and utility tools, repository layout | [docs/spec/source.md](docs/spec/source.md) |
| Build, make targets, KVM versus TCG, USB images, other hypervisors and real hardware | [docs/spec/build-run.md](docs/spec/build-run.md) |
| Performance work: every measured optimization with the mechanism behind it | [docs/spec/performance.md](docs/spec/performance.md) |

### The system

| Section | Document |
|---------|----------|
| Shell, command resolution, line editor, filesystem names, MiniFS fallback, scrollback, tracing | [docs/spec/shell-fs.md](docs/spec/shell-fs.md) |
| VESA desktop, graphics windows, window manager, taskbar, dock, tiling, desktop effects | [docs/spec/desktop.md](docs/spec/desktop.md) |
| Ring-3 apps: vedit, file browser, paint, themes, Lua, Lisp, MicroPython, Nuklear node editor, doomedit | [docs/spec/apps.md](docs/spec/apps.md) |
| Audio: PC speaker, Sound Blaster 16, pcm2, the FM piano and the OPL3 demo | [docs/spec/audio.md](docs/spec/audio.md) |
| Network: rtl8139, the IPv4 stack, the TLS 1.2 client, the browsers and the Wayland-mini compositor | [docs/spec/network.md](docs/spec/network.md) |
| Wayland-mini compositor (`wlcomp`), wire contract and session | [docs/spec/wayland.md](docs/spec/wayland.md) |
| USB: xHCI host controller, HID boot input, mass storage | [docs/spec/usb.md](docs/spec/usb.md) |
| QEMU guest agent channel on COM2 | [docs/spec/qga.md](docs/spec/qga.md) |

### Software that runs on it

| Section | Document |
|---------|----------|
| Python: MicroPython sockets, `mip`, asyncio, static CPython 3.12 and pip | [docs/spec/python.md](docs/spec/python.md) |
| Games: DOOM, Quake 2 (and the kernel bugs its memory map uncovered), Minicraft, Pokemon | [docs/spec/games.md](docs/spec/games.md) |
| TopoGPT3: the 24.5M-parameter language model running at ring 3 | [docs/spec/topogpt3.md](docs/spec/topogpt3.md) |
| MCP bridge, agent skill and the addon marketplace | [docs/spec/mcp.md](docs/spec/mcp.md) |

### Verification

| Section | Document |
|---------|----------|
| Headless harnesses, the one-boot suite, in-OS suites, the validation gate and the library verdicts | [docs/spec/testing.md](docs/spec/testing.md) |
| In-OS and host dissection toolbox: trace, strace, vmmap, schedtop, irqstat, bootlog, gdb | [docs/debug_tools.md](docs/debug_tools.md) |
| Architecture decision records | [docs/adr/](docs/adr/) |

## Demos

- [https://www.youtube.com/watch?v=G1H5dkMCvmI](https://www.youtube.com/watch?v=G1H5dkMCvmI)
- [https://www.youtube.com/watch?v=fhYKG21Cx-A](https://www.youtube.com/watch?v=fhYKG21Cx-A)
- [https://www.youtube.com/watch?v=M4yVOq6bzMs](https://www.youtube.com/watch?v=M4yVOq6bzMs)
- [https://www.youtube.com/watch?v=YUYEK7lQt0U](https://www.youtube.com/watch?v=YUYEK7lQt0U)
- [https://www.youtube.com/watch?v=4aHe6T0bD1o](https://www.youtube.com/watch?v=4aHe6T0bD1o)

## Wiki

- [![Ask DeepWiki](https://deepwiki.com/badge.svg)](https://deepwiki.com/grisuno/miniOS)

## Acknowledgments

MiniOS stands on the shoulders of third-party software: DOOM, Quake 2,
MicroPython, Lua, Nuklear, Nuked-OPL3, Lexbor, miniz, dlmalloc, stb, xxHash,
gb-recompiled, raycastlib and QEMU. The full list with authors and links is
in **[docs/acknowledgments.md](docs/acknowledgments.md)**.

## Easteregg

The wallpaper is the image from the [cgoblin](https://github.com/grisuno/cgoblin)
readme, one of the first tools we wrote in Go.

<!-- readmenator-kb-link -->
## Knowledge Base

This project has been analyzed by [ReadMenator](https://github.com/grisuno/ReadMenator),
a zero-token polyglot static analysis tool. Regenerate with
`pip install readmenator && readmenator . --rebuild`. Analysis outputs:

- **[KNOWLEDGE_BASE.md](./KNOWLEDGE_BASE.md)** -- Full architecture reference with all
  classes, functions, imports, dependency graphs, UML class diagrams, security
  audit findings, community analysis, taint paths, hotspots, cycles, and more.
- **[readmenator-agent/](./readmenator-agent/)** -- Agent-friendly, grep-optimized index.
  - `INDEX.md` -- Quick reference: what each file does
  - `SYMBOLS.md` -- Every symbol with file:line
  - `ARCHITECTURE.md` -- Internal dependency pairs + external imports
  - `API.md` -- Public function contracts
  - `GOTCHAS.md` -- Change warnings (blast radius, cycles, hotspots)
  - `SECURITY.md` -- Findings by severity with fix hints
  - `MEMORY.md` -- Rules, workflow, style, deliverables, session log
  - `MANIFEST.json` -- Freshness (git_commit + source_fingerprint) + read order
  - `KB_<subsystem>.md` -- Per-subsystem context
  - `recipes/*.md` -- Grounded task guides (add-function, fix-cycle, ...)
- **[readmenator-wiki/](./readmenator-wiki/)** -- Navigable wiki (start here for the big picture).
  - `index.md` -- Entry point: overview, reading order, god nodes, connections
  - `community_*.md` -- One synthesis page per code community
  - `connections.json` -- Typed bridges between communities
  - `queries.md` -- Suggested questions + answer log
  - `REPORT.md` -- Honest audit: coverage, confidence, limits
- **[readmenator-graphrag/](./readmenator-graphrag/)** -- Zero-token GraphRAG index.
  - `index.json` + `REPORTS.md` -- Query with `readmenator . ask "<question>"`
- **[readmenator-apidocs/](./readmenator-apidocs/)** -- API reference (Sphinx/Doxygen style).
  - `index.md` + `modules/*.md` -- Signatures, parameters, returns, raises, examples, call graphs
  - `architecture.md` -- Tiered architecture + execution flows (control flow, call tree, sequence)
  - `classes.md`, `genindex.md`, `COVERAGE.md` -- Hierarchy, A-Z index, doc coverage + warnings
  - `index.html` + `api/` -- Offline searchable browser and machine-readable model (`api/index.json`, `api/modules/*.jsonl` one entity per line)
- **[readmenator-maps/](./readmenator-maps/)** -- Interactive gallery (`index.html`).
  - 5 system maps: architecture, workflow, sequence, dataflow, lifecycle
  - `graph-force.html` -- Force-graph explorer (2D/3D, reach, paths, lenses)
  - `graph-bundle.html` -- Edge bundle explorer (circle + sphere)
  - `components.html` -- Component diagrams
- **[docs/](./docs/)** -- Static site (GitHub Pages ready).
  - Gallery copy + `llms.txt` (agent entry point) + `md/` docs + video
- **[readmenator-diagrams/](./readmenator-diagrams/)** -- Component diagrams.
  - `analysis.json` + `graph LR` markdown + per-component pages + `index.html`
- **[readmenator-rules/](./readmenator-rules/)** -- Suggested Semgrep rules (`*.yml`),
  `yara_rules.yar` (YARA-lite) + `exclusions.yaml` (false-positive blocklist)
- **[readmenator.mp4](./readmenator.mp4)** -- Cinematic synthwave overview video
- **[.cursorrules](./.cursorrules)** -- Generated AI assistant rules
- **[readmenator_audit.sarif](./readmenator_audit.sarif)** -- SARIF v2.1.0 audit (when security scan is on)

Cache (`.readmenator_cache/`), packaged agent skills (`.claude/skills/`), and the
GitHub wiki mirror are also produced on `run`/`--rebuild`.

AI agents: Read `readmenator-wiki/index.md` first for the big picture, then `readmenator-agent/INDEX.md` for grep-friendly lookup.
Developers: Read `KNOWLEDGE_BASE.md` for full architecture reference, open `readmenator-maps/index.html` for the visual gallery.
<!-- /readmenator-kb-link -->

<!-- deploynator-footer -->

---

Deployed with [deploynator](https://github.com/grisuno/deploynator)

<!-- /deploynator-footer -->
