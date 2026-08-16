/* freedom - a headless text browser for MiniOS.
 *
 * The engine is a minimal HTTP/1.0 client and an HTML filter in the
 * spirit of curlfree (http.c + htmlfilter.c): a bounded header phase,
 * Content-Length or EOF body reading, Transfer-Encoding: chunked
 * decoding, redirect chasing with a hop bound, and a filter that
 * strips tags, skips comments, suppresses script/style, decodes
 * entities and collapses whitespace. The command-line behaviour
 * follows FreeDom: an argument that is not a URL is a DuckDuckGo HTML
 * (no-JS) search, any non-http scheme is searched and never executed,
 * remote page bytes pass a UTF-8 gate before reaching the console,
 * and the User-Agent is a fixed anti-fingerprinting identity.
 *
 * All filter state lives in file-scope variables so a tag or entity
 * split between two network chunks is still decoded.
 *
 * usage: freedom [url-or-query]
 */

int socket(int domain, int type, int proto);
int connect(int fd, void *addr, int addrlen);
int sendto(int fd, char *buf, int len, int flags, void *to, int tolen);
int recvfrom(int fd, char *buf, int len, int flags, void *from, int *fromlen);
int close(int fd);
int net_dns_resolve(char *host);
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
#define FREEDOM_HDR_MAX  2048
#define FREEDOM_BUF      768
#define FREEDOM_CHUNK_MAX 16777216

static char f_host[64];
static char f_path[128];
static int  f_port;

static char f_loc[192];
static int  f_redir;
static int  f_status;
static int  f_clen;
static int  f_has_clen;
static int  f_chunked;
static char f_hdr[FREEDOM_HDR_MAX];
static int  f_hlen;

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
 * and the omnibox policy is: only http:// is executed. */
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

/* Split an http:// URL into f_host, f_path and f_port. Returns 0 on
 * failure. The input buffer is never modified: the parse is index-only,
 * so it stays valid when the compiler widens dereferenced stores. */
static int split_url(char *url) {
    char *p;
    int hl, plen, k, v;
    if (strncmp(url, "http://", 7) != 0) return 0;
    p = url + 7;
    hl = 0;
    while (p[hl] && p[hl] != ':' && p[hl] != '/' && hl < 64) hl++;
    if (hl < 1 || hl >= 64) return 0;
    memcpy(f_host, p, hl);
    f_host[hl] = 0;
    f_port = 80;
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

/* Recompute f_host/f_path/f_port from the last Location value. Returns
 * 1 when the chase may continue, 0 when it must stop (diagnostic
 * already printed). */
static int resolve_redirect(void) {
    char tmp[192];
    char *loc;
    int pos;
    loc = f_loc;
    if (strncmp(loc, "https://", 8) == 0) {
        puts("freedom: https needs TLS, which MiniOS does not speak yet");
        return 0;
    }
    if (strncmp(loc, "http://", 7) == 0) {
        return split_url(loc);
    }
    if (loc[0] == '/' && loc[1] == '/') {
        pos = append(tmp, 0, "http:", 192);
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
    if (!f_ws) {
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
 * through the UTF-8 gate. */
static void put_text(int c) {
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

/* A tag was fully collected into f_tagn. Decide what it does to the
 * stream. */
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
        if (ci_eq(f_tagn + 1, "script") || ci_eq(f_tagn + 1, "style"))
            f_suppress = 0;
        return;
    }
    if (ci_eq(f_tagn, "script") || ci_eq(f_tagn, "style")) {
        f_suppress = 1;
        return;
    }
    if (ci_eq(f_tagn, "br") || ci_eq(f_tagn, "p") || ci_eq(f_tagn, "div") ||
        ci_eq(f_tagn, "h1") || ci_eq(f_tagn, "h2") || ci_eq(f_tagn, "h3") ||
        ci_eq(f_tagn, "h4") || ci_eq(f_tagn, "h5") || ci_eq(f_tagn, "h6") ||
        ci_eq(f_tagn, "li") || ci_eq(f_tagn, "tr")) {
        putchar('\n');
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
        } else if (c == '>' && f_tag) {
            f_tag = 0;
            f_tagn[f_tagnlen] = 0;
            if (f_tagnlen > 0 && f_tagn[0] == '/' &&
                (ci_eq(f_tagn + 1, "script") || ci_eq(f_tagn + 1, "style")))
                f_suppress = 0;
        } else if (f_tag && c != ' ' && c != '\t' && f_tagnlen < 7) {
            f_tagn[f_tagnlen++] = c;
        }
        return;
    }
    if (f_tag) {
        if (c == '>') {
            f_tag = 0;
            classify_tag();
        } else if (c != ' ' && c != '\t' && f_tagnlen < 7) {
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

/* Send one HTTP request and print the filtered response body. Returns
 * the status code, or 0 on transport failure. Sets f_redir when a
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

    pos = 0;
    pos = append(req, pos, "GET ", 768);
    pos = append(req, pos, path, 768);
    pos = append(req, pos, " HTTP/1.0\r\nHost: ", 768);
    pos = append(req, pos, host, 768);
    pos = append(req, pos, "\r\nUser-Agent: freedom/1.0 (MiniOS)", 768);
    pos = append(req, pos, "\r\nAccept: text/html", 768);
    pos = append(req, pos, "\r\nConnection: close\r\n\r\n", 768);
    sendto(fd, req, pos, 0, 0, 0);

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

    stage = 0;         /* 0 = header, 1 = body */
    got = 0;
    for (;;) {
        if (f_bdone) break;
        if (!f_chunked && f_has_clen && got >= f_clen) break;
        n = recvfrom(fd, buf, FREEDOM_BUF, 0, 0, 0);
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
    putchar('\n');
    printf("freedom: %s (%d bytes)\n", host, got);
    return f_status;
}

int main(int argc, char **argv) {
    char url[192];
    int hops;
    if (argc < 2) {
        puts("usage: freedom [url-or-query]");
        return 1;
    }
    if (has_scheme(argv[1])) {
        if (strncmp(argv[1], "https://", 8) == 0) {
            puts("freedom: https needs TLS, which MiniOS does not speak yet");
            return 2;
        }
        if (strncmp(argv[1], "http://", 7) != 0) {
            make_search(f_path, argv[1], 128);
            memcpy(f_host, "html.duckduckgo.com", 19);
            f_host[19] = 0;
            f_port = 80;
            fetch(f_host, f_path, f_port);
            return 0;
        }
        {
            int l;
            l = strlen(argv[1]);
            if (l >= 192) l = 191;
            memcpy(url, argv[1], l);
            url[l] = 0;
        }
    } else if (looks_like_url(argv[1])) {
        append(url, 0, "http://", 192);
        append(url, 7, argv[1], 192);
    } else {
        make_search(f_path, argv[1], 128);
        memcpy(f_host, "html.duckduckgo.com", 19);
        f_host[19] = 0;
        f_port = 80;
        fetch(f_host, f_path, f_port);
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
    return 0;
}
