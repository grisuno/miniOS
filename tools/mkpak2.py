#!/usr/bin/env python3
"""Build baseq2/pak2.pak carrying the classic campaign's first missions.

The shareware pak0.pak ships the first three campaign missions as
demo1/2/3.bsp (Outer Base, Installation, Commander's Quarters) but the game's
'new game' loads maps/base1.bsp.  Add base1/2/3.bsp aliases so the campaign
menu starts Outer Base instead of freezing on a missing map.
"""

import os, struct, sys

BASE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PAK0 = os.path.join(BASE, "progs/baseq2/pak0.pak")
OUT = os.path.join(BASE, "progs/baseq2/pak2.pak")


def main():
    data = open(PAK0, "rb").read()
    o, s = struct.unpack("<II", data[4:12])
    n = s // 64
    demos = {}
    for i in range(n):
        e = data[o + i * 64:o + i * 64 + 64]
        name = e[:56].split(b"\0")[0].decode()
        fo, sz = struct.unpack("<II", e[56:64])
        if name.startswith("maps/demo"):
            demos[name] = data[fo:fo + sz]
    if len(demos) < 3:
        print("missing demo maps in %s" % PAK0)
        sys.exit(1)
    files = [("maps/base1.bsp", demos["maps/demo1.bsp"]),
             ("maps/base2.bsp", demos["maps/demo2.bsp"]),
             ("maps/base3.bsp", demos["maps/demo3.bsp"])]
    payload = b""
    entries = []
    for name, blob in files:
        entries.append((name, len(blob), 8 + len(payload)))
        payload += blob
    dirstart = 8 + len(payload)
    dirlen = 64 * len(entries)
    dirblob = b""
    for name, sz, pos in entries:
        nb = name.encode() + b"\0" * 56
        dirblob += nb[:56] + struct.pack("<II", pos, sz)
    out = b"PACK" + struct.pack("<II", dirstart, dirlen) + payload + dirblob
    os.makedirs(os.path.dirname(OUT), exist_ok=True)
    with open(OUT, "wb") as f:
        f.write(out)
    print("wrote %s (%d files, %d bytes)" % (OUT, len(entries), len(out)))


if __name__ == "__main__":
    main()
