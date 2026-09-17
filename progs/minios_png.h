/** Docstring: shared ring-3 PNG helpers for MiniOS apps (progs/minios_png.h).
 *
 * Header-only, single-file contract. Owns every PNG-adjacent bound and the
 * side-art policy so file.c, paint.c and the pokemon platform layer never
 * duplicate decode, nearest-palette or scale-blit logic again.
 *
 * Scope: pure helpers only, no stb_image and no syscalls inside. Callers
 * decode with stb_image (STBI_ONLY_PNG, STBI_NO_STDIO) and pass RGB bytes
 * in; this header maps and places them. File reads use plain stdio with a
 * byte cap, so a hostile archive or a multi-megapixel root PNG fails
 * closed instead of exhausting the heap.
 *
 * Side-art policy: the pokemon right fringe always shows the pokemon icon
 * and the left fringe shows the first decodable candidate below. Paths
 * point at /icons (the 32x32 RGBA build of each repo-root source via
 * tools/gen_desktop_pngs.py), never at the multi-megapixel roots, so no
 * guest decode can exceed MPNG_FILE_MAX. cgoblin (the 1024x1024 wallpaper
 * source) is deliberately absent from every candidate list.
 */

#ifndef MINIOS_PNG_H
#define MINIOS_PNG_H

#include <stdio.h>
#include <stdlib.h>

/** Central configuration: every bound, path and limit lives here. */
#define MPNG_FILE_MAX 1048576L
#define MPNG_MAX_DIM 512
#define MPNG_PAL_N 256L
#define MPNG_PAL_BYTES 768L
#define MPNG_PATH_MAX 64
#define MPNG_RIGHT_PATH "/icons/pokemon.png"
#define MPNG_LEFT_N 10
#define MPNG_ERR_OK 0
#define MPNG_ERR_BOUND (-1)
#define MPNG_ERR_EMPTY (-2)

/** Left-fringe candidates in probe order, repo-root art except cgoblin. */
static const char *mpng_left_candidates[MPNG_LEFT_N] = {
    "/icons/doom.png",
    "/icons/doomedit.png",
    "/icons/quake2.png",
    "/icons/piano.png",
    "/icons/nuklear.png",
    "/icons/vedit.png",
    "/icons/file.png",
    "/icons/shell.png",
    "/icons/paint.png",
    "/icons/minicraft.png"
};

/** Docstring: direct 3-3-2 index for one RGB triple, the pokemon ramp. */
static int mpng_332_idx(unsigned r, unsigned g, unsigned b) {
    return (int)(((r & 0xE0u)) | (((g & 0xE0u) >> 3)) | (((b & 0xC0u) >> 6)));
}

/** Docstring: nearest palette index by squared RGB distance, fail closed. */
static int mpng_nearest(const unsigned char *pal, long pal_n, unsigned r,
                        unsigned g, unsigned b) {
    long k;
    long best = -1;
    long bd = 0x7FFFFFFFL;
    if (!pal || pal_n <= 0 || pal_n > MPNG_PAL_N)
        return -1;
    for (k = 0; k < pal_n; k++) {
        long dr = (long)pal[k * 3] - (long)r;
        long dg = (long)pal[k * 3 + 1] - (long)g;
        long db = (long)pal[k * 3 + 2] - (long)b;
        long d = dr * dr + dg * dg + db * db;
        if (d < bd) {
            bd = d;
            best = k;
        }
    }
    return (int)best;
}

/** Docstring: centered offset of inner inside outer, negative when unfit. */
static int mpng_center(int outer, int inner) {
    if (outer < 0 || inner < 0)
        return -1;
    if (inner > outer)
        return -1;
    return (outer - inner) / 2;
}

/** Docstring: integer scale that fits src inside a box, at least 1. */
static int mpng_fit_scale(int sw, int sh, int boxw, int boxh) {
    int s = 1;
    int best = 1;
    if (sw <= 0 || sh <= 0 || boxw <= 0 || boxh <= 0)
        return -1;
    for (s = 1; s <= boxw && s <= boxh; s++) {
        if (sw * s <= boxw && sh * s <= boxh)
            best = s;
        else
            break;
    }
    return best;
}

/** Docstring: scale RGB into indexed dst with nearest neighbour. */
static int mpng_rgb_to_idx_scaled(const unsigned char *rgb, int sw, int sh,
                                  const unsigned char *pal, long pal_n,
                                  unsigned char *dst, int dw, int dh) {
    int x;
    int y;
    if (!rgb || !pal || !dst)
        return MPNG_ERR_BOUND;
    if (sw <= 0 || sh <= 0 || dw <= 0 || dh <= 0)
        return MPNG_ERR_BOUND;
    if (sw > MPNG_MAX_DIM || sh > MPNG_MAX_DIM)
        return MPNG_ERR_BOUND;
    if (dw > MPNG_MAX_DIM || dh > MPNG_MAX_DIM)
        return MPNG_ERR_BOUND;
    if (pal_n <= 0 || pal_n > MPNG_PAL_N)
        return MPNG_ERR_BOUND;
    for (y = 0; y < dh; y++) {
        int sy = y * sh / dh;
        for (x = 0; x < dw; x++) {
            int sx = x * sw / dw;
            const unsigned char *p = rgb + (sy * sw + sx) * 3;
            int v = mpng_nearest(pal, pal_n, p[0], p[1], p[2]);
            if (v < 0)
                return MPNG_ERR_BOUND;
            dst[y * dw + x] = (unsigned char)v;
        }
    }
    return MPNG_ERR_OK;
}

/** Docstring: scale RGB into 3-3-2 indexed dst with nearest neighbour. */
static int mpng_rgb_to_332_scaled(const unsigned char *rgb, int sw, int sh,
                                  unsigned char *dst, int dw, int dh) {
    int x;
    int y;
    if (!rgb || !dst)
        return MPNG_ERR_BOUND;
    if (sw <= 0 || sh <= 0 || dw <= 0 || dh <= 0)
        return MPNG_ERR_BOUND;
    if (sw > MPNG_MAX_DIM || sh > MPNG_MAX_DIM)
        return MPNG_ERR_BOUND;
    if (dw > MPNG_MAX_DIM || dh > MPNG_MAX_DIM)
        return MPNG_ERR_BOUND;
    for (y = 0; y < dh; y++) {
        int sy = y * sh / dh;
        for (x = 0; x < dw; x++) {
            int sx = x * sw / dw;
            const unsigned char *p = rgb + (sy * sw + sx) * 3;
            dst[y * dw + x] = (unsigned char)mpng_332_idx(p[0], p[1], p[2]);
        }
    }
    return MPNG_ERR_OK;
}

/** Docstring: blit an indexed tile into an indexed frame, clipped. */
static int mpng_blit_idx(unsigned char *fb, int fw, int fh,
                         const unsigned char *tile, int tw, int th,
                         int ox, int oy) {
    int x;
    int y;
    if (!fb || !tile)
        return MPNG_ERR_BOUND;
    if (fw <= 0 || fh <= 0 || tw <= 0 || th <= 0)
        return MPNG_ERR_BOUND;
    if (tw > MPNG_MAX_DIM || th > MPNG_MAX_DIM)
        return MPNG_ERR_BOUND;
    for (y = 0; y < th; y++) {
        int dy = oy + y;
        if (dy < 0 || dy >= fh)
            continue;
        for (x = 0; x < tw; x++) {
            int dx = ox + x;
            if (dx < 0 || dx >= fw)
                continue;
            fb[dy * fw + dx] = tile[y * tw + x];
        }
    }
    return MPNG_ERR_OK;
}

/** Docstring: bounded whole-file read, malloced, caller frees. */
static int mpng_load_file(const char *path, unsigned char **out, long *out_n,
                          long cap) {
    FILE *f;
    long sz;
    unsigned char *buf;
    if (!path || !path[0] || !out || !out_n)
        return MPNG_ERR_BOUND;
    if (cap <= 0 || cap > MPNG_FILE_MAX)
        return MPNG_ERR_BOUND;
    f = fopen(path, "rb");
    if (!f)
        return MPNG_ERR_EMPTY;
    fseek(f, 0, SEEK_END);
    sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (sz <= 0 || sz > cap) {
        fclose(f);
        return MPNG_ERR_BOUND;
    }
    buf = (unsigned char *)malloc((unsigned long)sz);
    if (!buf) {
        fclose(f);
        return MPNG_ERR_BOUND;
    }
    if (fread(buf, 1, (unsigned long)sz, f) != (unsigned long)sz) {
        free(buf);
        fclose(f);
        return MPNG_ERR_BOUND;
    }
    fclose(f);
    *out = buf;
    *out_n = sz;
    return MPNG_ERR_OK;
}

#endif
