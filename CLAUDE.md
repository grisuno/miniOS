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
`cmd > file` redirects the command's console output into a ramdisk file
(truncating it); `cmd >> file` appends. Shell status text — exit codes and
the shell's own diagnostics — is lifted out of the capture: a redirection
captures what the command wrote, not what the shell reported about it.
This is what makes `run minigcc.o p.c > p.s` produce assembly a linker can
consume.

The prompt keeps a bounded command history (`SHELL_HIST_MAX` entries).
Up arrow (ESC `[` `A`, or PS/2 make code `E0 48`) recalls the previous
command onto the edit line; down arrow (ESC `[` `B`, `E0 50`) moves
forward again, back to the live line. The recalled text replaces the
line the user was typing, which is preserved while scrolling. The
history stores commands on submission (even unknown ones), skips
consecutive duplicates, and survives only until reboot. A bare ESC or
an incomplete escape sequence is discarded, never inserted into the
line, and the editor (`edit`) is unaffected: history is a shell-prompt
feature, not a readline library.

Command resolution is a fixed order: builtin, registered program, then the
command path. The path is the ramdisk directory prefix `SHELL_BIN_PATH`
(`bin/`): a non-builtin name without a `/` is looked up as `bin/<cmd>`,
loaded as an ELF and run with the original argv, so `cp fib.c x.txt` works
without `run` or `load`, exactly like Linux `/bin`. Lookup bounds:
the command must be 1..`SHELL_BIN_MAX_CMD` characters and contain no `/`,
so a name can never escape the path prefix; the exit code is reported
exactly as `run` reports it. Files that are not ELF are skipped and the
name falls through to `command not found`.

### Network (rtl8139 + slirp)
The kernel owns an rtl8139 NIC under QEMU user networking (slirp) with the
standard fixed configuration: address `10.0.2.15`, netmask `255.255.255.0`,
gateway `10.0.2.2` (the host), DNS `10.0.2.3`. Every QEMU launch in the
build, the BDD suite and the MCP attaches `-nic user,model=rtl8139`.

- The driver polls the NIC (no interrupt controller is configured): TX
  waits for the descriptor owner bit, RX drains the classic ring by
  comparing CAPR against CBR. The MAC is read from the NIC IDR registers.
- Stack: Ethernet (ARP cache, broadcast requests, replies to our address),
  IPv4 (checksum verified; fragmented datagrams are dropped, fail closed),
  ICMP echo, UDP and a minimal client TCP: SYN/SYN-ACK/ACK handshake,
  stop-and-wait with retransmission timeouts (PIT-calibrated TSC clock),
  FIN teardown, fixed 536-byte MSS and a bounded window. A kernel DNS
  client resolves A records against `10.0.2.3` (UDP, retries, bounded
  timeout).
- Programs reach the stack two ways. ET_REL programs get the libc-style
  symbols `net_open`, `net_connect` (resolves the hostname itself),
  `net_send`, `net_recv` (0 = EOF) and `net_close`. Linux binaries get
  the socket syscalls: `socket`, `connect`, `sendto`, `recvfrom`,
  `shutdown`, `close` and a minimal `poll` (POLLIN when data is ready,
  bounded timeout otherwise) — enough for a static glibc resolver.
- The shell gets `net` (status: MAC, IP, counters) and `net ping <ip>`
  (one ICMP echo, reported as `reply from <ip>` or a timeout diagnostic).
- All constants are named in `net.h` (`NET_*`); none of the fixed
  addresses, ports or timeouts appears as a bare literal.

### TLS client (tls.c + tls_crypto.c + tls_x509.c)
The kernel speaks TLS 1.2 as a client over an established TCP socket, so
`https://` works without the browser ever touching key material. The scope
is fixed and fail-closed: no downgrade, no fallback, no session resumption.

- Handshake: `TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256` (0xC02F) and
  `TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256` (0xC02B). ClientHello carries
  SNI (the request host), the secp256r1 (23) group only and both signature
  algorithms; every message feeds the running handshake hash, and the
  server's Finished is verified before the first application byte is
  accepted. Application data is AES-128-GCM, one record = one TLS record,
  GCM tag verified before any plaintext byte is released.
- Crypto (all constant-time where it counts, no table lookups indexed by
  secret bytes): SHA-256, HMAC-SHA256, the TLS 1.2 PRF, AES-128-GCM with a
  GHASH that never branches on key bits, P-256 and P-384 field arithmetic
  for ECDSA verify and P-256 ECDHE, and RSA PKCS#1 v1.5 verify (SHA-256)
  up to 4096-bit moduli for the chain and the ServerKeyExchange signature.
  The ECDHE private scalar is rejected unless it is a valid non-zero
  scalar, so invalid-curve attacks have nothing to land on.
- Certificate chain: X.509 DER parsed from the Certificate message; the
  leaf is verified against the presented chain down to an embedded root
  (`ISRG Root X1`, `DigiCert Global Root CA`, `GlobalSign Root CA`), the
  leaf public key must match the handshake signature, the hostname must
  match a SAN `dNSName` or the subject CN (exact or `*.`-single-label
  wildcard), and the validity window is checked against the CMOS RTC.
  Any parse error, unknown signature algorithm, expired chain, wrong
  hostname or bad signature aborts with `freedom: tls: <stage>: <reason>`
  and the session is freed.
- Session state is heap-allocated per handshake and freed on `close`; a
  socket without TLS costs nothing. Handshake reads are deadline-bounded
  (`net_recv_timeout`), so a silent peer cannot hang the shell forever.
- Client random: the kernel has no CSPRNG; the ClientRandom mixes the TSC,
  accumulated RX bytes/frames and the retransmit counters. Documented,
  not hidden.
- Syscall surface (ld stubs, MiniOS namespace like 200 = dns): 201
  `tls_handshake(fd, host)` on an already connected TCP socket, 202
  `tls_send(fd, buf, len)` (all-or-error, no partial TLS record), 203
  `tls_recv(fd, buf, len)` (decrypted application bytes; 0 = clean EOF:
  close_notify or FIN at a record boundary, truncation is reported). All
  three validate fd and length and return -1 with a diagnostic on misuse.

### Headless browser (`freedom`)
`bin/freedom` is the headless text browser: a curlfree-style engine (the
host `http.c` + `htmlfilter.c` ideas) with a FreeDom-style omnibox. It is
built from `progs/freedom.c` through the miniGCC-to-ld chain, like `bin/cp`,
and talks to the stack through the Linux socket syscalls plus the DNS
syscall; every timeout, retransmission and EOF (0 = FIN) semantics it leans
on is already implemented in the network driver, so the program owns only
HTTP semantics.

- Omnibox (FreeDom): an argument that is not a URL is a DuckDuckGo HTML
  (no-JS) search over https; `javascript:`/`data:` (any non-http scheme) is
  searched, never executed; the User-Agent is a fixed anti-fingerprinting
  identity. Secure by Default: a bare host (no scheme) is fetched as
  `https://`. Explicit `http://` stays http: the host dev loop serves the
  BDD fixtures over plain HTTP, so the upgrade FreeDom applies to
  `http://` input is not applied here (documented deviation).
- Engine (curlfree): a header phase reads the response head into a bounded
  buffer, then the body is read either to `Content-Length` (never waiting
  for the FIN past the announced body) or to EOF, decoding
  `Transfer-Encoding: chunked` in place. Header names match
  case-insensitively. On `https://` the same dialogue runs over the TLS
  syscalls after `tls_handshake`.
- Redirects (curlfree + FreeDom policy): a 3xx with a `Location` is chased
  up to `FREEDOM_HOPS_MAX` hops. Absolute `http://` and `https://` targets
  are followed (https through the TLS syscalls); relative targets resolve
  against the current path; any other explicit scheme in a `Location` is
  refused, fail closed.
- HTML filter (htmlfilter.c): comments are skipped, `script`/`style`
  contents are suppressed, block tags (`p`, `div`, `h1`-`h6`, `li`, `tr`)
  and `br` become newlines, entities (named and numeric, decimal and hex)
  are decoded, whitespace collapses. Filter state carries across network
  chunk boundaries, so a tag or entity split between two segments is still
  decoded.
- Remote pages are hostile data (FreeDom): every byte printed to the
  console passes a UTF-8 gate that replaces bytes outside a valid sequence
  (overlong, surrogate, out of range) with `?`.
- Headless dumps (the FreeDom agent surface MiniOS can carry, no JS):
  `freedom --dump-css <url>` prints `=== freedom css ===` then every
  stylesheet the page carries — `<style>` blocks captured in document
  order, inline `style="..."` attributes as `tag#id.class { ... }` lines,
  and `<link rel=stylesheet>` targets fetched (bounded count
  `FREEDOM_CSS_MAX`, each bounded bytes) and printed with their source.
  `freedom --dump-dom <url>` prints `=== freedom dom ===` then the
  element outline: one depth-indented `tag#id.class` line per element in
  document order (bounded buffer `FREEDOM_DOM_MAX`). Dump modes suppress
  the normal filtered text. Both flags validate argv and refuse unknown
  flags with a usage diagnostic.
- Diagnostics are `freedom: ...` lines; the fetch ends with
  `freedom: <host> (<n> bytes)`.
- Build: the ld stubs grew `tls_handshake`/`tls_send`/`tls_recv` (MiniOS
  syscalls 201-203), so the toolchain in `ld/ld.c` and the ramdisk binary
  must be rebuilt together; the Makefile already derives `bin/freedom`
  from `progs/freedom.c`.

### Ramdisk names
File names are at most `RAMDISK_FNAME_LEN - 1` characters. Names may
contain `/`, which is how directories are expressed (`bin/cp`): the ramdisk
is flat, the slash is data. `mkramdisk.py` derives each name from the path
relative to the shared parent of the packed files, so `progs/bin/cp` ships
as `bin/cp`. A name longer than the bound or a collision between two files
is a build error, never a silent truncation that would make a lookup miss.

### Filesystem commands
A working directory (`cwd`) and directory-aware builtins, over the same flat
namespace the ramdisk names describe:

- `pwd` prints the cwd (`/` for root). `cd [dir]` changes it: bare `cd` goes
  to root, `cd ..` pops one level, anything else resolves against the current
  cwd. A directory is any ramdisk name ending in `/`; it exists when the
  exact entry exists or some file name starts with it. `cd` into a
  nonexistent directory is a diagnostic, never a silent no-op.
- `mkdir <name>` creates a directory entry: an empty file named
  `<resolved name>/`. The parent directory must already exist. Creating a
  directory that already exists is a diagnostic.
- `rm <file>` deletes a ramdisk file; a missing file is a diagnostic and a
  directory name (trailing `/`) is refused, never silently removed.
- `ls [dir]` lists the entries under a directory, defaulting to the cwd,
  names relative to it. Directory entries appear with their trailing `/`.
- `cat <file> [file...]` prints files in order; with a redirection it
  concatenates them (`cat a b > c`), which is how the MCP marketplace
  reassembles sources larger than the editor buffer.
- Path resolution is one choke point: `kfopen` and the builtins resolve a
  path against the cwd (leading `/` = root, `..` pops one component) into a
  buffer of `RAMDISK_FNAME_LEN`; a name that does not fit is rejected like
  a missing file, never truncated. `kfopen` refuses directory names, so
  `edit dir/`, `cat dir/` and redirects into a directory fail cleanly.
- `ps` lists the registered programs (name, kind, entry address).
- The prompt stays `miniOS> `: the cwd is reported by `pwd`, so the MCP
  marker wait keeps working unchanged.

### Syscall tracing
`trace` prints the current state; `trace on` / `trace off` set it (off by
default). While tracing, every Linux-ABI syscall is reported on the console
as `syscall <n>(a1, a2, a3, ...) = <result>`, so a program's dialogue with
the kernel can be watched from outside without a debugger. `make gdb`
boots QEMU with the gdb stub (`-s -S`) for register-level debugging;
`gdb -ex 'target remote :1234' -ex 'add-symbol-file kernel.elf 0x100000'`
attaches to the 64-bit kernel.

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
./mutate.sh         # every mutant killed (BDD + host TLS suite)
make test-tls       # host-side crypto + full-handshake suite green
python3 -m unittest -v mcp/test_minios_mcp.py   # unit + QEMU BDD green
mcp/mutate_mcp.sh                                # every MCP mutant killed
```

The TLS engine is host-tested because the BDD gate boots a machine that can
only see plain-HTTP fixtures: `make test-tls` builds `tls.c`/`tls_crypto.c`/
`tls_x509.c` against the host libc with a compile-time test root injected,
runs fixed-vector checks (SHA-256, AES-GCM, P-256 ECDH) and then full TLS
1.2 handshakes against an OpenSSL-driven server (RSA and ECDSA chains,
correct hostname), plus the negative set (unknown CA, wrong hostname,
tampered record, expired certificate). Mutants of the TLS files are killed
by that host suite; the BDD scenarios cover the in-OS wiring fail-closed
(https against a plain-HTTP port, https redirect landing on plain HTTP) and
the dump modes over the host fixture server.

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
| `minios_poweroff` | `poweroff`, wait for `powering off` and QEMU exit, release the pid file |

Every tool carries a `timeout_ms` parameter capped by a config constant; a
wait that expires is an error, never a silent hang. A caller's budget is a
budget for the whole job: boot is bounded on its own, its marker waits are
capped by the boot timeout, so a stuck prompt can never burn an install's
full budget before failing. The host shell is never invoked
(`shell=False` everywhere); the only shell driven is the one inside
MiniOS.

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
    - src: progs/bin/cp.c
      dst: build/cp.c
  build:
    - run minigcc.o build/cp.c > build/cp.s
    - run ld.o -f elf -o bin/cp build/cp.s
  verify:
    - line: cp bin/cp.c build/cp2.c
      exit_code: 0
```

- `minios_addons` lists the addons and whether each is installed. The
  marketplace ships `cp` and `freedom`; the freedom addon is the dogfood
  of the whole system: its source travels from git into the OS and is
  rebuilt inside the OS by miniGCC and `ld`.
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
write sources with `minios_write`, compile with `run minigcc.o f.c > f.s`,
link with `run ld.o -f elf -o f.elf f.s`, run and read `exit code: N`,
power off when done. It also documents the headless browser (`freedom`,
plain command path, http only) and the addon marketplace
(`minios_addons` / `minios_install`, dogfooded by `mcp/mcp_dogfood.py`).
Extending miniGCC, `ld` or cvm/cvm2 happens on the host against the
sibling repositories (clone to a scratch dir, `make`, suites); only the
result travels into the OS.

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
