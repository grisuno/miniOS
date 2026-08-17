# MiniOS

A 64-bit x86 teaching kernel that carries its own toolchain. You can write a C
program inside the running system, compile it, link it and execute it without
leaving the machine.

```
miniOS> edit p.c
edit> a
int main(void) { return 7; }
edit> x
miniOS> run minigcc.o p.c > p.s
miniOS> run ld.o -f elf -o p.elf p.s
miniOS> run p.elf
exit code: 7
```

## The four repositories

MiniOS is one of four projects that together make up the system. This
repository holds the kernel, the boot path and the ramdisk; the toolchain it
carries lives next door.

| Repository | Role |
|------------|------|
| [miniOS](https://github.com/grisuno/miniOS) | this repository: kernel, two-stage boot path, ramdisk, shell, editor |
| [miniGCC](https://github.com/grisuno/miniGCC) | C compiler: C to x86-64 AT&T assembly |
| [ld](https://github.com/grisuno/ld) | assembler and linker: assembly to a Linux ELF or a CVM module |
| [cvm](https://github.com/grisuno/cvm) | the CVM / cvm2 bytecode interpreter |

The ramdisk ships prebuilt objects in `progs/`, so `make` produces a bootable
image with nothing else installed. To build the whole system from source
instead, clone the other three next to this one:

```bash
make sources          # clone the missing repositories from GitHub
make toolchain        # build minigcc, ld and cvm2 from those sources
make                  # rebuild every ramdisk object and os.img
```

`make sources` never touches a directory that already exists, so a checkout
with local work is left alone. `make sources-update` pulls the latest commit
of each before rebuilding, and `make sources-status` shows which revision
each one is sitting on.

Expected layout — the directory holding this repository can have any name:

```
src/
├── miniOS/     (this repository)
├── miniGCC/
├── ld/
└── cvm/            with cvm/cvm2 inside
```

Point the build somewhere else with `MINIGCC_DIR=`, `LD_DIR=`,
`CVM_REPO_DIR=` or `CVM_DIR=`; change where `make sources` clones from with
`MINIGCC_URL=`, `LD_URL=` or `CVM_URL=`.

Everything on the ramdisk is regenerated from source by `make`: `minigcc.o`,
`ld.o` and `cvm.o` are compiled from the sibling checkouts, and the demo
programs (`ldhello`, `w1`, `fib`) are compiled from this repository's own C
sources in `progs/` through the full miniGCC-to-ld chain. Nothing in the
image is a binary you have to take on trust.

The compiler on the ramdisk is self-hosted: `minigcc.elf` was compiled by
minigcc itself (generation 3) and linked by `ld` (no GNU as/ld anywhere after
generation 1), and `make selfhost` verifies the bootstrap fixed point on the
host. Inside the OS the self-hosted compiler drives the same edit/compile/
link/run loop as `minigcc.o`.

<img width="4082" height="7837" alt="diagram" src="https://github.com/user-attachments/assets/c3ba2575-c657-44c4-b0f5-d3c4b414da10" />


## Build and run

```bash
make            # builds os.img
make run        # boots it in QEMU with a display
make serial     # boots it headless on the serial console
make test       # behavioural suite (QEMU + serial console)
make selfhost   # compile minigcc with minigcc, link with ld, check fixed point
```

The image is attached as an IDE disk. The boot path uses INT 13h extended
(LBA) reads, which floppy emulation does not provide.

## Network and https

The kernel owns an rtl8139 NIC under QEMU user networking (slirp): Ethernet,
ARP, IPv4, ICMP echo, UDP, DNS and a client TCP (SYN handshake, stop-and-wait
with retransmissions, FIN teardown). `net` shows the counters and
`net ping 10.0.2.2` sends one ICMP echo.

On top of TCP the kernel speaks TLS 1.2 as a client
(`tls_handshake`/`tls_send`/`tls_recv`, MiniOS syscalls 201-203):
ECDHE-RSA/ECDSA with AES-128-GCM, certificate chains verified down to 8
embedded public roots, hostnames checked against SAN or CN with
single-label wildcards. Real-world browsing works from the shell:

```
miniOS> run bin/freedom https://duckduckgo.com
miniOS> run bin/freedom mini os kernel        # DuckDuckGo search over https
miniOS> run bin/freedom https://en.wikipedia.org/wiki/Mini
miniOS> run bin/freedom --dump-dom https://example.com
```

`bin/freedom` is the headless text browser: a curlfree-style HTTP engine
with a FreeDom-style omnibox (an argument that is not a URL is a DuckDuckGo
search; bare hosts are fetched as `https://`), redirect chasing, chunked
decoding, an HTML-to-text filter, and `--dump-css`/`--dump-dom` headless
dumps. The crypto and the roots are host-tested by `make test-tls` (fixed
vectors plus full TLS 1.2 handshakes against OpenSSL-driven servers,
including the negative set).

## Shell

| Command | Purpose |
|---------|---------|
| `help` | command summary |
| `ls` / `cat <file>` / `echo <text>` | ramdisk browsing |
| `edit <file>` | line editor |
| `load <file>` | load an ELF (`.o` relocatable, or a Linux executable) |
| `run <name\|file> [args]` | run a program, an ELF or a `.cvm` module |
| `<cmd> [args]` | run an ELF from `bin/<cmd>`: the Linux-style command path |
| `<cmd> > <file>` | redirect command output to a ramdisk file |
| `net` / `net ping <ip>` | network status and one ICMP echo |
| `clear` / `poweroff` | console and power |

Redirection captures what the command writes, not what the shell reports
about it, so `run minigcc.o p.c > p.s` yields assembly a linker can consume.

`bin/cp` is the first command-path utility: `cp fib.c x.txt` copies a
ramdisk file without `run` or `load`. It is compiled from this repository's
own `progs/bin/cp.c` through the miniGCC-to-ld chain, and the source ships
on the ramdisk as `bin/cp.c`, so the utility can be rebuilt inside the OS
by the OS.

## Editor

`edit <file>` opens a line editor over a ramdisk file.

| Key | Action |
|-----|--------|
| `h` | help |
| `l` | list the buffer |
| `p N` | print line N |
| `e N` | replace line N with the next line typed |
| `a` | append the next line typed |
| `i N` | insert before line N |
| `d N` | delete line N |
| `w` | save |
| `x` | save and quit |
| `q` | quit, refusing to discard unsaved changes |
| `q!` | quit, discarding changes |

A file too large for the buffer is loaded read-only: the editor refuses to
write it back rather than silently dropping the part it never read.

## Program formats

MiniOS runs three kinds of program:

- **Relocatable objects** (`.o`) — linked at load time against the kernel's
  libc symbol table. `minigcc.o`, `ld.o` and `cvm.o` ship this way.
- **Linux executables** (`ET_EXEC` / `ET_DYN`) — static binaries run
  unmodified through the x86-64 `syscall` ABI. A binary built on the host can
  be used simply by copying it onto the ramdisk.
- **CVM modules** (`.cvm`) — stack bytecode produced by `ld -f cvm` and
  executed by the cvm2 interpreter in `cvm.o`.

## Layout

| File | Role |
|------|------|
| `bootdefs.h` | every constant shared by the boot path |
| `stage1.S` | 512-byte boot sector: loads stage 2 over LBA |
| `stage2.S` | loads the kernel above 1 MB, enters long mode |
| `kernel.c` / `kernel.h` | kernel: console, heap, ramdisk, loaders, shell, editor |
| `net.c` / `net.h` | rtl8139 driver, ARP/IP/ICMP/UDP/DNS/TCP |
| `tls.c` / `tls_crypto.c` / `tls_x509.c` | kernel TLS 1.2 client, crypto, X.509 |
| `tls_roots_src/` + `mkroots.sh` | the 8 embedded CA roots and their generator |
| `tls_test.py` / `tls_test.c` | host TLS suite: vectors + full handshakes |
| `cvm_host.c` | host glue for the CVM interpreter |
| `progs/*.c` | ramdisk contents: demo programs and the C sources they are built from |
| `mkramdisk.py` | packs `progs/` into the ramdisk image |
| `test_bdd.sh` / `test_http_server.py` | behavioural suite and its HTTP fixture |
| `mcp/minios_mcp.py` | MCP bridge: boots the OS and exposes its console as tools |
| `mcp/test_minios_mcp.py` | unit + QEMU BDD suite for the bridge |
| `mcp/mutate_mcp.sh` | mutation testing for the bridge |
| `skills/minios/SKILL.md` | agent skill: the edit/compile/link/run workflow over the bridge |
| `mutate.sh` | mutation testing |

## Agent bridge (MCP + skill)

`mcp/minios_mcp.py` exposes a running MiniOS as MCP tools: `minios_boot`,
`minios_status`, `minios_send`, `minios_expect`, `minios_snapshot`,
`minios_write`, `minios_cat`, `minios_poweroff`. The server owns the QEMU
child and a pty-backed serial console; the companion skill
(`skills/minios/SKILL.md`) teaches the edit/compile/link/run workflow, so an
agent can write a C program inside the OS, build it with `minigcc.o` and
`ld.o`, run it and read `exit code: N`, all without leaving the machine.

```bash
python3 -m unittest -v mcp/test_minios_mcp.py   # unit + QEMU BDD (skips without QEMU)
mcp/mutate_mcp.sh                                # every bridge mutant must die
```

The bridge is driven over stdio JSON-RPC, uses only the Python standard
library, validates every input before a byte reaches the console (path
whitelist, printable ASCII, editor line and buffer limits), and never leaks
a QEMU process: the pid file under the system temp dir reaps stale
instances and every exit path terminates the child. See `CLAUDE.md` for the
full contract.

## Make targets

| Target | Purpose |
|--------|---------|
| `all` (default) | build `os.img` |
| `sources` | clone the missing toolchain repositories from GitHub |
| `sources-update` | pull the latest commit of each one |
| `sources-status` | show the revision each checkout is on |
| `toolchain` | build `minigcc`, `ld` and `cvm2` from those sources |
| `selfhost` | compile minigcc with minigcc, link with `ld`, verify the bootstrap fixed point |
| `test-tls` | host TLS suite: crypto vectors + full handshakes |
| `run` / `serial` / `debug` | boot the image in QEMU |
| `test` | behavioural suite |
| `clean` | remove every build product |

See `CLAUDE.md` for the full engineering contract.

[https://medium.com/@lazyown.redteam/because-i-can-the-most-dangerous-words-in-a-world-of-subscription-based-obedience-05f38f99cd36](https://medium.com/@lazyown.redteam/because-i-can-the-most-dangerous-words-in-a-world-of-subscription-based-obedience-05f38f99cd36)
