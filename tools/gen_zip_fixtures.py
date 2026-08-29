#!/usr/bin/env python3
"""gen_zip_fixtures.py -- generate the zip test fixtures shipped on the ramdisk.

Two small ZIP archives, built with the host's standard zipfile so the in-OS
extractor is tested against bytes produced by a reference implementation, not
just by its own writer:

  host.zip    a well-formed archive with a directory and two files, proving
              the in-OS extractor interops with host-produced ZIPs.

  hostile.zip an archive whose entry names try to escape the extraction
              root: a traversal ("../escape.txt"), an absolute path
              ("/abs.txt") and a directory marker ("dir/") beside one plain
              file.  The in-OS extractor must create only good.txt, dir/ and
              abs.txt (the absolute name is sanitized to relative) and must
              never create escape.txt.

Timestamps are fixed so the build is reproducible.
"""

import os
import sys
import zipfile

FIXED_TIME = (2000, 1, 1, 0, 0, 0)


def write_zip(path, entries):
    """entries: list of (name, data_or_None).  data None marks a directory."""
    with zipfile.ZipFile(path, 'w', zipfile.ZIP_DEFLATED) as zf:
        for name, data in entries:
            zi = zipfile.ZipInfo(name, date_time=FIXED_TIME)
            if data is None:
                zi.external_attr = 0o40775 << 16
                zf.writestr(zi, b'')
            else:
                zi.external_attr = 0o100644 << 16
                zi.compress_type = zipfile.ZIP_DEFLATED
                zf.writestr(zi, data)


def main():
    outdir = sys.argv[1] if len(sys.argv) > 1 else 'progs/etc'
    os.makedirs(outdir, exist_ok=True)
    write_zip(os.path.join(outdir, 'host.zip'), [
        ('sub/note.txt', b'hello host\n'),
        ('top.txt', b'top\n'),
    ])
    write_zip(os.path.join(outdir, 'hostile.zip'), [
        ('good.txt', b'ok\n'),
        ('dir/', None),
        ('../escape.txt', b'evil\n'),
        ('/abs.txt', b'abs\n'),
    ])
    print(f'Generated zip fixtures in {outdir}/')


if __name__ == '__main__':
    main()