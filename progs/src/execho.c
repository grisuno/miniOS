/* execho -- fork(57) + execve(59) + wait4(61) probe.
 *
 * Proves the UNIX process composition the kernel lacked: a child
 * produced by fork replaces its image with execve and the parent
 * reaps the REPLACED program (not a clone). First child execs
 * bin/lxhello.elf (prints Hello, exits with argc=2); second child
 * execs a ghost path (must fail -2, exits 42). The parent checks
 * both statuses and prints "execho: ok" with exit 0 only when the
 * whole chain behaves. Built as a static Linux ELF like mvrn.elf. */
static long ex_sc(long n, long a1, long a2, long a3, long a4) {
    long r;
    __asm__ volatile("syscall" : "=a"(r) : "a"(n), "D"(a1), "S"(a2),
                     "d"(a3), "r"(a4)
                     : "rcx", "r11", "memory");
    return r;
}

static void ex_write(const char *s, unsigned long len) {
    ex_sc(1, 1, (long)s, (long)len, 0);
}

static void ex_exit(long code) {
    __asm__ volatile("syscall" :: "a"(60), "D"(code) : "rcx", "r11",
                     "memory");
}

static void ex_fail(int step) {
    char c = (char)('0' + step);
    ex_write("execho: FAIL ", 13);
    ex_write(&c, 1);
    ex_write("\n", 1);
    ex_exit(1);
}

int lmain(void) {
    long pid;
    long st = 0;
    long rc;
    static const char *args1[3];
    args1[0] = "bin/lxhello.elf";
    args1[1] = "hi";
    args1[2] = 0;
    pid = ex_sc(57, 0, 0, 0, 0);
    if (pid < 0) ex_fail(1);
    if (pid == 0) {
        ex_sc(59, (long)"bin/lxhello.elf", (long)args1, 0, 0);
        ex_exit(99);
    }
    rc = ex_sc(61, -1, (long)&st, 0, 0);
    if (rc != 2 || st != 2) ex_fail(2);
    pid = ex_sc(57, 0, 0, 0, 0);
    if (pid < 0) ex_fail(3);
    if (pid == 0) {
        rc = ex_sc(59, (long)"bin/ghost.elf", (long)args1, 0, 0);
        if (rc != -2) ex_exit(98);
        ex_exit(42);
    }
    st = 0;
    rc = ex_sc(61, -1, (long)&st, 0, 0);
    if (rc != 42 || st != 42) ex_fail(4);
    ex_write("execho: ok\n", 11);
    ex_exit(0);
    return 0;
}

__asm__(
    ".global _start\n"
    "_start:\n"
    "  call lmain\n"
    "  movl %eax, %edi\n"
    "  movl $60, %eax\n"
    "  syscall\n"
    "  hlt\n"
);
