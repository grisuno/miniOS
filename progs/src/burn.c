/* burn -- SMP mixed-workload probe: brk plus mmap plus CPU burn with
 * a deterministic checksum. Concurrent isolated copies must all print
 * the same sum and exit 0; a corrupted brk view, an aliased mmap or a
 * torn page changes the sum or faults before it prints. Built as a
 * static Linux ELF like aslr.elf. */
static long bn_sc(long n, long a1, long a2, long a3) {
    long r;
    __asm__ volatile("syscall" : "=a"(r) : "a"(n), "D"(a1), "S"(a2),
                     "d"(a3)
                     : "rcx", "r11", "memory");
    return r;
}

static long bn_mmap(unsigned long len) {
    register long r10 __asm__("r10") = 0x22;
    register long r8 __asm__("r8") = -1;
    register long r9 __asm__("r9") = 0;
    long r;
    __asm__ volatile("syscall"
                     : "=a"(r)
                     : "a"(9), "D"(0), "S"(len), "d"(3), "r"(r10),
                       "r"(r8), "r"(r9)
                     : "rcx", "r11", "memory");
    return r;
}

static void bn_write(const char *s, unsigned long len) {
    bn_sc(1, 1, (long)s, (long)len);
}

static void bn_exit(long code) {
    __asm__ volatile("syscall" :: "a"(60), "D"(code) : "rcx", "r11",
                     "memory");
}

static void bn_putu(unsigned long v) {
    char buf[24];
    int i = (int)sizeof(buf);
    buf[--i] = 0;
    if (v == 0) buf[--i] = '0';
    while (v > 0 && i > 0) {
        buf[--i] = (char)('0' + v % 10);
        v /= 10;
    }
    bn_write(&buf[i], (unsigned long)(sizeof(buf) - 1 - i));
}

static void bn_fail(void) {
    bn_write("burn: FAIL\n", 11);
    bn_exit(1);
}

int lmain(void) {
    long cur = bn_sc(12, 0, 0, 0);
    long nb;
    long mm;
    unsigned long sum = 0;
    unsigned long i;
    unsigned char *p;
    if (cur <= 0) bn_fail();
    nb = bn_sc(12, cur + 0x100000L, 0, 0);
    if (nb != cur + 0x100000L) bn_fail();
    for (i = 0; i < 0x100000UL; i++) {
        unsigned char v = (unsigned char)(i & 255);
        ((unsigned char *)cur)[i] = v;
        sum += v;
    }
    mm = bn_mmap(0x100000UL);
    if (mm <= 0) bn_fail();
    p = (unsigned char *)mm;
    for (i = 0; i < 0x100000UL; i++) {
        unsigned char v = (unsigned char)((i * 7) & 255);
        p[i] = v;
        sum += v;
    }
    for (i = 0; i < 20000000UL; i++) sum += i & 15;
    for (i = 0; i < 0x100000UL; i++) {
        if (((unsigned char *)cur)[i] != (unsigned char)(i & 255))
            bn_fail();
        if (p[i] != (unsigned char)((i * 7) & 255)) bn_fail();
    }
    bn_write("burn: done ", 11);
    bn_putu(sum);
    bn_write("\n", 1);
    bn_exit(0);
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
