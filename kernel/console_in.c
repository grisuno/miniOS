/** Docstring: Console input device (kernel/console_in.c).
 *
 * Owns the pushback FIFO, the serial + PS/2 raw multiplexer, the
 * blocking/peek/raw/job console readers and the text-console scrollback
 * view. Extracted from kernel/shell.c: these readers serve the shell
 * prompt, the built-in editor, the SPAWN wait loop and the GETC_RAW
 * syscall, so they belong to the console layer, not to the shell.
 * Reaches the rest of the kernel through kernel.h plus drivers/kbd.h
 * and vga_fb.h only. */
#include "kernel.h"
#include "drivers/kbd.h"
#include "vga_fb.h"
#include "console_in.h"

#define PB_LEN 8
static unsigned char pb_buf[PB_LEN];
static int pb_head, pb_tail;

static int pb_empty(void) { return pb_head == pb_tail; }
static int pb_count(void) { return (pb_tail - pb_head + PB_LEN) % PB_LEN; }
static void pb_push_back(unsigned char c) {
    if (pb_count() >= PB_LEN - 1) return;
    pb_buf[pb_tail] = c;
    pb_tail = (pb_tail + 1) % PB_LEN;
}
static void pb_push_front(unsigned char c) {
    if (pb_count() >= PB_LEN - 1) return;
    pb_head = (pb_head - 1 + PB_LEN) % PB_LEN;
    pb_buf[pb_head] = c;
}
static int pb_pop(void) {
    if (pb_empty()) return -1;
    int c = pb_buf[pb_head];
    pb_head = (pb_head + 1) % PB_LEN;
    return c;
}
static int pb_peek(void) {
    if (pb_empty()) return -1;
    return pb_buf[pb_head];
}

/** Docstring: Push one byte back into the console FIFO; the next
 * console_getc/console_peek serves it first. Drops the byte when full. */
void console_ungetc(unsigned char c) {
    pb_push_front(c);
}

/** Docstring: Next raw byte (kbd queue, then serial, then PS/2) without
 * touching the pushback FIFO; blocks until one is available. */
static int raw_blocking_getc(void) {
    static unsigned mouse_tick_cnt;
    for (;;) {
        if (!kbd_q_empty()) return kbd_q_pop();
        if (serial_available()) {
            int c = serial_getc();
            if (c >= 0) return c;
        }
        if (kbd_available()) {
            int c = kbd_read();
            if (c >= 0) return c;
        }
        if (vga_fb_active && (++mouse_tick_cnt & 0xFF) == 0)
            vga_fb_mouse_tick();
        __asm__ volatile("pause");
    }
}

/** Docstring: Non-blocking variant of the above for sequence lookahead. */
static int raw_try_getc(void) {
    if (!kbd_q_empty()) return kbd_q_pop();
    if (serial_available()) {
        int c = serial_getc();
        if (c >= 0) return c;
    }
    if (kbd_available()) {
        int c = kbd_read();
        if (c >= 0) return c;
    }
    return -1;
}

/** Docstring: Poll for the next raw byte with a bounded spin, so a
 * multi-byte escape sequence arriving over the serial line (byte by byte)
 * is read as a unit. Returns the byte, or -1 after MAX_SEQ_POLL polls.
 * The bound keeps a bare ESC (never completed into a sequence) from
 * hanging the reader. */
#define MAX_SEQ_POLL 200000
static int raw_wait_seq(void) {
    int n;
    for (n = 0; n < MAX_SEQ_POLL; n++) {
        int c = raw_try_getc();
        if (c >= 0) return c;
        __asm__ volatile("pause");
    }
    return -1;
}

static void scrollback_view(int initial_dir);

/** Docstring: Called after an ESC byte has been read. Pulls the remainder
 * of the sequence non-blocking and classifies it. Returns 1 (PageUp),
 * 2 (PageDown), or 0 for "not a page key" — in which case every byte
 * pulled EXCEPT the leading ESC is re-injected into the pushback FIFO so
 * the caller can hand them back to the readline layer exactly as it would
 * a raw escape. */
static int consume_page_after_esc(void) {
    int p0 = raw_try_getc();
    if (p0 < 0) return 0;                 /* bare ESC */
    if (p0 != KEY_CSI) { pb_push_front((unsigned char)p0); return 0; }
    /* After ESC [ the sequence is a unit: wait briefly for its final byte so
     * a serial-delivered escape (arrow, Home/End, Del, PageUp/Down) is read
     * intact instead of being split across reads. */
    int p1 = raw_wait_seq();
    if (p1 < 0) { pb_push_front((unsigned char)KEY_CSI); return 0; }
    if (p1 == KEY_PGUP_SEQ || p1 == KEY_PGDN_SEQ || p1 == '3') {
        int p2 = raw_wait_seq();
        if (p2 == KEY_TILDE) return (p1 == KEY_PGUP_SEQ) ? 1 : (p1 == KEY_PGDN_SEQ) ? 2 : 3;
        if (p2 >= 0) pb_push_front((unsigned char)p2);
        pb_push_front((unsigned char)p1);
        pb_push_front((unsigned char)KEY_CSI);
        return 0;
    }
    pb_push_front((unsigned char)p1);
    pb_push_front((unsigned char)KEY_CSI);
    return 0;
}

/** Docstring: Blocking read from either the PS/2 keyboard or COM1 serial
 * line. Recognises the PageUp/PageDown escape sequences and detours into
 * the scrollback view; the view re-injects any terminating key into the
 * pushback FIFO, so once it returns console_getc() simply serves the FIFO
 * again. */
int console_getc(void) {
    if (!pb_empty()) return pb_pop();
    int c = raw_blocking_getc();
    if (c != KEY_ESC) return c;
    int r = consume_page_after_esc();
    if (r == 1) { scrollback_view(-1); return console_getc(); }
    if (r == 2) { scrollback_view(+1); return console_getc(); }
    if (r == 3) {
        /* Delete key: re-inject the ESC [ 3 ~ sequence so the readline layer
         * handles it identically to a keyboard-delivered Del. */
        pb_push_front(KEY_TILDE);
        pb_push_front('3');
        pb_push_front(KEY_CSI);
        return KEY_ESC;
    }
    return KEY_ESC;
}

/** Docstring: Next buffered byte without consuming it, or -1 when nothing
 * is available right now. Used to tell an ESC prefix from a complete
 * escape sequence, which always arrives in one burst. Global so SYS_SPAWN
 * waits in spawn.c can poll for Ctrl+C exactly like the shell foreground
 * wait does. */
int console_peek(void) {
    if (!pb_empty()) return pb_peek();
    int c = raw_try_getc();
    if (c >= 0) pb_push_back((unsigned char)c);
    return pb_peek();
}

/** Docstring: Raw console multiplexer for the GETC_RAW syscall. The same
 * serial + PS/2 sources console_getc funnels, but without the line
 * buffering, echo or scrollback detour: a ring-3 fullscreen program reads
 * keystrokes byte by byte. Blocking spins with a pause (and the desktop
 * tick, as the shell idle loop does); the try variant returns -1 when
 * nothing is available so user space can implement its own timeout. */
int console_raw_try(void) {
    return raw_try_getc();
}

int console_raw_get(void) {
    return raw_blocking_getc();
}

/** Docstring: PS/2-only GETC_RAW source for ring-3 background jobs. */
int console_job_try(void) {
    if (kbd_available()) {
        int c = kbd_read();
        if (c >= 0) return c;
    }
    return -1;
}

/** Docstring: Blocking PS/2-only GETC_RAW source for background jobs. */
int console_job_get(void) {
    for (;;) {
        int c = console_job_try();
        if (c >= 0) return c;
        __asm__ volatile("pause");
    }
}

/** Docstring: Scrollback view. Renders a 25-row window over (scrollback
 * ring + live screen) into the VGA framebuffer and to the serial console,
 * hides the cursor, and lets the user page up/down through history.
 * PageDown at the bottom, or any other key, exits; the exit key is
 * re-injected into the pushback FIFO so the readline that was waiting for
 * input receives it as if scrollback never happened. */
#define SB_LEN  (VGA_ROWS * VGA_COLS * 2)

static void scrollback_render(int voff, int total, const unsigned char *saved) {
    int sb_cnt = sb_get_count();
    char color = vga_get_color();
    for (int r = 0; r < VGA_ROWS; r++) {
        int li = voff + r;
        for (int x = 0; x < VGA_COLS; x++) {
            char ch;
            if (li < sb_cnt) {
                ch = sb_get_char(li, x);
            } else {
                int live_row = li - sb_cnt;
                ch = (char)saved[(unsigned long)(live_row * VGA_COLS + x) * 2];
            }
            VGA_BASE[(unsigned long)(r * VGA_COLS + x) * 2]     = ch;
            VGA_BASE[(unsigned long)(r * VGA_COLS + x) * 2 + 1] = color;
            serial_putc(ch);
        }
        serial_putc('\n');
    }
}

#define SB_PGUP  1
#define SB_PGDN  2
#define SB_EXIT  3

/** Docstring: Reads the next scrollback key event: PageUp/PageDown
 * navigate; any other key (or a non-page escape sequence) is re-injected
 * and reported as SB_EXIT. */
static int sb_next(void) {
    int c = raw_blocking_getc();
    if (c != KEY_ESC) { pb_push_front((unsigned char)c); return SB_EXIT; }
    int r = consume_page_after_esc();
    if (r == 1) return SB_PGUP;
    if (r == 2) return SB_PGDN;
    pb_push_front((unsigned char)KEY_ESC);   /* rest already re-injected */
    return SB_EXIT;
}

static void scrollback_view(int initial_dir) {
    sb_init();
    int sb_cnt = sb_get_count();
    if (sb_cnt == 0) return;

    static unsigned char saved[SB_LEN];
    for (int i = 0; i < SB_LEN; i++) saved[i] = VGA_BASE[i];
    int saved_x = vga_get_x(), saved_y = vga_get_y();
    vga_cursor_enable(0);

    int total  = sb_cnt + VGA_ROWS;
    int bottom = total - VGA_ROWS;
    int voff   = (initial_dir < 0) ? bottom - VGA_ROWS : bottom;
    if (voff < 0) voff = 0;
    if (voff > bottom) voff = bottom;

    scrollback_render(voff, total, saved);

    for (;;) {
        int k = sb_next();
        if (k == SB_PGUP) {
            int n = voff - VGA_ROWS;
            if (n < 0) n = 0;
            if (n != voff) { voff = n; scrollback_render(voff, total, saved); }
            continue;
        }
        if (k == SB_PGDN) {
            if (voff >= bottom) break;       /* at the live screen: leave */
            int n = voff + VGA_ROWS;
            if (n > bottom) n = bottom;
            if (n != voff) { voff = n; scrollback_render(voff, total, saved); }
            continue;
        }
        break;                               /* SB_EXIT: key re-injected     */
    }

    for (int i = 0; i < SB_LEN; i++) VGA_BASE[i] = saved[i];
    vga_set_xy(saved_x, saved_y);
    vga_set_cursor(saved_x, saved_y);
    vga_cursor_enable(1);
}
