/** test_ps2_keymap - host suite for the PS/2 set 1 to keysym translator.
 *
 * Covers progs/freedomui/ps2_keymap.c: keysym values pinned to xkbcommon,
 * letters with Shift and Caps Lock, punctuation, the xkb text of control
 * keys, Ctrl/Alt chords without text, extended (E0) keys, the keypad under
 * both Num Lock states, the fake shifts of Print Screen, the E1 Pause
 * sequence, release events and fail-closed arguments. Exit nonzero on the
 * first failure.
 */
#include <stdio.h>
#include <string.h>
#include <xkbcommon/xkbcommon-keysyms.h>

#include "../progs/freedomui/ps2_keymap.h"

static int fails;

/** Report helper for single check lines. */
static void check(int cond, const char *name) {
    if (!cond) {
        printf("FAIL: %s\n", name);
        fails++;
        return;
    }
    printf("PASS: %s\n", name);
}

/** Feeds a byte sequence and returns the kind of the last event. */
static int feed_seq(ps2_state *s, const unsigned char *seq, int n, ps2_key *out) {
    int kind = PS2_EV_NONE;
    for (int i = 0; i < n; i++) kind = ps2_feed(s, seq[i], out);
    return kind;
}

/** Presses one non-extended make code and returns the event kind. */
static int press(ps2_state *s, unsigned char code, ps2_key *out) {
    return ps2_feed(s, code, out);
}

/** Releases one non-extended code (break = make | 0x80). */
static int release(ps2_state *s, unsigned char code, ps2_key *out) {
    return ps2_feed(s, (unsigned char)(code | 0x80), out);
}

static void test_letters_and_shift(void) {
    ps2_state s;
    ps2_key k;
    ps2_init(&s);
    check(press(&s, 0x1E, &k) == PS2_EV_PRESS, "a press is a press");
    check(k.sym == XKB_KEY_a && k.text_len == 1 && strcmp(k.text, "a") == 0, "a sym and text");
    check(k.mods == 0, "a without modifiers");
    check(release(&s, 0x1E, &k) == PS2_EV_RELEASE && k.sym == XKB_KEY_a, "a release");
    check(k.text_len == 0 && k.text[0] == '\0', "release carries no text");
    press(&s, 0x2A, &k);
    check(k.sym == XKB_KEY_Shift_L && k.text_len == 0, "left shift sym");
    press(&s, 0x1E, &k);
    check(k.sym == XKB_KEY_A && strcmp(k.text, "A") == 0, "shift a gives A");
    check(k.mods == KE_MOD_SHIFT, "shift a mods");
    release(&s, 0x2A, &k);
    press(&s, 0x36, &k);
    check(k.sym == XKB_KEY_Shift_R, "right shift sym");
    press(&s, 0x26, &k);
    check(k.sym == XKB_KEY_L, "right shift l gives L");
    release(&s, 0x36, &k);
    press(&s, 0x26, &k);
    check(k.sym == XKB_KEY_l && k.mods == 0, "shift released");
}

static void test_caps_lock(void) {
    ps2_state s;
    ps2_key k;
    ps2_init(&s);
    press(&s, 0x3A, &k);
    check(k.sym == XKB_KEY_Caps_Lock, "caps lock sym");
    release(&s, 0x3A, &k);
    press(&s, 0x1E, &k);
    check(k.sym == XKB_KEY_A && strcmp(k.text, "A") == 0, "caps a gives A");
    press(&s, 0x02, &k);
    check(k.sym == XKB_KEY_1 && strcmp(k.text, "1") == 0, "caps leaves digits");
    press(&s, 0x2A, &k);
    press(&s, 0x1E, &k);
    check(k.sym == XKB_KEY_a && strcmp(k.text, "a") == 0, "caps xor shift gives a");
    release(&s, 0x2A, &k);
    press(&s, 0x3A, &k);
    release(&s, 0x3A, &k);
    press(&s, 0x1E, &k);
    check(k.sym == XKB_KEY_a, "caps toggled off");
}

static void test_punctuation(void) {
    ps2_state s;
    ps2_key k;
    ps2_init(&s);
    press(&s, 0x0C, &k);
    check(k.sym == XKB_KEY_minus && strcmp(k.text, "-") == 0, "minus");
    press(&s, 0x0D, &k);
    check(k.sym == XKB_KEY_equal && strcmp(k.text, "=") == 0, "equal");
    press(&s, 0x39, &k);
    check(k.sym == XKB_KEY_space && strcmp(k.text, " ") == 0, "space");
    press(&s, 0x2A, &k);
    press(&s, 0x0D, &k);
    check(k.sym == XKB_KEY_plus && strcmp(k.text, "+") == 0, "shift equal gives plus");
    press(&s, 0x0C, &k);
    check(k.sym == XKB_KEY_underscore && strcmp(k.text, "_") == 0, "shift minus gives underscore");
    press(&s, 0x02, &k);
    check(k.sym == XKB_KEY_exclam && strcmp(k.text, "!") == 0, "shift 1 gives exclam");
    press(&s, 0x28, &k);
    check(k.sym == XKB_KEY_quotedbl && strcmp(k.text, "\"") == 0, "shift quote gives quotedbl");
}

static void test_control_key_text(void) {
    ps2_state s;
    ps2_key k;
    ps2_init(&s);
    press(&s, 0x01, &k);
    check(k.sym == XKB_KEY_Escape && k.text_len == 1 && k.text[0] == 0x1b, "escape text");
    press(&s, 0x0E, &k);
    check(k.sym == XKB_KEY_BackSpace && k.text_len == 1 && k.text[0] == '\b', "backspace text");
    press(&s, 0x0F, &k);
    check(k.sym == XKB_KEY_Tab && k.text_len == 1 && k.text[0] == '\t', "tab text");
    press(&s, 0x1C, &k);
    check(k.sym == XKB_KEY_Return && k.text_len == 1 && k.text[0] == '\r', "return text");
    press(&s, 0x2A, &k);
    press(&s, 0x0F, &k);
    check(k.sym == XKB_KEY_ISO_Left_Tab && k.text_len == 0, "shift tab is iso left tab");
}

static void test_chords_have_no_text(void) {
    ps2_state s;
    ps2_key k;
    ps2_init(&s);
    press(&s, 0x1D, &k);
    check(k.sym == XKB_KEY_Control_L, "left ctrl sym");
    press(&s, 0x26, &k);
    check(k.sym == XKB_KEY_l && k.text_len == 0 && k.mods == KE_MOD_CTRL, "ctrl l no text");
    press(&s, 0x2A, &k);
    press(&s, 0x26, &k);
    check(k.sym == XKB_KEY_L && k.mods == (KE_MOD_CTRL | KE_MOD_SHIFT), "ctrl shift l");
    release(&s, 0x2A, &k);
    release(&s, 0x1D, &k);
    press(&s, 0x38, &k);
    check(k.sym == XKB_KEY_Alt_L, "left alt sym");
    press(&s, 0x1C, &k);
    check(k.sym == XKB_KEY_Return && k.text_len == 0 && k.mods == KE_MOD_ALT, "alt return no text");
    release(&s, 0x38, &k);
    press(&s, 0x1E, &k);
    check(k.mods == 0 && k.text_len == 1, "alt released");
}

static void test_extended_keys(void) {
    ps2_state s;
    ps2_key k;
    const unsigned char up[] = { 0xE0, 0x48 };
    const unsigned char up_rel[] = { 0xE0, 0xC8 };
    const unsigned char del[] = { 0xE0, 0x53 };
    const unsigned char rctrl[] = { 0xE0, 0x1D };
    const unsigned char rctrl_rel[] = { 0xE0, 0x9D };
    const unsigned char kpenter[] = { 0xE0, 0x1C };
    const unsigned char kpdiv[] = { 0xE0, 0x35 };
    const unsigned char home[] = { 0xE0, 0x47 };
    const unsigned char end[] = { 0xE0, 0x4F };
    const unsigned char pgup[] = { 0xE0, 0x49 };
    const unsigned char pgdn[] = { 0xE0, 0x51 };
    const unsigned char left[] = { 0xE0, 0x4B };
    const unsigned char right[] = { 0xE0, 0x4D };
    const unsigned char down[] = { 0xE0, 0x50 };
    const unsigned char ins[] = { 0xE0, 0x52 };
    const unsigned char ralt[] = { 0xE0, 0x38 };
    const unsigned char super_l[] = { 0xE0, 0x5B };
    ps2_init(&s);
    check(ps2_feed(&s, 0xE0, &k) == PS2_EV_NONE, "e0 prefix alone is no event");
    check(ps2_feed(&s, 0x48, &k) == PS2_EV_PRESS && k.sym == XKB_KEY_Up, "e0 up");
    check(k.code == (PS2_CODE_EXTENDED | 0x48u), "extended code tagged");
    check(feed_seq(&s, up_rel, 2, &k) == PS2_EV_RELEASE && k.sym == XKB_KEY_Up, "e0 up release");
    check(feed_seq(&s, up, 2, &k) == PS2_EV_PRESS && k.text_len == 0, "arrow has no text");
    check(feed_seq(&s, del, 2, &k) == PS2_EV_PRESS && k.sym == XKB_KEY_Delete, "delete");
    check(k.text_len == 1 && (unsigned char)k.text[0] == 0x7f, "delete text");
    check(feed_seq(&s, home, 2, &k) == PS2_EV_PRESS && k.sym == XKB_KEY_Home, "home");
    check(feed_seq(&s, end, 2, &k) == PS2_EV_PRESS && k.sym == XKB_KEY_End, "end");
    check(feed_seq(&s, pgup, 2, &k) == PS2_EV_PRESS && k.sym == XKB_KEY_Page_Up, "page up");
    check(feed_seq(&s, pgdn, 2, &k) == PS2_EV_PRESS && k.sym == XKB_KEY_Page_Down, "page down");
    check(feed_seq(&s, left, 2, &k) == PS2_EV_PRESS && k.sym == XKB_KEY_Left, "left");
    check(feed_seq(&s, right, 2, &k) == PS2_EV_PRESS && k.sym == XKB_KEY_Right, "right");
    check(feed_seq(&s, down, 2, &k) == PS2_EV_PRESS && k.sym == XKB_KEY_Down, "down");
    check(feed_seq(&s, ins, 2, &k) == PS2_EV_PRESS && k.sym == XKB_KEY_Insert, "insert");
    check(feed_seq(&s, kpenter, 2, &k) == PS2_EV_PRESS && k.sym == XKB_KEY_KP_Enter, "kp enter");
    check(k.text_len == 1 && k.text[0] == '\r', "kp enter text");
    check(feed_seq(&s, kpdiv, 2, &k) == PS2_EV_PRESS && k.sym == XKB_KEY_KP_Divide, "kp divide");
    check(strcmp(k.text, "/") == 0, "kp divide text");
    check(feed_seq(&s, super_l, 2, &k) == PS2_EV_PRESS && k.sym == XKB_KEY_Super_L, "super left");
    check(feed_seq(&s, rctrl, 2, &k) == PS2_EV_PRESS && k.sym == XKB_KEY_Control_R, "right ctrl");
    press(&s, 0x13, &k);
    check(k.mods == KE_MOD_CTRL && k.text_len == 0, "right ctrl holds ctrl");
    feed_seq(&s, rctrl_rel, 2, &k);
    press(&s, 0x13, &k);
    check(k.mods == 0 && strcmp(k.text, "r") == 0, "right ctrl released");
    check(feed_seq(&s, ralt, 2, &k) == PS2_EV_PRESS && k.sym == XKB_KEY_Alt_R, "right alt");
    press(&s, 0x13, &k);
    check(k.mods == KE_MOD_ALT, "right alt holds alt");
}

static void test_function_keys(void) {
    ps2_state s;
    ps2_key k;
    ps2_init(&s);
    press(&s, 0x3B, &k);
    check(k.sym == XKB_KEY_F1 && k.text_len == 0, "f1");
    press(&s, 0x3F, &k);
    check(k.sym == XKB_KEY_F5, "f5");
    press(&s, 0x44, &k);
    check(k.sym == XKB_KEY_F10, "f10");
    press(&s, 0x57, &k);
    check(k.sym == XKB_KEY_F11, "f11");
    press(&s, 0x58, &k);
    check(k.sym == XKB_KEY_F12, "f12");
}

static void test_keypad_num_lock(void) {
    ps2_state s;
    ps2_key k;
    ps2_init(&s);
    press(&s, 0x52, &k);
    check(k.sym == XKB_KEY_KP_0 && strcmp(k.text, "0") == 0, "num lock starts on: kp 0");
    press(&s, 0x47, &k);
    check(k.sym == XKB_KEY_KP_7 && strcmp(k.text, "7") == 0, "kp 7");
    press(&s, 0x53, &k);
    check(k.sym == XKB_KEY_KP_Decimal && strcmp(k.text, ".") == 0, "kp decimal");
    press(&s, 0x4E, &k);
    check(k.sym == XKB_KEY_KP_Add && strcmp(k.text, "+") == 0, "kp add");
    press(&s, 0x4A, &k);
    check(k.sym == XKB_KEY_KP_Subtract && strcmp(k.text, "-") == 0, "kp subtract");
    press(&s, 0x37, &k);
    check(k.sym == XKB_KEY_KP_Multiply && strcmp(k.text, "*") == 0, "kp multiply");
    press(&s, 0x45, &k);
    check(k.sym == XKB_KEY_Num_Lock, "num lock sym");
    release(&s, 0x45, &k);
    press(&s, 0x52, &k);
    check(k.sym == XKB_KEY_KP_Insert && k.text_len == 0, "num lock off: kp insert");
    press(&s, 0x47, &k);
    check(k.sym == XKB_KEY_KP_Home, "kp home");
    press(&s, 0x48, &k);
    check(k.sym == XKB_KEY_KP_Up, "kp up");
    press(&s, 0x49, &k);
    check(k.sym == XKB_KEY_KP_Prior, "kp prior");
    press(&s, 0x4B, &k);
    check(k.sym == XKB_KEY_KP_Left, "kp left");
    press(&s, 0x4C, &k);
    check(k.sym == XKB_KEY_KP_Begin, "kp begin");
    press(&s, 0x4D, &k);
    check(k.sym == XKB_KEY_KP_Right, "kp right");
    press(&s, 0x4F, &k);
    check(k.sym == XKB_KEY_KP_End, "kp end");
    press(&s, 0x50, &k);
    check(k.sym == XKB_KEY_KP_Down, "kp down");
    press(&s, 0x51, &k);
    check(k.sym == XKB_KEY_KP_Next, "kp next");
    press(&s, 0x53, &k);
    check(k.sym == XKB_KEY_KP_Delete && k.text_len == 0, "kp delete");
    press(&s, 0x4E, &k);
    check(k.sym == XKB_KEY_KP_Add, "kp add ignores num lock");
}

static void test_prefix_sequences(void) {
    ps2_state s;
    ps2_key k;
    const unsigned char print_make[] = { 0xE0, 0x2A, 0xE0, 0x37 };
    const unsigned char pause_seq[] = { 0xE1, 0x1D, 0x45, 0xE1, 0x9D, 0xC5 };
    ps2_init(&s);
    check(feed_seq(&s, print_make, 2, &k) == PS2_EV_NONE, "fake shift is no event");
    check(feed_seq(&s, print_make + 2, 2, &k) == PS2_EV_PRESS && k.sym == XKB_KEY_Print, "print screen");
    press(&s, 0x1E, &k);
    check(k.mods == 0 && strcmp(k.text, "a") == 0, "fake shift does not latch shift");
    check(feed_seq(&s, pause_seq, 6, &k) == PS2_EV_NONE, "pause sequence swallowed");
    press(&s, 0x45, &k);
    check(k.sym == XKB_KEY_Num_Lock, "num lock after pause still toggles");
    press(&s, 0x1E, &k);
    check(k.sym == XKB_KEY_a, "stream in sync after pause");
}

static void test_fail_closed(void) {
    ps2_state s;
    ps2_key k;
    ps2_init(&s);
    check(ps2_feed(NULL, 0x1E, &k) == PS2_EV_NONE, "null state");
    check(ps2_feed(&s, 0x1E, NULL) == PS2_EV_NONE, "null out");
    check(ps2_feed(&s, 0x00, &k) == PS2_EV_NONE, "code zero ignored");
    check(ps2_feed(&s, 0x7F, &k) == PS2_EV_NONE, "unmapped code ignored");
    check(ps2_feed(&s, 0xFA, &k) == PS2_EV_NONE, "controller ack ignored");
    check(press(&s, 0x1E, &k) == PS2_EV_PRESS && k.sym == XKB_KEY_a, "stream usable after junk");
}

/** Entry point running all translator checks. */
int main(void) {
    test_letters_and_shift();
    test_caps_lock();
    test_punctuation();
    test_control_key_text();
    test_chords_have_no_text();
    test_extended_keys();
    test_function_keys();
    test_keypad_num_lock();
    test_prefix_sequences();
    test_fail_closed();
    if (fails) {
        printf("ps2_keymap: %d failure(s)\n", fails);
        return 1;
    }
    printf("ps2_keymap: all checks passed\n");
    return 0;
}
