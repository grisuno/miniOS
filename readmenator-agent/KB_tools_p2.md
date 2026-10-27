# Subsystem: tools (page 2 of 2)
Previous: [KB_tools.md](KB_tools.md)

## tools/mkramdisk.py
- Doc: Build a MiniOS ramdisk image from files in a directory tree.
- Layer: utility
- Language: py
- Symbols:
  - `read_fname_bytes` (function, line 41) `def read_fname_bytes(kernel_h_path)`
  - `pack_name` (function, line 64) `def pack_name(path, common)`
  - `main` (function, line 74) `def main()`

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
  - `restore_sources` (function, line 138)
  - `cleanup` (function, line 145)
  - `record` (function, line 547)
  - `find_index` (function, line 553)

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

## tools/probe_minicraft.py
- Doc: numeric minicraft probe without any PNG.
- Layer: utility
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
- Doc: Minimal QEMU guest agent client for MiniOS.
- Layer: infrastructure
- Language: py
- Symbols:
  - `send_command` (function, line 33) `def send_command(sock, cmd, args)`
  - `read_reply` (function, line 41) `def read_reply(sock, timeout)`
  - `connect` (function, line 57) `def connect(path)`
  - `main` (function, line 74) `def main(argv)`
- Depends on: `kernel/time.c`

## tools/qga_test.sh
- Doc: Quick standalone smoke test for the QEMU guest agent: boots os.img once with the agent socket...
- Layer: testing
- Language: sh
- Symbols:
  - `cleanup` (function, line 25)
  - `check` (function, line 31)
  - `expect_in` (function, line 43)

## tools/repro_gui.py
- Doc: — reproduce the VGA/mouse state bug after ring-3 programs.
- Layer: utility
- Language: py
- Symbols:
  - `read_serial` (function, line 30) `def read_serial(master, timeout)`
  - `QMP` (class, line 46) `class QMP`
  - `main` (function, line 92) `def main()`
  - `__init__` (method, line 47) `def __init__(self, path)`
  - `cmd` (method, line 59) `def cmd(self, obj)`
  - `_recv` (method, line 63) `def _recv(self)`
  - `mouse` (method, line 78) `def mouse(self, dx, dy, left)`
  - `key` (method, line 87) `def key(self, qcode, down)`
  - `send` (function, line 113) `def send(line)`
  - `mouse_state` (function, line 118) `def mouse_state()`
- Depends on: `kernel/time.c`

## tools/sign_elf.py
- Doc: Sign MiniOS user binaries with Ed25519 (development key). .
- Layer: utility
- Language: py
- Symbols:
  - `Config` (class, line 31) `class Config`
  - `sha512` (function, line 61) `def sha512(data)`
  - `encodepoint_raw` (function, line 66) `def encodepoint_raw(x, y)`
  - `edwards_add` (function, line 71) `def edwards_add(p, q)`
  - `scalarmult` (function, line 88) `def scalarmult(p, e)`
  - `base_point` (function, line 99) `def base_point()`
  - `publickey` (function, line 112) `def publickey(seed)`
  - `sign_digest` (function, line 121) `def sign_digest(digest, seed)`
  - `pad_to` (function, line 135) `def pad_to(blob, alignment)`
  - `parse_ehdr` (function, line 143) `def parse_ehdr(data)`
  - `parse_phdrs` (function, line 158) `def parse_phdrs(data, ehdr)`
  - `canonical_digest` (function, line 172) `def canonical_digest(data, ehdr, phdrs)`
  - `find_note_slots` (function, line 199) `def find_note_slots(data, ehdr, phdrs)`
  - `find_section_slot` (function, line 222) `def find_section_slot(data, ehdr)`
  - `append_section` (function, line 257) `def append_section(data, ehdr, desc)`
  - `pub_for_key` (function, line 305) `def pub_for_key(key_id)`
  - `key_material` (function, line 321) `def key_material(key_id)`
  - `process` (function, line 341) `def process(path, key_id, check_only)`
  - `verify_external` (function, line 395) `def verify_external(sig, digest, pub)`
  - `fallback_verify` (function, line 408) `def fallback_verify(sig, digest, pub)`
  - `decode_point` (function, line 429) `def decode_point(raw)`
  - `points_equal` (function, line 447) `def points_equal(p, q)`
  - `main` (function, line 454) `def main(argv)`

## tools/test_bdd.sh
- Doc: BDD suite for MiniOS: boots the disk image in QEMU and drives the shell over the serial console...
- Layer: testing
- Language: sh
- Symbols:
  - `should_run` (function, line 35)
  - `cleanup_stale_qemu` (function, line 43)
  - `scenario` (function, line 56)
  - `scenario_smp` (function, line 77)
  - `expect` (function, line 100)
  - `expect_min` (function, line 123)
  - `expect_count` (function, line 148)
  - `refute` (function, line 171)
  - `scenario_uefi` (function, line 196)
  - `usb_stick_ready` (function, line 672)
  - `http_server_start` (function, line 1487)
  - `http_server_stop` (function, line 1494)
  - `http_fixture_start` (function, line 1499)
  - `http_fixture_stop` (function, line 1506)
  - `net_fixture_start` (function, line 1511)
  - `net_fixture_stop` (function, line 1518)

## tools/test_call_align.py
- Doc: verify stack alignment at call sites, both parities.
- Layer: testing
- Language: py
- Symbols:
  - `AlignConfig` (class, line 24) `class AlignConfig`
  - `find_minigcc` (function, line 59) `def find_minigcc(explicit)`
  - `run` (function, line 74) `def run(argv)`
  - `main` (function, line 79) `def main(argv)`

## tools/test_codecs.sh
- Doc: exercise the lzss/lz4/aes command-pair tools inside the OS.
- Layer: testing
- Language: sh

## tools/test_gui_fashion.py
- Doc: GUI proof for the cursor/flicker/quit fixes.
- Layer: testing
- Language: py
- Symbols:
  - `note` (function, line 39) `def note(ok, msg)`
  - `Guest` (class, line 45) `class Guest`
  - `meandiff` (function, line 190) `def meandiff(a_path, b_path)`
  - `count_arrows` (function, line 206) `def count_arrows(shot_path)`
  - `main` (function, line 239) `def main()`
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

## tools/test_gui_freedom.py
- Doc: GUI proof that freedom-gui takes real input.
- Layer: testing
- Language: py
- Symbols:
  - `Config` (class, line 45) `class Config`
  - `note` (function, line 98) `def note(ok, msg)`
  - `Guest` (class, line 105) `class Guest`
  - `region_diff` (function, line 256) `def region_diff(a_path, b_path, box)`
  - `content_origin` (function, line 264) `def content_origin(listing)`
  - `changed_pixels` (function, line 273) `def changed_pixels(a_path, b_path, box)`
  - `around` (function, line 283) `def around(point)`
  - `walk` (function, line 289) `def walk(g, delta)`
  - `foreground_phase` (function, line 300) `def foreground_phase(g)`
  - `screen_box` (function, line 332) `def screen_box(origin, box)`
  - `move_to` (function, line 337) `def move_to(g, frame_size, target)`
  - `fb_move` (function, line 343) `def fb_move(g, pos, target)`
  - `main` (function, line 350) `def main()`
  - `__init__` (method, line 108) `def __init__(self, work)`
  - `_connect` (method, line 132) `def _connect(self, path)`
  - `_serial` (method, line 141) `def _serial(self)`
  - `_reader` (method, line 146) `def _reader(self)`
  - `snapshot` (method, line 157) `def snapshot(self)`
  - `wait_for` (method, line 161) `def wait_for(self, text, timeout, since)`
  - `send` (method, line 170) `def send(self, line, settle)`
  - `qmp_cmd` (method, line 181) `def qmp_cmd(self, obj)`
  - `_qmp` (method, line 188) `def _qmp(self, obj)`
  - `keys` (method, line 196) `def keys(self, events)`
  - `tap` (method, line 204) `def tap(self, qcode)`
  - `chord` (method, line 207) `def chord(self, mod, qcode)`
  - `rel` (method, line 210) `def rel(self, dx, dy)`
  - `button` (method, line 215) `def button(self, down)`
  - `wheel` (method, line 221) `def wheel(self, up)`
  - `dump` (method, line 231) `def dump(self, name)`
  - `stop` (method, line 237) `def stop(self)`
- Depends on: `kernel/time.c`

## tools/test_gui_gfxview.py
- Doc: pixel + serial proof of the graphics view contract.
- Layer: testing
- Language: py
- Symbols:
  - `Config` (class, line 39) `class Config`
  - `note` (function, line 56) `def note(ok, msg)`
  - `last_line` (function, line 63) `def last_line(g, prefix)`
  - `gfx_row` (function, line 73) `def gfx_row(g)`
  - `dark_share` (function, line 85) `def dark_share(img, box)`
  - `wait_frames` (function, line 95) `def wait_frames(g, want)`
  - `main` (function, line 110) `def main()`
- Depends on: `kernel/time.c`, `tools/test_gui_wm.py`

## tools/test_gui_icon_cwd.py
- Doc: GUI proof that dock launches ignore shell cwd.
- Layer: testing
- Language: py
- Symbols:
  - `note` (function, line 36) `def note(ok, msg)`
  - `Guest` (class, line 42) `class Guest`
  - `find_icon` (function, line 180) `def find_icon(shot_path, icon_path)`
  - `walk` (function, line 213) `def walk(g, tx, ty, fw, fh)`
  - `main` (function, line 228) `def main()`
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
- Doc: serial proof that the minicraft pause menu works.
- Layer: testing
- Language: py
- Symbols:
  - `main` (function, line 20) `def main()`
- Depends on: `kernel/time.c`, `tools/test_gui_wm.py`

## tools/test_gui_wm.py
- Doc: GUI proof that graphics windows survive the WM.
- Layer: testing
- Language: py
- Symbols:
  - `note` (function, line 40) `def note(ok, msg)`
  - `Guest` (class, line 46) `class Guest`
  - `meandiff` (function, line 204) `def meandiff(a_path, b_path)`
  - `main` (function, line 214) `def main()`
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
- Imported by: `tools/test_gui_gfxview.py`, `tools/test_gui_menu.py`, `tools/test_gui_zoom.py`, `tools/test_readme_shot.py`

## tools/test_gui_zoom.py
- Doc: pixel proof that GFX_ZOOM doubles the game window.
- Layer: testing
- Language: py
- Symbols:
  - `main` (function, line 22) `def main()`
- Depends on: `kernel/time.c`, `tools/test_gui_wm.py`

## tools/test_http_server.py
- Layer: testing
- Language: py
- Symbols:
  - `Handler` (class, line 21) `class Handler(BaseHTTPRequestHandler)`
  - `do_GET` (method, line 24) `def do_GET(self)`
  - `log_message` (method, line 114) `def log_message(self, fmt)`
- Depends on: `kernel/time.c`

## tools/test_lisp.py
- Doc: Host test suite for the MiniOS Lisp interpreter.
- Layer: testing
- Language: py
- Symbols:
  - `LispConfig` (class, line 28) `class LispConfig`
  - `LispTest` (class, line 37) `class LispTest`
  - `build_binary` (function, line 308) `def build_binary(source, output)`
  - `main` (function, line 321) `def main()`
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

## tools/test_net_fixture.py
- Doc: host-side UDP and TCP echo fixture for lxnet.
- Layer: testing
- Language: py
- Symbols:
  - `Config` (class, line 26) `class Config`
  - `serve_udp` (function, line 34) `def serve_udp(port)`
  - `echo_stream` (function, line 43) `def echo_stream(conn)`
  - `serve_tcp` (function, line 53) `def serve_tcp(port)`
  - `main` (function, line 64) `def main()`

## tools/test_readme_shot.py
- Doc: verify the desktop and refresh the README image.
- Layer: testing
- Language: py
- Symbols:
  - `Config` (class, line 43) `class Config`
  - `crop_box` (function, line 66) `def crop_box(size, fractions)`
  - `pixels` (function, line 73) `def pixels(img)`
  - `count_pixels` (function, line 79) `def count_pixels(img, box, predicate)`
  - `check_frame` (function, line 84) `def check_frame(img)`
  - `write_atomic` (function, line 115) `def write_atomic(img, path)`
  - `stage_scene` (function, line 131) `def stage_scene(guest)`
  - `main` (function, line 140) `def main(argv)`
- Depends on: `kernel/time.c`, `tools/test_gui_wm.py`

## tools/test_sb16.sh
- Doc: — targeted BDD harness for the SB16 audio path.
- Layer: testing
- Language: sh
- Symbols:
  - `fail_msg` (function, line 45)

## tools/tls_test.py
- Doc: Host-side TLS test driver for the MiniOS kernel TLS client.
- Layer: testing
- Language: py
- Symbols:
  - `run` (function, line 32) `def run(cmd)`
  - `check` (function, line 36) `def check(cmd)`
  - `gen_certs` (function, line 43) `def gen_certs()`
  - `der_bytes` (function, line 160) `def der_bytes(pem_path)`
  - `rsa_params` (function, line 168) `def rsa_params(key_path)`
  - `ec_pub` (function, line 178) `def ec_pub(key_path)`
  - `c_bytes` (function, line 189) `def c_bytes(data, name)`
  - `gen_header` (function, line 197) `def gen_header(p)`
  - `Server` (class, line 247) `class Server(Thread)`
  - `serve` (function, line 286) `def serve(cert, key)`
  - `serve_openssl` (function, line 294) `def serve_openssl(cert, key, chain)`
  - `expect` (function, line 312) `def expect(bin_path, args, want_zero, marker)`
  - `main` (function, line 325) `def main()`
  - `server_cert` (function, line 67) `def server_cert(name, algo, curve, ca_name, ca_algo, curve_ca, extra, subj)`
  - `__init__` (method, line 248) `def __init__(self, cert, key, tls13_ok)`
  - `run` (method, line 254) `def run(self)`
- Depends on: `kernel/time.c`

## tools/update_sources.py
- Doc: Update the sibling source checkouts MiniOS builds against.
- Layer: utility
- Language: py
- Symbols:
  - `Repo` (class, line 96) `class Repo`
  - `GitResult` (class, line 203) `class GitResult`
  - `Outcome` (class, line 216) `class Outcome`
  - `GitError` (class, line 232) `class GitError(RuntimeError)`
  - `run_git` (function, line 236) `def run_git(git, cwd)`
  - `git_out` (function, line 253) `def git_out(git, cwd)`
  - `head_sha` (function, line 261) `def head_sha(git, path)`
  - `short_sha` (function, line 266) `def short_sha(sha)`
  - `current_branch` (function, line 271) `def current_branch(git, path)`
  - `is_dirty` (function, line 276) `def is_dirty(git, path)`
  - `is_shallow` (function, line 281) `def is_shallow(git, path)`
  - `resolve_path` (function, line 286) `def resolve_path(directory)`
  - `fetch_upstream` (function, line 294) `def fetch_upstream(git, path, branch, shallow_depth)`
  - `deepen_upstream` (function, line 306) `def deepen_upstream(git, path, branch, commits)`
  - `upstream_target` (function, line 316) `def upstream_target(git, path, branch)`
  - `ahead_behind` (function, line 325) `def ahead_behind(git, path, branch)`
  - `fast_forward` (function, line 339) `def fast_forward(git, path, target)`
  - `reconcile` (function, line 344) `def reconcile(git, path, target, strategy)`
  - `abort_reconcile` (function, line 351) `def abort_reconcile(git, path, strategy)`
  - `conflicted_files` (function, line 359) `def conflicted_files(git, path)`
  - `update_submodules` (function, line 365) `def update_submodules(git, path, submodules)`
  - `handle_tracked` (function, line 375) `def handle_tracked(git, repo, path, dry_run, fetch_enabled, strategy)`
  - `handle_pinned` (function, line 446) `def handle_pinned(git, repo, path, dry_run, fetch_enabled)`
  - `handle_repo` (function, line 493) `def handle_repo(git, repo, directory, dry_run, fetch_enabled, strategy)`
  - `write_snapshot` (function, line 513) `def write_snapshot(path, outcomes)`
  - `rollback` (function, line 535) `def rollback(git, snapshot_path, directories)`
  - `print_status` (function, line 572) `def print_status(git, selected, directories)`
  - `print_outcome` (function, line 594) `def print_outcome(outcome)`
  - `select_repos` (function, line 599) `def select_repos(names)`
  - `parse_overrides` (function, line 614) `def parse_overrides(pairs)`
  - `main` (function, line 634) `def main(argv)`
  - `ok` (method, line 211) `def ok(self)`
  - `changed` (method, line 228) `def changed(self)`

## tools/wl_scoped.sh
- Doc: Docstring: Scoped Wayland-mini validation for the tiled ring-3 compositor.
- Layer: utility
- Language: sh
- Symbols:
  - `say` (function, line 8)
  - `die` (function, line 9)
  - `mut` (function, line 77)
  - `mutm` (function, line 84)

## tools/wm_layout_sync.py
- Doc: Docstring: Synchronize the WM layout manifest from source truth.
- Layer: presentation
- Language: py
- Symbols:
  - `WmLayoutSyncConfig` (class, line 17) `class WmLayoutSyncConfig`
  - `WmLayoutSyncResult` (class, line 36) `class WmLayoutSyncResult`
  - `WmLayoutSync` (class, line 46) `class WmLayoutSync`
  - `parse_args` (function, line 151) `def parse_args(argv)`
  - `main` (function, line 159) `def main(argv)`
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
- Doc: Docstring: Scoped WM validation for Alt-Tab and tile across all windows.
- Layer: utility
- Language: sh
- Symbols:
  - `say` (function, line 8)
  - `die` (function, line 9)

