#!/usr/bin/env python3
"""Build baseq2/pak1.pak carrying the player model.

The Quake 2 shareware pak0.pak omits the player model (players/male/tris.md2,
grunt.pcx, weapon.md2, grunt_i.pcx are loose files in the retail game).  The
q2generic client must find them in a pak, so this script packages the loose
player model (from the Quake 2 install, held under progs/quake2generic/players)
into a small second pak the game loads after pak0.pak.

Quake 2 pak format: 4-byte "PACK", u32 directory offset, u32 directory length,
then 64-byte directory entries (56-byte NUL-padded name, u32 filepos, u32
filelen), then the concatenated file data.
"""

import os, struct, sys

BASE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(BASE, "progs/quake2generic/players/male")
OUT = os.path.join(BASE, "progs/baseq2/pak1.pak")

FILES = [
    ("players/male/tris.md2", "tris.md2"),
    ("players/male/grunt.pcx", "grunt.pcx"),
    ("players/male/weapon.md2", "weapon.md2"),
    ("players/male/grunt_i.pcx", "grunt_i.pcx"),
]


def main():
    if not all(os.path.isfile(os.path.join(SRC, fn)) for _, fn in FILES):
        print("missing player model files; put tris.md2/grunt.pcx/weapon.md2/grunt_i.pcx in %s" % SRC)
        sys.exit(1)

    payload = bytearray()
    entries = []
    for name, fn in FILES:
        blob = open(os.path.join(SRC, fn), "rb").read()
        entries.append((name, len(blob), 8 + len(payload)))
        payload += blob

    dirstart = 8 + len(payload)
    dirlen = 64 * len(entries)
    dirblob = b""
    for name, size, pos in entries:
        nb = name.encode() + b"\0" * 56
        dirblob += nb[:56] + struct.pack("<II", pos, size)

    out = b"PACK" + struct.pack("<II", dirstart, dirlen) + bytes(payload) + dirblob
    os.makedirs(os.path.dirname(OUT), exist_ok=True)
    with open(OUT, "wb") as f:
        f.write(out)
    print("wrote %s (%d files, %d bytes)" % (OUT, len(entries), len(out)))


if __name__ == "__main__":
    main()
