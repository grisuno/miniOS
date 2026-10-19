/* lxsel.c -- select(2)/pselect6(2) ABI probe (docs/spec/python.md).
 *
 * Static glibc's select() enters pselect6 (270) on x86-64 and MicroPython's
 * time.sleep rides it, so this probe pins the kernel contract directly:
 * the nfds bound, negative timeout fields, the timeout actually waiting,
 * select's timeval write-back, readiness of a pipe read end (both the
 * legacy select number and pselect6), readiness of a pipe write end,
 * an empty read end timing out, and a bad fd answering EBADF instead of
 * a silent zero.
 *
 * Prints one "lxsel: <name> ok" line per vector and "lxsel: all ok";
 * a failure prints "lxsel: <name> FAILED" and a final "lxsel: FAILED".
 * Driven by the `lxsel` BDD scenario (tools/test_bdd.sh) and mutated by
 * tools/mutate.sh (lxsel-* mutants kill on a missing check here).
 */

#define _GNU_SOURCE
#include <errno.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

/* The kernel's real fd_set is the Linux 1024-fd form; glibc's FD_SET
 * covers it, and 1025 is out of range on either side. */
#define LXSEL_NFDS_OUT_OF_RANGE 1025
#define LXSEL_BAD_FD 999
#define LXSEL_TIMEOUT_US 30000
#define LXSEL_TIMEOUT_MS_MIN 20
#define LXSEL_PSELECT_TIMEOUT_NS 20000000L

static int failures;

static void report(const char *name, int ok) {
    if (ok) {
        printf("lxsel: %s ok\n", name);
    } else {
        printf("lxsel: %s FAILED\n", name);
        failures++;
    }
}

static long raw_select(long nfds, fd_set *r, fd_set *w, fd_set *e,
                       struct timeval *tv) {
    return syscall(SYS_select, nfds, r, w, e, tv);
}

static long raw_pselect6(long nfds, fd_set *r, fd_set *w, fd_set *e,
                         struct timespec *ts) {
    return syscall(SYS_pselect6, nfds, r, w, e, ts, NULL);
}

static long elapsed_ms(struct timespec *a, struct timespec *b) {
    return (b->tv_sec - a->tv_sec) * 1000L +
           (b->tv_nsec - a->tv_nsec) / 1000000L;
}

int main(void) {
    struct timeval tv;
    struct timespec ts, t0, t1;
    fd_set r, w;
    int fds[2];
    long ret;
    char byte = 'x';

    ts.tv_sec = 0;
    ts.tv_nsec = 0;
    errno = 0;
    ret = raw_pselect6(LXSEL_NFDS_OUT_OF_RANGE, NULL, NULL, NULL, &ts);
    report("nfds-bounds", ret == -1 && errno == EINVAL);

    tv.tv_sec = -1;
    tv.tv_usec = 0;
    errno = 0;
    ret = raw_select(0, NULL, NULL, NULL, &tv);
    report("negative-timeout", ret == -1 && errno == EINVAL);

    tv.tv_sec = 0;
    tv.tv_usec = LXSEL_TIMEOUT_US;
    clock_gettime(CLOCK_MONOTONIC, &t0);
    errno = 0;
    ret = raw_select(0, NULL, NULL, NULL, &tv);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    report("timeout-waits",
           ret == 0 && elapsed_ms(&t0, &t1) >= LXSEL_TIMEOUT_MS_MIN);
    report("timeval-writeback",
           tv.tv_sec == 0 && tv.tv_usec >= 0 && tv.tv_usec < LXSEL_TIMEOUT_US);

    if (pipe(fds) != 0) {
        report("pipe-created", 0);
        printf("lxsel: FAILED\n");
        return 1;
    }
    if (write(fds[1], &byte, 1) != 1) {
        report("pipe-write", 0);
    }

    FD_ZERO(&r);
    FD_SET(fds[0], &r);
    ts.tv_sec = 0;
    ts.tv_nsec = 0;
    ret = raw_pselect6(fds[0] + 1, &r, NULL, NULL, &ts);
    report("pselect6-ready-read", ret == 1 && FD_ISSET(fds[0], &r));

    FD_ZERO(&r);
    FD_SET(fds[0], &r);
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    ret = raw_select(fds[0] + 1, &r, NULL, NULL, &tv);
    report("select-ready-read", ret == 1 && FD_ISSET(fds[0], &r));

    FD_ZERO(&w);
    FD_SET(fds[1], &w);
    ts.tv_sec = 0;
    ts.tv_nsec = 0;
    ret = raw_pselect6(fds[1] + 1, NULL, &w, NULL, &ts);
    report("pselect6-ready-write", ret == 1 && FD_ISSET(fds[1], &w));

    if (read(fds[0], &byte, 1) != 1) {
        report("pipe-read", 0);
    }
    FD_ZERO(&r);
    FD_SET(fds[0], &r);
    ts.tv_sec = 0;
    ts.tv_nsec = LXSEL_PSELECT_TIMEOUT_NS;
    ret = raw_pselect6(fds[0] + 1, &r, NULL, NULL, &ts);
    report("pselect6-times-out", ret == 0 && !FD_ISSET(fds[0], &r));

    FD_ZERO(&r);
    FD_SET(LXSEL_BAD_FD, &r);
    ts.tv_sec = 0;
    ts.tv_nsec = 0;
    errno = 0;
    ret = raw_pselect6(LXSEL_BAD_FD + 1, &r, NULL, NULL, &ts);
    report("bad-fd-ebadf", ret == -1 && errno == EBADF);

    close(fds[0]);
    close(fds[1]);

    if (failures) {
        printf("lxsel: FAILED (%d)\n", failures);
        return 1;
    }
    printf("lxsel: all ok\n");
    return 0;
}
