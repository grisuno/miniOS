/** platform_minios.c - MiniOS implementation of FreeDom's gui/platform.h.
 *
 * Contract: FreeDom spec/platform.md plus docs/spec/network.md (freedom-gui).
 * The NK RGB back-buffer (MINIOS_NK_W x MINIOS_NK_H, 3 bytes per pixel) is
 * the only surface a process owns, so the most recently opened window is the
 * visible one and receives input; the window manager draws the chrome and the
 * pointer. FreeDom paints into a heap ARGB32 Cairo surface; present converts
 * it to RGB and hands it to GFX_PRESENT. Every MiniOS call goes through the
 * Linux syscall ABI with numbers from minios_abi.h.
 */
#define _GNU_SOURCE

#include "platform.h"

#include <errno.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>

#include "minios_abi.h"
#include "ps2_keymap.h"

/** Granularity of the input wait loop, in milliseconds. */
#define FREEDOM_GUI_TICK_MS 10L
/** Keyboard bytes drained per input pump, so a stuck controller cannot spin. */
#define FREEDOM_GUI_KBD_DRAIN_MAX 64
/** GFX_SET_TITLE accepts at most this many bytes. */
#define FREEDOM_GUI_TITLE_MAX 31
/** Kernel clipboard capacity (kernel/clip.c CLIP_MAX); longer text is refused. */
#define FREEDOM_GUI_CLIP_MAX 4096L
/** malloc arenas: one, the main arena (see minios_malloc_single_arena). */
#define FREEDOM_GUI_MALLOC_ARENAS 1

/** SYS_MOUSE reply: x, y, buttons, wheel delta. */
#define FREEDOM_GUI_MOUSE_WORDS 4
#define FREEDOM_GUI_MOUSE_X 0
#define FREEDOM_GUI_MOUSE_Y 1
#define FREEDOM_GUI_MOUSE_BUTTONS 2
#define FREEDOM_GUI_MOUSE_WHEEL 3
/** SYS_MOUSE button bits in PF_BUTTON order. */
#define FREEDOM_GUI_BUTTONS 3
/** X11 keysym of F4: Alt+F4 asks the visible window to close. */
#define FREEDOM_GUI_KEY_F4 0xffc1u
/** RGB bytes per pixel of the NK RGB back-buffer. */
#define FREEDOM_GUI_RGB_BPP 3
/** SYS_FB_INFO fourth out-word value announcing the RGB back-buffer. */
#define FREEDOM_GUI_RGB_PRESENT 1

static const uint32_t freedom_gui_buttons[FREEDOM_GUI_BUTTONS] = {
    PF_BUTTON_LEFT, PF_BUTTON_RIGHT, PF_BUTTON_MIDDLE
};

struct pf_window {
    pf_display        *d;
    pf_window         *below;   /* the window shown again when this one closes */
    pf_window_handlers h;
    void              *ud;
    cairo_surface_t   *cairo;
    int                width, height;
    unsigned           states;  /* PF_STATE_* */
    int                pending; /* configure + ready not yet delivered */
    char               title[FREEDOM_GUI_TITLE_MAX + 1];
};

struct pf_display {
    pf_window *top;
    ps2_state  kbd;
    uint8_t    held[PS2_CODE_LIMIT];       /* key currently down */
    uint8_t    repeat_ok[PS2_CODE_LIMIT];  /* handler asked to repeat it */
    int        origin[2];                  /* content origin from GFX_PRESENT */
    int        ptr_inside;
    int        ptr_x, ptr_y;
    int        buttons;
    int        zoomed;
    int        frame_reported;
};

/* ---------------------------------------------------------------- syscalls */

static long sys_fb_info_rgb(int *rgb) {
    int w = 0, h = 0, pitch = 0;
    long ret;
    register long r10 __asm__("r10") = (long)rgb;
    __asm__ volatile("syscall"
                     : "=a"(ret)
                     : "a"((long)MINIOS_SYS_FB_INFO), "D"(&w), "S"(&h), "d"(&pitch), "r"(r10)
                     : "rcx", "r11", "memory");
    return ret;
}

static long now_ms(void) {
    return syscall(MINIOS_SYS_TIME, 0L);
}

static void set_title(const char *title) {
    char buf[FREEDOM_GUI_TITLE_MAX + 1];
    size_t n = strlen(title);
    if (n > FREEDOM_GUI_TITLE_MAX) {
        n = FREEDOM_GUI_TITLE_MAX;
        while (n > 0 && ((unsigned char)title[n] & 0xC0u) == 0x80u) n--;
    }
    memcpy(buf, title, n);
    buf[n] = '\0';
    (void)syscall(MINIOS_SYS_GFX_SET_TITLE, buf);
}

/* ---------------------------------------------------------------- display */

/* One malloc arena for every thread, set before main (and so before any
 * thread exists, in the browser and in every exec'd tab worker). glibc
 * gives each new thread arena a 64 MB address-space reservation; the
 * MiniOS user window leaves brk and mmap about 140 MB together, so a
 * single extra arena starved the browser until malloc returned NULL. */
__attribute__((constructor)) static void minios_malloc_single_arena(void) {
    (void)mallopt(M_ARENA_MAX, FREEDOM_GUI_MALLOC_ARENAS);
}

/* Run as a process, never in the shell's pid-0 exec frame: the browser's
 * fetch threads, renderer fork and /proc/self/exe tab workers need real
 * process semantics (minios_abi.h, process note). */
struct minios_process_note {
    uint32_t namesz;
    uint32_t descsz;
    uint32_t type;
    char     name[sizeof MINIOS_NOTE_NAME];
    uint32_t desc;
};

__attribute__((section(".note.minios.process"), used, aligned(4)))
static const struct minios_process_note freedom_gui_process_note = {
    sizeof MINIOS_NOTE_NAME, sizeof(uint32_t), MINIOS_NOTE_PROCESS, MINIOS_NOTE_NAME, 1u
};

pf_status pf_display_open(pf_display **out) {
    if (out == NULL) return PF_ERR_NULL_ARG;
    *out = NULL;
    int rgb = 0;
    if (sys_fb_info_rgb(&rgb) != 0 || rgb != FREEDOM_GUI_RGB_PRESENT) return PF_ERR_UNSUPPORTED;
    pf_display *d = (pf_display *)calloc(1, sizeof *d);
    if (d == NULL) return PF_ERR_OOM;
    ps2_init(&d->kbd);
    d->ptr_x = -1;
    d->ptr_y = -1;
    (void)syscall(MINIOS_SYS_VGA_MODE, 1L);
    (void)syscall(MINIOS_SYS_KBD_RAW, 1L);
    *out = d;
    return PF_OK;
}

void pf_display_close(pf_display *d) {
    if (d == NULL) return;
    while (d->top != NULL) pf_window_close(d->top);
    if (d->zoomed) (void)syscall(MINIOS_SYS_GFX_ZOOM, (long)MINIOS_GFX_ZOOM_WINDOWED);
    (void)syscall(MINIOS_SYS_KBD_RAW, 0L);
    (void)syscall(MINIOS_SYS_VGA_MODE, 0L);
    free(d);
}

void pf_display_flush(pf_display *d) {
    (void)d;
}

void pf_display_set_cursor(pf_display *d, pf_cursor c) {
    (void)d;
    (void)c;
}

/* ---------------------------------------------------------------- input */

static int deliver_pending(pf_display *d) {
    pf_window *w = d->top;
    if (w == NULL || !w->pending) return 0;
    w->pending = 0;
    if (w->h.decoration) w->h.decoration(w->ud, 0);
    if (w->h.configure) w->h.configure(w->ud, w->width, w->height, w->states);
    if (w->h.ready) w->h.ready(w->ud);
    return 1;
}

static void key_event(pf_display *d, const ps2_key *k, int kind) {
    if (k->code >= PS2_CODE_LIMIT) return;
    if (kind == PS2_EV_RELEASE) {
        d->held[k->code] = 0;
        d->repeat_ok[k->code] = 0;
        return;
    }
    pf_window *w = d->top;
    if (w == NULL) return;
    if (k->sym == FREEDOM_GUI_KEY_F4 && (k->mods & KE_MOD_ALT)) {
        if (w->h.close) w->h.close(w->ud);
        return;
    }
    int repeat = d->held[k->code];
    if (repeat && !d->repeat_ok[k->code]) return;
    d->held[k->code] = 1;
    if (w->h.key == NULL) { d->repeat_ok[k->code] = 0; return; }
    pf_key pk;
    memset(&pk, 0, sizeof pk);
    pk.sym = k->sym;
    memcpy(pk.text, k->text, sizeof k->text);
    pk.text_len = k->text_len;
    pk.mods = k->mods;
    pk.repeat = repeat;
    d->repeat_ok[k->code] = (uint8_t)(w->h.key(w->ud, &pk) != 0);
}

static int pump_keyboard(pf_display *d) {
    int handled = 0;
    for (int i = 0; i < FREEDOM_GUI_KBD_DRAIN_MAX; ++i) {
        long sc = syscall(MINIOS_SYS_KBD, 0L);
        if (sc < 0) break;
        ps2_key k;
        int kind = ps2_feed(&d->kbd, (uint8_t)sc, &k);
        if (kind == PS2_EV_NONE) continue;
        key_event(d, &k, kind);
        handled = 1;
    }
    return handled;
}

static int pump_mouse(pf_display *d) {
    int m[FREEDOM_GUI_MOUSE_WORDS] = { 0, 0, 0, 0 };
    pf_window *w = d->top;
    if (w == NULL || syscall(MINIOS_SYS_MOUSE, m) != 0) return 0;
    int handled = 0;
    int x = m[FREEDOM_GUI_MOUSE_X] - d->origin[0];
    int y = m[FREEDOM_GUI_MOUSE_Y] - d->origin[1];
    int inside = x >= 0 && y >= 0 && x < w->width && y < w->height;
    if (inside && !d->ptr_inside) {
        d->ptr_inside = 1;
        d->ptr_x = x;
        d->ptr_y = y;
        if (w->h.pointer_enter) w->h.pointer_enter(w->ud, x, y);
        handled = 1;
    } else if (!inside && d->ptr_inside) {
        d->ptr_inside = 0;
        if (w->h.pointer_leave) w->h.pointer_leave(w->ud);
        handled = 1;
    } else if (inside && (x != d->ptr_x || y != d->ptr_y)) {
        d->ptr_x = x;
        d->ptr_y = y;
        if (w->h.pointer_motion) w->h.pointer_motion(w->ud, x, y);
        handled = 1;
    }
    int b = m[FREEDOM_GUI_MOUSE_BUTTONS];
    for (int i = 0; i < FREEDOM_GUI_BUTTONS; ++i) {
        int bit = 1 << i;
        if ((b & bit) == (d->buttons & bit)) continue;
        int pressed = (b & bit) != 0;
        if (pressed && !inside) continue;
        d->buttons = pressed ? (d->buttons | bit) : (d->buttons & ~bit);
        if (d->top != w) return 1;
        if (w->h.pointer_button) w->h.pointer_button(w->ud, freedom_gui_buttons[i], pressed);
        handled = 1;
    }
    int wheel = m[FREEDOM_GUI_MOUSE_WHEEL];
    if (wheel != 0 && inside && d->top == w) {
        if (w->h.pointer_axis) w->h.pointer_axis(w->ud, -(double)wheel);
        handled = 1;
    }
    return handled;
}

int pf_display_wait(pf_display *d, struct pollfd *extra, int n, int timeout_ms) {
    if (d == NULL || n < 0 || n > PF_WAIT_MAX_EXTRA || (n > 0 && extra == NULL))
        return PF_WAIT_FATAL;
    for (int i = 0; i < n; ++i) extra[i].revents = 0;
    if (deliver_pending(d)) return PF_WAIT_EVENTS;
    long start = now_ms();
    for (;;) {
        int handled = pump_keyboard(d);
        handled |= pump_mouse(d);
        handled |= deliver_pending(d);
        if (n > 0) {
            int pr = poll(extra, (nfds_t)n, 0);
            if (pr > 0) return PF_WAIT_EVENTS;
            if (pr < 0 && errno != EINTR) return PF_WAIT_FATAL;
        }
        if (handled) return PF_WAIT_EVENTS;
        long elapsed = now_ms() - start;
        if (timeout_ms >= 0 && elapsed >= (long)timeout_ms) return PF_WAIT_TIMEOUT;
        long slice_end = now_ms() + FREEDOM_GUI_TICK_MS;
        while (now_ms() < slice_end) (void)syscall(MINIOS_SYS_SCHED_YIELD, 0L);
    }
}

/* ---------------------------------------------------------------- clipboard */

int pf_clipboard_available(const pf_display *d) {
    return d != NULL;
}

pf_status pf_clipboard_set_text(pf_display *d, const char *text) {
    if (d == NULL || text == NULL) return PF_ERR_NULL_ARG;
    size_t len = strlen(text);
    if (len > (size_t)FREEDOM_GUI_CLIP_MAX) return PF_ERR_IO;
    return syscall(MINIOS_SYS_CLIP_SET, text, (long)len) == 0 ? PF_OK : PF_ERR_IO;
}

pf_status pf_clipboard_get_text(pf_display *d, char **out, size_t *out_len) {
    if (out != NULL) *out = NULL;
    if (out_len != NULL) *out_len = 0;
    if (d == NULL || out == NULL) return PF_ERR_NULL_ARG;
    char *buf = (char *)malloc((size_t)FREEDOM_GUI_CLIP_MAX + 1);
    if (buf == NULL) return PF_ERR_OOM;
    long got = syscall(MINIOS_SYS_CLIP_GET, buf, FREEDOM_GUI_CLIP_MAX);
    if (got <= 0) { free(buf); return PF_ERR_UNSUPPORTED; }
    buf[got] = '\0';
    *out = buf;
    if (out_len != NULL) *out_len = (size_t)got;
    return PF_OK;
}

/* ---------------------------------------------------------------- window */

pf_status pf_window_open(pf_display *d, const pf_window_opts *o,
                         const pf_window_handlers *h, void *ud, pf_window **out) {
    if (out != NULL) *out = NULL;
    if (d == NULL || o == NULL || h == NULL || out == NULL) return PF_ERR_NULL_ARG;
    pf_window *w = (pf_window *)calloc(1, sizeof *w);
    if (w == NULL) return PF_ERR_OOM;
    w->d = d;
    w->h = *h;
    w->ud = ud;
    w->width = MINIOS_NK_W;
    w->height = MINIOS_NK_H;
    w->states = (d->top != NULL) ? d->top->states : 0u;
    w->pending = 1;
    snprintf(w->title, sizeof w->title, "%s", o->title != NULL ? o->title : "");
    w->below = d->top;
    d->top = w;
    d->ptr_inside = 0;
    set_title(w->title);
    *out = w;
    return PF_OK;
}

void pf_window_close(pf_window *w) {
    if (w == NULL) return;
    pf_display *d = w->d;
    for (pf_window **pp = &d->top; *pp != NULL; pp = &(*pp)->below) {
        if (*pp == w) { *pp = w->below; break; }
    }
    if (w->cairo != NULL) cairo_surface_destroy(w->cairo);
    free(w);
    memset(d->held, 0, sizeof d->held);
    memset(d->repeat_ok, 0, sizeof d->repeat_ok);
    d->ptr_inside = 0;
    if (d->top != NULL) {
        d->top->pending = 1;
        set_title(d->top->title);
    }
}

cairo_surface_t *pf_window_surface(pf_window *w, int width, int height) {
    if (w == NULL || width <= 0 || height <= 0) return NULL;
    if (w->cairo != NULL && cairo_image_surface_get_width(w->cairo) == width &&
        cairo_image_surface_get_height(w->cairo) == height)
        return w->cairo;
    if (w->cairo != NULL) { cairo_surface_destroy(w->cairo); w->cairo = NULL; }
    cairo_surface_t *s = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    if (cairo_surface_status(s) != CAIRO_STATUS_SUCCESS) {
        cairo_surface_destroy(s);
        return NULL;
    }
    w->cairo = s;
    return s;
}

void pf_window_present(pf_window *w) {
    if (w == NULL || w->cairo == NULL || w->d->top != w) return;
    pf_display *d = w->d;
    cairo_surface_flush(w->cairo);
    const unsigned char *src = cairo_image_surface_get_data(w->cairo);
    int stride = cairo_image_surface_get_stride(w->cairo);
    int sw = cairo_image_surface_get_width(w->cairo);
    int sh = cairo_image_surface_get_height(w->cairo);
    unsigned char *dst = (unsigned char *)MINIOS_NK_RGB_ADDR;
    for (int y = 0; y < MINIOS_NK_H; ++y) {
        unsigned char *row = dst + (size_t)y * MINIOS_NK_W * FREEDOM_GUI_RGB_BPP;
        if (y >= sh) {
            memset(row, 0, (size_t)MINIOS_NK_W * FREEDOM_GUI_RGB_BPP);
            continue;
        }
        const uint32_t *px = (const uint32_t *)(src + (size_t)y * (size_t)stride);
        for (int x = 0; x < MINIOS_NK_W; ++x) {
            uint32_t p = (x < sw) ? px[x] : 0u;
            row[x * FREEDOM_GUI_RGB_BPP + 0] = (unsigned char)((p >> 16) & 0xFFu);
            row[x * FREEDOM_GUI_RGB_BPP + 1] = (unsigned char)((p >> 8) & 0xFFu);
            row[x * FREEDOM_GUI_RGB_BPP + 2] = (unsigned char)(p & 0xFFu);
        }
    }
    int origin[2] = { 0, 0 };
    if (syscall(MINIOS_SYS_GFX_PRESENT, (long)MINIOS_GFX_BUF_NK_RGB, origin) != 0) return;
    d->origin[0] = origin[0];
    d->origin[1] = origin[1];
    if (!d->frame_reported) {
        d->frame_reported = 1;
        printf("freedom: frame ok (%dx%d)\n", MINIOS_NK_W, MINIOS_NK_H);
        fflush(stdout);
    }
}

void pf_window_set_title(pf_window *w, const char *title) {
    if (w == NULL || title == NULL) return;
    snprintf(w->title, sizeof w->title, "%s", title);
    if (w->d->top == w) set_title(w->title);
}

static void set_zoom_state(pf_window *w, unsigned bit, int on) {
    long arg = on ? (long)MINIOS_GFX_ZOOM_FULLSCREEN : (long)MINIOS_GFX_ZOOM_WINDOWED;
    if (syscall(MINIOS_SYS_GFX_ZOOM, arg) != 0) return;
    w->d->zoomed = on;
    w->states &= ~(PF_STATE_MAXIMIZED | PF_STATE_FULLSCREEN);
    if (on) w->states |= bit;
    w->pending = 1;
}

void pf_window_set_maximized(pf_window *w, int on) {
    if (w != NULL) set_zoom_state(w, PF_STATE_MAXIMIZED, on);
}

void pf_window_set_fullscreen(pf_window *w, int on) {
    if (w != NULL) set_zoom_state(w, PF_STATE_FULLSCREEN, on);
}

void pf_window_minimize(pf_window *w) {
    (void)w;
}

void pf_window_begin_move(pf_window *w) {
    (void)w;
}

void pf_window_begin_resize(pf_window *w, pf_edge edge) {
    (void)w;
    (void)edge;
}
