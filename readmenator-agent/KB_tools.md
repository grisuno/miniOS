# Subsystem: tools

## tools/abi_stamp.c
- Layer: utility
- Doc: Docstring: tools/abi_stamp.c -- Build-time ABI manifest generator.
- Language: c
- Symbols:
  - `main` (function, line 14) `int main(void)`
- Depends on: `progs/minios_abi.h`

## tools/boot_run.sh
- Layer: utility
- Doc: boot_run.sh -- boot the MiniOS image in QEMU and drive the shell over the serial console with a list of commands, captur
- Language: sh

## tools/boot_wl.py
- Layer: utility
- Doc: boot_wl.py - boot the miniOS Wayland-mini desktop in one step.  Builds nothing; `make wl` owns the build. Boots os.img, 
- Language: py
- Symbols:
  - `WlBootConfig` (class, line 40) `class WlBootConfig`
  - `WlBoot` (class, line 67) `class WlBoot`
  - `main` (method, line 226) `def main()`
  - `__init__` (method, line 68) `def __init__(self, cfg)`
  - `fail` (method, line 75) `def fail(self, msg)`
  - `close` (method, line 80) `def close(self)`
  - `boot` (method, line 91) `def boot(self)`
  - `snapshot` (method, line 107) `def snapshot(self, timeout)`
  - `wait_prompt` (method, line 124) `def wait_prompt(self)`
  - `send` (method, line 135) `def send(self, line)`
  - `send_wait` (method, line 142) `def send_wait(self, line, timeout)`
  - `setup` (method, line 154) `def setup(self)`
  - `qmp` (method, line 165) `def qmp(self, obj)`
  - `headless` (method, line 182) `def headless(self)`
  - `proxy` (method, line 195) `def proxy(self)`
- Depends on: `kernel/time.c`

## tools/check_abi_numbers.py
- Layer: utility
- Doc: check_abi_numbers.py -- MiniOS syscall numbers vs Linux x86-64 truth.  Phase 0.6 of the FreeDom readiness plan: a browse
- Language: py
- Symbols:
  - `normalize` (function, line 127) `def normalize(minios_name)`
  - `parse_abi` (function, line 131) `def parse_abi(path)`
  - `parse_dispatch` (function, line 142) `def parse_dispatch(path)`
  - `main` (function, line 155) `def main()`

## tools/check_addons.py
- Layer: utility
- Doc: check_addons.py -- validate the MiniOS addon marketplace index.  Loads every addons/*.yaml through the strict stdlib-onl
- Language: py
- Symbols:
  - `load_parser` (function, line 22) `def load_parser()`
  - `main` (function, line 31) `def main()`

## tools/check_cohesion.py
- Layer: utility
- Doc: check_cohesion.py -- Architectural cohesion gate for MiniOS CI.  Parses the CPG JSON-LD output from readmenator and fail
- Language: py
- Symbols:
  - `load_cpg` (function, line 23) `def load_cpg(path)`
  - `compute_cohesion` (function, line 31) `def compute_cohesion(community_nodes, community_edges)`
  - `extract_communities` (function, line 42) `def extract_communities(cpg)`
  - `main` (function, line 58) `def main()`

## tools/check_complexity.py
- Layer: utility
- Doc: check_complexity.py -- Kernel complexity gate for MiniOS CI.  Validates that kernel.c does not exceed the configured sym
- Language: py
- Symbols:
  - `count_symbols` (function, line 24) `def count_symbols(filepath)`
  - `load_approval` (function, line 46) `def load_approval(policy_path)`
  - `main` (function, line 61) `def main()`

## tools/check_fork_stubs.py
- Layer: testing
- Doc: Fail-closed stub gate for unimplemented process syscalls.  vfork has no implementation in this kernel. A stub that answe
- Language: py
- Symbols:
  - `Config` (class, line 18) `class Config`
  - `handler_body` (method, line 27) `def handler_body(text, name)`
  - `check_stubs` (method, line 37) `def check_stubs(text, cfg)`
  - `main` (method, line 52) `def main()`

## tools/check_kb_sync.py
- Layer: utility
- Doc: check_kb_sync.py -- Verify KNOWLEDGE_BASE.md is in sync with code.  Runs readmenator to regenerate the knowledge base, t
- Language: py
- Symbols:
  - `regenerate_kb` (function, line 24) `def regenerate_kb()`
  - `main` (function, line 43) `def main()`

## tools/check_mutant_anchors.py
- Layer: utility
- Doc: Verify every mutate.sh mutant anchor matches its target file.  A mutant whose sed expression matches nothing is reported
- Language: py
- Symbols:
  - `Config` (class, line 17) `class Config`
  - `bash_unquote` (method, line 26) `def bash_unquote(expr)`
  - `parse_mutations` (method, line 41) `def parse_mutations(text)`
  - `anchor_matches` (method, line 67) `def anchor_matches(repo, target, expr)`
  - `main` (method, line 86) `def main()`

## tools/check_surprising.py
- Layer: utility
- Doc: check_surprising.py -- Detect surprising architectural connections.  Parses the CPG JSON-LD output from readmenator and 
- Language: py
- Symbols:
  - `load_cpg` (function, line 25) `def load_cpg(path)`
  - `build_graph` (function, line 33) `def build_graph(cpg)`
  - `bfs_min_hops` (function, line 56) `def bfs_min_hops(nodes, edges, source, target_community, max_hops)`
  - `find_surprising_connections` (function, line 87) `def find_surprising_connections(nodes, edges, min_hops)`
  - `main` (function, line 118) `def main()`

## tools/check_syscall_sanitize.py
- Layer: utility
- Doc: Scoped audit gate for syscall user-pointer sanitization.  Every ring-3 pointer that reaches a syscall handler as a1..a6 
- Language: py
- Symbols:
  - `Config` (class, line 18) `class Config`
  - `split_functions` (method, line 69) `def split_functions(lines)`
  - `checked_names` (method, line 112) `def checked_names(body)`
  - `delegated_only` (method, line 122) `def delegated_only(body, alias)`
  - `split_top_args` (method, line 143) `def split_top_args(argtext)`
  - `audit_body` (method, line 162) `def audit_body(name, body)`
  - `audit_file` (method, line 217) `def audit_file(path)`
  - `main` (method, line 228) `def main()`

## tools/doom_pwad.py
- Layer: utility
- Doc: doom_pwad.py - grid map to vanilla Doom PWAD writer and checker.  Converts a text grid map into a single-level PWAD that
- Language: py
- Symbols:
  - `DoomPwadConfig` (class, line 52) `class DoomPwadConfig`
  - `PwadError` (class, line 161) `class PwadError(Exception)`
  - `pad_tex` (method, line 165) `def pad_tex(raw)`
  - `parse_grid` (method, line 172) `def parse_grid(text)`
  - `grid_extents` (method, line 195) `def grid_extents(rows)`
  - `is_wall` (method, line 203) `def is_wall(rows, row, col)`
  - `flood_reachable` (method, line 210) `def flood_reachable(rows)`
  - `validate_grid` (method, line 240) `def validate_grid(rows)`
  - `cell_corners` (method, line 269) `def cell_corners(row, col)`
  - `cell_class` (method, line 279) `def cell_class(cell)`
  - `label_regions` (method, line 291) `def label_regions(rows)`
  - `region_sector` (method, line 326) `def region_sector(region, door_tag)`
  - `compile_geometry` (method, line 371) `def compile_geometry(rows, exit_pos, wall_side)`
  - `compile_things` (method, line 485) `def compile_things(rows)`
  - `seg_angle` (method, line 506) `def seg_angle(dx, dy)`
  - `build_lumps` (method, line 516) `def build_lumps(rows)`
  - `build_pwad` (method, line 597) `def build_pwad(rows)`
  - `read_pwad` (method, line 616) `def read_pwad(data)`
  - `check_pwad` (method, line 639) `def check_pwad(data)`
  - `cmd_build` (method, line 816) `def cmd_build(grid_path, out_path)`
  - `cmd_check` (method, line 826) `def cmd_check(path)`
  - `main` (method, line 834) `def main(argv)`
  - `vertex` (method, line 386) `def vertex(x, y)`
  - `payload` (method, line 650) `def payload(name)`
  - `check_multiple` (method, line 655) `def check_multiple(name, fmt)`
- Imported by: `tests/test_doom_pwad.py`, `tests/test_doom_pwad.py`, `tests/test_doom_pwad.py`

## tools/extract_shell.py
- Layer: utility
- Doc: tools/extract_shell.py -- Plan for Phase 6.1 shell extraction.  This script documents the shell extraction plan. The act
- Language: py

## tools/gdb_repro.py
- Layer: utility
- Doc: gdb_repro.py — drive a graphics-program sequence under the GDB stub.  Boots MiniOS with the gdb server (-s), a QMP socke
- Language: py
- Symbols:
  - `rs` (function, line 23) `def rs(m, t)`
  - `main` (function, line 27) `def main()`
  - `send` (function, line 65) `def send(line)`
  - `quit_doom` (function, line 70) `def quit_doom()`
- Depends on: `kernel/time.c`

## tools/gen_desktop_pngs.py
- Layer: utility
- Doc: gen_desktop_pngs.py -- build MiniOS desktop art from user-supplied PNGs.  Sources (images/ by default, overridable with 
- Language: py
- Symbols:
  - `write_atomic` (function, line 69) `def write_atomic(img, path)`
  - `main` (function, line 75) `def main()`

## tools/gen_icons.py
- Layer: utility
- Doc: gen_icons.py -- generate 32x32 RGBA PNG icon files for the MiniOS desktop.  Each icon is defined as a 32-line string of 
- Language: py
- Symbols:
  - `make_png` (function, line 179) `def make_png(pixels, palette, width, height)`
  - `make_chunk` (function, line 209) `def make_chunk(chunk_type, data)`
  - `main` (function, line 214) `def main()`

## tools/gen_minifs.py
- Layer: utility
- Doc: Generate minifs.c for MiniOS.
- Language: py

## tools/gen_zip_fixtures.py
- Layer: data_access
- Doc: gen_zip_fixtures.py -- generate the zip test fixtures shipped on the ramdisk.  Two small ZIP archives, built with the ho
- Language: py
- Symbols:
  - `write_zip` (function, line 28) `def write_zip(path, entries)`
  - `main` (function, line 42) `def main()`

## tools/install.sh
- Layer: utility
- Language: sh

## tools/kernel_feature_survey.py
- Layer: utility
- Doc: kernel_feature_survey.py - verify which C features the MiniOS kernel needs.  Scans kernel and ring-3 sources for constru
- Language: py
- Symbols:
  - `SurveyConfig` (class, line 18) `class SurveyConfig`
  - `iter_sources` (method, line 34) `def iter_sources(root)`
  - `find_fnptr_hits` (method, line 43) `def find_fnptr_hits(path, text)`
  - `find_asm_constraints` (method, line 49) `def find_asm_constraints(path, text)`
  - `count_params` (method, line 59) `def count_params(params)`
  - `survey` (method, line 67) `def survey(root)`
  - `render_text` (method, line 103) `def render_text(findings)`
  - `main` (method, line 122) `def main(argv)`

## tools/lisp_scoped.sh
- Layer: utility
- Doc: Docstring: Scoped Lisp validation for the MiniOS interpreter contract. Builds the ring-3 static ELF with zero warnings, 
- Language: sh
- Symbols:
  - `say` (function, line 8)
  - `die` (function, line 9)
  - `mutant` (function, line 20)
  - `lisp_mut` (function, line 41)
  - `mut_usage` (function, line 63)

## tools/make_usb.sh
- Layer: utility
- Doc: Build the MiniOS bootable USB image and optionally write it to a device.  Wraps the Makefile targets so there is a singl
- Language: sh
- Symbols:
  - `usage` (function, line 40)
  - `wizard` (function, line 56)

## tools/minifs_dump.py
- Layer: utility
- Doc: minifs_dump.py - Dump/inspect a MiniFS filesystem image.
- Language: py
- Symbols:
  - `u16` (function, line 13) `def u16(d, o)`
  - `u32` (function, line 14) `def u32(d, o)`
  - `mode_str` (function, line 16) `def mode_str(m)`
  - `FS` (class, line 25) `class FS`
  - `main` (method, line 105) `def main()`
  - `__init__` (method, line 26) `def __init__(self, fn)`
  - `blk` (method, line 29) `def blk(self, n)`
  - `_sb` (method, line 30) `def _sb(self)`
  - `inode` (method, line 38) `def inode(self, i)`
  - `read` (method, line 47) `def read(self, ino)`
  - `resolve` (method, line 67) `def resolve(self, path)`
  - `ls` (method, line 86) `def ls(self, ino, prefix)`

## tools/minifs_fsck.py
- Layer: utility
- Doc: minifs_fsck.py - Check MiniFS filesystem consistency.
- Language: py
- Symbols:
  - `u16` (function, line 13) `def u16(d, o)`
  - `u32` (function, line 14) `def u32(d, o)`
  - `FSCK` (class, line 16) `class FSCK`
  - `main` (method, line 136) `def main()`
  - `__init__` (method, line 17) `def __init__(self, fn)`
  - `_find_base` (method, line 24) `def _find_base(self)`
  - `blk` (method, line 42) `def blk(self, n)`
  - `_sb` (method, line 45) `def _sb(self)`
  - `inode` (method, line 51) `def inode(self, i)`
  - `read` (method, line 58) `def read(self, ino)`
  - `err` (method, line 73) `def err(self, msg)`
  - `mark_block` (method, line 75) `def mark_block(self, n)`
  - `scan_inode` (method, line 80) `def scan_inode(self, i)`
  - `scan_dir` (method, line 89) `def scan_dir(self, ino)`
  - `run` (method, line 121) `def run(self)`

## tools/minifs_saves.py
- Layer: utility
- Doc: minifs_saves.py - preserve the guest's saves/ dir across image rebuilds.  Regenerating minifs.bin from scratch wipes eve
- Language: py
- Symbols:
  - `u16` (function, line 53) `def u16(d, o)`
  - `u32` (function, line 57) `def u32(d, o)`
  - `Image` (class, line 61) `class Image`
  - `FS` (class, line 85) `class FS`
  - `valid_name` (method, line 216) `def valid_name(nm)`
  - `strict_name` (method, line 224) `def strict_name(nm)`
  - `find_partition_base` (method, line 233) `def find_partition_base(fn)`
  - `cmd_backup` (method, line 271) `def cmd_backup(img_path, stage)`
  - `main` (method, line 343) `def main(argv)`
  - `__init__` (method, line 64) `def __init__(self, fn, base)`
  - `close` (method, line 72) `def close(self)`
  - `blk` (method, line 75) `def blk(self, n)`
  - `__init__` (method, line 86) `def __init__(self, img)`
  - `inode` (method, line 95) `def inode(self, i)`
  - `is_dir` (method, line 110) `def is_dir(self, st)`
  - `read_file` (method, line 113) `def read_file(self, ino)`
  - `listdir` (method, line 146) `def listdir(self, ino)`
  - `read_file_dir` (method, line 165) `def read_file_dir(self, ino)`
  - `read_file_raw` (method, line 173) `def read_file_raw(self, st)`
  - `resolve` (method, line 197) `def resolve(self, path)`
  - `walk` (method, line 293) `def walk(dir_ino, rel)`

## tools/minios_cli.py
- Layer: utility
- Doc: minios_cli.py — drive MiniOS through the MCP bridge, not by hand.  Starts mcp/minios_mcp.py (which owns the QEMU child a
- Language: py
- Symbols:
  - `Client` (class, line 38) `class Client`
  - `main` (method, line 100) `def main()`
  - `__init__` (method, line 39) `def __init__(self)`
  - `request` (method, line 56) `def request(self, method, params)`
  - `tool` (method, line 77) `def tool(self, name, params)`
  - `close` (method, line 87) `def close(self)`
- Depends on: `kernel/time.c`

## tools/minios_gui.py
- Layer: presentation
- Doc: minios_gui.py — inject VGA-mode input and capture the framebuffer.  Boots MiniOS with the emulated std VGA device (the l
- Language: py
- Symbols:
  - `read_serial` (function, line 44) `def read_serial(master, timeout)`
  - `QMP` (class, line 60) `class QMP`
  - `main` (method, line 112) `def main()`
  - `__init__` (method, line 61) `def __init__(self, path)`
  - `cmd` (method, line 73) `def cmd(self, obj)`
  - `_recv` (method, line 77) `def _recv(self)`
  - `mouse` (method, line 92) `def mouse(self, dx, dy, click)`
  - `key` (method, line 102) `def key(self, qcode, up)`
  - `screendump` (method, line 108) `def screendump(self, path)`
- Depends on: `kernel/time.c`

## tools/minios_hyper.py
- Layer: utility
- Doc: minios_hyper.py -- host-side ring-minus-one debugger for MiniOS.  QEMU already runs in host root mode above the guest ke
- Language: py
- Symbols:
  - `HyperConfig` (class, line 50) `class HyperConfig`
  - `RspCodec` (class, line 73) `class RspCodec`
  - `QmpChannel` (class, line 96) `class QmpChannel`
  - `GdbChannel` (class, line 152) `class GdbChannel`
  - `Guest` (class, line 211) `class Guest`
  - `FrameDiff` (class, line 339) `class FrameDiff`
  - `HyperChecks` (class, line 409) `class HyperChecks`
  - `run_selftest` (method, line 491) `def run_selftest()`
  - `run_boot` (method, line 523) `def run_boot(checks, extra_shell, interactive)`
  - `repl` (method, line 561) `def repl(guest)`
  - `main` (method, line 591) `def main(argv)`
  - `encode` (method, line 77) `def encode(payload)`
  - `decode` (method, line 85) `def decode(frame)`
  - `__init__` (method, line 99) `def __init__(self, path)`
  - `_roundtrip` (method, line 109) `def _roundtrip(self, obj)`
  - `raw` (method, line 117) `def raw(self, obj)`
  - `screendump` (method, line 121) `def screendump(self, path)`
  - `rel` (method, line 126) `def rel(self, dx, dy)`
  - `key` (method, line 132) `def key(self, qcode)`
  - `status` (method, line 141) `def status(self)`
  - `close` (method, line 145) `def close(self)`
  - `__init__` (method, line 155) `def __init__(self, port)`
  - `_drain` (method, line 162) `def _drain(self)`
  - `_cmd` (method, line 168) `def _cmd(self, payload)`
  - `regs` (method, line 181) `def regs(self)`
  - `read_mem` (method, line 185) `def read_mem(self, addr, length)`
  - `halt` (method, line 195) `def halt(self)`
  - `cont` (method, line 201) `def cont(self)`
  - `close` (method, line 204) `def close(self)`
  - `__init__` (method, line 214) `def __init__(self, with_gdb)`
  - `_ser` (method, line 248) `def _ser(self)`
  - `_reader` (method, line 260) `def _reader(self)`
  - `snapshot` (method, line 276) `def snapshot(self)`
  - `wait_for` (method, line 280) `def wait_for(self, marker, timeout)`
  - `send` (method, line 288) `def send(self, line, settle)`
  - `qmp_chan` (method, line 298) `def qmp_chan(self)`
  - `gdb_chan` (method, line 303) `def gdb_chan(self)`
  - `dump` (method, line 308) `def dump(self, name)`
  - `stop` (method, line 314) `def stop(self)`
  - `mean_diff` (method, line 343) `def mean_diff(a_path, b_path)`
  - `cursor_positions` (method, line 356) `def cursor_positions(shot_path)`
  - `count_cursors` (method, line 394) `def count_cursors(shot_path)`
  - `moved_cursors` (method, line 399) `def moved_cursors(before_path, after_path)`
  - `__init__` (method, line 412) `def __init__(self, guest)`
  - `vga_idle` (method, line 415) `def vga_idle(self)`
  - `vga_cursor` (method, line 427) `def vga_cursor(self)`
  - `gfx_frames` (method, line 439) `def gfx_frames(self)`
  - `pixel_oob` (method, line 452) `def pixel_oob(self)`
  - `sys_trace` (method, line 465) `def sys_trace(self)`
  - `_last_frames` (method, line 476) `def _last_frames(self)`
  - `check` (method, line 495) `def check(ok, msg)`
- Depends on: `kernel/time.c`

## tools/mkfs.minifs.py
- Layer: utility
- Doc: mkfs.minifs.py - Create a MiniFS filesystem image for MiniOS.  Usage: python3 mkfs.minifs.py <output_file> <total_blocks
- Language: py
- Symbols:
  - `roundup4` (function, line 22) `def roundup4(v)`
  - `div_round_up` (function, line 25) `def div_round_up(n, d)`
  - `crc16` (function, line 28) `def crc16(data)`
  - `crc32` (function, line 36) `def crc32(data)`
  - `MiniFS` (class, line 44) `class MiniFS`
  - `main` (method, line 241) `def main()`
  - `__init__` (method, line 45) `def __init__(self, total_blocks)`
  - `mark_inodes_used` (method, line 67) `def mark_inodes_used(self, start, count)`
  - `mark_blocks_used` (method, line 71) `def mark_blocks_used(self, start, count)`
  - `alloc_inode` (method, line 75) `def alloc_inode(self)`
  - `alloc_block` (method, line 81) `def alloc_block(self)`
  - `create_root` (method, line 87) `def create_root(self)`
  - `create_inode` (method, line 95) `def create_inode(self, mode)`
  - `inode_set_size` (method, line 102) `def inode_set_size(self, ino, size)`
  - `inode_set_block` (method, line 106) `def inode_set_block(self, ino, logblk, phys)`
  - `add_dir_entry` (method, line 136) `def add_dir_entry(self, dir_ino, name, child_ino, ftype)`
  - `write_file` (method, line 174) `def write_file(self, parent_ino, name, data)`
  - `write_dir` (method, line 191) `def write_dir(self, parent_ino, name)`
  - `serialize` (method, line 197) `def serialize(self)`
  - `pack_tree` (method, line 271) `def pack_tree(parent_ino, path, rel)`

## tools/mkpak1.py
- Layer: utility
- Doc: Build baseq2/pak1.pak carrying the player model.  The Quake 2 shareware pak0.pak omits the player model (players/male/tr
- Language: py
- Symbols:
  - `main` (function, line 29) `def main()`

## tools/mkramdisk.py
- Layer: infrastructure
- Doc: Build a MiniOS ramdisk image from files in a directory tree.  Each packed file is named by its path relative to the shar
- Language: py
- Symbols:
  - `pack_name` (function, line 20) `def pack_name(path, common)`
  - `main` (function, line 30) `def main()`

## tools/mkroots.sh
- Layer: utility
- Doc: mkroots.sh - regenerate tls_roots.h from the DER files in tls_roots_src/.  Provenance of each root (2026 web PKI reality
- Language: sh

## tools/mutate.sh
- Layer: utility
- Doc: Mutation testing for MiniOS.  Each mutation is applied to the source in place, the disk image is rebuilt and the behavio
- Language: sh
- Symbols:
  - `usage` (function, line 51)
  - `restore_sources` (function, line 118)
  - `cleanup` (function, line 125)
  - `record` (function, line 355)
  - `find_index` (function, line 361)

## tools/probe_compute_vga.py
- Layer: utility
- Doc: Docstring: VGA liveness probe during CPU-bound ring-3 compute. Boots os.img headless, runs a command, moves the PS/2 mou
- Language: py
- Symbols:
  - `main` (function, line 22) `def main()`
  - `send` (function, line 55) `def send(line)`
  - `poll` (function, line 61) `def poll(timeout)`
  - `qmp` (function, line 88) `def qmp(obj)`
  - `rel` (function, line 97) `def rel(dx, dy)`
  - `dump` (function, line 104) `def dump(name)`
- Depends on: `kernel/time.c`

## tools/probe_minicraft.py
- Layer: utility
- Doc: probe_minicraft.py -- numeric minicraft probe without any PNG.  Boots os.img headless (display none), runs minicraft in 
- Language: py
- Symbols:
  - `main` (function, line 34) `def main()`
  - `send` (function, line 68) `def send(line)`
  - `poll` (function, line 74) `def poll(timeout)`
  - `grab` (function, line 85) `def grab(pat, timeout)`
  - `qkey` (function, line 143) `def qkey(qcode, down)`
  - `pos` (function, line 154) `def pos(tag)`
- Depends on: `kernel/time.c`

## tools/qga_client.py
- Layer: infrastructure
- Doc: Minimal QEMU guest agent client for MiniOS.  Connects to the guest agent socket (a QEMU chardev mapped to the kernel's C
- Language: py
- Symbols:
  - `send_command` (function, line 33) `def send_command(sock, cmd, args)`
  - `read_reply` (function, line 41) `def read_reply(sock, timeout)`
  - `connect` (function, line 57) `def connect(path)`
  - `main` (function, line 74) `def main(argv)`
- Depends on: `kernel/time.c`

## tools/qga_test.sh
- Layer: testing
- Doc: Quick standalone smoke test for the QEMU guest agent: boots os.img once with the agent socket chardev, waits for the she
- Language: sh
- Symbols:
  - `cleanup` (function, line 25)
  - `check` (function, line 31)
  - `expect_in` (function, line 43)

## tools/repro_gui.py
- Layer: presentation
- Doc: repro_gui.py — reproduce the VGA/mouse state bug after ring-3 programs.  Boots MiniOS with a QMP socket (to inject PS/2 
- Language: py
- Symbols:
  - `read_serial` (function, line 30) `def read_serial(master, timeout)`
  - `QMP` (class, line 46) `class QMP`
  - `main` (method, line 92) `def main()`
  - `__init__` (method, line 47) `def __init__(self, path)`
  - `cmd` (method, line 59) `def cmd(self, obj)`
  - `_recv` (method, line 63) `def _recv(self)`
  - `mouse` (method, line 78) `def mouse(self, dx, dy, left)`
  - `key` (method, line 87) `def key(self, qcode, down)`
  - `send` (method, line 113) `def send(line)`
  - `mouse_state` (method, line 118) `def mouse_state()`
- Depends on: `kernel/time.c`

## tools/test_bdd.sh
- Layer: testing
- Doc: BDD suite for MiniOS: boots the disk image in QEMU and drives the shell over the serial console (COM1). Every scenario s
- Language: sh
- Symbols:
  - `should_run` (function, line 35)
  - `cleanup_stale_qemu` (function, line 43)
  - `scenario` (function, line 54)
  - `scenario_smp` (function, line 74)
  - `expect` (function, line 97)
  - `expect_count` (function, line 119)
  - `refute` (function, line 142)
  - `scenario_uefi` (function, line 167)
  - `http_server_start` (function, line 1028)
  - `http_server_stop` (function, line 1035)
  - `http_fixture_start` (function, line 1040)
  - `http_fixture_stop` (function, line 1047)

## tools/test_call_align.py
- Layer: testing
- Doc: test_call_align.py - verify stack alignment at call sites, both parities.  Compiles a probe with miniGCC whose callees r
- Language: py
- Symbols:
  - `AlignConfig` (class, line 24) `class AlignConfig`
  - `find_minigcc` (method, line 59) `def find_minigcc(explicit)`
  - `run` (method, line 74) `def run(argv)`
  - `main` (method, line 79) `def main(argv)`

## tools/test_codecs.sh
- Layer: testing
- Doc: test_codecs.sh -- exercise the lzss/lz4/aes command-pair tools inside the OS.  The interpreter in-OS suites (test.lua / 
- Language: sh

## tools/test_gui_fashion.py
- Layer: testing
- Doc: test_gui_fashion.py -- GUI proof for the cursor/flicker/quit fixes.  Boots the real image and judges pixels over QMP scr
- Language: py
- Symbols:
  - `note` (function, line 39) `def note(ok, msg)`
  - `Guest` (class, line 45) `class Guest`
  - `meandiff` (method, line 190) `def meandiff(a_path, b_path)`
  - `count_arrows` (method, line 206) `def count_arrows(shot_path)`
  - `main` (method, line 239) `def main()`
  - `__init__` (method, line 46) `def __init__(self)`
  - `_ser` (method, line 70) `def _ser(self)`
  - `_reader` (method, line 82) `def _reader(self)`
  - `snapshot` (method, line 98) `def snapshot(self)`
  - `wait_prompt` (method, line 102) `def wait_prompt(self, timeout)`
  - `wait_for` (method, line 110) `def wait_for(self, marker, timeout)`
  - `send` (method, line 118) `def send(self, line, settle)`
  - `qmp_cmd` (method, line 128) `def qmp_cmd(self, obj)`
  - `_qmp` (method, line 141) `def _qmp(self, obj)`
  - `key` (method, line 149) `def key(self, qcode, down, up)`
  - `rel` (method, line 161) `def rel(self, dx, dy)`
  - `dump` (method, line 168) `def dump(self, name)`
  - `stop` (method, line 175) `def stop(self)`
- Depends on: `kernel/time.c`

## tools/test_gui_icon_cwd.py
- Layer: testing
- Doc: test_gui_icon_cwd.py -- GUI proof that dock launches ignore shell cwd.  Boots the real image, `cd cvm` over serial (the 
- Language: py
- Symbols:
  - `note` (function, line 36) `def note(ok, msg)`
  - `Guest` (class, line 42) `class Guest`
  - `find_icon` (method, line 180) `def find_icon(shot_path, icon_path)`
  - `walk` (method, line 213) `def walk(g, tx, ty, fw, fh)`
  - `main` (method, line 228) `def main()`
  - `__init__` (method, line 43) `def __init__(self)`
  - `_ser` (method, line 67) `def _ser(self)`
  - `_reader` (method, line 79) `def _reader(self)`
  - `snapshot` (method, line 95) `def snapshot(self)`
  - `wait_prompt` (method, line 99) `def wait_prompt(self, timeout)`
  - `send` (method, line 107) `def send(self, line, settle)`
  - `qmp_cmd` (method, line 117) `def qmp_cmd(self, obj)`
  - `_qmp` (method, line 130) `def _qmp(self, obj)`
  - `rel` (method, line 138) `def rel(self, dx, dy)`
  - `click` (method, line 145) `def click(self)`
  - `dump` (method, line 155) `def dump(self, name)`
  - `stop` (method, line 162) `def stop(self)`
- Depends on: `kernel/time.c`

## tools/test_gui_menu.py
- Layer: testing
- Doc: test_gui_menu.py -- serial proof that the minicraft pause menu works.  ESC must open the pause menu even when QMP delive
- Language: py
- Symbols:
  - `main` (function, line 20) `def main()`
- Depends on: `kernel/time.c`, `tools/test_gui_wm.py`

## tools/test_gui_wm.py
- Layer: testing
- Doc: test_gui_wm.py -- GUI proof that graphics windows survive the WM.  Serial `wm` commands call the same functions as the r
- Language: py
- Symbols:
  - `note` (function, line 40) `def note(ok, msg)`
  - `Guest` (class, line 46) `class Guest`
  - `meandiff` (method, line 204) `def meandiff(a_path, b_path)`
  - `main` (method, line 214) `def main()`
  - `__init__` (method, line 47) `def __init__(self)`
  - `_ser` (method, line 75) `def _ser(self)`
  - `_reader` (method, line 87) `def _reader(self)`
  - `snapshot` (method, line 103) `def snapshot(self)`
  - `wait_prompt` (method, line 107) `def wait_prompt(self, timeout)`
  - `send` (method, line 115) `def send(self, line, settle)`
  - `qmp_cmd` (method, line 130) `def qmp_cmd(self, obj)`
  - `_qmp` (method, line 143) `def _qmp(self, obj)`
  - `key` (method, line 151) `def key(self, qcode, down, up)`
  - `rel` (method, line 163) `def rel(self, dx, dy)`
  - `btn` (method, line 170) `def btn(self, down)`
  - `dump` (method, line 176) `def dump(self, name)`
  - `stop` (method, line 183) `def stop(self)`
- Depends on: `kernel/time.c`
- Imported by: `tools/test_gui_menu.py`, `tools/test_gui_zoom.py`

## tools/test_gui_zoom.py
- Layer: testing
- Doc: test_gui_zoom.py -- pixel proof that GFX_ZOOM doubles the game window.  Boots MiniOS headless (display none, QMP screend
- Language: py
- Symbols:
  - `main` (function, line 22) `def main()`
- Depends on: `kernel/time.c`, `tools/test_gui_wm.py`

## tools/test_http_server.py
- Layer: testing
- Doc: Host-side HTTP fixture for the freedom BDD scenarios.  Serves behaviours that python -m http.server cannot produce:  /ch
- Language: py
- Symbols:
  - `Handler` (class, line 21) `class Handler(BaseHTTPRequestHandler)`
  - `do_GET` (method, line 24) `def do_GET(self)`
  - `log_message` (method, line 114) `def log_message(self, fmt)`
- Depends on: `kernel/time.c`

## tools/test_lisp.py
- Layer: testing
- Doc: Host test suite for the MiniOS Lisp interpreter.  Builds progs/lisp/lisp.c with the host toolchain and drives the result
- Language: py
- Symbols:
  - `LispConfig` (class, line 28) `class LispConfig`
  - `LispTest` (class, line 37) `class LispTest`
  - `build_binary` (method, line 308) `def build_binary(source, output)`
  - `main` (method, line 321) `def main()`
  - `__init__` (method, line 40) `def __init__(self, binary, suite)`
  - `check` (method, line 47) `def check(self, name, actual, expected)`
  - `run_expr` (method, line 58) `def run_expr(self, code)`
  - `check_eval` (method, line 65) `def check_eval(self, name, code, stdout)`
  - `check_error` (method, line 70) `def check_error(self, name, code, fragment)`
  - `run_all` (method, line 76) `def run_all(self)`
  - `check_file_roundtrip` (method, line 121) `def check_file_roundtrip(self)`
  - `check_exit_code` (method, line 135) `def check_exit_code(self)`
  - `check_cli` (method, line 142) `def check_cli(self)`
  - `check_suite_language_only` (method, line 159) `def check_suite_language_only(self)`
  - `check_minigcc_subset` (method, line 177) `def check_minigcc_subset(self)`
  - `report` (method, line 300) `def report(self)`

## tools/test_sb16.sh
- Layer: testing
- Doc: test_sb16.sh — targeted BDD harness for the SB16 audio path.  Boots the disk image once with the SB16 device attached (h
- Language: sh
- Symbols:
  - `fail_msg` (function, line 45)

## tools/tls_test.py
- Layer: testing
- Doc: Host-side TLS test driver for the MiniOS kernel TLS client.  Generates a throwaway CA and server certificates with opens
- Language: py
- Symbols:
  - `run` (function, line 26) `def run(cmd)`
  - `check` (function, line 30) `def check(cmd)`
  - `gen_certs` (function, line 37) `def gen_certs()`
  - `der_bytes` (function, line 154) `def der_bytes(pem_path)`
  - `rsa_params` (function, line 162) `def rsa_params(key_path)`
  - `ec_pub` (function, line 172) `def ec_pub(key_path)`
  - `c_bytes` (function, line 183) `def c_bytes(data, name)`
  - `gen_header` (function, line 191) `def gen_header(p)`
  - `Server` (class, line 241) `class Server(Thread)`
  - `serve` (method, line 280) `def serve(cert, key)`
  - `serve_openssl` (method, line 288) `def serve_openssl(cert, key, chain)`
  - `expect` (method, line 306) `def expect(bin_path, args, want_zero, marker)`
  - `main` (method, line 319) `def main()`
  - `server_cert` (method, line 61) `def server_cert(name, algo, curve, ca_name, ca_algo, curve_ca, extra, subj)`
  - `__init__` (method, line 242) `def __init__(self, cert, key, tls13_ok)`
  - `run` (method, line 248) `def run(self)`
- Depends on: `kernel/time.c`

## tools/wl_scoped.sh
- Layer: utility
- Doc: Docstring: Scoped Wayland-mini validation for the tiled ring-3 compositor. Runs host wire, mailbox and palette tests, re
- Language: sh
- Symbols:
  - `say` (function, line 8)
  - `die` (function, line 9)
  - `mut` (function, line 77)
  - `mutm` (function, line 84)

## tools/wm_layout_sync.py
- Layer: presentation
- Doc: Docstring: Synchronize the WM layout manifest from source truth.  I read wm_layout.h and tests/test_wm.c and regenerate 
- Language: py
- Symbols:
  - `WmLayoutSyncConfig` (class, line 17) `class WmLayoutSyncConfig`
  - `WmLayoutSyncResult` (class, line 36) `class WmLayoutSyncResult`
  - `WmLayoutSync` (class, line 46) `class WmLayoutSync`
  - `parse_args` (method, line 151) `def parse_args(argv)`
  - `main` (method, line 159) `def main(argv)`
  - `__init__` (method, line 20) `def __init__(self, root)`
  - `__init__` (method, line 39) `def __init__(self, modes, symbols, checks)`
  - `__init__` (method, line 49) `def __init__(self, config)`
  - `discover` (method, line 53) `def discover(self)`
  - `render` (method, line 66) `def render(self, result)`
  - `synchronize` (method, line 101) `def synchronize(self, write)`
  - `_read_text` (method, line 110) `def _read_text(self, path)`
  - `_extract_modes` (method, line 116) `def _extract_modes(self, header_text)`
  - `_extract_symbols` (method, line 125) `def _extract_symbols(self, header_text)`
  - `_count_layout_checks` (method, line 133) `def _count_layout_checks(self, tests_text)`
  - `_require_modes` (method, line 138) `def _require_modes(self, modes)`
  - `_require_symbols` (method, line 144) `def _require_symbols(self, symbols)`

## tools/wm_scoped.sh
- Layer: utility
- Doc: Docstring: Scoped WM validation for Alt-Tab and tile across all windows. Runs host WM unit tests, rebuilds touched kerne
- Language: sh
- Symbols:
  - `say` (function, line 8)
  - `die` (function, line 9)
