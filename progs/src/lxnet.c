/** lxnet.c - Linux socket ABI probe (FreeDom readiness step 6,
 * docs/spec/network.md "Linux socket ABI").
 *
 * Exercises what static glibc's resolver, libcurl and OpenSSL need from the
 * socket layer, against the host fixture tools/test_net_fixture.py (UDP and
 * TCP echo on one port, reached as 10.0.2.2 through QEMU slirp): datagram
 * sockets with sendto/recvfrom and connect/send/recv, socket type flags,
 * non-blocking connect completed through poll(POLLOUT) and SO_ERROR,
 * setsockopt/getsockopt/getsockname/getpeername, send flags MSG_NOSIGNAL and
 * MSG_DONTWAIT, read/write on a socket, AF_INET6 refusal, and getaddrinfo
 * through /etc/hosts.
 *
 * Usage: lxnet <host-ip> <port>
 * Prints "lxnet: <check> ok" or "lxnet: <check> FAIL <detail>", then
 * "lxnet: all ok" with exit 0, or "lxnet: <n> failed" with exit 1.
 *
 * Diagnostic mode: lxnet --dial <host> <port>
 * Resolves host through getaddrinfo (resolv.conf, hosts, nsswitch.conf)
 * and dials the first IPv4 answer with libcurl's sequence (non-blocking
 * connect, poll for POLLOUT, SO_ERROR). Prints "lxnet: resolve <host> ->
 * <ip>" or the resolver error, then "lxnet: dial ok" with exit 0 or
 * "lxnet: dial FAIL <reason>" with exit 1.
 */
#define _GNU_SOURCE
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/uio.h>
#include <unistd.h>

#define LXNET_WAIT_MS   3000
#define LXNET_BUF       64
#define LXNET_UDP_MSG   "lxnet-udp"
#define LXNET_TCP_MSG   "lxnet-tcp"
#define LXNET_LOOPBACK  "127.0.0.1"
#define LXNET_IP_UNKNOWN 0x7ff

static int failures;

static void report(const char *name, int ok, const char *detail) {
    if (ok) printf("lxnet: %s ok\n", name);
    else { printf("lxnet: %s FAIL %s\n", name, detail ? detail : ""); failures++; }
    fflush(stdout);
}

static int wait_for(int fd, short events) {
    struct pollfd p = { fd, events, 0 };
    int r = poll(&p, 1, LXNET_WAIT_MS);
    return r == 1 && (p.revents & events);
}

/* Read exactly len bytes or fail (waits through poll between chunks). */
static int read_all(int fd, char *buf, size_t len) {
    size_t got = 0;
    while (got < len) {
        if (!wait_for(fd, POLLIN)) return 0;
        ssize_t n = recv(fd, buf + got, len - got, MSG_DONTWAIT);
        if (n <= 0) return 0;
        got += (size_t)n;
    }
    return 1;
}

static void check_udp(const struct sockaddr_in *peer) {
    char buf[LXNET_BUF];
    struct sockaddr_in from;
    socklen_t fl = sizeof from;
    int fd = socket(AF_INET, SOCK_DGRAM | SOCK_CLOEXEC, 0);
    report("udp-socket", fd >= 0 && (fcntl(fd, F_GETFD) & FD_CLOEXEC), strerror(errno));
    if (fd < 0) return;
    {
        int one = 1, tos = 0;
        socklen_t tl = sizeof tos;
        int recverr = setsockopt(fd, IPPROTO_IP, IP_RECVERR, &one, sizeof one) == 0;
        int settos = setsockopt(fd, IPPROTO_IP, IP_TOS, &one, sizeof one) == 0;
        int gettos = getsockopt(fd, IPPROTO_IP, IP_TOS, &tos, &tl) == 0;
        errno = 0;
        int bad = setsockopt(fd, IPPROTO_IP, LXNET_IP_UNKNOWN, &one, sizeof one) == -1 &&
                  errno == ENOPROTOOPT;
        report("udp-ip-options", recverr && settos && gettos && bad,
               "IP_RECVERR/IP_TOS refused or unknown IP option accepted");
    }
    ssize_t w = sendto(fd, LXNET_UDP_MSG, strlen(LXNET_UDP_MSG), 0,
                       (const struct sockaddr *)peer, sizeof *peer);
    int ready = wait_for(fd, POLLIN);
    int pending = -1;
    int fionread = ready && ioctl(fd, FIONREAD, &pending) == 0;
    errno = 0;
    int notty = !isatty(fd) && errno == ENOTTY;
    report("udp-ioctl-fionread", fionread && pending == (int)strlen(LXNET_UDP_MSG) && notty,
           "FIONREAD wrong or a socket claimed to be a terminal");
    memset(buf, 0, sizeof buf);
    ssize_t r = ready ? recvfrom(fd, buf, sizeof buf, 0, (struct sockaddr *)&from, &fl) : -1;
    report("udp-sendto-recvfrom",
           w == (ssize_t)strlen(LXNET_UDP_MSG) && r == w && memcmp(buf, LXNET_UDP_MSG, (size_t)w) == 0 &&
           from.sin_addr.s_addr == peer->sin_addr.s_addr && from.sin_port == peer->sin_port,
           "datagram not echoed by the fixture");
    close(fd);

    fd = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
    int conn = fd >= 0 && connect(fd, (const struct sockaddr *)peer, sizeof *peer) == 0;
    errno = 0;
    int again = conn && recv(fd, buf, sizeof buf, 0) == -1 && errno == EAGAIN;
    w = conn ? send(fd, LXNET_UDP_MSG, strlen(LXNET_UDP_MSG), 0) : -1;
    memset(buf, 0, sizeof buf);
    r = (conn && wait_for(fd, POLLIN)) ? recv(fd, buf, sizeof buf, 0) : -1;
    report("udp-nonblock-eagain", again, "empty non-blocking datagram socket did not EAGAIN");
    report("udp-connect-send-recv", r == w && w > 0 && memcmp(buf, LXNET_UDP_MSG, (size_t)w) == 0,
           "connected datagram not echoed");
    if (fd >= 0) close(fd);

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    conn = fd >= 0 && connect(fd, (const struct sockaddr *)peer, sizeof *peer) == 0;
    {
        struct iovec iov[2] = { { (void *)LXNET_UDP_MSG, 5 }, { (void *)LXNET_TCP_MSG, 5 } };
        struct mmsghdr mm[2];
        char a[LXNET_BUF], b[LXNET_BUF];
        int sent = -1;
        ssize_t ra = -1, rb = -1;
        memset(mm, 0, sizeof mm);
        mm[0].msg_hdr.msg_iov = &iov[0];
        mm[0].msg_hdr.msg_iovlen = 1;
        mm[1].msg_hdr.msg_iov = &iov[1];
        mm[1].msg_hdr.msg_iovlen = 1;
        if (conn) sent = sendmmsg(fd, mm, 2, MSG_NOSIGNAL);
        memset(a, 0, sizeof a);
        memset(b, 0, sizeof b);
        if (sent == 2 && wait_for(fd, POLLIN)) ra = recv(fd, a, sizeof a, 0);
        if (ra == 5 && wait_for(fd, POLLIN)) rb = recv(fd, b, sizeof b, 0);
        report("udp-sendmmsg",
               sent == 2 && mm[0].msg_len == 5 && mm[1].msg_len == 5 &&
               ra == 5 && rb == 5 && memcmp(a, LXNET_UDP_MSG, 5) == 0 &&
               memcmp(b, LXNET_TCP_MSG, 5) == 0,
               "two datagrams not sent and echoed in order");
    }
    if (fd >= 0) close(fd);
}

/* A non-blocking connect to a port nobody listens on fails through poll
 * (POLLERR) with SO_ERROR = ECONNREFUSED, cleared once read. */
static void check_refused(const struct sockaddr_in *peer) {
    struct sockaddr_in closed = *peer;
    struct pollfd p;
    int soerr = 0, again = -1;
    socklen_t sl = sizeof soerr;
    int fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    closed.sin_port = htons((unsigned short)(ntohs(peer->sin_port) + 1));
    if (fd < 0) { report("tcp-connect-refused", 0, strerror(errno)); return; }
    errno = 0;
    int rc = connect(fd, (const struct sockaddr *)&closed, sizeof closed);
    int inprog = rc == -1 && errno == EINPROGRESS;
    p.fd = fd;
    p.events = POLLOUT;
    p.revents = 0;
    int pr = poll(&p, 1, LXNET_WAIT_MS);
    getsockopt(fd, SOL_SOCKET, SO_ERROR, &soerr, &sl);
    sl = sizeof again;
    getsockopt(fd, SOL_SOCKET, SO_ERROR, &again, &sl);
    report("tcp-connect-refused",
           inprog && pr == 1 && (p.revents & POLLERR) && soerr == ECONNREFUSED && again == 0,
           "refused connect not reported through POLLERR and SO_ERROR");
    close(fd);
}

static void check_tcp(const struct sockaddr_in *peer) {
    char buf[LXNET_BUF];
    int fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
    if (fd < 0) { report("tcp-nonblock-connect", 0, strerror(errno)); return; }
    int rc = connect(fd, (const struct sockaddr *)peer, sizeof *peer);
    int inprog = rc == 0 || errno == EINPROGRESS;
    int writable = inprog && wait_for(fd, POLLOUT);
    int soerr = -1;
    socklen_t sl = sizeof soerr;
    int got = getsockopt(fd, SOL_SOCKET, SO_ERROR, &soerr, &sl) == 0;
    report("tcp-nonblock-connect", inprog && writable && got && soerr == 0, "connect did not complete");

    int one = 1;
    int nodelay = setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &one, sizeof one) == 0;
    int keep = setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &one, sizeof one) == 0;
    report("tcp-setsockopt", nodelay && keep, "TCP_NODELAY or SO_KEEPALIVE refused");

    struct sockaddr_in me, them;
    socklen_t ml = sizeof me, tl = sizeof them;
    int names = getsockname(fd, (struct sockaddr *)&me, &ml) == 0 &&
                getpeername(fd, (struct sockaddr *)&them, &tl) == 0;
    report("tcp-sock-peer-names",
           names && me.sin_family == AF_INET && me.sin_port != 0 &&
           them.sin_addr.s_addr == peer->sin_addr.s_addr && them.sin_port == peer->sin_port,
           "addresses wrong");

    ssize_t w = send(fd, LXNET_TCP_MSG, strlen(LXNET_TCP_MSG), MSG_NOSIGNAL);
    memset(buf, 0, sizeof buf);
    int echoed = w == (ssize_t)strlen(LXNET_TCP_MSG) && read_all(fd, buf, (size_t)w) &&
                 memcmp(buf, LXNET_TCP_MSG, (size_t)w) == 0;
    report("tcp-send-nosignal", echoed, "stream not echoed");

    w = write(fd, LXNET_TCP_MSG, strlen(LXNET_TCP_MSG));
    memset(buf, 0, sizeof buf);
    int rw = 0;
    if (w == (ssize_t)strlen(LXNET_TCP_MSG) && wait_for(fd, POLLIN)) {
        ssize_t r = read(fd, buf, (size_t)w);
        rw = r > 0 && memcmp(buf, LXNET_TCP_MSG, (size_t)r) == 0;
    }
    report("tcp-read-write", rw, "read/write on a socket failed");
    close(fd);
}

static void check_misc(void) {
    errno = 0;
    int fd = socket(AF_INET6, SOCK_STREAM, 0);
    report("socket-inet6-clean", fd >= 0 || errno == EAFNOSUPPORT,
           "AF_INET6 neither served nor refused with EAFNOSUPPORT");
    if (fd >= 0) close(fd);

    struct addrinfo hints, *res = NULL;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    int rc = getaddrinfo("localhost", "80", &hints, &res);
    int ok = rc == 0 && res && res->ai_family == AF_INET &&
             ((struct sockaddr_in *)res->ai_addr)->sin_addr.s_addr == inet_addr(LXNET_LOOPBACK);
    report("getaddrinfo-hosts", ok, rc ? gai_strerror(rc) : "wrong address");
    if (res) freeaddrinfo(res);
}

/* Resolve host and dial port the way libcurl does; 0 when connected. */
static int dial(const char *host, const char *port) {
    struct addrinfo hints, *res = NULL;
    struct sockaddr_in addr;
    char text[INET_ADDRSTRLEN];
    int soerr = -1;
    socklen_t sl = sizeof soerr;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    int rc = getaddrinfo(host, port, &hints, &res);
    if (rc != 0 || !res) {
        printf("lxnet: resolve %s FAIL %s\n", host, rc ? gai_strerror(rc) : "no answer");
        return 1;
    }
    memcpy(&addr, res->ai_addr, sizeof addr);
    freeaddrinfo(res);
    inet_ntop(AF_INET, &addr.sin_addr, text, sizeof text);
    printf("lxnet: resolve %s -> %s\n", host, text);
    int fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
    if (fd < 0) {
        printf("lxnet: dial FAIL socket %s\n", strerror(errno));
        return 1;
    }
    rc = connect(fd, (const struct sockaddr *)&addr, sizeof addr);
    if (rc != 0 && errno != EINPROGRESS) {
        printf("lxnet: dial FAIL connect %s\n", strerror(errno));
        close(fd);
        return 1;
    }
    if (rc != 0 && !wait_for(fd, POLLOUT)) {
        printf("lxnet: dial FAIL no POLLOUT within %d ms\n", LXNET_WAIT_MS);
        close(fd);
        return 1;
    }
    getsockopt(fd, SOL_SOCKET, SO_ERROR, &soerr, &sl);
    close(fd);
    if (soerr != 0) {
        printf("lxnet: dial FAIL SO_ERROR %s\n", strerror(soerr));
        return 1;
    }
    printf("lxnet: dial ok\n");
    return 0;
}

int main(int argc, char **argv) {
    struct sockaddr_in peer;
    if (argc == 4 && strcmp(argv[1], "--dial") == 0)
        return dial(argv[2], argv[3]);
    if (argc != 3) {
        fprintf(stderr, "usage: lxnet <host-ip> <port>\n");
        return 2;
    }
    memset(&peer, 0, sizeof peer);
    peer.sin_family = AF_INET;
    peer.sin_port = htons((unsigned short)atoi(argv[2]));
    if (inet_pton(AF_INET, argv[1], &peer.sin_addr) != 1) {
        fprintf(stderr, "lxnet: bad address %s\n", argv[1]);
        return 2;
    }
    check_udp(&peer);
    check_tcp(&peer);
    check_refused(&peer);
    check_misc();
    if (failures == 0) {
        printf("lxnet: all ok\n");
        return 0;
    }
    printf("lxnet: %d failed\n", failures);
    return 1;
}
