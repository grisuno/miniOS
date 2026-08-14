MiniOS - minimal 64-bit kernel for x86_64
Commands: help clear ls cat echo load run

Program loading:
  load <file>       Load an ELF from the ramdisk.
                    .o  = ET_REL relocatable, linked against kernel libc.
                    ELF executable = real Linux ET_EXEC/ET_DYN binary.
  run <name|file>   Run a loaded program, or auto-load+run a ramdisk file.

Linux ELF binaries run at ring 0 and talk to the kernel through the
x86-64 `syscall` instruction (write/read/open/close/brk/mmap/exit/...).
See lxhello.c for a self-contained -static -nostdlib example.
