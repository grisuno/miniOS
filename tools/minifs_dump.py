#!/usr/bin/env python3
"""minifs_dump.py - Dump/inspect a MiniFS filesystem image."""
import struct
import sys

MAGIC = 0x4D494E49
BLOCK_SIZE = 4096
ROOT_INODE = 2
S_IFMT = 0o170000
S_IFDIR = 0o040000
DIR_HDR = 8

def u16(d, o): return struct.unpack_from('<H', d, o)[0]
def u32(d, o): return struct.unpack_from('<I', d, o)[0]

def mode_str(m):
    t = 'd' if (m & S_IFMT) == S_IFDIR else '-'
    for s in (6,3,0):
        b = (m >> s) & 7
        t += 'r' if b&4 else '-'
        t += 'w' if b&2 else '-'
        t += 'x' if b&1 else '-'
    return t

class FS:
    def __init__(self, fn):
        with open(fn, 'rb') as f: self.d = f.read()
        self.sb = self._sb()
    def blk(self, n): return self.d[n*BLOCK_SIZE:(n+1)*BLOCK_SIZE]
    def _sb(self):
        b = self.blk(0)
        sb = {}
        for i,n in enumerate(['magic','version','block_size','total_blocks','free_blocks','total_inodes','free_inodes','root_inode','inode_bitmap_start','block_bitmap_start','inode_table_start','data_start','first_free_hint']):
            sb[n] = u32(b, i*4)
        sb['compression'] = b[52]
        sb['dirty'] = b[53]
        return sb
    def inode(self, i):
        b = self.d[self.sb['inode_table_start']*BLOCK_SIZE+i*128:self.sb['inode_table_start']*BLOCK_SIZE+i*128+128]
        r = {}
        r['mode']=u16(b,0); r['nlink']=u16(b,2); r['uid']=u32(b,4); r['size']=u32(b,8)
        r['atime']=u32(b,12); r['ctime']=u32(b,16); r['mtime']=u32(b,20)
        r['direct']=[u32(b,24+j*4) for j in range(10)]
        r['indirect']=u32(b,64); r['dindirect']=u32(b,68)
        r['flags']=u32(b,72); r['checksum']=u32(b,76)
        return r
    def read(self, ino):
        r = self.inode(ino)
        if r['size']==0: return b''
        out = bytearray()
        done = 0
        while done < r['size']:
            lb = done // BLOCK_SIZE
            bo = done % BLOCK_SIZE
            tr = min(r['size']-done, BLOCK_SIZE-bo)
            p = 0
            if lb < 10:
                p = r['direct'][lb]
            elif lb < 10 + BLOCK_SIZE // 4:
                if r.get('indirect', 0) == 0: out.extend(b'\x00'*tr); done += tr; continue
                ib = self.blk(r['indirect'])
                p = u32(ib, (lb - 10) * 4)
            if p: out.extend(self.blk(p)[bo:bo+tr])
            else: out.extend(b'\x00'*tr)
            done += tr
        return bytes(out[:r['size']])
    def resolve(self, path):
        if path in ('/',''): return ROOT_INODE
        ino = ROOT_INODE
        for part in path.strip('/').split('/'):
            if not part: continue
            r = self.inode(ino)
            if (r['mode']&S_IFMT)!=S_IFDIR: return -1
            data = self.read(ino)
            off = 0
            found = False
            while off+DIR_HDR<=len(data):
                ci = u32(data,off); rl=u16(data,off+4); nl=data[off+6]
                if rl==0: break
                if ci>0:
                    nm = data[off+DIR_HDR:off+DIR_HDR+nl].decode('utf-8','replace')
                    if nm==part: ino=ci; found=True; break
                off += rl
            if not found: return -1
        return ino
    def ls(self, ino, prefix=''):
        r = self.inode(ino)
        if r['size']==0: return
        data = self.read(ino)
        off = 0
        while off+DIR_HDR<=len(data):
            ci=u32(data,off); rl=u16(data,off+4); nl=data[off+6]; ft=data[off+7]
            if rl==0 or off+rl>len(data): break
            if ci>0:
                nm=data[off+DIR_HDR:off+DIR_HDR+nl].decode('utf-8','replace')
                cr=self.inode(ci)
                c=' [LZ4]' if cr['flags']&1 else ''
                if ft==2:
                    print(f"{prefix}{mode_str(cr['mode'])} {cr['size']:>10}  {nm}/")
                    self.ls(ci, prefix+'  ')
                else:
                    print(f"{prefix}{mode_str(cr['mode'])} {cr['size']:>10}  {nm}{c}")
            off += rl

def main():
    if len(sys.argv)<2:
        print("Usage: minifs_dump.py <image> [path [-o file]]")
        sys.exit(1)
    fs = FS(sys.argv[1])
    sb = fs.sb
    print(f"MiniFS v{sb['version']}: {sb['total_blocks']} blocks x {sb['block_size']} bytes")
    print(f"  free: {sb['free_blocks']} blocks, {sb['free_inodes']} inodes")
    print(f"  compression: {sb['compression']}, dirty: {sb['dirty']}")
    if len(sys.argv)<3:
        fs.ls(ROOT_INODE)
    else:
        p = sys.argv[2]
        i = fs.resolve(p)
        if i<0: print(f"{p}: not found",file=sys.stderr); sys.exit(1)
        data = fs.read(i)
        if len(sys.argv)>=5 and sys.argv[3]=='-o':
            with open(sys.argv[4],'wb') as f: f.write(data)
            print(f"{p}: {len(data)} bytes -> {sys.argv[4]}")
        else:
            sys.stdout.buffer.write(data)

if __name__=='__main__': main()
