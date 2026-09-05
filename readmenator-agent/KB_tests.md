# Subsystem: tests

## tests/host_aes.sh
- Layer: testing
- Doc: host_aes.sh - host-side verification for the AES-256-CTR command tools.  The miniGCC-built tools are static Linux ELFs, 
- Language: sh
- Symbols:
  - `ok` (function, line 23)
  - `bad` (function, line 24)
  - `rd` (function, line 25)

## tests/host_codecs.sh
- Layer: testing
- Doc: host_codecs.sh - reusable host-side verification for the in-OS codec tools.  The miniGCC-compiled tools are static Linux
- Language: sh
- Symbols:
  - `ok` (function, line 22)
  - `bad` (function, line 23)
  - `gen_input` (function, line 27)
  - `roundtrip` (function, line 31)
  - `reject` (function, line 40)

## tests/test_sync.c
- Layer: testing
- Doc: Host-side unit test for the blocking sync primitives (kernel/sync.c).
- Language: c
- Symbols:
  - `proc_get` (function, line 23) `proc_t *proc_get(int pid)`
  - `schedule` (function, line 29) `void schedule(void)`
  - `fresh_proc` (function, line 43) `static void fresh_proc(int pid)`
  - `fresh_all` (function, line 51) `static void fresh_all(void)`
  - `main` (function, line 62) `int main(void)`
  - `CHECK` (macro, line 36)

## tests/test_vma.c
- Layer: testing
- Doc: Host-side unit test for the VMA red-black tree (vma.c).
- Language: c
- Symbols:
  - `black_height` (function, line 26) `static int black_height(const vma_node_t *n)`
  - `tree_valid` (function, line 37) `static int tree_valid(const vma_node_t *root)`
  - `count_nodes` (function, line 74) `static int count_nodes(const vma_node_t *root)`
  - `test_insert_find_delete` (function, line 88) `static void test_insert_find_delete(void)`
  - `test_pool_exhaustion` (function, line 135) `static void test_pool_exhaustion(void)`
  - `test_full_drain` (function, line 152) `static void test_full_drain(void)`
  - `main` (function, line 166) `int main(void)`
  - `CHECK` (macro, line 19)
