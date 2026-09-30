/** Docstring: host test for the bump arena (make test-arena).
 *
 * Pins headers/arena.h without any kernel boot: borrow alignment,
 * exhaustion, checkpoint and rewind, reset reuse, overflow-closed sizing
 * and the single-backing-block scope pattern that spawn argv copies use.
 */

#include <stdio.h>
#include <string.h>
#include "arena.h"

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

static unsigned char scope[4096];

int main(void) {
    arena_t a;
    void *p;
    void *q;
    size_t ck;
    arena_init(&a, scope, sizeof(scope));
    CHECK(arena_used(&a) == 0, "fresh arena uses nothing");
    CHECK(arena_free_bytes(&a) == sizeof(scope), "fresh arena frees all");
    p = arena_alloc(&a, 16, 8);
    CHECK(p != 0, "first borrow succeeds");
    CHECK(((size_t)p & 7u) == 0, "borrow honors alignment");
    CHECK(arena_used(&a) == 16, "used counts the borrow");
    q = arena_alloc(&a, 3, 16);
    CHECK(q != 0, "second borrow succeeds");
    CHECK(((size_t)q & 15u) == 0, "borrow honors wider alignment");
    ck = arena_checkpoint(&a);
    p = arena_alloc(&a, 64, 0);
    CHECK(p != 0, "zero align falls back to default");
    CHECK(arena_rewind(&a, ck) == 0, "rewind to checkpoint works");
    CHECK(arena_used(&a) == ck, "rewind releases the tail");
    CHECK(arena_rewind(&a, ck + 1) != 0, "forward rewind refuses");
    CHECK(arena_rewind(&a, sizeof(scope) + 1) != 0, "wild rewind refuses");
    CHECK(arena_alloc(&a, sizeof(scope), 1) == 0, "oversize borrow fails");
    CHECK(arena_alloc(&a, 0, 8) == 0, "zero borrow fails closed");
    CHECK(arena_alloc(&a, 8, 3) == 0, "non-power-of-two align fails");
    CHECK(arena_bytes_for(4, 8) == 32, "bytes_for multiplies");
    CHECK(arena_bytes_for((size_t)-1, 2) == 0, "bytes_for overflow closes");
    CHECK(arena_bytes_for(0, 8) == 0, "bytes_for zero closes");
    CHECK(arena_align_up(5, 8) == 8, "align_up rounds");
    CHECK(arena_align_up(16, 8) == 16, "align_up keeps aligned");
    CHECK(arena_align_up(1, 3) == 0, "align_up rejects odd align");
    arena_reset(&a);
    CHECK(arena_used(&a) == 0, "reset empties the scope");
    CHECK(arena_free_bytes(&a) == sizeof(scope), "reset frees the block");
    p = arena_alloc(&a, sizeof(scope), 1);
    CHECK(p == scope, "reset block borrows whole");
    CHECK(arena_alloc(&a, 1, 1) == 0, "full arena refuses");
    CHECK(arena_contains(&a, scope) != 0, "contains sees the base");
    CHECK(arena_contains(&a, scope + sizeof(scope)) == 0, "contains rejects end");
    CHECK(arena_contains(&a, 0) == 0, "contains rejects null");
    {
        arena_t empty;
        arena_init(&empty, 0, 0);
        CHECK(arena_alloc(&empty, 8, 8) == 0, "empty arena refuses");
        CHECK(arena_used(&empty) == 0, "empty arena uses nothing");
    }
    {
        char *argv[3];
        const char *words[2] = {"ab", "cdef"};
        size_t need = arena_bytes_for(3, sizeof(char *));
        size_t k;
        arena_t b;
        unsigned char *back;
        need += 3 + 5;
        back = scope;
        arena_init(&b, back, need);
        memcpy(argv, words, sizeof(words));
        for (k = 0; k < 2; k++) {
            size_t n = strlen(words[k]) + 1;
            char *dst = arena_alloc(&b, n, 1);
            CHECK(dst != 0, "scope borrow succeeds");
            if (dst) {
                memcpy(dst, words[k], n);
                argv[k] = dst;
            }
        }
        argv[2] = 0;
        CHECK(strcmp(argv[0], "ab") == 0, "scoped argv keeps words");
        CHECK(strcmp(argv[1], "cdef") == 0, "scoped argv keeps words");
    }
    if (failures == 0) printf("arena: ok\n");
    return failures != 0;
}
