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

## tests/test_driver.c
- Layer: testing
- Doc: test_driver.c -- Host test for the Strategy-pattern device registry.
- Language: c
- Symbols:
  - `test_read` (function, line 15) `static int test_read(device_t *d, unsigned lba, unsigned count, void *buf)`
  - `main` (function, line 24) `int main(void)`
  - `memset` (function, line 27) `memset(&a, 0, sizeof(a));`
  - `strcpy` (function, line 28) `strcpy(a.name, "ide0");`
  - `device_reset` (function, line 31) `device_reset();`
  - `assert` (function, line 33) `assert(device_count() == 0);`
  - `snprintf` (function, line 66) `snprintf(d.name, sizeof(d.name), "dev%d", i);`
  - `printf` (function, line 82) `printf("driver: ok\n");`
- Depends on: `driver.h`, `kernel/string.c`

## tests/test_fault.c
- Layer: testing
- Doc: test_fault.c -- fault-injection suite (boyscout gap #10).
- Language: c
- Symbols:
  - `range_ok` (function, line 35) `static int range_ok(unsigned long p, unsigned long len)`
  - `str_ok` (function, line 41) `static int str_ok(const unsigned char *mem, unsigned long p,
                  unsigned long maxlen)`
  - `normalize` (function, line 52) `static void normalize(const char *path, char *out, unsigned cap)`
  - `path_trusted` (function, line 83) `static int path_trusted(const char *full)`
  - `main` (function, line 93) `int main(void)`
  - `against` (function, line 10) `* after bounding against (END-BASE)/elemsz, so the product cannot * wrap past the range check);`
  - `memcpy` (function, line 74) `memcpy(out + len, start, clen);`
  - `vma_tree_init` (function, line 96) `vma_tree_init();`
  - `CHECK` (function, line 102) `CHECK(i == VMA_MAX, "pool holds VMA_MAX nodes");`
  - `memset` (function, line 124) `memset(umem, 'A', sizeof(umem));`
  - `CHECK` (macro, line 28) `#define CHECK(c, m)`
  - `U_BASE` (macro, line 31) `#define U_BASE`
  - `U_END` (macro, line 32) `#define U_END`
  - `TRUSTED_DIR` (macro, line 81) `#define TRUSTED_DIR`
  - `TRUSTED_LEN` (macro, line 82) `#define TRUSTED_LEN`
- Depends on: `kernel/string.c`, `vma.h`

## tests/test_freedom_wl.c
- Layer: testing
- Doc: test_freedom_wl - host suite for the Wayland to MiniOS mapping.
- Language: c
- Symbols:
  - `check_host` (function, line 12) `static int check_host(int cond, const char *name)`
  - `main` (function, line 22) `int main(void)`
  - `printf` (function, line 14) `printf("FAIL: %s\n", name);`
  - `wl_copy` (function, line 108) `wl_copy(rh, "a.b", 64L);`
  - `FREEDOM_WL_HOST_TEST` (macro, line 7) `#define FREEDOM_WL_HOST_TEST`
- Depends on: `progs/src/freedom_wl.c`

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
  - `printf` (function, line 156) `else printf("futex: %d failures\n", failures);`
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
  - `hal_outb` (function, line 50) `hal_outb(HAL_PIC1_CMD, HAL_PIC_EOI);`
  - `hal_lapic_eoi` (function, line 55) `hal_lapic_eoi();`
  - `hal_pic_eoi` (function, line 58) `hal_pic_eoi(12);`
  - `printf` (function, line 64) `printf("hal_io: ok\n");`
  - `HAL_IO_HOST_TEST` (macro, line 10) `#define HAL_IO_HOST_TEST`
  - `CHECK` (macro, line 22) `#define CHECK(cond, msg)`
- Depends on: `arch/x86/hal_io.h`

## tests/test_ktime.c
- Layer: testing
- Doc: test_ktime.c -- host test for the pure conversion math in ktime.h
- Language: c
- Symbols:
  - `main` (function, line 15) `int main(void)`
  - `CHECK` (function, line 17) `CHECK(ktime_us_from_delta(0, 3000000UL) == 0, "zero delta");`
  - `CHECK` (macro, line 14) `#define CHECK(c, m)`
- Depends on: `ktime.h`

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

## tests/test_randmix.c
- Layer: testing
- Doc: test_randmix.c -- host test for the getrandom mixer in randmix.h
- Language: c
- Symbols:
  - `popcount64` (function, line 17) `static int popcount64(unsigned long x)`
  - `main` (function, line 23) `int main(void)`
  - `CHECK` (function, line 25) `CHECK(randmix64(0) == randmix64(0), "deterministic");`
  - `CHECK` (macro, line 16) `#define CHECK(c, m)`
- Depends on: `randmix.h`

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

## tests/test_rtc.c
- Layer: testing
- Doc: test_rtc.c -- host test for the pure date math in drivers/rtc.c
- Language: c
- Symbols:
  - `main` (function, line 17) `int main(void)`
  - `CHECK` (function, line 19) `CHECK(rtc_days_from_civil(1970, 1, 1) == 0, "epoch is day zero");`
  - `CHECK` (macro, line 16) `#define CHECK(c, m)`
- Depends on: `rtc.h`

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
  - `pi_set_base` (function, line 214) `pi_set_base(1, 1);`
  - `mutex_note_waiter` (function, line 225) `mutex_note_waiter(&m, 2);`
  - `printf` (function, line 267) `else printf("sync: %d failures\n", failures);`
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

## tests/test_vedit_build.c
- Layer: testing
- Doc: Docstring: Host test for the vedit IDE build contract (make test-vedit).
- Language: c
- Symbols:
  - `t_has_ext` (function, line 30) `static int t_has_ext(const char *fname, const char *ext)`
  - `t_base_of` (function, line 41) `static int t_base_of(const char *fname, char *dst, size_t cap)`
  - `t_join` (function, line 61) `static int t_join(const char *dir, const char *base, const char *ext,
                  char *dst...`
  - `t_link_fmt` (function, line 77) `static int t_link_fmt(const char *s)`
  - `main` (function, line 107) `int main(void)`
  - `fprintf` (function, line 27) `fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__);`
  - `CHECK` (function, line 111) `CHECK(t_lang_of("untitled") == 1, "untitled highlights as C");`
  - `printf` (function, line 146) `printf("vedit build host test FAIL (%d)\n", failures);`
  - `CHECK` (macro, line 23) `#define CHECK(cond, msg)`
- Depends on: `kernel/string.c`

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

## tests/test_vma_bench.c
- Layer: testing
- Doc: test_vma_bench.c -- RB-tree vs sorted-list benchmark (boyscout gap #9).
- Language: c
- Symbols:
  - `now_us` (function, line 12) `static long now_us(void)`
  - `l_insert` (function, line 23) `static void l_insert(unsigned long b)`
  - `l_find` (function, line 28) `static int l_find(unsigned long b)`
  - `bench` (function, line 33) `static void bench(int n)`
  - `main` (function, line 53) `int main(void)`
  - `gettimeofday` (function, line 15) `gettimeofday(&tv, 0);`
  - `vma_tree_init` (function, line 37) `vma_tree_init();`
  - `vma_tree_insert` (function, line 40) `vma_tree_insert(&vma_live_root, 0x500000ul + (unsigned long)i * 0x1000, 0x1000);`
  - `vma_tree_find` (function, line 43) `vma_tree_find(vma_live_root, 0x500000ul + (unsigned long)i * 0x1000);`
  - `LIST_MAX` (macro, line 20) `#define LIST_MAX`
- Depends on: `kernel/time.c`, `vma.h`

## tests/test_wm.c
- Layer: testing
- Doc: Docstring: Host test for wm_geom.h and wm_events.h (make test-wm).
- Language: c
- Symbols:
  - `main` (function, line 26) `int main(void)`
  - `fprintf` (function, line 23) `fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__);`
  - `CHECK` (function, line 40) `CHECK(gcfg.font_w == 8, "geom config carries font width");`
  - `wm_clamp_point` (function, line 85) `wm_clamp_point(&cx, &cy, 800, 600);`
  - `printf` (function, line 304) `printf("wm: ok\n");`
  - `CHECK` (macro, line 19) `#define CHECK(cond, msg)`
- Depends on: `wm_events.h`, `wm_focus.h`, `wm_geom.h`, `wm_render.h`, `wm_tiling.h`, `wm_window.h`
