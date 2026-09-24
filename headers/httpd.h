/** Docstring: httpd.h -- Minimal static HTTP/1.0 server contract.
 *
 * Single source of truth for the `httpd` builtin's wire parsing and
 * response building. Header-only like pipe.h: pure bounded
 * string/number work over caller buffers, so tests/test_httpd.c (make
 * test-httpd) drives it on the host with no kernel stubs.
 *
 * Scope: GET only, one request per connection, Connection: close.
 * Paths are fail-closed (overlong, non-printable or `..` traversal
 * refuses); the kernel maps the surviving path through fs_resolve,
 * which clamps `..` at the filesystem root, so a hostile path can
 * never escape the served tree. */

#ifndef HTTPD_H
#define HTTPD_H

#define HTTPD_MAX_PATH 128u
#define HTTPD_MAX_REQ  2048u
#define HTTPD_HEAD_MAX 512u

#define HTTPD_ERR_BOUND (-1)
#define HTTPD_ERR_METHOD (-2)
#define HTTPD_ERR_PATH (-3)
#define HTTPD_ERR_VERSION (-4)

/** Docstring: Content type by file suffix. Unknown suffixes serve as
 * application/octet-stream, never refused. Null path reads as octet. */
static inline const char *httpd_ctype(const char *path) {
    unsigned long n, i;
    if (!path)
        return "application/octet-stream";
    n = 0u;
    while (path[n])
        n++;
    i = n;
    while (i > 0u && path[i - 1u] != '.' && path[i - 1u] != '/')
        i--;
    if (i == 0u || path[i - 1u] != '.')
        return "application/octet-stream";
    {
        const char *e = path + i;
        if ((e[0] == 'h' || e[0] == 'H') && (e[1] == 't' || e[1] == 'T') &&
                (e[2] == 'm' || e[2] == 'M') && (e[3] == 'l' || e[3] == 'L') &&
                e[4] == 0)
            return "text/html";
        if (e[0] == 't' && e[1] == 'x' && e[2] == 't' && e[3] == 0)
            return "text/plain";
        if (e[0] == 'c' && e[1] == 0)
            return "text/plain";
        if (e[0] == 'h' && e[1] == 0)
            return "text/plain";
        if (e[0] == 'p' && e[1] == 'n' && e[2] == 'g' && e[3] == 0)
            return "image/png";
        if (e[0] == 'w' && e[1] == 'a' && e[2] == 'd' && e[3] == 0)
            return "application/octet-stream";
        return "application/octet-stream";
    }
}

/** Docstring: Parse a GET request line out of a received buffer. Copies
 * the path (without the leading `/`, without query) into path_out.
 * Fails closed: non-GET is ERR_METHOD, overlong/unprintable/`..`
 * paths are ERR_PATH, a missing HTTP/ token is ERR_VERSION, a buffer
 * with no CRLF yet is ERR_BOUND (read more). */
static inline int httpd_parse_get(const char *req, unsigned long len,
        char *path_out, unsigned cap) {
    unsigned long i = 0u, n = 0u;
    if (!req || !path_out || cap == 0u)
        return HTTPD_ERR_BOUND;
    if (len < 5u || req[0] != 'G' || req[1] != 'E' || req[2] != 'T' ||
            req[3] != ' ')
        return HTTPD_ERR_METHOD;
    i = 4u;
    if (i < len && req[i] == '/')
        i++;
    n = 0u;
    while (i < len && req[i] != ' ' && req[i] != '\r' && req[i] != '\n' &&
            req[i] != '?') {
        unsigned char c = (unsigned char)req[i];
        if (c < 32u || c > 126u)
            return HTTPD_ERR_PATH;
        if (n + 1u >= cap)
            return HTTPD_ERR_PATH;
        path_out[n++] = req[i];
        i++;
    }
    if (req[i] == '?') {
        while (i < len && req[i] != ' ' && req[i] != '\r' && req[i] != '\n')
            i++;
    }
    path_out[n] = 0;
    if (n == 0u)
        return HTTPD_ERR_PATH;
    {
        unsigned long k;
        for (k = 0u; k + 1u < n; k++) {
            if (path_out[k] == '.' && path_out[k + 1u] == '.')
                return HTTPD_ERR_PATH;
        }
    }
    {
        unsigned long k = i;
        int spaced = 0;
        while (k < len && req[k] == ' ') {
            k++;
            spaced = 1;
        }
        if (!spaced)
            return HTTPD_ERR_VERSION;
        if (k + 5u > len || req[k] != 'H' || req[k + 1u] != 'T' ||
                req[k + 2u] != 'T' || req[k + 3u] != 'P' ||
                req[k + 4u] != '/')
            return HTTPD_ERR_VERSION;
    }
    return 0;
}

/** Docstring: Emit a response head into out. Returns the head length,
 * or HTTPD_ERR_BOUND past cap. body_len is the exact Content-Length;
 * the caller streams the body after the head. */
static inline int httpd_header(int code, const char *reason,
        const char *ctype, unsigned long body_len, char *out,
        unsigned cap) {
    unsigned long n = 0u;
    const char *p;
    if (!reason || !ctype || !out || cap == 0u)
        return HTTPD_ERR_BOUND;
    if (code < 100 || code > 599)
        return HTTPD_ERR_BOUND;
    {
        char num[4];
        num[0] = (char)('0' + (code / 100));
        num[1] = (char)('0' + ((code / 10) % 10));
        num[2] = (char)('0' + (code % 10));
        num[3] = 0;
        p = "HTTP/1.0 ";
        while (*p) {
            if (n + 1u >= cap)
                return HTTPD_ERR_BOUND;
            out[n++] = *p++;
        }
        for (p = num; *p; p++) {
            if (n + 1u >= cap)
                return HTTPD_ERR_BOUND;
            out[n++] = *p;
        }
        out[n++] = ' ';
        while (*reason) {
            if (n + 1u >= cap)
                return HTTPD_ERR_BOUND;
            out[n++] = *reason++;
        }
        p = "\r\nContent-Type: ";
        while (*p) {
            if (n + 1u >= cap)
                return HTTPD_ERR_BOUND;
            out[n++] = *p++;
        }
        while (*ctype) {
            if (n + 1u >= cap)
                return HTTPD_ERR_BOUND;
            out[n++] = *ctype++;
        }
        p = "\r\nContent-Length: ";
        while (*p) {
            if (n + 1u >= cap)
                return HTTPD_ERR_BOUND;
            out[n++] = *p++;
        }
        {
            char ds[12];
            int di = 0, k;
            unsigned long v = body_len;
            if (v == 0u)
                ds[di++] = '0';
            else {
                char rev[12];
                int ri = 0;
                while (v > 0u && ri < 11) {
                    rev[ri++] = (char)('0' + (v % 10u));
                    v /= 10u;
                }
                for (k = ri - 1; k >= 0; k--)
                    ds[di++] = rev[k];
            }
            ds[di] = 0;
            for (p = ds; *p; p++) {
                if (n + 1u >= cap)
                    return HTTPD_ERR_BOUND;
                out[n++] = *p;
            }
        }
        p = "\r\nConnection: close\r\n\r\n";
        while (*p) {
            if (n + 1u >= cap)
                return HTTPD_ERR_BOUND;
            out[n++] = *p++;
        }
    }
    if (n >= cap)
        return HTTPD_ERR_BOUND;
    out[n] = 0;
    return (int)n;
}

#endif
