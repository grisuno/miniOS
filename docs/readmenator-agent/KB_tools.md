# Subsystem: tools (page 1 of 2)
Pages: [KB_tools.md](KB_tools.md), [KB_tools_p2.md](KB_tools_p2.md)

## tools/abi_stamp.c
- Doc: Docstring: tools/abi_stamp.c -- Build-time ABI manifest generator.
- Layer: utility
- Language: c
- Symbols:
  - `main` (function, line 14) `int main(void)`
- Depends on: `progs/minios_abi.h`

## tools/boot_run.sh
- Doc: boot the MiniOS image in QEMU and drive the shell over the serial console with a list of...
- Layer: utility
- Language: sh

## tools/boot_wl.py
- Doc: boot the miniOS Wayland-mini desktop in one step.
- Layer: utility
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
- Doc: MiniOS syscall numbers vs Linux x86-64 truth.
- Layer: utility
- Language: py
- Symbols:
  - `normalize` (function, line 128) `def normalize(minios_name)`
  - `parse_abi` (function, line 132) `def parse_abi(path)`
  - `parse_dispatch` (function, line 143) `def parse_dispatch(path)`
  - `main` (function, line 156) `def main()`

## tools/check_addons.py
- Doc: validate the MiniOS addon marketplace index.
- Layer: utility
- Language: py
- Symbols:
  - `load_parser` (function, line 22) `def load_parser()`
  - `main` (function, line 31) `def main()`

## tools/check_cohesion.py
- Doc: Architectural cohesion gate for MiniOS CI.
- Layer: utility
- Language: py
- Symbols:
  - `load_cpg` (function, line 23) `def load_cpg(path)`
  - `compute_cohesion` (function, line 31) `def compute_cohesion(community_nodes, community_edges)`
  - `extract_communities` (function, line 42) `def extract_communities(cpg)`
  - `main` (function, line 58) `def main()`

## tools/check_complexity.py
- Doc: Kernel complexity gate for MiniOS CI.
- Layer: utility
- Language: py
- Symbols:
  - `count_symbols` (function, line 24) `def count_symbols(filepath)`
  - `load_approval` (function, line 46) `def load_approval(policy_path)`
  - `main` (function, line 61) `def main()`

## tools/check_fork_stubs.py
- Doc: Fail-closed stub gate for unimplemented process syscalls.  vfork has no implementation in this...
- Layer: testing
- Language: py
- Symbols:
  - `Config` (class, line 18) `class Config`
  - `handler_body` (method, line 27) `def handler_body(text, name)`
  - `check_stubs` (method, line 37) `def check_stubs(text, cfg)`
  - `main` (method, line 52) `def main()`

## tools/check_kb_sync.py
- Doc: Verify KNOWLEDGE_BASE.md is in sync with code.
- Layer: utility
- Language: py
- Symbols:
  - `regenerate_kb` (function, line 24) `def regenerate_kb()`
  - `main` (function, line 43) `def main()`

## tools/check_mutant_anchors.py
- Doc: Verify every mutate.sh mutant anchor matches its target file.
- Layer: utility
- Language: py
- Symbols:
  - `Config` (class, line 17) `class Config`
  - `bash_unquote` (method, line 26) `def bash_unquote(expr)`
  - `parse_mutations` (method, line 41) `def parse_mutations(text)`
  - `anchor_matches` (method, line 67) `def anchor_matches(repo, target, expr)`
  - `main` (method, line 86) `def main()`

## tools/check_spin_discipline.py
- Doc: Check spinlock call-site discipline across kernel C sources.
- Layer: utility
- Language: py
- Symbols:
  - `Config` (class, line 23) `class Config`
  - `iter_functions` (method, line 38) `def iter_functions(path)`
  - `check_file` (method, line 64) `def check_file(path)`
  - `main` (method, line 99) `def main(argv)`

## tools/check_surprising.py
- Doc: Detect surprising architectural connections.
- Layer: utility
- Language: py
- Symbols:
  - `load_cpg` (function, line 25) `def load_cpg(path)`
  - `build_graph` (function, line 33) `def build_graph(cpg)`
  - `bfs_min_hops` (function, line 56) `def bfs_min_hops(nodes, edges, source, target_community, max_hops)`
  - `find_surprising_connections` (function, line 87) `def find_surprising_connections(nodes, edges, min_hops)`
  - `main` (function, line 118) `def main()`

## tools/check_syscall_sanitize.py
- Doc: Scoped audit gate for syscall user-pointer sanitization.
- Layer: utility
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

## tools/clip_bridge.py
- Doc: Host to MiniOS clipboard bridge plan builder.
- Layer: utility
- Language: py
- Symbols:
  - `ClipBridgeConfig` (class, line 30) `class ClipBridgeConfig`
  - `valid_dst` (method, line 41) `def valid_dst(name, cfg)`
  - `printable_line` (method, line 52) `def printable_line(line, cfg)`
  - `build_plan` (method, line 59) `def build_plan(text, dst, cfg)`
  - `main` (method, line 84) `def main(argv)`

## tools/doom_pwad.py
- Doc: grid map to vanilla Doom PWAD writer and checker.
- Layer: utility
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
- Imported by: `tests/test_doom_pwad.py`

## tools/extract_shell.py
- Doc: tools/extract_shell.py -- Plan for Phase 6.1 shell extraction.
- Layer: utility
- Language: py

## tools/gdb_repro.py
- Doc: — drive a graphics-program sequence under the GDB stub.
- Layer: utility
- Language: py
- Symbols:
  - `rs` (function, line 23) `def rs(m, t)`
  - `main` (function, line 27) `def main()`
  - `send` (function, line 65) `def send(line)`
  - `quit_doom` (function, line 70) `def quit_doom()`
- Depends on: `kernel/time.c`

## tools/gen_desktop_pngs.py
- Doc: build MiniOS desktop art from user-supplied PNGs.
- Layer: utility
- Language: py
- Symbols:
  - `write_atomic` (function, line 69) `def write_atomic(img, path)`
  - `main` (function, line 75) `def main()`

## tools/gen_icons.py
- Doc: generate 32x32 RGBA PNG icon files for the MiniOS desktop.
- Layer: utility
- Language: py
- Symbols:
  - `make_png` (function, line 179) `def make_png(pixels, palette, width, height)`
  - `make_chunk` (function, line 209) `def make_chunk(chunk_type, data)`
  - `main` (function, line 214) `def main()`

## tools/gen_minifs.py
- Doc: Generate minifs.c for MiniOS.
- Layer: utility
- Language: py

## tools/gen_zip_fixtures.py
- Doc: generate the zip test fixtures shipped on the ramdisk.
- Layer: data_access
- Language: py
- Symbols:
  - `write_zip` (function, line 28) `def write_zip(path, entries)`
  - `main` (function, line 42) `def main()`

## tools/install.sh
- Layer: utility
- Language: sh

## tools/kernel_feature_survey.py
- Doc: verify which C features the MiniOS kernel needs.
- Layer: utility
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
- Doc: Docstring: Scoped Lisp validation for the MiniOS interpreter contract.
- Layer: utility
- Language: sh
- Symbols:
  - `say` (function, line 8)
  - `die` (function, line 9)
  - `mutant` (function, line 20)
  - `lisp_mut` (function, line 41)
  - `mut_usage` (function, line 63)

## tools/make_usb.sh
- Doc: Build the MiniOS bootable USB image and optionally write it to a device.
- Layer: utility
- Language: sh
- Symbols:
  - `usage` (function, line 40)
  - `wizard` (function, line 56)

## tools/minifs_dump.py
- Doc: Dump/inspect a MiniFS filesystem image.
- Layer: utility
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
- Doc: Check MiniFS filesystem consistency.
- Layer: utility
- Language: py
- Symbols:
  - `u16` (function, line 13) `def u16(d, o)`
  - `u32` (function, line 14) `def u32(d, o)`
  - `crc32` (function, line 15) `def crc32(data)`
  - `FSCK` (class, line 23) `class FSCK`
  - `main` (method, line 152) `def main()`
  - `__init__` (method, line 24) `def __init__(self, fn)`
  - `_find_base` (method, line 31) `def _find_base(self)`
  - `blk` (method, line 49) `def blk(self, n)`
  - `_sb` (method, line 52) `def _sb(self)`
  - `inode` (method, line 58) `def inode(self, i)`
  - `inode_crc_ok` (method, line 65) `def inode_crc_ok(self, i)`
  - `read` (method, line 71) `def read(self, ino)`
  - `err` (method, line 86) `def err(self, msg)`
  - `mark_block` (method, line 88) `def mark_block(self, n)`
  - `scan_inode` (method, line 93) `def scan_inode(self, i)`
  - `scan_dir` (method, line 105) `def scan_dir(self, ino)`
  - `run` (method, line 137) `def run(self)`

## tools/minifs_saves.py
- Doc: preserve the guest's saves/ dir across image rebuilds.
- Layer: utility
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
- Doc: — drive MiniOS through the MCP bridge, not by hand.
- Layer: utility
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
- Doc: — inject VGA-mode input and capture the framebuffer.
- Layer: utility
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
- Doc: host-side ring-minus-one debugger for MiniOS.
- Layer: utility
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
- Doc: Create a MiniFS filesystem image for MiniOS.
- Layer: utility
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
- Doc: Build baseq2/pak1.pak carrying the player model.
- Layer: utility
- Language: py
- Symbols:
  - `main` (function, line 29) `def main()`

## tools/mkramdisk.py
- Doc: Build a MiniOS ramdisk image from files in a directory tree.
- Layer: utility
- Language: py
- Symbols:
  - `pack_name` (function, line 38) `def pack_name(path, common)`
  - `main` (function, line 48) `def main()`

## tools/mkroots.sh
- Doc: regenerate tls_roots.h from the DER files in tls_roots_src/.
- Layer: utility
- Language: sh

## tools/mkvocab.py
- Doc: Build progs/topogpt3/vocab.bin from the GPT-2 encoder.json.
- Layer: utility
- Language: py
- Symbols:
  - `bytes_to_unicode` (function, line 18) `def bytes_to_unicode()`
  - `main` (function, line 35) `def main(encoder_path, vocab_path)`

## tools/mutate.sh
- Doc: Mutation testing for MiniOS.
- Layer: utility
- Language: sh
- Symbols:
  - `usage` (function, line 51)
  - `restore_sources` (function, line 126)
  - `cleanup` (function, line 133)
  - `record` (function, line 410)
  - `find_index` (function, line 416)

## tools/probe_compute_vga.py
- Doc: Docstring: VGA liveness probe during CPU-bound ring-3 compute.
- Layer: utility
- Language: py
- Symbols:
  - `main` (function, line 22) `def main()`
  - `send` (function, line 55) `def send(line)`
  - `poll` (function, line 61) `def poll(timeout)`
  - `qmp` (function, line 88) `def qmp(obj)`
  - `rel` (function, line 97) `def rel(dx, dy)`
  - `dump` (function, line 104) `def dump(name)`
- Depends on: `kernel/time.c`


Next: [KB_tools_p2.md](KB_tools_p2.md)
