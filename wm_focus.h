/** Docstring: Focus manager contract for the MiniOS desktop.
 *
 * Single-file header-only contract owning focus state transitions. Focus
 * ids share one space across terminals and the graphics window; every
 * transition validates against present flags and the graphics mode so an
 * invalid id can never steal the keyboard. The state struct carries no
 * kernel dependency, keeping all transitions host-testable.
 */
#ifndef WM_FOCUS_H
#define WM_FOCUS_H

#include "wm_window.h"

/** Docstring: Focus state snapshot consumed by every transition. */
typedef struct {
    int focus;
    int nterms;
    int present[4];
    int gfx_active;
} wm_focus_state_t;

/** Docstring: True when id is a selectable focus target in this state. */
static inline int wm_focus_selectable(const wm_focus_state_t *st, int id)
{
    if (st == 0) {
        return 0;
    }
    if (id == WM_WINDOW_GFX_ID) {
        return st->gfx_active ? 1 : 0;
    }
    if (id < 0 || id >= st->nterms || id >= 4) {
        return 0;
    }
    return st->present[id] ? 1 : 0;
}

/** Docstring: Next focus id in rotation order, unchanged when < 2 targets. */
static inline int wm_focus_next(const wm_focus_state_t *st)
{
    int flat[4];
    int i;
    if (st == 0) {
        return 0;
    }
    for (i = 0; i < 4; i++) {
        flat[i] = 0;
    }
    for (i = 0; i < st->nterms && i < 4; i++) {
        flat[i] = st->present[i];
    }
    return wm_focus_next_id(flat, st->nterms > 4 ? 4 : st->nterms, st->gfx_active, st->focus);
}

/** Docstring: Validated focus assignment, -1 when id is not selectable. */
static inline int wm_focus_set(const wm_focus_state_t *st, int id)
{
    if (!wm_focus_selectable(st, id)) {
        return -1;
    }
    return id;
}

#endif
