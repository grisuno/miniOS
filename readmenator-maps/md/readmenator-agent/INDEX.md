# Index (page 1 of 2)
Pages: [INDEX.md](INDEX.md), [INDEX_p2.md](INDEX_p2.md)

| File | Purpose | Subsystem | Symbols | Used by |
|------|---------|-----------|---------|---------|
| `arch/x86/ap_entry.S` | SMP application-processor bootstrap stub. | x86 | 9 | 0 |
| `arch/x86/boot/stage1.S` | MiniOS boot sector. | boot | 11 | 0 |
| `arch/x86/boot/stage2.S` | MiniOS second-stage loader. | boot | 40 | 0 |
| `arch/x86/ctx_sw.S` | sched_park_capture: captured the rest. | x86 | 9 | 0 |
| `arch/x86/isr_stubs.S` | - | x86 | 24 | 0 |
| `arch/x86/syscall_entry.S` | - | x86 | 4 | 0 |
| `boot/uefi_stub.c` | Docstring: boot/uefi_stub.c -- Minimal MiniOS UEFI stub (Phase 1). | misc | 50 | 0 |
| `bootloader.c` | - | root | 2 | 0 |
| `drivers/block.c` | Block device layer for MiniFS. | drivers | 19 | 0 |
| `drivers/driver.c` | Device registry for the Strategy-pattern driver layer. | drivers | 8 | 0 |
| `drivers/ide.c` | IDE/ATA PIO driver for MiniOS. | drivers | 19 | 0 |
| `drivers/kbd.c` | kbd_drop_counts: #define kbd_super (kbd_mods.super) #define kbd_altgr (kbd_mods.altgr) #define... | drivers | 35 | 0 |
| `drivers/mouse.c` | Docstring: PS/2 mouse device driver (drivers/mouse.c). | drivers | 7 | 0 |
| `drivers/nvme.c` | - | drivers | 50 | 0 |
| `drivers/pcm2.c` | drivers/pcm2.c -- low-latency PCM audio over SB16 single-cycle DMA. | drivers | 43 | 0 |
| `drivers/pcspk.c` | PC speaker driver with a software master volume. | drivers | 18 | 0 |
| `drivers/rtc.c` | CMOS RTC time-of-day reader. | drivers | 25 | 0 |
| `drivers/sb16.c` | Sound Blaster 16 DMA audio driver. | drivers | 64 | 0 |
| `drivers/usbblk.c` | USB mass storage, Bulk-Only Transport over SCSI. | drivers | 44 | 1 |
| `drivers/usbhid.c` | USB HID boot-protocol keyboard and mouse. | drivers | 26 | 1 |
| `drivers/virtio_blk.c` | Docstring: drivers/virtio_blk.c -- Polled legacy virtio-blk driver. | drivers | 39 | 0 |
| `drivers/virtio_net.c` | Docstring: drivers/virtio_net.c -- Polled legacy virtio-net driver. | drivers | 44 | 0 |
| `drivers/xhci.c` | xHCI host controller driver, polled event ring. | drivers | 209 | 3 |
| `fs/ext4.c` | ext_geo_t: Filesystem geometry from the superblock. | fs | 38 | 1 |
| `fs/fat32.c` | fat_geo_t: Parsed BPB plus derived geometry. secs = total data clusters + 2 (cluster numbers 0/1... | fs | 31 | 1 |
| `fs/fsimg.c` | fsimg_dev_read: Docstring: Sector reads off the active backend through the block layer, so a... | fs | 5 | 2 |
| `fs/kfile.c` | kpipe_pair: Docstring: Create a connected pipe pair sharing one ring. | fs | 30 | 0 |
| `fs/minifs.c` | MiniFS: minimal Unix-like filesystem for MiniOS. | fs | 66 | 0 |
| `fs/pcache.c` | Docstring: fs/pcache.c -- page cache store for MiniFS (T5 slice 1). | fs | 16 | 1 |
| `fs/ramdisk.c` | ramdisk_usage: int ramdisk_list(RDFile **out, int max) { if (!rd) return 0; int n =... | fs | 25 | 0 |
| `fs/vfs.c` | ramdisk_vfs_readdir: Docstring: List ramdisk leaves under dir ("" or "/" is root). | fs | 44 | 0 |
| `fs/zip.c` | — the unzip/zip shell builtins over the miniz zip library. | fs | 10 | 0 |
| `headers/abi.h` | Docstring: abi.h -- Boot-time ABI manifest gate contract. | headers | 10 | 3 |
| `headers/ap_stub.h` | generated from ap_stub.bin - do not edit | headers | 0 | 1 |
| `headers/arch/x86/boot/bootdefs.h` | centralized configuration for the MiniOS two-stage boot path. | misc | 151 | 13 |
| `headers/arch/x86/hal_io.h` | Docstring: x86 port I/O hardware abstraction contract. | headers_arch_x86 | 69 | 8 |
| `headers/arch/x86/msr.h` | Model-Specific Register access for x86-64. | headers_arch_x86 | 9 | 7 |
| `headers/arena.h` | Docstring: bump arena for MiniOS, kernel and ring-3 alike. | headers | 15 | 2 |
| `headers/audio.h` | Unified audio API for MiniOS. | headers | 18 | 1 |
| `headers/batch.h` | Docstring: batch.h -- Batched synchronous syscall submission. | headers | 12 | 3 |
| `headers/block.h` | Block device abstraction for MiniFS. | headers | 14 | 7 |
| `headers/desktop_icons.h` | embedded icon pixel data for desktop shortcuts. | headers | 3 | 1 |
| `headers/desktop_shortcuts.h` | configurable desktop icon shortcuts. | headers | 27 | 1 |
| `headers/driver.h` | Strategy pattern for hardware drivers (thesis correction 2). | headers | 16 | 10 |
| `headers/drivers/kbd.h` | Keyboard layout: US qwerty (default) or Spanish (Spain) qwerty. | headers_drivers | 24 | 7 |
| `headers/drivers/modifiers.h` | Docstring: Unified modifier tracking for cooked and raw paths. | headers_drivers | 11 | 4 |
| `headers/drivers/mouse.h` | Docstring: mouse.h -- boundary of the PS/2 mouse device driver | headers_drivers | 4 | 2 |
| `headers/drivers/nvme.h` | - | headers_drivers | 7 | 3 |
| `headers/drivers/pci.h` | Docstring: drivers/pci.h -- PCI configuration-space access. | headers_drivers | 54 | 6 |
| `headers/drivers/usbblk.h` | Docstring: drivers/usbblk.h -- boundary of the USB mass-storage driver. | headers_drivers | 13 | 5 |
| `headers/drivers/usbhid.h` | Docstring: drivers/usbhid.h -- boundary of the USB HID boot-protocol driver. | headers_drivers | 33 | 5 |
| `headers/drivers/virtio_blk.h` | Docstring: drivers/virtio_blk.h -- virtio-blk boundary. | headers_drivers | 7 | 4 |
| `headers/drivers/virtio_net.h` | Docstring: drivers/virtio_net.h -- virtio-net boundary. | headers_drivers | 9 | 3 |
| `headers/drivers/xhci.h` | Docstring: drivers/xhci.h -- boundary of the xHCI host controller driver. | headers_drivers | 51 | 8 |
| `headers/editor.h` | the built-in line editor contract. | headers | 2 | 2 |
| `headers/ext4.h` | Read-only ext4 loopback/device driver. | headers | 15 | 4 |
| `headers/fat32.h` | Read-only FAT32 loopback driver over ramdisk/MiniFS images. | headers | 16 | 4 |
| `headers/fsimg.h` | One image backend for read-only filesystem drivers. | headers | 6 | 5 |
| `headers/futex.h` | Docstring: futex.h -- Fast userspace mutex sleep/wake contract. | headers | 27 | 4 |
| `headers/httpd.h` | Docstring: httpd.h -- Minimal static HTTP/1.0 server contract. | headers | 10 | 2 |
| `headers/ide.h` | IDE/ATA PIO driver for MiniOS. | headers | 35 | 6 |
| `headers/kernel.h` | The user-window memory layout (load base, stack, brk cap, graphics | headers | 410 | 4 |
| `headers/kernel/console_in.h` | Docstring: console_in.h -- boundary of the console input device | headers_kernel | 11 | 3 |
| `headers/kernel/vga_cursor.h` | Docstring: vga_cursor.h -- boundary of the pointer sprite layer | headers_kernel | 9 | 2 |
| `headers/ktime.h` | pure time-conversion helpers shared by the kernel clock | headers | 3 | 3 |
| `headers/ldso.h` | Docstring: headers/ldso.h -- minimal dynamic-linking (T8 ld.so) contract. | headers | 45 | 5 |
| `headers/leakcheck.h` | Docstring: allocation tracker for MiniOS, STB leakcheck lineage. | headers | 24 | 3 |
| `headers/lz4_kernel.h` | - | headers | 4 | 4 |
| `headers/minifetch.h` | Docstring: minifetch.h -- neofetch-style system screen contract. | headers | 2 | 2 |
| `headers/minifs.h` | MiniFS: a minimal Unix-like filesystem for MiniOS. | headers | 77 | 15 |
| `headers/net.h` | net_sys_is_socket: net_connect / socket fds are NET_FD_BASE + index for Linux syscalls and *... | headers | 103 | 9 |
| `headers/net/rtl8139.h` | rtl_present: rtl8139 NIC driver interface. | misc | 8 | 2 |
| `headers/panic.h` | Docstring: panic.h -- Kernel panic backtrace contract (header-only). | headers | 3 | 2 |
| `headers/pcache.h` | Docstring: pcache.h -- page cache for MiniFS, slice 1 (store only). | headers | 17 | 9 |
| `headers/pcm2.h` | low-latency PCM audio path over SB16 single-cycle DMA. | headers | 21 | 5 |
| `headers/pcm_ring.h` | single-producer/single-consumer byte ring for PCM audio. | headers | 7 | 2 |
| `headers/pcspk.h` | - | headers | 9 | 3 |
| `headers/percpu_rq.h` | Docstring: percpu_rq.h -- Per-CPU runqueues with work stealing. | headers | 14 | 5 |
| `headers/pipe.h` | Docstring: pipe.h -- Kernel pipe ring contract (header-only). | headers | 17 | 3 |
| `headers/proc_sec.h` | Docstring: proc_sec.h -- per-process security state behind the Linux | headers | 12 | 5 |
| `headers/qga.h` | - | headers | 29 | 1 |
| `headers/randmix.h` | entropy mixer for getrandom (318). | headers | 2 | 2 |
| `headers/rcu.h` | Docstring: rcu.h -- Read-copy-update, lite epoch edition. | headers | 17 | 4 |
| `headers/rtc.h` | rtc_days_from_civil: Days since 1970-01-01 for a civil date (Howard Hinnant's algorithm, pure... | headers | 6 | 6 |
| `headers/sanitize.h` | Docstring: sanitize.h -- Single choke point for syscall argument checks. | headers | 5 | 4 |
| `headers/sb16.h` | Sound Blaster 16 DMA audio driver contract. | headers | 28 | 6 |
| `headers/sched.h` | Forward: full view lives in kernel.h (needs KFILE first); the PCB | headers | 157 | 27 |
| `headers/seccomp_bpf.h` | Docstring: seccomp_bpf.h -- classic BPF checker and interpreter for | headers | 58 | 3 |
| `headers/shell.h` | shared shell constants and the line reader/parser reused by | headers | 8 | 3 |
| `headers/smp.h` | SMP bring-up: wake the application processors (APs) via the LAPIC INIT/SIPI | headers | 11 | 4 |
| `headers/spawn.h` | Docstring: Scalar shared-window view saved across a child run. | headers | 9 | 3 |
| `headers/spinlock.h` | Lightweight spinlock for MiniOS kernel. | headers | 19 | 8 |
| `headers/sync.h` | Blocking synchronization primitives (roadmap Phase 3.1). | headers | 36 | 7 |
| `headers/syscall_asm.h` | numeric contract for arch/x86/syscall_entry.S. | headers | 13 | 2 |
| `headers/syscalls_proc.h` | process-management syscall handlers shared with the | headers | 20 | 3 |
| `headers/tick.h` | Docstring: Tick listener bus contract. | headers | 16 | 3 |
| `headers/tls.h` | tls_free_fd: Kernel built without the TLS engine (net/tls*.c unlinked): no session can ever... | headers | 73 | 6 |
| `headers/tls_port.h` | Portability shim between the MiniOS kernel and the host-side test | headers | 49 | 5 |
| `headers/tls_roots.h` | embedded CA roots (DER), generated by mkroots.sh. | headers | 0 | 1 |
| `headers/tls_test_roots.h` | generated by tls_test.py; never built into the kernel. | headers | 0 | 1 |
| `headers/vga_fb.h` | Framebuffer geometry. | headers | 149 | 19 |
| `headers/vga_fx.h` | Docstring: DOOM-melt desktop effect contract for MiniOS. | headers | 9 | 3 |
| `headers/vma.h` | vma_ctx_t: Per-process VMA context (multitask foundation): every non-CLONE_VM process owns its... | headers | 26 | 8 |
| `headers/wm_events.h` | Docstring: Window event contract for the MiniOS desktop. | headers | 39 | 3 |
| `headers/wm_focus.h` | Docstring: Focus manager contract for the MiniOS desktop. | headers | 5 | 2 |
| `headers/wm_geom.h` | Docstring: Window geometry contract for the MiniOS desktop. | headers | 11 | 3 |
| `headers/wm_gfxview.h` | Docstring: Graphics-window view contract for the MiniOS desktop. | headers | 15 | 2 |
| `headers/wm_layout.h` | Docstring: Unified layout contract for the MiniOS desktop. | headers | 16 | 3 |
| `headers/wm_notify.h` | Docstring: Focus event bus for the MiniOS desktop. | headers | 9 | 4 |
| `headers/wm_render.h` | Docstring: Render pipeline contract for the MiniOS desktop. | headers | 5 | 2 |
| `headers/wm_tiling.h` | Docstring: Tiling layout contract for the MiniOS desktop. | headers | 3 | 2 |
| `headers/wm_window.h` | Docstring: Unified window contract for the MiniOS desktop. | headers | 10 | 4 |
| `headers/zip.h` | — MiniOS integration API for the miniz zip library. | headers | 3 | 2 |
| `kernel.c` | Mediator: boot orchestration and the syscall trampoline. | root | 16 | 0 |
| `kernel/abi.c` | Docstring: kernel/abi.c -- Boot-time ABI manifest gate. | kernel | 3 | 0 |
| `kernel/batch.c` | Docstring: kernel/batch.c -- Ordered batch executor. | kernel | 1 | 0 |
| `kernel/clip.c` | Docstring: kernel/clip.c -- Shared text clipboard. | kernel | 4 | 0 |
| `kernel/console.c` | Execution-context output: text console, capture, libc names. | kernel | 27 | 0 |
| `kernel/console_in.c` | Docstring: Console input device (kernel/console_in.c). | kernel | 31 | 0 |
| `kernel/cvm_host.c` | - | kernel | 45 | 0 |
| `kernel/editor.c` | edit_list: List a (possibly empty) range [start, end], both 1-based inclusive. | kernel | 22 | 0 |
| `kernel/exec.c` | Process execution: setjmp/longjmp, k_exec_user, k_run_rel, kexit. | kernel | 10 | 0 |
| `kernel/futex.c` | Docstring: kernel/futex.c -- Kernel side of the futex contract. | kernel | 8 | 0 |
| `kernel/klog.c` | Structured kernel logging with levels and subsystems. | kernel | 6 | 0 |
| `kernel/ldso_parse.c` | Docstring: kernel/ldso_parse.c -- pure dynamic-table parsing (T8 ld.so). | kernel | 20 | 1 |
| `kernel/loader.c` | ldso_read_file: Read a whole library file by DT_NEEDED name: exact path first, then the... | kernel | 47 | 0 |
| `kernel/lz4_kernel.c` | - | kernel | 10 | 0 |
| `kernel/minifetch.c` | Docstring: kernel/minifetch.c -- neofetch-style system screen. | kernel | 6 | 0 |
| `kernel/mm.c` | kheap_ram_top: RAM top from the CMOS extended-memory count (the identity map covers the first... | kernel | 11 | 0 |
| `kernel/mm/cow.c` | Docstring: kernel/mm/cow.c -- Copy-on-write fork support. | mm | 28 | 0 |
| `kernel/mm/paging.c` | Page table management for the user window and per-process KPTI. | mm | 33 | 0 |
| `kernel/mm/swap.c` | Swap-out/swap-in for the user window (LZ4-compressed disk swap). | mm | 11 | 0 |
| `kernel/panic.c` | Docstring: kernel/panic.c -- Kernel panic screen. | kernel | 4 | 0 |
| `kernel/percpu_rq.c` | Docstring: kernel/percpu_rq.c -- Per-CPU runqueue hints and stealing. | kernel | 9 | 0 |
| `kernel/printf.c` | - | kernel | 10 | 0 |
| `kernel/proc_sec.c` | Docstring: proc_sec.c -- per-process security state: the Linux seccomp | kernel | 43 | 0 |
| `kernel/rcu.c` | Docstring: kernel/rcu.c -- Epoch grace periods over scheduler ticks. | kernel | 14 | 0 |
| `kernel/redirect.c` | - | kernel | 3 | 0 |
| `kernel/sched.c` | trap_frame_t: if (len == 0 \|\| len > 256) { kprintf("gdb: dump length 1..256 (got %lu)\n", len)... | kernel | 132 | 0 |
| `kernel/scrollback.c` | Console scrollback ring buffer. | kernel | 8 | 0 |
| `kernel/seccomp_bpf.c` | Docstring: seccomp_bpf.c -- classic BPF checker and interpreter for Linux | kernel | 12 | 0 |
| `kernel/serial.c` | COM1 16550 UART driver. | kernel | 9 | 0 |
| `kernel/shell.c` | ShellRunDir: Runnable-file lookup: a bare name is mapped to a toolchain directory by its suffix... | kernel | 97 | 0 |
| `kernel/spawn.c` | Docstring: Save the caller shared-window view into ctx. | kernel | 9 | 0 |
| `kernel/string.c` | Kernel string and memory functions. | kernel | 13 | 85 |
| `kernel/symtab.c` | - | kernel | 7 | 0 |
| `kernel/sync.c` | Blocking synchronization primitives (roadmap Phase 3.1). | kernel | 26 | 0 |
| `kernel/syscalls.c` | Linux x86-64 syscall dispatcher and SYS_SPAWN. | kernel | 237 | 0 |
| `kernel/syscalls_proc.c` | Process-management syscall handlers. | kernel | 24 | 0 |
| `kernel/tick.c` | Docstring: Tick listener bus implementation. | kernel | 11 | 0 |
| `kernel/time.c` | ktime_us: Microsecond resolution over the same calibrated ratio (Phase 0.2/0.3: clock_gettime... | kernel | 4 | 27 |
| `kernel/vga_cursor.c` | Docstring: Hardware pointer sprite layer (kernel/vga_cursor.c). | kernel | 13 | 0 |
| `kernel/vga_fb.c` | wm_geom_cfg: /** Docstring: Focus ids share one space across terminals and graphics.... | kernel | 200 | 0 |
| `kernel/vga_fx.c` | DOOM-melt desktop effects (see headers/vga_fx.h for the contract). | kernel | 9 | 0 |
| `mcp/__init__.py` | - | mcp | 0 | 0 |
| `mcp/mcp_dbg_driver.py` | Debug driver: boot MiniOS through the MCP bridge and run freedom. | mcp | 6 | 0 |
| `mcp/mcp_dogfood.py` | Dogfood: drive minios_mcp.py over stdio JSON-RPC and install the freedom addon from a git repo... | mcp | 6 | 0 |
| `mcp/minios_addons.py` | MiniOS addon marketplace (lazyaddons-style). | mcp | 16 | 1 |
| `mcp/minios_mcp.py` | MiniOS MCP bridge. | mcp | 51 | 0 |
| `mcp/mutate_mcp.sh` | Mutation testing for the MiniOS MCP bridge. | mcp | 1 | 0 |
| `mcp/test_minios_mcp.py` | Unit and BDD suite for the MiniOS MCP bridge. | mcp | 107 | 0 |
| `net/net.c` | MiniOS network stack: virtio-net preferred, rtl8139 fallback, under | net | 157 | 0 |
| `net/rtl8139.c` | outl_port: Byte/word port I/O comes from kernel.h (outb/inb/outw/inw, same asm). * Only the... | net | 29 | 0 |
| `net/tls.c` | TLS 1.2 client sessions for MiniOS. | net | 27 | 0 |
| `net/tls_crypto.c` | the crypto behind the kernel TLS 1.2 client. | net | 78 | 0 |
| `net/tls_x509.c` | minimal X.509 DER parsing and chain verification. | net | 23 | 0 |
| `progs/asm/aes.s` | - | asm | 30 | 0 |
| `progs/asm/cp.s` | - | asm | 2 | 0 |
| `progs/asm/fib.s` | - | asm | 3 | 0 |
| `progs/asm/freedom.s` | - | asm | 92 | 0 |
| `progs/asm/http.s` | - | asm | 3 | 0 |
| `progs/asm/json.s` | - | asm | 32 | 0 |
| `progs/asm/ldhello.s` | - | asm | 2 | 0 |
| `progs/asm/lz4.s` | - | asm | 7 | 0 |
| `progs/asm/lzss.s` | - | asm | 30 | 0 |
| `progs/asm/mtop.s` | - | asm | 36 | 0 |
| `progs/asm/w1.s` | - | asm | 2 | 0 |
| `progs/doomedit/doomedit.c` | tile map editor that builds playable Doom PWADs. | misc | 108 | 0 |
| `progs/doomgeneric/am_map.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 87 | 0 |
| `progs/doomgeneric/am_map.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 8 | 5 |
| `progs/doomgeneric/config.h` | config.hin. | doomgeneric | 16 | 11 |
| `progs/doomgeneric/d_englsh.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 286 | 1 |
| `progs/doomgeneric/d_event.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 3 | 0 |
| `progs/doomgeneric/d_event.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 4 | 13 |
| `progs/doomgeneric/d_items.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 0 | 0 |
| `progs/doomgeneric/d_items.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 3 | 2 |
| `progs/doomgeneric/d_iwad.c` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it... | doomgeneric | 27 | 0 |
| `progs/doomgeneric/d_iwad.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it... | doomgeneric | 14 | 4 |
| `progs/doomgeneric/d_loop.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 18 | 0 |
| `progs/doomgeneric/d_loop.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 10 | 4 |
| `progs/doomgeneric/d_main.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 29 | 0 |
| `progs/doomgeneric/d_main.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 8 | 6 |
| `progs/doomgeneric/d_mode.c` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it... | doomgeneric | 6 | 0 |
| `progs/doomgeneric/d_mode.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 3 | 6 |
| `progs/doomgeneric/d_net.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 8 | 0 |
| `progs/doomgeneric/d_player.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 5 | 4 |
| `progs/doomgeneric/d_textur.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 2 | 0 |
| `progs/doomgeneric/d_think.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 4 | 3 |
| `progs/doomgeneric/d_ticcmd.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 2 | 6 |
| `progs/doomgeneric/deh_main.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it... | doomgeneric | 12 | 19 |
| `progs/doomgeneric/deh_misc.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it... | doomgeneric | 49 | 5 |
| `progs/doomgeneric/deh_str.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it... | doomgeneric | 11 | 7 |
| `progs/doomgeneric/doom.h` | - | doomgeneric | 2 | 0 |
| `progs/doomgeneric/doomdata.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 11 | 2 |
| `progs/doomgeneric/doomdef.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 0 | 0 |
| `progs/doomgeneric/doomdef.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 9 | 41 |
| `progs/doomgeneric/doomfeatures.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it... | doomgeneric | 2 | 11 |
| `progs/doomgeneric/doomgeneric.c` | - | doomgeneric | 1 | 0 |
| `progs/doomgeneric/doomgeneric.h` | - | doomgeneric | 10 | 11 |
| `progs/doomgeneric/doomgeneric_minios.c` | MiniOS platform layer for doomgeneric. | doomgeneric | 29 | 0 |
| `progs/doomgeneric/doomgeneric_sdl.c` | doomgeneric for soso os | doomgeneric | 10 | 0 |
| `progs/doomgeneric/doomgeneric_soso.c` | doomgeneric for soso os | doomgeneric | 13 | 0 |
| `progs/doomgeneric/doomgeneric_sosox.c` | doomgeneric for soso os (nano-x version) TODO: get keys from X, not using direct keyboard access! | doomgeneric | 12 | 0 |
| `progs/doomgeneric/doomgeneric_win.c` | - | doomgeneric | 10 | 0 |
| `progs/doomgeneric/doomgeneric_xlib.c` | - | doomgeneric | 9 | 0 |
| `progs/doomgeneric/doomkeys.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 59 | 17 |
| `progs/doomgeneric/doomstat.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 0 | 0 |
| `progs/doomgeneric/doomstat.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 68 | 34 |
| `progs/doomgeneric/doomtype.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 14 | 50 |
| `progs/doomgeneric/dstrings.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 0 | 0 |
| `progs/doomgeneric/dstrings.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 5 | 11 |
| `progs/doomgeneric/dummy.c` | - | doomgeneric | 1 | 0 |
| `progs/doomgeneric/f_finale.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 18 | 0 |
| `progs/doomgeneric/f_finale.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 4 | 2 |
| `progs/doomgeneric/f_wipe.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 10 | 0 |
| `progs/doomgeneric/f_wipe.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 4 | 2 |
| `progs/doomgeneric/g_game.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 54 | 0 |
| `progs/doomgeneric/g_game.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 22 | 11 |
| `progs/doomgeneric/gusconf.c` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it... | doomgeneric | 10 | 0 |
| `progs/doomgeneric/gusconf.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it... | doomgeneric | 3 | 1 |
| `progs/doomgeneric/hu_lib.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 22 | 0 |
| `progs/doomgeneric/hu_lib.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 24 | 2 |
| `progs/doomgeneric/hu_stuff.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 24 | 0 |
| `progs/doomgeneric/hu_stuff.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 17 | 6 |
| `progs/doomgeneric/i_cdmus.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 9 | 0 |
| `progs/doomgeneric/i_cdmus.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 18 | 1 |
| `progs/doomgeneric/i_endoom.c` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it... | doomgeneric | 3 | 0 |
| `progs/doomgeneric/i_endoom.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 2 | 1 |
| `progs/doomgeneric/i_input.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 5 | 0 |
| `progs/doomgeneric/i_joystick.c` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it... | doomgeneric | 10 | 0 |
| `progs/doomgeneric/i_joystick.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it... | doomgeneric | 18 | 4 |
| `progs/doomgeneric/i_main.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 4 | 0 |
| `progs/doomgeneric/i_minios_sound.c` | audio_pump: SFX are muted on pcm2 (music only): effect tones ruined the melody, so audio_pump... | doomgeneric | 54 | 0 |
| `progs/doomgeneric/i_scale.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 39 | 0 |
| `progs/doomgeneric/i_scale.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 18 | 1 |
| `progs/doomgeneric/i_sound.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 34 | 0 |
| `progs/doomgeneric/i_sound.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 30 | 5 |
| `progs/doomgeneric/i_swap.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 8 | 14 |
| `progs/doomgeneric/i_system.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 21 | 0 |
| `progs/doomgeneric/i_system.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 12 | 38 |
| `progs/doomgeneric/i_timer.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 6 | 0 |
| `progs/doomgeneric/i_timer.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 7 | 9 |
| `progs/doomgeneric/i_video.c` | Emacs style mode select   -*- C++ -*- | doomgeneric | 31 | 0 |
| `progs/doomgeneric/i_video.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 41 | 18 |
| `progs/doomgeneric/icon.c` | - | doomgeneric | 0 | 0 |
| `progs/doomgeneric/info.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 74 | 0 |
| `progs/doomgeneric/info.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 6 | 4 |
| `progs/doomgeneric/m_argv.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 7 | 0 |
| `progs/doomgeneric/m_argv.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 7 | 24 |
| `progs/doomgeneric/m_bbox.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 2 | 0 |
| `progs/doomgeneric/m_bbox.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 3 | 7 |
| `progs/doomgeneric/m_cheat.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 2 | 0 |
| `progs/doomgeneric/m_cheat.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 7 | 5 |
| `progs/doomgeneric/m_config.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 26 | 0 |
| `progs/doomgeneric/m_config.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 12 | 7 |
| `progs/doomgeneric/m_controls.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 9 | 0 |
| `progs/doomgeneric/m_controls.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 119 | 5 |
| `progs/doomgeneric/m_fixed.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 2 | 0 |
| `progs/doomgeneric/m_fixed.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 6 | 9 |
| `progs/doomgeneric/m_menu.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 68 | 0 |
| `progs/doomgeneric/m_menu.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 7 | 5 |
| `progs/doomgeneric/m_misc.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 22 | 0 |
| `progs/doomgeneric/m_misc.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 14 | 25 |
| `progs/doomgeneric/m_random.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 3 | 0 |
| `progs/doomgeneric/m_random.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 4 | 13 |
| `progs/doomgeneric/memio.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 9 | 0 |
| `progs/doomgeneric/memio.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 10 | 1 |
| `progs/doomgeneric/net_client.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it... | doomgeneric | 21 | 2 |
| `progs/doomgeneric/net_dedicated.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it... | doomgeneric | 2 | 1 |
| `progs/doomgeneric/net_defs.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it... | doomgeneric | 28 | 9 |
| `progs/doomgeneric/net_gui.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it... | doomgeneric | 2 | 1 |
| `progs/doomgeneric/net_io.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it... | doomgeneric | 9 | 1 |
| `progs/doomgeneric/net_loop.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it... | doomgeneric | 3 | 1 |
| `progs/doomgeneric/net_packet.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it... | doomgeneric | 9 | 0 |
| `progs/doomgeneric/net_query.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it... | doomgeneric | 12 | 2 |
| `progs/doomgeneric/net_sdl.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it... | doomgeneric | 2 | 1 |
| `progs/doomgeneric/net_server.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it... | doomgeneric | 6 | 1 |
| `progs/doomgeneric/p_ceilng.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 6 | 0 |
| `progs/doomgeneric/p_doors.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 10 | 0 |
| `progs/doomgeneric/p_enemy.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 68 | 0 |
| `progs/doomgeneric/p_floor.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 4 | 0 |
| `progs/doomgeneric/p_inter.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 10 | 0 |
| `progs/doomgeneric/p_inter.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 1 | 2 |
| `progs/doomgeneric/p_lights.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 11 | 0 |
| `progs/doomgeneric/p_local.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 91 | 24 |
| `progs/doomgeneric/p_map.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 24 | 0 |
| `progs/doomgeneric/p_maputl.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 19 | 0 |
| `progs/doomgeneric/p_mobj.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 21 | 0 |
| `progs/doomgeneric/p_mobj.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 3 | 4 |
| `progs/doomgeneric/p_plats.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 6 | 0 |
| `progs/doomgeneric/p_pspr.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 35 | 0 |
| `progs/doomgeneric/p_pspr.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 4 | 2 |
| `progs/doomgeneric/p_saveg.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 58 | 0 |
| `progs/doomgeneric/p_saveg.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 16 | 4 |
| `progs/doomgeneric/p_setup.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 17 | 0 |
| `progs/doomgeneric/p_setup.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 3 | 2 |
| `progs/doomgeneric/p_sight.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 5 | 0 |
| `progs/doomgeneric/p_spec.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 31 | 0 |
| `progs/doomgeneric/p_spec.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 94 | 1 |
| `progs/doomgeneric/p_switch.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 4 | 0 |
| `progs/doomgeneric/p_telept.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 1 | 0 |
| `progs/doomgeneric/p_tick.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 6 | 0 |
| `progs/doomgeneric/p_tick.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 2 | 1 |
| `progs/doomgeneric/p_user.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 8 | 0 |
| `progs/doomgeneric/r_bsp.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 11 | 0 |
| `progs/doomgeneric/r_bsp.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 20 | 1 |
| `progs/doomgeneric/r_data.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 17 | 0 |
| `progs/doomgeneric/r_data.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 7 | 7 |
| `progs/doomgeneric/r_defs.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 25 | 3 |
| `progs/doomgeneric/r_draw.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 20 | 0 |
| `progs/doomgeneric/r_draw.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 32 | 2 |
| `progs/doomgeneric/r_local.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 1 | 15 |
| `progs/doomgeneric/r_main.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 20 | 0 |
| `progs/doomgeneric/r_main.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 36 | 2 |
| `progs/doomgeneric/r_plane.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 9 | 0 |
| `progs/doomgeneric/r_plane.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 15 | 2 |
| `progs/doomgeneric/r_segs.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 5 | 0 |
| `progs/doomgeneric/r_segs.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 2 | 1 |
| `progs/doomgeneric/r_sky.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 1 | 0 |
| `progs/doomgeneric/r_sky.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 6 | 6 |
| `progs/doomgeneric/r_state.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 45 | 17 |
| `progs/doomgeneric/r_things.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 17 | 0 |
| `progs/doomgeneric/r_things.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 22 | 2 |
| `progs/doomgeneric/s_sound.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 25 | 0 |
| `progs/doomgeneric/s_sound.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 15 | 22 |
| `progs/doomgeneric/sha1.c` | SHA1 hash function | doomgeneric | 19 | 0 |
| `progs/doomgeneric/sha1.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it... | doomgeneric | 9 | 5 |
| `progs/doomgeneric/sounds.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 3 | 0 |
| `progs/doomgeneric/sounds.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 3 | 23 |
| `progs/doomgeneric/st_lib.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 11 | 0 |
| `progs/doomgeneric/st_lib.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 14 | 2 |
| `progs/doomgeneric/st_stuff.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 137 | 0 |
| `progs/doomgeneric/st_stuff.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 19 | 6 |
| `progs/doomgeneric/statdump.c` | - | doomgeneric | 11 | 0 |
| `progs/doomgeneric/statdump.h` | - | doomgeneric | 3 | 3 |
| `progs/doomgeneric/tables.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 1 | 0 |
| `progs/doomgeneric/tables.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 21 | 6 |
| `progs/doomgeneric/v_patch.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 2 | 2 |
| `progs/doomgeneric/v_video.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 32 | 0 |
| `progs/doomgeneric/v_video.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 27 | 15 |
| `progs/doomgeneric/w_checksum.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 3 | 0 |
| `progs/doomgeneric/w_checksum.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 2 | 2 |
| `progs/doomgeneric/w_file.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 6 | 0 |
| `progs/doomgeneric/w_file.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 7 | 3 |
| `progs/doomgeneric/w_file_stdc.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 5 | 0 |
| `progs/doomgeneric/w_main.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 1 | 0 |
| `progs/doomgeneric/w_main.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it... | doomgeneric | 1 | 2 |
| `progs/doomgeneric/w_merge.h` | Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it... | doomgeneric | 7 | 1 |
| `progs/doomgeneric/w_wad.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 16 | 0 |
| `progs/doomgeneric/w_wad.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 17 | 27 |
| `progs/doomgeneric/wi_stuff.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 68 | 0 |
| `progs/doomgeneric/wi_stuff.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 5 | 3 |
| `progs/doomgeneric/z_zone.c` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 18 | 0 |
| `progs/doomgeneric/z_zone.h` | Copyright(C) 1993-1996 Id Software, Inc. | doomgeneric | 13 | 40 |
| `progs/file/file.c` | Docstring: MiniOS file browser (Nuklear ring-3 app, MiniFS: file/file.elf). | file | 65 | 0 |
| `progs/file/file_assoc.h` | Docstring: dynamic association table for the MiniOS file browser. | file | 17 | 3 |
| `progs/freedomui/freedomui_minios.c` | freedomui_minios - Real FreeDom browser on MiniOS, DOOM/Q2G pattern. | freedomui | 42 | 1 |
| `progs/freedomui/media_unavailable.c` | FreeDom media decoder entry points for a build | freedomui | 2 | 0 |
| `progs/freedomui/platform_minios.c` | MiniOS implementation of FreeDom's gui/platform.h. | freedomui | 43 | 0 |
| `progs/freedomui/ps2_keymap.c` | pure PS/2 set 1 scancode to keysym translator (US layout). | freedomui | 82 | 0 |
| `progs/freedomui/ps2_keymap.h` | pure PS/2 set 1 scancode to keysym translator (US layout). | freedomui | 13 | 3 |
| `progs/lisp/lisp.c` | Node: Runtime value node with one payload per type. | lisp | 105 | 0 |
| `progs/lisp/tin.c` | - | lisp | 1 | 0 |
| `progs/lua/lua_main.c` | - | lua | 7 | 0 |
| `progs/lua/minios.c` | msys5: /* ── raw syscall helpers (x86-64 Linux ABI) ─────────────────────────── static long... | lua | 17 | 3 |
| `progs/micropython/variants/minios/lib/__init__.py` | MiniOS frozen library package. | lib | 0 | 0 |
| `progs/micropython/variants/minios/lib/hello.py` | frozen demo: runs at import time as a smoke test. | lib | 0 | 0 |
| `progs/micropython/variants/minios/manifest.py` | frozen modules for the MiniOS MicroPython variant. | minios | 0 | 0 |
| `progs/micropython/variants/minios/minios_module.c` | msys5: /* ── raw syscall helper (x86-64 Linux ABI) ─────────────────────────── static long... | minios | 21 | 0 |
| `progs/micropython/variants/minios/mpconfigvariant.h` | - | minios | 38 | 0 |
| `progs/minicraft/minicraft.c` | Minecraft-like voxel walker for MiniOS (ring 3, static ELF). | misc | 237 | 0 |
| `progs/minios_abi.h` | Single source of truth for the MiniOS user-kernel ABI. | progs | 153 | 30 |
| `progs/minios_png.h` | Docstring: shared ring-3 PNG helpers for MiniOS apps (progs/minios_png.h). | progs | 21 | 3 |
| `progs/nk_palette.h` | one shared hybrid palette for every NK-window app. | progs | 9 | 5 |
| `progs/nuklear/cvm_emit.c` | — node-graph to CVM bytecode compiler. | nuklear | 56 | 0 |
| `progs/nuklear/cvm_emit.h` | — node-graph compiler for CVM (cvm2 module format v2). | nuklear | 6 | 2 |
| `progs/nuklear/font8x8.c` | font8x8 - shared 8x8 bitmap font for MiniOS ring-3 graphics programs. | nuklear | 0 | 0 |
| `progs/nuklear/node_editor.c` | — visual low-code editor that compiles to CVM bytecode. | nuklear | 34 | 0 |
| `progs/nuklear/nuklear_minios.c` | — MiniOS platform layer for Nuklear. | nuklear | 52 | 0 |
| `progs/nuklear/nuklear_minios.h` | — MiniOS platform layer for Nuklear. | nuklear | 29 | 8 |
| `progs/nuklear/nuklear_theme.c` | Docstring: shared Nuklear theme loader, linked by every NK app. | nuklear | 7 | 0 |
| `progs/nuklear/nuklear_theme.h` | Docstring: shared Nuklear theme contract for every MiniOS NK app. | nuklear | 13 | 8 |
| `progs/paint/paint.c` | Docstring: MiniOS paint program (Nuklear ring-3 app, MiniFS: paint/paint.elf). | misc | 53 | 0 |
| `progs/piano/piano.c` | — a Nuklear piano that plays FM sound through the SB16 driver. | misc | 65 | 0 |
| `progs/pokemon/fetch.sh` | clone the gb-recompiled tool into progs/pokemon/upstream. | pokemon | 0 | 0 |
| `progs/pokemon/minios_stubs/SDL.h` | stub for MiniOS cross-compilation | misc | 10 | 4 |
| `progs/pokemon/platform_minios.c` | push_332_palette: 3-3-2 RGB palette ramp, pushed ONCE at init (not per frame). * Pixel index =... | pokemon | 111 | 0 |
| `progs/quake2generic/q2generic_minios.c` | MiniOS platform layer for quake2generic. | quake2generic | 34 | 0 |
| `progs/quake2generic/snddma_minios.c` | Quake 2 DMA sound backend over the MiniOS pcm2 path. | quake2generic | 16 | 0 |
| `progs/src/aes.c` | command path AES-256-CTR encryption tools: aes and unaes. | src | 54 | 0 |
| `progs/src/aslr.c` | aslr -- userspace ASLR probe (self-exec chain). | src | 10 | 0 |
| `progs/src/audio.c` | - | src | 17 | 0 |
| `progs/src/burn.c` | burn -- SMP mixed-workload probe: brk plus mmap plus CPU burn with | src | 7 | 0 |
| `progs/src/cp.c` | - | src | 8 | 0 |
| `progs/src/cpl.c` | Ring-3 privilege probe. | src | 3 | 0 |
| `progs/src/execho.c` | execho -- fork(57) + execve(59) + wait4(61) probe. | src | 6 | 0 |
| `progs/src/execthr.c` | execthr -- execve kills sibling threads (Linux semantics). | src | 4 | 0 |
| `progs/src/fib.c` | - | src | 2 | 0 |
| `progs/src/forktest.c` | - | src | 14 | 0 |
| `progs/src/fptest.c` | FPU/SSE context-switch probe (Phase 0.1, ADR-0014). | src | 9 | 0 |
| `progs/src/freedom.c` | freedom - a headless text browser for MiniOS. | src | 61 | 0 |
| `progs/src/freedom_wl.c` | freedom_wl - Wayland to MiniOS intermediate layer for FreeDom. | src | 62 | 1 |
| `progs/src/ftest.c` | Exercises the kernel libc surface used by loaded .o programs: | src | 9 | 0 |
| `progs/src/hello.c` | MiniOS test program — compiled as relocatable .o, loaded by kernel ELF loader | src | 2 | 0 |
| `progs/src/hello.py` | - | src | 0 | 0 |
| `progs/src/http.c` | Minimal HTTP/1.0 GET through the Linux socket syscalls. | src | 13 | 0 |
| `progs/src/json.c` | command path JSON tool: validate, pretty-print and query. | src | 41 | 0 |
| `progs/src/kmem.c` | Kernel-pointer rejection probe. | src | 3 | 0 |
| `progs/src/ldhello.c` | - | src | 1 | 0 |
| `progs/src/lxabi.c` | Linux process, thread and descriptor ABI probe (FreeDom | src | 57 | 0 |
| `progs/src/lxhello.c` | lmain: static void lx_write_int(long v) { char buf[24]; int i = (int)sizeof(buf); int neg = 0... | src | 7 | 0 |
| `progs/src/lxnet.c` | Linux socket ABI probe (FreeDom readiness step 6, | src | 16 | 0 |
| `progs/src/lxsecc.c` | Linux seccomp-bpf, prctl and /proc/self/exe probe (FreeDom | src | 30 | 0 |
| `progs/src/lxtls.c` | libcurl/OpenSSL fetch probe (FreeDom readiness step 6, | src | 10 | 0 |
| `progs/src/lz4.c` | command path LZ4 (de)compression tools: lz4 and unlz4. | src | 26 | 0 |
| `progs/src/lzss.c` | command path LZSS (de)compression tools: lzss and unlzss. | src | 48 | 0 |
| `progs/src/mmreuse.c` | mmap/munmap reclaim stress test. | src | 5 | 0 |
| `progs/src/mprot.c` | mprotect probe. | src | 5 | 0 |
| `progs/src/mthreads.h` | Minimal pthread-like threads for MiniOS ELFs (roadmap | src | 20 | 3 |
| `progs/src/mtop.c` | ASCII real-time system monitor for MiniOS. | src | 39 | 0 |
| `progs/src/mvrn.c` | mvrn -- rename(82) syscall probe. | src | 5 | 0 |
| `progs/src/nx.c` | NX probe. | src | 3 | 0 |
| `progs/src/opl3.c` | opl3_set_instrument: } static long sys_open(long on) { long r; __asm__... | src | 18 | 1 |
| `progs/src/pcmap.c` | pcmap probe: file-backed MAP_PRIVATE mmap shares text. | src | 8 | 0 |
| `progs/src/pollready.c` | lmain: int v = 0; int digits = 0; while (*s >= '0' && *s <= '9') { v = v * 10 + (*s - '0'); s++... | src | 6 | 0 |
| `progs/src/sbtone.c` | — headless SB16 diagnostic (ring-3, no GUI). | src | 8 | 0 |
| `progs/src/scfuzz.c` | scfuzz: deterministic syscall fuzzer (syzkaller spirit, BDD scale). | src | 19 | 0 |
| `progs/src/shell.py` | pybash: a Python shell layer on top of MiniOS's C shell. | src | 3 | 0 |
| `progs/src/spin.c` | - | src | 19 | 0 |
| `progs/src/test.c` | - | src | 2 | 0 |
| `progs/src/test.lua` | - | src | 20 | 0 |
| `progs/src/test.py` | in-OS test suite for MiniOS, driven by MicroPython. | src | 20 | 0 |
| `progs/src/test_all.sh` | comprehensive non-interactive test suite for MiniOS. | src | 0 | 0 |
| `progs/src/thdemo.c` | Producer-consumer over mthreads (roadmap Phase 1, M1). | src | 10 | 0 |
| `progs/src/w1.c` | - | src | 2 | 0 |
| `progs/tls_u/tls_u_main.c` | tlsget - minimal HTTPS GET over the ring-3 TLS stack. | tls_u | 5 | 0 |
| `progs/tls_u/tls_u_port.c` | ring-3 transport for the shared TLS stack (TLS_RING3). | tls_u | 15 | 0 |
| `progs/topogpt3/topogpt3.c` | FILE: topogpt3 -p "prompt" [-n N] [-t T]   Headless mode topogpt3 -i... | misc | 128 | 0 |
| `progs/vedit/vedit.c` | vedit IDE build and run contract. | misc | 243 | 0 |
| `progs/wl/wl_client.h` | Thin mailbox client for Wayland-mini (ADR-0026). | wl | 5 | 2 |
| `progs/wl/wl_mbox.h` | Mailbox file transport for Wayland-mini (ADR-0026). | wl | 26 | 4 |
| `progs/wl/wl_mini.h` | Wayland-mini subset contract (header-only, ADR-0024). | wl | 111 | 4 |
| `progs/wl/wl_pixbuf.h` | Docstring: heap pixel store for the Wayland-mini server. | wl | 18 | 2 |
| `progs/wl/wlcomp.c` | wlcomp - Wayland-mini ring-3 compositor (ADR-0024, ADR-0026). | wl | 47 | 0 |
| `qga.c` | MiniOS QEMU guest agent (QGA). | root | 27 | 0 |
| `smp.c` | SMP application-processor bring-up. | root | 39 | 0 |
| `tests/host_aes.sh` | host-side verification for the AES-256-CTR command tools. | tests | 3 | 0 |
| `tests/host_codecs.sh` | reusable host-side verification for the in-OS codec tools. | tests | 5 | 0 |
| `tests/stubs/kernel.h` | Docstring: Host-test stand-in for headers/kernel.h (tests/stubs first on | misc | 15 | 0 |
| `tests/test_abi.c` | Docstring: tests/test_abi.c -- Host test for the ABI manifest gate. | tests | 2 | 0 |
| `tests/test_arena.c` | Docstring: host test for the bump arena (make test-arena). | tests | 2 | 0 |
| `tests/test_batch.c` | Docstring: Host test for kernel/batch.c (make test-batch). | tests | 3 | 0 |
| `tests/test_doom_pwad.py` | host contract suite for tools/doom_pwad.py. | tests | 44 | 0 |
| `tests/test_driver.c` | Host test for the Strategy-pattern device registry. | tests | 5 | 0 |
| `tests/test_ext4.c` | Docstring: Host test for the ext4 loopback driver (make test-ext4). | tests | 31 | 0 |
| `tests/test_fat32.c` | Docstring: Host test for the FAT32 loopback driver (make test-fat). | tests | 29 | 0 |
| `tests/test_fault.c` | fault-injection suite (boyscout gap #10). | tests | 11 | 0 |
| `tests/test_file_assoc.c` | Docstring: host test for the file browser assoc contract (make test-file). | tests | 10 | 0 |
| `tests/test_freedom_wl.c` | test_freedom_wl - host suite for the Wayland to MiniOS mapping. | tests | 3 | 0 |
| `tests/test_freedomui.c` | test_freedomui - host suite for the real FreeDom MiniOS backend. | tests | 2 | 0 |
| `tests/test_futex.c` | Docstring: Host test for kernel/futex.c (make test-futex). | tests | 7 | 0 |
| `tests/test_fx.c` | Docstring: Host test for headers/vga_fx.h (make test-fx). | tests | 2 | 0 |
| `tests/test_hal_io.c` | Docstring: Host test for arch/x86/hal_io.h (make test-hal). | tests | 3 | 0 |
| `tests/test_httpd.c` | Docstring: Host test for headers/httpd.h (make test-httpd). | tests | 2 | 0 |
| `tests/test_ktime.c` | host test for the pure conversion math in ktime.h | tests | 2 | 0 |
| `tests/test_ldso.c` | Docstring: host test for the ld.so pure parser (make test-ldso). | tests | 12 | 0 |
| `tests/test_leakcheck.c` | Docstring: host test for the leak tracker (make test-leakcheck). | tests | 4 | 0 |
| `tests/test_minifs_tools.py` | Host suite for the MiniFS image tools (docs/spec/shell-fs.md).  tools/mkfs.minifs.py builds the... | tests | 12 | 0 |
| `tests/test_minios_png.c` | Docstring: host test for the shared ring-3 PNG helpers (make test-png). | tests | 10 | 0 |
| `tests/test_modifiers.c` | Docstring: Designated initializers, so adding a member cannot silently | tests | 2 | 0 |
| `tests/test_notify.c` | - | tests | 3 | 0 |
| `tests/test_paint.c` | Docstring: host test for the paint canvas/PNG contract (make test-paint). | tests | 21 | 0 |
| `tests/test_panic.c` | Docstring: Host test for headers/panic.h (make test-panic). | tests | 5 | 0 |
| `tests/test_pcache.c` | Docstring: host test for the page cache store (make test-pcache). | tests | 5 | 0 |
| `tests/test_pci.c` | Docstring: Host test for headers/drivers/pci.h (make test-pci). | tests | 7 | 0 |
| `tests/test_pcm.c` | Host-side unit test for the PCM ring buffer (headers/pcm_ring.h). | tests | 9 | 0 |
| `tests/test_percpu_rq.c` | Docstring: Host test for kernel/percpu_rq.c (make test-percpu-rq). | tests | 2 | 0 |
| `tests/test_pipe.c` | Docstring: Host test for headers/pipe.h (make test-pipe). | tests | 2 | 0 |
| `tests/test_ps2_keymap.c` | test_ps2_keymap - host suite for the PS/2 set 1 to keysym translator. | tests | 15 | 0 |
| `tests/test_randmix.c` | host test for the getrandom mixer in randmix.h | tests | 3 | 0 |
| `tests/test_rcu.c` | Docstring: Host test for kernel/rcu.c (make test-rcu). | tests | 4 | 0 |
| `tests/test_rtc.c` | host test for the pure date math in drivers/rtc.c | tests | 2 | 0 |
| `tests/test_sanitize.c` | Docstring: Host test for sanitize.h (make test-sanitize). | tests | 9 | 0 |

Next: [INDEX_p2.md](INDEX_p2.md)
