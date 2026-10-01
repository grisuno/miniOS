/* pcmap probe: file-backed MAP_PRIVATE mmap shares text.
 *
 * Maps 17 pages of lisp.c (65933 bytes on MiniFS) plus a second
 * mapping of page 1 at file offset 4096, checksums the content and
 * cross-checks the overlap: the offset mapping must read exactly
 * what the base mapping holds 4096 bytes in. Both mappings stay
 * resident (no munmap) so the `mem` pcache count proves one shared
 * copy, and exit tears the window down through the ref-drop walk.
 * Built as a static Linux ELF like mprot.elf; run twice under mrun
 * for the cross-process share. Pinned hash and page count assume
 * the current lisp.c size; drift fails loudly, never silently. */
static long sc_open(const char *p) {
    long r;
    __asm__ volatile("syscall"
        : "=a"(r)
        : "a"(2), "D"(p), "S"(0), "d"(0)
        : "rcx", "r11", "memory");
    return r;
}

static long sc_mmap(long len, long prot, long flags, long fd, long off) {
    long r;
    register long a4 asm("r10") = flags;
    register long a5 asm("r8") = fd;
    register long a6 asm("r9") = off;
    __asm__ volatile("syscall"
        : "=a"(r)
        : "0"(9), "D"(0), "S"(len), "d"(prot),
          "r"(a4), "r"(a5), "r"(a6)
        : "rcx", "r11", "memory");
    return r;
}

static long sc_write(long fd, const char *s, long n) {
    long r;
    __asm__ volatile("syscall" : "=a"(r)
                     : "a"(1), "D"(fd), "S"(s), "d"(n)
                     : "rcx", "r11", "memory");
    return r;
}

static void sc_exit(long code) {
    __asm__ volatile("syscall" :: "a"(60), "D"(code) : "rcx", "r11", "memory");
}

static unsigned long sc_fnv(const char *p, long n) {
    unsigned long h = 2166136261UL;
    long i;
    for (i = 0; i < n; i++) {
        h ^= (unsigned long)(unsigned char)p[i];
        h *= 16777619UL;
    }
    return h & 0xFFFFFFFFUL;
}

static void sc_hex8(unsigned long v, char *out) {
    int i;
    for (i = 7; i >= 0; i--) {
        unsigned d = (unsigned)(v & 0xFu);
        out[i] = (char)(d < 10 ? '0' + d : 'a' + d - 10);
        v >>= 4;
    }
}

static long sc_munmap(long addr, long len) {
    long r;
    register long a2 asm("rsi") = len;
    __asm__ volatile("syscall"
        : "=a"(r)
        : "0"(11), "D"(addr), "r"(a2)
        : "rcx", "r11", "memory");
    return r;
}

void _start(void) {
    long fd = sc_open("lisp.c");
    long p;
    long q;
    long r;
    long i;
    unsigned long h;
    char msg[24];
    char orig;
    if (fd < 0) sc_exit(10);
    p = sc_mmap(69632, 3, 0x02, fd, 0);
    if (p < 0) sc_exit(11);
    q = sc_mmap(4096, 3, 0x02, fd, 4096);
    if (q < 0) sc_exit(12);
    r = sc_mmap(4096, 3, 0x02, fd, 0);
    if (r < 0) sc_exit(14);
    h = sc_fnv((const char *)p, 69632);
    for (i = 0; i < 4096; i++) {
        if (((const char *)q)[i] != ((const char *)p)[4096 + i])
            sc_exit(13);
    }
    orig = ((const char *)r)[0];
    ((volatile char *)p)[0] = (char)(orig ^ 0xFF);
    if (((const char *)p)[0] != (char)(orig ^ 0xFF)) sc_exit(15);
    if (((const char *)r)[0] != orig) sc_exit(16);
    if (sc_munmap(p, 69632) != 0) sc_exit(17);
    if (sc_munmap(q, 4096) != 0) sc_exit(17);
    if (sc_munmap(r, 4096) != 0) sc_exit(17);
    p = sc_mmap(69632, 3, 0x02, fd, 0);
    if (p < 0) sc_exit(18);
    if (sc_fnv((const char *)p, 69632) != h) sc_exit(19);
    msg[0] = 'p';
    msg[1] = 'c';
    msg[2] = 'm';
    msg[3] = 'a';
    msg[4] = 'p';
    msg[5] = ':';
    msg[6] = ' ';
    sc_hex8(h, msg + 7);
    msg[15] = '\n';
    sc_write(1, msg, 16);
    sc_exit(0);
}
