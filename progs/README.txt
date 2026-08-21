MiniOS - minimal 64-bit kernel for x86_64

Commands: help clear ls cat echo edit rm mkdir cd pwd ps load run poweroff
Redirection: <cmd> > <file>   stores the command's output in a ramdisk file

The ramdisk is organized by kind: objects/ (ET_REL toolchain), bin/ (Linux
ELFs + command path), cvm/ (CVM modules), src/ (C sources), asm/ (miniGCC
assembly), docs/. Use ls <dir> to list any of them.

Any ELF stored as bin/<cmd> runs as a plain command, Linux style:

  cp src/fib.c x.txt            cp is bin/cp, invoked without run or load
  cat x.txt                     copies src/fib.c into x.txt

bin/cp is compiled from src/cp.c through the miniGCC-to-ld chain; the
source ships alongside the binary, so the OS can rebuild the utility:

  run objects/minigcc.o src/cp.c > asm/cp.s
  run objects/ld.o -f elf -o bin/cp asm/cp.s

Writing a program without leaving the machine:

  edit src/p.c                       write the source
  run objects/minigcc.o src/p.c > asm/p.s   compile to x86-64 AT&T assembly
  run objects/ld.o -f elf -o bin/p.elf asm/p.s   assemble and link a Linux ELF
  run bin/p.elf                      execute it

Use -f cvm instead of -f elf to build a CVM module, executed by the cvm2
interpreter in objects/cvm.o:

  run objects/ld.o -f cvm -o cvm/p.cvm asm/p.s
  run cvm/p.cvm

bin/minigcc.elf is the same compiler, but self-hosted: it was compiled by
minigcc itself (generation 3) and linked by 'ld', then checked to reach
the bootstrap fixed point:

  run bin/minigcc.elf src/p.c > asm/p.s

Editor commands:
  h help          l list           p N print line N
  a append        i N insert       e N replace line N
  d N delete      w save           x save and quit
  q quit (refuses to discard changes)     q! quit discarding changes

A file too large for the buffer is loaded read-only: the editor refuses to
write it back rather than dropping the part it never read.

Program loading:
  load <file>       Load an ELF from the ramdisk.
                    .o  = ET_REL relocatable, linked against kernel libc.
                    ELF executable = real Linux ET_EXEC/ET_DYN binary.
  run <name|file>   Run a loaded program, or auto-load+run a ramdisk file.

CVM modules (.cvm files, built by the 'ld' assembler from miniGCC output):
  run cvm/fib.cvm    Runs the module on the C virtual machine (objects/cvm.o).
  run cvm/w1.cvm     Prints a string through the CVM write native.

Linux ELF binaries run at ring 3 under hardware page protection and talk to
the kernel through the x86-64 syscall instruction (write/read/open/close/
brk/mmap/exit/...). User pages are 4 KB with the no-execute bit set except
on the pages a program's executable segments occupy. A static binary built
on a Linux host runs by copying it onto the ramdisk.
See src/lxhello.c for a self-contained -static -nostdlib example.
