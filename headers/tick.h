/** Docstring: Tick listener bus contract.
 *
 * Decouples the 100 Hz timer ISR from its effects. The ISR used to call
 * sb16_poll and vga_fb_mouse_tick directly, which forced every new
 * periodic effect to edit sched.c. This bus owns two bounded listener
 * lists, one for unconditional BSP audio effects and one for the gated
 * desktop effect, plus a pure gating predicate for the desktop tick.
 *
 * Design: fixed-size tables, no heap, no locks. Registration happens at
 * boot before sti, dispatch happens in ISR context and only reads. A
 * failed registration returns a negative code and changes nothing. A
 * null entry is never dispatched. Dispatch order equals registration
 * order. Behavior of existing listeners is unchanged; only the call
 * path moves.
 */

#ifndef TICK_H
#define TICK_H

/** Docstring: Centralized bounds for the tick listener bus. */
typedef struct {
    int max_audio_listeners;
    int max_desktop_listeners;
} tick_config_t;

/** Docstring: Default bus capacities. */
#define TICK_MAX_AUDIO_LISTENERS 8
/** Docstring: Default desktop bus capacity. */
#define TICK_MAX_DESKTOP_LISTENERS 8

/** Docstring: Default bus configuration. */
#define TICK_CONFIG_DEFAULT ((tick_config_t){ \
    TICK_MAX_AUDIO_LISTENERS, \
    TICK_MAX_DESKTOP_LISTENERS \
})

/** Docstring: Periodic effect signature. Context is opaque to the bus. */
typedef void (*tick_fn_t)(void *ctx);

/** Docstring: Reset both listener lists to empty. */
void tick_reset(void);

/** Docstring: Register an unconditional BSP audio effect.
 *
 * Returns 0 on success, -1 when the handler is null or the audio
 * table is full. A refusal changes nothing.
 */
int tick_register_audio(tick_fn_t fn, void *ctx);

/** Docstring: Register a gated desktop effect.
 *
 * Returns 0 on success, -1 when the handler is null or the desktop
 * table is full. A refusal changes nothing.
 */
int tick_register_desktop(tick_fn_t fn, void *ctx);

/** Docstring: Run audio listeners in registration order. */
void tick_run_audio(void);

/** Docstring: Run desktop listeners in registration order. */
void tick_run_desktop(void);

/** Docstring: Count registered audio listeners. */
int tick_audio_count(void);

/** Docstring: Count registered desktop listeners. */
int tick_desktop_count(void);

/** Docstring: Pure desktop gating predicate.
 *
 * Returns nonzero when the given tick count falls on a desktop tick
 * for the given interval. A non-positive interval never fires. Holds
 * for every tick value including zero.
 */
int tick_desktop_due(unsigned long long ticks, unsigned interval);

#endif
