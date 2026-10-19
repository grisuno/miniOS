# GraphRAG Community Reports

Entities: 13725 | Relationships: 25392 | Communities: 11 | Themes: 4 | Text units: 13479

Query with `readmenator . ask "<question>"` (local: BM25 + Personalized PageRank; global: map-reduce over these reports) or the MCP tool `readmenator.graphrag`.

## Project overview (`root`, root, rating 7.0)

587 files in 11 communities and 4 themes. Highest-impact communities: headers: kernel (7.0), progs/doomgeneric: d_englsh (6.4), progs/src (4.9). God nodes: kernel/string.c, progs/doomgeneric/doomtype.h, progs/doomgeneric/doomdef.h, kernel/syscalls.c, progs/doomgeneric/doomstat.h.

- [headers: kernel] rating 7.0: `headers/spinlock.h` ranks 1 by PageRank, 9 importers, 19 symbols: Lightweight spinlock for MiniOS kernel.
- [progs/doomgeneric: d_englsh] rating 6.4: `progs/doomgeneric/doomtype.h` ranks 1 by PageRank, 50 importers, 14 symbols: Copyright(C) 1993-1996 Id Software, Inc.
- [progs/src] rating 4.9: `kernel/string.c` ranks 1 by PageRank, 89 importers, 13 symbols: Kernel string and memory functions.
- [progs/doomgeneric: p_spec] rating 4.4: `progs/doomgeneric/doomdef.h` ranks 1 by PageRank, 41 importers, 9 symbols: Copyright(C) 1993-1996 Id Software, Inc.
- [unassigned files] rating 3.4: `arch/x86/ctx_sw.S` ranks 1 by PageRank, 0 importers, 9 symbols: sched_park_capture: captured the rest.
- [tools: tls_crypto] rating 2.8: `kernel/time.c` ranks 1 by PageRank, 32 importers, 4 symbols: ktime_us: Microsecond resolution over the same calibrated ratio (Phase 0.2/0.3: clock_gettime nsec and gettimeofday usec both derive from here, so the * two clocks share one source and never disagree about ordering).
- [progs/doomgeneric: net_defs] rating 0.9: `progs/doomgeneric/net_defs.h` ranks 1 by PageRank, 9 importers, 28 symbols: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the...
- [headers: vga_fb] rating 0.7: `headers/wm_geom.h` ranks 1 by PageRank, 3 importers, 11 symbols: Docstring: Window geometry contract for the MiniOS desktop.
- Key entities: file:headers/kernel.h, file:kernel/syscalls.c, file:progs/doomgeneric/d_englsh.h, file:progs/doomgeneric/st_stuff.c, file:progs/vedit/vedit.c, file:progs/minicraft/minicraft.c
- Children: t0, t1, t2, t3
- Root rating = highest community rating.

## headers: kernel + headers: vga_fb +2 (`t1`, theme, rating 7.0)

Theme of 4 communities and 160 files: headers: kernel (137 files, rating 7.0); headers: vga_fb (17 files, rating 0.7); headers: batch (3 files, rating 0.1); headers: tick (3 files, rating 0.1).

- [headers: kernel] `headers/spinlock.h` ranks 1 by PageRank, 9 importers, 19 symbols: Lightweight spinlock for MiniOS kernel.
- [headers: kernel] `headers/sched.h` ranks 2 by PageRank, 28 importers, 158 symbols: Forward: full view lives in kernel.h (needs KFILE first); the PCB
- [headers: vga_fb] `headers/wm_geom.h` ranks 1 by PageRank, 3 importers, 11 symbols: Docstring: Window geometry contract for the MiniOS desktop.
- [headers: vga_fb] `headers/wm_window.h` ranks 2 by PageRank, 4 importers, 10 symbols: Docstring: Unified window contract for the MiniOS desktop.
- [headers: batch] `headers/batch.h` ranks 1 by PageRank, 3 importers, 12 symbols: Docstring: batch.h -- Batched synchronous syscall submission.
- [headers: batch] `kernel/batch.c` ranks 2 by PageRank, 0 importers, 1 symbols: Docstring: kernel/batch.c -- Ordered batch executor.
- [headers: tick] `headers/tick.h` ranks 1 by PageRank, 3 importers, 16 symbols: Docstring: Tick listener bus contract.
- [headers: tick] `kernel/tick.c` ranks 2 by PageRank, 0 importers, 11 symbols: Docstring: Tick listener bus implementation.
- Key entities: file:headers/kernel.h, file:kernel/syscalls.c, file:kernel/vga_fb.c, file:headers/wm_events.h, file:headers/batch.h, file:tests/test_batch.c, file:headers/tick.h, file:kernel/tick.c
- Children: c0, c5, c7, c8
- Theme rating = highest child community rating.

## progs/doomgeneric: d_englsh + progs/src +3 (`t0`, theme, rating 6.4)

Theme of 5 communities and 310 files: progs/doomgeneric: d_englsh (99 files, rating 6.4); progs/src (85 files, rating 4.9); progs/doomgeneric: p_spec (69 files, rating 4.4); tools: tls_crypto (44 files, rating 2.8); progs/doomgeneric: net_defs (13 files, rating 0.9).

- [progs/doomgeneric: d_englsh] `progs/doomgeneric/doomtype.h` ranks 1 by PageRank, 50 importers, 14 symbols: Copyright(C) 1993-1996 Id Software, Inc.
- [progs/doomgeneric: d_englsh] `progs/doomgeneric/d_event.h` ranks 2 by PageRank, 13 importers, 4 symbols: Copyright(C) 1993-1996 Id Software, Inc.
- [progs/src] `kernel/string.c` ranks 1 by PageRank, 89 importers, 13 symbols: Kernel string and memory functions.
- [progs/src] `progs/minios_abi.h` ranks 2 by PageRank, 32 importers, 156 symbols: Single source of truth for the MiniOS user-kernel ABI.
- [progs/doomgeneric: p_spec] `progs/doomgeneric/doomdef.h` ranks 1 by PageRank, 41 importers, 9 symbols: Copyright(C) 1993-1996 Id Software, Inc.
- [progs/doomgeneric: p_spec] `progs/doomgeneric/m_fixed.h` ranks 2 by PageRank, 9 importers, 6 symbols: Copyright(C) 1993-1996 Id Software, Inc.
- [tools: tls_crypto] `kernel/time.c` ranks 1 by PageRank, 32 importers, 4 symbols: ktime_us: Microsecond resolution over the same calibrated ratio (Phase 0.2/0.3: clock_gettime nsec and gettimeofday usec both derive from here, so the * two clocks share one source and never disagree about ordering).
- [tools: tls_crypto] `headers/ktime.h` ranks 2 by PageRank, 3 importers, 3 symbols: pure time-conversion helpers shared by the kernel clock
- Key entities: file:progs/doomgeneric/d_englsh.h, file:progs/doomgeneric/st_stuff.c, file:progs/vedit/vedit.c, file:progs/minicraft/minicraft.c, file:progs/doomgeneric/p_local.h, file:progs/doomgeneric/p_spec.h, file:net/tls_crypto.c, file:headers/tls.h
- Children: c1, c2, c3, c4, c6
- Theme rating = highest child community rating.

## unassigned files (`t2`, theme, rating 3.4)

Theme of 1 communities and 115 files: unassigned files (115 files, rating 3.4).

- [unassigned files] `arch/x86/ctx_sw.S` ranks 1 by PageRank, 0 importers, 9 symbols: sched_park_capture: captured the rest.
- [unassigned files] `arch/x86/isr_stubs.S` ranks 2 by PageRank, 0 importers, 24 symbols.
- Key entities: file:progs/asm/freedom.s, file:progs/asm/sign.s
- Children: c10
- Theme rating = highest child community rating.

## tools: doom_pwad (`t3`, theme, rating 0.1)

Theme of 1 communities and 2 files: tools: doom_pwad (2 files, rating 0.1).

- [tools: doom_pwad] `tools/doom_pwad.py` ranks 1 by PageRank, 3 importers, 25 symbols: grid map to vanilla Doom PWAD writer and checker.
- [tools: doom_pwad] `tests/test_doom_pwad.py` ranks 2 by PageRank, 0 importers, 44 symbols: host contract suite for tools/doom_pwad.py.
- Key entities: file:tests/test_doom_pwad.py, file:tools/doom_pwad.py
- Children: c9
- Theme rating = highest child community rating.

## headers: kernel (`c0`, community, rating 7.0)

137 files under headers (c 76, h 57, S 4), mostly utility. Core file headers/spinlock.h (PageRank 0.0119, imported by 9 files): Lightweight spinlock for MiniOS kernel. Key abstractions: spinlock_t, SPINLOCK_H, irqflags_t, SPINLOCK_INIT, spin_init, spin_save_irq. Depends on progs/src (17), tools: tls_crypto (3), headers: vga_fb (2). Used by headers: vga_fb (8), tools: tls_crypto (3), progs/src (2).

- `headers/spinlock.h` ranks 1 by PageRank, 9 importers, 19 symbols: Lightweight spinlock for MiniOS kernel.
- `headers/sched.h` ranks 2 by PageRank, 28 importers, 158 symbols: Forward: full view lives in kernel.h (needs KFILE first); the PCB
- `headers/vma.h` ranks 3 by PageRank, 8 importers, 26 symbols: vma_ctx_t: Per-process VMA context (multitask foundation): every non-CLONE_VM process owns its live/free trees plus a private node pool, so two concurrent jobs never corrupt each other's mmap bookkeeping the way the old single global...
- Hotspot `kernel/syscalls.c`: 263 symbols, 65 connections (score 0.69).
- Hotspot `kernel/shell.c`: 97 symbols, 64 connections (score 0.52).
- Dataflow: 27 INFERRED issues (first: DEAD_STORE in sb16_pump).
- Surprising bridge: qga.h <-> d_englsh.h (9 hops across communities).
- Key entities: file:headers/kernel.h, file:kernel/syscalls.c, file:drivers/xhci.c, file:headers/sched.h, file:headers/arch/x86/boot/bootdefs.h, file:net/net.c, file:headers/vga_fb.h, file:kernel/sched.c
- Rating 7.0/10 = 7 x PageRank share 1.00 + 3 x risk 0.00. Internal imports: 319.

## progs/doomgeneric: d_englsh (`c1`, community, rating 6.4)

99 files under progs/doomgeneric (h 50, c 49), mostly utility. Core file progs/doomgeneric/doomtype.h (PageRank 0.0598, imported by 50 files): Copyright(C) 1993-1996 Id Software, Inc. Key abstractions: strcasecmp, strncasecmp, PACKEDATTR, PACKEDATTR, boolean, byte. Depends on progs/doomgeneric: p_spec (77), progs/src (21), progs/doomgeneric: net_defs (6). Used by progs/doomgeneric: p_spec (70), progs/doomgeneric: net_defs (12), progs/src (3).

- `progs/doomgeneric/doomtype.h` ranks 1 by PageRank, 50 importers, 14 symbols: Copyright(C) 1993-1996 Id Software, Inc.
- `progs/doomgeneric/d_event.h` ranks 2 by PageRank, 13 importers, 4 symbols: Copyright(C) 1993-1996 Id Software, Inc.
- `progs/doomgeneric/z_zone.h` ranks 3 by PageRank, 40 importers, 13 symbols: Copyright(C) 1993-1996 Id Software, Inc.
- Hotspot `progs/doomgeneric/d_main.c`: 29 symbols, 81 connections (score 0.57).
- Hotspot `progs/doomgeneric/g_game.c`: 54 symbols, 70 connections (score 0.52).
- Dataflow: 7 INFERRED issues (first: UNCHECKED_ALLOC in GetRegistryString).
- Surprising bridge: qga.h <-> d_englsh.h (9 hops across communities).
- Key entities: file:progs/doomgeneric/d_englsh.h, file:progs/doomgeneric/st_stuff.c, file:progs/doomgeneric/m_controls.h, file:progs/doomgeneric/am_map.c, file:progs/doomgeneric/m_menu.c, file:progs/doomgeneric/wi_stuff.c, file:progs/doomgeneric/g_game.c, file:progs/doomgeneric/doomkeys.h
- Rating 6.4/10 = 7 x PageRank share 0.92 + 3 x risk 0.00. Internal imports: 379.

## progs/src (`c2`, community, rating 4.9)

85 files under tests (c 61, h 24), mostly utility. Core file kernel/string.c (PageRank 0.0344, imported by 89 files): Kernel string and memory functions. Key abstractions: kstrlen, kstrcpy, kstrncpy, kstrncat, kstrcmp, kstrncmp. Depends on progs/doomgeneric: d_englsh (3), headers: kernel (2), progs/doomgeneric: p_spec (1). Used by progs/doomgeneric: d_englsh (21), headers: kernel (17), tools: tls_crypto (7).

- `kernel/string.c` ranks 1 by PageRank, 89 importers, 13 symbols: Kernel string and memory functions.
- `progs/minios_abi.h` ranks 2 by PageRank, 32 importers, 156 symbols: Single source of truth for the MiniOS user-kernel ABI.
- `progs/wl/wl_mini.h` ranks 3 by PageRank, 4 importers, 111 symbols: Wayland-mini subset contract (header-only, ADR-0024).
- Hotspot `kernel/string.c`: 13 symbols, 90 connections (score 0.61).
- Hotspot `progs/minios_abi.h`: 156 symbols, 35 connections (score 0.38).
- 1 layer violations, e.g. test_httpd.c (testing) -> httpd.h (presentation).
- Dataflow: 6 INFERRED issues (first: DEAD_STORE in dmap_build_wad).
- Key entities: file:progs/vedit/vedit.c, file:progs/minicraft/minicraft.c, file:progs/minios_abi.h, file:progs/topogpt3/topogpt3.c, file:progs/pokemon/platform_minios.c, file:progs/wl/wl_mini.h, file:progs/doomedit/doomedit.c, file:progs/lisp/lisp.c
- Rating 4.9/10 = 7 x PageRank share 0.70 + 3 x risk 0.00. Internal imports: 142.

## progs/doomgeneric: p_spec (`c3`, community, rating 4.4)

69 files under progs/doomgeneric (c 35, h 34), mostly utility. Core file progs/doomgeneric/doomdef.h (PageRank 0.0112, imported by 41 files): Copyright(C) 1993-1996 Id Software, Inc. Key abstractions: DOOM_VERSION, DOOM_191_VERSION, RANGECHECK, MAXPLAYERS, MTF_EASY, MTF_NORMAL. Depends on progs/doomgeneric: d_englsh (70), progs/src (4), progs/doomgeneric: net_defs (4). Used by progs/doomgeneric: d_englsh (77), progs/doomgeneric: net_defs (2), progs/src (1).

- `progs/doomgeneric/doomdef.h` ranks 1 by PageRank, 41 importers, 9 symbols: Copyright(C) 1993-1996 Id Software, Inc.
- `progs/doomgeneric/m_fixed.h` ranks 2 by PageRank, 9 importers, 6 symbols: Copyright(C) 1993-1996 Id Software, Inc.
- `progs/doomgeneric/d_mode.h` ranks 3 by PageRank, 6 importers, 3 symbols: Copyright(C) 1993-1996 Id Software, Inc.
- Hotspot `progs/doomgeneric/doomstat.h`: 68 symbols, 44 connections (score 0.36).
- Hotspot `progs/doomgeneric/doomdef.h`: 9 symbols, 50 connections (score 0.34).
- Dependency cycle: r_data.h -> r_state.h -> r_data.h.
- Surprising bridge: qga.h <-> d_items.c (9 hops across communities).
- Key entities: file:progs/doomgeneric/p_local.h, file:progs/doomgeneric/p_spec.h, file:progs/doomgeneric/doomstat.h, file:progs/doomgeneric/info.c, file:progs/doomgeneric/p_enemy.c, file:progs/doomgeneric/r_state.h, file:progs/doomgeneric/deh_misc.h, file:progs/quake2generic/q2generic_minios.c
- Rating 4.4/10 = 7 x PageRank share 0.63 + 3 x risk 0.00. Internal imports: 200.

## unassigned files (`c10`, community, rating 3.4)

115 files under tools (c 43, py 37, sh 17, s 12, S 3, h 2, lua 1), mostly utility. Core file arch/x86/ctx_sw.S (PageRank 0.0009, imported by 0 files): sched_park_capture: captured the rest. Key abstractions: sched_park_capture, switch_save_only, switch_to, switch_to_notrap, user_trampoline, fork_trampoline.

- `arch/x86/ctx_sw.S` ranks 1 by PageRank, 0 importers, 9 symbols: sched_park_capture: captured the rest.
- `arch/x86/isr_stubs.S` ranks 2 by PageRank, 0 importers, 24 symbols.
- `arch/x86/tlb_nmi.S` ranks 3 by PageRank, 0 importers, 1 symbols.
- Hotspot `mcp/test_minios_mcp.py`: 107 symbols, 15 connections (score 0.20).
- Hotspot `tests/test_mip.py`: 44 symbols, 7 connections (score 0.09).
- Taint: 4 paths reach this group via subprocess.
- Dataflow: 1 INFERRED issues (first: UNCHECKED_ALLOC in efi_main).
- Key entities: file:progs/asm/freedom.s, file:progs/asm/sign.s, file:progs/src/sign.c, file:mcp/test_minios_mcp.py, file:progs/src/aes.c, file:boot/uefi_stub.c, file:progs/src/lzss.c, file:kernel/cvm_host.c
- Rating 3.4/10 = 7 x PageRank share 0.48 + 3 x risk 0.00. Internal imports: 0.

## tools: tls_crypto (`c4`, community, rating 2.8)

44 files under tools (py 27, c 12, h 5), mostly utility. Core file kernel/time.c (PageRank 0.0218, imported by 32 files): ktime_us: Microsecond resolution over the same calibrated ratio (Phase 0.2/0.3: clock_gettime nsec and gettimeofday usec both derive from here, so the * two clocks share one source and never disagree about ordering). Key abstractions: ktime_rdtsc, ktime_init, ktime_ms, ktime_us, KTIME_H, ktime_us_from_delta. Depends on progs/src (7), headers: kernel (3), progs/doomgeneric: d_englsh (2). Used by headers: kernel (3).

- `kernel/time.c` ranks 1 by PageRank, 32 importers, 4 symbols: ktime_us: Microsecond resolution over the same calibrated ratio (Phase 0.2/0.3: clock_gettime nsec and gettimeofday usec both derive from here, so the * two clocks share one source and never disagree about ordering).
- `headers/ktime.h` ranks 2 by PageRank, 3 importers, 3 symbols: pure time-conversion helpers shared by the kernel clock
- `progs/lua/minios.c` ranks 3 by PageRank, 4 importers, 17 symbols: msys5: /* ── raw syscall helpers (x86-64 Linux ABI) ─────────────────────────── static long msys(long n, long a1, long a2, long a3) { long ret; __asm__ volatile( "syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2), "d"(a3) : "rcx", "r11"...
- Hotspot `kernel/time.c`: 4 symbols, 35 connections (score 0.24).
- Hotspot `progs/src/lxabi.c`: 61 symbols, 26 connections (score 0.23).
- Taint: 16 paths reach this group via subprocess.
- Dataflow: 1 INFERRED issues (first: UNINIT_USE in ecdsa_verify).
- Key entities: file:net/tls_crypto.c, file:headers/tls.h, file:progs/src/lxabi.c, file:headers/tls_port.h, file:net/tls.c, file:tls_test.c, file:tools/minios_hyper.py, file:net/tls_x509.c
- Rating 2.8/10 = 7 x PageRank share 0.40 + 3 x risk 0.00. Internal imports: 54.

## progs/doomgeneric: net_defs (`c6`, community, rating 0.9)

13 files under progs/doomgeneric (h 11, c 2), mostly utility. Core file progs/doomgeneric/net_defs.h (PageRank 0.0087, imported by 9 files): Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the... Key abstractions: net_connect_data_t, net_gamesettings_t, net_ticdiff_t, net_full_ticcmd_t, net_querydata_t, net_waitdata_t. Depends on progs/doomgeneric: d_englsh (12), progs/src (2), progs/doomgeneric: p_spec (2). Used by progs/doomgeneric: d_englsh (6), progs/doomgeneric: p_spec (4).

- `progs/doomgeneric/net_defs.h` ranks 1 by PageRank, 9 importers, 28 symbols: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the...
- `progs/doomgeneric/d_ticcmd.h` ranks 2 by PageRank, 6 importers, 2 symbols: Copyright(C) 1993-1996 Id Software, Inc.
- `progs/doomgeneric/sha1.h` ranks 3 by PageRank, 5 importers, 9 symbols: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the...
- Hotspot `progs/doomgeneric/d_loop.c`: 18 symbols, 35 connections (score 0.25).
- Hotspot `progs/doomgeneric/net_defs.h`: 28 symbols, 16 connections (score 0.13).
- Key entities: file:progs/doomgeneric/net_defs.h, file:progs/doomgeneric/d_loop.c, file:progs/doomgeneric/net_client.h, file:progs/doomgeneric/sha1.c, file:progs/doomgeneric/net_query.h, file:progs/doomgeneric/sha1.h, file:progs/doomgeneric/net_io.h, file:progs/doomgeneric/net_packet.h
- Rating 0.9/10 = 7 x PageRank share 0.13 + 3 x risk 0.00. Internal imports: 19.

## headers: vga_fb (`c5`, community, rating 0.7)

17 files under headers (h 12, c 5), mostly utility. Core file headers/wm_geom.h (PageRank 0.0036, imported by 3 files): Docstring: Window geometry contract for the MiniOS desktop. Key abstractions: wm_geom_config_t, wm_rect_t, WM_GEOM_H, WM_GEOM_CONFIG_DEFAULT, wm_rect_valid, wm_rect_contains. Depends on headers: kernel (8). Used by headers: kernel (2).

- `headers/wm_geom.h` ranks 1 by PageRank, 3 importers, 11 symbols: Docstring: Window geometry contract for the MiniOS desktop.
- `headers/wm_window.h` ranks 2 by PageRank, 4 importers, 10 symbols: Docstring: Unified window contract for the MiniOS desktop.
- `headers/vga_fx.h` ranks 3 by PageRank, 3 importers, 9 symbols: Docstring: DOOM-melt desktop effect contract for MiniOS.
- Hotspot `kernel/vga_fb.c`: 205 symbols, 36 connections (score 0.44).
- Hotspot `tests/test_wm.c`: 2 symbols, 17 connections (score 0.12).
- 2 layer violations, e.g. test_wm.c (testing) -> wm_render.h (presentation).
- Dataflow: 8 INFERRED issues (first: DEAD_STORE in taskbar_render).
- Key entities: file:kernel/vga_fb.c, file:headers/wm_events.h, file:headers/desktop_shortcuts.h, file:headers/wm_layout.h, file:headers/wm_gfxview.h, file:kernel/vga_cursor.c, file:headers/wm_window.h, file:headers/wm_geom.h
- Rating 0.7/10 = 7 x PageRank share 0.10 + 3 x risk 0.00. Internal imports: 26.

## headers: batch (`c7`, community, rating 0.1)

3 files under headers (c 2, h 1), mostly utility. Core file headers/batch.h (PageRank 0.0026, imported by 3 files): Docstring: batch.h -- Batched synchronous syscall submission. Key abstractions: batch_op_t, BATCH_H, BATCH_MAX_OPS, BATCH_OP_NOP, BATCH_OP_YIELD, BATCH_OP_TIME. Used by headers: kernel (1).

- `headers/batch.h` ranks 1 by PageRank, 3 importers, 12 symbols: Docstring: batch.h -- Batched synchronous syscall submission.
- `kernel/batch.c` ranks 2 by PageRank, 0 importers, 1 symbols: Docstring: kernel/batch.c -- Ordered batch executor.
- `tests/test_batch.c` ranks 3 by PageRank, 0 importers, 3 symbols: Docstring: Host test for kernel/batch.c (make test-batch).
- Hotspot `headers/batch.h`: 12 symbols, 4 connections (score 0.04).
- Hotspot `tests/test_batch.c`: 3 symbols, 3 connections (score 0.02).
- Key entities: file:headers/batch.h, file:tests/test_batch.c, file:kernel/batch.c, sym:headers/batch.h::BATCH_ERR_COUNT@49, sym:headers/batch.h::BATCH_ERR_OPCODE@51, sym:headers/batch.h::BATCH_ERR_PTR@50, sym:headers/batch.h::BATCH_H@2, sym:headers/batch.h::BATCH_MAX_OPS@41
- Rating 0.1/10 = 7 x PageRank share 0.02 + 3 x risk 0.00. Internal imports: 2.

## headers: tick (`c8`, community, rating 0.1)

3 files under headers (c 2, h 1), mostly utility. Core file headers/tick.h (PageRank 0.0026, imported by 3 files): Docstring: Tick listener bus contract. Key abstractions: tick_config_t, TICK_H, TICK_MAX_AUDIO_LISTENERS, TICK_MAX_DESKTOP_LISTENERS, TICK_MAX_USB_LISTENERS, TICK_CONFIG_DEFAULT. Used by headers: kernel (1).

- `headers/tick.h` ranks 1 by PageRank, 3 importers, 16 symbols: Docstring: Tick listener bus contract.
- `kernel/tick.c` ranks 2 by PageRank, 0 importers, 11 symbols: Docstring: Tick listener bus implementation.
- `tests/test_tick.c` ranks 3 by PageRank, 0 importers, 6 symbols: Docstring: Host test for kernel/tick.c (make test-tick).
- Hotspot `headers/tick.h`: 16 symbols, 3 connections (score 0.04).
- Hotspot `kernel/tick.c`: 11 symbols, 3 connections (score 0.03).
- Key entities: file:headers/tick.h, file:kernel/tick.c, file:tests/test_tick.c, sym:headers/tick.h::TICK_CONFIG_DEFAULT@37, sym:headers/tick.h::TICK_H@19, sym:headers/tick.h::TICK_MAX_AUDIO_LISTENERS@29, sym:headers/tick.h::TICK_MAX_DESKTOP_LISTENERS@31, sym:headers/tick.h::TICK_MAX_USB_LISTENERS@34
- Rating 0.1/10 = 7 x PageRank share 0.02 + 3 x risk 0.00. Internal imports: 2.

## tools: doom_pwad (`c9`, community, rating 0.1)

2 files under tests (py 2), mostly testing. Core file tools/doom_pwad.py (PageRank 0.0018, imported by 3 files): grid map to vanilla Doom PWAD writer and checker. Key abstractions: DoomPwadConfig, PwadError, pad_tex, parse_grid, grid_extents, is_wall.

- `tools/doom_pwad.py` ranks 1 by PageRank, 3 importers, 25 symbols: grid map to vanilla Doom PWAD writer and checker.
- `tests/test_doom_pwad.py` ranks 2 by PageRank, 0 importers, 44 symbols: host contract suite for tools/doom_pwad.py.
- Hotspot `tests/test_doom_pwad.py`: 44 symbols, 10 connections (score 0.11).
- Hotspot `tools/doom_pwad.py`: 25 symbols, 6 connections (score 0.06).
- Key entities: file:tests/test_doom_pwad.py, file:tools/doom_pwad.py, sym:tools/doom_pwad.py::parse_grid@172, sym:tools/doom_pwad.py::check_pwad@639, sym:tools/doom_pwad.py::build_pwad@597, sym:tools/doom_pwad.py::read_pwad@616, sym:tools/doom_pwad.py::PwadError@161, sym:tools/doom_pwad.py::build_lumps@516
- Rating 0.1/10 = 7 x PageRank share 0.01 + 3 x risk 0.00. Internal imports: 3.
