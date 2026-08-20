#include "kernel.h"
#include "net.h"
#include "tls.h"
#include "bootdefs.h"

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

/* Console output capture used by shell redirection. While a capture is
 * active every character produced through vga_putc is accumulated in memory
 * instead of reaching the screen, and the shell commits the result to a
 * ramdisk file once the command returns. */
#define REDIR_INITIAL_CAP (16UL * 1024)
#define REDIR_MAX_BYTES   (16UL * 1024 * 1024)

static char         *redir_buf;
static unsigned long  redir_len;
static unsigned long  redir_cap;
static int            redir_active;
static int            redir_overflow;

static int redir_grow(void) {
    unsigned long want = redir_cap ? redir_cap * 2 : REDIR_INITIAL_CAP;
    if (want > REDIR_MAX_BYTES) return 0;
    char *grown = krealloc(redir_buf, want);
    if (!grown) return 0;
    redir_buf = grown;
    redir_cap = want;
    return 1;
}

void vga_putc(char c) {
    if (redir_active) {
        if (redir_len < redir_cap || redir_grow()) redir_buf[redir_len++] = c;
        else redir_overflow = 1;
        return;
    }
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

/* PS/2 set 1 arrow keys arrive as E0-prefixed make codes; they are
 * translated into the same three-byte CSI sequence a serial terminal
 * sends (ESC [ A / ESC [ B) and buffered here. */
#define KBD_QUEUE_LEN 4
static unsigned char kbd_queue[KBD_QUEUE_LEN];
static int kbd_q_head, kbd_q_tail;
static int kbd_e0;

static void kbd_q_push(unsigned char c) {
    int next = (kbd_q_tail + 1) % KBD_QUEUE_LEN;
    if (next == kbd_q_head) return;
    kbd_queue[kbd_q_tail] = c;
    kbd_q_tail = next;
}

static int kbd_q_empty(void) { return kbd_q_head == kbd_q_tail; }

static int kbd_q_pop(void) {
    if (kbd_q_empty()) return -1;
    unsigned char c = kbd_queue[kbd_q_head];
    kbd_q_head = (kbd_q_head + 1) % KBD_QUEUE_LEN;
    return (int)c;
}

static int kbd_q_peek(void) {
    if (kbd_q_empty()) return -1;
    return (int)kbd_queue[kbd_q_head];
}

int kbd_available(void) {
    unsigned char s;
    __asm__ volatile("inb $0x64, %0" : "=a"(s));
    return (s & 1);
}

int kbd_read(void) {
    if (!kbd_q_empty()) return kbd_q_pop();
    while (!kbd_available()) __asm__ volatile("pause");
    unsigned char sc;
    __asm__ volatile("inb $0x60, %0" : "=a"(sc));

    if (sc & 0x80) { /* key release */
        sc &= 0x7F;
        if (sc == KEY_LSHIFT || sc == KEY_RSHIFT) kbd_shift = 0;
        if (sc == KEY_E0) kbd_e0 = 0;
        return -1;
    }

    if (sc == KEY_E0) { kbd_e0 = 1; return -1; }

    if (kbd_e0) {
        kbd_e0 = 0;
        if (sc == KEY_UP) {
            kbd_q_push(KEY_ESC); kbd_q_push(KEY_CSI); kbd_q_push(KEY_ARR_UP);
        } else if (sc == KEY_DOWN) {
            kbd_q_push(KEY_ESC); kbd_q_push(KEY_CSI); kbd_q_push(KEY_ARR_DOWN);
        }
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
#define FREE_MAGIC  0xFEEDC0DE
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
#define USER_STACK_SIZE (256UL * 1024)
#define USER_STACK_TOP  USER_LOAD_END
#define USER_STACK_BASE (USER_STACK_TOP - USER_STACK_SIZE)
#define USER_BRK_END    USER_STACK_BASE
#define SYS_KSTK_TOP    0x00088000UL
#define SYS_KSTK_BASE   (SYS_KSTK_TOP - 0x8000)
#define HEAP_BASE       0x02000000UL
#define HEAP_SIZE       (64UL * 1024 * 1024)

#define EFAULT  (-14)

/* Asm-safe (no UL suffix) mirror of the user window for the syscall-entry
 * return discriminator; the trampoline is a raw string literal, so the C
 * preprocessor cannot paste the UL-suffixed macros into it. */
#define USER_WIN_LO     0x00400000
#define USER_WIN_HI     0x02000000
#define STR_(x) #x
#define STR(x)  STR_(x)

/* Mark the user window [USER_LOAD_BASE, USER_LOAD_END) as user-accessible
 * (U/S bit) in the 2 MB page directory built by the boot path. A ring-3
 * access requires U/S set at every level of the walk, so the PML4 and PDPT
 * entries that cover the whole identity map are lifted too; the per-2 MB
 * isolation then lives entirely in the PD leaf bits, and every other page —
 * page tables, kernel image, heap, VGA, MMIO — stays supervisor, so a
 * ring-3 program is stopped in hardware from reading or writing kernel
 * memory. */
static void mm_setup_protections(void) {
    volatile unsigned long *pml4 = (volatile unsigned long *)PT_PML4_ADDR;
    volatile unsigned long *pdpt = (volatile unsigned long *)PT_PDPT_ADDR;
    volatile unsigned long *pd = (volatile unsigned long *)PT_PD_ADDR;
    unsigned long lo = USER_LOAD_BASE >> PT_PD_INDEX_SHIFT;
    unsigned long hi = (USER_LOAD_END - 1) >> PT_PD_INDEX_SHIFT;
    unsigned long i;
    pml4[0] |= (unsigned long)PT_FLAGS_USER;
    pdpt[0] |= (unsigned long)PT_FLAGS_USER;
    for (i = lo; i <= hi; i++) pd[i] |= (unsigned long)PT_FLAGS_USER;
    __asm__ volatile("mov %%cr3, %%rax; mov %%rax, %%cr3" ::: "rax", "memory");
}

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
            /* Split the remainder back into the free list: reusing a
             * big block for a small request must never swallow the
             * space the request did not use. */
            unsigned long rem = b->size - size;
            if (rem >= BLOCK_HDR_SZ + 16) {
                Block *tail = (Block *)((char *)b + BLOCK_HDR_SZ + size);
                tail->magic = FREE_MAGIC;
                tail->size  = rem - BLOCK_HDR_SZ;
                tail->next  = free_list;
                free_list   = tail;
            }
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
    b->magic = FREE_MAGIC;
    /* Coalesce with physically adjacent free blocks so consecutive
     * frees rebuild one big block instead of a chain of crumbs. */
    int merged = 1;
    while (merged) {
        merged = 0;
        Block *prev = 0, *fb = free_list;
        while (fb) {
            if ((char *)fb + BLOCK_HDR_SZ + fb->size == (char *)b) {
                fb->size += BLOCK_HDR_SZ + b->size;
                if (prev) prev->next = fb->next;
                else       free_list  = fb->next;
                b = fb;
                merged = 1;
                break;
            }
            if ((char *)b + BLOCK_HDR_SZ + b->size == (char *)fb) {
                b->size += BLOCK_HDR_SZ + fb->size;
                if (prev) prev->next = fb->next;
                else       free_list  = fb->next;
                merged = 1;
                break;
            }
            prev = fb;
            fb = fb->next;
        }
    }
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
    size = ALIGN_UP(size, 16);
    Block *b = (Block *)((char *)ptr - BLOCK_HDR_SZ);
    if (b->magic != ALLOC_MAGIC) return 0;
    if (b->size >= size) {
        unsigned long rem = b->size - size;
        if (rem >= BLOCK_HDR_SZ + 16) {
            Block *tail = (Block *)((char *)b + BLOCK_HDR_SZ + size);
            tail->magic = FREE_MAGIC;
            tail->size  = rem - BLOCK_HDR_SZ;
            tail->next  = free_list;
            free_list   = tail;
        }
        b->size = size;
        return ptr;
    }
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

char *kstrncat(char *dst, const char *src, unsigned long n) {
    char *d = dst;
    while (*d) d++;
    while (n-- && *src) *d++ = *src++;
    *d = 0;
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

#define RD_MAGIC       0x4B534452
#define RD_HEADER_SIZE 8
#define RD_ENTRY_SIZE  (RAMDISK_FNAME_LEN + 8)
#define RD_DATA_MIN    (512UL * 1024)
#define RD_DATA_SPARE  (1024UL * 1024)
#define RD_DATA_MAX    (64UL * 1024 * 1024)

typedef struct {
    unsigned magic;
    unsigned count;
    RDFile  files[RAMDISK_MAX_FILES];
} RDSuper;

static RDSuper *rd;
static char    *rd_data;
static unsigned rd_used;
static unsigned rd_cap;

/* Reserve a data area of `want` bytes, clamped to the configured maximum.
 * An existing area is kept when it is already large enough, otherwise the
 * live contents are carried over to the new one. Returns 1 on success. */
static int ramdisk_reserve(unsigned long want) {
    if (want > RD_DATA_MAX) return 0;
    if (want < RD_DATA_MIN) want = RD_DATA_MIN;
    if (rd_data && rd_cap >= want) return 1;
    char *area = kmalloc(want);
    if (!area) return 0;
    kmemset(area, 0, want);
    if (rd_data && rd_used > 0) kmemcpy(area, rd_data, rd_used);
    if (rd_data) kfree(rd_data);
    rd_data = area;
    rd_cap  = (unsigned)want;
    return 1;
}

/* Populate the ramdisk from a packed image. The image is validated in full
 * before any entry is published, so a rejected image leaves the directory
 * untouched instead of advertising files whose data was never copied. */
void ramdisk_setup_from(void *data, unsigned size) {
    char *raw = (char *)data;
    unsigned i;

    if (!raw || size < RD_HEADER_SIZE) return;
    if (*(unsigned *)raw != RD_MAGIC) return;

    unsigned count = *(unsigned *)(raw + 4);
    if (count > RAMDISK_MAX_FILES) return;

    unsigned long table_bytes = (unsigned long)count * RD_ENTRY_SIZE;
    if (table_bytes > (unsigned long)size - RD_HEADER_SIZE) return;

    char *entry_start = raw + RD_HEADER_SIZE;
    char *data_start  = entry_start + table_bytes;
    unsigned long payload = (unsigned long)size - RD_HEADER_SIZE - table_bytes;

    unsigned long total = 0;
    for (i = 0; i < count; i++) {
        char *esrc = entry_start + (unsigned long)i * RD_ENTRY_SIZE;
        unsigned fsize = *(unsigned *)(esrc + RAMDISK_FNAME_LEN);
        unsigned forig = *(unsigned *)(esrc + RAMDISK_FNAME_LEN + 4);
        if (forig > payload || fsize > payload - forig) return;
        if (total > RD_DATA_MAX - fsize) return;
        total += fsize;
    }

    if (!rd) ramdisk_init();
    if (!rd) return;
    if (!ramdisk_reserve(total + RD_DATA_SPARE)) {
        kprintf("ramdisk: image needs %u bytes, capacity unavailable\n",
                (unsigned)total);
        return;
    }

    unsigned offset = 0;
    for (i = 0; i < count; i++) {
        char *esrc = entry_start + (unsigned long)i * RD_ENTRY_SIZE;
        unsigned fsize = *(unsigned *)(esrc + RAMDISK_FNAME_LEN);
        unsigned forig = *(unsigned *)(esrc + RAMDISK_FNAME_LEN + 4);
        RDFile *f = &rd->files[i];
        kmemcpy(f->name, esrc, RAMDISK_FNAME_LEN);
        f->name[RAMDISK_FNAME_LEN - 1] = 0;
        f->size   = fsize;
        f->offset = offset;
        if (fsize) kmemcpy(rd_data + offset, data_start + forig, fsize);
        offset += fsize;
    }
    rd->count = count;
    rd_used   = offset;
}

void ramdisk_init(void) {
    if (!rd) {
        rd = kcalloc(1, sizeof(RDSuper));
        if (!rd) return;
        rd_used = 0;
        rd_cap  = 0;
        rd_data = 0;
        if (!ramdisk_reserve(RD_DATA_MIN)) {
            kfree(rd);
            rd = 0;
            return;
        }
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
    if (!rd || !name || rd->count >= RAMDISK_MAX_FILES) return 0;
    if (size > RD_DATA_MAX - rd_used) return 0;
    if (!ramdisk_reserve((unsigned long)rd_used + size)) return 0;
    RDFile *f = &rd->files[rd->count];
    kstrncpy(f->name, name, RAMDISK_FNAME_LEN - 1);
    f->name[RAMDISK_FNAME_LEN - 1] = 0;
    f->size   = size;
    f->offset = rd_used;
    rd_used  += size;
    rd->count++;
    return f;
}

/* Grow or shrink an existing file by relocating the data that follows it.
 * Files are stored back to back in the data area; this moves every file
 * after `f` by the size delta. Returns 1 on success, 0 on overflow. */
int ramdisk_resize(RDFile *f, unsigned newsize) {
    unsigned i;
    if (!rd || !f || !rd_data) return 0;
    if (newsize == f->size) return 1;

    unsigned old_end = f->offset + f->size;
    unsigned new_end = f->offset + newsize;
    unsigned delta;
    unsigned move_len;

    if (newsize > f->size) {
        delta = newsize - f->size;
        if (delta > RD_DATA_MAX - rd_used) return 0;
        if (!ramdisk_reserve((unsigned long)rd_used + delta)) return 0;
        move_len = rd_used - old_end;
        for (i = 0; i < rd->count; i++)
            if (&rd->files[i] != f && rd->files[i].offset >= old_end)
                rd->files[i].offset += delta;
        kmemmove(rd_data + new_end, rd_data + old_end, move_len);
        kmemset(rd_data + old_end, 0, delta);
        f->size  = newsize;
        rd_used += delta;
        return 1;
    }

    delta    = f->size - newsize;
    move_len = rd_used - old_end;
    kmemmove(rd_data + new_end, rd_data + old_end, move_len);
    kmemset(rd_data + rd_used - delta, 0, delta);
    for (i = 0; i < rd->count; i++)
        if (&rd->files[i] != f && rd->files[i].offset >= old_end)
            rd->files[i].offset -= delta;
    f->size  = newsize;
    rd_used -= delta;
    return 1;
}

int ramdisk_list(RDFile **out, int max) {
    if (!rd) return 0;
    int n = (int)rd->count < max ? (int)rd->count : max;
    unsigned i;
    for (i = 0; i < (unsigned)n; i++) out[i] = &rd->files[i];
    return n;
}

/* Remove an entry and compact the data area. Files after `f` are shifted
 * left by f->size and the directory slot is dropped. Returns 1 on success,
 * 0 when the pointer is not a live entry. */
int ramdisk_delete(RDFile *f) {
    unsigned i;
    int idx = -1;
    if (!rd || !f) return 0;
    for (i = 0; i < rd->count; i++) {
        if (&rd->files[i] == f) { idx = (int)i; break; }
    }
    if (idx < 0) return 0;

    unsigned old_end = f->offset + f->size;
    unsigned move_len = rd_used - old_end;
    kmemmove(rd_data + f->offset, rd_data + old_end, move_len);
    for (i = 0; i < rd->count; i++)
        if (&rd->files[i] != f && rd->files[i].offset >= old_end)
            rd->files[i].offset -= f->size;
    for (i = (unsigned)idx; i + 1 < rd->count; i++)
        rd->files[i] = rd->files[i + 1];
    rd->count--;
    rd_used -= f->size;
    return 1;
}


/* ================================================================
 *  FILE interface (wraps ramdisk)
 * ================================================================ */

/* Working directory. Root is the empty string; every other cwd ends in '/'.
 * A directory is a ramdisk name ending in '/': it exists when the exact
 * entry exists or some file name starts with it. */
static char fs_cwd[RAMDISK_FNAME_LEN];

/* Resolve a path against the cwd into `out` (cap >= RAMDISK_FNAME_LEN).
 * A leading '/' starts from the root, '..' pops one component, '.' and
 * empty components are skipped. Returns 1 on success; a name that does
 * not fit is rejected like a missing file, never truncated. */
static int fs_resolve(const char *path, char *out, unsigned cap) {
    unsigned len = 0;
    const char *p = path;
    out[0] = 0;
    if (*p == '/') p++;
    else {
        kmemcpy(out, fs_cwd, kstrlen(fs_cwd) + 1);
        len = (unsigned)kstrlen(out);
    }
    while (*p) {
        const char *start = p;
        while (*p && *p != '/') p++;
        unsigned clen = (unsigned)(p - start);
        if (clen == 0 || (clen == 1 && start[0] == '.')) { if (*p) p++; continue; }
        if (clen == 2 && start[0] == '.' && start[1] == '.') {
            if (len > 0) {
                len--;
                while (len > 0 && out[len - 1] != '/') len--;
                out[len] = 0;
            }
            if (*p) p++;
            continue;
        }
        if (len + 1 + clen >= cap) return 0;
        if (len > 0 && out[len - 1] != '/') out[len++] = '/';
        kmemcpy(out + len, start, clen);
        len += clen;
        out[len] = 0;
        if (*p) p++;
    }
    return 1;
}

/* Does the directory `dir` (ending in '/') exist? The root always does. */
static int fs_dir_exists(const char *dir) {
    unsigned i;
    if (!dir[0]) return 1;
    for (i = 0; i < rd->count; i++)
        if (kstrncmp(rd->files[i].name, dir, kstrlen(dir)) == 0) return 1;
    return 0;
}

/* Return 1 when the resolved name refers to a directory: a trailing '/'
 * always does, otherwise the name denotes a directory when no exact file
 * entry exists and some entry starts with `<name>/`. */
static int fs_is_dir(const char *resolved) {
    unsigned len = (unsigned)kstrlen(resolved);
    if (len == 0) return 0;
    if (resolved[len - 1] == '/') return 1;
    if (ramdisk_open(resolved)) return 0;
    char with_slash[RAMDISK_FNAME_LEN];
    if (len + 1 >= sizeof(with_slash)) return 0;
    kmemcpy(with_slash, resolved, len);
    with_slash[len] = '/';
    with_slash[len + 1] = 0;
    return fs_dir_exists(with_slash);
}

KFILE *kfopen(const char *path, const char *mode) {
    char resolved[RAMDISK_FNAME_LEN];
    if (!fs_resolve(path, resolved, sizeof(resolved))) return 0;
    if (fs_is_dir(resolved)) return 0;      /* never open a directory */
    KFILE *f = kmalloc(sizeof(KFILE));
    if (!f) return 0;
    kmemset(f, 0, sizeof(KFILE));
    f->rf = ramdisk_open(resolved);
    if (!f->rf && (mode[0] == 'w' || mode[0] == 'a')) {
        f->rf = ramdisk_create(resolved, 0);
        if (!f->rf) { kfree(f); return 0; }
    }
    if (!f->rf) { kfree(f); return 0; }
    f->mode = (mode[0] == 'w') ? 1 : ((mode[0] == 'a') ? 2 : 0);
    f->pos  = (f->mode == 2) ? f->rf->size : 0;
    if (f->mode != 0) {
        if (f->mode == 1 && f->rf->size && !ramdisk_resize(f->rf, 0)) { kfree(f); return 0; }
        f->wbuf = kmalloc(4096);
        f->wcap = 4096;
        f->wsize = 0;
        if (!f->wbuf) { kfree(f); return 0; }
    }
    return f;
}

int kfclose(KFILE *f) {
    int rc = 0;
    if (!f) return 0;
    if (f->mode != 0) rc = kfflush(f);
    if (f->wbuf) kfree(f->wbuf);
    kfree(f);
    return rc;
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

/* Read at most size-1 bytes up to and including the first newline. Returns
 * buf, or 0 when nothing could be read. */
char *kfgets(char *buf, int size, KFILE *f) {
    int i = 0;
    if (!buf || size <= 0 || !f) return 0;
    while (i < size - 1) {
        int c = kfgetc(f);
        if (c == EOF) break;
        buf[i++] = (char)c;
        if (c == '\n') break;
    }
    if (i == 0) return 0;
    buf[i] = 0;
    return buf;
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
    if (f->mode != 1 && f->mode != 2) return 0;
    unsigned long bytes = size * n;
    if (bytes > RD_DATA_MAX || f->wsize > RD_DATA_MAX - bytes) return 0;
    if (!f->wbuf) {
        f->wbuf = kmalloc(4096);
        f->wcap = 4096;
        f->wsize = 0;
        if (!f->wbuf) return 0;
    }
    while (f->wsize + bytes > f->wcap) {
        if (f->wcap > RD_DATA_MAX / 2) return 0;
        f->wcap *= 2;
        f->wbuf = krealloc(f->wbuf, f->wcap);
        if (!f->wbuf) return 0;
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
    if (!f || !f->rf || f->mode == 0) return 0;
    if (f->wbuf && f->wsize > 0) {
        unsigned base = (f->mode == 2) ? (unsigned)(f->pos - f->wsize) : 0;
        if (!ramdisk_resize(f->rf, base + f->wsize)) return -1;
        ramdisk_write(f->rf, f->wbuf, base, f->wsize);
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

#define PF_X               1
#define ELF_MAX_SEGMENTS   64
#define ELF_NAME_MAX       64

struct exec_range { unsigned long start, end; };

/* Copy a NUL-terminated name out of a string table without reading past
 * the table's bounds; an out-of-range or unterminated name yields an
 * empty string, never a wild pointer into the kernel heap. */
static void elf_name_copy(char *out, unsigned out_cap, const char *tab,
                          Elf64_Xword tab_size, Elf64_Word off) {
    unsigned long i = 0;
    if (out_cap == 0) return;
    if (off < tab_size) {
        while (i < out_cap - 1 && off + i < tab_size) {
            out[i] = tab[off + i];
            if (out[i] == '\0') break;
            i++;
        }
    }
    out[i] = '\0';
}

/* Release a partially built relocatable image and report why it was
 * rejected. Used on every failure path of elf_load. */
static void elf_load_fail(void *base, void **sec_addrs, const char *why) {
    if (why) kprintf("load: %s\n", why);
    if (sec_addrs) kfree(sec_addrs);
    if (base) kfree(base);
}

void *elf_load(void *data, unsigned size) {
    Elf64_Ehdr *ehdr = (Elf64_Ehdr *)data;

    if (size < sizeof(Elf64_Ehdr)) return 0;
    if (ehdr->e_ident[0] != 0x7F || ehdr->e_ident[1] != 'E' ||
        ehdr->e_ident[2] != 'L'  || ehdr->e_ident[3] != 'F')
        return 0;
    if (ehdr->e_type != ET_REL)   return 0;
    if (ehdr->e_machine != EM_X86_64) return 0;

    if (ehdr->e_shentsize < sizeof(Elf64_Shdr)) return 0;
    if (ehdr->e_shoff > size ||
        (Elf64_Xword)ehdr->e_shnum * ehdr->e_shentsize > size - ehdr->e_shoff)
        return 0;
    if (ehdr->e_shstrndx >= ehdr->e_shnum) return 0;

    Elf64_Shdr *shdrs = (Elf64_Shdr *)((char *)data + ehdr->e_shoff);
    Elf64_Half  shnum = ehdr->e_shnum;

    Elf64_Shdr *shstr = &shdrs[ehdr->e_shstrndx];
    if (shstr->sh_offset > size || shstr->sh_size > size - shstr->sh_offset)
        return 0;
    const char *shstrtab = (const char *)data + shstr->sh_offset;
    char        secname[ELF_NAME_MAX];

    /* Find .symtab and .strtab */
    Elf64_Sym  *symtab = 0;
    unsigned    symcount = 0;
    const char *strtab = 0;
    Elf64_Xword strtab_size = 0;

    unsigned total_alloc = 0;
    unsigned i;
    for (i = 0; i < shnum; i++) {
        elf_name_copy(secname, sizeof(secname), shstrtab, shstr->sh_size,
                      shdrs[i].sh_name);
        if (kstrcmp(secname, ".symtab") == 0) {
            if (shdrs[i].sh_offset > size ||
                shdrs[i].sh_size > size - shdrs[i].sh_offset)
                return 0;
            symtab = (Elf64_Sym *)((char *)data + shdrs[i].sh_offset);
            symcount = (unsigned)(shdrs[i].sh_size / sizeof(Elf64_Sym));
        }
        if (kstrcmp(secname, ".strtab") == 0) {
            if (shdrs[i].sh_offset > size ||
                shdrs[i].sh_size > size - shdrs[i].sh_offset)
                return 0;
            strtab = (const char *)data + shdrs[i].sh_offset;
            strtab_size = shdrs[i].sh_size;
        }
        if (shdrs[i].sh_flags & SHF_ALLOC) {
            if (shdrs[i].sh_size >
                (Elf64_Xword)0xFFFFFFFFu - 32 - (Elf64_Xword)total_alloc)
                return 0;
            total_alloc += (unsigned)shdrs[i].sh_size + 32;
        }
    }
    if (!symtab || !strtab) {
        kprintf("load: object has no symbol table\n");
        return 0;
    }

    char *base = kmalloc(total_alloc);
    if (!base) {
        kprintf("load: cannot allocate %u bytes for the image\n", total_alloc);
        return 0;
    }
    kmemset(base, 0, total_alloc);

    void **sec_addrs = kmalloc(shnum * sizeof(void *));
    if (!sec_addrs) { kfree(base); return 0; }
    for (i = 0; i < shnum; i++) sec_addrs[i] = 0;

    unsigned off = 0;
    for (i = 0; i < shnum; i++) {
        if (!(shdrs[i].sh_flags & SHF_ALLOC)) continue;
        sec_addrs[i] = base + off;
        Elf64_Xword ssize = shdrs[i].sh_size;
        if (shdrs[i].sh_type == SHT_PROGBITS && ssize > 0) {
            if (shdrs[i].sh_offset > size ||
                ssize > size - shdrs[i].sh_offset) {
                elf_load_fail(base, sec_addrs, 0);
                return 0;
            }
            kmemcpy(sec_addrs[i], (char *)data + shdrs[i].sh_offset, (unsigned long)ssize);
        }
        off += (unsigned)ssize + 16;
        off = (off + 15) & ~15U;
    }

    /* Apply relocations. Every relocation is bounds checked against the
     * section it patches, and an unresolved symbol or an unsupported
     * relocation type aborts the load: leaving a relocation unapplied would
     * hand the program a wild call target. */
    for (i = 0; i < shnum; i++) {
        if (shdrs[i].sh_type != SHT_RELA) continue;
        if (shdrs[i].sh_offset > size ||
            shdrs[i].sh_size > size - shdrs[i].sh_offset) {
            elf_load_fail(base, sec_addrs, 0);
            return 0;
        }

        unsigned target_sec = shdrs[i].sh_info;
        if (target_sec >= shnum) continue;
        char *target_base = (char *)sec_addrs[target_sec];
        if (!target_base) continue;
        Elf64_Xword target_size = shdrs[target_sec].sh_size;

        unsigned symsec = shdrs[i].sh_link;
        if (symsec >= shnum) { elf_load_fail(base, sec_addrs, "bad symtab link"); return 0; }
        if (shdrs[symsec].sh_offset > size ||
            shdrs[symsec].sh_size > size - shdrs[symsec].sh_offset) {
            elf_load_fail(base, sec_addrs, 0);
            return 0;
        }
        Elf64_Sym *rela_symtab = (Elf64_Sym *)((char *)data + shdrs[symsec].sh_offset);
        unsigned   rela_symcount = (unsigned)(shdrs[symsec].sh_size / sizeof(Elf64_Sym));

        Elf64_Rela *relas = (Elf64_Rela *)((char *)data + shdrs[i].sh_offset);
        unsigned    rcount = (unsigned)(shdrs[i].sh_size / sizeof(Elf64_Rela));
        unsigned j;
        for (j = 0; j < rcount; j++) {
            Elf64_Word   sym_idx = ELF64_R_SYM(relas[j].r_info);
            unsigned     rtype   = ELF64_R_TYPE(relas[j].r_info);
            Elf64_Addr   S = 0;
            unsigned     width;

            if (sym_idx >= rela_symcount) {
                elf_load_fail(base, sec_addrs, "relocation symbol out of range");
                return 0;
            }
            Elf64_Sym *sym = &rela_symtab[sym_idx];

            switch (rtype) {
            case R_X86_64_64:   width = 8; break;
            case R_X86_64_PC32:
            case R_X86_64_PLT32:
            case R_X86_64_32:
            case R_X86_64_32S:  width = 4; break;
            default:
                kprintf("load: unsupported relocation type %u\n", rtype);
                elf_load_fail(base, sec_addrs, 0);
                return 0;
            }
            if (relas[j].r_offset > target_size ||
                width > target_size - relas[j].r_offset) {
                elf_load_fail(base, sec_addrs, "relocation outside section");
                return 0;
            }

            if (sym->st_shndx != SHN_UNDEF && sym->st_shndx < shnum) {
                S = (Elf64_Addr)(unsigned long)sec_addrs[sym->st_shndx] + sym->st_value;
            } else {
                char symname[ELF_NAME_MAX];
                elf_name_copy(symname, sizeof(symname), strtab, strtab_size,
                              sym->st_name);
                void *addr = ksym_resolve(symname);
                if (!addr && symname[0] == '_') addr = ksym_resolve(symname + 1);
                if (!addr) {
                    kprintf("load: undefined symbol '%s'\n", symname);
                    elf_load_fail(base, sec_addrs, 0);
                    return 0;
                }
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
            char symname[ELF_NAME_MAX];
            elf_name_copy(symname, sizeof(symname), strtab, strtab_size,
                          symtab[k].st_name);
            if (kstrcmp(symname, entry_names[ei]) == 0 && symtab[k].st_shndx < shnum && symtab[k].st_shndx != SHN_UNDEF) {
                entry = (char *)sec_addrs[symtab[k].st_shndx] + symtab[k].st_value;
                break;
            }
        }
    }

    if (!entry) { elf_load_fail(base, sec_addrs, "no entry point"); return 0; }
    kfree(sec_addrs);
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
static unsigned long user_mmap_cur; /* anonymous mmap cursor, grows down */

static void apply_exec_relocs(void *data, unsigned size, unsigned long base,
                              const struct exec_range *xr, unsigned nxr) {
    Elf64_Ehdr *e = (Elf64_Ehdr *)data;
    if (size < sizeof(Elf64_Ehdr)) return;
    if (e->e_shentsize < sizeof(Elf64_Shdr)) return;
    if (e->e_shoff > size) return;
    if (e->e_shnum > (size - e->e_shoff) / e->e_shentsize) return;
    Elf64_Shdr *sh = (Elf64_Shdr *)((char *)data + e->e_shoff);
    unsigned i;
    for (i = 0; i < e->e_shnum; i++) {
        if (sh[i].sh_type != SHT_RELA) continue;
        if (sh[i].sh_offset > size || sh[i].sh_size > size - sh[i].sh_offset)
            continue;
        Elf64_Rela *rela = (Elf64_Rela *)((char *)data + sh[i].sh_offset);
        unsigned n = (unsigned)(sh[i].sh_size / sizeof(Elf64_Rela));
        Elf64_Sym  *syms = 0;
        unsigned    syms_count = 0;
        const char *str  = 0;
        Elf64_Xword str_size = 0;
        if (sh[i].sh_link && sh[i].sh_link < e->e_shnum) {
            Elf64_Shdr *ss = &sh[sh[i].sh_link];
            if (ss->sh_offset <= size && ss->sh_size <= size - ss->sh_offset) {
                syms = (Elf64_Sym *)((char *)data + ss->sh_offset);
                syms_count = (unsigned)(ss->sh_size / sizeof(Elf64_Sym));
                if (ss->sh_link && ss->sh_link < e->e_shnum) {
                    Elf64_Shdr *ts = &sh[ss->sh_link];
                    if (ts->sh_offset <= size &&
                        ts->sh_size <= size - ts->sh_offset) {
                        str = (const char *)data + ts->sh_offset;
                        str_size = ts->sh_size;
                    }
                }
            }
        }
        unsigned j;
        for (j = 0; j < n; j++) {
            unsigned    type = ELF64_R_TYPE(rela[j].r_info);
            unsigned    si   = ELF64_R_SYM(rela[j].r_info);
            unsigned long P = base + rela[j].r_offset;
            if (P < USER_LOAD_BASE || P > USER_LOAD_END - 8)
                continue; /* relocation outside the user image */
            unsigned long *PP = (unsigned long *)P;
            unsigned long S  = 0;
            if (syms && si < syms_count) {
                Elf64_Sym *sym = &syms[si];
                if (sym->st_shndx != SHN_UNDEF) S = base + sym->st_value;
                else if (str) {
                    char symname[ELF_NAME_MAX];
                    elf_name_copy(symname, sizeof(symname), str, str_size,
                                  sym->st_name);
                    void *a = ksym_resolve(symname);
                    if (!a && symname[0] == '_')
                        a = ksym_resolve(symname + 1);
                    S = (unsigned long)a;
                }
            }
            switch (type) {
            case R_X86_64_RELATIVE:
                *PP = base + (unsigned long)rela[j].r_addend;
                break;
            case R_X86_64_IRELATIVE: {
                unsigned long fn = base + (unsigned long)rela[j].r_addend;
                unsigned k;
                int in_exec = 0;
                for (k = 0; k < nxr; k++) {
                    if (fn >= xr[k].start && fn < xr[k].end) { in_exec = 1; break; }
                }
                if (!in_exec) continue; /* target outside an executable segment */
                *PP = ((unsigned long (*)(void))fn)();
                break;
            }
            case R_X86_64_64:
                *PP = S + (unsigned long)rela[j].r_addend;
                break;
            case R_X86_64_GLOB_DAT:
            case R_X86_64_JUMP_SLOT:
                *PP = S;
                break;
            }
        }
    }
}

void *load_exec_elf(void *data, unsigned size) {
    Elf64_Ehdr *e = (Elf64_Ehdr *)data;
    if (size < sizeof(Elf64_Ehdr)) return 0;
    if (e->e_ident[0] != 0x7F || e->e_ident[1] != 'E' ||
        e->e_ident[2] != 'L'  || e->e_ident[3] != 'F') return 0;
    if (e->e_machine != EM_X86_64) return 0;
    if (e->e_type != ET_EXEC && e->e_type != ET_DYN) return 0;

    if (e->e_phentsize < sizeof(Elf64_Phdr)) return 0;
    if (e->e_phoff > size) return 0;
    if (e->e_phnum > (size - e->e_phoff) / e->e_phentsize) return 0;
    if (e->e_phnum > ELF_MAX_SEGMENTS) return 0;

    unsigned long base = (e->e_type == ET_DYN) ? USER_LOAD_BASE : 0;

    Elf64_Phdr *ph = (Elf64_Phdr *)((char *)data + e->e_phoff);
    struct exec_range xr[ELF_MAX_SEGMENTS];
    unsigned nxr = 0;
    unsigned long max_end = 0;
    unsigned i;
    for (i = 0; i < e->e_phnum; i++) {
        if (ph[i].p_type != PT_LOAD) continue;
        if (ph[i].p_vaddr > USER_LOAD_END - base) return 0;
        unsigned long dst = base + ph[i].p_vaddr;
        if (dst < USER_LOAD_BASE || dst >= USER_LOAD_END)
            return 0; /* segment outside the user region */
        if (ph[i].p_memsz > USER_LOAD_END - dst) return 0;
        if (ph[i].p_filesz > USER_LOAD_END - dst) return 0;
        if (ph[i].p_offset > size || ph[i].p_filesz > size - ph[i].p_offset)
            return 0; /* segment data beyond the end of the file */
        if (ph[i].p_filesz > 0 && (ph[i].p_flags & PF_X) && nxr < ELF_MAX_SEGMENTS) {
            xr[nxr].start = dst;
            xr[nxr].end   = dst + ph[i].p_filesz;
            nxr++;
        }
        kmemcpy((void *)dst, (char *)data + ph[i].p_offset,
                (unsigned long)ph[i].p_filesz);
        if (ph[i].p_memsz > ph[i].p_filesz)
            kmemset((void *)(dst + ph[i].p_filesz), 0,
                    (unsigned long)(ph[i].p_memsz - ph[i].p_filesz));
        if (dst + ph[i].p_memsz > max_end) max_end = dst + ph[i].p_memsz;
    }
    if (max_end == 0) return 0;

    apply_exec_relocs(data, size, base, xr, nxr);

    g_brk       = ALIGN_UP(max_end, 0x1000);
    g_brk_limit = USER_BRK_END;
    user_mmap_cur = USER_BRK_END;
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
extern unsigned long syscall_kstack;

void syscall_init(void) {
    /* SYSCALL loads CS=0x08, SS=0x10 from STAR[47:32]. SYSRET derives its
     * selectors from STAR[63:48]: CS = n + 16 = 0x20 (user code), SS =
     * n + 8 = 0x18 (user data), the Linux layout. */
    wrmsr(MSR_STAR,  ((unsigned long)GDT64_DATA_SEL << 48) | ((unsigned long)GDT64_CODE_SEL << 32));
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

#define SYSCALL_TRACE 0

static long ksyscall_dispatch(long n, long a1, long a2, long a3, long a4, long a5, long a6);

long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6);
long syscall_trace_enabled(void);
void syscall_trace_set(int on);

static int s_trace_enabled = SYSCALL_TRACE;

long syscall_trace_enabled(void) { return s_trace_enabled; }
void syscall_trace_set(int on) { s_trace_enabled = on ? 1 : 0; }

long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6) {
    long ret;
    if (s_trace_enabled)
        kprintf("syscall %d(%d, %d, %d, %d, %d, %d)",
                (int)n, (int)a1, (int)a2, (int)a3, (int)a4, (int)a5, (int)a6);
    ret = ksyscall_dispatch(n, a1, a2, a3, a4, a5, a6);
    if (s_trace_enabled) kprintf(" = %d\n", (int)ret);
    return ret;
}

static long ksyscall_dispatch(long n, long a1, long a2, long a3, long a4, long a5, long a6);

/* ---- User-pointer validation ---------------------------------------------
 * The syscall boundary is the hardened edge between ring 3 and ring 0.
 * Every pointer a Linux ABI program hands the kernel must lie inside the
 * user window [USER_LOAD_BASE, USER_LOAD_END), because that is the only
 * memory the page tables marked user-accessible. Anything else — kernel
 * heap, kernel image, page tables, MMIO — must be rejected before a single
 * dereference. All arithmetic is overflow checked. */

static int user_range_ok(unsigned long p, unsigned long len) {
    if (p < USER_LOAD_BASE) return 0;
    if (len > USER_LOAD_END - p) return 0;
    return p + len <= USER_LOAD_END;
}

static int user_str_ok(unsigned long p, unsigned long maxlen) {
    unsigned long i;
    if (p < USER_LOAD_BASE || p >= USER_LOAD_END) return 0;
    for (i = 0; i < maxlen && p + i < USER_LOAD_END; i++)
        if (((unsigned char *)p)[i] == 0) return 1;
    return 0;
}

static long ksyscall_dispatch(long n, long a1, long a2, long a3, long a4, long a5, long a6) {
    switch (n) {
    case 0: { /* read */
        char *buf = (char *)a2; long cnt = a3, i = 0;
        if (cnt > 0 && !user_range_ok((unsigned long)buf, (unsigned long)cnt)) return EFAULT;
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
        if (cnt > 0 && !user_range_ok((unsigned long)buf, (unsigned long)cnt)) return EFAULT;
        if (a1 == 1 || a1 == 2) { for (i = 0; i < cnt; i++) vga_putc(buf[i]); return cnt; }
        if (a1 >= 3 && a1 < KFD_MAX && kfd_table[a1])
            return (long)kfwrite(buf, 1, (unsigned long)cnt, kfd_table[a1]);
        return -9;
    }
    case 20: { /* writev */
        struct kiovec *iov = (struct kiovec *)a2; long cnt = a3, total = 0, k;
        if (cnt < 0 || (unsigned long)cnt > (USER_LOAD_END - USER_LOAD_BASE) / sizeof(struct kiovec))
            return -22;
        if (cnt > 0 && !user_range_ok((unsigned long)iov, (unsigned long)cnt * sizeof(struct kiovec)))
            return EFAULT;
        for (k = 0; k < cnt; k++) {
            unsigned long j;
            if (iov[k].iov_len > 0 &&
                !user_range_ok((unsigned long)iov[k].iov_base, iov[k].iov_len))
                return EFAULT;
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
        if (!user_str_ok((unsigned long)path, RAMDISK_FNAME_LEN)) return EFAULT;
        for (fd = 3; fd < KFD_MAX; fd++) if (!kfd_table[fd]) break;
        if (fd >= KFD_MAX) return -24;
        KFILE *f = kfopen(path, mode);
        if (!f) return -2;
        kfd_table[fd] = f;
        return fd;
    }
    case 3: /* close */
        if (a1 >= NET_FD_BASE) return net_sys_close(a1);
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
    case 9: { /* mmap (anonymous only), carved from the top of the user window */
        unsigned long len = (unsigned long)a2;
        unsigned long n = ALIGN_UP(len ? len : 1, 0x1000);
        if (n > user_mmap_cur - USER_LOAD_BASE) return -12;
        user_mmap_cur -= n;
        return (long)user_mmap_cur;
    }
    case 11: return 0; /* munmap */
    case 158: /* arch_prctl: accept only canonical bases */
        if (a1 == 0x1002 || a1 == 0x1001) {
            unsigned long v = (unsigned long)a2;
            unsigned long sign = (v >> 47) & 1;
            if (((v >> 48) & 0xFFFF) != (sign ? 0xFFFF : 0)) return -22;
            wrmsr(a1 == 0x1002 ? MSR_FSBASE : MSR_GSBASE, v);
            return 0;
        }
        return -22;
    case 218: return 1;  /* set_tid_address */
    case 228: /* clock_gettime */
        if (a2) {
            unsigned long *ts = (unsigned long *)a2;
            if (!user_range_ok((unsigned long)ts, 2 * sizeof(unsigned long))) return EFAULT;
            ts[0] = 0; ts[1] = 0;
        }
        return 0;
    case 16: return 0;   /* ioctl */
    case 39: return 1;   /* getpid */
    case 60: case 231:   /* exit / exit_group */
        exec_exit_code = (int)a1;
        klongjmp(&exec_return, 1);
        return 0; /* unreachable */
    case 41:             /* socket */
        return net_sys_socket(a1, a2, a3);
    case 42:             /* connect */
        if (!user_range_ok((unsigned long)a2, 16)) return EFAULT;
        return net_sys_connect(a1, a2, a3);
    case 44:             /* sendto */
        if (a3 > 0 && !user_range_ok((unsigned long)a2, (unsigned long)a3)) return EFAULT;
        return net_sys_sendto(a1, a2, a3, a4, a5, a6);
    case 45:             /* recvfrom */
        if (a3 > 0 && !user_range_ok((unsigned long)a2, (unsigned long)a3)) return EFAULT;
        return net_sys_recvfrom(a1, a2, a3, a4, a5, a6);
    case 48:             /* shutdown */
        return net_sys_shutdown(a1, a2);
    case 7:              /* poll */
        if (a2 < 0 || (unsigned long)a2 > (USER_LOAD_END - USER_LOAD_BASE) / 8) return -22;
        if (a2 > 0 && !user_range_ok((unsigned long)a1, (unsigned long)a2 * 8)) return EFAULT;
        return net_sys_poll(a1, a2, a3);
    case 200:            /* MiniOS: hostname resolution */
        if (!user_str_ok((unsigned long)a1, 255)) return EFAULT;
        return net_sys_dns(a1);
    case 201:            /* MiniOS: TLS handshake on a connected TCP fd */
        if (!user_str_ok((unsigned long)a2, 255)) return EFAULT;
        return tls_sys_handshake(a1, a2);
    case 202:            /* MiniOS: send one TLS record (all-or-error) */
        if (a3 > 0 && !user_range_ok((unsigned long)a2, (unsigned long)a3)) return EFAULT;
        return tls_sys_send(a1, a2, a3);
    case 203:            /* MiniOS: receive decrypted TLS application data */
        if (a3 > 0 && !user_range_ok((unsigned long)a2, (unsigned long)a3)) return EFAULT;
        return tls_sys_recv(a1, a2, a3);
    default:
        return -38; /* ENOSYS */
    }
}


/* ---- syscall trampoline: marshal Linux ABI regs into the C ABI ----------
 * The kernel stack is a fixed region (SYS_KSTK_TOP) exchanged on entry, so
 * the kernel never runs on a user stack and never touches the user red
 * zone. `syscall_kstack` holds the kernel stack top while a program runs
 * and the incoming rsp during a syscall. The return discriminates on the
 * restored rsp: a syscall that came from ring 3 ran on the user stack in
 * the user window and returns with sysretq (ring 3); a ring-0 ET_REL
 * syscall ran on a kernel stack and returns with `jmp *%rcx`, the old
 * contract, because sysretq always lands on ring 3. */

__asm__(
    ".text\n"
    ".global syscall_kstack\n"
    ".data\n"
    ".align 8\n"
    "syscall_kstack:\n"
    "  .quad 0\n"
    ".text\n"
    ".global syscall_entry\n"
    "syscall_entry:\n"
    "  xchgq %rsp, syscall_kstack(%rip)\n"
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
    "  xchgq %rsp, syscall_kstack(%rip)\n"
    "  cmpq $" STR(USER_WIN_LO) ", %rsp\n"
    "  jb 1f\n"
    "  cmpq $" STR(USER_WIN_HI) ", %rsp\n"
    "  jae 1f\n"
    "  sysretq\n"
    "1:\n"
    "  jmp *%rcx\n"
);


/* ---- Build the SysV initial stack and jump to the ELF entry ------------- */

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
    char *stk = (char *)USER_STACK_BASE;   /* fixed region, no heap churn */
    unsigned long *sp = setup_user_stack(stk, USER_STACK_SIZE, argc, argv);
    unsigned long frame[5];
    exec_exit_code = 0;
    syscall_kstack = SYS_KSTK_TOP;
    wrmsr(MSR_FSBASE, 0);
    wrmsr(MSR_GSBASE, 0);

    /* Ring-3 entry frame, popped by iretq: RIP, CS, RFLAGS, RSP, SS. */
    frame[0] = (unsigned long)entry;
    frame[1] = (unsigned long)(GDT64_USER_CODE_SEL | 3);
    frame[2] = 0x002;                       /* IF=0: no IDT, no interrupts */
    frame[3] = (unsigned long)sp;
    frame[4] = (unsigned long)(GDT64_USER_DATA_SEL | 3);

    if (ksetjmp(&exec_return) == 0) {
        __asm__ volatile(
            "mov %[udata], %%ax\n"
            "mov %%ax, %%ds\n"
            "mov %%ax, %%es\n"
            "mov %%ax, %%fs\n"
            "mov %%ax, %%gs\n"
            "mov %[frame], %%rsp\n"
            "xorl %%ebp, %%ebp\n"
            "iretq\n"
            :: [frame] "r"(frame), [udata] "i"(GDT64_USER_DATA_SEL | 3)
            : "rax", "memory");
        __builtin_unreachable();
    }

    /* exit() went through the SYSCALL path, which already reloaded CS/SS to
     * the kernel selectors; restore the data segments and syscall stack. */
    __asm__ volatile(
        "mov %[kdata], %%ax\n"
        "mov %%ax, %%ds\n"
        "mov %%ax, %%es\n"
        "mov %%ax, %%fs\n"
        "mov %%ax, %%gs\n"
        "mov %%ax, %%ss\n"
        :: [kdata] "i"(GDT64_DATA_SEL)
        : "ax", "memory");
    wrmsr(MSR_FSBASE, 0);
    wrmsr(MSR_GSBASE, 0);
    syscall_kstack = SYS_KSTK_TOP;
    return exec_exit_code;
}

/* Run an ET_REL program as a plain function call, but catch a libc exit(). */
int k_run_rel(prog_entry_t entry, int argc, char **argv) {
    exec_exit_code = 0;
    syscall_kstack = SYS_KSTK_TOP;
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

#define SHELL_BIN_PATH     "bin/"
#define SHELL_BIN_PATH_LEN 4
#define SHELL_BIN_MAX_CMD  (RAMDISK_FNAME_LEN - SHELL_BIN_PATH_LEN - 2)

static char cmd_buf[CMD_BUF_SZ];

#define SHELL_HIST_MAX 16
static char shell_hist[SHELL_HIST_MAX][CMD_BUF_SZ];
static int  shell_hist_count;
static int  shell_hist_idx = -1;
static char shell_line_saved[CMD_BUF_SZ];
static int  shell_line_saved_pos;

static void shell_prompt(void) { vga_puts("\nminiOS> "); }

static void shell_exec_builtin(int argc, char **argv);

static int console_pushback = -1;

/* Blocking read from either the PS/2 keyboard or COM1 serial line. */
static int console_getc(void) {
    if (console_pushback >= 0) {
        int c = console_pushback;
        console_pushback = -1;
        return c;
    }
    while (1) {
        if (!kbd_q_empty()) return kbd_q_pop();
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

/* Next buffered byte without consuming it, or -1 when nothing is
 * available right now. Used to tell an ESC prefix from a complete
 * escape sequence, which always arrives in one burst. */
static int console_peek(void) {
    if (console_pushback >= 0) return console_pushback;
    if (!kbd_q_empty()) return kbd_q_peek();
    if (serial_available()) {
        console_pushback = serial_getc();
        return console_pushback;
    }
    if (kbd_available()) {
        console_pushback = kbd_read();
        return console_pushback;
    }
    return -1;
}

/* Read one line into buf (at most size-1 chars). Echoes input and
 * honours backspace. Shared by the shell prompt and the editor. */
static void shell_readline_buf(char *buf, int size) {
    int pos = 0;
    kmemset(buf, 0, (unsigned long)size);
    while (1) {
        int c = console_getc();
        if (c < 0) continue;
        if (c == '\n' || c == '\r') {
            vga_putc('\n');
            buf[pos] = 0;
            return;
        }
        if (c == '\b' || c == 0x7F) {
            if (pos > 0) {
                pos--;
                vga_putc('\b');
            }
            continue;
        }
        if (pos < size - 1 && c >= 32 && c < 127) {
            buf[pos++] = (char)c;
            vga_putc((char)c);
        }
    }
}

static void shell_readline_hist(char *buf, int size);

static void shell_readline(void) {
    shell_readline_hist(cmd_buf, CMD_BUF_SZ);
}

/* Redraw the edit line with the recalled text: erase what is shown,
 * then write the replacement into buf and onto the console. */
static void shell_hist_show(char *buf, int size, int *pos, const char *text) {
    int i;
    for (i = 0; i < *pos; i++) vga_putc(' ');
    for (i = 0; i < *pos; i++) vga_putc('\b');
    kmemset(buf, 0, (unsigned long)size);
    int n = 0;
    while (text[n] && n < size - 1) {
        buf[n] = text[n];
        vga_putc(text[n]);
        n++;
    }
    *pos = n;
}

/* Move through the history ring: up recalls older entries, down moves
 * forward again and finally restores the live line. */
static void shell_hist_nav(char *buf, int size, int *pos, int up) {
    if (shell_hist_count == 0) return;
    if (up) {
        if (shell_hist_idx < 0) {
            kmemcpy(shell_line_saved, buf, (unsigned long)size);
            shell_line_saved_pos = *pos;
            shell_hist_idx = shell_hist_count - 1;
        } else if (shell_hist_idx > 0) {
            shell_hist_idx--;
        } else {
            return;
        }
        shell_hist_show(buf, size, pos, shell_hist[shell_hist_idx]);
    } else {
        if (shell_hist_idx < 0) return;
        if (shell_hist_idx >= shell_hist_count - 1) {
            shell_hist_idx = -1;
            shell_hist_show(buf, size, pos, shell_line_saved);
            *pos = shell_line_saved_pos;
            return;
        }
        shell_hist_idx++;
        shell_hist_show(buf, size, pos, shell_hist[shell_hist_idx]);
    }
}

/* Shell prompt readline: like shell_readline_buf plus command history.
 * Up arrow (ESC [ A) recalls the previous command, down arrow moves
 * forward. Any editing key while scrolling returns to the live line. */
static void shell_readline_hist(char *buf, int size) {
    int pos = 0;
    kmemset(buf, 0, (unsigned long)size);
    while (1) {
        int c = console_getc();
        if (c < 0) continue;
        if (c == '\n' || c == '\r') {
            vga_putc('\n');
            buf[pos] = 0;
            shell_hist_idx = -1;
            if (buf[0] && (shell_hist_count == 0 ||
                kstrcmp(shell_hist[shell_hist_count - 1], buf) != 0)) {
                if (shell_hist_count == SHELL_HIST_MAX) {
                    for (int i = 1; i < SHELL_HIST_MAX; i++)
                        kmemcpy(shell_hist[i - 1], shell_hist[i],
                                (unsigned long)CMD_BUF_SZ);
                    shell_hist_count--;
                }
                kmemcpy(shell_hist[shell_hist_count], buf,
                        (unsigned long)CMD_BUF_SZ);
                shell_hist_count++;
            }
            return;
        }
        if (c == KEY_ESC) {
            if (console_peek() == KEY_CSI) {
                console_getc();
                int b = console_peek();
                if (b == KEY_ARR_UP || b == KEY_ARR_DOWN) {
                    console_getc();
                    shell_hist_nav(buf, size, &pos, b == KEY_ARR_UP);
                }
            }
            continue;
        }
        if (c == '\b' || c == 0x7F || (c >= 32 && c < 127)) {
            if (shell_hist_idx >= 0) shell_hist_idx = -1;
        }
        if (c == '\b' || c == 0x7F) {
            if (pos > 0) {
                pos--;
                vga_putc('\b');
            }
            continue;
        }
        if (pos < size - 1 && c >= 32 && c < 127) {
            buf[pos++] = (char)c;
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

/* Shell status text must never land inside a redirected command's output:
 * `cmd > file` captures what the command wrote, not what the shell reported
 * about it. These helpers lift a print out of the active capture. */
static int redirect_suspend(void) {
    int was = redir_active;
    redir_active = 0;
    return was;
}

static void redirect_resume(int was) {
    redir_active = was;
}

static void shell_report_exit(int code) {
    int was = redirect_suspend();
    kprintf("exit code: %d\n", code);
    redirect_resume(was);
}

static void shell_report(const char *what, const char *detail) {
    int was = redirect_suspend();
    vga_puts(what);
    if (detail) vga_puts(detail);
    vga_putc('\n');
    redirect_resume(was);
}

/* Start capturing console output for a `> file` redirection. */
static int redirect_begin(void) {
    redir_len      = 0;
    redir_overflow = 0;
    if (!redir_buf && !redir_grow()) return 0;
    redir_active = 1;
    return 1;
}

/* Stop capturing and store the captured bytes in `path`. Returns 0 on
 * success. The capture is released on every path so that a failure cannot
 * leave the console silently detached from the screen. */
static int redirect_commit(const char *path, int append_mode) {
    KFILE *f;
    unsigned long written;
    int rc;

    redir_active = 0;
    if (redir_overflow) { redir_len = 0; return -1; }

    f = kfopen(path, append_mode ? "a" : "w");
    if (!f) { redir_len = 0; return -1; }
    written = redir_len ? kfwrite(redir_buf, 1, redir_len, f) : 0;
    rc = kfclose(f);
    if (redir_len && written != redir_len) rc = -1;
    redir_len = 0;
    return rc;
}

/* Split a `> file` / `>> file` redirection off the end of a parsed command
 * line. Returns 1 when a redirection was found, 0 when there was none and
 * -1 when the syntax is incomplete. On success argc is trimmed to the
 * command and append_mode is set for `>>`. */
static int shell_take_redirect(int *argc, char **argv, char **path, int *append_mode) {
    int i;
    *path = 0;
    *append_mode = 0;
    for (i = 0; i < *argc; i++) {
        if (argv[i][0] != '>') continue;
        if (argv[i][1] == '>') {
            *append_mode = 1;
            if (argv[i][2]) *path = argv[i] + 2;
        } else if (argv[i][1]) {
            *path = argv[i] + 1;
        }
        if (!*path) {
            if (i + 1 >= *argc) return -1;
            *path = argv[i + 1];
        }
        *argc  = i;
        argv[i] = 0;
        return 1;
    }
    return 0;
}

void shell_run(void) {
    while (1) {
        shell_prompt();
        shell_readline();

        if (cmd_buf[0] == 0) continue;

        char *argv[MAX_ARGS + 1];
        int argc = shell_parse(cmd_buf, argv, MAX_ARGS);

        if (argc == 0) continue;

        char *redir_path = 0;
        int redir_append = 0;
        int redirected = shell_take_redirect(&argc, argv, &redir_path, &redir_append);
        if (redirected < 0) {
            vga_puts("syntax: > needs a target file\n");
            continue;
        }
        if (argc == 0) {
            vga_puts("syntax: > needs a command\n");
            continue;
        }
        if (redirected && !redirect_begin()) {
            vga_puts("redirect: out of memory\n");
            continue;
        }

        shell_exec_builtin(argc, argv);

        if (redirected && redirect_commit(redir_path, redir_append) != 0)
            kprintf("redirect: cannot write %s\n", redir_path);
    }
}

/* Load an ELF file from the ramdisk and register it under its filename stem.
 * Returns 1 for an ET_REL program, 2 for an ET_EXEC/ET_DYN Linux process,
 * 0 on failure.  progname_out must hold at least 32 bytes. */
static int shell_load(const char *fname, char *progname_out, void **entry_out) {
    char resolved[RAMDISK_FNAME_LEN];
    if (!fs_resolve(fname, resolved, sizeof(resolved)) || fs_is_dir(resolved))
        return 0;
    RDFile *f = ramdisk_open(resolved);
    if (!f) return 0;
    unsigned char *data = kmalloc(f->size);
    if (!data) return 0;
    ramdisk_read(f, data, 0, f->size);

    const char *base = resolved;
    const char *slash = kstrchr(base, '/');
    while (slash) { base = slash + 1; slash = kstrchr(base, '/'); }
    const char *dot = kstrchr(base, '.');
    int nl = dot ? (int)(dot - base) : (int)kstrlen(base);
    if (nl > 30) nl = 30;
    kmemcpy(progname_out, base, nl);
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

/* ================================================================
 *  Line editor (edit command)
 * ================================================================ */

#define EDIT_MAX_LINES 512
#define EDIT_LINE_MAX  128
#define EDIT_FILE_MAX  (64UL * 1024)

typedef struct {
    char text[EDIT_LINE_MAX];
    int  used;
} EditLine;

typedef struct {
    EditLine *lines;
    int       count;
    char      fname[RAMDISK_FNAME_LEN];
    int       dirty;
    int       truncated;
} EditBuf;

static EditBuf *edit_alloc(const char *fname) {
    EditBuf *e = kmalloc(sizeof(EditBuf));
    if (!e) return 0;
    e->lines = kcalloc(EDIT_MAX_LINES, sizeof(EditLine));
    if (!e->lines) {
        kfree(e);
        return 0;
    }
    e->count     = 0;
    e->dirty     = 0;
    e->truncated = 0;
    kstrncpy(e->fname, fname, RAMDISK_FNAME_LEN - 1);
    e->fname[RAMDISK_FNAME_LEN - 1] = 0;
    return e;
}

static void edit_free(EditBuf *e) {
    if (!e) return;
    if (e->lines) kfree(e->lines);
    kfree(e);
}

static int edit_load(EditBuf *e) {
    KFILE *f = kfopen(e->fname, "r");
    if (!f) return 0;
    if (f->rf->size > EDIT_FILE_MAX) {
        kfclose(f);
        return -1;
    }
    int idx = 0;
    int used = 0;
    while (1) {
        int c = kfgetc(f);
        if (c == EOF) break;
        if (idx >= EDIT_MAX_LINES) { e->truncated = 1; break; }
        if (c == '\n') {
            e->lines[idx].used = used;
            idx++;
            used = 0;
            continue;
        }
        if (c == '\r') continue;
        if (used < EDIT_LINE_MAX - 1) {
            e->lines[idx].text[used++] = (char)c;
        } else {
            e->truncated = 1;
        }
    }
    if (used > 0 && idx < EDIT_MAX_LINES) {
        e->lines[idx].used = used;
        idx++;
    }
    e->count = idx;
    kfclose(f);
    return 1;
}

static int edit_save(EditBuf *e) {
    KFILE *f = kfopen(e->fname, "w");
    if (!f) return -1;
    int i;
    for (i = 0; i < e->count; i++) {
        if (e->lines[i].used > 0)
            kfwrite(e->lines[i].text, 1, (unsigned long)e->lines[i].used, f);
        if (i + 1 < e->count) kfputc('\n', f);
    }
    if (kfclose(f) != 0) return -1;
    e->dirty = 0;
    return 0;
}

static void edit_print(EditBuf *e, int idx) {
    if (idx < 0 || idx >= e->count) return;
    kprintf("%4d: ", idx + 1);
    int i;
    for (i = 0; i < e->lines[idx].used; i++) vga_putc(e->lines[idx].text[i]);
    vga_putc('\n');
}

static void edit_list(EditBuf *e) {
    int i;
    if (e->count == 0) {
        vga_puts("(empty)\n");
        return;
    }
    for (i = 0; i < e->count; i++) edit_print(e, i);
}

static int edit_set_line(EditBuf *e, int idx, const char *text) {
    unsigned long n = kstrlen(text);
    if (n > EDIT_LINE_MAX - 1) n = EDIT_LINE_MAX - 1;
    kmemcpy(e->lines[idx].text, text, n);
    e->lines[idx].used = (int)n;
    e->dirty = 1;
    return 0;
}

static int edit_insert(EditBuf *e, int idx, const char *text) {
    if (e->count >= EDIT_MAX_LINES) return -1;
    if (idx < 0) idx = 0;
    if (idx > e->count) idx = e->count;
    kmemmove(&e->lines[idx + 1], &e->lines[idx],
             (unsigned long)(e->count - idx) * sizeof(EditLine));
    e->count++;
    return edit_set_line(e, idx, text);
}

static int edit_delete(EditBuf *e, int idx) {
    if (idx < 0 || idx >= e->count) return -1;
    kmemmove(&e->lines[idx], &e->lines[idx + 1],
             (unsigned long)(e->count - idx - 1) * sizeof(EditLine));
    e->count--;
    e->dirty = 1;
    return 0;
}

static void edit_usage(void) {
    vga_puts("editor: h help, l list, p N print, e N edit, a append,\n");
    vga_puts("        i N insert, d N delete, w save, x save+quit,\n");
    vga_puts("        q quit, q! quit discarding changes\n");
}

/* A buffer that did not hold the whole file must never be written back:
 * saving it would drop the part that was never loaded. */
static int edit_refuse_save(EditBuf *e) {
    if (!e->truncated) return 0;
    vga_puts("refusing to save: file did not fit in the buffer\n");
    return 1;
}

static void edit_loop(EditBuf *e) {
    char buf[CMD_BUF_SZ];
    vga_puts("edit: 'h' for help\n");
    while (1) {
        vga_puts("edit> ");
        shell_readline_buf(buf, CMD_BUF_SZ);
        char *argv[MAX_ARGS + 1];
        int argc = shell_parse(buf, argv, MAX_ARGS);
        if (argc == 0) continue;

        if (kstrcmp(argv[0], "h") == 0) {
            edit_usage();
        } else if (kstrcmp(argv[0], "l") == 0) {
            edit_list(e);
        } else if (kstrcmp(argv[0], "p") == 0) {
            if (argc < 2) { vga_puts("usage: p <line>\n"); continue; }
            int n = (int)katol(argv[1]);
            if (n < 1 || n > e->count) { vga_puts("no such line\n"); continue; }
            edit_print(e, n - 1);
        } else if (kstrcmp(argv[0], "e") == 0) {
            if (argc < 2) { vga_puts("usage: e <line>\n"); continue; }
            int n = (int)katol(argv[1]);
            if (n < 1 || n > e->count) { vga_puts("no such line\n"); continue; }
            char line[EDIT_LINE_MAX];
            shell_readline_buf(line, EDIT_LINE_MAX);
            edit_set_line(e, n - 1, line);
        } else if (kstrcmp(argv[0], "a") == 0) {
            char line[EDIT_LINE_MAX];
            shell_readline_buf(line, EDIT_LINE_MAX);
            if (edit_insert(e, e->count, line) != 0) vga_puts("buffer full\n");
        } else if (kstrcmp(argv[0], "i") == 0) {
            int n = argc >= 2 ? (int)katol(argv[1]) : e->count + 1;
            if (n < 1 || n > e->count + 1) { vga_puts("no such line\n"); continue; }
            char line[EDIT_LINE_MAX];
            shell_readline_buf(line, EDIT_LINE_MAX);
            if (edit_insert(e, n - 1, line) != 0) vga_puts("buffer full\n");
        } else if (kstrcmp(argv[0], "d") == 0) {
            if (argc < 2) { vga_puts("usage: d <line>\n"); continue; }
            int n = (int)katol(argv[1]);
            if (edit_delete(e, n - 1) != 0) vga_puts("no such line\n");
        } else if (kstrcmp(argv[0], "w") == 0) {
            if (edit_refuse_save(e)) continue;
            if (edit_save(e) != 0) vga_puts("save failed\n");
            else kprintf("wrote %d line(s) to %s\n", e->count, e->fname);
        } else if (kstrcmp(argv[0], "x") == 0) {
            if (edit_refuse_save(e)) continue;
            if (edit_save(e) != 0) { vga_puts("save failed\n"); continue; }
            kprintf("wrote %d line(s) to %s\n", e->count, e->fname);
            return;
        } else if (kstrcmp(argv[0], "q") == 0) {
            if (e->dirty) {
                vga_puts("unsaved changes: 'w' to save, 'q!' to discard\n");
                continue;
            }
            return;
        } else if (kstrcmp(argv[0], "q!") == 0) {
            return;
        } else {
            vga_puts("unknown command\n");
            edit_usage();
        }
    }
}

static void shell_cmd_edit(int argc, char **argv) {
    if (argc < 2) {
        vga_puts("usage: edit <file>\n");
        return;
    }
    char resolved[RAMDISK_FNAME_LEN];
    if (!fs_resolve(argv[1], resolved, sizeof(resolved))) {
        kprintf("edit: %s: cannot open\n", argv[1]);
        return;
    }
    if (fs_is_dir(resolved)) {
        kprintf("edit: %s: is a directory\n", argv[1]);
        return;
    }
    EditBuf *e = edit_alloc(argv[1]);
    if (!e) {
        vga_puts("edit: out of memory\n");
        return;
    }
    int rc = edit_load(e);
    if (rc < 0) {
        vga_puts("edit: file too large\n");
        edit_free(e);
        return;
    }
    if (rc == 0) {
        kprintf("edit: new file %s\n", argv[1]);
    }
    edit_loop(e);
    edit_free(e);
}

static inline void outw_port(unsigned short port, unsigned short val) {
    __asm__ volatile("outw %0, %1" : : "a"(val), "Nd"(port));
}

#define QEMU_PM_PORT 0x604

static void shell_cmd_poweroff(void) {
    vga_puts("powering off\n");
    outw_port(QEMU_PM_PORT, 0x2000);
    while (1) __asm__ volatile("hlt");
}

/* Resolve a command through the bin path: load /bin/<cmd> (root-anchored,
 * like Linux /bin, so the cwd never changes where commands are found) from
 * the ramdisk as a Linux ELF and run it with the original argv. Returns
 * the exit code or -1 when the name is not eligible or no ELF exists. */
static int shell_run_from_path(const char *cmd, int argc, char **argv) {
    if (kstrchr(cmd, '/')) return -1;
    int clen = (int)kstrlen(cmd);
    if (clen == 0 || clen > SHELL_BIN_MAX_CMD) return -1;
    char binname[RAMDISK_FNAME_LEN + 1];
    kmemset(binname, 0, sizeof(binname));
    binname[0] = '/';
    kmemcpy(binname + 1, SHELL_BIN_PATH, SHELL_BIN_PATH_LEN);
    kmemcpy(binname + 1 + SHELL_BIN_PATH_LEN, cmd, (unsigned long)clen);
    char progname[RAMDISK_FNAME_LEN];
    void *entry = 0;
    if (!shell_load(binname, progname, &entry)) return -1;
    return k_spawn(progname, argc, argv);
}

static void shell_exec_builtin(int argc, char **argv) {
    if (kstrcmp(argv[0], "help") == 0) {
        vga_puts("Commands: help clear ls cat echo edit rm mkdir cd pwd ps load run poweroff\n");
        vga_puts("  ls [dir]           list files (under the cwd by default)\n");
        vga_puts("  cd [dir] / pwd     change / print the working directory\n");
        vga_puts("  mkdir <name>       create a directory entry\n");
        vga_puts("  rm <file>          delete a ramdisk file\n");
        vga_puts("  ps                 list registered programs\n");
        vga_puts("  net                network status (rtl8139, slirp)\n");
        vga_puts("  net ping <ip>      one ICMP echo\n");
        vga_puts("  trace [on|off]     report Linux syscalls\n");
        vga_puts("  edit <file>        line editor for ramdisk files\n");
        vga_puts("  run  <name|file>   run a loaded program, ELF or .cvm module\n");
        vga_puts("  load <file>        load an ELF (.o relocatable or Linux exe)\n");
        vga_puts("  <cmd> > <file>     redirect command output to a file\n");
        vga_puts("  <cmd> [args...]    run an ELF from bin/<cmd> (command path)\n");
        vga_puts("Toolchain: edit p.c; run minigcc.o p.c > p.s;\n");
        vga_puts("           run ld.o -f elf -o p.elf p.s; run p.elf\n");
        vga_puts("CVM:       run minigcc.o w1.c > w1.s; run ld.o -f cvm -o w1.cvm w1.s; run w1.cvm\n");
    }
    else if (kstrcmp(argv[0], "clear") == 0) {
        vga_clear();
    }
    else if (kstrcmp(argv[0], "poweroff") == 0) {
        shell_cmd_poweroff();
    }
    else if (kstrcmp(argv[0], "edit") == 0) {
        shell_cmd_edit(argc, argv);
    }
    else if (kstrcmp(argv[0], "ls") == 0) {
        char dir[RAMDISK_FNAME_LEN];
        if (argc > 1) {
            if (!fs_resolve(argv[1], dir, sizeof(dir))) {
                shell_report("ls: name too long: ", argv[1]);
                return;
            }
            unsigned dl = (unsigned)kstrlen(dir);
            if (dl && dir[dl - 1] != '/') {
                if (dl + 1 >= sizeof(dir)) return;
                dir[dl] = '/';
                dir[dl + 1] = 0;
            }
            if (!fs_dir_exists(dir)) {
                shell_report("ls: no such directory: ", dir);
                return;
            }
        } else {
            kmemcpy(dir, fs_cwd, sizeof(fs_cwd));
        }
        unsigned plen = (unsigned)kstrlen(dir);
        RDFile *files[RAMDISK_MAX_FILES];
        int n = ramdisk_list(files, RAMDISK_MAX_FILES);
        int i, shown = 0;
        for (i = 0; i < n; i++) {
            if (plen && kstrncmp(files[i]->name, dir, plen) != 0) continue;
            if ((unsigned)kstrlen(files[i]->name) == plen) continue; /* dir marker */
            kprintf("  %-20s  %u bytes\n", files[i]->name + plen, files[i]->size);
            shown = 1;
        }
        if (!shown) vga_puts("  (empty)\n");
    }
    else if (kstrcmp(argv[0], "cat") == 0) {
        if (argc < 2) { vga_puts("usage: cat <file> [file...]\n"); return; }
        int fi;
        for (fi = 1; fi < argc; fi++) {
            char resolved[RAMDISK_FNAME_LEN];
            if (!fs_resolve(argv[fi], resolved, sizeof(resolved)) || fs_is_dir(resolved)) {
                kprintf("cat: %s: no such file or is a directory\n", argv[fi]);
                return;
            }
            RDFile *f = ramdisk_open(resolved);
            if (!f) { kprintf("cat: %s: no such file\n", argv[fi]); return; }
            unsigned i;
            for (i = 0; i < f->size; i++) {
                char c;
                ramdisk_read(f, &c, i, 1);
                vga_putc(c);
            }
        }
        vga_putc('\n');
    }
    else if (kstrcmp(argv[0], "rm") == 0) {
        if (argc < 2) { vga_puts("usage: rm <file>\n"); return; }
        char resolved[RAMDISK_FNAME_LEN];
        if (!fs_resolve(argv[1], resolved, sizeof(resolved))) {
            kprintf("rm: %s: no such file\n", argv[1]);
            return;
        }
        if (fs_is_dir(resolved)) {
            kprintf("rm: %s: is a directory\n", argv[1]);
            return;
        }
        RDFile *f = ramdisk_open(resolved);
        if (!f) { kprintf("rm: %s: no such file\n", argv[1]); return; }
        ramdisk_delete(f);
        kprintf("removed %s\n", resolved);
    }
    else if (kstrcmp(argv[0], "mkdir") == 0) {
        if (argc < 2) { vga_puts("usage: mkdir <name>\n"); return; }
        char resolved[RAMDISK_FNAME_LEN];
        if (!fs_resolve(argv[1], resolved, sizeof(resolved))) {
            kprintf("mkdir: %s: name too long\n", argv[1]);
            return;
        }
        char dirname[RAMDISK_FNAME_LEN];
        kmemcpy(dirname, resolved, sizeof(dirname));
        unsigned dl = (unsigned)kstrlen(dirname);
        if (dl == 0 || dirname[dl - 1] != '/') {
            if (dl + 1 >= sizeof(dirname)) { kprintf("mkdir: %s: name too long\n", argv[1]); return; }
            dirname[dl] = '/';
            dirname[dl + 1] = 0;
        }
        if (fs_dir_exists(dirname)) {
            kprintf("mkdir: %s: already exists\n", dirname);
            return;
        }
        if (dl > 0) {
            char parent[RAMDISK_FNAME_LEN];
            unsigned pl = dl - 1;
            while (pl > 0 && dirname[pl - 1] != '/') pl--;
            kmemcpy(parent, dirname, pl);
            parent[pl] = 0;
            if (!fs_dir_exists(parent)) {
                kprintf("mkdir: %s: no such directory\n", parent);
                return;
            }
        }
        if (!ramdisk_create(dirname, 0)) {
            kprintf("mkdir: %s: cannot create\n", dirname);
            return;
        }
        kprintf("created %s\n", dirname);
    }
    else if (kstrcmp(argv[0], "cd") == 0) {
        if (argc < 2) { fs_cwd[0] = 0; return; }
        char resolved[RAMDISK_FNAME_LEN];
        if (!fs_resolve(argv[1], resolved, sizeof(resolved))) {
            kprintf("cd: %s: no such directory\n", argv[1]);
            return;
        }
        unsigned rl = (unsigned)kstrlen(resolved);
        if (rl == 0) { fs_cwd[0] = 0; return; }   /* root has no marker */
        char target[RAMDISK_FNAME_LEN];
        kmemcpy(target, resolved, rl + 1);
        if (target[rl - 1] != '/') {
            if (rl + 1 >= sizeof(target)) { kprintf("cd: %s: no such directory\n", argv[1]); return; }
            target[rl] = '/';
            target[rl + 1] = 0;
        }
        if (!fs_dir_exists(target)) {
            kprintf("cd: %s: no such directory\n", argv[1]);
            return;
        }
        kmemcpy(fs_cwd, target, sizeof(target));
    }
    else if (kstrcmp(argv[0], "pwd") == 0) {
        vga_puts(fs_cwd[0] ? fs_cwd : "/");
        vga_putc('\n');
    }
    else if (kstrcmp(argv[0], "trace") == 0) {
        if (argc > 1) {
            if (kstrcmp(argv[1], "on") == 0) syscall_trace_set(1);
            else if (kstrcmp(argv[1], "off") == 0) syscall_trace_set(0);
            else { vga_puts("usage: trace [on|off]\n"); return; }
        }
        kprintf("syscall tracing: %s\n", syscall_trace_enabled() ? "on" : "off");
    }
    else if (kstrcmp(argv[0], "net") == 0) {
        if (argc < 2) {
            net_cmd_status();
        } else if (kstrcmp(argv[1], "ping") == 0) {
            if (argc < 3) { vga_puts("usage: net ping <ip>\n"); return; }
            net_cmd_ping(argv[2]);
        } else if (kstrcmp(argv[1], "dns") == 0) {
            if (argc < 3) { vga_puts("usage: net dns <host>\n"); return; }
            net_cmd_dns(argv[2]);
        } else {
            vga_puts("usage: net [ping <ip> | dns <host>]\n");
        }
    }
    else if (kstrcmp(argv[0], "ps") == 0) {
        int i;
        for (i = 0; i < kprog_count; i++) {
            KProg *p = &kprog_table[i];
            kprintf("  %-12s  %s  %p\n", p->name,
                    p->is_proc ? "proc" : "rel",
                    p->is_proc ? p->proc_entry : (void *)p->entry);
        }
        if (kprog_count == 0) vga_puts("  (no programs registered)\n");
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
        int nl = (int)kstrlen(argv[1]);
        if (nl > 4 && kstrcmp(argv[1] + nl - 4, ".cvm") == 0) {
            static prog_entry_t cvm_entry = 0;
            if (!cvm_entry) {
                RDFile *rf = ramdisk_open("cvm.o");
                if (!rf) { shell_report("run: cvm.o not on ramdisk", 0); return; }
                unsigned char *data = kmalloc(rf->size);
                if (!data) { kprintf("run: oom\n"); return; }
                ramdisk_read(rf, data, 0, rf->size);
                void *e = elf_load(data, rf->size);
                if (!e) { shell_report("run: cannot load cvm.o", 0); return; }
                cvm_entry = (prog_entry_t)e;
            }
            int ret = cvm_entry(argc - 1, argv + 1);
            shell_report_exit(ret);
            return;
        }
        int i, found = 0;
        for (i = 0; i < kprog_count; i++)
            if (kstrcmp(kprog_table[i].name, argv[1]) == 0) { found = 1; break; }
        const char *target = argv[1];
        char progname[32];
        if (!found) {
            void *entry = 0;
            if (!shell_load(argv[1], progname, &entry)) {
                shell_report("run: not found: ", argv[1]);
                return;
            }
            target = progname;
        }
        int ret = k_spawn(target, argc - 1, argv + 1);
        shell_report_exit(ret);
    }
    else {
        int ret = k_spawn(argv[0], argc, argv);
        if (ret == -1) {
            ret = shell_run_from_path(argv[0], argc, argv);
            if (ret < 0) shell_report("command not found: ", argv[0]);
            else shell_report_exit(ret);
        } else {
            shell_report_exit(ret);
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
    k_register_symbol("strncat",  (void *)kstrncat);
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
    k_register_symbol("fgets",    (void *)kfgets);
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
    k_register_symbol("atol",     (void *)katol);
    k_register_symbol("strtol",   (void *)katol);
    k_register_symbol("abort",    (void *)kexit);
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
    mm_setup_protections();
    kprintf("isolation: user window %x..%x ring 3, syscall ABI on %x\n",
            USER_LOAD_BASE, USER_LOAD_END, SYS_KSTK_TOP);
    net_init();

    if ((unsigned long)(ramdisk_end - ramdisk_start) > 0) {
        ramdisk_setup_from(ramdisk_start, (unsigned)(ramdisk_end - ramdisk_start));
    }

    kprintf("Heap: 64 MB  Symbols: %d  (Linux ELF: syscall ABI ready)\n", ksym_count);

    shell_run();
}
