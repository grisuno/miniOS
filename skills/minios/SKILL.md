---
name: minios
description: Build, compile, link and run software inside MiniOS over the minios-* MCP tools that drive its QEMU serial console. Use whenever the user asks to write code inside MiniOS, extend MiniOS or its toolchain (miniGCC, ld, cvm/cvm2), run or test a program in the OS, or work with the boot repository.
---

# MiniOS development over the MCP bridge

MiniOS is driven through the `minios-*` MCP tools. The MCP owns the QEMU
child and the serial console; never start QEMU by hand, never run
`test_bdd.sh` scenarios through Bash while the MCP has a machine booted.

## Core loop

Boot once and keep the machine for the whole session:

```text
minios_boot          waits for the shell prompt; returns the boot log
minios_status        {booted, pid, log_bytes}
```

Everything else goes through the shell. `minios_send` sends ONE line, waits
for the next `miniOS> ` prompt and returns everything the kernel printed in
between, including `exit code: N`. Never send a multi-line command; use one
`minios_send` per line.

Compile, link and run inside the OS:

```text
minios_write {path: "p.c", content: "int main(void) { return 7; }\n"}
minios_send {line: "run minigcc.o p.c > p.s"}    redirect captures the asm
minios_send {line: "run ld.o -f elf -o p.elf p.s"}
minios_send {line: "run p.elf"}                   output ends with exit code: 7
```

The CVM path is `run ld.o -f cvm -o p.cvm p.s` and `run p.cvm`. The
self-hosted compiler is `minigcc.elf` (compiled by miniGCC itself, linked
by ld); use it instead of `minigcc.o` to run the milestone compiler.

Read and write files:

```text
minios_write {path, content}   editor flow: edit, a per line, x; returns the
                               transcript (watch for "refusing to save")
minios_cat {path}              prints a ramdisk file
```

`minios_write` rejects lines of 128+ chars, more than 512 lines, non-ASCII
and control characters: those are kernel editor limits, and the kernel would
truncate silently. Break long content into files that fit; a real C file
with long lines can be assembled from chunks, but prefer short lines.

## Waiting for markers

`minios_expect {marker}` waits for a marker not yet consumed. After every
command the prompt is consumed by `minios_send` itself, so `expect` is for
shutdown or long-running output; a marker that already scrolled past the
consume cursor returns `matched: false` after the timeout, which is the
correct signal that nothing new happened.

`minios_snapshot` shows the unconsumed console tail without consuming it.

## Internet inside the OS

The headless browser ships as `bin/freedom` (curlfree-style engine,
FreeDom-style omnibox):

```text
minios_send {line: "freedom example.com"}       omnibox: a query searches
minios_send {line: "freedom http://10.0.2.2:8899/README.txt"}
```

No `run` prefix: `bin/freedom` resolves through the command path like
`cp`. It speaks plain http only; `https://` is refused with a diagnostic
(exit code 2), dangerous schemes are searched, never executed, and page
bytes pass a UTF-8 gate before reaching the console. For a fetch target,
serve files from the host (for example `python3 -m http.server 8899`) and
address it as `http://10.0.2.2:8899/...`.

## The addon marketplace

Programs travel from git into the OS through `addons/*.yaml` (repo URL,
files, build and verify shell lines):

```text
minios_addons                      list addons and their installed state
minios_install {name: "freedom"}   clone, upload, build inside the OS,
                                   run the verify lines, record the install
```

An install splits each source into editor-sized parts, uploads them with
`minios_write`, reassembles with `cat` redirects (append included), then
runs the `build` lines and asserts the `verify` exit codes. A failure at
any step aborts and never records a half-installed package. Dogfooding the
marketplace end to end is `mcp/mcp_dogfood.py <addons-dir>`: it drives the
MCP server over stdio, installs `freedom` from a git repo and browses with
the installed binary.

## Error recovery

A `minios_send` that times out means the command did not finish (or a
previous one is still running: the editor or a program may be waiting for
input). Recover by reading `minios_snapshot` to see where the machine is,
then send the input the active prompt expects (`edit> ` commands, or a
line the editor's `a` is waiting for). Never blind-type commands after a
timeout.

Finish with `minios_poweroff` (asserts `powering off` and QEMU exit). A
session that ends without poweroff leaves a stale QEMU; the next
`minios_boot` reaps it automatically.

## Extending the toolchain

MiniOS, miniGCC, ld and cvm/cvm2 live in sibling repositories. Extending
the toolchain is a host-side job: clone or copy the repositories into a
scratch directory (for example under /tmp), apply SDD+TDD+BDD there, run
their suites (miniGCC `test.sh`, ld `tests/run_tests.sh` and
`tests/mutate.sh`, cvm suite, MiniOS `make`, `test_bdd.sh`, `mutate.sh`,
`mcp/test_minios_mcp.py`, `mcp/mutate_mcp.sh`), then rebuild the ramdisk
with `make` in the MiniOS repository and verify the change inside the OS
through this bridge.

## Limits that shape the code you write

The editor line is 127 printable ASCII characters, 512 lines per buffer,
files larger than the buffer open read-only. miniGCC compiles the C subset
documented in its README. The OS runs ELF (ET_EXEC/ET_DYN, syscall ABI),
ET_REL objects linked against the kernel, and CVM modules. Programs are
written to the ramdisk only: every file lives in memory and is lost on
poweroff unless it ships in `progs/` on the host.

## Working rhythm

Write a source file, compile, link, run, read the exit code, iterate. Keep
output small: `exit code: N` is the assertion currency for programs; for
text, `puts` through the mini libc prints to the console. Before declaring
a change done, run it through the full in-OS loop once and power off.
