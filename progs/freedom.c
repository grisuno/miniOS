/* freedom - a headless text browser for MiniOS.
 *
 * The engine is a minimal HTTP/1.0 client and an HTML filter in the
 * spirit of curlfree (http.c + htmlfilter.c): a bounded header phase,
 * Content-Length or EOF body reading, Transfer-Encoding: chunked
 * decoding, redirect chasing with a hop bound, and a filter that
 * strips tags, skips comments, suppresses script/style, decodes
 * entities and collapses whitespace. The command-line behaviour
 * follows FreeDom: an argument that is not a URL is a DuckDuckGo HTML
 * (no-JS) search over https, any non-http scheme is searched and never
 * executed, bare hosts are fetched as https:// (Secure by Default),
 * explicit http:// stays http so the host dev loop keeps working, and
 * remote page bytes pass a UTF-8 gate before reaching the console.
 * The User-Agent is a fixed anti-fingerprinting identity.
 *
 * https:// runs the same dialogue over the kernel TLS syscalls
 * (tls_handshake/tls_send/tls_recv, MiniOS 201-203) after the TCP
 * connect, so freedom never touches key material itself.
 *
 * Headless dumps (the FreeDom agent surface MiniOS can carry, no JS):
 *   freedom --dump-css <url>   collected author CSS + linked sheets
 *   freedom --dump-dom <url>   element outline (tag#id.class, depth)
 * Dump modes suppress the normal filtered text.
 *
 * All filter state lives in file-scope variables so a tag or entity
 * split between two network chunks is still decoded.
 *
 * usage: freedom [--dump-css|--dump-dom] [url-or-query]
 */

int socket(int domain, int type, int proto);
int connect(int fd, void *addr, int addrlen);
int sendto(int fd, char *buf, int len, int flags, void *to, int tolen);
int recvfrom(int fd, char *buf, int len, int flags, void *from, int *fromlen);
int close(int fd);
int net_dns_resolve(char *host);
int tls_handshake(int fd, char *host);
int tls_send(int fd, char *buf, int len);
int tls_recv(int fd, char *buf, int len);
int printf(char *fmt, ...);
int puts(char *s);
int strlen(char *s);
char *strchr(char *s, int c);
int strcmp(char *a, char *b);
int strncmp(char *a, char *b, int n);
int memcpy(char *dst, char *src, int n);
int memset(char *dst, int c, int n);
int putchar(int c);

#define FREEDOM_HOPS_MAX 3
#define FREEDOM_HDR_MAX  16384
#define FREEDOM_BUF      768
#define FREEDOM_CHUNK_MAX 16777216
#define FREEDOM_CSS_MAX  8
#define FREEDOM_CSS_BUF  8192
#define FREEDOM_DOM_BUF  8192
#define FREEDOM_ATTR_MAX 96
#define FREEDOM_LINE_MAX 160

static char f_host[64];
static char f_path[128];
static int  f_port;
static int  f_secure;

static char f_loc[192];
static int  f_redir;
static int  f_status;
static int  f_clen;
static int  f_has_clen;
static int  f_chunked;
static char f_hdr[FREEDOM_HDR_MAX];
static int  f_hlen;

/* filter state */
static int  f_tag;
static int  f_suppress;
static int  f_comment;
static int  f_cmdash;
static char f_tagn[8];
static int  f_tagnlen;
static char f_ent[8];
static int  f_entlen;
static int  f_ws;
static char f_utbuf[4];
static int  f_utlen;
static int  f_utrem;

/* attribute parsing */
static int  f_attr_on;
static int  f_waitq;
static int  f_inval;
static int  f_inval2;
static char f_attr[8];
static int  f_attrlen;
static char f_val[FREEDOM_ATTR_MAX];
static int  f_vallen;
static char f_id[32];
static int  f_idlen;
static char f_cls[32];
static int  f_clslen;
static char f_href[128];
static int  f_hreflen;
static int  f_rel_ss;
static char f_styleattr[FREEDOM_ATTR_MAX];
static int  f_stylelen;

/* dump state */
static int  f_dump_css;
static int  f_dump_dom;
static int  f_mode;      /* 0 text, 1 raw css body, 2 dom only */
static int  f_rawcap;    /* capturing a <style> block */
static int  f_depth;
static char f_dom[FREEDOM_DOM_BUF];
static int  f_domlen;
static char f_css[FREEDOM_CSS_BUF];
static int  f_csslen;
static char f_linkhost[FREEDOM_CSS_MAX][64];
static char f_linkpath[FREEDOM_CSS_MAX][128];
static int  f_linkn;

static int  f_cstage;
static int  f_csize;
static int  f_crem;
static int  f_bdone;

/* Decimal string to int (the ld stub set has no atol). */
static int atoi(char *s) {
    int v, i;
    v = 0;
    i = 0;
    while (s[i] >= '0' && s[i] <= '9') {
        v = v * 10 + (s[i] - '0');
        i++;
    }
    return v;
}

/* Append src to dst at pos; returns the new length or -1 when it does
 * not fit. */
static int append(char *dst, int pos, char *src, int cap) {
    int n;
    n = strlen(src);
    if (pos + n >= cap) return -1;
    memcpy(dst + pos, src, n);
    dst[pos + n] = 0;
    return pos + n;
}

static int ci_lower(int c) {
    if (c >= 'A' && c <= 'Z') return c + ('a' - 'A');
    return c;
}

/* Case-insensitive starts-with. */
static int ci_starts(char *s, char *pre) {
    while (*pre) {
        if (!*s) return 0;
        if (ci_lower(*s) != ci_lower(*pre)) return 0;
        s++;
        pre++;
    }
    return 1;
}

/* Case-insensitive equality. */
static int ci_eq(char *a, char *b) {
    while (*a && *b) {
        if (ci_lower(*a) != ci_lower(*b)) return 0;
        a++;
        b++;
    }
    return *a == 0 && *b == 0;
}

/* Case-insensitive index of needle in haystack, or -1. */
static int ci_index(char *s, char *needle) {
    int i;
    for (i = 0; s[i]; i++) {
        if (ci_starts(s + i, needle)) return i;
    }
    return -1;
}

/* Does the input look like an URL (no spaces, contains a dot)? */
static int looks_like_url(char *s) {
    int dot;
    dot = 0;
    while (*s) {
        if (*s == ' ' || *s == '\t') return 0;
        if (*s == '.') dot = 1;
        s++;
    }
    return dot;
}

/* Does s begin with "<scheme>:" per RFC 3986 (ALPHA
 * *(ALPHA/DIGIT/+/-/.) ":")? Any such prefix makes the string a scheme,
 * and the omnibox policy is: only http:// and https:// are executed. */
static int has_scheme(char *s) {
    int i;
    char c;
    c = s[0];
    if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) return 0;
    for (i = 1; s[i]; i++) {
        c = s[i];
        if (c == ':') return 1;
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
              (c >= '0' && c <= '9') || c == '+' || c == '-' || c == '.'))
            return 0;
    }
    return 0;
}

/* Encode a query for the DuckDuckGo HTML endpoint (no-JS). */
static void make_search(char *out, char *query, int cap) {
    int pos;
    pos = append(out, 0, "/html/?q=", cap);
    while (*query && pos < cap - 4) {
        if (*query == ' ') {
            pos = append(out, pos, "+", cap);
        } else if (*query == '&') {
            pos = append(out, pos, "%26", cap);
        } else if (*query == '=') {
            pos = append(out, pos, "%3D", cap);
        } else if (*query == '+') {
            pos = append(out, pos, "%2B", cap);
        } else {
            out[pos++] = *query;
            out[pos] = 0;
        }
        query++;
    }
}

/* Split an http:// or https:// URL into f_host, f_path, f_port and
 * f_secure. Returns 0 on failure. The input buffer is never modified:
 * the parse is index-only, so it stays valid when the compiler widens
 * dereferenced stores. */
static int split_url(char *url) {
    char *p;
    int hl, plen, k, v, defport;
    if (strncmp(url, "https://", 8) == 0) {
        f_secure = 1;
        defport = 443;
        p = url + 8;
    } else if (strncmp(url, "http://", 7) == 0) {
        f_secure = 0;
        defport = 80;
        p = url + 7;
    } else {
        return 0;
    }
    hl = 0;
    while (p[hl] && p[hl] != ':' && p[hl] != '/' && hl < 64) hl++;
    if (hl < 1 || hl >= 64) return 0;
    memcpy(f_host, p, hl);
    f_host[hl] = 0;
    f_port = defport;
    if (p[hl] == ':') {
        k = hl + 1;
        v = 0;
        while (p[k] >= '0' && p[k] <= '9') {
            v = v * 10 + (p[k] - '0');
            k++;
        }
        if (v <= 0 || v > 65535) return 0;
        if (p[k] != '/' && p[k] != 0) return 0;
        f_port = v;
        hl = k;
    }
    if (p[hl] == '/') {
        plen = strlen(p + hl);
        if (plen >= 128) return 0;
        memcpy(f_path, p + hl, plen);
        f_path[plen] = 0;
    } else {
        f_path[0] = '/';
        f_path[1] = 0;
    }
    return 1;
}

/* Recompute f_host/f_path/f_port/f_secure from the last Location
 * value. Returns 1 when the chase may continue, 0 when it must stop
 * (diagnostic already printed). */
static int resolve_redirect(void) {
    char tmp[192];
    char *loc;
    int pos;
    loc = f_loc;
    if (strncmp(loc, "https://", 8) == 0) {
        return split_url(loc);
    }
    if (strncmp(loc, "http://", 7) == 0) {
        return split_url(loc);
    }
    if (loc[0] == '/' && loc[1] == '/') {
        pos = append(tmp, 0, f_secure ? "https:" : "http:", 192);
        pos = append(tmp, pos, loc, 192);
        if (pos < 0) return 0;
        return split_url(tmp);
    }
    if (has_scheme(loc)) {
        puts("freedom: redirect scheme refused");
        return 0;
    }
    if (loc[0] == '/') {
        int l;
        l = strlen(loc);
        if (l >= 128) return 0;
        memcpy(f_path, loc, l);
        f_path[l] = 0;
        return 1;
    }
    {
        int i, last, l, plen;
        plen = strlen(f_path);
        last = -1;
        for (i = 0; i < plen; i++) {
            if (f_path[i] == '/') last = i;
        }
        l = strlen(loc);
        if (last < 0) {
            if (l + 1 >= 128) return 0;
            f_path[0] = '/';
            memcpy(f_path + 1, loc, l);
            f_path[l + 1] = 0;
        } else {
            if (last + 1 + l >= 128) return 0;
            memcpy(f_path + last + 1, loc, l);
            f_path[last + 1 + l] = 0;
        }
    }
    return 1;
}

/* --- HTML filter -------------------------------------------------- */

static void put_ws(void) {
    if (!f_ws && f_mode == 0) {
        putchar(' ');
        f_ws = 1;
    }
}

/* Print one text byte through the UTF-8 gate. Remote pages are
 * hostile data: bytes outside a valid UTF-8 sequence (overlong,
 * surrogate, out of range) are replaced with '?' (FreeDom policy).
 * Sequence state is kept in f_utbuf/f_utlen/f_utrem. */
static void put_utf(int c) {
    int k;
    c = c & 255;
    if (c < 128) {
        putchar(c);
        return;
    }
    if (f_utrem == 0) {
        int len;
        len = 0;
        if (c >= 194 && c <= 223) len = 2;
        else if (c >= 224 && c <= 239) len = 3;
        else if (c >= 240 && c <= 244) len = 4;
        if (!len) {
            putchar('?');
            return;
        }
        f_utbuf[0] = c;
        f_utlen = 1;
        f_utrem = len - 1;
        return;
    }
    if ((c & 192) != 128) {
        f_utrem = 0;
        f_utlen = 0;
        putchar('?');
        put_utf(c);
        return;
    }
    f_utbuf[f_utlen] = c;
    f_utlen++;
    f_utrem--;
    if (f_utrem == 0) {
        int ok;
        ok = 1;
        if ((f_utbuf[0] & 255) == 224 && (f_utbuf[1] & 255) < 160) ok = 0;
        if ((f_utbuf[0] & 255) == 237 && (f_utbuf[1] & 255) > 159) ok = 0;
        if ((f_utbuf[0] & 255) == 240 && (f_utbuf[1] & 255) < 144) ok = 0;
        if ((f_utbuf[0] & 255) == 244 && (f_utbuf[1] & 255) > 143) ok = 0;
        if (ok) {
            for (k = 0; k < f_utlen; k++) putchar(f_utbuf[k]);
        } else {
            putchar('?');
        }
        f_utlen = 0;
    }
}

/* Print one text byte: whitespace collapses, everything else goes
 * through the UTF-8 gate. Dump modes suppress the page text. */
static void put_text(int c) {
    if (f_mode != 0) return;
    if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
        put_ws();
        return;
    }
    f_ws = 0;
    put_utf(c);
}

/* Decode the entity whose body (between & and ;) is e[0..]. Unknown
 * entities are echoed verbatim (htmlfilter.c). */
static void put_entity(char *e) {
    if (strcmp(e, "amp") == 0) put_text('&');
    else if (strcmp(e, "lt") == 0) put_text('<');
    else if (strcmp(e, "gt") == 0) put_text('>');
    else if (strcmp(e, "quot") == 0) put_text('"');
    else if (strcmp(e, "apos") == 0) put_text('\'');
    else if (strcmp(e, "nbsp") == 0) put_text(' ');
    else if (e[0] == '#') {
        int v, k;
        v = 0;
        k = 1;
        if (e[1] == 'x' || e[1] == 'X') k = 2;
        while (e[k]) {
            char h;
            h = e[k];
            if (e[1] == 'x' || e[1] == 'X') {
                if (h >= '0' && h <= '9') v = v * 16 + h - '0';
                else if (h >= 'a' && h <= 'f') v = v * 16 + h - 'a' + 10;
                else if (h >= 'A' && h <= 'F') v = v * 16 + h - 'A' + 10;
            } else if (h >= '0' && h <= '9') {
                v = v * 10 + h - '0';
            }
            k++;
        }
        if (v == 10 || v == 13) put_ws();
        else if (v >= 32 && v < 127) put_text(v);
        else if (v >= 128 && v < 2048) {
            put_text(192 | (v >> 6));
            put_text(128 | (v & 63));
        } else if (v >= 2048 && v < 65536) {
            put_text(224 | (v >> 12));
            put_text(128 | ((v >> 6) & 63));
            put_text(128 | (v & 63));
        }
    } else {
        int k;
        put_text('&');
        for (k = 0; e[k]; k++) put_text(e[k]);
        put_text(';');
    }
}

/* --- dump capture helpers ------------------------------------------ */

static void css_append(char *s, int n) {
    int i;
    for (i = 0; i < n && f_csslen < FREEDOM_CSS_BUF - 1; i++)
        f_css[f_csslen++] = s[i];
}

static void css_line(char *s) {
    css_append(s, strlen(s));
    if (f_csslen < FREEDOM_CSS_BUF - 1) f_css[f_csslen++] = '\n';
}

static void dom_append(char *s, int n) {
    int i;
    for (i = 0; i < n && f_domlen < FREEDOM_DOM_BUF - 1; i++)
        f_dom[f_domlen++] = s[i];
}

static void dom_space(void) {
    if (f_domlen < FREEDOM_DOM_BUF - 1) f_dom[f_domlen++] = ' ';
}

static void dom_nl(void) {
    if (f_domlen < FREEDOM_DOM_BUF - 1) f_dom[f_domlen++] = '\n';
}

/* Record the finished attribute in its place. */
static void record_attr(void) {
    if (f_attrlen == 0 || f_vallen == 0) return;
    if (ci_eq(f_attr, "id")) {
        f_idlen = f_vallen < 31 ? f_vallen : 31;
        memcpy(f_id, f_val, f_idlen);
        f_id[f_idlen] = 0;
    } else if (ci_eq(f_attr, "class")) {
        f_clslen = f_vallen < 31 ? f_vallen : 31;
        memcpy(f_cls, f_val, f_clslen);
        f_cls[f_clslen] = 0;
    } else if (ci_eq(f_attr, "href")) {
        f_hreflen = f_vallen < 127 ? f_vallen : 127;
        memcpy(f_href, f_val, f_hreflen);
        f_href[f_hreflen] = 0;
    } else if (ci_eq(f_attr, "style")) {
        f_stylelen = f_vallen < (FREEDOM_ATTR_MAX - 1) ? f_vallen
                                                       : (FREEDOM_ATTR_MAX - 1);
        memcpy(f_styleattr, f_val, f_stylelen);
        f_styleattr[f_stylelen] = 0;
    } else if (ci_eq(f_attr, "rel")) {
        f_rel_ss = ci_index(f_val, "stylesheet") >= 0;
    }
}

/* Is tagname a void element (no closing tag, no children)? */
static int is_void_tag(void) {
    return ci_eq(f_tagn, "br") || ci_eq(f_tagn, "img") ||
           ci_eq(f_tagn, "meta") || ci_eq(f_tagn, "link") ||
           ci_eq(f_tagn, "input") || ci_eq(f_tagn, "hr") ||
           ci_eq(f_tagn, "area") || ci_eq(f_tagn, "base") ||
           ci_eq(f_tagn, "col") || ci_eq(f_tagn, "embed") ||
           ci_eq(f_tagn, "param") || ci_eq(f_tagn, "source") ||
           ci_eq(f_tagn, "track") || ci_eq(f_tagn, "wbr");
}

/* A tag was fully collected into f_tagn (+ attributes). Decide what it
 * does to the stream and the dumps. */
static void classify_tag(void) {
    f_tagn[f_tagnlen] = 0;
    if (f_tagnlen == 0) return;
    if (f_tagn[0] == '!') {
        if (f_tagnlen >= 3 && f_tagn[1] == '-' && f_tagn[2] == '-') {
            f_comment = 1;
            f_cmdash = 0;
        }
        return;
    }
    if (f_tagn[0] == '/') {
        if (ci_eq(f_tagn + 1, "script") || ci_eq(f_tagn + 1, "style")) {
            f_suppress = 0;
        } else if (f_dump_dom && f_depth > 0) {
            f_depth--;
        }
        return;
    }
    if (ci_eq(f_tagn, "script") || ci_eq(f_tagn, "style")) {
        f_suppress = 1;
        if (f_dump_css && ci_eq(f_tagn, "style")) {
            css_line("== style ==");
            f_rawcap = 1;
        }
        return;
    }
    if (f_dump_css) {
        if (f_stylelen > 0) {
            char line[FREEDOM_LINE_MAX];
            int pos;
            pos = 0;
            pos = append(line, pos, f_tagn, FREEDOM_LINE_MAX);
            if (f_idlen > 0) {
                pos = append(line, pos, "#", FREEDOM_LINE_MAX);
                pos = append(line, pos, f_id, FREEDOM_LINE_MAX);
            }
            if (f_clslen > 0) {
                pos = append(line, pos, ".", FREEDOM_LINE_MAX);
                pos = append(line, pos, f_cls, FREEDOM_LINE_MAX);
            }
            pos = append(line, pos, " { ", FREEDOM_LINE_MAX);
            pos = append(line, pos, f_styleattr, FREEDOM_LINE_MAX);
            if (f_stylelen > 0 && f_styleattr[f_stylelen - 1] != ';')
                pos = append(line, pos, ";", FREEDOM_LINE_MAX);
            pos = append(line, pos, " }", FREEDOM_LINE_MAX);
            if (pos >= 0) css_line(line);
        }
        if (ci_eq(f_tagn, "link") && f_rel_ss && f_hreflen > 0 &&
            !ci_starts(f_href, "http://") && !ci_starts(f_href, "https://") &&
            f_linkn < FREEDOM_CSS_MAX) {
            memcpy(f_linkhost[f_linkn], f_host, 63);
            f_linkhost[f_linkn][63] = 0;
            memcpy(f_linkpath[f_linkn], f_href, 127);
            f_linkpath[f_linkn][127] = 0;
            f_linkn++;
        }
    }
    if (f_dump_dom) {
        int i;
        for (i = 0; i < f_depth && i < 12; i++) {
            dom_space();
            dom_space();
        }
        dom_append(f_tagn, f_tagnlen);
        if (f_idlen > 0) {
            dom_append("#", 1);
            dom_append(f_id, f_idlen);
        }
        if (f_clslen > 0) {
            dom_append(".", 1);
            dom_append(f_cls, f_clslen);
        }
        dom_nl();
        if (!is_void_tag()) f_depth++;
    }
    if (ci_eq(f_tagn, "br") || ci_eq(f_tagn, "p") || ci_eq(f_tagn, "div") ||
        ci_eq(f_tagn, "h1") || ci_eq(f_tagn, "h2") || ci_eq(f_tagn, "h3") ||
        ci_eq(f_tagn, "h4") || ci_eq(f_tagn, "h5") || ci_eq(f_tagn, "h6") ||
        ci_eq(f_tagn, "li") || ci_eq(f_tagn, "tr")) {
        if (f_mode == 0) putchar('\n');
        f_ws = 1;
    }
}

/* Feed one body byte into the filter. */
static void body_byte(int c) {
    int k;
    if (f_comment) {
        if (c == '-') f_cmdash++;
        else if (c == '>' && f_cmdash >= 2) {
            f_comment = 0;
            f_cmdash = 0;
        } else f_cmdash = 0;
        return;
    }
    if (f_suppress) {
        if (c == '<') {
            f_tag = 1;
            f_tagnlen = 0;
            return;
        }
        if (f_tag) {
            if (c == '>') {
                f_tag = 0;
                f_tagn[f_tagnlen] = 0;
                if (f_tagnlen > 0 && f_tagn[0] == '/' &&
                    (ci_eq(f_tagn + 1, "script") ||
                     ci_eq(f_tagn + 1, "style"))) {
                    f_suppress = 0;
                    if (f_rawcap && ci_eq(f_tagn + 1, "style")) {
                        if (f_csslen < FREEDOM_CSS_BUF - 1)
                            f_css[f_csslen++] = '\n';
                        f_rawcap = 0;
                    }
                }
            } else if (c != ' ' && c != '\t' && f_tagnlen < 7) {
                f_tagn[f_tagnlen++] = c;
            }
            return;
        }
        if (f_rawcap && f_csslen < FREEDOM_CSS_BUF - 1)
            f_css[f_csslen++] = c;
        return;
    }
    if (f_tag) {
        if (f_inval) {
            if (c == '"') {
                f_inval = 0;
                record_attr();
            } else if (f_vallen < FREEDOM_ATTR_MAX - 1) {
                f_val[f_vallen++] = c;
            }
            return;
        }
        if (f_inval2) {
            if (c == ' ' || c == '\t') {
                f_inval2 = 0;
                record_attr();
                return;
            }
            if (c == '>') {
                f_inval2 = 0;
                record_attr();
                f_tag = 0;
                classify_tag();
                return;
            }
            if (f_vallen < FREEDOM_ATTR_MAX - 1) f_val[f_vallen++] = c;
            return;
        }
        if (f_waitq) {
            if (c == '"') {
                f_waitq = 0;
                f_inval = 1;
            } else if (c == '>') {
                f_waitq = 0;
                f_tag = 0;
                record_attr();
                classify_tag();
            } else if (c != ' ' && c != '\t') {
                f_waitq = 0;
                f_inval2 = 1;
                f_vallen = 1;
                f_val[0] = c;
            }
            return;
        }
        if (f_attr_on) {
            if (c == '=') {
                f_attr_on = 0;
                f_waitq = 1;
                f_vallen = 0;
            } else if (c != ' ' && c != '\t' && f_attrlen < 7) {
                f_attr[f_attrlen++] = c;
                f_attr[f_attrlen] = 0;
            }
            return;
        }
        if (c == '>') {
            f_tag = 0;
            classify_tag();
            return;
        }
        if (c == ' ' || c == '\t') {
            if (f_tagnlen > 0) {
                f_attr_on = 1;
                f_attrlen = 0;
            }
            return;
        }
        if (c == '/') {
            /* a closing tag starts with '/'; self-closing slashes come
             * after the tag name and are ignored */
            if (f_tagnlen == 0) f_tagn[f_tagnlen++] = c;
            return;
        }
        if (f_tagnlen < 7) {
            f_tagn[f_tagnlen++] = c;
            if (f_tagnlen == 3 && f_tagn[0] == '!' &&
                f_tagn[1] == '-' && f_tagn[2] == '-') {
                f_tag = 0;
                f_comment = 1;
                f_cmdash = 0;
            }
        }
        return;
    }
    if (f_entlen > 0) {
        if (c == ';') {
            f_ent[f_entlen - 1] = 0;
            f_entlen = 0;
            put_entity(f_ent);
        } else if (f_entlen <= 7) {
            f_ent[f_entlen - 1] = c;
            f_entlen++;
        } else {
            put_text('&');
            for (k = 0; k < f_entlen - 1; k++) put_text(f_ent[k]);
            f_entlen = 0;
            body_byte(c);
        }
        return;
    }
    if (c == '<') {
        f_tag = 1;
        f_tagnlen = 0;
        f_attr_on = 0;
        f_waitq = 0;
        f_inval = 0;
        f_inval2 = 0;
        f_attrlen = 0;
        f_vallen = 0;
        f_idlen = 0;
        f_clslen = 0;
        f_hreflen = 0;
        f_stylelen = 0;
        f_rel_ss = 0;
        return;
    }
    if (c == '&') {
        f_entlen = 1;
        f_ent[0] = 0;
        return;
    }
    put_text(c);
}

/* --- HTTP ---------------------------------------------------------- */

/* Classify one header line (NUL-terminated). */
static void head_line(char *line) {
    char *p;
    int v;
    if (ci_starts(line, "location:")) {
        p = line + 9;
        while (*p == ' ' || *p == '\t') p++;
        v = 0;
        while (p[v] && v < 191) {
            f_loc[v] = p[v];
            v++;
        }
        f_loc[v] = 0;
        f_redir = 1;
    } else if (ci_starts(line, "content-length:")) {
        p = line + 15;
        while (*p == ' ' || *p == '\t') p++;
        f_clen = atoi(p);
        f_has_clen = 1;
    } else if (ci_starts(line, "transfer-encoding:")) {
        if (ci_index(line, "chunked") >= 0) f_chunked = 1;
    }
}

/* Parse the collected header block f_hdr[0..f_hlen-1] (the last four
 * bytes are the terminating CRLF CRLF). */
static void parse_head(void) {
    int i, lend;
    i = 0;
    while (i + 1 <= f_hlen - 4) {
        lend = i;
        while (lend + 1 <= f_hlen - 4 &&
               !(f_hdr[lend] == '\r' && f_hdr[lend + 1] == '\n'))
            lend++;
        f_hdr[lend] = 0;
        if (i == 0) {
            char *sp;
            sp = strchr(f_hdr, ' ');
            if (sp) f_status = atoi(sp + 1);
        } else if (lend > i) {
            head_line(f_hdr + i);
        }
        f_hdr[lend] = '\r';
        i = lend + 2;
    }
}

/* Receive body bytes: TLS for f_secure, plain TCP otherwise. */
static int recv_body(int fd, char *buf, int len) {
    if (f_secure) return tls_recv(fd, buf, len);
    return recvfrom(fd, buf, len, 0, 0, 0);
}

/* Send the whole request: TLS for f_secure, plain TCP otherwise. */
static int send_all(int fd, char *buf, int len) {
    if (f_secure) {
        if (tls_send(fd, buf, len) < 0) return -1;
        return len;
    }
    return sendto(fd, buf, len, 0, 0, 0);
}

/* Send one HTTP request and process the response body. Returns the
 * status code, or 0 on transport failure. Sets f_redir when a
 * Location header was seen. */
static int fetch(char *host, char *path, int port) {
    char sa[16];
    char buf[FREEDOM_BUF];
    char req[768];
    int fd, n, i, ip, pos, stage, got;

    ip = net_dns_resolve(host);
    if (ip < 0) {
        printf("freedom: cannot resolve %s\n", host);
        return 0;
    }
    fd = socket(2, 1, 0);
    if (fd < 0) {
        puts("freedom: socket failed");
        return 0;
    }
    memset(sa, 0, 16);
    sa[0] = 2;
    sa[2] = (port >> 8) & 255;
    sa[3] = port & 255;
    sa[4] = (ip >> 24) & 255;
    sa[5] = (ip >> 16) & 255;
    sa[6] = (ip >> 8) & 255;
    sa[7] = ip & 255;
    if (connect(fd, sa, 16) < 0) {
        printf("freedom: connect to %s failed\n", host);
        close(fd);
        return 0;
    }
    if (f_secure) {
        if (tls_handshake(fd, host) < 0) {
            printf("freedom: https handshake with %s failed\n", host);
            close(fd);
            return 0;
        }
    }

    pos = 0;
    pos = append(req, pos, "GET ", 768);
    pos = append(req, pos, path, 768);
    pos = append(req, pos, " HTTP/1.0\r\nHost: ", 768);
    pos = append(req, pos, host, 768);
    pos = append(req, pos, "\r\nUser-Agent: freedom/1.0 (MiniOS)", 768);
    pos = append(req, pos, "\r\nAccept: text/html", 768);
    pos = append(req, pos, "\r\nConnection: close\r\n\r\n", 768);
    if (send_all(fd, req, pos) < 0) {
        printf("freedom: send to %s failed\n", host);
        close(fd);
        return 0;
    }

    f_hlen = 0;
    f_status = 0;
    f_clen = 0;
    f_has_clen = 0;
    f_chunked = 0;
    f_redir = 0;
    f_cstage = 0;
    f_csize = 0;
    f_crem = 0;
    f_bdone = 0;
    f_tag = 0;
    f_suppress = 0;
    f_comment = 0;
    f_cmdash = 0;
    f_tagnlen = 0;
    f_entlen = 0;
    f_ws = 0;
    f_utlen = 0;
    f_utrem = 0;
    f_attr_on = 0;
    f_waitq = 0;
    f_inval = 0;
    f_inval2 = 0;
    f_rawcap = 0;
    f_depth = 0;
    f_idlen = 0;
    f_clslen = 0;
    f_hreflen = 0;
    f_stylelen = 0;
    f_rel_ss = 0;

    stage = 0;         /* 0 = header, 1 = body */
    got = 0;
    for (;;) {
        if (f_bdone) break;
        if (!f_chunked && f_has_clen && got >= f_clen) break;
        n = recv_body(fd, buf, FREEDOM_BUF);
        if (n <= 0) break;
        i = 0;
        while (i < n && !f_bdone) {
            int c;
            c = buf[i++];
            if (stage == 0) {
                if (f_hlen >= FREEDOM_HDR_MAX) {
                    close(fd);
                    puts("freedom: response header too large");
                    return 0;
                }
                f_hdr[f_hlen++] = c;
                if (f_hlen >= 4 &&
                    f_hdr[f_hlen - 4] == '\r' && f_hdr[f_hlen - 3] == '\n' &&
                    f_hdr[f_hlen - 2] == '\r' && f_hdr[f_hlen - 1] == '\n') {
                    parse_head();
                    stage = 1;
                }
                continue;
            }
            if (f_chunked) {
                if (f_cstage == 0) {
                    if (c == '\n') {
                        if (f_csize == 0) {
                            f_bdone = 1;
                        } else {
                            f_crem = f_csize;
                            f_csize = 0;
                            f_cstage = 1;
                        }
                    } else if (c != '\r') {
                        int d;
                        d = -1;
                        if (c >= '0' && c <= '9') d = c - '0';
                        else if (c >= 'a' && c <= 'f') d = c - 'a' + 10;
                        else if (c >= 'A' && c <= 'F') d = c - 'A' + 10;
                        if (d >= 0) f_csize = f_csize * 16 + d;
                        if (f_csize > FREEDOM_CHUNK_MAX) {
                            close(fd);
                            puts("freedom: chunk too large");
                            return 0;
                        }
                    }
                } else if (f_cstage == 1) {
                    body_byte(c);
                    got++;
                    f_crem--;
                    if (f_crem == 0) f_cstage = 2;
                } else if (f_cstage == 2) {
                    if (c == '\r') f_cstage = 3;
                    else if (c == '\n') f_cstage = 0;
                } else {
                    if (c == '\n') f_cstage = 0;
                }
            } else {
                if (f_has_clen && got >= f_clen) {
                    f_bdone = 1;
                    break;
                }
                body_byte(c);
                got++;
            }
        }
    }
    close(fd);
    if (f_mode == 0) putchar('\n');
    printf("freedom: %s (%d bytes)\n", host, got);
    return f_status;
}

/* Fetch a linked stylesheet and print its raw body (through the UTF-8
 * gate). No redirect chasing: the bound is one request. */
static void fetch_css(char *host, char *path) {
    char sa[16];
    char buf[FREEDOM_BUF];
    char req[768];
    int fd, n, i, ip, pos, stage, got;

    ip = net_dns_resolve(host);
    if (ip < 0) {
        printf("freedom: cannot resolve %s\n", host);
        return;
    }
    fd = socket(2, 1, 0);
    if (fd < 0) return;
    memset(sa, 0, 16);
    sa[0] = 2;
    sa[2] = (f_port >> 8) & 255;
    sa[3] = f_port & 255;
    sa[4] = (ip >> 24) & 255;
    sa[5] = (ip >> 16) & 255;
    sa[6] = (ip >> 8) & 255;
    sa[7] = ip & 255;
    if (connect(fd, sa, 16) < 0) {
        printf("freedom: connect to %s failed\n", host);
        close(fd);
        return;
    }
    if (f_secure) {
        if (tls_handshake(fd, host) < 0) {
            printf("freedom: https handshake with %s failed\n", host);
            close(fd);
            return;
        }
    }
    pos = 0;
    pos = append(req, pos, "GET ", 768);
    pos = append(req, pos, path, 768);
    pos = append(req, pos, " HTTP/1.0\r\nHost: ", 768);
    pos = append(req, pos, host, 768);
    pos = append(req, pos, "\r\nUser-Agent: freedom/1.0 (MiniOS)", 768);
    pos = append(req, pos, "\r\nConnection: close\r\n\r\n", 768);
    if (send_all(fd, req, pos) < 0) {
        close(fd);
        return;
    }
    f_hlen = 0;
    stage = 0;
    got = 0;
    for (;;) {
        n = recv_body(fd, buf, FREEDOM_BUF);
        if (n <= 0) break;
        i = 0;
        while (i < n) {
            int c;
            c = buf[i++];
            if (stage == 0) {
                f_hdr[f_hlen++] = c;
                if (f_hlen >= FREEDOM_HDR_MAX) {
                    close(fd);
                    return;
                }
                if (f_hlen >= 4 &&
                    f_hdr[f_hlen - 4] == '\r' && f_hdr[f_hlen - 3] == '\n' &&
                    f_hdr[f_hlen - 2] == '\r' && f_hdr[f_hlen - 1] == '\n') {
                    stage = 1;
                }
                continue;
            }
            f_ws = 0;
            put_utf(c);
            got++;
        }
    }
    close(fd);
    putchar('\n');
    printf("freedom: %s (%d bytes)\n", host, got);
}

/* Print the collected CSS dump. */
static void print_css_dump(void) {
    int i;
    puts("=== freedom css ===");
    for (i = 0; i < f_csslen; i++) put_utf(f_css[i]);
    if (f_csslen == 0) puts("(no css)");
    if (f_linkn > 0) putchar('\n');
}

/* Print the collected DOM outline. */
static void print_dom_dump(void) {
    int i;
    puts("=== freedom dom ===");
    for (i = 0; i < f_domlen; i++) put_utf(f_dom[i]);
    if (f_domlen == 0) puts("(no dom)");
}

int main(int argc, char **argv) {
    char url[192];
    int hops;
    int argidx;
    int i;

    f_dump_css = 0;
    f_dump_dom = 0;
    f_mode = 0;
    f_csslen = 0;
    f_domlen = 0;
    f_linkn = 0;
    argidx = 1;
    if (argc < 2) {
        puts("usage: freedom [--dump-css|--dump-dom] [url-or-query]");
        return 1;
    }
    if (strcmp(argv[1], "--dump-css") == 0) {
        f_dump_css = 1;
        f_mode = 1;
        argidx = 2;
        if (argc < 3) {
            puts("usage: freedom --dump-css <url>");
            return 1;
        }
    } else if (strcmp(argv[1], "--dump-dom") == 0) {
        f_dump_dom = 1;
        f_mode = 2;
        argidx = 2;
        if (argc < 3) {
            puts("usage: freedom --dump-dom <url>");
            return 1;
        }
    } else if (argv[1][0] == '-' && argv[1][1] == '-') {
        printf("freedom: unknown flag %s\n", argv[1]);
        puts("usage: freedom [--dump-css|--dump-dom] [url-or-query]");
        return 1;
    }

    if (has_scheme(argv[argidx])) {
        if (strncmp(argv[argidx], "https://", 8) == 0) {
            int l;
            l = strlen(argv[argidx]);
            if (l >= 192) l = 191;
            memcpy(url, argv[argidx], l);
            url[l] = 0;
        } else if (strncmp(argv[argidx], "http://", 7) == 0) {
            int l;
            l = strlen(argv[argidx]);
            if (l >= 192) l = 191;
            memcpy(url, argv[argidx], l);
            url[l] = 0;
        } else {
            make_search(f_path, argv[argidx], 128);
            memcpy(f_host, "html.duckduckgo.com", 19);
            f_host[19] = 0;
            f_port = 443;
            f_secure = 1;
            fetch(f_host, f_path, f_port);
            if (f_dump_css) print_css_dump();
            if (f_dump_dom) print_dom_dump();
            return 0;
        }
    } else if (looks_like_url(argv[argidx])) {
        /* Secure by Default: a bare host is fetched over https */
        append(url, 0, "https://", 192);
        append(url, 8, argv[argidx], 192);
    } else {
        make_search(f_path, argv[argidx], 128);
        memcpy(f_host, "html.duckduckgo.com", 19);
        f_host[19] = 0;
        f_port = 443;
        f_secure = 1;
        fetch(f_host, f_path, f_port);
        if (f_dump_css) print_css_dump();
        if (f_dump_dom) print_dom_dump();
        return 0;
    }
    if (!split_url(url)) {
        printf("freedom: cannot parse %s\n", url);
        return 3;
    }
    hops = 0;
    for (;;) {
        int status;
        status = fetch(f_host, f_path, f_port);
        if (status >= 300 && status < 400 && f_redir) {
            if (hops >= FREEDOM_HOPS_MAX) {
                puts("freedom: too many redirects");
                break;
            }
            hops++;
            if (resolve_redirect()) continue;
        }
        break;
    }
    if (f_dump_css) {
        print_css_dump();
        if (f_linkn > 0) {
            for (i = 0; i < f_linkn; i++) {
                printf("\n== %s ==\n", f_linkpath[i]);
                fetch_css(f_linkhost[i], f_linkpath[i]);
            }
        }
    }
    if (f_dump_dom) print_dom_dump();
    return 0;
}
