/** wl_mini.h - Wayland-mini subset contract (header-only, ADR-0024).
 *
 * One-file contract like wm_geom.h: wire encode/decode, interface ids,
 * opcodes, shm pool and surface state, mini client helpers and the
 * ring-3 compositor z-order. Integer-only, no libc beyond string ops
 * at call sites. Every bound fails closed with WL_ERR_*, never truncates.
 *
 * Wire format matches Wayland: u32 object_id, u16 opcode, u16 size
 * (total incl. header), then args. Args: int/uint/fd as u32, string as
 * u32 len + bytes + NUL + pad-to-4.
 *
 * Addresses never hardcoded here: surface pixel bounds derive from
 * minios_abi.h MINIOS_NK_W/H at the call site; this header only carries
 * counts and byte limits.
 */

#ifndef WL_MINI_H
#define WL_MINI_H

#define WL_MAX_MSG 4096
#define WL_MAX_STR 256
#define WL_MAX_SURFACES 8
#define WL_MAX_POOLS 8
#define WL_SURF_MAX_W 800
#define WL_SURF_MAX_H 360
#define WL_POOL_MAX (WL_SURF_MAX_W * WL_SURF_MAX_H)
#define WL_HDR_SZ 8
#define WL_ATTACH_SZ 12
#define WL_COMMIT_SZ 4

#define WL_ERR_OK 0
#define WL_ERR_BOUND (-1)
#define WL_ERR_TRUNC (-2)
#define WL_ERR_SIZE (-3)
#define WL_ERR_ID (-4)
#define WL_ERR_STR (-5)
#define WL_ERR_MORE (-6)

#define WL_ID_DISPLAY 1u
#define WL_ID_REGISTRY 2u
#define WL_ID_COMPOSITOR 3u
#define WL_ID_SHM 4u
#define WL_ID_XDG_BASE 5u
#define WL_ID_SURFACE_BASE 16u
#define WL_ID_POOL_BASE 64u
#define WL_ID_BUFFER_BASE 128u

#define WL_OP_DISPLAY_GET_REGISTRY 1u
#define WL_OP_REGISTRY_BIND 0u
#define WL_OP_COMPOSITOR_CREATE_SURFACE 0u
#define WL_OP_SHM_CREATE_POOL 0u
#define WL_OP_POOL_CREATE_BUFFER 0u
#define WL_OP_SURFACE_ATTACH 1u
#define WL_OP_SURFACE_COMMIT 6u
#define WL_OP_XDG_GET_TOPLEVEL 1u

typedef struct {
    unsigned int id;
    unsigned short opcode;
    unsigned short size;
} wl_hdr_t;

typedef struct {
    unsigned int surfaces;
    unsigned int pools;
    unsigned int focus;
} wl_cfg_t;

#define WL_CFG_DEFAULT { 8u, 8u, 0u }

static inline int wl_hdr_encode(unsigned char *dst, int cap,
        unsigned int id, unsigned int opcode, unsigned int size,
        wl_hdr_t *out) {
    if (!dst || cap < WL_HDR_SZ)
        return WL_ERR_BOUND;
    if (id == 0 || id >= 256u)
        return WL_ERR_ID;
    if (size < (unsigned int)WL_HDR_SZ || size > (unsigned int)WL_MAX_MSG)
        return WL_ERR_SIZE;
    if (opcode > 255u)
        return WL_ERR_BOUND;
    dst[0] = (unsigned char)(id & 0xFFu);
    dst[1] = (unsigned char)((id >> 8) & 0xFFu);
    dst[2] = (unsigned char)((id >> 16) & 0xFFu);
    dst[3] = (unsigned char)((id >> 24) & 0xFFu);
    /* Canonical layout: bytes 4..5 opcode LE, 6..7 size LE. */
    dst[4] = (unsigned char)(opcode & 0xFFu);
    dst[5] = (unsigned char)((opcode >> 8) & 0xFFu);
    dst[6] = (unsigned char)(size & 0xFFu);
    dst[7] = (unsigned char)((size >> 8) & 0xFFu);
    if (out) {
        out->id = id;
        out->opcode = (unsigned short)opcode;
        out->size = (unsigned short)size;
    }
    return WL_ERR_OK;
}

static inline int wl_hdr_decode(const unsigned char *src, int len,
        wl_hdr_t *out) {
    unsigned int id;
    unsigned int opcode;
    unsigned int size;
    if (!src || !out)
        return WL_ERR_BOUND;
    if (len < WL_HDR_SZ)
        return WL_ERR_TRUNC;
    id = (unsigned int)src[0]
        | ((unsigned int)src[1] << 8)
        | ((unsigned int)src[2] << 16)
        | ((unsigned int)src[3] << 24);
    opcode = (unsigned int)src[4] | ((unsigned int)src[5] << 8);
    size = (unsigned int)src[6] | ((unsigned int)src[7] << 8);
    if (id == 0 || id >= 256u)
        return WL_ERR_ID;
    if (size < (unsigned int)WL_HDR_SZ || size > (unsigned int)WL_MAX_MSG)
        return WL_ERR_SIZE;
    if ((int)size > len)
        return WL_ERR_TRUNC;
    if (opcode > 255u)
        return WL_ERR_BOUND;
    out->id = id;
    out->opcode = (unsigned short)opcode;
    out->size = (unsigned short)size;
    return WL_ERR_OK;
}

static inline int wl_u32_encode(unsigned char *dst, int cap, int off,
        unsigned int v) {
    if (!dst || off < 0 || cap - off < 4)
        return WL_ERR_BOUND;
    dst[off] = (unsigned char)(v & 0xFFu);
    dst[off + 1] = (unsigned char)((v >> 8) & 0xFFu);
    dst[off + 2] = (unsigned char)((v >> 16) & 0xFFu);
    dst[off + 3] = (unsigned char)((v >> 24) & 0xFFu);
    return WL_ERR_OK;
}

static inline int wl_u32_decode(const unsigned char *src, int len, int off,
        unsigned int *v) {
    if (!src || !v || off < 0 || len - off < 4)
        return WL_ERR_BOUND;
    *v = (unsigned int)src[off]
        | ((unsigned int)src[off + 1] << 8)
        | ((unsigned int)src[off + 2] << 16)
        | ((unsigned int)src[off + 3] << 24);
    return WL_ERR_OK;
}

static inline int wl_strlen_bounded(const char *s) {
    int n = 0;
    if (!s)
        return WL_ERR_STR;
    while (s[n] != '\0') {
        n++;
        if (n >= WL_MAX_STR)
            return WL_ERR_STR;
    }
    return n;
}

/* String arg: u32 len (incl. NUL) + bytes + pad to 4. Returns total or err. */
static inline int wl_str_encode(unsigned char *dst, int cap, int off,
        const char *s) {
    int n;
    int total;
    int pad;
    int i;
    if (!dst || !s)
        return WL_ERR_STR;
    n = wl_strlen_bounded(s);
    if (n < 0)
        return n;
    total = 4 + n + 1;
    pad = (4 - (total & 3)) & 3;
    total += pad;
    if (off < 0 || cap - off < total)
        return WL_ERR_BOUND;
    if (wl_u32_encode(dst, cap, off, (unsigned int)(n + 1)) != WL_ERR_OK)
        return WL_ERR_BOUND;
    for (i = 0; i <= n; i++)
        dst[off + 4 + i] = (unsigned char)s[i];
    for (i = 0; i < pad; i++)
        dst[off + 4 + n + 1 + i] = 0;
    return total;
}

static inline int wl_str_decode(const unsigned char *src, int len, int off,
        char *dst, int dcap) {
    unsigned int slen = 0;
    unsigned int total;
    unsigned int pad;
    unsigned int i;
    if (!src || !dst)
        return WL_ERR_STR;
    if (wl_u32_decode(src, len, off, &slen) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (slen == 0 || slen > (unsigned int)WL_MAX_STR)
        return WL_ERR_STR;
    total = 4 + slen;
    pad = (4 - (total & 3u)) & 3u;
    total += pad;
    if (off < 0 || (unsigned int)(len - off) < total)
        return WL_ERR_TRUNC;
    if ((int)slen > dcap - 1)
        return WL_ERR_BOUND;
    if (src[off + 4 + slen - 1] != 0)
        return WL_ERR_STR;
    for (i = 0; i < slen; i++)
        dst[i] = (char)src[off + 4 + i];
    return (int)total;
}

static inline int wl_surface_id_valid(unsigned int id) {
    return id >= WL_ID_SURFACE_BASE
        && id < WL_ID_SURFACE_BASE + WL_MAX_SURFACES;
}

static inline int wl_pool_id_valid(unsigned int id) {
    return id >= WL_ID_POOL_BASE && id < WL_ID_POOL_BASE + WL_MAX_POOLS;
}

static inline int wl_pool_fit(int w, int h) {
    long n;
    if (w <= 0 || h <= 0 || w > WL_SURF_MAX_W || h > WL_SURF_MAX_H)
        return WL_ERR_BOUND;
    n = (long)w * (long)h;
    if (n > (long)WL_POOL_MAX)
        return WL_ERR_BOUND;
    return WL_ERR_OK;
}

/** Window chrome geometry and inks. Title bar lives inside the
 * surface frame below the 1px border so hit testing and compositing
 * share one layout. Inks stay in the desktop-exact 0-14 range so the
 * desktop behind never recolors. Small surfaces skip the bar and
 * render exactly like before. */
#define WL_TITLE_H 14
#define WL_CLOSE_W 12
#define WL_RESIZE_EDGE 5
#define WL_TITLE_ACTIVE 4
#define WL_TITLE_INACTIVE 2
#define WL_CLOSE_INK 11

#define WL_HIT_NONE (-1)
#define WL_HIT_BODY 0
#define WL_HIT_TITLE 1
#define WL_HIT_CLOSE 2
#define WL_HIT_RESIZE 3

typedef struct {
    unsigned int id;
    int x;
    int y;
    int w;
    int h;
    int mapped;
    unsigned int pool;
    int color;
    int active;
    int minimized;
} wl_surface_t;

typedef struct {
    wl_surface_t items[WL_MAX_SURFACES];
    unsigned int order[WL_MAX_SURFACES];
    int count;
    int focus;
} wl_comp_t;

static inline void wl_comp_init(wl_comp_t *c) {
    int i;
    if (!c)
        return;
    c->count = 0;
    c->focus = -1;
    for (i = 0; i < WL_MAX_SURFACES; i++) {
        c->items[i].id = 0;
        c->items[i].mapped = 0;
        c->items[i].active = 0;
        c->items[i].minimized = 0;
        c->order[i] = 0;
    }
}

/** Refresh the active flag from z-order: only the top-most mapped,
 * non-minimized surface reads active. Single place so focus, add and
 * remove can never disagree on which title paints bright. */
static inline void wl_comp_refresh_active(wl_comp_t *c) {
    int i;
    int top = -1;
    if (!c)
        return;
    for (i = 0; i < WL_MAX_SURFACES; i++)
        c->items[i].active = 0;
    for (i = c->count - 1; i >= 0; i--) {
        int slot = (int)c->order[i];
        if (slot < 0 || slot >= WL_MAX_SURFACES)
            continue;
        if (c->items[slot].mapped && !c->items[slot].minimized) {
            top = slot;
            break;
        }
    }
    if (top >= 0)
        c->items[top].active = 1;
}

static inline int wl_comp_add(wl_comp_t *c, unsigned int id, int w, int h) {
    int i;
    if (!c)
        return WL_ERR_BOUND;
    if (!wl_surface_id_valid(id))
        return WL_ERR_ID;
    if (wl_pool_fit(w, h) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (c->count >= WL_MAX_SURFACES)
        return WL_ERR_BOUND;
    for (i = 0; i < WL_MAX_SURFACES; i++) {
        if (c->items[i].id == id)
            return WL_ERR_ID;
    }
    for (i = 0; i < WL_MAX_SURFACES; i++) {
        if (c->items[i].id == 0) {
            c->items[i].id = id;
            c->items[i].x = 0;
            c->items[i].y = 0;
            c->items[i].w = w;
            c->items[i].h = h;
            c->items[i].mapped = 1;
            c->items[i].pool = 0;
            c->items[i].color = 4;
            c->items[i].minimized = 0;
            c->items[i].active = 0;
            c->order[c->count] = (unsigned int)i;
            c->count++;
            c->focus = i;
            wl_comp_refresh_active(c);
            return WL_ERR_OK;
        }
    }
    return WL_ERR_BOUND;
}

static inline int wl_comp_remove(wl_comp_t *c, unsigned int id) {
    int i;
    int k;
    int slot = -1;
    if (!c)
        return WL_ERR_BOUND;
    for (i = 0; i < WL_MAX_SURFACES; i++) {
        if (c->items[i].id == id)
            slot = i;
    }
    if (slot < 0)
        return WL_ERR_ID;
    c->items[slot].id = 0;
    c->items[slot].mapped = 0;
    for (i = 0; i < c->count; i++) {
        if ((int)c->order[i] == slot) {
            for (k = i; k + 1 < c->count; k++)
                c->order[k] = c->order[k + 1];
            c->count--;
            break;
        }
    }
    c->focus = c->count > 0 ? (int)c->order[c->count - 1] : -1;
    wl_comp_refresh_active(c);
    return WL_ERR_OK;
}

static inline int wl_comp_focus(wl_comp_t *c, unsigned int id) {
    int i;
    int slot = -1;
    int k;
    if (!c)
        return WL_ERR_BOUND;
    for (i = 0; i < WL_MAX_SURFACES; i++) {
        if (c->items[i].id == id)
            slot = i;
    }
    if (slot < 0)
        return WL_ERR_ID;
    for (i = 0; i < c->count; i++) {
        if ((int)c->order[i] == slot) {
            for (k = i; k + 1 < c->count; k++)
                c->order[k] = c->order[k + 1];
            c->order[c->count - 1] = (unsigned int)slot;
            c->focus = slot;
            wl_comp_refresh_active(c);
            return WL_ERR_OK;
        }
    }
    return WL_ERR_ID;
}

static inline int wl_comp_hit(const wl_comp_t *c, int x, int y) {
    int i;
    if (!c)
        return -1;
    for (i = c->count - 1; i >= 0; i--) {
        const wl_surface_t *s = &c->items[c->order[i]];
        if (!s->mapped || s->minimized)
            continue;
        if (x >= s->x && x < s->x + s->w && y >= s->y && y < s->y + s->h)
            return (int)s->id;
    }
    return -1;
}

/** Classify a point inside one surface: close button first, then
 * title drag strip, then the resize rim, else body. Points outside
 * fail closed with HIT_NONE. Geometry mirrors wlcomp_blit_chrome so
 * clicks and pixels can never disagree. */
static inline int wl_surface_hit_zone(const wl_surface_t *s, int x, int y) {
    int lx;
    int ly;
    int has_title;
    if (!s || !s->mapped || s->minimized)
        return WL_HIT_NONE;
    if (x < s->x || x >= s->x + s->w || y < s->y || y >= s->y + s->h)
        return WL_HIT_NONE;
    lx = x - s->x;
    ly = y - s->y;
    if (lx == 0 || ly == 0 || lx == s->w - 1 || ly == s->h - 1)
        return WL_HIT_RESIZE;
    has_title = (s->w > WL_CLOSE_W + 4 && s->h > WL_TITLE_H + 2);
    if (has_title && ly >= 1 && ly <= WL_TITLE_H) {
        if (lx >= s->w - 1 - WL_CLOSE_W && lx < s->w - 1)
            return WL_HIT_CLOSE;
        return WL_HIT_TITLE;
    }
    if (lx >= s->w - WL_RESIZE_EDGE || ly >= s->h - WL_RESIZE_EDGE)
        return WL_HIT_RESIZE;
    return WL_HIT_BODY;
}

/** Minimize/restore one surface. Minimized surfaces keep their slot
 * and geometry but skip hit testing, tiling and compositing until
 * restored. */
static inline int wl_comp_set_minimized(wl_comp_t *c, unsigned int id,
        int minimized) {
    int i;
    if (!c)
        return WL_ERR_BOUND;
    for (i = 0; i < WL_MAX_SURFACES; i++) {
        if (c->items[i].id == id) {
            c->items[i].minimized = minimized ? 1 : 0;
            wl_comp_refresh_active(c);
            return WL_ERR_OK;
        }
    }
    return WL_ERR_ID;
}

static inline int wl_comp_set_color(wl_comp_t *c, unsigned int id, int color) {
    int i;
    if (!c)
        return WL_ERR_BOUND;
    if (color < 0 || color > 255)
        return WL_ERR_BOUND;
    for (i = 0; i < WL_MAX_SURFACES; i++) {
        if (c->items[i].id == id) {
            c->items[i].color = color;
            return WL_ERR_OK;
        }
    }
    return WL_ERR_ID;
}

/* Software composite of the surface stack into a palette-index fb.
 * Pure function, no syscalls: the guest points fb at the NK back-buffer,
 * the host test points it at malloc. Colors are desktop palette indices
 * 0-14 (vga_fb.h COL_*, exact so the desktop behind never recolors);
 * callers pass their own pixels for richer content in later phases.
 * Fills bg, then mapped surfaces bottom-to-top, each clipped to the fb
 * with a 1px border. Fail-closed on null or degenerate geometry. */
#define WLCOMP_BG 1
#define WLCOMP_BORDER 9

static inline int wlcomp_render(const wl_comp_t *c, unsigned char *fb,
        int fb_w, int fb_h) {
    int i;
    int x;
    int y;
    if (!c || !fb || fb_w <= 0 || fb_h <= 0)
        return WL_ERR_BOUND;
    if (fb_w > 800 || fb_h > 360)
        return WL_ERR_BOUND;
    for (y = 0; y < fb_h; y++) {
        for (x = 0; x < fb_w; x++)
            fb[y * fb_w + x] = WLCOMP_BG;
    }
    for (i = 0; i < c->count; i++) {
        const wl_surface_t *s = &c->items[c->order[i]];
        int x0 = s->x < 0 ? 0 : s->x;
        int y0 = s->y < 0 ? 0 : s->y;
        int x1 = s->x + s->w > fb_w ? fb_w : s->x + s->w;
        int y1 = s->y + s->h > fb_h ? fb_h : s->y + s->h;
        if (!s->mapped || s->minimized)
            continue;
        if (x0 >= x1 || y0 >= y1)
            continue;
        for (y = y0; y < y1; y++) {
            for (x = x0; x < x1; x++) {
                if (x == x0 || y == y0 || x == x1 - 1 || y == y1 - 1)
                    fb[y * fb_w + x] = WLCOMP_BORDER;
                else
                    fb[y * fb_w + x] = (unsigned char)s->color;
            }
        }
    }
    return WL_ERR_OK;
}

/** Move and resize a mapped surface. Geometry validates through
 * wl_pool_fit; positions allow a one-screen negative margin so a drag
 * can park a surface partly offscreen, anything beyond fails closed. */
static inline int wl_comp_set_rect(wl_comp_t *c, unsigned int id,
        int x, int y, int w, int h) {
    int i;
    if (!c)
        return WL_ERR_BOUND;
    if (wl_pool_fit(w, h) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (x < -WL_SURF_MAX_W || x > WL_SURF_MAX_W
        || y < -WL_SURF_MAX_H || y > WL_SURF_MAX_H)
        return WL_ERR_BOUND;
    for (i = 0; i < WL_MAX_SURFACES; i++) {
        if (c->items[i].id == id) {
            c->items[i].x = x;
            c->items[i].y = y;
            c->items[i].w = w;
            c->items[i].h = h;
            return WL_ERR_OK;
        }
    }
    return WL_ERR_ID;
}

/** Tile every mapped surface over the frame in z-order. One surface
 * fills the frame, two split it vertically, three or more form a
 * rows-by-columns grid with the last row and column absorbing the
 * integer remainder. Returns the tiled count, fail-closed when there
 * is nothing mapped or the frame is degenerate. */
static inline int wl_comp_layout_tile(wl_comp_t *c, int fb_w, int fb_h) {
    int mapped = 0;
    int rows = 0;
    int cols = 0;
    int cell_w = 0;
    int cell_h = 0;
    int k = 0;
    int i;
    if (!c)
        return WL_ERR_BOUND;
    if (fb_w <= 0 || fb_h <= 0 || fb_w > WL_SURF_MAX_W
        || fb_h > WL_SURF_MAX_H)
        return WL_ERR_BOUND;
    for (i = 0; i < c->count; i++) {
        if (c->items[c->order[i]].mapped
            && !c->items[c->order[i]].minimized)
            mapped++;
    }
    if (mapped <= 0)
        return WL_ERR_BOUND;
    if (mapped == 1) {
        rows = 1;
        cols = 1;
    } else if (mapped == 2) {
        rows = 1;
        cols = 2;
    } else {
        rows = 1;
        while (rows * rows < mapped)
            rows++;
        cols = (mapped + rows - 1) / rows;
    }
    cell_w = fb_w / cols;
    cell_h = fb_h / rows;
    if (cell_w <= 0 || cell_h <= 0)
        return WL_ERR_BOUND;
    for (i = 0; i < c->count; i++) {
        wl_surface_t *s = &c->items[c->order[i]];
        int col;
        int row;
        if (!s->mapped || s->minimized)
            continue;
        col = k % cols;
        row = k / cols;
        s->x = col * cell_w;
        s->y = row * cell_h;
        s->w = (col == cols - 1) ? fb_w - s->x : cell_w;
        s->h = (row == rows - 1) ? fb_h - s->y : cell_h;
        if (wl_pool_fit(s->w, s->h) != WL_ERR_OK)
            return WL_ERR_BOUND;
        k++;
    }
    return mapped;
}

/** Composite the surface stack with real client pixels. px, pw and ph
 * are slot-indexed tables over items[]; a null slot entry renders the
 * surface solid color exactly like wlcomp_render, which keeps single
 * color clients working. A present pixel table whose dimensions differ
 * from the surface fails closed. Null table means all solid. */
static inline int wlcomp_blit(const wl_comp_t *c, unsigned char *fb,
        int fb_w, int fb_h, const unsigned char * const *px,
        const int *pw, const int *ph) {
    int i;
    int x;
    int y;
    if (!c || !fb || fb_w <= 0 || fb_h <= 0)
        return WL_ERR_BOUND;
    if (fb_w > WL_SURF_MAX_W || fb_h > WL_SURF_MAX_H)
        return WL_ERR_BOUND;
    if (px) {
        for (i = 0; i < WL_MAX_SURFACES; i++) {
            if (!px[i])
                continue;
            if (!pw || !ph || pw[i] <= 0 || ph[i] <= 0)
                return WL_ERR_BOUND;
        }
    }
    for (y = 0; y < fb_h; y++) {
        for (x = 0; x < fb_w; x++)
            fb[y * fb_w + x] = WLCOMP_BG;
    }
    for (i = 0; i < c->count; i++) {
        const wl_surface_t *s = &c->items[c->order[i]];
        const unsigned char *src = 0;
        int slot;
        int x0;
        int y0;
        int x1;
        int y1;
        if (!s->mapped || s->minimized)
            continue;
        slot = (int)(s - c->items);
        if (px && px[slot]) {
            if (pw[slot] != s->w || ph[slot] != s->h)
                return WL_ERR_BOUND;
            src = px[slot];
        }
        x0 = s->x < 0 ? 0 : s->x;
        y0 = s->y < 0 ? 0 : s->y;
        x1 = s->x + s->w > fb_w ? fb_w : s->x + s->w;
        y1 = s->y + s->h > fb_h ? fb_h : s->y + s->h;
        if (x0 >= x1 || y0 >= y1)
            continue;
        for (y = y0; y < y1; y++) {
            for (x = x0; x < x1; x++) {
                if (x == x0 || y == y0 || x == x1 - 1 || y == y1 - 1)
                    fb[y * fb_w + x] = WLCOMP_BORDER;
                else if (src)
                    fb[y * fb_w + x] = src[(y - s->y) * s->w + (x - s->x)];
                else
                    fb[y * fb_w + x] = (unsigned char)s->color;
            }
        }
    }
    return WL_ERR_OK;
}

/** Composite with window chrome: a title strip inside the frame
 * paints active vs inactive, with a close box at its right end, and
 * client pixels fill only below it. Small surfaces render exactly
 * like wlcomp_blit so the legacy selftest vectors never move. Pure
 * function, same fail-closed bounds as wlcomp_blit, same slot tables. */
static inline int wlcomp_blit_chrome(const wl_comp_t *c, unsigned char *fb,
        int fb_w, int fb_h, const unsigned char * const *px,
        const int *pw, const int *ph) {
    int i;
    int x;
    int y;
    if (!c || !fb || fb_w <= 0 || fb_h <= 0)
        return WL_ERR_BOUND;
    if (fb_w > WL_SURF_MAX_W || fb_h > WL_SURF_MAX_H)
        return WL_ERR_BOUND;
    if (px) {
        for (i = 0; i < WL_MAX_SURFACES; i++) {
            if (!px[i])
                continue;
            if (!pw || !ph || pw[i] <= 0 || ph[i] <= 0)
                return WL_ERR_BOUND;
        }
    }
    for (y = 0; y < fb_h; y++) {
        for (x = 0; x < fb_w; x++)
            fb[y * fb_w + x] = WLCOMP_BG;
    }
    for (i = 0; i < c->count; i++) {
        const wl_surface_t *s = &c->items[c->order[i]];
        const unsigned char *src = 0;
        int slot;
        int x0;
        int y0;
        int x1;
        int y1;
        int has_title;
        if (!s->mapped || s->minimized)
            continue;
        slot = (int)(s - c->items);
        if (px && px[slot]) {
            if (pw[slot] != s->w || ph[slot] != s->h)
                return WL_ERR_BOUND;
            src = px[slot];
        }
        x0 = s->x < 0 ? 0 : s->x;
        y0 = s->y < 0 ? 0 : s->y;
        x1 = s->x + s->w > fb_w ? fb_w : s->x + s->w;
        y1 = s->y + s->h > fb_h ? fb_h : s->y + s->h;
        if (x0 >= x1 || y0 >= y1)
            continue;
        has_title = (s->w > WL_CLOSE_W + 4 && s->h > WL_TITLE_H + 2);
        for (y = y0; y < y1; y++) {
            for (x = x0; x < x1; x++) {
                int lx = x - s->x;
                int ly = y - s->y;
                if (x == x0 || y == y0 || x == x1 - 1 || y == y1 - 1) {
                    fb[y * fb_w + x] = WLCOMP_BORDER;
                } else if (has_title && ly >= 1 && ly <= WL_TITLE_H) {
                    if (lx >= s->w - 1 - WL_CLOSE_W && lx < s->w - 1)
                        fb[y * fb_w + x] = WL_CLOSE_INK;
                    else
                        fb[y * fb_w + x] = (unsigned char)(s->active
                            ? WL_TITLE_ACTIVE : WL_TITLE_INACTIVE);
                } else if (src) {
                    fb[y * fb_w + x] = src[(y - s->y) * s->w + (x - s->x)];
                } else {
                    fb[y * fb_w + x] = (unsigned char)s->color;
                }
            }
        }
    }
    return WL_ERR_OK;
}

/** Nearest-neighbour scale of an indexed frame, the compositor side
 * of a client buffer meeting a layout cell of another size. A real
 * compositor scales or clips; refusing would unmap every client the
 * moment it tiles, so the resample stays exact and bounded instead.
 * Fail-closed on null or degenerate geometry and on arithmetic the
 * frame cannot hold. */
static inline int wl_scale_nearest(unsigned char *dst, int dw, int dh,
        const unsigned char *src, int sw, int sh) {
    int y;
    int x;
    long n;
    if (!dst || !src)
        return WL_ERR_BOUND;
    if (dw <= 0 || dh <= 0 || sw <= 0 || sh <= 0)
        return WL_ERR_BOUND;
    if (dw > WL_SURF_MAX_W || dh > WL_SURF_MAX_H)
        return WL_ERR_BOUND;
    if (sw > WL_SURF_MAX_W || sh > WL_SURF_MAX_H)
        return WL_ERR_BOUND;
    n = (long)dw * (long)dh;
    if (n > (long)WL_POOL_MAX)
        return WL_ERR_BOUND;
    for (y = 0; y < dh; y++) {
        int sy = (y * sh) / dh;
        for (x = 0; x < dw; x++) {
            int sx = (x * sw) / dw;
            dst[y * dw + x] = src[sy * sw + sx];
        }
    }
    return WL_ERR_OK;
}

/** Attach payload: u32 pool id, u32 width, u32 height. The client speaks
 * it over the mailbox transport; the compositor decodes it before
 * touching any pixel, so a wild pool or an oversized frame never
 * reaches layout. */
static inline int wl_attach_encode(unsigned char *dst, int cap,
        unsigned int pool, int w, int h) {
    if (!dst)
        return WL_ERR_BOUND;
    if (!wl_pool_id_valid(pool))
        return WL_ERR_ID;
    if (wl_pool_fit(w, h) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (cap < WL_ATTACH_SZ)
        return WL_ERR_BOUND;
    if (wl_u32_encode(dst, cap, 0, pool) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (wl_u32_encode(dst, cap, 4, (unsigned int)w) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (wl_u32_encode(dst, cap, 8, (unsigned int)h) != WL_ERR_OK)
        return WL_ERR_BOUND;
    return WL_ATTACH_SZ;
}

static inline int wl_attach_decode(const unsigned char *src, int len,
        unsigned int *pool, int *w, int *h) {
    unsigned int pw = 0;
    unsigned int ph = 0;
    if (!src || !pool || !w || !h)
        return WL_ERR_BOUND;
    if (len < WL_ATTACH_SZ)
        return WL_ERR_TRUNC;
    if (wl_u32_decode(src, len, 0, pool) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (wl_u32_decode(src, len, 4, &pw) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (wl_u32_decode(src, len, 8, &ph) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (!wl_pool_id_valid(*pool))
        return WL_ERR_ID;
    if (pw == 0 || pw > (unsigned int)WL_SURF_MAX_W || ph == 0
        || ph > (unsigned int)WL_SURF_MAX_H)
        return WL_ERR_BOUND;
    if ((long)pw * (long)ph > (long)WL_POOL_MAX)
        return WL_ERR_BOUND;
    *w = (int)pw;
    *h = (int)ph;
    return WL_ERR_OK;
}

/** Commit payload: u32 surface id naming the surface whose attached
 * buffer becomes visible. Wild ids fail closed, never focus a stranger. */
static inline int wl_commit_encode(unsigned char *dst, int cap,
        unsigned int id) {
    if (!dst)
        return WL_ERR_BOUND;
    if (!wl_surface_id_valid(id))
        return WL_ERR_ID;
    if (cap < WL_COMMIT_SZ)
        return WL_ERR_BOUND;
    if (wl_u32_encode(dst, cap, 0, id) != WL_ERR_OK)
        return WL_ERR_BOUND;
    return WL_COMMIT_SZ;
}

static inline int wl_commit_decode(const unsigned char *src, int len,
        unsigned int *id) {
    if (!src || !id)
        return WL_ERR_BOUND;
    if (len < WL_COMMIT_SZ)
        return WL_ERR_TRUNC;
    if (wl_u32_decode(src, len, 0, id) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (!wl_surface_id_valid(*id))
        return WL_ERR_ID;
    return WL_ERR_OK;
}

/** Server-to-client input event, one fixed frame per focused box.
 * The server owns PS/2 while it owns the display, so clients never
 * touch the port in client mode: they poll their <box>.ev file and
 * feed whatever batch carries a newer seq. Mouse is client-buffer
 * coords (mapped by wl_ev_map, -1 when outside), wheel is a
 * monotonic total the client diffs, scancodes are raw Set-1 bytes
 * (E0 prefixes included) the client's own translator consumes.
 * A slow client loses middle batches (latest wins, documented);
 * a batch is never replayed because the server clears after write. */
#define WL_EV_MAGIC 0x56454C57u
#define WL_EV_SC_MAX 16
#define WL_EV_SZ 44

typedef struct {
    unsigned int seq;
    int mx;
    int my;
    unsigned int buttons;
    unsigned int wheel;
    unsigned int nsc;
    unsigned char sc[WL_EV_SC_MAX];
} wl_ev_t;

static inline int wl_ev_encode(unsigned char *dst, int cap,
        const wl_ev_t *ev) {
    int i;
    if (!dst || !ev)
        return WL_ERR_BOUND;
    if (ev->nsc > (unsigned int)WL_EV_SC_MAX)
        return WL_ERR_BOUND;
    if (cap < WL_EV_SZ)
        return WL_ERR_BOUND;
    dst[0] = (unsigned char)(WL_EV_MAGIC & 0xFFu);
    dst[1] = (unsigned char)((WL_EV_MAGIC >> 8) & 0xFFu);
    dst[2] = (unsigned char)((WL_EV_MAGIC >> 16) & 0xFFu);
    dst[3] = (unsigned char)((WL_EV_MAGIC >> 24) & 0xFFu);
    if (wl_u32_encode(dst, cap, 4, ev->seq) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (wl_u32_encode(dst, cap, 8, (unsigned int)ev->mx) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (wl_u32_encode(dst, cap, 12, (unsigned int)ev->my) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (wl_u32_encode(dst, cap, 16, ev->buttons) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (wl_u32_encode(dst, cap, 20, ev->wheel) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (wl_u32_encode(dst, cap, 24, ev->nsc) != WL_ERR_OK)
        return WL_ERR_BOUND;
    for (i = 0; i < WL_EV_SC_MAX; i++)
        dst[28 + i] = i < (int)ev->nsc ? ev->sc[i] : 0;
    return WL_EV_SZ;
}

static inline int wl_ev_decode(const unsigned char *src, int len,
        wl_ev_t *ev) {
    unsigned int magic = 0;
    unsigned int nsc = 0;
    int i;
    if (!src || !ev)
        return WL_ERR_BOUND;
    if (len < WL_EV_SZ)
        return WL_ERR_TRUNC;
    if (len > WL_EV_SZ)
        return WL_ERR_BOUND;
    magic = (unsigned int)src[0]
        | ((unsigned int)src[1] << 8)
        | ((unsigned int)src[2] << 16)
        | ((unsigned int)src[3] << 24);
    if (magic != WL_EV_MAGIC)
        return WL_ERR_BOUND;
    if (wl_u32_decode(src, len, 4, &ev->seq) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (wl_u32_decode(src, len, 8, (unsigned int *)&ev->mx)
        != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (wl_u32_decode(src, len, 12, (unsigned int *)&ev->my)
        != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (wl_u32_decode(src, len, 16, &ev->buttons) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (wl_u32_decode(src, len, 20, &ev->wheel) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (wl_u32_decode(src, len, 24, &nsc) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (nsc > (unsigned int)WL_EV_SC_MAX)
        return WL_ERR_BOUND;
    ev->nsc = nsc;
    for (i = 0; i < WL_EV_SC_MAX; i++)
        ev->sc[i] = src[28 + i];
    return WL_ERR_OK;
}

/** Map a frame point into a client's raw buffer coords. The content
 * area starts below the 1px border plus the title bar; the scale
 * covers layout cells differing from attach dims. Outside maps to
 * (-1,-1) with 0, never a clamped edge that would warp clicks. */
static inline int wl_ev_map(int fx, int fy, int sx, int sy, int sw,
        int sh, int rw, int rh, int *cx, int *cy) {
    long x0;
    long y0;
    long cw;
    long ch;
    if (!cx || !cy)
        return WL_ERR_BOUND;
    *cx = -1;
    *cy = -1;
    if (sw <= WL_CLOSE_W + 4 || sh <= WL_TITLE_H + 2)
        return 0;
    if (rw <= 0 || rh <= 0 || rw > WL_SURF_MAX_W || rh > WL_SURF_MAX_H)
        return WL_ERR_BOUND;
    x0 = (long)sx + 1;
    y0 = (long)sy + 1 + WL_TITLE_H;
    cw = (long)sw - 2;
    ch = (long)sh - 2 - WL_TITLE_H - 1;
    if (cw <= 0 || ch <= 0)
        return 0;
    if (fx < x0 || fy < y0 || fx >= x0 + cw || fy >= y0 + ch)
        return 0;
    *cx = (int)(((long)(fx - x0) * (long)rw) / cw);
    *cy = (int)(((long)(fy - y0) * (long)rh) / ch);
    if (*cx < 0)
        *cx = 0;
    if (*cy < 0)
        *cy = 0;
    if (*cx >= rw)
        *cx = rw - 1;
    if (*cy >= rh)
        *cy = rh - 1;
    return 1;
}

typedef struct {
    unsigned int display;
    unsigned int next_surface;
    unsigned int next_pool;
} wl_client_t;

static inline void wl_client_init(wl_client_t *cl) {
    if (!cl)
        return;
    cl->display = WL_ID_DISPLAY;
    cl->next_surface = WL_ID_SURFACE_BASE;
    cl->next_pool = WL_ID_POOL_BASE;
}

static inline int wl_client_surface(wl_client_t *cl, unsigned int *id) {
    if (!cl || !id)
        return WL_ERR_BOUND;
    if (cl->next_surface >= WL_ID_SURFACE_BASE + WL_MAX_SURFACES)
        return WL_ERR_BOUND;
    *id = cl->next_surface++;
    return WL_ERR_OK;
}

static inline int wl_client_pool(wl_client_t *cl, unsigned int *id) {
    if (!cl || !id)
        return WL_ERR_BOUND;
    if (cl->next_pool >= WL_ID_POOL_BASE + WL_MAX_POOLS)
        return WL_ERR_BOUND;
    *id = cl->next_pool++;
    return WL_ERR_OK;
}

/** Bounded reassembly buffer for one connection. Bytes arrive split
 * anywhere, even mid-header, so feed appends and next only reports a
 * message whose declared size fully arrived. MORE means feed again,
 * SIZE means the peer lied and the connection must die. */
#define WL_STREAM_CAP (WL_MAX_MSG * 2)

typedef struct {
    unsigned char buf[WL_STREAM_CAP];
    int len;
} wl_stream_t;

static inline void wl_stream_init(wl_stream_t *s) {
    if (!s)
        return;
    s->len = 0;
}

static inline int wl_stream_feed(wl_stream_t *s, const unsigned char *src,
        int n) {
    int i;
    if (!s || !src || n < 0)
        return WL_ERR_BOUND;
    if (s->len > WL_STREAM_CAP)
        return WL_ERR_BOUND;
    if (n > WL_STREAM_CAP - s->len)
        return WL_ERR_BOUND;
    for (i = 0; i < n; i++)
        s->buf[s->len + i] = src[i];
    s->len += n;
    return WL_ERR_OK;
}

static inline int wl_stream_next(wl_stream_t *s, int *size) {
    wl_hdr_t h;
    int r;
    if (!s || !size)
        return WL_ERR_BOUND;
    if (s->len < WL_HDR_SZ)
        return WL_ERR_MORE;
    r = wl_hdr_decode(s->buf, s->len, &h);
    if (r == WL_ERR_TRUNC)
        return WL_ERR_MORE;
    if (r != WL_ERR_OK)
        return r;
    *size = (int)h.size;
    return WL_ERR_OK;
}

static inline int wl_stream_consume(wl_stream_t *s, int n) {
    int i;
    if (!s || n < 0 || n > s->len)
        return WL_ERR_BOUND;
    for (i = 0; i + n < s->len; i++)
        s->buf[i] = s->buf[i + n];
    s->len -= n;
    return WL_ERR_OK;
}

/** Interface descriptor table, the hand-written wl_interface subset.
 * request and event counts name what wl_dispatch answers, nothing
 * more; a scanner earns its place only if the subset grows. */
typedef struct {
    const char *name;
    int requests;
    int events;
} wl_iface_t;

#define WL_IFACE_COUNT 10

static inline int wl_iface_find(const char *name) {
    static const wl_iface_t table[WL_IFACE_COUNT] = {
        { "wl_display", 2, 0 },
        { "wl_registry", 1, 1 },
        { "wl_compositor", 1, 0 },
        { "wl_shm", 1, 1 },
        { "xdg_wm_base", 1, 1 },
        { "wl_surface", 2, 0 },
        { "wl_shm_pool", 1, 0 },
        { "wl_buffer", 1, 1 },
        { "xdg_surface", 1, 1 },
        { "xdg_toplevel", 0, 1 }
    };
    int i;
    int k;
    if (!name)
        return WL_ERR_ID;
    for (i = 0; i < WL_IFACE_COUNT; i++) {
        k = 0;
        while (table[i].name[k] != '\0' && name[k] != '\0'
            && table[i].name[k] == name[k])
            k++;
        if (table[i].name[k] == '\0' && name[k] == '\0')
            return i;
    }
    return WL_ERR_ID;
}

/** Bind an attached buffer to a surface, keeping its position. The
 * pool id stands in for the passed fd miniOS cannot carry, validated
 * here before any pixel is ever addressed through it. */
static inline int wl_comp_attach_buf(wl_comp_t *c, unsigned int id,
        unsigned int pool, int w, int h) {
    int i;
    if (!c)
        return WL_ERR_BOUND;
    if (!wl_surface_id_valid(id))
        return WL_ERR_ID;
    if (!wl_pool_id_valid(pool))
        return WL_ERR_ID;
    if (wl_pool_fit(w, h) != WL_ERR_OK)
        return WL_ERR_BOUND;
    for (i = 0; i < WL_MAX_SURFACES; i++) {
        if (c->items[i].id == id) {
            c->items[i].w = w;
            c->items[i].h = h;
            c->items[i].pool = pool;
            c->items[i].mapped = 1;
            return WL_ERR_OK;
        }
    }
    return WL_ERR_ID;
}

/** Route one framed request to the compositor state, the protocol.c
 * plus server.c shape collapsed into one pure function. Unknown ids
 * name strangers, unknown opcodes name unimplemented verbs, short
 * payloads never reach the surface they address. */
static inline int wl_dispatch(wl_comp_t *c, wl_client_t *cl,
        unsigned int id, unsigned int opcode,
        const unsigned char *arg, int alen) {
    unsigned int pool = 0;
    unsigned int nid = 0;
    int w = 0;
    int h = 0;
    int r;
    int i;
    if (!c || !cl)
        return WL_ERR_BOUND;
    if (id == WL_ID_DISPLAY) {
        if (opcode == WL_OP_DISPLAY_GET_REGISTRY || opcode == 0)
            return WL_ERR_OK;
        return WL_ERR_BOUND;
    }
    if (id == WL_ID_REGISTRY) {
        if (opcode != WL_OP_REGISTRY_BIND)
            return WL_ERR_BOUND;
        if (!arg || alen < 4)
            return WL_ERR_BOUND;
        return WL_ERR_OK;
    }
    if (id == WL_ID_COMPOSITOR) {
        if (opcode != WL_OP_COMPOSITOR_CREATE_SURFACE)
            return WL_ERR_BOUND;
        if (wl_client_surface(cl, &nid) != WL_ERR_OK)
            return WL_ERR_BOUND;
        if (wl_comp_add(c, nid, 64, 64) != WL_ERR_OK)
            return WL_ERR_BOUND;
        return WL_ERR_OK;
    }
    if (id == WL_ID_SHM) {
        if (opcode != WL_OP_SHM_CREATE_POOL)
            return WL_ERR_BOUND;
        if (wl_client_pool(cl, &nid) != WL_ERR_OK)
            return WL_ERR_BOUND;
        return WL_ERR_OK;
    }
    if (id == WL_ID_XDG_BASE) {
        if (opcode != WL_OP_XDG_GET_TOPLEVEL)
            return WL_ERR_BOUND;
        return WL_ERR_OK;
    }
    if (wl_surface_id_valid(id)) {
        if (opcode == WL_OP_SURFACE_ATTACH) {
            if (!arg || alen < WL_ATTACH_SZ)
                return WL_ERR_BOUND;
            r = wl_attach_decode(arg, alen, &pool, &w, &h);
            if (r != WL_ERR_OK)
                return r;
            return wl_comp_attach_buf(c, id, pool, w, h);
        }
        if (opcode == WL_OP_SURFACE_COMMIT) {
            for (i = 0; i < WL_MAX_SURFACES; i++) {
                if (c->items[i].id == id) {
                    c->items[i].mapped = 1;
                    return WL_ERR_OK;
                }
            }
            return WL_ERR_ID;
        }
        return WL_ERR_BOUND;
    }
    if (wl_pool_id_valid(id)) {
        if (opcode != WL_OP_POOL_CREATE_BUFFER)
            return WL_ERR_BOUND;
        return WL_ERR_OK;
    }
    if (id >= WL_ID_BUFFER_BASE && id < WL_ID_BUFFER_BASE + WL_MAX_POOLS) {
        if (opcode != 0)
            return WL_ERR_BOUND;
        return WL_ERR_OK;
    }
    return WL_ERR_ID;
}

#endif
