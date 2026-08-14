#include "kernel.h"

/* ================================================================
 *  Port I/O helpers
 * ================================================================ */

static inline void outb(unsigned short port, unsigned char val) {
    __asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}
static inline unsigned char inb(unsigned short port) {
    unsigned char r;
    __asm__ volatile("inb %1, %0" : "=a"(r) : "Nd"(port));
    return r;
}

/* ================================================================
 *  Serial console (COM1, 16550 UART) — mirrors VGA, drives input
 * ================================================================ */

#define COM1 0x3F8

void serial_init(void) {
    outb(COM1 + 1, 0x00); /* disable interrupts */
    outb(COM1 + 3, 0x80); /* enable DLAB */
    outb(COM1 + 0, 0x01); /* divisor lo -> 115200 baud */
    outb(COM1 + 1, 0x00); /* divisor hi */
    outb(COM1 + 3, 0x03); /* 8 bits, no parity, one stop */
    outb(COM1 + 2, 0xC7); /* enable FIFO, clear, 14-byte threshold */
    outb(COM1 + 4, 0x0B); /* IRQs off, RTS/DSR set */
}

static int serial_tx_ready(void) { return inb(COM1 + 5) & 0x20; }
static int serial_rx_ready(void) { return inb(COM1 + 5) & 0x01; }

void serial_putc(char c) {
    if (c == '\n') { while (!serial_tx_ready()); outb(COM1, '\r'); }
    while (!serial_tx_ready());
    outb(COM1, (unsigned char)c);
}
void serial_puts(const char *s) { while (*s) serial_putc(*s++); }

int serial_available(void) { return serial_rx_ready(); }
int serial_getc(void) { return serial_rx_ready() ? (int)inb(COM1) : -1; }

static int console_getc(void); /* defined in the shell section */

/* ================================================================
 *  VGA driver
 * ================================================================ */

static int vga_x, vga_y;
static char vga_color = 0x07; /* light grey on black */

static inline unsigned vga_offset(int x, int y) { return (unsigned)(y * VGA_COLS + x) * 2; }

void vga_clear(void) {
    int i;
    for (i = 0; i < VGA_COLS * VGA_ROWS; i++) {
        VGA_BASE[i * 2]     = ' ';
        VGA_BASE[i * 2 + 1] = vga_color;
    }
    vga_x = vga_y = 0;
    vga_set_cursor(0, 0);
}

void vga_set_cursor(int x, int y) {
    unsigned short pos = (unsigned short)(y * VGA_COLS + x);
    unsigned char lo = pos & 0xFF;
    unsigned char hi = (pos >> 8) & 0xFF;
    __asm__ volatile(
        "movw $0x3D4, %%dx\n\t"
        "movb $0x0F, %%al\n\t"
        "outb %%al, %%dx\n\t"
        "movb %b0, %%al\n\t"
        "outb %%al, %%dx\n\t"
        "movb $0x0E, %%al\n\t"
        "outb %%al, %%dx\n\t"
        "movb %b1, %%al\n\t"
        "outb %%al, %%dx"
        :
        : "r"((unsigned long)lo), "r"((unsigned long)hi)
        : "ax", "dx"
    );
}

void vga_scroll(void) {
    int y, x;
    for (y = 0; y < VGA_ROWS - 1; y++) {
        for (x = 0; x < VGA_COLS; x++) {
            unsigned src = vga_offset(x, y + 1);
            unsigned dst = vga_offset(x, y);
            VGA_BASE[dst]     = VGA_BASE[src];
            VGA_BASE[dst + 1] = VGA_BASE[src + 1];
        }
    }
    for (x = 0; x < VGA_COLS; x++) {
        unsigned off = vga_offset(x, VGA_ROWS - 1);
        VGA_BASE[off]     = ' ';
        VGA_BASE[off + 1] = vga_color;
    }
    vga_y = VGA_ROWS - 1;
}

void vga_newline(void) {
    vga_x = 0;
    vga_y++;
    if (vga_y >= VGA_ROWS) vga_scroll();
}

static void vga_raw_space(void) {
    unsigned off = vga_offset(vga_x, vga_y);
    VGA_BASE[off]     = ' ';
    VGA_BASE[off + 1] = vga_color;
    vga_x++;
    if (vga_x >= VGA_COLS) vga_newline();
}

void vga_putc(char c) {
    serial_putc(c);
    if (c == '\n') { vga_newline(); vga_set_cursor(vga_x, vga_y); return; }
    if (c == '\r') { vga_x = 0; vga_set_cursor(vga_x, vga_y); return; }
    if (c == '\t') {
        int spaces = 8 - (vga_x & 7);
        while (spaces--) vga_raw_space();
        vga_set_cursor(vga_x, vga_y);
        return;
    }
    if (c == '\b') {
        if (vga_x > 0) {
            vga_x--;
            unsigned off = vga_offset(vga_x, vga_y);
            VGA_BASE[off] = ' ';
            VGA_BASE[off + 1] = vga_color;
            vga_set_cursor(vga_x, vga_y);
        }
        return;
    }
    unsigned off = vga_offset(vga_x, vga_y);
    VGA_BASE[off]     = c;
    VGA_BASE[off + 1] = vga_color;
    vga_x++;
    if (vga_x >= VGA_COLS) vga_newline();
    vga_set_cursor(vga_x, vga_y);
}

void vga_puts(const char *s) {
    while (*s) vga_putc(*s++);
}


/* ================================================================
 *  Keyboard driver — PS/2 scancode set 1 (US qwerty)
 * ================================================================ */

static const unsigned char kbd_us[128] = {
    0,   0x1B, '1','2','3','4','5','6','7','8','9','0','-','=','\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0,   'a','s','d','f','g','h','j','k','l',';','\'','`',
    0,   '\\','z','x','c','v','b','n','m',',','.','/', 0,
    '*', 0,   ' ', 0,
    /* F1-F10 */   0,0,0,0,0,0,0,0,0,0,
    /* numlock, scrlk */ 0,0,
    /* home, up, pgup, - */  0,0,0,'-',
    /* left, center, right */ 0,0,0,
    /* +, end, down, pgdn, ins, del */ '+',0,0,0,0,0,
    0,0,0,
    /* F11-F12 */ 0,0,
    0,0,0,0,0,0,0
};

static const unsigned char kbd_us_shift[128] = {
    0,   0x1B, '!','@','#','$','%','^','&','*','(',')','_','+','\b',
    '\t','Q','W','E','R','T','Y','U','I','O','P','{','}','\n',
    0,   'A','S','D','F','G','H','J','K','L',':','"','~',
    0,   '|','Z','X','C','V','B','N','M','<','>','?', 0,
    '*', 0,   ' ', 0,
    0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, '-',0,0,0,0,
    '+', 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

static int kbd_shift;

int kbd_available(void) {
    unsigned char s;
    __asm__ volatile("inb $0x64, %0" : "=a"(s));
    return (s & 1);
}

int kbd_read(void) {
    while (!kbd_available()) __asm__ volatile("pause");
    unsigned char sc;
    __asm__ volatile("inb $0x60, %0" : "=a"(sc));

    if (sc & 0x80) { /* key release */
        sc &= 0x7F;
        if (sc == KEY_LSHIFT || sc == KEY_RSHIFT) kbd_shift = 0;
        return -1;
    }

    if (sc == KEY_LSHIFT || sc == KEY_RSHIFT) { kbd_shift = 1; return -1; }

    if (kbd_shift)
        return kbd_us_shift[sc];
    else
        return kbd_us[sc];
}


/* ================================================================
 *  Memory allocator — simple free-list
 * ================================================================ */

#define ALLOC_MAGIC 0xDEADBEEF
#define ALIGN_UP(x, a) (((x) + (a) - 1) & ~((a) - 1))

typedef struct Block {
    unsigned long  magic;
    unsigned long  size;    /* user-requested size */
    struct Block  *next;    /* free list link */
} Block;

#define BLOCK_HDR_SZ ALIGN_UP(sizeof(Block), 16)

static Block *free_list;
static char  *heap_start, *heap_end, *heap_curr;

/* ---- Physical memory map (identity-mapped 0..1GB by the bootloader) ----
 *   0x00000000 .. 0x00100000   BIOS / kernel image / page tables / stack
 *   0x00400000 .. 0x02000000   user program region (ELF load addr + brk)
 *   0x02000000 .. 0x06000000   64 MB kernel heap
 */
#define USER_LOAD_BASE  0x00400000UL
#define USER_LOAD_END   0x02000000UL
#define HEAP_BASE       0x02000000UL
#define HEAP_SIZE       (64UL * 1024 * 1024)

void kallocator_init(void) {
    heap_start = (char *)HEAP_BASE;
    heap_end   = heap_start + HEAP_SIZE;
    heap_curr  = heap_start;
    free_list  = 0;
}

void *kmalloc(unsigned long size) {
    if (size == 0) return 0;
    size = ALIGN_UP(size, 16);

    Block *prev = 0, *b = free_list;
    while (b) {
        if (b->size >= size) {
            if (prev) prev->next = b->next;
            else       free_list  = b->next;
            b->magic = ALLOC_MAGIC;
            b->size  = size;
            return (char *)b + BLOCK_HDR_SZ;
        }
        prev = b;
        b = b->next;
    }

    if (heap_curr + BLOCK_HDR_SZ + size > heap_end) return 0;
    b = (Block *)heap_curr;
    heap_curr += BLOCK_HDR_SZ + size;
    b->magic = ALLOC_MAGIC;
    b->size  = size;
    b->next  = 0;
    return (char *)b + BLOCK_HDR_SZ;
}

void kfree(void *ptr) {
    if (!ptr) return;
    Block *b = (Block *)((char *)ptr - BLOCK_HDR_SZ);
    if (b->magic != ALLOC_MAGIC) return;
    b->next = free_list;
    free_list = b;
}

void *kcalloc(unsigned long nmemb, unsigned long size) {
    unsigned long total = nmemb * size;
    void *p = kmalloc(total);
    if (p) kmemset(p, 0, total);
    return p;
}

void *krealloc(void *ptr, unsigned long size) {
    if (!ptr) return kmalloc(size);
    if (size == 0) { kfree(ptr); return 0; }
    Block *b = (Block *)((char *)ptr - BLOCK_HDR_SZ);
    if (b->magic != ALLOC_MAGIC) return 0;
    if (b->size >= size) { b->size = size; return ptr; }
    void *newp = kmalloc(size);
    if (newp) {
        kmemcpy(newp, ptr, b->size);
        kfree(ptr);
    }
    return newp;
}


/* ================================================================
 *  String functions
 * ================================================================ */

unsigned long kstrlen(const char *s) {
    const char *p = s;
    while (*p) p++;
    return (unsigned long)(p - s);
}

char *kstrcpy(char *dst, const char *src) {
    char *d = dst;
    while ((*d++ = *src++));
    return dst;
}

char *kstrncpy(char *dst, const char *src, unsigned long n) {
    char *d = dst;
    while (n-- && (*d++ = *src++));
    return dst;
}

int kstrcmp(const char *a, const char *b) {
    while (*a && *a == *b) { a++; b++; }
    return (unsigned char)*a - (unsigned char)*b;
}

int kstrncmp(const char *a, const char *b, unsigned long n) {
    while (n-- && *a && *a == *b) { a++; b++; }
    return n == (unsigned long)-1 ? 0 : (unsigned char)*a - (unsigned char)*b;
}

char *kstrchr(const char *s, int c) {
    while (*s) { if (*s == (char)c) return (char *)s; s++; }
    return 0;
}

char *kstrstr(const char *hay, const char *ndl) {
    unsigned long nl = kstrlen(ndl);
    if (nl == 0) return (char *)hay;
    while (*hay) {
        if (kstrncmp(hay, ndl, nl) == 0) return (char *)hay;
        hay++;
    }
    return 0;
}

void *kmemcpy(void *dst, const void *src, unsigned long n) {
    char *d = dst;
    const char *s = src;
    while (n--) *d++ = *s++;
    return dst;
}

void *kmemset(void *dst, int c, unsigned long n) {
    char *d = dst;
    while (n--) *d++ = (char)c;
    return dst;
}

int kmemcmp(const void *a, const void *b, unsigned long n) {
    const unsigned char *pa = a, *pb = b;
    while (n--) { if (*pa != *pb) return *pa - *pb; pa++; pb++; }
    return 0;
}

void *kmemmove(void *dst, const void *src, unsigned long n) {
    char *d = dst;
    const char *s = src;
    if (d < s) { while (n--) *d++ = *s++; }
    else       { d += n; s += n; while (n--) *--d = *--s; }
    return dst;
}

/* atoi helper */
static long katol(const char *s) {
    long v = 0, sign = 1;
    while (*s == ' ') s++;
    if (*s == '-') { sign = -1; s++; }
    else if (*s == '+') s++;
    while (*s >= '0' && *s <= '9') { v = v * 10 + (*s - '0'); s++; }
    return v * sign;
}


/* ================================================================
 *  Ramdisk file system
 * ================================================================ */

#define RD_MAGIC     0x4B534452 /* "RDSK" */
#define RD_DATA_SIZE (512UL * 1024) /* 512 KB data area */

typedef struct {
    unsigned magic;
    unsigned count;
    RDFile  files[RAMDISK_MAX_FILES];
} RDSuper;

static RDSuper *rd;
static char    *rd_data;
static unsigned rd_used;

void ramdisk_setup_from(void *data, unsigned size) {
    (void)size;
    char *raw = (char *)data;
    unsigned magic = *(unsigned *)raw;
    if (magic != RD_MAGIC) return;

    unsigned count = *(unsigned *)(raw + 4);
    if (count > RAMDISK_MAX_FILES) return;

    if (!rd) ramdisk_init();
    if (!rd || !rd_data) return;

    char *entry_start = raw + 8;
    char *data_start  = entry_start + count * sizeof(RDFile);

    /* Compute total data size and copy entries */
    unsigned total = 0;
    unsigned i;
    for (i = 0; i < count; i++) {
        char *esrc = entry_start + i * sizeof(RDFile);
        unsigned fsize  = *(unsigned *)(esrc + RAMDISK_FNAME_LEN);
        RDFile *f = &rd->files[i];
        kmemcpy(f->name, esrc, RAMDISK_FNAME_LEN);
        f->name[RAMDISK_FNAME_LEN - 1] = 0;
        f->size   = fsize;
        f->offset = total;
        total    += fsize;
        rd_used   = total;
    }
    rd->count = count;

    /* Ensure rd_data can hold the total data */
    if (total > RD_DATA_SIZE) return;

    /* Copy file data from embedded binary to rd_data */
    for (i = 0; i < count; i++) {
        char *esrc = entry_start + i * sizeof(RDFile);
        unsigned forig  = *(unsigned *)(esrc + RAMDISK_FNAME_LEN + 4);
        RDFile *f = &rd->files[i];
        kmemcpy(rd_data + f->offset, data_start + forig, f->size);
    }
}

void ramdisk_init(void) {
    if (!rd) {
        rd      = kcalloc(1, sizeof(RDSuper));
        rd_data = kmalloc(RD_DATA_SIZE);
        rd_used = 0;
        if (!rd || !rd_data) return;
        rd->magic = RD_MAGIC;
        rd->count = 0;
    }
}

RDFile *ramdisk_open(const char *name) {
    unsigned i;
    if (!rd) return 0;
    for (i = 0; i < rd->count; i++) {
        if (kstrcmp(rd->files[i].name, name) == 0)
            return &rd->files[i];
    }
    return 0;
}

int ramdisk_read(RDFile *f, void *buf, unsigned offset, unsigned len) {
    if (!f || !buf || !rd_data) return 0;
    if (offset >= f->size) return 0;
    if (offset + len > f->size) len = f->size - offset;
    kmemcpy(buf, rd_data + f->offset + offset, len);
    return (int)len;
}

int ramdisk_write(RDFile *f, const void *buf, unsigned offset, unsigned len) {
    if (!f || !buf || !rd_data) return 0;
    if (offset >= f->size) return 0;
    if (offset + len > f->size) len = f->size - offset;
    kmemcpy(rd_data + f->offset + offset, buf, len);
    return (int)len;
}

RDFile *ramdisk_create(const char *name, unsigned size) {
    if (!rd || rd->count >= RAMDISK_MAX_FILES) return 0;
    if (rd_used + size > RD_DATA_SIZE) return 0;
    RDFile *f = &rd->files[rd->count];
    kstrncpy(f->name, name, RAMDISK_FNAME_LEN - 1);
    f->name[RAMDISK_FNAME_LEN - 1] = 0;
    f->size   = size;
    f->offset = rd_used;
    rd_used  += size;
    rd->count++;
    return f;
}

int ramdisk_list(RDFile **out, int max) {
    if (!rd) return 0;
    int n = (int)rd->count < max ? (int)rd->count : max;
    unsigned i;
    for (i = 0; i < (unsigned)n; i++) out[i] = &rd->files[i];
    return n;
}


/* ================================================================
 *  FILE interface (wraps ramdisk)
 * ================================================================ */

KFILE *kfopen(const char *path, const char *mode) {
    KFILE *f = kmalloc(sizeof(KFILE));
    if (!f) return 0;
    kmemset(f, 0, sizeof(KFILE));
    f->rf = ramdisk_open(path);
    if (!f->rf && mode[0] == 'w') {
        f->rf = ramdisk_create(path, 0);
        if (!f->rf) { kfree(f); return 0; }
    }
    if (!f->rf) { kfree(f); return 0; }
    f->pos  = 0;
    f->mode = (mode[0] == 'w') ? 1 : 0;
    if (f->mode) {
        f->wbuf = kmalloc(4096);
        f->wcap = 4096;
        f->wsize = 0;
    }
    return f;
}

int kfclose(KFILE *f) {
    if (!f) return 0;
    if (f->mode == 1) kfflush(f);
    if (f->wbuf) kfree(f->wbuf);
    kfree(f);
    return 0;
}

int kfgetc(KFILE *f) {
    if (!f) return EOF;
    if (f->is_console) {
        int c = console_getc();
        if (c == '\r') c = '\n';
        return c;
    }
    if (!f->rf || f->pos >= f->rf->size) return EOF;
    char c;
    ramdisk_read(f->rf, &c, f->pos, 1);
    f->pos++;
    return (unsigned char)c;
}

int kfungetc(int c, KFILE *f) {
    if (!f || c == EOF || f->pos == 0) return EOF;
    f->pos--;
    return c;
}

unsigned long kfread(void *ptr, unsigned long size, unsigned long n, KFILE *f) {
    if (!f) return 0;
    if (f->is_console) {
        char *b = ptr; unsigned long got = 0, total = size * n;
        while (got < total) { int c = kfgetc(f); if (c == EOF) break; b[got++] = (char)c; }
        return size ? got / size : 0;
    }
    if (!f->rf) return 0;
    unsigned long total = size * n;
    if (f->pos + total > f->rf->size) total = f->rf->size - f->pos;
    ramdisk_read(f->rf, ptr, f->pos, (unsigned)total);
    f->pos += total;
    return total / size;
}

unsigned long kfwrite(const void *ptr, unsigned long size, unsigned long n, KFILE *f) {
    if (!f) return 0;
    if (f->is_console) {
        const char *b = ptr; unsigned long bytes = size * n, i;
        for (i = 0; i < bytes; i++) vga_putc(b[i]);
        return n;
    }
    if (f->mode != 1) return 0;
    unsigned long bytes = size * n;
    if (!f->wbuf) {
        f->wbuf = kmalloc(4096);
        f->wcap = 4096;
        f->wsize = 0;
    }
    while (f->wsize + bytes > f->wcap) {
        f->wcap *= 2;
        f->wbuf = krealloc(f->wbuf, f->wcap);
    }
    kmemcpy(f->wbuf + f->wsize, ptr, bytes);
    f->wsize += bytes;
    f->pos += bytes;
    return n;
}

int kfseek(KFILE *f, long offset, int whence) {
    if (!f || !f->rf) return -1;
    unsigned base;
    if (whence == 0) base = 0;
    else if (whence == 1) base = f->pos;
    else base = f->rf->size;
    long newp = (long)base + offset;
    if (newp < 0) newp = 0;
    if ((unsigned long)newp > f->rf->size) newp = (long)f->rf->size;
    f->pos = (unsigned)newp;
    return 0;
}

long kftell(KFILE *f) {
    return f ? (long)f->pos : -1;
}

int kfflush(KFILE *f) {
    if (!f || !f->rf || f->mode != 1) return 0;
    if (f->wbuf && f->wsize > 0) {
        f->rf->size = f->wsize;
        ramdisk_write(f->rf, f->wbuf, 0, f->wsize);
        f->wsize = 0;
    }
    return 0;
}

int kfputs(const char *s, KFILE *f) {
    if (!f || !s) return 0;
    unsigned long len = kstrlen(s);
    return (int)kfwrite(s, 1, len, f);
}

int kfputc(int c, KFILE *f) {
    unsigned char ch = (unsigned char)c;
    return (int)kfwrite(&ch, 1, 1, f);
}

void krewind(KFILE *f) { if (f) kfseek(f, 0, 0); }

/* Default stdin/stdout/stderr for programs.  A C program references the
 * symbols `stdin`/`stdout`/`stderr` as FILE* *variables*, so we register the
 * addresses of these pointer variables, each aimed at a console-backed KFILE. */
static KFILE  console_in  = { 0, 0, 0, 0, 0, 0, 1 };
static KFILE  console_out = { 0, 0, 0, 0, 0, 0, 1 };
static KFILE  console_err = { 0, 0, 0, 0, 0, 0, 1 };
KFILE *kstdin  = &console_in;
KFILE *kstdout = &console_out;
KFILE *kstderr = &console_err;

KFILE *kfile_stdin(void)  { return kstdin; }
KFILE *kfile_stdout(void) { return kstdout; }
KFILE *kfile_stderr(void) { return kstderr; }


/* ================================================================
 *  printf family
 * ================================================================ */

static void putc_buf(char c, void *ctx, int *written) {
    (void)ctx;
    vga_putc(c);
    (*written)++;
}

static void putc_file(char c, void *ctx, int *written) {
    KFILE *f = (KFILE *)ctx;
    kfputc(c, f);
    (*written)++;
}

static void putc_str(char c, void *ctx, int *written) {
    char **p = (char **)ctx;
    **p = c;
    (*p)++;
    (*written)++;
}

/* Emit a reverse-ordered digit buffer honouring width, left-justify and
 * zero-fill flags. buf holds `pos` digits least-significant first. */
static void emit_num(void (*emit)(char, void *, int *), void *ctx, int *written,
                     char *buf, int pos, int neg, int pad, int left, int zero) {
    int total = pos + (neg ? 1 : 0);
    if (left) {
        if (neg) emit('-', ctx, written);
        while (pos > 0) emit(buf[--pos], ctx, written);
        while (pad > total) { emit(' ', ctx, written); pad--; }
    } else if (zero) {
        if (neg) emit('-', ctx, written);
        while (pad > total) { emit('0', ctx, written); pad--; }
        while (pos > 0) emit(buf[--pos], ctx, written);
    } else {
        while (pad > total) { emit(' ', ctx, written); pad--; }
        if (neg) emit('-', ctx, written);
        while (pos > 0) emit(buf[--pos], ctx, written);
    }
}

static void kformat(void (*emit)(char, void *, int *), void *ctx,
                    int *written, const char *fmt, __builtin_va_list ap) {
    const char *p;
    for (p = fmt; *p; p++) {
        if (*p != '%') { emit(*p, ctx, written); continue; }
        p++;
        if (*p == 0) break;
        if (*p == '%') { emit('%', ctx, written); continue; }

        int left = 0, zero = 0;
        if (*p == '-') { left = 1; p++; }
        if (*p == '0') { zero = 1; p++; }
        int pad = 0;
        while (*p >= '0' && *p <= '9') { pad = pad * 10 + (*p - '0'); p++; }

        if (*p == 's') {
            const char *s = __builtin_va_arg(ap, const char *);
            if (!s) s = "(null)";
            int slen = (int)kstrlen(s);
            if (left) {
                while (*s) { emit(*s++, ctx, written); }
                while (pad > slen) { emit(' ', ctx, written); pad--; }
            } else {
                while (pad > slen) { emit(' ', ctx, written); pad--; }
                while (*s) { emit(*s++, ctx, written); }
            }
        } else if (*p == 'c') {
            char c = (char)__builtin_va_arg(ap, int);
            emit(c, ctx, written);
        } else if (*p == 'd' || *p == 'i') {
            long v = __builtin_va_arg(ap, int);
            int neg = 0;
            if (v < 0) { neg = 1; v = -v; }
            char buf[32];
            int pos = 0;
            if (v == 0) buf[pos++] = '0';
            else while (v > 0) { buf[pos++] = '0' + (v % 10); v /= 10; }
            emit_num(emit, ctx, written, buf, pos, neg, pad, left, zero);
        } else if (*p == 'u') {
            unsigned long v = __builtin_va_arg(ap, unsigned int);
            char buf[32];
            int pos = 0;
            if (v == 0) buf[pos++] = '0';
            else while (v > 0) { buf[pos++] = '0' + (v % 10); v /= 10; }
            emit_num(emit, ctx, written, buf, pos, 0, pad, left, zero);
        } else if (*p == 'x' || *p == 'X') {
            unsigned long v = __builtin_va_arg(ap, unsigned int);
            char hex_base = (*p == 'X') ? 'A' : 'a';
            char buf[32];
            int pos = 0;
            if (v == 0) buf[pos++] = '0';
            else while (v > 0) {
                int d = v & 0xF;
                buf[pos++] = (d < 10) ? ('0' + d) : (hex_base + d - 10);
                v >>= 4;
            }
            emit_num(emit, ctx, written, buf, pos, 0, pad, left, zero);
        } else if (*p == 'p') {
            emit('0', ctx, written);
            emit('x', ctx, written);
            unsigned long v = (unsigned long)__builtin_va_arg(ap, void *);
            int i;
            for (i = 15; i >= 0; i--) {
                int d = (v >> (i * 4)) & 0xF;
                emit((d < 10) ? ('0' + d) : ('a' + d - 10), ctx, written);
            }
        } else if (*p == 'l') {
            p++;
            if (*p == 'l') p++; /* accept %ll* as %l* */
            if (*p == 'd' || *p == 'i') {
                long v = __builtin_va_arg(ap, long);
                int neg = 0;
                if (v < 0) { neg = 1; v = -v; }
                char buf[32]; int pos = 0;
                if (v == 0) buf[pos++] = '0';
                else while (v) { buf[pos++] = '0' + (v % 10); v /= 10; }
                emit_num(emit, ctx, written, buf, pos, neg, pad, left, zero);
            } else if (*p == 'u') {
                unsigned long v = __builtin_va_arg(ap, unsigned long);
                char buf[32]; int pos = 0;
                if (v == 0) buf[pos++] = '0';
                else while (v) { buf[pos++] = '0' + (v % 10); v /= 10; }
                emit_num(emit, ctx, written, buf, pos, 0, pad, left, zero);
            } else if (*p == 'x' || *p == 'X') {
                unsigned long v = __builtin_va_arg(ap, unsigned long);
                char hex_base = (*p == 'X') ? 'A' : 'a';
                char buf[32]; int pos = 0;
                if (v == 0) buf[pos++] = '0';
                else while (v) {
                    int d = v & 0xF;
                    buf[pos++] = (d < 10) ? ('0' + d) : (hex_base + d - 10);
                    v >>= 4;
                }
                emit_num(emit, ctx, written, buf, pos, 0, pad, left, zero);
            }
        }
    }
}

int kprintf(const char *fmt, ...) {
    int written = 0;
    __builtin_va_list ap;
    __builtin_va_start(ap, fmt);
    kformat(putc_buf, 0, &written, fmt, ap);
    __builtin_va_end(ap);
    return written;
}

int kfprintf(KFILE *f, const char *fmt, ...) {
    int written = 0;
    __builtin_va_list ap;
    __builtin_va_start(ap, fmt);
    kformat(putc_file, f, &written, fmt, ap);
    __builtin_va_end(ap);
    return written;
}

int ksprintf(char *buf, const char *fmt, ...) {
    int written = 0;
    char *p = buf;
    __builtin_va_list ap;
    __builtin_va_start(ap, fmt);
    kformat(putc_str, &p, &written, fmt, ap);
    __builtin_va_end(ap);
    *p = 0;
    return written;
}

struct snctx { char *p; unsigned long rem; };
static void putc_snbuf(char c, void *ctx, int *written) {
    struct snctx *s = (struct snctx *)ctx;
    if (s->rem > 1) { *s->p++ = c; s->rem--; }
    (*written)++;
}

int ksnprintf(char *buf, unsigned long size, const char *fmt, ...) {
    int written = 0;
    struct snctx s = { buf, size };
    __builtin_va_list ap;
    __builtin_va_start(ap, fmt);
    kformat(putc_snbuf, &s, &written, fmt, ap);
    __builtin_va_end(ap);
    if (size > 0) *s.p = 0;
    return written;
}


/* ================================================================
 *  Symbol table (for resolving program references)
 * ================================================================ */

#define KSYM_MAX 256

typedef struct {
    const char *name;
    void       *addr;
} KSym;

static KSym  ksym_table[KSYM_MAX];
static int   ksym_count;

void k_register_symbol(const char *name, void *addr) {
    if (ksym_count < KSYM_MAX) {
        ksym_table[ksym_count].name = name;
        ksym_table[ksym_count].addr = addr;
        ksym_count++;
    }
}

void *ksym_resolve(const char *name) {
    int i;
    for (i = 0; i < ksym_count; i++) {
        if (kstrcmp(ksym_table[i].name, name) == 0)
            return ksym_table[i].addr;
    }
    return 0;
}


/* ================================================================
 *  Program registry
 * ================================================================ */

#define KPROG_MAX 64

typedef struct {
    const char  *name;
    prog_entry_t entry;      /* ET_REL: called directly as a C function */
    void        *proc_entry; /* ET_EXEC/ET_DYN: Linux _start, run as a process */
    int          is_proc;
} KProg;

static KProg  kprog_table[KPROG_MAX];
static int    kprog_count;

static KProg *kprog_slot(const char *name) {
    int i;
    for (i = 0; i < kprog_count; i++)
        if (kstrcmp(kprog_table[i].name, name) == 0) return &kprog_table[i];
    if (kprog_count < KPROG_MAX) return &kprog_table[kprog_count++];
    return 0;
}

void k_register_program(const char *name, prog_entry_t entry) {
    KProg *p = kprog_slot(name);
    if (!p) return;
    p->name = name; p->entry = entry; p->proc_entry = 0; p->is_proc = 0;
}

void k_register_process(const char *name, void *proc_entry) {
    KProg *p = kprog_slot(name);
    if (!p) return;
    p->name = name; p->entry = 0; p->proc_entry = proc_entry; p->is_proc = 1;
}

int k_spawn(const char *name, int argc, char **argv) {
    int i;
    for (i = 0; i < kprog_count; i++) {
        if (kstrcmp(kprog_table[i].name, name) == 0) {
            if (kprog_table[i].is_proc)
                return k_exec_user(kprog_table[i].proc_entry, argc, argv);
            return k_run_rel(kprog_table[i].entry, argc, argv);
        }
    }
    return -1;
}


/* ================================================================
 *  ELF loader — loads ET_REL x86_64 .o files, applies relocations,
 *  resolves symbols via ksym_resolve, returns entry point.
 * ================================================================ */

/* Minimal ELF64 definitions */
#define EI_NIDENT 16
typedef unsigned long long Elf64_Addr;
typedef unsigned long long Elf64_Off;
typedef unsigned int       Elf64_Word;
typedef unsigned short     Elf64_Half;
typedef unsigned long long Elf64_Xword;
typedef long long          Elf64_Sxword;

typedef struct {
    unsigned char e_ident[EI_NIDENT];
    Elf64_Half    e_type;
    Elf64_Half    e_machine;
    Elf64_Word    e_version;
    Elf64_Addr    e_entry;
    Elf64_Off     e_phoff;
    Elf64_Off     e_shoff;
    Elf64_Word    e_flags;
    Elf64_Half    e_ehsize;
    Elf64_Half    e_phentsize;
    Elf64_Half    e_phnum;
    Elf64_Half    e_shentsize;
    Elf64_Half    e_shnum;
    Elf64_Half    e_shstrndx;
} Elf64_Ehdr;

typedef struct {
    Elf64_Word  sh_name;
    Elf64_Word  sh_type;
    Elf64_Xword sh_flags;
    Elf64_Addr  sh_addr;
    Elf64_Off   sh_offset;
    Elf64_Xword sh_size;
    Elf64_Word  sh_link;
    Elf64_Word  sh_info;
    Elf64_Xword sh_addralign;
    Elf64_Xword sh_entsize;
} Elf64_Shdr;

typedef struct {
    Elf64_Word  st_name;
    unsigned char st_info;
    unsigned char st_other;
    Elf64_Half  st_shndx;
    Elf64_Addr  st_value;
    Elf64_Xword st_size;
} Elf64_Sym;

typedef struct {
    Elf64_Addr   r_offset;
    Elf64_Xword  r_info;
    Elf64_Sxword r_addend;
} Elf64_Rela;

typedef struct {
    Elf64_Word  p_type;
    Elf64_Word  p_flags;
    Elf64_Off   p_offset;
    Elf64_Addr  p_vaddr;
    Elf64_Addr  p_paddr;
    Elf64_Xword p_filesz;
    Elf64_Xword p_memsz;
    Elf64_Xword p_align;
} Elf64_Phdr;

#define ELF64_R_SYM(i)    ((i) >> 32)
#define ELF64_R_TYPE(i)   ((i) & 0xffffffff)
#define SHN_UNDEF         0

#define SHT_SYMTAB  2
#define SHT_STRTAB  3
#define SHT_RELA    4
#define SHT_PROGBITS 1
#define SHT_NOBITS  8
#define SHF_ALLOC   2
#define SHF_EXECINSTR 4

#define ET_REL      1
#define ET_EXEC     2
#define ET_DYN      3
#define EM_X86_64  62
#define PT_LOAD     1

#define R_X86_64_64        1
#define R_X86_64_PC32      2
#define R_X86_64_PLT32     4
#define R_X86_64_GLOB_DAT  6
#define R_X86_64_JUMP_SLOT 7
#define R_X86_64_RELATIVE  8
#define R_X86_64_32       10
#define R_X86_64_32S      11
#define R_X86_64_IRELATIVE 37

void *elf_load(void *data, unsigned size) {
    (void)size;
    Elf64_Ehdr *ehdr = (Elf64_Ehdr *)data;

    if (ehdr->e_ident[0] != 0x7F || ehdr->e_ident[1] != 'E' ||
        ehdr->e_ident[2] != 'L'  || ehdr->e_ident[3] != 'F')
        return 0;
    if (ehdr->e_type != ET_REL)   return 0;
    if (ehdr->e_machine != EM_X86_64) return 0;

    Elf64_Shdr *shdrs = (Elf64_Shdr *)((char *)data + ehdr->e_shoff);
    Elf64_Half  shnum = ehdr->e_shnum;

    Elf64_Shdr *shstr = &shdrs[ehdr->e_shstrndx];
    const char *shstrtab = (const char *)data + shstr->sh_offset;

    /* Find .symtab and .strtab */
    Elf64_Sym  *symtab = 0;
    unsigned    symcount = 0;
    const char *strtab = 0;

    unsigned total_alloc = 0;
    unsigned i;
    for (i = 0; i < shnum; i++) {
        const char *sname = shstrtab + shdrs[i].sh_name;
        if (kstrcmp(sname, ".symtab") == 0) {
            symtab = (Elf64_Sym *)((char *)data + shdrs[i].sh_offset);
            symcount = (unsigned)(shdrs[i].sh_size / sizeof(Elf64_Sym));
        }
        if (kstrcmp(sname, ".strtab") == 0)
            strtab = (const char *)data + shdrs[i].sh_offset;
        if (shdrs[i].sh_flags & SHF_ALLOC)
            total_alloc += (unsigned)shdrs[i].sh_size + 16;
    }
    if (!symtab || !strtab) return 0;

    char *base = kmalloc(total_alloc);
    if (!base) return 0;
    kmemset(base, 0, total_alloc);

    void **sec_addrs = kmalloc(shnum * sizeof(void *));
    if (!sec_addrs) { kfree(base); return 0; }
    for (i = 0; i < shnum; i++) sec_addrs[i] = 0;

    unsigned off = 0;
    for (i = 0; i < shnum; i++) {
        if (!(shdrs[i].sh_flags & SHF_ALLOC)) continue;
        sec_addrs[i] = base + off;
        Elf64_Xword ssize = shdrs[i].sh_size;
        if (shdrs[i].sh_type == SHT_PROGBITS && ssize > 0)
            kmemcpy(sec_addrs[i], (char *)data + shdrs[i].sh_offset, (unsigned long)ssize);
        off += (unsigned)ssize + 16;
        off = (off + 15) & ~15U;
    }

    /* Apply relocations */
    for (i = 0; i < shnum; i++) {
        if (shdrs[i].sh_type != SHT_RELA) continue;

        /* The section being relocated */
        unsigned target_sec = shdrs[i].sh_info;
        char *target_base = (char *)sec_addrs[target_sec];
        if (!target_base) continue;

        /* The symbol table for this rela section */
        Elf64_Sym *rela_symtab = (Elf64_Sym *)((char *)data + shdrs[shdrs[i].sh_link].sh_offset);

        Elf64_Rela *relas = (Elf64_Rela *)((char *)data + shdrs[i].sh_offset);
        unsigned    rcount = (unsigned)(shdrs[i].sh_size / sizeof(Elf64_Rela));
        unsigned j;
        for (j = 0; j < rcount; j++) {
            Elf64_Word   sym_idx = ELF64_R_SYM(relas[j].r_info);
            unsigned     rtype   = ELF64_R_TYPE(relas[j].r_info);
            Elf64_Addr   S = 0;
            Elf64_Sym   *sym = &rela_symtab[sym_idx];

            if (sym->st_shndx != SHN_UNDEF && sym->st_shndx < shnum) {
                /* Local: address = section base + symbol value */
                S = (Elf64_Addr)(unsigned long)sec_addrs[sym->st_shndx] + sym->st_value;
            } else {
                /* Undefined: resolve via kernel symbol table */
                const char *sname = strtab + sym->st_name;
                void *addr = ksym_resolve(sname);
                if (!addr) {
                    /* Try with leading underscore removed */
                    if (sname[0] == '_') addr = ksym_resolve(sname + 1);
                }
                if (!addr) continue; /* unresolved, skip */
                S = (Elf64_Addr)(unsigned long)addr;
            }
            S += relas[j].r_addend;

            Elf64_Addr *P = (Elf64_Addr *)(target_base + relas[j].r_offset);

            switch (rtype) {
            case R_X86_64_64:
                *P = S;
                break;
            case R_X86_64_PC32:
            case R_X86_64_PLT32: {
                long long delta = (long long)(S - (Elf64_Addr)(unsigned long)P);
                *(int *)P = (int)delta;
                break;
            }
            case R_X86_64_32:
                *(unsigned int *)P = (unsigned int)S;
                break;
            case R_X86_64_32S:
                *(int *)P = (int)(long)S;
                break;
            }
        }
    }

    /* Find the requested symbol as entry point */
    /* For default, look for "go" or "main" or "kmain" or "minigcc_main" */
    void *entry = 0;
    const char *entry_names[] = {"go", "kmain", "minigcc_main", "cvm_main", "main", 0};
    int ei;
    for (ei = 0; entry_names[ei] && !entry; ei++) {
        unsigned k;
        for (k = 0; k < symcount; k++) {
            const char *sn = strtab + symtab[k].st_name;
            if (kstrcmp(sn, entry_names[ei]) == 0 && symtab[k].st_shndx < shnum && symtab[k].st_shndx != SHN_UNDEF) {
                entry = (char *)sec_addrs[symtab[k].st_shndx] + symtab[k].st_value;
                break;
            }
        }
    }

    if (!entry) { kfree(sec_addrs); kfree(base); return 0; }
    return entry;
}


/* ================================================================
 *  Linux ELF executable loader (ET_EXEC / ET_DYN) + process runtime
 *
 *  Loads program headers into the identity-mapped user region, applies
 *  RELATIVE / IRELATIVE / symbol relocations, sets up a System V initial
 *  stack (argc/argv/envp/auxv) and jumps to the ELF entry point.  The
 *  program talks back to the kernel through the x86-64 `syscall`
 *  instruction (see the syscall dispatcher below).
 * ================================================================ */

static unsigned long g_brk;        /* current program break         */
static unsigned long g_brk_limit;  /* upper bound for brk growth    */

static void apply_exec_relocs(void *data, unsigned long base) {
    Elf64_Ehdr *e = (Elf64_Ehdr *)data;
    Elf64_Shdr *sh = (Elf64_Shdr *)((char *)data + e->e_shoff);
    unsigned i;
    for (i = 0; i < e->e_shnum; i++) {
        if (sh[i].sh_type != SHT_RELA) continue;
        Elf64_Rela *rela = (Elf64_Rela *)((char *)data + sh[i].sh_offset);
        unsigned n = (unsigned)(sh[i].sh_size / sizeof(Elf64_Rela));
        Elf64_Sym  *syms = 0;
        const char *str  = 0;
        if (sh[i].sh_link && sh[i].sh_link < e->e_shnum) {
            Elf64_Shdr *ss = &sh[sh[i].sh_link];
            syms = (Elf64_Sym *)((char *)data + ss->sh_offset);
            if (ss->sh_link && ss->sh_link < e->e_shnum)
                str = (const char *)data + sh[ss->sh_link].sh_offset;
        }
        unsigned j;
        for (j = 0; j < n; j++) {
            unsigned    type = ELF64_R_TYPE(rela[j].r_info);
            unsigned    si   = ELF64_R_SYM(rela[j].r_info);
            unsigned long *P = (unsigned long *)(base + rela[j].r_offset);
            unsigned long S  = 0;
            if (syms && si) {
                Elf64_Sym *sym = &syms[si];
                if (sym->st_shndx != SHN_UNDEF) S = base + sym->st_value;
                else if (str) {
                    void *a = ksym_resolve(str + sym->st_name);
                    if (!a && str[sym->st_name] == '_')
                        a = ksym_resolve(str + sym->st_name + 1);
                    S = (unsigned long)a;
                }
            }
            switch (type) {
            case R_X86_64_RELATIVE:
                *P = base + (unsigned long)rela[j].r_addend;
                break;
            case R_X86_64_IRELATIVE: {
                unsigned long (*fn)(void) =
                    (unsigned long (*)(void))(base + (unsigned long)rela[j].r_addend);
                *P = fn();
                break;
            }
            case R_X86_64_64:
                *P = S + (unsigned long)rela[j].r_addend;
                break;
            case R_X86_64_GLOB_DAT:
            case R_X86_64_JUMP_SLOT:
                *P = S;
                break;
            }
        }
    }
}

void *load_exec_elf(void *data, unsigned size) {
    (void)size;
    Elf64_Ehdr *e = (Elf64_Ehdr *)data;
    if (e->e_ident[0] != 0x7F || e->e_ident[1] != 'E' ||
        e->e_ident[2] != 'L'  || e->e_ident[3] != 'F') return 0;
    if (e->e_machine != EM_X86_64) return 0;
    if (e->e_type != ET_EXEC && e->e_type != ET_DYN) return 0;

    unsigned long base = (e->e_type == ET_DYN) ? USER_LOAD_BASE : 0;

    Elf64_Phdr *ph = (Elf64_Phdr *)((char *)data + e->e_phoff);
    unsigned long max_end = 0;
    unsigned i;
    for (i = 0; i < e->e_phnum; i++) {
        if (ph[i].p_type != PT_LOAD) continue;
        unsigned long dst = base + ph[i].p_vaddr;
        if (dst < USER_LOAD_BASE || dst + ph[i].p_memsz > USER_LOAD_END)
            return 0; /* segment outside the user region */
        kmemcpy((void *)dst, (char *)data + ph[i].p_offset,
                (unsigned long)ph[i].p_filesz);
        if (ph[i].p_memsz > ph[i].p_filesz)
            kmemset((void *)(dst + ph[i].p_filesz), 0,
                    (unsigned long)(ph[i].p_memsz - ph[i].p_filesz));
        if (dst + ph[i].p_memsz > max_end) max_end = dst + ph[i].p_memsz;
    }
    if (max_end == 0) return 0;

    apply_exec_relocs(data, base);

    g_brk       = ALIGN_UP(max_end, 0x1000);
    g_brk_limit = USER_LOAD_END;
    return (void *)(base + e->e_entry);
}


/* ---- MSR access + SYSCALL/SYSRET setup ---------------------------------- */

static inline void wrmsr(unsigned msr, unsigned long val) {
    unsigned lo = (unsigned)val, hi = (unsigned)(val >> 32);
    __asm__ volatile("wrmsr" :: "c"(msr), "a"(lo), "d"(hi));
}
static inline unsigned long rdmsr(unsigned msr) {
    unsigned lo, hi;
    __asm__ volatile("rdmsr" : "=a"(lo), "=d"(hi) : "c"(msr));
    return ((unsigned long)hi << 32) | lo;
}

#define MSR_EFER   0xC0000080
#define MSR_STAR   0xC0000081
#define MSR_LSTAR  0xC0000082
#define MSR_SFMASK 0xC0000084
#define MSR_FSBASE 0xC0000100
#define MSR_GSBASE 0xC0000101

extern void syscall_entry(void);

void syscall_init(void) {
    /* SYSCALL loads CS=0x08, SS=0x10 from STAR[47:32]; SYSRET field unused. */
    wrmsr(MSR_STAR,  ((unsigned long)0x08 << 48) | ((unsigned long)0x08 << 32));
    wrmsr(MSR_LSTAR, (unsigned long)syscall_entry);
    wrmsr(MSR_SFMASK, 0x600); /* clear DF and IF on entry */
    wrmsr(MSR_EFER, rdmsr(MSR_EFER) | 1); /* SCE: enable SYSCALL */
}


/* ---- setjmp/longjmp used to unwind back to the shell on exit() ---------- */

typedef struct { unsigned long v[8]; } kjmpbuf; /* rbx rbp r12-r15 rsp rip */
int  ksetjmp(void *buf) __attribute__((returns_twice));
void klongjmp(void *buf, int val) __attribute__((noreturn));

__asm__(
    ".text\n"
    ".global ksetjmp\n"
    "ksetjmp:\n"
    "  movq %rbx,  0(%rdi)\n"
    "  movq %rbp,  8(%rdi)\n"
    "  movq %r12, 16(%rdi)\n"
    "  movq %r13, 24(%rdi)\n"
    "  movq %r14, 32(%rdi)\n"
    "  movq %r15, 40(%rdi)\n"
    "  leaq 8(%rsp), %rax\n"
    "  movq %rax, 48(%rdi)\n"
    "  movq (%rsp), %rax\n"
    "  movq %rax, 56(%rdi)\n"
    "  xorl %eax, %eax\n"
    "  ret\n"
    ".global klongjmp\n"
    "klongjmp:\n"
    "  movq  0(%rdi), %rbx\n"
    "  movq  8(%rdi), %rbp\n"
    "  movq 16(%rdi), %r12\n"
    "  movq 24(%rdi), %r13\n"
    "  movq 32(%rdi), %r14\n"
    "  movq 40(%rdi), %r15\n"
    "  movq 48(%rdi), %rsp\n"
    "  movl %esi, %eax\n"
    "  testl %eax, %eax\n"
    "  jnz 1f\n"
    "  incl %eax\n"
    "1:\n"
    "  jmp *56(%rdi)\n"
);

static kjmpbuf exec_return;
static int     exec_exit_code;


/* ---- File descriptor table for open/read/write/close -------------------- */

#define KFD_MAX 32
static KFILE *kfd_table[KFD_MAX];

static int console_getc(void); /* defined in the shell section below */


/* ---- Linux x86-64 syscall dispatcher ------------------------------------ */

struct kiovec { const char *iov_base; unsigned long iov_len; };

long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6);

long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a4; (void)a5; (void)a6;
    switch (n) {
    case 0: { /* read */
        char *buf = (char *)a2; long cnt = a3, i = 0;
        if (a1 == 0) {
            while (i < cnt) {
                int c = console_getc();
                if (c < 0) continue;
                if (c == '\r') c = '\n';
                vga_putc((char)c);
                buf[i++] = (char)c;
                if (c == '\n') break;
            }
            return i;
        }
        if (a1 >= 3 && a1 < KFD_MAX && kfd_table[a1])
            return (long)kfread(buf, 1, (unsigned long)cnt, kfd_table[a1]);
        return -9;
    }
    case 1: { /* write */
        const char *buf = (const char *)a2; long cnt = a3, i;
        if (a1 == 1 || a1 == 2) { for (i = 0; i < cnt; i++) vga_putc(buf[i]); return cnt; }
        if (a1 >= 3 && a1 < KFD_MAX && kfd_table[a1])
            return (long)kfwrite(buf, 1, (unsigned long)cnt, kfd_table[a1]);
        return -9;
    }
    case 20: { /* writev */
        struct kiovec *iov = (struct kiovec *)a2; long cnt = a3, total = 0, k;
        for (k = 0; k < cnt; k++) {
            unsigned long j;
            if (a1 == 1 || a1 == 2)
                for (j = 0; j < iov[k].iov_len; j++) vga_putc(iov[k].iov_base[j]);
            total += (long)iov[k].iov_len;
        }
        return total;
    }
    case 2: case 257: { /* open / openat */
        const char *path = (const char *)(n == 257 ? a2 : a1);
        long flags = (n == 257 ? a3 : a2);
        const char *mode = ((flags & 1) || (flags & 0x40)) ? "w" : "r";
        int fd;
        for (fd = 3; fd < KFD_MAX; fd++) if (!kfd_table[fd]) break;
        if (fd >= KFD_MAX) return -24;
        KFILE *f = kfopen(path, mode);
        if (!f) return -2;
        kfd_table[fd] = f;
        return fd;
    }
    case 3: /* close */
        if (a1 >= 3 && a1 < KFD_MAX && kfd_table[a1]) {
            kfclose(kfd_table[a1]); kfd_table[a1] = 0;
        }
        return 0;
    case 8: /* lseek */
        if (a1 >= 3 && a1 < KFD_MAX && kfd_table[a1]) {
            kfseek(kfd_table[a1], a2, (int)a3);
            return kftell(kfd_table[a1]);
        }
        return -9;
    case 12: { /* brk */
        unsigned long addr = (unsigned long)a1;
        if (addr == 0) return (long)g_brk;
        if (addr >= USER_LOAD_BASE && addr <= g_brk_limit) g_brk = addr;
        return (long)g_brk;
    }
    case 9: { /* mmap (anonymous only) */
        unsigned long len = (unsigned long)a2;
        void *p = kmalloc(len ? len : 1);
        return p ? (long)p : -12;
    }
    case 11: return 0; /* munmap */
    case 158: /* arch_prctl */
        if (a1 == 0x1002) { wrmsr(MSR_FSBASE, (unsigned long)a2); return 0; }
        if (a1 == 0x1001) { wrmsr(MSR_GSBASE, (unsigned long)a2); return 0; }
        return -22;
    case 218: return 1;  /* set_tid_address */
    case 228: /* clock_gettime */
        if (a2) { unsigned long *ts = (unsigned long *)a2; ts[0] = 0; ts[1] = 0; }
        return 0;
    case 16: return 0;   /* ioctl */
    case 39: return 1;   /* getpid */
    case 60: case 231:   /* exit / exit_group */
        exec_exit_code = (int)a1;
        klongjmp(&exec_return, 1);
        return 0; /* unreachable */
    default:
        return -38; /* ENOSYS */
    }
}


/* ---- syscall trampoline: marshal Linux ABI regs into the C ABI ---------- */

__asm__(
    ".text\n"
    ".global syscall_entry\n"
    "syscall_entry:\n"
    "  subq $128, %rsp\n"        /* preserve the interrupted red zone */
    "  pushq %r9\n"              /* 64(%rsp) a6 */
    "  pushq %r8\n"              /* 56       a5 */
    "  pushq %r10\n"             /* 48       a4 */
    "  pushq %rdx\n"             /* 40       a3 */
    "  pushq %rsi\n"             /* 32       a2 */
    "  pushq %rdi\n"             /* 24       a1 */
    "  pushq %rax\n"             /* 16       n / return value slot */
    "  pushq %rcx\n"             /*  8       user rip */
    "  pushq %r11\n"             /*  0       user rflags */
    "  movq 16(%rsp), %rdi\n"    /* C arg1 = n  */
    "  movq 24(%rsp), %rsi\n"    /* C arg2 = a1 */
    "  movq 32(%rsp), %rdx\n"    /* C arg3 = a2 */
    "  movq 40(%rsp), %rcx\n"    /* C arg4 = a3 */
    "  movq 48(%rsp), %r8\n"     /* C arg5 = a4 */
    "  movq 56(%rsp), %r9\n"     /* C arg6 = a5 */
    "  movq 64(%rsp), %rax\n"
    "  pushq %rax\n"             /* C arg7 = a6 (stack) */
    "  call ksyscall\n"
    "  addq $8, %rsp\n"
    "  movq %rax, 16(%rsp)\n"    /* stash return value in the n slot */
    "  popq %r11\n"
    "  popq %rcx\n"
    "  popq %rax\n"
    "  popq %rdi\n"
    "  popq %rsi\n"
    "  popq %rdx\n"
    "  popq %r10\n"
    "  popq %r8\n"
    "  popq %r9\n"
    "  addq $128, %rsp\n"
    "  jmp *%rcx\n"              /* return to user, staying in ring 0 */
);


/* ---- Build the SysV initial stack and jump to the ELF entry ------------- */

#define USTACK_SIZE (256 * 1024)

static unsigned long *setup_user_stack(char *sbase, unsigned long ssize,
                                       int argc, char **argv) {
    char *p = sbase + ssize;
    char *argp[64];
    int i;
    if (argc > 64) argc = 64;
    for (i = 0; i < argc; i++) {
        unsigned long l = kstrlen(argv[i]) + 1;
        p -= l;
        kmemcpy(p, argv[i], l);
        argp[i] = p;
    }
    p -= 16;                       /* 16 random bytes for AT_RANDOM */
    char *randp = p;
    for (i = 0; i < 16; i++) randp[i] = (char)(0x37 + i);
    p = (char *)((unsigned long)p & ~15UL);

    int nwords = 1 + argc + 1 + 1 + 6; /* argc, argv[], NULL, envp NULL, 3 aux pairs */
    unsigned long sp = ((unsigned long)p - (unsigned long)nwords * 8) & ~15UL;
    unsigned long *w = (unsigned long *)sp;
    int idx = 0;
    w[idx++] = (unsigned long)argc;
    for (i = 0; i < argc; i++) w[idx++] = (unsigned long)argp[i];
    w[idx++] = 0;                       /* argv terminator */
    w[idx++] = 0;                       /* envp terminator */
    w[idx++] = 6;  w[idx++] = 4096;                     /* AT_PAGESZ */
    w[idx++] = 25; w[idx++] = (unsigned long)randp;     /* AT_RANDOM */
    w[idx++] = 0;  w[idx++] = 0;                        /* AT_NULL   */
    return w;
}

int k_exec_user(void *entry, int argc, char **argv) {
    char *stk = kmalloc(USTACK_SIZE);
    if (!stk) return -1;
    unsigned long *sp = setup_user_stack(stk, USTACK_SIZE, argc, argv);
    exec_exit_code = 0;

    if (ksetjmp(&exec_return) == 0) {
        __asm__ volatile(
            "movq %0, %%rsp\n\t"
            "xorq %%rbp, %%rbp\n\t"
            "jmpq *%1\n\t"
            :: "r"(sp), "r"(entry) : "memory");
        __builtin_unreachable();
    }

    /* exit() longjmp'd back here */
    wrmsr(MSR_FSBASE, 0);
    wrmsr(MSR_GSBASE, 0);
    kfree(stk);
    return exec_exit_code;
}

/* Run an ET_REL program as a plain function call, but catch a libc exit(). */
int k_run_rel(prog_entry_t entry, int argc, char **argv) {
    exec_exit_code = 0;
    if (ksetjmp(&exec_return) == 0)
        return entry(argc, argv);
    return exec_exit_code;
}

/* libc exit() for loaded programs: unwind back to the shell. */
void kexit(int code) {
    exec_exit_code = code;
    klongjmp(&exec_return, 1);
}


/* ================================================================
 *  Shell
 * ================================================================ */

#define CMD_BUF_SZ 256
#define MAX_ARGS   16

static char cmd_buf[CMD_BUF_SZ];
static int  cmd_pos;

static void shell_prompt(void) { vga_puts("\nminiOS> "); }

static void shell_exec_builtin(int argc, char **argv);

/* Blocking read from either the PS/2 keyboard or COM1 serial line. */
static int console_getc(void) {
    while (1) {
        if (serial_available()) {
            int c = serial_getc();
            if (c >= 0) return c;
        }
        if (kbd_available()) {
            int c = kbd_read();
            if (c >= 0) return c;
        }
        __asm__ volatile("pause");
    }
}

static void shell_readline(void) {
    cmd_pos = 0;
    kmemset(cmd_buf, 0, CMD_BUF_SZ);

    while (1) {
        int c = console_getc();
        if (c < 0) continue;
        if (c == '\n' || c == '\r') {
            vga_putc('\n');
            cmd_buf[cmd_pos] = 0;
            return;
        }
        if (c == '\b' || c == 0x7F) {
            if (cmd_pos > 0) {
                cmd_pos--;
                vga_putc('\b');
            }
            continue;
        }
        if (cmd_pos < CMD_BUF_SZ - 1 && c >= 32 && c < 127) {
            cmd_buf[cmd_pos++] = (char)c;
            vga_putc((char)c);
        }
    }
}

static int shell_parse(char *line, char **argv, int max_args) {
    int argc = 0;
    char *p = line;
    while (*p && argc < max_args) {
        while (*p == ' ' || *p == '\t') p++;
        if (*p == 0) break;
        argv[argc++] = p;
        while (*p && *p != ' ' && *p != '\t') p++;
        if (*p) { *p = 0; p++; }
    }
    argv[argc] = 0;
    return argc;
}

void shell_run(void) {
    while (1) {
        shell_prompt();
        shell_readline();

        if (cmd_buf[0] == 0) continue;

        char *argv[MAX_ARGS + 1];
        int argc = shell_parse(cmd_buf, argv, MAX_ARGS);

        if (argc == 0) continue;

        /* Try built-in */
        shell_exec_builtin(argc, argv);
    }
}

/* Load an ELF file from the ramdisk and register it under its filename stem.
 * Returns 1 for an ET_REL program, 2 for an ET_EXEC/ET_DYN Linux process,
 * 0 on failure.  progname_out must hold at least 32 bytes. */
static int shell_load(const char *fname, char *progname_out, void **entry_out) {
    RDFile *f = ramdisk_open(fname);
    if (!f) return 0;
    unsigned char *data = kmalloc(f->size);
    if (!data) return 0;
    ramdisk_read(f, data, 0, f->size);

    const char *dot = kstrchr(fname, '.');
    int nl = dot ? (int)(dot - fname) : (int)kstrlen(fname);
    if (nl > 30) nl = 30;
    kmemcpy(progname_out, fname, nl);
    progname_out[nl] = 0;

    int kind = 0;
    void *entry = 0;
    if (data[0] == 0x7F && data[1] == 'E' && data[2] == 'L' && data[3] == 'F') {
        Elf64_Half etype = ((Elf64_Ehdr *)data)->e_type;
        if (etype == ET_REL) {
            entry = elf_load(data, f->size);
            if (entry) { k_register_program(progname_out, (prog_entry_t)entry); kind = 1; }
        } else if (etype == ET_EXEC || etype == ET_DYN) {
            entry = load_exec_elf(data, f->size);
            if (entry) { k_register_process(progname_out, entry); kind = 2; }
        }
    }
    if (entry_out) *entry_out = entry;
    kfree(data);
    return kind;
}

static void shell_exec_builtin(int argc, char **argv) {
    if (kstrcmp(argv[0], "help") == 0) {
        vga_puts("Commands: help clear ls cat echo load run\n");
        vga_puts("  load <file>        load an ELF (.o relocatable or Linux exe)\n");
        vga_puts("  run  <name|file>   run a loaded program or ELF from disk\n");
    }
    else if (kstrcmp(argv[0], "clear") == 0) {
        vga_clear();
    }
    else if (kstrcmp(argv[0], "ls") == 0) {
        RDFile *files[RAMDISK_MAX_FILES];
        int n = ramdisk_list(files, RAMDISK_MAX_FILES);
        int i;
        for (i = 0; i < n; i++) {
            kprintf("  %-20s  %u bytes\n", files[i]->name, files[i]->size);
        }
        if (n == 0) vga_puts("  (empty)\n");
    }
    else if (kstrcmp(argv[0], "cat") == 0) {
        if (argc < 2) { vga_puts("usage: cat <file>\n"); return; }
        RDFile *f = ramdisk_open(argv[1]);
        if (!f) { kprintf("cat: %s: no such file\n", argv[1]); return; }
        unsigned i;
        for (i = 0; i < f->size; i++) {
            char c;
            ramdisk_read(f, &c, i, 1);
            vga_putc(c);
        }
        vga_putc('\n');
    }
    else if (kstrcmp(argv[0], "echo") == 0) {
        int i;
        for (i = 1; i < argc; i++) {
            if (i > 1) vga_putc(' ');
            vga_puts(argv[i]);
        }
        vga_putc('\n');
    }
    else if (kstrcmp(argv[0], "load") == 0) {
        if (argc < 2) { vga_puts("usage: load <file>\n"); return; }
        char progname[32];
        void *entry = 0;
        int kind = shell_load(argv[1], progname, &entry);
        if (kind == 0) { kprintf("load: %s: not an ELF or load failed\n", argv[1]); return; }
        if (kind == 1) kprintf("Loaded relocatable '%s' at %p\n", progname, entry);
        else           kprintf("Loaded Linux ELF '%s' entry %p  (run %s)\n",
                               progname, entry, progname);
    }
    else if (kstrcmp(argv[0], "run") == 0) {
        if (argc < 2) { vga_puts("usage: run <program|file> [args...]\n"); return; }
        int i, found = 0;
        for (i = 0; i < kprog_count; i++)
            if (kstrcmp(kprog_table[i].name, argv[1]) == 0) { found = 1; break; }
        const char *target = argv[1];
        char progname[32];
        if (!found) {
            void *entry = 0;
            if (!shell_load(argv[1], progname, &entry)) {
                kprintf("run: %s: not found\n", argv[1]);
                return;
            }
            target = progname;
        }
        int ret = k_spawn(target, argc - 1, argv + 1);
        kprintf("exit code: %d\n", ret);
    }
    else {
        /* Try to run as registered program */
        int ret = k_spawn(argv[0], argc, argv);
        if (ret == -1) {
            kprintf("%s: command not found\n", argv[0]);
        } else {
            kprintf("exit code: %d\n", ret);
        }
    }
}


/* ================================================================
 *  Libc symbol registration
 * ================================================================ */

static void register_libc_symbols(void) {
    /* String functions */
    k_register_symbol("strlen",   (void *)kstrlen);
    k_register_symbol("strcpy",   (void *)kstrcpy);
    k_register_symbol("strncpy",  (void *)kstrncpy);
    k_register_symbol("strcmp",   (void *)kstrcmp);
    k_register_symbol("strncmp",  (void *)kstrncmp);
    k_register_symbol("strchr",   (void *)kstrchr);
    k_register_symbol("strstr",   (void *)kstrstr);
    k_register_symbol("memcpy",   (void *)kmemcpy);
    k_register_symbol("memmove",  (void *)kmemmove);
    k_register_symbol("memset",   (void *)kmemset);
    k_register_symbol("memcmp",   (void *)kmemcmp);
    k_register_symbol("strlen",   (void *)kstrlen);

    /* Memory */
    k_register_symbol("malloc",   (void *)kmalloc);
    k_register_symbol("free",     (void *)kfree);
    k_register_symbol("calloc",   (void *)kcalloc);
    k_register_symbol("realloc",  (void *)krealloc);

    /* File I/O */
    k_register_symbol("fopen",    (void *)kfopen);
    k_register_symbol("fclose",   (void *)kfclose);
    k_register_symbol("fread",    (void *)kfread);
    k_register_symbol("fwrite",   (void *)kfwrite);
    k_register_symbol("fseek",    (void *)kfseek);
    k_register_symbol("ftell",    (void *)kftell);
    k_register_symbol("fputs",    (void *)kfputs);
    k_register_symbol("fputc",    (void *)kfputc);
    k_register_symbol("fgetc",    (void *)kfgetc);
    k_register_symbol("ungetc",   (void *)kfungetc);
    k_register_symbol("fflush",   (void *)kfflush);
    k_register_symbol("rewind",   (void *)krewind);
    k_register_symbol("fprintf",  (void *)kfprintf);

    /* Output */
    k_register_symbol("printf",   (void *)kprintf);
    k_register_symbol("sprintf",  (void *)ksprintf);
    k_register_symbol("putchar",  (void *)vga_putc);
    k_register_symbol("puts",     (void *)vga_puts);

    /* Stdio streams are FILE* *variables*: register the address of each. */
    k_register_symbol("stdin",    (void *)&kstdin);
    k_register_symbol("stdout",   (void *)&kstdout);
    k_register_symbol("stderr",   (void *)&kstderr);

    /* Exit */
    k_register_symbol("exit",     (void *)kexit);

    /* Additional libc */
    k_register_symbol("snprintf", (void *)ksnprintf);
    k_register_symbol("perror",   (void *)0);
    k_register_symbol("atol",     (void *)katol);
    k_register_symbol("strtol",   (void *)katol);
    k_register_symbol("qsort",    (void *)0);
    k_register_symbol("abort",    (void *)kexit);

    /* Syscalls */
    k_register_symbol("write",    (void *)0);
    k_register_symbol("read",     (void *)0);
    k_register_symbol("open",     (void *)0);
    k_register_symbol("close",    (void *)0);
    k_register_symbol("lseek",    (void *)0);
    k_register_symbol("fdopen",   (void *)0);
    k_register_symbol("fileno",   (void *)0);

    /* POSIX/file */
    k_register_symbol("open",     (void *)0);
    k_register_symbol("read",     (void *)0);
    k_register_symbol("lseek",    (void *)0);
    k_register_symbol("close",    (void *)0);
    k_register_symbol("write",    (void *)0);

    /* mmap/mprotect */
    k_register_symbol("mmap",     (void *)0);
    k_register_symbol("mprotect", (void *)0);
    k_register_symbol("munmap",   (void *)0);

    /* dlfcn */
    k_register_symbol("dlopen",   (void *)0);
    k_register_symbol("dlsym",    (void *)0);
    k_register_symbol("dlclose",  (void *)0);
    k_register_symbol("dlerror",  (void *)0);
}


/* ================================================================
 *  Kernel entry point
 * ================================================================ */

extern char ramdisk_start[];
extern char ramdisk_end[];

__attribute__((section(".init.text")))
void kmain(void) {
    __asm__ volatile(
        "mov $0x10, %%ax\n"
        "mov %%ax, %%ds\n"
        "mov %%ax, %%es\n"
        "mov %%ax, %%fs\n"
        "mov %%ax, %%gs\n"
        "mov %%ax, %%ss\n"
        "mov $0x90000, %%rsp\n"
        ::: "ax"
    );

    /* Enable SSE so loaded programs (and Linux binaries) may use XMM/SSE2.
     * CR0: clear EM (bit 2), set MP (bit 1); CR4: set OSFXSR|OSXMMEXCPT. */
    __asm__ volatile(
        "mov %%cr0, %%rax\n"
        "and $0xFFFFFFFFFFFFFFFB, %%rax\n"
        "or  $0x2, %%rax\n"
        "mov %%rax, %%cr0\n"
        "mov %%cr4, %%rax\n"
        "or  $0x600, %%rax\n"
        "mov %%rax, %%cr4\n"
        ::: "rax"
    );

    serial_init();
    vga_clear();
    vga_puts("MiniOS Kernel v0.3\n====================\n");

    kallocator_init();
    ramdisk_init();
    register_libc_symbols();
    syscall_init();

    if ((unsigned long)(ramdisk_end - ramdisk_start) > 0) {
        ramdisk_setup_from(ramdisk_start, (unsigned)(ramdisk_end - ramdisk_start));
    }

    kprintf("Heap: 64 MB  Symbols: %d  (Linux ELF: syscall ABI ready)\n", ksym_count);

    shell_run();
}
