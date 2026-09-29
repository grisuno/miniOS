#!/usr/bin/env python3
"""test_gui_gfxview.py -- pixel + serial proof of the graphics view contract.

Purpose
    Proves that the tiling WM governs graphics apps (headers/wm_gfxview.h,
    kernel/vga_fb.c): DOOM starts in true fullscreen (scaled to the whole
    display, aspect kept, taskbar hidden), Alt+Enter returns it to a
    floating window, `wm tile` places it in a layout cell scaled to fit
    beside the terminal, `wm minimize` hides it to the taskbar while it
    keeps running, `wm focus 2` restores it, and the title-bar close
    request still ends it with exit code 130.

Usage
    python3 tools/test_gui_gfxview.py
    Needs qemu-system-x86_64, Pillow and a built os.img (make).

Inputs
    os.img next to tools/, driven through the Guest harness of
    tools/test_gui_wm.py (QMP screendumps, unix-socket serial console).

Outputs
    PASS/FAIL lines per assertion, then GFXVIEW OK (exit 0) or
    GFXVIEW FAIL (exit 1). Screendumps land in the harness temp dir.

Failure modes
    No boot prompt, DOOM never composites, a `wm list` view that does not
    match the requested mode, or pixels that contradict it (a fullscreen
    frame that still shows the taskbar row, a floating frame that shows
    no desktop around the window).
"""
import os
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from test_gui_wm import Guest, DUMPS  # noqa: E402


class Config:
    """Every tunable of the run in one place."""

    boot_timeout = 150
    frame_wait = 90
    settle = 2.5
    doom_cmd = "run doomgeneric.elf &"
    band_rows = 8
    dark_level = 24
    dark_fraction = 0.90
    desk_fraction = 0.30


FAIL = []


def note(ok, msg):
    """Record one assertion."""
    print(("PASS " if ok else "FAIL ") + msg, flush=True)
    if not ok:
        FAIL.append(msg)


def last_line(g, prefix):
    """Last serial line starting with prefix, or an empty string."""
    found = ""
    for ln in g.snapshot().splitlines():
        s = ln.strip()
        if s.startswith(prefix):
            found = s
    return found


def gfx_row(g):
    """Fresh `win gfx` line from `wm list` as a dict of key=value fields."""
    g.send("wm list", settle=1.0)
    ln = last_line(g, "win gfx ")
    out = {"raw": ln}
    for tok in ln.split():
        if "=" in tok:
            k, v = tok.split("=", 1)
            out[k] = v
    return out


def dark_share(img, box):
    """Fraction of near-black pixels inside box (x0, y0, x1, y1)."""
    crop = img.crop(box).convert("L")
    hist = crop.histogram()
    total = sum(hist)
    if total == 0:
        return 0.0
    return sum(hist[:Config.dark_level]) / float(total)


def wait_frames(g, want):
    """Poll `gfx frames` until the counter reaches want."""
    end = time.time() + Config.frame_wait
    while time.time() < end:
        g.send("gfx frames", settle=1.0)
        ln = last_line(g, "gfx: frames composited")
        try:
            if int(ln.split()[-1]) >= want:
                return True
        except (ValueError, IndexError):
            pass
        time.sleep(1.0)
    return False


def main():
    from PIL import Image
    g = Guest()
    try:
        note(g.wait_prompt(Config.boot_timeout), "guest booted to prompt")
        g.rel(5, 5)
        g.rel(-5, -5)
        g.send(Config.doom_cmd, settle=1.0)
        note(wait_frames(g, 20), "doom composited frames in the background")
        time.sleep(Config.settle)

        row = gfx_row(g)
        print("info " + row["raw"], flush=True)
        note(row.get("view") == "fullscreen", "doom starts in fullscreen")
        shot = Image.open(g.dump("gv_full"))
        fw, fh = shot.size
        note(int(row.get("cw", "0")) >= fw * 3 // 4,
             "fullscreen content spans most of the width (%s px)" % row.get("cw"))
        bottom = dark_share(shot, (0, fh - Config.band_rows, fw, fh))
        note(bottom >= Config.dark_fraction,
             "fullscreen hides the taskbar row (dark %.2f)" % bottom)

        g.key("alt", down=True, up=False)
        g.key("ret")
        g.key("alt", down=False, up=True)
        time.sleep(Config.settle)
        row = gfx_row(g)
        print("info " + row["raw"], flush=True)
        note(row.get("view") == "floating", "Alt+Enter returns to floating")
        shot = Image.open(g.dump("gv_float"))
        corner = dark_share(shot, (0, 0, fw // 6, fh // 6))
        note(corner < 1.0 - Config.desk_fraction,
             "floating window shows the desktop around it (dark %.2f)" % corner)

        g.send("wm tile", settle=Config.settle)
        row = gfx_row(g)
        print("info " + row["raw"], flush=True)
        note(row.get("view") == "tiled", "wm tile places doom in a layout cell")
        note(int(row.get("x", "0")) >= fw // 3,
             "tiled doom sits right of the terminal (x=%s)" % row.get("x"))
        note(int(row.get("cw", "0")) > 320,
             "tiled doom scales up to its cell (%s px)" % row.get("cw"))
        g.dump("gv_tiled")

        g.send("wm focus 2", settle=1.0)
        g.send("wm minimize", settle=Config.settle)
        row = gfx_row(g)
        note(row.get("view") == "minimized", "wm minimize hides doom to the taskbar")
        before = last_line(g, "gfx: frames composited")
        wait_frames(g, 0)
        g.send("wm focus 2", settle=Config.settle)
        row = gfx_row(g)
        note(row.get("view") == "tiled", "wm focus 2 restores the tiled view")
        after = last_line(g, "gfx: frames composited")
        print("info frames %s -> %s" % (before, after), flush=True)

        g.send("wm close", settle=1.0)
        g.send("wait", settle=4.0)
        note("exit code: 130" in g.snapshot(), "close request ends doom (130)")
    finally:
        g.stop()
    print("dumps in %s" % DUMPS, flush=True)
    if FAIL:
        print("GFXVIEW FAIL (%d)" % len(FAIL), flush=True)
        return 1
    print("GFXVIEW OK", flush=True)
    return 0


if __name__ == "__main__":
    sys.exit(main())
