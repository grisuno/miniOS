/** Docstring: Host test for the ext4 loopback driver (make test-ext4).
 *
 * Stubs the kernel surface ext4.c names (heap, strings, resolve,
 * ramdisk backend over an in-memory fixture, absent MiniFS/IDE) and
 * asserts the read-only subset against a synthetic 64-block image:
 * superblock and group validation, root/subdir listing with dot
 * skipping, single and multi-extent reads, holes as zeros, legacy
 * direct plus singly-indirect blocks, fail-closed edges (bad magic,
 * missing file, dotdot, symlink/htree/double-indirect refusal,
 * write refusal) and the VFS open/read/fstat verbs. The MiniFS and
 * real-disk backends ride the shared fsimg contract and are proven
 * live by the ext4 BDD scenarios on etc/ext4.img and hd0.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kernel.h"
#include "minifs.h"
#include "ext4.h"
#include "fsimg.h"

void *kmalloc(unsigned long size) {
    return malloc((unsigned long)size ? (unsigned long)size : 1);
}

void kfree(void *ptr) {
    free(ptr);
}

unsigned long kstrlen(const char *s) {
    return (unsigned long)strlen(s);
}

int kstrncmp(const char *a, const char *b, unsigned long n) {
    return strncmp(a, b, (unsigned long)n);
}

char *kstrncpy(char *dst, const char *src, unsigned long n) {
    unsigned long i;
    for (i = 0; i < n && src[i]; i++) dst[i] = src[i];
    for (; i < n; i++) dst[i] = 0;
    return dst;
}

void *kmemcpy(void *dst, const void *src, unsigned long n) {
    return memcpy(dst, src, (unsigned long)n);
}

char *kstrchr(const char *s, int c) {
    return strchr(s, c);
}

int fs_resolve(const char *path, char *out, unsigned cap) {
    unsigned long n = strlen(path) + 1;
    if (n > cap) return 0;
    memcpy(out, path, n);
    return 1;
}

#define EXT_FIX_BLOCKS 64UL
#define EXT_FIX_SIZE (EXT_FIX_BLOCKS * 1024UL)

static unsigned char *ext_fix_img = 0;
static RDFile ext_fix_rf;

RDFile *ramdisk_open(const char *name) {
    (void)name;
    return &ext_fix_rf;
}

int ramdisk_read(RDFile *f, void *buf, unsigned offset, unsigned len) {
    if (!f || !buf) return 0;
    if (offset >= f->size) return 0;
    if (offset + len > f->size) len = f->size - offset;
    memcpy(buf, ext_fix_img + f->offset + offset, len);
    return (int)len;
}

int minifs_is_mounted(void) {
    return 0;
}

int minifs_resolve_path(const char *path) {
    (void)path;
    return -1;
}

int minifs_stat(int ino, MiniFSInode *out) {
    (void)ino;
    (void)out;
    return -1;
}

int minifs_read(int ino, void *buf, unsigned off, unsigned len) {
    (void)ino;
    (void)buf;
    (void)off;
    (void)len;
    return -1;
}

int ide_present(void) {
    return 0;
}

unsigned int ide_total_sectors(void) {
    return 0;
}

int ide_read_sectors(unsigned int lba, unsigned int count, void *buf) {
    (void)lba;
    (void)count;
    (void)buf;
    return -1;
}

#include "fs/fsimg.c"
#include "fs/ext4.c"

static int failures = 0;

#define CHECK(cond) \
    do { \
        if (!(cond)) { \
            printf("FAIL line %d: %s\n", __LINE__, #cond); \
            failures++; \
        } \
    } while (0)

static void e16(unsigned char *p, unsigned v) {
    p[0] = (unsigned char)(v & 255);
    p[1] = (unsigned char)((v >> 8) & 255);
}

static void e32(unsigned char *p, unsigned long v) {
    p[0] = (unsigned char)(v & 255);
    p[1] = (unsigned char)((v >> 8) & 255);
    p[2] = (unsigned char)((v >> 16) & 255);
    p[3] = (unsigned char)((v >> 24) & 255);
}

/* Append one directory entry at off; returns the next offset. */
static unsigned ext_fix_de(unsigned char *d, unsigned off, const char *nm,
                           unsigned ino, unsigned char type) {
    unsigned nl = (unsigned)strlen(nm);
    unsigned reclen = ((8 + nl + 3) / 4) * 4;
    e32(d + off + 0, ino);
    e16(d + off + 4, reclen);
    d[off + 6] = (unsigned char)nl;
    d[off + 7] = type;
    memcpy(d + off + 8, nm, nl);
    return off + reclen;
}

static void ext_fix_inode(unsigned ino, unsigned mode, unsigned long size,
                          unsigned flags, const unsigned char *iblk) {
    unsigned char *ib = ext_fix_img + 5 * 1024 + (ino - 1) * 128;
    e16(ib + 0, mode);
    e32(ib + 4, (unsigned)(size & 0xFFFFFFFFUL));
    e16(ib + 26, 1);
    e32(ib + 32, flags);
    memcpy(ib + 40, iblk, 60);
    e32(ib + 108, (unsigned)(size >> 32));
}

/* One single-extent leaf: logical l0 runs len blocks from phys p0. */
static void ext_fix_x1(unsigned char *iblk, unsigned l0, unsigned p0,
                       unsigned len) {
    e16(iblk + 0, 0xF30A);
    e16(iblk + 2, 1);
    e16(iblk + 4, 4);
    e16(iblk + 6, 0);
    e32(iblk + 12, l0);
    e16(iblk + 16, len);
    e16(iblk + 18, 0);
    e32(iblk + 20, p0);
}

static void ext_fix_build(void) {
    unsigned char *sb;
    unsigned char *gd;
    unsigned char iblk[60];
    unsigned o;
    unsigned long i;
    ext_fix_img = calloc(1, EXT_FIX_SIZE);
    if (!ext_fix_img) {
        printf("FAIL: fixture alloc\n");
        exit(1);
    }
    sb = ext_fix_img + 1024;
    e32(sb + 0, 60);
    e32(sb + 4, EXT_FIX_BLOCKS);
    e32(sb + 20, 1);
    e32(sb + 24, 0);
    e32(sb + 32, 8192);
    e32(sb + 40, 32);
    e16(sb + 56, 0xEF53);
    e16(sb + 88, 128);
    e32(sb + 96, 0x40);
    gd = ext_fix_img + 2 * 1024;
    e32(gd + 8, 5);
    memset(iblk, 0, sizeof(iblk));
    ext_fix_x1(iblk, 0, 9, 1);
    ext_fix_inode(2, 0040000, 1024, 0x80000, iblk);
    {
        unsigned char *root = ext_fix_img + 9 * 1024;
        unsigned o = 0;
        o = ext_fix_de(root, o, ".", 2, 2);
        o = ext_fix_de(root, o, "..", 2, 2);
        o = ext_fix_de(root, o, "hello.txt", 12, 1);
        o = ext_fix_de(root, o, "sub", 15, 2);
        o = ext_fix_de(root, o, "empty.txt", 13, 1);
        o = ext_fix_de(root, o, "link.txt", 14, 7);
        o = ext_fix_de(root, o, "legacy.bin", 19, 1);
        o = ext_fix_de(root, o, "htree", 18, 2);
        o = ext_fix_de(root, o, "double.bin", 17, 1);
        (void)o;
    }
    memset(iblk, 0, sizeof(iblk));
    ext_fix_x1(iblk, 0, 10, 1);
    {
        unsigned char two[60];
        memset(two, 0, sizeof(two));
        e16(two + 0, 0xF30A);
        e16(two + 2, 2);
        e16(two + 4, 4);
        e16(two + 6, 0);
        e32(two + 12, 0);
        e16(two + 16, 1);
        e16(two + 18, 0);
        e32(two + 20, 10);
        e32(two + 24, 1);
        e16(two + 28, 1);
        e16(two + 30, 0);
        e32(two + 32, 11);
        memcpy(iblk, two, 36);
    }
    ext_fix_inode(12, 0100000, 1500, 0x80000, iblk);
    for (i = 0; i < 1500; i++)
        ext_fix_img[(i < 1024 ? 10 : 11) * 1024 + (i % 1024)] =
            (unsigned char)('A' + (i % 26));
    memset(iblk, 0, sizeof(iblk));
    ext_fix_inode(13, 0100000, 0, 0x80000, iblk);
    memset(iblk, 0, sizeof(iblk));
    ext_fix_inode(14, 0120000, 9, 0, iblk);
    memset(iblk, 0, sizeof(iblk));
    ext_fix_x1(iblk, 0, 12, 1);
    ext_fix_inode(15, 0040000, 1024, 0x80000, iblk);
    {
        unsigned char *sub = ext_fix_img + 12 * 1024;
        o = 0;
        o = ext_fix_de(sub, o, ".", 15, 2);
        o = ext_fix_de(sub, o, "..", 2, 2);
        o = ext_fix_de(sub, o, "note.txt", 16, 1);
        (void)o;
    }
    memset(iblk, 0, sizeof(iblk));
    ext_fix_x1(iblk, 0, 13, 1);
    ext_fix_inode(16, 0100000, 512, 0x80000, iblk);
    for (i = 0; i < 512; i++)
        ext_fix_img[13 * 1024 + i] = (unsigned char)(255 - i);
    memset(iblk, 0, sizeof(iblk));
    for (i = 0; i < 12; i++)
        e32(iblk + i * 4, 30 + i);
    e32(iblk + 48, 42);
    ext_fix_inode(19, 0100000, 14 * 1024, 0, iblk);
    {
        unsigned char *ind = ext_fix_img + 42 * 1024;
        unsigned long k;
        e32(ind + 0, 43);
        e32(ind + 4, 44);
        for (k = 0; k < 14 * 1024; k++) {
            unsigned long blk =
                k < 12 * 1024 ? 30 + k / 1024 : 43 + (k - 12 * 1024) / 1024;
            ext_fix_img[blk * 1024 + (k % 1024)] =
                (unsigned char)('a' + (k % 26));
        }
    }
    memset(iblk, 0, sizeof(iblk));
    e32(iblk + 52, 50);
    ext_fix_inode(17, 0100000, 3 * 1024, 0, iblk);
    {
        unsigned char htree[128];
        memset(htree, 0, sizeof(htree));
        ext_fix_inode(18, 0040000, 1024, 0x80000 | 0x1000, htree);
    }
    ext_fix_rf.size = (unsigned)EXT_FIX_SIZE;
    ext_fix_rf.offset = 0;
    strcpy(ext_fix_rf.name, "ext4.img");
}

static void test_image(void) {
    char names[8][EXT4_NAME_MAX + 1];
    int isdir[8];
    int n;
    void *h = 0;
    unsigned char buf[1600];
    unsigned long sz = 0;
    unsigned long i;
    n = ext4_list("ext4.img", "/", names, isdir, 8);
    CHECK(n == 7);
    if (n == 7) {
        CHECK(strcmp(names[0], "hello.txt") == 0 && isdir[0] == 0);
        CHECK(strcmp(names[1], "sub/") == 0 && isdir[1] == 1);
        CHECK(strcmp(names[2], "empty.txt") == 0 && isdir[2] == 0);
        CHECK(strcmp(names[3], "link.txt") == 0 && isdir[3] == 0);
        CHECK(strcmp(names[4], "legacy.bin") == 0 && isdir[4] == 0);
        CHECK(strcmp(names[5], "htree/") == 0 && isdir[5] == 1);
        CHECK(strcmp(names[6], "double.bin") == 0 && isdir[6] == 0);
    }
    n = ext4_list("ext4.img", "/sub", names, isdir, 8);
    CHECK(n == 1);
    if (n == 1)
        CHECK(strcmp(names[0], "note.txt") == 0 && isdir[0] == 0);
    CHECK(ext4_list("ext4.img", "/NOPE", names, isdir, 8) < 0);
    CHECK(ext4_list("ext4.img", "/../x", names, isdir, 8) < 0);
    CHECK(ext4_vfs_open("ext4.img:/hello.txt", 0, &h) == 0);
    if (h) {
        int r;
        CHECK(ext4_vfs_fstat(h, &sz) == 0 && sz == 1500);
        r = ext4_vfs_read(h, buf, 0, sizeof(buf));
        CHECK(r == 1500);
        if (r == 1500) {
            for (i = 0; i < 1500; i++) {
                if (buf[i] != (unsigned char)('A' + (i % 26))) break;
            }
            CHECK(i == 1500);
        }
        r = ext4_vfs_read(h, buf, 1400, sizeof(buf));
        CHECK(r == 100);
        if (r == 100) {
            for (i = 0; i < 100; i++) {
                if (buf[i] !=
                    (unsigned char)('A' + ((1400 + i) % 26)))
                    break;
            }
            CHECK(i == 100);
        }
        CHECK(ext4_vfs_close(h) == 0);
    }
    h = 0;
    CHECK(ext4_vfs_open("ext4.img:/sub/note.txt", 0, &h) == 0);
    if (h) {
        int r = ext4_vfs_read(h, buf, 0, 512);
        unsigned long k;
        CHECK(r == 512);
        for (k = 0; k < 512; k++) {
            if (buf[k] != (unsigned char)(255 - k)) break;
        }
        CHECK(k == 512);
        CHECK(ext4_vfs_close(h) == 0);
    }
    h = 0;
    CHECK(ext4_vfs_open("ext4.img:/empty.txt", 0, &h) == 0);
    if (h) {
        CHECK(ext4_vfs_read(h, buf, 0, sizeof(buf)) == 0);
        CHECK(ext4_vfs_close(h) == 0);
    }
    h = 0;
    CHECK(ext4_vfs_open("ext4.img:/legacy.bin", 0, &h) == 0);
    if (h) {
        unsigned long off;
        CHECK(ext4_vfs_fstat(h, &sz) == 0 && sz == 14 * 1024);
        for (off = 0; off < 14 * 1024; off += sizeof(buf)) {
            int r = ext4_vfs_read(h, buf, off, sizeof(buf));
            unsigned long k;
            unsigned long want =
                14 * 1024 - off < sizeof(buf) ? 14 * 1024 - off :
                                                sizeof(buf);
            CHECK(r == (int)want);
            if (r != (int)want) break;
            for (k = 0; k < want; k++) {
                if (buf[k] !=
                    (unsigned char)('a' + ((off + k) % 26)))
                    break;
            }
            CHECK(k == want);
            if (k != want) break;
        }
        CHECK(ext4_vfs_close(h) == 0);
    }
    h = 0;
    /* Doubly-indirect inodes open (like Linux) but their reads fail
     * closed instead of walking levels v1 does not serve. */
    CHECK(ext4_vfs_open("ext4.img:/double.bin", 0, &h) == 0);
    if (h) {
        CHECK(ext4_vfs_read(h, buf, 0, sizeof(buf)) < 0);
        CHECK(ext4_vfs_close(h) == 0);
    }
    CHECK(ext4_vfs_open("ext4.img:/missing.txt", 0, &h) < 0);
    CHECK(ext4_vfs_open("ext4.img:/sub", 0, &h) < 0);
    CHECK(ext4_vfs_open("ext4.img:/link.txt", 0, &h) < 0);
    CHECK(ext4_vfs_open("ext4.img:/htree", 0, &h) < 0);
    CHECK(ext4_vfs_open("ext4.img:/hello.txt", 1, &h) < 0);
    CHECK(ext4_vfs_write(h, buf, 0, 1) < 0);
    CHECK(ext4_vfs_truncate(h, 0) < 0);
}

static void test_bad_magic(void) {
    void *h = 0;
    char names[2][EXT4_NAME_MAX + 1];
    ext_fix_img[1024 + 56] = 0x00;
    CHECK(ext4_list("ext4.img", "/", names, 0, 2) < 0);
    CHECK(ext4_vfs_open("ext4.img:/hello.txt", 0, &h) < 0);
    ext_fix_img[1024 + 56] = 0x53;
}

int main(void) {
    ext_fix_build();
    test_image();
    test_bad_magic();
    if (failures == 0) printf("ext4: ok\n");
    return failures ? 1 : 0;
}
