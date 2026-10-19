#!/usr/bin/env python3
"""test_mip.py -- host test for the frozen MicroPython installer (make test-mip).

Two layers:

1. Pure vectors: URL split, module-name validation, HTTP response
   parsing, redirect resolution and the write path, all loaded straight
   from progs/micropython/variants/minios/lib/mip.py under CPython (the
   module imports nothing at top level that the host lacks).

2. Live install: drives progs/bin/micropython.elf (a static Linux ELF,
   same artifact MiniOS runs) against a local http.server and asserts
   real files land on disk for plain fetch, redirect and the CLI, while
   https, chunked responses and traversal names are refused. Skipped
   until the ELF is rebuilt with MICROPY_PY_SOCKET=1.
"""

import importlib.util
import os
import subprocess
import tempfile
import threading
import unittest
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
MIP_PY = os.path.join(
    ROOT, "progs", "micropython", "variants", "minios", "lib", "mip.py"
)
MPY_ELF = os.path.join(ROOT, "progs", "bin", "micropython.elf")

HELLO = b"print('mip installed')\n"
RUN_TIMEOUT = 60


def load_mip():
    """Import lib/mip.py as a standalone module under CPython."""
    spec = importlib.util.spec_from_file_location("minios_mip_under_test", MIP_PY)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


class MipPureTests(unittest.TestCase):
    """Vectors for the pure helpers; no sockets, no subprocesses."""

    @classmethod
    def setUpClass(cls):
        cls.mip = load_mip()

    def test_split_url_default_port(self):
        self.assertEqual(
            self.mip.split_url("http://python.local/pkg.py"),
            ("python.local", 80, "/pkg.py"),
        )

    def test_split_url_explicit_port_and_query(self):
        self.assertEqual(
            self.mip.split_url("http://10.0.2.2:8899/a/b.py?x=1"),
            ("10.0.2.2", 8899, "/a/b.py?x=1"),
        )

    def test_split_url_path_defaults_to_root(self):
        self.assertEqual(self.mip.split_url("http://h"), ("h", 80, "/"))

    def test_split_url_refuses_https(self):
        with self.assertRaises(ValueError):
            self.mip.split_url("https://pypi.org/simple/x.py")

    def test_split_https_url_default_port(self):
        self.assertEqual(
            self.mip.split_https_url("https://python.local/pkg.py"),
            ("python.local", 443, "/pkg.py"),
        )

    def test_split_https_url_explicit_port(self):
        self.assertEqual(
            self.mip.split_https_url("https://host:8443/a.py"),
            ("host", 8443, "/a.py"),
        )

    def test_split_https_url_refuses_plain_http(self):
        with self.assertRaises(ValueError):
            self.mip.split_https_url("http://host/a.py")

    def test_parse_url_reports_scheme(self):
        self.assertEqual(
            self.mip.parse_url("http://h/a.py"), ("http", "h", 80, "/a.py")
        )
        self.assertEqual(
            self.mip.parse_url("https://h/a.py"), ("https", "h", 443, "/a.py")
        )
        with self.assertRaises(ValueError):
            self.mip.parse_url("ftp://h/a.py")

    def test_split_url_refuses_other_schemes(self):
        for url in ("ftp://h/x.py", "file:///x.py", "h/x.py", ""):
            with self.assertRaises(ValueError):
                self.mip.split_url(url)

    def test_split_url_refuses_bad_authority(self):
        for url in ("http://", "http://:80/x.py", "http://h:0/x.py",
                    "http://h:99999/x.py", "http://h:80x/x.py"):
            with self.assertRaises(ValueError):
                self.mip.split_url(url)

    def test_split_url_refuses_control_chars(self):
        for url in ("http://h/a b.py", "http://h/a\rb.py", "http://h/a\nb.py"):
            with self.assertRaises(ValueError):
                self.mip.split_url(url)

    def test_module_name_accepts_plain_module(self):
        self.assertEqual(self.mip.module_name("http://h/a/pkg.py"), "pkg.py")
        self.assertEqual(self.mip.module_name("https://h/a/pkg.py"), "pkg.py")

    def test_module_name_strips_query(self):
        self.assertEqual(self.mip.module_name("http://h/pkg.py?v=1"), "pkg.py")

    def test_module_name_refuses_unsafe_names(self):
        bad = (
            "http://h/../evil.py",
            "http://h/a/..%2Fevil.py",
            "http://h/sub/",           # directory, no .py
            "http://h/pkg.txt",
            "http://h/pkg.py.txt",
            "http://h/a-b.py",
            "http://h/1pkg.py",
            "http://h/.py",
            "http://h/",
        )
        for url in bad:
            with self.assertRaises(ValueError):
                self.mip.module_name(url)

    def test_parse_response_crlf(self):
        status, headers, body = self.mip.parse_response(
            b"HTTP/1.0 200 OK\r\nContent-Length: 2\r\nX-A: b\r\n\r\nhi"
        )
        self.assertEqual(status, 200)
        self.assertEqual(headers["content-length"], "2")
        self.assertEqual(headers["x-a"], "b")
        self.assertEqual(body, b"hi")

    def test_parse_response_bare_lf(self):
        status, headers, body = self.mip.parse_response(
            b"HTTP/1.0 404 Not Found\nContent-Length: 0\n\n"
        )
        self.assertEqual(status, 404)
        self.assertEqual(body, b"")

    def test_parse_response_rejects_garbage(self):
        for data in (b"", b"NOTHTTP", b"HTTP/1.0 xx OK\r\n\r\n",
                     b"HTTP/1.0 200 OK\r\nBad-Header\r\n\r\n"):
            with self.assertRaises(ValueError):
                self.mip.parse_response(data)

    def test_parse_response_rejects_content_length_mismatch(self):
        with self.assertRaises(ValueError):
            self.mip.parse_response(
                b"HTTP/1.0 200 OK\r\nContent-Length: 10\r\n\r\nshort"
            )
        with self.assertRaises(ValueError):
            self.mip.parse_response(
                b"HTTP/1.0 200 OK\r\nContent-Length: 1\r\n\r\nlong"
            )

    def test_parse_response_refuses_chunked(self):
        with self.assertRaises(ValueError):
            self.mip.parse_response(
                b"HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n0\r\n\r\n"
            )

    def test_https_get_needs_minios_on_host(self):
        with self.assertRaises(OSError):
            self.mip.https_get("host", 443, "/x.py")

    def test_absolute_url_resolves_path_location(self):
        self.assertEqual(
            self.mip.absolute_url("http://h:8899/a/b.py", "/c.py"),
            "http://h:8899/c.py",
        )
        self.assertEqual(
            self.mip.absolute_url("http://h/a/b.py", "/c.py"),
            "http://h/c.py",
        )

    def test_absolute_url_keeps_absolute_location(self):
        self.assertEqual(
            self.mip.absolute_url("http://h/a", "http://other/c.py"),
            "http://other/c.py",
        )
        self.assertEqual(
            self.mip.absolute_url("http://h/a", "https://other/c.py"),
            "https://other/c.py",
        )

    def test_absolute_url_keeps_base_scheme(self):
        self.assertEqual(
            self.mip.absolute_url("https://h/a.py", "/c.py"),
            "https://h/c.py",
        )
        self.assertEqual(
            self.mip.absolute_url("https://h:8443/a.py", "/c.py"),
            "https://h:8443/c.py",
        )

    def test_absolute_url_refuses_relative_location(self):
        with self.assertRaises(ValueError):
            self.mip.absolute_url("http://h/a/b.py", "c.py")


class _Handler(BaseHTTPRequestHandler):
    """Serve HELLO script plus redirect, chunked and 404 responses."""

    directory = None

    def log_message(self, fmt, *args):
        pass

    def do_GET(self):
        if self.path == "/hello_inst.py":
            self.send_response(200)
            self.send_header("Content-Length", str(len(HELLO)))
            self.end_headers()
            self.wfile.write(HELLO)
        elif self.path == "/redir.py":
            self.send_response(302)
            self.send_header("Location", "/hello_inst.py")
            self.end_headers()
        elif self.path == "/chunked.py":
            self.send_response(200)
            self.send_header("Transfer-Encoding", "chunked")
            self.end_headers()
            self.wfile.write(b"5\r\nhello\r\n0\r\n\r\n")
        else:
            self.send_response(404)
            self.send_header("Content-Length", "0")
            self.end_headers()


@unittest.skipUnless(os.path.exists(MPY_ELF), "micropython.elf not built")
class MipLiveTests(unittest.TestCase):
    """Install for real through the static MicroPython ELF on localhost."""

    @classmethod
    def setUpClass(cls):
        probe = subprocess.run(
            [MPY_ELF, "-c", "import socket"],
            capture_output=True, text=True, timeout=RUN_TIMEOUT,
        )
        if probe.returncode != 0:
            raise unittest.SkipTest(
                "micropython.elf predates MICROPY_PY_SOCKET=1; rebuild first"
            )
        cls.server = ThreadingHTTPServer(("127.0.0.1", 0), _Handler)
        cls.port = cls.server.server_address[1]
        cls.thread = threading.Thread(target=cls.server.serve_forever, daemon=True)
        cls.thread.start()

    @classmethod
    def tearDownClass(cls):
        cls.server.shutdown()
        cls.server.server_close()
        cls.thread.join(timeout=5)

    def setUp(self):
        self.workdir = tempfile.TemporaryDirectory(prefix="mip-")
        self.addCleanup(self.workdir.cleanup)

    def run_in_elf(self, code, *args):
        return subprocess.run(
            [MPY_ELF, "-c", code] + list(args),
            cwd=self.workdir.name, capture_output=True, text=True,
            timeout=RUN_TIMEOUT,
        )

    def combined(self, proc):
        return proc.stdout + proc.stderr

    def test_install_plain_and_load(self):
        proc = self.run_in_elf(
            "import mip\n"
            "print(mip.install('http://127.0.0.1:%d/hello_inst.py'))\n" % self.port
        )
        self.assertEqual(proc.returncode, 0, self.combined(proc))
        self.assertIn("lib/hello_inst.py", proc.stdout)
        with open(os.path.join(self.workdir.name, "lib", "hello_inst.py"), "rb") as fh:
            self.assertEqual(fh.read(), HELLO)

    def test_install_follows_redirect(self):
        proc = self.run_in_elf(
            "import mip\n"
            "print(mip.install('http://127.0.0.1:%d/redir.py'))\n" % self.port
        )
        self.assertEqual(proc.returncode, 0, self.combined(proc))
        self.assertTrue(
            os.path.exists(os.path.join(self.workdir.name, "lib", "hello_inst.py"))
        )

    def test_install_404_fails(self):
        proc = self.run_in_elf(
            "import mip\n"
            "mip.install('http://127.0.0.1:%d/missing.py')\n" % self.port
        )
        self.assertNotEqual(proc.returncode, 0)
        self.assertIn("404", self.combined(proc))

    def test_install_https_needs_minios(self):
        # On a host kernel the minios module is present in the ELF but
        # SYS_SPAWN is ENOSYS, so the https shim (bin/tlsget) must fail
        # closed naming tlsget; the in-OS live proof covers the working
        # path.
        proc = self.run_in_elf(
            "import mip\nmip.install('https://example.com/pkg.py')\n"
        )
        self.assertNotEqual(proc.returncode, 0)
        self.assertIn("tlsget", self.combined(proc).lower())

    def test_install_refuses_chunked(self):
        proc = self.run_in_elf(
            "import mip\n"
            "mip.install('http://127.0.0.1:%d/chunked.py')\n" % self.port
        )
        self.assertNotEqual(proc.returncode, 0)
        self.assertIn("chunked", self.combined(proc).lower())

    def test_install_refuses_traversal_name(self):
        proc = self.run_in_elf(
            "import mip\n"
            "mip.install('http://127.0.0.1:%d/..%%2Fevil.py')\n" % self.port
        )
        self.assertNotEqual(proc.returncode, 0)

    def test_install_twice_succeeds(self):
        proc = self.run_in_elf(
            "import mip\n"
            "a = mip.install('http://127.0.0.1:%d/hello_inst.py')\n"
            "b = mip.install('http://127.0.0.1:%d/hello_inst.py')\n"
            "print('twice', a, b)\n" % (self.port, self.port)
        )
        self.assertEqual(proc.returncode, 0, self.combined(proc))
        self.assertIn("twice", proc.stdout)

    def test_cli_install(self):
        proc = self.run_in_elf(
            "import mip\nraise SystemExit(mip.main())\n",
            "install", "http://127.0.0.1:%d/hello_inst.py" % self.port,
        )
        self.assertEqual(proc.returncode, 0, self.combined(proc))
        self.assertIn("installed", proc.stdout)
        self.assertTrue(
            os.path.exists(os.path.join(self.workdir.name, "lib", "hello_inst.py"))
        )


if __name__ == "__main__":
    unittest.main(verbosity=2)
