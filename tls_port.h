#ifndef TLS_PORT_H
#define TLS_PORT_H

/* Portability shim between the MiniOS kernel and the host-side test
 * build. All three TLS files include this instead of kernel headers, so
 * `make test-tls` compiles the exact same sources against the host libc.
 */

#ifdef TLS_TEST

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

#define TLS_FD_MAX        16

#define TLS_PRINTF        printf
#define TLS_MALLOC(n)     malloc((size_t)(n))
#define TLS_FREE(p)       free(p)
#define TLS_MEMCPY        memcpy
#define TLS_MEMSET        memset
#define TLS_MEMCMP        memcmp
#define TLS_STRLEN        strlen

/* Transport: the host test links its own POSIX-socket implementations
 * of these (tls_test.c). */
extern int  tls_test_send(int fd, const char *buf, int len);
extern int  tls_test_recv(int fd, char *buf, int len);
extern int  tls_test_recv_timeout(int fd, char *buf, int len, unsigned long ms);
extern void tls_test_close(int fd);

#define TLS_SEND           tls_test_send
#define TLS_RECV           tls_test_recv
#define TLS_RECV_TIMEOUT   tls_test_recv_timeout
#define TLS_CLOSE          tls_test_close

static inline long tls_now_days(void) {
    return (long)(time(0) / 86400);
}

static inline void tls_random(unsigned char *out, unsigned len) {
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
    while (got < len) out[got++] = (unsigned char)(rand() & 255);
}

#else /* MiniOS kernel */

#include "kernel.h"
#include "net.h"

#define TLS_PRINTF        kprintf
#define TLS_MALLOC(n)     kmalloc((unsigned long)(n))
#define TLS_FREE(p)       kfree(p)
#define TLS_MEMCPY        kmemcpy
#define TLS_MEMSET        kmemset
#define TLS_MEMCMP        kmemcmp
#define TLS_STRLEN        kstrlen

#define TLS_SEND           net_send
#define TLS_RECV           net_recv
#define TLS_RECV_TIMEOUT   net_recv_timeout
#define TLS_CLOSE          net_close
#define TLS_FD_MAX         NET_SOCKETS

/* Implemented in tls.c: current date as days since 1970-01-01 (CMOS RTC)
 * and best-effort entropy (TSC + network counters). */
long tls_now_days(void);
void tls_random(unsigned char *out, unsigned len);

#endif /* TLS_TEST */

#endif
