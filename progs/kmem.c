/* Kernel-pointer rejection probe. Passes a kernel-heap address (0x2000000,
 * a supervisor page) to write(2). The hardened syscall boundary must reject
 * it with -EFAULT; the program exits 0 when the write was refused and 1
 * when the kernel wrongly dereferenced a kernel pointer on its behalf.
 * Built as a static Linux ELF like lxhello.elf. */
static long syscall3(long n, long a1, long a2, long a3) {
    long r;
    __asm__ volatile("syscall" : "=a"(r) : "a"(n), "D"(a1), "S"(a2), "d"(a3)
                     : "rcx", "r11", "memory");
    return r;
}

static void exit_now(long code) {
    __asm__ volatile("syscall" :: "a"(60), "D"(code) : "rcx", "r11", "memory");
}

void _start(void) {
    long r = syscall3(1, 1, 0x2000000L, 8); /* write(1, kernel heap, 8) */
    exit_now(r < 0 ? 0 : 1);
}