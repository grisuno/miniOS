/** apsse.c - SSE in glibc threads on every CPU (docs/spec/smp-sched.md,
 * "Per-CPU control registers").
 *
 * CR0 and CR4 are per-CPU: an AP that never sets CR4.OSFXSR raises #UD on
 * the first XMM instruction a thread executes there, which is how the
 * FreeDom browser's fetch threads died under -smp 2 (glibc's string
 * routines are SSE2). Each worker grinds SSE2 integer and double arithmetic
 * plus memchr for a needle that moves every round through a private buffer
 * (so no round can be hoisted) for APSSE_ROUNDS rounds (many timer
 * ticks each, so idle APs claim them) and checks every result against one
 * reference the main thread computes first; the scheduler hands CLONE_VM
 * threads to idle APs, so with -smp 2 the work lands there.
 *
 * While the workers run, the main thread maps, fills and unmaps an anonymous
 * region APSSE_MAP_ROUNDS times: each munmap frees frames a worker's CPU
 * shares the address space with, which is the TLB shootdown path (the smp
 * builtin counts tlb_shootdowns).
 *
 * Prints "apsse: ok threads=<n>" and exits 0, or "apsse: FAIL <detail>" and
 * exits 1. A CPU without SSE kills the process with an exception dump
 * before either line.
 */
#define _GNU_SOURCE
#include <emmintrin.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

#define APSSE_THREADS 8
#define APSSE_ROUNDS  200000
#define APSSE_SEED    3
#define APSSE_BUF     2048
#define APSSE_NEEDLE  0x5a
#define APSSE_MAP_ROUNDS 64
#define APSSE_MAP_BYTES  (64 * 1024)
#define APSSE_MAP_FILL   0xa5
#define APSSE_OK      0
#define APSSE_BAD     1

struct apsse_job {
    uint64_t got;
};

/** SSE2 integer lanes, a double accumulator and an SSE2 memchr per round;
 * the folded value depends on every lane, so a corrupted XMM register
 * changes it. */
static uint64_t apsse_grind(int id) {
    unsigned char buf[APSSE_BUF];
    __m128i acc = _mm_set1_epi32(id + 1);
    __m128i step = _mm_set_epi32(3, 5, 7, 11);
    double d = (double)id;
    uint64_t hits = 0;
    int r;
    unsigned pos = (unsigned)id % APSSE_BUF;
    memset(buf, 0, sizeof buf);
    for (r = 0; r < APSSE_ROUNDS; r++) {
        const unsigned char *at;
        buf[pos] = APSSE_NEEDLE;
        acc = _mm_add_epi32(acc, step);
        acc = _mm_xor_si128(acc, _mm_srli_epi32(acc, 3));
        d = d * 0.5 + 1.25;
        at = (const unsigned char *)memchr(buf, APSSE_NEEDLE, sizeof buf);
        if (at != NULL) hits += (uint64_t)(at - buf);
        buf[pos] = 0;
        pos = (pos * 5u + 1u) % APSSE_BUF;
    }
    uint32_t lanes[4];
    _mm_storeu_si128((__m128i *)lanes, acc);
    return ((uint64_t)lanes[0] ^ ((uint64_t)lanes[1] << 8) ^ ((uint64_t)lanes[2] << 16) ^
            ((uint64_t)lanes[3] << 24)) + hits + (uint64_t)(d * 1000.0);
}

static void *apsse_worker(void *arg) {
    struct apsse_job *job = (struct apsse_job *)arg;
    job->got = apsse_grind(APSSE_SEED);
    return NULL;
}

int main(void) {
    pthread_t th[APSSE_THREADS];
    struct apsse_job jobs[APSSE_THREADS];
    int i, bad = 0;
    uint64_t want = apsse_grind(APSSE_SEED);
    for (i = 0; i < APSSE_THREADS; i++) jobs[i].got = 0;
    for (i = 0; i < APSSE_THREADS; i++) {
        if (pthread_create(&th[i], NULL, apsse_worker, &jobs[i]) != 0) {
            printf("apsse: FAIL pthread_create %d\n", i);
            return APSSE_BAD;
        }
    }
    for (i = 0; i < APSSE_MAP_ROUNDS; i++) {
        unsigned char *m = mmap(NULL, APSSE_MAP_BYTES, PROT_READ | PROT_WRITE,
                                MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (m == MAP_FAILED) {
            printf("apsse: FAIL mmap round %d\n", i);
            return APSSE_BAD;
        }
        memset(m, APSSE_MAP_FILL, APSSE_MAP_BYTES);
        if (munmap(m, APSSE_MAP_BYTES) != 0) {
            printf("apsse: FAIL munmap round %d\n", i);
            return APSSE_BAD;
        }
    }
    for (i = 0; i < APSSE_THREADS; i++) pthread_join(th[i], NULL);
    for (i = 0; i < APSSE_THREADS; i++) {
        if (jobs[i].got != want) {
            printf("apsse: FAIL thread %d got %llx want %llx\n", i,
                   (unsigned long long)jobs[i].got, (unsigned long long)want);
            bad = 1;
        }
    }
    if (bad) return APSSE_BAD;
    printf("apsse: ok threads=%d\n", APSSE_THREADS);
    return APSSE_OK;
}
