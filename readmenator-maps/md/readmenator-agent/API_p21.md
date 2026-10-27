# API (page 21 of 21)
Previous: [API_p20.md](API_p20.md)

## tools/gen_desktop_pngs.py
- `scaled` (function) `tools/gen_desktop_pngs.py:75` `def scaled(im, scale)` -- Resize an image by a factor with Lanczos, never below one pixel.
- `fit_wallpaper` (function) `tools/gen_desktop_pngs.py:81` `def fit_wallpaper(im)` -- Whole source, centred, over a blurred and dimmed cover-scaled copy.
- `write_atomic` (function) `tools/gen_desktop_pngs.py:93` `def write_atomic(img, path)`
- `main` (function) `tools/gen_desktop_pngs.py:99` `def main()`

## tools/gen_icons.py
- `make_png` (function) `tools/gen_icons.py:179` `def make_png(pixels, palette, width, height)` -- Create a minimal indexed-colour PNG from pixel indices and a palette.
- `make_chunk` (function) `tools/gen_icons.py:209` `def make_chunk(chunk_type, data)`
- `main` (function) `tools/gen_icons.py:214` `def main()`

## tools/gen_zip_fixtures.py
- `write_zip` (function) `tools/gen_zip_fixtures.py:28` `def write_zip(path, entries)` -- entries: list of (name, data_or_None).  data None marks a directory.
- `main` (function) `tools/gen_zip_fixtures.py:42` `def main()`

## tools/kernel_feature_survey.py
- `iter_sources` (function) `tools/kernel_feature_survey.py:34` `def iter_sources(root)` -- Yield C source paths under root, skipping vendored and cache dirs.
- `find_fnptr_hits` (function) `tools/kernel_feature_survey.py:43` `def find_fnptr_hits(path, text)` -- Return line numbers declaring function pointers.
- `find_asm_constraints` (function) `tools/kernel_feature_survey.py:49` `def find_asm_constraints(path, text)` -- Return sorted constraint letters used in extended asm.
- `count_params` (function) `tools/kernel_feature_survey.py:59` `def count_params(params)` -- Count parameters, treating void and empty as zero.
- `survey` (function) `tools/kernel_feature_survey.py:67` `def survey(root)` -- Collect findings per category across all sources.
- `render_text` (function) `tools/kernel_feature_survey.py:103` `def render_text(findings)` -- Render findings as plain text.
- `main` (function) `tools/kernel_feature_survey.py:122` `def main(argv)` -- Entry point for the survey tool.

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
- `main` (function) `tools/minifs_dump.py:105` `def main()`

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
- `main` (function) `tools/minifs_fsck.py:173` `def main()`

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
- `valid_name` (function) `tools/minifs_saves.py:216` `def valid_name(nm)`
- `strict_name` (function) `tools/minifs_saves.py:224` `def strict_name(nm)`
- `find_partition_base` (function) `tools/minifs_saves.py:233` `def find_partition_base(fn)` -- Locate the MiniFS partition inside a host image file.
- `cmd_backup` (function) `tools/minifs_saves.py:271` `def cmd_backup(img_path, stage)`
- `walk` (function) `tools/minifs_saves.py:293` `def walk(dir_ino, rel)`
- `main` (function) `tools/minifs_saves.py:343` `def main(argv)`

## tools/minios_cli.py
Depends on: `kernel/time.c`
- `Client.__init__` (method) `tools/minios_cli.py:39` `def __init__(self)`
- `Client.request` (method) `tools/minios_cli.py:56` `def request(self, method, params)`
- `Client.tool` (method) `tools/minios_cli.py:77` `def tool(self, name, params)`
- `Client.close` (method) `tools/minios_cli.py:87` `def close(self)`
- `main` (function) `tools/minios_cli.py:100` `def main()`

## tools/minios_gui.py
Depends on: `kernel/time.c`
- `read_serial` (function) `tools/minios_gui.py:50` `def read_serial(master, timeout)`
- `QMP.__init__` (method) `tools/minios_gui.py:67` `def __init__(self, path)`
- `QMP.cmd` (method) `tools/minios_gui.py:79` `def cmd(self, obj)`
- `QMP.mouse` (method) `tools/minios_gui.py:98` `def mouse(self, dx, dy, click)`
- `QMP.key` (method) `tools/minios_gui.py:108` `def key(self, qcode, up)`
- `QMP.screendump` (method) `tools/minios_gui.py:114` `def screendump(self, path)`
- `main` (function) `tools/minios_gui.py:118` `def main()`

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
- `run_selftest` (function) `tools/minios_hyper.py:491` `def run_selftest()` -- Host-only vectors for the packet codec and pixel math, no QEMU.
- `check` (function) `tools/minios_hyper.py:495` `def check(ok, msg)`
- `run_boot` (function) `tools/minios_hyper.py:523` `def run_boot(checks, extra_shell, interactive)` -- Boot the guest and run the requested scripted checks.
- `repl` (function) `tools/minios_hyper.py:561` `def repl(guest)` -- Tiny interactive loop joining shell, QMP and gdb reads.
- `main` (function) `tools/minios_hyper.py:591` `def main(argv)` -- Parse argv and dispatch to selftest, boot checks or repl.

## tools/mkcpyzip.py
- `build_zip` (function) `tools/mkcpyzip.py:22` `def build_zip(lib_dir, out_zip, skip)` -- Write out_zip with the Lib tree minus skip dirs; return file count.
- `main` (function) `tools/mkcpyzip.py:41` `def main()`

## tools/mkfs.minifs.py
- `roundup4` (function) `tools/mkfs.minifs.py:28` `def roundup4(v)`
- `div_round_up` (function) `tools/mkfs.minifs.py:31` `def div_round_up(n, d)`
- `crc16` (function) `tools/mkfs.minifs.py:34` `def crc16(data)`
- `crc32` (function) `tools/mkfs.minifs.py:42` `def crc32(data)`
- `count_free` (function) `tools/mkfs.minifs.py:50` `def count_free(bitmap, count)` -- Clear bits among the first count bits of bitmap: the superblock free counters must equal what the kernel allocator...
- `MiniFS.__init__` (method) `tools/mkfs.minifs.py:57` `def __init__(self, total_blocks)`
- `MiniFS.mark_inodes_used` (method) `tools/mkfs.minifs.py:80` `def mark_inodes_used(self, start, count)`
- `MiniFS.mark_blocks_used` (method) `tools/mkfs.minifs.py:84` `def mark_blocks_used(self, start, count)`
- `MiniFS.alloc_inode` (method) `tools/mkfs.minifs.py:88` `def alloc_inode(self)`
- `MiniFS.alloc_block` (method) `tools/mkfs.minifs.py:94` `def alloc_block(self)`
- `MiniFS.create_root` (method) `tools/mkfs.minifs.py:100` `def create_root(self)`
- `MiniFS.seal_inode` (method) `tools/mkfs.minifs.py:108` `def seal_inode(self, ino)` -- Store the inode checksum over its first 124 bytes; every mutation reseals, or the kernel rejects the inode on read.
- `MiniFS.create_inode` (method) `tools/mkfs.minifs.py:113` `def create_inode(self, mode, links)`
- `MiniFS.inode_set_size` (method) `tools/mkfs.minifs.py:120` `def inode_set_size(self, ino, size)`
- `MiniFS.inode_set_block` (method) `tools/mkfs.minifs.py:124` `def inode_set_block(self, ino, logblk, phys)`
- `MiniFS.add_dir_entry` (method) `tools/mkfs.minifs.py:154` `def add_dir_entry(self, dir_ino, name, child_ino, ftype)`
- `MiniFS.claim_name` (method) `tools/mkfs.minifs.py:192` `def claim_name(self, parent_ino, name, is_dir)` -- Record name in parent_ino.
- `MiniFS.write_file` (method) `tools/mkfs.minifs.py:205` `def write_file(self, parent_ino, name, data)`
- `MiniFS.write_dir` (method) `tools/mkfs.minifs.py:224` `def write_dir(self, parent_ino, name)`
- `MiniFS.serialize` (method) `tools/mkfs.minifs.py:236` `def serialize(self)`
- `main` (function) `tools/mkfs.minifs.py:280` `def main()`
- `pack_tree` (function) `tools/mkfs.minifs.py:310` `def pack_tree(parent_ino, path, rel)`

## tools/mkpak1.py
- `main` (function) `tools/mkpak1.py:29` `def main()`

## tools/mkramdisk.py
- `read_fname_bytes` (function) `tools/mkramdisk.py:41` `def read_fname_bytes(kernel_h_path)` -- Parse RAMDISK_FNAME_LEN from headers/kernel.h; fail closed.
- `pack_name` (function) `tools/mkramdisk.py:64` `def pack_name(path, common)`
- `main` (function) `tools/mkramdisk.py:74` `def main()`

## tools/mkvocab.py
- `bytes_to_unicode` (function) `tools/mkvocab.py:18` `def bytes_to_unicode()` -- Reversible byte to unicode map used by the GPT-2 encoder.
- `main` (function) `tools/mkvocab.py:35` `def main(encoder_path, vocab_path)` -- Convert encoder.json to the VOCB binary vocabulary.

## tools/mutate.sh
- `usage` (function) `tools/mutate.sh:51`
- `restore_sources` (function) `tools/mutate.sh:138`
- `cleanup` (function) `tools/mutate.sh:145`
- `record` (function) `tools/mutate.sh:547`
- `find_index` (function) `tools/mutate.sh:553` -- Locate a mutant by name.

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
- `main` (function) `tools/repro_gui.py:92` `def main()`
- `send` (function) `tools/repro_gui.py:113` `def send(line)`
- `mouse_state` (function) `tools/repro_gui.py:118` `def mouse_state()`

## tools/sign_elf.py
- `sha512` (function) `tools/sign_elf.py:61` `def sha512(data)` -- One-shot SHA-512.
- `encodepoint_raw` (function) `tools/sign_elf.py:66` `def encodepoint_raw(x, y)` -- Encode affine (x, y) to 32 bytes.
- `edwards_add` (function) `tools/sign_elf.py:71` `def edwards_add(p, q)` -- Add two extended points, all math mod field_p.
- `scalarmult` (function) `tools/sign_elf.py:88` `def scalarmult(p, e)` -- Multiply extended point p by scalar e.
- `base_point` (function) `tools/sign_elf.py:99` `def base_point()` -- Recompute the base point from y = 4/5.
- `publickey` (function) `tools/sign_elf.py:112` `def publickey(seed)` -- Derive the 32-byte public key from a 32-byte seed.
- `sign_digest` (function) `tools/sign_elf.py:121` `def sign_digest(digest, seed)` -- Sign a 64-byte canonical digest, returning 64 signature bytes.
- `pad_to` (function) `tools/sign_elf.py:135` `def pad_to(blob, alignment)` -- Pad blob with zero bytes up to alignment.
- `parse_ehdr` (function) `tools/sign_elf.py:143` `def parse_ehdr(data)` -- Unpack the ELF header, raising ValueError when truncated.
- `parse_phdrs` (function) `tools/sign_elf.py:158` `def parse_phdrs(data, ehdr)` -- Unpack the program headers, raising ValueError when out of range.
- `canonical_digest` (function) `tools/sign_elf.py:172` `def canonical_digest(data, ehdr, phdrs)` -- Build the kernel-agreed digest: entry plus PT_LOAD segments.
- `find_note_slots` (function) `tools/sign_elf.py:199` `def find_note_slots(data, ehdr, phdrs)` -- Locate patchable signature slots, returning file offsets of descs.
- `find_section_slot` (function) `tools/sign_elf.py:222` `def find_section_slot(data, ehdr)` -- Locate the .note.minios.sign section descriptor, else -1.
- `append_section` (function) `tools/sign_elf.py:257` `def append_section(data, ehdr, desc)` -- Append a .note.minios.sign section, returning the new image.
- `pub_for_key` (function) `tools/sign_elf.py:305` `def pub_for_key(key_id)` -- Resolve the trusted public key for checking without secrets.
- `key_material` (function) `tools/sign_elf.py:321` `def key_material(key_id)` -- Resolve the signing seed and public key for a key id.
- `process` (function) `tools/sign_elf.py:341` `def process(path, key_id, check_only)` -- Sign or verify one file, returning (action, detail).
- `verify_external` (function) `tools/sign_elf.py:395` `def verify_external(sig, digest, pub)` -- Verify with PyNaCl when present, else the local fallback.
- `fallback_verify` (function) `tools/sign_elf.py:408` `def fallback_verify(sig, digest, pub)` -- Pure-python Ed25519 verify for hosts without PyNaCl.
- `decode_point` (function) `tools/sign_elf.py:429` `def decode_point(raw)` -- Decode a point encoding to extended coordinates.
- `points_equal` (function) `tools/sign_elf.py:447` `def points_equal(p, q)` -- Compare extended points by cross-multiplied coordinates.
- `main` (function) `tools/sign_elf.py:454` `def main(argv)` -- Drive signing or checking over files and directory walks.

## tools/update_sources.py
- `GitResult.ok` (method) `tools/update_sources.py:211` `def ok(self)`
- `Outcome.changed` (method) `tools/update_sources.py:228` `def changed(self)`
- `run_git` (function) `tools/update_sources.py:236` `def run_git(git, cwd)` -- Run git in a directory and capture its output.
- `git_out` (function) `tools/update_sources.py:253` `def git_out(git, cwd)` -- Run git and return stdout, or the empty string on failure.
- `head_sha` (function) `tools/update_sources.py:261` `def head_sha(git, path)` -- Return the checked-out revision, or the empty string.
- `short_sha` (function) `tools/update_sources.py:266` `def short_sha(sha)` -- Shorten a revision for display.
- `current_branch` (function) `tools/update_sources.py:271` `def current_branch(git, path)` -- Return the checked-out branch name, empty when detached.
- `is_dirty` (function) `tools/update_sources.py:276` `def is_dirty(git, path)` -- Report whether the worktree carries uncommitted changes.
- `is_shallow` (function) `tools/update_sources.py:281` `def is_shallow(git, path)` -- Report whether the checkout is a shallow clone.
- `resolve_path` (function) `tools/update_sources.py:286` `def resolve_path(directory)` -- Resolve a checkout directory against the repository root.
- `fetch_upstream` (function) `tools/update_sources.py:294` `def fetch_upstream(git, path, branch, shallow_depth)` -- Fetch the upstream branch, optionally with a bounded depth.
- `deepen_upstream` (function) `tools/update_sources.py:306` `def deepen_upstream(git, path, branch, commits)` -- Deepen a shallow checkout so a fast-forward becomes provable.
- `upstream_target` (function) `tools/update_sources.py:316` `def upstream_target(git, path, branch)` -- Return the revision the upstream branch points at.
- `ahead_behind` (function) `tools/update_sources.py:325` `def ahead_behind(git, path, branch)` -- Return the (ahead, behind) commit counts against the upstream branch.
- `fast_forward` (function) `tools/update_sources.py:339` `def fast_forward(git, path, target)` -- Merge an upstream revision, refusing anything but a fast-forward.
- `reconcile` (function) `tools/update_sources.py:344` `def reconcile(git, path, target, strategy)` -- Integrate an upstream revision into a branch that carries local commits.
- `abort_reconcile` (function) `tools/update_sources.py:351` `def abort_reconcile(git, path, strategy)` -- Undo a failed reconciliation so the checkout stays clean.
- `conflicted_files` (function) `tools/update_sources.py:359` `def conflicted_files(git, path)` -- List the files a failed reconciliation left unmerged.
- `update_submodules` (function) `tools/update_sources.py:365` `def update_submodules(git, path, submodules)` -- Initialize and refresh the submodules of a checkout.
- `handle_tracked` (function) `tools/update_sources.py:375` `def handle_tracked(git, repo, path, dry_run, fetch_enabled, strategy)` -- Bring a tracked checkout to the upstream tip, keeping local commits.
- `handle_pinned` (function) `tools/update_sources.py:446` `def handle_pinned(git, repo, path, dry_run, fetch_enabled)` -- Hold a checkout at the release tag it is pinned to.
- `handle_repo` (function) `tools/update_sources.py:493` `def handle_repo(git, repo, directory, dry_run, fetch_enabled, strategy)` -- Dispatch one checkout to the handler its mode asks for.
- `write_snapshot` (function) `tools/update_sources.py:513` `def write_snapshot(path, outcomes)` -- Record the pre-update revision of every checkout that moved.
- `rollback` (function) `tools/update_sources.py:535` `def rollback(git, snapshot_path, directories)` -- Restore the revisions recorded by the last update.
- `print_status` (function) `tools/update_sources.py:572` `def print_status(git, selected, directories)` -- Print the revision of every managed checkout.
- `print_outcome` (function) `tools/update_sources.py:594` `def print_outcome(outcome)` -- Print one checkout result.
- `select_repos` (function) `tools/update_sources.py:599` `def select_repos(names)` -- Resolve the requested repository names, failing on unknown ones.
- `parse_overrides` (function) `tools/update_sources.py:614` `def parse_overrides(pairs)` -- Split the --repo overrides into directory and URL maps.
- `main` (function) `tools/update_sources.py:634` `def main(argv)` -- Run the updater and report what happened.

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
- `parse_args` (function) `tools/wm_layout_sync.py:151` `def parse_args(argv)` -- Docstring: Parse CLI flags for check or write modes.
- `main` (function) `tools/wm_layout_sync.py:159` `def main(argv)` -- Docstring: Run discovery and write or verify the manifest.

## tools/wm_scoped.sh
- `say` (function) `tools/wm_scoped.sh:8`
- `die` (function) `tools/wm_scoped.sh:9`

## vma.c
Depends on: `headers/vma.h`
- `vma_ctx_init` (function) `vma.c:37` `void vma_ctx_init(vma_ctx_t *c, vma_node_t *pool)`
- `vma_ctx_bind` (function) `vma.c:52` `void vma_ctx_bind(vma_ctx_t *c)`
- `vma_ctx_save` (function) `vma.c:64` `void vma_ctx_save(vma_ctx_t *c)`
- `vma_view_save` (function) `vma.c:74` `void vma_view_save(vma_view_t *v)`
- `vma_view_load` (function) `vma.c:86` `void vma_view_load(const vma_view_t *v)`
- `vma_tree_init` (function) `vma.c:98` `void vma_tree_init(void)`
- `vma_alloc_node` (function) `vma.c:113` `static vma_node_t *vma_alloc_node(void)`
- `vma_rotate_left` (function) `vma.c:124` `static void vma_rotate_left(vma_node_t **root, vma_node_t *x)`
- `vma_rotate_right` (function) `vma.c:136` `static void vma_rotate_right(vma_node_t **root, vma_node_t *x)`
- `vma_insert_fixup` (function) `vma.c:148` `static void vma_insert_fixup(vma_node_t **root, vma_node_t *z)`
- `vma_tree_insert` (function) `vma.c:187` `vma_node_t *vma_tree_insert(vma_node_t **root, unsigned long base, unsigned long len)`
- `vma_node_in_tree` (function) `vma.c:215` `static int vma_node_in_tree(vma_node_t *root, vma_node_t *n)` -- 1 when node n hangs in the tree rooted at root (live and free trees * share one pool and one cache, so a cached node...
- `vma_tree_find` (function) `vma.c:220` `vma_node_t *vma_tree_find(vma_node_t *root, unsigned long base)`
- `vma_tree_find_containing` (function) `vma.c:238` `vma_node_t *vma_tree_find_containing(vma_node_t *root, unsigned long va)` -- Docstring: Find the live node containing va (base <= va < base+len), or VMA_NIL.
- `vma_transplant` (function) `vma.c:252` `static void vma_transplant(vma_node_t **root, vma_node_t *u, vma_node_t *v)`
- `vma_tree_minimum` (function) `vma.c:259` `static vma_node_t *vma_tree_minimum(vma_node_t *x)`
- `vma_delete_fixup` (function) `vma.c:264` `static void vma_delete_fixup(vma_node_t **root, vma_node_t *x)`
- `vma_tree_delete` (function) `vma.c:319` `int vma_tree_delete(vma_node_t **root, unsigned long base)`

