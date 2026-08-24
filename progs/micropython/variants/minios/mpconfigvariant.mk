# MicroPython on MiniOS: static glibc ELF, no frozen modules.
# Variant-dir sources (*.c) are compiled automatically by the unix Makefile;
# we don't need any extra C files here.

FROZEN_MANIFEST =

MICROPY_PY_BTREE = 0
MICROPY_PY_FFI = 0
MICROPY_PY_SOCKET = 0
MICROPY_PY_THREAD = 0
MICROPY_PY_TERMIOS = 0
MICROPY_PY_SSL = 0
MICROPY_USE_READLINE = 0

MICROPY_VFS_FAT = 0
MICROPY_VFS_LFS1 = 0
MICROPY_VFS_LFS2 = 0
