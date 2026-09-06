/* thdemo.c -- Producer-consumer over mthreads (roadmap Phase 1, M1).
 *
 * Ten threads (1 main + 5 producers + 4 consumers) share one address
 * space through thread_spawn (MiniOS syscall 225): a bounded buffer,
 * a spin mutex and Mesa-style spin-waits.  Workers never touch stdio
 * or the allocator (both are process-global under CLONE_VM); only the
 * main thread prints, after every join, so the output is deterministic:
 *
 *   thdemo: produced=1000 consumed=1000 sum=2099500 threads=10
 *   thdemo: PASS
 *
 * Exit code is 0 on PASS, 1 otherwise.  Build with the host toolchain
 * (`make progs/bin/thdemo`, static, like sbtone); it ships on MiniFS.
 */

#include <stdio.h>

#include "mthreads.h"
#include "minios_abi.h"

#define NPROD    5
#define NCONS    4
#define PER_PROD 200
#define BUFSZ    16

#define EXPECTED_N   (NPROD * PER_PROD)
#define EXPECTED_SUM (PER_PROD * 1000 * (NPROD * (NPROD - 1) / 2) \
                      + NPROD * (PER_PROD * (PER_PROD - 1) / 2))

static int buf[BUFSZ];
static int head, tail, count;
static mmutex_t m;
static long produced_sum, consumed_sum;
static int produced_n, consumed_n, producers_done;

static void *producer(void *p) {
    long id = (long)p;
    int i;
    for (i = 0; i < PER_PROD; i++) {
        int v = (int)(id * 1000 + i);
        mmutex_lock(&m);
        while (count == BUFSZ) {
            mmutex_unlock(&m);
            myield();
            mmutex_lock(&m);
        }
        buf[head] = v;
        head = (head + 1) % BUFSZ;
        count++;
        produced_sum += v;
        produced_n++;
        mmutex_unlock(&m);
    }
    return (void *)(long)PER_PROD;
}

static void *consumer(void *p) {
    (void)p;
    int got = 0;
    for (;;) {
        int v;
        mmutex_lock(&m);
        while (count == 0) {
            if (producers_done == NPROD) {
                mmutex_unlock(&m);
                return (void *)(long)got;
            }
            mmutex_unlock(&m);
            myield();
            mmutex_lock(&m);
        }
        v = buf[tail];
        tail = (tail + 1) % BUFSZ;
        count--;
        consumed_sum += v;
        consumed_n++;
        got++;
        mmutex_unlock(&m);
    }
}

int main(void) {
    mthread_t prod[NPROD], cons[NCONS];
    int i;
    mmutex_init(&m);
    for (i = 0; i < NPROD; i++) {
        if (mthread_create(&prod[i], producer, (void *)(long)i) != 0) {
            printf("thdemo: producer create failed\n");
            return 1;
        }
    }
    printf("thdemo: producers started\n");
    for (i = 0; i < NCONS; i++) {
        if (mthread_create(&cons[i], consumer, 0) != 0) {
            printf("thdemo: consumer create failed\n");
            return 1;
        }
    }
    printf("thdemo: consumers started\n");
    for (i = 0; i < NPROD; i++)
        mthread_join(prod[i], 0);
    printf("thdemo: producers joined\n");
    mmutex_lock(&m);
    producers_done = NPROD;
    mmutex_unlock(&m);
    for (i = 0; i < NCONS; i++)
        mthread_join(cons[i], 0);
    printf("thdemo: produced=%d consumed=%d sum=%ld threads=%d\n",
           produced_n, consumed_n, consumed_sum, 1 + NPROD + NCONS);
    if (produced_n == EXPECTED_N && consumed_n == EXPECTED_N
        && produced_sum == EXPECTED_SUM && consumed_sum == EXPECTED_SUM) {
        printf("thdemo: PASS\n");
        return 0;
    }
    printf("thdemo: FAIL (want n=%d sum=%d)\n", EXPECTED_N, EXPECTED_SUM);
    return 1;
}
