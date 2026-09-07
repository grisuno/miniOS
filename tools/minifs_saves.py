#!/usr/bin/env python3
"""minifs_saves.py - preserve the guest's saves/ dir across image rebuilds.

Regenerating minifs.bin from scratch wipes everything the guest wrote at
runtime (Pokemon battery .sav/.rtc and .state savestates live in saves/ on
MiniFS). Before mkfs runs, this tool extracts the live saves/ tree out of
the previous os.img into a staging dir; the Makefile then passes that dir
back into mkfs, so a rebuild carries the saves forward instead of wiping
them.

Usage: minifs_saves.py backup <os.img|minifs.bin> <stagedir>

The saves land in <stagedir>/saves/... (nothing is created when the image
is missing or carries no saves/ dir). Guest files are written raw by
minifs_write, never compressed, so extraction is byte-exact; a file found
with the compressed flag set or with double-indirect blocks (both outside
what the guest write path produces) aborts with a nonzero exit instead of
backing up corrupt data.
"""
import os
import struct
import sys

MAGIC = 0x4D494E49
VERSION = 1
BLOCK_SIZE = 4096
ROOT_INODE = 2
S_IFMT = 0o170000
S_IFDIR = 0o040000
FLAG_COMPRESSED = 1
DIR_HDR = 8
FT_DIR = 2
PER_INDIRECT = BLOCK_SIZE // 4

MAX_FILE_BYTES = 16 * 1024 * 1024
MAX_TOTAL_BYTES = 64 * 1024 * 1024
MAX_ENTRIES = 1024


def u16(d, o):
    return struct.unpack_from('<H', d, o)[0]


def u32(d, o):
    return struct.unpack_from('<I', d, o)[0]


class Image:
    """Random-access MiniFS partition inside a host file."""

    def __init__(self, fn, base):
        self.f = open(fn, 'rb')
        self.base = base
        avail = os.fstat(self.f.fileno()).st_size - base
        if avail < BLOCK_SIZE:
            raise ValueError('image too small for a superblock')
        self.avail_blocks = avail // BLOCK_SIZE

    def close(self):
        self.f.close()

    def blk(self, n):
        if n >= self.avail_blocks:
            raise ValueError('block %d out of range' % n)
        self.f.seek(self.base + n * BLOCK_SIZE)
        d = self.f.read(BLOCK_SIZE)
        if len(d) != BLOCK_SIZE:
            raise ValueError('short read on block %d' % n)
        return d


class FS:
    def __init__(self, img):
        self.img = img
        b = img.blk(0)
        self.total_blocks = u32(b, 12)
        self.inode_table_start = u32(b, 40)
        if (u32(b, 0) != MAGIC or u32(b, 4) != VERSION
                or u32(b, 8) != BLOCK_SIZE or self.total_blocks == 0):
            raise ValueError('bad superblock')

    def inode(self, i):
        tbl = self.inode_table_start * BLOCK_SIZE + i * 128
        self.img.f.seek(self.img.base + tbl)
        b = self.img.f.read(128)
        if len(b) != 128:
            raise ValueError('short read on inode %d' % i)
        return {
            'mode': u16(b, 0),
            'size': u32(b, 8),
            'direct': [u32(b, 24 + j * 4) for j in range(10)],
            'indirect': u32(b, 64),
            'dindirect': u32(b, 68),
            'flags': u32(b, 72),
        }

    def is_dir(self, st):
        return (st['mode'] & S_IFMT) == S_IFDIR

    def read_file(self, ino):
        st = self.inode(ino)
        if self.is_dir(st):
            raise ValueError('inode %d is a directory' % ino)
        if st['flags'] & FLAG_COMPRESSED:
            raise ValueError('inode %d is compressed; refusing to back up '
                             'opaque bytes' % ino)
        if st['dindirect'] != 0:
            raise ValueError('inode %d uses double-indirect blocks; '
                             'refusing to back up' % ino)
        size = st['size']
        if size > MAX_FILE_BYTES:
            raise ValueError('inode %d too large (%d bytes)' % (ino, size))
        phys = list(st['direct'])
        if st['indirect'] != 0:
            ib = self.img.blk(st['indirect'])
            phys.extend(u32(ib, j * 4) for j in range(PER_INDIRECT))
        out = bytearray()
        done = 0
        bi = 0
        while done < size:
            if bi >= len(phys):
                raise ValueError('inode %d truncated' % ino)
            p = phys[bi]
            if p == 0 or p >= self.total_blocks:
                raise ValueError('inode %d has bad block' % ino)
            blk = self.img.blk(p)
            take = min(size - done, BLOCK_SIZE)
            out.extend(blk[:take])
            done += take
            bi += 1
        return bytes(out)

    def listdir(self, ino):
        data = self.read_file_dir(ino)
        off = 0
        while off + DIR_HDR <= len(data):
            ci = u32(data, off)
            rl = u16(data, off + 4)
            nl = data[off + 6]
            ft = data[off + 7]
            if rl == 0 or off + rl > len(data):
                break
            if ci > 0 and nl > 0:
                nm = data[off + DIR_HDR:off + DIR_HDR + nl].decode('utf-8')
                yield nm, ci, ft
            off += rl

    def read_file_dir(self, ino):
        st = self.inode(ino)
        if not self.is_dir(st):
            raise ValueError('inode %d is not a directory' % ino)
        if st['flags'] & FLAG_COMPRESSED:
            raise ValueError('directory inode %d is compressed' % ino)
        return self.read_file_raw(st)

    def read_file_raw(self, st):
        size = st['size']
        if size > MAX_FILE_BYTES:
            raise ValueError('directory too large')
        phys = list(st['direct'])
        if st['indirect'] != 0:
            ib = self.img.blk(st['indirect'])
            phys.extend(u32(ib, j * 4) for j in range(PER_INDIRECT))
        out = bytearray()
        done = 0
        bi = 0
        while done < size:
            if bi >= len(phys):
                raise ValueError('directory truncated')
            p = phys[bi]
            if p == 0 or p >= self.total_blocks:
                raise ValueError('directory has bad block')
            blk = self.img.blk(p)
            take = min(size - done, BLOCK_SIZE)
            out.extend(blk[:take])
            done += take
            bi += 1
        return bytes(out)

    def resolve(self, path):
        ino = ROOT_INODE
        for part in path.strip('/').split('/'):
            if not part:
                continue
            st = self.inode(ino)
            if not self.is_dir(st):
                return -1
            found = -1
            for nm, ci, _ft in self.listdir(ino):
                if nm == part:
                    found = ci
                    break
            if found < 0:
                return -1
            ino = found
        return ino


def valid_name(nm):
    if not nm or len(nm) > 255 or '/' in nm or '\x00' in nm:
        return False
    if nm in ('.', '..'):
        return False
    return True


def find_partition_base(fn):
    """Locate the MiniFS partition inside a host image file.

    Returns the byte offset of the partition, or None. Prefers the exact
    layout the build produces (kernel at LBA 9, partition 2048-sector
    aligned after it); falls back to a magic scan.
    """
    size = os.path.getsize(fn)
    with open(fn, 'rb') as f:
        head = f.read(BLOCK_SIZE)
    if len(head) == BLOCK_SIZE and u32(head, 0) == MAGIC:
        return 0
    here = os.path.dirname(os.path.abspath(__file__))
    kbin = os.path.join(here, '..', 'kernel.bin')
    if os.path.isfile(kbin):
        ksec = (os.path.getsize(kbin) + 511) // 512
        lba = ((9 + ksec + 2047) // 2048) * 2048
        off = lba * 512
        with open(fn, 'rb') as f:
            f.seek(off)
            sb = f.read(BLOCK_SIZE)
        if (len(sb) == BLOCK_SIZE and u32(sb, 0) == MAGIC
                and u32(sb, 4) == VERSION and u32(sb, 8) == BLOCK_SIZE):
            return off
    with open(fn, 'rb') as f:
        off = 0
        while off < min(size, 64 * 1024 * 1024):
            f.seek(off)
            sb = f.read(BLOCK_SIZE)
            if len(sb) < BLOCK_SIZE:
                break
            if (u32(sb, 0) == MAGIC and u32(sb, 4) == VERSION
                    and u32(sb, 8) == BLOCK_SIZE and u32(sb, 12) > 0):
                return off
            off += BLOCK_SIZE
    return None


def cmd_backup(img_path, stage):
    if not os.path.isfile(img_path):
        print('minifs_saves: %s not present, nothing to preserve' % img_path)
        return 0
    base = find_partition_base(img_path)
    if base is None:
        print('minifs_saves: no MiniFS partition in %s, nothing to preserve'
              % img_path)
        return 0
    img = Image(img_path, base)
    try:
        fs = FS(img)
    except ValueError as e:
        print('minifs_saves: cannot read filesystem: %s' % e)
        return 0
    ino = fs.resolve('saves')
    if ino < 0 or not fs.is_dir(fs.inode(ino)):
        print('minifs_saves: no saves/ in %s, nothing to preserve' % img_path)
        return 0
    total = [0]
    count = [0]

    def walk(dir_ino, rel):
        n = 0
        for nm, ci, ft in fs.listdir(dir_ino):
            if not valid_name(nm):
                raise ValueError('unsafe entry name %r under saves/' % nm)
            n += 1
            if n > MAX_ENTRIES:
                raise ValueError('too many entries under saves/')
            if ft == FT_DIR:
                walk(ci, rel + nm + '/')
            else:
                data = fs.read_file(ci)
                total[0] += len(data)
                if total[0] > MAX_TOTAL_BYTES:
                    raise ValueError('saves/ exceeds backup bound')
                dst = os.path.join(stage, 'saves', rel, nm)
                os.makedirs(os.path.dirname(dst), exist_ok=True)
                with open(dst, 'wb') as f:
                    f.write(data)
                count[0] += 1
                print('  keep saves/%s%s (%d bytes)' % (rel, nm, len(data)))

    try:
        walk(ino, '')
    except ValueError as e:
        print('minifs_saves: backup refused: %s' % e, file=sys.stderr)
        return 1
    finally:
        img.close()
    if count[0] == 0:
        print('minifs_saves: saves/ is empty, nothing to preserve')
        return 0
    print('minifs_saves: preserved %d file(s), %d bytes -> %s/saves/'
          % (count[0], total[0], stage))
    return 0


def main(argv):
    if len(argv) != 4 or argv[1] != 'backup':
        print('Usage: minifs_saves.py backup <os.img|minifs.bin> <stagedir>')
        return 2
    return cmd_backup(argv[2], argv[3])


if __name__ == '__main__':
    sys.exit(main(sys.argv))
