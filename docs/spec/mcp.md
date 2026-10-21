# MCP bridge contract and addon marketplace

Moved verbatim from CLAUDE.md (2026-09-29 compaction); CLAUDE.md keeps the
rules and hazards and indexes this file.

## MCP Bridge Contract

### Purpose
`mcp/minios_mcp.py` exposes MiniOS as a programmable environment over the
MCP protocol. It boots `os.img` in QEMU, drives the shell over a pty-backed
serial console, and gives an agent tools to write, compile, link and run
software inside the OS. The companion skill `skills/minios/SKILL.md` teaches
the workflow; this section is the engineering contract.

### Architecture
One file per contract, Python 3 standard library only, no dependencies.

- Transport: stdio JSON-RPC 2.0 (MCP): `initialize`, `tools/list`,
  `tools/call`, `ping`; notifications are accepted and not answered.
- QEMU is a child process owning a pty: serial console on the slave, server
  on the master. The slave runs raw (no echo, no line discipline): the
  kernel echoes input itself, so a cooked pty would duplicate every line.
- A reader thread appends console output to a bounded ring buffer (oldest
  bytes dropped, total counted). Marker waits search from a consume cursor,
  so output already seen can never satisfy a later wait.
- One QEMU child per server, guarded by a pid file (system temp dir by
  default, overridable with `MINIOS_PIDFILE`). A stale QEMU process is
  reaped on boot; the child is terminated on server exit and never left
  behind.

### Tools
| Tool | Contract |
|------|----------|
| `minios_status` | `{booted, pid, log_bytes, log_cap}`; never fails |
| `minios_boot` | spawn QEMU, wait for the `miniOS> ` prompt, return boot log; idempotent when already booted |
| `minios_snapshot` | tail of the log since the consume cursor (peek, does not consume) |
| `minios_send` | send one shell line, wait for the next prompt, return the output in between (this is how `run p.elf` reports `exit code: N`) |
| `minios_expect` | wait for a marker after the cursor; cursor advances to the end of the match |
| `minios_write` | create or replace a ramdisk file through the editor (`edit`, `a` per line, `x`); returns the editor transcript |
| `minios_cat` | print a ramdisk file |
| `minios_python` | run a ramdisk script with the in-OS MicroPython (`micropython <script> [args...]`); returns the output with its `exit code: N` (see `### Python tools`) |
| `minios_py_eval` | evaluate a MicroPython one-liner inside the OS (see `### Python tools`) |
| `minios_test` | generic scenario harness: send a list of shell commands, assert each `expect` marker appears and each `refute` marker does not in the produced output; returns `{pass, failures, transcript}`. This is the reusable in-OS test tool, so a session never hand-rolls a boot-and-assert script. |
| `minios_poweroff` | `poweroff`, wait for `powering off` and QEMU exit, release the pid file |

Every tool carries a `timeout_ms` parameter capped by a config constant; a
wait that expires is an error, never a silent hang. A caller's budget is a
budget for the whole job: boot is bounded on its own, its marker waits are
capped by the boot timeout, so a stuck prompt can never burn an install's
full budget before failing. The host shell is never invoked
(`shell=False` everywhere); the only shell driven is the one inside
MiniOS.

For host-side verification of the miniGCC-built command tools there is a
reusable harness, `tests/host_codecs.sh <progs_dir>`: it drives the static
ELF tools on the host (lzss/unlzss roundtrip + fail-closed + bidirectional
interop against the reference Okumura codec; lz4's fail-closed path; the lz4
roundtrip needs MiniOS syscalls 216/255 and is covered in-OS instead).

### Python tools
Two tools put the guest interpreters behind the same session, so a script
runs inside the machine without leaving it:

- `minios_python {script, args?, timeout_ms?}` sends `micropython <script>
  [args...]` to the shell and returns the console output, including the
  shell's `exit code: N` line. The command is assembled by joining the
  script path and the arguments with spaces: the kernel shell splits on
  spaces and carries no quoting, so neither the path nor an argument may
  contain one.
- `minios_py_eval {code, timeout_ms?}` evaluates a one-liner. The code is
  written to the ramdisk script `tmp/_eval.py` through the editor path (so
  it inherits the printable-ASCII, per-line and buffer limits of
  `minios_write`) and then run with `minios_python`; `micropython -c` is
  not an option, because the shell would split the quoted argument. The
  temporary script stays on the ramdisk until poweroff.

The guest toolchains reached this way ship with the image:

| Script | Role |
|--------|------|
| `src/build.py` | self-hosted toolchain orchestrator: the edit, minigcc, ld and run pipeline as one in-OS program (`micropython src/build.py [target...]`) |
| `src/shell.py` | pybash, a Python shell layer (pipelines, variables, control flow) over the untouched C shell |
| `src/test.py` | the in-OS suite, driven by MicroPython over every available binary |
| `src/test.lua` | the same suite driven by the host-built Lua interpreter (`lua src/test.lua`) |
| `src/test.lisp` | the same suite driven by the host-built Lisp interpreter (`lisp src/test.lisp`) |

### Addon marketplace (lazyaddons-style)
Addons are YAML files in `addons/`, one per package, inspired by LazyOwn's
lazyaddons: metadata plus an `install` block that says where the code comes
from and how it is built *inside* the OS. The marketplace is how new
programs travel from GitHub into a running MiniOS without ever rebuilding
the image.

```yaml
name: cp
description: Command-path utility cp, rebuilt from its C source in the OS.
author: miniOS
version: "1.0.0"
install:
  repo_url: https://github.com/grisuno/miniOS.git
  files:
    - src: progs/src/cp.c
      dst: build/cp.c
  build:
    - run objects/minigcc.o build/cp.c > build/cp.s
    - run objects/ld.o -f elf -o bin/cp build/cp.s
    - run sign bin/cp
  verify:
    - line: cp src/cp.c build/cp2.c
      exit_code: 0
```

- `minios_addons` lists the addons and whether each is installed. The
  marketplace ships `cp` and `freedom`; the freedom addon is the dogfood
  of the whole system: its source travels from git into the OS and is
  rebuilt inside the OS by miniGCC and `ld` as `bin/freedom-mini` (the
  http-only twin; https needs the host-built `freedom`).
- `minios_install <name>` boots the machine if needed, clones `repo_url`
  (`git clone`, `shell=False`, bounded timeout), uploads each `files` entry
  into the OS through the editor, builds with the `build` shell lines and
  asserts the `verify` exit codes. Success records the addon in the in-OS
  registry `var/lib/addons.txt` and in a host state file under the system
  temp dir; a failure at any step reports and aborts, never records a
  half-installed package, and removes its upload parts.
- Editor limits are the upload contract: a source is split into parts of at
  most 511 lines (`ADDON_CHUNK_LINES`, one below the 512-line editor buffer)
  with lines of at most 127 chars (`ADDON_CHUNK_LINE_MAX`), written as
  `<dst>.partN` and reassembled one `cat` invocation per part
  (`cat <dst>.part0 > <dst>` then `cat <dst>.partN >> <dst>`), because each
  invocation contributes exactly one trailing newline, which is what joins
  the parts; the reassembled file is read back and must equal the source
  byte for byte (modulo the trailing newline). A source with a line the
  kernel readline cannot carry is rejected up front.
- The YAML dialect is a strict subset parsed by stdlib-only code (no
  PyYAML): keys are whitelisted, names bounded, `dst` paths validated like
  tool paths, build/verify lines printable ASCII. The host shell is never
  invoked; the only shell driven is the one inside MiniOS.
- `mcp/mcp_dogfood.py <addons-dir>` is the end-to-end marketplace check:
  it drives the MCP server over stdio JSON-RPC, installs `freedom` from a
  git repo into the booted OS, then browses with the installed binary
  (plain command path, no `run`).

### Addon doctrine (every external source is an addon)
The marketplace is the one package index, not just the guest-install path.
Every external source — sibling checkout, nested upstream, vendored tree
or in-repo program — carries an `addons/<name>.yaml`, and adding a new
third-party dependency without one fails `make addons` review exactly like
a missing BDD scenario fails a feature. Three kinds share one dialect
(`mcp/minios_addons.py`, stdlib-only, no PyYAML):
- `guest` (default): built *inside* the OS through the editor-upload
  contract above. Only small miniGCC-compilable sources qualify (`cp`,
  `freedom-mini`). `minios_install` serves these and nothing else.
- `host`: built on the host with the ordinary gcc toolchain and packed
  into the image by `make` (toolchain, interpreters, engines, libraries:
  `minigcc`, `ld`, `cvm`, `lua`, `micropython`, `lisp`, `nuklear`,
  `nuked-opl3`, `doom`, `quake2`, `doomedit`, `minicraft`, `wlmini`).
  The YAML pins `repo_url`, the Makefile directory variable (`dir_var`),
  the pinned ref when one exists, the guest-visible `artifact`, the
  `host_build` make lines and the in-OS
  `verify` proof. `minios_install` refuses these before touching the
  session — the editor path cannot carry megabytes of host-built source,
  so a refusal naming the addon, its kind and the make-built path is the
  honest fail-closed behavior, never a half-installed package.
- `reference`: source-only checkouts that are never vendored, linked or
  built (`raycastlib`, the doomedit preview reference). No files, no
  build lines, no artifact: the YAML exists so the reference stays pinned
  and reproducible from its upstream alone.
- `make addons` (`tools/check_addons.py`) validates every file and runs
  inside `make lint`: a new dependency lands its YAML, its Makefile
  `*_URL`/`*_DIR` (overridable, never absolute), its `make sources`
  clone block and its row in the addon table below together, or it does
  not land. The addon table mirrors the `addons/` directory one row per
  file; a row without a file (or a file without a row) is drift.

### Addon table
One row per file in `addons/`: the marketplace index. `Kind` is the
`install.kind` key (`guest` by default), `Origin` is where the source comes
from and `Artifact` is what the guest ends up with.

| Addon | Kind | Origin | Artifact |
|-------|------|--------|----------|
| `cp` | guest | in-repo `progs/src/cp.c` | `bin/cp` (built in-OS) |
| `freedom` | guest | in-repo `progs/src/freedom.c` | `bin/freedom-mini` (built in-OS) |
| `minigcc` | host | sibling `../miniGCC` | `objects/minigcc.o` |
| `ld` | host | sibling `../ld` | `objects/ld.o` |
| `cvm` | host | sibling `../cvm` (checkout `cvm2`) | `objects/cvm.o` |
| `lua` | host | sibling `../lua` (`v5.4.7`) | `lua` on MiniFS |
| `micropython` | host | sibling `../micropython` (`v1.28.0`) | `micropython` on MiniFS |
| `lisp` | host | in-repo `progs/lisp` | `lisp` on MiniFS |
| `nuklear` | host | sibling `../nuklear` | `nuklear` on MiniFS |
| `nuked-opl3` | host | sibling `../nuked-opl3` | `opl3` on MiniFS |
| `doom` | host | vendored `progs/doomgeneric` | `doomgeneric.elf` on MiniFS |
| `quake2` | host | nested `progs/quake2generic/quake2generic` | `quake2generic.elf` on MiniFS |
| `doomedit` | host | in-repo `progs/doomedit` | `doomedit` on MiniFS |
| `minicraft` | host | in-repo `progs/minicraft` | `minicraft` on MiniFS |
| `wlmini` | host | in-repo `progs/wl` | `wlcomp` on MiniFS |
| `raycastlib` | reference | sibling `../raycastlib` | none (preview reference only) |

- Only the `guest` rows are served by `minios_install`, and their artifact
  is produced inside the OS by the addon's own `build` lines. The `host`
  rows are packed into the image by `make`; their YAML pins the source
  tree through `dir_var`, the Makefile variable that locates it
  (`MINIGCC_DIR`, `LD_DIR`, `CVM_DIR`, `LUA_DIR`, `MICROPYTHON_DIR`,
  `NUKLEAR_DIR`, `NUKED_OPL3_DIR`, `PROGS_DIR`), plus the pinned `ref`
  when the upstream has one (`v5.4.7` for Lua, `v1.28.0` for
  MicroPython). The `reference` row pins `RAYCASTLIB_DIR` and builds
  nothing.
- The install record has two halves: the in-OS registry
  `var/lib/addons.txt` holds one `name version` line per addon, and the
  host state file (`MINIOS_ADDON_STATE`, default
  `<tempdir>/minios_mcp_addons.json`) holds
  `{"addons": {name: {version, installed_at}}}`. `minios_addons` reports
  the `installed` flag from the host side.

### Validation
- `minios_write` and `minios_cat` accept file names over a strict
  character whitelist (`[A-Za-z0-9._/-]`, no leading `/`, no `..`, bounded
  length). Content lines must be printable ASCII (32..126): that is what
  the kernel readline can carry. Content is also bounded by the editor
  limits (`CFG_EDIT_LINE_MAX` chars per line, `CFG_EDIT_MAX_LINES` lines):
  longer input is rejected up front, because the kernel would truncate it
  silently. Anything invalid is rejected before a single byte reaches the
  console.
- JSON-RPC input is parsed and validated; a malformed message is answered
  with a JSON-RPC error, never an exception.
- Buffer sizes and timeouts are bounded by named constants; the reader
  thread is daemonized and the child is reaped through `atexit` and signal
  handlers so no error path leaks a QEMU process or a pty.

### Config
Defaults are named constants; the environment overrides them
(`MINIOS_IMAGE`, `QEMU`, `MINIOS_MEM`, `MINIOS_LOG_CAP`, `MINIOS_PIDFILE`,
`MINIOS_ADDON_STATE`, the timeout family). The default image path is
derived from the script's own directory, never from a host assumption.

### Tests
- `mcp/test_minios_mcp.py`: unit tests (protocol dispatch, validation,
  buffer and cursor semantics, config) plus BDD scenarios that boot the
  real image in QEMU and exercise the full edit/compile/link/run loop,
  including the self-hosted `minigcc.elf`. QEMU scenarios skip cleanly
  when QEMU or `os.img` is absent. The QEMU-backed classes fail fast:
  once a tool call has hit a console wait timeout, the bridge is stuck
  and the remaining tests are skipped instead of each burning a full
  timeout.
- `mcp/mutate_mcp.sh`: one-line mutations of `minios_mcp.py`; every mutant
  must be killed by the suite. A survivor is a test gap. Mutant suites run
  in parallel (`MUTATE_JOBS`, default 4) with a per-mutant pid file and
  addon state, so the runs stay independent; the shortened timeout family
  bounds the waits of a mutant that breaks the console.

### Skill
`skills/minios/SKILL.md` documents the workflow an agent follows: boot once,
write sources with `minios_write`, compile with `run objects/minigcc.o f.c > asm/f.s`,
link with `run objects/ld.o -f elf -o bin/f.elf asm/f.s`, sign with
`run sign bin/f.elf`, run and read `exit code: N`,
power off when done. It also documents the headless browser (`freedom`,
plain command path, http only) and the addon marketplace
(`minios_addons` / `minios_install`, dogfooded by `mcp/mcp_dogfood.py`).
The Python tools are documented by this spec, not by the skill: it covers
the console tools and the marketplace.
Extending miniGCC, `ld` or cvm/cvm2 happens on the host against the
sibling repositories (clone to a scratch dir, `make`, suites); only the
result travels into the OS.
