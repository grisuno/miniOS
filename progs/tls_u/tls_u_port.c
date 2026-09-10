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

#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
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

/* Session-aware close for multi-fetch processes (freedom follows
 * redirects and linked stylesheets, reusing the lowest free fd number
 * every time). The engine keys sessions by raw fd and only clears the
 * slot on handshake error; a successful session lives until someone
 * frees it, so plain close() leaks the slot and the next handshake on
 * the recycled fd number fails with "session already exists". Freeing
 * an fd with no session is a safe no-op. */
void tls_free_fd(int fd); /* session table owner: net/tls.c */
void tls_close(int fd) {
    tls_free_fd(fd);
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

static long u_raw_syscall3(long n, long a1, long a2, long a3) {
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
static int u_minios_dns(const char *host, unsigned *ip_out) {
    long r = u_raw_syscall3(200, (long)host, 0, 0);
    if (r <= 0 || r == (long)0xFFFFFFFFFFFFFFF2L) return -1;
    *ip_out = (unsigned)r;
    return 0;
}

/* Strict dotted-quad parser (clang-tidy cert-err34-c: sscanf %u has
 * undefined overflow and accepts whitespace/sign, so "9999999999.1.1.1"
 * is UB before the <256 check ever runs). Digits and dots only, four
 * octets 0..255, full-string consumption, else -1. */
static int parse_quad(const char *s, unsigned *ip_out) {
    unsigned ip = 0;
    int i;
    if (!s || !*s) return -1;
    for (i = 0; i < 4; i++) {
        unsigned v = 0;
        int digits = 0;
        while (*s >= '0' && *s <= '9') {
            v = v * 10 + (unsigned)(*s - '0');
            if (v > 255) return -1;
            digits++;
            s++;
        }
        if (!digits) return -1;
        ip = (ip << 8) | v;
        if (i < 3) {
            if (*s != '.') return -1;
            s++;
        }
    }
    if (*s) return -1;
    *ip_out = ip;
    return 0;
}

int tls_u_resolve(const char *host, unsigned *ip_out) {
    struct addrinfo hints;
    struct addrinfo *res = 0;
    struct sockaddr_in *sin;
    if (parse_quad(host, ip_out) == 0) return 0;
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
    /* IPv4-only stack: retry family-agnostic and take the first AF_INET
     * answer (some resolvers go IPv6-only on the first query). */
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(host, 0, &hints, &res) == 0 && res) {
        struct addrinfo *r;
        for (r = res; r; r = r->ai_next) {
            if (r->ai_family == AF_INET && r->ai_addr) {
                sin = (struct sockaddr_in *)r->ai_addr;
                *ip_out = ntohl(sin->sin_addr.s_addr);
                freeaddrinfo(res);
                return 0;
            }
        }
        freeaddrinfo(res);
    }
    return u_minios_dns(host, ip_out);
}

/* freedom's resolver name: kernel DNS value semantics (u32 host order,
 * -1 on failure). */
int net_dns_resolve(const char *host) {
    unsigned ip;
    if (tls_u_resolve(host, &ip) != 0) return -1;
    return (int)ip;
}
