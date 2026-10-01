/* mprotect probe. Maps two anonymous regions and walks the protection
 * contract end to end: RW stays writable, RO stays readable, unaligned
 * addresses and unknown prot bits refuse with EINVAL, kernel-space
 * addresses refuse with ENOMEM, an R|X page executes, and a write to a
 * read-only page faults (the shell reports EXCEPTION 0e and no exit
 * code, exactly like the nx probe). Legs print in order so a failure
 * names itself; the killer write is last and must never return. Built
 * as a static Linux ELF like nx.elf and run through the syscall ABI. */
typedef void (*fn_t)(void);

static long mmap_anon(long len) {
    long r;
    register long a2 asm("rsi") = len;
    register long a3 asm("rdx") = 3;
    register long a4 asm("r10") = 0x22;
    register long a5 asm("r8")  = -1;
    register long a6 asm("r9")  = 0;
    __asm__ volatile("syscall"
        : "=a"(r)
        : "0"(9), "D"(0), "r"(a2), "r"(a3), "r"(a4), "r"(a5), "r"(a6)
        : "rcx", "r11", "memory");
    return r;
}

static long mprotect_sys(long addr, long len, long prot) {
    long r;
    register long a2 asm("rsi") = len;
    register long a3 asm("rdx") = prot;
    __asm__ volatile("syscall"
        : "=a"(r)
        : "0"(10), "D"(addr), "r"(a2), "r"(a3)
        : "rcx", "r11", "memory");
    return r;
}

static long write_str(const char *s, long n) {
    long r;
    __asm__ volatile("syscall" : "=a"(r)
                     : "a"(1), "D"(1), "S"(s), "d"(n)
                     : "rcx", "r11", "memory");
    return r;
}

static void exit_now(long code) {
    __asm__ volatile("syscall" :: "a"(60), "D"(code) : "rcx", "r11", "memory");
}

void _start(void) {
    long p = mmap_anon(8192);
    long q = mmap_anon(4096);
    volatile char *m;
    volatile char *x;
    fn_t fn;
    if (p < 0 || q < 0) exit_now(10);
    m = (volatile char *)p;
    x = (volatile char *)q;
    m[0] = 1;
    m[4096] = 2;
    m[8191] = 3;
    if (mprotect_sys(p, 8192, 3) != 0) exit_now(11);
    m[0] = 4;
    if (mprotect_sys(p, 8192, 1) != 0) exit_now(12);
    if (m[0] != 4 || m[4096] != 2 || m[8191] != 3) exit_now(13);
    if (mprotect_sys(p + 1, 8192, 1) != -22) exit_now(14);
    if (mprotect_sys(p, 8192, 8) != -22) exit_now(15);
    if (mprotect_sys((long)0xFFFF800000000000UL, 4096, 1) != -12) exit_now(16);
    write_str("mprot: legs ok\n", 15);
    x[0] = (char)0xC3;
    if (mprotect_sys(q, 4096, 5) != 0) exit_now(17);
    fn = (fn_t)(unsigned long)(void *)x;
    fn();
    write_str("mprot: exec ok\n", 15);
    if (mprotect_sys(p, 8192, 1) != 0) exit_now(18);
    write_str("mprot: protecting\n", 18);
    m[0] = 9;
    exit_now(0);
}
