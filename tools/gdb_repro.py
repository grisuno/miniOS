#!/usr/bin/env python3
"""gdb_repro.py — drive a graphics-program sequence under the GDB stub.

Boots MiniOS with the gdb server (-s), a QMP socket for keyboard/mouse
injection and a pty serial console, attaches gdb with a conditional
breakpoint on the page-fault handler (isr_dispatch, vector 14), then drives
a sequence of graphics programs. When a page fault fires, gdb dumps the trap
frame (rip/rsp/cr2 = faulting address = FS base + offset) and exits.
"""
import os
import pty
import select
import socket
import subprocess
import time
import importlib.util

spec = importlib.util.spec_from_file_location("g", "tools/minios_gui.py")
g = importlib.util.module_from_spec(spec)
spec.loader.exec_module(g)


def rs(m, t=0.8):
    return g.read_serial(m, t)


def main():
    master, slave = pty.openpty()
    qemu = subprocess.Popen(
        ["qemu-system-x86_64", "-drive", "file=os.img,format=raw,if=ide",
         "-m", "256M", "-nic", "user,model=rtl8139", "-vga", "std",
         "-display", "sdl", "-serial", os.ttyname(slave),
         "-qmp", "unix:%s,server=on,wait=off" % g.QMP_SOCK, "-s", "-no-reboot"],
        env=dict(os.environ))
    try:
        boot = ""
        while "miniOS> " not in boot:
            boot += rs(master, 0.2)
        print("BOOTED")
        q = g.QMP(g.QMP_SOCK)

        # gdb command file: break on page fault, dump, continue.
        with open("/tmp/opencode/gdb_cmds.txt", "w") as f:
            f.write("set pagination off\n"
                    "set confirm off\n"
                    "target remote :1234\n"
                    "symbol-file kernel.elf\n"
                    "b isr_dispatch if $rdi == 14\n"
                    "commands\n"
                    " silent\n"
                    " printf \"\\n### GDB PAGE FAULT vec=%d frame=%p ###\\n\", $rdi, $rsi\n"
                    " set $f = (long)$rsi\n"
                    " printf \"rip=%lx rsp=%lx cr2=%lx\\n\", *(long*)($f+120), *(long*)($f+144), $cr2\n"
                    " x/5i *(long*)($f+120)\n"
                    " printf \"### end ###\\n\"\n"
                    " quit\n"
                    "end\n"
                    "continue\n")
        gdblog = open("/tmp/opencode/gdb.out", "w")
        gd = subprocess.Popen(["gdb", "-q", "-x", "/tmp/opencode/gdb_cmds.txt", "kernel.elf"],
                              stdout=gdblog, stderr=subprocess.STDOUT, env=dict(os.environ))
        time.sleep(4)
        print("gdb alive:", gd.poll() is None)

        def send(line):
            os.write(master, (line + "\n").encode())
            time.sleep(0.3)
            return rs(master, 0.8)

        def quit_doom():
            for k in ["esc", "down", "down", "down", "down", "down", "ret", "y"]:
                q.key(k)
                time.sleep(0.8)
            time.sleep(1.5)

        print("== DOOM 1 ==")
        print(send("doomgeneric.elf")[-30:].strip())
        time.sleep(8)
        rs(master, 0.8)
        quit_doom()
        print("== NK ==")
        print(send("nuklear --selftest")[-60:].strip())
        print("== DOOM 2 ==")
        print(send("doomgeneric.elf")[-30:].strip())
        time.sleep(8)
        rs(master, 0.8)
        quit_doom()
        time.sleep(2)
        out = rs(master, 2.0)
        print("SERIAL after: EXCEPTION?", "EXCEPTION" in out)
        time.sleep(1)
        print("gdb done:", gd.poll() is not None)
    finally:
        for pid in ():
            pass
        qemu.terminate()
        try:
            qemu.wait(timeout=5)
        except Exception:
            qemu.kill()
        os.close(master)
        os.close(slave)
        if os.path.exists(g.QMP_SOCK):
            os.unlink(g.QMP_SOCK)


if __name__ == "__main__":
    main()