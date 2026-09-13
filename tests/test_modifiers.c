#include <stdio.h>

#include "drivers/modifiers.h"

static const modifier_keys_t fixture = { 10, 11, 20, 30, 40, 50, 51 };

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

    if (failures == 0)
        printf("modifiers: ok\n");
    else
        printf("modifiers: %d failures\n", failures);
    return failures != 0;
}
