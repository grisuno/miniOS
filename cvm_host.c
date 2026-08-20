/*
 * cvm_host.c — MiniOS host for the CVM.
 * Provides cvm_main() (invoked by the kernel shell for .cvm files) and
 * registers the kernel libc as CVM natives so modules produced by the
 * 'ld' assembler (miniGCC dialect) can run inside the OS.
 *
 * Only kernel-registered libc-compatible symbol names are used here,
 * so the kernel ELF loader can resolve them (fopen -> kfopen, ...).
 */

#include "cvm.h"

static int64_t n_strlen(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 1) return -1;
    return (int64_t)strlen((const char *)(uintptr_t)av[0]);
}

static int64_t n_strcmp(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 2) return 0;
    return (int64_t)strcmp((const char *)(uintptr_t)av[0], (const char *)(uintptr_t)av[1]);
}

static int64_t n_strncmp(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 3) return 0;
    return (int64_t)strncmp((const char *)(uintptr_t)av[0],
                            (const char *)(uintptr_t)av[1], (unsigned long)av[2]);
}

static int64_t n_strcpy(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 2) return 0;
    return (int64_t)(uintptr_t)strcpy((char *)(uintptr_t)av[0], (const char *)(uintptr_t)av[1]);
}

static int64_t n_strncpy(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 3) return 0;
    return (int64_t)(uintptr_t)strncpy((char *)(uintptr_t)av[0],
                                       (const char *)(uintptr_t)av[1], (unsigned long)av[2]);
}

static int64_t n_memcpy(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 3) return 0;
    return (int64_t)(uintptr_t)memcpy((void *)(uintptr_t)av[0],
                                      (const void *)(uintptr_t)av[1], (unsigned long)av[2]);
}

static int64_t n_memset(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 3) return 0;
    return (int64_t)(uintptr_t)memset((void *)(uintptr_t)av[0], (int)av[1], (unsigned long)av[2]);
}

static int64_t n_memmove(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 3) return 0;
    return (int64_t)(uintptr_t)memmove((void *)(uintptr_t)av[0],
                                       (const void *)(uintptr_t)av[1], (unsigned long)av[2]);
}

static int64_t n_memcmp(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 3) return 0;
    return (int64_t)memcmp((const void *)(uintptr_t)av[0],
                           (const void *)(uintptr_t)av[1], (unsigned long)av[2]);
}

static int64_t n_strchr(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 2) return 0;
    return (int64_t)(uintptr_t)strchr((const char *)(uintptr_t)av[0], (int)av[1]);
}

static int64_t n_strstr(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 2) return 0;
    return (int64_t)(uintptr_t)strstr((const char *)(uintptr_t)av[0],
                                      (const char *)(uintptr_t)av[1]);
}

static int64_t n_malloc(void *vm, int ac, uint64_t *av) {
    if (ac < 1) return 0;
    return (int64_t)(uintptr_t)cvm_heap_alloc((CvmState *)vm, (size_t)av[0]);
}

static int64_t n_free(void *vm, int ac, uint64_t *av) {
    (void)vm; (void)ac; (void)av;
    return 0;
}

static int64_t n_calloc(void *vm, int ac, uint64_t *av) {
    if (ac < 2) return 0;
    size_t n = (size_t)av[0] * (size_t)av[1];
    void *p = cvm_heap_alloc((CvmState *)vm, n);
    if (p) memset(p, 0, n);
    return (int64_t)(uintptr_t)p;
}

static int64_t n_realloc(void *vm, int ac, uint64_t *av) {
    if (ac < 2) return 0;
    size_t n = (size_t)av[1];
    void *p = cvm_heap_alloc((CvmState *)vm, n);
    if (p) memcpy(p, (const void *)(uintptr_t)av[0], n);
    return (int64_t)(uintptr_t)p;
}

static int64_t n_exit(void *vm, int ac, uint64_t *av) {
    CvmState *v = (CvmState *)vm;
    v->running = 0;
    v->exit_code = (int64_t)(ac > 0 ? av[0] : 0);
    return 0;
}

static int64_t n_fopen(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 2) return 0;
    return (int64_t)(uintptr_t)fopen((const char *)(uintptr_t)av[0],
                                     (const char *)(uintptr_t)av[1]);
}

static int64_t n_fclose(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 1) return -1;
    return (int64_t)fclose((FILE *)(uintptr_t)av[0]);
}

static int64_t n_fread(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 4) return 0;
    return (int64_t)fread((void *)(uintptr_t)av[0], (unsigned long)av[1],
                          (unsigned long)av[2], (FILE *)(uintptr_t)av[3]);
}

static int64_t n_fwrite(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 4) return 0;
    return (int64_t)fwrite((const void *)(uintptr_t)av[0], (unsigned long)av[1],
                           (unsigned long)av[2], (FILE *)(uintptr_t)av[3]);
}

static int64_t n_fseek(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 3) return -1;
    return (int64_t)fseek((FILE *)(uintptr_t)av[0], (long)av[1], (int)av[2]);
}

static int64_t n_ftell(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 1) return -1;
    return (int64_t)ftell((FILE *)(uintptr_t)av[0]);
}

static int64_t n_rewind(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 1) return -1;
    rewind((FILE *)(uintptr_t)av[0]);
    return 0;
}

static int64_t n_fputs(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 2) return -1;
    return (int64_t)fputs((const char *)(uintptr_t)av[0], (FILE *)(uintptr_t)av[1]);
}

static int64_t n_fputc(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 2) return -1;
    return (int64_t)fputc((int)av[0], (FILE *)(uintptr_t)av[1]);
}

static int64_t n_fgetc(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 1) return -1;
    return (int64_t)fgetc((FILE *)(uintptr_t)av[0]);
}

static int64_t n_ungetc(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 2) return -1;
    return (int64_t)ungetc((int)av[0], (FILE *)(uintptr_t)av[1]);
}

static int64_t n_fflush(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 1) return -1;
    return (int64_t)fflush((FILE *)(uintptr_t)av[0]);
}

static int64_t n_putchar(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 1) return -1;
    fputc((int)(av[0] & 255), stdout);
    return 1;
}

static int64_t n_write(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 3) return -1;
    const unsigned char *p = (const unsigned char *)(uintptr_t)av[1];
    unsigned long n = (unsigned long)av[2];
    for (unsigned long i = 0; i < n; i++) fputc((int)p[i], stdout);
    return (int64_t)n;
}

static int64_t n_read(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 3) return -1;
    unsigned char *p = (unsigned char *)(uintptr_t)av[1];
    unsigned long n = (unsigned long)av[2];
    unsigned long got = 0;
    for (unsigned long i = 0; i < n; i++) {
        int c = fgetc(stdin);
        if (c < 0) break;
        p[i] = (unsigned char)c;
        got++;
    }
    return (int64_t)got;
}

static int64_t n_puts(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 1) return -1;
    fputs((const char *)(uintptr_t)av[0], stdout);
    fputc('\n', stdout);
    return 0;
}

static int64_t n_atol(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 1) return 0;
    const char *s = (const char *)(uintptr_t)av[0];
    long v = 0;
    int neg = 0;
    while (*s == ' ' || *s == '\t') s++;
    if (*s == '-') { neg = 1; s++; }
    else if (*s == '+') s++;
    while (*s >= '0' && *s <= '9') { v = v * 10 + (*s - '0'); s++; }
    return (int64_t)(neg ? -v : v);
}

static int64_t n_strtol(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 1) return 0;
    const char *s = (const char *)(uintptr_t)av[0];
    long v = 0;
    int neg = 0;
    while (*s == ' ' || *s == '\t') s++;
    if (*s == '-') { neg = 1; s++; }
    else if (*s == '+') s++;
    while (*s >= '0' && *s <= '9') { v = v * 10 + (*s - '0'); s++; }
    return (int64_t)(neg ? -v : v);
}

static int64_t n_stderr_addr(void *vm, int ac, uint64_t *av) {
    (void)vm; (void)ac; (void)av;
    return (int64_t)(uintptr_t)stderr;
}

static int64_t n_stdout_addr(void *vm, int ac, uint64_t *av) {
    (void)vm; (void)ac; (void)av;
    return (int64_t)(uintptr_t)stdout;
}

static int64_t n_stdin_addr(void *vm, int ac, uint64_t *av) {
    (void)vm; (void)ac; (void)av;
    return (int64_t)(uintptr_t)stdin;
}

static void kout_char(void *ctx, char c) {
    FILE *f = (FILE *)ctx;
    if (f) fputc(c, f);
    else fputc(c, stdout);
}

static void kout_uint(void *ctx, unsigned long long v, int base, int upper) {
    char tmp[24];
    int i = 23;
    tmp[i--] = 0;
    if (v == 0) tmp[i--] = '0';
    while (v) {
        int d = (int)(v % (unsigned long long)base);
        v /= (unsigned long long)base;
        tmp[i--] = (char)(d < 10 ? '0' + d : (upper ? 'A' : 'a') + d - 10);
    }
    for (int k = i + 1; k < 23; k++) kout_char(ctx, tmp[k]);
}

static void kformat(void *ctx, const char *fmt, uint64_t *argv, int argc) {
    int ai = 0;
    while (*fmt) {
        if (*fmt != '%') { kout_char(ctx, *fmt++); continue; }
        fmt++;
        if (*fmt == '%') { kout_char(ctx, '%'); fmt++; continue; }
        int left = 0, zero = 0, plus = 0, space = 0;
        for (;;) {
            if (*fmt == '-') { left = 1; fmt++; }
            else if (*fmt == '0') { zero = 1; fmt++; }
            else if (*fmt == '+') { plus = 1; fmt++; }
            else if (*fmt == ' ') { space = 1; fmt++; }
            else break;
        }
        int width = 0;
        while (*fmt >= '0' && *fmt <= '9') { width = width * 10 + (*fmt - '0'); fmt++; }
        int prec = -1;
        if (*fmt == '.') {
            fmt++;
            prec = 0;
            while (*fmt >= '0' && *fmt <= '9') { prec = prec * 10 + (*fmt - '0'); fmt++; }
        }
        while (*fmt == 'l') fmt++;
        char c = *fmt++;
        uint64_t val = ai < argc ? argv[ai++] : 0;
        if (c == 's') {
            const char *s = (const char *)(uintptr_t)val;
            if (!s) s = "(null)";
            unsigned long n = strlen(s);
            if (prec >= 0 && (unsigned long)prec < n) n = (unsigned long)prec;
            int pad = width - (int)n;
            if (pad > 0 && !left) while (pad-- > 0) kout_char(ctx, ' ');
            for (unsigned long i = 0; i < n; i++) kout_char(ctx, s[i]);
            if (pad > 0 && left) while (pad-- > 0) kout_char(ctx, ' ');
        } else if (c == 'd' || c == 'i') {
            long long sv = (long long)val;
            unsigned long long m = sv < 0 ? (unsigned long long)(-sv) : (unsigned long long)sv;
            int slen = (sv < 0 || plus || space) ? 1 : 0;
            int pad = width - 1 - slen;
            if (pad > 0 && !left && !zero) while (pad-- > 0) kout_char(ctx, ' ');
            if (sv < 0) kout_char(ctx, '-');
            else if (plus) kout_char(ctx, '+');
            else if (space) kout_char(ctx, ' ');
            if (pad > 0 && !left && zero) while (pad-- > 0) kout_char(ctx, '0');
            int d2 = 1;
            unsigned long long t = m;
            while (t >= 10) { t /= 10; d2++; }
            if (prec > 0) while (prec-- > d2) kout_char(ctx, '0');
            if (prec != 0 || m != 0) kout_uint(ctx, m, 10, 0);
            if (pad > 0 && left) while (pad-- > 0) kout_char(ctx, ' ');
        } else if (c == 'u') {
            kout_uint(ctx, val, 10, 0);
        } else if (c == 'x' || c == 'X') {
            kout_uint(ctx, val, 16, c == 'X');
        } else if (c == 'p') {
            kout_char(ctx, '0');
            kout_char(ctx, 'x');
            kout_uint(ctx, val, 16, 0);
        } else if (c == 'c') {
            kout_char(ctx, (char)(val & 255));
        } else {
            kout_char(ctx, c);
        }
    }
}

static int64_t n_fprintf(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 2) return -1;
    kformat((void *)(uintptr_t)av[0], (const char *)(uintptr_t)av[1], av + 2, ac - 2);
    return 0;
}

static int64_t n_printf(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 1) return -1;
    kformat(0, (const char *)(uintptr_t)av[0], av + 1, ac - 1);
    return 0;
}

static int64_t n_sprintf(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 2) return -1;
    char *buf = (char *)(uintptr_t)av[0];
    buf[0] = 0;
    return 0;
}

static int64_t n_snprintf(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 3) return -1;
    char *buf = (char *)(uintptr_t)av[0];
    if (av[1] > 0) buf[0] = 0;
    return 0;
}

static void register_host_natives(CvmState *vm) {
    cvm_register_native(vm, "strlen", n_strlen);
    cvm_register_native(vm, "strcmp", n_strcmp);
    cvm_register_native(vm, "strncmp", n_strncmp);
    cvm_register_native(vm, "strcpy", n_strcpy);
    cvm_register_native(vm, "strncpy", n_strncpy);
    cvm_register_native(vm, "strchr", n_strchr);
    cvm_register_native(vm, "strstr", n_strstr);
    cvm_register_native(vm, "memcpy", n_memcpy);
    cvm_register_native(vm, "memmove", n_memmove);
    cvm_register_native(vm, "memset", n_memset);
    cvm_register_native(vm, "memcmp", n_memcmp);
    cvm_register_native(vm, "malloc", n_malloc);
    cvm_register_native(vm, "free", n_free);
    cvm_register_native(vm, "calloc", n_calloc);
    cvm_register_native(vm, "realloc", n_realloc);
    cvm_register_native(vm, "exit", n_exit);
    cvm_register_native(vm, "abort", n_exit);
    cvm_register_native(vm, "fopen", n_fopen);
    cvm_register_native(vm, "fclose", n_fclose);
    cvm_register_native(vm, "fread", n_fread);
    cvm_register_native(vm, "fwrite", n_fwrite);
    cvm_register_native(vm, "fseek", n_fseek);
    cvm_register_native(vm, "ftell", n_ftell);
    cvm_register_native(vm, "rewind", n_rewind);
    cvm_register_native(vm, "fputs", n_fputs);
    cvm_register_native(vm, "fputc", n_fputc);
    cvm_register_native(vm, "fgetc", n_fgetc);
    cvm_register_native(vm, "ungetc", n_ungetc);
    cvm_register_native(vm, "fflush", n_fflush);
    cvm_register_native(vm, "putchar", n_putchar);
    cvm_register_native(vm, "write", n_write);
    cvm_register_native(vm, "read", n_read);
    cvm_register_native(vm, "puts", n_puts);
    cvm_register_native(vm, "atol", n_atol);
    cvm_register_native(vm, "strtol", n_strtol);
    cvm_register_native(vm, "fprintf", n_fprintf);
    cvm_register_native(vm, "printf", n_printf);
    cvm_register_native(vm, "sprintf", n_sprintf);
    cvm_register_native(vm, "snprintf", n_snprintf);
    cvm_register_native(vm, "stderr_addr", n_stderr_addr);
    cvm_register_native(vm, "stdout_addr", n_stdout_addr);
    cvm_register_native(vm, "stdin_addr", n_stdin_addr);
}

int cvm_main(int argc, char **argv) {
    if (argc < 1) return 1;
    const char *path = argv[0];
    FILE *f = fopen(path, "r");
    if (!f) {
        puts("cvm: cannot open module");
        return 1;
    }
    fseek(f, 0, 2);
    long sz = ftell(f);
    rewind(f);
    if (sz <= 0 || sz > (64L * 1024L * 1024L)) {
        puts("cvm: bad module size");
        fclose(f);
        return 1;
    }
    unsigned char *buf = (unsigned char *)malloc((unsigned long)sz);
    if (!buf) {
        fclose(f);
        return 1;
    }
    if (fread(buf, 1, (unsigned long)sz, f) != (unsigned long)sz) {
        puts("cvm: read error");
        free(buf);
        fclose(f);
        return 1;
    }
    fclose(f);

    CvmConfig cfg = cvm_config_default();
    CvmState *vm = cvm_create(&cfg);
    if (!vm) { free(buf); return 1; }
    register_host_natives(vm);
    int rc = cvm_load_module(vm, buf, (unsigned long)sz);
    free(buf);
    if (rc != CVM_OK) {
        puts("cvm: load error");
        cvm_destroy(vm);
        return 1;
    }
    /* Linux-style argv: argv[0] is the module path, the rest are the
     * program arguments. The ld-compiled startup reads them from the
     * stack cvm_set_args builds, so the full vector is passed here. */
    rc = cvm_set_args(vm, argc, argv);
    if (rc != CVM_OK) {
        cvm_destroy(vm);
        return 1;
    }
    rc = cvm_run(vm);
    if (rc != CVM_OK) {
        puts("cvm: runtime error");
        cvm_destroy(vm);
        return 1;
    }
    int ec = (int)cvm_exit_code(vm);
    cvm_destroy(vm);
    return ec;
}
