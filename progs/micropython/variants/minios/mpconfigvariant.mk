# MicroPython on MiniOS: static glibc ELF with frozen modules and the
# minios C module.  Variant-dir sources (*.c) are compiled automatically
# by the unix Makefile's $(wildcard $(VARIANT_DIR)/*.c) rule.

FROZEN_MANIFEST = $(VARIANT_DIR)/manifest.py

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
