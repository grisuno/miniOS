MiniOS - minimal 64-bit kernel for x86_64

Commands: help clear ls cat echo edit load run poweroff
Redirection: <cmd> > <file>   stores the command's output in a ramdisk file

Any ELF stored as bin/<cmd> runs as a plain command, Linux style:

  cp fib.c x.txt                cp is bin/cp, invoked without run or load
  cat x.txt                     copies fib.c into x.txt

bin/cp is compiled from bin/cp.c through the miniGCC-to-ld chain; the
source ships alongside the binary, so the OS can rebuild the utility:

  run minigcc.o bin/cp.c > cp.s
  run ld.o -f elf -o bin/cp cp.s

Writing a program without leaving the machine:

  edit p.c                        write the source
  run minigcc.o p.c > p.s         compile to x86-64 AT&T assembly
  run ld.o -f elf -o p.elf p.s    assemble and link a Linux ELF
  run p.elf                       execute it

Use -f cvm instead of -f elf to build a CVM module, executed by the cvm2
interpreter in cvm.o:

  run ld.o -f cvm -o p.cvm p.s
  run p.cvm

minigcc.elf is the same compiler, but self-hosted: it was compiled by
minigcc itself (generation 3) and linked by 'ld', then checked to reach
the bootstrap fixed point:

  run minigcc.elf p.c > p.s

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
  run fib.cvm       Runs the module on the C virtual machine (cvm.o).
  run w1.cvm        Prints a string through the CVM write native.

Linux ELF binaries run at ring 3 under hardware page protection and talk to
the kernel through the x86-64 syscall instruction (write/read/open/close/
brk/mmap/exit/...). User pages are 4 KB with the no-execute bit set except
on the pages a program's executable segments occupy. A static binary built
on a Linux host runs by copying it onto the ramdisk.
See lxhello.c for a self-contained -static -nostdlib example.
