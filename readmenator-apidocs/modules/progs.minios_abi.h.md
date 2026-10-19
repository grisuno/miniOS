# `progs/minios_abi.h`

> Source: [progs/minios_abi.h:1](../../progs/minios_abi.h#L1) | language `h` | coverage 20.8% | [API index](../index.md)

minios_abi.h -- Single source of truth for the MiniOS user-kernel ABI.

## Contents

- **Functions:** [`DOOM_BACKBUF_ADDR`](#doom_backbuf_addr), [`clock_nanosleep`](#clock_nanosleep)
- **Macros:** [`MINIOS_ABI_VERSION`](#minios_abi_version), [`MINIOS_ABI_CHECKSUM`](#minios_abi_checksum), [`MINIOS_USER_LOAD_BASE`](#minios_user_load_base), [`MINIOS_USER_LOAD_END`](#minios_user_load_end), [`MINIOS_USER_STACK_SIZE`](#minios_user_stack_size), [`MINIOS_USER_STACK_TOP`](#minios_user_stack_top), [`MINIOS_USER_STACK_BASE`](#minios_user_stack_base), [`MINIOS_USER_BRK_END`](#minios_user_brk_end), [`MINIOS_DOOM_BACKBUF_ADDR`](#minios_doom_backbuf_addr), [`MINIOS_DOOM_W`](#minios_doom_w), [`MINIOS_FB_ADDR`](#minios_fb_addr), [`MINIOS_NK_BACKBUF_ADDR`](#minios_nk_backbuf_addr), [`MINIOS_NK_W`](#minios_nk_w), [`MINIOS_LDSO_BASE`](#minios_ldso_base), [`MINIOS_LDSO_SIZE`](#minios_ldso_size), [`MINIOS_LDSO_END`](#minios_ldso_end), [`MINIOS_NK_RGB_ADDR`](#minios_nk_rgb_addr), [`MINIOS_NK_RGB_BYTES`](#minios_nk_rgb_bytes), [`MINIOS_HEAP_BASE`](#minios_heap_base), [`MINIOS_HEAP_SIZE`](#minios_heap_size), [`MINIOS_PCI_MMIO_SIZE`](#minios_pci_mmio_size), [`MINIOS_DEV_MMIO_VBASE`](#minios_dev_mmio_vbase), [`MINIOS_FB_WIDTH_MAX`](#minios_fb_width_max), [`MINIOS_FB_HEIGHT_MAX`](#minios_fb_height_max), [`MINIOS_SYS_READ`](#minios_sys_read), [`MINIOS_SYS_WRITE`](#minios_sys_write), [`MINIOS_SYS_OPEN`](#minios_sys_open), [`MINIOS_SYS_CLOSE`](#minios_sys_close), [`MINIOS_SYS_FSTAT`](#minios_sys_fstat), [`MINIOS_SYS_POLL`](#minios_sys_poll), [`MINIOS_SYS_LSEEK`](#minios_sys_lseek), [`MINIOS_SYS_MMAP`](#minios_sys_mmap), [`MINIOS_SYS_MPROTECT`](#minios_sys_mprotect), [`MINIOS_SYS_MUNMAP`](#minios_sys_munmap), [`MINIOS_SYS_BRK`](#minios_sys_brk), [`MINIOS_SYS_RT_SIGACTION`](#minios_sys_rt_sigaction), [`MINIOS_SYS_RT_SIGPROCMASK`](#minios_sys_rt_sigprocmask), [`MINIOS_SYS_IOCTL`](#minios_sys_ioctl), [`MINIOS_SYS_WRITEV`](#minios_sys_writev), [`MINIOS_SYS_ACCESS`](#minios_sys_access), [`MINIOS_SYS_SCHED_YIELD`](#minios_sys_sched_yield), [`MINIOS_SYS_GETPID`](#minios_sys_getpid), [`MINIOS_SYS_SOCKET`](#minios_sys_socket), [`MINIOS_SYS_CONNECT`](#minios_sys_connect), [`MINIOS_SYS_SENDTO`](#minios_sys_sendto), [`MINIOS_SYS_RECVFROM`](#minios_sys_recvfrom), [`MINIOS_SYS_SHUTDOWN`](#minios_sys_shutdown), [`MINIOS_SYS_FORK`](#minios_sys_fork), [`MINIOS_SYS_VFORK`](#minios_sys_vfork), [`MINIOS_SYS_EXECVE`](#minios_sys_execve), [`MINIOS_SYS_EXIT`](#minios_sys_exit), [`MINIOS_SYS_WAIT4`](#minios_sys_wait4), [`MINIOS_SYS_KILL`](#minios_sys_kill), [`MINIOS_SYS_UNAME`](#minios_sys_uname), [`MINIOS_SYS_UNLINK`](#minios_sys_unlink), [`MINIOS_SYS_RENAME`](#minios_sys_rename), [`MINIOS_SYS_READLINK`](#minios_sys_readlink), [`MINIOS_SYS_GETTID`](#minios_sys_gettid), [`MINIOS_SYS_FLOCK`](#minios_sys_flock), [`MINIOS_SYS_FSYNC`](#minios_sys_fsync), [`MINIOS_SYS_FDATASYNC`](#minios_sys_fdatasync), [`MINIOS_SYS_GETCWD`](#minios_sys_getcwd), [`MINIOS_SYS_GETTIMEOFDAY`](#minios_sys_gettimeofday), [`MINIOS_SYS_ARCH_PRCTL`](#minios_sys_arch_prctl), [`MINIOS_SYS_OPENAT`](#minios_sys_openat), [`MINIOS_SYS_NEWFSTATAT`](#minios_sys_newfstatat), [`MINIOS_SYS_STATX`](#minios_sys_statx), [`MINIOS_SYS_SET_ROBUST_LIST`](#minios_sys_set_robust_list), [`MINIOS_SYS_PRLIMIT64`](#minios_sys_prlimit64), [`MINIOS_SYS_GETRANDOM`](#minios_sys_getrandom), [`MINIOS_SYS_RSEQ`](#minios_sys_rseq), [`MINIOS_SYS_EXIT_GROUP`](#minios_sys_exit_group), [`MINIOS_SYS_SET_TID_ADDRESS`](#minios_sys_set_tid_address), [`MINIOS_SYS_CLOCK_GETTIME`](#minios_sys_clock_gettime), [`MINIOS_SYS_TGKILL`](#minios_sys_tgkill), [`MINIOS_SYS_DNS`](#minios_sys_dns), [`MINIOS_SYS_TLS_HANDSHAKE`](#minios_sys_tls_handshake), [`MINIOS_SYS_TLS_SEND`](#minios_sys_tls_send), [`MINIOS_SYS_TLS_RECV`](#minios_sys_tls_recv), [`MINIOS_SYS_TIME`](#minios_sys_time), [`MINIOS_SYS_KBD`](#minios_sys_kbd), [`MINIOS_SYS_PALETTE`](#minios_sys_palette), [`MINIOS_SYS_KBD_RAW`](#minios_sys_kbd_raw), [`MINIOS_SYS_VGA_MODE`](#minios_sys_vga_mode), [`MINIOS_SYS_PCSPK_INIT`](#minios_sys_pcspk_init), [`MINIOS_SYS_PCSPK_TONE`](#minios_sys_pcspk_tone), [`MINIOS_SYS_DOOM_FRAME`](#minios_sys_doom_frame), [`MINIOS_SYS_RTC`](#minios_sys_rtc), [`MINIOS_SYS_FB_INFO`](#minios_sys_fb_info), [`MINIOS_SYS_PCSPK_VOL`](#minios_sys_pcspk_vol), [`MINIOS_SYS_SPAWN`](#minios_sys_spawn), [`MINIOS_SYS_LZ4_COMPRESS`](#minios_sys_lz4_compress), [`MINIOS_SYS_LZ4_DECOMPRESS`](#minios_sys_lz4_decompress), [`MINIOS_SYS_MOUSE`](#minios_sys_mouse), [`MINIOS_SYS_NK_FRAME`](#minios_sys_nk_frame), [`MINIOS_SYS_SB16_OPEN`](#minios_sys_sb16_open), [`MINIOS_SYS_SB16_SUBMIT`](#minios_sys_sb16_submit), [`MINIOS_SYS_GFX_SET_TITLE`](#minios_sys_gfx_set_title), [`MINIOS_SYS_SB16_PUMP`](#minios_sys_sb16_pump), [`MINIOS_SYS_SB16_STREAM_OPEN`](#minios_sys_sb16_stream_open), [`MINIOS_SYS_SB16_STREAM_CLOSE`](#minios_sys_sb16_stream_close), [`MINIOS_SYS_SB16_STREAM_SUBMIT`](#minios_sys_sb16_stream_submit), [`MINIOS_SYS_SB16_STREAM_VOLUME`](#minios_sys_sb16_stream_volume), [`MINIOS_SYS_THREAD_SPAWN`](#minios_sys_thread_spawn), [`MINIOS_SYS_FUTEX_WAIT`](#minios_sys_futex_wait), [`MINIOS_SYS_FUTEX_WAKE`](#minios_sys_futex_wake), [`MINIOS_SYS_SUBMIT_BATCH`](#minios_sys_submit_batch), [`MINIOS_SYS_GETC_RAW`](#minios_sys_getc_raw), [`MINIOS_SYS_GFX_PRESENT`](#minios_sys_gfx_present), [`MINIOS_SYS_SECCOMP`](#minios_sys_seccomp), [`MINIOS_SYS_NICE`](#minios_sys_nice), [`MINIOS_SYS_RLIMIT`](#minios_sys_rlimit), [`MINIOS_SYS_DIR_LIST`](#minios_sys_dir_list), [`MINIOS_SYS_GFX_ZOOM`](#minios_sys_gfx_zoom), [`MINIOS_SYS_WL_ATTACH`](#minios_sys_wl_attach), [`MINIOS_SYS_WL_COMMIT`](#minios_sys_wl_commit), [`MINIOS_SYS_WL_INPUT`](#minios_sys_wl_input), [`MINIOS_SYS_PCM2_OPEN`](#minios_sys_pcm2_open), [`MINIOS_SYS_PCM2_WRITE`](#minios_sys_pcm2_write), [`MINIOS_SYS_PCM2_CLOSE`](#minios_sys_pcm2_close), [`MINIOS_SYS_CLIP_SET`](#minios_sys_clip_set), [`MINIOS_SYS_CLIP_GET`](#minios_sys_clip_get), [`MINIOS_SYS_MINFO`](#minios_sys_minfo), [`MINIOS_PCM2_NONBLOCK`](#minios_pcm2_nonblock), [`MINIOS_PCM2_RATE`](#minios_pcm2_rate), [`MINIOS_PCM2_FRAG`](#minios_pcm2_frag), [`MINIOS_SYS_CLONE`](#minios_sys_clone), [`MINIOS_GFX_BUF_GAME`](#minios_gfx_buf_game), [`MINIOS_GFX_BUF_NK`](#minios_gfx_buf_nk), [`MINIOS_GFX_BUF_NK_RGB`](#minios_gfx_buf_nk_rgb), [`MINIOS_SYS_FRAMEBUFFER_COMMIT`](#minios_sys_framebuffer_commit), [`MINIOS_SYS_WINDOW_PRESENT`](#minios_sys_window_present), [`MINIOS_SYS_WINDOW_TITLE`](#minios_sys_window_title), [`MINIOS_GFX_ZOOM_NATIVE`](#minios_gfx_zoom_native), [`MINIOS_GFX_ZOOM_2X`](#minios_gfx_zoom_2x), [`MINIOS_GFX_ZOOM_FULLSCREEN`](#minios_gfx_zoom_fullscreen), [`MINIOS_GFX_ZOOM_WINDOWED`](#minios_gfx_zoom_windowed), [`SYS_TIME_MS`](#sys_time_ms), [`SYS_PALETTE`](#sys_palette), [`SYS_PCSPK_INIT`](#sys_pcspk_init), [`SYS_PCSPK_TONE`](#sys_pcspk_tone), [`SYS_RTC`](#sys_rtc), [`SYS_FB_INFO`](#sys_fb_info), [`SYS_PCSPK_VOL`](#sys_pcspk_vol), [`SYS_SPAWN`](#sys_spawn), [`SYS_TIME`](#sys_time), [`SYS_WRITE`](#sys_write), [`MINIOS_EABI_MISMATCH`](#minios_eabi_mismatch), [`MINIOS_NOTE_NAME`](#minios_note_name), [`MINIOS_NOTE_PROCESS`](#minios_note_process), [`MINIOS_NOTE_SIGN`](#minios_note_sign)

## Functions

<a id="doom_backbuf_addr"></a>

### `DOOM_BACKBUF_ADDR`

`function` | [progs/minios_abi.h:128](../../progs/minios_abi.h#L128)

```c
* * All three sit in the reserved tail above DOOM_BACKBUF_ADDR (the brk cap), * so a growing heap or mmap region can never reach them. NK_BACKBUF sits * HIGHER than the framebuffer's maximum span: at
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `cap` | `the brk` |  |  |

**Returns:** `* * All three sit in the reserved tail above`

---

<a id="clock_nanosleep"></a>

### `clock_nanosleep`

`function` | [progs/minios_abi.h:338](../../progs/minios_abi.h#L338)

```c
* clock_nanosleep (static glibc's sleep, usleep and nanosleep). */ #define MINIOS_SYS_SB16_STREAM_OPEN 252 #define MINIOS_SYS_SB16_STREAM_CLOSE 253 #define MINIOS_SYS_SB16_STREAM_SUBMIT 232 #define MI
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `nanosleep` | `static glibc's sleep, usleep and` |  |  |

**Returns:** `*`

---

## Macros

<a id="minios_abi_version"></a>

### `MINIOS_ABI_VERSION`

`macro` | [progs/minios_abi.h:41](../../progs/minios_abi.h#L41)

```c
#define MINIOS_ABI_VERSION
```

========================================================================= ABI Version ========================================================================= Bump MINIOS_ABI_VERSION on every backwards-incompatible change: - layout constant address or size change - syscall number addition, removal, or reordering - graphics back-buffer geometry change - kernel heap relocation

MINIOS_ABI_CHECKSUM is computed at compile time from all layout constants.
It is verified at build time (kernel _Static_asserts), not at load time:
see the ABI Version note above for why the loader cannot gate on it.
=========================================================================

---

<a id="minios_abi_checksum"></a>

### `MINIOS_ABI_CHECKSUM`

`macro` | [progs/minios_abi.h:45](../../progs/minios_abi.h#L45)

```c
#define MINIOS_ABI_CHECKSUM
```

Compile-time checksum: XOR-fold of all layout constants.

Recomputed by the kernel at load time for verification.

---

<a id="minios_user_load_base"></a>

### `MINIOS_USER_LOAD_BASE`

`macro` | [progs/minios_abi.h:113](../../progs/minios_abi.h#L113)

```c
#define MINIOS_USER_LOAD_BASE
```

========================================================================= User window geometry ========================================================================= The user window is the virtual address range mapped for ring-3 programs: [USER_LOAD_BASE, USER_LOAD_END)

Programs load at USER_LOAD_BASE (ET_EXEC base 0, ET_DYN base =
USER_LOAD_BASE).  The brk grows upward from the end of loaded segments.
The mmap region grows downward from USER_BRK_END toward the brk.
The stack grows downward from USER_STACK_TOP.

Layout (low to high):
  USER_LOAD_BASE          program text/data start
  ...brk grows up...      heap (brk syscall)
  ...mmap grows down...   anonymous mmap allocations
  USER_BRK_END            hard ceiling for both brk and mmap
  DOOM_BACKBUF_ADDR       DOOM/Q2G 320x200 back-buffer (kernel-mapped)
  FB_ADDR                 linear framebuffer (kernel-mapped, VBE)
  NK_BACKBUF_ADDR         Nuklear 800x360 indexed back-buffer (kernel-mapped)
  NK_RGB_ADDR             Nuklear 800x360 RGB back-buffer (kernel-mapped,
                          3 bytes per pixel, same geometry as NK_BACKBUF)
  USER_STACK_BASE         stack region base (1 MB below top)
  USER_STACK_TOP          stack top (= USER_LOAD_END)
  HEAP_BASE               kernel heap (supervisor only, not in window)
=========================================================================

---

<a id="minios_user_load_end"></a>

### `MINIOS_USER_LOAD_END`

`macro` | [progs/minios_abi.h:114](../../progs/minios_abi.h#L114)

```c
#define MINIOS_USER_LOAD_END
```

---

<a id="minios_user_stack_size"></a>

### `MINIOS_USER_STACK_SIZE`

`macro` | [progs/minios_abi.h:115](../../progs/minios_abi.h#L115)

```c
#define MINIOS_USER_STACK_SIZE
```

---

<a id="minios_user_stack_top"></a>

### `MINIOS_USER_STACK_TOP`

`macro` | [progs/minios_abi.h:116](../../progs/minios_abi.h#L116)

```c
#define MINIOS_USER_STACK_TOP
```

---

<a id="minios_user_stack_base"></a>

### `MINIOS_USER_STACK_BASE`

`macro` | [progs/minios_abi.h:117](../../progs/minios_abi.h#L117)

```c
#define MINIOS_USER_STACK_BASE
```

---

<a id="minios_user_brk_end"></a>

### `MINIOS_USER_BRK_END`

`macro` | [progs/minios_abi.h:118](../../progs/minios_abi.h#L118)

```c
#define MINIOS_USER_BRK_END
```

---

<a id="minios_doom_backbuf_addr"></a>

### `MINIOS_DOOM_BACKBUF_ADDR`

`macro` | [progs/minios_abi.h:135](../../progs/minios_abi.h#L135)

```c
#define MINIOS_DOOM_BACKBUF_ADDR
```

========================================================================= Graphics back-buffers (kernel-mapped into user window) ========================================================================= The kernel allocates these from the kernel heap and maps them into the user window via the 4 KB page tables at boot (mm_setup_protections).

A ring-3 program writes to these addresses and calls the corresponding SYS_*_FRAME syscall; the kernel composites the buffer onto the desktop.

All three sit in the reserved tail above DOOM_BACKBUF_ADDR (the brk cap),
so a growing heap or mmap region can never reach them.  NK_BACKBUF sits
HIGHER than the framebuffer's maximum span: at 1024x768x24/32 the
framebuffer needs up to 3 MB, so a back-buffer at 0x0B400000 would overlap
its tail and steal its bottom rows (the mapped back-buffer overwrote the
framebuffer's second page-table slot, rendering the dock/taskbar black).
=========================================================================

---

<a id="minios_doom_w"></a>

### `MINIOS_DOOM_W`

`macro` | [progs/minios_abi.h:136](../../progs/minios_abi.h#L136)

```c
#define MINIOS_DOOM_W
```

---

<a id="minios_fb_addr"></a>

### `MINIOS_FB_ADDR`

`macro` | [progs/minios_abi.h:138](../../progs/minios_abi.h#L138)

```c
#define MINIOS_FB_ADDR
```

---

<a id="minios_nk_backbuf_addr"></a>

### `MINIOS_NK_BACKBUF_ADDR`

`macro` | [progs/minios_abi.h:139](../../progs/minios_abi.h#L139)

```c
#define MINIOS_NK_BACKBUF_ADDR
```

---

<a id="minios_nk_w"></a>

### `MINIOS_NK_W`

`macro` | [progs/minios_abi.h:140](../../progs/minios_abi.h#L140)

```c
#define MINIOS_NK_W
```

---

<a id="minios_ldso_base"></a>

### `MINIOS_LDSO_BASE`

`macro` | [progs/minios_abi.h:156](../../progs/minios_abi.h#L156)

```c
#define MINIOS_LDSO_BASE
```

========================================================================= Shared-library region (T8 ld.so, functions only) ========================================================================= Boot-global home for ET_DYN shared libraries.

The kernel assigns each library a base inside this region on first use (bump allocator, page aligned, fail closed when full); every process maps the same virtual address, and file-backed text pages are shared through the pcache (one phys page, N mappings), so the second loader only bumps the registry refcount and reuses the frames. brk and the mmap cursor are capped at LDSO_BASE, the munmap path refuses the region, and the end abuts DOOM_BACKBUF_ADDR (the graphics tail), so heap, mmap, stack and framebuffers can never reach it. No fixed cross-repo addresses: only the region bounds live here, per-boot bases stay in the kernel. =========================================================================

---

<a id="minios_ldso_size"></a>

### `MINIOS_LDSO_SIZE`

`macro` | [progs/minios_abi.h:157](../../progs/minios_abi.h#L157)

```c
#define MINIOS_LDSO_SIZE
```

---

<a id="minios_ldso_end"></a>

### `MINIOS_LDSO_END`

`macro` | [progs/minios_abi.h:158](../../progs/minios_abi.h#L158)

```c
#define MINIOS_LDSO_END
```

---

<a id="minios_nk_rgb_addr"></a>

### `MINIOS_NK_RGB_ADDR`

`macro` | [progs/minios_abi.h:166](../../progs/minios_abi.h#L166)

```c
#define MINIOS_NK_RGB_ADDR
```

RGB companion of NK_BACKBUF_ADDR: 800x360 x 3 bytes (R,G,B order), written by ring-3 Nuklear apps that want full color depth and presented with GFX_PRESENT + MINIOS_GFX_BUF_NK_RGB.

Sits clear of the framebuffer's worst span (FB + 3 MB = 0x0B500000), the indexed NK buffer (ends 0x0B646800) and the 1 MB stack (base 0x0BF00000): 0x0B700000 + 864000 ends 0x0B7D2E00. Same geometry as NK_W/NK_H, so no new dimension constants.

---

<a id="minios_nk_rgb_bytes"></a>

### `MINIOS_NK_RGB_BYTES`

`macro` | [progs/minios_abi.h:167](../../progs/minios_abi.h#L167)

```c
#define MINIOS_NK_RGB_BYTES
```

---

<a id="minios_heap_base"></a>

### `MINIOS_HEAP_BASE`

`macro` | [progs/minios_abi.h:172](../../progs/minios_abi.h#L172)

```c
#define MINIOS_HEAP_BASE
```

========================================================================= Kernel heap (supervisor only) =========================================================================

---

<a id="minios_heap_size"></a>

### `MINIOS_HEAP_SIZE`

`macro` | [progs/minios_abi.h:178](../../progs/minios_abi.h#L178)

```c
#define MINIOS_HEAP_SIZE
```

v12: 448 MB (was 192).

Every user page and page table lives on this heap, so it bounds all user memory; two FreeDom processes (browser and tab worker, an 18 MB image each, plus TLS and fonts) outgrew 192 MB. The kernel clamps it to the installed RAM at boot (CMOS), and the KASLR window starts at its end (bootdefs.h).

---

<a id="minios_pci_mmio_size"></a>

### `MINIOS_PCI_MMIO_SIZE`

`macro` | [progs/minios_abi.h:202](../../progs/minios_abi.h#L202)

```c
#define MINIOS_PCI_MMIO_SIZE
```

========================================================================= PCI MMIO relocation window ========================================================================= Physical window the xHCI driver relocates BAR0 into, and the single address at which a device register window is mapped.

It is the identity physical address: stage 2 already identity maps the first gigabyte, so mapping needs no new page directory, only a 2 MB leaf split into 4 KB page-table entries with PCD|PWT set (uncached, what Linux's ioremap produces). A write-back mapping would let a register read be answered from cache and a stale event-ring status read looks exactly like a keyboard that never types.

It sits in the gap above the heap and below the 1 GB identity limit:
the heap ends at 0x18000000 and nothing else claims the region up to
0x40000000, so a driver cannot collide with the user window, the
graphics slots or the kernel image under KASLR. The window is sized for
the largest xHCI register block in the field (HCSPARAMS1 DB size capped
by the hardware) plus room for the MMIO region, and a device whose
probed BAR0 is larger than this is refused rather than truncated.

Supervisor-only and outside [USER_LOAD_BASE, USER_LOAD_END): a ring-3
program can never see or forge a device address.

---

<a id="minios_dev_mmio_vbase"></a>

### `MINIOS_DEV_MMIO_VBASE`

`macro` | [progs/minios_abi.h:214](../../progs/minios_abi.h#L214)

```c
#define MINIOS_DEV_MMIO_VBASE
```

Virtual address the kernel maps a PCI MMIO BAR to.

It is a kernel-chosen address with no relation to the BAR's physical one, which is the whole point: a BAR lives in the host bridge's PCI hole above all of RAM, and the region above the heap is guest RAM rather than a hole, so a BAR relocated there reads back the heap. The window sits in PDPT slot 4, above the 1 GB identity map and outside the user window, so nothing else can reach it.

Supervisor-only: the KPTI clone copies this page directory into every
ring-3 process, and without the supervisor bits a user program could read
or write a device register through it.

---

<a id="minios_fb_width_max"></a>

### `MINIOS_FB_WIDTH_MAX`

`macro` | [progs/minios_abi.h:219](../../progs/minios_abi.h#L219)

```c
#define MINIOS_FB_WIDTH_MAX
```

========================================================================= Framebuffer geometry (queried via SYS_FB_INFO) =========================================================================

---

<a id="minios_fb_height_max"></a>

### `MINIOS_FB_HEIGHT_MAX`

`macro` | [progs/minios_abi.h:220](../../progs/minios_abi.h#L220)

```c
#define MINIOS_FB_HEIGHT_MAX
```

---

<a id="minios_sys_read"></a>

### `MINIOS_SYS_READ`

`macro` | [progs/minios_abi.h:238](../../progs/minios_abi.h#L238)

```c
#define MINIOS_SYS_READ
```

--- Linux ABI compatible syscalls (0-199) ---

---

<a id="minios_sys_write"></a>

### `MINIOS_SYS_WRITE`

`macro` | [progs/minios_abi.h:239](../../progs/minios_abi.h#L239)

```c
#define MINIOS_SYS_WRITE
```

---

<a id="minios_sys_open"></a>

### `MINIOS_SYS_OPEN`

`macro` | [progs/minios_abi.h:240](../../progs/minios_abi.h#L240)

```c
#define MINIOS_SYS_OPEN
```

---

<a id="minios_sys_close"></a>

### `MINIOS_SYS_CLOSE`

`macro` | [progs/minios_abi.h:241](../../progs/minios_abi.h#L241)

```c
#define MINIOS_SYS_CLOSE
```

---

<a id="minios_sys_fstat"></a>

### `MINIOS_SYS_FSTAT`

`macro` | [progs/minios_abi.h:242](../../progs/minios_abi.h#L242)

```c
#define MINIOS_SYS_FSTAT
```

---

<a id="minios_sys_poll"></a>

### `MINIOS_SYS_POLL`

`macro` | [progs/minios_abi.h:243](../../progs/minios_abi.h#L243)

```c
#define MINIOS_SYS_POLL
```

---

<a id="minios_sys_lseek"></a>

### `MINIOS_SYS_LSEEK`

`macro` | [progs/minios_abi.h:244](../../progs/minios_abi.h#L244)

```c
#define MINIOS_SYS_LSEEK
```

---

<a id="minios_sys_mmap"></a>

### `MINIOS_SYS_MMAP`

`macro` | [progs/minios_abi.h:245](../../progs/minios_abi.h#L245)

```c
#define MINIOS_SYS_MMAP
```

---

<a id="minios_sys_mprotect"></a>

### `MINIOS_SYS_MPROTECT`

`macro` | [progs/minios_abi.h:246](../../progs/minios_abi.h#L246)

```c
#define MINIOS_SYS_MPROTECT
```

---

<a id="minios_sys_munmap"></a>

### `MINIOS_SYS_MUNMAP`

`macro` | [progs/minios_abi.h:247](../../progs/minios_abi.h#L247)

```c
#define MINIOS_SYS_MUNMAP
```

---

<a id="minios_sys_brk"></a>

### `MINIOS_SYS_BRK`

`macro` | [progs/minios_abi.h:248](../../progs/minios_abi.h#L248)

```c
#define MINIOS_SYS_BRK
```

---

<a id="minios_sys_rt_sigaction"></a>

### `MINIOS_SYS_RT_SIGACTION`

`macro` | [progs/minios_abi.h:249](../../progs/minios_abi.h#L249)

```c
#define MINIOS_SYS_RT_SIGACTION
```

---

<a id="minios_sys_rt_sigprocmask"></a>

### `MINIOS_SYS_RT_SIGPROCMASK`

`macro` | [progs/minios_abi.h:250](../../progs/minios_abi.h#L250)

```c
#define MINIOS_SYS_RT_SIGPROCMASK
```

---

<a id="minios_sys_ioctl"></a>

### `MINIOS_SYS_IOCTL`

`macro` | [progs/minios_abi.h:251](../../progs/minios_abi.h#L251)

```c
#define MINIOS_SYS_IOCTL
```

---

<a id="minios_sys_writev"></a>

### `MINIOS_SYS_WRITEV`

`macro` | [progs/minios_abi.h:252](../../progs/minios_abi.h#L252)

```c
#define MINIOS_SYS_WRITEV
```

---

<a id="minios_sys_access"></a>

### `MINIOS_SYS_ACCESS`

`macro` | [progs/minios_abi.h:253](../../progs/minios_abi.h#L253)

```c
#define MINIOS_SYS_ACCESS
```

---

<a id="minios_sys_sched_yield"></a>

### `MINIOS_SYS_SCHED_YIELD`

`macro` | [progs/minios_abi.h:254](../../progs/minios_abi.h#L254)

```c
#define MINIOS_SYS_SCHED_YIELD
```

---

<a id="minios_sys_getpid"></a>

### `MINIOS_SYS_GETPID`

`macro` | [progs/minios_abi.h:255](../../progs/minios_abi.h#L255)

```c
#define MINIOS_SYS_GETPID
```

---

<a id="minios_sys_socket"></a>

### `MINIOS_SYS_SOCKET`

`macro` | [progs/minios_abi.h:256](../../progs/minios_abi.h#L256)

```c
#define MINIOS_SYS_SOCKET
```

---

<a id="minios_sys_connect"></a>

### `MINIOS_SYS_CONNECT`

`macro` | [progs/minios_abi.h:257](../../progs/minios_abi.h#L257)

```c
#define MINIOS_SYS_CONNECT
```

---

<a id="minios_sys_sendto"></a>

### `MINIOS_SYS_SENDTO`

`macro` | [progs/minios_abi.h:258](../../progs/minios_abi.h#L258)

```c
#define MINIOS_SYS_SENDTO
```

---

<a id="minios_sys_recvfrom"></a>

### `MINIOS_SYS_RECVFROM`

`macro` | [progs/minios_abi.h:259](../../progs/minios_abi.h#L259)

```c
#define MINIOS_SYS_RECVFROM
```

---

<a id="minios_sys_shutdown"></a>

### `MINIOS_SYS_SHUTDOWN`

`macro` | [progs/minios_abi.h:260](../../progs/minios_abi.h#L260)

```c
#define MINIOS_SYS_SHUTDOWN
```

---

<a id="minios_sys_fork"></a>

### `MINIOS_SYS_FORK`

`macro` | [progs/minios_abi.h:261](../../progs/minios_abi.h#L261)

```c
#define MINIOS_SYS_FORK
```

---

<a id="minios_sys_vfork"></a>

### `MINIOS_SYS_VFORK`

`macro` | [progs/minios_abi.h:262](../../progs/minios_abi.h#L262)

```c
#define MINIOS_SYS_VFORK
```

---

<a id="minios_sys_execve"></a>

### `MINIOS_SYS_EXECVE`

`macro` | [progs/minios_abi.h:263](../../progs/minios_abi.h#L263)

```c
#define MINIOS_SYS_EXECVE
```

---

<a id="minios_sys_exit"></a>

### `MINIOS_SYS_EXIT`

`macro` | [progs/minios_abi.h:264](../../progs/minios_abi.h#L264)

```c
#define MINIOS_SYS_EXIT
```

---

<a id="minios_sys_wait4"></a>

### `MINIOS_SYS_WAIT4`

`macro` | [progs/minios_abi.h:265](../../progs/minios_abi.h#L265)

```c
#define MINIOS_SYS_WAIT4
```

---

<a id="minios_sys_kill"></a>

### `MINIOS_SYS_KILL`

`macro` | [progs/minios_abi.h:266](../../progs/minios_abi.h#L266)

```c
#define MINIOS_SYS_KILL
```

---

<a id="minios_sys_uname"></a>

### `MINIOS_SYS_UNAME`

`macro` | [progs/minios_abi.h:267](../../progs/minios_abi.h#L267)

```c
#define MINIOS_SYS_UNAME
```

---

<a id="minios_sys_unlink"></a>

### `MINIOS_SYS_UNLINK`

`macro` | [progs/minios_abi.h:268](../../progs/minios_abi.h#L268)

```c
#define MINIOS_SYS_UNLINK
```

---

<a id="minios_sys_rename"></a>

### `MINIOS_SYS_RENAME`

`macro` | [progs/minios_abi.h:269](../../progs/minios_abi.h#L269)

```c
#define MINIOS_SYS_RENAME
```

---

<a id="minios_sys_readlink"></a>

### `MINIOS_SYS_READLINK`

`macro` | [progs/minios_abi.h:270](../../progs/minios_abi.h#L270)

```c
#define MINIOS_SYS_READLINK
```

---

<a id="minios_sys_gettid"></a>

### `MINIOS_SYS_GETTID`

`macro` | [progs/minios_abi.h:271](../../progs/minios_abi.h#L271)

```c
#define MINIOS_SYS_GETTID
```

---

<a id="minios_sys_flock"></a>

### `MINIOS_SYS_FLOCK`

`macro` | [progs/minios_abi.h:275](../../progs/minios_abi.h#L275)

```c
#define MINIOS_SYS_FLOCK
```

Phase 0.6 (ADR-0014): flock was 74, but Linux x86-64 74 is fsync (73 is flock).

A host-built static ELF trapping fsync got flock semantics. 73/74/75 now match the Linux table exactly.

---

<a id="minios_sys_fsync"></a>

### `MINIOS_SYS_FSYNC`

`macro` | [progs/minios_abi.h:276](../../progs/minios_abi.h#L276)

```c
#define MINIOS_SYS_FSYNC
```

---

<a id="minios_sys_fdatasync"></a>

### `MINIOS_SYS_FDATASYNC`

`macro` | [progs/minios_abi.h:277](../../progs/minios_abi.h#L277)

```c
#define MINIOS_SYS_FDATASYNC
```

---

<a id="minios_sys_getcwd"></a>

### `MINIOS_SYS_GETCWD`

`macro` | [progs/minios_abi.h:278](../../progs/minios_abi.h#L278)

```c
#define MINIOS_SYS_GETCWD
```

---

<a id="minios_sys_gettimeofday"></a>

### `MINIOS_SYS_GETTIMEOFDAY`

`macro` | [progs/minios_abi.h:279](../../progs/minios_abi.h#L279)

```c
#define MINIOS_SYS_GETTIMEOFDAY
```

---

<a id="minios_sys_arch_prctl"></a>

### `MINIOS_SYS_ARCH_PRCTL`

`macro` | [progs/minios_abi.h:280](../../progs/minios_abi.h#L280)

```c
#define MINIOS_SYS_ARCH_PRCTL
```

---

<a id="minios_sys_openat"></a>

### `MINIOS_SYS_OPENAT`

`macro` | [progs/minios_abi.h:281](../../progs/minios_abi.h#L281)

```c
#define MINIOS_SYS_OPENAT
```

---

<a id="minios_sys_newfstatat"></a>

### `MINIOS_SYS_NEWFSTATAT`

`macro` | [progs/minios_abi.h:282](../../progs/minios_abi.h#L282)

```c
#define MINIOS_SYS_NEWFSTATAT
```

---

<a id="minios_sys_statx"></a>

### `MINIOS_SYS_STATX`

`macro` | [progs/minios_abi.h:285](../../progs/minios_abi.h#L285)

```c
#define MINIOS_SYS_STATX
```

Phase 0.6 (ADR-0014): statx was 267, but Linux x86-64 267 is readlinkat; statx is 332.

The header now claims the true number.

---

<a id="minios_sys_set_robust_list"></a>

### `MINIOS_SYS_SET_ROBUST_LIST`

`macro` | [progs/minios_abi.h:289](../../progs/minios_abi.h#L289)

```c
#define MINIOS_SYS_SET_ROBUST_LIST
```

Phase 0.6 (ADR-0014): this was SET_MEMPOLICY 273, but Linux x86-64 273 is set_robust_list (set_mempolicy is 238).

The label now names the number the kernel actually stubs.

---

<a id="minios_sys_prlimit64"></a>

### `MINIOS_SYS_PRLIMIT64`

`macro` | [progs/minios_abi.h:293](../../progs/minios_abi.h#L293)

```c
#define MINIOS_SYS_PRLIMIT64
```

301 was a fossil alias of set_robust_list; the true number is 273.

The kernel still answers 0 there for old binaries (see syscalls.c), but new code must use 273.

---

<a id="minios_sys_getrandom"></a>

### `MINIOS_SYS_GETRANDOM`

`macro` | [progs/minios_abi.h:294](../../progs/minios_abi.h#L294)

```c
#define MINIOS_SYS_GETRANDOM
```

---

<a id="minios_sys_rseq"></a>

### `MINIOS_SYS_RSEQ`

`macro` | [progs/minios_abi.h:295](../../progs/minios_abi.h#L295)

```c
#define MINIOS_SYS_RSEQ
```

---

<a id="minios_sys_exit_group"></a>

### `MINIOS_SYS_EXIT_GROUP`

`macro` | [progs/minios_abi.h:296](../../progs/minios_abi.h#L296)

```c
#define MINIOS_SYS_EXIT_GROUP
```

---

<a id="minios_sys_set_tid_address"></a>

### `MINIOS_SYS_SET_TID_ADDRESS`

`macro` | [progs/minios_abi.h:297](../../progs/minios_abi.h#L297)

```c
#define MINIOS_SYS_SET_TID_ADDRESS
```

---

<a id="minios_sys_clock_gettime"></a>

### `MINIOS_SYS_CLOCK_GETTIME`

`macro` | [progs/minios_abi.h:298](../../progs/minios_abi.h#L298)

```c
#define MINIOS_SYS_CLOCK_GETTIME
```

---

<a id="minios_sys_tgkill"></a>

### `MINIOS_SYS_TGKILL`

`macro` | [progs/minios_abi.h:299](../../progs/minios_abi.h#L299)

```c
#define MINIOS_SYS_TGKILL
```

---

<a id="minios_sys_dns"></a>

### `MINIOS_SYS_DNS`

`macro` | [progs/minios_abi.h:302](../../progs/minios_abi.h#L302)

```c
#define MINIOS_SYS_DNS
```

--- MiniOS custom syscalls (200-299) ---

---

<a id="minios_sys_tls_handshake"></a>

### `MINIOS_SYS_TLS_HANDSHAKE`

`macro` | [progs/minios_abi.h:308](../../progs/minios_abi.h#L308)

```c
#define MINIOS_SYS_TLS_HANDSHAKE
```

201/202/203: retired kernel-TLS numbers (the engine left ring 0).

202 serves Linux futex(2) (glibc NPTL/malloc/resolver need __NR_futex; -ENOSYS there aborts the process) and 201 serves Linux time(2) (static glibc has no vDSO; OpenSSL validates certificate dates with it); 203 stays -ENOSYS. Values are frozen so the ABI checksum never moves.

---

<a id="minios_sys_tls_send"></a>

### `MINIOS_SYS_TLS_SEND`

`macro` | [progs/minios_abi.h:309](../../progs/minios_abi.h#L309)

```c
#define MINIOS_SYS_TLS_SEND
```

---

<a id="minios_sys_tls_recv"></a>

### `MINIOS_SYS_TLS_RECV`

`macro` | [progs/minios_abi.h:310](../../progs/minios_abi.h#L310)

```c
#define MINIOS_SYS_TLS_RECV
```

---

<a id="minios_sys_time"></a>

### `MINIOS_SYS_TIME`

`macro` | [progs/minios_abi.h:313](../../progs/minios_abi.h#L313)

```c
#define MINIOS_SYS_TIME
```

v12: relocated from 204, which belongs to Linux sched_getaffinity (glibc's get_nprocs read the millisecond clock as a CPU mask).

---

<a id="minios_sys_kbd"></a>

### `MINIOS_SYS_KBD`

`macro` | [progs/minios_abi.h:314](../../progs/minios_abi.h#L314)

```c
#define MINIOS_SYS_KBD
```

---

<a id="minios_sys_palette"></a>

### `MINIOS_SYS_PALETTE`

`macro` | [progs/minios_abi.h:315](../../progs/minios_abi.h#L315)

```c
#define MINIOS_SYS_PALETTE
```

---

<a id="minios_sys_kbd_raw"></a>

### `MINIOS_SYS_KBD_RAW`

`macro` | [progs/minios_abi.h:316](../../progs/minios_abi.h#L316)

```c
#define MINIOS_SYS_KBD_RAW
```

---

<a id="minios_sys_vga_mode"></a>

### `MINIOS_SYS_VGA_MODE`

`macro` | [progs/minios_abi.h:317](../../progs/minios_abi.h#L317)

```c
#define MINIOS_SYS_VGA_MODE
```

---

<a id="minios_sys_pcspk_init"></a>

### `MINIOS_SYS_PCSPK_INIT`

`macro` | [progs/minios_abi.h:318](../../progs/minios_abi.h#L318)

```c
#define MINIOS_SYS_PCSPK_INIT
```

---

<a id="minios_sys_pcspk_tone"></a>

### `MINIOS_SYS_PCSPK_TONE`

`macro` | [progs/minios_abi.h:319](../../progs/minios_abi.h#L319)

```c
#define MINIOS_SYS_PCSPK_TONE
```

---

<a id="minios_sys_doom_frame"></a>

### `MINIOS_SYS_DOOM_FRAME`

`macro` | [progs/minios_abi.h:320](../../progs/minios_abi.h#L320)

```c
#define MINIOS_SYS_DOOM_FRAME
```

---

<a id="minios_sys_rtc"></a>

### `MINIOS_SYS_RTC`

`macro` | [progs/minios_abi.h:321](../../progs/minios_abi.h#L321)

```c
#define MINIOS_SYS_RTC
```

---

<a id="minios_sys_fb_info"></a>

### `MINIOS_SYS_FB_INFO`

`macro` | [progs/minios_abi.h:322](../../progs/minios_abi.h#L322)

```c
#define MINIOS_SYS_FB_INFO
```

---

<a id="minios_sys_pcspk_vol"></a>

### `MINIOS_SYS_PCSPK_VOL`

`macro` | [progs/minios_abi.h:323](../../progs/minios_abi.h#L323)

```c
#define MINIOS_SYS_PCSPK_VOL
```

---

<a id="minios_sys_spawn"></a>

### `MINIOS_SYS_SPAWN`

`macro` | [progs/minios_abi.h:324](../../progs/minios_abi.h#L324)

```c
#define MINIOS_SYS_SPAWN
```

---

<a id="minios_sys_lz4_compress"></a>

### `MINIOS_SYS_LZ4_COMPRESS`

`macro` | [progs/minios_abi.h:325](../../progs/minios_abi.h#L325)

```c
#define MINIOS_SYS_LZ4_COMPRESS
```

---

<a id="minios_sys_lz4_decompress"></a>

### `MINIOS_SYS_LZ4_DECOMPRESS`

`macro` | [progs/minios_abi.h:330](../../progs/minios_abi.h#L330)

```c
#define MINIOS_SYS_LZ4_DECOMPRESS
```

lz4_decompress moved from 217 to 248: Linux x86-64 217 is getdents64, which the kernel now serves (directory enumeration for readdir(3) and CPython's os.scandir; see docs/spec/python.md).

248 is a free x86-64 number inside the MiniOS window, and the ABI checksum moved with it.

---

<a id="minios_sys_mouse"></a>

### `MINIOS_SYS_MOUSE`

`macro` | [progs/minios_abi.h:331](../../progs/minios_abi.h#L331)

```c
#define MINIOS_SYS_MOUSE
```

---

<a id="minios_sys_nk_frame"></a>

### `MINIOS_SYS_NK_FRAME`

`macro` | [progs/minios_abi.h:332](../../progs/minios_abi.h#L332)

```c
#define MINIOS_SYS_NK_FRAME
```

---

<a id="minios_sys_sb16_open"></a>

### `MINIOS_SYS_SB16_OPEN`

`macro` | [progs/minios_abi.h:333](../../progs/minios_abi.h#L333)

```c
#define MINIOS_SYS_SB16_OPEN
```

---

<a id="minios_sys_sb16_submit"></a>

### `MINIOS_SYS_SB16_SUBMIT`

`macro` | [progs/minios_abi.h:334](../../progs/minios_abi.h#L334)

```c
#define MINIOS_SYS_SB16_SUBMIT
```

---

<a id="minios_sys_gfx_set_title"></a>

### `MINIOS_SYS_GFX_SET_TITLE`

`macro` | [progs/minios_abi.h:335](../../progs/minios_abi.h#L335)

```c
#define MINIOS_SYS_GFX_SET_TITLE
```

---

<a id="minios_sys_sb16_pump"></a>

### `MINIOS_SYS_SB16_PUMP`

`macro` | [progs/minios_abi.h:336](../../progs/minios_abi.h#L336)

```c
#define MINIOS_SYS_SB16_PUMP
```

---

<a id="minios_sys_sb16_stream_open"></a>

### `MINIOS_SYS_SB16_STREAM_OPEN`

`macro` | [progs/minios_abi.h:339](../../progs/minios_abi.h#L339)

```c
#define MINIOS_SYS_SB16_STREAM_OPEN
```

v12: relocated from 229/230, which belong to Linux clock_getres and clock_nanosleep (static glibc's sleep, usleep and nanosleep).

---

<a id="minios_sys_sb16_stream_close"></a>

### `MINIOS_SYS_SB16_STREAM_CLOSE`

`macro` | [progs/minios_abi.h:340](../../progs/minios_abi.h#L340)

```c
#define MINIOS_SYS_SB16_STREAM_CLOSE
```

---

<a id="minios_sys_sb16_stream_submit"></a>

### `MINIOS_SYS_SB16_STREAM_SUBMIT`

`macro` | [progs/minios_abi.h:341](../../progs/minios_abi.h#L341)

```c
#define MINIOS_SYS_SB16_STREAM_SUBMIT
```

---

<a id="minios_sys_sb16_stream_volume"></a>

### `MINIOS_SYS_SB16_STREAM_VOLUME`

`macro` | [progs/minios_abi.h:342](../../progs/minios_abi.h#L342)

```c
#define MINIOS_SYS_SB16_STREAM_VOLUME
```

---

<a id="minios_sys_thread_spawn"></a>

### `MINIOS_SYS_THREAD_SPAWN`

`macro` | [progs/minios_abi.h:343](../../progs/minios_abi.h#L343)

```c
#define MINIOS_SYS_THREAD_SPAWN
```

---

<a id="minios_sys_futex_wait"></a>

### `MINIOS_SYS_FUTEX_WAIT`

`macro` | [progs/minios_abi.h:344](../../progs/minios_abi.h#L344)

```c
#define MINIOS_SYS_FUTEX_WAIT
```

---

<a id="minios_sys_futex_wake"></a>

### `MINIOS_SYS_FUTEX_WAKE`

`macro` | [progs/minios_abi.h:345](../../progs/minios_abi.h#L345)

```c
#define MINIOS_SYS_FUTEX_WAKE
```

---

<a id="minios_sys_submit_batch"></a>

### `MINIOS_SYS_SUBMIT_BATCH`

`macro` | [progs/minios_abi.h:346](../../progs/minios_abi.h#L346)

```c
#define MINIOS_SYS_SUBMIT_BATCH
```

---

<a id="minios_sys_getc_raw"></a>

### `MINIOS_SYS_GETC_RAW`

`macro` | [progs/minios_abi.h:347](../../progs/minios_abi.h#L347)

```c
#define MINIOS_SYS_GETC_RAW
```

---

<a id="minios_sys_gfx_present"></a>

### `MINIOS_SYS_GFX_PRESENT`

`macro` | [progs/minios_abi.h:348](../../progs/minios_abi.h#L348)

```c
#define MINIOS_SYS_GFX_PRESENT
```

---

<a id="minios_sys_seccomp"></a>

### `MINIOS_SYS_SECCOMP`

`macro` | [progs/minios_abi.h:349](../../progs/minios_abi.h#L349)

```c
#define MINIOS_SYS_SECCOMP
```

---

<a id="minios_sys_nice"></a>

### `MINIOS_SYS_NICE`

`macro` | [progs/minios_abi.h:350](../../progs/minios_abi.h#L350)

```c
#define MINIOS_SYS_NICE
```

---

<a id="minios_sys_rlimit"></a>

### `MINIOS_SYS_RLIMIT`

`macro` | [progs/minios_abi.h:351](../../progs/minios_abi.h#L351)

```c
#define MINIOS_SYS_RLIMIT
```

---

<a id="minios_sys_dir_list"></a>

### `MINIOS_SYS_DIR_LIST`

`macro` | [progs/minios_abi.h:352](../../progs/minios_abi.h#L352)

```c
#define MINIOS_SYS_DIR_LIST
```

---

<a id="minios_sys_gfx_zoom"></a>

### `MINIOS_SYS_GFX_ZOOM`

`macro` | [progs/minios_abi.h:353](../../progs/minios_abi.h#L353)

```c
#define MINIOS_SYS_GFX_ZOOM
```

---

<a id="minios_sys_wl_attach"></a>

### `MINIOS_SYS_WL_ATTACH`

`macro` | [progs/minios_abi.h:358](../../progs/minios_abi.h#L358)

```c
#define MINIOS_SYS_WL_ATTACH
```

Wayland-mini reservations (ADR-0024): ATTACH/COMMIT/INPUT for the ring-3 wlcomp compositor.

Reserved only: the kernel answers -ENOSYS until Phase 2 wires them, so they stay OUT of the checksum and the ABI version does not move yet.

---

<a id="minios_sys_wl_commit"></a>

### `MINIOS_SYS_WL_COMMIT`

`macro` | [progs/minios_abi.h:359](../../progs/minios_abi.h#L359)

```c
#define MINIOS_SYS_WL_COMMIT
```

---

<a id="minios_sys_wl_input"></a>

### `MINIOS_SYS_WL_INPUT`

`macro` | [progs/minios_abi.h:360](../../progs/minios_abi.h#L360)

```c
#define MINIOS_SYS_WL_INPUT
```

---

<a id="minios_sys_pcm2_open"></a>

### `MINIOS_SYS_PCM2_OPEN`

`macro` | [progs/minios_abi.h:365](../../progs/minios_abi.h#L365)

```c
#define MINIOS_SYS_PCM2_OPEN
```

Low-latency PCM path (pcm2, 8-bit mono 22050 Hz over SB16 single-cycle DMA): OPEN takes flags (bit 0 NONBLOCK), WRITE returns bytes taken (blocking unless NONBLOCK), CLOSE releases.

Numbers 246-248 are free in Linux x86-64 (no table entry), so no DEVIATION is needed.

---

<a id="minios_sys_pcm2_write"></a>

### `MINIOS_SYS_PCM2_WRITE`

`macro` | [progs/minios_abi.h:366](../../progs/minios_abi.h#L366)

```c
#define MINIOS_SYS_PCM2_WRITE
```

---

<a id="minios_sys_pcm2_close"></a>

### `MINIOS_SYS_PCM2_CLOSE`

`macro` | [progs/minios_abi.h:367](../../progs/minios_abi.h#L367)

```c
#define MINIOS_SYS_PCM2_CLOSE
```

---

<a id="minios_sys_clip_set"></a>

### `MINIOS_SYS_CLIP_SET`

`macro` | [progs/minios_abi.h:375](../../progs/minios_abi.h#L375)

```c
#define MINIOS_SYS_CLIP_SET
```

Shared text clipboard (terminal copy, vedit paste): SET copies len bytes in (refused past 4096, never truncated), GET copies out up to the caller's cap (refused when empty or undersize).

Linux x86-64 owns 249 (request_key) and 250 (keyctl); no ring-3 program MiniOS runs calls either (no keyutils in the static set), so the MiniOS window reuses them the same way 200+ reuses other Linux numbers. Bumping the ABI version with the addition, per contract.

---

<a id="minios_sys_clip_get"></a>

### `MINIOS_SYS_CLIP_GET`

`macro` | [progs/minios_abi.h:376](../../progs/minios_abi.h#L376)

```c
#define MINIOS_SYS_CLIP_GET
```

---

<a id="minios_sys_minfo"></a>

### `MINIOS_SYS_MINFO`

`macro` | [progs/minios_abi.h:393](../../progs/minios_abi.h#L393)

```c
#define MINIOS_SYS_MINFO
```

Machine info (mtop, 251): multiplexed kernel-statistics read with a selector in a1 and up to two out-words in a2/a3 (longs, KB unless noted), so every call fits the three-argument inline-syscall form miniGCC supports.

0 = heap used/free KB, 1 = ramdisk used/cap KB, 2 = MiniFS free/total blocks (0/0 when unmounted), 3 = cpu total/idle 100 Hz ticks (busy percent is (dt-didle)*100/dt between two reads of the same call), 4 = cpu count/uptime seconds, 5 = clear the caller's terminal view, 6 = sleep a2 milliseconds (0..60000, clamped; parks the caller on a wait queue woken by the 100 Hz tick, -EIO when the waker is missing so it fails closed instead of hanging). Unknown selectors are -EINVAL, short/out-of-window pointers -EFAULT. DEVIATION: Linux x86-64 owns 251 (ioprio_set). No ring-3 program MiniOS runs traps ioprio (no ionice port, glibc never calls it implicitly), and a trapped call fails closed on selector validation, the same class as the CLIP reuse of 249/250. Listed in tools/check_abi_numbers.py DEVIATIONS.

---

<a id="minios_pcm2_nonblock"></a>

### `MINIOS_PCM2_NONBLOCK`

`macro` | [progs/minios_abi.h:394](../../progs/minios_abi.h#L394)

```c
#define MINIOS_PCM2_NONBLOCK
```

---

<a id="minios_pcm2_rate"></a>

### `MINIOS_PCM2_RATE`

`macro` | [progs/minios_abi.h:398](../../progs/minios_abi.h#L398)

```c
#define MINIOS_PCM2_RATE
```

pcm2 geometry: 8-bit mono at MINIOS_PCM2_RATE, DMA fragments of MINIOS_PCM2_FRAG bytes (~11.6 ms).

A writer produces whole fragments; the kernel refills finished ones from its ring.

---

<a id="minios_pcm2_frag"></a>

### `MINIOS_PCM2_FRAG`

`macro` | [progs/minios_abi.h:399](../../progs/minios_abi.h#L399)

```c
#define MINIOS_PCM2_FRAG
```

---

<a id="minios_sys_clone"></a>

### `MINIOS_SYS_CLONE`

`macro` | [progs/minios_abi.h:401](../../progs/minios_abi.h#L401)

```c
#define MINIOS_SYS_CLONE
```

---

<a id="minios_gfx_buf_game"></a>

### `MINIOS_GFX_BUF_GAME`

`macro` | [progs/minios_abi.h:410](../../progs/minios_abi.h#L410)

```c
#define MINIOS_GFX_BUF_GAME
```

Generic framebuffer/window present ABI (boyscout fix for app-specific syscalls).

DOOM_FRAME/NK_FRAME remain as compat numbers that route through the same compositor; new code uses GFX_PRESENT with a buffer id: 0 = 320x200 paletted game buffer (DOOM/Q2G path) 1 = 800x360 indexed Nuklear buffer (NK path, 256-color compat) 2 = 800x360 RGB Nuklear buffer (NK_RGB_ADDR, full color depth) GFX_SET_TITLE is already generic (renamed from Q2G_SET_TITLE).

---

<a id="minios_gfx_buf_nk"></a>

### `MINIOS_GFX_BUF_NK`

`macro` | [progs/minios_abi.h:411](../../progs/minios_abi.h#L411)

```c
#define MINIOS_GFX_BUF_NK
```

---

<a id="minios_gfx_buf_nk_rgb"></a>

### `MINIOS_GFX_BUF_NK_RGB`

`macro` | [progs/minios_abi.h:412](../../progs/minios_abi.h#L412)

```c
#define MINIOS_GFX_BUF_NK_RGB
```

---

<a id="minios_sys_framebuffer_commit"></a>

### `MINIOS_SYS_FRAMEBUFFER_COMMIT`

`macro` | [progs/minios_abi.h:413](../../progs/minios_abi.h#L413)

```c
#define MINIOS_SYS_FRAMEBUFFER_COMMIT
```

---

<a id="minios_sys_window_present"></a>

### `MINIOS_SYS_WINDOW_PRESENT`

`macro` | [progs/minios_abi.h:414](../../progs/minios_abi.h#L414)

```c
#define MINIOS_SYS_WINDOW_PRESENT
```

---

<a id="minios_sys_window_title"></a>

### `MINIOS_SYS_WINDOW_TITLE`

`macro` | [progs/minios_abi.h:415](../../progs/minios_abi.h#L415)

```c
#define MINIOS_SYS_WINDOW_TITLE
```

---

<a id="minios_gfx_zoom_native"></a>

### `MINIOS_GFX_ZOOM_NATIVE`

`macro` | [progs/minios_abi.h:422](../../progs/minios_abi.h#L422)

```c
#define MINIOS_GFX_ZOOM_NATIVE
```

GFX_ZOOM (242) argument values.

0/1 are the original native/2x game zoom; 2 asks the WM for true fullscreen (the app scales to the whole display with its aspect kept, no chrome, keyboard focus taken) and 3 returns to the windowed view it came from. Kernels that predate the fullscreen values answer -EINVAL, so a caller simply stays windowed.

---

<a id="minios_gfx_zoom_2x"></a>

### `MINIOS_GFX_ZOOM_2X`

`macro` | [progs/minios_abi.h:423](../../progs/minios_abi.h#L423)

```c
#define MINIOS_GFX_ZOOM_2X
```

---

<a id="minios_gfx_zoom_fullscreen"></a>

### `MINIOS_GFX_ZOOM_FULLSCREEN`

`macro` | [progs/minios_abi.h:424](../../progs/minios_abi.h#L424)

```c
#define MINIOS_GFX_ZOOM_FULLSCREEN
```

---

<a id="minios_gfx_zoom_windowed"></a>

### `MINIOS_GFX_ZOOM_WINDOWED`

`macro` | [progs/minios_abi.h:425](../../progs/minios_abi.h#L425)

```c
#define MINIOS_GFX_ZOOM_WINDOWED
```

---

<a id="sys_time_ms"></a>

### `SYS_TIME_MS`

`macro` | [progs/minios_abi.h:428](../../progs/minios_abi.h#L428)

```c
#define SYS_TIME_MS
```

--- Compatibility aliases for runtime bindings ---

---

<a id="sys_palette"></a>

### `SYS_PALETTE`

`macro` | [progs/minios_abi.h:429](../../progs/minios_abi.h#L429)

```c
#define SYS_PALETTE
```

---

<a id="sys_pcspk_init"></a>

### `SYS_PCSPK_INIT`

`macro` | [progs/minios_abi.h:430](../../progs/minios_abi.h#L430)

```c
#define SYS_PCSPK_INIT
```

---

<a id="sys_pcspk_tone"></a>

### `SYS_PCSPK_TONE`

`macro` | [progs/minios_abi.h:431](../../progs/minios_abi.h#L431)

```c
#define SYS_PCSPK_TONE
```

---

<a id="sys_rtc"></a>

### `SYS_RTC`

`macro` | [progs/minios_abi.h:432](../../progs/minios_abi.h#L432)

```c
#define SYS_RTC
```

---

<a id="sys_fb_info"></a>

### `SYS_FB_INFO`

`macro` | [progs/minios_abi.h:433](../../progs/minios_abi.h#L433)

```c
#define SYS_FB_INFO
```

---

<a id="sys_pcspk_vol"></a>

### `SYS_PCSPK_VOL`

`macro` | [progs/minios_abi.h:434](../../progs/minios_abi.h#L434)

```c
#define SYS_PCSPK_VOL
```

---

<a id="sys_spawn"></a>

### `SYS_SPAWN`

`macro` | [progs/minios_abi.h:435](../../progs/minios_abi.h#L435)

```c
#define SYS_SPAWN
```

---

<a id="sys_time"></a>

### `SYS_TIME`

`macro` | [progs/minios_abi.h:436](../../progs/minios_abi.h#L436)

```c
#define SYS_TIME
```

---

<a id="sys_write"></a>

### `SYS_WRITE`

`macro` | [progs/minios_abi.h:437](../../progs/minios_abi.h#L437)

```c
#define SYS_WRITE
```

---

<a id="minios_eabi_mismatch"></a>

### `MINIOS_EABI_MISMATCH`

`macro` | [progs/minios_abi.h:440](../../progs/minios_abi.h#L440)

```c
#define MINIOS_EABI_MISMATCH
```

--- Error codes ---

---

<a id="minios_note_name"></a>

### `MINIOS_NOTE_NAME`

`macro` | [progs/minios_abi.h:453](../../progs/minios_abi.h#L453)

```c
#define MINIOS_NOTE_NAME
```

========================================================================= Process note (ELF PT_NOTE) ========================================================================= A foreground run normally executes in the shell's pid-0 exec frame, which is not a process: fork, execve and anything built on them fail there.

A program that needs process semantics (threads plus fork/exec, like the FreeDom browser) carries one ELF note with name MINIOS_NOTE_NAME, type MINIOS_NOTE_PROCESS and a 4-byte descriptor; the shell then runs it as an isolated process and waits for it in the foreground. Kernels that do not know the note ignore it, so it needs no ABI bump. =========================================================================

---

<a id="minios_note_process"></a>

### `MINIOS_NOTE_PROCESS`

`macro` | [progs/minios_abi.h:454](../../progs/minios_abi.h#L454)

```c
#define MINIOS_NOTE_PROCESS
```

---

<a id="minios_note_sign"></a>

### `MINIOS_NOTE_SIGN`

`macro` | [progs/minios_abi.h:455](../../progs/minios_abi.h#L455)

```c
#define MINIOS_NOTE_SIGN
```

---
