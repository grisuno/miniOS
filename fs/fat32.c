#include "kernel.h"
#include "minifs.h"
#include "fat32.h"

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

/* Loopback image backend: ramdisk first, MiniFS fallback, like kfopen.
 * img_size is the exact file size; every later offset is checked
 * against it with `len > size || off > size - len`, so a hostile BPB
 * can neither wrap the arithmetic nor read past the image. */
typedef struct {
    RDFile *rf;
    int ino;
    unsigned long size;
} fat_img_t;

static int fat_img_open(const char *resolved, fat_img_t *img) {
    RDFile *rf;
    MiniFSInode st;
    int ino;
    if (!resolved || !img) return -1;
    img->rf = 0;
    img->ino = -1;
    img->size = 0;
    rf = ramdisk_open(resolved);
    if (rf) {
        img->rf = rf;
        img->size = rf->size;
        return 0;
    }
    if (!minifs_is_mounted()) return -1;
    ino = minifs_resolve_path(resolved);
    if (ino < 0 && kstrchr(resolved, '/')) {
        /* Flat-root packing (mkfs packs files by basename, like
         * kfopen/spawn_load_image): etc/fat.img lives as fat.img. */
        const char *base = resolved;
        const char *p;
        for (p = resolved; *p; p++)
            if (*p == '/') base = p + 1;
        ino = minifs_resolve_path(base);
    }
    if (ino < 0) return -1;
    if (minifs_stat(ino, &st) < 0) return -1;
    if (st.mode & MINIFS_S_IFDIR) return -1;
    img->ino = ino;
    img->size = st.size;
    /* All sector math below is 32-bit: an image past 4 GB refuses
     * instead of truncating offsets. */
    if (img->size > 0xFFFFFFFFUL) return -1;
    return 0;
}

static int fat_img_read(const fat_img_t *img, unsigned long off,
                        void *buf, unsigned long len) {
    if (!img || !buf) return -1;
    if (len == 0) return 0;
    if (len > img->size || off > img->size - len) return -1;
    if (off > 0xFFFFFFFFUL || len > 0xFFFFFFFFUL) return -1;
    if (img->rf)
        return ramdisk_read(img->rf, buf, (unsigned)off,
                            (unsigned)len) == (int)len ? 0 : -1;
    /* Strict byte count: a short MiniFS read is a torn backend, not
     * a partial file (bounds were checked above), so it fails. */
    return minifs_read(img->ino, buf, (unsigned)off,
                       (unsigned)len) == (int)len ? 0 : -1;
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

static int fat_parse_bpb(const fat_img_t *img, fat_geo_t *g) {
    unsigned char bpb[512];
    unsigned tot16, tot32, fatsz16, data_sec;
    unsigned long fatsz_bytes, data_bytes;
    if (fat_img_read(img, 0, bpb, sizeof(bpb)) < 0) return -1;
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

static int fat_clus_ok(const fat_geo_t *g, unsigned c) {
    return c >= 2 && c < g->nclus + 2;
}

/* One FAT32 entry (low 28 bits). Reads the 512 B sector holding it;
 * the entry offset can never leave the image because the cluster is
 * range-checked first and the FAT region precedes data_off. */
static int fat_entry(const fat_img_t *img, const fat_geo_t *g,
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
    if (fat_img_read(img, sec_off, sec, sizeof(sec)) < 0) return -1;
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
static int fat_resolve(const fat_img_t *img, const fat_geo_t *g,
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
            if (fat_img_read(img, off, blk, clus_bytes) < 0) break;
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
    fat_img_t img;
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
        if (fat_img_read(&img, off, blk, clus_bytes) < 0) break;
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

/* Split "imgpath:fatpath" at the first ':' (image names never carry
 * one: the MCP/shell whitelist forbids it). */
static int fat_split(const char *path, char *img, char *fatp) {
    unsigned long i = 0, j = 0;
    if (!path || !img || !fatp) return -1;
    while (path[i] && path[i] != ':') {
        if (i >= RAMDISK_FNAME_LEN - 1) return -1;
        img[i] = path[i];
        i++;
    }
    img[i] = 0;
    if (!path[i]) return -1;
    i++;
    if (!path[i]) return -1;
    while (path[i]) {
        if (j >= RAMDISK_FNAME_LEN - 1) return -1;
        fatp[j++] = path[i++];
    }
    fatp[j] = 0;
    if (img[0] == 0 || fatp[0] == 0) return -1;
    return 0;
}

int fat32_vfs_open(const char *path, int mode, void **handle) {
    char img[RAMDISK_FNAME_LEN], fatp[RAMDISK_FNAME_LEN];
    char resolved[RAMDISK_FNAME_LEN];
    fat_img_t fimg;
    fat_geo_t g;
    fat32_handle_t *h = 0;
    unsigned sc = 0;
    unsigned long sz = 0;
    int isdir = 0;
    if (mode == 1 || mode == 2) return -1;
    if (fat_split(path, img, fatp) < 0) return -1;
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
static void fat_views(const fat32_handle_t *h, fat_img_t *img,
                      fat_geo_t *g) {
    img->rf = h->rf;
    img->ino = h->ino;
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
    fat_img_t img;
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
        fat_img_t img;
        fat_geo_t g;
        unsigned long take;
        unsigned long off;
        unsigned v;
        fat_views(h, &img, &g);
        take = clus_bytes - coff;
        if (take > len - done) take = len - done;
        off = h->data_off + ((unsigned long)c - 2) * clus_bytes +
            coff;
        if (take > img.size || off > img.size - take) return -1;
        if (img.rf) {
            if (ramdisk_read(img.rf, out + done, (unsigned)off,
                             (unsigned)take) != (int)take)
                return -1;
        } else {
            if (minifs_read(img.ino, out + done, (unsigned)off,
                            (unsigned)take) < 0)
                return -1;
        }
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
