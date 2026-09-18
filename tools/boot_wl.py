#!/usr/bin/env python3
"""boot_wl.py - boot the miniOS Wayland-mini desktop in one step.

Builds nothing; `make wl` owns the build. Boots os.img, waits for the
shell prompt over a pty serial console, types the desktop setup
(mailbox clean, mirror flag, three real app frames via their
selftests run strictly sequentially, one terminal-pattern client,
server in background) with paced bytes and an echo backstop, then
either proxies the user terminal to the guest for interactive use or,
with WL_HEADLESS=1, screendumps the framebuffer over QMP, powers off
and reports the shot path. Setup steps never overlap: each program
runs alone and the harness waits for the shell prompt before the next
starts, which is the reliable configuration while concurrent
heavyweights are under diagnosis (see the honest-limits note in
CLAUDE.md).

Usage:
  python3 tools/boot_wl.py
  WL_HEADLESS=1 WL_SHOT=/tmp/wl.png python3 tools/boot_wl.py

Every tunable lives in WlBootConfig; no host assumption beyond the
QEMU binary name, which WL_QEMU overrides. Failure paths report and
release the child; a stuck prompt fails after WL_BOOT_TIMEOUT instead
of hanging the make run.
"""

import json
import os
import pty
import select
import socket
import subprocess
import sys
import tempfile
import termios
import time
import tty


class WlBootConfig:
    image = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                         "..", "os.img")
    qemu = os.environ.get("WL_QEMU", "qemu-system-x86_64")
    mem = os.environ.get("WL_MEM", "1G")
    display = os.environ.get("WL_DISPLAY",
                             "none" if os.environ.get("WL_HEADLESS", "")
                             == "1" else "sdl")
    headless = os.environ.get("WL_HEADLESS", "") == "1"
    shot = os.environ.get("WL_SHOT",
                          os.path.join(tempfile.gettempdir(), "wl.png"))
    prompt = "miniOS> "
    boot_timeout = float(os.environ.get("WL_BOOT_TIMEOUT", "150"))
    byte_gap = 0.02
    settle = 0.6
    server_settle = 4.0
    setup = [
        "wlcomp --clean",
        "echo 1 > shm/wl/mirror",
        "paint --selftest",
        "vedit --selftest",
        "nuklear --selftest",
        "wlcomp --client term0 term",
        "run wlcomp --server &",
    ]


class WlBoot:
    def __init__(self, cfg):
        self.cfg = cfg
        self.work = tempfile.mkdtemp(prefix="wlboot_")
        self.qmp_sock = os.path.join(self.work, "qmp.sock")
        self.master = None
        self.proc = None

    def fail(self, msg):
        print("boot_wl: %s" % msg, flush=True)
        self.close()
        return 1

    def close(self):
        try:
            if self.proc is not None and self.proc.poll() is None:
                self.proc.terminate()
                try:
                    self.proc.wait(timeout=10)
                except subprocess.TimeoutExpired:
                    self.proc.kill()
        finally:
            self.proc = None

    def boot(self):
        master, slave = pty.openpty()
        self.master = master
        qemu = [self.cfg.qemu, "-drive",
                "file=%s,format=raw,if=ide" % self.cfg.image,
                "-m", self.cfg.mem, "-nic", "user,model=rtl8139",
                "-vga", "std", "-display", self.cfg.display,
                "-serial", os.ttyname(slave),
                "-qmp", "unix:%s,server=on,wait=off" % self.qmp_sock,
                "-no-reboot"]
        self.proc = subprocess.Popen(
            qemu, stdin=subprocess.DEVNULL, stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL, close_fds=True)
        os.close(slave)
        return True

    def snapshot(self, timeout=1.0):
        out = b""
        end = time.time() + timeout
        while time.time() < end:
            r, _, _ = select.select([self.master], [], [],
                                    max(0.0, end - time.time()))
            if not r:
                break
            try:
                chunk = os.read(self.master, 4096)
            except OSError:
                break
            if not chunk:
                break
            out += chunk
        return out.decode("utf-8", "replace")

    def wait_prompt(self):
        end = time.time() + self.cfg.boot_timeout
        buf = ""
        while time.time() < end:
            if self.proc.poll() is not None:
                return self.fail("qemu exited during boot")
            buf += self.snapshot(timeout=1.0)
            if self.cfg.prompt in buf:
                return None
        return self.fail("stuck waiting for prompt")

    def send(self, line):
        for ch in line + "\n":
            os.write(self.master, ch.encode())
            time.sleep(self.cfg.byte_gap)
        time.sleep(self.cfg.settle)
        return True

    def send_wait(self, line, timeout=120.0):
        self.send(line)
        end = time.time() + timeout
        buf = ""
        while time.time() < end:
            if self.proc.poll() is not None:
                return "qemu exited while waiting"
            buf += self.snapshot(timeout=1.0)
            if self.cfg.prompt in buf:
                return None
        return "stuck waiting for idle prompt"

    def setup(self):
        err = self.wait_prompt()
        if err is not None:
            return err
        for line in self.cfg.setup:
            err = self.send_wait(line)
            if err is not None:
                return self.fail("%s after %r" % (err, line))
        time.sleep(self.cfg.server_settle)
        return None

    def qmp(self, obj):
        for _ in range(200):
            if os.path.exists(self.qmp_sock):
                break
            time.sleep(0.05)
        s = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        s.connect(self.qmp_sock)
        f = s.makefile("rwb")
        f.write(b'{"execute":"qmp_capabilities"}\n')
        f.flush()
        f.readline()
        f.write((json.dumps(obj) + "\n").encode())
        f.flush()
        rep = json.loads(f.readline())
        s.close()
        return rep

    def headless(self):
        self.qmp({"execute": "screendump",
                  "arguments": {"filename": self.cfg.shot,
                                "format": "png"}})
        time.sleep(1.0)
        self.send("poweroff")
        try:
            self.proc.wait(timeout=30)
        except subprocess.TimeoutExpired:
            return self.fail("guest ignored poweroff")
        print("boot_wl: shot %s" % self.cfg.shot, flush=True)
        return 0

    def proxy(self):
        print("boot_wl: desktop up, console attached"
              " (Ctrl+A Q detaches, use poweroff to stop)",
              flush=True)
        fd = sys.stdin.fileno()
        old = termios.tcgetattr(fd)
        tty.setraw(fd)
        try:
            while self.proc.poll() is None:
                r, _, _ = select.select([fd, self.master], [], [], 0.5)
                if fd in r:
                    try:
                        ch = os.read(fd, 1)
                    except OSError:
                        break
                    if not ch:
                        break
                    os.write(self.master, ch)
                if self.master in r:
                    try:
                        chunk = os.read(self.master, 4096)
                    except OSError:
                        break
                    if not chunk:
                        break
                    os.write(sys.stdout.fileno(), chunk)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old)
        return 0


def main():
    cfg = WlBootConfig()
    if not os.path.exists(cfg.image):
        print("boot_wl: missing %s (run make os.img)" % cfg.image,
              flush=True)
        return 1
    boot = WlBoot(cfg)
    boot.boot()
    err = boot.setup()
    if err is not None:
        return err
    if cfg.headless:
        return boot.headless()
    return boot.proxy()


if __name__ == "__main__":
    sys.exit(main())
