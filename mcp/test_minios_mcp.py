"""Unit and BDD suite for the MiniOS MCP bridge.

Unit tests exercise protocol dispatch, input validation and buffer/cursor
semantics without QEMU. BDD scenarios boot the real os.img and drive the
edit/compile/link/run loop over JSON-RPC; they skip when QEMU or the image
is absent.

Environment overrides: MINIOS_MCP (server path), MINIOS_IMAGE, QEMU,
MINIOS_SKIP_BDD=1 forces the QEMU scenarios to skip.
"""

import importlib.util
import json
import os
import select
import subprocess
import sys
import tempfile
import unittest

HERE = os.path.dirname(os.path.abspath(__file__))
MCP_PATH = os.environ.get("MINIOS_MCP", os.path.join(HERE, "minios_mcp.py"))
ROOT = os.path.dirname(HERE)
IMAGE = os.environ.get("MINIOS_IMAGE", os.path.join(ROOT, "os.img"))
QEMU = os.environ.get("QEMU", "qemu-system-x86_64")
TMO = float(os.environ.get("MINIOS_TEST_TMO", "180"))


def load_module():
    spec = importlib.util.spec_from_file_location("minios_mcp", MCP_PATH)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module

EXPECTED_TOOLS = [
    "minios_status",
    "minios_boot",
    "minios_snapshot",
    "minios_send",
    "minios_expect",
    "minios_write",
    "minios_cat",
    "minios_addons",
    "minios_install",
    "minios_poweroff",
]


def have_qemu():
    import shutil

    return bool(shutil.which(QEMU)) and os.path.isfile(IMAGE) and os.environ.get("MINIOS_SKIP_BDD") != "1"


class MCPServer:
    """Child process running minios_mcp.py, driven over stdio JSON-RPC."""

    def __init__(self, env_extra=None):
        env = dict(os.environ)
        env["MINIOS_IMAGE"] = IMAGE
        self._tmp = tempfile.mkdtemp(prefix="minios_mcp_test.")
        env["TMPDIR"] = self._tmp
        if env_extra:
            env.update(env_extra)
        self.proc = subprocess.Popen(
            [sys.executable, MCP_PATH],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            env=env,
            text=True,
            bufsize=1,
        )
        self.next_id = 1
        self.initialize()

    def initialize(self):
        r = self.request("initialize", {"protocolVersion": "2024-11-05"})
        return r

    def request(self, method, params=None):
        msg = {"jsonrpc": "2.0", "id": self.next_id, "method": method}
        if params is not None:
            msg["params"] = params
        self.next_id += 1
        return self._roundtrip(msg)

    def raw(self, line):
        self.proc.stdin.write(line + "\n")
        self.proc.stdin.flush()
        return self._read_response()

    def _read_response(self):
        rlist, _, _ = select.select([self.proc.stdout], [], [], TMO)
        if not rlist:
            raise TimeoutError("server produced no response")
        return json.loads(self.proc.stdout.readline())

    def _roundtrip(self, msg):
        self.proc.stdin.write(json.dumps(msg) + "\n")
        self.proc.stdin.flush()
        resp = self._read_response()
        if resp.get("id") != msg.get("id"):
            raise AssertionError("response id mismatch: %r" % resp)
        return resp

    def tool(self, name, params=None):
        r = self.request("tools/call", {"name": name, "arguments": params or {}})
        if "error" in r:
            raise AssertionError("rpc error: %r" % r)
        res = r["result"]
        text = res.get("content", [{}])[0].get("text", "")
        if res.get("isError"):
            raise AssertionError("tool error: %s" % text)
        return json.loads(text)

    def close(self):
        try:
            if self.proc.poll() is None:
                self.proc.stdin.close()
                self.proc.terminate()
                try:
                    self.proc.wait(timeout=10)
                except subprocess.TimeoutExpired:
                    self.proc.kill()
                    self.proc.wait(timeout=10)
            for pipe in (self.proc.stdin, self.proc.stdout, self.proc.stderr):
                try:
                    pipe.close()
                except Exception:
                    pass
        finally:
            import shutil

            shutil.rmtree(self._tmp, ignore_errors=True)


class TestProtocol(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        if not os.path.isfile(MCP_PATH):
            raise unittest.SkipTest("minios_mcp.py not found")
        cls.server = MCPServer()

    @classmethod
    def tearDownClass(cls):
        cls.server.close()

    def test_initialize(self):
        r = self.server.initialize()
        self.assertEqual(r["result"]["protocolVersion"], "2024-11-05")
        self.assertEqual(r["result"]["serverInfo"]["name"], "minios-mcp")
        self.assertIn("tools", r["result"]["capabilities"])

    def test_tools_list(self):
        r = self.server.request("tools/list")
        names = [t["name"] for t in r["result"]["tools"]]
        self.assertEqual(sorted(names), sorted(EXPECTED_TOOLS))
        for t in r["result"]["tools"]:
            self.assertIn("inputSchema", t)
            self.assertIn("type", t["inputSchema"])

    def test_ping(self):
        r = self.server.request("ping")
        self.assertEqual(r["result"], {})

    def test_unknown_method(self):
        r = self.server.request("no_such_method")
        self.assertEqual(r["error"]["code"], -32601)

    def test_malformed_json(self):
        r = self.server.raw("this is not json")
        self.assertEqual(r["error"]["code"], -32700)

    def test_unknown_tool(self):
        r = self.server.request("tools/call", {"name": "minios_nope", "arguments": {}})
        self.assertIn("error", r)
        self.assertEqual(r["error"]["code"], -32602)

    def test_send_not_booted(self):
        r = self.server.request("tools/call", {"name": "minios_send", "arguments": {"line": "ls"}})
        res = r["result"]
        self.assertTrue(res["isError"])
        self.assertIn("not booted", res["content"][0]["text"])

    def test_send_empty_line_rejected(self):
        r = self.server.request("tools/call", {"name": "minios_send", "arguments": {"line": ""}})
        res = r["result"]
        self.assertTrue(res["isError"])
        self.assertIn("line", res["content"][0]["text"])


class TestValidation(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        if not os.path.isfile(MCP_PATH):
            raise unittest.SkipTest("minios_mcp.py not found")
        cls.m = load_module()

    def test_path_accepts_plain_names(self):
        for ok in ["p.c", "t.s", "a/b.c", "x.elf", "hello.txt"]:
            self.assertIsNone(self.m.validate_path(ok), ok)

    def test_path_rejects_unsafe(self):
        for bad in ["../x", "a/../b", "/abs", "a b", "a\nb", "a\tb", ""]:
            self.assertIsNotNone(self.m.validate_path(bad), bad)

    def test_path_rejects_long(self):
        self.assertIsNotNone(self.m.validate_path("x" * 40 + ".c"))

    def test_content_accepts_ascii(self):
        self.assertIsNone(self.m.validate_content("int main(void) { return 7; }\n"))

    def test_content_rejects_non_printable(self):
        for bad in ["tab\there", "ctrl\x01", "unicode \u00e9", "cr\r"]:
            self.assertIsNotNone(self.m.validate_content(bad), repr(bad))

    def test_timeout_clamped(self):
        self.assertEqual(self.m.clamp_timeout(0), self.m.CFG_TMO_MIN)
        self.assertEqual(self.m.clamp_timeout(10 ** 9), self.m.CFG_TMO_MAX)

    def test_write_rejects_line_too_long(self):
        server = MCPServer()
        try:
            r = server.request("tools/call", {"name": "minios_write", "arguments": {"path": "x.c", "content": "a" * 128}})
            self.assertTrue(r["result"]["isError"])
            self.assertIn("line too long", r["result"]["content"][0]["text"])
        finally:
            server.close()

    def test_write_rejects_too_many_lines(self):
        server = MCPServer()
        try:
            content = "\n".join(["x"] * 513)
            r = server.request("tools/call", {"name": "minios_write", "arguments": {"path": "x.c", "content": content}})
            self.assertTrue(r["result"]["isError"])
            self.assertIn("editor maximum", r["result"]["content"][0]["text"])
        finally:
            server.close()


class TestLogBuffer(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        if not os.path.isfile(MCP_PATH):
            raise unittest.SkipTest("minios_mcp.py not found")
        cls.m = load_module()

    def test_bounds(self):
        buf = self.m.LogBuffer(100)
        buf.append(b"a" * 150)
        self.assertEqual(buf.total, 150)
        self.assertEqual(len(buf.bytes_from(0)), 100)
        self.assertEqual(buf.bytes_from(0), b"a" * 100)

    def test_find_and_total(self):
        buf = self.m.LogBuffer(64)
        buf.append(b"boot ok\nprompt> ")
        self.assertGreaterEqual(buf.find(b"boot ok", 0), 0)
        self.assertEqual(buf.find(b"missing", 0), -1)
        self.assertEqual(buf.total, 16)

    def test_cursor_prevents_stale_match(self):
        buf = self.m.LogBuffer(64)
        buf.append(b"exit code: 7\n")
        pos = buf.find(b"exit code: 7", 0)
        self.assertGreaterEqual(pos, 0)
        buf.append(b"exit code: 8\n")
        second = buf.find(b"exit code: 7", pos + len(b"exit code: 7"))
        self.assertEqual(second, -1)


@unittest.skipUnless(have_qemu(), "QEMU or os.img not available")
class _ConsoleBDDBase(unittest.TestCase):
    """Fail-fast for QEMU-backed classes: once a tool call has hit a
    console wait timeout the bridge is stuck (a mutated marker, a hung
    shell) and every remaining test would only burn its own timeout, so
    they are skipped instead."""

    unhealthy = False

    @classmethod
    def guard_server(cls):
        orig = cls.server.tool

        def guarded(name, params=None):
            try:
                return orig(name, params)
            except AssertionError as exc:
                msg = str(exc)
                if (
                    "timed out" in msg
                    or "(timeout)" in msg
                    or "did not open" in msg
                    or "did not return" in msg
                    or "did not exit" in msg
                    or "not booted" in msg
                ):
                    cls.unhealthy = True
                raise

        cls.server.tool = guarded

    def setUp(self):
        if type(self).unhealthy:
            self.skipTest("bridge unhealthy after a console wait timeout")


@unittest.skipUnless(have_qemu(), "QEMU or os.img not available")
class TestMiniOSBDD(_ConsoleBDDBase):
    @classmethod
    def setUpClass(cls):
        if not os.path.isfile(MCP_PATH):
            raise unittest.SkipTest("minios_mcp.py not found")
        cls.server = MCPServer()
        cls.guard_server()

    @classmethod
    def tearDownClass(cls):
        if getattr(cls, "server", None):
            cls.server.close()

    def test_t01_boot(self):
        r = self.server.tool("minios_boot")
        self.assertTrue(r["booted"])
        self.assertIn("MiniOS Kernel", r["log"])
        s = self.server.tool("minios_status")
        self.assertTrue(s["booted"])
        self.assertGreater(s["log_bytes"], 0)
        snap = self.server.tool("minios_snapshot")
        self.assertIn("miniOS> ", snap["text"])

    def test_t02_expect(self):
        r = self.server.tool("minios_expect", {"marker": "miniOS> "})
        self.assertTrue(r["matched"])
        self.assertIn("miniOS> ", r["text"])
        r = self.server.tool("minios_expect", {"marker": "MiniOS Kernel", "timeout_ms": 3000})
        self.assertFalse(r["matched"])

    def test_t03_write_and_cat(self):
        r = self.server.tool(
            "minios_write",
            {"path": "hello.txt", "content": "hello from mcp\nsecond line\n"},
        )
        self.assertIn("wrote 2 line(s)", r["transcript"])
        c = self.server.tool("minios_cat", {"path": "hello.txt"})
        self.assertIn("hello from mcp", c["text"])
        self.assertIn("second line", c["text"])

    def test_t04_toolchain_elf(self):
        self.server.tool(
            "minios_write",
            {"path": "p.c", "content": "int main(void) { return 7; }\n"},
        )
        r = self.server.tool("minios_send", {"line": "run minigcc.o p.c > p.s"})
        self.assertIn("miniOS> ", r["text"])
        r = self.server.tool("minios_send", {"line": "run ld.o -f elf -o p.elf p.s"})
        r = self.server.tool("minios_send", {"line": "run p.elf"})
        self.assertIn("exit code: 7", r["text"])

    def test_t05_toolchain_cvm(self):
        self.server.tool(
            "minios_write",
            {"path": "q.c", "content": "int main(void) { return 21; }\n"},
        )
        self.server.tool("minios_send", {"line": "run minigcc.o q.c > q.s"})
        self.server.tool("minios_send", {"line": "run ld.o -f cvm -o q.cvm q.s"})
        r = self.server.tool("minios_send", {"line": "run q.cvm"})
        self.assertIn("exit code: 21", r["text"])

    def test_t06_selfhosted_compiler(self):
        self.server.tool("minios_send", {"line": "run minigcc.elf test.c > t.s", "timeout_ms": 60000})
        self.server.tool("minios_send", {"line": "run ld.o -f elf -o t.elf t.s"})
        r = self.server.tool("minios_send", {"line": "run t.elf"})
        self.assertIn("exit code: 12", r["text"])

    def test_t07_bin_command_path(self):
        r = self.server.tool("minios_send", {"line": "cp bin/cp.c bk.c"})
        self.assertIn("exit code: 0", r["text"])
        r = self.server.tool("minios_send", {"line": "cat bk.c"})
        self.assertIn("usage: cp", r["text"])
        r = self.server.tool("minios_send", {"line": "cp missing.txt z.txt"})
        self.assertIn("exit code: 1", r["text"])

    def test_t08_poweroff_and_reboot(self):
        r = self.server.tool("minios_poweroff")
        self.assertIn("powering off", r["text"])
        s = self.server.tool("minios_status")
        self.assertFalse(s["booted"])
        r = self.server.tool("minios_boot")
        self.assertTrue(r["booted"])


VALID_ADDON = """name: cp
description: Command-path utility cp.
author: miniOS
version: "1.0.0"
install:
  repo_url: https://github.com/grisuno/miniOS.git
  files:
    - src: progs/bin/cp.c
      dst: build/cp.c
  build:
    - run minigcc.o build/cp.c > build/cp.s
    - run ld.o -f elf -o bin/cp build/cp.s
  verify:
    - line: cp bin/cp.c build/cp2.c
      exit_code: 0
"""


class TestAddonYaml(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        if not os.path.isfile(MCP_PATH):
            raise unittest.SkipTest("minios_mcp.py not found")
        import importlib.util as iu

        path = os.path.join(os.path.dirname(MCP_PATH), "minios_addons.py")
        spec = iu.spec_from_file_location("minios_addons", path)
        cls.ma = iu.module_from_spec(spec)
        spec.loader.exec_module(cls.ma)

    def test_parse_valid(self):
        addon = self.ma.parse_addon_yaml(VALID_ADDON)
        self.assertEqual(addon["name"], "cp")
        self.assertEqual(addon["install"]["repo_url"], "https://github.com/grisuno/miniOS.git")
        files = addon["install"]["files"]
        self.assertEqual(files, [{"src": "progs/bin/cp.c", "dst": "build/cp.c"}])
        self.assertEqual(len(addon["install"]["build"]), 2)
        verify = addon["install"]["verify"]
        self.assertEqual(verify, [{"line": "cp bin/cp.c build/cp2.c", "exit_code": "0"}])

    def test_validate_accepts_valid(self):
        addon = self.ma.validate_addon(self.ma.parse_addon_yaml(VALID_ADDON), "cp.yaml")
        self.assertEqual(addon["install"]["verify"][0]["exit_code"], 0)

    def test_unknown_key_rejected(self):
        with self.assertRaises(self.ma.AddonError):
            self.ma.parse_addon_yaml("name: x\nbogus: 1\ninstall:\n  repo_url: r\n  files:\n    - src: a.c\n      dst: b.c\n")

    def test_bad_indent_rejected(self):
        with self.assertRaises(self.ma.AddonError):
            self.ma.parse_addon_yaml("name: x\ninstall:\n   repo_url: r\n  files: []\n")

    def test_validate_rejects_bad_dst(self):
        bad = VALID_ADDON.replace("dst: build/cp.c", "dst: ../x")
        with self.assertRaises(self.ma.AddonError):
            self.ma.validate_addon(self.ma.parse_addon_yaml(bad), "cp.yaml")

    def test_validate_rejects_missing_name(self):
        with self.assertRaises(self.ma.AddonError):
            self.ma.validate_addon(self.ma.parse_addon_yaml("description: d\ninstall:\n  repo_url: r\n  files: []\n"), "x.yaml")

    def test_validate_rejects_long_build_line(self):
        bad = VALID_ADDON.replace(
            "- run minigcc.o build/cp.c > build/cp.s",
            "- run " + "x" * 300,
        )
        with self.assertRaises(self.ma.AddonError):
            self.ma.validate_addon(self.ma.parse_addon_yaml(bad), "cp.yaml")

    def test_validate_rejects_control_chars(self):
        bad = VALID_ADDON.replace("exit_code: 0", "exit_code: 1\texit")
        with self.assertRaises(self.ma.AddonError):
            self.ma.validate_addon(self.ma.parse_addon_yaml(bad), "cp.yaml")

    def test_validate_rejects_empty_files(self):
        bad = VALID_ADDON.replace("  files:\n    - src: progs/bin/cp.c\n      dst: build/cp.c\n", "  files: []\n")
        with self.assertRaises(self.ma.AddonError):
            self.ma.validate_addon(self.ma.parse_addon_yaml(bad), "cp.yaml")


class TestAddonHelpers(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        if not os.path.isfile(MCP_PATH):
            raise unittest.SkipTest("minios_mcp.py not found")
        import importlib.util as iu

        path = os.path.join(os.path.dirname(MCP_PATH), "minios_addons.py")
        spec = iu.spec_from_file_location("minios_addons", path)
        cls.ma = iu.module_from_spec(spec)
        spec.loader.exec_module(cls.ma)

    def test_split_for_editor_chunks(self):
        text = "".join("line %d\n" % i for i in range(600))
        chunks = self.ma.split_for_editor(text)
        self.assertEqual(len(chunks), 2)
        self.assertLessEqual(len(chunks[0].split("\n")) - 1, self.ma.ADDON_CHUNK_LINES)
        self.assertEqual("".join(chunks), text)

    def test_split_rejects_long_line(self):
        with self.assertRaises(self.ma.AddonError):
            self.ma.split_for_editor("x" * 128 + "\n")

    def test_split_rejects_non_ascii(self):
        with self.assertRaises(self.ma.AddonError):
            self.ma.split_for_editor("hola \u00e9\n")

    def test_exit_code_of(self):
        self.assertEqual(self.ma.exit_code_of("foo\nexit code: 42\n"), 42)
        self.assertEqual(self.ma.exit_code_of("foo\nexit code: -1\n"), -1)
        self.assertIsNone(self.ma.exit_code_of("no code here"))

    def test_state_roundtrip(self):
        path = os.path.join(tempfile.mkdtemp(prefix="minios_state."), "state.json")
        state = self.ma.AddonState(path)
        self.assertEqual(state.load(), {})
        state.save({"cp": {"version": "1.0.0", "installed_at": 1}})
        self.assertEqual(state.load()["cp"]["version"], "1.0.0")


class FakeOS:
    """In-memory stand-in for the MiniOS session (no QEMU)."""

    def __init__(self, exit_codes=None):
        self.files = {}
        self.commands = []
        self.exit_codes = exit_codes or {}
        self.booted_flag = True
        self.removed = []

    def booted(self):
        return self.booted_flag

    def boot(self, timeout_ms=None):
        self.booted_flag = True
        return {"booted": True, "log": ""}

    def write(self, path, content):
        lines = content.split("\n")
        if lines and lines[-1] == "":
            lines.pop()
        self.files[path] = "\n".join(lines)
        return {"transcript": "ok"}

    def send(self, line, timeout_ms=None):
        self.commands.append(line)
        for sep in (">>", ">"):
            if (" " + sep + " ") in line:
                cmd, _, dst = line.partition(" " + sep + " ")
                if cmd.startswith("cat "):
                    data = "".join(self.files.get(s, "") for s in cmd[4:].split()) + "\n"
                elif cmd.startswith("echo"):
                    data = "\n"
                else:
                    data = ""
                if sep == ">>":
                    self.files[dst] = self.files.get(dst, "") + data
                else:
                    self.files[dst] = data
                return {"text": "exit code: 0\n"}
        if line.startswith("rm "):
            path = line[3:]
            self.files.pop(path, None)
            self.removed.append(path)
            return {"text": "removed %s\n" % path}
        code = self.exit_codes.get(line, 0)
        return {"text": "output\nexit code: %d\n" % code}

    def cat_body(self, path, missing_ok=False):
        if path not in self.files:
            if missing_ok:
                return ""
            raise self._toolerror("no such file")
        return self.files[path]

    class _toolerror(Exception):
        pass

    ToolError = _toolerror

    def _cleanup_parts(self, parts):
        for part in parts:
            self.files.pop(part, None)
            self.removed.append(part)


class TestAddonInstall(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        if not os.path.isfile(MCP_PATH):
            raise unittest.SkipTest("minios_mcp.py not found")
        import importlib.util as iu

        path = os.path.join(os.path.dirname(MCP_PATH), "minios_addons.py")
        spec = iu.spec_from_file_location("minios_addons", path)
        cls.ma = iu.module_from_spec(spec)
        spec.loader.exec_module(cls.ma)
        cls.repo = tempfile.mkdtemp(prefix="minios_fixrepo.")
        with open(os.path.join(cls.repo, "src.c"), "w") as f:
            f.write("int main(void) { return 42; }\n")
        subprocess.run(["git", "init", "-q", cls.repo], check=True)
        subprocess.run(["git", "-C", cls.repo, "add", "src.c"], check=True)
        subprocess.run(
            [
                "git",
                "-C",
                cls.repo,
                "-c",
                "user.email=t@t.t",
                "-c",
                "user.name=t",
                "commit",
                "-q",
                "-m",
                "init",
            ],
            check=True,
        )

    @classmethod
    def tearDownClass(cls):
        import shutil

        shutil.rmtree(cls.repo, ignore_errors=True)

    def make_addon(self):
        return self.ma.validate_addon(
            self.ma.parse_addon_yaml(
                """name: fixture-addon
description: test addon
author: test
version: "1.0.0"
install:
  repo_url: %s
  files:
    - src: src.c
      dst: build/src.c
  build:
    - run minigcc.o build/src.c > build/src.s
  verify:
    - line: run build/fixture
      exit_code: 42
""" % self.repo
            ),
            "fixture.yaml",
        )

    def test_install_success(self):
        os_session = FakeOS(exit_codes={"run build/fixture": 42})
        state_file = os.path.join(tempfile.mkdtemp(prefix="minios_astate."), "state.json")
        result = self.ma.install_addon(os_session, self.make_addon(), {"state_file": state_file})
        self.assertEqual(result["name"], "fixture-addon")
        self.assertEqual(os_session.files["build/src.c"].rstrip("\n"), "int main(void) { return 42; }")
        self.assertIn("run minigcc.o build/src.c > build/src.s", os_session.commands)
        registry = os_session.files[self.ma.ADDON_REGISTRY_PATH]
        self.assertIn("fixture-addon 1.0.0", registry)
        self.assertEqual(os_session.files.keys() & {"build/src.c.part0"}, set())
        state = self.ma.AddonState(state_file).load()
        self.assertIn("fixture-addon", state)

    def test_install_mismatch_aborts_and_cleans(self):
        os_session = FakeOS()
        os_session.files["build/src.c"] = "corrupted\n"

        def broken_cat(path, missing_ok=False):
            return "corrupted\n"

        os_session.cat_body = broken_cat
        with self.assertRaises(self.ma.AddonError):
            self.ma.install_addon(
                os_session, self.make_addon(), {"state_file": os.path.join(tempfile.mkdtemp(), "s.json")}
            )
        self.assertNotIn("build/src.c.part0", os_session.files)

    def test_install_multi_chunk_reassembly(self):
        big = "".join("int line_%d(void) { return %d; }\n" % (i, i % 10) for i in range(600))
        with open(os.path.join(self.repo, "big.c"), "w") as f:
            f.write(big)
        subprocess.run(["git", "-C", self.repo, "add", "big.c"], check=True)
        subprocess.run(
            ["git", "-C", self.repo, "-c", "user.email=t@t.t", "-c", "user.name=t", "commit", "-q", "-m", "big"],
            check=True,
        )
        addon = self.ma.validate_addon(
            self.ma.parse_addon_yaml(
                """name: fixture-addon
description: test addon
author: test
version: "1.0.0"
install:
  repo_url: %s
  files:
    - src: big.c
      dst: build/big.c
  build: []
  verify: []
"""
                % self.repo
            ),
            "fixture.yaml",
        )
        os_session = FakeOS()
        self.ma.install_addon(os_session, addon, {"state_file": os.path.join(tempfile.mkdtemp(), "s.json")})
        self.assertEqual(os_session.files["build/big.c"], big)

    def test_install_verify_failure_aborts(self):
        os_session = FakeOS(exit_codes={"run build/fixture": 1})
        state_file = os.path.join(tempfile.mkdtemp(prefix="minios_astate."), "state.json")
        with self.assertRaises(self.ma.AddonError):
            self.ma.install_addon(os_session, self.make_addon(), {"state_file": state_file})
        self.assertEqual(self.ma.AddonState(state_file).load(), {})

    def test_install_build_failure_aborts(self):
        os_session = FakeOS(exit_codes={"run minigcc.o build/src.c > build/src.s": 5})
        state_file = os.path.join(tempfile.mkdtemp(prefix="minios_astate."), "state.json")
        with self.assertRaises(self.ma.AddonError):
            self.ma.install_addon(os_session, self.make_addon(), {"state_file": state_file})
        self.assertEqual(self.ma.AddonState(state_file).load(), {})


@unittest.skipUnless(have_qemu(), "QEMU or os.img not available")
class TestAddonBDD(_ConsoleBDDBase):
    """Install a fixture addon from a local git repo into the real OS."""

    @classmethod
    def setUpClass(cls):
        if not os.path.isfile(MCP_PATH):
            raise unittest.SkipTest("minios_mcp.py not found")
        cls.repo = tempfile.mkdtemp(prefix="minios_fixrepo.")
        with open(os.path.join(cls.repo, "src.c"), "w") as f:
            f.write("int main(void) { return 42; }\n")
        subprocess.run(["git", "init", "-q", cls.repo], check=True)
        subprocess.run(["git", "-C", cls.repo, "add", "src.c"], check=True)
        subprocess.run(
            ["git", "-C", cls.repo, "-c", "user.email=t@t.t", "-c", "user.name=t", "commit", "-q", "-m", "init"],
            check=True,
        )
        cls.addons_dir = tempfile.mkdtemp(prefix="minios_addons.")
        with open(os.path.join(cls.addons_dir, "fixture.yaml"), "w") as f:
            f.write(
                """name: fixture-addon
description: bdd fixture addon
author: test
version: "1.0.0"
install:
  repo_url: %s
  files:
    - src: src.c
      dst: build/src.c
  build:
    - run minigcc.o build/src.c > build/src.s
    - run ld.o -f elf -o build/fixture build/src.s
  verify:
    - line: run build/fixture
      exit_code: 42
"""
                % cls.repo
            )
        cls.server = MCPServer({"MINIOS_ADDONS_DIR": cls.addons_dir})
        cls.guard_server()

    @classmethod
    def tearDownClass(cls):
        if getattr(cls, "server", None):
            cls.server.close()
        import shutil

        shutil.rmtree(cls.repo, ignore_errors=True)
        shutil.rmtree(cls.addons_dir, ignore_errors=True)

    def test_addons_list(self):
        r = self.server.tool("minios_addons")
        names = [a["name"] for a in r["addons"]]
        self.assertIn("fixture-addon", names)
        self.assertFalse(r["addons"][0]["installed"])

    def test_install_fixture(self):
        r = self.server.tool("minios_install", {"name": "fixture-addon", "timeout_ms": 120000})
        self.assertEqual(r["name"], "fixture-addon")
        self.assertIn("build/src.c", r["files"])
        r = self.server.tool("minios_addons")
        self.assertTrue(r["addons"][0]["installed"])
        c = self.server.tool("minios_send", {"line": "cat var/lib/addons.txt"})
        self.assertIn("fixture-addon 1.0.0", c["text"])

    def test_install_unknown_addon_fails(self):
        r = self.server.request("tools/call", {"name": "minios_install", "arguments": {"name": "no-such"}})
        self.assertTrue(r["result"]["isError"])
        self.assertIn("no such addon", r["result"]["content"][0]["text"])


if __name__ == "__main__":
    unittest.main(verbosity=2)
