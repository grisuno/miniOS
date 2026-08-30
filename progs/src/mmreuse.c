/* mmap/munmap reclaim stress test.  Repeatedly maps and unmaps a large
 * region.  On a kernel whose munmap never returns address space, the
 * downward mmap cursor drains until a map fails with ENOMEM (-12); with
 * reclaim the freed region is reused and no map ever fails.  Exit code 0 =
 * pass, 1 = a map failed (the leak it guards against).  Built as a static
 * Linux ELF like cpl.elf and run through the raw syscall ABI. */
static long mmap_anon(long len) {
    long r;
    register long a2 asm("rsi") = len;
    register long a3 asm("rdx") = 3;         /* PROT_READ|PROT_WRITE */
    register long a4 asm("r10") = 0x22;      /* MAP_PRIVATE|MAP_ANONYMOUS */
    register long a5 asm("r8")  = -1;
    register long a6 asm("r9")  = 0;
    __asm__ volatile("syscall"
        : "=a"(r)
        : "0"(9), "D"(0), "r"(a2), "r"(a3), "r"(a4), "r"(a5), "r"(a6)
        : "rcx", "r11", "memory");
    return r;
}

static long munmap(long addr, long len) {
    long r;
    register long a2 asm("rsi") = len;
    __asm__ volatile("syscall"
        : "=a"(r)
        : "0"(11), "D"(addr), "r"(a2)
        : "rcx", "r11", "memory");
    return r;
}

static void exit_now(long code) {
    __asm__ volatile("syscall" :: "a"(60), "D"(code) : "rcx", "r11", "memory");
}

void _start(void) {
    long size = 8 * 1024 * 1024;
    long i;
    for (i = 0; i < 64; i++) {
        long p = mmap_anon(size);
        if (p < 0) exit_now(1);       /* ENOMEM: the leak this guards against */
        *((volatile long *)p) = i;    /* touch the region so it is really used */
        if (munmap(p, size) != 0) exit_now(2);
    }
    exit_now(0);
}
