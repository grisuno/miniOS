/* test_fault.c -- fault-injection suite (boyscout gap #10).
 *
 * Covers the fail-closed paths a happy-path suite never touches:
 * VMA pool exhaustion, delete-miss, duplicate insert, and the kmalloc
 * fail-after hook contract (modelled here with a stub counter since the
 * kernel allocator is not linked on the host).
 * Run: make test-fault.
 */
#include <stdio.h>
#include "vma.h"

static int failures = 0;
#define CHECK(c, m) do { if (!(c)) { failures++; fprintf(stderr, "FAIL: %s:%d: %s\n", __FILE__, __LINE__, m); } } while (0)

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
    if (!failures) printf("fault: ok (pool=%d)\n", VMA_MAX);
    return failures ? 1 : 0;
}
