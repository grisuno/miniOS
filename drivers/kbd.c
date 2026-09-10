#include "kernel.h"
#include "vga_fb.h"
#include "kbd.h"

/* ================================================================
 *  Keyboard driver — PS/2 scancode set 1 (US qwerty)
 * ================================================================ */

static const unsigned char kbd_us[128] = {
    0,   0x1B, '1','2','3','4','5','6','7','8','9','0','-','=','\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0,   'a','s','d','f','g','h','j','k','l',';','\'','`',
    0,   '\\','z','x','c','v','b','n','m',',','.','/', 0,
    '*', 0,   ' ', 0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,
    0,0,0,'-',
    0,0,0,
    '+',0,0,0,0,0,
    0,0,0,
    0,0,
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

/* Spanish (Spain) qwerty layout, indexed by the same set-1 make codes.
 * Non-ASCII keys use single-byte Latin-1 codes (0xA1 ¡, 0xBF ¿, 0xB4 ´,
 * 0xA8 ¨, 0xB7 ·, 0xAA ª, 0xBA º, 0xF1 ñ, 0xD1 Ñ, 0xE7 ç, 0xC7 Ç);
 * the framebuffer font carries glyphs for these (see vga_fb.c), and the
 * serial console receives the raw Latin-1 byte. Dead keys (^ ´ ` ¨) emit
 * their spacing symbol directly: no composition is attempted. Brackets,
 * braces and @ # ~ | \ live on the AltGr layer below (Right Alt), as on
 * real hardware, so ES is fully usable for code editing. */
static const unsigned char kbd_es[128] = {
    0,   0x1B, '1','2','3','4','5','6','7','8','9','0','\'',0xA1,'\b',
    '\t','q','w','e','r','t','y','u','i','o','p','`','+','\n',
    0,   'a','s','d','f','g','h','j','k','l',0xF1,0xB4,0xBA,
    0,   0xE7,'z','x','c','v','b','n','m',',','.','-', 0,
    '*', 0,   ' ', 0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,
    0,0,0,'-',
    0,0,0,
    '+',0,0,0,0,0,
    0,0,'<',
    0,0,
    0,0,0,0,0,0,0
};

static const unsigned char kbd_es_shift[128] = {
    0,   0x1B, '!','"',0xB7,'$','%','&','/','(',')','=', '?',0xBF,'\b',
    '\t','Q','W','E','R','T','Y','U','I','O','P','^','*','\n',
    0,   'A','S','D','F','G','H','J','K','L',0xD1,0xA8,0xAA,
    0,   0xC7,'Z','X','C','V','B','N','M',';',':','_', 0,
    '*', 0,   ' ', 0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,
    0,0,0,'-',
    0,0,0,
    '+',0,0,0,0,0,
    0,0,'>',
    0,0,
    0,0,0,0,0,0,0
};

/* Spanish AltGr layer (Right Alt + key), indexed by set-1 make code.
 * This is what makes ES usable for code: brackets, braces, @ # ~ | \ and
 * the not sign live here on real hardware. A zero entry means "no AltGr
 * mapping": the key falls back to its normal/shift table entry. Only the
 * certain Spain-layout assignments are listed; € has no Latin-1 byte and
 * Dead-key composition is out of scope, so those are left out. Sparse on
 * purpose, hence designated initializers instead of the positional style
 * above (no counting, no shifted indices). */
static const unsigned char kbd_es_altgr[128] = {
    [0x02] = '|', [0x03] = '@', [0x04] = '#', [0x05] = '~',
    [0x07] = 0xAC,
    [0x1A] = '[', [0x1B] = ']',
    [0x28] = '{', [0x29] = '\\',
    [0x2B] = '}',
};

/* Active layout. EN by default; the taskbar widget and the `kbd` builtin
 * switch it at run time. Volatile: written from the mouse-tick path and
 * read from the keyboard path. */
static volatile int kbd_layout = KBD_LAYOUT_EN;

int kbd_get_layout(void) { return kbd_layout; }
void kbd_set_layout(int layout) {
    if (layout == KBD_LAYOUT_EN || layout == KBD_LAYOUT_ES)
        kbd_layout = layout;
}
void kbd_toggle_layout(void) {
    kbd_layout = (kbd_layout == KBD_LAYOUT_ES) ? KBD_LAYOUT_EN : KBD_LAYOUT_ES;
}

static int kbd_shift;
static int kbd_ctrl;
static int kbd_alt;
/* Right Alt (AltGr on ES hardware): E0 0x38 make/break, tracked separately
 * from Left Alt so the Alt+ tiling shortcuts never fire from it and EN (no
 * AltGr layer) ignores it. Cleared with the other modifiers on shell reset
 * so a held key cannot stick across a program exit. */
static int kbd_altgr;

#define KBD_QUEUE_LEN 8
#define KBD_SCAN_DEL 0x53
static unsigned char kbd_queue[KBD_QUEUE_LEN];
static int kbd_q_head, kbd_q_tail;
static int kbd_e0;

#define KBD_RAW_LEN 64
static unsigned char kbd_raw[KBD_RAW_LEN];
static int kbd_raw_head, kbd_raw_tail;
static int kbd_raw_mode;

void kbd_q_push(unsigned char c) {
    int next = (kbd_q_tail + 1) % KBD_QUEUE_LEN;
    if (next == kbd_q_head) return;
    kbd_queue[kbd_q_tail] = c;
    kbd_q_tail = next;
}

static void kbd_raw_push_internal(unsigned char c) {
    int next = (kbd_raw_tail + 1) % KBD_RAW_LEN;
    if (next == kbd_raw_head) return;
    kbd_raw[kbd_raw_tail] = c;
    kbd_raw_tail = next;
}

int kbd_q_empty(void) { return kbd_q_head == kbd_q_tail; }

int kbd_q_pop(void) {
    if (kbd_q_empty()) return -1;
    unsigned char c = kbd_queue[kbd_q_head];
    kbd_q_head = (kbd_q_head + 1) % KBD_QUEUE_LEN;
    return (int)c;
}

int kbd_available(void) {
    unsigned char s;
    __asm__ volatile("inb $0x64, %0" : "=a"(s));
    return (s & 1) && !(s & 0x20);
}

int kbd_raw_mode_get(void) { return kbd_raw_mode; }
void kbd_raw_mode_set(int on) { kbd_raw_mode = on; }
int kbd_raw_empty(void) { return kbd_raw_head == kbd_raw_tail; }
int kbd_raw_pop(void) {
    if (kbd_raw_head == kbd_raw_tail) return -1;
    unsigned char c = kbd_raw[kbd_raw_head];
    kbd_raw_head = (kbd_raw_head + 1) % KBD_RAW_LEN;
    return (int)c;
}
void kbd_raw_push_byte(unsigned char c) { kbd_raw_push_internal(c); }
int kbd_e0_get(void) { return kbd_e0; }
void kbd_e0_set(int v) { kbd_e0 = v; }
void kbd_flush_all(void) {
    kbd_q_head = kbd_q_tail = 0;
    kbd_raw_head = kbd_raw_tail = 0;
}

int kbd_read(void) {
    if (!kbd_q_empty()) return kbd_q_pop();
    while (!kbd_available()) __asm__ volatile("pause");
    unsigned char sc;
    __asm__ volatile("inb $0x60, %0" : "=a"(sc));

    if (kbd_raw_mode) {
        if (sc == KEY_E0) { kbd_e0 = 1; return -1; }
        if (kbd_e0) {
            kbd_e0 = 0;
            kbd_raw_push_internal(0xE0); kbd_raw_push_internal(sc);
            return -1;
        }
        kbd_raw_push_internal(sc);
        return -1;
    }

    if (sc == KEY_E0) { kbd_e0 = 1; return -1; }

    if (sc & 0x80) {
        sc &= 0x7F;
        if (sc == KEY_LSHIFT || sc == KEY_RSHIFT) kbd_shift = 0;
        if (sc == KEY_LCTRL) kbd_ctrl = 0;
        if (sc == KEY_LALT) kbd_alt = 0;
        if (kbd_e0 && sc == KEY_RALT) kbd_altgr = 0;
        kbd_e0 = 0;
        return -1;
    }

    if (kbd_e0) {
        kbd_e0 = 0;
        if (sc == KEY_RALT) { kbd_altgr = 1; return -1; }
        if (kbd_ctrl && vga_fb_active) {
            if (sc == KEY_UP)       { vga_fb_move_terminal(0, -1); return -1; }
            if (sc == KEY_DOWN)     { vga_fb_move_terminal(0,  1); return -1; }
            if (sc == KEY_LEFT)     { vga_fb_move_terminal(-1, 0); return -1; }
            if (sc == KEY_RIGHT)    { vga_fb_move_terminal( 1, 0); return -1; }
        }
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
        } else if (sc == KBD_SCAN_DEL) {
            kbd_q_push(KEY_ESC); kbd_q_push(KEY_CSI);
            kbd_q_push('3'); kbd_q_push(KEY_TILDE);
        }
        return -1;
    }

    if (sc == KEY_LSHIFT || sc == KEY_RSHIFT) { kbd_shift = 1; return -1; }
    if (sc == KEY_LCTRL) { kbd_ctrl = 1; return -1; }
    if (sc == KEY_LALT) { kbd_alt = 1; return -1; }

    if (vga_fb_active) {
        if (sc == KEY_F11) { vga_fb_toggle_fullscreen(); return -1; }
        if (sc == KEY_F5)  { vga_fb_move_terminal(0, 0); return -1; }
    }

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

    {
        const unsigned char *tab = (kbd_layout == KBD_LAYOUT_ES) ? kbd_es : kbd_us;
        const unsigned char *stab = (kbd_layout == KBD_LAYOUT_ES) ? kbd_es_shift : kbd_us_shift;
        /* ES AltGr layer wins over shift when it defines the key (code
         * characters, never letters, so the Ctrl+letter fold below cannot
         * misfire on them). EN has no AltGr layer: Right Alt is inert. */
        if (kbd_altgr && kbd_layout == KBD_LAYOUT_ES && kbd_es_altgr[sc])
            return kbd_es_altgr[sc];
        int ch = kbd_shift ? stab[sc] : tab[sc];
        if (kbd_ctrl && ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))) {
            int lower = (ch >= 'A' && ch <= 'Z') ? ch - 'A' + 'a' : ch;
            return lower - 'a' + 1;
        }
        return ch;
    }
}

void kbd_reset_for_shell(void) {
    kbd_raw_mode = 0;
    kbd_altgr = 0;
    kbd_q_head = kbd_q_tail = 0;
    kbd_raw_head = kbd_raw_tail = 0;
    kbd_e0 = 0;
}
