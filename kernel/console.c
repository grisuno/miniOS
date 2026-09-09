#include "kernel.h"
#include "sched.h"
#include "vga_fb.h"
#define XXH_STATIC_LINKING_ONLY
#include "xxhash.h"
#include "stb/stb_api.h"

/* console.c -- Execution-context output: text console, capture, libc names.
 *
 * Bounded Context (DDD): all character-console output lives here. kernel.c
 * keeps only orchestration (kmain) and the syscall trampoline; it owns no
 * console state and no libc table. Consumers call vga_putc/vga_puts,
 * redirect_* and register_libc_symbols through kernel.h. */

static int vga_x, vga_y;
static char vga_color = 0x07;

int vga_get_x(void) { return vga_x; }
int vga_get_y(void) { return vga_y; }
void vga_set_xy(int x, int y) { vga_x = x; vga_y = y; }
char vga_get_color(void) { return vga_color; }

static inline unsigned vga_offset(int x, int y) { return (unsigned)(y * VGA_COLS + x) * 2; }

void vga_clear(void) {
    int i;
    for (i = 0; i < VGA_COLS * VGA_ROWS; i++) {
        VGA_BASE[i * 2]     = ' ';
        VGA_BASE[i * 2 + 1] = vga_color;
    }
    vga_x = vga_y = 0;
    vga_set_cursor(0, 0);
    sb_reset();
}

void vga_set_cursor(int x, int y) {
    unsigned short pos = (unsigned short)(y * VGA_COLS + x);
    unsigned char lo = pos & 0xFF;
    unsigned char hi = (pos >> 8) & 0xFF;
    __asm__ volatile(
        "movw $0x3D4, %%dx\n\t"
        "movb $0x0F, %%al\n\t"
        "outb %%al, %%dx\n"
        "movb %b0, %%al\n\t"
        "outb %%al, %%dx\n"
        "movb $0x0E, %%al\n\t"
        "outb %%al, %%dx\n"
        "movb %b1, %%al\n\t"
        "outb %%al, %%dx"
        :
        : "r"((unsigned long)lo), "r"((unsigned long)hi)
        : "ax", "dx"
    );
}

void vga_scroll(void) {
    int y, x;
    sb_capture_row0();
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

void vga_cursor_enable(int on) {
    outb(0x3D4, 0x0A);
    unsigned char v = inb(0x3D5);
    if (on) v &= 0xDF; else v |= 0x20;
    outb(0x3D5, v);
}

static void vga_raw_space(void) {
    unsigned off = vga_offset(vga_x, vga_y);
    VGA_BASE[off]     = ' ';
    VGA_BASE[off + 1] = vga_color;
    vga_x++;
    if (vga_x >= VGA_COLS) vga_newline();
}

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

int redirect_active(void) { return redir_active; }

static int redirect_putc(char c) {
    if (!redir_active) return 0;
    if (redir_len < redir_cap || redir_grow()) redir_buf[redir_len++] = c;
    else redir_overflow = 1;
    return 1;
}

int redirect_suspend(void) {
    int was = redir_active;
    redir_active = 0;
    return was;
}

void redirect_resume(int was) {
    redir_active = was;
}

int redirect_begin(void) {
    redir_len      = 0;
    redir_overflow = 0;
    if (!redir_buf && !redir_grow()) return 0;
    redir_active = 1;
    return 1;
}

int redirect_commit(const char *path, int append_mode) {
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

spinlock_t console_lock = SPINLOCK_INIT;

void vga_putc(char c) {
    int locked = spin_trylock(&console_lock);
    if (redirect_putc(c)) { if (locked) spin_unlock(&console_lock); return; }
    serial_putc(c);
    if (vga_fb_active) {
        if (c == '\n') serial_putc('\r');
        vga_fb_putc_term(c);
        if (locked) spin_unlock(&console_lock);
        return;
    }
    if (vga_mode_is_active()) {
        if (c == '\n') serial_putc('\r');
        if (locked) spin_unlock(&console_lock);
        return;
    }
    if (c == '\n') { serial_putc('\r'); vga_newline(); vga_set_cursor(vga_x, vga_y); if (locked) spin_unlock(&console_lock); return; }
    if (c == '\r') { vga_x = 0; vga_set_cursor(vga_x, vga_y); if (locked) spin_unlock(&console_lock); return; }
    if (c == '\t') {
        int spaces = 8 - (vga_x & 7);
        while (spaces--) vga_raw_space();
        vga_set_cursor(vga_x, vga_y);
        if (locked) spin_unlock(&console_lock);
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
        if (locked) spin_unlock(&console_lock);
        return;
    }
    unsigned off = vga_offset(vga_x, vga_y);
    VGA_BASE[off]     = c;
    VGA_BASE[off + 1] = vga_color;
    vga_x++;
    if (vga_x >= VGA_COLS) vga_newline();
    vga_set_cursor(vga_x, vga_y);
    if (locked) spin_unlock(&console_lock);
}

void vga_puts(const char *s) {
    while (*s) vga_putc(*s++);
}

void register_libc_symbols(void) {
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

    k_register_symbol("malloc",   (void *)kmalloc);
    k_register_symbol("free",     (void *)kfree);
    k_register_symbol("calloc",   (void *)kcalloc);
    k_register_symbol("realloc",  (void *)krealloc);

    k_register_symbol("XXH64",    (void *)XXH64);

    k_register_symbol("stbi_load_file", (void *)stbi_load_file);
    k_register_symbol("stbi_load_from_memory", (void *)stbi_load_from_memory);
    k_register_symbol("stbi_image_free", (void *)stbi_image_free);

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

    k_register_symbol("printf",   (void *)kprintf);
    k_register_symbol("sprintf",  (void *)ksprintf);
    k_register_symbol("putchar",  (void *)vga_putc);
    k_register_symbol("puts",     (void *)vga_puts);

    k_register_symbol("stdin",    (void *)&kstdin);
    k_register_symbol("stdout",   (void *)&kstdout);
    k_register_symbol("stderr",   (void *)&kstderr);

    k_register_symbol("exit",     (void *)kexit);

    k_register_symbol("snprintf", (void *)ksnprintf);
    k_register_symbol("atol",     (void *)katol);
    k_register_symbol("strtol",   (void *)katol);
    k_register_symbol("abort",    (void *)kexit);
}
