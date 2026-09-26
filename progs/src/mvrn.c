/* mvrn -- rename(82) syscall probe.
 *
 * Exercises the rename path a ring-3 program sees: create a file through
 * open/write/close, move it with rename(82), then pin the fail-closed
 * edges (missing src is -ENOENT, a kernel-space pointer is -EFAULT) and
 * clean up with unlink. Prints "mvrn: ok" and exits 0 only when every
 * step behaves; any deviation prints "mvrn: FAIL <step>" and exits 1.
 * Built as a static Linux ELF like lxhello.elf (no libc, raw syscalls). */
static long mvrn_sc3(long n, long a1, long a2, long a3) {
    long r;
    __asm__ volatile("syscall" : "=a"(r) : "a"(n), "D"(a1), "S"(a2), "d"(a3)
                     : "rcx", "r11", "memory");
    return r;
}

static void mvrn_write(const char *s, unsigned long len) {
    mvrn_sc3(1, 1, (long)s, (long)len);
}

static void mvrn_exit(long code) {
    __asm__ volatile("syscall" :: "a"(60), "D"(code) : "rcx", "r11", "memory");
}

static void mvrn_fail(int step) {
    char c = (char)('0' + step);
    mvrn_write("mvrn: FAIL ", 11);
    mvrn_write(&c, 1);
    mvrn_write("\n", 1);
    mvrn_exit(1);
}

int lmain(void) {
    long fd = mvrn_sc3(2, (long)"mvrn_old", 0101, 0644);
    if (fd < 0) mvrn_fail(1);
    if (mvrn_sc3(1, fd, (long)"data", 4) != 4) mvrn_fail(2);
    if (mvrn_sc3(3, fd, 0, 0) != 0) mvrn_fail(3);
    if (mvrn_sc3(82, (long)"mvrn_old", (long)"mvrn_new", 0) != 0) mvrn_fail(4);
    if (mvrn_sc3(82, (long)"mvrn_old", (long)"mvrn_new2", 0) != -2) mvrn_fail(5);
    if (mvrn_sc3(82, 0x0C100000L, (long)"mvrn_new2", 0) != -14) mvrn_fail(6);
    if (mvrn_sc3(87, (long)"mvrn_new", 0, 0) != 0) mvrn_fail(7);
    mvrn_write("mvrn: ok\n", 9);
    mvrn_exit(0);
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
