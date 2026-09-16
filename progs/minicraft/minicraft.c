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
 *   minicraft walkframes <n>    flies up, walks +W across chunks, saves, exits 0
 *   minicraft standframes <n>   stands still while mobs converge, explode and
 *                               kill the player; reports deaths, saves, exits 0
 * Both make `gfx frames` climb so the BDD suite observes real rendering.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "minios_abi.h"

#define MC_H 32
#define MC_CHUNK 16
#define MC_LOAD_R 3
#define MC_CHUNKS ((MC_LOAD_R * 2 + 1) * (MC_LOAD_R * 2 + 1))
#define MC_CVOL (MC_CHUNK * MC_CHUNK * MC_H)
#define MC_COLS (MC_CHUNK * MC_CHUNK)

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
#define MC_SAVE_VERSION 4u
#define MC_SAVE_CRC_SEED 0xEDB88320u
#define MC_CHUNK_MAGIC 0x4D434348u
#define MC_CHUNK_VERSION 1u

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
#define MC_BREAK_GRACE_MS 1000
#define MC_PLACE_MS 220
#define MC_WATER_GRAV 8.0f
#define MC_WATER_SINK 3.0f
#define MC_WATER_SWIM 4.5f
#define MC_INV_MAX 999
#define MC_PITCH_MAX 1.25f
#define MC_AUTOSTEP 1.02f
#define MC_HP_MAX 20
#define MC_PIGS 5
#define MC_CREEPS_MAX 100
#define MC_CREEPS_DEF 3
#define MC_CREEP_HP 10
#define MC_FUSE_MS 900
#define MC_BOOM_R 2
#define MC_PORK_HEAL 6
#define MC_HUNGER_MAX 20
#define MC_HUNGER_MS 35000
#define MC_PIG_HP 12
#define MC_PIG_HURT_MS 250
#define MC_DAY_MS 240000
#define MC_SAVE_SECS 30
#define MC_BAYER_N 16
#define MC_H_BASE 4
#define MC_H_WT_DET 4
#define MC_H_WT_MID 6
#define MC_H_WT_COARSE 8

/* Named scancodes (Set 1): no bare 0x11/0x01 in logic. */
#define SC_ESC 0x01
#define SC_1 0x02
#define SC_9 0x0A
#define SC_Q 0x10
#define SC_W 0x11
#define SC_E 0x12
#define SC_R 0x13
#define SC_T 0x14
#define SC_U 0x16
#define SC_I 0x17
#define SC_O 0x18
#define SC_P 0x19
#define SC_J 0x24
#define SC_A 0x1E
#define SC_S 0x1F
#define SC_D 0x20
#define SC_F 0x21
#define SC_G 0x22
#define SC_K 0x25
#define SC_L 0x26
#define SC_C 0x2E
#define SC_V 0x2F
#define SC_B 0x30
#define SC_N 0x31
#define SC_ENTER 0x1C
#define SC_BACK 0x0E
#define SC_0 0x0B
#define MC_SEED_MAX 999999
#define MC_KBD_SEQ_SPINS 20000
#define SC_SPACE 0x39
#define SC_LSHIFT 0x2A
#define SC_RSHIFT 0x36
#define SC_CTRL 0x1D
#define EXT_UP 0x48
#define EXT_DOWN 0x50
#define EXT_LEFT 0x4B
#define EXT_RIGHT 0x4D
#define EXT_F11 0x57

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
    B_BED = 14,
    B_COUNT = 15
};

static unsigned char ch_blocks[MC_CHUNKS][MC_CVOL];
static unsigned char ch_light[MC_CHUNKS][MC_CVOL];
static unsigned char ch_grain[MC_CHUNKS][MC_CVOL];
static short ch_top[MC_CHUNKS][MC_COLS];
static int ch_cx[MC_CHUNKS], ch_cy[MC_CHUNKS];
static unsigned char ch_used[MC_CHUNKS], ch_dirty[MC_CHUNKS], ch_decor[MC_CHUNKS];
static int ch_max[MC_CHUNKS];
static int ch_cache = -1;
static float depth_buf[MINIOS_DOOM_W * MINIOS_DOOM_H];
static const unsigned char bayer4[MC_BAYER_N] = {
    0, 128, 32, 160, 192, 64, 224, 96, 48, 176, 16, 144, 240, 112, 208, 80
};
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
static int pl_hunger = 20;
static long hunger_ms = 0;
static int pork = 0;
static long n_respawns = 0;
static int have_tool[5];
static int break_bx, break_by, break_bz;
static long break_start;
static long break_seen;
static long break_dur;
static int break_active;
static float break_progress;

typedef struct {
    int in_block;
    int in_count;
    int out_tool;
    int out_block;
    int out_count;
} Recipe;

static const Recipe recipes[] = {
    { B_LOG, 4, -1, B_PLANKS, 16 },
    { B_PLANKS, 4, -1, B_BRICK, 4 },
};

enum { TOOL_HAND, TOOL_PICKAXE, TOOL_AXE, TOOL_SHOVEL, TOOL_SWORD };

static int best_tool_for(unsigned char b) {
    switch (b) {
    case B_STONE:
    case B_BRICK:
        return have_tool[TOOL_PICKAXE] ? TOOL_PICKAXE : TOOL_HAND;
    case B_LOG:
    case B_PLANKS:
    case B_LEAVES:
        return have_tool[TOOL_AXE] ? TOOL_AXE : TOOL_HAND;
    case B_DIRT:
    case B_GRASS:
    case B_SAND:
    case B_SNOW:
        return have_tool[TOOL_SHOVEL] ? TOOL_SHOVEL : TOOL_HAND;
    default:
        return TOOL_HAND;
    }
}

static long break_time_ms(unsigned char b, int tool) {
    switch (b) {
    case B_STONE:
    case B_BRICK:
        return tool == TOOL_PICKAXE ? 350 : 1400;
    case B_LOG:
        return tool == TOOL_AXE ? 300 : 1000;
    case B_PLANKS:
        return tool == TOOL_AXE ? 250 : 800;
    case B_LEAVES:
        return tool == TOOL_AXE ? 200 : 400;
    case B_DIRT:
    case B_GRASS:
    case B_SAND:
    case B_SNOW:
        return tool == TOOL_SHOVEL ? 180 : 500;
    case B_GLASS:
        return 300;
    case B_FLOWER:
        return 150;
    default:
        return 600;
    }
}

static long break_beep_for(unsigned char b) {
    switch (b) {
    case B_STONE:
    case B_BRICK:
        return 180;
    case B_LOG:
    case B_PLANKS:
        return 300;
    case B_SAND:
    case B_GLASS:
        return 520;
    default:
        return 220;
    }
}
static long drown_ms = 0;
static float fps_ema = 10.0f;
static int world_max_top = MC_H - 1;
static float spawn_x, spawn_y, spawn_z;

typedef struct {
    float x, y, z, yaw;
    float vz;
    int alive;
    int hp;
    int kind;
    long respawn_ms;
    long turn_ms;
    long hurt_until;
    long attack_ms;
    long fuse_ms;
} Pig;

#define MOB_PIG 0
#define MOB_CREEP 1

static float day_light = 1.0f;
static int mc_zoom = 0;
static long s_zoom(long on);
static int goal_idx = 0;

static void mc_toggle_zoom(void) {
    mc_zoom = !mc_zoom;
    s_zoom(mc_zoom ? 1 : 0);
    snprintf(last_act, sizeof(last_act), mc_zoom ? "ZOOM 2X" : "ZOOM 1X");
    last_act_ms = frame_ms;
    printf("minicraft: zoom %s\n", mc_zoom ? "2x" : "1x");
}
static int discovered_desert, discovered_snow, discovered_water;
static long discover_ms;
static Pig pigs[MC_PIGS];
static Pig creeps[MC_CREEPS_MAX];
static int n_creeps = MC_CREEPS_DEF;
static int synced_n = MC_CREEPS_DEF;
static long boom_flash_until;
static int save_world(void);
static void new_world(unsigned int seed);
static void mob_spawn_one(Pig *m, int id, int hp, long now);
static void hurt(int dmg, const char *why);
static const char *goal_text(void);
static int player_collides(float x, float y, float z);

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

/** Serial fallback for menus: SYS_KBD in raw mode carries PS/2 only,
 * so a serial console can never drive a scancode menu (Enter, digits
 * and arrows never arrive). GETC_RAW serves the serial side with no
 * line buffering; translate its bytes to the scancode the menu
 * already handles, -1 when idle. Menu-only: gameplay keeps the raw
 * scancode path untouched. */
static long s_getc_raw(void) {
    long r;
    __asm__ volatile("syscall" : "=a"(r) : "a"(MINIOS_SYS_GETC_RAW), "D"(0) : "rcx", "r11", "memory");
    return r;
}

/** Serial stash: the game loop must not eat the pause menu's bytes.
 * GETC_RAW consumes with no peek, so non-ESC bytes skipped in game
 * wait here in order for the menus; menus always read through here,
 * never past it. Bounded and app-local. */
#define SER_STASH_CAP 32
static unsigned char ser_stash[SER_STASH_CAP];
static int ser_stash_n = 0;

static long ser_get(void) {
    int i;
    long b;
    if (ser_stash_n > 0) {
        b = (long)ser_stash[0];
        for (i = 1; i < ser_stash_n; i++)
            ser_stash[i - 1] = ser_stash[i];
        ser_stash_n--;
        return b;
    }
    return s_getc_raw();
}

static void ser_unget(unsigned char b) {
    if (ser_stash_n < SER_STASH_CAP)
        ser_stash[ser_stash_n++] = b;
}

static long menu_ser_key(long b) {
    if (b == 13L || b == 10L)
        return (long)SC_ENTER;
    if (b == 27L || b == 'q')
        return (long)SC_ESC;
    if (b == 'w')
        return (long)SC_W;
    if (b == 'a')
        return (long)SC_A;
    if (b == 's')
        return (long)SC_S;
    if (b == 'd')
        return (long)SC_D;
    if (b == 8L || b == 127L)
        return (long)SC_BACK;
    if (b >= '1' && b <= '9')
        return (long)(SC_1 + (b - '1'));
    if (b == '0')
        return (long)SC_0;
    return -1L;
}
/* Bounded wait for the second byte of an E0-prefixed scancode: PS/2 bytes
 * land separately, so a single non-blocking read after E0 usually wins the
 * race but sometimes splits the pair across frames (the make then reads as
 * a bare key and F11/arrows die). Spins only, never blocks forever. */
static long s_kbd_seq(void) {
    long i;
    for (i = 0; i < MC_KBD_SEQ_SPINS; i++) {
        long sc = s_kbd();
        if (sc >= 0)
            return sc;
    }
    return -1;
}

/* Drain stale scancodes (typematic repeats, a release that arrived with
 * its press) before leaving a menu, so they never retrigger on return. */
static void kbd_drain(void) {
    long guard = 256;
    while (guard-- > 0 && s_kbd() >= 0)
        ;
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
static long s_zoom(long on) {
    long r;
    __asm__ volatile("syscall" : "=a"(r) : "a"(MINIOS_SYS_GFX_ZOOM), "D"(on) : "rcx", "r11", "memory");
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

static int in_world(int x, int y, int z) {
    (void)x;
    (void)y;
    return z >= 0 && z < MC_H;
}

static unsigned int hash2(int x, int y);
static unsigned int hash2_seed(int x, int y, unsigned int seed);
static void gen_terrain_chunk(int slot);
static void decorate_chunk(int slot);
static void chunk_build_meta(int slot);
static int save_chunk_file(int slot);
static int load_chunk_file(int slot, int cx, int cy);

/* Chunk math on unbounded coords: floor division so negatives land right. */
static int chunk_of(int v) {
    return v >= 0 ? v / MC_CHUNK : -((-v + MC_CHUNK - 1) / MC_CHUNK);
}

static int chunk_local(int v) {
    int r = v % MC_CHUNK;
    return r < 0 ? r + MC_CHUNK : r;
}

static int chunk_lidx(int lx, int ly, int z) {
    return (z * MC_CHUNK + ly) * MC_CHUNK + lx;
}

/* O(1) fast path: DDA walks neighbours, so the last chunk almost always
 * hits; the 49-slot scan is the rare slow path, never the hot loop. */
static int chunk_find(int cx, int cy) {
    int i;
    if (ch_cache >= 0 && ch_cache < MC_CHUNKS && ch_used[ch_cache] &&
        ch_cx[ch_cache] == cx && ch_cy[ch_cache] == cy)
        return ch_cache;
    for (i = 0; i < MC_CHUNKS; i++) {
        if (ch_used[i] && ch_cx[i] == cx && ch_cy[i] == cy) {
            ch_cache = i;
            return i;
        }
    }
    return -1;
}

static void world_max_recompute(void) {
    int i, m = -1;
    for (i = 0; i < MC_CHUNKS; i++) {
        if (ch_used[i] && ch_max[i] > m)
            m = ch_max[i];
    }
    world_max_top = m;
}

static int chunk_evict_slot(int cx, int cy) {
    int i, pick = -1, best = -1;
    for (i = 0; i < MC_CHUNKS; i++) {
        int d;
        if (!ch_used[i])
            return i;
        d = abs(ch_cx[i] - cx);
        {
            int dy = abs(ch_cy[i] - cy);
            if (dy > d)
                d = dy;
        }
        if (d > best) {
            best = d;
            pick = i;
        }
    }
    return pick;
}

static int chunk_ensure(int cx, int cy) {
    int s = chunk_find(cx, cy);
    if (s >= 0)
        return s;
    s = chunk_evict_slot(cx, cy);
    if (s < 0)
        return -1;
    if (ch_used[s] && ch_dirty[s])
        save_chunk_file(s);
    ch_used[s] = 1;
    ch_dirty[s] = 0;
    ch_decor[s] = 0;
    ch_cx[s] = cx;
    ch_cy[s] = cy;
    ch_max[s] = -1;
    ch_cache = s;
    if (!load_chunk_file(s, cx, cy))
        gen_terrain_chunk(s);
    chunk_build_meta(s);
    world_max_recompute();
    return s;
}

static void chunk_build_meta(int slot) {
    int lx, ly;
    int cx = ch_cx[slot], cy = ch_cy[slot];
    int s = slot;
    ch_max[s] = -1;
    for (ly = 0; ly < MC_CHUNK; ly++) {
        for (lx = 0; lx < MC_CHUNK; lx++) {
            int z, t = -1;
            for (z = MC_H - 1; z >= 0; z--) {
                if (ch_blocks[s][chunk_lidx(lx, ly, z)] != B_AIR) {
                    t = z;
                    break;
                }
            }
            ch_top[s][ly * MC_CHUNK + lx] = (short)t;
            if (t > ch_max[s])
                ch_max[s] = t;
        }
    }
    {
        int x0 = cx * MC_CHUNK, y0 = cy * MC_CHUNK;
        for (ly = 0; ly < MC_CHUNK; ly++) {
            for (lx = 0; lx < MC_CHUNK; lx++) {
                int x = x0 + lx, y = y0 + ly;
                int top = ch_top[s][ly * MC_CHUNK + lx];
                int z;
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
                    ch_light[s][chunk_lidx(lx, ly, z)] = (unsigned char)(l * 255.0f);
                    ch_grain[s][chunk_lidx(lx, ly, z)] =
                        (unsigned char)(((hash2(x * 13 + z * 7, y * 13 - z * 5) & 7) == 0) ? 1 : 0);
                }
            }
        }
    }
}

static void col_recompute(int x, int y) {
    int s = chunk_find(chunk_of(x), chunk_of(y));
    int lx, ly, z, t = -1;
    if (s < 0)
        return;
    lx = chunk_local(x);
    ly = chunk_local(y);
    for (z = MC_H - 1; z >= 0; z--) {
        if (ch_blocks[s][chunk_lidx(lx, ly, z)] != B_AIR) {
            t = z;
            break;
        }
    }
    ch_top[s][ly * MC_CHUNK + lx] = (short)t;
    {
        int m = -1, k;
        for (k = 0; k < MC_COLS; k++) {
            if (ch_top[s][k] > m)
                m = ch_top[s][k];
        }
        ch_max[s] = m;
    }
    world_max_recompute();
}

static int col_top_at(int x, int y) {
    int s = chunk_find(chunk_of(x), chunk_of(y));
    if (s < 0)
        return -1;
    return ch_top[s][chunk_local(y) * MC_CHUNK + chunk_local(x)];
}

static void light_recompute_col(int x, int y) {
    int s = chunk_find(chunk_of(x), chunk_of(y));
    int lx, ly, z, top;
    int x0, y0, xx, yy;
    if (s < 0)
        return;
    lx = chunk_local(x);
    ly = chunk_local(y);
    top = ch_top[s][ly * MC_CHUNK + lx];
    x0 = ch_cx[s] * MC_CHUNK;
    y0 = ch_cy[s] * MC_CHUNK;
    xx = x0 + lx;
    yy = y0 + ly;
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
        ch_light[s][chunk_lidx(lx, ly, z)] = (unsigned char)(l * 255.0f);
        ch_grain[s][chunk_lidx(lx, ly, z)] =
            (unsigned char)(((hash2(xx * 13 + z * 7, yy * 13 - z * 5) & 7) == 0) ? 1 : 0);
    }
}

static unsigned char get_b(int x, int y, int z) {
    int s;
    if (z < 0 || z >= MC_H)
        return B_AIR;
    s = chunk_find(chunk_of(x), chunk_of(y));
    if (s < 0)
        return B_AIR;
    return ch_blocks[s][chunk_lidx(chunk_local(x), chunk_local(y), z)];
}

static void set_b(int x, int y, int z, unsigned char b) {
    int s;
    if (z < 0 || z >= MC_H)
        return;
    if (b >= B_COUNT)
        return;
    s = chunk_ensure(chunk_of(x), chunk_of(y));
    if (s < 0)
        return;
    ch_blocks[s][chunk_lidx(chunk_local(x), chunk_local(y), z)] = b;
    ch_dirty[s] = 1;
    col_recompute(x, y);
    light_recompute_col(x, y);
    world_dirty = 1;
}

static void set_b_raw(int x, int y, int z, unsigned char b) {
    int s;
    if (z < 0 || z >= MC_H)
        return;
    s = chunk_find(chunk_of(x), chunk_of(y));
    if (s < 0)
        return;
    ch_blocks[s][chunk_lidx(chunk_local(x), chunk_local(y), z)] = b;
}

/* skylight 1.0 at surface fading to 0.22 deep: O(1) via chunk light */
static float sky_light(int x, int y, int z) {
    int s;
    if (z < 0 || z >= MC_H)
        return 1.0f;
    s = chunk_find(chunk_of(x), chunk_of(y));
    if (s < 0)
        return 1.0f;
    return (float)ch_light[s][chunk_lidx(chunk_local(x), chunk_local(y), z)] / 255.0f;
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

/* Discrete per-cell biome with wiggly borders: the cell hash keeps the
 * original 22%/12% rates exactly, while a cell-constant jitter of +-2
 * blocks breaks the perfect 16-grid alignment at the edges. A smoothed
 * (bilinear) field must NOT be thresholded here: averaging 4 uniforms
 * collapses the distribution and kills every biome but forest. */
static int biome_fdiv(int v, int c) {
    return v >= 0 ? v / c : -((-v + c - 1) / c);
}

static int biome_cell(int x, int y, unsigned int seed, int cell, int ox, int oy,
    unsigned int jit, int pct) {
    int cx = biome_fdiv(x, cell), cy = biome_fdiv(y, cell);
    int jx = (int)(hash2_seed(cx + ox, cy + oy, seed ^ jit) % 5) - 2;
    int jy = (int)(hash2_seed(cx + oy, cy + ox, seed ^ (jit ^ 0x51EDu)) % 5) - 2;
    int sx = biome_fdiv(x + jx, cell), sy = biome_fdiv(y + jy, cell);
    return (hash2_seed(sx + ox, sy + oy, seed) % 100) < (unsigned int)pct;
}

static int biome_desert(int x, int y, unsigned int seed) {
    return biome_cell(x, y, seed, 16, 31, 11, 0xD15EAu, 22);
}

static int biome_snow(int x, int y, unsigned int seed) {
    return biome_cell(x, y, seed ^ 0x5BD1E995u, 20, 3, 77, 0x5EEDu, 12);
}

static int is_cave(int x, int y, int z, unsigned int seed) {
    unsigned int n;
    if (z < 3 || z >= MC_H - 8)
        return 0;
    n = hash2_seed(x + z * 57, y - z * 31, seed ^ 0xCA9E03u) % 100;
    return n < 9;
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
    int h = MC_H_BASE + (int)(det * MC_H_WT_DET + mid * MC_H_WT_MID +
        coarse * (float)MC_H_WT_COARSE) / 100;
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

/* World gen per column, split in two phases so chunk borders never seam:
 * terrain first (position-pure from x, y, seed: identical on regen), then
 * decoration (trees may spill 2 blocks into neighbours, whose terrain is
 * guaranteed present by the load radius). */
static void gen_column_terrain(int x, int y, unsigned int seed) {
    int h = ground_h_seed(x, y, seed);
    int desert = biome_desert(x, y, seed);
    int snowy = h >= 19 || biome_snow(x, y, seed);
    int z;
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
    for (z = 3; z < h - 2 && z < MC_H - 8; z++) {
        unsigned char cur = get_b(x, y, z);
        if ((cur == B_STONE || cur == B_DIRT) && is_cave(x, y, z, seed))
            set_b_raw(x, y, z, B_AIR);
    }
    if (h <= 8) {
        for (z = h + 1; z <= 8; z++)
            set_b_raw(x, y, z, B_WATER);
    }
}

static void decorate_column(int x, int y, unsigned int seed) {
    int h = ground_h_seed(x, y, seed);
    int desert = biome_desert(x, y, seed);
    int snowy = h >= 19 || biome_snow(x, y, seed);
    if (h > 8 && !desert && !snowy && hash2_seed(x, y, seed) % 97 < 3) {
        int th = h + 4;
        int k;
        if (th >= MC_H - 1)
            th = MC_H - 2;
        for (k = h + 1; k <= th; k++)
            set_b(x, y, k, B_LOG);
        for (k = th - 1; k <= th + 1; k++) {
            int dx, dy;
            for (dy = -2; dy <= 2; dy++) {
                for (dx = -2; dx <= 2; dx++) {
                    if (dx == 0 && dy == 0 && k <= th)
                        continue;
                    if (dx * dx + dy * dy > 5 && k == th + 1)
                        continue;
                    if (get_b(x + dx, y + dy, k) == B_AIR)
                        set_b(x + dx, y + dy, k, B_LEAVES);
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
            set_b(x, y, k, B_LOG);
    }
    if (h > 8 && !desert && !snowy && hash2_seed(x * 5 + 1, y * 5 + 2, seed) % 100 < 6) {
        if (get_b(x, y, h + 1) == B_AIR)
            set_b(x, y, h + 1, B_FLOWER);
    }
}

static void gen_terrain_chunk(int slot) {
    int lx, ly;
    int x0 = ch_cx[slot] * MC_CHUNK, y0 = ch_cy[slot] * MC_CHUNK;
    for (ly = 0; ly < MC_CHUNK; ly++) {
        for (lx = 0; lx < MC_CHUNK; lx++)
            gen_column_terrain(x0 + lx, y0 + ly, mc_seed);
    }
}

static void decorate_chunk(int slot) {
    int lx, ly;
    int x0 = ch_cx[slot] * MC_CHUNK, y0 = ch_cy[slot] * MC_CHUNK;
    for (ly = 0; ly < MC_CHUNK; ly++) {
        for (lx = 0; lx < MC_CHUNK; lx++)
            decorate_column(x0 + lx, y0 + ly, mc_seed);
    }
}

/* Keep a (2R+1)^2 ring of terrain around the player, an inner ring
 * decorated, drop the rest (dirty chunks hit disk first). Runs every
 * frame: pure cache hits when standing still, a few chunk gens on border
 * crossings. Coordinates are unbounded: no edge, no wall, no wrap. */
static void ensure_around_px(float px, float py) {
    int pcx = chunk_of((int)floorf(px));
    int pcy = chunk_of((int)floorf(py));
    int dx, dy, i;
    for (dy = -MC_LOAD_R; dy <= MC_LOAD_R; dy++) {
        for (dx = -MC_LOAD_R; dx <= MC_LOAD_R; dx++)
            chunk_ensure(pcx + dx, pcy + dy);
    }
    for (dy = -(MC_LOAD_R - 1); dy <= MC_LOAD_R - 1; dy++) {
        for (dx = -(MC_LOAD_R - 1); dx <= MC_LOAD_R - 1; dx++) {
            int s = chunk_find(pcx + dx, pcy + dy);
            if (s >= 0 && !ch_decor[s]) {
                ch_decor[s] = 1;
                decorate_chunk(s);
            }
        }
    }
    for (i = 0; i < MC_CHUNKS; i++) {
        int ox, oy;
        if (!ch_used[i])
            continue;
        ox = abs(ch_cx[i] - pcx);
        oy = abs(ch_cy[i] - pcy);
        if (ox > MC_LOAD_R || oy > MC_LOAD_R) {
            if (ch_dirty[i])
                save_chunk_file(i);
            ch_used[i] = 0;
            if (ch_cache == i)
                ch_cache = -1;
        }
    }
    world_max_recompute();
}

static void ensure_around(void) {
    ensure_around_px(pl_x, pl_y);
}

/* World gen phases: 1 terrain ring 2 decor ring 3 spawn 4 mobs. */
static void new_world(unsigned int seed) {
    int z, i;
    mc_seed = seed;
    for (i = 0; i < MC_CHUNKS; i++)
        ch_used[i] = 0;
    ch_cache = -1;
    world_max_top = -1;
    ensure_around_px(8.5f, 8.5f);
    {
        int sx = 8, sy = 8;
        int tries, best_h = -1;
        for (tries = 0; tries < 40; tries++) {
            int tx = 8 + (tries * 7) % 17 - 8;
            int ty = 8 + (tries * 11) % 17 - 8;
            int dx, dy, clear = 1;
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
    pl_hunger = MC_HUNGER_MAX;
    hunger_ms = 0;
    pork = 0;
    goal_idx = 0;
    discovered_desert = discovered_snow = discovered_water = 0;
    drown_ms = 0;
    {
        int i;
        for (i = 0; i < MC_PIGS; i++) {
            pigs[i].yaw = (float)(hash2(i, i * 3) % 628) / 100.0f;
            pigs[i].kind = MOB_PIG;
            pigs[i].turn_ms = 0;
            mob_spawn_one(&pigs[i], i, MC_PIG_HP, 0);
        }
        for (i = 0; i < MC_CREEPS_MAX; i++) {
            creeps[i].yaw = (float)(hash2(i * 7, i) % 628) / 100.0f;
            creeps[i].kind = MOB_CREEP;
            creeps[i].turn_ms = 0;
            if (i < n_creeps) {
                mob_spawn_one(&creeps[i], MC_PIGS + i, MC_CREEP_HP, 0);
            } else {
                creeps[i].alive = 0;
                creeps[i].respawn_ms = 0;
                creeps[i].fuse_ms = 0;
            }
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
    hotbar[8] = B_BED;
        hot_sel = 0;
    synced_n = n_creeps;
    world_dirty = 1;
}

static void mob_spawn_one(Pig *m, int id, int hp, long now) {
    int tries;
    (void)now;
    m->alive = 1;
    m->hp = hp;
    m->hurt_until = 0;
    m->attack_ms = 0;
    m->fuse_ms = 0;
    m->vz = 0;
    for (tries = 0; tries < 20; tries++) {
        int tx = (int)pl_x + (int)(hash2(id * 91 + tries * 13, (int)frame_ms) % 21) - 10;
        int ty = (int)pl_y + (int)(hash2((int)frame_ms, id * 57 + tries * 7) % 21) - 10;
        int gz, z;
        gz = -1;
        for (z = MC_H - 1; z > 0; z--) {
            if (is_solid(get_b(tx, ty, z))) {
                gz = z;
                break;
            }
        }
        if (gz > 0 && get_b(tx, ty, gz + 1) != B_WATER) {
            m->x = (float)tx + 0.5f;
            m->y = (float)ty + 0.5f;
            m->z = (float)gz + 1.02f;
            return;
        }
    }
    m->x = spawn_x;
    m->y = spawn_y;
    m->z = spawn_z + 1.0f;
}

/* Sync live creeper slots with the menu count: raising it drops fresh
 * creepers near the player (instant encounters), lowering it retires
 * the extras quietly. Pigs are untouched. */
static void mobs_sync(void) {
    int i;
    if (n_creeps > MC_CREEPS_MAX)
        n_creeps = MC_CREEPS_MAX;
    if (n_creeps < 0)
        n_creeps = 0;
    if (n_creeps != synced_n)
        printf("minicraft: creeps %d\n", n_creeps);
    for (i = synced_n; i < n_creeps; i++)
        mob_spawn_one(&creeps[i], MC_PIGS + i, MC_CREEP_HP, frame_ms);
    for (i = n_creeps; i < synced_n; i++) {
        creeps[i].alive = 0;
        creeps[i].fuse_ms = 0;
    }
    synced_n = n_creeps;
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

static void creeper_explode(Pig *c, long now) {
    float cx = c->x, cy = c->y, cz = c->z + 0.5f;
    int ix, iy, iz, k;
    float pdx = pl_x - cx, pdy = pl_y - cy, pdz = (pl_z + 0.8f) - cz;
    float pd = sqrtf(pdx * pdx + pdy * pdy + pdz * pdz);
    c->alive = 0;
    c->respawn_ms = now;
    c->fuse_ms = 0;
    boom_flash_until = now + 180;
    beep(90, 250);
    printf("minicraft: BOOM\n");
    snprintf(last_act, sizeof(last_act), "BOOM");
    last_act_ms = now;
    for (iz = (int)cz - MC_BOOM_R; iz <= (int)cz + MC_BOOM_R; iz++) {
        for (iy = (int)cy - MC_BOOM_R; iy <= (int)cy + MC_BOOM_R; iy++) {
            for (ix = (int)cx - MC_BOOM_R; ix <= (int)cx + MC_BOOM_R; ix++) {
                float ddx = (float)ix + 0.5f - cx;
                float ddy = (float)iy + 0.5f - cy;
                float ddz = (float)iz + 0.5f - cz;
                unsigned char b;
                if (sqrtf(ddx * ddx + ddy * ddy + ddz * ddz) > (float)MC_BOOM_R + 0.2f)
                    continue;
                b = get_b(ix, iy, iz);
                if (b == B_AIR || b == B_BEDROCK)
                    continue;
                set_b(ix, iy, iz, B_AIR);
            }
        }
    }
    for (k = 0; k < MC_PIGS + n_creeps; k++) {
        Pig *m = k < MC_PIGS ? &pigs[k] : &creeps[k - MC_PIGS];
        float mdx, mdy, mdz, md;
        if (m == c || !m->alive)
            continue;
        mdx = m->x - cx;
        mdy = m->y - cy;
        mdz = (m->z + 0.5f) - cz;
        md = sqrtf(mdx * mdx + mdy * mdy + mdz * mdz);
        if (md > 3.0f)
            continue;
        if (m->kind == MOB_CREEP) {
            if (!m->fuse_ms)
                m->fuse_ms = now + 250;
        } else {
            m->alive = 0;
            m->respawn_ms = now;
            pork++;
            printf("minicraft: pork %d\n", pork);
        }
    }
    if (pd < 3.5f) {
        int dmg = pd < 1.5f ? 6 : pd < 2.5f ? 4 : 2;
        float kl = 1.5f;
        hurt(dmg, "BOOM");
        if (pd > 0.01f) {
            float nx = pl_x + pdx / pd * kl;
            float ny = pl_y + pdy / pd * kl;
            if (!player_collides(nx, pl_y, pl_z))
                pl_x = nx;
            if (!player_collides(pl_x, ny, pl_z))
                pl_y = ny;
        }
    }
}

static void tick_mob(Pig *p, int id, float dt, long now) {
    int i = id;
    {
        float sp = (day_light < 0.35f) ? 2.2f : 1.6f;
        float pdx, pdy, pd;
        if (!p->alive) {
            if (now - p->respawn_ms > 10000)
                mob_spawn_one(p, id, p->kind == MOB_CREEP ? MC_CREEP_HP : MC_PIG_HP, now);
            return;
        }
        pdx = p->x - pl_x;
        pdy = p->y - pl_y;
        pd = sqrtf(pdx * pdx + pdy * pdy);
        if (p->kind == MOB_CREEP) {
            sp = (day_light < 0.35f) ? 2.4f : 2.0f;
            if (pd < 10.0f && pd > 0.01f)
                p->yaw = atan2f(-pdy, -pdx);
            else if (now - p->turn_ms > 2500) {
                p->turn_ms = now;
                if ((hash2(id * 131 + (int)(now / 2500), id) % 100) < 60)
                    p->yaw += (float)((hash2(id, (int)(now / 1000)) % 200) - 100) / 100.0f;
            }
            if (!p->fuse_ms && pd < 1.6f) {
                p->fuse_ms = now + MC_FUSE_MS;
                beep(880, 120);
                printf("minicraft: fuse lit\n");
            }
            if (p->fuse_ms) {
                if (pd > 3.0f) {
                    p->fuse_ms = 0;
                } else {
                    snprintf(last_act, sizeof(last_act), "HUYE!");
                    last_act_ms = now;
                    if (now >= p->fuse_ms) {
                        creeper_explode(p, now);
                        return;
                    }
                }
            }
        } else if (p->hurt_until > now && pd > 0.01f) {
            p->yaw = atan2f(pdy, pdx);
            sp = 2.5f;
        } else if (now - p->turn_ms > 2500) {
            p->turn_ms = now;
            if ((hash2(i * 131 + (int)(now / 2500), i) % 100) < 60)
                p->yaw += (float)((hash2(i, (int)(now / 1000)) % 200) - 100) / 100.0f;
        }
        if (p->kind == MOB_PIG && pd < 1.3f && now - p->attack_ms > 1200) {
            p->attack_ms = now;
            hurt(day_light < 0.35f ? 2 : 1, "PIG");
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

static void tick_pigs(float dt, long now) {
    int i;
    for (i = 0; i < MC_PIGS; i++)
        tick_mob(&pigs[i], i, dt, now);
    for (i = 0; i < n_creeps; i++)
        tick_mob(&creeps[i], MC_PIGS + i, dt, now);
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
    case B_BED:
        if (face == 4)
            return 63;
        if (face == 5)
            return 50;
        return 60;
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
    if (day_light < 0.35f && sun_dot < 0.9965f) {
        if (c == 0 || c == 1 || c == 2)
            return 3;
        return c;
    }
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
    /* procedural grain: precomputed per block, no hash per pixel */
    {
        int gs = chunk_find(chunk_of(bx), chunk_of(by));
        if (gs >= 0 && in_world(bx, by, bz) &&
            ch_grain[gs][chunk_lidx(chunk_local(bx), chunk_local(by), bz)]) {
            if (c > 10 && c != 34)
                c = (unsigned char)(c - 1);
        }
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
    /* exponential-style fog: ordered Bayer dither to sky */
    if (dist > 12.0f) {
        float t = (dist - 12.0f) / 48.0f;
        unsigned char fogc;
        unsigned int gate;
        t = t * t * 3.0f;
        if (t > 1.0f)
            t = 1.0f;
        fogc = (dist > 48.0f) ? 1 : 0;
        gate = bayer4[((y & 3) * 4 + (x & 3)) & (MC_BAYER_N - 1)];
        if (gate < (unsigned int)(t * 255.0f))
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
    if (dz < 0 && iz > world_max_top + 1) {
        float t_enter = ((float)(world_max_top + 1) - oz) / dz;
        if (t_enter > 0.0f && t_enter < maxd) {
            ox += dx * t_enter;
            oy += dy * t_enter;
            oz = (float)(world_max_top + 1);
            ix = (int)floorf(ox);
            iy = (int)floorf(oy);
            iz = (int)floorf(oz);
            tmx = dx != 0 ? ((stepx > 0 ? (ix + 1 - ox) : (ox - ix)) * tdx) : 1e30f;
            tmy = dy != 0 ? ((stepy > 0 ? (iy + 1 - oy) : (oy - iy)) * tdy) : 1e30f;
            tmz = dz != 0 ? ((stepz > 0 ? (iz + 1 - oz) : (oz - iz)) * tdz) : 1e30f;
            t = t_enter;
            if (t > maxd)
                return h;
        }
    }
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
        /* Infinite x/y: unloaded columns read as AIR (sky). Only z ends
         * the ray; upward rays above the tallest loaded block quit early. */
        if (iz < 0 || iz >= MC_H)
            return h;
        if (iz > world_max_top && stepz > 0)
            return h;
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
    case B_BED: return "BED";
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

static unsigned char mob_pixel(Pig *m, int id, int px, int py, int x0, int x1, int y0, int y1) {
    int w = x1 - x0, h = y1 - y0;
    int head = py < y0 + h / 3;
    if (m->kind == MOB_CREEP) {
        int flash = m->fuse_ms && (((frame_ms / 120) & 1) == 0);
        if (flash)
            return 64;
        if (head) {
            int ex0 = x0 + w / 4, ex1 = x0 + 3 * w / 4;
            int my = y0 + h / 6;
            unsigned char eye = day_light < 0.35f ? 60 : 3;
            if ((px == ex0 || px == ex0 + 1 || px == ex1 - 1 || px == ex1) && py <= my + 1)
                return eye;
            if (px >= x0 + w / 2 - 1 && px <= x0 + w / 2 && py > my + 1)
                return 3;
            return ((px + py) & 1) ? 25 : 26;
        }
        if (px == x0 || px == x1 || py == y1)
            return 27;
        if (((px * 5 + py * 11 + id * 13) & 7) < 2)
            return 3;
        return ((px + py) & 1) ? 25 : 26;
    }
    if (head) {
        unsigned char c = 63;
        if (px == x0 + (x1 - x0) / 3 || px == x0 + 2 * (x1 - x0) / 3)
            c = 3;
        return c;
    }
    if (px == x0 || px == x1 || py == y1)
        return 50;
    return 63;
}

static void render_mob_array(Pig *arr, int n, float fx, float fy, float fz,
    float rx, float ry, float ux, float uy, float uz, float ez) {
    int i;
    for (i = 0; i < n; i++) {
        float ex, ey, ezz, fwd, rgt, up;
        float dist, sz, cx, cy;
        int x0, x1, y0, y1, px, py;
        if (!arr[i].alive)
            continue;
        ex = arr[i].x - pl_x;
        ey = arr[i].y - pl_y;
        ezz = (arr[i].z + 0.5f) - ez;
        fwd = ex * fx + ey * fy + ezz * fz;
        if (fwd < 0.6f || fwd > MC_VIEW)
            continue;
        rgt = ex * rx + ey * ry;
        up = ex * ux + ey * uy + ezz * uz;
        cx = (float)FB_W / 2.0f + (rgt / fwd) * (float)FB_W / 1.9f;
        cy = (float)FB_H / 2.0f - (up / fwd) * (float)FB_H / 1.2f;
        dist = fwd;
        sz = 26.0f / dist;
        if (arr[i].kind == MOB_CREEP)
            sz *= 1.25f;
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
                c = mob_pixel(&arr[i], i, px, py, x0, x1, y0, y1);
                BACKBUF[py * FB_W + px] = c;
            }
        }
    }
}

static void render_pigs(float cyaw, float syaw, float cpit, float spit, float ez) {
    float fx = cyaw * cpit, fy = syaw * cpit, fz = spit;
    float rx = syaw, ry = -cyaw;
    float ux = -cyaw * spit, uy = -syaw * spit, uz = cpit;
    render_mob_array(pigs, MC_PIGS, fx, fy, fz, rx, ry, ux, uy, uz, ez);
    render_mob_array(creeps, n_creeps, fx, fy, fz, rx, ry, ux, uy, uz, ez);
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
    if (frame_ms < boom_flash_until) {
        int e;
        for (e = 0; e < 6; e++) {
            int x, y;
            for (x = e; x < FB_W - e; x++) {
                mc_pixel(x, e, 64);
                mc_pixel(x, FB_H - 1 - e, 64);
            }
            for (y = e; y < FB_H - e; y++) {
                mc_pixel(e, y, 64);
                mc_pixel(FB_W - 1 - e, y, 64);
            }
        }
    }
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
        snprintf(hud2, sizeof(hud2), "HP:%d F:%d PORK:%d %s", pl_hp, pl_hunger,
            pork, goal_text());
        mc_text_bg(3, 19, hud2, 2, 3);
        if (mc_fly)
            mc_text_bg(FB_W - 3 * 4 * 4, 3, "FLY", 2, 3);
        if (last_act[0] && frame_ms - last_act_ms < 2500)
            mc_text_bg(3, 27, last_act, 2, 3);
        {
            int top = col_top_at((int)pl_x, (int)pl_y);
            if (pl_z < (float)top - 1.5f)
                mc_text_bg(3, 35, "T:SALIR", 2, 3);
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
        if (break_active) {
            int bw = 20, fill, k;
            fill = (int)(break_progress * (float)bw);
            if (fill > bw)
                fill = bw;
            for (k = 0; k < bw; k++)
                mc_pixel(cx - bw / 2 + k, cyy - 10, k < fill ? 2 : 3);
        }
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
static int esc_latch;
static unsigned char sc_hist[16];
static int sc_hist_n;
static int sc_seq_timeouts;

static void sc_hist_push(unsigned char b) {
    int i;
    if (sc_hist_n < 16)
        sc_hist[sc_hist_n++] = b;
    else {
        for (i = 0; i < 15; i++)
            sc_hist[i] = sc_hist[i + 1];
        sc_hist[15] = b;
    }
}

static void poll_kbd(void) {
    for (;;) {
        long sc = s_kbd();
        if (sc < 0 || sc > 0xFFFF)
            break;
        sc_hist_push((unsigned char)sc);
        sc_hist_push((unsigned char)sc);
        if (sc == 0xE0) {
            long sc2 = s_kbd_seq();
            if (sc2 < 0) {
                sc_seq_timeouts++;
                sc_hist_push(0xFE);
                break;
            }
            sc_hist_push((unsigned char)sc2);
            {
                unsigned char r2 = (unsigned char)sc2;
                int press = !(r2 & 0x80);
                ext_down[r2 & 0x7F] = press;
                if (press && (r2 & 0x7F) == EXT_F11)
                    mc_toggle_zoom();
            }
            continue;
        }
        {
            unsigned char r = (unsigned char)sc;
            int press = !(r & 0x80);
            key_down[r & 0x7F] = press;
            if ((r & 0x7F) == SC_ESC && press)
                esc_latch = 1;
            if (!press)
                continue;
            if ((r & 0x7F) >= SC_1 && (r & 0x7F) <= SC_9)
                hot_sel = (r & 0x7F) - SC_1;
            if ((r & 0x7F) == SC_F) {
                mc_fly = !mc_fly;
                pl_vz = 0;
                printf("minicraft: fly %s\n", mc_fly ? "on" : "off");
            }
            /* G mirrors F11: QEMU 11 drops the E0 prefix of F11/F12 over
             * QMP, so a non-extended zoom key is required in this setup. */
            if ((r & 0x7F) == SC_G)
                mc_toggle_zoom();
            if ((r & 0x7F) == SC_T) {
                int px = (int)pl_x, py = (int)pl_y;
                int gz = -1, z;
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
            if ((r & 0x7F) == SC_K || (r & 0x7F) == SC_L) {
                const Recipe *rc = &recipes[(r & 0x7F) == SC_K ? 0 : 1];
                if (inv_remove(rc->in_block, rc->in_count)) {
                    inv_add(rc->out_block, rc->out_count);
                    snprintf(last_act, sizeof(last_act), "+%d %s",
                        rc->out_count, mc_block_name((unsigned char)rc->out_block));
                    last_act_ms = frame_ms;
                    printf("minicraft: crafted %d %s\n",
                        rc->out_count, mc_block_name((unsigned char)rc->out_block));
                    beep(660, 60);
                } else {
                    snprintf(last_act, sizeof(last_act), "NEED %d %s",
                        rc->in_count, mc_block_name((unsigned char)rc->in_block));
                    last_act_ms = frame_ms;
                }
            }
            if ((r & 0x7F) == SC_J || (r & 0x7F) == SC_U ||
                (r & 0x7F) == SC_I || (r & 0x7F) == SC_O) {
                int tool = ((r & 0x7F) == SC_J) ? TOOL_PICKAXE :
                    ((r & 0x7F) == SC_U) ? TOOL_AXE :
                    ((r & 0x7F) == SC_I) ? TOOL_SHOVEL : TOOL_SWORD;
                int cost = (tool == TOOL_SHOVEL) ? 2 : (tool == TOOL_SWORD) ? 3 : 4;
                const char *tname = tool == TOOL_PICKAXE ? "PICK" :
                    tool == TOOL_AXE ? "AXE" : tool == TOOL_SHOVEL ? "SHOVEL" : "SWORD";
                if (have_tool[tool]) {
                    snprintf(last_act, sizeof(last_act), "GOT %s", tname);
                    last_act_ms = frame_ms;
                } else if (inv_remove(B_PLANKS, cost)) {
                    have_tool[tool] = 1;
                    snprintf(last_act, sizeof(last_act), "+%s", tname);
                    last_act_ms = frame_ms;
                    printf("minicraft: crafted %s\n", tname);
                    beep(700, 60);
                } else {
                    snprintf(last_act, sizeof(last_act), "NEED %d PLANKS", cost);
                    last_act_ms = frame_ms;
                }
            }
            if ((r & 0x7F) == SC_E || (r & 0x7F) == SC_Q) {
                if (pork > 0 && (pl_hunger < MC_HUNGER_MAX || pl_hp < MC_HP_MAX)) {
                    pork--;
                    world_dirty = 1;
                    pl_hunger += 6;
                    if (pl_hunger > MC_HUNGER_MAX)
                        pl_hunger = MC_HUNGER_MAX;
                    if (pl_hp < MC_HP_MAX) {
                        pl_hp += 1;
                        if (pl_hp > MC_HP_MAX)
                            pl_hp = MC_HP_MAX;
                    }
                    {
                        int fh = pl_hunger < 0 ? 0 : pl_hunger > 99 ? 99 : pl_hunger;
                        int hh = pl_hp < 0 ? 0 : pl_hp > 99 ? 99 : pl_hp;
                        snprintf(last_act, sizeof(last_act), "F%d HP%d", fh, hh);
                    }
                    last_act_ms = frame_ms;
                    beep(440, 80);
                } else if (pork <= 0) {
                    snprintf(last_act, sizeof(last_act), "NO PORK");
                    last_act_ms = frame_ms;
                } else {
                    snprintf(last_act, sizeof(last_act), "FULL");
                    last_act_ms = frame_ms;
                }
            }
            if ((r & 0x7F) == SC_B) {
                if (inv_remove(B_PLANKS, 4)) {
                    inv_add(B_BED, 1);
                    snprintf(last_act, sizeof(last_act), "+BED");
                    last_act_ms = frame_ms;
                    printf("minicraft: crafted bed\n");
                    beep(600, 60);
                } else {
                    snprintf(last_act, sizeof(last_act), "NEED 4 PLANKS");
                    last_act_ms = frame_ms;
                }
            }
            if ((r & 0x7F) == SC_N) {
                mc_seed++;
                new_world(mc_seed);
                if (save_world() != 0) {
                    snprintf(last_act, sizeof(last_act), "SAVE FAIL");
                    last_act_ms = frame_ms;
                    printf("minicraft: save failed\n");
                } else {
                    printf("minicraft: new world\n");
                }
            }
            if (((r & 0x7F) == SC_V || ((r & 0x7F) == SC_C && !mc_fly))) {
                pl_pitch = 0;
                printf("minicraft: view leveled\n");
            }
            if ((r & 0x7F) == SC_P) {
                RayHit th = cast_ray(pl_x, pl_y, eye_z(),
                                     cosf(pl_yaw) * cosf(pl_pitch),
                                     sinf(pl_yaw) * cosf(pl_pitch),
                                     sinf(pl_pitch), 6.0f);
                printf("minicraft: pos %d %d %d chunk %d %d yaw %.2f pitch %.2f tgt %s wood %d\n",
                       (int)pl_x, (int)pl_y, (int)pl_z,
                       chunk_of((int)floorf(pl_x)), chunk_of((int)floorf(pl_y)),
                       pl_yaw, pl_pitch,
                       th.hit ? mc_block_name(get_b(th.bx, th.by, th.bz)) : "-",
                       inv[B_LOG]);
                {
                    char scline[64];
                    int o = 0, i;
                    for (i = 0; i < sc_hist_n && o < 56; i++)
                        o += snprintf(scline + o, sizeof(scline) - (size_t)o,
                            "%02X ", sc_hist[i]);
                    printf("minicraft: sc %s timeouts=%d\n", scline, sc_seq_timeouts);
                    sc_hist_n = 0;
                }
            }
        }
    }
    /* Serial consoles never produce scancodes, so gameplay ESC would be
     * unreachable headless: one serial ESC arms the pause menu exactly
     * like the press edge above, and the main loop clears the latch.
     * At most one wire byte per frame, and stashed bytes belong to
     * whoever owns the next menu: draining the whole wire here would
     * eat bytes addressed past the game (the shell poweroff after a
     * scripted quit), with no way to put a front byte back. */
    long b;
    if (ser_stash_n > 0)
        return;
    b = s_getc_raw();
    if (b < 0)
        return;
    if (b == 27L)
        esc_latch = 1;
    else if (b >= 0 && b <= 255L)
        ser_unget((unsigned char)b);
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
        pl_hunger = MC_HUNGER_MAX;
        hunger_ms = frame_ms;
        pork = 0;
        pl_x = spawn_x;
        pl_y = spawn_y;
        pl_z = spawn_z;
        pl_vz = 0;
        n_respawns++;
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
            int moved_x, moved_y;
            mx = mx / l * speed * dt;
            my = my / l * speed * dt;
            move_x(pl_x + mx);
            move_y(pl_y + my);
            moved_x = (pl_x != ox);
            moved_y = (pl_y != oy);
            if (!mc_fly && !feet_wet && pl_on_ground && (!moved_x || !moved_y))
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
            top = col_top_at(x, y);
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

static void tick_hunger(long now) {
    if (hunger_ms == 0)
        hunger_ms = now;
    if (now - hunger_ms >= MC_HUNGER_MS) {
        hunger_ms = now;
        if (pl_hunger > 0)
            pl_hunger--;
        else
            hurt(1, "HUNGER");
    }
}

static const char *goal_text(void) {
    switch (goal_idx) {
    case 0: return "G:4 WOOD";
    case 1: return "G:16 PLANKS(K)";
    case 2: return "G:PICK(J)";
    case 3: return "G:1 PORK";
    case 4: return "G:PLACE BED";
    default: return "G:DONE";
    }
}

static void tick_goals(void) {
    if (goal_idx == 0 && inv[B_LOG] >= 4)
        goal_idx = 1;
    else if (goal_idx == 1 && inv[B_PLANKS] >= 16)
        goal_idx = 2;
    else if (goal_idx == 2 && have_tool[TOOL_PICKAXE])
        goal_idx = 3;
    else if (goal_idx == 3 && pork >= 1)
        goal_idx = 4;
}

static void tick_discover(long now) {
    int px = (int)pl_x, py = (int)pl_y;
    int desert, snowy, water = 0;
    int z;
    if (now - discover_ms < 1000)
        return;
    discover_ms = now;
    desert = biome_desert(px, py, mc_seed);
    snowy = biome_snow(px, py, mc_seed);
    for (z = (int)pl_z - 2; z <= (int)pl_z + 1; z++) {
        if (get_b(px, py, z) == B_WATER) {
            water = 1;
            break;
        }
    }
    if (desert && !discovered_desert) {
        discovered_desert = 1;
        snprintf(last_act, sizeof(last_act), "DESIERTO!");
        last_act_ms = now;
        printf("minicraft: discovered desert\n");
    }
    if (snowy && !discovered_snow) {
        discovered_snow = 1;
        snprintf(last_act, sizeof(last_act), "NIEVE!");
        last_act_ms = now;
        printf("minicraft: discovered snow\n");
    }
    if (water && !discovered_water) {
        discovered_water = 1;
        snprintf(last_act, sizeof(last_act), "AGUA!");
        last_act_ms = now;
        printf("minicraft: discovered water\n");
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
            if (break_active && now - break_seen >= MC_BREAK_GRACE_MS) {
                break_active = 0;
                break_progress = 0;
            }
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
            int pi, hit_id = -1;
            Pig *hit_pp = 0;
            float best = 1e30f;
            for (pi = 0; pi < MC_PIGS + n_creeps; pi++) {
                Pig *cand = pi < MC_PIGS ? &pigs[pi] : &creeps[pi - MC_PIGS];
                float ex = cand->x - pl_x;
                float ey = cand->y - pl_y;
                float ezz = (cand->z + 0.5f) - eye_z();
                float fwd = ex * dx + ey * dy + ezz * dz;
                float perp;
                if (!cand->alive || fwd < 0.5f || fwd > MC_REACH)
                    continue;
                perp = sqrtf(ex * ex + ey * ey + ezz * ezz - fwd * fwd);
                if (perp < 0.9f && fwd < best) {
                    best = fwd;
                    hit_id = pi;
                    hit_pp = cand;
                }
            }
            if (hit_pp && (!h.hit || best < h.dist)) {
                Pig *pp = hit_pp;
                if (now >= pp->hurt_until) {
                    int dmg = have_tool[TOOL_SWORD] ? 6 : 4;
                    float kl = 0.8f, klx = 0, kly = 0;
                    float kd;
                    pp->hp -= dmg;
                    pp->hurt_until = now + MC_PIG_HURT_MS;
                    kd = sqrtf((pp->x - pl_x) * (pp->x - pl_x) +
                        (pp->y - pl_y) * (pp->y - pl_y));
                    if (kd > 0.01f) {
                        klx = (pp->x - pl_x) / kd * kl;
                        kly = (pp->y - pl_y) / kd * kl;
                        if (!pig_collides(pp->x + klx, pp->y, pp->z))
                            pp->x += klx;
                        if (!pig_collides(pp->x, pp->y + kly, pp->z))
                            pp->y += kly;
                    }
                    if (pp->hp <= 0) {
                        pp->alive = 0;
                        pp->respawn_ms = now;
                        pp->fuse_ms = 0;
                        world_dirty = 1;
                        if (pp->kind == MOB_CREEP) {
                            snprintf(last_act, sizeof(last_act), "CREEP DOWN");
                            last_act_ms = now;
                            printf("minicraft: creeper down\n");
                            beep(520, 70);
                        } else {
                            int drop = 1 + (int)(hash2(hit_id, (int)(now / 1000)) % 3);
                            pork += drop;
                            snprintf(last_act, sizeof(last_act), "+PORK %d", pork);
                            last_act_ms = now;
                            printf("minicraft: pork %d\n", pork);
                            beep(520, 70);
                        }
                    } else {
                        snprintf(last_act, sizeof(last_act), "HIT %d", pp->hp);
                        last_act_ms = now;
                        beep(330, 50);
                    }
                }
                last_edit_ms = now;
                prev_buttons = m[2];
                return;
            }
        }
        if (!h.hit) {
            if (break_active && now - break_seen >= MC_BREAK_GRACE_MS) {
                break_active = 0;
                break_progress = 0;
            }
            prev_buttons = m[2];
            return;
        }
        if (lb && (lb_edge || lb_hold)) {
            unsigned char b = get_b(h.bx, h.by, h.bz);
            if (b == B_BEDROCK || b == B_AIR || b == B_WATER) {
                break_active = 0;
                break_progress = 0;
            } else {
                int tool = best_tool_for(b);
                long need = break_time_ms(b, tool);
                if (!break_active || h.bx != break_bx || h.by != break_by || h.bz != break_bz) {
                    break_active = 1;
                    break_bx = h.bx;
                    break_by = h.by;
                    break_bz = h.bz;
                    break_start = now;
                    break_dur = need;
                    break_progress = 0;
                    break_seen = now;
                } else {
                    break_dur = need;
                    break_seen = now;
                    break_progress = (float)(now - break_start) / (float)(need > 0 ? need : 1);
                    if (break_progress < 0)
                        break_progress = 0;
                    if (break_progress >= 1.0f) {
                        set_b(h.bx, h.by, h.bz, B_AIR);
                        inv_add(b, 1);
                        snprintf(last_act, sizeof(last_act), "-%s", mc_block_name(b));
                        last_act_ms = now;
                        beep(break_beep_for(b), 50);
                        if (b == B_LOG && inv[b] == 10) {
                            printf("minicraft: GOAL firewood x10 DONE\n");
                            snprintf(last_act, sizeof(last_act), "GOAL DONE");
                            last_act_ms = now;
                            beep(880, 120);
                        }
                        break_active = 0;
                        break_progress = 0;
                        last_edit_ms = now;
                    }
                }
            }
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
                        if (nb == B_BED) {
                            spawn_x = pl_x;
                            spawn_y = pl_y;
                            spawn_z = pl_z;
                            if (goal_idx == 4)
                                goal_idx = 5;
                            snprintf(last_act, sizeof(last_act), "SPAWN BED");
                            printf("minicraft: spawn set at bed\n");
                        } else {
                            snprintf(last_act, sizeof(last_act), "+%s", mc_block_name(nb));
                        }
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

/* Frozen v3 header (saves already on disk); v4 appends mobs_n. */
typedef struct {
    uint32_t magic;
    uint32_t version;
    uint32_t world_size;
    uint32_t seed;
    float px, py, pz, yaw, pitch;
    int32_t hot_sel;
    int32_t hp;
    int32_t pork_n;
    int32_t hunger;
    int32_t inv[B_COUNT];
    uint32_t crc;
} SaveHeaderV3;

typedef struct {
    uint32_t magic;
    uint32_t version;
    uint32_t world_size;
    uint32_t seed;
    float px, py, pz, yaw, pitch;
    int32_t hot_sel;
    int32_t hp;
    int32_t pork_n;
    int32_t hunger;
    int32_t mobs_n;
    int32_t inv[B_COUNT];
    uint32_t crc;
} SaveHeader;

typedef struct {
    uint32_t magic;
    uint32_t version;
    int32_t cx;
    int32_t cy;
    uint32_t seed;
    uint32_t crc;
} ChunkHeader;

#define MC_LEGACY_WORLD 131072u
static unsigned char carve_buf[MC_LEGACY_WORLD];

static uint32_t mc_crc32(const void *data, size_t len, uint32_t crc) {
    const unsigned char *p = (const unsigned char *)data;
    size_t i;
    int k;
    crc = ~crc;
    for (i = 0; i < len; i++) {
        crc ^= p[i];
        for (k = 0; k < 8; k++)
            crc = (crc & 1) ? (crc >> 1) ^ MC_SAVE_CRC_SEED : (crc >> 1);
    }
    return ~crc;
}

static uint32_t save_compute_crc(const SaveHeader *hd) {
    SaveHeader tmp = *hd;
    tmp.crc = 0;
    return mc_crc32(&tmp, sizeof(tmp), 0);
}

static void chunk_path(int cx, int cy, char *out, size_t n) {
    snprintf(out, n, "/saves/mc_c_%d_%d.bin", cx, cy);
}

static int save_chunk_file(int slot) {
    char path[64];
    FILE *f;
    ChunkHeader ch;
    if (!ch_used[slot])
        return 0;
    chunk_path(ch_cx[slot], ch_cy[slot], path, sizeof(path));
    f = fopen(path, "wb");
    if (!f)
        return -1;
    ch.magic = MC_CHUNK_MAGIC;
    ch.version = MC_CHUNK_VERSION;
    ch.cx = (int32_t)ch_cx[slot];
    ch.cy = (int32_t)ch_cy[slot];
    ch.seed = mc_seed;
    ch.crc = 0;
    ch.crc = mc_crc32(&ch, sizeof(ch), 0);
    ch.crc = mc_crc32(ch_blocks[slot], MC_CVOL, ch.crc);
    if (fwrite(&ch, 1, sizeof(ch), f) != sizeof(ch)) {
        fclose(f);
        return -1;
    }
    if (fwrite(ch_blocks[slot], 1, MC_CVOL, f) != MC_CVOL) {
        fclose(f);
        return -1;
    }
    if (fclose(f) != 0)
        return -1;
    ch_dirty[slot] = 0;
    return 0;
}

static int load_chunk_file(int slot, int cx, int cy) {
    char path[64];
    FILE *f;
    ChunkHeader ch;
    uint32_t crc;
    int z;
    chunk_path(cx, cy, path, sizeof(path));
    f = fopen(path, "rb");
    if (!f)
        return 0;
    if (fread(&ch, 1, sizeof(ch), f) != sizeof(ch)) {
        fclose(f);
        return 0;
    }
    if (ch.magic != MC_CHUNK_MAGIC || ch.version != MC_CHUNK_VERSION ||
        ch.cx != (int32_t)cx || ch.cy != (int32_t)cy || ch.seed != mc_seed) {
        fclose(f);
        return 0;
    }
    if (fread(ch_blocks[slot], 1, MC_CVOL, f) != MC_CVOL) {
        fclose(f);
        return 0;
    }
    fclose(f);
    {
        ChunkHeader tmp = ch;
        tmp.crc = 0;
        crc = mc_crc32(&tmp, sizeof(tmp), 0);
    }
    crc = mc_crc32(ch_blocks[slot], MC_CVOL, crc);
    if (crc != ch.crc)
        return 0;
    for (z = 0; z < MC_CVOL; z++) {
        if (ch_blocks[slot][z] >= B_COUNT)
            return 0;
    }
    return 1;
}

/* Direct write, no tmp+rename: the kernel has no rename(82) (UNIMPL),
 * only unlink(87). A torn write is fail-closed by the CRC check on load. */
static int save_world(void) {
    FILE *f = fopen(SAVE_PATH, "wb");
    SaveHeader hd;
    size_t i;
    int s, rc = 0;
    if (!f)
        return -1;
    hd.magic = MC_SAVE_MAGIC;
    hd.version = MC_SAVE_VERSION;
    hd.world_size = (uint32_t)MC_CVOL;
    hd.seed = mc_seed;
    hd.px = pl_x;
    hd.py = pl_y;
    hd.pz = pl_z;
    hd.yaw = pl_yaw;
    hd.pitch = pl_pitch;
    hd.hot_sel = (int32_t)hot_sel;
    hd.hp = (int32_t)pl_hp;
    hd.pork_n = (int32_t)pork;
    hd.hunger = (int32_t)pl_hunger;
    hd.mobs_n = (int32_t)n_creeps;
    for (i = 0; i < B_COUNT; i++)
        hd.inv[i] = (int32_t)inv[i];
    hd.crc = 0;
    hd.crc = save_compute_crc(&hd);
    if (fwrite(&hd, 1, sizeof(hd), f) != sizeof(hd)) {
        fclose(f);
        return -1;
    }
    if (fclose(f) != 0)
        return -1;
    for (s = 0; s < MC_CHUNKS; s++) {
        if (ch_used[s] && ch_dirty[s] && save_chunk_file(s) != 0)
            rc = -1;
    }
    unlink(SAVE_TMP_PATH);
    if (rc == 0)
        world_dirty = 0;
    return rc;
}

static int save_validate_loaded(void) {
    int k;
    if (!(pl_z >= 0 && pl_z < MC_H))
        return -1;
    if (hot_sel < 0 || hot_sel > 8)
        hot_sel = 0;
    if (pl_hp < 1 || pl_hp > MC_HP_MAX)
        pl_hp = MC_HP_MAX;
    if (pork < 0 || pork > MC_INV_MAX)
        pork = 0;
    if (pl_hunger < 0 || pl_hunger > MC_HUNGER_MAX)
        pl_hunger = MC_HUNGER_MAX;
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
        pigs[i].yaw = 0;
        pigs[i].kind = MOB_PIG;
        pigs[i].turn_ms = 0;
        mob_spawn_one(&pigs[i], i, MC_PIG_HP, frame_ms);
    }
    for (i = 0; i < MC_CREEPS_MAX; i++) {
        creeps[i].yaw = 0;
        creeps[i].kind = MOB_CREEP;
        creeps[i].turn_ms = 0;
        if (i < n_creeps) {
            mob_spawn_one(&creeps[i], MC_PIGS + i, MC_CREEP_HP, frame_ms);
        } else {
            creeps[i].alive = 0;
            creeps[i].respawn_ms = 0;
            creeps[i].fuse_ms = 0;
        }
    }
    synced_n = n_creeps;
    world_dirty = 0;
}

/* Import a 64x64x32 legacy blob into chunks (0..3, 0..3), then dirty so
 * region files persist it. Old saves keep their world, new code owns it. */
static void carve_blob(const unsigned char *blob) {
    int cx, cy, x, y, z, s;
    for (cy = 0; cy < 4; cy++) {
        for (cx = 0; cx < 4; cx++)
            chunk_ensure(cx, cy);
    }
    for (y = 0; y < 64; y++) {
        for (x = 0; x < 64; x++) {
            for (z = 0; z < MC_H; z++) {
                unsigned char b = blob[(z * 64 + y) * 64 + x];
                if (b < B_COUNT)
                    set_b_raw(x, y, z, b);
            }
        }
    }
    for (cy = 0; cy < 4; cy++) {
        for (cx = 0; cx < 4; cx++) {
            s = chunk_find(cx, cy);
            if (s >= 0) {
                chunk_build_meta(s);
                ch_dirty[s] = 1;
            }
        }
    }
    world_max_recompute();
}

/* Legacy raw save: fixed old_inv[12] layout is fragile if B_COUNT grows;
 * kept read-only for ancient saves, never written. Do not extend. */
static int load_world_legacy(FILE *f) {
    float st[6];
    int i;
    if (fread(carve_buf, 1, sizeof(carve_buf), f) != sizeof(carve_buf))
        return -1;
    carve_blob(carve_buf);
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
    ensure_around();
    if (save_validate_loaded() != 0)
        return -1;
    load_reset_runtime();
    return 0;
}

static void load_apply_player(const SaveHeader *hd) {
    size_t i;
    mc_seed = hd->seed;
    pl_x = hd->px;
    pl_y = hd->py;
    pl_z = hd->pz;
    pl_yaw = hd->yaw;
    pl_pitch = hd->pitch;
    hot_sel = (int)hd->hot_sel;
    pl_hp = (int)hd->hp;
    pork = (int)hd->pork_n;
    pl_hunger = (int)hd->hunger;
    n_creeps = (int)hd->mobs_n;
    if (n_creeps < 0 || n_creeps > MC_CREEPS_MAX)
        n_creeps = MC_CREEPS_DEF;
    for (i = 0; i < B_COUNT; i++)
        inv[i] = (int)hd->inv[i];
}

static int load_world_v3(FILE *f, SaveHeader *hd) {
    SaveHeaderV3 old;
    size_t i;
    if (fread(&old.seed, 1, sizeof(old) - sizeof(uint32_t) * 3, f) !=
        sizeof(old) - sizeof(uint32_t) * 3)
        return -1;
    if (fread(carve_buf, 1, sizeof(carve_buf), f) != sizeof(carve_buf))
        return -1;
    hd->magic = old.magic;
    hd->version = old.version;
    hd->world_size = old.world_size;
    hd->seed = old.seed;
    hd->px = old.px;
    hd->py = old.py;
    hd->pz = old.pz;
    hd->yaw = old.yaw;
    hd->pitch = old.pitch;
    hd->hot_sel = old.hot_sel;
    hd->hp = old.hp;
    hd->pork_n = old.pork_n;
    hd->hunger = old.hunger;
    hd->mobs_n = MC_CREEPS_DEF;
    for (i = 0; i < B_COUNT; i++)
        hd->inv[i] = old.inv[i];
    hd->crc = old.crc;
    {
        SaveHeaderV3 tmp = old;
        uint32_t crc;
        tmp.crc = 0;
        crc = mc_crc32(&tmp, sizeof(tmp), 0);
        crc = mc_crc32(carve_buf, sizeof(carve_buf), crc);
        if (crc != old.crc)
            return -1;
    }
    mc_seed = hd->seed;
    carve_blob(carve_buf);
    load_apply_player(hd);
    return 0;
}

static int load_world_v2(FILE *f, SaveHeader *hd) {
    SaveHeaderV3 old;
    size_t tail = sizeof(SaveHeaderV3) - sizeof(uint32_t) * 3 -
        sizeof(int32_t) - sizeof(uint32_t);
    size_t i;
    memset(&old, 0, sizeof(old));
    if (fread(&old.seed, 1, tail, f) != tail)
        return -1;
    if (fread(carve_buf, 1, sizeof(carve_buf), f) != sizeof(carve_buf))
        return -1;
    old.magic = MC_SAVE_MAGIC;
    old.version = 2;
    old.world_size = MC_LEGACY_WORLD;
    old.hunger = MC_HUNGER_MAX;
    hd->magic = old.magic;
    hd->version = old.version;
    hd->world_size = old.world_size;
    hd->seed = old.seed;
    hd->px = old.px;
    hd->py = old.py;
    hd->pz = old.pz;
    hd->yaw = old.yaw;
    hd->pitch = old.pitch;
    hd->hot_sel = old.hot_sel;
    hd->hp = old.hp;
    hd->pork_n = old.pork_n;
    hd->hunger = old.hunger;
    hd->mobs_n = MC_CREEPS_DEF;
    for (i = 0; i < B_COUNT; i++)
        hd->inv[i] = old.inv[i];
    hd->crc = 0;
    mc_seed = hd->seed;
    carve_blob(carve_buf);
    load_apply_player(hd);
    return 0;
}

static int load_world(void) {
    FILE *f = fopen(SAVE_PATH, "rb");
    SaveHeader hd;
    size_t i;
    int k, r = -1;
    uint32_t pre[3];
    if (!f)
        return -1;
    if (fread(pre, 1, sizeof(pre), f) != sizeof(pre)) {
        fclose(f);
        return -1;
    }
    if (pre[0] != MC_SAVE_MAGIC) {
        rewind(f);
        r = load_world_legacy(f);
        fclose(f);
        return r;
    }
    memset(&hd, 0, sizeof(hd));
    hd.magic = pre[0];
    hd.version = pre[1];
    hd.world_size = pre[2];
    if (hd.version == MC_SAVE_VERSION) {
        size_t tail = sizeof(hd) - sizeof(pre);
        if (fread(&hd.seed, 1, tail, f) == tail &&
            save_compute_crc(&hd) == hd.crc) {
            fclose(f);
            load_apply_player(&hd);
            r = 0;
        } else {
            fclose(f);
            return -1;
        }
    } else if (hd.version == 3 && hd.world_size == MC_LEGACY_WORLD) {
        if (load_world_v3(f, &hd) == 0) {
            fclose(f);
            r = 0;
        } else {
            fclose(f);
            return -1;
        }
    } else if (hd.version == 2 && hd.world_size == MC_LEGACY_WORLD) {
        if (load_world_v2(f, &hd) == 0) {
            fclose(f);
            r = 0;
        } else {
            fclose(f);
            return -1;
        }
    } else {
        rewind(f);
        r = load_world_legacy(f);
        fclose(f);
        return r;
    }
    if (r != 0)
        return -1;
    ensure_around();
    if (save_validate_loaded() != 0)
        return -1;
    for (k = 0; k < B_COUNT; k++) {
        if (inv[k] < 0 || inv[k] > MC_INV_MAX)
            inv[k] = 0;
    }
    load_reset_runtime();
    if (save_validate_loaded() != 0)
        return -1;
    for (i = 0; i < B_COUNT; i++) {
        if (inv[i] < 0 || inv[i] > MC_INV_MAX)
            inv[i] = 0;
    }
    return 0;
}

static int selftest(void) {
    int n_solid = 0;
    int i;
    new_world(1);
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
        ensure_around_px(32.5f, 32.5f);
        for (cx = 28; cx <= 37; cx++) {
            for (cy = 28; cy <= 37; cy++) {
                for (cz = 19; cz <= 23; cz++)
                    set_b(cx, cy, cz, B_AIR);
            }
        }
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
    if (!(MC_BREAK_GRACE_MS > MC_BREAK_MS)) {
        printf("minicraft: selftest FAIL (break grace <= repeat delay)\n");
        return 1;
    }
    {
        SaveHeader hd;
        memset(&hd, 0, sizeof(hd));
        hd.magic = MC_SAVE_MAGIC;
        hd.version = MC_SAVE_VERSION;
        hd.world_size = (uint32_t)MC_CVOL;
        if (hd.magic != MC_SAVE_MAGIC || hd.version != MC_SAVE_VERSION ||
            hd.world_size != MC_CVOL) {
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
        {
            long t0 = 100000;
            set_b(11, 10, 10, B_STONE);
            set_b(12, 10, 10, B_STONE);
            creeps[0].x = 11.5f;
            creeps[0].y = 10.5f;
            creeps[0].z = 10.02f;
            creeps[0].yaw = 0;
            creeps[0].vz = 0;
            creeps[0].alive = 1;
            creeps[0].hp = MC_CREEP_HP;
            creeps[0].kind = MOB_CREEP;
            creeps[0].hurt_until = 0;
            creeps[0].attack_ms = 0;
            creeps[0].fuse_ms = 0;
            pl_hp = MC_HP_MAX;
            tick_mob(&creeps[0], MC_PIGS, 0.05f, t0);
            if (!creeps[0].fuse_ms) {
                printf("minicraft: selftest FAIL (fuse not lit)\n");
                return 1;
            }
            tick_mob(&creeps[0], MC_PIGS, 0.05f, creeps[0].fuse_ms + 10);
            if (creeps[0].alive) {
                printf("minicraft: selftest FAIL (no boom)\n");
                return 1;
            }
            if (get_b(11, 10, 10) != B_AIR || get_b(12, 10, 10) != B_AIR) {
                printf("minicraft: selftest FAIL (crater missing)\n");
                return 1;
            }
            if (pl_hp != MC_HP_MAX - 6) {
                printf("minicraft: selftest FAIL (blast dmg %d)\n", pl_hp);
                return 1;
            }
            creeps[1].x = 30.5f;
            creeps[1].y = 30.5f;
            creeps[1].z = 10.02f;
            creeps[1].yaw = 0;
            creeps[1].vz = 0;
            creeps[1].alive = 1;
            creeps[1].hp = MC_CREEP_HP;
            creeps[1].kind = MOB_CREEP;
            creeps[1].hurt_until = 0;
            creeps[1].attack_ms = 0;
            creeps[1].fuse_ms = t0 + MC_FUSE_MS;
            tick_mob(&creeps[1], MC_PIGS + 1, 0.05f, t0 + 100);
            if (creeps[1].fuse_ms) {
                printf("minicraft: selftest FAIL (no defuse)\n");
                return 1;
            }
            if (!creeps[1].alive) {
                printf("minicraft: selftest FAIL (defused boom)\n");
                return 1;
            }
            {
                int g1 = 0, g0 = 0, sx, sy;
                pl_x = 32.5f;
                pl_y = 32.5f;
                pl_z = 20.02f;
                pl_yaw = 0;
                pl_pitch = 0;
                creeps[2].x = 34.5f;
                creeps[2].y = 32.5f;
                creeps[2].z = 21.0f;
                creeps[2].yaw = 0;
                creeps[2].vz = 0;
                creeps[2].alive = 1;
                creeps[2].hp = MC_CREEP_HP;
                creeps[2].kind = MOB_CREEP;
                creeps[2].hurt_until = 0;
                creeps[2].attack_ms = 0;
                creeps[2].fuse_ms = 0;
                render_frame();
                for (sy = 0; sy < FB_H; sy++)
                    for (sx = 0; sx < FB_W; sx++) {
                        unsigned char c = BACKBUF[sy * FB_W + sx];
                        if (c == 25 || c == 26)
                            g1++;
                    }
                creeps[2].alive = 0;
                render_frame();
                for (sy = 0; sy < FB_H; sy++)
                    for (sx = 0; sx < FB_W; sx++) {
                        unsigned char c = BACKBUF[sy * FB_W + sx];
                        if (c == 25 || c == 26)
                            g0++;
                    }
                if (g1 < g0 + 50) {
                    printf("minicraft: selftest FAIL (creeper not green)\n");
                    return 1;
                }
            }
        }
    }
    printf("minicraft: frame ok (%dx%d)\n", FB_W, FB_H);
    return 0;
}

#ifdef MINICRAFT_HOST_TEST
/* 128x128 columns (64 biome cells): a 64-wide patch covers too few
 * 16-block biome cells and the desert rate fluctuates wildly by area. */
static int census(void) {
    int cx, cy, x, y, z;
    int desert = 0, snow = 0, water = 0, logs = 0, land = 0;
    int hmin = MC_H, hmax = 0, lakes = 0, peaks = 0;
    new_world(1);
    for (cy = -4; cy < 4; cy++) {
        for (cx = -4; cx < 4; cx++) {
            int s = chunk_ensure(cx, cy);
            if (s < 0)
                continue;
            if (!ch_decor[s]) {
                ch_decor[s] = 1;
                decorate_chunk(s);
            }
            for (y = 0; y < MC_CHUNK; y++) {
                for (x = 0; x < MC_CHUNK; x++) {
                    int wx = cx * MC_CHUNK + x, wy = cy * MC_CHUNK + y;
                    int top = ch_top[s][y * MC_CHUNK + x];
                    unsigned char b;
                    int has_log = 0;
                    if (top < 0)
                        continue;
                    for (z = 0; z <= top; z++) {
                        if (ch_blocks[s][chunk_lidx(x, y, z)] == B_LOG) {
                            has_log = 1;
                            break;
                        }
                    }
                    if (has_log)
                        logs++;
                    b = ch_blocks[s][chunk_lidx(x, y, top)];
                    (void)wx;
                    (void)wy;
                    if (b == B_WATER) {
                        water++;
                        continue;
                    }
                    land++;
                    if (top < hmin)
                        hmin = top;
                    if (top > hmax)
                        hmax = top;
                    if (top <= 8)
                        lakes++;
                    if (top >= 19)
                        peaks++;
                    if (b == B_SAND && top > 8)
                        desert++;
                    if (b == B_SNOW)
                        snow++;
                }
            }
        }
    }
    printf("minicraft: census land=%d desert=%d snow=%d water=%d treecols=%d hmin=%d hmax=%d lakes=%d peaks=%d\n",
        land, desert, snow, water, logs, hmin, hmax, lakes, peaks);
    if (land > 12000 && desert > land / 10 && snow > land / 20 && water > land / 100 && logs > 0) {
        printf("minicraft: census ok (biomes present)\n");
        return 0;
    }
    printf("minicraft: census FAIL (biome missing)\n");
    return 1;
}

static int dumpstats(void) {
    int x, y;
    long top_sky = 0, top_ground = 0, bot_sky = 0, bot_ground = 0;
    new_world(1);
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
        ensure_around_px(32.5f, 32.5f);
        for (cx = 20; cx <= 45; cx++) {
            for (cy = 20; cy <= 45; cy++) {
                for (cz = 18; cz <= 26; cz++)
                    set_b(cx, cy, cz, B_AIR);
            }
        }
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

/* Title menu (pokemon FILE-menu pattern, keyboard only): lets the player
 * pick CONTINUE (old save) or NEW WORLD with an editable seed, so a stale
 * save never hides new worldgen. Returns 0 = play loaded world,
 * 1 = play fresh world with *seed_io, -1 = quit to shell. */
static void menu_text_c(int y, const char *s, unsigned char fg, unsigned char bg) {
    int n = 0;
    const char *p;
    for (p = s; *p; p++)
        n++;
    mc_text_bg((FB_W - n * 4) / 2, y, s, fg, bg);
}

static int title_menu(int have_save, int *seed_io) {
    int seed = *seed_io < 1 ? 1 : *seed_io;
    int nrows = have_save ? 5 : 4;
    int seedrow = have_save ? 2 : 1;
    int sel = 0;
    int shift = 0;
    int esc_armed = 1;
    if (seed > MC_SEED_MAX)
        seed = MC_SEED_MAX;
    for (;;) {
        int i;
        char row0[32], row1[32], row2[32], zoomrow[32], creeprow[32];
        const char *rows[5];
        for (i = 0; i < FB_W * FB_H; i++)
            BACKBUF[i] = 3;
        menu_text_c(28, "MINICRAFT", 2, 3);
        menu_text_c(40, "VOXEL SURVIVAL", 2, 3);
        if (have_save)
            snprintf(row0, sizeof(row0), "CONTINUE SEED %d", seed);
        else
            snprintf(row0, sizeof(row0), "NEW WORLD");
        snprintf(row1, sizeof(row1), "%s", have_save ? "NEW WORLD" : "SEED");
        snprintf(row2, sizeof(row2), "SEED < %d >", seed);
        snprintf(zoomrow, sizeof(zoomrow), "FULLSCREEN %s", mc_zoom ? "ON" : "OFF");
        snprintf(creeprow, sizeof(creeprow), "CREEPS < %d >", n_creeps);
        rows[0] = row0;
        if (have_save) {
            rows[1] = row1;
            rows[2] = row2;
            rows[3] = zoomrow;
            rows[4] = creeprow;
        } else {
            rows[1] = row2;
            rows[2] = zoomrow;
            rows[3] = creeprow;
        }
        for (i = 0; i < nrows; i++) {
            char line[36];
            snprintf(line, sizeof(line), "%c %s", i == sel ? '>' : ' ', rows[i]);
            if (i == sel)
                menu_text_c(84 + i * 15, line, 3, 2);
            else
                menu_text_c(84 + i * 15, line, 2, 3);
        }
        menu_text_c(162, "UP/DN CHOOSE L/R EDIT", 2, 3);
        menu_text_c(172, "0-9 TYPE ENTER OK ESC QUIT", 2, 3);
        s_present();
        for (;;) {
            long sc = s_kbd();
            int press;
            unsigned char r;
            if (sc < 0 || sc > 0xFFFF) {
                long m = menu_ser_key(ser_get());
                if (m < 0) {
                    s_yield();
                    break;
                }
                sc = m;
            }
            if (sc == 0xE0) {
                long sc2 = s_kbd_seq();
                unsigned char r2;
                int step;
                if (sc2 < 0)
                    break;
                r2 = (unsigned char)sc2;
                if (r2 & 0x80)
                    break;
                r2 &= 0x7F;
                step = shift ? 10 : 1;
                if (r2 == EXT_UP || r2 == EXT_DOWN) {
                    sel = (sel + (r2 == EXT_UP ? nrows - 1 : 1)) % nrows;
                    break;
                }
                if (r2 == EXT_LEFT || r2 == EXT_RIGHT) {
                    int dir = (r2 == EXT_LEFT ? -1 : 1);
                    if (sel == seedrow) {
                        seed += dir * step;
                        if (seed < 1)
                            seed = 1;
                        if (seed > MC_SEED_MAX)
                            seed = MC_SEED_MAX;
                    } else if (sel == nrows - 1) {
                        n_creeps += dir * (shift ? 10 : 1);
                        if (n_creeps < 0)
                            n_creeps = 0;
                        if (n_creeps > MC_CREEPS_MAX)
                            n_creeps = MC_CREEPS_MAX;
                    }
                    break;
                }
                continue;
            }
            r = (unsigned char)sc;
            press = !(r & 0x80);
            r &= 0x7F;
            if (r == SC_LSHIFT || r == SC_RSHIFT) {
                shift = press;
                continue;
            }
            if (r == SC_ESC && !press) {
                esc_armed = 1;
                continue;
            }
            if (!press)
                continue;
            if (r == SC_ENTER) {
                *seed_io = seed;
                if (sel == nrows - 2) {
                    mc_toggle_zoom();
                    break;
                }
                if (sel == nrows - 1)
                    break;
                kbd_drain();
                if (!have_save)
                    return 1;
                if (sel == 0)
                    return 0;
                return 1;
            }
            if (r == SC_ESC) {
                if (!esc_armed)
                    continue;
                kbd_drain();
                return -1;
            }
            if (r == SC_W || r == SC_S) {
                sel = (sel + (r == SC_W ? nrows - 1 : 1)) % nrows;
                break;
            }
            if (r == SC_A || r == SC_D) {
                int step = shift ? 10 : 1;
                int dir = (r == SC_A ? -1 : 1);
                if (sel == seedrow) {
                    seed += dir * step;
                    if (seed < 1)
                        seed = 1;
                    if (seed > MC_SEED_MAX)
                        seed = MC_SEED_MAX;
                } else if (sel == nrows - 1) {
                    n_creeps += dir * (shift ? 10 : 1);
                    if (n_creeps < 0)
                        n_creeps = 0;
                    if (n_creeps > MC_CREEPS_MAX)
                        n_creeps = MC_CREEPS_MAX;
                }
                break;
            }
            if (r == SC_BACK) {
                seed /= 10;
                if (seed < 1)
                    seed = 1;
                break;
            }
            if ((r >= SC_1 && r <= SC_9) || r == SC_0) {
                int d = (r == SC_0) ? 0 : (r - SC_1 + 1);
                seed = (seed > MC_SEED_MAX / 10) ? d : seed * 10 + d;
                if (seed < 1)
                    seed = 1;
                break;
            }
        }
    }
}

/* Pause menu on ESC (Alt+F4 still kills the process kernel-side):
 * 0 = resume, 1 = new world with *seed_io, 2 = save + quit to shell. */
static int pause_menu(int *seed_io) {
    int seed = *seed_io < 1 ? 1 : *seed_io;
    int sel = 0;
    int shift = 0;
    int esc_armed = 1;
    char status[24];
    int nrows = 7;
    if (seed > MC_SEED_MAX)
        seed = MC_SEED_MAX;
    status[0] = 0;
    for (;;) {
        int i;
        char seedrow[32], zoomrow[32], creeprow[32];
        const char *rows[7];
        for (i = 0; i < FB_W * FB_H; i++)
            BACKBUF[i] = 3;
        menu_text_c(24, "PAUSA", 2, 3);
        rows[0] = "RESUME";
        rows[1] = "SAVE";
        rows[2] = "NEW WORLD";
        snprintf(seedrow, sizeof(seedrow), "SEED < %d >", seed);
        rows[3] = seedrow;
        snprintf(zoomrow, sizeof(zoomrow), "FULLSCREEN %s", mc_zoom ? "ON" : "OFF");
        rows[4] = zoomrow;
        snprintf(creeprow, sizeof(creeprow), "CREEPS < %d >", n_creeps);
        rows[5] = creeprow;
        rows[6] = "QUIT";
        for (i = 0; i < nrows; i++) {
            char line[36];
            snprintf(line, sizeof(line), "%c %s", i == sel ? '>' : ' ', rows[i]);
            if (i == sel)
                menu_text_c(72 + i * 14, line, 3, 2);
            else
                menu_text_c(72 + i * 14, line, 2, 3);
        }
        if (status[0])
            menu_text_c(172, status, 2, 3);
        menu_text_c(180, "UP/DN CHOOSE ENTER OK", 2, 3);
        menu_text_c(190, "ESC RESUME ALTF4 QUIT", 2, 3);
        s_present();
        for (;;) {
            long sc = s_kbd();
            int press;
            unsigned char r;
            if (sc < 0 || sc > 0xFFFF) {
                long m = menu_ser_key(ser_get());
                if (m < 0) {
                    s_yield();
                    break;
                }
                sc = m;
            }
            if (sc == 0xE0) {
                long sc2 = s_kbd_seq();
                unsigned char r2;
                int step;
                if (sc2 < 0)
                    break;
                r2 = (unsigned char)sc2;
                if (r2 & 0x80)
                    break;
                r2 &= 0x7F;
                step = shift ? 10 : 1;
                if (r2 == EXT_UP || r2 == EXT_DOWN) {
                    sel = (sel + (r2 == EXT_UP ? nrows - 1 : 1)) % nrows;
                    break;
                }
                if (r2 == EXT_LEFT || r2 == EXT_RIGHT) {
                    int dir = (r2 == EXT_LEFT ? -1 : 1);
                    if (sel == 3) {
                        seed += dir * step;
                        if (seed < 1)
                            seed = 1;
                        if (seed > MC_SEED_MAX)
                            seed = MC_SEED_MAX;
                    } else if (sel == 5) {
                        n_creeps += dir * (shift ? 10 : 1);
                        if (n_creeps < 0)
                            n_creeps = 0;
                        if (n_creeps > MC_CREEPS_MAX)
                            n_creeps = MC_CREEPS_MAX;
                    }
                    break;
                }
                continue;
            }
            r = (unsigned char)sc;
            press = !(r & 0x80);
            r &= 0x7F;
            if (r == SC_LSHIFT || r == SC_RSHIFT) {
                shift = press;
                continue;
            }
            if (r == SC_ESC && !press) {
                esc_armed = 1;
                continue;
            }
            if (!press)
                continue;
            if (r == SC_ESC) {
                if (!esc_armed)
                    continue;
                kbd_drain();
                return 0;
            }
            if (r == SC_ENTER) {
                *seed_io = seed;
                if (sel == 0) {
                    kbd_drain();
                    return 0;
                }
                if (sel == 1) {
                    if (save_world() == 0)
                        snprintf(status, sizeof(status), "SAVED");
                    else
                        snprintf(status, sizeof(status), "SAVE FAIL");
                    break;
                }
                if (sel == 2) {
                    kbd_drain();
                    return 1;
                }
                if (sel == 4) {
                    mc_toggle_zoom();
                    break;
                }
                if (sel == 5)
                    break;
                if (sel == 6) {
                    kbd_drain();
                    return 2;
                }
                break;
            }
            if (r == SC_W || r == SC_S) {
                sel = (sel + (r == SC_W ? nrows - 1 : 1)) % nrows;
                break;
            }
            if (r == SC_A || r == SC_D) {
                int step = shift ? 10 : 1;
                int dir = (r == SC_A ? -1 : 1);
                if (sel == 3) {
                    seed += dir * step;
                    if (seed < 1)
                        seed = 1;
                    if (seed > MC_SEED_MAX)
                        seed = MC_SEED_MAX;
                } else if (sel == 5) {
                    n_creeps += dir * (shift ? 10 : 1);
                    if (n_creeps < 0)
                        n_creeps = 0;
                    if (n_creeps > MC_CREEPS_MAX)
                        n_creeps = MC_CREEPS_MAX;
                }
                break;
            }
            if (r == SC_BACK) {
                seed /= 10;
                if (seed < 1)
                    seed = 1;
                break;
            }
            if ((r >= SC_1 && r <= SC_9) || r == SC_0) {
                int d = (r == SC_0) ? 0 : (r - SC_1 + 1);
                seed = (seed > MC_SEED_MAX / 10) ? d : seed * 10 + d;
                if (seed < 1)
                    seed = 1;
                break;
            }
        }
    }
}

int main(int argc, char **argv) {
    int i;
    int autoframes = 0;
    int zoomframes = 0;
    int walkframes = 0;
    int standframes = 0;
    int force_new = 0;
    int arg_seed = 1;
    int have_save = 0;
    int menu_seed = 1;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--selftest") == 0)
            return selftest();
#ifdef MINICRAFT_HOST_TEST
        if (strcmp(argv[i], "--dumpstats") == 0)
            return dumpstats();
        if (strcmp(argv[i], "--census") == 0)
            return census();
#endif
        if (strcmp(argv[i], "autoframes") == 0 && i + 1 < argc)
            autoframes = atoi(argv[i + 1]);
        if (strcmp(argv[i], "zoomframes") == 0 && i + 1 < argc)
            zoomframes = atoi(argv[i + 1]);
        if (strcmp(argv[i], "walkframes") == 0 && i + 1 < argc)
            walkframes = atoi(argv[i + 1]);
        if (strcmp(argv[i], "standframes") == 0 && i + 1 < argc)
            standframes = atoi(argv[i + 1]);
        if (strcmp(argv[i], "--once") == 0)
            autoframes = 1;
        if (strcmp(argv[i], "new") == 0 || strcmp(argv[i], "seed") == 0) {
            int v = 0;
            force_new = 1;
            if (i + 1 < argc)
                v = atoi(argv[i + 1]);
            if (v >= 1 && v <= MC_SEED_MAX)
                arg_seed = v;
        }
    }
    build_palette();
    if (force_new) {
        printf("minicraft: new world seed %d\n", arg_seed);
        new_world((unsigned int)arg_seed);
    } else if (load_world() != 0) {
        printf("minicraft: no save, new world\n");
        new_world(1);
    } else {
        hotbar[0] = B_GRASS;
        hotbar[1] = B_DIRT;
        hotbar[2] = B_STONE;
        hotbar[3] = B_PLANKS;
        hotbar[4] = B_LOG;
        hotbar[5] = B_LEAVES;
        hotbar[6] = B_SAND;
        hotbar[7] = B_BRICK;
        hotbar[8] = B_BED;
        if (hot_sel < 0 || hot_sel > 8)
            hot_sel = 0;
        printf("minicraft: save loaded\n");
        have_save = 1;
        menu_seed = (int)mc_seed;
    }
    s_vga(1);
    s_kbd_raw(1);
    s_title("Minicraft");
    s_pal(mc_pal);
    s_pcspk_init();
    printf("minicraft: WASD move, mouse/arrows look, Space jump/swim, Shift sprint\n");
    printf("minicraft: F fly (Space up, C down), 1-9/wheel select\n");
    printf("minicraft: hold left-click to break, right-click place, R save\n");
    printf("minicraft: K 4WOOD->16PLANKS, L 4PLANKS->4BRICK, B 4PLANKS->BED\n");
    printf("minicraft: J/U/I/O craft PICK/AXE/SHOVEL/SWORD, E/Q eat pork\n");
    printf("minicraft: T rescue to surface, N new world, V/C level view\n");
    printf("minicraft: P pos report, goals: WOOD>PLANKS>PICK>PORK>BED\n");
    printf("minicraft: Esc menu (resume/save/new/zoom/quit), Alt+F4 quits\n");
    printf("minicraft: G or F11 toggles 2x fullscreen zoom\n");
    printf("minicraft: title menu when run plain; 'minicraft new [seed]' skips it\n");
    fflush(stdout);
    if (!force_new && autoframes == 0 && zoomframes == 0 && walkframes == 0 && standframes == 0) {
        int mr = title_menu(have_save, &menu_seed);
        if (mr < 0) {
            s_zoom(0);
            return 0;
        }
        if (mr == 1) {
            printf("minicraft: new world seed %d\n", menu_seed);
            new_world((unsigned int)menu_seed);
        }
        mobs_sync();
    }
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
    if (zoomframes > 0) {
        s_zoom(1);
        for (i = 0; i < zoomframes; i++) {
            pl_yaw += 0.08f;
            frame_ms += 16;
            render_frame();
            s_present();
        }
        s_zoom(0);
        printf("minicraft: played %d zoom frames, quitting\n", zoomframes);
        fflush(stdout);
        return 0;
    }
    if (walkframes > 0) {
        int f, sx0, sy0;
        mc_fly = 1;
        pl_yaw = 0;
        key_down[SC_SPACE] = 1;
        for (f = 0; f < 200 && pl_z < 28.0f; f++) {
            frame_ms += 16;
            ensure_around();
            tick_player(1.0f / 60.0f);
            if ((f & 3) == 0) {
                render_frame();
                s_present();
            }
        }
        key_down[SC_SPACE] = 0;
        key_down[SC_W] = 1;
        sx0 = chunk_of((int)floorf(pl_x));
        sy0 = chunk_of((int)floorf(pl_y));
        for (f = 0; f < walkframes; f++) {
            frame_ms += 16;
            ensure_around();
            tick_player(1.0f / 60.0f);
            tick_pigs(1.0f / 60.0f, frame_ms);
            if ((f & 3) == 0) {
                render_frame();
                s_present();
            }
        }
        key_down[SC_W] = 0;
        printf("minicraft: walked %d frames chunk %d %d -> %d %d z %.1f, quitting\n",
            walkframes, sx0, sy0,
            chunk_of((int)floorf(pl_x)), chunk_of((int)floorf(pl_y)), pl_z);
        if (save_world() != 0)
            printf("minicraft: walk save failed\n");
        else
            printf("minicraft: walk saved\n");
        fflush(stdout);
        return 0;
    }
    /* Headless death-loop stress: stand still while mobs converge,
     * explode and kill the player; exercises explosion, hurt, respawn
     * and the dirty autosave exactly like interactive play, with a
     * serial-observable death count. Kills the BDD gap where death was
     * only reachable with a live keyboard. */
    if (standframes > 0) {
        int f;
        long save_at = frame_ms + MC_SAVE_SECS * 1000;
        for (f = 0; f < standframes; f++) {
            frame_ms += 16;
            ensure_around();
            tick_player(1.0f / 60.0f);
            tick_pigs(1.0f / 60.0f, frame_ms);
            tick_water(frame_ms);
            tick_hunger(frame_ms);
            tick_goals();
            tick_discover(frame_ms);
            if ((f & 3) == 0) {
                render_frame();
                s_present();
            }
            if (world_dirty && frame_ms > save_at) {
                if (save_world() != 0)
                    printf("minicraft: autosave failed\n");
                save_at = frame_ms + MC_SAVE_SECS * 1000;
            }
        }
        printf("minicraft: stood %d frames deaths %ld dirty %d, quitting\n",
            standframes, n_respawns, world_dirty);
        if (save_world() != 0)
            printf("minicraft: stand save failed\n");
        else
            printf("minicraft: stand saved\n");
        fflush(stdout);
        return 0;
    }
    {
        long prev = s_time_ms();
        long save_at = prev + MC_SAVE_SECS * 1000;
        for (;;) {
            long now = s_time_ms();
            float dt = (float)(now - prev) / 1000.0f;
            float inst, phase;
            prev = now;
            frame_ms = now;
            if (dt < 0)
                dt = 0;
            if (dt > 0.1f)
                dt = 0.1f;
            inst = dt > 0.001f ? 1.0f / dt : 99.0f;
            fps_ema = fps_ema * 0.92f + inst * 0.08f;
            phase = (float)((now % MC_DAY_MS + MC_DAY_MS) % MC_DAY_MS) /
                (float)MC_DAY_MS;
            day_light = 0.5f + 0.5f * cosf(phase * 6.2831853f);
            poll_kbd();
            if (esc_latch) {
                int pr;
                esc_latch = 0;
                pr = pause_menu(&menu_seed);
                key_down[SC_ESC] = 0;
                hunger_ms = s_time_ms();
                if (pr == 2) {
                    if (save_world() != 0)
                        printf("minicraft: save failed\n");
                    s_zoom(0);
                    return 0;
                }
                if (pr == 1) {
                    printf("minicraft: new world seed %d\n", menu_seed);
                    new_world((unsigned int)menu_seed);
                }
                mobs_sync();
                save_at = s_time_ms() + MC_SAVE_SECS * 1000;
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
            ensure_around();
            tick_player(dt);
            tick_pigs(dt, now);
            tick_water(now);
            tick_hunger(now);
            tick_goals();
            tick_discover(now);
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
