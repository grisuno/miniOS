/* Exercises the kernel libc surface used by loaded .o programs:
 * fprintf to stdout/stderr, snprintf into a buffer, and exit(). */
extern int   fprintf(void *stream, const char *fmt, ...);
extern int   snprintf(char *buf, unsigned long size, const char *fmt, ...);
extern int   printf(const char *fmt, ...);
extern void  exit(int code);
extern void *stdout;
extern void *stderr;

int main(int argc, char **argv) {
    char buf[64];
    volatile double a = 3.5, b = 2.0;      /* forces SSE2 (mulsd) */
    int sse = (int)(a * b);
    printf("sse: %d (expect 7)\n", sse);
    snprintf(buf, sizeof(buf), "snprintf=%d/%s", argc, argv[0]);
    fprintf(stderr, "stderr: argc=%d prog=%s\n", argc, argv[0]);
    fprintf(stdout, "stdout: %s\n", buf);
    printf("printf: done, calling exit(7)\n");
    exit(7);
    return 0;
}
