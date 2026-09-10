# Subsystem: tls_u

## progs/tls_u/tls_u_main.c
- Layer: utility
- Doc: tlsget - minimal HTTPS GET over the ring-3 TLS stack.
- Language: c
- Symbols:
  - `syscall` (function, line 10) `* the MiniOS DNS syscall (200, sig 0: error-check only, sends nothing).
 * The kernel keeps servi...`
  - `parse_port` (function, line 47) `static int parse_port(const char *s)`
  - `main` (function, line 60) `int main(int argc, char **argv)`
  - `va_start` (function, line 38) `va_start(ap, fmt);`
  - `va_end` (function, line 40) `va_end(ap);`
  - `diag` (function, line 75) `diag("usage: tlsget <host-or-ip> [path] [port]\n");`
  - `perror` (function, line 94) `perror("tlsget: socket");`
  - `memset` (function, line 97) `memset(&sa, 0, sizeof(sa));`
  - `close` (function, line 103) `close(fd);`
  - `_POSIX_C_SOURCE` (macro, line 13) `#define _POSIX_C_SOURCE`
  - `_DEFAULT_SOURCE` (macro, line 15) `#define _DEFAULT_SOURCE`
- Depends on: `kernel/string.c`, `tls.h`, `tls_port.h`

## progs/tls_u/tls_u_port.c
- Layer: utility
- Doc: tls_u_port.c - ring-3 transport for the shared TLS stack (TLS_RING3).
- Language: c
- Symbols:
  - `sockets` (function, line 5) `* sockets: on the host they are host sockets (used by the
 * openssl-s_server interop test), insi...`
  - `tls_u_recv` (function, line 38) `int tls_u_recv(int fd, char *buf, int len)`
  - `tls_u_recv_timeout` (function, line 43) `int tls_u_recv_timeout(int fd, char *buf, int len, unsigned long ms)`
  - `tls_u_close` (function, line 54) `void tls_u_close(int fd)`
  - `tls_close` (function, line 67) `void tls_close(int fd)`
  - `tls_now_days` (function, line 71) `long tls_now_days(void)`
  - `tls_random` (function, line 77) `void tls_random(unsigned char *out, unsigned len)`
  - `u_raw_syscall3` (function, line 98) `static long u_raw_syscall3(long n, long a1, long a2, long a3)`
  - `parse_quad` (function, line 122) `static int parse_quad(const char *s, unsigned *ip_out)`
  - `tls_u_resolve` (function, line 146) `int tls_u_resolve(const char *host, unsigned *ip_out)`
  - `net_dns_resolve` (function, line 183) `int net_dns_resolve(const char *host)`
  - `close` (function, line 56) `close(fd);`
  - `tls_free_fd` (function, line 66) `void tls_free_fd(int fd);`
  - `volatile` (function, line 101) `__asm__ volatile("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2), "d"(a3) : "rcx", "r11", "memory");`
  - `memset` (function, line 152) `memset(&hints, 0, sizeof(hints));`
  - `freeaddrinfo` (function, line 158) `freeaddrinfo(res);`
  - `answer` (function, line 163) `* answer (some resolvers go IPv6-only on the first query). */ memset(&hints, 0, sizeof(hints));`
  - `u_minios_dns` (function, line 178) `return u_minios_dns(host, ip_out);`
  - `_POSIX_C_SOURCE` (macro, line 11) `#define _POSIX_C_SOURCE`
  - `_DEFAULT_SOURCE` (macro, line 13) `#define _DEFAULT_SOURCE`
- Depends on: `kernel/string.c`, `kernel/time.c`
