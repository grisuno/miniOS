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

/* Fire and genie transitions are counted both here and in the total above,
 * so the serial report can prove which effect a trigger point chose. */
unsigned long fx_burns_completed;
unsigned long fx_genies_completed;

void vga_fx_set_enabled(int on)
{
    fx_enabled = on ? 1 : 0;
}

int vga_fx_enabled(void)
{
    return fx_enabled;
}

/* Deadline pacing over the PIT-calibrated TSC clock. Interrupts stay on,
 * so the 100 Hz tick keeps running; a concurrent desktop tick may tear one
 * melt frame cosmetically, never corrupt state. */
static void fx_wait_until(unsigned long deadline)
{
    while ((long)(deadline - ktime_ms()) > 0) {
    }
}

unsigned int *vga_fx_snap_rect(int x, int y, int w, int h)
{
    unsigned int *buf;
    unsigned long n;
    int r;
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
        fb_read_row_packed(x, y + r, buf + (unsigned long)r * (unsigned long)w, w);
    }
    return buf;
}

void vga_fx_restore_rect(int x, int y, int w, int h, const unsigned int *buf)
{
    int r;
    if (!buf) {
        return;
    }
    if (vga_fx_clamp_rect(&x, &y, &w, &h, fb_width, fb_height)) {
        return;
    }
    for (r = 0; r < h; r++) {
        fb_write_row_packed(x, y + r, buf + (unsigned long)r * (unsigned long)w, w);
    }
}

void vga_fx_free(unsigned int *buf)
{
    if (buf) {
        kfree(buf);
    }
}

/* Shared melt driver: reveal newb over whatever the rect shows on entry.
 * Column fronts advance in virtual melt frames of cfg.frame_ms each, and
 * the driver catches up by elapsed time: a paint that took longer than a
 * frame advances several frames before the next paint, so the melt always
 * finishes in its nominal duration and moves at a constant speed instead
 * of stuttering whenever a paint runs slow. Each pixel is written exactly
 * once (prev[] tracks the revealed frontier per column), then the final
 * restore guarantees the exact new frame. */
static void fx_melt_run(int x, int y, int w, int h, const unsigned int *newb)
{
    vga_fx_config_t cfg = VGA_FX_CONFIG_DEFAULT;
    int *cols;
    int *prev;
    int i, r;
    int budget;
    int done = 0;
    unsigned long t0;
    unsigned long frames_done = 0;
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
    budget = h + cfg.max_delay + 8;
    t0 = ktime_ms();
    while (!done && budget > 0) {
        unsigned long due = (ktime_ms() - t0) / (unsigned long)cfg.frame_ms + 1UL;
        while (frames_done < due && !done && budget > 0) {
            done = vga_fx_advance(&cfg, cols, w, h);
            frames_done++;
            budget--;
        }
        for (i = 0; i < w; i++) {
            int front = vga_fx_front(cols[i], h);
            for (r = prev[i]; r < front; r++) {
                fb_write_packed(x + i, y + r,
                    (unsigned long)newb[(unsigned long)r * (unsigned long)w + (unsigned long)i]);
            }
            prev[i] = front;
        }
        if (!done) {
            fx_wait_until(t0 + frames_done * (unsigned long)cfg.frame_ms);
        }
    }
    fx_melts_completed++;
    vga_fx_restore_rect(x, y, w, h, newb);
    kfree(cols);
}

/* Drive one old->new melt. The framebuffer must show the old rect on entry
 * and shows the new rect on return. */
void vga_fx_melt_rect(int x, int y, int w, int h,
    const unsigned int *oldb, const unsigned int *newb)
{
    (void)oldb;
    fx_melt_run(x, y, w, h, newb);
}

/* Boot melt: the framebuffer is already cleared to black on entry, so no
 * old snapshot is needed; the new frame scrolls down over black. */
void vga_fx_melt_from_black(int x, int y, int w, int h, const unsigned int *newb)
{
    fx_melt_run(x, y, w, h, newb);
}

/* Fire driver: burn the old rect away into the new one. Ignition times are
 * computed once per pixel (vga_fx_burn_threshold), then each frame only
 * compares them with the elapsed-time progress, picks the old or new pixel
 * and lays the flame over it (vga_fx_burn_pixel/compose). Rows are built in
 * a scratch buffer and written once. oldb/newb are the rect's origin inside
 * buffers of `stride` pixels per row, so full-frame snapshots and exact rect
 * snapshots share this path. The loop is time-bounded and the final restore
 * writes the exact new frame. */
void vga_fx_burn_rect(int x, int y, int w, int h,
    const unsigned int *oldb, const unsigned int *newb, int stride)
{
    vga_fx_motion_t cfg = VGA_FX_MOTION_DEFAULT;
    short *thr;
    unsigned int *row;
    unsigned long t0;
    int span = vga_fx_burn_span(&cfg);
    int lx, ly;
    int frame = 0;
    if (!oldb || !newb || stride <= 0) {
        return;
    }
    if (vga_fx_clamp_rect(&x, &y, &w, &h, fb_width, fb_height) || w > stride) {
        return;
    }
    thr = kmalloc((unsigned long)w * (unsigned long)h * sizeof(short));
    row = kmalloc((unsigned long)w * sizeof(unsigned int));
    if (!thr || !row) {
        if (thr) {
            kfree(thr);
        }
        if (row) {
            kfree(row);
        }
        for (ly = 0; ly < h; ly++) {
            fb_write_row_packed(x, y + ly, newb + (unsigned long)ly * (unsigned long)stride, w);
        }
        return;
    }
    for (ly = 0; ly < h; ly++) {
        for (lx = 0; lx < w; lx++) {
            thr[(unsigned long)ly * (unsigned long)w + (unsigned long)lx] =
                (short)vga_fx_burn_threshold(&cfg, lx, ly, w, h);
        }
    }
    t0 = ktime_ms();
    for (;;) {
        unsigned long el = ktime_ms() - t0;
        int prog;
        if (el >= (unsigned long)cfg.burn_ms) {
            break;
        }
        prog = (int)((el * (unsigned long)span) / (unsigned long)cfg.burn_ms);
        for (ly = 0; ly < h; ly++) {
            const unsigned int *o = oldb + (unsigned long)ly * (unsigned long)stride;
            const unsigned int *n = newb + (unsigned long)ly * (unsigned long)stride;
            const short *t = thr + (unsigned long)ly * (unsigned long)w;
            for (lx = 0; lx < w; lx++) {
                int heat;
                int use_new = vga_fx_burn_pixel(&cfg, t[lx], prog, &heat);
                row[lx] = vga_fx_burn_compose(use_new ? n[lx] : o[lx], heat);
            }
            fb_write_row_packed(x, y + ly, row, w);
        }
        frame++;
        fx_wait_until(t0 + (unsigned long)frame * (unsigned long)VGA_FX_FRAME_MS);
    }
    for (ly = 0; ly < h; ly++) {
        fb_write_row_packed(x, y + ly, newb + (unsigned long)ly * (unsigned long)stride, w);
    }
    fx_melts_completed++;
    fx_burns_completed++;
    kfree(row);
    kfree(thr);
}

/* Genie driver: suck the window into (tx, ty), or pull it out when
 * `reverse` is set. bgb is the full frame without the window, winb the full
 * frame with it (both fb_width x fb_height). Each frame computes, per source
 * row, where it lands and how wide it is (vga_fx_genie_row), scatters rows
 * to screen rows (monotonic, so gap-free) and writes every screen row of the
 * affected band once: background with the narrowed window row over it,
 * sampled nearest-neighbour with 16.16 stepping. The final frame is the
 * state the caller drew (window gone, or window shown). */
void vga_fx_genie_rect(int wx, int wy, int ww, int wh, int tx, int ty,
    const unsigned int *bgb, const unsigned int *winb, int reverse)
{
    vga_fx_motion_t cfg = VGA_FX_MOTION_DEFAULT;
    const unsigned int *final_b = reverse ? winb : bgb;
    int *meta;
    unsigned int *row;
    int rx0, rx1, ry0, ry1, rw, rh;
    int r, i;
    unsigned long t0;
    int frame = 0;
    if (!bgb || !winb) {
        return;
    }
    if (vga_fx_clamp_rect(&wx, &wy, &ww, &wh, fb_width, fb_height)) {
        return;
    }
    if (ty > fb_height - 1) {
        ty = fb_height - 1;
    }
    if (ty < wy + wh - 1) {
        ty = wy + wh - 1;
    }
    rx0 = wx < tx - ww / 2 ? wx : tx - ww / 2;
    rx1 = wx + ww > tx + ww / 2 ? wx + ww : tx + ww / 2;
    if (rx0 < 0) {
        rx0 = 0;
    }
    if (rx1 > fb_width) {
        rx1 = fb_width;
    }
    ry0 = wy;
    ry1 = ty + 1;
    rw = rx1 - rx0;
    rh = ry1 - ry0;
    if (rw <= 0 || rh <= 0) {
        return;
    }
    meta = kmalloc((unsigned long)rh * 3UL * sizeof(int));
    row = kmalloc((unsigned long)rw * sizeof(unsigned int));
    if (!meta || !row) {
        if (meta) {
            kfree(meta);
        }
        if (row) {
            kfree(row);
        }
        return;
    }
    t0 = ktime_ms();
    for (;;) {
        unsigned long el = ktime_ms() - t0;
        int prog;
        int prev_dy = 0, prev_l = 0, prev_w = 1, have_prev = 0;
        if (el >= (unsigned long)cfg.genie_ms) {
            break;
        }
        prog = (int)((el * (unsigned long)VGA_FX_PROG_ONE) / (unsigned long)cfg.genie_ms);
        if (reverse) {
            prog = VGA_FX_PROG_ONE - prog;
        }
        for (i = 0; i < rh; i++) {
            meta[i * 3] = -1;
        }
        for (r = 0; r < wh; r++) {
            int dy, left, width;
            int from, to, k;
            if (vga_fx_genie_row(&cfg, wx, wy, ww, wh, tx, ty, r, prog, &dy, &left, &width)) {
                continue;
            }
            if (have_prev) {
                from = prev_dy - ry0;
                to = dy - ry0;
                if (to <= from) {
                    to = from + 1;
                }
                for (k = from; k < to && k < rh; k++) {
                    if (k >= 0) {
                        meta[k * 3] = r - 1;
                        meta[k * 3 + 1] = prev_l;
                        meta[k * 3 + 2] = prev_w;
                    }
                }
            }
            prev_dy = dy;
            prev_l = left;
            prev_w = width;
            have_prev = 1;
            if (r == wh - 1 && dy - ry0 >= 0 && dy - ry0 < rh) {
                meta[(dy - ry0) * 3] = r;
                meta[(dy - ry0) * 3 + 1] = left;
                meta[(dy - ry0) * 3 + 2] = width;
            }
        }
        for (i = 0; i < rh; i++) {
            int src = meta[i * 3];
            const unsigned int *bgr = bgb + (unsigned long)(ry0 + i) * (unsigned long)fb_width + (unsigned long)rx0;
            int c;
            for (c = 0; c < rw; c++) {
                row[c] = bgr[c];
            }
            if (src >= 0) {
                int left = meta[i * 3 + 1];
                int width = meta[i * 3 + 2];
                const unsigned int *wr = winb + (unsigned long)(wy + src) * (unsigned long)fb_width + (unsigned long)wx;
                unsigned long step = ((unsigned long)ww << 16) / (unsigned long)(width > 0 ? width : 1);
                unsigned long pos = 0;
                int xd;
                for (xd = left; xd < left + width; xd++, pos += step) {
                    int cx = xd - rx0;
                    if (cx >= 0 && cx < rw) {
                        row[cx] = wr[(int)(pos >> 16) < ww ? (int)(pos >> 16) : ww - 1];
                    }
                }
            }
            fb_write_row_packed(rx0, ry0 + i, row, rw);
        }
        frame++;
        fx_wait_until(t0 + (unsigned long)frame * (unsigned long)VGA_FX_FRAME_MS);
    }
    for (i = 0; i < rh; i++) {
        fb_write_row_packed(rx0, ry0 + i,
            final_b + (unsigned long)(ry0 + i) * (unsigned long)fb_width + (unsigned long)rx0, rw);
    }
    fx_melts_completed++;
    fx_genies_completed++;
    kfree(row);
    kfree(meta);
}
