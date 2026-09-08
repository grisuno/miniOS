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
  - `fprintf` (function, line 20) `fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__);`
  - `CHECK` (function, line 45) `CHECK(r == BATCH_OK, "clean batch returns OK");`
  - `printf` (function, line 100) `else printf("batch: %d failures\n", failures);`
  - `CHECK` (macro, line 16) `#define CHECK(cond, msg)`
- Depends on: `batch.h`

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
  - `fprintf` (function, line 35) `fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__);`
  - `futex_init` (function, line 57) `futex_init();`
  - `CHECK` (function, line 68) `CHECK(futex_wait((unsigned long)&word_a, 6) == FUTEX_NOMATCH, "mismatch returns NOMATCH");`
  - `futex_wait` (function, line 95) `futex_wait((unsigned long)&word_a, 1);`
  - `printf` (function, line 141) `else printf("futex: %d failures\n", failures);`
  - `CHECK` (macro, line 31) `#define CHECK(cond, msg)`
- Depends on: `futex.h`

## tests/test_hal_io.c
- Layer: testing
- Doc: Docstring: Host test for arch/x86/hal_io.h (make test-hal).
- Language: c
- Symbols:
  - `main` (function, line 29) `int main(void)`
  - `fprintf` (function, line 26) `fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__);`
  - `CHECK` (function, line 31) `CHECK(HAL_PIC1_CMD == 0x20, "master pic command port");`
  - `hal_outb` (function, line 49) `hal_outb(HAL_PIC1_CMD, HAL_PIC_EOI);`
  - `hal_lapic_eoi` (function, line 54) `hal_lapic_eoi();`
  - `hal_pic_eoi` (function, line 57) `hal_pic_eoi(12);`
  - `printf` (function, line 63) `printf("hal_io: ok\n");`
  - `HAL_IO_HOST_TEST` (macro, line 10) `#define HAL_IO_HOST_TEST`
  - `CHECK` (macro, line 22) `#define CHECK(cond, msg)`
- Depends on: `arch/x86/hal_io.h`

## tests/test_percpu_rq.c
- Layer: testing
- Doc: Docstring: Host test for kernel/percpu_rq.c (make test-percpu-rq).
- Language: c
- Symbols:
  - `main` (function, line 23) `int main(void)`
  - `fprintf` (function, line 20) `fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__);`
  - `rq_init` (function, line 31) `rq_init();`
  - `CHECK` (function, line 33) `CHECK(rq_empty(0), "fresh ring is empty");`
  - `rq_enqueue` (function, line 35) `rq_enqueue(0, 3);`
  - `rq_stats` (function, line 46) `rq_stats(1, &hits, &steals, &drops);`
  - `rq_pop_local` (function, line 50) `rq_pop_local(1);`
  - `rq_note_poll` (function, line 66) `rq_note_poll(0);`
  - `printf` (function, line 84) `else printf("percpu_rq: %d failures\n", failures);`
  - `CHECK` (macro, line 16) `#define CHECK(cond, msg)`
- Depends on: `percpu_rq.h`

## tests/test_rcu.c
- Layer: testing
- Doc: Docstring: Host test for kernel/rcu.c (make test-rcu).
- Language: c
- Symbols:
  - `rcu_host_cpu` (function, line 18) `cpu_t *rcu_host_cpu(void)`
  - `test_cb` (function, line 22) `static void test_cb(void *arg)`
  - `main` (function, line 36) `int main(void)`
  - `fprintf` (function, line 33) `fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__);`
  - `rcu_init` (function, line 45) `rcu_init();`
  - `rcu_publish` (function, line 47) `rcu_publish(&slot, &a);`
  - `CHECK` (function, line 48) `CHECK(rcu_deref(&slot) == &a, "published pointer is visible");`
  - `rcu_note_tick` (function, line 56) `rcu_note_tick(0);`
  - `rcu_poll` (function, line 57) `rcu_poll();`
  - `rcu_read_lock` (function, line 84) `rcu_read_lock();`
  - `rcu_read_unlock` (function, line 88) `rcu_read_unlock();`
  - `printf` (function, line 95) `else printf("rcu: %d failures\n", failures);`
  - `CHECK` (macro, line 29) `#define CHECK(cond, msg)`
- Depends on: `rcu.h`

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
  - `memcpy` (function, line 34) `return memcpy(dst, src, (unsigned long)n);`
  - `fprintf` (function, line 44) `fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__);`
  - `SANITIZE_LEN_NEG` (function, line 49) `SANITIZE_LEN_NEG(len);`
  - `SANITIZE_RANGE` (function, line 50) `SANITIZE_RANGE(p, len);`
  - `SANITIZE_STR` (function, line 55) `SANITIZE_STR(p, 255);`
  - `SANITIZE_COPY_IN` (function, line 63) `SANITIZE_COPY_IN(kbuf, uptr, count, elemsz);`
  - `CHECK` (function, line 70) `CHECK(range_probe(0x400000UL, 8) == 0, "valid range passes");`
  - `printf` (function, line 110) `else printf("sanitize: %d failures\n", failures);`
  - `EFAULT` (macro, line 12) `#define EFAULT`
  - `CHECK` (macro, line 40) `#define CHECK(cond, msg)`
- Depends on: `kernel/string.c`, `sanitize.h`

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
  - `fprintf` (function, line 40) `fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__);`
  - `CHECK` (function, line 67) `CHECK(wake_up(&q) == WQ_NONE, "empty wake_up returns WQ_NONE");`
  - `sleep_on` (function, line 78) `sleep_on(&q);`
  - `mutex_lock` (function, line 108) `mutex_lock(&m);`
  - `mutex_unlock` (function, line 118) `mutex_unlock(&m);`
  - `sem_wait` (function, line 134) `sem_wait(&s);`
  - `sem_post` (function, line 140) `sem_post(&s);`
  - `cond_signal` (function, line 165) `cond_signal(&c);`
  - `cond_broadcast` (function, line 172) `cond_broadcast(&c);`
  - `rwlock_write_unlock` (function, line 194) `rwlock_write_unlock(&rw);`
  - `printf` (function, line 209) `else printf("sync: %d failures\n", failures);`
  - `CHECK` (macro, line 36) `#define CHECK(cond, msg)`
- Depends on: `sync.h`

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
  - `fprintf` (function, line 20) `fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__);`
  - `CHECK` (function, line 56) `CHECK(cfg.max_audio_listeners == TICK_MAX_AUDIO_LISTENERS, "config carries audio bound");`
  - `tick_reset` (function, line 58) `tick_reset();`
  - `tick_run_audio` (function, line 62) `tick_run_audio();`
  - `tick_run_desktop` (function, line 63) `tick_run_desktop();`
  - `printf` (function, line 113) `printf("tick: ok\n");`
  - `CHECK` (macro, line 16) `#define CHECK(cond, msg)`
- Depends on: `tick.h`

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
  - `fprintf` (function, line 23) `fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__);`
  - `vma_tree_init` (function, line 93) `vma_tree_init();`
  - `CHECK` (function, line 99) `CHECK(node != VMA_NIL, "insert returned nil within pool capacity");`
  - `vma_tree_insert` (function, line 157) `vma_tree_insert(&vma_live_root, (unsigned long)i * 0x1000, 0x1000);`
  - `printf` (function, line 176) `printf("vma: ok\n");`
  - `CHECK` (macro, line 19) `#define CHECK(cond, msg)`
- Depends on: `vma.h`
