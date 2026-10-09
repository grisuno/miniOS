/** lxabi.c - Linux process, thread and descriptor ABI probe (FreeDom
 * readiness, docs/spec/smp-sched.md "Linux process, thread and descriptor
 * ABI").
 *
 * A static glibc program that exercises exactly the kernel surface the full
 * FreeDom GUI needs: register state across fork, clone threads with TLS and
 * join, auto-reaped detached threads, futex bitset waits with timeouts, pipe2
 * and fcntl flags, blocking and non-blocking pipe I/O with EOF and EPIPE,
 * close-on-exit of a child's descriptors, writev into a pipe, eventfd, poll on
 * pipes and eventfds, close_range, time(2) and mkdir. Every check prints
 * "lxabi: <check> ok" or "lxabi: <check> FAIL <detail>"; the run ends with
 * "lxabi: all ok" and exit 0, or "lxabi: <n> failed" and exit 1.
 *
 * Built with -mno-red-zone: the register probe pushes onto the stack from
 * inline assembly.
 */
#define _GNU_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <pthread.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/eventfd.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/uio.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define LXABI_CHILD_DELAY_MS   200L
#define LXABI_THREADS          4
#define LXABI_THREAD_ITERS     1000
#define LXABI_DETACHED         80
#define LXABI_WAIT_SPINS       5000000L
#define LXABI_TIMEDWAIT_MS     50L
#define LXABI_EPOCH_2023       1672531200L
#define LXABI_CLOCK_SKEW_S     2L
#define LXABI_REG_PROBE_WORDS  9
#define LXABI_CLONE_NR         56
#define LXABI_SIGCHLD          17
#define LXABI_A6_MAGIC         0x7777L
#define LXABI_CHILD_BAD        3
#define LXABI_MKDIR_PATH       "/tmp/lxabi_dir"
#define LXABI_MKDIR_FILE       "/tmp/lxabi_dir/probe.txt"
#define LXABI_CLOSE_RANGE_NR   436

static int failures;

static void report(const char *name, int ok, const char *detail) {
    if (ok) {
        printf("lxabi: %s ok\n", name);
    } else {
        printf("lxabi: %s FAIL %s\n", name, detail ? detail : "");
        failures++;
    }
    fflush(stdout);
}

static long now_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (long)ts.tv_sec * 1000L + ts.tv_nsec / 1000000L;
}

static void busy_wait_ms(long ms) {
    long end = now_ms() + ms;
    while (now_ms() < end) sched_yield();
}

/* ---------------------------------------------------------------- fork registers */

static const uint64_t reg_magic[6] = {
    0x1111111111111111ULL, 0x2222222222222222ULL, 0x3333333333333333ULL,
    0x4444444444444444ULL, 0x5555555555555555ULL, 0x6666666666666666ULL,
};

/* Raw clone(SIGCHLD) with known values in every callee-saved register and in
 * the argument registers; both sides store what they see after the syscall. */
static void fork_probe(uint64_t *out) {
    __asm__ volatile(
        "pushq %[out]\n\t"
        "pushq %%rbp\n\tpushq %%rbx\n\tpushq %%r12\n\t"
        "pushq %%r13\n\tpushq %%r14\n\tpushq %%r15\n\t"
        "movabsq $0x1111111111111111, %%rbx\n\t"
        "movabsq $0x2222222222222222, %%rbp\n\t"
        "movabsq $0x3333333333333333, %%r12\n\t"
        "movabsq $0x4444444444444444, %%r13\n\t"
        "movabsq $0x5555555555555555, %%r14\n\t"
        "movabsq $0x6666666666666666, %%r15\n\t"
        "movl $56, %%eax\n\t"
        "movl $17, %%edi\n\t"
        "xorl %%esi, %%esi\n\t"
        "xorl %%edx, %%edx\n\t"
        "xorl %%r10d, %%r10d\n\t"
        "xorl %%r8d, %%r8d\n\t"
        "movq $0x7777, %%r9\n\t"
        "syscall\n\t"
        "movq 48(%%rsp), %%rcx\n\t"
        "movq %%rax, 0(%%rcx)\n\t"
        "movq %%rbx, 8(%%rcx)\n\t"
        "movq %%rbp, 16(%%rcx)\n\t"
        "movq %%r12, 24(%%rcx)\n\t"
        "movq %%r13, 32(%%rcx)\n\t"
        "movq %%r14, 40(%%rcx)\n\t"
        "movq %%r15, 48(%%rcx)\n\t"
        "movq %%rdi, 56(%%rcx)\n\t"
        "movq %%r9, 64(%%rcx)\n\t"
        "popq %%r15\n\tpopq %%r14\n\tpopq %%r13\n\t"
        "popq %%r12\n\tpopq %%rbx\n\tpopq %%rbp\n\t"
        "addq $8, %%rsp\n\t"
        :
        : [out] "r"(out)
        : "rax", "rcx", "rdx", "rsi", "rdi", "r8", "r9", "r10", "r11", "memory");
}

static int regs_match(const uint64_t *r) {
    for (int i = 0; i < 6; i++)
        if (r[1 + i] != reg_magic[i]) return 0;
    return r[7] == (uint64_t)LXABI_SIGCHLD && r[8] == (uint64_t)LXABI_A6_MAGIC;
}

static void check_fork_registers(void) {
    uint64_t r[LXABI_REG_PROBE_WORDS];
    memset(r, 0, sizeof r);
    fork_probe(r);
    if ((long)r[0] == 0) {
        syscall(SYS_exit_group, regs_match(r) ? 0 : LXABI_CHILD_BAD);
    }
    if ((long)r[0] < 0) {
        report("fork-registers", 0, "clone(SIGCHLD) failed");
        return;
    }
    int st = -1;
    waitpid((pid_t)r[0], &st, 0);
    report("fork-registers", regs_match(r) && st == 0,
           regs_match(r) ? "child saw clobbered registers" : "parent registers clobbered");
}

/* ---------------------------------------------------------------- threads */

static pthread_mutex_t counter_lock = PTHREAD_MUTEX_INITIALIZER;
static long counter;
static __thread long tls_slot;
static pid_t main_pid;

typedef struct thread_result {
    long tls_seen;
    int  same_pid;
    long tid;
} thread_result;

static void *worker(void *arg) {
    thread_result *res = (thread_result *)arg;
    tls_slot = (long)(intptr_t)res;
    for (int i = 0; i < LXABI_THREAD_ITERS; i++) {
        pthread_mutex_lock(&counter_lock);
        counter++;
        pthread_mutex_unlock(&counter_lock);
    }
    res->tls_seen = tls_slot;
    res->same_pid = getpid() == main_pid;
    res->tid = syscall(SYS_gettid);
    return res;
}

static void check_threads(void) {
    pthread_t th[LXABI_THREADS];
    thread_result res[LXABI_THREADS];
    int created = 0, ok = 1;
    long main_tid = syscall(SYS_gettid);
    tls_slot = -1;
    memset(res, 0, sizeof res);
    for (int i = 0; i < LXABI_THREADS; i++) {
        if (pthread_create(&th[i], NULL, worker, &res[i]) != 0) { ok = 0; break; }
        created++;
    }
    for (int i = 0; i < created; i++) {
        void *ret = NULL;
        if (pthread_join(th[i], &ret) != 0 || ret != &res[i]) ok = 0;
    }
    report("thread-create-join", ok && created == LXABI_THREADS, "create or join failed");
    report("thread-mutex", counter == (long)LXABI_THREADS * LXABI_THREAD_ITERS, "lost increments");
    int tls_ok = tls_slot == -1, pid_ok = 1, tid_ok = 1;
    for (int i = 0; i < created; i++) {
        if (res[i].tls_seen != (long)(intptr_t)&res[i]) tls_ok = 0;
        if (!res[i].same_pid) pid_ok = 0;
        if (res[i].tid == main_tid || res[i].tid <= 0) tid_ok = 0;
    }
    report("thread-tls", tls_ok, "TLS shared between threads");
    report("thread-getpid", pid_ok, "getpid differs inside a thread");
    report("thread-gettid", tid_ok, "thread tid equals the main tid");
}

static volatile long detached_done;

static void *detached_worker(void *arg) {
    (void)arg;
    __atomic_add_fetch(&detached_done, 1, __ATOMIC_SEQ_CST);
    return NULL;
}

static void check_detached_reaped(void) {
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    int created = 0;
    for (int i = 0; i < LXABI_DETACHED; i++) {
        pthread_t t;
        long target = created;
        if (pthread_create(&t, &attr, detached_worker, NULL) != 0) break;
        created++;
        for (long spin = 0; spin < LXABI_WAIT_SPINS &&
             __atomic_load_n(&detached_done, __ATOMIC_SEQ_CST) <= target; spin++)
            sched_yield();
    }
    pthread_attr_destroy(&attr);
    char detail[64];
    snprintf(detail, sizeof detail, "only %d of %d threads", created, LXABI_DETACHED);
    report("thread-detached-reaped", created == LXABI_DETACHED, detail);
}

static pthread_mutex_t cv_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
static int cv_flag;

static void *signaller(void *arg) {
    (void)arg;
    busy_wait_ms(LXABI_TIMEDWAIT_MS);
    pthread_mutex_lock(&cv_lock);
    cv_flag = 1;
    pthread_cond_signal(&cv);
    pthread_mutex_unlock(&cv_lock);
    return NULL;
}

static void check_condvar(void) {
    struct timespec dl;
    clock_gettime(CLOCK_REALTIME, &dl);
    dl.tv_nsec += LXABI_TIMEDWAIT_MS * 1000000L;
    if (dl.tv_nsec >= 1000000000L) { dl.tv_sec++; dl.tv_nsec -= 1000000000L; }
    pthread_mutex_lock(&cv_lock);
    int rc = 0;
    while (!cv_flag && rc == 0) rc = pthread_cond_timedwait(&cv, &cv_lock, &dl);
    pthread_mutex_unlock(&cv_lock);
    report("futex-timedwait-timeout", rc == ETIMEDOUT, "timed wait did not time out");

    pthread_t t;
    int created = pthread_create(&t, NULL, signaller, NULL) == 0;
    pthread_mutex_lock(&cv_lock);
    while (created && !cv_flag) pthread_cond_wait(&cv, &cv_lock);
    pthread_mutex_unlock(&cv_lock);
    if (created) pthread_join(t, NULL);
    report("futex-condvar-signal", created && cv_flag, "condition variable never signalled");
}

/* ---------------------------------------------------------------- pipes */

static void check_pipe2_flags(void) {
    int p[2];
    if (pipe2(p, O_CLOEXEC | O_NONBLOCK) != 0) {
        report("pipe2-flags", 0, strerror(errno));
        return;
    }
    int fd_ok = (fcntl(p[0], F_GETFD) & FD_CLOEXEC) && (fcntl(p[1], F_GETFD) & FD_CLOEXEC);
    int fl_ok = (fcntl(p[0], F_GETFL) & O_NONBLOCK) != 0;
    char c;
    errno = 0;
    int again = read(p[0], &c, 1) == -1 && errno == EAGAIN;
    report("pipe2-flags", fd_ok && fl_ok, "cloexec or nonblock missing");
    report("pipe-nonblock-eagain", again, "empty nonblocking read did not answer EAGAIN");

    int dup_fd = fcntl(p[0], F_DUPFD_CLOEXEC, 10);
    int dup_ok = dup_fd >= 10 && (fcntl(dup_fd, F_GETFD) & FD_CLOEXEC);
    int clr_ok = fcntl(p[0], F_SETFD, 0) == 0 && (fcntl(p[0], F_GETFD) & FD_CLOEXEC) == 0;
    int fl_clr = fcntl(p[0], F_SETFL, 0) == 0 && (fcntl(p[0], F_GETFL) & O_NONBLOCK) == 0;
    report("fcntl-dupfd-cloexec", dup_ok, "F_DUPFD_CLOEXEC wrong");
    report("fcntl-setfd-setfl", clr_ok && fl_clr, "F_SETFD or F_SETFL ignored");
    errno = 0;
    report("fcntl-bad-fd", fcntl(-5, F_GETFD) == -1 && errno == EBADF, "bad fd not EBADF");
    if (dup_fd >= 0) close(dup_fd);
    close(p[0]);
    close(p[1]);
}

static void check_pipe_blocking(void) {
    int p[2];
    if (pipe(p) != 0) { report("pipe-blocking-read", 0, strerror(errno)); return; }
    pid_t pid = fork();
    if (pid == 0) {
        close(p[0]);
        busy_wait_ms(LXABI_CHILD_DELAY_MS);
        ssize_t w = write(p[1], "ping", 4);
        _exit(w == 4 ? 0 : LXABI_CHILD_BAD);
    }
    close(p[1]);
    char buf[8] = { 0 };
    ssize_t n = read(p[0], buf, sizeof buf);
    report("pipe-blocking-read", n == 4 && memcmp(buf, "ping", 4) == 0, "blocking read returned early");
    n = read(p[0], buf, sizeof buf);
    report("pipe-eof-after-child-exit", n == 0, "no EOF once the child exited");
    int st = -1;
    if (pid > 0) waitpid(pid, &st, 0);
    report("fork-child-exit", pid > 0 && st == 0, "child failed");
    close(p[0]);
}

static void check_pipe_epipe(void) {
    int p[2];
    signal(SIGPIPE, SIG_IGN);
    if (pipe(p) != 0) { report("pipe-epipe", 0, strerror(errno)); return; }
    close(p[0]);
    errno = 0;
    ssize_t n = write(p[1], "x", 1);
    report("pipe-epipe", n == -1 && errno == EPIPE, "write with no reader did not fail EPIPE");
    close(p[1]);
}

static void check_writev_pipe(void) {
    int p[2];
    if (pipe(p) != 0) { report("writev-pipe", 0, strerror(errno)); return; }
    struct iovec iov[2] = { { (void *)"ab", 2 }, { (void *)"cd", 2 } };
    ssize_t w = writev(p[1], iov, 2);
    char buf[8] = { 0 };
    ssize_t r = read(p[0], buf, sizeof buf);
    report("writev-pipe", w == 4 && r == 4 && memcmp(buf, "abcd", 4) == 0, "writev bytes lost");
    close(p[0]);
    close(p[1]);
}

static void check_poll(void) {
    int p[2];
    if (pipe(p) != 0) { report("poll-pipe", 0, strerror(errno)); return; }
    struct pollfd pf[2] = { { p[0], POLLIN, 0 }, { p[1], POLLOUT, 0 } };
    int idle = poll(pf, 1, 0) == 0 && pf[0].revents == 0;
    int out = poll(&pf[1], 1, 0) == 1 && (pf[1].revents & POLLOUT);
    (void)!write(p[1], "z", 1);
    int in = poll(pf, 1, 0) == 1 && (pf[0].revents & POLLIN);
    char c;
    (void)!read(p[0], &c, 1);
    close(p[1]);
    int hup = poll(pf, 1, 0) == 1 && (pf[0].revents & POLLHUP);
    struct pollfd neg = { -1, POLLIN, (short)0x7fff };
    int skip = poll(&neg, 1, 0) == 0 && neg.revents == 0;
    report("poll-pipe-idle", idle, "empty pipe reported ready");
    report("poll-pipe-pollout", out, "writable pipe not POLLOUT");
    report("poll-pipe-pollin", in, "pipe with data not POLLIN");
    report("poll-pipe-pollhup", hup, "closed writer not POLLHUP");
    report("poll-negative-fd", skip, "negative fd not skipped");
    close(p[0]);
}

/* ---------------------------------------------------------------- eventfd */

static void check_eventfd(void) {
    int fd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (fd < 0) { report("eventfd", 0, strerror(errno)); return; }
    uint64_t v = 3, got = 0;
    int w1 = write(fd, &v, sizeof v) == (ssize_t)sizeof v;
    v = 4;
    int w2 = write(fd, &v, sizeof v) == (ssize_t)sizeof v;
    struct pollfd pf = { fd, POLLIN, 0 };
    int in = poll(&pf, 1, 0) == 1 && (pf.revents & POLLIN);
    int r = read(fd, &got, sizeof got) == (ssize_t)sizeof got;
    errno = 0;
    int again = read(fd, &got, sizeof got) == -1 && errno == EAGAIN;
    errno = 0;
    int shortr = read(fd, &got, 4) == -1 && errno == EINVAL;
    int cloexec = (fcntl(fd, F_GETFD) & FD_CLOEXEC) != 0;
    report("eventfd-counter", w1 && w2 && r && got == 7, "counter did not sum to 7");
    report("eventfd-poll", in, "nonzero counter not POLLIN");
    report("eventfd-eagain", again, "empty counter did not answer EAGAIN");
    report("eventfd-short-read", shortr, "4-byte read not EINVAL");
    report("eventfd-cloexec", cloexec, "EFD_CLOEXEC ignored");
    close(fd);
}

/* ---------------------------------------------------------------- misc */

static void check_close_range(void) {
    int p[2];
    if (pipe(p) != 0) { report("close-range-cloexec", 0, strerror(errno)); return; }
    long rc = syscall(LXABI_CLOSE_RANGE_NR, (unsigned)p[0], ~0U, 4U);
    int marked = (fcntl(p[0], F_GETFD) & FD_CLOEXEC) && (fcntl(p[1], F_GETFD) & FD_CLOEXEC);
    report("close-range-cloexec", rc == 0 && marked, "CLOSE_RANGE_CLOEXEC did not mark fds");
    rc = syscall(LXABI_CLOSE_RANGE_NR, (unsigned)p[0], (unsigned)p[1], 0U);
    errno = 0;
    int closed = rc == 0 && fcntl(p[0], F_GETFD) == -1 && errno == EBADF;
    report("close-range-close", closed, "close_range did not close the range");
}

static void check_time(void) {
    time_t t = time(NULL);
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long skew = (long)t - (long)tv.tv_sec;
    if (skew < 0) skew = -skew;
    report("time", t > LXABI_EPOCH_2023 && skew <= LXABI_CLOCK_SKEW_S, "time(2) not the wall clock");
}

static void check_mkdir(void) {
    int rc = mkdir(LXABI_MKDIR_PATH, 0700);
    int ok = rc == 0 || errno == EEXIST;
    FILE *f = ok ? fopen(LXABI_MKDIR_FILE, "w") : NULL;
    if (f) { fputs("ok\n", f); fclose(f); }
    errno = 0;
    int again = mkdir(LXABI_MKDIR_PATH, 0700) == -1 && errno == EEXIST;
    report("mkdir", ok && f != NULL, "mkdir or file inside failed");
    report("mkdir-eexist", again, "second mkdir not EEXIST");
}

int main(void) {
    main_pid = getpid();
    check_time();
    check_fork_registers();
    check_pipe2_flags();
    check_pipe_blocking();
    check_pipe_epipe();
    check_writev_pipe();
    check_poll();
    check_eventfd();
    check_close_range();
    check_mkdir();
    check_threads();
    check_condvar();
    check_detached_reaped();
    if (failures == 0) {
        printf("lxabi: all ok\n");
        return 0;
    }
    printf("lxabi: %d failed\n", failures);
    return 1;
}
