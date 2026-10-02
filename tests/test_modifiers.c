#include <stdio.h>

#include "drivers/modifiers.h"

/** Docstring: Designated initializers, so adding a member cannot silently
 * shift every other one: positional order would have read the right-alt code
 * as right-ctrl and failed eight assertions instead of one. */
static const modifier_keys_t fixture = {
    .shift_l = 10, .shift_r = 11,
    .ctrl_l  = 20, .ctrl_r  = 21,
    .alt_l   = 30, .alt_r   = 40,
    .super_l = 50, .super_r = 51
};

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

int main(void)
{
    modifier_state_t st;
    modifiers_init(&st);
    CHECK(st.shift == 0 && st.super == 0, "init clears");

    CHECK(modifiers_update(&fixture, &st, 30, 0, 0) == 1, "alt make consumed");
    CHECK(st.alt == 1, "alt held");
    CHECK(modifiers_match(&st, MOD_ALT), "alt mask matches");
    CHECK(!modifiers_match(&st, MOD_ALT | MOD_SUPER), "missing bit fails");
    CHECK(modifiers_update(&fixture, &st, 30, 1, 0) == 1, "alt break consumed");
    CHECK(st.alt == 0, "alt released");

    CHECK(modifiers_update(&fixture, &st, 40, 0, 1) == 1, "altgr e0 consumed");
    CHECK(st.altgr == 1 && st.alt == 0, "altgr apart from alt");
    CHECK(modifiers_update(&fixture, &st, 99, 0, 0) == 0, "plain key passes");
    CHECK(modifiers_update(&fixture, &st, 99, 0, 1) == 0, "plain e0 passes");
    CHECK(modifiers_update(0, &st, 30, 0, 0) == 0, "null keys fail closed");
    CHECK(modifiers_update(&fixture, 0, 30, 0, 0) == 0, "null state fail closed");
    CHECK(!modifiers_match(0, MOD_ALT), "null match fail closed");

    modifiers_init(&st);
    CHECK(modifiers_update(&fixture, &st, 50, 0, 1) == 1, "super make consumed");
    CHECK(modifiers_match(&st, MOD_SUPER), "super mask matches");
    modifiers_init(&st);
    CHECK(!modifiers_match(&st, MOD_SUPER), "reset clears super");

    /* Set 1 gives both halves of Ctrl the same base code and separates them
     * with 0xE0, so the right one is only recognised when the prefix is
     * present. It was not tracked at all before, which left the window
     * manager believing Ctrl was up while a key was held. */
    modifiers_init(&st);
    CHECK(modifiers_update(&fixture, &st, 21, 0, 0) == 0,
          "right ctrl without the e0 prefix is not a modifier");
    CHECK(modifiers_update(&fixture, &st, 21, 0, 1) == 1,
          "right ctrl e0 make consumed");
    CHECK(modifiers_match(&st, MOD_CTRL), "right ctrl holds ctrl");
    CHECK(!modifiers_match(&st, MOD_CTRL | MOD_ALT), "right ctrl is not alt");
    CHECK(modifiers_update(&fixture, &st, 21, 1, 1) == 1,
          "right ctrl e0 break consumed");
    CHECK(!modifiers_match(&st, MOD_CTRL), "right ctrl released");

    modifiers_init(&st);
    CHECK(modifiers_update(&fixture, &st, 20, 0, 0) == 1, "left ctrl make");
    CHECK(modifiers_match(&st, MOD_CTRL), "left ctrl holds ctrl");
    CHECK(modifiers_update(&fixture, &st, 99, 0, 1) == 0,
          "an e0-prefixed plain key is not consumed");
    CHECK(modifiers_match(&st, MOD_CTRL), "left ctrl still held");

    if (failures == 0)
        printf("modifiers: ok\n");
    else
        printf("modifiers: %d failures\n", failures);
    return failures != 0;
}
