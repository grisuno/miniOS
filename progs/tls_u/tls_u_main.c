/* tlsget - minimal HTTPS GET over the ring-3 TLS stack.
 *
 * Phase 1 of the TLS-to-userspace migration (see docs/TLS_MIGRATION.md):
 * the same net/tls*.c sources the kernel serves on syscalls 201-203 now
 * run here, in a static ET_EXEC, without touching key material in ring 0.
 *
 * usage: tlsget <host-or-ip> [path] [port]
 *
 * Resolution order: dotted quad, then getaddrinfo (host dev loop), then
 * the MiniOS DNS syscall (200, sig 0: error-check only, sends nothing).
 * The kernel keeps serving 201-203 for freedom until phase 2 relinks it.
 */

#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "tls_port.h"
#include "tls.h"

static long raw_syscall3(long n, long a1, long a2, long a3) {
    long ret;
    __asm__ volatile("syscall"
                     : "=a"(ret)
                     : "a"(n), "D"(a1), "S"(a2), "d"(a3)
                     : "rcx", "r11", "memory");
    return ret;
}

/* MiniOS DNS syscall 200 with sig-style safety: only ever invoked as
 * syscall(200, host, 0, 0), so on a host kernel (where 200 is tkill)
 * the signal argument is 0, which sends nothing and returns an error. */
static int minios_dns(const char *host, unsigned *ip_out) {
    long r = raw_syscall3(200, (long)host, 0, 0);
    if (r <= 0 || r == (long)0xFFFFFFFFFFFFFFF2L) return -1;
    *ip_out = (unsigned)r;
    return 0;
}

static int resolve(const char *host, unsigned *ip_out) {
    unsigned a, b, c, d;
    char tail;
    struct addrinfo hints;
    struct addrinfo *res = 0;
    struct sockaddr_in *sin;
    if (sscanf(host, "%u.%u.%u.%u%c", &a, &b, &c, &d, &tail) == 4 &&
        a < 256 && b < 256 && c < 256 && d < 256) {
        *ip_out = (a << 24) | (b << 16) | (c << 8) | d;
        return 0;
    }
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(host, 0, &hints, &res) == 0 && res) {
        sin = (struct sockaddr_in *)res->ai_addr;
        *ip_out = ntohl(sin->sin_addr.s_addr);
        freeaddrinfo(res);
        return 0;
    }
    if (res) freeaddrinfo(res);
    return minios_dns(host, ip_out);
}

int main(int argc, char **argv) {
    const char *host;
    const char *path = "/";
    int port = 443;
    unsigned ip;
    int fd;
    struct sockaddr_in sa;
    char req[512];
    char body[8192];
    int n;
    long total = 0;
    int rlen;

    if (argc < 2) {
        fprintf(stderr, "usage: tlsget <host-or-ip> [path] [port]\n");
        return 2;
    }
    host = argv[1];
    if (argc > 2) path = argv[2];
    if (argc > 3) port = atoi(argv[3]);
    if (port <= 0 || port > 65535) {
        fprintf(stderr, "tlsget: bad port\n");
        return 2;
    }
    if (resolve(host, &ip) != 0) {
        fprintf(stderr, "tlsget: cannot resolve %s\n", host);
        return 1;
    }
    fd = (int)socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("tlsget: socket");
        return 1;
    }
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons((unsigned short)port);
    sa.sin_addr.s_addr = htonl(ip);
    if (connect(fd, (struct sockaddr *)&sa, sizeof(sa)) != 0) {
        perror("tlsget: connect");
        close(fd);
        return 1;
    }
    if (tls_handshake(fd, host) != 0) {
        fprintf(stderr, "tlsget: handshake failed\n");
        close(fd);
        return 1;
    }
    rlen = snprintf(req, sizeof(req),
                    "GET %s HTTP/1.0\r\nHost: %s\r\n"
                    "User-Agent: MiniOS-tlsget/1.0\r\n"
                    "Connection: close\r\n\r\n",
                    path, host);
    if (rlen <= 0 || rlen >= (int)sizeof(req)) {
        fprintf(stderr, "tlsget: request too long\n");
        close(fd);
        return 1;
    }
    if (tls_send(fd, req, rlen) != rlen) {
        fprintf(stderr, "tlsget: send failed\n");
        close(fd);
        return 1;
    }
    for (;;) {
        n = tls_recv(fd, body, (int)sizeof(body));
        if (n < 0) {
            fprintf(stderr, "tlsget: recv failed\n");
            close(fd);
            return 1;
        }
        if (n == 0) break;
        total += n;
        if (fwrite(body, 1, (size_t)n, stdout) != (size_t)n) {
            fprintf(stderr, "tlsget: stdout failed\n");
            close(fd);
            return 1;
        }
    }
    close(fd);
    fprintf(stderr, "tlsget: %s (%ld bytes)\n", host, total);
    return 0;
}
