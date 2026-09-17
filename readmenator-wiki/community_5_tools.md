# tools

*Community 5 | 21 files | cohesion 0.79*

## Definition

This community groups 21 file(s) rooted at `tools` with dominant language py (cohesion 0.79). Central symbols: `AddonError`, `AddonState`, `Client`, `FrameDiff`, `GdbChannel`, `Guest`, `Handler`, `HyperChecks`. Core file: `tools/minios_hyper.py` (51 symbols). Documented purpose: Debug driver: boot MiniOS through the MCP bridge and run freedom..

## Files

### `tools` (16 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tools/boot_wl.py` | py | utility | 14 | yes |
| `tools/gdb_repro.py` | py | utility | 4 | yes |
| `tools/minios_cli.py` | py | utility | 6 | yes |
| `tools/minios_gui.py` | py | presentation | 9 | yes |
| `tools/minios_hyper.py` | py | utility | 51 | yes |
| `tools/probe_compute_vga.py` | py | utility | 6 | yes |
| `tools/probe_minicraft.py` | py | utility | 6 | yes |
| `tools/qga_client.py` | py | infrastructure | 4 | yes |
| `tools/repro_gui.py` | py | presentation | 10 | yes |
| `tools/test_gui_fashion.py` | py | testing | 18 | yes |
| `tools/test_gui_icon_cwd.py` | py | testing | 17 | yes |
| `tools/test_gui_menu.py` | py | testing | 1 | yes |
| `tools/test_gui_wm.py` | py | testing | 17 | yes |
| `tools/test_gui_zoom.py` | py | testing | 1 | yes |
| `tools/test_http_server.py` | py | testing | 3 | yes |

### `mcp` (4 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `mcp/mcp_dbg_driver.py` | py | infrastructure | 6 | yes |
| `mcp/mcp_dogfood.py` | py | utility | 6 | yes |
| `mcp/minios_addons.py` | py | utility | 16 | yes |
| `mcp/minios_mcp.py` | py | utility | 50 | yes |

### `kernel` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/time.c` | c | utility | 4 | yes |

*... and 1 more files in this community.*


## Key Symbols

- `ktime_rdtsc` (function, `kernel/time.c:13`) `static unsigned long ktime_rdtsc(void)`
- `ktime_init` (function, `kernel/time.c:19`) `static void ktime_init(void)`
- `ktime_ms` (function, `kernel/time.c:33`) `unsigned long ktime_ms(void)`
- `ktime_us` (function, `kernel/time.c:41`) `unsigned long ktime_us(void)` - Microsecond resolution over the same calibrated ratio (Phase 0.2/0.3: clock_gettime nsec and gettime
- `Client` (class, `mcp/mcp_dbg_driver.py:15`) `class Client`
- `__init__` (method, `mcp/mcp_dbg_driver.py:16`) `def __init__(self)`
- `request` (method, `mcp/mcp_dbg_driver.py:28`) `def request(self, method, params)`
- `tool` (method, `mcp/mcp_dbg_driver.py:46`) `def tool(self, name, params)`
- `close` (method, `mcp/mcp_dbg_driver.py:54`) `def close(self)`
- `main` (method, `mcp/mcp_dbg_driver.py:64`) `def main()`
- `Client` (class, `mcp/mcp_dogfood.py:19`) `class Client`
- `__init__` (method, `mcp/mcp_dogfood.py:20`) `def __init__(self, addons_dir)`
- `request` (method, `mcp/mcp_dogfood.py:40`) `def request(self, method, params)`
- `tool` (method, `mcp/mcp_dogfood.py:58`) `def tool(self, name, params)`
- `close` (method, `mcp/mcp_dogfood.py:68`) `def close(self)`
- `main` (method, `mcp/mcp_dogfood.py:78`) `def main()`
- `AddonError` (class, `mcp/minios_addons.py:56`) `class AddonError(Exception)` - Expected marketplace failure, reported to the client as isError.
- `_clean` (method, `mcp/minios_addons.py:62`) `def _clean(s)`
- `_unquote` (method, `mcp/minios_addons.py:66`) `def _unquote(v)`
- `parse_addon_yaml` (method, `mcp/minios_addons.py:73`) `def parse_addon_yaml(text)` - Parse the strict YAML subset. Returns the addon dict.
- `fail` (method, `mcp/minios_addons.py:85`) `def fail(lineno, why)`
- `validate_addon` (method, `mcp/minios_addons.py:205`) `def validate_addon(addon, source)` - Check bounds and character sets. Raises AddonError.
- `validate_addon_path` (method, `mcp/minios_addons.py:295`) `def validate_addon_path(path)` - dst paths live on the ramdisk: relative, no '..', bounded charset.
- `validate_shell_line` (method, `mcp/minios_addons.py:309`) `def validate_shell_line(line)` - Build/verify lines are single printable-ASCII shell commands.
- `load_addons_dir` (method, `mcp/minios_addons.py:323`) `def load_addons_dir(addons_dir)` - Load every addon yaml; each entry is a dict or an error string.
- `split_for_editor` (method, `mcp/minios_addons.py:347`) `def split_for_editor(text)` - Split a source into editor-sized chunks. Raises AddonError.
- `exit_code_of` (method, `mcp/minios_addons.py:372`) `def exit_code_of(text)`
- `AddonState` (class, `mcp/minios_addons.py:377`) `class AddonState` - Host-side record of installed addons (system temp dir).
- `__init__` (method, `mcp/minios_addons.py:380`) `def __init__(self, path)`
- `load` (method, `mcp/minios_addons.py:383`) `def load(self)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 23
- Cross-boundary resolved imports (EXTRACTED): 7

## Connections

- [EXTRACTED] depends_on community 4 <-> 5 (strength 0.9): Extracted import edge crosses communities: headers/tls_port.h imports kernel/time.c.
- [EXTRACTED] depends_on community 5 <-> 0 (strength 0.9): Extracted import edge crosses communities: kernel/time.c imports headers/kernel.h.
- [EXTRACTED] depends_on community 2 <-> 5 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/doomgeneric_xlib.c imports kernel/time.c.
- [INFERRED] shares_context community 1 <-> 5 (strength 0.5): Inferred shared context (layer utility) with no import path between community 1 (headers) and community 5 (tools).

## Risks

- [taint high] `mcp/mcp_dbg_driver.py` -> `mcp/mcp_dbg_driver.py` via `subprocess` (0 hops)
- [taint high] `mcp/mcp_dbg_driver.py` -> `kernel/time.c` via `subprocess` (1 hops)
- [taint high] `mcp/mcp_dbg_driver.py` -> `headers/ktime.h` via `subprocess` (2 hops)
- [taint high] `mcp/mcp_dbg_driver.py` -> `headers/kernel.h` via `subprocess` (2 hops)
- [taint high] `mcp/mcp_dbg_driver.py` -> `headers/vma.h` via `subprocess` (3 hops)
- [taint high] `mcp/mcp_dbg_driver.py` -> `headers/spinlock.h` via `subprocess` (3 hops)
- [taint high] `mcp/mcp_dbg_driver.py` -> `progs/minios_abi.h` via `subprocess` (3 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `mcp/mcp_dogfood.py` via `subprocess` (0 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `kernel/time.c` via `subprocess` (1 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `headers/ktime.h` via `subprocess` (2 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `headers/kernel.h` via `subprocess` (2 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `headers/vma.h` via `subprocess` (3 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `headers/spinlock.h` via `subprocess` (3 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `progs/minios_abi.h` via `subprocess` (3 hops)
- [taint high] `mcp/minios_addons.py` -> `mcp/minios_addons.py` via `subprocess` (0 hops)

## Open Questions

- Is the dangerous import `subprocess` in `mcp/mcp_dbg_driver.py` still required, or can it be isolated?
- What would break if the most connected file in tools changed?
- Should tools be split, given cohesion 0.79?

## Sources

- `kernel/time.c`
- `mcp/mcp_dbg_driver.py`
- `mcp/mcp_dogfood.py`
- `mcp/minios_addons.py`
- `mcp/minios_mcp.py`
- `tools/boot_wl.py`
- `tools/gdb_repro.py`
- `tools/minios_cli.py`
- `tools/minios_gui.py`
- `tools/minios_hyper.py`
- `tools/probe_compute_vga.py`
- `tools/probe_minicraft.py`
- `tools/qga_client.py`
- `tools/repro_gui.py`
- `tools/test_gui_fashion.py`
- `tools/test_gui_icon_cwd.py`
- `tools/test_gui_menu.py`
- `tools/test_gui_wm.py`
- `tools/test_gui_zoom.py`
- `tools/test_http_server.py`
- *... and 1 more*
