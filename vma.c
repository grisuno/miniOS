#include "vma.h"

/*
 * VMA red-black tree implementation.
 *
 * The tree is a client-style red-black tree with the sentinel nils
 * embedded in the same object space as the nodes.  Insertion, lookup and
 * deletion are all O(log n).  vma_alloc_node draws from a fixed pool; it
 * fails closed (returns VMA_NIL) once the pool is exhausted, so a hostile
 * or runaway mmap workload can never overrun the pool.
 */

vma_node_t vma_pool[VMA_MAX];
int        vma_pool_n;

static vma_node_t vma_nil_store;
vma_node_t *VMA_NIL;

vma_node_t *vma_live_root;
vma_node_t *vma_free_root;

void vma_tree_init(void) {
    VMA_NIL = &vma_nil_store;
    VMA_NIL->red = 0;
    VMA_NIL->left = VMA_NIL->right = VMA_NIL->parent = VMA_NIL;
    VMA_NIL->base = 0;
    VMA_NIL->len = 0;
    vma_live_root = VMA_NIL;
    vma_free_root = VMA_NIL;
    vma_pool_n = 0;
}

static vma_node_t *vma_alloc_node(void) {
    if (vma_pool_n >= VMA_MAX) return VMA_NIL;
    return &vma_pool[vma_pool_n++];
}

static void vma_rotate_left(vma_node_t **root, vma_node_t *x) {
    vma_node_t *y = x->right;
    x->right = y->left;
    if (y->left != VMA_NIL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == VMA_NIL) *root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

static void vma_rotate_right(vma_node_t **root, vma_node_t *x) {
    vma_node_t *y = x->left;
    x->left = y->right;
    if (y->right != VMA_NIL) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == VMA_NIL) *root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

static void vma_insert_fixup(vma_node_t **root, vma_node_t *z) {
    while (z->parent->red) {
        if (z->parent == z->parent->parent->left) {
            vma_node_t *y = z->parent->parent->right;
            if (y->red) {
                z->parent->red = 0;
                y->red = 0;
                z->parent->parent->red = 1;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    vma_rotate_left(root, z);
                }
                z->parent->red = 0;
                z->parent->parent->red = 1;
                vma_rotate_right(root, z->parent->parent);
            }
        } else {
            vma_node_t *y = z->parent->parent->left;
            if (y->red) {
                z->parent->red = 0;
                y->red = 0;
                z->parent->parent->red = 1;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    vma_rotate_right(root, z);
                }
                z->parent->red = 0;
                z->parent->parent->red = 1;
                vma_rotate_left(root, z->parent->parent);
            }
        }
    }
    (*root)->red = 0;
}

vma_node_t *vma_tree_insert(vma_node_t **root, unsigned long base, unsigned long len) {
    vma_node_t *z = vma_alloc_node();
    if (z == VMA_NIL) return VMA_NIL;
    z->base = base;
    z->len = len;
    z->left = z->right = z->parent = VMA_NIL;
    z->red = 1;

    vma_node_t *y = VMA_NIL;
    vma_node_t *x = *root;
    while (x != VMA_NIL) {
        y = x;
        if (z->base < x->base) x = x->left;
        else x = x->right;
    }
    z->parent = y;
    if (y == VMA_NIL) *root = z;
    else if (z->base < y->base) y->left = z;
    else y->right = z;
    vma_insert_fixup(root, z);
    return z;
}

vma_node_t *vma_tree_find(vma_node_t *root, unsigned long base) {
    vma_node_t *x = root;
    while (x != VMA_NIL) {
        if (base == x->base) return x;
        else if (base < x->base) x = x->left;
        else x = x->right;
    }
    return VMA_NIL;
}

static void vma_transplant(vma_node_t **root, vma_node_t *u, vma_node_t *v) {
    if (u->parent == VMA_NIL) *root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
}

static vma_node_t *vma_tree_minimum(vma_node_t *x) {
    while (x->left != VMA_NIL) x = x->left;
    return x;
}

static void vma_delete_fixup(vma_node_t **root, vma_node_t *x) {
    while (x != *root && !x->red) {
        if (x == x->parent->left) {
            vma_node_t *w = x->parent->right;
            if (w->red) {
                w->red = 0;
                x->parent->red = 1;
                vma_rotate_left(root, x->parent);
                w = x->parent->right;
            }
            if (!w->left->red && !w->right->red) {
                w->red = 1;
                x = x->parent;
            } else {
                if (!w->right->red) {
                    w->left->red = 0;
                    w->red = 1;
                    vma_rotate_right(root, w);
                    w = x->parent->right;
                }
                w->red = x->parent->red;
                x->parent->red = 0;
                w->right->red = 0;
                vma_rotate_left(root, x->parent);
                x = *root;
            }
        } else {
            vma_node_t *w = x->parent->left;
            if (w->red) {
                w->red = 0;
                x->parent->red = 1;
                vma_rotate_right(root, x->parent);
                w = x->parent->left;
            }
            if (!w->right->red && !w->left->red) {
                w->red = 1;
                x = x->parent;
            } else {
                if (!w->left->red) {
                    w->right->red = 0;
                    w->red = 1;
                    vma_rotate_left(root, w);
                    w = x->parent->left;
                }
                w->red = x->parent->red;
                x->parent->red = 0;
                w->left->red = 0;
                vma_rotate_right(root, x->parent);
                x = *root;
            }
        }
    }
    x->red = 0;
}

int vma_tree_delete(vma_node_t **root, unsigned long base) {
    vma_node_t *z = vma_tree_find(*root, base);
    if (z == VMA_NIL) return -1;
    vma_node_t *y = z;
    vma_node_t *x;
    int y_orig_red = y->red;
    if (z->left == VMA_NIL) {
        x = z->right;
        vma_transplant(root, z, z->right);
    } else if (z->right == VMA_NIL) {
        x = z->left;
        vma_transplant(root, z, z->left);
    } else {
        y = vma_tree_minimum(z->right);
        y_orig_red = y->red;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            vma_transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        vma_transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->red = z->red;
    }
    if (!y_orig_red) vma_delete_fixup(root, x);
    return 0;
}