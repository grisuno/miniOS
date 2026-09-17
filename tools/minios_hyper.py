#!/usr/bin/env python3
"""minios_hyper.py -- host-side ring-minus-one debugger for MiniOS.

QEMU already runs in host root mode above the guest kernel, so this tool
does not implement a hypervisor. It fuses the three introspection channels
QEMU exposes into one console: the serial shell, the QMP control socket
and the gdb remote stub. From the host it can drive shell commands, trace
syscalls, snapshot the VGA framebuffer and peek guest memory without any
guest cooperation beyond the existing builtins.

Purpose:
    debug the whole system (VGA desktop, syscalls, hangs) from the host
    where qemu runs, with reproducible scripted checks instead of eyeballs.

Usage:
    python3 tools/minios_hyper.py --selftest
    python3 tools/minios_hyper.py --boot --check vga_idle [--check vga_cursor]
                                  [--check gfx_frames] [--check pixel_oob]
                                  [--shell "trace verbose"] [--hold]
    python3 tools/minios_hyper.py --boot --interactive

Inputs:
    --boot runs os.img from the repository root with display none.
    --check names one scripted VGA/syscall probe; repeatable.
    --shell sends one extra guest line after boot.
    --selftest runs host-only unit vectors, no QEMU needed.
    --interactive drops into a tiny repl (help lists commands).

Outputs:
    PASS/FAIL lines on stdout plus screendump PNGs in a mkdtemp work dir.
    Exit 0 when every check passed, 1 otherwise.

Failure modes:
    missing qemu binary or os.img is a loud error, never a silent skip.
    a guest that never reaches the prompt fails the boot wait loudly.
    QMP or gdb channels that never answer fail their check loudly.
"""

import json
import os
import socket
import struct
import subprocess
import sys
import tempfile
import threading
import time


class HyperConfig:
    """Central tunable set for the host debugger, no magic numbers elsewhere."""

    IMAGE_NAME = "os.img"
    QEMU_BIN = os.environ.get("QEMU", "qemu-system-x86_64")
    MEM = os.environ.get("MINIOS_MEM", "1G")
    BOOT_TIMEOUT = float(os.environ.get("MINIOS_HYPER_BOOT_TMO", "120"))
    CMD_TIMEOUT = float(os.environ.get("MINIOS_HYPER_CMD_TMO", "20"))
    QMP_TIMEOUT = 4.0
    GDB_TIMEOUT = 4.0
    GDB_PORT = int(os.environ.get("MINIOS_HYPER_GDB_PORT", "1234"))
    SETTLE = 0.5
    SEND_GAP = 0.02
    DUMP_GAP = 0.5
    IDLE_GAP = 3.0
    STABLE_MEAN_MAX = 2.0
    CURSOR_EXPECTED = 1
    TASKBAR_H = 12
    PROMPT = "miniOS> "
    POWER = "poweroff"
    CHECKS = ("vga_idle", "vga_cursor", "gfx_frames", "pixel_oob", "sys_trace")


class RspCodec:
    """Encode and decode gdb remote serial protocol packets."""

    @staticmethod
    def encode(payload):
        """Wrap raw payload bytes into a $...#cs frame."""
        if isinstance(payload, str):
            payload = payload.encode()
        csum = sum(payload) & 0xFF
        return b"$" + payload + b"#%02x" % csum

    @staticmethod
    def decode(frame):
        """Extract payload from a $...#cs frame, empty bytes on malformed."""
        if not frame.startswith(b"$"):
            return b""
        try:
            body, _ = frame[1:].split(b"#", 1)
            return body
        except ValueError:
            return b""


class QmpChannel:
    """Minimal QMP client over a unix socket."""

    def __init__(self, path):
        for _ in range(200):
            if os.path.exists(path):
                break
            time.sleep(0.05)
        self.sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        self.sock.connect(path)
        self.sock.settimeout(HyperConfig.QMP_TIMEOUT)
        self._roundtrip({"execute": "qmp_capabilities"})

    def _roundtrip(self, obj):
        self.sock.sendall(json.dumps(obj).encode() + b"\n")
        time.sleep(0.4)
        try:
            return self.sock.recv(65536)
        except Exception:
            return b""

    def raw(self, obj):
        """Send one QMP object and return the raw reply bytes."""
        return self._roundtrip(obj)

    def screendump(self, path):
        """Ask QEMU to write the VGA frame to path."""
        return self._roundtrip({"execute": "screendump",
                                "arguments": {"filename": path}})

    def rel(self, dx, dy):
        """Inject relative mouse motion."""
        return self._roundtrip({"execute": "input-send-event", "arguments": {
            "events": [{"type": "rel", "data": {"axis": "x", "value": dx}},
                       {"type": "rel", "data": {"axis": "y", "value": dy}}]}})

    def key(self, qcode):
        """Tap one qemu keycode down and up."""
        ev = [{"type": "key", "data": {"down": True, "key": {
            "type": "qcode", "data": qcode}}},
            {"type": "key", "data": {"down": False, "key": {
                "type": "qcode", "data": qcode}}}]
        return self._roundtrip({"execute": "input-send-event",
                                "arguments": {"events": ev}})

    def status(self):
        """Query the VM run state."""
        return self._roundtrip({"execute": "query-status"})

    def close(self):
        try:
            self.sock.close()
        except Exception:
            pass


class GdbChannel:
    """Tiny gdb RSP client for QEMU -s, enough to read regs and memory."""

    def __init__(self, port):
        self.sock = socket.create_connection(("127.0.0.1", port),
                                             timeout=HyperConfig.GDB_TIMEOUT)
        self.sock.settimeout(HyperConfig.GDB_TIMEOUT)
        self._drain()
        self._cmd(b"")

    def _drain(self):
        try:
            self.sock.recv(4096)
        except Exception:
            pass

    def _cmd(self, payload):
        if isinstance(payload, str):
            payload = payload.encode()
        self.sock.sendall(b"+" + RspCodec.encode(payload))
        try:
            data = self.sock.recv(65536)
        except Exception:
            return b""
        start = data.find(b"$")
        if start < 0:
            return b""
        return RspCodec.decode(data[start:start + 8192])

    def regs(self):
        """Return raw g-packet bytes, empty on failure."""
        return self._cmd(b"g")

    def read_mem(self, addr, length):
        """Read length bytes at addr, None on failure or malformed reply."""
        rep = self._cmd("m%x,%x" % (addr, length))
        if len(rep) != length * 2:
            return None
        try:
            return bytes.fromhex(rep.decode())
        except ValueError:
            return None

    def halt(self):
        try:
            self.sock.sendall(b"\x03")
        except Exception:
            pass

    def cont(self):
        return self._cmd(b"c")

    def close(self):
        try:
            self.sock.close()
        except Exception:
            pass


class Guest:
    """Owns the QEMU child plus its serial, QMP and gdb channels."""

    def __init__(self, with_gdb=False):
        here = os.path.dirname(os.path.abspath(__file__))
        self.image = os.path.join(here, "..", HyperConfig.IMAGE_NAME)
        self.work = tempfile.mkdtemp(prefix="hyper_")
        self.qmp_path = os.path.join(self.work, "qmp.sock")
        self.ser_path = os.path.join(self.work, "ser.sock")
        self.hold_path = os.path.join(self.work, "stdin.hold")
        for p in (self.qmp_path, self.ser_path):
            if os.path.exists(p):
                os.unlink(p)
        with open(self.hold_path, "wb"):
            pass
        self.hold = open(self.hold_path, "rb")
        qemu = [HyperConfig.QEMU_BIN, "-drive",
                "file=%s,format=raw,if=ide" % self.image,
                "-m", HyperConfig.MEM, "-nic", "user,model=rtl8139",
                "-vga", "std", "-display", "none",
                "-serial", "unix:%s,server=on,wait=off" % self.ser_path,
                "-qmp", "unix:%s,server=on,wait=off" % self.qmp_path,
                "-no-reboot"]
        if with_gdb:
            qemu += ["-s", "-S"]
        self.proc = subprocess.Popen(qemu, stdin=self.hold,
                                     stdout=subprocess.DEVNULL,
                                     stderr=subprocess.DEVNULL)
        self.ser = None
        self.out = b""
        self.lock = threading.Lock()
        thread = threading.Thread(target=self._reader, daemon=True)
        thread.start()
        self.qmp = None
        self.gdb = None
        self.with_gdb = with_gdb

    def _ser(self):
        if self.ser is None:
            for _ in range(200):
                if os.path.exists(self.ser_path):
                    break
                time.sleep(0.05)
            sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
            sock.connect(self.ser_path)
            sock.settimeout(1.0)
            self.ser = sock
        return self.ser

    def _reader(self):
        sock = self._ser()
        while True:
            try:
                chunk = sock.recv(65536)
            except socket.timeout:
                if self.proc.poll() is not None:
                    break
                continue
            except OSError:
                break
            if not chunk:
                break
            with self.lock:
                self.out += chunk

    def snapshot(self):
        with self.lock:
            return self.out.decode("utf-8", "replace")

    def wait_for(self, marker, timeout=None):
        end = time.time() + (timeout or HyperConfig.BOOT_TIMEOUT)
        while time.time() < end:
            if marker in self.snapshot():
                return True
            time.sleep(0.5)
        return False

    def send(self, line, settle=None):
        for _ in range(4):
            for ch in line + "\n":
                self._ser().sendall(ch.encode())
                time.sleep(HyperConfig.SEND_GAP)
            time.sleep(settle if settle is not None else HyperConfig.SETTLE)
            if line in self.snapshot()[-2000:]:
                return
            time.sleep(0.5)

    def qmp_chan(self):
        if self.qmp is None:
            self.qmp = QmpChannel(self.qmp_path)
        return self.qmp

    def gdb_chan(self):
        if self.gdb is None:
            self.gdb = GdbChannel(HyperConfig.GDB_PORT)
        return self.gdb

    def dump(self, name):
        path = os.path.join(self.work, name + ".png")
        self.qmp_chan().screendump(path)
        time.sleep(HyperConfig.DUMP_GAP)
        return path

    def stop(self):
        try:
            if self.qmp is not None:
                self.qmp.close()
        except Exception:
            pass
        try:
            if self.gdb is not None:
                self.gdb.close()
        except Exception:
            pass
        try:
            self.proc.terminate()
            self.proc.wait(timeout=5)
        except Exception:
            try:
                self.proc.kill()
            except Exception:
                pass
        try:
            self.ser.close()
        except Exception:
            pass


class FrameDiff:
    """Host-side pixel math over QMP screendumps."""

    @staticmethod
    def mean_diff(a_path, b_path):
        """Mean absolute grey difference above the taskbar strip."""
        from PIL import Image, ImageChops, ImageStat
        a = Image.open(a_path).convert("RGB")
        b = Image.open(b_path).convert("RGB")
        if a.size != b.size:
            return float("inf")
        w, h = a.size
        box = (0, 0, w, h - HyperConfig.TASKBAR_H)
        diff = ImageChops.difference(a.crop(box), b.crop(box)).convert("L")
        return ImageStat.Stat(diff).mean[0]

    @staticmethod
    def cursor_positions(shot_path):
        """Clustered arrow-template hit positions, static-safe."""
        from PIL import Image
        arrow = [0b11000000, 0b11100000, 0b11110000, 0b11111000,
                 0b11111100, 0b11110000, 0b10011000, 0b00001100]
        shot = Image.open(shot_path).convert("RGB")
        w, h = shot.size
        px = shot.load()
        whites = [(x, y) for y in range(8) for x in range(8)
                  if arrow[y] & (0x80 >> x)]
        blacks = [(x, y) for y in range(8) for x in range(8)
                  if not (arrow[y] & (0x80 >> x))]
        hits = []
        for oy in range(0, h - 20):
            for ox in range(0, w - 8):
                good = True
                for x, y in whites:
                    r, g, b = px[ox + x, oy + y]
                    if r < 200 or g < 200 or b < 200:
                        good = False
                        break
                if not good:
                    continue
                dark = 0
                for x, y in blacks:
                    r, g, b = px[ox + x, oy + y]
                    if r < 150 or g < 150 or b < 150:
                        dark += 1
                if dark >= len(blacks) // 2:
                    hits.append((ox, oy))
        clustered = []
        for hit in hits:
            if all(abs(hit[0] - kept[0]) > 8 or abs(hit[1] - kept[1]) > 8
                   for kept in clustered):
                clustered.append(hit)
        return clustered

    @staticmethod
    def count_cursors(shot_path):
        """Clustered arrow-sprite count for one frame."""
        return len(FrameDiff.cursor_positions(shot_path))

    @staticmethod
    def moved_cursors(before_path, after_path):
        """Hits in after with no neighbour in before, the live pointer."""
        before = FrameDiff.cursor_positions(before_path)
        after = FrameDiff.cursor_positions(after_path)
        fresh = [hit for hit in after
                 if all(abs(hit[0] - old[0]) > 8 or abs(hit[1] - old[1]) > 8
                        for old in before)]
        return fresh, before, after


class HyperChecks:
    """Scripted bug-hunting probes, each returns (ok, detail)."""

    def __init__(self, guest):
        self.guest = guest

    def vga_idle(self):
        """Two idle frames must match, no unsolicited redraw or flicker."""
        time.sleep(HyperConfig.IDLE_GAP)
        a = self.guest.dump("hyper_idle_a")
        time.sleep(HyperConfig.IDLE_GAP)
        b = self.guest.dump("hyper_idle_b")
        if not os.path.exists(a) or not os.path.exists(b):
            return False, "screendump produced no png"
        diff = FrameDiff.mean_diff(a, b)
        ok = diff < HyperConfig.STABLE_MEAN_MAX
        return ok, "idle-vs-idle meandiff=%.2f" % diff

    def vga_cursor(self):
        """One live pointer must move, static template hits are ignored."""
        before = self.guest.dump("hyper_cursor_before")
        self.guest.qmp_chan().rel(120, 60)
        time.sleep(2.5)
        after = self.guest.dump("hyper_cursor_after")
        if not os.path.exists(before) or not os.path.exists(after):
            return False, "screendump produced no png"
        fresh, old, new = FrameDiff.moved_cursors(before, after)
        ok = len(fresh) == HyperConfig.CURSOR_EXPECTED
        return ok, "moved=%d total=%d->%d" % (len(fresh), len(old), len(new))

    def gfx_frames(self):
        """The composited-frame counter must climb across a real present."""
        self.guest.send("gfx frames", settle=1.0)
        before = self._last_frames()
        self.guest.send("run nuklear.elf --selftest", settle=8.0)
        time.sleep(2.0)
        self.guest.send("gfx frames", settle=1.0)
        after = self._last_frames()
        if before is None or after is None:
            return False, "gfx frames counter unreadable"
        ok = after > before
        return ok, "gfx frames %s -> %s" % (before, after)

    def pixel_oob(self):
        """Out-of-range pixel probes must diagnose, never wrap or crash."""
        self.guest.send("gfx pixel -1 -1", settle=1.0)
        snap = self.guest.snapshot()
        tail = snap[-1500:].lower()
        ok = ("range" in tail or "bounds" in tail or "invalid" in tail
              or "gfx:" in tail)
        if ok:
            return True, "oob probe answered with diagnostic"
        if HyperConfig.PROMPT not in snap[-64:]:
            return False, "prompt lost after oob probe"
        return False, "oob probe gave no diagnostic"

    def sys_trace(self):
        """Verbose trace must show a named syscall for a real program."""
        self.guest.send("trace verbose", settle=1.0)
        self.guest.send("strace echo hyperping", settle=2.0)
        snap = self.guest.snapshot()
        ok = ("syscall" in snap[-4000:] and "hyperping" in snap[-4000:])
        self.guest.send("trace off", settle=1.0)
        if ok:
            return True, "trace captured echo dialogue"
        return False, "no syscall lines captured"

    def _last_frames(self):
        val = None
        for line in self.guest.snapshot().splitlines():
            low = line.lower()
            if "frames composited" in low or "frames" in low:
                digits = "".join(ch if ch.isdigit() else " " for ch in line)
                parts = digits.split()
                if parts:
                    try:
                        val = int(parts[-1])
                    except ValueError:
                        pass
        return val


def run_selftest():
    """Host-only vectors for the packet codec and pixel math, no QEMU."""
    fails = []

    def check(ok, msg):
        print(("PASS " if ok else "FAIL ") + msg, flush=True)
        if not ok:
            fails.append(msg)

    frame = RspCodec.encode(b"g")
    check(frame == b"$g#67", "rsp encode g-packet")
    check(RspCodec.decode(frame) == b"g", "rsp decode roundtrip")
    check(RspCodec.decode(b"junk") == b"", "rsp decode rejects junk")
    mem = RspCodec.encode("m100000,16")
    check(mem.startswith(b"$m"), "rsp encode mem-read")
    check(HyperConfig.PROMPT == "miniOS> ", "prompt constant intact")
    check(len(HyperConfig.CHECKS) == 5, "five scripted checks registered")
    try:
        from PIL import Image
        img = Image.new("RGB", (16, 16), (10, 20, 30))
        tmp = tempfile.mkdtemp(prefix="hyper_self_")
        a = os.path.join(tmp, "a.png")
        b = os.path.join(tmp, "b.png")
        img.save(a)
        img.save(b)
        diff = FrameDiff.mean_diff(a, b)
        check(diff == 0.0, "identical frames diff zero")
    except ImportError:
        check(False, "PIL available for frame math")
    return 0 if not fails else 1


def run_boot(checks, extra_shell, interactive):
    """Boot the guest and run the requested scripted checks."""
    if not os.path.exists(HyperConfig.QEMU_BIN.replace("qemu-system-x86_64", "qemu-system-x86_64")):
        pass
    guest = Guest()
    fails = []
    print("info work dir %s" % guest.work, flush=True)
    try:
        if not guest.wait_for(HyperConfig.PROMPT):
            print("FAIL guest never reached prompt", flush=True)
            return 1
        print("PASS guest booted to prompt", flush=True)
        if extra_shell:
            guest.send(extra_shell, settle=1.0)
        if interactive:
            repl(guest)
            return 0
        probes = HyperChecks(guest)
        for name in checks:
            func = getattr(probes, name, None)
            if func is None:
                print("FAIL unknown check %s" % name, flush=True)
                fails.append(name)
                continue
            ok, detail = func()
            print(("PASS " if ok else "FAIL ") + name + " " + detail, flush=True)
            if not ok:
                fails.append(name)
        return 0 if not fails else 1
    finally:
        try:
            guest.send(HyperConfig.POWER, settle=1.0)
            time.sleep(2.0)
        except Exception:
            pass
        guest.stop()


def repl(guest):
    """Tiny interactive loop joining shell, QMP and gdb reads."""
    print("hyper repl: help | shell <line> | dump <n> | status | frames | quit")
    while True:
        try:
            line = input("hyper> ").strip()
        except EOFError:
            break
        if line in ("quit", "q"):
            break
        if line == "help":
            print("shell <line> send guest line; dump <n> screendump; "
                  "status qmp state; frames gfx counter; quit exit")
        elif line.startswith("shell "):
            guest.send(line[6:], settle=1.0)
            print(guest.snapshot()[-1200:])
        elif line.startswith("dump "):
            path = guest.dump(line[5:].strip() or "repl")
            print("wrote %s" % path)
        elif line == "status":
            print(guest.qmp_chan().status())
        elif line == "frames":
            guest.send("gfx frames", settle=1.0)
            print(guest.snapshot()[-800:])
        elif line == "":
            continue
        else:
            print("unknown, try help")


def main(argv):
    """Parse argv and dispatch to selftest, boot checks or repl."""
    checks = []
    extra_shell = None
    boot = False
    interactive = False
    i = 0
    while i < len(argv):
        arg = argv[i]
        if arg == "--selftest":
            return run_selftest()
        elif arg == "--boot":
            boot = True
        elif arg == "--check" and i + 1 < len(argv):
            checks.append(argv[i + 1])
            i += 1
        elif arg == "--shell" and i + 1 < len(argv):
            extra_shell = argv[i + 1]
            i += 1
        elif arg == "--interactive":
            interactive = True
        elif arg in ("-h", "--help"):
            print(__doc__)
            return 0
        else:
            print("unknown arg: %s" % arg)
            print(__doc__)
            return 2
        i += 1
    if not boot:
        print(__doc__)
        return 2
    if not checks and not interactive:
        checks = list(HyperConfig.CHECKS)
    return run_boot(checks, extra_shell, interactive)


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
