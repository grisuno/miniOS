/*
 * spin - tiny preemptive-multitask probe (nostdlib, like lxhello).
 *
 * Loops N rounds; each round burns user cycles, yields the CPU and
 * reports progress on stdout. Two spins in background must interleave
 * and both finish with distinct exit codes while the shell answers.
 * No libc, no TLS, no heap: the only syscalls are write (1), yield
 * (24) and exit (60), so glibc init can never be blamed for a fault.
 */

static long lx_syscall3(long n, long a1, long a2, long a3) {
    long ret;
    __asm__ volatile("syscall"
                     : "=a"(ret)
                     : "a"(n), "D"(a1), "S"(a2), "d"(a3)
                     : "rcx", "r11", "memory");
    return ret;
}

static unsigned long lx_strlen(const char *s) {
    unsigned long n = 0;
    while (s[n]) n++;
    return n;
}

static void lx_write(const char *s) {
    lx_syscall3(1, 1, (long)s, (long)lx_strlen(s));
}

static void lx_write_int(long v) {
    char buf[24];
    int i = (int)sizeof(buf);
    int neg = 0;
    buf[--i] = 0;
    if (v < 0) { neg = 1; v = -v; }
    if (v == 0) buf[--i] = '0';
    while (v > 0 && i > 0) { buf[--i] = (char)('0' + v % 10); v /= 10; }
    if (neg && i > 0) buf[--i] = '-';
    lx_write(&buf[i]);
}

static long lx_atoi(const char *s) {
    long v = 0;
    if (!s || !*s) return 5;
    while (*s >= '0' && *s <= '9') { v = v * 10 + (*s - '0'); s++; }
    if (v < 1) return 1;
    if (v > 50) return 50;
    return v;
}

/* ---- Live Wayland-mini publisher (same wire, no libc) ----
 * Attaches one 200x90 stripe surface, then republishes a shifting
 * stripe plus a commit per frame. Tiny enough to survive startup
 * preempts that kill glibc-heavy clients, so the server tiles live
 * multiprocess frames while the scheduler proof stays honest. */
#define SPIN_WLW 200
#define SPIN_WLH 90
#define SPIN_WLA 4
#define SPIN_WLB 12

static unsigned char spin_raw[SPIN_WLW * SPIN_WLH];
static unsigned char spin_msg[32];
static unsigned char spin_frame[48];
static char spin_path[64];

static void spin_u32(unsigned char *d, unsigned long v) {
    d[0] = (unsigned char)(v & 0xFFUL);
    d[1] = (unsigned char)((v >> 8) & 0xFFUL);
    d[2] = (unsigned char)((v >> 16) & 0xFFUL);
    d[3] = (unsigned char)((v >> 24) & 0xFFUL);
}

static void spin_hdr(unsigned char *d, unsigned long id, unsigned long op,
        unsigned long size) {
    spin_u32(d, id);
    d[4] = (unsigned char)(op & 0xFFUL);
    d[5] = (unsigned char)((op >> 8) & 0xFFUL);
    d[6] = (unsigned char)(size & 0xFFUL);
    d[7] = (unsigned char)((size >> 8) & 0xFFUL);
}

static int spin_box_ok(const char *box) {
    int n = 0;
    if (!box) return 0;
    while (box[n] != '\0') {
        char ch = box[n];
        if (!((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9')))
            return 0;
        n++;
        if (n >= 17) return 0;
    }
    return n > 0;
}

static void spin_hex8(unsigned int v, char *dst) {
    static const char digits[] = "0123456789abcdef";
    int i;
    for (i = 0; i < 8; i++) {
        dst[7 - i] = digits[v & 0xFu];
        v >>= 4;
    }
}

static long spin_write_all(long fd, const unsigned char *buf, long len) {
    long off = 0;
    while (off < len) {
        long r = lx_syscall3(1, fd, (long)(buf + off), len - off);
        if (r <= 0) return -1;
        off += r;
    }
    return off;
}

static int spin_emit(const char *box, unsigned int seq,
        const unsigned char *msg, long mlen) {
    char *p = spin_path;
    char hex[8];
    int i = 0;
    long fd;
    static const char dir[] = "/shm/wl/";
    spin_hex8(seq, hex);
    while (dir[i] != '\0') { *p++ = dir[i++]; }
    i = 0;
    while (box[i] != '\0') { *p++ = box[i++]; }
    *p++ = '-';
    for (i = 0; i < 8; i++) *p++ = hex[i];
    *p++ = '.';
    *p++ = 'm';
    *p++ = 's';
    *p++ = 'g';
    *p++ = '\0';
    spin_u32(spin_frame, 0x424D4C57UL);
    spin_u32(spin_frame + 4, (unsigned long)seq);
    for (i = 0; i < mlen; i++) spin_frame[8 + i] = msg[i];
    fd = lx_syscall3(2, (long)spin_path, 577, 0);
    if (fd < 0) return -1;
    if (spin_write_all(fd, spin_frame, mlen + 8) < 0) {
        lx_syscall3(3, fd, 0, 0);
        return -1;
    }
    lx_syscall3(3, fd, 0, 0);
    return 0;
}

static int spin_raw_file(const char *box) {
    char *p = spin_path;
    int i = 0;
    long fd;
    static const char dir[] = "/shm/wl/";
    while (dir[i] != '\0') { *p++ = dir[i++]; }
    i = 0;
    while (box[i] != '\0') { *p++ = box[i++]; }
    *p++ = '.';
    *p++ = 'r';
    *p++ = 'a';
    *p++ = 'w';
    *p++ = '\0';
    fd = lx_syscall3(2, (long)spin_path, 577, 0);
    if (fd < 0) return -1;
    if (spin_write_all(fd, spin_raw,
            (long)SPIN_WLW * (long)SPIN_WLH) < 0) {
        lx_syscall3(3, fd, 0, 0);
        return -1;
    }
    lx_syscall3(3, fd, 0, 0);
    return 0;
}

static void spin_pixels(long off) {
    int y;
    int x;
    for (y = 0; y < SPIN_WLH; y++) {
        for (x = 0; x < SPIN_WLW; x++) {
            int pick = ((x + (int)off) / 16) & 1;
            spin_raw[y * SPIN_WLW + x] =
                (unsigned char)(pick ? SPIN_WLB : SPIN_WLA);
        }
    }
}

static int spin_wl(const char *box, const char *narg) {
    long frames = 0;
    unsigned int seq = 1;
    long i;
    long k;
    const char *p = narg;
    if (!spin_box_ok(box)) return 2;
    if (!p || *p == '\0') return 2;
    while (*p != '\0') {
        if (*p < '0' || *p > '9') return 2;
        frames = frames * 10 + (*p - '0');
        if (frames > 200) return 2;
        p++;
    }
    if (frames < 1) return 2;
    spin_pixels(0);
    if (spin_raw_file(box) != 0) { lx_write("spin: no pixels\n"); return 1; }
    spin_hdr(spin_msg, 1, 1, 8);
    if (spin_emit(box, seq++, spin_msg, 8) != 0) return 1;
    spin_hdr(spin_msg, 2, 0, 12);
    spin_u32(spin_msg + 8, 3);
    if (spin_emit(box, seq++, spin_msg, 12) != 0) return 1;
    spin_hdr(spin_msg, 3, 0, 8);
    if (spin_emit(box, seq++, spin_msg, 8) != 0) return 1;
    spin_hdr(spin_msg, 4, 0, 8);
    if (spin_emit(box, seq++, spin_msg, 8) != 0) return 1;
    spin_hdr(spin_msg, 16, 1, 20);
    spin_u32(spin_msg + 8, 64);
    spin_u32(spin_msg + 12, (unsigned long)SPIN_WLW);
    spin_u32(spin_msg + 16, (unsigned long)SPIN_WLH);
    if (spin_emit(box, seq++, spin_msg, 20) != 0) return 1;
    spin_hdr(spin_msg, 16, 6, 8);
    if (spin_emit(box, seq++, spin_msg, 8) != 0) return 1;
    for (i = 0; i < frames; i++) {
        spin_pixels(i % 16);
        if (spin_raw_file(box) != 0) return 1;
        spin_hdr(spin_msg, 16, 6, 8);
        if (spin_emit(box, seq++, spin_msg, 8) != 0) return 1;
        for (k = 0; k < 30; k++) lx_syscall3(24, 0, 0, 0);
    }
    lx_write("spin: live done\n");
    return 43;
}

int lmain(long argc, char **argv) {
    long rounds = 5;
    long tag = 0;
    long i;
    volatile unsigned long sink = 0;
    unsigned long k;
    if (argc > 1 && argv[1][0] == 'w' && argv[1][1] == 'l' &&
            argv[1][2] == '\0') {
        const char *box = (argc > 2) ? argv[2] : "";
        const char *narg = (argc > 3) ? argv[3] : "";
        return spin_wl(box, narg);
    }
    if (argc > 1) rounds = lx_atoi(argv[1]);
    if (argc > 2) tag = lx_atoi(argv[2]);
    for (i = 1; i <= rounds; i++) {
        for (k = 0; k < 200000UL; k++) sink += k & 7UL;
        lx_write("spin");
        lx_write_int(tag);
        lx_write(" tick ");
        lx_write_int(i);
        lx_write("\n");
        lx_syscall3(24, 0, 0, 0);
    }
    if (sink == 0xFFFFFFFFUL) lx_write("unreachable\n");
    return (int)(40 + tag);
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
