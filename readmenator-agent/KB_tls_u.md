# Subsystem: tls_u

## progs/tls_u/tls_u_main.c
- Layer: utility
- Doc: tlsget - minimal HTTPS GET over the ring-3 TLS stack.
- Language: c
- Symbols:
  - `syscall` (function, line 10) `* the MiniOS DNS syscall (200, sig 0: error-check only, sends nothing).
 * The kernel keeps servi...`
  - `resolve` (function, line 48) `static int resolve(const char *host, unsigned *ip_out)`
  - `main` (function, line 72) `int main(int argc, char **argv)`
  - `volatile` (function, line 32) `__asm__ volatile("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2), "d"(a3) : "rcx", "r11", "memory");`
  - `memset` (function, line 60) `memset(&hints, 0, sizeof(hints));`
  - `freeaddrinfo` (function, line 66) `freeaddrinfo(res);`
  - `minios_dns` (function, line 70) `return minios_dns(host, ip_out);`
  - `fprintf` (function, line 87) `fprintf(stderr, "usage: tlsget <host-or-ip> [path] [port]\n");`
  - `perror` (function, line 103) `perror("tlsget: socket");`
  - `close` (function, line 112) `close(fd);`
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
  - `tls_u_recv` (function, line 34) `int tls_u_recv(int fd, char *buf, int len)`
  - `tls_u_recv_timeout` (function, line 39) `int tls_u_recv_timeout(int fd, char *buf, int len, unsigned long ms)`
  - `tls_u_close` (function, line 50) `void tls_u_close(int fd)`
  - `tls_now_days` (function, line 54) `long tls_now_days(void)`
  - `tls_random` (function, line 60) `void tls_random(unsigned char *out, unsigned len)`
  - `close` (function, line 52) `close(fd);`
  - `_POSIX_C_SOURCE` (macro, line 11) `#define _POSIX_C_SOURCE`
- Depends on: `kernel/string.c`, `kernel/time.c`
