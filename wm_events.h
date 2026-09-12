/** Docstring: Window event contract for the MiniOS desktop.
 *
 * Single-file header-only contract translating raw mouse samples into
 * discrete window manager events. The translator is pure integer logic
 * over wm_mouse_t snapshots so it stays host-testable without kernel
 * dependencies. All thresholds arrive through wm_event_config_t and the
 * translator never retains state, so an interrupted drag cannot poison
 * a later gesture with stale grabs.
 */
#ifndef WM_EVENTS_H
#define WM_EVENTS_H

/** Docstring: Discrete window manager event kinds. */
typedef enum {
    WM_EVT_NONE = 0,
    WM_EVT_CLICK = 1,
    WM_EVT_RELEASE = 2,
    WM_EVT_MOVE = 3,
    WM_EVT_SCROLL = 4
} wm_event_type_t;

/** Docstring: Raw mouse snapshot consumed by the translator. */
typedef struct {
    int x;
    int y;
    int buttons;
    int wheel;
    int present;
} wm_mouse_t;

/** Docstring: Translated window manager event. */
typedef struct {
    wm_event_type_t type;
    int x;
    int y;
    int button;
    int wheel;
} wm_event_t;

/** Docstring: Centralized event translator configuration. */
typedef struct {
    int left_mask;
    int wheel_step;
} wm_event_config_t;

/** Docstring: Default event configuration matching the PS/2 mouse path. */
#define WM_EVENT_CONFIG_DEFAULT { 1, 3 }

/** Docstring: True on the rising edge of the left button. */
static inline int wm_is_click_edge(const wm_event_config_t *cfg, int prev_buttons, int curr_buttons)
{
    int mask = (cfg != 0 && cfg->left_mask != 0) ? cfg->left_mask : 1;
    return (curr_buttons & mask) && !(prev_buttons & mask);
}

/** Docstring: True on the falling edge of the left button. */
static inline int wm_is_release_edge(const wm_event_config_t *cfg, int prev_buttons, int curr_buttons)
{
    int mask = (cfg != 0 && cfg->left_mask != 0) ? cfg->left_mask : 1;
    return !(curr_buttons & mask) && (prev_buttons & mask);
}

/** Docstring: Translate two consecutive mouse snapshots into one event. */
static inline wm_event_t wm_translate_event(const wm_event_config_t *cfg, const wm_mouse_t *prev, const wm_mouse_t *curr)
{
    wm_event_t evt;
    evt.type = WM_EVT_NONE;
    evt.x = 0;
    evt.y = 0;
    evt.button = 0;
    evt.wheel = 0;
    if (prev == 0 || curr == 0) {
        return evt;
    }
    if (!curr->present) {
        return evt;
    }
    evt.x = curr->x;
    evt.y = curr->y;
    evt.button = curr->buttons;
    evt.wheel = curr->wheel;
    if (wm_is_click_edge(cfg, prev->buttons, curr->buttons)) {
        evt.type = WM_EVT_CLICK;
        return evt;
    }
    if (wm_is_release_edge(cfg, prev->buttons, curr->buttons)) {
        evt.type = WM_EVT_RELEASE;
        return evt;
    }
    if (curr->wheel != 0) {
        evt.type = WM_EVT_SCROLL;
        return evt;
    }
    if (curr->x != prev->x || curr->y != prev->y) {
        evt.type = WM_EVT_MOVE;
        return evt;
    }
    return evt;
}

/** Docstring: True when the event must suppress a title drag on this tick. */
static inline int wm_event_suppresses_drag(const wm_event_t *evt)
{
    return evt != 0 && evt->type == WM_EVT_CLICK;
}

#endif
