# API (page 19 of 19)
Previous: [API_p18.md](API_p18.md)

## tools/check_complexity.py
- `count_symbols` (function) `tools/check_complexity.py:24` `def count_symbols(filepath)` -- Count top-level function and global variable definitions.
- `load_approval` (function) `tools/check_complexity.py:46` `def load_approval(policy_path)` -- Load explicit complexity approval from ARCH_POLICY.yaml.
- `main` (function) `tools/check_complexity.py:61` `def main()`

## tools/check_kb_sync.py
- `regenerate_kb` (function) `tools/check_kb_sync.py:24` `def regenerate_kb()` -- Attempt to regenerate KNOWLEDGE_BASE.md using readmenator.
- `main` (function) `tools/check_kb_sync.py:43` `def main()`

## tools/check_mutant_anchors.py
- `Config.bash_unquote` (method) `tools/check_mutant_anchors.py:26` `def bash_unquote(expr)` -- Collapse the escapes bash applies inside the MUTATIONS string.
- `Config.unescaped_quote` (method) `tools/check_mutant_anchors.py:41` `def unescaped_quote(expr)` -- True when expr holds a double quote bash would not keep.
- `Config.parse_mutations` (method) `tools/check_mutant_anchors.py:58` `def parse_mutations(text)` -- Extract (name, expression, target) triples from the MUTATIONS block.
- `Config.anchor_matches` (method) `tools/check_mutant_anchors.py:84` `def anchor_matches(repo, target, expr)` -- Apply the sed expression to a scratch copy; True when it changes it.
- `Config.main` (method) `tools/check_mutant_anchors.py:105` `def main()` -- Entry point: report anchors that change nothing and exit nonzero.

## tools/check_spin_discipline.py
- `Config.iter_functions` (method) `tools/check_spin_discipline.py:38` `def iter_functions(path)` -- Yield (name, first_line, body_lines) with a brace-depth split.
- `Config.check_file` (method) `tools/check_spin_discipline.py:64` `def check_file(path)` -- Return a list of violation strings for one translation unit.
- `Config.main` (method) `tools/check_spin_discipline.py:99` `def main(argv)` -- Walk the configured roots and fail closed on any violation.

## tools/check_surprising.py
- `load_cpg` (function) `tools/check_surprising.py:25` `def load_cpg(path)` -- Load and parse the CPG JSON-LD file.
- `build_graph` (function) `tools/check_surprising.py:33` `def build_graph(cpg)` -- Build adjacency list from CPG nodes and edges.
- `bfs_min_hops` (function) `tools/check_surprising.py:56` `def bfs_min_hops(nodes, edges, source, target_community, max_hops)` -- BFS from source to any node in target_community, returning hop count.
- `find_surprising_connections` (function) `tools/check_surprising.py:87` `def find_surprising_connections(nodes, edges, min_hops)` -- Find connections of min_hops or more between distinct communities.
- `main` (function) `tools/check_surprising.py:118` `def main()`

## tools/check_syscall_sanitize.py
- `Config.split_functions` (method) `tools/check_syscall_sanitize.py:69` `def split_functions(lines)` -- Yield (name, start, body_lines) triples using brace depth.
- `Config.checked_names` (method) `tools/check_syscall_sanitize.py:112` `def checked_names(body)` -- Return identifiers named inside sanitizer checks in a body.
- `Config.delegated_only` (method) `tools/check_syscall_sanitize.py:122` `def delegated_only(body, alias)` -- Decide whether an alias flows only into sanitizing callees.
- `Config.split_top_args` (method) `tools/check_syscall_sanitize.py:143` `def split_top_args(argtext)` -- Split a call argument list on top-level commas only.
- `Config.audit_body` (method) `tools/check_syscall_sanitize.py:162` `def audit_body(name, body)` -- Return violation strings for one function body.
- `Config.audit_file` (method) `tools/check_syscall_sanitize.py:217` `def audit_file(path)` -- Audit every handler in one file, return violation strings.
- `Config.main` (method) `tools/check_syscall_sanitize.py:228` `def main()` -- Entry point used by lint and CI.

## tools/clip_bridge.py
- `ClipBridgeConfig.valid_dst` (method) `tools/clip_bridge.py:41` `def valid_dst(name, cfg)` -- True when name is a safe guest path.
- `ClipBridgeConfig.printable_line` (method) `tools/clip_bridge.py:52` `def printable_line(line, cfg)` -- True when every char survives the kernel readline.
- `ClipBridgeConfig.build_plan` (method) `tools/clip_bridge.py:59` `def build_plan(text, dst, cfg)` -- Return (ok, lines, diagnostic) for carrying text to dst.
- `ClipBridgeConfig.main` (method) `tools/clip_bridge.py:84` `def main(argv)` -- Entry point: clip_bridge.py <src-file> <dst-name>.

## tools/doom_pwad.py
Imported by: `tests/test_doom_pwad.py`
- `PwadError.pad_tex` (method) `tools/doom_pwad.py:165` `def pad_tex(raw)` -- Return a texture or flat name padded to its 8-byte field.
- `PwadError.parse_grid` (method) `tools/doom_pwad.py:172` `def parse_grid(text)` -- Parse grid text into rows, refusing empty or ragged input.
- `PwadError.grid_extents` (method) `tools/doom_pwad.py:195` `def grid_extents(rows)` -- Return coordinate bounds of the lattice in map units.
- `PwadError.is_wall` (method) `tools/doom_pwad.py:203` `def is_wall(rows, row, col)` -- Treat out-of-bounds cells as solid wall so maps stay closed.
- `PwadError.flood_reachable` (method) `tools/doom_pwad.py:210` `def flood_reachable(rows)` -- Return the walkable set reachable from the player start tile.
- `PwadError.validate_grid` (method) `tools/doom_pwad.py:240` `def validate_grid(rows)` -- Enforce single player, single exit, and full reachability.
- `PwadError.cell_corners` (method) `tools/doom_pwad.py:269` `def cell_corners(row, col)` -- Return cell corners as (x0, x1, y_top, y_bottom) in map units.
- `PwadError.cell_class` (method) `tools/doom_pwad.py:279` `def cell_class(cell)` -- Classify a walkable cell: doors stand alone, styles never merge.
- `PwadError.label_regions` (method) `tools/doom_pwad.py:291` `def label_regions(rows)` -- Flood same-class walkable cells into region ids; walls stay -1.
- `PwadError.region_sector` (method) `tools/doom_pwad.py:326` `def region_sector(region, door_tag)` -- Map a labelled region to its sector record fields and wall skin.
- `PwadError.compile_geometry` (method) `tools/doom_pwad.py:371` `def compile_geometry(rows, exit_pos, wall_side)` -- Compile edges into vertexes, two-sided rooms and tagged doors.
- `PwadError.vertex` (method) `tools/doom_pwad.py:386` `def vertex(x, y)` -- Deduplicate lattice points shared by adjacent edges.
- `PwadError.compile_things` (method) `tools/doom_pwad.py:485` `def compile_things(rows)` -- Compile thing stamps into mapthing records in scan order.
- `PwadError.seg_angle` (method) `tools/doom_pwad.py:506` `def seg_angle(dx, dy)` -- Return the stored short angle for a seg direction vector.
- `PwadError.build_lumps` (method) `tools/doom_pwad.py:516` `def build_lumps(rows)` -- Compile a validated grid into the eleven E1M1 lump payloads.
- `PwadError.build_pwad` (method) `tools/doom_pwad.py:597` `def build_pwad(rows)` -- Assemble lump payloads into a complete PWAD byte string.
- `PwadError.read_pwad` (method) `tools/doom_pwad.py:616` `def read_pwad(data)` -- Split PWAD bytes into header fields and an ordered lump table.
- `PwadError.check_pwad` (method) `tools/doom_pwad.py:639` `def check_pwad(data)` -- Validate lump order, record sizes and cross-lump references.
- `PwadError.payload` (method) `tools/doom_pwad.py:650` `def payload(name)` -- Slice one lump payload out of the file image.
- `PwadError.check_multiple` (method) `tools/doom_pwad.py:655` `def check_multiple(name, fmt)` -- Require the lump length to hold whole records only.
- `PwadError.cmd_build` (method) `tools/doom_pwad.py:816` `def cmd_build(grid_path, out_path)` -- Build a PWAD from a grid file, refusing to write on any error.
- `PwadError.cmd_check` (method) `tools/doom_pwad.py:826` `def cmd_check(path)` -- Validate a PWAD file and report its lump census on success.
- `PwadError.main` (method) `tools/doom_pwad.py:834` `def main(argv)` -- Dispatch the build, check and info verbs with host-safe errors.

## tools/gdb_repro.py
Depends on: `kernel/time.c`
- `rs` (function) `tools/gdb_repro.py:23` `def rs(m, t)`
- `main` (function) `tools/gdb_repro.py:27` `def main()`
- `send` (function) `tools/gdb_repro.py:65` `def send(line)`
- `quit_doom` (function) `tools/gdb_repro.py:70` `def quit_doom()`

## tools/gen_desktop_pngs.py
- `write_atomic` (function) `tools/gen_desktop_pngs.py:69` `def write_atomic(img, path)`
- `main` (function) `tools/gen_desktop_pngs.py:75` `def main()`

## tools/gen_icons.py
- `make_png` (function) `tools/gen_icons.py:179` `def make_png(pixels, palette, width, height)` -- Create a minimal indexed-colour PNG from pixel indices and a palette.
- `make_chunk` (function) `tools/gen_icons.py:209` `def make_chunk(chunk_type, data)`
- `main` (function) `tools/gen_icons.py:214` `def main()`

## tools/gen_zip_fixtures.py
- `write_zip` (function) `tools/gen_zip_fixtures.py:28` `def write_zip(path, entries)` -- entries: list of (name, data_or_None).  data None marks a directory.
- `main` (function) `tools/gen_zip_fixtures.py:42` `def main()`

## tools/kernel_feature_survey.py
- `SurveyConfig.iter_sources` (method) `tools/kernel_feature_survey.py:34` `def iter_sources(root)` -- Yield C source paths under root, skipping vendored and cache dirs.
- `SurveyConfig.find_fnptr_hits` (method) `tools/kernel_feature_survey.py:43` `def find_fnptr_hits(path, text)` -- Return line numbers declaring function pointers.
- `SurveyConfig.find_asm_constraints` (method) `tools/kernel_feature_survey.py:49` `def find_asm_constraints(path, text)` -- Return sorted constraint letters used in extended asm.
- `SurveyConfig.count_params` (method) `tools/kernel_feature_survey.py:59` `def count_params(params)` -- Count parameters, treating void and empty as zero.
- `SurveyConfig.survey` (method) `tools/kernel_feature_survey.py:67` `def survey(root)` -- Collect findings per category across all sources.
- `SurveyConfig.render_text` (method) `tools/kernel_feature_survey.py:103` `def render_text(findings)` -- Render findings as plain text.
- `SurveyConfig.main` (method) `tools/kernel_feature_survey.py:122` `def main(argv)` -- Entry point for the survey tool.

## tools/lisp_scoped.sh
- `say` (function) `tools/lisp_scoped.sh:8`
- `die` (function) `tools/lisp_scoped.sh:9`
- `mutant` (function) `tools/lisp_scoped.sh:20`
- `lisp_mut` (function) `tools/lisp_scoped.sh:41`
- `mut_usage` (function) `tools/lisp_scoped.sh:63`

## tools/make_usb.sh
- `usage` (function) `tools/make_usb.sh:40`
- `wizard` (function) `tools/make_usb.sh:56`

## tools/minifs_dump.py
- `u16` (function) `tools/minifs_dump.py:13` `def u16(d, o)`
- `u32` (function) `tools/minifs_dump.py:14` `def u32(d, o)`
- `mode_str` (function) `tools/minifs_dump.py:16` `def mode_str(m)`
- `FS.__init__` (method) `tools/minifs_dump.py:26` `def __init__(self, fn)`
- `FS.blk` (method) `tools/minifs_dump.py:29` `def blk(self, n)`
- `FS.inode` (method) `tools/minifs_dump.py:38` `def inode(self, i)`
- `FS.read` (method) `tools/minifs_dump.py:47` `def read(self, ino)`
- `FS.resolve` (method) `tools/minifs_dump.py:67` `def resolve(self, path)`
- `FS.ls` (method) `tools/minifs_dump.py:86` `def ls(self, ino, prefix)`
- `FS.main` (method) `tools/minifs_dump.py:105` `def main()`

## tools/minifs_fsck.py
- `u16` (function) `tools/minifs_fsck.py:13` `def u16(d, o)`
- `u32` (function) `tools/minifs_fsck.py:14` `def u32(d, o)`
- `crc32` (function) `tools/minifs_fsck.py:15` `def crc32(data)`
- `FSCK.__init__` (method) `tools/minifs_fsck.py:24` `def __init__(self, fn)`
- `FSCK.blk` (method) `tools/minifs_fsck.py:49` `def blk(self, n)`
- `FSCK.inode` (method) `tools/minifs_fsck.py:58` `def inode(self, i)`
- `FSCK.inode_crc_ok` (method) `tools/minifs_fsck.py:65` `def inode_crc_ok(self, i)`
- `FSCK.read` (method) `tools/minifs_fsck.py:71` `def read(self, ino)`
- `FSCK.err` (method) `tools/minifs_fsck.py:86` `def err(self, msg)`
- `FSCK.mark_block` (method) `tools/minifs_fsck.py:88` `def mark_block(self, n)`
- `FSCK.scan_inode` (method) `tools/minifs_fsck.py:93` `def scan_inode(self, i)`
- `FSCK.scan_dir` (method) `tools/minifs_fsck.py:105` `def scan_dir(self, ino)`
- `FSCK.bitmap_free` (method) `tools/minifs_fsck.py:137` `def bitmap_free(self, start, count)` -- Clear bits among the first count bits of the bitmap at block start.
- `FSCK.check_counters` (method) `tools/minifs_fsck.py:146` `def check_counters(self)` -- The superblock free counters must match the bitmaps, or every free-space report (and the kernel's own decrement)...
- `FSCK.run` (method) `tools/minifs_fsck.py:161` `def run(self)`
- `FSCK.main` (method) `tools/minifs_fsck.py:173` `def main()`

## tools/minifs_saves.py
- `u16` (function) `tools/minifs_saves.py:53` `def u16(d, o)`
- `u32` (function) `tools/minifs_saves.py:57` `def u32(d, o)`
- `Image.__init__` (method) `tools/minifs_saves.py:64` `def __init__(self, fn, base)`
- `Image.close` (method) `tools/minifs_saves.py:72` `def close(self)`
- `Image.blk` (method) `tools/minifs_saves.py:75` `def blk(self, n)`
- `FS.__init__` (method) `tools/minifs_saves.py:86` `def __init__(self, img)`
- `FS.inode` (method) `tools/minifs_saves.py:95` `def inode(self, i)`
- `FS.is_dir` (method) `tools/minifs_saves.py:110` `def is_dir(self, st)`
- `FS.read_file` (method) `tools/minifs_saves.py:113` `def read_file(self, ino)`
- `FS.listdir` (method) `tools/minifs_saves.py:146` `def listdir(self, ino)`
- `FS.read_file_dir` (method) `tools/minifs_saves.py:165` `def read_file_dir(self, ino)`
- `FS.read_file_raw` (method) `tools/minifs_saves.py:173` `def read_file_raw(self, st)`
- `FS.resolve` (method) `tools/minifs_saves.py:197` `def resolve(self, path)`
- `FS.valid_name` (method) `tools/minifs_saves.py:216` `def valid_name(nm)`
- `FS.strict_name` (method) `tools/minifs_saves.py:224` `def strict_name(nm)`
- `FS.find_partition_base` (method) `tools/minifs_saves.py:233` `def find_partition_base(fn)` -- Locate the MiniFS partition inside a host image file.
- `FS.cmd_backup` (method) `tools/minifs_saves.py:271` `def cmd_backup(img_path, stage)`
- `FS.walk` (method) `tools/minifs_saves.py:293` `def walk(dir_ino, rel)`
- `FS.main` (method) `tools/minifs_saves.py:343` `def main(argv)`

## tools/minios_cli.py
Depends on: `kernel/time.c`
- `Client.__init__` (method) `tools/minios_cli.py:39` `def __init__(self)`
- `Client.request` (method) `tools/minios_cli.py:56` `def request(self, method, params)`
- `Client.tool` (method) `tools/minios_cli.py:77` `def tool(self, name, params)`
- `Client.close` (method) `tools/minios_cli.py:87` `def close(self)`
- `Client.main` (method) `tools/minios_cli.py:100` `def main()`

## tools/minios_gui.py
Depends on: `kernel/time.c`
- `read_serial` (function) `tools/minios_gui.py:50` `def read_serial(master, timeout)`
- `QMP.__init__` (method) `tools/minios_gui.py:67` `def __init__(self, path)`
- `QMP.cmd` (method) `tools/minios_gui.py:79` `def cmd(self, obj)`
- `QMP.mouse` (method) `tools/minios_gui.py:98` `def mouse(self, dx, dy, click)`
- `QMP.key` (method) `tools/minios_gui.py:108` `def key(self, qcode, up)`
- `QMP.screendump` (method) `tools/minios_gui.py:114` `def screendump(self, path)`
- `QMP.main` (method) `tools/minios_gui.py:118` `def main()`

## tools/minios_hyper.py
Depends on: `kernel/time.c`
- `RspCodec.encode` (method) `tools/minios_hyper.py:77` `def encode(payload)` -- Wrap raw payload bytes into a $...#cs frame.
- `RspCodec.decode` (method) `tools/minios_hyper.py:85` `def decode(frame)` -- Extract payload from a $...#cs frame, empty bytes on malformed.
- `QmpChannel.__init__` (method) `tools/minios_hyper.py:99` `def __init__(self, path)`
- `QmpChannel.raw` (method) `tools/minios_hyper.py:117` `def raw(self, obj)` -- Send one QMP object and return the raw reply bytes.
- `QmpChannel.screendump` (method) `tools/minios_hyper.py:121` `def screendump(self, path)` -- Ask QEMU to write the VGA frame to path.
- `QmpChannel.rel` (method) `tools/minios_hyper.py:126` `def rel(self, dx, dy)` -- Inject relative mouse motion.
- `QmpChannel.key` (method) `tools/minios_hyper.py:132` `def key(self, qcode)` -- Tap one qemu keycode down and up.
- `QmpChannel.status` (method) `tools/minios_hyper.py:141` `def status(self)` -- Query the VM run state.
- `QmpChannel.close` (method) `tools/minios_hyper.py:145` `def close(self)`
- `GdbChannel.__init__` (method) `tools/minios_hyper.py:155` `def __init__(self, port)`
- `GdbChannel.regs` (method) `tools/minios_hyper.py:181` `def regs(self)` -- Return raw g-packet bytes, empty on failure.
- `GdbChannel.read_mem` (method) `tools/minios_hyper.py:185` `def read_mem(self, addr, length)` -- Read length bytes at addr, None on failure or malformed reply.
- `GdbChannel.halt` (method) `tools/minios_hyper.py:195` `def halt(self)`
- `GdbChannel.cont` (method) `tools/minios_hyper.py:201` `def cont(self)`
- `GdbChannel.close` (method) `tools/minios_hyper.py:204` `def close(self)`
- `Guest.__init__` (method) `tools/minios_hyper.py:214` `def __init__(self, with_gdb)`
- `Guest.snapshot` (method) `tools/minios_hyper.py:276` `def snapshot(self)`
- `Guest.wait_for` (method) `tools/minios_hyper.py:280` `def wait_for(self, marker, timeout)`
- `Guest.send` (method) `tools/minios_hyper.py:288` `def send(self, line, settle)`
- `Guest.qmp_chan` (method) `tools/minios_hyper.py:298` `def qmp_chan(self)`
- `Guest.gdb_chan` (method) `tools/minios_hyper.py:303` `def gdb_chan(self)`
- `Guest.dump` (method) `tools/minios_hyper.py:308` `def dump(self, name)`
- `Guest.stop` (method) `tools/minios_hyper.py:314` `def stop(self)`
- `FrameDiff.mean_diff` (method) `tools/minios_hyper.py:343` `def mean_diff(a_path, b_path)` -- Mean absolute grey difference above the taskbar strip.
- `FrameDiff.cursor_positions` (method) `tools/minios_hyper.py:356` `def cursor_positions(shot_path)` -- Clustered arrow-template hit positions, static-safe.
- `FrameDiff.count_cursors` (method) `tools/minios_hyper.py:394` `def count_cursors(shot_path)` -- Clustered arrow-sprite count for one frame.
- `FrameDiff.moved_cursors` (method) `tools/minios_hyper.py:399` `def moved_cursors(before_path, after_path)` -- Hits in after with no neighbour in before, the live pointer.
- `HyperChecks.__init__` (method) `tools/minios_hyper.py:412` `def __init__(self, guest)`
- `HyperChecks.vga_idle` (method) `tools/minios_hyper.py:415` `def vga_idle(self)` -- Two idle frames must match, no unsolicited redraw or flicker.
- `HyperChecks.vga_cursor` (method) `tools/minios_hyper.py:427` `def vga_cursor(self)` -- One live pointer must move, static template hits are ignored.
- `HyperChecks.gfx_frames` (method) `tools/minios_hyper.py:439` `def gfx_frames(self)` -- The composited-frame counter must climb across a real present.
- `HyperChecks.pixel_oob` (method) `tools/minios_hyper.py:452` `def pixel_oob(self)` -- Out-of-range pixel probes must diagnose, never wrap or crash.
- `HyperChecks.sys_trace` (method) `tools/minios_hyper.py:465` `def sys_trace(self)` -- Verbose trace must show a named syscall for a real program.
- `HyperChecks.run_selftest` (method) `tools/minios_hyper.py:491` `def run_selftest()` -- Host-only vectors for the packet codec and pixel math, no QEMU.
- `HyperChecks.check` (method) `tools/minios_hyper.py:495` `def check(ok, msg)`
- `HyperChecks.run_boot` (method) `tools/minios_hyper.py:523` `def run_boot(checks, extra_shell, interactive)` -- Boot the guest and run the requested scripted checks.
- `HyperChecks.repl` (method) `tools/minios_hyper.py:561` `def repl(guest)` -- Tiny interactive loop joining shell, QMP and gdb reads.
- `HyperChecks.main` (method) `tools/minios_hyper.py:591` `def main(argv)` -- Parse argv and dispatch to selftest, boot checks or repl.

## tools/mkfs.minifs.py
- `roundup4` (function) `tools/mkfs.minifs.py:22` `def roundup4(v)`
- `div_round_up` (function) `tools/mkfs.minifs.py:25` `def div_round_up(n, d)`
- `crc16` (function) `tools/mkfs.minifs.py:28` `def crc16(data)`
- `crc32` (function) `tools/mkfs.minifs.py:36` `def crc32(data)`
- `count_free` (function) `tools/mkfs.minifs.py:44` `def count_free(bitmap, count)` -- Clear bits among the first count bits of bitmap: the superblock free counters must equal what the kernel allocator...
- `MiniFS.__init__` (method) `tools/mkfs.minifs.py:51` `def __init__(self, total_blocks)`
- `MiniFS.mark_inodes_used` (method) `tools/mkfs.minifs.py:74` `def mark_inodes_used(self, start, count)`
- `MiniFS.mark_blocks_used` (method) `tools/mkfs.minifs.py:78` `def mark_blocks_used(self, start, count)`
- `MiniFS.alloc_inode` (method) `tools/mkfs.minifs.py:82` `def alloc_inode(self)`
- `MiniFS.alloc_block` (method) `tools/mkfs.minifs.py:88` `def alloc_block(self)`
- `MiniFS.create_root` (method) `tools/mkfs.minifs.py:94` `def create_root(self)`
- `MiniFS.seal_inode` (method) `tools/mkfs.minifs.py:102` `def seal_inode(self, ino)` -- Store the inode checksum over its first 124 bytes; every mutation reseals, or the kernel rejects the inode on read.
- `MiniFS.create_inode` (method) `tools/mkfs.minifs.py:107` `def create_inode(self, mode, links)`
- `MiniFS.inode_set_size` (method) `tools/mkfs.minifs.py:114` `def inode_set_size(self, ino, size)`
- `MiniFS.inode_set_block` (method) `tools/mkfs.minifs.py:118` `def inode_set_block(self, ino, logblk, phys)`
- `MiniFS.add_dir_entry` (method) `tools/mkfs.minifs.py:148` `def add_dir_entry(self, dir_ino, name, child_ino, ftype)`
- `MiniFS.claim_name` (method) `tools/mkfs.minifs.py:186` `def claim_name(self, parent_ino, name, is_dir)` -- Record name in parent_ino.
- `MiniFS.write_file` (method) `tools/mkfs.minifs.py:199` `def write_file(self, parent_ino, name, data)`
- `MiniFS.write_dir` (method) `tools/mkfs.minifs.py:218` `def write_dir(self, parent_ino, name)`
- `MiniFS.serialize` (method) `tools/mkfs.minifs.py:230` `def serialize(self)`
- `MiniFS.main` (method) `tools/mkfs.minifs.py:274` `def main()`
- `MiniFS.pack_tree` (method) `tools/mkfs.minifs.py:304` `def pack_tree(parent_ino, path, rel)`

## tools/mkpak1.py
- `main` (function) `tools/mkpak1.py:29` `def main()`

## tools/mkramdisk.py
- `pack_name` (function) `tools/mkramdisk.py:38` `def pack_name(path, common)`
- `main` (function) `tools/mkramdisk.py:48` `def main()`

## tools/mkvocab.py
- `bytes_to_unicode` (function) `tools/mkvocab.py:18` `def bytes_to_unicode()` -- Reversible byte to unicode map used by the GPT-2 encoder.
- `main` (function) `tools/mkvocab.py:35` `def main(encoder_path, vocab_path)` -- Convert encoder.json to the VOCB binary vocabulary.

## tools/mutate.sh
- `usage` (function) `tools/mutate.sh:51`
- `restore_sources` (function) `tools/mutate.sh:129`
- `cleanup` (function) `tools/mutate.sh:136`
- `record` (function) `tools/mutate.sh:465`
- `find_index` (function) `tools/mutate.sh:471` -- Locate a mutant by name.

## tools/probe_compute_vga.py
Depends on: `kernel/time.c`
- `main` (function) `tools/probe_compute_vga.py:22` `def main()`
- `send` (function) `tools/probe_compute_vga.py:55` `def send(line)`
- `poll` (function) `tools/probe_compute_vga.py:61` `def poll(timeout)`
- `qmp` (function) `tools/probe_compute_vga.py:88` `def qmp(obj)`
- `rel` (function) `tools/probe_compute_vga.py:97` `def rel(dx, dy)`
- `dump` (function) `tools/probe_compute_vga.py:104` `def dump(name)`

## tools/probe_minicraft.py
Depends on: `kernel/time.c`
- `main` (function) `tools/probe_minicraft.py:34` `def main()`
- `send` (function) `tools/probe_minicraft.py:68` `def send(line)`
- `poll` (function) `tools/probe_minicraft.py:74` `def poll(timeout)`
- `grab` (function) `tools/probe_minicraft.py:85` `def grab(pat, timeout)`
- `qkey` (function) `tools/probe_minicraft.py:143` `def qkey(qcode, down)`
- `pos` (function) `tools/probe_minicraft.py:154` `def pos(tag)`

## tools/qga_client.py
Depends on: `kernel/time.c`
- `send_command` (function) `tools/qga_client.py:33` `def send_command(sock, cmd, args)`
- `read_reply` (function) `tools/qga_client.py:41` `def read_reply(sock, timeout)` -- Read one newline-terminated JSON object from the agent.
- `connect` (function) `tools/qga_client.py:57` `def connect(path)`
- `main` (function) `tools/qga_client.py:74` `def main(argv)`

## tools/repro_gui.py
Depends on: `kernel/time.c`
- `read_serial` (function) `tools/repro_gui.py:30` `def read_serial(master, timeout)`
- `QMP.__init__` (method) `tools/repro_gui.py:47` `def __init__(self, path)`
- `QMP.cmd` (method) `tools/repro_gui.py:59` `def cmd(self, obj)`
- `QMP.mouse` (method) `tools/repro_gui.py:78` `def mouse(self, dx, dy, left)`
- `QMP.key` (method) `tools/repro_gui.py:87` `def key(self, qcode, down)`
- `QMP.main` (method) `tools/repro_gui.py:92` `def main()`
- `QMP.send` (method) `tools/repro_gui.py:113` `def send(line)`
- `QMP.mouse_state` (method) `tools/repro_gui.py:118` `def mouse_state()`

## tools/wl_scoped.sh
- `say` (function) `tools/wl_scoped.sh:8`
- `die` (function) `tools/wl_scoped.sh:9`
- `mut` (function) `tools/wl_scoped.sh:77`
- `mutm` (function) `tools/wl_scoped.sh:84`

## tools/wm_layout_sync.py
- `WmLayoutSyncConfig.__init__` (method) `tools/wm_layout_sync.py:20` `def __init__(self, root)` -- Docstring: Bind all paths to one repository root.
- `WmLayoutSyncResult.__init__` (method) `tools/wm_layout_sync.py:39` `def __init__(self, modes, symbols, checks)` -- Docstring: Store discovered modes, symbols and check count.
- `WmLayoutSync.__init__` (method) `tools/wm_layout_sync.py:49` `def __init__(self, config)` -- Docstring: Hold config as the sole tunable source.
- `WmLayoutSync.discover` (method) `tools/wm_layout_sync.py:53` `def discover(self)` -- Docstring: Extract modes, symbols and test checks from sources.
- `WmLayoutSync.render` (method) `tools/wm_layout_sync.py:66` `def render(self, result)` -- Docstring: Build manifest markdown from discovery result.
- `WmLayoutSync.synchronize` (method) `tools/wm_layout_sync.py:101` `def synchronize(self, write)` -- Docstring: Discover, render and optionally write the manifest.
- `WmLayoutSync.parse_args` (method) `tools/wm_layout_sync.py:151` `def parse_args(argv)` -- Docstring: Parse CLI flags for check or write modes.
- `WmLayoutSync.main` (method) `tools/wm_layout_sync.py:159` `def main(argv)` -- Docstring: Run discovery and write or verify the manifest.

## tools/wm_scoped.sh
- `say` (function) `tools/wm_scoped.sh:8`
- `die` (function) `tools/wm_scoped.sh:9`

## vma.c
Depends on: `headers/vma.h`
- `vma_ctx_init` (function) `vma.c:32` `void vma_ctx_init(vma_ctx_t *c, vma_node_t *pool)`
- `vma_ctx_bind` (function) `vma.c:46` `void vma_ctx_bind(vma_ctx_t *c)`
- `vma_ctx_save` (function) `vma.c:57` `void vma_ctx_save(vma_ctx_t *c)`
- `vma_view_save` (function) `vma.c:66` `void vma_view_save(vma_view_t *v)`
- `vma_view_load` (function) `vma.c:77` `void vma_view_load(const vma_view_t *v)`
- `vma_tree_init` (function) `vma.c:88` `void vma_tree_init(void)`
- `vma_alloc_node` (function) `vma.c:102` `static vma_node_t *vma_alloc_node(void)`
- `vma_rotate_left` (function) `vma.c:108` `static void vma_rotate_left(vma_node_t **root, vma_node_t *x)`
- `vma_rotate_right` (function) `vma.c:120` `static void vma_rotate_right(vma_node_t **root, vma_node_t *x)`
- `vma_insert_fixup` (function) `vma.c:132` `static void vma_insert_fixup(vma_node_t **root, vma_node_t *z)`
- `vma_tree_insert` (function) `vma.c:171` `vma_node_t *vma_tree_insert(vma_node_t **root, unsigned long base, unsigned long len)`
- `vma_tree_find` (function) `vma.c:197` `vma_node_t *vma_tree_find(vma_node_t *root, unsigned long base)`
- `vma_tree_find_containing` (function) `vma.c:213` `vma_node_t *vma_tree_find_containing(vma_node_t *root, unsigned long va)` -- Docstring: Find the live node containing va (base <= va < base+len), or VMA_NIL.
- `vma_transplant` (function) `vma.c:227` `static void vma_transplant(vma_node_t **root, vma_node_t *u, vma_node_t *v)`
- `vma_tree_minimum` (function) `vma.c:234` `static vma_node_t *vma_tree_minimum(vma_node_t *x)`
- `vma_delete_fixup` (function) `vma.c:239` `static void vma_delete_fixup(vma_node_t **root, vma_node_t *x)`
- `vma_tree_delete` (function) `vma.c:294` `int vma_tree_delete(vma_node_t **root, unsigned long base)`

