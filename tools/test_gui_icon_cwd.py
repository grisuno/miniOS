#!/usr/bin/env python3
"""test_gui_icon_cwd.py -- GUI proof that dock launches ignore shell cwd.

Boots the real image, `cd cvm` over serial (the exact trap from the bug
report: `+set basedir .` resolving against the shell cwd), then clicks
the Quake 2 dock icon with a real relative-mouse walk. The icon target
is found by template-matching progs/icons/quake2.png in the dock strip
of a screendump, so no layout math can drift.

PASS: serial shows the engine loading (ref_soft / Map:) with no
`colormap.pcx` error. FAIL: the old `Couldn't load pics/colormap.pcx`.
Dumps stay in the printed work dir for eyeballing.
"""
import json
import os
import socket
import subprocess
import sys
import tempfile
import threading
import time

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.join(HERE, "..")
IMAGE = os.path.join(REPO, "os.img")
ICON = os.path.join(REPO, "progs", "icons", "quake2.png")
WORK = tempfile.mkdtemp(prefix="icon_cwd_")
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
        with open(HOLD, "wb") as f:
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

    def rel(self, dx, dy):
        self.qmp_cmd({"execute": "input-send-event", "arguments": {
            "events": [{"type": "rel", "data": {"axis": "x", "value": dx}},
                       {"type": "rel", "data": {"axis": "y",
                                                "value": dy}}]}})
        time.sleep(0.3)

    def click(self):
        self.qmp_cmd({"execute": "input-send-event", "arguments": {
            "events": [{"type": "btn", "data": {"button": "left",
                                                "down": True}}]}})
        time.sleep(0.5)
        self.qmp_cmd({"execute": "input-send-event", "arguments": {
            "events": [{"type": "btn", "data": {"button": "left",
                                                "down": False}}]}})
        time.sleep(0.5)

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
        for p in (QMP_SOCK, SER_SOCK):
            if os.path.exists(p):
                os.unlink(p)


def find_icon(shot_path, icon_path):
    """Center of the dock icon: global best template match, strict bar."""
    from PIL import Image, ImageDraw
    shot = Image.open(shot_path).convert("RGB")
    icon = Image.open(icon_path).convert("RGBA")
    fw, fh = shot.size
    iw, ih = icon.size
    tpl = [(x, y, icon.getpixel((x, y))[:3])
           for y in range(ih) for x in range(iw)
           if icon.getpixel((x, y))[3] >= 128]
    px = shot.load()
    best = None
    y0 = fh - 110
    for oy in range(y0, fh - ih):
        for ox in range(0, fw - iw):
            good = 0
            for x, y, (tr, tg, tb) in tpl:
                r, g, b = px[ox + x, oy + y]
                if abs(r - tr) + abs(g - tg) + abs(b - tb) <= 90:
                    good += 1
            score = good / len(tpl)
            if best is None or score > best[0]:
                best = (score, ox + iw // 2, oy + ih // 2, ox, oy)
    print("info best template score %.3f" % best[0], flush=True)
    if best[0] < 0.85:
        return None
    dbg = shot.copy()
    ImageDraw.Draw(dbg).rectangle(
        [best[3], best[4], best[3] + iw, best[4] + ih], outline="red")
    dbg.save(os.path.join(DUMPS, "icon_match.png"))
    return best[1], best[2]


def walk(g, tx, ty, fw, fh):
    """Relative walk from screen center (guest 2px per host unit)."""
    hx = (tx - fw // 2) // 2
    hy = (ty - fh // 2) // 2
    if True:
        steps = 8
        for i in range(steps):
            qx = hx // steps + (1 if i < hx % steps else 0) if hx >= 0 \
                else -((-hx) // steps + (1 if i < (-hx) % steps else 0))
            qy = hy // steps + (1 if i < hy % steps else 0) if hy >= 0 \
                else -((-hy) // steps + (1 if i < (-hy) % steps else 0))
            if qx or qy:
                g.rel(qx, qy)


def main():
    from PIL import Image
    os.makedirs(DUMPS, exist_ok=True)
    g = Guest()
    try:
        note(g.wait_prompt(), "guest booted to prompt")
        g.rel(5, 5)
        g.rel(-5, -5)
        time.sleep(1.2)
        g.send("cd cvm")
        g.send("pwd")
        cwd_ok = False
        for _ in range(10):
            time.sleep(1.0)
            if "cvm" in g.snapshot():
                cwd_ok = True
                break
        note(cwd_ok, "shell cwd is /cvm")
        shot = g.dump("icon_dock")
        fw, fh = Image.open(shot).size
        print("info framebuffer %dx%d" % (fw, fh), flush=True)
        tgt = find_icon(shot, ICON)
        note(tgt is not None, "quake2 dock icon found by template")
        if tgt is None:
            return 1
        print("info icon at %s" % (tgt,), flush=True)
        walk(g, tgt[0], tgt[1], fw, fh)
        time.sleep(0.5)
        g.click()
        ok = False
        bad = False
        end = time.time() + 240
        while time.time() < end:
            time.sleep(2.0)
            s = g.snapshot()
            if "colormap.pcx" in s:
                bad = True
                break
            if "ref_soft" in s or "Map:" in s:
                ok = True
                break
        note(not bad, "no colormap.pcx error after icon launch from /cvm")
        note(ok, "quake engine loading from icon launch")
        return 0 if (ok and not bad) else 1
    finally:
        g.stop()


if __name__ == "__main__":
    sys.exit(main() if not FAIL else 1)
