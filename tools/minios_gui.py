#!/usr/bin/env python3
"""minios_gui.py — inject VGA-mode input and capture the framebuffer.

Boots MiniOS with the emulated std VGA device (the linear framebuffer the
kernel's desktop renders into), a QMP socket to inject PS/2 mouse motion,
clicks and keyboard, and a pty serial console to drive the shell. After each
action it saves the current VGA framebuffer to a PNG via QMP `screendump`,
so a desktop crash, a vanished mouse cursor or a corrupted window is visible
without a physical display.

This is the tool for the VGA-mode bugs (mouse cursor vanishing, desktop
crash after a ring-3 program): it triggers real input events in the VGA
desktop and captures what the guest drew.

Usage:
  python3 tools/minios_gui.py [actions...]

Actions:
  send  LINE         send a shell line, wait for prompt
  mouse DX DY        inject relative mouse motion
  click              inject a left-button press+release
  key QCODE [up]     inject a keyboard key (qemu keycode, e.g. esc, return)
  dump NAME          screendump the VGA to /tmp/opencode/NAME.png
  sleep SECS         pause
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
QMP_SOCK = "/tmp/opencode/gui_qmp.sock"
DUMPS = "/tmp/opencode"
DISPLAY = os.environ.get("DISPLAY", ":0")


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
        for _ in range(200):
            if os.path.exists(path):
                break
            time.sleep(0.05)
        self.sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        self.sock.connect(path)
        self.sock.settimeout(3)
        self._recv()
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

    def mouse(self, dx=0, dy=0, click=False):
        events = []
        if dx or dy:
            events.append({"type": "rel", "data": {"axis": "x", "value": dx}})
            events.append({"type": "rel", "data": {"axis": "y", "value": dy}})
        if click:
            events += [{"type": "btn", "data": {"button": "left", "down": True}},
                       {"type": "btn", "data": {"button": "left", "down": False}}]
        return self.cmd({"execute": "input-send-event", "arguments": {"events": events}})

    def key(self, qcode, up=True):
        ev = [{"type": "key", "data": {"down": True, "key": {"type": "qcode", "data": qcode}}}]
        if up:
            ev.append({"type": "key", "data": {"down": False, "key": {"type": "qcode", "data": qcode}}})
        return self.cmd({"execute": "input-send-event", "arguments": {"events": ev}})

    def screendump(self, path):
        return self.cmd({"execute": "screendump", "arguments": {"filename": path}})


def main():
    args = sys.argv[1:]
    if not args:
        print(__doc__)
        return 1
    master, slave = pty.openpty()
    qemu = ["qemu-system-x86_64", "-drive", f"file={IMAGE},format=raw,if=ide",
            "-m", "256M", "-nic", "user,model=rtl8139", "-vga", "std",
            "-display", "sdl", "-serial", os.ttyname(slave),
            "-qmp", f"unix:{QMP_SOCK},server=on,wait=off", "-no-reboot"]
    env = dict(os.environ)
    env["DISPLAY"] = DISPLAY
    proc = subprocess.Popen(qemu, env=env)
    try:
        boot = ""
        while "miniOS> " not in boot:
            boot += read_serial(master, 0.2)
        q = QMP(QMP_SOCK)
        ACTIONS = {"send", "mouse", "click", "key", "dump", "sleep"}
        i = 0
        while i < len(args):
            a = args[i]
            if a == "send":
                i += 1
                parts = []
                while i < len(args) and args[i] not in ACTIONS:
                    parts.append(args[i]); i += 1
                line = " ".join(parts)
                os.write(master, (line + "\n").encode())
                time.sleep(0.4)
                print("SEND %s -> %s" % (line, read_serial(master, 1.5)[-500:].strip()))
            elif a == "mouse":
                q.mouse(int(args[i + 1]), int(args[i + 2])); i += 3
                time.sleep(0.3)
            elif a == "click":
                q.mouse(click=True); i += 1; time.sleep(0.3)
            elif a == "key":
                q.key(args[i + 1]); i += 2; time.sleep(0.3)
            elif a == "dump":
                p = os.path.join(DUMPS, args[i + 1] + ".png")
                q.screendump(p); i += 2
                print("DUMP %s" % p)
            elif a == "sleep":
                time.sleep(float(args[i + 1])); i += 2
            else:
                print("unknown action: %s" % a); i += 1
    finally:
        try:
            q.screendump(os.path.join(DUMPS, "final.png"))
        except Exception:
            pass
        proc.terminate()
        try:
            proc.wait(timeout=5)
        except Exception:
            proc.kill()
        os.close(master)
        os.close(slave)
        if os.path.exists(QMP_SOCK):
            os.unlink(QMP_SOCK)
    return 0


if __name__ == "__main__":
    sys.exit(main())