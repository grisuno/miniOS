/* Minimal HTTP/1.0 GET through the Linux socket syscalls.
 * usage: http <host> <port> [path]
 * Hostnames are resolved by the kernel (net_dns_resolve syscall).
 */
int socket(int domain, int type, int proto);
int connect(int fd, void *addr, int addrlen);
int sendto(int fd, char *buf, int len, int flags, void *to, int tolen);
int recvfrom(int fd, char *buf, int len, int flags, void *from, int *fromlen);
int shutdown(int fd, int how);
int close(int fd);
int net_dns_resolve(char *host);
int puts(char *s);
int printf(char *fmt, ...);
int strlen(char *s);
int putchar(int c);

/* Decimal string to int (the ld stub set has no atol). */
int atoi(char *s) {
    int v, i;
    v = 0;
    i = 0;
    while (s[i] >= '0' && s[i] <= '9') {
        v = v * 10 + (s[i] - '0');
        i++;
    }
    return v;
}

int main(int argc, char **argv) {
    char *req = "GET ";
    char *req2 = " HTTP/1.0\r\n\r\n";
    char buf[512];
    char sa[16];
    int fd, n, total, i, ip, port;
    if (argc < 3) {
        puts("usage: http <host> <port> [path]");
        return 1;
    }
    ip = net_dns_resolve(argv[1]);
    if (ip < 0) {
        puts("dns failed");
        return 2;
    }
    fd = socket(2, 1, 0);
    if (fd < 0) {
        puts("socket failed");
        return 3;
    }
    port = atoi(argv[2]);
    sa[0] = 2;
    sa[1] = 0;
    sa[2] = (port >> 8) & 255;
    sa[3] = port & 255;
    sa[4] = (ip >> 24) & 255;
    sa[5] = (ip >> 16) & 255;
    sa[6] = (ip >> 8) & 255;
    sa[7] = ip & 255;
    if (connect(fd, sa, 16) < 0) {
        puts("connect failed");
        return 4;
    }
    sendto(fd, req, 4, 0, 0, 0);
    if (argc > 3) {
        sendto(fd, argv[3], strlen(argv[3]), 0, 0, 0);
    } else {
        sendto(fd, "/", 1, 0, 0, 0);
    }
    sendto(fd, req2, 13, 0, 0, 0);
    total = 0;
    for (;;) {
        n = recvfrom(fd, buf, sizeof(buf), 0, 0, 0);
        if (n <= 0) break;
        for (i = 0; i < n; i++) putchar(buf[i]);
        total += n;
    }
    close(fd);
    printf("\nreceived %d bytes\n", total);
    return 0;
}
