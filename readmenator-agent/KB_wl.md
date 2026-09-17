# Subsystem: wl

## progs/wl/wl_client.h
- Layer: infrastructure
- Doc: wl_client.h - Thin mailbox client for Wayland-mini (ADR-0026).
- Language: h
- Symbols:
  - `wl_client_emit_file` (function, line 21) `static inline int wl_client_emit_file(const char *box, unsigned int seq,
        const unsigned c...`
  - `wl_client_raw_file` (function, line 48) `static inline int wl_client_raw_file(const char *box,
        const unsigned char *px, int w, int h)`
  - `wl_client_attach` (function, line 75) `static inline int wl_client_attach(const char *box, unsigned int seq0,
        const unsigned cha...`
  - `WL_CLIENT_H` (macro, line 14) `#define WL_CLIENT_H`
  - `WL_CLIENT_MSGS` (macro, line 17) `#define WL_CLIENT_MSGS`
- Depends on: `progs/wl/wl_mbox.h`
- Imported by: `progs/nuklear/nuklear_minios.c`, `progs/wl/wlcomp.c`

## progs/wl/wl_mbox.h
- Layer: utility
- Doc: wl_mbox.h - Mailbox file transport for Wayland-mini (ADR-0026).
- Language: h
- Symbols:
  - `wl_mbox_box_t` (struct, line 30)
  - `wl_mbox_init` (function, line 36) `static inline void wl_mbox_init(wl_mbox_box_t *boxes)`
  - `wl_mbox_box_ok` (function, line 51) `static inline int wl_mbox_box_ok(const char *box)`
  - `wl_mbox_hex` (function, line 74) `static inline int wl_mbox_hex(unsigned int v, char *dst)`
  - `wl_mbox_unhex` (function, line 87) `static inline int wl_mbox_unhex(char ch, unsigned int *v)`
  - `wl_mbox_name` (function, line 103) `static inline int wl_mbox_name(char *dst, int cap, const char *box,
        unsigned int seq)`
  - `wl_mbox_parse` (function, line 147) `static inline int wl_mbox_parse(const char *path, char *box, int boxcap,
        unsigned int *seq)`
  - `wl_mbox_raw_name` (function, line 194) `static inline int wl_mbox_raw_name(char *dst, int cap, const char *box)`
  - `wl_mbox_ev_name` (function, line 225) `static inline int wl_mbox_ev_name(char *dst, int cap, const char *box)`
  - `wl_client_box` (function, line 257) `static inline int wl_client_box(const char *prog, long pid, char *dst,
        int cap)`
  - `wl_mbox_frame_encode` (function, line 310) `static inline int wl_mbox_frame_encode(unsigned char *dst, int cap,
        unsigned int seq, con...`
  - `wl_mbox_frame_decode` (function, line 332) `static inline int wl_mbox_frame_decode(const unsigned char *src, int len,
        unsigned int *s...`
  - `wl_mbox_assign` (function, line 358) `static inline int wl_mbox_assign(wl_mbox_box_t *boxes, const char *box)`
  - `wl_mbox_fresh` (function, line 394) `static inline int wl_mbox_fresh(const wl_mbox_box_t *boxes, int slot,
        unsigned int seq)`
  - `wl_mbox_route` (function, line 409) `static inline int wl_mbox_route(wl_comp_t *c, wl_mbox_box_t *boxes,
        const char *box, unsi...`
  - `WL_MBOX_H` (macro, line 15) `#define WL_MBOX_H`
  - `WL_MBOX_DIR` (macro, line 18) `#define WL_MBOX_DIR`
  - `WL_MBOX_SUFFIX` (macro, line 20) `#define WL_MBOX_SUFFIX`
  - `WL_MBOX_RAW_SUFFIX` (macro, line 21) `#define WL_MBOX_RAW_SUFFIX`
  - `WL_MBOX_EV_SUFFIX` (macro, line 22) `#define WL_MBOX_EV_SUFFIX`
  - `WL_MBOX_BOX_MAX` (macro, line 23) `#define WL_MBOX_BOX_MAX`
  - `WL_MBOX_NAME_MAX` (macro, line 24) `#define WL_MBOX_NAME_MAX`
  - `WL_MBOX_MAGIC` (macro, line 25) `#define WL_MBOX_MAGIC`
  - `WL_MBOX_FRAME_HEAD` (macro, line 26) `#define WL_MBOX_FRAME_HEAD`
  - `WL_MBOX_POLL_MAX` (macro, line 27) `#define WL_MBOX_POLL_MAX`
  - `WL_MBOX_SEQ_HEX` (macro, line 28) `#define WL_MBOX_SEQ_HEX`
- Depends on: `progs/wl/wl_mini.h`
- Imported by: `progs/nuklear/nuklear_minios.c`, `progs/wl/wl_client.h`, `progs/wl/wlcomp.c`, `tests/test_wl.c`

## progs/wl/wl_mini.h
- Layer: utility
- Doc: wl_mini.h - Wayland-mini subset contract (header-only, ADR-0024).
- Language: h
- Symbols:
  - `wl_hdr_t` (struct, line 57)
  - `wl_cfg_t` (struct, line 63)
  - `wl_surface_t` (struct, line 251)
  - `wl_comp_t` (struct, line 264)
  - `wl_ev_t` (struct, line 860)
  - `wl_client_t` (struct, line 978)
  - `wl_stream_t` (struct, line 1016)
  - `wl_iface_t` (struct, line 1071)
  - `wl_hdr_encode` (function, line 71) `static inline int wl_hdr_encode(unsigned char *dst, int cap,
        unsigned int id, unsigned in...`
  - `wl_hdr_decode` (function, line 99) `static inline int wl_hdr_decode(const unsigned char *src, int len,
        wl_hdr_t *out)`
  - `wl_u32_encode` (function, line 128) `static inline int wl_u32_encode(unsigned char *dst, int cap, int off,
        unsigned int v)`
  - `wl_u32_decode` (function, line 139) `static inline int wl_u32_decode(const unsigned char *src, int len, int off,
        unsigned int *v)`
  - `wl_strlen_bounded` (function, line 150) `static inline int wl_strlen_bounded(const char *s)`
  - `wl_str_encode` (function, line 163) `static inline int wl_str_encode(unsigned char *dst, int cap, int off,
        const char *s)`
  - `wl_str_decode` (function, line 188) `static inline int wl_str_decode(const unsigned char *src, int len, int off,
        char *dst, in...`
  - `wl_surface_id_valid` (function, line 214) `static inline int wl_surface_id_valid(unsigned int id)`
  - `wl_pool_id_valid` (function, line 219) `static inline int wl_pool_id_valid(unsigned int id)`
  - `wl_pool_fit` (function, line 223) `static inline int wl_pool_fit(int w, int h)`
  - `wl_comp_init` (function, line 271) `static inline void wl_comp_init(wl_comp_t *c)`
  - `wl_comp_refresh_active` (function, line 289) `static inline void wl_comp_refresh_active(wl_comp_t *c)`
  - `wl_comp_add` (function, line 309) `static inline int wl_comp_add(wl_comp_t *c, unsigned int id, int w, int h)`
  - `wl_comp_remove` (function, line 345) `static inline int wl_comp_remove(wl_comp_t *c, unsigned int id)`
  - `wl_comp_focus` (function, line 372) `static inline int wl_comp_focus(wl_comp_t *c, unsigned int id)`
  - `wl_comp_hit` (function, line 397) `static inline int wl_comp_hit(const wl_comp_t *c, int x, int y)`
  - `wl_surface_hit_zone` (function, line 415) `static inline int wl_surface_hit_zone(const wl_surface_t *s, int x, int y)`
  - `wl_comp_set_minimized` (function, line 441) `static inline int wl_comp_set_minimized(wl_comp_t *c, unsigned int id,
        int minimized)`
  - `wl_comp_set_color` (function, line 456) `static inline int wl_comp_set_color(wl_comp_t *c, unsigned int id, int color)`
  - `wlcomp_render` (function, line 481) `static inline int wlcomp_render(const wl_comp_t *c, unsigned char *fb,
        int fb_w, int fb_h)`
  - `wl_comp_set_rect` (function, line 519) `static inline int wl_comp_set_rect(wl_comp_t *c, unsigned int id,
        int x, int y, int w, in...`
  - `wl_comp_layout_tile` (function, line 546) `static inline int wl_comp_layout_tile(wl_comp_t *c, int fb_w, int fb_h)`
  - `wlcomp_blit` (function, line 606) `static inline int wlcomp_blit(const wl_comp_t *c, unsigned char *fb,
        int fb_w, int fb_h, ...`
  - `wlcomp_blit_chrome` (function, line 669) `static inline int wlcomp_blit_chrome(const wl_comp_t *c, unsigned char *fb,
        int fb_w, int...`
  - `wl_scale_nearest` (function, line 744) `static inline int wl_scale_nearest(unsigned char *dst, int dw, int dh,
        const unsigned cha...`
  - `wl_attach_encode` (function, line 774) `static inline int wl_attach_encode(unsigned char *dst, int cap,
        unsigned int pool, int w,...`
  - `wl_attach_decode` (function, line 793) `static inline int wl_attach_decode(const unsigned char *src, int len,
        unsigned int *pool,...`
  - `wl_commit_encode` (function, line 821) `static inline int wl_commit_encode(unsigned char *dst, int cap,
        unsigned int id)`
  - `wl_commit_decode` (function, line 834) `static inline int wl_commit_decode(const unsigned char *src, int len,
        unsigned int *id)`
  - `wl_ev_encode` (function, line 870) `static inline int wl_ev_encode(unsigned char *dst, int cap,
        const wl_ev_t *ev)`
  - `wl_ev_decode` (function, line 900) `static inline int wl_ev_decode(const unsigned char *src, int len,
        wl_ev_t *ev)`
  - `wl_ev_map` (function, line 943) `static inline int wl_ev_map(int fx, int fy, int sx, int sy, int sw,
        int sh, int rw, int r...`
  - `wl_client_init` (function, line 984) `static inline void wl_client_init(wl_client_t *cl)`
  - `wl_client_surface` (function, line 992) `static inline int wl_client_surface(wl_client_t *cl, unsigned int *id)`
  - `wl_client_pool` (function, line 1001) `static inline int wl_client_pool(wl_client_t *cl, unsigned int *id)`
  - `wl_stream_init` (function, line 1021) `static inline void wl_stream_init(wl_stream_t *s)`
  - `wl_stream_feed` (function, line 1027) `static inline int wl_stream_feed(wl_stream_t *s, const unsigned char *src,
        int n)`
  - `wl_stream_next` (function, line 1042) `static inline int wl_stream_next(wl_stream_t *s, int *size)`
  - `wl_stream_consume` (function, line 1058) `static inline int wl_stream_consume(wl_stream_t *s, int n)`
  - `wl_iface_find` (function, line 1079) `static inline int wl_iface_find(const char *name)`
  - `wl_comp_attach_buf` (function, line 1110) `static inline int wl_comp_attach_buf(wl_comp_t *c, unsigned int id,
        unsigned int pool, in...`
  - `wl_dispatch` (function, line 1137) `static inline int wl_dispatch(wl_comp_t *c, wl_client_t *cl,
        unsigned int id, unsigned in...`
  - `coords` (function, line 851) `* coords (mapped by wl_ev_map, -1 when outside), wheel is a * monotonic total the client diffs, scancodes are raw Set-1 bytes * (E0 prefixes included) the client's own translator consumes. * A slow cl`
  - `WL_MINI_H` (macro, line 18) `#define WL_MINI_H`
  - `WL_MAX_MSG` (macro, line 19) `#define WL_MAX_MSG`
  - `WL_MAX_STR` (macro, line 21) `#define WL_MAX_STR`
  - `WL_MAX_SURFACES` (macro, line 22) `#define WL_MAX_SURFACES`
  - `WL_MAX_POOLS` (macro, line 23) `#define WL_MAX_POOLS`
  - `WL_SURF_MAX_W` (macro, line 24) `#define WL_SURF_MAX_W`
  - `WL_SURF_MAX_H` (macro, line 25) `#define WL_SURF_MAX_H`
  - `WL_POOL_MAX` (macro, line 26) `#define WL_POOL_MAX`
  - `WL_HDR_SZ` (macro, line 27) `#define WL_HDR_SZ`
  - `WL_ATTACH_SZ` (macro, line 28) `#define WL_ATTACH_SZ`
  - `WL_COMMIT_SZ` (macro, line 29) `#define WL_COMMIT_SZ`
  - `WL_ERR_OK` (macro, line 30) `#define WL_ERR_OK`
  - `WL_ERR_BOUND` (macro, line 32) `#define WL_ERR_BOUND`
  - `WL_ERR_TRUNC` (macro, line 33) `#define WL_ERR_TRUNC`
  - `WL_ERR_SIZE` (macro, line 34) `#define WL_ERR_SIZE`
  - `WL_ERR_ID` (macro, line 35) `#define WL_ERR_ID`
  - `WL_ERR_STR` (macro, line 36) `#define WL_ERR_STR`
  - `WL_ERR_MORE` (macro, line 37) `#define WL_ERR_MORE`
  - `WL_ID_DISPLAY` (macro, line 38) `#define WL_ID_DISPLAY`
  - `WL_ID_REGISTRY` (macro, line 40) `#define WL_ID_REGISTRY`
  - `WL_ID_COMPOSITOR` (macro, line 41) `#define WL_ID_COMPOSITOR`
  - `WL_ID_SHM` (macro, line 42) `#define WL_ID_SHM`
  - `WL_ID_XDG_BASE` (macro, line 43) `#define WL_ID_XDG_BASE`
  - `WL_ID_SURFACE_BASE` (macro, line 44) `#define WL_ID_SURFACE_BASE`
  - `WL_ID_POOL_BASE` (macro, line 45) `#define WL_ID_POOL_BASE`
  - `WL_ID_BUFFER_BASE` (macro, line 46) `#define WL_ID_BUFFER_BASE`
  - `WL_OP_DISPLAY_GET_REGISTRY` (macro, line 47) `#define WL_OP_DISPLAY_GET_REGISTRY`
  - `WL_OP_REGISTRY_BIND` (macro, line 49) `#define WL_OP_REGISTRY_BIND`
  - `WL_OP_COMPOSITOR_CREATE_SURFACE` (macro, line 50) `#define WL_OP_COMPOSITOR_CREATE_SURFACE`
  - `WL_OP_SHM_CREATE_POOL` (macro, line 51) `#define WL_OP_SHM_CREATE_POOL`
  - `WL_OP_POOL_CREATE_BUFFER` (macro, line 52) `#define WL_OP_POOL_CREATE_BUFFER`
  - `WL_OP_SURFACE_ATTACH` (macro, line 53) `#define WL_OP_SURFACE_ATTACH`
  - `WL_OP_SURFACE_COMMIT` (macro, line 54) `#define WL_OP_SURFACE_COMMIT`
  - `WL_OP_XDG_GET_TOPLEVEL` (macro, line 55) `#define WL_OP_XDG_GET_TOPLEVEL`
  - `WL_CFG_DEFAULT` (macro, line 68) `#define WL_CFG_DEFAULT`
  - `WL_TITLE_H` (macro, line 238) `#define WL_TITLE_H`
  - `WL_CLOSE_W` (macro, line 239) `#define WL_CLOSE_W`
  - `WL_RESIZE_EDGE` (macro, line 240) `#define WL_RESIZE_EDGE`
  - `WL_TITLE_ACTIVE` (macro, line 241) `#define WL_TITLE_ACTIVE`
  - `WL_TITLE_INACTIVE` (macro, line 242) `#define WL_TITLE_INACTIVE`
  - `WL_CLOSE_INK` (macro, line 243) `#define WL_CLOSE_INK`
  - `WL_HIT_NONE` (macro, line 244) `#define WL_HIT_NONE`
  - `WL_HIT_BODY` (macro, line 246) `#define WL_HIT_BODY`
  - `WL_HIT_TITLE` (macro, line 247) `#define WL_HIT_TITLE`
  - `WL_HIT_CLOSE` (macro, line 248) `#define WL_HIT_CLOSE`
  - `WL_HIT_RESIZE` (macro, line 249) `#define WL_HIT_RESIZE`
  - `WLCOMP_BG` (macro, line 478) `#define WLCOMP_BG`
  - `WLCOMP_BORDER` (macro, line 479) `#define WLCOMP_BORDER`
  - `WL_EV_MAGIC` (macro, line 856) `#define WL_EV_MAGIC`
  - `WL_EV_SC_MAX` (macro, line 857) `#define WL_EV_SC_MAX`
  - `WL_EV_SZ` (macro, line 858) `#define WL_EV_SZ`
  - `WL_STREAM_CAP` (macro, line 1014) `#define WL_STREAM_CAP`
  - `WL_IFACE_COUNT` (macro, line 1076) `#define WL_IFACE_COUNT`
- Imported by: `progs/src/freedom_wl.c`, `progs/wl/wl_mbox.h`, `progs/wl/wlcomp.c`, `tests/test_wl.c`

## progs/wl/wlcomp.c
- Layer: utility
- Doc: wlcomp - Wayland-mini ring-3 compositor (ADR-0024, ADR-0026).
- Language: c
- Symbols:
  - `wlcomp_cfg_t` (struct, line 42)
  - `wlserv_t` (struct, line 397)
  - `wlclient_pat_t` (struct, line 952)
  - `wlcomp_sys_title` (function, line 54) `static long wlcomp_sys_title(const char *t)`
  - `wlcomp_sys_present` (function, line 62) `static long wlcomp_sys_present(long buf)`
  - `wlcomp_sys_present_origin` (function, line 70) `static long wlcomp_sys_present_origin(long buf, int *origin)`
  - `wlcomp_sys_palette` (function, line 78) `static long wlcomp_sys_palette(unsigned char *pal)`
  - `wlcomp_sys_mouse` (function, line 86) `static long wlcomp_sys_mouse(int *m)`
  - `wlcomp_sys_kbd` (function, line 94) `static long wlcomp_sys_kbd(void)`
  - `wlcomp_sys_kbd_raw` (function, line 102) `static long wlcomp_sys_kbd_raw(long on)`
  - `wlcomp_sys_vga_mode` (function, line 110) `static long wlcomp_sys_vga_mode(long on)`
  - `wlcomp_sys_yield` (function, line 118) `static long wlcomp_sys_yield(void)`
  - `wlcomp_sys_dir_list` (function, line 126) `static long wlcomp_sys_dir_list(const char *path, char *buf, long cap)`
  - `wlcomp_palette` (function, line 136) `static int wlcomp_palette(void)`
  - `wlcomp_pattern` (function, line 147) `static void wlcomp_pattern(unsigned char *dst, int w, int h,
        unsigned char a, unsigned ch...`
  - `wlcomp_demo` (function, line 186) `static int wlcomp_demo(wl_comp_t *c)`
  - `wlcomp_demo_blit` (function, line 211) `static int wlcomp_demo_blit(wl_comp_t *c, unsigned char *fb)`
  - `wlcomp_emit` (function, line 257) `static int wlcomp_emit(unsigned char *s, int cap, int o, unsigned int id,
        unsigned int op...`
  - `wlcomp_session` (function, line 269) `static int wlcomp_session(wl_comp_t *c, wl_client_t *cl)`
  - `wlcomp_selftest` (function, line 342) `static int wlcomp_selftest(void)`
  - `wlserv_init` (function, line 408) `static void wlserv_init(wlserv_t *s)`
  - `wlserv_slot` (function, line 424) `static int wlserv_slot(const wl_comp_t *c, unsigned int id)`
  - `wlserv_recolor` (function, line 437) `static void wlserv_recolor(wl_comp_t *c)`
  - `wlserv_present` (function, line 454) `static int wlserv_present(wlserv_t *s)`
  - `wlserv_drop` (function, line 475) `static void wlserv_drop(wlserv_t *s, int idx)`
  - `wlserv_fit` (function, line 487) `static void wlserv_fit(wlserv_t *s)`
  - `wlserv_gc_strays` (function, line 563) `static void wlserv_gc_strays(void)`
  - `wlserv_focus_box` (function, line 625) `static int wlserv_focus_box(const wlserv_t *s)`
  - `wlserv_key` (function, line 643) `static void wlserv_key(wlserv_t *s, unsigned char byte)`
  - `wlserv_ev_clear` (function, line 663) `static void wlserv_ev_clear(wlserv_t *s, int b)`
  - `wlserv_push_ev` (function, line 674) `static void wlserv_push_ev(wlserv_t *s, int fx, int fy, int buttons)`
  - `wlserv_clean_ev` (function, line 722) `static void wlserv_clean_ev(void)`
  - `wlserv_close` (function, line 765) `static int wlserv_close(wlserv_t *s, unsigned int id)`
  - `wlserv_drain` (function, line 799) `static int wlserv_drain(wlserv_t *s)`
  - `wlclient_find` (function, line 962) `static const wlclient_pat_t *wlclient_find(const char *name)`
  - `wlcomp_client` (function, line 991) `static int wlcomp_client(const char *box, const char *pat)`
  - `wlcomp_clean` (function, line 1057) `static int wlcomp_clean(void)`
  - `wlcomp_once` (function, line 1096) `static int wlcomp_once(void)`
  - `wlcomp_server` (function, line 1128) `static int wlcomp_server(void)`
  - `main` (function, line 1340) `int main(int argc, char **argv)`
  - `WLCOMP_W` (macro, line 37) `#define WLCOMP_W`
  - `WLCOMP_H` (macro, line 39) `#define WLCOMP_H`
  - `WLCOMP_CFG_DEFAULT` (macro, line 51) `#define WLCOMP_CFG_DEFAULT`
- Depends on: `kernel/string.c`, `progs/minios_abi.h`, `progs/nk_palette.h`, `progs/wl/wl_client.h`, `progs/wl/wl_mbox.h`, `progs/wl/wl_mini.h`
