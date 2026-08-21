"""Build a MiniOS ramdisk image from files in a directory tree.

Each packed file is named by its path relative to the shared parent of
all inputs, so progs/src/cp.c ships as src/cp.c and directories are carried
as slashes inside flat names. Names longer than NAME_MAX or two inputs
mapping to the same name are hard errors: a silently truncated or
overwritten name would make every later lookup miss.
"""

import os
import struct
import sys

MAGIC = 0x4B534452
FNAME_BYTES = 32
NAME_MAX = FNAME_BYTES - 1
MAX_FILES = 128


def pack_name(path, common):
    rel = os.path.relpath(path, common)
    if rel.startswith(".."):
        raise SystemExit("input escapes the shared directory: %s" % path)
    name = rel.replace(os.sep, "/")
    if not name or len(name) > NAME_MAX:
        raise SystemExit("ramdisk name too long (max %d): %s" % (NAME_MAX, name))
    return name


def main():
    if len(sys.argv) < 3:
        raise SystemExit("usage: %s <outfile> <file1> <file2> ..." % sys.argv[0])
    outfile = sys.argv[1]
    files = sys.argv[2:]
    if len(files) > MAX_FILES:
        raise SystemExit("too many files (%d, maximum %d)" % (len(files), MAX_FILES))
    common = os.path.commonpath([os.path.abspath(f) for f in files])
    pairs = [(pack_name(f, common), f) for f in files]
    seen = {}
    for name, path in pairs:
        if name in seen:
            raise SystemExit("ramdisk name collision: %s from %s and %s" % (name, seen[name], path))
        seen[name] = path

    file_data = []
    for name, f in pairs:
        with open(f, "rb") as fp:
            file_data.append((name, fp.read()))

    offset = 0
    entries = []
    for name, data in file_data:
        entries.append((name, len(data), offset))
        offset += len(data)

    with open(outfile, "wb") as fp:
        fp.write(struct.pack("<I", MAGIC))
        fp.write(struct.pack("<I", len(entries)))
        for name, size, off in entries:
            name_bytes = name.encode() + b"\x00" * (FNAME_BYTES - len(name))
            fp.write(name_bytes[:FNAME_BYTES])
            fp.write(struct.pack("<I", size))
            fp.write(struct.pack("<I", off))
        for _, data in file_data:
            fp.write(data)

    print("Wrote %s: %d files, %d bytes data" % (outfile, len(entries), offset))


if __name__ == "__main__":
    main()
