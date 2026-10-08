# API (page 19 of 19)
Previous: [API_p18.md](API_p18.md)

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
- `FSCK.run` (method) `tools/minifs_fsck.py:137` `def run(self)`
- `FSCK.main` (method) `tools/minifs_fsck.py:152` `def main()`

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
- `read_serial` (function) `tools/minios_gui.py:44` `def read_serial(master, timeout)`
- `QMP.__init__` (method) `tools/minios_gui.py:61` `def __init__(self, path)`
- `QMP.cmd` (method) `tools/minios_gui.py:73` `def cmd(self, obj)`
- `QMP.mouse` (method) `tools/minios_gui.py:92` `def mouse(self, dx, dy, click)`
- `QMP.key` (method) `tools/minios_gui.py:102` `def key(self, qcode, up)`
- `QMP.screendump` (method) `tools/minios_gui.py:108` `def screendump(self, path)`
- `QMP.main` (method) `tools/minios_gui.py:112` `def main()`

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
- `MiniFS.__init__` (method) `tools/mkfs.minifs.py:45` `def __init__(self, total_blocks)`
- `MiniFS.mark_inodes_used` (method) `tools/mkfs.minifs.py:67` `def mark_inodes_used(self, start, count)`
- `MiniFS.mark_blocks_used` (method) `tools/mkfs.minifs.py:71` `def mark_blocks_used(self, start, count)`
- `MiniFS.alloc_inode` (method) `tools/mkfs.minifs.py:75` `def alloc_inode(self)`
- `MiniFS.alloc_block` (method) `tools/mkfs.minifs.py:81` `def alloc_block(self)`
- `MiniFS.create_root` (method) `tools/mkfs.minifs.py:87` `def create_root(self)`
- `MiniFS.create_inode` (method) `tools/mkfs.minifs.py:95` `def create_inode(self, mode)`
- `MiniFS.inode_set_size` (method) `tools/mkfs.minifs.py:102` `def inode_set_size(self, ino, size)`
- `MiniFS.inode_set_block` (method) `tools/mkfs.minifs.py:106` `def inode_set_block(self, ino, logblk, phys)`
- `MiniFS.add_dir_entry` (method) `tools/mkfs.minifs.py:136` `def add_dir_entry(self, dir_ino, name, child_ino, ftype)`
- `MiniFS.write_file` (method) `tools/mkfs.minifs.py:174` `def write_file(self, parent_ino, name, data)`
- `MiniFS.write_dir` (method) `tools/mkfs.minifs.py:191` `def write_dir(self, parent_ino, name)`
- `MiniFS.serialize` (method) `tools/mkfs.minifs.py:197` `def serialize(self)`
- `MiniFS.main` (method) `tools/mkfs.minifs.py:241` `def main()`
- `MiniFS.pack_tree` (method) `tools/mkfs.minifs.py:271` `def pack_tree(parent_ino, path, rel)`

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
- `restore_sources` (function) `tools/mutate.sh:126`
- `cleanup` (function) `tools/mutate.sh:133`
- `record` (function) `tools/mutate.sh:410`
- `find_index` (function) `tools/mutate.sh:416` -- Locate a mutant by name.

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

