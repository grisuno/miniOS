#include "kernel.h"
#include "minifs.h"
#include "fsimg.h"
#include "block.h"

/* ================================================================
 *  fsimg -- shared loopback/device image backend
 * ================================================================
 * Moved whole from fs/fat32.c so ext4 rides the same contract:
 * ramdisk-first/MiniFS-fallback files plus absolute-LBA disk
 * regions, every offset fenced before it is used. No filesystem
 * parser lives here; drivers validate structure on top.
 * ================================================================ */

int fsimg_open_file(const char *resolved, fsimg_t *img) {
    RDFile *rf;
    MiniFSInode st;
    int ino;
    if (!resolved || !img) return -1;
    img->rf = 0;
    img->ino = -1;
    img->is_dev = 0;
    img->dev_lba = 0;
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
    if (img->size > 0xFFFFFFFFUL) return -1;
    return 0;
}

int fsimg_open_dev(unsigned long base_lba, unsigned long nsec,
                   fsimg_t *img) {
    unsigned long total;
    if (!img) return -1;
    total = block_disk_sectors();
    if (total == 0) return -1;
    if (nsec == 0 || base_lba >= total || nsec > total - base_lba)
        return -1;
    img->rf = 0;
    img->ino = -1;
    img->is_dev = 1;
    img->dev_lba = base_lba;
    img->size = nsec * 512UL;
    if (img->size > 0xFFFFFFFFUL) img->size = 0xFFFFFFFFUL;
    return 0;
}

/** Docstring: Sector reads off the active backend through the block layer,
 * so a device image on USB reads from USB. The scratch is heap, never the
 * caller's stack: the USB backend hands the buffer to the controller as a
 * physical address, which a stack address is not. */
static int fsimg_dev_read(const fsimg_t *img, unsigned long off,
                          void *buf, unsigned long len) {
    unsigned char *sec = (unsigned char *)kmalloc(512);
    unsigned char *out = (unsigned char *)buf;
    int rc = 0;
    if (!sec) return -1;
    while (len > 0) {
        unsigned long lba = img->dev_lba + off / 512UL;
        unsigned at = (unsigned)(off % 512UL);
        unsigned long take = 512UL - at;
        if (take > len) take = len;
        if (block_read_sectors((unsigned)lba, 1, sec) < 0) {
            rc = -1;
            break;
        }
        kmemcpy(out, sec + at, take);
        out += take;
        off += take;
        len -= take;
    }
    kfree(sec);
    return rc;
}

int fsimg_read(const fsimg_t *img, unsigned long off, void *buf,
               unsigned long len) {
    if (!img || !buf) return -1;
    if (len == 0) return 0;
    if (len > img->size || off > img->size - len) return -1;
    if (off > 0xFFFFFFFFUL || len > 0xFFFFFFFFUL) return -1;
    if (img->is_dev) return fsimg_dev_read(img, off, buf, len);
    if (img->rf)
        return ramdisk_read(img->rf, buf, (unsigned)off,
                            (unsigned)len) == (int)len ? 0 : -1;
    /* Strict byte count: a short MiniFS read is a torn backend, not
     * a partial file (bounds were checked above), so it fails. */
    return minifs_read(img->ino, buf, (unsigned)off,
                       (unsigned)len) == (int)len ? 0 : -1;
}

int fsimg_split(const char *path, char *left, unsigned llen,
                char *right, unsigned rlen) {
    unsigned long i = 0, j = 0;
    if (!path || !left || !right || llen == 0 || rlen == 0) return -1;
    while (path[i] && path[i] != ':') {
        if (i >= (unsigned long)llen - 1) return -1;
        left[i] = path[i];
        i++;
    }
    left[i] = 0;
    if (!path[i]) return -1;
    i++;
    if (!path[i]) return -1;
    while (path[i]) {
        if (j >= (unsigned long)rlen - 1) return -1;
        right[j++] = path[i++];
    }
    right[j] = 0;
    if (left[0] == 0 || right[0] == 0) return -1;
    return 0;
}
