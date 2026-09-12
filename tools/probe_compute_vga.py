#!/usr/bin/env python3
# Docstring: VGA liveness probe during CPU-bound ring-3 compute.
# Boots os.img headless, runs a command, moves the PS/2 mouse through QMP
# mid-run and screendumps. A live guest repaints cursor and clock even
# while a ring-3 loop never blocks: consecutive dumps must differ.
# Usage: tools/probe_compute_vga.py "<guest cmd>" [settle_secs]
import json
import os
import socket
import subprocess
import sys
import tempfile
import time

HERE = os.path.dirname(os.path.abspath(__file__)) + "/.."
WORK = tempfile.mkdtemp(prefix="probe_vga_")
QMP = os.path.join(WORK, "qmp.sock")
SER = os.path.join(WORK, "ser.sock")
HOLD = os.path.join(WORK, "stdin.hold")


def main():
    cmd = sys.argv[1] if len(sys.argv) > 1 else "echo hi"
    settle = int(sys.argv[2]) if len(sys.argv) > 2 else 30
    for p in (QMP, SER):
        if os.path.exists(p):
            os.unlink(p)
    open(HOLD, "ab").close()
    hold = open(HOLD, "rb")
    proc = subprocess.Popen(
        ["qemu-system-x86_64", "-drive",
         "file=%s/os.img,format=raw,if=ide" % HERE,
         "-m", "1G", "-nic", "user,model=rtl8139", "-vga", "std",
         "-display", "none",
         "-serial", "unix:%s,server=on,wait=off" % SER,
         "-qmp", "unix:%s,server=on,wait=off" % QMP, "-no-reboot"],
        stdin=hold, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    try:
        ser = None
        for _ in range(300):
            try:
                if os.path.exists(SER):
                    s = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
                    s.connect(SER)
                    s.settimeout(1.0)
                    ser = s
                    break
            except OSError:
                time.sleep(0.1)
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
            global out
            nonlocal ser
            end = time.time() + timeout
            while time.time() < end:
                try:
                    c = ser.recv(4096)
                except socket.timeout:
                    continue
                if c:
                    out += c

        end = time.time() + 120
        while time.time() < end:
            poll(5)
            if b"miniOS> " in out:
                break
        send(cmd)
        time.sleep(settle)
        qs = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        qs.connect(QMP)
        qf = qs.makefile("rwb")
        qf.readline()
        qf.write(b'{"execute": "qmp_capabilities"}\n')
        qf.flush()
        qf.readline()

        def qmp(obj):
            qf.write((json.dumps(obj) + "\n").encode())
            qf.flush()
            time.sleep(0.4)
            try:
                return qf.readline()
            except Exception:
                return b""

        def rel(dx, dy):
            qmp({"execute": "input-send-event", "arguments": {
                "events": [{"type": "rel", "data": {"axis": "x", "value": dx}},
                           {"type": "rel", "data": {"axis": "y",
                                                    "value": dy}}]}})
            time.sleep(0.3)

        def dump(name):
            qmp({"execute": "screendump",
                 "arguments": {"filename": os.path.join(WORK, "probe_%s.ppm" % name),
                               "format": "ppm"}})
            time.sleep(0.5)

        rel(150, 0)
        time.sleep(2)
        dump("a")
        rel(0, 150)
        time.sleep(2)
        dump("b")
        from PIL import Image, ImageChops
        a = Image.open(os.path.join(WORK, "probe_a.ppm")).convert("RGB")
        b = Image.open(os.path.join(WORK, "probe_b.ppm")).convert("RGB")
        bb = ImageChops.difference(a, b).convert("L").point(
            lambda v: 255 if v > 10 else 0).getbbox()
        print("diffbbox", bb)
        print("PASS live" if bb else "FAIL frozen")
        try:
            ser.sendall(b"poweroff\n")
        except OSError:
            pass
        time.sleep(4)
        return 0 if bb else 1
    finally:
        if proc.poll() is None:
            proc.kill()


if __name__ == "__main__":
    sys.exit(main())
