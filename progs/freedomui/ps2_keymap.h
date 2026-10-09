/** ps2_keymap.h - pure PS/2 set 1 scancode to keysym translator (US layout).
 *
 * Feeds the raw bytes SYS_KBD returns in raw mode one at a time and turns
 * them into key press and release events carrying an X11/xkb keysym, the
 * UTF-8 text the press produces (xkb semantics) and the modifier mask in
 * FreeDom's key_event vocabulary. No I/O, no global state: all state lives
 * in the caller's ps2_state. See docs/spec/network.md (freedom-gui).
 */
#ifndef MINIOS_PS2_KEYMAP_H
#define MINIOS_PS2_KEYMAP_H

#include <stdint.h>

#include "key_event.h"

#define PS2_EV_NONE    0
#define PS2_EV_PRESS   1
#define PS2_EV_RELEASE 2

/** Bit set in ps2_key.code for keys sent behind the E0 prefix. */
#define PS2_CODE_EXTENDED 0x100u

/** Upper bound of ps2_key.code, for callers that track held keys. */
#define PS2_CODE_LIMIT 0x200u

#define PS2_TEXT_MAX 8

/** Translator state: held modifiers, lock toggles and pending prefixes. */
typedef struct ps2_state {
    unsigned held;      /* PS2_HELD_* bits */
    int      caps_lock;
    int      num_lock;
    int      extended;  /* an E0 prefix is pending */
    int      skip;      /* bytes of an E1 sequence still to swallow */
} ps2_state;

/** One translated key event. */
typedef struct ps2_key {
    uint32_t sym;                /* X11/xkb keysym */
    uint32_t code;               /* make code, PS2_CODE_EXTENDED for E0 keys */
    char     text[PS2_TEXT_MAX]; /* UTF-8 produced by a press, NUL-terminated */
    int      text_len;
    unsigned mods;               /* KE_MOD_* held when the key changed */
} ps2_key;

/** Resets the state: nothing held, Caps Lock off, Num Lock on. */
void ps2_init(ps2_state *s);

/** Feeds one byte. Returns PS2_EV_PRESS or PS2_EV_RELEASE with *out filled,
 * or PS2_EV_NONE for prefixes, swallowed sequences, unmapped codes and NULL
 * arguments (out is then left untouched). */
int ps2_feed(ps2_state *s, uint8_t byte, ps2_key *out);

#endif
