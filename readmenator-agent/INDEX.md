# Index

| File | Purpose | Subsystem | Symbols |
|------|---------|-----------|---------|
| `ap_stub.h` | generated from ap_stub.bin - do not edit | root | 0 |
| `app.py` | _*_ coding: utf8 _*_ | root | 0 |
| `arch/x86/ap_entry.S` | ap_entry.S - SMP application-processor bootstrap stub. | x86 | 9 |
| `arch/x86/boot/bootdefs.h` | bootdefs.h - centralized configuration for the MiniOS two-stage boot path. | boot | 128 |
| `arch/x86/boot/stage1.S` | stage1.S - MiniOS boot sector. | boot | 11 |
| `arch/x86/boot/stage2.S` | stage2.S - MiniOS second-stage loader. | boot | 39 |
| `arch/x86/ctx_sw.S` | - | x86 | 2 |
| `arch/x86/isr_stubs.S` | - | x86 | 24 |
| `arch/x86/msr.h` | ifndef ARCH_X86_MSR_H define ARCH_X86_MSR_H  Model-Specific Register access for  | x86 | 8 |
| `audio.h` | ifndef AUDIO_H define AUDIO_H  Unified audio API for MiniOS. | root | 5 |
| `block.h` | ifndef BLOCK_H define BLOCK_H  Block device abstraction for MiniFS. Maps 4096-by | root | 4 |
| `bootloader.c` | - | root | 2 |
| `desktop_icons.h` | desktop_icons.h -- embedded icon pixel data for desktop shortcuts. | root | 3 |
| `desktop_shortcuts.h` | desktop_shortcuts.h -- configurable desktop icon shortcuts. | root | 13 |
| `drivers/block.c` | Block device layer for MiniFS. | drivers | 12 |
| `drivers/ide.c` | IDE/ATA PIO driver for MiniOS. | drivers | 14 |
| `drivers/kbd.c` | include "kernel.h" include "vga_fb.h" include "kbd.h"  ========================= | drivers | 17 |
| `drivers/kbd.h` | ifndef KBD_H define KBD_H | drivers | 1 |
| `drivers/pcspk.c` | include "kernel.h" include "pcspk.h"  PC speaker driver with a software master v | drivers | 14 |
| `drivers/rtc.c` | include "kernel.h" include "rtc.h"  CMOS RTC time-of-day reader. The desktop clo | drivers | 19 |
| `drivers/sb16.c` | include "kernel.h" include "sb16.h"  Sound Blaster 16 DMA audio driver. | drivers | 52 |
| `editor.h` | ifndef EDITOR_H define EDITOR_H  editor.h -- the built-in line editor contract. | root | 1 |
| `fs/kfile.c` | include "kernel.h" include "minifs.h"  ========================================= | fs | 16 |
| `fs/minifs.c` | MiniFS: minimal Unix-like filesystem for MiniOS. | fs | 53 |
| `fs/ramdisk.c` | include "kernel.h"  ============================================================ | fs | 18 |
| `fs/vfs.c` | include "kernel.h" include "minifs.h"  ========================================= | fs | 23 |
| `fs/zip.c` | zip.c — the unzip/zip shell builtins over the miniz zip library. | fs | 7 |
| `gen_minifs.py` | - | root | 0 |
| `ide.h` | ifndef IDE_H define IDE_H  IDE/ATA PIO driver for MiniOS. | root | 27 |
| `install.sh` | - | root | 0 |
| `kernel.c` | include "kernel.h" include "net.h" include "tls.h" include "bootdefs.h" include  | root | 31 |
| `kernel.h` | ifndef KERNEL_H define KERNEL_H  define EFAULT  (-14)  The user-window memory la | root | 64 |
| `kernel/cvm_host.c` | - | kernel | 45 |
| `kernel/editor.c` | include "kernel.h" include "shell.h" include "editor.h"  ======================= | kernel | 20 |
| `kernel/exec.c` | exec.c - Process execution: setjmp/longjmp, k_exec_user, k_run_rel, kexit. | kernel | 8 |
| `kernel/klog.c` | klog.c - Structured kernel logging with levels and subsystems. | kernel | 6 |
| `kernel/loader.c` | include "kernel.h" include "vga_fb.h"  ========================================= | kernel | 30 |
| `kernel/lz4_kernel.c` | include "kernel.h" include "lz4_kernel.h"  define HASH_BITS 12 define HASH_SIZE  | kernel | 9 |
| `kernel/mm.c` | include "kernel.h" include "sched.h"  ========================================== | kernel | 6 |
| `kernel/mm/paging.c` | paging.c - Page table management for the user window and per-process KPTI. | mm | 8 |
| `kernel/mm/swap.c` | swap.c - Swap-out/swap-in for the user window (LZ4-compressed disk swap). | mm | 8 |
| `kernel/printf.c` | include "kernel.h"  ============================================================ | kernel | 11 |
| `kernel/redirect.c` | include "kernel.h"  ============================================================ | kernel | 3 |
| `kernel/sched.c` | - | kernel | 32 |
| `kernel/scrollback.c` | scrollback.c - Console scrollback ring buffer. | kernel | 7 |
| `kernel/serial.c` | include "kernel.h"  serial.c -- COM1 16550 UART driver. | kernel | 8 |
| `kernel/shell.c` | include "kernel.h" include "net.h" include "minifs.h" include "sched.h" include  | kernel | 60 |
| `kernel/string.c` | include "kernel.h"  string.c -- Kernel string and memory functions. | kernel | 13 |
| `kernel/symtab.c` | include "kernel.h"  ============================================================ | kernel | 7 |
| `kernel/syscalls.c` | syscalls.c - Linux x86-64 syscall dispatcher and SYS_SPAWN. | kernel | 45 |
| `kernel/time.c` | include "kernel.h"  ============================================================ | kernel | 3 |
| `kernel/vga_fb.c` | - | kernel | 71 |
| `lz4_kernel.h` | ifndef LZ4_KERNEL_H define LZ4_KERNEL_H | root | 1 |
| `mcp/__init__.py` | - | mcp | 0 |
| `mcp/mcp_dbg_driver.py` | - | mcp | 6 |
| `mcp/mcp_dogfood.py` | - | mcp | 6 |
| `mcp/minios_addons.py` | - | mcp | 16 |
| `mcp/minios_mcp.py` | - | mcp | 50 |
| `mcp/mutate_mcp.sh` | Mutation testing for the MiniOS MCP bridge. Every mutant is injected into a priv | mcp | 1 |
| `mcp/test_minios_mcp.py` | - | mcp | 99 |
| `minifs.h` | ifndef MINIFS_H define MINIFS_H  MiniFS: a minimal Unix-like filesystem for Mini | root | 31 |
| `minifs_dump.py` | - | root | 12 |
| `minifs_fsck.py` | - | root | 14 |
| `mkfs.minifs.py` | - | root | 20 |
| `mkramdisk.py` | - | root | 2 |
| `mkroots.sh` | mkroots.sh - regenerate tls_roots.h from the DER files in tls_roots_src/.  Prove | root | 0 |
| `mutate.sh` | Mutation testing for MiniOS.  Each mutation is applied to the source in place, t | root | 5 |
| `net.h` | ifndef NET_H define NET_H  ========== Fixed slirp configuration (QEMU -nic user) | root | 34 |
| `net/net.c` | MiniOS network stack: rtl8139 under QEMU slirp user networking. | net | 55 |
| `net/rtl8139.c` | include "kernel.h" include "net.h" include "rtl8139.h" | net | 35 |
| `net/rtl8139.h` | ifndef RTL8139_H define RTL8139_H | net | 1 |
| `net/tls.c` | tls.c - TLS 1.2 client sessions for MiniOS. | net | 26 |
| `net/tls_crypto.c` | tls_crypto.c - the crypto behind the kernel TLS 1.2 client. | net | 76 |
| `net/tls_x509.c` | tls_x509.c - minimal X.509 DER parsing and chain verification. | net | 23 |
| `pcspk.h` | ifndef PCSPK_H define PCSPK_H  define PCSPK_VOL_MIN     0 define PCSPK_VOL_MAX   | root | 4 |
| `progs/asm/aes.s` | - | asm | 28 |
| `progs/asm/cp.s` | - | asm | 2 |
| `progs/asm/fib.s` | - | asm | 3 |
| `progs/asm/freedom.s` | - | asm | 91 |
| `progs/asm/http.s` | - | asm | 3 |
| `progs/asm/json.s` | - | asm | 32 |
| `progs/asm/ldhello.s` | - | asm | 2 |
| `progs/asm/lz4.s` | - | asm | 7 |
| `progs/asm/lzss.s` | - | asm | 29 |
| `progs/asm/w1.s` | - | asm | 2 |
| `progs/doomgeneric/am_map.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 82 |
| `progs/doomgeneric/am_map.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 4 |
| `progs/doomgeneric/config.h` | config.hin.  Generated from configure.ac by autoheader. | doomgeneric | 16 |
| `progs/doomgeneric/d_englsh.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 286 |
| `progs/doomgeneric/d_event.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 3 |
| `progs/doomgeneric/d_event.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/d_items.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 0 |
| `progs/doomgeneric/d_items.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/d_iwad.c` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 26 |
| `progs/doomgeneric/d_iwad.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 5 |
| `progs/doomgeneric/d_loop.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 17 |
| `progs/doomgeneric/d_loop.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/d_main.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 21 |
| `progs/doomgeneric/d_main.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/d_mode.c` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 6 |
| `progs/doomgeneric/d_mode.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/d_net.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 7 |
| `progs/doomgeneric/d_player.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 2 |
| `progs/doomgeneric/d_textur.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/d_think.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 2 |
| `progs/doomgeneric/d_ticcmd.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software C | doomgeneric | 1 |
| `progs/doomgeneric/deh_main.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 3 |
| `progs/doomgeneric/deh_misc.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 33 |
| `progs/doomgeneric/deh_str.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 6 |
| `progs/doomgeneric/doom.h` | - | doomgeneric | 1 |
| `progs/doomgeneric/doomdata.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 11 |
| `progs/doomgeneric/doomdef.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 0 |
| `progs/doomgeneric/doomdef.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 9 |
| `progs/doomgeneric/doomfeatures.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 2 |
| `progs/doomgeneric/doomgeneric.c` | include "doomgeneric.h" | doomgeneric | 1 |
| `progs/doomgeneric/doomgeneric.h` | ifndef DOOM_GENERIC define DOOM_GENERIC  include <stdlib.h> include <stdint.h>   | doomgeneric | 3 |
| `progs/doomgeneric/doomgeneric_minios.c` | doomgeneric_minios.c - MiniOS platform layer for doomgeneric. | doomgeneric | 22 |
| `progs/doomgeneric/doomgeneric_sdl.c` | doomgeneric for soso os  include "doomkeys.h" include "m_argv.h" include "doomge | doomgeneric | 10 |
| `progs/doomgeneric/doomgeneric_soso.c` | doomgeneric for soso os  include "doomkeys.h" include "m_argv.h" include "doomge | doomgeneric | 12 |
| `progs/doomgeneric/doomgeneric_sosox.c` | doomgeneric for soso os (nano-x version) TODO: get keys from X, not using direct | doomgeneric | 12 |
| `progs/doomgeneric/doomgeneric_win.c` | include "doomkeys.h"  include "doomgeneric.h"  include <stdio.h>  include <Windo | doomgeneric | 10 |
| `progs/doomgeneric/doomgeneric_xlib.c` | include "doomkeys.h"  include "doomgeneric.h"  include <ctype.h> include <stdio. | doomgeneric | 9 |
| `progs/doomgeneric/doomkeys.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 59 |
| `progs/doomgeneric/doomstat.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 0 |
| `progs/doomgeneric/doomstat.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 3 |
| `progs/doomgeneric/doomtype.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 12 |
| `progs/doomgeneric/dstrings.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 0 |
| `progs/doomgeneric/dstrings.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 3 |
| `progs/doomgeneric/dummy.c` | - | doomgeneric | 1 |
| `progs/doomgeneric/f_finale.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 15 |
| `progs/doomgeneric/f_finale.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/f_wipe.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 10 |
| `progs/doomgeneric/f_wipe.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/g_game.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 48 |
| `progs/doomgeneric/g_game.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/gusconf.c` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 9 |
| `progs/doomgeneric/gusconf.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 1 |
| `progs/doomgeneric/hu_lib.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 21 |
| `progs/doomgeneric/hu_lib.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 4 |
| `progs/doomgeneric/hu_stuff.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 23 |
| `progs/doomgeneric/hu_stuff.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 10 |
| `progs/doomgeneric/i_cdmus.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software   | doomgeneric | 9 |
| `progs/doomgeneric/i_cdmus.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software   | doomgeneric | 8 |
| `progs/doomgeneric/i_endoom.c` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 3 |
| `progs/doomgeneric/i_endoom.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/i_input.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 5 |
| `progs/doomgeneric/i_joystick.c` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 10 |
| `progs/doomgeneric/i_joystick.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 14 |
| `progs/doomgeneric/i_main.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/i_minios_sound.c` | include <stdio.h> include <stdlib.h> include <string.h> include "doomtype.h" inc | doomgeneric | 38 |
| `progs/doomgeneric/i_scale.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 39 |
| `progs/doomgeneric/i_scale.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/i_sound.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 24 |
| `progs/doomgeneric/i_sound.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 2 |
| `progs/doomgeneric/i_swap.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 8 |
| `progs/doomgeneric/i_system.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 20 |
| `progs/doomgeneric/i_system.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/i_timer.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 6 |
| `progs/doomgeneric/i_timer.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 2 |
| `progs/doomgeneric/i_video.c` | Emacs style mode select   -*- C++ -*- ------------------------------------------ | doomgeneric | 27 |
| `progs/doomgeneric/i_video.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 6 |
| `progs/doomgeneric/icon.c` | - | doomgeneric | 0 |
| `progs/doomgeneric/info.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 0 |
| `progs/doomgeneric/info.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/m_argv.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 7 |
| `progs/doomgeneric/m_argv.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/m_bbox.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 2 |
| `progs/doomgeneric/m_bbox.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/m_cheat.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 2 |
| `progs/doomgeneric/m_cheat.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 4 |
| `progs/doomgeneric/m_config.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software C | doomgeneric | 24 |
| `progs/doomgeneric/m_config.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/m_controls.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software C | doomgeneric | 9 |
| `progs/doomgeneric/m_controls.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software C | doomgeneric | 1 |
| `progs/doomgeneric/m_fixed.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 2 |
| `progs/doomgeneric/m_fixed.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 3 |
| `progs/doomgeneric/m_menu.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 60 |
| `progs/doomgeneric/m_menu.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/m_misc.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software C | doomgeneric | 22 |
| `progs/doomgeneric/m_misc.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/m_random.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 3 |
| `progs/doomgeneric/m_random.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/memio.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 9 |
| `progs/doomgeneric/memio.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/net_client.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 1 |
| `progs/doomgeneric/net_dedicated.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 1 |
| `progs/doomgeneric/net_defs.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 18 |
| `progs/doomgeneric/net_gui.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 1 |
| `progs/doomgeneric/net_io.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 1 |
| `progs/doomgeneric/net_loop.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 1 |
| `progs/doomgeneric/net_packet.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 1 |
| `progs/doomgeneric/net_query.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 1 |
| `progs/doomgeneric/net_sdl.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 1 |
| `progs/doomgeneric/net_server.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 1 |
| `progs/doomgeneric/p_ceilng.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 6 |
| `progs/doomgeneric/p_doors.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 10 |
| `progs/doomgeneric/p_enemy.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 67 |
| `progs/doomgeneric/p_floor.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 4 |
| `progs/doomgeneric/p_inter.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 10 |
| `progs/doomgeneric/p_inter.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/p_lights.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 11 |
| `progs/doomgeneric/p_local.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 27 |
| `progs/doomgeneric/p_map.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard, An | doomgeneric | 22 |
| `progs/doomgeneric/p_maputl.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard Cop | doomgeneric | 17 |
| `progs/doomgeneric/p_mobj.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 19 |
| `progs/doomgeneric/p_mobj.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 2 |
| `progs/doomgeneric/p_plats.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 6 |
| `progs/doomgeneric/p_pspr.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 35 |
| `progs/doomgeneric/p_pspr.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 3 |
| `progs/doomgeneric/p_saveg.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 58 |
| `progs/doomgeneric/p_saveg.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 2 |
| `progs/doomgeneric/p_setup.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 16 |
| `progs/doomgeneric/p_setup.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/p_sight.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 5 |
| `progs/doomgeneric/p_spec.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 24 |
| `progs/doomgeneric/p_spec.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 22 |
| `progs/doomgeneric/p_switch.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 4 |
| `progs/doomgeneric/p_telept.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/p_tick.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 6 |
| `progs/doomgeneric/p_tick.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/p_user.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 8 |
| `progs/doomgeneric/r_bsp.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 9 |
| `progs/doomgeneric/r_bsp.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/r_data.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 15 |
| `progs/doomgeneric/r_data.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/r_defs.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 11 |
| `progs/doomgeneric/r_draw.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 20 |
| `progs/doomgeneric/r_draw.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/r_local.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/r_main.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 19 |
| `progs/doomgeneric/r_main.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 8 |
| `progs/doomgeneric/r_plane.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 9 |
| `progs/doomgeneric/r_plane.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/r_segs.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 5 |
| `progs/doomgeneric/r_segs.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/r_sky.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/r_sky.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 3 |
| `progs/doomgeneric/r_state.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/r_things.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 16 |
| `progs/doomgeneric/r_things.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 2 |
| `progs/doomgeneric/s_sound.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 24 |
| `progs/doomgeneric/s_sound.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/sha1.c` | sha1.c - SHA1 hash function | doomgeneric | 19 |
| `progs/doomgeneric/sha1.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 2 |
| `progs/doomgeneric/sounds.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 3 |
| `progs/doomgeneric/sounds.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/st_lib.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 10 |
| `progs/doomgeneric/st_lib.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/st_stuff.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 137 |
| `progs/doomgeneric/st_stuff.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 4 |
| `progs/doomgeneric/statdump.c` | - | doomgeneric | 11 |
| `progs/doomgeneric/statdump.h` | - | doomgeneric | 1 |
| `progs/doomgeneric/tables.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/tables.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software C | doomgeneric | 15 |
| `progs/doomgeneric/v_patch.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/v_video.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software C | doomgeneric | 30 |
| `progs/doomgeneric/v_video.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 2 |
| `progs/doomgeneric/w_checksum.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 3 |
| `progs/doomgeneric/w_checksum.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/w_file.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 3 |
| `progs/doomgeneric/w_file.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 2 |
| `progs/doomgeneric/w_file_stdc.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 3 |
| `progs/doomgeneric/w_main.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/w_main.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 1 |
| `progs/doomgeneric/w_merge.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 3 |
| `progs/doomgeneric/w_wad.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 15 |
| `progs/doomgeneric/w_wad.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 2 |
| `progs/doomgeneric/wi_stuff.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 66 |
| `progs/doomgeneric/wi_stuff.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/z_zone.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 16 |
| `progs/doomgeneric/z_zone.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 2 |
| `progs/lua/lua_main.c` | - | lua | 6 |
| `progs/lua/minios.c` | - | lua | 17 |
| `progs/micropython/variants/minios/lib/__init__.py` | MiniOS frozen library package. | lib | 0 |
| `progs/micropython/variants/minios/lib/hello.py` | hello.py -- frozen demo: runs at import time as a smoke test. | lib | 0 |
| `progs/micropython/variants/minios/manifest.py` | manifest.py -- frozen modules for the MiniOS MicroPython variant. Scripts listed | minios | 0 |
| `progs/micropython/variants/minios/minios_module.c` | - | minios | 15 |
| `progs/micropython/variants/minios/mpconfigvariant.h` | - | minios | 38 |
| `progs/minios_abi.h` | ifndef MINIOS_ABI_H define MINIOS_ABI_H  minios_abi.h -- Single source of truth  | misc | 109 |
| `progs/nuklear/cvm_emit.c` | cvm_emit.c — node-graph to CVM bytecode compiler. | nuklear | 30 |
| `progs/nuklear/cvm_emit.h` | ifndef CVM_EMIT_H define CVM_EMIT_H  cvm_emit.h — node-graph compiler for CVM (c | nuklear | 2 |
| `progs/nuklear/node_editor.c` | node_editor.c — visual node editor that compiles to CVM bytecode. | nuklear | 22 |
| `progs/nuklear/nuklear_minios.c` | nuklear_minios.c — MiniOS platform layer for Nuklear. | nuklear | 30 |
| `progs/nuklear/nuklear_minios.h` | ifndef NUKLEAR_MINIOS_H define NUKLEAR_MINIOS_H  nuklear_minios.h — MiniOS platf | nuklear | 4 |
| `progs/piano/piano.c` | piano.c — a Nuklear piano that plays FM sound through the SB16 driver. | misc | 48 |
| `progs/pokemon/fetch.sh` | fetch.sh - clone the gb-recompiled tool into progs/pokemon/upstream.  The upstre | pokemon | 0 |
| `progs/pokemon/minios_stubs/SDL.h` | SDL.h stub for MiniOS cross-compilation | misc | 5 |
| `progs/pokemon/platform_minios.c` | - | pokemon | 61 |
| `progs/quake2generic/q2generic_minios.c` | q2generic_minios.c - MiniOS platform layer for quake2generic. | misc | 28 |
| `progs/src/aes.c` | aes.c - command path AES-256-CTR encryption tools: aes and unaes. | src | 41 |
| `progs/src/audio.c` | include "minios_abi.h" | src | 17 |
| `progs/src/cp.c` | - | src | 3 |
| `progs/src/cpl.c` | Ring-3 privilege probe. Reads the CS selector at runtime and exits with | src | 3 |
| `progs/src/fib.c` | - | src | 2 |
| `progs/src/freedom.c` | freedom - a headless text browser for MiniOS. | src | 41 |
| `progs/src/ftest.c` | Exercises the kernel libc surface used by loaded .o programs: fprintf to stdout/ | src | 1 |
| `progs/src/hello.c` | MiniOS test program — compiled as relocatable .o, loaded by kernel ELF loader | src | 1 |
| `progs/src/hello.py` | - | src | 0 |
| `progs/src/http.c` | Minimal HTTP/1.0 GET through the Linux socket syscalls. | src | 2 |
| `progs/src/json.c` | json.c - command path JSON tool: validate, pretty-print and query. | src | 28 |
| `progs/src/kmem.c` | Kernel-pointer rejection probe. Passes a kernel-heap address (0x2000000, | src | 3 |
| `progs/src/ldhello.c` | - | src | 1 |
| `progs/src/lxhello.c` | - | src | 7 |
| `progs/src/lz4.c` | lz4.c - command path LZ4 (de)compression tools: lz4 and unlz4. | src | 12 |
| `progs/src/lzss.c` | lzss.c - command path LZSS (de)compression tools: lzss and unlzss. | src | 36 |
| `progs/src/mmreuse.c` | mmap/munmap reclaim stress test.  Repeatedly maps and unmaps a large | src | 4 |
| `progs/src/nx.c` | NX probe. Under the isolation contract every user page starts | src | 3 |
| `progs/src/opl3.c` | - | src | 17 |
| `progs/src/sbtone.c` | sbtone.c — headless SB16 diagnostic (ring-3, no GUI). | src | 8 |
| `progs/src/shell.py` | shell.py -- pybash: a Python shell layer on top of MiniOS's C shell.  The C shel | src | 3 |
| `progs/src/test.c` | - | src | 2 |
| `progs/src/test.lua` | - | src | 20 |
| `progs/src/test.py` | test.py -- in-OS test suite for MiniOS, driven by MicroPython.  Tests every avai | src | 20 |
| `progs/src/test_all.sh` | test_all.sh -- comprehensive non-interactive test suite for MiniOS.  Run with:   | src | 0 |
| `progs/src/w1.c` | - | src | 1 |
| `progs/topogpt3/topogpt3.c` | - | misc | 99 |
| `qga.c` | MiniOS QEMU guest agent (QGA). | root | 26 |
| `qga.h` | ifndef QGA_H define QGA_H  ========== QEMU guest agent channel (COM2, ISA 16550) | root | 27 |
| `rtc.h` | ifndef RTC_H define RTC_H | root | 1 |
| `sb16.h` | ifndef SB16_H define SB16_H  Sound Blaster 16 DMA audio driver contract. | root | 10 |
| `sched.h` | ifndef SCHED_H define SCHED_H  include <stdint.h> include "spinlock.h"  ---- Pro | root | 16 |
| `shell.h` | ifndef SHELL_H define SHELL_H  shell.h -- shared shell constants and the line re | root | 3 |
| `smp.c` | include "kernel.h" include "bootdefs.h" include "smp.h" include "sched.h" includ | root | 30 |
| `smp.h` | ifndef SMP_H define SMP_H  include "spinlock.h"  SMP bring-up: wake the applicat | root | 1 |
| `spinlock.h` | ifndef SPINLOCK_H define SPINLOCK_H  spinlock.h -- Lightweight spinlock for Mini | root | 8 |
| `test_bdd.sh` | BDD suite for MiniOS: boots the disk image in QEMU and drives the shell over the | root | 10 |
| `test_http_server.py` | - | root | 3 |
| `tests/host_aes.sh` | host_aes.sh - host-side verification for the AES-256-CTR command tools.  The min | tests | 3 |
| `tests/host_codecs.sh` | host_codecs.sh - reusable host-side verification for the in-OS codec tools.  The | tests | 5 |
| `tests/test_vma.c` | Host-side unit test for the VMA red-black tree (vma.c). | tests | 8 |
| `tls.h` | ifndef TLS_H define TLS_H  ========== TLS 1.2 client (RFC 5246) ========== | root | 42 |
| `tls_port.h` | ifndef TLS_PORT_H define TLS_PORT_H  Portability shim between the MiniOS kernel  | root | 27 |
| `tls_roots.h` | tls_roots.h - embedded CA roots (DER), generated by mkroots.sh. | root | 0 |
| `tls_test.c` | tls_test.c - host-side tests for the kernel TLS stack. | root | 23 |
| `tls_test.py` | - | root | 16 |
| `tls_test_roots.h` | tls_test_roots.h - generated by tls_test.py; never built into the kernel. The te | root | 0 |
| `tools/boot_run.sh` | boot_run.sh -- boot the MiniOS image in QEMU and drive the shell over the serial | tools | 0 |
| `tools/check_cohesion.py` | - | tools | 4 |
| `tools/check_complexity.py` | - | tools | 3 |
| `tools/check_kb_sync.py` | - | tools | 2 |
| `tools/check_surprising.py` | - | tools | 5 |
| `tools/extract_shell.py` | - | tools | 0 |
| `tools/gdb_repro.py` | - | tools | 4 |
| `tools/gen_icons.py` | - | tools | 3 |
| `tools/gen_zip_fixtures.py` | - | tools | 2 |
| `tools/minios_cli.py` | - | tools | 6 |
| `tools/minios_gui.py` | - | tools | 9 |
| `tools/mkpak1.py` | - | tools | 1 |
| `tools/qga_client.py` | - | tools | 4 |
| `tools/qga_test.sh` | Quick standalone smoke test for the QEMU guest agent: boots os.img once with the | tools | 3 |
| `tools/repro_gui.py` | - | tools | 10 |
| `tools/test_codecs.sh` | test_codecs.sh -- exercise the lzss/lz4/aes command-pair tools inside the OS.  T | tools | 0 |
| `tools/test_sb16.sh` | test_sb16.sh — targeted BDD harness for the SB16 audio path.  Boots the disk ima | tools | 1 |
| `vga_fb.h` | ifndef VGA_FB_H define VGA_FB_H  include <stdint.h> include "minios_abi.h"  Fram | root | 51 |
| `vma.c` | include "vma.h" | root | 11 |
| `vma.h` | ifndef VMA_H define VMA_H | root | 3 |
| `zip.h` | ifndef ZIP_H define ZIP_H  zip.h — MiniOS integration API for the miniz zip libr | root | 1 |
