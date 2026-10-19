#!/usr/bin/env python3
"""mkcpyzip.py -- pack a CPython Lib tree into a zipimport stdlib.

Usage: mkcpyzip.py <lib_dir> <out_zip> [skip_dir ...]

CPython's sys.path already names <prefix>/lib/python312.zip, so one
stored (uncompressed) zip carries the whole pure-Python standard library
onto MiniFS as a single inode, and zipimport needs no zlib module inside
the guest for stored entries. Directories named in skip (typically test,
idlelib, tkinter, ensurepip, venv) and every __pycache__ are pruned;
compiled .py/.pyo files are not shipped (zipimport compiles on the fly).

Exit 0 with one summary line on success; a missing input or an empty
result exits 1 with the reason on stderr.
"""

import os
import sys
import zipfile


def build_zip(lib_dir, out_zip, skip):
    """Write out_zip with the Lib tree minus skip dirs; return file count."""
    count = 0
    with zipfile.ZipFile(out_zip, "w", zipfile.ZIP_STORED) as archive:
        for root, dirs, files in os.walk(lib_dir):
            rel_parts = os.path.relpath(root, lib_dir).split(os.sep)
            if any(part in skip for part in rel_parts):
                dirs[:] = []
                continue
            dirs[:] = [d for d in sorted(dirs) if d not in skip and d != "__pycache__"]
            for name in sorted(files):
                if name.endswith((".pyc", ".pyo")):
                    continue
                path = os.path.join(root, name)
                archive.write(path, os.path.relpath(path, lib_dir))
                count += 1
    return count


def main():
    if len(sys.argv) < 3:
        print(__doc__.strip(), file=sys.stderr)
        return 2
    lib_dir, out_zip = sys.argv[1], sys.argv[2]
    skip = set(sys.argv[3:])
    if not os.path.isdir(lib_dir):
        print("mkcpyzip: no such directory: %s" % lib_dir, file=sys.stderr)
        return 1
    count = build_zip(lib_dir, out_zip, skip)
    if count == 0:
        print("mkcpyzip: nothing packed from %s" % lib_dir, file=sys.stderr)
        return 1
    print("mkcpyzip: %s (%d files)" % (out_zip, count))
    return 0


if __name__ == "__main__":
    sys.exit(main())
