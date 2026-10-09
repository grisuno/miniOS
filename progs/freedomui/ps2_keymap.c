/** ps2_keymap.c - pure PS/2 set 1 scancode to keysym translator (US layout).
 *
 * Contract in ps2_keymap.h and docs/spec/network.md (freedom-gui). Keysym
 * values are the X11/xkb ones; text follows xkb: control keys produce their
 * C0 byte, letters follow Shift XOR Caps Lock, and any Ctrl or Alt chord
 * produces no text so a shortcut can never type into a field.
 */
#include "ps2_keymap.h"

#include <stddef.h>
#include <string.h>

#define PS2_PREFIX_EXTENDED 0xE0u
#define PS2_PREFIX_PAUSE    0xE1u
#define PS2_PAUSE_TAIL      5
#define PS2_BREAK_BIT       0x80u
#define PS2_CODE_MASK       0x7Fu
#define PS2_TABLE_SIZE      0x80u

#define PS2_HELD_LSHIFT 0x01u
#define PS2_HELD_RSHIFT 0x02u
#define PS2_HELD_LCTRL  0x04u
#define PS2_HELD_RCTRL  0x08u
#define PS2_HELD_LALT   0x10u
#define PS2_HELD_RALT   0x20u

#define SC_ESCAPE    0x01u
#define SC_BACKSPACE 0x0Eu
#define SC_TAB       0x0Fu
#define SC_RETURN    0x1Cu
#define SC_CTRL      0x1Du
#define SC_LSHIFT    0x2Au
#define SC_RSHIFT    0x36u
#define SC_KP_MUL    0x37u
#define SC_ALT       0x38u
#define SC_CAPS      0x3Au
#define SC_F1        0x3Bu
#define SC_F10       0x44u
#define SC_NUMLOCK   0x45u
#define SC_SCROLL    0x46u
#define SC_KP_FIRST  0x47u
#define SC_KP_LAST   0x53u
#define SC_F11       0x57u
#define SC_F12       0x58u
#define SC_E0_KP_DIV 0x35u
#define SC_E0_PRINT  0x37u
#define SC_E0_HOME   0x47u
#define SC_E0_UP     0x48u
#define SC_E0_PRIOR  0x49u
#define SC_E0_LEFT   0x4Bu
#define SC_E0_RIGHT  0x4Du
#define SC_E0_END    0x4Fu
#define SC_E0_DOWN   0x50u
#define SC_E0_NEXT   0x51u
#define SC_E0_INSERT 0x52u
#define SC_E0_DELETE 0x53u
#define SC_E0_SUPERL 0x5Bu
#define SC_E0_SUPERR 0x5Cu
#define SC_E0_MENU   0x5Du

#define KS_F1          0xffbeu
#define KS_F11         0xffc8u
#define KS_INSERT      0xff63u
#define KS_PRINT       0xff61u
#define KS_MENU        0xff67u
#define KS_SCROLL_LOCK 0xff14u
#define KS_NUM_LOCK    0xff7fu
#define KS_SUPER_L     0xffebu
#define KS_SUPER_R     0xffecu
#define KS_KP_HOME     0xff95u
#define KS_KP_LEFT     0xff96u
#define KS_KP_UP       0xff97u
#define KS_KP_RIGHT    0xff98u
#define KS_KP_DOWN     0xff99u
#define KS_KP_PRIOR    0xff9au
#define KS_KP_NEXT     0xff9bu
#define KS_KP_END      0xff9cu
#define KS_KP_BEGIN    0xff9du
#define KS_KP_INSERT   0xff9eu
#define KS_KP_MULTIPLY 0xffaau
#define KS_KP_DECIMAL  0xffaeu
#define KS_KP_DIVIDE   0xffafu

#define ASCII_BS  0x08
#define ASCII_TAB 0x09
#define ASCII_CR  0x0d
#define ASCII_ESC 0x1b
#define ASCII_DEL 0x7f

/* Printable keys of the main block, unshifted and shifted. */
static const char ps2_plain[PS2_TABLE_SIZE] = {
    [0x02] = '1', [0x03] = '2', [0x04] = '3', [0x05] = '4', [0x06] = '5',
    [0x07] = '6', [0x08] = '7', [0x09] = '8', [0x0A] = '9', [0x0B] = '0',
    [0x0C] = '-', [0x0D] = '=',
    [0x10] = 'q', [0x11] = 'w', [0x12] = 'e', [0x13] = 'r', [0x14] = 't',
    [0x15] = 'y', [0x16] = 'u', [0x17] = 'i', [0x18] = 'o', [0x19] = 'p',
    [0x1A] = '[', [0x1B] = ']',
    [0x1E] = 'a', [0x1F] = 's', [0x20] = 'd', [0x21] = 'f', [0x22] = 'g',
    [0x23] = 'h', [0x24] = 'j', [0x25] = 'k', [0x26] = 'l', [0x27] = ';',
    [0x28] = '\'', [0x29] = '`', [0x2B] = '\\',
    [0x2C] = 'z', [0x2D] = 'x', [0x2E] = 'c', [0x2F] = 'v', [0x30] = 'b',
    [0x31] = 'n', [0x32] = 'm', [0x33] = ',', [0x34] = '.', [0x35] = '/',
    [0x39] = ' ',
};

static const char ps2_shifted[PS2_TABLE_SIZE] = {
    [0x02] = '!', [0x03] = '@', [0x04] = '#', [0x05] = '$', [0x06] = '%',
    [0x07] = '^', [0x08] = '&', [0x09] = '*', [0x0A] = '(', [0x0B] = ')',
    [0x0C] = '_', [0x0D] = '+',
    [0x10] = 'Q', [0x11] = 'W', [0x12] = 'E', [0x13] = 'R', [0x14] = 'T',
    [0x15] = 'Y', [0x16] = 'U', [0x17] = 'I', [0x18] = 'O', [0x19] = 'P',
    [0x1A] = '{', [0x1B] = '}',
    [0x1E] = 'A', [0x1F] = 'S', [0x20] = 'D', [0x21] = 'F', [0x22] = 'G',
    [0x23] = 'H', [0x24] = 'J', [0x25] = 'K', [0x26] = 'L', [0x27] = ':',
    [0x28] = '"', [0x29] = '~', [0x2B] = '|',
    [0x2C] = 'Z', [0x2D] = 'X', [0x2E] = 'C', [0x2F] = 'V', [0x30] = 'B',
    [0x31] = 'N', [0x32] = 'M', [0x33] = '<', [0x34] = '>', [0x35] = '?',
    [0x39] = ' ',
};

/* Keypad 0x47..0x53: keysym and text with Num Lock on, keysym with it off. */
typedef struct ps2_keypad {
    uint32_t num_sym;
    char     num_text;
    uint32_t nav_sym;
} ps2_keypad;

static const ps2_keypad ps2_keypad_map[SC_KP_LAST - SC_KP_FIRST + 1] = {
    { 0xffb7u, '7', KS_KP_HOME },
    { 0xffb8u, '8', KS_KP_UP },
    { 0xffb9u, '9', KS_KP_PRIOR },
    { KE_KEY_KP_Subtract, '-', KE_KEY_KP_Subtract },
    { 0xffb4u, '4', KS_KP_LEFT },
    { 0xffb5u, '5', KS_KP_BEGIN },
    { 0xffb6u, '6', KS_KP_RIGHT },
    { KE_KEY_KP_Add, '+', KE_KEY_KP_Add },
    { 0xffb1u, '1', KS_KP_END },
    { 0xffb2u, '2', KS_KP_DOWN },
    { 0xffb3u, '3', KS_KP_NEXT },
    { KE_KEY_KP_0, '0', KS_KP_INSERT },
    { KS_KP_DECIMAL, '.', KE_KEY_KP_Delete },
};

void ps2_init(ps2_state *s) {
    if (s == NULL) return;
    memset(s, 0, sizeof *s);
    s->num_lock = 1;
}

static unsigned held_mods(const ps2_state *s) {
    unsigned m = 0;
    if (s->held & (PS2_HELD_LSHIFT | PS2_HELD_RSHIFT)) m |= KE_MOD_SHIFT;
    if (s->held & (PS2_HELD_LCTRL | PS2_HELD_RCTRL)) m |= KE_MOD_CTRL;
    if (s->held & (PS2_HELD_LALT | PS2_HELD_RALT)) m |= KE_MOD_ALT;
    return m;
}

static void set_text(ps2_key *k, char c) {
    k->text[0] = c;
    k->text[1] = '\0';
    k->text_len = 1;
}

static int is_letter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

/* Modifier and lock keys: update the held state; returns the keysym or 0. */
static uint32_t modifier_key(ps2_state *s, unsigned code, int extended, int make) {
    unsigned bit = 0;
    uint32_t sym = 0;
    if (!extended && code == SC_LSHIFT) { bit = PS2_HELD_LSHIFT; sym = KE_KEY_Shift_L; }
    else if (!extended && code == SC_RSHIFT) { bit = PS2_HELD_RSHIFT; sym = KE_KEY_Shift_R; }
    else if (code == SC_CTRL) {
        bit = extended ? PS2_HELD_RCTRL : PS2_HELD_LCTRL;
        sym = extended ? KE_KEY_Control_R : KE_KEY_Control_L;
    } else if (code == SC_ALT) {
        bit = extended ? PS2_HELD_RALT : PS2_HELD_LALT;
        sym = extended ? KE_KEY_Alt_R : KE_KEY_Alt_L;
    } else if (!extended && code == SC_CAPS) {
        if (make) s->caps_lock = !s->caps_lock;
        return KE_KEY_Caps_Lock;
    } else if (!extended && code == SC_NUMLOCK) {
        if (make) s->num_lock = !s->num_lock;
        return KS_NUM_LOCK;
    } else {
        return 0;
    }
    if (make) s->held |= bit;
    else      s->held &= ~bit;
    return sym;
}

/* Keys behind E0 that are not modifiers. */
static uint32_t extended_key(unsigned code, ps2_key *k) {
    switch (code) {
    case SC_RETURN:    set_text(k, ASCII_CR); return KE_KEY_KP_Enter;
    case SC_E0_KP_DIV: set_text(k, '/'); return KS_KP_DIVIDE;
    case SC_E0_PRINT:  return KS_PRINT;
    case SC_E0_HOME:   return KE_KEY_Home;
    case SC_E0_UP:     return KE_KEY_Up;
    case SC_E0_PRIOR:  return KE_KEY_Page_Up;
    case SC_E0_LEFT:   return KE_KEY_Left;
    case SC_E0_RIGHT:  return KE_KEY_Right;
    case SC_E0_END:    return KE_KEY_End;
    case SC_E0_DOWN:   return KE_KEY_Down;
    case SC_E0_NEXT:   return KE_KEY_Page_Down;
    case SC_E0_INSERT: return KS_INSERT;
    case SC_E0_DELETE: set_text(k, (char)ASCII_DEL); return KE_KEY_Delete;
    case SC_E0_SUPERL: return KS_SUPER_L;
    case SC_E0_SUPERR: return KS_SUPER_R;
    case SC_E0_MENU:   return KS_MENU;
    default:           return 0;
    }
}

/* Keys without a prefix that are not modifiers. */
static uint32_t plain_key(const ps2_state *s, unsigned code, ps2_key *k) {
    int shift = (s->held & (PS2_HELD_LSHIFT | PS2_HELD_RSHIFT)) != 0;
    switch (code) {
    case SC_ESCAPE:    set_text(k, ASCII_ESC); return KE_KEY_Escape;
    case SC_BACKSPACE: set_text(k, ASCII_BS); return KE_KEY_BackSpace;
    case SC_TAB:
        if (shift) return KE_KEY_ISO_Left_Tab;
        set_text(k, ASCII_TAB);
        return KE_KEY_Tab;
    case SC_RETURN:    set_text(k, ASCII_CR); return KE_KEY_Return;
    case SC_KP_MUL:    set_text(k, '*'); return KS_KP_MULTIPLY;
    case SC_SCROLL:    return KS_SCROLL_LOCK;
    case SC_F11:       return KS_F11;
    case SC_F12:       return KE_KEY_F12;
    default:           break;
    }
    if (code >= SC_F1 && code <= SC_F10) return KS_F1 + (code - SC_F1);
    if (code >= SC_KP_FIRST && code <= SC_KP_LAST) {
        const ps2_keypad *kp = &ps2_keypad_map[code - SC_KP_FIRST];
        int numeric = s->num_lock || kp->num_sym == kp->nav_sym;
        if (!numeric) return kp->nav_sym;
        set_text(k, kp->num_text);
        return kp->num_sym;
    }
    if (code < PS2_TABLE_SIZE && ps2_plain[code] != '\0') {
        char c = ps2_plain[code];
        int upper = shift;
        if (is_letter(c) && s->caps_lock) upper = !upper;
        if (upper) c = ps2_shifted[code];
        set_text(k, c);
        return (uint32_t)(unsigned char)c;
    }
    return 0;
}

int ps2_feed(ps2_state *s, uint8_t byte, ps2_key *out) {
    if (s == NULL || out == NULL) return PS2_EV_NONE;
    if (s->skip > 0) { s->skip--; return PS2_EV_NONE; }
    if (byte == PS2_PREFIX_PAUSE) { s->skip = PS2_PAUSE_TAIL; s->extended = 0; return PS2_EV_NONE; }
    if (byte == PS2_PREFIX_EXTENDED) { s->extended = 1; return PS2_EV_NONE; }

    int extended = s->extended;
    s->extended = 0;
    int make = (byte & PS2_BREAK_BIT) == 0;
    unsigned code = byte & PS2_CODE_MASK;
    if (code == 0) return PS2_EV_NONE;

    ps2_key k;
    memset(&k, 0, sizeof k);
    k.mods = held_mods(s);
    k.code = code | (extended ? PS2_CODE_EXTENDED : 0u);
    k.sym = modifier_key(s, code, extended, make);
    if (k.sym == 0)
        k.sym = extended ? extended_key(code, &k) : plain_key(s, code, &k);
    if (k.sym == 0) return PS2_EV_NONE;
    if (!make || (k.mods & (KE_MOD_CTRL | KE_MOD_ALT))) {
        k.text[0] = '\0';
        k.text_len = 0;
    }
    *out = k;
    return make ? PS2_EV_PRESS : PS2_EV_RELEASE;
}
