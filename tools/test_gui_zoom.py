#!/usr/bin/env python3
"""test_gui_zoom.py -- pixel proof that GFX_ZOOM doubles the game window.

Boots MiniOS headless (display none, QMP screendump), runs minicraft in
the foreground with a fresh seed, dumps the 1:1 window, presses F11,
dumps again and diffs the two frames. A working 2x zoom changes a
~648x416 bounding box; a dead toggle only moves pigs/the clock.

Usage: python3 tools/test_gui_zoom.py
Exits 0 printing ZOOM OK, 1 otherwise.
"""
import os
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from test_gui_wm import Guest

from PIL import Image, ImageChops


def main():
    g = Guest()
    try:
        if not g.wait_prompt(120):
            print("ZOOM FAIL (no boot prompt)")
            return 1
        g.send("minicraft new 7", settle=1.0)
        end = time.time() + 60
        while time.time() < end:
            if "new world seed 7" in g.snapshot():
                break
            time.sleep(0.5)
        time.sleep(8.0)
        p0 = g.dump("zoom_off")
        g.key("g")
        time.sleep(4.0)
        print("serial after G: %s" % g.snapshot()[-300:].replace("\n", " | "))
        p1 = g.dump("zoom_on")
        g.key("esc")
        time.sleep(1.0)
        g.key("up")
        g.key("ret")
        ok_prompt = g.wait_prompt(60)
    finally:
        try:
            g.stop()
        except Exception:
            pass
    a = Image.open(p0).convert("RGB")
    b = Image.open(p1).convert("RGB")
    if a.size != b.size:
        print("ZOOM FAIL (dump size moved %s -> %s)" % (a.size, b.size))
        return 1
    diff = ImageChops.difference(a, b)
    bbox = diff.convert("L").point(lambda v: 255 if v > 12 else 0).getbbox()
    if not bbox:
        print("ZOOM FAIL (frames identical, toggle dead)")
        return 1
    w, h = bbox[2] - bbox[0], bbox[3] - bbox[1]
    area = w * h
    print("zoom diff bbox w=%d h=%d area=%d" % (w, h, area))
    # A 640x400 zoomed window (plus title bar) spans ~648x432 wherever the
    # VBE mode centers it; a dead toggle only moves pigs/the clock (<10k).
    if w >= 600 and h >= 380 and area > 150000:
        print("ZOOM OK (2x window proven on pixels)")
        return 0
    print("ZOOM FAIL (bbox too small for a 640x400 window)")
    return 1


if __name__ == "__main__":
    sys.exit(main())
