/** Docstring: Host test for headers/select_map.h (make test-select-map).
 *
 * Drives the pure fd_set <-> pollfd translation with stack vectors:
 * bit isolation across bytes, count/build for mixed sets, the Linux
 * readiness classes (read = IN|ERR|HUP, write = OUT|ERR, except = PRI),
 * the "only requested fds" rule, POLLNVAL detection and NULL-set
 * tolerance, so a mutant that drops a class or an isset guard dies on
 * the host with no QEMU boot.
 */

#include <stdio.h>
#include <string.h>

#include "select_map.h"

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

static void test_bit_ops(void) {
    unsigned char set[SELECT_FD_SET_BYTES];
    memset(set, 0, sizeof(set));
    select_fd_put(set, 0);
    select_fd_put(set, 7);
    select_fd_put(set, 8);
    select_fd_put(set, 63);
    select_fd_put(set, 64);
    select_fd_put(set, 1023);
    CHECK(select_fd_isset(set, 0), "bit 0 set");
    CHECK(select_fd_isset(set, 7), "bit 7 set");
    CHECK(select_fd_isset(set, 8), "bit 8 set");
    CHECK(select_fd_isset(set, 63), "bit 63 set");
    CHECK(select_fd_isset(set, 64), "bit 64 set");
    CHECK(select_fd_isset(set, 1023), "bit 1023 set");
    CHECK(!select_fd_isset(set, 1), "bit 1 clear");
    CHECK(!select_fd_isset(set, 56), "bit 56 clear");
    CHECK(!select_fd_isset(set, 72), "bit 72 clear");
    CHECK(!select_fd_isset(set, 1022), "bit 1022 clear");
    CHECK(!select_fd_isset(NULL, 0), "NULL set reads as clear");
    select_fd_put(NULL, 3);
    select_fd_put(set, -1);
    CHECK(set[0] == 0x81 && set[1] == 0x01, "byte 0/1 exact after puts");
}

static void test_count_and_build(void) {
    unsigned char r[SELECT_FD_SET_BYTES];
    unsigned char w[SELECT_FD_SET_BYTES];
    select_pollfd_t pfd[8];
    unsigned n;
    memset(r, 0, sizeof(r));
    memset(w, 0, sizeof(w));
    select_fd_put(r, 0);
    select_fd_put(r, 70);
    select_fd_put(w, 1);
    CHECK(select_poll_count(r, w, NULL, 71) == 3, "count three of 71");
    CHECK(select_poll_count(r, w, NULL, 2) == 2, "count two below nfds");
    CHECK(select_poll_count(r, w, NULL, 0) == 0, "count zero nfds");
    CHECK(select_poll_count(NULL, NULL, NULL, 10) == 0, "count all NULL");
    n = select_poll_build(pfd, r, w, NULL, 71);
    CHECK(n == 3, "build three entries");
    CHECK(pfd[0].fd == 0 && pfd[0].events == SELECT_POLLIN, "entry 0 read");
    CHECK(pfd[1].fd == 1 && pfd[1].events == SELECT_POLLOUT, "entry 1 write");
    CHECK(pfd[2].fd == 70 && pfd[2].events == SELECT_POLLIN, "entry 2 read");
    CHECK(pfd[0].revents == 0, "build zeroes revents");
}

static void test_union_events(void) {
    unsigned char r[SELECT_FD_SET_BYTES];
    unsigned char w[SELECT_FD_SET_BYTES];
    unsigned char e[SELECT_FD_SET_BYTES];
    select_pollfd_t pfd[4];
    unsigned n;
    memset(r, 0, sizeof(r));
    memset(w, 0, sizeof(w));
    memset(e, 0, sizeof(e));
    select_fd_put(r, 5);
    select_fd_put(w, 5);
    select_fd_put(e, 5);
    n = select_poll_build(pfd, r, w, e, 8);
    CHECK(n == 1, "union is one entry");
    CHECK(pfd[0].events == (SELECT_POLLIN | SELECT_POLLOUT | SELECT_POLLPRI),
          "union events IN|OUT|PRI");
}

static void test_result_classes(void) {
    unsigned char rin[SELECT_FD_SET_BYTES];
    unsigned char win[SELECT_FD_SET_BYTES];
    unsigned char ein[SELECT_FD_SET_BYTES];
    unsigned char rout[SELECT_FD_SET_BYTES];
    unsigned char wout[SELECT_FD_SET_BYTES];
    unsigned char eout[SELECT_FD_SET_BYTES];
    select_pollfd_t pfd[3];
    unsigned ready;
    memset(rin, 0, sizeof(rin));
    memset(win, 0, sizeof(win));
    memset(ein, 0, sizeof(ein));
    memset(rout, 0xAA, sizeof(rout));
    memset(wout, 0xAA, sizeof(wout));
    memset(eout, 0xAA, sizeof(eout));
    select_fd_put(rin, 0);
    select_fd_put(rin, 1);
    select_fd_put(win, 1);
    select_fd_put(ein, 2);
    pfd[0].fd = 0; pfd[0].revents = SELECT_POLLIN;
    pfd[1].fd = 1; pfd[1].revents = SELECT_POLLERR;
    pfd[2].fd = 2; pfd[2].revents = SELECT_POLLPRI;
    ready = select_poll_result(rout, rin, wout, win, eout, ein, pfd, 3);
    CHECK(ready == 3, "three fds ready");
    CHECK(select_fd_isset(rout, 0), "fd0 readable");
    CHECK(select_fd_isset(rout, 1), "fd1 read class from POLLERR");
    CHECK(select_fd_isset(wout, 1), "fd1 write class from POLLERR");
    CHECK(!select_fd_isset(wout, 0), "fd0 not writable");
    CHECK(select_fd_isset(eout, 2), "fd2 except class from POLLPRI");
    CHECK(!select_fd_isset(rout, 2), "fd2 not in read set");
    CHECK(!select_fd_isset(ein, 0), "ein untouched by result");
}

static void test_result_only_requested(void) {
    unsigned char rin[SELECT_FD_SET_BYTES];
    unsigned char win[SELECT_FD_SET_BYTES];
    unsigned char rout[SELECT_FD_SET_BYTES];
    unsigned char wout[SELECT_FD_SET_BYTES];
    select_pollfd_t pfd[2];
    unsigned ready;
    memset(rin, 0, sizeof(rin));
    memset(win, 0, sizeof(win));
    select_fd_put(rin, 2);
    select_fd_put(win, 3);
    pfd[0].fd = 2; pfd[0].revents = SELECT_POLLOUT;
    pfd[1].fd = 3; pfd[1].revents = SELECT_POLLIN;
    ready = select_poll_result(rout, rin, wout, win, NULL, NULL, pfd, 2);
    CHECK(ready == 0, "class mismatch is not readiness");
    CHECK(!select_fd_isset(rout, 2), "read set keeps only read-class fds");
    CHECK(!select_fd_isset(wout, 3), "write set keeps only write-class fds");
}

static void test_result_hup_read_only(void) {
    unsigned char rin[SELECT_FD_SET_BYTES];
    unsigned char win[SELECT_FD_SET_BYTES];
    unsigned char rout[SELECT_FD_SET_BYTES];
    unsigned char wout[SELECT_FD_SET_BYTES];
    select_pollfd_t pfd[1];
    unsigned ready;
    memset(rin, 0, sizeof(rin));
    memset(win, 0, sizeof(win));
    select_fd_put(rin, 0);
    select_fd_put(win, 0);
    pfd[0].fd = 0; pfd[0].revents = SELECT_POLLHUP;
    ready = select_poll_result(rout, rin, wout, win, NULL, NULL, pfd, 1);
    CHECK(ready == 1, "hup is one ready fd");
    CHECK(select_fd_isset(rout, 0), "hup lands in read set");
    CHECK(!select_fd_isset(wout, 0), "hup is not write readiness");
}

static void test_badfd(void) {
    select_pollfd_t pfd[2];
    pfd[0].fd = 0; pfd[0].revents = SELECT_POLLIN;
    pfd[1].fd = 9; pfd[1].revents = SELECT_POLLNVAL;
    CHECK(!select_poll_badfd(pfd, 1), "no bad fd in first entry");
    CHECK(select_poll_badfd(pfd, 2), "NVAL detected");
    CHECK(!select_poll_badfd(pfd, 0), "empty array has no bad fd");
}

int main(void) {
    test_bit_ops();
    test_count_and_build();
    test_union_events();
    test_result_classes();
    test_result_only_requested();
    test_result_hup_read_only();
    test_badfd();
    if (failures) {
        fprintf(stderr, "select_map: %d failure(s)\n", failures);
        return 1;
    }
    printf("select_map: all ok\n");
    return 0;
}
