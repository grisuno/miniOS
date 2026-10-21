# MiniOS ABI — Programmer's Manual (v13)

Target: ring-3 `ET_EXEC`/`ET_DYN` programs (static, `-no-pie`).
Single source of truth: `progs/minios_abi.h`.

## Memory layout

| Symbol | Value | Notes |
|---|---|---|
| `MINIOS_USER_LOAD_BASE` | `0x400000` | ET_EXEC load base |
| `MINIOS_USER_LOAD_END` | `0xC000000` | window end = stack top |
| `MINIOS_USER_STACK_SIZE` | 1 MB | `STACK_BASE = END - 1MB` |
| `MINIOS_USER_BRK_END` | `STACK_BASE` | brk/mmap ceiling |
| `MINIOS_LDSO_BASE`/`SIZE` | `0x9000000`/32 MB | ld.so shared-library region, ends at `0xB000000` |
| `MINIOS_DOOM_BACKBUF_ADDR` | `0xB000000` | 320x200 game buffer |
| `MINIOS_FB_ADDR` | `0xB200000` | linear framebuffer |
| `MINIOS_NK_BACKBUF_ADDR` | `0xB600000` | 800x360 NK buffer |
| `MINIOS_NK_RGB_ADDR` | `0xB700000` | 800x360x3 NK RGB buffer (ABI v7) |
| `MINIOS_HEAP_BASE`/`SIZE` | `0xC000000`/448 MB | kernel heap, supervisor only |

Rule: never hardcode an address; include `minios_abi.h`.

## Syscalls

Linux 0-199 passthrough; MiniOS 200-299 custom, plus the 300 window
(300 `CLONE`, 301 fossil alias, 302 `PRLIMIT64`): 300+ is not reserved
wholesale.

Graphics, process control and limits (211-240; 237-239 landed in v4,
240 in v5, 211/220/223 predate both):

| # | Name | Args | Notes |
|---|---|---|---|
| 211 | `DOOM_FRAME` (=`FRAMEBUFFER_COMMIT`) | — | compat alias |
| 220 | `NK_FRAME` (=`WINDOW_PRESENT`) | `int *origin?` | compat alias |
| 223 | `GFX_SET_TITLE` (=`WINDOW_TITLE`) | `const char *t` | max 31+NUL, `EFAULT` outside window |
| 237 | `GFX_PRESENT` | `id, int *origin?` | generic: 0=game, 1=NK, 2=NK RGB |
| 238 | `SECCOMP` | `op, n` | 1=deny-one, 2=allow-one, 3=deny-all over 200-231 |
| 239 | `NICE` | `value, set?` | `-20..19`, default 0; fair-share weight |
| 240 | `RLIMIT` | `op, res, val` | cgroups-lite: 1=AS bytes, 2=CPU ticks, 3=NOFILE; op 1=SET 2=GET; 0=unlimited; CPU overrun kills with 137 |

New in v9 (pipes, server TCP, fork, clipboard):

| # | Name | Args | Notes |
|---|---|---|---|
| 22/32/33 | `pipe`/`dup`/`dup2` | Linux layout | KFILE pipes: empty+open reads `-EAGAIN`, drained+closed reads EOF; `dup2` targets 0..31 incl. stdio |
| 43/49/50 | `accept`/`bind`/`listen` | Linux `sockaddr_in` | server TCP beside the client machine; single backlog slot; `accept` waits up to `NET_ACCEPT_TMO_MS` |
| 57 | `fork` | — | copy-on-write clone of isolated processes; child resumes at the trapped return with 0; legacy pid 0 and `CLONE_VM` threads get `-ENOSYS` |
| 249/250 | `CLIP_SET`/`CLIP_GET` | `data, len` / `buf, cap` | shared text clipboard, 4096 bytes; set refuses past cap, get refuses empty/undersize, never truncates |

The rest of the custom window: 200 `DNS`, 201 `time` (Linux time(2)),
202 `futex` (Linux futex(2)), 203 retired (`-ENOSYS`), 205 `kbd`, 206
`palette`, 207 `kbd_raw`, 208 `vga_mode`, 209/210 PC speaker, 212 `rtc`,
213 `fb_info`, 214 PC speaker volume, 215 `spawn`, 216 `lz4_compress`,
219 `mouse`, 221/222/224 SB16 open/submit/pump, 225 `thread_spawn`,
226/227 `futex_wait`/`futex_wake`, 232/233 SB16 stream submit/volume,
235 `submit_batch`, 236 `getc_raw`, 241 `dir_list`, 242 `gfx_zoom`
(0 native, 1 2x, 2 fullscreen, 3 windowed), 246/247/248 PCM2
open/write/close, 251 `minfo`, 252/253 SB16 stream open/close, 254
`time` (milliseconds since boot), 255 `lz4_decompress`.

v12 moved three numbers out of the Linux table: `TIME` from 204
(`sched_getaffinity`), `SB16_STREAM_OPEN`/`SB16_STREAM_CLOSE` from
229/230 (`clock_getres`/`clock_nanosleep`). 204, 229 and 230 answer the
Linux calls again.

v13 moved `LZ4_DECOMPRESS` from 217 (Linux `getdents64`, now served) to
255. It had been parked on 248, which `PCM2_CLOSE` also claimed: the
dispatch table is indexed by number, so only the last entry survived and
`lz4_decompress` was unreachable. 255 is free in the Linux table and
outside the pcm2 range (246-248). The sibling `ld` links every miniGCC
program with a built-in libc whose stubs hardcode these numbers, so its
`lz4_decompress` stub moved with it; `tools/check_abi_numbers.py` now
fails closed on a duplicated MiniOS number (rule D) and on a stale
toolchain stub (rule E).

243-245 stay reserved for Wayland-mini (`WL_ATTACH`/`WL_COMMIT`/`WL_INPUT`)
and out of the checksum until the kernel answers them.

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

`MINIOS_ABI_VERSION` bumps on incompatible change (now 13).
`MINIOS_ABI_CHECKSUM` XOR-folds layout + syscall numbers. The checksum
is checked at boot, not at load: the ramdisk carries `etc/abi` (the
version and checksum the image was built from) and `kernel/abi.c` halts
the boot on a mismatch. A load-time gate is still open:
`MINIOS_EABI_MISMATCH` is defined but unused, because Linux-ABI
binaries carry no MiniOS version note and rejecting them would break
Linux compatibility.

## Security notes

- Every pointer validated against the user window; strings NUL-bounded.
- `ET_REL` is ring-0 and trusted-path only (`ETREL_TRUSTED_DIR` in
  kernel.h, `objects/`); anything else must
  link with `ld -f elf` and run at ring 3. Paths are normalised by
  `fs_resolve` before the gate; the image cap is `ETREL_IMAGE_MAX`
  (16 MB, `kernel/loader.c`).
- TLS is userspace-only (`tlsget`/`freedom`, ring-3 engine); 201 serves
  Linux `time(2)` and 203 answers `-ENOSYS`, and 202 serves Linux
  `futex(2)` (`__NR_futex` collides with the retired TLS_SEND number —
  answering `-ENOSYS` there aborts any glibc program that locks, e.g.
  `getaddrinfo`).
- MiniFS mounts only after a superblock self-check; full repair is host-side
  (`minifs_fsck.py`); journal recovery runs at mount.
