/** freedomui_minios - Real FreeDom browser on MiniOS, DOOM/Q2G pattern.
 *
 * A ring-3 static ELF that runs the real FreeDom engine core (url, link_nav,
 * html_parse over Lexbor, ui_layout) on MiniOS. It owns the same intermediate
 * role doomgeneric_minios and q2generic_minios own: every Wayland and Cairo
 * call the desktop engine would make is replaced by a MiniOS syscall through
 * this file. The NK back-buffer window (MINIOS_NK_W x MINIOS_NK_H) is the
 * surface, GFX_PRESENT with BUF_NK presents, GFX_SET_TITLE titles, SYS_MOUSE
 * and SYS_KBD feed input, SYS_PALETTE uploads the hybrid palette, SYS_TIME
 * paces the loop, VGA_MODE claims the display. Network runs over the socket
 * syscalls with DNS from syscall 200 and https through the shared ring-3 TLS
 * engine, so no key material crosses ring 0. Remote pages are hostile data:
 * every byte passes a gate before the back-buffer.
 *
 * Scope of this version: fetch plus parse plus text layout plus scroll. JS,
 * images, video, sandbox confinement and persistence stay out; each is a
 * follow-up file behind its own ADR. The parser still strips scripts and
 * event handlers exactly as on hosted builds.
 *
 * Build guest as static ELF on MiniFS with the FreeDom sources. Build host
 * test with FREEDOMUI_HOST_TEST for pure logic without syscalls.
 *
 * Usage guest: freedomui --selftest parses built-in HTML through the real
 * engine, presents one frame and verifies the composite origin, mirroring
 * the Nuklear selftest contract. Usage guest: freedomui [--once]
 * <url-or-query> fetches, renders and presents; without --once an input
 * loop drives scroll until q or ESC quits.
 */
#include "minios_abi.h"

#include "url.h"
#include "link_nav.h"
#include "html_parse.h"
#include "ui.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

int net_dns_resolve(const char *host);
int tls_handshake(int fd, char *host);
int tls_send(int fd, char *buf, int len);
int tls_recv(int fd, char *buf, int len);
void tls_close(int fd);

/** Named limits for the browser. */
#define FUI_COLS 100L
#define FUI_TEXT_ROWS 44L
#define FUI_BODY_CAP 262144L
#define FUI_HDR_MAX 16384L
#define FUI_NET_BUF 768L
#define FUI_REQ_MAX 768L
#define FUI_HOST_MAX 64L
#define FUI_PATH_MAX 128L
#define FUI_URL_MAX 512L
#define FUI_HOPS_MAX 3L
#define FUI_FONT_W 8L
#define FUI_FONT_H 8L
#define FUI_TITLE_MAX 31L

/** Shared 8x8 bitmap font, one copy in progs/nuklear/font8x8.c. */
extern const uint8_t nk_font8x8[96][8];

/** Centralized configuration for the MiniOS backend. */
typedef struct FreedomUiConfig {
    long present_buf;
    long surface_w;
    long surface_h;
    long title_max;
    long scroll_step;
    long key_esc;
    long cols;
    long text_rows;
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
} FreedomUiConfig;

/** Default configuration derived from the ABI header. */
static FreedomUiConfig freedomui_default(void) {
    FreedomUiConfig c;
    c.present_buf = (long)MINIOS_GFX_BUF_NK;
    c.surface_w = (long)MINIOS_NK_W;
    c.surface_h = (long)MINIOS_NK_H;
    c.title_max = FUI_TITLE_MAX;
    c.scroll_step = 3L;
    c.key_esc = 27L;
    c.cols = FUI_COLS;
    c.text_rows = FUI_TEXT_ROWS;
    c.body_cap = FUI_BODY_CAP;
    c.hdr_max = FUI_HDR_MAX;
    c.net_buf = FUI_NET_BUF;
    c.req_max = FUI_REQ_MAX;
    c.host_max = FUI_HOST_MAX;
    c.path_max = FUI_PATH_MAX;
    c.url_max = FUI_URL_MAX;
    c.hops_max = FUI_HOPS_MAX;
    c.font_w = FUI_FONT_W;
    c.font_h = FUI_FONT_H;
    c.port_http = 80L;
    c.port_https = 443L;
    c.ink_bg = 6L;
    c.ink_fg = 7L;
    c.bar_bg = 4L;
    c.bar_fg = 5L;
    return c;
}

/** Build the 768-byte graphics palette for the NK back-buffer window.
 *
 * Indices 0-14 exactly match the desktop palette in
 * progs/nuklear/nuklear_minios.c so the desktop behind the window is never
 * recolored; 15-230 carry a 6x6x6 RGB cube, 231-241 carry grays and 242-255
 * carry saturated accents. Fail-closed on null or short buffers.
 */
static long freedomui_build_palette(unsigned char *pal, long cap) {
    static const unsigned char desk[15][3] = {
        {0, 0, 0}, {15, 15, 50}, {100, 100, 110}, {255, 255, 255},
        {60, 90, 140}, {255, 255, 255}, {15, 15, 15}, {0, 220, 0},
        {0, 160, 0}, {180, 180, 190}, {255, 255, 255}, {30, 30, 40},
        {100, 140, 220}, {60, 60, 70}, {140, 140, 155}
    };
    static const unsigned char grays[11] = {0, 25, 51, 76, 102, 127, 153, 178, 204, 229, 255};
    static const unsigned char accents[14][3] = {
        {255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 255, 0},
        {0, 255, 255}, {255, 0, 255}, {255, 128, 0}, {128, 0, 255},
        {255, 0, 128}, {0, 128, 255}, {128, 255, 0}, {255, 128, 128},
        {128, 255, 128}, {128, 128, 255}
    };
    long idx;
    long r;
    long g;
    long b;
    long i;
    if (!pal || cap < 768L) {
        return -1L;
    }
    for (i = 0L; i < 15L; i++) {
        pal[i * 3L] = desk[i][0];
        pal[i * 3L + 1L] = desk[i][1];
        pal[i * 3L + 2L] = desk[i][2];
    }
    idx = 15L;
    for (r = 0L; r < 6L; r++) {
        for (g = 0L; g < 6L; g++) {
            for (b = 0L; b < 6L; b++) {
                pal[idx * 3L] = (unsigned char)(r * 51L);
                pal[idx * 3L + 1L] = (unsigned char)(g * 51L);
                pal[idx * 3L + 2L] = (unsigned char)(b * 51L);
                idx++;
            }
        }
    }
    for (i = 0L; i < 11L; i++) {
        pal[idx * 3L] = grays[i];
        pal[idx * 3L + 1L] = grays[i];
        pal[idx * 3L + 2L] = grays[i];
        idx++;
    }
    for (i = 0L; i < 14L; i++) {
        pal[idx * 3L] = accents[i][0];
        pal[idx * 3L + 1L] = accents[i][1];
        pal[idx * 3L + 2L] = accents[i][2];
        idx++;
    }
    if (idx != 256L) {
        return -1L;
    }
    return 0L;
}

/** Parse a fetched body through the real engine into owned title and text.
 *
 * Runs hp_parse with secure defaults (scripts stripped, handlers stripped)
 * then hp_get_title and hp_extract_text. Both out pointers are owned buffers
 * the caller releases with hp_free; either may be NULL when the document
 * carries no title or no text. Returns element count, or -1 on parse
 * failure. Fail-closed on every bound.
 */
static long freedomui_engine_text(char *body, long n, char **title, char **text) {
    hp_document *doc;
    hp_status st;
    char *ti;
    char *tx;
    long elems;
    if (!body || n <= 0L || !title || !text) {
        return -1L;
    }
    doc = 0;
    st = hp_parse(body, (size_t)n, 0, &doc);
    if (st != HP_OK || !doc) {
        return -1L;
    }
    elems = (long)hp_element_count(doc);
    ti = hp_get_title(doc, 0);
    tx = hp_extract_text(doc, 0);
    hp_document_free(doc);
    if (!tx) {
        if (ti) {
            hp_free(ti);
        }
        return -1L;
    }
    *title = ti;
    *text = tx;
    return elems;
}

/** Host harness probe lives in the FREEDOMUI_HOST_TEST block below. */

#ifndef FREEDOMUI_HOST_TEST
/** Runtime page state. */
static char f_host[FUI_HOST_MAX];
static char f_path[FUI_PATH_MAX];
static char f_loc[FUI_URL_MAX];
static char f_hdr[FUI_HDR_MAX];
static char f_body[FUI_BODY_CAP];
static char *f_text;
static ui_layout f_lay;
static long f_elems;
static long f_nbytes;
static long f_secure;
static long f_port;
static long f_status;
static long f_truncated;

/** Present syscall wrapper for the NK buffer path. */
static long freedomui_sys_present(long buf, long origin) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_GFX_PRESENT), "D"(buf), "S"(origin) : "rcx", "r11", "memory");
    return ret;
}

/** Set window title through the generic title syscall. */
static long freedomui_sys_title(char *t) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_GFX_SET_TITLE), "D"(t) : "rcx", "r11", "memory");
    return ret;
}

/** Upload the 768-byte graphics palette before presenting indexed pixels. */
static long freedomui_sys_palette(unsigned char *pal) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_PALETTE), "D"(pal) : "rcx", "r11", "memory");
    return ret;
}

/** Read desktop mouse state into a four word buffer. */
static long freedomui_sys_mouse(long *m) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_MOUSE), "D"(m) : "rcx", "r11", "memory");
    return ret;
}

/** Poll one raw keyboard scancode, negative when idle. */
static long freedomui_sys_kbd(void) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_KBD), "D"(0) : "rcx", "r11", "memory");
    return ret;
}

/** Tell the kernel a graphics program owns the display. */
static long freedomui_sys_vga_mode(long on) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_VGA_MODE), "D"(on) : "rcx", "r11", "memory");
    return ret;
}

/** Switch the console into raw scancode mode. */
static long freedomui_sys_kbd_raw(long on) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_KBD_RAW), "D"(on) : "rcx", "r11", "memory");
    return ret;
}

/** Voluntary yield to the scheduler. */
static long freedomui_sys_yield(void) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_SCHED_YIELD), "D"(0) : "rcx", "r11", "memory");
    return ret;
}

/** Bounded append of src at dst[pos]. */
static long fui_append(char *dst, long pos, char *src, long cap) {
    long i;
    if (!dst || !src || pos < 0L || cap <= 0L) {
        return -1L;
    }
    i = 0L;
    while (src[i] != 0) {
        if (pos + i + 1L >= cap) {
            return -1L;
        }
        dst[pos + i] = src[i];
        i++;
    }
    dst[pos + i] = 0;
    return pos + i;
}

/** Bounded string length. */
static long fui_strlen(char *s, long cap) {
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

/** Split an http(s) URL into host, path, port and secure flag. */
static long fui_split_url(FreedomUiConfig *c, char *url, char *host, char *path, long *port, long *secure) {
    char *p;
    long hl;
    long k;
    long v;
    if (!c || !url || !host || !path || !port || !secure) {
        return 0L;
    }
    if (url[0] == 'h' && url[1] == 't' && url[2] == 't' && url[3] == 'p' && url[4] == 's' && url[5] == ':' && url[6] == '/' && url[7] == '/') {
        *secure = 1L;
        *port = c->port_https;
        p = url + 8L;
    } else if (url[0] == 'h' && url[1] == 't' && url[2] == 't' && url[3] == 'p' && url[4] == ':' && url[5] == '/' && url[6] == '/') {
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
        if (fui_strlen(p + hl, c->path_max) < 0L) {
            return 0L;
        }
        k = 0L;
        while (p[hl + k]) {
            if (k + 1L >= c->path_max) {
                return 0L;
            }
            path[k] = p[hl + k];
            k++;
        }
        path[k] = 0;
    } else {
        path[0] = '/';
        path[1] = 0;
    }
    return 1L;
}

/** Parse response headers into status, length, encoding and routing. */
static long fui_parse_headers(FreedomUiConfig *c, char *hdr, long *status, long *clen, long *hasclen, long *chunked, long *redir, long *istext) {
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
            long is_loc;
            long is_len;
            long is_te;
            long is_ct;
            is_loc = hdr[ls] == 'L' || hdr[ls] == 'l';
            is_len = hdr[ls] == 'C' || hdr[ls] == 'c';
            is_te = hdr[ls] == 'T' || hdr[ls] == 't';
            is_ct = is_len;
            if (is_loc) {
                long k;
                long o;
                k = ls;
                while (hdr[k] && hdr[k] != ':') {
                    k++;
                }
                if (hdr[k] == ':') {
                    k++;
                    while (hdr[k] == ' ' || hdr[k] == '\t') {
                        k++;
                    }
                    o = 0L;
                    while (hdr[k] && hdr[k] != '\r' && hdr[k] != '\n' && o + 1L < c->url_max) {
                        f_loc[o] = hdr[k];
                        o++;
                        k++;
                    }
                    f_loc[o] = 0;
                    *redir = 1L;
                }
            } else if (is_len) {
                long k;
                k = ls;
                while (hdr[k] && hdr[k] != ':') {
                    k++;
                }
                if (hdr[k] == ':') {
                    k++;
                    while (hdr[k] == ' ' || hdr[k] == '\t') {
                        k++;
                    }
                    if ((hdr[k] >= '0' && hdr[k] <= '9')) {
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
                    } else if (is_ct) {
                        while (hdr[k] == ' ' || hdr[k] == '\t') {
                            k++;
                        }
                        if (!(hdr[k] == 't' || hdr[k] == 'T')) {
                            *istext = 0L;
                        }
                    }
                }
            } else if (is_te) {
                long k;
                k = ls;
                while (hdr[k] && hdr[k + 1L] && hdr[k + 2L] && hdr[k + 3L] && hdr[k + 4L] && hdr[k + 5L] && hdr[k + 6L]) {
                    if ((hdr[k] == 'c' || hdr[k] == 'C') && (hdr[k + 1L] == 'h' || hdr[k + 1L] == 'H')) {
                        *chunked = 1L;
                        break;
                    }
                    k++;
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
static long fui_fetch_raw(FreedomUiConfig *c, char *host, char *path, long port, long secure) {
    char sa[16];
    char net[FUI_NET_BUF];
    char req[FUI_REQ_MAX];
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
        printf("freedomui: cannot resolve %s\n", host);
        return -1L;
    }
    fd = socket(2, 1, 0);
    if (fd < 0) {
        printf("freedomui: socket failed\n");
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
        printf("freedomui: connect to %s failed\n", host);
        tls_close((int)fd);
        return -1L;
    }
    if (secure) {
        if (tls_handshake((int)fd, host) < 0) {
            printf("freedomui: https handshake with %s failed\n", host);
            tls_close((int)fd);
            return -1L;
        }
    }
    pos = 0L;
    pos = fui_append(req, pos, "GET ", c->req_max);
    pos = fui_append(req, pos, path, c->req_max);
    pos = fui_append(req, pos, " HTTP/1.0\r\nHost: ", c->req_max);
    pos = fui_append(req, pos, host, c->req_max);
    pos = fui_append(req, pos, "\r\nUser-Agent: freedomui/1.0 (MiniOS)", c->req_max);
    pos = fui_append(req, pos, "\r\nAccept: text/html", c->req_max);
    pos = fui_append(req, pos, "\r\nConnection: close\r\n\r\n", c->req_max);
    if (pos < 0L) {
        printf("freedomui: request overflow\n");
        tls_close((int)fd);
        return -1L;
    }
    if (secure) {
        if (tls_send((int)fd, req, (int)pos) < 0) {
            printf("freedomui: send to %s failed\n", host);
            tls_close((int)fd);
            return -1L;
        }
    } else if (sendto((int)fd, req, pos, 0, 0, 0) < 0) {
        printf("freedomui: send to %s failed\n", host);
        tls_close((int)fd);
        return -1L;
    }
    stage = 0L;
    got = 0L;
    hdrlen = 0L;
    f_loc[0] = 0;
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
    f_truncated = 0L;
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
                    printf("freedomui: header overflow\n");
                    tls_close((int)fd);
                    return -1L;
                }
                f_hdr[hdrlen] = (char)ch;
                hdrlen++;
                f_hdr[hdrlen] = 0;
                if (hdrlen >= 4L && f_hdr[hdrlen - 4L] == '\r' && f_hdr[hdrlen - 3L] == '\n' &&
                    f_hdr[hdrlen - 2L] == '\r' && f_hdr[hdrlen - 1L] == '\n') {
                    if (fui_parse_headers(c, f_hdr, &status, &clen, &hasclen, &chunked, &redir, &istext) < 0L) {
                        printf("freedomui: bad response from %s\n", host);
                        tls_close((int)fd);
                        return -1L;
                    }
                    if (!istext) {
                        printf("freedomui: %s: not text\n", host);
                        tls_close((int)fd);
                        return -1L;
                    }
                    f_status = status;
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
                    if (cline < 15L) {
                        cbuf[cline] = (char)ch;
                        cline++;
                    }
                    continue;
                }
                if (cstage == 1L) {
                    crem--;
                    if (got < c->body_cap) {
                        f_body[got] = (char)ch;
                        got++;
                    } else {
                        f_truncated = 1L;
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
                    f_body[got] = (char)ch;
                    got++;
                } else {
                    f_truncated = 1L;
                }
            }
        }
    }
    tls_close((int)fd);
    return got;
}

/** Render the engine text window at the given scroll offset. */
static long fui_render(FreedomUiConfig *c, size_t off) {
    volatile unsigned char *fb;
    unsigned char pal[768];
    long total;
    long i;
    size_t r;
    long col;
    long row;
    char status[128];
    long sp;
    if (!c) {
        return -1L;
    }
    if (freedomui_build_palette(pal, 768L) == 0L) {
        freedomui_sys_palette(pal);
    }
    fb = (volatile unsigned char *)MINIOS_NK_BACKBUF_ADDR;
    total = c->surface_w * c->surface_h;
    for (i = 0L; i < total; i++) {
        fb[i] = (unsigned char)c->ink_bg;
    }
    for (r = 0; r < (size_t)c->text_rows; r++) {
        size_t src;
        src = off + r;
        for (col = 0L; col < c->cols; col++) {
            long ch;
            ch = 32L;
            if (f_text && src < f_lay.count) {
                size_t o;
                o = f_lay.lines[src].offset + (size_t)col;
                if ((size_t)col < f_lay.lines[src].len) {
                    ch = (unsigned char)f_text[o];
                }
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
                    fb[(r * (size_t)c->font_h + (size_t)row) * (size_t)c->surface_w + (size_t)col * (size_t)c->font_w + (size_t)px] = (unsigned char)ink;
                }
            }
        }
    }
    for (col = 0L; col < c->surface_w; col++) {
        for (row = 0L; row < c->font_h; row++) {
            fb[((size_t)c->text_rows * (size_t)c->font_h + (size_t)row) * (size_t)c->surface_w + (size_t)col] = (unsigned char)c->bar_bg;
        }
    }
    sp = 0L;
    sp = fui_append(status, sp, f_host, 128L);
    sp = fui_append(status, sp, " (", 128L);
    {
        char num[24];
        long v;
        long div;
        long ni;
        v = f_nbytes;
        div = 1L;
        while (v / div >= 10L) {
            div = div * 10L;
        }
        ni = 0L;
        while (div > 0L) {
            long dg;
            dg = v / div;
            if (ni == 0L && dg == 0L && div != 1L) {
                div = div / 10L;
                continue;
            }
            num[ni] = (char)('0' + dg);
            ni++;
            v = v - dg * div;
            div = div / 10L;
        }
        num[ni] = 0;
        sp = fui_append(status, sp, num, 128L);
    }
    sp = fui_append(status, sp, " bytes)", 128L);
    if (sp < 0L) {
        return -1L;
    }
    for (col = 0L; col < c->cols && status[col]; col++) {
        long ch;
        ch = status[col];
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
                fb[((size_t)c->text_rows * (size_t)c->font_h + (size_t)row) * (size_t)c->surface_w + (size_t)col * (size_t)c->font_w + (size_t)px] = (unsigned char)ink;
            }
        }
    }
    return freedomui_sys_present(c->present_buf, 0L);
}

/** Interactive scroll loop until q or ESC quits. */
static long fui_browse(FreedomUiConfig *c) {
    size_t off;
    int m[4];
    long e0;
    if (!c) {
        return 1L;
    }
    off = 0;
    for (;;) {
        long sc;
        long changed;
        changed = 0L;
        e0 = 0L;
        sc = freedomui_sys_kbd();
        while (sc >= 0L) {
            if (sc == 0xE0L) {
                e0 = 1L;
                sc = freedomui_sys_kbd();
                if (sc < 0L) {
                    break;
                }
            }
            if (!(sc & 0x80L)) {
                long code;
                code = sc & 0x7FL;
                if (e0) {
                    if (code == 0x48L) {
                        off = off > 0 ? off - 1 : 0;
                        changed = 1L;
                    } else if (code == 0x50L) {
                        off = ui_clamp_scroll(off + 1, f_lay.count, (size_t)c->text_rows);
                        changed = 1L;
                    } else if (code == 0x49L) {
                        off = off > (size_t)c->text_rows ? off - (size_t)c->text_rows : 0;
                        changed = 1L;
                    } else if (code == 0x51L) {
                        off = ui_clamp_scroll(off + (size_t)c->text_rows, f_lay.count, (size_t)c->text_rows);
                        changed = 1L;
                    } else if (code == 0x47L) {
                        off = 0;
                        changed = 1L;
                    } else if (code == 0x4FL) {
                        off = ui_clamp_scroll(f_lay.count, f_lay.count, (size_t)c->text_rows);
                        changed = 1L;
                    }
                } else if (code == 0x01L) {
                    return 0L;
                } else if (code == 0x10L) {
                    return 0L;
                } else if (code == 0x48L) {
                    off = off > 0 ? off - 1 : 0;
                    changed = 1L;
                } else if (code == 0x50L) {
                    off = ui_clamp_scroll(off + 1, f_lay.count, (size_t)c->text_rows);
                    changed = 1L;
                }
            }
            e0 = 0L;
            sc = freedomui_sys_kbd();
        }
        if (freedomui_sys_mouse((long *)m) == 0L && m[3] != 0L) {
            long want;
            want = (long)off + (long)m[3] * c->scroll_step;
            if (want < 0L) {
                want = 0L;
            }
            off = ui_clamp_scroll((size_t)want, f_lay.count, (size_t)c->text_rows);
            changed = 1L;
        }
        if (changed) {
            if (fui_render(c, off) < 0L) {
                return 1L;
            }
        }
        freedomui_sys_yield();
    }
}

/** Guest selftest entry mirroring the Nuklear frame contract. */
static long freedomui_selftest(void) {
    FreedomUiConfig c;
    volatile unsigned char *fb;
    unsigned char pal[768];
    long i;
    long total;
    int origin[2];
    char *title;
    char *text;
    char html[64];
    long elems;
    c = freedomui_default();
    if (freedomui_build_palette(pal, 768L) != 0L) {
        printf("freedomui: palette failed\n");
        return 1L;
    }
    if (pal[6 * 3] != 15 || pal[6 * 3 + 1] != 15 || pal[6 * 3 + 2] != 15) {
        printf("freedomui: palette bg failed\n");
        return 1L;
    }
    html[0] = '<';
    html[1] = 't';
    html[2] = 'i';
    html[3] = 't';
    html[4] = 'l';
    html[5] = 'e';
    html[6] = '>';
    html[7] = 'H';
    html[8] = 'i';
    html[9] = '<';
    html[10] = '/';
    html[11] = 't';
    html[12] = 'i';
    html[13] = 't';
    html[14] = 'l';
    html[15] = 'e';
    html[16] = '>';
    html[17] = '<';
    html[18] = 'p';
    html[19] = '>';
    html[20] = 'o';
    html[21] = 'k';
    html[22] = '<';
    html[23] = '/';
    html[24] = 'p';
    html[25] = '>';
    html[26] = 0;
    title = 0;
    text = 0;
    elems = freedomui_engine_text(html, 26L, &title, &text);
    if (elems < 0L || !text) {
        printf("freedomui: engine parse failed\n");
        if (title) {
            hp_free(title);
        }
        return 1L;
    }
    hp_free(text);
    if (title) {
        hp_free(title);
    }
    freedomui_sys_palette(pal);
    fb = (volatile unsigned char *)MINIOS_NK_BACKBUF_ADDR;
    total = c.surface_w * c.surface_h;
    for (i = 0L; i < total; i++) {
        fb[i] = (unsigned char)(i & 0xFFL);
    }
    fb[0] = 14L;
    if (freedomui_sys_present(c.present_buf, (long)origin) != 0L) {
        printf("freedomui: present failed\n");
        return 1L;
    }
    if (freedomui_sys_mouse((long *)0) == 0L) {
        printf("freedomui: mouse accepted null pointer\n");
        return 1L;
    }
    if (freedomui_sys_kbd() > 0x7FFFFFFFL) {
        printf("freedomui: kbd out of range\n");
        return 1L;
    }
    freedomui_sys_title("FreeDom");
    printf("freedomui: frame ok (%ldx%ld)\n", c.surface_w, c.surface_h);
    return 0L;
}
#endif

#ifdef FREEDOMUI_HOST_TEST
/** Host harness probe for pure backend logic plus engine linkage. */
static long freedomui_host_probe(FreedomUiConfig *c) {
    char nav[512];
    url_omni_kind kind;
    char *title;
    char *text;
    char html[128];
    ui_layout lay;
    long elems;
    if (!c) {
        return -1L;
    }
    if (c->surface_w != 800L || c->surface_h != 360L) {
        return -1L;
    }
    if (c->present_buf != 1L) {
        return -1L;
    }
    if (url_omnibox("example.com", &kind, nav, sizeof(nav)) != 0) {
        return -1L;
    }
    if (kind != 0) {
        return -1L;
    }
    if (url_omnibox("hello world", &kind, nav, sizeof(nav)) != 0) {
        return -1L;
    }
    if (kind != 1) {
        return -1L;
    }
    html[0] = '<';
    html[1] = 't';
    html[2] = 'i';
    html[3] = 't';
    html[4] = 'l';
    html[5] = 'e';
    html[6] = '>';
    html[7] = 'H';
    html[8] = 'i';
    html[9] = '<';
    html[10] = '/';
    html[11] = 't';
    html[12] = 'i';
    html[13] = 't';
    html[14] = 'l';
    html[15] = 'e';
    html[16] = '>';
    html[17] = '<';
    html[18] = 'p';
    html[19] = '>';
    html[20] = 'b';
    html[21] = 'o';
    html[22] = 'd';
    html[23] = 'y';
    html[24] = '<';
    html[25] = '/';
    html[26] = 'p';
    html[27] = '>';
    html[28] = 0;
    title = 0;
    text = 0;
    elems = freedomui_engine_text(html, 28L, &title, &text);
    if (elems < 0L || !text) {
        if (title) {
            hp_free(title);
        }
        return -1L;
    }
    if (ui_wrap_text(text, strlen(text), (size_t)c->cols, &lay) != 0) {
        hp_free(text);
        if (title) {
            hp_free(title);
        }
        return -1L;
    }
    ui_layout_free(&lay);
    hp_free(text);
    if (title) {
        hp_free(title);
    }
    return 0L;
}

/** Host harness entry for pure backend logic plus engine linkage. */
int freedomui_host_entry(FreedomUiConfig *c) {
    return (int)freedomui_host_probe(c);
}
#else
/** Guest entry point shared by the MiniFS binary. */
int main(int argc, char **argv) {
    FreedomUiConfig c;
    char nav[512];
    char url[512];
    char title[32];
    url_omni_kind kind;
    long once;
    long qi;
    long hops;
    long n;
    long tl;
    long k;
    c = freedomui_default();
    if (argc == 2 && strcmp(argv[1], "--selftest") == 0) {
        return (int)freedomui_selftest();
    }
    once = 0L;
    qi = 1L;
    if (argc > 2 && strcmp(argv[1], "--once") == 0) {
        once = 1L;
        qi = 2L;
    }
    if (argc <= qi) {
        printf("usage: freedomui [--once] <url-or-query>\n");
        return 2;
    }
    if (argv[qi][0] == '-' && argv[qi][1] == '-') {
        printf("freedomui: unknown flag %s\n", argv[qi]);
        printf("usage: freedomui [--once] <url-or-query>\n");
        return 2;
    }
    freedomui_sys_vga_mode(1L);
    freedomui_sys_kbd_raw(1L);
    if (url_omnibox(argv[qi], &kind, nav, sizeof(nav)) != 0) {
        printf("freedomui: cannot parse %s\n", argv[qi]);
        return 3;
    }
    if (kind == 1) {
        printf("freedomui: search not yet in v1: %s\n", argv[qi]);
        return 3;
    }
    k = 0L;
    while (nav[k] && k + 1L < (long)sizeof(url)) {
        url[k] = nav[k];
        k++;
    }
    url[k] = 0;
    if (!fui_split_url(&c, url, f_host, f_path, &f_port, &f_secure)) {
        printf("freedomui: cannot parse %s\n", url);
        return 3;
    }
    hops = 0L;
    for (;;) {
        n = fui_fetch_raw(&c, f_host, f_path, f_port, f_secure);
        if (n < 0L) {
            return 1;
        }
        if (f_status >= 300L && f_status < 400L && f_loc[0] != 0) {
            if (hops >= c.hops_max) {
                printf("freedomui: too many redirects\n");
                return 1;
            }
            hops++;
            if (!fui_split_url(&c, f_loc, f_host, f_path, &f_port, &f_secure)) {
                if (f_loc[0] == '/') {
                    k = 0L;
                    while (f_loc[k] && k + 1L < c.path_max) {
                        f_path[k] = f_loc[k];
                        k++;
                    }
                    f_path[k] = 0;
                } else {
                    printf("freedomui: redirect refused %s\n", f_loc);
                    return 1;
                }
            }
            continue;
        }
        break;
    }
    f_nbytes = n;
    {
        char *ti;
        char *tx;
        ti = 0;
        tx = 0;
        f_elems = freedomui_engine_text(f_body, n, &ti, &tx);
        if (f_elems < 0L || !tx) {
            printf("freedomui: engine parse failed\n");
            if (ti) {
                hp_free(ti);
            }
            return 1;
        }
        if (ti) {
            tl = fui_strlen(ti, c.title_max + 1L);
            if (tl < 0L) {
                tl = c.title_max;
            }
            if (tl > c.title_max) {
                tl = c.title_max;
            }
            k = 0L;
            while (k < tl) {
                title[k] = ti[k];
                k++;
            }
            title[tl] = 0;
            hp_free(ti);
        } else {
            tl = fui_strlen(f_host, c.host_max);
            if (tl < 0L || tl > c.title_max) {
                tl = c.title_max;
            }
            k = 0L;
            while (k < tl) {
                title[k] = f_host[k];
                k++;
            }
            title[tl] = 0;
        }
        f_text = tx;
        if (ui_wrap_text(f_text, strlen(f_text), (size_t)c.cols, &f_lay) != 0) {
            printf("freedomui: layout failed\n");
            hp_free(f_text);
            f_text = 0;
            return 1;
        }
    }
    freedomui_sys_title(title);
    if (fui_render(&c, 0) < 0L) {
        printf("freedomui: render failed\n");
        return 1;
    }
    printf("freedomui: %s (%ld bytes, %ld elems)%s\n", f_host, n, f_elems, f_truncated ? " (truncated)" : "");
    if (once) {
        return 0;
    }
    return (int)fui_browse(&c);
}
#endif
