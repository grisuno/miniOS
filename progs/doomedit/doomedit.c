/** doomedit.c - tile map editor that builds playable Doom PWADs.
 *
 * A ring-3 Nuklear application built exactly like the node editor
 * (host gcc -static -no-pie, ships on MiniFS with a bare-name alias).
 * The author paints walls, the player start, the exit switch marker
 * and a small thing palette on a tile canvas, watches a live DDA
 * raycaster preview in the Wolfenstein style of the sibling
 * ../raycastlib checkout, exports a single-sector E1M1 PWAD snapshot
 * into /saves, and boots the shipped Doom on it without ever writing
 * to the immutable IWAD.
 *
 *     doomedit                      -> GUI editor
 *     doomedit --demo <out.wad>     -> write a fixed demo room PWAD
 *     doomedit --preset <0-4> <wad> -> write a bundled level PWAD
 *     doomedit --export <grid> <wad> -> compile a grid text file
 *     doomedit --check <file.wad>   -> validate a PWAD file
 *     doomedit --selftest           -> one UI frame plus a build check
 *
 * The PWAD layout implements the same algorithm as tools/doom_pwad.py:
 * one sector, segs mirroring the boundary linedefs, one subsector,
 * one root node, one shared-list blockmap. Both sides stay in sync
 * through the byte pin in tests/test_doom_pwad.py.
 *
 * Levels travel in the same one-char-per-tile grid text the editor saves
 * to /saves/dmapN.txt, so a level weighs a few hundred bytes. The five
 * bundled levels below are compiled in as string rows in exactly that
 * format; the Random button grows the same format procedurally.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "minios_abi.h"

#include "nuklear.h"
#include "nuklear_minios.h"
#include "nuklear_theme.h"

/** Central configuration: every bound, path, id and label in one place. */
#define DMAP_MAX_W 24
#define DMAP_MAX_H 16
#define DMAP_DEF_W 14
#define DMAP_DEF_H 10
#define DMAP_TILE 128
#define DMAP_CELL_PX 22
#define DMAP_PREV_W 240
#define DMAP_PREV_H 120
#define DMAP_UI_MEMORY (2 * 1024 * 1024)
#define DMAP_WAD_MAX (512 * 1024)
#define DMAP_FNAME_MAX 64
#define DMAP_STATUS_MAX 160
#define DMAP_SLOTS 4
#define DMAP_LEVEL_COUNT 5
#define DMAP_RANDOM_ATTEMPTS 64
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
#define DMAP_FLAG_BLOCKING 1
#define DMAP_NO_SIDE (-1)
#define DMAP_WALL_MID "STARTAN3"
#define DMAP_EXIT_MID "SW1EXIT"
#define DMAP_UNUSED_TEX "-"
#define DMAP_FLOOR_FLAT "FLOOR4_8"
#define DMAP_CEIL_FLAT "CEIL3_5"
#define DMAP_FLOOR_H 0
#define DMAP_CEIL_H 128
#define DMAP_LIGHT 160
#define DMAP_NODE_LEAF 0x8000u
#define DMAP_TOOL_DOOM "/doomgeneric.elf"
#define DMAP_SAVE_TXT "/saves/dmap%d.txt"
#define DMAP_SAVE_WAD "/saves/dmap%d.wad"
#define DMAP_TITLE "DoomEdit"

/** Brush kinds double as grid cell values on disk. */
enum {
    DMAP_WALL = '#',
    DMAP_FLOOR = '.',
    DMAP_PLAYER = 'P',
    DMAP_EXIT = 'E',
    DMAP_IMP = 'i',
    DMAP_DEMON = 'd',
    DMAP_SHOTGUY = 's',
    DMAP_MEDI = 'm',
    DMAP_SHELLS = 'a'
};

/** Thing type ids, verified present in the shareware IWAD. */
static int dmap_thing_type(int cell) {
    switch (cell) {
    case DMAP_PLAYER: return 1;
    case DMAP_IMP: return 3001;
    case DMAP_DEMON: return 3002;
    case DMAP_SHOTGUY: return 2001;
    case DMAP_MEDI: return 2012;
    case DMAP_SHELLS: return 2008;
    default: return 0;
    }
}

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

/** True for cells the player can stand on. */
static int dmap_walkable(int cell) {
    return cell == DMAP_FLOOR || cell == DMAP_PLAYER || cell == DMAP_EXIT ||
        cell == DMAP_IMP || cell == DMAP_DEMON || cell == DMAP_SHOTGUY ||
        cell == DMAP_MEDI || cell == DMAP_SHELLS;
}

/** Fill the grid with floor and a solid border. */
static void dmap_new(void) {
    int row, col;
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
    "Fortress of Lead"
};

static const char *dmap_levels[DMAP_LEVEL_COUNT][16] = {
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

/** Procedural map with the full palette: demons, imps, shotgunners,
 * medikits and shells on a random wall layout. Starts from the valid
 * plain room, carves wall blobs and scatters things only onto floor
 * cells (the player start and exit marker are never touched), then keeps
 * the first layout the validator accepts. Always leaves a valid map:
 * the fallback is the plain room when no attempt passes. */
static void dmap_random_map(unsigned seed) {
    char msg[DMAP_STATUS_MAX];
    int attempt;
    static const int pack[6] = {DMAP_IMP, DMAP_DEMON, DMAP_SHOTGUY,
        DMAP_IMP, DMAP_DEMON, DMAP_MEDI};
    dmap_rng = seed ? seed : 0x9E3779B9u;
    for (attempt = 0; attempt < DMAP_RANDOM_ATTEMPTS; attempt++) {
        int n, r, c, tries;
        dmap_w = 10 + (int)(dmap_rand() % 11);
        if (dmap_w > DMAP_MAX_W)
            dmap_w = DMAP_MAX_W;
        dmap_h = 8 + (int)(dmap_rand() % 5);
        if (dmap_h > DMAP_MAX_H)
            dmap_h = DMAP_MAX_H;
        dmap_new();
        n = 2 + (int)(dmap_rand() % 4);
        for (; n > 0; n--) {
            int len = 1 + (int)(dmap_rand() % 4);
            r = 1 + (int)(dmap_rand() % (unsigned)(dmap_h - 2));
            c = 1 + (int)(dmap_rand() % (unsigned)(dmap_w - 2));
            for (; len > 0; len--) {
                if (dmap_grid[r][c] == DMAP_FLOOR)
                    dmap_grid[r][c] = DMAP_WALL;
                r += (int)(dmap_rand() % 3) - 1;
                c += (int)(dmap_rand() % 3) - 1;
                if (r < 1)
                    r = 1;
                if (r > dmap_h - 2)
                    r = dmap_h - 2;
                if (c < 1)
                    c = 1;
                if (c > dmap_w - 2)
                    c = dmap_w - 2;
            }
        }
        n = 2 + (int)(dmap_rand() % 4);
        for (; n > 0; n--) {
            if (!dmap_free_cell(&r, &c))
                continue;
            dmap_grid[r][c] = (char)pack[dmap_rand() % 6];
        }
        {
            static const int must[4] = {DMAP_DEMON, DMAP_SHOTGUY, DMAP_MEDI, DMAP_SHELLS};
            for (n = 0; n < 4; n++) {
                for (tries = 0; tries < 32; tries++)
                    if (dmap_free_cell(&r, &c)) {
                        dmap_grid[r][c] = (char)must[n];
                        break;
                    }
            }
        }
        if (dmap_validate(msg, sizeof(msg)) == 0) {
            dmap_recenter();
            snprintf(dmap_status, sizeof(dmap_status), "random %dx%d ok", dmap_w, dmap_h);
            return;
        }
        dmap_rng = dmap_rng * 1664525u + 1013904223u;
    }
    dmap_new();
    snprintf(dmap_status, sizeof(dmap_status), "random fell back to plain room");
}

/** Load a grid text file, refusing ragged or illegal content. */
static int dmap_load(const char *path) {
    FILE *fp = fopen(path, "r");
    int row = 0, col = 0, ch;
    if (!fp)
        return -1;
    while ((ch = fgetc(fp)) != EOF && row < DMAP_MAX_H) {
        if (ch == '\n') {
            if (col == 0)
                continue;
            if (row == 0)
                dmap_w = col;
            if (col != dmap_w) {
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
        dmap_grid[row][col++] = (char)ch;
    }
    fclose(fp);
    if (col != 0) {
        if (row == 0)
            dmap_w = col;
        if (col != dmap_w)
            return -1;
        row++;
    }
    if (row < 3)
        return -1;
    dmap_h = row;
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
            snprintf(msg, (size_t)max, "ok: %dx%d single sector", dmap_w, dmap_h);
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

/** Compile the grid into a vanilla single-sector E1M1 PWAD image. */
static int dmap_build_wad(int *size_out) {
    static int vx[DMAP_MAX_VERTS * 2];
    static int li_v[DMAP_MAX_LINES * 2];
    static int li_exit[DMAP_MAX_LINES];
    static int th_x[DMAP_MAX_THINGS];
    static int th_y[DMAP_MAX_THINGS];
    static int th_t[DMAP_MAX_THINGS];
    int nv = 0, nl = 0, nt = 0;
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
            int x0, x1, yt, yb, e;
            int ex[4][2][2], ed[4];
            if (!dmap_walkable(dmap_grid[row][col]))
                continue;
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
                int v1 = -1, v2 = -1, q;
                if (!dmap_is_wall(nr, nc))
                    continue;
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
                if (v1 < 0 || v2 < 0 || nl >= DMAP_MAX_LINES)
                    return -1;
                if (row == er && col == ec && ed[e] == edir)
                    exit_edge = nl;
                li_v[nl * 2] = v1;
                li_v[nl * 2 + 1] = v2;
                li_exit[nl] = (nl == exit_edge);
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
        dmap_w16(DMAP_FLAG_BLOCKING);
        dmap_w16(li_exit[k] ? DMAP_EXIT_SPECIAL : 0);
        dmap_w16(0);
        dmap_w16(k);
        dmap_w16(DMAP_NO_SIDE);
    }
    lump_size[2] = (int)(dmap_wp - base) - lump_pos[2];
    lump_pos[3] = (int)(dmap_wp - base);
    for (k = 0; k < nl; k++) {
        dmap_w16(0);
        dmap_w16(0);
        dmap_wtex(DMAP_UNUSED_TEX);
        dmap_wtex(DMAP_UNUSED_TEX);
        dmap_wtex(li_exit[k] ? DMAP_EXIT_MID : DMAP_WALL_MID);
        dmap_w16(0);
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
    dmap_w16(DMAP_FLOOR_H);
    dmap_w16(DMAP_CEIL_H);
    dmap_wtex(DMAP_FLOOR_FLAT);
    dmap_wtex(DMAP_CEIL_FLAT);
    dmap_w16(DMAP_LIGHT);
    dmap_w16(0);
    dmap_w16(0);
    lump_size[8] = (int)(dmap_wp - base) - lump_pos[8];
    lump_pos[9] = (int)(dmap_wp - base);
    dmap_w8(0);
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
            else if (dmap_grid[mapy][mapx] == DMAP_WALL)
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

/** Brush button row above the canvas. */
static void dmap_brush_row(struct nk_context *ctx) {
    static const char *labels[9] = {"Wall", "Floor", "Player", "Exit", "Imp", "Demon", "Shot", "Medi", "Shell"};
    static const int kinds[9] = {DMAP_WALL, DMAP_FLOOR, DMAP_PLAYER, DMAP_EXIT,
        DMAP_IMP, DMAP_DEMON, DMAP_SHOTGUY, DMAP_MEDI, DMAP_SHELLS};
    int k;
    nk_layout_row_dynamic(ctx, 22, 9);
    for (k = 0; k < 9; k++) {
        if (nk_option_label(ctx, labels[k], dmap_brush == kinds[k]))
            dmap_brush = kinds[k];
    }
}

/** Paintable tile canvas with per-cell colors and status glyphs. */
static void dmap_canvas(struct nk_context *ctx) {
    struct nk_command_buffer *canvas;
    struct nk_rect total;
    int row, col;
    nk_layout_row_static(ctx, (float)(dmap_h * DMAP_CELL_PX + 8), dmap_w * DMAP_CELL_PX + 8, 1);
    if (!nk_widget(&total, ctx))
        return;
    canvas = nk_window_get_canvas(ctx);
    nk_fill_rect(canvas, total, 0.0f, nk_rgb(16, 16, 16));
    for (row = 0; row < dmap_h; row++)
        for (col = 0; col < dmap_w; col++) {
            struct nk_rect cell = nk_rect(total.x + 4.0f + (float)(col * DMAP_CELL_PX),
                total.y + 4.0f + (float)(row * DMAP_CELL_PX),
                (float)(DMAP_CELL_PX - 1), (float)(DMAP_CELL_PX - 1));
            struct nk_color fill = nk_rgb(64, 64, 64);
            int v = dmap_grid[row][col];
            if (v == DMAP_WALL)
                fill = nk_rgb(150, 110, 70);
            else if (v == DMAP_PLAYER)
                fill = nk_rgb(90, 200, 90);
            else if (v == DMAP_EXIT)
                fill = nk_rgb(220, 80, 80);
            else if (v != DMAP_FLOOR)
                fill = nk_rgb(200, 170, 60);
            nk_fill_rect(canvas, cell, 0.0f, fill);
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
            if (dmap_brush == DMAP_PLAYER || dmap_brush == DMAP_EXIT) {
                int rr, cc;
                for (rr = 0; rr < dmap_h; rr++)
                    for (cc = 0; cc < dmap_w; cc++)
                        if (dmap_grid[rr][cc] == dmap_brush)
                            dmap_grid[rr][cc] = DMAP_FLOOR;
            }
            dmap_grid[r][c] = (char)dmap_brush;
            dmap_level_sel = 0;
            if (dmap_brush == DMAP_PLAYER) {
                dmap_px = (float)c + 0.5f;
                dmap_py = (float)r + 0.5f;
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

/** Main window layout: toolbar, canvas, preview and snapshot bar. */
static void dmap_build(struct nk_context *ctx) {
    char txt[DMAP_FNAME_MAX], wad[DMAP_FNAME_MAX];
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
    if (nk_button_label(ctx, "Quit"))
        dmap_quit = 1;
    nk_layout_row_dynamic(ctx, 22, 1);
    {
        char line[DMAP_STATUS_MAX + 16];
        snprintf(line, sizeof(line), "slot: %d   %s", dmap_slot, dmap_status);
        nk_label(ctx, line, NK_TEXT_LEFT);
    }
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
    nk_layout_row_push(ctx, 240);
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
        nk_combobox(ctx, items, DMAP_LEVEL_COUNT + 1, &dmap_level_sel, 20, nk_vec2(240, 200));
        if (dmap_level_sel != before && dmap_level_sel > 0)
            dmap_load_preset(dmap_level_sel - 1);
    }
    nk_layout_row_push(ctx, 120);
    if (nk_button_label(ctx, "Random"))
        dmap_random_map((unsigned)nk_sys_time_ms() + 1u);
    nk_layout_row_end(ctx);
    dmap_brush_row(ctx);
    dmap_canvas(ctx);
    dmap_preview_row(ctx);
    dmap_validate(dmap_status, sizeof(dmap_status));
    nk_end(ctx);
}

/** Ctrl+R scancode hook: the Run gesture must work with focus in canvas. */
static void dmap_scancode(int code, int make, int e0, void *ud) {
    (void)ud;
    if (e0)
        return;
    if (code == 0x1D) {
        dmap_ctrl_held = make;
        return;
    }
    if (code == 0x13 && make && dmap_ctrl_held)
        dmap_run_requested = 1;
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
            printf("usage: doomedit --preset <0-4> <out.wad>\n");
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
        printf("  --preset N out.wad      write bundled level N (0-4)\n");
        printf("  --random [seed] out.wad write a procedural map\n");
        printf("  --export grid.txt out   compile a grid file\n");
        printf("  --check file.wad        validate a PWAD file\n");
        printf("  --selftest              one frame plus a build check\n");
        return 0;
    }
    dmap_gui_run();
    return 0;
}
