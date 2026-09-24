/** Docstring: kernel/clip.c -- Shared text clipboard.
 *
 * Bounded Context (DDD): one text slot owned by the kernel, written by
 * any producer (shell `clip`, Wayland-mini clients through the wl_mini
 * clipboard messages, later terminal selection) and read by any
 * consumer (shell, vedit paste). One CLIP_MAX buffer lives for the
 * machine's life: set copies in (refused past the cap, never silently
 * truncated), clear empties, get copies out.
 *
 * No locks: producers run on the shell context or in already
 * serialized syscalls; get reads the length once and copies in one
 * pass, so a racing set can only mix whole old/new bytes, never
 * overflow the reader. */

#include "kernel.h"

#define CLIP_MAX 4096

static char clip_buf[CLIP_MAX];
static unsigned clip_len;
static int clip_valid;

/** Docstring: Replace the clipboard with len bytes from data. Refused
 * (return -1) on null data or past CLIP_MAX; empty clears. */
int clip_set(const char *data, unsigned long len) {
    unsigned long i;
    if (!data) return -1;
    if (len > CLIP_MAX) return -1;
    for (i = 0u; i < len; i++) clip_buf[i] = data[i];
    clip_len = (unsigned)len;
    clip_valid = 1;
    return 0;
}

/** Docstring: Copy the clipboard into out (cap bytes). Returns the
 * length, or -1 when empty/cleared. Fail-closed on an undersize
 * buffer (refuse, never a silently truncated paste). */
int clip_get(char *out, unsigned long cap) {
    unsigned long i;
    if (!out || cap == 0u) return -1;
    if (!clip_valid || clip_len == 0u) return -1;
    if ((unsigned long)clip_len > cap) return -1;
    for (i = 0u; i < clip_len; i++) out[i] = clip_buf[i];
    return (int)clip_len;
}

/** Docstring: Empty the clipboard. Reads then report -1 (empty). */
void clip_clear(void) {
    clip_len = 0u;
    clip_valid = 0;
}

/** Docstring: Current length, or -1 when empty. Lets callers size the
 * read buffer before getting. */
int clip_len_get(void) {
    if (clip_valid && clip_len > 0u) return (int)clip_len;
    return -1;
}
