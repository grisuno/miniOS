/* aslr -- userspace ASLR probe (self-exec chain).
 *
 * gen0 (no args) prints its stack pointer, brk and first-mmap address,
 * then execve()s itself carrying those three values. gen1 compares its
 * own addresses against the parent's: stack top slides per exec, brk
 * starts past a random pad, the mmap cursor starts slid down. Any one
 * dimension differing proves fresh entropy; identical triples mean the
 * mixer is dead. Prints "aslr: ok" (exit 0) or "aslr: SAME" (exit 1).
 * Built as a static Linux ELF like execho.elf. */
static long as_sc(long n, long a1, long a2, long a3) {
    long r;
    __asm__ volatile("syscall" : "=a"(r) : "a"(n), "D"(a1), "S"(a2),
                     "d"(a3)
                     : "rcx", "r11", "memory");
    return r;
}

static long as_mmap(void) {
    register long r10 __asm__("r10") = 0x22;
    register long r8 __asm__("r8") = -1;
    register long r9 __asm__("r9") = 0;
    long r;
    __asm__ volatile("syscall"
                     : "=a"(r)
                     : "a"(9), "D"(0), "S"(4096), "d"(3), "r"(r10),
                       "r"(r8), "r"(r9)
                     : "rcx", "r11", "memory");
    return r;
}

static void as_write(const char *s, unsigned long len) {
    as_sc(1, 1, (long)s, (long)len);
}

static void as_exit(long code) {
    __asm__ volatile("syscall" :: "a"(60), "D"(code) : "rcx", "r11",
                     "memory");
}

static void as_execve(const char *path, const char **argv) {
    long r;
    __asm__ volatile("syscall" : "=a"(r) : "a"(59), "D"(path), "S"(argv)
                     : "rcx", "r11", "memory");
    (void)r;
}

static void as_putu(unsigned long v) {
    char buf[24];
    int i = (int)sizeof(buf);
    buf[--i] = 0;
    if (v == 0) buf[--i] = '0';
    while (v > 0 && i > 0) {
        buf[--i] = (char)('0' + v % 10);
        v /= 10;
    }
    as_write(&buf[i], (unsigned long)(sizeof(buf) - 1 - i));
}

static unsigned long as_atou(const char *s) {
    unsigned long v = 0;
    while (*s >= '0' && *s <= '9') {
        v = v * 10 + (unsigned long)(*s - '0');
        s++;
    }
    return v;
}

static unsigned long as_rsp(void) {
    unsigned long r;
    __asm__ volatile("mov %%rsp, %0" : "=r"(r));
    return r;
}

static void as_fail(int step) {
    char c = (char)('0' + step);
    as_write("aslr: FAIL ", 11);
    as_write(&c, 1);
    as_write("\n", 1);
    as_exit(1);
}

int lmain(long argc, char **argv) {
    unsigned long sp = as_rsp();
    long brk = as_sc(12, 0, 0, 0);
    long mm = as_mmap();
    if (brk <= 0 || mm <= 0) as_fail(1);
    if (argc >= 4) {
        unsigned long psp = as_atou(argv[1]);
        unsigned long pbrk = as_atou(argv[2]);
        unsigned long pmm = as_atou(argv[3]);
        as_write("aslr: gen1 sp=", 14);
        as_putu(sp);
        as_write(" brk=", 5);
        as_putu((unsigned long)brk);
        as_write(" mm=", 4);
        as_putu((unsigned long)mm);
        as_write("\n", 1);
        if (sp != psp || (unsigned long)brk != pbrk ||
            (unsigned long)mm != pmm) {
            as_write("aslr: ok\n", 9);
            return 0;
        }
        as_write("aslr: SAME\n", 11);
        return 1;
    }
    as_write("aslr: gen0 sp=", 14);
    as_putu(sp);
    as_write(" brk=", 5);
    as_putu((unsigned long)brk);
    as_write(" mm=", 4);
    as_putu((unsigned long)mm);
    as_write("\n", 1);
    {
        static char ssp[24], sbrk[24], smm[24];
        const char *args[5];
        unsigned long v;
        int i, j;
        v = sp;
        i = (int)sizeof(ssp);
        ssp[--i] = 0;
        if (v == 0) ssp[--i] = '0';
        while (v > 0 && i > 0) {
            ssp[--i] = (char)('0' + v % 10);
            v /= 10;
        }
        for (j = 0; ssp[i + j]; j++)
            ssp[j] = ssp[i + j];
        ssp[j] = 0;
        v = (unsigned long)brk;
        i = (int)sizeof(sbrk);
        sbrk[--i] = 0;
        if (v == 0) sbrk[--i] = '0';
        while (v > 0 && i > 0) {
            sbrk[--i] = (char)('0' + v % 10);
            v /= 10;
        }
        for (j = 0; sbrk[i + j]; j++)
            sbrk[j] = sbrk[i + j];
        sbrk[j] = 0;
        v = (unsigned long)mm;
        i = (int)sizeof(smm);
        smm[--i] = 0;
        if (v == 0) smm[--i] = '0';
        while (v > 0 && i > 0) {
            smm[--i] = (char)('0' + v % 10);
            v /= 10;
        }
        for (j = 0; smm[i + j]; j++)
            smm[j] = smm[i + j];
        smm[j] = 0;
        args[0] = "bin/aslr.elf";
        args[1] = ssp;
        args[2] = sbrk;
        args[3] = smm;
        args[4] = 0;
        as_execve("bin/aslr.elf", args);
        as_fail(2);
    }
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
