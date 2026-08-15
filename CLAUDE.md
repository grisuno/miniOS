# MiniOS Contract

## Purpose
MiniOS is a 64-bit x86 teaching kernel that hosts the miniGCC toolchain. It
boots from a raw disk image, runs programs in three formats, and carries the
whole toolchain on its ramdisk so that programs can be written, compiled,
linked and executed without ever leaving the machine:

```
edit p.c                        write C inside the OS
run minigcc.o p.c > p.s         compile to x86-64 AT&T assembly
run ld.o -f elf -o p.elf p.s    assemble and link
run p.elf                       execute
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

## Source Contract
The system spans four repositories: this one plus
[miniGCC](https://github.com/grisuno/miniGCC),
[ld](https://github.com/grisuno/ld) and
[cvm](https://github.com/grisuno/cvm). The build must be reproducible from
those upstreams alone, so:

- `make sources` clones the missing ones and `make sources-update` pulls
  them. Neither ever modifies a directory that already exists, so a checkout
  with local work is never clobbered.
- Every location is overridable (`MINIGCC_DIR`, `LD_DIR`, `CVM_REPO_DIR`,
  `CVM_DIR`) and so is every origin (`MINIGCC_URL`, `LD_URL`, `CVM_URL`).
  Nothing in the build assumes an absolute path.
- Everything on the ramdisk is regenerated from source: `minigcc.o`, `ld.o`
  and `cvm.o` from the sibling checkouts, and the demo programs from this
  repository's own C sources in `progs/`, driven through miniGCC and `ld`.
  The prebuilt objects in `progs/` are a convenience for a first boot, never
  an input the build depends on.
- Ramdisk content is owned here. Reaching into another project's test
  fixtures for files to ship would break the moment that project reorganizes
  them, which is exactly what happened when the image was built from
  `ld/tests/*.s`.
- `ramdisk.bin` lists the `Makefile` among its prerequisites: the file list
  lives there, so editing it must invalidate the image even when no
  individual file changed.
- `progs/bin/` ships the first command-path utility: `cp`, compiled from
  this repository's own `progs/bin/cp.c` through the miniGCC-to-ld chain,
  with the source on the ramdisk too so the OS can rebuild the utility
  from scratch without leaving the machine.

## Boot Path Contract
Two stages, because a correct single-stage loader does not fit in 512 bytes.
Every address, BIOS service, descriptor and control-register bit used by the
boot path is named in `bootdefs.h`; neither stage may carry a bare constant.

- `stage1.S` — the boot sector. Verifies INT 13h extended (LBA) support, reads
  stage 2 and jumps to it. Ends with `.org` so the assembler fails if the code
  ever outgrows the sector.
- `stage2.S` — the loader. Enables A20 (clearing the fast-reset bit before
  writing port 0x92), streams the kernel in 64 KB chunks through the staging
  buffer at 0x10000, copies each chunk above 1 MB during a short excursion
  into protected mode, builds identity-mapped 2 MB page tables for the first
  gigabyte, enables PAE and long mode, installs the 64-bit GDT at 0x8000 and
  jumps to the kernel at 0x100000. Loop state lives in memory, never in
  registers, so nothing is assumed about what the firmware preserves across
  INT 13h. Ends with `.org` to enforce its sector reservation.

The image is attached as an IDE disk: LBA addressing is not available for
floppies.

### Disk layout
```
LBA 0        stage 1
LBA 1 .. 8   stage 2
LBA 9 ..     kernel image (kernel.bin, ramdisk embedded)
```
`KERNEL_SECTORS` is supplied by the build from the size of `kernel.bin`; the
LBA constants come from `bootdefs.h` so the Makefile and the assembly cannot
disagree.

### Physical memory map
```
0x00000-0x004FF  IVT and BIOS data area
0x01000-0x04FFF  long-mode page tables (PML4, PDPT, PD)
0x07C00-0x07DFF  stage 1
0x07E00-0x07E10  disk address packet and boot drive
0x08000-0x08017  long-mode GDT handed to the kernel
0x09000-0x0AFFF  stage 2
0x10000-0x8FFFF  kernel staging buffer
0x90000          protected/long mode stack top
0x100000         kernel image
0x400000         user program load base
0x2000000        kernel heap (64 MB)
```

## Kernel Contracts

### Ramdisk
The data area is sized from the image that is loaded plus a spare margin, and
grows on demand up to `RD_DATA_MAX`; it is never a fixed reservation that the
payload can silently outgrow. `ramdisk_setup_from` validates the whole image
(header, table extent, per-file offset and size, total against the maximum)
**before** publishing any entry, so a rejected image leaves the directory
untouched instead of advertising files whose data was never copied.

### ELF loaders
Relocation is fail-closed. Every relocation is bounds checked against the
section it patches; a relocation symbol index outside the symbol table, an
unsupported relocation type, or a symbol that the kernel cannot resolve
aborts the load with a diagnostic. An unapplied relocation would hand the
program a wild call target, so it is never skipped. No libc name is ever
registered with a null address.

### Shell
`cmd > file` redirects the command's console output into a ramdisk file.
Shell status text — exit codes and the shell's own diagnostics — is lifted
out of the capture: a redirection captures what the command wrote, not what
the shell reported about it. This is what makes `run minigcc.o p.c > p.s`
produce assembly a linker can consume.

Command resolution is a fixed order: builtin, registered program, then the
command path. The path is the ramdisk directory prefix `SHELL_BIN_PATH`
(`bin/`): a non-builtin name without a `/` is looked up as `bin/<cmd>`,
loaded as an ELF and run with the original argv, so `cp fib.c x.txt` works
without `run` or `load`, exactly like Linux `/bin`. Lookup bounds:
the command must be 1..`SHELL_BIN_MAX_CMD` characters and contain no `/`,
so a name can never escape the path prefix; the exit code is reported
exactly as `run` reports it. Files that are not ELF are skipped and the
name falls through to `command not found`.

### Ramdisk names
File names are at most `RAMDISK_FNAME_LEN - 1` characters. Names may
contain `/`, which is how directories are expressed (`bin/cp`): the ramdisk
is flat, the slash is data. `mkramdisk.py` derives each name from the path
relative to the shared parent of the packed files, so `progs/bin/cp` ships
as `bin/cp`. A name longer than the bound or a collision between two files
is a build error, never a silent truncation that would make a lookup miss.

### Editor (`edit`)
A line editor over ramdisk files: `h l p e a i d w x q q!`. Two invariants:
- A buffer that did not hold the whole file is marked truncated and refuses
  to be written back, because saving it would drop what was never loaded.
- `q` refuses to discard unsaved changes; `q!` discards explicitly.

## Development Methodology (SDD + TDD + BDD)
1. **SDD**: every feature begins with a spec in this file.
2. **TDD**: add a failing scenario first, then implement.
3. **BDD**: `test_bdd.sh` boots the image in QEMU and drives the shell over
   the serial console, asserting observable behaviour.
4. **Mutation testing**: `mutate.sh` injects one-line mutations into the
   kernel and the boot path, rebuilds and runs the suite. A mutant that
   survives is a test gap and must be closed by adding a scenario, never by
   deleting the mutant.
5. **Boy Scout rule**: technical debt and security defects found on the way
   are fixed, never deferred as out of scope.

A mutant may only leave the set when it is provably *equivalent* — no input
can distinguish it from the original. That was the case for a mutant that
stopped `redirect_resume` from restoring the capture: every shell status
print is the last thing a command does, so nothing observable followed the
missed resume. It was replaced by `redirect-captures-nothing` and
`status-leaks-into-redirect`, which exercise the same contract through
effects the suite can actually see. Removing a mutant for any other reason
is forbidden; the answer to a survivor is a new scenario.

## Validation Gate (must pass before any commit)
```bash
make                # zero warnings
./test_bdd.sh       # all scenarios green
./mutate.sh         # every mutant killed
python3 -m unittest -v mcp/test_minios_mcp.py   # unit + QEMU BDD green
mcp/mutate_mcp.sh                                # every MCP mutant killed
```

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
- One QEMU child per server, guarded by a pid file under the system temp
  dir. A stale QEMU process is reaped on boot; the child is terminated on
  server exit and never left behind.

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
| `minios_poweroff` | `poweroff`, wait for `powering off` and QEMU exit, release the pid file |

Every tool carries a `timeout_ms` parameter capped by a config constant; a
wait that expires is an error, never a silent hang. The host shell is never
invoked (`shell=False` everywhere); the only shell driven is the one inside
MiniOS.

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
(`MINIOS_IMAGE`, `QEMU`, `MINIOS_MEM`, `MINIOS_LOG_CAP`, the timeout
family). The default image path is derived from the script's own directory,
never from a host assumption.

### Tests
- `mcp/test_minios_mcp.py`: unit tests (protocol dispatch, validation,
  buffer and cursor semantics, config) plus BDD scenarios that boot the
  real image in QEMU and exercise the full edit/compile/link/run loop,
  including the self-hosted `minigcc.elf`. QEMU scenarios skip cleanly
  when QEMU or `os.img` is absent.
- `mcp/mutate_mcp.sh`: one-line mutations of `minios_mcp.py`; every mutant
  must be killed by the suite. A survivor is a test gap.

### Skill
`skills/minios/SKILL.md` documents the workflow an agent follows: boot once,
write sources with `minios_write`, compile with `run minigcc.o f.c > f.s`,
link with `run ld.o -f elf -o f.elf f.s`, run and read `exit code: N`,
power off when done. Extending miniGCC, `ld` or cvm/cvm2 happens on the host
against the sibling repositories (clone to a scratch dir, `make`, suites);
only the result travels into the OS.

## Code Standards
- English only, no emojis, no inline commentary; docstrings above the code
  they describe.
- Production-ready: no placeholders, no simplifications.
- Every constant named; boot-path constants live in `bootdefs.h`, kernel
  constants at the top of their subsystem.
- No absolute filesystem paths and no host assumptions in the build.

## Security Requirements (Non-Negotiable)
- Every loader input is validated before use: ELF headers, section and
  relocation bounds, ramdisk table extents and per-file ranges.
- Size arithmetic is overflow checked before allocation.
- Failure paths report and release; no silent partial state.
- No function symbol is ever resolved to a null address.
