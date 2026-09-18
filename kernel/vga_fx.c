/* DOOM-melt desktop effects (see headers/vga_fx.h for the contract).
 *
 * Owns the heap snapshots, the per-frame melt driver and the pacing clock.
 * Column fronts come from vga_fx.h (the f_wipe.c mirror); this file only
 * moves pixels between the heap buffers and the framebuffer through the
 * mode-independent packed primitives, so 8-bit and true-color modes share
 * one path. Every entry fails closed: a disabled effect, a degenerate rect
 * or an OOM snapshot draws nothing extra and leaves the new frame in place.
 */

#include "kernel.h"
#include "vga_fb.h"
#include "vga_fx.h"

static int fx_enabled = 1;

/* Melt transitions completed since boot. The shell's `fx` builtin reports
 * it, so the BDD suite proves melts actually ran (not merely finished with
 * the right frame, which a skipped melt also leaves behind). */
unsigned long fx_melts_completed;

void vga_fx_set_enabled(int on)
{
    fx_enabled = on ? 1 : 0;
}

int vga_fx_enabled(void)
{
    return fx_enabled;
}

/* Busy-wait pacing over the PIT-calibrated TSC clock. Interrupts stay on,
 * so the 100 Hz tick keeps running; a concurrent desktop tick may tear one
 * melt frame cosmetically, never corrupt state. */
static void fx_wait_ms(unsigned long ms)
{
    unsigned long t0 = ktime_ms();
    while (ktime_ms() - t0 < ms) {
    }
}

unsigned int *vga_fx_snap_rect(int x, int y, int w, int h)
{
    unsigned int *buf;
    unsigned long n;
    int r, c;
    if (vga_fx_clamp_rect(&x, &y, &w, &h, fb_width, fb_height)) {
        return 0;
    }
    n = (unsigned long)w * (unsigned long)h;
    if (n == 0 || n > (unsigned long)VGA_FX_COLS_MAX * 1024UL) {
        return 0;
    }
    buf = kmalloc(n * sizeof(unsigned int));
    if (!buf) {
        return 0;
    }
    for (r = 0; r < h; r++) {
        for (c = 0; c < w; c++) {
            buf[(unsigned long)r * (unsigned long)w + (unsigned long)c] =
                (unsigned int)fb_read_packed(x + c, y + r);
        }
    }
    return buf;
}

void vga_fx_restore_rect(int x, int y, int w, int h, const unsigned int *buf)
{
    int r, c;
    if (!buf) {
        return;
    }
    if (vga_fx_clamp_rect(&x, &y, &w, &h, fb_width, fb_height)) {
        return;
    }
    for (r = 0; r < h; r++) {
        for (c = 0; c < w; c++) {
            fb_write_packed(x + c, y + r,
                (unsigned long)buf[(unsigned long)r * (unsigned long)w + (unsigned long)c]);
        }
    }
}

void vga_fx_free(unsigned int *buf)
{
    if (buf) {
        kfree(buf);
    }
}

/* Drive one old->new melt. The framebuffer must show the old rect on entry
 * and shows the new rect on return. Each pixel is written exactly once:
 * prev[] tracks the revealed frontier per column, so the total cost is one
 * rect copy plus the pacing waits. */
void vga_fx_melt_rect(int x, int y, int w, int h,
    const unsigned int *oldb, const unsigned int *newb)
{
    vga_fx_config_t cfg = VGA_FX_CONFIG_DEFAULT;
    int *cols;
    int *prev;
    int i, r;
    int frames;
    (void)oldb;
    if (!newb) {
        return;
    }
    if (vga_fx_clamp_rect(&x, &y, &w, &h, fb_width, fb_height)) {
        return;
    }
    cols = kmalloc((unsigned long)w * 2UL * sizeof(int));
    if (!cols) {
        vga_fx_restore_rect(x, y, w, h, newb);
        return;
    }
    prev = cols + w;
    if (vga_fx_init_cols(&cfg, cols, w)) {
        kfree(cols);
        vga_fx_restore_rect(x, y, w, h, newb);
        return;
    }
    for (i = 0; i < w; i++) {
        prev[i] = 0;
    }
    frames = h + cfg.max_delay + 8;
    while (frames-- > 0) {
        int done = vga_fx_advance(&cfg, cols, w, h);
        for (i = 0; i < w; i++) {
            int front = vga_fx_front(cols[i], h);
            for (r = prev[i]; r < front; r++) {
                fb_write_packed(x + i, y + r,
                    (unsigned long)newb[(unsigned long)r * (unsigned long)w + (unsigned long)i]);
            }
            prev[i] = front;
        }
        if (done) {
            break;
        }
        fx_wait_ms((unsigned long)cfg.frame_ms);
    }
    fx_melts_completed++;
    vga_fx_restore_rect(x, y, w, h, newb);
    kfree(cols);
}

/* Boot melt: the framebuffer is already cleared to black on entry, so no
 * old snapshot is needed; the new frame scrolls down over black. */
void vga_fx_melt_from_black(int x, int y, int w, int h, const unsigned int *newb)
{
    vga_fx_config_t cfg = VGA_FX_CONFIG_DEFAULT;
    int *cols;
    int *prev;
    int i, r;
    int frames;
    if (!newb) {
        return;
    }
    if (vga_fx_clamp_rect(&x, &y, &w, &h, fb_width, fb_height)) {
        return;
    }
    cols = kmalloc((unsigned long)w * 2UL * sizeof(int));
    if (!cols) {
        vga_fx_restore_rect(x, y, w, h, newb);
        return;
    }
    prev = cols + w;
    if (vga_fx_init_cols(&cfg, cols, w)) {
        kfree(cols);
        vga_fx_restore_rect(x, y, w, h, newb);
        return;
    }
    for (i = 0; i < w; i++) {
        prev[i] = 0;
    }
    frames = h + cfg.max_delay + 8;
    while (frames-- > 0) {
        int done = vga_fx_advance(&cfg, cols, w, h);
        for (i = 0; i < w; i++) {
            int front = vga_fx_front(cols[i], h);
            for (r = prev[i]; r < front; r++) {
                fb_write_packed(x + i, y + r,
                    (unsigned long)newb[(unsigned long)r * (unsigned long)w + (unsigned long)i]);
            }
            prev[i] = front;
        }
        if (done) {
            break;
        }
        fx_wait_ms((unsigned long)cfg.frame_ms);
    }
    fx_melts_completed++;
    vga_fx_restore_rect(x, y, w, h, newb);
    kfree(cols);
}
