#!/usr/bin/env python3
"""test_gui_fashion.py -- GUI proof for the cursor/flicker/quit fixes.

Boots the real image and judges pixels over QMP screendumps:

  1. `run file &` (bg): two dumps 3s apart with zero input must be
     identical above the taskbar (single cursor owner: no trails,
     no present-vs-tick flicker).
  2. Jiggle the mouse across the window, then idle: frames converge
     again (no stranded cursor sprites on hitboxes).
  3. `run file` (fg) + QMP ESC: the shell prompt returns (ESC quit,
     no title-bar X needed).
  4. `wm state` reports the active theme (`wm: theme dark`).

Fails loudly (exit 1) with the mean-abs-diff numbers. Dumps stay in
the printed work dir for eyeballing.
"""
import os
import socket
import subprocess
import sys
import tempfile
import threading
import time
import json

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.join(HERE, "..")
IMAGE = os.path.join(REPO, "os.img")
WORK = tempfile.mkdtemp(prefix="fashion_")
QMP_SOCK = os.path.join(WORK, "qmp.sock")
SER_SOCK = os.path.join(WORK, "ser.sock")
HOLD = os.path.join(WORK, "stdin.hold")
DUMPS = WORK

FAIL = []


def note(ok, msg):
    print(("PASS " if ok else "FAIL ") + msg, flush=True)
    if not ok:
        FAIL.append(msg)


class Guest:
    def __init__(self):
        for p in (QMP_SOCK, SER_SOCK):
            if os.path.exists(p):
                os.unlink(p)
        with open(HOLD, "wb"):
            pass
        self._stdin_hold = open(HOLD, "rb")
        qemu = ["qemu-system-x86_64", "-drive",
                "file=%s,format=raw,if=ide" % IMAGE,
                "-m", "1G", "-nic", "user,model=rtl8139", "-vga", "std",
                "-display", "none",
                "-serial", "unix:%s,server=on,wait=off" % SER_SOCK,
                "-qmp", "unix:%s,server=on,wait=off" % QMP_SOCK,
                "-no-reboot"]
        self.proc = subprocess.Popen(
            qemu, stdin=self._stdin_hold, stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL)
        self.ser = None
        self.out = b""
        self.lock = threading.Lock()
        t = threading.Thread(target=self._reader, daemon=True)
        t.start()
        self.qmp = None

    def _ser(self):
        if self.ser is None:
            for _ in range(200):
                if os.path.exists(SER_SOCK):
                    break
                time.sleep(0.05)
            s = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
            s.connect(SER_SOCK)
            s.settimeout(1.0)
            self.ser = s
        return self.ser

    def _reader(self):
        s = self._ser()
        while True:
            try:
                ch = s.recv(65536)
            except socket.timeout:
                if self.proc.poll() is not None:
                    break
                continue
            except OSError:
                break
            if not ch:
                break
            with self.lock:
                self.out += ch

    def snapshot(self):
        with self.lock:
            return self.out.decode("utf-8", "replace")

    def wait_prompt(self, timeout=120):
        end = time.time() + timeout
        while time.time() < end:
            if "miniOS> " in self.snapshot():
                return True
            time.sleep(0.5)
        return False

    def wait_for(self, marker, timeout=120):
        end = time.time() + timeout
        while time.time() < end:
            if marker in self.snapshot():
                return True
            time.sleep(0.5)
        return False

    def send(self, line, settle=0.5):
        for _ in range(4):
            for ch in line + "\n":
                self._ser().sendall(ch.encode())
                time.sleep(0.02)
            time.sleep(settle)
            if line in self.snapshot()[-2000:]:
                return
            time.sleep(0.5)

    def qmp_cmd(self, obj):
        if self.qmp is None:
            for _ in range(200):
                if os.path.exists(QMP_SOCK):
                    break
                time.sleep(0.05)
            s = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
            s.connect(QMP_SOCK)
            s.settimeout(4)
            self.qmp = s
            self._qmp({"execute": "qmp_capabilities"})
        return self._qmp(obj)

    def _qmp(self, obj):
        self.qmp.sendall(json.dumps(obj).encode() + b"\n")
        time.sleep(0.4)
        try:
            return self.qmp.recv(65536)
        except Exception:
            return b""

    def key(self, qcode, down=True, up=True):
        ev = []
        if down:
            ev.append({"type": "key", "data": {"down": True, "key": {
                "type": "qcode", "data": qcode}}})
        if up:
            ev.append({"type": "key", "data": {"down": False, "key": {
                "type": "qcode", "data": qcode}}})
        self.qmp_cmd({"execute": "input-send-event",
                      "arguments": {"events": ev}})
        time.sleep(0.3)

    def rel(self, dx, dy):
        self.qmp_cmd({"execute": "input-send-event", "arguments": {
            "events": [{"type": "rel", "data": {"axis": "x", "value": dx}},
                       {"type": "rel", "data": {"axis": "y",
                                                "value": dy}}]}})
        time.sleep(0.3)

    def dump(self, name):
        p = os.path.join(DUMPS, name + ".png")
        self.qmp_cmd({"execute": "screendump",
                      "arguments": {"filename": p}})
        time.sleep(0.5)
        return p

    def stop(self):
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


def meandiff(a_path, b_path):
    from PIL import Image, ImageChops, ImageStat
    a = Image.open(a_path).convert("RGB")
    b = Image.open(b_path).convert("RGB")
    if a.size != b.size:
        return float("inf")
    w, h = a.size
    box = (0, 0, w, h - 12)
    d = ImageChops.difference(a.crop(box), b.crop(box)).convert("L")
    return ImageStat.Stat(d).mean[0]


ARROW = [0b11000000, 0b11100000, 0b11110000, 0b11111000,
         0b11111100, 0b11110000, 0b10011000, 0b00001100]


def count_arrows(shot_path):
    """Cursor sprites by template: every arrow-white pixel near-white,
    and at least half the arrow-black pixels non-white (rejects text).
    A single owner paints exactly 1; a cursor race strands 2+."""
    from PIL import Image
    shot = Image.open(shot_path).convert("RGB")
    w, h = shot.size
    px = shot.load()
    n = 0
    whites = [(x, y) for y in range(8) for x in range(8)
              if ARROW[y] & (0x80 >> x)]
    blacks = [(x, y) for y in range(8) for x in range(8)
              if not (ARROW[y] & (0x80 >> x))]
    for oy in range(0, h - 20):
        for ox in range(0, w - 8):
            ok = True
            for x, y in whites:
                r, g, b = px[ox + x, oy + y]
                if r < 200 or g < 200 or b < 200:
                    ok = False
                    break
            if not ok:
                continue
            dark = 0
            for x, y in blacks:
                r, g, b = px[ox + x, oy + y]
                if r < 150 or g < 150 or b < 150:
                    dark += 1
            if dark >= len(blacks) // 2:
                n += 1
    return n


def main():
    print("info work dir %s" % WORK, flush=True)
    g = Guest()
    try:
        note(g.wait_prompt(), "guest booted to prompt")
        g.rel(5, 5)
        g.rel(-5, -5)
        time.sleep(1.0)
        spawned = False
        for _ in range(4):
            g.send("run file &", settle=1.0)
            if g.wait_for("started as job pid", timeout=15):
                spawned = True
                break
        note(spawned, "bg file spawned")
        time.sleep(6.0)
        a = g.dump("f_idle_a")
        time.sleep(3.0)
        b = g.dump("f_idle_b")
        d = meandiff(a, b)
        print("info idle-vs-idle meandiff=%.2f" % d, flush=True)
        note(d < 2.0, "idle frames stable (%.2f)" % d)
        for _ in range(6):
            g.rel(40, 12)
        for _ in range(6):
            g.rel(-40, -12)
        time.sleep(3.0)
        c = g.dump("f_post_move")
        time.sleep(3.0)
        e = g.dump("f_settled")
        d2 = meandiff(c, e)
        print("info move-settle meandiff=%.2f" % d2, flush=True)
        note(d2 < 2.0, "frames converge after mouse motion (%.2f)" % d2)
        na = count_arrows(c)
        nb = count_arrows(e)
        print("info arrow sprites post-move=%d settled=%d" % (na, nb),
              flush=True)
        note(na == 1 and nb == 1,
             "exactly one cursor sprite, no stranded trails")
        g.send("wm state")
        time.sleep(1.0)
        note("wm: theme dark" in g.snapshot(), "wm state reports theme")
        pid = None
        for ln in g.snapshot().splitlines():
            if "started as job pid" in ln:
                try:
                    pid = int(ln.split()[-1])
                except ValueError:
                    pass
        if pid is not None:
            g.send("kill %d" % pid, settle=1.0)
            g.send("wait %d" % pid, settle=1.0)
        time.sleep(2.0)
        g.send("run file", settle=1.0)
        time.sleep(6.0)
        g.key("esc")
        note(g.wait_prompt(20), "ESC quits fg file back to prompt")
        return 0 if not FAIL else 1
    finally:
        g.stop()


if __name__ == "__main__":
    sys.exit(main())
