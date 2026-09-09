/*
 * pollready - regression test for net_sys_poll byte order.
 *
 * poll(7) used to read struct pollfd with big-endian wire readers, so it
 * never reported a socket readable (found by the ring-3 TLS client, whose
 * record deadline polls starved). This program connects to a host TCP
 * server, sends a minimal GET, polls 5 s for POLLIN and reports:
 *   POLL-READY   poll returned 1 with revents & POLLIN, exit 0
 *   POLL-NOTREADY otherwise, exit 1
 *
 * usage: pollready <ip-dotted-quad> <port>
 * Built -nostdlib like lxhello: raw syscall instructions only.
 */

static long p_syscall6(long n, long a1, long a2, long a3, long a4, long a5) {
    long ret;
    register long r10 __asm__("r10") = a4;
    register long r8 __asm__("r8") = a5;
    __asm__ volatile("syscall"
                     : "=a"(ret)
                     : "a"(n), "D"(a1), "S"(a2), "d"(a3), "r"(r10), "r"(r8)
                     : "rcx", "r11", "memory");
    return ret;
}

static long p_write(long fd, const char *s, long n) {
    return p_syscall6(1, fd, (long)s, n, 0, 0);
}

static unsigned long p_strlen(const char *s) {
    unsigned long n = 0;
    while (s[n]) n++;
    return n;
}

static void p_puts(long fd, const char *s) {
    p_write(fd, s, (long)p_strlen(s));
}

static int p_atoi(const char *s) {
    int v = 0;
    while (*s >= '0' && *s <= '9') { v = v * 10 + (*s - '0'); s++; }
    return v;
}

static int p_parse_ip(const char *s, unsigned char out[4]) {
    int i;
    for (i = 0; i < 4; i++) {
        int v = 0;
        int digits = 0;
        while (*s >= '0' && *s <= '9') { v = v * 10 + (*s - '0'); s++; digits++; }
        if (!digits || v > 255) return -1;
        out[i] = (unsigned char)v;
        if (i < 3) {
            if (*s != '.') return -1;
            s++;
        }
    }
    return *s ? -1 : 0;
}

/* Entry called by _start with argc/argv off the initial stack. */
int lmain(long argc, char **argv) {
    unsigned char ip[4];
    int port;
    long fd;
    unsigned char sa[16];
    int i;
    /* pollfd: int fd; short events; short revents (host order). */
    struct { int fd; short events; short revents; } pfd;
    long pr;
    static const char get[] = "GET / HTTP/1.0\r\n\r\n";
    char buf[64];
    long nr;

    if (argc < 3) {
        p_puts(2, "usage: pollready <ip> <port>\n");
        return 2;
    }
    if (p_parse_ip(argv[1], ip) != 0) {
        p_puts(2, "pollready: bad ip\n");
        return 2;
    }
    port = p_atoi(argv[2]);
    fd = p_syscall6(41, 2, 1, 0, 0, 0);
    if (fd < 0) {
        p_puts(2, "pollready: socket failed\n");
        return 1;
    }
    sa[0] = 2; sa[1] = 0;
    sa[2] = (unsigned char)((port >> 8) & 255);
    sa[3] = (unsigned char)(port & 255);
    for (i = 0; i < 4; i++) sa[4 + i] = ip[i];
    for (i = 8; i < 16; i++) sa[i] = 0;
    if (p_syscall6(42, fd, (long)sa, 16, 0, 0) != 0) {
        p_puts(2, "pollready: connect failed\n");
        return 1;
    }
    if (p_syscall6(44, fd, (long)get, (long)(sizeof(get) - 1), 0, 0) < 0) {
        p_puts(2, "pollready: send failed\n");
        return 1;
    }
    pfd.fd = (int)fd;
    pfd.events = 1;
    pfd.revents = 0;
    pr = p_syscall6(7, (long)&pfd, 1, 5000, 0, 0);
    if (pr == 1 && (pfd.revents & 1)) {
        nr = p_syscall6(45, fd, (long)buf, (long)sizeof(buf), 0, 0);
        if (nr > 0) {
            p_puts(1, "POLL-READY\n");
            return 0;
        }
        p_puts(2, "pollready: ready but recv failed\n");
        return 1;
    }
    p_puts(1, "POLL-NOTREADY\n");
    return 1;
}

__asm__(
    ".global _start\n"
    "_start:\n"
    "  movq (%rsp), %rdi\n"
    "  leaq 8(%rsp), %rsi\n"
    "  call lmain\n"
    "  movl %eax, %edi\n"
    "  movl $60, %eax\n"
    "  syscall\n"
    "  hlt\n"
);
