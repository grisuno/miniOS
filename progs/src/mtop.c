/* mtop.c - ASCII real-time system monitor for MiniOS.
 *
 * A top-like dashboard written in the miniGCC subset: no structs, no
 * typedefs, no unsigned, only int/long/char plus pointers and flat
 * arrays. It builds through the hosted chain exactly like the other
 * command-path tools:
 *
 *   run objects/minigcc.o src/mtop.c > asm/mtop.s
 *   run objects/ld.o -f elf -o bin/mtop.elf asm/mtop.s
 *   mtop [frames] [interval_ms]
 *
 * All system figures come from the MINFO syscall (251): heap used /
 * free, ramdisk used / cap, MiniFS free / total blocks, cpu total /
 * idle 100 Hz ticks, cpu count / uptime. CPU busy percent is
 * (dt-didle)*100/dt between two reads. DISK throughput is measured
 * live by reading a ramdisk probe file (opened once, rewound every
 * frame, because the ld fclose stub never releases its file slot).
 * NET is a TCP socket create / close plus a cached localhost DNS
 * round trip. Every value is range-checked before display, so a
 * foreign kernel that answers the number with other semantics
 * degrades to unavailable instead of showing garbage.
 *
 * Frames after the first are preceded by a screen clear through MINFO
 * selector 5 (a true redraw on the framebuffer terminal, ANSI clear
 * on the serial console as fallback): the animation effect without
 * scrolling.
 *
 * Usage: mtop [frames] [interval_ms]
 *   frames       how many refreshes to draw, 0 means run until q (default 0)
 *   interval_ms  pause between frames, clamped to 100..5000 (default 500)
 * Quit with q, ESC, Ctrl+C or Ctrl+D. mtop -1 draws one snapshot.
 */

int write();
int putchar();
int strlen();
int strcmp();
void *fopen();
int fclose();
int fread();
void rewind();
int socket();
int close();
int net_dns_resolve();

#define MTOP_HIST 32
#define MTOP_DISK_BUF 4096
#define MTOP_DISK_MAX (64 * 1024)
#define MTOP_MINFO 251

static long h_cpu[MTOP_HIST];
static long h_mem[MTOP_HIST];
static int h_fill;
static long last_dns;
static long last_dns_ms;
static long last_sock;
static long prev_total;
static long prev_idle;
static int have_prev;
static void *disk_f;
static char *disk_path;

static long sc3(long n, long a1, long a2, long a3) {
    long r;
    __asm__ volatile("syscall"
        : "=a"(r)
        : "a"(n), "D"(a1), "S"(a2), "d"(a3)
        : "rcx", "r11", "memory");
    return r;
}

static long mtop_time(void) {
    return sc3(204, 0, 0, 0);
}

static long mtop_rtc(int *h, int *m, int *s) {
    return sc3(212, (long)h, (long)m, (long)s);
}

static long mtop_key(void) {
    return sc3(236, 0, 0, 0);
}

static long mtop_minfo(long sel, long *o1, long *o2) {
    *o1 = 0;
    *o2 = 0;
    return sc3(MTOP_MINFO, sel, (long)o1, (long)o2);
}

static void emit(char *s) {
    write(1, s, strlen(s));
}

static int mtop_quit_key(long k) {
    if (k == 113) return 1;
    if (k == 81) return 1;
    if (k == 27) return 1;
    if (k == 3) return 1;
    if (k == 4) return 1;
    return 0;
}

static void mtop_clear_ansi(void) {
    putchar(27);
    putchar('[');
    putchar('2');
    putchar('J');
    putchar(27);
    putchar('[');
    putchar('H');
}

static void mtop_clear(void) {
    if (sc3(MTOP_MINFO, 5, 0, 0) != 0) mtop_clear_ansi();
}

static int mtop_atoi(char *s) {
    int v;
    int i;
    int neg;
    v = 0;
    i = 0;
    neg = 0;
    if (s[0] == '-') {
        neg = 1;
        i = 1;
    }
    while (s[i] >= '0' && s[i] <= '9') {
        v = v * 10 + (s[i] - '0');
        i++;
    }
    if (neg) v = -v;
    return v;
}

static void mtop_putu(long v) {
    char buf[24];
    int i;
    i = 24;
    i--;
    buf[i] = 0;
    if (v < 0) {
        emit("-");
        v = -v;
    }
    if (v == 0) {
        i--;
        buf[i] = '0';
    }
    while (v > 0 && i > 0) {
        i--;
        buf[i] = (char)('0' + v % 10);
        v = v / 10;
    }
    emit(&buf[i]);
}

static void mtop_put2(int v) {
    if (v < 10) emit("0");
    mtop_putu(v);
}

static void mtop_put_kb(long kb) {
    long mb;
    long dec;
    if (kb < 1024) {
        mtop_putu(kb);
        emit(" KB");
        return;
    }
    mb = kb / 1024;
    dec = ((kb % 1024) * 10) / 1024;
    mtop_putu(mb);
    emit(".");
    mtop_putu(dec);
    emit(" MB");
}

static void mtop_bar(long v, long max, int w) {
    int fill;
    int i;
    if (max < 1) max = 1;
    if (v < 0) v = 0;
    fill = (int)((v * w) / max);
    if (fill > w) fill = w;
    putchar('[');
    for (i = 0; i < w; i++) {
        if (i < fill) putchar('#');
        else putchar('-');
    }
    putchar(']');
}

static long mtop_hist_max(long *h, int n) {
    long m;
    int i;
    m = 1;
    for (i = 0; i < n; i++) {
        if (h[i] > m) m = h[i];
    }
    return m;
}

static void mtop_hist_push(long *h, long v) {
    int i;
    if (h_fill < MTOP_HIST) {
        h[h_fill] = v;
        return;
    }
    for (i = 0; i < MTOP_HIST - 1; i++) h[i] = h[i + 1];
    h[MTOP_HIST - 1] = v;
}

static void mtop_spark(long *h, int n) {
    char ramp[11];
    char out[40];
    long max;
    int i;
    int c;
    ramp[0] = ' ';
    ramp[1] = '.';
    ramp[2] = ':';
    ramp[3] = '-';
    ramp[4] = '=';
    ramp[5] = '+';
    ramp[6] = '*';
    ramp[7] = '#';
    ramp[8] = '%';
    ramp[9] = '@';
    ramp[10] = 0;
    max = mtop_hist_max(h, n);
    for (i = 0; i < n && i < MTOP_HIST; i++) {
        c = (int)((h[i] * 9) / max);
        if (c < 0) c = 0;
        if (c > 9) c = 9;
        out[i] = ramp[c];
    }
    out[i] = 0;
    emit(out);
}

static long mtop_mem(long *used, long *freeb, long *total) {
    long rc;
    rc = mtop_minfo(0, used, freeb);
    if (rc != 0) return -1;
    if (*used < 0) return -1;
    if (*freeb < 0) return -1;
    *total = *used + *freeb;
    if (*total <= 0) return -1;
    return 0;
}

static long mtop_cpu(long *count, long *busy) {
    long total;
    long idle;
    long n;
    long up;
    long dt;
    long di;
    total = 0;
    idle = 0;
    n = 0;
    up = 0;
    if (mtop_minfo(4, &n, &up) != 0) return -1;
    if (n < 1) return -1;
    if (n > 64) return -1;
    if (mtop_minfo(3, &total, &idle) != 0) return -1;
    if (total <= 0) return -1;
    if (idle < 0) return -1;
    if (idle > total) return -1;
    *count = n;
    if (!have_prev) {
        prev_total = total;
        prev_idle = idle;
        have_prev = 1;
        return 1;
    }
    dt = total - prev_total;
    di = idle - prev_idle;
    prev_total = total;
    prev_idle = idle;
    if (dt <= 0) return 1;
    if (di < 0) di = 0;
    if (di > dt) di = dt;
    *busy = ((dt - di) * 100) / dt;
    return 0;
}

static void mtop_disk_open(void) {
    disk_f = fopen("src/mtop.c", "r");
    if (disk_f) {
        disk_path = "src/mtop.c";
        return;
    }
    disk_f = fopen("progs/src/mtop.c", "r");
    if (disk_f) {
        disk_path = "progs/src/mtop.c";
        return;
    }
    disk_f = fopen("src/fib.c", "r");
    if (disk_f) {
        disk_path = "src/fib.c";
        return;
    }
    disk_f = fopen("progs/src/fib.c", "r");
    if (disk_f) {
        disk_path = "progs/src/fib.c";
        return;
    }
    disk_path = 0;
}

static long mtop_disk_read(long *bytes) {
    char buf[MTOP_DISK_BUF];
    long t0;
    long t1;
    long total;
    long n;
    *bytes = 0;
    if (!disk_f) return -1;
    rewind(disk_f);
    t0 = mtop_time();
    total = 0;
    for (;;) {
        n = fread(buf, 1, MTOP_DISK_BUF, disk_f);
        if (n <= 0) break;
        total = total + n;
        if (total >= MTOP_DISK_MAX) break;
    }
    t1 = mtop_time();
    *bytes = total;
    if (t0 < 0) return -2;
    if (t1 < 0) return -2;
    return t1 - t0;
}

static long mtop_net_probe(long *dns_ms, long *sock_ok) {
    int fd;
    long t0;
    long t1;
    long rc;
    *dns_ms = -1;
    *sock_ok = 0;
    fd = socket(2, 1, 0);
    if (fd < 0) return -1;
    *sock_ok = 1;
    close(fd);
    t0 = mtop_time();
    rc = net_dns_resolve("localhost");
    t1 = mtop_time();
    if (t0 >= 0 && t1 >= 0) *dns_ms = t1 - t0;
    return rc;
}

static void mtop_frame(int n) {
    long now;
    long up;
    long used;
    long freeb;
    long total;
    long mem_ok;
    long pct;
    long count;
    long busy;
    long cpu_rc;
    long rd_used;
    long rd_cap;
    long fs_free;
    long fs_total;
    long disk_ok;
    long dms;
    long dbytes;
    long dns_ms;
    long nrc;
    long sock_ok;
    long do_dns;
    long max;
    int hh;
    int mm;
    int ss;
    int rtc_ok;
    now = mtop_time();
    up = -1;
    if (now >= 0) up = now / 1000;
    rtc_ok = 0;
    hh = 0;
    mm = 0;
    ss = 0;
    if (mtop_rtc(&hh, &mm, &ss) == 0) rtc_ok = 1;
    mem_ok = mtop_mem(&used, &freeb, &total);
    cpu_rc = mtop_cpu(&count, &busy);
    disk_ok = mtop_minfo(1, &rd_used, &rd_cap);
    if (disk_ok == 0) {
        if (rd_cap <= 0) disk_ok = -1;
        if (rd_used < 0) disk_ok = -1;
        if (rd_used > rd_cap) disk_ok = -1;
    }
    fs_free = 0;
    fs_total = 0;
    if (mtop_minfo(2, &fs_free, &fs_total) != 0) {
        fs_free = -1;
        fs_total = 0;
    }
    dms = mtop_disk_read(&dbytes);
    dns_ms = -1;
    nrc = -1;
    sock_ok = 0;
    do_dns = 0;
    if (n == 1) do_dns = 1;
    if ((n % 10) == 0) do_dns = 1;
    if (do_dns) {
        nrc = mtop_net_probe(&dns_ms, &sock_ok);
        last_dns = nrc;
        last_dns_ms = dns_ms;
        last_sock = sock_ok;
    } else {
        nrc = last_dns;
        dns_ms = last_dns_ms;
        sock_ok = last_sock;
    }
    if (mem_ok == 0) {
        pct = (used * 100) / total;
        mtop_hist_push(h_mem, pct);
    }
    if (cpu_rc == 0) mtop_hist_push(h_cpu, busy);
    if (h_fill < MTOP_HIST) h_fill = h_fill + 1;
    emit("================ mtop ================\n");
    if (up >= 0) {
        emit("encendido hace ");
        mtop_putu(up);
        emit(" s");
    }
    if (rtc_ok) {
        emit("  hora ");
        mtop_put2(hh);
        emit(":");
        mtop_put2(mm);
        emit(":");
        mtop_put2(ss);
    }
    emit("  (q sale)\n");
    emit("RAM  ");
    if (mem_ok != 0) {
        emit("no disponible");
    } else {
        emit("ocupada ");
        mtop_put_kb(used);
        emit(" de ");
        mtop_put_kb(total);
        emit(" (");
        mtop_putu(pct);
        emit("%) libres ");
        mtop_put_kb(freeb);
    }
    emit("\n  ");
    max = mtop_hist_max(h_mem, h_fill);
    if (mem_ok != 0) mtop_bar(0, 1, 20);
    else mtop_bar(pct, 100, 20);
    emit(" ultimos valores ");
    mtop_spark(h_mem, h_fill);
    emit("\n");
    emit("CPU  ");
    if (cpu_rc != 0) {
        if (cpu_rc < 0) emit("no disponible");
        else emit("midiendo...");
    } else {
        mtop_putu(count);
        if (count == 1) emit(" nucleo, en uso ");
        else emit(" nucleos, en uso ");
        mtop_putu(busy);
        emit("%");
    }
    emit("\n  ");
    if (cpu_rc != 0) mtop_bar(0, 1, 20);
    else mtop_bar(busy, 100, 20);
    emit(" ultimos valores ");
    mtop_spark(h_cpu, h_fill);
    emit("\n");
    emit("DISCO ");
    if (disk_ok != 0) {
        emit("capacidad no disponible");
    } else {
        emit("ramdisk ocupado ");
        mtop_put_kb(rd_used);
        emit(" de ");
        mtop_put_kb(rd_cap);
        if (fs_total > 0) {
            emit(", MiniFS libres ");
            mtop_putu(fs_free);
            emit(" de ");
            mtop_putu(fs_total);
            emit(" bloques");
        } else {
            emit(", MiniFS no montado");
        }
    }
    emit("\n  lectura ");
    if (!disk_f) {
        emit("sin fichero de prueba");
    } else if (dms == -1) {
        emit("no se puede leer ");
        emit(disk_path);
    } else {
        emit(disk_path);
        emit(" ");
        mtop_putu(dbytes);
        emit(" bytes en ");
        if (dms <= 0) emit("menos de 1 ms");
        else {
            mtop_putu(dms);
            emit(" ms (");
            mtop_putu((dbytes * 1000) / (dms * 1024));
            emit(" KB/s)");
        }
    }
    emit("\n");
    emit("RED  ");
    if (sock_ok == 0) emit("no disponible");
    else emit("disponible");
    emit("  DNS ");
    if (nrc != 0) emit("sin respuesta");
    else emit("responde");
    if (dns_ms >= 0) {
        emit(" en ");
        mtop_putu(dns_ms);
        emit(" ms");
    }
    emit("\n");
}

int main(int argc, char **argv) {
    int frames;
    int interval;
    int n;
    long deadline;
    long now;
    long chunk;
    long t;
    long k;
    if (argc > 1 && strcmp(argv[1], "help") == 0) {
        emit("uso: mtop [fotos] [milisegundos]\n");
        emit("  fotos 0 = hasta q, -1 = una foto\n");
        return 0;
    }
    if (argc > 1 && strcmp(argv[1], "-h") == 0) {
        emit("uso: mtop [fotos] [milisegundos]\n");
        return 0;
    }
    frames = 0;
    interval = 500;
    if (argc > 1) frames = mtop_atoi(argv[1]);
    if (argc > 2) interval = mtop_atoi(argv[2]);
    if (interval < 100) interval = 100;
    if (interval > 5000) interval = 5000;
    if (frames < 0) frames = 1;
    mtop_disk_open();
    h_fill = 0;
    have_prev = 0;
    n = 0;
    for (;;) {
        n = n + 1;
        if (n > 1) {
            if (frames != 1) mtop_clear();
        }
        mtop_frame(n);
        if (frames > 0 && n >= frames) break;
        deadline = mtop_time();
        if (deadline < 0) {
            k = mtop_key();
            if (mtop_quit_key(k)) return 0;
            if (frames == 0) break;
            continue;
        }
        deadline = deadline + interval;
        while (1) {
            now = mtop_time();
            if (now < 0) break;
            if (now >= deadline) break;
            chunk = deadline - now;
            if (chunk > 50) chunk = 50;
            if (sc3(MTOP_MINFO, 6, chunk, 0) != 0) {
                t = now + chunk;
                for (;;) {
                    now = mtop_time();
                    if (now < 0) break;
                    if (now >= t) break;
                }
            }
            for (;;) {
                k = mtop_key();
                if (k < 0) break;
                if (mtop_quit_key(k)) return 0;
            }
        }
        k = mtop_key();
        if (mtop_quit_key(k)) break;
    }
    if (disk_f) fclose(disk_f);
    return 0;
}
