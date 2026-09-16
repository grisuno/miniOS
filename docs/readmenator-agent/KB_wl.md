# Subsystem: wl

## progs/wl/wl_mini.h
- Layer: utility
- Doc: wl_mini.h - Wayland-mini subset contract (header-only, ADR-0024).
- Language: h
- Symbols:
  - `wl_hdr_t` (struct, line 52)
  - `wl_cfg_t` (struct, line 58)
  - `wl_surface_t` (struct, line 232)
  - `wl_comp_t` (struct, line 243)
  - `wl_client_t` (struct, line 419)
  - `wl_hdr_encode` (function, line 65) `static inline int wl_hdr_encode(unsigned char *dst, int cap,
        unsigned int id, unsigned in...`
  - `wl_hdr_decode` (function, line 97) `static inline int wl_hdr_decode(const unsigned char *src, int len,
        wl_hdr_t *out)`
  - `wl_u32_encode` (function, line 126) `static inline int wl_u32_encode(unsigned char *dst, int cap, int off,
        unsigned int v)`
  - `wl_u32_decode` (function, line 137) `static inline int wl_u32_decode(const unsigned char *src, int len, int off,
        unsigned int *v)`
  - `wl_strlen_bounded` (function, line 148) `static inline int wl_strlen_bounded(const char *s)`
  - `wl_str_encode` (function, line 162) `static inline int wl_str_encode(unsigned char *dst, int cap, int off,
        const char *s)`
  - `wl_str_decode` (function, line 186) `static inline int wl_str_decode(const unsigned char *src, int len, int off,
        char *dst, in...`
  - `wl_surface_id_valid` (function, line 212) `static inline int wl_surface_id_valid(unsigned int id)`
  - `wl_pool_id_valid` (function, line 217) `static inline int wl_pool_id_valid(unsigned int id)`
  - `wl_pool_fit` (function, line 221) `static inline int wl_pool_fit(int w, int h)`
  - `wl_comp_init` (function, line 249) `static inline void wl_comp_init(wl_comp_t *c)`
  - `wl_comp_add` (function, line 262) `static inline int wl_comp_add(wl_comp_t *c, unsigned int id, int w, int h)`
  - `wl_comp_remove` (function, line 295) `static inline int wl_comp_remove(wl_comp_t *c, unsigned int id)`
  - `wl_comp_focus` (function, line 321) `static inline int wl_comp_focus(wl_comp_t *c, unsigned int id)`
  - `wl_comp_hit` (function, line 345) `static inline int wl_comp_hit(const wl_comp_t *c, int x, int y)`
  - `wl_comp_set_color` (function, line 358) `static inline int wl_comp_set_color(wl_comp_t *c, unsigned int id, int color)`
  - `wlcomp_render` (function, line 383) `static inline int wlcomp_render(const wl_comp_t *c, unsigned char *fb,
        int fb_w, int fb_h)`
  - `wl_client_init` (function, line 424) `static inline void wl_client_init(wl_client_t *cl)`
  - `wl_client_surface` (function, line 432) `static inline int wl_client_surface(wl_client_t *cl, unsigned int *id)`
  - `wl_client_pool` (function, line 441) `static inline int wl_client_pool(wl_client_t *cl, unsigned int *id)`
  - `WL_MINI_H` (macro, line 18) `#define WL_MINI_H`
  - `WL_MAX_MSG` (macro, line 19) `#define WL_MAX_MSG`
  - `WL_MAX_STR` (macro, line 21) `#define WL_MAX_STR`
  - `WL_MAX_SURFACES` (macro, line 22) `#define WL_MAX_SURFACES`
  - `WL_MAX_POOLS` (macro, line 23) `#define WL_MAX_POOLS`
  - `WL_POOL_MAX` (macro, line 24) `#define WL_POOL_MAX`
  - `WL_HDR_SZ` (macro, line 25) `#define WL_HDR_SZ`
  - `WL_ERR_OK` (macro, line 26) `#define WL_ERR_OK`
  - `WL_ERR_BOUND` (macro, line 28) `#define WL_ERR_BOUND`
  - `WL_ERR_TRUNC` (macro, line 29) `#define WL_ERR_TRUNC`
  - `WL_ERR_SIZE` (macro, line 30) `#define WL_ERR_SIZE`
  - `WL_ERR_ID` (macro, line 31) `#define WL_ERR_ID`
  - `WL_ERR_STR` (macro, line 32) `#define WL_ERR_STR`
  - `WL_ID_DISPLAY` (macro, line 33) `#define WL_ID_DISPLAY`
  - `WL_ID_REGISTRY` (macro, line 35) `#define WL_ID_REGISTRY`
  - `WL_ID_COMPOSITOR` (macro, line 36) `#define WL_ID_COMPOSITOR`
  - `WL_ID_SHM` (macro, line 37) `#define WL_ID_SHM`
  - `WL_ID_XDG_BASE` (macro, line 38) `#define WL_ID_XDG_BASE`
  - `WL_ID_SURFACE_BASE` (macro, line 39) `#define WL_ID_SURFACE_BASE`
  - `WL_ID_POOL_BASE` (macro, line 40) `#define WL_ID_POOL_BASE`
  - `WL_ID_BUFFER_BASE` (macro, line 41) `#define WL_ID_BUFFER_BASE`
  - `WL_OP_DISPLAY_GET_REGISTRY` (macro, line 42) `#define WL_OP_DISPLAY_GET_REGISTRY`
  - `WL_OP_REGISTRY_BIND` (macro, line 44) `#define WL_OP_REGISTRY_BIND`
  - `WL_OP_COMPOSITOR_CREATE_SURFACE` (macro, line 45) `#define WL_OP_COMPOSITOR_CREATE_SURFACE`
  - `WL_OP_SHM_CREATE_POOL` (macro, line 46) `#define WL_OP_SHM_CREATE_POOL`
  - `WL_OP_POOL_CREATE_BUFFER` (macro, line 47) `#define WL_OP_POOL_CREATE_BUFFER`
  - `WL_OP_SURFACE_ATTACH` (macro, line 48) `#define WL_OP_SURFACE_ATTACH`
  - `WL_OP_SURFACE_COMMIT` (macro, line 49) `#define WL_OP_SURFACE_COMMIT`
  - `WL_OP_XDG_GET_TOPLEVEL` (macro, line 50) `#define WL_OP_XDG_GET_TOPLEVEL`
  - `WL_CFG_DEFAULT` (macro, line 63) `#define WL_CFG_DEFAULT`
  - `WLCOMP_BG` (macro, line 381) `#define WLCOMP_BG`
  - `WLCOMP_BORDER` (macro, line 382) `#define WLCOMP_BORDER`
- Imported by: `progs/src/freedom_wl.c`, `progs/wl/wlcomp.c`, `tests/test_wl.c`

## progs/wl/wlcomp.c
- Layer: utility
- Doc: wlcomp - Wayland-mini ring-3 compositor (ADR-0024).
- Language: c
- Symbols:
  - `wlcomp_sys_title` (function, line 26) `static long wlcomp_sys_title(const char *t)`
  - `wlcomp_sys_present` (function, line 34) `static long wlcomp_sys_present(long buf)`
  - `wlcomp_demo` (function, line 42) `static int wlcomp_demo(wl_comp_t *c)`
  - `wlcomp_selftest` (function, line 68) `static int wlcomp_selftest(void)`
  - `main` (function, line 105) `int main(int argc, char **argv)`
  - `volatile` (function, line 29) `__asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_GFX_SET_TITLE), "D"(t) : "rcx", "r11", "memory");`
  - `wl_client_init` (function, line 47) `wl_client_init(&cl);`
  - `wl_comp_init` (function, line 76) `wl_comp_init(&c);`
  - `printf` (function, line 102) `printf("wlcomp: frame ok (%dx%d)\n", WLCOMP_W, WLCOMP_H);`
  - `WLCOMP_W` (macro, line 23) `#define WLCOMP_W`
  - `WLCOMP_H` (macro, line 25) `#define WLCOMP_H`
- Depends on: `kernel/string.c`, `progs/minios_abi.h`, `progs/wl/wl_mini.h`
