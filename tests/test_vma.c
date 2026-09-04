/* Host-side unit test for the VMA red-black tree (vma.c).
 *
 * The tree is integer-only and free of kernel dependencies, so it is
 * exercised directly here against the host libc.  The test verifies the
 * observable contract (insert/find/delete, in-order uniqueness, pool
 * exhaustion) and, independently, the red-black invariants, so a mutant
 * that breaks a rotation or a fixup is caught even when the plain
 * roundtrip still looks correct.
 *
 * Run through `make test-vma`.
 */

#include <stdio.h>
#include <stdlib.h>

#include "vma.h"

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

static int black_height(const vma_node_t *n) {
    int left, right, add;
    if (n == VMA_NIL) return 1;
    if (!n->red) add = 1; else add = 0;
    left  = black_height(n->left);
    right = black_height(n->right);
    if (left == -1 || right == -1) return -1;
    if (left != right) return -1;
    return left + add;
}

static int tree_valid(const vma_node_t *root) {
    const vma_node_t *n;
    if (root == VMA_NIL) return 1;
    if (root->red) return 0;
    if (root->parent != VMA_NIL) return 0;
    if (black_height(root) == -1) return 0;

    /* Walk the tree with an explicit stack, checking BST order, the
     * no-double-red property and parent pointer consistency. */
    const vma_node_t *stack[65536];
    int sp = 0;
    int seq = 0;
    unsigned long prev = 0;
    int seen = 0;
    n = root;
    while (n != VMA_NIL || sp > 0) {
        while (n != VMA_NIL) {
            if (sp >= 65536) return 0;
            stack[sp++] = n;
            n = n->left;
        }
        n = stack[--sp];
        if (seen && n->base <= prev) return 0;
        prev = n->base;
        seen = 1;
        seq++;
        if (n->red) {
            if (n->left != VMA_NIL && n->left->red) return 0;
            if (n->right != VMA_NIL && n->right->red) return 0;
        }
        if (n->left != VMA_NIL && n->left->parent != n) return 0;
        if (n->right != VMA_NIL && n->right->parent != n) return 0;
        n = n->right;
    }
    return 1;
}

static int count_nodes(const vma_node_t *root) {
    const vma_node_t *stack[65536];
    int sp = 0;
    int cnt = 0;
    const vma_node_t *n = root;
    while (n != VMA_NIL || sp > 0) {
        while (n != VMA_NIL) { stack[sp++] = n; n = n->left; }
        n = stack[--sp];
        cnt++;
        n = n->right;
    }
    return cnt;
}

static void test_insert_find_delete(void) {
    int i;
    const int N = 2000;
    vma_node_t *node;

    vma_tree_init();

    for (i = 0; i < N; i++) {
        unsigned long base = (unsigned long)i * 0x1000;
        node = vma_tree_insert(&vma_live_root, base, 0x1000);
        CHECK(node != VMA_NIL, "insert returned nil within pool capacity");
        CHECK(vma_live_root != VMA_NIL, "live root must be non-nil after insert");
    }
    CHECK(tree_valid(vma_live_root), "red-black invariants after inserts");
    CHECK(count_nodes(vma_live_root) == N, "node count after inserts");

    for (i = 0; i < N; i++) {
        unsigned long base = (unsigned long)i * 0x1000;
        node = vma_tree_find(vma_live_root, base);
        CHECK(node != VMA_NIL, "find must locate every inserted base");
        CHECK(node->base == base, "find returns the matching node");
        CHECK(node->len == 0x1000, "find returns the matching length");
    }

    CHECK(vma_tree_find(vma_live_root, 0xDEAD0000UL) == VMA_NIL,
          "find nonexistent base returns nil");

    /* Delete every third node in reverse order. */
    for (i = N - 1; i >= 0; i -= 3) {
        unsigned long base = (unsigned long)i * 0x1000;
        CHECK(vma_tree_delete(&vma_live_root, base) == 0, "delete existing returns 0");
        CHECK(tree_valid(vma_live_root), "red-black invariants preserved during deletes");
    }
    CHECK(vma_tree_delete(&vma_live_root, 0xDEAD0000UL) == -1,
          "delete nonexistent returns -1");

    for (i = 0; i < N; i++) {
        unsigned long base = (unsigned long)i * 0x1000;
        node = vma_tree_find(vma_live_root, base);
        if (i % 3 != 1) {
            CHECK(node != VMA_NIL, "undeleted base still present");
        } else {
            CHECK(node == VMA_NIL, "deleted base must be gone");
        }
    }
}

static void test_pool_exhaustion(void) {
    int i;
    vma_node_t *node;

    vma_tree_init();
    for (i = 0; i < VMA_MAX; i++) {
        node = vma_tree_insert(&vma_live_root, (unsigned long)(i + 1) * 0x1000, 0x1000);
        CHECK(node != VMA_NIL, "insert succeeds up to pool capacity");
    }
    CHECK(count_nodes(vma_live_root) == VMA_MAX, "pool fully populated");

    node = vma_tree_insert(&vma_live_root, 0x10000000UL, 0x1000);
    CHECK(node == VMA_NIL, "insert beyond capacity fails closed");
    CHECK(count_nodes(vma_live_root) == VMA_MAX, "failed insert leaves tree unchanged");
    CHECK(tree_valid(vma_live_root), "red-black invariants at exhaustion");
}

static void test_full_drain(void) {
    int i;
    vma_tree_init();
    for (i = 0; i < 256; i++) {
        vma_tree_insert(&vma_live_root, (unsigned long)i * 0x1000, 0x1000);
    }
    for (i = 0; i < 256; i++) {
        CHECK(vma_tree_delete(&vma_live_root, (unsigned long)i * 0x1000) == 0,
              "draining delete returns 0");
    }
    CHECK(vma_live_root == VMA_NIL, "tree is empty after full drain");
    CHECK(tree_valid(vma_live_root), "empty tree is valid");
}

int main(void) {
    test_insert_find_delete();
    test_pool_exhaustion();
    test_full_drain();

    if (failures) {
        fprintf(stderr, "test_vma: %d failure(s)\n", failures);
        return 1;
    }
    printf("vma: ok\n");
    return 0;
}