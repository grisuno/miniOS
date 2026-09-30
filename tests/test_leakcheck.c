/** Docstring: host test for the leak tracker (make test-leakcheck).
 *
 * Pins headers/leakcheck.h with the override macros active, exactly as
 * file and vedit compile it: every malloc/free/realloc in this unit is
 * tracked, the live set must drain back to its entry baseline, and the
 * dump path runs without faulting. The fassoc cycle proves a real MiniOS
 * structure (the file browser association table) leaves nothing behind.
 */

#define MINIOS_LEAKCHECK_IMPL
#define MINIOS_LK_ENABLE
#include "leakcheck.h"

#include <stdio.h>
#include <string.h>
#include "progs/file/file_assoc.h"

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

int main(void) {
    unsigned long base_count;
    unsigned long base_bytes;
    void *p;
    void *q;
    struct fassoc_table t;
    printf("leakcheck: warmup\n");
    fflush(stdout);
    base_count = lk_live_count();
    base_bytes = lk_live_bytes();
    p = malloc(64);
    CHECK(p != 0, "tracked malloc succeeds");
    CHECK(lk_live_count() == base_count + 1, "malloc joins the live set");
    CHECK(lk_live_bytes() == base_bytes + 64, "malloc counts its bytes");
    q = realloc(p, 128);
    CHECK(q != 0, "tracked realloc succeeds");
    CHECK(lk_live_count() == base_count + 1, "realloc keeps one record");
    free(q);
    CHECK(lk_live_count() == base_count, "free drains the record");
    CHECK(lk_live_bytes() == base_bytes, "free drains the bytes");
    p = malloc(32);
    q = malloc(32);
    free(p);
    free(q);
    CHECK(lk_live_count() == base_count, "paired traffic nets zero");
    p = malloc(0);
    free(p);
    CHECK(lk_live_count() == base_count, "zero-size round trips clean");
    p = malloc(16);
    q = realloc(p, 0);
    CHECK(q == 0, "realloc to zero frees");
    CHECK(lk_live_count() == base_count, "realloc-zero drains");
    memset(&t, 0, sizeof(t));
    CHECK(fassoc_push(&t, "c", "/vedit") == 0, "assoc push works tracked");
    CHECK(fassoc_push(&t, "elf", "shell") == 0, "assoc push works tracked");
    CHECK(fassoc_push(&t, "png", "internal") == 0, "assoc push works tracked");
    CHECK(lk_live_count() == base_count + 1, "assoc table holds one block");
    fassoc_clear(&t);
    CHECK(lk_live_count() == base_count + 1, "clear keeps capacity live");
    CHECK(fassoc_count(&t) == 0, "clear empties the count");
    CHECK(strcmp(fassoc_lookup(&t, "c"), "") == 0, "clear hides entries");
    fassoc_free(&t);
    CHECK(lk_live_count() == base_count, "assoc free drains the table");
    CHECK(lk_live_bytes() == base_bytes, "assoc free drains the bytes");
    lk_dumpmem();
    if (lk_live_count() != base_count) {
        failures++;
        fprintf(stderr, "FAIL: live set did not drain\n");
    }
    if (failures == 0) printf("leakcheck: ok\n");
    return failures != 0;
}
