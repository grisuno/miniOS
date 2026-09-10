/* test_vma_bench.c -- RB-tree vs sorted-list benchmark (boyscout gap #9).
 *
 * Answers "is the RB-tree over-engineering for < 50 VMAs?" with numbers:
 * drives N=16/48/512 insert+find workloads through vma.c and through a
 * naive sorted array, printing microseconds per op for each. The tree is
 * kept for its O(log n) worst case; the MRU cache covers the O(1) hits.
 * Run: make test-vma-bench (informational, never fails the gate).
 */
#include <stdio.h>
#include <sys/time.h>
#include "vma.h"

static long now_us(void) {
    struct timeval tv;
    gettimeofday(&tv, 0);
    return (long)tv.tv_sec * 1000000L + tv.tv_usec;
}

/* naive sorted list over a static array */
#define LIST_MAX 4096
static unsigned long lb[LIST_MAX];
static int ln;
static void l_insert(unsigned long b) {
    int i = ln;
    while (i > 0 && lb[i-1] > b) { lb[i] = lb[i-1]; i--; }
    lb[i] = b; ln++;
}
static int l_find(unsigned long b) {
    int i;
    for (i = 0; i < ln; i++) if (lb[i] == b) return i;
    return -1;
}

static void bench(int n) {
    long t0, t1, t2, t3;
    int i;
    vma_tree_init();
    t0 = now_us();
    for (i = 0; i < n; i++)
        vma_tree_insert(&vma_live_root, 0x500000ul + (unsigned long)i * 0x1000, 0x1000);
    t1 = now_us();
    for (i = 0; i < n; i++)
        vma_tree_find(vma_live_root, 0x500000ul + (unsigned long)i * 0x1000);
    t2 = now_us();
    ln = 0;
    for (i = 0; i < n; i++) l_insert(0x500000ul + (unsigned long)i * 0x1000);
    for (i = 0; i < n; i++) l_find(0x500000ul + (unsigned long)i * 0x1000);
    t3 = now_us();
    if (printf("n=%d tree_insert=%.2fus/op tree_find=%.2fus/op list=%.2fus/op\n",
               n, (double)(t1-t0)/n, (double)(t2-t1)/n, (double)(t3-t2)/n) < 0)
        return;
}

int main(void) {
    bench(16); bench(48); bench(512);
    if (printf("vma-bench: ok (informational)\n") < 0) return 1;
    return 0;
}
