/** Docstring: Tick listener bus implementation.
 *
 * Owns two fixed listener tables behind the tick.h contract. Tables
 * are static storage, cleared by tick_reset, appended by the register
 * calls and read by the run calls. No allocation, no locks, no user
 * pointers. Registration is boot-time only; dispatch is ISR-safe
 * because it only reads entries written before sti.
 */

#include "tick.h"

#include <stddef.h>

/** Docstring: Single registered listener slot. */
typedef struct {
    tick_fn_t fn;
    void *ctx;
} tick_slot_t;

/** Docstring: Audio listener table. */
static tick_slot_t tick_audio_slots[TICK_MAX_AUDIO_LISTENERS];
/** Docstring: Desktop listener table. */
static tick_slot_t tick_desktop_slots[TICK_MAX_DESKTOP_LISTENERS];
/** Docstring: Active audio listener count. */
static int tick_audio_used;
/** Docstring: Active desktop listener count. */
static int tick_desktop_used;

/** Docstring: Reset both listener lists to empty. */
void tick_reset(void) {
    int i;
    for (i = 0; i < TICK_MAX_AUDIO_LISTENERS; i++) {
        tick_audio_slots[i].fn = NULL;
        tick_audio_slots[i].ctx = NULL;
    }
    for (i = 0; i < TICK_MAX_DESKTOP_LISTENERS; i++) {
        tick_desktop_slots[i].fn = NULL;
        tick_desktop_slots[i].ctx = NULL;
    }
    tick_audio_used = 0;
    tick_desktop_used = 0;
}

/** Docstring: Register an unconditional BSP audio effect.
 *
 * Returns 0 on success, -1 when the handler is null or the audio
 * table is full. A refusal changes nothing.
 */
int tick_register_audio(tick_fn_t fn, void *ctx) {
    if (fn == NULL) {
        return -1;
    }
    if (tick_audio_used < 0 || tick_audio_used >= TICK_MAX_AUDIO_LISTENERS) {
        return -1;
    }
    tick_audio_slots[tick_audio_used].fn = fn;
    tick_audio_slots[tick_audio_used].ctx = ctx;
    tick_audio_used++;
    return 0;
}

/** Docstring: Register a gated desktop effect.
 *
 * Returns 0 on success, -1 when the handler is null or the desktop
 * table is full. A refusal changes nothing.
 */
int tick_register_desktop(tick_fn_t fn, void *ctx) {
    if (fn == NULL) {
        return -1;
    }
    if (tick_desktop_used < 0 || tick_desktop_used >= TICK_MAX_DESKTOP_LISTENERS) {
        return -1;
    }
    tick_desktop_slots[tick_desktop_used].fn = fn;
    tick_desktop_slots[tick_desktop_used].ctx = ctx;
    tick_desktop_used++;
    return 0;
}

/** Docstring: Run audio listeners in registration order. */
void tick_run_audio(void) {
    int i;
    for (i = 0; i < tick_audio_used; i++) {
        if (tick_audio_slots[i].fn != NULL) {
            tick_audio_slots[i].fn(tick_audio_slots[i].ctx);
        }
    }
}

/** Docstring: Run desktop listeners in registration order. */
void tick_run_desktop(void) {
    int i;
    for (i = 0; i < tick_desktop_used; i++) {
        if (tick_desktop_slots[i].fn != NULL) {
            tick_desktop_slots[i].fn(tick_desktop_slots[i].ctx);
        }
    }
}

/** Docstring: Count registered audio listeners. */
int tick_audio_count(void) {
    if (tick_audio_used < 0) {
        return 0;
    }
    if (tick_audio_used > TICK_MAX_AUDIO_LISTENERS) {
        return TICK_MAX_AUDIO_LISTENERS;
    }
    return tick_audio_used;
}

/** Docstring: Count registered desktop listeners. */
int tick_desktop_count(void) {
    if (tick_desktop_used < 0) {
        return 0;
    }
    if (tick_desktop_used > TICK_MAX_DESKTOP_LISTENERS) {
        return TICK_MAX_DESKTOP_LISTENERS;
    }
    return tick_desktop_used;
}

/** Docstring: Pure desktop gating predicate.
 *
 * Returns nonzero when the given tick count falls on a desktop tick
 * for the given interval. A non-positive interval never fires. Holds
 * for every tick value including zero.
 */
int tick_desktop_due(unsigned long long ticks, unsigned interval) {
    if (interval == 0) {
        return 0;
    }
    return (ticks % interval) == 0;
}
