# GraphRAG Community Reports

Entities: 14130 | Relationships: 26104 | Communities: 10 | Themes: 4 | Text units: 13881

Query with `readmenator . ask "<question>"` (local: BM25 + Personalized PageRank; global: map-reduce over these reports) or the MCP tool `readmenator.graphrag`.

## Project overview (`root`, root, rating 7.0)

602 files in 10 communities and 4 themes. Highest-impact communities: headers: kernel (7.0), progs/doomgeneric: d_englsh (6.2), progs/src (4.4). God nodes: kernel/string.c, progs/doomgeneric/doomtype.h, progs/doomgeneric/doomdef.h, kernel/syscalls.c, progs/doomgeneric/doomstat.h.

- [headers: kernel] rating 7.0: `headers/spinlock.h` ranks 1 by PageRank, 9 importers, 19 symbols: Lightweight spinlock for MiniOS kernel.
- [progs/doomgeneric: d_englsh] rating 6.2: `progs/doomgeneric/doomtype.h` ranks 1 by PageRank, 50 importers, 14 symbols: Copyright(C) 1993-1996 Id Software, Inc.
- [progs/src] rating 4.4: `kernel/string.c` ranks 1 by PageRank, 91 importers, 18 symbols: Kernel string and memory functions.
- [progs/doomgeneric: p_spec] rating 4.2: `progs/doomgeneric/doomdef.h` ranks 1 by PageRank, 41 importers, 9 symbols: Copyright(C) 1993-1996 Id Software, Inc.
- [unassigned files] rating 3.3: `arch/x86/ctx_sw.S` ranks 1 by PageRank, 0 importers, 9 symbols: sched_park_capture: captured the rest.
- [tools: lxabi] rating 2.5: `kernel/time.c` ranks 1 by PageRank, 33 importers, 4 symbols: ktime_us: Microsecond resolution over the same calibrated ratio (Phase 0.2/0.3: clock_gettime nsec and gettimeofday usec both derive from here, so the * two clocks share one source and never disagree about ordering).
- [headers: vga_fb] rating 1.1: `headers/wm_notify.h` ranks 1 by PageRank, 4 importers, 9 symbols: Docstring: Focus event bus for the MiniOS desktop.
- [progs/doomgeneric: net_defs] rating 0.9: `progs/doomgeneric/net_defs.h` ranks 1 by PageRank, 9 importers, 28 symbols: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the...
- Key entities: file:headers/kernel.h, file:kernel/syscalls.c, file:progs/doomgeneric/d_englsh.h, file:progs/doomgeneric/st_stuff.c, file:progs/vedit/vedit.c, file:progs/minicraft/minicraft.c
- Children: t0, t1, t2, t3
- Root rating = highest community rating.

## headers: kernel + progs/src +3 (`t0`, theme, rating 7.0)

Theme of 5 communities and 301 files: headers: kernel (146 files, rating 7.0); progs/src (77 files, rating 4.4); tools: lxabi (37 files, rating 2.5); headers: vga_fb (27 files, rating 1.1); net (14 files, rating 0.6).

- [headers: kernel] `headers/spinlock.h` ranks 1 by PageRank, 9 importers, 19 symbols: Lightweight spinlock for MiniOS kernel.
- [headers: kernel] `headers/sched.h` ranks 2 by PageRank, 28 importers, 158 symbols: Forward: full view lives in kernel.h (needs KFILE first); the PCB
- [progs/src] `kernel/string.c` ranks 1 by PageRank, 91 importers, 18 symbols: Kernel string and memory functions.
- [progs/src] `progs/minios_abi.h` ranks 2 by PageRank, 32 importers, 156 symbols: Single source of truth for the MiniOS user-kernel ABI.
- [tools: lxabi] `kernel/time.c` ranks 1 by PageRank, 33 importers, 4 symbols: ktime_us: Microsecond resolution over the same calibrated ratio (Phase 0.2/0.3: clock_gettime nsec and gettimeofday usec both derive from here, so the * two clocks share one source and never disagree about ordering).
- [tools: lxabi] `headers/ktime.h` ranks 2 by PageRank, 3 importers, 3 symbols: pure time-conversion helpers shared by the kernel clock
- [headers: vga_fb] `headers/wm_notify.h` ranks 1 by PageRank, 4 importers, 9 symbols: Docstring: Focus event bus for the MiniOS desktop.
- [headers: vga_fb] `headers/wm_geom.h` ranks 2 by PageRank, 3 importers, 11 symbols: Docstring: Window geometry contract for the MiniOS desktop.
- Key entities: file:headers/kernel.h, file:kernel/syscalls.c, file:progs/vedit/vedit.c, file:progs/minicraft/minicraft.c, file:progs/src/lxabi.c, file:tools/minios_hyper.py, file:kernel/vga_fb.c, file:headers/desktop_shortcuts.h
- Children: c0, c2, c4, c5, c6
- Theme rating = highest child community rating.

## progs/doomgeneric: d_englsh + progs/doomgeneric: p_spec +1 (`t1`, theme, rating 6.2)

Theme of 3 communities and 181 files: progs/doomgeneric: d_englsh (99 files, rating 6.2); progs/doomgeneric: p_spec (69 files, rating 4.2); progs/doomgeneric: net_defs (13 files, rating 0.9).

- [progs/doomgeneric: d_englsh] `progs/doomgeneric/doomtype.h` ranks 1 by PageRank, 50 importers, 14 symbols: Copyright(C) 1993-1996 Id Software, Inc.
- [progs/doomgeneric: d_englsh] `progs/doomgeneric/d_event.h` ranks 2 by PageRank, 13 importers, 4 symbols: Copyright(C) 1993-1996 Id Software, Inc.
- [progs/doomgeneric: p_spec] `progs/doomgeneric/doomdef.h` ranks 1 by PageRank, 41 importers, 9 symbols: Copyright(C) 1993-1996 Id Software, Inc.
- [progs/doomgeneric: p_spec] `progs/doomgeneric/m_fixed.h` ranks 2 by PageRank, 9 importers, 6 symbols: Copyright(C) 1993-1996 Id Software, Inc.
- [progs/doomgeneric: net_defs] `progs/doomgeneric/net_defs.h` ranks 1 by PageRank, 9 importers, 28 symbols: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the...
- [progs/doomgeneric: net_defs] `progs/doomgeneric/d_ticcmd.h` ranks 2 by PageRank, 6 importers, 2 symbols: Copyright(C) 1993-1996 Id Software, Inc.
- Key entities: file:progs/doomgeneric/d_englsh.h, file:progs/doomgeneric/st_stuff.c, file:progs/doomgeneric/p_local.h, file:progs/doomgeneric/p_spec.h, file:progs/doomgeneric/net_defs.h, file:progs/doomgeneric/d_loop.c
- Children: c1, c3, c7
- Theme rating = highest child community rating.

## unassigned files (`t2`, theme, rating 3.3)

Theme of 1 communities and 118 files: unassigned files (118 files, rating 3.3).

- [unassigned files] `arch/x86/ctx_sw.S` ranks 1 by PageRank, 0 importers, 9 symbols: sched_park_capture: captured the rest.
- [unassigned files] `arch/x86/isr_stubs.S` ranks 2 by PageRank, 0 importers, 24 symbols.
- Key entities: file:progs/asm/freedom.s, file:progs/asm/sign.s
- Children: c9
- Theme rating = highest child community rating.

## tools: doom_pwad (`t3`, theme, rating 0.1)

Theme of 1 communities and 2 files: tools: doom_pwad (2 files, rating 0.1).

- [tools: doom_pwad] `tools/doom_pwad.py` ranks 1 by PageRank, 3 importers, 25 symbols: grid map to vanilla Doom PWAD writer and checker.
- [tools: doom_pwad] `tests/test_doom_pwad.py` ranks 2 by PageRank, 0 importers, 44 symbols: host contract suite for tools/doom_pwad.py.
- Key entities: file:tests/test_doom_pwad.py, file:tools/doom_pwad.py
- Children: c8
- Theme rating = highest child community rating.

## headers: kernel (`c0`, community, rating 7.0)

146 files under headers (c 82, h 60, S 4), mostly utility. Core file headers/spinlock.h (PageRank 0.0117, imported by 9 files): Lightweight spinlock for MiniOS kernel. Key abstractions: spinlock_t, SPINLOCK_H, irqflags_t, SPINLOCK_INIT, spin_init, spin_save_irq. Depends on progs/src (18), net (5), headers: vga_fb (3). Used by headers: vga_fb (8), net (5), tools: lxabi (2).

- `headers/spinlock.h` ranks 1 by PageRank, 9 importers, 19 symbols: Lightweight spinlock for MiniOS kernel.
- `headers/sched.h` ranks 2 by PageRank, 28 importers, 158 symbols: Forward: full view lives in kernel.h (needs KFILE first); the PCB
- `headers/vma.h` ranks 3 by PageRank, 8 importers, 26 symbols: vma_ctx_t: Per-process VMA context (multitask foundation): every non-CLONE_VM process owns its live/free trees plus a private node pool, so two concurrent jobs never corrupt each other's mmap bookkeeping the way the old single global...
- Hotspot `kernel/syscalls.c`: 263 symbols, 65 connections (score 0.68).
- Hotspot `kernel/shell.c`: 98 symbols, 66 connections (score 0.53).
- 1 layer violations, e.g. test_httpd.c (testing) -> httpd.h (presentation).
- Dataflow: 24 INFERRED issues (first: DEAD_STORE in ahc_port_start).
- Surprising bridge: qga.h <-> d_englsh.h (9 hops across communities).
- Key entities: file:headers/kernel.h, file:kernel/syscalls.c, file:drivers/xhci.c, file:headers/sched.h, file:headers/vga_fb.h, file:headers/arch/x86/boot/bootdefs.h, file:kernel/sched.c, file:drivers/ahci.c
- Rating 7.0/10 = 7 x PageRank share 1.00 + 3 x risk 0.00. Internal imports: 322.

## progs/doomgeneric: d_englsh (`c1`, community, rating 6.2)

99 files under progs/doomgeneric (h 50, c 49), mostly utility. Core file progs/doomgeneric/doomtype.h (PageRank 0.0585, imported by 50 files): Copyright(C) 1993-1996 Id Software, Inc. Key abstractions: strcasecmp, strncasecmp, PACKEDATTR, PACKEDATTR, boolean, byte. Depends on progs/doomgeneric: p_spec (77), progs/src (21), progs/doomgeneric: net_defs (6). Used by progs/doomgeneric: p_spec (70), progs/doomgeneric: net_defs (12), progs/src (3).

- `progs/doomgeneric/doomtype.h` ranks 1 by PageRank, 50 importers, 14 symbols: Copyright(C) 1993-1996 Id Software, Inc.
- `progs/doomgeneric/d_event.h` ranks 2 by PageRank, 13 importers, 4 symbols: Copyright(C) 1993-1996 Id Software, Inc.
- `progs/doomgeneric/z_zone.h` ranks 3 by PageRank, 40 importers, 13 symbols: Copyright(C) 1993-1996 Id Software, Inc.
- Hotspot `progs/doomgeneric/d_main.c`: 29 symbols, 81 connections (score 0.56).
- Hotspot `progs/doomgeneric/g_game.c`: 54 symbols, 70 connections (score 0.51).
- Dataflow: 6 INFERRED issues (first: UNCHECKED_ALLOC in GetRegistryString).
- Surprising bridge: qga.h <-> d_englsh.h (9 hops across communities).
- Key entities: file:progs/doomgeneric/d_englsh.h, file:progs/doomgeneric/st_stuff.c, file:progs/doomgeneric/m_controls.h, file:progs/doomgeneric/am_map.c, file:progs/doomgeneric/m_menu.c, file:progs/doomgeneric/wi_stuff.c, file:progs/doomgeneric/g_game.c, file:progs/doomgeneric/doomkeys.h
- Rating 6.2/10 = 7 x PageRank share 0.88 + 3 x risk 0.00. Internal imports: 379.

## progs/src (`c2`, community, rating 4.4)

77 files under progs/src (c 56, h 21), mostly utility. Core file kernel/string.c (PageRank 0.0350, imported by 91 files): Kernel string and memory functions. Key abstractions: kstrlen, kstrcpy, kstrncpy, kstrncat, kstrcmp, kstrncmp. Depends on progs/doomgeneric: d_englsh (3), headers: kernel (1), progs/doomgeneric: p_spec (1). Used by progs/doomgeneric: d_englsh (21), headers: kernel (18), progs/doomgeneric: p_spec (4).

- `kernel/string.c` ranks 1 by PageRank, 91 importers, 18 symbols: Kernel string and memory functions.
- `progs/minios_abi.h` ranks 2 by PageRank, 32 importers, 156 symbols: Single source of truth for the MiniOS user-kernel ABI.
- `progs/wl/wl_mini.h` ranks 3 by PageRank, 4 importers, 111 symbols: Wayland-mini subset contract (header-only, ADR-0024).
- Hotspot `kernel/string.c`: 18 symbols, 92 connections (score 0.62).
- Hotspot `progs/minios_abi.h`: 156 symbols, 35 connections (score 0.38).
- Dataflow: 6 INFERRED issues (first: DEAD_STORE in dmap_build_wad).
- Key entities: file:progs/vedit/vedit.c, file:progs/minicraft/minicraft.c, file:progs/minios_abi.h, file:progs/topogpt3/topogpt3.c, file:progs/pokemon/platform_minios.c, file:progs/wl/wl_mini.h, file:progs/doomedit/doomedit.c, file:progs/lisp/lisp.c
- Rating 4.4/10 = 7 x PageRank share 0.63 + 3 x risk 0.00. Internal imports: 134.

## progs/doomgeneric: p_spec (`c3`, community, rating 4.2)

69 files under progs/doomgeneric (c 35, h 34), mostly utility. Core file progs/doomgeneric/doomdef.h (PageRank 0.0110, imported by 41 files): Copyright(C) 1993-1996 Id Software, Inc. Key abstractions: DOOM_VERSION, DOOM_191_VERSION, RANGECHECK, MAXPLAYERS, MTF_EASY, MTF_NORMAL. Depends on progs/doomgeneric: d_englsh (70), progs/src (4), progs/doomgeneric: net_defs (4). Used by progs/doomgeneric: d_englsh (77), progs/doomgeneric: net_defs (2), progs/src (1).

- `progs/doomgeneric/doomdef.h` ranks 1 by PageRank, 41 importers, 9 symbols: Copyright(C) 1993-1996 Id Software, Inc.
- `progs/doomgeneric/m_fixed.h` ranks 2 by PageRank, 9 importers, 6 symbols: Copyright(C) 1993-1996 Id Software, Inc.
- `progs/doomgeneric/d_mode.h` ranks 3 by PageRank, 6 importers, 3 symbols: Copyright(C) 1993-1996 Id Software, Inc.
- Hotspot `progs/doomgeneric/doomstat.h`: 68 symbols, 44 connections (score 0.35).
- Hotspot `progs/doomgeneric/doomdef.h`: 9 symbols, 50 connections (score 0.33).
- Dependency cycle: r_data.h -> r_state.h -> r_data.h.
- Surprising bridge: qga.h <-> d_items.c (9 hops across communities).
- Key entities: file:progs/doomgeneric/p_local.h, file:progs/doomgeneric/p_spec.h, file:progs/doomgeneric/doomstat.h, file:progs/doomgeneric/info.c, file:progs/doomgeneric/p_enemy.c, file:progs/doomgeneric/r_state.h, file:progs/doomgeneric/deh_misc.h, file:progs/quake2generic/q2generic_minios.c
- Rating 4.2/10 = 7 x PageRank share 0.60 + 3 x risk 0.00. Internal imports: 200.

## unassigned files (`c9`, community, rating 3.3)

118 files under tools (c 43, py 39, sh 17, s 13, S 3, h 2, lua 1), mostly utility. Core file arch/x86/ctx_sw.S (PageRank 0.0009, imported by 0 files): sched_park_capture: captured the rest. Key abstractions: sched_park_capture, switch_save_only, switch_to, switch_to_notrap, user_trampoline, fork_trampoline.

- `arch/x86/ctx_sw.S` ranks 1 by PageRank, 0 importers, 9 symbols: sched_park_capture: captured the rest.
- `arch/x86/isr_stubs.S` ranks 2 by PageRank, 0 importers, 24 symbols.
- `arch/x86/tlb_nmi.S` ranks 3 by PageRank, 0 importers, 1 symbols.
- Hotspot `mcp/test_minios_mcp.py`: 107 symbols, 15 connections (score 0.20).
- Hotspot `progs/asm/freedom.s`: 92 symbols, 0 connections (score 0.09).
- Taint: 4 paths reach this group via subprocess.
- Dataflow: 1 INFERRED issues (first: UNCHECKED_ALLOC in efi_main).
- Key entities: file:progs/asm/freedom.s, file:progs/asm/sign.s, file:progs/src/sign.c, file:mcp/test_minios_mcp.py, file:progs/src/aes.c, file:boot/uefi_stub.c, file:progs/src/lzss.c, file:kernel/cvm_host.c
- Rating 3.3/10 = 7 x PageRank share 0.47 + 3 x risk 0.00. Internal imports: 0.

## tools: lxabi (`c4`, community, rating 2.5)

37 files under tools (py 28, c 8, h 1), mostly utility. Core file kernel/time.c (PageRank 0.0221, imported by 33 files): ktime_us: Microsecond resolution over the same calibrated ratio (Phase 0.2/0.3: clock_gettime nsec and gettimeofday usec both derive from here, so the * two clocks share one source and never disagree about ordering). Key abstractions: ktime_rdtsc, ktime_init, ktime_ms, ktime_us, KTIME_H, ktime_us_from_delta. Depends on progs/src (4), headers: kernel (2), progs/doomgeneric: d_englsh (2). Used by headers: kernel (1), net (1).

- `kernel/time.c` ranks 1 by PageRank, 33 importers, 4 symbols: ktime_us: Microsecond resolution over the same calibrated ratio (Phase 0.2/0.3: clock_gettime nsec and gettimeofday usec both derive from here, so the * two clocks share one source and never disagree about ordering).
- `headers/ktime.h` ranks 2 by PageRank, 3 importers, 3 symbols: pure time-conversion helpers shared by the kernel clock
- `progs/lua/minios.c` ranks 3 by PageRank, 4 importers, 17 symbols: msys5: /* ── raw syscall helpers (x86-64 Linux ABI) ─────────────────────────── static long msys(long n, long a1, long a2, long a3) { long ret; __asm__ volatile( "syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2), "d"(a3) : "rcx", "r11"...
- Hotspot `kernel/time.c`: 4 symbols, 36 connections (score 0.24).
- Hotspot `progs/src/lxabi.c`: 61 symbols, 26 connections (score 0.23).
- Taint: 16 paths reach this group via subprocess.
- Key entities: file:progs/src/lxabi.c, file:tools/minios_hyper.py, file:mcp/minios_mcp.py, file:progs/lua/minios.c, file:progs/tls_u/tls_u_port.c, file:kernel/time.c, file:tools/test_gui_freedom.py, sym:tools/minios_hyper.py::encode@77
- Rating 2.5/10 = 7 x PageRank share 0.35 + 3 x risk 0.00. Internal imports: 44.

## headers: vga_fb (`c5`, community, rating 1.1)

27 files under headers (h 17, c 10), mostly utility. Core file headers/wm_notify.h (PageRank 0.0035, imported by 4 files): Docstring: Focus event bus for the MiniOS desktop. Key abstractions: wm_notify_event_t, wm_notify_bus_t, WM_NOTIFY_H, WM_NOTIFY_MAX_HANDLERS, wm_notify_reset, wm_notify_subscribe. Depends on headers: kernel (8), progs/src (1). Used by headers: kernel (3).

- `headers/wm_notify.h` ranks 1 by PageRank, 4 importers, 9 symbols: Docstring: Focus event bus for the MiniOS desktop.
- `headers/wm_geom.h` ranks 2 by PageRank, 3 importers, 11 symbols: Docstring: Window geometry contract for the MiniOS desktop.
- `headers/wm_window.h` ranks 3 by PageRank, 4 importers, 10 symbols: Docstring: Unified window contract for the MiniOS desktop.
- Hotspot `kernel/vga_fb.c`: 270 symbols, 46 connections (score 0.56).
- Hotspot `tests/test_wm.c`: 2 symbols, 17 connections (score 0.11).
- 2 layer violations, e.g. test_wm.c (testing) -> wm_render.h (presentation).
- Dataflow: 8 INFERRED issues (first: DEAD_STORE in taskbar_render).
- Key entities: file:kernel/vga_fb.c, file:headers/desktop_shortcuts.h, file:headers/vga_fx.h, file:headers/wm_layout.h, file:headers/wm_gfxview.h, file:headers/wm_chrome.h, file:headers/wm_jelly.h, file:kernel/vga_cursor.c
- Rating 1.1/10 = 7 x PageRank share 0.16 + 3 x risk 0.00. Internal imports: 35.

## progs/doomgeneric: net_defs (`c7`, community, rating 0.9)

13 files under progs/doomgeneric (h 11, c 2), mostly utility. Core file progs/doomgeneric/net_defs.h (PageRank 0.0085, imported by 9 files): Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the... Key abstractions: net_connect_data_t, net_gamesettings_t, net_ticdiff_t, net_full_ticcmd_t, net_querydata_t, net_waitdata_t. Depends on progs/doomgeneric: d_englsh (12), progs/src (2), progs/doomgeneric: p_spec (2). Used by progs/doomgeneric: d_englsh (6), progs/doomgeneric: p_spec (4).

- `progs/doomgeneric/net_defs.h` ranks 1 by PageRank, 9 importers, 28 symbols: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the...
- `progs/doomgeneric/d_ticcmd.h` ranks 2 by PageRank, 6 importers, 2 symbols: Copyright(C) 1993-1996 Id Software, Inc.
- `progs/doomgeneric/sha1.h` ranks 3 by PageRank, 5 importers, 9 symbols: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the...
- Hotspot `progs/doomgeneric/d_loop.c`: 18 symbols, 35 connections (score 0.25).
- Hotspot `progs/doomgeneric/net_defs.h`: 28 symbols, 16 connections (score 0.13).
- Key entities: file:progs/doomgeneric/net_defs.h, file:progs/doomgeneric/d_loop.c, file:progs/doomgeneric/net_client.h, file:progs/doomgeneric/sha1.c, file:progs/doomgeneric/net_query.h, file:progs/doomgeneric/sha1.h, file:progs/doomgeneric/net_io.h, file:progs/doomgeneric/net_packet.h
- Rating 0.9/10 = 7 x PageRank share 0.13 + 3 x risk 0.00. Internal imports: 19.

## net (`c6`, community, rating 0.6)

14 files under net (c 8, h 6), mostly utility. Core file headers/net.h (PageRank 0.0034, imported by 9 files): net_sys_is_socket: net_connect / socket fds are NET_FD_BASE + index for Linux syscalls and * 0..NET_SOCKETS-1 for the libc-style symbols. void net_init(void); /* Linux socket ABI entry points (kernel/syscalls.c routes to them). Key abstractions: NET_H, NET_IP_ADDR, NET_NETMASK, NET_GATEWAY, NET_DNS, NET_POLLIN. Depends on headers: kernel (5), progs/src (3), tools: lxabi (1). Used by headers: kernel (5).

- `headers/net.h` ranks 1 by PageRank, 9 importers, 103 symbols: net_sys_is_socket: net_connect / socket fds are NET_FD_BASE + index for Linux syscalls and * 0..NET_SOCKETS-1 for the libc-style symbols. void net_init(void); /* Linux socket ABI entry points (kernel/syscalls.c routes to them).
- `headers/tls.h` ranks 2 by PageRank, 6 importers, 73 symbols: tls_free_fd: Kernel built without the TLS engine (net/tls*.c unlinked): no session can ever exist, so the net.c close path needs no call.
- `headers/tls_port.h` ranks 3 by PageRank, 5 importers, 49 symbols: Portability shim between the MiniOS kernel and the host-side test
- Hotspot `net/net.c`: 157 symbols, 11 connections (score 0.22).
- Hotspot `headers/net.h`: 103 symbols, 9 connections (score 0.16).
- Dataflow: 5 INFERRED issues (first: DEAD_STORE in vnet_desc).
- Key entities: file:net/net.c, file:headers/net.h, file:net/tls_crypto.c, file:headers/tls.h, file:headers/tls_port.h, file:drivers/virtio_net.c, file:net/rtl8139.c, file:net/tls.c
- Rating 0.6/10 = 7 x PageRank share 0.09 + 3 x risk 0.00. Internal imports: 21.

## tools: doom_pwad (`c8`, community, rating 0.1)

2 files under tests (py 2), mostly testing. Core file tools/doom_pwad.py (PageRank 0.0017, imported by 3 files): grid map to vanilla Doom PWAD writer and checker. Key abstractions: DoomPwadConfig, PwadError, pad_tex, parse_grid, grid_extents, is_wall.

- `tools/doom_pwad.py` ranks 1 by PageRank, 3 importers, 25 symbols: grid map to vanilla Doom PWAD writer and checker.
- `tests/test_doom_pwad.py` ranks 2 by PageRank, 0 importers, 44 symbols: host contract suite for tools/doom_pwad.py.
- Hotspot `tests/test_doom_pwad.py`: 44 symbols, 10 connections (score 0.11).
- Hotspot `tools/doom_pwad.py`: 25 symbols, 6 connections (score 0.06).
- Key entities: file:tests/test_doom_pwad.py, file:tools/doom_pwad.py, sym:tools/doom_pwad.py::check_pwad@639, sym:tools/doom_pwad.py::parse_grid@172, sym:tools/doom_pwad.py::build_pwad@597, sym:tools/doom_pwad.py::read_pwad@616, sym:tools/doom_pwad.py::PwadError@161, sym:tools/doom_pwad.py::build_lumps@516
- Rating 0.1/10 = 7 x PageRank share 0.01 + 3 x risk 0.00. Internal imports: 3.
