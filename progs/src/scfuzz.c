/* scfuzz: deterministic syscall fuzzer (syzkaller spirit, BDD scale).
 *
 * Two 1:1 threads hammer mmap/munmap/mprotect/yield with interleaved,
 * seeded operation streams and fold every result into an FNV-1a
 * checksum. The checksum is the oracle: same seed, same kernel, same
 * hash; any race, lost wakeup or behavioral drift changes it or wedges
 * the guest (the BDD timeout then talks). All fuzz maps stay inside
 * one private 4 MB arena (partitioned per thread plus one shared
 * counter page) and transient single pages, so a fault always names a
 * kernel bug, never self-corruption. Raw syscalls only, no libc, no
 * malloc in workers. Built as a static Linux ELF and run with
 * `run bin/scfuzz.elf`. */
#include "mthreads.h"

#define SC_OPS 400
#define SC_ARENA (4 * 1024 * 1024)
#define SC_PAGE 4096
#define SC_PAGES 1024
#define SC_T0_BASE 1
#define SC_T0_N 511
#define SC_T1_BASE 512
#define SC_T1_N 511

static long sc_mmap(long len) {
    long r;
    register long a2 asm("rsi") = len;
    register long a3 asm("rdx") = 3;
    register long a4 asm("r10") = 0x22;
    register long a5 asm("r8") = -1;
    register long a6 asm("r9") = 0;
    __asm__ volatile("syscall"
        : "=a"(r)
        : "0"(9), "D"(0), "r"(a2), "r"(a3), "r"(a4), "r"(a5), "r"(a6)
        : "rcx", "r11", "memory");
    return r;
}

static long sc_mprotect(long addr, long len, long prot) {
    long r;
    register long a2 asm("rsi") = len;
    register long a3 asm("rdx") = prot;
    __asm__ volatile("syscall"
        : "=a"(r)
        : "0"(10), "D"(addr), "r"(a2), "r"(a3)
        : "rcx", "r11", "memory");
    return r;
}

static long sc_munmap(long addr, long len) {
    return m_syscall6(11, addr, len, 0);
}

static long sc_write(long fd, const char *s, long n) {
    long r;
    __asm__ volatile("syscall" : "=a"(r)
                     : "a"(1), "D"(fd), "S"(s), "d"(n)
                     : "rcx", "r11", "memory");
    return r;
}

static void sc_exit(long code) {
    m_syscall6(MINIOS_SYS_EXIT, code, 0, 0);
    for (;;)
        ;
}

static unsigned long sc_rng(unsigned long *s) {
    unsigned long x = *s;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    *s = x;
    return x;
}

static unsigned long sc_fold(unsigned long h, unsigned long v) {
    h ^= v & 0xFFFFFFFFu;
    h *= 16777619u;
    h ^= (v >> 32) & 0xFFFFFFFFu;
    h *= 16777619u;
    return h;
}

static char sc_arena_prot[SC_PAGES];
static volatile long sc_shared;
static long sc_arena;

static void sc_hex8(unsigned long v, char *out) {
    int i;
    for (i = 7; i >= 0; i--) {
        unsigned d = (unsigned)(v & 0xFu);
        out[i] = (char)(d < 10 ? '0' + d : 'a' + d - 10);
        v >>= 4;
    }
}

static unsigned long sc_worker(int me, unsigned long seed) {
    unsigned long h = 2166136261u;
    unsigned long s = seed;
    long base = me == 0 ? SC_T0_BASE : SC_T1_BASE;
    long np = me == 0 ? SC_T0_N : SC_T1_N;
    long i;
    static const long prots[4] = {3, 1, 5, 0};
    for (i = 0; i < SC_OPS; i++) {
        unsigned long r = sc_rng(&s);
        long op = (long)(r % 5u);
        if (op == 0) {
            long pg = base + (long)(sc_rng(&s) % (unsigned long)np);
            volatile char *p = (volatile char *)(sc_arena + pg * SC_PAGE);
            if (sc_arena_prot[pg] & 2) {
                p[0] = (char)(i & 0xFF);
                p[4095] = (char)((i >> 8) & 0xFF);
                h = sc_fold(h, (unsigned long)(p[0] + p[4095] * 131 + i));
            } else {
                h = sc_fold(h, (unsigned long)(p[0] + p[4095] * 131 + i));
            }
        } else if (op == 1) {
            long pg = base + (long)(sc_rng(&s) % (unsigned long)np);
            long len = 1 + (long)(sc_rng(&s) % 3u);
            long prot = prots[i & 3];
            long rc;
            long k;
            if (pg + len > base + np) len = base + np - pg;
            rc = sc_mprotect(sc_arena + pg * SC_PAGE, len * SC_PAGE, prot);
            h = sc_fold(h, (unsigned long)rc);
            if (rc != 0) sc_exit(30 + me);
            for (k = 0; k < len; k++) sc_arena_prot[pg + k] = (char)prot;
        } else if (op == 2) {
            long p = sc_mmap(SC_PAGE);
            h = sc_fold(h, (unsigned long)p);
            if (p > 0) {
                volatile char *m = (volatile char *)p;
                m[0] = (char)(i & 0xFF);
                m[2048] = (char)((i >> 3) & 0xFF);
                h = sc_fold(h, (unsigned long)(m[0] * 7 + m[2048] + i));
                if (sc_munmap(p, SC_PAGE) != 0) sc_exit(40 + me);
                h = sc_fold(h, (unsigned long)i);
            }
        } else if (op == 3) {
            __sync_fetch_and_add(&sc_shared, 1);
            h = sc_fold(h, (unsigned long)i * 0x9E3779B1u);
        } else {
            myield();
            h = sc_fold(h, (unsigned long)i + 0x85EBCA6Bu);
        }
    }
    return h;
}

static unsigned long sc_seed0 = 0xC10C4001u;
static unsigned long sc_seed1 = 0xF00D5113u;
static unsigned long sc_h1;

static void *sc_thread1(void *arg) {
    (void)arg;
    sc_h1 = sc_worker(1, sc_seed1);
    return 0;
}

void _start(void) {
    unsigned long h;
    char msg[32];
    mthread_t t;
    long k;
    sc_arena = sc_mmap(SC_ARENA);
    if (sc_arena <= 0) sc_exit(10);
    for (k = 0; k < SC_PAGES; k++) sc_arena_prot[k] = 3;
    sc_write(1, "scfuzz: start\n", 14);
    if (mthread_create(&t, sc_thread1, 0) != 0) sc_exit(11);
    h = sc_worker(0, sc_seed0);
    if (mthread_join(t, 0) != 0) sc_exit(12);
    h = sc_fold(h, sc_h1);
    h = sc_fold(h, (unsigned long)sc_shared);
    msg[0] = 's';
    msg[1] = 'c';
    msg[2] = 'f';
    msg[3] = 'u';
    msg[4] = 'z';
    msg[5] = 'z';
    msg[6] = ':';
    msg[7] = ' ';
    sc_hex8(h & 0xFFFFFFFFu, msg + 8);
    msg[16] = '\n';
    sc_write(1, msg, 17);
    sc_exit(0);
}
