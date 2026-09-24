/** Docstring: kernel/panic.c -- Kernel panic screen.
 *
 * Bounded Context (DDD): every unrecoverable fault funnels here after
 * the serial forensics in kernel/sched.c. Owns the on-screen banner
 * (framebuffer terminal when the desktop is up, raw VGA text otherwise,
 * serial only while a graphics program owns the display), the
 * frame-pointer backtrace through headers/panic.h and the halt. The
 * serial dump in sched.c stays the primary record; this screen exists
 * for real hardware with no serial console.
 *
 * Fault-context discipline: no heap allocation, no locks, no kprintf.
 * All output goes through serial_putc (polled, lock-free) and the
 * framebuffer terminal or raw VGA cells. A re-entered fault (the banner
 * itself faulted on corrupt mappings) skips everything and halts. */

#include "kernel.h"
#include "sched.h"
#include "vga_fb.h"
#include "panic.h"

static volatile int panic_entered;

static void panic_hex(unsigned long v, int digits) {
    static const char d[] = "0123456789abcdef";
    int i;
    for (i = digits - 1; i >= 0; i--)
        serial_putc(d[(v >> (i * 4)) & 0xF]);
}

static void panic_fb_puts(const char *s) {
    if (vga_fb_active) {
        while (*s) vga_fb_putc_term(*s++);
        return;
    }
    if (!vga_mode_is_active()) {
        static int row = 0;
        int col = 0;
        while (*s && row < VGA_ROWS) {
            unsigned off;
            if (*s == '\n') {
                row++;
                col = 0;
                s++;
                continue;
            }
            if (col >= VGA_COLS) {
                row++;
                col = 0;
                continue;
            }
            off = (unsigned)(row * VGA_COLS + col) * 2u;
            VGA_BASE[off] = *s;
            VGA_BASE[off + 1] = (char)0x4F;
            col++;
            s++;
        }
        if (row < VGA_ROWS) row++;
    }
}

static void panic_fb_hex(unsigned long v, int digits) {
    static const char d[] = "0123456789abcdef";
    char buf[16];
    int i;
    for (i = 0; i < digits && i < 16; i++)
        buf[i] = d[(v >> ((digits - 1 - i) * 4)) & 0xF];
    buf[i] = 0;
    panic_fb_puts(buf);
}

/** Docstring: Predicate behind the backtrace walk: canonical low half
 * and inside a readable range (kernel image, kernel heap or the user
 * window). Anything else stops the chain instead of nesting a fault. */
static int panic_frame_valid(unsigned long a) {
    if (a >= 0x0000800000000000UL)
        return 0;
    /* Low stacks: the shell boot stack and the syscall kernel stack
     * live below the kernel link base (identity mapped RAM). */
    if (a >= 0x80000UL && a < 0x100000UL)
        return 1;
    if (a >= 0x100000UL && a < 0x1000000UL)
        return 1;
    if (a >= (unsigned long)HEAP_BASE &&
            a < (unsigned long)HEAP_BASE + (unsigned long)HEAP_SIZE)
        return 1;
    if (a >= (unsigned long)USER_LOAD_BASE && a < (unsigned long)USER_LOAD_END)
        return 1;
    return 0;
}

/** Docstring: Paint the panic screen for an unrecoverable fault and
 * halt when asked. vector/err/rip/rsp come from the trap frame, rbp is
 * the faulting frame pointer. halt != 0 ends in hlt (real faults);
 * halt == 0 returns (the `panic` builtin demo). Re-entry halts
 * silently: the banner path itself faulted, nothing more can print. */
void panic_screen(unsigned long vector, unsigned long err,
        unsigned long rip, unsigned long rsp, unsigned long rbp, int halt) {
    unsigned long bt[PANIC_BT_MAX];
    int nbt, i;
    if (panic_entered) {
        for (;;) __asm__ volatile("hlt");
    }
    panic_entered = 1;
    nbt = panic_backtrace(rbp, panic_frame_valid, bt, PANIC_BT_MAX);
    serial_puts("panic: vector=");
    panic_hex(vector, 2);
    serial_puts(" err=");
    panic_hex(err, 8);
    serial_puts(" rip=");
    panic_hex(rip, 16);
    serial_puts(" rsp=");
    panic_hex(rsp, 16);
    serial_puts(" bt=");
    for (i = 0; i < nbt; i++) {
        serial_putc(' ');
        panic_hex(bt[i], 16);
    }
    if (nbt == 0)
        serial_puts(" <empty>");
    serial_puts("\n");
    panic_fb_puts("\n*** KERNEL PANIC ***\nvector=");
    panic_fb_hex(vector, 2);
    panic_fb_puts(" err=");
    panic_fb_hex(err, 8);
    panic_fb_puts("\nrip=");
    panic_fb_hex(rip, 16);
    panic_fb_puts("\nrsp=");
    panic_fb_hex(rsp, 16);
    panic_fb_puts("\nbt=");
    for (i = 0; i < nbt; i++) {
        panic_fb_puts(" ");
        panic_fb_hex(bt[i], 16);
    }
    if (nbt == 0)
        panic_fb_puts(" <empty>");
    panic_fb_puts("\nsystem halted\n");
    panic_entered = 0;
    if (halt) {
        for (;;) __asm__ volatile("hlt");
    }
}
