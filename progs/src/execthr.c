/* execthr -- execve kills sibling threads (Linux semantics).
 *
 * Main spawns one thread that spins forever, then execve()s
 * bin/lxhello.elf. The thread must die with the old image: lxhello
 * prints Hello and exits 2, mrun reports it, and no fault or hang
 * follows. A kernel that frees the old window under the live thread
 * faults or wedges instead. The dead thread stays a zombie of the
 * exec'd program (no reparenting in v1), so each run costs one proc
 * slot; test-only, never a server pattern. Built as a static Linux
 * ELF like execho.elf. */
static long et_sc(long n, long a1, long a2, long a3) {
    long r;
    __asm__ volatile("syscall" : "=a"(r) : "a"(n), "D"(a1), "S"(a2),
                     "d"(a3)
                     : "rcx", "r11", "memory");
    return r;
}

static void et_exit(long code) {
    __asm__ volatile("syscall" :: "a"(60), "D"(code) : "rcx", "r11",
                     "memory");
}

static volatile long et_flag = 0;
static char et_stack[8192];

static void et_thread(void) {
    while (!et_flag)
        et_sc(24, 0, 0, 0);
    et_exit(3);
}

int lmain(void) {
    static const char *args[3];
    long tid;
    args[0] = "bin/lxhello.elf";
    args[1] = "hi";
    args[2] = 0;
    tid = et_sc(225, (long)et_thread,
                (long)(et_stack + sizeof(et_stack) - 8), 0);
    if (tid < 0)
        et_exit(4);
    et_sc(59, (long)"bin/lxhello.elf", (long)args, 0);
    et_exit(5);
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
