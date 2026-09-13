/** Docstring: kernel/minifetch.c -- neofetch-style system screen.
 *
 * Layout is text, so it renders identically on the framebuffer window
 * and the serial console and survives scrollback and redirection. The
 * logo is not canned art: icons/doom.png is decoded at runtime and each
 * row is downsampled 2:1 vertically into a brightness ramp, so the logo
 * tracks whatever art the image pipeline ships. Every spec reuses the
 * accessor its builtin owns (mem, net, date, smp, gfx), keeping one
 * source of truth per fact.
 */

#include "kernel.h"
#include "minifetch.h"
#include "minifs.h"
#include "net.h"
#include "rtc.h"
#include "sched.h"
#include "stb_api.h"
#include "vga_fb.h"

typedef struct minifetch_cfg {
    const char *logo_path;
    int logo_cols;
    int logo_rows;
    const char *ramp;
    int spec_gap;
} minifetch_cfg_t;

static const minifetch_cfg_t mf_cfg = {
    "icons/doom.png",
    32,
    16,
    " .:-=+*#%@",
    2,
};

static const char *mf_fallback[16] = {
    "            MINI OS            ",
    "        =============         ",
    "                              ",
    "     x86_64  ring 3  SMP      ",
    "                              ",
    "       DOOM  ready.           ",
    "                              ",
    "                              ",
    "                              ",
    "                              ",
    "                              ",
    "                              ",
    "                              ",
    "                              ",
    "                              ",
    "                              ",
};

/** Docstring: Render one logo row into out from RGBA pixels. */
static void minifetch_row(const unsigned char *img, int w, int h, int row,
                          char *out) {
    int x, ramp_len = 0, c;
    while (mf_cfg.ramp[ramp_len])
        ramp_len++;
    for (x = 0; x < mf_cfg.logo_cols; x++) {
        int sx = x * w / mf_cfg.logo_cols;
        int y0 = (row * 2) * h / (mf_cfg.logo_rows * 2);
        int y1 = (row * 2 + 1) * h / (mf_cfg.logo_rows * 2);
        const unsigned char *p0 = img + ((y0 * w) + sx) * 4;
        const unsigned char *p1 = img + ((y1 * w) + sx) * 4;
        unsigned lum;
        if (p0[3] < 128 && p1[3] < 128) {
            out[x] = ' ';
            continue;
        }
        lum = (unsigned)(p0[0] + p0[1] + p0[2] + p1[0] + p1[1] + p1[2]) / 6;
        c = (int)(lum * (unsigned)(ramp_len - 1) / 255);
        out[x] = mf_cfg.ramp[c];
    }
    out[mf_cfg.logo_cols] = 0;
}

/** Docstring: Fill rows with the live logo or the fallback text. */
static void minifetch_logo(char rows[16][33]) {
    unsigned char *img = 0;
    int w = 0, h = 0, ch = 0, r, i;
    img = stbi_load_file(mf_cfg.logo_path, &w, &h, &ch, 4);
    if (!img || w <= 0 || h <= 0) {
        if (img)
            stbi_image_free(img);
        for (r = 0; r < mf_cfg.logo_rows; r++) {
            for (i = 0; i < mf_cfg.logo_cols; i++)
                rows[r][i] = mf_fallback[r][i];
            rows[r][mf_cfg.logo_cols] = 0;
        }
        return;
    }
    for (r = 0; r < mf_cfg.logo_rows; r++)
        minifetch_row(img, w, h, r, rows[r]);
    stbi_image_free(img);
}

/** Docstring: Print the spec column into lines, return line count. */
static int minifetch_specs(char lines[20][96]) {
    unsigned long hu = 0, hf = 0, ha = 0;
    unsigned ru = 0, rc = 0, rm = 0;
    unsigned char mac[6] = {0, 0, 0, 0, 0, 0};
    unsigned char ip[4] = {0, 0, 0, 0};
    int hh = 0, mm = 0, ss = 0, n = 0, i, nlive = 0;
    unsigned long up = sys_ticks / 100;
    int ok = rtc_read_tod(&hh, &mm, &ss);

    dlmalloc_usage(&hu, &hf, &ha);
    ramdisk_usage(&ru, &rc, &rm);
    net_get_addrs(mac, ip);
    spin_lock(&sched_lock);
    for (i = 0; i < MAX_PROCS; i++)
        if (procs[i].state != PROC_FREE)
            nlive++;
    spin_unlock(&sched_lock);

    ksprintf(lines[n++], "user@minios");
    ksprintf(lines[n++], "----------------");
    ksprintf(lines[n++], "OS: MiniOS x86_64 ABI v%d", MINIOS_ABI_VERSION);
    ksprintf(lines[n++], "Kernel: v0.3 ring0 + ring3 isolated ELFs");
    if (up < 60)
        ksprintf(lines[n++], "Uptime: %lus", up);
    else if (up < 3600)
        ksprintf(lines[n++], "Uptime: %lum %lus", up / 60, up % 60);
    else
        ksprintf(lines[n++], "Uptime: %luh %lum", up / 3600, (up / 60) % 60);
    ksprintf(lines[n++], "CPU: %d x86_64 (%s)", cpu_count,
             cpu_count > 1 ? "SMP" : "single");
    ksprintf(lines[n++], "Procs: %d/%d live", nlive, MAX_PROCS);
    ksprintf(lines[n++], "Memory: heap %luK/%luK", hu / 1024,
             (hu + hf) / 1024);
    ksprintf(lines[n++], "Disk: ramdisk %uK/%uK", ru / 1024, rc / 1024);
    if (minifs_is_mounted()) {
        unsigned int fb = 0, tb = 0, fi = 0, ti = 0;
        minifs_usage(&fb, &tb, &fi, &ti);
        ksprintf(lines[n++], "MiniFS: %u/%u blocks free", fb, tb);
    } else {
        ksprintf(lines[n++], "MiniFS: not mounted");
    }
    ksprintf(lines[n++], "Display: %dx%dx%d", fb_width, fb_height, fb_bpp);
    ksprintf(lines[n++], "Net: %02x:%02x:%02x:%02x:%02x:%02x %u.%u.%u.%u",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5],
             ip[0], ip[1], ip[2], ip[3]);
    if (ok)
        ksprintf(lines[n++], "Date: %02d:%02d:%02d CMOS", hh, mm, ss);
    else
        ksprintf(lines[n++], "Date: unavailable");
    ksprintf(lines[n++], "Toolchain: minigcc.o + ld.o + cvm.o");
    ksprintf(lines[n++], "Shell: minios sh + lua + micropython");
    return n;
}

/** Docstring: Print the two-column fetch screen. */
void shell_cmd_minifetch(void) {
    char logo[16][33];
    char specs[20][96];
    int nspecs, r, g, i;
    char line[160];
    minifetch_logo(logo);
    nspecs = minifetch_specs(specs);
    for (r = 0; r < mf_cfg.logo_rows || r < nspecs; r++) {
        const char *left = r < mf_cfg.logo_rows ? logo[r] : 0;
        const char *right = r < nspecs ? specs[r] : 0;
        int p = 0;
        if (left) {
            for (i = 0; left[i] && p < (int)sizeof(line) - 1; i++)
                line[p++] = left[i];
            while (i++ < mf_cfg.logo_cols && p < (int)sizeof(line) - 1)
                line[p++] = ' ';
        } else {
            for (i = 0; i < mf_cfg.logo_cols && p < (int)sizeof(line) - 1; i++)
                line[p++] = ' ';
        }
        for (g = 0; g < mf_cfg.spec_gap && p < (int)sizeof(line) - 1; g++)
            line[p++] = ' ';
        if (right) {
            for (i = 0; right[i] && p < (int)sizeof(line) - 1; i++)
                line[p++] = right[i];
        }
        line[p++] = '\n';
        line[p] = 0;
        vga_puts(line);
    }
}
