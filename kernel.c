#include "kernel.h"
#include "net.h"
#include "tls.h"
#include "bootdefs.h"
#include "minifs.h"
#include "ide.h"
#include "block.h"
#include "sched.h"
#include "vga_fb.h"
#include "pcspk.h"
#include "sb16.h"
#include "smp.h"
#include "rtc.h"
#include "lz4_kernel.h"
#define XXH_STATIC_LINKING_ONLY
#include "xxhash.h"
#include "stb/stb_api.h"
#include "zip.h"

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

static int vga_mode13h; /* nonzero when a graphics program owns the display */
/* Set when a graphics program activates SYS_VGA_MODE and cleared when the
 * desktop is restored on return. A program (nuklear) may clear vga_mode13h
 * itself before exiting; this flag is what guarantees the desktop is still
 * redrawn on return, otherwise the framebuffer stays frozen on the program's
 * last frame and the cursor is never re-established. */
static int graphics_program_ran;
static int vga_x, vga_y;
static char vga_color = 0x07; /* light grey on black */

/* Console scrollback: a ring of lines that scrolled off the top of the VGA
 * screen. Captured lazily from vga_scroll(); viewed with PageUp/PageDown. */
static char *sb_ring;
static int   sb_head, sb_count, sb_inited;
static void sb_capture_row0(void);
static void sb_init(void);

static inline unsigned vga_offset(int x, int y) { return (unsigned)(y * VGA_COLS + x) * 2; }

void vga_clear(void) {
    int i;
    for (i = 0; i < VGA_COLS * VGA_ROWS; i++) {
        VGA_BASE[i * 2]     = ' ';
        VGA_BASE[i * 2 + 1] = vga_color;
    }
    vga_x = vga_y = 0;
    vga_set_cursor(0, 0);
    if (sb_ring) { sb_head = sb_count = 0; }
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

/* ---- Console scrollback ring ----
 *
 * The ring stores complete text lines that have scrolled off the top of the
 * 25-row VGA screen. Each line is VGA_COLS bytes (the character cell only;
 * colour is regenerated as the default attribute on re-display). The ring is
 * heap-allocated on first use and is a circular buffer of SCROLLBACK_ROWS
 * slots; `clear` resets the cursor (it does not free the ring, which would
 * be re-allocated again the next time a line scrolls). */
#define SCROLLBACK_ROWS 4096

static void sb_init(void) {
    sb_ring = (char *)kmalloc((unsigned long)SCROLLBACK_ROWS * VGA_COLS);
    sb_inited = sb_ring ? 1 : -1;
    sb_head = sb_count = 0;
}

/* Called from vga_scroll() immediately before row 0 is overwritten: copies
 * the row that is about to leave the screen into the ring. */
static void sb_capture_row0(void) {
    if (sb_inited == 0) sb_init();
    if (sb_inited != 1) return;
    int idx = (sb_head + sb_count) % SCROLLBACK_ROWS;
    for (int x = 0; x < VGA_COLS; x++)
        sb_ring[(unsigned long)idx * VGA_COLS + x] = VGA_BASE[vga_offset(x, 0)];
    if (sb_count < SCROLLBACK_ROWS) sb_count++;
    else sb_head = (sb_head + 1) % SCROLLBACK_ROWS;
}

/* Toggle the hardware text cursor. bit 5 of VGA index 0x0A disables the
 * cursor; clearing it brings the cursor back. */
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

static int redirect_suspend(void);
static int redirect_begin(void);
static int redirect_commit(const char *path, int append_mode);
static void redirect_resume(int was);

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
    if (vga_fb_active) {
        if (c == '\n') serial_putc('\r');
        vga_fb_putc_term(c);
        return;
    }
    if (vga_mode13h) {
        if (c == '\n') serial_putc('\r');
        return;
    }
    if (c == '\n') { serial_putc('\r'); vga_newline(); vga_set_cursor(vga_x, vga_y); return; }
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
static int kbd_ctrl;
static int kbd_alt;

/* PS/2 set 1 arrow keys arrive as E0-prefixed make codes; they are
 * translated into the same three-byte CSI sequence a serial terminal
 * sends (ESC [ A / ESC [ B) and buffered here. */
#define KBD_QUEUE_LEN 8
static unsigned char kbd_queue[KBD_QUEUE_LEN];
static int kbd_q_head, kbd_q_tail;
static int kbd_e0;

/* Raw keyboard mode for DOOM: when enabled, PS/2 make/break codes are
 * pushed into a separate queue so the caller sees both press and release
 * events.  The raw queue stores bytes with bit 7 set for break codes. */
#define KBD_RAW_LEN 64
static unsigned char kbd_raw[KBD_RAW_LEN];
static int kbd_raw_head, kbd_raw_tail;
static int kbd_raw_mode;  /* 1 = raw mode (DOOM), 0 = translated mode (shell) */

static void kbd_q_push(unsigned char c) {
    int next = (kbd_q_tail + 1) % KBD_QUEUE_LEN;
    if (next == kbd_q_head) return;
    kbd_queue[kbd_q_tail] = c;
    kbd_q_tail = next;
}

static void kbd_raw_push(unsigned char c) {
    int next = (kbd_raw_tail + 1) % KBD_RAW_LEN;
    if (next == kbd_raw_head) return;
    kbd_raw[kbd_raw_tail] = c;
    kbd_raw_tail = next;
}

static int kbd_q_empty(void) { return kbd_q_head == kbd_q_tail; }

static int kbd_q_pop(void) {
    if (kbd_q_empty()) return -1;
    unsigned char c = kbd_queue[kbd_q_head];
    kbd_q_head = (kbd_q_head + 1) % KBD_QUEUE_LEN;
    return (int)c;
}

int kbd_available(void) {
    unsigned char s;
    __asm__ volatile("inb $0x64, %0" : "=a"(s));
    /* Output-buffer full AND not auxiliary: the PS/2 controller shares one
     * port for keyboard and mouse, and bit 5 marks mouse data. The keyboard
     * poll must not consume mouse bytes (the IRQ12 handler owns those), or a
     * click would be misread as a scancode. */
    return (s & 1) && !(s & 0x20);
}

int kbd_read(void) {
    if (!kbd_q_empty()) return kbd_q_pop();
    while (!kbd_available()) __asm__ volatile("pause");
    unsigned char sc;
    __asm__ volatile("inb $0x60, %0" : "=a"(sc));

    /* Raw mode (DOOM): push make/break codes with E0 prefix preserved.
     * Make codes are sent as-is; break codes have bit 7 set.
     * E0 prefix is pushed as 0xE0 so the reader can detect extended keys. */
    if (kbd_raw_mode) {
        if (sc == KEY_E0) { kbd_e0 = 1; return -1; }
        if (kbd_e0) {
            kbd_e0 = 0;
            kbd_raw_push(0xE0); kbd_raw_push(sc);  /* E0 make or break */
            return -1;
        }
        /* Normal make or break */
        kbd_raw_push(sc);
        return -1;
    }

    /* The E0 prefix must be tested before the release check: 0xE0 has the
     * high bit set, so testing the release bit first swallows every
     * extended-key prefix and arrows/PageUp/PageDown never translate. */
    if (sc == KEY_E0) { kbd_e0 = 1; return -1; }

    if (sc & 0x80) { /* key release */
        sc &= 0x7F;
        if (sc == KEY_LSHIFT || sc == KEY_RSHIFT) kbd_shift = 0;
        if (sc == KEY_LCTRL) kbd_ctrl = 0;
        if (sc == KEY_LALT) kbd_alt = 0;
        kbd_e0 = 0;                     /* a release ends any E0 sequence */
        return -1;
    }

    if (kbd_e0) {
        kbd_e0 = 0;
        /* Ctrl+arrow keys move the framebuffer terminal window */
        if (kbd_ctrl && vga_fb_active) {
            if (sc == KEY_UP)       { vga_fb_move_terminal(0, -1); return -1; }
            if (sc == KEY_DOWN)     { vga_fb_move_terminal(0,  1); return -1; }
            if (sc == KEY_LEFT)     { vga_fb_move_terminal(-1, 0); return -1; }
            if (sc == KEY_RIGHT)    { vga_fb_move_terminal( 1, 0); return -1; }
        }
        /* Alt+arrow keys snap the window to the matching screen half. */
        if (kbd_alt && vga_fb_active) {
            if (sc == KEY_UP)       { vga_fb_snap_window(TILING_TOP); return -1; }
            if (sc == KEY_DOWN)     { vga_fb_snap_window(TILING_BOTTOM); return -1; }
            if (sc == KEY_LEFT)     { vga_fb_snap_window(TILING_LEFT); return -1; }
            if (sc == KEY_RIGHT)    { vga_fb_snap_window(TILING_RIGHT); return -1; }
            if (sc == KEY_HOME)     { vga_fb_snap_window(TILING_TOP_LEFT); return -1; }
            if (sc == KEY_END)      { vga_fb_snap_window(TILING_BOTTOM_RIGHT); return -1; }
        }
        if (sc == KEY_UP) {
            kbd_q_push(KEY_ESC); kbd_q_push(KEY_CSI); kbd_q_push(KEY_ARR_UP);
        } else if (sc == KEY_DOWN) {
            kbd_q_push(KEY_ESC); kbd_q_push(KEY_CSI); kbd_q_push(KEY_ARR_DOWN);
        } else if (sc == KEY_RIGHT) {
            kbd_q_push(KEY_ESC); kbd_q_push(KEY_CSI); kbd_q_push(KEY_ARR_RIGHT);
        } else if (sc == KEY_LEFT) {
            kbd_q_push(KEY_ESC); kbd_q_push(KEY_CSI); kbd_q_push(KEY_ARR_LEFT);
        } else if (sc == KEY_HOME) {
            kbd_q_push(KEY_ESC); kbd_q_push(KEY_CSI); kbd_q_push(KEY_HOME_SEQ);
        } else if (sc == KEY_END) {
            kbd_q_push(KEY_ESC); kbd_q_push(KEY_CSI); kbd_q_push(KEY_END_SEQ);
        } else if (sc == KEY_PGUP) {
            kbd_q_push(KEY_ESC); kbd_q_push(KEY_CSI);
            kbd_q_push(KEY_PGUP_SEQ); kbd_q_push(KEY_TILDE);
        } else if (sc == KEY_PGDN) {
            kbd_q_push(KEY_ESC); kbd_q_push(KEY_CSI);
            kbd_q_push(KEY_PGDN_SEQ); kbd_q_push(KEY_TILDE);
        }
        return -1;
    }

    if (sc == KEY_LSHIFT || sc == KEY_RSHIFT) { kbd_shift = 1; return -1; }
    if (sc == KEY_LCTRL) { kbd_ctrl = 1; return -1; }
    if (sc == KEY_LALT) { kbd_alt = 1; return -1; }

    /* F11: toggle fullscreen, F5: reset terminal position */
    if (vga_fb_active) {
        if (sc == KEY_F11) { vga_fb_toggle_fullscreen(); return -1; }
        if (sc == KEY_F5)  { vga_fb_move_terminal(0, 0); return -1; }
    }

    /* Alt = WM modifier: resize, quadrant snap, reset, minimize and close. */
    if (vga_fb_active && kbd_alt) {
        char ch = kbd_us[sc];
        if (sc == KEY_ENTER)      { vga_fb_toggle_fullscreen(); return -1; }
        if (sc == KEY_HOME)       { vga_fb_snap_window(TILING_TOP_LEFT); return -1; }
        if (sc == KEY_END)        { vga_fb_snap_window(TILING_BOTTOM_RIGHT); return -1; }
        if (ch == 'm' || ch == 'M') { vga_fb_toggle_minimize(); return -1; }
        if (ch == 'x' || ch == 'X') { vga_fb_close_active(); return -1; }
        if (ch == 'q' || ch == 'Q') { vga_fb_close_active(); return -1; }
        if (ch == '[')            { vga_fb_resize(-1, 0); return -1; }
        if (ch == ']')            { vga_fb_resize(1, 0); return -1; }
        if (ch == '-')            { vga_fb_resize(-1, -1); return -1; }
        if (ch == '=')            { vga_fb_resize(1, 1); return -1; }
        if (ch == '0')            { vga_fb_reset_default(); return -1; }
    }

    if (kbd_shift)
        return kbd_us_shift[sc];
    else
        return kbd_us[sc];
}

/* Restore the translated keyboard mode the shell expects after a user
 * program returns. A graphics program (DOOM) enables raw mode via
 * SYS_KBD_RAW(1) but does not always disable it on exit; if left set, the
 * shell's translated readline never sees PS/2 keystrokes and the desktop
 * appears frozen until a serial byte unblocks it. */
void kbd_reset_for_shell(void) {
    kbd_raw_mode = 0;
    kbd_q_head = kbd_q_tail = 0;
    kbd_raw_head = kbd_raw_tail = 0;
    kbd_e0 = 0;
}


/* ================================================================
 *  Memory allocator — dlmalloc backend over the fixed kernel heap.
 *  kmalloc/free/calloc/realloc delegate to a private mspace rooted at
 *  [HEAP_BASE, HEAP_BASE+HEAP_SIZE) (see third_party/dlmalloc). The
 *  mspace is built with HAVE_MORECORE=0 and HAVE_MMAP=0, so it can
 *  never grow beyond the heap; an exhausted heap returns 0 exactly
 *  like the first-fit allocator it replaced.
 * ================================================================ */

#define ALIGN_UP(x, a) (((x) + (a) - 1) & ~((a) - 1))

/* ---- Physical memory map (identity-mapped 0..1GB by the bootloader) ----
 * The user-window and kernel-heap layout lives in progs/minios_abi.h (single
 * source of truth) and is surfaced through kernel.h, so a layout change is a
 * one-line edit in one file instead of a cross-file address hunt.
 *   0x00000000 .. 0x00100000   BIOS / kernel image / page tables / stack
 *   0x00400000 .. 0x0C000000   user program region (ELF load addr + brk)
 *   0x0C000000 .. 0x18000000   192 MB kernel heap (HEAP_BASE/HEAP_SIZE)
 */
#define EFAULT  (-14)

#define MSR_EFER   0xC0000080
#define EFER_NXE   0x00000800

#define PT_FLAGS_PS       0x080
#define PT_FLAGS_NX       0x8000000000000000ULL
#define PT_ADDR_MASK      0x000FFFFFFFFFF000ULL
#define PT_USER_ENTRY     (0x003 | PT_FLAGS_USER)  /* present | rw | user */
#define PT_USER_NX_ENTRY  ((unsigned long)(PT_USER_ENTRY | PT_FLAGS_NX))

/* Asm-safe (no UL suffix) mirror of the user window for the syscall-entry
 * return discriminator; the trampoline is a raw string literal, so the C
 * preprocessor cannot paste the UL-suffixed macros into it. The values must
 * track minios_abi.h; the _Static_asserts below prove they do. */
#define USER_WIN_LO     0x00400000
#define USER_WIN_HI     0x0C000000
#define STR_(x) #x
#define STR(x)  STR_(x)

/* The kernel's layout constants are derived from minios_abi.h, and the
 * asm-safe mirrors above are checked against them at compile time, so a
 * layout edit in the ABI header can never silently leave the syscall return
 * discriminator, the page-table zone sizing or a ring-3 program out of step. */
_Static_assert(USER_WIN_LO == MINIOS_USER_LOAD_BASE, "USER_WIN_LO drift");
_Static_assert(USER_WIN_HI == MINIOS_USER_LOAD_END, "USER_WIN_HI drift");
_Static_assert(USER_LOAD_BASE == MINIOS_USER_LOAD_BASE, "USER_LOAD_BASE drift");
_Static_assert(USER_LOAD_END == MINIOS_USER_LOAD_END, "USER_LOAD_END drift");
_Static_assert(USER_STACK_TOP == MINIOS_USER_STACK_TOP, "USER_STACK_TOP drift");
_Static_assert(USER_BRK_END == MINIOS_USER_BRK_END, "USER_BRK_END drift");
_Static_assert(HEAP_BASE == MINIOS_HEAP_BASE, "HEAP_BASE drift");
_Static_assert(HEAP_SIZE == MINIOS_HEAP_SIZE, "HEAP_SIZE drift");

static inline unsigned long rdmsr(unsigned msr);
static inline void wrmsr(unsigned msr, unsigned long val);

/* Build 4 KB page tables for the whole user window and enable the NX bit
 * (EFER.NXE). Every user page is present, writable, user-accessible and
 * non-executable; the ELF loader later clears NX on the pages a program's
 * executable segments occupy, so a ring-3 program can only execute the text
 * it actually contains. The page tables live in the dedicated
 * PT_USER_TABLES_ADDR zone (0x10000, in the boot staging buffer below the
 * kernel link base), never in the heap (the ramdisk data area is
 * heap-backed and its final size is only discovered at boot, so heap-resident
 * tables could be overwritten by a later reservation) and never inside the
 * kernel image: the zone is BELOW 0x100000, so kernel code, data and .bss
 * can never reach it in the plain build or under KASLR. That zone stays
 * supervisor, so a ring-3 program cannot reach the tables that govern it.
 * The per-page isolation replaces the coarse 2 MB leaves the boot path
 * installs, so kernel image, heap, page tables, VGA and MMIO stay supervisor,
 * and the U/S bit stops a ring-3 program from reading or writing kernel
 * memory. */
static void mm_setup_protections(void) {
    volatile unsigned long *pml4 = (volatile unsigned long *)PT_PML4_ADDR;
    volatile unsigned long *pdpt = (volatile unsigned long *)PT_PDPT_ADDR;
    volatile unsigned long *pd = (volatile unsigned long *)PT_PD_ADDR;
    unsigned long lo = USER_LOAD_BASE >> PT_PD_INDEX_SHIFT;
    unsigned long hi = (USER_LOAD_END - 1) >> PT_PD_INDEX_SHIFT;
    unsigned long i;

    /* Guard against the kernel image growing into the user window: the whole
     * kernel (code + .bss) must end below USER_LOAD_BASE or the .bss would
     * be mapped where user programs load and silently corrupt them. */
    extern char _kernel_end[];
    if ((unsigned long)_kernel_end > USER_LOAD_BASE) {
        kprintf("mm: kernel image reaches 0x%lx, must stay below 0x%lx\n",
                (unsigned long)_kernel_end, USER_LOAD_BASE);
        return;
    }
    if (hi - lo + 1 > PT_USER_TABLES_BYTES / 0x1000) {
        kprintf("mm: user window needs more page table space\n");
        return;
    }
    wrmsr(MSR_EFER, rdmsr(MSR_EFER) | EFER_NXE);
    pml4[0] |= (unsigned long)PT_FLAGS_USER;
    pdpt[0] |= (unsigned long)PT_FLAGS_USER;
    for (i = lo; i <= hi; i++) {
        unsigned long *pt = (unsigned long *)PT_USER_TABLES_ADDR +
                            (i - lo) * 0x1000 / sizeof(unsigned long);
        unsigned long phys = i << PT_PD_INDEX_SHIFT;
        unsigned long k;
        for (k = 0; k < PT_PD_ENTRIES; k++)
            pt[k] = (phys + k * 0x1000) | PT_USER_NX_ENTRY;
        pd[i] = ((unsigned long)pt) | PT_USER_ENTRY;
    }
    __asm__ volatile("mov %%cr3, %%rax; mov %%rax, %%cr3" ::: "rax", "memory");

    /* Map the linear framebuffer into the user window at virtual FB_ADDR, in
     * the reserved tail above the DOOM back-buffer and the brk cap (so a
     * memory-hungry program's heap can never grow over it). The physical base
     * and stride come from the VBE probe (Mode 13h at 0xA0000 when
     * unavailable). The mapping is RW with NX set: it is data, not
     * executable. */
    {
        unsigned long fb_vaddr   = (unsigned long)FB_ADDR;
        unsigned long fb_pd_idx  = fb_vaddr >> PT_PD_INDEX_SHIFT;
        unsigned long fb_pt_off  = (fb_vaddr & 0x1FFFFF) >> 12;
        unsigned long *fb_pt     = (unsigned long *)PT_USER_TABLES_ADDR +
                                   (fb_pd_idx - lo) * 0x1000 /
                                   sizeof(unsigned long);
        unsigned long fb_bytes  = (unsigned long)fb_pitch * (unsigned long)fb_height;
        unsigned long fb_pages  = (fb_bytes + 0xFFF) >> 12;
        unsigned long k;
        if (fb_pages == 0) fb_pages = 1;
        if (fb_pages > PT_PD_ENTRIES - fb_pt_off)
            fb_pages = PT_PD_ENTRIES - fb_pt_off;
        for (k = 0; k < fb_pages; k++)
            fb_pt[fb_pt_off + k] = (fb_phys_base + k * 0x1000) | PT_USER_NX_ENTRY;
    }

    /* Map a kernel-heap back-buffer into the user window at DOOM_BACKBUF_ADDR
     * so a ring-3 graphics program (DOOM) can render off-screen; the kernel
     * composites it onto the desktop on SYS_DOOM_FRAME. The heap is identity
     * mapped, so the physical frame is the returned virtual address. */
    {
        unsigned long bb_vaddr = DOOM_BACKBUF_ADDR;
        unsigned long bb_pd_idx = bb_vaddr >> PT_PD_INDEX_SHIFT;
        unsigned long bb_pt_off = (bb_vaddr & 0x1FFFFF) >> 12;
        unsigned long *bb_pt = (unsigned long *)PT_USER_TABLES_ADDR +
                               (bb_pd_idx - lo) * 0x1000 /
                               sizeof(unsigned long);
        unsigned char *buf = (unsigned char *)kmalloc(DOOM_W * DOOM_H);
        unsigned long phys;
        unsigned long k;
        if (buf == 0) return;
        phys = (unsigned long)buf;
        for (k = 0; k < (DOOM_W * DOOM_H + 0xFFF) >> 12; k++)
            bb_pt[bb_pt_off + k] = (phys + k * 0x1000) | PT_USER_NX_ENTRY;
    }

    /* Map a kernel-heap back-buffer for Nuklear UI apps (the node editor) in
     * the same way, at its own fixed address; the kernel composites it as a
     * titled window on SYS_NK_FRAME (220). */
    {
        unsigned long bb_vaddr = NK_BACKBUF_ADDR;
        unsigned long bb_pd_idx = bb_vaddr >> PT_PD_INDEX_SHIFT;
        unsigned long bb_pt_off = (bb_vaddr & 0x1FFFFF) >> 12;
        unsigned long *bb_pt = (unsigned long *)PT_USER_TABLES_ADDR +
                               (bb_pd_idx - lo) * 0x1000 /
                               sizeof(unsigned long);
        unsigned char *buf = (unsigned char *)kmalloc(NK_W * NK_H);
        unsigned long phys;
        unsigned long k;
        if (buf == 0) return;
        phys = (unsigned long)buf;
        for (k = 0; k < (NK_W * NK_H + 0xFFF) >> 12; k++)
            bb_pt[bb_pt_off + k] = (phys + k * 0x1000) | PT_USER_NX_ENTRY;
    }
}

/* Set or clear the NX bit on the single 4 KB page holding vaddr. The page
 * table for vaddr is the one the user-window PD entry points at; a 2 MB
 * leaf (should not appear inside the window after mm_setup_protections) is
 * left untouched. */
static void mm_user_pte_update(unsigned long vaddr, int exec) {
    volatile unsigned long *pd = (volatile unsigned long *)PT_PD_ADDR;
    unsigned long pd_idx = vaddr >> PT_PD_INDEX_SHIFT;
    unsigned long pde = pd[pd_idx];
    if (!(pde & PT_FLAGS_PRESENT_RW)) return;
    if (pde & PT_FLAGS_PS) return;
    volatile unsigned long *pt =
        (volatile unsigned long *)(pde & PT_ADDR_MASK);
    unsigned long pte_idx = (vaddr >> 12) & 0x1FF;
    if (exec) pt[pte_idx] &= ~(unsigned long)PT_FLAGS_NX;
    else      pt[pte_idx] |=  (unsigned long)PT_FLAGS_NX;
}

/* Mark the pages of a loaded executable segment as executable (clear NX)
 * and flush the TLB so the new permissions take effect before the program
 * runs. */
static void mm_user_set_exec(unsigned long start, unsigned long end) {
    unsigned long p;
    start &= ~0xFFFUL;
    end = ALIGN_UP(end, 0x1000);
    for (p = start; p < end; p += 0x1000) mm_user_pte_update(p, 1);
    __asm__ volatile("mov %%cr3, %%rax; mov %%rax, %%cr3" ::: "rax", "memory");
}

void kallocator_init(void) {
    /* Build the dlmalloc mspace over the fixed kernel heap once. HAVE_MORECORE
     * and HAVE_MMAP are disabled in the backend, so the space is bounded by
     * HEAP_SIZE and an exhausted heap returns 0, exactly like the allocator
     * this replaces. */
    dlmalloc_init();
}

void *kmalloc(unsigned long size) {
    if (size == 0) return 0;
    return dlmalloc_malloc(size);
}

void kfree(void *ptr) {
    if (!ptr) return;
    dlmalloc_free(ptr);
}

void *kcalloc(unsigned long nmemb, unsigned long size) {
    return dlmalloc_calloc(nmemb, size);
}

void *krealloc(void *ptr, unsigned long size) {
    if (!ptr) return kmalloc(size);
    if (size == 0) { kfree(ptr); return 0; }
    return dlmalloc_realloc(ptr, size);
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
#define RD_DATA_MAX    (48UL * 1024 * 1024)

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
 * live contents are carried over to the new one.  The cap is deliberately
 * conservative (48 MB out of the 192 MB heap) to leave room for MiniFS
 * bitmaps, dlmalloc metadata, and transient compression buffers.  Returns
 * 1 on success, 0 when the allocation would leave the heap too small. */
static int ramdisk_reserve(unsigned long want) {
    if (want > RD_DATA_MAX) return 0;
    if (want < RD_DATA_MIN) want = RD_DATA_MIN;
    if (rd_data && rd_cap >= want) return 1;
    char *area = kmalloc(want);
    if (!area) {
        kprintf("ramdisk: cannot allocate %lu KB (heap exhausted)\n",
                want / 1024);
        return 0;
    }
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
int fs_resolve(const char *path, char *out, unsigned cap) {
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

/* Does the directory `dir` (ending in '/') exist? The root always does.
 * Checks the ramdisk first; when MiniFS is mounted, also checks the disk
 * filesystem so that directories created at runtime (asm/, cvm/, tmp/, ...)
 * are reachable via `cd`. */
int fs_dir_exists(const char *dir) {
    unsigned i;
    if (!dir[0]) return 1;
    for (i = 0; i < rd->count; i++)
        if (kstrncmp(rd->files[i].name, dir, kstrlen(dir)) == 0) return 1;
    /* MiniFS fallback: strip the trailing '/' for the resolver. */
    if (minifs_is_mounted()) {
        unsigned dl = (unsigned)kstrlen(dir);
        if (dl > 0 && dl < RAMDISK_FNAME_LEN) {
            char bare[RAMDISK_FNAME_LEN];
            kmemcpy(bare, dir, dl);
            if (bare[dl - 1] == '/') dl--;
            bare[dl] = 0;
            int ino = minifs_resolve_path(bare);
            if (ino >= 0) {
                MiniFSInode st;
                if (minifs_stat(ino, &st) == 0 &&
                    (st.mode & MINIFS_S_IFDIR) == MINIFS_S_IFDIR)
                    return 1;
            }
        }
    }
    return 0;
}

/* Return 1 when the resolved name refers to a directory: a trailing '/'
 * always does, otherwise the name denotes a directory when no exact file
 * entry exists and some entry starts with `<name>/`. */
int fs_is_dir(const char *resolved) {
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

/* Create the MiniFS parent-directory chain for a file whose parent directory
 * does not exist on the ramdisk (the flat ramdisk namespace can only host a
 * name under a directory entry it already carries). Walks every path
 * component before the final file name and mkdirs each missing directory, so
 * a redirect or program write like `asm/_t.s` lands on the disk filesystem
 * instead of failing. Returns 0 on success, -1 on failure. */
static int minifs_mkdir_p(const char *resolved) {
    char dir[RAMDISK_FNAME_LEN];
    unsigned len = 0;
    const char *p = resolved;
    while (*p) {
        const char *start = p;
        while (*p && *p != '/') p++;
        if (*p == 0) break;         /* final component is the file name */
        if (p == start) { p++; continue; }
        unsigned clen = (unsigned)(p - start);
        if (len > 0) dir[len++] = '/';
        if (len + clen + 1 >= sizeof(dir)) return -1;
        kmemcpy(dir + len, start, clen);
        len += clen;
        dir[len] = 0;
        if (minifs_resolve_path(dir) < 0) {
            if (minifs_mkdir(dir, 0755) < 0) return -1;
        }
        p++;
    }
    return 0;
}

KFILE *kfopen(const char *path, const char *mode) {
    char resolved[RAMDISK_FNAME_LEN];
    int want_write;
    if (!fs_resolve(path, resolved, sizeof(resolved))) return 0;
    if (fs_is_dir(resolved)) return 0;      /* never open a directory */
    KFILE *f = kmalloc(sizeof(KFILE));
    if (!f) return 0;
    kmemset(f, 0, sizeof(KFILE));
    f->minifs_ino = -1;
    want_write = (mode[0] == 'w' || mode[0] == 'a');

    f->rf = ramdisk_open(resolved);
    if (!f->rf && want_write) {
        /* Creating a new file on the ramdisk: the parent directory must
         * already exist there (the ramdisk is flat, so a name like
         * save/current/server.ssv can only be created under a real directory).
         * When it does not, the write falls through to MiniFS below, which
         * has real directories. */
        const char *slash = resolved + kstrlen(resolved);
        while (slash > resolved && slash[-1] != '/') slash--;
        int parent_ok = 1;
        if (slash != resolved && slash[-1] == '/') {
            char parent[RAMDISK_FNAME_LEN];
            unsigned plen = (unsigned)(slash - resolved);
            if (plen >= sizeof(parent)) plen = sizeof(parent) - 1;
            kmemcpy(parent, resolved, plen);
            parent[plen] = '/';
            parent[plen + 1] = 0;
            if (!fs_dir_exists(parent)) parent_ok = 0;
        }
        if (parent_ok) {
            f->rf = ramdisk_create(resolved, 0);
            if (!f->rf) { kfree(f); return 0; }
        }
    }
    /* Fall back to MiniFS for reads, and for writes the flat ramdisk cannot
     * host (missing parent directory, or the file already lives on MiniFS).
     * MiniFS is the real directory-capable filesystem: a redirect or program
     * write into `asm/_t.s` or `tmp/x` creates the parent chain on the disk
     * instead of being refused, which is what used to break the lua and
     * MicroPython in-OS test suites when the ramdisk dropped those dirs. */
    if (!f->rf && minifs_is_mounted()) {
        int ino = minifs_resolve_path(resolved);
        if (ino < 0 && kstrchr(resolved, '/')) {
            const char *base = resolved;
            const char *p;
            for (p = resolved; *p; p++)
                if (*p == '/') base = p + 1;
            ino = minifs_resolve_path(base);
        }
        if (want_write && ino < 0) {
            if (minifs_mkdir_p(resolved) == 0)
                ino = minifs_create(resolved, 0644);
        }
        if (ino >= 0) {
            MiniFSInode st;
            if (minifs_stat(ino, &st) >= 0) {
                f->minifs_ino = ino;
                f->minifs_size = st.size;
                if (want_write && mode[0] == 'w' && st.size > 0)
                    minifs_truncate(ino, 0);
            }
        }
    }
    if (!f->rf && f->minifs_ino < 0) { kfree(f); return 0; }
    f->mode = (mode[0] == 'w') ? 1 : ((mode[0] == 'a') ? 2 : 0);
    f->pos = 0;
    if (f->mode == 2) {
        if (f->rf) f->pos = f->rf->size;
        else if (f->minifs_ino >= 0) f->pos = f->minifs_size;
    }
    if (f->mode != 0 && (f->rf || f->minifs_ino >= 0)) {
        if (f->mode == 1 && f->rf && f->rf->size && !ramdisk_resize(f->rf, 0)) { kfree(f); return 0; }
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
    if (f->mode != 0) {
        rc = kfflush(f);
        /* Persist the MiniFS block/inode bitmaps and superblock after a write
         * so a later boot mounts a consistent filesystem (the in-memory
         * bitmaps minifs_alloc_block touches are only flushed by minifs_sync). */
        if (rc == 0 && f->minifs_ino >= 0 && minifs_is_mounted())
            minifs_sync();
    }
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
    if (f->minifs_ino >= 0) {
        if (f->pos >= f->minifs_size) return EOF;
        char c;
        minifs_read(f->minifs_ino, &c, f->pos, 1);
        f->pos++;
        return (unsigned char)c;
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
    if (!f || !size || !n) return 0;
    if (n > 0 && size > 0xFFFFFFFFUL / n) return 0;
    unsigned long total = size * n;
    if (f->is_console) {
        char *b = ptr; unsigned long got = 0;
        while (got < total) { int c = kfgetc(f); if (c == EOF) break; b[got++] = (char)c; }
        return got / size;
    }
    if (f->minifs_ino >= 0) {
        if (f->pos + total > f->minifs_size) total = f->minifs_size - f->pos;
        minifs_read(f->minifs_ino, ptr, f->pos, (unsigned)total);
        f->pos += total;
        return total / size;
    }
    if (!f->rf) return 0;
    if (f->pos + total > f->rf->size) total = f->rf->size - f->pos;
    ramdisk_read(f->rf, ptr, f->pos, (unsigned)total);
    f->pos += total;
    return total / size;
}

unsigned long kfwrite(const void *ptr, unsigned long size, unsigned long n, KFILE *f) {
    if (!f || !size || !n) return 0;
    if (n > 0 && size > 0xFFFFFFFFUL / n) return 0;
    unsigned long bytes = size * n;
    if (f->is_console) {
        const char *b = ptr; unsigned long i;
        for (i = 0; i < bytes; i++) vga_putc(b[i]);
        return n;
    }
    if (f->mode != 1 && f->mode != 2) return 0;
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
    if (!f) return -1;
    unsigned filesize = f->minifs_ino >= 0 ? f->minifs_size : (f->rf ? f->rf->size : 0);
    unsigned base;
    if (whence == 0) base = 0;
    else if (whence == 1) base = f->pos;
    else base = filesize;
    long newp = (long)base + offset;
    if (newp < 0) newp = 0;
    if ((unsigned long)newp > filesize) newp = (long)filesize;
    f->pos = (unsigned)newp;
    return 0;
}

long kftell(KFILE *f) {
    return f ? (long)f->pos : -1;
}

int kfflush(KFILE *f) {
    if (!f || f->mode == 0) return 0;
    /* MiniFS-backed writes go straight to the disk filesystem: the write is
     * buffered in f->wbuf and committed on flush exactly like the ramdisk
     * path, growing the inode as needed (minifs_write updates inode.size). */
    if (f->minifs_ino >= 0) {
        if (f->wbuf && f->wsize > 0) {
            unsigned base = (f->mode == 2) ? (unsigned)(f->pos - f->wsize) : 0;
            if (minifs_write(f->minifs_ino, f->wbuf, base, f->wsize) < 0)
                return -1;
            if (base + f->wsize > f->minifs_size)
                f->minifs_size = base + f->wsize;
            f->wsize = 0;
        }
        return 0;
    }
    if (!f->rf) return 0;
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
    char         name[31];    /* registered stem, copied (never a borrowed ptr) */
    prog_entry_t entry;       /* ET_REL: called directly as a C function */
    void        *proc_entry;  /* ET_EXEC/ET_DYN: Linux _start, run as a process */
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

/* Look up a registered program without creating a slot. Returns 0 when the
 * name is not registered, so the caller can fall through to file resolution
 * instead of polluting the table. */
static KProg *kprog_lookup(const char *name) {
    int i;
    for (i = 0; i < kprog_count; i++)
        if (kstrcmp(kprog_table[i].name, name) == 0) return &kprog_table[i];
    return 0;
}

void k_register_program(const char *name, prog_entry_t entry) {
    KProg *p = kprog_slot(name);
    if (!p) return;
    kstrncpy(p->name, name, sizeof(p->name) - 1);
    p->name[sizeof(p->name) - 1] = 0;
    p->entry = entry; p->proc_entry = 0; p->is_proc = 0;
}

void k_register_process(const char *name, void *proc_entry) {
    KProg *p = kprog_slot(name);
    if (!p) return;
    kstrncpy(p->name, name, sizeof(p->name) - 1);
    p->name[sizeof(p->name) - 1] = 0;
    p->entry = 0; p->proc_entry = proc_entry; p->is_proc = 1;
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
                if (sec_addrs[sym->st_shndx]) {
                    S = (Elf64_Addr)(unsigned long)sec_addrs[sym->st_shndx] + sym->st_value;
                } else {
                    /* Symbol is in a non-alloc section (debug, etc.).
                       Fall back to the raw ELF data buffer so the relocation
                       still produces a plausible address instead of S=small_offset. */
                    S = (Elf64_Addr)((char *)data + shdrs[sym->st_shndx].sh_offset + sym->st_value);
                }
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

            /* Print only suspicious relocations (S too small to be valid) */
            if (S < 0x1000) {
                char rname[ELF_NAME_MAX];
                elf_name_copy(rname, sizeof(rname), strtab, strtab_size, sym->st_name);
                kprintf("rel[%u] t=%u '%s' S=%lx P=%lx addend=%ld\n",
                        j, rtype, rname, (unsigned long)S,
                        (unsigned long)P, (long)relas[j].r_addend);
            }

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
    void *entry = 0;
    const char *entry_names[] = {"go", "kmain", "minigcc_main", "cvm_main", "main", 0};
    int ei;
    for (ei = 0; entry_names[ei] && !entry; ei++) {
        unsigned k;
        for (k = 0; k < symcount; k++) {
            char symname[ELF_NAME_MAX];
            elf_name_copy(symname, sizeof(symname), strtab, strtab_size,
                          symtab[k].st_name);
            if (kstrcmp(symname, entry_names[ei]) != 0) continue;
            if (symtab[k].st_shndx == SHN_UNDEF || symtab[k].st_shndx >= shnum) continue;
            if (!sec_addrs[symtab[k].st_shndx]) {
                kprintf("load: skip '%s' in non-alloc sec %d\n", symname, symtab[k].st_shndx);
                continue;
            }
            entry = (char *)sec_addrs[symtab[k].st_shndx] + symtab[k].st_value;
            break;
        }
    }

    if (!entry) {
        kprintf("load: NO ENTRY. symbols:\n");
        for (unsigned k = 0; k < symcount && k < 20; k++) {
            char sn[ELF_NAME_MAX];
            elf_name_copy(sn, sizeof(sn), strtab, strtab_size, symtab[k].st_name);
            int alloc = (symtab[k].st_shndx < shnum && sec_addrs[symtab[k].st_shndx]) ? 1 : 0;
            kprintf("  [%u] '%s' sec=%u val=%lu alloc=%d\n",
                    k, sn, symtab[k].st_shndx, symtab[k].st_value, alloc);
        }
        elf_load_fail(base, sec_addrs, "no valid entry point");
        return 0;
    }
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

/* Anonymous mmap regions, tracked so munmap can reclaim them for reuse.  The
   cursor alone only ever moves down, so a program that unmaps and re-allocates
   a working set (Quake 2 across level changes) would drain the whole user
   window until mmap fails with ENOMEM.  Two tables: mmap_used holds the live
   allocations (munmap reclaims only a region present here, so the stack or
   arbitrary program memory is never handed back), mmap_free holds reclaimed
   regions that a later mmap reuses.  All entries are page-aligned and lie at
   or above user_mmap_cur, which itself never drops below g_brk, so neither a
   live nor a reused chunk can overlap the heap. */
#define MMAP_MAX 4096
struct mmap_ent {
    unsigned long base;
    unsigned long len;
};
static struct mmap_ent mmap_used[MMAP_MAX];
static struct mmap_ent mmap_free[MMAP_MAX];
static int mmap_used_n;
static int mmap_free_n;

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
    if (size < sizeof(Elf64_Ehdr)) { kprintf("exec: too small %u\n", size); return 0; }
    if (e->e_ident[0] != 0x7F || e->e_ident[1] != 'E' ||
        e->e_ident[2] != 'L'  || e->e_ident[3] != 'F') { kprintf("exec: bad magic\n"); return 0; }
    if (e->e_machine != EM_X86_64) { kprintf("exec: bad machine %d\n", e->e_machine); return 0; }
    if (e->e_type != ET_EXEC && e->e_type != ET_DYN) { kprintf("exec: bad type %d\n", e->e_type); return 0; }

    if (e->e_phentsize < sizeof(Elf64_Phdr)) { kprintf("exec: phentsize %d\n", e->e_phentsize); return 0; }
    if (e->e_phoff > size) { kprintf("exec: phoff too big %lu > %u\n", e->e_phoff, size); return 0; }
    if (e->e_phnum > (size - e->e_phoff) / e->e_phentsize) { kprintf("exec: phnum overflow\n"); return 0; }
    if (e->e_phnum > ELF_MAX_SEGMENTS) { kprintf("exec: too many segments %d\n", e->e_phnum); return 0; }

    unsigned long base = (e->e_type == ET_DYN) ? USER_LOAD_BASE : 0;

    Elf64_Phdr *ph = (Elf64_Phdr *)((char *)data + e->e_phoff);
    struct exec_range xr[ELF_MAX_SEGMENTS];
    unsigned nxr = 0;
    unsigned long max_end = 0;
    unsigned i;
    for (i = 0; i < e->e_phnum; i++) {
        if (ph[i].p_type != PT_LOAD) continue;
        if (ph[i].p_vaddr > USER_LOAD_END - base) { kprintf("exec: vaddr %lx too big\n", ph[i].p_vaddr); return 0; }
        unsigned long dst = base + ph[i].p_vaddr;
        if (dst < USER_LOAD_BASE || dst >= USER_LOAD_END) {
            kprintf("exec: seg %d dst %lx outside user window\n", i, dst);
            return 0;
        }
        if (ph[i].p_memsz > USER_LOAD_END - dst) { kprintf("exec: memsz overflow\n"); return 0; }
        if (ph[i].p_filesz > USER_LOAD_END - dst) { kprintf("exec: filesz overflow\n"); return 0; }
        if (ph[i].p_offset > size || ph[i].p_filesz > size - ph[i].p_offset)
            { kprintf("exec: seg data beyond file\n"); return 0; }
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
    if (max_end == 0) { kprintf("exec: no loadable segments\n"); return 0; }

    /* Clear NX on the executable segments before applying relocations, so
     * IRELATIVE resolvers inside them can run, then reload the TLB. */
    for (i = 0; i < nxr; i++)
        mm_user_set_exec(xr[i].start, xr[i].end);

    apply_exec_relocs(data, size, base, xr, nxr);

    g_brk       = ALIGN_UP(max_end, 0x1000);
    g_brk_limit = USER_BRK_END;
    user_mmap_cur = USER_BRK_END;
    /* Reserve the graphics back-buffer span from both allocators so a
     * memory-hungry program (Quake 2) cannot grow its brk heap or its mmap
     * region over the pages the kernel maps at DOOM_BACKBUF_ADDR; rendering
     * into a glibc-allocated chunk there would corrupt the heap.  Both carve
     * below the cap, so cap each at the buffer's base to keep the buffer
     * itself (which sits just above) untouched. */
    if (DOOM_BACKBUF_ADDR < g_brk_limit) g_brk_limit = DOOM_BACKBUF_ADDR;
    if (DOOM_BACKBUF_ADDR < user_mmap_cur) user_mmap_cur = DOOM_BACKBUF_ADDR;
    /* The linear framebuffer (FB_ADDR) and the Nuklear back-buffer
     * (NK_BACKBUF_ADDR) are pinned in the reserved tail ABOVE the DOOM
     * back-buffer (see mm_setup_protections), so this single brk cap at
     * DOOM_BACKBUF_ADDR keeps every pinned mapping out of a program's heap. */
    mmap_used_n = 0;
    mmap_free_n = 0;
    /* Loader status is shell text, never the command's output: it must not
     * pollute a `> file` capture. */
    {
        int was = redirect_suspend();
        kprintf("exec: loaded at %lx entry %lx brk %lx\n", base + USER_LOAD_BASE, base + e->e_entry, g_brk);
        redirect_resume(was);
    }
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

/* Called from the ISR exception handler when a ring-3 user program faults.
 * Sets exec_exit_code and longjmps back to k_exec_user's setjmp point so
 * the parent interpreter gets EFAULT instead of the whole machine hanging. */
void k_user_fault_return(void) {
    exec_exit_code = EFAULT;
    /* Restore kernel data segments — the fault may have left user selectors
     * loaded in DS/ES/FS/GS. */
    __asm__ volatile(
        "mov %[kdata], %%ax\n"
        "mov %%ax, %%ds\n"
        "mov %%ax, %%es\n"
        "mov %%ax, %%fs\n"
        "mov %%ax, %%gs\n"
        :: [kdata] "i"(GDT64_DATA_SEL)
        : "ax", "memory");
    wrmsr(MSR_FSBASE, 0);
    wrmsr(MSR_GSBASE, 0);
    klongjmp(&exec_return, 1);
}


/* ---- File descriptor table for open/read/write/close -------------------- */

#define KFD_MAX 32
static KFILE *kfd_table[KFD_MAX];

static int console_getc(void); /* defined in the shell section below */


/* ---- Linux x86-64 syscall dispatcher ------------------------------------ */

struct kiovec { const char *iov_base; unsigned long iov_len; };

#define SYSCALL_TRACE 0

static long ksyscall_dispatch(long n, long a1, long a2, long a3, long a4, long a5, long a6);
static int k_syscall_spawn(const char *path, const char *redirect, int child_argc, const char **child_argv);

/* ---- PIT-calibrated TSC for SYS_TIME (syscall 204) ----
 * PIT channel 2 one-shot measures real TSC ticks per millisecond
 * so the timer works regardless of the host CPU frequency. */
static unsigned long tsc_per_ms;
static unsigned long tsc_base_ms;

static unsigned long ktime_rdtsc(void) {
    unsigned int lo, hi;
    __asm__ volatile("rdtsc" : "=a"(lo), "=d"(hi));
    return ((unsigned long)hi << 32) | lo;
}

static void ktime_init(void) {
    unsigned long t0, t1;
    /* channel 2, one-shot, lsb+msb, binary */
    outb(0x61, (unsigned char)((inb(0x61) & 0x0F) | 0x01));
    outb(0x43, 0xB0);
    outb(0x42, 0x96);  /* count = 0x0496 = 1174 → ~1 ms at 1.193 MHz */
    outb(0x42, 0x04);
    t0 = ktime_rdtsc();
    while (!(inb(0x61) & 0x20));   /* wait for channel 2 output high */
    t1 = ktime_rdtsc();
    outb(0x61, (unsigned char)(inb(0x61) & 0x0F));
    tsc_per_ms  = t1 - t0;
    tsc_base_ms = t0;
}

unsigned long ktime_ms(void) {
    if (!tsc_per_ms) ktime_init();
    return (ktime_rdtsc() - tsc_base_ms) / tsc_per_ms;
}

long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6);
long syscall_trace_enabled(void);
void syscall_trace_set(int on);

static int s_trace_enabled = SYSCALL_TRACE;

long syscall_trace_enabled(void) { return s_trace_enabled; }
void syscall_trace_set(int on) { s_trace_enabled = on ? 1 : 0; }

/* Syscall numbers that are poll/clock reads: tracing them floods the console
 * (SYS_TIME is called inside every pacing spin loop), which made `trace on`
 * turn an interactive program into a 100 ms-per-syscall crawl.  Other syscalls
 * are traced one-to-one so a short program's full dialogue stays visible. */
#define SYS_NOISY_TIME   204
#define SYS_NOISY_KBD    205
#define SYS_NOISY_MOUSE  219

static int trace_is_noisy(long n) {
    return n == SYS_NOISY_TIME || n == SYS_NOISY_KBD || n == SYS_NOISY_MOUSE;
}

long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6) {
    long ret;
    int show = s_trace_enabled && !trace_is_noisy(n);
    if (show)
        kprintf("syscall %d(%d, %d, %d, %d, %d, %d)",
                (int)n, (int)a1, (int)a2, (int)a3, (int)a4, (int)a5, (int)a6);
    ret = ksyscall_dispatch(n, a1, a2, a3, a4, a5, a6);
    if (show) kprintf(" = %d\n", (int)ret);
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
    /* Window-manager close: when the WM armed a close while a graphics
     * program owned the display, the program's next syscall terminates it on
     * the child's own stack (never from the ISR). Exit code 130 = SIGINT-like
     * user request. */
    if (wm_close_pending()) {
        wm_clear_close();
        exec_exit_code = 130;
        klongjmp(&exec_return, 1);
        return 0;
    }
    switch (n) {
    case 0: { /* read */
        char *buf = (char *)a2; long cnt = a3, i = 0;
        if (cnt > 0 && !user_range_ok((unsigned long)buf, (unsigned long)cnt)) {
            kprintf("READ: EFAULT fd=%ld buf=%lx cnt=%ld\n", a1, a2, a3);
            return EFAULT;
        }
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
        if (a1 >= 3 && a1 < KFD_MAX && kfd_table[a1]) {
            return (long)kfread(buf, 1, (unsigned long)cnt, kfd_table[a1]);
        }
        kprintf("READ: bad fd=%ld\n", a1);
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
        if (!user_str_ok((unsigned long)path, RAMDISK_FNAME_LEN)) {
            return EFAULT;
        }
        for (fd = 3; fd < KFD_MAX; fd++) if (!kfd_table[fd]) break;
        if (fd >= KFD_MAX) return -24;
        KFILE *f = kfopen(path, mode);
        if (!f) {
            return -2;
        }
        kfd_table[fd] = f;
        return fd;
    }
    case 3: /* close */
        if (a1 >= NET_FD_BASE) return net_sys_close(a1);
        if (a1 >= 3 && a1 < KFD_MAX && kfd_table[a1]) {
            kfclose(kfd_table[a1]); kfd_table[a1] = 0;
        }
        return 0;
    case 8: { /* lseek */
        if (a1 >= 3 && a1 < KFD_MAX && kfd_table[a1]) {
            kfseek(kfd_table[a1], a2, (int)a3);
            long pos = kftell(kfd_table[a1]);
            return pos;
        }
        return -9;
    }
    case 12: { /* brk */
        unsigned long addr = (unsigned long)a1;
        if (addr == 0) return (long)g_brk;
        if (addr >= USER_LOAD_BASE && addr <= g_brk_limit
            && addr <= user_mmap_cur)     /* don't grow into mmap region */
            g_brk = addr;
        return (long)g_brk;
    }
    case 9: { /* mmap (anonymous only).  Reuse a reclaimed region first so the
                 cursor is not drained by a free/reallocate working set; only
                 carve fresh space below the cursor, never below g_brk. */
        unsigned long len = (unsigned long)a2;
        unsigned long n = ALIGN_UP(len ? len : 1, 0x1000);
        if (n > user_mmap_cur - USER_LOAD_BASE) return -12;
        for (int i = 0; i < mmap_free_n; i++) {
            if (mmap_free[i].len < n) continue;
            unsigned long addr = mmap_free[i].base + mmap_free[i].len - n;
            if (mmap_used_n >= MMAP_MAX) continue;   /* can't track; skip reuse */
            mmap_used[mmap_used_n].base = addr;
            mmap_used[mmap_used_n].len  = n;
            mmap_used_n++;
            if (mmap_free[i].len == n) {
                mmap_free[i] = mmap_free[--mmap_free_n];
            } else {
                mmap_free[i].len -= n;                /* remainder stays at the bottom */
            }
            return (long)addr;
        }
        if (user_mmap_cur - n < g_brk) return -12;  /* would overlap brk */
        user_mmap_cur -= n;
        if (mmap_used_n < MMAP_MAX) {
            mmap_used[mmap_used_n].base = user_mmap_cur;
            mmap_used[mmap_used_n].len  = n;
            mmap_used_n++;
        }
        return (long)user_mmap_cur;
    }
    case 11: { /* munmap: reclaim only a region this kernel allocated */
        unsigned long base = (unsigned long)a1;
        unsigned long n = ALIGN_UP((unsigned long)a2, 0x1000);
        if (n == 0) return 0;
        for (int i = 0; i < mmap_used_n; i++) {
            if (mmap_used[i].base != base || n > mmap_used[i].len) continue;
            if (mmap_free_n < MMAP_MAX) {
                mmap_free[mmap_free_n].base = mmap_used[i].base;
                mmap_free[mmap_free_n].len  = mmap_used[i].len;
                mmap_free_n++;
            }
            mmap_used[i] = mmap_used[--mmap_used_n];
            return 0;
        }
        return 0;
    }
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
    case 24: yield(); return 0;   /* sched_yield */
    case 39: return 1;   /* getpid */
    case 57: return 0;   /* fork: stub, returns 0 (child) for now */
    case 58: return 0;   /* vfork: stub */
    case 59: { /* execve: stub - just run the program if loaded */
        return 0;
    }
    case 60: case 231:   /* exit / exit_group */
        if (proc_count > 1) {
            do_exit((int)a1);
            return 0;
        }
        exec_exit_code = (int)a1;
        klongjmp(&exec_return, 1);
        return 0; /* unreachable */
    case 61: return do_waitpid((int)a1);   /* wait4 / waitpid */
    case 62: return do_kill((int)a1);      /* kill */
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
    case 204: { /* SYS_TIME: PIT-calibrated elapsed milliseconds */
        return (long)ktime_ms();
    }
    case 205: { /* SYS_KBD: read PS/2 scancode without blocking */
        if (kbd_raw_mode) {
            /* Raw mode (DOOM): drain queue, then poll PS/2 directly */
            if (kbd_raw_head != kbd_raw_tail) {
                unsigned char c = kbd_raw[kbd_raw_head];
                kbd_raw_head = (kbd_raw_head + 1) % KBD_RAW_LEN;
                return (long)c;
            }
            if (!kbd_available()) return -1;
            unsigned char sc;
            __asm__ volatile("inb $0x60, %0" : "=a"(sc));
            /* E0 prefix: store flag, return 0xE0 so reader sees it */
            if (sc == KEY_E0) { kbd_e0 = 1; return 0xE0; }
            if (kbd_e0) {
                kbd_e0 = 0;
                return (long)sc;  /* raw scancode with make/break bit */
            }
            return (long)sc;
        }
        if (kbd_q_empty()) return -1;
        return kbd_q_pop();
    }
    case 207: { /* SYS_KBD_RAW: enable/disable raw keyboard mode */
        kbd_raw_mode = (int)a1;
        /* Flush queues on mode switch */
        kbd_q_head = kbd_q_tail = 0;
        kbd_raw_head = kbd_raw_tail = 0;
        return 0;
    }
    case 208: { /* SYS_VGA_MODE: tell kernel a graphics program owns the display */
        vga_mode13h = (int)a1;
        if (a1) graphics_program_ran = 1;
        /* While a graphics program owns the display the idle loop never runs,
         * so the desktop pointer is drawn by the frame composites instead.
         * Toggle that mode here. */
        vga_fb_set_gfx_mode((int)a1);
        return 0;
    }
    case 209: { /* SYS_PCSPK_INIT */
        pcspk_init();
        return 0;
    }
    case 210: { /* SYS_PCSPK_TONE: play PC speaker tone at freq Hz (0=off).
                 * Kept on the PC speaker so Doom's note player keeps its
                 * original distinguishable sound.  Real PCM audio (SB16) is
                 * opt-in through SYS_SB16_PCM_OPEN/SUBMIT (221/222). */
        pcspk_tone((unsigned)a1);
        return 0;
    }
    case 211: { /* SYS_DOOM_FRAME: composite the graphics back-buffer window */
        vga_fb_blit_gfx_window();
        return 0;
    }
    case 212: { /* SYS_RTC: read CMOS RTC time-of-day (hour, minute, second) */
        int *hp = (int *)(unsigned long)a1;
        int *mp = (int *)(unsigned long)a2;
        int *sp = (int *)(unsigned long)a3;
        if (!user_range_ok((unsigned long)a1, sizeof(int)) ||
            !user_range_ok((unsigned long)a2, sizeof(int)) ||
            !user_range_ok((unsigned long)a3, sizeof(int)))
            return EFAULT;
        int h, m, s;
        if (!rtc_read_tod(&h, &m, &s)) return -5; /* EIO */
        *hp = h; *mp = m; *sp = s;
        return 0;
    }
    case 213: { /* SYS_FB_INFO: return framebuffer geometry (w, h, pitch) */
        int *wp = (int *)(unsigned long)a1;
        int *hp = (int *)(unsigned long)a2;
        int *pp = (int *)(unsigned long)a3;
        if (!user_range_ok((unsigned long)a1, sizeof(int)) ||
            !user_range_ok((unsigned long)a2, sizeof(int)) ||
            !user_range_ok((unsigned long)a3, sizeof(int)))
            return EFAULT;
        *wp = fb_width; *hp = fb_height; *pp = fb_pitch;
        return 0;
    }
    case 214: { /* SYS_PCSPK_VOL: get/set speaker volume (0..100, -1=query) */
        int v = (int)a1;
        if (v < 0) return (long)pcspk_get_volume();
        if (v > 100) v = 100;
        pcspk_set_volume((unsigned)v);
        return (long)pcspk_get_volume();
    }
    case 215: { /* SYS_SPAWN: run a ramdisk program from inside the OS.
                  * args: path(a1), redirect(a2), argc(a3), argv(a4) */
        const char *path = (const char *)a1;
        if (!user_str_ok((unsigned long)path, RAMDISK_FNAME_LEN)) return EFAULT;
        return k_syscall_spawn(path, (const char *)a2, (int)a3,
                               (const char **)a4);
    }
    case 216: { /* MiniOS: LZ4 compress into a MiniFS size-prefixed block.
                 * args: src(a1), src_len(a2), dst(a3), dst_cap(a4).  Mirrors
                 * minifs_compress: refuses unless the stream is strictly
                 * shorter than the input, stores the original size little-
                 * endian at dst[0..3] and returns the block length. */
        char *src = (char *)a1;
        char *dst = (char *)a3;
        int src_len = (int)a2;
        int dst_cap = (int)a4;
        int ret;
        if (src_len <= 0 || dst_cap <= 4) return 0;
        if (!user_range_ok((unsigned long)src, (unsigned long)src_len)) return EFAULT;
        if (!user_range_ok((unsigned long)dst, (unsigned long)dst_cap)) return EFAULT;
        ret = LZ4_compress_default(src, dst + 4, src_len, dst_cap - 4);
        if (ret <= 0 || ret >= src_len) return 0;
        dst[0] = (char)(src_len & 255);
        dst[1] = (char)((src_len >> 8) & 255);
        dst[2] = (char)((src_len >> 16) & 255);
        dst[3] = (char)((src_len >> 24) & 255);
        return ret + 4;
    }
    case 217: { /* MiniOS: LZ4 decompress a MiniFS size-prefixed block.
                 * args: src(a1), src_len(a2), dst(a3), dst_cap(a4).  Mirrors
                 * minifs_decompress: reads the little-endian original size,
                 * refuses if it exceeds dst_cap and returns the decoded
                 * length only when it matches the declared size exactly. */
        char *src = (char *)a1;
        char *dst = (char *)a3;
        int src_len = (int)a2;
        int dst_cap = (int)a4;
        unsigned int orig;
        int ret;
        if (src_len <= 4) return 0;
        if (!user_range_ok((unsigned long)src, (unsigned long)src_len)) return EFAULT;
        orig = (unsigned int)((unsigned char)src[0] | ((unsigned char)src[1] << 8) |
                              ((unsigned char)src[2] << 16) | ((unsigned char)src[3] << 24));
        if (orig > (unsigned int)dst_cap) return 0;
        if (dst_cap > 0 && !user_range_ok((unsigned long)dst, (unsigned long)dst_cap)) return EFAULT;
        ret = LZ4_decompress_safe(src + 4, dst, src_len - 4, dst_cap);
        if (ret < 0 || (unsigned int)ret != orig) return 0;
        return ret;
    }
    case 219: { /* SYS_MOUSE: return mouse state (x, y, buttons, wheel) into a
                 * user int[4]. The wheel is a running delta consumed on read,
                 * exactly like the desktop's vga_fb_mouse_tick resets it. */
        int *m = (int *)(unsigned long)a1;
        if (!user_range_ok((unsigned long)a1, 4 * sizeof(int))) return EFAULT;
        m[0] = mouse_state.x;
        m[1] = mouse_state.y;
        m[2] = mouse_state.buttons;
        m[3] = mouse_state.wheel;
        mouse_state.wheel = 0;
        return 0;
    }
    case 220: { /* SYS_NK_FRAME: composite the Nuklear UI back-buffer as a
                 * titled window on the desktop, like SYS_DOOM_FRAME. a1, when
                 * non-null, receives the window content origin (int[2] =
                 * desktop x, y) so the app can translate mouse coordinates. */
        vga_fb_blit_nk_window();
        if (a1) {
            int *o = (int *)(unsigned long)a1;
            if (!user_range_ok((unsigned long)a1, 2 * sizeof(int))) return EFAULT;
            o[0] = nk_win_x;
            o[1] = nk_win_y + FONT_H;
        }
        return 0;
    }
    case 221: { /* SYS_SB16_PCM_OPEN: switch the SB16 sink to PCM streaming
                 * (a1=1) or back to tone/silence (a1=0).  Returns 1 when an
                 * SB16 is present so a ring-3 renderer can detect it. */
        if (a1) sb16_pcm_open();
        else    sb16_pcm_close();
        return sb16_present() ? 1 : 0;
    }
    case 222: { /* SYS_SB16_PCM_SUBMIT: queue a ring-3 PCM buffer (8-bit
                 * unsigned mono). a1=user buf, a2=len. Validated against the
                 * user window; returns -1 on no-SB16/full/oversize. */
        const unsigned char *pcm = (const unsigned char *)a1;
        long len = a2;
        if (len < 0) return -EFAULT;
        if (!user_range_ok((unsigned long)a1, (unsigned long)len)) return -EFAULT;
        return sb16_pcm_submit(pcm, (unsigned)len);
    }
    case 224: { /* SYS_SB16_PUMP: drain the kernel audio ring into DMA slots.
                 * A ring-3 renderer can call this to force an immediate flush
                 * after a burst of submits, reducing latency on the fast path.
                 * No arguments; returns 0. */
        sb16_pump();
        return 0;
    }
    case 206: { /* SYS_PALETTE: load 256-color VGA DAC palette (768 bytes) */
        unsigned char *pal = (unsigned char *)a1;
        if (!user_range_ok((unsigned long)a1, 768)) return -EFAULT;
        /* VGA DAC: set index 0 then write 768 bytes (6-bit per color) */
        outb(0x3C8, 0);
        for (int i = 0; i < 768; i++) {
            outb(0x3C9, pal[i] >> 2);
        }
        return 0;
    }
    case 5: { /* fstat: minimal stub for glibc static */
        /* struct stat on x86-64 is 144 bytes, zero it out */
        unsigned long *st = (unsigned long *)a2;
        if (!user_range_ok((unsigned long)a2, 144)) return EFAULT;
        for (int i = 0; i < 18; i++) st[i] = 0;
        /* st_mode at offset 24 (uint32): S_IFCHR|0666 for consoles, S_IFREG|0666 for files */
        if (a1 == 0 || a1 == 1 || a1 == 2) {
            ((unsigned int *)(unsigned long)a2)[6] = 0020666; /* S_IFCHR | 0666 */
        } else {
            ((unsigned int *)(unsigned long)a2)[6] = 0100666; /* S_IFREG | 0666 */
            if (a1 >= 3 && a1 < KFD_MAX && kfd_table[a1]) {
                KFILE *kf = kfd_table[a1];
                if (kf->rf)
                    ((unsigned long *)(unsigned long)a2)[6] = (unsigned long)kf->rf->size;
                else if (kf->minifs_ino >= 0)
                    ((unsigned long *)(unsigned long)a2)[6] = (unsigned long)kf->minifs_size;
            }
        }
        return 0;
    }
    case 10: /* mprotect: no-op (no MMU-based protection per-page for user) */
        return 0;
    case 13: /* rt_sigaction: no-op (no signal delivery in miniOS) */
        return 0;
    case 14: /* rt_sigprocmask: no-op (signals are not blocked/delivered) */
        return 0;
    case 186: /* gettid: single-threaded, so tid == pid */
        return 1;
    case 234: { /* tgkill: deliver a signal to a thread.  Only default
                   disposition is modelled: a signal whose default action is
                   to terminate (SIGABRT/SIGSEGV/...) exits the process so
                   glibc's abort() terminates cleanly instead of faulting. */
        int sig = (int)a3;
        static const int fatal[] = {1,2,3,4,5,6,7,8,9,11,13,14,15};
        if (sig <= 0) return -22;
        for (unsigned _i = 0; _i < sizeof(fatal)/sizeof(fatal[0]); _i++)
            if (sig == fatal[_i]) {
                if (proc_count > 1) {
                    do_exit(128 + sig);
                    return 0;
                }
                exec_exit_code = 128 + sig;
                klongjmp(&exec_return, 1);
                return 0; /* unreachable */
            }
        return 0; /* ignored/disposition not fatal */
    }
    case 87: { /* unlink: delete a ramdisk or MiniFS file */
        const char *path = (const char *)a1;
        if (!user_str_ok((unsigned long)path, RAMDISK_FNAME_LEN)) return EFAULT;
        char resolved[RAMDISK_FNAME_LEN];
        if (!fs_resolve(path, resolved, sizeof(resolved))) return -36;
        if (fs_is_dir(resolved)) return -21;
        RDFile *f = ramdisk_open(resolved);
        if (f) { ramdisk_delete(f); return 0; }
        if (minifs_is_mounted() && minifs_unlink(resolved) == 0) return 0;
        return -2;   /* ENOENT */
    }
    case 74: /* flock: no-op */
        return 0;
    case 21: { /* access: check if the file exists on the ramdisk or MiniFS */
        const char *path = (const char *)a1;
        if (!user_str_ok((unsigned long)path, RAMDISK_FNAME_LEN)) return EFAULT;
        char resolved[RAMDISK_FNAME_LEN];
        if (!fs_resolve(path, resolved, sizeof(resolved))) return -2; /* ENOENT */
        RDFile *f = ramdisk_open(resolved);
        if (f) return 0;
        if (minifs_is_mounted()) {
            int ino = minifs_resolve_path(resolved);
            if (ino < 0 && kstrchr(resolved, '/')) {
                const char *base = resolved;
                const char *p;
                for (p = resolved; *p; p++)
                    if (*p == '/') base = p + 1;
                ino = minifs_resolve_path(base);
            }
            if (ino >= 0) return 0;
        }
        return -2;
    }
    case 89: { /* readlink: always returns EINVAL (no symlinks in miniOS) */
        (void)a1; (void)a2; (void)a3;
        return -22; /* EINVAL */
    }
    case 96: /* gettimeofday: return approximate time via rdtsc */
        if (a1) {
            unsigned long *tv = (unsigned long *)a1;
            if (!user_range_ok((unsigned long)a1, 2 * sizeof(unsigned long))) return EFAULT;
            unsigned long lo = 0, hi = 0;
            __asm__ volatile("rdtsc" : "=a"(lo), "=d"(hi));
            unsigned long tsc = ((unsigned long)hi << 32) | lo;
            unsigned long ms = tsc / 1000000UL;
            tv[0] = ms / 1000;  /* seconds */
            tv[1] = (ms % 1000) * 1000; /* microseconds */
        }
        return 0;
    case 267: /* statx: not implemented, return -ENOENT */
        return -2;
    case 273: /* set_mempolicy: no-op */
        return 0;
    case 301: /* set_robust_list: no-op */
        return 0;
    case 302: /* prlimit64: no-op */
        return 0;
    case 318: { /* getrandom: fill buffer with RDTSC-based pseudo-random */
        unsigned char *buf = (unsigned char *)a1;
        unsigned long cnt = a2;
        if (cnt > 0 && !user_range_ok((unsigned long)buf, cnt)) return EFAULT;
        unsigned long lo = 0, hi = 0;
        for (unsigned long i = 0; i < cnt; i++) {
            if ((i & 7) == 0) {
                __asm__ volatile("rdtsc" : "=a"(lo), "=d"(hi));
            }
            buf[i] = (unsigned char)((lo >> (8 * (i & 7))) ^ (hi & 0xFF) ^ i);
        }
        return (long)cnt;
    }
    case 334: /* rseq: not supported, libc handles -1 gracefully */
        return -1;
    case 79: { /* getcwd: return the shell cwd into a user buffer */
        char *buf = (char *)a1;
        unsigned long sz = (unsigned long)a2;
        if (!buf || sz == 0) return -22; /* EINVAL */
        if (!user_range_ok((unsigned long)buf, sz)) return EFAULT;
        unsigned long cwd_len = (unsigned long)kstrlen(fs_cwd);
        if (sz < cwd_len + 1) return -34; /* ERANGE */
        for (unsigned long i = 0; i <= cwd_len; i++) buf[i] = fs_cwd[i];
        return (long)(cwd_len + 1);
    }
    case 262: { /* newfstatat: stat via the unified filesystem */
        const char *path = (const char *)a2;
        unsigned long *st = (unsigned long *)a3;
        if (!user_str_ok((unsigned long)path, RAMDISK_FNAME_LEN)) return EFAULT;
        if (!user_range_ok((unsigned long)st, 144)) return EFAULT;
        for (int i = 0; i < 18; i++) st[i] = 0;
        char resolved[RAMDISK_FNAME_LEN];
        if (!fs_resolve(path, resolved, sizeof(resolved))) return -2; /* ENOENT */
        if (fs_is_dir(resolved)) {
            ((unsigned int *)(unsigned long)st)[5] = 0040755; /* S_IFDIR | 0755 */
        } else {
            RDFile *rf = ramdisk_open(resolved);
            if (!rf) {
                /* try minifs */
                if (minifs_is_mounted()) {
                    int ino = minifs_resolve_path(resolved);
                    MiniFSInode mi;
                    if (ino >= 0 && minifs_stat(ino, &mi) >= 0) {
                        ((unsigned int *)(unsigned long)st)[5] = 0100666; /* S_IFREG | 0666 */
                        ((unsigned long *)(unsigned long)st)[6] = (unsigned long)mi.size;
                        return 0;
                    }
                }
                return -2; /* ENOENT */
            }
            ((unsigned int *)(unsigned long)st)[5] = 0100666; /* S_IFREG | 0666 */
            ((unsigned long *)(unsigned long)st)[6] = (unsigned long)rf->size;
        }
        return 0;
    }
    case 223: { /* SYS_Q2G_SET_TITLE: set graphics window title */
        const char *t = (const char *)(unsigned long)a1;
        if (!t) return EFAULT;
        if (!user_range_ok((unsigned long)t, 1)) return EFAULT;
        extern const char *gfx_win_title;
        static char title_buf[32];
        int i;
        for (i = 0; i < 31 && ((const char *)t)[i]; i++)
            title_buf[i] = ((const char *)t)[i];
        title_buf[i] = 0;
        gfx_win_title = title_buf;
        return 0;
    }
    default:
        kprintf("UNIMPL SYSCALL %ld\n", n);
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
        if (l > (unsigned long)(p - sbase)) return 0;
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

/* SYS_SPAWN (215): run a ramdisk program from inside the OS.
 * Saves the parent's user window, loads the child, runs it via k_exec_user,
 * and restores the parent on return. ET_REL children run at ring 0 via
 * k_run_rel; ET_EXEC/ET_DYN children run at ring 3 via k_exec_user.
 *
 * KNOWN LIMITATION (pre-existing): SYS_SPAWN of an ET_EXEC/ET_DYN child from
 * a ring-3 interpreter (lua/micropython) must save the parent's user window,
 * whose full span cannot fit in the kernel heap alongside the ramdisk, and the
 * klongjmp/syscall-stack unwind after the child exits is not robust in the
 * single shared address space.  Such a spawn therefore returns -EFAULT cleanly
 * (the interpreter gets nil) rather than running or crashing.  This is why the
 * in-OS interpreter suites exercise only the ET_REL toolchain (minigcc/ld);
 * ET_EXEC tools (lzss/lz4/aes/json/freedom) are run by the shell, not from an
 * interpreter.
 *
 * The parent window is saved to a swap area on the IDE disk instead of
 * kmalloc'ing a buffer in the kernel heap.  The swap area lives at the
 * end of the disk (last SWAP_MAX_SECTORS sectors) and is laid out as:
 *
 *   Sectors 0 .. nchunks-1: chunk data (each SWAP_CHUNK_SECTORS sectors)
 *     First 4 bytes: compressed_sz (u32 LE, 0 = stored raw)
 *     Rest: LZ4 compressed or raw data
 *   Last sector: header
 *     [0..3]   magic 0x53574150 ("SWAP")
 *     [4..7]   window_sz (u32 LE, original bytes)
 *     [8..11]  nchunks (u32 LE)
 *
 * LZ4 compression uses two static BSS buffers (no heap allocation).
 * A 64 KB chunk compresses to ~30-50% of its size for typical interpreter
 * windows, so the disk I/O is proportionally smaller. */
#define SWAP_CHUNK_RAW     65536   /* 64 KB raw data per chunk             */
#define SWAP_CHUNK_SECTORS 128     /* 64 KB / 512 = 128 sectors per chunk  */
#define SWAP_HDR_SECTORS   1       /* header occupies the last sector       */
#define SWAP_MAX_SECTORS   131072  /* 64 MB total swap area                 */
#define SWAP_MAGIC         0x53574150  /* "SWAP" */

/* Two static BSS buffers for LZ4 compression — no heap allocation needed.
 * swap_buf_raw: holds one raw 64 KB chunk from the user window.
 * swap_buf_cmp: holds the LZ4 compressed output (compressBound(64K) ≈ 66 KB). */
static unsigned char swap_buf_raw[SWAP_CHUNK_RAW];
static unsigned char swap_buf_cmp[SWAP_CHUNK_RAW + 1024];

/* Compute the swap base LBA (last SWAP_MAX_SECTORS sectors of the disk). */
static unsigned long swap_lba(void) {
    unsigned int total = ide_total_sectors();
    if (total <= SWAP_MAX_SECTORS) return 0;
    return (unsigned long)(total - SWAP_MAX_SECTORS);
}

/* Write the parent's user window to the swap area on disk, compressed
 * with LZ4 in 64 KB chunks.  Returns 1 on success, 0 on failure.
 * No heap allocation is used — the two static BSS buffers are enough. */
static int swap_out(unsigned long window_sz) {
    unsigned long slba = swap_lba();
    if (!slba) return 0;
    unsigned long nchunks = (window_sz + SWAP_CHUNK_RAW - 1) / SWAP_CHUNK_RAW;
    /* Sanity: swap area must be large enough for header + chunks. */
    if (nchunks * SWAP_CHUNK_SECTORS + SWAP_HDR_SECTORS > SWAP_MAX_SECTORS)
        return 0;

    unsigned long data_lba = slba;
    for (unsigned long i = 0; i < nchunks; i++) {
        unsigned long off = i * SWAP_CHUNK_RAW;
        unsigned long raw_sz = window_sz - off;
        if (raw_sz > SWAP_CHUNK_RAW) raw_sz = SWAP_CHUNK_RAW;

        /* Copy raw chunk from the user window (identity-mapped). */
        kmemcpy(swap_buf_raw, (void *)(USER_LOAD_BASE + off), raw_sz);
        /* Zero the tail so LZ4 doesn't read garbage beyond the window. */
        if (raw_sz < SWAP_CHUNK_RAW)
            kmemset(swap_buf_raw + raw_sz, 0, SWAP_CHUNK_RAW - raw_sz);

        /* Compress.  Output format: [compressed_sz:u32 LE][compressed data]. */
        int csz = LZ4_compress_default((const char *)swap_buf_raw,
                    (char *)swap_buf_cmp + 4,
                    (int)SWAP_CHUNK_RAW, (int)(sizeof(swap_buf_cmp) - 4));
        unsigned int disk_csz;
        if (csz > 0 && (unsigned long)csz < raw_sz) {
            /* Compression helped — store compressed. */
            disk_csz = (unsigned int)csz;
        } else {
            /* No benefit — store raw (compressed_sz = 0 signals raw). */
            disk_csz = 0;
            kmemcpy(swap_buf_cmp + 4, swap_buf_raw, raw_sz);
        }
        *(unsigned int *)swap_buf_cmp = disk_csz;

        unsigned long total = 4 + (disk_csz ? disk_csz : raw_sz);
        unsigned long sects = (total + IDE_SECTOR_SIZE - 1) / IDE_SECTOR_SIZE;
        if (ide_write_sectors((unsigned int)data_lba, (unsigned int)sects,
                              swap_buf_cmp) < 0)
            return 0;
        data_lba += sects;
    }

    /* Write the header in the LAST sector of the swap area. */
    unsigned long hdr_lba = slba + SWAP_MAX_SECTORS - SWAP_HDR_SECTORS;
    unsigned int hdr[3];
    hdr[0] = SWAP_MAGIC;
    hdr[1] = (unsigned int)window_sz;
    hdr[2] = (unsigned int)nchunks;
    kmemset(hdr + 3, 0, IDE_SECTOR_SIZE - 12);
    if (ide_write_sectors((unsigned int)hdr_lba, SWAP_HDR_SECTORS, hdr) < 0)
        return 0;

    return 1;
}

/* Restore the parent's user window from the swap area on disk.
 * Reads the header, then each compressed/raw chunk, and writes back
 * to USER_LOAD_BASE.  Returns 1 on success, 0 on failure. */
static int swap_in(void) {
    unsigned long slba = swap_lba();
    if (!slba) return 0;

    /* Read the header from the last sector of the swap area. */
    unsigned long hdr_lba = slba + SWAP_MAX_SECTORS - SWAP_HDR_SECTORS;
    unsigned int hdr[3];
    if (ide_read_sectors((unsigned int)hdr_lba, SWAP_HDR_SECTORS, hdr) < 0)
        return 0;
    if (hdr[0] != SWAP_MAGIC) return 0;
    unsigned long window_sz = hdr[1];
    unsigned long nchunks   = hdr[2];

    unsigned long data_lba = slba;
    unsigned long dst = USER_LOAD_BASE;
    for (unsigned long i = 0; i < nchunks; i++) {
        /* Read one chunk (up to SWAP_CHUNK_SECTORS = 64 KB). */
        if (ide_read_sectors((unsigned int)data_lba, SWAP_CHUNK_SECTORS,
                             swap_buf_cmp) < 0)
            return 0;
        unsigned int csz = *(unsigned int *)swap_buf_cmp;

        unsigned long raw_sz = window_sz - (dst - USER_LOAD_BASE);
        if (raw_sz > SWAP_CHUNK_RAW) raw_sz = SWAP_CHUNK_RAW;

        if (csz) {
            /* Compressed chunk — decompress. */
            int dsz = LZ4_decompress_safe((const char *)swap_buf_cmp + 4,
                        (char *)swap_buf_raw, (int)csz, (int)SWAP_CHUNK_RAW);
            if (dsz < 0 || (unsigned long)dsz != raw_sz)
                return 0;
        } else {
            /* Raw chunk — copy directly. */
            kmemcpy(swap_buf_raw, swap_buf_cmp + 4, raw_sz);
        }
        kmemcpy((void *)dst, swap_buf_raw, raw_sz);
        dst += raw_sz;
        data_lba += SWAP_CHUNK_SECTORS;
    }
    return 1;
}

static int k_syscall_spawn(const char *path, const char *redirect,
                            int child_argc, const char **child_argv) {
    if (!path || !user_str_ok((unsigned long)path, RAMDISK_FNAME_LEN))
        return EFAULT;

    /* Validate child_argv if provided. The strings are arbitrary program
     * arguments (a key, a path, an option), not filenames: a 64-char aes key
     * is legitimate, so each is validated as NUL-terminated anywhere within
     * the user window, never against RAMDISK_FNAME_LEN. */
    if (child_argc > 0 && child_argv) {
        if (!user_range_ok((unsigned long)child_argv,
                           (unsigned long)(child_argc + 1) * sizeof(char *)))
            return EFAULT;
        for (int i = 0; i < child_argc; i++) {
            if (!child_argv[i]) break;
            unsigned long s = (unsigned long)child_argv[i];
            if (s < USER_LOAD_BASE || s >= USER_LOAD_END) return EFAULT;
            if (!user_str_ok(s, USER_LOAD_END - s)) return EFAULT;
        }
    }

    /* Copy argv from user space to kernel heap BEFORE saving the window,
     * because the window save/restore would overwrite the originals. */
    char **kargv = 0;
    if (child_argc > 0 && child_argv) {
        kargv = (char **)kmalloc((unsigned)(child_argc + 1) * sizeof(char *));
        if (!kargv) return EFAULT;
        for (int i = 0; i <= child_argc; i++) kargv[i] = 0;
        for (int i = 0; i < child_argc; i++) {
            if (!child_argv[i]) break;
            unsigned slen = (unsigned)kstrlen(child_argv[i]) + 1;
            kargv[i] = (char *)kmalloc(slen);
            if (!kargv[i]) { for (int j = 0; j < i; j++) kfree(kargv[j]); kfree(kargv); return EFAULT; }
            kmemcpy(kargv[i], child_argv[i], slen);
        }
        kargv[child_argc] = 0;
    }

    /* Resolve the path against the cwd. */
    char resolved[RAMDISK_FNAME_LEN];
    if (!fs_resolve(path, resolved, sizeof(resolved))) {
        if (kargv) { for (int i = 0; i < child_argc; i++) if (kargv[i]) kfree(kargv[i]); kfree(kargv); }
        return EFAULT;
    }

    /* Read the file into a kernel buffer.  Try ramdisk first, then MiniFS. */
    RDFile *f = ramdisk_open(resolved);
    unsigned char *data = 0;
    unsigned data_size = 0;
    if (f) {
        data_size = f->size ? f->size : 1;
        data = (unsigned char *)kmalloc(data_size);
        if (!data) {
            if (kargv) { for (int i = 0; i < child_argc; i++) if (kargv[i]) kfree(kargv[i]); kfree(kargv); }
            return EFAULT;
        }
        ramdisk_read(f, data, 0, f->size);
    } else if (minifs_is_mounted()) {
        int ino = minifs_resolve_path(resolved);
        if (ino < 0) {
            const char *base = resolved;
            const char *p;
            for (p = resolved; *p; p++)
                if (*p == '/') base = p + 1;
            ino = minifs_resolve_path(base);
        }
        if (ino >= 0) {
            MiniFSInode mi;
            if (minifs_stat(ino, &mi) >= 0 && mi.size > 0) {
                data_size = mi.size;
                data = (unsigned char *)kmalloc(data_size);
                if (data) minifs_read(ino, data, 0, data_size);
            }
        }
    }
    if (!data) {
        if (kargv) { for (int i = 0; i < child_argc; i++) if (kargv[i]) kfree(kargv[i]); kfree(kargv); }
        return EFAULT;
    }

    /* Classify by ELF type. */
    if (data_size < EI_NIDENT ||
        !(data[0] == 0x7F && data[1] == 'E' && data[2] == 'L' && data[3] == 'F')) {
        kfree(data);
        if (kargv) { for (int i = 0; i < child_argc; i++) if (kargv[i]) kfree(kargv[i]); kfree(kargv); }
        return EFAULT;
    }
    Elf64_Half etype = ((const Elf64_Ehdr *)data)->e_type;

    /* Save parent state. */
    unsigned long saved_brk      = g_brk;
    unsigned long saved_brk_lim  = g_brk_limit;
    unsigned long saved_mmap     = user_mmap_cur;
    unsigned long saved_fsbase   = rdmsr(MSR_FSBASE);
    unsigned long saved_gsbase   = rdmsr(MSR_GSBASE);

    /* Snapshot the mmap tables so the child cannot corrupt them. */
    int saved_mmap_used_n = mmap_used_n;
    struct mmap_ent saved_mmap_used[MMAP_MAX];
    for (int i = 0; i < mmap_used_n; i++) saved_mmap_used[i] = mmap_used[i];
    int saved_mmap_free_n = mmap_free_n;
    struct mmap_ent saved_mmap_free[MMAP_MAX];
    for (int i = 0; i < mmap_free_n; i++) saved_mmap_free[i] = mmap_free[i];

    /* Snapshot the kernel fd table. */
    KFILE *saved_kfd[KFD_MAX];
    for (int i = 0; i < KFD_MAX; i++) saved_kfd[i] = kfd_table[i];

    /* Save the parent's user window to the IDE swap area.
     * For ET_REL children (ring 0 via k_run_rel) the user window is
     * untouched so we skip the save entirely.  For ET_EXEC/ET_DYN we
     * scan backwards for the actual high-water mark (last non-zero page),
     * then write LZ4-compressed 64 KB chunks directly to the disk swap
     * area.  No heap allocation is used — the two static BSS buffers
     * (swap_buf_raw/swap_buf_cmp, ~128 KB) handle the compression. */
    int swap_saved = 0;
    unsigned long window_sz = 0;
    if (etype == ET_EXEC || etype == ET_DYN) {
        /* Scan backwards from USER_LOAD_END to find the last non-zero page.
         * g_brk is the program's requested break, but programs often request
         * far more than they use (MicroPython ~16 MB brk, actual use ~5 MB). */
        unsigned long parent_top = USER_LOAD_BASE + 0x1000;
        volatile unsigned long *scan =
            (volatile unsigned long *)USER_LOAD_END;
        while (scan > (volatile unsigned long *)USER_LOAD_BASE) {
            scan = (volatile unsigned long *)((unsigned long)scan - 0x1000);
            int all_zero = 1;
            for (int j = 0; j < 512; j++) {
                if (scan[j] != 0) { all_zero = 0; break; }
            }
            if (!all_zero) {
                parent_top = (unsigned long)scan + 0x1000;
                break;
            }
        }
        /* Also check brk — if it is above the scan result, include it. */
        if (g_brk > parent_top) parent_top = g_brk;
        if (parent_top < USER_STACK_BASE) parent_top = USER_STACK_BASE;
        window_sz = parent_top - USER_LOAD_BASE;
        if (window_sz < 0x1000) window_sz = 0x1000;
        /* Cap at a reasonable maximum to avoid excessive disk I/O. */
        if (window_sz > 64UL * 1024 * 1024) window_sz = 64UL * 1024 * 1024;

        swap_saved = swap_out(window_sz);
        if (!swap_saved) {
            /* Swap failed (no disk, area too small, etc.) — child runs
             * without saving the parent window.  The child may corrupt
             * the parent, but this is a graceful degradation vs. EFAULT. */
        }
    }

    int rc = EFAULT;
    if (etype == ET_REL) {
        prog_entry_t entry = elf_load((void *)data, data_size);
        /* Diagnostics BEFORE redirect so they go to screen, not capture file */
        kprintf("SPAWN: ET_REL entry=%lx argc=%d\n",
                (unsigned long)entry, child_argc);
        if (entry) {
            unsigned char *code = (unsigned char *)entry;
            kprintf("  [%lx]: ", (unsigned long)entry);
            for (int _i = 0; _i < 16; _i++) kprintf("%02x ", code[_i]);
            kprintf("\n");
        }
        /* Start redirect capture after diagnostics */
        int did_redirect = 0;
        if (redirect && redirect[0]) did_redirect = redirect_begin();
        if (entry)
            rc = k_run_rel(entry, child_argc, kargv ? kargv : (char **)child_argv);
        if (did_redirect) redirect_commit(redirect, 0);
    } else if (etype == ET_EXEC || etype == ET_DYN) {
        void *entry = load_exec_elf((void *)data, data_size);
        int did_redirect = 0;
        if (redirect && redirect[0]) did_redirect = redirect_begin();
        if (entry)
            rc = k_exec_user(entry, child_argc,
                             kargv ? (char **)kargv : (char **)child_argv);
        if (did_redirect) redirect_commit(redirect, 0);
    }

    /* Restore the parent's user window from the IDE swap area. */
    if (swap_saved) {
        swap_in();
    }
    kfree(data);

    /* Free kernel argv copy. */
    if (kargv) {
        for (int i = 0; i < child_argc; i++) if (kargv[i]) kfree(kargv[i]);
        kfree(kargv);
    }

    /* Restore parent kernel state. */
    g_brk       = saved_brk;
    g_brk_limit = saved_brk_lim;
    user_mmap_cur = saved_mmap;
    mmap_used_n = saved_mmap_used_n;
    for (int i = 0; i < mmap_used_n; i++) mmap_used[i] = saved_mmap_used[i];
    mmap_free_n = saved_mmap_free_n;
    for (int i = 0; i < mmap_free_n; i++) mmap_free[i] = saved_mmap_free[i];
    wrmsr(MSR_FSBASE, saved_fsbase);
    wrmsr(MSR_GSBASE, saved_gsbase);
    for (int i = 0; i < KFD_MAX; i++) kfd_table[i] = saved_kfd[i];
    /* Do NOT clobber syscall_kstack here: it holds the outer syscall's
       incoming rsp, and the outer syscall_entry xchg needs that exact value
       to return to the parent.  k_run_rel/k_exec_user already restored it. */

    return rc;
}

int k_exec_user(void *entry, int argc, char **argv) {
    char *stk = (char *)USER_STACK_BASE;   /* fixed region, no heap churn */
    unsigned long *sp = setup_user_stack(stk, USER_STACK_SIZE, argc, argv);
    unsigned long frame[5];
    if (!sp) return -1;
    exec_exit_code = 0;
    /* Save the caller's saved stack pointer in syscall_kstack and restore it
       on the way out: when SYS_SPAWN runs an ET_EXEC child, syscall_kstack
       currently holds the outer syscall's incoming rsp.  Clobbering it here
       (as the old code did) would make the outer syscall_entry xchg restore
       rsp=0x88000 instead of the parent's real stack, and the parent would
       resume at ring 0 with a broken stack. */
    unsigned long saved_kstack = syscall_kstack;

    /* The child is a ring-3 Linux binary whose `syscall` instructions swap
       onto syscall_kstack.  If it points at SYS_KSTK_TOP (0x88000), every
       child syscall (including the final exit) pushes its frame there and
       clobbers THIS handler's frames on the same stack — so when the child
       exits via klongjmp, k_exec_user's return address on 0x88000 has been
       overwritten and `ret` lands in the wrong place.  Give the child a
       dedicated kernel stack so its syscalls never touch 0x88000. */
    unsigned long child_stack_sz = SYS_KSTK_TOP - SYS_KSTK_BASE;
    void *child_stack = kmalloc(child_stack_sz);
    if (child_stack)
        syscall_kstack = (unsigned long)child_stack + child_stack_sz;
    else
        syscall_kstack = SYS_KSTK_TOP;
    wrmsr(MSR_FSBASE, 0);
    wrmsr(MSR_GSBASE, 0);

    /* Ring-3 entry frame, popped by iretq: RIP, CS, RFLAGS, RSP, SS. */
    frame[0] = (unsigned long)entry;
    frame[1] = (unsigned long)(GDT64_USER_CODE_SEL | 3);
    frame[2] = 0x202;                       /* IF=1: interrupts enabled for desktop tick */
    frame[3] = (unsigned long)sp;
    frame[4] = (unsigned long)(GDT64_USER_DATA_SEL | 3);

    /* exec_return is a shared global: a nested SYS_SPAWN child overwrites it
       via its own ksetjmp, so save it and restore it after the child exits.
       Otherwise the parent's later exit() would klongjmp back into the
       already-returned nested k_exec_user instead of here. */
    kjmpbuf saved_exec = exec_return;
    user_program_active = 1;
    if (ksetjmp(&exec_return) == 0) {
        __asm__ volatile(
            "mov %[udata], %%ax\n"
            "mov %%ax, %%ds\n"
            "mov %%ax, %%es\n"
            "mov %%ax, %%fs\n"
            "mov %%ax, %%gs\n"
            "mov %[frame], %%rsp\n"
            "xorl %%ebp, %%ebp\n"
            "xorl %%edi, %%edi\n"
            "xorl %%esi, %%esi\n"
            "xorl %%edx, %%edx\n"
            "iretq\n"
            :: [frame] "r"(frame), [udata] "i"(GDT64_USER_DATA_SEL | 3)
            : "rax", "memory");
        __builtin_unreachable();
    }
    user_program_active = 0;

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
    exec_return = saved_exec;
    syscall_kstack = saved_kstack;
    if (child_stack) kfree(child_stack);
    if (vga_mode13h || graphics_program_ran) {
        if (s_trace_enabled)
            kprintf("[exit-gfx] reset: mode13h=%d ran=%d\n", vga_mode13h, graphics_program_ran);
        vga_mode13h = 0; /* reclaim the display for the text console */
        graphics_program_ran = 0;
        vga_fb_set_gfx_mode(0); /* drop the graphics pointer state */
        vga_fb_draw_desktop(); /* drop the graphics window, restore desktop */
    }
    kbd_reset_for_shell();
    return exec_exit_code;
}

/* Run an ET_REL program as a plain function call, but catch a libc exit(). */
int k_run_rel(prog_entry_t entry, int argc, char **argv) {
    exec_exit_code = 0;
    /* Save the caller's stack pointer held in syscall_kstack and restore it
       on the way out.  When SYS_SPAWN runs an ET_REL child, syscall_kstack
       holds the outer syscall's incoming rsp; clobbering it to SYS_KSTK_TOP
       would make the outer syscall_entry xchg restore rsp=0x88000, so the
       parent resumes at ring 0 with a broken stack (its retq pops 0 -> RIP=0).
       The child itself needs syscall_kstack = SYS_KSTK_TOP so its own ring-0
       syscalls swap onto the kernel stack. */
    unsigned long saved_kstack = syscall_kstack;
    syscall_kstack = SYS_KSTK_TOP;

    /* Enable SSE/OSFXSR so ring-0 code can use xmm instructions (miniGCC
       emits pcmpeqd etc. in prologues).  Clear CR0.TS to解除 any "device
       not available" trap. */
    unsigned long cr0, cr4;
    __asm__ volatile("mov %%cr0, %0" : "=r"(cr0));
    __asm__ volatile("mov %0, %%cr0" :: "r"(cr0 & ~0x8UL) : "memory");
    __asm__ volatile("mov %%cr4, %0" : "=r"(cr4));
    __asm__ volatile("mov %0, %%cr4" :: "r"(cr4 | 0x600UL) : "memory");

    /* Save the caller's exec_return too: a nested spawn's ksetjmp would
       overwrite the shared global and break the parent's later exit(). */
    kjmpbuf saved_exec = exec_return;

    if (ksetjmp(&exec_return) == 0) {
        int rc = entry(argc, argv);
        exec_return = saved_exec;
        syscall_kstack = saved_kstack;
        return rc;
    }

    /* klongjmp landed here after kexit() */
    exec_return = saved_exec;
    syscall_kstack = saved_kstack;
    if (vga_mode13h || graphics_program_ran) {
        vga_mode13h = 0;
        graphics_program_ran = 0;
        vga_fb_set_gfx_mode(0);
        vga_fb_draw_desktop();
    }
    kbd_reset_for_shell();
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

/* The CVM interpreter ships on the ramdisk as objects/cvm.o and is loaded
 * on demand the first time a .cvm module is run. */
#define SHELL_CVM_INTERP    "objects/cvm.o"

/* Runnable-file lookup: a bare name is mapped to a toolchain directory by
 * its suffix, so `ld.o` finds objects/ld.o, `fib.elf` finds bin/fib.elf and
 * `w1.cvm` finds cvm/w1.cvm. A bare name with no recognised suffix (cp,
 * freedom, ...) resolves through bin/, the command path. Every candidate is
 * checked for existence before it is run, so a name can never be truncated
 * into a path it does not own. */
typedef struct {
    const char *suffix;    /* matched against the name tail; "" is the default */
    const char *dir;       /* ramdisk directory prefix, no leading slash */
} ShellRunDir;

static const ShellRunDir shell_run_dirs[] = {
    { ".cvm",  "cvm/" },
    { ".o",    "objects/" },
    { ".elf",  "bin/" },
    { "",      "bin/" },
};
#define SHELL_RUN_DIRS (sizeof(shell_run_dirs) / sizeof(shell_run_dirs[0]))

static char cmd_buf[CMD_BUF_SZ];
/* A desktop-icon launch that arrived while a user program owned the CPU.
 * The ISR-driven desktop tick cannot run shell_run_any (it would re-enter
 * k_exec_user from ISR context and corrupt the running program), so the
 * command is queued here and executed as the shell's next command. */
static char shell_pending_cmd[CMD_BUF_SZ];
static int  shell_pending_len;

/* Queue a desktop-icon command to run after the current user program exits.
 * Overwrites any earlier pending launch; safe to call from the ISR (it only
 * copies into a kernel buffer). */
void shell_queue_launch(const char *cmd) {
    unsigned i = 0;
    if (!cmd) return;
    while (cmd[i] && i < (unsigned)CMD_BUF_SZ - 1) {
        shell_pending_cmd[i] = cmd[i];
        i++;
    }
    shell_pending_cmd[i] = 0;
    shell_pending_len = (int)i;
}

#define SHELL_HIST_MAX 16
static char shell_hist[SHELL_HIST_MAX][CMD_BUF_SZ];
static int  shell_hist_count;
static int  shell_hist_idx = -1;
static char shell_line_saved[CMD_BUF_SZ];
static int  shell_line_saved_pos;
/* On-screen cursor column within the edit line, so a repaint can back up to
 * the line start exactly. Kept in sync by every echo/repaint path. */
static int  shell_cur;

static void shell_prompt(void) { vga_puts("\nminiOS> "); }

static void shell_exec_builtin(int argc, char **argv);

/* Strict decimal parse for the `vol` builtin: the whole argument must be an
 * optional sign followed by at least one digit, and the value is clamped to
 * the speaker's valid range. Garbage is rejected, never silently zero. */
static int shell_parse_vol(const char *s, unsigned *out) {
    long v = 0;
    int sign = 1;
    if (!s || !*s) return 0;
    if (*s == '-') { sign = -1; s++; }
    else if (*s == '+') s++;
    if (!*s) return 0;
    for (; *s; s++) {
        int d = *s - '0';
        if (d < 0 || d > 9) return 0;
        if (v > (PCSPK_VOL_MAX - (unsigned)d) / 10) v = PCSPK_VOL_MAX;
        else v = v * 10 + d;
    }
    v *= sign;
    if (v < PCSPK_VOL_MIN) v = PCSPK_VOL_MIN;
    if (v > PCSPK_VOL_MAX) v = PCSPK_VOL_MAX;
    *out = (unsigned)v;
    return 1;
}


/* ---- Console input multiplexer (serial + PS/2) ----
 *
 * Bytes from either source are funneled through a small FIFO ("pb") so that
 * escape sequences can be recognised, partially consumed, and re-injected.
 * The PageUp/PageDown keys — whether they arrive as PS/2 E0-prefixed make
 * codes (translated by kbd_read into the standard CSI form) or directly over
 * the serial line as ESC [ 5 ~ / ESC [ 6 ~ — enter a scrollback view of past
 * output; any other key leaves scrollback and is delivered to the caller. */

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

/* Next raw byte (kbd queue, then serial, then PS/2) without touching the
 * pushback FIFO; blocks until one is available. */
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

/* Non-blocking variant of the above for sequence lookahead. */
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

/* Poll for the next raw byte with a bounded spin, so a multi-byte escape
 * sequence arriving over the serial line (byte by byte) is read as a unit.
 * Returns the byte, or -1 after MAX_SEQ_POLL polls. The bound keeps a bare
 * ESC (never completed into a sequence) from hanging the reader. */
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

/* Called after an ESC byte has been read. Pulls the remainder of the sequence
 * non-blocking and classifies it. Returns 1 (PageUp), 2 (PageDown), or 0 for
 * "not a page key" — in which case every byte pulled EXCEPT the leading ESC
 * is re-injected into the pushback FIFO so the caller can hand them back to
 * the readline layer exactly as it would a raw escape. */
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

/* Blocking read from either the PS/2 keyboard or COM1 serial line. Recognises
 * the PageUp/PageDown escape sequences and detours into the scrollback view;
* the view re-injects any terminating key into the pushback FIFO, so once it
 * returns console_getc() simply serves the FIFO again. */
static int console_getc(void) {
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

/* Next buffered byte without consuming it, or -1 when nothing is available
 * right now. Used to tell an ESC prefix from a complete escape sequence,
 * which always arrives in one burst. */
static int console_peek(void) {
    if (!pb_empty()) return pb_peek();
    int c = raw_try_getc();
    if (c >= 0) pb_push_back((unsigned char)c);
    return pb_peek();
}

/* ---- Scrollback view ----
 *
 * Renders a 25-row window over (scrollback ring + live screen) into the VGA
 * framebuffer and to the serial console, hides the cursor, and lets the user
 * page up/down through history. PageDown at the bottom, or any other key,
 * exits; the exit key is re-injected into the pushback FIFO so the readline
 * that was waiting for input receives it as if scrollback never happened. */
#define SB_LEN  (VGA_ROWS * VGA_COLS * 2)

static void scrollback_render(int voff, int total, const unsigned char *saved) {
    for (int r = 0; r < VGA_ROWS; r++) {
        int li = voff + r;
        for (int x = 0; x < VGA_COLS; x++) {
            char ch;
            if (li < sb_count) {
                int idx = (sb_head + li) % SCROLLBACK_ROWS;
                ch = sb_ring[(unsigned long)idx * VGA_COLS + x];
            } else {
                int live_row = li - sb_count;
                ch = (char)saved[(unsigned long)(live_row * VGA_COLS + x) * 2];
            }
            VGA_BASE[(unsigned long)(r * VGA_COLS + x) * 2]     = ch;
            VGA_BASE[(unsigned long)(r * VGA_COLS + x) * 2 + 1] = vga_color;
            serial_putc(ch);
        }
        serial_putc('\n');
    }
}

#define SB_PGUP  1
#define SB_PGDN  2
#define SB_EXIT  3

/* Reads the next scrollback key event: PageUp/PageDown navigate; any other
 * key (or a non-page escape sequence) is re-injected and reported as SB_EXIT. */
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
    if (sb_inited == 0) sb_init();
    if (sb_inited != 1 || sb_count == 0) return;   /* nothing scrolled yet */

    static unsigned char saved[SB_LEN];
    for (int i = 0; i < SB_LEN; i++) saved[i] = VGA_BASE[i];
    int saved_x = vga_x, saved_y = vga_y;
    vga_cursor_enable(0);

    int total  = sb_count + VGA_ROWS;
    int bottom = total - VGA_ROWS;          /* voff showing the live screen  */
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
    vga_x = saved_x; vga_y = saved_y;
    vga_set_cursor(vga_x, vga_y);
    vga_cursor_enable(1);
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

/* The component of a ramdisk path after the last '/', or the whole path when
 * there is no '/'. Used to match a bare command word against a file's name. */
static const char *shell_name_base(const char *path) {
    const char *base = path;
    const char *slash = kstrchr(path, '/');
    while (slash) { base = slash + 1; slash = kstrchr(base, '/'); }
    return base;
}

/* Replace the current word [word_start, word_start+wlen) in `buf` with `text`
 * and move the cursor to the end of the completed line. Bounds checked: a
 * completion that would overflow `size` is refused, never truncated. */
static void shell_complete_replace(char *buf, int size, int *pos,
                                   char *word_start, unsigned long wlen,
                                   const char *text) {
    unsigned long tlen = kstrlen(text);
    unsigned long head = (unsigned long)(word_start - buf);
    unsigned long tail = (unsigned long)(buf + *pos) - (unsigned long)(word_start + wlen);
    if (head + tlen + tail + 1 > (unsigned long)size) return;
    if (tlen != wlen)
        kmemmove(word_start + tlen, word_start + wlen, tail);
    kmemcpy(word_start, text, tlen);
    *pos = (int)(head + tlen + tail);
    buf[*pos] = 0;
    for (unsigned long i = 0; i < wlen; i++) vga_putc('\b');
    vga_puts(text);
    vga_putc('\n');
    shell_cur = 0;
}

static void shell_readline(void) {
    shell_readline_hist(cmd_buf, CMD_BUF_SZ);
}

/* Redraw the edit line: erase what is shown, then write `text` into buf and
 * onto the console, leaving the text cursor at `*pos`. The cursor is drawn
 * on the framebuffer terminal; on the serial console the text is rewritten
 * and the reader's position is implied by the console cursor. */
static void shell_hist_show(char *buf, int size, int *pos, const char *text) {
    int i, n = 0;
    /* Erase the whole current line: back up to its start, blank it, return. */
    for (i = 0; i < shell_cur; i++) vga_putc('\b');
    for (i = 0; i < shell_cur; i++) vga_putc(' ');
    for (i = 0; i < shell_cur; i++) vga_putc('\b');
    kmemset(buf, 0, (unsigned long)size);
    while (text[n] && n < size - 1) {
        buf[n] = text[n];
        vga_putc(text[n]);
        n++;
    }
    *pos = n;
    shell_cur = n;
    vga_fb_text_cursor(n);
}

/* Repaint the edit line after a cursor move or mid-line edit: erase the whole
 * visible line, rewrite buf, then back the console cursor up to `pos` and
 * redraw the framebuffer text cursor there. `shell_cur` holds the on-screen
 * cursor column, so the erase backs up to the line start before blanking it
 * (a serial backspace alone does not clear a character). */
static void shell_line_repaint(char *buf, int size, int pos) {
    int i, len = (int)kstrlen(buf);
    for (i = 0; i < shell_cur; i++) vga_putc('\b');
    for (i = 0; i < len; i++) vga_putc(' ');
    for (i = 0; i < len; i++) vga_putc('\b');
    for (i = 0; i < len; i++) vga_putc(buf[i]);
    for (i = len; i > pos; i--) vga_putc('\b');
    shell_cur = pos;
    vga_fb_text_cursor(pos);
}

/* Insert character c into buf at `pos`, shifting the tail right. Bounds
 * checked; the caller repaints afterwards. */
static void shell_line_insert(char *buf, int size, int *pos, char c) {
    int len = (int)kstrlen(buf);
    if (len >= size - 1) return;
    kmemmove(buf + *pos + 1, buf + *pos, (unsigned long)(len - *pos + 1));
    buf[*pos] = c;
    (*pos)++;
}

/* Delete the character before the cursor (backspace). */
static void shell_line_backspace(char *buf, int size, int *pos) {
    int len = (int)kstrlen(buf);
    if (*pos <= 0) return;
    kmemmove(buf + *pos - 1, buf + *pos, (unsigned long)(len - *pos + 1));
    (*pos)--;
}

/* Delete the character at the cursor (Delete key). */
static void shell_line_delete(char *buf, int size, int *pos) {
    int len = (int)kstrlen(buf);
    if (*pos >= len) return;
    kmemmove(buf + *pos, buf + *pos + 1, (unsigned long)(len - *pos));
}

/* Delete from the cursor to the start of the line (Ctrl+U). */
static void shell_line_kill_front(char *buf, int size, int *pos) {
    int len = (int)kstrlen(buf);
    kmemmove(buf, buf + *pos, (unsigned long)(len - *pos + 1));
    *pos = 0;
}

/* Delete from the cursor to the end of the line (Ctrl+K). */
static void shell_line_kill_tail(char *buf, int size, int *pos) {
    buf[*pos] = '\0';
}

/* Delete the word before the cursor (Ctrl+W): skip spaces, then non-spaces. */
static void shell_line_kill_word(char *buf, int size, int *pos) {
    int len = (int)kstrlen(buf);
    int s = *pos;
    while (s > 0 && buf[s - 1] == ' ') s--;
    while (s > 0 && buf[s - 1] != ' ') s--;
    kmemmove(buf + s, buf + *pos, (unsigned long)(len - *pos + 1));
    *pos = s;
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
            vga_fb_hide_text_cursor();
            shell_cur = 0;
            buf[kstrlen(buf)] = 0;
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
                } else if (b == KEY_ARR_LEFT || b == KEY_ARR_RIGHT) {
                    console_getc();
                    int len = (int)kstrlen(buf);
                    int npos = pos + (b == KEY_ARR_RIGHT ? 1 : -1);
                    if (npos >= 0 && npos <= len) {
                        pos = npos;
                        shell_line_repaint(buf, size, pos);
                    }
                } else if (b == KEY_HOME_SEQ || b == KEY_END_SEQ) {
                    console_getc();
                    pos = (b == KEY_HOME_SEQ) ? 0 : (int)kstrlen(buf);
                    shell_line_repaint(buf, size, pos);
                } else if (b == '3') {
                    console_getc();
                    /* The `~` terminator may not have arrived yet over serial;
                     * read it blocking. A non-~ byte is pushed back and
                     * reprocessed on the next loop iteration. */
                    int t = console_getc();
                    if (t == KEY_TILDE) {
                        shell_line_delete(buf, size, &pos);
                        shell_line_repaint(buf, size, pos);
                    } else if (t >= 0) {
                        pb_push_front((unsigned char)t);
                    }
                }
            }
            continue;
        }
        if (c == '\t') {
            char *word_start = buf + pos;
            while (word_start > buf && word_start[-1] != ' ' && word_start[-1] != '\t')
                word_start--;
            unsigned long wlen = (unsigned long)pos - (unsigned long)(word_start - buf);
            if (wlen == 0) { vga_putc('\a'); continue; }
            char *comps[32];
            int ncomps = 0;
            for (int i = 0; i < kprog_count && ncomps < 32; i++) {
                if (kstrncmp(kprog_table[i].name, word_start, wlen) == 0)
                    comps[ncomps++] = kprog_table[i].name;
            }
            if (ncomps == 0) {
                RDFile *files[RAMDISK_MAX_FILES];
                int n = ramdisk_list(files, RAMDISK_MAX_FILES);
                for (int i = 0; i < n && ncomps < 32; i++) {
                    const char *base = shell_name_base(files[i]->name);
                    if (kstrncmp(files[i]->name, word_start, wlen) == 0 ||
                        kstrncmp(base, word_start, wlen) == 0)
                        comps[ncomps++] = files[i]->name;
                }
            }
            if (ncomps == 0) { vga_putc('\a'); continue; }
            if (ncomps == 1) {
                if (kstrcmp(comps[0], word_start) != 0)
                    shell_complete_replace(buf, size, &pos, word_start, wlen, comps[0]);
                else {
                    if (pos < size - 1) { buf[pos++] = ' '; buf[pos] = 0; }
                    vga_putc(' ');
                    shell_cur = pos;
                }
                continue;
            }
            unsigned long common = kstrlen(comps[0]);
            for (int i = 1; i < ncomps; i++) {
                unsigned long l = kstrlen(comps[i]);
                if (l < common) common = l;
                unsigned long j;
                for (j = 0; j < common; j++)
                    if (comps[0][j] != comps[i][j]) break;
                common = j;
            }
            if (common > wlen && kstrncmp(comps[0], word_start, wlen) == 0) {
                char prefix[RAMDISK_FNAME_LEN];
                if (common < sizeof(prefix)) {
                    kmemcpy(prefix, comps[0], common);
                    prefix[common] = 0;
                    shell_complete_replace(buf, size, &pos, word_start, wlen, prefix);
                }
                continue;
            }
            vga_puts("Possible completions:");
            vga_putc('\n');
            for (int i = 0; i < ncomps; i++) {
                vga_puts("  ");
                vga_puts(comps[i]);
                vga_putc('\n');
            }
            continue;
        }
        if (c == '\b' || c == 0x7F || (c >= 32 && c < 127)) {
            if (shell_hist_idx >= 0) shell_hist_idx = -1;
        }
        /* Ctrl keys: A/E start/end, U kill front, K kill tail, W kill word. */
        if (c == 0x01 || c == 0x05) {
            pos = (c == 0x01) ? 0 : (int)kstrlen(buf);
            shell_line_repaint(buf, size, pos);
            continue;
        }
        if (c == 0x15) { /* Ctrl+U */
            shell_line_kill_front(buf, size, &pos);
            shell_line_repaint(buf, size, pos);
            continue;
        }
        if (c == 0x0B) { /* Ctrl+K */
            shell_line_kill_tail(buf, size, &pos);
            shell_line_repaint(buf, size, pos);
            continue;
        }
        if (c == 0x17) { /* Ctrl+W */
            shell_line_kill_word(buf, size, &pos);
            shell_line_repaint(buf, size, pos);
            continue;
        }
        if (c == '\b' || c == 0x7F) {
            if (pos > 0) {
                int at_end = (pos == (int)kstrlen(buf));
                shell_line_backspace(buf, size, &pos);
                if (at_end) {
                    vga_putc('\b'); vga_putc(' '); vga_putc('\b');
                    shell_cur = pos;
                } else {
                    shell_line_repaint(buf, size, pos);
                }
            }
            continue;
        }
        if (pos < size - 1 && c >= 32 && c < 127) {
            int at_end = (pos == (int)kstrlen(buf));
            shell_line_insert(buf, size, &pos, (char)c);
            if (at_end) {
                vga_putc(c);
                shell_cur = pos;
            } else {
                shell_line_repaint(buf, size, pos);
            }
        }
    }
}

static int shell_parse(char *line, char **argv, int max_args) {
    int argc = 0;
    char *p = line;
    while (*p && argc < max_args) {
        while (*p == ' ' || *p == '\t') p++;
        if (*p == 0) break;
        if (*p == '"') {
            p++;
            argv[argc++] = p;
            while (*p && *p != '"') p++;
            if (*p) { *p = 0; p++; }
        } else {
            argv[argc++] = p;
            while (*p && *p != ' ' && *p != '\t') p++;
            if (*p) { *p = 0; p++; }
        }
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
        if (shell_pending_len > 0) {
            /* A desktop icon was clicked while a program ran; run it now
             * that the shell has control again, without a fresh prompt. */
            kmemcpy(cmd_buf, shell_pending_cmd, (unsigned long)shell_pending_len + 1);
            shell_pending_len = 0;
        } else {
            shell_prompt();
            shell_readline();
        }

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
    if (!fs_resolve(fname, resolved, sizeof(resolved))) return 0;
    if (fs_is_dir(resolved)) return 0;
    RDFile *f = ramdisk_open(resolved);
    unsigned char *data = 0;
    unsigned data_size = 0;
    if (f) {
        data_size = f->size;
        data = kmalloc(data_size ? data_size : 1);
        if (!data) return 0;
        ramdisk_read(f, data, 0, data_size);
    } else if (minifs_is_mounted()) {
        int ino = minifs_resolve_path(resolved);
        if (ino < 0 && kstrchr(resolved, '/')) {
            const char *base = resolved;
            const char *p;
            for (p = resolved; *p; p++)
                if (*p == '/') base = p + 1;
            ino = minifs_resolve_path(base);
        }
        if (ino >= 0) {
            MiniFSInode st;
            if (minifs_stat(ino, &st) >= 0 && st.size > 0) {
                data_size = st.size;
                data = kmalloc(data_size);
                if (!data) return 0;
                minifs_read(ino, data, 0, data_size);
            }
        }
    }
    if (!data) return 0;

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
    if (data_size >= 4 && data[0] == 0x7F && data[1] == 'E' && data[2] == 'L' && data[3] == 'F') {
        Elf64_Half etype = ((Elf64_Ehdr *)data)->e_type;
        if (etype == ET_REL) {
            entry = elf_load(data, data_size);
            if (entry) { k_register_program(progname_out, (prog_entry_t)entry); kind = 1; }
        } else if (etype == ET_EXEC || etype == ET_DYN) {
            entry = load_exec_elf(data, data_size);
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

/* ---- Runnable-file resolution (objects/ bin/ cvm/) ----
 *
 * `run <file>` and a bare `<file>` share one resolver and one loader. A bare
 * name is mapped through shell_run_dirs by its suffix; a path with a '/' is
 * resolved against the cwd. Every candidate must exist as a real file before
 * it is considered. The same resolver backs the shell prompt's TAB
 * completion, so what completes is exactly what can run. */

/* The toolchain directory that owns `name`, chosen by suffix. Bare names with
 * no recognised suffix fall through to the command path bin/. */
static const ShellRunDir *shell_run_dir_for(const char *name) {
    int i;
    for (i = 0; i < SHELL_RUN_DIRS; i++) {
        const char *suf = shell_run_dirs[i].suffix;
        if (suf[0] == 0) continue;
        int sl = (int)kstrlen(suf);
        int nl = (int)kstrlen(name);
        if (nl >= sl && kstrcmp(name + nl - sl, suf) == 0)
            return &shell_run_dirs[i];
    }
    for (i = 0; i < SHELL_RUN_DIRS; i++)
        if (shell_run_dirs[i].suffix[0] == 0)
            return &shell_run_dirs[i];
    return &shell_run_dirs[0];
}

/* Is `resolved` (already normalised against the cwd) a real ramdisk file? A
 * directory name or a non-existent path is rejected, never run. */
static int shell_file_is_real(const char *resolved) {
    if (!resolved[0]) return 0;
    if (fs_is_dir(resolved)) return 0;
    return ramdisk_open(resolved) ? 1 : 0;
}

/* Resolve `name` to a full ramdisk path suitable for running. A bare name is
 * tried first against the cwd, then through the suffix-picked toolchain
 * directory, then through the remaining directories as fallback. Returns 1
 * and fills `out` (cap bytes) on success, 0 when no candidate is a real file.
 * A candidate that cannot fit `cap` is skipped like a missing file, never
 * truncated. */
static int shell_resolve_run(const char *name, char *out, unsigned cap) {
    char cand[RAMDISK_FNAME_LEN];
    if (kstrchr(name, '/')) {
        if (!fs_resolve(name, cand, sizeof(cand))) return 0;
        if (!shell_file_is_real(cand)) return 0;
        kmemcpy(out, cand, kstrlen(cand) + 1);
        return 1;
    }
    if (fs_resolve(name, cand, sizeof(cand)) && shell_file_is_real(cand)) {
        kmemcpy(out, cand, kstrlen(cand) + 1);
        return 1;
    }
    const ShellRunDir *pref = shell_run_dir_for(name);
    unsigned long pref_off = (unsigned long)(pref - shell_run_dirs);
    int i;
    for (i = 0; i < SHELL_RUN_DIRS; i++) {
        const ShellRunDir *d =
            &shell_run_dirs[(pref_off + (unsigned long)i) % SHELL_RUN_DIRS];
        unsigned dl = (unsigned)kstrlen(d->dir);
        unsigned nl = (unsigned)kstrlen(name);
        if (dl + nl + 1 > sizeof(cand)) continue;
        kmemcpy(cand, d->dir, dl);
        kmemcpy(cand + dl, name, nl + 1);
        if (shell_file_is_real(cand)) {
            if (dl + nl + 1 > cap) return 0;
            kmemcpy(out, cand, dl + nl + 1);
            return 1;
        }
    }
    return 0;
}

/* Run a raw ELF image (ET_REL, ET_EXEC or ET_DYN) already read into `data`.
 * argv[0] is the program name the program sees. Returns the exit code, or -1
 * when the buffer is not a loadable ELF. The image is not registered; it is
 * relocated and executed fresh, then dropped. */
static int shell_run_elf_buf(const char *data, unsigned size, int argc,
                             char **argv) {
    if (!data || size < EI_NIDENT ||
        !(data[0] == 0x7F && data[1] == 'E' && data[2] == 'L' && data[3] == 'F'))
        return -1;
    Elf64_Half etype = ((const Elf64_Ehdr *)data)->e_type;
    if (etype == ET_REL) {
        prog_entry_t entry = elf_load((void *)data, size);
        if (!entry) return -1;
        return k_run_rel(entry, argc, argv);
    }
    if (etype == ET_EXEC || etype == ET_DYN) {
        void *entry = load_exec_elf((void *)data, size);
        if (!entry) return -1;
        return k_exec_user(entry, argc, argv);
    }
    return -1;
}

/* Load the ramdisk file at `full` and run it as an ELF. Returns the exit
 * code, or -1 when the file cannot be read or loaded. */
static int shell_run_elf_file(const char *full, int argc, char **argv) {
    RDFile *f = ramdisk_open(full);
    if (!f) return -1;
    unsigned char *data = kmalloc(f->size ? f->size : 1);
    if (!data) { kprintf("run: out of memory\n"); return -1; }
    ramdisk_read(f, data, 0, f->size);
    int ret = shell_run_elf_buf((const char *)data, f->size, argc, argv);
    kfree(data);
    return ret;
}

/* Load a Linux ELF from the MiniFS disk and run it (preserves the historical
 * `run` fallback when a name is not on the ramdisk). */
static int shell_run_elf_minifs(const char *name, int argc, char **argv) {
    if (!minifs_is_mounted()) return -1;
    char cand[RAMDISK_FNAME_LEN];
    int ino = -1;
    if (kstrchr(name, '/')) {
        ino = minifs_resolve_path(name);
        if (ino < 0) {
            const char *base = name;
            const char *p;
            for (p = name; *p; p++)
                if (*p == '/') base = p + 1;
            ino = minifs_resolve_path(base);
        }
    } else {
        ino = minifs_resolve_path(name);
        if (ino < 0) {
            const ShellRunDir *pref = shell_run_dir_for(name);
            unsigned long pref_off = (unsigned long)(pref - shell_run_dirs);
            for (int i = 0; i < SHELL_RUN_DIRS; i++) {
                const ShellRunDir *d =
                    &shell_run_dirs[(pref_off + (unsigned long)i) % SHELL_RUN_DIRS];
                unsigned dl = (unsigned)kstrlen(d->dir);
                unsigned nl = (unsigned)kstrlen(name);
                if (dl + nl + 1 > sizeof(cand)) continue;
                kmemcpy(cand, d->dir, dl);
                kmemcpy(cand + dl, name, nl + 1);
                ino = minifs_resolve_path(cand);
                if (ino >= 0) break;
            }
        }
    }
    if (ino < 0) return -1;
    MiniFSInode st;
    if (minifs_stat(ino, &st) < 0 || st.size == 0) return -1;
    unsigned char *buf = (unsigned char *)kmalloc(st.size);
    if (!buf) return -1;
    minifs_read(ino, buf, 0, st.size);
    int ret = shell_run_elf_buf((const char *)buf, st.size, argc, argv);
    kfree(buf);
    return ret;
}

/* Run a `.cvm` module at the resolved path `full`. The interpreter is loaded
 * from the ramdisk on first use and cached. argv[0] is the module name the
 * module sees; the interpreter passes it and the remaining words through as
 * a Linux-style argv. */
static int shell_run_cvm(const char *full, int argc, char **argv) {
    static prog_entry_t cvm_entry = 0;
    if (!cvm_entry) {
        RDFile *rf = ramdisk_open(SHELL_CVM_INTERP);
        if (!rf) { shell_report("run: objects/cvm.o not on ramdisk", 0); return -1; }
        unsigned char *data = kmalloc(rf->size ? rf->size : 1);
        if (!data) { kprintf("run: out of memory\n"); return -1; }
        ramdisk_read(rf, data, 0, rf->size);
        void *e = elf_load(data, rf->size);
        kfree(data);
        if (!e) { shell_report("run: cannot load objects/cvm.o", 0); return -1; }
        cvm_entry = (prog_entry_t)e;
    }
    char *saved0 = argv[0];
    /* The interpreter opens argv[0] via fopen -> kfopen -> fs_resolve.
     * A bare ramdisk path like "cvm/fib.cvm" would be resolved against cwd
     * again, so build an absolute path to prevent double resolution. */
    char abspath[RAMDISK_FNAME_LEN];
    abspath[0] = '/';
    kmemcpy(abspath + 1, full, kstrlen(full) + 1);
    argv[0] = abspath;
    int ret = cvm_entry(argc, argv);
    argv[0] = saved0;
    return ret;
}

/* Run `name` as a ramdisk/MiniFS file: `.cvm` modules through the
 * interpreter, ELF files by content through the matching loader. Returns the
 * exit code, or -1 when the name resolves to nothing runnable. */
static int shell_run_file(const char *name, int argc, char **argv) {
    char full[RAMDISK_FNAME_LEN];
    int nl = (int)kstrlen(name);
    if (nl >= 4 && kstrcmp(name + nl - 4, ".cvm") == 0) {
        if (shell_resolve_run(name, full, sizeof(full)))
            return shell_run_cvm(full, argc, argv);
        if (minifs_is_mounted()) {
            int ino = minifs_resolve_path(name);
            if (ino < 0 && kstrchr(name, '/')) {
                const char *base = name;
                const char *p;
                for (p = name; *p; p++)
                    if (*p == '/') base = p + 1;
                ino = minifs_resolve_path(base);
                if (ino >= 0) name = base;
            }
            if (ino >= 0)
                return shell_run_cvm(name, argc, argv);
        }
        return -1;
    }
    if (shell_resolve_run(name, full, sizeof(full)))
        return shell_run_elf_file(full, argc, argv);
    return shell_run_elf_minifs(name, argc, argv);
}

/* Unified dispatcher used by `run` and by bare commands: a registered program
 * wins, then the runnable-file resolver. argv[0] is the command/program name
 * as typed. Returns the exit code, or -1 when the name cannot be run. */
static int shell_run_any(const char *name, int argc, char **argv) {
    int nl = (int)kstrlen(name);
    if (nl >= 4 && kstrcmp(name + nl - 4, ".cvm") == 0)
        return shell_run_file(name, argc, argv);
    KProg *p = kprog_lookup(name);
    if (p) {
        if (p->is_proc) return k_exec_user(p->proc_entry, argc, argv);
        return k_run_rel(p->entry, argc, argv);
    }
    return shell_run_file(name, argc, argv);
}

/* ---- Desktop shortcut launch ----
 * Called by the desktop click handler (vga_fb.c) when an icon is clicked.
 * Splits the command line into argv and routes through shell_exec_builtin,
 * which handles builtins (run, cat, ls, ...) and falls through to
 * shell_run_any for registered programs and files.  The ~shell command name
 * is special: it activates the terminal. */
void desktop_launch(const char *cmd) {
    if (!cmd || !*cmd) return;
    if (user_program_active) {
        /* The tick runs from the ISR while a program owns the CPU; defer the
         * launch until the program exits instead of re-entering k_exec_user
         * from ISR context (which corrupts the running program's state). */
        shell_queue_launch(cmd);
        return;
    }
    if (cmd[0] == '~' && kstrcmp(cmd, "~shell") == 0) {
        /* ~shell: bring the terminal to focus (already visible). */
        return;
    }
    /* Parse command into argv (space-separated, max 8 args).  Each arg is
     * copied sequentially into buf so argv pointers stay valid for the call. */
    char buf[128];
    char *argv[8];
    int argc = 0;
    int pos = 0;
    const char *p = cmd;
    while (*p && argc < 8) {
        while (*p == ' ') p++;
        if (!*p) break;
        argv[argc] = buf + pos;
        while (*p && *p != ' ' && pos < (int)sizeof(buf) - 1) {
            buf[pos++] = *p++;
        }
        buf[pos++] = '\0';
        argc++;
    }
    if (argc > 0) shell_exec_builtin(argc, argv);
}

/* ---- Graphics debugging (`gfx` builtin) ----
 *
 * The serial console is the observability surface the BDD suite drives, but a
 * framebuffer program's output never reaches it. `gfx` lifts the graphics
 * side onto the console: state, single-pixel sampling, region statistics and
 * a PPM screenshot are all reported as text, so the desktop and the windowed
 * graphics programs are testable from the shell exactly like `date`/`vol`
 * are. Every coordinate is clamped to the framebuffer and every parse is
 * strict, so a malformed invocation is a usage diagnostic, never a crash. */
static int gfx_parse_int(const char *s, int *out) {
    long v = 0;
    int sign = 1;
    if (!s || !*s) return 0;
    if (*s == '-') { sign = -1; s++; }
    else if (*s == '+') s++;
    if (!*s) return 0;
    for (; *s; s++) {
        int d = *s - '0';
        if (d < 0 || d > 9) return 0;
        v = v * 10 + d;
        if (v > 0x7FFFFFFFL) return 0;
    }
    *out = (int)(sign * v);
    return 1;
}

/* Read the current 256-entry VGA DAC palette (3x6-bit per entry, read at 8-bit
 * precision by the kernel's normalisation). Used by `gfx shot` to turn the
 * indexed framebuffer into an RGB PPM. */
static void gfx_read_palette(unsigned char pal[768]) {
    int i;
    outb(0x3C7, 0);            /* DAC read mode, start at index 0 */
    for (i = 0; i < 768; i++)
        pal[i] = inb(0x3C9);
}

static void shell_cmd_gfx(int argc, char **argv) {
    if (argc == 1) {
        kprintf("gfx: fb %dx%d pitch %d base %lx mode %s active %d\n",
                fb_width, fb_height, fb_pitch, fb_phys_base,
                vga_mode13h ? "gfx" : "text", vga_fb_active);
        kprintf("gfx: mouse present %d at (%d,%d) buttons %d wheel %d\n",
                mouse_state.present, mouse_state.x, mouse_state.y,
                mouse_state.buttons, mouse_state.wheel);
        kprintf("gfx: term (%d,%d) %dx%d cells  minimized %d  fullscreen %d\n",
                term_x, term_y, term_cols, term_rows,
                vga_fb_is_minimized(), vga_fb_is_fullscreen());
        return;
    }
    if (kstrcmp(argv[1], "pixel") == 0) {
        int x, y;
        if (argc < 4 || !gfx_parse_int(argv[2], &x) || !gfx_parse_int(argv[3], &y)) {
            vga_puts("usage: gfx pixel <x> <y>\n");
            return;
        }
        if (x < 0 || x >= fb_width || y < 0 || y >= fb_height) {
            kprintf("gfx: pixel (%d,%d) out of range (%dx%d)\n",
                    x, y, fb_width, fb_height);
            return;
        }
        kprintf("gfx: pixel (%d,%d) = %d\n", x, y, FB_ADDR[y * fb_pitch + x]);
        return;
    }
    if (kstrcmp(argv[1], "rect") == 0) {
        int x0, y0, x1, y1, i, x, y;
        if (argc < 6 || !gfx_parse_int(argv[2], &x0) || !gfx_parse_int(argv[3], &y0) ||
            !gfx_parse_int(argv[4], &x1) || !gfx_parse_int(argv[5], &y1)) {
            vga_puts("usage: gfx rect <x0> <y0> <x1> <y1>\n");
            return;
        }
        if (x0 < 0) x0 = 0;
        if (x1 >= fb_width) x1 = fb_width - 1;
        if (y0 < 0) y0 = 0;
        if (y1 >= fb_height) y1 = fb_height - 1;
        if (x1 < x0 || y1 < y0) {
            vga_puts("gfx: rect inverted or empty\n");
            return;
        }
        {
            unsigned hist[256];
            int min = 255, max = 0, distinct = 0, top = 0, top_n = 0;
            unsigned long total = 0;
            kmemset(hist, 0, sizeof(hist));
            for (y = y0; y <= y1; y++)
                for (x = x0; x <= x1; x++)
                    hist[FB_ADDR[y * fb_pitch + x]]++;
            for (i = 0; i < 256; i++) {
                if (hist[i]) {
                    distinct++;
                    if (i < min) min = i;
                    if (i > max) max = i;
                    if ((int)hist[i] > top_n) { top_n = (int)hist[i]; top = i; }
                    total += hist[i];
                }
            }
            kprintf("gfx: rect (%d,%d)-(%d,%d): %lu px distinct %d range [%d..%d] top %d x%lu\n",
                    x0, y0, x1, y1, total, distinct, min, max, top,
                    (unsigned long)top_n);
        }
        return;
    }
    if (kstrcmp(argv[1], "shot") == 0) {
        const char *path;
        KFILE *f;
        unsigned char pal[768];
        unsigned long written = 0;
        char hdr[64];
        int i, y, n;
        if (argc < 3) { vga_puts("usage: gfx shot <file>\n"); return; }
        path = argv[2];
        f = kfopen(path, "w");
        if (!f) { kprintf("gfx: shot: cannot open %s\n", path); return; }
        gfx_read_palette(pal);
        n = ksprintf(hdr, "P6\n%d %d\n255\n", fb_width, fb_height);
        written += (unsigned long)n;
        kfwrite(hdr, 1, (unsigned long)n, f);
        for (y = 0; y < fb_height; y++) {
            for (i = 0; i < fb_width; i++) {
                unsigned idx = FB_ADDR[y * fb_pitch + i];
                unsigned char rgb[3];
                rgb[0] = pal[idx * 3 + 0];
                rgb[1] = pal[idx * 3 + 1];
                rgb[2] = pal[idx * 3 + 2];
                kfwrite(rgb, 1, 3, f);
                written += 3;
            }
        }
        kfclose(f);
        kprintf("gfx: shot %s (%lu bytes)\n", path, written);
        return;
    }
    if (kstrcmp(argv[1], "frames") == 0) {
        kprintf("gfx: frames composited %lu\n", gfx_frames_composited);
        return;
    }
    if (kstrcmp(argv[1], "palette") == 0) {
        unsigned char pal[768];
        int i;
        gfx_read_palette(pal);
        for (i = 0; i < 15; i++)
            kprintf("  %2d: %3d %3d %3d\n", i, pal[i * 3], pal[i * 3 + 1], pal[i * 3 + 2]);
        return;
    }
    vga_puts("usage: gfx [pixel <x> <y> | rect <x0> <y0> <x1> <y1> | shot <file> | frames | palette]\n");
}

/* `wm <op>` — window-manager operations on the terminal window, exposed as a
 * shell builtin so the tilin-WM behaviour (minimize/maximize/close) is
 * observable and testable over the serial console exactly like `date`/`vol`.
 * The operations are the same functions the title-bar buttons and the Alt
 * shortcuts call, so the framebuffer and the shell can never disagree. */
static void shell_cmd_wm(int argc, char **argv) {
    if (argc > 1) {
        if (kstrcmp(argv[1], "minimize") == 0) { vga_fb_toggle_minimize(); return; }
        if (kstrcmp(argv[1], "maximize") == 0) { vga_fb_toggle_fullscreen(); return; }
        if (kstrcmp(argv[1], "close") == 0) { vga_fb_close_active(); return; }
        if (kstrcmp(argv[1], "state") == 0) { /* fall through to report */ }
        else {
            vga_puts("usage: wm [minimize|maximize|close|state]\n");
            return;
        }
    }
    kprintf("wm: minimized %d fullscreen %d gfx-mode %d\n",
            vga_fb_is_minimized(), vga_fb_is_fullscreen(),
            wm_gfx_mode_active());
}

/* `hash <file>` — XXH64 (64-bit, seed 0) of a ramdisk/MiniFS file, streamed
 * in bounded chunks so a large MiniFS file never needs a whole-file buffer.
 * This is the integrity tool for CVM modules and any ramdisk payload: an
 * image built from source is compared against a recorded hash, and a module
 * that drifted is detected before it is trusted. */
static void shell_cmd_hash(int argc, char **argv) {
    KFILE *f;
    unsigned char buf[1024];
    unsigned long n;
    XXH64_state_t h;
    if (argc < 2) { vga_puts("usage: hash <file>\n"); return; }
    f = kfopen(argv[1], "r");
    if (!f) { kprintf("hash: %s: no such file\n", argv[1]); return; }
    XXH64_reset(&h, 0);
    while ((n = kfread(buf, 1, sizeof(buf), f)) > 0)
        XXH64_update(&h, buf, n);
    kfclose(f);
    kprintf("hash: %s = %016lx\n", argv[1], (unsigned long)XXH64_digest(&h));
}

static void shell_exec_builtin(int argc, char **argv) {
    if (kstrcmp(argv[0], "help") == 0) {
        vga_puts("Commands: help clear ls lsfs cat catfs echo edit rm mkdir cd pwd ps load run\n");
        vga_puts("          net trace date vol gfx wm hash unzip zip poweroff\n");
        vga_puts("  ls [dir]           list files (under the cwd by default)\n");
        vga_puts("  lsfs               list files on the MiniFS disk filesystem\n");
        vga_puts("  catfs <file>       print a file from MiniFS\n");
        vga_puts("  cd [dir] / pwd     change / print the working directory\n");
        vga_puts("  mkdir <name>       create a directory entry\n");
        vga_puts("  rm <file>          delete a ramdisk file\n");
        vga_puts("  ps                 list registered programs\n");
        vga_puts("  net                network status (rtl8139, slirp)\n");
        vga_puts("  net ping <ip>      one ICMP echo\n");
        vga_puts("  trace [on|off]     report Linux syscalls\n");
        vga_puts("  date               print the CMOS clock (HH:MM:SS)\n");
        vga_puts("  vol [0-100]        print or set the PC-speaker volume\n");
        vga_puts("  gfx [..]           graphics state / pixel / rect / shot\n");
        vga_puts("  wm [op]            window mgmt: minimize|maximize|close|state\n");
        vga_puts("  hash <file>        XXH64 checksum of a file\n");
        vga_puts("  unzip <z> [dir]    extract a ZIP archive (or -l to list)\n");
        vga_puts("  zip <out> <f...>   store files into a ZIP archive\n");
        vga_puts("  edit <file>        line editor for ramdisk files\n");
        vga_puts("  run  <name|file>   run a loaded program, ELF or .cvm module\n");
        vga_puts("  load <file>        load an ELF (.o relocatable or Linux exe)\n");
        vga_puts("  <cmd> > <file>     redirect command output to a file\n");
        vga_puts("  <cmd> [args...]    run a file or bare name (objects/bin/cvm)\n");
        vga_puts("Toolchain: edit p.c; minigcc.o p.c > p.s;\n");
        vga_puts("           ld.o -f elf -o p.elf p.s; p.elf\n");
        vga_puts("CVM:       minigcc.o w1.c > w1.s; ld.o -f cvm -o w1.cvm w1.s; w1.cvm\n");
        vga_puts("Interpreters: micropython (REPL/script), lua (REPL/script);\n");
        vga_puts("           lua src/test.lua runs the in-OS test suite (minios module)\n");
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
    else if (kstrcmp(argv[0], "perf") == 0) {
        /* Diagnose where guest time goes: raw CPU, ktime_ms overhead, and
         * console output throughput (serial + terminal render). */
        unsigned long a, b, i;
        volatile unsigned long sink = 0;
        a = ktime_ms();
        for (i = 0; i < 1000000; i++) __asm__ volatile("nop");
        b = ktime_ms();
        kprintf("perf: 1M nop = %ld ms\n", (long)(b - a));
        a = ktime_ms();
        for (i = 0; i < 100000; i++) sink += ktime_ms();
        b = ktime_ms();
        kprintf("perf: 100k ktime_ms = %ld ms\n", (long)(b - a));
        a = ktime_ms();
        for (i = 0; i < 1000; i++)
            kprintf("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n");
        b = ktime_ms();
        kprintf("perf: 1000x100-char kprintf = %ld ms\n", (long)(b - a));
        kprintf("perf: done (sink %ld)\n", (long)sink);
    }
    else if (kstrcmp(argv[0], "cat") == 0) {
        if (argc < 2) { vga_puts("usage: cat <file> [file...]\n"); return; }
        int fi;
        for (fi = 1; fi < 2; fi++) {
            char resolved[RAMDISK_FNAME_LEN];
            if (!fs_resolve(argv[fi], resolved, sizeof(resolved)) || fs_is_dir(resolved)) {
                kprintf("cat: %s: no such file or is a directory\n", argv[fi]);
                return;
            }
            KFILE *kf = kfopen(argv[fi], "r");
            if (!kf) { kprintf("cat: %s: no such file\n", argv[fi]); return; }
            char c;
            while (kfread(&c, 1, 1, kf) == 1)
                vga_putc(c);
            kfclose(kf);
        }
        vga_putc('\n');
    }
    else if (kstrcmp(argv[0], "lsfs") == 0) {
        if (!minifs_is_mounted()) { vga_puts("minifs: not mounted\n"); return; }
        int parent = MINIFS_ROOT_INODE;
        if (argc > 1) {
            parent = minifs_resolve_path(argv[1]);
            if (parent < 0) { kprintf("lsfs: %s: not found\n", argv[1]); return; }
        }
        MiniFSInode dir_inode;
        if (minifs_stat(parent, &dir_inode) < 0) return;
        if ((dir_inode.mode & 0170000) != 0040000) {
            kprintf("  %s  %u bytes\n", argv[1], dir_inode.size);
            return;
        }
        MiniFSDirEntry de;
        char name[RAMDISK_FNAME_LEN];
        int idx = 0, shown = 0;
        while (minifs_dir_read(parent, idx, &de, name) == 0) {
            if (de.inode == 0) { idx++; continue; }
            MiniFSInode st;
            minifs_stat(de.inode, &st);
            if ((st.mode & 0170000) == 0040000)
                kprintf("  %s/\n", name);
            else
                kprintf("  %-20s  %u bytes\n", name, st.size);
            shown = 1;
            idx++;
        }
        if (!shown) vga_puts("  (empty)\n");
    }
    else if (kstrcmp(argv[0], "catfs") == 0) {
        if (!minifs_is_mounted()) { vga_puts("minifs: not mounted\n"); return; }
        if (argc < 2) { vga_puts("usage: catfs <file>\n"); return; }
        int ino = minifs_resolve_path(argv[1]);
        if (ino < 0) { kprintf("catfs: %s: not found\n", argv[1]); return; }
        MiniFSInode st;
        if (minifs_stat(ino, &st) < 0) { kprintf("catfs: %s: stat failed\n", argv[1]); return; }
        unsigned sz = st.size;
        if (sz == 0) { vga_putc('\n'); return; }
        char *catfs_buf = (char *)kmalloc(sz + 1);
        if (!catfs_buf) { vga_puts("catfs: out of memory\n"); return; }
        minifs_read(ino, catfs_buf, 0, sz);
        catfs_buf[sz] = 0;
        for (unsigned i = 0; i < sz; i++) vga_putc(catfs_buf[i]);
        vga_putc('\n');
        kfree(catfs_buf);
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
    else if (kstrcmp(argv[0], "vol") == 0) {
        if (argc > 1) {
            unsigned v;
            if (!shell_parse_vol(argv[1], &v)) { vga_puts("usage: vol [0-100]\n"); return; }
            pcspk_set_volume(v);
        }
        kprintf("volume: %u%%\n", pcspk_get_volume());
    }
    else if (kstrcmp(argv[0], "date") == 0) {
        int h, m, s;
        if (rtc_read_tod(&h, &m, &s))
            kprintf("%02d:%02d:%02d\n", h, m, s);
        else
            vga_puts("date: clock unavailable\n");
    }
    else if (kstrcmp(argv[0], "sb16") == 0) {
        sb16_counters_t c;
        sb16_counters(&c);
        kprintf("sb16: present=%d mode=%d ring=%u/%u\n",
                sb16_present(), sb16_mode_active(), sb16_ring_free(),
                (unsigned)SB16_RING_CAP);
        kprintf("sb16: arms irq=%lu poll=%lu submits=%lu drops=%lu\n",
                c.irq_arms, c.poll_arms, c.submits, c.drops);
        kprintf("sb16: stalls=%lu pump_fills=%lu\n",
                c.stalls, c.pump_fills);
    }
    else if (kstrcmp(argv[0], "gfx") == 0) {
        shell_cmd_gfx(argc, argv);
    }
    else if (kstrcmp(argv[0], "wm") == 0) {
        shell_cmd_wm(argc, argv);
    }
    else if (kstrcmp(argv[0], "hash") == 0) {
        shell_cmd_hash(argc, argv);
    }
    else if (kstrcmp(argv[0], "unzip") == 0) {
        shell_cmd_unzip(argc, argv);
    }
    else if (kstrcmp(argv[0], "zip") == 0) {
        shell_cmd_zip(argc, argv);
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
        int ret = shell_run_any(argv[1], argc - 1, argv + 1);
        if (ret < 0) shell_report("run: not found: ", argv[1]);
        else shell_report_exit(ret);
    }
    else {
        int ret = shell_run_any(argv[0], argc, argv);
        if (ret < 0) shell_report("command not found: ", argv[0]);
        else shell_report_exit(ret);
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

    /* Hash (xxHash XXH64) */
    k_register_symbol("XXH64",    (void *)XXH64);

    /* stb image API (third_party/stb, PNG/TGA decode) */
    k_register_symbol("stbi_load_file", (void *)stbi_load_file);
    k_register_symbol("stbi_load_from_memory", (void *)stbi_load_from_memory);
    k_register_symbol("stbi_image_free", (void *)stbi_image_free);

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
    vga_fb_boot_config();
    mm_setup_protections();
    kprintf("fb: %dx%d pitch %d base 0x%lx\n",
            fb_width, fb_height, fb_pitch, fb_phys_base);
    kprintf("kernel: physical base 0x%x, user pages 4 KB with NX\n",
            *(unsigned *)BOOT_KASLR_ADDR);
    kprintf("isolation: user window %x..%x ring 3, syscall ABI on %x\n",
            USER_LOAD_BASE, USER_LOAD_END, SYS_KSTK_TOP);
    net_init();

    if ((unsigned long)(ramdisk_end - ramdisk_start) > 0) {
        ramdisk_setup_from(ramdisk_start, (unsigned)(ramdisk_end - ramdisk_start));
    }

    block_init();
    minifs_init();
    if (ide_present()) {
        if (minifs_mount() < 0) {
            kprintf("minifs: no filesystem found on disk\n");
        }
    }

    kprintf("Heap: %d MB  Symbols: %d  (Linux ELF: syscall ABI ready)\n",
            (int)(HEAP_SIZE >> 20), ksym_count);

    /* Initialize the scheduler: IDT, TSS, PIC, PIT timer.
     * This enables interrupts and the 100 Hz timer tick. */
    sched_init();
    kprintf("Scheduler: IDT 256 entries, TSS loaded, PIT 100 Hz, preemptive\n");

    vga_fb_init();

    /* Probe the Sound Blaster 16 for real audio; fall back to the PC speaker
     * when none is present. */
    if (sb16_init())
        kprintf("sb16: DSP probed, 8-bit %d Hz DMA channel 1\n", 22050);
    else
        kprintf("sb16: not present, PC speaker stays the audio sink\n");

    /* Wake the application processors; fail-safe, APs idle, system unchanged. */
    smp_init();

    shell_run();
}
