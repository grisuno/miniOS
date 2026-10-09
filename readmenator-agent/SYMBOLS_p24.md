# Symbols (page 24 of 25)
Previous: [SYMBOLS_p23.md](SYMBOLS_p23.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `str_probe` | function | `tests/test_sanitize.c:54` | `static long str_probe(unsigned long p)` |
| `user_range_ok` | function | `tests/test_sanitize.c:20` | `int user_range_ok(unsigned long p, unsigned long len)` |
| `user_str_ok` | function | `tests/test_sanitize.c:26` | `int user_str_ok(unsigned long p, unsigned long maxlen)` |
| `CHECK` | macro | `tests/test_sync.c:37` | `#define CHECK(cond, msg)` |
| `fresh_all` | function | `tests/test_sync.c:52` | `static void fresh_all(void)` |
| `fresh_proc` | function | `tests/test_sync.c:44` | `static void fresh_proc(int pid)` |
| `main` | function | `tests/test_sync.c:63` | `int main(void)` |
| `proc_get` | function | `tests/test_sync.c:24` | `proc_t *proc_get(int pid)` |
| `schedule` | function | `tests/test_sync.c:30` | `void schedule(void)` |
| `CHECK` | macro | `tests/test_theme.c:16` | `#define CHECK(cond, msg)` |
| `X` | macro | `tests/test_theme.c:29` | `#define X(k, i)` |
| `check_theme_file` | function | `tests/test_theme.c:78` | `static void check_theme_file(const char *path)` |
| `cube_exact` | function | `tests/test_theme.c:74` | `static int cube_exact(long v)` |
| `main` | function | `tests/test_theme.c:107` | `int main(void)` |
| `t_name_ok` | function | `tests/test_theme.c:34` | `static int t_name_ok(const char *name)` |
| `t_parse_line` | function | `tests/test_theme.c:46` | `static int t_parse_line(const char *line, int *idx, long v[3])` |
| `tslot` | struct | `tests/test_theme.c:23` | `` |
| `CHECK` | macro | `tests/test_tick.c:17` | `#define CHECK(cond, msg)` |
| `dummy` | function | `tests/test_tick.c:47` | `static void dummy(void *ctx)` |
| `main` | function | `tests/test_tick.c:52` | `int main(void)` |
| `rec_a` | function | `tests/test_tick.c:24` | `static void rec_a(void *ctx)` |
| `rec_b` | function | `tests/test_tick.c:31` | `static void rec_b(void *ctx)` |
| `rec_d` | function | `tests/test_tick.c:38` | `static void rec_d(void *ctx)` |
| `CHECK` | macro | `tests/test_usbblk.c:36` | `#define CHECK(cond, msg)` |
| `device_find` | function | `tests/test_usbblk.c:26` | `device_t *device_find(const char *name)` |
| `device_register` | function | `tests/test_usbblk.c:20` | `int device_register(device_t *dev)` |
| `main` | function | `tests/test_usbblk.c:43` | `int main(void)` |
| `CHECK` | macro | `tests/test_usbhid.c:41` | `#define CHECK(cond, msg)` |
| `check_usage` | function | `tests/test_usbhid.c:48` | `static void check_usage(unsigned usage, unsigned char want_sc, int want_e0,                      ...` |
| `kbd_feed_scancode` | function | `tests/test_usbhid.c:22` | `int kbd_feed_scancode(unsigned char sc)` |
| `kbd_q_push` | function | `tests/test_usbhid.c:30` | `void kbd_q_push(unsigned char c)` |
| `main` | function | `tests/test_usbhid.c:59` | `int main(void)` |
| `CHECK` | macro | `tests/test_vedit_build.c:33` | `#define CHECK(cond, msg)` |
| `main` | function | `tests/test_vedit_build.c:345` | `int main(void)` |
| `t_base_of` | function | `tests/test_vedit_build.c:51` | `static int t_base_of(const char *fname, char *dst, size_t cap)` |
| `t_cmd` | function | `tests/test_vedit_build.c:299` | `static int t_cmd(const char *name)` |
| `t_has_ext` | function | `tests/test_vedit_build.c:40` | `static int t_has_ext(const char *fname, const char *ext)` |
| `t_join` | function | `tests/test_vedit_build.c:71` | `static int t_join(const char *dir, const char *base, const char *ext,                   char *dst...` |
| `t_lang_of` | function | `tests/test_vedit_build.c:101` | `static int t_lang_of(const char *fname)` |
| `t_link_fmt` | function | `tests/test_vedit_build.c:87` | `static int t_link_fmt(const char *s)` |
| `t_magic` | function | `tests/test_vedit_build.c:268` | `static int t_magic(const char *text, const char *pat, int *mlen)` |
| `t_matom` | function | `tests/test_vedit_build.c:188` | `static int t_matom(const char *pat, int c, int *atom_len)` |
| `t_mclass` | function | `tests/test_vedit_build.c:166` | `static int t_mclass(int c, const char *cls)` |
| `t_mhere` | function | `tests/test_vedit_build.c:211` | `static int t_mhere(const char *text, const char *pat, int *mlen)` |
| `t_parse_key` | function | `tests/test_vedit_build.c:312` | `static int t_parse_key(const char *s)` |
| `t_run_kind` | function | `tests/test_vedit_build.c:121` | `static int t_run_kind(const char *fname)` |
| `t_str_case` | function | `tests/test_vedit_build.c:131` | `static void t_str_case(char *s, int mode)` |
| `t_transpose` | function | `tests/test_vedit_build.c:157` | `static void t_transpose(char *s, int len, int pos)` |
| `CHECK` | macro | `tests/test_vma.c:20` | `#define CHECK(cond, msg)` |
| `black_height` | function | `tests/test_vma.c:27` | `static int black_height(const vma_node_t *n)` |
| `count_nodes` | function | `tests/test_vma.c:75` | `static int count_nodes(const vma_node_t *root)` |
| `main` | function | `tests/test_vma.c:199` | `int main(void)` |
| `test_file_tags_and_containing` | function | `tests/test_vma.c:167` | `static void test_file_tags_and_containing(void)` |
| `test_full_drain` | function | `tests/test_vma.c:153` | `static void test_full_drain(void)` |
| `test_insert_find_delete` | function | `tests/test_vma.c:89` | `static void test_insert_find_delete(void)` |
| `test_pool_exhaustion` | function | `tests/test_vma.c:136` | `static void test_pool_exhaustion(void)` |
| `tree_valid` | function | `tests/test_vma.c:38` | `static int tree_valid(const vma_node_t *root)` |
| `LIST_MAX` | macro | `tests/test_vma_bench.c:20` | `#define LIST_MAX` |
| `bench` | function | `tests/test_vma_bench.c:34` | `static void bench(int n)` |
| `l_find` | function | `tests/test_vma_bench.c:28` | `static int l_find(unsigned long b)` |
| `l_insert` | function | `tests/test_vma_bench.c:23` | `static void l_insert(unsigned long b)` |
| `main` | function | `tests/test_vma_bench.c:54` | `int main(void)` |
| `now_us` | function | `tests/test_vma_bench.c:13` | `static long now_us(void)` |
| `CHECK` | macro | `tests/test_wl.c:20` | `#define CHECK(cond, msg)` |
| `main` | function | `tests/test_wl.c:27` | `int main(void)` |
| `CHECK` | macro | `tests/test_wm.c:22` | `#define CHECK(cond, msg)` |
| `main` | function | `tests/test_wm.c:29` | `int main(void)` |
| `CHECK` | macro | `tests/test_xhci.c:23` | `#define CHECK(cond, msg)` |
| `main` | function | `tests/test_xhci.c:30` | `int main(void)` |
| `CHECK` | macro | `tls_test.c:62` | `#define CHECK(name, cond)` |
| `bytes_eq` | function | `tls_test.c:80` | `static int bytes_eq(const unsigned char *a, const unsigned char *b, int n)` |
| `hexdigit` | function | `tls_test.c:67` | `static int hexdigit(int c)` |
| `http_over_tls` | function | `tls_test.c:265` | `static int http_over_tls(int port, const char *host)` |
| `main` | function | `tls_test.c:349` | `int main(int argc, char **argv)` |
| `scenario_bad_ca` | function | `tls_test.c:329` | `static int scenario_bad_ca(int port)` |
| `scenario_bad_host` | function | `tls_test.c:319` | `static int scenario_bad_host(int port)` |
| `scenario_expired` | function | `tls_test.c:339` | `static int scenario_expired(int port)` |
| `scenario_good` | function | `tls_test.c:290` | `static int scenario_good(int port)` |
| `scenario_wild_deep` | function | `tls_test.c:309` | `static int scenario_wild_deep(int port)` |
| `scenario_wild_good` | function | `tls_test.c:295` | `static int scenario_wild_good(int port)` |
| `scenario_wild_root` | function | `tls_test.c:299` | `static int scenario_wild_root(int port)` |
| `tcp_connect` | function | `tls_test.c:249` | `static int tcp_connect(int port)` |
| `test_gcm` | function | `tls_test.c:114` | `static void test_gcm(void)` |
| `test_p256` | function | `tls_test.c:154` | `static void test_p256(void)` |
| `test_rsa_ecdsa_vectors` | function | `tls_test.c:200` | `static void test_rsa_ecdsa_vectors(void)` |
| `test_sha256` | function | `tls_test.c:88` | `static void test_sha256(void)` |
| `test_sha384` | function | `tls_test.c:103` | `static void test_sha384(void)` |
| `tls_test_close` | function | `tls_test.c:54` | `void tls_test_close(int fd)` |
| `tls_test_recv` | function | `tls_test.c:36` | `int tls_test_recv(int fd, char *buf, int len)` |
| `tls_test_recv_timeout` | function | `tls_test.c:41` | `int tls_test_recv_timeout(int fd, char *buf, int len, unsigned long ms)` |
| `tls_test_send` | function | `tls_test.c:26` | `int tls_test_send(int fd, const char *buf, int len)` |
| `unhex` | function | `tls_test.c:74` | `static void unhex(const char *hex, unsigned char *out, int n)` |
| `main` | function | `tools/abi_stamp.c:14` | `int main(void)` |
| `WlBoot` | class | `tools/boot_wl.py:67` | `class WlBoot` |
| `WlBootConfig` | class | `tools/boot_wl.py:40` | `class WlBootConfig` |
| `__init__` | method | `tools/boot_wl.py:68` | `def __init__(self, cfg)` |
| `boot` | method | `tools/boot_wl.py:91` | `def boot(self)` |
| `close` | method | `tools/boot_wl.py:80` | `def close(self)` |
| `fail` | method | `tools/boot_wl.py:75` | `def fail(self, msg)` |
| `headless` | method | `tools/boot_wl.py:182` | `def headless(self)` |
| `main` | method | `tools/boot_wl.py:226` | `def main()` |
| `proxy` | method | `tools/boot_wl.py:195` | `def proxy(self)` |
| `qmp` | method | `tools/boot_wl.py:165` | `def qmp(self, obj)` |
| `send` | method | `tools/boot_wl.py:135` | `def send(self, line)` |
| `send_wait` | method | `tools/boot_wl.py:142` | `def send_wait(self, line, timeout)` |
| `setup` | method | `tools/boot_wl.py:154` | `def setup(self)` |
| `snapshot` | method | `tools/boot_wl.py:107` | `def snapshot(self, timeout)` |
| `wait_prompt` | method | `tools/boot_wl.py:124` | `def wait_prompt(self)` |
| `main` | function | `tools/check_abi_numbers.py:156` | `def main()` |
| `normalize` | function | `tools/check_abi_numbers.py:128` | `def normalize(minios_name)` |
| `parse_abi` | function | `tools/check_abi_numbers.py:132` | `def parse_abi(path)` |
| `parse_dispatch` | function | `tools/check_abi_numbers.py:143` | `def parse_dispatch(path)` |
| `load_parser` | function | `tools/check_addons.py:22` | `def load_parser()` |
| `main` | function | `tools/check_addons.py:31` | `def main()` |
| `compute_cohesion` | function | `tools/check_cohesion.py:31` | `def compute_cohesion(community_nodes, community_edges)` |
| `extract_communities` | function | `tools/check_cohesion.py:42` | `def extract_communities(cpg)` |
| `load_cpg` | function | `tools/check_cohesion.py:23` | `def load_cpg(path)` |
| `main` | function | `tools/check_cohesion.py:58` | `def main()` |
| `count_symbols` | function | `tools/check_complexity.py:24` | `def count_symbols(filepath)` |
| `load_approval` | function | `tools/check_complexity.py:46` | `def load_approval(policy_path)` |
| `main` | function | `tools/check_complexity.py:61` | `def main()` |
| `Config` | class | `tools/check_fork_stubs.py:18` | `class Config` |
| `check_stubs` | method | `tools/check_fork_stubs.py:37` | `def check_stubs(text, cfg)` |
| `handler_body` | method | `tools/check_fork_stubs.py:27` | `def handler_body(text, name)` |
| `main` | method | `tools/check_fork_stubs.py:52` | `def main()` |
| `main` | function | `tools/check_kb_sync.py:43` | `def main()` |
| `regenerate_kb` | function | `tools/check_kb_sync.py:24` | `def regenerate_kb()` |
| `Config` | class | `tools/check_mutant_anchors.py:17` | `class Config` |
| `anchor_matches` | method | `tools/check_mutant_anchors.py:67` | `def anchor_matches(repo, target, expr)` |
| `bash_unquote` | method | `tools/check_mutant_anchors.py:26` | `def bash_unquote(expr)` |
| `main` | method | `tools/check_mutant_anchors.py:86` | `def main()` |
| `parse_mutations` | method | `tools/check_mutant_anchors.py:41` | `def parse_mutations(text)` |
| `Config` | class | `tools/check_spin_discipline.py:23` | `class Config` |
| `check_file` | method | `tools/check_spin_discipline.py:64` | `def check_file(path)` |
| `iter_functions` | method | `tools/check_spin_discipline.py:38` | `def iter_functions(path)` |
| `main` | method | `tools/check_spin_discipline.py:99` | `def main(argv)` |
| `bfs_min_hops` | function | `tools/check_surprising.py:56` | `def bfs_min_hops(nodes, edges, source, target_community, max_hops)` |
| `build_graph` | function | `tools/check_surprising.py:33` | `def build_graph(cpg)` |
| `find_surprising_connections` | function | `tools/check_surprising.py:87` | `def find_surprising_connections(nodes, edges, min_hops)` |
| `load_cpg` | function | `tools/check_surprising.py:25` | `def load_cpg(path)` |
| `main` | function | `tools/check_surprising.py:118` | `def main()` |
| `Config` | class | `tools/check_syscall_sanitize.py:18` | `class Config` |
| `audit_body` | method | `tools/check_syscall_sanitize.py:162` | `def audit_body(name, body)` |
| `audit_file` | method | `tools/check_syscall_sanitize.py:217` | `def audit_file(path)` |
| `checked_names` | method | `tools/check_syscall_sanitize.py:112` | `def checked_names(body)` |
| `delegated_only` | method | `tools/check_syscall_sanitize.py:122` | `def delegated_only(body, alias)` |
| `main` | method | `tools/check_syscall_sanitize.py:228` | `def main()` |
| `split_functions` | method | `tools/check_syscall_sanitize.py:69` | `def split_functions(lines)` |
| `split_top_args` | method | `tools/check_syscall_sanitize.py:143` | `def split_top_args(argtext)` |
| `ClipBridgeConfig` | class | `tools/clip_bridge.py:30` | `class ClipBridgeConfig` |
| `build_plan` | method | `tools/clip_bridge.py:59` | `def build_plan(text, dst, cfg)` |
| `main` | method | `tools/clip_bridge.py:84` | `def main(argv)` |
| `printable_line` | method | `tools/clip_bridge.py:52` | `def printable_line(line, cfg)` |
| `valid_dst` | method | `tools/clip_bridge.py:41` | `def valid_dst(name, cfg)` |
| `DoomPwadConfig` | class | `tools/doom_pwad.py:52` | `class DoomPwadConfig` |
| `PwadError` | class | `tools/doom_pwad.py:161` | `class PwadError(Exception)` |
| `build_lumps` | method | `tools/doom_pwad.py:516` | `def build_lumps(rows)` |
| `build_pwad` | method | `tools/doom_pwad.py:597` | `def build_pwad(rows)` |
| `cell_class` | method | `tools/doom_pwad.py:279` | `def cell_class(cell)` |
| `cell_corners` | method | `tools/doom_pwad.py:269` | `def cell_corners(row, col)` |
| `check_multiple` | method | `tools/doom_pwad.py:655` | `def check_multiple(name, fmt)` |
| `check_pwad` | method | `tools/doom_pwad.py:639` | `def check_pwad(data)` |
| `cmd_build` | method | `tools/doom_pwad.py:816` | `def cmd_build(grid_path, out_path)` |
| `cmd_check` | method | `tools/doom_pwad.py:826` | `def cmd_check(path)` |
| `compile_geometry` | method | `tools/doom_pwad.py:371` | `def compile_geometry(rows, exit_pos, wall_side)` |
| `compile_things` | method | `tools/doom_pwad.py:485` | `def compile_things(rows)` |
| `flood_reachable` | method | `tools/doom_pwad.py:210` | `def flood_reachable(rows)` |
| `grid_extents` | method | `tools/doom_pwad.py:195` | `def grid_extents(rows)` |
| `is_wall` | method | `tools/doom_pwad.py:203` | `def is_wall(rows, row, col)` |
| `label_regions` | method | `tools/doom_pwad.py:291` | `def label_regions(rows)` |
| `main` | method | `tools/doom_pwad.py:834` | `def main(argv)` |
| `pad_tex` | method | `tools/doom_pwad.py:165` | `def pad_tex(raw)` |
| `parse_grid` | method | `tools/doom_pwad.py:172` | `def parse_grid(text)` |
| `payload` | method | `tools/doom_pwad.py:650` | `def payload(name)` |
| `read_pwad` | method | `tools/doom_pwad.py:616` | `def read_pwad(data)` |
| `region_sector` | method | `tools/doom_pwad.py:326` | `def region_sector(region, door_tag)` |
| `seg_angle` | method | `tools/doom_pwad.py:506` | `def seg_angle(dx, dy)` |
| `validate_grid` | method | `tools/doom_pwad.py:240` | `def validate_grid(rows)` |
| `vertex` | method | `tools/doom_pwad.py:386` | `def vertex(x, y)` |
| `main` | function | `tools/gdb_repro.py:27` | `def main()` |
| `quit_doom` | function | `tools/gdb_repro.py:70` | `def quit_doom()` |
| `rs` | function | `tools/gdb_repro.py:23` | `def rs(m, t)` |
| `send` | function | `tools/gdb_repro.py:65` | `def send(line)` |
| `main` | function | `tools/gen_desktop_pngs.py:75` | `def main()` |
| `write_atomic` | function | `tools/gen_desktop_pngs.py:69` | `def write_atomic(img, path)` |
| `main` | function | `tools/gen_icons.py:214` | `def main()` |
| `make_chunk` | function | `tools/gen_icons.py:209` | `def make_chunk(chunk_type, data)` |
| `make_png` | function | `tools/gen_icons.py:179` | `def make_png(pixels, palette, width, height)` |
| `main` | function | `tools/gen_zip_fixtures.py:42` | `def main()` |
| `write_zip` | function | `tools/gen_zip_fixtures.py:28` | `def write_zip(path, entries)` |
| `SurveyConfig` | class | `tools/kernel_feature_survey.py:18` | `class SurveyConfig` |
| `count_params` | method | `tools/kernel_feature_survey.py:59` | `def count_params(params)` |
| `find_asm_constraints` | method | `tools/kernel_feature_survey.py:49` | `def find_asm_constraints(path, text)` |
| `find_fnptr_hits` | method | `tools/kernel_feature_survey.py:43` | `def find_fnptr_hits(path, text)` |
| `iter_sources` | method | `tools/kernel_feature_survey.py:34` | `def iter_sources(root)` |
| `main` | method | `tools/kernel_feature_survey.py:122` | `def main(argv)` |
| `render_text` | method | `tools/kernel_feature_survey.py:103` | `def render_text(findings)` |
| `survey` | method | `tools/kernel_feature_survey.py:67` | `def survey(root)` |
| `die` | function | `tools/lisp_scoped.sh:9` | `` |
| `lisp_mut` | function | `tools/lisp_scoped.sh:41` | `` |
| `mut_usage` | function | `tools/lisp_scoped.sh:63` | `` |
| `mutant` | function | `tools/lisp_scoped.sh:20` | `` |
| `say` | function | `tools/lisp_scoped.sh:8` | `` |
| `usage` | function | `tools/make_usb.sh:40` | `` |
| `wizard` | function | `tools/make_usb.sh:56` | `` |
| `FS` | class | `tools/minifs_dump.py:25` | `class FS` |
| `__init__` | method | `tools/minifs_dump.py:26` | `def __init__(self, fn)` |
| `_sb` | method | `tools/minifs_dump.py:30` | `def _sb(self)` |
| `blk` | method | `tools/minifs_dump.py:29` | `def blk(self, n)` |
| `inode` | method | `tools/minifs_dump.py:38` | `def inode(self, i)` |
| `ls` | method | `tools/minifs_dump.py:86` | `def ls(self, ino, prefix)` |
| `main` | method | `tools/minifs_dump.py:105` | `def main()` |
| `mode_str` | function | `tools/minifs_dump.py:16` | `def mode_str(m)` |
| `read` | method | `tools/minifs_dump.py:47` | `def read(self, ino)` |
| `resolve` | method | `tools/minifs_dump.py:67` | `def resolve(self, path)` |
| `u16` | function | `tools/minifs_dump.py:13` | `def u16(d, o)` |
| `u32` | function | `tools/minifs_dump.py:14` | `def u32(d, o)` |
| `FSCK` | class | `tools/minifs_fsck.py:23` | `class FSCK` |
| `__init__` | method | `tools/minifs_fsck.py:24` | `def __init__(self, fn)` |
| `_find_base` | method | `tools/minifs_fsck.py:31` | `def _find_base(self)` |
| `_sb` | method | `tools/minifs_fsck.py:52` | `def _sb(self)` |
| `blk` | method | `tools/minifs_fsck.py:49` | `def blk(self, n)` |
| `crc32` | function | `tools/minifs_fsck.py:15` | `def crc32(data)` |
| `err` | method | `tools/minifs_fsck.py:86` | `def err(self, msg)` |
| `inode` | method | `tools/minifs_fsck.py:58` | `def inode(self, i)` |
| `inode_crc_ok` | method | `tools/minifs_fsck.py:65` | `def inode_crc_ok(self, i)` |
| `main` | method | `tools/minifs_fsck.py:152` | `def main()` |
| `mark_block` | method | `tools/minifs_fsck.py:88` | `def mark_block(self, n)` |
| `read` | method | `tools/minifs_fsck.py:71` | `def read(self, ino)` |
| `run` | method | `tools/minifs_fsck.py:137` | `def run(self)` |
| `scan_dir` | method | `tools/minifs_fsck.py:105` | `def scan_dir(self, ino)` |
| `scan_inode` | method | `tools/minifs_fsck.py:93` | `def scan_inode(self, i)` |
| `u16` | function | `tools/minifs_fsck.py:13` | `def u16(d, o)` |
| `u32` | function | `tools/minifs_fsck.py:14` | `def u32(d, o)` |
| `FS` | class | `tools/minifs_saves.py:85` | `class FS` |
| `Image` | class | `tools/minifs_saves.py:61` | `class Image` |
| `__init__` | method | `tools/minifs_saves.py:64` | `def __init__(self, fn, base)` |
| `__init__` | method | `tools/minifs_saves.py:86` | `def __init__(self, img)` |
| `blk` | method | `tools/minifs_saves.py:75` | `def blk(self, n)` |
| `close` | method | `tools/minifs_saves.py:72` | `def close(self)` |
| `cmd_backup` | method | `tools/minifs_saves.py:271` | `def cmd_backup(img_path, stage)` |
| `find_partition_base` | method | `tools/minifs_saves.py:233` | `def find_partition_base(fn)` |
| `inode` | method | `tools/minifs_saves.py:95` | `def inode(self, i)` |
| `is_dir` | method | `tools/minifs_saves.py:110` | `def is_dir(self, st)` |
| `listdir` | method | `tools/minifs_saves.py:146` | `def listdir(self, ino)` |
| `main` | method | `tools/minifs_saves.py:343` | `def main(argv)` |
| `read_file` | method | `tools/minifs_saves.py:113` | `def read_file(self, ino)` |
| `read_file_dir` | method | `tools/minifs_saves.py:165` | `def read_file_dir(self, ino)` |
| `read_file_raw` | method | `tools/minifs_saves.py:173` | `def read_file_raw(self, st)` |
| `resolve` | method | `tools/minifs_saves.py:197` | `def resolve(self, path)` |
| `strict_name` | method | `tools/minifs_saves.py:224` | `def strict_name(nm)` |
| `u16` | function | `tools/minifs_saves.py:53` | `def u16(d, o)` |
| `u32` | function | `tools/minifs_saves.py:57` | `def u32(d, o)` |
| `valid_name` | method | `tools/minifs_saves.py:216` | `def valid_name(nm)` |
| `walk` | method | `tools/minifs_saves.py:293` | `def walk(dir_ino, rel)` |
| `Client` | class | `tools/minios_cli.py:38` | `class Client` |
| `__init__` | method | `tools/minios_cli.py:39` | `def __init__(self)` |
| `close` | method | `tools/minios_cli.py:87` | `def close(self)` |
| `main` | method | `tools/minios_cli.py:100` | `def main()` |
| `request` | method | `tools/minios_cli.py:56` | `def request(self, method, params)` |
| `tool` | method | `tools/minios_cli.py:77` | `def tool(self, name, params)` |
| `QMP` | class | `tools/minios_gui.py:66` | `class QMP` |
| `__init__` | method | `tools/minios_gui.py:67` | `def __init__(self, path)` |
| `_recv` | method | `tools/minios_gui.py:83` | `def _recv(self)` |
| `cmd` | method | `tools/minios_gui.py:79` | `def cmd(self, obj)` |
| `key` | method | `tools/minios_gui.py:108` | `def key(self, qcode, up)` |
| `main` | method | `tools/minios_gui.py:118` | `def main()` |
| `mouse` | method | `tools/minios_gui.py:98` | `def mouse(self, dx, dy, click)` |
| `read_serial` | function | `tools/minios_gui.py:50` | `def read_serial(master, timeout)` |
| `screendump` | method | `tools/minios_gui.py:114` | `def screendump(self, path)` |
| `FrameDiff` | class | `tools/minios_hyper.py:339` | `class FrameDiff` |
| `GdbChannel` | class | `tools/minios_hyper.py:152` | `class GdbChannel` |
| `Guest` | class | `tools/minios_hyper.py:211` | `class Guest` |
| `HyperChecks` | class | `tools/minios_hyper.py:409` | `class HyperChecks` |
| `HyperConfig` | class | `tools/minios_hyper.py:50` | `class HyperConfig` |
| `QmpChannel` | class | `tools/minios_hyper.py:96` | `class QmpChannel` |
| `RspCodec` | class | `tools/minios_hyper.py:73` | `class RspCodec` |
| `__init__` | method | `tools/minios_hyper.py:99` | `def __init__(self, path)` |
| `__init__` | method | `tools/minios_hyper.py:155` | `def __init__(self, port)` |
| `__init__` | method | `tools/minios_hyper.py:214` | `def __init__(self, with_gdb)` |
| `__init__` | method | `tools/minios_hyper.py:412` | `def __init__(self, guest)` |
| `_cmd` | method | `tools/minios_hyper.py:168` | `def _cmd(self, payload)` |
| `_drain` | method | `tools/minios_hyper.py:162` | `def _drain(self)` |
| `_last_frames` | method | `tools/minios_hyper.py:476` | `def _last_frames(self)` |
| `_reader` | method | `tools/minios_hyper.py:260` | `def _reader(self)` |
| `_roundtrip` | method | `tools/minios_hyper.py:109` | `def _roundtrip(self, obj)` |
| `_ser` | method | `tools/minios_hyper.py:248` | `def _ser(self)` |
| `check` | method | `tools/minios_hyper.py:495` | `def check(ok, msg)` |
| `close` | method | `tools/minios_hyper.py:145` | `def close(self)` |
| `close` | method | `tools/minios_hyper.py:204` | `def close(self)` |
| `cont` | method | `tools/minios_hyper.py:201` | `def cont(self)` |
| `count_cursors` | method | `tools/minios_hyper.py:394` | `def count_cursors(shot_path)` |
| `cursor_positions` | method | `tools/minios_hyper.py:356` | `def cursor_positions(shot_path)` |
| `decode` | method | `tools/minios_hyper.py:85` | `def decode(frame)` |
| `dump` | method | `tools/minios_hyper.py:308` | `def dump(self, name)` |
| `encode` | method | `tools/minios_hyper.py:77` | `def encode(payload)` |
| `gdb_chan` | method | `tools/minios_hyper.py:303` | `def gdb_chan(self)` |
| `gfx_frames` | method | `tools/minios_hyper.py:439` | `def gfx_frames(self)` |
| `halt` | method | `tools/minios_hyper.py:195` | `def halt(self)` |
| `key` | method | `tools/minios_hyper.py:132` | `def key(self, qcode)` |
| `main` | method | `tools/minios_hyper.py:591` | `def main(argv)` |
| `mean_diff` | method | `tools/minios_hyper.py:343` | `def mean_diff(a_path, b_path)` |
| `moved_cursors` | method | `tools/minios_hyper.py:399` | `def moved_cursors(before_path, after_path)` |
| `pixel_oob` | method | `tools/minios_hyper.py:452` | `def pixel_oob(self)` |
| `qmp_chan` | method | `tools/minios_hyper.py:298` | `def qmp_chan(self)` |
| `raw` | method | `tools/minios_hyper.py:117` | `def raw(self, obj)` |
| `read_mem` | method | `tools/minios_hyper.py:185` | `def read_mem(self, addr, length)` |
| `regs` | method | `tools/minios_hyper.py:181` | `def regs(self)` |
| `rel` | method | `tools/minios_hyper.py:126` | `def rel(self, dx, dy)` |
| `repl` | method | `tools/minios_hyper.py:561` | `def repl(guest)` |
| `run_boot` | method | `tools/minios_hyper.py:523` | `def run_boot(checks, extra_shell, interactive)` |
| `run_selftest` | method | `tools/minios_hyper.py:491` | `def run_selftest()` |
| `screendump` | method | `tools/minios_hyper.py:121` | `def screendump(self, path)` |
| `send` | method | `tools/minios_hyper.py:288` | `def send(self, line, settle)` |
| `snapshot` | method | `tools/minios_hyper.py:276` | `def snapshot(self)` |
| `status` | method | `tools/minios_hyper.py:141` | `def status(self)` |
| `stop` | method | `tools/minios_hyper.py:314` | `def stop(self)` |
| `sys_trace` | method | `tools/minios_hyper.py:465` | `def sys_trace(self)` |
| `vga_cursor` | method | `tools/minios_hyper.py:427` | `def vga_cursor(self)` |
| `vga_idle` | method | `tools/minios_hyper.py:415` | `def vga_idle(self)` |
| `wait_for` | method | `tools/minios_hyper.py:280` | `def wait_for(self, marker, timeout)` |
| `MiniFS` | class | `tools/mkfs.minifs.py:44` | `class MiniFS` |
| `__init__` | method | `tools/mkfs.minifs.py:45` | `def __init__(self, total_blocks)` |
| `add_dir_entry` | method | `tools/mkfs.minifs.py:136` | `def add_dir_entry(self, dir_ino, name, child_ino, ftype)` |
| `alloc_block` | method | `tools/mkfs.minifs.py:81` | `def alloc_block(self)` |
| `alloc_inode` | method | `tools/mkfs.minifs.py:75` | `def alloc_inode(self)` |
| `crc16` | function | `tools/mkfs.minifs.py:28` | `def crc16(data)` |
| `crc32` | function | `tools/mkfs.minifs.py:36` | `def crc32(data)` |
| `create_inode` | method | `tools/mkfs.minifs.py:95` | `def create_inode(self, mode)` |
| `create_root` | method | `tools/mkfs.minifs.py:87` | `def create_root(self)` |
| `div_round_up` | function | `tools/mkfs.minifs.py:25` | `def div_round_up(n, d)` |
| `inode_set_block` | method | `tools/mkfs.minifs.py:106` | `def inode_set_block(self, ino, logblk, phys)` |
| `inode_set_size` | method | `tools/mkfs.minifs.py:102` | `def inode_set_size(self, ino, size)` |
| `main` | method | `tools/mkfs.minifs.py:241` | `def main()` |
| `mark_blocks_used` | method | `tools/mkfs.minifs.py:71` | `def mark_blocks_used(self, start, count)` |
| `mark_inodes_used` | method | `tools/mkfs.minifs.py:67` | `def mark_inodes_used(self, start, count)` |
| `pack_tree` | method | `tools/mkfs.minifs.py:271` | `def pack_tree(parent_ino, path, rel)` |
| `roundup4` | function | `tools/mkfs.minifs.py:22` | `def roundup4(v)` |
| `serialize` | method | `tools/mkfs.minifs.py:197` | `def serialize(self)` |
| `write_dir` | method | `tools/mkfs.minifs.py:191` | `def write_dir(self, parent_ino, name)` |
| `write_file` | method | `tools/mkfs.minifs.py:174` | `def write_file(self, parent_ino, name, data)` |
| `main` | function | `tools/mkpak1.py:29` | `def main()` |
| `main` | function | `tools/mkramdisk.py:48` | `def main()` |
| `pack_name` | function | `tools/mkramdisk.py:38` | `def pack_name(path, common)` |
| `bytes_to_unicode` | function | `tools/mkvocab.py:18` | `def bytes_to_unicode()` |
| `main` | function | `tools/mkvocab.py:35` | `def main(encoder_path, vocab_path)` |
| `cleanup` | function | `tools/mutate.sh:134` | `` |
| `find_index` | function | `tools/mutate.sh:424` | `` |
| `record` | function | `tools/mutate.sh:418` | `` |
| `restore_sources` | function | `tools/mutate.sh:127` | `` |
| `usage` | function | `tools/mutate.sh:51` | `` |
| `dump` | function | `tools/probe_compute_vga.py:104` | `def dump(name)` |
| `main` | function | `tools/probe_compute_vga.py:22` | `def main()` |
| `poll` | function | `tools/probe_compute_vga.py:61` | `def poll(timeout)` |
| `qmp` | function | `tools/probe_compute_vga.py:88` | `def qmp(obj)` |
| `rel` | function | `tools/probe_compute_vga.py:97` | `def rel(dx, dy)` |
| `send` | function | `tools/probe_compute_vga.py:55` | `def send(line)` |
| `grab` | function | `tools/probe_minicraft.py:85` | `def grab(pat, timeout)` |
| `main` | function | `tools/probe_minicraft.py:34` | `def main()` |
| `poll` | function | `tools/probe_minicraft.py:74` | `def poll(timeout)` |
| `pos` | function | `tools/probe_minicraft.py:154` | `def pos(tag)` |
| `qkey` | function | `tools/probe_minicraft.py:143` | `def qkey(qcode, down)` |
| `send` | function | `tools/probe_minicraft.py:68` | `def send(line)` |
| `connect` | function | `tools/qga_client.py:57` | `def connect(path)` |
| `main` | function | `tools/qga_client.py:74` | `def main(argv)` |
| `read_reply` | function | `tools/qga_client.py:41` | `def read_reply(sock, timeout)` |
| `send_command` | function | `tools/qga_client.py:33` | `def send_command(sock, cmd, args)` |
| `check` | function | `tools/qga_test.sh:31` | `` |
| `cleanup` | function | `tools/qga_test.sh:25` | `` |
| `expect_in` | function | `tools/qga_test.sh:43` | `` |
| `QMP` | class | `tools/repro_gui.py:46` | `class QMP` |
| `__init__` | method | `tools/repro_gui.py:47` | `def __init__(self, path)` |
| `_recv` | method | `tools/repro_gui.py:63` | `def _recv(self)` |
| `cmd` | method | `tools/repro_gui.py:59` | `def cmd(self, obj)` |
| `key` | method | `tools/repro_gui.py:87` | `def key(self, qcode, down)` |
| `main` | method | `tools/repro_gui.py:92` | `def main()` |
| `mouse` | method | `tools/repro_gui.py:78` | `def mouse(self, dx, dy, left)` |
| `mouse_state` | method | `tools/repro_gui.py:118` | `def mouse_state()` |
| `read_serial` | function | `tools/repro_gui.py:30` | `def read_serial(master, timeout)` |
| `send` | method | `tools/repro_gui.py:113` | `def send(line)` |
| `cleanup_stale_qemu` | function | `tools/test_bdd.sh:43` | `` |
| `expect` | function | `tools/test_bdd.sh:97` | `` |
| `expect_count` | function | `tools/test_bdd.sh:119` | `` |
| `http_fixture_start` | function | `tools/test_bdd.sh:1292` | `` |
| `http_fixture_stop` | function | `tools/test_bdd.sh:1299` | `` |
| `http_server_start` | function | `tools/test_bdd.sh:1280` | `` |
| `http_server_stop` | function | `tools/test_bdd.sh:1287` | `` |
| `refute` | function | `tools/test_bdd.sh:142` | `` |
| `scenario` | function | `tools/test_bdd.sh:54` | `` |
| `scenario_smp` | function | `tools/test_bdd.sh:74` | `` |
| `scenario_uefi` | function | `tools/test_bdd.sh:167` | `` |
| `should_run` | function | `tools/test_bdd.sh:35` | `` |
| `AlignConfig` | class | `tools/test_call_align.py:24` | `class AlignConfig` |
| `find_minigcc` | method | `tools/test_call_align.py:59` | `def find_minigcc(explicit)` |
| `main` | method | `tools/test_call_align.py:79` | `def main(argv)` |
| `run` | method | `tools/test_call_align.py:74` | `def run(argv)` |
| `Guest` | class | `tools/test_gui_fashion.py:45` | `class Guest` |
| `__init__` | method | `tools/test_gui_fashion.py:46` | `def __init__(self)` |
| `_qmp` | method | `tools/test_gui_fashion.py:141` | `def _qmp(self, obj)` |
| `_reader` | method | `tools/test_gui_fashion.py:82` | `def _reader(self)` |
| `_ser` | method | `tools/test_gui_fashion.py:70` | `def _ser(self)` |
| `count_arrows` | method | `tools/test_gui_fashion.py:206` | `def count_arrows(shot_path)` |
| `dump` | method | `tools/test_gui_fashion.py:168` | `def dump(self, name)` |
| `key` | method | `tools/test_gui_fashion.py:149` | `def key(self, qcode, down, up)` |
| `main` | method | `tools/test_gui_fashion.py:239` | `def main()` |
| `meandiff` | method | `tools/test_gui_fashion.py:190` | `def meandiff(a_path, b_path)` |
| `note` | function | `tools/test_gui_fashion.py:39` | `def note(ok, msg)` |
| `qmp_cmd` | method | `tools/test_gui_fashion.py:128` | `def qmp_cmd(self, obj)` |
| `rel` | method | `tools/test_gui_fashion.py:161` | `def rel(self, dx, dy)` |
| `send` | method | `tools/test_gui_fashion.py:118` | `def send(self, line, settle)` |
| `snapshot` | method | `tools/test_gui_fashion.py:98` | `def snapshot(self)` |
| `stop` | method | `tools/test_gui_fashion.py:175` | `def stop(self)` |
| `wait_for` | method | `tools/test_gui_fashion.py:110` | `def wait_for(self, marker, timeout)` |
| `wait_prompt` | method | `tools/test_gui_fashion.py:102` | `def wait_prompt(self, timeout)` |
| `Config` | class | `tools/test_gui_freedom.py:36` | `class Config` |
| `Guest` | class | `tools/test_gui_freedom.py:73` | `class Guest` |
| `__init__` | method | `tools/test_gui_freedom.py:76` | `def __init__(self, work)` |
| `_connect` | method | `tools/test_gui_freedom.py:100` | `def _connect(self, path)` |
| `_qmp` | method | `tools/test_gui_freedom.py:155` | `def _qmp(self, obj)` |
| `_reader` | method | `tools/test_gui_freedom.py:114` | `def _reader(self)` |
| `_serial` | method | `tools/test_gui_freedom.py:109` | `def _serial(self)` |
| `button` | method | `tools/test_gui_freedom.py:182` | `def button(self, down)` |
| `chord` | method | `tools/test_gui_freedom.py:174` | `def chord(self, mod, qcode)` |
| `content_origin` | method | `tools/test_gui_freedom.py:221` | `def content_origin(listing)` |
| `dump` | method | `tools/test_gui_freedom.py:188` | `def dump(self, name)` |
| `keys` | method | `tools/test_gui_freedom.py:163` | `def keys(self, events)` |
| `main` | method | `tools/test_gui_freedom.py:247` | `def main()` |
| `move_to` | method | `tools/test_gui_freedom.py:235` | `def move_to(g, frame_size, target)` |
| `note` | method | `tools/test_gui_freedom.py:66` | `def note(ok, msg)` |
| `qmp_cmd` | method | `tools/test_gui_freedom.py:148` | `def qmp_cmd(self, obj)` |
| `region_diff` | method | `tools/test_gui_freedom.py:213` | `def region_diff(a_path, b_path, box)` |
| `rel` | method | `tools/test_gui_freedom.py:177` | `def rel(self, dx, dy)` |
| `screen_box` | method | `tools/test_gui_freedom.py:230` | `def screen_box(origin, box)` |
| `send` | method | `tools/test_gui_freedom.py:137` | `def send(self, line, settle)` |
| `snapshot` | method | `tools/test_gui_freedom.py:125` | `def snapshot(self)` |
| `stop` | method | `tools/test_gui_freedom.py:194` | `def stop(self)` |
| `tap` | method | `tools/test_gui_freedom.py:171` | `def tap(self, qcode)` |
| `wait_for` | method | `tools/test_gui_freedom.py:129` | `def wait_for(self, text, timeout)` |
| `Config` | class | `tools/test_gui_gfxview.py:39` | `class Config` |
| `dark_share` | method | `tools/test_gui_gfxview.py:84` | `def dark_share(img, box)` |
| `gfx_row` | method | `tools/test_gui_gfxview.py:72` | `def gfx_row(g)` |
| `last_line` | method | `tools/test_gui_gfxview.py:62` | `def last_line(g, prefix)` |
| `main` | method | `tools/test_gui_gfxview.py:109` | `def main()` |
| `note` | method | `tools/test_gui_gfxview.py:55` | `def note(ok, msg)` |
| `wait_frames` | method | `tools/test_gui_gfxview.py:94` | `def wait_frames(g, want)` |
| `Guest` | class | `tools/test_gui_icon_cwd.py:42` | `class Guest` |
| `__init__` | method | `tools/test_gui_icon_cwd.py:43` | `def __init__(self)` |
| `_qmp` | method | `tools/test_gui_icon_cwd.py:130` | `def _qmp(self, obj)` |
| `_reader` | method | `tools/test_gui_icon_cwd.py:79` | `def _reader(self)` |
| `_ser` | method | `tools/test_gui_icon_cwd.py:67` | `def _ser(self)` |
| `click` | method | `tools/test_gui_icon_cwd.py:145` | `def click(self)` |
| `dump` | method | `tools/test_gui_icon_cwd.py:155` | `def dump(self, name)` |
| `find_icon` | method | `tools/test_gui_icon_cwd.py:180` | `def find_icon(shot_path, icon_path)` |
| `main` | method | `tools/test_gui_icon_cwd.py:228` | `def main()` |
| `note` | function | `tools/test_gui_icon_cwd.py:36` | `def note(ok, msg)` |
| `qmp_cmd` | method | `tools/test_gui_icon_cwd.py:117` | `def qmp_cmd(self, obj)` |
| `rel` | method | `tools/test_gui_icon_cwd.py:138` | `def rel(self, dx, dy)` |
| `send` | method | `tools/test_gui_icon_cwd.py:107` | `def send(self, line, settle)` |
| `snapshot` | method | `tools/test_gui_icon_cwd.py:95` | `def snapshot(self)` |
| `stop` | method | `tools/test_gui_icon_cwd.py:162` | `def stop(self)` |
| `wait_prompt` | method | `tools/test_gui_icon_cwd.py:99` | `def wait_prompt(self, timeout)` |
| `walk` | method | `tools/test_gui_icon_cwd.py:213` | `def walk(g, tx, ty, fw, fh)` |
| `main` | function | `tools/test_gui_menu.py:20` | `def main()` |
| `Guest` | class | `tools/test_gui_wm.py:46` | `class Guest` |
| `__init__` | method | `tools/test_gui_wm.py:47` | `def __init__(self)` |
| `_qmp` | method | `tools/test_gui_wm.py:143` | `def _qmp(self, obj)` |
| `_reader` | method | `tools/test_gui_wm.py:87` | `def _reader(self)` |
| `_ser` | method | `tools/test_gui_wm.py:75` | `def _ser(self)` |
| `btn` | method | `tools/test_gui_wm.py:170` | `def btn(self, down)` |
| `dump` | method | `tools/test_gui_wm.py:176` | `def dump(self, name)` |
| `key` | method | `tools/test_gui_wm.py:151` | `def key(self, qcode, down, up)` |
| `main` | method | `tools/test_gui_wm.py:214` | `def main()` |
| `meandiff` | method | `tools/test_gui_wm.py:204` | `def meandiff(a_path, b_path)` |
| `note` | function | `tools/test_gui_wm.py:40` | `def note(ok, msg)` |
| `qmp_cmd` | method | `tools/test_gui_wm.py:130` | `def qmp_cmd(self, obj)` |
| `rel` | method | `tools/test_gui_wm.py:163` | `def rel(self, dx, dy)` |
| `send` | method | `tools/test_gui_wm.py:115` | `def send(self, line, settle)` |
| `snapshot` | method | `tools/test_gui_wm.py:103` | `def snapshot(self)` |
| `stop` | method | `tools/test_gui_wm.py:183` | `def stop(self)` |
| `wait_prompt` | method | `tools/test_gui_wm.py:107` | `def wait_prompt(self, timeout)` |
| `main` | function | `tools/test_gui_zoom.py:22` | `def main()` |
| `Handler` | class | `tools/test_http_server.py:21` | `class Handler(BaseHTTPRequestHandler)` |
| `do_GET` | method | `tools/test_http_server.py:24` | `def do_GET(self)` |
| `log_message` | method | `tools/test_http_server.py:114` | `def log_message(self, fmt)` |
| `LispConfig` | class | `tools/test_lisp.py:28` | `class LispConfig` |
| `LispTest` | class | `tools/test_lisp.py:37` | `class LispTest` |
| `__init__` | method | `tools/test_lisp.py:40` | `def __init__(self, binary, suite)` |
| `build_binary` | method | `tools/test_lisp.py:308` | `def build_binary(source, output)` |
| `check` | method | `tools/test_lisp.py:47` | `def check(self, name, actual, expected)` |
| `check_cli` | method | `tools/test_lisp.py:142` | `def check_cli(self)` |
| `check_error` | method | `tools/test_lisp.py:70` | `def check_error(self, name, code, fragment)` |
| `check_eval` | method | `tools/test_lisp.py:65` | `def check_eval(self, name, code, stdout)` |
| `check_exit_code` | method | `tools/test_lisp.py:135` | `def check_exit_code(self)` |

Next: [SYMBOLS_p25.md](SYMBOLS_p25.md)
