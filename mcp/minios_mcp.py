"""MiniOS MCP bridge.

Exposes a running MiniOS instance as tools over the MCP stdio protocol.
The server boots os.img in QEMU, owns a pty-backed serial console, and
lets a client write, compile, link and run software inside the OS.

Python 3 standard library only. One QEMU child per server, terminated on
every exit path. The host shell is never invoked.
"""

import atexit
import json
import os
import signal
import sys
import tempfile
import threading
import time
import tty

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import minios_addons  # noqa: E402

CFG_SERVER_NAME = "minios-mcp"
CFG_SERVER_VERSION = "1.0.0"
CFG_PROTOCOL_VERSION = "2024-11-05"

CFG_PROMPT_SHELL = "miniOS> "
CFG_PROMPT_EDITOR = "edit> "
CFG_MARK_POWEROFF = "powering off"
CFG_MARK_BOOT = "MiniOS Kernel"

CFG_EDITOR_APPEND = "a"
CFG_EDITOR_SAVE = "x"

CFG_EDIT_LINE_MAX = 128
CFG_EDIT_MAX_LINES = 512

CFG_PATH_CHARS = frozenset("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789._/-")
CFG_PATH_MAX = 32

CFG_MEM = "256M"
CFG_LOG_CAP = 1048576
CFG_SNAP_MAX = 16384

CFG_TMO_BOOT_MS = 60000
CFG_TMO_PROMPT_MS = 30000
CFG_TMO_EXPECT_MS = 30000
CFG_TMO_POWEROFF_MS = 30000
CFG_TMO_MIN = 500
CFG_TMO_MAX = 600000

CFG_READ_CHUNK = 4096
CFG_KILL_GRACE_S = 2.0

CFG_JSONRPC_PARSE_ERROR = -32700
CFG_JSONRPC_INVALID_REQUEST = -32600
CFG_JSONRPC_METHOD_NOT_FOUND = -32601
CFG_JSONRPC_INVALID_PARAMS = -32602
CFG_JSONRPC_INTERNAL_ERROR = -32603

_IMAGE = os.path.join(os.path.dirname(os.path.abspath(__file__)), "os.img")
_ADDONS_DIR = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "addons")
_ADDON_STATE = os.path.join(tempfile.gettempdir(), "minios_mcp_addons.json")
_PIDFILE = os.path.join(tempfile.gettempdir(), "minios_mcp_qemu.pid")


def env_config():
    """Resolve the configuration: defaults overridden by the environment."""
    return {
        "qemu": os.environ.get("QEMU", "qemu-system-x86_64"),
        "image": os.environ.get("MINIOS_IMAGE", _IMAGE),
        "mem": os.environ.get("MINIOS_MEM", CFG_MEM),
        "log_cap": int(os.environ.get("MINIOS_LOG_CAP", str(CFG_LOG_CAP))),
        "tmo_boot_ms": int(os.environ.get("MINIOS_TMO_BOOT", str(CFG_TMO_BOOT_MS))),
        "tmo_prompt_ms": int(os.environ.get("MINIOS_TMO_PROMPT", str(CFG_TMO_PROMPT_MS))),
        "tmo_expect_ms": int(os.environ.get("MINIOS_TMO_EXPECT", str(CFG_TMO_EXPECT_MS))),
        "tmo_poweroff_ms": int(os.environ.get("MINIOS_TMO_POWEROFF", str(CFG_TMO_POWEROFF_MS))),
        "addons_dir": os.environ.get("MINIOS_ADDONS_DIR", _ADDONS_DIR),
        "git": os.environ.get("MINIOS_GIT", "git"),
        "addon_state": os.environ.get("MINIOS_ADDON_STATE", _ADDON_STATE),
        "pidfile": os.environ.get("MINIOS_PIDFILE", _PIDFILE),
    }


def clamp_timeout(ms):
    """Clamp a requested wait to the bounded timeout range."""
    try:
        value = int(ms)
    except (TypeError, ValueError):
        return CFG_TMO_MIN
    if value < CFG_TMO_MIN:
        return CFG_TMO_MIN
    if value > CFG_TMO_MAX:
        return CFG_TMO_MAX
    return value


def validate_path(name):
    """Reject file names the ramdisk or the shell would mishandle."""
    if not isinstance(name, str):
        return "path must be a string"
    if not name or len(name) > CFG_PATH_MAX:
        return "path length must be 1..%d" % CFG_PATH_MAX
    if name.startswith("/") or name.startswith("."):
        return "path must be relative and not start with a dot"
    if ".." in name:
        return "path must not contain '..'"
    for ch in name:
        if ch not in CFG_PATH_CHARS:
            return "path character not allowed: %r" % ch
    return None


def validate_content(text):
    """Reject lines the kernel readline cannot carry (printable ASCII)."""
    if not isinstance(text, str):
        return "content must be a string"
    for ch in text:
        code = ord(ch)
        if ch == "\n":
            continue
        if code < 32 or code > 126:
            return "content character not allowed: U+%04X" % code
    return None


class ToolError(Exception):
    """Expected tool failure, reported to the client as isError."""

    pass


class RPCError(Exception):
    """JSON-RPC level failure carrying a standard error code."""

    def __init__(self, code, message):
        super().__init__(message)
        self.code = code
        self.message = message


class LogBuffer:
    """Bounded console log with absolute byte positions and waits."""

    def __init__(self, cap):
        self.cap = cap
        self.buf = bytearray()
        self.total = 0
        self.cond = threading.Condition(threading.Lock())

    def append(self, data):
        with self.cond:
            self.buf.extend(data)
            if len(self.buf) > self.cap:
                del self.buf[: len(self.buf) - self.cap]
            self.total += len(data)
            self.cond.notify_all()

    def bytes_from(self, pos):
        with self.cond:
            base = self.total - len(self.buf)
            return bytes(self.buf[max(pos, base) - base:])

    def text_from(self, pos, end=None):
        with self.cond:
            base = self.total - len(self.buf)
            start = max(pos, base)
            stop = self.total if end is None else min(max(end, start), self.total)
            return self.buf[start - base:stop - base].decode("latin-1")

    def find(self, marker, start):
        with self.cond:
            return self._find_locked(marker, start)

    def wait_for(self, marker, start, timeout_ms):
        """Block until marker appears at or after start; return position."""
        deadline = time.monotonic() + timeout_ms / 1000.0
        with self.cond:
            while True:
                pos = self._find_locked(marker, start)
                if pos >= 0:
                    return pos
                remaining = deadline - time.monotonic()
                if remaining <= 0:
                    return -1
                self.cond.wait(remaining)

    def _find_locked(self, marker, start):
        base = self.total - len(self.buf)
        if not self.buf:
            return -1
        idx = bytes(self.buf[max(start, base) - base:]).find(marker)
        if idx < 0:
            return -1
        return max(start, base) + idx


class MiniOSSession:
    """One QEMU child, one pty, one console log, one consume cursor."""

    def __init__(self, cfg):
        self.cfg = cfg
        self.log = LogBuffer(cfg["log_cap"])
        self.master = None
        self.slave = None
        self.proc = None
        self.reader = None
        self.cursor = 0
        self.closed = False
        self.pidfile = cfg["pidfile"]

    def booted(self):
        return self.proc is not None and self.proc.poll() is None and not self.closed

    def status(self):
        pid = self.proc.pid if self.booted() else None
        return {
            "booted": self.booted(),
            "pid": pid,
            "log_bytes": self.log.total,
            "log_cap": self.log.cap,
        }

    def _reap_stale(self):
        try:
            with open(self.pidfile, "r") as f:
                stale = int(f.read().strip())
        except (OSError, ValueError):
            return
        try:
            os.kill(stale, 0)
        except OSError:
            self._drop_pidfile()
            return
        try:
            with open("/proc/%d/cmdline" % stale, "rb") as f:
                cmdline = f.read()
        except OSError:
            cmdline = b""
        if b"qemu" not in cmdline:
            return
        try:
            os.kill(stale, signal.SIGTERM)
        except OSError:
            pass
        deadline = time.monotonic() + CFG_KILL_GRACE_S
        while time.monotonic() < deadline:
            try:
                os.kill(stale, 0)
            except OSError:
                break
            time.sleep(0.1)
        else:
            try:
                os.kill(stale, signal.SIGKILL)
            except OSError:
                pass
        self._drop_pidfile()

    def _drop_pidfile(self):
        try:
            os.remove(self.pidfile)
        except OSError:
            pass

    def boot(self, timeout_ms):
        if self.booted():
            return {"booted": True, "log": self.log.text_from(self.cursor)}
        self._reap_stale()
        if not os.path.isfile(self.cfg["image"]):
            raise ToolError("image not found: %s" % self.cfg["image"])
        self.master, self.slave = os.openpty()
        tty.setraw(self.slave)
        try:
            self.proc = subprocess_launch(self.cfg, self.slave)
        except OSError as exc:
            self._close_pty()
            raise ToolError("could not start %s: %s" % (self.cfg["qemu"], exc))
        with open(self.pidfile, "w") as f:
            f.write(str(self.proc.pid))
        self.reader = threading.Thread(target=self._read_loop, daemon=True)
        self.reader.start()
        start = self.log.total
        # Boot is a bounded operation on its own: its waits are capped by
        # the boot timeout, never by a caller's budget for a whole job
        # (minios_install passes its total budget, which a hung prompt
        # would otherwise burn in full before failing).
        budget = min(
            clamp_timeout(timeout_ms or self.cfg["tmo_boot_ms"]),
            clamp_timeout(self.cfg["tmo_boot_ms"]),
        )
        pos = self.log.wait_for(CFG_MARK_BOOT.encode("latin-1"), start, budget)
        if pos < 0:
            raise ToolError("boot timed out waiting for %r" % CFG_MARK_BOOT)
        ready = self.log.wait_for(CFG_PROMPT_SHELL.encode("latin-1"), pos, budget)
        if ready < 0:
            raise ToolError("boot timed out waiting for the shell prompt")
        self.cursor = pos + len(CFG_MARK_BOOT.encode("latin-1"))
        return {"booted": True, "log": self.log.text_from(start, self.cursor)}

    def _read_loop(self):
        while True:
            try:
                chunk = os.read(self.master, CFG_READ_CHUNK)
            except OSError:
                break
            if not chunk:
                break
            self.log.append(chunk)

    def _close_pty(self):
        for fd in (self.master, self.slave):
            if fd is not None:
                try:
                    os.close(fd)
                except OSError:
                    pass
        self.master = None
        self.slave = None

    def _write_line(self, line):
        if not isinstance(line, str) or "\n" in line or "\r" in line:
            raise ToolError("line must be a single non-empty string without newlines")
        if not line:
            raise ToolError("line must not be empty")
        if not self.booted():
            raise ToolError("MiniOS is not booted")
        os.write(self.master, (line + "\n").encode("latin-1"))

    def _write_editor_line(self, line):
        """Editor content lines may be empty (blank lines in the file)."""
        if not isinstance(line, str) or "\n" in line or "\r" in line:
            raise ToolError("line must be a single string without newlines")
        if not self.booted():
            raise ToolError("MiniOS is not booted")
        os.write(self.master, (line + "\n").encode("latin-1"))

    def send(self, line, timeout_ms):
        start = self.log.total
        self._write_line(line)
        marker = CFG_PROMPT_SHELL.encode("latin-1")
        pos = self.log.wait_for(marker, start, clamp_timeout(timeout_ms or self.cfg["tmo_prompt_ms"]))
        if pos < 0:
            raise ToolError("no shell prompt after %r (timeout)" % line)
        end = pos + len(marker)
        self.cursor = end
        return {"text": self.log.text_from(start, end)}

    def expect(self, marker, timeout_ms):
        if not isinstance(marker, str) or not marker:
            raise ToolError("marker must be a non-empty string")
        if not self.booted():
            raise ToolError("MiniOS is not booted")
        raw = marker.encode("latin-1")
        pos = self.log.wait_for(raw, self.cursor, clamp_timeout(timeout_ms or self.cfg["tmo_expect_ms"]))
        if pos < 0:
            return {"matched": False, "text": self.log.text_from(self.cursor)}
        end = pos + len(raw)
        text = self.log.text_from(self.cursor, end)
        self.cursor = end
        return {"matched": True, "text": text}

    def snapshot(self, max_bytes):
        try:
            limit = int(max_bytes)
        except (TypeError, ValueError):
            limit = CFG_SNAP_MAX
        limit = max(1, min(limit, CFG_SNAP_MAX))
        if not self.booted():
            raise ToolError("MiniOS is not booted")
        return {"text": self.log.text_from(self.cursor, self.cursor + limit)}

    def cat(self, path):
        problem = validate_path(path)
        if problem:
            raise ToolError(problem)
        return self.send("cat " + path, self.cfg["tmo_prompt_ms"])

    def run_python(self, script, args=None, timeout_ms=None):
        """Run a MicroPython script (or `-c` code) inside MiniOS and return
        its output, including the `exit code: N` line. MicroPython now runs
        reliably thanks to the kernel fix that zeroes the initial registers
        at the ELF entry (rdx is rtld_fini for glibc's _start)."""
        argv = [script]
        if args:
            argv.extend(str(a) for a in args)
        line = "micropython " + " ".join(argv)
        return self.send(line, timeout_ms)

    def cat_body(self, path, missing_ok=False):
        """Read a ramdisk file and return exactly its bytes.

        The serial driver emits CRLF; the kernel cat appends one newline
        after the content, so the body is extracted by stripping the echoed
        command line, the prompt and that single trailing newline.
        """
        problem = validate_path(path)
        if problem:
            raise ToolError(problem)
        text = self.send("cat " + path, self.cfg["tmo_prompt_ms"])["text"]
        if ("cat: %s: no such file" % path) in text or ("or is a directory" in text):
            if missing_ok:
                return ""
            raise ToolError("no such file: %s" % path)
        nl = text.find("\n")
        body = text[nl + 1:] if nl >= 0 else ""
        marker = "\nminiOS> "
        if body.endswith(marker):
            body = body[: -len(marker)]
        body = body.rstrip("\r")
        body = body.replace("\r\n", "\n")
        if body.endswith("\n"):
            body = body[:-1]
        return body

    def _cleanup_parts(self, parts):
        for part in parts:
            try:
                self.send("rm " + part, self.cfg["tmo_prompt_ms"])
            except ToolError:
                pass

    def write(self, path, content):
        problem = validate_path(path)
        if problem:
            raise ToolError(problem)
        problem = validate_content(content)
        if problem:
            raise ToolError(problem)
        lines = content.split("\n")
        if lines and lines[-1] == "":
            lines.pop()
        if len(lines) > CFG_EDIT_MAX_LINES:
            raise ToolError("content has %d lines, editor maximum is %d" % (len(lines), CFG_EDIT_MAX_LINES))
        for line in lines:
            if len(line) >= CFG_EDIT_LINE_MAX:
                raise ToolError("line too long: %d chars, editor maximum is %d" % (len(line), CFG_EDIT_LINE_MAX - 1))
        if not self.booted():
            raise ToolError("MiniOS is not booted")
        start = self.log.total
        self._write_line("edit " + path)
        editor = CFG_PROMPT_EDITOR.encode("latin-1")
        pos = self.log.wait_for(editor, start, clamp_timeout(self.cfg["tmo_prompt_ms"]))
        if pos < 0:
            raise ToolError("editor did not open (no %r prompt)" % CFG_PROMPT_EDITOR)
        for line in lines:
            self._write_line(CFG_EDITOR_APPEND)
            self._write_editor_line(line)
            pos = self.log.wait_for(editor, pos + 1, clamp_timeout(self.cfg["tmo_prompt_ms"]))
            if pos < 0:
                raise ToolError("editor append did not return")
        self._write_line(CFG_EDITOR_SAVE)
        shell = CFG_PROMPT_SHELL.encode("latin-1")
        pos = self.log.wait_for(shell, pos + 1, clamp_timeout(self.cfg["tmo_prompt_ms"]))
        if pos < 0:
            raise ToolError("editor save did not return to the shell")
        self.cursor = pos + len(shell)
        return {"transcript": self.log.text_from(start, self.cursor)}

    def poweroff(self, timeout_ms):
        if not self.booted():
            return {"text": ""}
        start = self.log.total
        os.write(self.master, b"poweroff\n")
        marker = CFG_MARK_POWEROFF.encode("latin-1")
        pos = self.log.wait_for(marker, start, clamp_timeout(timeout_ms or self.cfg["tmo_poweroff_ms"]))
        if pos < 0:
            self.terminate()
            raise ToolError("poweroff timed out waiting for %r" % CFG_MARK_POWEROFF)
        deadline = time.monotonic() + clamp_timeout(timeout_ms or self.cfg["tmo_poweroff_ms"]) / 1000.0
        while self.proc.poll() is None and time.monotonic() < deadline:
            time.sleep(0.1)
        if self.proc.poll() is None:
            self.terminate()
            raise ToolError("QEMU did not exit after poweroff")
        text = self.log.text_from(start, pos + len(marker))
        self.terminate()
        return {"text": text}

    def terminate(self):
        if self.proc is None:
            return
        if self.proc.poll() is None:
            self.proc.terminate()
            try:
                self.proc.wait(timeout=CFG_KILL_GRACE_S)
            except Exception:
                self.proc.kill()
                try:
                    self.proc.wait(timeout=CFG_KILL_GRACE_S)
                except Exception:
                    pass
        self._close_pty()
        self._drop_pidfile()
        self.proc = None
        self.reader = None
        self.closed = True

    def close(self):
        self.terminate()


def subprocess_launch(cfg, slave_fd):
    import subprocess

    return subprocess.Popen(
        [
            cfg["qemu"],
            "-drive",
            "file=%s,format=raw,if=ide" % cfg["image"],
            "-m",
            cfg["mem"],
            "-nic",
            "user,model=rtl8139",
            "-display",
            "none",
            "-serial",
            "stdio",
            "-no-reboot",
        ],
        stdin=slave_fd,
        stdout=slave_fd,
        stderr=subprocess.DEVNULL,
        close_fds=True,
        start_new_session=True,
    )


TOOLS = [
    {
        "name": "minios_status",
        "description": "Report whether MiniOS is booted and console log sizes.",
        "inputSchema": {"type": "object", "properties": {}},
    },
    {
        "name": "minios_boot",
        "description": "Boot os.img in QEMU and wait for the shell prompt. Idempotent.",
        "inputSchema": {"type": "object", "properties": {"timeout_ms": {"type": "integer"}}},
    },
    {
        "name": "minios_snapshot",
        "description": "Return the console output since the last consumed position, without consuming it.",
        "inputSchema": {"type": "object", "properties": {"max_bytes": {"type": "integer"}}},
    },
    {
        "name": "minios_send",
        "description": "Send one shell command and wait for the next prompt; returns everything in between.",
        "inputSchema": {
            "type": "object",
            "properties": {
                "line": {"type": "string"},
                "timeout_ms": {"type": "integer"},
            },
            "required": ["line"],
        },
    },
    {
        "name": "minios_expect",
        "description": "Wait until a marker appears in the console output; consumes through the match.",
        "inputSchema": {
            "type": "object",
            "properties": {
                "marker": {"type": "string"},
                "timeout_ms": {"type": "integer"},
            },
            "required": ["marker"],
        },
    },
    {
        "name": "minios_write",
        "description": "Create or replace a file on the ramdisk through the MiniOS line editor.",
        "inputSchema": {
            "type": "object",
            "properties": {
                "path": {"type": "string"},
                "content": {"type": "string"},
            },
            "required": ["path", "content"],
        },
    },
    {
        "name": "minios_cat",
        "description": "Print a ramdisk file inside MiniOS.",
        "inputSchema": {
            "type": "object",
            "properties": {"path": {"type": "string"}},
            "required": ["path"],
        },
    },
    {
        "name": "minios_python",
        "description": "Run a Python script inside MiniOS with MicroPython (e.g. src/test.py, src/build.py) and return its output.",
        "inputSchema": {
            "type": "object",
            "properties": {
                "script": {"type": "string", "description": "ramdisk path of the .py script to run"},
                "args": {"type": "array", "items": {"type": "string"}, "description": "optional script arguments"},
                "timeout_ms": {"type": "integer"},
            },
            "required": ["script"],
        },
    },
    {
        "name": "minios_py_eval",
        "description": "Evaluate a MicroPython one-liner inside MiniOS and return its output.",
        "inputSchema": {
            "type": "object",
            "properties": {
                "code": {"type": "string"},
                "timeout_ms": {"type": "integer"},
            },
            "required": ["code"],
        },
    },
    {
        "name": "minios_addons",
        "description": "List the addon marketplace entries and whether each is installed.",
        "inputSchema": {"type": "object", "properties": {}},
    },
    {
        "name": "minios_install",
        "description": "Install an addon: clone its repo, upload sources, build and verify inside MiniOS.",
        "inputSchema": {
            "type": "object",
            "properties": {
                "name": {"type": "string"},
                "timeout_ms": {"type": "integer"},
            },
            "required": ["name"],
        },
    },
    {
        "name": "minios_poweroff",
        "description": "Power the machine off and terminate QEMU; releases the pid file.",
        "inputSchema": {"type": "object", "properties": {"timeout_ms": {"type": "integer"}}},
    },
]


class MCPServer:
    """JSON-RPC dispatch loop over stdio."""

    def __init__(self, cfg):
        self.cfg = cfg
        self.session = MiniOSSession(cfg)

    def run(self):
        for line in sys.stdin:
            line = line.strip()
            if not line:
                continue
            self._handle(line)
            sys.stdout.flush()

    def _handle(self, line):
        try:
            msg = json.loads(line)
        except ValueError:
            self._reply({"id": None, "error": {"code": CFG_JSONRPC_PARSE_ERROR, "message": "parse error"}})
            return
        if not isinstance(msg, dict) or "method" not in msg or not isinstance(msg["method"], str):
            self._reply({"id": msg.get("id"), "error": {"code": CFG_JSONRPC_INVALID_REQUEST, "message": "invalid request"}})
            return
        if "id" not in msg:
            return
        method = msg["method"]
        if method == "initialize":
            self._reply({"id": msg["id"], "result": self._initialize(msg.get("params", {}))})
        elif method == "tools/list":
            self._reply({"id": msg["id"], "result": {"tools": TOOLS}})
        elif method == "tools/call":
            try:
                self._reply({"id": msg["id"], "result": self._call(msg.get("params"))})
            except RPCError as exc:
                self._reply({"id": msg["id"], "error": {"code": exc.code, "message": exc.message}})
        elif method == "ping":
            self._reply({"id": msg["id"], "result": {}})
        else:
            self._reply({"id": msg["id"], "error": {"code": CFG_JSONRPC_METHOD_NOT_FOUND, "message": "method not found: %s" % method}})

    def _initialize(self, params):
        return {
            "protocolVersion": params.get("protocolVersion", CFG_PROTOCOL_VERSION),
            "capabilities": {"tools": {}},
            "serverInfo": {"name": CFG_SERVER_NAME, "version": CFG_SERVER_VERSION},
        }

    def _call(self, params):
        if not isinstance(params, dict) or not isinstance(params.get("name"), str):
            raise RPCError(CFG_JSONRPC_INVALID_PARAMS, "invalid params: name required")
        name = params["name"]
        if name not in {t["name"] for t in TOOLS}:
            raise RPCError(CFG_JSONRPC_INVALID_PARAMS, "unknown tool: %s" % name)
        args = params.get("arguments")
        if not isinstance(args, dict):
            args = {}
        try:
            result = self._dispatch(name, args)
        except ToolError as exc:
            return {"content": [{"type": "text", "text": str(exc)}], "isError": True}
        except Exception as exc:
            return {"content": [{"type": "text", "text": "internal error: %r" % exc}], "isError": True}
        return {"content": [{"type": "text", "text": json.dumps(result)}]}

    def _dispatch(self, name, args):
        if name == "minios_status":
            return self.session.status()
        if name == "minios_boot":
            return self.session.boot(args.get("timeout_ms"))
        if name == "minios_snapshot":
            return self.session.snapshot(args.get("max_bytes"))
        if name == "minios_send":
            if not isinstance(args.get("line"), str):
                raise ToolError("line must be a string")
            return self.session.send(args["line"], args.get("timeout_ms"))
        if name == "minios_expect":
            if not isinstance(args.get("marker"), str):
                raise ToolError("marker must be a string")
            return self.session.expect(args["marker"], args.get("timeout_ms"))
        if name == "minios_write":
            return self.session.write(args.get("path"), args.get("content", ""))
        if name == "minios_cat":
            return self.session.cat(args.get("path"))
        if name == "minios_python":
            if not isinstance(args.get("script"), str):
                raise ToolError("script must be a string")
            return self.session.run_python(args["script"], args.get("args"), args.get("timeout_ms"))
        if name == "minios_py_eval":
            if not isinstance(args.get("code"), str):
                raise ToolError("code must be a string")
            # The kernel shell splits on spaces, so a one-liner with spaces
            # cannot travel as a single `-c` argument; write it to a temp
            # script and run that instead.
            self.session.write("tmp/_eval.py", args["code"] + "\n")
            return self.session.run_python("tmp/_eval.py", None, args.get("timeout_ms"))
        if name == "minios_addons":
            return self._addons_list()
        if name == "minios_install":
            return self._addon_install(args)
        if name == "minios_poweroff":
            return self.session.poweroff(args.get("timeout_ms"))
        raise ToolError("unknown tool: %s" % name)

    def _addons_list(self):
        state = minios_addons.AddonState(self.cfg["addon_state"]).load()
        entries = minios_addons.load_addons_dir(self.cfg["addons_dir"])
        out = []
        for addon in entries:
            if "error" in addon:
                out.append(
                    {"name": addon["name"], "error": addon["error"], "installed": False}
                )
                continue
            out.append(
                {
                    "name": addon["name"],
                    "description": addon.get("description", ""),
                    "version": addon.get("version", ""),
                    "file": addon.get("file", ""),
                    "installed": addon["name"] in state,
                }
            )
        return {"addons": out, "state_file": self.cfg["addon_state"]}

    def _addon_install(self, args):
        name = args.get("name")
        if not isinstance(name, str) or not name:
            raise ToolError("name must be a non-empty string")
        entries = minios_addons.load_addons_dir(self.cfg["addons_dir"])
        addon = None
        for entry in entries:
            if entry.get("name") == name:
                addon = entry
                break
        if addon is None:
            raise ToolError("no such addon: %s" % name)
        if "error" in addon:
            raise ToolError("addon %s is invalid: %s" % (name, addon["error"]))
        cfg = {
            "git": self.cfg["git"],
            "timeout_ms": args.get("timeout_ms"),
            "state_file": self.cfg["addon_state"],
        }
        return minios_addons.install_addon(self.session, addon, cfg)

    def _reply(self, msg):
        sys.stdout.write(json.dumps(msg) + "\n")


def main():
    cfg = env_config()
    server = MCPServer(cfg)
    atexit.register(server.session.close)
    for sig in (signal.SIGTERM, signal.SIGINT):
        signal.signal(sig, lambda s, f: sys.exit(0))
    server.run()
    return 0


if __name__ == "__main__":
    sys.exit(main())
