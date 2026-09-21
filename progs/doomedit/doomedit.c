/** doomedit.c - tile map editor that builds playable Doom PWADs.
 *
 * A ring-3 Nuklear application built exactly like the node editor
 * (host gcc -static -no-pie, ships on MiniFS with a bare-name alias).
 * The author paints walls, the player start, the exit switch marker
 * and a full thing palette on a tile canvas, watches a live DDA
 * raycaster preview in the Wolfenstein style of the sibling
 * ../raycastlib checkout, exports a multi-sector E1M1 PWAD snapshot
 * into /saves, and boots the shipped Doom on it without ever writing
 * to the immutable IWAD.
 *
 *     doomedit                      -> GUI editor
 *     doomedit --demo <out.wad>     -> write a fixed demo room PWAD
 *     doomedit --preset <0-8> <wad> -> write a bundled level PWAD
 *     doomedit --export <grid> <wad> -> compile a grid text file
 *     doomedit --check <file.wad>   -> validate a PWAD file
 *     doomedit --selftest           -> one UI frame plus a build check
 *
 * The PWAD layout implements the same algorithm as tools/doom_pwad.py:
 * one sector per room and door block, segs mirroring the linedefs, one
 * subsector, one root node, one shared-list blockmap. Both sides stay
 * in sync through the byte pin in tests/test_doom_pwad.py.
 *
 * Grid legend beyond walls/floor/things: '+' door cell (own tagged
 * sector, D1 open-door lines both sides), ',' dark floor (low light),
 * '~' nukage pit (low floor, damaging slime flat).
 *
 * Levels travel in the same one-char-per-tile grid text the editor saves
 * to /saves/dmapN.txt, so a level weighs a few hundred bytes. The seven
 * bundled levels below are compiled in as string rows in exactly that
 * format; the Random button grows rooms-plus-corridors maps in the same
 * format procedurally.
 *
 * The thing palette only carries ids whose sprites ship in the bundled
 * shareware Doom1.wad (checked against the engine's mobjinfo table and
 * the IWAD lump list): cacodemon, lost soul, plasma rifle, BFG, berserk,
 * invulnerability and the megasphere have no sprites there, so spawning
 * them faults the renderer the moment they become visible. Doom has no
 * quad damage; invisibility is the closest surviving powerup.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "minios_abi.h"

#include "nuklear.h"
#include "nuklear_minios.h"
#include "nuklear_theme.h"

/** Central configuration: every bound, path, id and label in one place.
 * The window is 800x360, so the canvas column (32 tiles at 14 px) plus
 * the side panel must fit beside the toolbar and status rows without
 * scrolling: 22 + 16 + max(canvas, panel) stays under 360. */
#define DMAP_MAX_W 32
#define DMAP_MAX_H 20
#define DMAP_DEF_W 20
#define DMAP_DEF_H 12
#define DMAP_TILE 128
#define DMAP_CELL_PX 14
#define DMAP_CANVAS_W (DMAP_MAX_W * DMAP_CELL_PX + 8)
#define DMAP_PANEL_MIN_H 230
#define DMAP_PREV_W 240
#define DMAP_PREV_H 120
#define DMAP_UI_MEMORY (2 * 1024 * 1024)
#define DMAP_WAD_MAX (512 * 1024)
#define DMAP_FNAME_MAX 64
#define DMAP_STATUS_MAX 160
#define DMAP_SLOTS 4
#define DMAP_LEVEL_COUNT 9
#define DMAP_RANDOM_ATTEMPTS 64
#define DMAP_MAX_SECTORS 256
#define DMAP_ROOM_MAX 8
#define DMAP_ROOM_TRIES 40
#define DMAP_FRAME_MS 8
#define DMAP_TURN_STEP 0.26f
#define DMAP_MOVE_STEP 0.5f
#define DMAP_FOV_PLANE 0.73f
#define DMAP_MAX_LINES 2048
#define DMAP_MAX_VERTS 4096
#define DMAP_MAX_THINGS 256
#define DMAP_PLAYER_TYPE 1
#define DMAP_THING_OPT 7
#define DMAP_EXIT_SPECIAL 11
#define DMAP_DOOR_SPECIAL 31
#define DMAP_FLAG_BLOCKING 1
#define DMAP_FLAG_TWOSIDED 4
#define DMAP_NO_SIDE (-1)
#define DMAP_WALL_MID "STARTAN3"
#define DMAP_EXIT_MID "SW1EXIT"
#define DMAP_DOOR_UPPER "DOORTRAK"
#define DMAP_DARK_MID "BROWN1"
#define DMAP_NUKE_MID "STONE2"
#define DMAP_UNUSED_TEX "-"
#define DMAP_FLOOR_FLAT "FLOOR4_8"
#define DMAP_NUKE_FLAT "NUKAGE1"
#define DMAP_CEIL_FLAT "CEIL3_5"
#define DMAP_FLOOR_H 0
#define DMAP_NUKE_FLOOR (-16)
#define DMAP_CEIL_H 128
#define DMAP_DOOR_CEIL 64
#define DMAP_LIGHT 160
#define DMAP_DARK_LIGHT 96
#define DMAP_DOOR_LIGHT 128
#define DMAP_NUKE_SPECIAL 7
#define DMAP_NODE_LEAF 0x8000u
#define DMAP_TOOL_DOOM "/doomgeneric.elf"
#define DMAP_SAVE_TXT "/saves/dmap%d.txt"
#define DMAP_SAVE_WAD "/saves/dmap%d.wad"
#define DMAP_TITLE "DoomEdit"
#define DMAP_HISTORY 16
#define DMAP_TOOL_PAINT 0
#define DMAP_TOOL_LINE 1
#define DMAP_TOOL_RECT 2
#define DMAP_TOOL_FILL 3

/** Brush kinds double as grid cell values on disk. Only things whose
 * sprites ship in the shareware IWAD get a letter; the rest would fault
 * the renderer once visible (see the file header). */
enum {
    DMAP_WALL = '#',
    DMAP_FLOOR = '.',
    DMAP_PLAYER = 'P',
    DMAP_EXIT = 'E',
    DMAP_IMP = 'i',
    DMAP_DEMON = 'd',
    DMAP_ZOMBIE = 'z',
    DMAP_SHOTGUY = 'g',
    DMAP_SPECTRE = 'v',
    DMAP_BARON = 'b',
    DMAP_BARREL = 'B',
    DMAP_SHOTGUN = 's',
    DMAP_CHAINGUN = 'h',
    DMAP_RLAUNCH = 'r',
    DMAP_CHAINSAW = 'w',
    DMAP_SHELLS = 'a',
    DMAP_CLIP = 'u',
    DMAP_BULBOX = 'o',
    DMAP_ROCKETS = 'k',
    DMAP_RBOX = 'x',
    DMAP_SBOX = 'T',
    DMAP_STIM = 'q',
    DMAP_MEDI = 'm',
    DMAP_SOUL = 'y',
    DMAP_HBONUS = 'n',
    DMAP_ABONUS = 'f',
    DMAP_GARMOR = 'G',
    DMAP_BARMOR = 'U',
    DMAP_KEYB = '1',
    DMAP_KEYR = '2',
    DMAP_KEYY = '3',
    DMAP_INVIS = 'V',
    DMAP_RSUIT = 'R',
    DMAP_CMAP = 'C',
    DMAP_LAMP = 'L',
    DMAP_PACK = 'D',
    DMAP_PILLAR = '0',
    DMAP_DOOR = '+',
    DMAP_DARK = ',',
    DMAP_NUKE = '~'
};

/** Thing type ids from the engine mobjinfo table, each with its sprite
 * verified present in the shareware IWAD. */
static int dmap_thing_type(int cell) {
    switch (cell) {
    case DMAP_PLAYER: return 1;
    case DMAP_IMP: return 3001;
    case DMAP_DEMON: return 3002;
    case DMAP_ZOMBIE: return 3004;
    case DMAP_SHOTGUY: return 9;
    case DMAP_SPECTRE: return 58;
    case DMAP_BARON: return 3003;
    case DMAP_BARREL: return 2035;
    case DMAP_SHOTGUN: return 2001;
    case DMAP_CHAINGUN: return 2002;
    case DMAP_RLAUNCH: return 2003;
    case DMAP_CHAINSAW: return 2005;
    case DMAP_SHELLS: return 2008;
    case DMAP_CLIP: return 2007;
    case DMAP_BULBOX: return 2048;
    case DMAP_ROCKETS: return 2010;
    case DMAP_RBOX: return 2046;
    case DMAP_SBOX: return 2049;
    case DMAP_STIM: return 2011;
    case DMAP_MEDI: return 2012;
    case DMAP_SOUL: return 2013;
    case DMAP_HBONUS: return 2014;
    case DMAP_ABONUS: return 2015;
    case DMAP_GARMOR: return 2018;
    case DMAP_BARMOR: return 2019;
    case DMAP_KEYB: return 5;
    case DMAP_KEYR: return 13;
    case DMAP_KEYY: return 6;
    case DMAP_INVIS: return 2024;
    case DMAP_RSUIT: return 2025;
    case DMAP_CMAP: return 2026;
    case DMAP_LAMP: return 2045;
    case DMAP_PACK: return 8;
    case DMAP_PILLAR: return 2028;
    default: return 0;
    }
}

/** Brush metadata for the palette combobox, kind plus display label. */
static const int dmap_brush_kinds[] = {
    '#', '.', 'P', 'E',
    'i', 'd', 'z', 'g', 'v', 'b', 'B',
    's', 'h', 'r', 'w',
    'a', 'u', 'o', 'k', 'x', 'T',
    'q', 'm', 'y', 'n', 'f', 'G', 'U',
    '1', '2', '3',
    'V', 'R', 'C', 'L', 'D', '0',
    '+', ',', '~'
};
static const char *dmap_brush_labels[] = {
    "Wall (#)", "Floor (.)", "Player (P)", "Exit (E)",
    "Imp (i)", "Demon (d)", "Zombie (z)", "Shotgun guy (g)",
    "Spectre (v)", "Baron (b)", "Barrel (B)",
    "Shotgun (s)", "Chaingun (h)", "Rocket launcher (r)", "Chainsaw (w)",
    "Shells (a)", "Clip (u)", "Bullet box (o)", "Rockets (k)",
    "Rocket box (x)", "Shell box (T)",
    "Stimpack (q)", "Medikit (m)", "Soulsphere (y)", "Health bonus (n)",
    "Armor bonus (f)", "Green armor (G)", "Blue armor (U)",
    "Blue key (1)", "Red key (2)", "Yellow key (3)",
    "Invisibility (V)", "Rad suit (R)", "Computer map (C)",
    "Light amp (L)", "Backpack (D)", "Pillar (0)",
    "Door (+)", "Dark floor (,)", "Nukage (~)"
};
#define DMAP_BRUSH_COUNT (sizeof(dmap_brush_kinds) / sizeof(dmap_brush_kinds[0]))
static int dmap_brush_sel = 0;

/** Editor state: grid, brush, player view, slot and status line. */
static char dmap_grid[DMAP_MAX_H][DMAP_MAX_W];
static int dmap_w = DMAP_DEF_W;
static int dmap_h = DMAP_DEF_H;
static int dmap_brush = DMAP_WALL;
static int dmap_slot = 0;
static float dmap_angle = 0.0f;
static float dmap_px = 2.5f;
static float dmap_py = 2.5f;
static char dmap_status[DMAP_STATUS_MAX];
static int dmap_quit = 0;
static int dmap_ctrl_held = 0;
static int dmap_run_requested = 0;
static int dmap_level_sel = 0;
static unsigned dmap_rng = 0x12345678u;
static char dmap_ui_memory[DMAP_UI_MEMORY];
static unsigned char dmap_wad[DMAP_WAD_MAX];
static int dmap_tool = DMAP_TOOL_PAINT;
static int dmap_anchor_active = 0;
static int dmap_anchor_r = 0;
static int dmap_anchor_c = 0;
static int dmap_show_grid = 1;
static int dmap_show_unreach = 0;
static int dmap_walkable(int cell);
static void dmap_recenter(void);
static int dmap_validate(char *msg, int max);
static int dmap_nsectors;

/** Undo/redo stacks: whole-grid snapshots, pushed once per gesture so a
 * line, rect or fill undoes atomically. Any new edit clears redo. */
static char dmap_undo_g[DMAP_HISTORY][DMAP_MAX_H][DMAP_MAX_W];
static int dmap_undo_w[DMAP_HISTORY];
static int dmap_undo_h[DMAP_HISTORY];
static int dmap_undo_top = 0;
static char dmap_redo_g[DMAP_HISTORY][DMAP_MAX_H][DMAP_MAX_W];
static int dmap_redo_w[DMAP_HISTORY];
static int dmap_redo_h[DMAP_HISTORY];
static int dmap_redo_top = 0;

static void dmap_push_history(void) {
    int i;
    if (dmap_undo_top >= DMAP_HISTORY) {
        for (i = 0; i < DMAP_HISTORY - 1; i++) {
            dmap_undo_w[i] = dmap_undo_w[i + 1];
            dmap_undo_h[i] = dmap_undo_h[i + 1];
            memcpy(dmap_undo_g[i], dmap_undo_g[i + 1], sizeof(dmap_undo_g[i]));
        }
        dmap_undo_top = DMAP_HISTORY - 1;
    }
    dmap_undo_w[dmap_undo_top] = dmap_w;
    dmap_undo_h[dmap_undo_top] = dmap_h;
    memcpy(dmap_undo_g[dmap_undo_top], dmap_grid, sizeof(dmap_grid));
    dmap_undo_top++;
    dmap_redo_top = 0;
}

static int dmap_undo(void) {
    if (dmap_undo_top <= 0)
        return -1;
    if (dmap_redo_top < DMAP_HISTORY) {
        dmap_redo_w[dmap_redo_top] = dmap_w;
        dmap_redo_h[dmap_redo_top] = dmap_h;
        memcpy(dmap_redo_g[dmap_redo_top], dmap_grid, sizeof(dmap_grid));
        dmap_redo_top++;
    }
    dmap_undo_top--;
    dmap_w = dmap_undo_w[dmap_undo_top];
    dmap_h = dmap_undo_h[dmap_undo_top];
    memcpy(dmap_grid, dmap_undo_g[dmap_undo_top], sizeof(dmap_grid));
    dmap_anchor_active = 0;
    dmap_recenter();
    return 0;
}

static int dmap_redo(void) {
    if (dmap_redo_top <= 0)
        return -1;
    if (dmap_undo_top < DMAP_HISTORY) {
        dmap_undo_w[dmap_undo_top] = dmap_w;
        dmap_undo_h[dmap_undo_top] = dmap_h;
        memcpy(dmap_undo_g[dmap_undo_top], dmap_grid, sizeof(dmap_grid));
        dmap_undo_top++;
    }
    dmap_redo_top--;
    dmap_w = dmap_redo_w[dmap_redo_top];
    dmap_h = dmap_redo_h[dmap_redo_top];
    memcpy(dmap_grid, dmap_redo_g[dmap_redo_top], sizeof(dmap_grid));
    dmap_anchor_active = 0;
    dmap_recenter();
    return 0;
}

/** Single-cell paint keeping the one-player / one-exit invariant. */
static void dmap_apply_cell(int r, int c, int brush) {
    int rr, cc;
    if (r < 0 || c < 0 || r >= dmap_h || c >= dmap_w)
        return;
    if (brush == DMAP_PLAYER || brush == DMAP_EXIT) {
        for (rr = 0; rr < dmap_h; rr++)
            for (cc = 0; cc < dmap_w; cc++)
                if (dmap_grid[rr][cc] == brush)
                    dmap_grid[rr][cc] = DMAP_FLOOR;
    }
    dmap_grid[r][c] = (char)brush;
    if (brush == DMAP_PLAYER) {
        dmap_px = (float)c + 0.5f;
        dmap_py = (float)r + 0.5f;
    }
}

/** 4-way flood fill of the connected region holding old_cell. */
static void dmap_flood_fill(int sr, int sc, int new_cell) {
    static int stack_r[DMAP_MAX_W * DMAP_MAX_H];
    static int stack_c[DMAP_MAX_W * DMAP_MAX_H];
    static const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int old_cell, top = 0, k;
    if (sr < 0 || sc < 0 || sr >= dmap_h || sc >= dmap_w)
        return;
    old_cell = dmap_grid[sr][sc];
    if (old_cell == new_cell)
        return;
    if (new_cell == DMAP_PLAYER || new_cell == DMAP_EXIT)
        return;
    if (old_cell == DMAP_PLAYER || old_cell == DMAP_EXIT)
        return;
    stack_r[top] = sr;
    stack_c[top] = sc;
    top++;
    dmap_grid[sr][sc] = (char)new_cell;
    while (top > 0) {
        int r, c;
        top--;
        r = stack_r[top];
        c = stack_c[top];
        for (k = 0; k < 4; k++) {
            int nr = r + dirs[k][0], nc = c + dirs[k][1];
            if (nr < 0 || nc < 0 || nr >= dmap_h || nc >= dmap_w)
                continue;
            if (dmap_grid[nr][nc] != old_cell)
                continue;
            dmap_grid[nr][nc] = (char)new_cell;
            stack_r[top] = nr;
            stack_c[top] = nc;
            top++;
        }
    }
    dmap_level_sel = 0;
}

/** Bresenham line of cells, clipped to the grid. */
static void dmap_draw_line(int r0, int c0, int r1, int c1, int cell) {
    int dr = r1 > r0 ? r1 - r0 : r0 - r1;
    int dc = c1 > c0 ? c1 - c0 : c0 - c1;
    int sr = r0 < r1 ? 1 : -1, sc = c0 < c1 ? 1 : -1;
    int err = (dr > dc ? dr : -dc) / 2, e2;
    if (cell == DMAP_PLAYER || cell == DMAP_EXIT)
        return;
    for (;;) {
        if (r0 >= 0 && r0 < dmap_h && c0 >= 0 && c0 < dmap_w) {
            if (dmap_grid[r0][c0] != DMAP_PLAYER && dmap_grid[r0][c0] != DMAP_EXIT)
                dmap_grid[r0][c0] = (char)cell;
        }
        if (r0 == r1 && c0 == c1)
            break;
        e2 = err;
        if (e2 > -dr) {
            err -= dc;
            r0 += sr;
        }
        if (e2 < dc) {
            err += dr;
            c0 += sc;
        }
    }
    dmap_level_sel = 0;
}

/** Hollow rectangle border between two corners, clipped to the grid. */
static void dmap_draw_rect(int r0, int c0, int r1, int c1, int cell) {
    int r, c, rt = r0 < r1 ? r0 : r1, rb = r0 < r1 ? r1 : r0;
    int cl = c0 < c1 ? c0 : c1, cr = c0 < c1 ? c1 : c0;
    if (cell == DMAP_PLAYER || cell == DMAP_EXIT)
        return;
    for (c = cl; c <= cr; c++) {
        if (rt >= 0 && rt < dmap_h && c >= 0 && c < dmap_w) {
            if (dmap_grid[rt][c] != DMAP_PLAYER && dmap_grid[rt][c] != DMAP_EXIT)
                dmap_grid[rt][c] = (char)cell;
        }
        if (rb >= 0 && rb < dmap_h && c >= 0 && c < dmap_w) {
            if (dmap_grid[rb][c] != DMAP_PLAYER && dmap_grid[rb][c] != DMAP_EXIT)
                dmap_grid[rb][c] = (char)cell;
        }
    }
    for (r = rt; r <= rb; r++) {
        if (r >= 0 && r < dmap_h && cl >= 0 && cl < dmap_w) {
            if (dmap_grid[r][cl] != DMAP_PLAYER && dmap_grid[r][cl] != DMAP_EXIT)
                dmap_grid[r][cl] = (char)cell;
        }
        if (r >= 0 && r < dmap_h && cr >= 0 && cr < dmap_w) {
            if (dmap_grid[r][cr] != DMAP_PLAYER && dmap_grid[r][cr] != DMAP_EXIT)
                dmap_grid[r][cr] = (char)cell;
        }
    }
    dmap_level_sel = 0;
}

/** BFS reachability from the player start; seen[] is 1 for reachable. */
static void dmap_reach_map(int seen[DMAP_MAX_H][DMAP_MAX_W]) {
    static const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    static int stack_r[DMAP_MAX_W * DMAP_MAX_H];
    static int stack_c[DMAP_MAX_W * DMAP_MAX_H];
    int r, c, top = 0, sr = -1, sc = -1, k;
    for (r = 0; r < dmap_h; r++)
        for (c = 0; c < dmap_w; c++)
            seen[r][c] = 0;
    for (r = 0; r < dmap_h; r++)
        for (c = 0; c < dmap_w; c++)
            if (dmap_grid[r][c] == DMAP_PLAYER) {
                sr = r;
                sc = c;
            }
    if (sr < 0)
        return;
    seen[sr][sc] = 1;
    stack_r[top] = sr;
    stack_c[top] = sc;
    top++;
    while (top > 0) {
        int cr, cc;
        top--;
        cr = stack_r[top];
        cc = stack_c[top];
        for (k = 0; k < 4; k++) {
            int nr = cr + dirs[k][0], nc = cc + dirs[k][1];
            if (nr < 0 || nc < 0 || nr >= dmap_h || nc >= dmap_w)
                continue;
            if (seen[nr][nc] || !dmap_walkable(dmap_grid[nr][nc]))
                continue;
            seen[nr][nc] = 1;
            stack_r[top] = nr;
            stack_c[top] = nc;
            top++;
        }
    }
}

/** Shortest walkable distance player -> exit in tiles, -1 when broken. */
static int dmap_path_len(void) {
    static const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    static int dist[DMAP_MAX_H][DMAP_MAX_W];
    static int qr[DMAP_MAX_W * DMAP_MAX_H];
    static int qc[DMAP_MAX_W * DMAP_MAX_H];
    int r, c, head = 0, tail = 0, k, sr = -1, sc = -1;
    for (r = 0; r < dmap_h; r++)
        for (c = 0; c < dmap_w; c++)
            dist[r][c] = -1;
    for (r = 0; r < dmap_h; r++)
        for (c = 0; c < dmap_w; c++)
            if (dmap_grid[r][c] == DMAP_PLAYER) {
                sr = r;
                sc = c;
            }
    if (sr < 0)
        return -1;
    dist[sr][sc] = 0;
    qr[tail] = sr;
    qc[tail] = sc;
    tail++;
    while (head < tail) {
        int cr = qr[head], cc = qc[head];
        head++;
        if (dmap_grid[cr][cc] == DMAP_EXIT)
            return dist[cr][cc];
        for (k = 0; k < 4; k++) {
            int nr = cr + dirs[k][0], nc = cc + dirs[k][1];
            if (nr < 0 || nc < 0 || nr >= dmap_h || nc >= dmap_w)
                continue;
            if (dist[nr][nc] >= 0 || !dmap_walkable(dmap_grid[nr][nc]))
                continue;
            dist[nr][nc] = dist[cr][cc] + 1;
            qr[tail] = nr;
            qc[tail] = nc;
            tail++;
        }
    }
    return -1;
}

/** Headless stats line for the panel: size, sectors, path, monsters. */
static void dmap_stats(char *out, int max) {
    int r, c, monsters = 0, floors = 0, things = 0, path;
    char msg[DMAP_STATUS_MAX];
    for (r = 0; r < dmap_h; r++)
        for (c = 0; c < dmap_w; c++) {
            int cell = dmap_grid[r][c];
            if (cell == DMAP_WALL)
                continue;
            floors++;
            if (dmap_thing_type(cell) > 0)
                things++;
            if (cell == DMAP_IMP || cell == DMAP_DEMON || cell == DMAP_ZOMBIE ||
                cell == DMAP_SHOTGUY || cell == DMAP_SPECTRE || cell == DMAP_BARON)
                monsters++;
        }
    path = dmap_path_len();
    if (dmap_validate(msg, sizeof(msg)) == 0)
        snprintf(out, (size_t)max, "%dx%d %d sect path %d mon %d things %d",
            dmap_w, dmap_h, dmap_nsectors, path, monsters, things);
    else
        snprintf(out, (size_t)max, "%dx%d floor %d path - mon %d: %s",
            dmap_w, dmap_h, floors, monsters, msg);
}

/** Forward: the validator lives below the level tables. */
static int dmap_validate(char *msg, int max);

/** Run a program through SYS_SPAWN, preserving the editor. */
static long dmap_spawn(const char *path, int argc, const char **argv) {
    long ret;
    register long r10 __asm__("r10") = (long)argv;
    __asm__ volatile("syscall" : "=a"(ret)
                     : "a"(MINIOS_SYS_SPAWN), "D"(path), "S"((long)0),
                       "d"((long)argc), "r"(r10)
                     : "rcx", "r11", "memory");
    return ret;
}

/** Release or reclaim the display around a spawned child. */
static long dmap_vga(int on) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret)
                     : "a"(MINIOS_SYS_VGA_MODE), "D"((long)on)
                     : "rcx", "r11", "memory");
    return ret;
}

/** True for solid cells; out of bounds counts as wall to stay closed. */
static int dmap_is_wall(int row, int col) {
    if (row < 0 || col < 0 || row >= dmap_h || col >= dmap_w)
        return 1;
    return dmap_grid[row][col] == DMAP_WALL;
}

/** True for cells the player can stand on: floor, markers and things. */
static int dmap_walkable(int cell) {
    return cell == DMAP_FLOOR || cell == DMAP_EXIT || cell == DMAP_DOOR ||
        cell == DMAP_DARK || cell == DMAP_NUKE || dmap_thing_type(cell) > 0;
}

/** Sector class of a walkable cell: doors stand alone, styles never merge. */
static int dmap_cell_class(int cell) {
    if (cell == DMAP_DOOR)
        return 1;
    if (cell == DMAP_DARK)
        return 2;
    if (cell == DMAP_NUKE)
        return 3;
    return 0;
}

/** Canvas ink per cell category, so the palette reads at a glance. */
static struct nk_color dmap_cell_color(int cell) {
    switch (cell) {
    case DMAP_WALL: return nk_rgb(150, 110, 70);
    case DMAP_PLAYER: return nk_rgb(90, 200, 90);
    case DMAP_EXIT: return nk_rgb(220, 80, 80);
    case DMAP_IMP:
    case DMAP_DEMON:
    case DMAP_ZOMBIE:
    case DMAP_SHOTGUY:
    case DMAP_SPECTRE:
    case DMAP_BARON:
    case DMAP_BARREL: return nk_rgb(200, 90, 50);
    case DMAP_SHOTGUN:
    case DMAP_CHAINGUN:
    case DMAP_RLAUNCH:
    case DMAP_CHAINSAW: return nk_rgb(90, 160, 220);
    case DMAP_SHELLS:
    case DMAP_CLIP:
    case DMAP_BULBOX:
    case DMAP_ROCKETS:
    case DMAP_RBOX:
    case DMAP_SBOX:
    case DMAP_PACK: return nk_rgb(220, 200, 90);
    case DMAP_STIM:
    case DMAP_MEDI:
    case DMAP_SOUL:
    case DMAP_HBONUS: return nk_rgb(90, 200, 120);
    case DMAP_ABONUS:
    case DMAP_GARMOR:
    case DMAP_BARMOR: return nk_rgb(90, 120, 220);
    case DMAP_INVIS:
    case DMAP_RSUIT:
    case DMAP_CMAP:
    case DMAP_LAMP: return nk_rgb(200, 90, 200);
    case DMAP_KEYB:
    case DMAP_KEYR:
    case DMAP_KEYY: return nk_rgb(240, 240, 240);
    case DMAP_DOOR: return nk_rgb(220, 140, 40);
    case DMAP_DARK: return nk_rgb(40, 40, 56);
    case DMAP_NUKE: return nk_rgb(60, 160, 60);
    default: return nk_rgb(64, 64, 64);
    }
}

/** Fill the grid with floor and a solid border. */
static void dmap_new(void) {
    int row, col;
    dmap_push_history();
    dmap_anchor_active = 0;
    for (row = 0; row < dmap_h; row++)
        for (col = 0; col < dmap_w; col++)
            dmap_grid[row][col] = DMAP_FLOOR;
    for (col = 0; col < dmap_w; col++) {
        dmap_grid[0][col] = DMAP_WALL;
        dmap_grid[dmap_h - 1][col] = DMAP_WALL;
    }
    for (row = 0; row < dmap_h; row++) {
        dmap_grid[row][0] = DMAP_WALL;
        dmap_grid[row][dmap_w - 1] = DMAP_WALL;
    }
    dmap_grid[1][1] = DMAP_PLAYER;
    dmap_grid[1][2] = DMAP_EXIT;
    dmap_px = 1.5f;
    dmap_py = 1.5f;
    dmap_angle = 0.0f;
    dmap_level_sel = 0;
}

/** Bundled levels in grid text, one char per tile, a few hundred bytes
 * each. Every level carries one player start, one exit marker next to a
 * wall, a closed wall perimeter and full player-to-exit reachability, so
 * the validator and the exporter accept each one unconditionally. */
static const char *dmap_level_names[DMAP_LEVEL_COUNT] = {
    "Hangar of Dawn",
    "Imp Gallery",
    "Demon Pit",
    "Crossfire Chapel",
    "Fortress of Lead",
    "Sunken Halls",
    "Baron's Court",
    "Gatehouse",
    "Nukage Mills"
};

static const char *dmap_levels[DMAP_LEVEL_COUNT][DMAP_MAX_H + 1] = {
    {
        "############",
        "#P.........#",
        "#..##..##..#",
        "#..##..##..#",
        "#....i.....#",
        "#.m....a..E#",
        "#....i.....#",
        "#..........#",
        "############",
        0
    },
    {
        "##############",
        "#P..i....i...#",
        "#.##.##.##.#.#",
        "#............#",
        "#.a..####..m.#",
        "#....####...E#",
        "#.i..........#",
        "#............#",
        "##############",
        0
    },
    {
        "############",
        "#P....d....#",
        "#.####.###.#",
        "#.#......#.#",
        "#.#..dd..#.#",
        "#.#..dd..#.#",
        "#.#......#.#",
        "#.####.###.#",
        "#.s..m..a.E#",
        "############",
        0
    },
    {
        "#############",
        "#P..i...s...#",
        "#.....m.....#",
        "#.#########.#",
        "#.....a.....#",
        "#.#########.#",
        "#.....i.....#",
        "#.d.......E.#",
        "#############",
        0
    },
    {
        "##############",
        "#P...#...m...#",
        "#.i..#.###.#.#",
        "#....#.#...#.#",
        "#.##...#.a.#.#",
        "#..#.###.#.#.#",
        "#.s..d...#.E.#",
        "#.##.###.#.#.#",
        "#..i...m...d.#",
        "##############",
        0
    },
    {
        "##########################",
        "#P......#........#.......#",
        "#.yy....#.uu.............#",
        "#................#.......#",
        "#..z....#...q....#..b.g..#",
        "#.......#........#.......#",
        "####.#######.########.####",
        "#.......#........#.......#",
        "#.o.....#.k......#.n.V...#",
        "#.......#................#",
        "#.w........h.....#E.r....#",
        "#.......#........#.......#",
        "#..f....#...G....#...U...#",
        "##########################",
        0
    },
    {
        "############################",
        "#P.......#........#........#",
        "#.s......#...........u.....#",
        "#........#..g.....#........#",
        "#.................#........#",
        "#....zz..#.....v..#.....a..#",
        "#........#........#........#",
        "#####.########.#######.#####",
        "#........#........#........#",
        "#.m..q...#.DB..B..#...R....#",
        "#........#...bb...#........#",
        "#.........###..####........#",
        "#.h......#E...........r....#",
        "#....T...#.G......#.....y..#",
        "#........#........#........#",
        "############################",
        0
    },
    {
        "######################",
        "#P.,,,.....####......#",
        "#..,,,,....+...i....E#",
        "#..,,,,....####..m...#",
        "#......,...#+....a...#",
        "#......,...#....##...#",
        "#..s...,...d.........#",
        "#......,...#####.....#",
        "######################",
        0
    },
    {
        "########################",
        "#P.....####............#",
        "#..i...+......,,,,,....#",
        "#......####...,,,,,...E#",
        "#..m...#~~~#..,,,,,....#",
        "#......#~~~+....a......#",
        "#..s...#~~~#..d........#",
        "#......#~~~#...........#",
        "########################",
        0
    }
};

/** Move the preview camera onto the player start tile. */
static void dmap_recenter(void) {
    int r, c;
    for (r = 0; r < dmap_h; r++)
        for (c = 0; c < dmap_w; c++)
            if (dmap_grid[r][c] == DMAP_PLAYER) {
                dmap_px = (float)c + 0.5f;
                dmap_py = (float)r + 0.5f;
            }
    dmap_angle = 0.0f;
}

/** Load a bundled level into the grid, fail closed on a bad index. */
static int dmap_load_preset(int idx) {
    int row;
    if (idx < 0 || idx >= DMAP_LEVEL_COUNT)
        return -1;
    dmap_push_history();
    dmap_anchor_active = 0;
    dmap_h = 0;
    while (dmap_levels[idx][dmap_h])
        dmap_h++;
    if (dmap_h < 3 || dmap_h > DMAP_MAX_H)
        return -1;
    dmap_w = (int)strlen(dmap_levels[idx][0]);
    if (dmap_w < 3 || dmap_w > DMAP_MAX_W)
        return -1;
    for (row = 0; row < dmap_h; row++) {
        int k;
        if ((int)strlen(dmap_levels[idx][row]) != dmap_w)
            return -1;
        for (k = 0; k < dmap_w; k++) {
            int ch = dmap_levels[idx][row][k];
            if (!dmap_walkable(ch) && ch != DMAP_WALL)
                return -1;
            dmap_grid[row][k] = (char)ch;
        }
    }
    dmap_anchor_active = 0;
    dmap_recenter();
    dmap_level_sel = idx + 1;
    snprintf(dmap_status, sizeof(dmap_status), "level: %s", dmap_level_names[idx]);
    return 0;
}

/** Xorshift32: the only RNG the editor needs, no libc state. */
static unsigned dmap_rand(void) {
    dmap_rng ^= dmap_rng << 13;
    dmap_rng ^= dmap_rng >> 17;
    dmap_rng ^= dmap_rng << 5;
    return dmap_rng;
}

/** One random interior floor cell, 0 when it is not floor. */
static int dmap_free_cell(int *r, int *c) {
    *r = 1 + (int)(dmap_rand() % (unsigned)(dmap_h - 2));
    *c = 1 + (int)(dmap_rand() % (unsigned)(dmap_w - 2));
    return dmap_grid[*r][*c] == DMAP_FLOOR;
}

/** Procedural map of connected rooms: several non-overlapping rect
 * rooms carved out of solid rock, joined in sequence by L corridors,
 * the player starting in the first room and the exit marker in the
 * last one, with the full thing palette scattered on floor cells.
 * Keeps the first layout the validator accepts; the fallback is the
 * plain room when no attempt passes. Each attempt then gains a wall
 * divider pierced by working doors, dark patches and one nukage pool,
 * so random maps are multi-sector like the bundled ones. */
static void dmap_random_map(unsigned seed) {
    char msg[DMAP_STATUS_MAX];
    int attempt;
    static const int pack[] = {DMAP_IMP, DMAP_IMP, DMAP_DEMON, DMAP_DEMON,
        DMAP_ZOMBIE, DMAP_SHOTGUY, DMAP_SPECTRE, DMAP_BARON, DMAP_BARREL,
        DMAP_SHOTGUN, DMAP_CHAINGUN, DMAP_RLAUNCH, DMAP_CHAINSAW,
        DMAP_SHELLS, DMAP_CLIP, DMAP_BULBOX, DMAP_ROCKETS, DMAP_RBOX,
        DMAP_SBOX, DMAP_STIM, DMAP_MEDI, DMAP_SOUL, DMAP_HBONUS,
        DMAP_ABONUS, DMAP_GARMOR, DMAP_INVIS, DMAP_RSUIT, DMAP_CMAP,
        DMAP_LAMP, DMAP_PACK, DMAP_PILLAR};
    static const int must[] = {DMAP_DEMON, DMAP_SHOTGUY, DMAP_SHOTGUN,
        DMAP_MEDI, DMAP_SHELLS};
    dmap_rng = seed ? seed : 0x9E3779B9u;
    dmap_push_history();
    dmap_anchor_active = 0;
    for (attempt = 0; attempt < DMAP_RANDOM_ATTEMPTS; attempt++) {
        int r, c, k, n, nrooms = 0, tries;
        static int rx[DMAP_ROOM_MAX], ry[DMAP_ROOM_MAX];
        static int rw[DMAP_ROOM_MAX], rh[DMAP_ROOM_MAX];
        static int cand_r[DMAP_MAX_W * DMAP_MAX_H];
        static int cand_c[DMAP_MAX_W * DMAP_MAX_H];
        int ncand = 0;
        dmap_w = 18 + (int)(dmap_rand() % 15);
        if (dmap_w > DMAP_MAX_W)
            dmap_w = DMAP_MAX_W;
        dmap_h = 12 + (int)(dmap_rand() % 9);
        if (dmap_h > DMAP_MAX_H)
            dmap_h = DMAP_MAX_H;
        for (r = 0; r < dmap_h; r++)
            for (c = 0; c < dmap_w; c++)
                dmap_grid[r][c] = DMAP_WALL;
        n = 4 + (int)(dmap_rand() % 3);
        for (; n > 0 && nrooms < DMAP_ROOM_MAX; n--) {
            int w = 4 + (int)(dmap_rand() % 6);
            int h = 3 + (int)(dmap_rand() % 5);
            int x = -1, y = -1, ok;
            if (w > dmap_w - 2 || h > dmap_h - 2)
                continue;
            for (tries = 0; tries < DMAP_ROOM_TRIES; tries++) {
                x = 1 + (int)(dmap_rand() % (unsigned)(dmap_w - w - 1));
                y = 1 + (int)(dmap_rand() % (unsigned)(dmap_h - h - 1));
                ok = 1;
                for (k = 0; k < nrooms; k++)
                    if (x - 1 < rx[k] + rw[k] + 1 && rx[k] - 1 < x + w + 1 &&
                        y - 1 < ry[k] + rh[k] + 1 && ry[k] - 1 < y + h + 1) {
                        ok = 0;
                        break;
                    }
                if (ok)
                    break;
            }
            if (!ok)
                continue;
            rx[nrooms] = x;
            ry[nrooms] = y;
            rw[nrooms] = w;
            rh[nrooms] = h;
            nrooms++;
            for (r = y; r < y + h; r++)
                for (c = x; c < x + w; c++)
                    dmap_grid[r][c] = DMAP_FLOOR;
        }
        if (nrooms < 3) {
            dmap_rng = dmap_rng * 1664525u + 1013904223u;
            continue;
        }
        for (k = 1; k < nrooms; k++) {
            int x0 = rx[k - 1] + rw[k - 1] / 2, y0 = ry[k - 1] + rh[k - 1] / 2;
            int x1 = rx[k] + rw[k] / 2, y1 = ry[k] + rh[k] / 2;
            int order = (int)(dmap_rand() & 1u);
            int x, y;
            if (order) {
                for (x = x0 < x1 ? x0 : x1; x <= (x0 < x1 ? x1 : x0); x++)
                    dmap_grid[y0][x] = DMAP_FLOOR;
                for (y = y0 < y1 ? y0 : y1; y <= (y0 < y1 ? y1 : y0); y++)
                    dmap_grid[y][x1] = DMAP_FLOOR;
            } else {
                for (y = y0 < y1 ? y0 : y1; y <= (y0 < y1 ? y1 : y0); y++)
                    dmap_grid[y][x0] = DMAP_FLOOR;
                for (x = x0 < x1 ? x0 : x1; x <= (x0 < x1 ? x1 : x0); x++)
                    dmap_grid[y1][x] = DMAP_FLOOR;
            }
        }
        if (nrooms >= 4 && (dmap_rand() & 1u)) {
            int x0 = rx[nrooms - 1] + rw[nrooms - 1] / 2, y0 = ry[nrooms - 1] + rh[nrooms - 1] / 2;
            int x1 = rx[0] + rw[0] / 2, y1 = ry[0] + rh[0] / 2;
            int x, y;
            for (x = x0 < x1 ? x0 : x1; x <= (x0 < x1 ? x1 : x0); x++)
                dmap_grid[y0][x] = DMAP_FLOOR;
            for (y = y0 < y1 ? y0 : y1; y <= (y0 < y1 ? y1 : y0); y++)
                dmap_grid[y][x1] = DMAP_FLOOR;
        }
        dmap_grid[ry[0] + rh[0] / 2][rx[0] + rw[0] / 2] = DMAP_PLAYER;
        for (r = ry[nrooms - 1]; r < ry[nrooms - 1] + rh[nrooms - 1]; r++)
            for (c = rx[nrooms - 1]; c < rx[nrooms - 1] + rw[nrooms - 1]; c++) {
                static const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
                int q, wall = 0;
                if (dmap_grid[r][c] != DMAP_FLOOR)
                    continue;
                for (q = 0; q < 4; q++)
                    if (dmap_grid[r + dirs[q][0]][c + dirs[q][1]] == DMAP_WALL)
                        wall = 1;
                if (wall && ncand < DMAP_MAX_W * DMAP_MAX_H) {
                    cand_r[ncand] = r;
                    cand_c[ncand] = c;
                    ncand++;
                }
            }
        if (ncand == 0) {
            dmap_rng = dmap_rng * 1664525u + 1013904223u;
            continue;
        }
        k = (int)(dmap_rand() % (unsigned)ncand);
        dmap_grid[cand_r[k]][cand_c[k]] = DMAP_EXIT;
        n = dmap_w * dmap_h / 12;
        for (; n > 0; n--) {
            if (!dmap_free_cell(&r, &c))
                continue;
            dmap_grid[r][c] = (char)pack[dmap_rand() %
                (sizeof(pack) / sizeof(pack[0]))];
        }
        for (n = 0; n < (int)(sizeof(must) / sizeof(must[0])); n++) {
            for (tries = 0; tries < 32; tries++)
                if (dmap_free_cell(&r, &c)) {
                    dmap_grid[r][c] = (char)must[n];
                    break;
                }
        }
        /* Split the map with a wall divider pierced by doors, then
         * stain dark patches and one nukage pool. Reachability survives
         * through the doors; blobs only replace plain floor. */
        {
            int vertical = (dmap_rand() & 1u) != 0, line, placed;
            if (vertical && dmap_w > 8) {
                line = 2 + (int)(dmap_rand() % (unsigned)(dmap_w - 4));
                for (r = 1; r < dmap_h - 1; r++) {
                    int ch = dmap_grid[r][line];
                    if (ch == DMAP_PLAYER || ch == DMAP_EXIT)
                        continue;
                    if (dmap_thing_type(ch) > 0)
                        continue;
                    dmap_grid[r][line] = DMAP_WALL;
                }
                placed = 0;
                for (tries = 0; tries < 16 && placed < 2; tries++) {
                    r = 1 + (int)(dmap_rand() % (unsigned)(dmap_h - 2));
                    if (dmap_grid[r][line] == DMAP_WALL) {
                        dmap_grid[r][line] = DMAP_DOOR;
                        placed++;
                    }
                }
            } else if (!vertical && dmap_h > 8) {
                line = 2 + (int)(dmap_rand() % (unsigned)(dmap_h - 4));
                for (c = 1; c < dmap_w - 1; c++) {
                    int ch = dmap_grid[line][c];
                    if (ch == DMAP_PLAYER || ch == DMAP_EXIT)
                        continue;
                    if (dmap_thing_type(ch) > 0)
                        continue;
                    dmap_grid[line][c] = DMAP_WALL;
                }
                placed = 0;
                for (tries = 0; tries < 16 && placed < 2; tries++) {
                    c = 1 + (int)(dmap_rand() % (unsigned)(dmap_w - 2));
                    if (dmap_grid[line][c] == DMAP_WALL) {
                        dmap_grid[line][c] = DMAP_DOOR;
                        placed++;
                    }
                }
            }
            for (n = 0; n < 3; n++) {
                int br, bc, q;
                if (!dmap_free_cell(&br, &bc))
                    continue;
                dmap_grid[br][bc] = DMAP_DARK;
                for (q = 0; q < 4; q++) {
                    int qr = br + (int)(dmap_rand() % 3) - 1;
                    int qc = bc + (int)(dmap_rand() % 3) - 1;
                    if (qr > 0 && qc > 0 && qr < dmap_h - 1 && qc < dmap_w - 1 &&
                        dmap_grid[qr][qc] == DMAP_FLOOR)
                        dmap_grid[qr][qc] = DMAP_DARK;
                }
            }
            if (dmap_free_cell(&r, &c) && r + 1 < dmap_h - 1 && c + 1 < dmap_w - 1 &&
                dmap_grid[r][c + 1] == DMAP_FLOOR &&
                dmap_grid[r + 1][c] == DMAP_FLOOR &&
                dmap_grid[r + 1][c + 1] == DMAP_FLOOR) {
                dmap_grid[r][c] = DMAP_NUKE;
                dmap_grid[r][c + 1] = DMAP_NUKE;
                dmap_grid[r + 1][c] = DMAP_NUKE;
                dmap_grid[r + 1][c + 1] = DMAP_NUKE;
            }
        }
        if (dmap_validate(msg, sizeof(msg)) == 0) {
            dmap_recenter();
            snprintf(dmap_status, sizeof(dmap_status), "random %dx%d %d rooms ok",
                dmap_w, dmap_h, nrooms);
            return;
        }
        dmap_rng = dmap_rng * 1664525u + 1013904223u;
    }
    dmap_new();
    snprintf(dmap_status, sizeof(dmap_status), "random fell back to plain room");
}

/** Load a grid text file, refusing ragged or illegal content. */
static int dmap_load(const char *path) {
    static char tmp[DMAP_MAX_H][DMAP_MAX_W];
    FILE *fp = fopen(path, "r");
    int row = 0, col = 0, ch, w = 0, r, c;
    if (!fp)
        return -1;
    while ((ch = fgetc(fp)) != EOF && row < DMAP_MAX_H) {
        if (ch == '\n') {
            if (col == 0)
                continue;
            if (row == 0)
                w = col;
            if (col != w) {
                fclose(fp);
                return -1;
            }
            row++;
            col = 0;
            continue;
        }
        if (!dmap_walkable(ch) && ch != DMAP_WALL) {
            fclose(fp);
            return -1;
        }
        if (col >= DMAP_MAX_W) {
            fclose(fp);
            return -1;
        }
        tmp[row][col++] = (char)ch;
    }
    fclose(fp);
    if (col != 0) {
        if (row == 0)
            w = col;
        if (col != w)
            return -1;
        row++;
    }
    if (row < 3 || w < 3 || w > DMAP_MAX_W)
        return -1;
    dmap_push_history();
    dmap_anchor_active = 0;
    dmap_w = w;
    dmap_h = row;
    for (r = 0; r < dmap_h; r++)
        for (c = 0; c < dmap_w; c++)
            dmap_grid[r][c] = tmp[r][c];
    dmap_recenter();
    return 0;
}

/** Store the grid as text for later editing sessions. */
static int dmap_save_txt(const char *path) {
    FILE *fp = fopen(path, "w");
    int row, col;
    if (!fp)
        return -1;
    for (row = 0; row < dmap_h; row++) {
        for (col = 0; col < dmap_w; col++)
            if (fputc(dmap_grid[row][col], fp) == EOF) {
                fclose(fp);
                return -1;
            }
        if (fputc('\n', fp) == EOF) {
            fclose(fp);
            return -1;
        }
    }
    fclose(fp);
    return 0;
}

/** Sector table backing the multi-sector exporter. Regions are same-class
 * floor areas (doors stand alone, dark and nukage never merge); every
 * region becomes one sector, so light, heights and flats vary per room
 * while the BSP stays one trivial subsector. */
static int dmap_sect[DMAP_MAX_H][DMAP_MAX_W];
static int dmap_sec_floor[DMAP_MAX_SECTORS];
static int dmap_sec_ceil[DMAP_MAX_SECTORS];
static int dmap_sec_light[DMAP_MAX_SECTORS];
static int dmap_sec_special[DMAP_MAX_SECTORS];
static int dmap_sec_tag[DMAP_MAX_SECTORS];
static const char *dmap_sec_flat[DMAP_MAX_SECTORS];
static const char *dmap_sec_skin[DMAP_MAX_SECTORS];

/** Flood same-class walkable cells into sector ids; walls stay -1. */
static int dmap_label_regions(void) {
    static const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    static int stack_r[DMAP_MAX_W * DMAP_MAX_H];
    static int stack_c[DMAP_MAX_W * DMAP_MAX_H];
    int row, col, nsec = 0, ndoor = 0;
    for (row = 0; row < dmap_h; row++)
        for (col = 0; col < dmap_w; col++)
            dmap_sect[row][col] = -1;
    for (row = 0; row < dmap_h; row++)
        for (col = 0; col < dmap_w; col++) {
            int want, top, k;
            if (dmap_grid[row][col] == DMAP_WALL || dmap_sect[row][col] >= 0)
                continue;
            if (nsec >= DMAP_MAX_SECTORS)
                return -1;
            want = dmap_cell_class(dmap_grid[row][col]);
            top = 0;
            dmap_sect[row][col] = nsec;
            stack_r[top] = row;
            stack_c[top] = col;
            top++;
            while (top > 0) {
                int r, c;
                top--;
                r = stack_r[top];
                c = stack_c[top];
                for (k = 0; k < 4; k++) {
                    int nr = r + dirs[k][0], nc = c + dirs[k][1];
                    if (nr < 0 || nc < 0 || nr >= dmap_h || nc >= dmap_w)
                        continue;
                    if (dmap_sect[nr][nc] >= 0 ||
                        dmap_grid[nr][nc] == DMAP_WALL ||
                        dmap_cell_class(dmap_grid[nr][nc]) != want)
                        continue;
                    dmap_sect[nr][nc] = nsec;
                    stack_r[top] = nr;
                    stack_c[top] = nc;
                    top++;
                }
            }
            if (want == 1) {
                ndoor++;
                dmap_sec_tag[nsec] = ndoor;
                dmap_sec_floor[nsec] = DMAP_FLOOR_H;
                dmap_sec_ceil[nsec] = DMAP_DOOR_CEIL;
                dmap_sec_flat[nsec] = DMAP_FLOOR_FLAT;
                dmap_sec_light[nsec] = DMAP_DOOR_LIGHT;
                dmap_sec_special[nsec] = 0;
                dmap_sec_skin[nsec] = DMAP_DOOR_UPPER;
            } else if (want == 2) {
                dmap_sec_tag[nsec] = 0;
                dmap_sec_floor[nsec] = DMAP_FLOOR_H;
                dmap_sec_ceil[nsec] = DMAP_CEIL_H;
                dmap_sec_flat[nsec] = DMAP_FLOOR_FLAT;
                dmap_sec_light[nsec] = DMAP_DARK_LIGHT;
                dmap_sec_special[nsec] = 0;
                dmap_sec_skin[nsec] = DMAP_DARK_MID;
            } else if (want == 3) {
                dmap_sec_tag[nsec] = 0;
                dmap_sec_floor[nsec] = DMAP_NUKE_FLOOR;
                dmap_sec_ceil[nsec] = DMAP_CEIL_H;
                dmap_sec_flat[nsec] = DMAP_NUKE_FLAT;
                dmap_sec_light[nsec] = DMAP_DARK_LIGHT;
                dmap_sec_special[nsec] = DMAP_NUKE_SPECIAL;
                dmap_sec_skin[nsec] = DMAP_NUKE_MID;
            } else {
                dmap_sec_tag[nsec] = 0;
                dmap_sec_floor[nsec] = DMAP_FLOOR_H;
                dmap_sec_ceil[nsec] = DMAP_CEIL_H;
                dmap_sec_flat[nsec] = DMAP_FLOOR_FLAT;
                dmap_sec_light[nsec] = DMAP_LIGHT;
                dmap_sec_special[nsec] = 0;
                dmap_sec_skin[nsec] = DMAP_WALL_MID;
            }
            nsec++;
        }
    dmap_nsectors = nsec;
    return 0;
}

/** Validate the map, reporting the first problem for the status line. */
static int dmap_validate(char *msg, int max) {
    int row, col, players = 0, exits = 0;
    int seen[DMAP_MAX_H][DMAP_MAX_W];
    int stack_r[DMAP_MAX_W * DMAP_MAX_H];
    int stack_c[DMAP_MAX_W * DMAP_MAX_H];
    int top = 0, sr = -1, sc = -1, er = -1, ec = -1;
    static const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int k;
    for (row = 0; row < dmap_h; row++)
        for (col = 0; col < dmap_w; col++) {
            seen[row][col] = 0;
            if (dmap_grid[row][col] == DMAP_PLAYER) {
                players++;
                sr = row;
                sc = col;
            }
            if (dmap_grid[row][col] == DMAP_EXIT) {
                exits++;
                er = row;
                ec = col;
            }
        }
    if (players != 1) {
        snprintf(msg, (size_t)max, "need exactly one player start");
        return -1;
    }
    if (exits != 1) {
        snprintf(msg, (size_t)max, "need exactly one exit marker");
        return -1;
    }
    seen[sr][sc] = 1;
    stack_r[top] = sr;
    stack_c[top] = sc;
    top++;
    while (top > 0) {
        int r, c;
        top--;
        r = stack_r[top];
        c = stack_c[top];
        for (k = 0; k < 4; k++) {
            int nr = r + dirs[k][0], nc = c + dirs[k][1];
            if (nr < 0 || nc < 0 || nr >= dmap_h || nc >= dmap_w)
                continue;
            if (seen[nr][nc] || !dmap_walkable(dmap_grid[nr][nc]))
                continue;
            seen[nr][nc] = 1;
            stack_r[top] = nr;
            stack_c[top] = nc;
            top++;
        }
    }
    for (row = 0; row < dmap_h; row++)
        for (col = 0; col < dmap_w; col++)
            if (dmap_walkable(dmap_grid[row][col]) && !seen[row][col]) {
                snprintf(msg, (size_t)max, "unreachable tile %d,%d", row, col);
                return -1;
            }
    for (k = 0; k < 4; k++)
        if (dmap_is_wall(er + dirs[k][0], ec + dirs[k][1])) {
            if (dmap_label_regions() != 0) {
                snprintf(msg, (size_t)max, "too many sectors");
                return -1;
            }
            snprintf(msg, (size_t)max, "ok: %dx%d %d sectors",
                dmap_w, dmap_h, dmap_nsectors);
            return 0;
        }
    snprintf(msg, (size_t)max, "exit marker is not next to a wall");
    return -1;
}

/** Little-endian emit helpers over the shared WAD buffer. */
static unsigned char *dmap_wp;
static void dmap_w8(unsigned v) { *dmap_wp++ = (unsigned char)(v & 0xFFu); }
static void dmap_w16(int v) {
    *dmap_wp++ = (unsigned char)(v & 0xFF);
    *dmap_wp++ = (unsigned char)((v >> 8) & 0xFF);
}
static void dmap_w32(int v) {
    dmap_w16(v & 0xFFFF);
    dmap_w16((v >> 16) & 0xFFFF);
}
static void dmap_wtex(const char *name) {
    int k;
    for (k = 0; k < 8; k++)
        dmap_w8(name[k] ? (unsigned)name[k] : 0u);
}

/** Stored short angle for a seg direction, matching the engine loader. */
static int dmap_seg_angle(int dx, int dy) {
    double full = atan2((double)dy, (double)dx) / (2.0 * 3.141592653589793) * 4294967296.0;
    unsigned u = (unsigned)(full < 0.0 ? full + 4294967296.0 : full);
    int s = (int)((u >> 16) & 0xFFFFu);
    return s >= 0x8000 ? s - 0x10000 : s;
}

/** Compile the grid into a vanilla multi-sector E1M1 PWAD image. Every
 * region and door block is its own sector; all segs share one subsector
 * under a trivial root node, which needs no ordering. */
static int dmap_build_wad(int *size_out) {
    static int vx[DMAP_MAX_VERTS * 2];
    static int li_v[DMAP_MAX_LINES * 2];
    static int li_exit[DMAP_MAX_LINES];
    static int li_flags[DMAP_MAX_LINES];
    static int li_special[DMAP_MAX_LINES];
    static int li_tag[DMAP_MAX_LINES];
    static int li_s0[DMAP_MAX_LINES];
    static int li_s1[DMAP_MAX_LINES];
    static const char *sd_upper[DMAP_MAX_LINES * 2];
    static const char *sd_lower[DMAP_MAX_LINES * 2];
    static const char *sd_mid[DMAP_MAX_LINES * 2];
    static int sd_sec[DMAP_MAX_LINES * 2];
    static int em_a[DMAP_MAX_LINES];
    static int em_b[DMAP_MAX_LINES];
    static int th_x[DMAP_MAX_THINGS];
    static int th_y[DMAP_MAX_THINGS];
    static int th_t[DMAP_MAX_THINGS];
    int nv = 0, nl = 0, nt = 0, nsides = 0, nem = 0;
    int row, col, k, exit_edge = -1;
    int er = -1, ec = -1, edir = -1;
    static const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int minx, maxx, miny, maxy, bw, bh, list_off, n;
    int lump_pos[11], lump_size[11];
    static const char *names[11] = {"E1M1", "THINGS", "LINEDEFS", "SIDEDEFS",
        "VERTEXES", "SEGS", "SSECTORS", "NODES", "SECTORS", "REJECT", "BLOCKMAP"};
    unsigned char *base;
    if (dmap_validate(dmap_status, sizeof(dmap_status)) != 0)
        return -1;
    for (row = 0; row < dmap_h; row++)
        for (col = 0; col < dmap_w; col++) {
            if (dmap_grid[row][col] == DMAP_EXIT) {
                er = row;
                ec = col;
            }
            if (dmap_thing_type(dmap_grid[row][col]) > 0 && nt < DMAP_MAX_THINGS) {
                th_x[nt] = col * DMAP_TILE + DMAP_TILE / 2;
                th_y[nt] = -row * DMAP_TILE - DMAP_TILE / 2;
                th_t[nt] = dmap_thing_type(dmap_grid[row][col]);
                nt++;
            }
        }
    for (k = 0; k < 4; k++)
        if (dmap_is_wall(er + dirs[k][0], ec + dirs[k][1])) {
            edir = k;
            break;
        }
    for (row = 0; row < dmap_h; row++)
        for (col = 0; col < dmap_w; col++) {
            int x0, x1, yt, yb, e, here;
            int ex[4][2][2], ed[4];
            if (!dmap_walkable(dmap_grid[row][col]))
                continue;
            here = dmap_sect[row][col];
            x0 = col * DMAP_TILE;
            x1 = (col + 1) * DMAP_TILE;
            yt = -row * DMAP_TILE;
            yb = -(row + 1) * DMAP_TILE;
            ex[0][0][0] = x0; ex[0][0][1] = yt; ex[0][1][0] = x1; ex[0][1][1] = yt;
            ex[1][0][0] = x1; ex[1][0][1] = yb; ex[1][1][0] = x0; ex[1][1][1] = yb;
            ex[2][0][0] = x0; ex[2][0][1] = yb; ex[2][1][0] = x0; ex[2][1][1] = yt;
            ex[3][0][0] = x1; ex[3][0][1] = yt; ex[3][1][0] = x1; ex[3][1][1] = yb;
            ed[0] = 0; ed[1] = 2; ed[2] = 3; ed[3] = 1;
            for (e = 0; e < 4; e++) {
                int nr = row + dirs[ed[e]][0], nc = col + dirs[ed[e]][1];
                int v1 = -1, v2 = -1, q, back = -2, ka, kb, kk;
                if (nr < 0 || nc < 0 || nr >= dmap_h || nc >= dmap_w ||
                    dmap_grid[nr][nc] == DMAP_WALL)
                    back = -1;
                else if (dmap_sect[nr][nc] == here)
                    continue;
                else
                    back = dmap_sect[nr][nc];
                ka = row * DMAP_MAX_W + col;
                kb = nr * DMAP_MAX_W + nc;
                if (back >= 0 && ka > kb) {
                    kk = ka;
                    ka = kb;
                    kb = kk;
                }
                if (back >= 0) {
                    for (q = 0; q < nem; q++)
                        if (em_a[q] == ka && em_b[q] == kb)
                            break;
                    if (q < nem)
                        continue;
                    if (nem >= DMAP_MAX_LINES)
                        return -1;
                    em_a[nem] = ka;
                    em_b[nem] = kb;
                    nem++;
                }
                for (q = 0; q < nv; q++)
                    if (vx[q * 2] == ex[e][0][0] && vx[q * 2 + 1] == ex[e][0][1])
                        v1 = q;
                if (v1 < 0 && nv < DMAP_MAX_VERTS) {
                    v1 = nv++;
                    vx[v1 * 2] = ex[e][0][0];
                    vx[v1 * 2 + 1] = ex[e][0][1];
                }
                for (q = 0; q < nv; q++)
                    if (vx[q * 2] == ex[e][1][0] && vx[q * 2 + 1] == ex[e][1][1])
                        v2 = q;
                if (v2 < 0 && nv < DMAP_MAX_VERTS) {
                    v2 = nv++;
                    vx[v2 * 2] = ex[e][1][0];
                    vx[v2 * 2 + 1] = ex[e][1][1];
                }
                if (v1 < 0 || v2 < 0 || nl >= DMAP_MAX_LINES ||
                    nsides + 2 >= DMAP_MAX_LINES * 2)
                    return -1;
                if (row == er && col == ec && ed[e] == edir && back < 0)
                    exit_edge = nl;
                li_v[nl * 2] = v1;
                li_v[nl * 2 + 1] = v2;
                li_exit[nl] = (nl == exit_edge);
                if (back < 0) {
                    li_flags[nl] = DMAP_FLAG_BLOCKING;
                    li_special[nl] = 0;
                    li_tag[nl] = 0;
                    li_s0[nl] = nsides;
                    li_s1[nl] = DMAP_NO_SIDE;
                    sd_upper[nsides] = DMAP_UNUSED_TEX;
                    sd_lower[nsides] = DMAP_UNUSED_TEX;
                    sd_mid[nsides] = dmap_sec_skin[here];
                    sd_sec[nsides] = here;
                    nsides++;
                } else {
                    int verspre = dmap_sec_tag[here] != 0 ||
                        dmap_sec_tag[back] != 0;
                    li_flags[nl] = DMAP_FLAG_TWOSIDED;
                    li_special[nl] = verspre ? DMAP_DOOR_SPECIAL : 0;
                    li_tag[nl] = verspre ?
                        (dmap_sec_tag[here] != 0 ? dmap_sec_tag[here] :
                            dmap_sec_tag[back]) : 0;
                    li_s0[nl] = nsides;
                    li_s1[nl] = nsides + 1;
                    if (verspre) {
                        sd_upper[nsides] = DMAP_DOOR_UPPER;
                        sd_lower[nsides] = DMAP_UNUSED_TEX;
                        sd_mid[nsides] = DMAP_UNUSED_TEX;
                        sd_sec[nsides] = here;
                        sd_upper[nsides + 1] = DMAP_DOOR_UPPER;
                        sd_lower[nsides + 1] = DMAP_UNUSED_TEX;
                        sd_mid[nsides + 1] = DMAP_UNUSED_TEX;
                        sd_sec[nsides + 1] = back;
                    } else if (dmap_sec_floor[here] == dmap_sec_floor[back]) {
                        sd_upper[nsides] = DMAP_UNUSED_TEX;
                        sd_lower[nsides] = DMAP_UNUSED_TEX;
                        sd_mid[nsides] = DMAP_UNUSED_TEX;
                        sd_sec[nsides] = here;
                        sd_upper[nsides + 1] = DMAP_UNUSED_TEX;
                        sd_lower[nsides + 1] = DMAP_UNUSED_TEX;
                        sd_mid[nsides + 1] = DMAP_UNUSED_TEX;
                        sd_sec[nsides + 1] = back;
                    } else {
                        sd_upper[nsides] = DMAP_UNUSED_TEX;
                        sd_lower[nsides] = dmap_sec_skin[here];
                        sd_mid[nsides] = DMAP_UNUSED_TEX;
                        sd_sec[nsides] = here;
                        sd_upper[nsides + 1] = DMAP_UNUSED_TEX;
                        sd_lower[nsides + 1] = dmap_sec_skin[back];
                        sd_mid[nsides + 1] = DMAP_UNUSED_TEX;
                        sd_sec[nsides + 1] = back;
                    }
                    nsides += 2;
                }
                nl++;
            }
        }
    if (exit_edge < 0 || nl < 1)
        return -1;
    minx = 0;
    maxx = dmap_w * DMAP_TILE;
    miny = -dmap_h * DMAP_TILE;
    maxy = 0;
    bw = (maxx - minx) / DMAP_TILE + 1;
    bh = (maxy - miny) / DMAP_TILE + 1;
    list_off = 4 + bw * bh;
    dmap_wp = dmap_wad + 12;
    base = dmap_wad;
    lump_pos[0] = 12;
    lump_size[0] = 0;
    lump_pos[1] = (int)(dmap_wp - base);
    for (k = 0; k < nt; k++) {
        dmap_w16(th_x[k]);
        dmap_w16(th_y[k]);
        dmap_w16(0);
        dmap_w16(th_t[k]);
        dmap_w16(DMAP_THING_OPT);
    }
    lump_size[1] = (int)(dmap_wp - base) - lump_pos[1];
    lump_pos[2] = (int)(dmap_wp - base);
    for (k = 0; k < nl; k++) {
        dmap_w16(li_v[k * 2]);
        dmap_w16(li_v[k * 2 + 1]);
        dmap_w16(li_flags[k]);
        dmap_w16(li_exit[k] ? DMAP_EXIT_SPECIAL : li_special[k]);
        dmap_w16(li_tag[k]);
        dmap_w16(li_s0[k]);
        dmap_w16(li_s1[k]);
    }
    lump_size[2] = (int)(dmap_wp - base) - lump_pos[2];
    lump_pos[3] = (int)(dmap_wp - base);
    for (k = 0; k < nsides; k++) {
        dmap_w16(0);
        dmap_w16(0);
        dmap_wtex(sd_upper[k]);
        dmap_wtex(sd_lower[k]);
        dmap_wtex(sd_mid[k]);
        dmap_w16(sd_sec[k]);
    }
    if (exit_edge >= 0) {
        unsigned char *side = base + lump_pos[3] + li_s0[exit_edge] * 30 + 20;
        const char *mid = DMAP_EXIT_MID;
        int q;
        for (q = 0; q < 8; q++)
            side[q] = mid[q] ? (unsigned char)mid[q] : 0u;
    }
    lump_size[3] = (int)(dmap_wp - base) - lump_pos[3];
    lump_pos[4] = (int)(dmap_wp - base);
    for (k = 0; k < nv; k++) {
        dmap_w16(vx[k * 2]);
        dmap_w16(vx[k * 2 + 1]);
    }
    lump_size[4] = (int)(dmap_wp - base) - lump_pos[4];
    lump_pos[5] = (int)(dmap_wp - base);
    for (k = 0; k < nl; k++) {
        int dx = vx[li_v[k * 2 + 1] * 2] - vx[li_v[k * 2] * 2];
        int dy = vx[li_v[k * 2 + 1] * 2 + 1] - vx[li_v[k * 2] * 2 + 1];
        dmap_w16(li_v[k * 2]);
        dmap_w16(li_v[k * 2 + 1]);
        dmap_w16(dmap_seg_angle(dx, dy));
        dmap_w16(k);
        dmap_w16(0);
        dmap_w16(0);
    }
    lump_size[5] = (int)(dmap_wp - base) - lump_pos[5];
    lump_pos[6] = (int)(dmap_wp - base);
    dmap_w16(nl);
    dmap_w16(0);
    lump_size[6] = (int)(dmap_wp - base) - lump_pos[6];
    lump_pos[7] = (int)(dmap_wp - base);
    dmap_w16(vx[li_v[0] * 2]);
    dmap_w16(vx[li_v[0] * 2 + 1]);
    dmap_w16(vx[li_v[1] * 2] - vx[li_v[0] * 2]);
    dmap_w16(vx[li_v[1] * 2 + 1] - vx[li_v[0] * 2 + 1]);
    dmap_w16(maxy);
    dmap_w16(miny);
    dmap_w16(minx);
    dmap_w16(maxx);
    dmap_w16(maxy);
    dmap_w16(miny);
    dmap_w16(minx);
    dmap_w16(maxx);
    dmap_w16((int)DMAP_NODE_LEAF);
    dmap_w16((int)DMAP_NODE_LEAF);
    lump_size[7] = (int)(dmap_wp - base) - lump_pos[7];
    lump_pos[8] = (int)(dmap_wp - base);
    for (k = 0; k < dmap_nsectors; k++) {
        dmap_w16(dmap_sec_floor[k]);
        dmap_w16(dmap_sec_ceil[k]);
        dmap_wtex(dmap_sec_flat[k]);
        dmap_wtex(DMAP_CEIL_FLAT);
        dmap_w16(dmap_sec_light[k]);
        dmap_w16(dmap_sec_special[k]);
        dmap_w16(dmap_sec_tag[k]);
    }
    lump_size[8] = (int)(dmap_wp - base) - lump_pos[8];
    lump_pos[9] = (int)(dmap_wp - base);
    {
        int rj = (dmap_nsectors * dmap_nsectors + 7) / 8;
        for (k = 0; k < rj; k++)
            dmap_w8(0);
    }
    lump_size[9] = (int)(dmap_wp - base) - lump_pos[9];
    lump_pos[10] = (int)(dmap_wp - base);
    dmap_w16(minx);
    dmap_w16(miny);
    dmap_w16(bw);
    dmap_w16(bh);
    for (k = 0; k < bw * bh; k++)
        dmap_w16(list_off);
    dmap_w16(0);
    for (k = 0; k < nl; k++)
        dmap_w16(k);
    dmap_w16(-1);
    lump_size[10] = (int)(dmap_wp - base) - lump_pos[10];
    n = (int)(dmap_wp - base);
    {
        unsigned char *dir = dmap_wp;
        int table_off = n;
        for (k = 0; k < 11; k++) {
            int q, len = (int)strlen(names[k]);
            dmap_w32(lump_pos[k]);
            dmap_w32(lump_size[k]);
            for (q = 0; q < 8; q++)
                dmap_w8(q < len ? (unsigned)names[k][q] : 0u);
        }
        {
            int total = n + 11 * 16;
            if (total > DMAP_WAD_MAX)
                return -1;
            dmap_wp = dmap_wad;
            dmap_w8('P');
            dmap_w8('W');
            dmap_w8('A');
            dmap_w8('D');
            dmap_w32(11);
            dmap_w32(table_off);
            *size_out = total;
        }
    }
    return 0;
}

/** Write the compiled level to a snapshot path in /saves. */
static int dmap_export_wad(const char *path) {
    int size = 0;
    FILE *fp;
    size_t wrote;
    if (dmap_build_wad(&size) != 0)
        return -1;
    fp = fopen(path, "wb");
    if (!fp)
        return -1;
    wrote = fwrite(dmap_wad, 1, (size_t)size, fp);
    fclose(fp);
    return wrote == (size_t)size ? 0 : -1;
}

/** Validate a PWAD file header and lump census, headless. */
static int dmap_check_wad(const char *path) {
    unsigned char head[12];
    FILE *fp = fopen(path, "rb");
    long magic_ok;
    if (!fp)
        return -1;
    if (fread(head, 1, 12, fp) != 12) {
        fclose(fp);
        return -1;
    }
    fclose(fp);
    magic_ok = head[0] == 'P' && head[1] == 'W' && head[2] == 'A' && head[3] == 'D';
    if (!magic_ok)
        return -1;
    return 0;
}

/** DDA raycaster preview in the raycastlib grid style, integer math free. */
static void dmap_preview(struct nk_command_buffer *canvas, struct nk_rect area) {
    float dirx = cosf(dmap_angle), diry = sinf(dmap_angle);
    float planx = -diry * DMAP_FOV_PLANE, plany = dirx * DMAP_FOV_PLANE;
    int col, n = DMAP_PREV_W;
    float cell = area.w / (float)n;
    struct nk_rect top = nk_rect(area.x, area.y, area.w, area.h / 2.0f);
    struct nk_rect bottom = nk_rect(area.x, area.y + area.h / 2.0f, area.w, area.h / 2.0f);
    nk_fill_rect(canvas, top, 0.0f, nk_rgb(24, 24, 40));
    nk_fill_rect(canvas, bottom, 0.0f, nk_rgb(48, 36, 24));
    for (col = 0; col < n; col++) {
        float camera = 2.0f * (float)col / (float)n - 1.0f;
        float rdx = dirx + planx * camera;
        float rdy = diry + plany * camera;
        int mapx = (int)dmap_px, mapy = (int)dmap_py;
        float ddx = rdx == 0.0f ? 1e30f : fabsf(1.0f / rdx);
        float ddy = rdy == 0.0f ? 1e30f : fabsf(1.0f / rdy);
        float sdx, sdy;
        int stepx, stepy, hit = 0, side = 0, guard = 0;
        float dist;
        int line_h, y0;
        struct nk_color shade;
        if (rdx < 0.0f) {
            stepx = -1;
            sdx = (dmap_px - (float)mapx) * ddx;
        } else {
            stepx = 1;
            sdx = ((float)mapx + 1.0f - dmap_px) * ddx;
        }
        if (rdy < 0.0f) {
            stepy = -1;
            sdy = (dmap_py - (float)mapy) * ddy;
        } else {
            stepy = 1;
            sdy = ((float)mapy + 1.0f - dmap_py) * ddy;
        }
        while (!hit && guard++ < 128) {
            if (sdx < sdy) {
                sdx += ddx;
                mapx += stepx;
                side = 0;
            } else {
                sdy += ddy;
                mapy += stepy;
                side = 1;
            }
            if (mapx < 0 || mapy < 0 || mapx >= dmap_w || mapy >= dmap_h)
                hit = 1;
            else if (dmap_grid[mapy][mapx] == DMAP_WALL ||
                dmap_grid[mapy][mapx] == DMAP_DOOR)
                hit = 1;
        }
        dist = side == 0 ? sdx - ddx : sdy - ddy;
        if (dist < 0.05f)
            dist = 0.05f;
        line_h = (int)(area.h / dist);
        if (line_h > (int)area.h)
            line_h = (int)area.h;
        y0 = (int)(area.y + (area.h - (float)line_h) / 2.0f);
        if (side == 0)
            shade = nk_rgb(176, 150, 120);
        else
            shade = nk_rgb(128, 106, 84);
        nk_fill_rect(canvas, nk_rect(area.x + (float)col * cell, (float)y0, cell + 1.0f, (float)line_h), 0.0f, shade);
    }
}

/** Brush combobox above the canvas: one row for the whole palette. */
static void dmap_brush_combo(struct nk_context *ctx) {
    int before = dmap_brush_sel;
    nk_layout_row_dynamic(ctx, 22, 1);
    nk_combobox(ctx, dmap_brush_labels, DMAP_BRUSH_COUNT, &dmap_brush_sel,
        20, nk_vec2(280, 260));
    if (dmap_brush_sel != before)
        dmap_brush = dmap_brush_kinds[dmap_brush_sel];
}

/** Paintable tile canvas with per-category colors. The caller owns the
 * layout row and column: this only claims the widget, draws and paints.
 * Tools: paint one cell, fill the connected region, or two clicks for a
 * line / rectangle border. Single edits stay single-undo gestures. */
static void dmap_canvas(struct nk_context *ctx) {
    struct nk_command_buffer *canvas;
    struct nk_rect total;
    int row, col;
    if (!nk_widget(&total, ctx))
        return;
    canvas = nk_window_get_canvas(ctx);
    nk_fill_rect(canvas, total, 0.0f, nk_rgb(16, 16, 16));
    for (row = 0; row < dmap_h; row++)
        for (col = 0; col < dmap_w; col++) {
            struct nk_rect cell = nk_rect(total.x + 4.0f + (float)(col * DMAP_CELL_PX),
                total.y + 4.0f + (float)(row * DMAP_CELL_PX),
                (float)(DMAP_CELL_PX - 1), (float)(DMAP_CELL_PX - 1));
            nk_fill_rect(canvas, cell, 0.0f,
                dmap_cell_color((unsigned char)dmap_grid[row][col]));
        }
    if (dmap_show_unreach) {
        int seen[DMAP_MAX_H][DMAP_MAX_W];
        dmap_reach_map(seen);
        for (row = 0; row < dmap_h; row++)
            for (col = 0; col < dmap_w; col++) {
                if (dmap_grid[row][col] == DMAP_WALL || seen[row][col])
                    continue;
                if (!dmap_walkable(dmap_grid[row][col]))
                    continue;
                nk_stroke_rect(canvas,
                    nk_rect(total.x + 4.0f + (float)(col * DMAP_CELL_PX),
                        total.y + 4.0f + (float)(row * DMAP_CELL_PX),
                        (float)(DMAP_CELL_PX - 1), (float)(DMAP_CELL_PX - 1)),
                    0.0f, 1.0f, nk_rgb(255, 60, 60));
            }
    }
    if (dmap_show_grid) {
        int k;
        struct nk_color line = nk_rgb(70, 70, 70);
        for (k = 0; k <= dmap_h; k++) {
            float y = total.y + 4.0f + (float)(k * DMAP_CELL_PX) - 0.5f;
            nk_stroke_line(canvas, total.x + 4.0f, y,
                total.x + 4.0f + (float)(dmap_w * DMAP_CELL_PX), y, 1.0f, line);
        }
        for (k = 0; k <= dmap_w; k++) {
            float x = total.x + 4.0f + (float)(k * DMAP_CELL_PX) - 0.5f;
            nk_stroke_line(canvas, x, total.y + 4.0f,
                x, total.y + 4.0f + (float)(dmap_h * DMAP_CELL_PX), 1.0f, line);
        }
    }
    if (dmap_anchor_active) {
        nk_stroke_rect(canvas,
            nk_rect(total.x + 4.0f + (float)(dmap_anchor_c * DMAP_CELL_PX),
                total.y + 4.0f + (float)(dmap_anchor_r * DMAP_CELL_PX),
                (float)(DMAP_CELL_PX - 1), (float)(DMAP_CELL_PX - 1)),
            0.0f, 1.0f, nk_rgb(255, 255, 0));
    }
    {
        float fx = total.x + 4.0f + (dmap_px - 0.15f) * (float)DMAP_CELL_PX;
        float fy = total.y + 4.0f + (dmap_py - 0.15f) * (float)DMAP_CELL_PX;
        nk_fill_rect(canvas, nk_rect(fx, fy, (float)DMAP_CELL_PX * 0.3f, (float)DMAP_CELL_PX * 0.3f), 0.0f, nk_rgb(255, 255, 255));
    }
    if (nk_input_is_mouse_click_in_rect(&ctx->input, NK_BUTTON_LEFT, total)) {
        struct nk_vec2 m = ctx->input.mouse.pos;
        int c = (int)((m.x - total.x - 4.0f) / (float)DMAP_CELL_PX);
        int r = (int)((m.y - total.y - 4.0f) / (float)DMAP_CELL_PX);
        if (r >= 0 && c >= 0 && r < dmap_h && c < dmap_w) {
            if (dmap_tool == DMAP_TOOL_FILL) {
                dmap_push_history();
                dmap_flood_fill(r, c, dmap_brush);
            } else if (dmap_tool == DMAP_TOOL_LINE || dmap_tool == DMAP_TOOL_RECT) {
                if (!dmap_anchor_active) {
                    dmap_anchor_r = r;
                    dmap_anchor_c = c;
                    dmap_anchor_active = 1;
                } else {
                    dmap_push_history();
                    if (dmap_tool == DMAP_TOOL_LINE)
                        dmap_draw_line(dmap_anchor_r, dmap_anchor_c, r, c, dmap_brush);
                    else
                        dmap_draw_rect(dmap_anchor_r, dmap_anchor_c, r, c, dmap_brush);
                    dmap_anchor_active = 0;
                    dmap_level_sel = 0;
                }
            } else {
                dmap_push_history();
                dmap_apply_cell(r, c, dmap_brush);
                dmap_level_sel = 0;
            }
        }
    }
}

/** Preview strip with turn and step controls bound to the player. */
static void dmap_preview_row(struct nk_context *ctx) {
    struct nk_command_buffer *canvas;
    struct nk_rect total;
    nk_layout_row_static(ctx, (float)(DMAP_PREV_H + 8), DMAP_PREV_W + 8, 1);
    if (!nk_widget(&total, ctx))
        return;
    canvas = nk_window_get_canvas(ctx);
    dmap_preview(canvas, nk_rect(total.x + 4.0f, total.y + 4.0f, (float)DMAP_PREV_W, (float)DMAP_PREV_H));
    nk_layout_row_dynamic(ctx, 22, 4);
    if (nk_button_label(ctx, "Turn <"))
        dmap_angle -= DMAP_TURN_STEP;
    if (nk_button_label(ctx, "Turn >"))
        dmap_angle += DMAP_TURN_STEP;
    if (nk_button_label(ctx, "Step")) {
        float nx = dmap_px + cosf(dmap_angle) * DMAP_MOVE_STEP;
        float ny = dmap_py + sinf(dmap_angle) * DMAP_MOVE_STEP;
        int cx = (int)nx, cy = (int)ny;
        if (cx >= 0 && cy >= 0 && cx < dmap_w && cy < dmap_h && dmap_walkable(dmap_grid[cy][cx])) {
            dmap_px = nx;
            dmap_py = ny;
        }
    }
    if (nk_button_label(ctx, "Reset")) {
        int r, c;
        for (r = 0; r < dmap_h; r++)
            for (c = 0; c < dmap_w; c++)
                if (dmap_grid[r][c] == DMAP_PLAYER) {
                    dmap_px = (float)c + 0.5f;
                    dmap_py = (float)r + 0.5f;
                }
        dmap_angle = 0.0f;
    }
}

/** Export the snapshot pair and boot Doom on the fresh PWAD. */
static void dmap_run_map(void) {
    char txt[DMAP_FNAME_MAX], wad[DMAP_FNAME_MAX];
    const char *args[4];
    snprintf(txt, sizeof(txt), DMAP_SAVE_TXT, dmap_slot);
    snprintf(wad, sizeof(wad), DMAP_SAVE_WAD, dmap_slot);
    if (dmap_save_txt(txt) != 0) {
        snprintf(dmap_status, sizeof(dmap_status), "cannot write %s", txt);
        return;
    }
    if (dmap_export_wad(wad) != 0) {
        snprintf(dmap_status, sizeof(dmap_status), "export refused: %s", dmap_status);
        return;
    }
    dmap_vga(0);
    nk_sys_kbd_raw(0);
    args[0] = DMAP_TOOL_DOOM;
    args[1] = "-file";
    args[2] = wad;
    args[3] = 0;
    dmap_spawn(DMAP_TOOL_DOOM, 3, args);
    nk_sys_kbd_raw(1);
    dmap_vga(1);
    nk_sys_gfx_set_title(DMAP_TITLE);
    snprintf(dmap_status, sizeof(dmap_status), "played %s", wad);
}

/** Main window layout: toolbar and status rows, then the canvas column
 * beside the side panel (slots, level picker, brush combo, preview).
 * The row height fits the taller side so nothing clips off the 360 px
 * window: previously the preview buttons fell off-screen whenever the
 * map had ten or more rows. */
static void dmap_build(struct nk_context *ctx) {
    char txt[DMAP_FNAME_MAX], wad[DMAP_FNAME_MAX];
    float canvas_h = (float)(dmap_h * DMAP_CELL_PX + 8);
    float row_h = canvas_h > DMAP_PANEL_MIN_H ? canvas_h : DMAP_PANEL_MIN_H;
    if (!nk_begin(ctx, DMAP_TITLE, nk_rect(0, 0, (float)NK_W, (float)NK_H), 0)) {
        nk_end(ctx);
        return;
    }
    nk_layout_row_dynamic(ctx, 22, 5);
    if (nk_button_label(ctx, "New"))
        dmap_new();
    if (nk_button_label(ctx, "Export")) {
        snprintf(txt, sizeof(txt), DMAP_SAVE_TXT, dmap_slot);
        snprintf(wad, sizeof(wad), DMAP_SAVE_WAD, dmap_slot);
        if (dmap_save_txt(txt) == 0 && dmap_export_wad(wad) == 0)
            snprintf(dmap_status, sizeof(dmap_status), "wrote %s", wad);
    }
    if (nk_button_label(ctx, "Run (Ctrl+R)"))
        dmap_run_map();
    if (nk_button_label(ctx, "Undo"))
        dmap_undo();
    if (nk_button_label(ctx, "Quit"))
        dmap_quit = 1;
    nk_layout_row_dynamic(ctx, 22, 8);
    if (nk_button_label(ctx, dmap_tool == DMAP_TOOL_PAINT ? "[Paint]" : "Paint")) {
        dmap_tool = DMAP_TOOL_PAINT;
        dmap_anchor_active = 0;
    }
    if (nk_button_label(ctx, dmap_tool == DMAP_TOOL_LINE ? "[Line]" : "Line")) {
        dmap_tool = DMAP_TOOL_LINE;
        dmap_anchor_active = 0;
    }
    if (nk_button_label(ctx, dmap_tool == DMAP_TOOL_RECT ? "[Rect]" : "Rect")) {
        dmap_tool = DMAP_TOOL_RECT;
        dmap_anchor_active = 0;
    }
    if (nk_button_label(ctx, dmap_tool == DMAP_TOOL_FILL ? "[Fill]" : "Fill")) {
        dmap_tool = DMAP_TOOL_FILL;
        dmap_anchor_active = 0;
    }
    if (nk_button_label(ctx, dmap_show_grid ? "[Grid]" : "Grid"))
        dmap_show_grid = !dmap_show_grid;
    if (nk_button_label(ctx, dmap_show_unreach ? "[Unreach]" : "Unreach"))
        dmap_show_unreach = !dmap_show_unreach;
    if (nk_button_label(ctx, "Redo"))
        dmap_redo();
    if (nk_button_label(ctx, "Valid"))
        dmap_validate(dmap_status, sizeof(dmap_status));
    nk_layout_row_dynamic(ctx, 16, 1);
    {
        char line[DMAP_STATUS_MAX + 16];
        snprintf(line, sizeof(line), "slot: %d   %s", dmap_slot, dmap_status);
        nk_label(ctx, line, NK_TEXT_LEFT);
    }
    nk_layout_row_begin(ctx, NK_STATIC, row_h, 2);
    nk_layout_row_push(ctx, (float)DMAP_CANVAS_W);
    dmap_canvas(ctx);
    nk_layout_row_push(ctx, (float)NK_W - (float)DMAP_CANVAS_W - 14.0f);
    if (nk_group_begin(ctx, "panel", NK_WINDOW_BORDER)) {
        nk_layout_row_dynamic(ctx, 22, 4);
        if (nk_button_label(ctx, "Slot 0"))
            dmap_slot = 0;
        if (nk_button_label(ctx, "Slot 1"))
            dmap_slot = 1;
        if (nk_button_label(ctx, "Slot 2"))
            dmap_slot = 2;
        if (nk_button_label(ctx, "Slot 3"))
            dmap_slot = 3;
        nk_layout_row_begin(ctx, NK_STATIC, 22, 2);
        nk_layout_row_push(ctx, 190);
        {
            static const char *items[DMAP_LEVEL_COUNT + 1];
            static int items_init = 0;
            int before, k;
            if (!items_init) {
                items[0] = "Custom";
                for (k = 0; k < DMAP_LEVEL_COUNT; k++)
                    items[k + 1] = dmap_level_names[k];
                items_init = 1;
            }
            before = dmap_level_sel;
            nk_combobox(ctx, items, DMAP_LEVEL_COUNT + 1, &dmap_level_sel, 20, nk_vec2(190, 200));
            if (dmap_level_sel != before && dmap_level_sel > 0)
                dmap_load_preset(dmap_level_sel - 1);
        }
        nk_layout_row_push(ctx, 90);
        if (nk_button_label(ctx, "Random"))
            dmap_random_map((unsigned)nk_sys_time_ms() + 1u);
        nk_layout_row_end(ctx);
        dmap_brush_combo(ctx);
        nk_layout_row_dynamic(ctx, 14, 1);
        {
            char stats[DMAP_STATUS_MAX];
            dmap_stats(stats, sizeof(stats));
            nk_label(ctx, stats, NK_TEXT_LEFT);
        }
        dmap_preview_row(ctx);
        nk_group_end(ctx);
    }
    nk_layout_row_end(ctx);
    dmap_validate(dmap_status, sizeof(dmap_status));
    nk_end(ctx);
}

/** Ctrl+R scancode hook: the Run gesture must work with focus in canvas.
 * Ctrl+Z / Ctrl+Y drive undo / redo on the same path. */
static int dmap_undo_requested = 0;
static int dmap_redo_requested = 0;
static void dmap_scancode(int code, int make, int e0, void *ud) {
    (void)ud;
    if (e0)
        return;
    if (code == 0x1D) {
        dmap_ctrl_held = make;
        return;
    }
    if (!make || !dmap_ctrl_held)
        return;
    if (code == 0x13)
        dmap_run_requested = 1;
    else if (code == 0x2C)
        dmap_undo_requested = 1;
    else if (code == 0x15)
        dmap_redo_requested = 1;
}

/** Frame loop owning the display exactly like the sibling editors. */
static void dmap_gui_run(void) {
    unsigned char pal768[768];
    struct nk_user_font font = nk_minios_font();
    struct nk_context ctx;
    int origin[2] = {0, 0};
    nk_sys_vga_mode(1);
    nk_sys_gfx_set_title(DMAP_TITLE);
    nk_sys_kbd_raw(1);
    nk_build_palette(pal768);
    nk_sys_palette(pal768);
    if (!nk_init_fixed(&ctx, dmap_ui_memory, DMAP_UI_MEMORY, &font)) {
        printf("doomedit: init failed\n");
        nk_sys_kbd_raw(0);
        nk_sys_vga_mode(0);
        return;
    }
    nk_theme_apply(&ctx, 0);
    dmap_new();
    nk_set_scancode_hook(dmap_scancode, 0);
    while (!dmap_quit) {
        nk_input_begin(&ctx);
        nk_poll_input(&ctx);
        nk_input_end(&ctx);
        if (nk_quit_requested())
            dmap_quit = 1;
        if (dmap_run_requested) {
            dmap_run_requested = 0;
            dmap_run_map();
        }
        if (dmap_undo_requested) {
            dmap_undo_requested = 0;
            dmap_undo();
        }
        if (dmap_redo_requested) {
            dmap_redo_requested = 0;
            dmap_redo();
        }
        dmap_build(&ctx);
        nk_rasterize(&ctx);
        if (nk_sys_nk_frame(origin) == 0)
            nk_set_window_origin(origin[0], origin[1]);
        nk_clear(&ctx);
        {
            unsigned t0 = (unsigned)nk_sys_time_ms();
            while ((unsigned)nk_sys_time_ms() - t0 < DMAP_FRAME_MS)
                __asm__ volatile("pause");
        }
    }
    nk_free(&ctx);
    nk_sys_kbd_raw(0);
    nk_sys_vga_mode(0);
}

/** Headless demo room shared by --demo and the selftest build check. */
static void dmap_demo_room(void) {
    dmap_w = 9;
    dmap_h = 7;
    dmap_new();
    dmap_grid[1][2] = DMAP_FLOOR;
    dmap_grid[2][7] = DMAP_EXIT;
    dmap_grid[3][5] = DMAP_IMP;
    dmap_grid[4][3] = DMAP_MEDI;
    dmap_grid[2][6] = DMAP_SHELLS;
}

/** Render one UI frame and prove the composite plus the PWAD builder. */
static int dmap_selftest(void) {
    unsigned char pal768[768];
    struct nk_user_font font = nk_minios_font();
    struct nk_context ctx;
    int origin[2] = {0, 0};
    int size = 0;
    nk_sys_vga_mode(1);
    nk_sys_kbd_raw(1);
    nk_build_palette(pal768);
    nk_sys_palette(pal768);
    if (!nk_init_fixed(&ctx, dmap_ui_memory, DMAP_UI_MEMORY, &font)) {
        printf("doomedit: init failed\n");
        return 1;
    }
    nk_input_begin(&ctx);
    nk_input_end(&ctx);
    dmap_new();
    dmap_build(&ctx);
    nk_rasterize(&ctx);
    NK_BACKBUF[0] = 0xF0;
    /* Mirror the marker into the RGB twin when the kernel maps it: the
     * present routes there. Mirrored exact, never nearest. */
    if (nk_rgb_available()) {
        volatile uint8_t *mrgb = NK_RGB_BUF;
        mrgb[0] = pal768[0xF0 * 3];
        mrgb[1] = pal768[0xF0 * 3 + 1];
        mrgb[2] = pal768[0xF0 * 3 + 2];
    }
    if (nk_sys_nk_frame(origin) != 0) {
        printf("doomedit: frame syscall failed\n");
        return 1;
    }
    {
        volatile uint8_t *fb = (volatile uint8_t *)MINIOS_FB_ADDR;
        int fw = 0, fh = 0, fp = 0;
        int bpx;
        nk_sys_fb_info(&fw, &fh, &fp);
        bpx = (fw > 0 && fp % fw == 0) ? fp / fw : 1;
        if (origin[0] < 0 || origin[1] < 0 || origin[0] >= fw || origin[1] >= fh) {
            printf("doomedit: bad window origin\n");
            return 1;
        }
        if (bpx == 1) {
            if (fb[origin[1] * fp + origin[0]] != NK_BACKBUF[0]) {
                printf("doomedit: composite did not land\n");
                return 1;
            }
        }
    }
    nk_free(&ctx);
    dmap_demo_room();
    if (dmap_build_wad(&size) != 0) {
        printf("doomedit: demo room refused: %s\n", dmap_status);
        return 1;
    }
    if (size < 64 || dmap_wad[0] != 'P' || dmap_wad[1] != 'W') {
        printf("doomedit: demo PWAD header broken\n");
        return 1;
    }
    {
        int k;
        for (k = 0; k < DMAP_LEVEL_COUNT; k++) {
            if (dmap_load_preset(k) != 0) {
                printf("doomedit: preset %d refused to load\n", k);
                return 1;
            }
            if (dmap_build_wad(&size) != 0) {
                printf("doomedit: preset %d export refused: %s\n", k, dmap_status);
                return 1;
            }
        }
        printf("doomedit: presets ok (%d levels)\n", DMAP_LEVEL_COUNT);
    }
    dmap_random_map(0xC0FFEEu);
    if (dmap_validate(dmap_status, sizeof(dmap_status)) != 0) {
        printf("doomedit: random map invalid: %s\n", dmap_status);
        return 1;
    }
    if (dmap_build_wad(&size) != 0) {
        printf("doomedit: random export refused: %s\n", dmap_status);
        return 1;
    }
    printf("doomedit: random ok (%d bytes)\n", size);
    {
        char stats[DMAP_STATUS_MAX];
        dmap_w = 9;
        dmap_h = 7;
        dmap_new();
        dmap_push_history();
        dmap_flood_fill(3, 3, DMAP_DARK);
        if (dmap_grid[3][3] != DMAP_DARK || dmap_grid[1][1] != DMAP_PLAYER) {
            printf("doomedit: flood fill broke markers\n");
            return 1;
        }
        dmap_push_history();
        dmap_draw_line(2, 1, 2, 7, DMAP_WALL);
        if (dmap_grid[2][4] != DMAP_WALL) {
            printf("doomedit: line tool broke\n");
            return 1;
        }
        if (dmap_undo() != 0 || dmap_grid[2][4] == DMAP_WALL) {
            printf("doomedit: undo broke\n");
            return 1;
        }
        if (dmap_redo() != 0 || dmap_grid[2][4] != DMAP_WALL) {
            printf("doomedit: redo broke\n");
            return 1;
        }
        dmap_undo();
        dmap_undo();
        dmap_stats(stats, sizeof(stats));
        if (!stats[0]) {
            printf("doomedit: stats broke\n");
            return 1;
        }
        printf("doomedit: tools ok (%s)\n", stats);
    }
    nk_sys_kbd_raw(0);
    nk_sys_vga_mode(0);
    printf("doomedit: frame ok (%dx%d)\n", NK_W, NK_H);
    printf("doomedit: build ok (%d bytes)\n", size);
    return 0;
}

int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], "--selftest") == 0)
        return dmap_selftest();
    if (argc > 1 && strcmp(argv[1], "--demo") == 0) {
        if (argc < 3) {
            printf("usage: doomedit --demo <out.wad>\n");
            return 2;
        }
        dmap_demo_room();
        if (dmap_export_wad(argv[2]) != 0) {
            printf("doomedit: export refused: %s\n", dmap_status);
            return 1;
        }
        printf("doomedit: wrote %s\n", argv[2]);
        return 0;
    }
    if (argc > 1 && strcmp(argv[1], "--random") == 0) {
        unsigned seed = 0x9E3779B9u;
        const char *out;
        if (argc < 3) {
            printf("usage: doomedit --random [seed] <out.wad>\n");
            return 2;
        }
        if (argc >= 4) {
            seed = (unsigned)strtoul(argv[2], 0, 0);
            out = argv[3];
        } else {
            out = argv[2];
        }
        dmap_random_map(seed);
        if (dmap_export_wad(out) != 0) {
            printf("doomedit: export refused: %s\n", dmap_status);
            return 1;
        }
        printf("doomedit: wrote %s (%s)\n", out, dmap_status);
        return 0;
    }
    if (argc > 1 && strcmp(argv[1], "--preset") == 0) {
        int idx;
        if (argc < 4) {
            printf("usage: doomedit --preset <0-8> <out.wad>\n");
            return 2;
        }
        idx = atoi(argv[2]);
        if (dmap_load_preset(idx) != 0) {
            printf("doomedit: bad preset %s\n", argv[2]);
            return 1;
        }
        if (dmap_export_wad(argv[3]) != 0) {
            printf("doomedit: export refused: %s\n", dmap_status);
            return 1;
        }
        printf("doomedit: wrote %s (%s)\n", argv[3], dmap_level_names[idx]);
        return 0;
    }
    if (argc > 1 && strcmp(argv[1], "--export") == 0) {
        if (argc < 4) {
            printf("usage: doomedit --export <grid.txt> <out.wad>\n");
            return 2;
        }
        if (dmap_load(argv[2]) != 0) {
            printf("doomedit: cannot load %s\n", argv[2]);
            return 1;
        }
        if (dmap_export_wad(argv[3]) != 0) {
            printf("doomedit: export refused: %s\n", dmap_status);
            return 1;
        }
        printf("doomedit: wrote %s\n", argv[3]);
        return 0;
    }
    if (argc > 1 && strcmp(argv[1], "--check") == 0) {
        if (argc < 3) {
            printf("usage: doomedit --check <file.wad>\n");
            return 2;
        }
        if (dmap_check_wad(argv[2]) != 0) {
            printf("doomedit: %s invalid\n", argv[2]);
            return 1;
        }
        printf("doomedit: %s ok\n", argv[2]);
        return 0;
    }
    if (argc > 1 && strcmp(argv[1], "--help") == 0) {
        printf("doomedit: tile editor that builds Doom PWAD snapshots\n");
        printf("  (no args)               GUI editor\n");
        printf("  --demo out.wad          write a fixed demo room\n");
        printf("  --preset N out.wad      write bundled level N (0-8)\n");
        printf("  --random [seed] out.wad write connected rooms procedurally\n");
        printf("  --export grid.txt out   compile a grid file\n");
        printf("  --check file.wad        validate a PWAD file\n");
        printf("  --selftest              one frame plus a build check\n");
        return 0;
    }
    dmap_gui_run();
    return 0;
}
