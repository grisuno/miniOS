#!/usr/bin/env python3
"""minifs_fsck.py - Check MiniFS filesystem consistency."""
import struct
import sys

MAGIC = 0x4D494E49
BLOCK_SIZE = 4096
ROOT_INODE = 2
DIR_HDR = 8
S_IFMT = 0o170000
S_IFDIR = 0o040000

def u16(d,o): return struct.unpack_from('<H',d,o)[0]
def u32(d,o): return struct.unpack_from('<I',d,o)[0]

class FSCK:
    def __init__(self, fn):
        with open(fn,'rb') as f: self.d=f.read()
        self.base = self._find_base()
        self.errors = 0
        self.sb = self._sb()
        self.bmap = bytearray(self.sb['total_blocks'])
        self.imap = bytearray(self.sb['total_inodes'])
    def _find_base(self):
        if len(self.d) >= BLOCK_SIZE and u32(self.d,0) == MAGIC:
            return 0
        import os
        here = os.path.dirname(os.path.abspath(__file__))
        kbin = os.path.join(here, 'kernel.bin')
        if os.path.isfile(kbin):
            ksec = (os.path.getsize(kbin) + 511) // 512
            lba = ((9 + ksec + 2047) // 2048) * 2048
            off = lba * 512
            if off + BLOCK_SIZE <= len(self.d) and u32(self.d,off) == MAGIC:
                return off
        off = 0
        while off < min(len(self.d), 64 * 1024 * 1024):
            if off + BLOCK_SIZE <= len(self.d) and u32(self.d,off) == MAGIC:
                return off
            off += BLOCK_SIZE
        return 0
    def blk(self,n):
        o = self.base + n*BLOCK_SIZE
        return self.d[o:o+BLOCK_SIZE]
    def _sb(self):
        b=self.blk(0)
        sb={}
        for i,n in enumerate(['magic','version','block_size','total_blocks','free_blocks','total_inodes','free_inodes','root_inode','inode_bitmap_start','block_bitmap_start','inode_table_start','data_start','first_free_hint']):
            sb[n]=u32(b,i*4)
        return sb
    def inode(self,i):
        o=self.base+self.sb['inode_table_start']*BLOCK_SIZE+i*128
        b=self.d[o:o+128]
        r={'mode':u16(b,0),'nlink':u16(b,2),'size':u32(b,8),'flags':u32(b,72)}
        r['direct']=[u32(b,24+j*4) for j in range(10)]
        r['indirect']=u32(b,64)
        return r
    def read(self,ino):
        r=self.inode(ino)
        if r['size']==0: return b''
        out=bytearray(); done=0
        while done<r['size']:
            lb=done//BLOCK_SIZE; bo=done%BLOCK_SIZE; tr=min(r['size']-done,BLOCK_SIZE-bo)
            p=0
            if lb<10: p=r['direct'][lb]
            elif lb<10+BLOCK_SIZE//4:
                if r.get('indirect',0)==0: out.extend(b'\x00'*tr); done+=tr; continue
                ib=self.blk(r['indirect']); p=u32(ib,(lb-10)*4)
            if p: out.extend(self.blk(p)[bo:bo+tr])
            else: out.extend(b'\x00'*tr)
            done+=tr
        return bytes(out[:r['size']])
    def err(self, msg):
        print(f"  ERROR: {msg}"); self.errors+=1
    def mark_block(self, n):
        if n==0: return
        if n<self.sb['data_start'] or n>=self.sb['total_blocks']:
            self.err(f"block {n} out of range"); return
        self.bmap[n]=1
    def scan_inode(self, i):
        if i<ROOT_INODE or i>=self.sb['total_inodes']: return
        self.imap[i]=1
        r=self.inode(i)
        sz=r['size']
        if sz>0:
            blks=(sz+BLOCK_SIZE-1)//BLOCK_SIZE
            for j in range(min(blks,10)):
                self.mark_block(r['direct'][j])
    def scan_dir(self, ino):
        r=self.inode(ino)
        if (r['mode']&S_IFMT)!=S_IFDIR: return
        data=self.read(ino); off=0
        while off+DIR_HDR<=len(data):
            ci=u32(data,off); rl=u16(data,off+4); nl=data[off+6]; ft=data[off+7]
            if rl==0: break
            if rl < DIR_HDR or off+rl > len(data):
                self.err(f"dir inode {ino}: entry at {off} has bad rec_len {rl}")
                break
            if ci>0 and nl>0:
                minimal = ((DIR_HDR+nl+3)&~3)
                if rl < minimal:
                    raw = data[off+DIR_HDR:off+DIR_HDR+nl]
                    self.err(f"dir inode {ino}: entry {raw!r} name spills past record (rl={rl} < {minimal})")
                else:
                    raw = data[off+DIR_HDR:off+DIR_HDR+nl]
                    try:
                        nm = raw.decode('utf-8')
                    except UnicodeDecodeError:
                        self.err(f"dir inode {ino}: entry at {off} name not utf-8")
                        nm = ''
                    if any(ord(c) < 32 or ord(c) == 127 for c in nm):
                        self.err(f"dir inode {ino}: entry {nm!r} has control chars")
                if ci<ROOT_INODE or ci>=self.sb['total_inodes']:
                    self.err(f"dir inode {ino}: entry inode {ci} out of range")
                else:
                    self.scan_inode(ci)
                    if ft==2: self.scan_dir(ci)
                if ft not in (1,2,3):
                    self.err(f"dir inode {ino}: entry at {off} has bad file_type {ft}")
            off+=rl
    def run(self):
        sb=self.sb
        print(f"MiniFS v{sb['version']}: {sb['total_blocks']} blocks, {sb['total_inodes']} inodes")
        if sb['magic']!=MAGIC: self.err(f"bad magic: 0x{sb['magic']:08X}"); return
        self.scan_dir(ROOT_INODE)
        err=0
        for i in range(ROOT_INODE, sb['total_inodes']):
            used = self.imap[i]
            bitmap = 0  # Would need to read actual bitmap
            if used: self.scan_inode(i)
        print(f"  blocks: {sb['total_blocks']-sb['free_blocks']} used, {sb['free_blocks']} free")
        print(f"  inodes: {sb['total_inodes']-sb['free_inodes']} used, {sb['free_inodes']} free")
        print(f"  errors: {self.errors}")
        return self.errors==0

def main():
    if len(sys.argv)<2:
        print("Usage: minifs_fsck.py <image>"); sys.exit(1)
    fsck=FSCK(sys.argv[1])
    ok=fsck.run()
    sys.exit(0 if ok else 1)

if __name__=='__main__': main()
