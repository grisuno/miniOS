#!/usr/bin/env python3
"""test_gui_wm.py -- GUI proof that graphics windows survive the WM.

Serial `wm` commands call the same functions as the real paths, but they
cannot prove what the user sees: a program blocked in read (vedit) stops
compositing, so any desktop redraw used to bury it until the next keypress.
This boots the real image headless (-display none), drives the shell over
stdio pipes, injects PS/2 through QMP and judges pixels with PIL:

  1. split terminals, run vedit (foreground, shell blocked)
  2. Alt+Tab -> vedit still painted (was: wiped until next key)
  3. Super+Tab -> vedit still painted after tiling
  4. quit, run vedit in background, click its taskbar button ->
     serial `wm state` reports focus 2 (the buried app comes back)

Fails loudly (exit 1) with the mean-abs-diff numbers. Dumps stay in
/tmp/opencode/ for eyeballing.
"""
import json
import os
import socket
import subprocess
import sys
import threading
import time

HERE = os.path.dirname(os.path.abspath(__file__))
IMAGE = os.path.join(HERE, "..", "os.img")
QMP_SOCK = "/tmp/opencode/gui_qmp.sock"
SER_SOCK = "/tmp/opencode/gui_ser.sock"
DUMPS = "/tmp/opencode"

FAIL = []


def note(ok, msg):
    print(("PASS " if ok else "FAIL ") + msg, flush=True)
    if not ok:
        FAIL.append(msg)


class Guest:
    def __init__(self):
        if os.path.exists(QMP_SOCK):
            os.unlink(QMP_SOCK)
        if os.path.exists(SER_SOCK):
            os.unlink(SER_SOCK)
        # Unix-socket serial: bidirectional and unbuffered (pipes make QEMU
        # block-buffer stdout; ptys EIO here). stdin is a held-open file,
        # never EOF (EOF on stdin exits QEMU silently).
        self._stdin_hold = open("/tmp/opencode/gui_stdin.hold", "rb")
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
        # The 16550 RX FIFO is 16 bytes: a burst line can lose its head
        # while the guest renders or loads (deterministic mangling like
        # "wm list" -> "m list"). Pace bytes ~8ms apart so the polling
        # shell always drains in time; the echo check resends as backstop
        # (shell is interactive at every send site in this test).
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

    def btn(self, down):
        self.qmp_cmd({"execute": "input-send-event", "arguments": {
            "events": [{"type": "btn", "data": {"button": "left",
                                                "down": down}}]}})
        time.sleep(0.5)

    def dump(self, name):
        p = os.path.join(DUMPS, name + ".png")
        self.qmp_cmd({"execute": "screendump",
                      "arguments": {"filename": p}})
        time.sleep(0.5)
        return p

    def stop(self):
        try:
            self._ser().sendall(b"poweroff\n")
        except Exception:
            pass
        time.sleep(3)
        try:
            self.proc.terminate()
            self.proc.wait(timeout=5)
        except Exception:
            self.proc.kill()
        try:
            self.ser.close()
        except Exception:
            pass
        if os.path.exists(QMP_SOCK):
            os.unlink(QMP_SOCK)
        if os.path.exists(SER_SOCK):
            os.unlink(SER_SOCK)


def meandiff(a_path, b_path):
    from PIL import Image, ImageChops, ImageStat
    a = Image.open(a_path).convert("RGB")
    b = Image.open(b_path).convert("RGB")
    if a.size != b.size:
        return float("inf"), a.size
    d = ImageChops.difference(a, b).convert("L")
    return ImageStat.Stat(d).mean[0], a.size


def main():
    os.makedirs(DUMPS, exist_ok=True)
    g = Guest()
    try:
        note(g.wait_prompt(), "guest booted to prompt")

        g.send("wm split")
        time.sleep(1.0)
        # Jiggle the mouse once: the desktop tick (taskbar clock, running-
        # app button) only runs after the first mouse packet sets present.
        g.rel(5, 5)
        g.rel(-5, -5)
        time.sleep(1.2)
        g.dump("wm_base")
        from PIL import Image
        fw, fh = Image.open(os.path.join(DUMPS, "wm_base.png")).size
        print("info framebuffer %dx%d" % (fw, fh), flush=True)

        g.send("run vedit.elf", settle=0.5)
        time.sleep(9.0)  # vedit boots, composites, blocks in read
        g.dump("wm_pre")

        d, _ = meandiff(os.path.join(DUMPS, "wm_pre.png"),
                        os.path.join(DUMPS, "wm_base.png"))
        print("info pre-vs-base meandiff=%.2f" % d, flush=True)
        note(d > 4.0, "vedit visibly painted (pre-vs-base %.2f)" % d)

        # Alt+Tab with alt held across the tab press.
        g.key("alt", down=True, up=False)
        g.key("tab")
        g.key("alt", down=False, up=True)
        time.sleep(1.5)
        g.dump("wm_alttab")
        d, _ = meandiff(os.path.join(DUMPS, "wm_alttab.png"),
                        os.path.join(DUMPS, "wm_pre.png"))
        print("info alttab-vs-pre meandiff=%.2f" % d, flush=True)
        note(d < 4.0, "vedit survives Alt+Tab (diff %.2f)" % d)

        g.key("meta_l", down=True, up=False)
        g.key("tab")
        g.key("meta_l", down=False, up=True)
        time.sleep(1.5)
        g.dump("wm_supertab")
        d, _ = meandiff(os.path.join(DUMPS, "wm_supertab.png"),
                        os.path.join(DUMPS, "wm_base.png"))
        print("info supertab-vs-base meandiff=%.2f" % d, flush=True)
        note(d > 10.0, "vedit still painted after Super+Tab (%.2f)" % d)

        # Quit vedit (Esc), shell returns; rerun in background for click.
        g.key("esc")
        note(g.wait_prompt(15), "shell back after vedit quit")
        time.sleep(2.0)

        # Spawn polling for the job line: a send that lands mid-redraw can
        # mangle, and the ELF load takes seconds.
        spawned = False
        for _ in range(4):
            g.send("run vedit.elf &", settle=1.0)
            for _ in range(15):
                time.sleep(1.0)
                if "started as job pid" in g.snapshot():
                    spawned = True
                    break
            if spawned:
                break
        note(spawned, "bg vedit spawned")
        # Wait for the first composite before asserting.
        framed = False
        for _ in range(20):
            g.send("gfx frames", settle=1.0)
            m = None
            for ln in g.snapshot().splitlines():
                if "frames composited" in ln:
                    try:
                        m = int(ln.split()[-1])
                    except ValueError:
                        pass
            if m is not None and m >= 1:
                framed = True
                break
            time.sleep(1.0)
        note(framed, "bg vedit composited its first frame")
        g.send("wm list")
        out = g.snapshot()
        tail = "\n".join(out.splitlines()[-8:])
        print("info wm list tail:\n" + tail, flush=True)
        note("win gfx" in out and "win gfxbtn" in out,
             "bg vedit composited with taskbar button")
        bx = bw = None
        for ln in out.splitlines():
            if "win gfxbtn" in ln:
                for tok in ln.split():
                    if tok.startswith("x="):
                        bx = int(tok[2:])
                    if tok.startswith("w="):
                        bw = int(tok[2:])
        note(bw is not None and bw > 0,
             "button geometry serial-readable (x=%s w=%s)" % (bx, bw))
        if bw is not None and bw > 0:
            from PIL import Image, ImageStat
            g.rel(3, 3)
            g.rel(-3, -3)
            time.sleep(1.2)
            g.dump("wm_btn")
            shot = Image.open(
                os.path.join(DUMPS, "wm_btn.png")).convert("RGB")
            btn = shot.crop((bx, fh - 8, bx + bw, fh))
            n = btn.size[0] * btn.size[1]
            grow = btn.crop((0, 0, 8, 8)).convert("L")
            varied = sum(1 for v in grow.getdata()
                         if abs(v - 40) > 25)
            print("info button icon varied px: %d/%d" % (varied, n),
                  flush=True)
            note(varied > 10, "taskbar button paints mini icon + title")
            # Mouse starts centered; guest moves 2px per host unit, and in
            # practice QMP +y goes down on screen. Walk in steps plus
            # remainder (Python floor-div/mod reconstruct negatives exactly).
            # NOTE: the two jiggles above moved the pointer (+3,-3 net
            # zero... in guest px: +6,-6 then back), so it is centered.
            cx = bx + bw // 2
            cy = fh - 4
            hx, hy = (cx - fw // 2) // 2, (cy - fh // 2) // 2
            for _ in range(8):
                g.rel(hx // 8, hy // 8)
            g.rel(hx - 8 * (hx // 8), hy - 8 * (hy // 8))
            # Separated press/release: a joint click can land in one tick.
            g.btn(True)
            g.btn(False)
            fresh = ""
            for _ in range(3):
                mark = len(g.snapshot())
                g.send("wm state", settle=1.5)
                for _ in range(10):
                    time.sleep(1.0)
                    fresh = g.snapshot()[mark:]
                    if "gfx-mode" in fresh:
                        break
                if "gfx-mode" in fresh:
                    break
            print("info wm state: %s" % [ln for ln in fresh.splitlines()
                                         if "focus" in ln], flush=True)
            note("focus 2" in fresh, "taskbar click focuses the gfx app")
    finally:
        g.stop()
    if FAIL:
        print("GUI FAILURES: %d" % len(FAIL), flush=True)
        return 1
    print("GUI ALL PASS", flush=True)
    return 0


if __name__ == "__main__":
    sys.exit(main())
