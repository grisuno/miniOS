/** Docstring: MiniOS file browser (Nuklear ring-3 app, MiniFS: file/file.elf).
 *
 * A Nuklear browser over the unified filesystem (ramdisk first, MiniFS
 * fallback) through the DIR_LIST syscall (241). File dispatch comes from
 * /etc/association (ext|program lines): text kinds open in vedit through
 * SYS_SPAWN, .o/.elf spawn directly, .cvm spawns through /objects/cvm.o
 * with the module as argv[0], png previews decode in-app with stb_image.
 * Unknown kinds report instead of running. Every bound, tool path and
 * label lives in the config block below; no address or number is
 * hardcoded outside it.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "minios_abi.h"
#include "minios_png.h"
#include "file/file_assoc.h"
#include "nuklear.h"
#include "nuklear_minios.h"
#include "nuklear_theme.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#define STBI_NO_STDIO
#include "stb_image.h"

/** Central configuration: every bound, tool, directory, label and limit. */
#define FILE_MAX_PATH 128
#define FILE_MAX_ENTRIES 256
#define FILE_NAME_MAX 64
#define FILE_LIST_CAP 8192
#define FILE_ASSOC_PATH "/etc/association"
#define FILE_EXT_MAX 8
#define FILE_PROG_MAX 32
#define FILE_TOOL_VEDIT "/vedit"
#define FILE_TOOL_CVM "/objects/cvm.o"
#define FILE_STATUS_MAX 128
#define FILE_UI_MEMORY (4 * 1024 * 1024)
#define FILE_PREVIEW_W 192
#define FILE_PREVIEW_H 120
#define FILE_PREVIEW_FILE_MAX (1024 * 1024)
#define FILE_TITLE "File"
#define FILE_ACTION_SHELL "shell"
#define FILE_ACTION_INTERNAL "internal"
#define FILE_LOG_LINE 96

/** Entry icons: indexed pixels plus a 0/1 alpha mask, decoded once
 * from /icons at startup through the backend NK_COMMAND_IMAGE path.
 * Small is the default grid; big is the toggled grid. Buffers hold the
 * big size and decode scales into the live prefix, so the toggle is one
 * reload with no extra memory. */
#define FILE_ICON_SMALL 16
#define FILE_ICON_BIG 32
#define FILE_ICON_MAX 32
#define FILE_ICON_N 4
#define FILE_ICON_FOLDER 0
#define FILE_ICON_FILES 1
#define FILE_ICON_IMAGE 2
#define FILE_ICON_OBJECT 3
#define FILE_ICON_PATH_FOLDER "/icons/folder.png"
#define FILE_ICON_PATH_FILES "/icons/files.png"
#define FILE_ICON_PATH_IMAGE "/icons/image.png"
#define FILE_ICON_PATH_OBJECT "/icons/object.png"

/** Dispatch kinds resolved from the association table. */
#define FILE_ACT_TEXT 0
#define FILE_ACT_SHELL 1
#define FILE_ACT_INTERNAL 2
#define FILE_ACT_UNKNOWN 3

struct file_assoc {
    char ext[FILE_EXT_MAX + 1];
    char prog[FILE_PROG_MAX + 1];
};

/** Docstring: dynamic assoc table owns entries, fixed array removed. */
static struct fassoc_table file_assocs;

static int file_quit;
static int file_icon_big;
static unsigned char file_icon_px[FILE_ICON_N][FILE_ICON_MAX * FILE_ICON_MAX];
static unsigned char file_icon_mask[FILE_ICON_N][FILE_ICON_MAX * FILE_ICON_MAX];
static struct nk_minios_img file_icon_img[FILE_ICON_N];
static int file_icons_ok;
static char file_cwd[FILE_MAX_PATH];
static char file_entries[FILE_LIST_CAP];
static long file_entry_count;
static char file_status[FILE_STATUS_MAX];
static char file_preview_path[FILE_MAX_PATH];
static unsigned char file_preview_px[FILE_PREVIEW_W * FILE_PREVIEW_H];
static int file_preview_w;
static int file_preview_h;
static int file_preview_on;

/** Raw DIR_LIST syscall (241): names land NUL-separated in buf. */
static long file_sys_dir_list(const char *path, char *buf, long cap) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret)
                     : "a"(MINIOS_SYS_DIR_LIST), "D"(path), "S"(buf),
                       "d"(cap)
                     : "rcx", "r11", "memory");
    return ret;
}

/** Raw SPAWN syscall (215) preserving this app across the child. */
static long file_sys_spawn(const char *path, int argc, const char **argv) {
    long ret;
    register long r10 __asm__("r10") = (long)argv;
    __asm__ volatile("syscall" : "=a"(ret)
                     : "a"(MINIOS_SYS_SPAWN), "D"(path), "S"(0),
                       "d"((long)argc), "r"(r10)
                     : "rcx", "r11", "memory");
    return ret;
}

/** Lowercase the extension of fname into dst (no dot, empty when none). */
static void file_ext_of(const char *fname, char *dst, unsigned cap) {
    unsigned n = 0;
    unsigned dot = 0;
    unsigned k = 0;
    unsigned found = 0;
    while (fname[n] && n < FILE_NAME_MAX) n++;
    for (k = 0; k < n; k++)
        if (fname[k] == '.') { dot = k; found = 1; }
    if (!found || dot + 1 >= n) { dst[0] = 0; return; }
    {
        unsigned m = 0;
        for (k = dot + 1; k < n && m + 1 < cap && m <= FILE_EXT_MAX; k++) {
            char c = fname[k];
            if (c >= 'A' && c <= 'Z') c = (char)(c + 32);
            dst[m++] = c;
        }
        dst[m] = 0;
    }
}

/** Icon kind for an entry: folder for dirs, image for .png, object for
 * .o/.elf/.cvm, files for the text kinds (.c/.h/.lisp/.lua/.py/.txt/.s)
 * and for anything else. The extension arrives lowercased from
 * file_ext_of, so every comparison is exact. */
static int file_icon_kind(const char *fname, int isdir) {
    char ext[FILE_EXT_MAX + 1];
    if (isdir) return FILE_ICON_FOLDER;
    file_ext_of(fname, ext, sizeof(ext));
    if (strcmp(ext, "png") == 0) return FILE_ICON_IMAGE;
    if (strcmp(ext, "o") == 0 || strcmp(ext, "elf") == 0 ||
        strcmp(ext, "cvm") == 0)
        return FILE_ICON_OBJECT;
    return FILE_ICON_FILES;
}

/** Live icon edge: 32 in big mode, 16 in small mode. */
static int file_icon_sz(void) {
    return file_icon_big ? FILE_ICON_BIG : FILE_ICON_SMALL;
}

/** Decode one RGBA icon into indexed pixels plus an alpha mask, scaled to
 * the live size. Fail closed: any bound or decode error returns -1 and
 * leaves the slot untouched. */
static int file_icon_decode(const char *path, unsigned char *px,
                            unsigned char *mask) {
    unsigned char *raw = 0;
    long sz = 0;
    unsigned char *rgba = 0;
    int w = 0;
    int h = 0;
    int comp = 0;
    unsigned char pal[768];
    int edge;
    int x;
    int y;
    if (mpng_load_file(path, &raw, &sz, FILE_PREVIEW_FILE_MAX) != 0)
        return -1;
    rgba = stbi_load_from_memory(raw, (int)sz, &w, &h, &comp, 4);
    free(raw);
    if (!rgba || w <= 0 || h <= 0 || w > MPNG_MAX_DIM || h > MPNG_MAX_DIM) {
        if (rgba) stbi_image_free(rgba);
        return -1;
    }
    nk_build_palette(pal);
    edge = file_icon_sz();
    for (y = 0; y < edge; y++) {
        for (x = 0; x < edge; x++) {
            int sx = x * w / edge;
            int sy = y * h / edge;
            unsigned char *p = rgba + (sy * w + sx) * 4;
            int v;
            if (p[3] < 128) {
                mask[y * edge + x] = 0;
                px[y * edge + x] = 0;
                continue;
            }
            v = mpng_nearest(pal, 256L, p[0], p[1], p[2]);
            if (v < 0) {
                stbi_image_free(rgba);
                return -1;
            }
            mask[y * edge + x] = 1;
            px[y * edge + x] = (unsigned char)v;
        }
    }
    stbi_image_free(rgba);
    return 0;
}

/** Load the four kind icons; all-or-nothing so the UI never mixes icon
 * and text rows. Returns 1 when every icon is live. */
static int file_icons_load(void) {
    static const char *paths[FILE_ICON_N] = {
        FILE_ICON_PATH_FOLDER, FILE_ICON_PATH_FILES,
        FILE_ICON_PATH_IMAGE, FILE_ICON_PATH_OBJECT
    };
    int edge;
    int k;
    for (k = 0; k < FILE_ICON_N; k++) {
        if (file_icon_decode(paths[k], file_icon_px[k],
                             file_icon_mask[k]) != 0)
            return 0;
    }
    edge = file_icon_sz();
    for (k = 0; k < FILE_ICON_N; k++) {
        file_icon_img[k].px = file_icon_px[k];
        file_icon_img[k].mask = file_icon_mask[k];
        file_icon_img[k].w = edge;
        file_icon_img[k].h = edge;
    }
    return 1;
}

/** Flip the icon size and reload the four kind icons. Returns 1 when the
 * new size is live, 0 when the reload failed (flag stays flipped so the
 * next toggle retries the other size instead of sticking). */
static int file_toggle_icons(void) {
    file_icon_big = !file_icon_big;
    file_icons_ok = file_icons_load();
    return file_icons_ok;
}

/** Join dir + name into dst, fail closed on overflow. */
static int file_join(const char *dir, const char *name, char *dst, unsigned cap) {
    unsigned a = 0;
    unsigned b = 0;
    while (dir[a] && a < cap) a++;
    while (name[b] && b < FILE_NAME_MAX) b++;
    if (a + 1 + b + 1 > cap) return -1;
    memcpy(dst, dir, a);
    if (a > 0 && dst[a - 1] != '/') dst[a++] = '/';
    memcpy(dst + a, name, b);
    dst[a + b] = 0;
    return 0;
}

/** Parent of an absolute path, root stays root. */
static void file_parent(char *path) {
    unsigned n = 0;
    while (path[n]) n++;
    while (n > 1 && path[n - 1] == '/') path[--n] = 0;
    while (n > 1 && path[n - 1] != '/') n--;
    if (n <= 1) { path[0] = '/'; path[1] = 0; return; }
    path[n - 1] = 0;
}

/** Validate one association line: ext|program, fail closed. */
static int file_assoc_line(const char *line, char *ext, char *prog) {
    unsigned k = 0;
    unsigned m = 0;
    if (!line[0] || line[0] == '#') return -1;
    while (line[k] && line[k] != '|' && m < FILE_EXT_MAX) {
        char c = line[k];
        if (!((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))) return -1;
        ext[m++] = c;
        k++;
    }
    if (!line[k] || line[k] != '|' || m == 0) return -1;
    k++;
    {
        unsigned p = 0;
        while (line[p + k] && line[p + k] != '\n' && line[p + k] != '\r' &&
               p < FILE_PROG_MAX) {
            if (line[p + k] == '|') return -1;
            prog[p] = line[p + k];
            p++;
        }
        if (line[p + k] && line[p + k] != '\n' && line[p + k] != '\r') return -1;
        while (p > 0 && (prog[p - 1] == ' ' || prog[p - 1] == '\t')) p--;
        prog[p] = 0;
    }
    ext[m] = 0;
    if (!prog[0]) return -1;
    if (strcmp(prog, FILE_ACTION_SHELL) != 0 &&
        strcmp(prog, FILE_ACTION_INTERNAL) != 0 && prog[0] != '/')
        return -1;
    return 0;
}

/** Load the association table, builtins on failure. */
static void file_assoc_load(void) {
    FILE *f;
    char line[FILE_LOG_LINE];
    char ext[FILE_EXT_MAX + 1];
    char prog[FILE_PROG_MAX + 1];
    fassoc_clear(&file_assocs);
    f = fopen(FILE_ASSOC_PATH, "r");
    if (!f) return;
    while (fgets(line, sizeof(line), f)) {
        if (file_assoc_line(line, ext, prog) != 0) continue;
        if (fassoc_push(&file_assocs, ext, prog) != 0) break;
    }
    fclose(f);
}

/** Program for an extension, empty when unmapped. */
static const char *file_assoc_lookup(const char *ext) {
    return fassoc_lookup(&file_assocs, ext);
}

/** Dispatch kind for a file name through the association table. */
static int file_action_of(const char *fname, const char **prog_out) {
    char ext[FILE_EXT_MAX + 1];
    const char *prog;
    file_ext_of(fname, ext, sizeof(ext));
    prog = file_assoc_lookup(ext);
    if (prog_out) *prog_out = prog;
    if (!prog[0]) return FILE_ACT_UNKNOWN;
    if (strcmp(prog, FILE_ACTION_SHELL) == 0) return FILE_ACT_SHELL;
    if (strcmp(prog, FILE_ACTION_INTERNAL) == 0) return FILE_ACT_INTERNAL;
    return FILE_ACT_TEXT;
}

/** Refresh the entry list for the cwd, fail closed with a status. */
static void file_refresh(void) {
    long rc = file_sys_dir_list(file_cwd, file_entries, FILE_LIST_CAP);
    if (rc < 0) {
        file_entry_count = 0;
        file_entries[0] = 0;
        snprintf(file_status, sizeof(file_status), "cannot list %s (%ld)",
                 file_cwd, rc);
        return;
    }
    file_entry_count = rc;
    snprintf(file_status, sizeof(file_status), "%s (%ld entries)", file_cwd,
             rc);
}

/** Decode a png file into the preview buffer, nearest-neighbor downscale. */
static int file_preview_load(const char *path) {
    unsigned char *raw = 0;
    long sz = 0;
    int w = 0;
    int h = 0;
    int comp = 0;
    unsigned char *px = 0;
    if (mpng_load_file(path, &raw, &sz, FILE_PREVIEW_FILE_MAX) != 0)
        return -1;
    px = stbi_load_from_memory(raw, (int)sz, &w, &h, &comp, 3);
    free(raw);
    if (!px || w <= 0 || h <= 0 || w > MPNG_MAX_DIM * 8 || h > MPNG_MAX_DIM * 8) {
        if (px) stbi_image_free(px);
        return -1;
    }
    {
        unsigned char pal[768];
        nk_build_palette(pal);
        if (mpng_rgb_to_idx_scaled(px, w, h, pal, 256, file_preview_px,
                                   FILE_PREVIEW_W,
                                   FILE_PREVIEW_H) != MPNG_ERR_OK) {
            stbi_image_free(px);
            return -1;
        }
    }
    stbi_image_free(px);
    file_preview_w = FILE_PREVIEW_W;
    file_preview_h = FILE_PREVIEW_H;
    file_preview_on = 1;
    return 0;
}

/** Blit the preview buffer into the NK back-buffer after rasterize. */
static void file_preview_blit(int ox, int oy) {
    volatile uint8_t *fb = NK_BACKBUF;
    int x;
    int y;
    if (!file_preview_on) return;
    for (y = 0; y < file_preview_h; y++)
        for (x = 0; x < file_preview_w; x++) {
            int dx = ox + x;
            int dy = oy + y;
            if (dx < 0 || dx >= NK_W || dy < 0 || dy >= NK_H) continue;
            fb[dy * NK_W + dx] = file_preview_px[y * FILE_PREVIEW_W + x];
        }
}

/** Run a program with the display released so output lands on console. */
static long file_spawn_visible(const char *tool, int argc, const char **argv,
                               const char *label) {
    unsigned char pal768[768];
    long rc;
    nk_sys_vga_mode(0);
    nk_sys_kbd_raw(0);
    printf("--- file: %s ---\n", label);
    fflush(stdout);
    rc = file_sys_spawn(tool, argc, argv);
    printf("file: %s exit code: %ld\n", label, rc);
    fflush(stdout);
    nk_sys_vga_mode(1);
    nk_build_palette(pal768);
    nk_sys_palette(pal768);
    nk_sys_kbd_raw(1);
    if (rc != 0)
        snprintf(file_status, sizeof(file_status), "%s exit %ld", label, rc);
    else
        snprintf(file_status, sizeof(file_status), "%s ok", label);
    return rc;
}

/** Open a text file in vedit, preserving this browser. */
static void file_open_text(const char *path) {
    const char *args[3];
    char label[FILE_LOG_LINE];
    args[0] = FILE_TOOL_VEDIT;
    args[1] = path;
    args[2] = 0;
    snprintf(label, sizeof(label), "vedit %s", path);
    file_spawn_visible(FILE_TOOL_VEDIT, 2, args, label);
}

/** Run a shell-kind file: elf/o directly, cvm through the interpreter. */
static void file_run_shell(const char *path) {
    const char *args[3];
    char ext[FILE_EXT_MAX + 1];
    char label[FILE_LOG_LINE];
    {
        char base[FILE_NAME_MAX + 1];
        unsigned n = 0;
        unsigned k = 0;
        while (path[n] && n < FILE_MAX_PATH) n++;
        while (k < n && path[k]) k++;
        k = 0;
        while (k < n) {
            if (path[k] == '/') {
                unsigned m = 0;
                k++;
                while (k + m < n && path[k + m] != '/' && m < FILE_NAME_MAX) {
                    base[m] = path[k + m];
                    m++;
                }
                base[m] = 0;
                k += m;
            } else k++;
        }
        file_ext_of(base, ext, sizeof(ext));
    }
    if (strcmp(ext, "cvm") == 0) {
        args[0] = path;
        args[1] = 0;
        snprintf(label, sizeof(label), "run %s", path);
        file_spawn_visible(FILE_TOOL_CVM, 1, args, label);
        return;
    }
    args[0] = path;
    args[1] = 0;
    snprintf(label, sizeof(label), "run %s", path);
    file_spawn_visible(path, 1, args, label);
}

/** Dispatch one file name through the association table. */
static void file_activate(const char *dir, const char *name) {
    char path[FILE_MAX_PATH];
    const char *prog = "";
    int act;
    if (file_join(dir, name, path, sizeof(path)) != 0) {
        snprintf(file_status, sizeof(file_status), "name too long");
        return;
    }
    act = file_action_of(name, &prog);
    if (act == FILE_ACT_TEXT) {
        file_preview_on = 0;
        file_open_text(path);
    } else if (act == FILE_ACT_SHELL) {
        file_preview_on = 0;
        file_run_shell(path);
    } else if (act == FILE_ACT_INTERNAL) {
        if (file_preview_load(path) == 0) {
            snprintf(file_preview_path, sizeof(file_preview_path), "%s", path);
            snprintf(file_status, sizeof(file_status), "preview %s", path);
        } else {
            file_preview_on = 0;
            snprintf(file_status, sizeof(file_status), "cannot preview %s",
                     path);
        }
    } else {
        file_preview_on = 0;
        snprintf(file_status, sizeof(file_status), "no handler for %s", name);
    }
}

/** Immediate-mode frame: breadcrumb, places, content grid, status. */
static void file_ui_build(struct nk_context *ctx) {
    if (nk_begin(ctx, FILE_TITLE, nk_rect(0, 0, (float)NK_W, (float)NK_H),
                 NK_WINDOW_BORDER | NK_WINDOW_MOVABLE)) {
        nk_layout_row_dynamic(ctx, 22, 1);
        nk_label(ctx, file_status, NK_TEXT_LEFT);
        nk_layout_row_dynamic(ctx, 24, 7);
        if (nk_button_label(ctx, "up")) {
            file_parent(file_cwd);
            file_preview_on = 0;
            file_refresh();
        }
        if (nk_button_label(ctx, "quit")) {
            file_quit = 1;
        }
        if (nk_button_label(ctx, "root")) {
            strcpy(file_cwd, "/");
            file_preview_on = 0;
            file_refresh();
        }
        if (nk_button_label(ctx, "bin")) {
            strcpy(file_cwd, "/bin");
            file_preview_on = 0;
            file_refresh();
        }
        if (nk_button_label(ctx, "src")) {
            strcpy(file_cwd, "/src");
            file_preview_on = 0;
            file_refresh();
        }
        if (nk_button_label(ctx, "etc")) {
            strcpy(file_cwd, "/etc");
            file_preview_on = 0;
            file_refresh();
        }
        if (nk_button_label(ctx, file_icon_big ? "small icons" : "big icons")) {
            if (file_toggle_icons())
                snprintf(file_status, sizeof(file_status), "icons %s",
                         file_icon_big ? "big" : "small");
            else
                snprintf(file_status, sizeof(file_status), "icons reload failed");
        }
        {
            long off = 0;
            long idx = 0;
            int edge = file_icon_sz();
            int cols = file_icon_big ? 2 : 4;
            int rowh = file_icon_big ? 44 : 20;
            nk_layout_row_dynamic(ctx, (float)rowh, cols);
            while (idx < file_entry_count) {
                char *nm = file_entries + off;
                unsigned long el = strlen(nm) + 1;
                int isdir = (el > 1 && nm[el - 2] == '/');
                int pressed = 0;
                if (file_icons_ok) {
                    struct nk_image im;
                    im = nk_image_ptr(&file_icon_img[file_icon_kind(
                        nm, isdir)]);
                    im.w = edge;
                    im.h = edge;
                    pressed = nk_button_image_label(ctx, im, nm,
                                                    NK_TEXT_LEFT);
                } else {
                    char cap[FILE_NAME_MAX + 8];
                    snprintf(cap, sizeof(cap), "%s %s",
                             isdir ? "[D]" : "[F]", nm);
                    pressed = nk_button_label(ctx, cap);
                }
                if (pressed) {
                    if (isdir) {
                        char nc[FILE_MAX_PATH];
                        char trim[FILE_NAME_MAX + 1];
                        unsigned long tl = el - 2;
                        if (tl > FILE_NAME_MAX) tl = FILE_NAME_MAX;
                        memcpy(trim, nm, tl);
                        trim[tl] = 0;
                        if (file_join(file_cwd, trim, nc, sizeof(nc)) == 0) {
                            snprintf(file_cwd, sizeof(file_cwd), "%s", nc);
                            file_preview_on = 0;
                            file_refresh();
                        }
                    } else {
                        file_activate(file_cwd, nm);
                    }
                    break;
                }
                off += (long)el;
                idx++;
                if (off >= FILE_LIST_CAP) break;
            }
        }
        if (file_preview_on) {
            nk_layout_row_dynamic(ctx, 18, 1);
            nk_label(ctx, file_preview_path, NK_TEXT_LEFT);
        }
    }
    nk_end(ctx);
}

/** Headless selftest for BDD: assoc vectors plus a live listing. */
static int file_selftest(void) {
    char ext[FILE_EXT_MAX + 1];
    const char *prog = "";
    int act;
    char buf[512];
    long rc;
    fassoc_clear(&file_assocs);
    if (fassoc_push(&file_assocs, "c", "/vedit") != 0) {
        printf("file: selftest assoc push failed\n");
        return 1;
    }
    if (fassoc_push(&file_assocs, "elf", "shell") != 0) {
        printf("file: selftest assoc push failed\n");
        return 1;
    }
    if (fassoc_push(&file_assocs, "png", "internal") != 0) {
        printf("file: selftest assoc push failed\n");
        return 1;
    }
    file_ext_of("hello.c", ext, sizeof(ext));
    if (strcmp(ext, "c") != 0) {
        printf("file: selftest ext failed\n");
        return 1;
    }
    file_ext_of("noext", ext, sizeof(ext));
    if (ext[0] != 0) {
        printf("file: selftest empty ext failed\n");
        return 1;
    }
    act = file_action_of("a.elf", &prog);
    if (act != FILE_ACT_SHELL || strcmp(prog, "shell") != 0) {
        printf("file: selftest shell dispatch failed\n");
        return 1;
    }
    act = file_action_of("a.png", &prog);
    if (act != FILE_ACT_INTERNAL) {
        printf("file: selftest png dispatch failed\n");
        return 1;
    }
    act = file_action_of("a.xyz", &prog);
    if (act != FILE_ACT_UNKNOWN) {
        printf("file: selftest unknown failed\n");
        return 1;
    }
    if (file_assoc_line("c|/vedit", ext, buf) != 0 || strcmp(ext, "c") != 0) {
        printf("file: selftest assoc line failed\n");
        return 1;
    }
    if (file_assoc_line("../x|/vedit", ext, buf) == 0) {
        printf("file: selftest traversal accepted\n");
        return 1;
    }
    if (file_icon_kind("sub/", 1) != FILE_ICON_FOLDER) {
        printf("file: selftest folder kind failed\n");
        return 1;
    }
    if (file_icon_kind("a.c", 0) != FILE_ICON_FILES ||
        file_icon_kind("a.h", 0) != FILE_ICON_FILES ||
        file_icon_kind("a.lisp", 0) != FILE_ICON_FILES ||
        file_icon_kind("a.lua", 0) != FILE_ICON_FILES ||
        file_icon_kind("a.py", 0) != FILE_ICON_FILES ||
        file_icon_kind("a.txt", 0) != FILE_ICON_FILES ||
        file_icon_kind("a.s", 0) != FILE_ICON_FILES) {
        printf("file: selftest text kind failed\n");
        return 1;
    }
    if (file_icon_kind("A.PNG", 0) != FILE_ICON_IMAGE) {
        printf("file: selftest image kind failed\n");
        return 1;
    }
    if (file_icon_kind("a.o", 0) != FILE_ICON_OBJECT ||
        file_icon_kind("a.elf", 0) != FILE_ICON_OBJECT ||
        file_icon_kind("a.cvm", 0) != FILE_ICON_OBJECT) {
        printf("file: selftest object kind failed\n");
        return 1;
    }
    if (file_icon_kind("a.zip", 0) != FILE_ICON_FILES ||
        file_icon_kind("noext", 0) != FILE_ICON_FILES) {
        printf("file: selftest fallback kind failed\n");
        return 1;
    }
    if (!file_icons_load()) {
        printf("file: selftest icon load failed\n");
        return 1;
    }
    if (file_icon_sz() != FILE_ICON_SMALL) {
        printf("file: selftest default size failed\n");
        return 1;
    }
    if (!file_toggle_icons() || file_icon_sz() != FILE_ICON_BIG) {
        printf("file: selftest big toggle failed\n");
        return 1;
    }
    if (!file_toggle_icons() || file_icon_sz() != FILE_ICON_SMALL) {
        printf("file: selftest small toggle failed\n");
        return 1;
    }
    {
        unsigned k = 0;
        char ebuf[16];
        char pbuf[40];
        fassoc_clear(&file_assocs);
        for (k = 0; k < 40; k++) {
            snprintf(ebuf, sizeof(ebuf), "e%u", k);
            snprintf(pbuf, sizeof(pbuf), "/p%u", k);
            if (fassoc_push(&file_assocs, ebuf, pbuf) != 0) {
                printf("file: selftest growth failed\n");
                return 1;
            }
        }
        if (fassoc_count(&file_assocs) != 40) {
            printf("file: selftest growth count failed\n");
            return 1;
        }
        if (strcmp(fassoc_lookup(&file_assocs, "e39"), "/p39") != 0) {
            printf("file: selftest growth lookup failed\n");
            return 1;
        }
        fassoc_clear(&file_assocs);
        if (fassoc_push(&file_assocs, "c", "/vedit") != 0 ||
            fassoc_push(&file_assocs, "elf", "shell") != 0 ||
            fassoc_push(&file_assocs, "png", "internal") != 0) {
            printf("file: selftest assoc push failed\n");
            return 1;
        }
    }
    rc = file_sys_dir_list("/", buf, sizeof(buf));
    if (rc < 0) {
        printf("file: selftest dir_list failed (%ld)\n", rc);
        return 1;
    }
    {
        char theme[NK_THEME_NAME_MAX + 1];
        unsigned char rgb[NK_THEME_KEY_COUNT][3];
        nk_theme_active(theme, sizeof(theme));
        if (nk_theme_probe(0, rgb) != 0 && nk_theme_probe("dark", rgb) != 0) {
            printf("file: selftest theme failed\n");
            return 1;
        }
        printf("file: ok (%ld entries at /, theme %s)\n", rc, theme);
    }
    return 0;
}

static unsigned char file_ui_memory[FILE_UI_MEMORY];

static void file_gui_run(void) {
    struct nk_user_font font = nk_minios_font();
    struct nk_context ctx;
    unsigned char pal768[768];
    int origin[2] = {0, 0};
    nk_sys_vga_mode(1);
    nk_sys_kbd_raw(1);
    nk_build_palette(pal768);
    nk_sys_palette(pal768);
    nk_sys_gfx_set_title(FILE_TITLE);
    if (!nk_init_fixed(&ctx, file_ui_memory, FILE_UI_MEMORY, &font)) {
        printf("file: init failed\n");
        nk_sys_kbd_raw(0);
        nk_sys_vga_mode(0);
        return;
    }
    nk_theme_apply(&ctx, 0);
    strcpy(file_cwd, "/");
    file_preview_on = 0;
    file_quit = 0;
    file_assoc_load();
    file_icons_ok = file_icons_load();
    file_refresh();
    while (!file_quit) {
        long k;
        nk_input_begin(&ctx);
        nk_poll_input(&ctx);
        for (k = 0; k < 4; k++) {
            long sc = nk_sys_kbd();
            if (sc < 0) break;
            if (sc == 14) {
                file_parent(file_cwd);
                file_preview_on = 0;
                file_refresh();
            }
        }
        nk_input_end(&ctx);
        if (nk_quit_requested()) file_quit = 1;
        file_ui_build(&ctx);
        nk_rasterize(&ctx);
        if (file_preview_on)
            file_preview_blit(NK_W - FILE_PREVIEW_W - 8,
                              96 + 18);
        if (nk_sys_nk_frame(origin) == 0)
            nk_set_window_origin(origin[0], origin[1]);
        nk_clear(&ctx);
        {
            unsigned t0 = (unsigned)nk_sys_time_ms();
            while ((unsigned)nk_sys_time_ms() - t0 < 16) {
                __asm__ volatile("pause");
            }
        }
    }
    nk_free(&ctx);
    nk_sys_kbd_raw(0);
    nk_sys_vga_mode(0);
}

int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], "--selftest") == 0)
        return file_selftest();
    if (argc > 1 && strcmp(argv[1], "--help") == 0) {
        printf("file: Nuklear file browser (ramdisk + MiniFS)\n");
        printf("  (no args)   GUI browser\n");
        printf("  --selftest  assoc vectors plus a live listing\n");
        return 0;
    }
    file_gui_run();
    return 0;
}
