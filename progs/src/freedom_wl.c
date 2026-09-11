/** freedom_wl - Wayland to MiniOS intermediate layer for FreeDom.
 *
 * Maps the Wayland client subset used by FreeDom gui/ui_render onto
 * MiniOS syscalls, following the doomgeneric_minios precedent. A
 * Wayland surface becomes the Nuklear back-buffer window. Present
 * routes through GFX_PRESENT with BUF_NK. Title routes through
 * GFX_SET_TITLE. Pointer and keyboard route through MOUSE and KBD.
 * All layout facts come from minios_abi.h. All tunables live in
 * FreedomWlConfig. No absolute paths. Fail-closed on every bound.
 *
 * Beyond the mapping, this file is a complete graphical browser:
 * the FreeDom omnibox policy (bare host fetches as https, any
 * non-http scheme becomes a search, explicit http stays http),
 * an HTTP/1.0 fetch over the socket syscalls with DNS from syscall
 * 200 and https through the shared ring-3 TLS engine (no key
 * material crosses ring 0, exactly like bin/freedom), an HTML to
 * text filter, a fixed 100x45 text layout over the shared 8x8 font,
 * and an input loop with keyboard and wheel scroll. Remote pages
 * are hostile data: every byte passes a gate before reaching the
 * back-buffer.
 *
 * Build guest as static ELF on MiniFS. Build host test with
 * FREEDOM_WL_HOST_TEST for pure logic without syscalls.
 *
 * Usage guest: freedom_wl --selftest renders one frame and verifies
 * the composite origin, mirroring the Nuklear selftest contract.
 * Usage guest: freedom_wl [--once] <url-or-query> fetches, renders
 * and presents; without --once an input loop drives scroll until
 * q or ESC quits.
 */
#include "minios_abi.h"
#include "vga_fb.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/socket.h>

int net_dns_resolve(const char *host);
int tls_handshake(int fd, char *host);
int tls_send(int fd, char *buf, int len);
int tls_recv(int fd, char *buf, int len);
void tls_close(int fd);

/** Named limits for the browser. */
#define WL_COLS 100L
#define WL_ROWS 45L
#define WL_TEXT_ROWS 44L
#define WL_LINES_MAX 2048L
#define WL_LINE_LEN 100L
#define WL_BODY_CAP 262144L
#define WL_HDR_MAX 16384L
#define WL_NET_BUF 768L
#define WL_REQ_MAX 768L
#define WL_HOST_MAX 64L
#define WL_PATH_MAX 128L
#define WL_URL_MAX 192L
#define WL_HOPS_MAX 3L
#define WL_FONT_W 8L
#define WL_FONT_H 8L
#define WL_TAG_MAX 16L
#define WL_ENT_MAX 10L

/** Shared 8x8 bitmap font, one copy in progs/nuklear/font8x8.c. */
extern const uint8_t nk_font8x8[96][8];

/** Well-known network endpoints. */
static const char WL_SEARCH_HOST[] = "html.duckduckgo.com";
static const char WL_SEARCH_PREFIX[] = "/html/?q=";
static const char WL_USER_AGENT[] = "freedom_wl/1.0 (MiniOS)";

/** Centralized configuration for the Wayland to MiniOS mapping. */
typedef struct FreedomWlConfig {
    long present_buf;
    long surface_w;
    long surface_h;
    long title_max;
    long mouse_words;
    long origin_words;
    long scroll_step;
    long btn_left;
    long key_esc;
    long key_enter;
    long cols;
    long rows;
    long text_rows;
    long lines_max;
    long line_len;
    long body_cap;
    long hdr_max;
    long net_buf;
    long req_max;
    long host_max;
    long path_max;
    long url_max;
    long hops_max;
    long font_w;
    long font_h;
    long port_http;
    long port_https;
    long ink_bg;
    long ink_fg;
    long bar_bg;
    long bar_fg;
} FreedomWlConfig;

/** Default configuration derived from the ABI header. */
static FreedomWlConfig freedom_wl_default(void) {
    FreedomWlConfig c;
    c.present_buf = (long)MINIOS_GFX_BUF_NK;
    c.surface_w = (long)MINIOS_NK_W;
    c.surface_h = (long)MINIOS_NK_H;
    c.title_max = 31L;
    c.mouse_words = 4L;
    c.origin_words = 2L;
    c.scroll_step = 3L;
    c.btn_left = 1L;
    c.key_esc = 27L;
    c.key_enter = 13L;
    c.cols = WL_COLS;
    c.rows = WL_ROWS;
    c.text_rows = WL_TEXT_ROWS;
    c.lines_max = WL_LINES_MAX;
    c.line_len = WL_LINE_LEN;
    c.body_cap = WL_BODY_CAP;
    c.hdr_max = WL_HDR_MAX;
    c.net_buf = WL_NET_BUF;
    c.req_max = WL_REQ_MAX;
    c.host_max = WL_HOST_MAX;
    c.path_max = WL_PATH_MAX;
    c.url_max = WL_URL_MAX;
    c.hops_max = WL_HOPS_MAX;
    c.font_w = WL_FONT_W;
    c.font_h = WL_FONT_H;
    c.port_http = 80L;
    c.port_https = 443L;
    c.ink_bg = (long)COL_TERMINAL;
    c.ink_fg = (long)COL_TERM_TXT;
    c.bar_bg = (long)COL_TITLEBAR;
    c.bar_fg = (long)COL_TITLE_TXT;
    return c;
}

/** Clamp a dirty rect into the surface bounds. */
static long freedom_wl_clip_rect(FreedomWlConfig *c, long *x, long *y, long *w, long *h) {
    if (!c || !x || !y || !w || !h) {
        return -1L;
    }
    if (*w <= 0L || *h <= 0L) {
        return -1L;
    }
    if (*x < 0L) {
        *w += *x;
        *x = 0L;
    }
    if (*y < 0L) {
        *h += *y;
        *y = 0L;
    }
    if (*x >= c->surface_w || *y >= c->surface_h) {
        return -1L;
    }
    if (*x + *w > c->surface_w) {
        *w = c->surface_w - *x;
    }
    if (*y + *h > c->surface_h) {
        *h = c->surface_h - *y;
    }
    if (*w <= 0L || *h <= 0L) {
        return -1L;
    }
    return 0L;
}

/** Expected byte size of the shared-memory frame for given geometry. */
static long freedom_wl_frame_bytes(FreedomWlConfig *c, long w, long h) {
    long bytes_per_pixel;
    if (!c) {
        return -1L;
    }
    if (w <= 0L || h <= 0L) {
        return -1L;
    }
    if (w > c->surface_w || h > c->surface_h) {
        return -1L;
    }
    bytes_per_pixel = 1L;
    if (w > 0x7FFFFFFFL / (h * bytes_per_pixel)) {
        return -1L;
    }
    return w * h * bytes_per_pixel;
}

/** Translate a PS/2 Set 1 scancode base into a keysym. */
static long freedom_wl_keysym(FreedomWlConfig *c, long sc) {
    long make;
    if (!c) {
        return -1L;
    }
    if (sc < 0L || sc > 255L) {
        return -1L;
    }
    make = sc & 0x7FL;
    if (make == 0x01L) {
        return c->key_esc;
    }
    if (make == 0x1CL) {
        return c->key_enter;
    }
    if (make >= 0x02L && make <= 0x0BL) {
        return (long)"1234567890"[make - 0x02L];
    }
    if (make >= 0x10L && make <= 0x19L) {
        return (long)"qwertyuiop"[make - 0x10L];
    }
    if (make >= 0x1EL && make <= 0x26L) {
        return (long)"asdfghjkl"[make - 0x1EL];
    }
    if (make >= 0x2CL && make <= 0x32L) {
        return (long)"zxcvbnm"[make - 0x2CL];
    }
    if (make == 0x39L) {
        return 32L;
    }
    if (make == 0x0EL) {
        return 8L;
    }
    if (make == 0x0FL) {
        return 9L;
    }
    return -1L;
}

/** Rewrite a buffer in place to well-formed UTF-8. */
static long freedom_wl_sanitize_utf8(char *s, long cap) {
    long i;
    long o;
    unsigned long cu;
    long len;
    long ok;
    long k;
    if (!s || cap <= 0L) {
        return -1L;
    }
    i = 0L;
    o = 0L;
    while (s[i] != 0 && i < cap) {
        cu = (unsigned long)(unsigned char)s[i];
        len = 0L;
        if (cu < 0x80UL) {
            len = 1L;
        } else if (cu >= 0xC2UL && cu <= 0xDFUL) {
            len = 2L;
        } else if (cu >= 0xE0UL && cu <= 0xEFUL) {
            len = 3L;
        } else if (cu >= 0xF0UL && cu <= 0xF4UL) {
            len = 4L;
        } else {
            len = 0L;
        }
        ok = (len >= 1L);
        if (ok) {
            k = 1L;
            while (k < len) {
                if ((((unsigned char)s[i + k]) & 0xC0U) != 0x80U) {
                    ok = 0L;
                }
                k++;
            }
        }
        if (ok && len == 3L && cu == 0xE0UL && (unsigned char)s[i + 1L] < 0xA0U) {
            ok = 0L;
        }
        if (ok && len == 3L && cu == 0xEDUL && (unsigned char)s[i + 1L] > 0x9FUL) {
            ok = 0L;
        }
        if (ok && len == 4L && cu == 0xF0UL && (unsigned char)s[i + 1L] < 0x90U) {
            ok = 0L;
        }
        if (ok && len == 4L && cu == 0xF4UL && (unsigned char)s[i + 1L] > 0x8FUL) {
            ok = 0L;
        }
        if (ok) {
            k = 0L;
            while (k < len) {
                s[o] = s[i + k];
                o++;
                k++;
            }
            i += len;
        } else {
            s[o] = '?';
            o++;
            i++;
        }
        if (o >= cap - 1L) {
            break;
        }
    }
    if (o >= cap) {
        return -1L;
    }
    s[o] = 0;
    return o;
}

/** Validate a window title against the kernel title bound. */
static long freedom_wl_title_ok(FreedomWlConfig *c, char *t, long n) {
    if (!c || !t) {
        return -1L;
    }
    if (n < 0L || n > c->title_max) {
        return -1L;
    }
    return 0L;
}

/** Bounded string copy with NUL termination. */
static long wl_copy(char *dst, char *src, long cap) {
    long i;
    if (!dst || !src || cap <= 0L) {
        return -1L;
    }
    i = 0L;
    while (src[i] != 0) {
        if (i + 1L >= cap) {
            return -1L;
        }
        dst[i] = src[i];
        i++;
    }
    dst[i] = 0;
    return 0L;
}

/** Bounded string length. */
static long wl_strlen(char *s, long cap) {
    long i;
    if (!s || cap <= 0L) {
        return -1L;
    }
    i = 0L;
    while (i < cap && s[i] != 0) {
        i++;
    }
    if (i >= cap) {
        return -1L;
    }
    return i;
}

/** Bounded append of src at dst[pos]. */
static long wl_append(char *dst, long pos, char *src, long cap) {
    long n;
    long i;
    if (!dst || !src || pos < 0L || cap <= 0L) {
        return -1L;
    }
    n = wl_strlen(src, cap);
    if (n < 0L) {
        return -1L;
    }
    if (pos + n >= cap) {
        return -1L;
    }
    i = 0L;
    while (i < n) {
        dst[pos + i] = src[i];
        i++;
    }
    dst[pos + n] = 0;
    return pos + n;
}

/** ASCII lowercase fold. */
static long wl_ci_lower(long ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return ch + ('a' - 'A');
    }
    return ch;
}

/** Case-insensitive prefix match. */
static long wl_ci_starts(char *s, char *pre) {
    if (!s || !pre) {
        return 0L;
    }
    while (*pre) {
        if (*s == 0) {
            return 0L;
        }
        if (wl_ci_lower(*s) != wl_ci_lower(*pre)) {
            return 0L;
        }
        s++;
        pre++;
    }
    return 1L;
}

/** Case-insensitive substring search. */
static long wl_ci_contains(char *s, char *needle) {
    if (!s || !needle) {
        return 0L;
    }
    while (*s) {
        if (wl_ci_starts(s, needle)) {
            return 1L;
        }
        s++;
    }
    return 0L;
}

/** RFC 3986 scheme probe: ALPHA *(ALPHA/DIGIT/+/-/.) then colon. */
static long wl_has_scheme(char *s) {
    long i;
    long ch;
    if (!s || !s[0]) {
        return 0L;
    }
    ch = s[0];
    if (!((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))) {
        return 0L;
    }
    i = 1L;
    while (s[i]) {
        ch = s[i];
        if (ch == ':') {
            return 1L;
        }
        if (!((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') ||
              (ch >= '0' && ch <= '9') || ch == '+' || ch == '-' || ch == '.')) {
            return 0L;
        }
        i++;
    }
    return 0L;
}

/** Omnibox URL probe: no spaces and at least one dot. */
static long wl_looks_like_url(char *s) {
    long dot;
    if (!s) {
        return 0L;
    }
    dot = 0L;
    while (*s) {
        if (*s == ' ' || *s == '\t') {
            return 0L;
        }
        if (*s == '.') {
            dot = 1L;
        }
        s++;
    }
    return dot;
}

/** Encode a query for the no-JS search endpoint. */
static long wl_make_search(char *out, char *query, long cap) {
    long pos;
    if (!out || !query || cap <= 0L) {
        return -1L;
    }
    pos = wl_append(out, 0L, (char *)WL_SEARCH_PREFIX, cap);
    if (pos < 0L) {
        return -1L;
    }
    while (*query && pos < cap - 4L) {
        if (*query == ' ') {
            pos = wl_append(out, pos, "+", cap);
        } else if (*query == '&') {
            pos = wl_append(out, pos, "%26", cap);
        } else if (*query == '=') {
            pos = wl_append(out, pos, "%3D", cap);
        } else if (*query == '+') {
            pos = wl_append(out, pos, "%2B", cap);
        } else {
            out[pos] = *query;
            pos++;
            out[pos] = 0;
        }
        if (pos < 0L) {
            return -1L;
        }
        query++;
    }
    return pos;
}

/** Split an http(s) URL into host, path, port and secure flag. */
static long wl_split_url(FreedomWlConfig *c, char *url, char *host, char *path, long *port, long *secure) {
    char *p;
    long hl;
    long k;
    long v;
    long plen;
    if (!c || !url || !host || !path || !port || !secure) {
        return 0L;
    }
    if (wl_ci_starts(url, "https://")) {
        *secure = 1L;
        *port = c->port_https;
        p = url + 8L;
    } else if (wl_ci_starts(url, "http://")) {
        *secure = 0L;
        *port = c->port_http;
        p = url + 7L;
    } else {
        return 0L;
    }
    hl = 0L;
    while (p[hl] && p[hl] != ':' && p[hl] != '/' && hl < c->host_max) {
        hl++;
    }
    if (hl < 1L || hl >= c->host_max) {
        return 0L;
    }
    k = 0L;
    while (k < hl) {
        host[k] = p[k];
        k++;
    }
    host[hl] = 0;
    if (p[hl] == ':') {
        k = hl + 1L;
        v = 0L;
        while (p[k] >= '0' && p[k] <= '9') {
            v = v * 10L + (p[k] - '0');
            k++;
        }
        if (v <= 0L || v > 65535L) {
            return 0L;
        }
        if (p[k] != '/' && p[k] != 0) {
            return 0L;
        }
        *port = v;
        hl = k;
    }
    if (p[hl] == '/') {
        plen = wl_strlen(p + hl, c->path_max);
        if (plen < 0L) {
            return 0L;
        }
        if (wl_copy(path, p + hl, c->path_max) < 0L) {
            return 0L;
        }
    } else {
        path[0] = '/';
        path[1] = 0;
    }
    return 1L;
}

/** Recompute host/path/port/secure from a Location value. */
static long wl_resolve_redirect(FreedomWlConfig *c, char *loc, long secure, char *host, char *path, long *port, long *newsecure) {
    char tmp[WL_URL_MAX];
    long pos;
    long i;
    long last;
    long plen;
    long l;
    if (!c || !loc || !host || !path || !port || !newsecure) {
        return 0L;
    }
    if (wl_ci_starts(loc, "https://") || wl_ci_starts(loc, "http://")) {
        return wl_split_url(c, loc, host, path, port, newsecure);
    }
    if (loc[0] == '/' && loc[1] == '/') {
        if (secure) {
            pos = wl_append(tmp, 0L, "https:", c->url_max);
        } else {
            pos = wl_append(tmp, 0L, "http:", c->url_max);
        }
        if (pos < 0L) {
            return 0L;
        }
        pos = wl_append(tmp, pos, loc, c->url_max);
        if (pos < 0L) {
            return 0L;
        }
        return wl_split_url(c, tmp, host, path, port, newsecure);
    }
    if (wl_has_scheme(loc)) {
        return -1L;
    }
    *newsecure = secure;
    if (loc[0] == '/') {
        if (wl_copy(path, loc, c->path_max) < 0L) {
            return 0L;
        }
        return 1L;
    }
    plen = wl_strlen(path, c->path_max);
    if (plen < 0L) {
        return 0L;
    }
    last = -1L;
    i = 0L;
    while (i < plen) {
        if (path[i] == '/') {
            last = i;
        }
        i++;
    }
    l = wl_strlen(loc, c->path_max);
    if (l < 0L) {
        return 0L;
    }
    if (last < 0L) {
        if (l + 1L >= c->path_max) {
            return 0L;
        }
        path[0] = '/';
        i = 0L;
        while (i < l) {
            path[1L + i] = loc[i];
            i++;
        }
        path[1L + l] = 0;
    } else {
        if (last + 1L + l >= c->path_max) {
            return 0L;
        }
        i = 0L;
        while (i < l) {
            path[last + 1L + i] = loc[i];
            i++;
        }
        path[last + 1L + l] = 0;
    }
    return 1L;
}

/** Clamp a scroll offset into the page range. */
static long wl_scroll_clamp(FreedomWlConfig *c, long off, long nlines) {
    long maxoff;
    if (!c) {
        return 0L;
    }
    if (nlines <= c->text_rows) {
        return 0L;
    }
    maxoff = nlines - c->text_rows;
    if (off < 0L) {
        return 0L;
    }
    if (off > maxoff) {
        return maxoff;
    }
    return off;
}

/** HTML to wrapped text lines over a flat line array. */
static long wl_filter_wrap(FreedomWlConfig *c, char *body, long n, char *lines, long maxlines, long linelen) {
    long li;
    long co;
    long i;
    long intag;
    long incomment;
    long suppress;
    long closing;
    long tagnlen;
    long entlen;
    long entemit;
    long entdone;
    long k;
    long v;
    long d;
    char tag[WL_TAG_MAX];
    char ent[WL_ENT_MAX];
    char name[WL_TAG_MAX];
    if (!c || !body || !lines || maxlines <= 0L || linelen <= 0L) {
        return 0L;
    }
    li = 0L;
    co = 0L;
    lines[0] = 0;
    i = 0L;
    intag = 0L;
    incomment = 0L;
    suppress = 0L;
    closing = 0L;
    tagnlen = 0L;
    entlen = -1L;
    while (i < n) {
        long ch;
        ch = (unsigned char)body[i];
        i++;
        entdone = 0L;
        if (incomment) {
            if (ch == '>' && i >= 3L && body[i - 2L] == '-' && body[i - 3L] == '-') {
                incomment = 0L;
            }
            continue;
        }
        if (intag) {
            if (ch == '>') {
                long ni;
                ni = 0L;
                k = 0L;
                while (k < tagnlen && tag[k] != ' ' && tag[k] != '\t' && tag[k] != '/') {
                    if (ni + 1L < WL_TAG_MAX) {
                        name[ni] = tag[k];
                        ni++;
                    }
                    k++;
                }
                name[ni] = 0;
                k = 0L;
                while (name[k]) {
                    if (name[k] >= 'A' && name[k] <= 'Z') {
                        name[k] = name[k] + ('a' - 'A');
                    }
                    k++;
                }
                intag = 0L;
                tagnlen = 0L;
                if ((name[0] == 's' && name[1] == 'c' && name[2] == 'r' && name[3] == 'i' && name[4] == 'p' && name[5] == 't' && name[6] == 0) ||
                    (name[0] == 's' && name[1] == 't' && name[2] == 'y' && name[3] == 'l' && name[4] == 'e' && name[5] == 0)) {
                    if (closing) {
                        suppress = 0L;
                    } else {
                        suppress = 1L;
                    }
                } else if (suppress) {
                    continue;
                } else if (name[0] == 'b' && name[1] == 'r' && name[2] == 0) {
                    goto wl_newline;
                } else if (name[0] == 'p' && (name[1] == 0 || name[1] == ' ')) {
                    goto wl_newline;
                } else if (name[0] == 'd' && name[1] == 'i' && name[2] == 'v') {
                    goto wl_newline;
                } else if (name[0] == 'l' && name[1] == 'i' && name[2] == 0) {
                    goto wl_newline;
                } else if (name[0] == 't' && name[1] == 'r' && name[2] == 0) {
                    goto wl_newline;
                } else if (name[0] == 'h' && name[1] >= '1' && name[1] <= '6' && name[2] == 0) {
                    goto wl_newline;
                }
                continue;
wl_newline:
                if (co > 0L || li == 0L) {
                    li++;
                    if (li >= maxlines) {
                        li = maxlines - 1L;
                        lines[li * linelen] = 0;
                        return li + 1L;
                    }
                    co = 0L;
                    lines[li * linelen] = 0;
                }
                continue;
            }
            if (tagnlen + 1L < WL_TAG_MAX) {
                tag[tagnlen] = (char)ch;
                tagnlen++;
            }
            continue;
        }
        if (entlen >= 0L) {
            if (ch == '<') {
                entlen = -1L;
            } else if (ch == ';') {
                ent[entlen] = 0;
                entemit = -1L;
                if (ent[0] == 'l' && ent[1] == 't' && ent[2] == 0) {
                    entemit = '<';
                } else if (ent[0] == 'g' && ent[1] == 't' && ent[2] == 0) {
                    entemit = '>';
                } else if (ent[0] == 'a' && ent[1] == 'm' && ent[2] == 'p' && ent[3] == 0) {
                    entemit = '&';
                } else if (ent[0] == 'q' && ent[1] == 'u' && ent[2] == 'o' && ent[3] == 't' && ent[4] == 0) {
                    entemit = '"';
                } else if (ent[0] == '#') {
                    v = 0L;
                    k = 1L;
                    if (ent[1] == 'x' || ent[1] == 'X') {
                        k = 2L;
                        while (ent[k]) {
                            d = -1L;
                            if (ent[k] >= '0' && ent[k] <= '9') {
                                d = ent[k] - '0';
                            } else if (ent[k] >= 'a' && ent[k] <= 'f') {
                                d = ent[k] - 'a' + 10L;
                            } else if (ent[k] >= 'A' && ent[k] <= 'F') {
                                d = ent[k] - 'A' + 10L;
                            }
                            if (d < 0L) {
                                break;
                            }
                            v = v * 16L + d;
                            k++;
                        }
                        if (ent[k] == 0 && k > 2L) {
                            entemit = v;
                        }
                    } else {
                        while (ent[k] >= '0' && ent[k] <= '9') {
                            v = v * 10L + (ent[k] - '0');
                            k++;
                        }
                        if (ent[k] == 0 && k > 1L) {
                            entemit = v;
                        }
                    }
                }
                entlen = -1L;
                entdone = 1L;
                if (entemit < 32L || entemit > 126L) {
                    entemit = '?';
                }
                ch = entemit;
            } else if (entlen + 1L < WL_ENT_MAX) {
                ent[entlen] = (char)ch;
                entlen++;
                continue;
            } else {
                entlen = -1L;
            }
        }
        if (!entdone && ch == '<') {
            if (i + 3L <= n && body[i] == '!' && body[i + 1L] == '-' && body[i + 2L] == '-') {
                incomment = 1L;
                i += 3L;
            } else {
                intag = 1L;
                tagnlen = 0L;
                if (i < n && body[i] == '/') {
                    closing = 1L;
                    i++;
                } else {
                    closing = 0L;
                }
            }
            continue;
        }
        if (suppress) {
            continue;
        }
        if (!entdone && ch == '&') {
            entlen = 0L;
            continue;
        }
        if (ch == '\r') {
            continue;
        }
        if (ch == '\n' || ch == '\t') {
            ch = (ch == '\n') ? -2L : 32L;
        } else if (ch == 32L) {
            ch = 32L;
        } else if (ch < 32L || ch > 126L) {
            ch = '?';
        }
        if (ch == -2L) {
            if (co > 0L || li == 0L) {
                li++;
                if (li >= maxlines) {
                    li = maxlines - 1L;
                    lines[li * linelen] = 0;
                    return li + 1L;
                }
                co = 0L;
                lines[li * linelen] = 0;
            }
            continue;
        }
        if (ch == 32L && co == 0L) {
            continue;
        }
        if (co + 1L >= linelen) {
            li++;
            if (li >= maxlines) {
                li = maxlines - 1L;
                lines[li * linelen] = 0;
                return li + 1L;
            }
            co = 0L;
            lines[li * linelen] = 0;
            if (ch == 32L) {
                continue;
            }
        }
        lines[li * linelen + co] = (char)ch;
        co++;
        lines[li * linelen + co] = 0;
    }
    if (co > 0L) {
        return li + 1L;
    }
    if (li == 0L) {
        return 1L;
    }
    return li;
}

/** Compose the status bar line for the bottom row. */
static long wl_status_text(FreedomWlConfig *c, char *host, long nbytes, long off, long nlines, char *out, long cap) {
    long pos;
    long v;
    long div;
    long started;
    long maxoff;
    long shown;
    char num[24];
    long ni;
    if (!c || !host || !out || cap <= 0L || nbytes < 0L) {
        return -1L;
    }
    pos = 0L;
    while (*host && pos + 1L < cap && pos + 1L < c->cols) {
        out[pos] = *host;
        pos++;
        host++;
    }
    pos = wl_append(out, pos, " (", cap);
    v = nbytes;
    div = 1L;
    while (v / div >= 10L) {
        div = div * 10L;
    }
    ni = 0L;
    started = 0L;
    while (div > 0L) {
        long dg;
        dg = v / div;
        if (dg != 0L || started || div == 1L) {
            num[ni] = (char)('0' + dg);
            ni++;
            started = 1L;
        }
        v = v - dg * div;
        div = div / 10L;
    }
    num[ni] = 0;
    pos = wl_append(out, pos, num, cap);
    pos = wl_append(out, pos, " bytes)", cap);
    if (pos < 0L) {
        return -1L;
    }
    maxoff = nlines > c->text_rows ? nlines - c->text_rows : 0L;
    shown = maxoff > 0L ? off + 1L : 1L;
    if (shown > maxoff + 1L) {
        shown = maxoff + 1L;
    }
    v = shown;
    div = 1L;
    while (v / div >= 10L) {
        div = div * 10L;
    }
    ni = 0L;
    started = 0L;
    while (div > 0L) {
        long dg;
        dg = v / div;
        if (dg != 0L || started || div == 1L) {
            num[ni] = (char)('0' + dg);
            ni++;
            started = 1L;
        }
        v = v - dg * div;
        div = div / 10L;
    }
    num[ni] = 0;
    while (pos < c->cols - 12L && pos + 1L < cap) {
        out[pos] = ' ';
        pos++;
    }
    out[pos] = 0;
    pos = wl_append(out, pos, "Ln ", cap);
    pos = wl_append(out, pos, num, cap);
    if (pos < 0L) {
        return -1L;
    }
    while (pos + 1L < c->cols && pos + 1L < cap) {
        out[pos] = ' ';
        pos++;
    }
    out[pos] = 0;
    return pos;
}

#ifndef FREEDOM_WL_HOST_TEST
/** Runtime page buffers. */
static char w_host[WL_HOST_MAX];
static char w_path[WL_PATH_MAX];
static char w_loc[WL_URL_MAX];
static char w_hdr[WL_HDR_MAX];
static char w_body[WL_BODY_CAP];
static char w_lines[WL_LINES_MAX][WL_LINE_LEN];
static long w_nlines;
static long w_nbytes;
static long w_secure;
static long w_port;
static long w_status;
static long w_truncated;

/** Present syscall wrapper for the NK buffer path. */
static long freedom_wl_sys_present(long buf, long origin) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_GFX_PRESENT), "D"(buf), "S"(origin) : "rcx", "r11", "memory");
    return ret;
}

/** Set window title through the generic title syscall. */
static long freedom_wl_sys_title(char *t) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_GFX_SET_TITLE), "D"(t) : "rcx", "r11", "memory");
    return ret;
}

/** Read desktop mouse state into a four word buffer. */
static long freedom_wl_sys_mouse(long *m) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_MOUSE), "D"(m) : "rcx", "r11", "memory");
    return ret;
}

/** Poll one raw keyboard scancode, negative when idle. */
static long freedom_wl_sys_kbd(void) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_KBD), "D"(0) : "rcx", "r11", "memory");
    return ret;
}

/** Tell the kernel a graphics program owns the display. */
static long freedom_wl_sys_vga_mode(long on) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_VGA_MODE), "D"(on) : "rcx", "r11", "memory");
    return ret;
}

/** Switch the console into raw scancode mode. */
static long freedom_wl_sys_kbd_raw(long on) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_KBD_RAW), "D"(on) : "rcx", "r11", "memory");
    return ret;
}

/** Voluntary yield to the scheduler. */
static long freedom_wl_sys_yield(void) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_SCHED_YIELD), "D"(0) : "rcx", "r11", "memory");
    return ret;
}

/** Parse response headers into status, length, encoding and routing. */
static long wl_parse_headers(FreedomWlConfig *c, char *hdr, long *status, long *clen, long *hasclen, long *chunked, long *redir, long *istext) {
    long i;
    long line;
    long v;
    if (!c || !hdr || !status || !clen || !hasclen || !chunked || !redir || !istext) {
        return -1L;
    }
    *status = 0L;
    *clen = 0L;
    *hasclen = 0L;
    *chunked = 0L;
    *redir = 0L;
    *istext = 1L;
    if (hdr[0] != 'H' || hdr[1] != 'T' || hdr[2] != 'T' || hdr[3] != 'P' || hdr[4] != '/') {
        return -1L;
    }
    i = 0L;
    while (hdr[i] && hdr[i] != ' ' && hdr[i] != '\r') {
        i++;
    }
    if (hdr[i] != ' ') {
        return -1L;
    }
    i++;
    if (hdr[i] < '0' || hdr[i] > '9' || hdr[i + 1L] < '0' || hdr[i + 1L] > '9' || hdr[i + 2L] < '0' || hdr[i + 2L] > '9') {
        return -1L;
    }
    *status = (hdr[i] - '0') * 100L + (hdr[i + 1L] - '0') * 10L + (hdr[i + 2L] - '0');
    line = 0L;
    i = 0L;
    while (hdr[i]) {
        long ls;
        ls = i;
        while (hdr[i] && hdr[i] != '\r' && hdr[i] != '\n') {
            i++;
        }
        if (line > 0L) {
            if (wl_ci_starts(hdr + ls, "content-length:")) {
                long k;
                k = ls + 15L;
                while (hdr[k] == ' ' || hdr[k] == '\t') {
                    k++;
                }
                v = 0L;
                while (hdr[k] >= '0' && hdr[k] <= '9') {
                    v = v * 10L + (hdr[k] - '0');
                    k++;
                    if (v > c->body_cap) {
                        break;
                    }
                }
                *clen = v > c->body_cap ? c->body_cap : v;
                *hasclen = 1L;
            } else if (wl_ci_starts(hdr + ls, "location:")) {
                long k;
                long o;
                k = ls + 9L;
                while (hdr[k] == ' ' || hdr[k] == '\t') {
                    k++;
                }
                o = 0L;
                while (hdr[k] && hdr[k] != '\r' && hdr[k] != '\n' && o + 1L < c->url_max) {
                    w_loc[o] = hdr[k];
                    o++;
                    k++;
                }
                w_loc[o] = 0;
                *redir = 1L;
            } else if (wl_ci_starts(hdr + ls, "transfer-encoding:")) {
                if (wl_ci_contains(hdr + ls, "chunked")) {
                    *chunked = 1L;
                }
            } else if (wl_ci_starts(hdr + ls, "content-type:")) {
                long k;
                k = ls + 13L;
                while (hdr[k] == ' ' || hdr[k] == '\t') {
                    k++;
                }
                if (!wl_ci_starts(hdr + k, "text")) {
                    *istext = 0L;
                }
            }
        }
        line++;
        while (hdr[i] == '\r' || hdr[i] == '\n') {
            i++;
        }
    }
    return 0L;
}

/** Fetch one response body into the page buffer. */
static long wl_fetch_raw(FreedomWlConfig *c, char *host, char *path, long port, long secure) {
    char sa[16];
    char net[WL_NET_BUF];
    char req[WL_REQ_MAX];
    long fd;
    long ip;
    long n;
    long i;
    long pos;
    long stage;
    long got;
    long hdrlen;
    long status;
    long clen;
    long hasclen;
    long chunked;
    long redir;
    long istext;
    long cstage;
    long csize;
    long crem;
    long cline;
    long done;
    char cbuf[16];
    ip = net_dns_resolve(host);
    if (ip == 0 || ip == -1) {
        printf("freedom_wl: cannot resolve %s\n", host);
        return -1L;
    }
    fd = socket(2, 1, 0);
    if (fd < 0) {
        printf("freedom_wl: socket failed\n");
        return -1L;
    }
    sa[0] = 2;
    sa[1] = 0;
    sa[2] = (char)((port >> 8L) & 255L);
    sa[3] = (char)(port & 255L);
    sa[4] = (char)((ip >> 24L) & 255L);
    sa[5] = (char)((ip >> 16L) & 255L);
    sa[6] = (char)((ip >> 8L) & 255L);
    sa[7] = (char)(ip & 255L);
    sa[8] = 0;
    sa[9] = 0;
    sa[10] = 0;
    sa[11] = 0;
    sa[12] = 0;
    sa[13] = 0;
    sa[14] = 0;
    sa[15] = 0;
    if (connect((int)fd, (void *)sa, 16) < 0) {
        printf("freedom_wl: connect to %s failed\n", host);
        tls_close((int)fd);
        return -1L;
    }
    if (secure) {
        if (tls_handshake((int)fd, host) < 0) {
            printf("freedom_wl: https handshake with %s failed\n", host);
            tls_close((int)fd);
            return -1L;
        }
    }
    pos = 0L;
    pos = wl_append(req, pos, "GET ", c->req_max);
    pos = wl_append(req, pos, path, c->req_max);
    pos = wl_append(req, pos, " HTTP/1.0\r\nHost: ", c->req_max);
    pos = wl_append(req, pos, host, c->req_max);
    pos = wl_append(req, pos, "\r\nUser-Agent: ", c->req_max);
    pos = wl_append(req, pos, (char *)WL_USER_AGENT, c->req_max);
    pos = wl_append(req, pos, "\r\nAccept: text/html", c->req_max);
    pos = wl_append(req, pos, "\r\nConnection: close\r\n\r\n", c->req_max);
    if (pos < 0L) {
        printf("freedom_wl: request overflow\n");
        tls_close((int)fd);
        return -1L;
    }
    if (secure) {
        if (tls_send((int)fd, req, (int)pos) < 0) {
            printf("freedom_wl: send to %s failed\n", host);
            tls_close((int)fd);
            return -1L;
        }
    } else if (sendto((int)fd, req, pos, 0, 0, 0) < 0) {
        printf("freedom_wl: send to %s failed\n", host);
        tls_close((int)fd);
        return -1L;
    }
    stage = 0L;
    got = 0L;
    hdrlen = 0L;
    w_loc[0] = 0;
    status = 0L;
    clen = 0L;
    hasclen = 0L;
    chunked = 0L;
    redir = 0L;
    istext = 1L;
    cstage = 0L;
    csize = 0L;
    crem = 0L;
    cline = 0L;
    done = 0L;
    w_truncated = 0L;
    for (;;) {
        if (done) {
            break;
        }
        if (stage == 1L && !chunked && hasclen && got >= clen) {
            break;
        }
        if (secure) {
            n = tls_recv((int)fd, net, (int)c->net_buf);
        } else {
            n = recvfrom((int)fd, net, (int)c->net_buf, 0, 0, 0);
        }
        if (n <= 0L) {
            break;
        }
        i = 0L;
        while (i < n) {
            long ch;
            ch = (unsigned char)net[i];
            i++;
            if (stage == 0L) {
                if (hdrlen + 1L >= c->hdr_max) {
                    printf("freedom_wl: header overflow\n");
                    tls_close((int)fd);
                    return -1L;
                }
                w_hdr[hdrlen] = (char)ch;
                hdrlen++;
                w_hdr[hdrlen] = 0;
                if (hdrlen >= 4L && w_hdr[hdrlen - 4L] == '\r' && w_hdr[hdrlen - 3L] == '\n' &&
                    w_hdr[hdrlen - 2L] == '\r' && w_hdr[hdrlen - 1L] == '\n') {
                    if (wl_parse_headers(c, w_hdr, &status, &clen, &hasclen, &chunked, &redir, &istext) < 0L) {
                        printf("freedom_wl: bad response from %s\n", host);
                        tls_close((int)fd);
                        return -1L;
                    }
                    if (!istext) {
                        printf("freedom_wl: %s: not text\n", host);
                        tls_close((int)fd);
                        return -1L;
                    }
                    w_status = status;
                    stage = 1L;
                }
                continue;
            }
            if (chunked) {
                if (cstage == 0L) {
                    if (ch == '\r') {
                        continue;
                    }
                    if (ch == '\n') {
                        long k;
                        csize = 0L;
                        k = 0L;
                        while (k < cline) {
                            long d;
                            d = -1L;
                            if (cbuf[k] >= '0' && cbuf[k] <= '9') {
                                d = cbuf[k] - '0';
                            } else if (cbuf[k] >= 'a' && cbuf[k] <= 'f') {
                                d = cbuf[k] - 'a' + 10L;
                            } else if (cbuf[k] >= 'A' && cbuf[k] <= 'F') {
                                d = cbuf[k] - 'A' + 10L;
                            } else {
                                break;
                            }
                            csize = csize * 16L + d;
                            k++;
                        }
                        cline = 0L;
                        if (csize == 0L) {
                            done = 1L;
                            break;
                        }
                        crem = csize;
                        cstage = 1L;
                        continue;
                    }
                    if (ch == ';') {
                        while (i < n && net[i] != '\n') {
                            i++;
                        }
                        continue;
                    }
                    if (cline < 15L) {
                        cbuf[cline] = (char)ch;
                        cline++;
                    }
                    continue;
                }
                if (cstage == 1L) {
                    crem--;
                    if (got < c->body_cap) {
                        w_body[got] = (char)ch;
                        got++;
                    } else {
                        w_truncated = 1L;
                    }
                    if (crem == 0L) {
                        cstage = 2L;
                        cline = 2L;
                    }
                    continue;
                }
                if (cstage == 2L) {
                    if (cline > 0L) {
                        cline--;
                    }
                    if (cline == 0L) {
                        cstage = 0L;
                    }
                    continue;
                }
            } else {
                if (hasclen && got >= clen) {
                    break;
                }
                if (got < c->body_cap) {
                    w_body[got] = (char)ch;
                    got++;
                } else {
                    w_truncated = 1L;
                }
            }
        }
    }
    tls_close((int)fd);
    return got;
}

/** Render the page window at the given scroll offset. */
static long wl_render(FreedomWlConfig *c, long off) {
    volatile unsigned char *fb;
    long total;
    long i;
    long r;
    long col;
    long row;
    char status[WL_LINE_LEN];
    if (!c) {
        return -1L;
    }
    fb = (volatile unsigned char *)MINIOS_NK_BACKBUF_ADDR;
    total = c->surface_w * c->surface_h;
    for (i = 0L; i < total; i++) {
        fb[i] = (unsigned char)c->ink_bg;
    }
    for (r = 0L; r < c->text_rows; r++) {
        long src;
        src = off + r;
        for (col = 0L; col < c->cols; col++) {
            long ch;
            ch = 32L;
            if (src < w_nlines) {
                ch = w_lines[src][col];
                if (ch == 0L) {
                    ch = 32L;
                }
            }
            if (ch < 32L || ch > 126L) {
                ch = '?';
            }
            for (row = 0L; row < c->font_h; row++) {
                unsigned char bits;
                long px;
                bits = nk_font8x8[ch - 32L][row];
                for (px = 0L; px < c->font_w; px++) {
                    long ink;
                    if (bits & (0x80 >> px)) {
                        ink = c->ink_fg;
                    } else {
                        ink = c->ink_bg;
                    }
                    fb[(r * c->font_h + row) * c->surface_w + col * c->font_w + px] = (unsigned char)ink;
                }
            }
        }
    }
    for (col = 0L; col < c->surface_w; col++) {
        for (row = 0L; row < c->font_h; row++) {
            fb[(c->text_rows * c->font_h + row) * c->surface_w + col] = (unsigned char)c->bar_bg;
        }
    }
    if (wl_status_text(c, w_host, w_nbytes, off, w_nlines, status, c->line_len) < 0L) {
        return -1L;
    }
    for (col = 0L; col < c->cols; col++) {
        long ch;
        ch = status[col];
        if (ch == 0L) {
            break;
        }
        if (ch < 32L || ch > 126L) {
            ch = '?';
        }
        for (row = 0L; row < c->font_h; row++) {
            unsigned char bits;
            long px;
            bits = nk_font8x8[ch - 32L][row];
            for (px = 0L; px < c->font_w; px++) {
                long ink;
                if (bits & (0x80 >> px)) {
                    ink = c->bar_fg;
                } else {
                    ink = c->bar_bg;
                }
                fb[(c->text_rows * c->font_h + row) * c->surface_w + col * c->font_w + px] = (unsigned char)ink;
            }
        }
    }
    return freedom_wl_sys_present(c->present_buf, 0L);
}

/** Interactive scroll loop until q or ESC quits. */
static long wl_browse(FreedomWlConfig *c) {
    long off;
    int m[4];
    long e0;
    if (!c) {
        return 1L;
    }
    off = 0L;
    for (;;) {
        long sc;
        long changed;
        changed = 0L;
        e0 = 0L;
        sc = freedom_wl_sys_kbd();
        while (sc >= 0L) {
            if (sc == 0xE0L) {
                e0 = 1L;
                sc = freedom_wl_sys_kbd();
                if (sc < 0L) {
                    break;
                }
            }
            if (!(sc & 0x80L)) {
                long code;
                code = sc & 0x7FL;
                if (e0) {
                    if (code == 0x48L) {
                        off = off - 1L;
                        changed = 1L;
                    } else if (code == 0x50L) {
                        off = off + 1L;
                        changed = 1L;
                    } else if (code == 0x49L) {
                        off = off - c->text_rows;
                        changed = 1L;
                    } else if (code == 0x51L) {
                        off = off + c->text_rows;
                        changed = 1L;
                    } else if (code == 0x47L) {
                        off = 0L;
                        changed = 1L;
                    } else if (code == 0x4FL) {
                        off = w_nlines;
                        changed = 1L;
                    }
                } else if (code == 0x01L) {
                    return 0L;
                } else if (freedom_wl_keysym(c, sc) == 'q') {
                    return 0L;
                } else if (code == 0x48L) {
                    off = off - 1L;
                    changed = 1L;
                } else if (code == 0x50L) {
                    off = off + 1L;
                    changed = 1L;
                } else if (code == 0x24L) {
                    off = off + 1L;
                    changed = 1L;
                } else if (code == 0x25L) {
                    off = off - 1L;
                    changed = 1L;
                }
            }
            e0 = 0L;
            sc = freedom_wl_sys_kbd();
        }
        if (freedom_wl_sys_mouse((long *)m) == 0L && m[3] != 0L) {
            off = off + (long)m[3] * c->scroll_step;
            changed = 1L;
        }
        if (changed) {
            off = wl_scroll_clamp(c, off, w_nlines);
            if (wl_render(c, off) < 0L) {
                return 1L;
            }
        }
        freedom_wl_sys_yield();
    }
}

/** Guest selftest entry mirroring the Nuklear frame contract. */
static long freedom_wl_selftest(void) {
    FreedomWlConfig c;
    volatile unsigned char *fb;
    long i;
    long total;
    int origin[2];
    long cx;
    long cy;
    long cw;
    long ch;
    char sanit[8];
    c = freedom_wl_default();
    cx = 10L;
    cy = 10L;
    cw = 100L;
    ch = 100L;
    if (freedom_wl_clip_rect(&c, &cx, &cy, &cw, &ch) != 0L) {
        printf("freedom_wl: clip failed\n");
        return 1L;
    }
    if (freedom_wl_frame_bytes(&c, c.surface_w, c.surface_h) != c.surface_w * c.surface_h) {
        printf("freedom_wl: frame bytes failed\n");
        return 1L;
    }
    if (freedom_wl_keysym(&c, 0x1CL) != c.key_enter) {
        printf("freedom_wl: keysym failed\n");
        return 1L;
    }
    sanit[0] = 'h';
    sanit[1] = 'i';
    sanit[2] = 0;
    if (freedom_wl_sanitize_utf8(sanit, 8L) != 2L) {
        printf("freedom_wl: utf8 failed\n");
        return 1L;
    }
    if (freedom_wl_title_ok(&c, sanit, 2L) != 0L) {
        printf("freedom_wl: title bound failed\n");
        return 1L;
    }
    fb = (volatile unsigned char *)MINIOS_NK_BACKBUF_ADDR;
    total = c.surface_w * c.surface_h;
    for (i = 0L; i < total; i++) {
        fb[i] = (unsigned char)(i & 0xFFL);
    }
    fb[0] = 14L;
    if (freedom_wl_sys_present(c.present_buf, (long)origin) != 0L) {
        printf("freedom_wl: present failed\n");
        return 1L;
    }
    if (freedom_wl_sys_mouse((long *)0) == 0L) {
        printf("freedom_wl: mouse accepted null pointer\n");
        return 1L;
    }
    if (freedom_wl_sys_kbd() > 0x7FFFFFFFL) {
        printf("freedom_wl: kbd out of range\n");
        return 1L;
    }
    freedom_wl_sys_title("FreeDom");
    printf("freedom_wl: frame ok (%ldx%ld)\n", c.surface_w, c.surface_h);
    return 0L;
}
#endif

#ifdef FREEDOM_WL_HOST_TEST
/** Host harness entry for the pure mapping logic. */
int freedom_wl_host_probe(FreedomWlConfig *c) {
    long x;
    long y;
    long w;
    long h;
    char buf[16];
    if (!c) {
        return 1;
    }
    x = 10L;
    y = 10L;
    w = 100L;
    h = 100L;
    if (freedom_wl_clip_rect(c, &x, &y, &w, &h) != 0L) {
        return 1;
    }
    if (freedom_wl_frame_bytes(c, c->surface_w, c->surface_h) <= 0L) {
        return 1;
    }
    if (freedom_wl_keysym(c, 0x1CL) != c->key_enter) {
        return 1;
    }
    buf[0] = 'h';
    buf[1] = 'i';
    buf[2] = 0;
    if (freedom_wl_sanitize_utf8(buf, 16L) != 2L) {
        return 1;
    }
    return 0;
}
#else
/** Guest entry point shared by the MiniFS binary. */
int main(int argc, char **argv) {
    FreedomWlConfig c;
    char url[WL_URL_MAX];
    char title[32];
    long once;
    long qi;
    long hops;
    long n;
    long tl;
    c = freedom_wl_default();
    if (argc == 2 && strcmp(argv[1], "--selftest") == 0) {
        return (int)freedom_wl_selftest();
    }
    once = 0L;
    qi = 1L;
    if (argc > 2 && strcmp(argv[1], "--once") == 0) {
        once = 1L;
        qi = 2L;
    }
    if (argc <= qi) {
        printf("usage: freedom_wl [--once] <url-or-query>\n");
        return 2;
    }
    if (argv[qi][0] == '-' && argv[qi][1] == '-') {
        printf("freedom_wl: unknown flag %s\n", argv[qi]);
        printf("usage: freedom_wl [--once] <url-or-query>\n");
        return 2;
    }
    freedom_wl_sys_vga_mode(1L);
    freedom_wl_sys_kbd_raw(1L);
    if (wl_has_scheme(argv[qi])) {
        if (wl_ci_starts(argv[qi], "https://") || wl_ci_starts(argv[qi], "http://")) {
            if (wl_copy(url, argv[qi], c.url_max) < 0L) {
                printf("freedom_wl: url too long\n");
                return 3;
            }
        } else {
            if (wl_make_search(w_path, argv[qi], c.path_max) < 0L) {
                printf("freedom_wl: query too long\n");
                return 3;
            }
            if (wl_copy(w_host, (char *)WL_SEARCH_HOST, c.host_max) < 0L) {
                return 3;
            }
            w_port = c.port_https;
            w_secure = 1L;
            goto wl_fetch;
        }
    } else if (wl_looks_like_url(argv[qi])) {
        if (wl_append(url, 0L, "https://", c.url_max) < 0L) {
            return 3;
        }
        if (wl_append(url, 8L, argv[qi], c.url_max) < 0L) {
            printf("freedom_wl: url too long\n");
            return 3;
        }
    } else {
        if (wl_make_search(w_path, argv[qi], c.path_max) < 0L) {
            printf("freedom_wl: query too long\n");
            return 3;
        }
        if (wl_copy(w_host, (char *)WL_SEARCH_HOST, c.host_max) < 0L) {
            return 3;
        }
        w_port = c.port_https;
        w_secure = 1L;
        goto wl_fetch;
    }
    if (!wl_split_url(&c, url, w_host, w_path, &w_port, &w_secure)) {
        printf("freedom_wl: cannot parse %s\n", url);
        return 3;
    }
wl_fetch:
    hops = 0L;
    for (;;) {
        n = wl_fetch_raw(&c, w_host, w_path, w_port, w_secure);
        if (n < 0L) {
            return 1;
        }
        if (w_status >= 300L && w_status < 400L && w_loc[0] != 0) {
            long rr;
            if (hops >= c.hops_max) {
                printf("freedom_wl: too many redirects\n");
                return 1;
            }
            hops++;
            rr = wl_resolve_redirect(&c, w_loc, w_secure, w_host, w_path, &w_port, &w_secure);
            if (rr < 0L) {
                printf("freedom_wl: redirect scheme refused\n");
                return 1;
            }
            if (!rr) {
                return 1;
            }
            continue;
        }
        break;
    }
    w_nbytes = n;
    w_nlines = wl_filter_wrap(&c, w_body, n, (char *)w_lines, c.lines_max, c.line_len);
    tl = wl_strlen(w_host, c.host_max);
    if (tl < 0L) {
        tl = c.title_max;
    }
    if (tl > c.title_max) {
        tl = c.title_max;
    }
    {
        long k;
        k = 0L;
        while (k < tl) {
            title[k] = w_host[k];
            k++;
        }
        title[tl] = 0;
    }
    if (freedom_wl_title_ok(&c, title, tl) == 0L) {
        freedom_wl_sys_title(title);
    }
    if (wl_render(&c, 0L) < 0L) {
        printf("freedom_wl: render failed\n");
        return 1;
    }
    printf("freedom_wl: %s (%ld bytes)%s\n", w_host, n, w_truncated ? " (truncated)" : "");
    if (once) {
        return 0;
    }
    return (int)wl_browse(&c);
}
#endif
