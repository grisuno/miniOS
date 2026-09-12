# Subsystem: tools

## tools/boot_run.sh
- Layer: utility
- Doc: boot_run.sh -- boot the MiniOS image in QEMU and drive the shell over the serial console with a list of commands, captur
- Language: sh

## tools/check_abi_numbers.py
- Layer: utility
- Language: py
- Symbols:
  - `normalize` (function, line 127) `def normalize(minios_name)`
  - `parse_abi` (function, line 131) `def parse_abi(path)`
  - `parse_dispatch` (function, line 142) `def parse_dispatch(path)`
  - `main` (function, line 155) `def main()`

## tools/check_cohesion.py
- Layer: utility
- Language: py
- Symbols:
  - `load_cpg` (function, line 23) `def load_cpg(path)`
  - `compute_cohesion` (function, line 31) `def compute_cohesion(community_nodes, community_edges)`
  - `extract_communities` (function, line 42) `def extract_communities(cpg)`
  - `main` (function, line 58) `def main()`

## tools/check_complexity.py
- Layer: utility
- Language: py
- Symbols:
  - `count_symbols` (function, line 24) `def count_symbols(filepath)`
  - `load_approval` (function, line 46) `def load_approval(policy_path)`
  - `main` (function, line 61) `def main()`

## tools/check_kb_sync.py
- Layer: utility
- Language: py
- Symbols:
  - `regenerate_kb` (function, line 24) `def regenerate_kb()`
  - `main` (function, line 43) `def main()`

## tools/check_surprising.py
- Layer: utility
- Language: py
- Symbols:
  - `load_cpg` (function, line 25) `def load_cpg(path)`
  - `build_graph` (function, line 33) `def build_graph(cpg)`
  - `bfs_min_hops` (function, line 56) `def bfs_min_hops(nodes, edges, source, target_community, max_hops)`
  - `find_surprising_connections` (function, line 87) `def find_surprising_connections(nodes, edges, min_hops)`
  - `main` (function, line 118) `def main()`

## tools/extract_shell.py
- Layer: utility
- Language: py

## tools/gdb_repro.py
- Layer: utility
- Language: py
- Symbols:
  - `rs` (function, line 23) `def rs(m, t)`
  - `main` (function, line 27) `def main()`
  - `send` (function, line 65) `def send(line)`
  - `quit_doom` (function, line 70) `def quit_doom()`
- Depends on: `kernel/time.c`

## tools/gen_desktop_pngs.py
- Layer: utility
- Language: py
- Symbols:
  - `write_atomic` (function, line 56) `def write_atomic(img, path)`
  - `main` (function, line 62) `def main()`

## tools/gen_icons.py
- Layer: utility
- Language: py
- Symbols:
  - `make_png` (function, line 179) `def make_png(pixels, palette, width, height)`
  - `make_chunk` (function, line 209) `def make_chunk(chunk_type, data)`
  - `main` (function, line 214) `def main()`

## tools/gen_zip_fixtures.py
- Layer: data_access
- Language: py
- Symbols:
  - `write_zip` (function, line 28) `def write_zip(path, entries)`
  - `main` (function, line 42) `def main()`

## tools/minifs_saves.py
- Layer: utility
- Language: py
- Symbols:
  - `u16` (function, line 40) `def u16(d, o)`
  - `u32` (function, line 44) `def u32(d, o)`
  - `Image` (class, line 48) `class Image`
  - `FS` (class, line 72) `class FS`
  - `valid_name` (method, line 199) `def valid_name(nm)`
  - `find_partition_base` (method, line 207) `def find_partition_base(fn)`
  - `cmd_backup` (method, line 245) `def cmd_backup(img_path, stage)`
  - `main` (method, line 304) `def main(argv)`
  - `__init__` (method, line 51) `def __init__(self, fn, base)`
  - `close` (method, line 59) `def close(self)`
  - `blk` (method, line 62) `def blk(self, n)`
  - `__init__` (method, line 73) `def __init__(self, img)`
  - `inode` (method, line 82) `def inode(self, i)`
  - `is_dir` (method, line 97) `def is_dir(self, st)`
  - `read_file` (method, line 100) `def read_file(self, ino)`
  - `listdir` (method, line 133) `def listdir(self, ino)`
  - `read_file_dir` (method, line 148) `def read_file_dir(self, ino)`
  - `read_file_raw` (method, line 156) `def read_file_raw(self, st)`
  - `resolve` (method, line 180) `def resolve(self, path)`
  - `walk` (method, line 267) `def walk(dir_ino, rel)`

## tools/minios_cli.py
- Layer: utility
- Language: py
- Symbols:
  - `Client` (class, line 37) `class Client`
  - `main` (method, line 99) `def main()`
  - `__init__` (method, line 38) `def __init__(self)`
  - `request` (method, line 55) `def request(self, method, params)`
  - `tool` (method, line 76) `def tool(self, name, params)`
  - `close` (method, line 86) `def close(self)`
- Depends on: `kernel/time.c`

## tools/minios_gui.py
- Layer: presentation
- Language: py
- Symbols:
  - `read_serial` (function, line 42) `def read_serial(master, timeout)`
  - `QMP` (class, line 58) `class QMP`
  - `main` (method, line 110) `def main()`
  - `__init__` (method, line 59) `def __init__(self, path)`
  - `cmd` (method, line 71) `def cmd(self, obj)`
  - `_recv` (method, line 75) `def _recv(self)`
  - `mouse` (method, line 90) `def mouse(self, dx, dy, click)`
  - `key` (method, line 100) `def key(self, qcode, up)`
  - `screendump` (method, line 106) `def screendump(self, path)`
- Depends on: `kernel/time.c`

## tools/mkpak1.py
- Layer: utility
- Language: py
- Symbols:
  - `main` (function, line 29) `def main()`

## tools/qga_client.py
- Layer: infrastructure
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
- Language: py
- Symbols:
  - `read_serial` (function, line 28) `def read_serial(master, timeout)`
  - `QMP` (class, line 44) `class QMP`
  - `main` (method, line 90) `def main()`
  - `__init__` (method, line 45) `def __init__(self, path)`
  - `cmd` (method, line 57) `def cmd(self, obj)`
  - `_recv` (method, line 61) `def _recv(self)`
  - `mouse` (method, line 76) `def mouse(self, dx, dy, left)`
  - `key` (method, line 85) `def key(self, qcode, down)`
  - `send` (method, line 111) `def send(line)`
  - `mouse_state` (method, line 116) `def mouse_state()`
- Depends on: `kernel/time.c`

## tools/test_codecs.sh
- Layer: testing
- Doc: test_codecs.sh -- exercise the lzss/lz4/aes command-pair tools inside the OS.  The interpreter in-OS suites (test.lua / 
- Language: sh

## tools/test_gui_wm.py
- Layer: testing
- Language: py
- Symbols:
  - `note` (function, line 36) `def note(ok, msg)`
  - `Guest` (class, line 42) `class Guest`
  - `meandiff` (method, line 198) `def meandiff(a_path, b_path)`
  - `main` (method, line 208) `def main()`
  - `__init__` (method, line 43) `def __init__(self)`
  - `_ser` (method, line 69) `def _ser(self)`
  - `_reader` (method, line 81) `def _reader(self)`
  - `snapshot` (method, line 97) `def snapshot(self)`
  - `wait_prompt` (method, line 101) `def wait_prompt(self, timeout)`
  - `send` (method, line 109) `def send(self, line, settle)`
  - `qmp_cmd` (method, line 124) `def qmp_cmd(self, obj)`
  - `_qmp` (method, line 137) `def _qmp(self, obj)`
  - `key` (method, line 145) `def key(self, qcode, down, up)`
  - `rel` (method, line 157) `def rel(self, dx, dy)`
  - `btn` (method, line 164) `def btn(self, down)`
  - `dump` (method, line 170) `def dump(self, name)`
  - `stop` (method, line 177) `def stop(self)`
- Depends on: `kernel/time.c`

## tools/test_sb16.sh
- Layer: testing
- Doc: test_sb16.sh — targeted BDD harness for the SB16 audio path.  Boots the disk image once with the SB16 device attached (h
- Language: sh
- Symbols:
  - `fail_msg` (function, line 45)

## tools/wm_scoped.sh
- Layer: utility
- Doc: Docstring: Scoped WM validation for Alt-Tab and tile across all windows. Runs host WM unit tests, rebuilds touched kerne
- Language: sh
- Symbols:
  - `say` (function, line 8)
  - `die` (function, line 9)
