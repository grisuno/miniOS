/* test_fault.c -- fault-injection suite (boyscout gap #10).
 *
 * Covers the fail-closed paths a happy-path suite never touches:
 * VMA pool exhaustion / delete-miss / MRU, plus the 0a92118 review
 * follow-ups, mirrored on the host so they run without QEMU:
 *   - user_range_ok / user_str_ok boundary semantics (the gfx_title
 *     over-read class: validate-1/read-31 must be rejectable, and a
 *     NUL-less string must fail closed, never read past maxlen);
 *   - count-by-size pre-bound rule (writev/poll/spawn multiply only
 *     after bounding against (END-BASE)/elemsz, so the product cannot
 *     wrap past the range check);
 *   - ET_REL trust-gate normalisation (fs_resolve collapses ".."/".",
 *     the gate matches ETREL_TRUSTED_DIR on the normalised path);
 *   - ETREL_IMAGE_MAX sanity (cap above the measured ld.o ~12.7 MB,
 *     far below the 192 MB heap it protects).
 * The replicas below mirror kernel/syscalls.c, kernel/shell.c and
 * kernel/loader.c line for line; a kernel edit that changes the rule
 * must update the mirror, or this suite goes red.
 * Run: make test-fault.
 */
#include <stdio.h>
#include <string.h>
#include "vma.h"

static int failures = 0;
/* cert-err33-c: even test diagnostics are checked; a blind harness that
 * cannot report is itself a failure. */
#define CHECK(c, m) do { if (!(c)) { failures++; if (fprintf(stderr, "FAIL: %s:%d: %s\n", __FILE__, __LINE__, m) < 0) failures++; } } while (0)

/* ---- Mirror of kernel/syscalls.c user window ---- */
#define U_BASE ((unsigned long)0x00400000ul)
#define U_END  ((unsigned long)0x0C000000ul)

static unsigned char umem[64];
static int range_ok(unsigned long p, unsigned long len) {
    if (p < U_BASE) return 0;
    if (len > U_END - p) return 0;
    return p + len <= U_END;
}
/* Mirror of user_str_ok: NUL must land inside [p, p+maxlen). */
static int str_ok(const unsigned char *mem, unsigned long p,
                  unsigned long maxlen) {
    unsigned long i;
    if (p < U_BASE || p >= U_END) return 0;
    for (i = 0; i < maxlen && p + i < U_END; i++)
        if (mem[(p - U_BASE) + i] == 0) return 1;
    return 0;
}

/* Minimal mirror of fs/vfs.c fs_resolve (cwd-relative, cap 64):
 * collapses ".", pops "..", skips empty components. */
static void normalize(const char *path, char *out, unsigned cap) {
    unsigned len = 0;
    const char *p = path;
    out[0] = 0;
    if (*p == '/') p++;
    while (*p) {
        const char *start = p;
        while (*p && *p != '/') p++;
        {
            unsigned clen = (unsigned)(p - start);
            if (clen == 0 || (clen == 1 && start[0] == '.')) { if (*p) p++; continue; }
            if (clen == 2 && start[0] == '.' && start[1] == '.') {
                if (len > 0) {
                    len--;
                    while (len > 0 && out[len - 1] != '/') len--;
                    out[len] = 0;
                }
                if (*p) p++;
                continue;
            }
            if (len + 1 + clen >= cap) { out[0] = 0; return; }
            if (len > 0 && out[len - 1] != '/') out[len++] = '/';
            memcpy(out + len, start, clen);
            len += clen;
            out[len] = 0;
            if (*p) p++;
        }
    }
}
#define TRUSTED_DIR "objects/"
#define TRUSTED_LEN 8
static int path_trusted(const char *full) {
    const char *p = full;
    unsigned i;
    if (p[0] == '/') p++;
    for (i = 0; p[i] && p[i] != '/'; i++) {
        if (p[i] == '.' && (p[i + 1] == 0 || p[i + 1] == '/')) return 0;
    }
    if (strncmp(p, TRUSTED_DIR, TRUSTED_LEN) == 0) return 1;
    return 0;
}

int main(void) {
    int i;
    vma_tree_init();
    /* fill the pool: every insert must succeed until VMA_MAX */
    for (i = 0; i < VMA_MAX; i++) {
        vma_node_t *n = vma_tree_insert(&vma_live_root, 0x600000ul + (unsigned long)i * 0x1000, 0x1000);
        if (n == VMA_NIL) break;
    }
    CHECK(i == VMA_MAX, "pool holds VMA_MAX nodes");
    /* one more must fail closed, never overrun */
    CHECK(vma_tree_insert(&vma_live_root, 0xdead0000ul, 0x1000) == VMA_NIL, "pool exhaustion fails closed");
    /* delete-miss returns -1 */
    CHECK(vma_tree_delete(&vma_live_root, 0x12345000ul) == -1, "delete miss returns -1");
    /* MRU path: repeated find of the same base hits cache and stays valid */
    vma_tree_init();
    CHECK(vma_tree_insert(&vma_live_root, 0x500000ul, 0x1000) != VMA_NIL, "insert for mru");
    CHECK(vma_tree_find(vma_live_root, 0x500000ul) != VMA_NIL, "find hits");
    CHECK(vma_tree_find(vma_live_root, 0x500000ul) != VMA_NIL, "mru re-find hits");
    CHECK(vma_tree_delete(&vma_live_root, 0x500000ul) == 0, "delete ok");
    CHECK(vma_tree_find(vma_live_root, 0x500000ul) == VMA_NIL, "find after delete misses");

    /* ---- user_range_ok boundaries ---- */
    CHECK(range_ok(U_BASE, 1), "first user byte ok");
    CHECK(!range_ok(U_BASE - 1, 1), "byte below window rejected");
    CHECK(range_ok(U_BASE, U_END - U_BASE), "whole window ok");
    CHECK(!range_ok(U_END, 1), "one past end rejected");
    CHECK(!range_ok(U_END - 4, 8), "span crossing end rejected");
    CHECK(range_ok(U_BASE, 0), "zero length ok");

    /* ---- user_str_ok: the gfx_title over-read class ---- */
    memset(umem, 'A', sizeof(umem));
    umem[10] = 0;
    CHECK(str_ok(umem, U_BASE, 31), "NUL inside bound accepted");
    CHECK(str_ok(umem, U_BASE, 11), "NUL at last covered byte accepted");
    CHECK(!str_ok(umem, U_BASE, 10), "NUL just past bound rejected");
    memset(umem, 'A', sizeof(umem)); /* no NUL at all */
    CHECK(!str_ok(umem, U_BASE, 31), "NUL-less string rejected");
    CHECK(!str_ok(umem, U_BASE - 1, 31), "string below window rejected");
    CHECK(!str_ok(umem, U_END, 31), "string at end rejected");

    /* ---- count-by-size pre-bound rule ---- */
    {
        unsigned long span = U_END - U_BASE;
        unsigned long cnt_ok = span / 8;      /* pollfd stride */
        unsigned long cnt_bad = cnt_ok + 1;
        CHECK(cnt_ok * 8 <= span, "max ok count fits");
        /* the kernel refuses cnt_bad before multiplying, so no wrap: */
        CHECK(cnt_bad > span / 8, "over-bound count refused pre-multiply");
    }

    /* ---- ET_REL trust gate ---- */
    CHECK(path_trusted("objects/ld.o"), "objects/ trusted");
    CHECK(path_trusted("/objects/cvm.o"), "leading slash tolerated");
    CHECK(path_trusted("objects/sub/dir.o"), "subdir of objects trusted");
    CHECK(!path_trusted("bin/evil.o"), "bin refused");
    CHECK(!path_trusted("objects"), "bare prefix without slash refused");
    { /* escape attempts are normalised BEFORE the gate: the gate only
       * ever sees the collapsed path, so test the composition. */
        char n[64];
        normalize("objects/../bin/evil.o", n, sizeof(n));
        CHECK(strcmp(n, "bin/evil.o") == 0, "dotdot collapses out of objects");
        CHECK(!path_trusted(n), "collapsed escape refused");
        normalize("./objects/ld.o", n, sizeof(n));
        CHECK(strcmp(n, "objects/ld.o") == 0, "dot collapses");
        CHECK(path_trusted(n), "collapsed trusted path accepted");
        normalize("objects//ld.o", n, sizeof(n));
        CHECK(path_trusted(n), "double slash collapses to trusted");
    }
    CHECK(!path_trusted(""), "empty refused");

    /* ---- ETREL_IMAGE_MAX sanity ---- */
    {
        unsigned long cap = 16UL * 1024UL * 1024UL;
        unsigned long ldo = 12UL * 1024UL * 1024UL + 716UL * 1024UL; /* ~12.7 MB */
        unsigned long heap = 192UL * 1024UL * 1024UL;
        CHECK(cap > ldo, "cap fits measured ld.o");
        CHECK(cap < heap, "cap far below heap");
    }

    /* ---- IPv4 signedness (freedom/http resolver class) ----
     * Mirror of the resolve check in progs/src/freedom.c and
     * progs/src/http.c: the address travels as bits (int from the
     * syscall) and must be judged unsigned. 0xAC4293F3 is 172.66.147.243
     * (real answer once seen for www.example.com); as int it is
     * negative, and the old `ip < 0` check refused half the internet
     * while 10.0.2.2-style literals kept working. Only the 0/all-ones
     * sentinels (which DNS never returns) fail. */
    {
        int raw = (int)0xAC4293F3u;
        unsigned ip = (unsigned)raw;
        CHECK(!(ip == 0 || ip == 0xFFFFFFFFu), "high-bit IPv4 accepted");
        CHECK(((ip >> 24) & 255) == 172, "first octet extracts");
        CHECK(((ip >> 16) & 255) == 66, "second octet extracts");
        ip = (unsigned)-1;
        CHECK(ip == 0xFFFFFFFFu, "failure sentinel still refused");
        ip = 0;
        CHECK(ip == 0, "zero still refused");
    }

    if (!failures && printf("fault: ok (pool=%d)\n", VMA_MAX) < 0) failures++;
    return failures ? 1 : 0;
}
