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

## Build and run

```bash
make            # builds os.img
make run        # boots it in QEMU with a display
make serial     # boots it headless on the serial console
make test       # behavioural suite (QEMU + serial console)
```

The image is attached as an IDE disk. The boot path uses INT 13h extended
(LBA) reads, which floppy emulation does not provide.

## Shell

| Command | Purpose |
|---------|---------|
| `help` | command summary |
| `ls` / `cat <file>` / `echo <text>` | ramdisk browsing |
| `edit <file>` | line editor |
| `load <file>` | load an ELF (`.o` relocatable, or a Linux executable) |
| `run <name\|file> [args]` | run a program, an ELF or a `.cvm` module |
| `<cmd> > <file>` | redirect command output to a ramdisk file |
| `clear` / `poweroff` | console and power |

Redirection captures what the command writes, not what the shell reports
about it, so `run minigcc.o p.c > p.s` yields assembly a linker can consume.

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
| `cvm_host.c` | host glue for the CVM interpreter |
| `progs/*.c` | ramdisk contents: demo programs and the C sources they are built from |
| `mkramdisk.py` | packs `progs/` into the ramdisk image |
| `test_bdd.sh` | behavioural suite |
| `mutate.sh` | mutation testing |

## Make targets

| Target | Purpose |
|--------|---------|
| `all` (default) | build `os.img` |
| `sources` | clone the missing toolchain repositories from GitHub |
| `sources-update` | pull the latest commit of each one |
| `sources-status` | show the revision each checkout is on |
| `toolchain` | build `minigcc`, `ld` and `cvm2` from those sources |
| `run` / `serial` / `debug` | boot the image in QEMU |
| `test` | behavioural suite |
| `clean` | remove every build product |

See `CLAUDE.md` for the full engineering contract.
