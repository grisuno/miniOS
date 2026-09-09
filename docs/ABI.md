# MiniOS ABI — Programmer's Manual (v4)

Target: ring-3 `ET_EXEC`/`ET_DYN` programs (static, `-no-pie`).
Single source of truth: `progs/minios_abi.h`.

## Memory layout

| Symbol | Value | Notes |
|---|---|---|
| `MINIOS_USER_LOAD_BASE` | `0x400000` | ET_EXEC load base |
| `MINIOS_USER_LOAD_END` | `0xC000000` | window end = stack top |
| `MINIOS_USER_STACK_SIZE` | 1 MB | `STACK_BASE = END - 1MB` |
| `MINIOS_USER_BRK_END` | `STACK_BASE` | brk/mmap ceiling |
| `MINIOS_DOOM_BACKBUF_ADDR` | `0xB000000` | 320x200 game buffer |
| `MINIOS_FB_ADDR` | `0xB200000` | linear framebuffer |
| `MINIOS_NK_BACKBUF_ADDR` | `0xB600000` | 800x360 NK buffer |
| `MINIOS_HEAP_BASE/SIZE` | `0xC000000`/192 MB | kernel heap, supervisor only |

Rule: never hardcode an address; include `minios_abi.h`.

## Syscalls

Linux 0-199 passthrough; MiniOS 200-299 custom. New in v4:

| # | Name | Args | Notes |
|---|---|---|---|
| 211 | `DOOM_FRAME` (=`FRAMEBUFFER_COMMIT`) | — | compat alias |
| 220 | `NK_FRAME` (=`WINDOW_PRESENT`) | `int *origin?` | compat alias |
| 223 | `GFX_SET_TITLE` (=`WINDOW_TITLE`) | `const char *t` | max 31+NUL, `EFAULT` outside window |
| 237 | `GFX_PRESENT` | `id, int *origin?` | generic: 0=game, 1=NK |
| 238 | `SECCOMP` | `op, n` | 1=deny-one, 2=allow-one, 3=deny-all(keep TIME); window 200-231 |
| 239 | `NICE` | `value, set?` | `-20..19`, default 0; fair-share weight |

Example (generic present):

```c
/* present the game buffer */
syscall(237, 0, 0, 0, 0, 0, 0);
/* present NK and get origin */
int o[2]; syscall(237, 1, (long)o, 0, 0, 0, 0);
/* drop framebuffer rights for this process */
syscall(238, 1, 211, 0, 0, 0, 0);
/* lower priority */
syscall(239, 10, 1, 0, 0, 0, 0);
```

## Versioning

`MINIOS_ABI_VERSION` bumps on incompatible change (now 4).
`MINIOS_ABI_CHECKSUM` XOR-folds layout + new numbers; loader rejects mismatch
with `-EABI_MISMATCH`.

## Security notes

- Every pointer validated against the user window; strings NUL-bounded.
- `ET_REL` is ring-0 and trusted-path only (`objects/`); anything else must
  link with `ld -f elf` and run at ring 3.
- TLS lives in the kernel for now (fail-closed, no downgrade); build with
  `make ENABLE_TLS=0` to remove it (`-ENOSYS`).
- MiniFS mounts only after a superblock self-check; full repair is host-side
  (`minifs_fsck.py`); journal recovery runs at mount.
