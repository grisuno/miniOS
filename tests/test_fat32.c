/** Docstring: Host test for the FAT32 loopback driver (make test-fat).
 *
 * Stubs the kernel surface fat32.c names (heap, strings, resolve,
 * ramdisk backend over an in-memory fixture) and asserts the whole
 * read-only contract against a synthetic 64 MB FAT32 image built
 * here: BPB validation, root/subdir listing, multi-cluster chain
 * reads, fail-closed edges (bad magic, missing file, overlong name,
 * dotdot, empty file, write refusal) and the VFS open/read/fstat
 * verbs. A mutant that drops any check reads garbage or succeeds
 * where this test demands refusal, so it dies here with no QEMU
 * boot. The MiniFS backend rides the same code and is proven live
 * by the fat BDD scenarios on etc/fat.img.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kernel.h"
#include "minifs.h"
#include "fat32.h"

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

int fs_resolve(const char *path, char *out, unsigned cap) {
    unsigned long n = strlen(path) + 1;
    if (n > cap) return 0;
    memcpy(out, path, n);
    return 1;
}

#define FAT_FIX_SECTORS 131072UL
#define FAT_FIX_SIZE (FAT_FIX_SECTORS * 512UL)

static unsigned char *fat_fix_img = 0;
static unsigned fat_fix_nclus = 0;

static RDFile fat_fix_rf;

RDFile *ramdisk_open(const char *name) {
    (void)name;
    return &fat_fix_rf;
}

int ramdisk_read(RDFile *f, void *buf, unsigned offset, unsigned len) {
    if (!f || !buf) return 0;
    if (offset >= f->size) return 0;
    if (offset + len > f->size) len = f->size - offset;
    memcpy(buf, fat_fix_img + f->offset + offset, len);
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

#include "fs/fat32.c"

static int failures = 0;

#define CHECK(cond) \
    do { \
        if (!(cond)) { \
            printf("FAIL line %d: %s\n", __LINE__, #cond); \
            failures++; \
        } \
    } while (0)

static void st16(unsigned char *p, unsigned v) {
    p[0] = (unsigned char)(v & 255);
    p[1] = (unsigned char)((v >> 8) & 255);
}

static void st32(unsigned char *p, unsigned long v) {
    p[0] = (unsigned char)(v & 255);
    p[1] = (unsigned char)((v >> 8) & 255);
    p[2] = (unsigned char)((v >> 16) & 255);
    p[3] = (unsigned char)((v >> 24) & 255);
}

static void fat_fix_build(void) {
    unsigned char *bpb;
    unsigned char *fat;
    unsigned char *root;
    unsigned char *sub;
    unsigned long data_off;
    unsigned long i;
    fat_fix_img = calloc(1, FAT_FIX_SIZE);
    if (!fat_fix_img) {
        printf("FAIL: fixture alloc\n");
        exit(1);
    }
    bpb = fat_fix_img;
    bpb[0] = 0xEB;
    bpb[1] = 0x58;
    bpb[2] = 0x90;
    memcpy(bpb + 3, "MINIFAT ", 8);
    st16(bpb + 11, 512);
    bpb[13] = 1;
    st16(bpb + 14, 32);
    bpb[16] = 2;
    st16(bpb + 19, 0);
    bpb[21] = 0xF8;
    st16(bpb + 22, 0);
    st32(bpb + 32, FAT_FIX_SECTORS);
    st32(bpb + 36, 1024);
    st32(bpb + 44, 2);
    bpb[510] = 0x55;
    bpb[511] = 0xAA;
    data_off = (32 + 2 * 1024) * 512UL;
    fat_fix_nclus = (unsigned)((FAT_FIX_SIZE - data_off) / 512UL);
    fat = fat_fix_img + 32 * 512UL;
    st32(fat + 0, 0x0FFFFFF8UL);
    st32(fat + 4, 0x0FFFFFFFUL);
    st32(fat + 8, 0x0FFFFFFFUL);
    st32(fat + 12, 4);
    st32(fat + 16, 0x0FFFFFFFUL);
    st32(fat + 20, 6);
    st32(fat + 24, 7);
    st32(fat + 28, 0x0FFFFFFFUL);
    memcpy(fat_fix_img + (32 + 1024) * 512UL, fat, 1024 * 512UL);
    root = fat_fix_img + data_off;
    memcpy(root + 0, "HELLO   TXT", 11);
    root[11] = 0x20;
    st16(root + 26, 3);
    st32(root + 28, 600);
    memcpy(root + 32, "SUBDIR     ", 11);
    root[32 + 11] = 0x10;
    st16(root + 32 + 26, 5);
    st32(root + 32 + 28, 0);
    memcpy(root + 64, "EMPTY   TXT", 11);
    root[64 + 11] = 0x20;
    st16(root + 64 + 26, 0);
    st32(root + 64 + 28, 0);
    for (i = 0; i < 600; i++)
        fat_fix_img[data_off + (3 - 2) * 512UL + i] =
            (unsigned char)('A' + (i % 26));
    for (i = 0; i < 512; i++)
        fat_fix_img[data_off + (4 - 2) * 512UL + i] =
            (unsigned char)('A' + ((512 + i) % 26));
    sub = fat_fix_img + data_off + (5 - 2) * 512UL;
    memcpy(sub + 0, ".          ", 11);
    sub[11] = 0x10;
    memcpy(sub + 32, "..         ", 11);
    sub[32 + 11] = 0x10;
    memcpy(sub + 64, "NOTE    TXT", 11);
    sub[64 + 11] = 0x20;
    st16(sub + 64 + 26, 6);
    st32(sub + 64 + 28, 512);
    for (i = 0; i < 512; i++)
        fat_fix_img[data_off + (6 - 2) * 512UL + i] =
            (unsigned char)(255 - i);
    sub = fat_fix_img + data_off + (7 - 2) * 512UL;
    (void)sub;
    fat_fix_rf.size = (unsigned)FAT_FIX_SIZE;
    fat_fix_rf.offset = 0;
    strcpy(fat_fix_rf.name, "fat.img");
}

static void test_units(void) {
    char n8[8], e3[3];
    unsigned char de[32];
    memset(de, ' ', sizeof(de));
    memcpy(de, "HELLO   TXT", 11);
    de[11] = 0x20;
    CHECK(fat_qword("hello.txt", 9, n8, e3) == 0);
    CHECK(fat_match(de, n8, e3) == 1);
    CHECK(fat_qword("toolongname.txt", 15, n8, e3) < 0);
    CHECK(fat_qword("a/b", 3, n8, e3) < 0);
    CHECK(fat_qword("x*.txt", 6, n8, e3) < 0);
    CHECK(fat_eoc(0x0FFFFFF8UL) == 1);
    CHECK(fat_eoc(12) == 0);
    CHECK(fat_qword("SUBDIR", 6, n8, e3) == 0);
    memset(de, ' ', sizeof(de));
    memcpy(de, "SUBDIR     ", 11);
    de[11] = 0x10;
    CHECK(fat_match(de, n8, e3) == 1);
    de[0] = 0xE5;
    CHECK(fat_match(de, n8, e3) == 0);
}

static void test_image(void) {
    char names[8][FAT32_NAME_MAX];
    int isdir[8];
    int n;
    void *h = 0;
    unsigned char buf[700];
    unsigned long sz = 0;
    unsigned long i;
    n = fat32_list("fat.img", "/", names, isdir, 8);
    CHECK(n == 3);
    if (n == 3) {
        CHECK(strcmp(names[0], "HELLO.TXT") == 0 && isdir[0] == 0);
        CHECK(strcmp(names[1], "SUBDIR/") == 0 && isdir[1] == 1);
        CHECK(strcmp(names[2], "EMPTY.TXT") == 0 && isdir[2] == 0);
    }
    n = fat32_list("fat.img", "/SUBDIR", names, isdir, 8);
    CHECK(n == 1);
    if (n == 1)
        CHECK(strcmp(names[0], "NOTE.TXT") == 0 && isdir[0] == 0);
    CHECK(fat32_list("fat.img", "/NOPE", names, isdir, 8) < 0);
    CHECK(fat32_list("fat.img", "/../x", names, isdir, 8) < 0);
    CHECK(fat32_vfs_open("fat.img:/HELLO.TXT", 0, &h) == 0);
    if (h) {
        int r;
        CHECK(fat32_vfs_fstat(h, &sz) == 0 && sz == 600);
        r = fat32_vfs_read(h, buf, 0, sizeof(buf));
        CHECK(r == 600);
        if (r == 600) {
            for (i = 0; i < 600; i++) {
                if (buf[i] != (unsigned char)('A' + (i % 26))) break;
            }
            CHECK(i == 600);
        }
        r = fat32_vfs_read(h, buf, 590, sizeof(buf));
        CHECK(r == 10);
        CHECK(fat32_vfs_close(h) == 0);
    }
    h = 0;
    CHECK(fat32_vfs_open("fat.img:/SUBDIR/NOTE.TXT", 0, &h) == 0);
    if (h) {
        int r = fat32_vfs_read(h, buf, 0, 512);
        unsigned long k;
        CHECK(r == 512);
        for (k = 0; k < 512; k++) {
            if (buf[k] != (unsigned char)(255 - k)) break;
        }
        CHECK(k == 512);
        CHECK(fat32_vfs_close(h) == 0);
    }
    h = 0;
    CHECK(fat32_vfs_open("fat.img:/EMPTY.TXT", 0, &h) == 0);
    if (h) {
        CHECK(fat32_vfs_read(h, buf, 0, sizeof(buf)) == 0);
        CHECK(fat32_vfs_close(h) == 0);
    }
    CHECK(fat32_vfs_open("fat.img:/MISSING.TXT", 0, &h) < 0);
    CHECK(fat32_vfs_open("fat.img:/SUBDIR", 0, &h) < 0);
    CHECK(fat32_vfs_open("fat.img:/HELLO.TXT", 1, &h) < 0);
    CHECK(fat32_vfs_write(h, buf, 0, 1) < 0);
    CHECK(fat32_vfs_truncate(h, 0) < 0);
}

static void test_bad_magic(void) {
    void *h = 0;
    char names[2][FAT32_NAME_MAX];
    fat_fix_img[510] = 0x00;
    CHECK(fat32_list("fat.img", "/", names, 0, 2) < 0);
    CHECK(fat32_vfs_open("fat.img:/HELLO.TXT", 0, &h) < 0);
    fat_fix_img[510] = 0x55;
}

int main(void) {
    fat_fix_build();
    test_units();
    test_image();
    test_bad_magic();
    if (failures == 0) printf("fat32: ok\n");
    return failures ? 1 : 0;
}
