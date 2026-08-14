/*
 * lxhello — a genuine Linux x86-64 ELF executable.
 *
 * Built with `gcc -static -no-pie -nostdlib` so it links as ET_EXEC at
 * 0x400000 with a hand-written _start.  It never uses libc: it reads
 * argc/argv straight off the SysV initial stack and talks to the kernel
 * exclusively through the `syscall` instruction.  If MiniOS runs this and
 * prints the message, its ELF loader + Linux syscall ABI are working.
 */

static long lx_syscall3(long n, long a1, long a2, long a3) {
    long ret;
    __asm__ volatile("syscall"
                     : "=a"(ret)
                     : "a"(n), "D"(a1), "S"(a2), "d"(a3)
                     : "rcx", "r11", "memory");
    return ret;
}

#define SYS_write 1
#define SYS_exit  60

static unsigned long lx_strlen(const char *s) {
    unsigned long n = 0;
    while (s[n]) n++;
    return n;
}

static void lx_write(const char *s) {
    lx_syscall3(SYS_write, 1, (long)s, (long)lx_strlen(s));
}

static void lx_write_int(long v) {
    char buf[24];
    int i = (int)sizeof(buf);
    int neg = 0;
    buf[--i] = 0;
    if (v < 0) { neg = 1; v = -v; }
    if (v == 0) buf[--i] = '0';
    while (v > 0 && i > 0) { buf[--i] = (char)('0' + v % 10); v /= 10; }
    if (neg && i > 0) buf[--i] = '-';
    lx_write(&buf[i]);
}

/* Entry called by _start with the real argc/argv pulled off the stack. */
int lmain(long argc, char **argv) {
    long i;
    lx_write("Hello from a REAL Linux ELF executable (syscall ABI)!\n");
    lx_write("argc = ");
    lx_write_int(argc);
    lx_write("\n");
    for (i = 0; i < argc; i++) {
        lx_write("argv[");
        lx_write_int(i);
        lx_write("] = ");
        lx_write(argv[i]);
        lx_write("\n");
    }
    return (int)argc; /* becomes the process exit code */
}

__asm__(
    ".global _start\n"
    "_start:\n"
    "  movq (%rsp), %rdi\n"      /* argc */
    "  leaq 8(%rsp), %rsi\n"     /* argv */
    "  call lmain\n"
    "  movl %eax, %edi\n"        /* exit code = lmain() return */
    "  movl $60, %eax\n"         /* SYS_exit */
    "  syscall\n"
    "  hlt\n"
);
