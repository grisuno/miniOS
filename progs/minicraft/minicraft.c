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
 * exponential-style distance fog to sky. Physics: AABB player with gravity,
 * jump, swim and axis-separated collision. Interaction: left click breaks,
 * right click places the selected hotbar block (raycast up to 6 blocks).
 * Survival: HP, fall damage, drowning, wandering pigs, pork, crafting.
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
#define SAVE_TMP_PATH "/saves/minicraft.map.tmp"
#define MC_SAVE_MAGIC 0x4D434631u
#define MC_SAVE_VERSION 2u

/* Tunables: every magic lives here, never scattered in logic. */
#define MC_EYE 1.55f
#define MC_GRAV 25.0f
#define MC_JUMP 8.4f
#define MC_MAXFALL 16.0f
#define MC_SPEED 4.4f
#define MC_FLY_SPEED 8.0f
#define MC_SPRINT 1.6f
#define MC_MOUSE 0.006f
#define MC_REACH 6.0f
#define MC_VIEW 60.0f
#define MC_DDA_STEPS 128
#define MC_BREAK_MS 240
#define MC_PLACE_MS 220
#define MC_WATER_GRAV 8.0f
#define MC_WATER_SINK 3.0f
#define MC_WATER_SWIM 4.5f
#define MC_INV_MAX 999
#define MC_PITCH_MAX 1.25f
#define MC_AUTOSTEP 1.02f
#define MC_HP_MAX 20
#define MC_PIGS 5
#define MC_PORK_HEAL 6
#define MC_SAVE_SECS 30

/* Named scancodes (Set 1): no bare 0x11/0x01 in logic. */
#define SC_ESC 0x01
#define SC_1 0x02
#define SC_9 0x0A
#define SC_W 0x11
#define SC_E 0x12
#define SC_R 0x13
#define SC_T 0x14
#define SC_P 0x19
#define SC_A 0x1E
#define SC_S 0x1F
#define SC_D 0x20
#define SC_F 0x21
#define SC_K 0x25
#define SC_L 0x26
#define SC_C 0x2E
#define SC_N 0x31
#define SC_SPACE 0x39
#define SC_LSHIFT 0x2A
#define SC_RSHIFT 0x36
#define SC_CTRL 0x1D
#define EXT_UP 0x48
#define EXT_DOWN 0x50
#define EXT_LEFT 0x4B
#define EXT_RIGHT 0x4D

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
    B_SNOW = 12,
    B_FLOWER = 13,
    B_COUNT = 14
};

static unsigned char world[MC_WORLD];
static float depth_buf[MINIOS_DOOM_W * MINIOS_DOOM_H];
static unsigned char light_map[MC_WORLD];
static float cam_ray[MINIOS_DOOM_W * MINIOS_DOOM_H * 3];
static int cam_ray_ready = 0;
static unsigned int mc_seed = 1;
static int world_dirty = 0;

static float pl_x, pl_y, pl_z;
static float pl_vz;
static float pl_yaw, pl_pitch;
static int pl_on_ground;
static int hotbar[9];
static int hot_sel;
static int mc_fly;
static long frame_ms;
static long last_act_ms;
static char last_act[24];
static int inv[B_COUNT];
static int pl_hp = MC_HP_MAX;
static int pork = 0;
static long drown_ms = 0;
static float fps_ema = 10.0f;
static int world_max_top = MC_H - 1;
static float spawn_x, spawn_y, spawn_z;

typedef struct {
    float x, y, z, yaw;
    float vz;
    int alive;
    long respawn_ms;
    long turn_ms;
} Pig;
static Pig pigs[MC_PIGS];
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
static long s_pcspk_init(void) {
    long r;
    __asm__ volatile("syscall" : "=a"(r) : "a"(MINIOS_SYS_PCSPK_INIT), "D"(0) : "rcx", "r11", "memory");
    return r;
}
static long __attribute__((unused)) s_tone(long f) {
    long r;
    __asm__ volatile("syscall" : "=a"(r) : "a"(MINIOS_SYS_PCSPK_TONE), "D"(f) : "rcx", "r11", "memory");
    return r;
}
static void beep(long freq, long dur_ms) {
#ifdef MINICRAFT_HOST_TEST
    (void)freq;
    (void)dur_ms;
#else
    long t0 = s_time_ms();
    if (freq <= 0) {
        s_tone(0);
        return;
    }
    s_tone(freq);
    while (s_time_ms() - t0 < dur_ms)
        s_yield();
    s_tone(0);
#endif
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
    pal_set(46, 235, 242, 250);
    pal_set(47, 210, 225, 240);
    pal_set(48, 180, 200, 220);
    pal_set(50, 90, 60, 30);
    pal_set(51, 60, 40, 20);
    pal_set(60, 200, 60, 60);
    pal_set(61, 240, 220, 60);
    pal_set(62, 255, 120, 200);
    pal_set(63, 240, 180, 180);
    pal_set(64, 255, 255, 255);
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

static void light_recompute_col(int x, int y) {
    int z, top = col_top[y * MC_W + x];
    for (z = 0; z < MC_H; z++) {
        int d = top - z;
        float l;
        if (d <= 0)
            l = 1.0f;
        else {
            l = 1.0f - (float)d / 10.0f;
            if (l < 0.22f)
                l = 0.22f;
        }
        light_map[widx(x, y, z)] = (unsigned char)(l * 255.0f);
    }
}

static void set_b(int x, int y, int z, unsigned char b) {
    int t;
    if (!in_world(x, y, z))
        return;
    if (b >= B_COUNT)
        return;
    world[widx(x, y, z)] = b;
    col_recompute(x, y);
    light_recompute_col(x, y);
    world_dirty = 1;
    t = col_top[y * MC_W + x];
    if (t > world_max_top)
        world_max_top = t;
    else if (t < world_max_top && (int)b == B_AIR) {
        int xx, yy, m = -1;
        for (yy = 0; yy < MC_D && m < world_max_top; yy++)
            for (xx = 0; xx < MC_W; xx++)
                if (col_top[yy * MC_W + xx] > m)
                    m = col_top[yy * MC_W + xx];
        world_max_top = m;
    }
}

static void set_b_raw(int x, int y, int z, unsigned char b) {
    if (!in_world(x, y, z))
        return;
    world[widx(x, y, z)] = b;
}

static void light_build(void) {
    int x, y, m = -1;
    for (y = 0; y < MC_D; y++) {
        for (x = 0; x < MC_W; x++) {
            int t;
            col_recompute(x, y);
            light_recompute_col(x, y);
            t = col_top[y * MC_W + x];
            if (t > m)
                m = t;
        }
    }
    world_max_top = m;
}

/* skylight 1.0 at surface fading to 0.22 deep: O(1) via light_map */
static float sky_light(int x, int y, int z) {
    if (!in_world(x, y, z))
        return 1.0f;
    return (float)light_map[widx(x, y, z)] / 255.0f;
}

static int is_solid(unsigned char b) {
    return b != B_AIR && b != B_WATER && b != B_FLOWER;
}
static int in_water_at(float x, float y, float z) {
    int ix = (int)floorf(x), iy = (int)floorf(y), iz = (int)floorf(z);
    return get_b(ix, iy, iz) == B_WATER;
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

static unsigned int hash2_seed(int x, int y, unsigned int seed) {
    unsigned int h = seed * 2246822519u;
    h ^= (unsigned int)x * 374761393u;
    h ^= (unsigned int)y * 668265263u;
    h = (h ^ (h >> 13)) * 1274126177u;
    h ^= h >> 16;
    return h;
}

static float mc_smoothstep(float t) {
    return t * t * (3.0f - 2.0f * t);
}

static int ground_h_seed(int x, int y, unsigned int seed) {
    int cell = 9;
    int x0 = (x / cell) * cell, y0 = (y / cell) * cell;
    float fx = mc_smoothstep((float)(x - x0) / (float)cell);
    float fy = mc_smoothstep((float)(y - y0) / (float)cell);
    float n00 = (float)(hash2_seed(x0 / cell + 7, y0 / cell + 3, seed) % 100);
    float n10 = (float)(hash2_seed(x0 / cell + 8, y0 / cell + 3, seed) % 100);
    float n01 = (float)(hash2_seed(x0 / cell + 7, y0 / cell + 4, seed) % 100);
    float n11 = (float)(hash2_seed(x0 / cell + 8, y0 / cell + 4, seed) % 100);
    float coarse = n00 + (n10 - n00) * fx + (n01 - n00) * fy +
        (n00 - n10 - n01 + n11) * fx * fy;
    unsigned int mid = hash2_seed(x / 4, y / 4, seed ^ 0x9e3779b9u) % 100;
    unsigned int det = hash2_seed(x, y, seed ^ 0x51ed2703u) % 100;
    int h = 10 + (int)(det * 2 + mid * 5 + coarse * 10.0f) / 100;
    if (h < 4)
        h = 4;
    if (h > MC_H - 10)
        h = MC_H - 10;
    return h;
}

static int inv_add(int b, int n) {
    if (b <= B_AIR || b >= B_COUNT || n <= 0)
        return 0;
    if (b == B_WATER || b == B_BEDROCK)
        return 0;
    if (inv[b] >= MC_INV_MAX)
        return 0;
    inv[b] += n;
    if (inv[b] > MC_INV_MAX)
        inv[b] = MC_INV_MAX;
    world_dirty = 1;
    return 1;
}

static int inv_remove(int b, int n) {
    if (b <= B_AIR || b >= B_COUNT || n <= 0)
        return 0;
    if (inv[b] < n)
        return 0;
    inv[b] -= n;
    world_dirty = 1;
    return 1;
}

/* World gen phases: 1 heights 2 materials 3 water 4 trees/cacti 5 deco 6 spawn. */
static void gen_world(unsigned int seed) {
    int x, y, z;
    mc_seed = seed;
    memset(world, 0, sizeof(world));
    for (y = 0; y < MC_D; y++) {
        for (x = 0; x < MC_W; x++) {
            int h = ground_h_seed(x, y, seed);
            int desert = (hash2_seed(x / 16 + 31, y / 16 + 11, seed) % 100) < 22;
            int snowy = h >= 19 || (hash2_seed(x / 20 + 3, y / 20 + 77, seed) % 100) < 12;
            for (z = 0; z <= h; z++) {
                unsigned char b;
                if (z == 0)
                    b = B_BEDROCK;
                else if (z == h && h <= 8)
                    b = B_SAND;
                else if (z == h && desert && h > 8)
                    b = B_SAND;
                else if (z == h && snowy && h > 8)
                    b = B_SNOW;
                else if (z == h)
                    b = B_GRASS;
                else if (z >= h - 2)
                    b = (desert && h > 8) ? B_SAND : B_DIRT;
                else if (z >= h - 5)
                    b = B_STONE;
                else
                    b = (hash2_seed(x * 3 + z, y * 5 - z, seed) % 7 == 0) ? B_DIRT : B_STONE;
                set_b_raw(x, y, z, b);
            }
            if (h > 8 && !desert && !snowy && hash2_seed(x, y, seed) % 97 < 3) {
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
            if (h > 8 && desert && hash2_seed(x * 7, y * 7, seed) % 89 < 4) {
                int ch = h + 2 + (hash2_seed(x, y * 3, seed) % 2);
                int k;
                if (ch >= MC_H - 1)
                    ch = MC_H - 2;
                for (k = h + 1; k <= ch; k++)
                    set_b_raw(x, y, k, B_LOG);
            }
            if (h > 8 && !desert && !snowy && hash2_seed(x * 5 + 1, y * 5 + 2, seed) % 100 < 6) {
                if (get_b(x, y, h + 1) == B_AIR)
                    set_b_raw(x, y, h + 1, B_FLOWER);
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
                    int h = ground_h_seed(tx + dx, ty + dy, seed);
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
    spawn_x = pl_x;
    spawn_y = pl_y;
    spawn_z = pl_z;
    pl_hp = MC_HP_MAX;
    pork = 0;
    drown_ms = 0;
    {
        int i;
        for (i = 0; i < MC_PIGS; i++) {
            pigs[i].x = pl_x + (float)((hash2(i * 17 + 5, 9) % 21) - 10);
            pigs[i].y = pl_y + (float)((hash2(3, i * 29 + 7) % 21) - 10);
            pigs[i].z = pl_z + 1.0f;
            pigs[i].yaw = (float)(hash2(i, i * 3) % 628) / 100.0f;
            pigs[i].vz = 0;
            pigs[i].alive = 1;
            pigs[i].respawn_ms = 0;
            pigs[i].turn_ms = 0;
        }
    }
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
    world_dirty = 1;
}

static void pigs_spawn_one(int i, long now) {
    int tries;
    (void)now;
    pigs[i].alive = 1;
    pigs[i].vz = 0;
    for (tries = 0; tries < 20; tries++) {
        int tx = (int)pl_x + (int)(hash2(i * 91 + tries * 13, (int)frame_ms) % 21) - 10;
        int ty = (int)pl_y + (int)(hash2((int)frame_ms, i * 57 + tries * 7) % 21) - 10;
        int gz, z;
        if (tx < 2 || ty < 2 || tx >= MC_W - 2 || ty >= MC_D - 2)
            continue;
        gz = -1;
        for (z = MC_H - 1; z > 0; z--) {
            if (is_solid(get_b(tx, ty, z))) {
                gz = z;
                break;
            }
        }
        if (gz > 0 && get_b(tx, ty, gz + 1) != B_WATER) {
            pigs[i].x = (float)tx + 0.5f;
            pigs[i].y = (float)ty + 0.5f;
            pigs[i].z = (float)gz + 1.02f;
            return;
        }
    }
    pigs[i].x = spawn_x;
    pigs[i].y = spawn_y;
    pigs[i].z = spawn_z + 1.0f;
}

static int pig_collides(float x, float y, float z) {
    float r = 0.3f, h = 0.9f;
    int x0 = (int)floorf(x - r), x1 = (int)floorf(x + r);
    int y0 = (int)floorf(y - r), y1 = (int)floorf(y + r);
    int z0 = (int)floorf(z), z1 = (int)floorf(z + h);
    int ix, iy, iz;
    for (iz = z0; iz <= z1; iz++)
        for (iy = y0; iy <= y1; iy++)
            for (ix = x0; ix <= x1; ix++)
                if (is_solid(get_b(ix, iy, iz)))
                    return 1;
    return 0;
}

static void tick_pigs(float dt, long now) {
    int i;
    for (i = 0; i < MC_PIGS; i++) {
        Pig *p = &pigs[i];
        float sp = 1.6f;
        if (!p->alive) {
            if (now - p->respawn_ms > 10000)
                pigs_spawn_one(i, now);
            continue;
        }
        if (now - p->turn_ms > 2500) {
            p->turn_ms = now;
            if ((hash2(i * 131 + (int)(now / 2500), i) % 100) < 60)
                p->yaw += (float)((hash2(i, (int)(now / 1000)) % 200) - 100) / 100.0f;
        }
        {
            float nx = p->x + cosf(p->yaw) * sp * dt;
            float ny = p->y + sinf(p->yaw) * sp * dt;
            if (!pig_collides(nx, p->y, p->z))
                p->x = nx;
            else
                p->yaw += 1.7f;
            if (!pig_collides(p->x, ny, p->z))
                p->y = ny;
            else
                p->yaw -= 1.7f;
            if (p->x < 1)
                p->x = 1;
            if (p->y < 1)
                p->y = 1;
            if (p->x >= MC_W - 1)
                p->x = MC_W - 2;
            if (p->y >= MC_D - 1)
                p->y = MC_D - 2;
        }
        p->vz -= MC_GRAV * dt;
        if (p->vz < -MC_MAXFALL)
            p->vz = -MC_MAXFALL;
        {
            float nz = p->z + p->vz * dt;
            if (!pig_collides(p->x, p->y, nz))
                p->z = nz;
            else
                p->vz = 0;
            if (p->z < 1.0f) {
                p->z = 1.0f;
                p->vz = 0;
            }
        }
    }
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
    case B_SNOW:
        return face == 4 ? 46 : (face == 5 ? 48 : 47);
    case B_FLOWER:
        if (face == 4)
            return 61;
        if (face == 5)
            return 50;
        return ((face & 1) == 0) ? 60 : 62;
    default:
        return 17;
    }
}

static unsigned char sky_color(float dz, float sun_dot, int x, int y, float tsec) {
    unsigned char c;
    if (dz > 0.35f)
        c = 0;
    else if (dz > 0.04f)
        c = 1;
    else if (dz > -0.04f)
        c = 2;
    else if (dz > -0.40f)
        c = 30;
    else
        c = 44;
    if (sun_dot > 0.9985f)
        return 2;
    if (sun_dot > 0.9965f)
        return 1;
    if (dz > 0.06f) {
        int cx = (int)floorf(sun_dot * 40.0f + (float)x * 0.05f + tsec * 0.4f);
        int cy = (int)floorf(dz * 60.0f + (float)y * 0.05f);
        unsigned int n = hash2(cx, cy) % 100;
        if (n < 22)
            return 2;
        if (n < 30)
            return 1;
    }
    return c;
}

static unsigned char shade_block(unsigned char b, int face, int bx, int by, int bz,
                                 float dist, int x, int y) {
    unsigned char c = face_color(get_b(bx, by, bz), face);
    float li;
    /* palette-indexed honesty: no true blending, dither suggests it */
    if (b == B_WATER && (((x * 2 + y * 3) & 3) == 0))
        return 34;
    if (b == B_LEAVES && (((x + y) & 3) == 0)) {
        li = sky_light(bx, by, bz);
        if (li < 0.9f)
            return 3;
    }
    /* procedural grain: 1 in 8 pixels shifts one palette step */
    if (((unsigned int)hash2(bx * 13 + bz * 7, by * 13 - bz * 5) & 7) == 0) {
        if (c > 10 && c != 34)
            c = (unsigned char)(c - 1);
    }
    /* directional sun: Y-facing sides one dither step darker */
    if (face == 2 && ((x * 3 + y * 7) & 3) == 0) {
        if (c > 10)
            c = (unsigned char)(c + 1 > 64 ? c : c + 1);
    }
    li = sky_light(bx, by, bz);
    {
        int hh = ((x * 73 + y * 149) & 7);
        if ((float)hh >= li * 8.0f)
            return 3;
    }
    /* exponential-style fog: quadratic dither to sky */
    if (dist > 12.0f) {
        float t = (dist - 12.0f) / 48.0f;
        unsigned char fogc;
        t = t * t * 3.0f;
        if (t > 1.0f)
            t = 1.0f;
        fogc = (dist > 48.0f) ? 1 : 0;
        if ((((unsigned int)(x * 73 + y * 149)) & 255) < (unsigned int)(t * 255.0f))
            return fogc;
    }
    return c;
}

typedef struct {
    int hit;
    int bx, by, bz;
    int px, py, pz;
    int nx, ny, nz;
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
    int hnx = 0, hny = 0, hnz = 1;
    float t = 0;
    int i;
    memset(&h, 0, sizeof(h));
    if (dz > 0 && iz > world_max_top)
        return h;
    for (i = 0; i < MC_DDA_STEPS; i++) {
        if (tmx < tmy && tmx < tmz) {
            ix += stepx;
            t = tmx;
            tmx += tdx;
            face = 0;
            hnx = -stepx;
            hny = 0;
            hnz = 0;
        } else if (tmy < tmz) {
            iy += stepy;
            t = tmy;
            tmy += tdy;
            face = 2;
            hnx = 0;
            hny = -stepy;
            hnz = 0;
        } else {
            iz += stepz;
            t = tmz;
            tmz += tdz;
            face = dz > 0 ? 5 : 4;
            hnx = 0;
            hny = 0;
            hnz = -stepz;
        }
        if (t > maxd)
            return h;
        if (!in_world(ix, iy, iz)) {
            if (iz < 0 || iz >= MC_H)
                return h;
            if ((ix < 0 && stepx < 0) || (ix >= MC_W && stepx > 0) ||
                (iy < 0 && stepy < 0) || (iy >= MC_D && stepy > 0))
                return h;
            if (iz > world_max_top && stepz > 0)
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
            h.nx = hnx;
            h.ny = hny;
            h.nz = hnz;
            h.px = ix + hnx;
            h.py = iy + hny;
            h.pz = iz + hnz;
            return h;
        }
    }
    return h;
}

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
    case B_SNOW: return "SNOW";
    case B_FLOWER: return "FLOWER";
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

static void cam_build(void) {
    int x, y;
    if (cam_ray_ready)
        return;
    for (y = 0; y < FB_H; y++) {
        for (x = 0; x < FB_W; x++) {
            float cx = ((float)x / (float)FB_W * 2.0f - 1.0f) * 0.95f;
            float cyy = 1.0f;
            float cz = (1.0f - (float)y / (float)FB_H * 2.0f) * 0.60f;
            float il = 1.0f / sqrtf(cx * cx + cyy * cyy + cz * cz);
            cam_ray[(y * FB_W + x) * 3 + 0] = cx * il;
            cam_ray[(y * FB_W + x) * 3 + 1] = cyy * il;
            cam_ray[(y * FB_W + x) * 3 + 2] = cz * il;
        }
    }
    cam_ray_ready = 1;
}

static void render_terrain(RayHit tgt, float cyaw, float syaw, float cpit,
                           float spit, float ez, float tsec) {
    int x, y;
    cam_build();
    for (y = 0; y < FB_H; y++) {
        for (x = 0; x < FB_W; x++) {
            float cx = cam_ray[(y * FB_W + x) * 3 + 0];
            float cyy = cam_ray[(y * FB_W + x) * 3 + 1];
            float cz = cam_ray[(y * FB_W + x) * 3 + 2];
            float f2 = cyy * cpit - cz * spit;
            float u2 = cyy * spit + cz * cpit;
            float dx = f2 * cyaw + cx * syaw;
            float dy2 = f2 * syaw - cx * cyaw;
            float dz2 = u2;
            RayHit h;
            unsigned char c;
            h = cast_ray(pl_x, pl_y, ez, dx, dy2, dz2, MC_VIEW);
            if (!h.hit) {
                float sd = dx * 0.55f + dy2 * 0.35f + dz2 * 0.76f;
                c = sky_color(dz2, sd, x, y, tsec);
                depth_buf[y * FB_W + x] = 1e30f;
            } else {
                c = shade_block(get_b(h.bx, h.by, h.bz), h.face,
                                h.bx, h.by, h.bz, h.dist, x, y);
                if (tgt.hit && h.bx == tgt.bx && h.by == tgt.by && h.bz == tgt.bz) {
                    if (((x + y) & 1) == 0)
                        c = 2;
                }
                depth_buf[y * FB_W + x] = h.dist;
            }
            BACKBUF[y * FB_W + x] = c;
        }
    }
}

static void render_pigs(float cyaw, float syaw, float cpit, float spit, float ez) {
    int i;
    float fx = cyaw * cpit, fy = syaw * cpit, fz = spit;
    float rx = syaw, ry = -cyaw;
    float ux = -cyaw * spit, uy = -syaw * spit, uz = cpit;
    for (i = 0; i < MC_PIGS; i++) {
        float ex, ey, ezz, fwd, rgt, up;
        float dist, sz, cx, cy;
        int x0, x1, y0, y1, px, py;
        if (!pigs[i].alive)
            continue;
        ex = pigs[i].x - pl_x;
        ey = pigs[i].y - pl_y;
        ezz = (pigs[i].z + 0.5f) - ez;
        fwd = ex * fx + ey * fy + ezz * fz;
        if (fwd < 0.6f || fwd > MC_VIEW)
            continue;
        rgt = ex * rx + ey * ry;
        up = ex * ux + ey * uy + ezz * uz;
        cx = (float)FB_W / 2.0f + (rgt / fwd) * (float)FB_W / 1.9f;
        cy = (float)FB_H / 2.0f - (up / fwd) * (float)FB_H / 1.2f;
        dist = fwd;
        sz = 26.0f / dist;
        if (sz < 2.0f)
            sz = 2.0f;
        if (sz > 60.0f)
            sz = 60.0f;
        x0 = (int)(cx - sz / 2);
        x1 = (int)(cx + sz / 2);
        y0 = (int)(cy - sz / 2);
        y1 = (int)(cy + sz / 2);
        if (x1 < 0 || x0 >= FB_W || y1 < 0 || y0 >= FB_H)
            continue;
        for (py = y0; py <= y1; py++) {
            for (px = x0; px <= x1; px++) {
                int body;
                unsigned char c;
                if (px < 0 || px >= FB_W || py < 0 || py >= FB_H)
                    continue;
                if (depth_buf[py * FB_W + px] < dist)
                    continue;
                body = px > x0 && px < x1 && py > y0 && py < y1;
                if (!body)
                    continue;
                if (py < y0 + (y1 - y0) / 3) {
                    c = 63;
                    if (px == x0 + (x1 - x0) / 3 || px == x0 + 2 * (x1 - x0) / 3)
                        c = 3;
                } else {
                    c = 63;
                    if (px == x0 || px == x1 || py == y1)
                        c = 50;
                }
                BACKBUF[py * FB_W + px] = c;
            }
        }
    }
}

static void render_frame(void) {
    float cyaw = cosf(pl_yaw), syaw = sinf(pl_yaw);
    float cpit = cosf(pl_pitch), spit = sinf(pl_pitch);
    float ez = eye_z();
    float fdx = cyaw * cpit, fdy = syaw * cpit, fdz = spit;
    float tsec = (float)frame_ms / 1000.0f;
    RayHit tgt = cast_ray(pl_x, pl_y, ez, fdx, fdy, fdz, MC_REACH);
    render_terrain(tgt, cyaw, syaw, cpit, spit, ez, tsec);
    render_pigs(cyaw, syaw, cpit, spit, ez);
    {
        char hud0[48], hud1[64], hud2[48];
        char fc = mc_facing();
        int ix = (int)pl_x, iy = (int)pl_y, iz = (int)pl_z;
        snprintf(hud0, sizeof(hud0), "X%d Y%d Z%d F:%c %dFPS", ix, iy, iz, fc, (int)(fps_ema + 0.5f));
        mc_text_bg(3, 3, hud0, 2, 3);
        {
            unsigned char sb = (unsigned char)hotbar[hot_sel];
            if (tgt.hit)
                snprintf(hud1, sizeof(hud1), "T:%s %dM S:%sX%d",
                        mc_block_name(get_b(tgt.bx, tgt.by, tgt.bz)),
                        (int)tgt.dist, mc_block_name(sb), inv[sb]);
            else
                snprintf(hud1, sizeof(hud1), "T:- S:%sX%d", mc_block_name(sb), inv[sb]);
        }
        mc_text_bg(3, 11, hud1, 2, 3);
        snprintf(hud2, sizeof(hud2), "HP:%d PORK:%d W:%d/10", pl_hp, pork, inv[B_LOG]);
        mc_text_bg(3, 19, hud2, 2, 3);
        if (mc_fly)
            mc_text_bg(FB_W - 3 * 4 * 4, 3, "FLY", 2, 3);
        if (last_act[0] && frame_ms - last_act_ms < 2500)
            mc_text_bg(3, 27, last_act, 2, 3);
        {
            int px = (int)pl_x, py = (int)pl_y;
            if (px >= 0 && py >= 0 && px < MC_W && py < MC_D) {
                int top = col_top[py * MC_W + px];
                if (pl_z < (float)top - 1.5f)
                    mc_text_bg(3, 35, "T:SALIR", 2, 3);
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
            if ((r & 0x7F) >= SC_1 && (r & 0x7F) <= SC_9)
                hot_sel = (r & 0x7F) - SC_1;
            if ((r & 0x7F) == SC_F) {
                mc_fly = !mc_fly;
                pl_vz = 0;
                printf("minicraft: fly %s\n", mc_fly ? "on" : "off");
            }
            if ((r & 0x7F) == SC_T) {
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
            if ((r & 0x7F) == SC_K) {
                if (inv_remove(B_LOG, 4)) {
                    inv_add(B_PLANKS, 16);
                    snprintf(last_act, sizeof(last_act), "+16 PLANKS");
                    last_act_ms = frame_ms;
                    printf("minicraft: crafted 16 planks\n");
                    beep(660, 60);
                } else {
                    snprintf(last_act, sizeof(last_act), "NEED 4 WOOD");
                    last_act_ms = frame_ms;
                }
            }
            if ((r & 0x7F) == SC_L) {
                if (inv_remove(B_PLANKS, 4)) {
                    inv_add(B_BRICK, 4);
                    snprintf(last_act, sizeof(last_act), "+4 BRICK");
                    last_act_ms = frame_ms;
                    printf("minicraft: crafted 4 brick\n");
                    beep(520, 60);
                } else {
                    snprintf(last_act, sizeof(last_act), "NEED 4 PLANKS");
                    last_act_ms = frame_ms;
                }
            }
            if ((r & 0x7F) == SC_E) {
                if (pork > 0 && pl_hp < MC_HP_MAX) {
                    pork--;
                    world_dirty = 1;
                    pl_hp += MC_PORK_HEAL;
                    if (pl_hp > MC_HP_MAX)
                        pl_hp = MC_HP_MAX;
                    snprintf(last_act, sizeof(last_act), "+HP %d", pl_hp);
                    last_act_ms = frame_ms;
                    beep(440, 80);
                } else if (pork <= 0) {
                    snprintf(last_act, sizeof(last_act), "NO PORK");
                    last_act_ms = frame_ms;
                }
            }
            if ((r & 0x7F) == SC_N) {
                mc_seed++;
                gen_world(mc_seed);
                if (save_world() != 0) {
                    snprintf(last_act, sizeof(last_act), "SAVE FAIL");
                    last_act_ms = frame_ms;
                    printf("minicraft: save failed\n");
                } else {
                    printf("minicraft: new world\n");
                }
            }
            if ((r & 0x7F) == SC_C && !mc_fly) {
                pl_pitch = 0;
                printf("minicraft: view leveled\n");
            }
            if ((r & 0x7F) == SC_P) {
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

typedef enum {
    MOVE_FREE = 0,
    MOVE_HIT_FLOOR,
    MOVE_HIT_CEILING,
    MOVE_HIT_WALL
} MoveResult;

static void move_x(float nx) {
    if (!player_collides(nx, pl_y, pl_z))
        pl_x = nx;
}

static void move_y(float ny) {
    if (!player_collides(pl_x, ny, pl_z))
        pl_y = ny;
}

static MoveResult move_z_abs(float nz) {
    if (!player_collides(pl_x, pl_y, nz)) {
        pl_z = nz;
        pl_on_ground = 0;
        return MOVE_FREE;
    }
    if (nz < pl_z) {
        pl_on_ground = 1;
        pl_vz = 0;
        return MOVE_HIT_FLOOR;
    }
    pl_vz = 0;
    return MOVE_HIT_CEILING;
}

static int block_intersects_player(int bx, int by, int bz) {
    float minx = pl_x - 0.3f, maxx = pl_x + 0.3f;
    float miny = pl_y - 0.3f, maxy = pl_y + 0.3f;
    float minz = pl_z, maxz = pl_z + 1.7f;
    return maxx > (float)bx && minx < (float)(bx + 1) &&
        maxy > (float)by && miny < (float)(by + 1) &&
        maxz > (float)bz && minz < (float)(bz + 1);
}

static void try_autostep(float tx, float ty) {
    float nz = pl_z + MC_AUTOSTEP;
    if (player_collides(tx, ty, pl_z) && !player_collides(tx, ty, nz)) {
        pl_x = tx;
        pl_y = ty;
        pl_z = nz;
        pl_on_ground = 1;
        pl_vz = 0;
    }
}

static void hurt(int dmg, const char *why) {
    if (mc_fly || dmg <= 0)
        return;
    if (pl_hp <= 0)
        return;
    pl_hp -= dmg;
    snprintf(last_act, sizeof(last_act), "-%dHP %s", dmg, why);
    last_act_ms = frame_ms;
    beep(110, 120);
    if (pl_hp <= 0) {
        pl_hp = MC_HP_MAX;
        pork = 0;
        pl_x = spawn_x;
        pl_y = spawn_y;
        pl_z = spawn_z;
        pl_vz = 0;
        printf("minicraft: died (%s), respawned\n", why);
        snprintf(last_act, sizeof(last_act), "RESPAWN");
        last_act_ms = frame_ms;
    }
}

static void tick_player(float dt) {
    float sprint = (key_down[SC_LSHIFT] || key_down[SC_RSHIFT] || key_down[SC_CTRL]) ? MC_SPRINT : 1.0f;
    float speed = (mc_fly ? MC_FLY_SPEED : MC_SPEED) * sprint;
    float fx = cosf(pl_yaw), fy = sinf(pl_yaw);
    float rx = -fy, ry = fx;
    float mx = 0, my = 0;
    float ox, oy;
    int feet_wet = in_water_at(pl_x, pl_y, pl_z + 0.2f);
    int head_wet = in_water_at(pl_x, pl_y, eye_z());
    if (feet_wet)
        speed *= 0.6f;
    if (key_down[SC_W])
        mx += fx, my += fy;
    if (key_down[SC_S])
        mx -= fx, my -= fy;
    if (key_down[SC_A])
        mx += rx, my += ry;
    if (key_down[SC_D])
        mx -= rx, my -= ry;
    ox = pl_x;
    oy = pl_y;
    {
        float l = sqrtf(mx * mx + my * my);
        if (l > 0.01f) {
            mx = mx / l * speed * dt;
            my = my / l * speed * dt;
            move_x(pl_x + mx);
            move_y(pl_y + my);
            if (!mc_fly && !feet_wet && pl_on_ground && pl_x == ox && pl_y == oy)
                try_autostep(ox + mx, oy + my);
        }
    }
    if (mc_fly) {
        if (key_down[SC_SPACE])
            move_z_abs(pl_z + 6.0f * dt);
        /* shift doubles as sprint already; sink with C */
        if (key_down[SC_C])
            move_z_abs(pl_z - 6.0f * dt);
        pl_vz = 0;
        pl_on_ground = 0;
    } else if (feet_wet || head_wet) {
        if (key_down[SC_SPACE])
            pl_vz = MC_WATER_SWIM;
        else {
            pl_vz -= MC_WATER_GRAV * dt;
            if (pl_vz < -MC_WATER_SINK)
                pl_vz = -MC_WATER_SINK;
        }
        move_z_abs(pl_z + pl_vz * dt);
        pl_on_ground = 0;
        if (head_wet) {
            drown_ms += (long)(dt * 1000.0f);
            if (drown_ms > 4000) {
                drown_ms = 3000;
                hurt(1, "DROWN");
            }
        } else {
            drown_ms = 0;
        }
    } else {
        float fall_v;
        MoveResult zr;
        drown_ms = 0;
        if (key_down[SC_SPACE] && pl_on_ground) {
            pl_vz = MC_JUMP;
            pl_on_ground = 0;
        }
        fall_v = pl_vz;
        pl_vz -= MC_GRAV * dt;
        if (pl_vz < -MC_MAXFALL)
            pl_vz = -MC_MAXFALL;
        zr = move_z_abs(pl_z + pl_vz * dt);
        if (zr == MOVE_HIT_FLOOR && fall_v < -12.0f) {
            int dmg = (int)((-fall_v - 12.0f) / 2.0f) + 1;
            hurt(dmg, "FALL");
        }
    }
    if (pl_z < 1.0f) {
        pl_z = 1.0f;
        pl_vz = 0;
        pl_on_ground = 1;
    }
    if (ext_down[EXT_UP])
        pl_pitch += 2.4f * dt;
    if (ext_down[EXT_DOWN])
        pl_pitch -= 2.4f * dt;
    if (ext_down[EXT_LEFT])
        pl_yaw += 3.2f * dt;
    if (ext_down[EXT_RIGHT])
        pl_yaw -= 3.2f * dt;
    if (pl_pitch > MC_PITCH_MAX)
        pl_pitch = MC_PITCH_MAX;
    if (pl_pitch < -MC_PITCH_MAX)
        pl_pitch = -MC_PITCH_MAX;
}

static void tick_water(long now) {
    static long last_w = 0;
    static int qx[256], qy[256], qz[256];
    int cx = (int)pl_x, cy = (int)pl_y;
    int budget = 200;
    int dx, dy, nq = 0, k;
    if (now - last_w < 300)
        return;
    last_w = now;
    for (dy = -8; dy <= 8 && budget > 0; dy++) {
        for (dx = -8; dx <= 8 && budget > 0; dx++) {
            int x = cx + dx, y = cy + dy;
            int z, top;
            if (x < 1 || y < 1 || x >= MC_W - 1 || y >= MC_D - 1)
                continue;
            top = col_top[y * MC_W + x];
            for (z = top; z >= top - 3 && z > 0 && budget > 0; z--) {
                if (get_b(x, y, z) != B_WATER)
                    continue;
                budget--;
                if (get_b(x, y, z - 1) == B_AIR) {
                    if (nq < 256) {
                        qx[nq] = x;
                        qy[nq] = y;
                        qz[nq] = z - 1;
                        nq++;
                    }
                } else if ((hash2(x * 31 + z, y * 17 + (int)now / 300) % 100) < 25) {
                    int dir = hash2(x + (int)now, y - z) % 4;
                    int nx = x + (dir == 0 ? 1 : dir == 1 ? -1 : 0);
                    int ny = y + (dir == 2 ? 1 : dir == 3 ? -1 : 0);
                    if (in_world(nx, ny, z) && get_b(nx, ny, z) == B_AIR &&
                        (is_solid(get_b(nx, ny, z - 1)) || get_b(nx, ny, z - 1) == B_WATER)) {
                        if (nq < 256) {
                            qx[nq] = nx;
                            qy[nq] = ny;
                            qz[nq] = z;
                            nq++;
                        }
                    }
                }
            }
        }
    }
    for (k = 0; k < nq; k++) {
        if (get_b(qx[k], qy[k], qz[k]) == B_AIR)
            set_b(qx[k], qy[k], qz[k], B_WATER);
    }
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
                pl_yaw -= (float)ddx * MC_MOUSE;
                pl_pitch -= (float)ddy * MC_MOUSE;
                if (pl_pitch > MC_PITCH_MAX)
                    pl_pitch = MC_PITCH_MAX;
                if (pl_pitch < -MC_PITCH_MAX)
                    pl_pitch = -MC_PITCH_MAX;
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
        int lb_hold = lb && (now - last_edit_ms >= MC_BREAK_MS);
        int rb_hold = rb && (now - last_edit_ms >= MC_PLACE_MS);
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
        h = cast_ray(pl_x, pl_y, eye_z(), dx, dy, dz, MC_REACH);
        if (lb && (lb_edge || lb_hold)) {
            int pi, hit_pig = -1;
            float best = 1e30f;
            for (pi = 0; pi < MC_PIGS; pi++) {
                float ex = pigs[pi].x - pl_x;
                float ey = pigs[pi].y - pl_y;
                float ezz = (pigs[pi].z + 0.5f) - eye_z();
                float fwd = ex * dx + ey * dy + ezz * dz;
                float perp;
                if (!pigs[pi].alive || fwd < 0.5f || fwd > MC_REACH)
                    continue;
                perp = sqrtf(ex * ex + ey * ey + ezz * ezz - fwd * fwd);
                if (perp < 0.7f && fwd < best) {
                    best = fwd;
                    hit_pig = pi;
                }
            }
            if (hit_pig >= 0 && (!h.hit || best < h.dist)) {
                pigs[hit_pig].alive = 0;
                pigs[hit_pig].respawn_ms = now;
                pork++;
                world_dirty = 1;
                snprintf(last_act, sizeof(last_act), "+PORK %d", pork);
                last_act_ms = now;
                printf("minicraft: pork %d\n", pork);
                beep(520, 70);
                last_edit_ms = now;
                prev_buttons = m[2];
                return;
            }
        }
        if (!h.hit) {
            prev_buttons = m[2];
            return;
        }
        if (lb && (lb_edge || lb_hold)) {
            unsigned char b = get_b(h.bx, h.by, h.bz);
            if (b != B_BEDROCK && b != B_AIR) {
                set_b(h.bx, h.by, h.bz, B_AIR);
                if (b != B_WATER)
                    inv_add(b, 1);
                snprintf(last_act, sizeof(last_act), "-%s", mc_block_name(b));
                last_act_ms = now;
                beep(220, 50);
                if (b == B_LOG && inv[b] == 10) {
                    printf("minicraft: GOAL firewood x10 DONE\n");
                    snprintf(last_act, sizeof(last_act), "GOAL DONE");
                    last_act_ms = now;
                    beep(880, 120);
                }
            }
            last_edit_ms = now;
        } else if (rb && (rb_edge || rb_hold)) {
            unsigned char there = in_world(h.px, h.py, h.pz)
                ? get_b(h.px, h.py, h.pz)
                : B_BEDROCK;
            if (there == B_AIR || there == B_WATER) {
                unsigned char nb = (unsigned char)hotbar[hot_sel];
                if (inv[nb] <= 0) {
                    snprintf(last_act, sizeof(last_act), "VACIO");
                    last_act_ms = now;
                } else if (block_intersects_player(h.px, h.py, h.pz)) {
                    snprintf(last_act, sizeof(last_act), "OCUPADO");
                    last_act_ms = now;
                } else {
                    if (inv_remove(nb, 1)) {
                        set_b(h.px, h.py, h.pz, nb);
                        snprintf(last_act, sizeof(last_act), "+%s", mc_block_name(nb));
                        last_act_ms = now;
                        beep(440, 50);
                    }
                }
                last_edit_ms = now;
            }
        }
    }
    prev_buttons = m[2];
}

typedef struct {
    uint32_t magic;
    uint32_t version;
    uint32_t world_size;
    uint32_t seed;
    float px, py, pz, yaw, pitch;
    int32_t hot_sel;
    int32_t hp;
    int32_t pork_n;
    int32_t inv[B_COUNT];
} SaveHeader;

static int save_world(void) {
    FILE *f = fopen(SAVE_TMP_PATH, "wb");
    SaveHeader hd;
    size_t i;
    if (!f)
        return -1;
    hd.magic = MC_SAVE_MAGIC;
    hd.version = MC_SAVE_VERSION;
    hd.world_size = (uint32_t)sizeof(world);
    hd.seed = mc_seed;
    hd.px = pl_x;
    hd.py = pl_y;
    hd.pz = pl_z;
    hd.yaw = pl_yaw;
    hd.pitch = pl_pitch;
    hd.hot_sel = (int32_t)hot_sel;
    hd.hp = (int32_t)pl_hp;
    hd.pork_n = (int32_t)pork;
    for (i = 0; i < B_COUNT; i++)
        hd.inv[i] = (int32_t)inv[i];
    if (fwrite(&hd, 1, sizeof(hd), f) != sizeof(hd)) {
        fclose(f);
        return -1;
    }
    if (fwrite(world, 1, sizeof(world), f) != sizeof(world)) {
        fclose(f);
        return -1;
    }
    if (fclose(f) != 0)
        return -1;
    if (rename(SAVE_TMP_PATH, SAVE_PATH) != 0)
        return -1;
    world_dirty = 0;
    return 0;
}

static int save_validate_loaded(void) {
    size_t i;
    int k;
    for (i = 0; i < sizeof(world); i++) {
        if (world[i] >= B_COUNT)
            return -1;
    }
    if (!(pl_x >= 0 && pl_x < MC_W && pl_y >= 0 && pl_y < MC_D && pl_z >= 0 && pl_z < MC_H))
        return -1;
    if (hot_sel < 0 || hot_sel > 8)
        hot_sel = 0;
    if (pl_hp < 1 || pl_hp > MC_HP_MAX)
        pl_hp = MC_HP_MAX;
    if (pork < 0 || pork > MC_INV_MAX)
        pork = 0;
    for (k = 0; k < B_COUNT; k++) {
        if (inv[k] < 0 || inv[k] > MC_INV_MAX)
            inv[k] = 0;
    }
    return 0;
}

static void load_reset_runtime(void) {
    int i;
    mc_fly = 0;
    pl_vz = 0;
    pl_on_ground = 0;
    drown_ms = 0;
    spawn_x = pl_x;
    spawn_y = pl_y;
    spawn_z = pl_z;
    for (i = 0; i < MC_PIGS; i++) {
        pigs[i].x = pl_x + (float)((hash2(i * 17 + 5, 9) % 21) - 10);
        pigs[i].y = pl_y + (float)((hash2(3, i * 29 + 7) % 21) - 10);
        pigs[i].z = pl_z + 1.0f;
        pigs[i].yaw = 0;
        pigs[i].vz = 0;
        pigs[i].alive = 1;
        pigs[i].respawn_ms = 0;
        pigs[i].turn_ms = 0;
    }
    world_dirty = 0;
}

static int load_world_legacy(FILE *f) {
    float st[6];
    int i;
    if (fread(world, 1, sizeof(world), f) != sizeof(world))
        return -1;
    light_build();
    for (i = 0; i < B_COUNT; i++)
        inv[i] = 0;
    if (fread(st, 1, sizeof(st), f) == sizeof(st)) {
        pl_x = st[0];
        pl_y = st[1];
        pl_z = st[2];
        pl_yaw = st[3];
        pl_pitch = st[4];
        hot_sel = (int)st[5] % 9;
    }
    {
        int old_inv[12];
        if (fread(old_inv, 1, sizeof(old_inv), f) == sizeof(old_inv)) {
            for (i = 0; i < 12 && i < B_COUNT; i++)
                inv[i] = old_inv[i];
            if (fread(&inv[12], 1, sizeof(inv) - sizeof(old_inv), f) !=
                sizeof(inv) - sizeof(old_inv)) {
                inv[12] = 0;
                inv[13] = 0;
            }
        }
    }
    mc_seed = 1;
    pl_hp = MC_HP_MAX;
    pork = 0;
    if (save_validate_loaded() != 0)
        return -1;
    load_reset_runtime();
    return 0;
}

static int load_world(void) {
    FILE *f = fopen(SAVE_PATH, "rb");
    SaveHeader hd;
    size_t i;
    int k;
    if (!f)
        return -1;
    if (fread(&hd, 1, sizeof(hd), f) != sizeof(hd)) {
        fclose(f);
        return -1;
    }
    if (hd.magic != MC_SAVE_MAGIC || hd.version != MC_SAVE_VERSION ||
        hd.world_size != sizeof(world)) {
        int r;
        rewind(f);
        r = load_world_legacy(f);
        fclose(f);
        return r;
    }
    if (fread(world, 1, sizeof(world), f) != sizeof(world)) {
        fclose(f);
        return -1;
    }
    fclose(f);
    light_build();
    mc_seed = hd.seed;
    pl_x = hd.px;
    pl_y = hd.py;
    pl_z = hd.pz;
    pl_yaw = hd.yaw;
    pl_pitch = hd.pitch;
    hot_sel = (int)hd.hot_sel;
    pl_hp = (int)hd.hp;
    pork = (int)hd.pork_n;
    for (i = 0; i < B_COUNT; i++)
        inv[i] = (int)hd.inv[i];
    if (save_validate_loaded() != 0)
        return -1;
    for (k = 0; k < B_COUNT; k++) {
        if (inv[k] < 0 || inv[k] > MC_INV_MAX)
            inv[k] = 0;
    }
    load_reset_runtime();
    pl_hp = (int)hd.hp;
    pork = (int)hd.pork_n;
    if (pl_hp < 1 || pl_hp > MC_HP_MAX)
        pl_hp = MC_HP_MAX;
    if (pork < 0 || pork > MC_INV_MAX)
        pork = 0;
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
        for (i = 0; i < MC_PIGS; i++)
            pigs[i].alive = 0;
        memset(key_down, 0, sizeof(key_down));
        memset(ext_down, 0, sizeof(ext_down));
        key_down[SC_W] = 1;
        tick_player(0.1f);
        key_down[SC_W] = 0;
        if (pl_x <= 32.5f) {
            printf("minicraft: selftest FAIL (W does not advance)\n");
            return 1;
        }
        if (fabsf(pl_y - 32.5f) > 0.01f) {
            printf("minicraft: selftest FAIL (W strafes)\n");
            return 1;
        }
        render_frame();
        {
            int sx, sy, found = 0;
            RayHit th = cast_ray(pl_x, pl_y, eye_z(), 1, 0, 0, MC_REACH);
            if (!th.hit || get_b(th.bx, th.by, th.bz) != B_BRICK) {
                printf("minicraft: selftest FAIL (crosshair ray off +X)\n");
                return 1;
            }
            for (sy = 90; sy <= 110 && !found; sy++)
                for (sx = 140; sx <= 200; sx++)
                    if (BACKBUF[sy * FB_W + sx] == 2)
                        found = 1;
            if (!found) {
                printf("minicraft: selftest FAIL (no highlight near center)\n");
                return 1;
            }
        }
    }
    {
        SaveHeader hd;
        memset(&hd, 0, sizeof(hd));
        hd.magic = MC_SAVE_MAGIC;
        hd.version = MC_SAVE_VERSION;
        hd.world_size = (uint32_t)sizeof(world);
        if (hd.magic != MC_SAVE_MAGIC || hd.version != MC_SAVE_VERSION ||
            hd.world_size != sizeof(world)) {
            printf("minicraft: selftest FAIL (save header)\n");
            return 1;
        }
        inv[B_LOG] = 5;
        if (!inv_remove(B_LOG, 4) || inv[B_LOG] != 1) {
            printf("minicraft: selftest FAIL (inv_remove)\n");
            return 1;
        }
        if (!inv_add(B_PLANKS, 16) || inv[B_PLANKS] < 16) {
            printf("minicraft: selftest FAIL (inv_add)\n");
            return 1;
        }
        if (inv_add(B_WATER, 1) || inv_add(B_BEDROCK, 1) || inv_add(B_COUNT, 1)) {
            printf("minicraft: selftest FAIL (inv_add accepts junk)\n");
            return 1;
        }
        set_b(10, 10, 10, B_BRICK);
        if (get_b(10, 10, 10) != B_BRICK) {
            printf("minicraft: selftest FAIL (set_b)\n");
            return 1;
        }
        set_b(10, 10, 10, B_AIR);
        if (get_b(10, 10, 10) != B_AIR) {
            printf("minicraft: selftest FAIL (break)\n");
            return 1;
        }
        pl_x = 10.5f;
        pl_y = 10.5f;
        pl_z = 10.02f;
        if (block_intersects_player(10, 10, 10) == 0) {
            printf("minicraft: selftest FAIL (AABB miss)\n");
            return 1;
        }
        if (block_intersects_player(30, 30, 30) != 0) {
            printf("minicraft: selftest FAIL (AABB false hit)\n");
            return 1;
        }
        {
            RayHit h = cast_ray(8.5f, 10.5f, 10.5f, 1, 0, 0, MC_REACH);
            if (!h.hit || h.nx != -1 || h.ny != 0 || h.nz != 0 ||
                h.px != h.bx - 1 || h.py != h.by || h.pz != h.bz) {
                printf("minicraft: selftest FAIL (ray normal)\n");
                return 1;
            }
        }
        {
            unsigned int s1 = ground_h_seed(5, 5, 1);
            unsigned int s2 = ground_h_seed(5, 5, 999);
            if (s1 == s2 && ground_h_seed(6, 7, 1) == ground_h_seed(6, 7, 999)) {
                printf("minicraft: selftest FAIL (seed ignored)\n");
                return 1;
            }
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
            else if ((c >= 10 && c <= 48) || (c >= 60 && c <= 64))
                top_ground++;
        }
    }
    for (y = 120; y < 160; y++) {
        for (x = 0; x < FB_W; x++) {
            unsigned char c = host_fb[y * FB_W + x];
            if (c == 0 || c == 1)
                bot_sky++;
            else if ((c >= 10 && c <= 48) || (c >= 60 && c <= 64))
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
    if (load_world() != 0) {
        printf("minicraft: no save, new world\n");
        gen_world(1);
    } else {
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
        printf("minicraft: save loaded\n");
    }
    s_vga(1);
    s_kbd_raw(1);
    s_title("Minicraft");
    s_pal(mc_pal);
    s_pcspk_init();
    printf("minicraft: WASD move, mouse/arrows look, Space jump/swim, Shift sprint\n");
    printf("minicraft: F fly (Space up, C down), 1-9/wheel select\n");
    printf("minicraft: left-click break/hunt, right-click place, R save\n");
    printf("minicraft: K 4WOOD->16PLANKS, L 4PLANKS->4BRICK, E eat pork\n");
    printf("minicraft: T rescue to surface, N new world, C level view\n");
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
        long save_at = prev + MC_SAVE_SECS * 1000;
        for (;;) {
            long now = s_time_ms();
            float dt = (float)(now - prev) / 1000.0f;
            float inst;
            prev = now;
            frame_ms = now;
            if (dt < 0)
                dt = 0;
            if (dt > 0.1f)
                dt = 0.1f;
            inst = dt > 0.001f ? 1.0f / dt : 99.0f;
            fps_ema = fps_ema * 0.92f + inst * 0.08f;
            poll_kbd();
            if (key_down[SC_ESC]) {
                if (save_world() != 0)
                    printf("minicraft: save failed\n");
                return 0;
            }
            if (key_down[SC_R]) {
                if (save_world() != 0) {
                    snprintf(last_act, sizeof(last_act), "SAVE FAIL");
                    last_act_ms = now;
                    printf("minicraft: save failed\n");
                } else {
                    snprintf(last_act, sizeof(last_act), "SAVED");
                    last_act_ms = now;
                }
                key_down[SC_R] = 0;
            }
            tick_player(dt);
            tick_pigs(dt, now);
            tick_water(now);
            tick_interact();
            render_frame();
            s_present();
            if (world_dirty && now > save_at) {
                if (save_world() != 0)
                    printf("minicraft: autosave failed\n");
                save_at = now + MC_SAVE_SECS * 1000;
            }
            s_yield();
        }
    }
    return 0;
}
