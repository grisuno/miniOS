# MiniOS - minimal 64-bit kernel for x86_64

Commands: help clear ls cat echo edit rm mkdir cd pwd ps load run poweroff

The ramdisk directory structure (use `ls <dir>` to list each kind):

- `objects/` — ET_REL toolchain (`minigcc.o`, `ld.o`, `cvm.o`)
- `bin/` — Linux ELFs + command-path utilities (`cp`, `freedom`)
- `cvm/` — CVM modules (`fib.cvm`, `w1.cvm`, `minigcc.cvm`)
- `src/` — C sources for ramdisk programs
- `asm/` — miniGCC assembly (`*.s`)
- `docs/` — HTML and documentation fixtures

Redirection: `<cmd> > <file>` stores output in a ramdisk file.

Any ELF stored as `bin/<cmd>` runs as a plain Linux command without `run` or
`load`:

  cp src/fib.c x.txt            cp is bin/cp, invoked directly
  cat x.txt                     copies src/fib.c into x.txt

`bin/cp` is compiled from `src/cp.c` through the miniGCC-to-ld chain; the
source ships alongside the binary.

Writing a program inside the OS:

  edit src/p.c                       write the source
  run objects/minigcc.o src/p.c > asm/p.s   compile to x86-64 AT&T assembly
  run objects/ld.o -f elf -o bin/p.elf asm/p.s   assemble and link a Linux ELF
  run bin/p.elf                      execute it

Use `-f cvm` to build a CVM module:

  run objects/ld.o -f cvm -o cvm/p.cvm asm/p.s
  run cvm/p.cvm

`bin/minigcc.elf` is the self-hosted compiler (minigcc gen3, linked by ld).

Editor:

  h help          l list           p N print line N
  a append        i N insert       e N replace line N
  d N delete      w save           x save and quit
  q quit (refuses to discard changes)     q! quit discarding changes

CVM modules (.cvm files):

  run cvm/fib.cvm    Runs the module on the C virtual machine.
  run cvm/w1.cvm     Prints a string through the CVM write native.