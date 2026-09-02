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
 */

/* ---- User window geometry ----
 *
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
 */
#define MINIOS_USER_LOAD_BASE   0x00400000UL
#define MINIOS_USER_LOAD_END    0x0C000000UL
#define MINIOS_USER_STACK_SIZE  (1024UL * 1024)
#define MINIOS_USER_STACK_TOP   MINIOS_USER_LOAD_END
#define MINIOS_USER_STACK_BASE  (MINIOS_USER_STACK_TOP - MINIOS_USER_STACK_SIZE)
#define MINIOS_USER_BRK_END     MINIOS_USER_STACK_BASE

/* ---- Graphics back-buffers (kernel-mapped into user window) ----
 *
 * The kernel allocates these from the kernel heap and maps them into the user
 * window via the 4 KB page tables at boot (mm_setup_protections).  A ring-3
 * program writes to these addresses and calls the corresponding SYS_*_FRAME
 * syscall; the kernel composites the buffer onto the desktop.
 *
 * All three sit in the reserved tail above DOOM_BACKBUF_ADDR (the brk cap),
 * so a growing heap or mmap region can never reach them. */
#define MINIOS_DOOM_BACKBUF_ADDR  0x0B000000UL
#define MINIOS_DOOM_W             320
#define MINIOS_DOOM_H             200
#define MINIOS_FB_ADDR            0x0B200000UL
#define MINIOS_NK_BACKBUF_ADDR    0x0B400000UL
#define MINIOS_NK_W               800
#define MINIOS_NK_H               360

/* ---- Kernel heap (supervisor only) ---- */
#define MINIOS_HEAP_BASE  0x0C000000UL
#define MINIOS_HEAP_SIZE  (192UL * 1024 * 1024)

/* ---- Syscall numbers for ring-3 programs ---- */
#define MINIOS_SYS_TIME      204
#define MINIOS_SYS_KBD       205
#define MINIOS_SYS_PALETTE   206
#define MINIOS_SYS_KBD_RAW   207
#define MINIOS_SYS_VGA_MODE  208
#define MINIOS_SYS_PCSPK_INIT 209
#define MINIOS_SYS_PCSPK_TONE 210
#define MINIOS_SYS_DOOM_FRAME 211
#define MINIOS_SYS_RTC       212
#define MINIOS_SYS_FB_INFO   213
#define MINIOS_SYS_PCSPK_VOL 214
#define MINIOS_SYS_SPAWN     215
#define MINIOS_SYS_LZ4_COMPRESS   216
#define MINIOS_SYS_LZ4_DECOMPRESS 217
#define MINIOS_SYS_MOUSE     219
#define MINIOS_SYS_NK_FRAME  220
#define MINIOS_SYS_SB16_OPEN 221
#define MINIOS_SYS_SB16_SUBMIT 222
#define MINIOS_SYS_GFX_SET_TITLE 223

/* ---- Framebuffer geometry (queried via SYS_FB_INFO) ---- */
#define MINIOS_FB_WIDTH_MAX  256
#define MINIOS_FB_HEIGHT_MAX 128

#endif
