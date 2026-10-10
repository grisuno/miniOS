#!/usr/bin/env python3
"""test_gui_freedom.py -- GUI proof that freedom-gui takes real input.

The BDD scenario proves the full FreeDom GUI presents a frame; it cannot
prove that keys, chords, the clipboard and the mouse reach the browser
through the MiniOS platform layer (progs/freedomui/platform_minios.c and
ps2_keymap.c, docs/spec/network.md). This boots the real image headless
(-display none), drives the shell over a unix-socket serial, injects PS/2
through QMP and judges pixels with PIL plus the kernel clipboard:

  0. foreground run, the way a user (or the dock) starts it: the pointer
     parks on the wallpaper, bare `freedom-gui` runs as a process (process
     note), then the pointer moves over the idle browser
                                            -> the arrow follows (the
                                               desktop tick moves it while
                                               the app presents nothing)
                                            -> no dead arrow stays where it
                                               was parked
     serial Ctrl+C                          -> `exit code: 130`, prompt back
  1. `clip abc`, then `run freedom-gui &` until `freedom: frame ok`
  2. type `x` into the focused URL bar      -> URL bar pixels change
  3. Ctrl+V pastes the kernel clipboard     -> bar holds `xabc`
     Ctrl+C copies the bar back             -> `clip` prints `xabc`
  4. click the toolbar menu button          -> the menu panel paints

Usage:
  python3 tools/test_gui_freedom.py

Inputs: os.img in the repository root (built with freedom-gui on MiniFS).
Outputs: PASS/FAIL lines, the work dir with every dump, exit 0 when all
checks pass and 1 otherwise. Failure modes: guest never reaches the prompt,
freedom-gui never presents, a pixel diff stays under its threshold, or the
clipboard does not round-trip.
"""
import json
import os
import socket
import subprocess
import sys
import tempfile
import threading
import time


class Config:
    """Every tunable of the proof in one place."""
    HERE = os.path.dirname(os.path.abspath(__file__))
    IMAGE = os.path.join(HERE, "..", "os.img")
    MEM = os.environ.get("MEM", "1G")
    BOOT_TIMEOUT_S = 120
    FRAME_TIMEOUT_S = 60
    SERIAL_BYTE_GAP_S = 0.02
    SEND_SETTLE_S = 0.5
    QMP_SETTLE_S = 0.4
    KEY_SETTLE_S = 0.3
    INPUT_SETTLE_S = 1.5
    CLIP_SEED = "abc"
    TYPED_CHAR = "x"
    CLIP_EXPECTED = "xabc"
    MOUSE_UNIT_PX = 2
    MOUSE_STEPS = 8
    DIFF_TYPED_MIN = 2.0
    DIFF_MENU_MIN = 4.0
    # Content-local geometry of FreeDom's chrome at 800x360 without CSD:
    # the URL bar band and the menu button sit in the toolbar row below the
    # tab strip; the menu panel opens under the button's right edge.
    URLBAR_BOX = (150, 36, 700, 58)
    MENU_BUTTON = (776, 47)
    MENU_PANEL_BOX = (520, 64, 800, 300)
    # Foreground phase, screen pixels: the pointer parks on bare wallpaper
    # outside the centred browser window, the terminal and the dock, then
    # returns to the screen centre, which lies on the browser's page area.
    PARK_POINT = (60, 600)
    POINTER_BOX = 12
    POINTER_MOVED_MIN = 8
    STALE_ARROW_MAX = 0
    FG_SETTLE_S = 6.0
    FG_EXIT_CODE = "exit code: 130"


FAIL = []


def note(ok, msg):
    """Print one PASS/FAIL line and remember failures."""
    print(("PASS " if ok else "FAIL ") + msg, flush=True)
    if not ok:
        FAIL.append(msg)


class Guest:
    """QEMU guest with a unix-socket serial console and a QMP socket."""

    def __init__(self, work):
        self.work = work
        self.qmp_sock = os.path.join(work, "qmp.sock")
        self.ser_sock = os.path.join(work, "ser.sock")
        hold = os.path.join(work, "stdin.hold")
        with open(hold, "wb"):
            pass
        self._stdin_hold = open(hold, "rb")
        qemu = ["qemu-system-x86_64", "-drive",
                "file=%s,format=raw,if=ide" % Config.IMAGE,
                "-m", Config.MEM, "-nic", "user,model=rtl8139", "-vga", "std",
                "-display", "none",
                "-serial", "unix:%s,server=on,wait=off" % self.ser_sock,
                "-qmp", "unix:%s,server=on,wait=off" % self.qmp_sock,
                "-no-reboot"]
        self.proc = subprocess.Popen(qemu, stdin=self._stdin_hold,
                                     stdout=subprocess.DEVNULL,
                                     stderr=subprocess.DEVNULL)
        self.ser = None
        self.qmp = None
        self.out = b""
        self.lock = threading.Lock()
        threading.Thread(target=self._reader, daemon=True).start()

    def _connect(self, path):
        for _ in range(200):
            if os.path.exists(path):
                break
            time.sleep(0.05)
        s = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        s.connect(path)
        return s

    def _serial(self):
        if self.ser is None:
            self.ser = self._connect(self.ser_sock)
        return self.ser

    def _reader(self):
        while True:
            try:
                chunk = self._serial().recv(4096)
            except OSError:
                return
            if not chunk:
                return
            with self.lock:
                self.out += chunk

    def snapshot(self):
        with self.lock:
            return self.out.decode("utf-8", "replace")

    def wait_for(self, text, timeout, since=0):
        """Wait for text in the console output past offset `since`."""
        end = time.time() + timeout
        while time.time() < end:
            if text in self.snapshot()[since:]:
                return True
            time.sleep(0.5)
        return False

    def send(self, line, settle=Config.SEND_SETTLE_S):
        """Pace bytes so the 16-byte UART FIFO never drops a line head."""
        for _ in range(4):
            for ch in line + "\n":
                self._serial().sendall(ch.encode())
                time.sleep(Config.SERIAL_BYTE_GAP_S)
            time.sleep(settle)
            if line in self.snapshot()[-2000:]:
                return
            time.sleep(0.5)

    def qmp_cmd(self, obj):
        if self.qmp is None:
            self.qmp = self._connect(self.qmp_sock)
            self.qmp.settimeout(4)
            self._qmp({"execute": "qmp_capabilities"})
        return self._qmp(obj)

    def _qmp(self, obj):
        self.qmp.sendall(json.dumps(obj).encode() + b"\n")
        time.sleep(Config.QMP_SETTLE_S)
        try:
            return self.qmp.recv(65536)
        except OSError:
            return b""

    def keys(self, events):
        """events: list of (qcode, down) pairs sent in one batch each."""
        for qcode, down in events:
            self.qmp_cmd({"execute": "input-send-event", "arguments": {
                "events": [{"type": "key", "data": {"down": down, "key": {
                    "type": "qcode", "data": qcode}}}]}})
            time.sleep(Config.KEY_SETTLE_S)

    def tap(self, qcode):
        self.keys([(qcode, True), (qcode, False)])

    def chord(self, mod, qcode):
        self.keys([(mod, True), (qcode, True), (qcode, False), (mod, False)])

    def rel(self, dx, dy):
        self.qmp_cmd({"execute": "input-send-event", "arguments": {
            "events": [{"type": "rel", "data": {"axis": "x", "value": dx}},
                       {"type": "rel", "data": {"axis": "y", "value": dy}}]}})

    def button(self, down):
        self.qmp_cmd({"execute": "input-send-event", "arguments": {
            "events": [{"type": "btn", "data": {"button": "left",
                                                "down": down}}]}})
        time.sleep(Config.SEND_SETTLE_S)

    def dump(self, name):
        path = os.path.join(self.work, name + ".png")
        self.qmp_cmd({"execute": "screendump", "arguments": {"filename": path}})
        time.sleep(Config.SEND_SETTLE_S)
        return path

    def stop(self):
        try:
            self._serial().sendall(b"poweroff\n")
        except OSError:
            pass
        time.sleep(3)
        try:
            self.proc.terminate()
            self.proc.wait(timeout=5)
        except Exception:
            self.proc.kill()
        for s in (self.ser, self.qmp):
            try:
                if s is not None:
                    s.close()
            except OSError:
                pass


def region_diff(a_path, b_path, box):
    """Mean absolute luminance difference of one region of two dumps."""
    from PIL import Image, ImageChops, ImageStat
    a = Image.open(a_path).convert("RGB").crop(box)
    b = Image.open(b_path).convert("RGB").crop(box)
    return ImageStat.Stat(ImageChops.difference(a, b).convert("L")).mean[0]


def content_origin(listing):
    """Parse `wm list` for the gfx window's content origin (cx, cy)."""
    for line in listing.splitlines():
        if line.startswith("win gfx ") and " cx=" in line:
            fields = dict(tok.split("=", 1) for tok in line.split() if "=" in tok)
            return int(fields["cx"]), int(fields["cy"])
    return None


def changed_pixels(a_path, b_path, box):
    """Pixels of one region that differ between two dumps."""
    from PIL import Image, ImageChops
    a = Image.open(a_path).convert("RGB").crop(box)
    b = Image.open(b_path).convert("RGB").crop(box)
    r, g, bl = ImageChops.difference(a, b).split()
    peak = ImageChops.lighter(ImageChops.lighter(r, g), bl)
    return peak.size[0] * peak.size[1] - peak.histogram()[0]


def around(point):
    """Square region of Config.POINTER_BOX pixels from a pointer's tip."""
    x, y = point
    return (x, y, x + Config.POINTER_BOX, y + Config.POINTER_BOX)


def walk(g, delta):
    """Move the pointer by a screen-pixel delta in MOUSE_STEPS slices."""
    hx = delta[0] // Config.MOUSE_UNIT_PX
    hy = delta[1] // Config.MOUSE_UNIT_PX
    for _ in range(Config.MOUSE_STEPS):
        g.rel(hx // Config.MOUSE_STEPS, hy // Config.MOUSE_STEPS)
    g.rel(hx - Config.MOUSE_STEPS * (hx // Config.MOUSE_STEPS),
          hy - Config.MOUSE_STEPS * (hy // Config.MOUSE_STEPS))
    time.sleep(Config.INPUT_SETTLE_S)


def foreground_phase(g):
    """Bare `freedom-gui` in the foreground with the pointer in use: the
    arrow follows over the idle window, leaves no dead sprite on the
    wallpaper, and serial Ctrl+C ends the run with the prompt back. The
    pointer ends at the screen centre, where move_to expects it."""
    from PIL import Image
    desk = g.dump("fg_desk")
    fw, fh = Image.open(desk).size
    centre = (fw // 2, fh // 2)
    park = Config.PARK_POINT
    walk(g, (park[0] - centre[0], park[1] - centre[1]))
    mark = len(g.snapshot())
    g.send("freedom-gui", settle=1.0)
    note(g.wait_for("freedom: frame ok", Config.FRAME_TIMEOUT_S, mark),
         "foreground freedom-gui presented its first frame")
    time.sleep(Config.FG_SETTLE_S)
    idle = g.dump("fg_idle")
    walk(g, (centre[0] - park[0], centre[1] - park[1]))
    moved = g.dump("fg_moved")
    n = changed_pixels(idle, moved, around(centre))
    note(n >= Config.POINTER_MOVED_MIN,
         "pointer follows over the idle foreground window (%d px)" % n)
    n = changed_pixels(desk, moved, around(park))
    note(n <= Config.STALE_ARROW_MAX,
         "no dead arrow left where the pointer was parked (%d px)" % n)
    mark = len(g.snapshot())
    g._serial().sendall(b"\x03")
    note(g.wait_for(Config.FG_EXIT_CODE, Config.FRAME_TIMEOUT_S, mark),
         "serial Ctrl+C ends the foreground run (%s)" % Config.FG_EXIT_CODE)
    time.sleep(Config.INPUT_SETTLE_S)


def screen_box(origin, box):
    ox, oy = origin
    return (ox + box[0], oy + box[1], ox + box[2], oy + box[3])


def move_to(g, frame_size, target):
    """Walk the pointer from the screen centre (where it starts) to target."""
    fw, fh = frame_size
    walk(g, (target[0] - fw // 2, target[1] - fh // 2))


def main():
    from PIL import Image
    work = tempfile.mkdtemp(prefix="gui_fd_")
    print("info work dir %s" % work, flush=True)
    g = Guest(work)
    try:
        note(g.wait_for("miniOS> ", Config.BOOT_TIMEOUT_S), "guest booted to prompt")
        foreground_phase(g)
        g.send("clip %s" % Config.CLIP_SEED)
        mark = len(g.snapshot())
        g.send("run freedom-gui &", settle=1.0)
        note(g.wait_for("freedom: frame ok", Config.FRAME_TIMEOUT_S, mark),
             "freedom-gui presented its first frame")
        time.sleep(Config.INPUT_SETTLE_S)
        mark = len(g.snapshot())
        g.send("wm list", settle=2.0)
        origin = content_origin(g.snapshot()[mark:])
        note(origin is not None, "wm list reports the content origin %s" % (origin,))
        if origin is None:
            return 1
        base = g.dump("base")
        frame_size = Image.open(base).size

        g.tap(Config.TYPED_CHAR)
        time.sleep(Config.INPUT_SETTLE_S)
        typed = g.dump("typed")
        d = region_diff(base, typed, screen_box(origin, Config.URLBAR_BOX))
        note(d > Config.DIFF_TYPED_MIN, "typed key reaches the URL bar (diff %.2f)" % d)

        g.chord("ctrl", "v")
        g.chord("ctrl", "c")
        time.sleep(Config.INPUT_SETTLE_S)
        g.dump("pasted")

        move_to(g, frame_size, (origin[0] + Config.MENU_BUTTON[0],
                                origin[1] + Config.MENU_BUTTON[1]))
        g.button(True)
        g.button(False)
        time.sleep(Config.INPUT_SETTLE_S)
        menu = g.dump("menu")
        d = region_diff(typed, menu, screen_box(origin, Config.MENU_PANEL_BOX))
        note(d > Config.DIFF_MENU_MIN, "click opens the toolbar menu (diff %.2f)" % d)

        g.send("kill 1", settle=1.5)
        g.send("wait", settle=1.5)
        mark = len(g.snapshot())
        g.send("clip", settle=1.5)
        lines = [ln.strip() for ln in g.snapshot()[mark:].splitlines()]
        note(Config.CLIP_EXPECTED in lines,
             "Ctrl+V pasted and Ctrl+C copied back (clip: %s)" % lines[1:3])
    finally:
        g.stop()
    if FAIL:
        print("GUI FAILURES: %d" % len(FAIL), flush=True)
        return 1
    print("GUI ALL PASS", flush=True)
    return 0


if __name__ == "__main__":
    sys.exit(main())
