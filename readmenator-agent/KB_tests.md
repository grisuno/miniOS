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

## tests/test_batch.c
- Layer: testing
- Doc: Docstring: Host test for kernel/batch.c (make test-batch).
- Language: c
- Symbols:
  - `stub_dispatch` (function, line 23) `static long stub_dispatch(uint32_t opcode)`
  - `main` (function, line 30) `int main(void)`
  - `CHECK` (macro, line 16)

## tests/test_futex.c
- Layer: testing
- Doc: Docstring: Host test for kernel/futex.c (make test-futex).
- Language: c
- Symbols:
  - `proc_get` (function, line 17) `proc_t *proc_get(int pid)`
  - `schedule` (function, line 25) `void schedule(void)`
  - `fresh_proc` (function, line 38) `static void fresh_proc(int pid)`
  - `fresh_all` (function, line 47) `static void fresh_all(void)`
  - `main` (function, line 59) `int main(void)`
  - `CHECK` (macro, line 31)

## tests/test_hal_io.c
- Layer: testing
- Doc: Docstring: Host test for arch/x86/hal_io.h (make test-hal).
- Language: c
- Symbols:
  - `main` (function, line 29) `int main(void)`
  - `HAL_IO_HOST_TEST` (macro, line 10)
  - `CHECK` (macro, line 22)

## tests/test_percpu_rq.c
- Layer: testing
- Doc: Docstring: Host test for kernel/percpu_rq.c (make test-percpu-rq).
- Language: c
- Symbols:
  - `main` (function, line 23) `int main(void)`
  - `CHECK` (macro, line 16)

## tests/test_rcu.c
- Layer: testing
- Doc: Docstring: Host test for kernel/rcu.c (make test-rcu).
- Language: c
- Symbols:
  - `rcu_host_cpu` (function, line 18) `cpu_t *rcu_host_cpu(void)`
  - `test_cb` (function, line 22) `static void test_cb(void *arg)`
  - `main` (function, line 36) `int main(void)`
  - `CHECK` (macro, line 29)

## tests/test_sanitize.c
- Layer: testing
- Doc: Docstring: Host test for sanitize.h (make test-sanitize).
- Language: c
- Symbols:
  - `user_range_ok` (function, line 19) `int user_range_ok(unsigned long p, unsigned long len)`
  - `user_str_ok` (function, line 25) `int user_str_ok(unsigned long p, unsigned long maxlen)`
  - `kmemcpy` (function, line 31) `void *kmemcpy(void *dst, const void *src, unsigned long n)`
  - `range_probe` (function, line 47) `static long range_probe(unsigned long p, long len)`
  - `str_probe` (function, line 53) `static long str_probe(unsigned long p)`
  - `copy_probe` (function, line 60) `static long copy_probe(unsigned long uptr, long count, unsigned long elemsz)`
  - `main` (function, line 66) `int main(void)`
  - `EFAULT` (macro, line 12)
  - `CHECK` (macro, line 40)

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

## tests/test_tick.c
- Layer: testing
- Doc: Docstring: Host test for kernel/tick.c (make test-tick).
- Language: c
- Symbols:
  - `rec_a` (function, line 23) `static void rec_a(void *ctx)`
  - `rec_b` (function, line 30) `static void rec_b(void *ctx)`
  - `rec_d` (function, line 37) `static void rec_d(void *ctx)`
  - `dummy` (function, line 46) `static void dummy(void *ctx)`
  - `main` (function, line 51) `int main(void)`
  - `CHECK` (macro, line 16)

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
