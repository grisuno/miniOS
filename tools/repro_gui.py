#!/usr/bin/env python3
"""repro_gui.py — reproduce the VGA/mouse state bug after ring-3 programs.

Boots MiniOS with a QMP socket (to inject PS/2 mouse motion into the guest)
and a pty serial console (to drive the shell), then runs a sequence of shell
commands and reports the mouse_state visible through `gfx` plus any kernel
EXCEPTION dump on the serial line. This is how the GUI-only bug (mouse
cursor vanishing / VGA crash after DOOM, SYS_SPAWN, etc.) is observed
without a physical display: the kernel desktop tick runs on the guest
framebuffer, and its failures surface on serial.

Usage: python3 tools/repro_gui.py send "micropython src/test.py" [send ...]
"""
import json
import os
import pty
import select
import socket
import subprocess
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
IMAGE = os.path.join(HERE, "..", "os.img")
QMP_SOCK = "/tmp/opencode/repro_qmp.sock"


def read_serial(master, timeout=1.0):
    out = b""
    while True:
        r, _, _ = select.select([master], [], [], timeout)
        if not r:
            break
        try:
            chunk = os.read(master, 4096)
        except OSError:
            break
        if not chunk:
            break
        out += chunk
    return out.decode("utf-8", "replace")


class QMP:
    def __init__(self, path):
        for _ in range(100):
            if os.path.exists(path):
                break
            time.sleep(0.05)
        self.sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        self.sock.connect(path)
        self.sock.settimeout(2)
        self._recv()  # QMP greeting
        self.cmd({"execute": "qmp_capabilities"})
        self._recv()

    def cmd(self, obj):
        self.sock.sendall(json.dumps(obj).encode() + b"\n")
        return self._recv()

    def _recv(self):
        buf = b""
        while True:
            try:
                chunk = self.sock.recv(65536)
            except socket.timeout:
                break
            if not chunk:
                break
            buf += chunk
            try:
                return json.loads(buf.decode())
            except json.JSONDecodeError:
                continue

    def mouse(self, dx=0, dy=0, left=None):
        events = []
        if dx or dy:
            events.append({"type": "rel", "data": {"axis": "x", "value": dx}})
            events.append({"type": "rel", "data": {"axis": "y", "value": dy}})
        if left is not None:
            events.append({"type": "btn", "data": {"button": "left", "down": left}})
        return self.cmd({"execute": "input-send-event", "arguments": {"events": events}})

    def key(self, qcode, down=True):
        return self.cmd({"execute": "input-send-event", "arguments": {
            "events": [{"type": "key", "data": {"down": down, "key": {"type": "qcode", "data": qcode}}}]}})


def main():
    commands = sys.argv[1:]
    master, slave = pty.openpty()
    proc = subprocess.Popen(
        ["qemu-system-x86_64", "-drive", f"file={IMAGE},format=raw,if=ide",
         "-m", "256M", "-nic", "user,model=rtl8139", "-display", "none",
         "-serial", os.ttyname(slave), "-qmp", f"unix:{QMP_SOCK},server=on,wait=off",
         "-no-reboot"],
        stdin=subprocess.DEVNULL,
    )
    try:
        # Wait for the shell prompt.
        boot = ""
        deadline = time.monotonic() + 60
        while time.monotonic() < deadline and "miniOS> " not in boot:
            boot += read_serial(master, 0.2)
        print("=== BOOT TAIL ===")
        print(boot[-800:])

        qmp = QMP(QMP_SOCK)

        def send(line):
            os.write(master, (line + "\n").encode())
            time.sleep(0.3)
            return read_serial(master, 1.5)

        def mouse_state():
            os.write(master, b"gfx\n")
            time.sleep(0.4)
            out = read_serial(master, 1.0)
            return out

        # Give the guest a mouse so present=1.
        print("=== INJECT MOUSE ===")
        qmp.mouse(dx=40, dy=30)
        time.sleep(0.3)
        print(mouse_state())

        for cmd in commands:
            print("=== SEND: %s ===" % cmd)
            out = send(cmd)
            print(out[-1500:])
            # A kernel fault surfaces as an EXCEPTION dump on serial.
            if "EXCEPTION" in out or "exception" in out:
                print("### KERNEL EXCEPTION DETECTED ###")

        print("=== MOUSE STATE AFTER ===")
        print(mouse_state())
    finally:
        proc.terminate()
        try:
            proc.wait(timeout=5)
        except Exception:
            proc.kill()
        os.close(master)
        os.close(slave)
        if os.path.exists(QMP_SOCK):
            os.unlink(QMP_SOCK)


if __name__ == "__main__":
    main()