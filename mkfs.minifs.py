#!/usr/bin/env python3
"""mkfs.minifs.py - Create a MiniFS filesystem image for MiniOS.

Usage: python3 mkfs.minifs.py <output_file> <total_blocks> [files...]
       python3 mkfs.minifs.py minifs.bin 32768
       python3 mkfs.minifs.py minifs.bin 32768 -d files/
"""
import struct
import os
import sys

MAGIC = 0x4D494E49
VERSION = 1
BLOCK_SIZE = 4096
ROOT_INODE = 2
S_IFREG = 0o100000
S_IFDIR = 0o040000
FT_FILE = 1
FT_DIR = 2
DIR_ENTRY_HDR_SIZE = 8

def roundup4(v):
    return (v + 3) & ~3

def div_round_up(n, d):
    return (n + d - 1) // d

def crc16(data):
    crc = 0xFFFF
    for b in data:
        crc ^= b
        for _ in range(8):
            crc = (crc >> 1) ^ (0xA001 if (crc & 1) else 0)
    return crc & 0xFFFF

def crc32(data):
    crc = 0xFFFFFFFF
    for b in data:
        crc ^= b
        for _ in range(8):
            crc = (crc >> 1) ^ (0xEDB88320 if (crc & 1) else 0)
    return crc ^ 0xFFFFFFFF

class MiniFS:
    def __init__(self, total_blocks):
        self.total_blocks = total_blocks
        self.ibm_blocks = 1
        self.bbm_blocks = div_round_up(total_blocks, BLOCK_SIZE * 8)
        self.it_blocks = 16
        self.data_start = 1 + self.ibm_blocks + self.bbm_blocks + self.it_blocks
        self.total_inodes = self.it_blocks * (BLOCK_SIZE // 128)

        self.ibitmap = bytearray(BLOCK_SIZE * self.ibm_blocks)
        self.bbitmap = bytearray(BLOCK_SIZE * self.bbm_blocks)
        self.inodes = [bytearray(128) for _ in range(self.total_inodes)]

        self.next_inode = ROOT_INODE + 1
        self.next_block = self.data_start

        self.blocks = [bytearray(BLOCK_SIZE) for _ in range(self.total_blocks)]

        self.mark_inodes_used(0, self.data_start)
        self.mark_blocks_used(0, self.data_start)

        self.create_root()

    def mark_inodes_used(self, start, count):
        for i in range(start, min(start + count, len(self.ibitmap) * 8)):
            self.ibitmap[i // 8] |= 1 << (i % 8)

    def mark_blocks_used(self, start, count):
        for i in range(start, min(start + count, len(self.bbitmap) * 8)):
            self.bbitmap[i // 8] |= 1 << (i % 8)

    def alloc_inode(self):
        num = self.next_inode
        self.next_inode += 1
        self.mark_inodes_used(num, 1)
        return num

    def alloc_block(self):
        num = self.next_block
        self.next_block += 1
        self.mark_blocks_used(num, 1)
        return num

    def create_root(self):
        ino = ROOT_INODE
        self.mark_inodes_used(ino, 1)
        mode = S_IFDIR | 0o755
        struct.pack_into('<HHiIIII', self.inodes[ino], 0,
                         mode, 2, 0, 0, 0, 0, 0)
        self.inodes[ino][124:128] = struct.pack('<I', crc32(bytes(self.inodes[ino][:124])))

    def create_inode(self, mode):
        ino = self.alloc_inode()
        struct.pack_into('<HHiIIII', self.inodes[ino], 0,
                         mode, 1, 0, 0, 0, 0, 0)
        self.inodes[ino][124:128] = struct.pack('<I', crc32(bytes(self.inodes[ino][:124])))
        return ino

    def inode_set_size(self, ino, size):
        struct.pack_into('<I', self.inodes[ino], 8, size)
        self.inodes[ino][124:128] = struct.pack('<I', crc32(bytes(self.inodes[ino][:124])))

    def inode_set_block(self, ino, logblk, phys):
        if logblk < 10:
            struct.pack_into('<I', self.inodes[ino], 24 + logblk * 4, phys)
        else:
            logblk -= 10
            per = BLOCK_SIZE // 4
            if logblk < per:
                if struct.unpack_from('<I', self.inodes[ino], 64)[0] == 0:
                    b = self.alloc_block()
                    struct.pack_into('<I', self.inodes[ino], 64, b)
                indir = struct.unpack_from('<I', self.inodes[ino], 64)[0]
                struct.pack_into('<I', self.blocks[indir], logblk * 4, phys)
            else:
                logblk -= per
                if struct.unpack_from('<I', self.inodes[ino], 68)[0] == 0:
                    b = self.alloc_block()
                    self.blocks[b][:] = bytes(BLOCK_SIZE)
                    struct.pack_into('<I', self.inodes[ino], 68, b)
                dindir = struct.unpack_from('<I', self.inodes[ino], 68)[0]
                l1idx = logblk // per
                l2idx = logblk % per
                l1 = struct.unpack_from('<I', self.blocks[dindir], l1idx * 4)[0]
                if l1 == 0:
                    b = self.alloc_block()
                    self.blocks[b][:] = bytes(BLOCK_SIZE)
                    l1 = b
                    struct.pack_into('<I', self.blocks[dindir], l1idx * 4, l1)
                struct.pack_into('<I', self.blocks[l1], l2idx * 4, phys)
        self.inodes[ino][124:128] = struct.pack('<I', crc32(bytes(self.inodes[ino][:124])))

    def add_dir_entry(self, dir_ino, name, child_ino, ftype):
        data = bytes(self.inodes[dir_ino])
        size = struct.unpack_from('<I', data, 8)[0]
        name_bytes = name.encode('utf-8')
        entry_len = roundup4(DIR_ENTRY_HDR_SIZE + len(name_bytes))

        if size > 0:
            nb = (size + BLOCK_SIZE - 1) // BLOCK_SIZE
            last_block_idx = nb - 1
            phys = struct.unpack_from('<I', self.inodes[dir_ino],
                                      24 + last_block_idx * 4)[0]
            buf = bytearray(self.blocks[phys])

            off = 0
            while off < BLOCK_SIZE:
                if struct.unpack_from('<I', buf, off)[0] == 0:
                    break
                rec_len = struct.unpack_from('<H', buf, off + 4)[0]
                if rec_len == 0:
                    break
                off += rec_len

            if off < BLOCK_SIZE and off + entry_len <= BLOCK_SIZE:
                struct.pack_into('<IHBB', buf, off, child_ino, entry_len, len(name_bytes), ftype)
                buf[off + DIR_ENTRY_HDR_SIZE:off + DIR_ENTRY_HDR_SIZE + len(name_bytes)] = name_bytes
                self.blocks[phys] = buf
                return

        b = self.alloc_block()
        buf = bytearray(BLOCK_SIZE)
        struct.pack_into('<IHBB', buf, 0, child_ino, entry_len, len(name_bytes), ftype)
        buf[DIR_ENTRY_HDR_SIZE:DIR_ENTRY_HDR_SIZE + len(name_bytes)] = name_bytes
        self.blocks[b] = buf

        logblk = size // BLOCK_SIZE
        self.inode_set_block(dir_ino, logblk, b)
        self.inode_set_size(dir_ino, size + BLOCK_SIZE)

    def write_file(self, parent_ino, name, data):
        ino = self.create_inode(S_IFREG | 0o644)
        self.inode_set_size(ino, len(data))

        offset = 0
        logblk = 0
        while offset < len(data):
            b = self.alloc_block()
            chunk = data[offset:offset + BLOCK_SIZE]
            self.blocks[b][:len(chunk)] = chunk
            self.inode_set_block(ino, logblk, b)
            offset += BLOCK_SIZE
            logblk += 1

        self.add_dir_entry(parent_ino, name, ino, FT_FILE)
        return ino

    def write_dir(self, parent_ino, name):
        ino = self.create_inode(S_IFDIR | 0o755)
        self.inodes[ino][2:4] = struct.pack('<H', 2)
        self.add_dir_entry(parent_ino, name, ino, FT_DIR)
        return ino

    def serialize(self):
        header_size = BLOCK_SIZE * self.data_start
        image = bytearray(header_size)

        # Superblock at block 0
        sb = struct.pack('<IIIIIIIIIIIIIBBH',
                         MAGIC, VERSION, BLOCK_SIZE,
                         self.total_blocks,
                         self.total_blocks - self.data_start,
                         self.total_inodes,
                         self.total_inodes - ROOT_INODE,
                         ROOT_INODE,
                         1,                    # inode_bitmap_start
                         1 + self.ibm_blocks,   # block_bitmap_start
                         1 + self.ibm_blocks + self.bbm_blocks,  # inode_table_start
                         self.data_start,
                         self.data_start,       # first_free_hint
                         0,                     # compression
                         0,                     # dirty
                         0)                     # checksum placeholder
        sb_crc = crc16(sb[:len(sb) - 2])
        sb = sb[:len(sb) - 2] + struct.pack('<H', sb_crc)
        image[0:len(sb)] = sb

        # Bitmaps
        off = BLOCK_SIZE * 1
        image[off:off + len(self.ibitmap)] = self.ibitmap

        off = BLOCK_SIZE * (1 + self.ibm_blocks)
        image[off:off + len(self.bbitmap)] = self.bbitmap

        # Inode table
        off = BLOCK_SIZE * (1 + self.ibm_blocks + self.bbm_blocks)
        for i, ino in enumerate(self.inodes):
            image[off + i * 128:off + i * 128 + 128] = ino

        # Data blocks
        for i in range(self.data_start, self.total_blocks):
            off = BLOCK_SIZE * i
            image[off:off + BLOCK_SIZE] = self.blocks[i]

        return bytes(image)


def main():
    if len(sys.argv) < 3:
        print("Usage: mkfs.minifs.py <output> <total_blocks> [files...]")
        print("       mkfs.minifs.py <output> <total_blocks> -d <dir>")
        sys.exit(1)

    output = sys.argv[1]
    total_blocks = int(sys.argv[2])

    fs = MiniFS(total_blocks)

    if len(sys.argv) >= 5 and sys.argv[3] == '-d':
        src_dir = sys.argv[4]
        for entry in sorted(os.listdir(src_dir)):
            path = os.path.join(src_dir, entry)
            if os.path.isfile(path):
                with open(path, 'rb') as f:
                    data = f.read()
                fs.write_file(ROOT_INODE, entry, data)
                print(f"  + {entry} ({len(data)} bytes)")
            elif os.path.isdir(path):
                ino = fs.write_dir(ROOT_INODE, entry)
                for sub in sorted(os.listdir(path)):
                    sub_path = os.path.join(path, sub)
                    if os.path.isfile(sub_path):
                        with open(sub_path, 'rb') as f:
                            data = f.read()
                        fs.write_file(ino, sub, data)
                        print(f"  + {entry}/{sub} ({len(data)} bytes)")
    else:
        def pack_tree(parent_ino, path, rel):
            for sub in sorted(os.listdir(path)):
                sub_path = os.path.join(path, sub)
                if os.path.isfile(sub_path):
                    with open(sub_path, 'rb') as f:
                        data = f.read()
                    fs.write_file(parent_ino, sub, data)
                    print(f"  + {rel}/{sub} ({len(data)} bytes)" if rel else f"  + {sub} ({len(data)} bytes)")
                elif os.path.isdir(sub_path):
                    ino = fs.write_dir(parent_ino, sub)
                    print(f"  + {rel}/{sub}/" if rel else f"  + {sub}/")
                    pack_tree(ino, sub_path, f"{rel}/{sub}" if rel else sub)

        for path in sys.argv[3:]:
            name = os.path.basename(path)
            if os.path.isfile(path):
                with open(path, 'rb') as f:
                    data = f.read()
                fs.write_file(ROOT_INODE, name, data)
                print(f"  + {name} ({len(data)} bytes)")
            elif os.path.isdir(path):
                ino = fs.write_dir(ROOT_INODE, name)
                print(f"  + {name}/")
                pack_tree(ino, path, name)

    image = fs.serialize()
    with open(output, 'wb') as f:
        f.write(image)

    print(f"mkfs.minifs: {output} ({total_blocks} blocks, {total_blocks * 4} KB)")


if __name__ == '__main__':
    main()
