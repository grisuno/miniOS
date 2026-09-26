# progs/wl

*Community 9 | 12 files | cohesion 0.59*

## Definition

This community groups 12 file(s) rooted at `progs/wl` with dominant language c (cohesion 0.59). Central symbols: `CHECK`, `FREEDOMUI_HOST_TEST`, `FREEDOM_WL_HOST_TEST`, `FUI_BODY_CAP`, `FUI_COLS`, `FUI_FONT_H`, `FUI_FONT_W`, `FUI_HDR_MAX`. Core file: `progs/wl/wl_mini.h` (110 symbols). Documented purpose: freedomui_minios - Real FreeDom browser on MiniOS, DOOM/Q2G pattern..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/freedomui/freedomui_minios.c` | c | presentation | 42 | yes |
| `progs/nk_palette.h` | h | utility | 9 | yes |
| `progs/nuklear/nuklear_minios.c` | c | utility | 52 | yes |
| `progs/src/freedom_wl.c` | c | utility | 62 | yes |
| `progs/wl/wl_client.h` | h | infrastructure | 5 | yes |
| `progs/wl/wl_mbox.h` | h | utility | 26 | yes |
| `progs/wl/wl_mini.h` | h | utility | 110 | yes |
| `progs/wl/wl_pixbuf.h` | h | utility | 18 | yes |
| `progs/wl/wlcomp.c` | c | utility | 45 | yes |
| `tests/test_freedom_wl.c` | c | testing | 3 | yes |
| `tests/test_freedomui.c` | c | testing | 2 | yes |
| `tests/test_wl.c` | c | testing | 2 | yes |

## Key Symbols

- `net_dns_resolve` (function, `progs/freedomui/freedomui_minios.c:44`) `int net_dns_resolve(const char *host);`
- `tls_handshake` (function, `progs/freedomui/freedomui_minios.c:45`) `int tls_handshake(int fd, char *host);`
- `tls_send` (function, `progs/freedomui/freedomui_minios.c:46`) `int tls_send(int fd, char *buf, int len);`
- `tls_recv` (function, `progs/freedomui/freedomui_minios.c:47`) `int tls_recv(int fd, char *buf, int len);`
- `tls_close` (function, `progs/freedomui/freedomui_minios.c:48`) `void tls_close(int fd);`
- `FUI_COLS` (macro, `progs/freedomui/freedomui_minios.c:51`) `#define FUI_COLS`
- `FUI_TEXT_ROWS` (macro, `progs/freedomui/freedomui_minios.c:52`) `#define FUI_TEXT_ROWS`
- `FUI_BODY_CAP` (macro, `progs/freedomui/freedomui_minios.c:53`) `#define FUI_BODY_CAP`
- `FUI_HDR_MAX` (macro, `progs/freedomui/freedomui_minios.c:54`) `#define FUI_HDR_MAX`
- `FUI_NET_BUF` (macro, `progs/freedomui/freedomui_minios.c:55`) `#define FUI_NET_BUF`
- `FUI_REQ_MAX` (macro, `progs/freedomui/freedomui_minios.c:56`) `#define FUI_REQ_MAX`
- `FUI_HOST_MAX` (macro, `progs/freedomui/freedomui_minios.c:57`) `#define FUI_HOST_MAX`
- `FUI_PATH_MAX` (macro, `progs/freedomui/freedomui_minios.c:58`) `#define FUI_PATH_MAX`
- `FUI_URL_MAX` (macro, `progs/freedomui/freedomui_minios.c:59`) `#define FUI_URL_MAX`
- `FUI_HOPS_MAX` (macro, `progs/freedomui/freedomui_minios.c:60`) `#define FUI_HOPS_MAX`
- `FUI_FONT_W` (macro, `progs/freedomui/freedomui_minios.c:61`) `#define FUI_FONT_W`
- `FUI_FONT_H` (macro, `progs/freedomui/freedomui_minios.c:62`) `#define FUI_FONT_H`
- `FUI_TITLE_MAX` (macro, `progs/freedomui/freedomui_minios.c:63`) `#define FUI_TITLE_MAX`
- `FreedomUiConfig` (struct, `progs/freedomui/freedomui_minios.c:69`) - #define FUI_NET_BUF 768L #define FUI_REQ_MAX 768L #define FUI_HOST_MAX 64L #define FUI_PATH_MAX 128L
- `present_buf` (type_alias, `progs/freedomui/freedomui_minios.c:69`) `typedef struct FreedomUiConfig { long present_buf;` - #define FUI_NET_BUF 768L #define FUI_REQ_MAX 768L #define FUI_HOST_MAX 64L #define FUI_PATH_MAX 128L
- `freedomui_default` (function, `progs/freedomui/freedomui_minios.c:97`) `static FreedomUiConfig freedomui_default(void)` - long path_max; long url_max; long hops_max; long font_w; long font_h; long port_http; long port_http
- `freedomui_build_palette` (function, `progs/freedomui/freedomui_minios.c:130`) `static long freedomui_build_palette(unsigned char *pal, long cap)` - Shared hybrid palette, one table for every NK-window app (progs/nk_palette.h); this wrapper keeps th
- `freedomui_engine_text` (function, `progs/freedomui/freedomui_minios.c:145`) `static long freedomui_engine_text(char *body, long n, char **title, char **text)` - Parse a fetched body through the real engine into owned title and text.  Runs hp_parse with secure d
- `freedomui_sys_present` (function, `progs/freedomui/freedomui_minios.c:193`) `static long freedomui_sys_present(long buf, long origin)` - static char f_path[FUI_PATH_MAX]; static char f_loc[FUI_URL_MAX]; static char f_hdr[FUI_HDR_MAX]; st
- `freedomui_sys_title` (function, `progs/freedomui/freedomui_minios.c:200`) `static long freedomui_sys_title(char *t)` - static long f_nbytes; static long f_secure; static long f_port; static long f_status; static long f_
- `freedomui_sys_palette` (function, `progs/freedomui/freedomui_minios.c:207`) `static long freedomui_sys_palette(unsigned char *pal)` - static long freedomui_sys_present(long buf, long origin) { long ret; __asm__ volatile("syscall" : "=
- `freedomui_sys_mouse` (function, `progs/freedomui/freedomui_minios.c:214`) `static long freedomui_sys_mouse(long *m)` - static long freedomui_sys_title(char *t) { long ret; __asm__ volatile("syscall" : "=a"(ret) : "a"(MI
- `freedomui_sys_kbd` (function, `progs/freedomui/freedomui_minios.c:221`) `static long freedomui_sys_kbd(void)` - static long freedomui_sys_palette(unsigned char *pal) { long ret; __asm__ volatile("syscall" : "=a"(
- `freedomui_sys_vga_mode` (function, `progs/freedomui/freedomui_minios.c:228`) `static long freedomui_sys_vga_mode(long on)` - static long freedomui_sys_mouse(long *m) { long ret; __asm__ volatile("syscall" : "=a"(ret) : "a"(MI
- `freedomui_sys_kbd_raw` (function, `progs/freedomui/freedomui_minios.c:235`) `static long freedomui_sys_kbd_raw(long on)` - static long freedomui_sys_kbd(void) { long ret; __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 19
- Cross-boundary resolved imports (EXTRACTED): 13

## Connections

- [EXTRACTED] depends_on community 9 <-> 3 (strength 0.9): Extracted import edge crosses communities: progs/freedomui/freedomui_minios.c imports progs/minios_abi.h.
- [EXTRACTED] depends_on community 9 <-> 0 (strength 0.9): Extracted import edge crosses communities: progs/src/freedom_wl.c imports headers/vga_fb.h.

## Risks

- [layer strict] `tests/test_freedomui.c` (testing) -> `progs/freedomui/freedomui_minios.c` (presentation)

## Open Questions

- What would break if the most connected file in progs/wl changed?
- Should progs/wl be split, given cohesion 0.59?

## Sources

- `progs/freedomui/freedomui_minios.c`
- `progs/nk_palette.h`
- `progs/nuklear/nuklear_minios.c`
- `progs/src/freedom_wl.c`
- `progs/wl/wl_client.h`
- `progs/wl/wl_mbox.h`
- `progs/wl/wl_mini.h`
- `progs/wl/wl_pixbuf.h`
- `progs/wl/wlcomp.c`
- `tests/test_freedom_wl.c`
- `tests/test_freedomui.c`
- `tests/test_wl.c`
