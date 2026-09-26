#include "kernel.h"
#include "minifs.h"
#include "ext4.h"
#include "fsimg.h"
#include "ide.h"

/* ================================================================
 *  ext4 -- read-only loopback/device driver (subset)
 * ================================================================
 * On-disk structures are parsed with explicit little-endian loads;
 * no packed structs, so alignment can never lie. Supported: 1K/2K/4K
 * blocks, 32 and 64 bit group descriptors, extent trees (bounded
 * depth), legacy direct plus singly-indirect blocks, linear
 * directories. Everything else (htree, symlinks, encrypted/inline
 * files, double/triple indirect, journal) refuses fail-closed.
 * ================================================================ */

#define EXT4_SUPER_OFF   1024
#define EXT4_MAGIC       0xEF53
#define EXT4_EXT_MAGIC   0xF30A
#define EXT4_S_IFMT      0170000
#define EXT4_S_IFREG     0100000
#define EXT4_S_IFDIR     0040000
#define EXT4_S_IFLNK     0120000
#define EXT4_EXTENTS_FL  0x00080000UL
#define EXT4_INDEX_FL    0x00001000UL
#define EXT4_ENCRYPT_FL  0x00800000UL
#define EXT4_INLINE_FL   0x10000000UL
#define EXT4_EXT_UNINIT  0x8000
#define EXT4_MBR_LINUX   0x83

static unsigned ext_ld16(const unsigned char *p) {
    return (unsigned)p[0] | ((unsigned)p[1] << 8);
}

static unsigned long ext_ld32(const unsigned char *p) {
    return (unsigned long)p[0] | ((unsigned long)p[1] << 8) |
        ((unsigned long)p[2] << 16) | ((unsigned long)p[3] << 24);
}

/* Filesystem geometry from the superblock. 64-bit block counts ride
 * along (real disks use them) but every byte offset is fenced to
 * the image size before use. */
typedef struct {
    unsigned bs;
    unsigned inodes_per_group;
    unsigned blocks_per_group;
    unsigned long ngroups;
    unsigned inode_size;
    int is_64bit;
    unsigned desc_size;
    unsigned long desc_off;
} ext_geo_t;

static int ext_parse_sb(const fsimg_t *img, ext_geo_t *g) {
    unsigned char sb[1024];
    unsigned log_bs;
    unsigned long blocks_count;
    if (fsimg_read(img, EXT4_SUPER_OFF, sb, sizeof(sb)) < 0) return -1;
    if (ext_ld16(sb + 56) != EXT4_MAGIC) return -1;
    log_bs = ext_ld32(sb + 24);
    if (log_bs > 2) return -1;
    g->bs = 1024U << log_bs;
    g->blocks_per_group = (unsigned)ext_ld32(sb + 32);
    g->inodes_per_group = (unsigned)ext_ld32(sb + 40);
    if (g->blocks_per_group == 0 || g->inodes_per_group == 0) return -1;
    if (g->blocks_per_group > g->bs * 8) return -1;
    blocks_count = ext_ld32(sb + 4);
    if (ext_ld32(sb + 96) & 0x80) {
        unsigned char hi[4];
        if (fsimg_read(img, EXT4_SUPER_OFF + 336, hi, 4) < 0) return -1;
        blocks_count |= ext_ld32(hi) << 32;
    }
    if (blocks_count == 0) return -1;
    g->ngroups = (blocks_count + g->blocks_per_group - 1) /
        g->blocks_per_group;
    if (g->ngroups == 0 || g->ngroups > 1000000UL) return -1;
    g->inode_size = (unsigned)ext_ld16(sb + 88);
    if (g->inode_size < 128 || g->inode_size > g->bs) return -1;
    g->is_64bit = (ext_ld32(sb + 96) & 0x80) ? 1 : 0;
    g->desc_size = g->is_64bit ? 64 : 32;
    /* Descriptor table follows the superblock: block 2 on 1K
     * filesystems (the superblock occupies block 1), block 1 above
     * (superblock in block 0). */
    g->desc_off = (unsigned long)((log_bs == 0) ? 2 : 1) * g->bs;
    if (g->desc_off + g->desc_size > img->size) return -1;
    return 0;
}

/* Byte offset of an inode. Group and index arithmetic is 64-bit and
 * fenced to the image before any read. */
static int ext_inode_off(const fsimg_t *img, const ext_geo_t *g,
                         unsigned ino, unsigned long *off_out) {
    unsigned char desc[64];
    unsigned long grp, idx, tab, off;
    unsigned long doff;
    if (ino < 1) return -1;
    grp = ((unsigned long)ino - 1) / g->inodes_per_group;
    idx = ((unsigned long)ino - 1) % g->inodes_per_group;
    if (grp >= g->ngroups) return -1;
    doff = g->desc_off + grp * g->desc_size;
    if (doff + g->desc_size > img->size) return -1;
    if (fsimg_read(img, doff, desc, g->desc_size) < 0) return -1;
    tab = ext_ld32(desc + 8);
    if (g->is_64bit) tab |= ext_ld32(desc + 40) << 32;
    off = tab * g->bs + idx * g->inode_size;
    if (off + g->inode_size < off) return -1;
    if (off + g->inode_size > img->size) return -1;
    *off_out = off;
    return 0;
}

/* Decoded inode: kind (0 file, 1 dir), size, extent root or legacy
 * block list (copied, so later reads never re-parse the inode). */
typedef struct {
    int isdir;
    unsigned long size;
    int use_extents;
    unsigned char iblock[60];
} ext_ino_t;

static int ext_read_inode(const fsimg_t *img, const ext_geo_t *g,
                          unsigned ino, ext_ino_t *out) {
    unsigned char *ib = 0;
    unsigned long off;
    unsigned mode, flags;
    unsigned long sz;
    unsigned i;
    if (ext_inode_off(img, g, ino, &off) < 0) return -1;
    ib = (unsigned char *)kmalloc(g->inode_size);
    if (!ib) return -1;
    if (fsimg_read(img, off, ib, g->inode_size) < 0) {
        kfree(ib);
        return -1;
    }
    mode = ext_ld16(ib + 0);
    if ((mode & EXT4_S_IFMT) != EXT4_S_IFREG &&
        (mode & EXT4_S_IFMT) != EXT4_S_IFDIR) {
        kfree(ib);
        return -1;
    }
    out->isdir = ((mode & EXT4_S_IFMT) == EXT4_S_IFDIR) ? 1 : 0;
    sz = ext_ld32(ib + 4) | (ext_ld32(ib + 108) << 32);
    out->size = sz;
    flags = (unsigned)ext_ld32(ib + 32);
    if (flags & EXT4_INDEX_FL) {
        kfree(ib);
        return -1;
    }
    if (flags & (EXT4_ENCRYPT_FL | EXT4_INLINE_FL)) {
        kfree(ib);
        return -1;
    }
    out->use_extents = (flags & EXT4_EXTENTS_FL) ? 1 : 0;
    for (i = 0; i < 60; i++) out->iblock[i] = ib[40 + i];
    kfree(ib);
    return 0;
}

/* Map one logical file block to a physical disk block. Returns 1
 * with *phys_out set, 0 for a hole/uninitialized range (caller
 * zeroes), -1 on any structural fault. Extent index depth is
 * capped; each level is bounds-checked to the image. */
static int ext_map_leaf(const fsimg_t *img, const ext_geo_t *g,
                        const unsigned char *root, unsigned nent,
                        unsigned long lblk, unsigned long *phys_out,
                        int *zero_out);
static int ext_map_down(const fsimg_t *img, const ext_geo_t *g,
                        const unsigned char *root, unsigned nent,
                        unsigned long lblk, unsigned char *node);
static int ext_map(const fsimg_t *img, const ext_geo_t *g,
                   const unsigned char *iblock, unsigned long lblk,
                   unsigned long *phys_out, int *zero_out) {
    unsigned char *node = 0;
    int r = -1;
    node = (unsigned char *)kmalloc(g->bs);
    if (!node) return -1;
    /* First level lives in the inode itself (60 bytes); deeper
     * levels are read from disk blocks, at most 5 down. */
    {
        unsigned char root[60];
        unsigned d;
        for (d = 0; d < 60; d++) root[d] = iblock[d];
        for (d = 0; d < 5; d++) {
            unsigned magic = (unsigned)root[0] | ((unsigned)root[1] << 8);
            unsigned nent;
            if (magic != EXT4_EXT_MAGIC) break;
            nent = (unsigned)root[2] | ((unsigned)root[3] << 8);
            {
                unsigned depth =
                    (unsigned)root[6] | ((unsigned)root[7] << 8);
                if (nent == 0 || nent > (g->bs - 12) / 12) break;
                if (depth == 0) {
                    r = ext_map_leaf(img, g, root, nent, lblk,
                                     phys_out, zero_out);
                    break;
                }
                r = ext_map_down(img, g, root, nent, lblk, node);
                if (r <= 0) break;
                for (d = 0; d < 60 && d < g->bs; d++) root[d] = node[d];
                r = -1;
                continue;
            }
        }
    }
    kfree(node);
    return r;
}

/* One leaf level: find the extent covering lblk. */
static int ext_map_leaf(const fsimg_t *img, const ext_geo_t *g,
                        const unsigned char *root, unsigned nent,
                        unsigned long lblk, unsigned long *phys_out,
                        int *zero_out) {
    unsigned j;
    for (j = 0; j < nent; j++) {
        const unsigned char *e = root + 12 + j * 12;
        unsigned long start =
            (unsigned long)(e[0] | (e[1] << 8) | (e[2] << 16) |
                            (e[3] << 24));
        unsigned raw = (unsigned)(e[4] | (e[5] << 8));
        unsigned long len = raw & 0x7FFFUL;
        int uninit = (raw & EXT4_EXT_UNINIT) ? 1 : 0;
        unsigned long phys =
            (unsigned long)(e[8] | (e[9] << 8) | (e[10] << 16) |
                            (e[11] << 24));
        unsigned hi = (unsigned)(e[6] | (e[7] << 8));
        if (len == 0) len = 32768UL;
        phys |= (unsigned long)hi << 32;
        if (lblk < start) break;
        if (lblk >= start + len) continue;
        if (phys > img->size / g->bs) return -1;
        if ((phys + (lblk - start)) * g->bs < phys * g->bs) return -1;
        if ((phys + (lblk - start) + 1) * g->bs > img->size)
            return -1;
        if (uninit) {
            *zero_out = 1;
            *phys_out = 0;
        } else {
            *zero_out = 0;
            *phys_out = phys + (lblk - start);
        }
        return 1;
    }
    return 0;
}

/* One index level: descend into the child covering lblk, loading it
 * over the caller's level buffer. Returns 1 loaded, 0 when no entry
 * covers lblk (hole), -1 on structural fault. */
static int ext_map_down(const fsimg_t *img, const ext_geo_t *g,
                        const unsigned char *root, unsigned nent,
                        unsigned long lblk, unsigned char *node) {
    unsigned j;
    unsigned long child = 0;
    int found = 0;
    for (j = 0; j < nent; j++) {
        const unsigned char *e = root + 12 + j * 12;
        unsigned long eb =
            (unsigned long)(e[0] | (e[1] << 8) | (e[2] << 16) |
                            (e[3] << 24));
        unsigned long leaf =
            (unsigned long)(e[4] | (e[5] << 8) | (e[6] << 16) |
                            (e[7] << 24));
        unsigned hi = (unsigned)(e[8] | (e[9] << 8));
        leaf |= (unsigned long)hi << 32;
        if (lblk >= eb) {
            child = leaf;
            found = 1;
        } else {
            break;
        }
    }
    if (!found) return 0;
    if (child > img->size / g->bs) return -1;
    if (fsimg_read(img, child * g->bs, node, g->bs) < 0) return -1;
    return 1;
}

/* Legacy direct blocks plus one singly-indirect level. Doubly and
 * triply indirect inodes refuse (v1 scope). Holes read as zeros. */
static int ext_map_legacy(const fsimg_t *img, const ext_geo_t *g,
                          const unsigned char *iblock,
                          unsigned long lblk, unsigned long *phys_out,
                          int *zero_out) {
    unsigned long direct[12];
    unsigned sind;
    unsigned i;
    for (i = 0; i < 12; i++)
        direct[i] =
            (unsigned long)(iblock[i * 4] | (iblock[i * 4 + 1] << 8) |
                            (iblock[i * 4 + 2] << 16) |
                            (iblock[i * 4 + 3] << 24));
    sind = (unsigned)(iblock[48] | (iblock[49] << 8) |
                      (iblock[50] << 16) | (iblock[51] << 24));
    if (iblock[52] | iblock[53] | iblock[54] | iblock[55] |
        iblock[56] | iblock[57] | iblock[58] | iblock[59])
        return -1;
    if (lblk < 12) {
        if (direct[lblk] == 0) {
            *zero_out = 1;
            *phys_out = 0;
            return 1;
        }
        if (direct[lblk] > img->size / g->bs) return -1;
        *zero_out = 0;
        *phys_out = direct[lblk];
        return 1;
    }
    if (sind == 0) {
        *zero_out = 1;
        *phys_out = 0;
        return 1;
    }
    {
        unsigned char *blk = (unsigned char *)kmalloc(g->bs);
        unsigned long per = g->bs / 4;
        unsigned long p;
        if (!blk) return -1;
        if (lblk - 12 >= per) {
            kfree(blk);
            return -1;
        }
        if (sind > img->size / g->bs) {
            kfree(blk);
            return -1;
        }
        if (fsimg_read(img, (unsigned long)sind * g->bs, blk, g->bs) <
            0) {
            kfree(blk);
            return -1;
        }
        p = (unsigned long)(blk[(lblk - 12) * 4] |
                            (blk[(lblk - 12) * 4 + 1] << 8) |
                            (blk[(lblk - 12) * 4 + 2] << 16) |
                            (blk[(lblk - 12) * 4 + 3] << 24));
        kfree(blk);
        if (p == 0) {
            *zero_out = 1;
            *phys_out = 0;
            return 1;
        }
        if (p > img->size / g->bs) return -1;
        *zero_out = 0;
        *phys_out = p;
        return 1;
    }
}

/* Resolve an ext4 path to its inode number, size and kind. Iterative
 * over '/'-separated words, depth-capped; dot entries navigate in
 * listings only ('.' skipped, '..' refused). "" or "/" is root (2). */
static int ext_file_block(const fsimg_t *img, const ext_geo_t *g,
                          const ext_ino_t *st, unsigned long lblk,
                          unsigned char *blk, unsigned long want);
static int ext_resolve(const fsimg_t *img, const ext_geo_t *g,
                       const char *path, unsigned *ino_out,
                       unsigned long *size_out, int *isdir_out) {
    const char *p = path;
    unsigned cur = 2;
    int depth = 0;
    while (*p == '/') p++;
    if (*p == 0) {
        ext_ino_t st;
        if (ext_read_inode(img, g, cur, &st) < 0 || !st.isdir)
            return -1;
        if (ino_out) *ino_out = cur;
        if (size_out) *size_out = 0;
        if (isdir_out) *isdir_out = 1;
        return 0;
    }
    while (*p) {
        const char *start = p;
        unsigned long qlen;
        ext_ino_t st;
        unsigned char *blk = 0;
        unsigned long off = 0;
        int found = 0;
        while (*p && *p != '/') p++;
        qlen = (unsigned long)(p - start);
        if (qlen == 0 || qlen > EXT4_NAME_MAX) return -1;
        if (qlen == 1 && start[0] == '.') goto next_word;
        if (qlen == 2 && start[0] == '.' && start[1] == '.') return -1;
        if (++depth > EXT4_MAX_DEPTH) return -1;
        if (ext_read_inode(img, g, cur, &st) < 0 || !st.isdir)
            return -1;
        blk = (unsigned char *)kmalloc(g->bs);
        if (!blk) return -1;
        while (off < st.size) {
            unsigned long boff = off % g->bs;
            unsigned long left = g->bs - boff;
            unsigned long k = 0;
            if (ext_file_block(img, g, &st, off / g->bs, blk, left) <
                0)
                break;
            while (k + 8 <= left) {
                unsigned ino_e =
                    (unsigned)(blk[k] | (blk[k + 1] << 8) |
                               (blk[k + 2] << 16) | (blk[k + 3] << 24));
                unsigned rec =
                    (unsigned)(blk[k + 4] | (blk[k + 5] << 8));
                unsigned nl = blk[k + 6];
                if (rec < 8 || k + rec > left) break;
                if (nl > 0 && k + 8 + nl <= left && ino_e != 0 &&
                    nl == qlen) {
                    unsigned q;
                    for (q = 0; q < nl; q++)
                        if (blk[k + 8 + q] != (unsigned char)start[q])
                            break;
                    if (q == nl) {
                        ext_ino_t cst;
                        if (ext_read_inode(img, g, ino_e, &cst) < 0) {
                            kfree(blk);
                            return -1;
                        }
                        if (!*p && !cst.isdir) {
                            if (ino_out) *ino_out = ino_e;
                            if (size_out) *size_out = cst.size;
                            if (isdir_out) *isdir_out = 0;
                            kfree(blk);
                            return 0;
                        }
                        if (!*p && cst.isdir) {
                            if (ino_out) *ino_out = ino_e;
                            if (size_out) *size_out = 0;
                            if (isdir_out) *isdir_out = 1;
                            kfree(blk);
                            return 0;
                        }
                        if (*p && !cst.isdir) {
                            kfree(blk);
                            return -1;
                        }
                        cur = ino_e;
                        found = 1;
                        break;
                    }
                }
                if (rec == 0) break;
                k += rec;
            }
            if (found) break;
            off += left;
        }
        kfree(blk);
        if (!found) return -1;
next_word:
        while (*p == '/') p++;
        if (*p == 0) {
            ext_ino_t cst;
            if (ext_read_inode(img, g, cur, &cst) < 0 || !cst.isdir)
                return -1;
            if (ino_out) *ino_out = cur;
            if (size_out) *size_out = 0;
            if (isdir_out) *isdir_out = 1;
            return 0;
        }
    }
    return -1;
}

/* Read one logical file block of an open inode into blk (block
 * sized). Holes and uninitialized extents come back zeroed. */
static int ext_file_block(const fsimg_t *img, const ext_geo_t *g,
                          const ext_ino_t *st, unsigned long lblk,
                          unsigned char *blk, unsigned long want) {
    unsigned long phys = 0;
    int zero = 0;
    int r;
    if (want > g->bs) return -1;
    if (st->use_extents)
        r = ext_map(img, g, st->iblock, lblk, &phys, &zero);
    else
        r = ext_map_legacy(img, g, st->iblock, lblk, &phys, &zero);
    if (r < 0) return -1;
    if (r == 0 || zero) {
        unsigned long k;
        for (k = 0; k < want; k++) blk[k] = 0;
        return 0;
    }
    if (phys > img->size / g->bs) return -1;
    return fsimg_read(img, phys * g->bs, blk, want);
}

int ext4_list(const char *imgpath, const char *dirpath,
              char names[][EXT4_NAME_MAX + 1], int *isdir, int cap) {
    char resolved[RAMDISK_FNAME_LEN];
    fsimg_t img;
    ext_geo_t g;
    unsigned char *blk = 0;
    unsigned dino = 0;
    ext_ino_t st;
    unsigned long off = 0;
    int n = 0;
    if (!imgpath || !dirpath || !names || cap <= 0) return -1;
    if (!fs_resolve(imgpath, resolved, sizeof(resolved))) return -1;
    if (fsimg_open_file(resolved, &img) < 0) {
        if (kstrcmp(resolved, "hd0") != 0) return -1;
        {
            long base = ext_dev_base();
            unsigned long total;
            if (base < 0 || !ide_present()) return -1;
            total = (unsigned long)ide_total_sectors();
            if (fsimg_open_dev((unsigned long)base,
                               total - (unsigned long)base, &img) < 0)
                return -1;
        }
    }
    if (ext_parse_sb(&img, &g) < 0) return -1;
    {
        int isd = 0;
        if (ext_resolve(&img, &g, dirpath, &dino, 0, &isd) < 0 || !isd)
            return -1;
    }
    if (ext_read_inode(&img, &g, dino, &st) < 0 || !st.isdir)
        return -1;
    blk = (unsigned char *)kmalloc(g.bs);
    if (!blk) return -1;
    while (off < st.size && n < cap) {
        unsigned long boff = off % g.bs;
        unsigned long left = g.bs - boff;
        unsigned long k = 0;
        if (ext_file_block(&img, &g, &st, off / g.bs, blk, left) <
            0)
            break;
        while (k + 8 <= left && n < cap) {
            unsigned ino_e =
                (unsigned)(blk[k] | (blk[k + 1] << 8) |
                           (blk[k + 2] << 16) | (blk[k + 3] << 24));
            unsigned rec = (unsigned)(blk[k + 4] | (blk[k + 5] << 8));
            unsigned nl = blk[k + 6];
            unsigned i;
            if (rec < 8 || k + rec > left) break;
            if (ino_e != 0 && nl > 0 && nl <= EXT4_NAME_MAX &&
                k + 8 + nl <= left) {
                if (!((nl == 1 && blk[k + 8] == '.') ||
                      (nl == 2 && blk[k + 8] == '.' &&
                       blk[k + 9] == '.'))) {
                    /* Kind comes from the dirent type byte, not a
                     * stat: htree directories refuse stat (their
                     * entries are not linear), but they still list.
                     * Unknown type falls back to stat. */
                    unsigned ft = blk[k + 7];
                    ext_ino_t est;
                    int di = 0;
                    for (i = 0; i < nl; i++)
                        names[n][i] = (char)blk[k + 8 + i];
                    names[n][nl] = 0;
                    if (ft == 2) {
                        di = 1;
                    } else if (ft != 1 && ft != 7) {
                        if (ext_read_inode(&img, &g, ino_e, &est) ==
                            0 &&
                            est.isdir)
                            di = 1;
                    }
                    if (di) {
                        if (nl + 1 >= EXT4_NAME_MAX + 1) {
                            k += rec;
                            continue;
                        }
                        names[n][nl++] = '/';
                        names[n][nl] = 0;
                    }
                    if (isdir) isdir[n] = di;
                    n++;
                }
            }
            if (rec == 0) break;
            k += rec;
        }
        off += left;
    }
    kfree(blk);
    return n;
}

/* Split "imgpath:extpath" (first ':' wins; image names never carry
 * one). ext paths run deeper than FAT, hence the wider right side. */
static int ext_split(const char *path, char *img, char *extp) {
    return fsimg_split(path, img, RAMDISK_FNAME_LEN, extp,
                       EXT4_PATH_MAX);
}

int ext4_vfs_open(const char *path, int mode, void **handle) {
    char img[RAMDISK_FNAME_LEN], extp[EXT4_PATH_MAX];
    char resolved[RAMDISK_FNAME_LEN];
    fsimg_t fimg;
    ext_geo_t g;
    ext4_handle_t *h = 0;
    unsigned ino = 0;
    unsigned long sz = 0;
    int isdir = 0;
    if (mode == 1 || mode == 2) return -1;
    if (ext_split(path, img, extp) < 0) return -1;
    if (!fs_resolve(img, resolved, sizeof(resolved))) return -1;
    if (fsimg_open_file(resolved, &fimg) < 0) {
        long base;
        unsigned long total;
        if (kstrcmp(resolved, "hd0") != 0) return -1;
        if (!ide_present()) return -1;
        base = ext_dev_base();
        if (base < 0) return -1;
        total = (unsigned long)ide_total_sectors();
        if (fsimg_open_dev((unsigned long)base,
                           total - (unsigned long)base, &fimg) < 0)
            return -1;
    }
    if (ext_parse_sb(&fimg, &g) < 0) return -1;
    if (ext_resolve(&fimg, &g, extp, &ino, &sz, &isdir) < 0 || isdir)
        return -1;
    h = (ext4_handle_t *)kmalloc(sizeof(ext4_handle_t));
    if (!h) return -1;
    h->ino_img = fimg.ino;
    h->rf = fimg.rf;
    h->is_dev = fimg.is_dev;
    h->dev_lba = fimg.dev_lba;
    h->img_size = fimg.size;
    h->bs = g.bs;
    h->ino = ino;
    h->file_size = sz;
    *handle = h;
    return 0;
}

int ext4_vfs_read(void *handle, void *buf, unsigned long pos,
                  unsigned long len) {
    ext4_handle_t *h = (ext4_handle_t *)handle;
    unsigned char *out = (unsigned char *)buf;
    fsimg_t img;
    ext_geo_t g;
    ext_ino_t st;
    unsigned char *blk = 0;
    unsigned long done = 0;
    if (!h || !out) return -1;
    if (pos >= h->file_size) return 0;
    if (len > h->file_size - pos) len = h->file_size - pos;
    if (len == 0) return 0;
    img.rf = h->rf;
    img.ino = h->ino_img;
    img.is_dev = h->is_dev;
    img.dev_lba = h->dev_lba;
    img.size = h->img_size;
    if (ext_parse_sb(&img, &g) < 0) return -1;
    if (ext_read_inode(&img, &g, h->ino, &st) < 0) return -1;
    blk = (unsigned char *)kmalloc(g.bs);
    if (!blk) return -1;
    while (done < len) {
        unsigned long lblk = (pos + done) / g.bs;
        unsigned long frag = (pos + done) % g.bs;
        unsigned long take = g.bs - frag;
        if (take > len - done) take = len - done;
        /* Whole block in, fragment out: ext_file_block maps
         * block-aligned ranges only. */
        if (ext_file_block(&img, &g, &st, lblk, blk, g.bs) < 0) {
            kfree(blk);
            return -1;
        }
        kmemcpy(out + done, blk + frag, take);
        done += take;
    }
    kfree(blk);
    return (int)done;
}

int ext4_vfs_write(void *handle, const void *buf, unsigned long pos,
                   unsigned long len) {
    (void)handle;
    (void)buf;
    (void)pos;
    (void)len;
    return -1;
}

int ext4_vfs_close(void *handle) {
    if (handle) kfree(handle);
    return 0;
}

int ext4_vfs_fstat(void *handle, unsigned long *size_out) {
    ext4_handle_t *h = (ext4_handle_t *)handle;
    if (!h || !size_out) return -1;
    *size_out = h->file_size;
    return 0;
}

int ext4_vfs_truncate(void *handle, unsigned long size) {
    (void)handle;
    (void)size;
    return -1;
}

const vfs_ops_t ext4_vfs_ops = {
    .open     = ext4_vfs_open,
    .read     = ext4_vfs_read,
    .write    = ext4_vfs_write,
    .close    = ext4_vfs_close,
    .fstat    = ext4_vfs_fstat,
    .truncate = ext4_vfs_truncate,
};

/* First Linux-native partition: MBR 0x83 first (proven by a
 * superblock read), then a magic scan for superfloppy layouts.
 * Bounds and overflow discipline match the FAT prober. */
static int ext_mbr_entry(const unsigned char *mbr, int idx,
                         unsigned long total_sec,
                         unsigned long *base_out) {
    const unsigned char *e = mbr + 0x1BE + idx * 16;
    unsigned long start, count;
    fsimg_t probe;
    ext_geo_t g;
    if (e[4] != EXT4_MBR_LINUX) return -1;
    start = (unsigned long)e[8] | ((unsigned long)e[9] << 8) |
        ((unsigned long)e[10] << 16) | ((unsigned long)e[11] << 24);
    count = (unsigned long)e[12] | ((unsigned long)e[13] << 8) |
        ((unsigned long)e[14] << 16) | ((unsigned long)e[15] << 24);
    if (start == 0 || count == 0) return -1;
    if (start >= total_sec || count > total_sec - start) return -1;
    probe.rf = 0;
    probe.ino = -1;
    probe.is_dev = 1;
    probe.dev_lba = start;
    probe.size = count * 512UL;
    if (probe.size > 0xFFFFFFFFUL) return -1;
    if (ext_parse_sb(&probe, &g) < 0) return -1;
    *base_out = start;
    return 0;
}

static int ext_scan_dev(unsigned long total_sec,
                        unsigned long *base_out) {
    unsigned long lba;
    for (lba = 2048; lba < total_sec; lba += 2048) {
        fsimg_t probe;
        ext_geo_t g;
        probe.rf = 0;
        probe.ino = -1;
        probe.is_dev = 1;
        probe.dev_lba = lba;
        probe.size = (total_sec - lba) * 512UL;
        if (probe.size > 0xFFFFFFFFUL) probe.size = 0xFFFFFFFFUL;
        if (ext_parse_sb(&probe, &g) < 0) continue;
        *base_out = lba;
        return 0;
    }
    return -1;
}

static long ext_dev_cached = -1;

long ext_dev_base(void) {
    unsigned char mbr[512];
    unsigned long total;
    unsigned long base;
    int i;
    if (ext_dev_cached != -1) return ext_dev_cached;
    ext_dev_cached = -2;
    if (!ide_present()) return -2;
    total = (unsigned long)ide_total_sectors();
    if (total < 2048) return -2;
    if (ide_read_sectors(0, 1, mbr) < 0) return -2;
    if (mbr[510] == 0x55 && mbr[511] == 0xAA &&
        mbr[0x1BE + 4] != 0xEE) {
        for (i = 0; i < 4; i++) {
            if (ext_mbr_entry(mbr, i, total, &base) == 0) {
                ext_dev_cached = (long)base;
                return ext_dev_cached;
            }
        }
    }
    if (ext_scan_dev(total, &base) == 0) {
        ext_dev_cached = (long)base;
        return ext_dev_cached;
    }
    return -2;
}
