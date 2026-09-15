/** wlcomp - Wayland-mini ring-3 compositor (ADR-0024).
 *
 * Owns up to WL_MAX_SURFACES client surfaces, orders them by focus
 * (z-order), and presents through the existing kernel compositor
 * (GFX_PRESENT BUF_NK) so no kernel change is needed in Phase 1.
 *
 * Guest: wlcomp --selftest runs the pure state machine (no display
 * touch, safe anywhere) and prints wlcomp: frame ok (800x360).
 * Guest: wlcomp builds a two-surface demo, software-composites it
 * with wlcomp_render into the NK back-buffer, titles the window and
 * presents it, so the desktop visibly gains a second client beside
 * the terminal. The existing gfx frames counter proves composition.
 *
 * Host test: tests/test_wl.c covers wl_mini.h (wire, state, render);
 * this file only wires the compositor state to syscalls and stays thin.
 */

#include <stdio.h>
#include <string.h>

#include "minios_abi.h"
#include "wl_mini.h"

#define WLCOMP_W 800
#define WLCOMP_H 360

static long wlcomp_sys_title(const char *t) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret)
        : "a"(MINIOS_SYS_GFX_SET_TITLE), "D"(t)
        : "rcx", "r11", "memory");
    return ret;
}

static long wlcomp_sys_present(long buf) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret)
        : "a"(MINIOS_SYS_GFX_PRESENT), "D"(buf), "S"(0L)
        : "rcx", "r11", "memory");
    return ret;
}

static int wlcomp_demo(wl_comp_t *c) {
    wl_client_t cl;
    unsigned int s0 = 0;
    unsigned int s1 = 0;
    wl_client_init(&cl);
    if (wl_client_surface(&cl, &s0) != WL_ERR_OK)
        return 1;
    if (wl_client_surface(&cl, &s1) != WL_ERR_OK)
        return 1;
    if (wl_comp_add(c, s0, 320, 200) != WL_ERR_OK)
        return 1;
    if (wl_comp_add(c, s1, 400, 180) != WL_ERR_OK)
        return 1;
    c->items[0].x = 40;
    c->items[0].y = 40;
    if (wl_comp_set_color(c, s0, 4) != WL_ERR_OK)
        return 1;
    c->items[1].x = 240;
    c->items[1].y = 100;
    if (wl_comp_set_color(c, s1, 6) != WL_ERR_OK)
        return 1;
    if (wl_comp_focus(c, s0) != WL_ERR_OK)
        return 1;
    return 0;
}

static int wlcomp_selftest(void) {
    wl_comp_t c;
    wl_client_t cl;
    unsigned char fb[16 * 10];
    unsigned int s0 = 0;
    unsigned int s1 = 0;
    int hit;

    wl_comp_init(&c);
    wl_client_init(&cl);
    if (wl_client_surface(&cl, &s0) != WL_ERR_OK)
        return 1;
    if (wl_client_surface(&cl, &s1) != WL_ERR_OK)
        return 1;
    if (wl_comp_add(&c, s0, 320, 200) != WL_ERR_OK)
        return 1;
    if (wl_comp_add(&c, s1, 800, 360) != WL_ERR_OK)
        return 1;
    c.items[1].x = 0;
    c.items[1].y = 0;
    if (wl_comp_focus(&c, s0) != WL_ERR_OK)
        return 1;
    hit = wl_comp_hit(&c, 10, 10);
    if (hit != (int)s0)
        return 1;
    if (wlcomp_render(&c, fb, 16, 10) != WL_ERR_OK)
        return 1;
    if (fb[0] == WLCOMP_BG)
        return 1;
    if (wl_comp_remove(&c, s1) != WL_ERR_OK)
        return 1;
    if (c.count != 1)
        return 1;
    printf("wlcomp: frame ok (%dx%d)\n", WLCOMP_W, WLCOMP_H);
    return 0;
}

int main(int argc, char **argv) {
    if (argc == 2 && strcmp(argv[1], "--selftest") == 0)
        return wlcomp_selftest();
    {
        wl_comp_t c;
        unsigned char *fb = (unsigned char *)MINIOS_NK_BACKBUF_ADDR;
        wl_comp_init(&c);
        if (wlcomp_demo(&c) != 0) {
            printf("wlcomp: demo setup failed\n");
            return 1;
        }
        if (wlcomp_render(&c, fb, WLCOMP_W, WLCOMP_H) != WL_ERR_OK) {
            printf("wlcomp: render failed\n");
            return 1;
        }
        wlcomp_sys_title("wlcomp");
        wlcomp_sys_present((long)MINIOS_GFX_BUF_NK);
        printf("wlcomp: presented 2 surfaces (%dx%d)\n", WLCOMP_W, WLCOMP_H);
        return 0;
    }
}
