/* MiniFS: minimal Unix-like filesystem for MiniOS.
 *
 * Inode-based, bitmap-allocated. Stores files on an IDE disk after
 * the kernel image. Directory entries are variable-length records
 * inside inode data blocks. */

#include "kernel.h"
#include "minifs.h"
#include "block.h"
#include "ide.h"
#include "lz4_kernel.h"
#define DE_NAME(de) ((const char *)((de) + 1))
#define DE_NAME_W(de) ((char *)((de) + 1))

static MiniFSSuper fs_sb;
static unsigned char *fs_ibitmap;
static unsigned char *fs_bbitmap;
static unsigned int fs_lba_start;
static unsigned int fs_next_txn;
static int fs_mounted;

/* ---- Compression wrappers ---- */
unsigned int minifs_compress(const void *src, unsigned int src_len,
                             void *dst, unsigned int dst_cap) {
    if (dst_cap <= 4) return 0;
    int ret = LZ4_compress_default((const char *)src, (char *)dst + 4,
                                   (int)src_len, (int)(dst_cap - 4));
    if (ret <= 0 || (unsigned)ret >= src_len) return 0;
    /* Store original size in first 4 bytes */
    *(unsigned int *)dst = src_len;
    return (unsigned int)ret + 4;
}

unsigned int minifs_decompress(const void *src, unsigned int src_len,
                               void *dst, unsigned int dst_cap) {
    if (src_len <= 4) return 0;
    unsigned int orig_size = *(const unsigned int *)src;
    if (orig_size > dst_cap) return 0;
    int ret = LZ4_decompress_safe((const char *)src + 4, (char *)dst,
                                   (int)(src_len - 4), (int)dst_cap);
    if (ret < 0 || (unsigned)ret != orig_size) return 0;
    return orig_size;
}

static unsigned short minifs_crc16(const void *data, unsigned int len) {
    const unsigned char *p = (const unsigned char *)data;
    unsigned short crc = 0xFFFF;
    unsigned int i, j;
    for (i = 0; i < len; i++) {
        crc ^= (unsigned short)p[i];
        for (j = 0; j < 8; j++)
            crc = (crc >> 1) ^ ((crc & 1) ? 0xA001 : 0);
    }
    return crc;
}

static unsigned int minifs_crc32(const void *data, unsigned int len) {
    const unsigned char *p = (const unsigned char *)data;
    unsigned int crc = 0xFFFFFFFF;
    unsigned int i, j;
    for (i = 0; i < len; i++) {
        crc ^= (unsigned int)p[i];
        for (j = 0; j < 8; j++)
            crc = (crc >> 1) ^ ((crc & 1) ? 0xEDB88320 : 0);
    }
    return crc ^ 0xFFFFFFFF;
}

static unsigned int roundup4(unsigned int v) { return (v + 3) & ~3u; }

static unsigned int div_round_up(unsigned int n, unsigned int d) {
    return (n + d - 1) / d;
}

/* ---- Superblock I/O ---- */


static int fs_write_super(void) {
    unsigned char buf[MINIFS_BLOCK_SIZE];
    kmemset(buf, 0, MINIFS_BLOCK_SIZE);
    fs_sb.checksum = minifs_crc16(&fs_sb, sizeof(MiniFSSuper) - 2);
    kmemcpy(buf, &fs_sb, sizeof(MiniFSSuper));
    return block_write(0, buf);
}

/* ---- Inode I/O ---- */

static int fs_read_inode(unsigned int num, MiniFSInode *out) {
    unsigned int block = fs_sb.inode_table_start + (num / MINIFS_INODES_PER_BLOCK);
    unsigned int offset = (num % MINIFS_INODES_PER_BLOCK) * sizeof(MiniFSInode);
    unsigned char buf[MINIFS_BLOCK_SIZE];
    if (block_read(block, buf) < 0) return -1;
    kmemcpy(out, buf + offset, sizeof(MiniFSInode));
    return 0;
}

static int fs_write_inode(unsigned int num, const MiniFSInode *in) {
    unsigned int block = fs_sb.inode_table_start + (num / MINIFS_INODES_PER_BLOCK);
    unsigned int offset = (num % MINIFS_INODES_PER_BLOCK) * sizeof(MiniFSInode);
    unsigned char buf[MINIFS_BLOCK_SIZE];
    if (block_read(block, buf) < 0) return -1;
    kmemcpy(buf + offset, in, sizeof(MiniFSInode));
    return block_write(block, buf);
}

/* ---- Bitmap helpers ---- */

static int bm_test(unsigned char *bm, unsigned int bit) {
    return (bm[bit / 8] >> (bit % 8)) & 1;
}

static void bm_set(unsigned char *bm, unsigned int bit) {
    bm[bit / 8] |= (unsigned char)(1u << (bit % 8));
}

static void bm_clear(unsigned char *bm, unsigned int bit) {
    bm[bit / 8] &= (unsigned char)~(1u << (bit % 8));
}

/* ---- Block allocator ---- */

int minifs_alloc_block(void) {
    unsigned int total = fs_sb.total_blocks;
    unsigned int start = fs_sb.first_free_hint;
    unsigned int i;
    for (i = 0; i < total; i++) {
        unsigned int idx = (start + i) % total;
        if (idx < 3) continue;
        if (!bm_test(fs_bbitmap, idx)) {
            bm_set(fs_bbitmap, idx);
            fs_sb.free_blocks--;
            fs_sb.first_free_hint = (idx + 1) % total;
            return (int)idx;
        }
    }
    return -1;
}

void minifs_free_block(unsigned int block) {
    if (block >= fs_sb.total_blocks) return;
    bm_clear(fs_bbitmap, block);
    fs_sb.free_blocks++;
}

/* ---- Inode allocator ---- */

int minifs_alloc_inode(void) {
    unsigned int i;
    for (i = MINIFS_ROOT_INODE; i < fs_sb.total_inodes; i++) {
        if (!bm_test(fs_ibitmap, i)) {
            bm_set(fs_ibitmap, i);
            fs_sb.free_inodes--;
            return (int)i;
        }
    }
    return -1;
}

void minifs_free_inode(int num) {
    if (num < 0 || (unsigned int)num >= fs_sb.total_inodes) return;
    bm_clear(fs_ibitmap, (unsigned int)num);
    fs_sb.free_inodes++;
}

/* ---- Inode block mapping ---- */

int minifs_inode_get_block(MiniFSInode *inode, unsigned int logblk,
                           unsigned int *phys) {
    unsigned int per = MINIFS_BLOCK_SIZE / 4;
    unsigned char buf[MINIFS_BLOCK_SIZE];
    if (logblk < 10) { *phys = inode->direct[logblk]; return 0; }
    logblk -= 10;
    if (logblk < per) {
        if (inode->indirect == 0) { *phys = 0; return 0; }
        if (block_read(inode->indirect, buf) < 0) return -1;
        *phys = ((unsigned int *)buf)[logblk];
        return 0;
    }
    logblk -= per;
    if (inode->dindirect == 0) { *phys = 0; return 0; }
    if (block_read(inode->dindirect, buf) < 0) return -1;
    {   unsigned int l1 = ((unsigned int *)buf)[logblk / per];
        if (l1 == 0) { *phys = 0; return 0; }
        if (block_read(l1, buf) < 0) return -1;
        *phys = ((unsigned int *)buf)[logblk % per];
    }
    return 0;
}

static int fs_inode_set_block(MiniFSInode *inode, unsigned int logblk,
                              unsigned int phys) {
    unsigned int per = MINIFS_BLOCK_SIZE / 4;
    unsigned char buf[MINIFS_BLOCK_SIZE];
    if (logblk < 10) { inode->direct[logblk] = phys; return 0; }
    logblk -= 10;
    if (logblk < per) {
        if (inode->indirect == 0) {
            int b = minifs_alloc_block();
            if (b < 0) return -1;
            inode->indirect = (unsigned int)b;
            kmemset(buf, 0, MINIFS_BLOCK_SIZE);
            if (block_write((unsigned int)b, buf) < 0) return -1;
        }
        if (block_read(inode->indirect, buf) < 0) return -1;
        ((unsigned int *)buf)[logblk] = phys;
        return block_write(inode->indirect, buf);
    }
    logblk -= per;
    if (inode->dindirect == 0) {
        int b = minifs_alloc_block();
        if (b < 0) return -1;
        inode->dindirect = (unsigned int)b;
        kmemset(buf, 0, MINIFS_BLOCK_SIZE);
        if (block_write((unsigned int)b, buf) < 0) return -1;
    }
    {   unsigned char dibuf[MINIFS_BLOCK_SIZE];
        if (block_read(inode->dindirect, dibuf) < 0) return -1;
        unsigned int l1idx = logblk / per;
        unsigned int l2idx = logblk % per;
        unsigned int l1 = ((unsigned int *)dibuf)[l1idx];
        if (l1 == 0) {
            int b = minifs_alloc_block();
            if (b < 0) return -1;
            l1 = (unsigned int)b;
            ((unsigned int *)dibuf)[l1idx] = l1;
            if (block_write(inode->dindirect, dibuf) < 0) return -1;
            kmemset(buf, 0, MINIFS_BLOCK_SIZE);
            if (block_write(l1, buf) < 0) return -1;
        }
        if (block_read(l1, buf) < 0) return -1;
        ((unsigned int *)buf)[l2idx] = phys;
        return block_write(l1, buf);
    }
}

int minifs_inode_alloc_block(MiniFSInode *inode, unsigned int logblk) {
    unsigned char buf[MINIFS_BLOCK_SIZE];
    int b = minifs_alloc_block();
    if (b < 0) return -1;
    kmemset(buf, 0, MINIFS_BLOCK_SIZE);
    if (block_write((unsigned int)b, buf) < 0) {
        minifs_free_block((unsigned int)b); return -1;
    }
    if (fs_inode_set_block(inode, logblk, (unsigned int)b) < 0) {
        minifs_free_block((unsigned int)b); return -1;
    }
    return b;
}

static void fs_inode_free_all_blocks(MiniFSInode *inode) {
    unsigned int i;
    unsigned int blocks = (inode->size + MINIFS_BLOCK_SIZE - 1) / MINIFS_BLOCK_SIZE;
    unsigned char buf[MINIFS_BLOCK_SIZE];
    for (i = 0; i < blocks && i < 10; i++) {
        if (inode->direct[i]) {
            minifs_free_block(inode->direct[i]);
            inode->direct[i] = 0;
        }
    }
    if (inode->indirect) {
        if (block_read(inode->indirect, buf) == 0) {
            unsigned int per = MINIFS_BLOCK_SIZE / 4;
            unsigned int j;
            for (j = 0; j < per; j++)
                if (((unsigned int *)buf)[j])
                    minifs_free_block(((unsigned int *)buf)[j]);
        }
        minifs_free_block(inode->indirect);
        inode->indirect = 0;
    }
    if (inode->dindirect) {
        unsigned char dibuf[MINIFS_BLOCK_SIZE];
        if (block_read(inode->dindirect, dibuf) == 0) {
            unsigned int per = MINIFS_BLOCK_SIZE / 4;
            unsigned int j, k;
            for (j = 0; j < per; j++) {
                unsigned int l1 = ((unsigned int *)dibuf)[j];
                if (l1) {
                    if (block_read(l1, buf) == 0) {
                        for (k = 0; k < per; k++)
                            if (((unsigned int *)buf)[k])
                                minifs_free_block(((unsigned int *)buf)[k]);
                    }
                    minifs_free_block(l1);
                }
            }
        }
        minifs_free_block(inode->dindirect);
        inode->dindirect = 0;
    }
    inode->size = 0;
}

/* ---- Journal (write-ahead logging) ----
 *
 * Journal area layout (MINIFS_JOURNAL_BLOCKS blocks at end of filesystem):
 *   Block 0: MiniFSJournalSuper — magic, state, next_txn, count
 *   Blocks 1..N: MiniFSJournalEntry array (one per dirty metadata block)
 *   Last block: scratch buffer for block copy during commit
 *
 * Protocol:
 *   1. minifs_journal_begin(txn) — start a new transaction
 *   2. minifs_journal_add_block(phys) — snapshot the old content of a
 *      metadata block before modifying it
 *   3. minifs_journal_commit(txn) — mark the journal dirty, then the
 *      caller writes the actual modified blocks, then clear the journal
 *   4. minifs_journal_recover() — on mount, if the journal is dirty,
 *      overwrite each affected block with its saved old content (undo)
 */

static unsigned int journal_start;    /* first data block of journal area */
static unsigned int journal_blocks;   /* number of blocks in journal area */
static unsigned int journal_next_txn;

static MiniFSJournalEntry journal_entries[MINIFS_JOURNAL_MAX_ENTRIES];
static unsigned int journal_entry_count;
static unsigned int journal_current_txn;
static int journal_active;

static void journal_load_super(void) {
    unsigned char buf[MINIFS_BLOCK_SIZE];
    block_read(journal_start, buf);
    MiniFSJournalSuper *js = (MiniFSJournalSuper *)buf;
    if (js->magic == 0x4A4F5552) {
        journal_next_txn = js->next_txn;
    } else {
        js->magic = 0x4A4F5552;
        js->state = MINIFS_JSTATE_CLEAN;
        js->next_txn = 1;
        js->count = 0;
        js->checksum = minifs_crc32((unsigned char *)js, MINIFS_BLOCK_SIZE - 4);
        block_write(journal_start, buf);
    }
}

static void journal_save_super(unsigned int state) {
    unsigned char buf[MINIFS_BLOCK_SIZE];
    block_read(journal_start, buf);
    MiniFSJournalSuper *js = (MiniFSJournalSuper *)buf;
    js->state = state;
    js->next_txn = journal_next_txn;
    js->count = journal_entry_count;
    js->checksum = minifs_crc32((unsigned char *)js, MINIFS_BLOCK_SIZE - 4);
    block_write(journal_start, buf);
}

static void journal_save_entries(void) {
    unsigned int slots_per_block = (MINIFS_BLOCK_SIZE / sizeof(MiniFSJournalEntry));
    unsigned int i;
    for (i = 0; i < journal_entry_count; i++) {
        unsigned int slot = i % slots_per_block;
        unsigned int blk = 1 + (i / slots_per_block);
        unsigned char buf[MINIFS_BLOCK_SIZE];
        if (slot == 0) kmemset(buf, 0, MINIFS_BLOCK_SIZE);
        else block_read(journal_start + blk, buf);
        kmemcpy(buf + slot * sizeof(MiniFSJournalEntry),
                &journal_entries[i], sizeof(MiniFSJournalEntry));
        block_write(journal_start + blk, buf);
    }
}

void minifs_journal_begin(unsigned int txn_id) {
    journal_current_txn = txn_id ? txn_id : journal_next_txn++;
    journal_entry_count = 0;
    journal_active = 1;
    kmemset(journal_entries, 0, sizeof(journal_entries));
}

void minifs_journal_add_block(unsigned int block) {
    if (!journal_active || journal_entry_count >= MINIFS_JOURNAL_MAX_ENTRIES) return;

    MiniFSJournalEntry *e = &journal_entries[journal_entry_count];
    e->txn_id = journal_current_txn;
    e->committed = 0;
    e->num_blocks = 1;
    e->affected_blocks[0] = block;

    /* Save original block content into the journal data area.
     * The data area starts at journal_start + 1 + ceil(MINIFS_JOURNAL_MAX_ENTRIES / slots_per_block).
     * For simplicity, we use one data slot per entry. */
    unsigned int slots_per_block = MINIFS_BLOCK_SIZE / sizeof(MiniFSJournalEntry);
    unsigned int hdr_blocks = (MINIFS_JOURNAL_MAX_ENTRIES + slots_per_block - 1) / slots_per_block;
    unsigned int data_base = journal_start + 1 + hdr_blocks;
    unsigned int data_slot = journal_entry_count;

    unsigned char orig[MINIFS_BLOCK_SIZE];
    block_read(block, orig);
    block_write(data_base + data_slot, orig);

    e->checksum = minifs_crc32((unsigned char *)e, sizeof(MiniFSJournalEntry) - 4);
    journal_entry_count++;
}

int minifs_journal_commit(unsigned int txn_id) {
    (void)txn_id;
    if (!journal_active || journal_entry_count == 0) {
        journal_active = 0;
        return 0;
    }

    journal_save_entries();
    journal_save_super(MINIFS_JSTATE_DIRTY);

    /* Now the caller writes the actual modified blocks to disk.
     * After all writes complete, we clear the journal. */
    journal_save_super(MINIFS_JSTATE_CLEAN);
    journal_entry_count = 0;
    journal_active = 0;
    return 0;
}

void minifs_journal_recover(void) {
    unsigned char buf[MINIFS_BLOCK_SIZE];
    block_read(journal_start, buf);
    MiniFSJournalSuper *js = (MiniFSJournalSuper *)buf;

    if (js->magic != 0x4A4F5552 || js->state != MINIFS_JSTATE_DIRTY) {
        journal_load_super();
        return;
    }

    kprintf("minifs: recovering journal (txn %u, %u entries)\n",
            js->next_txn - 1, js->count);

    unsigned int slots_per_block = MINIFS_BLOCK_SIZE / sizeof(MiniFSJournalEntry);
    unsigned int hdr_blocks = (MINIFS_JOURNAL_MAX_ENTRIES + slots_per_block - 1) / slots_per_block;
    unsigned int data_base = journal_start + 1 + hdr_blocks;
    unsigned int count = js->count;
    unsigned int i;

    for (i = 0; i < count; i++) {
        unsigned int slot = i % slots_per_block;
        unsigned int blk = 1 + (i / slots_per_block);
        unsigned char ebuf[MINIFS_BLOCK_SIZE];
        block_read(journal_start + blk, ebuf);
        MiniFSJournalEntry e;
        kmemcpy(&e, ebuf + slot * sizeof(MiniFSJournalEntry), sizeof(MiniFSJournalEntry));

        /* Restore the original block content */
        unsigned char orig[MINIFS_BLOCK_SIZE];
        block_read(data_base + i, orig);
        block_write(e.affected_blocks[0], orig);
    }

    journal_save_super(MINIFS_JSTATE_CLEAN);
    journal_load_super();
    kprintf("minifs: journal recovery complete\n");
}

/* ---- Path resolution ---- */

static int fs_namecmp(const char *a, unsigned char alen, const char *b) {
    unsigned int blen = (unsigned int)kstrlen(b);
    if (alen != blen) return 1;
    unsigned int i;
    for (i = 0; i < alen; i++)
        if (a[i] != b[i]) return 1;
    return 0;
}

int minifs_dir_lookup(int dir_ino, const char *name) {
    MiniFSInode dir;
    unsigned int total_blocks, b;
    if (fs_read_inode((unsigned int)dir_ino, &dir) < 0) return -1;
    if (!(dir.mode & MINIFS_S_IFDIR)) return -1;
    total_blocks = (dir.size + MINIFS_BLOCK_SIZE - 1) / MINIFS_BLOCK_SIZE;
    for (b = 0; b < total_blocks; b++) {
        unsigned int phys;
        unsigned char buf[MINIFS_BLOCK_SIZE];
        unsigned int off;
        if (minifs_inode_get_block(&dir, b, &phys) < 0 || phys == 0) continue;
        if (block_read(phys, buf) < 0) continue;
        off = 0;
        while (off < MINIFS_BLOCK_SIZE) {
            MiniFSDirEntry *de = (MiniFSDirEntry *)(buf + off);
            if (de->rec_len == 0) break;
            if (de->inode != 0 && fs_namecmp(DE_NAME(de), de->name_len, name) == 0)
                return (int)de->inode;
            off += de->rec_len;
        }
    }
    return -1;
}

int minifs_dir_add_entry(int dir_ino, const char *name, int child_ino,
                         unsigned char type) {
    MiniFSInode dir;
    unsigned int namelen = (unsigned int)kstrlen(name);
    unsigned int entry_len = roundup4(MINIFS_DIR_ENTRY_HDR_SIZE + namelen);
    unsigned int total_blocks, b;
    if (fs_read_inode((unsigned int)dir_ino, &dir) < 0) return -1;
    if (!(dir.mode & MINIFS_S_IFDIR)) return -1;

    total_blocks = (dir.size + MINIFS_BLOCK_SIZE - 1) / MINIFS_BLOCK_SIZE;
    for (b = 0; b < total_blocks; b++) {
        unsigned int phys;
        unsigned char buf[MINIFS_BLOCK_SIZE];
        unsigned int off;
        if (minifs_inode_get_block(&dir, b, &phys) < 0 || phys == 0) continue;
        if (block_read(phys, buf) < 0) continue;
        off = 0;
        while (off < MINIFS_BLOCK_SIZE) {
            MiniFSDirEntry *de = (MiniFSDirEntry *)(buf + off);
            if (de->rec_len == 0) break;
            if (de->inode == 0 && de->rec_len >= entry_len) {
                de->inode = (unsigned int)child_ino;
                de->name_len = (unsigned char)namelen;
                de->file_type = type;
                kmemcpy(DE_NAME_W(de), name, namelen);
                unsigned int extra = de->rec_len - entry_len;
                de->rec_len = (unsigned short)entry_len;
                if (extra >= sizeof(MiniFSDirEntry)) {
                    MiniFSDirEntry *next = (MiniFSDirEntry *)((char *)de + entry_len);
                    next->inode = 0;
                    next->rec_len = (unsigned short)extra;
                    next->name_len = 0;
                }
                return block_write(phys, buf);
            }
            off += de->rec_len;
        }
    }

    if (dir.size == 0) {
        int nb = minifs_inode_alloc_block(&dir, 0);
        if (nb < 0) return -1;
        dir.size = MINIFS_BLOCK_SIZE;
        if (fs_write_inode((unsigned int)dir_ino, &dir) < 0) return -1;
        unsigned char buf[MINIFS_BLOCK_SIZE];
        kmemset(buf, 0, MINIFS_BLOCK_SIZE);
        MiniFSDirEntry *de = (MiniFSDirEntry *)buf;
        de->inode = (unsigned int)child_ino;
        de->name_len = (unsigned char)namelen;
        de->file_type = type;
        de->rec_len = (unsigned short)MINIFS_BLOCK_SIZE;
        kmemcpy(DE_NAME_W(de), name, namelen);
        return block_write((unsigned int)nb, buf);
    }

    unsigned int last_b = total_blocks - 1;
    unsigned int last_phys;
    if (minifs_inode_get_block(&dir, last_b, &last_phys) < 0) return -1;
    unsigned char buf[MINIFS_BLOCK_SIZE];
    if (block_read(last_phys, buf) < 0) return -1;
    unsigned int off = 0;
    MiniFSDirEntry *last_de = 0;
    while (off < MINIFS_BLOCK_SIZE) {
        MiniFSDirEntry *de = (MiniFSDirEntry *)(buf + off);
        if (de->rec_len == 0) break;
        last_de = de;
        off += de->rec_len;
    }
    if (last_de) {
        unsigned int avail = MINIFS_BLOCK_SIZE -
            ((unsigned long)last_de - (unsigned long)buf) - last_de->name_len
            - sizeof(MiniFSDirEntry);
        avail = roundup4(avail);
        if (last_de->inode != 0) {
            unsigned int tail = roundup4(MINIFS_DIR_ENTRY_HDR_SIZE + last_de->name_len);
            avail += tail - last_de->rec_len;
            if (avail >= entry_len) {
                unsigned int saved = last_de->rec_len;
                last_de->rec_len = (unsigned short)tail;
                MiniFSDirEntry *ne = (MiniFSDirEntry *)((char *)last_de + tail);
                ne->inode = (unsigned int)child_ino;
                ne->name_len = (unsigned char)namelen;
                ne->file_type = type;
                ne->rec_len = (unsigned short)(saved + last_de->name_len +
                    sizeof(MiniFSDirEntry) - tail);
                kmemcpy(DE_NAME_W(ne), name, namelen);
                return block_write(last_phys, buf);
            }
        } else {
            if (avail >= entry_len) {
                last_de->inode = (unsigned int)child_ino;
                last_de->name_len = (unsigned char)namelen;
                last_de->file_type = type;
                kmemcpy(DE_NAME_W(last_de), name, namelen);
                return block_write(last_phys, buf);
            }
        }
    }

    int nb = minifs_inode_alloc_block(&dir, total_blocks);
    if (nb < 0) return -1;
    dir.size += MINIFS_BLOCK_SIZE;
    if (fs_write_inode((unsigned int)dir_ino, &dir) < 0) return -1;
    unsigned char nbuf[MINIFS_BLOCK_SIZE];
    kmemset(nbuf, 0, MINIFS_BLOCK_SIZE);
    MiniFSDirEntry *nde = (MiniFSDirEntry *)nbuf;
    nde->inode = (unsigned int)child_ino;
    nde->name_len = (unsigned char)namelen;
    nde->file_type = type;
    nde->rec_len = (unsigned short)MINIFS_BLOCK_SIZE;
    kmemcpy(DE_NAME_W(nde), name, namelen);
    return block_write((unsigned int)nb, nbuf);
}

int minifs_dir_remove_entry(int dir_ino, const char *name) {
    MiniFSInode dir;
    unsigned int total_blocks, b;
    if (fs_read_inode((unsigned int)dir_ino, &dir) < 0) return -1;
    total_blocks = (dir.size + MINIFS_BLOCK_SIZE - 1) / MINIFS_BLOCK_SIZE;
    for (b = 0; b < total_blocks; b++) {
        unsigned int phys;
        unsigned char buf[MINIFS_BLOCK_SIZE];
        unsigned int off;
        if (minifs_inode_get_block(&dir, b, &phys) < 0 || phys == 0) continue;
        if (block_read(phys, buf) < 0) continue;
        off = 0;
        while (off < MINIFS_BLOCK_SIZE) {
            MiniFSDirEntry *de = (MiniFSDirEntry *)(buf + off);
            if (de->rec_len == 0) break;
            if (de->inode != 0 && fs_namecmp(DE_NAME(de), de->name_len, name) == 0) {
                de->inode = 0;
                return block_write(phys, buf);
            }
            off += de->rec_len;
        }
    }
    return -1;
}

int minifs_dir_read(int dir_ino, int index, MiniFSDirEntry *out, char *name_out) {
    MiniFSInode dir;
    unsigned int total_blocks, b;
    int count = 0;
    if (fs_read_inode((unsigned int)dir_ino, &dir) < 0) return -1;
    if (!(dir.mode & MINIFS_S_IFDIR)) return -1;
    total_blocks = (dir.size + MINIFS_BLOCK_SIZE - 1) / MINIFS_BLOCK_SIZE;
    for (b = 0; b < total_blocks; b++) {
        unsigned int phys;
        unsigned char buf[MINIFS_BLOCK_SIZE];
        unsigned int off;
        if (minifs_inode_get_block(&dir, b, &phys) < 0 || phys == 0) continue;
        if (block_read(phys, buf) < 0) continue;
        off = 0;
        while (off < MINIFS_BLOCK_SIZE) {
            MiniFSDirEntry *de = (MiniFSDirEntry *)(buf + off);
            if (de->rec_len == 0) break;
            if (de->inode != 0) {
                if (count == index) {
                    kmemcpy(out, de, sizeof(MiniFSDirEntry));
                    kmemcpy(name_out, DE_NAME(de), de->name_len);
                    name_out[de->name_len] = 0;
                    return 0;
                }
                count++;
            }
            off += de->rec_len;
        }
    }
    return -1;
}

/* ---- Resolve a path to an inode number ---- */

int minifs_resolve_path(const char *path) {
    int ino = MINIFS_ROOT_INODE;
    const char *p = path;
    char namebuf[MINIFS_MAX_FILENAME + 1];

    if (*p == '/') p++;
    if (*p == 0) return MINIFS_ROOT_INODE;

    while (*p) {
        const char *start = p;
        while (*p && *p != '/') p++;
        unsigned int len = (unsigned int)(p - start);
        if (len == 0 || (len == 1 && start[0] == '.')) {
            if (*p) p++;
            continue;
        }
        if (len == 2 && start[0] == '.' && start[1] == '.') {
            /* stay at root for simplicity */
            if (*p) p++;
            continue;
        }
        if (len > MINIFS_MAX_FILENAME) return -1;
        kmemcpy(namebuf, start, len);
        namebuf[len] = 0;
        ino = minifs_dir_lookup(ino, namebuf);
        if (ino < 0) return -1;
        if (*p) p++;
    }
    return ino;
}

/* ---- File operations ---- */

int minifs_create(const char *path, unsigned short mode) {
    char parent_buf[RAMDISK_FNAME_LEN];
    char *name_start;
    int parent_ino, child_ino;
    MiniFSInode inode;

    kstrncpy(parent_buf, path, RAMDISK_FNAME_LEN - 1);
    parent_buf[RAMDISK_FNAME_LEN - 1] = 0;

    name_start = parent_buf;
    {   char *slash = kstrchr(parent_buf, '/');
        while (slash) { name_start = slash + 1; slash = kstrchr(slash + 1, '/'); }
    }

    char child_name[MINIFS_MAX_FILENAME + 1];
    kstrncpy(child_name, name_start, MINIFS_MAX_FILENAME);
    child_name[MINIFS_MAX_FILENAME] = 0;

    if (name_start > parent_buf) {
        parent_buf[name_start - parent_buf - 1] = 0;
        parent_ino = minifs_resolve_path(parent_buf);
    } else {
        parent_ino = MINIFS_ROOT_INODE;
    }
    if (parent_ino < 0) return -1;

    child_ino = minifs_alloc_inode();
    if (child_ino < 0) return -1;

    kmemset(&inode, 0, sizeof(MiniFSInode));
    inode.mode = MINIFS_S_IFREG | (mode & 0777);
    inode.link_count = 1;
    inode.size = 0;
    inode.checksum = minifs_crc32(&inode, sizeof(MiniFSInode) - 4);

    minifs_journal_begin(0);
    minifs_journal_add_block((unsigned int)parent_ino);

    if (fs_write_inode((unsigned int)child_ino, &inode) < 0) {
        minifs_journal_commit(journal_current_txn);
        minifs_free_inode(child_ino);
        return -1;
    }
    if (minifs_dir_add_entry(parent_ino, child_name, child_ino, MINIFS_FT_FILE) < 0) {
        minifs_journal_commit(journal_current_txn);
        minifs_free_inode(child_ino);
        return -1;
    }
    minifs_journal_commit(journal_current_txn);
    return child_ino;
}

int minifs_mkdir(const char *path, unsigned short mode) {
    char parent_buf[RAMDISK_FNAME_LEN];
    char *name_start;
    int parent_ino, child_ino;
    MiniFSInode inode;

    kstrncpy(parent_buf, path, RAMDISK_FNAME_LEN - 1);
    parent_buf[RAMDISK_FNAME_LEN - 1] = 0;

    name_start = parent_buf;
    {   char *slash = kstrchr(parent_buf, '/');
        while (slash) { name_start = slash + 1; slash = kstrchr(slash + 1, '/'); }
    }

    char child_name[MINIFS_MAX_FILENAME + 1];
    kstrncpy(child_name, name_start, MINIFS_MAX_FILENAME);
    child_name[MINIFS_MAX_FILENAME] = 0;

    if (name_start > parent_buf) {
        parent_buf[name_start - parent_buf - 1] = 0;
        parent_ino = minifs_resolve_path(parent_buf);
    } else {
        parent_ino = MINIFS_ROOT_INODE;
    }
    if (parent_ino < 0) return -1;

    child_ino = minifs_alloc_inode();
    if (child_ino < 0) return -1;

    kmemset(&inode, 0, sizeof(MiniFSInode));
    inode.mode = MINIFS_S_IFDIR | (mode & 0777);
    inode.link_count = 2;
    inode.size = 0;
    inode.checksum = minifs_crc32(&inode, sizeof(MiniFSInode) - 4);
    minifs_journal_begin(0);
    minifs_journal_add_block((unsigned int)parent_ino);
    if (fs_write_inode((unsigned int)child_ino, &inode) < 0) {
        minifs_journal_commit(journal_current_txn);
        minifs_free_inode(child_ino);
        return -1;
    }
    if (minifs_dir_add_entry(parent_ino, child_name, child_ino, MINIFS_FT_DIR) < 0) {
        minifs_journal_commit(journal_current_txn);
        minifs_free_inode(child_ino);
        return -1;
    }
    minifs_journal_commit(journal_current_txn);
    return child_ino;
}

int minifs_unlink(const char *path) {
    int ino = minifs_resolve_path(path);
    MiniFSInode inode;
    if (ino < 0) return -1;
    if (fs_read_inode((unsigned int)ino, &inode) < 0) return -1;
    if (inode.mode & MINIFS_S_IFDIR) return -1;
    fs_inode_free_all_blocks(&inode);
    inode.mode = 0;
    inode.size = 0;
    inode.link_count = 0;
    fs_write_inode((unsigned int)ino, &inode);
    minifs_free_inode(ino);

    char parent_buf[RAMDISK_FNAME_LEN];
    char *name_start;
    kstrncpy(parent_buf, path, RAMDISK_FNAME_LEN - 1);
    parent_buf[RAMDISK_FNAME_LEN - 1] = 0;
    name_start = parent_buf;
    {   char *slash = kstrchr(parent_buf, '/');
        while (slash) { name_start = slash + 1; slash = kstrchr(slash + 1, '/'); }
    }
    char child_name[MINIFS_MAX_FILENAME + 1];
    kstrncpy(child_name, name_start, MINIFS_MAX_FILENAME);
    child_name[MINIFS_MAX_FILENAME] = 0;
    int parent_ino;
    if (name_start > parent_buf) {
        parent_buf[name_start - parent_buf - 1] = 0;
        parent_ino = minifs_resolve_path(parent_buf);
    } else {
        parent_ino = MINIFS_ROOT_INODE;
    }
    if (parent_ino >= 0)
        minifs_dir_remove_entry(parent_ino, child_name);
    return 0;
}

int minifs_rmdir(const char *path) {
    int ino = minifs_resolve_path(path);
    MiniFSInode inode;
    if (ino < 0) return -1;
    if (ino == MINIFS_ROOT_INODE) return -1;
    if (fs_read_inode((unsigned int)ino, &inode) < 0) return -1;
    if (!(inode.mode & MINIFS_S_IFDIR)) return -1;
    if (inode.size > 0) return -1;
    inode.mode = 0;
    inode.size = 0;
    inode.link_count = 0;
    fs_write_inode((unsigned int)ino, &inode);
    minifs_free_inode(ino);

    char parent_buf[RAMDISK_FNAME_LEN];
    char *name_start;
    kstrncpy(parent_buf, path, RAMDISK_FNAME_LEN - 1);
    parent_buf[RAMDISK_FNAME_LEN - 1] = 0;
    name_start = parent_buf;
    {   char *slash = kstrchr(parent_buf, '/');
        while (slash) { name_start = slash + 1; slash = kstrchr(slash + 1, '/'); }
    }
    char child_name[MINIFS_MAX_FILENAME + 1];
    kstrncpy(child_name, name_start, MINIFS_MAX_FILENAME);
    child_name[MINIFS_MAX_FILENAME] = 0;
    int parent_ino;
    if (name_start > parent_buf) {
        parent_buf[name_start - parent_buf - 1] = 0;
        parent_ino = minifs_resolve_path(parent_buf);
    } else {
        parent_ino = MINIFS_ROOT_INODE;
    }
    if (parent_ino >= 0)
        minifs_dir_remove_entry(parent_ino, child_name);
    return 0;
}

int minifs_read(int inode_num, void *buf, unsigned int offset, unsigned int len) {
    MiniFSInode inode;
    unsigned char *dst = (unsigned char *)buf;
    if (fs_read_inode((unsigned int)inode_num, &inode) < 0) return -1;

    /* If file is compressed, read compressed data, decompress, then extract */
    if (inode.flags & MINIFS_INODE_COMPRESSED) {
        unsigned int clen = inode.size;
        unsigned char *cbuf = (unsigned char *)kmalloc(clen);
        if (!cbuf) return -1;
        unsigned int done = 0;
        while (done < clen) {
            unsigned int logblk = done / MINIFS_BLOCK_SIZE;
            unsigned int blkoff = done % MINIFS_BLOCK_SIZE;
            unsigned int toread = clen - done;
            if (toread > MINIFS_BLOCK_SIZE - blkoff) toread = MINIFS_BLOCK_SIZE - blkoff;
            unsigned int phys;
            if (minifs_inode_get_block(&inode, logblk, &phys) < 0 || phys == 0) {
                kmemset(cbuf + done, 0, toread);
                done += toread;
                continue;
            }
            unsigned char blkbuf[MINIFS_BLOCK_SIZE];
            if (block_read(phys, blkbuf) < 0) { kfree(cbuf); return -1; }
            kmemcpy(cbuf + done, blkbuf + blkoff, toread);
            done += toread;
        }
        /* Decompress */
        unsigned int osize = *(unsigned int *)cbuf;
        if (osize == 0 || osize > MINIFS_BLOCK_SIZE * 1024) { kfree(cbuf); return -1; }
        unsigned char *obuf = (unsigned char *)kmalloc(osize);
        if (!obuf) { kfree(cbuf); return -1; }
        unsigned int dsize = minifs_decompress(cbuf, clen, obuf, osize);
        kfree(cbuf);
        if (dsize == 0) return -1;
        if (offset >= dsize) { kfree(obuf); return 0; }
        if (offset + len > dsize) len = dsize - offset;
        kmemcpy(dst, obuf + offset, len);
        kfree(obuf);
        return (int)len;
    }

    if (offset >= inode.size) return 0;
    if (offset + len > inode.size) len = inode.size - offset;
    unsigned int done = 0;
    while (done < len) {
        unsigned int logblk = (offset + done) / MINIFS_BLOCK_SIZE;
        unsigned int blkoff = (offset + done) % MINIFS_BLOCK_SIZE;
        unsigned int toread = len - done;
        if (toread > MINIFS_BLOCK_SIZE - blkoff) toread = MINIFS_BLOCK_SIZE - blkoff;
        unsigned int phys;
        if (minifs_inode_get_block(&inode, logblk, &phys) < 0 || phys == 0) {
            kmemset(dst + done, 0, toread);
            done += toread;
            continue;
        }
        unsigned char blkbuf[MINIFS_BLOCK_SIZE];
        if (block_read(phys, blkbuf) < 0) return -1;
        kmemcpy(dst + done, blkbuf + blkoff, toread);
        done += toread;
    }
    return (int)done;
}

int minifs_write(int inode_num, const void *buf, unsigned int offset,
                 unsigned int len) {
    MiniFSInode inode;
    const unsigned char *src = (const unsigned char *)buf;
    if (fs_read_inode((unsigned int)inode_num, &inode) < 0) return -1;
    unsigned int done = 0;
    while (done < len) {
        unsigned int logblk = (offset + done) / MINIFS_BLOCK_SIZE;
        unsigned int blkoff = (offset + done) % MINIFS_BLOCK_SIZE;
        unsigned int towrite = len - done;
        if (towrite > MINIFS_BLOCK_SIZE - blkoff) towrite = MINIFS_BLOCK_SIZE - blkoff;
        unsigned int phys;
        if (minifs_inode_get_block(&inode, logblk, &phys) < 0 || phys == 0) {
            if (minifs_inode_alloc_block(&inode, logblk) < 0) return -1;
            if (minifs_inode_get_block(&inode, logblk, &phys) < 0) return -1;
            if (fs_read_inode((unsigned int)inode_num, &inode) < 0) return -1;
        }
        if (blkoff > 0 || towrite < MINIFS_BLOCK_SIZE) {
            unsigned char blkbuf[MINIFS_BLOCK_SIZE];
            if (block_read(phys, blkbuf) < 0) return -1;
            kmemcpy(blkbuf + blkoff, src + done, towrite);
            if (block_write(phys, blkbuf) < 0) return -1;
        } else {
            unsigned char blkbuf[MINIFS_BLOCK_SIZE];
            kmemcpy(blkbuf, src + done, MINIFS_BLOCK_SIZE);
            if (block_write(phys, blkbuf) < 0) return -1;
        }
        done += towrite;
    }
    if (offset + len > inode.size) {
        inode.size = offset + len;
    }
    inode.mtime = 0;
    inode.checksum = minifs_crc32(&inode, sizeof(MiniFSInode) - 4);
    fs_write_inode((unsigned int)inode_num, &inode);
    return (int)done;
}

/* Write a whole file, optionally compressing with LZ4.
 * Returns the number of bytes written (compressed size), or -1 on error. */
int minifs_write_compressed(int inode_num, const void *buf, unsigned int len) {
    MiniFSInode inode;
    if (fs_read_inode((unsigned int)inode_num, &inode) < 0) return -1;

    /* Truncate first */
    minifs_truncate((unsigned int)inode_num, 0);
    if (fs_read_inode((unsigned int)inode_num, &inode) < 0) return -1;

    /* Try compression for files > 64 bytes */
    if (len > 64) {
        unsigned int cap = len + (len / 255) + 16 + 4;
        unsigned char *cbuf = (unsigned char *)kmalloc(cap);
        if (cbuf) {
            unsigned int clen = minifs_compress(buf, len, cbuf, cap);
            if (clen > 0 && clen < len) {
                inode.flags |= MINIFS_INODE_COMPRESSED;
                fs_write_inode((unsigned int)inode_num, &inode);
                int ret = minifs_write(inode_num, cbuf, 0, clen);
                kfree(cbuf);
                if (ret < 0) return -1;
                if (fs_read_inode((unsigned int)inode_num, &inode) < 0) return -1;
                inode.size = clen;
                inode.checksum = minifs_crc32(&inode, sizeof(MiniFSInode) - 4);
                fs_write_inode((unsigned int)inode_num, &inode);
                return (int)clen;
            }
            kfree(cbuf);
        }
    }

    /* Uncompressed path */
    inode.flags &= ~MINIFS_INODE_COMPRESSED;
    fs_write_inode((unsigned int)inode_num, &inode);
    return minifs_write(inode_num, buf, 0, len);
}

int minifs_truncate(int inode_num, unsigned int new_size) {
    MiniFSInode inode;
    if (fs_read_inode((unsigned int)inode_num, &inode) < 0) return -1;
    unsigned int old_blocks = (inode.size + MINIFS_BLOCK_SIZE - 1) / MINIFS_BLOCK_SIZE;
    unsigned int new_blocks = (new_size + MINIFS_BLOCK_SIZE - 1) / MINIFS_BLOCK_SIZE;
    unsigned int i;
    if (new_size < inode.size) {
        for (i = new_blocks; i < old_blocks && i < 10; i++) {
            if (inode.direct[i]) { minifs_free_block(inode.direct[i]); inode.direct[i] = 0; }
        }
    }
    inode.size = new_size;
    inode.checksum = minifs_crc32(&inode, sizeof(MiniFSInode) - 4);
    return fs_write_inode((unsigned int)inode_num, &inode);
}

int minifs_stat(int inode_num, MiniFSInode *out) {
    return fs_read_inode((unsigned int)inode_num, out);
}

int minifs_access(const char *path) {
    return minifs_resolve_path(path) >= 0 ? 0 : -1;
}

/* ---- Init / mount / mkfs ---- */

void minifs_init(void) {
    fs_mounted = 0;
    fs_ibitmap = 0;
    fs_bbitmap = 0;
    fs_lba_start = 0;
    fs_next_txn = 1;
}

unsigned int minifs_get_lba_start(void) { return fs_lba_start; }
int minifs_is_mounted(void) { return fs_mounted; }

int minifs_mount(void) {
    unsigned int total_sectors = ide_total_sectors();
    unsigned int fs_lba_raw;
    unsigned int ibm_blocks, bbm_blocks;
    unsigned int i;

    if (total_sectors == 0) return -1;

#ifdef KERNEL_SECTORS
    fs_lba_raw = 9 + KERNEL_SECTORS;
#else
    fs_lba_raw = 9;
    {   unsigned int ksize = (unsigned int)(&ramdisk_end[0] - &ramdisk_start[0]);
        if (ksize == 0) ksize = 1;
        fs_lba_raw += (ksize + IDE_SECTOR_SIZE - 1) / IDE_SECTOR_SIZE;
    }
#endif

    fs_lba_start = (fs_lba_raw + 2047) & ~2047u;

    unsigned int fs_sectors = total_sectors - fs_lba_start;
    if (fs_sectors < SECTORS_PER_BLOCK * 4) {
        kprintf("minifs: not enough space after kernel (%u sectors, start=%u)\n",
                fs_sectors, fs_lba_start);
        return -1;
    }

    kprintf("minifs: looking for superblock at LBA %u\n", fs_lba_start);
    block_set_base(fs_lba_start);
    if (block_read(0, (void *)&fs_sb) < 0) return -1;
    if (fs_sb.magic != MINIFS_MAGIC) {
        kprintf("minifs: no valid filesystem, run mkfs first\n");
        return -1;
    }

    ibm_blocks = div_round_up(fs_sb.total_inodes, MINIFS_BLOCK_SIZE * 8);
    bbm_blocks = div_round_up(fs_sb.total_blocks, MINIFS_BLOCK_SIZE * 8);

    /* Defensive: clamp bbm_blocks so the bitmap does not overflow into the
     * inode table.  A mismatch between mkfs and the kernel (e.g. mkfs wrote
     * 1 bitmap block but the kernel calculates 2 for 65536 blocks) would
     * otherwise let minifs_sync overwrite inode table data. */
    if (fs_sb.inode_table_start > fs_sb.block_bitmap_start &&
        bbm_blocks > fs_sb.inode_table_start - fs_sb.block_bitmap_start) {
        kprintf("minifs: bbm_blocks %u overflows inode table, clamping to %u\n",
                bbm_blocks, fs_sb.inode_table_start - fs_sb.block_bitmap_start);
        bbm_blocks = fs_sb.inode_table_start - fs_sb.block_bitmap_start;
    }

    fs_ibitmap = (unsigned char *)kmalloc(ibm_blocks * MINIFS_BLOCK_SIZE);
    fs_bbitmap = (unsigned char *)kmalloc(bbm_blocks * MINIFS_BLOCK_SIZE);
    if (!fs_ibitmap || !fs_bbitmap) return -1;

    for (i = 0; i < ibm_blocks; i++)
        block_read(fs_sb.inode_bitmap_start + i,
                   fs_ibitmap + i * MINIFS_BLOCK_SIZE);
    for (i = 0; i < bbm_blocks; i++)
        block_read(fs_sb.block_bitmap_start + i,
                   fs_bbitmap + i * MINIFS_BLOCK_SIZE);

    fs_mounted = 1;

    /* Set up journal area at the end of the filesystem */
    journal_start = fs_sb.total_blocks - MINIFS_JOURNAL_BLOCKS;
    journal_blocks = MINIFS_JOURNAL_BLOCKS;
    journal_load_super();
    minifs_journal_recover();

    kprintf("minifs: mounted, %u/%u blocks free, %u/%u inodes free\n",
            fs_sb.free_blocks, fs_sb.total_blocks,
            fs_sb.free_inodes, fs_sb.total_inodes);
    return 0;
}

int minifs_mkfs(unsigned int total_blocks) {
    unsigned int ibm_blocks, bbm_blocks, it_blocks, data_start;
    unsigned int i;
    unsigned char buf[MINIFS_BLOCK_SIZE];

    if (total_blocks < 16) return -1;

    ibm_blocks = 1;
    bbm_blocks = div_round_up(total_blocks, MINIFS_BLOCK_SIZE * 8);
    it_blocks = 8;
    data_start = 1 + ibm_blocks + bbm_blocks + it_blocks;

    kmemset(&fs_sb, 0, sizeof(MiniFSSuper));
    fs_sb.magic = MINIFS_MAGIC;
    fs_sb.version = MINIFS_VERSION;
    fs_sb.block_size = MINIFS_BLOCK_SIZE;
    fs_sb.total_blocks = total_blocks;
    fs_sb.free_blocks = total_blocks - data_start;
    fs_sb.total_inodes = it_blocks * MINIFS_INODES_PER_BLOCK;
    fs_sb.free_inodes = fs_sb.total_inodes - MINIFS_ROOT_INODE;
    fs_sb.root_inode = MINIFS_ROOT_INODE;
    fs_sb.inode_bitmap_start = 1;
    fs_sb.block_bitmap_start = 1 + ibm_blocks;
    fs_sb.inode_table_start = 1 + ibm_blocks + bbm_blocks;
    fs_sb.data_start = data_start;
    fs_sb.first_free_hint = data_start;
    fs_sb.compression = 0;
    fs_sb.dirty = 0;

    kmemset(buf, 0, MINIFS_BLOCK_SIZE);
    if (block_write(0, buf) < 0) return -1;

    kmemset(buf, 0xFF, MINIFS_BLOCK_SIZE);
    for (i = 0; i < data_start / 8 + 1 && i < MINIFS_BLOCK_SIZE; i++)
        buf[i] = 0xFF;
    unsigned int reserved_bits = data_start;
    for (i = 0; i < reserved_bits; i++)
        buf[i / 8] &= (unsigned char)~(1u << (i % 8));
    for (i = 0; i < ibm_blocks; i++)
        block_write(fs_sb.inode_bitmap_start + i, buf);
    for (i = 0; i < bbm_blocks; i++)
        block_write(fs_sb.block_bitmap_start + i, buf);

    kmemset(buf, 0, MINIFS_BLOCK_SIZE);
    for (i = 0; i < it_blocks; i++)
        block_write(fs_sb.inode_table_start + i, buf);

    MiniFSInode root;
    kmemset(&root, 0, sizeof(MiniFSInode));
    root.mode = MINIFS_S_IFDIR | 0755;
    root.link_count = 2;
    root.checksum = minifs_crc32(&root, sizeof(MiniFSInode) - 4);
    fs_write_inode(MINIFS_ROOT_INODE, &root);

    fs_ibitmap = (unsigned char *)kmalloc(ibm_blocks * MINIFS_BLOCK_SIZE);
    fs_bbitmap = (unsigned char *)kmalloc(bbm_blocks * MINIFS_BLOCK_SIZE);
    if (!fs_ibitmap || !fs_bbitmap) return -1;
    for (i = 0; i < ibm_blocks; i++)
        block_read(fs_sb.inode_bitmap_start + i,
                   fs_ibitmap + i * MINIFS_BLOCK_SIZE);
    for (i = 0; i < bbm_blocks; i++)
        block_read(fs_sb.block_bitmap_start + i,
                   fs_bbitmap + i * MINIFS_BLOCK_SIZE);

    fs_write_super();
    fs_mounted = 1;
    kprintf("minifs: mkfs done, %u blocks (%u KB)\n",
            total_blocks, total_blocks * 4);
    return 0;
}

int minifs_sync(void) {
    if (!fs_mounted) return -1;
    unsigned int ibm_blocks = div_round_up(fs_sb.total_inodes, MINIFS_BLOCK_SIZE * 8);
    unsigned int bbm_blocks = div_round_up(fs_sb.total_blocks, MINIFS_BLOCK_SIZE * 8);
    unsigned int i;
    for (i = 0; i < ibm_blocks; i++)
        block_write(fs_sb.inode_bitmap_start + i,
                    fs_ibitmap + i * MINIFS_BLOCK_SIZE);
    for (i = 0; i < bbm_blocks; i++)
        block_write(fs_sb.block_bitmap_start + i,
                    fs_bbitmap + i * MINIFS_BLOCK_SIZE);
    fs_write_super();
    return 0;
}

MiniFSFile *minifs_file_open(int inode_num, int flags) {
    MiniFSInode inode;
    if (fs_read_inode((unsigned int)inode_num, &inode) < 0) return 0;
    MiniFSFile *f = (MiniFSFile *)kmalloc(sizeof(MiniFSFile));
    if (!f) return 0;
    f->inode_num = inode_num;
    f->pos = 0;
    f->flags = flags;
    f->inode_cache = (MiniFSInode *)kmalloc(sizeof(MiniFSInode));
    if (!f->inode_cache) { kfree(f); return 0; }
    kmemcpy(f->inode_cache, &inode, sizeof(MiniFSInode));
    return f;
}

int minifs_file_close(MiniFSFile *f) {
    if (!f) return 0;
    if (f->inode_cache) kfree(f->inode_cache);
    kfree(f);
    return 0;
}

unsigned int minifs_get_total_blocks(void) {
    return fs_sb.total_blocks;
}
