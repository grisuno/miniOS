"""Build a MiniOS ramdisk image from files in a directory tree.

Each packed file is named by its path relative to the shared parent of
all inputs, so progs/src/cp.c ships as src/cp.c and directories are carried
as slashes inside flat names. Names longer than NAME_MAX or two inputs
mapping to the same name are hard errors: a silently truncated or
overwritten name would make every later lookup miss.

Payloads are deflate compressed (a zlib stream, exactly what the kernel
miniz mz_uncompress consumes). The kernel decompresses every entry once
at boot into its working ramdisk area, so runtime reads and writes see
plain bytes and lose no performance; only the on-disk/embedded image
shrinks. A payload that does not compress (tiny or incompressible) is
stored raw and flagged so.

Layout (little endian):
    u32 magic, u32 count
    count * { char name[64]; u32 raw_size; u32 stored_size;
              u32 data_offset; u32 flags }
    payload area (concatenated, offsets relative to its start)
flags bit 0: stored_size bytes are a zlib stream, else raw.
"""

import os
import struct
import sys
import zlib

MAGIC = 0x4B534452
FNAME_BYTES = 64
NAME_MAX = FNAME_BYTES - 1
MAX_FILES = 128
ENTRY_BYTES = FNAME_BYTES + 16
FLAG_DEFLATE = 1
DEFLATE_LEVEL = 6


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
    raw_total = 0
    stored_total = 0
    compressed_files = 0
    for name, f in pairs:
        with open(f, "rb") as fp:
            data = fp.read()
        raw_total += len(data)
        stored = data
        flags = 0
        if len(data) > 0:
            cand = zlib.compress(data, DEFLATE_LEVEL)
            if len(cand) < len(data):
                stored = cand
                flags = FLAG_DEFLATE
                compressed_files += 1
        stored_total += len(stored)
        file_data.append((name, len(data), stored, flags))

    offset = 0
    with open(outfile, "wb") as fp:
        fp.write(struct.pack("<I", MAGIC))
        fp.write(struct.pack("<I", len(file_data)))
        for name, raw_size, stored, flags in file_data:
            name_bytes = name.encode() + b"\x00" * (FNAME_BYTES - len(name))
            fp.write(name_bytes[:FNAME_BYTES])
            fp.write(struct.pack("<I", raw_size))
            fp.write(struct.pack("<I", len(stored)))
            fp.write(struct.pack("<I", offset))
            fp.write(struct.pack("<I", flags))
            offset += len(stored)
        for _, _, stored, _ in file_data:
            fp.write(stored)

    ratio = (100.0 * stored_total / raw_total) if raw_total else 100.0
    print("Wrote %s: %d files, %d -> %d bytes (%.1f%%), %d compressed"
          % (outfile, len(file_data), raw_total, stored_total, ratio,
             compressed_files))


if __name__ == "__main__":
    main()
