#include "kernel.h"
#include "sched.h"
#include "vga_fb.h"
#include "kbd.h"
#include "modifiers.h"
#include "wm_events.h"

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

/** Docstring: Single modifier state shared by cooked and raw paths. */
static modifier_state_t kbd_mods;
static const modifier_keys_t kbd_keys = {
    KEY_LSHIFT, KEY_RSHIFT, KEY_LCTRL, KEY_LALT, KEY_RALT,
    KEY_SUPER_L, KEY_SUPER_R
};
#define kbd_shift (kbd_mods.shift)
#define kbd_ctrl (kbd_mods.ctrl)
#define kbd_alt (kbd_mods.alt)
#define kbd_super (kbd_mods.super)
#define kbd_altgr (kbd_mods.altgr)

#define KBD_QUEUE_LEN 8
#define KBD_SCAN_DEL 0x53
static unsigned char kbd_queue[KBD_QUEUE_LEN];
static int kbd_q_head, kbd_q_tail;
static int kbd_e0;

/** Docstring: Full-queue drop counters observable via wm state. */
static unsigned long kbd_drop_cooked;
static unsigned long kbd_drop_raw;

/** Docstring: Report cooked and raw queue drop counters. */
void kbd_drop_counts(unsigned long *cooked, unsigned long *raw) {
    if (cooked != 0) {
        *cooked = kbd_drop_cooked;
    }
    if (raw != 0) {
        *raw = kbd_drop_raw;
    }
}

#define KBD_RAW_LEN 64
static unsigned char kbd_raw[KBD_RAW_LEN];
static int kbd_raw_head, kbd_raw_tail;
static int kbd_raw_mode;

void kbd_q_push(unsigned char c) {
    int next = (kbd_q_tail + 1) % KBD_QUEUE_LEN;
    if (next == kbd_q_head) {
        kbd_drop_cooked++;
        return;
    }
    kbd_queue[kbd_q_tail] = c;
    kbd_q_tail = next;
}

static void kbd_raw_push_internal(unsigned char c) {
    int next = (kbd_raw_tail + 1) % KBD_RAW_LEN;
    if (next == kbd_raw_head) {
        kbd_drop_raw++;
        return;
    }
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

/* Drop queued raw scancodes (shell-typed while a terminal owned PS/2) so a
 * newly focused game never replays them as input. Cooked shell keys stay. */
void kbd_raw_flush(void) {
    kbd_raw_head = kbd_raw_tail = 0;
}

/* ---- Raw-path WM filter (shared core) ----
 *
 * A ring-3 graphics program (DOOM, Quake, Nuklear, piano) reads raw PS/2
 * scancodes through SYS_KBD / the raw queue, bypassing the cooked
 * translation below where Alt-Tab / Super-Tab live. Without interception
 * here the WM dies the moment a game owns the keyboard. raw_track_mods
 * keeps the modifier state in sync on both paths (the old raw branch never
 * tracked Alt/Super, so a modifier held across raw mode stuck forever);
 * wm_raw_combo performs the WM action and reports 1 when the byte must be
 * swallowed. Deliberately narrower than the cooked set: bare keys (Tab,
 * F11/F5, arrows) always reach the game, and Alt+arrows stay with the game
 * too (DOOM strafes with Alt+arrows); Super is never a game key, so the
 * full Super set plus Alt+Tab / Alt+Enter / Alt+M,X,Q / Alt+[/]-/=/0 work
 * raw. A swallowed Tab make also swallows its break (same flag as cooked
 * would need, kept here beside the consumer). */
static int wm_raw_swallow_tab_break;

static int raw_track_mods(int code, int brk, int e0) {
    return modifiers_update(&kbd_keys, &kbd_mods, code, brk, e0);
}

/** Docstring: Dispatch one looked-up WM combo to the window manager. */
static int wm_combo_dispatch(int action, int zone)
{
    if (!vga_fb_active) {
        return 0;
    }
    if (action == WM_COMBO_FOCUS_NEXT) {
        vga_fb_focus_next();
        return 1;
    }
    if (action == WM_COMBO_TILE_ALL) {
        vga_fb_tile_all();
        return 1;
    }
    if (action == WM_COMBO_FULLSCREEN) {
        vga_fb_toggle_fullscreen();
        return 1;
    }
    if (action == WM_COMBO_MINIMIZE) {
        vga_fb_toggle_minimize();
        return 1;
    }
    if (action == WM_COMBO_CLOSE) {
        vga_fb_close_active();
        return 1;
    }
    if (action == WM_COMBO_SNAP) {
        vga_fb_snap_window(zone);
        return 1;
    }
    if (action == WM_COMBO_RESIZE_DEC_W) {
        vga_fb_resize(-1, 0);
        return 1;
    }
    if (action == WM_COMBO_RESIZE_INC_W) {
        vga_fb_resize(1, 0);
        return 1;
    }
    if (action == WM_COMBO_RESIZE_DEC_BOTH) {
        vga_fb_resize(-1, -1);
        return 1;
    }
    if (action == WM_COMBO_RESIZE_INC_BOTH) {
        vga_fb_resize(1, 1);
        return 1;
    }
    if (action == WM_COMBO_RESET) {
        vga_fb_reset_default();
        return 1;
    }
    return 0;
}

static int wm_raw_combo(int code, int e0) {
    int zone = 0;
    int action;
    if (!vga_fb_active) return 0;
    action = wm_combo_lookup_mods(&kbd_mods, e0 ? 1 : 0, code, WM_PATH_RAW, &zone);
    if (action == WM_COMBO_NONE) {
        return 0;
    }
    if (action == WM_COMBO_FOCUS_NEXT || action == WM_COMBO_TILE_ALL) {
        wm_raw_swallow_tab_break = 1;
    }
    return wm_combo_dispatch(action, zone);
}

/* SYS_KBD raw-path filter (one byte per syscall). Owns the E0 flag on this
 * path: the 0xE0 prefix was already delivered to the app on the previous
 * call, so when Alt/Super is held the prefix is held back (e0 == 2) instead
 * — swallowing the pair avoids a stray 0xE0 that would wedge a game's key
 * pump waiting for a second byte that never comes. A held-back prefix whose
 * second byte is not a WM combo is delivered bare (keypad alias): games map
 * both, so play survives. Returns 1 when sc must be swallowed. */
int kbd_sys_raw_filter(unsigned char sc) {
    int brk, code, e0;
    if (sc == KEY_E0) {
        if (kbd_alt || kbd_super) { kbd_e0 = 2; return 1; }
        kbd_e0 = 1;
        return 0;
    }
    brk = (sc & 0x80) ? 1 : 0;
    code = sc & 0x7F;
    e0 = kbd_e0;
    kbd_e0 = 0;
    if (raw_track_mods(code, brk, e0 != 0)) return 0;
    if (brk) {
        if (e0 == 0 && code == KEY_TAB && wm_raw_swallow_tab_break) {
            wm_raw_swallow_tab_break = 0;
            return 1;
        }
        return 0;
    }
    return wm_raw_combo(code, e0 != 0);
}

int kbd_read(void) {
    /* Not the PS/2 owner (bg gfx focused while the shell polls, or vice
     * versa): touch no hardware, drop stale shell keys. The serial path
     * in raw_try/blocking_getc is untouched, so the serial console stays
     * a shell console at every focus. */
    if (!vga_fb_ps2_owner(current_pid)) {
        while (!kbd_q_empty()) kbd_q_pop();
        return -1;
    }
    if (!kbd_q_empty()) return kbd_q_pop();
    while (!kbd_available()) __asm__ volatile("pause");
    unsigned char sc;
    __asm__ volatile("inb $0x60, %0" : "=a"(sc));

    /* Raw fill only for non-shell owners (a bg/fg proc reading through
     * GETC_RAW with raw mode on). The shell itself (pid 0, alive) always
     * takes the cooked translation below, so a background raw game can
     * never deafen the shell's PS/2 input by flipping the global mode. */
    if (kbd_raw_mode && (user_program_active || current_pid != 0)) {
        int brk = (sc & 0x80) ? 1 : 0;
        int code = sc & 0x7F;
        int e0;
        if (sc == KEY_E0) { kbd_e0 = 1; return -1; }
        e0 = kbd_e0;
        kbd_e0 = 0;
        if (raw_track_mods(code, brk, e0)) {
            if (e0) kbd_raw_push_internal(0xE0);
            kbd_raw_push_internal(sc);
            return -1;
        }
        if (brk) {
            if (!e0 && code == KEY_TAB && wm_raw_swallow_tab_break) {
                wm_raw_swallow_tab_break = 0;
                return -1;
            }
            if (e0) kbd_raw_push_internal(0xE0);
            kbd_raw_push_internal(sc);
            return -1;
        }
        if (wm_raw_combo(code, e0)) return -1;
        if (e0) kbd_raw_push_internal(0xE0);
        kbd_raw_push_internal(sc);
        return -1;
    }

    if (sc == KEY_E0) { kbd_e0 = 1; return -1; }

    if (sc & 0x80) {
        sc &= 0x7F;
        modifiers_update(&kbd_keys, &kbd_mods, sc, 1, kbd_e0);
        kbd_e0 = 0;
        return -1;
    }

    if (kbd_e0) {
        int zone = 0;
        int action;
        kbd_e0 = 0;
        if (modifiers_update(&kbd_keys, &kbd_mods, sc, 0, 1)) return -1;
        if (kbd_ctrl && vga_fb_active) {
            if (sc == KEY_UP)       { vga_fb_move_terminal(0, -1); return -1; }
            if (sc == KEY_DOWN)     { vga_fb_move_terminal(0,  1); return -1; }
            if (sc == KEY_LEFT)     { vga_fb_move_terminal(-1, 0); return -1; }
            if (sc == KEY_RIGHT)    { vga_fb_move_terminal( 1, 0); return -1; }
        }
        action = wm_combo_lookup_mods(&kbd_mods, 1, sc, WM_PATH_COOKED, &zone);
        if (action != WM_COMBO_NONE) {
            if (wm_combo_dispatch(action, zone)) return -1;
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

    if (modifiers_update(&kbd_keys, &kbd_mods, sc, 0, 0)) return -1;
    {
        int zone = 0;
        int action = wm_combo_lookup_mods(&kbd_mods, 0, sc, WM_PATH_COOKED, &zone);
        if (action != WM_COMBO_NONE) {
            if (wm_combo_dispatch(action, zone)) return -1;
        }
    }

    if (vga_fb_active) {
        if (sc == KEY_F11) { vga_fb_toggle_fullscreen(); return -1; }
        if (sc == KEY_F5)  { vga_fb_move_terminal(0, 0); return -1; }
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
    modifiers_init(&kbd_mods);
    wm_raw_swallow_tab_break = 0;
    kbd_q_head = kbd_q_tail = 0;
    kbd_raw_head = kbd_raw_tail = 0;
    kbd_e0 = 0;
}
