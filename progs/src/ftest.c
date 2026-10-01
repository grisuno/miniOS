/* Exercises the kernel libc surface used by loaded .o programs:
 * fprintf to stdout/stderr, snprintf into a buffer, errno on a failed
 * open, and exit(). */
extern int   fprintf(void *stream, const char *fmt, ...);
extern int   snprintf(char *buf, unsigned long size, const char *fmt, ...);
extern int   printf(const char *fmt, ...);
extern void  exit(int code);
extern void *stdout;
extern void *stderr;
extern int   errno;
extern void *fopen(const char *path, const char *mode);

int main(int argc, char **argv) {
    char buf[64];
    volatile double a = 3.5, b = 2.0;      /* forces SSE2 (mulsd) */
    int sse = (int)(a * b);
    void *f;
    printf("sse: %d (expect 7)\n", sse);
    snprintf(buf, sizeof(buf), "snprintf=%d/%s", argc, argv[0]);
    fprintf(stderr, "stderr: argc=%d prog=%s\n", argc, argv[0]);
    fprintf(stdout, "stdout: %s\n", buf);
    f = fopen("no-such-xyz", "r");
    if (f) {
        printf("ftest: unexpected open\n");
        exit(8);
    }
    printf("ftest: errno=%d (expect 2)\n", errno);
    if (errno != 2) exit(9);
    printf("printf: done, calling exit(7)\n");
    exit(7);
    return 0;
}
