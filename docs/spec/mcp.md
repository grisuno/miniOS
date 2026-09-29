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
roundtrip needs MiniOS syscalls 216/217 and is covered in-OS instead).

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
  most 512 lines with lines shorter than 128 chars, written as
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
  `minigcc`, `ld`, `cvm`, `lua`, `micropython`, `nuklear`, `nuked-opl3`,
  `doom`, `quake2`, `doomedit`). The YAML pins `repo_url`, the Makefile
  directory variable (`dir_var`), the pinned ref when one exists, the
  guest-visible `artifact`, the `host_build` make lines and the in-OS
  `verify` proof. `minios_install` refuses these before touching the
  session — the editor path cannot carry megabytes of host-built source,
  so a refusal naming the make target is the honest fail-closed behavior,
  never a half-installed package.
- `reference`: source-only checkouts that are never vendored, linked or
  built (`raycastlib`, the doomedit preview reference). No files, no
  build lines, no artifact: the YAML exists so the reference stays pinned
  and reproducible from its upstream alone.
- `make addons` (`tools/check_addons.py`) validates every file and runs
  inside `make lint`: a new dependency lands its YAML, its Makefile
  `*_URL`/`*_DIR` (overridable, never absolute), its `make sources`
  clone block and its README table row together, or it does not land.
  The README addon table mirrors the `addons/` directory one row per
  file; a row without a file (or a file without a row) is drift.

### Validation
- `minios_write` and `minios_cat` accept file names over a strict
  character whitelist (`[A-Za-z0-9._/-]`, no leading `/`, no `..`, bounded
  length). Content lines must be printable ASCII (32..126): that is what
  the kernel readline can carry. Content is also bounded by the editor
  limits (`EDIT_LINE_MAX` chars per line, `EDIT_MAX_LINES` lines): longer
  input is rejected up front, because the kernel would truncate it
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
link with `run objects/ld.o -f elf -o bin/f.elf asm/f.s`, run and read `exit code: N`,
power off when done. It also documents the headless browser (`freedom`,
plain command path, http only) and the addon marketplace
(`minios_addons` / `minios_install`, dogfooded by `mcp/mcp_dogfood.py`).
Extending miniGCC, `ld` or cvm/cvm2 happens on the host against the
sibling repositories (clone to a scratch dir, `make`, suites); only the
result travels into the OS.
