# tools: lxabi

tools: lxabi groups 37 files (c, h, py) around ktime_rdtsc, ktime_init, ktime_ms, ktime_us, KTIME_H. pure time-conversion helpers shared by the kernel clock

```mermaid
graph LR
    headers["headers"]
    kernel["kernel"]
    mcp["mcp"]
    progs["progs"]
    tests["tests"]
    tools["tools"]
    kernel -- "calls into" --> headers
    mcp -- "depends on" --> kernel
    mcp -- "calls into" --> tools
    progs -- "depends on" --> kernel
    progs -- "calls into" --> mcp
    progs -- "calls into" --> tools
    tests -- "calls into" --> headers
    tests -- "depends on" --> kernel
    tools -- "depends on" --> kernel
    tools -- "calls into" --> mcp
```

## headers (5.1)

headers groups 1 files (h) around KTIME_H, ktime_us_from_delta, wall_us_from_parts. pure time-conversion helpers shared by the kernel clock

## kernel (5.2)

kernel groups 1 files (c) around ktime_rdtsc, ktime_init, ktime_ms, ktime_us. ktime_us: Microsecond resolution over the same calibrated ratio (Phase 0.2/0.3...

## mcp (5.3)

mcp groups 4 files (py) around AddonError, _clean, _unquote, parse_addon_yaml, fail. Debug driver: boot MiniOS through the MCP bridge and run freedom.

## progs (5.4)

progs groups 10 files (c, py) around msys5, SYS_TIME_MS, SYS_PALETTE, SYS_PCSPK_INIT, SYS_PCSPK_TONE. msys5: /* ── raw syscall helpers (x86-64 Linux ABI) ─────────────────────────── static...

## tests (5.5)

tests groups 2 files (c) around CHECK, main, now_us, LIST_MAX, l_insert. host test for the pure conversion math in ktime.h

## tools (5.6)

tools groups 19 files (py) around note, Guest, __init__, _ser, _reader. boot the miniOS Wayland-mini desktop in one step.

**Files**:

- headers/ktime.h
- kernel/time.c
- mcp/mcp_dbg_driver.py
- mcp/mcp_dogfood.py
- mcp/minios_addons.py
- mcp/minios_mcp.py
- progs/doomgeneric/doomgeneric_xlib.c
- progs/lua/minios.c
- progs/micropython/variants/minios/lib/hello.py
- progs/micropython/variants/minios/lib/mip.py
- progs/src/lxabi.c
- progs/src/lxsel.c
- progs/src/shell.py
- progs/src/test.py
- progs/src/test_py.py
- progs/tls_u/tls_u_port.c
- tests/test_ktime.c
- tests/test_vma_bench.c
- tools/boot_wl.py
- tools/gdb_repro.py
- tools/minios_cli.py
- tools/minios_gui.py
- tools/minios_hyper.py
- tools/probe_compute_vga.py
- tools/probe_minicraft.py
- tools/qga_client.py
- tools/repro_gui.py
- tools/test_gui_fashion.py
- tools/test_gui_freedom.py
- tools/test_gui_gfxview.py
- tools/test_gui_icon_cwd.py
- tools/test_gui_menu.py
- tools/test_gui_wm.py
- tools/test_gui_zoom.py
- tools/test_http_server.py
- tools/test_readme_shot.py
- tools/tls_test.py
