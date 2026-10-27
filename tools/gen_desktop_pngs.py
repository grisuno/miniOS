#!/usr/bin/env python3
"""gen_desktop_pngs.py -- build MiniOS desktop art from user-supplied PNGs.

Sources (images/ by default, overridable with --src-dir):
  paint.png              paint icon source
  animegirl.png          wallpaper source (any size, RGB/RGBA)
  doom.png               DOOM icon source
  doomedit.png           doomedit map-editor icon source
  quake2.png             Quake 2 icon source
  piano.png              piano icon source
  nuklear.png            Nuklear icon source
  vedit.png              vedit editor icon source
  pokemon.png            Pokemon icon source (Pikachu art, not pixel art)
  freedom.png            FreeDom browser icon source

Outputs (under the MiniOS repo):
  progs/icons/doom.png, doomedit.png, quake2.png, piano.png, nuklear.png,
  vedit.png, pokemon.png, file.png, shell.png, paint.png, minicraft.png,
  freedom.png, folder.png, files.png, image.png, object.png  32x32 RGBA
  (folder/files/image/object are the file-browser kind icons).
  progs/wall/wallpaper.png                                   1024x768 RGB

The kernel runs in an 8-bit palette mode, so it maps icon pixels to the
16-entry icon palette and wallpaper pixels to a fixed 6x6x6 colour cube
at boot; these files only need the right dimensions. Icons keep alpha
(the kernel treats fully transparent pixels as transparent). The
wallpaper keeps the whole source visible: it is contain-scaled
(aspect-preserving fit, centred) over a blurred, darkened cover-scaled copy
of itself, so a square source never looks stretched or cropped.

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
    from PIL import Image, ImageEnhance, ImageFilter
except ImportError:
    print("gen_desktop_pngs.py: error: PIL (Pillow) is required", file=sys.stderr)
    sys.exit(1)

ICON_SIZE = 32
WALL_W, WALL_H = 1024, 768
WALL_SRC = "animegirl.png"
WALL_BACKDROP_BLUR = 28
WALL_BACKDROP_DIM = 0.45

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
    ("minicraft.png", "minicraft.png"),
    ("freedom.png", "freedom.png"),
    ("folder.png", "folder.png"),
    ("files.png", "files.png"),
    ("image.png", "image.png"),
    ("object.png", "object.png"),
)


def scaled(im, scale):
    """Resize an image by a factor with Lanczos, never below one pixel."""
    size = (max(1, int(im.width * scale + 0.5)), max(1, int(im.height * scale + 0.5)))
    return im.resize(size, Image.LANCZOS)


def fit_wallpaper(im):
    """Whole source, centred, over a blurred and dimmed cover-scaled copy."""
    back = scaled(im, max(WALL_W / im.width, WALL_H / im.height))
    left, top = (back.width - WALL_W) // 2, (back.height - WALL_H) // 2
    back = back.crop((left, top, left + WALL_W, top + WALL_H))
    back = back.filter(ImageFilter.GaussianBlur(WALL_BACKDROP_BLUR))
    back = ImageEnhance.Brightness(back).enhance(WALL_BACKDROP_DIM)
    front = scaled(im, min(WALL_W / im.width, WALL_H / im.height))
    back.paste(front, ((WALL_W - front.width) // 2, (WALL_H - front.height) // 2))
    return back


def write_atomic(img, path, **save_kw):
    tmp = path + ".tmp"
    img.save(tmp, format="PNG", **save_kw)
    os.replace(tmp, path)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--src-dir", default="images",
                    help="directory holding the user source PNGs")
    ap.add_argument("--repo", default=".",
                    help="MiniOS repo root (holds progs/ and tools/)")
    args = ap.parse_args()

    # Validate every source before writing anything.
    missing = []
    for src, _ in ICON_JOBS + ((WALL_SRC, None),):
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

    with Image.open(os.path.join(args.src_dir, WALL_SRC)) as im:
        im = fit_wallpaper(im.convert("RGB"))
        out = os.path.join(wall_dir, "wallpaper.png")
        write_atomic(im, out)
        print("  %s (%dx%d RGB)" % (out, WALL_W, WALL_H))


if __name__ == "__main__":
    main()
