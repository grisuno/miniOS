/* tls_u_port.c - ring-3 transport for the shared TLS stack (TLS_RING3).
 *
 * The kernel's net/tls*.c sources compile unchanged here; only this
 * file and tls_u_main.c are ring-3-specific. Transport is POSIX
 * sockets: on the host they are host sockets (used by the
 * openssl-s_server interop test), inside MiniOS glibc maps
 * socket/connect/send/recv/poll onto the kernel Linux ABI numbers
 * (41/42/44/45/7) the stack already serves. poll(7) - not select -
 * backs the read deadline because MiniOS implements poll, not select.
 */

#define _POSIX_C_SOURCE 200112L

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <poll.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int tls_u_send(int fd, const char *buf, int len) {
    int sent = 0;
    while (sent < len) {
        ssize_t r = send(fd, buf + sent, (size_t)(len - sent), 0);
        if (r <= 0) return -1;
        sent += (int)r;
    }
    return sent;
}

int tls_u_recv(int fd, char *buf, int len) {
    ssize_t r = recv(fd, buf, (size_t)len, 0);
    return (int)r;
}

int tls_u_recv_timeout(int fd, char *buf, int len, unsigned long ms) {
    struct pollfd pfd;
    int r;
    pfd.fd = fd;
    pfd.events = POLLIN;
    pfd.revents = 0;
    r = poll(&pfd, 1, (int)ms);
    if (r <= 0) return -1;
    return (int)recv(fd, buf, (size_t)len, 0);
}

void tls_u_close(int fd) {
    close(fd);
}

long tls_now_days(void) {
    struct timeval tv;
    if (gettimeofday(&tv, 0) != 0) return 0;
    return (long)(tv.tv_sec / 86400);
}

void tls_random(unsigned char *out, unsigned len) {
    int fd = open("/dev/urandom", O_RDONLY);
    unsigned got = 0;
    if (fd >= 0) {
        while (got < len) {
            ssize_t n = read(fd, out + got, len - got);
            if (n <= 0) break;
            got += (unsigned)n;
        }
        close(fd);
    }
    /* Fail-soft fallback (documented, same stance as the kernel TSC
     * mixer): time x pid x rand. Better than aborting the handshake. */
    while (got < len) {
        unsigned v = (unsigned)time(0) ^ ((unsigned)getpid() << 16) ^
                     (unsigned)rand();
        out[got++] = (unsigned char)(v & 255);
        if (got < len) out[got++] = (unsigned char)((v >> 8) & 255);
    }
}
