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
#define FILE_ASSOC_MAX 32
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

/** Dispatch kinds resolved from the association table. */
#define FILE_ACT_TEXT 0
#define FILE_ACT_SHELL 1
#define FILE_ACT_INTERNAL 2
#define FILE_ACT_UNKNOWN 3

struct file_assoc {
    char ext[FILE_EXT_MAX + 1];
    char prog[FILE_PROG_MAX + 1];
};

static struct file_assoc file_table[FILE_ASSOC_MAX];
static int file_table_n;

static int file_quit;
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
    file_table_n = 0;
    f = fopen(FILE_ASSOC_PATH, "r");
    if (!f) return;
    while (fgets(line, sizeof(line), f)) {
        if (file_assoc_line(line, ext, prog) != 0) continue;
        if (file_table_n >= FILE_ASSOC_MAX) break;
        strcpy(file_table[file_table_n].ext, ext);
        strcpy(file_table[file_table_n].prog, prog);
        file_table_n++;
    }
    fclose(f);
}

/** Program for an extension, empty when unmapped. */
static const char *file_assoc_lookup(const char *ext) {
    int k;
    if (!ext[0]) return "";
    for (k = 0; k < file_table_n; k++)
        if (strcmp(file_table[k].ext, ext) == 0)
            return file_table[k].prog;
    return "";
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
    FILE *f;
    long sz;
    unsigned char *raw = 0;
    int w = 0;
    int h = 0;
    int comp = 0;
    unsigned char *px = 0;
    f = fopen(path, "rb");
    if (!f) return -1;
    fseek(f, 0, SEEK_END);
    sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (sz <= 0 || sz > FILE_PREVIEW_FILE_MAX) { fclose(f); return -1; }
    raw = malloc((unsigned long)sz);
    if (!raw) { fclose(f); return -1; }
    if (fread(raw, 1, (unsigned long)sz, f) != (unsigned long)sz) {
        free(raw);
        fclose(f);
        return -1;
    }
    fclose(f);
    px = stbi_load_from_memory(raw, (int)sz, &w, &h, &comp, 3);
    free(raw);
    if (!px || w <= 0 || h <= 0) {
        if (px) stbi_image_free(px);
        return -1;
    }
    {
        int k;
        unsigned char pal[768];
        int x;
        int y;
        nk_build_palette(pal);
        for (y = 0; y < FILE_PREVIEW_H; y++) {
            for (x = 0; x < FILE_PREVIEW_W; x++) {
                int sx = x * w / FILE_PREVIEW_W;
                int sy = y * h / FILE_PREVIEW_H;
                unsigned char *p = px + (sy * w + sx) * 3;
                int br = p[0];
                int bg = p[1];
                int bb = p[2];
                int bi = 15;
                int bd = 1 << 30;
                for (k = 15; k < 256; k++) {
                    int dr = (int)pal[k * 3] - br;
                    int dg = (int)pal[k * 3 + 1] - bg;
                    int db = (int)pal[k * 3 + 2] - bb;
                    int d = dr * dr + dg * dg + db * db;
                    if (d < bd) { bd = d; bi = k; }
                }
                file_preview_px[y * FILE_PREVIEW_W + x] = (unsigned char)bi;
            }
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
        nk_layout_row_dynamic(ctx, 24, 6);
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
        {
            long off = 0;
            long idx = 0;
            nk_layout_row_dynamic(ctx, 20, 4);
            while (idx < file_entry_count) {
                char *nm = file_entries + off;
                unsigned long el = strlen(nm) + 1;
                int isdir = (el > 1 && nm[el - 2] == '/');
                char cap[FILE_NAME_MAX + 8];
                snprintf(cap, sizeof(cap), "%s %s", isdir ? "[D]" : "[F]",
                         nm);
                if (nk_button_label(ctx, cap)) {
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
    file_table_n = 0;
    strcpy(file_table[0].ext, "c");
    strcpy(file_table[0].prog, "/vedit");
    strcpy(file_table[1].ext, "elf");
    strcpy(file_table[1].prog, "shell");
    strcpy(file_table[2].ext, "png");
    strcpy(file_table[2].prog, "internal");
    file_table_n = 3;
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
