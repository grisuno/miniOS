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
#define WL_POOL_MAX (800 * 360)
#define WL_HDR_SZ 8

#define WL_ERR_OK 0
#define WL_ERR_BOUND (-1)
#define WL_ERR_TRUNC (-2)
#define WL_ERR_SIZE (-3)
#define WL_ERR_ID (-4)
#define WL_ERR_STR (-5)

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
    dst[4] = (unsigned char)(opcode & 0xFFu);
    dst[5] = (unsigned char)((size >> 8) & 0xFFu);
    dst[6] = (unsigned char)(size & 0xFFu);
    dst[7] = (unsigned char)((size >> 8) & 0xFFu);
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
    if (w <= 0 || h <= 0 || w > 800 || h > 360)
        return WL_ERR_BOUND;
    n = (long)w * (long)h;
    if (n > (long)WL_POOL_MAX)
        return WL_ERR_BOUND;
    return WL_ERR_OK;
}

typedef struct {
    unsigned int id;
    int x;
    int y;
    int w;
    int h;
    int mapped;
    unsigned int pool;
    int color;
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
        c->order[i] = 0;
    }
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
            c->order[c->count] = (unsigned int)i;
            c->count++;
            c->focus = i;
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
            return WL_ERR_OK;
        }
    }
    return WL_ERR_ID;
}

static inline int wl_comp_hit(const wl_comp_t *c, int x, int y) {    int i;
    if (!c)
        return -1;
    for (i = c->count - 1; i >= 0; i--) {
        const wl_surface_t *s = &c->items[c->order[i]];
        if (!s->mapped)
            continue;
        if (x >= s->x && x < s->x + s->w && y >= s->y && y < s->y + s->h)
            return (int)s->id;
    }
    return -1;
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
        if (!s->mapped)
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

#endif
