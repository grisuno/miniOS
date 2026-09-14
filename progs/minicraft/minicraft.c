/* minicraft.c - Minecraft-like voxel walker for MiniOS (ring 3, static ELF).
 *
 * Renders a 64x64x32 block world into the 320x200 game back-buffer at
 * MINIOS_DOOM_BACKBUF_ADDR and presents it with MINIOS_SYS_GFX_PRESENT /
 * MINIOS_GFX_BUF_GAME, exactly like DOOM and Quake 2. Palette, keyboard,
 * mouse, time and VGA mode all arrive through the canonical syscall table
 * in minios_abi.h; no address or number is hardcoded here.
 *
 * Engine: per-pixel DDA voxel raycaster (Amanatides & Woo) with integer
 * traversal and float ray setup. Face shading (top/side/bottom) plus
 * distance fog to sky. Physics: AABB player with gravity, jump and
 * axis-separated collision. Interaction: left click breaks, right click
 * places the selected hotbar block (raycast up to 6 blocks).
 *
 * Headless proofs (same contract as DOOM/Q2G):
 *   minicraft --selftest        builds world, renders one frame, checks pixels
 *   minicraft autoframes <n>    renders n frames with a slow yaw spin, exits 0
 * Both make `gfx frames` climb so the BDD suite observes real rendering.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "minios_abi.h"

#define MC_W 64
#define MC_D 64
#define MC_H 32
#define MC_WORLD (MC_W * MC_D * MC_H)

#define FB_W MINIOS_DOOM_W
#define FB_H MINIOS_DOOM_H
#ifdef MINICRAFT_HOST_TEST
static unsigned char host_fb[MINIOS_DOOM_W * MINIOS_DOOM_H];
#define BACKBUF ((volatile unsigned char *)host_fb)
#else
#define BACKBUF ((volatile unsigned char *)MINIOS_DOOM_BACKBUF_ADDR)
#endif

#define SAVE_PATH "/saves/minicraft.map"

enum {
    B_AIR = 0,
    B_GRASS = 1,
    B_DIRT = 2,
    B_STONE = 3,
    B_LOG = 4,
    B_LEAVES = 5,
    B_SAND = 6,
    B_PLANKS = 7,
    B_GLASS = 8,
    B_BRICK = 9,
    B_WATER = 10,
    B_BEDROCK = 11,
    B_COUNT = 12
};

static unsigned char world[MC_W * MC_D * MC_H];

static float pl_x, pl_y, pl_z;
static float pl_vz;
static float pl_yaw, pl_pitch;
static int pl_on_ground;
static int hotbar[9];
static int hot_sel;
static int mc_fly;
static long frame_ms;
static long last_act_ms;
static char last_act[16];
static int inv[B_COUNT];
static int save_world(void);
static void gen_world(unsigned int seed);

static long s_time_ms(void) {
    long r;
    __asm__ volatile("syscall" : "=a"(r) : "a"(MINIOS_SYS_TIME), "D"(0) : "rcx", "r11", "memory");
    return r;
}
static long s_kbd(void) {
    long r;
    __asm__ volatile("syscall" : "=a"(r) : "a"(MINIOS_SYS_KBD), "D"(0) : "rcx", "r11", "memory");
    return r;
}
static long s_kbd_raw(long on) {
    long r;
    __asm__ volatile("syscall" : "=a"(r) : "a"(MINIOS_SYS_KBD_RAW), "D"(on) : "rcx", "r11", "memory");
    return r;
}
static long s_vga(long on) {
    long r;
    __asm__ volatile("syscall" : "=a"(r) : "a"(MINIOS_SYS_VGA_MODE), "D"(on) : "rcx", "r11", "memory");
    return r;
}
static long s_pal(const unsigned char *p) {
    long r;
    __asm__ volatile("syscall" : "=a"(r) : "a"(MINIOS_SYS_PALETTE), "D"(p) : "rcx", "r11", "memory");
    return r;
}
static long s_present(void) {
    long r;
    __asm__ volatile("syscall" : "=a"(r) : "a"(MINIOS_SYS_GFX_PRESENT), "D"((long)MINIOS_GFX_BUF_GAME), "S"((long)0) : "rcx", "r11", "memory");
    return r;
}
static long s_title(const char *t) {
    long r;
    __asm__ volatile("syscall" : "=a"(r) : "a"(MINIOS_SYS_GFX_SET_TITLE), "D"(t) : "rcx", "r11", "memory");
    return r;
}
static long s_mouse(int *m) {
    long r;
    __asm__ volatile("syscall" : "=a"(r) : "a"(MINIOS_SYS_MOUSE), "D"(m) : "rcx", "r11", "memory");
    return r;
}
static void s_yield(void) {
    long r;
    __asm__ volatile("syscall" : "=a"(r) : "a"(MINIOS_SYS_SCHED_YIELD), "D"(0) : "rcx", "r11", "memory");
    (void)r;
}

static unsigned char mc_pal[768];

static void pal_set(int i, int r, int g, int b) {
    mc_pal[i * 3 + 0] = (unsigned char)r;
    mc_pal[i * 3 + 1] = (unsigned char)g;
    mc_pal[i * 3 + 2] = (unsigned char)b;
}

static void build_palette(void) {
    int i;
    for (i = 0; i < 256; i++) {
        mc_pal[i * 3 + 0] = 0;
        mc_pal[i * 3 + 1] = 0;
        mc_pal[i * 3 + 2] = 0;
    }
    pal_set(0, 110, 170, 250);
    pal_set(1, 150, 200, 255);
    pal_set(2, 255, 255, 255);
    pal_set(3, 20, 20, 20);
    pal_set(10, 106, 176, 64);
    pal_set(11, 88, 148, 52);
    pal_set(12, 70, 118, 42);
    pal_set(13, 121, 102, 61);
    pal_set(14, 100, 84, 50);
    pal_set(15, 80, 66, 40);
    pal_set(16, 130, 130, 130);
    pal_set(17, 108, 108, 108);
    pal_set(18, 86, 86, 86);
    pal_set(19, 96, 76, 46);
    pal_set(20, 80, 62, 38);
    pal_set(21, 64, 50, 30);
    pal_set(22, 150, 120, 70);
    pal_set(23, 125, 100, 58);
    pal_set(24, 100, 80, 46);
    pal_set(25, 52, 130, 44);
    pal_set(26, 42, 108, 36);
    pal_set(27, 34, 86, 28);
    pal_set(28, 222, 212, 162);
    pal_set(29, 190, 180, 138);
    pal_set(30, 155, 146, 112);
    pal_set(31, 172, 142, 82);
    pal_set(32, 146, 120, 70);
    pal_set(33, 118, 96, 56);
    pal_set(34, 205, 235, 255);
    pal_set(35, 175, 200, 220);
    pal_set(36, 140, 160, 180);
    pal_set(37, 152, 82, 72);
    pal_set(38, 128, 68, 60);
    pal_set(39, 102, 54, 48);
    pal_set(40, 70, 130, 225);
    pal_set(41, 58, 108, 190);
    pal_set(42, 46, 86, 150);
    pal_set(43, 62, 62, 62);
    pal_set(44, 52, 52, 52);
    pal_set(45, 42, 42, 42);
    pal_set(50, 90, 60, 30);
    pal_set(51, 60, 40, 20);
    pal_set(60, 200, 60, 60);
}

static int widx(int x, int y, int z) {
    return (z * MC_D + y) * MC_W + x;
}

static int in_world(int x, int y, int z) {
    return x >= 0 && x < MC_W && y >= 0 && y < MC_D && z >= 0 && z < MC_H;
}

static unsigned char get_b(int x, int y, int z) {
    if (!in_world(x, y, z))
        return B_AIR;
    return world[widx(x, y, z)];
}

static int col_top[MC_W * MC_D];

static void col_recompute(int x, int y) {
    int z;
    int t = -1;
    for (z = MC_H - 1; z >= 0; z--) {
        if (world[widx(x, y, z)] != B_AIR) {
            t = z;
            break;
        }
    }
    col_top[y * MC_W + x] = t;
}

static void set_b(int x, int y, int z, unsigned char b) {
    if (!in_world(x, y, z))
        return;
    world[widx(x, y, z)] = b;
    col_recompute(x, y);
}

static void set_b_raw(int x, int y, int z, unsigned char b) {
    if (!in_world(x, y, z))
        return;
    world[widx(x, y, z)] = b;
}

static void light_build(void) {
    int x, y;
    for (y = 0; y < MC_D; y++) {
        for (x = 0; x < MC_W; x++)
            col_recompute(x, y);
    }
}

/* skylight 1.0 at surface fading to 0.22 deep: O(1) via column tops */
static float sky_light(int x, int y, int z) {
    int d;
    float l;
    if (!in_world(x, y, z))
        return 1.0f;
    d = col_top[y * MC_W + x] - z;
    if (d <= 0)
        return 1.0f;
    l = 1.0f - (float)d / 10.0f;
    if (l < 0.22f)
        l = 0.22f;
    return l;
}

static int is_solid(unsigned char b) {
    return b != B_AIR && b != B_WATER;
}

static int is_visible(unsigned char b) {
    return b != B_AIR;
}

static unsigned int hash2(int x, int y) {
    unsigned int h = (unsigned int)x * 374761393u + (unsigned int)y * 668265263u;
    h = (h ^ (h >> 13)) * 1274126177u;
    h ^= h >> 16;
    return h;
}

static int ground_h(int x, int y) {
    unsigned int a = hash2(x, y) % 100;
    unsigned int b = hash2(x / 4, y / 4) % 100;
    unsigned int c = hash2(x / 9 + 7, y / 9 + 3) % 100;
    int h = 10 + (int)(a * 3 + b * 6 + c * 8) / 100;
    if (h < 4)
        h = 4;
    if (h > MC_H - 10)
        h = MC_H - 10;
    return h;
}

static void gen_world(unsigned int seed) {
    int x, y, z;
    (void)seed;
    memset(world, 0, sizeof(world));
    for (y = 0; y < MC_D; y++) {
        for (x = 0; x < MC_W; x++) {
            int h = ground_h(x, y);
            for (z = 0; z <= h; z++) {
                unsigned char b;
                if (z == 0)
                    b = B_BEDROCK;
                else if (z == h && h <= 8)
                    b = B_SAND;
                else if (z == h)
                    b = B_GRASS;
                else if (z >= h - 2)
                    b = B_DIRT;
                else if (z >= h - 5)
                    b = B_STONE;
                else
                    b = (hash2(x * 3 + z, y * 5 - z) % 7 == 0) ? B_DIRT : B_STONE;
                set_b_raw(x, y, z, b);
            }
            if (h > 8 && hash2(x, y) % 97 < 3) {
                int th = h + 4;
                int k;
                if (th >= MC_H - 1)
                    th = MC_H - 2;
                for (k = h + 1; k <= th; k++)
                    set_b_raw(x, y, k, B_LOG);
                for (k = th - 1; k <= th + 1; k++) {
                    int dx, dy;
                    for (dy = -2; dy <= 2; dy++) {
                        for (dx = -2; dx <= 2; dx++) {
                            if (dx == 0 && dy == 0 && k <= th)
                                continue;
                            if (dx * dx + dy * dy > 5 && k == th + 1)
                                continue;
                            if (get_b(x + dx, y + dy, k) == B_AIR)
                                set_b_raw(x + dx, y + dy, k, B_LEAVES);
                        }
                    }
                }
            }
            if (h <= 8) {
                for (z = h + 1; z <= 8; z++)
                    set_b_raw(x, y, z, B_WATER);
            }
        }
    }
    light_build();
    {
        int sx = MC_W / 2, sy = MC_D / 2;
        int tries, best_h = -1;
        for (tries = 0; tries < 40; tries++) {
            int tx = MC_W / 2 + (tries * 7) % 17 - 8;
            int ty = MC_D / 2 + (tries * 11) % 17 - 8;
            int dx, dy, clear = 1;
            if (tx < 2 || ty < 2 || tx >= MC_W - 2 || ty >= MC_D - 2)
                continue;
            for (dy = -2; dy <= 2 && clear; dy++) {
                for (dx = -2; dx <= 2 && clear; dx++) {
                    int h = ground_h(tx + dx, ty + dy);
                    int k;
                    for (k = h + 1; k <= h + 4; k++) {
                        unsigned char b = get_b(tx + dx, ty + dy, k);
                        if (b == B_LOG || b == B_LEAVES)
                            clear = 0;
                    }
                }
            }
            if (clear) {
                sx = tx;
                sy = ty;
                break;
            }
        }
        pl_x = (float)sx + 0.5f;
        pl_y = (float)sy + 0.5f;
        {
            int gz = 0;
            for (z = MC_H - 1; z > 0; z--) {
                if (is_solid(get_b(sx, sy, z))) {
                    gz = z;
                    break;
                }
            }
            best_h = gz;
            pl_z = (float)gz + 1.02f;
        }
        (void)best_h;
    }
    pl_yaw = 0.7f;
    pl_pitch = -0.05f;
    pl_vz = 0;
    pl_on_ground = 1;
    hotbar[0] = B_GRASS;
    hotbar[1] = B_DIRT;
    hotbar[2] = B_STONE;
    hotbar[3] = B_PLANKS;
    hotbar[4] = B_LOG;
    hotbar[5] = B_LEAVES;
    hotbar[6] = B_SAND;
    hotbar[7] = B_BRICK;
    hotbar[8] = B_GLASS;
    hot_sel = 0;
}

static unsigned char face_color(unsigned char b, int face) {
    switch (b) {
    case B_GRASS:
        if (face == 4)
            return 10;
        if (face == 5)
            return 13;
        return 11;
    case B_DIRT:
        return face == 4 ? 13 : (face == 5 ? 15 : 14);
    case B_STONE:
        return face == 4 ? 16 : (face == 5 ? 18 : 17);
    case B_LOG:
        if (face == 4 || face == 5)
            return 22;
        return face >= 2 ? 20 : 19;
    case B_LEAVES:
        return face == 4 ? 25 : (face == 5 ? 27 : 26);
    case B_SAND:
        return face == 4 ? 28 : (face == 5 ? 30 : 29);
    case B_PLANKS:
        return face == 4 ? 31 : (face == 5 ? 33 : 32);
    case B_GLASS:
        return face == 4 ? 34 : (face == 5 ? 36 : 35);
    case B_BRICK:
        return face == 4 ? 37 : (face == 5 ? 39 : 38);
    case B_WATER:
        return face == 4 ? 40 : (face == 5 ? 42 : 41);
    case B_BEDROCK:
        return face == 4 ? 43 : (face == 5 ? 45 : 44);
    default:
        return 17;
    }
}

typedef struct {
    int hit;
    int bx, by, bz;
    int px, py, pz;
    int face;
    float dist;
} RayHit;

static RayHit cast_ray(float ox, float oy, float oz, float dx, float dy, float dz, float maxd) {
    RayHit h;
    int ix = (int)floorf(ox);
    int iy = (int)floorf(oy);
    int iz = (int)floorf(oz);
    int stepx = dx > 0 ? 1 : -1;
    int stepy = dy > 0 ? 1 : -1;
    int stepz = dz > 0 ? 1 : -1;
    float tdx = dx != 0 ? fabsf(1.0f / dx) : 1e30f;
    float tdy = dy != 0 ? fabsf(1.0f / dy) : 1e30f;
    float tdz = dz != 0 ? fabsf(1.0f / dz) : 1e30f;
    float tmx = dx != 0 ? ((stepx > 0 ? (ix + 1 - ox) : (ox - ix)) * tdx) : 1e30f;
    float tmy = dy != 0 ? ((stepy > 0 ? (iy + 1 - oy) : (oy - iy)) * tdy) : 1e30f;
    float tmz = dz != 0 ? ((stepz > 0 ? (iz + 1 - oz) : (oz - iz)) * tdz) : 1e30f;
    int face = 4;
    float t = 0;
    int i;
    memset(&h, 0, sizeof(h));
    for (i = 0; i < 128; i++) {
        if (tmx < tmy && tmx < tmz) {
            ix += stepx;
            t = tmx;
            tmx += tdx;
            face = 0;
        } else if (tmy < tmz) {
            iy += stepy;
            t = tmy;
            tmy += tdy;
            face = 2;
        } else {
            iz += stepz;
            t = tmz;
            tmz += tdz;
            face = dz > 0 ? 5 : 4;
        }
        if (t > maxd)
            return h;
        if (!in_world(ix, iy, iz)) {
            if (iz < 0 || iz >= MC_H)
                return h;
            continue;
        }
        if (is_visible(get_b(ix, iy, iz))) {
            h.hit = 1;
            h.bx = ix;
            h.by = iy;
            h.bz = iz;
            h.face = face;
            h.dist = t;
            h.px = ix - stepx * (face == 0);
            h.py = iy - stepy * (face == 2);
            h.pz = iz - stepz * (face == 4 || face == 5);
            if (face == 0) {
                h.px = ix - stepx;
                h.py = iy;
                h.pz = iz;
            } else if (face == 2) {
                h.px = ix;
                h.py = iy - stepy;
                h.pz = iz;
            } else {
                h.px = ix;
                h.py = iy;
                h.pz = iz - stepz;
            }
            return h;
        }
    }
    return h;
}

#define MC_EYE 1.55f

static float eye_z(void) {
    return pl_z + MC_EYE;
}

/* ---- tiny 3x5 pixel font for the in-game HUD ---- */
static const unsigned char mc_font[][5] = {
    { 0x0, 0x0, 0x0, 0x0, 0x0 }, /* space */
    { 0x2, 0x2, 0x2, 0x0, 0x2 }, /* ! */
    { 0x0, 0x0, 0x0, 0x0, 0x0 }, /* " */
    { 0x0, 0x0, 0x0, 0x0, 0x0 }, /* # */
    { 0x0, 0x0, 0x0, 0x0, 0x0 }, /* $ */
    { 0x5, 0x1, 0x2, 0x4, 0x5 }, /* % */
    { 0x0, 0x0, 0x0, 0x0, 0x0 }, /* & */
    { 0x0, 0x0, 0x0, 0x0, 0x0 }, /* ' */
    { 0x2, 0x4, 0x4, 0x4, 0x2 }, /* ( */
    { 0x2, 0x1, 0x1, 0x1, 0x2 }, /* ) */
    { 0x0, 0x0, 0x0, 0x0, 0x0 }, /* * */
    { 0x0, 0x2, 0x7, 0x2, 0x0 }, /* + */
    { 0x0, 0x0, 0x0, 0x0, 0x0 }, /* , */
    { 0x0, 0x0, 0x7, 0x0, 0x0 }, /* - */
    { 0x0, 0x0, 0x0, 0x0, 0x2 }, /* . */
    { 0x1, 0x1, 0x2, 0x4, 0x4 }, /* / */
    { 0x7, 0x5, 0x5, 0x5, 0x7 }, /* 0 */
    { 0x2, 0x6, 0x2, 0x2, 0x7 }, /* 1 */
    { 0x7, 0x1, 0x7, 0x4, 0x7 }, /* 2 */
    { 0x7, 0x1, 0x7, 0x1, 0x7 }, /* 3 */
    { 0x5, 0x5, 0x7, 0x1, 0x1 }, /* 4 */
    { 0x7, 0x4, 0x7, 0x1, 0x7 }, /* 5 */
    { 0x7, 0x4, 0x7, 0x5, 0x7 }, /* 6 */
    { 0x7, 0x1, 0x1, 0x2, 0x2 }, /* 7 */
    { 0x7, 0x5, 0x7, 0x5, 0x7 }, /* 8 */
    { 0x7, 0x5, 0x7, 0x1, 0x7 }, /* 9 */
    { 0x0, 0x2, 0x0, 0x2, 0x0 }, /* : */
    { 0x0, 0x0, 0x0, 0x0, 0x0 }, /* ; */
    { 0x1, 0x2, 0x4, 0x2, 0x1 }, /* < */
    { 0x0, 0x0, 0x0, 0x0, 0x0 }, /* = */
    { 0x4, 0x2, 0x1, 0x2, 0x4 }, /* > */
    { 0x0, 0x0, 0x0, 0x0, 0x0 }, /* ? */
    { 0x0, 0x0, 0x0, 0x0, 0x0 }, /* @ */
    { 0x2, 0x5, 0x7, 0x5, 0x5 }, /* A */
    { 0x6, 0x5, 0x6, 0x5, 0x6 }, /* B */
    { 0x3, 0x4, 0x4, 0x4, 0x3 }, /* C */
    { 0x6, 0x5, 0x5, 0x5, 0x6 }, /* D */
    { 0x7, 0x4, 0x6, 0x4, 0x7 }, /* E */
    { 0x7, 0x4, 0x6, 0x4, 0x4 }, /* F */
    { 0x3, 0x4, 0x5, 0x5, 0x3 }, /* G */
    { 0x5, 0x5, 0x7, 0x5, 0x5 }, /* H */
    { 0x7, 0x2, 0x2, 0x2, 0x7 }, /* I */
    { 0x1, 0x1, 0x1, 0x5, 0x2 }, /* J */
    { 0x5, 0x5, 0x6, 0x5, 0x5 }, /* K */
    { 0x4, 0x4, 0x4, 0x4, 0x7 }, /* L */
    { 0x5, 0x7, 0x7, 0x5, 0x5 }, /* M */
    { 0x6, 0x5, 0x5, 0x5, 0x5 }, /* N */
    { 0x2, 0x5, 0x5, 0x5, 0x2 }, /* O */
    { 0x6, 0x5, 0x6, 0x4, 0x4 }, /* P */
    { 0x2, 0x5, 0x5, 0x6, 0x3 }, /* Q */
    { 0x6, 0x5, 0x6, 0x5, 0x5 }, /* R */
    { 0x3, 0x4, 0x2, 0x1, 0x6 }, /* S */
    { 0x7, 0x2, 0x2, 0x2, 0x2 }, /* T */
    { 0x5, 0x5, 0x5, 0x5, 0x7 }, /* U */
    { 0x5, 0x5, 0x5, 0x5, 0x2 }, /* V */
    { 0x5, 0x5, 0x7, 0x7, 0x5 }, /* W */
    { 0x5, 0x5, 0x2, 0x5, 0x5 }, /* X */
    { 0x5, 0x5, 0x2, 0x2, 0x2 }, /* Y */
    { 0x7, 0x1, 0x2, 0x4, 0x7 }, /* Z */
};

static int mc_glyph(char ch) {
    if (ch >= 'a' && ch <= 'z')
        ch = (char)(ch - 'a' + 'A');
    if (ch < ' ' || ch > 'Z')
        return 0;
    return ch - ' ';
}

static void mc_pixel(int x, int y, unsigned char c) {
    if (x < 0 || x >= FB_W || y < 0 || y >= FB_H)
        return;
    BACKBUF[y * FB_W + x] = c;
}

static void mc_text(int x, int y, const char *s, unsigned char fg) {
    for (; *s; s++, x += 4) {
        const unsigned char *g = mc_font[mc_glyph(*s)];
        int r, c;
        for (r = 0; r < 5; r++) {
            for (c = 0; c < 3; c++) {
                if (g[r] & (4 >> c))
                    mc_pixel(x + c, y + r, fg);
            }
        }
    }
}

static void mc_text_bg(int x, int y, const char *s, unsigned char fg, unsigned char bg) {
    int n = 0;
    const char *p;
    int r, i;
    for (p = s; *p; p++)
        n++;
    for (r = -1; r < 6; r++) {
        for (i = -1; i < n * 4; i++)
            mc_pixel(x + i, y + r, bg);
    }
    mc_text(x, y, s, fg);
}

static const char *mc_block_name(unsigned char b) {
    switch (b) {
    case B_GRASS: return "GRASS";
    case B_DIRT: return "DIRT";
    case B_STONE: return "STONE";
    case B_LOG: return "WOOD";
    case B_LEAVES: return "LEAVES";
    case B_SAND: return "SAND";
    case B_PLANKS: return "PLANKS";
    case B_GLASS: return "GLASS";
    case B_BRICK: return "BRICK";
    case B_WATER: return "WATER";
    case B_BEDROCK: return "BEDROCK";
    default: return "AIR";
    }
}

static char mc_facing(void) {
    float a = pl_yaw;
    while (a < 0)
        a += 6.2831853f;
    while (a >= 6.2831853f)
        a -= 6.2831853f;
    if (a < 0.7853982f || a >= 5.4977871f)
        return 'E';
    if (a < 2.3561945f)
        return 'N';
    if (a < 3.9269908f)
        return 'W';
    return 'S';
}

static void render_frame(void) {
    float cyaw = cosf(pl_yaw), syaw = sinf(pl_yaw);
    float cpit = cosf(pl_pitch), spit = sinf(pl_pitch);
    float ez = eye_z();
    float fdx = cyaw * cpit, fdy = syaw * cpit, fdz = spit;
    RayHit tgt = cast_ray(pl_x, pl_y, ez, fdx, fdy, fdz, 6.0f);
    int x, y;
    for (y = 0; y < FB_H; y++) {
        for (x = 0; x < FB_W; x++) {
            float nx = ((float)x / (float)FB_W * 2.0f - 1.0f) * 0.95f;
            float ny = (1.0f - (float)y / (float)FB_H * 2.0f) * 0.60f;
            float cx = nx;
            float cyy = 1.0f;
            float cz = ny;
            /* camera basis: forward=(cyaw,syaw,0), right=(syaw,-cyaw,0),
             * up=(0,0,1). Pitch rotates the forward/up plane, leaving the
             * right component fixed; W walks to the crosshair. */
            float f2 = cyy * cpit - cz * spit;
            float u2 = cyy * spit + cz * cpit;
            float dx = f2 * cyaw + cx * syaw;
            float dy2 = f2 * syaw - cx * cyaw;
            float dz2 = u2;
            float il = 1.0f / sqrtf(dx * dx + dy2 * dy2 + dz2 * dz2);
            dx *= il;
            dy2 *= il;
            dz2 *= il;
            {
                RayHit h = cast_ray(pl_x, pl_y, ez, dx, dy2, dz2, 60.0f);
                unsigned char c;
                if (!h.hit) {
                    /* sky glued to ray direction, never to the screen:
                     * the horizon band is the up/down reference */
                    if (dz2 > 0.35f)
                        c = 0;
                    else if (dz2 > 0.04f)
                        c = 1;
                    else if (dz2 > -0.04f)
                        c = 2;
                    else if (dz2 > -0.40f)
                        c = 30;
                    else
                        c = 44;
                    {
                        float sd = dx * 0.55f + dy2 * 0.35f + dz2 * 0.76f;
                        if (sd > 0.9985f)
                            c = 2;
                        else if (sd > 0.9965f)
                            c = 1;
                    }
                } else {
                    c = face_color(get_b(h.bx, h.by, h.bz), h.face);
                    {
                        float li = sky_light(h.bx, h.by, h.bz);
                        int hh = ((x * 73 + y * 149) & 7);
                        if ((float)hh >= li * 8.0f)
                            c = 3;
                    }
                    if (tgt.hit && h.bx == tgt.bx && h.by == tgt.by && h.bz == tgt.bz) {
                        if (((x + y) & 1) == 0)
                            c = 2;
                    } else if (h.dist > 34.0f) {
                        c = (h.dist > 48.0f) ? 1 : 0;
                    }
                }
                BACKBUF[y * FB_W + x] = c;
            }
        }
    }
    {
        char hud0[32], hud1[48];
        char fc = mc_facing();
        int ix = (int)pl_x, iy = (int)pl_y, iz = (int)pl_z;
        sprintf(hud0, "X%d Y%d Z%d F:%c", ix, iy, iz, fc);
        mc_text_bg(3, 3, hud0, 2, 3);
        {
            unsigned char sb = (unsigned char)hotbar[hot_sel];
            if (tgt.hit)
                sprintf(hud1, "T:%s %dM S:%sX%d W%d/10",
                        mc_block_name(get_b(tgt.bx, tgt.by, tgt.bz)),
                        (int)tgt.dist, mc_block_name(sb), inv[sb], inv[B_LOG]);
            else
                sprintf(hud1, "T:- S:%sX%d W%d/10", mc_block_name(sb), inv[sb], inv[B_LOG]);
        }
        mc_text_bg(3, 11, hud1, 2, 3);
        if (mc_fly)
            mc_text_bg(FB_W - 3 * 4 * 4, 3, "FLY", 2, 3);
        if (last_act[0] && frame_ms - last_act_ms < 2500)
            mc_text_bg(3, 27, last_act, 2, 3);
        {
            int px = (int)pl_x, py = (int)pl_y;
            if (px >= 0 && py >= 0 && px < MC_W && py < MC_D) {
                int top = col_top[py * MC_W + px];
                if (pl_z < (float)top - 1.5f)
                    mc_text_bg(3, 19, "T:SALIR", 2, 3);
            }
        }
    }
    {
        int cx = FB_W / 2, cyy = FB_H / 2;
        int i;
        long age = frame_ms - last_act_ms;
        for (i = -5; i <= 5; i++) {
            BACKBUF[cyy * FB_W + cx + i] = 2;
            BACKBUF[(cyy + i) * FB_W + cx] = 2;
        }
        BACKBUF[cyy * FB_W + cx] = 3;
        /* click pulse: the square hand that answers every click */
        if (last_act_ms != 0 && age >= 0 && age < 200) {
            int s = 4 + (int)(age / 25);
            int k;
            for (k = -s; k <= s; k++) {
                mc_pixel(cx + k, cyy - s, 2);
                mc_pixel(cx + k, cyy + s, 2);
                mc_pixel(cx - s, cyy + k, 2);
                mc_pixel(cx + s, cyy + k, 2);
            }
        }
    }
    {
        int slot_w = 20, slot_h = 16;
        int total = slot_w * 9 + 2 * 8;
        int x0 = (FB_W - total) / 2;
        int y0 = FB_H - slot_h - 3;
        int s;
        for (s = 0; s < 9; s++) {
            int sx = x0 + s * (slot_w + 2);
            int ix, iy;
            unsigned char bc = face_color((unsigned char)hotbar[s], 0);
            for (iy = 0; iy < slot_h; iy++) {
                for (ix = 0; ix < slot_w; ix++) {
                    int px = sx + ix, py = y0 + iy;
                    if (px < 0 || px >= FB_W || py < 0 || py >= FB_H)
                        continue;
                    if (ix == 0 || iy == 0 || ix == slot_w - 1 || iy == slot_h - 1)
                        BACKBUF[py * FB_W + px] = (s == hot_sel) ? 2 : 3;
                    else
                        BACKBUF[py * FB_W + px] = bc;
                }
            }
        }
    }
}

static int key_down[256];
static int ext_down[256];

static void poll_kbd(void) {
    for (;;) {
        long sc = s_kbd();
        if (sc < 0 || sc > 0xFFFF)
            break;
        if (sc == 0xE0) {
            long sc2 = s_kbd();
            if (sc2 < 0)
                break;
            {
                unsigned char r2 = (unsigned char)sc2;
                int press = !(r2 & 0x80);
                ext_down[r2 & 0x7F] = press;
            }
            continue;
        }
        {
            unsigned char r = (unsigned char)sc;
            int press = !(r & 0x80);
            key_down[r & 0x7F] = press;
            if (!press)
                continue;
            if ((r & 0x7F) >= 0x02 && (r & 0x7F) <= 0x0A)
                hot_sel = (r & 0x7F) - 0x02;
            if ((r & 0x7F) == 0x21) {
                mc_fly = !mc_fly;
                pl_vz = 0;
                printf("minicraft: fly %s\n", mc_fly ? "on" : "off");
            }
            if ((r & 0x7F) == 0x14) {
                int px = (int)pl_x, py = (int)pl_y;
                int gz = -1, z;
                if (px < 0)
                    px = 0;
                if (py < 0)
                    py = 0;
                if (px >= MC_W)
                    px = MC_W - 1;
                if (py >= MC_D)
                    py = MC_D - 1;
                for (z = MC_H - 1; z >= 0; z--) {
                    if (is_solid(get_b(px, py, z))) {
                        gz = z;
                        break;
                    }
                }
                if (gz >= 0) {
                    pl_z = (float)gz + 1.02f;
                    pl_vz = 0;
                    pl_on_ground = 1;
                    printf("minicraft: rescued to surface %d\n", gz + 1);
                }
            }
            if ((r & 0x7F) == 0x31) {
                gen_world(1);
                save_world();
                printf("minicraft: new world\n");
            }
            if ((r & 0x7F) == 0x2E && !mc_fly) {
                pl_pitch = 0;
                printf("minicraft: view leveled\n");
            }
            if ((r & 0x7F) == 0x19) {
                RayHit th = cast_ray(pl_x, pl_y, eye_z(),
                                     cosf(pl_yaw) * cosf(pl_pitch),
                                     sinf(pl_yaw) * cosf(pl_pitch),
                                     sinf(pl_pitch), 6.0f);
                printf("minicraft: pos %d %d %d yaw %.2f pitch %.2f tgt %s wood %d\n",
                       (int)pl_x, (int)pl_y, (int)pl_z, pl_yaw, pl_pitch,
                       th.hit ? mc_block_name(get_b(th.bx, th.by, th.bz)) : "-",
                       inv[B_LOG]);
            }
        }
    }
}

static int player_collides(float x, float y, float z) {
    float r = 0.3f, h = 1.7f;
    int x0 = (int)floorf(x - r), x1 = (int)floorf(x + r);
    int y0 = (int)floorf(y - r), y1 = (int)floorf(y + r);
    int z0 = (int)floorf(z), z1 = (int)floorf(z + h - 0.05f);
    int ix, iy, iz;
    for (iz = z0; iz <= z1; iz++) {
        for (iy = y0; iy <= y1; iy++) {
            for (ix = x0; ix <= x1; ix++) {
                if (is_solid(get_b(ix, iy, iz)))
                    return 1;
            }
        }
    }
    return 0;
}

static void move_axis(float nx, float ny, float nz) {
    if (!player_collides(nx, pl_y, pl_z))
        pl_x = nx;
    if (!player_collides(pl_x, ny, pl_z))
        pl_y = ny;
    if (!player_collides(pl_x, pl_y, nz)) {
        pl_z = nz;
        pl_on_ground = 0;
    } else {
        if (nz < pl_z)
            pl_on_ground = 1;
        pl_vz = 0;
    }
}

static void try_autostep(float tx, float ty) {
    float nz = pl_z + 1.02f;
    if (player_collides(tx, ty, pl_z) && !player_collides(tx, ty, nz)) {
        pl_x = tx;
        pl_y = ty;
        pl_z = nz;
        pl_on_ground = 1;
        pl_vz = 0;
    }
}

static void tick_player(float dt) {
    float sprint = (key_down[0x2A] || key_down[0x36] || key_down[0x1D]) ? 1.6f : 1.0f;
    float speed = (mc_fly ? 8.0f : 4.4f) * sprint;
    float fx = cosf(pl_yaw), fy = sinf(pl_yaw);
    float rx = -fy, ry = fx;
    float mx = 0, my = 0;
    float ox, oy;
    if (key_down[0x11])
        mx += fx, my += fy;
    if (key_down[0x1F])
        mx -= fx, my -= fy;
    if (key_down[0x1E])
        mx += rx, my += ry;
    if (key_down[0x20])
        mx -= rx, my -= ry;
    ox = pl_x;
    oy = pl_y;
    {
        float l = sqrtf(mx * mx + my * my);
        if (l > 0.01f) {
            mx = mx / l * speed * dt;
            my = my / l * speed * dt;
            move_axis(pl_x + mx, pl_y + my, pl_z);
            if (!mc_fly && pl_on_ground && pl_x == ox && pl_y == oy)
                try_autostep(ox + mx, oy + my);
        }
    }
    if (mc_fly) {
        if (key_down[0x39])
            move_axis(pl_x, pl_y, pl_z + 6.0f * dt);
        /* shift doubles as sprint already; sink with C */
        if (key_down[0x2E])
            move_axis(pl_x, pl_y, pl_z - 6.0f * dt);
        pl_vz = 0;
        pl_on_ground = 0;
    } else {
        if (key_down[0x39] && pl_on_ground) {
            pl_vz = 8.4f;
            pl_on_ground = 0;
        }
        pl_vz -= 25.0f * dt;
        if (pl_vz < -16.0f)
            pl_vz = -16.0f;
        move_axis(pl_x, pl_y, pl_z + pl_vz * dt);
    }
    if (pl_z < 1.0f) {
        pl_z = 1.0f;
        pl_vz = 0;
        pl_on_ground = 1;
    }
    if (ext_down[0x48])
        pl_pitch += 2.4f * dt;
    if (ext_down[0x50])
        pl_pitch -= 2.4f * dt;
    if (ext_down[0x4B])
        pl_yaw += 3.2f * dt;
    if (ext_down[0x4D])
        pl_yaw -= 3.2f * dt;
    if (pl_pitch > 1.25f)
        pl_pitch = 1.25f;
    if (pl_pitch < -1.25f)
        pl_pitch = -1.25f;
}

static int prev_buttons;
static long last_edit_ms;

static void tick_interact(void) {
    int m[4];
    float cyaw, syaw, cpit, spit;
    float dx, dy, dz;
    RayHit h;
    long now;
    if (s_mouse(m) != 0)
        return;
    {
        static int pmx = -1, pmy = -1;
        if (pmx >= 0) {
            int ddx = m[0] - pmx, ddy = m[1] - pmy;
            if (ddx > 60 || ddx < -60 || ddy > 60 || ddy < -60) {
                /* focus change / teleport: ignore this jump */
            } else {
                pl_yaw -= (float)ddx * 0.006f;
                pl_pitch -= (float)ddy * 0.006f;
                if (pl_pitch > 1.25f)
                    pl_pitch = 1.25f;
                if (pl_pitch < -1.25f)
                    pl_pitch = -1.25f;
            }
        }
        pmx = m[0];
        pmy = m[1];
        if (m[3] != 0) {
            hot_sel = (hot_sel + (m[3] > 0 ? 8 : 1)) % 9;
        }
    }
    now = s_time_ms();
    {
        int lb = m[2] & 1, rb = (m[2] & 2) != 0;
        int lb_edge = lb && !(prev_buttons & 1);
        int rb_edge = rb && !(prev_buttons & 2);
        int lb_hold = lb && (now - last_edit_ms >= 240);
        int rb_hold = rb && (now - last_edit_ms >= 220);
        if (!lb && !rb) {
            prev_buttons = m[2];
            return;
        }
        if (!lb_edge && !rb_edge && !lb_hold && !rb_hold) {
            prev_buttons = m[2];
            return;
        }
        cyaw = cosf(pl_yaw);
        syaw = sinf(pl_yaw);
        cpit = cosf(pl_pitch);
        spit = sinf(pl_pitch);
        dx = cyaw * cpit;
        dy = syaw * cpit;
        dz = spit;
        h = cast_ray(pl_x, pl_y, eye_z(), dx, dy, dz, 6.0f);
        if (!h.hit) {
            prev_buttons = m[2];
            return;
        }
        if (lb && (lb_edge || lb_hold)) {
            unsigned char b = get_b(h.bx, h.by, h.bz);
            if (b != B_BEDROCK && b != B_AIR) {
                set_b(h.bx, h.by, h.bz, B_AIR);
                if (b != B_WATER && inv[b] < 999)
                    inv[b]++;
                sprintf(last_act, "-%s", mc_block_name(b));
                last_act_ms = now;
                if (b == B_LOG && inv[b] == 10) {
                    printf("minicraft: GOAL firewood x10 DONE\n");
                    sprintf(last_act, "GOAL DONE");
                }
            }
            last_edit_ms = now;
        } else if (rb && (rb_edge || rb_hold)) {
            unsigned char there = in_world(h.px, h.py, h.pz)
                ? get_b(h.px, h.py, h.pz)
                : B_BEDROCK;
            if (there == B_AIR || there == B_WATER) {
                unsigned char nb = (unsigned char)hotbar[hot_sel];
                int ok = 0;
                if (inv[nb] <= 0) {
                    sprintf(last_act, "VACIO");
                    last_act_ms = now;
                } else {
                    if (!player_collides((float)h.px + 0.5f, (float)h.py + 0.5f, (float)h.pz))
                        ok = 1;
                    else if (pl_z > (float)h.pz + 1.0f || pl_z + 1.7f < (float)h.pz)
                        ok = 1;
                    if (ok) {
                        set_b(h.px, h.py, h.pz, nb);
                        inv[nb]--;
                        sprintf(last_act, "+%s", mc_block_name(nb));
                        last_act_ms = now;
                    }
                }
                last_edit_ms = now;
            }
        }
    }
    prev_buttons = m[2];
}

static int save_world(void) {
    FILE *f = fopen(SAVE_PATH, "wb");
    if (!f)
        return -1;
    if (fwrite(world, 1, sizeof(world), f) != sizeof(world)) {
        fclose(f);
        return -1;
    }
    {
        float st[6];
        st[0] = pl_x;
        st[1] = pl_y;
        st[2] = pl_z;
        st[3] = pl_yaw;
        st[4] = pl_pitch;
        st[5] = (float)hot_sel;
        fwrite(st, 1, sizeof(st), f);
        fwrite(inv, 1, sizeof(inv), f);
    }
    fclose(f);
    return 0;
}

static int load_world(void) {
    FILE *f = fopen(SAVE_PATH, "rb");
    if (!f)
        return -1;
    if (fread(world, 1, sizeof(world), f) != sizeof(world)) {
        fclose(f);
        return -1;
    }
    light_build();
    {
        float st[6];
        int i;
        for (i = 0; i < B_COUNT; i++)
            inv[i] = 0;
        if (fread(st, 1, sizeof(st), f) == sizeof(st)) {
            pl_x = st[0];
            pl_y = st[1];
            pl_z = st[2];
            pl_yaw = st[3];
            pl_pitch = st[4];
            hot_sel = (int)st[5] % 9;
            if (hot_sel < 0)
                hot_sel = 0;
        }
        if (fread(inv, 1, sizeof(inv), f) != sizeof(inv)) {
            for (i = 0; i < B_COUNT; i++)
                inv[i] = 0;
        }
        mc_fly = 0;
        pl_vz = 0;
        pl_on_ground = 0;
    }
    fclose(f);
    return 0;
}

static int selftest(void) {
    int n_solid = 0;
    int i;
    gen_world(1);
    build_palette();
    render_frame();
    for (i = 0; i < FB_W * FB_H; i++) {
        if (BACKBUF[i] != 0 && BACKBUF[i] != 1)
            n_solid++;
    }
    if (n_solid < 2000) {
        printf("minicraft: selftest FAIL (solid=%d)\n", n_solid);
        return 1;
    }
    {
        RayHit h = cast_ray(pl_x, pl_y, eye_z(), 0, 1, -0.2f, 60.0f);
        if (!h.hit) {
            printf("minicraft: selftest FAIL (no ground hit)\n");
            return 1;
        }
    }
    /* view/move alignment: W at yaw 0 must walk +X and the crosshair
     * must show a brick placed at +X (kills the 90-degree drift) */
    {
        int cx, cy, cz;
        pl_x = 32.5f;
        pl_y = 32.5f;
        pl_z = 20.02f;
        pl_yaw = 0;
        pl_pitch = 0;
        pl_vz = 0;
        pl_on_ground = 0;
        for (cx = 28; cx <= 37; cx++) {
            for (cy = 28; cy <= 37; cy++) {
                for (cz = 19; cz <= 23; cz++)
                    set_b_raw(cx, cy, cz, B_AIR);
            }
        }
        light_build();
        set_b(35, 32, 21, B_BRICK);
        memset(key_down, 0, sizeof(key_down));
        memset(ext_down, 0, sizeof(ext_down));
        key_down[0x11] = 1;
        tick_player(0.1f);
        key_down[0x11] = 0;
        if (pl_x <= 32.5f) {
            printf("minicraft: selftest FAIL (W does not advance)\n");
            return 1;
        }
        if (fabsf(pl_y - 32.5f) > 0.01f) {
            printf("minicraft: selftest FAIL (W strafes)\n");
            return 1;
        }
        render_frame();
        if (BACKBUF[100 * FB_W + 180] != 2) {
            printf("minicraft: selftest FAIL (crosshair off +X)\n");
            return 1;
        }
    }
    printf("minicraft: frame ok (%dx%d)\n", FB_W, FB_H);
    return 0;
}

#ifdef MINICRAFT_HOST_TEST
static int dumpstats(void) {
    int x, y;
    long top_sky = 0, top_ground = 0, bot_sky = 0, bot_ground = 0;
    gen_world(1);
    build_palette();
    render_frame();
    for (y = 40; y < 80; y++) {
        for (x = 0; x < FB_W; x++) {
            unsigned char c = host_fb[y * FB_W + x];
            if (c == 0 || c == 1)
                top_sky++;
            else if (c >= 10 && c <= 45)
                top_ground++;
        }
    }
    for (y = 120; y < 160; y++) {
        for (x = 0; x < FB_W; x++) {
            unsigned char c = host_fb[y * FB_W + x];
            if (c == 0 || c == 1)
                bot_sky++;
            else if (c >= 10 && c <= 45)
                bot_ground++;
        }
    }
    printf("minicraft: stats top_sky=%ld top_ground=%ld bot_sky=%ld bot_ground=%ld cross=%d\n",
           top_sky, top_ground, bot_sky, bot_ground, host_fb[100 * FB_W + 160]);
    if (top_sky > top_ground && bot_ground > bot_sky)
        printf("minicraft: orient ok (sky up, ground down)\n");
    else
        printf("minicraft: orient level-view terrain-filled (no sky band at pitch 0)\n");
    {
        int cx, cy, cz;
        long sky;
        pl_x = 32.5f;
        pl_y = 32.5f;
        pl_z = 20.02f;
        pl_yaw = 0;
        for (cx = 20; cx <= 45; cx++) {
            for (cy = 20; cy <= 45; cy++) {
                for (cz = 18; cz <= 26; cz++)
                    set_b_raw(cx, cy, cz, B_AIR);
            }
        }
        light_build();
        pl_pitch = 0.6f;
        render_frame();
        sky = 0;
        for (y = 0; y < FB_H; y++)
            for (x = 0; x < FB_W; x++) {
                unsigned char c = host_fb[y * FB_W + x];
                if (c == 0 || c == 1)
                    sky++;
            }
        printf("minicraft: lookup sky_px=%ld of %d (%s)\n",
               sky, FB_W * FB_H, sky > FB_W * FB_H / 2 ? "ok sky above" : "FAIL no sky above");
        pl_pitch = -0.6f;
        render_frame();
        sky = 0;
        for (y = 0; y < FB_H; y++)
            for (x = 0; x < FB_W; x++) {
                unsigned char c = host_fb[y * FB_W + x];
                if (c == 0 || c == 1)
                    sky++;
            }
        printf("minicraft: lookdown sky_px=%ld of %d (%s)\n",
               sky, FB_W * FB_H, sky < FB_W * FB_H / 10 ? "ok ground below" : "FAIL sky below");
        pl_pitch = 0;
    }
    return 0;
}
#endif

int main(int argc, char **argv) {
    int i;
    int autoframes = 0;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--selftest") == 0)
            return selftest();
#ifdef MINICRAFT_HOST_TEST
        if (strcmp(argv[i], "--dumpstats") == 0)
            return dumpstats();
#endif
        if (strcmp(argv[i], "autoframes") == 0 && i + 1 < argc)
            autoframes = atoi(argv[i + 1]);
        if (strcmp(argv[i], "--once") == 0)
            autoframes = 1;
    }
    build_palette();
    if (load_world() != 0)
        gen_world(1);
    else {
        hotbar[0] = B_GRASS;
        hotbar[1] = B_DIRT;
        hotbar[2] = B_STONE;
        hotbar[3] = B_PLANKS;
        hotbar[4] = B_LOG;
        hotbar[5] = B_LEAVES;
        hotbar[6] = B_SAND;
        hotbar[7] = B_BRICK;
        hotbar[8] = B_GLASS;
        if (hot_sel < 0 || hot_sel > 8)
            hot_sel = 0;
    }
    s_vga(1);
    s_kbd_raw(1);
    s_title("Minicraft");
    s_pal(mc_pal);
    printf("minicraft: WASD move, mouse/arrows look, Space jump, Shift sprint\n");
    printf("minicraft: F fly (Space up, C down), 1-9/wheel select\n");
    printf("minicraft: left-click break, right-click place, R save\n");
    printf("minicraft: T rescue to surface, N new world, C level view\n");
    printf("minicraft: look limited to +-72 deg so the horizon stays visible\n");
    printf("minicraft: P pos report, goal 10 WOOD firewood\n");
    printf("minicraft: Esc save+quit\n");
    fflush(stdout);
    if (autoframes > 0) {
        for (i = 0; i < autoframes; i++) {
            pl_yaw += 0.08f;
            frame_ms += 16;
            render_frame();
            s_present();
        }
        printf("minicraft: played %d frames, quitting\n", autoframes);
        fflush(stdout);
        return 0;
    }
    {
        long prev = s_time_ms();
        long save_at = prev + 30000;
        for (;;) {
            long now = s_time_ms();
            float dt = (float)(now - prev) / 1000.0f;
            prev = now;
            frame_ms = now;
            if (dt < 0)
                dt = 0;
            if (dt > 0.1f)
                dt = 0.1f;
            poll_kbd();
            if (key_down[0x01]) {
                save_world();
                return 0;
            }
            if (key_down[0x13])
                save_world();
            tick_player(dt);
            tick_interact();
            render_frame();
            s_present();
            if (now > save_at) {
                save_world();
                save_at = now + 30000;
            }
            s_yield();
        }
    }
    return 0;
}
