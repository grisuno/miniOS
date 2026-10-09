# Subsystem: tools (page 2 of 2)
Previous: [KB_tools.md](KB_tools.md)

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
- Doc: BDD suite for MiniOS: boots the disk image in QEMU and drives the shell over the serial console...
- Layer: testing
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
  - `http_server_start` (function, line 1311)
  - `http_server_stop` (function, line 1318)
  - `http_fixture_start` (function, line 1323)
  - `http_fixture_stop` (function, line 1330)
  - `net_fixture_start` (function, line 1335)
  - `net_fixture_stop` (function, line 1342)

## tools/test_call_align.py
- Doc: verify stack alignment at call sites, both parities.
- Layer: testing
- Language: py
- Symbols:
  - `AlignConfig` (class, line 24) `class AlignConfig`
  - `find_minigcc` (method, line 59) `def find_minigcc(explicit)`
  - `run` (method, line 74) `def run(argv)`
  - `main` (method, line 79) `def main(argv)`

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

## tools/test_gui_freedom.py
- Doc: GUI proof that freedom-gui takes real input.
- Layer: testing
- Language: py
- Symbols:
  - `Config` (class, line 36) `class Config`
  - `note` (method, line 66) `def note(ok, msg)`
  - `Guest` (class, line 73) `class Guest`
  - `region_diff` (method, line 213) `def region_diff(a_path, b_path, box)`
  - `content_origin` (method, line 221) `def content_origin(listing)`
  - `screen_box` (method, line 230) `def screen_box(origin, box)`
  - `move_to` (method, line 235) `def move_to(g, frame_size, target)`
  - `main` (method, line 247) `def main()`
  - `__init__` (method, line 76) `def __init__(self, work)`
  - `_connect` (method, line 100) `def _connect(self, path)`
  - `_serial` (method, line 109) `def _serial(self)`
  - `_reader` (method, line 114) `def _reader(self)`
  - `snapshot` (method, line 125) `def snapshot(self)`
  - `wait_for` (method, line 129) `def wait_for(self, text, timeout)`
  - `send` (method, line 137) `def send(self, line, settle)`
  - `qmp_cmd` (method, line 148) `def qmp_cmd(self, obj)`
  - `_qmp` (method, line 155) `def _qmp(self, obj)`
  - `keys` (method, line 163) `def keys(self, events)`
  - `tap` (method, line 171) `def tap(self, qcode)`
  - `chord` (method, line 174) `def chord(self, mod, qcode)`
  - `rel` (method, line 177) `def rel(self, dx, dy)`
  - `button` (method, line 182) `def button(self, down)`
  - `dump` (method, line 188) `def dump(self, name)`
  - `stop` (method, line 194) `def stop(self)`
- Depends on: `kernel/time.c`

## tools/test_gui_gfxview.py
- Doc: pixel + serial proof of the graphics view contract.
- Layer: testing
- Language: py
- Symbols:
  - `Config` (class, line 39) `class Config`
  - `note` (method, line 55) `def note(ok, msg)`
  - `last_line` (method, line 62) `def last_line(g, prefix)`
  - `gfx_row` (method, line 72) `def gfx_row(g)`
  - `dark_share` (method, line 84) `def dark_share(img, box)`
  - `wait_frames` (method, line 94) `def wait_frames(g, want)`
  - `main` (method, line 109) `def main()`
- Depends on: `kernel/time.c`, `tools/test_gui_wm.py`

## tools/test_gui_icon_cwd.py
- Doc: GUI proof that dock launches ignore shell cwd.
- Layer: testing
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
- Imported by: `tools/test_gui_gfxview.py`, `tools/test_gui_menu.py`, `tools/test_gui_zoom.py`

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

## tools/test_net_fixture.py
- Doc: host-side UDP and TCP echo fixture for lxnet.
- Layer: testing
- Language: py
- Symbols:
  - `Config` (class, line 26) `class Config`
  - `serve_udp` (method, line 34) `def serve_udp(port)`
  - `echo_stream` (method, line 43) `def echo_stream(conn)`
  - `serve_tcp` (method, line 53) `def serve_tcp(port)`
  - `main` (method, line 64) `def main()`

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
- Doc: Docstring: Scoped WM validation for Alt-Tab and tile across all windows.
- Layer: utility
- Language: sh
- Symbols:
  - `say` (function, line 8)
  - `die` (function, line 9)

