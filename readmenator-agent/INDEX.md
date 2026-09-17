# Index

| File | Purpose | Subsystem | Symbols |
|------|---------|-----------|---------|
| `arch/x86/ap_entry.S` | ap_entry.S - SMP application-processor bootstrap stub. | - | 9 |
| `arch/x86/boot/stage1.S` | stage1.S - MiniOS boot sector. | boot | 11 |
| `arch/x86/boot/stage2.S` | stage2.S - MiniOS second-stage loader. | boot | 40 |
| `arch/x86/ctx_sw.S` | - | - | 6 |
| `arch/x86/isr_stubs.S` | - | - | 24 |
| `bootloader.c` | - | root | 2 |
| `drivers/block.c` | Block device layer for MiniFS. | - | 14 |
| `drivers/driver.c` | driver.c -- Device registry for the Strategy-pattern driver layer. | - | 8 |
| `drivers/ide.c` | IDE/ATA PIO driver for MiniOS. | - | 19 |
| `drivers/kbd.c` | ================================================================ | - | 34 |
| `drivers/mouse.c` | Docstring: PS/2 mouse device driver (drivers/mouse.c). | - | 8 |
| `drivers/pcspk.c` | PC speaker driver with a software master volume. The speaker has no | - | 18 |
| `drivers/rtc.c` | CMOS RTC time-of-day reader. The desktop clock and the shell `date` builtin | - | 25 |
| `drivers/sb16.c` | Sound Blaster 16 DMA audio driver. | - | 64 |
| `fs/kfile.c` | ================================================================ | fs | 20 |
| `fs/minifs.c` | MiniFS: minimal Unix-like filesystem for MiniOS. | fs | 61 |
| `fs/ramdisk.c` | ================================================================ | fs | 19 |
| `fs/vfs.c` | ================================================================ | fs | 30 |
| `fs/zip.c` | zip.c — the unzip/zip shell builtins over the miniz zip library. | fs | 10 |
| `headers/abi.h` | Docstring: abi.h -- Boot-time ABI manifest gate contract. | headers | 10 |
| `headers/ap_stub.h` | generated from ap_stub.bin - do not edit | headers | 0 |
| `headers/arch/x86/boot/bootdefs.h` | bootdefs.h - centralized configuration for the MiniOS two-stage boot path. | misc | 139 |
| `headers/arch/x86/hal_io.h` | Docstring: x86 port I/O hardware abstraction contract. | x86 | 52 |
| `headers/arch/x86/msr.h` | Model-Specific Register access for x86-64. | x86 | 9 |
| `headers/audio.h` | Unified audio API for MiniOS. | headers | 18 |
| `headers/batch.h` | Docstring: batch.h -- Batched synchronous syscall submission. | headers | 12 |
| `headers/block.h` | Block device abstraction for MiniFS. Maps 4096-byte logical blocks to 512-byte I | headers | 12 |
| `headers/desktop_icons.h` | desktop_icons.h -- embedded icon pixel data for desktop shortcuts. | headers | 3 |
| `headers/desktop_shortcuts.h` | desktop_shortcuts.h -- configurable desktop icon shortcuts. | headers | 20 |
| `headers/driver.h` | driver.h -- Strategy pattern for hardware drivers (thesis correction 2). | headers | 16 |
| `headers/drivers/kbd.h` | Keyboard layout: US qwerty (default) or Spanish (Spain) qwerty. Toggled from the | drivers | 23 |
| `headers/drivers/modifiers.h` | Docstring: Unified modifier tracking for cooked and raw paths. | drivers | 11 |
| `headers/drivers/mouse.h` | Docstring: mouse.h -- boundary of the PS/2 mouse device driver | drivers | 4 |
| `headers/editor.h` | editor.h -- the built-in line editor contract. | headers | 2 |
| `headers/futex.h` | Docstring: futex.h -- Fast userspace mutex sleep/wake contract. | headers | 17 |
| `headers/ide.h` | IDE/ATA PIO driver for MiniOS. | headers | 35 |
| `headers/kernel.h` | The user-window memory layout (load base, stack, brk cap, graphics | headers | 314 |
| `headers/kernel/console_in.h` | Docstring: console_in.h -- boundary of the console input device | kernel | 8 |
| `headers/kernel/vga_cursor.h` | Docstring: vga_cursor.h -- boundary of the pointer sprite layer | kernel | 9 |
| `headers/ktime.h` | ktime.h -- pure time-conversion helpers shared by the kernel clock | headers | 3 |
| `headers/lz4_kernel.h` | - | headers | 4 |
| `headers/minifetch.h` | Docstring: minifetch.h -- neofetch-style system screen contract. | headers | 2 |
| `headers/minifs.h` | MiniFS: a minimal Unix-like filesystem for MiniOS. | headers | 76 |
| `headers/net.h` | ========== Fixed slirp configuration (QEMU -nic user) ========== | headers | 59 |
| `headers/net/rtl8139.h` | - | misc | 8 |
| `headers/pcspk.h` | - | headers | 9 |
| `headers/percpu_rq.h` | Docstring: percpu_rq.h -- Per-CPU runqueues with work stealing. | headers | 14 |
| `headers/qga.h` | ========== QEMU guest agent channel (COM2, ISA 16550) ========== | headers | 29 |
| `headers/randmix.h` | randmix.h -- entropy mixer for getrandom (318). | headers | 2 |
| `headers/rcu.h` | Docstring: rcu.h -- Read-copy-update, lite epoch edition. | headers | 17 |
| `headers/rtc.h` | - | headers | 6 |
| `headers/sanitize.h` | Docstring: sanitize.h -- Single choke point for syscall argument checks. | headers | 5 |
| `headers/sb16.h` | Sound Blaster 16 DMA audio driver contract. | headers | 27 |
| `headers/sched.h` | ---- Process states ---- | headers | 101 |
| `headers/shell.h` | shell.h -- shared shell constants and the line reader/parser reused by | headers | 7 |
| `headers/smp.h` | SMP bring-up: wake the application processors (APs) via the LAPIC INIT/SIPI | headers | 11 |
| `headers/spawn.h` | Docstring: Scalar shared-window view saved across a child run. | headers | 9 |
| `headers/spinlock.h` | spinlock.h -- Lightweight spinlock for MiniOS kernel. | headers | 19 |
| `headers/sync.h` | sync.h -- Blocking synchronization primitives (roadmap Phase 3.1). | headers | 36 |
| `headers/syscalls_proc.h` | syscalls_proc.h -- process-management syscall handlers shared with the | headers | 15 |
| `headers/tick.h` | Docstring: Tick listener bus contract. | headers | 13 |
| `headers/tls.h` | ========== TLS 1.2 client (RFC 5246) ========== | headers | 73 |
| `headers/tls_port.h` | Portability shim between the MiniOS kernel and the host-side test | headers | 49 |
| `headers/tls_roots.h` | tls_roots.h - embedded CA roots (DER), generated by mkroots.sh. | headers | 0 |
| `headers/tls_test_roots.h` | tls_test_roots.h - generated by tls_test.py; never built into the kernel. The te | headers | 0 |
| `headers/vga_fb.h` | Framebuffer geometry. The boot loader probes VESA BIOS Extensions for a | headers | 125 |
| `headers/vma.h` | - | headers | 21 |
| `headers/wm_events.h` | Docstring: Window event contract for the MiniOS desktop. | headers | 39 |
| `headers/wm_focus.h` | Docstring: Focus manager contract for the MiniOS desktop. | headers | 5 |
| `headers/wm_geom.h` | Docstring: Window geometry contract for the MiniOS desktop. | headers | 11 |
| `headers/wm_layout.h` | Docstring: Unified layout contract for the MiniOS desktop. | headers | 16 |
| `headers/wm_notify.h` | Docstring: Focus event bus for the MiniOS desktop. | headers | 9 |
| `headers/wm_render.h` | Docstring: Render pipeline contract for the MiniOS desktop. | headers | 5 |
| `headers/wm_tiling.h` | Docstring: Tiling layout contract for the MiniOS desktop. | headers | 3 |
| `headers/wm_window.h` | Docstring: Unified window contract for the MiniOS desktop. | headers | 10 |
| `headers/zip.h` | zip.h — MiniOS integration API for the miniz zip library. | headers | 3 |
| `kernel.c` | kernel.c -- Mediator: boot orchestration and the syscall trampoline. | root | 20 |
| `kernel/abi.c` | Docstring: kernel/abi.c -- Boot-time ABI manifest gate. | - | 3 |
| `kernel/batch.c` | Docstring: kernel/batch.c -- Ordered batch executor. | - | 1 |
| `kernel/console.c` | console.c -- Execution-context output: text console, capture, libc names. | - | 24 |
| `kernel/console_in.c` | Docstring: Console input device (kernel/console_in.c). | - | 26 |
| `kernel/cvm_host.c` | - | - | 45 |
| `kernel/editor.c` | ================================================================ | - | 22 |
| `kernel/exec.c` | exec.c - Process execution: setjmp/longjmp, k_exec_user, k_run_rel, kexit. | - | 10 |
| `kernel/futex.c` | Docstring: kernel/futex.c -- Kernel side of the futex contract. | - | 7 |
| `kernel/klog.c` | klog.c - Structured kernel logging with levels and subsystems. | - | 6 |
| `kernel/loader.c` | ================================================================ | - | 37 |
| `kernel/lz4_kernel.c` | - | - | 10 |
| `kernel/minifetch.c` | Docstring: kernel/minifetch.c -- neofetch-style system screen. | - | 6 |
| `kernel/mm.c` | ================================================================ | - | 6 |
| `kernel/mm/paging.c` | paging.c - Page table management for the user window and per-process KPTI. | mm | 14 |
| `kernel/mm/swap.c` | swap.c - Swap-out/swap-in for the user window (LZ4-compressed disk swap). | mm | 8 |
| `kernel/percpu_rq.c` | Docstring: kernel/percpu_rq.c -- Per-CPU runqueue hints and stealing. | - | 9 |
| `kernel/printf.c` | ================================================================ | - | 10 |
| `kernel/rcu.c` | Docstring: kernel/rcu.c -- Epoch grace periods over scheduler ticks. | - | 14 |
| `kernel/redirect.c` | ================================================================ | - | 3 |
| `kernel/sched.c` | - | - | 92 |
| `kernel/scrollback.c` | scrollback.c - Console scrollback ring buffer. | - | 8 |
| `kernel/serial.c` | serial.c -- COM1 16550 UART driver. | - | 9 |
| `kernel/shell.c` | ================================================================ | - | 79 |
| `kernel/spawn.c` | Docstring: File-static VMA pool copy, stack-safe by construction. | - | 9 |
| `kernel/string.c` | string.c -- Kernel string and memory functions. | - | 13 |
| `kernel/symtab.c` | ================================================================ | - | 7 |
| `kernel/sync.c` | sync.c -- Blocking synchronization primitives (roadmap Phase 3.1). | - | 26 |
| `kernel/syscalls.c` | syscalls.c - Linux x86-64 syscall dispatcher and SYS_SPAWN. | - | 104 |
| `kernel/syscalls_proc.c` | syscalls_proc.c - Process-management syscall handlers. | - | 14 |
| `kernel/tick.c` | Docstring: Tick listener bus implementation. | - | 9 |
| `kernel/time.c` | ================================================================ | - | 4 |
| `kernel/vga_cursor.c` | Docstring: Hardware pointer sprite layer (kernel/vga_cursor.c). | - | 13 |
| `kernel/vga_fb.c` | - | - | 150 |
| `mcp/__init__.py` | - | mcp | 0 |
| `mcp/mcp_dbg_driver.py` | Debug driver: boot MiniOS through the MCP bridge and run freedom. | mcp | 6 |
| `mcp/mcp_dogfood.py` | Dogfood: drive minios_mcp.py over stdio JSON-RPC and install the freedom addon f | mcp | 6 |
| `mcp/minios_addons.py` | MiniOS addon marketplace (lazyaddons-style).  Addons are YAML files that say whe | mcp | 16 |
| `mcp/minios_mcp.py` | MiniOS MCP bridge.  Exposes a running MiniOS instance as tools over the MCP stdi | mcp | 50 |
| `mcp/mutate_mcp.sh` | Mutation testing for the MiniOS MCP bridge. Every mutant is injected into a priv | mcp | 1 |
| `mcp/test_minios_mcp.py` | Unit and BDD suite for the MiniOS MCP bridge.  Unit tests exercise protocol disp | mcp | 104 |
| `net/net.c` | MiniOS network stack: rtl8139 under QEMU slirp user networking. | net | 56 |
| `net/rtl8139.c` | - | net | 31 |
| `net/tls.c` | tls.c - TLS 1.2 client sessions for MiniOS. | net | 27 |
| `net/tls_crypto.c` | tls_crypto.c - the crypto behind the kernel TLS 1.2 client. | net | 78 |
| `net/tls_x509.c` | tls_x509.c - minimal X.509 DER parsing and chain verification. | net | 23 |
| `progs/asm/aes.s` | - | asm | 28 |
| `progs/asm/cp.s` | - | asm | 2 |
| `progs/asm/fib.s` | - | asm | 3 |
| `progs/asm/freedom.s` | - | asm | 92 |
| `progs/asm/http.s` | - | asm | 3 |
| `progs/asm/json.s` | - | asm | 32 |
| `progs/asm/ldhello.s` | - | asm | 2 |
| `progs/asm/lz4.s` | - | asm | 7 |
| `progs/asm/lzss.s` | - | asm | 30 |
| `progs/asm/w1.s` | - | asm | 2 |
| `progs/doomedit/doomedit.c` | doomedit.c - tile map editor that builds playable Doom PWADs. | misc | 108 |
| `progs/doomgeneric/am_map.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 87 |
| `progs/doomgeneric/am_map.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 8 |
| `progs/doomgeneric/config.h` | config.hin.  Generated from configure.ac by autoheader. | doomgeneric | 16 |
| `progs/doomgeneric/d_englsh.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 286 |
| `progs/doomgeneric/d_event.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 3 |
| `progs/doomgeneric/d_event.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 4 |
| `progs/doomgeneric/d_items.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 0 |
| `progs/doomgeneric/d_items.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 3 |
| `progs/doomgeneric/d_iwad.c` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 27 |
| `progs/doomgeneric/d_iwad.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 14 |
| `progs/doomgeneric/d_loop.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 18 |
| `progs/doomgeneric/d_loop.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 10 |
| `progs/doomgeneric/d_main.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 29 |
| `progs/doomgeneric/d_main.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 8 |
| `progs/doomgeneric/d_mode.c` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 6 |
| `progs/doomgeneric/d_mode.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 3 |
| `progs/doomgeneric/d_net.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 8 |
| `progs/doomgeneric/d_player.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 5 |
| `progs/doomgeneric/d_textur.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 2 |
| `progs/doomgeneric/d_think.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 4 |
| `progs/doomgeneric/d_ticcmd.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software C | doomgeneric | 2 |
| `progs/doomgeneric/deh_main.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 12 |
| `progs/doomgeneric/deh_misc.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 49 |
| `progs/doomgeneric/deh_str.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 11 |
| `progs/doomgeneric/doom.h` | - | doomgeneric | 2 |
| `progs/doomgeneric/doomdata.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 11 |
| `progs/doomgeneric/doomdef.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 0 |
| `progs/doomgeneric/doomdef.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 9 |
| `progs/doomgeneric/doomfeatures.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 2 |
| `progs/doomgeneric/doomgeneric.c` | - | doomgeneric | 1 |
| `progs/doomgeneric/doomgeneric.h` | - | doomgeneric | 10 |
| `progs/doomgeneric/doomgeneric_minios.c` | doomgeneric_minios.c - MiniOS platform layer for doomgeneric. | doomgeneric | 27 |
| `progs/doomgeneric/doomgeneric_sdl.c` | doomgeneric for soso os | doomgeneric | 10 |
| `progs/doomgeneric/doomgeneric_soso.c` | doomgeneric for soso os | doomgeneric | 13 |
| `progs/doomgeneric/doomgeneric_sosox.c` | doomgeneric for soso os (nano-x version) TODO: get keys from X, not using direct | doomgeneric | 12 |
| `progs/doomgeneric/doomgeneric_win.c` | - | doomgeneric | 10 |
| `progs/doomgeneric/doomgeneric_xlib.c` | - | doomgeneric | 9 |
| `progs/doomgeneric/doomkeys.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 59 |
| `progs/doomgeneric/doomstat.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 0 |
| `progs/doomgeneric/doomstat.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 68 |
| `progs/doomgeneric/doomtype.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 14 |
| `progs/doomgeneric/dstrings.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 0 |
| `progs/doomgeneric/dstrings.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 5 |
| `progs/doomgeneric/dummy.c` | - | doomgeneric | 1 |
| `progs/doomgeneric/f_finale.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 18 |
| `progs/doomgeneric/f_finale.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 4 |
| `progs/doomgeneric/f_wipe.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 10 |
| `progs/doomgeneric/f_wipe.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 4 |
| `progs/doomgeneric/g_game.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 54 |
| `progs/doomgeneric/g_game.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 22 |
| `progs/doomgeneric/gusconf.c` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 10 |
| `progs/doomgeneric/gusconf.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 3 |
| `progs/doomgeneric/hu_lib.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 22 |
| `progs/doomgeneric/hu_lib.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 24 |
| `progs/doomgeneric/hu_stuff.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 24 |
| `progs/doomgeneric/hu_stuff.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 17 |
| `progs/doomgeneric/i_cdmus.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software   | doomgeneric | 9 |
| `progs/doomgeneric/i_cdmus.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software   | doomgeneric | 18 |
| `progs/doomgeneric/i_endoom.c` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 3 |
| `progs/doomgeneric/i_endoom.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 2 |
| `progs/doomgeneric/i_input.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 5 |
| `progs/doomgeneric/i_joystick.c` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 10 |
| `progs/doomgeneric/i_joystick.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 18 |
| `progs/doomgeneric/i_main.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 4 |
| `progs/doomgeneric/i_minios_sound.c` | - | doomgeneric | 40 |
| `progs/doomgeneric/i_scale.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 39 |
| `progs/doomgeneric/i_scale.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 18 |
| `progs/doomgeneric/i_sound.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 34 |
| `progs/doomgeneric/i_sound.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 30 |
| `progs/doomgeneric/i_swap.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 8 |
| `progs/doomgeneric/i_system.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 21 |
| `progs/doomgeneric/i_system.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 12 |
| `progs/doomgeneric/i_timer.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 6 |
| `progs/doomgeneric/i_timer.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 7 |
| `progs/doomgeneric/i_video.c` | Emacs style mode select   -*- C++ -*- ------------------------------------------ | doomgeneric | 31 |
| `progs/doomgeneric/i_video.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 41 |
| `progs/doomgeneric/icon.c` | - | doomgeneric | 0 |
| `progs/doomgeneric/info.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 74 |
| `progs/doomgeneric/info.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 6 |
| `progs/doomgeneric/m_argv.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 7 |
| `progs/doomgeneric/m_argv.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 7 |
| `progs/doomgeneric/m_bbox.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 2 |
| `progs/doomgeneric/m_bbox.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 3 |
| `progs/doomgeneric/m_cheat.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 2 |
| `progs/doomgeneric/m_cheat.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 7 |
| `progs/doomgeneric/m_config.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software C | doomgeneric | 26 |
| `progs/doomgeneric/m_config.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 12 |
| `progs/doomgeneric/m_controls.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software C | doomgeneric | 9 |
| `progs/doomgeneric/m_controls.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software C | doomgeneric | 119 |
| `progs/doomgeneric/m_fixed.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 2 |
| `progs/doomgeneric/m_fixed.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 6 |
| `progs/doomgeneric/m_menu.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 68 |
| `progs/doomgeneric/m_menu.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 7 |
| `progs/doomgeneric/m_misc.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software C | doomgeneric | 22 |
| `progs/doomgeneric/m_misc.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 14 |
| `progs/doomgeneric/m_random.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 3 |
| `progs/doomgeneric/m_random.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 4 |
| `progs/doomgeneric/memio.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 9 |
| `progs/doomgeneric/memio.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 10 |
| `progs/doomgeneric/net_client.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 21 |
| `progs/doomgeneric/net_dedicated.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 2 |
| `progs/doomgeneric/net_defs.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 28 |
| `progs/doomgeneric/net_gui.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 2 |
| `progs/doomgeneric/net_io.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 9 |
| `progs/doomgeneric/net_loop.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 3 |
| `progs/doomgeneric/net_packet.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 9 |
| `progs/doomgeneric/net_query.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 12 |
| `progs/doomgeneric/net_sdl.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 2 |
| `progs/doomgeneric/net_server.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 6 |
| `progs/doomgeneric/p_ceilng.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 6 |
| `progs/doomgeneric/p_doors.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 10 |
| `progs/doomgeneric/p_enemy.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 68 |
| `progs/doomgeneric/p_floor.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 4 |
| `progs/doomgeneric/p_inter.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 10 |
| `progs/doomgeneric/p_inter.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/p_lights.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 11 |
| `progs/doomgeneric/p_local.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 91 |
| `progs/doomgeneric/p_map.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard, An | doomgeneric | 24 |
| `progs/doomgeneric/p_maputl.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard Cop | doomgeneric | 19 |
| `progs/doomgeneric/p_mobj.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 21 |
| `progs/doomgeneric/p_mobj.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 3 |
| `progs/doomgeneric/p_plats.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 6 |
| `progs/doomgeneric/p_pspr.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 35 |
| `progs/doomgeneric/p_pspr.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 4 |
| `progs/doomgeneric/p_saveg.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 58 |
| `progs/doomgeneric/p_saveg.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 16 |
| `progs/doomgeneric/p_setup.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 17 |
| `progs/doomgeneric/p_setup.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 3 |
| `progs/doomgeneric/p_sight.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 5 |
| `progs/doomgeneric/p_spec.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 31 |
| `progs/doomgeneric/p_spec.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 94 |
| `progs/doomgeneric/p_switch.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 4 |
| `progs/doomgeneric/p_telept.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/p_tick.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 6 |
| `progs/doomgeneric/p_tick.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 2 |
| `progs/doomgeneric/p_user.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 8 |
| `progs/doomgeneric/r_bsp.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 11 |
| `progs/doomgeneric/r_bsp.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 20 |
| `progs/doomgeneric/r_data.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 17 |
| `progs/doomgeneric/r_data.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 7 |
| `progs/doomgeneric/r_defs.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 25 |
| `progs/doomgeneric/r_draw.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 20 |
| `progs/doomgeneric/r_draw.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 32 |
| `progs/doomgeneric/r_local.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/r_main.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 20 |
| `progs/doomgeneric/r_main.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 36 |
| `progs/doomgeneric/r_plane.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 9 |
| `progs/doomgeneric/r_plane.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 15 |
| `progs/doomgeneric/r_segs.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 5 |
| `progs/doomgeneric/r_segs.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 2 |
| `progs/doomgeneric/r_sky.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/r_sky.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 6 |
| `progs/doomgeneric/r_state.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 45 |
| `progs/doomgeneric/r_things.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 17 |
| `progs/doomgeneric/r_things.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 22 |
| `progs/doomgeneric/s_sound.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 25 |
| `progs/doomgeneric/s_sound.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 15 |
| `progs/doomgeneric/sha1.c` | sha1.c - SHA1 hash function | doomgeneric | 19 |
| `progs/doomgeneric/sha1.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 9 |
| `progs/doomgeneric/sounds.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 3 |
| `progs/doomgeneric/sounds.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 3 |
| `progs/doomgeneric/st_lib.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 11 |
| `progs/doomgeneric/st_lib.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 14 |
| `progs/doomgeneric/st_stuff.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 137 |
| `progs/doomgeneric/st_stuff.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 19 |
| `progs/doomgeneric/statdump.c` | - | doomgeneric | 11 |
| `progs/doomgeneric/statdump.h` | - | doomgeneric | 3 |
| `progs/doomgeneric/tables.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/tables.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software C | doomgeneric | 21 |
| `progs/doomgeneric/v_patch.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 2 |
| `progs/doomgeneric/v_video.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 1993-2008 Raven Software C | doomgeneric | 32 |
| `progs/doomgeneric/v_video.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 27 |
| `progs/doomgeneric/w_checksum.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 3 |
| `progs/doomgeneric/w_checksum.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 2 |
| `progs/doomgeneric/w_file.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 6 |
| `progs/doomgeneric/w_file.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 7 |
| `progs/doomgeneric/w_file_stdc.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 5 |
| `progs/doomgeneric/w_main.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 1 |
| `progs/doomgeneric/w_main.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 1 |
| `progs/doomgeneric/w_merge.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redi | doomgeneric | 7 |
| `progs/doomgeneric/w_wad.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 16 |
| `progs/doomgeneric/w_wad.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 17 |
| `progs/doomgeneric/wi_stuff.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 68 |
| `progs/doomgeneric/wi_stuff.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 5 |
| `progs/doomgeneric/z_zone.c` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 18 |
| `progs/doomgeneric/z_zone.h` | Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  Th | doomgeneric | 13 |
| `progs/file/file.c` | Docstring: MiniOS file browser (Nuklear ring-3 app, MiniFS: file/file.elf). | misc | 47 |
| `progs/freedomui/freedomui_minios.c` | freedomui_minios - Real FreeDom browser on MiniOS, DOOM/Q2G pattern. | misc | 42 |
| `progs/lisp/lisp.c` | - | lisp | 105 |
| `progs/lisp/tin.c` | - | lisp | 1 |
| `progs/lua/lua_main.c` | - | lua | 7 |
| `progs/lua/minios.c` | - | lua | 17 |
| `progs/micropython/variants/minios/lib/__init__.py` | MiniOS frozen library package. | lib | 0 |
| `progs/micropython/variants/minios/lib/hello.py` | hello.py -- frozen demo: runs at import time as a smoke test. | lib | 0 |
| `progs/micropython/variants/minios/manifest.py` | manifest.py -- frozen modules for the MiniOS MicroPython variant. Scripts listed | minios | 0 |
| `progs/micropython/variants/minios/minios_module.c` | - | minios | 21 |
| `progs/micropython/variants/minios/mpconfigvariant.h` | - | minios | 38 |
| `progs/minicraft/minicraft.c` | minicraft.c - Minecraft-like voxel walker for MiniOS (ring 3, static ELF). | misc | 233 |
| `progs/minios_abi.h` | minios_abi.h -- Single source of truth for the MiniOS user-kernel ABI. | progs | 129 |
| `progs/minios_png.h` | Docstring: shared ring-3 PNG helpers for MiniOS apps (progs/minios_png.h). | progs | 19 |
| `progs/nk_palette.h` | nk_palette.h - one shared hybrid palette for every NK-window app. | progs | 9 |
| `progs/nuklear/cvm_emit.c` | cvm_emit.c — node-graph to CVM bytecode compiler. | nuklear | 56 |
| `progs/nuklear/cvm_emit.h` | cvm_emit.h — node-graph compiler for CVM (cvm2 module format v2). | nuklear | 6 |
| `progs/nuklear/font8x8.c` | font8x8 - shared 8x8 bitmap font for MiniOS ring-3 graphics programs. | nuklear | 0 |
| `progs/nuklear/node_editor.c` | node_editor.c — visual low-code editor that compiles to CVM bytecode. | nuklear | 34 |
| `progs/nuklear/nuklear_minios.c` | nuklear_minios.c — MiniOS platform layer for Nuklear. | nuklear | 44 |
| `progs/nuklear/nuklear_minios.h` | nuklear_minios.h — MiniOS platform layer for Nuklear. | nuklear | 24 |
| `progs/nuklear/nuklear_theme.c` | Docstring: shared Nuklear theme loader, linked by every NK app. | nuklear | 7 |
| `progs/nuklear/nuklear_theme.h` | Docstring: shared Nuklear theme contract for every MiniOS NK app. | nuklear | 13 |
| `progs/paint/paint.c` | Docstring: MiniOS paint program (Nuklear ring-3 app, MiniFS: paint/paint.elf). | misc | 53 |
| `progs/piano/piano.c` | piano.c — a Nuklear piano that plays FM sound through the SB16 driver. | misc | 60 |
| `progs/pokemon/fetch.sh` | fetch.sh - clone the gb-recompiled tool into progs/pokemon/upstream.  The upstre | pokemon | 0 |
| `progs/pokemon/minios_stubs/SDL.h` | SDL.h stub for MiniOS cross-compilation | misc | 10 |
| `progs/pokemon/platform_minios.c` | - | pokemon | 105 |
| `progs/quake2generic/q2generic_minios.c` | q2generic_minios.c - MiniOS platform layer for quake2generic. | misc | 30 |
| `progs/src/aes.c` | aes.c - command path AES-256-CTR encryption tools: aes and unaes. | src | 54 |
| `progs/src/audio.c` | - | src | 17 |
| `progs/src/cp.c` | - | src | 8 |
| `progs/src/cpl.c` | Ring-3 privilege probe. Reads the CS selector at runtime and exits with | src | 3 |
| `progs/src/fib.c` | - | src | 2 |
| `progs/src/fptest.c` | fptest.c -- FPU/SSE context-switch probe (Phase 0.1, ADR-0014). | src | 9 |
| `progs/src/freedom.c` | freedom - a headless text browser for MiniOS. | src | 61 |
| `progs/src/freedom_wl.c` | freedom_wl - Wayland to MiniOS intermediate layer for FreeDom. | src | 62 |
| `progs/src/ftest.c` | Exercises the kernel libc surface used by loaded .o programs: fprintf to stdout/ | src | 7 |
| `progs/src/hello.c` | MiniOS test program — compiled as relocatable .o, loaded by kernel ELF loader | src | 2 |
| `progs/src/hello.py` | - | src | 0 |
| `progs/src/http.c` | Minimal HTTP/1.0 GET through the Linux socket syscalls. | src | 13 |
| `progs/src/json.c` | json.c - command path JSON tool: validate, pretty-print and query. | src | 41 |
| `progs/src/kmem.c` | Kernel-pointer rejection probe. Passes a supervisor-only address | src | 3 |
| `progs/src/ldhello.c` | - | src | 1 |
| `progs/src/lxhello.c` | - | src | 7 |
| `progs/src/lz4.c` | lz4.c - command path LZ4 (de)compression tools: lz4 and unlz4. | src | 26 |
| `progs/src/lzss.c` | lzss.c - command path LZSS (de)compression tools: lzss and unlzss. | src | 48 |
| `progs/src/mmreuse.c` | mmap/munmap reclaim stress test.  Repeatedly maps and unmaps a large | src | 5 |
| `progs/src/mthreads.h` | mthreads.h -- Minimal pthread-like threads for MiniOS ELFs (roadmap | src | 20 |
| `progs/src/nx.c` | NX probe. Under the isolation contract every user page starts | src | 3 |
| `progs/src/opl3.c` | - | src | 18 |
| `progs/src/pollready.c` | - | src | 6 |
| `progs/src/sbtone.c` | sbtone.c — headless SB16 diagnostic (ring-3, no GUI). | src | 8 |
| `progs/src/shell.py` | shell.py -- pybash: a Python shell layer on top of MiniOS's C shell.  The C shel | src | 3 |
| `progs/src/spin.c` | - | src | 19 |
| `progs/src/test.c` | - | src | 2 |
| `progs/src/test.lua` | - | src | 20 |
| `progs/src/test.py` | test.py -- in-OS test suite for MiniOS, driven by MicroPython.  Tests every avai | src | 20 |
| `progs/src/test_all.sh` | test_all.sh -- comprehensive non-interactive test suite for MiniOS.  Run with:   | src | 0 |
| `progs/src/thdemo.c` | thdemo.c -- Producer-consumer over mthreads (roadmap Phase 1, M1). | src | 10 |
| `progs/src/w1.c` | - | src | 2 |
| `progs/tls_u/tls_u_main.c` | tlsget - minimal HTTPS GET over the ring-3 TLS stack. | tls_u | 5 |
| `progs/tls_u/tls_u_port.c` | tls_u_port.c - ring-3 transport for the shared TLS stack (TLS_RING3). | tls_u | 15 |
| `progs/topogpt3/topogpt3.c` | - | misc | 128 |
| `progs/vedit/vedit.c` | vedit IDE build and run contract. | misc | 128 |
| `progs/wl/wl_client.h` | wl_client.h - Thin mailbox client for Wayland-mini (ADR-0026). | wl | 5 |
| `progs/wl/wl_mbox.h` | wl_mbox.h - Mailbox file transport for Wayland-mini (ADR-0026). | wl | 26 |
| `progs/wl/wl_mini.h` | wl_mini.h - Wayland-mini subset contract (header-only, ADR-0024). | wl | 104 |
| `progs/wl/wlcomp.c` | wlcomp - Wayland-mini ring-3 compositor (ADR-0024, ADR-0026). | wl | 43 |
| `qga.c` | MiniOS QEMU guest agent (QGA). | root | 27 |
| `smp.c` | SMP application-processor bring-up. | root | 39 |
| `tests/host_aes.sh` | host_aes.sh - host-side verification for the AES-256-CTR command tools.  The min | tests | 3 |
| `tests/host_codecs.sh` | host_codecs.sh - reusable host-side verification for the in-OS codec tools.  The | tests | 5 |
| `tests/test_abi.c` | Docstring: tests/test_abi.c -- Host test for the ABI manifest gate. | tests | 2 |
| `tests/test_batch.c` | Docstring: Host test for kernel/batch.c (make test-batch). | tests | 3 |
| `tests/test_doom_pwad.py` | test_doom_pwad.py - host contract suite for tools/doom_pwad.py.  Runs the grid c | tests | 44 |
| `tests/test_driver.c` | test_driver.c -- Host test for the Strategy-pattern device registry. | tests | 5 |
| `tests/test_fault.c` | test_fault.c -- fault-injection suite (boyscout gap #10). | tests | 11 |
| `tests/test_file_assoc.c` | Docstring: host test for the file browser assoc contract (make test-file). | tests | 6 |
| `tests/test_freedom_wl.c` | test_freedom_wl - host suite for the Wayland to MiniOS mapping. | tests | 3 |
| `tests/test_freedomui.c` | test_freedomui - host suite for the real FreeDom MiniOS backend. | tests | 2 |
| `tests/test_futex.c` | Docstring: Host test for kernel/futex.c (make test-futex). | tests | 6 |
| `tests/test_hal_io.c` | Docstring: Host test for arch/x86/hal_io.h (make test-hal). | tests | 3 |
| `tests/test_ktime.c` | test_ktime.c -- host test for the pure conversion math in ktime.h | tests | 2 |
| `tests/test_minios_png.c` | Docstring: host test for the shared ring-3 PNG helpers (make test-png). | tests | 9 |
| `tests/test_modifiers.c` | - | tests | 2 |
| `tests/test_notify.c` | - | tests | 3 |
| `tests/test_paint.c` | Docstring: host test for the paint canvas/PNG contract (make test-paint). | tests | 21 |
| `tests/test_percpu_rq.c` | Docstring: Host test for kernel/percpu_rq.c (make test-percpu-rq). | tests | 2 |
| `tests/test_randmix.c` | test_randmix.c -- host test for the getrandom mixer in randmix.h | tests | 3 |
| `tests/test_rcu.c` | Docstring: Host test for kernel/rcu.c (make test-rcu). | tests | 4 |
| `tests/test_rtc.c` | test_rtc.c -- host test for the pure date math in drivers/rtc.c | tests | 2 |
| `tests/test_sanitize.c` | Docstring: Host test for sanitize.h (make test-sanitize). | tests | 9 |
| `tests/test_sync.c` | Host-side unit test for the blocking sync primitives (kernel/sync.c). | tests | 6 |
| `tests/test_theme.c` | Docstring: host test for the shared Nuklear theme contract. | tests | 8 |
| `tests/test_tick.c` | Docstring: Host test for kernel/tick.c (make test-tick). | tests | 6 |
| `tests/test_vedit_build.c` | Docstring: Host test for the vedit IDE build contract (make test-vedit). | tests | 8 |
| `tests/test_vma.c` | Host-side unit test for the VMA red-black tree (vma.c). | tests | 8 |
| `tests/test_vma_bench.c` | test_vma_bench.c -- RB-tree vs sorted-list benchmark (boyscout gap #9). | tests | 6 |
| `tests/test_wl.c` | Host test for progs/wl/wl_mini.h (make test-wl). | tests | 2 |
| `tests/test_wm.c` | Docstring: Host test for wm_geom.h and wm_events.h (make test-wm). | tests | 2 |
| `tls_test.c` | tls_test.c - host-side tests for the kernel TLS stack. | root | 23 |
| `tools/abi_stamp.c` | Docstring: tools/abi_stamp.c -- Build-time ABI manifest generator. | tools | 1 |
| `tools/boot_run.sh` | boot_run.sh -- boot the MiniOS image in QEMU and drive the shell over the serial | tools | 0 |
| `tools/boot_wl.py` | boot_wl.py - boot the miniOS Wayland-mini desktop in one step.  Builds nothing;  | tools | 14 |
| `tools/check_abi_numbers.py` | check_abi_numbers.py -- MiniOS syscall numbers vs Linux x86-64 truth.  Phase 0.6 | tools | 4 |
| `tools/check_addons.py` | check_addons.py -- validate the MiniOS addon marketplace index.  Loads every add | tools | 2 |
| `tools/check_cohesion.py` | check_cohesion.py -- Architectural cohesion gate for MiniOS CI.  Parses the CPG  | tools | 4 |
| `tools/check_complexity.py` | check_complexity.py -- Kernel complexity gate for MiniOS CI.  Validates that ker | tools | 3 |
| `tools/check_fork_stubs.py` | Fail-closed stub gate for unimplemented process syscalls.  fork, vfork and execv | tools | 4 |
| `tools/check_kb_sync.py` | check_kb_sync.py -- Verify KNOWLEDGE_BASE.md is in sync with code.  Runs readmen | tools | 2 |
| `tools/check_mutant_anchors.py` | Verify every mutate.sh mutant anchor matches its target file.  A mutant whose se | tools | 5 |
| `tools/check_surprising.py` | check_surprising.py -- Detect surprising architectural connections.  Parses the  | tools | 5 |
| `tools/check_syscall_sanitize.py` | Scoped audit gate for syscall user-pointer sanitization.  Every ring-3 pointer t | tools | 8 |
| `tools/doom_pwad.py` | doom_pwad.py - grid map to vanilla Doom PWAD writer and checker.  Converts a tex | tools | 25 |
| `tools/extract_shell.py` | tools/extract_shell.py -- Plan for Phase 6.1 shell extraction.  This script docu | tools | 0 |
| `tools/gdb_repro.py` | gdb_repro.py — drive a graphics-program sequence under the GDB stub.  Boots Mini | tools | 4 |
| `tools/gen_desktop_pngs.py` | gen_desktop_pngs.py -- build MiniOS desktop art from user-supplied PNGs.  Source | tools | 2 |
| `tools/gen_icons.py` | gen_icons.py -- generate 32x32 RGBA PNG icon files for the MiniOS desktop.  Each | tools | 3 |
| `tools/gen_minifs.py` | Generate minifs.c for MiniOS. | tools | 0 |
| `tools/gen_zip_fixtures.py` | gen_zip_fixtures.py -- generate the zip test fixtures shipped on the ramdisk.  T | tools | 2 |
| `tools/install.sh` | - | tools | 0 |
| `tools/kernel_feature_survey.py` | kernel_feature_survey.py - verify which C features the MiniOS kernel needs.  Sca | tools | 8 |
| `tools/lisp_scoped.sh` | Docstring: Scoped Lisp validation for the MiniOS interpreter contract. Builds th | tools | 5 |
| `tools/make_usb.sh` | Build the MiniOS bootable USB image and optionally write it to a device.  Wraps  | tools | 2 |
| `tools/minifs_dump.py` | minifs_dump.py - Dump/inspect a MiniFS filesystem image. | tools | 12 |
| `tools/minifs_fsck.py` | minifs_fsck.py - Check MiniFS filesystem consistency. | tools | 15 |
| `tools/minifs_saves.py` | minifs_saves.py - preserve the guest's saves/ dir across image rebuilds.  Regene | tools | 21 |
| `tools/minios_cli.py` | minios_cli.py — drive MiniOS through the MCP bridge, not by hand.  Starts mcp/mi | tools | 6 |
| `tools/minios_gui.py` | minios_gui.py — inject VGA-mode input and capture the framebuffer.  Boots MiniOS | tools | 9 |
| `tools/minios_hyper.py` | minios_hyper.py -- host-side ring-minus-one debugger for MiniOS.  QEMU already r | tools | 51 |
| `tools/mkfs.minifs.py` | mkfs.minifs.py - Create a MiniFS filesystem image for MiniOS.  Usage: python3 mk | tools | 20 |
| `tools/mkpak1.py` | Build baseq2/pak1.pak carrying the player model.  The Quake 2 shareware pak0.pak | tools | 1 |
| `tools/mkramdisk.py` | Build a MiniOS ramdisk image from files in a directory tree.  Each packed file i | tools | 2 |
| `tools/mkroots.sh` | mkroots.sh - regenerate tls_roots.h from the DER files in tls_roots_src/.  Prove | tools | 0 |
| `tools/mutate.sh` | Mutation testing for MiniOS.  Each mutation is applied to the source in place, t | tools | 5 |
| `tools/probe_compute_vga.py` | Docstring: VGA liveness probe during CPU-bound ring-3 compute. Boots os.img head | tools | 6 |
| `tools/probe_minicraft.py` | probe_minicraft.py -- numeric minicraft probe without any PNG.  Boots os.img hea | tools | 6 |
| `tools/qga_client.py` | Minimal QEMU guest agent client for MiniOS.  Connects to the guest agent socket  | tools | 4 |
| `tools/qga_test.sh` | Quick standalone smoke test for the QEMU guest agent: boots os.img once with the | tools | 3 |
| `tools/repro_gui.py` | repro_gui.py — reproduce the VGA/mouse state bug after ring-3 programs.  Boots M | tools | 10 |
| `tools/test_bdd.sh` | BDD suite for MiniOS: boots the disk image in QEMU and drives the shell over the | tools | 11 |
| `tools/test_call_align.py` | test_call_align.py - verify stack alignment at call sites, both parities.  Compi | tools | 4 |
| `tools/test_codecs.sh` | test_codecs.sh -- exercise the lzss/lz4/aes command-pair tools inside the OS.  T | tools | 0 |
| `tools/test_gui_fashion.py` | test_gui_fashion.py -- GUI proof for the cursor/flicker/quit fixes.  Boots the r | tools | 18 |
| `tools/test_gui_icon_cwd.py` | test_gui_icon_cwd.py -- GUI proof that dock launches ignore shell cwd.  Boots th | tools | 17 |
| `tools/test_gui_menu.py` | test_gui_menu.py -- serial proof that the minicraft pause menu works.  ESC must  | tools | 1 |
| `tools/test_gui_wm.py` | test_gui_wm.py -- GUI proof that graphics windows survive the WM.  Serial `wm` c | tools | 17 |
| `tools/test_gui_zoom.py` | test_gui_zoom.py -- pixel proof that GFX_ZOOM doubles the game window.  Boots Mi | tools | 1 |
| `tools/test_http_server.py` | Host-side HTTP fixture for the freedom BDD scenarios.  Serves behaviours that py | tools | 3 |
| `tools/test_lisp.py` | Host test suite for the MiniOS Lisp interpreter.  Builds progs/lisp/lisp.c with  | tools | 16 |
| `tools/test_sb16.sh` | test_sb16.sh — targeted BDD harness for the SB16 audio path.  Boots the disk ima | tools | 1 |
| `tools/tls_test.py` | Host-side TLS test driver for the MiniOS kernel TLS client.  Generates a throwaw | tools | 16 |
| `tools/wl_scoped.sh` | Docstring: Scoped Wayland-mini validation for the tiled ring-3 compositor. Runs  | tools | 4 |
| `tools/wm_layout_sync.py` | Docstring: Synchronize the WM layout manifest from source truth.  I read wm_layo | tools | 17 |
| `tools/wm_scoped.sh` | Docstring: Scoped WM validation for Alt-Tab and tile across all windows. Runs ho | tools | 2 |
| `vma.c` | - | root | 14 |
