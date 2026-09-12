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

/** Docstring: Set-1 scancode ids for every key the WM consumes. */
#define WM_SC_TAB 0x0F
#define WM_SC_ENTER 0x1C
#define WM_SC_MINUS 0x0C
#define WM_SC_EQUAL 0x0D
#define WM_SC_ZERO 0x0B
#define WM_SC_Q 0x10
#define WM_SC_LBRACKET 0x1A
#define WM_SC_RBRACKET 0x1B
#define WM_SC_M 0x32
#define WM_SC_X 0x2D
#define WM_SC_UP 0x48
#define WM_SC_DOWN 0x50
#define WM_SC_LEFT 0x4B
#define WM_SC_RIGHT 0x4D
#define WM_SC_HOME 0x47
#define WM_SC_END 0x4F

/** Docstring: Snap targets matching the TILING_* order left to bottom-right. */
#define WM_SNAP_LEFT 0
#define WM_SNAP_RIGHT 1
#define WM_SNAP_TOP 2
#define WM_SNAP_BOTTOM 3
#define WM_SNAP_TOP_LEFT 4
#define WM_SNAP_TOP_RIGHT 5
#define WM_SNAP_BOTTOM_LEFT 6
#define WM_SNAP_BOTTOM_RIGHT 7

/** Docstring: Input paths sharing one combo table. */
#define WM_PATH_COOKED 1
#define WM_PATH_RAW 2

/** Docstring: Discrete WM combo actions. */
typedef enum {
    WM_COMBO_NONE = 0,
    WM_COMBO_FOCUS_NEXT = 1,
    WM_COMBO_TILE_ALL = 2,
    WM_COMBO_FULLSCREEN = 3,
    WM_COMBO_MINIMIZE = 4,
    WM_COMBO_CLOSE = 5,
    WM_COMBO_SNAP = 6,
    WM_COMBO_RESIZE_DEC_W = 7,
    WM_COMBO_RESIZE_INC_W = 8,
    WM_COMBO_RESIZE_DEC_BOTH = 9,
    WM_COMBO_RESIZE_INC_BOTH = 10,
    WM_COMBO_RESET = 11
} wm_combo_action_t;

/** Docstring: One row of the shared Alt/Super combo table. */
typedef struct {
    int alt;
    int sup;
    int e0;
    int sc;
    int paths;
    int action;
    int zone;
} wm_combo_t;

/** Docstring: Shared Alt/Super combo table for cooked and raw paths. */
static const wm_combo_t WM_COMBOS[] = {
    {1, 0, 0, WM_SC_TAB, WM_PATH_COOKED | WM_PATH_RAW, WM_COMBO_FOCUS_NEXT, 0},
    {0, 1, 0, WM_SC_TAB, WM_PATH_COOKED | WM_PATH_RAW, WM_COMBO_TILE_ALL, 0},
    {1, 0, 0, WM_SC_ENTER, WM_PATH_COOKED | WM_PATH_RAW, WM_COMBO_FULLSCREEN, 0},
    {1, 0, 0, WM_SC_M, WM_PATH_COOKED | WM_PATH_RAW, WM_COMBO_MINIMIZE, 0},
    {1, 0, 0, WM_SC_X, WM_PATH_COOKED | WM_PATH_RAW, WM_COMBO_CLOSE, 0},
    {1, 0, 0, WM_SC_Q, WM_PATH_COOKED | WM_PATH_RAW, WM_COMBO_CLOSE, 0},
    {1, 0, 0, WM_SC_LBRACKET, WM_PATH_COOKED | WM_PATH_RAW, WM_COMBO_RESIZE_DEC_W, 0},
    {1, 0, 0, WM_SC_RBRACKET, WM_PATH_COOKED | WM_PATH_RAW, WM_COMBO_RESIZE_INC_W, 0},
    {1, 0, 0, WM_SC_MINUS, WM_PATH_COOKED | WM_PATH_RAW, WM_COMBO_RESIZE_DEC_BOTH, 0},
    {1, 0, 0, WM_SC_EQUAL, WM_PATH_COOKED | WM_PATH_RAW, WM_COMBO_RESIZE_INC_BOTH, 0},
    {1, 0, 0, WM_SC_ZERO, WM_PATH_COOKED | WM_PATH_RAW, WM_COMBO_RESET, 0},
    {1, 0, 0, WM_SC_HOME, WM_PATH_RAW, WM_COMBO_SNAP, WM_SNAP_TOP_LEFT},
    {1, 0, 0, WM_SC_END, WM_PATH_RAW, WM_COMBO_SNAP, WM_SNAP_BOTTOM_RIGHT},
    {1, 0, 1, WM_SC_UP, WM_PATH_COOKED, WM_COMBO_SNAP, WM_SNAP_TOP},
    {1, 0, 1, WM_SC_DOWN, WM_PATH_COOKED, WM_COMBO_SNAP, WM_SNAP_BOTTOM},
    {1, 0, 1, WM_SC_LEFT, WM_PATH_COOKED, WM_COMBO_SNAP, WM_SNAP_LEFT},
    {1, 0, 1, WM_SC_RIGHT, WM_PATH_COOKED, WM_COMBO_SNAP, WM_SNAP_RIGHT},
    {1, 0, 1, WM_SC_HOME, WM_PATH_COOKED, WM_COMBO_SNAP, WM_SNAP_TOP_LEFT},
    {1, 0, 1, WM_SC_END, WM_PATH_COOKED, WM_COMBO_SNAP, WM_SNAP_BOTTOM_RIGHT},
    {0, 1, 1, WM_SC_UP, WM_PATH_COOKED | WM_PATH_RAW, WM_COMBO_SNAP, WM_SNAP_TOP},
    {0, 1, 1, WM_SC_DOWN, WM_PATH_COOKED | WM_PATH_RAW, WM_COMBO_SNAP, WM_SNAP_BOTTOM},
    {0, 1, 1, WM_SC_LEFT, WM_PATH_COOKED | WM_PATH_RAW, WM_COMBO_SNAP, WM_SNAP_LEFT},
    {0, 1, 1, WM_SC_RIGHT, WM_PATH_COOKED | WM_PATH_RAW, WM_COMBO_SNAP, WM_SNAP_RIGHT},
    {0, 1, 1, WM_SC_HOME, WM_PATH_COOKED | WM_PATH_RAW, WM_COMBO_SNAP, WM_SNAP_TOP_LEFT},
    {0, 1, 1, WM_SC_END, WM_PATH_COOKED | WM_PATH_RAW, WM_COMBO_SNAP, WM_SNAP_BOTTOM_RIGHT}
};

/** Docstring: Row count of the shared combo table. */
#define WM_COMBOS_N (sizeof(WM_COMBOS) / sizeof(WM_COMBOS[0]))

/** Docstring: Lookup one Alt/Super combo, fail closed on AltGr or mismatch. */
static inline int wm_combo_lookup(int alt, int altgr, int sup, int e0, int sc, int path, int *zone_out)
{
    unsigned long i;
    if (zone_out != 0) {
        *zone_out = 0;
    }
    if (altgr) {
        return WM_COMBO_NONE;
    }
    if (path != WM_PATH_COOKED && path != WM_PATH_RAW) {
        return WM_COMBO_NONE;
    }
    for (i = 0; i < WM_COMBOS_N; i++) {
        if (WM_COMBOS[i].alt != (alt ? 1 : 0)) {
            continue;
        }
        if (WM_COMBOS[i].sup != (sup ? 1 : 0)) {
            continue;
        }
        if (WM_COMBOS[i].e0 != (e0 ? 1 : 0)) {
            continue;
        }
        if (WM_COMBOS[i].sc != sc) {
            continue;
        }
        if (!(WM_COMBOS[i].paths & path)) {
            continue;
        }
        if (zone_out != 0) {
            *zone_out = WM_COMBOS[i].zone;
        }
        return WM_COMBOS[i].action;
    }
    return WM_COMBO_NONE;
}

#endif
