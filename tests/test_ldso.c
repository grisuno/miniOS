/** Docstring: host test for the ld.so pure parser (make test-ldso).
 *
 * Builds minimal ELF64/dynamic images in memory (never from disk: no
 * fixtures, no host paths) and pins the T8 L3 contract: PT_DYNAMIC
 * discovery, VA translation, dynamic scan, hash-sized symbol counts,
 * bounded string copies, GLOBAL FUNC/NOTYPE lookup, RELA validation
 * (GLOB_DAT/JUMP_SLOT pass, anything else refuses), and basename
 * normalization. Every corrupt input fails closed; every valid input
 * resolves exactly.
 */

#include <stdio.h>
#include <string.h>

#include "ldso.h"
#include "kernel/ldso_parse.c"

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

static void w16(unsigned char *p, unsigned v) {
    p[0] = (unsigned char)v;
    p[1] = (unsigned char)(v >> 8);
}

static void w32(unsigned char *p, unsigned long v) {
    p[0] = (unsigned char)v;
    p[1] = (unsigned char)(v >> 8);
    p[2] = (unsigned char)(v >> 16);
    p[3] = (unsigned char)(v >> 24);
}

static void w64(unsigned char *p, unsigned long long v) {
    w32(p, (unsigned long)v);
    w32(p + 4, (unsigned long)(v >> 32));
}

/* Minimal image layout (all offsets identity: VA == file offset):
 *   0x0000 ehdr (64)
 *   0x0040 phdr[LOAD 0,filesz] + phdr[DYNAMIC]
 *   0x0100 dynamic array
 *   0x0200 strtab ("libx.so", "myfunc")
 *   0x0300 symtab (null + one GLOBAL FUNC myfunc @0x1234)
 *   0x0400 hash (1 bucket, 2 chain)
 *   0x0500 rela (one GLOB_DAT row, sym 1, offset 0x600)
 */
#define IMG_SZ 0x800
#define DYN_OFF 0x100
#define STR_OFF 0x200
#define SYM_OFF 0x300
#define HASH_OFF 0x400
#define RELA_OFF 0x500

static void build_ehdr(unsigned char *img, int with_dyn) {
    memset(img, 0, IMG_SZ);
    img[0] = 0x7F;
    img[1] = 'E';
    img[2] = 'L';
    img[3] = 'F';
    img[4] = 2;
    img[5] = 1;
    w16(img + 16, 3);
    w16(img + 18, 62);
    w64(img + 32, 0x40);
    w16(img + 54, 56);
    w16(img + 56, with_dyn ? 2 : 1);
    w64(img + 8, 0x100);
    w64(img + 40, 0x40);
    w32(img + 64, 1);
    w32(img + 68, 5);
    w64(img + 72, 0);
    w64(img + 80, 0);
    w64(img + 96, IMG_SZ);
    w64(img + 104, IMG_SZ);
    if (with_dyn) {
        unsigned char *p = img + 0x40 + 56;
        w32(p, 2);
        w32(p + 4, 4);
        w64(p + 8, DYN_OFF);
        w64(p + 16, DYN_OFF);
        w64(p + 32, 0xa0);
        w64(p + 40, 0xa0);
    }
}

static void build_tables(unsigned char *img, int rela_type) {
    unsigned char *d = img + DYN_OFF;
    memcpy(img + STR_OFF, "libx.so\0myfunc\0", 15);
    w32(img + SYM_OFF + 24, 8);
    img[SYM_OFF + 28] = 0x12;
    w16(img + SYM_OFF + 30, 1);
    w64(img + SYM_OFF + 32, 0x1234);
    w32(img + HASH_OFF, 1);
    w32(img + HASH_OFF + 4, 2);
    w32(img + HASH_OFF + 8, 1);
    w64(img + RELA_OFF, 0x600);
    w64(img + RELA_OFF + 8, ((unsigned long long)1 << 32) | (unsigned)rela_type);
    w64(img + RELA_OFF + 16, 0);
    w64(d + 0, 1);
    w64(d + 8, 0);
    w64(d + 16, 4);
    w64(d + 24, HASH_OFF);
    w64(d + 32, 5);
    w64(d + 40, STR_OFF);
    w64(d + 48, 6);
    w64(d + 56, SYM_OFF);
    w64(d + 64, 10);
    w64(d + 72, 15);
    w64(d + 80, 11);
    w64(d + 88, 24);
    w64(d + 96, 7);
    w64(d + 104, RELA_OFF);
    w64(d + 112, 8);
    w64(d + 120, 24);
    w64(d + 128, 9);
    w64(d + 136, 24);
    w64(d + 144, 0);
    w64(d + 152, 0);
}

int main(void) {
    static unsigned char img[IMG_SZ];
    unsigned long long off = 0;
    unsigned long long size = 0;
    LdsoDynInfo info;
    LdsoRelaRow row;
    LdsoSeg segs[4];
    unsigned nseg = 0;
    unsigned n = 0;
    unsigned long long val = 0;
    char name[LDSO_NAME_LEN];
    int rc;

    build_ehdr(img, 1);
    build_tables(img, 6);
    rc = ldso_find_dynamic(img, IMG_SZ, &off, &size);
    CHECK(rc == 1 && off == DYN_OFF && size == 0xa0, "find dynamic");
    CHECK(ldso_scan_dynamic(img, IMG_SZ, off, size, &info) == 0,
        "scan dynamic");
    CHECK(info.needed_count == 1 && info.strtab_va == STR_OFF,
        "scan needed/strtab");
    CHECK(info.symtab_va == SYM_OFF && info.strsz == 15, "scan symtab");
    CHECK(info.has_rela && info.relasz == 24 && info.relaent == 24,
        "scan rela");
    CHECK(ldso_vaddr_to_offset(img, IMG_SZ, STR_OFF, &off) == 0 &&
        off == STR_OFF, "vaddr identity");
    CHECK(ldso_vaddr_to_offset(img, IMG_SZ, 0xdead, &off) != 0,
        "vaddr miss refuses");
    CHECK(ldso_segments(img, IMG_SZ, segs, 4, &nseg) == 0 && nseg == 1,
        "segments");
    CHECK(ldso_sym_count(img, IMG_SZ, HASH_OFF, &n) == 0 && n == 2,
        "hash count");
    CHECK(ldso_copy_str(img, IMG_SZ, STR_OFF, 15, 8, name,
        sizeof(name)) == 0 && strcmp(name, "myfunc") == 0, "copy str");
    CHECK(ldso_copy_str(img, IMG_SZ, STR_OFF, 15, 99, name,
        sizeof(name)) != 0, "copy str oob refuses");
    CHECK(ldso_copy_str(img, IMG_SZ, STR_OFF, 7, 0, name,
        sizeof(name)) != 0, "copy unterminated refuses");
    rc = ldso_sym_lookup(img, IMG_SZ, SYM_OFF, 2, STR_OFF, 15, "myfunc",
        &val);
    CHECK(rc == 1 && val == 0x1234, "lookup hit");
    CHECK(ldso_sym_lookup(img, IMG_SZ, SYM_OFF, 2, STR_OFF, 15, "nope",
        &val) == 0, "lookup miss");
    CHECK(ldso_rela_count(&info, &n) == 0 && n == 1, "rela count");
    CHECK(ldso_read_rela(img, IMG_SZ, RELA_OFF, 1, 0, 2, &row) == 0 &&
        row.offset == 0x600 && row.sym == 1 && row.type == 6,
        "rela glob_dat");
    CHECK(ldso_read_rela(img, IMG_SZ, RELA_OFF, 1, 0, 1, &row) != 0,
        "rela bad sym refuses");
    CHECK(ldso_read_rela(img, IMG_SZ, RELA_OFF, 1, 7, 2, &row) != 0,
        "rela bad idx refuses");

    build_tables(img, 8);
    CHECK(ldso_read_rela(img, IMG_SZ, RELA_OFF, 1, 0, 2, &row) == -2,
        "rela relative unsupported");

    img[SYM_OFF + 28] = 0x02;
    CHECK(ldso_sym_lookup(img, IMG_SZ, SYM_OFF, 2, STR_OFF, 15, "myfunc",
        &val) == 0, "lookup local skipped");
    img[SYM_OFF + 28] = 0x12;
    w16(img + SYM_OFF + 30, 0);
    CHECK(ldso_sym_lookup(img, IMG_SZ, SYM_OFF, 2, STR_OFF, 15, "myfunc",
        &val) == 0, "lookup undef skipped");
    w16(img + SYM_OFF + 30, 1);

    build_ehdr(img, 0);
    CHECK(ldso_find_dynamic(img, IMG_SZ, &off, &size) == 0,
        "static has no dynamic");
    img[0] = 0x7E;
    CHECK(ldso_find_dynamic(img, IMG_SZ, &off, &size) != 0,
        "bad magic refuses");
    CHECK(ldso_segments(img, IMG_SZ, segs, 4, &nseg) != 0,
        "bad ehdr segments refuse");

    ldso_basename(name, "a/b/libx.so");
    CHECK(strcmp(name, "libx.so") == 0, "basename strips dirs");
    ldso_basename(name, "plain.so");
    CHECK(strcmp(name, "plain.so") == 0, "basename keeps plain");
    ldso_basename(name, 0);
    CHECK(name[0] == '\0', "basename null safe");

    if (failures == 0) printf("ldso: all parse checks passed\n");
    return failures != 0;
}
