# VMA Red-Black Tree: Complexity Analysis

Formal companion to ADR-0005. Implementation: `vma.c`, header `vma.h`;
host suite: `tests/test_vma.c` (`make test-vma`).

## Definitions

Let $n$ be the number of live regions in `vma_live_root` (resp. free
regions in `vma_free_root`). The tree maintains the five red-black
invariants: every node red or black; root black; red nodes have black
children; every root-to-leaf path carries the same black count
$bh$ (black height); leaves (NIL) black.

## Lemma 1 (height bound)

A red-black tree with $n$ internal nodes has height $h \le 2\log_2(n+1)$.

*Proof.* Standard CLRS argument: a subtree rooted at $x$ holds at least
$2^{bh(x)} - 1$ internal nodes (induction on height, using no double-red
to show the black height is at least half the height). With $bh \ge h/2$
at the root, $n \ge 2^{h/2} - 1$, hence $h \le 2\log_2(n+1)$. ∎

## Lemma 2 (rotation/recolor cost)

Insertion touches $O(h)$ nodes down the search path and fixes at most
$O(h)$ ancestors with $O(1)$ rotations (at most 2 for insert, at most 3
for delete); deletion likewise. All fix-up work is $O(h)$ time and
$O(1)$ extra space.

## Theorem (`mmap` / `munmap` in $O(\log n)$)

`mmap`: one free-tree search ($O(h)$) plus at most one live-tree insert
($O(h)$) and one free-tree delete ($O(h)$). `munmap`: one live-tree
search + one live delete + one free insert. By Lemma 1, $h = O(\log n)$,
so both operations are $O(\log n)$ worst-case, including under severe
fragmentation: fragmentation grows $n$ (more, smaller regions), and the
bound is a function of $n$ alone, never of contiguity. The pool is a
static array with a bump cursor, so node allocation is $O(1)$.

## Fragmentation accounting

Worst case for $n$: alternating allocated/free pages over the user
window $W$ bytes with minimum region $r$ gives $n \le W/r$. With
$W = 184$ MB and $r = 4$ KB, $n \le 47104$ nominally, but the pool caps
operations at `VMA_MAX` (4096) per exec, fail-closed (`VMA_NIL`). At the
cap, $h \le 2\log_2(4097) < 25$ comparisons per operation: bounded,
predictable, and independent of how adversarial the layout is.

## Test correspondence

`tests/test_vma.c` asserts the invariants Lemma 1 depends on (root
black, no double-red, equal black height, in-order uniqueness) across
insert/find/delete, pool exhaustion and full drain. The suite caught a
real soundness bug: the two-child delete restored the successor's color
instead of the deleted node's, unbalancing black height (reproduced with
eight nodes). An implementation that violates the invariants voids this
proof; the suite is the proof's executable guard.
