/** Docstring: host test for the page cache store (make test-pcache).
 *
 * Stubs the kernel surface fs/pcache.c names (heap, print) and pins
 * the slice-1 contract with no guest boot: miss reserves empty with
 * is_new, hits bump refs, put floors at zero, a full pinned pool
 * refuses, eviction reuses the oldest unpinned slot, invalidate
 * drops one inode and keeps the rest, dirty accounting flows to
 * stats, and every bad argument fails closed. Slice 2 wires the
 * fault path to this exact behavior; slice 3 exposes generations.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kernel.h"
#include "pcache.h"

void *kmalloc(unsigned long size) {
    return malloc(size ? size : 1);
}

void kfree(void *ptr) {
    free(ptr);
}

int kprintf(const char *fmt, ...) {
    (void)fmt;
    return 0;
}

#include "fs/pcache.c"

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

int main(void) {
    int is_new = 0;
    int s0;
    int s1;
    int i;
    unsigned long pages = 0;
    unsigned long hits = 0;
    unsigned long miss = 0;
    unsigned long evicted = 0;
    unsigned long dirty = 0;
    pcache_init();
    CHECK(pcache_lookup(7, 0) < 0, "empty lookup misses");
    CHECK(pcache_get(-1, 0, &is_new) < 0, "negative ino refuses");
    CHECK(pcache_data(-1) == 0, "bad slot data is null");
    pcache_put(-1);
    pcache_mark_dirty(-1);
    s0 = pcache_get(7, 0, &is_new);
    CHECK(s0 >= 0 && is_new == 1, "miss reserves with is_new");
    CHECK(((unsigned long)pcache_data(s0) & 0xFFFUL) == 0,
          "slot bodies are page-aligned for mapping");
    CHECK(pcache_lookup(7, 0) == s0, "lookup finds reserved");
    CHECK(pcache_lookup(7, 1) < 0, "other index misses");
    CHECK(pcache_lookup(8, 0) < 0, "other ino misses");
    memset(pcache_data(s0), 0xA5, PCACHE_PAGE);
    s1 = pcache_get(7, 0, &is_new);
    CHECK(s1 == s0 && is_new == 0, "hit reuses without is_new");
    CHECK(((unsigned char *)pcache_data(s0))[0] == 0xA5, "data persists");
    pcache_put(s0);
    pcache_put(s1);
    pcache_put(s1);
    CHECK(pcache_lookup(7, 0) == s0, "refs floor at zero, slot stays");
    pcache_mark_dirty(s0);
    pcache_stats(&pages, &hits, &miss, &evicted, &dirty);
    CHECK(pages == 1 && dirty == 1, "stats count live and dirty");
    CHECK(hits >= 1 && miss >= 1, "stats count hits and misses");
    pcache_invalidate_ino(7);
    CHECK(pcache_lookup(7, 0) < 0, "invalidate drops the ino");
    pcache_stats(&pages, 0, 0, 0, &dirty);
    CHECK(pages == 0 && dirty == 0, "invalidate clears stats");
    CHECK(pcache_ref(7, 0) < 0, "ref on dropped page fails");
    s0 = pcache_get(11, 3, &is_new);
    CHECK(s0 >= 0, "reserve for ref test");
    pcache_put(s0);
    CHECK(pcache_ref(11, 3) >= 0, "ref pins without allocating");
    pcache_put(s0);
    pcache_put(s0);
    CHECK(pcache_lookup(11, 3) == s0, "double put floors, slot stays");
    pcache_unmap(11, 3);
    pcache_unmap(11, 99);
    CHECK(pcache_lookup(11, 3) == s0, "unmap drops one ref only");
    pcache_invalidate_ino(11);
    {
        unsigned char page[PCACHE_PAGE];
        unsigned char *body;
        int sa;
        int sb;
        memset(page, 0x5A, sizeof(page));
        sa = pcache_publish(21, 0, page);
        CHECK(sa >= 0, "publish reserves and fills");
        body = pcache_data(sa);
        CHECK(body && body[0] == 0x5A && body[4095] == 0x5A,
              "published bytes are complete");
        sb = pcache_publish(21, 0, page);
        CHECK(sb == sa, "republish hits the live slot");
        pcache_put(sa);
        pcache_put(sb);
        CHECK(pcache_put_if(21, 0, 0xDEADUL) == 0, "put_if refuses alien phys");
        CHECK(pcache_ref_if(21, 0, 0xDEADUL) < 0, "ref_if refuses alien phys");
        CHECK(pcache_put_if(21, 0, (unsigned long)body) == 1,
              "put_if drops on phys match");
        CHECK(pcache_ref_if(21, 0, (unsigned long)body) == sa,
              "ref_if pins on phys match");
        pcache_put(sa);
        CHECK(pcache_publish(-1, 0, page) < 0, "publish refuses bad ino");
        CHECK(pcache_publish(21, 1, 0) < 0, "publish refuses null data");
        pcache_invalidate_ino(21);
    }
    {
        int first = -1;
        for (i = 0; i < PCACHE_PAGES; i++) {
            int s = pcache_get(1000 + i, 0, 0);
            CHECK(s >= 0, "pool fills to capacity");
            if (i == 0) first = s;
        }
        CHECK(pcache_get(4242, 0, 0) < 0, "full pinned pool refuses");
        pcache_put(first);
        {
            int s = pcache_get(5000, 0, &is_new);
            CHECK(s == first && is_new == 1, "evict reuses unpinned slot");
        }
    }
    pcache_stats(0, 0, 0, &evicted, 0);
    CHECK(evicted >= 1, "eviction counted");
    pcache_invalidate_ino(5000);
    s0 = pcache_get(9, 0, &is_new);
    CHECK(s0 >= 0, "get after invalidate works");
    pcache_put(s0);
    if (failures == 0) printf("pcache: ok\n");
    return failures != 0;
}
