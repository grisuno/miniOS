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

/* Strict port parser (clang-tidy cert-err34-c: atoi reports no
 * errors, so "abc" and overflow both become 0 and fail open into the
 * default 443). All digits, at least one, value 1..65535, else -1. */
static int parse_port(const char *s) {
    long v = 0;
    int digits = 0;
    if (!s || !*s) return -1;
    while (*s >= '0' && *s <= '9') {
        v = v * 10 + (*s - '0');
        if (v > 65535) return -1;
        digits++;
        s++;
    }
    if (*s || !digits || v <= 0) return -1;
    return (int)v;
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
    if (argc > 3) {
        int p = parse_port(argv[3]);
        if (p < 0) {
            fprintf(stderr, "tlsget: bad port\n");
            return 2;
        }
        port = p;
    }
    if (tls_u_resolve(host, &ip) != 0) {
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
