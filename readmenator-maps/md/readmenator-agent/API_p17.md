# API (page 17 of 19)
Previous: [API_p16.md](API_p16.md)

## progs/src/freedom.c
Depends on: `kernel/string.c`
- `curlfree` (function) `progs/src/freedom.c:4` `* spirit of curlfree (http.c + htmlfilter.c): a bounded header phase, * Content-Length or EOF body reading...`
- `net_dns_resolve` (function) `progs/src/freedom.c:41` `int net_dns_resolve(const char *host);` -- Ring-3 TLS build (phase 2 of docs/TLS_MIGRATION.md): host libc for sockets/stdio/strings (identical ABI numbers...
- `tls_handshake` (function) `progs/src/freedom.c:42` `int tls_handshake(int fd, char *host);`
- `tls_send` (function) `progs/src/freedom.c:43` `int tls_send(int fd, char *buf, int len);`
- `tls_recv` (function) `progs/src/freedom.c:44` `int tls_recv(int fd, char *buf, int len);`
- `socket` (function) `progs/src/freedom.c:52` `int socket(int domain, int type, int proto);` -- else
- `connect` (function) `progs/src/freedom.c:53` `int connect(int fd, void *addr, int addrlen);`
- `sendto` (function) `progs/src/freedom.c:54` `int sendto(int fd, char *buf, int len, int flags, void *to, int tolen);`
- `recvfrom` (function) `progs/src/freedom.c:55` `int recvfrom(int fd, char *buf, int len, int flags, void *from, int *fromlen);`
- `close` (function) `progs/src/freedom.c:56` `int close(int fd);`
- `tls_close` (function) `progs/src/freedom.c:58` `static int tls_close(int fd)` -- Session-aware close (frees the TLS session for fd, no-op when none): every fetch path must use this, never raw...
- `printf` (function) `progs/src/freedom.c:63` `int printf(char *fmt, ...);`
- `puts` (function) `progs/src/freedom.c:64` `int puts(char *s);`
- `strlen` (function) `progs/src/freedom.c:65` `int strlen(char *s);`
- `strchr` (function) `progs/src/freedom.c:66` `char *strchr(char *s, int c);`
- `strcmp` (function) `progs/src/freedom.c:67` `int strcmp(char *a, char *b);`
- `strncmp` (function) `progs/src/freedom.c:68` `int strncmp(char *a, char *b, int n);`
- `memcpy` (function) `progs/src/freedom.c:69` `int memcpy(char *dst, char *src, int n);`
- `memset` (function) `progs/src/freedom.c:70` `int memset(char *dst, int c, int n);`
- `putchar` (function) `progs/src/freedom.c:71` `int putchar(int c);`
- `atoi` (function) `progs/src/freedom.c:151` `static int atoi(char *s)` -- static char f_dom[FREEDOM_DOM_BUF]; static int  f_domlen; static char f_css[FREEDOM_CSS_BUF]; static int  f_csslen...
- `append` (function) `progs/src/freedom.c:166` `static int append(char *dst, int pos, char *src, int cap)` -- Append src to dst at pos; returns the new length or -1 when it does not fit.
- `ci_lower` (function) `progs/src/freedom.c:176` `static int ci_lower(int c)`
- `ci_starts` (function) `progs/src/freedom.c:182` `static int ci_starts(char *s, char *pre)` -- if (pos < 0) return -1; n = strlen(src); if (pos + n >= cap) return -1; memcpy(dst + pos, src, n); dst[pos + n] = 0...
- `ci_eq` (function) `progs/src/freedom.c:193` `static int ci_eq(char *a, char *b)` -- } /* Case-insensitive starts-with. static int ci_starts(char *s, char *pre) { while (*pre) { if (!*s) return 0; if...
- `ci_index` (function) `progs/src/freedom.c:203` `static int ci_index(char *s, char *needle)` -- return 1; } /* Case-insensitive equality. static int ci_eq(char *a, char *b) { while (*a && *b) { if (ci_lower(*a)...
- `looks_like_url` (function) `progs/src/freedom.c:212` `static int looks_like_url(char *s)` -- } return *a == 0 && *b == 0; } /* Case-insensitive index of needle in haystack, or -1. static int ci_index(char *s...
- `has_scheme` (function) `progs/src/freedom.c:226` `static int has_scheme(char *s)` -- Does s begin with "<scheme>:" per RFC 3986 (ALPHA *(ALPHA/DIGIT/+/-/.) ":")?
- `make_search` (function) `progs/src/freedom.c:242` `static void make_search(char *out, char *query, int cap)` -- char c; c = s[0]; if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) return 0; for (i = 1; s[i]; i++) { c =...
- `split_url` (function) `progs/src/freedom.c:266` `static int split_url(char *url)` -- Split an http:// or https:// URL into f_host, f_path, f_port and f_secure.
- `resolve_redirect` (function) `progs/src/freedom.c:313` `static int resolve_redirect(void)` -- Recompute f_host/f_path/f_port/f_secure from the last Location value.
- `put_ws` (function) `progs/src/freedom.c:366` `static void put_ws(void)`
- `put_utf` (function) `progs/src/freedom.c:377` `static void put_utf(int c)` -- Print one text byte through the UTF-8 gate.
- `put_text` (function) `progs/src/freedom.c:427` `static void put_text(int c)` -- Print one text byte: whitespace collapses, everything else goes * through the UTF-8 gate.
- `css_append` (function) `progs/src/freedom.c:483` `static void css_append(char *s, int n)`
- `css_line` (function) `progs/src/freedom.c:489` `static void css_line(char *s)`
- `dom_append` (function) `progs/src/freedom.c:494` `static void dom_append(char *s, int n)`
- `dom_space` (function) `progs/src/freedom.c:500` `static void dom_space(void)`
- `dom_nl` (function) `progs/src/freedom.c:504` `static void dom_nl(void)`
- `record_attr` (function) `progs/src/freedom.c:509` `static void record_attr(void)` -- int i; for (i = 0; i < n && f_domlen < FREEDOM_DOM_BUF - 1; i++) f_dom[f_domlen++] = s[i]; } static void...
- `is_void_tag` (function) `progs/src/freedom.c:534` `static int is_void_tag(void)` -- f_hreflen = f_vallen < 127 ? f_vallen : 127; memcpy(f_href, f_val, f_hreflen); f_href[f_hreflen] = 0; } else if...
- `classify_tag` (function) `progs/src/freedom.c:546` `static void classify_tag(void)` -- A tag was fully collected into f_tagn (+ attributes).
- `body_byte` (function) `progs/src/freedom.c:631` `static void body_byte(int c)` -- } dom_nl(); if (!is_void_tag()) f_depth++; } if (ci_eq(f_tagn, "br") || ci_eq(f_tagn, "p") || ci_eq(f_tagn, "div")...
- `head_line` (function) `progs/src/freedom.c:796` `static void head_line(char *line)` -- f_rel_ss = 0; return; } if (c == '&') { f_entlen = 1; f_ent[0] = 0; return; } put_text(c); } /* --- HTTP
- `parse_head` (function) `progs/src/freedom.c:821` `static void parse_head(void)` -- Parse the collected header block f_hdr[0..f_hlen-1] (the last four * bytes are the terminating CRLF CRLF).
- `recv_body` (function) `progs/src/freedom.c:843` `static int recv_body(int fd, char *buf, int len)` -- f_hdr[lend] = 0; if (i == 0) { char *sp; sp = strchr(f_hdr, ' '); if (sp) f_status = atoi(sp + 1); } else if (lend >...
- `send_all` (function) `progs/src/freedom.c:849` `static int send_all(int fd, char *buf, int len)` -- head_line(f_hdr + i); } f_hdr[lend] = '\r'; i = lend + 2; } } /* Receive body bytes: TLS for f_secure, plain TCP...
- `fetch` (function) `progs/src/freedom.c:860` `static int fetch(char *host, char *path, int port)` -- Send one HTTP request and process the response body.
- `fetch_css` (function) `progs/src/freedom.c:1031` `static void fetch_css(char *host, char *path)` -- Fetch a linked stylesheet and print its raw body (through the UTF-8 * gate).
- `print_css_dump` (function) `progs/src/freedom.c:1113` `static void print_css_dump(void)` -- } continue; } f_ws = 0; put_utf(c); got++; } } tls_close(fd); putchar('\n'); printf("freedom: %s (%d bytes)\n"...
- `print_dom_dump` (function) `progs/src/freedom.c:1122` `static void print_dom_dump(void)` -- putchar('\n'); printf("freedom: %s (%d bytes)\n", host, got); } /* Print the collected CSS dump. static void...
- `main` (function) `progs/src/freedom.c:1129` `int main(int argc, char **argv)`

## progs/src/freedom_wl.c
Depends on: `headers/vga_fb.h`, `kernel/string.c`, `progs/minios_abi.h`, `progs/nk_palette.h`, `progs/wl/wl_mini.h`
Imported by: `tests/test_freedom_wl.c`
- `net_dns_resolve` (function) `progs/src/freedom_wl.c:42` `int net_dns_resolve(const char *host);`
- `tls_handshake` (function) `progs/src/freedom_wl.c:43` `int tls_handshake(int fd, char *host);`
- `tls_send` (function) `progs/src/freedom_wl.c:44` `int tls_send(int fd, char *buf, int len);`
- `tls_recv` (function) `progs/src/freedom_wl.c:45` `int tls_recv(int fd, char *buf, int len);`
- `tls_close` (function) `progs/src/freedom_wl.c:46` `void tls_close(int fd);`
- `freedom_wl_surface_id` (function) `progs/src/freedom_wl.c:114` `static long freedom_wl_surface_id(void)` -- Logical Wayland-mini surface id for this client (ADR-0024).
- `freedom_wl_surface_attach` (function) `progs/src/freedom_wl.c:129` `static long freedom_wl_surface_attach(FreedomWlConfig *c)` -- Attach this client to the wlcomp mapping: encode an attach message for the first pool and a commit for our surface...
- `freedom_wl_default` (function) `progs/src/freedom_wl.c:158` `static FreedomWlConfig freedom_wl_default(void)` -- if (pool != WL_ID_POOL_BASE || w != (int)c->surface_w || h != (int)c->surface_h) return -1L; n =...
- `freedom_wl_clip_rect` (function) `progs/src/freedom_wl.c:196` `static long freedom_wl_clip_rect(FreedomWlConfig *c, long *x, long *y, long *w, long *h)` -- c.hops_max = WL_HOPS_MAX; c.font_w = WL_FONT_W; c.font_h = WL_FONT_H; c.port_http = 80L; c.port_https = 443L...
- `freedom_wl_frame_bytes` (function) `progs/src/freedom_wl.c:227` `static long freedom_wl_frame_bytes(FreedomWlConfig *c, long w, long h)` -- } if (*x + *w > c->surface_w) { w = c->surface_w - *x; } if (*y + *h > c->surface_h) { h = c->surface_h - *y; } if...
- `freedom_wl_keysym` (function) `progs/src/freedom_wl.c:246` `static long freedom_wl_keysym(FreedomWlConfig *c, long sc)` -- if (w <= 0L || h <= 0L) { return -1L; } if (w > c->surface_w || h > c->surface_h) { return -1L; } bytes_per_pixel =...
- `freedom_wl_sanitize_utf8` (function) `progs/src/freedom_wl.c:286` `static long freedom_wl_sanitize_utf8(char *s, long cap)` -- } if (make == 0x39L) { return 32L; } if (make == 0x0EL) { return 8L; } if (make == 0x0FL) { return 9L; } return -1L...
- `freedom_wl_title_ok` (function) `progs/src/freedom_wl.c:359` `static long freedom_wl_title_ok(FreedomWlConfig *c, char *t, long n)` -- i++; } if (o >= cap - 1L) { break; } } if (o >= cap) { return -1L; } s[o] = 0; return o; } /** Validate a window...
- `wl_copy` (function) `progs/src/freedom_wl.c:370` `static long wl_copy(char *dst, char *src, long cap)` -- } /** Validate a window title against the kernel title bound. static long freedom_wl_title_ok(FreedomWlConfig *c...
- `wl_strlen` (function) `progs/src/freedom_wl.c:388` `static long wl_strlen(char *s, long cap)` -- } i = 0L; while (src[i] != 0) { if (i + 1L >= cap) { return -1L; } dst[i] = src[i]; i++; } dst[i] = 0; return 0L; }...
- `wl_append` (function) `progs/src/freedom_wl.c:404` `static long wl_append(char *dst, long pos, char *src, long cap)` -- if (!s || cap <= 0L) { return -1L; } i = 0L; while (i < cap && s[i] != 0) { i++; } if (i >= cap) { return -1L; }...
- `wl_ci_lower` (function) `progs/src/freedom_wl.c:427` `static long wl_ci_lower(long ch)` -- } if (pos + n >= cap) { return -1L; } i = 0L; while (i < n) { dst[pos + i] = src[i]; i++; } dst[pos + n] = 0; return...
- `wl_ci_starts` (function) `progs/src/freedom_wl.c:435` `static long wl_ci_starts(char *s, char *pre)` -- } dst[pos + n] = 0; return pos + n; } /** ASCII lowercase fold. static long wl_ci_lower(long ch) { if (ch >= 'A' &&...
- `wl_ci_contains` (function) `progs/src/freedom_wl.c:453` `static long wl_ci_contains(char *s, char *needle)` -- while (*pre) { if (*s == 0) { return 0L; } if (wl_ci_lower(*s) != wl_ci_lower(*pre)) { return 0L; } s++; pre++; }...
- `wl_has_scheme` (function) `progs/src/freedom_wl.c:467` `static long wl_has_scheme(char *s)` -- static long wl_ci_contains(char *s, char *needle) { if (!s || !needle) { return 0L; } while (*s) { if...
- `wl_looks_like_url` (function) `progs/src/freedom_wl.c:493` `static long wl_looks_like_url(char *s)` -- ch = s[i]; if (ch == ':') { return 1L; } if (!((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' &&...
- `wl_make_search` (function) `progs/src/freedom_wl.c:512` `static long wl_make_search(char *out, char *query, long cap)` -- dot = 0L; while (*s) { if (*s == ' ' || *s == '\t') { return 0L; } if (*s == '.') { dot = 1L; } s++; } return dot; }...
- `wl_split_url` (function) `progs/src/freedom_wl.c:544` `static long wl_split_url(FreedomWlConfig *c, char *url, char *host, char *path, long *port, long ...` -- } else { out[pos] = *query; pos++; out[pos] = 0; } if (pos < 0L) { return -1L; } query++; } return pos; } /** Split...
- `wl_resolve_redirect` (function) `progs/src/freedom_wl.c:609` `static long wl_resolve_redirect(FreedomWlConfig *c, char *loc, long secure, char *host, char *pat...` -- if (plen < 0L) { return 0L; } if (wl_copy(path, p + hl, c->path_max) < 0L) { return 0L; } } else { path[0] = '/'...
- `wl_scroll_clamp` (function) `progs/src/freedom_wl.c:689` `static long wl_scroll_clamp(FreedomWlConfig *c, long off, long nlines)` -- if (last + 1L + l >= c->path_max) { return 0L; } i = 0L; while (i < l) { path[last + 1L + i] = loc[i]; i++; }...
- `wl_filter_wrap` (function) `progs/src/freedom_wl.c:708` `static long wl_filter_wrap(FreedomWlConfig *c, char *body, long n, char *lines, long maxlines, lo...` -- if (nlines <= c->text_rows) { return 0L; } maxoff = nlines - c->text_rows; if (off < 0L) { return 0L; } if (off >...
- `wl_status_text` (function) `progs/src/freedom_wl.c:951` `static long wl_status_text(FreedomWlConfig *c, char *host, long nbytes, long off, long nlines, ch...` -- lines[li * linelen + co] = (char)ch; co++; lines[li * linelen + co] = 0; } if (co > 0L) { return li + 1L; } if (li...
- `freedom_wl_build_palette` (function) `progs/src/freedom_wl.c:1039` `static long freedom_wl_build_palette(unsigned char *pal, long cap)` -- Shared hybrid palette, one table for every NK-window app (progs/nk_palette.h); this wrapper keeps the historic name...
- `freedom_wl_sys_present` (function) `progs/src/freedom_wl.c:1062` `static long freedom_wl_sys_present(long buf, long origin)` -- static char w_host[WL_HOST_MAX]; static char w_path[WL_PATH_MAX]; static char w_loc[WL_URL_MAX]; static char...
- `freedom_wl_sys_title` (function) `progs/src/freedom_wl.c:1069` `static long freedom_wl_sys_title(char *t)` -- static long w_nbytes; static long w_secure; static long w_port; static long w_status; static long w_truncated; /**...
- `freedom_wl_sys_palette` (function) `progs/src/freedom_wl.c:1076` `static long freedom_wl_sys_palette(unsigned char *pal)` -- static long freedom_wl_sys_present(long buf, long origin) { long ret; __asm__ volatile("syscall" : "=a"(ret)...
- `freedom_wl_sys_mouse` (function) `progs/src/freedom_wl.c:1083` `static long freedom_wl_sys_mouse(long *m)` -- static long freedom_wl_sys_title(char *t) { long ret; __asm__ volatile("syscall" : "=a"(ret)...
- `freedom_wl_sys_kbd` (function) `progs/src/freedom_wl.c:1090` `static long freedom_wl_sys_kbd(void)` -- static long freedom_wl_sys_palette(unsigned char *pal) { long ret; __asm__ volatile("syscall" : "=a"(ret)...
- `freedom_wl_sys_vga_mode` (function) `progs/src/freedom_wl.c:1097` `static long freedom_wl_sys_vga_mode(long on)` -- static long freedom_wl_sys_mouse(long *m) { long ret; __asm__ volatile("syscall" : "=a"(ret)...
- `freedom_wl_sys_kbd_raw` (function) `progs/src/freedom_wl.c:1104` `static long freedom_wl_sys_kbd_raw(long on)` -- static long freedom_wl_sys_kbd(void) { long ret; __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_KBD)...
- `freedom_wl_sys_yield` (function) `progs/src/freedom_wl.c:1111` `static long freedom_wl_sys_yield(void)` -- static long freedom_wl_sys_vga_mode(long on) { long ret; __asm__ volatile("syscall" : "=a"(ret)...
- `wl_parse_headers` (function) `progs/src/freedom_wl.c:1118` `static long wl_parse_headers(FreedomWlConfig *c, char *hdr, long *status, long *clen, long *hascl...` -- static long freedom_wl_sys_kbd_raw(long on) { long ret; __asm__ volatile("syscall" : "=a"(ret)...
- `wl_fetch_raw` (function) `progs/src/freedom_wl.c:1210` `static long wl_fetch_raw(FreedomWlConfig *c, char *host, char *path, long port, long secure)` -- if (!wl_ci_starts(hdr + k, "text")) { istext = 0L; } } } line++; while (hdr[i] == '\r' || hdr[i] == '\n') { i++; } }...
- `wl_render` (function) `progs/src/freedom_wl.c:1445` `static long wl_render(FreedomWlConfig *c, long off)` -- if (got < c->body_cap) { w_body[got] = (char)ch; got++; } else { w_truncated = 1L; } } } } tls_close((int)fd)...
- `wl_browse` (function) `progs/src/freedom_wl.c:1532` `static long wl_browse(FreedomWlConfig *c)` -- long ink; if (bits & (0x80 >> px)) { ink = c->bar_fg; } else { ink = c->bar_bg; } fb[(c->text_rows * c->font_h +...
- `freedom_wl_selftest` (function) `progs/src/freedom_wl.c:1613` `static long freedom_wl_selftest(void)` -- off = off + (long)m[3] * c->scroll_step; changed = 1L; } if (changed) { off = wl_scroll_clamp(c, off, w_nlines); if...
- `freedom_wl_host_probe` (function) `progs/src/freedom_wl.c:1696` `int freedom_wl_host_probe(FreedomWlConfig *c)` -- return 1L; } if (freedom_wl_sys_kbd() > 0x7FFFFFFFL) { printf("freedom_wl: kbd out of range\n"); return 1L; }...
- `main` (function) `progs/src/freedom_wl.c:1731` `int main(int argc, char **argv)` -- } buf[0] = 'h'; buf[1] = 'i'; buf[2] = 0; if (freedom_wl_sanitize_utf8(buf, 16L) != 2L) { return 1; } if...

## progs/src/ftest.c
- `fprintf` (function) `progs/src/ftest.c:4` `extern int fprintf(void *stream, const char *fmt, ...);` -- Exercises the kernel libc surface used by loaded .o programs: fprintf to stdout/stderr, snprintf into a buffer...
- `snprintf` (function) `progs/src/ftest.c:5` `extern int snprintf(char *buf, unsigned long size, const char *fmt, ...);`
- `printf` (function) `progs/src/ftest.c:6` `extern int printf(const char *fmt, ...);`
- `exit` (function) `progs/src/ftest.c:7` `extern void exit(int code);`
- `fopen` (function) `progs/src/ftest.c:11` `extern void *fopen(const char *path, const char *mode);`
- `main` (function) `progs/src/ftest.c:13` `int main(int argc, char **argv)`

## progs/src/hello.c
- `printf` (function) `progs/src/hello.c:2` `extern int printf(const char *fmt, ...);` -- /* MiniOS test program — compiled as relocatable .o, loaded by kernel ELF loader
- `main` (function) `progs/src/hello.c:4` `int main(int argc, char **argv)`

## progs/src/http.c
- `kernel` (function) `progs/src/http.c:3` `* Hostnames are resolved by the kernel (net_dns_resolve syscall). */ int socket(int domain, int type, int proto);`
- `connect` (function) `progs/src/http.c:6` `int connect(int fd, void *addr, int addrlen);`
- `sendto` (function) `progs/src/http.c:7` `int sendto(int fd, char *buf, int len, int flags, void *to, int tolen);`
- `recvfrom` (function) `progs/src/http.c:8` `int recvfrom(int fd, char *buf, int len, int flags, void *from, int *fromlen);`
- `shutdown` (function) `progs/src/http.c:9` `int shutdown(int fd, int how);`
- `close` (function) `progs/src/http.c:10` `int close(int fd);`
- `net_dns_resolve` (function) `progs/src/http.c:11` `int net_dns_resolve(const char *host);`
- `puts` (function) `progs/src/http.c:12` `int puts(char *s);`
- `printf` (function) `progs/src/http.c:13` `int printf(char *fmt, ...);`
- `strlen` (function) `progs/src/http.c:14` `int strlen(char *s);`
- `putchar` (function) `progs/src/http.c:15` `int putchar(int c);`
- `atoi` (function) `progs/src/http.c:18` `int atoi(char *s)` -- int socket(int domain, int type, int proto); int connect(int fd, void *addr, int addrlen); int sendto(int fd, char...
- `main` (function) `progs/src/http.c:29` `int main(int argc, char **argv)`

## progs/src/json.c
- `js_str` (function) `progs/src/json.c:5` `* members keep their key in js_str (the member value node) and their value * in the node itself, and object members...`
- `free` (function) `progs/src/json.c:14` `void free();`
- `printf` (function) `progs/src/json.c:15` `int printf();`
- `putchar` (function) `progs/src/json.c:16` `int putchar();`
- `puts` (function) `progs/src/json.c:17` `int puts();`
- `strlen` (function) `progs/src/json.c:18` `int strlen();`
- `strcmp` (function) `progs/src/json.c:19` `int strcmp();`
- `fopen` (function) `progs/src/json.c:20` `void *fopen();`
- `fclose` (function) `progs/src/json.c:21` `int fclose();`
- `fread` (function) `progs/src/json.c:22` `int fread();`
- `fseek` (function) `progs/src/json.c:23` `int fseek();`
- `ftell` (function) `progs/src/json.c:24` `int ftell();`
- `rewind` (function) `progs/src/json.c:25` `void rewind();`
- `js_read_all` (function) `progs/src/json.c:58` `static char *js_read_all(const char *name, int *len)`
- `js_new` (function) `progs/src/json.c:76` `static int js_new(void)`
- `js_skip_ws` (function) `progs/src/json.c:81` `static void js_skip_ws(void)`
- `js_peek` (function) `progs/src/json.c:89` `static int js_peek(void)`
- `js_parse_string` (function) `progs/src/json.c:97` `static int js_parse_string(void)`
- `js_parse_number` (function) `progs/src/json.c:133` `static int js_parse_number(void)`
- `js_key_match` (function) `progs/src/json.c:143` `static int js_key_match(int child, const char *key)`
- `js_parse_object` (function) `progs/src/json.c:147` `static int js_parse_object(void)`
- `js_parse_array` (function) `progs/src/json.c:182` `static int js_parse_array(void)`
- `js_parse_value` (function) `progs/src/json.c:211` `static int js_parse_value(void)`
- `js_indent` (function) `progs/src/json.c:281` `static void js_indent(int n)`
- `js_print_str` (function) `progs/src/json.c:286` `static void js_print_str(const char *s)`
- `js_print_value` (function) `progs/src/json.c:303` `static void js_print_value(int node, int depth)`
- `js_find_member` (function) `progs/src/json.c:347` `static int js_find_member(int obj, const char *key)`
- `js_array_at` (function) `progs/src/json.c:357` `static int js_array_at(int arr, int idx)`
- `js_query` (function) `progs/src/json.c:369` `static int js_query(int root, const char *path)`
- `main` (function) `progs/src/json.c:401` `int main(int argc, char **argv)`

## progs/src/kmem.c
- `syscall3` (function) `progs/src/kmem.c:7` `static long syscall3(long n, long a1, long a2, long a3)` -- Kernel-pointer rejection probe.
- `exit_now` (function) `progs/src/kmem.c:14` `static void exit_now(long code)`

## progs/src/ldhello.c
- `main` (function) `progs/src/ldhello.c:1` `int main(void)`

## progs/src/lxabi.c
Depends on: `headers/sched.h`, `kernel/string.c`, `kernel/time.c`
- `report` (function) `progs/src/lxabi.c:64` `static void report(const char *name, int ok, const char *detail)`
- `now_ms` (function) `progs/src/lxabi.c:74` `static long now_ms(void)`
- `busy_wait_ms` (function) `progs/src/lxabi.c:80` `static void busy_wait_ms(long ms)`
- `fork_probe` (function) `progs/src/lxabi.c:94` `static void fork_probe(uint64_t *out)` -- Raw clone(SIGCHLD) with known values in every callee-saved register and in * the argument registers; both sides...
- `regs_match` (function) `progs/src/lxabi.c:131` `static int regs_match(const uint64_t *r)`
- `check_fork_registers` (function) `progs/src/lxabi.c:137` `static void check_fork_registers(void)`
- `check_fork_cow_kernel_write` (function) `progs/src/lxabi.c:159` `static void check_fork_cow_kernel_write(void)`
- `worker` (function) `progs/src/lxabi.c:200` `static void *worker(void *arg)`
- `check_threads` (function) `progs/src/lxabi.c:214` `static void check_threads(void)`
- `detached_worker` (function) `progs/src/lxabi.c:244` `static void *detached_worker(void *arg)`
- `check_detached_reaped` (function) `progs/src/lxabi.c:250` `static void check_detached_reaped(void)`
- `signaller` (function) `progs/src/lxabi.c:274` `static void *signaller(void *arg)`
- `check_condvar` (function) `progs/src/lxabi.c:284` `static void check_condvar(void)`
- `check_pipe2_flags` (function) `progs/src/lxabi.c:306` `static void check_pipe2_flags(void)`
- `check_pipe_blocking` (function) `progs/src/lxabi.c:333` `static void check_pipe_blocking(void)`
- `check_pipe_epipe` (function) `progs/src/lxabi.c:355` `static void check_pipe_epipe(void)`
- `check_writev_pipe` (function) `progs/src/lxabi.c:381` `static void check_writev_pipe(void)`
- `check_poll` (function) `progs/src/lxabi.c:393` `static void check_poll(void)`
- `check_eventfd` (function) `progs/src/lxabi.c:417` `static void check_eventfd(void)`
- `check_close_range` (function) `progs/src/lxabi.c:442` `static void check_close_range(void)`
- `check_time` (function) `progs/src/lxabi.c:454` `static void check_time(void)`
- `check_mkdir` (function) `progs/src/lxabi.c:463` `static void check_mkdir(void)`
- `check_limits` (function) `progs/src/lxabi.c:477` `static void check_limits(void)` -- The answers glibc sizes memory from: a finite stack limit (thread stacks default to it) and a CPU count that matches...
- `mono_us` (function) `progs/src/lxabi.c:490` `static long mono_us(void)`
- `check_sleep` (function) `progs/src/lxabi.c:499` `static void check_sleep(void)` -- Sleeps really wait: nanosleep for a relative interval, clock_nanosleep until an absolute monotonic deadline, and a...
- `lxabi_sleeper` (function) `progs/src/lxabi.c:526` `static void *lxabi_sleeper(void *arg)` -- rc = clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &abs_t, NULL); waited = mono_us() - t0...
- `child_status` (function) `progs/src/lxabi.c:534` `static int child_status(void (*body)(void))` -- Fork a child that runs body, wait for it with a bounded spin and return * its wait status, or -1 when it never ended...
- `abort_from_worker_body` (function) `progs/src/lxabi.c:554` `static void abort_from_worker_body(void)`
- `lxabi_exit_group_worker` (function) `progs/src/lxabi.c:560` `static void *lxabi_exit_group_worker(void *arg)`
- `exit_group_from_worker_body` (function) `progs/src/lxabi.c:566` `static void exit_group_from_worker_body(void)`
- `wild_jump_body` (function) `progs/src/lxabi.c:572` `static void wild_jump_body(void)`
- `process` (function) `progs/src/lxabi.c:580` `* process (never a kernel panic), and kill(pid, 0) or a harmless signal
 * leaves the target aliv...`
- `main` (function) `progs/src/lxabi.c:617` `int main(void)`

## progs/src/lxhello.c
- `lx_syscall3` (function) `progs/src/lxhello.c:11` `static long lx_syscall3(long n, long a1, long a2, long a3)`
- `lx_strlen` (function) `progs/src/lxhello.c:23` `static unsigned long lx_strlen(const char *s)`
- `lx_write` (function) `progs/src/lxhello.c:29` `static void lx_write(const char *s)`
- `lx_write_int` (function) `progs/src/lxhello.c:33` `static void lx_write_int(long v)`
- `lmain` (function) `progs/src/lxhello.c:46` `int lmain(long argc, char **argv)` -- static void lx_write_int(long v) { char buf[24]; int i = (int)sizeof(buf); int neg = 0; buf[--i] = 0; if (v < 0) {...

## progs/src/lxnet.c
Depends on: `kernel/string.c`
- `report` (function) `progs/src/lxnet.c:49` `static void report(const char *name, int ok, const char *detail)`
- `wait_for` (function) `progs/src/lxnet.c:55` `static int wait_for(int fd, short events)`
- `read_all` (function) `progs/src/lxnet.c:62` `static int read_all(int fd, char *buf, size_t len)` -- static void report(const char *name, int ok, const char *detail) { if (ok) printf("lxnet: %s ok\n", name); else {...
- `check_udp` (function) `progs/src/lxnet.c:73` `static void check_udp(const struct sockaddr_in *peer)`
- `check_refused` (function) `progs/src/lxnet.c:150` `static void check_refused(const struct sockaddr_in *peer)` -- A non-blocking connect to a port nobody listens on fails through poll * (POLLERR) with SO_ERROR = ECONNREFUSED...
- `check_tcp` (function) `progs/src/lxnet.c:174` `static void check_tcp(const struct sockaddr_in *peer)`
- `check_misc` (function) `progs/src/lxnet.c:217` `static void check_misc(void)`
- `dial` (function) `progs/src/lxnet.c:236` `static int dial(const char *host, const char *port)` -- if (fd >= 0) close(fd); struct addrinfo hints, *res = NULL; memset(&hints, 0, sizeof hints); hints.ai_family =...
- `main` (function) `progs/src/lxnet.c:280` `int main(int argc, char **argv)`

## progs/src/lxsecc.c
Depends on: `kernel/string.c`
- `report` (function) `progs/src/lxsecc.c:44` `static void report(const char *name, int ok, const char *detail)`
- `exit_code_of` (function) `progs/src/lxsecc.c:53` `static int exit_code_of(int st)` -- Exit code of a reaped child under both encodings: Linux's status word (code << 8, signal in the low bits) and...
- `run_child` (function) `progs/src/lxsecc.c:58` `static int run_child(void (*body)(void))`
- `install_filter` (function) `progs/src/lxsecc.c:72` `static int install_filter(unsigned getpid_action)` -- Filter: arch guard, getpid -> ERRNO(err_getpid), write/exit/exit_group/ * rt_sigreturn/mprotect(no PROT_EXEC)/fork...
- `child_errno_action` (function) `progs/src/lxsecc.c:100` `static void child_errno_action(void)`
- `child_kill_action` (function) `progs/src/lxsecc.c:107` `static void child_kill_action(void)`
- `child_wx` (function) `progs/src/lxsecc.c:116` `static void child_wx(void)` -- The page is the child's own anonymous mapping, made before the filter (which forbids mmap): a copy-on-write page...
- `grandchild_inherits` (function) `progs/src/lxsecc.c:127` `static void grandchild_inherits(void)`
- `child_inherit` (function) `progs/src/lxsecc.c:133` `static void child_inherit(void)`
- `child_stacked` (function) `progs/src/lxsecc.c:142` `static void child_stacked(void)`
- `child_strict` (function) `progs/src/lxsecc.c:150` `static void child_strict(void)`
- `child_no_nnp` (function) `progs/src/lxsecc.c:157` `static void child_no_nnp(void)`
- `child_bad_program` (function) `progs/src/lxsecc.c:165` `static void child_bad_program(void)`
- `check_prctl_flags` (function) `progs/src/lxsecc.c:177` `static void check_prctl_flags(void)`
- `check_proc_self_exe` (function) `progs/src/lxsecc.c:197` `static void check_proc_self_exe(const char *argv0)`
- `main` (function) `progs/src/lxsecc.c:215` `int main(int argc, char **argv)`

## progs/src/lxtls.c
Depends on: `kernel/string.c`
- `lxtls_sink` (function) `progs/src/lxtls.c:39` `static size_t lxtls_sink(char *data, size_t size, size_t nmemb, void *user)` -- Count the body without storing it: the probe proves transport, not * content.
- `lxtls_debug` (function) `progs/src/lxtls.c:46` `static int lxtls_debug(CURL *h, curl_infotype type, char *data, size_t size, void *user)` -- Count the body without storing it: the probe proves transport, not * content. static size_t lxtls_sink(char *data...
- `lxtls_step` (function) `progs/src/lxtls.c:65` `static int lxtls_step(const char *name, int ok)` -- return 0; for (i = 0; i <= size; i++) { if (i == size || data[i] == '\n') { size_t len = i - start; if (len > 0 &&...
- `lxtls_rand` (function) `progs/src/lxtls.c:73` `static int lxtls_rand(void)` -- } fflush(stdout); return 0; } /* Report one RAND step and, on failure, OpenSSL's error queue. static int...
- `main` (function) `progs/src/lxtls.c:87` `int main(int argc, char **argv)`

## progs/src/lz4.c
- `kernel` (function) `progs/src/lz4.c:6` `* * The codec lives in the kernel (lz4_kernel.c, the same one MiniFS uses), so * these tools are thin front-ends...`
- `free` (function) `progs/src/lz4.c:15` `void free();`
- `printf` (function) `progs/src/lz4.c:16` `int printf();`
- `strcmp` (function) `progs/src/lz4.c:17` `int strcmp();`
- `strlen` (function) `progs/src/lz4.c:18` `int strlen();`
- `fopen` (function) `progs/src/lz4.c:19` `void *fopen();`
- `fclose` (function) `progs/src/lz4.c:20` `int fclose();`
- `fread` (function) `progs/src/lz4.c:21` `int fread();`
- `fwrite` (function) `progs/src/lz4.c:22` `int fwrite();`
- `fseek` (function) `progs/src/lz4.c:23` `int fseek();`
- `ftell` (function) `progs/src/lz4.c:24` `int ftell();`
- `rewind` (function) `progs/src/lz4.c:25` `void rewind();`
- `lz4_compress` (function) `progs/src/lz4.c:27` `int lz4_compress(char *src, int srclen, char *dst, int dstcap);`
- `lz4_decompress` (function) `progs/src/lz4.c:28` `int lz4_decompress(char *src, int srclen, char *dst, int dstcap);`
- `lz4_has` (function) `progs/src/lz4.c:39` `static int lz4_has(const char *s, const char *needle)`
- `lz4_read_all` (function) `progs/src/lz4.c:53` `static char *lz4_read_all(const char *name, int *len)`
- `lz4_write_all` (function) `progs/src/lz4.c:70` `static int lz4_write_all(const char *name, char *data, int len)`
- `lz4_compress_file` (function) `progs/src/lz4.c:80` `static int lz4_compress_file(const char *src, const char *dst)`
- `lz4_decompress_file` (function) `progs/src/lz4.c:117` `static int lz4_decompress_file(const char *src, const char *dst)`
- `main` (function) `progs/src/lz4.c:164` `int main(int argc, char **argv)`

## progs/src/lzss.c
- `malloc` (function) `progs/src/lzss.c:13` `void *malloc();`
- `free` (function) `progs/src/lzss.c:14` `void free();`
- `printf` (function) `progs/src/lzss.c:15` `int printf();`
- `strcmp` (function) `progs/src/lzss.c:16` `int strcmp();`
- `strlen` (function) `progs/src/lzss.c:17` `int strlen();`
- `fopen` (function) `progs/src/lzss.c:18` `void *fopen();`
- `fclose` (function) `progs/src/lzss.c:19` `int fclose();`
- `fread` (function) `progs/src/lzss.c:20` `int fread();`
- `fwrite` (function) `progs/src/lzss.c:21` `int fwrite();`
- `fseek` (function) `progs/src/lzss.c:22` `int fseek();`
- `ftell` (function) `progs/src/lzss.c:23` `int ftell();`
- `rewind` (function) `progs/src/lzss.c:24` `void rewind();`
- `lz_in_getc` (function) `progs/src/lzss.c:64` `static int lz_in_getc(void)`
- `lz_out_put` (function) `progs/src/lzss.c:69` `static void lz_out_put(int c)`
- `lz_putbit1` (function) `progs/src/lzss.c:74` `static void lz_putbit1(void)`
- `lz_putbit0` (function) `progs/src/lzss.c:84` `static void lz_putbit0(void)`
- `lz_flush_bits` (function) `progs/src/lzss.c:93` `static void lz_flush_bits(void)`
- `lz_out_literal` (function) `progs/src/lzss.c:97` `static void lz_out_literal(int c)`
- `lz_out_pair` (function) `progs/src/lzss.c:105` `static void lz_out_pair(int x, int y)`
- `lz_encode` (function) `progs/src/lzss.c:118` `static int lz_encode(void)`
- `lz_getbit` (function) `progs/src/lzss.c:173` `static int lz_getbit(int n)`
- `lz_decode` (function) `progs/src/lzss.c:189` `static int lz_decode(void)`
- `lz_hdr_put` (function) `progs/src/lzss.c:218` `static void lz_hdr_put(char *h, int size)`
- `lz_hdr_get` (function) `progs/src/lzss.c:229` `static int lz_hdr_get(char *h)`
- `lz_has` (function) `progs/src/lzss.c:237` `static int lz_has(const char *s, const char *needle)`
- `lz_read_all` (function) `progs/src/lzss.c:251` `static char *lz_read_all(const char *name, int *len)`
- `lz_write_all` (function) `progs/src/lzss.c:268` `static int lz_write_all(const char *name, char *data, int len)`
- `lz_compress` (function) `progs/src/lzss.c:278` `static int lz_compress(const char *src, const char *dst)`
- `lz_decompress` (function) `progs/src/lzss.c:325` `static int lz_decompress(const char *src, const char *dst)`
- `main` (function) `progs/src/lzss.c:397` `int main(int argc, char **argv)`

## progs/src/mmreuse.c
- `ENOMEM` (function) `progs/src/mmreuse.c:3` `* downward mmap cursor drains until a map fails with ENOMEM (-12);`
- `mmap_anon` (function) `progs/src/mmreuse.c:7` `static long mmap_anon(long len)` -- mmap/munmap reclaim stress test.
- `munmap` (function) `progs/src/mmreuse.c:21` `static long munmap(long addr, long len)`
- `exit_now` (function) `progs/src/mmreuse.c:31` `static void exit_now(long code)`

## progs/src/mprot.c
- `mmap_anon` (function) `progs/src/mprot.c:11` `static long mmap_anon(long len)`
- `mprotect_sys` (function) `progs/src/mprot.c:25` `static long mprotect_sys(long addr, long len, long prot)`
- `write_str` (function) `progs/src/mprot.c:36` `static long write_str(const char *s, long n)`
- `exit_now` (function) `progs/src/mprot.c:44` `static void exit_now(long code)`

## progs/src/mthreads.h
Depends on: `progs/minios_abi.h`
Imported by: `progs/src/fptest.c`, `progs/src/scfuzz.c`, `progs/src/thdemo.c`
- `m_syscall6` (function) `progs/src/mthreads.h:50` `static inline long m_syscall6(long n, long a, long b, long c)`
- `myield` (function) `progs/src/mthreads.h:59` `static inline void myield(void)`
- `mfutex_wait` (function) `progs/src/mthreads.h:63` `static inline long mfutex_wait(volatile int *addr, int val)`
- `mfutex_wake` (function) `progs/src/mthreads.h:67` `static inline long mfutex_wake(volatile int *addr, int n)`
- `mmutex_init` (function) `progs/src/mthreads.h:71` `static inline void mmutex_init(mmutex_t *m)`
- `mmutex_lock` (function) `progs/src/mthreads.h:75` `static inline void mmutex_lock(mmutex_t *m)`
- `mmutex_unlock` (function) `progs/src/mthreads.h:90` `static inline void mmutex_unlock(mmutex_t *m)`
- `mthread_entry` (function) `progs/src/mthreads.h:98` `static void mthread_entry(void *p)` -- Thread entry trampoline: runs fn(arg), stores the return, exits 0. * The exit code is always 0; join reads retval...
- `mthread_create` (function) `progs/src/mthreads.h:117` `static int mthread_create(mthread_t *t, void *(*fn)(void *), void *arg)`
- `mthread_join` (function) `progs/src/mthreads.h:144` `static int mthread_join(mthread_t t, void **retval)` -- Join: wait4 (Linux semantics) answers the reaped pid and stores the status word; the thread always exits 0, so a...

## progs/src/mtop.c
- `syscall` (function) `progs/src/mtop.c:12` `* * All system figures come from the MINFO syscall (251): heap used / * free, ramdisk used / cap, MiniFS free /...`
- `putchar` (function) `progs/src/mtop.c:35` `int putchar();`
- `strlen` (function) `progs/src/mtop.c:36` `int strlen();`
- `strcmp` (function) `progs/src/mtop.c:37` `int strcmp();`
- `fopen` (function) `progs/src/mtop.c:38` `void *fopen();`
- `fclose` (function) `progs/src/mtop.c:39` `int fclose();`
- `fread` (function) `progs/src/mtop.c:40` `int fread();`
- `rewind` (function) `progs/src/mtop.c:41` `void rewind();`
- `socket` (function) `progs/src/mtop.c:42` `int socket();`
- `close` (function) `progs/src/mtop.c:43` `int close();`
- `net_dns_resolve` (function) `progs/src/mtop.c:44` `int net_dns_resolve();`
- `sc3` (function) `progs/src/mtop.c:63` `static long sc3(long n, long a1, long a2, long a3)`
- `mtop_time` (function) `progs/src/mtop.c:72` `static long mtop_time(void)`
- `mtop_rtc` (function) `progs/src/mtop.c:76` `static long mtop_rtc(int *h, int *m, int *s)`
- `mtop_key` (function) `progs/src/mtop.c:80` `static long mtop_key(void)`
- `mtop_minfo` (function) `progs/src/mtop.c:84` `static long mtop_minfo(long sel, long *o1, long *o2)`
- `emit` (function) `progs/src/mtop.c:90` `static void emit(char *s)`
- `mtop_quit_key` (function) `progs/src/mtop.c:94` `static int mtop_quit_key(long k)`
- `mtop_clear_ansi` (function) `progs/src/mtop.c:103` `static void mtop_clear_ansi(void)`
- `mtop_clear` (function) `progs/src/mtop.c:113` `static void mtop_clear(void)`
- `mtop_atoi` (function) `progs/src/mtop.c:117` `static int mtop_atoi(char *s)`
- `mtop_putu` (function) `progs/src/mtop.c:136` `static void mtop_putu(long v)`
- `mtop_put2` (function) `progs/src/mtop.c:158` `static void mtop_put2(int v)`
- `mtop_put_kb` (function) `progs/src/mtop.c:163` `static void mtop_put_kb(long kb)`
- `mtop_bar` (function) `progs/src/mtop.c:179` `static void mtop_bar(long v, long max, int w)`
- `mtop_hist_max` (function) `progs/src/mtop.c:194` `static long mtop_hist_max(long *h, int n)`
- `mtop_hist_push` (function) `progs/src/mtop.c:204` `static void mtop_hist_push(long *h, long v)`
- `mtop_spark` (function) `progs/src/mtop.c:214` `static void mtop_spark(long *h, int n)`
- `mtop_mem` (function) `progs/src/mtop.c:242` `static long mtop_mem(long *used, long *freeb, long *total)`
- `mtop_cpu` (function) `progs/src/mtop.c:253` `static long mtop_cpu(long *count, long *busy)`
- `mtop_disk_open` (function) `progs/src/mtop.c:289` `static void mtop_disk_open(void)`
- `mtop_disk_read` (function) `progs/src/mtop.c:313` `static long mtop_disk_read(long *bytes)`
- `mtop_net_probe` (function) `progs/src/mtop.c:337` `static long mtop_net_probe(long *dns_ms, long *sock_ok)`
- `mtop_frame` (function) `progs/src/mtop.c:355` `static void mtop_frame(int n)`
- `main` (function) `progs/src/mtop.c:531` `int main(int argc, char **argv)`

## progs/src/mvrn.c
- `mvrn_sc3` (function) `progs/src/mvrn.c:9` `static long mvrn_sc3(long n, long a1, long a2, long a3)` -- mvrn -- rename(82) syscall probe.
- `mvrn_write` (function) `progs/src/mvrn.c:16` `static void mvrn_write(const char *s, unsigned long len)`
- `mvrn_exit` (function) `progs/src/mvrn.c:20` `static void mvrn_exit(long code)`
- `mvrn_fail` (function) `progs/src/mvrn.c:24` `static void mvrn_fail(int step)`
- `lmain` (function) `progs/src/mvrn.c:32` `int lmain(void)`

## progs/src/nx.c
- `write_str` (function) `progs/src/nx.c:11` `static long write_str(const char *s, long n)`
- `exit_now` (function) `progs/src/nx.c:19` `static void exit_now(long code)`

## progs/src/opl3.c
Depends on: `kernel/string.c`, `progs/minios_abi.h`
Imported by: `progs/piano/piano.c`
- `sys_time` (function) `progs/src/opl3.c:36` `static long sys_time(void)`
- `sys_open` (function) `progs/src/opl3.c:39` `static long sys_open(long on)`
- `sys_submit` (function) `progs/src/opl3.c:42` `static long sys_submit(const void *buf, long len)`
- `busy_ms` (function) `progs/src/opl3.c:46` `static void busy_ms(long ms)`
- `opl3_set_instrument` (function) `progs/src/opl3.c:52` `static void opl3_set_instrument(opl3_chip *chip)` -- } static long sys_open(long on) { long r; __asm__ volatile("syscall":"=a"(r):"a"(SYS_SB16_OPEN),"D"(on):"rcx","r11","...
- `opl3_note` (function) `progs/src/opl3.c:69` `static void opl3_note(opl3_chip *chip, unsigned block, unsigned fnum, int on)`
- `render` (function) `progs/src/opl3.c:77` `static void render(opl3_chip *chip, long ms, long *fail)` -- Render `ms` of the current note and stream it to the SB16.
- `main` (function) `progs/src/opl3.c:107` `int main(void)`

## progs/src/pcmap.c
- `sc_open` (function) `progs/src/pcmap.c:12` `static long sc_open(const char *p)` -- pcmap probe: file-backed MAP_PRIVATE mmap shares text.
- `sc_mmap` (function) `progs/src/pcmap.c:21` `static long sc_mmap(long len, long prot, long flags, long fd, long off)`
- `sc_write` (function) `progs/src/pcmap.c:34` `static long sc_write(long fd, const char *s, long n)`
- `sc_exit` (function) `progs/src/pcmap.c:42` `static void sc_exit(long code)`
- `sc_fnv` (function) `progs/src/pcmap.c:46` `static unsigned long sc_fnv(const char *p, long n)`
- `sc_hex8` (function) `progs/src/pcmap.c:56` `static void sc_hex8(unsigned long v, char *out)`
- `sc_munmap` (function) `progs/src/pcmap.c:65` `static long sc_munmap(long addr, long len)`

## progs/src/pollready.c
- `p_write` (function) `progs/src/pollready.c:26` `static long p_write(long fd, const char *s, long n)`
- `p_strlen` (function) `progs/src/pollready.c:30` `static unsigned long p_strlen(const char *s)`
- `p_puts` (function) `progs/src/pollready.c:36` `static void p_puts(long fd, const char *s)`
- `p_atoi` (function) `progs/src/pollready.c:40` `static int p_atoi(const char *s)`
- `p_parse_ip` (function) `progs/src/pollready.c:46` `static int p_parse_ip(const char *s, unsigned char out[4])`
- `lmain` (function) `progs/src/pollready.c:63` `int lmain(long argc, char **argv)` -- int v = 0; int digits = 0; while (*s >= '0' && *s <= '9') { v = v * 10 + (*s - '0'); s++; digits++; } if (!digits ||...

## progs/src/sbtone.c
Depends on: `progs/minios_abi.h`
- `buffers` (function) `progs/src/sbtone.c:14` `*
 * Exit code is the number of submitted buffers (0 on failure to open).
 */

#include <stdio.h>...`
- `main` (function) `progs/src/sbtone.c:36` `int main(void)`

## progs/src/scfuzz.c
Depends on: `progs/src/mthreads.h`
- `guest` (function) `progs/src/scfuzz.c:7` `* the guest (the BDD timeout then talks). All fuzz maps stay inside
 * one private 4 MB arena (pa...`
- `sc_mprotect` (function) `progs/src/scfuzz.c:38` `static long sc_mprotect(long addr, long len, long prot)`
- `sc_munmap` (function) `progs/src/scfuzz.c:49` `static long sc_munmap(long addr, long len)`
- `sc_write` (function) `progs/src/scfuzz.c:53` `static long sc_write(long fd, const char *s, long n)`
- `sc_exit` (function) `progs/src/scfuzz.c:61` `static void sc_exit(long code)`
- `sc_rng` (function) `progs/src/scfuzz.c:67` `static unsigned long sc_rng(unsigned long *s)`
- `sc_fold` (function) `progs/src/scfuzz.c:76` `static unsigned long sc_fold(unsigned long h, unsigned long v)`
- `sc_hex8` (function) `progs/src/scfuzz.c:88` `static void sc_hex8(unsigned long v, char *out)`
- `sc_worker` (function) `progs/src/scfuzz.c:97` `static unsigned long sc_worker(int me, unsigned long seed)`
- `sc_thread1` (function) `progs/src/scfuzz.c:154` `static void *sc_thread1(void *arg)`

## progs/src/shell.py
Depends on: `progs/lua/minios.c`
- `run_capture` (function) `progs/src/shell.py:20` `def run_capture(cmd, args)`
- `expand` (function) `progs/src/shell.py:30` `def expand(line, env)`
- `main` (function) `progs/src/shell.py:36` `def main()`

## progs/src/spin.c
- `lx_syscall3` (function) `progs/src/spin.c:11` `static long lx_syscall3(long n, long a1, long a2, long a3)`
- `lx_strlen` (function) `progs/src/spin.c:20` `static unsigned long lx_strlen(const char *s)`
- `lx_write` (function) `progs/src/spin.c:26` `static void lx_write(const char *s)`
- `lx_write_int` (function) `progs/src/spin.c:30` `static void lx_write_int(long v)`
- `lx_atoi` (function) `progs/src/spin.c:42` `static long lx_atoi(const char *s)`
- `spin_u32` (function) `progs/src/spin.c:66` `static void spin_u32(unsigned char *d, unsigned long v)`
- `spin_hdr` (function) `progs/src/spin.c:73` `static void spin_hdr(unsigned char *d, unsigned long id, unsigned long op,
        unsigned long ...`
- `spin_box_ok` (function) `progs/src/spin.c:82` `static int spin_box_ok(const char *box)`
- `spin_hex8` (function) `progs/src/spin.c:95` `static void spin_hex8(unsigned int v, char *dst)`
- `spin_write_all` (function) `progs/src/spin.c:104` `static long spin_write_all(long fd, const unsigned char *buf, long len)`
- `spin_emit` (function) `progs/src/spin.c:114` `static int spin_emit(const char *box, unsigned int seq,
        const unsigned char *msg, long mlen)`
- `spin_raw_file` (function) `progs/src/spin.c:145` `static int spin_raw_file(const char *box)`
- `spin_pixels` (function) `progs/src/spin.c:169` `static void spin_pixels(long off)`
- `spin_wl` (function) `progs/src/spin.c:181` `static int spin_wl(const char *box, const char *narg)`
- `lmain` (function) `progs/src/spin.c:225` `int lmain(long argc, char **argv)`

## progs/src/thdemo.c
Depends on: `progs/minios_abi.h`, `progs/src/mthreads.h`
- `threads` (function) `progs/src/thdemo.c:3` `* * Ten threads (1 main + 5 producers + 4 consumers) share one address * space through thread_spawn (MiniOS syscall...`
- `producer` (function) `progs/src/thdemo.c:36` `static void *producer(void *p)`
- `consumer` (function) `progs/src/thdemo.c:57` `static void *consumer(void *p)`
- `main` (function) `progs/src/thdemo.c:82` `int main(void)`

## progs/src/w1.c
- `write` (function) `progs/src/w1.c:1` `int write(int fd, char *buf, int n);`
- `main` (function) `progs/src/w1.c:3` `int main(void)`

## progs/tls_u/tls_u_main.c
Depends on: `headers/tls.h`, `headers/tls_port.h`, `kernel/string.c`
- `syscall` (function) `progs/tls_u/tls_u_main.c:10` `* the MiniOS DNS syscall (200, sig 0: error-check only, sends nothing).
 * The kernel keeps servi...`
- `parse_port` (function) `progs/tls_u/tls_u_main.c:47` `static int parse_port(const char *s)` -- Strict port parser (clang-tidy cert-err34-c: atoi reports no errors, so "abc" and overflow both become 0 and fail...
- `main` (function) `progs/tls_u/tls_u_main.c:61` `int main(int argc, char **argv)`

## progs/tls_u/tls_u_port.c
Depends on: `kernel/string.c`, `kernel/time.c`
- `sockets` (function) `progs/tls_u/tls_u_port.c:5` `* sockets: on the host they are host sockets (used by the
 * openssl-s_server interop test), insi...`
- `tls_u_recv` (function) `progs/tls_u/tls_u_port.c:39` `int tls_u_recv(int fd, char *buf, int len)`
- `tls_u_recv_timeout` (function) `progs/tls_u/tls_u_port.c:44` `int tls_u_recv_timeout(int fd, char *buf, int len, unsigned long ms)`
- `tls_u_close` (function) `progs/tls_u/tls_u_port.c:55` `void tls_u_close(int fd)`
- `tls_free_fd` (function) `progs/tls_u/tls_u_port.c:66` `void tls_free_fd(int fd);` -- Session-aware close for multi-fetch processes (freedom follows redirects and linked stylesheets, reusing the lowest...
- `tls_close` (function) `progs/tls_u/tls_u_port.c:67` `void tls_close(int fd)` -- Session-aware close for multi-fetch processes (freedom follows redirects and linked stylesheets, reusing the lowest...
- `tls_now_days` (function) `progs/tls_u/tls_u_port.c:72` `long tls_now_days(void)`
- `tls_random` (function) `progs/tls_u/tls_u_port.c:78` `void tls_random(unsigned char *out, unsigned len)`
- `u_raw_syscall3` (function) `progs/tls_u/tls_u_port.c:99` `static long u_raw_syscall3(long n, long a1, long a2, long a3)`
- `parse_quad` (function) `progs/tls_u/tls_u_port.c:122` `static int parse_quad(const char *s, unsigned *ip_out)` -- Strict dotted-quad parser (clang-tidy cert-err34-c: sscanf %u has undefined overflow and accepts whitespace/sign, so...
- `tls_u_resolve` (function) `progs/tls_u/tls_u_port.c:147` `int tls_u_resolve(const char *host, unsigned *ip_out)`
- `answer` (function) `progs/tls_u/tls_u_port.c:163` `* answer (some resolvers go IPv6-only on the first query). */ memset(&hints, 0, sizeof(hints));`
- `net_dns_resolve` (function) `progs/tls_u/tls_u_port.c:183` `int net_dns_resolve(const char *host)` -- freedom's resolver name: kernel DNS value semantics (u32 host order, * -1 on failure).


Next: [API_p18.md](API_p18.md)
