"""Generate the desktop profile avatar as a C header.

Purpose
    Draws a stylized anime-style portrait with vector primitives at a high
    supersampling factor, downsamples it with a Lanczos filter and writes
    the pixels as a packed 0x00RRGGBB array that the kernel blits inside a
    circular mask (headers/avatar_data.h). The artwork is procedural, so the
    repository ships no third-party image and the portrait can be tuned by
    editing AvatarConfig.

Usage
    python3 tools/gen_avatar.py [--out headers/avatar_data.h] [--preview png]

Inputs
    None. All tunables live in AvatarConfig.

Outputs
    A header defining AVATAR_SIZE and the avatar_pixels array, and with
    --preview a PNG of the same pixels for review.

Failure modes
    Missing Pillow aborts with a clear message; an unwritable output path
    aborts with the OS error. The output is written atomically through a
    temporary file in the same directory, never left half written.
"""

import argparse
import os
import sys
import tempfile

try:
    from PIL import Image, ImageDraw
except ImportError:
    sys.exit("gen_avatar: Pillow is required (pip install pillow)")


class AvatarConfig:
    """Central, immutable tunables for the portrait."""

    SIZE = 48
    SUPERSAMPLE = 8
    DEFAULT_OUT = os.path.join("headers", "avatar_data.h")
    BG_TOP = (255, 214, 236)
    BG_BOTTOM = (150, 170, 255)
    HAIR = (146, 108, 222)
    HAIR_SHADE = (104, 72, 186)
    HAIR_LIGHT = (190, 156, 250)
    SKIN = (255, 228, 212)
    SKIN_SHADE = (246, 196, 180)
    BLUSH = (255, 150, 170)
    IRIS_TOP = (60, 110, 230)
    IRIS_BOTTOM = (130, 220, 255)
    PUPIL = (28, 32, 80)
    LINE = (70, 40, 90)
    WHITE = (255, 255, 255)
    RIBBON = (255, 90, 130)
    MOUTH = (226, 100, 118)


class AvatarPainter:
    """Paints the portrait on a square canvas in unit coordinates 0..1."""

    def __init__(self, cfg):
        self.cfg = cfg
        self.px = cfg.SIZE * cfg.SUPERSAMPLE
        self.img = Image.new("RGB", (self.px, self.px))
        self.draw = ImageDraw.Draw(self.img)

    def _pt(self, p):
        return (p[0] * self.px, p[1] * self.px)

    def _box(self, cx, cy, rx, ry):
        return [(cx - rx) * self.px, (cy - ry) * self.px,
                (cx + rx) * self.px, (cy + ry) * self.px]

    def _gradient(self, top, bottom, y0, y1, box_fn=None):
        for row in range(int(y0 * self.px), int(y1 * self.px)):
            t = (row - y0 * self.px) / max(1.0, (y1 - y0) * self.px)
            col = tuple(int(top[i] + (bottom[i] - top[i]) * t) for i in range(3))
            self.draw.line([(0, row), (self.px, row)], fill=col)

    def background(self):
        self._gradient(self.cfg.BG_TOP, self.cfg.BG_BOTTOM, 0.0, 1.0)

    def hair_back(self):
        c = self.cfg
        self.draw.ellipse(self._box(0.5, 0.46, 0.40, 0.40), fill=c.HAIR)
        self.draw.polygon([self._pt(p) for p in
                           [(0.10, 0.50), (0.04, 0.98), (0.30, 0.90), (0.26, 0.60)]],
                          fill=c.HAIR_SHADE)
        self.draw.polygon([self._pt(p) for p in
                           [(0.90, 0.50), (0.96, 0.98), (0.70, 0.90), (0.74, 0.60)]],
                          fill=c.HAIR_SHADE)

    def face(self):
        c = self.cfg
        self.draw.rectangle(self._box(0.5, 0.80, 0.07, 0.10), fill=c.SKIN_SHADE)
        self.draw.ellipse(self._box(0.5, 0.52, 0.29, 0.31), fill=c.SKIN)
        self.draw.ellipse(self._box(0.31, 0.62, 0.065, 0.040), fill=c.BLUSH)
        self.draw.ellipse(self._box(0.69, 0.62, 0.065, 0.040), fill=c.BLUSH)

    def eye(self, cx, cy):
        c = self.cfg
        rx, ry = 0.085, 0.115
        self.draw.ellipse(self._box(cx, cy, rx, ry), fill=c.WHITE)
        top = int((cy - ry) * self.px)
        bottom = int((cy + ry) * self.px)
        for row in range(top, bottom):
            t = (row - top) / max(1, bottom - top)
            col = tuple(int(c.IRIS_TOP[i] + (c.IRIS_BOTTOM[i] - c.IRIS_TOP[i]) * t)
                        for i in range(3))
            half = ((1.0 - ((row - (top + bottom) / 2) / ((bottom - top) / 2)) ** 2) ** 0.5
                    if abs(row - (top + bottom) / 2) < (bottom - top) / 2 else 0.0)
            span = 0.072 * self.px * half
            self.draw.line([(cx * self.px - span, row), (cx * self.px + span, row)], fill=col)
        self.draw.ellipse(self._box(cx, cy + 0.01, 0.034, 0.055), fill=c.PUPIL)
        self.draw.ellipse(self._box(cx - 0.028, cy - 0.045, 0.022, 0.026), fill=c.WHITE)
        self.draw.ellipse(self._box(cx + 0.026, cy + 0.04, 0.011, 0.013), fill=c.WHITE)
        self.draw.arc(self._box(cx, cy - 0.005, rx + 0.004, ry + 0.004), 195, 345,
                      fill=c.LINE, width=max(2, self.cfg.SUPERSAMPLE))

    def eyes(self):
        self.eye(0.355, 0.535)
        self.eye(0.645, 0.535)

    def nose_mouth(self):
        c = self.cfg
        self.draw.line([self._pt((0.50, 0.625)), self._pt((0.495, 0.645))],
                       fill=c.SKIN_SHADE, width=max(2, self.cfg.SUPERSAMPLE // 2))
        self.draw.arc(self._box(0.5, 0.685, 0.045, 0.030), 20, 160, fill=c.MOUTH,
                      width=max(2, self.cfg.SUPERSAMPLE))

    def bangs(self):
        c = self.cfg
        polys = [
            [(0.18, 0.36), (0.50, 0.12), (0.82, 0.36), (0.78, 0.30), (0.50, 0.19), (0.22, 0.30)],
            [(0.19, 0.40), (0.31, 0.14), (0.47, 0.44), (0.40, 0.50), (0.32, 0.34), (0.24, 0.52)],
            [(0.47, 0.44), (0.53, 0.16), (0.66, 0.44), (0.58, 0.40)],
            [(0.60, 0.42), (0.74, 0.16), (0.82, 0.42), (0.80, 0.56), (0.74, 0.40)],
        ]
        for poly in polys:
            self.draw.polygon([self._pt(p) for p in poly], fill=c.HAIR)
        self.draw.polygon([self._pt(p) for p in
                           [(0.28, 0.22), (0.46, 0.14), (0.40, 0.24)]], fill=c.HAIR_LIGHT)
        self.draw.polygon([self._pt(p) for p in
                           [(0.62, 0.18), (0.74, 0.20), (0.68, 0.26)]], fill=c.HAIR_LIGHT)

    def ribbon(self):
        c = self.cfg
        self.draw.polygon([self._pt(p) for p in
                           [(0.74, 0.20), (0.92, 0.10), (0.90, 0.30)]], fill=c.RIBBON)
        self.draw.polygon([self._pt(p) for p in
                           [(0.74, 0.20), (0.62, 0.06), (0.68, 0.28)]], fill=c.RIBBON)
        self.draw.ellipse(self._box(0.74, 0.20, 0.035, 0.035), fill=c.WHITE)

    def render(self):
        self.background()
        self.hair_back()
        self.face()
        self.eyes()
        self.nose_mouth()
        self.bangs()
        self.ribbon()
        size = self.cfg.SIZE
        return self.img.resize((size, size), Image.LANCZOS)


def load_portrait(path, crop):
    """Crop the square face region of a picture and downsample it."""
    left, top, side = crop
    image = Image.open(path).convert("RGB")
    width, height = image.size
    if side <= 0 or left < 0 or top < 0 or left + side > width or top + side > height:
        sys.exit("gen_avatar: crop %s is outside the %dx%d source" % (crop, width, height))
    region = image.crop((left, top, left + side, top + side))
    return region.resize((AvatarConfig.SIZE, AvatarConfig.SIZE), Image.LANCZOS)


def parse_crop(text):
    """Parse 'X,Y,SIZE' into three integers or abort with a clear message."""
    try:
        parts = tuple(int(v) for v in text.split(","))
    except ValueError:
        parts = ()
    if len(parts) != 3:
        sys.exit("gen_avatar: --crop expects X,Y,SIZE")
    return parts


def write_header(image, path):
    """Write the avatar as a C header, atomically."""
    size = image.size[0]
    loaded = image.load()
    pixels = [loaded[x, y] for y in range(size) for x in range(size)]
    lines = [
        "/** Docstring: Desktop profile avatar, generated by tools/gen_avatar.py.",
        " * Packed 0x00RRGGBB pixels, row-major, AVATAR_SIZE square. Do not edit",
        " * by hand: change AvatarConfig and regenerate.",
        " */",
        "#ifndef AVATAR_DATA_H",
        "#define AVATAR_DATA_H",
        "",
        "#define AVATAR_SIZE %d" % size,
        "",
        "static const unsigned int avatar_pixels[AVATAR_SIZE * AVATAR_SIZE] = {",
    ]
    for row in range(size):
        chunk = pixels[row * size:(row + 1) * size]
        lines.append("    " + ", ".join("0x%06X" % ((r << 16) | (g << 8) | b)
                                        for r, g, b in chunk) + ",")
    lines += ["};", "", "#endif", ""]
    directory = os.path.dirname(os.path.abspath(path))
    fd, tmp = tempfile.mkstemp(dir=directory, prefix=".avatar_", suffix=".tmp")
    try:
        with os.fdopen(fd, "w") as handle:
            handle.write("\n".join(lines))
        os.replace(tmp, path)
    except BaseException:
        if os.path.exists(tmp):
            os.unlink(tmp)
        raise


def main(argv=None):
    """Entry point: render, write the header, optionally a preview PNG."""
    parser = argparse.ArgumentParser(description="Generate the desktop avatar header.")
    parser.add_argument("--out", default=AvatarConfig.DEFAULT_OUT)
    parser.add_argument("--preview", default=None)
    parser.add_argument("--source", default=None)
    parser.add_argument("--crop", default=None)
    args = parser.parse_args(argv)
    if args.source:
        if not args.crop:
            sys.exit("gen_avatar: --source requires --crop")
        image = load_portrait(args.source, parse_crop(args.crop))
    else:
        image = AvatarPainter(AvatarConfig).render()
    write_header(image, args.out)
    if args.preview:
        image.resize((AvatarConfig.SIZE * 8, AvatarConfig.SIZE * 8), Image.NEAREST).save(args.preview)
    return 0


if __name__ == "__main__":
    sys.exit(main())
