#ifndef SELECT_MAP_H
#define SELECT_MAP_H

/** Docstring: select_map.h -- fd_set <-> pollfd translation for select(2).
 *
 * The kernel answers select(2)/pselect6(2) by polling through
 * net_sys_poll, whose units are pollfds. This header owns the pure
 * translation: Linux x86-64 fd_set bits (1024 fds, 128 bytes) to a
 * compact pollfd array and back, with the Linux readiness classes
 * (read = POLLIN|POLLERR|POLLHUP, write = POLLOUT|POLLERR, except =
 * POLLPRI). Nothing here touches user memory, the float side or the
 * scheduler, so tests/test_select_map.c (make test-select-map) drives
 * every branch on the host and a mutant that drops a class or a bounds
 * check dies without a QEMU boot.
 *
 * The pollfd struct is layout-compatible with Linux struct pollfd
 * (host order, 8 bytes) and net_sys_poll's in-memory view.
 */

#define SELECT_FD_SETSIZE 1024
#define SELECT_FD_SET_BYTES (SELECT_FD_SETSIZE / 8)

/* Linux poll(2) event bits (struct pollfd), same values net/net.c uses. */
#define SELECT_POLLIN 0x001
#define SELECT_POLLPRI 0x002
#define SELECT_POLLOUT 0x004
#define SELECT_POLLERR 0x008
#define SELECT_POLLHUP 0x010
#define SELECT_POLLNVAL 0x020

typedef struct {
    int fd;
    short events;
    short revents;
} select_pollfd_t;

static inline int select_fd_isset(const unsigned char *set, int fd) {
    return set && fd >= 0 && (set[fd >> 3] & (1u << (fd & 7))) != 0;
}

static inline void select_fd_put(unsigned char *set, int fd) {
    if (set && fd >= 0) set[fd >> 3] |= (unsigned char)(1u << (fd & 7));
}

/** Docstring: Count fds below nfds present in any of the three sets. */
static inline unsigned select_poll_count(const unsigned char *r,
                                         const unsigned char *w,
                                         const unsigned char *e,
                                         unsigned nfds) {
    unsigned i, n = 0;
    for (i = 0; i < nfds; i++) {
        if (select_fd_isset(r, (int)i) || select_fd_isset(w, (int)i) ||
            select_fd_isset(e, (int)i)) {
            n++;
        }
    }
    return n;
}

/** Docstring: Build the pollfd array for the fds the sets request.
 *
 * Entries come out in ascending fd order, one per requested fd, with
 * the union of the classes the three sets asked for. The caller sizes
 * the array through select_poll_count with the same arguments.
 */
static inline unsigned select_poll_build(select_pollfd_t *pfd,
                                         const unsigned char *r,
                                         const unsigned char *w,
                                         const unsigned char *e,
                                         unsigned nfds) {
    unsigned i, n = 0;
    for (i = 0; i < nfds; i++) {
        short events = 0;
        if (select_fd_isset(r, (int)i)) events |= SELECT_POLLIN;
        if (select_fd_isset(w, (int)i)) events |= SELECT_POLLOUT;
        if (select_fd_isset(e, (int)i)) events |= SELECT_POLLPRI;
        if (events) {
            pfd[n].fd = (int)i;
            pfd[n].events = events;
            pfd[n].revents = 0;
            n++;
        }
    }
    return n;
}

/** Docstring: Map poll revents into fresh result sets (Linux classes).
 *
 * The "in" sets are the kernel-side copies of what the caller requested
 * (roin/win/ein may be NULL); "out" sets are zeroed and receive only fds
 * that were both requested in that set and ready in that class, so an
 * fd armed for write only never appears in the read results. Returns
 * the number of fds ready in at least one set, like Linux select.
 */
static inline unsigned select_poll_result(unsigned char *rout,
                                          const unsigned char *rin,
                                          unsigned char *wout,
                                          const unsigned char *win,
                                          unsigned char *eout,
                                          const unsigned char *ein,
                                          const select_pollfd_t *pfd,
                                          unsigned count) {
    unsigned i, j, ready = 0;
    if (rout) for (j = 0; j < SELECT_FD_SET_BYTES; j++) rout[j] = 0;
    if (wout) for (j = 0; j < SELECT_FD_SET_BYTES; j++) wout[j] = 0;
    if (eout) for (j = 0; j < SELECT_FD_SET_BYTES; j++) eout[j] = 0;
    for (i = 0; i < count; i++) {
        int fd = pfd[i].fd;
        short rv = pfd[i].revents;
        int any = 0;
        if (rout && select_fd_isset(rin, fd) &&
            (rv & (SELECT_POLLIN | SELECT_POLLERR | SELECT_POLLHUP))) {
            select_fd_put(rout, fd);
            any = 1;
        }
        if (wout && select_fd_isset(win, fd) &&
            (rv & (SELECT_POLLOUT | SELECT_POLLERR))) {
            select_fd_put(wout, fd);
            any = 1;
        }
        if (eout && select_fd_isset(ein, fd) && (rv & SELECT_POLLPRI)) {
            select_fd_put(eout, fd);
            any = 1;
        }
        if (any) ready++;
    }
    return ready;
}

/** Docstring: True when any polled fd reported POLLNVAL (a bad fd). */
static inline int select_poll_badfd(const select_pollfd_t *pfd,
                                    unsigned count) {
    unsigned i;
    for (i = 0; i < count; i++) {
        if (pfd[i].revents & SELECT_POLLNVAL) return 1;
    }
    return 0;
}

#endif
