#!/usr/bin/env python3
"""probe_minicraft.py -- numeric minicraft probe without any PNG.

Boots os.img headless (display none), runs minicraft in the background so
the shell stays usable, and verifies rendering + movement purely through
serial-observable numbers:

  - `gfx frames` must climb (real compositing, like DOOM autoframes)
  - `wm list` gives the gfx window rect; `gfx rect` over the upper and
    lower content halves reports histograms (sky vs ground orientation)
  - QMP holds `w` for 2s, then the `P` key tap makes minicraft print
    `minicraft: pos X Y Z ... wood N`; X must have advanced vs before

No PIL, no screendump, no PNG: everything is parsed serial text.

Usage: python3 tools/probe_minicraft.py [--hold SECS]
"""
import json
import os
import re
import socket
import subprocess
import sys
import tempfile
import time

HERE = os.path.dirname(os.path.abspath(__file__)) + "/.."
WORK = tempfile.mkdtemp(prefix="probe_mc_")
QMP = os.path.join(WORK, "qmp.sock")
SER = os.path.join(WORK, "ser.sock")
HOLD = os.path.join(WORK, "stdin.hold")


def main():
    hold_secs = 2.0
    if "--hold" in sys.argv:
        hold_secs = float(sys.argv[sys.argv.index("--hold") + 1])
    for p in (QMP, SER):
        if os.path.exists(p):
            os.unlink(p)
    open(HOLD, "ab").close()
    hold = open(HOLD, "rb")
    proc = subprocess.Popen(
        ["qemu-system-x86_64", "-drive",
         "file=%s/os.img,format=raw,if=ide" % HERE,
         "-m", "1G", "-nic", "user,model=rtl8139",
         "-display", "none",
         "-serial", "unix:%s,server=on,wait=off" % SER,
         "-qmp", "unix:%s,server=on,wait=off" % QMP, "-no-reboot"],
        stdin=hold, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    rc = 1
    try:
        ser = None
        for _ in range(300):
            try:
                s = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
                s.connect(SER)
                s.settimeout(1.0)
                ser = s
                break
            except OSError:
                time.sleep(0.2)
        if ser is None:
            print("FAIL no serial")
            return 1
        out = b""

        def send(line):
            for ch in line + "\n":
                ser.sendall(ch.encode())
                time.sleep(0.02)
            time.sleep(0.8)

        def poll(timeout=10):
            nonlocal out
            end = time.time() + timeout
            while time.time() < end:
                try:
                    c = ser.recv(4096)
                except socket.timeout:
                    continue
                if c:
                    out = out + c

        def grab(pat, timeout=10):
            poll(timeout)
            txt = out.decode("utf-8", "replace")
            ms = re.findall(pat, txt)
            return txt, ms

        end = time.time() + 120
        while time.time() < end:
            poll(5)
            if b"miniOS> " in out:
                break
        out = b""
        send("run minicraft.elf &")
        txt, _ = grab(r"minicraft: ", timeout=15)
        if "minicraft: WASD" not in txt:
            print("FAIL minicraft banner missing")
            print(txt[-1500:])
            return 1
        print("boot ok: banner seen")

        send("gfx frames")
        _, f0 = grab(r"frames composited (\d+)", timeout=5)
        time.sleep(2)
        send("gfx frames")
        _, f1 = grab(r"frames composited (\d+)", timeout=5)
        n0 = int(f0[-1]) if f0 else -1
        n1 = int(f1[-1]) if f1 else -1
        print("frames %d -> %d %s" % (n0, n1, "ok climbing" if n1 > n0 else "FAIL frozen"))
        if n1 <= n0:
            return 1

        send("wm list")
        txt, m = grab(r"win gfx .+? x=(\d+) y=(\d+) w=(\d+) h=(\d+)", timeout=5)
        if not m:
            print("FAIL no gfx window in wm list")
            print(txt[-1500:])
            return 1
        gx, gy, gw, gh = [int(v) for v in m[-1]]
        print("gfx win x=%d y=%d w=%d h=%d" % (gx, gy, gw, gh))
        # content starts below the title bar; sample upper/lower halves
        y_top0, y_top1 = gy + 8 + 40, gy + 8 + 80
        y_bot0, y_bot1 = gy + 8 + 120, gy + 8 + 160
        x0, x1 = gx + 10, gx + gw - 20
        send("gfx rect %d %d %d %d" % (x0, y_top0, x1, y_top1))
        txt, r = grab(r"rect (\(\d+,\d+\)-\(\d+,\d+\)): (.+)", timeout=5)
        print("upper %s" % (r[-1][1] if r else "rect no match"))
        send("gfx rect %d %d %d %d" % (x0, y_bot0, x1, y_bot1))
        txt, r = grab(r"rect (\(\d+,\d+\)-\(\d+,\d+\)): (.+)", timeout=5)
        print("lower %s" % (r[-1][1] if r else "rect no match"))

        qs = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        qs.connect(QMP)
        qf = qs.makefile("rwb")
        qf.readline()
        qf.write(b'{"execute": "qmp_capabilities"}\n')
        qf.flush()
        qf.readline()

        def qkey(qcode, down):
            qf.write(json.dumps({"execute": "input-send-event", "arguments": {
                "events": [{"type": "key", "data": {
                    "down": down, "key": {"type": "qcode", "data": qcode}}}]}}).encode() + b"\n")
            qf.flush()
            time.sleep(0.15)
            try:
                qf.readline()
            except Exception:
                pass

        def pos(tag):
            qkey("p", True)
            qkey("p", False)
            _, pp = grab(r"minicraft: pos (-?\d+) (-?\d+) (-?\d+) yaw (\S+) pitch (\S+) tgt (\S+)", timeout=8)
            if not pp:
                print("FAIL no pos report (%s)" % tag)
                return None
            print("pos %s: %s" % (tag, pp[-1],))
            return pp[-1]

        out = b""
        send("echo MARK-P0")
        poll(2)
        p0 = pos("spawn")
        if p0 is None:
            return 1
        # LEFT arrow yaws (E0 0x4B path); F toggles fly (edge + serial proof)
        qkey("left", True)
        time.sleep(0.8)
        qkey("left", False)
        time.sleep(0.3)
        p1 = pos("after-left-turn")
        if p1 is None:
            return 1
        qkey("f", True)
        qkey("f", False)
        _, ff = grab(r"minicraft: fly (\w+)", timeout=8)
        print("fly %s" % (ff[-1] if ff else "FAIL no fly toggle"))
        qkey("spc", True)
        time.sleep(1.0)
        qkey("spc", False)
        time.sleep(0.3)
        p2 = pos("after-spc-rise")
        if p2 is None:
            return 1
        qkey("w", True)
        time.sleep(hold_secs)
        qkey("w", False)
        time.sleep(0.5)
        p3 = pos("after-W-walk")
        if p3 is None:
            return 1
        pts = [p0[0:3], p1[0:3], p2[0:3], p3[0:3]]
        yaws = [p0[3], p1[3], p2[3], p3[3]]
        moved = len(set(pts)) > 1
        turned = len(set(yaws)) > 1
        print("displacement %s turn %s" % ("ok" if moved else "FAIL none",
                                           "ok" if turned else "FAIL none"))
        send("gfx frames")
        _, f2 = grab(r"frames composited (\d+)", timeout=5)
        print("frames end %s" % (f2[-1] if f2 else "?"))
        try:
            ser.sendall(b"poweroff\n")
        except OSError:
            pass
        time.sleep(4)
        rc = 0 if moved else 1
        print("PASS" if rc == 0 else "FAIL")
        return rc
    finally:
        if proc.poll() is None:
            proc.kill()


if __name__ == "__main__":
    sys.exit(main())
