#!/usr/bin/env python3
"""gen_desktop_pngs.py -- build MiniOS desktop art from user-supplied PNGs.

Sources (repo root by default, overridable with --src-dir):
  paint.png              paint icon source
  cgoblin.png            wallpaper source (any size, RGB/RGBA)
  doom.png               DOOM icon source
  doomedit.png           doomedit map-editor icon source
  quake2.png             Quake 2 icon source
  piano.png              piano icon source
  nuklear.png            Nuklear icon source
  vedit.png              vedit editor icon source
  pokemon.png            Pokemon icon source (Pikachu art, not pixel art)

Outputs (under the MiniOS repo):
  progs/icons/doom.png, doomedit.png, quake2.png, piano.png, nuklear.png,
  vedit.png, pokemon.png, file.png, shell.png, paint.png  32x32 RGBA
  progs/wall/wallpaper.png                                   800x600 RGB

The kernel runs in an 8-bit palette mode, so it maps icon pixels to the
16-entry icon palette and wallpaper pixels to a fixed 6x6x6 colour cube
at boot; these files only need the right dimensions. Icons keep alpha
(the kernel treats fully transparent pixels as transparent). The
wallpaper is cover-scaled (aspect-preserving fill + centre crop) so a
square source like cgoblin.png never looks stretched.

Fail-closed: a missing source aborts with a diagnostic and nonzero exit
before anything is written; each output is written atomically (tmp +
rename), never a partial file.

Usage:
  python3 tools/gen_desktop_pngs.py [--src-dir DIR] [--repo DIR]
"""

import argparse
import os
import sys

try:
    from PIL import Image
except ImportError:
    print("gen_desktop_pngs.py: error: PIL (Pillow) is required", file=sys.stderr)
    sys.exit(1)

ICON_SIZE = 32
WALL_W, WALL_H = 800, 600

ICON_JOBS = (
    ("doom.png", "doom.png"),
    ("doomedit.png", "doomedit.png"),
    ("quake2.png", "quake2.png"),
    ("piano.png", "piano.png"),
    ("nuklear.png", "nuklear.png"),
    ("vedit.png", "vedit.png"),
    ("pokemon.png", "pokemon.png"),
    ("file.png", "file.png"),
    ("shell.png", "shell.png"),
    ("paint.png", "paint.png"),
)


def write_atomic(img, path, **save_kw):
    tmp = path + ".tmp"
    img.save(tmp, format="PNG", **save_kw)
    os.replace(tmp, path)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--src-dir", default=".",
                    help="directory holding the user source PNGs")
    ap.add_argument("--repo", default=".",
                    help="MiniOS repo root (holds progs/ and tools/)")
    args = ap.parse_args()

    # Validate every source before writing anything.
    missing = []
    for src, _ in ICON_JOBS + (("cgoblin.png", None),):
        p = os.path.join(args.src_dir, src)
        if not os.path.isfile(p):
            missing.append(p)
    if missing:
        for p in missing:
            print("gen_desktop_pngs.py: error: missing source %s" % p,
                  file=sys.stderr)
        sys.exit(1)

    icons_dir = os.path.join(args.repo, "progs", "icons")
    wall_dir = os.path.join(args.repo, "progs", "wall")
    os.makedirs(icons_dir, exist_ok=True)
    os.makedirs(wall_dir, exist_ok=True)

    for src, dst in ICON_JOBS:
        with Image.open(os.path.join(args.src_dir, src)) as im:
            im = im.convert("RGBA")
            im = im.resize((ICON_SIZE, ICON_SIZE), Image.LANCZOS)
            out = os.path.join(icons_dir, dst)
            write_atomic(im, out)
            print("  %s (32x32 RGBA)" % out)

    with Image.open(os.path.join(args.src_dir, "cgoblin.png")) as im:
        im = im.convert("RGB")
        scale = max(WALL_W / im.width, WALL_H / im.height)
        nw, nh = int(im.width * scale + 0.5), int(im.height * scale + 0.5)
        im = im.resize((nw, nh), Image.LANCZOS)
        left, top = (nw - WALL_W) // 2, (nh - WALL_H) // 2
        im = im.crop((left, top, left + WALL_W, top + WALL_H))
        out = os.path.join(wall_dir, "wallpaper.png")
        write_atomic(im, out)
        print("  %s (800x600 RGB)" % out)


if __name__ == "__main__":
    main()
