#!/usr/bin/env python3
"""test_gui_menu.py -- serial proof that the minicraft pause menu works.

ESC must open the pause menu even when QMP delivers down+up inside one
guest frame (the old esc_prev edge dropped those); navigating to CREEPS
and pressing right must print "creeps 4" via mobs_sync; ESC, up-wrap to
QUIT and Enter must return to the shell prompt.

Usage: python3 tools/test_gui_menu.py
Exits 0 printing MENU OK, 1 otherwise.
"""
import os
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from test_gui_wm import Guest


def main():
    g = Guest()
    try:
        if not g.wait_prompt(120):
            print("MENU FAIL (no boot prompt)")
            return 1
        g.send("minicraft new 7", settle=1.0)
        end = time.time() + 60
        while time.time() < end:
            if "new world seed 7" in g.snapshot():
                break
            time.sleep(0.5)
        time.sleep(4.0)
        g.key("esc")
        time.sleep(1.0)
        for _ in range(5):
            g.key("down")
        g.key("right")
        time.sleep(0.5)
        g.key("esc")
        time.sleep(1.0)
        if "creeps 4" not in g.snapshot():
            print("MENU FAIL (creeps count never applied)")
            return 1
        print("menu creeps row ok")
        g.key("esc")
        time.sleep(1.0)
        g.key("up")
        g.key("ret")
        if not g.wait_prompt(60):
            print("MENU FAIL (no shell after QUIT)")
            return 1
        print("MENU OK (pause/nav/sync/quit proven over serial)")
        return 0
    finally:
        try:
            g.stop()
        except Exception:
            pass


if __name__ == "__main__":
    sys.exit(main())
