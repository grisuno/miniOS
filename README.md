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
| `mkramdisk.py` | packs `progs/` into the ramdisk image |
| `test_bdd.sh` | behavioural suite |
| `mutate.sh` | mutation testing |

See `CLAUDE.md` for the full engineering contract.
