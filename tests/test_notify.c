#include <stdio.h>

#include "wm_notify.h"

static int failures = 0;
static int calls;
static wm_notify_event_t seen;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

static void probe_handler(const wm_notify_event_t *e)
{
    calls++;
    seen = *e;
}

int main(void)
{
    wm_notify_bus_t bus;
    wm_notify_event_t e;
    int i;
    wm_notify_reset(&bus);
    CHECK(wm_notify_last(&bus) == 0, "empty bus has no last");
    CHECK(wm_notify_subscribe(&bus, 0) < 0, "null handler refused");
    CHECK(wm_notify_subscribe(0, probe_handler) < 0, "null bus refused");
    wm_notify_emit(0, 0);
    wm_notify_emit(&bus, 0);
    CHECK(calls == 0, "null emit calls nobody");
    CHECK(wm_notify_subscribe(&bus, probe_handler) == 0, "subscribe works");
    e.type = WM_NOTIFY_FOCUS;
    e.old_focus = 0;
    e.new_focus = 2;
    e.source = WM_FOCUS_SRC_POINTER;
    wm_notify_emit(&bus, &e);
    CHECK(calls == 1, "emit delivers once");
    CHECK(seen.old_focus == 0 && seen.new_focus == 2, "payload intact");
    CHECK(wm_notify_last(&bus) != 0, "last recorded");
    CHECK(wm_notify_last(&bus)->source == WM_FOCUS_SRC_POINTER, "source kept");
    for (i = 0; i < WM_NOTIFY_MAX_HANDLERS; i++)
        wm_notify_subscribe(&bus, probe_handler);
    CHECK(wm_notify_subscribe(&bus, probe_handler) < 0, "full table refused");
    wm_notify_reset(&bus);
    CHECK(wm_notify_last(&bus) == 0, "reset forgets last");
    wm_notify_emit(&bus, &e);
    CHECK(calls == 1, "reset drops subscribers");
    CHECK(wm_notify_last(0) == 0, "null bus has no last");
    CHECK(wm_notify_src_name(WM_FOCUS_SRC_KEYBOARD) != 0, "names exist");
    CHECK(wm_notify_src_name(99) != 0, "unknown source named");
    if (failures == 0)
        printf("notify: ok\n");
    else
        printf("notify: %d failures\n", failures);
    return failures != 0;
}
