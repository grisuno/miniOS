#!/usr/bin/env python3
"""test_readme_shot.py -- verify the desktop and refresh the README image.

Purpose
    Boots the MiniOS image headless in QEMU, stages the showcase scene
    (a terminal running `minifetch` over the wallpaper, the profile card and
    the dock), asserts that the desktop is really painted, and only then
    replaces docs/img/desktop.png, the picture the README presents. Run by
    every release (deploynator test stage, `make readme-shot`), so the
    published image can never lag behind the desktop that ships.

Usage
    python3 tools/test_readme_shot.py [--out docs/img/desktop.png]

Inputs
    os.img built by `make`, qemu-system-x86_64 and Pillow on the host.

Outputs
    PASS/FAIL lines, exit 0 when every check passed and the image was
    written, exit 1 on any failed check, exit 2 when the environment lacks
    the image or QEMU.

Failure modes
    Fail-closed: the existing image is replaced only after every check
    passed, through a temporary file renamed over it, so a black, partial
    or crashed frame never reaches the README. Guest and QMP errors abort
    with a diagnostic and always power the guest off.
"""

import argparse
import os
import shutil
import sys
import tempfile
import time

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

from test_gui_wm import Guest, IMAGE, note, FAIL, DUMPS  # noqa: E402


class Config:
    """Central tunables for the showcase capture and its checks."""

    boot_timeout = 180
    settle = 2.5
    scene_commands = ("clear", "minifetch")
    wiggle = ((6, 4), (-6, -4))
    frame_size = (1024, 768)
    default_out = os.path.join(HERE, "..", "docs", "img", "desktop.png")
    file_mode = 0o644
    card_probe = (0.80, 0.0, 1.0, 0.12)
    dock_probe = (0.0, 0.88, 1.0, 0.985)
    min_mean_luma = 28
    min_colors = 4000
    ring_white_min = 40
    ring_white_level = 245
    green_min = 150
    green_min_channel = 180
    green_max_other = 120
    dock_varied_min = 0.30
    dock_dark_level = 24


def crop_box(size, fractions):
    """Fractional (x0, y0, x1, y1) box in pixel coordinates."""
    w, h = size
    x0, y0, x1, y1 = fractions
    return (int(w * x0), int(h * y0), int(w * x1), int(h * y1))


def pixels(img):
    """Iterate (r, g, b) tuples of an image without deprecated accessors."""
    raw = img.convert("RGB").tobytes()
    return zip(raw[0::3], raw[1::3], raw[2::3])


def count_pixels(img, box, predicate):
    """Number of pixels in box satisfying predicate((r, g, b))."""
    return sum(1 for p in pixels(img.crop(box)) if predicate(p))


def check_frame(img):
    """Assert the desktop is painted; returns True when every check passed."""
    from PIL import ImageStat

    note(img.size == Config.frame_size,
         "framebuffer is %dx%d" % Config.frame_size)
    luma = ImageStat.Stat(img.convert("L")).mean[0]
    note(luma >= Config.min_mean_luma, "desktop is lit (mean luma %.1f)" % luma)
    colors = len(set(pixels(img.resize((256, 192)))))
    note(colors >= Config.min_colors, "desktop has depth (%d colors)" % colors)

    card = crop_box(img.size, Config.card_probe)
    ring = count_pixels(img, card, lambda p: min(p) >= Config.ring_white_level)
    note(ring >= Config.ring_white_min,
         "profile card avatar ring painted (%d bright px)" % ring)

    green = count_pixels(
        img, (0, 0, img.size[0], img.size[1]),
        lambda p: p[1] >= Config.green_min_channel
        and p[0] <= Config.green_max_other and p[2] <= Config.green_max_other)
    note(green >= Config.green_min,
         "terminal text rendered (%d green px)" % green)

    dock = crop_box(img.size, Config.dock_probe)
    total = (dock[2] - dock[0]) * (dock[3] - dock[1])
    bright = count_pixels(img, dock, lambda p: max(p) >= Config.dock_dark_level)
    note(bright / float(total) >= Config.dock_varied_min,
         "dock icons painted (%.2f lit)" % (bright / float(total)))
    return not FAIL


def write_atomic(img, path):
    """Save img as PNG at path through a temporary file in its directory."""
    directory = os.path.dirname(os.path.abspath(path))
    os.makedirs(directory, exist_ok=True)
    fd, tmp = tempfile.mkstemp(dir=directory, prefix=".desktop_", suffix=".png")
    os.close(fd)
    try:
        img.save(tmp, format="PNG", optimize=True)
        os.chmod(tmp, Config.file_mode)
        os.replace(tmp, path)
    except BaseException:
        if os.path.exists(tmp):
            os.unlink(tmp)
        raise


def stage_scene(guest):
    """Run the showcase commands and park the pointer in a visible spot."""
    for line in Config.scene_commands:
        guest.send(line, settle=1.0)
    for dx, dy in Config.wiggle:
        guest.rel(dx, dy)
    time.sleep(Config.settle)


def main(argv=None):
    """Entry point: capture, verify, then publish the README image."""
    parser = argparse.ArgumentParser(description="Refresh the README desktop image.")
    parser.add_argument("--out", default=Config.default_out)
    args = parser.parse_args(argv)

    if not os.path.isfile(IMAGE) or shutil.which("qemu-system-x86_64") is None:
        print("test_readme_shot: os.img or qemu-system-x86_64 missing", file=sys.stderr)
        return 2
    try:
        from PIL import Image
    except ImportError:
        print("test_readme_shot: Pillow is required", file=sys.stderr)
        return 2

    guest = Guest()
    try:
        note(guest.wait_prompt(Config.boot_timeout), "guest booted to prompt")
        if FAIL:
            return 1
        stage_scene(guest)
        shot = Image.open(guest.dump("readme_shot")).convert("RGB")
        shot.load()
        if not check_frame(shot):
            print("test_readme_shot: checks failed, image not updated "
                  "(frame kept in %s)" % DUMPS, file=sys.stderr)
            return 1
        write_atomic(shot, args.out)
        print("PASS README image written: %s" % os.path.normpath(args.out))
        return 0
    finally:
        guest.stop()


if __name__ == "__main__":
    sys.exit(main())
