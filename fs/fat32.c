#include "kernel.h"
#include "minifs.h"
#include "fat32.h"
#include "fsimg.h"
#include "ide.h"

/* ================================================================
 *  FAT32 -- read-only loopback driver
 * ================================================================
 * On-disk structures are parsed with explicit little-endian loads;
 * no packed structs, so alignment can never lie. The loopback image
 * is an ordinary ramdisk/MiniFS file read through ramdisk_read/
 * minifs_read at absolute byte offsets, never mapped. Write paths
 * refuse: the driver owns no allocator for FAT updates and the
 * backing file is opened read-only.
 * ================================================================ */

static unsigned fat_ld16(const unsigned char *p) {
    return (unsigned)p[0] | ((unsigned)p[1] << 8);
}

static unsigned fat_ld32(const unsigned char *p) {
    return (unsigned)p[0] | ((unsigned)p[1] << 8) |
        ((unsigned)p[2] << 16) | ((unsigned)p[3] << 24);
}

/* Open by resolved path: files first (a real file named hd0 keeps
 * working), the hd0 disk device only as a fallback. */
static int fat_img_open(const char *resolved, fsimg_t *img) {
    long base;
    unsigned long total;
    if (fsimg_open_file(resolved, img) == 0) return 0;
    if (kstrcmp(resolved, "hd0") != 0) return -1;
    if (!ide_present()) return -1;
    base = fat_dev_base();
    if (base < 0) return -1;
    total = (unsigned long)ide_total_sectors();
    return fsimg_open_dev((unsigned long)base,
                          total - (unsigned long)base, img);
}

/* Parsed BPB plus derived geometry. secs = total data clusters + 2
 * (cluster numbers 0/1 are reserved), so a valid cluster is
 * 2 <= c < nclus + 2. */
typedef struct {
    unsigned byts_per_sec;
    unsigned sec_per_clus;
    unsigned rsvd_sec;
    unsigned num_fats;
    unsigned fatsz_sec;
    unsigned root_clus;
    unsigned long data_off;
    unsigned nclus;
} fat_geo_t;

static int fat_parse_bpb(const fsimg_t *img, fat_geo_t *g) {
    unsigned char bpb[512];
    unsigned tot16, tot32, fatsz16, data_sec;
    unsigned long fatsz_bytes, data_bytes;
    if (fsimg_read(img, 0, bpb, sizeof(bpb)) < 0) return -1;
    if (bpb[510] != 0x55 || bpb[511] != 0xAA) return -1;
    g->byts_per_sec = fat_ld16(bpb + 11);
    if (g->byts_per_sec != 512 && g->byts_per_sec != 1024 &&
        g->byts_per_sec != 2048 && g->byts_per_sec != 4096)
        return -1;
    g->sec_per_clus = bpb[13];
    if (g->sec_per_clus != 1 && g->sec_per_clus != 2 &&
        g->sec_per_clus != 4 && g->sec_per_clus != 8 &&
        g->sec_per_clus != 16 && g->sec_per_clus != 32 &&
        g->sec_per_clus != 64 && g->sec_per_clus != 128)
        return -1;
    if ((unsigned)g->sec_per_clus * g->byts_per_sec > FAT32_CLUS_MAX)
        return -1;
    g->rsvd_sec = fat_ld16(bpb + 14);
    if (g->rsvd_sec == 0) return -1;
    g->num_fats = bpb[16];
    if (g->num_fats == 0) return -1;
    tot16 = fat_ld16(bpb + 19);
    tot32 = fat_ld32(bpb + 32);
    if (tot16 != 0 || tot32 == 0) return -1;
    fatsz16 = fat_ld16(bpb + 22);
    g->fatsz_sec = fat_ld32(bpb + 36);
    if (fatsz16 != 0 || g->fatsz_sec == 0) return -1;
    g->root_clus = fat_ld32(bpb + 44);
    if (g->root_clus < 2) return -1;
    if (bpb[21] != 0xF0 && bpb[21] < 0xF8) return -1;
    fatsz_bytes = (unsigned long)g->num_fats * g->fatsz_sec *
        g->byts_per_sec;
    g->data_off = (unsigned long)g->rsvd_sec * g->byts_per_sec +
        fatsz_bytes;
    if (g->data_off >= img->size) return -1;
    data_bytes = img->size - g->data_off;
    data_sec = (unsigned)(data_bytes /
        ((unsigned long)g->sec_per_clus * g->byts_per_sec));
    g->nclus = data_sec;
    if (g->nclus < 65525) return -1;
    if (g->root_clus >= g->nclus + 2) return -1;
    return 0;
}

/* MBR partition entry offsets and the FAT32 type bytes, including
 * hidden variants real dual-boot setups carry. Extended types are
 * deliberately absent: v1 serves primaries, logical volumes wait
 * for an EBR follower. */
#define FAT_MBR_SIG_OFF   510
#define FAT_MBR_TAB_OFF   0x1BE
#define FAT_MBR_ENTRY_SZ  16
#define FAT_MBR_NENTRY    4
#define FAT_MBR_TYPE_OFF  4
#define FAT_MBR_START_OFF 8
#define FAT_MBR_COUNT_OFF 12
#define FAT_MBR_GPT_PROT  0xEE

static int fat_mbr_is_fat(unsigned char t) {
    return t == 0x0B || t == 0x0C || t == 0x1B || t == 0x1C;
}

/* Validate one MBR entry and, when it claims FAT32, prove it with a
 * BPB read at its start LBA (a type byte alone is a rumor: stage1
 * code bytes at 0x1BE on a table-less image decode as garbage
 * entries). Bounds are 64-bit and fenced to the drive size, so a
 * hostile table can neither wrap nor address past the disk. Real
 * hardware notes: CHS fields are ignored (LBA only, like every
 * modern loader), LBA48 is out of scope (LBA28 covers 137 GB), and
 * only the primary master is served. */
static int fat_mbr_entry(const unsigned char *mbr, int idx,
                         unsigned long total_sec, unsigned long *base_out) {
    const unsigned char *e = mbr + FAT_MBR_TAB_OFF + idx * FAT_MBR_ENTRY_SZ;
    unsigned long start, count;
    fsimg_t probe;
    fat_geo_t g;
    if (!fat_mbr_is_fat(e[FAT_MBR_TYPE_OFF])) return -1;
    start = (unsigned long)e[FAT_MBR_START_OFF] |
        ((unsigned long)e[FAT_MBR_START_OFF + 1] << 8) |
        ((unsigned long)e[FAT_MBR_START_OFF + 2] << 16) |
        ((unsigned long)e[FAT_MBR_START_OFF + 3] << 24);
    count = (unsigned long)e[FAT_MBR_COUNT_OFF] |
        ((unsigned long)e[FAT_MBR_COUNT_OFF + 1] << 8) |
        ((unsigned long)e[FAT_MBR_COUNT_OFF + 2] << 16) |
        ((unsigned long)e[FAT_MBR_COUNT_OFF + 3] << 24);
    if (start == 0 || count == 0) return -1;
    if (start >= total_sec || count > total_sec - start) return -1;
    probe.rf = 0;
    probe.ino = -1;
    probe.is_dev = 1;
    probe.dev_lba = start;
    probe.size = count * 512UL;
    if (probe.size > 0xFFFFFFFFUL) return -1;
    if (fat_parse_bpb(&probe, &g) < 0) return -1;
    *base_out = start;
    return 0;
}

/* First FAT32 partition on the disk: a real MBR entry first (real
 * hardware carries a table), then a magic scan over 2048-aligned
 * LBAs for superfloppy layouts with no table at all (the os.img
 * tail). The scan skips LBA 0 (boot sector) and fences every
 * candidate to the drive size. */
static int fat_scan_dev(unsigned long total_sec, unsigned long *base_out) {
    unsigned char sec[512];
    unsigned long lba;
    for (lba = 2048; lba < total_sec; lba += 2048) {
        fsimg_t probe;
        fat_geo_t g;
        if (ide_read_sectors((unsigned int)lba, 1, sec) < 0) return -1;
        if (sec[510] != 0x55 || sec[511] != 0xAA) continue;
        probe.rf = 0;
        probe.ino = -1;
        probe.is_dev = 1;
        probe.dev_lba = lba;
        probe.size = (total_sec - lba) * 512UL;
        if (probe.size > 0xFFFFFFFFUL) probe.size = 0xFFFFFFFFUL;
        if (fat_parse_bpb(&probe, &g) < 0) continue;
        *base_out = lba;
        return 0;
    }
    return -1;
}

static long fat_dev_cached = -1;

long fat_dev_base(void) {
    unsigned char mbr[512];
    unsigned long total;
    unsigned long base;
    int i;
    if (fat_dev_cached != -1) return fat_dev_cached;
    fat_dev_cached = -2;
    if (!ide_present()) return -2;
    total = (unsigned long)ide_total_sectors();
    if (total < 2048) return -2;
    if (ide_read_sectors(0, 1, mbr) < 0) return -2;
    if (mbr[FAT_MBR_SIG_OFF] == 0x55 && mbr[FAT_MBR_SIG_OFF + 1] == 0xAA &&
        mbr[FAT_MBR_TAB_OFF + FAT_MBR_TYPE_OFF] != FAT_MBR_GPT_PROT) {
        for (i = 0; i < FAT_MBR_NENTRY; i++) {
            if (fat_mbr_entry(mbr, i, total, &base) == 0) {
                fat_dev_cached = (long)base;
                return fat_dev_cached;
            }
        }
    }
    if (fat_scan_dev(total, &base) == 0) {
        fat_dev_cached = (long)base;
        return fat_dev_cached;
    }
    return -2;
}


static int fat_clus_ok(const fat_geo_t *g, unsigned c) {
    return c >= 2 && c < g->nclus + 2;
}

/* One FAT32 entry (low 28 bits). Reads the 512 B sector holding it;
 * the entry offset can never leave the image because the cluster is
 * range-checked first and the FAT region precedes data_off. */
static int fat_entry(const fsimg_t *img, const fat_geo_t *g,
                     unsigned clus, unsigned *out) {
    unsigned long ent_off;
    unsigned char sec[512];
    unsigned long sec_off;
    unsigned at;
    if (!fat_clus_ok(g, clus) || !out) return -1;
    ent_off = (unsigned long)g->rsvd_sec * g->byts_per_sec +
        (unsigned long)clus * 4;
    sec_off = ent_off & ~(unsigned long)511;
    at = (unsigned)(ent_off - sec_off);
    if (sec_off + 512 > img->size) return -1;
    if (fsimg_read(img, sec_off, sec, sizeof(sec)) < 0) return -1;
    *out = fat_ld32(sec + at) & 0x0FFFFFFFUL;
    return 0;
}

static int fat_eoc(unsigned v) {
    return v >= 0x0FFFFFF8UL;
}

/* Byte offset of a cluster's first byte. Overflow-safe: both factors
 * are validated small (cluster < 2^28, bytes/cluster <= 64 KB). */
static unsigned long fat_clus_off(const fat_geo_t *g, unsigned clus) {
    return g->data_off +
        ((unsigned long)clus - 2) * g->sec_per_clus * g->byts_per_sec;
}

/* FAT 8.3 forbids these in a query word (plus '/' and extra dots,
 * handled by the splitter). Lowercase folds to upper like the
 * on-disk short names mtools writes. */
static int fat_badch(char c) {
    const char *bad = "\"*+,/:;<=>?[\\]|";
    const char *b = bad;
    while (*b) {
        if (c == *b) return 1;
        b++;
    }
    return 0;
}

/* Uppercase one 8.3 query word ("name.ext", "name", never ".ext") into
 * padded 8+3 for raw comparison. Refuses overlong parts and paths. */
static int fat_qword(const char *q, unsigned qlen, char name8[8],
                     char ext3[3]) {
    unsigned i, dot = qlen, nl, xl;
    for (i = 0; i < 8; i++) name8[i] = ' ';
    for (i = 0; i < 3; i++) ext3[i] = ' ';
    if (qlen == 0 || qlen > 12) return -1;
    for (i = 0; i < qlen; i++) {
        if (q[i] == '.' && dot == qlen) { dot = i; continue; }
        if (q[i] == '.' && dot != qlen) return -1;
        if (fat_badch(q[i])) return -1;
    }
    nl = (dot == qlen) ? qlen : dot;
    xl = (dot == qlen) ? 0 : qlen - dot - 1;
    if (nl == 0 || nl > 8 || xl > 3) return -1;
    for (i = 0; i < nl; i++) {
        char c = q[i];
        if (c >= 'a' && c <= 'z') c -= 32;
        if ((unsigned char)c < 33 || (unsigned char)c > 126) return -1;
        name8[i] = c;
    }
    for (i = 0; i < xl; i++) {
        char c = q[dot + 1 + i];
        if (c >= 'a' && c <= 'z') c -= 32;
        if ((unsigned char)c < 33 || (unsigned char)c > 126) return -1;
        ext3[i] = c;
    }
    return 0;
}

/* Match one 32-byte directory entry against padded 8+3. Skips
 * end/deleted/LFN/volume entries; the caller checks the subdir bit. */
static int fat_match(const unsigned char *de, const char name8[8],
                     const char ext3[3]) {
    unsigned i;
    if (de[0] == 0x00 || de[0] == 0xE5) return 0;
    if (de[11] == 0x0F) return 0;
    if (de[11] & 0x08) return 0;
    for (i = 0; i < 8; i++)
        if (de[i] != (unsigned char)name8[i]) return 0;
    for (i = 0; i < 3; i++)
        if (de[8 + i] != (unsigned char)ext3[i]) return 0;
    return 1;
}

/* Resolve a FAT path to its first cluster, size and subdir bit.
 * Iterative over '/'-separated 8.3 words, depth-capped; '..' and
 * empty middles refuse. "" or "/" is the root directory itself. */
static int fat_resolve(const fsimg_t *img, const fat_geo_t *g,
                       const char *path, unsigned *clus_out,
                       unsigned long *size_out, int *isdir_out) {
    unsigned char *blk = 0;
    unsigned long clus_bytes;
    const char *p = path;
    unsigned cur = g->root_clus;
    int depth = 0;
    clus_bytes = (unsigned long)g->sec_per_clus * g->byts_per_sec;
    while (*p == '/') p++;
    if (*p == 0) {
        if (clus_out) *clus_out = cur;
        if (size_out) *size_out = 0;
        if (isdir_out) *isdir_out = 1;
        return 0;
    }
    blk = (unsigned char *)kmalloc(clus_bytes);
    if (!blk) return -1;
    while (*p) {
        const char *start = p;
        char name8[8], ext3[3];
        unsigned long qlen;
        int found = 0;
        unsigned c = cur;
        unsigned steps = 0;
        while (*p && *p != '/') p++;
        qlen = (unsigned long)(p - start);
        if (qlen == 0) { kfree(blk); return -1; }
        if (qlen == 1 && start[0] == '.') goto next_word;
        if ((qlen == 2 && start[0] == '.' && start[1] == '.') ||
            fat_qword(start, qlen, name8, ext3) < 0) {
            kfree(blk);
            return -1;
        }
        if (++depth > FAT32_MAX_DEPTH) { kfree(blk); return -1; }
        {
            int enddir = 0;
            while (fat_clus_ok(g, c) && !enddir) {
            unsigned long off = fat_clus_off(g, c);
            unsigned long k;
            unsigned v;
            if (off + clus_bytes > img->size) break;
            if (fsimg_read(img, off, blk, clus_bytes) < 0) break;
            for (k = 0; k < clus_bytes; k += 32) {
                unsigned nc;
                unsigned long ns;
                int nd;
                if (blk[k] == 0x00) { enddir = 1; break; }
                if (!fat_match(blk + k, name8, ext3)) continue;
                nd = (blk[k + 11] & 0x10) ? 1 : 0;
                nc = ((unsigned)blk[k + 20] << 16) | fat_ld16(blk + k + 26);
                ns = fat_ld32(blk + k + 28);
                if (!*p && !nd) {
                    if (clus_out) *clus_out = nc;
                    if (size_out) *size_out = ns;
                    if (isdir_out) *isdir_out = 0;
                    if (ns > 0 && !fat_clus_ok(g, nc)) {
                        kfree(blk);
                        return -1;
                    }
                    kfree(blk);
                    return 0;
                }
                if (!*p && nd) {
                    if (!fat_clus_ok(g, nc)) { kfree(blk); return -1; }
                    if (clus_out) *clus_out = nc;
                    if (size_out) *size_out = 0;
                    if (isdir_out) *isdir_out = 1;
                    kfree(blk);
                    return 0;
                }
                if (*p && !nd) { kfree(blk); return -1; }
                if (!fat_clus_ok(g, nc)) { kfree(blk); return -1; }
                cur = nc;
                found = 1;
                break;
            }
            if (found) break;
            if (enddir) break;
            if (fat_entry(img, g, c, &v) < 0) break;
            if (fat_eoc(v)) break;
            c = v;
            if (++steps > g->nclus) break;
        }
        }
        if (!found) { kfree(blk); return -1; }
next_word:
        while (*p == '/') p++;
        if (*p == 0) {
            if (clus_out) *clus_out = cur;
            if (size_out) *size_out = 0;
            if (isdir_out) *isdir_out = 1;
            kfree(blk);
            return 0;
        }
    }
    kfree(blk);
    return -1;
}

int fat32_list(const char *imgpath, const char *dirpath,
               char names[][FAT32_NAME_MAX], int *isdir, int cap) {
    char resolved[RAMDISK_FNAME_LEN];
    fsimg_t img;
    fat_geo_t g;
    unsigned char *blk = 0;
    unsigned long clus_bytes;
    unsigned dirclus;
    int ndir = 0;
    int n = 0;
    unsigned c;
    unsigned steps = 0;
    if (!imgpath || !dirpath || !names || cap <= 0) return -1;
    if (!fs_resolve(imgpath, resolved, sizeof(resolved))) return -1;
    if (fat_img_open(resolved, &img) < 0) return -1;
    if (fat_parse_bpb(&img, &g) < 0) return -1;
    if (fat_resolve(&img, &g, dirpath, &dirclus, 0, &ndir) < 0 ||
        !ndir) {
        return -1;
    }
    clus_bytes = (unsigned long)g.sec_per_clus * g.byts_per_sec;
    blk = (unsigned char *)kmalloc(clus_bytes);
    if (!blk) return -1;
    c = dirclus;
    while (fat_clus_ok(&g, c)) {
        unsigned long off = fat_clus_off(&g, c);
        unsigned long k;
        unsigned v;
        int done = 0;
        if (off + clus_bytes > img.size) break;
        if (fsimg_read(&img, off, blk, clus_bytes) < 0) break;
        for (k = 0; k < clus_bytes && n < cap; k += 32) {
            unsigned i, nl = 0, xl = 0;
            int di;
            if (blk[k] == 0x00) { done = 1; break; }
            if (blk[k] == 0xE5 || blk[k + 11] == 0x0F ||
                (blk[k + 11] & 0x08))
                continue;
            /* Dot entries navigate, they are not content: listings
             * skip them (the resolver handles "." and refuses ".."). */
            if (blk[k] == '.' &&
                (blk[k + 1] == ' ' ||
                 (blk[k + 1] == '.' && blk[k + 2] == ' ')))
                continue;
            for (i = 0; i < 8 && blk[k + i] != ' '; i++)
                names[n][nl++] = (char)blk[k + i];
            for (i = 0; i < 3 && blk[k + 8 + i] != ' '; i++)
                xl++;
            if (xl > 0) {
                if (nl + xl + 1 >= FAT32_NAME_MAX) continue;
                names[n][nl++] = '.';
                for (i = 0; i < xl; i++)
                    names[n][nl++] = (char)blk[k + 8 + i];
            } else if (nl == 0 || nl >= FAT32_NAME_MAX) {
                continue;
            }
            di = (blk[k + 11] & 0x10) ? 1 : 0;
            if (di) {
                if (nl + 1 >= FAT32_NAME_MAX) continue;
                names[n][nl++] = '/';
            }
            names[n][nl] = 0;
            if (isdir) isdir[n] = di;
            n++;
        }
        if (done || n >= cap) break;
        if (fat_entry(&img, &g, c, &v) < 0) break;
        if (fat_eoc(v)) break;
        c = v;
        if (++steps > g.nclus) break;
    }
    kfree(blk);
    return n;
}

int fat32_vfs_open(const char *path, int mode, void **handle) {
    char img[RAMDISK_FNAME_LEN], fatp[RAMDISK_FNAME_LEN];
    char resolved[RAMDISK_FNAME_LEN];
    fsimg_t fimg;
    fat_geo_t g;
    fat32_handle_t *h = 0;
    unsigned sc = 0;
    unsigned long sz = 0;
    int isdir = 0;
    if (mode == 1 || mode == 2) return -1;
    if (fsimg_split(path, img, sizeof(img), fatp, sizeof(fatp)) < 0)
        return -1;
    if (!fs_resolve(img, resolved, sizeof(resolved))) return -1;
    if (fat_img_open(resolved, &fimg) < 0) return -1;
    if (fat_parse_bpb(&fimg, &g) < 0) return -1;
    if (fat_resolve(&fimg, &g, fatp, &sc, &sz, &isdir) < 0 ||
        isdir) {
        return -1;
    }
    h = (fat32_handle_t *)kmalloc(sizeof(fat32_handle_t));
    if (!h) return -1;
    h->ino = fimg.ino;
    h->rf = fimg.rf;
    h->is_dev = fimg.is_dev;
    h->dev_lba = fimg.dev_lba;
    h->img_size = fimg.size;
    h->byts_per_sec = g.byts_per_sec;
    h->sec_per_clus = g.sec_per_clus;
    h->rsvd_sec = g.rsvd_sec;
    h->num_fats = g.num_fats;
    h->fatsz_sec = g.fatsz_sec;
    h->root_clus = g.root_clus;
    h->data_off = (unsigned)g.data_off;
    h->nclus = g.nclus;
    h->start_clus = sc;
    h->file_size = sz;
    *handle = h;
    return 0;
}

/* Fill the loopback backend and geometry views of an open handle. */
static void fat_views(const fat32_handle_t *h, fsimg_t *img,
                      fat_geo_t *g) {
    img->rf = h->rf;
    img->ino = h->ino;
    img->is_dev = h->is_dev;
    img->dev_lba = h->dev_lba;
    img->size = h->img_size;
    g->byts_per_sec = h->byts_per_sec;
    g->sec_per_clus = h->sec_per_clus;
    g->rsvd_sec = h->rsvd_sec;
    g->num_fats = h->num_fats;
    g->fatsz_sec = h->fatsz_sec;
    g->root_clus = h->root_clus;
    g->data_off = h->data_off;
    g->nclus = h->nclus;
}

/* Advance from the file's first cluster to the one holding `pos`,
 * step-bounded by the cluster count so a cyclic FAT terminates. */
static int fat_seek(const fat32_handle_t *h, unsigned long pos,
                    unsigned *clus_out, unsigned long *coff_out) {
    fsimg_t img;
    fat_geo_t g;
    unsigned c = h->start_clus;
    unsigned long skip;
    unsigned long cb;
    fat_views(h, &img, &g);
    cb = (unsigned long)g.sec_per_clus * g.byts_per_sec;
    if (h->file_size == 0) return -1;
    if (c < 2) return -1;
    skip = pos / cb;
    while (skip > 0) {
        unsigned v;
        if (fat_entry(&img, &g, c, &v) < 0) return -1;
        if (fat_eoc(v)) return -1;
        c = v;
        if (c < 2) return -1;
        skip--;
    }
    *clus_out = c;
    *coff_out = pos % cb;
    return 0;
}

int fat32_vfs_read(void *handle, void *buf, unsigned long pos,
                   unsigned long len) {
    fat32_handle_t *h = (fat32_handle_t *)handle;
    unsigned char *out = (unsigned char *)buf;
    unsigned long clus_bytes;
    unsigned long done = 0;
    unsigned c;
    unsigned long coff;
    if (!h || !out) return -1;
    if (pos >= h->file_size) return 0;
    if (len > h->file_size - pos) len = h->file_size - pos;
    if (len == 0) return 0;
    clus_bytes = (unsigned long)h->sec_per_clus * h->byts_per_sec;
    if (fat_seek(h, pos, &c, &coff) < 0) return -1;
    while (done < len) {
        fsimg_t img;
        fat_geo_t g;
        unsigned long take;
        unsigned long off;
        unsigned v;
        fat_views(h, &img, &g);
        take = clus_bytes - coff;
        if (take > len - done) take = len - done;
        off = h->data_off + ((unsigned long)c - 2) * clus_bytes +
            coff;
        /* One checked choke point serves all three backends
         * (ramdisk, MiniFS, real disk): no per-backend copy, so a
         * new backend can never be forgotten here again. */
        if (fsimg_read(&img, off, out + done, take) < 0) return -1;
        done += take;
        coff = 0;
        if (done >= len) break;
        if (fat_entry(&img, &g, c, &v) < 0) return -1;
        if (fat_eoc(v)) return (int)done;
        c = v;
        if (c < 2) return -1;
    }
    return (int)done;
}

int fat32_vfs_write(void *handle, const void *buf, unsigned long pos,
                    unsigned long len) {
    (void)handle;
    (void)buf;
    (void)pos;
    (void)len;
    return -1;
}

int fat32_vfs_close(void *handle) {
    if (handle) kfree(handle);
    return 0;
}

int fat32_vfs_fstat(void *handle, unsigned long *size_out) {
    fat32_handle_t *h = (fat32_handle_t *)handle;
    if (!h || !size_out) return -1;
    *size_out = h->file_size;
    return 0;
}

int fat32_vfs_truncate(void *handle, unsigned long size) {
    (void)handle;
    (void)size;
    return -1;
}

const vfs_ops_t fat32_vfs_ops = {
    .open     = fat32_vfs_open,
    .read     = fat32_vfs_read,
    .write    = fat32_vfs_write,
    .close    = fat32_vfs_close,
    .fstat    = fat32_vfs_fstat,
    .truncate = fat32_vfs_truncate,
};
