#ifndef MINIOS_ABI_H
#define MINIOS_ABI_H

/* minios_abi.h -- Single source of truth for the MiniOS user-kernel ABI.
 *
 * Both the kernel (kernel.c, vga_fb.h, kernel.h) and ring-3 programs (DOOM,
 * Quake 2, Nuklear, MicroPython, Lua) include this header so that memory
 * layout constants never drift apart.  When you change an address here, both
 * sides pick it up on the next build -- no manual cross-file synchronization
 * needed.
 *
 * RULE: every magic address that a ring-3 program hardcodes today MUST live
 * here instead.  Programs include this header; the kernel includes vga_fb.h
 * and kernel.h which derive their values from the same source.
 *
 * ABI versioning: MINIOS_ABI_VERSION is a monotonic integer bumped on every
 * backwards-incompatible change to layout constants or syscall numbers.
 * MINIOS_ABI_CHECKSUM is a compile-time hash of all layout constants; the
 * ELF loader verifies both before accepting a binary.  A mismatch returns
 * -EABI_MISMATCH with a diagnostic.
 */

/* =========================================================================
 * ABI Version
 * =========================================================================
 * Bump MINIOS_ABI_VERSION on every backwards-incompatible change:
 *   - layout constant address or size change
 *   - syscall number addition, removal, or reordering
 *   - graphics back-buffer geometry change
 *   - kernel heap relocation
 *
 * MINIOS_ABI_CHECKSUM is computed at compile time from all layout constants.
 * The kernel ELF loader recomputes it and compares against the binary's
 * embedded copy.  A mismatch rejects the binary before execution.
 * ========================================================================= */
#define MINIOS_ABI_VERSION 1

/* Compile-time checksum: XOR-fold of all layout constants.
 * Recomputed by the kernel at load time for verification. */
#define MINIOS_ABI_CHECKSUM ( \
    MINIOS_USER_LOAD_BASE      ^ \
    MINIOS_USER_LOAD_END       ^ \
    MINIOS_USER_STACK_SIZE     ^ \
    MINIOS_USER_STACK_TOP      ^ \
    MINIOS_USER_STACK_BASE     ^ \
    MINIOS_USER_BRK_END        ^ \
    MINIOS_DOOM_BACKBUF_ADDR   ^ \
    MINIOS_DOOM_W              ^ \
    MINIOS_DOOM_H              ^ \
    MINIOS_FB_ADDR             ^ \
    MINIOS_NK_BACKBUF_ADDR     ^ \
    MINIOS_NK_W                ^ \
    MINIOS_NK_H                ^ \
    MINIOS_HEAP_BASE           ^ \
    MINIOS_HEAP_SIZE           ^ \
    MINIOS_FB_WIDTH_MAX        ^ \
    MINIOS_FB_HEIGHT_MAX         \
)

/* =========================================================================
 * User window geometry
 * =========================================================================
 * The user window is the virtual address range mapped for ring-3 programs:
 *   [USER_LOAD_BASE, USER_LOAD_END)
 *
 * Programs load at USER_LOAD_BASE (ET_EXEC base 0, ET_DYN base =
 * USER_LOAD_BASE).  The brk grows upward from the end of loaded segments.
 * The mmap region grows downward from USER_BRK_END toward the brk.
 * The stack grows downward from USER_STACK_TOP.
 *
 * Layout (low to high):
 *   USER_LOAD_BASE          program text/data start
 *   ...brk grows up...      heap (brk syscall)
 *   ...mmap grows down...   anonymous mmap allocations
 *   USER_BRK_END            hard ceiling for both brk and mmap
 *   DOOM_BACKBUF_ADDR       DOOM/Q2G 320x200 back-buffer (kernel-mapped)
 *   FB_ADDR                 linear framebuffer (kernel-mapped, VBE)
 *   NK_BACKBUF_ADDR         Nuklear 800x360 back-buffer (kernel-mapped)
 *   USER_STACK_BASE         stack region base (1 MB below top)
 *   USER_STACK_TOP          stack top (= USER_LOAD_END)
 *   HEAP_BASE               kernel heap (supervisor only, not in window)
 * ========================================================================= */
#define MINIOS_USER_LOAD_BASE   0x00400000UL
#define MINIOS_USER_LOAD_END    0x0C000000UL
#define MINIOS_USER_STACK_SIZE  (1024UL * 1024)
#define MINIOS_USER_STACK_TOP   MINIOS_USER_LOAD_END
#define MINIOS_USER_STACK_BASE  (MINIOS_USER_STACK_TOP - MINIOS_USER_STACK_SIZE)
#define MINIOS_USER_BRK_END     MINIOS_USER_STACK_BASE

/* =========================================================================
 * Graphics back-buffers (kernel-mapped into user window)
 * =========================================================================
 * The kernel allocates these from the kernel heap and maps them into the user
 * window via the 4 KB page tables at boot (mm_setup_protections).  A ring-3
 * program writes to these addresses and calls the corresponding SYS_*_FRAME
 * syscall; the kernel composites the buffer onto the desktop.
 *
 * All three sit in the reserved tail above DOOM_BACKBUF_ADDR (the brk cap),
 * so a growing heap or mmap region can never reach them.
 * ========================================================================= */
#define MINIOS_DOOM_BACKBUF_ADDR  0x0B000000UL
#define MINIOS_DOOM_W             320
#define MINIOS_DOOM_H             200
#define MINIOS_FB_ADDR            0x0B200000UL
#define MINIOS_NK_BACKBUF_ADDR    0x0B400000UL
#define MINIOS_NK_W               800
#define MINIOS_NK_H               360

/* =========================================================================
 * Kernel heap (supervisor only)
 * ========================================================================= */
#define MINIOS_HEAP_BASE  0x0C000000UL
#define MINIOS_HEAP_SIZE  (192UL * 1024 * 1024)

/* =========================================================================
 * Framebuffer geometry (queried via SYS_FB_INFO)
 * ========================================================================= */
#define MINIOS_FB_WIDTH_MAX  256
#define MINIOS_FB_HEIGHT_MAX 128

/* =========================================================================
 * Canonical syscall table
 * =========================================================================
 * Single source of truth for all kernel syscall numbers.  CVM, Lua, and
 * MicroPython MUST reference these constants instead of defining their own.
 *
 * Layout:
 *   0-199   Linux ABI compatible syscalls (read, write, brk, mmap, ...)
 *   200-299 MiniOS custom syscalls (networking, audio, graphics, ...)
 *   300+    Reserved for future use
 *
 * RULE: never reorder or remove existing numbers.  Append new syscalls
 * at the end of their section.  Gaps are reserved and must not be reused.
 * ========================================================================= */

/* --- Linux ABI compatible syscalls (0-199) --- */
#define MINIOS_SYS_READ          0
#define MINIOS_SYS_WRITE         1
#define MINIOS_SYS_OPEN          2
#define MINIOS_SYS_CLOSE         3
#define MINIOS_SYS_FSTAT         5
#define MINIOS_SYS_POLL          7
#define MINIOS_SYS_LSEEK         8
#define MINIOS_SYS_MMAP          9
#define MINIOS_SYS_MPROTECT     10
#define MINIOS_SYS_MUNMAP       11
#define MINIOS_SYS_BRK          12
#define MINIOS_SYS_RT_SIGACTION 13
#define MINIOS_SYS_RT_SIGPROCMASK 14
#define MINIOS_SYS_IOCTL        16
#define MINIOS_SYS_WRITEV       20
#define MINIOS_SYS_ACCESS       21
#define MINIOS_SYS_SCHED_YIELD  24
#define MINIOS_SYS_GETPID       39
#define MINIOS_SYS_SOCKET       41
#define MINIOS_SYS_CONNECT      42
#define MINIOS_SYS_SENDTO       44
#define MINIOS_SYS_RECVFROM     45
#define MINIOS_SYS_SHUTDOWN     48
#define MINIOS_SYS_FORK         57
#define MINIOS_SYS_VFORK        58
#define MINIOS_SYS_EXECVE       59
#define MINIOS_SYS_EXIT         60
#define MINIOS_SYS_WAIT4        61
#define MINIOS_SYS_KILL         62
#define MINIOS_SYS_UNLINK       87
#define MINIOS_SYS_READLINK     89
#define MINIOS_SYS_GETTID      186
#define MINIOS_SYS_FLOCK        74
#define MINIOS_SYS_GETCWD       79
#define MINIOS_SYS_GETTIMEOFDAY 96
#define MINIOS_SYS_ARCH_PRCTL  158
#define MINIOS_SYS_OPENAT      257
#define MINIOS_SYS_NEWFSTATAT  262
#define MINIOS_SYS_READLINK     89
#define MINIOS_SYS_STATX       267
#define MINIOS_SYS_SET_MEMPOLICY 273
#define MINIOS_SYS_SET_ROBUST_LIST 301
#define MINIOS_SYS_PRLIMIT64   302
#define MINIOS_SYS_GETRANDOM   318
#define MINIOS_SYS_RSEQ        334
#define MINIOS_SYS_EXIT_GROUP  231
#define MINIOS_SYS_SET_TID_ADDRESS 218
#define MINIOS_SYS_CLOCK_GETTIME 228
#define MINIOS_SYS_TGKILL      234

/* --- MiniOS custom syscalls (200-299) --- */
#define MINIOS_SYS_DNS          200
#define MINIOS_SYS_TLS_HANDSHAKE 201
#define MINIOS_SYS_TLS_SEND     202
#define MINIOS_SYS_TLS_RECV     203
#define MINIOS_SYS_TIME        204
#define MINIOS_SYS_KBD         205
#define MINIOS_SYS_PALETTE     206
#define MINIOS_SYS_KBD_RAW     207
#define MINIOS_SYS_VGA_MODE    208
#define MINIOS_SYS_PCSPK_INIT  209
#define MINIOS_SYS_PCSPK_TONE  210
#define MINIOS_SYS_DOOM_FRAME  211
#define MINIOS_SYS_RTC         212
#define MINIOS_SYS_FB_INFO     213
#define MINIOS_SYS_PCSPK_VOL   214
#define MINIOS_SYS_SPAWN       215
#define MINIOS_SYS_LZ4_COMPRESS   216
#define MINIOS_SYS_LZ4_DECOMPRESS 217
#define MINIOS_SYS_MOUSE       219
#define MINIOS_SYS_NK_FRAME    220
#define MINIOS_SYS_SB16_OPEN   221
#define MINIOS_SYS_SB16_SUBMIT 222
#define MINIOS_SYS_GFX_SET_TITLE 223
#define MINIOS_SYS_SB16_PUMP   224
#define MINIOS_SYS_SB16_STREAM_OPEN   229
#define MINIOS_SYS_SB16_STREAM_CLOSE  230
#define MINIOS_SYS_SB16_STREAM_SUBMIT 232
#define MINIOS_SYS_SB16_STREAM_VOLUME 233
#define MINIOS_SYS_THREAD_SPAWN  225

#define MINIOS_SYS_CLONE             300

/* --- Compatibility aliases for runtime bindings --- */
#define SYS_TIME_MS    MINIOS_SYS_TIME
#define SYS_PALETTE    MINIOS_SYS_PALETTE
#define SYS_PCSPK_INIT MINIOS_SYS_PCSPK_INIT
#define SYS_PCSPK_TONE MINIOS_SYS_PCSPK_TONE
#define SYS_RTC        MINIOS_SYS_RTC
#define SYS_FB_INFO    MINIOS_SYS_FB_INFO
#define SYS_PCSPK_VOL  MINIOS_SYS_PCSPK_VOL
#define SYS_SPAWN      MINIOS_SYS_SPAWN
#define SYS_TIME       MINIOS_SYS_TIME
#define SYS_WRITE      MINIOS_SYS_WRITE

/* --- Error codes --- */
#define MINIOS_EABI_MISMATCH (-100)

#endif
