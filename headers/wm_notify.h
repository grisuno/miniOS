#ifndef WM_NOTIFY_H
#define WM_NOTIFY_H

/** Docstring: Focus event bus for the MiniOS desktop.
 *
 * Explicit state struct, no hidden globals: one wm_notify_bus_t lives in
 * the desktop owner (kernel/vga_fb.c) and every other translation unit
 * reaches it through accessors, so two includers can never split the
 * subscriber table. Fixed table, no heap, no locks: registration is
 * boot-time only, dispatch only reads. Every focus move emits once at
 * the user-intent site (keyboard cycle, pointer click, taskbar button,
 * mode switch, shell command), never inside the focus mechanism itself,
 * so one user gesture is exactly one event. A null or full registration
 * changes nothing; emit with no subscribers still records.
 */

typedef enum {
    WM_NOTIFY_FOCUS = 1
} wm_notify_type_t;

typedef enum {
    WM_FOCUS_SRC_KEYBOARD = 1,
    WM_FOCUS_SRC_POINTER = 2,
    WM_FOCUS_SRC_TASKBAR = 3,
    WM_FOCUS_SRC_MODE = 4,
    WM_FOCUS_SRC_PROGRAM = 5
} wm_focus_source_t;

/** Docstring: One focus move, old and new ids share the focus space. */
typedef struct {
    int type;
    int old_focus;
    int new_focus;
    int source;
} wm_notify_event_t;

/** Docstring: Focus listener, runs synchronously inside emit. */
typedef void (*wm_notify_handler_t)(const wm_notify_event_t *event);

/** Docstring: Static subscriber table plus last emitted event. */
#define WM_NOTIFY_MAX_HANDLERS 4

typedef struct {
    wm_notify_handler_t handlers[WM_NOTIFY_MAX_HANDLERS];
    int count;
    wm_notify_event_t last;
    int has_event;
} wm_notify_bus_t;

/** Docstring: Drop every subscriber and forget the last event. */
static inline void wm_notify_reset(wm_notify_bus_t *bus)
{
    int i;
    if (bus == 0) return;
    for (i = 0; i < WM_NOTIFY_MAX_HANDLERS; i++)
        bus->handlers[i] = 0;
    bus->count = 0;
    bus->last.type = 0;
    bus->last.old_focus = 0;
    bus->last.new_focus = 0;
    bus->last.source = 0;
    bus->has_event = 0;
}

/** Docstring: Register one listener, -1 when full or null. */
static inline int wm_notify_subscribe(wm_notify_bus_t *bus,
                                      wm_notify_handler_t handler)
{
    if (bus == 0 || handler == 0) return -1;
    if (bus->count >= WM_NOTIFY_MAX_HANDLERS) return -1;
    bus->handlers[bus->count++] = handler;
    return 0;
}

/** Docstring: Deliver one event to every listener, then record it. */
static inline void wm_notify_emit(wm_notify_bus_t *bus,
                                  const wm_notify_event_t *event)
{
    int i;
    if (bus == 0 || event == 0) return;
    for (i = 0; i < bus->count; i++) {
        if (bus->handlers[i])
            bus->handlers[i](event);
    }
    bus->last = *event;
    bus->has_event = 1;
}

/** Docstring: Last emitted event, 0 when none was ever emitted. */
static inline const wm_notify_event_t *wm_notify_last(
    const wm_notify_bus_t *bus)
{
    if (bus == 0 || !bus->has_event) return 0;
    return &bus->last;
}

/** Docstring: Short source name for serial-observable state. */
static inline const char *wm_notify_src_name(int source)
{
    if (source == WM_FOCUS_SRC_KEYBOARD) return "kbd";
    if (source == WM_FOCUS_SRC_POINTER) return "ptr";
    if (source == WM_FOCUS_SRC_TASKBAR) return "bar";
    if (source == WM_FOCUS_SRC_MODE) return "mode";
    if (source == WM_FOCUS_SRC_PROGRAM) return "prog";
    return "?";
}

#endif
