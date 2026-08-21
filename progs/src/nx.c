/* NX probe. Under the isolation contract every user page starts
 * non-executable and load_exec_elf clears NX only on the pages a program's
 * executable segments occupy. This program writes a `ret` instruction into a
 * stack buffer and calls it through a function pointer: with NX enforced the
 * instruction fetch faults and the machine resets (no IDT), so the shell
 * never reports an exit code and `poweroff` is never reached; a regression
 * that drops NX lets the shellcode return and the program exits 0 normally.
 * Built as a static Linux ELF like cpl.elf and run through the syscall ABI. */
typedef void (*fn_t)(void);

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
    volatile unsigned char code[1];
    fn_t fn;
    write_str("nx: jumping to stack\n", 21);
    code[0] = 0xC3;
    fn = (fn_t)(unsigned long)(void *)code;
    fn();
    exit_now(0);
}