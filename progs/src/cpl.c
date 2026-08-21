/* Ring-3 privilege probe. Reads the CS selector at runtime and exits with
 * the CPL it is executing at. Under the isolation contract a Linux ELF
 * runs at ring 3, so CS is the user code selector (0x23) and the exit
 * code is 3; a regression to ring-0 execution would report 0. Built as a
 * static Linux ELF like lxhello.elf and run through the syscall ABI. */
static long read_cpl(void) {
    long cs;
    __asm__ volatile("mov %%cs, %0" : "=r"(cs));
    return cs & 3;
}

static void exit_now(long code) {
    __asm__ volatile("syscall" :: "a"(60), "D"(code) : "rcx", "r11", "memory");
}

void _start(void) {
    exit_now(read_cpl());
}