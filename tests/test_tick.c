/** Docstring: Host test for kernel/tick.c (make test-tick).
 *
 * Drives both listener buses with stub effects. Verifies empty start,
 * ordered dispatch, audio and desktop separation, null and full
 * refusal without state change, reset clearing, count clamping and
 * the pure desktop gating predicate across interval boundaries.
 */

#include <stdio.h>

#include "tick.h"

static int failures = 0;
static int order[16];
static int order_used;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

static void rec_a(void *ctx) {
    (void)ctx;
    if (order_used < 16) {
        order[order_used++] = 1;
    }
}

static void rec_b(void *ctx) {
    (void)ctx;
    if (order_used < 16) {
        order[order_used++] = 2;
    }
}

static void rec_d(void *ctx) {
    int *p = (int *)ctx;
    if (p != NULL) {
        (*p)++;
    }
}

static int dummy_calls;

static void dummy(void *ctx) {
    (void)ctx;
    dummy_calls++;
}

int main(void) {
    int i;
    int hits;
    tick_config_t cfg = TICK_CONFIG_DEFAULT;
    CHECK(cfg.max_audio_listeners == TICK_MAX_AUDIO_LISTENERS, "config carries audio bound");
    CHECK(cfg.max_desktop_listeners == TICK_MAX_DESKTOP_LISTENERS, "config carries desktop bound");
    tick_reset();
    CHECK(tick_audio_count() == 0, "audio starts empty");
    CHECK(tick_desktop_count() == 0, "desktop starts empty");
    order_used = 0;
    tick_run_audio();
    tick_run_desktop();
    CHECK(order_used == 0, "empty dispatch runs nothing");
    CHECK(tick_register_audio(rec_a, NULL) == 0, "audio register ok");
    CHECK(tick_register_audio(rec_b, NULL) == 0, "second audio register ok");
    CHECK(tick_audio_count() == 2, "audio count tracks registration");
    CHECK(tick_desktop_count() == 0, "desktop untouched by audio registration");
    order_used = 0;
    tick_run_audio();
    CHECK(order_used == 2, "audio dispatch runs both");
    CHECK(order[0] == 1 && order[1] == 2, "audio dispatch keeps order");
    order_used = 0;
    tick_run_desktop();
    CHECK(order_used == 0, "desktop dispatch skips audio listeners");
    hits = 0;
    CHECK(tick_register_desktop(rec_d, &hits) == 0, "desktop register ok");
    tick_run_desktop();
    CHECK(hits == 1, "desktop dispatch reaches context");
    order_used = 0;
    tick_run_audio();
    CHECK(order_used == 2, "audio dispatch skips desktop listeners");
    CHECK(tick_register_audio(NULL, NULL) == -1, "null audio refused");
    CHECK(tick_register_desktop(NULL, NULL) == -1, "null desktop refused");
    CHECK(tick_audio_count() == 2, "refused audio keeps count");
    CHECK(tick_desktop_count() == 1, "refused desktop keeps count");
    tick_reset();
    dummy_calls = 0;
    for (i = 0; i < TICK_MAX_AUDIO_LISTENERS; i++) {
        CHECK(tick_register_audio(dummy, NULL) == 0, "audio fills to bound");
    }
    CHECK(tick_register_audio(dummy, NULL) == -1, "full audio refused");
    CHECK(tick_audio_count() == TICK_MAX_AUDIO_LISTENERS, "audio count clamps at bound");
    tick_reset();
    for (i = 0; i < TICK_MAX_DESKTOP_LISTENERS; i++) {
        CHECK(tick_register_desktop(dummy, NULL) == 0, "desktop fills to bound");
    }
    CHECK(tick_register_desktop(dummy, NULL) == -1, "full desktop refused");
    CHECK(tick_desktop_count() == TICK_MAX_DESKTOP_LISTENERS, "desktop count clamps at bound");
    tick_reset();
    order_used = 0;
    tick_run_audio();
    tick_run_desktop();
    CHECK(order_used == 0 && dummy_calls == 0, "reset clears both buses");
    CHECK(tick_desktop_due(0, 4) != 0, "tick zero is due");
    CHECK(tick_desktop_due(4, 4) != 0, "interval multiple is due");
    CHECK(tick_desktop_due(8, 4) != 0, "second multiple is due");
    CHECK(tick_desktop_due(1, 4) == 0, "off tick is not due");
    CHECK(tick_desktop_due(5, 4) == 0, "off tick past multiple is not due");
    CHECK(tick_desktop_due(7, 1) != 0, "interval one always due");
    CHECK(tick_desktop_due(99, 0) == 0, "zero interval never due");
    if (failures == 0) {
        printf("tick: ok\n");
    }
    return failures != 0;
}
