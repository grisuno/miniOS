# MiniOS Contract

## Purpose
MiniOS is a 64-bit x86 teaching kernel that hosts the miniGCC toolchain. It
boots from a raw disk image, runs programs in three formats, and carries the
whole toolchain on its ramdisk so that programs can be written, compiled,
linked and executed without ever leaving the machine:

```
edit src/p.c                          write C inside the OS
run objects/minigcc.o src/p.c > asm/p.s   compile to x86-64 AT&T assembly
run objects/ld.o -f elf -o bin/p.elf asm/p.s   assemble and link
run bin/p.elf                         execute
```

`ld -f cvm` produces a CVM module instead, executed by the cvm2 interpreter
that ships as `cvm.o`.

## Execution Formats
| Format | Loader | Notes |
|--------|--------|-------|
| `ET_REL` (`.o`) | `elf_load` | relocatable, linked against the kernel symbol table |
| `ET_EXEC` / `ET_DYN` | `load_exec_elf` | Linux binaries, syscall ABI, run unmodified |
| `.cvm` | `cvm.o` | CVM v2 stack bytecode |

Linux compatibility is a hard requirement: a static binary built by the host
toolchain must run by copying it onto the ramdisk, with no translation.

### CVM modules (`.cvm`)
A CVM v2 module runs with a Linux-style argv: `run <file>.cvm [args...]`
passes the module path as `argv[0]` and the remaining words as `argv[1..]`,
so the startup code every `ld -f cvm` module carries reads `argc` and
`argv` exactly as on real hardware, and a program like
`run minigcc.cvm test.c` works without extra ceremony. The data section is
laid out so that argument passing can never corrupt module data: globals,
string blobs and extern slots precede the x86 stack region, `ld` stores the
region's offset and size in the module ABI area, and the interpreter reads
those values at run time (older modules without the stored offset fall back
to the fixed layout). `cvm_set_args` copies the argument strings into the
module heap and builds the argv pointer array in the reserved area above the
stack region; a module whose layout cannot hold the argument list is
rejected with a diagnostic, never silently corrupted.


## Spec index (read the matching file before touching a subsystem)
The full contracts live in `docs/spec/`, moved verbatim from this file.
This file keeps only what must be in context on every task.

| File | Covers |
|------|--------|
| `docs/spec/source.md` | sibling repos, `make sources`, toolchain kernel-build plan, lzss/lz4/zip/json/aes tools |
| `docs/spec/boot-memory.md` | stage1/stage2, disk layout, physical map, KASLR, userspace ASLR, low-4MB hazards |
| `docs/spec/kernel.md` | `minios_abi.h` layout SSOT, loaders, kernel stack discipline, `sanitize.h`, spawn, user-mode isolation |
| `docs/spec/smp-sched.md` | SMP bring-up, per-CPU views, futex/runqueues/batch/RCU, tick bus, HAL, preemption, job control, execve |
| `docs/spec/desktop.md` | VESA desktop, graphics view contract (fullscreen/tiled/floating), WM, double buffer, taskbar, dock, melt |
| `docs/spec/shell-fs.md` | shell, redirects, history, resolver, ramdisk names, MiniFS/FAT/ext4, tracing, observability, `edit` |
| `docs/spec/network.md` | rtl8139 + stack, ring-3 TLS, `freedom`, `freedom_wl`, `freedomui` |
| `docs/spec/wayland.md` | Wayland-mini `wlcomp`, mailbox transport, chrome, desktop builtin |
| `docs/spec/apps.md` | vedit, file, paint, themes, MicroPython, Lisp, Nuklear, Quake 2, doomedit |
| `docs/spec/audio.md` | PC speaker, SB16, pcm2 standard mode, Doom MUS |
| `docs/spec/testing.md` | `boot_run.sh`, game render proofs, `test_all.sh`, in-OS suites, library assessments, TLS host gate |
| `docs/spec/mcp.md` | MCP bridge, tools, addon marketplace and doctrine |
| `docs/spec/architecture.md` | VFS, mounts/pipes/fork/httpd record, mutation-harness repairs, VMA, ABI versioning, decomposition plan |

## Hard rules and hazards (always in force)
Each line is a digest; the linked spec carries the mechanism and history.

- **Layout addresses** live once in `progs/minios_abi.h`; never hardcode one in
  the kernel or a ring-3 program (kernel.md).
- **Low 4 MB** (boot-memory.md): the user page-table zone stays at `0x10000`,
  below the kernel; the kernel image + `.bss` must end below `USER_LOAD_BASE`
  (`make check-size` gates it); grow `KASLR_IMAGE_SPAN`, stage2 `PT1` and the
  link layout together; page-by-page user mappings of heap buffers must be
  page-aligned (`kmalloc_aligned`).
- **Kernel stacks** (kernel.md): 16 KB per proc, `-Werror=frame-larger-than=2048`;
  block-sized scratch goes on the heap; exemptions need a written proof.
- **Syscalls** take user pointers only through `SANITIZE_*`; violations return
  `-EFAULT`; `tools/check_syscall_sanitize.py` gates it in `make lint`.
- **SB16/DMA**: never auto-init DMA; arm one single-cycle block per terminal
  count IRQ plus a timer fallback (audio.md, HAZARD).
- **Build discipline**: per-object header deps live in the Makefile; a new
  `#include` updates that rule in the same edit; when in doubt `rm *.o && make`.
- **Mutation table** (`tools/mutate.sh`): every target file is in `SOURCES`,
  `tools/check_mutant_anchors.py` must be green before any run, literal `*`,
  `[` and `"` are escaped, and a survivor is closed with a scenario, never by
  deleting the mutant. `expect` is an unordered grep: order-sensitive claims
  need `expect_count`/`refute`. An interrupted run leaves `os.img` built from
  the mutant: rebuild before trusting any boot.
- **Graphics apps**: present through `GFX_PRESENT`; report mouse via the
  origin the present returns; set the title after `SYS_VGA_MODE(1)` (mode-on
  resets it); request fullscreen with `GFX_ZOOM` value 2 (desktop.md).
- **Heavy ring-3 overlap** (two big glibc processes) is the known-red
  configuration until per-CPU views land; run heavyweights sequentially.

## Development Methodology (SDD + TDD + BDD)
1. **SDD**: every feature begins with a spec in the matching `docs/spec/*.md`
   file (hard rules and hazards also get a digest line here).
2. **TDD**: add a failing scenario first, then implement.
3. **BDD**: `test_bdd.sh` boots the image in QEMU and drives the shell over
   the serial console, asserting observable behaviour.
4. **Mutation testing**: `mutate.sh` injects one-line mutations into the
   kernel and the boot path, rebuilds and runs the suite. A mutant that
   survives is a test gap and must be closed by adding a scenario, never by
   deleting the mutant.
5. **Boy Scout rule**: technical debt and security defects found on the way
   are fixed, never deferred as out of scope.

Anchor hygiene: every `mutate.sh` expression must match its target file, or
`mutate.sh` reports BROKEN instead of a kill and the gate silently weakens.
`tools/check_mutant_anchors.py` (in `make lint`) applies each expression
with sed itself to a scratch copy and fails closed on any no-change anchor.
A BRE metacharacter left unescaped (notably a bare `*` where a literal star
stands in the source) matches nothing: always escape literals (`\*`) and
always run the checker after touching the table. The checker derives the
table bounds from the `MUTATIONS="` markers, never from line numbers: a
hardcoded range once silently dropped the last row (and would have dropped
every row added past it), so the range itself is structural now. The same
BRE caution applies to `test_bdd.sh` markers: `expect` matches with grep,
so a scenario must never assert a string containing `[...]` (`usage: wait
[pid]` matches one char of {p,i,d}, never the brackets; assert `usage:
wait` instead).

A mutant may only leave the set when it is provably *equivalent* — no input
can distinguish it from the original. That was the case for a mutant that
stopped `redirect_resume` from restoring the capture: every shell status
print is the last thing a command does, so nothing observable followed the
missed resume. It was replaced by `redirect-captures-nothing` and
`status-leaks-into-redirect`, which exercise the same contract through
effects the suite can actually see. Removing a mutant for any other reason
is forbidden; the answer to a survivor is a new scenario.


## Validation Gate (must pass before any commit)
Full `mutate.sh` and `test_bdd.sh` take hours: during work scope tests and
mutants to touched files (`tools/wm_scoped.sh`, `tools/wl_scoped.sh`,
`mutate.sh --match`), and run the full gate once at the end.
```bash
make                        # zero warnings
make lint                   # cppcheck + -Wextra (ring-3) + clang-tidy curated + bash -n + abi-numbers + fork-stubs + sanitize-audit + addons + mutant anchors
sh src/test_all.sh          # one-boot comprehensive non-interactive suite (96 PASS)
./tools/test_bdd.sh         # all scenarios green (full interactive suite)
python3 tools/test_gui_wm.py        # QMP pixels: gfx survives Alt+Tab/tile, taskbar button refocuses
python3 tools/test_gui_icon_cwd.py  # QMP pixels: dock launch ignores shell cwd
python3 tools/test_gui_fashion.py   # QMP pixels: one cursor, stable frames, ESC quit
python3 tools/test_gui_gfxview.py   # QMP pixels: fullscreen DOOM, Alt+Enter, tile, minimize, close
./tools/test_codecs.sh      # lzss/lz4/aes roundtrips (pass=3)
./tools/mutate.sh           # every mutant killed
make test-tls test-vma test-lisp test-wl test-freedom-wl test-freedomui
make test-futex test-percpu-rq test-batch test-rcu test-sanitize test-tick test-hal
make test-driver test-sync test-pcm test-rtc test-vedit test-file test-paint test-png
make test-doomedit test-theme test-wm test-fx test-pipe test-panic test-pci test-httpd
make test-fat test-ext4 test-ktime test-randmix
python3 tools/check_abi_numbers.py
python3 -m unittest -v mcp/test_minios_mcp.py   # unit + QEMU BDD
mcp/mutate_mcp.sh                                # every MCP mutant killed
python3 tools/check_cohesion.py KNOWLEDGE_BASE.jsonld
python3 tools/check_complexity.py --policy ARCH_POLICY.yaml
python3 tools/check_surprising.py KNOWLEDGE_BASE.jsonld
```

## Code Standards
- English only, no emojis, no inline commentary; docstrings above the code
  they describe.
- Production-ready: no placeholders, no simplifications.
- Every constant named; boot-path constants live in `bootdefs.h`, kernel
  constants at the top of their subsystem.
- No absolute filesystem paths and no host assumptions in the build.

## Tools Doctrine
Every helper that survives a session lives in `tools/` as a reusable
contract, never as a scratch file. I build each tool self-contained in one
file per contract, DRY and SOLID, production-ready with no placeholders and
no simplifications, secure by default, with an adhoc architecture for its
problem and no hardcoded values or magic numbers: every tunable lives in a
central config class. I write each tool in English without emojis and without
inline comments, using docstrings above the code they describe, with no
absolute paths from any machine and no host assumptions. I document every
tool with its purpose, usage, inputs, outputs and failure modes so a future
session reuses it instead of rebuilding it, and I keep `tools/` free of
single-use garbage: a script that cannot be reused does not land there. I
scope tests and mutations to touched files between runs (`tools/wm_scoped.sh`
pattern); I run `mutate.sh` and `test_bdd.sh` complete only at the end of a
todo list because the full suites take hours. I debug fast from inside MiniOS
with `trace on` followed by `sh src/test_all.sh`, `micropython src/test.py`
or `lua src/test.lua`, adding cases there when they prove behavior faster
than a host reboot.


## Security Requirements (Non-Negotiable)
- Every loader input is validated before use: ELF headers, section and
  relocation bounds, ramdisk table extents and per-file ranges.
- Size arithmetic is overflow checked before allocation (`size * n` included).
- Failure paths report and release; no silent partial state.
- No function symbol is ever resolved to a null address.
- Stack setup for user programs validates that argv writes stay within bounds.

## Project Knowledge Base (MUST read before coding)

MUST read `readmenator-agent/MANIFEST.json` first for freshness. NEVER `glob src/**` before `grep` in `readmenator-agent/INDEX.md`.

Orient first: `ls *.md readmenator-agent/ readmenator-wiki/` (docs only, ignore build noise). Then follow the workflow below.

Workflow: 1) `grep -n '<keyword>' readmenator-agent/INDEX.md readmenator-agent/SYMBOLS.md` 2) `cat readmenator-agent/KB_<subsystem>.md` 3) check `readmenator-agent/GOTCHAS.md` before editing.

This project contains analysis outputs generated by [ReadMenator](https://github.com/grisuno/ReadMenator), a zero-token polyglot static analysis tool.

**For humans:** Read `KNOWLEDGE_BASE.md` -- full architecture reference.

**For agents:** Read `readmenator-agent/INDEX.md` -- grep-friendly index.
  - `readmenator-agent/MANIFEST.json` -- freshness + entrypoints (start here)
  - `readmenator-agent/INDEX.md` -- file -> purpose map
  - `readmenator-agent/SYMBOLS.md` -- symbol index (grep-friendly)
  - `readmenator-agent/API.md` -- public functions + contracts
  - `readmenator-agent/GOTCHAS.md` -- "don't change X because Y breaks"
  - `readmenator-agent/KB_<subsystem>.md` -- per-subsystem context (grep-friendly)
  - `readmenator-agent/SECURITY.md` -- findings by severity
  - `readmenator-agent/recipes/*.md` -- actionable task blocks
**For agents (big picture first):** Read `readmenator-wiki/index.md` --
  overview, reading order, god nodes, connections. Then use the files above.

If MANIFEST date/commit is stale vs `git HEAD`, regenerate:

    pip install readmenator && readmenator . --rebuild
<!-- /readmenator-agent-kb-link -->
