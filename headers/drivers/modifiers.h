#ifndef MODIFIERS_H
#define MODIFIERS_H

/** Docstring: Unified modifier tracking for cooked and raw paths. */
typedef struct {
    int shift;
    int ctrl;
    int alt;
    int altgr;
    int super;
} modifier_state_t;

/** Docstring: Key codes feeding the tracker, one config per layout.
 *
 * The right-hand members are only recognised when the event carries the
 * 0xE0 prefix, which is how scancode set 1 disambiguates the two halves of
 * each pair. Right Alt is the exception that proves the rule: on a Spanish
 * layout it is AltGr, so it feeds the separate altgr bit rather than alt. */
typedef struct {
    int shift_l;
    int shift_r;
    int ctrl_l;
    int ctrl_r;
    int alt_l;
    int alt_r;
    int super_l;
    int super_r;
} modifier_keys_t;

#define MOD_SHIFT (1 << 0)
#define MOD_CTRL  (1 << 1)
#define MOD_ALT   (1 << 2)
#define MOD_ALTGR (1 << 3)
#define MOD_SUPER (1 << 4)

/** Docstring: Clear every modifier, shell reset path. */
static inline void modifiers_init(modifier_state_t *st)
{
    if (!st) return;
    st->shift = 0;
    st->ctrl = 0;
    st->alt = 0;
    st->altgr = 0;
    st->super = 0;
}

/** Docstring: Track one make or break code, 1 when consumed.
 *
 * Set 1 gives both halves of Ctrl, Alt and Super the same base code and
 * separates them with 0xE0, so an unprefixed code is always the left one.
 * Right Ctrl arrived from a PS/2 keyboard and from a USB HID report with no
 * prefix difference at all before this, and was silently dropped: the state
 * said Ctrl was up while a key was physically held. */
static inline int modifiers_update(const modifier_keys_t *keys,
                                   modifier_state_t *st,
                                   int code, int is_break, int e0)
{
    int pressed;
    if (!keys || !st) return 0;
    pressed = !is_break;
    if (!e0) {
        if (code == keys->shift_l || code == keys->shift_r) {
            st->shift = pressed;
            return 1;
        }
        if (code == keys->ctrl_l) {
            st->ctrl = pressed;
            return 1;
        }
        if (code == keys->alt_l) {
            st->alt = pressed;
            return 1;
        }
        return 0;
    }
    if (code == keys->ctrl_r) {
        st->ctrl = pressed;
        return 1;
    }
    if (code == keys->alt_r) {
        st->altgr = pressed;
        return 1;
    }
    if (code == keys->super_l || code == keys->super_r) {
        st->super = pressed;
        return 1;
    }
    return 0;
}

/** Docstring: True when the state covers every bit in mask. */
static inline int modifiers_match(const modifier_state_t *st, int mask)
{
    int actual = 0;
    if (!st) return 0;
    if (st->shift) actual |= MOD_SHIFT;
    if (st->ctrl) actual |= MOD_CTRL;
    if (st->alt) actual |= MOD_ALT;
    if (st->altgr) actual |= MOD_ALTGR;
    if (st->super) actual |= MOD_SUPER;
    return (actual & mask) == mask;
}

#endif
