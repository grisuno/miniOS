/*
 * vga_fb.c  --  Mode 13h framebuffer desktop (320x200, 256 colors)
 *
 * Desktop with terminal window, PS/2 mouse cursor, scrollbar and
 * scrollback buffer.  When vga_fb_active, all kernel output renders
 * in the framebuffer terminal instead of VGA text buffer 0xB8000.
 * Keyboard shortcuts: F11=fullscreen, Ctrl+arrows=move, F5=reset.
 */
/**
 * Docstring: vga_fb desktop with terminal windows, mouse cursor and taskbar.
 *
 * Window geometry and mouse edge detection delegate to the wm_geom and
 * wm_events contracts. Drag state lives at file scope so a focus change
 * can reset it instead of leaking a stale grab into the next gesture.
 */
#include "kernel.h"
#include "kernel/vga_cursor.h"
#include "vga_fb.h"
#include "bootdefs.h"
#include "sched.h"
#include "drivers/kbd.h"
#include "desktop_shortcuts.h"
#include "desktop_icons.h"
#include "stb_api.h"
#include "wm_geom.h"
#include "wm_events.h"
#include "wm_window.h"
#include "wm_render.h"
#include "wm_tiling.h"
#include "wm_focus.h"
#include "wm_layout.h"
#include "wm_notify.h"
#include "wm_gfxview.h"
#include "vga_fx.h"

/** Docstring: Focus ids share one space across terminals and graphics. */
_Static_assert(WM_FOCUS_GFX == WM_WINDOW_GFX_ID,
               "gfx focus id drifted from unified window contract");

/** Docstring: File-scope drag state shared by the tick and focus paths. */
static int wm_dragging;
static int wm_grab_cx;
static int wm_skip_drag;
static int wm_gdrag;
static int wm_ggx;
static int wm_ggy;

/** Docstring: Geometry config derived once from the font layout. */
static wm_geom_config_t wm_geom_cfg(void)
{
    wm_geom_config_t cfg;
    cfg.font_w = FONT_W;
    cfg.font_h = FONT_H;
    cfg.scrollbar_w = SCROLLBAR_W;
    cfg.title_h = FONT_H;
    return cfg;
}

/** Docstring: Event config for the PS/2 mouse button mask. */
static wm_event_config_t wm_event_cfg(void)
{
    wm_event_config_t cfg;
    cfg.left_mask = 1;
    cfg.wheel_step = 3;
    return cfg;
}

/** Docstring: Reset terminal and graphics drag grabs on focus change. */
static void wm_drag_reset(void)
{
    wm_dragging = 0;
    wm_grab_cx = 0;
    wm_skip_drag = 0;
    wm_gdrag = 0;
    wm_ggx = 0;
    wm_ggy = 0;
}

int vga_fb_active;
unsigned long gfx_frames_composited;

/* Framebuffer geometry, sized by vga_fb_boot_config from the VBE info the
 * boot loader recorded (Mode 13h defaults when VBE is unavailable). */
int fb_width  = 320;
int fb_height = 200;
int fb_pitch  = 320;
int fb_bpp    = 8;
unsigned long fb_phys_base = 0x000A0000UL;

void vga_fb_boot_config(void) {
    volatile uint8_t *p = (volatile uint8_t *)VBE_INFO_ADDR;
    unsigned long base;
    unsigned pitch, width, height, bpp;
    int valid = p[VBE_INFO_VALID_OFF];
    if (!valid) return;
    base   = p[VBE_INFO_FBBASE_OFF + 0]
           | ((unsigned long)p[VBE_INFO_FBBASE_OFF + 1] << 8)
           | ((unsigned long)p[VBE_INFO_FBBASE_OFF + 2] << 16)
           | ((unsigned long)p[VBE_INFO_FBBASE_OFF + 3] << 24);
    pitch  = p[VBE_INFO_PITCH_OFF + 0] | (p[VBE_INFO_PITCH_OFF + 1] << 8);
    width  = p[VBE_INFO_WIDTH_OFF + 0] | (p[VBE_INFO_WIDTH_OFF + 1] << 8);
    height = p[VBE_INFO_HEIGHT_OFF + 0] | (p[VBE_INFO_HEIGHT_OFF + 1] << 8);
    bpp    = p[VBE_INFO_BPP_OFF];
    if (base == 0 || width == 0 || height == 0 || pitch == 0)
        return;
    /* Only the modes stage 2 probes are accepted; anything else keeps the
     * 8-bit defaults instead of misinterpreting the framebuffer layout. */
    if (bpp != 8 && bpp != 24 && bpp != 32)
        bpp = 8;
    fb_phys_base = base;
    fb_pitch     = pitch;
    fb_width     = width;
    fb_height    = height;
    fb_bpp       = (int)bpp;
}

int fb_bytes_per_pixel(void) {
    if (fb_bpp == 32) return 4;
    if (fb_bpp == 24) return 3;
    return 1;
}

/* ---- Render target (double-buffered desktop composition) ----
 *
 * Every drawing primitive in this file writes through FBT. It is the
 * framebuffer itself unless a full desktop composition is in flight, in
 * which case it is an off-screen heap shadow of identical layout (same
 * pitch, same pixel format). A composition clears, repaints wallpaper,
 * dock, taskbar, terminals and the graphics layer into the shadow and
 * then presents it with one bulk copy, so the screen never shows the
 * intermediate cleared or half-painted frame: that transient is exactly
 * the flash every drag, Alt-Tab and tile used to produce. Nested
 * compositions (an ISR tick composing inside a syscall composition) draw
 * into the same shadow and leave the present to the outermost owner.
 * The shadow is allocated once on first use and never freed (no
 * alloc/free race with the ISR tick); an OOM degrades to direct drawing,
 * which is the historical behaviour. A held present leaves the finished
 * frame in the shadow so a melt can read it and reveal it instead of
 * flashing it first. */
static volatile uint8_t *fb_tgt;
static uint8_t *fb_shadow;
static unsigned long fb_shadow_bytes;
static int fb_compose_depth;
static int fb_hold_present;
#define FBT (fb_tgt ? fb_tgt : FB_ADDR)

/** Docstring: Bulk copy through the string engine: quadwords first
 * (rep movsq, an eighth of the iterations, which is what matters under
 * an emulator that runs every string iteration as its own step), then
 * the byte tail. Source and destination never overlap here. */
static void fb_copy_bytes(volatile void *dst, const volatile void *src, unsigned long n)
{
    void *d = (void *)dst;
    const void *s = (const void *)src;
    unsigned long q = n >> 3;
    unsigned long t = n & 7UL;
    __asm__ volatile("cld; rep movsq"
                     : "+D"(d), "+S"(s), "+c"(q)
                     :
                     : "memory");
    __asm__ volatile("rep movsb"
                     : "+D"(d), "+S"(s), "+c"(t)
                     :
                     : "memory");
}

/** Docstring: Fill n 32-bit words with one value: pairs as quadwords
 * (rep stosq), then the odd word. */
static void fb_fill_u32(volatile void *dst, unsigned int v, unsigned long n)
{
    void *d = (void *)dst;
    unsigned long q = n >> 1;
    unsigned long pat = ((unsigned long)v << 32) | (unsigned long)v;
    __asm__ volatile("cld; rep stosq"
                     : "+D"(d), "+c"(q)
                     : "a"(pat)
                     : "memory");
    if (n & 1UL)
        *(volatile unsigned int *)d = v;
}

/** Docstring: Bytes one framebuffer frame spans (pitch times height). */
static unsigned long fb_frame_bytes(void)
{
    return (unsigned long)fb_pitch * (unsigned long)fb_height;
}

/** Docstring: Ensure the shadow exists; 1 when it is usable. */
static int fb_shadow_ready(void)
{
    unsigned long need = fb_frame_bytes();
    if (need == 0) {
        return 0;
    }
    if (fb_shadow && fb_shadow_bytes >= need) {
        return 1;
    }
    if (fb_shadow) {
        return 0;
    }
    fb_shadow = (uint8_t *)kmalloc(need);
    if (!fb_shadow) {
        return 0;
    }
    fb_shadow_bytes = need;
    return 1;
}

/** Docstring: Copy the whole shadow onto the visible framebuffer. */
static void fb_present_shadow(void)
{
    if (!fb_shadow) {
        return;
    }
    fb_copy_bytes(FB_ADDR, fb_shadow, fb_frame_bytes());
}

/** Docstring: Enter a composition. Returns 1 for the outermost owner
 * that redirected drawing into the shadow, 0 for a nested or degraded
 * entry that must not present. */
static int fb_compose_begin(void)
{
    if (fb_compose_depth++ > 0) {
        return 0;
    }
    if (!fb_shadow_ready()) {
        return 0;
    }
    fb_tgt = fb_shadow;
    return 1;
}

/** Docstring: Leave a composition; the owner presents unless held. */
static void fb_compose_end(int owner)
{
    if (fb_compose_depth > 0) {
        fb_compose_depth--;
    }
    if (!owner) {
        return;
    }
    fb_tgt = 0;
    if (!fb_hold_present) {
        fb_present_shadow();
    }
}

/* ---- Mouse state (fed by sched.c IRQ12 handler) ---- */
mouse_state_t mouse_state;

/* True-color pixel layer (defined beside the palette tables below). In a
 * 32/24-bit mode every palette-index write is expanded to RGB here, so all
 * drawing code above keeps speaking indices; in 8-bit mode the helpers are
 * plain framebuffer accesses. Packed pixels are 0x00RRGGBB. */
static unsigned long fb_pack_idx(unsigned idx);
unsigned long fb_read_packed(int x, int y);
void fb_write_packed(int x, int y, unsigned long rgb);

/* Forward: the wallpaper cache lives with the shortcut-icon code below, but
 * the desktop painter above needs it. */
static void wallpaper_draw(void);
static int icon_nearest(int r, int g, int b);
static const uint8_t *gfx_task_icon(void);
static void taskbar_layout(void);
static int tb_gfx_x, tb_gfx_w;
static struct desktop_shortcut shortcuts[MAX_SHORTCUTS];
static int shortcut_count;

/* ---- Unified terminal buffer (logical lines, re-flowed at display width) ----
 *
 * The whole terminal history lives in ONE place: a ring of logical lines
 * (`lg`) holding every completed line, plus the in-progress line being typed
 * or emitted (`act`). The screen is never stored pre-wrapped; on every render
 * the visible window is reconstructed by wrapping the logical lines at the
 * current `term_cols`. Because there is a single source of truth, live screen
 * and scrollback can never disagree, and resizing the window re-wraps the
 * content instead of clipping it.
 *
 * A display row is the slice of a logical line that fits in `term_cols`
 * columns. A logical line of length L occupies max(1, ceil(L/term_cols))
 * display rows. The whole history occupies `total_rows` display rows stacked
 * oldest at top, and the viewport shows `term_rows` of them. `disp_off` is
 * how many display rows the viewport is scrolled up from the bottom (0 =
 * live). Scrolling is implicit: completed lines naturally leave the viewport
 * as new content is added, and remain reachable in the ring.
 *
 * There is deliberately no "scroll the screen up" operation. A completed
 * logical line is pushed to the ring exactly once, when it ends with '\n';
 * that eliminates the duplicated/partial scrollback entries the old two-buffer
 * scheme produced, which were the source of the pixel artifacts. */
/** Docstring: Completed-logical-lines ring, heap-owned since the .bss
 * diet (256 x TERM_MAX_COLS). Null until vga_fb_init owns it; pushes
 * before then are dropped and reads see an empty ring, so early boot
 * text still reaches the screen and serial without a scrollback entry. */
static char (*lg)[SB_LINE_MAX] = 0;
#define LG_LINE(a) (lg[(a) % SB_MAX_LINES])
static int  lg_head, lg_tail, lg_count;
static char act[SB_LINE_MAX];                /* in-progress line */
static int  act_len;
static int  disp_off;                        /* scrollback rows above the bottom */
static int  term_cursor_col = -1;            /* text cursor column (-1 = hidden) */
static int  csi_state;                       /* ANSI CSI drop: 1 after ESC, 2 in params */

/* Ring accessor: logical line at age i (0 = oldest, count-1 = newest). */
static const char *lg_get(int i) {
    if (!lg) return "";
    return LG_LINE(lg_head + i);
}

/* Append a completed logical line to the ring. The line is stored whole (no
 * width-dependent wrap), so it can be re-wrapped on any future resize. */
static void lg_push(const char *line, int len) {
    int k, idx;
    char *dst;
    if (!lg) return;
    if (len >= SB_LINE_MAX) len = SB_LINE_MAX - 1;
    idx = lg_tail;
    dst = LG_LINE(idx);
    for (k = 0; k < len; k++) dst[k] = line[k];
    dst[len] = '\0';
    lg_tail = (lg_tail + 1) % SB_MAX_LINES;
    if (lg_count < SB_MAX_LINES) lg_count++;
    else lg_head = (lg_head + 1) % SB_MAX_LINES;
}

/* Display rows a logical line of `len` characters occupies at term_cols. */
static int line_nrows(int len) {
    int w = term_cols > 0 ? term_cols : 1;
    int n = len / w + (len % w ? 1 : 0);
    if (n < 1) n = 1;   /* an empty line still shows as one row */
    return n;
}

static int act_nrows(void) { return line_nrows(act_len); }

/* Total display rows of the whole history (completed lines + active line). */
static int total_rows(void) {
    int t = 0, i;
    for (i = 0; i < lg_count; i++)
        t += line_nrows((int)kstrlen(lg_get(i)));
    return t + act_nrows();
}

/* Clamp disp_off to a legal scroll range. */
static void disp_clamp(void) {
    int tr = total_rows();
    int max = tr > term_rows ? tr - term_rows : 0;
    if (disp_off > max) disp_off = max;
    if (disp_off < 0)   disp_off = 0;
}

/* Absolute display-row index of the top of the viewport. Negative when the
 * history is shorter than the window (those rows are rendered blank). */
static int disp_top(void) {
    int tr = total_rows();
    if (tr <= term_rows) return tr - term_rows;
    return (tr - term_rows) - disp_off;
}

/* Locate the logical line contributing the display row `abs`, and set *off to
 * the character offset where that display row starts. Returns the line text,
 * or 0 when abs is beyond the history. */
static const char *line_at(int abs, int *off) {
    int acc = 0, i;
    for (i = 0; i < lg_count; i++) {
        const char *l = lg_get(i);
        int n = line_nrows((int)kstrlen(l));
        if (abs < acc + n) { *off = (abs - acc) * term_cols; return l; }
        acc += n;
    }
    if (abs < acc + act_nrows()) { *off = (abs - acc) * term_cols; return act; }
    return 0;
}

static void draw_scrollbar(void);
static void term_render(void);

/* Pointer sprite state and ops live in kernel/vga_cursor.c; this file
 * reaches them through kernel/vga_cursor.h. */


/* ---- Graphics-mode pointer (compositor contract) ----
 *
 * While a ring-3 graphics program owns the display (SYS_VGA_MODE 1) the
 * kernel never runs the idle loop that drives vga_fb_mouse_tick, so the
 * desktop pointer would simply vanish as soon as e.g. the Nuklear node
 * editor composites its first frame. The frame syscalls take its place:
 * the kernel restores the previous frame's pointer before a composite and
 * redraws it afterwards, using the same save/restore machinery as the
 * desktop path, so the pointer stays live over the whole display without
 * ever leaving a trail. */
static int vga_fb_gfx_mode;

/* Geometry of the last composited graphics window (DOOM or Nuklear). The WM
 * uses it to hit-test the title-bar window controls while a graphics program
 * owns the display. gfx_win_ox/oy are WM offsets added to the centered
 * position (move/snap/tile/drag write them; 0 = centered); gfx_win_h is the
 * content height for hit-testing. Offsets reset when graphics mode ends, so
 * the next program starts centered. */
static int gfx_win_x, gfx_win_y, gfx_win_w, gfx_win_h;
static int gfx_win_ox, gfx_win_oy;

/* DOOM-melt transition state (kernel/vga_fx.c owns the pixels, this file
 * owns the trigger points). fx_gfx_armed melts the first composite after a
 * mode-on (window appears); fx_close_* melts the desktop over the last
 * graphics rect on the redraw that follows a mode-off (window disappears).
 * Terminal show/hide (minimize, fullscreen, split, close) snapshots around
 * their own redraw through fx_start/finish_full below. Moves, resizes,
 * snaps, tiles and focus changes never melt: they relocate, not appear. */
static int fx_gfx_armed;
static int fx_close_pending;
static int fx_close_x, fx_close_y, fx_close_w, fx_close_h;

/* Snapshot the current fullscreen frame for a show/hide melt. Cursor erased
 * first so its pixels do not bake into the old frame. Returns 0 when the
 * effect is off or the snapshot OOMs, and the caller then just redraws.
 * On success the presents of the redraws that follow are held: the new
 * frame stays in the shadow, so fx_finish_full can melt it in without the
 * screen ever showing it whole first (the old flash-then-melt). */
static unsigned int *fx_start_full(void)
{
    unsigned int *oldb;
    if (!vga_fx_enabled()) {
        return 0;
    }
    cursor_erase();
    oldb = vga_fx_snap_rect(0, 0, fb_width, fb_height);
    if (oldb && fb_compose_depth == 0 && fb_shadow_ready()) {
        fb_hold_present = 1;
    }
    return oldb;
}

/* Complete a show/hide melt after the new state has been drawn: snapshot
 * the new frame (from the held shadow when there is one, else from the
 * screen after restoring the old pixels), melt old->new on the visible
 * framebuffer and free both snapshots. A 0 old snapshot (effect off or
 * OOM) is a no-op: the new frame stays. */
static void fx_finish_full(unsigned int *oldb)
{
    unsigned int *newb;
    int held = fb_hold_present;
    if (!oldb) {
        return;
    }
    fb_hold_present = 0;
    if (held) {
        fb_tgt = fb_shadow;
        newb = vga_fx_snap_rect(0, 0, fb_width, fb_height);
        fb_tgt = 0;
        if (!newb) {
            fb_present_shadow();
            vga_fx_free(oldb);
            cursor_invalidate();
            return;
        }
    } else {
        newb = vga_fx_snap_rect(0, 0, fb_width, fb_height);
        if (!newb) {
            vga_fx_free(oldb);
            return;
        }
        vga_fx_restore_rect(0, 0, fb_width, fb_height, oldb);
    }
    vga_fx_melt_rect(0, 0, fb_width, fb_height, oldb, newb);
    vga_fx_free(oldb);
    vga_fx_free(newb);
    cursor_invalidate();
}

/* Persistent graphics layer: a private copy of the last presented SOURCE
 * frame (the back-buffer bytes, before scaling), not of the screen pixels.
 * A desktop redraw (Alt+Tab, tile, drag, taskbar tick) wipes the whole
 * framebuffer, which used to bury any program that only composites on
 * input — vedit/Nuklear sit blocked in read with no next frame coming, so
 * the window vanished until the next keypress. draw_desktop re-composes
 * this copy on top after the terminals, at the CURRENT view: because the
 * copy is the unscaled source, the same frame re-renders correctly when
 * the window is re-tiled, maximized or animated between two rects, which
 * a screen-pixel copy could never do. One fixed buffer sized for the
 * largest source (the RGB Nuklear buffer), allocated once on the first
 * present and never freed: no alloc/free race between the syscall present
 * path and the ISR-driven desktop tick, and no UAF. The copy is taken
 * right after the present reads the back-buffer, so a program rendering
 * its next frame can never tear what the desktop re-shows. Validity
 * resets on mode-on so a new program never flashes the previous one. */
#define GFX_SRC_IDX 0
#define GFX_SRC_RGB 1
#define GFX_KEEP_BYTES ((unsigned long)NK_RGB_BYTES)
static uint8_t *gfx_keep;
static int gfx_keep_valid, gfx_keep_kind, gfx_keep_sw, gfx_keep_sh;

/* View state of the graphics window (wm_gfxview.h owns the math).
 * gfx_view_mode is the requested mode; gfx_view_back is where fullscreen
 * returns to; gfx_cell is the frame the tiling layout assigned; gfx_hidden
 * is the minimized flag (the program keeps running, nothing composites);
 * gfx_view is the geometry the last present or restore actually used, and
 * the hit-tests, `wm list` and the pointer map all read it, so what the WM
 * reports is always what is on screen. gfx_frame_dirty forces the next
 * present to repaint chrome plus letterbox (after a desktop redraw or a
 * view change); steady frames repaint only the title and the content. */
static int gfx_view_mode = WM_GFXVIEW_FLOAT;
static int gfx_view_back = WM_GFXVIEW_FLOAT;
static wm_gfxview_rect_t gfx_cell;
static int gfx_hidden;
static wm_gfxview_t gfx_view;
static int gfx_view_valid;
static int gfx_frame_dirty = 1;
static int gfx_suppress;
static int gfx_cursor_lx = -1, gfx_cursor_ly = -1;
static unsigned long gfx_cursor_moved;

/** Docstring: Hide the pointer over a fullscreen app after this many
 * idle timer ticks (100 Hz), so a game plays without a stray arrow. */
#define GFX_CURSOR_IDLE_TICKS 150

/** Docstring: Timer ticks (100 Hz) without a present after which the
 * desktop tick moves the pointer itself in graphics mode. An app that
 * presents only on damage (the FreeDom browser idles on a static page)
 * would otherwise freeze the arrow wherever its last frame left it. */
#define GFX_CURSOR_FOLLOW_TICKS 5

/* Handshake between the present path and the desktop tick, the two
 * painters of the graphics-mode pointer. A present announces itself and
 * waits out a tick that is mid-paint; the tick announces itself and backs
 * off when a present is running. Both sides are sequentially consistent,
 * so at most one of them ever touches the sprite. The tick runs in the
 * timer interrupt and never waits, so a present interrupted on its own
 * CPU cannot deadlock it. */
static volatile int gfx_presenting;
static volatile int gfx_cursor_following;
static volatile unsigned long gfx_last_present;

/** Docstring: View configuration shared by every graphics path. */
static wm_gfxview_config_t gfx_view_cfg(void)
{
    wm_gfxview_config_t cfg = WM_GFXVIEW_CONFIG_DEFAULT;
    cfg.title_h = FONT_H;
    return cfg;
}

/** Docstring: 1 while a visible fullscreen graphics window owns every
 * pixel: the terminals, taskbar and dock must not paint through it. */
static int gfx_covers_screen(void)
{
    return vga_fb_gfx_mode && !gfx_hidden && gfx_view_mode == WM_GFXVIEW_FULL;
}

/** Docstring: Copy the presented source into the persistent layer. */
static void gfx_keep_save(const volatile uint8_t *src, int kind, int sw, int sh)
{
    unsigned long n;
    if (!src || sw <= 0 || sh <= 0) return;
    n = (unsigned long)sw * (unsigned long)sh * (kind == GFX_SRC_RGB ? 3UL : 1UL);
    if (n > GFX_KEEP_BYTES) return;
    if (!gfx_keep) {
        gfx_keep = kmalloc(GFX_KEEP_BYTES);
        if (!gfx_keep) return;
    }
    fb_copy_bytes(gfx_keep, src, n);
    gfx_keep_kind = kind;
    gfx_keep_sw = sw;
    gfx_keep_sh = sh;
    gfx_keep_valid = 1;
}

/* Compositor identity for the taskbar button: basename of the program that
 * composited last. The shell records its fg launch name; the syscall layer
 * attributes every background frame to procs[current_pid].name, so the
 * button always shows whoever is actually on screen (last frame wins, same
 * as the pixels). Matched against the shortcut COMMANDS from etc/shortcuts
 * — never against a hardcoded app list. Cleared with the graphics mode. */
#define GFX_PROG_LEN 32
static char gfx_prog[GFX_PROG_LEN];

void vga_fb_set_gfx_program(const char *name) {
    unsigned long i = 0, start = 0;
    if (!name) {
        gfx_prog[0] = '\0';
        return;
    }
    {
        unsigned long k = kstrlen(name), j;
        for (j = 0; j < k; j++)
            if (name[j] == '/') start = j + 1;
    }
    for (i = 0; i < (unsigned long)(GFX_PROG_LEN - 1) && name[start + i]; i++)
        gfx_prog[i] = name[start + i];
    gfx_prog[i] = '\0';
}

/* Basename of a shortcut command's program: first token after an optional
 * `run`, then past the last '/'. "run quake2generic.elf +set basedir ." ->
 * "quake2generic.elf"; "nuklear" -> "nuklear". */
static void shcmd_base(const char *cmd, char *out, unsigned long cap) {
    unsigned long s = 0, e, i, last;
    if (cap == 0) return;
    out[0] = '\0';
    if (!cmd) return;
    if (kstrncmp(cmd, "run ", 4) == 0) s = 4;
    while (cmd[s] == ' ') s++;
    e = s;
    while (cmd[e] && cmd[e] != ' ') e++;
    last = s;
    for (i = s; i < e; i++)
        if (cmd[i] == '/') last = i + 1;
    for (i = 0; i + 1 < cap && last + i < e; i++)
        out[i] = cmd[last + i];
    out[i] = '\0';
}

static int ci_eq(const char *a, const char *b) {
    unsigned long i;
    for (i = 0; ; i++) {
        int ca = a[i], cb = b[i];
        if (ca >= 'A' && ca <= 'Z') ca += 32;
        if (cb >= 'A' && cb <= 'Z') cb += 32;
        if (ca != cb) return 0;
        if (ca == 0) return 1;
    }
}

/* Icon of the running program via the shortcuts config: whoever composited
 * last, resolved through its launch command. Zero hardcoded names. */
static const uint8_t *gfx_prog_icon(void) {
    int i;
    char base[GFX_PROG_LEN];
    desktop_shortcuts_load();
    if (!gfx_prog[0]) return 0;
    for (i = 0; i < shortcut_count; i++) {
        shcmd_base(shortcuts[i].cmd, base, sizeof(base));
        if (base[0] && ci_eq(base, gfx_prog)) return shortcuts[i].pixels;
    }
    return 0;
}

static void wm_gfx_focus_sync(int on);
void vga_fb_set_gfx_mode(int on) {
    vga_fb_gfx_mode = on;
    if (!on) {
        cursor_invalidate();
        gfx_win_ox = 0;
        gfx_win_oy = 0;
        gfx_prog[0] = '\0';
        /* Arm the close melt: the redraw that follows still shows the
         * graphics window, so draw_desktop snapshots this rect first. A
         * hidden window is not on screen, so there is nothing to melt. */
        if (gfx_win_w > 0 && gfx_win_h > 0 && !gfx_hidden) {
            fx_close_x = gfx_win_x;
            fx_close_y = gfx_win_y;
            fx_close_w = gfx_win_w;
            fx_close_h = gfx_win_h;
            fx_close_pending = 1;
        }
        gfx_view_mode = WM_GFXVIEW_FLOAT;
        gfx_view_back = WM_GFXVIEW_FLOAT;
        gfx_hidden = 0;
        gfx_view_valid = 0;
        gfx_keep_valid = 0;
    } else {
        /* Lift the desktop pointer while its saved background is still
         * exact: the focus sync below repaints chrome and invalidates the
         * sprite without restoring it, which stranded a dead arrow on the
         * wallpaper once the graphics pointer moved away. */
        cursor_erase();
        gfx_keep_valid = 0;
        gfx_view_valid = 0;
        gfx_hidden = 0;
        gfx_frame_dirty = 1;
        /* Arm the open melt: the next composite melts the desktop into
         * the fresh window instead of flashing it. */
        fx_gfx_armed = 1;
        fx_close_pending = 0;
    }
    wm_gfx_focus_sync(on);
    /* A new graphics program claims the display: drop any title the previous
     * one set (via SYS_GFX_SET_TITLE), so the next DOOM window is not
     * mis-labelled with the last program's name. */
    if (on) gfx_win_title = GFX_TITLE_DEFAULT;
}

/** Docstring: 2x nearest-neighbour zoom for the 320x200 game window,
 * set via SYS_GFX_ZOOM. One int of .bss; the NK buffer never zooms. */
int gfx_zoom_2x;

/** Docstring: Compute the view for a sw x sh source under the current
 * mode. A tiled mode without a usable cell, or any degenerate result,
 * falls back to floating so a frame is never dropped for geometry. */
static int gfx_view_for(int sw, int sh, wm_gfxview_t *v)
{
    wm_gfxview_config_t cfg = gfx_view_cfg();
    int zoom = (gfx_zoom_2x && sw == DOOM_W && sh == DOOM_H) ? 2 : 1;
    if (wm_gfxview_compute(&cfg, gfx_view_mode, sw, sh, zoom, fb_width,
                           fb_height, &gfx_cell, gfx_win_ox, gfx_win_oy, v))
        return 1;
    return wm_gfxview_compute(&cfg, WM_GFXVIEW_FLOAT, sw, sh, zoom, fb_width,
                              fb_height, &gfx_cell, gfx_win_ox, gfx_win_oy, v);
}

/** Docstring: Publish a view as the window geometry every reader uses. */
static void gfx_view_publish(const wm_gfxview_t *v)
{
    gfx_view = *v;
    gfx_view_valid = 1;
    gfx_win_x = v->frame.x;
    gfx_win_y = v->frame.y;
    gfx_win_w = v->frame.w;
    gfx_win_h = v->frame.h;
    nk_win_x = v->content.x;
    nk_win_y = v->content.y - FONT_H;
}

/** Docstring: Floating-mode frame of the current source, used by the
 * snap and drag math, which move the native window, never a tile. */
static int gfx_float_frame(wm_gfxview_rect_t *out)
{
    wm_gfxview_config_t cfg = gfx_view_cfg();
    wm_gfxview_t v;
    int sw = gfx_keep_valid ? gfx_keep_sw : DOOM_W;
    int sh = gfx_keep_valid ? gfx_keep_sh : DOOM_H;
    int zoom = (gfx_zoom_2x && sw == DOOM_W && sh == DOOM_H) ? 2 : 1;
    if (!wm_gfxview_compute(&cfg, WM_GFXVIEW_FLOAT, sw, sh, zoom, fb_width,
                            fb_height, 0, 0, 0, &v))
        return 0;
    *out = v.frame;
    return 1;
}

/** Docstring: Content origin of the graphics window (the point an app
 * subtracts from SYS_MOUSE coordinates), for the present syscalls. */
void vga_fb_gfx_origin(int *x, int *y)
{
    if (!x || !y) return;
    if (gfx_view_valid) {
        *x = gfx_view.content.x;
        *y = gfx_view.content.y;
    } else {
        *x = nk_win_x;
        *y = nk_win_y + FONT_H;
    }
}

/** Docstring: Map a desktop pointer into the graphics app's back-buffer
 * space when its view is scaled. A 1:1 view is left untouched so native
 * windows keep the exact historical coordinates (including outside the
 * window); a scaled view maps through the inverse transform so the app's
 * `mouse - origin` lands on the pixel under the arrow. */
void vga_fb_gfx_map_mouse(int *x, int *y)
{
    int sw, sh;
    if (!x || !y || !vga_fb_gfx_mode || !gfx_view_valid || !gfx_keep_valid)
        return;
    sw = gfx_keep_sw;
    sh = gfx_keep_sh;
    if (gfx_view.content.w == sw && gfx_view.content.h == sh)
        return;
    wm_gfxview_map_point(&gfx_view, sw, sh, *x, *y, x, y);
}

/* Restore the last composite's pointer before the new frame covers it. Only
 * meaningful in graphics mode; the desktop path (vga_fb_mouse_tick) manages
 * its own cursor with the same functions. */
static void vga_fb_gfx_cursor_erase(void) {
    if (!vga_fb_gfx_mode) return;
    cursor_erase();
}

/* Clamp the mouse into the framebuffer (the idle loop that normally clamps
 * never runs in graphics mode) and draw the pointer at the current position.
 * Over a fullscreen app the arrow hides after GFX_CURSOR_IDLE_TICKS without
 * motion and reappears on the next move, so a game never plays with a
 * stray pointer parked in the middle of the screen. */
static void vga_fb_gfx_cursor_draw(void) {
    int mx, my;
    if (!vga_fb_gfx_mode) return;
    mx = mouse_state.x;
    my = mouse_state.y;
    if (mx < 0) mx = 0;
    if (mx >= fb_width)    mx = fb_width - 1;
    if (my < 0) my = 0;
    if (my >= fb_height)   my = fb_height - 1;
    mouse_state.x = mx;
    mouse_state.y = my;
    if (mx != gfx_cursor_lx || my != gfx_cursor_ly) {
        gfx_cursor_lx = mx;
        gfx_cursor_ly = my;
        gfx_cursor_moved = (unsigned long)sys_ticks;
    }
    if (gfx_covers_screen() &&
        (unsigned long)sys_ticks - gfx_cursor_moved > GFX_CURSOR_IDLE_TICKS)
        return;
    cursor_place(mx, my);
}

/* ---- 8x8 CP437 font (ASCII 32-127) ---- */
static const uint8_t font8x8[96][8] = {
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    {0x18,0x18,0x18,0x18,0x18,0x00,0x18,0x00},
    {0x6C,0x6C,0x00,0x00,0x00,0x00,0x00,0x00},
    {0x6C,0x6C,0xFE,0x6C,0xFE,0x6C,0x6C,0x00},
    {0x18,0x3E,0x60,0x3C,0x06,0x7C,0x18,0x00},
    {0xC2,0xC6,0x0C,0x18,0x30,0x66,0xC6,0x00},
    {0x38,0x6C,0x38,0x76,0xDC,0xCC,0x76,0x00},
    {0x18,0x18,0x30,0x00,0x00,0x00,0x00,0x00},
    {0x0C,0x18,0x30,0x30,0x30,0x18,0x0C,0x00},
    {0x30,0x18,0x0C,0x0C,0x0C,0x18,0x30,0x00},
    {0x00,0x66,0x3C,0xFF,0x3C,0x66,0x00,0x00},
    {0x00,0x18,0x18,0x7E,0x18,0x18,0x00,0x00},
    {0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x30},
    {0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00},
    {0x02,0x06,0x0C,0x18,0x30,0x60,0x40,0x00},
    {0x7C,0xC6,0xCE,0xDE,0xF6,0xE6,0x7C,0x00},
    {0x18,0x38,0x78,0x18,0x18,0x18,0x7E,0x00},
    {0x7C,0xC6,0x06,0x1C,0x30,0x66,0xFE,0x00},
    {0x7C,0xC6,0x06,0x3C,0x06,0xC6,0x7C,0x00},
    {0x1C,0x3C,0x6C,0xCC,0xFE,0x0C,0x1E,0x00},
    {0xFE,0xC0,0xFC,0x06,0x06,0xC6,0x7C,0x00},
    {0x38,0x60,0xC0,0xFC,0xC6,0xC6,0x7C,0x00},
    {0xFE,0xC6,0x0C,0x18,0x30,0x30,0x30,0x00},
    {0x7C,0xC6,0xC6,0x7C,0xC6,0xC6,0x7C,0x00},
    {0x7C,0xC6,0xC6,0x7E,0x06,0x0C,0x78,0x00},
    {0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x00},
    {0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x30},
    {0x0C,0x18,0x30,0x60,0x30,0x18,0x0C,0x00},
    {0x00,0x00,0x7E,0x00,0x7E,0x00,0x00,0x00},
    {0x60,0x30,0x18,0x0C,0x18,0x30,0x60,0x00},
    {0x7C,0xC6,0x0C,0x18,0x18,0x00,0x18,0x00},
    {0x7C,0xC6,0xDE,0xDE,0xDE,0xC0,0x78,0x00},
    {0x38,0x6C,0xC6,0xC6,0xFE,0xC6,0xC6,0x00},
    {0xFC,0x66,0x66,0x7C,0x66,0x66,0xFC,0x00},
    {0x3C,0x66,0xC0,0xC0,0xC0,0x66,0x3C,0x00},
    {0xF8,0x6C,0x66,0x66,0x66,0x6C,0xF8,0x00},
    {0xFE,0x62,0x68,0x78,0x68,0x62,0xFE,0x00},
    {0xFE,0x62,0x68,0x78,0x68,0x60,0xF0,0x00},
    {0x3C,0x66,0xC0,0xC0,0xC6,0x66,0x3E,0x00},
    {0xC6,0xC6,0xC6,0xFE,0xC6,0xC6,0xC6,0x00},
    {0x3C,0x18,0x18,0x18,0x18,0x18,0x3C,0x00},
    {0x1E,0x0C,0x0C,0x0C,0xCC,0xCC,0x78,0x00},
    {0xE6,0x66,0x6C,0x78,0x6C,0x66,0xE6,0x00},
    {0xF0,0x60,0x60,0x60,0x62,0x66,0xFE,0x00},
    {0xC6,0xEE,0xFE,0xFE,0xD6,0xC6,0xC6,0x00},
    {0xC6,0xE6,0xF6,0xDE,0xCE,0xC6,0xC6,0x00},
    {0x7C,0xC6,0xC6,0xC6,0xC6,0xC6,0x7C,0x00},
    {0xFC,0x66,0x66,0x7C,0x60,0x60,0xF0,0x00},
    {0x7C,0xC6,0xC6,0xC6,0xD6,0xDE,0x7C,0x06},
    {0xFC,0x66,0x66,0x7C,0x6C,0x66,0xE6,0x00},
    {0x7C,0xC6,0xE0,0x7C,0x0E,0xC6,0x7C,0x00},
    {0x7E,0x7E,0x5A,0x18,0x18,0x18,0x3C,0x00},
    {0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x7C,0x00},
    {0xC6,0xC6,0xC6,0xC6,0x6C,0x38,0x10,0x00},
    {0xC6,0xC6,0xC6,0xD6,0xFE,0xEE,0xC6,0x00},
    {0xC6,0xC6,0x6C,0x38,0x6C,0xC6,0xC6,0x00},
    {0x66,0x66,0x66,0x3C,0x18,0x18,0x3C,0x00},
    {0xFE,0xC6,0x8C,0x18,0x32,0x66,0xFE,0x00},
    {0x3C,0x30,0x30,0x30,0x30,0x30,0x3C,0x00},
    {0xC0,0x60,0x30,0x18,0x0C,0x06,0x02,0x00},
    {0x3C,0x0C,0x0C,0x0C,0x0C,0x0C,0x3C,0x00},
    {0x10,0x38,0x6C,0xC6,0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF},
    {0x30,0x18,0x0C,0x00,0x00,0x00,0x00,0x00},
    {0x00,0x00,0x78,0x0C,0x7C,0xCC,0x76,0x00},
    {0xE0,0x60,0x7C,0x66,0x66,0x66,0xDC,0x00},
    {0x00,0x00,0x7C,0xC6,0xC0,0xC6,0x7C,0x00},
    {0x1C,0x0C,0x7C,0xCC,0xCC,0xCC,0x76,0x00},
    {0x00,0x00,0x7C,0xC6,0xFE,0xC0,0x7C,0x00},
    {0x1C,0x36,0x30,0x7C,0x30,0x30,0x78,0x00},
    {0x00,0x00,0x76,0xCC,0xCC,0x7C,0x0C,0x78},
    {0xE0,0x60,0x6C,0x76,0x66,0x66,0xE6,0x00},
    {0x18,0x00,0x38,0x18,0x18,0x18,0x3C,0x00},
    {0x06,0x00,0x06,0x06,0x06,0x66,0x66,0x3C},
    {0xE0,0x60,0x66,0x6C,0x78,0x6C,0xE6,0x00},
    {0x38,0x18,0x18,0x18,0x18,0x18,0x3C,0x00},
    {0x00,0x00,0xEC,0xFE,0xD6,0xD6,0xD6,0x00},
    {0x00,0x00,0xDC,0x66,0x66,0x66,0x66,0x00},
    {0x00,0x00,0x7C,0xC6,0xC6,0xC6,0x7C,0x00},
    {0x00,0x00,0xDC,0x66,0x66,0x7C,0x60,0xF0},
    {0x00,0x00,0x76,0xCC,0xCC,0x7C,0x0C,0x1E},
    {0x00,0x00,0xDC,0x76,0x60,0x60,0xF0,0x00},
    {0x00,0x00,0x7E,0xC0,0x7C,0x06,0xFC,0x00},
    {0x30,0x30,0x7C,0x30,0x30,0x36,0x1C,0x00},
    {0x00,0x00,0xCC,0xCC,0xCC,0xCC,0x76,0x00},
    {0x00,0x00,0xC6,0xC6,0xC6,0x6C,0x38,0x00},
    {0x00,0x00,0xC6,0xD6,0xD6,0xFE,0x6C,0x00},
    {0x00,0x00,0xC6,0x6C,0x38,0x6C,0xC6,0x00},
    {0x00,0x00,0xC6,0xC6,0xCE,0x76,0x06,0xFC},
    {0x00,0x00,0xFC,0x98,0x30,0x64,0xFC,0x00},
    {0x0E,0x18,0x18,0x70,0x18,0x18,0x0E,0x00},
    {0x18,0x18,0x18,0x00,0x18,0x18,0x18,0x00},
    {0x70,0x18,0x18,0x0E,0x18,0x18,0x70,0x00},
    {0x76,0xDC,0x00,0x00,0x00,0x00,0x00,0x00},
    {0x00,0x10,0x38,0x6C,0xC6,0xC6,0xFE,0x00}
};

/* Default non-fullscreen terminal window geometry. The shell runs in a
 * movable window: a title bar on top, a scrollbar on its right edge and text
 * below. The defaults are clamped to the framebuffer so the window always
 * fits (a small screen degrades to a near-fullscreen window). */
#define WIN_DEF_COLS  74
#define WIN_DEF_ROWS  28
#define WIN_DEF_X     4
#define WIN_DEF_Y     3

/* ---- Terminal state ---- */
int term_x = WIN_DEF_X, term_y = WIN_DEF_Y;
int term_cols, term_rows;
static int term_sz_cols = WIN_DEF_COLS;   /* persisted size across redraws */
static int term_sz_rows = WIN_DEF_ROWS;
static int term_fullscreen;
static int term_minimized;
static int term_px_x, term_px_y, term_px_w, term_px_h;

/* ---- Multi-window manager (Alt-Tab focus + Super-Tab tiling) ----
 *
 * Up to WM_MAX_TERMS terminal windows share one shell engine: the globals
 * above always mirror the FOCUSED window, so every terminal function below
 * keeps working untouched. tw_park/tw_unpark copy the whole window state
 * (geometry + logical ring + active line + cursor) between the globals and
 * the per-window slot. The second window's ring lives on the kernel heap
 * (64 KB: a static would blow the USER_LOAD_BASE .bss budget); window 0
 * keeps the historical static ring. Focus ids: 0/1 = terminals,
 * WM_FOCUS_GFX = a composited graphics window. The shell parks its input
 * line per window through shell_focus_park/restore (kernel.h), so each
 * terminal keeps its own half-typed command across Alt-Tab. History and
 * cwd stay shared; running a program blocks both windows (one exec
 * engine), documented in CLAUDE.md. While split, window 0 also snapshots
 * to the heap: its slot borrows the static ring, which IS the live one,
 * so sharing it would merge both windows' content and alias park's copy.
 * Close drops the snapshot and re-homes window 0 on the static ring. */
#define WM_MAX_TERMS 2
#define WM_ELINE_SZ 256
static void term_finish_layout(void);
static void term_recalc(void);
static int term_max_cols(void);
static int term_max_rows(void);
static void term_toggle_minimize(void);
static void term_toggle_fullscreen(void);
static void term_close_default(void);
static void gfx_transition(const wm_gfxview_rect_t *from, int from_titled);
static void gfx_drop_focus(int source);
typedef struct {
    int present;
    int valid;
    int x, y, sz_cols, sz_rows, cols, rows, px_x, px_y, px_w, px_h;
    int fullscreen, minimized;
    char (*lg)[SB_LINE_MAX];
    int head, tail, count;
    char act[SB_LINE_MAX];
    int act_len, disp_off, cursor_col, csi;
    char eline[WM_ELINE_SZ];
    int epos, has_line;
    int prompted;
} termwin_t;
static termwin_t twins[WM_MAX_TERMS];
static int wm_nterms = 1;
static int wm_focus;
static int wm_term;
static int wm_inited;
/** Docstring: Single focus event bus owned by the desktop. */
static wm_notify_bus_t wm_bus;
static int wm_bus_ready;

/** Docstring: Focus listener clearing a possibly stale cursor sprite. */
static void wm_focus_cursor_sync(const wm_notify_event_t *e)
{
    (void)e;
    cursor_invalidate();
}

/** Docstring: Emit one focus event when the id actually moved. */
static void wm_emit_focus_moved(int before, int source)
{
    wm_notify_event_t e;
    if (before == wm_focus) return;
    e.type = WM_NOTIFY_FOCUS;
    e.old_focus = before;
    e.new_focus = wm_focus;
    e.source = source;
    wm_notify_emit(&wm_bus, &e);
}

/** Docstring: Last focus event for serial-observable state. */
const wm_notify_event_t *vga_fb_focus_event(void)
{
    return wm_notify_last(&wm_bus);
}

/** Docstring: Record a programmatic focus move from another unit. */
void vga_fb_focus_report(int before, int source)
{
    wm_emit_focus_moved(before, source);
}
/** Docstring: Active layout mode plus last published plan for repaint skip. */
static int wm_layout_mode = WM_LAYOUT_TILE;
static wm_layout_cell_t wm_last_cells[WM_MAX_TERMS + 1];
static int wm_last_n = -1;

static void tw_park(int i) {
    termwin_t *t = &twins[i];
    int k;
    if (i < 0 || i >= WM_MAX_TERMS || !t->present) return;
    t->x = term_x; t->y = term_y;
    t->sz_cols = term_sz_cols; t->sz_rows = term_sz_rows;
    t->cols = term_cols; t->rows = term_rows;
    t->px_x = term_px_x; t->px_y = term_px_y;
    t->px_w = term_px_w; t->px_h = term_px_h;
    t->fullscreen = term_fullscreen; t->minimized = term_minimized;
    if (t->lg == lg) {
        /* Window 0 at home borrows the live ring itself: snapshot indices
         * only. A line copy here would alias src == dst and rotate the
         * ring once lg_head != 0, eating scrollback on every switch. */
        t->head = lg_head; t->tail = lg_tail; t->count = lg_count;
    } else {
        for (k = 0; k < lg_count && k < SB_MAX_LINES; k++) {
            const char *s = lg ? LG_LINE(lg_head + k) : "";
            int l;
            for (l = 0; l < SB_LINE_MAX - 1 && s[l]; l++) t->lg[k][l] = s[l];
            t->lg[k][l] = '\0';
        }
        t->head = 0; t->tail = lg_count % SB_MAX_LINES; t->count = lg_count;
    }
    for (k = 0; k <= act_len && k < SB_LINE_MAX; k++) t->act[k] = act[k];
    t->act_len = act_len;
    t->disp_off = disp_off; t->cursor_col = term_cursor_col; t->csi = csi_state;
    t->valid = 1;
}

static void tw_unpark(int i) {
    termwin_t *t = &twins[i];
    int k;
    if (i < 0 || i >= WM_MAX_TERMS || !t->present || !t->valid) return;
    term_x = t->x; term_y = t->y;
    term_sz_cols = t->sz_cols; term_sz_rows = t->sz_rows;
    term_cols = t->cols; term_rows = t->rows;
    term_px_x = t->px_x; term_px_y = t->px_y;
    term_px_w = t->px_w; term_px_h = t->px_h;
    term_fullscreen = t->fullscreen; term_minimized = t->minimized;
    if (t->lg == lg) {
        lg_head = t->head; lg_tail = t->tail; lg_count = t->count;
    } else if (lg) {
        lg_head = 0; lg_tail = 0; lg_count = 0;
        for (k = 0; k < t->count && k < SB_MAX_LINES; k++) {
            const char *s = t->lg[k];
            char *d = LG_LINE(k);
            int l;
            for (l = 0; l < SB_LINE_MAX - 1 && s[l]; l++) d[l] = s[l];
            d[l] = '\0';
            lg_tail = (lg_tail + 1) % SB_MAX_LINES;
            lg_count++;
        }
    } else {
        lg_head = 0; lg_tail = 0; lg_count = 0;
    }
    for (k = 0; k <= t->act_len && k < SB_LINE_MAX; k++) act[k] = t->act[k];
    act_len = t->act_len;
    disp_off = t->disp_off; term_cursor_col = t->cursor_col; csi_state = t->csi;
    /* The slot's derived fields (cols/rows/px) lag resizes: tile/snap write
     * x/y/sz only, so recompute from the restored size or a refocused
     * window paints with the previous layout's dimensions. */
    term_recalc();
}

static void wm_init_once(void) {
    int k;
    if (wm_inited) return;
    wm_inited = 1;
    wm_nterms = 1;
    wm_focus = 0;
    wm_term = 0;
    for (k = 0; k < WM_MAX_TERMS; k++) {
        twins[k].present = (k == 0);
        twins[k].valid = 0;
        twins[k].lg = 0;
        twins[k].has_line = 0;
        twins[k].eline[0] = '\0';
        twins[k].epos = 0;
        twins[k].prompted = 0;
    }
    twins[0].lg = lg;
    if (!wm_bus_ready) {
        wm_bus_ready = 1;
        wm_notify_reset(&wm_bus);
        wm_notify_subscribe(&wm_bus, wm_focus_cursor_sync);
    }
}

/** Docstring: Select window i and drop any in-flight drag grab. */
static void tw_select(int i) {
    if (i < 0 || i >= wm_nterms) return;
    if (!twins[i].present) return;
    if (shell_readline_active()) shell_focus_park();
    tw_park(wm_term);
    wm_focus = i;
    wm_term = i;
    tw_unpark(i);
    wm_drag_reset();
    if (shell_readline_active()) shell_focus_restore();
}

int vga_fb_focus_get(void) { return wm_focus; }
int vga_fb_nterms_get(void) { return wm_nterms; }

/** Docstring: Single snapshot of every window for focus decisions. */
static void wm_snapshot_state(wm_focus_state_t *st) {
    int i;
    wm_init_once();
    st->focus = wm_focus;
    st->nterms = wm_nterms;
    st->gfx_active = vga_fb_gfx_mode ? 1 : 0;
    for (i = 0; i < 4; i++)
        st->present[i] = 0;
    for (i = 0; i < wm_nterms && i < 4; i++)
        st->present[i] = twins[i].present ? 1 : 0;
}

/** Docstring: Cycle focus across terminals plus graphics when active. */
void vga_fb_focus_next(void) {
    wm_focus_state_t st;
    int i;
    int nx;
    int ntargets = 0;
    int before;
    wm_snapshot_state(&st);
    for (i = 0; i < st.nterms && i < 4; i++)
        if (st.present[i]) ntargets++;
    if (st.gfx_active) ntargets++;
    if (ntargets < 2) return;
    nx = wm_focus_next(&st);
    if (nx == wm_focus) return;
    if (!wm_focus_selectable(&st, nx)) return;
    before = wm_focus;
    if (nx == WM_FOCUS_GFX) {
        if (shell_readline_active()) shell_focus_park();
        tw_park(wm_term);
        wm_focus = WM_FOCUS_GFX;
        kbd_raw_flush();
        if (gfx_hidden) {
            gfx_hidden = 0;
            gfx_frame_dirty = 1;
        }
    } else {
        if ((user_program_active || shell_fg_active) && wm_focus == WM_FOCUS_GFX)
            serial_puts("wm: fg program owns input; use `run X &` so Alt-Tab splits input\n");
        /* Leaving a fullscreen app would hand the keyboard to a terminal
         * the app still covers: minimize it like any desktop does, and the
         * next Alt-Tab back restores it fullscreen. */
        if (wm_focus == WM_FOCUS_GFX && gfx_covers_screen())
            gfx_hidden = 1;
        tw_select(nx);
    }
    wm_emit_focus_moved(before, WM_FOCUS_SRC_KEYBOARD);
    vga_fb_draw_desktop();
}

/** Docstring: Route WM focus with the graphics mode switch.
 *
 * A program that enables the display owns the keyboard: without this,
 * a gfx child spawned from another gfx app (file -> vedit) keeps the
 * terminal focused, so its keys and wheel keep landing on the shell
 * while the app looks hung. The enable arm mirrors the focus-gfx path
 * (park shell line, flush stale raw bytes); the disable arm hands the
 * terminal back silently, never with the Alt-Tab nag. */
static void wm_gfx_focus_sync(int on) {
    int before = wm_focus;
    if (on) {
        if (wm_focus != WM_FOCUS_GFX) {
            if (shell_readline_active()) shell_focus_park();
            tw_park(wm_term);
            wm_focus = WM_FOCUS_GFX;
            kbd_raw_flush();
            wm_emit_focus_moved(before, WM_FOCUS_SRC_MODE);
        }
    } else {
        if (wm_focus == WM_FOCUS_GFX) {
            tw_select(wm_term);
            wm_emit_focus_moved(before, WM_FOCUS_SRC_MODE);
        }
    }
}

/** Docstring: Focus window id directly, fail closed on invalid id. */
int vga_fb_focus_id(int id) {
    wm_focus_state_t st;
    wm_snapshot_state(&st);
    if (wm_focus_set(&st, id) < 0) return -1;
    if (id == WM_FOCUS_GFX) {
        if (wm_focus == WM_FOCUS_GFX && !gfx_hidden) return 0;
        if (gfx_hidden) {
            gfx_hidden = 0;
            gfx_frame_dirty = 1;
        }
        if (wm_focus != WM_FOCUS_GFX) {
            if (shell_readline_active()) shell_focus_park();
            tw_park(wm_term);
            wm_focus = WM_FOCUS_GFX;
            kbd_raw_flush();
        }
        vga_fb_draw_desktop();
        return 0;
    }
    if (id == wm_focus) return 0;
    if ((user_program_active || shell_fg_active) && wm_focus == WM_FOCUS_GFX)
        serial_puts("wm: fg program owns input; use `run X &` so Alt-Tab splits input\n");
    if (wm_focus == WM_FOCUS_GFX && gfx_covers_screen())
        gfx_hidden = 1;
    tw_select(id);
    wm_term = id;
    vga_fb_draw_desktop();
    return 0;
}

/* Open the second terminal (heap ring, right half) or focus it when open.
 * Window 0 also takes a heap snapshot while split: its slot borrows the
 * static ring, which IS the live one, so without a private copy both
 * windows would share content (same prompt/output on both) and a park
 * would alias src == dst. Single-terminal boots keep the static ring. */
int vga_fb_term_split(void) {
    int i;
    unsigned int *fx_old = 0;
    char (*ring)[SB_LINE_MAX];
    char (*snap0)[SB_LINE_MAX];
    wm_init_once();
    if (wm_nterms >= WM_MAX_TERMS && twins[1].present) {
        tw_select(1);
        vga_fb_draw_desktop();
        return 0;
    }
    ring = (char (*)[SB_LINE_MAX])kmalloc(
        (unsigned long)SB_MAX_LINES * (unsigned long)SB_LINE_MAX);
    if (!ring) return -1;
    for (i = 0; i < SB_MAX_LINES; i++) ring[i][0] = '\0';
    if (twins[0].lg == lg) {
        snap0 = (char (*)[SB_LINE_MAX])kmalloc(
            (unsigned long)SB_MAX_LINES * (unsigned long)SB_LINE_MAX);
        if (!snap0) { kfree(ring); return -1; }
        for (i = 0; i < SB_MAX_LINES; i++) snap0[i][0] = '\0';
        twins[0].lg = snap0;
        twins[0].valid = 0;
    }
    tw_park(wm_term);
    twins[1].present = 1;
    twins[1].lg = ring;
    twins[1].head = twins[1].tail = twins[1].count = 0;
    twins[1].act[0] = '\0';
    twins[1].act_len = 0;
    twins[1].disp_off = 0;
    twins[1].cursor_col = -1;
    twins[1].csi = 0;
    twins[1].has_line = 0;
    twins[1].eline[0] = '\0';
    twins[1].epos = 0;
    twins[1].valid = 1;
    wm_nterms = WM_MAX_TERMS;
    tw_unpark(wm_term);
    fx_old = fx_start_full();
    vga_fb_tile_all();
    tw_select(1);
    vga_fb_draw_desktop();
    fx_finish_full(fx_old);
    return 0;
}

/* Close the second terminal (window 0 never closes: it resets like the
 * historical close button). Closes from any focus — `wm close` typed in
 * window 0 still means "drop the split", never a silent no-op. The live
 * ring is adopted as window 0's own (it may show the closing window), its
 * heap snapshot is dropped and the slot re-homes on the static ring, so
 * closing never eats the output printed since the last switch (that loss
 * is what left phantom duplicate prompts behind). */
int vga_fb_term_close_focused(void) {
    unsigned int *fx_old;
    wm_init_once();
    if (!twins[1].present) return 0;
    fx_old = fx_start_full();
    if (twins[0].lg && twins[0].lg != lg) kfree(twins[0].lg);
    twins[0].lg = lg;
    twins[0].head = lg_head; twins[0].tail = lg_tail; twins[0].count = lg_count;
    twins[0].valid = 1;
    if (wm_term == 1) wm_term = 0;
    if (wm_focus == 1) wm_focus = 0;
    if (twins[1].lg && twins[1].lg != lg) kfree(twins[1].lg);
    twins[1].lg = 0;
    twins[1].present = 0;
    twins[1].has_line = 0;
    twins[1].eline[0] = '\0';
    twins[1].epos = 0;
    twins[1].prompted = 0;
    wm_nterms = 1;
    vga_fb_reset_default();
    fx_finish_full(fx_old);
    return 1;
}

/** Docstring: Tile terminals through the tiling contract, graphics right. */
/** Docstring: Set active layout mode, fail closed on bad mode. */
int vga_fb_layout_set(int mode)
{
    if (!wm_layout_mode_valid(mode)) {
        return -1;
    }
    wm_layout_mode = mode;
    wm_last_n = -1;
    return 0;
}

/** Docstring: Cycle layout mode tile bsp cascade fibonacci. */
void vga_fb_layout_cycle(void)
{
    if (wm_layout_mode == WM_LAYOUT_TILE) {
        wm_layout_mode = WM_LAYOUT_BSP;
    } else if (wm_layout_mode == WM_LAYOUT_BSP) {
        wm_layout_mode = WM_LAYOUT_CASCADE;
    } else if (wm_layout_mode == WM_LAYOUT_CASCADE) {
        wm_layout_mode = WM_LAYOUT_FIBONACCI;
    } else {
        wm_layout_mode = WM_LAYOUT_TILE;
    }
    wm_last_n = -1;
    vga_fb_tile_all();
}

/** Docstring: Active layout mode id. */
int vga_fb_layout_get(void)
{
    return wm_layout_mode;
}

/** Docstring: Active layout mode name, never null. */
const char *vga_fb_layout_name(void)
{
    const char *n = wm_layout_mode_name(wm_layout_mode);
    return n ? n : "tile";
}

/** Docstring: Tile every window, graphics included, through the layout
 * contract. The graphics window is one more layout participant (placed
 * after the terminals, so the tile mode keeps it on the right like the
 * historical side-tile); its cell becomes the tiled view and the app is
 * scaled to fit it with the aspect kept. A fullscreen graphics window
 * drops back to its tile, and the fullscreen layout shows the focused
 * window alone (an unfocused graphics window minimizes to the taskbar,
 * exactly like the hidden terminals). The graphics move glides. */
void vga_fb_tile_all(void) {
    int mc, mr;
    int cur;
    wm_focus_state_t st;
    wm_layout_config_t lcfg = WM_LAYOUT_CONFIG_DEFAULT;
    wm_layout_window_t wins[WM_MAX_TERMS + 1];
    wm_layout_cell_t cells[WM_MAX_TERMS + 1];
    int slot_of[WM_MAX_TERMS + 1];
    int nwin = 0;
    int n;
    int i;
    int c;
    int with_gfx = vga_fb_gfx_mode && (!gfx_hidden || wm_layout_mode != WM_LAYOUT_FULLSCREEN);
    wm_gfxview_rect_t gfx_from = gfx_view.frame;
    int gfx_from_titled = gfx_view.title_h > 0;
    int gfx_had = vga_fb_gfx_mode && gfx_view_valid && !gfx_hidden;
    wm_snapshot_state(&st);
    cur = wm_term;
    tw_park(cur);
    mc = (fb_width - SCROLLBAR_W) / FONT_W;
    if (mc > TERM_MAX_COLS) mc = TERM_MAX_COLS;
    mr = (fb_height - 2 * FONT_H) / FONT_H;
    if (mr > TERM_MAX_ROWS) mr = TERM_MAX_ROWS;
    for (i = 0; i < wm_nterms && i < WM_MAX_TERMS; i++) {
        wins[nwin].kind = 1;
        wins[nwin].id = i;
        wins[nwin].present = st.present[i];
        wins[nwin].min_cols = 1;
        wins[nwin].min_rows = 1;
        slot_of[nwin] = i;
        nwin++;
    }
    if (with_gfx) {
        wins[nwin].kind = 2;
        wins[nwin].id = WM_FOCUS_GFX;
        wins[nwin].present = 1;
        wins[nwin].min_cols = 1;
        wins[nwin].min_rows = 1;
        slot_of[nwin] = WM_FOCUS_GFX;
        nwin++;
    }
    n = wm_layout_compute(&lcfg, wins, nwin, wm_layout_mode, wm_focus, mc, mr,
                          cells, WM_MAX_TERMS + 1);
    if (n <= 0) {
        tw_unpark(cur);
        term_finish_layout();
        return;
    }
    /* A window of c columns paints c cells of content plus a
     * SCROLLBAR_W-wide scrollbar (or letterbox strip) on its right, one
     * more grid column than the layout reserved, so a cell with a
     * neighbour to its right gives that column back instead of painting
     * under the neighbour's first column (the 8 px overlap every split
     * used to show). The rightmost cell keeps it: the grid already
     * leaves exactly one scrollbar of room at the screen edge. */
    for (i = 0; i < n; i++) {
        int sb_cols = (SCROLLBAR_W + FONT_W - 1) / FONT_W;
        if (cells[i].cols > sb_cols && cells[i].x + cells[i].cols < mc)
            cells[i].cols -= sb_cols;
    }
    if (!with_gfx && (wm_nterms < 2 || !twins[1].present)) {
        twins[0].fullscreen = 1;
        twins[0].minimized = 0;
        wm_last_n = -1;
        tw_unpark(cur);
        term_finish_layout();
        return;
    }
    if (wm_last_n == n && wm_layout_same(wm_last_cells, cells, n) &&
        (!with_gfx || (gfx_view_mode == WM_GFXVIEW_TILED && !gfx_hidden))) {
        tw_unpark(cur);
        return;
    }
    c = 0;
    for (i = 0; i < nwin && c < n; i++) {
        int id;
        if (!wins[i].present) continue;
        id = slot_of[i];
        if (id == WM_FOCUS_GFX) {
            if (cells[c].cols <= 0 || cells[c].rows <= 0) {
                gfx_hidden = 1;
                if (wm_focus == WM_FOCUS_GFX) gfx_drop_focus(WM_FOCUS_SRC_MODE);
            } else {
                gfx_cell.x = cells[c].x * FONT_W;
                gfx_cell.y = cells[c].y * FONT_H;
                gfx_cell.w = cells[c].cols * FONT_W + SCROLLBAR_W;
                gfx_cell.h = (cells[c].rows + 1) * FONT_H;
                gfx_hidden = 0;
                gfx_view_mode = WM_GFXVIEW_TILED;
                gfx_view_back = WM_GFXVIEW_TILED;
                gfx_win_ox = 0;
                gfx_win_oy = 0;
                gfx_frame_dirty = 1;
            }
        } else if (id >= 0 && id < WM_MAX_TERMS) {
            twins[id].fullscreen = cells[c].fullscreen;
            twins[id].minimized = 0;
            twins[id].sz_cols = cells[c].cols;
            twins[id].sz_rows = cells[c].rows;
            twins[id].x = cells[c].x;
            twins[id].y = cells[c].y;
        }
        wm_last_cells[c] = cells[c];
        c++;
    }
    wm_last_n = n;
    tw_unpark(cur);
    term_recalc();
    disp_off = 0;
    if (with_gfx && !gfx_hidden)
        gfx_transition(gfx_had ? &gfx_from : 0, gfx_from_titled);
    else
        vga_fb_draw_desktop();
}

/* Serial-observable window list for `wm list` (BDD surface). Parked state
 * is read from the slots, never by disturbing the live globals: the
 * focused window's live values sit in the globals, the rest in twins.
 * A parked slot's derived cols/rows lag resizes (tile/snap write x/y/sz
 * only), so they are derived from the authoritative size here; the live
 * window reports its globals. Dock columns ride along so a headless
 * driver can click exact icon coordinates instead of guessing. */
static int dock_cell_w;
static int shortcut_cell_left(int i);
static void shortcuts_layout(void);
void vga_fb_list_windows(void) {
    int i;
    int cur = wm_term;
    char b[128];
    wm_init_once();
    tw_park(cur);
    for (i = 0; i < wm_nterms; i++) {
        termwin_t *t;
        int dc, dr;
        if (!twins[i].present) continue;
        t = &twins[i];
        if (i == cur) {
            dc = term_cols; dr = term_rows;
        } else if (t->fullscreen) {
            dc = term_max_cols(); dr = term_max_rows();
        } else {
            dc = t->sz_cols; dr = t->sz_rows;
            if (dc > term_max_cols()) dc = term_max_cols();
            if (dr > term_max_rows()) dr = term_max_rows();
        }
        ksprintf(b, "win term%d %c cols=%d rows=%d x=%d y=%d min=%d fs=%d%s\n",
                 i, (i == wm_focus) ? '*' : ' ',
                 dc, dr, (i == cur) ? term_x : t->x, (i == cur) ? term_y : t->y,
                 t->minimized, t->fullscreen,
                 t->has_line ? " line" : "");
        serial_puts(b);
    }
    tw_unpark(cur);
    {
        int j;
        desktop_shortcuts_load();
        shortcuts_layout();
        for (j = 0; j < shortcut_count; j++) {
            ksprintf(b, "win dock%d x=%d y=%d w=%d h=%d %s\n",
                     j, shortcut_cell_left(j), shortcuts[j].y,
                     dock_cell_w, ICON_H + ICON_LABEL_H, shortcuts[j].cmd);
            serial_puts(b);
        }
    }
    if (vga_fb_gfx_mode) {
        const char *vn = gfx_hidden ? "minimized" : wm_gfxview_mode_name(gfx_view_mode);
        ksprintf(b, "win gfx %c %s x=%d y=%d w=%d h=%d view=%s cx=%d cy=%d cw=%d ch=%d\n",
                 (wm_focus == WM_FOCUS_GFX) ? '*' : ' ',
                 gfx_win_title, gfx_win_x, gfx_win_y, gfx_win_w, gfx_win_h,
                 vn ? vn : "floating",
                 gfx_view_valid ? gfx_view.content.x : gfx_win_x,
                 gfx_view_valid ? gfx_view.content.y : gfx_win_y,
                 gfx_view_valid ? gfx_view.content.w : 0,
                 gfx_view_valid ? gfx_view.content.h : 0);
        serial_puts(b);
        taskbar_layout();
        ksprintf(b, "win gfxbtn x=%d w=%d %s\n",
                 tb_gfx_x, tb_gfx_w, gfx_task_icon() ? "icon" : "text");
        serial_puts(b);
    }
}

/* 1 when the focused window's active line is empty (fresh prompt spot). */
int vga_fb_act_empty(void) { return act_len == 0; }

/* The shell loop calls note after printing a prompt (it is live in the
 * focused window) and clear once the line is submitted for execution. */
void vga_fb_note_prompt(void) {
    wm_init_once();
    if (wm_focus >= 0 && wm_focus < WM_MAX_TERMS)
        twins[wm_focus].prompted = 1;
}
void vga_fb_clear_prompt(void) {
    wm_init_once();
    if (wm_focus >= 0 && wm_focus < WM_MAX_TERMS)
        twins[wm_focus].prompted = 0;
}
int vga_fb_prompted(void) {
    wm_init_once();
    if (wm_focus < 0 || wm_focus >= WM_MAX_TERMS) return 0;
    return twins[wm_focus].prompted;
}

/* 1 when the active line is empty or holds exactly a fresh prompt, so
 * printing another one would stack duplicate `miniOS> ` lines on every
 * refocus. Compares the whole line, not a prefix. */
int vga_fb_prompt_live(void) {
    if (act_len == 0) return 1;
    if (kstrcmp(act, "miniOS> ") == 0) return 1;
    return 0;
}

/* Park the shell's half-typed line into the focused window slot. */
void vga_fb_park_line(const char *b, int p) {
    termwin_t *t;
    int k;
    wm_init_once();
    if (wm_focus < 0 || wm_focus >= WM_MAX_TERMS) return;
    t = &twins[wm_focus];
    for (k = 0; k < WM_ELINE_SZ - 1 && b[k]; k++) t->eline[k] = b[k];
    t->eline[k] = '\0';
    t->epos = p;
    /* A fresh prompt parks empty: record no line, so `wm list` does not
     * claim a half-typed command that never existed. */
    t->has_line = (b[0] != '\0' || p > 0) ? 1 : 0;
}

/* Restore the focused window's parked line. Returns 1 when one existed. */
int vga_fb_unpark_line(char *b, int *p) {
    termwin_t *t;
    int k;
    wm_init_once();
    if (wm_focus < 0 || wm_focus >= WM_MAX_TERMS) return 0;
    t = &twins[wm_focus];
    if (!t->has_line) return 0;
    for (k = 0; k < WM_ELINE_SZ - 1 && t->eline[k]; k++) b[k] = t->eline[k];
    b[k] = '\0';
    *p = t->epos;
    return 1;
}

/* Hit-test: is (mx,my) inside terminal i's rectangle (title + content)? */
/** Docstring: True when point hits terminal window i including decorations. */
static int tw_hit(int i, int mx, int my) {
    termwin_t *t = &twins[i];
    wm_window_t w;
    if (i < 0 || i >= WM_MAX_TERMS) return 0;
    w.kind = WM_WIN_TERMINAL;
    w.id = i;
    w.x = t->px_x;
    w.y = t->px_y;
    w.w = t->px_w + SCROLLBAR_W;
    w.h = t->px_h + FONT_H;
    w.present = t->present;
    w.minimized = t->minimized;
    return wm_window_contains(&w, mx, my);
}

/** Docstring: True when point hits the visible graphics window, chrome
 * and letterbox included (the whole frame belongs to the app). */
static int gfx_hit(int mx, int my) {
    wm_window_t w;
    if (!vga_fb_gfx_mode || gfx_hidden || !gfx_view_valid) {
        return 0;
    }
    w.kind = WM_WIN_GRAPHICS;
    w.id = WM_FOCUS_GFX;
    w.x = gfx_view.frame.x;
    w.y = gfx_view.frame.y;
    w.w = gfx_view.frame.w;
    w.h = gfx_view.frame.h;
    w.present = 1;
    w.minimized = 0;
    return wm_window_contains(&w, mx, my);
}

/* Close request for a graphics window. A ring-3 program owns the display and
 * only the kernel can end it: the WM's close button sets this flag and the
 * syscall dispatcher acts on it at the program's next syscall, so the exit
 * runs on the child's own stack, never from the ISR. */
static volatile int wm_close_request;

/* There is no pre-wrapped screen buffer: the visible window is reconstructed
 * from the logical line history on every render (see term_render), so a resize
 * re-wraps the content instead of clipping it. */

#define FB_OFFSET(x,y) ((unsigned)(y) * fb_pitch + (unsigned)(x))

/* The text area starts one FONT_H below the window's top-left corner, which
 * is occupied by the title bar. */
static int term_content_y(void) { return term_px_y + FONT_H; }

/* ---- Palette ---- */
/* Icon palette (16 colours at VGA DAC indices 240-255). File scope so the
 * DAC programming below and the runtime PNG-to-palette mapper share one
 * table instead of drifting apart. */
static const uint8_t icon_pal[][3] = {
    {  0,  0,  0},   /* 0  transparent/black   */
    { 70,130,180},   /* 1  steel blue           */
    {220, 80, 60},   /* 2  tomato               */
    { 60,179,113},   /* 3  sea green            */
    {255,255,255},   /* 4  white                */
    { 40, 40, 50},   /* 5  dark bg              */
    {100,100,110},   /* 6  gray                 */
    {180,180,190},   /* 7  light gray           */
    {255,215,  0},   /* 8  gold                 */
    {  0,160,  0},   /* 9  green                */
    {147,112,219},   /* A  medium purple        */
    {255,165,  0},   /* B  orange               */
    {100,149,237},   /* C  cornflower           */
    { 15, 15, 50},   /* D  navy (desktop bg)    */
    { 60, 90,140},   /* E  title blue           */
    {  0,220,  0},   /* F  terminal green       */
};

/* Wallpaper colour cube: 6 levels per channel (websafe) at DAC 16-231.
 * The desktop UI owns 0-14 and the icons 240-255; the 216 cube slots give
 * a photographic wallpaper without touching either range. In true color the
 * cached wallpaper indices resolve through the same cube levels to full RGB
 * instead of the quantized DAC entries. */
static const uint8_t wall_levels[6] = { 0, 51, 102, 153, 204, 255 };

/* Desktop palette (DAC indices 0-14). File scope so the DAC programming, the
 * true-color packer and the icon mapper share one table. */
static const uint8_t desk_pal[][3] = {
    {  0,  0,  0},  /*  0 black        */
    { 15, 15, 50},  /*  1 bg (dark navy)*/
    {100,100,110},  /*  2 taskbar       */
    {255,255,255},  /*  3 taskbar text  */
    { 60, 90,140},  /*  4 title bar     */
    {255,255,255},  /*  5 title text    */
    { 15, 15, 15},  /*  6 terminal bg   */
    {  0,220,  0},  /*  7 terminal text */
    {  0,160,  0},  /*  8 cursor        */
    {180,180,190},  /*  9 border        */
    {255,255,255},  /* 10 white         */
    { 30, 30, 40},  /* 11 shadow        */
    {100,140,220},  /* 12 highlight     */
    { 60, 60, 70},  /* 13 scrollbar bg  */
    {140,140,155},  /* 14 scrollbar thumb */
};

/* Graphics program palette (768 bytes, set through SYS_PALETTE). In 8-bit
 * mode it owns the whole DAC; in true color it is only the lookup table the
 * DOOM/Nuklear blits expand their indexed back-buffers through, so a game
 * can no longer recolor the desktop behind its window. A gray ramp until the
 * first program sets it, never uninitialized pixels. */
static unsigned char gfx_pal[768];

void vga_fb_set_gfx_palette(const unsigned char *pal) {
    int i;
    for (i = 0; i < 768; i++) gfx_pal[i] = pal[i];
    if (fb_bpp != 8) return;
    outb(0x3C8, 0);
    for (i = 0; i < 768; i++) outb(0x3C9, pal[i] >> 2);
}

/* ---- True-color pixel layer ----
 * VBE true-color framebuffers store pixels natively as B,G,R(,X) bytes, so
 * the DAC is bypassed entirely. Every index the desktop draws with resolves
 * here: UI 0-14 through desk_pal, wallpaper 16-231 through the websafe cube,
 * icons 240-255 through icon_pal. Indices with no owner (15, 232-239) are
 * black. Graphics back-buffers never pass through this table; they expand
 * through gfx_pal at blit time. */
static unsigned long fb_pack_idx(unsigned idx) {
    unsigned r, g, b;
    if (idx < 15) {
        r = desk_pal[idx][0]; g = desk_pal[idx][1]; b = desk_pal[idx][2];
    } else if (idx >= WALL_PAL_BASE && idx < WALL_PAL_BASE + WALL_PAL_SIZE) {
        unsigned c = idx - WALL_PAL_BASE;
        r = wall_levels[c / 36]; g = wall_levels[(c / 6) % 6]; b = wall_levels[c % 6];
    } else if (idx >= ICON_PAL_BASE && idx < ICON_PAL_BASE + ICON_PAL_SIZE) {
        unsigned c = idx - ICON_PAL_BASE;
        r = icon_pal[c][0]; g = icon_pal[c][1]; b = icon_pal[c][2];
    } else {
        r = 0; g = 0; b = 0;
    }
    return (r << 16) | (g << 8) | b;
}

void fb_write_packed(int x, int y, unsigned long rgb) {
    volatile uint8_t *p;
    if (x < 0 || x >= fb_width || y < 0 || y >= fb_height) return;
    p = FBT + (unsigned)y * (unsigned)fb_pitch;
    if (fb_bpp == 32) {
        p += (unsigned)x * 4;
        p[0] = (uint8_t)(rgb & 0xFF);
        p[1] = (uint8_t)((rgb >> 8) & 0xFF);
        p[2] = (uint8_t)((rgb >> 16) & 0xFF);
        p[3] = 0;
    } else if (fb_bpp == 24) {
        p += (unsigned)x * 3;
        p[0] = (uint8_t)(rgb & 0xFF);
        p[1] = (uint8_t)((rgb >> 8) & 0xFF);
        p[2] = (uint8_t)((rgb >> 16) & 0xFF);
    } else {
        p[x] = (uint8_t)(rgb & 0xFF);
    }
}

unsigned long fb_read_packed(int x, int y) {
    volatile uint8_t *p;
    if (x < 0 || x >= fb_width || y < 0 || y >= fb_height) return 0;
    p = FBT + (unsigned)y * (unsigned)fb_pitch;
    if (fb_bpp == 32) {
        p += (unsigned)x * 4;
        return (unsigned long)p[0]
             | ((unsigned long)p[1] << 8)
             | ((unsigned long)p[2] << 16);
    }
    if (fb_bpp == 24) {
        p += (unsigned)x * 3;
        return (unsigned long)p[0]
             | ((unsigned long)p[1] << 8)
             | ((unsigned long)p[2] << 16);
    }
    /* 8-bit: return the raw palette index, not its resolved RGB. The cursor
     * save/restore round-trips through fb_write_packed, which in 8-bit writes
     * the low byte straight back into the framebuffer; resolving to RGB here
     * (and thus restoring only the blue channel as an index) is what smeared
     * the pointer into a trail. */
    return p[x];
}

unsigned long vga_fb_read_rgb(int x, int y) { return fb_read_packed(x, y); }

/** Docstring: Write n packed pixels (0x00RRGGBB, or raw indices in 8-bit
 * mode) to row y from column x, clipped once. The row fast path the
 * melt and the snapshot restore use instead of one call per pixel. */
void fb_write_row_packed(int x, int y, const unsigned int *src, int n) {
    volatile uint8_t *p;
    int i;
    int x0 = 0;
    if (!src || y < 0 || y >= fb_height || n <= 0) return;
    if (x < 0) { x0 = -x; }
    if (x + n > fb_width) n = fb_width - x;
    if (x0 >= n) return;
    p = FBT + (unsigned)y * (unsigned)fb_pitch;
    if (fb_bpp == 32) {
        volatile unsigned int *q = (volatile unsigned int *)(p + (unsigned)(x + x0) * 4u);
        for (i = x0; i < n; i++)
            *q++ = src[i] & 0x00FFFFFFu;
    } else if (fb_bpp == 24) {
        volatile uint8_t *q = p + (unsigned)(x + x0) * 3u;
        for (i = x0; i < n; i++) {
            q[0] = (uint8_t)(src[i] & 0xFF);
            q[1] = (uint8_t)((src[i] >> 8) & 0xFF);
            q[2] = (uint8_t)((src[i] >> 16) & 0xFF);
            q += 3;
        }
    } else {
        volatile uint8_t *q = p + (unsigned)(x + x0);
        for (i = x0; i < n; i++)
            *q++ = (uint8_t)(src[i] & 0xFF);
    }
}

/** Docstring: Read n packed pixels of row y from column x into dst,
 * clipped once; pixels outside the screen read as 0. */
void fb_read_row_packed(int x, int y, unsigned int *dst, int n) {
    volatile uint8_t *p;
    int i;
    if (!dst || n <= 0) return;
    for (i = 0; i < n; i++) dst[i] = 0;
    if (y < 0 || y >= fb_height) return;
    p = FBT + (unsigned)y * (unsigned)fb_pitch;
    for (i = 0; i < n; i++) {
        int xx = x + i;
        if (xx < 0 || xx >= fb_width) continue;
        if (fb_bpp == 32) {
            dst[i] = *(volatile unsigned int *)(p + (unsigned)xx * 4u) & 0x00FFFFFFu;
        } else if (fb_bpp == 24) {
            const volatile uint8_t *q = p + (unsigned)xx * 3u;
            dst[i] = (unsigned int)q[0] | ((unsigned int)q[1] << 8) | ((unsigned int)q[2] << 16);
        } else {
            dst[i] = p[xx];
        }
    }
}

/** Docstring: Fill a clipped horizontal run with one packed pixel. */
static void fb_fill_run(int x, int y, int n, unsigned long px) {
    volatile uint8_t *p;
    int i;
    if (y < 0 || y >= fb_height || n <= 0) return;
    if (x < 0) { n += x; x = 0; }
    if (x + n > fb_width) n = fb_width - x;
    if (n <= 0) return;
    p = FBT + (unsigned)y * (unsigned)fb_pitch;
    if (fb_bpp == 32) {
        fb_fill_u32(p + (unsigned)x * 4u, (unsigned int)(px & 0x00FFFFFFu), (unsigned long)n);
    } else if (fb_bpp == 24) {
        volatile uint8_t *q = p + (unsigned)x * 3u;
        for (i = 0; i < n; i++) {
            q[0] = (uint8_t)(px & 0xFF);
            q[1] = (uint8_t)((px >> 8) & 0xFF);
            q[2] = (uint8_t)((px >> 16) & 0xFF);
            q += 3;
        }
    } else {
        volatile uint8_t *q = p + (unsigned)x;
        for (i = 0; i < n; i++)
            q[i] = (uint8_t)(px & 0xFF);
    }
}

/* Nearest cube level for one 0-255 channel (boundaries at 25/76/127/178/229). */
static int wall_level(int v) {
    if (v <= 25) return 0;
    if (v <= 76) return 1;
    if (v <= 127) return 2;
    if (v <= 178) return 3;
    if (v <= 229) return 4;
    return 5;
}

static void vga_fb_set_palette(void) {
    int i;
    if (fb_bpp != 8) return;
    outb(0x3C8, 0);
    for (i = 0; i < 15; i++) {
        outb(0x3C9, desk_pal[i][0] >> 2);
        outb(0x3C9, desk_pal[i][1] >> 2);
        outb(0x3C9, desk_pal[i][2] >> 2);
    }
    /* Icon palette: 16 colours at VGA DAC indices 240-255. */
    {
        int i;
        outb(0x3C8, ICON_PAL_BASE);
        for (i = 0; i < ICON_PAL_SIZE; i++) {
            outb(0x3C9, icon_pal[i][0] >> 2);
            outb(0x3C9, icon_pal[i][1] >> 2);
            outb(0x3C9, icon_pal[i][2] >> 2);
        }
    }
    /* Wallpaper cube: 216 websafe colours at DAC 16-231. */
    {
        int r, g, b;
        outb(0x3C8, WALL_PAL_BASE);
        for (r = 0; r < 6; r++)
            for (g = 0; g < 6; g++)
                for (b = 0; b < 6; b++) {
                    outb(0x3C9, wall_levels[r] >> 2);
                    outb(0x3C9, wall_levels[g] >> 2);
                    outb(0x3C9, wall_levels[b] >> 2);
                }
    }
}

/* ---- Latin-1 Spanish glyphs (8x8, same style as font8x8) ----
 * The ES keyboard layout emits these single-byte Latin-1 codes; without
 * glyphs they would render as blanks. Approximations of the base letter
 * with the Spanish diacritic, recognizable at 8x8. */
static const uint8_t glyph_inv_excl[8] = {0x18,0x00,0x18,0x18,0x18,0x18,0x18,0x00};
static const uint8_t glyph_diaeresis[8]= {0x66,0x66,0x00,0x00,0x00,0x00,0x00,0x00};
static const uint8_t glyph_ord_fem[8]  = {0x78,0x0C,0x7C,0xCC,0x7C,0x00,0x00,0x00};
static const uint8_t glyph_notsign[8]  = {0x7C,0x04,0x04,0x04,0x00,0x00,0x00,0x00};static const uint8_t glyph_acute[8]    = {0x0C,0x0C,0x18,0x00,0x00,0x00,0x00,0x00};
static const uint8_t glyph_middot[8]   = {0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00};
static const uint8_t glyph_ord_masc[8] = {0x38,0x44,0x44,0x38,0x00,0x00,0x00,0x00};
static const uint8_t glyph_inv_quest[8]= {0x00,0x18,0x00,0x18,0x18,0x30,0x66,0x3C};
static const uint8_t glyph_Ccedil[8]   = {0x3C,0x66,0xC0,0xC0,0xC0,0x66,0x3C,0x30};
static const uint8_t glyph_Ntilde[8]   = {0x76,0xDC,0xE6,0xF6,0xDE,0xCE,0xC6,0x00};
static const uint8_t glyph_ccedil[8]   = {0x00,0x00,0x7C,0xC6,0xC0,0xC6,0x7C,0x30};
static const uint8_t glyph_ntilde[8]   = {0x76,0xDC,0xDC,0x66,0x66,0x66,0x66,0x00};

/* Resolve one byte to its 8-row glyph: ASCII through font8x8, Spanish
 * Latin-1 through the table above, anything else (including control codes)
 * as a blank. Takes an unsigned value so Latin-1 bytes above 127 survive a
 * signed-char parameter. */
static const uint8_t *fb_glyph(unsigned char c) {
    if (c < 32) return font8x8[0];
    if (c <= 127) return font8x8[c - 32];
    switch (c) {
    case 0xA1: return glyph_inv_excl;
    case 0xA8: return glyph_diaeresis;
    case 0xAA: return glyph_ord_fem;
    case 0xAC: return glyph_notsign;
    case 0xB4: return glyph_acute;
    case 0xB7: return glyph_middot;
    case 0xBA: return glyph_ord_masc;
    case 0xBF: return glyph_inv_quest;
    case 0xC7: return glyph_Ccedil;
    case 0xD1: return glyph_Ntilde;
    case 0xE7: return glyph_ccedil;
    case 0xF1: return glyph_ntilde;
    default: return font8x8[0];
    }
}

/* ---- Drawing primitives ---- */
void vga_fb_pixel(int x, int y, uint8_t color) {
    if (fb_bpp == 8) {
        if (x >= 0 && x < fb_width && y >= 0 && y < fb_height)
            FBT[(unsigned)y * (unsigned)fb_pitch + (unsigned)x] = color;
        return;
    }
    fb_write_packed(x, y, fb_pack_idx(color));
}

/** Docstring: Clear the render target to black in bulk. */
void vga_fb_clear(void) {
    unsigned long n = fb_frame_bytes();
    if ((n & 3UL) == 0)
        fb_fill_u32(FBT, 0u, n / 4UL);
    else
        kmemset((void *)FBT, 0, n);
}

/** Docstring: Solid rectangle: the color resolves once, every row is one
 * clipped run fill instead of a per-pixel palette lookup and call. */
void vga_fb_rect(int x, int y, int w, int h, uint8_t color) {
    int j;
    unsigned long px;
    if (w <= 0 || h <= 0) return;
    px = (fb_bpp == 8) ? (unsigned long)color : fb_pack_idx(color);
    if (y < 0) { h += y; y = 0; }
    if (y + h > fb_height) h = fb_height - y;
    for (j = 0; j < h; j++)
        fb_fill_run(x, y + j, w, px);
}

/* Direct RGB pixel: full color depth in true-color modes, best-effort
 * quantization in 8-bit mode. This is the primitive future UI (gradients,
 * hover glows, selection blends) builds on instead of the 15-entry UI
 * palette. Packed order 0x00RRGGBB, same as fb_write_packed. */
void vga_fb_pixel_rgb(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
    if (fb_bpp == 8) {
        vga_fb_pixel(x, y, (uint8_t)(WALL_PAL_BASE +
                     (wall_level(r) * 6 + wall_level(g)) * 6 + wall_level(b)));
        return;
    }
    fb_write_packed(x, y, ((unsigned long)r << 16) | ((unsigned long)g << 8) | (unsigned long)b);
}

void vga_fb_rect_rgb(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b) {
    int i, j;
    for (j = y; j < y + h; j++)
        for (i = x; i < x + w; i++)
            vga_fb_pixel_rgb(i, j, r, g, b);
}

void vga_fb_char(int col, int row, char c, uint8_t fg, uint8_t bg) {
    int px, py, i, j;
    uint8_t bits;
    const uint8_t *glyph;
    glyph = fb_glyph((unsigned char)c);
    px = term_px_x + col * FONT_W;
    py = term_content_y() + row * FONT_H;
    for (j = 0; j < FONT_H; j++) {
        bits = glyph[j];
        for (i = 0; i < FONT_W; i++)
            vga_fb_pixel(px + i, py + j, (bits & (0x80 >> i)) ? fg : bg);
    }
}

void vga_fb_str(int col, int row, const char *s, uint8_t fg, uint8_t bg) {
    int i = 0;
    while (s[i] && col + i < term_cols) {
        vga_fb_char(col + i, row, s[i], fg, bg);
        i++;
    }
}

/* Blit a text string at an absolute pixel position. Used for window chrome
 * (title bar, taskbar) which lives outside the content-relative coordinate
 * space that vga_fb_char/str operate in. */
static void text_px(int px, int py, const char *s, uint8_t fg, uint8_t bg) {
    int k, i, j;
    uint8_t bits;
    const uint8_t *glyph;
    for (k = 0; s[k]; k++) {
        unsigned char c = (unsigned char)s[k];
        glyph = fb_glyph(c);
        for (j = 0; j < FONT_H; j++) {
            bits = glyph[j];
            for (i = 0; i < FONT_W; i++)
                vga_fb_pixel(px + k * FONT_W + i, py + j,
                             (bits & (0x80 >> i)) ? fg : bg);
        }
    }
}

/* ---- Window controls ----
 * Three glyph buttons at the right end of a window's title bar: minimize (_),
 * maximize (square) and close (X). They are shared by the terminal window and
 * the composited graphics windows (DOOM/Nuklear), so hit-testing must work on
 * any titled window. Each button is FONT_W x FONT_H, separated by WM_BTN_PAD. */
static int wm_buttons_x0(int win_x, int win_w) {
    return win_x + win_w - 3 * (WM_BTN_W + WM_BTN_PAD);
}

/* Draw the three window-control glyphs at (px,py), the title bar's top-left. */
static void wm_draw_buttons(int px, int py, int win_w, uint8_t fg, uint8_t bg) {
    int bx = wm_buttons_x0(px, win_w);
    int by = py;
    int i;
    vga_fb_rect(bx, by, 3 * WM_BTN_W + 2 * WM_BTN_PAD, WM_BTN_H, bg);
    /* minimize: a short bar across the lower half. */
    vga_fb_rect(bx + 1, by + WM_BTN_H - 3, WM_BTN_W - 2, 1, fg);
    bx += WM_BTN_W + WM_BTN_PAD;
    /* maximize: an open square outline. */
    for (i = 1; i < WM_BTN_W - 1; i++) {
        vga_fb_pixel(bx + i, by + 1, fg);
        vga_fb_pixel(bx + i, by + WM_BTN_H - 2, fg);
    }
    for (i = 1; i < WM_BTN_H - 1; i++) {
        vga_fb_pixel(bx + 1, by + i, fg);
        vga_fb_pixel(bx + WM_BTN_W - 2, by + i, fg);
    }
    bx += WM_BTN_W + WM_BTN_PAD;
    /* close: two crossing diagonals. */
    for (i = 1; i < WM_BTN_W - 1; i++) {
        vga_fb_pixel(bx + i, by + i, fg);
        vga_fb_pixel(bx + WM_BTN_W - 1 - i, by + i, fg);
    }
}

/* Return which window-control button is under (mx,my), or 0 for none. */
static int wm_buttons_hit(int mx, int my, int win_x, int win_y, int win_w) {
    int x0 = wm_buttons_x0(win_x, win_w);
    int rel;
    if (my < win_y || my >= win_y + WM_BTN_H) return 0;
    if (mx < x0 || mx >= win_x + win_w) return 0;
    rel = mx - x0;
    if (rel < WM_BTN_W) return WM_BTN_MIN;
    if (rel < WM_BTN_W + WM_BTN_PAD + WM_BTN_W) return WM_BTN_MAX;
    if (rel < WM_BTN_W + WM_BTN_PAD + WM_BTN_W + WM_BTN_PAD + WM_BTN_W)
        return WM_BTN_CLOSE;
    return 0;
}

/* Close request bridge: the syscall dispatcher polls this so a graphics
 * program's next syscall exits it on the child's own stack. */
int wm_close_pending(void) { return wm_close_request; }
void wm_clear_close(void) { wm_close_request = 0; }
int wm_gfx_mode_active(void) { return vga_fb_gfx_mode; }

/** Docstring: PS/2 owner check with pid range validation, focus routed. */
int vga_fb_ps2_owner(int pid) {
    if (pid < 0 || pid >= MAX_PROCS) {
        return 0;
    }
    if (user_program_active || shell_fg_active) {
        return 1;
    }
    if (!vga_fb_gfx_mode) {
        return pid == 0;
    }
    if (wm_focus == WM_FOCUS_GFX) {
        return pid != 0;
    }
    return pid == 0;
}

/* Hit-test and dispatch a click on a titled window's controls. The
 * graphics window composites on top, so its title buttons are tested
 * first; a click elsewhere falls through to the focused terminal's
 * buttons, which work while a graphics program runs too. Graphics
 * minimize hides the app to the taskbar (it never closes it), maximize
 * toggles true fullscreen, close arms the close request. The terminal
 * buttons act on the terminal even while the graphics window holds the
 * focus, so its X can never close the game. Returns 1 when a control
 * consumed the click. */
static int wm_button_click(int mx, int my) {
    int btn;
    if (vga_fb_gfx_mode && !gfx_hidden && gfx_view_valid && gfx_view.title_h > 0) {
        btn = wm_buttons_hit(mx, my, gfx_view.frame.x, gfx_view.frame.y, gfx_view.frame.w);
        switch (btn) {
        case WM_BTN_MIN:
            vga_fb_gfx_set_hidden(1);
            return 1;
        case WM_BTN_MAX:
            vga_fb_gfx_set_fullscreen(1);
            return 1;
        case WM_BTN_CLOSE:
            wm_close_request = 1;
            return 1;
        default:
            break;
        }
    }
    if (gfx_covers_screen() || gfx_hit(mx, my) || term_minimized) return 0;
    btn = wm_buttons_hit(mx, my, term_px_x, term_px_y, term_px_w + SCROLLBAR_W);
    switch (btn) {
    case WM_BTN_MIN:
        term_toggle_minimize();
        return 1;
    case WM_BTN_MAX:
        term_toggle_fullscreen();
        return 1;
    case WM_BTN_CLOSE:
        if (vga_fb_gfx_mode) return 1;
        term_close_default();
        return 1;
    default:
        return 0;
    }
}

/** Docstring: Current graphics window title set via SYS_GFX_SET_TITLE. */
const char *gfx_win_title = GFX_TITLE_DEFAULT;

/** Docstring: Convert one source row into the target at the given scale.
 * sx advances in 16.16 fixed point from the first visible column, so
 * there is no division per pixel. Indexed sources expand through the
 * caller's lookup table in true color and copy as indices in 8-bit mode;
 * RGB sources pack directly (quantized to the wallpaper cube in 8-bit). */
static void gfx_scale_row(volatile uint8_t *row, const volatile uint8_t *srow,
                          int kind, int sw, int n, unsigned long fx,
                          unsigned long step, const unsigned *lut)
{
    int i;
    if (fb_bpp == 32) {
        volatile unsigned *q = (volatile unsigned *)row;
        for (i = 0; i < n; i++) {
            unsigned long sx = fx >> 16;
            if (sx >= (unsigned long)sw) sx = (unsigned long)sw - 1;
            if (kind == GFX_SRC_RGB) {
                const volatile uint8_t *p = srow + sx * 3UL;
                q[i] = ((unsigned)p[0] << 16) | ((unsigned)p[1] << 8) | (unsigned)p[2];
            } else {
                q[i] = lut[srow[sx]];
            }
            fx += step;
        }
    } else if (fb_bpp == 24) {
        for (i = 0; i < n; i++) {
            unsigned long sx = fx >> 16;
            unsigned px;
            if (sx >= (unsigned long)sw) sx = (unsigned long)sw - 1;
            if (kind == GFX_SRC_RGB) {
                const volatile uint8_t *p = srow + sx * 3UL;
                px = ((unsigned)p[0] << 16) | ((unsigned)p[1] << 8) | (unsigned)p[2];
            } else {
                px = lut[srow[sx]];
            }
            row[0] = (uint8_t)(px & 0xFF);
            row[1] = (uint8_t)((px >> 8) & 0xFF);
            row[2] = (uint8_t)((px >> 16) & 0xFF);
            row += 3;
            fx += step;
        }
    } else {
        for (i = 0; i < n; i++) {
            unsigned long sx = fx >> 16;
            if (sx >= (unsigned long)sw) sx = (unsigned long)sw - 1;
            if (kind == GFX_SRC_RGB) {
                const volatile uint8_t *p = srow + sx * 3UL;
                row[i] = (uint8_t)(WALL_PAL_BASE +
                         (wall_level((int)p[0]) * 6 + wall_level((int)p[1])) * 6 +
                         wall_level((int)p[2]));
            } else {
                row[i] = srow[sx];
            }
            fx += step;
        }
    }
}

/** Docstring: Nearest-neighbour blit of a sw x sh source into the dw x dh
 * rect at (dx, dy) of the render target, clipped once. The lookup table
 * is built once per call from gfx_pal (1 KB of stack, under the 2 KB
 * frame gate). Consecutive destination rows that sample the same source
 * row are copied from the row just written instead of re-converted, so a
 * 2.5x upscale costs barely more than the 1x path. */
static void gfx_scale_blit(const volatile uint8_t *src, int kind, int sw, int sh,
                           int dx, int dy, int dw, int dh)
{
    unsigned lut[256];
    unsigned long step;
    unsigned long bpx = (unsigned long)fb_bytes_per_pixel();
    int x0, x1, y, prev_sy = -1;
    volatile uint8_t *prev_row = 0;
    if (!src || sw <= 0 || sh <= 0 || dw <= 0 || dh <= 0) return;
    if (kind != GFX_SRC_RGB) {
        int k;
        for (k = 0; k < 256; k++) {
            unsigned o = (unsigned)k * 3u;
            lut[k] = ((unsigned)gfx_pal[o] << 16) | ((unsigned)gfx_pal[o + 1] << 8) |
                     (unsigned)gfx_pal[o + 2];
        }
    }
    x0 = dx < 0 ? -dx : 0;
    x1 = dx + dw > fb_width ? fb_width - dx : dw;
    if (x0 >= x1) return;
    step = ((unsigned long)sw << 16) / (unsigned long)dw;
    for (y = 0; y < dh; y++) {
        int ty = dy + y;
        int sy;
        volatile uint8_t *row;
        if (ty < 0) continue;
        if (ty >= fb_height) break;
        sy = (int)(((long)y * (long)sh) / (long)dh);
        if (sy >= sh) sy = sh - 1;
        row = FBT + (unsigned long)ty * (unsigned long)fb_pitch +
              (unsigned long)(dx + x0) * bpx;
        if (sy == prev_sy && prev_row) {
            fb_copy_bytes(row, prev_row, (unsigned long)(x1 - x0) * bpx);
        } else {
            const volatile uint8_t *srow = src + (unsigned long)sy * (unsigned long)sw *
                                           (kind == GFX_SRC_RGB ? 3UL : 1UL);
            gfx_scale_row(row, srow, kind, sw, x1 - x0,
                          (unsigned long)x0 * step, step, lut);
        }
        prev_sy = sy;
        prev_row = row;
    }
}

/** Docstring: Clear the frame area the content does not cover (the
 * letterbox bars of a tiled or fullscreen view) to black. */
static void gfx_letterbox(const wm_gfxview_t *v)
{
    int ax = v->frame.x;
    int ay = v->frame.y + v->title_h;
    int aw = v->frame.w;
    int ah = v->frame.h - v->title_h;
    const wm_gfxview_rect_t *c = &v->content;
    if (aw <= 0 || ah <= 0) return;
    if (c->y > ay)
        vga_fb_rect(ax, ay, aw, c->y - ay, COL_BLACK);
    if (c->y + c->h < ay + ah)
        vga_fb_rect(ax, c->y + c->h, aw, ay + ah - (c->y + c->h), COL_BLACK);
    if (c->x > ax)
        vga_fb_rect(ax, c->y, c->x - ax, c->h, COL_BLACK);
    if (c->x + c->w < ax + aw)
        vga_fb_rect(c->x + c->w, c->y, ax + aw - (c->x + c->w), c->h, COL_BLACK);
}

/** Docstring: Paint the title strip (title text plus window controls). */
static void gfx_title(const wm_gfxview_t *v)
{
    uint8_t gbg;
    if (v->title_h <= 0) return;
    gbg = (wm_focus == WM_FOCUS_GFX) ? COL_TITLEBAR : COL_SHADOW;
    vga_fb_rect(v->frame.x, v->frame.y, v->frame.w, v->title_h, gbg);
    text_px(v->frame.x + 4, v->frame.y, gfx_win_title, COL_TITLE_TXT, gbg);
    wm_draw_buttons(v->frame.x, v->frame.y, v->frame.w, COL_TITLE_TXT, gbg);
}

/** Docstring: Compose one graphics frame at a view into the render target:
 * title, letterbox (when full is set) and the scaled content. */
static void gfx_compose(const volatile uint8_t *src, int kind, int sw, int sh,
                        const wm_gfxview_t *v, int full)
{
    gfx_title(v);
    if (full)
        gfx_letterbox(v);
    gfx_scale_blit(src, kind, sw, sh, v->content.x, v->content.y,
                   v->content.w, v->content.h);
}

/** Docstring: Re-compose the persistent layer at the current view on top
 * of a desktop redraw (the target is the shadow inside draw_desktop). */
static void gfx_keep_restore(void) {
    wm_gfxview_t v;
    if (!vga_fb_gfx_mode || gfx_hidden || gfx_suppress || !gfx_keep || !gfx_keep_valid)
        return;
    if (!gfx_view_for(gfx_keep_sw, gfx_keep_sh, &v)) return;
    gfx_view_publish(&v);
    gfx_compose(gfx_keep, gfx_keep_kind, gfx_keep_sw, gfx_keep_sh, &v, 1);
    gfx_frame_dirty = 0;
}

/** Docstring: Present one back-buffer as the graphics window.
 * Every source (DOOM 320x200, the 800x360 indexed and RGB Nuklear
 * buffers) funnels through here, so the three view modes, the open melt,
 * the persistent layer and the pointer ownership are identical for every
 * app. A minimized window still counts and keeps its frame (the program
 * runs on) but paints nothing. */
static void gfx_present_locked(const volatile uint8_t *bb, int kind, int sw, int sh)
{
    wm_gfxview_t v;
    unsigned int *fx_old = 0;
    int fx_do;
    int changed;
    gfx_frames_composited++;
    if (!gfx_view_for(sw, sh, &v)) return;
    changed = !gfx_view_valid || !wm_gfxview_rect_same(&v.frame, &gfx_view.frame) ||
              !wm_gfxview_rect_same(&v.content, &gfx_view.content);
    gfx_view_publish(&v);
    if (gfx_hidden) {
        gfx_keep_save(bb, kind, sw, sh);
        return;
    }
    fx_do = fx_gfx_armed && vga_fx_enabled();
    fx_gfx_armed = 0;
    vga_fb_gfx_cursor_erase();
    if (fx_do)
        fx_old = vga_fx_snap_rect(v.frame.x, v.frame.y, v.frame.w, v.frame.h);
    gfx_compose(bb, kind, sw, sh, &v, changed || gfx_frame_dirty);
    gfx_frame_dirty = 0;
    gfx_keep_save(bb, kind, sw, sh);
    if (fx_old) {
        unsigned int *fx_new = vga_fx_snap_rect(v.frame.x, v.frame.y, v.frame.w, v.frame.h);
        if (fx_new) {
            vga_fx_restore_rect(v.frame.x, v.frame.y, v.frame.w, v.frame.h, fx_old);
            vga_fx_melt_rect(v.frame.x, v.frame.y, v.frame.w, v.frame.h, fx_old, fx_new);
            vga_fx_free(fx_new);
        }
        vga_fx_free(fx_old);
    }
    vga_fb_gfx_cursor_draw();
}

/** Docstring: Present under the pointer handshake: wait out a desktop tick
 * that is moving the sprite, composite, then stamp the present time the
 * tick's idle follow measures against. */
static void gfx_present(const volatile uint8_t *bb, int kind, int sw, int sh)
{
    __atomic_add_fetch(&gfx_presenting, 1, __ATOMIC_SEQ_CST);
    while (__atomic_load_n(&gfx_cursor_following, __ATOMIC_SEQ_CST))
        __asm__ volatile("pause" ::: "memory");
    gfx_present_locked(bb, kind, sw, sh);
    gfx_last_present = (unsigned long)sys_ticks;
    __atomic_sub_fetch(&gfx_presenting, 1, __ATOMIC_SEQ_CST);
}

/** Docstring: Move the graphics-mode pointer from the desktop tick while the
 * app is idle. The present path stays the pointer's painter whenever frames
 * flow; only after GFX_CURSOR_FOLLOW_TICKS without one, with the pointer
 * moved and no present or desktop composite in flight, does the tick
 * restore the old sprite and draw it at the new position with the same
 * save/restore helpers the present uses. */
static void gfx_cursor_follow_idle(void)
{
    if (!vga_fb_gfx_mode || fb_compose_depth > 0) return;
    if ((unsigned long)sys_ticks - gfx_last_present < GFX_CURSOR_FOLLOW_TICKS) return;
    if (mouse_state.x == gfx_cursor_lx && mouse_state.y == gfx_cursor_ly) return;
    __atomic_store_n(&gfx_cursor_following, 1, __ATOMIC_SEQ_CST);
    if (__atomic_load_n(&gfx_presenting, __ATOMIC_SEQ_CST) == 0) {
        vga_fb_gfx_cursor_erase();
        vga_fb_gfx_cursor_draw();
    }
    __atomic_store_n(&gfx_cursor_following, 0, __ATOMIC_SEQ_CST);
}

void vga_fb_blit_gfx_window(void) {
    gfx_present((const volatile uint8_t *)DOOM_BACKBUF_ADDR, GFX_SRC_IDX, DOOM_W, DOOM_H);
}

/* Window origin of the last Nuklear composite. Kept for ABI readers of
 * the header; the present syscalls report vga_fb_gfx_origin, which is the
 * real content origin in every view mode. */
int nk_win_x, nk_win_y;

void vga_fb_blit_nk_window(void) {
    gfx_present((const volatile uint8_t *)NK_BACKBUF_ADDR, GFX_SRC_IDX, NK_W, NK_H);
}

/* Composite the Nuklear RGB back-buffer (NK_RGB_ADDR, NK_W x NK_H x 3 bytes)
 * through the same present path as the indexed buffers. */
void vga_fb_blit_nk_rgb_window(void) {
    gfx_present((const volatile uint8_t *)NK_RGB_ADDR, GFX_SRC_RGB, NK_W, NK_H);
}

/* ---- Layout ---- */
static int term_max_cols(void);
static int term_max_rows(void);
static void term_render(void);

static void term_recalc(void) {
    int max_cols = term_max_cols();
    int max_rows = term_max_rows();
    if (term_fullscreen) {
        term_x = 0; term_y = 0;
        term_cols = max_cols;
        term_rows = max_rows;
    } else {
        term_cols = term_sz_cols;
        if (term_cols > max_cols) term_cols = max_cols;
        term_rows = term_sz_rows;
        if (term_rows > max_rows) term_rows = max_rows;
        /* Preserve the current window position, clamping it into range so a
         * drag or Ctrl+arrow move is not undone by the next layout pass. */
        if (term_x < 0) term_x = 0;
        if (term_y < 0) term_y = 0;
        if (term_x > max_cols - term_cols) term_x = max_cols - term_cols;
        if (term_y > max_rows - term_rows) term_y = max_rows - term_rows;
    }
    term_px_x = term_x * FONT_W;
    term_px_y = term_y * FONT_H;
    term_px_w = term_cols * FONT_W;
    term_px_h = term_rows * FONT_H;
}

/* ---- Desktop ---- */
static void draw_title_win(int idx, int focused) {
    const char *title = idx == 0 ? "MiniOS Terminal" : "MiniOS Terminal 2";
    uint8_t bg = focused ? COL_TITLEBAR : COL_SHADOW;
    int w = term_px_w + SCROLLBAR_W;
    int tw = 3 * (WM_BTN_W + WM_BTN_PAD) + 8;   /* room for the controls */
    vga_fb_rect(term_px_x, term_px_y, w, FONT_H, bg);
    if (w > tw)
        text_px(term_px_x + 4, term_px_y, title, COL_TITLE_TXT, bg);
    if (focused && w > tw + 2 * FONT_W)
        text_px(term_px_x + w - tw - 2 * FONT_W - 4, term_px_y, "*",
                COL_TITLE_TXT, bg);
    wm_draw_buttons(term_px_x, term_px_y, w, COL_TITLE_TXT, bg);
}



/* ---- Taskbar (clock + speaker volume + keyboard layout) ----
 * The bottom strip is the desktop's status bar: a live CMOS clock on the
 * right, a speaker icon with -/+ volume buttons, and an "EN"/"ES" keyboard
 * layout widget left of the speaker. The widgets and the shell
 * `date`/`vol`/`kbd` builtins share the same
 * rtc_read_tod/pcspk_get_volume/kbd_get_layout state, so the framebuffer and
 * the serial console can never disagree. */
static int tb_spk_x, tb_minus_x, tb_plus_x, tb_vol_x, tb_clock_x, tb_kbd_x;
static int tb_theme_x;
static int tb_restore_x, tb_restore_w;

/* Title chars shown on the running-app taskbar button (icon + text must
 * stay small: the taskbar is a single 8px row). */
#define TB_GFX_TITLE_MAX 10

static void taskbar_layout(void) {
    int x = fb_width;
    x -= TASKBAR_CLOCK_CH * FONT_W; tb_clock_x = x;
    x -= TASKBAR_PAD;
    x -= TASKBAR_VOL_CH * FONT_W;   tb_vol_x = x;
    x -= TASKBAR_PAD;
    x -= TASKBAR_BTN_W;             tb_plus_x = x;
    x -= TASKBAR_PAD;
    x -= TASKBAR_BTN_W;             tb_minus_x = x;
    x -= TASKBAR_PAD;
    x -= TASKBAR_ICON_W;            tb_spk_x = x;
    x -= TASKBAR_PAD;
    x -= TASKBAR_KBD_W;             tb_kbd_x = x;
    x -= TASKBAR_PAD;
    x -= TASKBAR_THEME_W;           tb_theme_x = x;
    /* Restore button on the far left: "[]" when a window is minimized. */
    tb_restore_w = 2 * FONT_W;
    tb_restore_x = TASKBAR_PAD;
    /* Running-app button right after it: mini icon + title while a graphics
     * program owns the display. Clicking it focuses the app (brings it to
     * the front), so a window buried by Alt+Tab/tile is always reachable. */
    tb_gfx_x = tb_restore_x + tb_restore_w + TASKBAR_PAD;
    tb_gfx_w = 0;
    if (vga_fb_gfx_mode) {
        int tl = (int)kstrlen(gfx_win_title);
        if (tl > TB_GFX_TITLE_MAX) tl = TB_GFX_TITLE_MAX;
        tb_gfx_w = FONT_W + 2 + tl * FONT_W;
    }
}

/* 8x8 speaker glyph: body on the left, two sound arcs to the right. */
static void draw_speaker_icon(int x, int y, uint8_t color) {
    vga_fb_rect(x, y + 1, 2, 6, color);
    vga_fb_rect(x + 2, y + 3, 2, 2, color);
    vga_fb_pixel(x + 4, y + 3, color);
    vga_fb_pixel(x + 5, y + 2, color);
    vga_fb_pixel(x + 5, y + 4, color);
    vga_fb_pixel(x + 6, y + 3, color);
}

static void taskbar_render(void) {
    char buf[16];
    int h, m, s;
    unsigned vol = pcspk_get_volume();
    int y = fb_height - FONT_H;
    int lx = 0;
    vga_fb_rect(0, y, fb_width, FONT_H, COL_TASKBAR);
    taskbar_layout();
    if (vga_fb_gfx_mode) {
        /* Running-app button: the app's own 32x32 icon downsampled to the
         * 8px row plus its title (bright when focused). The hint line
         * starts after it instead of underneath. */
        const uint8_t *ipx = gfx_task_icon();
        int tx = tb_gfx_x;
        int k;
        char t[TB_GFX_TITLE_MAX + 1];
        uint8_t fg = (wm_focus == WM_FOCUS_GFX) ? COL_HIGHLIGHT :
                                                   COL_TASKBAR_TXT;
        vga_fb_rect(tb_gfx_x, y, tb_gfx_w, FONT_H, COL_TASKBAR);
        if (ipx) {
            int ix, iy;
            for (iy = 0; iy < FONT_H; iy++) {
                for (ix = 0; ix < FONT_W; ix++) {
                    const uint8_t *sp =
                        ipx + ((unsigned long)(iy * 4) * ICON_W +
                               (unsigned long)(ix * 4)) * 4UL;
                    if (sp[3] < 128) continue;
                    if (fb_bpp == 8)
                        vga_fb_pixel(tx + ix, y + iy,
                                     (uint8_t)(ICON_PAL_BASE +
                                               icon_nearest(sp[0], sp[1],
                                                            sp[2])));
                    else
                        fb_write_packed(tx + ix, y + iy,
                                        ((unsigned long)sp[0] << 16) |
                                        ((unsigned long)sp[1] << 8) |
                                        (unsigned long)sp[2]);
                }
            }
            tx += FONT_W + 2;
        }
        for (k = 0; k < TB_GFX_TITLE_MAX && gfx_win_title[k]; k++)
            t[k] = gfx_win_title[k];
        t[k] = '\0';
        text_px(tx, y, t, fg, COL_TASKBAR);
        lx = tb_gfx_x + tb_gfx_w + TASKBAR_PAD;
    }
    text_px(lx, y, "Drag title:move Wheel:scroll Alt:snap/resize",
            COL_TASKBAR_TXT, COL_TASKBAR);
    if (term_minimized)
        text_px(tb_restore_x, y, "[]", COL_HIGHLIGHT, COL_TASKBAR);
    draw_speaker_icon(tb_spk_x, y, vol ? COL_TASKBAR_TXT : COL_HIGHLIGHT);
    text_px(tb_minus_x, y, "-", COL_TASKBAR_TXT, COL_TASKBAR);
    text_px(tb_plus_x, y, "+", COL_TASKBAR_TXT, COL_TASKBAR);
    ksprintf(buf, "%u%%", vol);
    text_px(tb_vol_x, y, buf, COL_TASKBAR_TXT, COL_TASKBAR);
    text_px(tb_kbd_x, y,
            kbd_get_layout() == KBD_LAYOUT_ES ? "ES" : "EN",
            COL_TASKBAR_TXT, COL_TASKBAR);
    {
        char theme[17];
        char tshow[TASKBAR_THEME_CH + 1];
        int k;
        vga_fb_theme_name(theme, sizeof(theme));
        for (k = 0; k < TASKBAR_THEME_CH && theme[k]; k++)
            tshow[k] = theme[k];
        tshow[k] = 0;
        text_px(tb_theme_x, y, tshow, COL_HIGHLIGHT, COL_TASKBAR);
    }
    if (rtc_read_tod(&h, &m, &s)) {
        ksprintf(buf, "%02d:%02d:%02d", h, m, s);
        text_px(tb_clock_x, y, buf, COL_TASKBAR_TXT, COL_TASKBAR);
    }
}

/* Redraw the clock only when the wall-clock second changes. Only the taskbar
 * strip is repainted, so the cursor must be re-saved (invalidated) only
 * when it actually sat over the taskbar; otherwise it keeps its saved
 * background and moves normally, which is what prevents pointer trails. */
static void taskbar_tick(void) {
    int h, m, s;
    int y = fb_height - FONT_H;
    static int last_h = -1, last_m = -1, last_s = -1;
    if (gfx_covers_screen()) return;
    if (!rtc_read_tod(&h, &m, &s)) return;
    if (h == last_h && m == last_m && s == last_s) return;
    last_h = h; last_m = m; last_s = s;
    taskbar_render();
    cursor_note_repaint(0, y, fb_width, FONT_H);
}

/** Docstring: Active Nuklear theme name for the taskbar widget.
 *
 * Reads etc/themes/current (ramdisk); a missing file, a bad name or an
 * overlong read falls back to "dark", never a stale or partial name. */
int vga_fb_theme_name(char *dst, int cap) {
    KFILE *f;
    int n = 0;
    if (cap <= 16) return -1;
    f = kfopen("etc/themes/current", "r");
    if (f) {
        int c;
        while (n < 16 && (c = kfgetc(f)) != EOF && c != '\n' && c != '\r') {
            if (!((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))) break;
            dst[n++] = (char)c;
        }
        kfclose(f);
        if (n > 0) { dst[n] = 0; return 0; }
    }
    dst[0] = 'd'; dst[1] = 'a'; dst[2] = 'r'; dst[3] = 'k'; dst[4] = 0;
    return -1;
}

/* Cycle the active theme to the next etc/themes/ entry (ramdisk). Holds
 * no locks; click context only. Writes the choice back to current so the
 * next app launch picks it up; running apps keep their theme. */
static void taskbar_theme_cycle(void) {
    RDFile *files[RAMDISK_MAX_FILES];
    char cur[17];
    int n, i, idx = -1, count = 0;
    char names[16][17];
    vga_fb_theme_name(cur, sizeof(cur));
    n = ramdisk_list(files, RAMDISK_MAX_FILES);
    for (i = 0; i < n && count < 16; i++) {
        const char *nm = files[i]->name;
        const char *rel;
        unsigned k;
        int ok = 1;
        if (kstrncmp(nm, "etc/themes/", 11) != 0) continue;
        rel = nm + 11;
        if (!rel[0] || kstrcmp(rel, "current") == 0) continue;
        for (k = 0; rel[k]; k++) {
            if (k >= 16 ||
                !((rel[k] >= 'a' && rel[k] <= 'z') ||
                  (rel[k] >= '0' && rel[k] <= '9'))) { ok = 0; break; }
        }
        if (!ok || k == 0) continue;
        kmemcpy(names[count], rel, k + 1);
        if (kstrcmp(rel, cur) == 0) idx = count;
        count++;
    }
    if (count == 0) return;
    {
        const char *next = names[(idx + 1) % count];
        KFILE *f = kfopen("etc/themes/current", "w");
        if (!f) return;
        kfputs(next, f);
        kfputc('\n', f);
        kfclose(f);
    }
}

/* Click handling for the keyboard widget, the speaker icon and -/+
 * buttons, plus the restore button that reappears while the terminal window
 * is minimized. A click on "EN" switches to Spanish and a click on "ES"
 * switches back to English. A click on the theme name cycles etc/themes. */
static void taskbar_handle_click(int mx, int my) {
    unsigned v;
    static int spk_saved_valid;
    static unsigned spk_saved_vol;
    int y = fb_height - FONT_H;
    if (my < y || my >= y + FONT_H) return;
    if (term_minimized &&
        mx >= tb_restore_x && mx < tb_restore_x + tb_restore_w) {
        vga_fb_toggle_minimize();
        return;
    }
    /* Running-app button: focus the graphics window, which redraws it on
     * top through the persistent layer — the buried app comes back. */
    taskbar_layout();
    if (vga_fb_gfx_mode && tb_gfx_w > 0 &&
        mx >= tb_gfx_x && mx < tb_gfx_x + tb_gfx_w) {
        int before = wm_focus;
        if (gfx_hidden) {
            vga_fb_gfx_set_hidden(0);
            return;
        }
        vga_fb_focus_id(WM_FOCUS_GFX);
        wm_emit_focus_moved(before, WM_FOCUS_SRC_TASKBAR);
        return;
    }
    if (mx >= tb_kbd_x && mx < tb_kbd_x + TASKBAR_KBD_W) {
        kbd_toggle_layout();
        taskbar_render();
        cursor_note_repaint(0, y, fb_width, FONT_H);
        return;
    }
    if (mx >= tb_theme_x && mx < tb_theme_x + TASKBAR_THEME_W) {
        taskbar_theme_cycle();
        taskbar_render();
        cursor_note_repaint(0, y, fb_width, FONT_H);
        return;
    }
    if (mx >= tb_spk_x && mx < tb_spk_x + TASKBAR_ICON_W) {
        v = pcspk_get_volume();
        if (v == 0) {
            pcspk_set_volume(spk_saved_valid ? spk_saved_vol : v);
        } else {
            spk_saved_vol = v;
            spk_saved_valid = 1;
            pcspk_set_volume(0);
        }
        return;
    }
    if (mx >= tb_minus_x && mx < tb_minus_x + TASKBAR_BTN_W) {
        v = pcspk_get_volume();
        pcspk_set_volume(v > TASKBAR_VOL_STEP ? v - TASKBAR_VOL_STEP : 0);
        return;
    }
    if (mx >= tb_plus_x && mx < tb_plus_x + TASKBAR_BTN_W) {
        pcspk_set_volume(pcspk_get_volume() + TASKBAR_VOL_STEP);
        return;
    }
}

/* ---- Scrollbar (attached to the window's right edge) ---- */
static void draw_scrollbar(void) {
    int sx = term_px_x + term_px_w;
    int sy = term_content_y();
    int sh = term_px_h;
    int total = total_rows();
    int visible = term_rows;
    int thumb_h, thumb_y;

    /* Track background */
    vga_fb_rect(sx, sy, SCROLLBAR_W, sh, COL_SCROLLBAR);

    /* Compute thumb size and position */
    if (total <= visible) {
        thumb_h = sh;
        thumb_y = sy;
    } else {
        int max_off = total - visible;
        thumb_h = (visible * sh) / total;
        if (thumb_h < 4) thumb_h = 4;
        thumb_y = sy + sh - thumb_h
                  - (disp_off * (sh - thumb_h)) / max_off;
    }
    /* Clamp */
    if (thumb_y < sy) thumb_y = sy;
    if (thumb_y + thumb_h > sy + sh) thumb_y = sy + sh - thumb_h;

    /* Thumb (with 1px inset on each side) */
    vga_fb_rect(sx + SCROLLBAR_PAD, thumb_y + SCROLLBAR_PAD,
                SCROLLBAR_W - 2 * SCROLLBAR_PAD,
                thumb_h - 2 * SCROLLBAR_PAD, COL_SCROLL_THUMB);
}

/* Blank one viewport row: every cell is repainted with the terminal
 * background. vga_fb_str with an empty string would draw nothing and leave
 * whatever pixels the previous content left behind, so blanking is explicit. */
static void render_blank_row(int vrow) {
    int c;
    for (c = 0; c < term_cols; c++)
        vga_fb_char(c, vrow, ' ', COL_TERM_TXT, COL_TERMINAL);
}

/* Render one display row at viewport row `vrow` for the absolute display row
 * `abs`. Rows outside the history (above the oldest line, or below the active
 * line) are blanked. When this is a row of the active line and a text cursor
 * is shown, the cursor cell is drawn inverted (COL_TERM_CUR background). */
static void render_row(int vrow, int abs) {
    const char *line;
    int off, len, c, src;
    int active_start = total_rows() - act_nrows();
    int is_active = (abs >= active_start);
    if (abs < 0) { render_blank_row(vrow); return; }
    line = line_at(abs, &off);
    if (!line) { render_blank_row(vrow); return; }
    len = (int)kstrlen(line);
    for (c = 0; c < term_cols; c++) {
        src = off + c;
        if (is_active && term_cursor_col >= 0) {
            int cl = term_cursor_col % term_cols;
            int crow = (term_cursor_col / term_cols);
            if (abs == active_start + crow && c == cl) {
                vga_fb_char(c, vrow, src < len ? line[src] : ' ',
                            COL_TERMINAL, COL_TERM_CUR);
                continue;
            }
        }
        vga_fb_char(c, vrow, src < len ? line[src] : ' ',
                    COL_TERM_TXT, COL_TERMINAL);
    }
}

/* Full repaint of the terminal window from the logical history, honouring the
 * current scroll position. Used on desktop redraws, resize, wrap, scroll and
 * any structural change. */
/** Docstring: 1 when the live terminal window may paint: never while it
 * is minimized (its text used to print onto the desktop where the window
 * had been) or while a fullscreen graphics window covers the display. */
static int term_paintable(void) {
    return !term_minimized && !gfx_covers_screen();
}

static void term_render(void) {
    int top = disp_top();
    int v;
    if (!term_paintable()) return;
    vga_fb_rect(term_px_x, term_content_y(), term_px_w, term_px_h, COL_TERMINAL);
    for (v = 0; v < term_rows; v++)
        render_row(v, top + v);
    draw_scrollbar();
}

/** Docstring: Clear the focused terminal view: drop the logical-line ring
 * and the in-progress line, snap the viewport to the live bottom and
 * repaint. The focused window owns the live globals, so a parked twin
 * keeps its own snapshot and picks up the cleared state only when it
 * becomes focused and parks again. Null-ring safe before vga_fb_init
 * owns the buffer (indices reset, render reads an empty ring). */
void term_clear(void) {
    lg_head = 0;
    lg_tail = 0;
    lg_count = 0;
    act[0] = '\0';
    act_len = 0;
    disp_off = 0;
    term_cursor_col = 0;
    csi_state = 0;
    term_render();
}

/* Repaint only the bottom region that a live edit touches: from the active
 * line's first visible display row to the bottom of the window. Used for a
 * character append/backspace that does not change the number of display rows,
 * so typing stays cheap while remaining correct. */
static void term_render_active(void) {
    int top = disp_top();
    int abs_active = total_rows() - act_nrows();
    int v0 = abs_active - top;
    int v;
    if (!term_paintable()) return;
    if (v0 < 0) v0 = 0;
    if (v0 >= term_rows) v0 = term_rows - 1;
    for (v = v0; v < term_rows; v++)
        render_row(v, top + v);
    draw_scrollbar();
}

/* Draw ONE cell of the active (typed) line, honoring the text cursor. This is
 * the O(1) per-character path: bulk console output appends a char at a time,
 * and redrawing the whole active row (term_cols glyphs, via term_render_active)
 * on every char made 100000-char output take ~14 s. A single cell draw is
 * ~100x cheaper and keeps the accumulating line live. */
static void term_draw_cell(int col) {
    int top = disp_top();
    int active_start = total_rows() - act_nrows();
    int crow = col / term_cols;
    int cl = col % term_cols;
    int abs = active_start + crow;
    int vrow = abs - top;
    if (!term_paintable()) return;
    if (vrow < 0 || vrow >= term_rows) return;
    char ch = (col < act_len) ? act[col] : ' ';
    int is_cur = (term_cursor_col == col);
    vga_fb_char(cl, vrow, ch,
                is_cur ? COL_TERMINAL : COL_TERM_TXT,
                is_cur ? COL_TERM_CUR : COL_TERMINAL);
}

/* Emit one character into the logical terminal. The active line is the only
 * editable state: '\n' completes it into the ring, printable characters append
 * to it, '\b' shortens it. The viewport always snaps to the live bottom on
 * output, so new input/output is always visible. When the edit changes the
 * number of display rows (wrap or newline), the whole window is repainted;
 * otherwise only the active line's rows are redrawn.
 *
 * act is kept NUL-terminated at act[act_len] after every mutation: render_row
 * reads it with kstrlen, so without that terminator a shorter new line would
 * display stale bytes left over from a longer previous line (e.g. the prompt
 * would show the tail of the previous command's last output line stuck after
 * it). */
void vga_fb_putc_term(char c) {
    int rows_before = total_rows();

    /* ANSI CSI drop: ring-3 fullscreen programs (vedit) address the serial
     * console with ESC [ ... final sequences. The logical terminal is a
     * scrolling line device with no 2D cursor, so it cannot honour them;
     * swallowing them here keeps the escapes (which the serial side needs)
     * from printing as literal "[2J[H" garbage on the desktop. A bare ESC
     * outside a sequence is ignored as before. */
    if (csi_state == 1) {
        if (c == '[') { csi_state = 2; return; }
        csi_state = 0;
        if (c == '\x1b') { csi_state = 1; return; }
    } else if (csi_state == 2) {
        if ((c >= '0' && c <= '9') || c == ';' || c == '?') return;
        csi_state = 0;
        return;
    }
    if (c == '\x1b') { csi_state = 1; return; }

    if (c == '\n') {
        /* Once the ring is full every push evicts the oldest line, so the
         * total row count can stay identical while the whole viewport moved
         * up one line. Comparing row counts alone would then take the
         * active-line-only fast path and freeze the screen (only the bottom
         * line ever repainted), so an evicting push always fully renders. */
        int evicted = (lg_count == SB_MAX_LINES);
        lg_push(act, act_len);
        act_len = 0;
        act[0] = '\0';
        disp_off = 0;
        if (evicted || total_rows() != rows_before) term_render();
        else term_render_active();
        return;
    }
    if (c == '\r') { disp_off = 0; return; }
    if (c == '\b') {
        if (act_len > 0) act_len--;
        act[act_len] = '\0';
        disp_off = 0;
        if (total_rows() != rows_before) term_render();
        else term_render_active();
        return;
    }
    if (kbd_is_printable((unsigned char)c)) {
        int old_len = act_len;
        if (act_len < SB_LINE_MAX - 1) {
            act[act_len++] = c;
            act[act_len] = '\0';
        }
        disp_off = 0;
        if (total_rows() != rows_before) {
            term_render();          /* wrap changed the row count: full repaint */
        } else {
            /* Revert the previous cursor cell, then paint the new char cell. */
            if (term_cursor_col >= 0 && term_cursor_col < old_len)
                term_draw_cell(term_cursor_col);
            term_draw_cell(act_len - 1);
        }
        return;
    }
}

void vga_fb_puts_term(const char *s) {
    while (*s) vga_fb_putc_term(*s++);
}

/* Show the text cursor at character column `col` of the active line, or hide
 * it with a negative column. The cursor is a block rendered by render_row. */
void vga_fb_text_cursor(int col) {
    if (col < 0) { term_cursor_col = -1; }
    else { term_cursor_col = col; }
    disp_clamp();
    term_render();
}

/* Hide the text cursor (used when a live edit starts or the window redraws). */
void vga_fb_hide_text_cursor(void) {
    term_cursor_col = -1;
}

/** Docstring: Paint the pointer into the frame being composed, so the
 * presented frame already carries it (no pointer-less flash after every
 * redraw). The graphics path keeps its idle autohide. */
static void desktop_cursor_paint(void) {
    cursor_invalidate();
    if (!mouse_state.present && !vga_fb_gfx_mode) return;
    if (vga_fb_gfx_mode) {
        vga_fb_gfx_cursor_draw();
        return;
    }
    wm_clamp_point(&mouse_state.x, &mouse_state.y, fb_width, fb_height);
    cursor_place(mouse_state.x, mouse_state.y);
}

/** Docstring: Repaint the desktop through the shared render plan.
 * The whole frame composes off-screen (see the render-target section)
 * and is presented once, pointer included, so a redraw never flashes a
 * cleared or half-painted screen. A pending graphics-close melt keeps
 * the closing rect showing the old pixels in the presented frame and
 * then melts the fresh desktop over it on the visible framebuffer. */
void vga_fb_draw_desktop(void) {
    int cur;
    int i;
    int owner;
    int present[WM_MAX_TERMS];
    wm_render_config_t rcfg = WM_RENDER_CONFIG_DEFAULT;
    wm_render_item_t plan[8];
    int nplan = 0;
    int focus_term;
    int fx_cx = fx_close_x, fx_cy = fx_close_y, fx_cw = fx_close_w, fx_ch = fx_close_h;
    unsigned int *fx_old = 0;
    int fx_do = fx_close_pending && vga_fx_enabled();
    fx_close_pending = 0;
    if (fx_do) {
        cursor_erase();
        fx_old = vga_fx_snap_rect(fx_cx, fx_cy, fx_cw, fx_ch);
        if (!fx_old) {
            fx_do = 0;
        }
    }
    owner = fb_compose_begin();
    vga_fb_set_palette();
    vga_fb_clear();
    wm_init_once();
    cur = wm_term;
    term_recalc();
    tw_park(cur);
    wallpaper_draw();
    desktop_shortcuts_load();
    desktop_shortcuts_draw();
    taskbar_render();
    for (i = 0; i < wm_nterms && i < WM_MAX_TERMS; i++)
        present[i] = twins[i].present;
    focus_term = (wm_focus == WM_FOCUS_GFX) ? cur : wm_focus;
    nplan = wm_build_render_plan(&rcfg, present, wm_nterms, focus_term, vga_fb_gfx_mode ? 1 : 0, plan, 8);
    for (i = 0; i < nplan; i++) {
        if (plan[i].layer != WM_LAYER_TERMINAL) {
            continue;
        }
        tw_unpark(plan[i].id);
        term_recalc();
        if (!term_minimized) {
            draw_title_win(plan[i].id, plan[i].id == wm_focus);
            disp_clamp();
            term_render();
        }
    }
    tw_unpark(cur);
    gfx_frame_dirty = 1;
    gfx_keep_restore();
    if (fx_do) {
        unsigned int *fx_new = vga_fx_snap_rect(fx_cx, fx_cy, fx_cw, fx_ch);
        cursor_invalidate();
        if (fx_new) {
            vga_fx_restore_rect(fx_cx, fx_cy, fx_cw, fx_ch, fx_old);
            fb_compose_end(owner);
            vga_fx_melt_rect(fx_cx, fx_cy, fx_cw, fx_ch, fx_old, fx_new);
            vga_fx_free(fx_new);
        } else {
            fb_compose_end(owner);
        }
        vga_fx_free(fx_old);
        cursor_invalidate();
        return;
    }
    if (!fb_hold_present)
        desktop_cursor_paint();
    else
        cursor_invalidate();
    fb_compose_end(owner);
}

/* ---- Graphics window transitions ----
 *
 * A view change (fullscreen on/off, tile, snap, reset, minimize, restore)
 * glides the graphics window between its old and new frame instead of
 * jumping: the desktop without the graphics layer is composed once, kept
 * as a background, and every animation step copies it back into the
 * shadow, scales the persistent source frame into the interpolated rect
 * (ease-out cubic, wm_gfxview.h) and presents. Steps are paced against
 * the PIT-calibrated clock by deadline, so a slow step shortens the next
 * wait instead of stretching the whole glide. The final frame is a
 * normal desktop redraw, so the end state is byte-identical with the
 * effect on or off, and every failure (effect off, OOM, no source yet,
 * nested composition) degrades to that plain redraw. */

/** Docstring: Busy-wait until an absolute ktime_ms deadline. */
static void gfx_wait_until(unsigned long deadline)
{
    while ((long)(deadline - ktime_ms()) > 0) {
    }
}

/** Docstring: View of the persistent source inside an arbitrary frame,
 * titled when the frame is tall enough to carry a title strip. */
static void gfx_view_in_rect(const wm_gfxview_rect_t *r, int titled, wm_gfxview_t *v)
{
    wm_gfxview_config_t cfg = gfx_view_cfg();
    wm_gfxview_rect_t area;
    v->mode = gfx_view_mode;
    v->frame = *r;
    v->title_h = (titled && r->h > 2 * FONT_H) ? FONT_H : 0;
    area.x = r->x;
    area.y = r->y + v->title_h;
    area.w = r->w;
    area.h = r->h - v->title_h;
    if (area.h < 1) area.h = 1;
    if (!wm_gfxview_place_content(&cfg, gfx_keep_sw, gfx_keep_sh, &area, &v->content)) {
        v->content = area;
    }
}

/** Docstring: Glide the persistent source frame from one rect to
 * another over the desktop, then settle with a plain redraw. */
static void gfx_animate(const wm_gfxview_rect_t *from, const wm_gfxview_rect_t *to,
                        int from_titled, int to_titled)
{
    wm_gfxview_config_t cfg = gfx_view_cfg();
    uint8_t *bg;
    unsigned long bytes;
    unsigned long t0;
    int t;
    int n = cfg.anim_frames;
    if (!from || !to || !vga_fx_enabled() || !gfx_keep || !gfx_keep_valid ||
        fb_compose_depth > 0 || fb_hold_present || !fb_shadow_ready() || n < 2 ||
        wm_gfxview_rect_same(from, to)) {
        vga_fb_draw_desktop();
        return;
    }
    bytes = fb_frame_bytes();
    bg = (uint8_t *)kmalloc(bytes);
    if (!bg) {
        vga_fb_draw_desktop();
        return;
    }
    gfx_suppress = 1;
    fb_hold_present = 1;
    vga_fb_draw_desktop();
    fb_hold_present = 0;
    gfx_suppress = 0;
    fb_copy_bytes(bg, fb_shadow, bytes);
    cursor_erase();
    t0 = ktime_ms();
    for (t = 1; t < n; t++) {
        wm_gfxview_rect_t r;
        wm_gfxview_t v;
        wm_gfxview_lerp_rect(from, to, t, n, &r);
        gfx_view_in_rect(&r, (t * 2 < n) ? from_titled : to_titled, &v);
        fb_copy_bytes(fb_shadow, bg, bytes);
        fb_compose_depth++;
        fb_tgt = fb_shadow;
        gfx_compose(gfx_keep, gfx_keep_kind, gfx_keep_sw, gfx_keep_sh, &v, 0);
        fb_tgt = 0;
        fb_compose_depth--;
        fb_present_shadow();
        gfx_wait_until(t0 + (unsigned long)(t * cfg.anim_frame_ms));
    }
    kfree(bg);
    cursor_invalidate();
    gfx_frame_dirty = 1;
    vga_fb_draw_desktop();
}

/** Docstring: Taskbar button rect of the running app (minimize target). */
static void gfx_taskbar_rect(wm_gfxview_rect_t *r)
{
    taskbar_layout();
    r->x = tb_gfx_x;
    r->y = fb_height - FONT_H;
    r->w = tb_gfx_w > 0 ? tb_gfx_w : FONT_W;
    r->h = FONT_H;
}

/** Docstring: Glide from a previous frame to the view the current state
 * computes (or just redraw when there is nothing to glide from). */
static void gfx_transition(const wm_gfxview_rect_t *from, int from_titled)
{
    wm_gfxview_t to;
    if (!from || gfx_hidden || !gfx_keep_valid ||
        !gfx_view_for(gfx_keep_sw, gfx_keep_sh, &to)) {
        gfx_frame_dirty = 1;
        vga_fb_draw_desktop();
        return;
    }
    gfx_animate(from, &to.frame, from_titled, to.title_h > 0);
}

/** Docstring: Hand keyboard focus to the graphics window without a
 * redraw (callers repaint once afterwards). */
static void gfx_take_focus(int source)
{
    int before = wm_focus;
    if (wm_focus == WM_FOCUS_GFX) return;
    if (shell_readline_active()) shell_focus_park();
    tw_park(wm_term);
    wm_focus = WM_FOCUS_GFX;
    kbd_raw_flush();
    wm_emit_focus_moved(before, source);
}

/** Docstring: Hand keyboard focus back to the last terminal. */
static void gfx_drop_focus(int source)
{
    int before = wm_focus;
    if (wm_focus != WM_FOCUS_GFX) return;
    tw_select(wm_term);
    wm_emit_focus_moved(before, source);
}

/** Docstring: Enter or leave true fullscreen for the graphics window.
 * Fullscreen scales the app to the whole display (aspect kept, black
 * bars, no chrome, taskbar and terminals hidden) and takes the keyboard;
 * leaving returns to the view it came from (floating or tiled). Returns
 * 0 on success, -1 without a graphics program. */
int vga_fb_gfx_set_fullscreen(int on)
{
    wm_gfxview_rect_t from;
    int had = gfx_view_valid && !gfx_hidden;
    int titled = had && gfx_view.title_h > 0;
    if (!vga_fb_gfx_mode) return -1;
    from = gfx_view.frame;
    if (gfx_hidden) {
        gfx_hidden = 0;
        gfx_taskbar_rect(&from);
        had = 1;
        titled = 0;
    }
    if (on) {
        if (gfx_view_mode == WM_GFXVIEW_FULL) return 0;
        gfx_view_back = gfx_view_mode;
        gfx_view_mode = WM_GFXVIEW_FULL;
        gfx_take_focus(WM_FOCUS_SRC_MODE);
    } else {
        if (gfx_view_mode != WM_GFXVIEW_FULL) return 0;
        gfx_view_mode = (gfx_view_back == WM_GFXVIEW_FULL) ? WM_GFXVIEW_FLOAT : gfx_view_back;
    }
    gfx_frame_dirty = 1;
    wm_last_n = -1;
    gfx_transition(had ? &from : 0, titled);
    return 0;
}

/** Docstring: Minimize (hide) or restore the graphics window. The app
 * keeps running; a hidden window paints nothing, drops the keyboard to
 * the terminal and glides into its taskbar button; a restore glides back
 * out and takes the keyboard. Returns 0, or -1 without a program. */
int vga_fb_gfx_set_hidden(int hide)
{
    wm_gfxview_rect_t btn;
    wm_gfxview_rect_t from;
    int titled;
    if (!vga_fb_gfx_mode) return -1;
    if ((hide ? 1 : 0) == gfx_hidden) return 0;
    gfx_taskbar_rect(&btn);
    if (hide) {
        from = gfx_view.frame;
        titled = gfx_view.title_h > 0;
        gfx_hidden = 1;
        gfx_drop_focus(WM_FOCUS_SRC_TASKBAR);
        wm_last_n = -1;
        if (gfx_view_valid)
            gfx_animate(&from, &btn, titled, 0);
        else
            vga_fb_draw_desktop();
        return 0;
    }
    gfx_hidden = 0;
    gfx_take_focus(WM_FOCUS_SRC_TASKBAR);
    wm_last_n = -1;
    gfx_transition(&btn, 0);
    return 0;
}

/** Docstring: Graphics view state for `wm state`/`wm list`. */
const char *vga_fb_gfx_view_name(void)
{
    const char *n;
    if (!vga_fb_gfx_mode) return "none";
    if (gfx_hidden) return "minimized";
    n = wm_gfxview_mode_name(gfx_view_mode);
    return n ? n : "floating";
}

/* ---- Keyboard shortcuts ---- */

/** Docstring: Toggle fullscreen of the focused terminal window. */
static void term_toggle_fullscreen(void) {
    unsigned int *fx_old = fx_start_full();
    term_fullscreen = !term_fullscreen;
    if (term_fullscreen) term_minimized = 0;
    disp_off = 0;
    wm_last_n = -1;
    vga_fb_draw_desktop();
    fx_finish_full(fx_old);
}

/** Docstring: Toggle fullscreen on the focused window: the graphics
 * window scales to the whole display, a terminal fills the grid. */
void vga_fb_toggle_fullscreen(void) {
    if (vga_fb_gfx_mode && wm_focus == WM_FOCUS_GFX) {
        vga_fb_gfx_set_fullscreen(gfx_view_mode != WM_GFXVIEW_FULL);
        return;
    }
    term_toggle_fullscreen();
}

/* Minimize/restore the terminal window. The content is not touched; the
 * window is merely hidden and repainted on restore. Fullscreen and minimize
 * are mutually exclusive: entering fullscreen un-minimizes. */
static void term_toggle_minimize(void) {
    unsigned int *fx_old = fx_start_full();
    term_minimized = !term_minimized;
    if (term_minimized) term_fullscreen = 0;
    disp_off = 0;
    vga_fb_draw_desktop();
    fx_finish_full(fx_old);
}

/** Docstring: Minimize/restore the focused window (graphics or terminal). */
void vga_fb_toggle_minimize(void) {
    if (vga_fb_gfx_mode && wm_focus == WM_FOCUS_GFX) {
        vga_fb_gfx_set_hidden(1);
        return;
    }
    term_toggle_minimize();
}

int vga_fb_is_minimized(void) { return term_minimized; }
int vga_fb_is_fullscreen(void) { return term_fullscreen; }

/* Snap the focused graphics window into a screen region (halves place it
 * against that edge, quadrants into that corner) at its native size: a
 * snap floats the window, it never scales it. Glides to the target. */
static void gfx_snap(int zone) {
    wm_gfxview_rect_t ff;
    wm_gfxview_rect_t from = gfx_view.frame;
    int titled = gfx_view.title_h > 0;
    int w, h, cx, cy, tx, ty;
    if (!gfx_float_frame(&ff)) return;
    w = ff.w;
    h = ff.h;
    cx = (fb_width - w) / 2;
    cy = (fb_height - h) / 2;
    tx = cx;
    ty = cy;
    switch (zone) {
    case TILING_LEFT: tx = 0; ty = cy; break;
    case TILING_RIGHT: tx = fb_width - w; ty = cy; break;
    case TILING_TOP: tx = cx; ty = 0; break;
    case TILING_BOTTOM: tx = cx; ty = fb_height - h; break;
    case TILING_TOP_LEFT: tx = 0; ty = 0; break;
    case TILING_TOP_RIGHT: tx = fb_width - w; ty = 0; break;
    case TILING_BOTTOM_LEFT: tx = 0; ty = fb_height - h; break;
    case TILING_BOTTOM_RIGHT: tx = fb_width - w; ty = fb_height - h; break;
    default: return;
    }
    gfx_view_mode = WM_GFXVIEW_FLOAT;
    gfx_view_back = WM_GFXVIEW_FLOAT;
    gfx_win_ox = tx - cx;
    gfx_win_oy = ty - cy;
    gfx_frame_dirty = 1;
    gfx_transition(gfx_view_valid ? &from : 0, titled);
}

/** Docstring: Terminal close button: restore the default geometry (the
 * shell cannot be closed). */
static void term_close_default(void) {
    term_minimized = 0;
    term_fullscreen = 0;
    term_sz_cols = WIN_DEF_COLS;
    term_sz_rows = WIN_DEF_ROWS;
    term_x = WIN_DEF_X;
    term_y = WIN_DEF_Y;
    disp_off = 0;
    vga_fb_draw_desktop();
}

/* Close the focused window. For the graphics window (focused) this arms
 * the close request that the syscall dispatcher honours on the child's
 * next syscall; for a terminal it restores the default position (the
 * shell cannot be closed). Returns 1 when a close was armed, 0
 * otherwise. */
int vga_fb_close_active(void) {
    if (vga_fb_gfx_mode && wm_focus == WM_FOCUS_GFX) {
        wm_close_request = 1;
        return 1;
    }
    if (vga_fb_gfx_mode) {
        /* A graphics program owns the display: only its own focused
         * window may close it, never a terminal shortcut. */
        return 0;
    }
    term_close_default();
    return 0;
}

void vga_fb_move_terminal(int dx, int dy) {
    /* Ctrl+arrows move the focused window: terminals by cell, graphics
     * by pixels (which floats a tiled graphics window first). */
    if (wm_focus == WM_FOCUS_GFX && vga_fb_gfx_mode) {
        if (gfx_view_mode == WM_GFXVIEW_FULL) return;
        if (gfx_view_mode != WM_GFXVIEW_FLOAT) {
            gfx_view_mode = WM_GFXVIEW_FLOAT;
            gfx_view_back = WM_GFXVIEW_FLOAT;
            gfx_win_ox = 0;
            gfx_win_oy = 0;
        }
        gfx_frame_dirty = 1;
        if (dx == 0 && dy == 0) { gfx_win_ox = 0; gfx_win_oy = 0; vga_fb_draw_desktop(); return; }
        gfx_win_ox += dx * FONT_W;
        gfx_win_oy += dy * FONT_H;
        vga_fb_draw_desktop();
        return;
    }
    if (dx == 0 && dy == 0) {
        /* Reset to default position */
        term_fullscreen = 0;
        term_x = WIN_DEF_X; term_y = WIN_DEF_Y;
        disp_off = 0;
        vga_fb_draw_desktop();
        return;
    }
    int max_x = (fb_width - SCROLLBAR_W) / FONT_W - term_cols;
    int max_y = (fb_height - 2 * FONT_H) / FONT_H - term_rows;
    int nx = term_x + dx;
    int ny = term_y + dy;
    if (nx < 0) nx = 0;
    if (ny < 0) ny = 0;
    if (nx > max_x) nx = max_x;
    if (ny > max_y) ny = max_y;
    if (nx == term_x && ny == term_y) return;
    term_x = nx; term_y = ny;
    term_px_x = term_x * FONT_W;
    term_px_y = term_y * FONT_H;
    vga_fb_draw_desktop();
}

/* ---- Tiling window operations (Alt = WM modifier) ----
 * Snap places the window in a screen half or quadrant and sizes it to that
 * region; resize grows/shrinks the persisted size. Both exit fullscreen and
 * preserve the new size across redraws. */
static int term_max_cols(void) {
    int m = (fb_width - SCROLLBAR_W) / FONT_W;
    return m > TERM_MAX_COLS ? TERM_MAX_COLS : m;
}
static int term_max_rows(void) {
    int m = (fb_height - 2 * FONT_H) / FONT_H;
    return m > TERM_MAX_ROWS ? TERM_MAX_ROWS : m;
}

static void term_finish_layout(void) {
    term_recalc();
    disp_off = 0;
    vga_fb_draw_desktop();
}

void vga_fb_snap_window(int zone) {
    int mc;
    if (wm_focus == WM_FOCUS_GFX && vga_fb_gfx_mode) {
        if (gfx_view_mode != WM_GFXVIEW_FULL)
            gfx_snap(zone);
        return;
    }
    mc = term_max_cols();
    int mr = term_max_rows();
    int hw = mc / 2;
    int hh = mr / 2;
    int ow = mc - hw;   /* right/bottom half (larger when odd) */
    int oh = mr - hh;
    term_fullscreen = 0;
    switch (zone) {
    case TILING_LEFT:        term_sz_cols = hw; term_sz_rows = mr; term_x = 0; term_y = 0; break;
    case TILING_RIGHT:       term_sz_cols = ow; term_sz_rows = mr; term_x = hw; term_y = 0; break;
    case TILING_TOP:         term_sz_cols = mc; term_sz_rows = hh; term_x = 0; term_y = 0; break;
    case TILING_BOTTOM:      term_sz_cols = mc; term_sz_rows = oh; term_x = 0; term_y = hh; break;
    case TILING_TOP_LEFT:    term_sz_cols = hw; term_sz_rows = hh; term_x = 0; term_y = 0; break;
    case TILING_TOP_RIGHT:   term_sz_cols = ow; term_sz_rows = hh; term_x = hw; term_y = 0; break;
    case TILING_BOTTOM_LEFT: term_sz_cols = hw; term_sz_rows = oh; term_x = 0; term_y = hh; break;
    case TILING_BOTTOM_RIGHT: term_sz_cols = ow; term_sz_rows = oh; term_x = hw; term_y = hh; break;
    default: return;
    }
    term_finish_layout();
}

void vga_fb_resize(int dcols, int drows) {
    int mc;
    /* Graphics backbuffers are fixed-size: resize is terminal-only. */
    if (wm_focus == WM_FOCUS_GFX && vga_fb_gfx_mode) return;
    mc = term_max_cols();
    int mr = term_max_rows();
    int ncol = term_sz_cols + dcols;
    int nrow = term_sz_rows + drows;
    if (ncol < 1) ncol = 1;
    if (nrow < 1) nrow = 1;
    if (ncol > mc) ncol = mc;
    if (nrow > mr) nrow = mr;
    if (ncol == term_sz_cols && nrow == term_sz_rows && !term_fullscreen) return;
    term_fullscreen = 0;
    term_sz_cols = ncol;
    term_sz_rows = nrow;
    term_finish_layout();
}

/** Docstring: Restore defaults on the focused window plus graphics offset. */
void vga_fb_reset_default(void) {
    if (vga_fb_gfx_mode) {
        gfx_win_ox = 0;
        gfx_win_oy = 0;
        gfx_view_mode = WM_GFXVIEW_FLOAT;
        gfx_view_back = WM_GFXVIEW_FLOAT;
        gfx_frame_dirty = 1;
    }
    term_fullscreen = 0;
    term_sz_cols = WIN_DEF_COLS;
    term_sz_rows = WIN_DEF_ROWS;
    term_x = WIN_DEF_X;
    term_y = WIN_DEF_Y;
    term_finish_layout();
}

/* Move the window so its title bar follows the mouse during a drag. grab_cx
 * is the character column (within the title bar) where the grab happened, so
 * the window stays under the pointer instead of jumping to the mouse origin. */
static void vga_fb_drag_terminal(int mx, int my, int grab_cx) {
    int max_x = (fb_width - SCROLLBAR_W) / FONT_W - term_cols;
    int max_y = (fb_height - 2 * FONT_H) / FONT_H - term_rows;
    int nx = mx / FONT_W - grab_cx;
    int ny = my / FONT_H;
    if (nx < 0) nx = 0;
    if (ny < 0) ny = 0;
    if (nx > max_x) nx = max_x;
    if (ny > max_y) ny = max_y;
    if (nx == term_x && ny == term_y) return;
    term_x = nx; term_y = ny;
    term_px_x = term_x * FONT_W;
    term_px_y = term_y * FONT_H;
    vga_fb_draw_desktop();
}

/* ---- Wallpaper ----
 * The background is a photographic PNG (wall/wallpaper.png on the ramdisk),
 * not a solid fill. It is decoded ONCE per boot via stbi_load_file and cached
 * in the kernel heap: draw_desktop runs on every window move/resize/drag
 * tick, and re-decoding a ~650 KB PNG there would stall the pointer. In
 * 8-bit mode the cache holds cube-mapped indices; in true color it holds
 * full 24-bit RGB (3 bytes per pixel, no quantization), so a photographic
 * wallpaper shows its real colors instead of the 216-entry websafe cube.
 * A failed or missing image falls back to the solid COL_BG fill, and
 * a failed cache allocation does the same, never a partial background. */
/** Docstring: Wallpaper cache in the framebuffer's native pixel format
 * (palette indices in 8-bit, B,G,R in 24-bit, B,G,R,X in 32-bit), rows of
 * fb_width pixels with no pitch padding. A full paint or a strip erase is
 * then one bulk row copy per scanline instead of a packed write per
 * pixel, which is what makes every desktop redraw cheap. */
static uint8_t *wall_native;
static int wall_cw, wall_ch, wall_bpx;
static int wall_tried;

static void wallpaper_ensure(void) {
    int w, h, ch, x, y;
    int bpx = fb_bytes_per_pixel();
    unsigned char *img;
    uint8_t *cache;
    unsigned long npix;
    if (wall_tried || fb_width <= 0 || fb_height <= 0)
        return;
    wall_tried = 1;
    npix = (unsigned long)fb_width * (unsigned long)fb_height;
    if (npix == 0 || npix > 4194304UL)
        return;
    img = stbi_load_file(WALLPAPER_PATH, &w, &h, &ch, 4);
    if (!img)
        return;
    if (w <= 0 || h <= 0) {
        stbi_image_free(img);
        return;
    }
    cache = kmalloc(npix * (unsigned long)bpx);
    if (!cache) {
        stbi_image_free(img);
        return;
    }
    for (y = 0; y < fb_height; y++) {
        int sy = y * h / fb_height;
        uint8_t *drow = cache + (unsigned long)y * (unsigned long)fb_width * (unsigned long)bpx;
        for (x = 0; x < fb_width; x++) {
            int sx = x * w / fb_width;
            unsigned char *px = img + ((sy * w) + sx) * 4;
            if (bpx == 1) {
                int idx = (wall_level(px[0]) * 6 + wall_level(px[1])) * 6
                          + wall_level(px[2]);
                drow[x] = (uint8_t)(WALL_PAL_BASE + idx);
            } else {
                uint8_t *d = drow + (unsigned long)x * (unsigned long)bpx;
                d[0] = px[2];
                d[1] = px[1];
                d[2] = px[0];
                if (bpx == 4)
                    d[3] = 0;
            }
        }
    }
    stbi_image_free(img);
    wall_native = cache;
    wall_cw = fb_width;
    wall_ch = fb_height;
    wall_bpx = bpx;
}

/** Docstring: True when the native cache matches the live mode. */
static int wallpaper_usable(void) {
    return wall_native && wall_cw == fb_width && wall_ch == fb_height &&
           wall_bpx == fb_bytes_per_pixel();
}

static void wallpaper_draw(void) {
    int y;
    unsigned long row;
    wallpaper_ensure();
    if (!wallpaper_usable()) {
        vga_fb_rect(0, 0, fb_width, fb_height, COL_BG);
        return;
    }
    row = (unsigned long)fb_width * (unsigned long)wall_bpx;
    for (y = 0; y < fb_height; y++)
        fb_copy_bytes(FBT + (unsigned long)y * (unsigned long)fb_pitch,
                      wall_native + (unsigned long)y * row, row);
}

/* ---- Desktop shortcut icons ----
 * Shortcuts are defined in etc/shortcuts on the ramdisk, one per line:
 *   name|icon_path|command
 * Icons are 32x32 PNG files decoded at boot via stbi_load_file and mapped
 * to the icon palette (VGA DAC indices 240-255).  The cached palette-indexed
 * pixels are redrawn on every desktop paint; mouse clicks launch the command. */

static struct desktop_shortcut shortcuts[MAX_SHORTCUTS];
static int shortcut_count;
static int shortcuts_loaded;

/* Find a pipe-delimited field by index (0-based). */
static const char *pipe_field(const char *line, int idx, char *buf, int buflen) {
    const char *p = line;
    for (int i = 0; i < idx; i++) {
        while (*p && *p != '|') p++;
        if (*p == '|') p++;
        else return 0;
    }
    const char *start = p;
    while (*p && *p != '\n' && *p != '\r' && *p != '|') p++;
    int len = (int)(p - start);
    if (len >= buflen) len = buflen - 1;
    for (int i = 0; i < len; i++) buf[i] = start[i];
    buf[len] = '\0';
    return buf;
}

/* Nearest entry in the 16-colour icon palette (squared RGB distance,
 * integer-only: at most 3*255*255 per entry, far from overflow). */
static int icon_nearest(int r, int g, int b) {
    int best = 0, best_d = 0x7fffffff, i;
    for (i = 0; i < ICON_PAL_SIZE; i++) {
        int dr = r - icon_pal[i][0];
        int dg = g - icon_pal[i][1];
        int db = b - icon_pal[i][2];
        int d = dr * dr + dg * dg + db * db;
        if (d < best_d) {
            best_d = d;
            best = i;
        }
    }
    return best;
}

/* Embedded fallback when the shortcut's PNG is missing or undecodable. */
static const uint8_t *icon_embedded(const char *name) {
    if (kstrcmp(name, "Terminal") == 0)
        return icon_terminal;
    if (kstrcmp(name, "DOOM") == 0)
        return icon_doom;
    if (kstrcmp(name, "Nuklear") == 0)
        return icon_nuklear;
    if (kstrcmp(name, "Piano") == 0)
        return icon_piano;
    if (kstrcmp(name, "Quake 2") == 0)
        return icon_quake2;
    return 0;
}

/* Decode a shortcut's PNG to raw 32x32 RGBA pixels. Returns a heap buffer
 * that lives until reboot, or 0 on any failure (missing file, undecodable
 * image, exhausted heap); the caller then uses icon_embedded. Keeping the
 * PNG's own colors (instead of mapping to the 16-entry icon palette) is
 * what makes icons distinguishable on a true-color desktop; the 8-bit mode
 * quantizes back through icon_nearest at draw time. */
static const uint8_t *icon_decode(const char *path) {
    int w, h, ch, x, y;
    unsigned char *img;
    uint8_t *out;
    if (!path || !path[0])
        return 0;
    img = stbi_load_file(path, &w, &h, &ch, 4);
    if (!img)
        return 0;
    if (w <= 0 || h <= 0) {
        stbi_image_free(img);
        return 0;
    }
    out = kmalloc(ICON_W * ICON_H * 4);
    if (!out) {
        stbi_image_free(img);
        return 0;
    }
    for (y = 0; y < ICON_H; y++) {
        int sy = y * h / ICON_H;
        for (x = 0; x < ICON_W; x++) {
            int sx = x * w / ICON_W;
            unsigned char *px = img + ((sy * w) + sx) * 4;
            uint8_t *dst = out + ((y * ICON_W) + x) * 4;
            dst[0] = px[0]; dst[1] = px[1]; dst[2] = px[2]; dst[3] = px[3];
        }
    }
    stbi_image_free(img);
    return out;
}

/* Expand an embedded index icon (desktop_icons.h, transparent 0) to RGBA
 * through the icon palette, so fallback art follows the same draw path as
 * decoded PNGs. Returns a heap buffer or 0 when exhausted. */
static const uint8_t *icon_embedded_rgba(const uint8_t *idx) {
    uint8_t *out;
    int i;
    if (!idx) return 0;
    out = kmalloc(ICON_W * ICON_H * 4);
    if (!out) return 0;
    for (i = 0; i < ICON_W * ICON_H; i++) {
        uint8_t c = idx[i];
        uint8_t *dst = out + i * 4;
        if (c == 0) {
            dst[0] = dst[1] = dst[2] = dst[3] = 0;
        } else {
            if (c >= ICON_PAL_SIZE) c = ICON_PAL_SIZE - 1;
            dst[0] = icon_pal[c][0];
            dst[1] = icon_pal[c][1];
            dst[2] = icon_pal[c][2];
            dst[3] = 255;
        }
    }
    return out;
}

/* Width of the longest shortcut label in pixels (cached after load). Labels
 * are centred under their icon and a dock column must be wide enough for one,
 * or neighbouring labels overlap. */
static int dock_cell_w;

/* Width (px) one label occupies (FONT_W per character). */
static int dock_label_px(const struct desktop_shortcut *sc) {
    return (int)kstrlen(sc->name) * FONT_W;
}

/* Dock layout: one centred row just above the taskbar. Every shortcut owns a
 * column `dock_cell_w` wide (enough for its label), the icon is centred in the
 * column and the label centred beneath it, so long names never collide with a
 * neighbour. Recomputed on every draw/hit-test from fb_width/fb_height so a
 * resolution change never leaves stale coordinates behind. */
static void shortcuts_layout(void) {
    int dock_w, x0, y0, dock_h, cell_left, i;
    if (shortcut_count <= 0) return;
    dock_w = shortcut_count * dock_cell_w + 2 * DOCK_PAD_X;
    dock_h = ICON_H + DOCK_LABEL_GAP + ICON_LABEL_H + 2 * DOCK_PAD_Y;
    x0 = (fb_width - dock_w) / 2;
    if (x0 < 0) x0 = 0;
    y0 = fb_height - TASKBAR_H - DOCK_GAP - dock_h;
    if (y0 < 0) y0 = 0;
    cell_left = x0 + DOCK_PAD_X;
    for (i = 0; i < shortcut_count; i++) {
        shortcuts[i].x = cell_left + (dock_cell_w - ICON_W) / 2;
        shortcuts[i].y = y0 + DOCK_PAD_Y;
        cell_left += dock_cell_w;
    }
}

/* Left edge of shortcut i's column (used to centre its label under the icon). */
static int shortcut_cell_left(int i) {
    int dock_w = shortcut_count * dock_cell_w + 2 * DOCK_PAD_X;
    int x0 = (fb_width - dock_w) / 2;
    if (x0 < 0) x0 = 0;
    return x0 + DOCK_PAD_X + i * dock_cell_w;
}

void desktop_shortcuts_load(void) {
    char line[128];
    char name[SHORTCUT_NAME_LEN];
    char path[SHORTCUT_PATH_LEN];
    char cmd[SHORTCUT_CMD_LEN];

    if (shortcuts_loaded) return;
    shortcuts_loaded = 1;
    shortcut_count = 0;

    KFILE *f = kfopen("etc/shortcuts", "r");
    if (!f) return;

    while (kfgets(line, sizeof(line), f) && shortcut_count < MAX_SHORTCUTS) {
        /* Skip comments and empty lines. */
        if (line[0] == '#' || line[0] == '\n' || line[0] == '\r' || line[0] == '\0')
            continue;
        if (!pipe_field(line, 0, name, sizeof(name))) continue;
        if (!pipe_field(line, 1, path, sizeof(path))) continue;
        if (!pipe_field(line, 2, cmd, sizeof(cmd))) continue;

        struct desktop_shortcut *sc = &shortcuts[shortcut_count];
        kmemset(sc, 0, sizeof(*sc));
        /* Copy name (truncated). */
        for (int i = 0; i < SHORTCUT_NAME_LEN - 1 && name[i]; i++)
            sc->name[i] = name[i];
        /* Copy command. */
        for (int i = 0; i < SHORTCUT_CMD_LEN - 1 && cmd[i]; i++)
            sc->cmd[i] = cmd[i];
        sc->w = ICON_W;
        sc->h = ICON_H;

        /* PNG first (custom art from tools/gen_desktop_pngs.py), embedded
         * pixel data as fallback when the file is missing or undecodable. */
        sc->pixels = icon_decode(path);
        if (!sc->pixels)
            sc->pixels = icon_embedded_rgba(icon_embedded(name));

        shortcut_count++;
    }
    kfclose(f);

    /* Cache the widest cell after the names are known, then lay the dock out.
     * A label is the widest thing in a column, so the column is sized to hold
     * it (never narrower than the icon) and labels cannot overlap. */
    dock_cell_w = ICON_W;
    for (int i = 0; i < shortcut_count; i++) {
        int pw = dock_label_px(&shortcuts[i]) + 6;
        if (pw > dock_cell_w) dock_cell_w = pw;
    }
    shortcuts_layout();
}

/* Blit one shortcut icon scaled to dw x dh at (dx, dy), nearest
 * neighbour from the cached 32x32 RGBA source. Alpha below 128 stays
 * transparent; 8-bit mode quantizes through the icon palette. */
static void shortcut_draw_scaled(const struct desktop_shortcut *sc,
                                 int dx, int dy, int dw, int dh) {
    int ox, oy;
    if (!sc->pixels || dw <= 0 || dh <= 0) return;
    for (oy = 0; oy < dh; oy++) {
        int sy = oy * ICON_H / dh;
        for (ox = 0; ox < dw; ox++) {
            int sx = ox * ICON_W / dw;
            const uint8_t *sp = sc->pixels + ((sy * ICON_W) + sx) * 4;
            if (sp[3] < 128) continue;
            if (fb_bpp == 8)
                vga_fb_pixel(dx + ox, dy + oy,
                             (uint8_t)(ICON_PAL_BASE +
                                       icon_nearest(sp[0], sp[1], sp[2])));
            else
                fb_write_packed(dx + ox, dy + oy,
                                ((unsigned long)sp[0] << 16) |
                                ((unsigned long)sp[1] << 8) |
                                (unsigned long)sp[2]);
        }
    }
}

/* Index of the shortcut column under (mx, my), or -1. Same column bounds
 * as the click hit test, so hover and click always agree. */
static int dock_hover_index(int mx, int my) {
    int i;
    if (!mouse_state.present) return -1;
    for (i = 0; i < shortcut_count; i++) {
        struct desktop_shortcut *sc = &shortcuts[i];
        int cl = shortcut_cell_left(i);
        if (mx >= cl && mx < cl + dock_cell_w &&
            my >= sc->y && my < sc->y + ICON_H + ICON_LABEL_H)
            return i;
    }
    return -1;
}

/* Last hover index the dock was painted for. A full desktop paint resets
 * it so the next tick repaints the strip from fresh pixels. */
static int dock_last_hover = -2;

/* Click bounce (Mac style): index of the hopping icon and the sys_ticks
 * value of its click. The icon lifts off its slot on decaying parabolic
 * hops for DOCK_BOUNCE_TICKS while its program launches. -1 when idle. */
static int dock_bounce_idx = -1;
static unsigned long dock_bounce_start;
/* Serial-observable bounce proof: arms since boot and strip repaints while
 * live (reported by `wm state`, the same surface as fx melts). */
static unsigned long dock_bounce_kicks;
static unsigned long dock_bounce_paints;

void dock_bounce_counts(unsigned long *kicks, unsigned long *paints) {
    if (kicks) *kicks = dock_bounce_kicks;
    if (paints) *paints = dock_bounce_paints;
}

/* Rising edges seen by the tick (anywhere, before dispatch). Reported in
 * `wm state` beside the bounce counters to split "click never arrived"
 * from "click missed the dock". */
static unsigned long dock_click_edges;

void dock_click_count(unsigned long *edges) {
    if (edges) *edges = dock_click_edges;
}

/* Ticks elapsed since the bounce click, capped so the subtraction can
 * never wrap on a late read. */
static unsigned long dock_bounce_elapsed(void) {
    unsigned long now = (unsigned long)sys_ticks;
    unsigned long el = now - dock_bounce_start;
    if (el > DOCK_BOUNCE_TICKS) el = DOCK_BOUNCE_TICKS;
    return el;
}

/* 1 while the bounce animation is live, 0 once it expired or is idle. */
static int dock_bounce_live(void) {
    if (dock_bounce_idx < 0 || dock_bounce_idx >= shortcut_count) return 0;
    return (unsigned long)sys_ticks - dock_bounce_start < DOCK_BOUNCE_TICKS;
}

/* Bounce lift in pixels for elapsed 100 Hz ticks: two full parabolic
 * hops (peaks 24/14 px over 45 ticks each, total 0.9 s). Integer-only:
 * h = H - H*d*d/hw*hw around each hop centre, so both hops start and
 * land at exactly 0 and the tail joins the slot with no step. */
static int dock_bounce_height(unsigned long t) {
    long d;
    if (t < 45) {
        d = (long)t - 22;
        return 24 - (int)(24 * d * d / (22 * 22));
    }
    if (t < DOCK_BOUNCE_TICKS) {
        d = (long)t - 67;
        return 14 - (int)(14 * d * d / (22 * 22));
    }
    return 0;
}

/* Last bounce height painted (-1 = none). The idle tick runs far faster
 * than the 100 Hz height clock, so most ticks would erase+redraw an
 * identical strip (a wallpaper flash reads as flicker). Gated repaints
 * only on a new height. Hover stability candidate below: a pointer
 * resting on a cell edge jitters ±1 count between neighbours, and
 * repainting every flip flashes the strip the same way. */
static int dock_last_bounce_h = -1;
static int dock_hover_cand = -2;
static int dock_hover_n = 0;

/* Arm the bounce for the clicked icon. Called on the click edge; the
 * launch stays pending until the hops finish, so the animation paints
 * before desktop_launch blocks the tick (a synchronous launch in the
 * same tick would never show a frame). Pretends height 0 already
 * painted so the first idle tick does not flash an identical strip. */
static void dock_bounce_kick(int idx) {
    if (idx < 0 || idx >= shortcut_count) return;
    dock_bounce_idx = idx;
    dock_bounce_start = (unsigned long)sys_ticks;
    dock_bounce_kicks++;
    dock_last_bounce_h = 0;
}

/* Deferred dock launch: the shortcut command waits here while its icon
 * hops, then the tick fires it once the bounce expires. */
static char dock_pending_cmd[128];
static int dock_pending_len;

int dock_pending_active(void) {
    return dock_pending_len > 0;
}

/* Paint every shortcut icon and label at the given hover sizes. Shared by
 * the full desktop paint and the flicker-free hover repaint, so the two
 * can never diverge. Growth is bottom-aligned on the slot with no
 * relayout: it overlays upward and the strip erase restores it. */
static void dock_paint_icons(int hover) {
    int i;
    for (i = 0; i < shortcut_count; i++) {
        struct desktop_shortcut *sc = &shortcuts[i];
        int cl = shortcut_cell_left(i);
        int dw = ICON_W, dh = ICON_H;
        int dx, dy;
        if (i == hover) {
            dw = DOCK_MAG_W;
            dh = DOCK_MAG_H;
        } else if (hover >= 0 && (i == hover - 1 || i == hover + 1)) {
            dw = DOCK_NEAR_W;
            dh = DOCK_NEAR_H;
        }
        dx = cl + (dock_cell_w - dw) / 2;
        dy = sc->y + ICON_H - dh;
        /* A bouncing icon lifts off its slot on top of any hover size. */
        if (i == dock_bounce_idx && dock_bounce_live())
            dy -= dock_bounce_height(dock_bounce_elapsed());
        if (sc->pixels) {
            shortcut_draw_scaled(sc, dx, dy, dw, dh);
        } else {
            /* No icon: draw a placeholder rectangle. */
            vga_fb_rect(sc->x, sc->y, ICON_W, ICON_H, COL_SHADOW);
        }
        /* Draw label centred in its own column, on the dock backing, so it
         * never runs into a neighbour's label. */
        {
            int label_w = dock_label_px(sc);
            int lx = cl + (dock_cell_w - label_w) / 2;
            text_px(lx, sc->y + ICON_H + DOCK_LABEL_GAP, sc->name,
                    COL_TASKBAR_TXT, COL_SHADOW);
        }
    }
}

void desktop_shortcuts_draw(void) {
    int dock_w, dock_h, x0, y0, hover, yy, xx;
    shortcuts_layout();
    if (shortcut_count <= 0) return;
    /* Dock bar: crystal backing over the wallpaper, Mac style. Only every
     * other pixel is painted, so the wallpaper shows through the bar. */
    dock_w = shortcut_count * dock_cell_w + 2 * DOCK_PAD_X;
    dock_h = ICON_H + DOCK_LABEL_GAP + ICON_LABEL_H + 2 * DOCK_PAD_Y;
    x0 = (fb_width - dock_w) / 2;
    if (x0 < 0) x0 = 0;
    y0 = fb_height - TASKBAR_H - DOCK_GAP - dock_h;
    if (y0 < 0) y0 = 0;
    for (yy = y0; yy < y0 + dock_h; yy++)
        for (xx = x0; xx < x0 + dock_w; xx++)
            if (((xx + yy) & (DOCK_CRYSTAL_STEP - 1)) == 0)
                vga_fb_pixel(xx, yy, COL_SHADOW);
    vga_fb_rect(x0, y0, dock_w, 1, COL_BORDER);
    vga_fb_rect(x0, y0 + dock_h - 1, dock_w, 1, COL_BORDER);
    vga_fb_rect(x0, y0, 1, dock_h, COL_BORDER);
    vga_fb_rect(x0 + dock_w - 1, y0, 1, dock_h, COL_BORDER);
    hover = dock_hover_index(mouse_state.x, mouse_state.y);
    dock_paint_icons(hover);
    dock_last_hover = hover;
}

/* Paint one wallpaper rectangle from the cache (solid fill when the cache
 * is absent or stale): the strip-erase primitive for the hover repaint. */
static void wallpaper_rect(int x0, int y0, int w, int h) {
    int y;
    unsigned long row;
    if (x0 < 0) { w += x0; x0 = 0; }
    if (y0 < 0) { h += y0; y0 = 0; }
    if (w <= 0 || h <= 0) return;
    if (x0 + w > fb_width) w = fb_width - x0;
    if (y0 + h > fb_height) h = fb_height - y0;
    if (w <= 0 || h <= 0) return;
    if (!wallpaper_usable()) {
        vga_fb_rect(x0, y0, w, h, COL_BG);
        return;
    }
    row = (unsigned long)fb_width * (unsigned long)wall_bpx;
    for (y = 0; y < h; y++)
        fb_copy_bytes(FBT + (unsigned long)(y0 + y) * (unsigned long)fb_pitch +
                          (unsigned long)x0 * (unsigned long)wall_bpx,
                      wall_native + (unsigned long)(y0 + y) * row +
                          (unsigned long)x0 * (unsigned long)wall_bpx,
                      (unsigned long)w * (unsigned long)wall_bpx);
}

/* Hover repaint without the fullscreen flash: erase only the dock strip
 * (bar plus the overflow the magnified icons rise into), restore the
 * crystal and repaint the icons at the new hover sizes. No clear, no
 * wallpaper rewrite, no terminal re-render, so there is no black frame;
 * the strip is cheap (a few rows) and runs once per hover crossing.
 * Terminals paint over the dock on a full desktop paint, so a terminal
 * dragged across the dock is overpainted here until its next render;
 * that drag case is rare and heals on the next paint. Fullscreen
 * terminals hide the dock, so the tick never calls this there. */
static void dock_paint_hover(int hover) {
    int dock_w, dock_h, x0, y0, y_top, yy, xx;
    int bouncing = dock_bounce_live();
    shortcuts_layout();
    if (shortcut_count <= 0) return;
    dock_w = shortcut_count * dock_cell_w + 2 * DOCK_PAD_X;
    dock_h = ICON_H + DOCK_LABEL_GAP + ICON_LABEL_H + 2 * DOCK_PAD_Y;
    x0 = (fb_width - dock_w) / 2;
    if (x0 < 0) x0 = 0;
    y0 = fb_height - TASKBAR_H - DOCK_GAP - dock_h;
    if (y0 < 0) y0 = 0;
    /* The strip erase covers the magnified overflow plus the full bounce
     * lift above the slot, so a hopping icon never smears. */
    y_top = y0 - (DOCK_MAG_H - ICON_H) - DOCK_BOUNCE_H - 2;
    if (y_top < 0) y_top = 0;
    wallpaper_rect(x0, y_top, dock_w, y0 + dock_h - y_top);
    for (yy = y0; yy < y0 + dock_h; yy++)
        for (xx = x0; xx < x0 + dock_w; xx++)
            if (((xx + yy) & (DOCK_CRYSTAL_STEP - 1)) == 0)
                vga_fb_pixel(xx, yy, COL_SHADOW);
    vga_fb_rect(x0, y0, dock_w, 1, COL_BORDER);
    vga_fb_rect(x0, y0 + dock_h - 1, dock_w, 1, COL_BORDER);
    vga_fb_rect(x0, y0, 1, dock_h, COL_BORDER);
    vga_fb_rect(x0 + dock_w - 1, y0, 1, dock_h, COL_BORDER);
    dock_paint_icons(hover);
    dock_last_hover = hover;
    if (bouncing) dock_bounce_paints++;
    cursor_note_repaint(x0, y_top, dock_w, y0 + dock_h - y_top);
}

/* Icon for the taskbar running-app button. First the running program via
 * its launch command (config-driven, covers apps that never set a window
 * title); then the window title against the shortcut name as fallback
 * (case-insensitive, "*" suffix ignored). Text-only button when nothing
 * matches. Load is idempotent, so a click before the first desktop paint
 * still resolves. */
static const uint8_t *gfx_task_icon(void) {
    const uint8_t *p = gfx_prog_icon();
    int i, k;
    if (p) return p;
    desktop_shortcuts_load();
    for (i = 0; i < shortcut_count; i++) {
        const char *a = shortcuts[i].name;
        const char *b = gfx_win_title;
        if (!a[0] || !b) continue;
        for (k = 0; ; k++) {
            int ca = a[k], cb = b[k];
            if (ca >= 'A' && ca <= 'Z') ca += 32;
            if (cb >= 'A' && cb <= 'Z') cb += 32;
            if (ca == 0 && (cb == 0 || cb == ' ' || cb == '*'))
                return shortcuts[i].pixels;
            if (ca != cb) break;
        }
    }
    return 0;
}

const char *desktop_shortcuts_hit_test(int mx, int my) {
    shortcuts_layout();
    for (int i = 0; i < shortcut_count; i++) {
        struct desktop_shortcut *sc = &shortcuts[i];
        int cl = shortcut_cell_left(i);
        if (mx >= cl && mx < cl + dock_cell_w &&
            my >= sc->y && my < sc->y + ICON_H + ICON_LABEL_H) {
            return sc->cmd;
        }
    }
    return 0;
}

/** Docstring: Focus the topmost window at point, paint order. */
static int mouse_focus_topmost(int mx, int my)
{
    int f;
    int before;
    if (gfx_hit(mx, my)) {
        if (wm_focus == WM_FOCUS_GFX) return 0;
        before = wm_focus;
        vga_fb_focus_id(WM_FOCUS_GFX);
        wm_emit_focus_moved(before, WM_FOCUS_SRC_POINTER);
        return 1;
    }
    for (f = 0; f < wm_nterms; f++) {
        if (!twins[f].present) continue;
        if (tw_hit(f, mx, my)) {
            if (f == wm_focus) return 0;
            before = wm_focus;
            tw_select(f);
            vga_fb_draw_desktop();
            wm_emit_focus_moved(before, WM_FOCUS_SRC_POINTER);
            return 1;
        }
    }
    return 0;
}

/** Docstring: Scroll the focused terminal from a wheel sample. */
static void mouse_apply_wheel(int wheel, int step)
{
    int tr;
    int max_off;
    if (wheel == 0 || term_minimized || wm_focus == WM_FOCUS_GFX) return;
    tr = total_rows();
    max_off = tr > term_rows ? tr - term_rows : 0;
    if (wheel > 0)
        disp_off += step;
    else
        disp_off -= step;
    if (disp_off > max_off) disp_off = max_off;
    if (disp_off < 0) disp_off = 0;
    term_render();
    if (cursor_over(term_px_x, term_content_y(), term_px_w, term_px_h))
        cursor_invalidate();
}

/** Docstring: Title-bar drag of the graphics window. Redraws on every
 * offset change and once more on release, so the persistent layer moves
 * with the pointer and no duplicated copy survives the drop. Grabbing a
 * tiled window floats it at native size under the pointer (the grab point
 * keeps its relative position along the title); a fullscreen window has
 * no title and never drags. */
static void mouse_drag_gfx(const wm_geom_config_t *gcfg, int mx, int my)
{
    int gx, gy, gw;
    int was = wm_gdrag;
    int old_ox = gfx_win_ox, old_oy = gfx_win_oy;
    wm_gfxview_rect_t ff;
    if (!vga_fb_gfx_mode || wm_skip_drag || gfx_hidden || !gfx_view_valid ||
        gfx_view_mode == WM_GFXVIEW_FULL || gfx_view.title_h <= 0) {
        wm_gdrag = 0;
        if (was) vga_fb_draw_desktop();
        return;
    }
    gx = gfx_view.frame.x;
    gy = gfx_view.frame.y;
    gw = gfx_view.frame.w;
    if (wm_hit_title_bar(gcfg, gx, gy, gw, mx, my)) {
        if (mouse_state.buttons & 1) {
            if (!wm_gdrag) {
                wm_gdrag = 1;
                wm_ggx = mx - gx;
                wm_ggy = my - gy;
                if (gfx_view_mode != WM_GFXVIEW_FLOAT && gfx_float_frame(&ff) && gw > 0) {
                    wm_ggx = (int)(((long)(mx - gx) * (long)ff.w) / (long)gw);
                    gfx_view_mode = WM_GFXVIEW_FLOAT;
                    gfx_view_back = WM_GFXVIEW_FLOAT;
                    gfx_frame_dirty = 1;
                    old_ox = old_oy = 0x7FFFFFFF;
                }
            }
        } else {
            wm_gdrag = 0;
        }
    } else if (!(mouse_state.buttons & 1)) {
        wm_gdrag = 0;
    }
    if (wm_gdrag) {
        int cx, cy;
        if (!gfx_float_frame(&ff)) return;
        cx = (fb_width - ff.w) / 2;
        cy = (fb_height - ff.h) / 2;
        gfx_win_ox = mx - wm_ggx - cx;
        gfx_win_oy = my - wm_ggy - cy;
        if (gfx_win_ox != old_ox || gfx_win_oy != old_oy)
            vga_fb_draw_desktop();
    } else if (was) {
        vga_fb_draw_desktop();
    }
}

/** Docstring: Title-bar drag of the focused terminal window. The motion
 * path already repaints per step; the release edge repaints once more so
 * the final coordinates settle with no duplicated copy left behind. */
static void mouse_drag_term(const wm_geom_config_t *gcfg, int win_w, int mx, int my, int gfx_cursor)
{
    int in_title;
    int was = wm_dragging;
    if (term_fullscreen || term_minimized || wm_skip_drag) return;
    in_title = wm_hit_title_bar(gcfg, term_px_x, term_px_y, win_w, mx, my);
    if (mouse_state.buttons & 1) {
        if (!wm_dragging && in_title) {
            wm_dragging = 1;
            wm_grab_cx = (mx - term_px_x) / FONT_W;
        }
    } else {
        wm_dragging = 0;
    }
    if (wm_dragging) {
        vga_fb_drag_terminal(mx, my, wm_grab_cx);
        if (!gfx_cursor) cursor_invalidate();
    } else if (was) {
        vga_fb_draw_desktop();
    }
}

/** Docstring: Scrollbar drag of the focused terminal window. */
static void mouse_scrollbar(const wm_geom_config_t *gcfg, int mx, int my)
{
    wm_rect_t sb;
    int sy, sh, total, visible, max_off, new_off;
    if (!(mouse_state.buttons & 1) || wm_dragging || term_minimized) return;
    sb = wm_scrollbar_rect(gcfg, term_px_x, term_px_y, term_px_w, term_px_h);
    if (!wm_rect_contains(&sb, mx, my)) return;
    sy = term_content_y();
    sh = term_px_h;
    total = total_rows();
    visible = term_rows;
    if (total <= visible || sh <= 0) return;
    max_off = total - visible;
    new_off = ((sy + sh - my) * max_off) / sh;
    if (new_off < 0) new_off = 0;
    if (new_off > max_off) new_off = max_off;
    disp_off = new_off;
    term_render();
    if (cursor_over(term_px_x, term_content_y(), term_px_w, term_px_h))
        cursor_invalidate();
}

/** Docstring: Drive the desktop from a kernel wait loop. While the shell
 * waits for a foreground process nothing else runs vga_fb_mouse_tick: the
 * timer ISR drives it only for the pid-0 exec frame (user_program_active)
 * and the shell's input loop is not running, so the pointer, taskbar and
 * window controls froze for the whole run. The loop calls this between
 * yields; it ticks at the ISR's cadence and stands down whenever the ISR
 * owns the desktop, so the two never run the tick concurrently. */
void vga_fb_wait_tick(void) {
    static unsigned long last;
    if (!vga_fb_active || user_program_active) return;
    if ((unsigned long)sys_ticks - last < DESKTOP_TICK_INTERVAL) return;
    last = (unsigned long)sys_ticks;
    vga_fb_mouse_tick();
}

/** Docstring: Per-tick mouse dispatch over unified geometry and events. */
void vga_fb_mouse_tick(void) {
    static unsigned tb_prev_buttons;
    wm_geom_config_t gcfg = wm_geom_cfg();
    wm_event_config_t ecfg = wm_event_cfg();
    int mx, my;
    int win_w = term_px_w + SCROLLBAR_W;
    int gfx_cursor;

    if (!mouse_state.present) return;

    /* Single cursor owner: while a graphics program owns the display the
     * present path (blit_gfx_buf) is the sole cursor painter. The tick
     * used to share the sprite state with it and raced every present
     * (~60fps vs 25Hz): stale restores painted trails and flicker, worst
     * on the title-bar hitboxes the tick touches each pass. So in gfx
     * mode the tick never draws or restores the cursor and only
     * invalidates it
     * across real repaints (draw_desktop/taskbar_render clear it
     * themselves); anywhere else the invalidation is gated off. */
    gfx_cursor = vga_fb_gfx_mode;
    gfx_cursor_follow_idle();

    /* A fullscreen graphics window owns every pixel and every click: no
     * taskbar widget, dock icon, terminal title or scrollbar lies under
     * the pointer, so a click only (re)focuses the app and nothing else
     * in the desktop may paint. */
    if (gfx_covers_screen()) {
        if (wm_is_click_edge(&ecfg, (int)tb_prev_buttons, mouse_state.buttons)) {
            dock_click_edges++;
            mouse_focus_topmost(mouse_state.x, mouse_state.y);
        }
        tb_prev_buttons = (unsigned)(mouse_state.buttons & 1);
        wm_skip_drag = (mouse_state.buttons & 1) ? 1 : 0;
        wm_dragging = 0;
        wm_gdrag = 0;
        wm_clamp_point(&mouse_state.x, &mouse_state.y, fb_width, fb_height);
        return;
    }

    taskbar_tick();
    if (wm_is_click_edge(&ecfg, (int)tb_prev_buttons, mouse_state.buttons)) {
        dock_click_edges++;
        taskbar_handle_click(mouse_state.x, mouse_state.y);
        if (wm_button_click(mouse_state.x, mouse_state.y)) {
            tb_prev_buttons = (unsigned)(mouse_state.buttons & 1);
            if (!gfx_cursor) cursor_invalidate();
            wm_skip_drag = 1;
            return;
        }
        /* Click-to-focus in paint order through one dispatcher: the
         * graphics window composites on top of the terminals, so it owns
         * overlapping clicks. Testing terminals first stole gfx clicks
         * (wrong focus + swallowed press: the unfocused app reads -1
         * from SYS_MOUSE, so the user paid one click to focus the
         * terminal, one to focus gfx, one to act). Same select path as
         * Alt-Tab, so mouse and key agree. */
        if (mouse_focus_topmost(mouse_state.x, mouse_state.y)) {
            tb_prev_buttons = (unsigned)(mouse_state.buttons & 1);
            wm_skip_drag = 1;
            return;
        }
        const char *cmd = desktop_shortcuts_hit_test(mouse_state.x, mouse_state.y);
        if (cmd) {
            /* Mac bounce: arm the hops and defer the launch until they
             * finish, so the strip paints at tick rate first. */
            int idx = dock_hover_index(mouse_state.x, mouse_state.y);
            unsigned i = 0;
            dock_bounce_kick(idx);
            while (cmd[i] && i < sizeof(dock_pending_cmd) - 1) {
                dock_pending_cmd[i] = cmd[i];
                i++;
            }
            dock_pending_cmd[i] = 0;
            dock_pending_len = (int)i;
        }
    }
    if (!(mouse_state.buttons & 1)) wm_skip_drag = 0;
    tb_prev_buttons = (unsigned)(mouse_state.buttons & 1);

    /* The wheel belongs to whoever holds the focus: a focused graphics
     * app reads it through SYS_MOUSE, so the tick must leave it alone
     * (consuming it here silently ate vedit's and the file browser's
     * wheel scroll whenever a tick landed between two app polls). */
    if (!vga_fb_gfx_mode || wm_focus != WM_FOCUS_GFX) {
        int wheel;
        irqflags_t flags = spin_save_irq();
        wheel = mouse_state.wheel;
        mouse_state.wheel = 0;
        spin_restore_irq(flags);
        mouse_apply_wheel(wheel, ecfg.wheel_step);
    }

    mx = mouse_state.x;
    my = mouse_state.y;

    mouse_drag_gfx(&gcfg, mx, my);
    if (wm_gdrag) {
        mx = mouse_state.x;
        my = mouse_state.y;
    }

    mouse_drag_term(&gcfg, win_w, mx, my, gfx_cursor);
    if (wm_dragging) {
        mx = mouse_state.x;
        my = mouse_state.y;
    }

    mouse_scrollbar(&gcfg, mx, my);

    wm_clamp_point(&mouse_state.x, &mouse_state.y, fb_width, fb_height);

    mx = mouse_state.x;
    my = mouse_state.y;

    /* Dock magnify lives in the dock paint, which a full desktop paint
     * runs only occasionally, so the tick repaints the dock strip itself:
     * strip-only, no clear, no wallpaper rewrite, zero cost while hovering
     * still. Flicker discipline: a repaint is an erase (wallpaper flash)
     * plus a redraw, so the tick repaints only on a real change — a new
     * bounce height, or a hover that persisted two consecutive ticks
     * (a pointer on a cell edge jitters between neighbours). The height
     * decision and its paint run with the timer IRQ held: the 100 Hz ISR
     * advances sys_ticks between the check and the paint otherwise, and
     * every torn read doubles into a redundant flash. A live bounce
     * ignores the button state (the arming press is consumed) and settles
     * once on expiry, so the hops animate and the icon lands back in its
     * slot. The deferred launch fires after the IRQ restore: it blocks
     * running a program and must never hold the IRQ off. */
    if (!gfx_cursor && !term_fullscreen && !wm_dragging && !wm_gdrag) {
        int hover = dock_hover_index(mx, my);
        int bounce;
        int stable;
        int fire = 0;
        char launch[128];
        irqflags_t dflags;
        launch[0] = 0;
        dflags = spin_save_irq();
        bounce = dock_bounce_live();
        if (hover != dock_hover_cand) {
            dock_hover_cand = hover;
            dock_hover_n = 0;
        } else if (dock_hover_n < 2) {
            dock_hover_n++;
        }
        stable = (dock_hover_n >= 1);
        if (bounce) {
            int h = dock_bounce_height(dock_bounce_elapsed());
            if (h != dock_last_bounce_h ||
                (stable && hover != dock_last_hover)) {
                dock_paint_hover(hover);
                dock_last_bounce_h = h;
            }
        } else if (stable && hover != dock_last_hover &&
                   !(mouse_state.buttons & 1)) {
            dock_paint_hover(hover);
            dock_last_bounce_h = -1;
        } else if (dock_bounce_idx >= 0 &&
                 (unsigned long)sys_ticks - dock_bounce_start >= DOCK_BOUNCE_TICKS) {
            unsigned i = 0;
            dock_bounce_idx = -1;
            dock_last_bounce_h = -1;
            dock_paint_hover(hover);
            if (dock_pending_len > 0) {
                while (dock_pending_cmd[i] && i < sizeof(launch) - 1) {
                    launch[i] = dock_pending_cmd[i];
                    i++;
                }
                launch[i] = 0;
                dock_pending_len = 0;
                dock_pending_cmd[0] = 0;
                fire = 1;
            }
        }
        spin_restore_irq(dflags);
        if (fire) {
            desktop_launch(launch);
            return;
        }
    } else if (dock_bounce_idx >= 0 &&
               (unsigned long)sys_ticks - dock_bounce_start >= DOCK_BOUNCE_TICKS) {
        dock_bounce_idx = -1;
        if (dock_pending_len > 0) {
            char launch[128];
            unsigned i = 0;
            while (dock_pending_cmd[i] && i < sizeof(launch) - 1) {
                launch[i] = dock_pending_cmd[i];
                i++;
            }
            launch[i] = 0;
            dock_pending_len = 0;
            dock_pending_cmd[0] = 0;
            desktop_launch(launch);
            return;
        }
    }

    /* Erase old cursor and draw new one. Skipped wholesale in gfx mode:
     * the present path owns the cursor there (see above). */
    if (gfx_cursor) return;
    cursor_move(mx, my);
}

void vga_fb_mouse_init(void) {
    mouse_state.x = fb_width / 2;
    mouse_state.y = fb_height / 2;
    mouse_state.buttons = 0;
    mouse_state.dx = 0;
    mouse_state.dy = 0;
    mouse_state.wheel = 0;
    mouse_state.present = 0;
    cursor_invalidate();
    lg_head = lg_tail = lg_count = 0;
    act_len = 0;
    act[0] = '\0';
    disp_off = 0;
    wm_inited = 0;
    wm_nterms = 1;
    wm_focus = 0;
    wm_term = 0;
    dock_bounce_idx = -1;
    dock_bounce_start = 0;
    dock_bounce_kicks = 0;
    dock_bounce_paints = 0;
    dock_last_bounce_h = -1;
    dock_hover_cand = -2;
    dock_hover_n = 0;
    dock_pending_len = 0;
    dock_pending_cmd[0] = 0;
}

void vga_fb_init(void) {
    int i;
    lg = (char (*)[SB_LINE_MAX])kmalloc(SB_MAX_LINES * SB_LINE_MAX);
    if (!lg) kprintf("vga: no scrollback ring (out of memory)\n");
    /* Gray ramp until the first graphics program sets its palette. */
    for (i = 0; i < 256; i++) {
        gfx_pal[i * 3 + 0] = (unsigned char)i;
        gfx_pal[i * 3 + 1] = (unsigned char)i;
        gfx_pal[i * 3 + 2] = (unsigned char)i;
    }
    vga_fb_active = 1;
    vga_fb_mouse_init();
    /* Boot melt: the desktop scrolls down over black like a DOOM level
     * intro. The fresh desktop is snapshotted, the screen cleared, and
     * the snapshot melted back over black. OOM degrades to a plain draw. */
    if (vga_fx_enabled()) {
        unsigned int *newb;
        vga_fb_draw_desktop();
        newb = vga_fx_snap_rect(0, 0, fb_width, fb_height);
        if (newb) {
            vga_fb_clear();
            vga_fx_melt_from_black(0, 0, fb_width, fb_height, newb);
            vga_fx_free(newb);
            cursor_invalidate();
            return;
        }
    }
    vga_fb_draw_desktop();
}
